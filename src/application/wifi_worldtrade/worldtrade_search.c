//============================================================================================
/**
 * @file	worldtrade_search.c
 * @bfief	世界交換ポケモン検索画面処理
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
#include "communication/communication.h"

#include "msgdata/msg_wifi_gtc.h"



#include "worldtrade.naix"			// グラフィックアーカイブ定義
#include "../zukanlist/zkn_data/zukan_data.naix"



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
static int  SubSeq_Start( WORLDTRADE_WORK *wk);
static int  SubSeq_Main( WORLDTRADE_WORK *wk);
static int  SubSeq_SearchCheck( WORLDTRADE_WORK *wk );
static int  SubSeq_ServerQuery(WORLDTRADE_WORK *wk );
static int  SubSeq_ServerResult( WORLDTRADE_WORK *wk );
static int  SubSeq_SearchResultMessage( WORLDTRADE_WORK *wk );
static int  CursorPosGet( WORLDTRADE_WORK *wk );
static void CursorMove( WORLDTRADE_WORK *wk );
static int  SubSeq_End( WORLDTRADE_WORK *wk);
static int 	SubSeq_InputPokenameMessage( WORLDTRADE_WORK *wk);
static int 	SUBSEQ_HeadwordSelectList( WORLDTRADE_WORK *wk);
static int  SUBSEQ_HeadwordSelectWait( WORLDTRADE_WORK *wk);
static int  SUBSEQ_PokenameSelectList( WORLDTRADE_WORK *wk);
static int  SUBSEQ_PokenameSelectWait( WORLDTRADE_WORK *wk);
static int  SUBSEQ_SexSelectMes( WORLDTRADE_WORK *wk);
static int  SUBSEQ_SexSelectList( WORLDTRADE_WORK *wk);
static int  SUBSEQ_SexSelectWait( WORLDTRADE_WORK *wk);
static int  SUBSEQ_LevelSelectMes( WORLDTRADE_WORK *wk);
static int  SUBSEQ_LevelSelectList( WORLDTRADE_WORK *wk);
static int  SUBSEQ_LevelSelectWait( WORLDTRADE_WORK *wk);
static int  SubSeq_YesNo( WORLDTRADE_WORK *wk);
static int  SubSeq_YesNoSelect( WORLDTRADE_WORK *wk);
static int  SubSeq_PageChange( WORLDTRADE_WORK *wk);
static int  SubSeq_SearchErrorMessage(WORLDTRADE_WORK *wk);
static int  SubSeq_MessageWait( WORLDTRADE_WORK *wk );
static int  SubSeq_SearchResultMessageWait( WORLDTRADE_WORK *wk );
static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat );
static int  SubSeq_ServerQueryFailure( WORLDTRADE_WORK *wk );
static int SubSeq_SearchErrorDisconnectMessage1( WORLDTRADE_WORK *wk );
static int SubSeq_SearchErrorDisconnectMessage2( WORLDTRADE_WORK *wk );
static int SubSeq_SearchErrorDisconnectMessage3( WORLDTRADE_WORK *wk );


static void WantLabelPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager );
static int LastTradeDateCheck( WORLDTRADE_WORK *wk );
static int DpwSerachCompare( const Dpw_Tr_PokemonSearchData *s1, const Dpw_Tr_PokemonSearchData *s2 );
static int SubSeq_MessageWait1Min( WORLDTRADE_WORK *wk );


enum{
	SUBSEQ_START=0,
	SUBSEQ_MAIN,
	SUBSEQ_END,

	SUBSEQ_INPUT_POKENAME_MES,
	SUBSEQ_HEADWORD_SELECT_LIST,
    SUBSEQ_HEADWORD_SELECT_WAIT,
    SUBSEQ_POKENAME_SELECT_LIST,
    SUBSEQ_POKENAME_SELECT_WAIT,
	SUBSEQ_SEX_SELECT_MES,
	SUBSEQ_SEX_SELECT_LIST,
	SUBSEQ_SEX_SELECT_WAIT,
	SUBSEQ_LEVEL_SELECT_MES,
	SUBSEQ_LEVEL_SELECT_LIST,
	SUBSEQ_LEVEL_SELECT_WAIT,

	SUBSEQ_SEARCH_CHECK,
	SUBSEQ_SERVER_QUERY,
	SUBSEQ_SERVER_RESULT,
	SUBSEQ_SEARCH_RESULT_MESSAGE,
	SUBSEQ_SEARCH_RESULT_MESSAGE_WAIT,

	SUBSEQ_SERVER_QUERY_FAILURE,


	SUBSEQ_MES_WAIT,
	SUBSEQ_MES_WAIT_1MIN,
	SUBSEQ_YESNO,
	SUBSEQ_YESNO_SELECT,
	SUBSEQ_PAGE_CHANGE,
	SUBSEQ_SEARCH_ERROR_MES,

	SUBSEQ_SEARCH_ERROR_DICONNECT_MES1,
	SUBSEQ_SEARCH_ERROR_DICONNECT_MES2,
};

static int (*Functable[])( WORLDTRADE_WORK *wk ) = {
	SubSeq_Start,			// SUBSEQ_START=0,
	SubSeq_Main,             // SUBSEQ_MAIN,
	SubSeq_End,              // SUBSEQ_END,

	SubSeq_InputPokenameMessage,
	SUBSEQ_HeadwordSelectList,
    SUBSEQ_HeadwordSelectWait,
    SUBSEQ_PokenameSelectList,
    SUBSEQ_PokenameSelectWait,
	SUBSEQ_SexSelectMes,
	SUBSEQ_SexSelectList,
	SUBSEQ_SexSelectWait,
	SUBSEQ_LevelSelectMes,
	SUBSEQ_LevelSelectList,
	SUBSEQ_LevelSelectWait,

	SubSeq_SearchCheck,		// SUBSEQ_SEARCH_CHECK,
	SubSeq_ServerQuery,
	SubSeq_ServerResult,
	SubSeq_SearchResultMessage,
	SubSeq_SearchResultMessageWait,

	SubSeq_ServerQueryFailure,


	SubSeq_MessageWait,     // SUBSEQ_MES_WAIT
	SubSeq_MessageWait1Min, // SUBSEQ_MES_WAIT_1MIN
	SubSeq_YesNo,			// SUBSEQ_YESNO
	SubSeq_YesNoSelect,		// SUBSEQ_YESNO_SELECT
	SubSeq_PageChange,		// SUBSEQ_PAGE_CHANGE,
	SubSeq_SearchErrorMessage,

	SubSeq_SearchErrorDisconnectMessage1,	// 	SUBSEQ_SEARCH_ERROR_DICONNECT_MES1,
	SubSeq_SearchErrorDisconnectMessage2,	// 	SUBSEQ_SEARCH_ERROR_DICONNECT_MES2,
};

#define INFO_TEXT_WORD_NUM	(10*2)


static u16 CursorPos[][2]={
	{ 20,  39 },
	{ 20,  79 },
	{ 20, 119 },
	{140,  64 },
	{140, 120 },
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
int WorldTrade_Search_Init(WORLDTRADE_WORK *wk, int seq)
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


	WantLabelPrint( &wk->InfoWin[0], wk->MsgManager );

		// 名前決定
		WorldTrade_PokeNamePrint( &wk->InfoWin[1], wk->MonsNameManager, 
			wk->Search.characterNo, 2, 0, GF_PRINTCOLOR_MAKE(1,2,0)  );

		// 性別決定
		WorldTrade_SexPrint( &wk->InfoWin[3], wk->MsgManager, 
			wk->Search.gender, 1, 0, 2, GF_PRINTCOLOR_MAKE(1,2,0)  );

		// レベル指定決定
		WorldTrade_WantLevelPrint( &wk->InfoWin[5], wk->MsgManager, 
			WorldTrade_LevelTermGet(wk->Search.level_min,wk->Search.level_max),
			2, 0, GF_PRINTCOLOR_MAKE(1,2,0) );

	
	// ２回目以降
	// ワイプフェード開始（両画面）
	WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_search.c [218] M ********************\n" );
#endif
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
int WorldTrade_Search_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret;
	
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
int WorldTrade_Search_End(WORLDTRADE_WORK *wk, int seq)
{
	DelCellActor( wk );
	
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
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	// メイン画面第２テキスト面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}


/*
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
	}

*/

	GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, HEAPID_WORLDTRADE );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_WORLDTRADE );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_WORLDTRADE );

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

	// 上下画面ＢＧパレット転送
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_search_nclr, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_WORLDTRADE);
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_traderoom_nclr, PALTYPE_SUB_BG,  0, 16*8*2,  HEAPID_WORLDTRADE);
	
	// 会話フォントパレット転送
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );
  // 	TalkFontPaletteLoad( PALTYPE_SUB_BG,  WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );

	// 会話ウインドウグラフィック転送
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MESFRAME_CHR, 
						WORLDTRADE_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_WORLDTRADE );

	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MENUFRAME_CHR,
						WORLDTRADE_MENUFRAME_PAL, 0, HEAPID_WORLDTRADE );



	// メイン画面BG1キャラ転送
	ArcUtil_BgCharSet( ARC_WORLDTRADE_GRA, NARC_worldtrade_search_lz_ncgr, bgl, GF_BGL_FRAME1_M, 0, 16*5*0x20, 1, HEAPID_WORLDTRADE);

	// メイン画面BG1スクリーン転送
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_search_lz_nscr, bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);


	// サブ画面BG1キャラ転送
	//ArcUtil_BgCharSet( ARC_WORLDTRADE_GRA, NARC_worldtrade_traderoom_lz_ncgr, bgl, GF_BGL_FRAME1_S, 0, 32*21*0x40, 1, HEAPID_WORLDTRADE);

	// サブ画面BG1スクリーン転送
	//ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_traderoom_lz_nscr, bgl, GF_BGL_FRAME1_S, 0, 32*24*2, 1, HEAPID_WORLDTRADE);



}


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

	add.mat.x = FX32_ONE;
	add.mat.y = FX32_ONE;
	wk->CursorActWork = CLACT_Add(&add);
	CLACT_SetAnmFlag( wk->CursorActWork, 1 );
	CLACT_AnmChg( wk->CursorActWork, 0 );
	
	WirelessIconEasy();
}

//------------------------------------------------------------------
/**
 * @brief   
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


// 「ポケモン」・名前・「せいべつ」・性別・「レベル」・レベル
#define INFORMATION_STR_X	(  3 )
#define INFORMATION_STR_X2	(  2 )
#define INFORMATION1_STR_Y	(  4 )
#define INFORMATION2_STR_Y	(  6 )
#define INFORMATION3_STR_Y	(  9 )
#define INFORMATION4_STR_Y	( 11 )
#define INFORMATION5_STR_Y	( 14 )
#define INFORMATION6_STR_Y	( 16 )
#define INFORMATION_STR_SX	( 11 )
#define INFORMATION_STR_SY	(  2 )

#define BUTTON_STR_X		( 21 )
#define BUTTON1_STR_Y		(  7 )
#define BUTTON2_STR_Y		( 14 )
#define BUTTON_STR_SX		(  8 )
#define BUTTON_STR_SY		(  2 )

#define TITLE_MESSAGE_OFFSET   ( WORLDTRADE_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define LINE_MESSAGE_OFFSET    ( TITLE_MESSAGE_OFFSET     + TITLE_TEXT_SX*TITLE_TEXT_SY )
#define INFOMATION_STR_OFFSET  ( LINE_MESSAGE_OFFSET      + LINE_TEXT_SX*LINE_TEXT_SY )
#define BUTTON_STR_OFFSET	   ( INFOMATION_STR_OFFSET    + INFORMATION_STR_SX*INFORMATION_STR_SY*6)
#define SELECT_MENU1_OFFSET    ( BUTTON_STR_OFFSET        + BUTTON_STR_SX*BUTTON_STR_SY*2 )
#define SELECT_MENU2_OFFSET    ( SELECT_MENU1_OFFSET      + SELECT_MENU1_SX*SELECT_MENU1_SY )
#define SELECT_MENU3_OFFSET    ( SELECT_MENU1_OFFSET )
#define SELECT_MENU4_OFFSET    ( SELECT_MENU1_OFFSET )
#define YESNO_OFFSET 		   ( SELECT_MENU4_OFFSET      + SELECT_MENU4_SX*SELECT_MENU4_SY )

static const u16 infomation_bmpwin_table[6][2]={
	{INFORMATION_STR_X,   INFORMATION1_STR_Y,},
	{INFORMATION_STR_X2,  INFORMATION2_STR_Y,},
	{INFORMATION_STR_X,   INFORMATION3_STR_Y,},
	{INFORMATION_STR_X2,  INFORMATION4_STR_Y,},
	{INFORMATION_STR_X,   INFORMATION5_STR_Y,},
	{INFORMATION_STR_X2,  INFORMATION6_STR_Y,},

};

static const u16 button_bmpwin_table[][2]={
	{BUTTON_STR_X,	BUTTON1_STR_Y},
	{BUTTON_STR_X,	BUTTON2_STR_Y},
};

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

	GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME0_M,
		TITLE_TEXT_X, TITLE_TEXT_Y, TITLE_TEXT_SX, TITLE_TEXT_SY, 
		WORLDTRADE_TALKFONT_PAL,  TITLE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x0000 );
	
	// 「ポケモンをさがす」描画
	WorldTrade_TalkPrint( &wk->TitleWin, wk->TitleString, 0, 1, 0, GF_PRINTCOLOR_MAKE(15,13,0) );

	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		LINE_TEXT_X, LINE_TEXT_Y, LINE_TEXT_SX, LINE_TEXT_SY, 
		WORLDTRADE_TALKFONT_PAL,  LINE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0000 );


	// BG0面BMPWIN情報ウインドウ確保
	{
		int i, offset;

		// ほしいポケモン情報x６文字列
		for(i=0;i<6;i++){
			GF_BGL_BmpWinAdd(wk->bgl, &wk->InfoWin[i], GF_BGL_FRAME0_M,
					infomation_bmpwin_table[i][0], 
					infomation_bmpwin_table[i][1], 
					INFORMATION_STR_SX, INFORMATION_STR_SY,
					WORLDTRADE_TALKFONT_PAL,  
					INFOMATION_STR_OFFSET + (INFORMATION_STR_SX*INFORMATION_STR_SY)*i );
			GF_BGL_BmpWinDataFill( &wk->InfoWin[i], 0x0000 );
		}

		// さがす・もどる
		for(i=0;i<2;i++){
			GF_BGL_BmpWinAdd(wk->bgl, &wk->InfoWin[6+i], GF_BGL_FRAME2_M,
					button_bmpwin_table[i][0], 
					button_bmpwin_table[i][1], 
					BUTTON_STR_SX,BUTTON_STR_SY,
					WORLDTRADE_TALKFONT_PAL,  BUTTON_STR_OFFSET+(BUTTON_STR_SX*BUTTON_STR_SY)*i );
			GF_BGL_BmpWinDataFill( &wk->InfoWin[6+i], 0x0000 );
		}
	}

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
	GF_BGL_BmpWinDel( &wk->TitleWin );
	{
		int i;
		for(i=0;i<8;i++){
			GF_BGL_BmpWinDel( &wk->InfoWin[i] );
		}
	}


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
	int i;

	// 文字列バッファ作成
	wk->TalkString  = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WORLDTRADE );

	// 「ポケモンをさがす」
	wk->TitleString = MSGMAN_AllocString( wk->MsgManager, msg_gtc_02_003 );


	// ポケモン名テーブル作成用のワーク確保
	wk->dw = sys_AllocMemory(HEAPID_WORLDTRADE, sizeof(DEPOSIT_WORK));
	MI_CpuClearFast(wk->dw, sizeof(DEPOSIT_WORK));

	// 図鑑ソートデータ(全国図鑑と、シンオウ図鑑の分岐が必要だとおもう）
	wk->dw->nameSortTable = WorldTrade_ZukanSortDataGet( HEAPID_WORLDTRADE, 0, &wk->dw->nameSortNum );
	wk->dw->sinouTable    = WorldTrade_SinouZukanDataGet( HEAPID_WORLDTRADE );

	// カーソル位置初期化
	WorldTrade_SelectListPosInit( &wk->selectListPos );
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
	sys_FreeMemoryEz( wk->dw->sinouTable );
	sys_FreeMemoryEz( wk->dw->nameSortTable );
	sys_FreeMemoryEz( wk->dw );

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
 * $brief   サブプロセスシーケンススタート処理
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_Start( WORLDTRADE_WORK *wk)
{
	// 
	SubSeq_MessagePrint( wk, msg_gtc_01_009, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );

	OS_Printf("monsno = %d, gender = %d, level = %d - %d\n", 
			wk->Search.characterNo,wk->Search.gender,wk->Search.level_min,wk->Search.level_max);
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
	// カーソル移動
	CursorMove(wk);

	if(sys.trg & PAD_BUTTON_DECIDE){
		int pos = CursorPosGet(wk);
		switch(pos){
		// ポケモン指定
		case 0:	
			wk->subprocess_seq = SUBSEQ_INPUT_POKENAME_MES;	
			Snd_SePlay(WORLDTRADE_DECIDE_SE);
			break;
		// 性別指定
		case 1:		
			// 既にポケモンを入力していて、そのポケモンの性別が決定しているときは
			// 入力できないようにする
			if(wk->Search.characterNo!=0){
				wk->dw->sex_selection = PokePersonalParaGet(wk->Search.characterNo,ID_PER_sex);
				if(WorldTrade_SexSelectionCheck( &wk->Search, wk->dw->sex_selection )){
					OS_Printf("性別決定？ = %d\n", wk->dw->sex_selection);
					Snd_SePlay(WORLDTRADE_DECIDE_SE);
					return SEQ_MAIN;
				}
			}
			wk->subprocess_seq = SUBSEQ_SEX_SELECT_MES;		
			Snd_SePlay(WORLDTRADE_DECIDE_SE);
			break;
		// レベル指定
		case 2:		
			wk->subprocess_seq = SUBSEQ_LEVEL_SELECT_MES;	
			Snd_SePlay(WORLDTRADE_DECIDE_SE);
			break;
		// 探す
		case 3:		
			wk->subprocess_seq = SUBSEQ_SEARCH_CHECK;		
			break;
		// もどる
		case 4:
			SubSeq_MessagePrint( wk, msg_gtc_01_016, 1, 0, 0x0f0f );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_YESNO );
			Snd_SePlay(WORLDTRADE_DECIDE_SE);
			break;
		}

	}else if(sys.trg & PAD_BUTTON_CANCEL){
		// キャンセル
		SubSeq_MessagePrint( wk, msg_gtc_01_016, 1, 0, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_YESNO );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
	}else{
		// タッチパネルチェック
		int result = WorldTrade_SubLcdObjHitCheck( wk->SearchResult );
		if(wk->SubLcdTouchOK){
			if(result>=0){
				CLACT_AnmChg( wk->SubActWork[result+1], 16+result*4 );
				wk->subprocess_seq     = SUBSEQ_END; 
				WorldTrade_SubProcessChange( wk, WORLDTRADE_PARTNER, 0 );
				wk->TouchTrainerPos = result;
				Snd_SePlay(WORLDTRADE_DECIDE_SE);
			}
		}
	
	}

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   検索できるかチェック
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SearchCheck( WORLDTRADE_WORK *wk )
{

	// ポケモンを決めていない
	if(wk->Search.characterNo==0){
		SubSeq_MessagePrint( wk, msg_gtc_01_013, 1, 0, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );
		Snd_SePlay(SE_GTC_NG);
	}else{
	// 以前の条件と違うなら

		if(DpwSerachCompare( &wk->Search, &wk->SearchBackup)){
			// 条件が変わっていないのでダメ「かわらないみたい…」
			SubSeq_MessagePrint( wk, msg_gtc_01_034, 1, 0, 0x0f0f );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );
			Snd_SePlay(SE_GTC_NG);
		}else{
			Snd_SePlay(SE_GTC_SEARCH);

			OS_TPrintf("search start\n");
			OS_Printf( "SearchData  No = %d,  gender = %d, level min= %d max = %d\n", wk->Search.characterNo, wk->Search.gender, wk->Search.level_min, wk->Search.level_max);

			// ただいま　けんさくちゅう…
			SubSeq_MessagePrint( wk, msg_gtc_01_014, 1, 0, 0x0f0f );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SERVER_QUERY );

			// 表示されている検索結果ＯＢＪがいる場合は隠す
			WorldTrade_SubLcdMatchObjHide( wk );
			
		}
		
	}
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   最終交換成立日をチェック
 *
 * @param   wk		
 *
 * @retval  int		成立日が昨日か今日なら1,違うなら0
 */
//------------------------------------------------------------------
static int LastTradeDateCheck( WORLDTRADE_WORK *wk )
{
	GF_DATE gfDate;
	RTCDate sdkDate, todayDate;
	RTCTime time;
	int diff;
	
	// セーブされている日付をSDKの日付情報に変換
	gfDate = WorldTradeData_GetLastDate( wk->param->worldtrade_data );
	GFDate2RTCDate( gfDate, &sdkDate );
	
	// 現在サーバー時刻を取得
	DWC_GetDateTime( &todayDate, &time);

	diff = RTC_ConvertDateToDay( &todayDate )-RTC_ConvertDateToDay( &sdkDate );
	if(diff>=0 && diff<3){
		OS_Printf("今日-交換最終日 = %d　なので＋２\n",diff);
		return 1;
	}

	return 0;
}

//------------------------------------------------------------------
/**
 * @brief   ポケモン検索開始
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_ServerQuery(WORLDTRADE_WORK *wk )
{
	Dpw_Tr_PokemonSearchData search;
	int  search_max = 3;				// 初期検索数は３

	// 現在サーバーにポケモンを預けているならば、最大検索数が２匹増える
	if(wk->DepositFlag){
		search_max += 2;
		OS_Printf( "預けているので+2\n");
	}
	
	if(LastTradeDateCheck(wk)){
		search_max += 2;
	}

#ifdef PM_DEBUG
	if(sys.cont & PAD_BUTTON_L){
		search_max = 7;
	}
#endif

	// 検索開始	
	Dpw_Tr_DownloadMatchDataAsync (&wk->Search, search_max, wk->DownloadPokemonData );
	wk->SearchBackup = wk->Search;
	
	OS_Printf("検索最大数 = %d\n", search_max);
	
	wk->subprocess_seq = SUBSEQ_SERVER_RESULT;
	
	// 下画面をタッチしても反応しない
	wk->SubLcdTouchOK = 0;
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   サーバー検索応答待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_ServerResult( WORLDTRADE_WORK *wk )
{
	int result;
	result=Dpw_Tr_IsAsyncEnd();
	if (result){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		case 0:		case 1:		case 2:		case 3:		case 4:		
		case 5:		case 6:		case 7:
			OS_TPrintf(" query is success!\n");

			// 検索の結果の数を保存
			wk->SearchResult   = result;

			Snd_SeStopBySeqNo( SE_GTC_SEARCH, 0 );

			// 下画面にＯＢＪを反映させる
			WorldTrade_SubLcdMatchObjAppear( wk, result, 1 );

			wk->subprocess_seq = SUBSEQ_SEARCH_RESULT_MESSAGE;
			break;
			


	// -----------------------------------------
	// 共通エラー処理
	// -----------------------------------------

		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// サーバーと通信できません→終了
			OS_TPrintf(" server full.\n");
			wk->subprocess_seq = SUBSEQ_SEARCH_ERROR_DICONNECT_MES1;
			break;
		case DPW_TR_ERROR_FATAL:			//!< 通信致命的エラー。電源の再投入が必要です
			// 即ふっとばし
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------

		// 検索結果取得失敗（「いなかった」ではない）リトライする
		case DPW_TR_ERROR_FAILURE:
		case DPW_TR_ERROR_CANCEL :
			wk->subprocess_seq = SUBSEQ_SERVER_QUERY_FAILURE;
			break;
		default:
			OS_TPrintf(" dpw result = %d.\n",result);
			break;
		}
		
	}
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   検索結果表示が必要な時は表示
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SearchResultMessage( WORLDTRADE_WORK *wk )
{
	if(wk->SearchResult==0){
		// ヒット無しだった
		SubSeq_MessagePrint( wk, msg_gtc_01_015, 1, 0, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );
		Snd_SePlay(SE_GTC_NG);
		
	}else{
		// 仕様では検索結果ありの時はメッセージ無しだったけど
		// 要望が来たので「みつかりました！」と表示
		SubSeq_MessagePrint( wk, msg_gtc_01_031, 1, 0, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SEARCH_RESULT_MESSAGE_WAIT );
		wk->wait = 0;
	}

	return SEQ_MAIN;

}

//------------------------------------------------------------------
/**
 * @brief   「みつかりました！」を1秒待つ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SearchResultMessageWait( WORLDTRADE_WORK *wk )
{
	wk->wait++;
	if(wk->wait>45){
		SubSeq_MessagePrint( wk, msg_gtc_01_033, 1, 0, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );
		wk->SubLcdTouchOK = 1;
	}
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   検索自体に失敗している（サーバーからの返事がタイムアウトした）
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_ServerQueryFailure( WORLDTRADE_WORK *wk )
{
	// 検索失敗なので、続けてもう一度同じ検索もできるようにする
	wk->SearchBackup.characterNo = 0;

	// 「ＧＴＳのかくにんにしっぱいしました」
	SubSeq_MessagePrint( wk, msg_gtc_01_039, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );
	Snd_SePlay(SE_GTC_NG);

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   検索エラー（ＧＴＳ終了）その１
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SearchErrorDisconnectMessage1( WORLDTRADE_WORK *wk )
{
	// 「ＧＴＳのかくにんにしっぱいしました」
	SubSeq_MessagePrint( wk, msg_gtc_error_004, 4, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT_1MIN, SUBSEQ_SEARCH_ERROR_DICONNECT_MES2 );
	wk->wait =0;
	Snd_SePlay(SE_GTC_NG);

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   検索エラー（ＧＴＳ終了）その２
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SearchErrorDisconnectMessage2( WORLDTRADE_WORK *wk )
{
	// うけつけにもどります
	SubSeq_MessagePrint( wk, msg_gtc_error_006_02, 4, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT_1MIN, SUBSEQ_END );
	WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
	Snd_SePlay(SE_GTC_NG);

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * @brief   カーソルの位置番号を取得
 *
 * @param   wk		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static int CursorPosGet( WORLDTRADE_WORK *wk )
{
	int pos;
	// 現在のカーソルの位置を取得
	if(wk->dw->cursorSide==0){
		pos = wk->dw->leftCursorPos;
	}else{
		pos = wk->dw->rightCursorPos+3;
	}
	return pos;
}

//------------------------------------------------------------------
/**
 * @brief   カーソル移動
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorMove( WORLDTRADE_WORK *wk )
{
	int pos ;
	if(sys.trg & PAD_KEY_UP){
		if(wk->dw->cursorSide==0){
			if(wk->dw->leftCursorPos>0){
				wk->dw->leftCursorPos--;
				Snd_SePlay(WORLDTRADE_MOVE_SE);
			}
		}else{
			if(wk->dw->rightCursorPos!=0){
				Snd_SePlay(WORLDTRADE_MOVE_SE);
			}
			wk->dw->rightCursorPos=0;
		}
		
	}else if(sys.trg & PAD_KEY_DOWN){
		if(wk->dw->cursorSide==0){
			if(wk->dw->leftCursorPos<2){
				wk->dw->leftCursorPos++;
				Snd_SePlay(WORLDTRADE_MOVE_SE);
			}
		}else{
			if(wk->dw->rightCursorPos!=1){
				Snd_SePlay(WORLDTRADE_MOVE_SE);
			}
			wk->dw->rightCursorPos=1;
		}
		
	}else if(sys.trg & PAD_KEY_RIGHT){
		if(wk->dw->cursorSide != 1){
			Snd_SePlay(WORLDTRADE_MOVE_SE);
		}
		wk->dw->cursorSide = 1;
	}else if(sys.trg & PAD_KEY_LEFT){
		if(wk->dw->cursorSide != 0){
			Snd_SePlay(WORLDTRADE_MOVE_SE);
		}
		wk->dw->cursorSide = 0;
	}


	// カーソル移動
	{
		VecFx32 mat;
		mat.x = FX32_ONE * CursorPos[CursorPosGet( wk )][0];
		mat.y = FX32_ONE * CursorPos[CursorPosGet( wk )][1];
		CLACT_SetMatrix( wk->CursorActWork, &mat );
	}
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
	WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );


#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_search.c [1076] M ********************\n" );
#endif
	wk->subprocess_seq = 0;
	
	return SEQ_FADEOUT;
}





//------------------------------------------------------------------
/**
 * @brief   ポケモンの名前を入力してください
 *
 * @param   wk		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	SubSeq_InputPokenameMessage( WORLDTRADE_WORK *wk)
{
	SubSeq_MessagePrint( wk, msg_gtc_01_010, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_HEADWORD_SELECT_LIST );

		// アイウエオ選択ウインドウ確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[0], GF_BGL_FRAME0_M,
		SELECT_MENU1_X,		SELECT_MENU1_Y,		SELECT_MENU1_SX, 		SELECT_MENU1_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU1_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MenuWin[0], 0x0000 );


	// ポケモン名選択ウインドウ確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[1], GF_BGL_FRAME0_M,
		SELECT_MENU2_X,		SELECT_MENU2_Y,		SELECT_MENU2_SX, 		SELECT_MENU2_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU2_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MenuWin[1], 0x0000 );
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   名前選択リスト準備
 *
 * @param   wk		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	SUBSEQ_HeadwordSelectList( WORLDTRADE_WORK *wk)
{
	// 頭文字選択メニュー作成
	wk->BmpListWork = WorldTrade_WordheadBmpListMake( wk, &wk->BmpMenuList, &wk->MenuWin[0], wk->MsgManager );
	wk->listpos = 0xffff;

	wk->subprocess_seq = SUBSEQ_HEADWORD_SELECT_WAIT;
	
	return SEQ_MAIN;

}

//------------------------------------------------------------------
/**
 * @brief   頭文字選択待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SUBSEQ_HeadwordSelectWait( WORLDTRADE_WORK *wk)
{
	switch(WorldTrade_BmpListMain( wk->BmpListWork, &wk->listpos )){
	case 1: case 2: case 3: case 4: case 5:	case 6: case 7: case 8: case 9: case 10:
		BmpListExit( wk->BmpListWork, &wk->dw->headwordListPos, &wk->dw->headwordPos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
		
		wk->subprocess_seq  = SUBSEQ_POKENAME_SELECT_LIST;
		break;

	// キャンセル
	case BMPMENU_CANCEL:
		BmpListExit( wk->BmpListWork, &wk->dw->headwordListPos, &wk->dw->headwordPos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		GF_BGL_BmpWinDel( &wk->MenuWin[1] );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		wk->subprocess_seq  = SUBSEQ_START;
		break;
	}
	return SEQ_MAIN;
	
}
//------------------------------------------------------------------
/**
 * @brief   ポケモン名選択開始
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SUBSEQ_PokenameSelectList( WORLDTRADE_WORK *wk)
{
	// ポケモン名リスト作成
	wk->BmpListWork = WorldTrade_PokeNameListMake( wk,
							&wk->BmpMenuList, &wk->MenuWin[1], 
							wk->MsgManager, wk->MonsNameManager,wk->dw,
							wk->param->zukanwork );
	wk->listpos = 0xffff;

	wk->subprocess_seq = SUBSEQ_POKENAME_SELECT_WAIT;

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   名前入力
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SUBSEQ_PokenameSelectWait( WORLDTRADE_WORK *wk)
{
	u32 result;
	switch((result=WorldTrade_BmpListMain( wk->BmpListWork, &wk->listpos ))){
	case BMPLIST_NULL:
		break;

	// キャンセル
	case BMPMENU_CANCEL:
		BmpListExit( wk->BmpListWork, &wk->dw->nameListPos, &wk->dw->namePos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[1], WINDOW_TRANS_ON );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
		wk->subprocess_seq  = SUBSEQ_HEADWORD_SELECT_LIST;
		WorldTrade_SelectNameListBackup( &wk->selectListPos, wk->dw->headwordListPos+wk->dw->headwordPos, 
										wk->dw->nameListPos, wk->dw->namePos );

		break;
	// 選択
	default:
		BmpListExit( wk->BmpListWork, &wk->dw->nameListPos, &wk->dw->namePos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpMenuWinClear( &wk->MenuWin[1], WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		GF_BGL_BmpWinDel( &wk->MenuWin[1] );
		wk->Search.characterNo = result;
		wk->subprocess_seq     = SUBSEQ_START;
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		// 名前決定
		GF_BGL_BmpWinDataFill( &wk->InfoWin[1], 0x0000 );
		WorldTrade_PokeNamePrint( &wk->InfoWin[1], wk->MonsNameManager, 
			result, 2, 0, GF_PRINTCOLOR_MAKE(1,2,0)  );
		
		// 決定したポケモンの性別分布を取得
		wk->dw->sex_selection = PokePersonalParaGet(result,ID_PER_sex);
		OS_Printf("");

		// カーソル位置保存
		WorldTrade_SelectNameListBackup( &wk->selectListPos, wk->dw->headwordListPos+wk->dw->headwordPos, 
										wk->dw->nameListPos, wk->dw->namePos );

		if(WorldTrade_SexSelectionCheck( &wk->Search, wk->dw->sex_selection )){
			GF_BGL_BmpWinDataFill( &wk->InfoWin[3], 0x0000 );
			WorldTrade_SexPrint( &wk->InfoWin[3], wk->MsgManager, wk->Search.gender, 1, 0, 2,  GF_PRINTCOLOR_MAKE(1,2,0)  );
			
		}

		break;

	}

	return SEQ_MAIN;
}
//------------------------------------------------------------------
/**
 * @brief   性別を選択してください
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SUBSEQ_SexSelectMes( WORLDTRADE_WORK *wk)
{
	// ポケモンの性別を選んでください
	SubSeq_MessagePrint( wk, msg_gtc_01_011, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SEX_SELECT_LIST );

	// 性別選択ウインドウ確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[0], GF_BGL_FRAME0_M,
		SELECT_MENU3_X,		SELECT_MENU3_Y,		SELECT_MENU3_SX, 		SELECT_MENU3_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU3_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MenuWin[0], 0x0000 );

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   性別選択開始
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SUBSEQ_SexSelectList( WORLDTRADE_WORK *wk)
{
	wk->BmpListWork = WorldTrade_SexSelectListMake( &wk->BmpMenuList, &wk->MenuWin[0], wk->MsgManager );
	wk->listpos = 0xffff;

	wk->subprocess_seq = SUBSEQ_SEX_SELECT_WAIT;
	
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   性別選択待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SUBSEQ_SexSelectWait( WORLDTRADE_WORK *wk)
{
	u32 result;
	switch((result=WorldTrade_BmpListMain( wk->BmpListWork, &wk->listpos ))){
	// キャンセル
	case BMPMENU_CANCEL:
		BmpListExit( wk->BmpListWork, NULL, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		wk->subprocess_seq = SUBSEQ_START;
		break;
	// 選択
	case PARA_MALE: case PARA_FEMALE: case PARA_UNK: 
		BmpListExit( wk->BmpListWork, NULL, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		wk->Search.gender	= result+1;
		wk->subprocess_seq  = SUBSEQ_START;

		// 性別決定
		GF_BGL_BmpWinDataFill( &wk->InfoWin[3], 0x0000 );
		WorldTrade_SexPrint( &wk->InfoWin[3], wk->MsgManager, wk->Search.gender, 
												1, 0, 2, GF_PRINTCOLOR_MAKE(1,2,0)  );


		break;
	}


	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   ほしいレベルを選択してください
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SUBSEQ_LevelSelectMes( WORLDTRADE_WORK *wk)
{
	// ポケモンのレベルをきめてください
	SubSeq_MessagePrint( wk, msg_gtc_01_012, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_LEVEL_SELECT_LIST );

	// 性別選択ウインドウ確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[0], GF_BGL_FRAME0_M,
		SELECT_MENU4_X,		SELECT_MENU4_Y,		SELECT_MENU4_SX, 		SELECT_MENU4_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU4_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MenuWin[0], 0x0000 );

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   レベル選択開始
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SUBSEQ_LevelSelectList( WORLDTRADE_WORK *wk)
{
	// レベル選択リスト作成
	wk->BmpListWork = WorldTrade_LevelListMake(&wk->BmpMenuList, &wk->MenuWin[0], wk->MsgManager );
	wk->listpos = 0xffff;

	wk->subprocess_seq = SUBSEQ_LEVEL_SELECT_WAIT;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   レベル選択待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SUBSEQ_LevelSelectWait( WORLDTRADE_WORK *wk)
{
	u32 result;
	switch((result=WorldTrade_BmpListMain( wk->BmpListWork, &wk->listpos ))){
	case BMPLIST_NULL:
		break;
	// キャンセル
	case BMPMENU_CANCEL:
	case 12:
		BmpListExit( wk->BmpListWork, NULL, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		wk->subprocess_seq = SUBSEQ_START;
		break;
	// レベル指定決定
	default: 
		BmpListExit( wk->BmpListWork, NULL, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		WorldTrade_LevelMinMaxSet(&wk->Search, result);
		wk->subprocess_seq  = SUBSEQ_START;

		GF_BGL_BmpWinDataFill( &wk->InfoWin[5], 0x0000 );
		// レベル指定決定
		WorldTrade_WantLevelPrint( &wk->InfoWin[5], wk->MsgManager, result, 2, 0, GF_PRINTCOLOR_MAKE(1,2,0) );

		break;
	}


	return SEQ_MAIN;
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
	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY1, YESNO_OFFSET );
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
			wk->subprocess_seq = SUBSEQ_START;
		}else{
			// タイトルメニューへ
			wk->subprocess_seq  = SUBSEQ_END;
			WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );

			// 下画面のOBJを隠す
			WorldTrade_SubLcdMatchObjHide( wk );

			// 検索結果人数はクリアする
			wk->SearchResult = 0;

		}
	}

	return SEQ_MAIN;
	
}




//------------------------------------------------------------------
/**
 * $brief   情報ページを切り替える
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_PageChange( WORLDTRADE_WORK *wk)
{
//	ChangePage( wk );
	wk->subprocess_seq = SUBSEQ_MAIN;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   検索エラーメッセージ表示
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SearchErrorMessage(WORLDTRADE_WORK *wk)
{
	SubSeq_MessagePrint( wk, msg_gtc_error_003, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );
	
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
 * @brief   メッセージ終了後１秒待つ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_MessageWait1Min( WORLDTRADE_WORK *wk )
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		wk->wait++;
		if(wk->wait>45){
			wk->wait = 0;
			wk->subprocess_seq = wk->subprocess_nextseq;
		}
	}
	return SEQ_MAIN;


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
	
//	tempbuf = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WORLDTRADE );
	MSGMAN_GetString(  wk->MsgManager, msgno, wk->TalkString );
//	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );
//	STRBUF_Delete(tempbuf);

	// 会話ウインドウ枠描画
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, WORLDTRADE_MESFRAME_CHR, WORLDTRADE_MESFRAME_PAL );

	// 文字列描画開始
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);


}

//------------------------------------------------------------------
/**
 * @brief   ほしいポケモン情報の「ラベル」描画
 *
 * @param   win		
 * @param   MsgManager		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void WantLabelPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager )
{
	STRBUF *strbuf, *levelbuf, *sexbuf;

	//「ほしいポケモン」描画
	strbuf = MSGMAN_AllocString( MsgManager, msg_gtc_03_002 );
	WorldTrade_SysPrint( &win[0], strbuf,    0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	STRBUF_Delete(strbuf);

	// せいべつ
	sexbuf = MSGMAN_AllocString( MsgManager, msg_gtc_03_004  );
	WorldTrade_SysPrint( &win[2], sexbuf,    0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	STRBUF_Delete(sexbuf);

	// レベル
	levelbuf = MSGMAN_AllocString( MsgManager, msg_gtc_03_006 );
	WorldTrade_SysPrint( &win[4], levelbuf,  0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	STRBUF_Delete(levelbuf);

	//「さがす」描画
	strbuf = MSGMAN_AllocString( MsgManager, msg_gtc_03_008 );
	WorldTrade_SysPrint( &win[6], strbuf,    0, 0, 0, GF_PRINTCOLOR_MAKE(1,2,0) );
	STRBUF_Delete(strbuf);

	//「もどる」描画
	strbuf = MSGMAN_AllocString( MsgManager, msg_gtc_03_009 );
	WorldTrade_SysPrint( &win[7], strbuf,    0, 0, 0, GF_PRINTCOLOR_MAKE(1,2,0) );
	STRBUF_Delete(strbuf);
	

}

//------------------------------------------------------------------
/**
 * @brief   検索データがまったく同じか比較
 *
 * @param   s1		
 * @param   s2		
 *
 * @retval  int		同じなら１
 */
//------------------------------------------------------------------
static int DpwSerachCompare( const Dpw_Tr_PokemonSearchData *s1, const Dpw_Tr_PokemonSearchData *s2 )
{
	if( s1->characterNo==s2->characterNo && s1->gender==s2->gender
	&&	s1->level_min==s2->level_min     && s1->level_max==s2->level_max){
		return 1;
	}
	
	return 0;
}
