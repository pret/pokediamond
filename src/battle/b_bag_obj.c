//============================================================================================
/**
 * @file	b_bag_obj.c
 * @brief	戦闘用バッグ画面 OBJ関連
 * @author	Hiroyuki Nakamura
 * @date	05.02.15
 */
//============================================================================================
#include "common.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "battle/battle_common.h"
#include "battle/fight_tool.h"
#include "itemtool/item.h"
#include "b_app_tool.h"

#include "../src/demo/ev_pokeselect.naix"

#define	B_BAG_OBJ_H_GLOBAL
#include "b_bag.h"
#include "b_bag_main.h"
#include "b_bag_obj.h"
#include "b_bag_item.h"


//============================================================================================
//	定数定義
//============================================================================================
#define	CLACT_ID_COMMON		( 46263 )	// この画面で使用するセルアクターのID

// キャラリソースID
enum {
	CHR_ID_ITEM1 = CLACT_ID_COMMON,		// アイテムアイコン：１
	CHR_ID_ITEM2,						// アイテムアイコン：２
	CHR_ID_ITEM3,						// アイテムアイコン：３
	CHR_ID_ITEM4,						// アイテムアイコン：４
	CHR_ID_ITEM5,						// アイテムアイコン：５
	CHR_ID_ITEM6,						// アイテムアイコン：６
	CHR_ID_GETDEMO,						// 捕獲デモカーソル
	CHR_ID_CURSOR,						// カーソル

	CHR_ID_MAX = CHR_ID_CURSOR - CLACT_ID_COMMON + 1
};

// パレットリソースID
enum {
	PAL_ID_ITEM1 = CLACT_ID_COMMON,		// アイテムアイコン：１
	PAL_ID_ITEM2,						// アイテムアイコン：２
	PAL_ID_ITEM3,						// アイテムアイコン：３
	PAL_ID_ITEM4,						// アイテムアイコン：４
	PAL_ID_ITEM5,						// アイテムアイコン：５
	PAL_ID_ITEM6,						// アイテムアイコン：６
	PAL_ID_GETDEMO,						// 捕獲デモカーソル
	PAL_ID_CURSOR,						// カーソル

	PAL_ID_MAX = PAL_ID_CURSOR - CLACT_ID_COMMON + 1
};

// セルリソースID
enum {
	CEL_ID_ITEM = CLACT_ID_COMMON,		// アイテムアイコン
	CEL_ID_GETDEMO,						// 捕獲デモカーソル
	CEL_ID_CURSOR,						// カーソル

	CEL_ID_MAX = CEL_ID_CURSOR - CLACT_ID_COMMON + 1
};

// セルアニメリソースID
enum {
	ANM_ID_ITEM = CLACT_ID_COMMON,		// アイテムアイコン
	ANM_ID_GETDEMO,						// 捕獲デモカーソル
	ANM_ID_CURSOR,						// カーソル

	ANM_ID_MAX = ANM_ID_CURSOR - CLACT_ID_COMMON + 1
};

#define	CURSOR_CLA_MAX		( 5 )		// カーソルのOBJ数
#define	FINGER_CLA_MAX		( 1 )		// 指カーソルのOBJ数


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void BBAG_ClactResManInit( BBAG_WORK * wk );
static void BBAG_ClactItemLoad( BBAG_WORK * wk );
static void BBAG_ItemIconCharChg( BBAG_WORK * wk, u16 item, u32 res_id );
static void BBAG_ItemIconPlttChg( BBAG_WORK * wk, u16 item, u16 pos, u32 res_id );
static void BBAG_ClactGetDemoLoad( BBAG_WORK * wk );
static void BBAG_ClactAddAll( BBAG_WORK * wk );
static void BBAG_Page1ObjSet( BBAG_WORK * wk );
static void BBAG_Page2ObjSet( BBAG_WORK * wk );
static void BBAG_Page3ObjSet( BBAG_WORK * wk );
static void BBAG_ClactCursorAdd( BBAG_WORK * wk );
static void BBAG_CursorDel( BBAG_WORK * wk );
static void BBAG_ClactGetDemoCursorAdd( BBAG_WORK * wk );
static void BBAG_GetDemoCursorDel( BBAG_WORK * wk );


//============================================================================================
//	グローバル変数
//============================================================================================
// ページ１のポケモンアイコンの座標
static const int P1_ItemIconPos[2] = { 24, 178 };

// ページ２のアイテムアイコンの座標
static const int P2_ItemIconPos[][2] =
{
	{  44,  45 }, { 172,  45 },
	{  44,  93 }, { 172,  93 },
	{  44, 141 }, { 172, 141 },
};

// ページ３のポケモンアイコンの座標
static const int P3_ItemIconPos[2] = { 40, 44 };

// セルアクターのデータ
static const int ClactDat[][5] =
{	// char, pal, cell, anm, obj_pri
	{ CHR_ID_ITEM1, PAL_ID_ITEM1, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
	{ CHR_ID_ITEM2, PAL_ID_ITEM2, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
	{ CHR_ID_ITEM3, PAL_ID_ITEM3, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
	{ CHR_ID_ITEM4, PAL_ID_ITEM4, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
	{ CHR_ID_ITEM5, PAL_ID_ITEM5, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
	{ CHR_ID_ITEM6, PAL_ID_ITEM6, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
//	{ CHR_ID_GETDEMO, PAL_ID_GETDEMO, CEL_ID_GETDEMO, ANM_ID_GETDEMO, 0 }
};



//--------------------------------------------------------------------------------------------
/**
 * 戦闘用バッグOBJ初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_ObjInit( BBAG_WORK * wk )
{
	BBAG_ClactResManInit( wk );
	BBAG_ClactItemLoad( wk );
//	BBAG_ClactGetDemoLoad( wk );
	BBAG_ClactAddAll( wk );
	BBAG_ClactCursorAdd( wk );
	BBAG_ClactGetDemoCursorAdd( wk );

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
static void BBAG_ClactResManInit( BBAG_WORK * wk )
{
	TCATS_RESOURCE_NUM_LIST	crnl = { CHR_ID_MAX, PAL_ID_MAX, CEL_ID_MAX, ANM_ID_MAX, 0, 0 };
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	wk->crp = CATS_ResourceCreate( csp );
	CATS_ClactSetInit( csp, wk->crp, BBAG_CA_MAX+CURSOR_CLA_MAX+FINGER_CLA_MAX );
	CATS_ResourceManagerInit( csp, wk->crp, &crnl );
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
static void BBAG_ClactItemLoad( BBAG_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	for( i=0; i<6; i++ ){
		// キャラ
		CATS_LoadResourceCharArc(
			csp, wk->crp, ARC_ITEMICON,
			GetItemIndex(1,ITEM_GET_ICON_CGX), 0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_ITEM1+i );
		// パレット
		CATS_LoadResourcePlttWorkArc(
			wk->pfd, FADE_SUB_OBJ, csp, wk->crp, ARC_ITEMICON,
			GetItemIndex(1,ITEM_GET_ICON_PAL), 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_ITEM1+i );
	}
	// セル
	CATS_LoadResourceCellArc( csp, wk->crp, ARC_ITEMICON, ItemIconCellGet(), 0, CEL_ID_ITEM );
	// セルアニメ
	CATS_LoadResourceCellAnmArc( csp, wk->crp, ARC_ITEMICON, ItemIconCAnmGet(), 0, ANM_ID_ITEM );
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコン切り替え
 *
 * @param	wk		ワーク
 * @param	cap		セルアクターデータ
 * @param	item	アイテム番号
 * @param	res_id	キャラリソースID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BBAG_ItemIconCharChg( BBAG_WORK * wk, u16 item, u32 res_id )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	CATS_ChangeResourceCharArc(
		csp, wk->crp, ARC_ITEMICON,
		GetItemIndex(item,ITEM_GET_ICON_CGX), 0, res_id );
}

static void BBAG_ItemIconPlttChg( BBAG_WORK * wk, u16 item, u16 pos, u32 res_id )
{
	PaletteWorkSet_Arc(
		wk->pfd, ARC_ITEMICON,
		GetItemIndex(item,ITEM_GET_ICON_PAL), wk->dat->heap,FADE_SUB_OBJ, 0x20, pos*16 );
}


//--------------------------------------------------------------------------------------------
/**
 * 捕獲デモカーソルのグラフィックロード
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
/*
static void BBAG_ClactGetDemoLoad( BBAG_WORK * wk )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// キャラ
	CATS_LoadResourceCharArc(
		csp, wk->crp, ARC_EV_POKESELECT_GRA,
		NARC_ev_pokeselect_psel_cursol_NCGR, 0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_GETDEMO );
	// パレット
	CATS_LoadResourcePlttWorkArc(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp, ARC_EV_POKESELECT_GRA,
		NARC_ev_pokeselect_psel_cursol_NCLR, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_GETDEMO );
	// セル
	CATS_LoadResourceCellArc(
		csp, wk->crp, ARC_EV_POKESELECT_GRA,
		NARC_ev_pokeselect_psel_cursol_NCER, 0, CEL_ID_GETDEMO );
	// セルアニメ
	CATS_LoadResourceCellAnmArc(
		csp, wk->crp, ARC_EV_POKESELECT_GRA,
		NARC_ev_pokeselect_psel_cursol_NANR, 0, ANM_ID_GETDEMO );
}
*/

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
static CATS_ACT_PTR BBAG_ClactAdd( BBAG_WORK * wk, u32 id )
{
	TCATS_OBJECT_ADD_PARAM_S	prm;
	CATS_SYS_PTR	csp;

	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	prm.x = 0;
	prm.y = 0;
	prm.z = 0;

	prm.anm = 0;
	prm.pri = ClactDat[id][4];
	prm.pal = 0;
	prm.d_area = NNS_G2D_VRAM_TYPE_2DSUB;

	prm.id[0] = ClactDat[id][0];
	prm.id[1] = ClactDat[id][1];
	prm.id[2] = ClactDat[id][2];
	prm.id[3] = ClactDat[id][3];
	
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
static void BBAG_ClactAddAll( BBAG_WORK * wk )
{
	u32	i;

	for( i=0; i<BBAG_CA_MAX; i++ ){
		wk->cap[i] = BBAG_ClactAdd( wk, i );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 戦闘用バッグOBJ削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_ObjFree( BBAG_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	for( i=0; i<BBAG_CA_MAX; i++ ){
		CATS_ActorPointerDelete_S( wk->cap[i] );
	}

	BBAG_CursorDel( wk );
	BBAG_GetDemoCursorDel( wk );

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
static void BBAG_ClactOn( CATS_ACT_PTR cap, const int x, const int y )
{
	CATS_ObjectEnableCap( cap, 1 );
	CATS_ObjectPosSetCap( cap, x, y );
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
void BattleBag_PageObjSet( BBAG_WORK * wk, u32 page )
{
	u32	i;

	for( i=0; i<BBAG_CA_MAX; i++ ){
		CATS_ObjectEnableCap( wk->cap[i], 0 );
	}

	switch( page ){
	case BBAG_PAGE_POCKET:		// ポケット選択ページ
		BBAG_Page1ObjSet( wk );
		break;
	case BBAG_PAGE_MAIN:		// アイテム選択ページ
		BBAG_Page2ObjSet( wk );
		break;
	case BBAG_PAGE_ITEM:		// アイテム使用ページ
		BBAG_Page3ObjSet( wk );
		break;
	}
}

#define	P1_GETDEMO_CURSOR_X		( 192 )
#define	P1_GETDEMO_CURSOR_Y		( 24 )
#define	P2_GETDEMO_CURSOR_X		( 64 )
#define	P2_GETDEMO_CURSOR_Y		( 16 )
#define	P3_GETDEMO_CURSOR_X		( 104 )
#define	P3_GETDEMO_CURSOR_Y		( 152 )

static void BBAG_Page1ObjSet( BBAG_WORK * wk )
{
	u16	item;

	if( wk->dat->used_item != 0 ){
		BBAG_ItemIconCharChg( wk, wk->dat->used_item, CHR_ID_ITEM1 );
		BBAG_ItemIconPlttChg( wk, wk->dat->used_item, 0, PAL_ID_ITEM1 );
		BBAG_ClactOn( wk->cap[BBAG_CA_ITEM1], P1_ItemIconPos[0], P1_ItemIconPos[1] );
	}
/*
	if( wk->dat->mode == BBAG_MODE_GETDEMO ){
		BBAG_ClactOn( wk->cap[BBAG_CA_GETDEMO], P1_GETDEMO_CURSOR_X, P1_GETDEMO_CURSOR_Y );
	}
*/
}

static void BBAG_Page2ObjSet( BBAG_WORK * wk )
{
	u32	i;
	u16	item;

	for( i=0; i<6; i++ ){
		item = BattleBag_PosItemCheck( wk, i );
		if( item == 0 ){ continue; }
		BBAG_ItemIconCharChg( wk, item, CHR_ID_ITEM1+i );
		BBAG_ItemIconPlttChg( wk, item, (u16)i, PAL_ID_ITEM1+i );
		BBAG_ClactOn( wk->cap[i], P2_ItemIconPos[i][0], P2_ItemIconPos[i][1] );
	}
/*
	if( wk->dat->mode == BBAG_MODE_GETDEMO ){
		BBAG_ClactOn( wk->cap[BBAG_CA_GETDEMO], P2_GETDEMO_CURSOR_X, P2_GETDEMO_CURSOR_Y );
	}
*/
}

static void BBAG_Page3ObjSet( BBAG_WORK * wk )
{
	u16	item;

	item = BattleBag_PosItemCheck( wk, wk->dat->item_pos[wk->poke_id] );
	BBAG_ItemIconCharChg( wk, item, CHR_ID_ITEM1 );
	BBAG_ItemIconPlttChg( wk, item, 0, PAL_ID_ITEM1 );
	BBAG_ClactOn( wk->cap[BBAG_CA_ITEM1], P3_ItemIconPos[0], P3_ItemIconPos[1] );
/*
	if( wk->dat->mode == BBAG_MODE_GETDEMO ){
		BBAG_ClactOn( wk->cap[BBAG_CA_GETDEMO], P3_GETDEMO_CURSOR_X, P3_GETDEMO_CURSOR_Y );
	}
*/
}


//============================================================================================
//	カーソル
//============================================================================================
static void BBAG_ClactCursorAdd( BBAG_WORK * wk )
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

static void BBAG_CursorDel( BBAG_WORK * wk )
{
	BCURSOR_ActorDelete( BAPP_CursorMvWkGetBCURSOR_PTR( wk->cmv_wk ) );
	BCURSOR_ResourceFree(
		wk->crp, CHR_ID_CURSOR, PAL_ID_CURSOR, CEL_ID_CURSOR, ANM_ID_CURSOR );
}


// ポケット選択画面移動テーブル
static const POINTER_WORK P1_CursorPosTbl[] =
{
	{   8,  16, 120,  72, 0, 1, 0, 2 },					// 0 : HP回復ポケット
	{   8,  88, 120, 144, 0, 4, 1, 3 },					// 1 : 状態回復ポケット
	{ 136,  16, 248,  72, 2, 3, 0, 2 },					// 2 : ボールポケット
	{ 136,  88, 248, 144, 2, 5, 1, 3 },					// 3 : 戦闘用ポケット
	{   8, 160, 200, 184, 1, 4, 4, 5 },					// 4 : 最後に使用した道具
	{ 224, 160, 248, 184, BAPP_CMV_RETBIT|3, 5, 4, 5 },	// 5 : 戻る
//	{ 224, 160, 248, 184, BAPP_CMV_RETBIT|3, 5, 4, 5 },	// 5 : 戻る
};

// アイテム選択画面移動テーブル
static const POINTER_WORK P2_CursorPosTbl[] =
{
	{   8,  16, 120,  48, 0, 2, 0, 1 },					// 0 : アイテム１
	{ 136,  16, 248,  48, 1, 3, 0, 1 },					// 1 : アイテム２
	{   8,  64, 120,  96, 0, 4, 2, 3 },					// 2 : アイテム３
	{ 136,  64, 248,  96, 1, 5, 2, 3 },					// 3 : アイテム４
	{   8, 112, 120, 144, 2, BAPP_CMV_RETBIT|6, 4, 5 },	// 4 : アイテム５
	{ 136, 112, 248, 144, 3, 8, 4, 5 },					// 5 : アイテム６
	{   8, 160,  32, 184, 4, 6, 6, 7 },					// 6 : 前へ
	{  48, 160,  72, 184, 4, 7, 6, 8 },					// 7 : 次へ
	{ 224, 160, 248, 184, 5, 8, 7, 8 },					// 8 : 戻る
};

// アイテム選択画面移動テーブル
static const POINTER_WORK P3_CursorPosTbl[] =
{
	{   8, 160, 200, 184, 0, 0, 0, 1 },	// 0 : 使う
	{ 224, 160, 248, 184, 1, 1, 0, 1 },	// 1 : 戻る
};

static const POINTER_WORK * const CursorPosTable[] = {
	P1_CursorPosTbl,
	P2_CursorPosTbl,
	P3_CursorPosTbl,
};


#define	P1_DEF_CMV_TBL	( 0x3f )	// ページ１のデフォルトカーソル移動テーブル
#define	P1_LST_CMV_TBL	( 0x2f )	// ページ１の最後に使った道具有のカーソル移動テーブル
#define	P2_DEF_CMV_TBL	( 0x100 )	// ページ２のデフォルトカーソル移動テーブル
#define	P2_PAGE_TBL		( 0xc0 )	// ページ２のページ切り替えカーソル移動テーブル

/*
void BBAG_P1CursorMvTblMake( BBAG_WORK * wk )
{
	if( wk->dat->used_item != 0 ){
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, P1_DEF_CMV_TBL );
	}else{
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, P1_LST_CMV_TBL );
	}
}
*/

void BBAG_P2CursorMvTblMake( BBAG_WORK * wk )
{
	u32	tbl;
	u32	i;

	tbl = P2_DEF_CMV_TBL;
	for( i=0; i<6; i++ ){
		if( wk->pocket[wk->poke_id][wk->dat->item_scr[wk->poke_id]*6+i].id == 0 ){
			continue;
		}
		tbl |= (1<<i);
	}
	if( wk->scr_max[wk->poke_id] != 0 ){
		tbl |= P2_PAGE_TBL;
	}
	BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, tbl );
}

void BattleBag_CursorMoveSet( BBAG_WORK * wk, u8 page )
{
	BAPP_CursorMvWkSetPoint( wk->cmv_wk, CursorPosTable[page] );

	switch( page ){
	case BBAG_PAGE_POCKET:		// ポケット選択ページ
//		if( BAPP_CursorMvWkGetFlag( wk->cmv_wk ) == 1 ){
			BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->poke_id );
//		}
//		BBAG_P1CursorMvTblMake( wk );
		break;

	case BBAG_PAGE_MAIN:		// アイテム選択ページ
//		if( BAPP_CursorMvWkGetFlag( wk->cmv_wk ) == 1 ){
			BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->dat->item_pos[wk->poke_id] );
//		}
//		BBAG_P2CursorMvTblMake( wk );
		break;

	case BBAG_PAGE_ITEM:		// アイテム使用ページ
		break;
	}
}

void BattleBag_CursorOff( BBAG_WORK * wk )
{
	BAPP_CursorMvWkSetFlag( wk->cmv_wk, 0 );
	BAPP_CursorMvWkPosInit( wk->cmv_wk );
	BCURSOR_OFF( BAPP_CursorMvWkGetBCURSOR_PTR( wk->cmv_wk ) );
}



//============================================================================================
//	捕獲デモカーソル
//============================================================================================
/*
void BattleBag_GetDemoCursorAnm( BBAG_WORK * wk )
{
	CATS_ObjectUpdateNumCap( wk->cap[BBAG_CA_GETDEMO], FX32_ONE );
//	BattleBag_GetDemoCursorPush( wk );
}

void BattleBag_GetDemoCursorPush( BBAG_WORK * wk )
{
//	if( wk->get_anm == 1 ){
		s16	x, y;
		CATS_ObjectPosGetCap( wk->cap[BBAG_CA_GETDEMO], &x, &y );
		CATS_ObjectPosSetCap( wk->cap[BBAG_CA_GETDEMO], x, y+8 );
//	}
}
*/

static void BBAG_ClactGetDemoCursorAdd( BBAG_WORK * wk )
{
	CATS_SYS_PTR csp;
	FINGER_PTR	finger;

	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	FINGER_ResourceLoad(
		csp, wk->crp, wk->pfd, CHR_ID_GETDEMO, PAL_ID_GETDEMO, CEL_ID_GETDEMO, ANM_ID_GETDEMO );


	wk->finger = FINGER_ActorCreate(
					csp, wk->crp, wk->dat->heap,
					CHR_ID_GETDEMO, PAL_ID_GETDEMO, CEL_ID_GETDEMO, ANM_ID_GETDEMO, 0, 0 );
}

static void BBAG_GetDemoCursorDel( BBAG_WORK * wk )
{
	FINGER_ActorDelete( wk->finger );
	FINGER_ResourceFree(
		wk->crp, CHR_ID_GETDEMO, PAL_ID_GETDEMO, CEL_ID_GETDEMO, ANM_ID_GETDEMO );
}


#define	GET_DEMO_FINGER_WAIT	( 60 )

static const int GetDemoCursorPos[3][2] =
{
	{ P1_GETDEMO_CURSOR_X, P1_GETDEMO_CURSOR_Y },
	{ P2_GETDEMO_CURSOR_X, P2_GETDEMO_CURSOR_Y },
	{ P3_GETDEMO_CURSOR_X, P3_GETDEMO_CURSOR_Y }
};

void BBAG_GetDemoCursorSet( BBAG_WORK * wk, u8 page )
{
	if( wk->dat->mode == BBAG_MODE_GETDEMO ){
		FINGER_PosSetON( wk->finger, GetDemoCursorPos[page][0], GetDemoCursorPos[page][1] );
		FINGER_TouchReq( wk->finger, GET_DEMO_FINGER_WAIT );
	}else{
		FINGER_OFF( wk->finger );
	}
}
