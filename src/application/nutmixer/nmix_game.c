/**
 *	@file	nmix_game.c
 *	@brief	ナッツミキサー　ゲームメイン
 *	@author	Miyuki Iwasawa
 *	@date	06.04.07
 */

#include "common.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/palanm.h"
#include "system/savedata.h"
#include "itemtool/itemsym.h"
#include "itemtool/item.h"
#include "gflib/strbuf_family.h"

#include "savedata/record.h"

#include "nutmixer.naix"
#include "system/arc_util.h"

#include "communication/communication.h"
#include "communication/comm_state.h"

#include "comm_command_nutmixer.h"
#include "comm_command_nutmixer_func.h"

#include "application/nutmixer.h"
#include "nutmixer_sys.h"
#include "nmix_game.h"
#include "nmix_gameseq.h"
#include "nmix_res.h"
#include "nmix_game_comm.h"
#include "nmix_game_demo.h"
#include "system/wipe.h"
#include "field/tvtopic_extern.h"

#include "include/communication/wm_icon.h"

#include "nmix_game_snd_def.h"

typedef enum{
 GAMEMAIN_SEQ_MAIN,
 GAMEMAIN_SEQ_SYNCSTART,
 GAMEMAIN_SEQ_SYNCWAIT,
};


//// ウエイト
#define GAMEMAIN_GAMEEND_WAIT	( 30*1 )	// ゲーム終了時のウエイト
#define GAMERESULT_SEEN1_WAIT	( 30*1 )	// 結果発表シーン１待ち
#define GAMERESULT_SEEN2_WAIT	( 30*1 )	// 結果発表シーン２待ち
#define GAMERESULT_END_WAIT		( 30*20 )	// 結果発表終了待ち
#define GAMENEXT_END_WAIT		( 30*5 )	// 次に進む待ち
#define GAMESYS_END_WAIT		( 30*2 )	// 完全終了時の待ち

#define GAMESTART_NUTIN_WAIT	( 24 )	// カウントダウン前ウエイト

#define GAME_OKURI_KEY	( (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ) 


/// 結果発表からもう一度やるのかを聞くところ
enum{
	GAMERESULT_SEQ_START = 0,			// 結果表示開始
	GAMERESULT_SEQ_WIPE_WAIT,			// ワイプ待ち
	GAMERESULT_SEQ_SEEN1_ON,			// 結果1表示
	GAMERESULT_SEQ_SEEN2_ON,			// 結果2表示
	GAMERESULT_SEQ_SEEN2_ENDWAIT,		// 結果表示終了待ち
	GAMERESULT_SEQ_PORUTO_SAVE,			// ポルトセーブ
	GAMERESULT_SEQ_PORUTO_SAVEWAIT,		// セーブ待ち
	GAMERESULT_SEQ_NEXT_Q,				// 続けるか質問
	GAMERESULT_SEQ_NEXT_Q_WAIT,			// 質問の答え待ち
	GAMERESULT_SEQ_NEXT_YES,			// 続ける
	GAMERESULT_SEQ_TEXTON_YAMERU,		// ハイだけどポルトケースが一杯だったら木の実をもっていなかったとき
	GAMERESULT_SEQ_NEXT_NO,				// やめる処理
};


///プロトタイプ宣言
//===================================================
///オーバーレイプロセス定義
PROC_RESULT NMixGameProc_Init(PROC* proc,int *seq);
PROC_RESULT NMixGameProc_Main(PROC* proc,int *seq);
PROC_RESULT NMixGameProc_End(PROC* proc,int *seq);

///ゲームコマンドプロトタイプ
//===================================================
static int NMixGameCom_SeqEnd( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_SeqSysInit( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_SeqSysStart( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_SeqDummyWait( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_SeqBefore( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameStart( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameMain( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameEnd( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameResult( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameResLoad( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameResRelease( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );


///画面構築関数郡
static void NMixGame_Tool_Data_DrawLink( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_SpriteDrawSet( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_YazirusiDrawSet( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_CommentDrawSet( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_SoopEffectSet( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_Yazirusi_ReqDrawSet( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_KiraKira_ReqDrawSet( NMIX_GAMEWORK* wk );

/// 音
static void NMixGame_Tool_ChapuChapuSnd( NMIX_GAMEWORK* wk );


/// 通信ワーク作成
static void NMixGame_Tool_CommDataInit( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_CommDataDelete( NMIX_GAMEWORK* wk );


/// ポルト格納部分
static BOOL NMixGame_Tool_PorutoSet( NUTMIXER_WORK* mp, PORUTO_DATA* p_poruto, int num );

///ゲームシーケンス配列定義
//===================================================
typedef int (*NMixGameFunc)(NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq);

typedef struct _NMIX_GAMEMAIN_SEQ{
 NMixGameFunc	func;	///<シーケンスFunc
 int			syncID;	///<シンクロID
}NMIX_GAMEMAIN_SEQ;

static const NMIX_GAMEMAIN_SEQ NMixGameMainTbl[] = {
	{ NMixGameCom_SeqSysInit,	SYNCHROID_BAG_END },// SYSINIT
	{ NMixGameCom_SeqSysStart,	SYNCHROID_NONE },	// SYSSTART
	{ NMixGameCom_SeqDummyWait, SYNCHROID_NONE },	// SYSSTART_WAIT
	{ NMixGameCom_SeqBefore,	SYNCHROID_NONE },	// BEFORE
	{ NMixGameCom_SeqDummyWait,	SYNCHROID_NONE },	// BEFORE_WAIT
	{ NMixGameCom_GameResLoad,	SYNCHROID_GAME_START },	// RES_LOAD
	{ NMixGameCom_GameStart,	SYNCHROID_NONE },	// GAMESTART
	{ NMixGameCom_GameMain,		SYNCHROID_NONE },	// GAMEMAIN
	{ NMixGameCom_GameEnd,		SYNCHROID_NONE },	// GAMEEND
	{ NMixGameCom_SeqDummyWait,	SYNCHROID_NONE },	// RESULT_WAIT
	{ NMixGameCom_GameResult,	SYNCHROID_NONE },	// RESULT
	{ NMixGameCom_SeqDummyWait,	SYNCHROID_NONE },	// SYSEND_WAIT
	{ NMixGameCom_GameResRelease,SYNCHROID_GAME_END },// RES_RELEASE
	{ NMixGameCom_SeqEnd,		SYNCHROID_NONE },
};

/**
 *	@brief VBlank割り込み関数
 */
static void NMixGameVBlank(void* work)
{
	NUTMIXER_WORK	*mp = (NUTMIXER_WORK*)work;
	NMIX_GAMEWORK	*wk = (mp->app_wk);

	// 描画関係Vブランク関数
	NMixGame_GraVBlank( wk );

	DoVramTransferManager();
}


///プロセス
//===================================================
/**
 *	@brief	ナッツミキサー　ゲームメイン初期化
 */
PROC_RESULT NMixGameProc_Init(PROC* proc,int *seq)
{
	NUTMIXER_WORK* pp = PROC_GetParentWork(proc);
	NMIX_GAMEWORK* wk;

	HeapStatePush();

	
	//ヒープ作成
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_NMIXER_GM,0x20000);
	
	wk = PROC_AllocWork(proc,sizeof(NMIX_GAMEWORK),HEAPID_NMIXER_GM);
	memset(wk, 0, sizeof(NMIX_GAMEWORK));

	pp->app_wk = wk;


	wk->heapID = HEAPID_NMIXER_GM;


	// Vram転送マネージャ初期化
	initVramTransferManagerHeap( 16, wk->heapID );

	// 通信開始
	if( pp->comm_f == TRUE ){
		wk->commpack_flg = NUTMIX_COMM_PACK_COMM; 
	}else{
		wk->commpack_flg = NUTMIX_COMM_PACK_ONE;
	}
	CommCommandNutMixerInitialize( wk, pp->param->mySave );

	// コンフィグ情報取得
	wk->wnd_type = CONFIG_GetWindowType( pp->param->configSave );
	wk->msg_speed = CONFIG_GetMsgPrintSpeed( pp->param->configSave );

	// OAM表示
	wk->clact_draw = TRUE;

	// Vブランク関数登録
	sys_VBlankFuncChange( NMixGameVBlank, pp );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止
	
	// サウンドデータロード(料理)
	Snd_DataSetByScene( SND_SCENE_NUTMIXER, SEQ_KINOMI1, 1 );

	return PROC_RES_FINISH;
}

/**
 *	@brief	ナッツミキサー　ゲームメイン
 */
PROC_RESULT NMixGameProc_Main(PROC* proc,int *seq)
{
	int	now_seq,synchro;
	NUTMIXER_WORK* pp = PROC_GetParentWork(proc);
	NMIX_GAMEWORK* wk = (NMIX_GAMEWORK*)PROC_GetWork(proc);

	const NMIX_GAMEMAIN_SEQ *sp;
	
	now_seq = wk->main_seq;
	sp = &(NMixGameMainTbl[now_seq]); 

	switch(*seq){
	case GAMEMAIN_SEQ_MAIN:
		if(sp->func == NULL){
			break;
		}
		//メイン呼び出し
		synchro = sp->syncID;
		wk->main_seq = (sp->func)(pp,wk,&wk->sub_seq); 
		
		// リクエストシーケンスを設定
		if( wk->main_seq_chg_req ){
			wk->main_seq = wk->main_seq_req;
			wk->main_seq_chg_req = FALSE;
		}
			
		if(now_seq == wk->main_seq){
			break;
		}
		//リセット
		wk->sub_seq = 0;	//リセット

		if(!pp->comm_f){
			break;	//ローカルプレイ
		}

		//通信プレイ
		if(synchro == SYNCHROID_NONE){
			break;
		}
		//通信同期に入る
		wk->synchroID = synchro;

		*seq = GAMEMAIN_SEQ_SYNCSTART;
		break;
	case GAMEMAIN_SEQ_SYNCSTART:
		CommTimingSyncStart(wk->synchroID);
		*seq = GAMEMAIN_SEQ_SYNCWAIT;
		break;
	case GAMEMAIN_SEQ_SYNCWAIT:
		if(!CommIsTimingSync(wk->synchroID)){
			break;
		}
		//通信同期終了&次のシーケンスへ
		*seq = GAMEMAIN_SEQ_MAIN;
		wk->synchroID = 0;
		break;
	}

	// 描画処理
	NMixGame_Draw( wk );

	// 通信エラー処理
	CommErrorCheck( wk->heapID, wk->bgl );
	
	if( wk->seqend_f ){
		return PROC_RES_FINISH;
	}else{
		return PROC_RES_CONTINUE;
	}
}

/**
 *	@brief	ナッツミキサー　ゲームメイン終了
 */
PROC_RESULT NMixGameProc_End(PROC* proc,int* seq)
{
	int	heapID;
	NUTMIXER_WORK* pp = PROC_GetParentWork(proc);
	NMIX_GAMEWORK* wk = (NMIX_GAMEWORK*)PROC_GetWork(proc);

	heapID = wk->heapID;

	// 通信破棄
	CommCommandNutMixerDest( wk );

	// Vブランク関数登録
	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	// Vram転送マネージャ破棄
	DellVramTransferManager();

	//ワーク解放
	MI_CpuClear8(wk,sizeof(NMIX_GAMEWORK));
	PROC_FreeWork(proc);
	
	HeapStatePop();
	HeapStateCheck(heapID);

	pp->app_wk = NULL;
	
	sys_DeleteHeap(heapID);
	return PROC_RES_FINISH;
}



//----------------------------------------------------------------------------
/**
 *	@brief	シーケンス設定お願い
 *
 *	@param	p_work	ゲームワーク
 *	@param	seq		設定シーケンス
 */
//-----------------------------------------------------------------------------
void NMIX_SetMainSeq( NMIX_GAMEWORK* p_work, int seq )
{
	p_work->main_seq_req = seq;
	p_work->main_seq_chg_req = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了リクエスト
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMIX_SetEndReq( NMIX_GAMEWORK* p_work )
{
	p_work->seqend_f = TRUE;
}


//======================================================
//ゲームプロセス　コマンド群
//======================================================
//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム処理の初期化	
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_SeqSysInit( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	switch( *seq ){
	case 0:
		// 通信ワーク初期化
		NMixGame_Tool_CommDataInit( wk );

		// 親かチェック
		if( NMIX_CommPack_CommGetCurrentID( wk->comm_work ) == COMM_PARENT_ID ){
			NMIX_DATA_OyaInit( &wk->oya_data );	
		}
		NMixGameDemo_SubWin_Init( &wk->sub_win,
				wk->comm_count, &wk->msgDat, &wk->game_comm_pack,
				wk->wnd_type, wk->heapID );
		NMixGameDemo_NabeGra_Init( &wk->nabe_gra );
		NMixGameDemo_MainWin_Init( &wk->main_win,
				wk->comm_count, &wk->msgDat, &wk->game_comm_pack,
				wk->wnd_type, wk->heapID );


		
		NMixGameDemo_CountDown_Init( &wk->countdown );
		NMixGameDemo_CountDown_Init( &wk->end_mark );
		NMixGameDemo_CountDown_Init( &wk->pen );
		NMixGameDemo_OtherMark_Init( &wk->other_mark, &wk->game_comm_pack, wk->comm_count, wk->comm_work );
		NMixGameDemo_SoopEffect_Init( &wk->soop_effect );
		NMixGameDemo_Yazirusi_Init( &wk->yazirusi );
		NMixGameDemo_HosiKiraKira_Init( &wk->hosi_kira, wk->comm_count );

		NMIX_DATA_KoInit( &wk->ko_data );

		NMixGameCom_GameStartGraphicInit( wk );

		// COMM_ICON設定
		WirelessIconEasy();	
		// メイン画面、OAM表示
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		// 通信相手がいるとき
		if( wk->comm_count > 1 ){
			// そのままお待ちください
			NMixGameDemo_SubWin_WinWaitMsgOn( &wk->sub_win );
		}

		// 鍋グラフィックON
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_NABE_UP, TRUE );	
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_NABE_DOWN, TRUE );	
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_SOOP_0, TRUE );	
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_SOOP_1, TRUE );	

		(*seq) ++;
		break;

	case 1:
		
		//ブラックイン
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_OUTCOLOR, WIPE_DEF_DIV, WIPE_DEF_SYNC, wk->heapID );
		(*seq)++;
		break;

	case 2:
		if( WIPE_SYS_EndCheck() ){
			return wk->main_seq + 1;
		}
		break;
	}

	return wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム処理の開始	親ー＞子開始命令
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_SeqSysStart( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	// 親のとき、子に開始命令を転送
	if( NMIX_CommPack_CommGetCurrentID( wk->comm_work ) == COMM_PARENT_ID ){
		NMIX_CommPack_CommSendData( CNM_MIXER_GAME_SYS_START,
			NULL, 0, wk->comm_work );
	}
	return wk->main_seq + 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ダミーウエイト　親との同期待ち用
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_SeqDummyWait( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	return wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム前処理		木の実データの転送など
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_SeqBefore( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	switch( *seq ){
	case 0:
		// 動さワークなどのメモリ確保を行う
		NMixGameDemo_NutsIn_Init( &wk->nuts_in, wk->comm_count );
		(*seq) ++;
		break;
	case 1:
		wk->game_comm_pack.send_before_data.nut_type = mp->itemno;
		
		// 木の実データ転送
		NMIX_CommPack_CommSendData( CNM_MIXER_GAME_BEFOREDATA, 
				&wk->game_comm_pack.send_before_data, 
				CommNutMixerGetGameBeforeSize(), wk->comm_work );	
		(*seq) ++;
		return wk->main_seq + 1;
	}
	return wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム開始時処理	フェードイン　ポロック投入やらカウントダウンやら
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameStart( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	u32 main_ret;
	int net_id;
	BOOL check;
	
	switch( *seq ){
	case 0:
		// YESNOワーク初期化	BGLがひつようなのでここで確保
		NMixGameDemo_YesNoWnd_Init( &wk->yes_no, wk->heapID, wk->bgl );

		(*seq) ++;
		break;

	case 1:
		// 皆のポロックを投入
		NMixGameDemo_NutsIn_Start( &wk->nuts_in );
		(*seq)++;
		break;

	case 2:
		main_ret = NMixGameDemo_NutsIn_Main( &wk->nuts_in );
		if( main_ret == NMIX_DEMO_NUTS_RET_TRUE ){
			(*seq)++;
			NMixGameDemo_SubWin_WinNutsOff( &wk->sub_win );

			wk->wait = GAMESTART_NUTIN_WAIT;
		}else if( main_ret != NMIX_DEMO_NUTS_RET_FALSE ){

			// ～をいれた！！
			net_id = wk->game_comm_pack.playno_netid[ main_ret - NMIX_DEMO_NUTS_RET_NUTS_00 ];
			// 投下したとテキストを出す
			NMixGameDemo_SubWin_WinNutsOn( &wk->sub_win, wk->game_comm_pack.get_ko_before_data.before[ net_id ].nut_type );

		}
		break;

	case 3:	// ペン表示
		// ウエイト入れる
		if( wk->wait > 0 ){
			wk->wait--;
			break;
		}
		
		NMixGameDemo_CountDown_Start_Pen( &wk->pen );

		(*seq)++;
		break;
	
	case 4:	// カウントダウン開始

		// ペンが終わるのを待つ
		if( NMixGameDemo_CountDown_Main( &wk->pen ) == FALSE ){
			break;
		}
		
		// 上の絵を変更
		NMixGameDemo_SubWin_PlayerNameOn( &wk->sub_win );

		// カウントダウン開始
		NMixGameDemo_CountDown_Start( &wk->countdown );

		(*seq)++;
		break;

	case 5:	// カウントダウンが終わったらメインへ
		check = NMixGameDemo_CountDown_Main( &wk->countdown );

		// アニメフレームが変わったら音を鳴らす
		{
			int anm_num = CLACT_AnmFrameGet( wk->countdown.clact );
			if( wk->last_count_down != (anm_num+1) / 3 ){
				// 最後の1回は、スタート音になる
				if( anm_num < 10 ){
					// 開始
					Snd_SePlay( NMIXGAME_SE_COUNT_DOWN );
				}else{

					// 開始
					Snd_SePlay( NMIXGAME_SE_GAME_START );
				}
				wk->last_count_down = (anm_num+1) / 3;
			}
		}
		if( check ){

			NMixGameDemo_OtherMark_DrawFlag( &wk->other_mark, TRUE );

			// 火アニメ開始
			NMixGameDemo_NabeGra_FireAnmStart( &wk->nabe_gra );

			
			return wk->main_seq + 1;
		}
		break;
	}
	return  wk->main_seq;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ゲームメイン処理	実際のゲーム処理
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameMain( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	BOOL result;
	
	//-------------------------------------
	//	転送データ作成部
	//=====================================
	// 子動さ
	NMIX_DATA_KoMain( &wk->ko_data );
	// 子転送データ作成
	NMIX_DATA_KoMake( &wk->game_comm_pack.send_game_data.one,
			&wk->ko_data );
	// 親動さ
	if( NMIX_CommPack_CommGetCurrentID( wk->comm_work ) == COMM_PARENT_ID ){
		// 親動さメイン
		result = NMIX_DATA_OyaMain( &wk->oya_data, &wk->game_comm_pack, wk->comm_count );

		// 終了ちぇっく
		if( result == TRUE ){
//			OS_Printf( "終了を転送\n" );
			result = NMIX_CommPack_CommSendData( CNM_MIXER_GAME_END, NULL, 0, wk->comm_work );
			GF_ASSERT( result );
			return wk->main_seq;
		}

		NMIX_DATA_OyaCookCountAdd( &wk->oya_data );
		
		NMIX_DATA_OyaCommDataMake( &wk->oya_data, &wk->game_comm_pack, wk->comm_count );	// 通信データ設定
	}

	// 転送
	result = NMIX_CommPack_CommSendData( CNM_MIXER_GAMEDATA, &wk->game_comm_pack.send_game_data, CommNutMixerGetGameSize(), wk->comm_work );
	if( result == FALSE ){

#ifdef PM_DEBUG
		wk->comm_err_count ++;
#endif
	}

	//-------------------------------------
	//	描画データ作成部
	//=====================================
	NMixGame_Tool_Data_DrawLink( wk );

	// スープエフェクト動さ
	NMixGameDemo_SoopEffect_Main( &wk->soop_effect, &wk->game_comm_pack );

	// 矢印エフェクトメイン
	NMixGameDemo_Yazirusi_Main( &wk->yazirusi );

	// キラキラエフェクトメイン
	NMixGameDemo_HosiKiraKira_Main( &wk->hosi_kira );

	return  wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム終了処理	ゲーム終了処理	”おわり”　引ける　フェードアウト
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameEnd( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	PORUTO_DATA* p_poruto;
	BOOL result;

	// ゲーム終了前にエフェクトが出ている可能性があるので
	// ここで終わらせる
	// スープエフェクト動さ
	NMixGameDemo_SoopEffect_Main( &wk->soop_effect, &wk->game_comm_pack );


	switch( *seq ){
	case 0:
		// コメントが出ていたらとめる
		NMixGameDemo_StopComment( &wk->main_win );

		// 矢印が出ていたらとめる
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT );
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT_R );
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT );
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT_R );
		
		// 終わりと表示
		NMixGameDemo_CountDown_Start( &wk->end_mark );

		// おととめる
		Snd_SeStopBySeqNo(NMIXGAME_SE_SOBORO_ROTA,0);
        Snd_SeStopBySeqNo(NMIXGAME_SE_SOBORO_KOGE,0);
        Snd_SeStopBySeqNo(NMIXGAME_SE_GAME_KIRAKIRA,0);
        Snd_SeStopBySeqNo(NMIXGAME_SE_GAME_ROTAWAY_ON,0);

		// 終わり音
		Snd_SePlay( NMIXGAME_SE_GAME_END );

		// 火を消す
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_0, FALSE );	
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_1, FALSE );	
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_2, FALSE );	

		(*seq) ++;
		break;

	case 1:
		// カウントダウン待ち
		if( NMixGameDemo_CountDown_Main( &wk->end_mark ) == FALSE ){
			break;
		}

		// 画面フェードアウト
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, wk->heapID );
		(*seq) ++;
		break;

	case 2:
		if( WIPE_SYS_EndCheck() ){
			(*seq) ++;
		}
		break;
	
	case 3:
		// レコード　スコア処理
		{
			RECORD* p_record = SaveData_GetRecord( mp->param->SaveData );
			if( wk->commpack_flg == NUTMIX_COMM_PACK_ONE ){
				RECORD_Score_Add( p_record, SCORE_ID_MINIGAME_NUTS );
			}else{
				RECORD_Score_Add( p_record, SCORE_ID_COMM_MINIGAME_NUTS );
			}
		}

		// 親ならポルトデータ転送を行う
		if( NMIX_CommPack_CommGetCurrentID( wk->comm_work ) == COMM_PARENT_ID ){
			p_poruto = PorutoData_AllocWork( wk->heapID );
			NMIX_DATA_OyaCalcPorutoData( &wk->oya_data, p_poruto, &wk->game_comm_pack, wk->comm_count, wk->heapID );

			// 転送
			result = NMIX_CommPack_CommSendData( CNM_MIXER_PORUTO_DATA, p_poruto, PorutoData_GetWorkSize(), wk->comm_work );
			GF_ASSERT( result );

			sys_FreeMemoryEz( p_poruto );
		}
		(*seq) ++;
		break;

	case 4:
		// 親なら結果転送を行う
		if( NMIX_CommPack_CommGetCurrentID( wk->comm_work ) == COMM_PARENT_ID ){
			
			// 結果作成
			NMIX_DATA_OyaCommDataMake_Result( &wk->oya_data, &wk->game_comm_pack, wk->comm_count );

#ifdef NMIX_DEBUG_DUMMY_RESULT_ON
			if( sys.cont & PAD_BUTTON_A ){
				NMIX_DATA_OyaCommDataMake_Result_MaxDebug( &wk->oya_data, &wk->game_comm_pack, wk->comm_count );
			}
#endif	// NMIX_DEBUG_DUMMY_RESULT_ON

			// 転送
			result = NMIX_CommPack_CommSendData( CNM_MIXER_GAME_RESULTDATA, &wk->game_comm_pack.send_oya_result_data, CommNutMixerGetGameResultSize(), wk->comm_work );
			GF_ASSERT( result );
		}
		return wk->main_seq + 1;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return  wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム結果表示	フェードインー＞表示ー＞フェードアウト
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameResult( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	u32 yes_no;
	BOOL result;
	u8 send_data;

	switch( *seq ){
	case GAMERESULT_SEQ_START:
		NMixGameDemo_ResultOn( &wk->main_win, NMIX_DEMO_MINWIN_RESULT_SEEN0 );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		wk->clact_draw = FALSE;	// OAM表示OFF
//		CLACT_DrawFlagSet( wk->clact.cas, FALSE );	// OAM非表示

		// ポルト表示ON
		NMixGameDemo_PorutoDraw_Init( &wk->poruto_draw, NMIX_DEMO_RESULT_PORUTO_DRAW_X, NMIX_DEMO_RESULT_PORUTO_DRAW_Y, wk->game_comm_pack.get_result_data.poruto_type, wk->heapID );
	
		// 画面フェードイン
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, wk->heapID );
		(*seq) ++;
		break;

	case GAMERESULT_SEQ_WIPE_WAIT:
		if( WIPE_SYS_EndCheck() ){
			(*seq)++;
			wk->wait = GAMERESULT_SEEN1_WAIT;
		}
		break;

	case GAMERESULT_SEQ_SEEN1_ON:
		wk->wait --;
		if( wk->wait < 0 ){
			NMixGameDemo_ResultOn( &wk->main_win, NMIX_DEMO_MINWIN_RESULT_SEEN1 );

			// 結果表示
			Snd_SePlay( NMIXGAME_SE_GAME_RESULT_ON );
			(*seq)++;
			wk->wait = GAMERESULT_SEEN2_WAIT;
		}
		break;
		
	case GAMERESULT_SEQ_SEEN2_ON:
		wk->wait --;
		if( wk->wait < 0 ){
			NMixGameDemo_ResultOn( &wk->main_win, NMIX_DEMO_MINWIN_RESULT_SEEN2 );

			NMixGameDemo_PorutoDraw_Draw( &wk->poruto_draw );

			// 結果表示
			Snd_SePlay( NMIXGAME_SE_GAME_RESULT_ON );
			(*seq)++;
			wk->wait = GAMERESULT_END_WAIT;
		}
		break;

	case GAMERESULT_SEQ_SEEN2_ENDWAIT:
#ifdef DEBUG_NUTMIXER_AUTO
		sys.tp_trg = 1;	//タッチパネル押しっぱなし
#endif	// DEBUG_NUTMIXER_AUTO
	
		// 10秒たつか、タッチされたら終わり
		wk->wait --;
		if( (wk->wait < 0) || (sys.tp_trg) || (sys.trg & GAME_OKURI_KEY) ){
			(*seq)++;
			break;
		}
		NMixGameDemo_PorutoDraw_Draw( &wk->poruto_draw );
		break;

	case GAMERESULT_SEQ_PORUTO_SAVE:		// セーブデータにポロックを追加する
		// ポルト破棄
		NMixGameDemo_PorutoDraw_Delete( &wk->poruto_draw );

		// テキスト非表示
		NMixGameDemo_ResultOff( &wk->main_win );

#ifndef DEBUG_NUTMIXER_AUTO
		// ポルト格納
		NMixGame_Tool_PorutoSet( mp, wk->game_comm_pack.p_get_ko_poruto, wk->comm_count );
#endif
		NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_SAVE_PORUTO );
		wk->wait = GAMENEXT_END_WAIT;
		(*seq)++;
		break;

	case GAMERESULT_SEQ_PORUTO_SAVEWAIT:
#ifdef DEBUG_NUTMIXER_AUTO
		sys.tp_trg = 1;	//タッチパネル押しっぱなし
#endif	// DEBUG_NUTMIXER_AUTO
		wk->wait --;
		// タッチしたら次へ
		if( (sys.tp_trg) || (wk->wait < 0) || (sys.trg & GAME_OKURI_KEY) ){
			(*seq)++;
		}
		break;

	case GAMERESULT_SEQ_NEXT_Q:
		// ひきつづきポルトを作成しますか？
		NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_HIKITUDUKI );

		// YESNOウィンドウ
		NMixGameDemo_YesNoWnd_Start( &wk->yes_no );


#ifdef DEBUG_NUTMIXER_AUTO
		wk->wait = 2600;
#endif

		(*seq)++;
		break;

	case GAMERESULT_SEQ_NEXT_Q_WAIT:
#ifdef DEBUG_NUTMIXER_AUTO
		wk->wait --;

		if( sys.trg & PAD_BUTTON_A ){
			OS_Printf( "wait %d\n", wk->wait );
		}
		if( wk->wait < 0 ){
			sys.tp_trg = 1;	//タッチパネル押しっぱなし
			sys.tp_cont = 1;//タッチパネル押しっぱなし
			sys.tp_x = (24 * 8) + 2;
			sys.tp_y = (8 * 8) + 2;//*/
/*			// 子機通信を終わらせる
			if( wk->game_comm_pack.my_netid != COMM_PARENT_ID ){
				CommSetError();
//				sys.DontSoftReset = 0xff;
			}
//*/
		}
#endif	// DEBUG_NUTMIXER_AUTO

		yes_no = NMixGameDemo_YesNoWnd_Main( &wk->yes_no );

		if( (yes_no == TOUCH_SW_RET_YES) ||
			(yes_no == TOUCH_SW_RET_NO) ){

			if( yes_no == TOUCH_SW_RET_YES ){

				// まだポルトがはいるかチェック
				//ポルトケースがいっぱいでないかチェック
				if( PORUTO_GetDataNum( mp->param->poruSave ) >= PORUTO_STOCK_MAX ){
				
					NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_PORUTO_IPPAI );
					(*seq) = GAMERESULT_SEQ_TEXTON_YAMERU;	// やめる処理へ

					wk->wait = GAMENEXT_END_WAIT;
					break;
				}
				// バッグの中に木の実があるかチェック
				if( MyItem_CheckItemPocket( mp->param->itemSave ,BAG_POKE_NUTS) == FALSE ){
					NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_NUTS_NONE );
					(*seq) = GAMERESULT_SEQ_TEXTON_YAMERU;	// やめる処理へ
					wk->wait = GAMENEXT_END_WAIT;
					break;
				}
				
				(*seq) = GAMERESULT_SEQ_NEXT_YES;

			}else{
				(*seq) = GAMERESULT_SEQ_NEXT_NO;
			}

			if( wk->comm_count > 1 ){
				// 通信待機中
				NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_TUUSHIN_TAIKI );
			}
		}
		break;

	case GAMERESULT_SEQ_NEXT_YES:
		wk->game_next = TRUE;
		// まだ続けると親に転送
		result = NMIX_CommPack_CommSendData( CNM_MIXER_GAME_NEXT, &wk->game_next, CommNutMixerGetOneSize(), wk->comm_work );
		GF_ASSERT( result );
		return  wk->main_seq + 1;

	case GAMERESULT_SEQ_TEXTON_YAMERU:	// ポルトが一杯のとき
		wk->wait --;
		// タッチしたら次へ
		if( (sys.tp_trg) || (wk->wait < 0) || (sys.trg & GAME_OKURI_KEY) ){

			if( wk->comm_count > 1 ){
				// 通信待機中
				NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_TUUSHIN_TAIKI );
			}

			(*seq) = GAMERESULT_SEQ_NEXT_NO;
		}
		break;
		
	case GAMERESULT_SEQ_NEXT_NO:
		// もうやめると親に転送
		wk->game_next = FALSE;
		result = NMIX_CommPack_CommSendData( CNM_MIXER_GAME_NEXT, &wk->game_next, CommNutMixerGetOneSize(), wk->comm_work );
		GF_ASSERT( result );
		return  wk->main_seq + 1;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return  wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲームリソース読み込み
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameResLoad( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	return NMixGameCom_ResInit( wk, seq );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲームリソース破棄
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameResRelease( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{

	switch( *seq ){
	case 0:
		if( wk->game_comm_pack.get_game_next == TRUE ){
			
			// バッグから木の実を選んでください
			NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_BAG );
			mp->game_next = TRUE;
		}else{
			mp->game_next = FALSE;
			// 自分が続けるなのに、親から来た命令が終わるのとき
			if( wk->game_next == TRUE ){
				// 都合が悪くなったひとがいます
				NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_TUGOUWARU );
			}else{

				// 1人用のときはウエイトいれない
				// 複数人数用は、フェードアウトのタイミングを
				// 合わせるためウエイトをいれる
				if( wk->comm_count <= 1 ){
					(*seq) = 2;
					break;
				}
			}

			// 冒険ノート
			{
				void* buff;
				if( wk->commpack_flg == NUTMIX_COMM_PACK_COMM ){
					buff = FNOTE_SioPorutoDataMake( wk->heapID );	
					FNOTE_DataSave( mp->param->fnote, buff, FNOTE_TYPE_SIO );
				}
			}
		
		}
		wk->wait = GAMESYS_END_WAIT;
		(*seq)++;
		break;
	
	case 1:
		wk->wait --;
		if( (wk->wait < 0) ){
			(*seq)++;
		}
		break;

	case 2:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, wk->heapID );
		(*seq) ++;
		break;

	case 3:
		if( WIPE_SYS_EndCheck() ){
			(*seq) ++;
		}
		break;


	case 4:
		NMixGameCom_ResRelease( wk, seq );
		NMixGameCom_GameStartGraphicRelease(  wk );
		return wk->main_seq + 1;
	};

	return  wk->main_seq;
}

/**
 *	@brief	コマンド ゲームプロセス終了　
 */
static int NMixGameCom_SeqEnd(NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq)
{
	// 確保していたワークを破棄する
	NMixGameDemo_NutsIn_Delete( &wk->nuts_in );
	NMixGameDemo_SubWin_Delete( &wk->sub_win );
	NMixGameDemo_CountDown_Delete( &wk->countdown );
	NMixGameDemo_CountDown_Delete( &wk->end_mark );
	NMixGameDemo_CountDown_Delete( &wk->pen );
	NMixGameDemo_NabeGra_Delete( &wk->nabe_gra );
	NMixGameDemo_OtherMark_Delete( &wk->other_mark );
	NMixGameDemo_MainWin_Delete( &wk->main_win );
	NMixGameDemo_SoopEffect_Delete( &wk->soop_effect );
	NMixGameDemo_Yazirusi_Delete( &wk->yazirusi );
	NMixGameDemo_HosiKiraKira_Delete( &wk->hosi_kira );
	NMixGameDemo_YesNoWnd_Delete( &wk->yes_no );

	// 通信ワーク破棄
	NMixGame_Tool_CommDataDelete( wk );

	// 通信エラー数を表示
#ifdef PM_DEBUG
	OS_Printf( "通信エラー数　%d\n", wk->comm_err_count );
#endif
	
	NMIX_SetEndReq( wk );
	return wk->main_seq; 
}









//-----------------------------------------------------------------------------
/**
 * 
 *		描画構築関数関連
 * 
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	ゲームデータを描画に反映させる
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_Data_DrawLink( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	fx32 scale;
	
	// グラフィック回転
	NMixGameDemo_NabeGra_GraphicSetSoopRota( &wk->nabe_gra, p_oya->rota );

	// チャプチャプ音
	NMixGame_Tool_ChapuChapuSnd( wk );

	// グラフィック拡大率
	scale = NMIX_DATA_SoopSpeedGraScale( p_oya->rota_sp, p_oya->mix_type );
	NMixGameDemo_NabeGra_GraphicSetSoopScale( &wk->nabe_gra, scale );

	// 火アニメ
	NMixGameDemo_NabeGra_FireAnm( &wk->nabe_gra, p_oya->mix_type );


	// 皆の位置を設定
	NMixGameDemo_OtherMark_Main( &wk->other_mark );

	// スプライト描画設定
	NMixGame_Tool_SpriteDrawSet( wk );

	// 方向変更
	NMixGame_Tool_Yazirusi_ReqDrawSet( wk );

	// 逆回転エフェクト
	NMixGame_Tool_YazirusiDrawSet( wk );

	// こげる　こぼれる　テキスト描画
	NMixGame_Tool_CommentDrawSet( wk );

	// こげる　こぼれる　エフェクト設定
	NMixGame_Tool_SoopEffectSet( wk );

	// キラキラエフェクト
	NMixGame_Tool_KiraKira_ReqDrawSet( wk );
}

//----------------------------------------------------------------------------
/**
 *	@brief	スプライト描画　設定
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_SpriteDrawSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	static const u8 draw_flg[ NMIX_SOOPTYPE_SOOP_NUM ][7] = {
		{
			TRUE, TRUE, FALSE,
			TRUE, FALSE, FALSE,
			NMIX_DEMO_NABE_OBJ_SOOP_0,	// α値を設定するスープ
		},
		{
			FALSE, TRUE, TRUE,
			FALSE, TRUE, FALSE,
			NMIX_DEMO_NABE_OBJ_SOOP_1,
		},
		{
			FALSE, FALSE, TRUE,
			FALSE, FALSE, TRUE,
			NMIX_DEMO_NABE_OBJ_NUM,	// =none
		},	
	};

	// スープタイプのグラフィック設定
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_SOOP_0, draw_flg[ p_oya->mix_type ][0] );
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_SOOP_1, draw_flg[ p_oya->mix_type ][1] );
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_SOOP_2, draw_flg[ p_oya->mix_type ][2] );

	// 火加減
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_0, draw_flg[ p_oya->mix_type ][3] );
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_1, draw_flg[ p_oya->mix_type ][4] );
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_2, draw_flg[ p_oya->mix_type ][5] );

	// α値設定
	if( draw_flg[ p_oya->mix_type ][6] != NMIX_DEMO_NABE_OBJ_NUM ){
		if( p_oya->alpha_num > 0 ){
			NMixGameDemo_NabeGra_GraphicSetAlpha( &wk->nabe_gra, draw_flg[ p_oya->mix_type ][6], p_oya->alpha_num );
		}else{
			NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, draw_flg[ p_oya->mix_type ][6], FALSE );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	逆回転矢印表示制御
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_YazirusiDrawSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;

	// 回転リクエスト方向と一致しているかチェック
	// 方向支持が出ているときも消す
	if( (p_oya->now_rota_req == p_oya->rota_way) ||
		(p_oya->rota_sp == 0) || ( wk->houkou_draw_flg != 0 ) ){	// 回転速度０のときは関係なし
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT_R );
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT_R );
		// 表示OFF
		wk->gyaku_draw_flg = 0;
	}else{
		// 逆ですよ！
		if( p_oya->now_rota_req == 0 ){
			if( wk->gyaku_draw_flg != NMIX_GAME_WAY_FLAG_RIGHT ){
				// 右に回れ～
				NMixGameDemo_Yazirusi_Add( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT_R );
				wk->gyaku_draw_flg = NMIX_GAME_WAY_FLAG_RIGHT;
				// 左周りOFF
				NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT_R );

				// 逆回転
				Snd_SePlay( NMIXGAME_SE_GAME_ROTAWAY_ON );
			}
		}else{
			// 左に回れ～
			if( wk->gyaku_draw_flg != NMIX_GAME_WAY_FLAG_LEFT ){
				// 左に回れ～
				NMixGameDemo_Yazirusi_Add( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT_R );
				wk->gyaku_draw_flg = NMIX_GAME_WAY_FLAG_LEFT;
				// 右周りOFF
				NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT_R );

				// 逆回転
				Snd_SePlay( NMIXGAME_SE_GAME_ROTAWAY_ON );
			}
		}
	}	
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGコメント描画制御
 *
 *	このエフェクトは、
 *	逆回転エフェクト設定後に呼ぶ必要があります
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_CommentDrawSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	static const u8 kobore_comm[ NMIX_SOOPTYPE_SOOP_NUM ] ={
		NMIX_STMSG_SPEED_HAYAI00, NMIX_STMSG_SPEED_HAYAI01, 0
	};
	static const u8 kogeru_comm[ NMIX_SOOPTYPE_SOOP_NUM ] ={
		NMIX_STMSG_SPEED_KOGERU00, NMIX_STMSG_SPEED_KOGERU01, NMIX_STMSG_SPEED_KOGERU02
	};
 	
	// 逆回転や回転方向支持をしているときは、表示しない
	if( (wk->gyaku_draw_flg != 0) || 
		(wk->houkou_draw_flg != 0) ){
		NMixGameDemo_StopComment( &wk->main_win );
		wk->kobore_draw_flg = FALSE;
		wk->kogeru_draw_flg = FALSE;
	}else{

		// スピードチェック
		// こぼれ
		if( wk->kobore_draw_flg == FALSE ){

			if( p_oya->kobore_req ){
				NMixGameDemo_StopComment( &wk->main_win );
				NMixGameDemo_StartComment( &wk->main_win, kobore_comm[ p_oya->mix_type ] );
				wk->kobore_draw_flg = TRUE;
				wk->kogeru_draw_flg = FALSE;
			}
		}else{
			// 終わったらフラグを下げる
			if( NMixGameDemo_EndCheckComment( &wk->main_win ) ){
				wk->kobore_draw_flg = FALSE;
			}
		}
		
		// こげる
		if( wk->kogeru_draw_flg == FALSE ){

			if( p_oya->koge_req ){
				NMixGameDemo_StopComment( &wk->main_win );
				NMixGameDemo_StartComment( &wk->main_win, kogeru_comm[ p_oya->mix_type ] );
				wk->kogeru_draw_flg = TRUE;
				wk->kobore_draw_flg = FALSE;
			}
		}else{
			// 終わったらフラグを下げる
			if( NMixGameDemo_EndCheckComment( &wk->main_win ) ){
				wk->kogeru_draw_flg = FALSE;
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	スープエフェクト設定
 *
 *	@param	wk	ワーク
 *
 *	音もだします
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_SoopEffectSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	static const u32 SoopEffectKoboreSndTbl[ NMIX_SOOPTYPE_SOOP_NUM ] = {
		NMIXGAME_SE_SOOP_KOBORE,
		NMIXGAME_SE_CREAM_KOBORE,
		NMIXGAME_SE_CREAM_KOBORE
	};
	static const u32 SoopEffectKogeSndTbl[ NMIX_SOOPTYPE_SOOP_NUM ] = {
		NMIXGAME_SE_SOOP_KOGE,
		NMIXGAME_SE_CREAM_KOGE,
		NMIXGAME_SE_SOBORO_KOGE
	};

	
	if( p_oya->kobore_req ){
		NMixGameDemo_SoopEffect_Add( &wk->soop_effect, p_oya->mix_type, NMIX_DMEO_SOOP_EFF_TYPE_KOBORE );

		// こぼれ音
		Snd_SePlay( SoopEffectKoboreSndTbl[ p_oya->mix_type ] );
	}
	
	if( p_oya->koge_req == NMIX_GAME_COMM_KOGE_KOGE_REQ ){
		
			NMixGameDemo_SoopEffect_Add( &wk->soop_effect, p_oya->mix_type, NMIX_DEMO_SOOP_EFF_TYPE_KOGE );
			
			// こげ音
			Snd_SePlay( SoopEffectKogeSndTbl[ p_oya->mix_type ] );
		
	}else if( p_oya->koge_req == NMIX_GAME_COMM_KOGE_KEMURI_REQ ){
		NMixGameDemo_SoopEffect_Add( &wk->soop_effect, p_oya->mix_type, NMIX_DMEO_SOOP_EFF_TYPE_KEMURI );
	}

	// スープのスピードがちょうど良くなったらこげを消す
	if( NMIX_DATA_SoopSpeedKoge( p_oya->rota_sp, p_oya->mix_type ) == FALSE ){
		NMixGameDemo_SoopEffect_DelReq( &wk->soop_effect );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	今の回転方向　描画
 *
 *	@param	wk	ワーク
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_Yazirusi_ReqDrawSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	BOOL result;

	// 今の回転方向と親から来た回転方向が違うかチェック
	if( p_oya->rota_req_eff ){
		
		// 回転方向エフェクト設定
		if( p_oya->now_rota_req == 0 ){
			// 右へ
			NMixGameDemo_Yazirusi_Add( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT );
			NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT );
			
			// 方向指示
			Snd_SePlay( NMIXGAME_SE_GAME_ROTAWAY_ON );
			
			wk->houkou_draw_flg = NMIX_GAME_WAY_FLAG_RIGHT;
		}else{
			// 左へ
			NMixGameDemo_Yazirusi_Add( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT );
			NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT );

			// 方向指示
			Snd_SePlay( NMIXGAME_SE_GAME_ROTAWAY_ON );
			wk->houkou_draw_flg = NMIX_GAME_WAY_FLAG_LEFT;
		}
	}

	// 表示完了したらフラグをOFF
	if( wk->houkou_draw_flg == NMIX_GAME_WAY_FLAG_RIGHT ){
		
		result = NMixGameDemo_Yazirusi_EndCheck( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT );
		if( result == TRUE ){
			wk->houkou_draw_flg = 0;
		}
	}else if( wk->houkou_draw_flg == NMIX_GAME_WAY_FLAG_LEFT ){

		result = NMixGameDemo_Yazirusi_EndCheck( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT );
		if( result == TRUE ){
			wk->houkou_draw_flg = 0;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	キラキラエフェクト
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_KiraKira_ReqDrawSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	int x = wk->game_comm_pack.send_game_data.one.x;
	int y = wk->game_comm_pack.send_game_data.one.y;

	if( p_oya->kirakira_eff == 1 ){
		NMixGameDemo_HosiKiraKira_Add( &wk->hosi_kira, x, y );

		// キラキラ音
		Snd_SePlay( NMIXGAME_SE_GAME_KIRAKIRA );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	通信ワーク初期化処理
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_CommDataInit( NMIX_GAMEWORK* wk )
{
	int i;
	wk->game_comm_pack.p_get_ko_poruto = PorutoData_AllocWork( wk->heapID );
	wk->game_comm_pack.my_netid = NMIX_CommPack_CommGetCurrentID( wk->comm_work );


	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		wk->game_comm_pack.get_game_data[ i ].one.x = 128;
		wk->game_comm_pack.get_game_data[ i ].one.y = 96;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	通信ワーク破棄処理
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_CommDataDelete( NMIX_GAMEWORK* wk )
{
	GF_ASSERT( wk->game_comm_pack.p_get_ko_poruto );
	sys_FreeMemoryEz( wk->game_comm_pack.p_get_ko_poruto );
	wk->game_comm_pack.p_get_ko_poruto = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポルトデータをセーブする
 *
 *	@param	wk			ワーク
 *	@param	p_poruto	ポルトデータ
 *	@param	num			格納数
 *
 *	@retval	TRUE	成功
 *	@retval	FALSE	ケースが一杯
 */
//-----------------------------------------------------------------------------
static BOOL NMixGame_Tool_PorutoSet( NUTMIXER_WORK* mp, PORUTO_DATA* p_poruto, int num )
{
	int i;
	u16 ret;
	int poruto_type;
	BOOL return_val = TRUE;
	TV_WORK* p_tvw = SaveData_GetTvWork( mp->param->SaveData );
		
	for( i=0; i<num; i++ ){
		ret = PORUTO_AddData( mp->param->poruSave, p_poruto );
		if( ret == PORUTO_DATA_NULL ){
//			OS_Printf( "ポルト一杯 %d\n", i );
			return_val = FALSE;
			break;
		}
	}

	//　テレビワークに保存
	poruto_type = PorutoData_GetParam( p_poruto, PORUTO_PARAID_FLAVOR );
	TVTOPIC_PorutoTemp_Set( p_tvw, poruto_type );
	
	return return_val;
}

//----------------------------------------------------------------------------
/**
 *	@brief	チャプチャプ音　を出す
 *
 *	@param	wk	ワーク
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_ChapuChapuSnd( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	static const u32 SndTbl[ NMIX_SOOPTYPE_SOOP_NUM ] = {
		NMIXGAME_SE_SOOP_ROTA,
		NMIXGAME_SE_CREAM_ROTA,
		NMIXGAME_SE_SOBORO_ROTA,
	};

	if( ((p_oya->rota_way == 0) && (wk->last_rota > p_oya->rota)) ||
		((p_oya->rota_way == 1) && (wk->last_rota < p_oya->rota)) ){
		Snd_SePlay( SndTbl[ p_oya->mix_type ] );
	}
	
	wk->last_rota = p_oya->rota;
}

