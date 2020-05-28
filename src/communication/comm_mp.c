//=============================================================================
/**
 * @file	comm_mp.c
 * @brief	通信の接続を管理しているクラス  comm_system.c から分離
            最終的に WIFIライブラリと並列になっていく...予定

            comm_sys    ---   comm_mp         --   comm_local.c
                         |                     |--  wh.c
                         |
                         |
                         --   comm_wifi      --   comm_local.c
                                              |----wifi.lib

   
 * @author	Katsumi Ohno
 * @date    2006.01.25
 */
//=============================================================================


#include "common.h"
#include "wh_config.h"
#include "wh.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "comm_local.h"

#include "system/pm_str.h"
#include "system/gamedata.h"  //PERSON_NAME_SIZE

#include "comm_ring_buff.h"
#include "system/pm_rtc.h"  //GF_RTC
#include "system/savedata.h"
#include "savedata/regulation.h"

//==============================================================================
// extern宣言
//==============================================================================

// コンパイル時にワーニングが出るので定義してある
#include "communication/comm_system.h"


//==============================================================================
// 定義
//==============================================================================


#define _PORT_DATA_RETRANSMISSION   (14)    // 切断するまで無限再送を行う  こちらを使用している
#define _PORT_DATA_PARENT           _PORT_DATA_RETRANSMISSION
#define _PORT_DATA_CHILD            _PORT_DATA_RETRANSMISSION

#define _KEEP_CHANNEL_TIME_MAX   (5)

#define _NOT_INIT_BITMAP  (0xffff)   // 接続人数を固定に指定ない場合の値

typedef enum{    // 切断状態
    _DISCONNECT_NONE,
    _DISCONNECT_END,
    _DISCONNECT_SECRET,
    _DISCONNECT_STEALTH,
};

#define _BEACON_SIZE_MAX   MATH_MAX(sizeof(_GF_BSS_MYSTERY),sizeof(_GF_BSS_DATA_INFO))


//管理構造体定義
typedef struct{
    u8 mysteryData[MYSTERY_BEACON_DATA_SIZE];
    WMBssDesc sBssDesc[SCAN_PARENT_COUNT_MAX];  ///< 親機の情報を記憶している構造体
    u8  backupBssid[COMM_MACHINE_MAX][WM_SIZE_BSSID];   // 今まで接続していた
    u16 bconUnCatchTime[SCAN_PARENT_COUNT_MAX]; ///< 親機のビーコンを拾わなかった時間+データがあるかどうか
    void* _pWHWork;                           ///whライブラリが使用するワークのポインタ
    PMS_DATA pmsData;
    int sBeaconCount;                           ///< ビーコンカウンタ
//    MATHRandContext32 sRand;                    ///< wep用乱数キー
    u8 bScanCallBack;  ///< 親のスキャンがかかった場合TRUE, いつもはFALSE
    u8 regulationNo;   ///< ゲームレギュレーション
#ifdef PM_DEBUG		//DebugROM
    u8 soloDebugNo;
#endif
    /// ----------------------------子機用
    MYSTATUS* pMyStatus;            // 自分のステータス
    REGULATION* pRegulation;        // 探すレギュレーション 必要ない場合はNULL
//    u32 wepSeed;
    u32 ggid;
    u16 gameInfoBuff[WM_SIZE_USER_GAMEINFO];
    u16 keepChannelNo;
    u16 errCheckBitmap;      ///< このBITMAPが食い違うとエラーになる
    u8 channel;
    u8 keepChannelTime;
    u8 disconnectType;    ///< 切断状況
    u8 bSetReceiver;
    u8 bEndScan;  // endscan
    u8 bErrorState:1;     ///< エラーを引き起こしている場合その状態をもちます
    u8 bErrorDisconnectOther:1;     ///< 誰かが落ちるとエラーになります
    u8 bErrorNoChild:1;  ///< 子機が無い場合エラー扱いするかどうか
    u8 bTGIDChange:1;
    u8 bAutoExit:1;
    u8 bEntry:1;   // 子機の新規参入
//    u8 bStalth:1;
} _COMM_WORK;

//==============================================================================
// ワーク
//==============================================================================

///< ワーク構造体のポインタ
static _COMM_WORK* _pCommMP = NULL;

// 親機になる場合のTGID 構造体に入れていないのは
// 通信ライブラリーを切ったとしてもインクリメントしたいため
/// TGID管理
static u16 _sTgid = 0;


// WEP Key 作成用の共通鍵（親子で共通の鍵を使用する）
// アプリケーションごとに固有のものとすること
// ASCII 文字列である必要はなく、任意の長さのバイナリデータでよい
//static char* _sSecretKey = " http://www.gamefreak.co.jp/ ";



// コンポーネント転送終了の確認用
// イクニューモンコンポーネント処理を移動させるときはこれも移動
static volatile int   startCheck;	

//==============================================================================
// static宣言
//==============================================================================

static void _whInitialize(void);
static void _childDataInit(void);
static void _parentDataInit(BOOL bTGIDChange);
static void _commInit(void);
static void _setUserGameInfo( void );
static BOOL _isMachBackupMacAddress(u8* pMac);
static u16 _getServiceBeaconPeriod(u16 serviceNo);

static void _scanCallback(WMBssDesc *bssdesc);
static void _startUpCallback(void *arg, WVRResult result);
static void _indicateCallback(void *arg);
static int _connectNum(void);

//==============================================================================
/**
 * 接続クラスの初期化
 * @param   pMyStatus   MYSTATUSポインタ
 * @retval  none
 */
//==============================================================================

void CommMPInitialize(MYSTATUS* pMyStatus)
{
    int i;
    
    if(_pCommMP!=NULL){  // すでに初期化している場合はreturn
        return;
    }
    _pCommMP = (_COMM_WORK*)sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_WORK));
    MI_CpuClear8(_pCommMP, sizeof(_COMM_WORK));
    _pCommMP->_pWHWork = sys_AllocMemory(HEAPID_COMMUNICATION, WH_GetHeapSize());
    MI_CpuClear8(_pCommMP->_pWHWork, WH_GetHeapSize());
    _pCommMP->pRegulation = sys_AllocMemory(HEAPID_COMMUNICATION, Regulation_GetWorkSize());
    MI_CpuClear8(_pCommMP->pRegulation, Regulation_GetWorkSize());
    _pCommMP->ggid = _DP_GGID;
    _pCommMP->pMyStatus = pMyStatus;
	// 簡易会話初期化
	PMSDAT_Clear( (PMS_DATA*)&_pCommMP->pmsData );
    // 無線ライブラリ駆動開始
    _whInitialize();
}

BOOL CommMPIsConnect(void)
{
    if(_pCommMP){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * 比較関数
 * @param   pCmp1,pCmp2   比較対象
 * @retval  一致したらTRUE
 */
//==============================================================================

static BOOL _bmemcmp(const u8* pCmp1,const u8* pCmp2, int size)
{
    int i;
    const u8* pc1 = pCmp1;
    const u8* pc2 = pCmp2;

    for(i = 0; i < size; i++){
        if(*pc1 != *pc2){
            return FALSE;
        }
        pc1++;
        pc2++;
    }
    return TRUE;
}

//==============================================================================
/**
 * 子機が親機を探し出した時に呼ばれるコールバック関数
 * 親機を拾うたびに呼ばれる
 * @param   bssdesc   グループ情報
 * @retval  none
 */
//==============================================================================

static void DEBUG_MACDISP(char* msg,WMBssDesc *bssdesc)
{
    OHNO_PRINT("%s %02x%02x%02x%02x%02x%02x\n",msg,
               bssdesc->bssid[0],bssdesc->bssid[1],bssdesc->bssid[2],
               bssdesc->bssid[3],bssdesc->bssid[4],bssdesc->bssid[5]);
}

static void _scanCallback(WMBssDesc *bssdesc)
{
    int i;
    _GF_BSS_DATA_INFO* pGF;
    int serviceNo = CommStateGetServiceNo();
    int regulationNo = CommStateGetRegulationNo();
#ifdef PM_DEBUG		//DebugROM
    int soloDebugNo = CommStateGetSoloDebugNo();
#endif

    // catchした親データ
    pGF = (_GF_BSS_DATA_INFO*)bssdesc->gameInfo.userGameInfo;
    if(serviceNo == COMM_MODE_POKETCH){  // ポケッチは何でも拾う
    }
    else if(CommLocalIsUnionGroup(pGF->serviceNo) && CommLocalIsUnionGroup(serviceNo)){  // お互いを拾う
    }
    else if(pGF->pause && (pGF->serviceNo == COMM_MODE_UNDERGROUND)){
        OHNO_PRINT("pGF->pause\n");
        return;  // ポーズ中の親機は無視
    }
    else if(pGF->serviceNo != serviceNo){
//        DEBUG_MACDISP("サービスが異なる場合は拾わない\n",bssdesc);
        return;   // サービスが異なる場合は拾わない
    }
    if(pGF->regulationNo != regulationNo){
//        DEBUG_MACDISP("レギュレーションが異なる場合は拾わない\n",bssdesc);
        return;   // レギュレーションが異なる場合は拾わない
    }
#ifdef PM_DEBUG		//DebugROM
    if(serviceNo != COMM_MODE_POKETCH){
        if(pGF->soloDebugNo != soloDebugNo){
//            DEBUG_MACDISP("デバッグが異なる場合は拾わないx\n",bssdesc);
            return;   // デバッグ識別番号が異なる場合は拾わない
        }
    }
#endif
    
    // このループは同じものなのかどうか検査
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        if(_pCommMP->bconUnCatchTime[i] == 0 ){
            // 親機情報が入っていない場合continue
            continue;
        }
        if (_bmemcmp(_pCommMP->sBssDesc[i].bssid, bssdesc->bssid, WM_SIZE_BSSID)) {
#ifdef DEBUG_ONLY_FOR_mori
            OS_TPrintf("ビーコンを更新 %02x%02x%02x%02x%02x%02x\n",
                       bssdesc->bssid[0],bssdesc->bssid[1],bssdesc->bssid[2],
                       bssdesc->bssid[3],bssdesc->bssid[4],bssdesc->bssid[5]);
#endif
            // もう一度拾った場合にタイマー加算
            _pCommMP->bconUnCatchTime[i] = _DEFAULT_TIMEOUT_FRAME;
            // 新しい親情報を保存しておく。
            MI_CpuCopy8( bssdesc, &_pCommMP->sBssDesc[i], sizeof(WMBssDesc));

//            DEBUG_DUMP(pGF->regulationBuff, Regulation_GetWorkSize(),"受け取ったレギュ");
            return;
        }
    }
    // このループは空きがあるかどうか検査
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        if(_pCommMP->bconUnCatchTime[i] == 0 ){
            // 親機情報が入っていない場合break;
            break;
        }
    }
    if(i >= SCAN_PARENT_COUNT_MAX){
        // 構造体がいっぱいの場合は親機を拾わない
        // @@OO親機が多数存在する場合、検索機能とか必要と思われる
        return;
    }
    // 新しい親情報を保存しておく。
#ifdef DEBUG_ONLY_FOR_mori
    OS_TPrintf("新規親機ビーコンを拾った %02x%02x%02x%02x%02x%02x\n",
               bssdesc->bssid[0],bssdesc->bssid[1],bssdesc->bssid[2],
               bssdesc->bssid[3],bssdesc->bssid[4],bssdesc->bssid[5]);
#endif
    _pCommMP->bconUnCatchTime[i] = _DEFAULT_TIMEOUT_FRAME;
    MI_CpuCopy8( bssdesc, &_pCommMP->sBssDesc[i],sizeof(WMBssDesc));
    _pCommMP->bScanCallBack = TRUE;
}

//------------------------------------------------------------------
/**
 * 無線駆動制御ライブラリの非同期的な処理終了が通知されるコールバック関数。
 *
 * @param   arg		WVR_StartUpAsyncコール時に指定した引数。未使用。
 * @param   result	非同期関数の処理結果。
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _startUpCallback(void *arg, WVRResult result)
{
    if (result != WVR_RESULT_SUCCESS) {
        OS_TPanic("WVR_StartUpAsync error.[%08xh]\n", result);
    }
    else{
		OS_Printf("WVR Trans VRAM-D.\n");
	}
    startCheck = 2;
}

//------------------------------------------------------------------
/**
 * 無線駆動制御ライブラリの非同期的な処理終了が通知されるコールバック関数。
 *
 * @param   arg		WVR_StartUpAsyncコール時に指定した引数。未使用。
 * @param   result	非同期関数の処理結果。
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _endCallback(void *arg, WVRResult result)
{
    startCheck = 0;
    sys_SleepOK(SLEEPTYPE_COMM);  // スリープを許可する
}

//==============================================================================
/**
 * WVRをVRAMDに移動
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommVRAMDInitialize(void)
{
    //************************************
//	GX_DisableBankForTex();			// テクスチャイメージ

    sys_SleepNG(SLEEPTYPE_COMM);  // スリープを禁止
    // 無線ライブラリ駆動開始
	// イクニューモンコンポーネントをVRAM-Dに転送する
    startCheck = 1;
    if (WVR_RESULT_OPERATING != WVR_StartUpAsync(GX_VRAM_ARM7_128_D, _startUpCallback, NULL)) {
        OS_TPanic("WVR_StartUpAsync failed. \n");
    }
    else{
        OHNO_PRINT("WVRStart\n");
    }
}

//==============================================================================
/**
 * WVRをVRAMDに移動し終わったら1
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommIsVRAMDInitialize(void)
{
    return (startCheck==2);
}

//==============================================================================
/**
 * WVRをVRAMDに移動しはじめたら１
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommIsVRAMDStart(void)
{
    return (startCheck!=0);
}

//==============================================================================
/**
 * イクニューモン開放
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommVRAMDFinalize(void)
{
    OHNO_PRINT("VRAMD Finalize\n");
    WVR_TerminateAsync(_endCallback,NULL);  // イクニューモン切断
}


//==============================================================================
/**
 * 通信状態を知らせるのコールバック
 * @param   arg WMIndCallback構造体
 * @retval  none
 */
//==============================================================================
static void _indicateCallback(void *arg)
{
    WMIndCallback *cb;
    cb = (WMIndCallback *)arg;
    if (cb->state == WM_STATECODE_BEACON_RECV) {
        if(_pCommMP){
            _pCommMP->sBeaconCount = 2;
        }
    }
}

//==============================================================================
/**
 * WHライブラリの初期化
 * @param   bReInit  再初期化かどうか
 * @param   pLocal  通信共通構造体
 * @retval  none
 */
//==============================================================================

static void _whInitialize(void)
{
    
    _pCommMP->sBeaconCount = 0;

    
    // 無線初期化
    {
        u32 addr = (u32)_pCommMP->_pWHWork;
        addr = 32 - (addr % 32) + addr;   //32byteアライメント
        (void)WH_Initialize((void*)addr);
        (void)WM_SetIndCallback(_indicateCallback);
    }

    // WH 初期設定
    WH_SetGgid(_pCommMP->ggid);

    // WEP Key の種用の乱数生成機の初期化
//    CommRandSeedInitialize(&_pCommMP->sRand);
}

//==============================================================================
/**
 * 子機の使用しているデータの初期化
 * @param   bssdesc   グループ情報
 * @retval  none
 */
//==============================================================================

void ChildBconDataInit(void)
{
    int i;

    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        _pCommMP->bconUnCatchTime[i] = 0;
    }
    MI_CpuClear8(_pCommMP->sBssDesc,sizeof(WMBssDesc)*SCAN_PARENT_COUNT_MAX);
}

//==============================================================================
/**
 * 親機の使用しているデータの初期化
 * @param   bTGIDChange  新規のゲームの初期化の場合TRUE 古いビーコンでの誤動作を防ぐため用
 * @retval  none
 */
//==============================================================================

static void _parentDataInit(BOOL bTGIDChange)
{
    _pCommMP->bTGIDChange = bTGIDChange;
}

//==============================================================================
/**
 * 親子共通、通信の初期化をまとめた
 * @param   work_area 　システムで使うメモリー領域
 *                      NULLの場合すでに初期化済みとして動作
 * @retval  初期化に成功したらTRUE
 */
//==============================================================================

static void _commInit(void)
{
    _pCommMP->bScanCallBack = FALSE;
    _pCommMP->bErrorState = FALSE;
    _pCommMP->bErrorNoChild = FALSE;
    
    _pCommMP->disconnectType = _DISCONNECT_NONE;
    _pCommMP->bAutoExit = FALSE;
    _pCommMP->bEndScan = 0;

    _pCommMP->bSetReceiver = FALSE;
    
    return;
}


//==============================================================================
/**
 * 通信ライブラリに必要なワークサイズを返す
 * @param   none
 * @retval  ワークサイズ
 */
//==============================================================================
u32 CommGetWorkSize(void)
{
    OHNO_PRINT("_COMM_WORK size %d \n", sizeof(_COMM_WORK));
    return sizeof(_COMM_WORK);
}

//==============================================================================
/**
 * 親機の接続開始を行う
 * @param   work_area 　システムで使うメモリー領域
 *                      NULLの場合すでに初期化済みとして動作
 * @param   serviceNo     ゲームの種類
 * @param   regulationNo  ゲームの種類
 * @param   bTGIDChange  新規のゲームの初期化の場合TRUE 古いビーコンでの誤動作を防ぐため用
 * @param  子機を受け付けるかどうか
 * @retval  初期化に成功したらTRUE
 */
//==============================================================================
BOOL CommMPParentInit(BOOL bAlloc, BOOL bTGIDChange, BOOL bEntry)
{
    _commInit();
    _parentDataInit(bTGIDChange);

    WH_ParentDataInit();
    if(!_pCommMP->bSetReceiver){
        WH_SetReceiver(CommRecvParentCallback, _PORT_DATA_CHILD);
      _pCommMP->bSetReceiver = TRUE;
    }
    _pCommMP->bEntry = bEntry;

    // 電波使用率から最適なチャンネルを取得して接続する。非同期関数
    if(WH_GetSystemState() == WH_SYSSTATE_IDLE){
        if(WH_StartMeasureChannel()){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * 子機の接続開始を行う
 * @param   work_area 　システムで使うメモリー領域
 *                      NULLの場合はすでに初期化済みとして扱う
 * @param   serviceNo  ゲームの種類
 * @param   regulationNo  ゲームの種類
 * @param   bBconInit  ビーコンデータを初期化するのかどうか
 * @retval  初期化に成功したらTRUE
 */
//==============================================================================
BOOL CommMPChildInit(BOOL bAlloc, BOOL bBconInit)
{
    _commInit();
    if(bBconInit){
        OHNO_PRINT("ビーコンの初期化\n");
        ChildBconDataInit(); // データの初期化
    }
    if(!_pCommMP->bSetReceiver ){
        WH_SetReceiver(CommRecvCallback, _PORT_DATA_PARENT);
        _pCommMP->bSetReceiver = TRUE;
    }
    // 親機検索スタート
    if(WH_GetSystemState() == WH_SYSSTATE_IDLE){
        // MACアドレス指定　　全部FFで全てを探しにいく
        const u8 sAnyParent[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
        if(WH_StartScan(_scanCallback, sAnyParent, _SCAN_ALL_CHANNEL)){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * 通信切り替えを行う（親子反転に必要な処理）
 * @param   none
 * @retval  リセットしたらTRUE
 */
//==============================================================================

BOOL CommMPSwitchParentChild(void)
{
    if(!_pCommMP){
        return TRUE;
    }
    switch(_pCommMP->bEndScan){
      case 0:
        if(WH_IsSysStateScan()){
            WH_EndScan();
            _pCommMP->bEndScan = 1;
            break;
        }
        else if(WH_IsSysStateBusy()){  //しばらく待つ
        }
        else{
            WH_Finalize();
            _pCommMP->bEndScan = 2;
        }
        break;
      case 1:
        if(!WH_IsSysStateBusy()){
            WH_Finalize();
            _pCommMP->bEndScan = 2;
        }
        break;
      case 2:
        if(WH_IsSysStateIdle()){
            return TRUE;
        }
        if(WH_IsSysStateError()){
            _pCommMP->bEndScan = 1;
        }
        break;
    }
    return FALSE;
}

//==============================================================================
/**
 * 通信切断を行う  ここではあくまで通信終了手続きに入るだけ
 *  ホントに消すのは下の_commEnd
 * @param   none
 * @retval  終了処理に移った場合TRUE
 */
//==============================================================================
BOOL CommMPFinalize(void)
{
    if(_pCommMP){
        if(_pCommMP->disconnectType == _DISCONNECT_NONE){
            _pCommMP->disconnectType = _DISCONNECT_END;
            WH_Finalize();
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * 通信切断を行う  ただしメモリー開放を行わない
 * @param   切断の場合TRUE
 * @retval  none
 */
//==============================================================================
void CommMPStealth(BOOL bStalth)
{
    if(!_pCommMP){
        return;
    }
    if(bStalth){
        _pCommMP->disconnectType = _DISCONNECT_SECRET;
    }
    else{
        _pCommMP->disconnectType = _DISCONNECT_NONE;
        _whInitialize();  // 無線駆動再開
    }
}

//==============================================================================
/**
 * 通信の全てを消す
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _commEnd(void)
{
    sys_FreeMemoryEz(_pCommMP->pRegulation);
    sys_FreeMemoryEz(_pCommMP->_pWHWork);
    sys_FreeMemoryEz(_pCommMP);
    _pCommMP = NULL;
}

//==============================================================================
/**
 * 探すことができた親の数を返す
 * @param   none
 * @retval  親機の数
 */
//==============================================================================

int CommMPGetParentCount(void)
{
    int i, cnt;

    if(!CommIsInitialize()){
        return 0;
    }

    cnt = 0;
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        if(_pCommMP->bconUnCatchTime[i] != 0 ){
            cnt++;
        }
    }
    return cnt;
}

//--------------------------------------------------------------
/**
 * @brief   BmpListの位置からBconの存在するIndex位置を取得する
 * @param   index		BmpList位置
 * @retval  Index
 */
//--------------------------------------------------------------
int CommBmpListPosBconIndexGet(int index)
{
	int i, count;
	
//	for(i = 0; i < SCAN_PARENT_COUNT_MAX; i++){
//		OS_TPrintf("Listのビーコンチェック %d = %d\n", i, _pCommMP->bconUnCatchTime[i]);
//	}
	
	count = 0;
	for(i = 0; i < SCAN_PARENT_COUNT_MAX; i++){
		if(_pCommMP->bconUnCatchTime[i] != 0){
			if(count == index){
				return i;
			}
			count++;
		}
	}
	GF_ASSERT(0 && "ここには来ないはず");
	return 0;
}

//==============================================================================
/**
 * 親機リストに変化があった場合TRUE
 * @param   none
 * @retval  親機リストに変化があった場合TRUE なければFALSE
 */
//==============================================================================

BOOL CommMPIsScanListChange(void)
{
    return _pCommMP->bScanCallBack;
}

//==============================================================================
/**
 * 親機の変化を知らせるフラグをリセットする
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommMPResetScanChangeFlag(void)
{
    _pCommMP->bScanCallBack = FALSE;
}

//==============================================================================
/**
 * この親機がいくつとコネクションをもっているのかを得る
 * @param   index   親のリストのindex
 * @retval  コネクション数 0-16
 */
//==============================================================================

int CommMPGetParentConnectionNum(int index)
{
    int cnt;
    _GF_BSS_DATA_INFO* pGF;

    cnt = 0;
    if(_pCommMP->bconUnCatchTime[index] != 0){
        pGF = (_GF_BSS_DATA_INFO*)_pCommMP->sBssDesc[index].gameInfo.userGameInfo;
        if(pGF->connectNum==0){
            return 1;
        }
        return pGF->connectNum;
    }
    return 0;
}

//==============================================================================
/**
 * 接続人数に該当する親を返す
 * @param   none
 * @retval  親のindex
 */
//==============================================================================

static int _getParentNum(int machNum)
{
    int i,num;

    for (i = SCAN_PARENT_COUNT_MAX-1; i >= 0; i--) {
        num = CommMPGetParentConnectionNum(i);
        if((num > machNum) && (num < COMM_MACHINE_MAX)){
            return i;
        }
    }
    return -1;
}

//==============================================================================
/**
 * すぐに接続していい人が見つかった場合indexを返す
 * @param   none
 * @retval  該当したらindexを返す
 */
//==============================================================================

int CommMPGetFastConnectIndex(void)
{
    int i,num;

    if(CommMPGetParentCount()==0){
        return -1;
    }
    for (i = SCAN_PARENT_COUNT_MAX -1; i >= 0; i--) {
        if(_pCommMP->bconUnCatchTime[i] != 0){
            if(_isMachBackupMacAddress(&_pCommMP->sBssDesc[i].bssid[0])){  // 古いMACに合致
                num = CommMPGetParentConnectionNum(i);
                if(( num > 1) && (num < COMM_MACHINE_MAX)){      // 本親に該当した まだ参加可能
                    return i;
                }
            }
        }
    }
    return -1;
}

//==============================================================================
/**
 * 次のレベルで繋いでいい人がいたらそのindexを返します
 * @param   none
 * @retval  該当したらindexを返す
 */
//==============================================================================

int CommMPGetNextConnectIndex(void)
{
    int i;
 
    if(CommMPGetParentCount()==0){  // ビーコンが無い状態
        return -1;
    }
    for (i = SCAN_PARENT_COUNT_MAX-1; i >= 0; i--) {
        if(_pCommMP->bconUnCatchTime[i] != 0){
            if(_isMachBackupMacAddress(&_pCommMP->sBssDesc[i].bssid[0])){  // 古いMACに合致
                OHNO_PRINT("昔の親 %d\n",i);
                return i;
            }
        }
    }
    i = _getParentNum(1);
    if(i != -1 ){
        OHNO_PRINT("履歴なし本親 %d \n", i);
        return i;
    }
    i = _getParentNum(0);
    if(i != -1){
        OHNO_PRINT("履歴なし仮親 %d \n", i);
        return i;
    }
    return i;
}

//==============================================================================
/**
 * 親機リストをindex順に返す
 * @param   index      親のリストのindex
 * @param   pMyStatus  格納するMYSTATUSのポインタ
 * @retval  none
 */
//==============================================================================

void CommMPGetParentName(int index, MYSTATUS* pMyStatus)
{
    int i, cnt;
    _GF_BSS_DATA_INFO* pGF;

    cnt = 0;
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        if(_pCommMP->bconUnCatchTime[i] != 0){
            if(index == cnt){
                MyStatus_Copy( CommMPGetBconMyStatus(i), pMyStatus);
                return;
            }
            cnt++;
        }
    }
    OHNO_PRINT("名前を取得できなかった index = %d\n", index);
}

//==============================================================================
/**
 * 親機ぽけIDをindex順に返す
 * @param   index   親のリストのindex
 * @retval  pokeID
 */
//==============================================================================

u32 CommMPGetPokeID(int index)
{
    int i, cnt;
    _GF_BSS_DATA_INFO *pGF;

    cnt = 0;
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        if(_pCommMP->bconUnCatchTime[i] != 0 ){
            if(index == cnt){
                pGF = (_GF_BSS_DATA_INFO*)_pCommMP->sBssDesc[i].gameInfo.userGameInfo;
                return pGF->pokeID;
            }
            cnt++;
        }
    }
    return 0;
}

//==============================================================================
/**
 * 子機　MP状態で接続
 * @param   index   親のリストのindex
 * @retval  子機接続を親機に送ったらTRUE
 */
//==============================================================================
BOOL CommMPChildIndexConnect(u16 index)
{
    int serviceNo;
    
    if (WH_GetSystemState() == WH_SYSSTATE_SCANNING) {
        (void)WH_EndScan();
        return FALSE;
    }
    if (WH_GetSystemState() == WH_SYSSTATE_IDLE) {
        OHNO_PRINT("子機 接続開始 WH_ChildConnect\n");
        serviceNo = CommStateGetServiceNo();
        _pCommMP->channel = _pCommMP->sBssDesc[index].channel;
        if(CommLocalIsUnionGroup(serviceNo)){
           WH_ChildConnectAuto(WH_CONNECTMODE_MP_CHILD, _pCommMP->sBssDesc[index].bssid,0);
        }
        else{
            WH_ChildConnect(WH_CONNECTMODE_MP_CHILD, &(_pCommMP->sBssDesc[index]));
        }
//        WH_ChildConnectAuto(WH_CONNECTMODE_MP_CHILD, _pCommMP->sBssDesc[index].bssid,0);
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * ビーコンデータの定期確認
 *  接続が完了する間での間、この関数を呼び、タイムアウト処理を行う
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommMPParentBconCheck(void)
{
    int id;

    for(id = 0; id < SCAN_PARENT_COUNT_MAX; id++){
        if(_pCommMP->bconUnCatchTime[id] == 0 ){
            continue;
        }
        if(_pCommMP->bconUnCatchTime[id] > 0){
            _pCommMP->bconUnCatchTime[id]--;
            if(_pCommMP->bconUnCatchTime[id] == 0){
                OHNO_PRINT("親機反応なし %d\n", id);
                _pCommMP->bScanCallBack = TRUE;   // データを変更したのでTRUE
            }
        }
    }
}

//==============================================================================
/**
 *  ユーザ定義の親機情報を設定します。
 *  _GF_BSS_DATA_INFO構造体の中身を送ります
 *  @param   userGameInfo  ユーザ定義の親機情報へのポインタ
 *  @param   length        ユーザ定義の親機情報のサイズ
 *  @retval  none
 */
//==============================================================================
static void _setUserGameInfo( void )
{
    u8 macBuff[6];
    MYSTATUS* pMyStatus;
    _GF_BSS_DATA_INFO* pGF;
    _GF_BSS_MYSTERY* pMist;
    int serviceNo = CommStateGetServiceNo();

    pMyStatus = CommMPGetMyStatus();
    if(serviceNo != COMM_MODE_MYSTERY){
        pGF = (_GF_BSS_DATA_INFO*)_pCommMP->gameInfoBuff;

        GF_ASSERT(COMM_SEND_REGULATION_SIZE >= Regulation_GetWorkSize());  // regulationが予定より大きい
        GF_ASSERT(COMM_SEND_MYSTATUS_SIZE == MyStatus_GetWorkSize());  // mystatusが予定より大きい
        GF_ASSERT(WM_SIZE_USER_GAMEINFO >= _BEACON_SIZE_MAX);  // bconサイズよりGFビーコンが大きい

        MI_CpuCopy8( pMyStatus, pGF->myStatusBuff, MyStatus_GetWorkSize());
        MI_CpuCopy8( _pCommMP->pRegulation,pGF->regulationBuff, Regulation_GetWorkSize());
        pGF->pokeID = MyStatus_GetID(pMyStatus);
        pGF->serviceNo = CommStateGetServiceNo();
        pGF->regulationNo = CommStateGetRegulationNo();
        // 簡易会話
        MI_CpuCopy8( &_pCommMP->pmsData, &pGF->pmsData, sizeof(PMS_DATA));
#ifdef PM_DEBUG		//DebugROM
        pGF->soloDebugNo = CommStateGetSoloDebugNo();
#endif
        pGF->pause = WHGetParentConnectPause();
    }
    else{
        pMist = (_GF_BSS_MYSTERY*)_pCommMP->gameInfoBuff;

        pMist->pokeID = MyStatus_GetID(pMyStatus);
        pMist->serviceNo = CommStateGetServiceNo();
        pMist->regulationNo = CommStateGetRegulationNo();
#ifdef PM_DEBUG		//DebugROM
        pMist->soloDebugNo = CommStateGetSoloDebugNo();
#endif
        MI_CpuCopy8(_pCommMP->mysteryData, pMist->mysteryData, MYSTERY_BEACON_DATA_SIZE);
    }
    DC_FlushRange(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX);
    WH_SetUserGameInfo(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX);
}


//==============================================================================
/**
 *  ユーザ定義の親機情報の 人数部分を監視し常に更新する
 *  _GF_BSS_DATA_INFO構造体の中身を送ります
 *  @param   none
 *  @retval  none
 */
//==============================================================================
static void _funcBconDataChange( void )
{
    _GF_BSS_DATA_INFO* pGF = (_GF_BSS_DATA_INFO*)_pCommMP->gameInfoBuff;

    if(_connectNum() != pGF->connectNum){
        pGF->connectNum = _connectNum();
        DC_FlushRange(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX);
        WH_SetUserGameInfo(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX);
        WHSetGameInfo(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX,
                      _pCommMP->ggid,_sTgid);
    }
}

//==============================================================================
/**
 * 通信ライブラリー内部の状態を見て、処理をする関数
 * VBlankとは関係ないのでprocessの時に処理すればいい
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _stateProcess(u16 bitmap)
{
    int state = WH_GetSystemState();
    CommInfoFunc();
    _funcBconDataChange();      // ビーコンの中身を書き換え中
    if((WH_GetCurrentAid() == COMM_PARENT_ID) && (!CommMPIsChildsConnecting())){
        if(_pCommMP->bErrorNoChild){
            _pCommMP->bErrorState = TRUE;   ///< エラーを引き起こしている場合その状態をもちます
//            OHNO_PRINT("エラー中 NOCHILD \n");
        }
    }
    if(_pCommMP->errCheckBitmap == _NOT_INIT_BITMAP){
        _pCommMP->errCheckBitmap = bitmap;  // このときの接続人数を保持
    }
    if(_pCommMP->bErrorDisconnectOther){ // エラー検査を行う
        if(_pCommMP->errCheckBitmap > bitmap){  // 切断した場合必ず数字が減る 増える分にはOK
            _pCommMP->bErrorState = TRUE;   ///< エラーを引き起こしている場合その状態をもちます
//            OHNO_PRINT("エラー中 誰か落ちた \n");
        }
    }
    if(WH_ERRCODE_FATAL == WH_GetLastError()){
        CommFatalErrorFunc(0);  // 割り込み中に画面表示をできないので移動
    }
    switch (state) {
      case WH_SYSSTATE_STOP:
        if(_pCommMP->disconnectType == _DISCONNECT_END){
            OHNO_SP_PRINT("WHEnd を呼んで終了しました\n");
            _commEnd();  // ワークから何から全て開放
            return;
        }
        if(_pCommMP->disconnectType == _DISCONNECT_SECRET){
            OHNO_SP_PRINT("WHEnd を呼んで死んだふり開始\n");
            _pCommMP->disconnectType = _DISCONNECT_STEALTH;
            return;
        }
        break;
      case WH_SYSSTATE_IDLE:
        if(_pCommMP->disconnectType == _DISCONNECT_END){
            if(WH_End()){
                return;
            }
        }
        if(_pCommMP->disconnectType == _DISCONNECT_SECRET){
            if(WH_End()){
                return;
            }
        }
        break;
      case WH_SYSSTATE_CONNECT_FAIL:
      case WH_SYSSTATE_ERROR:
        OHNO_PRINT("エラー中 %d \n",WH_GetLastError());
        if(_pCommMP){
            _pCommMP->bErrorState = TRUE;   ///< エラーを引き起こしている場合その状態をもちます
        }
        break;
      case WH_SYSSTATE_MEASURECHANNEL:
        {
            u16 channel;
            // 利用可能な中から一番使用率の低いチャンネルを返します。
            channel = WH_GetMeasureChannel();  //WH_SYSSTATE_MEASURECHANNEL => WH_SYSSTATE_IDLE
            if(_pCommMP->keepChannelTime==0){
                _pCommMP->keepChannelNo = channel;
                _pCommMP->keepChannelTime = _KEEP_CHANNEL_TIME_MAX;
            }
            else{
                _pCommMP->keepChannelTime--;
            }
            channel = _pCommMP->keepChannelNo;  
            if(_pCommMP->bTGIDChange){
                _sTgid++;
            }
            _setUserGameInfo();
//            OHNO_PRINT("親機接続開始   tgid=%d channel=%d \n",_sTgid, channel);
            (void)WH_ParentConnect(WH_CONNECTMODE_MP_PARENT,
                                   _sTgid, channel,
                                   CommLocalGetServiceMaxEntry(CommStateGetServiceNo()),
                                   _getServiceBeaconPeriod(CommStateGetServiceNo()),
                                   _pCommMP->bEntry);
            _pCommMP->channel = channel;
        }
        break;
      default:
        break;
    }

}

//==============================================================================
/**
 * 通信ライブラリー内部の状態を見て、処理をする関数
 * VBlankとは関係ないのでprocessの時に処理すればいい
 * 子機はお互いの接続がわからないので、通信結果をcommsystemからもらってエラー検査する
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommMpProcess(u16 bitmap)
{
    if(_pCommMP){
        _stateProcess(bitmap);
    }
}

//==============================================================================
/**
 * 通信可能状態なのかどうかを返す
 * @param   親子機のnetID
 * @retval  TRUE  通信可能    FALSE 通信切断
 */
//==============================================================================
static BOOL _isConnect(u16 netID)
{
    if(!_pCommMP){
        return FALSE;
    }
    if (WH_GetSystemState() != WH_SYSSTATE_CONNECTED) {
        return FALSE;
    }
    {
        u16 bitmap = WH_GetBitmap();
        if( bitmap & (1<<netID)){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * 通信可能状態の人数を返す
 * @param   none
 * @retval  接続人数
 */
//==============================================================================
static int _connectNum(void)
{
    int num = 0,i;

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(_isConnect(i)){
            num++;
        }
    }
    return num;
}

//==============================================================================
/**
 * 通信切断モードにはいったかどうか
 * @param   none
 * @retval  接続人数
 */
//==============================================================================

BOOL CommMPIsConnectStalth(void)
{
    if(_pCommMP && (_pCommMP->disconnectType == _DISCONNECT_STEALTH)){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * 初期化しているかどうかを返す
 * @param   none
 * @retval  初期が終わっていたらTRUE
 */
//==============================================================================
BOOL CommMPIsInitialize(void)
{
    return (_pCommMP!=NULL);
}

//==============================================================================
/**
 * WHライブラリで　状態がIDLEになっているか確認する
 * @param   none
 * @retval  IDLEになっている=TRUE
 */
//==============================================================================

BOOL CommMPIsStateIdle(void)
{
    if(_pCommMP){
        return WH_IsSysStateIdle();
    }
    return TRUE;
}


//==============================================================================
/**
 * WHライブラリで　通信状態のBITを確認  子機がつながっているかどうか
 * @param   none
 * @retval  つながったらTRUE
 */
//==============================================================================

BOOL CommMPIsChildsConnecting(void)
{
    if(_pCommMP){
        return( WH_GetBitmap() & 0xfffe);
    }
    return FALSE;
}

//==============================================================================
/**
 * 親機が落ちたかどうか
 * @param   none
 * @retval  落ちた場合TRUE
 */
//==============================================================================

BOOL CommMPParentDisconnect(void)
{
    if(CommMPIsError() && ( WH_ERRCODE_DISCONNECTED == WH_GetLastError())){
        return TRUE;
    }
    return FALSE;
}


//==============================================================================
/**
 * エラー状態かどうか
 * @param   none
 * @retval  エラーの時TRUE
 */
//==============================================================================

BOOL CommMPIsError(void)
{
    if(_pCommMP){
        if(_pCommMP->bErrorState){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * 子機がいないのをエラー扱いにするかどうかをSET
 * @param   bOn  有効時にTRUE
 * @retval  none
 */
//==============================================================================

void CommMPSetNoChildError(BOOL bOn)
{
    if(_pCommMP){
        _pCommMP->bErrorNoChild = bOn;
    }
}

//==============================================================================
/**
 * 誰かが落ちたのをエラー扱いにするかどうかをSET
 * @param   bOn  有効時にTRUE
 * @retval  none
 */
//==============================================================================

void CommMPSetDisconnectOtherError(BOOL bOn)
{
    if(_pCommMP){
        _pCommMP->bErrorDisconnectOther = bOn;
        _pCommMP->errCheckBitmap = _NOT_INIT_BITMAP;
    }
}

//==============================================================================
/**
 * サービス番号に対応したビーコン間隔を得ます
 * サービス番号は include/communication/comm_def.hにあります
 * @param   serviceNo サービス番号
 * @retval  beacon間隔 msec
 */
//==============================================================================

u16 _getServiceBeaconPeriod(u16 serviceNo)
{
    u16 beaconPeriod = WM_GetDispersionBeaconPeriod();
    GF_ASSERT_RETURN(serviceNo < COMM_MODE_MAX, beaconPeriod);

    if(COMM_MODE_UNDERGROUND == serviceNo){
        return beaconPeriod/4;
    }
    if((COMM_MODE_UNION == serviceNo) ||
       (COMM_MODE_PICTURE == serviceNo)){
        return (beaconPeriod / 4);
    }
    return beaconPeriod;
}

//==============================================================================
/**
 * ビーコンデータを得る
 * @param   index ビーコンバッファに対するindex
 * @retval   WMBssDesc*  ビーコンバッファポインタ
 */
//==============================================================================

WMBssDesc* CommMPGetWMBssDesc(int index)
{
    if(_pCommMP && (_pCommMP->bconUnCatchTime[index]!=0)){
        return &_pCommMP->sBssDesc[index];
    }
    return NULL;
}

//==============================================================================
/**
 * GFビーコンデータを得る
 * @param   index ビーコンバッファに対するindex
 * @retval   GF_BSS_DATA_INFO*  ビーコンバッファポインタ
 */
//==============================================================================

_GF_BSS_DATA_INFO* CommMPGetGFBss(int index)
{
    if(_pCommMP && (_pCommMP->bconUnCatchTime[index]!=0)){
        return (_GF_BSS_DATA_INFO*)_pCommMP->sBssDesc[index].gameInfo.userGameInfo;
    }
    return NULL;
}

//==============================================================================
/**
 * ビーコンデータを消す
 * @param    index ビーコンバッファに対するindex
 * @retval   none
 */
//==============================================================================

void CommMPResetWMBssDesc(int index)
{
    if(_pCommMP && (_pCommMP->bconUnCatchTime[index]!=0)){
        _pCommMP->bconUnCatchTime[index] = 0;
    }
}

//==============================================================================
/**
 * ビーコンデータを消す
 * @param    index ビーコンバッファに対するindex
 * @retval   none
 */
//==============================================================================

void CommMPResetGFBss(int index)
{
    if(_pCommMP && (_pCommMP->bconUnCatchTime[index]!=0)){
        _pCommMP->bconUnCatchTime[index] = 0;
    }
}

//==============================================================================
/**
 * 通信用に自分のMYSTATUSを得る
 * @param    none
 * @retval   MYSTATUS*
 */
//==============================================================================

MYSTATUS* CommMPGetMyStatus(void)
{
    return _pCommMP->pMyStatus;
}

//==============================================================================
/**
 * BCON内に含まれるMYSTATUSを返す
 * @param   index   親のリストのindex
 * @retval  MYSTATUS*
 */
//==============================================================================

MYSTATUS* CommMPGetBconMyStatus(int index)
{
    MYSTATUS* pMyStatus;
    _GF_BSS_DATA_INFO* pGF;
    
    if(_pCommMP->bconUnCatchTime[index] == 0){
        return NULL;
    }
    pGF = (_GF_BSS_DATA_INFO*)_pCommMP->sBssDesc[index].gameInfo.userGameInfo;
    pMyStatus = (MYSTATUS*)&pGF->myStatusBuff[0];
    return pMyStatus;
}

//==============================================================================
/**
 * macアドレスをバックアップする
 * @param   pMac   mac address
 * @retval  none
 */
//==============================================================================

void CommMPSetBackupMacAddress(u8* pMac, int netID)
{
    if(_pCommMP){
        GF_ASSERT_RETURN(netID < COMM_MACHINE_MAX,);
        MI_CpuCopy8(pMac, _pCommMP->backupBssid[netID], WM_SIZE_BSSID);
    }
}

//==============================================================================
/**
 * バックアップしたMACアドレスに該当するかどうかを得る
 * @param   pMac   mac address
 * @retval  none
 */
//==============================================================================

static BOOL _isMachBackupMacAddress(u8* pMac)
{
    int i;
    
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(WM_IsBssidEqual(_pCommMP->backupBssid[i], pMac)){
            return TRUE;
        }
    }
    return FALSE;
}


//==============================================================================
/**
 * 自動切断モードに入ったかどうかを返す
 * @param   none
 * @retval  入っているならばTRUE
 */
//==============================================================================

BOOL CommMPIsAutoExit(void)
{
    if(_pCommMP){
        return _pCommMP->bAutoExit;
    }
    return FALSE;
}

//==============================================================================
/**
 * 自動切断モードON
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommMPSetAutoExit(void)
{
    if(_pCommMP){
        _pCommMP->bAutoExit = TRUE;
    }
}

//==============================================================================
/**
 * 自分のBCONのPMSデータを書き換える この関数はCommMPFlashMyBssを呼ぶことで反映される
 * @param   PMS_DATA
 * @retval  none
 */
//==============================================================================

void CommMPSetMyPMS(PMS_DATA* pPMS)
{
    MI_CpuCopy8( pPMS, &_pCommMP->pmsData, sizeof(PMS_DATA));
}


//==============================================================================
/**
 * 自分のBCONのレギュレーションデータを書き換える この関数はCommMPFlashMyBssを呼ぶことで反映される
 * @param   pRegulation  レギュレーションデータ構造体のポインタ
 * @retval  none
 */
//==============================================================================

void CommMPSetMyRegulation(void* pRegulation)
{

    MI_CpuCopy8( pRegulation,_pCommMP->pRegulation, Regulation_GetWorkSize());
}

//==============================================================================
/**
 * ビーコンデータに現在の状況を反映させる
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommMPFlashMyBss(void)
{
    _setUserGameInfo();
    WHSetGameInfo(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX,
                  _pCommMP->ggid,_sTgid);
}

//==============================================================================
/**
 * ライフタイムを小さくする または元に戻す
 * @param   bMinimum TRUEなら小さくする
 * @retval  none
 */
//==============================================================================

void CommMPSetLifeTime(BOOL bMinimum)
{
    WHSetLifeTime(bMinimum);
}

//------------------------------------------------------
/**
 * @brief   サービス番号のビーコン数を返します
 * @param   serviceNo   comm_def.hにあるサービス番号
 * @retval  利用者数
 */
//------------------------------------------------------

int CommMPGetServiceNumber(int serviceNo)
{
    int i,num=0;
    
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; i++) {
        _GF_BSS_DATA_INFO* pGF = CommMPGetGFBss(i);
        if(pGF){
            if( pGF->serviceNo == serviceNo){
                num += pGF->connectNum;
            }
        }
    }
    //
    return num;
}

//------------------------------------------------------
/**
 * @brief   親機が一回でもビーコンを送信し終わったかどうか
 * @param   none
 * @retval  送信完了=TRUE
 */
//------------------------------------------------------

BOOL CommMPIsParentBeaconSent(void)
{
    return HWIsParentBeaconSent();
}

//------------------------------------------------------
/**
 * @brief   スキャン状態かどうか
 * @param   none
 * @retval  送信完了=TRUE
 */
//------------------------------------------------------

BOOL CommMPIsChildStateScan(void)
{
    return WH_IsSysStateScan();
}

//------------------------------------------------------
/**
 * @brief   ビーコンデータに自由にデータを載せます
 * @param   pData   データ   COMM_SEND_REGULATION_SIZEまでのっかります
 * @retval  none
 */
//------------------------------------------------------

void CommMPSetBeaconTempData(void* pData)
{
    MI_CpuCopy8(pData,_pCommMP->mysteryData,MYSTERY_BEACON_DATA_SIZE);
    CommMPFlashMyBss();
}

//------------------------------------------------------
/**
 * @brief   ビーコンデータからデータを引き出します
 * @param   index     何番目のビーコンなのか
 * @retval  データポインタ
 */
//------------------------------------------------------

const void* CommMPGetBeaconTempData(int index)
{
    if(_pCommMP && (_pCommMP->bconUnCatchTime[index]!=0)){
        _GF_BSS_MYSTERY* pMyst;
        pMyst = (_GF_BSS_MYSTERY*)_pCommMP->sBssDesc[index].gameInfo.userGameInfo;
        return pMyst->mysteryData;
    }
    return NULL;
}

//------------------------------------------------------
/**
 * @brief   チャンネルを返す
 * @retval  接続チャンネル
 */
//------------------------------------------------------

int CommMPGetChannel(void)
{
    return _pCommMP->channel;
}

//==============================================================================
/**
 * @brief	自機ビーコン送信内容の取得
 */
//==============================================================================
void * CommMPGetMyGFBss(void)
{
	if (_pCommMP == NULL) {
		return NULL;
	}
	return _pCommMP->gameInfoBuff;
}

//------------------------------------------------------
/**
 * @brief	ビーコンを拾ってからのカウントダウンタイマ取得
 * @param	index	位置
 */
//------------------------------------------------------
int CommMPGetBConUncacheTime(int index)
{
	if (_pCommMP == NULL) {
		return 0;
	}
	return _pCommMP->bconUnCatchTime[index];
}

