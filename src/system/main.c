//=============================================================================
/**
 * @file	main.c
 * @brief	ポケモンＤＰメイン
 * @author	GAME FREAK Inc.
 */
//=============================================================================

#include "common.h"
#include "snd_system.h"
#include "communication/communication.h"
#include "communication/comm_state.h"

#include "system/main.h"

#include "gflib\apptimer.h"
#include "system\fontproc.h"
#include "system/brightness.h"
#include "system/pm_rtc.h"
#include "gflib/gf_gx.h"

#include "system/savedata.h"
#include "system/pm_overlay.h"

#include "demo/title.h"

#include "system/wipe.h"
#include "wifi/dwc_rap.h"
#include "system/playtime_ctrl.h"

#include "system/debug_flag.h"
#include "system/pm_debug_wifi.h"

#include "application/backup.h"
#include "system/gamestart.h"

#include "savedata/config.h"

static void Main_CallProc(void);
static void ResetUpdateVBlank(void);
static void ResetLoop(int resetNo);
static void ResetFunc(int resetNo);
static void ResetErrorFunc(int resetNo, int messageType);
static void ErrorCheckComm(void);
void sleepFunc(void);

//=============================================================================
//=============================================================================
//#define TEST_60_FRAME

//--- デバッグ用  描画遅延を発生させる


// -------------------------------------------------------------------------
#ifdef	PM_DEBUG



#ifdef DEBUG_ONLY_FOR_ohno

#define _DELAY_DEBUG
static void delayDebug(void);

#endif // DEBUG_ONLY_FOR_ohno



// WIFI　対戦AUTOﾓｰﾄﾞデバック
#ifdef _WIFI_DEBUG_TUUSHIN
static void wifiDebug(void);
WIFI_DEBUG_BATTLE_WK WIFI_DEBUG_BATTLE_Work;
#endif	// _WIFI_DEBUG_TUUSHIN


// Aボタンを0.6秒に１回押す
//#define PAD_DEBUG
#ifdef PAD_DEBUG
static void DebugPad();

#endif // PAD_DEBUG

#endif // PM_DEBUG


// -------------------------------------------------------------------------

//---------------------------------------------------------------------------
/**
 * @brief	メイン制御用ワーク
 */
//---------------------------------------------------------------------------
typedef struct {
	FSOverlayID ov_id;				///<現在のメインプロセスのオーバーレイID
	PROC * proc;					///<現在のメインプロセスのポインタ
	FSOverlayID next_ov_id;			///<次のメインプロセスのオーバーレイID
	const PROC_DATA * next_data;	///<次のメインプロセスデータへのポインタ
	MAINWORK work;					///<メインプロセス用ワーク（main.hで定義）
}SYSWORK;

static SYSWORK main;

#ifdef	PM_DEBUG
DEBUG_FLAG_DATA	DebugFlagData;		///<デバッグデータ
#endif


//=============================================================================
//
//				メイン
//
//=============================================================================
extern const PROC_DATA TitleProcData;
extern const PROC_DATA OpDemoProcData;
FS_EXTERN_OVERLAY( title );

//---------------------------------------------------------------------------
/**
 * @brief	メイン関数
 */
//---------------------------------------------------------------------------
void NitroMain(void)
{
	//===========================
	//		初期化
	//===========================
	GF_AssertInit();

    sys_InitSystem();
    sys_InitVRAM();
    sys_InitKeyRead();
	sys_InitAgbCasetteVer(0);
	
	GF_GX_Init();
	GF_RTC_Init();

	Main_Init();

	// フォントデータのロード
	FontProcInit();
	FontProc_LoadFont( FONT_SYSTEM, HEAPID_BASE_APP );
	FontProc_LoadFont( FONT_TALK, HEAPID_BASE_APP );
	FontProc_LoadFont( FONT_UNKNOWN, HEAPID_BASE_APP );

	main.work.select_id = -1;
	main.work.savedata = SaveData_System_Init();

	Snd_AllInit(SaveData_GetPerapVoice(main.work.savedata),SaveData_GetConfig(main.work.savedata) );

	APTM_Init();

    if( DWC_INIT_RESULT_DESTROY_OTHER_SETTING == mydwc_init(HEAPID_BASE_APP) ){ //dwc初期化
        DWClibWarningCall(HEAPID_BASE_APP,0); //dwc初期化のエラー表示
    }

//バックアップフラッシュがないときの処理は製品版でのみ有効にする
#ifndef	PM_DEBUG
	if (SaveData_GetFlashExistsFlag(main.work.savedata) == FALSE) {
		//バックアップフラッシュの存在が認められないときは
		//エラー画面に遷移する
		//Main_SetNextProc(NO_OVERLAY_ID, &BackupErrorProcData);
		BackupErrorWarningCall( 0 );
	} else
#endif
	{
		switch (OS_GetResetParameter()) {
		case _SOFT_RESET_NORMAL:
			main.work.comm_error_flag = FALSE;
			Main_SetNextProc( FS_OVERLAY_ID(title), &OpDemoProcData);
			break;
		case _SOFT_RESET_NETERROR:
			main.work.comm_error_flag = TRUE;
			Main_SetNextProc( OVERLAY_ID_GAMESTART, &ContinueGameStartProcData);
			break;
		default:
			GF_ASSERT_MSG(0, "未定義なリセット定義が返りました！\n");
		};
	}

	sys.DS_Boot_Flag = TRUE;		//ブートフラグ

	sys.vsync_flame_counter = 0;
	Main_InitRandom();

	//輝度変更構造体初期化
	BrightnessChgInit();

	// プレイ時間カウント初期化
	PlayTimeCtrl_Init();

	//===========================
	//	メインループ
	//===========================
	while (1) {
        ErrorCheckComm(); // 通信エラー検査

        sleepFunc();   // スリープ機能部分

		sys_MainKeyRead();	//キー情報読み取り

		GF_AssertMain();

// WIFI　対戦AUTOﾓｰﾄﾞデバック
#ifdef _WIFI_DEBUG_TUUSHIN
		wifiDebug();
#endif	// _WIFI_DEBUG_TUUSHIN

#ifdef PAD_DEBUG
		DebugPad();
#endif

        
		if ((sys.cont_org & (PAD_BUTTON_START|PAD_BUTTON_SELECT|PAD_BUTTON_L|PAD_BUTTON_R))
			==(PAD_BUTTON_START|PAD_BUTTON_SELECT|PAD_BUTTON_L|PAD_BUTTON_R)) {
            if(sys.DontSoftReset == 0){  // 抑制するBITが何も無ければOK
                ResetFunc(_SOFT_RESET_NORMAL);
            }
		}
        
        if(CommUpdateData()){  // データ共有通信の通信処理

			Main_CallProc();	//メインプロセス呼び出し

			TCBSYS_Main( sys.mainTCBSys );
			TCBSYS_Main( sys.printTCBSys );
#ifndef TEST_60_FRAME
			if(!sys.vsync_flame_counter){
                OS_WaitIrq(TRUE, OS_IE_V_BLANK);	// Ｖブランク待ち
                sys.vsync_counter++;	// Ｖブランク用カウンタ
            }
#endif
        }
		GF_RTC_Main();
		PlayTimeCtrl_Countup();

#ifdef _DELAY_DEBUG
        delayDebug();
#endif// _DELAY_DEBUG

		GF_G3_SwapBuffers();	// G3_SwapBuffers呼び出し
#ifndef TEST_60_FRAME
		TCBSYS_Main( sys.printTCBSys );
#endif
        OS_WaitIrq(TRUE, OS_IE_V_BLANK); 	// Ｖブランク待ち
		sys.vsync_counter++;	// Ｖブランク用カウンタ
		sys.vsync_flame_counter = 0;


		//===========================
		BrightnessChgMain();	//輝度変更メイン
		WIPE_SYS_Main();		///<ワイプ処理メイン
		if (sys.pVBlank != NULL) {
			sys.pVBlank(sys.pVBlankWork);
		}
		Snd_Main();

		TCBSYS_Main( sys.vwaitTCBSys );
    }
}


//=============================================================================
//
//
//		メインプロセス制御
//
//
//=============================================================================

//---------------------------------------------------------------------------
/**
 * @brief	メインプロセス初期化
 */
//---------------------------------------------------------------------------
void Main_Init(void)
{
	main.ov_id = NO_OVERLAY_ID;
	main.proc = NULL;
	main.next_ov_id = NO_OVERLAY_ID;
	main.next_data = NULL;
}

//---------------------------------------------------------------------------
/**
 * @brief	メインプロセス実行
 */
//---------------------------------------------------------------------------
static void Main_CallProc(void)
{
	BOOL result;

	if (main.proc == NULL) {
		if (main.next_data == NULL) {
			return;
		}
		if (main.next_ov_id != NO_OVERLAY_ID) {
			//必要であればオーバーレイのロードを行う
			Overlay_Load(main.next_ov_id, OVERLAY_LOAD_SYNCHRONIZE);
		}
		main.ov_id = main.next_ov_id;
		main.proc = PROC_Create(main.next_data, &main.work, HEAPID_BASE_SYSTEM);
		main.next_ov_id = NO_OVERLAY_ID;
		main.next_data = NULL;
	}

	result = ProcMain(main.proc);
	if (result) {
		PROC_Delete(main.proc);
		main.proc = NULL;
		if (main.ov_id != NO_OVERLAY_ID) {
			//必要であればオーバーレイのアンロードを行う
			Overlay_UnloadID(main.ov_id);
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	次のプロセスの登録
 * @param	ov_id		オーバーレイID
 * @param	proc_data	PROC_DATAへのポインタ
 */
//---------------------------------------------------------------------------
void Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data)
{
	GF_ASSERT(main.next_data == NULL);
	main.next_ov_id = ov_id;
	main.next_data = proc_data;
}

//---------------------------------------------------------------------------
/**
 * @brief	リセットの待機状態の時に最低限必要なループ処理
 * @param	none
 */
//---------------------------------------------------------------------------

static void ResetUpdateVBlank(void)
{
    if(CommUpdateData()){  // データ共有通信の通信処理
    }
    OS_WaitIrq(TRUE, OS_IE_V_BLANK);
    sys.vsync_counter++;	// Ｖブランク用カウンタ
    sys.vsync_flame_counter = 0;
    if (sys.pVBlank != NULL) {
        sys.pVBlank(sys.pVBlankWork);
    }
}

//---------------------------------------------------------------------------
/**
 * @brief	リセットの待機状態の時に最低限必要なループ処理 リセットが実際にかかる
 * @param	resetNo   OS_ResetSystemに渡すリセット種類
 */
//---------------------------------------------------------------------------

static void ResetLoop(int resetNo)
{
    if(CommStateIsResetEnd()){ // 通信終了
        if(CARD_TryWaitBackupAsync()==TRUE){  //メモリーカード終了
            OS_ResetSystem(resetNo);  // 切断確認後終了
        }
    }
    ResetUpdateVBlank();
}

//---------------------------------------------------------------------------
/**
 * @brief	通信エラー検査
 * @param	resetNo   OS_ResetSystemに渡すリセット種類
 */
//---------------------------------------------------------------------------

static void ErrorCheckComm(void)
{
    int type = CommIsResetError();
    switch(type){
      case COMM_ERROR_RESET_SAVEPOINT:  // リセットを伴う通信エラー発生
        ResetErrorFunc(_SOFT_RESET_NETERROR,type);
        break;
      case COMM_ERROR_RESET_TITLE:  // タイトル戻りエラー
        ResetErrorFunc(_SOFT_RESET_NORMAL,type);
        break;
      case COMM_ERROR_RESET_GTS:  // GTS特有のエラー
        ResetErrorFunc(_SOFT_RESET_NETERROR,type);
        break;
    }
}

//---------------------------------------------------------------------------
/**
 * @brief	ソフトウエアリセットが起きた場合の処理
 * @param	resetNo   OS_ResetSystemに渡すリセット種類
 */
//---------------------------------------------------------------------------
static void ResetFunc(int resetNo)
{
	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_WHITE );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_WHITE );
    if(CommStateExitReset()){  // 通信リセットへ移行
        SaveData_DivSave_Cancel(SaveData_GetPointer()); //もしセーブしてたらキャンセルしておかないとリセットできない
    }
	while (1) {
        sleepFunc();   // スリープ機能部分
        ResetLoop(resetNo);
    }
}

//---------------------------------------------------------------------------
/**
 * @brief	通信エラーによるソフトウエアリセットが起きた場合の処理
 * @param	resetNo   OS_ResetSystemに渡すリセット種類
 */
//---------------------------------------------------------------------------

static void ResetErrorFunc(int resetNo, int messageType)
{
    if(messageType==COMM_ERROR_RESET_GTS){
        ComErrorWarningResetCall(HEAPID_BASE_SYSTEM,COMM_ERRORTYPE_GTS,0);
    }
    else if(_SOFT_RESET_NORMAL == resetNo){
        ComErrorWarningResetCall(HEAPID_BASE_SYSTEM,COMM_ERRORTYPE_TITLE,0);
    }
    else{
        ComErrorWarningResetCall(HEAPID_BASE_SYSTEM,COMM_ERRORTYPE_ARESET,0);
    }
    CommStateExitReset();  // 通信リセットへ移行
    while(1){
        sleepFunc();   // スリープ機能部分
		sys_MainKeyRead();	//キー情報読み取り
        if(sys.trg & PAD_BUTTON_DECIDE){
            break;
        }
        ResetUpdateVBlank();
    }
    ResetFunc(resetNo);  // リセット処理へ
}

//=============================================================================
//=============================================================================
//---------------------------------------------------------------------------
/**
 * @brief	乱数初期化処理
 *
 * RTCの時間とゲーム開始からのVsyncカウンタの値で初期化を行っている。
 * それぞれが使われるコンテキストごとにシードやワークを保持している場合は、
 * それぞれで初期化処理を別途行う
 */
//---------------------------------------------------------------------------
void Main_InitRandom(void)
{
	RTCDate date;
	RTCTime time;
	u32 seed;
	GF_RTC_GetDateTime(&date, &time);
	seed = date.year + date.month * 0x100 * date.day * 0x10000
		+ time.hour * 0x10000 + (time.minute + time.second) * 0x1000000
		+ sys.vsync_counter;
	gf_mtSrand(seed);
	gf_srand(seed);
}



//---------------------------------------------------------------------------
/**
 * @brief	スリープ状態の管理
 * @param	none
 */
//---------------------------------------------------------------------------
void sleepFunc(void)
{
  PMBackLightSwitch up,down;
  PMWakeUpTrigger trigger;
    
  if(PAD_DetectFold()){ // ふたが閉まっている
    if(sys.DontSleep == 0){
      StopTP_Sleep();
      trigger = PM_TRIGGER_COVER_OPEN|PM_TRIGGER_CARD;
      // 特定のAGBカートリッジが刺さっている場合のみ復帰条件にカートリッジ設定
      if(sys.AgbCasetteVersion)
	trigger |= PM_TRIGGER_CARTRIDGE;
      //SLEEP
      PM_GoSleepMode( trigger, 0, 0 );
      // 復帰後、カードが抜かれていたら電源OFF
      if(CARD_IsPulledOut()){
	PM_ForceToPowerOff();
      } else if((OS_GetIrqMask() & OS_IE_CARTRIDGE) && CTRDG_IsPulledOut()){
	// 復帰後、カートリッジが抜かれていたら…
	if(PAD_DetectFold()){
	  // まだふたが閉まっている状態ならば再度スリープに入った後に電源OFF
	  PM_GoSleepMode( PM_TRIGGER_COVER_OPEN|PM_TRIGGER_CARD, 0, 0 );
	  PM_ForceToPowerOff();
	} else {
	  // ふたが開いていたら電源OFF
	  PM_ForceToPowerOff();
	}
      }
      ReStartTP_Sleep();
    } else{
      // もしもカートリッジが抜かれたらSLEEP→電源OFF
      if((OS_GetIrqMask() & OS_IE_CARTRIDGE) && CTRDG_IsPulledOut()){
	PM_GoSleepMode( PM_TRIGGER_COVER_OPEN|PM_TRIGGER_CARD, 0, 0 );
	PM_ForceToPowerOff();
      }
      //BK OFF
      PM_GetBackLight(&up,&down);
      if(PM_BACKLIGHT_ON == up){
	PM_SetBackLight(PM_LCD_ALL,PM_BACKLIGHT_OFF);
      }
    }
  } else{  // 開いている
    PM_GetBackLight(&up,&down);
    if(PM_BACKLIGHT_OFF == up){
      PM_SetBackLight(PM_LCD_ALL,PM_BACKLIGHT_ON);
    }
  }
}


//---------------------------------------------------------------------------
/**
 * @brief	描画遅延　デバッグ関数 
 *  この関数を使うと スローモーションで再生可能なので
 *  どんなフレームで動いているかわかります
 */
//---------------------------------------------------------------------------
#ifdef	PM_DEBUG
static void delayDebug(void)
{
    static u8 trg = 0;
    static u8 speed = 5;
    int i;

    if(sys.cont & PAD_BUTTON_SELECT){
        if(sys.trg & PAD_BUTTON_Y){
            trg = 1 - trg;
            OS_TPrintf("DEBUG:描画遅延 %d\n", trg);
        }
    }
    if(trg){
        if(sys.trg & PAD_BUTTON_X){
            speed++;
            OS_TPrintf("speed %d\n",speed);
        }
        if(sys.trg & PAD_BUTTON_Y){
            speed--;
            OS_TPrintf("speed %d\n",speed);
        }
        for(i = 0; i < speed; i++){
            OS_WaitIrq(TRUE, OS_IE_V_BLANK);
        }
    }
}


// WIFI　対戦AUTOﾓｰﾄﾞデバック
#ifdef _WIFI_DEBUG_TUUSHIN
static void wifiDebug(void)
{
	if( sys.cont & PAD_BUTTON_L ){
		if( sys.trg & PAD_BUTTON_X ){
			sys.trg ^= PAD_BUTTON_X;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MODE = _WIFI_DEBUG_MODE_X;
			OS_TPrintf( "デバッグWIFIﾓｰﾄﾞ　X\n" );
		}else if( sys.trg & PAD_BUTTON_Y ){

			sys.trg ^= PAD_BUTTON_Y;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MODE = _WIFI_DEBUG_MODE_Y;
			OS_TPrintf( "デバッグWIFIﾓｰﾄﾞ　Y\n" );
		}
	}
	if( sys.trg & PAD_BUTTON_R ){
		OS_TPrintf( "デバッグWIFIﾓｰﾄﾞ　OFF\n" );
		memset( &WIFI_DEBUG_BATTLE_Work, 0, sizeof(WIFI_DEBUG_BATTLE_WK) );
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MODE = _WIFI_DEBUG_NONE;
	}

	if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MODE == _WIFI_DEBUG_NONE ){
		return ;
	}

	/* wifiリスト画面用 */
	if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_A_REQ == TRUE ){
		sys.trg |= PAD_BUTTON_A;
		sys.cont |= PAD_BUTTON_A;
	}
	if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_B_REQ == TRUE ){
		sys.trg |= PAD_BUTTON_B;
		sys.cont |= PAD_BUTTON_B;
	}
	if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_TOUCH_REQ == TRUE ){
		sys.tp_trg |= PAD_BUTTON_B;
		sys.tp_cont |= PAD_BUTTON_B;
		sys.tp_x	= 128;
		sys.tp_y	= 180;
	}

	/* フィールド用処理 */
	switch( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ ){
	case 0:	// 待機
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		break;

	case 1:
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT ++;
		if( (WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT > 300) || (WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MODE == _WIFI_DEBUG_MODE_X) ){
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ ++;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		}
		break;

	case 2:	// 右へ
		sys.trg |= PAD_KEY_RIGHT;
		sys.cont |= PAD_KEY_RIGHT;

		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT ++;
		if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT > 8 ){
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ ++;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		}
		break;

	case 3:
		sys.trg |= PAD_KEY_UP;
		sys.cont |= PAD_KEY_UP;

		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT ++;
		if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT > 16 ){
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ ++;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		}
		break;

	case 4:	// 左へ
		sys.trg |= PAD_KEY_LEFT;
		sys.cont |= PAD_KEY_LEFT;

		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT ++;
		if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT > 16 ){
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ ++;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		}
		break;

	case 5:
		sys.trg |= PAD_KEY_UP;
		sys.cont |= PAD_KEY_UP;

		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT ++;
		if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT > 16 ){
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ = 1;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		}
		break;
	}
}
#endif	// _WIFI_DEBUG_TUUSHIN

#endif // PM_DEBUG


#ifdef PAD_DEBUG

#include "../field/d_taya.h"

static int pad_wait=5;
static int pad_on=0;

static void DebugPad()
{
	if(pad_on){
		pad_wait--;
		if(pad_wait == 0){
			sys.trg |= PAD_BUTTON_X;
//			sys.trg |= PAD_BUTTON_A;
			pad_wait = gf_rand()%4+1;
		}
	}
	if((sys.cont & PAD_BUTTON_L) && (sys.trg & PAD_BUTTON_DEBUG)){
			pad_on^=1;
	}
}

#endif
