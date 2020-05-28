//============================================================================================
/**
 * @file	worldtrade_title.c
 * @bfief	世界交換タイトル画面処理
 * @author	Akito Mori
 * @date	06.04.16
 */
//============================================================================================
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
#include "savedata/wifilist.h"
#include "savedata/zukanwork.h"

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "msgdata/msg_wifi_lobby.h"
#include "msgdata/msg_wifi_gtc.h"


#include "worldtrade.naix"			// グラフィックアーカイブ定義

#define SEVERNO_MESSAGE_WAIT	( 45 )

//============================================================================================
//	プロトタイプ宣言
//============================================================================================
/*** 関数プロトタイプ ***/
static void BgInit( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( WORLDTRADE_WORK * wk );
static void SetCellActor(WORLDTRADE_WORK *wk);
static void DelCellActor( WORLDTRADE_WORK *wk );
static void BmpWinInit( WORLDTRADE_WORK *wk );
static void BmpWinDelete( WORLDTRADE_WORK *wk );
static void InitWork( WORLDTRADE_WORK *wk );
static void FreeWork( WORLDTRADE_WORK *wk );
static int SubSeq_Opening( WORLDTRADE_WORK *wk);
static int SubSeq_OpeningMessage( WORLDTRADE_WORK *wk );
static int SubSeq_OpeningFade( WORLDTRADE_WORK *wk );
static int SubSeq_OpeningFadeWait( WORLDTRADE_WORK *wk );
static int SubSeq_OpeningWait( WORLDTRADE_WORK *wk);
static int SubSeq_Start( WORLDTRADE_WORK *wk);
static int SubSeq_Main( WORLDTRADE_WORK *wk);
static int SubSeq_End( WORLDTRADE_WORK *wk);
static int SubSeq_YesNo( WORLDTRADE_WORK *wk);
static int SubSeq_YesNoSelect( WORLDTRADE_WORK *wk);
static int SubSeq_MessageWait( WORLDTRADE_WORK *wk );
static int SubSeq_Message1MinWait( WORLDTRADE_WORK *wk );
static int SubSeq_EndDemo( WORLDTRADE_WORK *wk );
static int SubSeq_EndDemoWait( WORLDTRADE_WORK *wk );

static void TitleMenuPrint( WORLDTRADE_WORK *wk );
static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat );
static void SubSeq_TalkPrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat );
static void DemoBgSet( WORLDTRADE_WORK *wk );


enum{
	SUBSEQ_OPENING=0,
	SUBSEQ_OPENING_MESSAGE,
	SUBSEQ_OPENING_FADE,
	SUBSEQ_OPENING_FADE_WAIT,
	SUBSEQ_OPENING_WAIT,
	SUBSEQ_START,
	SUBSEQ_MAIN,
	SUBSEQ_END_DEMO,
	SUBSEQ_END_DEMO_WAIT,
	SUBSEQ_END,
	SUBSEQ_MES_WAIT,
	SUBSEQ_MES_1MIN_WAIT,
	SUBSEQ_YESNO,
	SUBSEQ_YESNO_SELECT,
};

static int (*Functable[])( WORLDTRADE_WORK *wk ) = {
	SubSeq_Opening,
	SubSeq_OpeningMessage,
	SubSeq_OpeningFade,
	SubSeq_OpeningFadeWait,
	SubSeq_OpeningWait,
	SubSeq_Start,			// SUBSEQ_START=0,
	SubSeq_Main,             // SUBSEQ_MAIN,
	SubSeq_EndDemo,
	SubSeq_EndDemoWait,
	SubSeq_End,              // SUBSEQ_END,
	SubSeq_MessageWait,      // SUBSEQ_MES_WAIT
	SubSeq_Message1MinWait,  // SUBSEQ_MES_1MIN_WAIT
	SubSeq_YesNo,			// SUBSEQ_YESNO
	SubSeq_YesNoSelect,		// SUBSEQ_YESNO_SELECT
	

};

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
int WorldTrade_Title_Init(WORLDTRADE_WORK *wk, int seq)
{
	// ワーク初期化
	InitWork( wk );
	
	
	// BG設定
	BgInit( wk->bgl );

	// BGグラフィック転送
	BgGraphicSet( wk );

	// BMPWIN確保
	BmpWinInit( wk );

	SetCellActor(wk);

	// 通信状態を確認してアイコンの表示を変える
    WorldTrade_WifiIconAdd( wk );

	// メニューの項目を描画
	TitleMenuPrint( wk );

	// サウンドデータロード(フィールド)
	Snd_DataSetByScene( SND_SCENE_FIELD, SEQ_BLD_BLD_GTC, 1 );

	if(wk->OpeningFlag==0){
		// 主人公登場デモ用の上画面設定
		DemoBgSet( wk );


		// 最初の１回目
		// ワイプフェード開始（サブ画面だけ）
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_title.c [159] MS ********************\n" );
#endif

		wk->subprocess_seq = SUBSEQ_OPENING;
		wk->OpeningFlag     = 1;

		// 下画面に主人公を登場させる
		WorldTrade_HeroDemo( wk, MyStatus_GetMySex(wk->param->mystatus) );
	
	}else{
		// ２回目以降
		// ワイプフェード開始（両画面）
		if( wk->sub_out_flg == 1 ){
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
			OS_Printf( "******************** worldtrade_title.c [171] MS ********************\n" );
#endif
		}else{
			WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
			OS_Printf( "******************** worldtrade_title.c [175] M ********************\n" );
#endif
		}
		wk->subprocess_seq = SUBSEQ_START;
	}
	wk->sub_out_flg = 0;
	OS_TPrintf("opening flag = %d\n", wk->OpeningFlag);
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
int WorldTrade_Title_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret;
	
	// 通信状態を確認してアイコンの表示を変える
    WirelessIconEasy_SetLevel(WorldTrade_WifiLinkLevel());

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
int WorldTrade_Title_End(WORLDTRADE_WORK *wk, int seq)
{
	WirelessIconEasyEnd();

	DelCellActor(wk);

	FreeWork( wk );
	
	BmpWinDelete( wk );
	
	BgExit( wk->bgl );
	
	WorldTrade_SubProcessUpdate( wk );
	
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

	// メイン画面メニュー面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	// メイン画面背景面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
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


	// サブ画面背景BG1( この面は256色 )
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
//		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_S );
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


//------------------------------------------------------------------
/**
 * @brief   主人公登場デモ時は上画面はOBJ以外OFFにする
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DemoBgSet( WORLDTRADE_WORK *wk )
{
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_BG0, VISIBLE_OFF );	//メイン画面OBJ面ＯＮ
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_BG1, VISIBLE_OFF );	//メイン画面OBJ面ＯＮ
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_BG2, VISIBLE_OFF );	//メイン画面OBJ面ＯＮ
	
	CLACT_SetDrawFlag( wk->CursorActWork, 0 );
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
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_title_nclr, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_WORLDTRADE);


	
	// 会話フォントパレット転送
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );
   //	TalkFontPaletteLoad( PALTYPE_SUB_BG,  WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );


	// 会話ウインドウグラフィック転送
	
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MESFRAME_CHR, 
						WORLDTRADE_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_WORLDTRADE );


	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MENUFRAME_CHR,
						WORLDTRADE_MENUFRAME_PAL, 0, HEAPID_WORLDTRADE );



	// メイン画面BG1キャラ転送
	ArcUtil_BgCharSet( ARC_WORLDTRADE_GRA, NARC_worldtrade_title_lz_ncgr, bgl, GF_BGL_FRAME1_M, 0, 16*6*0x20, 1, HEAPID_WORLDTRADE);


	// メイン画面BG1スクリーン転送
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_title_menu_lz_nscr, bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);



	// メイン画面BG2スクリーン転送
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_title_base_lz_nscr, bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);


	// 下画面256色背景転送
	WorldTrade_SubLcdBgGraphicSet( wk );



}


static const u16 CursorPosTbl[][2]={
	{50,96-5*8},
	{50,96},
	{50,96+5*8},
};

//------------------------------------------------------------------
/**
 * セルアクター登録
 *
 * @param   wk			WORLDTRADE_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(WORLDTRADE_WORK *wk)
{
	//登録情報格納
	CLACT_ADD add;
	WorldTrade_MakeCLACT( &add,  wk, &wk->clActHeader_main, NNS_G2D_VRAM_TYPE_2DMAIN );

	add.mat.x = FX32_ONE *   CursorPosTbl[wk->TitleCursorPos][0];
	add.mat.y = FX32_ONE *   CursorPosTbl[wk->TitleCursorPos][1];
	wk->CursorActWork = CLACT_Add(&add);
	CLACT_SetAnmFlag(wk->CursorActWork,1);
	CLACT_AnmChg( wk->CursorActWork, 1 );
	


	
}

//------------------------------------------------------------------
/**
 * $brief   表示セルアクターの解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DelCellActor( WORLDTRADE_WORK *wk )
{
	CLACT_Delete(wk->CursorActWork);
}

#define MENU_TEXT_X		(  9 )
#define MENU_TEXT_Y		(  6 )
#define MENU_TEXT_SX	( 15 )
#define MENU_TEXT_SY	(  2 )

#define WT_MENU_MAX_NUM	(  3 )

#define MENU_MESSAGE_OFFSET    ( 16*6+1 )	// これだけBG1面なので

#define TITLE_MESSAGE_OFFSET   ( WORLDTRADE_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define LINE_MESSAGE_OFFSET    ( TITLE_MESSAGE_OFFSET     + TITLE_TEXT_SX*TITLE_TEXT_SY )
#define TALK_MESSAGE_OFFSET    ( LINE_MESSAGE_OFFSET      + LINE_TEXT_SX*LINE_TEXT_SY )
#define YESNO_OFFSET 		   ( TALK_MESSAGE_OFFSET      + TALK_WIN_SX*TALK_WIN_SY )



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

	// BG0面BMPWINタイトルウインドウ確保・描画
	
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME0_M,
	TITLE_TEXT_X, TITLE_TEXT_Y, TITLE_TEXT_SX, TITLE_TEXT_SY, WORLDTRADE_TALKFONT_PAL,  TITLE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x0000 );
	
	// POKMON GLOBAL TRADING SYSTEM
	GF_STR_PrintColor(	&wk->TitleWin, FONT_TALK, wk->TitleString, 
				0, 2, MSG_ALLPUT, 
				GF_PRINTCOLOR_MAKE(15,4,0),NULL);

	// BG0面BMPWINメニューテキストウインドウ確保・描画
	{
		int i;
		for(i=0;i<WT_MENU_MAX_NUM;i++){
			GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[i], GF_BGL_FRAME1_M,
			MENU_TEXT_X, MENU_TEXT_Y+i*5, MENU_TEXT_SX, MENU_TEXT_SY, WORLDTRADE_TALKFONT_PAL,  
			MENU_MESSAGE_OFFSET + (MENU_TEXT_SX*MENU_TEXT_SY)*i );
			GF_BGL_BmpWinDataFill( &wk->MenuWin[i], 0x0000 );
		}
	}
	
	// 1行会話ウインドウ
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		LINE_TEXT_X, LINE_TEXT_Y, LINE_TEXT_SX, LINE_TEXT_SY, 
		WORLDTRADE_TALKFONT_PAL,  LINE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0f0f );


	// 通常会話ウインドウ
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TalkWin, GF_BGL_FRAME0_M,
		TALK_WIN_X, TALK_WIN_Y, TALK_WIN_SX, TALK_WIN_SY, 
		WORLDTRADE_TALKFONT_PAL,  TALK_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->TalkWin, 0x0f0f );


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
	int i;

	GF_BGL_BmpWinDel( &wk->TalkWin );
	GF_BGL_BmpWinDel( &wk->MsgWin  );

	for(i=0;i<WT_MENU_MAX_NUM;i++){
		GF_BGL_BmpWinDel( &wk->MenuWin[i] );
	}

	GF_BGL_BmpWinDel( &wk->TitleWin );


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
	wk->TalkString  = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WORLDTRADE );

	// POKeMON GLOBAL TRADING SYSTEM
	wk->TitleString = MSGMAN_AllocString( wk->MsgManager, msg_gtc_02_001 );

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
	STRBUF_Delete( wk->TitleString ); 

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
 * $brief   最初に世界交換メニュー画面に来たとき
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_Opening( WORLDTRADE_WORK *wk)
{
	// 主人公降りてくるデモが終わるのを待つ
	if(wk->demo_end){

		GF_Disp_GX_VisibleControl(  GX_PLANEMASK_BG0, VISIBLE_OFF );	//メイン画面OBJ面ＯＮ
		GF_Disp_GX_VisibleControl(  GX_PLANEMASK_BG1, VISIBLE_OFF );	//メイン画面OBJ面ＯＮ
		GF_Disp_GX_VisibleControl(  GX_PLANEMASK_BG2, VISIBLE_OFF );	//メイン画面OBJ面ＯＮ
//		GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_OFF );	//メイン画面OBJ面ＯＮ
		// 終わったらサーバーチェックへ
		WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_SERVER_CHECK );
		wk->sub_returnprocess = WORLDTRADE_TITLE;
		wk->subprocess_seq  = SUBSEQ_END;
	}

	return SEQ_MAIN;

}

//------------------------------------------------------------------
/**
 * @brief   ???
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_OpeningMessage( WORLDTRADE_WORK *wk )
{
//	SubSeq_MessagePrint( wk, msg_gtc_01_001, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_OPENING_FADE );
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   上画面フェードイン
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_OpeningFade( WORLDTRADE_WORK *wk )
{
	WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_title.c [654] M ********************\n" );
#endif
	wk->subprocess_seq = SUBSEQ_OPENING_FADE_WAIT;
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   上画面フェード待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_OpeningFadeWait( WORLDTRADE_WORK *wk )
{
	if(WIPE_SYS_EndCheck()){
		wk->subprocess_seq = SUBSEQ_START;
	}
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   フェード待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_OpeningWait( WORLDTRADE_WORK *wk)
{
	if(WIPE_SYS_EndCheck()){
		wk->subprocess_seq = SUBSEQ_START;
	}
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   サブプロセスシーケンススタート処理
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_Start( WORLDTRADE_WORK *wk)
{
	// おさがしですか？おあずけですか？
	SubSeq_MessagePrint( wk, msg_gtc_01_005, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );
	CLACT_SetAnmFlag(wk->CursorActWork,1);
	WorldTrade_BoxPokeNumGetStart( wk );

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
static int SubSeq_Main( WORLDTRADE_WORK *wk)
{
	if(sys.trg & PAD_BUTTON_B){
			SubSeq_TalkPrint( wk, msg_gtc_01_008, WorldTrade_GetTalkSpeed(wk), 0, 0x0f0f );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_YESNO );
			CLACT_SetAnmFlag(wk->CursorActWork,0);
	}else if(sys.trg & PAD_BUTTON_A){
		switch(wk->TitleCursorPos){
		// あずけるか？ようすをみるか？
		case 0:		
			if(wk->DepositFlag==0){
				// あずける
				WorldTrade_SubProcessChange( wk, WORLDTRADE_MYBOX, MODE_DEPOSIT_SELECT );
				wk->subprocess_seq  = SUBSEQ_END;
				Snd_SePlay(WORLDTRADE_DECIDE_SE);
			}else{
				// ようすをみる
				if(wk->serverWaitTime==0){
					WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_SERVER_CHECK );
					wk->sub_returnprocess = WORLDTRADE_MYPOKE;
					wk->subprocess_seq    = SUBSEQ_END;
					wk->serverWaitTime    = SEVER_RETRY_WAIT;
					Snd_SePlay(WORLDTRADE_DECIDE_SE);
				}else{
					// 待ち時間が過ぎないと再度ようすを見に行くことができない
#ifdef PM_DEBUG
					if(sys.cont&PAD_BUTTON_L){
						WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_SERVER_CHECK );
						wk->sub_returnprocess = WORLDTRADE_MYPOKE;
						wk->subprocess_seq    = SUBSEQ_END;
						wk->serverWaitTime    = SEVER_RETRY_WAIT;
						Snd_SePlay(WORLDTRADE_DECIDE_SE);
					}else{
						CLACT_SetAnmFlag(wk->CursorActWork,0);
						SubSeq_MessagePrint( wk, msg_gtc_01_035, 1, 0, 0x0f0f );
						WorldTrade_SetNextSeq( wk, SUBSEQ_MES_1MIN_WAIT, SUBSEQ_START );
						Snd_SePlay(SE_GTC_NG);
						wk->wait = 0;
					}
#else
					CLACT_SetAnmFlag(wk->CursorActWork,0);
					SubSeq_MessagePrint( wk, msg_gtc_01_035, 1, 0, 0x0f0f );
					WorldTrade_SetNextSeq( wk, SUBSEQ_MES_1MIN_WAIT, SUBSEQ_START );
					Snd_SePlay(SE_GTC_NG);
					wk->wait = 0;
#endif
				}
			}
			break;

		// ポケモンを探す
		case 1:
			 WorldTrade_SubProcessChange( wk, WORLDTRADE_SEARCH, 0 );
			wk->subprocess_seq  = SUBSEQ_END;
			Snd_SePlay(WORLDTRADE_DECIDE_SE);
			break;

		// しゅうりょうする
		case 2:
			SubSeq_TalkPrint( wk, msg_gtc_01_008, WorldTrade_GetTalkSpeed(wk), 0, 0x0f0f );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_YESNO );
			CLACT_SetAnmFlag(wk->CursorActWork,0);
			Snd_SePlay(WORLDTRADE_DECIDE_SE);
			break;
		}
	}else if(sys.trg & PAD_KEY_UP){
		if(wk->TitleCursorPos!=0){
			wk->TitleCursorPos--;
			Snd_SePlay(WORLDTRADE_MOVE_SE);
			WorldTrade_ActPos(wk->CursorActWork, 
				CursorPosTbl[wk->TitleCursorPos][0],
				CursorPosTbl[wk->TitleCursorPos][1]);
		}
	}else if(sys.trg & PAD_KEY_DOWN){
		if(wk->TitleCursorPos<2){
			wk->TitleCursorPos++;
			Snd_SePlay(WORLDTRADE_MOVE_SE);
			WorldTrade_ActPos(wk->CursorActWork, 
				CursorPosTbl[wk->TitleCursorPos][0],
				CursorPosTbl[wk->TitleCursorPos][1]);
		}
	}

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   主人公さよならデモ開始
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_EndDemo( WORLDTRADE_WORK *wk )
{
	
	WorldTrade_ReturnHeroDemo( wk, MyStatus_GetMySex(wk->param->mystatus) );
	wk->subprocess_seq = SUBSEQ_END_DEMO_WAIT;
	wk->demo_end       = 0;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   主人公さよならデモ待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_EndDemoWait( WORLDTRADE_WORK *wk )
{
	if(wk->demo_end){
		wk->subprocess_seq = SUBSEQ_END;
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
static int SubSeq_End( WORLDTRADE_WORK *wk)
{
	// 接続画面だったら、上下画面でフェード
	if(wk->sub_nextprocess==WORLDTRADE_ENTER){
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_title.c [846] MS ********************\n" );
#endif
	}else{
		// 続きの画面にいく場合は上画面だけフェード
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_title.c [850] M ********************\n" );
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
static int SubSeq_YesNo( WORLDTRADE_WORK *wk)
{
	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY2, YESNO_OFFSET );
	wk->subprocess_seq = SUBSEQ_YESNO_SELECT;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * $brief   はい・いいえ選択
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_YesNoSelect( WORLDTRADE_WORK *wk)
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WORLDTRADE );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// もういっかいトライ
			BmpTalkWinClear( &wk->TalkWin, WINDOW_TRANS_OFF );
			GF_BGL_BmpWinOff( &wk->TalkWin );
			CLACT_SetAnmFlag(wk->CursorActWork,1);
			wk->subprocess_seq = SUBSEQ_START;
		}else{
			// 主人公帰るデモ
			BmpTalkWinClear( &wk->TalkWin, WINDOW_TRANS_OFF );
			GF_BGL_BmpWinOff( &wk->TalkWin );
			WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
			wk->subprocess_seq  = SUBSEQ_END_DEMO;
			
		}
	}

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
static int SubSeq_MessageWait( WORLDTRADE_WORK *wk )
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		wk->subprocess_seq = wk->subprocess_nextseq;
	}
	return SEQ_MAIN;

}

//------------------------------------------------------------------
/**
 * @brief   １秒待って次のシーケンスへ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_Message1MinWait( WORLDTRADE_WORK *wk )
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		wk->wait++;
		if(wk->wait > SEVERNO_MESSAGE_WAIT){
			wk->wait = 0;
			wk->subprocess_seq = wk->subprocess_nextseq;
		}
	}
	return SEQ_MAIN;
	
}























static const int menu_str_table[][3]={
	{
		msg_gtc_05_001,
		msg_gtc_02_003,
		msg_gtc_02_004,
	},
	{
		msg_gtc_02_002,
		msg_gtc_02_003,
		msg_gtc_02_004,
	},
};

//------------------------------------------------------------------
/**
 * @brief   ３つのメニュー項目を描画する
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TitleMenuPrint( WORLDTRADE_WORK *wk )
{
	int i;
//	int menu = WorldTradeData_GetFlag( wk->param->worldtrade_data );
	int menu = wk->DepositFlag;

	// ポケモンを預けているかどうかで、メニューの項目が変わる
	for(i=0;i<3;i++){
		WorldTrade_BmpWinPrint( &wk->MenuWin[i], wk->MsgManager, menu_str_table[menu][i], 0x0f0f );
		GF_BGL_BmpWinOn( &wk->MenuWin[i] );
	}
}





//------------------------------------------------------------------
/**
 * $brief   会話ウインドウ表示
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat )
{
	// 文字列取得
	STRBUF *tempbuf;
	
	MSGMAN_GetString(  wk->MsgManager, msgno, wk->TalkString );

	// 会話ウインドウ枠描画
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, WORLDTRADE_MESFRAME_CHR, WORLDTRADE_MESFRAME_PAL );

	// 文字列描画開始
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);


}

//------------------------------------------------------------------
/**
 * $brief   会話ウインドウ表示
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SubSeq_TalkPrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat )
{
	// 文字列取得
	STRBUF *tempbuf;
	
	MSGMAN_GetString(  wk->MsgManager, msgno, wk->TalkString );

	// 会話ウインドウ枠描画
	GF_BGL_BmpWinDataFill( &wk->TalkWin,  0x0f0f );
	BmpTalkWinWrite( &wk->TalkWin, WINDOW_TRANS_ON, WORLDTRADE_MESFRAME_CHR, WORLDTRADE_MESFRAME_PAL );

	// 文字列描画開始
	wk->MsgIndex = GF_STR_PrintSimple( &wk->TalkWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);


}

//------------------------------------------------------------------
/**
 * $brief   BMPWINに文字列描画
 *
 * @param   win		
 * @param   msgman		
 * @param   msgno		
 * @param   dat		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WorldTrade_BmpWinPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int msgno, u16 dat )
{
	// 文字列取得
	STRBUF *tempbuf;
	
	tempbuf = MSGMAN_AllocString(  msgman, msgno );

	// 会話ウインドウ枠描画
	GF_BGL_BmpWinDataFill( win,  dat );

	// 文字列描画開始
	GF_STR_PrintSimple( win, FONT_TALK, tempbuf, 0, 0, MSG_ALLPUT, NULL);

	STRBUF_Delete(tempbuf);
}


//==============================================================================
/**
 * @brief   下画面用「世界交換ルーム」256色グラフィック転送
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SubLcdBgGraphicSet( WORLDTRADE_WORK *wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// 
	// 下画面ＢＧパレット転送
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_traderoom_nclr, PALTYPE_SUB_BG,  0, 16*16*2,  HEAPID_WORLDTRADE);

	// サブ画面BG1キャラ転送
	ArcUtil_BgCharSet( ARC_WORLDTRADE_GRA, NARC_worldtrade_traderoom_lz_ncgr, bgl, GF_BGL_FRAME1_S, 0, 32*21*0x40, 1, HEAPID_WORLDTRADE);

	// サブ画面BG1スクリーン転送
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_traderoom_lz_nscr, bgl, GF_BGL_FRAME1_S, 0, 32*24*2, 1, HEAPID_WORLDTRADE);

}
