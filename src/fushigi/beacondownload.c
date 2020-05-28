/**
 * @version "$Id: beacondownload.c,v 1.3 2006/08/09 09:29:51 mitsuhara Exp $"
 *
 * @file beacondownload.cpp
 * @brief ビーコンを使用したデータダウンロード処理
 * 
 */
 
 
#include <nitro.h>
#include <nitro/wm.h>
#include <nitro/cht.h>
#include "beacondownload.h"
#include "nitrocrypto/crypto.h"

/* ======================================================================
   送受信するデータのゲームデータ構造体
   ====================================================================== */  
#define BSDOWN_ONEPACKET_SIZE (WM_SIZE_USER_GAMEINFO - 8)
#define BSDOWN_PACKET_MAXSIZE ((BSOWN_MAXSIZE - 1) / BSDOWN_ONEPACKET_SIZE + 1)
typedef struct
{
	u16 crc;							// 送信するスクリプトのCRC
	u16 index;							// このビーコンの通し番号
	u32 size;							// 送ろうとしているスクリプトの大きさ
	u8 data[BSDOWN_ONEPACKET_SIZE];	// データ本体（１０４バイト）
} BSDOWN_GAMEINFO_STRUCT;

/* ======================================================================
  作業領域のデータ構造体
   ====================================================================== */
typedef struct
{
	/* WM 用システムワーク領域バッファ */
	u8  WmBuffer[ WM_SYSTEM_BUF_SIZE ] ATTRIBUTE_ALIGN(32);
	WMBssDesc BssDesc ATTRIBUTE_ALIGN(32);	
	WMScanParam ScanParam ATTRIBUTE_ALIGN(32);
	u8 fileinfo[BSDOWN_ONEPACKET_SIZE];
	int infoflag;
	CRYPTORC4Context rc4context;
	int SysState;
	// エラーコード格納用
	int ErrCode;	
	
	u16 state;	  // 現在の状況
	u16 crc;	  // 現在受信中のデータのCRC（識別に利用）
	u16 packets;  // 現在受信中のデータは、何分割されて送られてくるか
	u16 received; // 現在何個のパケットを受け取ったか
	u32 size;	  // 現在受信中のデータのサイズ
	u32 count;
	int index;	  // 一番最後に受け取ったパケットの通し番号（親機が今、どのあたりを送信しているかを判断するため）
	int linklevel;
	u8 macaddress[6];
	u16 channel;
	u8 *target;	  // スクリプトを保存する先。４バイトアライメントされている必要があります。
	BSDOWN_CALLBACK callback;
	u8 flags[ BSDOWN_PACKET_MAXSIZE ];	// どのパケットが送られて来るか。
} BSDOWN_WORK;

enum
{
	BSDOWNSTATE_STOP,			// 初期状態
	BSDOWNSTATE_STARTSCAN,		// スキャンを開始しようとしているところ
	BSDOWNSTATE_SCANNING,		// スキャン中（ビーコン受信前）
	BSDOWNSTATE_RECEVING,		// 一回でもビーコンを受け取ったことがある状態
	BSDOWNSTATE_COMPLETE,		// 受信完了
	
	BSDOWNSTATE_SIZE	
};

/* ======================================================================
   static contents
   ====================================================================== */

enum 
{
    mywh_SYSSTATE_STOP,           // 初期状態
    mywh_SYSSTATE_IDLE,           // 待機中
    mywh_SYSSTATE_SCANNING,       // スキャン中
    mywh_SYSSTATE_BUSY,           // 接続作業中
    mywh_SYSSTATE_CONNECTED,      // 接続完了（この状態で通信可能）
    mywh_SYSSTATE_DATASHARING,    // data-sharing有効で接続完了
    mywh_SYSSTATE_KEYSHARING,     // key-sharing有効で接続完了
    mywh_SYSSTATE_MEASURECHANNEL, // チャンネルの電波使用率をチェック
    mywh_SYSSTATE_CONNECT_FAIL,   // 親機への接続失敗
    mywh_SYSSTATE_ERROR,          // エラー発生
    mywh_SYSSTATE_FATAL,          // FATALエラー発生
    mywh_SYSSTATE_NUM
};

enum 
{
    mywh_CONNECTMODE_MP_PARENT,  // 親機 MP 接続モード
    mywh_CONNECTMODE_MP_CHILD,   // 子機 MP 接続モード
    mywh_CONNECTMODE_KS_PARENT,  // 親機 key-sharing 接続モード
    mywh_CONNECTMODE_KS_CHILD,   // 子機 key-sharing 接続モード
    mywh_CONNECTMODE_DS_PARENT,  // 親機 data-sharing 接続モード
    mywh_CONNECTMODE_DS_CHILD,   // 子機 data-sharing 接続モード
    mywh_CONNECTMODE_NUM
};

enum {
    // 自前のエラーコード
    mywh_ERRCODE_DISCONNECTED      = WM_ERRCODE_MAX, // 親から切断された
    mywh_ERRCODE_PARENT_NOT_FOUND,                   // 親がいない
    mywh_ERRCODE_NO_RADIO,                           // 無線使用不可
    mywh_ERRCODE_LOST_PARENT,                        // 親を見失った
    mywh_ERRCODE_NOMORE_CHANNEL,                     // すべてのチャンネルの調査を終えた
    mywh_ERRCODE_MAX
};
#define mywh_DMA_NO                 2
typedef void (*WHStartScanCallbackFunc)( WMBssDesc* bssDesc );

static BSDOWN_WORK *s_work_ptr;   
#define s_work (*s_work_ptr)
//static BSDOWN_WORK s_work;   







// はじめてデータを受けとったとき。
static void bsdown_c_startdownload( BSDOWN_GAMEINFO_STRUCT *info );
// 受信ステップ。
static int bsdown_c_step( BSDOWN_GAMEINFO_STRUCT *info );

/* デバッグ出力フック関数 */
static void (*wh_trace)(const char *, ...) =
#if !defined(SDK_FINALROM)
    OS_TPrintf;
#else
    NULL;
#endif


/* ======================================================================
   state functions
   ====================================================================== */


#define mywh_MAX(a, b) ( ((a) > (b)) ? (a) : (b) )

/* 不定期な通知を受け取る関数 */
static void mywh_IndicateHandler( void* arg );

/* (stateless) -> READY -> STOP -> IDLE */
static BOOL mywh_StateInInitialize(void);

static void mywh_StateOutInitialize(void *arg);


/* IDLE -> SCAN */
static BOOL mywh_StateInStartScan(void);
static void mywh_StateOutStartScan(void *arg);

/* SCAN -> IDLE */
static BOOL mywh_StateInEndScan(void);
static void mywh_StateOutEndScan(void *arg);

/* IDLE -> STOP -> READY -> (stateless) */
static BOOL mywh_StateInPowerOff(void);
static void mywh_StateOutPowerOff(void *arg);
static BOOL mywh_StateInDisable(void);
static void mywh_StateOutDisable(void *arg);
static void mywh_StateOutEnd( void *arg );

/* X -> IDLE */
static BOOL mywh_StateInReset(void);
static void mywh_StateOutReset(void *arg);


/* ======================================================================
   debug codes
   ====================================================================== */
#define WMHIGH_DEBUG

#if defined(WMHIGH_DEBUG)

#define WH_TRACE    if(wh_trace) wh_trace

#define WH_TRACE_STATE OS_TPrintf("%s s_work.SysState = %d\n", __func__, s_work.SysState)

#define mywh_REPORT_FAILURE(result)                \
    do{ OS_TPrintf("Failed in %s, %s = %s\n",      \
                  __func__,                      \
                  #result,                       \
                  mywh_GetWMErrCodeName(result));  \
        mywh_SetError(result); }while(0)

#define mywh_ASSERT(exp) \
    (void) ((exp) || (OSi_Panic(__FILE__, __LINE__, "Failed assertion " #exp), 0))

#else /* defined(WMHIGH_DEBUG) */

#define WH_TRACE_STATE              /* */
#define WH_TRACE(...)               ((void)0)
#define mywh_REPORT_FAILURE(result)   mywh_SetError(result)
#define mywh_ASSERT(exp)              ((void) 0)

#endif



#if defined(WMHIGH_DEBUG)
static const char *sStateNames[] = {
    "WM_STATE_READY",
    "WM_STATE_STOP",
    "WM_STATE_IDLE",
    "WM_STATE_CLASS1",
    "WM_STATE_TESTMODE",
    "WM_STATE_SCAN",
    "WM_STATE_CONNECT",
    "WM_STATE_PARENT",
    "WM_STATE_CHILD",
    "WM_STATE_MP_PARENT",
    "WM_STATE_MP_CHILD",
    "WM_STATE_DCF_CHILD",
};

static const char *mywh_GetWMErrCodeName(int result)
{
    static const char *errnames[] = {
        "WM_ERRCODE_SUCCESS",
        "WM_ERRCODE_FAILED",
        "WM_ERRCODE_OPERATING",
        "WM_ERRCODE_ILLEGAL_STATE",
        "WM_ERRCODE_WM_DISABLE",
        "WM_ERRCODE_NO_DATASET",
        "WM_ERRCODE_INVALID_PARAM",
        "WM_ERRCODE_NO_CHILD",
        "WM_ERRCODE_FIFO_ERROR",
        "WM_ERRCODE_TIMEOUT",
        "WM_ERRCODE_SEND_QUEUE_FULL",
        "WM_ERRCODE_NO_ENTRY",
        "WM_ERRCODE_OVER_MAX_ENTRY",
        "WM_ERRCODE_INVALID_POLLBITMAP",
        "WM_ERRCODE_NO_DATA",
        "WM_ERRCODE_SEND_FAILED",
        "WM_ERRCODE_DCF_TEST" ,
        "WM_ERRCODE_WL_INVALID_PARAM" ,
        "WM_ERRCODE_WL_LENGTH_ERR" ,
        "WM_ERRCODE_FLASH_ERROR" ,
        
        "mywh_ERRCODE_DISCONNECTED",
        "mywh_ERRCODE_PARENT_NOT_FOUND",
        "mywh_ERRCODE_NO_RADIO",
    };

    if ( 0 <= result && result < sizeof(errnames) / sizeof(char*) )
    {
        return errnames[result];
    }
    else
    {
        return "N/A";
    }
}

static const char *mywh_GetWMStateCodeName(u16 code)
{
    static const char *statenames[] = {
        "WM_STATECODE_PARENT_START",
        "N/A",
        "WM_STATECODE_BEACON_SENT",
        "WM_STATECODE_SCAN_START",
        "WM_STATECODE_PARENT_NOT_FOUND",
        "WM_STATECODE_PARENT_FOUND",
        "WM_STATECODE_CONNECT_START",
        "WM_STATECODE_CONNECTED",
        "WM_STATECODE_BEACON_LOST",
        "WM_STATECODE_DISCONNECTED",
        "WM_STATECODE_MP_START",
        "WM_STATECODE_MPEND_IND",
        "WM_STATECODE_MP_IND",
        "WM_STATECODE_MPACK_IND",
        "WM_STATECODE_DCF_START",
        "WM_STATECODE_DCF_IND",
        "WM_STATECODE_BEACON_RECV",
        "WM_STATECODE_DISASSOCIATE",
        "WM_STATECODE_REASSOCIATE",
        "WM_STATECODE_AUTHENTICATE",
        "WM_STATECODE_PORT_SEND",
        "WM_STATECODE_PORT_RECV",
        "WM_STATECODE_FIFO_ERROR",
    };

    if ( 0 <= code && code < sizeof(statenames) / sizeof(char*) )
    {
        return statenames[code];
    }
    else
    {
        return "N/A";
    }
}

static const char *mywh_GetWMApiidName(u16 apiid)
{
    static const char *apinames[] = {
        "WM_APIID_INITIALIZE",
        "WM_APIID_RESET",
        "WM_APIID_END",

        "WM_APIID_ENABLE",
        "WM_APIID_DISABLE",
        "WM_APIID_POWER_ON",
        "WM_APIID_POWER_OFF",

        "WM_APIID_SET_P_PARAM",
        "WM_APIID_START_PARENT",
        "WM_APIID_END_PARENT",
        "WM_APIID_START_SCAN",
        "WM_APIID_END_SCAN",
        "WM_APIID_START_CONNECT",
        "WM_APIID_DISCONNECT",
        "WM_APIID_START_MP",
        "WM_APIID_SET_MP_DATA",
        "WM_APIID_END_MP",
        "WM_APIID_START_DCF",
        "WM_APIID_SET_DCF_DATA",
        "WM_APIID_END_DCF",
        "WM_APIID_SET_WEPKEY",
        "WM_APIID_START_KS",
        "WM_APIID_END_KS",
        "WM_APIID_GET_KEYSET",
        "WM_APIID_SET_GAMEINFO",
        "WM_APIID_SET_BEACON_IND",
        "WM_APIID_START_TESTMODE",
        "WM_APIID_STOP_TESTMODE",
        "WM_APIID_VALARM_MP",
        "WM_APIID_SET_LIFETIME",
        "WM_APIID_MEASURE_CHANNEL",
        "WM_APIID_INIT_W_COUNTER",
        "WM_APIID_GET_W_COUNTER",
        "WM_APIID_SET_ENTRY",
        "WM_APIID_AUTO_DEAUTH",
        "WM_APIID_SET_MP_FREQ",
        "WM_APIID_SET_BEACON_PERIOD",
        "WM_APIID_AUTO_DISCONNECT",

        "WM_APIID_KICK_MP_PARENT",
        "WM_APIID_KICK_MP_CHILD",
        "WM_APIID_KICK_MP_RESUME",
    };
    static const char *apinames_indicates[] = {
        "WM_APIID_INDICATION",
        "WM_APIID_PORT_SEND",
        "WM_APIID_PORT_RECV",
        "WM_APIID_READ_STATUS"
        };
    static const char *apiname_unknown =
        "WM_APIID_UNKNOWN";

    if ( 0 <= apiid && apiid < sizeof(apinames) / sizeof(char*) )
    {
        return apinames[apiid];
    }
    else if ( WM_APIID_INDICATION <= apiid &&
              apiid < WM_APIID_INDICATION + sizeof(apinames_indicates) / sizeof(char*) )
    {
        return apinames_indicates[apiid - WM_APIID_INDICATION];
    }
    else if ( apiid == WM_APIID_UNKNOWN )
    {
        return apiname_unknown;
    }
    else
    {
        return "N/A";
    }
}

static void mywh_ChangeSysState(int state)
{
    static const char *statenames[] = {
        "mywh_SYSSTATE_STOP",
        "mywh_SYSSTATE_IDLE",
        "mywh_SYSSTATE_SCANNING",
        "mywh_SYSSTATE_BUSY",
        "mywh_SYSSTATE_CONNECTED",
        "mywh_SYSSTATE_DATASHARING",
        "mywh_SYSSTATE_KEYSHARING",
        "mywh_SYSSTATE_MEASURECHANNEL",
        "mywh_SYSSTATE_CONNECT_FAIL",
        "mywh_SYSSTATE_ERROR",
    };
    
    WH_TRACE("%s -> ", statenames[s_work.SysState]);
    s_work.SysState = state;
    WH_TRACE("%s\n", statenames[s_work.SysState]);
}

#else

#define mywh_GetWMErrCodeName(result)    ("")
#define mywh_GetWMStateCodeName(result)  ("")
#define mywh_GetWMApiidName(result)      ("")

static void mywh_ChangeSysState(int state)
{
    s_work.SysState = state;
}

#endif

static void mywh_SetError(int code)
{
    // 既にシステムが ERROR 状態になっている場合は、上書きしない。
    if ( s_work.SysState == mywh_SYSSTATE_ERROR ||
         s_work.SysState == mywh_SYSSTATE_FATAL )
    {
        return;
    }

    s_work.ErrCode = code;
}


/*---------------------------------------------------------------------------*
  Name:         mywh_StartScan

  Description:  親機のビーコンを取得する関数

  Arguments:    callback - 親機発見時に返すコールバックを設定する。
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static BOOL mywh_StartScan( void )
{
    WH_TRACE_STATE;
    mywh_ASSERT( s_work.SysState != mywh_SYSSTATE_CONNECTED );
    
    mywh_ChangeSysState( mywh_SYSSTATE_SCANNING );
    // 検索するMACアドレスの条件を設定
    *(u16*)(&(s_work.ScanParam).bssid[4]) = 0xffff;
    *(u16*)(&(s_work.ScanParam).bssid[2]) = 0xffff;
    *(u16*)(&(s_work.ScanParam).bssid[0]) = 0xffff;
    
    if ( ! mywh_StateInStartScan() )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        return FALSE;
    }
    
    s_work.state = BSDOWNSTATE_SCANNING;
    if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_STARTSCAN );
    return TRUE;
}

/* ----------------------------------------------------------------------
  state : StartScan
  ---------------------------------------------------------------------- */
static BOOL mywh_StateInStartScan( void )
{
    // この状態の時、親機を探索します。
    WMErrCode result;
    u16 chanpat;
    
    mywh_ASSERT( s_work.SysState == mywh_SYSSTATE_SCANNING );
    
    chanpat = WM_GetAllowedChannel();
    
    // 無線が使用可能かどうかをチェックする
    if ( chanpat == 0x8000 )
    {
        // 0x8000 が返ってきた場合は、無線が初期化されていないなど
        // 無線ライブラリの状態異常を表しているのでエラーにします。
        mywh_REPORT_FAILURE( WM_ERRCODE_ILLEGAL_STATE );
        return FALSE;
    }
    if ( chanpat == 0 )
    {
        // 無線が使えない状態。
        mywh_REPORT_FAILURE( mywh_ERRCODE_NO_RADIO );
        return FALSE;
    }
    
    if( s_work.channel >= 16 )
    {
    	// 親機発見前。チャンネルを変えて検索
    	int next = s_work.channel - 16;
    	int i;
    	for( i = 0; i < 13; i++ )
    	{
    		next = (next + 1) % 13;    	
    		if( chanpat & (1 << next) ) break;
    	}
    	s_work.channel = (u16)(16 + next);
    	s_work.ScanParam.channel = (u16)(next + 1);
    }
    else 
    {
    	// 親機発見後
    	s_work.ScanParam.channel = s_work.channel;    	
    }
    s_work.ScanParam.maxChannelTime = BSDOWN_SCANTIME;
    s_work.ScanParam.scanBuf = &(s_work.BssDesc);
    
    if( s_work.state == BSDOWNSTATE_RECEVING ) 
    {
	    // 検索するMACアドレスの条件を設定
	    int i;
	    for(i = 0; i < 6; i++) s_work.ScanParam.bssid[i] = s_work.macaddress[i];
    }
    
    result = WM_StartScan( mywh_StateOutStartScan, &(s_work.ScanParam) );
    
    if (result != WM_ERRCODE_OPERATING) 
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    return TRUE;
}


static void mywh_StateOutStartScan( void *arg )
{
    WMstartScanCallback* cb  = (WMstartScanCallback*)arg;
    
    // スキャンコマンドに失敗した場合
    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_REPORT_FAILURE(cb->errcode);
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        return;
    }

    if ( s_work.SysState != mywh_SYSSTATE_SCANNING )
    {
        // 状態が変更されていればスキャン終了
        if ( ! mywh_StateInEndScan() )
        {
            mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
            if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        }
        return;
    }
    
//    OS_TPrintf( "WMstartScanCallback state = %d\n", cb->state );
    
    switch ( cb->state ) 
    {
    case WM_STATECODE_SCAN_START:
        return;
        
    case WM_STATECODE_PARENT_NOT_FOUND:
        break;
        
    case WM_STATECODE_PARENT_FOUND:
        // 親機が見つかった場合
        // GUIDELINE : ガイドライン準拠ポイント(6.3.5)
        // ggid を比較し、違っていたら失敗とします。
        // まず、WMBssDesc.gameInfoLength を確認し、
        // ggid に有効な値が入っていることから調べる必要があります。

        // BssDescの情報がARM7側から書き込まれているため
        // バッファに設定されたBssDescのキャッシュを破棄
        DC_InvalidateRange( &(s_work.BssDesc), sizeof(WMbssDesc) );
               
        if ( cb->gameInfoLength < 8 || cb->gameInfo.ggid != BDOWN_GGID )
        {
            // GGIDが違っていれば無視する
            WH_TRACE("not my parent ggid (%d != %d)\n",  cb->gameInfo.ggid, BDOWN_GGID );
            break;
        }
      
      	// 最後にうけとった電波のリンク強度を記憶
      	s_work.linklevel = cb->linkLevel;
        
        if( s_work.state == BSDOWNSTATE_SCANNING ) 
        {
			// はじめてデータを受けとったとき。
        	bsdown_c_startdownload( (BSDOWN_GAMEINFO_STRUCT *) &(cb->gameInfo.userGameInfo[0]) );
        	// 検索するマックアドレスを固定
        	{
        		int i;
        		for(i = 0; i < 6; i++ ) s_work.macaddress[i] = cb->macAddress[i];
        	}
        	// 検索するチャンネルを固定
        	s_work.channel = (u16)(s_work.channel - 16 + 1);
        	if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_START );
        }
        
        if( bsdown_c_step( (BSDOWN_GAMEINFO_STRUCT *) &(cb->gameInfo.userGameInfo[0]) ) )
        {
     		// 受信完了   	
     		OS_TPrintf("Complete!");
        	s_work.state = BSDOWNSTATE_COMPLETE;
        	bsdown_end();
        	return;
        }

        break;
    }

    // 再スキャンを開始します。
    if ( ! mywh_StateInStartScan() )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
    }
}

/* ----------------------------------------------------------------------
   state : EndScan
  ---------------------------------------------------------------------- */

/*---------------------------------------------------------------------------*
  Name:         mywh_EndScan

  Description:  親機のビーコンを取得する関数

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static BOOL mywh_EndScan( void )
{
    if ( s_work.SysState != mywh_SYSSTATE_SCANNING )
    {
        return FALSE;
    }
    
    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
    return TRUE;
}


static BOOL mywh_StateInEndScan(void)
{
    WMErrCode result;
    WH_TRACE_STATE;

    // この状態では、スキャンの終了処理を行います。
    result = WM_EndScan( mywh_StateOutEndScan );
    if ( result != WM_ERRCODE_OPERATING )
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    
    return TRUE;
}

static void mywh_StateOutEndScan( void *arg )
{
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;
    
    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_REPORT_FAILURE( cb->errcode );
        return;
    }
    
    mywh_ChangeSysState( mywh_SYSSTATE_IDLE );
    
}

/* ----------------------------------------------------------------------
  state : Reset
  ---------------------------------------------------------------------- */
static BOOL mywh_StateInReset(void)
{
    // この状態は、親機子機共通です。
    // システムを初期状態に戻します。
    WMErrCode result;
    WH_TRACE_STATE;

    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
    result = WM_Reset( mywh_StateOutReset );
    if ( result != WM_ERRCODE_OPERATING )
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    return TRUE;
}

static void mywh_StateOutReset(void *arg)
{
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;
    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        mywh_REPORT_FAILURE( cb->errcode );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        return;
    }
    // Reset は次の状態を開始せず、アイドリング（待機中）状態にします。
    mywh_ChangeSysState(mywh_SYSSTATE_IDLE);
}
/* ----------------------------------------------------------------------
   power off
  ---------------------------------------------------------------------- */
static BOOL mywh_StateInPowerOff(void)
{
    // 無線ハードウェアへの電力供給を終了します。
    // この状態は、親機子機共通です。
    WMErrCode result;
    WH_TRACE_STATE;

    result = WM_PowerOff( mywh_StateOutPowerOff );
    if (result != WM_ERRCODE_OPERATING)
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    return TRUE;
}

static void mywh_StateOutPowerOff(void *arg)
{
    // 電源切断後状態です。
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;

    if (cb->errcode != WM_ERRCODE_SUCCESS)
    {
        mywh_REPORT_FAILURE(cb->errcode);
        return;
    }

    if ( ! mywh_StateInDisable() )
    {
        mywh_ChangeSysState(mywh_SYSSTATE_FATAL);
    }
}

/* ----------------------------------------------------------------------
   disable
  ---------------------------------------------------------------------- */
static BOOL mywh_StateInDisable(void)
{
    // 無線ハードウェアの使用終了を通知します。
    // この状態は、親機子機共通です。
    WMErrCode result;
    WH_TRACE_STATE;

    result = WM_Disable( mywh_StateOutDisable );
    if (result != WM_ERRCODE_OPERATING)
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    return TRUE;
}

static void mywh_StateOutDisable(void *arg)
{
    // 全て終了しました。
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;

    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_REPORT_FAILURE(cb->errcode);
    }
}


/* ----------------------------------------------------------------------
  state : End
  ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
  state : WM_End
  ---------------------------------------------------------------------- */
static void mywh_StateOutEnd( void *arg )
{
    WMCallback *cb = (WMCallback*)arg;
    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_FATAL );
        return;
    }
    mywh_ChangeSysState( mywh_SYSSTATE_STOP );
   	if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_FINISH );
}


/* ======================================================================
   Public Interfaces
   ====================================================================== */


/**************************************************************************
 * 以下は、WH の各種設定値を変更する関数です。
 **************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         mywh_SetDebugOutput

  Description:  デバッグ文字列出力用の関数を設定します。

  Arguments:    func    設定するデバッグ文字列出力用の関数.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void mywh_SetDebugOutput( void (*func)(const char *, ...) )
{
    OSIntrMode enabled = OS_DisableInterrupts();
    wh_trace = func;
    (void)OS_RestoreInterrupts( enabled );
}


/* ----------------------------------------------------------------------
   Name:        mywh_GetSystemState
   Description: WH の内部状態を取得します。
   Arguments:   none.
   Returns:     内部状態（mywh_SYSSTATE_XXXX）。
   ---------------------------------------------------------------------- */
static int mywh_GetSystemState(void)
{
    return s_work.SysState;
}

/**************************************************************************
 * 以下は、無線を初期化して通信可能状態まで遷移する関数です。
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        mywh_Initialize
   Description: 初期化作業を行い、初期化シーケンスを開始します。
   Arguments:   None.
   Returns:     シーケンス開始に成功すれば真。
   ---------------------------------------------------------------------- */
static BOOL mywh_Initialize( void )
{
    s_work.ErrCode = WM_ERRCODE_SUCCESS;
    
    // 初期化シーケンス開始。
    if ( ! mywh_StateInInitialize() )
    {
        return FALSE;
    }
    
    return TRUE;
}

/* ----------------------------------------------------------------------
   Indicate handler
   ---------------------------------------------------------------------- */
static void mywh_IndicateHandler( void* arg )
{
    WMindCallback*  cb = (WMindCallback*)arg;

    if( cb->errcode == WM_ERRCODE_FIFO_ERROR )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
    }
}

/* ----------------------------------------------------------------------
   state : Initialize
   ---------------------------------------------------------------------- */
static BOOL mywh_StateInInitialize(void)
{
    // 初期化シーケンスを開始します。
    WMErrCode result;
    WH_TRACE_STATE;
    
    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
    result = WM_Initialize( &(s_work.WmBuffer[0]), mywh_StateOutInitialize, mywh_DMA_NO );
    if ( result != WM_ERRCODE_OPERATING )
    {
        mywh_REPORT_FAILURE( result );
        mywh_ChangeSysState( mywh_SYSSTATE_FATAL );
        return FALSE;
    }
    
     return TRUE;
}

static void mywh_StateOutInitialize(void *arg)
{
    // 電源投入後状態です。
    WMErrCode result;
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;
    
    if (cb->errcode != WM_ERRCODE_SUCCESS)
    {
        mywh_REPORT_FAILURE(cb->errcode);
        mywh_ChangeSysState( mywh_SYSSTATE_FATAL );
        return;
    }
    // 不定期に発生する通知を受け取るコールバック関数を設定します。
    result = WM_SetIndCallback( mywh_IndicateHandler );
    if( result != WM_ERRCODE_SUCCESS )
    {
        mywh_REPORT_FAILURE( result );
        mywh_ChangeSysState( mywh_SYSSTATE_FATAL );
        return;
    }
    
    // システム状態をアイドリング（待機中）に変更。
    mywh_ChangeSysState( mywh_SYSSTATE_IDLE );
    
    // スキャンを開始します。
    (void) mywh_StartScan();
}


/**************************************************************************
 * 以下は、通信を終了して初期化状態まで遷移させる関数です。
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        mywh_Reset
   Description: リセットシーケンスを開始します。
                この関数を呼ぶと、今の状態に構わずリセットします。
        エラーからの強制復帰用です。
   Arguments:   none.
   Returns:     処理開始に成功すれば真。
   ---------------------------------------------------------------------- */
static void mywh_Reset(void)
{
    if ( ! mywh_StateInReset() )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_FATAL );
    }
}

/* ----------------------------------------------------------------------
   Name:        mywh_Finalize
   Description: 後処理・終了シーケンスを開始します。
                この関数を呼ぶと、今の状態を見て適切な終了シーケンスを
                実行します。
                通常の終了処理には（mywh_Resetではなく）この関数を使用します。
   Arguments:   None.
   Returns:     None.
   ---------------------------------------------------------------------- */
static void mywh_Finalize(void)
{
    if ( s_work.SysState == mywh_SYSSTATE_IDLE )
    {
        WH_TRACE("already mywh_SYSSTATE_IDLE\n");
        return;
    }

    WH_TRACE("mywh_Finalize, state = %d\n", s_work.SysState);

    
    if ( (s_work.SysState != mywh_SYSSTATE_KEYSHARING)
         && (s_work.SysState != mywh_SYSSTATE_DATASHARING)
         && (s_work.SysState != mywh_SYSSTATE_CONNECTED) )
    {
        // 接続していない・エラー状態などの場合はリセットしておく。
        mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
        mywh_Reset();
        return;
    }
    
    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
   
}

/*---------------------------------------------------------------------------*
  Name:         mywh_End

  Description:  無線通信を終了する。

  Arguments:    None.

  Returns:      成功すれば真。
 *---------------------------------------------------------------------------*/
static BOOL mywh_End( void )
{
    mywh_ASSERT( s_work.SysState == mywh_SYSSTATE_IDLE );
    
    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
    if ( WM_End( mywh_StateOutEnd ) != WM_ERRCODE_OPERATING )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        return FALSE;
    }
    return TRUE;
}

static BOOL mywh_StateInMyReset(void);
static void mywh_StateOutMyReset(void *arg);
BOOL bsdown_end( void )
{
    if ( s_work.SysState == mywh_SYSSTATE_IDLE ) 
    {
    	return mywh_End( );
    }
    return mywh_StateInMyReset();
}

static BOOL mywh_StateInMyReset(void)
{
    // この状態は、親機子機共通です。
    // システムを初期状態に戻します。
    WMErrCode result;
    WH_TRACE_STATE;

    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
    result = WM_Reset( mywh_StateOutMyReset );
    if ( result != WM_ERRCODE_OPERATING )
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    return TRUE;
}

static void mywh_StateOutMyReset(void *arg)
{
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;
    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        mywh_REPORT_FAILURE( cb->errcode );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        return;
    }
    // アイドリング（待機中）状態にします。
    mywh_ChangeSysState(mywh_SYSSTATE_IDLE);
    
    // 終了処理を開始します。
    mywh_End();
}

/*---------------------------------------------------------------------------*
  Name:         bsdown_c_init

  Description:  
	  子機用初期化。
	  内部でWM_INITを呼び出し、スキャン開始まで一気に進めます。
	  

  Arguments:    None.

  Returns:      成功すれば真。
 *---------------------------------------------------------------------------*/
BOOL bsdown_c_init( void *target, BSDOWN_CALLBACK callback, void *buffer )
{
	s_work_ptr = (BSDOWN_WORK*) (((u32)buffer + 31) / 32 * 32);
	s_work.SysState = mywh_SYSSTATE_STOP;
	s_work.state = BSDOWNSTATE_STARTSCAN;
	s_work.target = (u8*)target;
	s_work.packets = 0;
	s_work.received = 0;
	s_work.callback = callback;	
	s_work.channel = 16 + 0;
	s_work.infoflag = 0;
	s_work.linklevel = -1;
	return mywh_Initialize();
}

// はじめてデータを受けとったとき。
static void bsdown_c_startdownload( BSDOWN_GAMEINFO_STRUCT *info )
{
	int i;
	s_work.infoflag = 0;
	s_work.state = BSDOWNSTATE_RECEVING;
	s_work.crc = info->crc;
	s_work.size = info->size;
	s_work.packets = (u16)((s_work.size - 1) / BSDOWN_ONEPACKET_SIZE + 1);
	s_work.received = 0;
	s_work.count = 0;
	for(i = 0; i < s_work.packets; i++) s_work.flags[i] = 0;
}

// 受信ステップ。
static int bsdown_c_step( BSDOWN_GAMEINFO_STRUCT *info )
{
	if( s_work.crc != info->crc || s_work.size != info->size ) 
	{
		OS_TPrintf("!!!!!\n");
		// 違うタイプのスクリプトが並行して配信中？
		if( s_work.count++ >= BSDOWN_TIMEOUT )
		{
			// スクリプトの受信をやり直し。
			bsdown_c_startdownload( info );
			if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_RESTART );
		}
		else 
		{
			return 0;
		}
	}
	
	OS_TPrintf("%d.", info->index);
	if( info->index == 0xffff )
	{
	  MI_CpuCopy32( &(info->data[0]), &(s_work.fileinfo[0]), BSDOWN_ONEPACKET_SIZE );
	  s_work.infoflag = 1;
		
	}
	 else
	{ 	
		s_work.index = info->index;
		if( info->index >= s_work.packets )
		{
		   // indexがおかしい。エラー
		   if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
		   mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
		}
		// このパケットは既に受け取り済みかどうか
		if( s_work.flags[info->index] == 0) 
		{
			// まだ受け取っていない
			s_work.flags[info->index] = 1;
			if( info->index == s_work.packets - 1 ) 
			{
				MI_CpuCopy32( &(info->data[0]), &(s_work.target[info->index * BSDOWN_ONEPACKET_SIZE]), s_work.size - info->index * BSDOWN_ONEPACKET_SIZE );
			}
			else 
			{
				MI_CpuCopy32( &(info->data[0]), &(s_work.target[info->index * BSDOWN_ONEPACKET_SIZE]), BSDOWN_ONEPACKET_SIZE );			
			}

			s_work.received++;
			OS_TPrintf("receive %d, (%d / %d)\n", info->index, s_work.received, s_work.packets); 
			if( s_work.received == s_work.packets ) 
			{
				if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_SUCCESS );
				return 1;
			}
			
		}
	}
	
	return 0;
}

// 受信データのＣＲＣを計算
static u16 culcCRC(u8 *data, u32 size)
{
	u16 ans, i;
	u16 *target = (u16 *) data;
	ans = 0;
	for(i = 0; i < size / 2; i++ )
	{
		ans += target[i];
		ans = (u16)((ans << 1) | (ans >> 15));	
	}
	return ans;
}

// 現在までに受信したパケット量を取得
int bsdown_c_received(void)
{
	return s_work.received;	
}

// 受信すべきパケットの量
int bsdown_c_total(void)
{
	return s_work.packets;
}

// 受信しているデータのサイズ。まだ受信が開始されていなければ０を返す。
int bsdown_c_size(void)
{
	return (int)s_work.size;	
}

// 最後に受信したパケットのインデックス
int bsdown_c_lastreceive(void)
{
	return s_work.index;	
}

// 現在まで受け取ったパケットの表
u8 *bsdown_c_downloadpacket(void)
{
	return &(s_work.flags[0]);	
}

#define SECRET_KEY 0x3fa2

// 受信済みのＣＲＣが正しいかチェック。
int bsdown_c_checkcrc(void)
{
	{
		// 暗号化に使うkey。送信元のMacAddr（６バイト） + CRC（２バイト）
		u16 key[4];
		u16 *ptr;
		ptr = (u16*)&(s_work.macaddress[0]);
		key[0] = ptr[0];
		key[3] = ptr[1];
		key[2] = ptr[2];
		key[1] = s_work.crc;
		
		{
			int i;
			u16 mask = SECRET_KEY;
			for(i = 0; i < 4; i++)
			{
				key[i] = key[i] ^ mask;
				mask = key[i];
			}	
		}
		
		// デバッグ用
		{
			u8 *test = (u8*)&(key[0]);
			int i;
			OS_TPrintf("key = ");
			for( i = 0; i < 8; i++ ){
				OS_TPrintf("%d, ", key[i]);
			}	
			OS_TPrintf("\n");
		}
		OS_TPrintf("CRYPTO_RC4Init開始\n");
		
		CRYPTO_RC4Init( &(s_work.rc4context), &(key[0]), 8 );

		OS_TPrintf("CRYPTO_RC4Init終了\n");
		
		CRYPTO_RC4Encrypt(
			&(s_work.rc4context),
			s_work.target,
			s_work.size,
			s_work.target
		);

		OS_TPrintf("CRYPTO_RC4Encrypt終了\n");
		
		// 念のため、コンテキストは削除しておく
		MI_CpuClear32( &(s_work.rc4context), sizeof(s_work.rc4context) );
	}	
	
	return ( culcCRC( s_work.target, s_work.size ) == s_work.crc );
}

// 最後にうけとったビーコンの強度を取得
int bsdown_c_linklevel(void)
{
	return s_work.linklevel;	
}

int bsdown_c_worksize(void){
	return sizeof(BSDOWN_WORK) + 32;
}

void *bsdown_c_fileheader(void)
{
  if( s_work.infoflag ) return &(s_work.fileinfo[0]);
  return NULL;
}
//
