//============================================================================================
/**
 * @file	worldtrade_mypoke.c
 * @bfief	世界交換自分ポケモン閲覧画面
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
#include "system/gra_tool.h"
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
#include "itemtool/item.h"
#include "poketool/pokeparty.h"

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "msgdata/msg_wifi_lobby.h"
#include "msgdata/msg_wifi_gtc.h"

#include "worldtrade.naix"			// グラフィックアーカイブ定義



//============================================================================================
//	プロトタイプ宣言
//============================================================================================
/*** 関数プロトタイプ ***/
static void BgInit( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( WORLDTRADE_WORK *wk );
static void BmpWinInit( WORLDTRADE_WORK *wk );
static void BmpWinDelete( WORLDTRADE_WORK *wk );
static void InitWork( WORLDTRADE_WORK *wk );
static void FreeWork( WORLDTRADE_WORK *wk );
static void SetCellActor(WORLDTRADE_WORK *wk);
static void DelCellActor(WORLDTRADE_WORK *wk);
static void WantPokePrintReWrite( WORLDTRADE_WORK *wk );


static int SubSeq_Start( WORLDTRADE_WORK *wk);
static int SubSeq_Main( WORLDTRADE_WORK *wk);
static int SubSeq_End( WORLDTRADE_WORK *wk);
static int SubSeq_MessageWait( WORLDTRADE_WORK *wk );
static int SubSeq_Message1MinWait( WORLDTRADE_WORK *wk );
static int SubSeq_YesNo( WORLDTRADE_WORK *wk);
static int SubSeq_YesNoSelect( WORLDTRADE_WORK *wk);
static int SubSeq_SelectList( WORLDTRADE_WORK *wk);
static int SubSeq_SelectWait( WORLDTRADE_WORK *wk);


static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat, POKEMON_PARAM *pp );


enum{
	SUBSEQ_START=0,
	SUBSEQ_MAIN,
	SUBSEQ_END,
	SUBSEQ_MES_WAIT,
	SUBSEQ_MES_1MIN_WAIT,
	SUBSEQ_YESNO,
	SUBSEQ_YESNO_SELECT,
	SUBSEQ_SELECT_LIST,
	SUBSEQ_SELECT_WAIT,
};

static int (*Functable[])( WORLDTRADE_WORK *wk ) = {
	SubSeq_Start,			// SUBSEQ_START=0,
	SubSeq_Main,            // SUBSEQ_MAIN,
	SubSeq_End,             // SUBSEQ_END,
	SubSeq_MessageWait,     // SUBSEQ_MES_WAIT
	SubSeq_Message1MinWait,	// SUBSEQ_MES_1MIN_WAIT,
	SubSeq_YesNo,			// SUBSEQ_YESNO
	SubSeq_YesNoSelect,		// SUBSEQ_YESNO_SELECT
	SubSeq_SelectList,		// SUBSEQ_SELECT_LIST,
	SubSeq_SelectWait,		// SUBSEQ_SELECT_WAIT,
};

#define INFO_TEXT_WORD_NUM	(10*2)
#define MESSAGE_WAIT_1MIN	( 45 )


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
int WorldTrade_MyPoke_Init(WORLDTRADE_WORK *wk, int seq)
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

	// 自分のポケモンの情報
	WorldTrade_PokeInfoPrint( 	wk->MsgManager, wk->MonsNameManager, wk->WordSet, &wk->InfoWin[0], 
					PPPPointerGet((POKEMON_PARAM*)wk->UploadPokemonData.postData.data),
					&wk->UploadPokemonData.postSimple );

	// 持ち主情報の表示
	WorldTrade_PokeInfoPrint2( wk->MsgManager, &wk->InfoWin[5], wk->UploadPokemonData.name );

	// ほしいポケモンの条件
	WodrldTrade_MyPokeWantPrint( wk->MsgManager, wk->MonsNameManager, wk->WordSet, 
				&wk->InfoWin[7], 
				wk->UploadPokemonData.wantSimple.characterNo,
				wk->UploadPokemonData.wantSimple.gender,
				WorldTrade_LevelTermGet(wk->UploadPokemonData.wantSimple.level_min,wk->UploadPokemonData.wantSimple.level_max));

	// ポケモン画像転送
	WorldTrade_TransPokeGraphic( (POKEMON_PARAM*)wk->UploadPokemonData.postData.data );
	
	// ２回目以降
	// ワイプフェード開始（両画面）
	WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_mypoke.c [152] M ********************\n" );
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
int WorldTrade_MyPoke_Main(WORLDTRADE_WORK *wk, int seq)
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
int WorldTrade_MyPoke_End(WORLDTRADE_WORK *wk, int seq)
{
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
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_poke_view_nclr, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_WORLDTRADE);
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_traderoom_nclr, PALTYPE_SUB_BG,  0, 16*8*2,  HEAPID_WORLDTRADE);
	
	// 会話フォントパレット転送
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );
  //	TalkFontPaletteLoad( PALTYPE_SUB_BG,  WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );

	// 会話ウインドウグラフィック転送
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MESFRAME_CHR, 
						WORLDTRADE_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_WORLDTRADE );

	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MENUFRAME_CHR,
						WORLDTRADE_MENUFRAME_PAL, 0, HEAPID_WORLDTRADE );



	// メイン画面BG1キャラ転送
	ArcUtil_BgCharSet( ARC_WORLDTRADE_GRA, NARC_worldtrade_poke_view_lz_ncgr, bgl, GF_BGL_FRAME1_M, 0, 16*5*0x20, 1, HEAPID_WORLDTRADE);

	// メイン画面BG1スクリーン転送
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_mypoke_lz_nscr, bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);


	// サブ画面BG1キャラ転送
	ArcUtil_BgCharSet( ARC_WORLDTRADE_GRA, NARC_worldtrade_traderoom_lz_ncgr, bgl, GF_BGL_FRAME1_S, 0, 32*21*0x40, 1, HEAPID_WORLDTRADE);

	// サブ画面BG1スクリーン転送
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_traderoom_lz_nscr, bgl, GF_BGL_FRAME1_S, 0, 32*24*2, 1, HEAPID_WORLDTRADE);



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

	// 自分のポケモン表示
	add.mat.x = FX32_ONE *   200;
	add.mat.y = FX32_ONE *    58;
	wk->PokemonActWork = CLACT_Add(&add);
	CLACT_SetAnmFlag(wk->PokemonActWork,1);
	CLACT_AnmChg( wk->PokemonActWork, 37 );
	
	WirelessIconEasy();

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
	CLACT_Delete(wk->PokemonActWork);
}

#define NAME_TEXT_X		(  8 )
#define NAME_TEXT_Y		(  5 )
#define NAME_TEXT_SX	( 10 )
#define NAME_TEXT_SY	(  2 )

#define MENU_MAX_NUM	(  3 )

#define SELECT_MENU_X	(  21 )
#define SELECT_MENU_Y 	(  15 )
#define SELECT_MENU_SX	( 5*2 )
#define SELECT_MENU_SY	(   4 )

#define LINE_MESSAGE_OFFSET   ( WORLDTRADE_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define SELECT_MENU_OFFSET    ( LINE_MESSAGE_OFFSET + LINE_TEXT_SX*LINE_TEXT_SY )
#define INFO_TEXT_OFFSET	  ( SELECT_MENU_OFFSET + SELECT_MENU_SX*SELECT_MENU_SY )
static const info_bmpwin_table[][4]={
	{  2,  2, 10,  2,},
	{  3,  4,  8,  2,},
	{  12,  4,  7,  2,},
	{  2,  7,  6,  2,},
	{  9,  7, 10,  2,},
	{  4, 10,  6,  2,},
	{ 11, 10,  8,  2,},
	{  2, 15, 12,  2,},
	{  4, 17, 10,  2,},
	{ 16, 17, 12,  2,},
};

// はい・いいえのBMPWIN領域は最後にもってきたいのだが、
// 情報ウインドウの総数がよめないので、200キャラずらしておく
#define YESNO_OFFSET 		   ( SELECT_MENU_OFFSET + SELECT_MENU_SX*SELECT_MENU_SY+200 )

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

	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		LINE_TEXT_X, LINE_TEXT_Y, LINE_TEXT_SX, LINE_TEXT_SY, 
		WORLDTRADE_TALKFONT_PAL,  LINE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0000 );

	// BMPMENU用の領域がここにある
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[0], GF_BGL_FRAME0_M,
		SELECT_MENU_X, SELECT_MENU_Y, SELECT_MENU_SX, SELECT_MENU_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU_OFFSET );	

	// BG0面BMPWIN情報ウインドウ確保
	{
		int i, offset;

		offset = INFO_TEXT_OFFSET;
		for(i=0;i<10;i++){
			GF_BGL_BmpWinAdd(wk->bgl, &wk->InfoWin[i], GF_BGL_FRAME0_M,
					info_bmpwin_table[i][0], 
					info_bmpwin_table[i][1], 
					info_bmpwin_table[i][2], 
					info_bmpwin_table[i][3], 
					WORLDTRADE_TALKFONT_PAL,  offset );
			GF_BGL_BmpWinDataFill( &wk->InfoWin[i], 0x0000 );
			offset += info_bmpwin_table[i][2]*info_bmpwin_table[i][3];
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
	GF_BGL_BmpWinDel( &wk->MenuWin[0] );
	{
		int i;
		for(i=0;i<10;i++){
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

	// POKeMON GLOBAL TRADING SYSTEM
	wk->TitleString = MSGMAN_AllocString( wk->MsgManager, msg_gtc_02_001 );

	for(i=0;i<10;i++){
		wk->InfoString[i]  = STRBUF_Create( INFO_TEXT_WORD_NUM, HEAPID_WORLDTRADE );
	}
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
	int i;
	for(i=0;i<10;i++){
		STRBUF_Delete( wk->InfoString[i] );
	}
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
	// GTCへようこそ！
//	SubSeq_MessagePrint( wk, msg_wifilobby_028, 1, 0, 0x0f0f );
//	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );
	wk->subprocess_seq = SUBSEQ_MAIN;;


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
//	if(sys.trg & PAD_BUTTON_A){
//		SubSeq_MessagePrint( wk, msg_wifilobby_009, 1, 0, 0x0f0f );
//		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_YESNO );
//	}

	if(sys.trg & PAD_BUTTON_A){
		// 「●●●●をどうしますか？」
		SubSeq_MessagePrint( wk, msg_gtc_01_006, 1, 0, 0x0f0f,(POKEMON_PARAM*)wk->UploadPokemonData.postData.data );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SELECT_LIST );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
	}else if(sys.trg & PAD_BUTTON_B){
		wk->subprocess_seq  = SUBSEQ_END;
		WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
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
	WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_mypoke.c [605] M ********************\n" );
#endif
	wk->subprocess_seq = 0;
	
	return SEQ_FADEOUT;
}

//------------------------------------------------------------------
/**
 * $brief   引き取りますか？はい・いいえ
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
 * $brief   引き取りますか？はい・いいえ選択待ち
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
			// いいえ
			wk->subprocess_seq = SUBSEQ_START;
			BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );

		}else{
			// はい→引取りへ
			wk->subprocess_seq  = SUBSEQ_END;
			wk->sub_out_flg = 1;
			WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_DOWNLOAD );
		}

		// はい・いいえで背景が崩れているので再描画
		WantPokePrintReWrite( wk );

	}

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * $brief   選択リスト作成
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SelectList( WORLDTRADE_WORK *wk )
{
	BMPMENU_HEADER temp;

	temp.font  = FONT_SYSTEM;
	temp.x_max = 1;
	temp.y_max = 2;
	temp.line_spc = 0;
	temp.c_disp_f = 0;
	temp.loop_f   = 0;


	wk->BmpMenuList = BMP_MENULIST_Create( 2, HEAPID_WORLDTRADE );
	// ひきとる
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_02_016, 1 );
	// そのまま
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_02_017, 2 );

	temp.menu = wk->BmpMenuList;
	temp.win  = &wk->MenuWin[0];

	// 枠描画
	BmpMenuWinWrite( &wk->MenuWin[0], WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMPメニュー開始
	wk->BmpMenuWork = BmpMenuAddEx( &temp, 9, 0, 0, HEAPID_WORLDTRADE, PAD_BUTTON_B );


	wk->subprocess_seq = SUBSEQ_SELECT_WAIT;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * $brief   「ひきとる」「そのまま」選択待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SelectWait( WORLDTRADE_WORK *wk )
{
	switch(BmpMenuMain( wk->BmpMenuWork )){
	// 「ひきとる」
	case 1:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		{
			POKEMON_PARAM *pp = (POKEMON_PARAM *)wk->UploadPokemonData.postData.data;
			// あずけたポケモンはメールを持っているか？
			if(WorldTrade_PokemonMailCheck( pp )){
				// てもちがいっぱいだと受け取れない
				if(PokeParty_GetPokeCount(wk->param->myparty)==6){
					SubSeq_MessagePrint( wk, msg_gtc_01_037, 1, 0, 0x0f0f, pp );
					WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );
					return SEQ_MAIN;
				}
			}
			
			// ●●●をひきとります
			SubSeq_MessagePrint( wk, msg_gtc_01_007, 1, 0, 0x0f0f, pp );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_YESNO );
		}
		WantPokePrintReWrite(wk);
		break;

	// 「そのまま」
	case 2:case BMPMENU_CANCEL:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		wk->subprocess_seq  = SUBSEQ_END;
		 WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
		WantPokePrintReWrite(wk);
		break;
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
 * @brief   メッセージを出して１．５秒待つ
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
		if(wk->wait > MESSAGE_WAIT_1MIN){
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
static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat, POKEMON_PARAM *pp )
{
	// 文字列取得
	STRBUF *tempbuf;
	
	WORDSET_RegisterPokeMonsName( wk->WordSet, 0, PPPPointerGet(pp) );
	tempbuf = MSGMAN_AllocString(  wk->MsgManager, msgno );
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );

	// 会話ウインドウ枠描画
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, WORLDTRADE_MESFRAME_CHR, WORLDTRADE_MESFRAME_PAL );

	// 文字列描画開始
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);
	
	STRBUF_Delete(tempbuf);

}


// 性別アイコンを表示するためのカラー指定
static GF_PRINTCOLOR sex_mark_col[]={
	0,GF_PRINTCOLOR_MAKE(5,6,0),GF_PRINTCOLOR_MAKE(3,4,0),
};

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
void WorldTrade_PokeInfoPrint( 	MSGDATA_MANAGER *MsgManager,
							MSGDATA_MANAGER *MonsNameManager, 	
							WORDSET *WordSet, 
							GF_BGL_BMPWIN win[], 	
							POKEMON_PASO_PARAM *ppp,
							Dpw_Tr_PokemonDataSimple *post )
{
	STRBUF *strbuf,	*sexbuf, *levelbuf, *itemlabel;
	STRBUF *namebuf = STRBUF_Create( (MONS_NAME_SIZE+EOM_SIZE)*2, HEAPID_WORLDTRADE );
	STRBUF *itembuf = STRBUF_Create( (ITEM_NAME_SIZE+EOM_SIZE)*2, HEAPID_WORLDTRADE );
	int sex, level,itemno,i,monsno;
	
	// ニックネーム・性別・レベル・開発ＮＯ・アイテム取得
	PokePasoParaGet(ppp, ID_PARA_nickname_buf, namebuf );
	monsno = post->characterNo;
	sex    = post->gender;
	level  = post->level;
	itemno = PokePasoParaGet( ppp, ID_PARA_item, NULL );
	
	OS_Printf("sex=%d, level=%d\n",sex, level);
	
	// 「もちもの」・性別文字列・ＬＶ．？？？・種族名・アイテム名、文字列生成
	itemlabel = MSGMAN_AllocString( MsgManager, msg_gtc_04_004  );
	sexbuf    = MSGMAN_AllocString( MsgManager, WorldTrade_SexStringTable[sex]  );
	WORDSET_RegisterNumber( WordSet, 3, level, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	levelbuf  = MSGDAT_UTIL_AllocExpandString( WordSet, MsgManager, msg_gtc_05_013, HEAPID_WORLDTRADE );
	strbuf    = MSGMAN_AllocString( MonsNameManager, monsno );
	GetItemName( itembuf, itemno, HEAPID_WORLDTRADE );

	// 描画の前にクリア
	for(i=0;i<5;i++){
		GF_BGL_BmpWinDataFill( &win[i], 0x0000 );
	}

	// 描画
	WorldTrade_SysPrint( &win[0], namebuf,   0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	if(sex!=DPW_TR_GENDER_NONE){
		WorldTrade_SysPrint( &win[0], sexbuf,   70, 0, 0, sex_mark_col[sex] );
	}
	WorldTrade_SysPrint( &win[1], strbuf,    0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	WorldTrade_SysPrint( &win[2], levelbuf,  0, 0, 2, GF_PRINTCOLOR_MAKE(15,2,0) );
	WorldTrade_SysPrint( &win[3], itemlabel, 0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	WorldTrade_SysPrint( &win[4], itembuf,   0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );

	STRBUF_Delete( itemlabel );
	STRBUF_Delete( itembuf   );
	STRBUF_Delete( levelbuf  );
	STRBUF_Delete( sexbuf    );
	STRBUF_Delete( namebuf   );
	STRBUF_Delete( strbuf    );
}


//------------------------------------------------------------------
/**
 * @brief   持ち主情報の描画
 *
 * @param   MsgManager		
 * @param   win[]		
 * @param   name		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WorldTrade_PokeInfoPrint2( MSGDATA_MANAGER *MsgManager, GF_BGL_BMPWIN win[], STRCODE *name )
{
	STRBUF *ornerbuf, *ornerlabel;
	ornerbuf = STRBUF_Create( (PERSON_NAME_SIZE+EOM_SIZE)*2, HEAPID_WORLDTRADE );

	ornerlabel = MSGMAN_AllocString( MsgManager, msg_gtc_02_010  );
	STRBUF_SetStringCode( ornerbuf, name );

	WorldTrade_SysPrint( &win[0], ornerlabel, 0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	WorldTrade_SysPrint( &win[1], ornerbuf,   0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	
	STRBUF_Delete( ornerlabel );
	STRBUF_Delete( ornerbuf   );
}

#define POKEGRA_VRAM_OFFSET	(   (18*32+16)*32 )
#define POKEGRA_VRAM_SIZE	( 0x20*10*10 )

//------------------------------------------------------------------
/**
 * ポケモン画像を転送する
 *
 * @param   pokeno		POKEMON_PARAM
 *
 * @retval  none
 */
//------------------------------------------------------------------
void WorldTrade_TransPokeGraphic( POKEMON_PARAM *pp )
{
	SOFT_SPRITE_ARC ssa;
	u8  *char_work = sys_AllocMemory( HEAPID_WORLDTRADE, POKEGRA_VRAM_SIZE );

	// ポケモンの画像を読み込む（ただしソフトウェアスプライト用のテクスチャ状態）
	PokeGraArcDataGetPP(&ssa, pp, PARA_FRONT);

	// テクスチャをOAM用の並びに変換する
	{
		int rnd    = PokeParaGet( pp, ID_PARA_personal_rnd, NULL );
		int monsno = PokeParaGet( pp, ID_PARA_monsno, NULL );
		Ex_ChangesInto_OAM_from_PokeTex(ssa.arc_no, ssa.index_chr, HEAPID_WORLDTRADE, 0, 0, 10, 10, char_work, 
										rnd, 0, PARA_FRONT, monsno);
	}
//	ChangesInto_OAM_from_PokeTex(ssa.arc_no, ssa.index_chr, HEAPID_WORLDTRADE, 0, 0, 10, 10, char_work);
	DC_FlushRange( char_work,POKEGRA_VRAM_SIZE );	// 転送前にメモリ安定

	// OAM用VRAMに転送
	GX_LoadOBJ( char_work, POKEGRA_VRAM_OFFSET, POKEGRA_VRAM_SIZE );

	// パレット転送
	ArcUtil_PalSet( ssa.arc_no, ssa.index_pal, PALTYPE_MAIN_OBJ, 0x20*13, 32, HEAPID_WORLDTRADE );
	
	// ワーク解放
	sys_FreeMemoryEz(char_work);
}


//------------------------------------------------------------------
/**
 * @brief   ほしいポケモンの部分を再描画
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void WantPokePrintReWrite( WORLDTRADE_WORK *wk )
{

	// ほしいポケモンの条件
	WodrldTrade_MyPokeWantPrint( wk->MsgManager, wk->MonsNameManager, wk->WordSet, 
				&wk->InfoWin[7], 
				wk->UploadPokemonData.wantSimple.characterNo,
				wk->UploadPokemonData.wantSimple.gender,
				WorldTrade_LevelTermGet(wk->UploadPokemonData.wantSimple.level_min,wk->UploadPokemonData.wantSimple.level_max));


}