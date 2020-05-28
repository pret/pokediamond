//============================================================================================
/**
 * @file	worldtrade_box.c
 * @bfief	世界交換えせボックス画面処理
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
#include "poketool/pokeicon.h"
#include "poketool/pokeparty.h"
#include "itemtool/item.h"

#include "savedata/wifilist.h"
#include "savedata/zukanwork.h"

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "msgdata/msg_wifi_lobby.h"
#include "msgdata/msg_wifi_gtc.h"


#include "worldtrade.naix"			// グラフィックアーカイブ定義


//============================================================================================
//	型宣言
//============================================================================================
#define POKEICON_TRANS_CHARA	(4*4)
#define POKEICON_TRANS_SIZE		(POKEICON_TRANS_CHARA*0x20)

typedef struct {
  int vadrs;				// VRAMアドレス
  int palno;				// パレット番号
  CLACT_WORK_PTR icon;			// CLACT
  u8 chbuf[POKEICON_TRANS_SIZE];	// キャラクタバッファ
} WORLDTRADE_POKEBUF;



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
static int SubSeq_Start( WORLDTRADE_WORK *wk);
static int SubSeq_Main( WORLDTRADE_WORK *wk);
static int SubSeq_End( WORLDTRADE_WORK *wk);
static int SubSeq_YesNo( WORLDTRADE_WORK *wk);
static int SubSeq_YesNoSelect( WORLDTRADE_WORK *wk);
static int SubSeq_MessageWait( WORLDTRADE_WORK *wk );
static int SubSeq_MessageClearWait( WORLDTRADE_WORK *wk );
static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat, int winflag );
static void TransPokeIconCharaPal( int pokeno, int form, int tamago, int no, CLACT_WORK_PTR icon, ARCHANDLE* handle, WORLDTRADE_POKEBUF *pbuf );
static void NowBoxPageInfoGet( WORLDTRADE_WORK *wk, int now);
static int RoundWork( int num, int max, int move );
static void CursorControl( WORLDTRADE_WORK *wk );
static int SubSeq_SelectList( WORLDTRADE_WORK *wk );
static int SubSeq_SelectWait( WORLDTRADE_WORK *wk );
static int SubSeq_ExchangeSelectList( WORLDTRADE_WORK *wk );
static int SubSeq_ExchangeSelectWait( WORLDTRADE_WORK *wk );
static int SubSeq_CBallYesNoSelect( WORLDTRADE_WORK *wk );
static int SubSeq_CBallYesNo( WORLDTRADE_WORK *wk );
static int SubSeq_CBallYesNoMessage( WORLDTRADE_WORK *wk );
static int SubSeq_CBallDepositYesNoMessage( WORLDTRADE_WORK *wk );
static int SubSeq_CBallDepositYesNo( WORLDTRADE_WORK *wk );
static int SubSeq_CBallDepositYesNoSelect( WORLDTRADE_WORK *wk );


static int WantPokeCheck(POKEMON_PASO_PARAM *ppp, Dpw_Tr_PokemonSearchData *dtsd);
static void MakeExchangePokemonData( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk );
//static void PokemonIconSet( POKEMON_PASO_PARAM *paso, CLACT_WORK_PTR icon, CLACT_WORK_PTR itemact, u16 *no, int pos );
static void PokemonIconSet( POKEMON_PASO_PARAM *paso, CLACT_WORK_PTR icon, CLACT_WORK_PTR itemact, u16 *no, int pos, ARCHANDLE* handle, Dpw_Tr_PokemonDataSimple *dat, WORLDTRADE_POKEBUF *pbuf );
void* CharDataGetbyHandle( ARCHANDLE *handle, u32 dataIdx, NNSG2dCharacterData** charData, u32 heapID );
static int CompareSearchData( Dpw_Tr_PokemonDataSimple *poke,  Dpw_Tr_PokemonSearchData *search );
static void PokeIconPalSet( Dpw_Tr_PokemonDataSimple *box, CLACT_WORK_PTR *icon, Dpw_Tr_PokemonSearchData *want, WORLDTRADE_POKEBUF *pbuf);
static int CheckPocket( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos );
static int PokemonCheck( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos  );
static int ExchangeCheck( WORLDTRADE_WORK *wk );
static int PokeRibbonCheck( POKEMON_PASO_PARAM *ppp );

#define WANT_POKE_NO		( 0 )
#define WANT_POKE_OK		( 1 )
#define WANT_POKE_TAMAGO	( 2 )

enum{
	SUBSEQ_START=0,
	SUBSEQ_MAIN,
	SUBSEQ_END,
	SUBSEQ_MES_WAIT,
	SUBSEQ_MES_CLEAR_WAIT,
	SUBSEQ_YESNO,
	SUBSEQ_YESNO_SELECT,
	SUBSEQ_SELECT_LIST,
	SUBSEQ_SELECT_WAIT,
	SUBSEQ_EXCHANGE_SELECT_LIST,
	SUBSEQ_EXCHANGE_SELECT_WAIT,

	SUBSEQ_CBALL_YESNO_MES,
	SUBSEQ_CBALL_YESNO,
	SUBSEQ_CBALL_YESNO_SELECT,

	SUBSEQ_CBALL_DEPOSIT_YESNO_MES,
	SUBSEQ_CBALL_DEPOSIT_YESNO,
	SUBSEQ_CBALL_DEPOSIT_YESNO_SELECT,
};

static int (*Functable[])( WORLDTRADE_WORK *wk ) = {
	SubSeq_Start,			// SUBSEQ_START=0,
	SubSeq_Main,            // SUBSEQ_MAIN,
	SubSeq_End,             // SUBSEQ_END,
	SubSeq_MessageWait,     // SUBSEQ_MES_WAIT
	SubSeq_MessageClearWait,// SUBSEQ_MES_CLEAR_WAIT
	SubSeq_YesNo,			// SUBSEQ_YESNO
	SubSeq_YesNoSelect,		// SUBSEQ_YESNO_SELECT
	SubSeq_SelectList,		// SUBSEQ_SELECT_LIST
	SubSeq_SelectWait,		// SUBSEQ_SELECT_WAIT
	SubSeq_ExchangeSelectList,	// SUBSEQ_EXCHANGE_SELECT_LIST
	SubSeq_ExchangeSelectWait,	// SUBSEQ_EXCHANGE_SELECT_WAIT

	SubSeq_CBallYesNoMessage,	// SUBSEQ_CBALL_YESNO_MES
	SubSeq_CBallYesNo,			// SUBSEQ_CBALL_YESNO
	SubSeq_CBallYesNoSelect,	// SUBSEQ_CBALL_YESNO_SELECT

	SubSeq_CBallDepositYesNoMessage,	// SUBSEQ_CBALL_YESNO_MES
	SubSeq_CBallDepositYesNo,			// SUBSEQ_CBALL_YESNO
	SubSeq_CBallDepositYesNoSelect,	// SUBSEQ_CBALL_YESNO_SELECT
};

#define BOX_CUROSOR_END_POS			( 30 )
#define BOX_CUROSOR_TRAYNAME_POS	( 31 )


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
int WorldTrade_Box_Init(WORLDTRADE_WORK *wk, int seq)
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

	// ステータス画面からもどってきたときは両画面フェード
	if(wk->old_sub_process==WORLDTRADE_STATUS){
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_box.c [179] MS ********************\n" );
#endif
	}else{
		// それ以外は上画面だけフェード
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_box.c [183] M ********************\n" );
#endif
	}
	NowBoxPageInfoGet(wk, wk->BoxTrayNo);

	// 通信状態を確認してアイコンの表示を変える
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
int WorldTrade_Box_Main(WORLDTRADE_WORK *wk, int seq)
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
int WorldTrade_Box_End(WORLDTRADE_WORK *wk, int seq)
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
			2, 0, 0, FALSE
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

	// 上下画面ＢＧパレット転送
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_mybox_nclr, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_WORLDTRADE);
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_traderoom_nclr, PALTYPE_SUB_BG,  0, 16*8*2,  HEAPID_WORLDTRADE);
	
	// 会話フォントパレット転送
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );
	// TalkFontPaletteLoad( PALTYPE_SUB_BG,  WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );

	// 会話ウインドウグラフィック転送
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MESFRAME_CHR, 
						WORLDTRADE_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_WORLDTRADE );

	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MENUFRAME_CHR,
						WORLDTRADE_MENUFRAME_PAL, 0, HEAPID_WORLDTRADE );



	// メイン画面BG1キャラ転送
	ArcUtil_BgCharSet( ARC_WORLDTRADE_GRA, NARC_worldtrade_mybox_lz_ncgr, bgl, GF_BGL_FRAME1_M, 0, 16*5*0x20, 1, HEAPID_WORLDTRADE);

	// メイン画面BG1スクリーン転送
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_mybox_lz_nscr, bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);

	// メイン画面BG2スクリーン転送
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_title_base_lz_nscr, bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);


}
#define BOX_SX		( 25 )
#define BOX_SY		( 60 )
#define BOX_W		( 26 )
#define BOX_H		( 24 )

static const u16 PokemonIconPosTbl[][2]={
	{BOX_SX+BOX_W*0, BOX_SY+BOX_H*0},{BOX_SX+BOX_W*1, BOX_SY+BOX_H*0},{BOX_SX+BOX_W*2, BOX_SY+BOX_H*0},
	{BOX_SX+BOX_W*3, BOX_SY+BOX_H*0},{BOX_SX+BOX_W*4, BOX_SY+BOX_H*0},{BOX_SX+BOX_W*5, BOX_SY+BOX_H*0},

	{BOX_SX+BOX_W*0, BOX_SY+BOX_H*1},{BOX_SX+BOX_W*1, BOX_SY+BOX_H*1},{BOX_SX+BOX_W*2, BOX_SY+BOX_H*1},
	{BOX_SX+BOX_W*3, BOX_SY+BOX_H*1},{BOX_SX+BOX_W*4, BOX_SY+BOX_H*1},{BOX_SX+BOX_W*5, BOX_SY+BOX_H*1},

	{BOX_SX+BOX_W*0, BOX_SY+BOX_H*2},{BOX_SX+BOX_W*1, BOX_SY+BOX_H*2},{BOX_SX+BOX_W*2, BOX_SY+BOX_H*2},
	{BOX_SX+BOX_W*3, BOX_SY+BOX_H*2},{BOX_SX+BOX_W*4, BOX_SY+BOX_H*2},{BOX_SX+BOX_W*5, BOX_SY+BOX_H*2},

	{BOX_SX+BOX_W*0, BOX_SY+BOX_H*3},{BOX_SX+BOX_W*1, BOX_SY+BOX_H*3},{BOX_SX+BOX_W*2, BOX_SY+BOX_H*3},
	{BOX_SX+BOX_W*3, BOX_SY+BOX_H*3},{BOX_SX+BOX_W*4, BOX_SY+BOX_H*3},{BOX_SX+BOX_W*5, BOX_SY+BOX_H*3},

	{BOX_SX+BOX_W*0, BOX_SY+BOX_H*4},{BOX_SX+BOX_W*1, BOX_SY+BOX_H*4},{BOX_SX+BOX_W*2, BOX_SY+BOX_H*4},
	{BOX_SX+BOX_W*3, BOX_SY+BOX_H*4},{BOX_SX+BOX_W*4, BOX_SY+BOX_H*4},{BOX_SX+BOX_W*5, BOX_SY+BOX_H*4},
	{ 224,175 },{98, 32}
};


static const u16 BoxArrowPos[][2]={
	{162, 36 },
	{ 22, 36,}
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
	int i;
	//登録情報格納
	CLACT_ADD add;
	WorldTrade_MakeCLACT( &add,  wk, &wk->clActHeader_main, NNS_G2D_VRAM_TYPE_2DMAIN );


	// ポケモンをさす指
	add.mat.x = FX32_ONE *   PokemonIconPosTbl[wk->BoxCursorPos][0];
	add.mat.y = FX32_ONE *   PokemonIconPosTbl[wk->BoxCursorPos][1];
	wk->CursorActWork = CLACT_Add(&add);
	CLACT_SetAnmFlag(wk->CursorActWork,1);
	CLACT_AnmChg( wk->CursorActWork, 4 );	
	CLACT_BGPriorityChg( wk->CursorActWork, 1 );
	
	// ポケモンアイコン
	for(i=0;i<BOX_POKE_NUM;i++){
		add.mat.x = FX32_ONE *   PokemonIconPosTbl[i][0];
		add.mat.y = FX32_ONE *   PokemonIconPosTbl[i][1];
		add.pri   = 20;
		wk->PokeIconActWork[i] = CLACT_Add(&add);
		CLACT_AnmChg( wk->PokeIconActWork[i], 6+i );	
		CLACT_BGPriorityChg( wk->PokeIconActWork[i], 1 );
	}

	// アイテムアイコン
	for(i=0;i<BOX_POKE_NUM;i++){
		add.mat.x = FX32_ONE *   ( PokemonIconPosTbl[i][0]+4);
		add.mat.y = FX32_ONE *   ( PokemonIconPosTbl[i][1]+6);
		add.pri   = 10;
		wk->ItemIconActWork[i] = CLACT_Add(&add);
		CLACT_AnmChg( wk->ItemIconActWork[i], CELL_ITEMICON_NO );	
		CLACT_BGPriorityChg( wk->ItemIconActWork[i], 1 );

	}

	// ボールカプセルアイコン
	for(i=0;i<TEMOTI_POKEMAX;i++){
		add.mat.x = FX32_ONE *   ( PokemonIconPosTbl[i][0]+4+8);
		add.mat.y = FX32_ONE *   ( PokemonIconPosTbl[i][1]+6);
		add.pri   = 10;
		wk->CBallActWork[i] = CLACT_Add(&add);
		CLACT_AnmChg( wk->CBallActWork[i], CELL_CBALLICON_NO );	
		CLACT_BGPriorityChg( wk->CBallActWork[i], 1 );

	}

	// ボックス切り替えの矢印
	for(i=0;i<2;i++){
		add.mat.x = FX32_ONE * BoxArrowPos[i][0];
		add.mat.y = FX32_ONE * BoxArrowPos[i][1];
		wk->BoxArrowActWork[i] = CLACT_Add(&add);
		CLACT_SetAnmFlag( wk->BoxArrowActWork[i], 1 );
		CLACT_AnmChg( wk->BoxArrowActWork[i], CELL_BOXARROW_NO+i );	
		CLACT_BGPriorityChg( wk->BoxArrowActWork[i], 1 );
	}
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
	int i;

	// ボックス横の矢印２こ
	for(i=0;i<2;i++){
		CLACT_Delete(wk->BoxArrowActWork[i]);
	}

	// カーソル削除
	CLACT_Delete(wk->CursorActWork);

	// ポケモンアイコン削除
	for(i=0;i<BOX_POKE_NUM;i++){
		CLACT_Delete(wk->PokeIconActWork[i]);
		CLACT_Delete(wk->ItemIconActWork[i]);
	}
	// カスタムボールアイコン削除
	for(i=0;i<TEMOTI_POKEMAX;i++){
		CLACT_Delete(wk->CBallActWork[i]);
	}

}

#define SELECT_MENU_X	(  21 )
#define SELECT_MENU_Y 	(  13 )
#define SELECT_MENU_SX	( 5*2 )
#define SELECT_MENU_SY	(   6 )


#define BOX_TRAY_NAME_X		(  5 )
#define BOX_TRAY_NAME_Y		(  3 )
#define BOX_TRAY_NAME_SX	( 13 )
#define BOX_TRAY_NAME_SY	(  3 )

#define END_TEXT_X			( 25 )
#define END_TEXT_Y			( 21 )
#define END_TEXT_SX			(  6 )
#define END_TEXT_SY			(  2 )


#define TITLE_MESSAGE_OFFSET   ( WORLDTRADE_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define BOX_TRAY_NAME_OFFSET   ( TITLE_MESSAGE_OFFSET     + TITLE_TEXT_SX*TITLE_TEXT_SY )
#define LINE_MESSAGE_OFFSET    ( BOX_TRAY_NAME_OFFSET     + BOX_TRAY_NAME_SX*BOX_TRAY_NAME_SX )
#define TALK_MESSAGE_OFFSET	   ( LINE_MESSAGE_OFFSET      + LINE_TEXT_SX*LINE_TEXT_SY )
#define END_MESSAGE_OFFSET	   ( TALK_MESSAGE_OFFSET      + TALK_WIN_X*TALK_WIN_Y )
#define SELECT_MENU_OFFSET 	   ( END_MESSAGE_OFFSET       + END_TEXT_SX*END_TEXT_SY )
#define YESNO_OFFSET 		   ( SELECT_MENU_OFFSET       + SELECT_MENU_SX*SELECT_MENU_SY )

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
	
	// あずけるポケモンをえらんでください
	WorldTrade_SysPrint( &wk->TitleWin, wk->TitleString, 0, 1, 0, GF_PRINTCOLOR_MAKE(15,14,0) );


	// ボックストレイ名BMPWIN確保
	
	GF_BGL_BmpWinAdd(wk->bgl, &wk->SubWin, GF_BGL_FRAME0_M,
	BOX_TRAY_NAME_X, BOX_TRAY_NAME_Y, BOX_TRAY_NAME_SX, BOX_TRAY_NAME_SY, WORLDTRADE_TALKFONT_PAL,  
	BOX_TRAY_NAME_OFFSET  );
	GF_BGL_BmpWinDataFill( &wk->SubWin, 0x0000 );
	GF_BGL_BmpWinOn(&wk->SubWin);
	
	// 一行ウインドウ
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		LINE_TEXT_X, LINE_TEXT_Y, LINE_TEXT_SX, LINE_TEXT_SY, 
		WORLDTRADE_TALKFONT_PAL,  LINE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0000 );

	// 2行ウインドウ
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TalkWin, GF_BGL_FRAME0_M,
		TALK_WIN_X, TALK_WIN_Y, TALK_WIN_SX, TALK_WIN_SY, 
		WORLDTRADE_TALKFONT_PAL,  TALK_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->TalkWin, 0x0000 );

	// やめる
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[1], GF_BGL_FRAME1_M,
		END_TEXT_X, END_TEXT_Y, END_TEXT_SX, END_TEXT_SY, 
		0,  END_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->MenuWin[1], 0x0606 );
	// 「もどる」描画
	WorldTrade_SysPrint( &wk->MenuWin[1], wk->EndString, 0, 1, 1, GF_PRINTCOLOR_MAKE(1,3,6) );

	// 選択メニュー領域
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[0], GF_BGL_FRAME0_M,
		SELECT_MENU_X, SELECT_MENU_Y, SELECT_MENU_SX, SELECT_MENU_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU_OFFSET );	


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
	GF_BGL_BmpWinDel( &wk->TalkWin );
	GF_BGL_BmpWinDel( &wk->MenuWin[1] );
	GF_BGL_BmpWinDel( &wk->MenuWin[0] );
	GF_BGL_BmpWinDel( &wk->MsgWin );
	GF_BGL_BmpWinDel( &wk->SubWin );
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

	// ボックストレイ名文字列バッファ
	wk->BoxTrayNameString = STRBUF_Create( BOX_TRAY_NAME_BUF_NUM, HEAPID_WORLDTRADE );

	// 文字列バッファ作成
	wk->TalkString  = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WORLDTRADE );

	// 「あずけるポケモンをえらんでください」「かわりのポケモンをえらんでください」
	if(wk->sub_process_mode==MODE_DEPOSIT_SELECT){
		wk->TitleString = MSGMAN_AllocString( wk->MsgManager, msg_gtc_01_022 );
	}else if(wk->sub_process_mode==MODE_EXCHANGE_SELECT){
		wk->TitleString = MSGMAN_AllocString( wk->MsgManager, msg_gtc_01_018 );
	}

	// もどる
	wk->EndString   = MSGMAN_AllocString( wk->MsgManager, msg_gtc_05_014 );

	if(wk->BoxCursorPos==BOX_CUROSOR_END_POS){
		wk->BoxCursorPos = 0;
	}
	
	// ボックス用ワーク
	wk->boxWork = sys_AllocMemory(HEAPID_WORLDTRADE, sizeof(BOX_RESEARCH));

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
	sys_FreeMemoryEz(wk->boxWork);

	STRBUF_Delete( wk->BoxTrayNameString );
	STRBUF_Delete( wk->TalkString ); 
	STRBUF_Delete( wk->EndString ); 
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
	if(WIPE_SYS_EndCheck()){
//		SubSeq_MessagePrint( wk, msg_gtc_01_018, 1, 0, 0x0f0f );
//		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );
		wk->subprocess_seq = SUBSEQ_MAIN;
	}

	return SEQ_MAIN;
}
/* 
       31

 0  1  2  3  4  5
 6  7  8  9 10 11
12 13 14 15 16 17
18 19 20 21 22 23
24 25 26 27 28 29 30

 */

static const u8 box_pos_table[][4]={
	// 上下左右
	{31, 6, 5, 1,},{31, 7, 0, 2,},{31, 8, 1, 3,},{31, 9, 2, 4,},{31,10, 3, 5,},{31,11, 4, 0,},
	{ 0,12,11, 7,},{ 1,13, 6, 8,},{ 2,14, 7, 9,},{ 3,15, 8,10,},{ 4,16, 9,11,},{ 5,17,10, 6,},
	{ 6,18,17,13,},{ 7,19,12,14,},{ 8,20,13,15,},{ 9,21,14,16,},{10,22,15,17,},{11,23,16,12,},
	{12,24,23,19,},{13,25,18,20,},{14,26,19,21,},{15,27,20,22,},{16,28,21,23,},{17,29,22,18,},
	{18,31,30,25,},{19,31,24,26,},{20,31,25,27,},{21,31,26,28,},{22,31,27,29,},{23,31,28,30,},{30,30,29,24},
	{ 26,2,99,101, },

};

static const s8 movetbl[][2]={
	{0,0},{0,-1},{0,1},{1,0},{-1,0},
};

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
	CursorControl(wk);

	// あずける時
	if(wk->sub_process_mode==MODE_DEPOSIT_SELECT){
		if(sys.trg & PAD_BUTTON_B){
			// タイトルメニューにもどる
			WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
			wk->subprocess_seq = SUBSEQ_END;

		}else if(sys.trg & PAD_BUTTON_DECIDE){
			if(wk->BoxCursorPos == BOX_CUROSOR_END_POS){
			// タイトルメニューにもどる
				WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
				wk->subprocess_seq = SUBSEQ_END;
				Snd_SePlay(WORLDTRADE_DECIDE_SE);
			}else{
				if(wk->BoxCursorPos!=BOX_CUROSOR_TRAYNAME_POS){
					Snd_SePlay(WORLDTRADE_DECIDE_SE);
					// ●●●をあずけますか？
					switch(PokemonCheck( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos )){
					// だせる
					case WANT_POKE_OK:
						if(CheckPocket( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos )){
							WORDSET_RegisterPokeNickName( wk->WordSet, 0, 
									WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos) );
							SubSeq_MessagePrint( wk, msg_gtc_01_023, 1, 0, 0x0f0f, 0 );
							WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT,  SUBSEQ_SELECT_LIST);
							OS_Printf("deposit_ppp0 = %08x\n",WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos));
						}else{
							// てもちの最後の1匹だった場合はだせない
							SubSeq_MessagePrint( wk, msg_gtc_01_027, 1, 0, 0x0f0f, 1 );
							WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN);
						}
						break;
					// タマゴはだせない
					case WANT_POKE_TAMAGO:
						SubSeq_MessagePrint( wk, msg_gtc_01_028, 1, 0, 0x0f0f, 1 );
						WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN);
						break;
					// 特殊リボンがついているのでダメ
					}
				}
			}
		}
		
	// 交換するとき
	}else if(wk->sub_process_mode==MODE_EXCHANGE_SELECT){
		if(sys.trg & PAD_BUTTON_CANCEL){
			// 検索結果ポケモンの画面にもどる
			WorldTrade_SubProcessChange( wk, WORLDTRADE_PARTNER, 0 );
			wk->subprocess_seq  = SUBSEQ_END;
			Snd_SePlay(WORLDTRADE_DECIDE_SE);
		}else if(sys.trg & PAD_BUTTON_DECIDE){
			if(wk->BoxCursorPos == BOX_CUROSOR_END_POS){
				// サーバーチェックの後タイトルメニューへ
				WorldTrade_SubProcessChange( wk, WORLDTRADE_PARTNER, 0 );
				wk->subprocess_seq  = SUBSEQ_END;
				Snd_SePlay(WORLDTRADE_DECIDE_SE);
			}else{
				if(wk->BoxCursorPos!=BOX_CUROSOR_TRAYNAME_POS){
					// ●●●を交換にだしますか？
					switch(PokemonCheck( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos )){
					case WANT_POKE_OK:
						{
							POKEMON_PASO_PARAM *ppp = WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos);

							// 名前を取得してWordSetに登録
							if(WantPokeCheck( ppp, &wk->DownloadPokemonData[wk->TouchTrainerPos].wantSimple)){
								if(CheckPocket( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos )){
									WORDSET_RegisterPokeNickName( wk->WordSet, 0, ppp);
									SubSeq_MessagePrint( wk, msg_gtc_01_019, 1, 0, 0x0f0f, 0 );
									WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT,  SUBSEQ_EXCHANGE_SELECT_LIST);
									OS_Printf("deposit_ppp0 = %08x\n",WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos));
									Snd_SePlay(WORLDTRADE_DECIDE_SE);
								}else{
									// てもちの最後の1匹だった場合はだせない
									SubSeq_MessagePrint( wk, msg_gtc_01_027, 1, 0, 0x0f0f, 1 );
									WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN);
								}
							}else{
								Snd_SePlay(SE_CANCEL);
							}
						}
						break;
					case WANT_POKE_TAMAGO: case WANT_POKE_NO:
						Snd_SePlay(SE_CANCEL);
						break;
					}
				}
			}
		}
	}


	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   カーソル制御
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorControl( WORLDTRADE_WORK *wk )
{
	int move=0, arrow=0, tmp=0;

	// カーソル操作
	if(sys.trg & PAD_KEY_UP){
		arrow = 1;
	}else if(sys.trg & PAD_KEY_DOWN){
		arrow = 2;
	}else if(sys.trg & PAD_KEY_LEFT){
		arrow = 3;
	}else if(sys.trg & PAD_KEY_RIGHT){
		arrow = 4;
	}

	// 上下左右が入った？
	if(arrow!=0){
		tmp = box_pos_table[wk->BoxCursorPos][arrow-1];
		if(tmp!=wk->BoxCursorPos){
			if(tmp==99||tmp==101){
				wk->BoxTrayNo = RoundWork( wk->BoxTrayNo, 19, tmp-100);
				NowBoxPageInfoGet( wk, wk->BoxTrayNo );
				Snd_SePlay(WORLDTRADE_DECIDE_SE);
			}else{
				move = 1;
				wk->BoxCursorPos = tmp;
			}
		}
	}
	
	// 移動した？
	if(move){
		Snd_SePlay(WORLDTRADE_MOVE_SE);
		WorldTrade_ActPos(wk->CursorActWork, 
			PokemonIconPosTbl[wk->BoxCursorPos][0],
			PokemonIconPosTbl[wk->BoxCursorPos][1]);
	}

	// カーソルプライオリティ操作
	if(wk->BoxCursorPos==31 || (wk->BoxCursorPos>=0 && wk->BoxCursorPos<=5)){
		// ボックストレイ名の上にあるときとボックス１列目にいるときは最上位に
		CLACT_BGPriorityChg( wk->CursorActWork, 0 );
	}else{
		// それ以外はひとつ下に
		CLACT_BGPriorityChg( wk->CursorActWork, 1 );
	}

}


//------------------------------------------------------------------
/**
 * $brief   numにmoveを足し,0以下ならmax-1に、maxなら0にして返す
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
	temp.y_max = 3;
	temp.line_spc = 0;
	temp.c_disp_f = 0;
	temp.loop_f   = 0;


	wk->BmpMenuList = BMP_MENULIST_Create( 3, HEAPID_WORLDTRADE );
	// ようすをみる
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_05_005, 1 );
	// あずける
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_05_006, 2 );
	// やめる
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_05_007, 3 );

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
 * $brief   「ようすをみる」「あずける」「やめる」選択待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SelectWait( WORLDTRADE_WORK *wk )
{
	switch(BmpMenuMain( wk->BmpMenuWork )){
	// 「ようすをみる」
	case 1:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		wk->subprocess_seq  = SUBSEQ_END;
		WorldTrade_SubProcessChange( wk, WORLDTRADE_STATUS, MODE_DEPOSIT_SELECT );
		break;

	// 「あずける」
	case 2:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );

		if( PokeRibbonCheck( WorldTrade_GetPokePtr( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos)) ){
			SubSeq_MessagePrint( wk, msg_gtc_01_038, 1, 0, 0x0f0f, 1 );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN);
		}else{
			int flag = 0;
			// てもちのときはカスタムボールチェック
			if(WorldTrade_GetPPorPPP( wk->BoxTrayNo )){
				POKEMON_PARAM *pp;
				pp = PokeParty_GetMemberPointer(wk->param->myparty, wk->BoxCursorPos);
				if(PokeParaGet( pp, ID_PARA_cb_id, NULL )){
					flag = 1;
					wk->subprocess_seq = SUBSEQ_CBALL_DEPOSIT_YESNO_MES;
				}
				OS_Printf("てもち指定 カスタム=%d\n", PokeParaGet( pp, ID_PARA_cb_id, NULL ));
			}

			// 問題なければポケモン預けへ
			if(flag==0){
				wk->deposit_ppp     = WorldTrade_GetPokePtr( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos );
				wk->subprocess_seq  = SUBSEQ_END;
				 WorldTrade_SubProcessChange( wk, WORLDTRADE_DEPOSIT, 0 );
				OS_Printf("deposit_ppp1 = %08x\n",WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos));
			}
		}
		break;
		
	// 「やめる」
	case 3:case BMPMENU_CANCEL:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
		wk->subprocess_seq  = SUBSEQ_MAIN;

		break;
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
static int SubSeq_ExchangeSelectList( WORLDTRADE_WORK *wk )
{
	BMPMENU_HEADER temp;

	temp.font  = FONT_SYSTEM;
	temp.x_max = 1;
	temp.y_max = 3;
	temp.line_spc = 0;
	temp.c_disp_f = 0;
	temp.loop_f   = 0;


	wk->BmpMenuList = BMP_MENULIST_Create( 3, HEAPID_WORLDTRADE );
	// ようすをみる
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_04_018, 1 );
	// こうかんする
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_04_019, 2 );
	// やめる
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_04_020, 3 );

	temp.menu = wk->BmpMenuList;
	temp.win  = &wk->MenuWin[0];

	// 枠描画
	BmpMenuWinWrite( &wk->MenuWin[0], WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMPメニュー開始
	wk->BmpMenuWork = BmpMenuAddEx( &temp, 9, 0, 0, HEAPID_WORLDTRADE, PAD_BUTTON_B );


	wk->subprocess_seq = SUBSEQ_EXCHANGE_SELECT_WAIT;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * $brief   「ようすをみる」「こうかんする」「やめる」選択待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_ExchangeSelectWait( WORLDTRADE_WORK *wk )
{
	switch(BmpMenuMain( wk->BmpMenuWork )){
	// 「ようすをみる」
	case 1:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		wk->subprocess_seq  = SUBSEQ_END;
		 WorldTrade_SubProcessChange( wk, WORLDTRADE_STATUS, MODE_EXCHANGE_SELECT );
		break;

	// 「こうかんする」
	case 2:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );

		if( PokeRibbonCheck( WorldTrade_GetPokePtr( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos))){
			SubSeq_MessagePrint( wk, msg_gtc_01_038, 1, 0, 0x0f0f, 1 );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN);
		}else{
			int flag = 0;
			// てもちのときはカスタムボールチェック
			if(WorldTrade_GetPPorPPP( wk->BoxTrayNo )){
				POKEMON_PARAM *pp;
				pp = PokeParty_GetMemberPointer(wk->param->myparty, wk->BoxCursorPos);
				if(PokeParaGet( pp, ID_PARA_cb_id, NULL )){
					flag = 1;
					wk->subprocess_seq = SUBSEQ_CBALL_YESNO_MES;
				}
				OS_Printf("てもち指定 カスタム=%d\n", PokeParaGet( pp, ID_PARA_cb_id, NULL ));
			}
			
			// 問題なければ交換へ
			if(flag==0){
				ExchangeCheck(wk);
			}
		}
		break;
		
	// 「やめる」
	case 3:case BMPMENU_CANCEL:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
		wk->subprocess_seq  = SUBSEQ_MAIN;

		break;
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
static int SubSeq_End( WORLDTRADE_WORK *wk )
{
	// 接続画面だったら、上下画面でフェード
	if(wk->sub_nextprocess==WORLDTRADE_ENTER || wk->sub_nextprocess==WORLDTRADE_STATUS){
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_box.c [1164] MS ********************\n" );
#endif
		wk->sub_out_flg = 1;
	}else{
		// 続きの画面にいく場合は上画面だけフェード
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_box.c [1169] M ********************\n" );
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
			// タイトルメニューを終了
			wk->subprocess_seq  = SUBSEQ_END;
			 WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
		}
	}

	return SEQ_MAIN;
	
}



//------------------------------------------------------------------
/**
 * @brief   「ボールカプセルが外れますが、よろしいですか？」
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallYesNoMessage( WORLDTRADE_WORK *wk )
{
	SubSeq_MessagePrint( wk, msg_gtc_01_026, 1, 0, 0x0f0f, 1 );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT,  SUBSEQ_CBALL_YESNO );

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * $brief   ボールカプセルが外れますが・・・はい・いいえ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallYesNo( WORLDTRADE_WORK *wk )
{
	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY2, YESNO_OFFSET );
	wk->subprocess_seq = SUBSEQ_CBALL_YESNO_SELECT;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * $brief   ボールカプセルが外れますが・・・・・はい・いいえ選択
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallYesNoSelect( WORLDTRADE_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WORLDTRADE );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// もういっかい
			BmpTalkWinClear( &wk->TalkWin, WINDOW_TRANS_ON );
			wk->subprocess_seq  = SUBSEQ_MAIN;
		}else{
			// 交換へ
			ExchangeCheck(wk);
		}
	}

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * @brief   交換するためのチェック
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ExchangeCheck( WORLDTRADE_WORK *wk )
{
	POKEMON_PARAM *pp;
	pp = (POKEMON_PARAM*)wk->DownloadPokemonData[wk->TouchTrainerPos].postData.data;

	// あいてのポケモンにメールがついていて、自分のてもちが６ひきだったときは交換できない。
	if(WorldTrade_PokemonMailCheck(pp) && wk->BoxTrayNo!=18){
		if(PokeParty_GetPokeCount(wk->param->myparty)==6){
			SubSeq_MessagePrint( wk, msg_gtc_01_029, 1, 0, 0x0f0f, 1 );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN );
			return 0;
		}
	}

	wk->deposit_ppp     = WorldTrade_GetPokePtr( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos );
	wk->subprocess_seq  = SUBSEQ_END;
	wk->sub_out_flg = 1;
	WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_EXCHANGE );
	OS_Printf("deposit_ppp1 = %08x\n",WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos));

	MakeExchangePokemonData( &wk->UploadPokemonData, wk );

	// 検索ヒット数をクリアしておかないと、デモ終了後にＯＢＪが表示されてしまう
	wk->SearchResult = 0;

	return 1;
}

//------------------------------------------------------------------
/**
 * @brief   「ボールカプセルが外れますが、よろしいですか？」
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallDepositYesNoMessage( WORLDTRADE_WORK *wk )
{
	SubSeq_MessagePrint( wk, msg_gtc_01_026, 1, 0, 0x0f0f, 1 );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT,  SUBSEQ_CBALL_DEPOSIT_YESNO );

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * $brief   ボールカプセルが外れますが・・・はい・いいえ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallDepositYesNo( WORLDTRADE_WORK *wk )
{
	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY2, YESNO_OFFSET );
	wk->subprocess_seq = SUBSEQ_CBALL_DEPOSIT_YESNO_SELECT;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * $brief   ボールカプセルが外れますが・・・・・はい・いいえ選択
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallDepositYesNoSelect( WORLDTRADE_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WORLDTRADE );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// もういっかい
			BmpTalkWinClear( &wk->TalkWin, WINDOW_TRANS_ON );
			wk->subprocess_seq  = SUBSEQ_MAIN;
		}else{
			// 交換へ
			wk->deposit_ppp     = WorldTrade_GetPokePtr( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos );
			wk->subprocess_seq  = SUBSEQ_END;
			 WorldTrade_SubProcessChange( wk, WORLDTRADE_DEPOSIT, 0 );
			OS_Printf("deposit_ppp1 = %08x\n",WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos));
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
 * $brief   会話終了を待ってウインドウを消去し、次のシーケンスへ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_MessageClearWait( WORLDTRADE_WORK *wk )
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		BmpTalkWinClear( &wk->TalkWin, WINDOW_TRANS_ON );
		wk->subprocess_seq = wk->subprocess_nextseq;
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
static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat, int winflag )
{
	GF_BGL_BMPWIN *win;
	
	// 文字列取得
	STRBUF *tempbuf;
	
	// 文字列取得
	tempbuf = MSGMAN_AllocString(  wk->MsgManager, msgno );

	// WORDSET展開
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );
	

	if(winflag==0){
		win = &wk->MsgWin;
	}else{
		win = &wk->TalkWin;
	}
	// 会話ウインドウ枠描画
	GF_BGL_BmpWinDataFill( win,  0x0f0f );
	BmpTalkWinWrite( win, WINDOW_TRANS_ON, WORLDTRADE_MESFRAME_CHR, WORLDTRADE_MESFRAME_PAL );

	// 文字列描画開始
	wk->MsgIndex = GF_STR_PrintSimple( win, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);

	STRBUF_Delete(tempbuf);
}


//==============================================================================
/**
 * @brief   ポケモンアイコンの読み込みを速くするためにハンドルを開いたハンドルから読み込む
 *
 * @param   handle		
 * @param   dataIdx		
 * @param   charData		
 * @param   heapID		
 *
 * @retval  void*		
 */
//==============================================================================
void* CharDataGetbyHandle( ARCHANDLE *handle, u32 dataIdx, NNSG2dCharacterData** charData, u32 heapID )
{
	void* arcData = ArchiveDataLoadAllocByHandle( handle, dataIdx, heapID );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedBGCharacterData( arcData, charData ) == FALSE)
		{
			// 失敗したらNULL
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}

//------------------------------------------------------------------
/**
 * $brief   ポケモンアイコンを転送してアクターのパレットを合わせる
 *
 * @param   chara		
 * @param   pokeno		
 * @param   no		
 * @param   icon		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransPokeIconCharaPal( int pokeno, int form, int tamago, int no, CLACT_WORK_PTR icon, ARCHANDLE* handle, WORLDTRADE_POKEBUF *pbuf )
{
	u8 *pokepal;
	u8 *buf;
	NNSG2dCharacterData *chara;

	// ポケモンアイコンのキャラデータをバッファの読み込む

	buf = CharDataGetbyHandle( handle, PokeIconCgxArcIndexGetByMonsNumber( pokeno, tamago, form ), 
								&chara, HEAPID_WORLDTRADE );
	// VBLANK中にキャラクタを転送するための準備
	MI_CpuCopyFast(chara->pRawData, pbuf->chbuf, POKEICON_TRANS_SIZE);
	pbuf->vadrs = (POKEICON_VRAM_OFFSET+no*POKEICON_TRANS_CHARA)*0x20;
	pbuf->icon = icon;
	pbuf->palno = PokeIconPalNumGet( pokeno, form, tamago )+POKEICON_PAL_OFFSET;
	sys_FreeMemoryEz(buf);
}


//------------------------------------------------------------------
/**
 * @brief   ポケモンアイコンの転送とセルアクターの表示・非表示を制御する
 *
 * @param   paso		
 * @param   dat
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonLevelSet(POKEMON_PASO_PARAM *paso, Dpw_Tr_PokemonDataSimple *dat )
{
	dat->level = PokePasoLevelCalc( paso );
}

//------------------------------------------------------------------
/**
 * @brief   ポケモンアイコンの転送
 *
 * @param   paso		
 * @param   icon		
 * @param   no		
 * @param   pos		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonIconDraw(void *work)
{
  WORLDTRADE_WORK *wk = work;
  
  int i;
  WORLDTRADE_POKEBUF *pbuf = wk->boxicon;

  for(i = 0; i < BOX_POKE_NUM; i++, pbuf++){
    if(pbuf->icon){
      // キャラクター転送
      DC_FlushRange(pbuf->chbuf, POKEICON_TRANS_SIZE);
      GX_LoadOBJ(pbuf->chbuf, pbuf->vadrs, POKEICON_TRANS_SIZE);
      // パレット設定
      CLACT_PaletteNoChg(pbuf->icon, pbuf->palno);
    }
  }
  sys_FreeMemoryEz( wk->boxicon );
}

//------------------------------------------------------------------
/**
 * @brief   ポケモンアイコンの転送とセルアクターの表示・非表示を制御する
 *
 * @param   paso		
 * @param   icon		
 * @param   no		
 * @param   pos		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonIconSet( POKEMON_PASO_PARAM *paso, CLACT_WORK_PTR icon, 
							CLACT_WORK_PTR itemact, u16 *no, int pos, ARCHANDLE* handle, 
							Dpw_Tr_PokemonDataSimple *dat, WORLDTRADE_POKEBUF *pbuf )
{
	int flag,itemno, tamago,form;
	
	PokePasoParaFastModeOn(paso);

	flag   = PokePasoParaGet(paso, ID_PARA_poke_exist, NULL);
	*no    = PokePasoParaGet(paso, ID_PARA_monsno,     NULL);
	form   = PokePasoParaGet(paso, ID_PARA_form_no,    NULL);
	tamago = PokePasoParaGet(paso, ID_PARA_tamago_flag,NULL);
	itemno = PokePasoParaGet(paso, ID_PARA_item,       NULL);
	dat->characterNo = *no;
	dat->gender      = PokePasoParaGet( paso, ID_PARA_sex, NULL )+1;

	// 検索用にタマゴのレベルを０としてしまう（本当は０じゃないけど）
	if(tamago){
		dat->level = 0;
	}

	PokePasoParaFastModeOff(paso,TRUE);
	
	if(flag){
		TransPokeIconCharaPal( *no, form, tamago, pos, icon, handle, pbuf );
		CLACT_SetDrawFlag( icon, 1 );

		// アイテムを持っているか
		if(itemno!=0){	
			CLACT_SetDrawFlag( itemact, 1 );

			// アイテムはメールか？
			if(ItemMailCheck( itemno )){	
				CLACT_AnmChg( itemact, CELL_MAILICON_NO );	// メール
			}else{
				CLACT_AnmChg( itemact, CELL_ITEMICON_NO );	// アイテム
			}
		}else{
			CLACT_SetDrawFlag( itemact, 0 );
		}
	}else{
		CLACT_SetDrawFlag( icon, 0 );
		CLACT_SetDrawFlag( itemact, 0 );
		pbuf->icon = NULL;
	}
}

//------------------------------------------------------------------
/**
 * $brief   ボックス・てもちのポケモンデータを読み込む
 *
 * @param   wk		
 * @param   now		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NowBoxPageInfoGet( WORLDTRADE_WORK *wk, int now)
{
	u16 monsno[30],i,flag;
	POKEMON_PARAM      *pp;
	POKEMON_PASO_PARAM *paso;
	BOX_DATA *boxdata = wk->param->mybox;
	ARCHANDLE* handle;
	WORLDTRADE_POKEBUF *pokebuf;
	
	// ポケモンアイコンを転送する
	wk->boxicon = pokebuf =   sys_AllocMemoryLo(HEAPID_BASE_APP, sizeof(WORLDTRADE_POKEBUF) * BOX_POKE_NUM);

	handle = ArchiveDataHandleOpen( ARC_POKEICON, HEAPID_WORLDTRADE );

	// ボックス
	if(now>=0 && now <18){
		for(i=0;i<BOX_POKE_NUM;i++){
		  PokemonLevelSet(BOXDAT_GetPokeDataAddress( boxdata, now, i ), &wk->boxWork->info[i] );
		}
		for(i=0;i<BOX_POKE_NUM;i++){
			wk->boxWork->info[i].characterNo = 0;
			PokemonIconSet(BOXDAT_GetPokeDataAddress( boxdata, now, i ), 
							wk->PokeIconActWork[i], wk->ItemIconActWork[i],
							&monsno[i], i, handle, &wk->boxWork->info[i], &pokebuf[i] );
			// ボールカプセルのセルアクターはすべて隠す
			if(i<TEMOTI_POKEMAX){
				CLACT_SetDrawFlag( wk->CBallActWork[i], 0 );
			}
		}

		// ボックスのトレイ名取得
		BOXDAT_GetBoxName( boxdata, now, wk->BoxTrayNameString );
	
	}else{
	// てもち
		int num = PokeParty_GetPokeCount( wk->param->myparty );

		for(i=0;i<num;i++){
			pp   = PokeParty_GetMemberPointer(wk->param->myparty, i);
			paso = PPPPointerGet(pp);
			PokemonLevelSet(paso, &wk->boxWork->info[i] );
			PokemonIconSet( paso, wk->PokeIconActWork[i], wk->ItemIconActWork[i],
							&monsno[i], i, handle, &wk->boxWork->info[i], &pokebuf[i] );

			// ボールカプセルをつけているか？
			if(PokeParaGet(pp, ID_PARA_cb_id, NULL)){
				CLACT_SetDrawFlag( wk->CBallActWork[i], 1 );
			}else{
				CLACT_SetDrawFlag( wk->CBallActWork[i], 0 );
			}
		}

		// てもちのポケモンを表示し終わったら後は全て非表示に
		for(;i<BOX_POKE_NUM;i++){
			wk->boxWork->info[i].characterNo = 0;
			CLACT_SetDrawFlag( wk->PokeIconActWork[i], 0 );
			CLACT_SetDrawFlag( wk->ItemIconActWork[i], 0 );
			pokebuf[i].icon = NULL;
			if(i<TEMOTI_POKEMAX){
				CLACT_SetDrawFlag( wk->CBallActWork[i], 0 );
			}
		}
		MSGMAN_GetString( wk->MsgManager, msg_gtc_04_023, wk->BoxTrayNameString );
	}
	ArchiveDataHandleClose( handle );
	
	GF_BGL_BmpWinDataFill( &wk->SubWin, 0x0000 );
	WorldTrade_SysPrint( &wk->SubWin, wk->BoxTrayNameString, 0, 5, 1, GF_PRINTCOLOR_MAKE(1,2,0) );
	
	// 交換ポケモン選択モードの時は条件に合わないポケモンを暗くする
	if(wk->sub_process_mode==MODE_EXCHANGE_SELECT){
		PokeIconPalSet( wk->boxWork->info, wk->PokeIconActWork, &wk->DownloadPokemonData[wk->TouchTrainerPos].wantSimple, pokebuf);
	}
	
	// pokebufの開放はPokemonIconDraw内で行われる
	wk->vfunc = PokemonIconDraw;
}


//==============================================================================
/**
 * @brief   指定したポケモンデータはPOKEMON_PARAMか、POKEMON_PASO_PARAMか？
 *
 * @param   box		
 *
 * @retval  int		0:POKEMON_PASO_PARAM 1:POKEMON_PARAM
 */
//==============================================================================
int WorldTrade_GetPPorPPP( int tray )
{
	if( tray == 18 ){
		return 1;
	}else{
		return 0;
	}
}

//==============================================================================
/**
 * $brief   番号からてもちかボックスの中のPOKEMON_PASO_PARAMへの構造体を返す
 *
 * @param   party		
 * @param   box		
 * @param   tray		
 * @param   pos		
 *
 * @retval  POKEMON_PASO_PARAM *		
 */
//==============================================================================
POKEMON_PASO_PARAM *WorldTrade_GetPokePtr( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos )
{
	// てもち
	if(WorldTrade_GetPPorPPP( tray )){
		if(pos>(PokeParty_GetPokeCount(party)-1)){
			return NULL;
		}
		return  PPPPointerGet(PokeParty_GetMemberPointer( party, pos ));
	}

	// ボックス
	return BOXDAT_GetPokeDataAddress( box, tray, pos );
}

//==============================================================================
/**
 * @brief   てもちポケモンだったときに残りをチェックする
 *
 * @param   party		
 * @param   box		
 * @param   tray		
 * @param   pos		
 *
 * @retval  int		
 */
//==============================================================================
static int CheckPocket( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos )
{
	// てもちだった時は残りを数える
	if(WorldTrade_GetPPorPPP( tray )){
		if( PokeParty_GetPokeCount(party) < 2 ){
			return 0;
		}
	}
	return 1;
}



//==============================================================================
// 拡張リボン用の定義
//==============================================================================

#define SPECIAL_RIBBON_NUM	( 10 )				// 拡張リボンの総数

static const u16 SpRibbonTbl[]={
	ID_PARA_marine_ribbon,						//マリンリボン
	ID_PARA_land_ribbon,						//ランドリボン
	ID_PARA_sky_ribbon,							//スカイリボン

	ID_PARA_sinou_red_ribbon,					//シンオウレッドリボン
	ID_PARA_sinou_green_ribbon,					//シンオウグリーンリボン
	ID_PARA_sinou_blue_ribbon,					//シンオウブルーリボン
	ID_PARA_sinou_festival_ribbon,				//シンオウフェスティバルリボン
	ID_PARA_sinou_carnival_ribbon,				//シンオウカーニバルリボン
	ID_PARA_sinou_classic_ribbon,				//シンオウクラシックリボン
	ID_PARA_sinou_premiere_ribbon,				//シンオウプレミアリボン
};


//------------------------------------------------------------------
/**
 * @brief   特殊リボンを持っているかチェック
 *
 * @param   ppp		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int PokeRibbonCheck( POKEMON_PASO_PARAM *ppp )
{
	// 特殊リボンを持っていないか？
	int i, ret = 0, flag;

	flag = PokePasoParaFastModeOn(ppp);
	for(i=0;i<SPECIAL_RIBBON_NUM;i++){
		ret += PokePasoParaGet( ppp, SpRibbonTbl[i], NULL );
	}
	PokePasoParaFastModeOff(ppp, flag);

	OS_Printf("特殊リボン取得数 %d\n", ret);

	// 特殊リボンをもっているのでダメ
	if(ret){
		return 1;
	}
	
	return 0;
}

//==============================================================================
/**
 * $brief   指定のボックスNO・POSにはポケモンがいるか？
 *
 * @param   party		
 * @param   box		
 * @param   tray		
 * @param   pos		
 *
 * @retval  int		
 */
//==============================================================================
static int PokemonCheck( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos  )
{
	POKEMON_PASO_PARAM *ppp = WorldTrade_GetPokePtr(party, box, tray, pos );
	
	
	// NULLチェック
	if(ppp==NULL){
		return WANT_POKE_NO;
	}

	// ポケモンはいるか？
	if(!PokePasoParaGet(ppp, ID_PARA_poke_exist, NULL)){
		return WANT_POKE_NO;
	}

	// タマゴじゃないか？
	if(PokePasoParaGet(ppp, ID_PARA_tamago_exist, NULL)){
		return WANT_POKE_TAMAGO;
	}


	return WANT_POKE_OK;
}


//------------------------------------------------------------------
/**
 * @brief   検索条件に合致しているか比較する
 *
 * @param   poke		
 * @param   search		
 *
 * @retval  int		0:合致していない	1:合致している
 */
//------------------------------------------------------------------
static int CompareSearchData( Dpw_Tr_PokemonDataSimple *poke,  Dpw_Tr_PokemonSearchData *search )
{
	// ポケモンが違う
	if( poke->characterNo != search->characterNo){
		return 0;
	}
	
	// 性別指定と違う
	if( search->gender!=DPW_TR_GENDER_NONE){
		if(search->gender != poke->gender){
			return 0;
		}
	}
	
	// ポケモンがタマゴ
	if(poke->level==0){
		return 0;
	}
	
	// 指定の最低レベルよりも低い
	if( search->level_min!=0){
		if( search->level_min > poke->level){
			return 0;
		}
	}
	// 指定の最高レベルよりも高い
	if( search->level_max!=0){
		if( search->level_max < poke->level){
			return 0;
		}
	}
	
	// 合致している
	return 1;

}

//------------------------------------------------------------------
/**
 * @brief   相手が要求するポケモンにあっているか？
 *
 * @param   ppp		
 * @param   dtp		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int WantPokeCheck(POKEMON_PASO_PARAM *ppp, Dpw_Tr_PokemonSearchData *dtsd)
{
	Dpw_Tr_PokemonDataSimple temp;
	temp.characterNo = PokePasoParaGet(ppp, ID_PARA_monsno, NULL);
	temp.gender      = PokePasoParaGet( ppp, ID_PARA_sex,   NULL )+1;
	temp.level       = PokePasoLevelCalc(ppp);

	OS_Printf("want pokeno = %d, mypoke    = %d\n", dtsd->characterNo, temp.characterNo);
	OS_Printf("want sex    = %d, minesex   = %d\n", dtsd->gender     , temp.gender   );
	OS_Printf("want level_min  = %d, max  = %d, level = %d\n", dtsd->level_min,dtsd->level_max, temp.level );

	// 比較する
	return CompareSearchData( &temp, dtsd );
}

//------------------------------------------------------------------
/**
 * @brief   送信データの準備を行う
 *
 * @param   dtd		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void MakeExchangePokemonData( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk )
{
	Dpw_Tr_PokemonDataSimple post;
	Dpw_Tr_PokemonSearchData want;
	POKEMON_PASO_PARAM *ppp;

	// 名前・性別・レベル取得
	post.characterNo = PokePasoParaGet( wk->deposit_ppp, ID_PARA_monsno, NULL );
	post.gender      = PokePasoParaGet( wk->deposit_ppp, ID_PARA_sex,   NULL )+1;
	post.level       = PokePasoLevelCalc( wk->deposit_ppp );

	dtd->postSimple = post;

	WorldTrade_PostPokemonBaseDataMake( dtd, wk );

	ppp = PPPPointerGet( (POKEMON_PARAM*)wk->DownloadPokemonData[wk->TouchTrainerPos].postData.data );

	want.characterNo = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
	want.gender      = PokePasoParaGet( ppp, ID_PARA_sex,   NULL )+1;
	want.level_min   = 0;
	want.level_max   = 0;
	dtd->wantSimple  = want;

	OS_Printf( "postData  No = %d,  gender = %d, level = %d\n", dtd->postSimple.characterNo, dtd->postSimple.gender, dtd->postSimple.level);

}

//------------------------------------------------------------------
/**
 * @brief   検索条件に合わないポケモンアイコンのカラーを暗くする
 *
 * @param   box		
 * @param   icon		
 * @param   want		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeIconPalSet( Dpw_Tr_PokemonDataSimple *box, CLACT_WORK_PTR *icon, Dpw_Tr_PokemonSearchData *want, WORLDTRADE_POKEBUF *pbuf)
{
	int pal,i;
	for(i=0;i<BOX_POKE_NUM;i++){
		if(box[i].characterNo!=0){
			if(CompareSearchData( &box[i], want )==0){
				pbuf[i].palno += 3;
			}
		}
	}
}


//------------------------------------------------------------------
/**
 * @brief   メールを持っているか？
 *
 * @param   pp		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL WorldTrade_PokemonMailCheck( POKEMON_PARAM *pp )
{
	int itemno = PokeParaGet( pp, ID_PARA_item,       NULL);
	// アイテムはメールか？
	if(ItemMailCheck( itemno )){
		return TRUE;
	}
	
	return FALSE;
}
