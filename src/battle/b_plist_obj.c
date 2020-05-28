//============================================================================================
/**
 * @file	b_plist_obj.c
 * @brief	戦闘用ポケモンリスト画面OBJ処理
 * @author	Hiroyuki Nakamura
 * @date	05.02.07
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/palanm.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "battle/battle_common.h"
#include "battle/fight_tool.h"
#include "battle/wazatype_icon.h"
#include "poketool/pokeparty.h"
#include "poketool/pokeicon.h"
#include "poketool/waza_tool.h"
#include "application/p_status.h"
#include "application/pokelist.h"
#include "application/app_tool.h"
#include "itemtool/item.h"
#include "b_app_tool.h"

#define	B_PLIST_OBJ_H_GLOBAL
#include "b_plist.h"
#include "b_plist_main.h"
#include "b_plist_obj.h"
#include "b_plist_gra.naix"


//============================================================================================
//	定数定義
//============================================================================================
#define	CLACT_ID_COMMON		( 45063 )	// この画面で使用するセルアクターのID

// キャラリソースID
enum {
	CHR_ID_POKE1 = CLACT_ID_COMMON,		// ポケモンアイコン：１匹目
	CHR_ID_POKE2,						// ポケモンアイコン：２匹目
	CHR_ID_POKE3,						// ポケモンアイコン：３匹目
	CHR_ID_POKE4,						// ポケモンアイコン：４匹目
	CHR_ID_POKE5,						// ポケモンアイコン：５匹目
	CHR_ID_POKE6,						// ポケモンアイコン：６匹目

	CHR_ID_STATUS,						// 状態異常アイコン：１匹目

	CHR_ID_POKETYPE1,					// ポケモンタイプアイコン１
	CHR_ID_POKETYPE2,					// ポケモンタイプアイコン２

	CHR_ID_WAZATYPE1,					// 技タイプアイコン１
	CHR_ID_WAZATYPE2,					// 技タイプアイコン２
	CHR_ID_WAZATYPE3,					// 技タイプアイコン３
	CHR_ID_WAZATYPE4,					// 技タイプアイコン４
	CHR_ID_WAZATYPE5,					// 技タイプアイコン５

	CHR_ID_BUNRUI,						// 分類アイコン

	CHR_ID_ITEM,						// アイテムアイコン

	CHR_ID_CND,							// コンディション

	CHR_ID_CURSOR,						// カーソル

	CHR_ID_MAX = CHR_ID_CURSOR - CLACT_ID_COMMON + 1
};

// パレットリソースID
enum {
	PAL_ID_POKE = CLACT_ID_COMMON,		// ポケモンアイコン（３本）
	PAL_ID_STATUS,						// 状態異常アイコン（１本）
	PAL_ID_TYPE,						// タイプ/分類アイコン（３本）
	PAL_ID_ITEM,						// アイテムアイコン（１本）
	PAL_ID_CND,							// コンディション（１本）
	PAL_ID_CURSOR,						// カーソル（１本）
	PAL_ID_MAX = PAL_ID_CURSOR - CLACT_ID_COMMON + 1
};

// セルリソースID
enum {
	CEL_ID_POKE = CLACT_ID_COMMON,		// ポケモンアイコン
	CEL_ID_STATUS,						// 状態異常アイコン
	CEL_ID_TYPE,						// タイプ/分類アイコン
	CEL_ID_ITEM,						// アイテムアイコン
	CEL_ID_CND,							// コンディション
	CEL_ID_CURSOR,						// カーソル
	CEL_ID_MAX = CEL_ID_CURSOR - CLACT_ID_COMMON + 1
};

// セルアニメリソースID
enum {
	ANM_ID_POKE = CLACT_ID_COMMON,		// ポケモンアイコン
	ANM_ID_STATUS,						// 状態異常アイコン
	ANM_ID_TYPE,						// タイプ/分類アイコン
	ANM_ID_ITEM,						// アイテムアイコン
	ANM_ID_CND,							// コンディション
	ANM_ID_CURSOR,						// カーソル
	ANM_ID_MAX = ANM_ID_CURSOR - CLACT_ID_COMMON + 1
};

#define	CURSOR_CLA_MAX		( 5 )		// カーソルのOBJ数


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void BPL_ClactResManInit( BPLIST_WORK * wk );
static void BPL_ClactPokeLoad( BPLIST_WORK * wk );
static void BPL_ClactStatusLoad( BPLIST_WORK * wk );
static void BPL_ClactConditionLoad( BPLIST_WORK * wk );
static void BPL_ClactTypeLoad( BPLIST_WORK * wk );
static void BPL_ClactItemLoad( BPLIST_WORK * wk );
static void BPL_ClactAddAll( BPLIST_WORK * wk );

static void BPL_PokeIconPaletteChg( BPLIST_WORK * wk );

static void BPL_Page1ObjSet( BPLIST_WORK * wk );
static void BPL_ChgPageObjSet( BPLIST_WORK * wk );
static void BPL_StMainPageObjSet( BPLIST_WORK * wk );
static void BPL_StWazaSelPageObjSet( BPLIST_WORK * wk );
static void BPL_Page4ObjSet( BPLIST_WORK * wk );
static void BPL_Page5ObjSet( BPLIST_WORK * wk );
static void BPL_Page6ObjSet( BPLIST_WORK * wk );
static void BPL_Page7ObjSet( BPLIST_WORK * wk );
static void BPL_Page8ObjSet( BPLIST_WORK * wk );
static void BPL_Page9ObjSet( BPLIST_WORK * wk );

static void BPL_BattleWazaTypeSet( BPLIST_WORK * wk );
static void BPL_ContestWazaTypeSet( BPLIST_WORK * wk );

static void BPL_EzConditionPut( BPLIST_WORK * wk );

static void BPL_ClactCursorAdd( BPLIST_WORK * wk );
static void BPL_CursorDel( BPLIST_WORK * wk );


//============================================================================================
//	グローバル変数
//============================================================================================
// リソーステーブル
static const int ObjParamEz[][5] =
{	// キャラ、パレット、セル、セルアニメ、OBJプライオリティ
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// アイテムアイコン１
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// アイテムアイコン２
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// アイテムアイコン３
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// アイテムアイコン４
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// アイテムアイコン５
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// アイテムアイコン６
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// アイテムアイコン７
	{ CHR_ID_POKE1, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// ポケモンアイコン１
	{ CHR_ID_POKE2, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// ポケモンアイコン２
	{ CHR_ID_POKE3, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// ポケモンアイコン３
	{ CHR_ID_POKE4, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// ポケモンアイコン４
	{ CHR_ID_POKE5, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// ポケモンアイコン５
	{ CHR_ID_POKE6, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// ポケモンアイコン６
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// 状態異常アイコン１
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// 状態異常アイコン２
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// 状態異常アイコン３
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// 状態異常アイコン４
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// 状態異常アイコン５
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// 状態異常アイコン６
	{ CHR_ID_POKETYPE1, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// ポケモンタイプアイコン１
	{ CHR_ID_POKETYPE2, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// ポケモンタイプアイコン２
	{ CHR_ID_WAZATYPE1, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// 技タイプアイコン１
	{ CHR_ID_WAZATYPE2, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// 技タイプアイコン２
	{ CHR_ID_WAZATYPE3, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// 技タイプアイコン３
	{ CHR_ID_WAZATYPE4, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// 技タイプアイコン４
	{ CHR_ID_WAZATYPE5, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// 技タイプアイコン４
	{ CHR_ID_BUNRUI, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// 分類アイコン
	{ CHR_ID_CND, PAL_ID_CND, CEL_ID_CND, ANM_ID_CND, 0 },				// コンディション１
	{ CHR_ID_CND, PAL_ID_CND, CEL_ID_CND, ANM_ID_CND, 0 },				// コンディション２
	{ CHR_ID_CND, PAL_ID_CND, CEL_ID_CND, ANM_ID_CND, 0 },				// コンディション３
	{ CHR_ID_CND, PAL_ID_CND, CEL_ID_CND, ANM_ID_CND, 0 },				// コンディション４
	{ CHR_ID_CND, PAL_ID_CND, CEL_ID_CND, ANM_ID_CND, 0 },				// コンディション５
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// カスタムボールアイコン１
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// カスタムボールアイコン２
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// カスタムボールアイコン３
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// カスタムボールアイコン４
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// カスタムボールアイコン５
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// カスタムボールアイコン６
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// カスタムボールアイコン７
};

// ページ１のポケモンアイコンの座標
static const int P1_PokePos[][2] =
{
	{ 16,  16 }, { 144,  24 },
	{ 16,  64 }, { 144,  72 },
	{ 16, 112 }, { 144, 120 },
};
// ページ１の状態異常アイコンの座標
static const int P1_StatusPos[][2] =
{
	{ 16+12,  16+24 }, { 144+12,  24+24 },
	{ 16+12,  64+24 }, { 144+12,  72+24 },
	{ 16+12, 112+24 }, { 144+12, 120+24 },
};

static const int P_CHG_PokePos[2] = { 128, 72 };	// 入れ替えページのポケモンアイコンの座標

static const int P2_PokePos[2] = { 24, 12 };		// ページ２のポケモンアイコンの座標
static const int P2_StatusPos[2] = { 192+6, 17+3 };	// ページ２の状態異常アイコンの座標
// ページ２のポケモンのタイプアイコンの座標
static const int P2_PokeTypePos[][2] =
{
	{ 128+2, 16 },
	{ 160+4, 16 }
};
// ページ２の技のタイプアイコンの座標
static const int P2_WazaTypePos[][2] =
{
	{  24,  80 },
	{ 152,  80 },
	{  24, 128 },
	{ 152, 128 }
};

static const int P3_PokePos[2] = { 24, 12 };		// ページ３のポケモンアイコンの座標
static const int P3_StatusPos[2] = { 192+6, 17+3 };	// ページ３の状態異常アイコンの座標
// ページ３のポケモンのタイプアイコンの座標
static const int P3_PokeTypePos[][2] =
{
	{ 128+2, 16 },
	{ 160+4, 16 }
};

static const int P4_PokePos[2] = { 24, 12 };		// ページ４のポケモンアイコンの座標
static const int P4_StatusPos[2] = { 192+6, 17+3 };	// ページ４の状態異常アイコンの座標
// ページ４のポケモンのタイプアイコンの座標
static const int P4_PokeTypePos[][2] =
{
	{ 128+2, 16 },
	{ 160+4, 16 }
};
static const int P4_WazaTypePos[2] = { 136, 48 };	// ページ４の技タイプアイコンの座標
static const int P4_WazaKindPos[2] = { 24, 88 };	// ページ４の技分類アイコンの座標

static const int P5_PokePos[2] = { 24, 12 };		// ページ５のポケモンアイコンの座標
// ページ５のポケモンのタイプアイコンの座標
static const int P5_PokeTypePos[][2] =
{
	{ 128+2, 16 },
	{ 160+4, 16 }
};
// ページ５の技のタイプアイコンの座標
static const int P5_WazaTypePos[][2] =
{
	{  24,  80 },
	{ 152,  80 },
	{  24, 128 },
	{ 152, 128 },
	{  88, 176 }
};

static const int P6_PokePos[2] = { 24, 12 };		// ページ６のポケモンアイコンの座標
// ページ６のポケモンのタイプアイコンの座標
static const int P6_PokeTypePos[][2] =
{
	{ 128+2, 16 },
	{ 160+4, 16 }
};
static const int P6_WazaTypePos[2] = { 136, 48 };	// ページ６の技タイプアイコンの座標
static const int P6_WazaKindPos[2] = { 24, 88 };	// ページ６の技分類アイコンの座標

static const int P8_WazaTypePos[2] = { 136, 72 };	// ページ８の技タイプアイコンの座標


//--------------------------------------------------------------------------------------------
/**
 * 戦闘用ポケリストOBJ初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattlePokeList_ObjInit( BPLIST_WORK * wk )
{
	BPL_ClactResManInit( wk );
	BPL_ClactPokeLoad( wk );
	BPL_ClactStatusLoad( wk );
	BPL_ClactTypeLoad( wk );
	BPL_ClactItemLoad( wk );
	BPL_ClactConditionLoad( wk );
	BPL_ClactAddAll( wk );
	BPL_ClactCursorAdd( wk );

	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//--------------------------------------------------------------------------------------------
/**
 * リソースマネージャー初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactResManInit( BPLIST_WORK * wk )
{
	TCATS_RESOURCE_NUM_LIST	crnl = { CHR_ID_MAX, PAL_ID_MAX, CEL_ID_MAX, ANM_ID_MAX, 0, 0 };
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	wk->crp = CATS_ResourceCreate( csp );
	CATS_ClactSetInit( csp, wk->crp, BPL_CA_MAX+CURSOR_CLA_MAX );
	CATS_ResourceManagerInit( csp, wk->crp, &crnl );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンアイコンのグラフィックロード
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactPokeLoad( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// パレット
	CATS_LoadResourcePlttWorkArc(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp,
		ARC_POKEICON, PokeIconPalArcIndexGet(), 0, 3, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_POKE );
	// セル
	CATS_LoadResourceCellArc(
		csp, wk->crp, ARC_POKEICON, PokeIconAnmCellArcIndexGet(), 0, CEL_ID_POKE );
	// セルアニメ
	CATS_LoadResourceCellAnmArc(
		csp, wk->crp, ARC_POKEICON, PokeIconAnmCellAnmArcIndexGet(), 0, ANM_ID_POKE );
	// キャラ
	for( i=0; i<6; i++ ){
		if( wk->poke[i].mons != 0 ){
			CATS_LoadResourceCharArc(
				csp, wk->crp, ARC_POKEICON,
				PokeIconCgxArcIndexGetByPP(wk->poke[i].pp),
				0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_POKE1+i );
		}else{
			CATS_LoadResourceCharArc(
				csp, wk->crp, ARC_POKEICON,
				PokeIconCgxArcIndexGetByMonsNumber(0,0,0),
				0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_POKE1+i );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 状態異常アイコンのグラフィックロード
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactStatusLoad( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// パレット
	CATS_LoadResourcePlttWorkArc(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp, ARC_PSTATUS_GRA,
		BadStatusIconPlttArcGet(), 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_STATUS );
	// セル
	CATS_LoadResourceCellArc(
		csp, wk->crp, ARC_PSTATUS_GRA, BadStatusIconCellArcGet(), 0, CEL_ID_STATUS );
	// セルアニメ
	CATS_LoadResourceCellAnmArc(
		csp, wk->crp, ARC_PSTATUS_GRA, BadStatusIconCanmArcGet(), 0, ANM_ID_STATUS );
	// キャラ
	CATS_LoadResourceCharArc(
		csp, wk->crp, ARC_PSTATUS_GRA,
		BadStatusIconCharArcGet(), 0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_STATUS );
}

//--------------------------------------------------------------------------------------------
/**
 * タイプ/分類アイコンのグラフィックロード
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactTypeLoad( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// パレット
	WazaTypeIcon_PlttWorkResourceLoad(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_TYPE );
	// セル・アニメ
	WazaTypeIcon_CellAnmResourceLoad( csp, wk->crp, CEL_ID_TYPE, ANM_ID_TYPE );
	// キャラ
	for( i=CHR_ID_POKETYPE1; i<=CHR_ID_WAZATYPE5; i++ ){
		WazaTypeIcon_CharResourceLoad( csp, wk->crp, NNS_G2D_VRAM_TYPE_2DSUB, 0, i );
	}
	// 分類キャラ
	WazaKindIcon_CharResourceLoad( csp, wk->crp, NNS_G2D_VRAM_TYPE_2DSUB, 0, CHR_ID_BUNRUI );
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのグラフィックロード
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactItemLoad( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// パレット
	CATS_LoadResourcePlttWorkArc(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp, ARC_PLIST_GRA,
		Pokelist_ItemIconPalArcGet(), 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_ITEM );
	// セル
	CATS_LoadResourceCellArc(
		csp, wk->crp, ARC_PLIST_GRA, Pokelist_ItemIconCellArcGet(), 0, CEL_ID_ITEM );
	// セルアニメ
	CATS_LoadResourceCellAnmArc(
		csp, wk->crp, ARC_PLIST_GRA, Pokelist_ItemIconCAnmArcGet(), 0, ANM_ID_ITEM );
	// キャラ
	CATS_LoadResourceCharArc(
		csp, wk->crp, ARC_PLIST_GRA,
		Pokelist_ItemIconCgxArcGet(), 0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_ITEM );
}

//--------------------------------------------------------------------------------------------
/**
 * コンディションのグラフィックロード
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactConditionLoad( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// パレット
	CATS_LoadResourcePlttWorkArc(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp, ARC_BPLIST_GRA,
		NARC_b_plist_gra_b_plist_obj_NCLR, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_CND );
	// セル
	CATS_LoadResourceCellArc(
		csp, wk->crp, ARC_BPLIST_GRA, NARC_b_plist_gra_b_plist_obj_NCER, 0, CEL_ID_CND );
	// セルアニメ
	CATS_LoadResourceCellAnmArc(
		csp, wk->crp, ARC_BPLIST_GRA, NARC_b_plist_gra_b_plist_obj_NANR, 0, ANM_ID_CND );
	// キャラ
	CATS_LoadResourceCharArc(
		csp, wk->crp, ARC_BPLIST_GRA,
		NARC_b_plist_gra_b_plist_obj_NCGR, 0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_CND );
}



//--------------------------------------------------------------------------------------------
/**
 * セルアクター追加（個別）
 *
 * @param	wk		ワーク
 * @param	id		追加するセルアクターのID
 *
 * @return	セルアクターデータ
 */
//--------------------------------------------------------------------------------------------
static CATS_ACT_PTR BPL_ClactAdd( BPLIST_WORK * wk, u32 id )
{
	TCATS_OBJECT_ADD_PARAM_S	prm;
	CATS_SYS_PTR	csp;

	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	prm.x = 0;
	prm.y = 0;
	prm.z = 0;

	prm.anm = 0;
	prm.pri = ObjParamEz[id][4];
	prm.pal = 0;
	prm.d_area = NNS_G2D_VRAM_TYPE_2DSUB;

	prm.id[0] = ObjParamEz[id][0];
	prm.id[1] = ObjParamEz[id][1];
	prm.id[2] = ObjParamEz[id][2];
	prm.id[3] = ObjParamEz[id][3];
	
	prm.bg_pri = 1;
	prm.vram_trans = 0;

	return CATS_ObjectAdd_S( csp, wk->crp, &prm );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター追加（全て）
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactAddAll( BPLIST_WORK * wk )
{
	u32	i;

	for( i=0; i<BPL_CA_MAX; i++ ){
		wk->cap[i] = BPL_ClactAdd( wk, i );
	}
	BPL_PokeIconPaletteChg( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * 戦闘用ポケリストOBJ削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattlePokeList_ObjFree( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	for( i=0; i<BPL_CA_MAX; i++ ){
		CATS_ActorPointerDelete_S( wk->cap[i] );
	}

	BPL_CursorDel( wk );

	CATS_ResourceDestructor_S( csp, wk->crp );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクターを表示して座標変更
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactOn( CATS_ACT_PTR cap, const int x, const int y )
{
	CATS_ObjectEnableCap( cap, 1 );
	CATS_ObjectPosSetCap( cap, x, y );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンアイコンのパレット切り替え
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_PokeIconPaletteChg( BPLIST_WORK * wk )
{
	s32	i;

	for( i=0; i<6; i++ ){
		if( wk->poke[i].mons == 0 ){ continue; }
		CATS_ObjectPaletteSetCap(
			wk->cap[BPL_CA_POKE1+i],
			PokeIconPalNumGet(wk->poke[i].mons,wk->poke[i].form,wk->poke[i].egg) );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * タイプアイコン切り替え
 *
 * @param	wk		ワーク
 * @param	cap		セルアクターデータ
 * @param	res_id	リソースID
 * @param	type	タイプ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_TypeIconChange( BPLIST_WORK * wk, CATS_ACT_PTR cap, u32 res_id, u8 type )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	CATS_ChangeResourceCharArc(
		csp, wk->crp, WazaTypeIcon_ArcIDGet(),
		WazaTypeIcon_CgrIDGet(type), WAZATYPEICON_COMP_CHAR, res_id );

	CATS_ObjectPaletteSetCap( cap, WazaTypeIcon_PlttOffsetGet(type)+4 );
}

//--------------------------------------------------------------------------------------------
/**
 * 分類アイコン切り替え
 *
 * @param	wk		ワーク
 * @param	cap		セルアクターデータ
 * @param	kind	分類
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_KindIconChange( BPLIST_WORK * wk, CATS_ACT_PTR cap, u32 kind )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	CATS_ChangeResourceCharArc(
		csp, wk->crp, WazaKindIcon_ArcIDGet(),
		WazaKindIcon_CgrIDGet(kind), WAZAKINDICON_COMP_CHAR, CHR_ID_BUNRUI );

	CATS_ObjectPaletteSetCap( cap, WazaKindIcon_PlttOffsetGet(kind)+4 );
}

//--------------------------------------------------------------------------------------------
/**
 * 状態異常アイコン切り替え
 *
 * @param	st		ステータス
 * @param	cap		セルアクターデータ
 * @param	x		X座標
 * @param	y		Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_StIconPut( u16 st, CATS_ACT_PTR cap, const int x, const int y )
{
	if( st == ST_ICON_NONE ){ return; }

	CATS_ObjectAnimeSeqSetCap( cap, st );
	BPL_ClactOn( cap, x, y );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンのタイプアイコン切り替え
 *
 * @param	wk		ワーク
 * @param	pd		ポケモンデータ
 * @param	pos		座標データ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_PokeTypeIconPut( BPLIST_WORK * wk, BPL_POKEDATA * pd, const int * pos )
{
	BPL_TypeIconChange( wk, wk->cap[BPL_CA_POKETYPE1], CHR_ID_POKETYPE1, pd->type1 );
	BPL_ClactOn( wk->cap[BPL_CA_POKETYPE1], pos[0], pos[1] );
	if( pd->type1 != pd->type2 ){
		BPL_TypeIconChange( wk, wk->cap[BPL_CA_POKETYPE2], CHR_ID_POKETYPE2, pd->type2 );
		BPL_ClactOn( wk->cap[BPL_CA_POKETYPE2], pos[2], pos[3] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコン切り替え
 *
 * @param	item	ステータス
 * @param	cap		セルアクターデータ
 * @param	x		X座標
 * @param	y		Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ItemIconPut( u16 item, CATS_ACT_PTR cap, const int x, const int y )
{
	if( item == 0 ){ return; }

	if( ItemMailCheck( item ) == TRUE ){
		CATS_ObjectAnimeSeqSetCap( cap, 1 );
	}else{
		CATS_ObjectAnimeSeqSetCap( cap, 0 );
	}
	BPL_ClactOn( cap, x, y );
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコン切り替え
 *
 * @param	cb		カスタムボールID
 * @param	cap		セルアクターデータ
 * @param	x		X座標
 * @param	y		Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_CustomBallIconPut( u8 cb, CATS_ACT_PTR cap, const int x, const int y )
{
	if( cb == 0 ){ return; }

	CATS_ObjectAnimeSeqSetCap( cap, 2 );
	BPL_ClactOn( cap, x, y );
}

//--------------------------------------------------------------------------------------------
/**
 * ページごとにOBJをセット
 *
 * @param	wk		ワーク
 * @param	page	ページ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattlePokeList_PageObjSet( BPLIST_WORK * wk, u32 page )
{
	u32	i;

	for( i=0; i<BPL_CA_MAX; i++ ){
		CATS_ObjectEnableCap( wk->cap[i], 0 );
	}

	switch( page ){
	case BPLIST_PAGE_SELECT:	// ポケモン選択ページ
		BPL_Page1ObjSet( wk );
		break;
	case BPLIST_PAGE_POKE_CHG:	// ポケモン入れ替えページ
		BPL_ChgPageObjSet( wk );
		break;
	case BPLIST_PAGE_MAIN:		// ステータスメインページ
		BPL_StMainPageObjSet( wk );
		break;

	case BPLIST_PAGE_WAZA_SEL:	// ステータス技選択ページ
		BPL_StWazaSelPageObjSet( wk );
		break;

	case BPLIST_PAGE_SKILL:		// ステータス技ページ
		BPL_Page4ObjSet( wk );
		break;

	case BPLIST_PAGE_PP_RCV:		// PP回復技選択ページ
		BPL_Page7ObjSet( wk );
		break;

	case BPLIST_PAGE_WAZASET_BS:	// ステータス技忘れ１ページ（戦闘技選択）
		BPL_Page5ObjSet( wk );
		break;

	case BPLIST_PAGE_WAZASET_BI:	// ステータス技忘れ２ページ（戦闘技詳細）
		BPL_Page6ObjSet( wk );
		break;

	case BPLIST_PAGE_WAZASET_CS:	// ステータス技忘れ３ページ（コンテスト技詳細）
		BPL_Page9ObjSet( wk );
		break;

	case BPLIST_PAGE_WAZASET_CI:	// ステータス技忘れ４ページ（コンテスト技選択）
		BPL_Page8ObjSet( wk );
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ページ１のOBJをセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page1ObjSet( BPLIST_WORK * wk )
{
	s32	i;

	for( i=0; i<6; i++ ){
		if( wk->poke[i].mons == 0 ){ continue; }
		// ポケモンアイコン
		BPL_ClactOn( wk->cap[BPL_CA_POKE1+i], P1_PokePos[i][0], P1_PokePos[i][1] );
		// 状態異常アイコン
		BPL_StIconPut(
			wk->poke[i].st, wk->cap[BPL_CA_STATUS1+i], P1_StatusPos[i][0], P1_StatusPos[i][1] );
		// アイテムアイコン
		BPL_ItemIconPut(
			wk->poke[i].item, wk->cap[BPL_CA_ITEM1+i], P1_PokePos[i][0]+8, P1_PokePos[i][1]+8 );
		// カスタムボールアイコン
		BPL_CustomBallIconPut(
			wk->poke[i].cb, wk->cap[BPL_CA_CB1+i], P1_PokePos[i][0]+16, P1_PokePos[i][1]+8 );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 入れ替えページのOBJをセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ChgPageObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// ポケアイコン
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P_CHG_PokePos[0], P_CHG_PokePos[1] );
	// アイテムアイコン
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P_CHG_PokePos[0]+8, P_CHG_PokePos[1]+8 );
	// カスタムボールアイコン
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P_CHG_PokePos[0]+16, P_CHG_PokePos[1]+8 );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ２のOBJをセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	P_STMAIN_ITEM_PX	( 20 )
#define	P_STMAIN_ITEM_PY	( 132 )

static void BPL_StMainPageObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// ポケアイコン
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P2_PokePos[0], P2_PokePos[1] );
	// ステータス異常
	BPL_StIconPut(
		pd->st, wk->cap[BPL_CA_STATUS1+wk->dat->sel_poke], P2_StatusPos[0], P2_StatusPos[1] );
	// タイプ
	BPL_PokeTypeIconPut( wk, pd, &P2_PokeTypePos[0][0] );
	// アイテムアイコン
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P2_PokePos[0]+8, P2_PokePos[1]+8 );
	// カスタムボールアイコン
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P2_PokePos[0]+16, P2_PokePos[1]+8 );

	// アイテムアイコン（アイテム名の横の）
	BPL_ItemIconPut( pd->item, wk->cap[BPL_CA_ITEM7], P_STMAIN_ITEM_PX, P_STMAIN_ITEM_PY );
}

//--------------------------------------------------------------------------------------------
/**
 * ステータス技選択ページのOBJをセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_StWazaSelPageObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u32	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// ポケアイコン
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P3_PokePos[0], P3_PokePos[1] );
	// ステータス異常
	BPL_StIconPut(
		pd->st, wk->cap[BPL_CA_STATUS1+wk->dat->sel_poke], P3_StatusPos[0], P3_StatusPos[1] );
	// タイプ
	BPL_PokeTypeIconPut( wk, pd, &P3_PokeTypePos[0][0] );
	// アイテムアイコン
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P3_PokePos[0]+8, P3_PokePos[1]+8 );
	// カスタムボールアイコン
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P3_PokePos[0]+16, P3_PokePos[1]+8 );

	// 技タイプ
	for( i=0; i<4; i++ ){
		if( pd->waza[i].id == 0 ){ continue; }

		BPL_TypeIconChange(
			wk, wk->cap[BPL_CA_WAZATYPE1+i], CHR_ID_WAZATYPE1+i, pd->waza[i].type );
		BPL_ClactOn( wk->cap[BPL_CA_WAZATYPE1+i], P2_WazaTypePos[i][0], P2_WazaTypePos[i][1] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ページ４のOBJをセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page4ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd = &wk->poke[wk->dat->sel_poke];

	// ポケアイコン
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P4_PokePos[0], P4_PokePos[1] );
	// ステータス異常
	BPL_StIconPut(
		pd->st, wk->cap[BPL_CA_STATUS1+wk->dat->sel_poke], P4_StatusPos[0], P4_StatusPos[1] );
	// タイプ
	BPL_PokeTypeIconPut( wk, pd, &P4_PokeTypePos[0][0] );
	// 技タイプ
	BPL_ClactOn(
		wk->cap[BPL_CA_WAZATYPE1+wk->dat->sel_wp], P4_WazaTypePos[0], P4_WazaTypePos[1] );
	// アイテムアイコン
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P4_PokePos[0]+8, P4_PokePos[1]+8 );
	// カスタムボールアイコン
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P4_PokePos[0]+16, P4_PokePos[1]+8 );
	// 分類アイコン
	BPL_KindIconChange(
		wk, wk->cap[BPL_CA_BUNRUI], pd->waza[wk->dat->sel_wp].kind );
	BPL_ClactOn( wk->cap[BPL_CA_BUNRUI], P4_WazaKindPos[0], P4_WazaKindPos[1] );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ５のOBJをセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page5ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// ポケアイコン
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P5_PokePos[0], P5_PokePos[1] );
	// タイプ
	BPL_PokeTypeIconPut( wk, pd, &P5_PokeTypePos[0][0] );
	// アイテムアイコン
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P5_PokePos[0]+8, P5_PokePos[1]+8 );
	// カスタムボールアイコン
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P5_PokePos[0]+16, P5_PokePos[1]+8 );

	// 技タイプ
	BattlePokelist_WazaTypeSet( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ６のOBJをセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page6ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd = &wk->poke[wk->dat->sel_poke];

	// ポケアイコン
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P6_PokePos[0], P6_PokePos[1] );
	// タイプ
	BPL_PokeTypeIconPut( wk, pd, &P6_PokeTypePos[0][0] );
	// 技タイプ
	BPL_ClactOn(
		wk->cap[BPL_CA_WAZATYPE1+wk->dat->sel_wp], P6_WazaTypePos[0], P6_WazaTypePos[1] );
	// アイテムアイコン
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P6_PokePos[0]+8, P6_PokePos[1]+8 );
	// カスタムボールアイコン
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P6_PokePos[0]+16, P6_PokePos[1]+8 );
	// 分類アイコン
	if( wk->dat->sel_wp < 4 ){
		BPL_KindIconChange(
			wk, wk->cap[BPL_CA_BUNRUI], pd->waza[wk->dat->sel_wp].kind );
	}else{
		BPL_KindIconChange(
			wk, wk->cap[BPL_CA_BUNRUI], WT_WazaDataParaGet(wk->dat->chg_waza,ID_WTD_kind) );
	}
	BPL_ClactOn( wk->cap[BPL_CA_BUNRUI], P6_WazaKindPos[0], P6_WazaKindPos[1] );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ７のOBJをセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page7ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// ポケアイコン
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P5_PokePos[0], P5_PokePos[1] );
	// タイプ
	BPL_PokeTypeIconPut( wk, pd, &P5_PokeTypePos[0][0] );
	// アイテムアイコン
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P5_PokePos[0]+8, P5_PokePos[1]+8 );
	// カスタムボールアイコン
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P5_PokePos[0]+16, P5_PokePos[1]+8 );

	// 技タイプ
	BattlePokelist_WazaTypeSet( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ８のOBJをセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page8ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd = &wk->poke[wk->dat->sel_poke];

	// ポケアイコン
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P6_PokePos[0], P6_PokePos[1] );

	// 技タイプ
	BPL_ClactOn(
		wk->cap[BPL_CA_WAZATYPE1+wk->dat->sel_wp], P8_WazaTypePos[0], P8_WazaTypePos[1] );
	// アイテムアイコン
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P6_PokePos[0]+8, P6_PokePos[1]+8 );
	// カスタムボールアイコン
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P6_PokePos[0]+16, P6_PokePos[1]+8 );

	// コンディション
	BPL_EzConditionPut( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ９のOBJをセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page9ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd = &wk->poke[wk->dat->sel_poke];

	// ポケアイコン
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P6_PokePos[0], P6_PokePos[1] );

	// 技タイプ
//	BPL_ClactOn(
//		wk->cap[BPL_CA_WAZATYPE1+wk->dat->sel_wp], P8_WazaTypePos[0], P8_WazaTypePos[1] );

	// アイテムアイコン
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P6_PokePos[0]+8, P6_PokePos[1]+8 );
	// カスタムボールアイコン
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P6_PokePos[0]+16, P6_PokePos[1]+8 );

	// 技タイプ
	BattlePokelist_WazaTypeSet( wk );

	// コンディション
	BPL_EzConditionPut( wk );
}


//--------------------------------------------------------------------------------------------
/**
 * 技アイコンセット：戦闘
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_BattleWazaTypeSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// 技タイプ
	for( i=0; i<4; i++ ){
		if( pd->waza[i].id == 0 ){ continue; }

		BPL_TypeIconChange(
			wk, wk->cap[BPL_CA_WAZATYPE1+i], CHR_ID_WAZATYPE1+i, pd->waza[i].type );
		BPL_ClactOn( wk->cap[BPL_CA_WAZATYPE1+i], P5_WazaTypePos[i][0], P5_WazaTypePos[i][1] );
	}

	if( wk->dat->chg_waza != 0 ){
		BPL_TypeIconChange(
			wk, wk->cap[BPL_CA_WAZATYPE5], CHR_ID_WAZATYPE5,
			WT_WazaDataParaGet( wk->dat->chg_waza, ID_WTD_wazatype ) );
		BPL_ClactOn( wk->cap[BPL_CA_WAZATYPE5], P5_WazaTypePos[4][0], P5_WazaTypePos[4][1] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 技アイコンセット：コンテスト
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ContestWazaTypeSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// 技タイプ
	for( i=0; i<4; i++ ){
		if( pd->waza[i].id == 0 ){ continue; }

		BPL_TypeIconChange(
			wk, wk->cap[BPL_CA_WAZATYPE1+i], CHR_ID_WAZATYPE1+i,
			WT_WazaDataParaGet(pd->waza[i].id,ID_WTD_contype)+ICONTYPE_STYLE );
		BPL_ClactOn( wk->cap[BPL_CA_WAZATYPE1+i], P5_WazaTypePos[i][0], P5_WazaTypePos[i][1] );
	}

	if( wk->dat->chg_waza != 0 ){
		BPL_TypeIconChange(
			wk, wk->cap[BPL_CA_WAZATYPE5], CHR_ID_WAZATYPE5,
			WT_WazaDataParaGet(wk->dat->chg_waza,ID_WTD_contype)+ICONTYPE_STYLE );
		BPL_ClactOn( wk->cap[BPL_CA_WAZATYPE5], P5_WazaTypePos[4][0], P5_WazaTypePos[4][1] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 技アイコンセット：戦闘 or コンテスト
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattlePokelist_WazaTypeSet( BPLIST_WORK * wk )
{
	if( wk->bc_put == 0 ){
		BPL_BattleWazaTypeSet( wk );
	}else{
		BPL_ContestWazaTypeSet( wk );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * ポケモンアイコンアニメ切り替え
 *
 * @param	cap		セルアクターデータ
 * @param	anm		アニメ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_PokeIconAnmChg( CATS_ACT_PTR cap, u8 anm )
{
	if( CATS_ObjectAnimeSeqGetCap( cap ) == anm ){ return; }
	CATS_ObjectAnimeFrameSetCap( cap, 0 );
	CATS_ObjectAnimeSeqSetCap( cap, anm );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンアイコンアニメチェック
 *
 * @param	pd		ポケモンデータ
 *
 * @return	アニメ番号
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_PokeIconAnmCheck( BPL_POKEDATA * pd )
{
	if( pd->hp == 0 ){
		return POKEICON_ANM_DEATH;
	}

	if( pd->st != ST_ICON_NONE && pd->st != ST_ICON_HINSI ){
		return POKEICON_ANM_STCHG;
	}

	switch( GetHPGaugeDottoColor( pd->hp, pd->mhp, BPL_HP_DOTTO_MAX ) ){
	case HP_DOTTO_MAX:
		return POKEICON_ANM_HPMAX;
	case HP_DOTTO_GREEN:	// 緑
		return POKEICON_ANM_HPGREEN;
	case HP_DOTTO_YELLOW:	// 黄
		return POKEICON_ANM_HPYERROW;
	case HP_DOTTO_RED:		// 赤
		return POKEICON_ANM_HPRED;
	}

	return POKEICON_ANM_DEATH;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンアイコンアニメ
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BPL_PokeIconAnime( BPLIST_WORK * wk )
{
	u16	i;
	u16	anm;

	for( i=0; i<PokeParty_GetPokeCount(wk->dat->pp); i++ ){

		if( wk->poke[i].mons == 0 ){ continue; }

		anm = BPL_PokeIconAnmCheck( &wk->poke[i] );

		BPL_PokeIconAnmChg( wk->cap[BPL_CA_POKE1+i], anm );
		CATS_ObjectUpdateNumCap( wk->cap[BPL_CA_POKE1+i], FX32_ONE );

/*
		if( wk->pos == i && anm != POKEICON_ANM_DEATH && anm != POKEICON_ANM_STCHG ){
			if( CLACT_AnmFrameGet( dat->icon_cwp ) == 0 ){
				CATS_ObjectPosSet( dat->icon_cwp, dat->mons_px, dat->mons_py-3 );
			}else{
				CATS_ObjectPosSet( dat->icon_cwp, dat->mons_px, dat->mons_py+1 );
			}
			continue;
		}
		CATS_ObjectPosSet( dat->icon_cwp, dat->mons_px, dat->mons_py );
*/

	}
}

//============================================================================================
//	簡易コンディション
//============================================================================================
#define	EZCON1_MIN_X	( 144 )
#define	EZCON1_MAX_X	( 144 )
#define	EZCON1_MIN_Y	( 24 )
#define	EZCON1_MAX_Y	( 2 )

#define	EZCON2_MIN_X	( 144 )
#define	EZCON2_MAX_X	( 167 )
#define	EZCON2_MIN_Y	( 24 )
#define	EZCON2_MAX_Y	( 18 )

#define	EZCON3_MIN_X	( 144 )
#define	EZCON3_MAX_X	( 159 )
#define	EZCON3_MIN_Y	( 24 )
#define	EZCON3_MAX_Y	( 47 )

#define	EZCON4_MIN_X	( 143 )
#define	EZCON4_MAX_X	( 128 )
#define	EZCON4_MIN_Y	( 24 )
#define	EZCON4_MAX_Y	( 47 )

#define	EZCON5_MIN_X	( 143 )
#define	EZCON5_MAX_X	( 120 )
#define	EZCON5_MIN_Y	( 24 )
#define	EZCON5_MAX_Y	( 18 )

#define	EZCND_MAX_RPM	( 300 )
#define	EZCND_DEF_RPM	( 44 )		// 300 = 256 + EZCND_DEF_RPM



static s16 BPL_EzCndPosGet( u32 prm, s16 max, s16 min )
{
	u32	dot;

	prm += EZCND_DEF_RPM;

	if( min > max ){
		dot = ( ( min - max ) * prm ) << 16;
		dot = ( dot / EZCND_MAX_RPM ) >> 16;
		return min + (s16)dot * -1;
	}
	
	dot = ( ( max - min ) * prm ) << 16;
	dot = ( dot / EZCND_MAX_RPM ) >> 16;
	return min + (s16)dot;
}


static void BPL_EzConditionPut( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	BPL_PokeIconAnmChg( wk->cap[BPL_CA_CND1], 0 );
	BPL_PokeIconAnmChg( wk->cap[BPL_CA_CND2], 1 );
	BPL_PokeIconAnmChg( wk->cap[BPL_CA_CND3], 3 );
	BPL_PokeIconAnmChg( wk->cap[BPL_CA_CND4], 4 );
	BPL_PokeIconAnmChg( wk->cap[BPL_CA_CND5], 2 );

	BPL_ClactOn(
		wk->cap[BPL_CA_CND1],
		BPL_EzCndPosGet( pd->style, EZCON1_MAX_X, EZCON1_MIN_X ),
		BPL_EzCndPosGet( pd->style, EZCON1_MAX_Y, EZCON1_MIN_Y ) );
	BPL_ClactOn(
		wk->cap[BPL_CA_CND2],
		BPL_EzCndPosGet( pd->beautiful, EZCON2_MAX_X, EZCON2_MIN_X ),
		BPL_EzCndPosGet( pd->beautiful, EZCON2_MAX_Y, EZCON2_MIN_Y ) );
	BPL_ClactOn(
		wk->cap[BPL_CA_CND3],
		BPL_EzCndPosGet( pd->cute, EZCON3_MAX_X, EZCON3_MIN_X ),
		BPL_EzCndPosGet( pd->cute, EZCON3_MAX_Y, EZCON3_MIN_Y ) );
	BPL_ClactOn(
		wk->cap[BPL_CA_CND4],
		BPL_EzCndPosGet( pd->clever, EZCON4_MAX_X, EZCON4_MIN_X ),
		BPL_EzCndPosGet( pd->clever, EZCON4_MAX_Y, EZCON4_MIN_Y ) );
	BPL_ClactOn(
		wk->cap[BPL_CA_CND5],
		BPL_EzCndPosGet( pd->strong, EZCON5_MAX_X, EZCON5_MIN_X ),
		BPL_EzCndPosGet( pd->strong, EZCON5_MAX_Y, EZCON5_MIN_Y ) );
}


//============================================================================================
//	カーソル
//============================================================================================
static void BPL_ClactCursorAdd( BPLIST_WORK * wk )
{
	CATS_SYS_PTR csp;
	BCURSOR_PTR	cursor;

	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	BCURSOR_ResourceLoad(
		csp, wk->crp, wk->pfd, CHR_ID_CURSOR, PAL_ID_CURSOR, CEL_ID_CURSOR, ANM_ID_CURSOR );

	cursor = BCURSOR_ActorCreate(
				csp, wk->crp, wk->dat->heap,
				CHR_ID_CURSOR, PAL_ID_CURSOR, CEL_ID_CURSOR, ANM_ID_CURSOR, 0, 1 );

	BAPP_CursorMvWkSetBCURSOR_PTR( wk->cmv_wk, cursor );
}

static void BPL_CursorDel( BPLIST_WORK * wk )
{
	BCURSOR_ActorDelete( BAPP_CursorMvWkGetBCURSOR_PTR( wk->cmv_wk ) );
	BCURSOR_ResourceFree(
		wk->crp, CHR_ID_CURSOR, PAL_ID_CURSOR, CEL_ID_CURSOR, ANM_ID_CURSOR );
}


// ポケモン選択画面移動テーブル
static const POINTER_WORK P1_CursorPosTbl[] =
{
	{   8,   8, 120,  40, 6, 2, 6, 1 },		// 0
	{ 136,  16, 248,  48, 4, 3, 0, 2 },		// 1
	{   8,  56, 120,  88, 0, 4, 1, 3 },		// 2
	{ 136,  64, 248,  96, 1, 5, 2, 4 },		// 3
	{   8, 104, 120, 136, 2, 1, 3, 5 },		// 4
	{ 136, 112, 248, 144, 3, 6, 4, 6 },		// 5
	{ 224, 160, 248, 184, 5, 0, 5, 0 },		// 6（戻る）
};
static const POINTER_WORK Chg_CursorPosTbl[] =
{
	{  16,  16, 240, 136, 0, BAPP_CMV_RETBIT|1, 0, 0 },		// 0 : いれかえる
	{   8, 160,  96, 184, 0, 1, 1, 2 },						// 1 : 強さを見る
	{ 112, 160, 200, 184, 0, 2, 1, 3 },						// 2 : 技を見る
	{ 224, 160, 248, 184, 0, 3, 2, 3 },						// 3 : 戻る
};
static const POINTER_WORK StMain_CursorPosTbl[] =
{
	{   8, 160,  32, 184, 0, 0, 0, 1 },		// 0 : 上
	{  48, 160,  72, 184, 1, 1, 0, 2 },		// 1 : 下
	{ 104, 160, 192, 184, 2, 2, 1, 3 },		// 2 : 技を見る
	{ 224, 160, 248, 184, 3, 3, 2, 3 },		// 3 : 戻る
};
static const POINTER_WORK StWazaSel_CursorPosTbl[] =
{
	{   8,  56, 120,  88, 0, 2, 0, 1 },		// 0 : 技１
	{ 136,  56, 248,  88, 1, 3, 0, 1 },		// 1 : 技２
	{   8, 104, 120, 136, 0, BAPP_CMV_RETBIT|4, 2, 3 },		// 2 : 技３
	{ 136, 104, 248, 136, 1, BAPP_CMV_RETBIT|7, 2, 3 },		// 3 : 技４
	{   8, 160,  32, 184, 2, 4, 4, 5 },		// 4 : 上
	{  48, 160,  72, 184, 2, 5, 4, 6 },		// 5 : 下
	{ 104, 160, 192, 184, 3, 6, 5, 7 },		// 6 : 強さを見る
	{ 224, 160, 248, 184, 3, 7, 6, 7 },		// 7 : 戻る
};
static const POINTER_WORK StWazaInfo_CursorPosTbl[] =
{
	{  92, 157, 124, 165, 0, 2, 0, 1 },		// 0 : 技１
	{ 132, 157, 164, 165, 1, 3, 0, 4 },		// 1 : 技２
	{  92, 173, 124, 181, 0, 2, 2, 3 },		// 2 : 技３
	{ 132, 173, 164, 181, 1, 3, 2, 4 },		// 3 : 技４
	{ 224, 160, 248, 184, 4, 4, BAPP_CMV_RETBIT|3, 4 },		// 4 : 戻る
};
static const POINTER_WORK DelSel_CursorPosTbl[] =
{
	{   8,  56, 120,  88, 5, 2, 0, 1 },						// 0 : 技１画面へ
	{ 136,  56, 248,  88, 5, 3, 0, 1 },						// 1 : 技２画面へ
	{   8, 104, 120, 136, 0, 4, 2, 3 },						// 2 : 技３画面へ
	{ 136, 104, 248, 136, 1, 6, 2, 3 },						// 3 : 技４画面へ
	{  72, 152, 184, 184, 2, 4, 4, 6 },						// 4 : 技５画面へ
	{ 192,   8, 248,  24, 5, BAPP_CMV_RETBIT|1, 0, 5 },		// 5 : 戦闘<->コンテストの切り替え
	{ 224, 160, 248, 184, 3, 6, 4, 6 },						// 6 : 戻る
};

static const POINTER_WORK DelInfo_CursorPosTbl[] =
{
	{   8, 160, 200, 184, 1, 0, 0, 2 },						// 0 : わすれる
	{ 192,   8, 248,  24, 1, BAPP_CMV_RETBIT|2, 0, 1 },		// 1 : 戦闘<->コンテストの切り替え
	{ 224, 160, 248, 184, 1, 2, 0, 2 },						// 2 : 戻る
};

static const POINTER_WORK PPRcv_CursorPosTbl[] =
{
	{   8,  56, 120,  88, 0, 2, 0, 1 },						// 0 : 技１回復
	{ 136,  56, 248,  88, 1, 3, 0, 1 },						// 1 : 技２回復
	{   8, 104, 120, 136, 0, 4, 2, 3 },						// 2 : 技３回復
	{ 136, 104, 248, 136, 1, 4, 2, 3 },						// 3 : 技４回復
	{ 224, 160, 248, 184, BAPP_CMV_RETBIT|3, 4, 4, 4 },		// 4 : 戻る
};

static const POINTER_WORK * const CursorPosTable[] = {
	P1_CursorPosTbl,			// ポケモン選択ページ
	Chg_CursorPosTbl,			// ポケモン入れ替えページ
	StMain_CursorPosTbl,		// ステータスメインページ
	StWazaSel_CursorPosTbl,		// ステータス技選択ページ
	StWazaInfo_CursorPosTbl,	// ステータス技詳細ページ
	PPRcv_CursorPosTbl,			// PP回復技選択ページ
	DelSel_CursorPosTbl,		// ステータス技忘れ１ページ（戦闘技選択）
	DelInfo_CursorPosTbl,		// ステータス技忘れ２ページ（戦闘技詳細）
	DelSel_CursorPosTbl,		// ステータス技忘れ３ページ（コンテスト技選択）
	DelInfo_CursorPosTbl,		// ステータス技忘れ４ページ（コンテスト技詳細）
};

/*
#define	P1_DEF_CMV_TBL	( 0x40 )	// ページ１のデフォルトカーソル移動テーブル
#define	P2_DEF_CMV_TBL	( 0x1e1 )	// ページ２のデフォルトカーソル移動テーブル
#define	P7_DEF_CMV_TBL	( 0x10 )	// ページ７のデフォルトカーソル移動テーブル

static void BPL_P1CursorMvTblMake( BPLIST_WORK * wk )
{
	u32	tbl;
	u32	i;

	tbl = P1_DEF_CMV_TBL;
	for( i=0; i<6; i++ ){
		if( wk->poke[i].mons == 0 ){ continue; }
		tbl |= (1<<i);
	}
	BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, tbl );
}

void BPL_P2CursorMvTblMake( BPLIST_WORK * wk )
{
	u32	tbl;
	u32	i;

	tbl = P2_DEF_CMV_TBL;
	for( i=0; i<4; i++ ){
		if( wk->poke[wk->dat->sel_poke].waza[i].id == 0 ){ continue; }
		tbl |= (1<<(i+1));
	}
	BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, tbl );
}

static void BPL_P7CursorMvTblMake( BPLIST_WORK * wk )
{
	u32	tbl;
	u32	i;

	tbl = P7_DEF_CMV_TBL;
	for( i=0; i<4; i++ ){
		if( wk->poke[wk->dat->sel_poke].waza[i].id == 0 ){ continue; }
		tbl |= (1<<i);
	}
	BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, tbl );
}
*/

#define	WAZADEL_SEL_MV_TBL_N	( 0x7f )	// 技忘れの技選択のカーソル移動テーブル（通常）
#define	WAZADEL_SEL_MV_TBL_C	( 0x5f )	// 技忘れの技選択のカーソル移動テーブル（コンテストなし）
#define	WAZADEL_MAIN_MV_TBL_N	( 7 )	// 技忘れの詳細のカーソル移動テーブル（通常）
#define	WAZADEL_MAIN_MV_TBL_C	( 5 )	// 技忘れの詳細のカーソル移動テーブル（コンテストなし）

static void BPL_WazaDelSelCursorMvTblMake( BPLIST_WORK * wk )
{
	if( wk->ev_contest == 0 ){
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, WAZADEL_SEL_MV_TBL_C );
	}else{
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, WAZADEL_SEL_MV_TBL_N );
	}
}

static void BPL_WazaDelMainCursorMvTblMake( BPLIST_WORK * wk )
{
	if( wk->ev_contest == 0 ){
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, WAZADEL_MAIN_MV_TBL_C );
	}else{
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, WAZADEL_MAIN_MV_TBL_N );
	}
}


void BattlePokeList_CursorMoveSet( BPLIST_WORK * wk, u8 page )
{
	BAPP_CursorMvWkSetPoint( wk->cmv_wk, CursorPosTable[page] );

	switch( page ){

	case BPLIST_PAGE_SELECT:		// ポケモン選択ページ
//		if( BAPP_CursorMvWkGetFlag( wk->cmv_wk ) == 1 ){
//			OS_Printf( "SEL_POS : %d\n", wk->dat->sel_poke );
			BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->dat->sel_poke );
//		}
//		BPL_P1CursorMvTblMake( wk );
		wk->chg_page_cp = 0;
		wk->dat->sel_wp = 0;
		break;

	case BPLIST_PAGE_POKE_CHG:		// ポケモン入れ替えページ
		BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->chg_page_cp );
		wk->dat->sel_wp = 0;
		break;

	case BPLIST_PAGE_WAZA_SEL:		// ステータス技選択ページ
	case BPLIST_PAGE_SKILL:			// ステータス技詳細ページ
		BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->dat->sel_wp );
		break;

/*
	case BPLIST_PAGE_MAIN:			// ステータスメインページ
//		if( BAPP_CursorMvWkGetFlag( wk->cmv_wk ) == 1 && wk->page == BPLIST_PAGE_SKILL ){
		if( wk->page == BPLIST_PAGE_SKILL ){
			BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->dat->sel_wp+1 );
		}
		BPL_P2CursorMvTblMake( wk );
		break;
*/
//	case BPLIST_PAGE_WAZA_SEL:		// ステータス詳細ページ
//	case BPLIST_PAGE_SKILL:			// ステータス技ページ
//	case BPLIST_PAGE_WAZASET_BS:	// ステータス技忘れ１ページ（戦闘技選択）
//	case BPLIST_PAGE_WAZASET_BI:	// ステータス技忘れ２ページ（戦闘技詳細）
/*
	case BPLIST_PAGE_PP_RCV:		// PP回復技選択ページ
//		BPL_P7CursorMvTblMake( wk );
		break;
*/

	case BPLIST_PAGE_WAZASET_BS:	// ステータス技忘れ１ページ（戦闘技選択）
	case BPLIST_PAGE_WAZASET_CS:	// ステータス技忘れ３ページ（コンテスト技選択）
		BPL_WazaDelSelCursorMvTblMake( wk );
		BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->wws_page_cp );
		break;

	case BPLIST_PAGE_WAZASET_BI:	// ステータス技忘れ２ページ（戦闘技詳細）
	case BPLIST_PAGE_WAZASET_CI:	// ステータス技忘れ４ページ（コンテスト技詳細）
		BPL_WazaDelMainCursorMvTblMake( wk );
		BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->wwm_page_cp );
		break;
	}
}


void BattlePokeList_CursorOff( BPLIST_WORK * wk )
{
	BAPP_CursorMvWkSetFlag( wk->cmv_wk, 0 );
	BAPP_CursorMvWkPosInit( wk->cmv_wk );
	BCURSOR_OFF( BAPP_CursorMvWkGetBCURSOR_PTR( wk->cmv_wk ) );
}
