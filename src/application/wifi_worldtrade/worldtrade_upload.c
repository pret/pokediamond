//============================================================================================
/**
 * @file	worldtrade_upload.c
 * @bfief	世界交換ポケモンデータアップロードデモ
 * @author	Akito Mori
 * @date	06.05.04
 */
//============================================================================================

//#define TEST_DEMO_OFF	// 今はデモに行くと止まるのでタイトルに戻るようにしておく

#ifdef PM_DEBUG
// コメントをはずすと必ずアップロードで失敗する
//#define DEBUG_UPLOAD_ERROR
#endif

// サーバー確認からダウンロードに流れる時にﾌｪｰﾄﾞｱｳﾄしないようにする版
#define REPAIR_060804

#include "common.h"
#include <dwc.h>
#include "libdpw/dpw_tr.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/touchpanel.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "savedata/savedata.h"
#include "savedata/wifilist.h"
#include "savedata/worldtrade_data.h"
#include "savedata/zukanwork.h"
#include "savedata/perapvoice.h"
#include "poketool/pokeparty.h"
#include "poketool/boxdata.h"
#include "itemtool/itemsym.h"
#include "communication/comm_state.h"
#include "communication/comm_wifihistory.h"
#include "savedata/get_poke.h"

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "msgdata/msg_wifi_lobby.h"
#include "msgdata/msg_wifi_gtc.h"
#include "msgdata/msg_wifi_system.h"

#include "libdpw/dpw_tr.h"


#include "worldtrade.naix"			// グラフィックアーカイブ定義

#define FIRST_NATUKIDO  (70)		///交換されたポケモンに入れるなつき度



//============================================================================================
//	プロトタイプ宣言
//============================================================================================
/*** 関数プロトタイプ ***/
static void BgInit( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( WORLDTRADE_WORK * wk );
static void BmpWinInit( WORLDTRADE_WORK *wk );
static void BmpWinDelete( WORLDTRADE_WORK *wk );
static void InitWork( WORLDTRADE_WORK *wk );
static void FreeWork( WORLDTRADE_WORK *wk );
static void SetFnoteData( FNOTE_DATA *fnote,  Dpw_Tr_Data *trData );
static void AfterTradeCheck_ProcessControl( WORLDTRADE_WORK *wk );
static void WifiHistoryDataSet( WIFI_HISTORY *wifiHistory, Dpw_Tr_Data *trData );
static void ExchangePokemonDataAdd( WORLDTRADE_WORK *wk, POKEMON_PARAM *pp, int boxno);
static void TradeDateUpDate( WORLDTRADE_DATA *worldtrade_data );
static int MyPokemonPocketFullCheck( WORLDTRADE_WORK *wk, Dpw_Tr_Data *trData);
static void PrintError( WORLDTRADE_WORK *wk );
static void SetSaveNextSequence( WORLDTRADE_WORK *wk, int nextSeq1st, int nextSeq2nd );


static int Subseq_Start( WORLDTRADE_WORK *wk);
static int Subseq_UploadStart( WORLDTRADE_WORK *wk );
static int Subseq_UploadResult( WORLDTRADE_WORK *wk );
static int Subseq_UploadFinish( WORLDTRADE_WORK *wk );
static int Subseq_UploadFinishResult( WORLDTRADE_WORK *wk );
static int Subseq_Main( WORLDTRADE_WORK *wk);
static int Subseq_UploadSuccessMessage( WORLDTRADE_WORK *wk);
static int Subseq_DownloadSuccessMessage( WORLDTRADE_WORK *wk);
static int Subseq_ErrorMessage( WORLDTRADE_WORK *wk );
static int Subseq_ReturnTitleMessage( WORLDTRADE_WORK *wk );
static int Subseq_End( WORLDTRADE_WORK *wk);
static int Subseq_YesNo( WORLDTRADE_WORK *wk);
static int Subseq_ServerServiceError( WORLDTRADE_WORK *wk );
static int Subseq_ServerServiceEnd( WORLDTRADE_WORK *wk );
static int Subseq_MessageWait( WORLDTRADE_WORK *wk );
static int Subseq_DownloadStart( WORLDTRADE_WORK *wk );
static int Subseq_DownloadResult( WORLDTRADE_WORK *wk );
static int Subseq_DownloadFinish( WORLDTRADE_WORK *wk );
static int Subseq_DownloadFinishResult( WORLDTRADE_WORK *wk );
static int Subseq_ExchangeStart( WORLDTRADE_WORK *wk );			
static int Subseq_ExchangeResult( WORLDTRADE_WORK *wk );
static int Subseq_ExchangeFinish( WORLDTRADE_WORK *wk );
static int Subseq_ExchangeFinishResult( WORLDTRADE_WORK *wk );
static int Subseq_ExchangeSuccessMessage( WORLDTRADE_WORK *wk );
static int Subseq_ExchangeFailedMessage( WORLDTRADE_WORK *wk);
static void UploadPokemonDataDelete( WORLDTRADE_WORK *wk, int flag );
static void DownloadPokemonDataAdd( WORLDTRADE_WORK *wk, POKEMON_PARAM *pp, int boxno, int flag );
static int SubSeq_Save( WORLDTRADE_WORK *wk );
static int SubSeq_NowSaveMessage( WORLDTRADE_WORK *wk );
static int SubSeq_SaveLast( WORLDTRADE_WORK *wk );
static int Subseq_ServerDownloadResult( WORLDTRADE_WORK *wk );
static int Subseq_ServerDownload( WORLDTRADE_WORK *wk );
static int Subseq_ServerTradeCheckResult( WORLDTRADE_WORK *wk );
static int Subseq_ServerTradeCheck( WORLDTRADE_WORK *wk );
static int Subseq_DownloadExStart( WORLDTRADE_WORK *wk );
static int Subseq_DownloadExFinishResult( WORLDTRADE_WORK *wk );
static int Subseq_DownloadExSuccessMessage( WORLDTRADE_WORK *wk );
static int SubSeq_SaveWait( WORLDTRADE_WORK *wk );
static int SubSeq_SaveRandomWait( WORLDTRADE_WORK *wk );
static int Subseq_ServerTradeCheckEnd( WORLDTRADE_WORK *wk );
static int SubSeq_TimeoutSave( WORLDTRADE_WORK *wk );
static int SubSeq_TimeoutSaveWait( WORLDTRADE_WORK *wk );
static int Subseq_DownloadExFinish( WORLDTRADE_WORK *wk );




enum{
	SUBSEQ_START=0,
	SUBSEQ_MAIN,
	SUBSEQ_UPLOAD_START,
	SUBSEQ_UPLOAD_RESULT,
	SUBSEQ_UPLOAD_FINISH,
	SUBSEQ_UPLOAD_FINISH_RESULT,
	SUBSEQ_UPLOAD_SUCCESS_MESSAGE,

	SUBSEQ_DOWNLOAD_START,
	SUBSEQ_DOWNLOAD_RESULT,
	SUBSEQ_DOWNLOAD_FINISH,
	SUBSEQ_DOWNLOAD_FINISH_RESULT,
	SUBSEQ_DOWNLOAD_SUCCESS_MESSAGE,

	SUBSEQ_EXCHANGE_START,
	SUBSEQ_EXCHANGE_RESULT,
	SUBSEQ_EXCHANGE_FINISH,
	SUBSEQ_EXCHANGE_FINISH_RESULT,
	SUBSEQ_EXCHANGE_SUCCESS_MESSAGE,
	SUBSEQ_EXCHANGE_FAILED_MESSAGE,

	SUBSEQ_DOWNLOAD_EX_START,
	SUBSEQ_DOWNLOAD_EX_FINISH,
	SUBSEQ_DOWNLOAD_EX_FINISH_RESULT,
	SUBSEQ_DOWNLOAD_EX_SUCCESS_MESSAGE,
	

	SUBSEQ_SERVER_TRADE_CHECK,	
    SUBSEQ_SERVER_TRADECHECK_RESULT,
    SUBSEQ_SERVER_DOWNLOAD,		
    SUBSEQ_SERVER_DOWNLOAD_RESULT,	
	SUBSEQ_SERVER_TRADE_CHECK_END,


	SUBSEQ_NOW_SAVE_MES,
	SUBSEQ_SAVE,
	SUBSEQ_SAVE_RANDOM_WAIT,
	SUBSEQ_SAVE_WAIT,
	SUBSEQ_SAVE_LAST,

	SUBSEQ_TIMEOUT_SAVE,
    SUBSEQ_TIMEOUT_SAVE_WAIT,

	SUBSEQ_END,
	SUBSEQ_MES_WAIT,
	SUBSEQ_ERROR_MESSAGE,
	
	SUBSEQ_RETURN_TITLE_MESSAGE,

};



static int (*Functable[])( WORLDTRADE_WORK *wk ) = {
	Subseq_Start,				// SUBSEQ_START=0,
	Subseq_Main,             	// SUBSEQ_MAIN,
	Subseq_UploadStart,			// SUBSEQ_UPLOAD_START,
	Subseq_UploadResult,		// SUBSEQ_UPLOAD_RESULT,
	Subseq_UploadFinish,		// SUBSEQ_UPLOAD_FINISH,
	Subseq_UploadFinishResult,	// SUBSEQ_UPLOAD_FINISH_RESULT,
	Subseq_UploadSuccessMessage,// SUBSEQ_UPLOAD_SUCCESS_MESSAGE

	Subseq_DownloadStart,			// SUBSEQ_DOWNLOAD_START,
	Subseq_DownloadResult,			// SUBSEQ_DOWNLOAD_RESULT,
	Subseq_DownloadFinish,			// SUBSEQ_DOWNLOAD_FINISH,
	Subseq_DownloadFinishResult,	// SUBSEQ_DOWNLOAD_FINISH_RESULT,
	Subseq_DownloadSuccessMessage,	// SUBSEQ_DOWNLOAD_SUCCESS_MESSAGE

	Subseq_ExchangeStart,			// SUBSEQ_EXCHANGE_START,
	Subseq_ExchangeResult,			// SUBSEQ_EXCHANGE_RESULT,
	Subseq_ExchangeFinish,			// SUBSEQ_EXCHANGE_FINISH,
	Subseq_ExchangeFinishResult,	// SUBSEQ_EXCHANGE_FINISH_RESULT,
	Subseq_ExchangeSuccessMessage,	// SUBSEQ_EXCHANGE_SUCCESS_MESSAGE
	Subseq_ExchangeFailedMessage,	// SUBSEQ_EXCHANGE_FAILED_MESSAGE

	Subseq_DownloadExStart,			// SUBSEQ_DOWNLOAD_EX_START
	Subseq_DownloadExFinish,		// SUBSEQ_DOWNLOAD_EX_FINISH
	Subseq_DownloadExFinishResult,	// SUBSEQ_DOWNLOAD_EX_FINISH_RESULT
	Subseq_DownloadExSuccessMessage,// 


	Subseq_ServerTradeCheck,		// SUBSEQ_SERVER_TRADE_CHECK,	
	Subseq_ServerTradeCheckResult,	// 
	Subseq_ServerDownload,			// 
	Subseq_ServerDownloadResult,		// 
	Subseq_ServerTradeCheckEnd,		// SUBSEQ_SERVER_TRADE_CHECK_END,	

	SubSeq_NowSaveMessage,			// SUBSEQ_NOW_SAVE_MES,
	SubSeq_Save,					// SUBSEQ_SAVE,
	SubSeq_SaveRandomWait,			// SUBSEQ_SAVE_RANDOM_WAIT
	SubSeq_SaveWait,				// SUBSEQ_SAVE_WAIT,
	SubSeq_SaveLast,				// SUBSEQ_SAVE_LAST

	SubSeq_TimeoutSave,				// SUBSEQ_TIMEOUT_SAVE,
	SubSeq_TimeoutSaveWait,			// SUBSEQ_TIMEOUT_SAVE_WAIT


	Subseq_End,             	// SUBSEQ_END,
	Subseq_MessageWait,     	// SUBSEQ_MES_WAIT
	Subseq_ErrorMessage,		// SUBSEQ_ERROR_MES,
	Subseq_ReturnTitleMessage,	// SUBSEQ_RETURN_TITLE_MESSAGE,
};


#define POKEMON_RECV_OK						( 0 )
#define	POKEMON_ALL_FULL					( 1 )
#define POKEMON_NOT_FULL_BUT_MAIL_NORECV	( 2 )


//============================================================================================
//	プロセス関数
//============================================================================================

//==============================================================================
/**
 * $brief   世界交換入り口画面初期化
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Upload_Init(WORLDTRADE_WORK *wk, int seq)
{
	// ワーク初期化
	InitWork( wk );
	
	// BG設定
	BgInit( wk->bgl );

	// BGグラフィック転送
	BgGraphicSet( wk );

	// BMPWIN確保
	BmpWinInit( wk );

	// ワイプフェード開始
	WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_upload.c [250] M ********************\n" );
#endif

	// Wifi通信アイコン
	WorldTrade_WifiIconAdd( wk );

	wk->subprocess_seq = SUBSEQ_START;



	return SEQ_FADEIN;
}
//==============================================================================
/**
 * $brief   世界交換入り口画面メイン
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Upload_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret;

	// 通信状態を確認してアイコンの表示を変える
    WirelessIconEasy_SetLevel(WorldTrade_WifiLinkLevel());

	// シーケンス遷移で実行
	ret = (*Functable[wk->subprocess_seq])( wk );

	return ret;
}


//==============================================================================
/**
 * $brief   世界交換入り口画面終了
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Upload_End(WORLDTRADE_WORK *wk, int seq)
{
	FreeWork( wk );
	
	BmpWinDelete( wk );
	
	BgExit( wk->bgl );

	// 次のサブプロセスを設定する
	WorldTrade_SubProcessUpdate( wk );
	
	// 次が設定されていたら初期化へ
	return SEQ_INIT;
}


//--------------------------------------------------------------------------------------------
/**
 * BG設定
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInit( GF_BGL_INI * ini )
{

	// BG SYSTEM
	{	
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	// メイン画面テキスト面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}

	// メイン画面背景面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	// メイン画面背景面2
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}



	// サブ画面文字版0
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );

	}


	// サブ画面背景( この面は256色 )
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}


	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_WORLDTRADE );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_WORLDTRADE );

	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//メイン画面OBJ面ＯＮ
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );	//サブ画面OBJ面ＯＮ

}

//--------------------------------------------------------------------------------------------
/**
 * BG解放
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgExit( GF_BGL_INI * ini )
{

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

}


//--------------------------------------------------------------------------------------------
/**
 * グラフィックデータセット
 *
 * @param	wk		ポケモンリスト画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgGraphicSet( WORLDTRADE_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// 上画面ＢＧパレット転送
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_conect_nclr, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_WORLDTRADE);
	
	// 会話フォントパレット転送
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );
//	TalkFontPaletteLoad( PALTYPE_SUB_BG,  WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );

	// 会話ウインドウグラフィック転送
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MESFRAME_CHR, 
						WORLDTRADE_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_WORLDTRADE );

	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MENUFRAME_CHR,
						WORLDTRADE_MENUFRAME_PAL, 0, HEAPID_WORLDTRADE );

	// 主人公が登場してないときはサブ画面を表示しない
	if(wk->demo_end==0){
		GF_BGL_VisibleSet( GF_BGL_FRAME0_S, VISIBLE_OFF );
		GF_BGL_VisibleSet( GF_BGL_FRAME1_S, VISIBLE_OFF );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_OFF );	//サブ画面OBJ面ＯＮ
	}

	// デモから遷移してきた時は背景が壊れているので再転送
	if(wk->old_sub_process==WORLDTRADE_DEMO){
		WorldTrade_SubLcdBgGraphicSet( wk );
	}

}

#define SUB_TEXT_X		(  2 )
#define SUB_TEXT_Y		(  1 )
#define SUB_TEXT_SX		( 28 )
#define SUB_TEXT_SY		( 16 )

#define SUB_NUMBER_X	( 20 )
#define SUB_NUMBER_Y	( 21 )
#define SUB_NUMBER_SX	( 10 )
#define SUB_NUMBER_SY	(  2 )


#define TALK_MESSAGE_OFFSET	 ( WORLDTRADE_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define YESNO_OFFSET 		 ( TALK_MESSAGE_OFFSET + SUB_TEXT_SX*SUB_TEXT_SY )
//#define TITLE_MESSAGE_OFFSET ( TALK_MESSAGE_OFFSET + SUB_TEXT_SX*SUB_TEXT_SY )
//------------------------------------------------------------------
/**
 * BMPWIN処理（文字パネルにフォント描画）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinInit( WORLDTRADE_WORK *wk )
{
	// ---------- メイン画面 ------------------

	// BG0面BMP（会話ウインドウ）確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		TALK_WIN_X, TALK_WIN_Y, TALK_WIN_SX, TALK_WIN_SY, WORLDTRADE_TALKFONT_PAL,  TALK_MESSAGE_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0000 );

}	

//------------------------------------------------------------------
/**
 * $brief   確保したBMPWINを解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( WORLDTRADE_WORK *wk )
{
	
	GF_BGL_BmpWinDel( &wk->MsgWin );


}

//------------------------------------------------------------------
/**
 * 世界交換ワーク初期化
 *
 * @param   wk		WORLDTRADE_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( WORLDTRADE_WORK *wk )
{

	// 文字列バッファ作成
	wk->TalkString   = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WORLDTRADE );

	// レコードこうかんぼしゅう中！文字列取得
//	MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_002, wk->TitleString );

}


//------------------------------------------------------------------
/**
 * $brief   ワーク解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeWork( WORLDTRADE_WORK *wk )
{

	STRBUF_Delete( wk->TalkString ); 

}




//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//------------------------------------------------------------------
/**
 * $brief   サブプロセスシーケンススタート処理
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_Start( WORLDTRADE_WORK *wk)
{
	// 預けるのか？引き取るのか？もしくは交換か？

	switch(wk->sub_process_mode){
	case MODE_UPLOAD:
		// おくっています
		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_025, 1, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_UPLOAD_START );
		break;
	case MODE_DOWNLOAD:
		// うけとっています。
		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_025, 1, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_DOWNLOAD_START );
		break;
	case MODE_EXCHANGE:
		// 交換します
 		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_025, 1, 0x0f0f );
 		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_EXCHANGE_START );
		break;

		// 交換が終わったポケモンを受け取ります
	case MODE_DOWNLOAD_EX:
 		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_025, 1, 0x0f0f );
 		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_DOWNLOAD_EX_START );
		wk->sub_out_flg = 1;
		break;
		
	case MODE_SERVER_CHECK:	
		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_025, MSG_ALLPUT, 0x0f0f );
		// 「ようすをみる」に行く前にサーバーチェックを行う
		wk->subprocess_seq = SUBSEQ_SERVER_TRADE_CHECK;
		break;
	case MODE_POKEMON_EVO_SAVE:
		// 「ポケモンレポートをかいています。でんげんをきらないでください」
		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_15_004, 1, 0x0f0f );
		wk->sub_nextprocess = WORLDTRADE_TITLE;

		// 「セーブしています」と表示してからセーブ
		wk->subprocess_seq  = SUBSEQ_NOW_SAVE_MES;
		break;
	default:
		OS_TPrintf("モード指定がない\n");
		GF_ASSERT(0);
	}
	// 必ず時間アイコンを追加(upload.cの中では１回しかよばないはず）
	WorldTrade_TimeIconAdd(wk);

	return SEQ_MAIN;
}








//------------------------------------------------------------------
/**
 * $brief   世界交換ライブラリ接続状況取得開始
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_UploadStart( WORLDTRADE_WORK *wk )
{
	
	// カスタムボール領域をクリア
	PokePara_CustomBallDataInit( (POKEMON_PARAM*)wk->UploadPokemonData.postData.data );
	
	// ポケモンデータアップロード開始
	Dpw_Tr_UploadAsync( &wk->UploadPokemonData );

	OS_TPrintf("Dpw Trade データアップロード開始\n");

	// サーバー状態確認待ちへ
	wk->subprocess_seq = SUBSEQ_UPLOAD_RESULT;
	
	SetSaveNextSequence( wk, SUBSEQ_UPLOAD_FINISH, SUBSEQ_UPLOAD_SUCCESS_MESSAGE);

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   サーバー状態確認待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_UploadResult( WORLDTRADE_WORK *wk )
{
	int result;
	if ((result=Dpw_Tr_IsAsyncEnd())){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		case 0:		// 正常に動作している
			OS_TPrintf(" upload is right!\n");

			// データ退避
			UploadPokemonDataDelete( wk, 1 );

			wk->subprocess_seq = SUBSEQ_SAVE;
			break;
		case DPW_TR_ERROR_SERVER_FULL:
			// サーバーが満杯なのでアクセスできません→終了
			OS_TPrintf(" server full.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_ILLEGAL_DATA:
		case DPW_TR_ERROR_CHEAT_DATA:
		case DPW_TR_ERROR_NG_POKEMON_NAME :
		case DPW_TR_ERROR_NG_PARENT_NAME :
		case DPW_TR_ERROR_NG_MAIL_NAME :
		case DPW_TR_ERROR_NG_OWNER_NAME:
		case DPW_TR_ERROR_ILLIGAL_REQUEST :
			// 「このポケモンはあずける事ができません」→タイトルへ
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;		
		case DPW_TR_ERROR_CANCEL :
		case DPW_TR_ERROR_DATA_TIMEOUT :
			// 入り口で預けるか確認してからここ３０日前ポケモンはありなのか？
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;

		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// 「GTSのかくにんにしっぱいしました」
		case DPW_TR_ERROR_FAILURE :
			// サーバーと通信できません→終了
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_FATAL:			//!< 通信致命的エラー。電源の再投入が必要です
			// 即ふっとばし
			CommFatalErrorFunc_NoNumber();
			break;
		}
		
	}
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   サーバーにアップロードしたデータを有効にする
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_UploadFinish( WORLDTRADE_WORK *wk )
{
	Dpw_Tr_UploadFinishAsync();
	
	wk->subprocess_seq = SUBSEQ_UPLOAD_FINISH_RESULT;
	
	// ここに来ている時点でセーブには成功しているので、DepsitFlagを立てておかないと
	// 通信エラーになった時にもう一度「預ける」が表示されてしまう
	wk->DepositFlag = 1;
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   データ有効処理待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_UploadFinishResult( WORLDTRADE_WORK *wk )
{
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
#ifdef DEBUG_UPLOAD_ERROR
		result = DPW_TR_ERROR_FAILURE;
#endif
		switch(result){
		case 0:		// 正常に動作している
			// アップロード成功。セーブする。
			OS_TPrintf(" upload success.\n");
			wk->subprocess_seq = SUBSEQ_SAVE_LAST;
			break;

		case DPW_TR_ERROR_CANCEL :
		case DPW_TR_ERROR_DATA_TIMEOUT :
			// 入り口で預けるか確認してからここ３０日前ポケモンはありなのか？
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;

		case DPW_TR_ERROR_SERVER_FULL:
			// サーバーが満杯なのでアクセスできません→終了
			// （ここくるの？）
			OS_TPrintf(" server full.\n");
		case DPW_TR_ERROR_NO_DATA:
		case DPW_TR_ERROR_ILLIGAL_REQUEST :
			// 「このポケモンはあずける事ができません」→タイトルへ
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
		case DPW_TR_ERROR_FAILURE :
			// 「GTSのかくにんにしっぱいしました」
			// サーバーと通信できません→終了
			OS_TPrintf(" upload error. %d \n", result);
//			wk->ConnectErrorNo = result;
//			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			// ここはうけつけに戻ってはいけない。無理矢理通信エラー
			CommStateSetError(COMM_ERROR_RESET_OTHER);
			break;

		case DPW_TR_ERROR_FATAL:			//!< 通信致命的エラー。電源の再投入が必要です
			// 即ふっとばし
			CommFatalErrorFunc_NoNumber();
			break;
		}

	}
	return SEQ_MAIN;
}




//------------------------------------------------------------------
/**
 * $brief   世界交換ライブラリ接続状況取得開始
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadStart( WORLDTRADE_WORK *wk )
{
	
	// ポケモンデータダウンロード開始

	Dpw_Tr_DownloadAsync( &wk->UploadPokemonData );
	OS_TPrintf("Dpw Trade データダウンロード開始\n");

	// サーバー状態確認待ちへ
	wk->subprocess_seq = SUBSEQ_DOWNLOAD_RESULT;

	// セーブ込みシーケンス予約
	SetSaveNextSequence( wk, SUBSEQ_DOWNLOAD_FINISH, SUBSEQ_DOWNLOAD_SUCCESS_MESSAGE);


	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   サーバー状態確認待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadResult( WORLDTRADE_WORK *wk )
{
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		case 0:		// 正常に動作している

			// 引き取ったポケモンが交換成立していたらひきとったポケモンデータは間違っているので放棄
			// もう一度サーバーチェックに戻る
			if(wk->UploadPokemonData.isTrade){
				OS_TPrintf(" download is right! but traded\n");

				wk->subprocess_seq = SUBSEQ_SERVER_TRADE_CHECK;
			}else{
				OS_TPrintf(" download is right!\n");
				// データ復元
				DownloadPokemonDataAdd( wk, (POKEMON_PARAM*)wk->UploadPokemonData.postData.data,
										WorldTradeData_GetBoxNo( wk->param->worldtrade_data ), 
										wk->UploadPokemonData.isTrade );
				wk->subprocess_seq = SUBSEQ_SAVE;
			}


			break;

		// データが無い（かなりおかしい状況、さっきは落とせたのに）
		case DPW_TR_ERROR_NO_DATA :	
			OS_TPrintf(" download server stop service.\n");
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;

		// 1ヶ月過ぎてしまった
		case DPW_TR_ERROR_DATA_TIMEOUT :
			OS_TPrintf(" server full.\n");
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;

	// -----------------------------------------
	// 共通エラー処理
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;

		case DPW_TR_ERROR_FAILURE :
			// 「GTSのかくにんにしっぱいしました」
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// サーバーと通信できません→終了
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_FATAL:			//!< 通信致命的エラー。電源の再投入が必要です
			// 即ふっとばし
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------
		}
		
	}
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   サーバーからデータを削除する
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadFinish( WORLDTRADE_WORK *wk )
{
	Dpw_Tr_ReturnAsync();
	OS_TPrintf("-------------------------------------Dpw_Tr_ReturnAsyncよびだし\n");
	
	wk->subprocess_seq = SUBSEQ_DOWNLOAD_FINISH_RESULT;
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   データ有効処理待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadFinishResult( WORLDTRADE_WORK *wk )
{
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch(result){
		case 0:
			// サーバーからダウンロード成功。セーブする。
			OS_TPrintf(" download success.\n");
			wk->subprocess_seq = SUBSEQ_SAVE_LAST;

			break;
		// データが無い（かなりおかしい状況、さっきは落とせたのに）
		case DPW_TR_ERROR_NO_DATA :	
			OS_TPrintf(" download server stop service.\n");

		// 1ヶ月過ぎてしまった(来ないような気がする）
		case DPW_TR_ERROR_DATA_TIMEOUT :
			OS_TPrintf(" server full.\n");

		// 最後のつめを行おうとしたら交換が成立してしまった。
		// エラーが起きた事にして外にだしてしまう→もどってくれば交換が成立してます。
		case DPW_TR_ERROR_ILLIGAL_REQUEST:
			CommStateSetError(COMM_ERROR_RESET_GTS);
			break;
	// -----------------------------------------
	// 共通エラー処理
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :

		case DPW_TR_ERROR_FAILURE :
			// 「GTSのかくにんにしっぱいしました」
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// サーバーと通信できません→終了
			OS_TPrintf(" upload error. %d \n", result);

			// セーブがほとんど書き込まれている状況ではデータを元に戻せない
			// 無理矢理通信エラーへ
			CommStateSetError(COMM_ERROR_RESET_OTHER);
			break;
		case DPW_TR_ERROR_FATAL:			//!< 通信致命的エラー。電源の再投入が必要です
			// 即ふっとばし
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------

		}

	}
	return SEQ_MAIN;
}







//------------------------------------------------------------------
/**
 * $brief   世界交換ライブラリ接続状況取得開始
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ExchangeStart( WORLDTRADE_WORK *wk )
{

	// カスタムボール領域をクリア
	PokePara_CustomBallDataInit( (POKEMON_PARAM*)wk->UploadPokemonData.postData.data );

	
	// ポケモンデータ交換開始
	Dpw_Tr_TradeAsync ( wk->DownloadPokemonData[wk->TouchTrainerPos].id,
						&wk->UploadPokemonData,
						&wk->ExchangePokemonData );

	OS_TPrintf("Dpw Trade データ交換開始 id = %08x\n", wk->DownloadPokemonData[wk->TouchTrainerPos].id);


	// セーブ込みシーケンス予約
	SetSaveNextSequence( wk, SUBSEQ_EXCHANGE_FINISH, SUBSEQ_EXCHANGE_SUCCESS_MESSAGE);

	// サーバー状態確認待ちへ
	wk->subprocess_seq = SUBSEQ_EXCHANGE_RESULT;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   サーバー状態確認待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ExchangeResult( WORLDTRADE_WORK *wk )
{
	int result;
	if ((result=Dpw_Tr_IsAsyncEnd())){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		case 0:		// 正常に動作している
			OS_TPrintf(" exchange is right!\n");
			wk->subprocess_seq = SUBSEQ_SAVE;

			UploadPokemonDataDelete( wk, 0 );
			ExchangePokemonDataAdd(  wk, (POKEMON_PARAM*)wk->ExchangePokemonData.postData.data,
										wk->BoxTrayNo);

			// 地球儀情報登録
			WifiHistoryDataSet( wk->param->wifihistory, &wk->ExchangePokemonData );

			// スコア加算
			RECORD_Score_Add( wk->param->record, SCORE_ID_WORLD_TRADE );

			// 冒険ノートデータ登録処理
			SetFnoteData( wk->param->fnote,  &wk->ExchangePokemonData );

			// レコード用処理
			RECORD_Inc( wk->param->record, RECID_WIFI_TRADE );


			break;

		// トレード発行失敗
		case DPW_TR_ERROR_ILLIGAL_REQUEST :	
			OS_TPrintf(" exchange is failed.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_EXCHANGE_FAILED_MESSAGE;
			break;

		// 不正データだった
		case DPW_TR_ERROR_ILLEGAL_DATA:
		case DPW_TR_ERROR_CHEAT_DATA:
		case DPW_TR_ERROR_NG_POKEMON_NAME :
		case DPW_TR_ERROR_NG_PARENT_NAME :
		case DPW_TR_ERROR_NG_MAIL_NAME :
		case DPW_TR_ERROR_NG_OWNER_NAME:
			// 「このポケモンはあずける事ができません」→タイトルへ
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;		
	// -----------------------------------------
	// 共通エラー処理
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
			// 「GTSのかくにんにしっぱいしました」→タイトルへ
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;

		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
		case DPW_TR_ERROR_FAILURE :
			// サーバーと通信できません→終了
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_FATAL:			//!< 通信致命的エラー。電源の再投入が必要です
			// 即ふっとばし
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------
		}
		
	}
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   サーバーからデータを削除する
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ExchangeFinish( WORLDTRADE_WORK *wk )
{
	Dpw_Tr_TradeFinishAsync();
	OS_TPrintf("交換終了処理開始\n");
	
	wk->subprocess_seq = SUBSEQ_EXCHANGE_FINISH_RESULT;
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   データ有効処理待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ExchangeFinishResult( WORLDTRADE_WORK *wk )
{
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch(result){
		case 0:
			OS_TPrintf(" exchange success.\n");
			wk->subprocess_seq = SUBSEQ_SAVE_LAST;

			break;

		// 引き取られてしまった
		case DPW_TR_ERROR_ILLIGAL_REQUEST:
			CommStateSetError(COMM_ERROR_RESET_GTS);
			break;
	// -----------------------------------------
	// 共通エラー処理
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
			// 「GTSのかくにんにしっぱいしました」→タイトルへ

		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
		case DPW_TR_ERROR_FAILURE :
			// サーバーと通信できません→終了
			OS_TPrintf(" upload error. %d \n", result);
	
			// ９９％までセーブが書き込まれた状況では元に戻せないので
			// 無理矢理通信エラーへ
			CommStateSetError(COMM_ERROR_RESET_OTHER);
			break;

			break;
		case DPW_TR_ERROR_FATAL:			//!< 通信致命的エラー。電源の再投入が必要です
			// 即ふっとばし
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------
		}

	}
	return SEQ_MAIN;
}




//------------------------------------------------------------------
/**
 * @brief   交換が成立しているか確認する
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ServerTradeCheck( WORLDTRADE_WORK *wk )
{
	Dpw_Tr_GetUploadResultAsync( &wk->UploadPokemonData );

	OS_Printf("サーバー状態確認開始\n");

	wk->subprocess_seq  = SUBSEQ_SERVER_TRADECHECK_RESULT;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   交換ポケモンサーバー確認処理待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ServerTradeCheckResult( WORLDTRADE_WORK *wk )
{
	// サーバー問い合わせ終了待ち
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		// 交換は成立していなかったので、自分のデータ取得へ
		case 0:
//			OS_TPrintf(" no exchange.\n");
			wk->subprocess_seq = SUBSEQ_SERVER_DOWNLOAD;

#ifdef PM_DEBUG
			{
				Dpw_Tr_Data *dtd = &wk->UploadPokemonData;

				OS_Printf( "TrainerId = %05d,  nation = %d, area = %d\n", dtd->trainerID, dtd->countryCode, dtd->localCode);
				OS_Printf( "Version   = %d,  language = %d, \n", dtd->versionCode, dtd->langCode);
				OS_Printf( "postData  No = %d,  gender = %d, level = %d\n", dtd->postSimple.characterNo, dtd->postSimple.gender, dtd->postSimple.level);
				OS_Printf( "WantData  No = %d,  gender = %d, level min = %d max = %d\n", 
						dtd->wantSimple.characterNo, dtd->wantSimple.gender, dtd->wantSimple.level_min,dtd->wantSimple.level_max);
			}
#endif
			// 預けているか？
			break;

		// 交換は成立していた
		case 1:
			OS_TPrintf(" download exchange pokemon on sever.\n");
			// サーバーにポケモンを預けているのは確か。
			wk->DepositFlag = 1;

#ifdef PM_DEBUG
			{
				Dpw_Tr_Data *dtd = &wk->UploadPokemonData;
	
				OS_Printf( "TrainerId = %05d,  nation = %d, area = %d\n", dtd->trainerID, dtd->countryCode, dtd->localCode);
				OS_Printf( "Version   = %d,  language = %d, \n", dtd->versionCode, dtd->langCode);
				OS_Printf( "postData  No = %d,  gender = %d, level = %d\n", dtd->postSimple.characterNo, dtd->postSimple.gender, dtd->postSimple.level);
				OS_Printf( "WantData  No = %d,  gender = %d, level min = %d max = %d\n", 
						dtd->wantSimple.characterNo, dtd->wantSimple.gender, dtd->wantSimple.level_min,dtd->wantSimple.level_max);
			}
#endif
			switch(MyPokemonPocketFullCheck(wk, &wk->UploadPokemonData)){
			// 空きが無い
			case POKEMON_ALL_FULL:
				WorldTrade_TimeIconDel(wk);
		 		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_030, 1, 0x0f0f );
 				WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SERVER_TRADE_CHECK_END );
				break;
			// メールが受け取れない
			case POKEMON_NOT_FULL_BUT_MAIL_NORECV:
				WorldTrade_TimeIconDel(wk);
		 		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_036, 1, 0x0f0f );
 				WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SERVER_TRADE_CHECK_END );
				break;
			// 受け取れる
			case POKEMON_RECV_OK:
#ifdef REPAIR_060804
				// こっちがバグ修正しているほう
				wk->subprocess_seq   = SUBSEQ_DOWNLOAD_EX_START;
				wk->sub_out_flg = 1;
#else
				WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_DOWNLOAD_EX );
				wk->subprocess_seq  = SUBSEQ_END;
#endif

				break;
			}
			break;
		// ポケモンをあずけている場合はタイムアウトが発生してしまっている（てもちに戻す）
		case DPW_TR_ERROR_NO_DATA :	
			OS_TPrintf(" no data on sever.\n");
			wk->DepositFlag = 0;
			if(WorldTradeData_GetFlag(wk->param->worldtrade_data)){
				POKEMON_PARAM *pp = PokemonParam_AllocWork(HEAPID_WORLDTRADE);
				WorldTradeData_GetPokemonData( wk->param->worldtrade_data, pp );
				WORDSET_RegisterPokeNickName( wk->WordSet, 0, PPPPointerGet(pp) );

				wk->error_mes_no   = msg_gtc_01_003;
				wk->subprocess_seq = SUBSEQ_TIMEOUT_SAVE;
				
				// 保存してあったポケモンを戻す
				DownloadPokemonDataAdd( wk, pp, WorldTradeData_GetBoxNo( wk->param->worldtrade_data ), 0 );
				// 預けてあるフラグを解除
				WorldTradeData_SetFlag(wk->param->worldtrade_data, 0);
				sys_FreeMemoryEz(pp);
			}else{
				// サーバー確認処理終了後の行き先を設定
				AfterTradeCheck_ProcessControl( wk );
			}
			break;

		// 預けたポケモンが交換成立後にタイムアウトした。そのまま削除
		case DPW_TR_ERROR_DATA_TIMEOUT :
			OS_TPrintf(" your data on server is timeout.\n");

			// サーバー確認処理終了後の行き先を設定
//			AfterTradeCheck_ProcessControl( wk );

			wk->DepositFlag = 0;
			// 絶対預けてあるはずだけど念のため、フラグ確認
			if(WorldTradeData_GetFlag(wk->param->worldtrade_data)){
				POKEMON_PARAM *pp = PokemonParam_AllocWork(HEAPID_WORLDTRADE);
				WorldTradeData_GetPokemonData( wk->param->worldtrade_data, pp );
				WORDSET_RegisterPokeNickName( wk->WordSet, 0, PPPPointerGet(pp) );

				wk->error_mes_no   = msg_gtc_01_004;
				wk->subprocess_seq = SUBSEQ_TIMEOUT_SAVE;
				
				// 預けてあるフラグを解除
				WorldTradeData_SetFlag(wk->param->worldtrade_data, 0);

				sys_FreeMemoryEz(pp);
			}
			break;
	// -----------------------------------------
	// 共通エラー処理
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
		case DPW_TR_ERROR_FAILURE :
			// 他の場合はタイトルに戻すが、ここで失敗すると
			// その後の操作も失敗する可能性が高いので。
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// サーバーと通信できません→終了
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_FATAL:			//!< 通信致命的エラー。電源の再投入が必要です
			// 即ふっとばし
			ComErrorWarningResetCall(HEAPID_BASE_APP,COMM_ERRORTYPE_POWEROFF,0);
			break;
	// -----------------------------------------
		}
		

	}
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   受け取ることができなかったのでタイトルにもどる
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ServerTradeCheckEnd( WORLDTRADE_WORK *wk )
{
	// ポケモンを受け取ることができないので、タイトルにもどる
	WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
	wk->subprocess_seq = SUBSEQ_END;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   既にサーバーに預けているか確認
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ServerDownload( WORLDTRADE_WORK *wk )
{
	Dpw_Tr_DownloadAsync( &wk->UploadPokemonData );

	wk->subprocess_seq  = SUBSEQ_SERVER_DOWNLOAD_RESULT;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   交換ポケモンサーバー確認処理待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ServerDownloadResult( WORLDTRADE_WORK *wk )
{
	// サーバー問い合わせ終了待ち
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		// 預けているポケモンのデータを取得した
		case 0:
			OS_TPrintf(" download data on sever.\n");
			wk->DepositFlag = 1;

			{
				Dpw_Tr_Data *dtd = &wk->UploadPokemonData;

				OS_Printf( "TrainerId = %05d,  nation = %d, area = %d\n", dtd->trainerID, dtd->countryCode, dtd->localCode);
				OS_Printf( "Version   = %d,  language = %d, \n", dtd->versionCode, dtd->langCode);
				OS_Printf( "postData  No = %d,  gender = %d, level = %d\n", dtd->postSimple.characterNo, dtd->postSimple.gender, dtd->postSimple.level);
				OS_Printf( "WantData  No = %d,  gender = %d, level min = %d max = %d\n", 
						dtd->wantSimple.characterNo, dtd->wantSimple.gender, dtd->wantSimple.level_min,dtd->wantSimple.level_max);

			}
			break;
		// ポケモンは預けられていない
		case DPW_TR_ERROR_NO_DATA :	
			OS_TPrintf(" no data on sever.\n");
			wk->DepositFlag = 0;
			break;
		// 預けたポケモンがタイムアウトしてしまったので、隠しているポケモンを復活させる
		case DPW_TR_ERROR_DATA_TIMEOUT :
			OS_TPrintf(" your data on server is timeout.\n");
			break;
	// -----------------------------------------
	// 共通エラー処理
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;

		case DPW_TR_ERROR_FAILURE :
			// 「GTSのかくにんにしっぱいしました」
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// サーバーと通信できません→終了
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_FATAL:			//!< 通信致命的エラー。電源の再投入が必要です
			// 即ふっとばし
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------

		}

		// サーバー確認処理終了後の行き先を設定
		AfterTradeCheck_ProcessControl( wk );

	}
	return SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   サーバー確認処理終了後の戻り先を設定
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void AfterTradeCheck_ProcessControl( WORLDTRADE_WORK *wk )
{
	switch( wk->sub_returnprocess ){
	case WORLDTRADE_TITLE:
		// GTC入り口画面へ
		WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
		wk->subprocess_seq  = SUBSEQ_END;
		break;

	// 自分のポケモン確認画面へ	
	case WORLDTRADE_MYPOKE:
		WorldTrade_SubProcessChange( wk, WORLDTRADE_MYPOKE, MODE_VIEW );
		wk->subprocess_seq  = SUBSEQ_END;
		break;
	}

}


//------------------------------------------------------------------
/**
 * @brief   交換済みポケモンをサーバーから削除する
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadExStart( WORLDTRADE_WORK *wk)
{

	// データ復元
	DownloadPokemonDataAdd( wk, (POKEMON_PARAM*)wk->UploadPokemonData.postData.data,
							WorldTradeData_GetBoxNo( wk->param->worldtrade_data ), 
							wk->UploadPokemonData.isTrade );

	// 地球儀情報登録
	WifiHistoryDataSet( wk->param->wifihistory, &wk->UploadPokemonData );

	// スコア加算
	RECORD_Score_Add( wk->param->record, SCORE_ID_WORLD_TRADE );

	// 冒険ノートデータ登録処理
	SetFnoteData( wk->param->fnote,  &wk->UploadPokemonData );

	// レコード用処理
	RECORD_Inc( wk->param->record, RECID_WIFI_TRADE );

	// 引き取った事にする
	WorldTradeData_SetFlag( wk->param->worldtrade_data, 0 );

	// セーブへ
	wk->subprocess_seq = SUBSEQ_SAVE;

	// セーブ込みシーケンス予約
	SetSaveNextSequence( wk, SUBSEQ_DOWNLOAD_EX_FINISH, SUBSEQ_DOWNLOAD_SUCCESS_MESSAGE);
	
	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   交換済みデータ安定処理開始
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadExFinish( WORLDTRADE_WORK *wk )
{

	// 交換済みポケモンサーバーから削除処理
	Dpw_Tr_DeleteAsync();
	OS_TPrintf("-------------------------------------Dpw_Tr_DeleteAsyncよびだし\n");
	OS_TPrintf("ダウンロード終了処理開始\n");

	// セーブへ
	wk->subprocess_seq = SUBSEQ_DOWNLOAD_EX_FINISH_RESULT;
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   結果待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadExFinishResult( WORLDTRADE_WORK *wk)
{
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		case 0:		// 正常に動作している

			// 引き取ったポケモンが交換成立していたらひきとったポケモンデータは間違っているので放棄
			// もう一度サーバーチェックに戻る
			OS_TPrintf(" downloadEx is right!\n");

			wk->subprocess_seq = SUBSEQ_SAVE_LAST;
			break;

		// データが無い（かなりおかしい状況、さっきは落とせたのに）
		case DPW_TR_ERROR_NO_DATA :	
			OS_TPrintf(" download server stop service.\n");
			CommStateSetError(COMM_ERROR_RESET_GTS);
			break;

		// 1ヶ月過ぎてしまった
		case DPW_TR_ERROR_DATA_TIMEOUT :
			OS_TPrintf(" server full.\n");


	// -----------------------------------------
	// 共通エラー処理
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
			wk->ConnectErrorNo = result;

		case DPW_TR_ERROR_FAILURE :
			// 「GTSのかくにんにしっぱいしました」
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// サーバーと通信できません→終了
			OS_TPrintf(" upload error. %d \n", result);

			// ９９％までセーブが書き込まれた状況では元に戻せないので
			// 無理矢理通信エラーへ
			CommStateSetError(COMM_ERROR_RESET_OTHER);

			break;
		case DPW_TR_ERROR_FATAL:			//!< 通信致命的エラー。電源の再投入が必要です
			// 即ふっとばし
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------
		}
		
	}
	return SEQ_MAIN;
	
}



//------------------------------------------------------------------
/**
 * $brief   サブプロセスシーケンスメイン
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_Main( WORLDTRADE_WORK *wk)
{


	return SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   あずけるのに成功しましたメッセージ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_UploadSuccessMessage( WORLDTRADE_WORK *wk )
{
//	Enter_MessagePrint( wk, wk->MsgManager,msg_gtc_13_002, 1, 0x0f0f );
//	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_NOW_SAVE_MES );
	
	// あずけたフラグを立てる
	wk->DepositFlag     = 1;

	// デモへ行く予約をしておく
	WorldTrade_SubProcessChange( wk, WORLDTRADE_DEMO, MODE_UPLOAD );
	
	wk->subprocess_seq = SUBSEQ_END;
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   ひきとるのに成功しましたメッセージ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadSuccessMessage( WORLDTRADE_WORK *wk)
{
//	Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_14_002, 1, 0x0f0f );
//	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_NOW_SAVE_MES );
	
	// あずけたフラグを落とす
	 wk->DepositFlag     = 0;


	// デモへ行く予約をしておく
	WorldTrade_SubProcessChange( wk, WORLDTRADE_DEMO, MODE_DOWNLOAD );
	
	wk->subprocess_seq = SUBSEQ_END;

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   交換に成功しましたメッセージ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ExchangeSuccessMessage( WORLDTRADE_WORK *wk)
{
//	Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_15_002, 1, 0x0f0f );
//	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_NOW_SAVE_MES );
	
	// デモへ行く予約をしておく
	WorldTrade_SubProcessChange( wk, WORLDTRADE_DEMO, MODE_EXCHANGE );

	wk->subprocess_seq = SUBSEQ_END;

	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   あたらしいポケモンがやってきました
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadExSuccessMessage( WORLDTRADE_WORK *wk)
{
//	Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_14_002, 1, 0x0f0f );
//	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_NOW_SAVE_MES );
	
	// あずけたフラグを落とす
	 wk->DepositFlag     = 0;

	// デモへ行く予約をしておく
	WorldTrade_SubProcessChange( wk, WORLDTRADE_DEMO, MODE_DOWNLOAD_EX );
	
	wk->subprocess_seq = SUBSEQ_SAVE;

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   交換しようとしたポケモンが既に交換されてしまった
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ExchangeFailedMessage( WORLDTRADE_WORK *wk)
{
	Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_15_003, 1, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_END );
	
	WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );

	// 時間アイコン消去(２重解放になるのでNULLチェックはする）
	WorldTrade_TimeIconDel( wk );

	// 交換失敗なので下画面のＯＢＪを隠す
	WorldTrade_SubLcdMatchObjHide( wk );
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   エラーに対応したメッセージでプリント
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static void PrintError( WORLDTRADE_WORK *wk )
{
	int msgno = msg_gtc_error_004_01;

	// エラーが発生しました。
	switch(wk->ConnectErrorNo){
	case DPW_TR_ERROR_ILLEGAL_DATA :
	case DPW_TR_ERROR_CHEAT_DATA:		//!< アップロードされたデータが不正
	case DPW_TR_ERROR_NG_POKEMON_NAME:	//!< アップロードされたポケモンの名前がNGワードを含んでいる
	case DPW_TR_ERROR_NG_PARENT_NAME:	//!< アップロードされたポケモンの親の名前がNGワードを含んでいる
	case DPW_TR_ERROR_NG_MAIL_NAME:	//!< アップロードされたメールの名前がNGワードを含んでいる
	case DPW_TR_ERROR_NG_OWNER_NAME:	//!< アップロードされた主人公名がNGワードを含んでいる

		// このポケモンは預けることができません！
		msgno = msg_gtc_01_027;
		break;
	case DPW_TR_ERROR_SERVER_FULL:
		// サーバーがいっぱいです。しばらくしてからきてください
		msgno = msg_gtc_error_002;
		break;
	case DPW_TR_ERROR_SERVER_TIMEOUT:
	case DPW_TR_ERROR_DISCONNECTED:
		// ＧＴＳとのせつぞくがきれました。うけつけにもどります
		msgno = msg_gtc_error_006;
		break;
	case DPW_TR_ERROR_CANCEL  :
	case DPW_TR_ERROR_FAILURE :
	case DPW_TR_ERROR_NO_DATA:
	case DPW_TR_ERROR_ILLIGAL_REQUEST :
		//　つうしんエラーが発生しました。
		msgno = msg_gtc_error_004_01;
		break;
	
	}

	OS_TPrintf("error %d\n", wk->ConnectErrorNo);
	// エラーに対応したプリント
	Enter_MessagePrint( wk, wk->MsgManager, msgno, 1, 0x0f0f );

	
}


//------------------------------------------------------------------
/**
 * @brief   GTS終了エラーのメッセージ表示（この後強制終了）
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ErrorMessage( WORLDTRADE_WORK *wk )
{

	// エラーに対応したプリント
	PrintError(wk);
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_END );
	WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
	
	// 時間アイコン消去(２重解放になるのを気をつける）
	WorldTrade_TimeIconDel(wk);

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   アクセスに失敗して、エラーを表示してタイトルへ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ReturnTitleMessage( WORLDTRADE_WORK *wk )
{	
	// エラーに対応したプリント
	PrintError(wk);
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_END );
	WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
	
	// 時間アイコン消去(SUBSEQ_ENDと２重解放になるのでNULLチェックは必要
	WorldTrade_TimeIconDel(wk);

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   進化後に「セーブ中」表示して終了する流れの最初
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_NowSaveMessage( WORLDTRADE_WORK *wk )
{
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SAVE );

	// 進化後セーブはサーバーアクセスはないので、素直にセーブして終わる
	SetSaveNextSequence( wk, SUBSEQ_SAVE_LAST, SUBSEQ_END);
	
	return SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   セーブ処理呼び出し
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_Save( WORLDTRADE_WORK *wk )
{

	// 必ず全体セーブにする
	SaveData_RequestTotalSave();
	
	// セーブ初期化
	SaveData_DivSave_Init( wk->param->savedata,SVBLK_ID_MAX);

	wk->subprocess_seq = SUBSEQ_SAVE_RANDOM_WAIT;
	wk->wait           = gf_p_rand(60)+2;

	OS_TPrintf("セーブ開始 wait=%d\n", wk->wait);

	return SEQ_MAIN;

}



//------------------------------------------------------------------
/**
 * @brief   セーブ開始までのランダム終了待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SaveRandomWait( WORLDTRADE_WORK *wk )
{
	wk->wait--;
	if(wk->wait==0){
		wk->subprocess_seq = SUBSEQ_SAVE_WAIT;
	}
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   セーブ処理終了待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SaveWait( WORLDTRADE_WORK *wk )
{
	if(SaveData_DivSave_Main(wk->param->savedata)==SAVE_RESULT_LAST){

		// セーブシーケンスにくるまでに次の設定は終えているので、SUBSEQ_ENDだけでよい
		wk->subprocess_seq = wk->saveNextSeq1st;
		OS_TPrintf("セーブ９９％終了\n");

	}
	
	
	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * @brief   セーブ最後の１セクタ書き込み呼び出し処理
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SaveLast( WORLDTRADE_WORK *wk )
{
	if(SaveData_DivSave_Main(wk->param->savedata)==SAVE_RESULT_OK){
		wk->subprocess_seq = wk->saveNextSeq2nd;

		OS_TPrintf("セーブ100％終了\n");
		// 時間アイコン消去
		WorldTrade_TimeIconDel(wk);
	}
	
	
	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   セーブ処理呼び出し
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_TimeoutSave( WORLDTRADE_WORK *wk )
{

	// 必ず全体セーブにする
	SaveData_RequestTotalSave();

	
	// セーブ初期化
	SaveData_DivSave_Init( wk->param->savedata,SVBLK_ID_MAX);
	wk->subprocess_seq = SUBSEQ_TIMEOUT_SAVE_WAIT;

	return SEQ_MAIN;

}



//------------------------------------------------------------------
/**
 * @brief   セーブ処理終了待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_TimeoutSaveWait( WORLDTRADE_WORK *wk )
{
	if(SaveData_DivSave_Main(wk->param->savedata)==SAVE_RESULT_OK){

		// タイトル画面に戻る設定
		WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );

		// 時間アイコン消去(２重解放になるのを気をつける）
		WorldTrade_TimeIconDel(wk);

		// ●●●はこうかんされませんでした…
		Enter_MessagePrint( wk, wk->MsgManager, wk->error_mes_no, 1, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SERVER_TRADE_CHECK_END );

	}
	
	
	return SEQ_MAIN;
	
}



//------------------------------------------------------------------
/**
 * $brief   サブプロセスシーケンス終了処理
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_End( WORLDTRADE_WORK *wk)
{
	// 必ず時間アイコンを消去(２重解放対策はしておく）
	WorldTrade_TimeIconDel(wk);
	
	WirelessIconEasyEnd();

	if( wk->sub_out_flg == 1 ){
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_upload.c [1737] MS ********************\n" );
#endif
	}else{
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_upload.c [1741] M ********************\n" );
#endif
	}
	wk->subprocess_seq = 0;
	
	return SEQ_FADEOUT;
}

//------------------------------------------------------------------
/**
 * $brief   はい・いいえ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_YesNo( WORLDTRADE_WORK *wk)
{
	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY2, YESNO_OFFSET );
	wk->subprocess_seq = wk->subprocess_nextseq;
//	wk->subprocess_seq = SUBSEQ_YESNO_SELECT;

	return SEQ_MAIN;
	
}





//------------------------------------------------------------------
/**
 * $brief   会話終了を待って次のシーケンスへ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_MessageWait( WORLDTRADE_WORK *wk )
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		wk->subprocess_seq = wk->subprocess_nextseq;
	}
	return SEQ_MAIN;

}




//------------------------------------------------------------------
/**
 * @brief   預けたポケモンデータをBOXかてもちから消去する
 *
 * @param   pp		
 * @param   flag	格納フラグを立てるか?(1:立てる 0:立てない）
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UploadPokemonDataDelete( WORLDTRADE_WORK *wk, int flag )
{
//	BOXDAT_PutPokemonBox( BOX_DATA* box, u32 boxNum, POKEMON_PASO_PARAM* poke );

	// 手持ちからでなければBOXのポケモンを消去する
	if(wk->BoxTrayNo!=18){
		POKEMON_PARAM *pp = PokemonParam_AllocWork(HEAPID_WORLDTRADE);
		PokeReplace(
			BOXDAT_GetPokeDataAddress( wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos ),
			pp
		);

		WorldTradeData_SetPokemonData( wk->param->worldtrade_data, pp, wk->BoxTrayNo );

		// ボックスから消去
		BOXDAT_ClearPokemon( wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos );
		OS_Printf("box %d, %d のポケモンを削った\n", wk->BoxTrayNo, wk->BoxCursorPos);

		sys_FreeMemoryEz(pp);
	}else{
	// てもち

		POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->param->myparty, wk->BoxCursorPos);
		OS_Printf("てもちから消去 pos = %d\n", wk->BoxCursorPos);

		// カスタムボール領域をクリア
		PokePara_CustomBallDataInit( pp );

		// セーブ領域に保存
		WorldTradeData_SetPokemonData( wk->param->worldtrade_data, pp, wk->BoxTrayNo );

		// 手持ちから消去
		PokeParty_Delete( wk->param->myparty, wk->BoxCursorPos );

		// てもちからペラップがいなくなったら声データを消去する
		if(PokeParty_PokemonCheck( wk->param->myparty, MONSNO_PERAPPU )==0){
			PERAPVOICE *pv = SaveData_GetPerapVoice( wk->param->savedata );
			PERAPVOICE_ClearExistFlag( pv );
		}
		
	}
	
	if(flag){
		// 預けたフラグ
		WorldTradeData_SetFlag( wk->param->worldtrade_data, 1 );
	}
}

//------------------------------------------------------------------
/**
 * @brief   引き取る処理
 *
 * @param   wk		
 * @param   pp		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DownloadPokemonDataAdd( WORLDTRADE_WORK *wk, POKEMON_PARAM *pp, int boxno, int flag )
{
	int itemno = PokeParaGet(pp, ID_PARA_item, NULL);

	// 図鑑等の登録処理
	SaveData_GetPokeRegister( wk->param->savedata, pp );

	// なにはともあれてもちに入れようとする
	// ボックスに入れようとしている時にポケモンにメールがついている場合は
	// てもちに入れるようにする
	boxno = 18;

	if(PokeParty_GetPokeCount(wk->param->myparty)==6){
		// てもちがいっぱいだったらボックスに
		boxno = 0;
	}

	// 交換が成立していた
	if(flag){
		u8 friend = FIRST_NATUKIDO;

		// なつき度を初期値７０にする
		PokeParaPut( pp, ID_PARA_friend, &friend );

		// ポケモンの交換成立最終日をセーブする
		TradeDateUpDate( wk->param->worldtrade_data );
	}

	// てもち(てもちが一杯はこの時点だとどうしようもないのでこないようにしないと）
	if(boxno==18){
		int num;

		// メールがついているので、手持ちにしか受け取れない
		PokeParty_Add(wk->param->myparty, pp);
		num = PokeParty_GetPokeCount( wk->param->myparty );

		wk->EvoPokeInfo.boxno = 18;
		wk->EvoPokeInfo.pos   = num-1;

	}else{
	// ボックス
		
		int boxpos=0;
		// メールが無ければBOXに入れる

		// ボックスの空いているところを探す
		BOXDAT_GetEmptyTrayNumberAndPos( wk->param->mybox, &boxno, &boxpos );

		// 受け取ったポケモンを格納する
		BOXDAT_PutPokemonBox( wk->param->mybox, boxno, PPPPointerGet(pp) );

		wk->EvoPokeInfo.boxno = boxno;
		wk->EvoPokeInfo.pos   = boxpos;
	}

	// 世界交換ワークから預けてるフラグを落とす
	WorldTradeData_SetFlag( wk->param->worldtrade_data, 0 );



}


//------------------------------------------------------------------
/**
 * @brief   検索してみつけたポケモンと交換する時の処理
 *
 * @param   wk		
 * @param   pp		
 * @param   boxno		
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ExchangePokemonDataAdd( WORLDTRADE_WORK *wk, POKEMON_PARAM *pp, int boxno )
{

	// 図鑑登録処理
	SaveData_GetPokeRegister( wk->param->savedata, pp );

	boxno = 18;
	if(PokeParty_GetPokeCount(wk->param->myparty)==6){
		// てもちがいっぱいだったら格納先をボックスに
		OS_Printf("格納先はBOX\n");
		boxno = 0;
	}

	{
		// 交換されたポケモンに入れるなつき度
		u8 friend = FIRST_NATUKIDO;
		PokeParaPut(pp, ID_PARA_friend, &friend);
	}

	// てもち(てもちが一杯はこの時点だとどうしようもないので）
	if(boxno==18){
		int num;

		// メールがついているので、手持ちにしか受け取れない
		PokeParty_Add(wk->param->myparty, pp);
		num = PokeParty_GetPokeCount( wk->param->myparty );

		wk->EvoPokeInfo.boxno = 18;
		wk->EvoPokeInfo.pos   = num-1;
		OS_Printf("てもちに追加した\n");

	}else{
	// ボックス
		
		int boxpos=0;
		// メールが無ければBOXに入れる

		// ボックスの空いているところを探す
		BOXDAT_GetEmptyTrayNumberAndPos( wk->param->mybox, &boxno, &boxpos );

		// 受け取ったポケモンを格納する
		BOXDAT_PutPokemonBox( wk->param->mybox, boxno, PPPPointerGet(pp) );

		wk->EvoPokeInfo.boxno = boxno;
		wk->EvoPokeInfo.pos   = boxpos;

		OS_Printf("BOXの %d トレイに追加した\n", boxno);

	}

	WorldTradeData_SetFlag( wk->param->worldtrade_data, 0 );


	// ポケモンの交換成立最終日をセーブする
	TradeDateUpDate( wk->param->worldtrade_data );
	
}

//------------------------------------------------------------------
/**
 * @brief   最終交換日付を更新
 *
 * @param   worldtrade_data		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TradeDateUpDate( WORLDTRADE_DATA *worldtrade_data )
{
	RTCDate date;
	RTCTime time;
	GF_DATE gfDate;

	// サーバー基準の現在時刻を取得
	DWC_GetDateTime( &date, &time);

	// 最終交換日付として保存
	gfDate = RTCDate2GFDate( &date );
	WorldTradeData_SetLastDate( worldtrade_data, gfDate );
	OS_Printf(" %d年 %d月 %d日に交換成立\n",
				GFDate_GetYear( gfDate ),GFDate_GetMonth( gfDate ),GFDate_GetDay( gfDate ));

}

//------------------------------------------------------------------
/**
 * @brief   相手の交換情報を参照して地球儀情報を登録する
 *
 * @param   wifiHistory		
 * @param   trData		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void WifiHistoryDataSet( WIFI_HISTORY *wifiHistory, Dpw_Tr_Data *trData )
{

	Comm_WifiHistoryDataSet( wifiHistory, trData->countryCode, trData->localCode, trData->langCode );
	
}

//------------------------------------------------------------------
/**
 * @brief   冒険ノートデータ登録処理
 *
 * @param   fnote		
 * @param   trData		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetFnoteData( FNOTE_DATA *fnote,  Dpw_Tr_Data *trData )
{
	void *fnoteWork;
	STRCODE  MonsName[MONS_NAME_SIZE+EOM_SIZE];
	POKEMON_PARAM *pp = (POKEMON_PARAM*)trData->postData.data;

	PokeParaGet( pp, ID_PARA_nickname, MonsName );

	fnoteWork = FNOTE_SioGTCDataMake( trData->name, trData->gender, 
									MonsName, PokeSexGet(pp), HEAPID_WORLDTRADE );

	FNOTE_DataSave( fnote, fnoteWork, FNOTE_TYPE_SIO );
}

#define BOX_MAX_NUM	(BOX_MAX_RAW*BOX_MAX_COLUMN*BOX_MAX_TRAY)

//------------------------------------------------------------------
/**
 * @brief   自分はポケモンを受け取れるか？メールがついていても受け取れる？
 *
 * @param   wk		
 * @param   trData		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int MyPokemonPocketFullCheck( WORLDTRADE_WORK *wk, Dpw_Tr_Data *trData)
{
	
	// うけとるポケモンがメールをもっている時はてもちに空き無いといけない
	if( WorldTrade_PokemonMailCheck( (POKEMON_PARAM*)trData->postData.data ) 
		&&  PokeParty_GetPokeCount(wk->param->myparty) == 6){
		return POKEMON_NOT_FULL_BUT_MAIL_NORECV;
	}

	OS_Printf("boxnum = %d, temochi = %d\n", wk->boxPokeNum, PokeParty_GetPokeCount(wk->param->myparty));
	// とにかくてもちもボックスも空きがない
	if(wk->boxPokeNum == BOX_MAX_NUM && PokeParty_GetPokeCount(wk->param->myparty) == 6){
		return POKEMON_ALL_FULL;
	}

	// OK
	return POKEMON_RECV_OK;
}


//------------------------------------------------------------------
/**
 * @brief   セーブシーケンス後に移動する先を予約する
 *
 * @param   nextSeq1st		セーブ前半終了後に遷移するシーケンス
 * @param   nextSeq2nd		セーブ後半終了後に遷移するシーケンス
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetSaveNextSequence( WORLDTRADE_WORK *wk, int nextSeq1st, int nextSeq2nd )
{
	wk->saveNextSeq1st = nextSeq1st;
	wk->saveNextSeq2nd = nextSeq2nd;
	
}

