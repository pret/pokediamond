//============================================================================================
/**
 * @file	worldtrade_deposit.c
 * @bfief	世界交換ポケモン預ける画面処理
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
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/monsno.h"

#include "savedata/wifilist.h"
#include "savedata/zukanwork.h"
#include "application/worldtrade.h"
#include "worldtrade_local.h"
#include "msgdata/msg_wifi_lobby.h"
#include "msgdata/msg_wifi_gtc.h"

#include "worldtrade.naix"			// グラフィックアーカイブ定義
#include "../zukanlist/zkn_data/zukan_data.naix"
#include "application/zukanlist/zkn_sort_akstnhmyrw_idx.h"

//============================================================================================
//	プロトタイプ宣言
//============================================================================================
/*** 関数プロトタイプ ***/
static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat );
static void BgInit( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( WORLDTRADE_WORK * wk );
static void BmpWinInit( WORLDTRADE_WORK *wk );
static void BmpWinDelete( WORLDTRADE_WORK *wk );
static void InitWork( WORLDTRADE_WORK *wk );
static void FreeWork( WORLDTRADE_WORK *wk );
static int SubSeq_Start( WORLDTRADE_WORK *wk);
static int SubSeq_Main( WORLDTRADE_WORK *wk);
static int RoundWork( int num, int max, int move );
static int SubSeq_HeadWordSelectList( WORLDTRADE_WORK *wk );
static int SubSeq_HeadWordSelectWait( WORLDTRADE_WORK *wk );
static int SubSeq_PokeNameSelectList( WORLDTRADE_WORK *wk );
static int SubSeq_PokeNameSelectWait( WORLDTRADE_WORK *wk );
static int SubSeq_End( WORLDTRADE_WORK *wk);
static int SubSeq_YesNo( WORLDTRADE_WORK *wk);
static int SubSeq_MessageWait( WORLDTRADE_WORK *wk );
static void PokeWantPrint( MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager,WORDSET *WordSet, GF_BGL_BMPWIN win[], int monsno, int sex, int level );
static void PokeDepositPrint( MSGDATA_MANAGER *MsgManager, WORDSET *WordSet, GF_BGL_BMPWIN win[], POKEMON_PASO_PARAM *ppp, Dpw_Tr_PokemonDataSimple *post );
static int 	SubSeq_SexSelctWait( WORLDTRADE_WORK *wk );
static int 	SubSeq_SexSelctList( WORLDTRADE_WORK *wk );
static int 	SubSeq_SexSelctMessage( WORLDTRADE_WORK *wk );
static int  SubSeq_LevelSelectMessage( WORLDTRADE_WORK *wk );
static int  SubSeq_LevelSelectWait( WORLDTRADE_WORK *wk );
static int  SubSeq_LevelSelectList( WORLDTRADE_WORK *wk );
static int  SubSeq_DepositOkMessage( WORLDTRADE_WORK *wk );
static int  SubSeq_DepositOkYesNo( WORLDTRADE_WORK *wk );
static int SubSeq_DepositOkYesNoWait( WORLDTRADE_WORK *wk );
static void DepositPokemonDataMake( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk );


static int PokeNameSortListMake( BMP_MENULIST_DATA **menulist, MSGDATA_MANAGER *monsnameman, 
									MSGDATA_MANAGER *msgman,u16 *table, u8 *sinou,
									int num, int select,ZUKAN_WORK *zukan );
static u16* ZukanSortDataGet( int heap, int idx, int* p_arry_num );
static GF_PRINTCOLOR GetSexColor( int sex, GF_PRINTCOLOR color );



enum{
	SUBSEQ_START=0,
	SUBSEQ_MAIN,
	SUBSEQ_END,

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
	SUBSEQ_DEPOSITOK_MESSAGE,
	SUBSEQ_DEPOSIT_YESNO,
	SUBSEQ_DEPOSIT_YESNO_WAIT,
	
	SUBSEQ_MES_WAIT,
};
static int (*Functable[])( WORLDTRADE_WORK *wk ) = {
	SubSeq_Start,				// SUBSEQ_START=0,
	SubSeq_Main,    	        // SUBSEQ_MAIN,
	SubSeq_End,         	    // SUBSEQ_END,
	SubSeq_HeadWordSelectList,	// SUBSEQ_HEADWORD_SELECT_LIST
	SubSeq_HeadWordSelectWait,	// SUBSEQ_HEADWORD_SELECT_WAIT
	SubSeq_PokeNameSelectList,	// SUBSEQ_POKENAME_SELECT_LIST
	SubSeq_PokeNameSelectWait,	// SUBSEQ_POKENAME_SELECT_WAIT
	SubSeq_SexSelctMessage,		// SUBSEQ_SEX_SELECT_MES,
	SubSeq_SexSelctList,		// SUBSEQ_SEX_SELECT_LIST,
	SubSeq_SexSelctWait,		// SUBSEQ_SEX_SELECT_WAIT,
	SubSeq_LevelSelectMessage,	// SUBSEQ_LEVEL_SELECT_MES,
    SubSeq_LevelSelectList,     // SUBSEQ_LEVEL_SELECT_LIST,
    SubSeq_LevelSelectWait,     // SUBSEQ_LEVEL_SELECT_WAIT,
	SubSeq_DepositOkMessage,
    SubSeq_DepositOkYesNo,
	SubSeq_DepositOkYesNoWait,

	SubSeq_MessageWait,			// SUBSEQ_MES_WAIT
};

#define BOX_CUROSOR_END_POS			( 30 )
#define BOX_CUROSOR_TRAYNAME_POS	( 31 )


// ほしいポケモン・あずけるポケモン情報
#define INFORMATION_STR_X	(  1 )
#define INFORMATION_STR_Y	(  4 )
#define INFORMATION2_STR_X	(  3 )
#define INFORMATION2_STR_Y	(  6 )
#define INFORMATION3_STR_X	(  1 )
#define INFORMATION3_STR_Y	(  8 )
#define INFORMATION_STR_SX	( 11 )
#define INFORMATION_STR_SY	(  2 )


#define TITLE_MESSAGE_OFFSET   ( WORLDTRADE_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define LINE_MESSAGE_OFFSET    ( TITLE_MESSAGE_OFFSET     + TITLE_TEXT_SX*TITLE_TEXT_SY )
#define INFOMATION_STR_OFFSET  ( LINE_MESSAGE_OFFSET      + LINE_TEXT_SX*LINE_TEXT_SY )
#define SELECT_MENU1_OFFSET    ( INFOMATION_STR_OFFSET    + INFORMATION_STR_SX*INFORMATION_STR_SY*6 )
#define SELECT_MENU2_OFFSET    ( SELECT_MENU1_OFFSET      + SELECT_MENU1_SX*SELECT_MENU1_SY )
#define SELECT_MENU3_OFFSET    ( SELECT_MENU1_OFFSET )
#define SELECT_MENU4_OFFSET    ( SELECT_MENU1_OFFSET )
#define YESNO_OFFSET 		   ( SELECT_MENU4_OFFSET      + SELECT_MENU4_SX*SELECT_MENU4_SY )

static const u16 infomation_bmp_table[6][2]={
	{INFORMATION_STR_X,  INFORMATION_STR_Y,   },
	{INFORMATION2_STR_X, INFORMATION2_STR_Y,  },
	{INFORMATION3_STR_X, INFORMATION3_STR_Y,  },
	{INFORMATION_STR_X,  INFORMATION_STR_Y+9, },
	{INFORMATION2_STR_X, INFORMATION2_STR_Y+9,},
	{INFORMATION3_STR_X, INFORMATION3_STR_Y+9,},

};

// 検索レベル指定用構造体
typedef struct{
	int msg;
	s16 min;
	s16 max;
}WT_LEVEL_TERM;

// 検索レベル数(最後はキャンセルだけど）
#define LEVEL_SELECT_NUM	(13)

// 検索レベル指定テーブル
static const WT_LEVEL_TERM level_minmax_table[]={
	{ msg_gtc_12_001, 0,   0, },	// きにしない
	{ msg_gtc_12_002, 0,   9, },	// レベル１０みまん
	{ msg_gtc_12_003,10,   0, },	// レベル１０以上
	{ msg_gtc_12_004,20,   0, },	// レベル２０以上
	{ msg_gtc_12_005,30,   0, },	// レベル３０以上
	{ msg_gtc_12_006,40,   0, },	// レベル４０以上
	{ msg_gtc_12_007,50,   0, },	// レベル５０以上
	{ msg_gtc_12_008,60,   0, },	// レベル６０以上
	{ msg_gtc_12_009,70,   0, },	// レベル７０以上
	{ msg_gtc_12_010,80,   0, },	// レベル８０以上
	{ msg_gtc_12_011,90,   0, },	// レベル９０以上
	{ msg_gtc_12_012,100,100, },	// レベル１００
    { msg_gtc_12_013, 0,  0, }, // キャンセル
};




//============================================================================================
//	プロセス関数
//============================================================================================

//==============================================================================
/**
 * @brief   世界交換入り口画面初期化
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Deposit_Init(WORLDTRADE_WORK *wk, int seq)
{
	// ワーク初期化
	InitWork( wk );
	
	// BG設定
	BgInit( wk->bgl );

	// BGグラフィック転送
	BgGraphicSet( wk );

	// BMPWIN確保
	BmpWinInit( wk );

//	SetCellActor(wk);


	WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_deposit.c [226] M ********************\n" );
#endif

	// 通信状態を確認してアイコンの表示を変える
    WorldTrade_WifiIconAdd( wk );
   
    // ほしいポケモン・あずけるポケモン描画
	WodrldTrade_PokeWantPrint( wk->MsgManager, wk->MonsNameManager, 
				wk->WordSet, &wk->InfoWin[0], 0,DPW_TR_GENDER_NONE,-1);
	PokeDepositPrint( wk->MsgManager, wk->WordSet, &wk->InfoWin[3], wk->deposit_ppp, &wk->Post );

	OS_TPrintf("図鑑総数 = %d\n",wk->dw->nameSortNum);


	wk->subprocess_seq = SUBSEQ_START;
	
	
	return SEQ_FADEIN;
}

//==============================================================================
/**
 * @brief   世界交換入り口画面メイン
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Deposit_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret;

	// 通信状態を確認してアイコンの表示を変える
    WirelessIconEasy_SetLevel(WorldTrade_WifiLinkLevel());
	
	ret = (*Functable[wk->subprocess_seq])( wk );

	return ret;
}


//==============================================================================
/**
 * @brief   世界交換入り口画面終了
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Deposit_End(WORLDTRADE_WORK *wk, int seq)
{
	WirelessIconEasyEnd();

//	DelCellActor(wk);

	FreeWork( wk );
	
	BmpWinDelete( wk );
	
	BgExit( wk->bgl );
	
	WorldTrade_SubProcessUpdate( wk );
	
	return SEQ_INIT;
}


//------------------------------------------------------------------
/**
 * @brief   会話ウインドウ表示
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
	
	// 文字列取得
	tempbuf = MSGMAN_AllocString(  wk->MsgManager, msgno );

	// WORDSET展開
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );
	

	// 会話ウインドウ枠描画
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, WORLDTRADE_MESFRAME_CHR, WORLDTRADE_MESFRAME_PAL );

	// 文字列描画開始
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);

	STRBUF_Delete(tempbuf);
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
	}



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
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_deposit_nclr, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_WORLDTRADE);
	
	// 会話フォントパレット転送
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );

	// 会話ウインドウグラフィック転送
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MESFRAME_CHR, 
						WORLDTRADE_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_WORLDTRADE );


	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MENUFRAME_CHR,
						WORLDTRADE_MENUFRAME_PAL, 0, HEAPID_WORLDTRADE );


	// メイン画面BG1キャラ転送
	ArcUtil_BgCharSet( ARC_WORLDTRADE_GRA, NARC_worldtrade_deposit_lz_ncgr, bgl, GF_BGL_FRAME1_M, 0, 16*5*0x20, 1, HEAPID_WORLDTRADE);

	// メイン画面BG1スクリーン転送
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_deposit_lz_nscr, bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);


}






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
	int i;
	// ---------- メイン画面 ------------------

	// BG0面BMPWINタイトルウインドウ確保・描画
	
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME0_M,
	TITLE_TEXT_X, TITLE_TEXT_Y, TITLE_TEXT_SX, TITLE_TEXT_SY, WORLDTRADE_TALKFONT_PAL,  TITLE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x0000 );
	
	// 「ポケモンをあずける」描画
	WorldTrade_TalkPrint( &wk->TitleWin, wk->TitleString, 0, 1, 0, GF_PRINTCOLOR_MAKE(15,14,0) );


	// 一行ウインドウ
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		LINE_TEXT_X, LINE_TEXT_Y, LINE_TEXT_SX, LINE_TEXT_SY, 
		WORLDTRADE_TALKFONT_PAL,  LINE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0000 );
//	Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_05_001, MSG_ALLPUT, 0 );


	// あずけるポケモン・ほしいポケモン情報BMPWIN確保
	for(i=0;i<6;i++){
		GF_BGL_BmpWinAdd(wk->bgl, &wk->InfoWin[i], GF_BGL_FRAME0_M,
			infomation_bmp_table[i][0], infomation_bmp_table[i][1], 
			INFORMATION_STR_SX, INFORMATION_STR_SY, WORLDTRADE_TALKFONT_PAL,  
			INFOMATION_STR_OFFSET+(INFORMATION_STR_SX*INFORMATION_STR_SY)*i  );
		GF_BGL_BmpWinDataFill( &wk->InfoWin[i], 0x0000 );
		GF_BGL_BmpWinOn(&wk->InfoWin[i]);
	}

	OS_Printf("WORLDTRADE heap残り = %d\n",sys_GetHeapFreeSize( HEAPID_WORLDTRADE ));
}	

//------------------------------------------------------------------
/**
 * @brief   確保したBMPWINを解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( WORLDTRADE_WORK *wk )
{
	int i;
	
	for(i=0;i<6;i++){
		GF_BGL_BmpWinDel( &wk->InfoWin[i] );
	}
	GF_BGL_BmpWinDel( &wk->MsgWin );
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

	// ポケモンをあずける
	wk->TitleString = MSGMAN_AllocString( wk->MsgManager, msg_gtc_05_001 );

	// ポケモン名テーブル作成用のワーク確保
	wk->dw = sys_AllocMemory(HEAPID_WORLDTRADE, sizeof(DEPOSIT_WORK));
	MI_CpuClearFast( wk->dw, sizeof(DEPOSIT_WORK) );

	// 図鑑ソートデータ(全国図鑑と、シンオウ図鑑の分岐が必要だとおもう）
	wk->dw->nameSortTable = WorldTrade_ZukanSortDataGet( HEAPID_WORLDTRADE, 0, &wk->dw->nameSortNum );

	// シンオウ図鑑テーブル
	wk->dw->sinouTable    = WorldTrade_SinouZukanDataGet( HEAPID_WORLDTRADE );

	// カーソル位置初期化
	WorldTrade_SelectListPosInit( &wk->selectListPos );
}


//------------------------------------------------------------------
/**
 * @brief   ワーク解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeWork( WORLDTRADE_WORK *wk )
{

	sys_FreeMemoryEz( wk->dw->sinouTable );
	sys_FreeMemoryEz(wk->dw->nameSortTable);
	sys_FreeMemoryEz(wk->dw);

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
 * @brief   サブプロセスシーケンススタート処理
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_Start( WORLDTRADE_WORK *wk)
{
	// 
	if(WIPE_SYS_EndCheck()){
		SubSeq_MessagePrint( wk, msg_gtc_01_010, 1, 0, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );

		// ほしいポケモン・あずけるポケモン描画
		
//		 wk->subprocess_seq = SUBSEQ_MAIN;
	}

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   サブプロセスシーケンスメイン
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_Main( WORLDTRADE_WORK *wk)
{

	if(sys.trg & PAD_BUTTON_B){
		 WorldTrade_SubProcessChange( wk, WORLDTRADE_MYBOX, MODE_DEPOSIT_SELECT );
		wk->subprocess_seq = SUBSEQ_END;
	}

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

	wk->subprocess_seq = SUBSEQ_HEADWORD_SELECT_LIST;

	return SEQ_MAIN;
}




//------------------------------------------------------------------
/**
 * @brief   numにmoveを足し,0以下ならmax-1に、maxなら0にして返す
 *
 * @param   num		元の値
 * @param   max		最大値
 * @param   move	足す値（＋－あり）
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int RoundWork( int num, int max, int move )
{
	num += move;
	if(num < 0) {
		return max-1;
	}
	if(num==max){
		return 0;
	}
	return num;
}


//------------------------------------------------------------------
/**
 * @brief   頭文字選択リスト作成
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_HeadWordSelectList( WORLDTRADE_WORK *wk )
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
static int SubSeq_HeadWordSelectWait( WORLDTRADE_WORK *wk )
{
	switch(WorldTrade_BmpListMain( wk->BmpListWork, &wk->listpos )){
	case 1: case 2: case 3: case 4: case 5:	case 6: case 7: case 8: case 9: case 10:
		BmpListExit( wk->BmpListWork, &wk->dw->headwordListPos, &wk->dw->headwordPos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		wk->subprocess_seq  = SUBSEQ_POKENAME_SELECT_LIST;
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		break;

	// キャンセル
	case BMPMENU_CANCEL:
		BmpListExit( wk->BmpListWork, &wk->dw->headwordListPos, &wk->dw->headwordPos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		GF_BGL_BmpWinDel( &wk->MenuWin[1] );

		WorldTrade_SubProcessChange( wk, WORLDTRADE_MYBOX, MODE_DEPOSIT_SELECT );
		wk->subprocess_seq = SUBSEQ_END;
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
		break;
	}
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   ポケモン名前選択リスト作成
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_PokeNameSelectList( WORLDTRADE_WORK *wk )
{
	// ポケモン名リスト作成
	wk->BmpListWork = WorldTrade_PokeNameListMake( wk,
						&wk->BmpMenuList, &wk->MenuWin[1], 
						wk->MsgManager, wk->MonsNameManager,wk->dw,
						wk->param->zukanwork );
	wk->listpos = 0xffff;

	OS_Printf("in trade 図鑑フラグ = %d\n", ZukanWork_GetZenkokuZukanFlag(wk->param->zukanwork));


	wk->subprocess_seq = SUBSEQ_POKENAME_SELECT_WAIT;

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   ポケモンの説別分布から性別は決定するか？入力が必要か？
 *
 * @param   dtp		
 * @param   sex_selection		
 *
 * @retval  int		0:性別の入力が必要	1:決定しているので必要ない
 */
//------------------------------------------------------------------
int WorldTrade_SexSelectionCheck( Dpw_Tr_PokemonSearchData *dtsd, int sex_selection ) 
{
	switch(sex_selection){
	case MONS_MALE:
		dtsd->gender = PARA_MALE+1;
		return 1;
		break;
	case MONS_FEMALE:
		dtsd->gender = PARA_FEMALE+1;
		return 1;
		break;
	case MONS_UNKNOWN:
		dtsd->gender = PARA_UNK+1;
		return 1;
		break;
	}
	
	return 0;
}


//------------------------------------------------------------------
/**
 * @brief   ポケモン名前選択
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_PokeNameSelectWait( WORLDTRADE_WORK *wk )
{
	u32 result;
	int sex;
	
	switch((result=WorldTrade_BmpListMain( wk->BmpListWork, &wk->listpos ))){
	case BMPLIST_NULL:
		break;

	// キャンセル
	case BMPMENU_CANCEL:
		BmpListExit( wk->BmpListWork, &wk->dw->nameListPos, &wk->dw->namePos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[1], WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		GF_BGL_BmpWinDel( &wk->MenuWin[1] );		
		wk->subprocess_seq  = SUBSEQ_START;
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
		
		WorldTrade_SelectNameListBackup( &wk->selectListPos, wk->dw->headwordListPos+wk->dw->headwordPos, wk->dw->nameListPos, wk->dw->namePos );

		break;
	// 選択
	default:
		BmpListExit( wk->BmpListWork, &wk->dw->nameListPos, &wk->dw->namePos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpMenuWinClear( &wk->MenuWin[1], WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		GF_BGL_BmpWinDel( &wk->MenuWin[1] );
		wk->Want.characterNo = result;
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		// 性別分布情報取得 
		wk->dw->sex_selection = PokePersonalParaGet(result,ID_PER_sex);
		// 性別は固定か？（固定の場合は性別がWantに格納される）
		if(WorldTrade_SexSelectionCheck( &wk->Want, wk->dw->sex_selection )){
			// 性別は決定しているので、入力する必要が無い
			wk->subprocess_seq  = SUBSEQ_LEVEL_SELECT_MES;
			sex                 = wk->Want.gender;
		}else{
			// 性別は決定していないので入力が必要
			wk->subprocess_seq  = SUBSEQ_SEX_SELECT_MES;
			sex = DPW_TR_GENDER_NONE;
		}

		// 名前決定(性別がきまることもある）
		WodrldTrade_PokeWantPrint( wk->MsgManager, wk->MonsNameManager, wk->WordSet, 
							&wk->InfoWin[0], wk->Want.characterNo,sex,-1);

		WorldTrade_SelectNameListBackup( &wk->selectListPos, wk->dw->headwordListPos+wk->dw->headwordPos, wk->dw->nameListPos, wk->dw->namePos );

		break;

	}
	
	return SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   性別を選んでくださいメッセージ
 *
 * @param   wk		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	SubSeq_SexSelctMessage( WORLDTRADE_WORK *wk )
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
 * @brief   性別選択リスト作成・表示
 *
 * @param   wk		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	SubSeq_SexSelctList( WORLDTRADE_WORK *wk )
{
	wk->BmpListWork = WorldTrade_SexSelectListMake( &wk->BmpMenuList, &wk->MenuWin[0], wk->MsgManager );
	wk->listpos = 0xffff;

	wk->subprocess_seq = SUBSEQ_SEX_SELECT_WAIT;

	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   性別選択リスト選択待ち
 *
 * @param   wk		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	SubSeq_SexSelctWait( WORLDTRADE_WORK *wk )
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

		wk->Want.gender			= result+1;
		wk->subprocess_seq  = SUBSEQ_LEVEL_SELECT_MES;

		// 性別決定
		WodrldTrade_PokeWantPrint( wk->MsgManager, wk->MonsNameManager, wk->WordSet, 
							&wk->InfoWin[0], wk->Want.characterNo,wk->Want.gender,-1);

		break;
	}

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   レベルを選んでくださいメッセージ表示
 *
 * @param   wk		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static int SubSeq_LevelSelectMessage( WORLDTRADE_WORK *wk )
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
 * @brief   レベル選択リスト作成・表示
 *
 * @param   wk		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static int SubSeq_LevelSelectList( WORLDTRADE_WORK *wk )
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
 * @retval  static		
 */
//------------------------------------------------------------------
static int SubSeq_LevelSelectWait( WORLDTRADE_WORK *wk )
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
		
		// ポケモンの性別が固定かどうかをチェックして戻る
		if(WorldTrade_SexSelectionCheck( &wk->Want, wk->dw->sex_selection )){
			// 性別は固定無いので、ポケモン選択まで戻る
			wk->subprocess_seq = SUBSEQ_START;
		}else{
			// 性別入力が必要
			wk->subprocess_seq = SUBSEQ_SEX_SELECT_MES;
		}
		break;
	// レベル指定決定
	default: 
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
		BmpListExit( wk->BmpListWork, NULL, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );

		WorldTrade_LevelMinMaxSet(&wk->Want, result);
		wk->subprocess_seq  = SUBSEQ_DEPOSITOK_MESSAGE;

		// レベル指定決定
		WodrldTrade_PokeWantPrint( wk->MsgManager, wk->MonsNameManager, wk->WordSet, 
						&wk->InfoWin[0], wk->Want.characterNo,wk->Want.gender,
						WorldTrade_LevelTermGet(wk->Want.level_min,wk->Want.level_max));

		break;
	}

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   この条件でよい？メッセージ表示
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_DepositOkMessage( WORLDTRADE_WORK *wk )
{
	// このじょうけんでよろしいですか？
	SubSeq_MessagePrint( wk, msg_gtc_01_024, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_DEPOSIT_YESNO );
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   これで条件であずけます？はい・いいえ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_DepositOkYesNo( WORLDTRADE_WORK *wk )
{

	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY1, YESNO_OFFSET );
	wk->subprocess_seq = SUBSEQ_DEPOSIT_YESNO_WAIT;

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   はい・いいえ待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_DepositOkYesNoWait( WORLDTRADE_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WORLDTRADE );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// いいえ→ポケモン選択からやり直し
			WorldTrade_SubProcessChange( wk, WORLDTRADE_MYBOX, MODE_DEPOSIT_SELECT );
			wk->subprocess_seq  = SUBSEQ_END;
		}else{
			// はい→ポケモンをあずける
		 	WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_UPLOAD );
			wk->subprocess_seq  = SUBSEQ_END;
			wk->sub_out_flg = 1;

			// サーバーアップロード用のデータを作成
			DepositPokemonDataMake( &wk->UploadPokemonData, wk );
		}
	}

	return SEQ_MAIN;
	
}














//------------------------------------------------------------------
/**
 * @brief   サブプロセスシーケンス終了処理
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_End( WORLDTRADE_WORK *wk )
{
	// 接続画面だったら、上下画面でフェード
	if(wk->sub_nextprocess==WORLDTRADE_ENTER ){
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_deposit.c [1165] MS ********************\n" );
#endif
		wk->sub_out_flg = 1;
	}else{
		// 続きの画面にいく場合は上画面だけフェード
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_deposit.c [1171] M ********************\n" );
#endif
	}
	wk->subprocess_seq = 0;
	
	return SEQ_FADEOUT;
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













// 性別アイコンを表示するためのカラー指定
static GF_PRINTCOLOR sex_mark_col[]={
	GF_PRINTCOLOR_MAKE(5,6,0),
	GF_PRINTCOLOR_MAKE(3,4,0),
};


//==============================================================================
/**
 * @brief   
 *
 * @param   win		
 * @param   nameman		
 * @param   monsno		
 * @param   flag		
 * @param   color		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_PokeNamePrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *nameman, int monsno, int flag, int y, GF_PRINTCOLOR color )
{
	STRBUF *namebuf;

	// 名前
	if(monsno!=0){
		namebuf = MSGMAN_AllocString( nameman, monsno );
		WorldTrade_SysPrint( win, namebuf, 0, y, flag, color );
		STRBUF_Delete(namebuf);
	}

}




//------------------------------------------------------------------
/**
 * @brief   
 *
 * @param   sex		
 * @param   color		
 *
 * @retval  GF_PRINTCOLOR		
 */
//------------------------------------------------------------------
static GF_PRINTCOLOR GetSexColor( int sex, GF_PRINTCOLOR color )
{

	if(sex==DPW_TR_GENDER_MALE){
		return sex_mark_col[0];
	}else if(sex==DPW_TR_GENDER_FEMALE){
		return sex_mark_col[1];
	}
	return color;
}

// 性別文字列のテーブル「きにしない・♂・♀・きにしない」
const int WorldTrade_SexStringTable[]={
	msg_gtc_11_001,
	msg_gtc_11_002,
	msg_gtc_11_003,
	msg_gtc_11_001,
	
};

//==============================================================================
/**
 * @brief   性別を表示する
 *
 * @param   win		
 * @param   msgman		
 * @param   sex		
 * @param   flag	「きにしない」を表示するかどうか
 * @param   color	
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SexPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int sex, int flag, int y, int printflag, GF_PRINTCOLOR color )
{
	STRBUF *sexbuf;

	OS_Printf("SEX Print flag = %d, sex = %d\n", flag, sex);

	if(flag==0 && sex==DPW_TR_GENDER_NONE){
		// 性別無しを表示しなくてもいい時は表示しない
		return;
	}
	
	sexbuf = MSGMAN_AllocString( msgman, WorldTrade_SexStringTable[sex]  );
	// flagが3以内の場合はセンタリング指定・以上の場合はＸ座標指定
	if(printflag > 3){
		WorldTrade_SysPrint( win, sexbuf,   printflag, y, 0, GetSexColor( sex, color ) );
	}else{
		WorldTrade_SysPrint( win, sexbuf,   0, y, printflag, GetSexColor( sex, color ) );
	}
	STRBUF_Delete(sexbuf);
}

//==============================================================================
/**
 * @brief   レベル条件の文字列描画を行う
 *
 * @param   win		
 * @param   msgman		
 * @param   sex		
 * @param   flag		
 * @param   color		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_WantLevelPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int level, int flag, int y, GF_PRINTCOLOR color )
{
	STRBUF *levelbuf;

	if(level!=-1){
		levelbuf = MSGMAN_AllocString( msgman, level_minmax_table[level].msg );
		WorldTrade_SysPrint( win, levelbuf,  0, y, flag, color );
		STRBUF_Delete(levelbuf);
	}
}
//------------------------------------------------------------------
/**
 * @brief   交換して欲しいポケモンの条件を描画する
 *
 * @param   MsgManager		
 * @param   MonsNameManager
 * @param   WordSet		
 * @param   win[]		
 * @param   monsno		
 * @param   sex		
 * @param   level		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WodrldTrade_PokeWantPrint( MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager,
	WORDSET *WordSet, GF_BGL_BMPWIN win[], int monsno, int sex, int level )
{
	STRBUF *strbuf;
	int i;

	//「ほしいポケモン」描画
	strbuf = MSGMAN_AllocString( MsgManager, msg_gtc_05_008 );
	WorldTrade_SysPrint( &win[0], strbuf,    0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );

	// 名前・性別・レベルの欄はクリアする
	for(i=1;i<3;i++){
		GF_BGL_BmpWinDataFill( &win[i], 0x0000 );
	}

	// 名前
	WorldTrade_PokeNamePrint(&win[1], MonsNameManager, monsno, 0, 0,GF_PRINTCOLOR_MAKE(15,2,0) );

	// 性別
	if( sex==DPW_TR_GENDER_MALE || sex==DPW_TR_GENDER_FEMALE ){
		OS_Printf("性別描画した %d\n", sex);
		WorldTrade_SexPrint( &win[1], MsgManager, sex, 0, 0, 70, GF_PRINTCOLOR_MAKE(15,2,0) );
	}else{
		OS_Printf("性別描画してない %d\n");
	
	}

	// レベル指定
	WorldTrade_WantLevelPrint( &win[2], MsgManager, level, 2, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	
	

	STRBUF_Delete(strbuf);
}

//------------------------------------------------------------------
/**
 * @brief   交換して欲しいポケモンの条件を描画する
 *
 * @param   MsgManager		
 * @param   MonsNameManager
 * @param   WordSet		
 * @param   win[]		
 * @param   monsno		
 * @param   sex		
 * @param   level		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WodrldTrade_MyPokeWantPrint( MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager,
	WORDSET *WordSet, GF_BGL_BMPWIN win[], int monsno, int sex, int level )
{
	STRBUF *strbuf;
	int i;

	//「ほしいポケモン」描画
	strbuf = MSGMAN_AllocString( MsgManager, msg_gtc_05_008 );
	WorldTrade_SysPrint( &win[0], strbuf,    0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );

	// 名前・性別・レベルの欄はクリアする
	for(i=1;i<3;i++){
		GF_BGL_BmpWinDataFill( &win[i], 0x0000 );
	}

	// 名前
	WorldTrade_PokeNamePrint(&win[1], MonsNameManager, monsno, 0, 0,GF_PRINTCOLOR_MAKE(15,2,0) );

	// 性別
	if( sex==DPW_TR_GENDER_MALE || sex==DPW_TR_GENDER_FEMALE ){
		OS_Printf("性別描画した %d\n", sex);
		WorldTrade_SexPrint( &win[1], MsgManager, sex, 0, 0, 70, GF_PRINTCOLOR_MAKE(15,2,0) );
	}else{
		OS_Printf("性別描画してない\n");
	}

	// レベル指定
	WorldTrade_WantLevelPrint( &win[2], MsgManager, level, 2, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	
	

	STRBUF_Delete(strbuf);
}

//------------------------------------------------------------------
/**
 * @brief   今から預けようとするポケモンの情報を描画する
 *
 * @param   MsgManager		
 * @param   WordSet		
 * @param   win[]		
 * @param   ppp		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeDepositPrint( 
	MSGDATA_MANAGER *MsgManager, 
	WORDSET *WordSet, 
	GF_BGL_BMPWIN win[], 
	POKEMON_PASO_PARAM *ppp,
	Dpw_Tr_PokemonDataSimple *post )
{
	STRBUF *strbuf,	*levelbuf;
	STRBUF *namebuf = STRBUF_Create( MONS_NAME_SIZE+EOM_SIZE, HEAPID_WORLDTRADE );
	STRBUF *sexbuf = STRBUF_Create( MONS_NAME_SIZE+EOM_SIZE, HEAPID_WORLDTRADE );
	int sex, level,i;
	
	OS_TPrintf("deposit_ppp3 = %08x", ppp);
	
	// あずけるポケモン

	// 名前・性別・レベル取得
	PokePasoParaGet(ppp, ID_PARA_nickname_buf, namebuf );
	sex   = PokePasoParaGet( ppp, ID_PARA_sex,   NULL )+1;
	level = PokePasoLevelCalc(ppp);
	
	OS_Printf("sex=%d, level=%d\n",sex, level);
	
	// 「あずけるポケモン」・性別アイコン文字列取得
	strbuf = MSGMAN_AllocString( MsgManager, msg_gtc_05_011  );
	WORDSET_RegisterNumber( WordSet, 3, level, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	levelbuf = MSGDAT_UTIL_AllocExpandString( WordSet, MsgManager, msg_gtc_05_013, HEAPID_WORLDTRADE );
	if(sex!=DPW_TR_GENDER_NONE){
		MSGMAN_GetString( MsgManager, WorldTrade_SexStringTable[sex], sexbuf );
	}

	// 描画の前にクリア
	for(i=0;i<3;i++){
		GF_BGL_BmpWinDataFill( &win[i], 0x0000 );
	}

	// 描画
	WorldTrade_SysPrint( &win[0], strbuf,    0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	WorldTrade_SysPrint( &win[1], namebuf,   0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	WorldTrade_SysPrint( &win[2], levelbuf,  0, 0, 2, GF_PRINTCOLOR_MAKE(15,2,0) );
	if(sex!=DPW_TR_GENDER_NONE){
		WorldTrade_SysPrint( &win[1], sexbuf,   70, 0, 0, sex_mark_col[sex-1] );
	}

	post->characterNo = PokePasoParaGet(ppp, ID_PARA_monsno, NULL);
	post->gender      = sex;
	post->level       = level;

	STRBUF_Delete( levelbuf );
	STRBUF_Delete( sexbuf   );
	STRBUF_Delete( namebuf  );
	STRBUF_Delete( strbuf   );
}

#define ZKN_SORTDATA_ONESIZE	( sizeof(u16) )

//------------------------------------------------------------------
/**
 * @brief   ずかんソートデータ取得（あういえお順）。解放はじぶんで。
 *			
 * @param   heap		
 * @param   idx		
 * @param   p_arry_num		
 *
 * @retval  u16*		
 */
//------------------------------------------------------------------
u16* WorldTrade_ZukanSortDataGet( int heap, int idx, int* p_arry_num )
{
	u32 size;
	u16* p_buf;
	
	// 読み込み
	p_buf = ArcUtil_LoadEx( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_sort_aiueo_dat, FALSE, heap, ALLOC_TOP, &size );

	*p_arry_num = size / ZKN_SORTDATA_ONESIZE;

	return p_buf;
	
	// ポケモンの名前を取得する
	//STRBUF* MSGDAT_UTIL_GetMonsName( u32 monsno, u32 heapID )
}

//==============================================================================
/**
 * @brief   シンオウ図鑑データを読み込む			解放はじぶんで
 *			シンオウ図鑑の順に開発NOが入っているので、
 *			新たにテーブルを確保して「この開発NOはシンオウか？」の作成もする
 *
 * @param   heap		
 * @param   p_arry_num	MONS_END+1
 *
 * @retval  u16 *		494個分のシンオウ図鑑かどうかのフラグが入ったテーブル
 */
//==============================================================================
u8 *WorldTrade_SinouZukanDataGet( int heap  )
{
	u32 size,num,i;
	u16* p_buf;

	// テーブル確保・初期化
	u8 *sinouData = sys_AllocMemory( HEAPID_WORLDTRADE, MONSNO_END+1 );
	MI_CpuClearFast( sinouData, MONSNO_END+1 );

	// シンオウ図鑑テーブル
	p_buf = ArcUtil_LoadEx( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_sort_shinoh_dat, FALSE, heap, ALLOC_TOP, &size );
	
	num = size / ZKN_SORTDATA_ONESIZE;

	// フラグテーブルに作り直す
	for(i=0;i<num;i++){
		if(p_buf[i]<MONSNO_END+1){
			sinouData[p_buf[i]] = 1;
		}
	}

	sys_FreeMemoryEz(p_buf);

	return sinouData;
	
}


//==============================================================================
/**
 * @brief   サーバーに送信する基本情報を格納する
 *
 * @param   dtd		
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_PostPokemonBaseDataMake( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk )
{
	STRCODE *name;
	// ポケモン構造体を代入
	
	if(WorldTrade_GetPPorPPP( wk->BoxTrayNo )){
		// POKEMON_PARAMとしてコピー
		MI_CpuCopyFast( wk->deposit_ppp, dtd->postData.data,  PokemonParam_GetWorkSize() );
	}else{
		// POKEMON_PASO_PARAMなのでReplace関数でPOKEMON_PARAMに肉付けする
		PokeReplace(wk->deposit_ppp,(POKEMON_PARAM *)dtd->postData.data);
	}

	// トレーナー名コピー
	PM_strncpy( dtd->name, MyStatus_GetMyName(wk->param->mystatus), DPW_TR_NAME_SIZE );

	
	// ID
	dtd->trainerID   = MyStatus_GetID_Low( wk->param->mystatus );

	// 国・地域
	dtd->countryCode = WIFIHISTORY_GetMyNation( wk->param->wifihistory );
	dtd->localCode   = WIFIHISTORY_GetMyArea( wk->param->wifihistory );

	// 見た目
	dtd->trainerType = MyStatus_GetTrainerView( wk->param->mystatus );

	// 性別
	dtd->gender      = MyStatus_GetMySex( wk->param->mystatus );

	// バージョン・国コード
	dtd->versionCode = PM_VERSION;
	dtd->langCode    = PM_LANG;
	
}


//------------------------------------------------------------------
/**
 * @brief   ポケモンを預けるのに必要なデータを作成する
 *
 * @param   dtd		
 * @param   wk		
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void DepositPokemonDataMake( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk )
{

	// 基本情報を格納（ポケモン・トレーナー名・国・地域・見た目など）
	WorldTrade_PostPokemonBaseDataMake( dtd, wk );
	
	// ほしいポケモン情報を格納
	dtd->postSimple = wk->Post;
	dtd->wantSimple = wk->Want;

	OS_Printf( "postData  No = %d,  gender = %d, level min= %d\n", wk->Post.characterNo, wk->Post.gender, wk->Post.level);
	OS_Printf( "WantData  No = %d,  gender = %d, level min= %d\n", wk->Want.characterNo, wk->Want.gender, wk->Want.level_min);


	OS_Printf( "TrainerId = %05d,  nation = %d, area = %d\n", dtd->trainerID, dtd->countryCode, dtd->localCode);
	OS_Printf( "Version   = %d,  language = %d, \n", dtd->versionCode, dtd->langCode);


}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// BMPLIST関係
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#define DEPOSIT_HEADWORD_NUM	( 10 )
#define DEPOSIT_Y_NUM			(  6 )

///BMPLIST用定義
static const BMPLIST_HEADER MenuListHeader = {
    NULL,			// 表示文字データポインタ
    NULL,					// カーソル移動ごとのコールバック関数
    NULL,					// 一列表示ごとのコールバック関数
    NULL,					// 
    DEPOSIT_HEADWORD_NUM,	// リスト項目数
    DEPOSIT_Y_NUM,			// 表示最大項目数
    4,						// ラベル表示Ｘ座標
    8,						// 項目表示Ｘ座標
    0,						// カーソル表示Ｘ座標
    2,						// 表示Ｙ座標
    FBMP_COL_BLACK,			// 文字色
    FBMP_COL_WHITE,			// 背景色
    FBMP_COL_BLK_SDW,		// 文字影色
    0,						// 文字間隔Ｘ
    16,						// 文字間隔Ｙ
    BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
    FONT_SYSTEM,			// 文字指定
    0,						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
    NULL,                   // ワーク
};



//==============================================================================
/**
 * @brief   頭文字選択メニュー作成
 *
 * @param  none
 *
 * @retval  none		
 */
//==============================================================================
BMPLIST_WORK *WorldTrade_WordheadBmpListMake( WORLDTRADE_WORK *wk, BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager )
{
	BMPLIST_HEADER list_h;
	int i;

	*menulist = BMP_MENULIST_Create( 10, HEAPID_WORLDTRADE );
	for(i=0;i<10;i++){
		BMP_MENULIST_AddArchiveString( *menulist, MsgManager, msg_gtc_10_001+i, i+1 );
	}

    list_h       = MenuListHeader;
    list_h.list  = *menulist;
    list_h.win   = win;

	// 枠描画
	BmpMenuWinWrite( win, WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMPメニュー開始
    return BmpListSet(&list_h, wk->dw->headwordListPos, wk->dw->headwordPos, HEAPID_WORLDTRADE);

}

// 頭文字テーブル（ソートされたポケモンの何番目に「ア・カ・サ…」が登場するか？
static u16 NameHeadTable[]={
	ZKN_AKSTNHMYRW_IDX_A,
	ZKN_AKSTNHMYRW_IDX_K,
	ZKN_AKSTNHMYRW_IDX_S,
	ZKN_AKSTNHMYRW_IDX_T,
	ZKN_AKSTNHMYRW_IDX_N,
	ZKN_AKSTNHMYRW_IDX_H,
	ZKN_AKSTNHMYRW_IDX_M,
	ZKN_AKSTNHMYRW_IDX_Y,
	ZKN_AKSTNHMYRW_IDX_R,
	ZKN_AKSTNHMYRW_IDX_W,
	ZKN_AKSTNHMYRW_IDX_END,
};

//------------------------------------------------------------------
/**
 * @brief   ポケモン名、５０音順ソートリスト作成
 *
 * @param   menulist	リストデータ（ここに登録する）
 * @param   msgman		ポケモン名メッセージデータ
 * @param   table		５０音順モンスターナンバーテーブル
 * @param   num			ポケモンの総数
 * @param   select		アカサタナハマヤラワのどれを選択したか？（ア: 0～9まで）
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int PokeNameSortListMake( BMP_MENULIST_DATA **menulist, MSGDATA_MANAGER *monsnameman, 
									MSGDATA_MANAGER *msgman,u16 *table, u8 *sinou,
									int num, int select,ZUKAN_WORK *zukan )
{
	int i,index,see_count=0;
	int pokenum = NameHeadTable[select+1]-NameHeadTable[select];
	int flag    = ZukanWork_GetZenkokuZukanFlag(zukan);

	OS_TPrintf("select = %d, num = %d\n",select, pokenum);
	
	// 図鑑と比べて何体見ているかを確認
	index = NameHeadTable[select];
	for(i=0;i<pokenum;i++){
		// 全国図鑑か？
		if(flag){
			if(ZukanWork_GetPokeSeeFlag( zukan, table[index+i] )){
				OS_Printf(" SeeCheck i = %d, table[index+i] = %d\n", i, table[index+i]);
				see_count++;
			}
		}else{
			// シンオウ図鑑にいることを確認した上で図鑑チェック
			if(sinou[table[index+i]]){
				if(ZukanWork_GetPokeSeeFlag( zukan, table[index+i] )){
					see_count++;
				}
			}
		
		}
	}

	// 項目リストの作成
	*menulist = BMP_MENULIST_Create( see_count+1, HEAPID_WORLDTRADE );


	// ポケモン名の登録
	for(i=0;i<pokenum;i++){
		// 全国図鑑か？
		if(flag){
			if(ZukanWork_GetPokeSeeFlag( zukan, table[index+i] )){
				OS_Printf(" ListAdd i = %d, table[index+i] = %d\n", i, table[index+i]);
				BMP_MENULIST_AddArchiveString( *menulist, monsnameman, table[index+i], table[index+i] );
			}
		}else{
			// シンオウ図鑑にいることを確認した上で図鑑チェック
			if(sinou[table[index+i]]){
				if(ZukanWork_GetPokeSeeFlag( zukan, table[index+i] )){
					BMP_MENULIST_AddArchiveString( *menulist, monsnameman, table[index+i], table[index+i] );
				}
			}
		}
	}
	// 「もどる」を登録
	BMP_MENULIST_AddArchiveString( *menulist, msgman, msg_gtc_11_004, BMPMENU_CANCEL );

	return see_count+1;
}


//==============================================================================
/**
 * @brief   ポケモン名選択リスト作成
 *
 * @param   menulist		
 * @param   win		
 * @param   MsgManager		
 * @param   MonsNameManager		
 * @param   dw		
 *
 * @retval  BMPLIST_WORK *		
 */
//==============================================================================
BMPLIST_WORK *WorldTrade_PokeNameListMake( WORLDTRADE_WORK *wk, BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, 
			MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager, DEPOSIT_WORK* dw, ZUKAN_WORK *zukan)
{
	BMPLIST_HEADER list_h;
	int i,listnum,head;

	GF_BGL_BmpWinDataFill( win, 0x0f0f );

	head = dw->headwordListPos+dw->headwordPos;
	listnum = PokeNameSortListMake( menulist, MonsNameManager, MsgManager, 
									dw->nameSortTable, dw->sinouTable, 
									dw->nameSortNum, head, zukan );
	
	
    list_h       = MenuListHeader;
    list_h.count = listnum;
    list_h.list  = *menulist;
    list_h.win   = win;

	// 枠描画
	BmpMenuWinWrite( win, WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMPメニュー開始
    return BmpListSet(&list_h, wk->selectListPos.name_list[head],
    						   wk->selectListPos.name_pos[head], HEAPID_WORLDTRADE);

}


// 選択リスト用性別アイコン列
static sex_select_table[][2]={
	{msg_gtc_11_001, PARA_UNK,},
	{msg_gtc_11_002, PARA_MALE,},
	{msg_gtc_11_003, PARA_FEMALE,} ,
	{msg_gtc_11_004, BMPMENU_CANCEL},
};

//==============================================================================
/**
 * @brief   ポケモン性別選択リスト作成
 *
 * @param   menulist		
 * @param   win		
 * @param   MsgManager		
 *
 * @retval  BMPLIST_MENU *		
 */
//==============================================================================
BMPLIST_WORK *WorldTrade_SexSelectListMake( BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager  )
{
	BMPLIST_HEADER list_h;
	int i;

	*menulist = BMP_MENULIST_Create( 4, HEAPID_WORLDTRADE );
	for(i=0;i<4;i++){
		BMP_MENULIST_AddArchiveString( *menulist, MsgManager, sex_select_table[i][0], sex_select_table[i][1] );
	}

    list_h       = MenuListHeader;
    list_h.count = 4;
    list_h.list  = *menulist;
    list_h.win   = win;

	// 枠描画
	BmpMenuWinWrite( win, WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMPメニュー開始
    return BmpListSet(&list_h, 0, 0, HEAPID_WORLDTRADE);
	
}



//==============================================================================
/**
 * @brief   レベル選択リスト作成
 *
 * @param   menulist		
 * @param   win		
 * @param   MsgManager		
 *
 * @retval  BMPLIST_WORK *		
 */
//==============================================================================
BMPLIST_WORK *WorldTrade_LevelListMake(BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager  )
{
	BMPLIST_HEADER list_h;
	int i;

	*menulist = BMP_MENULIST_Create( LEVEL_SELECT_NUM, HEAPID_WORLDTRADE );
	for(i=0;i<LEVEL_SELECT_NUM;i++){
		BMP_MENULIST_AddArchiveString( *menulist, MsgManager, level_minmax_table[i].msg, i );
	}

    list_h       = MenuListHeader;
    list_h.count = LEVEL_SELECT_NUM;
    list_h.list  = *menulist;
    list_h.win   = win;

	// 枠描画
	BmpMenuWinWrite( win, WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMPメニュー開始
    return BmpListSet(&list_h, 0, 0, HEAPID_WORLDTRADE);

}


//==============================================================================
/**
 * @brief   レベル指定条件を代入する
 *
 * @param   dtps		検索条件構造体
 * @param   index		検索条件の添え字
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_LevelMinMaxSet( Dpw_Tr_PokemonSearchData *dtps, int index )
{
	GF_ASSERT(index<(LEVEL_SELECT_NUM-1));// レベル指定の配列より上だった
	
	dtps->level_min = level_minmax_table[index].min;
	dtps->level_max = level_minmax_table[index].max;
}

//==============================================================================
/**
 * @brief   指定のレベル条件のインデックスを取得する
 *
 * @param   min		最低
 * @param   max		最大レベル
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_LevelTermGet( int min, int max )
{
	int i;
	
	for(i=0;i<LEVEL_SELECT_NUM;i++){
		if(level_minmax_table[i].min==min && level_minmax_table[i].max==max){
			return i;
		}
	}

	// レベル条件が合わなかったからといってASSERTにすると、後々が怖いので
	// 「なんでもあり」にしておく
	return 0;
}


//==============================================================================
/**
 * @brief   効果音に対応したBMPLISTMAIN関数
 *
 * @param   lw		
 * @param   posbackup		
 *
 * @retval  u32		
 */
//==============================================================================
u32 WorldTrade_BmpListMain( BMPLIST_WORK * lw, u16 *posbackup )
{
	u16 listpos;
	u32 result = BmpListMain( lw );

	BmpListDirectPosGet( lw, &listpos );

	if(*posbackup != listpos){
		if(*posbackup!=0xffff){
			Snd_SePlay(WORLDTRADE_MOVE_SE);
		}
		*posbackup = listpos;
		
	}

	return result;
}

//==============================================================================
/**
 * @brief   選択位置カーソル情報のクリア
 *
 * @param   slp		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SelectListPosInit( SELECT_LIST_POS *slp)
{
	int i;
	
	for(i=0;i<NAME_HEAD_MAX;i++){
		slp->name_list[i] = 0;
		slp->name_pos[i]  = 0;
	}
	
	slp->head_list = 0;
	slp->head_pos  = 0;

	
}


//==============================================================================
/**
 * @brief   カーソル位置保存
 *
 * @param   SELECT_LIST_POS		
 * @param   slp		
 * @param   head		
 * @param   list		
 * @param   pos		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SelectNameListBackup( SELECT_LIST_POS *slp, int head, int list, int pos )
{
	slp->name_list[head] = list;
	slp->name_pos[head]  = pos;
}