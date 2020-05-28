//============================================================================================
/**
 * @file	fd_shop.c
 * @brief	フレンドリィショップ処理
 * @author	Hiroyuki Nakamura
 * @date	2004.12.15
 */
//============================================================================================
#include "common.h"
#include "savedata/fnote_mem.h"
#include "system/procsys.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/buflen.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/snd_tool.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/wipe.h"
#include "itemtool/item.h"
#include "itemtool/myitem.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_shop.h"
#include "msgdata/msg_undergroundgoods.h"
#include "msgdata/msg_place_name.h"
#include "application/app_tool.h"
#include "application/bag.h"
#include "application/cb_sys.h"

#include "fieldsys.h"
#include "fieldmap.h"
#include "field_clact.h"
#include "fld_bmp.h"
#include "talk_msg.h"
#include "syswork.h"
#include "zonedata.h"
#include "mapdefine.h"

#include "goods_data.h"
#include "../fielddata/base_goods/goods_id_def.h"
#include "savedata/undergrounddata.h"

#include "savedata/record.h"

#define	FD_SHOP_H_GLOBAL
#include "fd_shop_sys.h"
#include "fd_shop.h"
#include "fd_shop_snd_def.h"
#include "shop_gra.naix"

#include "fld_debug.h"		//DEBUG_VIEW_HOOK

//============================================================================================
//	定数定義
//============================================================================================


// BGフレーム
#define	SHOP_FRM_3D			( FLD_MBGFRM_MAP )		// 3D面
#define	SHOP_FRM_BG			( FLD_MBGFRM_EFFECT1 )	// 枠
#define	SHOP_FRM_LIST		( FLD_MBGFRM_EFFECT2 )	// アイテムリスト
#define	SHOP_FRM_WINDOW		( FLD_MBGFRM_FONT )		// ウィンドウ面
#define	SHOP_BG_PAL			( 0 )

#define	SHOP_TALK_WIN_CGX	( 1 )
#define	SHOP_MENU_WIN_CGX	( SHOP_TALK_WIN_CGX + TALK_WIN_CGX_SIZ )

// BMPウィンドウ定義
// ショップメニュー（フィールドの領域に注意！）
#define	WIN_SHOP_MENU_PX	( 1 )
#define	WIN_SHOP_MENU_PY	( 1 )
#define	WIN_SHOP_MENU_SX	( 13 )
#define	WIN_SHOP_MENU_SY	( 6 )		// アイテムショップ
#define	WIN_SHOP_MENU_SY_GS	( 4 )		// グッズ・シールショップ
#define	WIN_SHOP_MENU_PAL	( FLD_SYSFONT_PAL )
#define	WIN_SHOP_MENU_CGX	( FLD_MSG_WIN_CGX - ( WIN_SHOP_MENU_SX * WIN_SHOP_MENU_SY ) )

// アイテムリスト
#define	WIN_SHOP_LIST_PX	( 13 )
#define	WIN_SHOP_LIST_PY	( 2 )
#define	WIN_SHOP_LIST_SX	( 18 )
#define	WIN_SHOP_LIST_SY	( 14 )
#define	WIN_SHOP_LIST_FRM	( SHOP_FRM_LIST )
#define	WIN_SHOP_LIST_PAL	( FLD_SYSFONT_PAL )
//#define	WIN_SHOP_LIST_CGX	( SHOP_MENU_WIN_CGX - ( WIN_SHOP_LIST_SX * WIN_SHOP_LIST_SY ) )
#define	WIN_SHOP_LIST_CGX	( 1 )
// アイテム説明
#define	WIN_SHOP_INFO_PX	( 5 )		// アイテムショップ
#define	WIN_SHOP_INFO_PX_GS	( 1 )		// グッズ・シールショップ
#define	WIN_SHOP_INFO_PY	( 18 )
#define	WIN_SHOP_INFO_SX	( 27 )
#define	WIN_SHOP_INFO_SY	( 6 )
#define	WIN_SHOP_INFO_FRM	( SHOP_FRM_LIST )
#define	WIN_SHOP_INFO_PAL	( FLD_SYSFONT_PAL )
//#define	WIN_SHOP_INFO_CGX	( WIN_SHOP_LIST_CGX - ( WIN_SHOP_INFO_SX * WIN_SHOP_INFO_SY ) )
#define	WIN_SHOP_INFO_CGX	( WIN_SHOP_LIST_CGX + ( WIN_SHOP_LIST_SX * WIN_SHOP_LIST_SY ) )

// おこずかい
#define	WIN_SHOP_GOLD_PX	( 1 )
#define	WIN_SHOP_GOLD_PY	( 1 )
#define	WIN_SHOP_GOLD_SX	( 10 )
#define	WIN_SHOP_GOLD_SY	( 4 )
#define	WIN_SHOP_GOLD_FRM	( SHOP_FRM_WINDOW )
#define	WIN_SHOP_GOLD_PAL	( FLD_SYSFONT_PAL )
//#define	WIN_SHOP_GOLD_CGX	( WIN_SHOP_INFO_CGX - ( WIN_SHOP_GOLD_SX * WIN_SHOP_GOLD_SY ) )
#define	WIN_SHOP_GOLD_CGX	( SHOP_MENU_WIN_CGX + MENU_WIN_CGX_SIZ )
// 個数選択
#define	WIN_SHOP_NUM_PX		( 19 )
#define	WIN_SHOP_NUM_PY		( 13 )
#define	WIN_SHOP_NUM_SX		( 12 )
#define	WIN_SHOP_NUM_SY		( 4 )
#define	WIN_SHOP_NUM_FRM	( SHOP_FRM_WINDOW )
#define	WIN_SHOP_NUM_PAL	( FLD_SYSFONT_PAL )
//#define	WIN_SHOP_NUM_CGX	( WIN_SHOP_GOLD_CGX - ( WIN_SHOP_NUM_SX * WIN_SHOP_NUM_SY ) )
#define	WIN_SHOP_NUM_CGX	( WIN_SHOP_GOLD_CGX + ( WIN_SHOP_GOLD_SX * WIN_SHOP_GOLD_SY ) )
// 持っている数
#define	WIN_SHOP_MINE_PX	( 1 )
#define	WIN_SHOP_MINE_PY	( 15 )
#define	WIN_SHOP_MINE_SX	( 14 )
#define	WIN_SHOP_MINE_SY	( 2 )
#define	WIN_SHOP_MINE_FRM	( SHOP_FRM_WINDOW )
#define	WIN_SHOP_MINE_PAL	( FLD_SYSFONT_PAL )
//#define	WIN_SHOP_MINE_CGX	( WIN_SHOP_NUM_CGX - ( WIN_SHOP_MINE_SX * WIN_SHOP_MINE_SY ) )
#define	WIN_SHOP_MINE_CGX	( WIN_SHOP_NUM_CGX + ( WIN_SHOP_NUM_SX * WIN_SHOP_NUM_SY ) )
// 会話
#define	WIN_SHOP_TALK_PX	( 2 )
#define	WIN_SHOP_TALK_PY	( 19 )
#define	WIN_SHOP_TALK_SX	( 27 )
#define	WIN_SHOP_TALK_SY	( 4 )
#define	WIN_SHOP_TALK_FRM	( SHOP_FRM_WINDOW )
#define	WIN_SHOP_TALK_PAL	( FLD_MESFONT_PAL )
//#define	WIN_SHOP_TALK_CGX	( WIN_SHOP_MINE_CGX - ( WIN_SHOP_TALK_SX * WIN_SHOP_TALK_SY ) )
#define	WIN_SHOP_TALK_CGX	( WIN_SHOP_MINE_CGX + ( WIN_SHOP_MINE_SX * WIN_SHOP_MINE_SY ) )
// はい・いいえ
#define	WIN_SHOP_YESNO_PX	( 23 )
#define	WIN_SHOP_YESNO_PY	( 13 )
#define	WIN_SHOP_YESNO_SX	( 7 )
#define	WIN_SHOP_YESNO_SY	( 4 )
#define	WIN_SHOP_YESNO_FRM	( SHOP_FRM_WINDOW )
#define	WIN_SHOP_YESNO_PAL	( FLD_SYSFONT_PAL )
//#define	WIN_SHOP_YESNO_CGX	( WIN_SHOP_TALK_CGX - ( WIN_SHOP_YESNO_SX * WIN_SHOP_YESNO_SY ) )
#define	WIN_SHOP_YESNO_CGX	( WIN_SHOP_TALK_CGX + ( WIN_SHOP_TALK_SX * WIN_SHOP_TALK_SY ) )

#define	SHOPCOL_N_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// フォントカラー：黒
#define	SHOPCOL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// フォントカラー：白
#define	SHOPCOL_N_BLUE	( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// フォントカラー：青
#define	SHOPCOL_N_RED	( GF_PRINTCOLOR_MAKE( 5, 6, 0 ) )		// フォントカラー：赤

#define	MSG_BUFLEN		( 24*2*2 )


#define	CURSOR_ACT_PX	( 176 )
#define	CURSOR_ACT_PY	( 24 )


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static u8 CameraMoveCntGet( FIELDSYS_WORK * fsys );
static u8 ShopEndSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk );
static void ShopInitSeq( SHOP_WORK * wk );
static void ShopMsgCreate( SHOP_WORK * wk );
static void ShopMenuSet( SHOP_WORK * wk );
static u8 ShopMenuSelect( SHOP_WORK * wk );
static void ShopMenuExit( SHOP_WORK * wk );
static void ShopBuyInitSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk );
static void ShopBuyWinAdd( SHOP_WORK * wk );
static void ShopBuyGraphicSet( SHOP_WORK * wk );
static u8 ShopBuyScrollSeq( SHOP_WORK * wk );
static u8 ShopBuySelectSeq( SHOP_WORK * wk );
static u8 ShopBuyEndSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk );
static void ShopBuyItemListMake( SHOP_WORK * wk );
static void CB_ItemListMove( BMPLIST_WORK * work, u32 param, u8 mode );
static void CB_ItemListWrite( BMPLIST_WORK * work, u32 param, u8 y );
static void ShopBuyGoldWinPut( SHOP_WORK * wk, u8 flg );
static u8 ShopBuySelWaitSeq( SHOP_WORK * wk );
static u8 ShopBuyNumSelSeq( SHOP_WORK * wk );
static void NumSelWinPut( SHOP_WORK * wk, u8 flg );
static void MyItemWinPut( SHOP_WORK * wk );
static u8 ShopBuyCmpWaitSeq( SHOP_WORK * wk );
static u8 ShopBuyOmakeWait( SHOP_WORK * wk );
static u8 ShopBuyNumWaitSeq( SHOP_WORK * wk );
static u8 ShopBuyYesNoSeq( SHOP_WORK * wk );
static u8 ShopBuyCmpSeq( SHOP_WORK * wk );
static u8 ShopBuyMenuRetSeq( SHOP_WORK * wk );
static void ShopExitSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk );
static void ShopSaleInitSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk );
static void ShopSaleCallSeq( GMEVENT_CONTROL * event );
//static u8 ShopSaleWaitSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk );
//static u8 ShopSaleRetSeq( FIELDSYS_WORK * fsys );
static u8 ShopSaleMenuRetSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk );

static void ShopBuyActSet( SHOP_WORK * wk );
static void ShopBuyActExit( SHOP_WORK * wk );
static void load2DResFile( SHOP_WORK * wk );
static int loadOneData(
			CLACT_U_RES_MANAGER_PTR resMan, CLACT_U_RES_OBJ_TBL** resObjTbl, const char* path );

static void ShopBuyScrCurPosChg( SHOP_WORK * wk, u8 flg );

static void ShopBuyItemIconChg( SHOP_WORK * wk, u16 item );
static void ShopBuyCursorPalChg( SHOP_WORK * wk, u8 num );

static u8 ShopBuyCmpCheck( SHOP_WORK * wk );
static void ShopBuyItemNameWordSet( SHOP_WORK * wk, u16 item, u16 bufID );
static u32 ShopBuyItemPriceGet( SHOP_WORK * wk, u16 item );


//============================================================================================
//	グローバル変数
//============================================================================================
static const BMPWIN_DAT ShopBuyBmpWin[] =
{
	{	// アイテムリスト
		WIN_SHOP_LIST_FRM, WIN_SHOP_LIST_PX, WIN_SHOP_LIST_PY,
		WIN_SHOP_LIST_SX, WIN_SHOP_LIST_SY, WIN_SHOP_LIST_PAL, WIN_SHOP_LIST_CGX
	},
	{	// アイテム説明
		WIN_SHOP_INFO_FRM, WIN_SHOP_INFO_PX, WIN_SHOP_INFO_PY,
		WIN_SHOP_INFO_SX, WIN_SHOP_INFO_SY, WIN_SHOP_INFO_PAL, WIN_SHOP_INFO_CGX
	},
	{	// おこずかい
		WIN_SHOP_GOLD_FRM, WIN_SHOP_GOLD_PX, WIN_SHOP_GOLD_PY,
		WIN_SHOP_GOLD_SX, WIN_SHOP_GOLD_SY, WIN_SHOP_GOLD_PAL, WIN_SHOP_GOLD_CGX
	},
	{	// 個数選択
		WIN_SHOP_NUM_FRM, WIN_SHOP_NUM_PX, WIN_SHOP_NUM_PY,
		WIN_SHOP_NUM_SX, WIN_SHOP_NUM_SY, WIN_SHOP_NUM_PAL, WIN_SHOP_NUM_CGX
	},
	{	// 持っている数
		WIN_SHOP_MINE_FRM, WIN_SHOP_MINE_PX, WIN_SHOP_MINE_PY,
		WIN_SHOP_MINE_SX, WIN_SHOP_MINE_SY, WIN_SHOP_MINE_PAL, WIN_SHOP_MINE_CGX
	},
	{	// 会話
		WIN_SHOP_TALK_FRM, WIN_SHOP_TALK_PX, WIN_SHOP_TALK_PY,
		WIN_SHOP_TALK_SX, WIN_SHOP_TALK_SY, WIN_SHOP_TALK_PAL, WIN_SHOP_TALK_CGX
	},
};

// グッズ・シールの説明
static const BMPWIN_DAT ShopBuyGoodsInfoWin = {
	WIN_SHOP_INFO_FRM, WIN_SHOP_INFO_PX_GS, WIN_SHOP_INFO_PY,
	WIN_SHOP_INFO_SX, WIN_SHOP_INFO_SY, WIN_SHOP_INFO_PAL, WIN_SHOP_INFO_CGX
};

// はい・いいえ
static const BMPWIN_DAT ShopBuyYesNoBmpWin = {
	WIN_SHOP_YESNO_FRM, WIN_SHOP_YESNO_PX, WIN_SHOP_YESNO_PY,
	WIN_SHOP_YESNO_SX, WIN_SHOP_YESNO_SY, WIN_SHOP_YESNO_PAL, WIN_SHOP_YESNO_CGX
};

// バッグのポケットリスト
static const u8 BagList[] = {
	BAG_POKE_NORMAL, BAG_POKE_DRUG, BAG_POKE_BALL, BAG_POKE_WAZA,
	BAG_POKE_NUTS, BAG_POKE_SEAL, BAG_POKE_BATTLE, BAG_POKE_EVENT, 0xff
};



//--------------------------------------------------------------------------------------------
/**
 * アイテムデータをショップワークにセット
 *
 * @param	wk		ショップワーク
 * @param	item	アイテムデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ShopItemSet( SHOP_WORK * wk, u16 * item )
{
	u16	i;

	for( i=0; i<256; i++ ){
		if( item[i] == 0xffff ){ break; }
	}
	wk->max = i;
	wk->item = sys_AllocMemory( HEAPID_WORLD, wk->max*2 );
	for( i=0; i<wk->max; i++ ){
		wk->item[i] = item[i];
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ショップワーク確保
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static SHOP_WORK * ShopWorkAlloc(void)
{
	SHOP_WORK * wk = sys_AllocMemory( HEAPID_WORLD, sizeof(SHOP_WORK) );
	memset( wk, 0, sizeof(SHOP_WORK) );
	return wk;
}



void ShopInit( GMEVENT_CONTROL * event, FIELDSYS_WORK * repw, u16 * item, u8 type, BOOL dp_flg )
{
	SHOP_WORK * wk = ShopWorkAlloc();

	wk->bgl    = repw->bgl;
	wk->msgb   = STRBUF_Create( MSG_BUFLEN, HEAPID_WORLD );
	wk->my     = SaveData_GetMyStatus( repw->savedata );
	wk->cfg    = SaveData_GetConfig( repw->savedata );
	wk->rec    = SaveData_GetRecord( repw->savedata );
	wk->evwk   = SaveData_GetEventWork( repw->savedata );
	wk->dp_flg = dp_flg;
	wk->cm_max = CameraMoveCntGet( repw );
	wk->fnote  = repw->fnote;
	wk->shop_type = type;

	if( wk->shop_type == SHOP_TYPE_ITEM ){
		wk->myitem = SaveData_GetMyItem( repw->savedata );
	}else if( wk->shop_type == SHOP_TYPE_GOODS ){
		wk->myitem = SaveData_GetUnderGroundData( repw->savedata );
	}else{
		wk->myitem = CB_SaveData_AllDataGet( repw->savedata );
	}

//	DummyShopDataSet( wk );
	ShopItemSet( wk, item );

	//FieldEvent_Set( repw, GMEVENT_Shop, wk );
	FieldEvent_Call( event, GMEVENT_Shop, wk );
}



static u8 CameraMoveCntGet( FIELDSYS_WORK * fsys )
{
	int	dir = Player_DirGet( fsys->player );

	if( dir == DIR_UP || dir == DIR_DOWN || dir == DIR_RIGHT ){
		return 10;
	}
	return 8;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	フィールドイベント：メニュー制御
 * @param	event	フィールドイベント用パラメータ
 * @retval	TRUE	イベント終了
 * @retval	FALSE	イベント継続
 */
//--------------------------------------------------------------------------------------------
BOOL GMEVENT_Shop( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	SHOP_WORK * wk;

	fsys = FieldEvent_GetFieldSysWork(event);
	wk = FieldEvent_GetSpecialWork(event);

	switch( wk->seq ){
	case SHOP_SEQ_INIT:
#ifdef PM_DEBUG
		DEBUG_VIEW_HOOK(TRUE);		//デバッグ情報表示不許可
#endif
		ShopInitSeq( wk );
		wk->seq = SHOP_SEQ_MENU;
		break;

	case SHOP_SEQ_MENU:
		wk->seq = ShopMenuSelect( wk );
		break;


	case SHOP_SEQ_BUY_INIT:		// 購入画面初期化
		ShopBuyInitSeq( fsys, wk );
		wk->seq = SHOP_SEQ_BUY_SCROLL;
		break;
	case SHOP_SEQ_BUY_SCROLL:	// 購入位置へスクロール
		wk->seq = ShopBuyScrollSeq( wk );
		break;
	case SHOP_SEQ_BUY_SELECT:	// アイテム選択
		wk->seq = ShopBuySelectSeq( wk );
		break;

	case SHOP_SEQ_BUYSEL_WAIT:	// 「いくつ～」表示ウェイト
		wk->seq = ShopBuySelWaitSeq( wk );
		break;

	case SHOP_SEQ_BUYNUM_SEL:	// 個数選択
		wk->seq = ShopBuyNumSelSeq( wk );
		break;

	case SHOP_SEQ_BUYNUM_WAIT:	// 「合計～なりますが」表示ウェイト
		wk->seq = ShopBuyNumWaitSeq( wk );
		break;

	case SHOP_SEQ_BUY_YESNO:	// はい・いいえ選択
		wk->seq = ShopBuyYesNoSeq( wk );
		break;

	case SHOP_SEQ_BUY_CMP:		// 購入
		wk->seq = ShopBuyCmpSeq( wk );
		break;

	case SHOP_SEQ_BUYCMP_WAIT:	// アイテム選択へ
		wk->seq = ShopBuyCmpWaitSeq( wk );
		break;

	case SHOP_SEQ_BUYOMAKE_WAIT:	// プレミアボール待ち
		wk->seq = ShopBuyOmakeWait( wk );
		break;

	case SHOP_SEQ_BUY_END:		// 購入画面終了
		wk->seq = ShopBuyEndSeq( fsys, wk );
		break;

	case SHOP_SEQ_MENU_RET:		// メニュー選択へ戻り待ち
		wk->seq = ShopBuyMenuRetSeq( wk );
		break;

	case SHOP_SEQ_SALE_INIT:		// 「売る」初期化
		ShopSaleInitSeq( fsys, wk );
		break;

	case SHOP_SEQ_SALE_CALL:		// 「売る」呼び出し
		ShopSaleCallSeq( event );
		break;

	/* 常駐領域の処理に移動 ( fd_shop_sale.c ) */
	case SHOP_SEQ_SALE_WAIT:		// 「売る」終了待ち
	case SHOP_SEQ_SALE_RET:			// 「売る」終了 -> フェードイン
		break;

/*
	case SHOP_SEQ_SALE_WAIT:		// 「売る」終了待ち
		wk->seq = ShopSaleWaitSeq( fsys, wk );
		break;
	case SHOP_SEQ_SALE_RET:			// 「売る」終了 -> フェードイン
		wk->seq = ShopSaleRetSeq( fsys );
		break;
*/

	case SHOP_SEQ_SALE_MENU_RET:	// フェードイン -> メニューへ
		wk->seq = ShopSaleMenuRetSeq( fsys, wk );
		break;

	case SHOP_SEQ_EXIT:
		ShopExitSeq( fsys, wk );
		wk->seq = SHOP_SEQ_END;
		break;

	case SHOP_SEQ_END:
		return ShopEndSeq( fsys, wk );
	}


	if( wk->seq >= SHOP_SEQ_BUY_SELECT && wk->seq <= SHOP_SEQ_BUYOMAKE_WAIT ){
		CLACT_AnmFrameChg( wk->cwp[0], FX32_ONE );
		CLACT_AnmFrameChg( wk->cwp[1], FX32_ONE );
		CLACT_Draw( wk->fcat.cas );
	}


	return FALSE;
}


//--------------------------------------------------------------------------------------------
/**
 * 初期化
 */
//--------------------------------------------------------------------------------------------
static void ShopInitSeq( SHOP_WORK * wk )
{
	ShopMsgCreate( wk );
	ShopMenuSet( wk );
}

static void ShopMsgCreate( SHOP_WORK * wk )
{
	wk->mman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_shop_dat, HEAPID_WORLD );
	wk->wset = WORDSET_Create( HEAPID_WORLD );
}

static void ShopMenuSet( SHOP_WORK * wk )
{
	BMPMENU_HEADER	hed;
	u8	max;

	if( wk->shop_type == SHOP_TYPE_ITEM ){
		max = 3;
		wk->md = BMP_MENULIST_Create( max, HEAPID_WORLD );
		BMP_MENULIST_AddArchiveString( wk->md, wk->mman, mes_shop_04_01, SHOP_SEQ_BUY_INIT );
		BMP_MENULIST_AddArchiveString( wk->md, wk->mman, mes_shop_04_02, SHOP_SEQ_SALE_INIT );
		BMP_MENULIST_AddArchiveString( wk->md, wk->mman, mes_shop_04_03, BMPMENU_CANCEL );

		GF_BGL_BmpWinAdd(
			wk->bgl, &wk->win[WIN_IDX_NENU], FLD_MBGFRM_FONT,
			WIN_SHOP_MENU_PX, WIN_SHOP_MENU_PY, WIN_SHOP_MENU_SX,
			WIN_SHOP_MENU_SY, WIN_SHOP_MENU_PAL, WIN_SHOP_MENU_CGX );
	}else{
		max = 2;
		wk->md = BMP_MENULIST_Create( max, HEAPID_WORLD );
		BMP_MENULIST_AddArchiveString( wk->md, wk->mman, mes_shop_04_01, SHOP_SEQ_BUY_INIT );
		BMP_MENULIST_AddArchiveString( wk->md, wk->mman, mes_shop_04_03, BMPMENU_CANCEL );

		GF_BGL_BmpWinAdd(
			wk->bgl, &wk->win[WIN_IDX_NENU], FLD_MBGFRM_FONT,
			WIN_SHOP_MENU_PX, WIN_SHOP_MENU_PY, WIN_SHOP_MENU_SX,
			WIN_SHOP_MENU_SY_GS, WIN_SHOP_MENU_PAL, WIN_SHOP_MENU_CGX );
	}

	hed.menu     = wk->md;
	hed.win      = &wk->win[WIN_IDX_NENU];
	hed.font     = FONT_SYSTEM;
	hed.x_max    = 1;
	hed.y_max    = max;
	hed.line_spc = 0;
	hed.c_disp_f = 0;
	hed.loop_f   = 0;

	MenuWinGraphicSet(
		wk->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_WORLD );
	BmpMenuWinWrite( &wk->win[WIN_IDX_NENU], WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	wk->mw = BmpMenuAddEx( &hed, 8, 0, 0, HEAPID_WORLD, PAD_BUTTON_CANCEL );
}


//--------------------------------------------------------------------------------------------
/**
 * メニュー選択
 */
//--------------------------------------------------------------------------------------------
static u8 ShopMenuSelect( SHOP_WORK * wk )
{
	u32	ret = BmpMenuMain( wk->mw );

	switch( ret ){
	case BMPMENU_NULL:
		break;
	case BMPMENU_CANCEL:
		ShopMenuExit( wk );
		return SHOP_SEQ_EXIT;
	default:
		return (u8)ret;
	}
	return SHOP_SEQ_MENU;
}


static void ShopMenuExit( SHOP_WORK * wk )
{
	BmpMenuWinClear( &wk->win[WIN_IDX_NENU], WINDOW_TRANS_OFF );
	GF_BGL_BmpWinOff( &wk->win[WIN_IDX_NENU] );

	BmpMenuExit( wk->mw, NULL );
	BMP_MENULIST_Delete( wk->md );

	GF_BGL_BmpWinDel( &wk->win[WIN_IDX_NENU] );
}



//--------------------------------------------------------------------------------------------
/**
 * 終了
 */
//--------------------------------------------------------------------------------------------
static u8 ShopEndSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk )
{
	if( FldTalkMsgEndCheck( wk->midx ) == 0 ){
		return FALSE;
	}

	if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) ){
		void * buf;

		BmpTalkWinClear( &wk->win[WIN_IDX_FLDTALK], WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->win[WIN_IDX_FLDTALK] );

		MSGMAN_Delete( wk->mman );
		WORDSET_Delete( wk->wset );

		STRBUF_Delete( wk->msgb );

		if( wk->shop_type == SHOP_TYPE_ITEM ){
			if( ZoneData_GetPlaceNameID( fsys->location->zone_id ) != MAPNAME_C7DEPARTMENT &&
				fsys->location->zone_id != ZONE_ID_C04R0501 &&
				fsys->location->zone_id != ZONE_ID_T05R0201 ){

				if( wk->fnote_buy_cnt != 0 && wk->fnote_sale_cnt != 0 ){
					buf = FNOTE_ActionShopTradeDataMake( HEAPID_WORLD );
					FNOTE_DataSave( wk->fnote, buf, FNOTE_TYPE_ACTION );
				}else if( wk->fnote_buy_cnt > 1 ){
					buf = FNOTE_ActionShopBuy2DataMake( HEAPID_WORLD );
					FNOTE_DataSave( wk->fnote, buf, FNOTE_TYPE_ACTION );
				}else if( wk->fnote_sale_cnt > 1 ){
					buf = FNOTE_ActionShopSale2DataMake( HEAPID_WORLD );
					FNOTE_DataSave( wk->fnote, buf, FNOTE_TYPE_ACTION );
				}else if( wk->fnote_buy_cnt != 0 ){
					buf = FNOTE_ActionShopBuyDataMake( HEAPID_WORLD );
					FNOTE_DataSave( wk->fnote, buf, FNOTE_TYPE_ACTION );
				}else if( wk->fnote_sale_cnt != 0 ){
					buf = FNOTE_ActionShopSaleDataMake( HEAPID_WORLD );
					FNOTE_DataSave( wk->fnote, buf, FNOTE_TYPE_ACTION );
				}
			}
		}

		sys_FreeMemoryEz( wk->item );
		sys_FreeMemoryEz( wk );

#ifdef PM_DEBUG
		DEBUG_VIEW_HOOK(FALSE);			//デバッグ情報表示許可
#endif
		return TRUE;
	}
	return FALSE;
}



//=============================================================================================
//	買う
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 初期化
 */
//--------------------------------------------------------------------------------------------
static void ShopBuyInitSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk )
{
//	BmpTalkWinClear( &wk->win[WIN_IDX_FLDTALK], WINDOW_TRANS_ON );
	GF_BGL_ScrFill(
		wk->bgl, FLD_MBGFRM_FONT, 0, 
		FLD_MSG_WIN_PX-2,FLD_MSG_WIN_PY-1,FLD_MSG_WIN_SX+5,FLD_MSG_WIN_SY+2, 0 );
//	GF_BGL_LoadScreenReq( win->ini, frm );

	ShopMenuExit( wk );
	ShopBuyWinAdd( wk );
//	ShopBuyGraphicSet( wk );

	wk->camera = GFC_AllocCamera( HEAPID_WORLD );
	GFC_CopyCamera( fsys->camera_ptr, wk->camera );
	GFC_AttachCamera( wk->camera );
	wk->cm_cnt = 0;
}

static void ShopBuyWinAdd( SHOP_WORK * wk )
{
	u32	i;

	for( i=0; i<WIN_IDX_MAX; i++ ){
		if( wk->shop_type != SHOP_TYPE_ITEM && i == WIN_IDX_INFO ){
			GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[i], &ShopBuyGoodsInfoWin );
		}else{
			GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[i], &ShopBuyBmpWin[i] );
		}
	}
}

static void ShopBuyWinDel( SHOP_WORK * wk )
{
	u32	i;

	BmpMenuWinClear( &wk->win[WIN_IDX_GOLD], WINDOW_TRANS_OFF );

	for( i=0; i<WIN_IDX_MAX; i++ ){
		GF_BGL_BmpWinOff( &wk->win[i] );
		GF_BGL_BmpWinDel( &wk->win[i] );
	}
}

static void ShopBuyGraphicSet( SHOP_WORK * wk )
{
	ArcUtil_BgCharSet(
		ARC_SHOP_GRA, NARC_shop_gra_shop_bg_NCGR,
		wk->bgl, SHOP_FRM_BG, 0, 0, 0, HEAPID_WORLD );
	if( wk->shop_type == SHOP_TYPE_ITEM ){
		ArcUtil_ScrnSet(
			ARC_SHOP_GRA, NARC_shop_gra_shop_bg1_NSCR,
			wk->bgl, SHOP_FRM_BG, 0, 0, 0, HEAPID_WORLD );
	}else{
		ArcUtil_ScrnSet(
			ARC_SHOP_GRA, NARC_shop_gra_shop_bg2_NSCR,
			wk->bgl, SHOP_FRM_BG, 0, 0, 0, HEAPID_WORLD );
	}
	ArcUtil_PalSet(
		ARC_SHOP_GRA, NARC_shop_gra_shop_bg_NCLR, PALTYPE_MAIN_BG, 0, 32, HEAPID_WORLD );

	// メニューウィンドウセット
	MenuWinGraphicSet(
		wk->bgl, SHOP_FRM_WINDOW, SHOP_MENU_WIN_CGX, MENU_WIN_PAL, 0, HEAPID_WORLD );
	// 会話ウィンドウセット
	TalkWinGraphicSet(
		wk->bgl, SHOP_FRM_WINDOW, SHOP_TALK_WIN_CGX,
		TALK_WIN_PAL, CONFIG_GetWindowType(wk->cfg), HEAPID_WORLD );
}

static void ShopBgPriorityChg( SHOP_WORK * wk )
{
	wk->disp = GF_Disp_MainVisibleGet();

	wk->pri[0] = GF_BGL_PriorityGet( wk->bgl, SHOP_FRM_3D );
	wk->pri[1] = GF_BGL_PriorityGet( wk->bgl, SHOP_FRM_BG );
	wk->pri[2] = GF_BGL_PriorityGet( wk->bgl, SHOP_FRM_LIST );
	wk->pri[3] = GF_BGL_PriorityGet( wk->bgl, SHOP_FRM_WINDOW );

	GF_BGL_PrioritySet( SHOP_FRM_3D, 3 );
	GF_BGL_PrioritySet( SHOP_FRM_BG, 2 );
	GF_BGL_PrioritySet( SHOP_FRM_LIST, 1 );
	GF_BGL_PrioritySet( SHOP_FRM_WINDOW, 0 );

	GF_Disp_GX_VisibleControl( SHOP_FRM_3D, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( SHOP_FRM_BG, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( SHOP_FRM_LIST, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( SHOP_FRM_WINDOW, VISIBLE_ON );
}

static void ShopBgPriorityReset( SHOP_WORK * wk )
{
	GF_BGL_PrioritySet( SHOP_FRM_3D, wk->pri[0] );
	GF_BGL_PrioritySet( SHOP_FRM_BG, wk->pri[1] );
	GF_BGL_PrioritySet( SHOP_FRM_LIST, wk->pri[2] );
	GF_BGL_PrioritySet( SHOP_FRM_WINDOW, wk->pri[3] );

	GF_Disp_GX_VisibleControlDirect( wk->disp );
}

//--------------------------------------------------------------------------------------------
/**
 * 開始スクロール
 */
//--------------------------------------------------------------------------------------------
static u8 ShopBuyScrollSeq( SHOP_WORK * wk )
{
	if( wk->cm_cnt != wk->cm_max ){
		VecFx32 move = {8*FX32_ONE,0,0};
		GFC_ShiftCamera( &move, wk->camera );
		wk->cm_cnt++;
		return SHOP_SEQ_BUY_SCROLL;
	}
/*
		if( sys.trg & PAD_KEY_UP ){
			move.z = FX32_ONE;
			GFC_ShiftCamera( &move, wk->camera );
		}else if( sys.trg & PAD_KEY_DOWN ){
			move.z = FX32_ONE;
			GFC_ShiftCamera( &move, wk->camera );
		}else if( sys.trg & PAD_KEY_LEFT ){
			move.x = FX32_ONE;
			GFC_ShiftCamera( &move, wk->camera );
		}else if( sys.trg & PAD_KEY_RIGHT ){
			move.x = FX32_ONE;
			GFC_ShiftCamera( &move, wk->camera );
		}
*/

	wk->cm_cnt = 0;
	ShopBuyActSet( wk );
	ShopBuyGraphicSet( wk );
	ShopBgPriorityChg( wk );
	ShopBuyItemListMake( wk );
	ShopBuyGoldWinPut( wk, 0 );
	return SHOP_SEQ_BUY_SELECT;
}

// アイテムリストデータ（BMPリスト）
static const BMPLIST_HEADER ShopItemList = {
	NULL, CB_ItemListMove, CB_ItemListWrite, NULL,
	0, 7, 0,
	0, 0,			// 項目X, カーソルX
	0,				// 表示Y
	FBMP_COL_BLACK, FBMP_COL_NULL, FBMP_COL_BLK_SDW,
	0, 16,						// 文字間隔Ｙ
	BMPLIST_NO_SKIP, FONT_SYSTEM, 1,
	NULL,
};

static u32 ShopByeGetItemNameID( SHOP_WORK * wk, u16 item )
{
	if( wk->shop_type == SHOP_TYPE_GOODS ){
		return (UGGoods001+item-1);
	}else if( wk->shop_type == SHOP_TYPE_SEAL ){
		return (u32)Seal_NameGet( (u8)item );
	}
	return (u32)item;
}

static void ShopBuyItemListMake( SHOP_WORK * wk )
{
	MSGDATA_MANAGER * man;
	STRBUF * buf;
	BMPLIST_HEADER	lh;
	u32	i;

	if( wk->shop_type == SHOP_TYPE_ITEM ){
		man = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_itemname_dat, HEAPID_WORLD );
	}else if( wk->shop_type == SHOP_TYPE_GOODS ){
		man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,NARC_msg_undergroundgoods_dat,HEAPID_WORLD);
	}else{
		man = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, CB_SEAL_MSG_ARC, HEAPID_WORLD );
	}

	wk->ld = BMP_MENULIST_Create( wk->max+1, HEAPID_WORLD );
	for( i=0; i<wk->max; i++ ){
		buf = MSGMAN_AllocString( man, ShopByeGetItemNameID( wk, wk->item[i] ) );
		BMP_MENULIST_AddString( wk->ld, buf, wk->item[i] );
		STRBUF_Delete( buf );
	}
	BMP_MENULIST_AddArchiveString( wk->ld, wk->mman, mes_shop_02_06, BMPLIST_CANCEL );

	MSGMAN_Delete( man );

	lh = ShopItemList;
	lh.list  = wk->ld;
	lh.win   = &wk->win[WIN_IDX_LIST];
	lh.count = wk->max+1;
	lh.work  = (void *)wk;
	wk->lw = BmpListSet( &lh, 0, 0, HEAPID_WORLD );
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムリストコールバック関数（カーソル移動ごと）
 *
 * @param	work	BMPリストで設定したワーク
 * @param	param	BMPリストのパラメータ
 * @param	mode	初期化時 = 1
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CB_ItemListMove( BMPLIST_WORK * work, u32 param, u8 mode )
{
	SHOP_WORK * wk = (SHOP_WORK *)BmpListParamGet( work, BMPLIST_ID_WORK );

	if( mode != 1 ){
		Snd_SePlay( FD_SHOP_SE_CURSOR_MOVE );
	}
	
	GF_BGL_BmpWinDataFill( &wk->win[WIN_IDX_INFO], 0 );

	if( param != BMPLIST_CANCEL ){
		STRBUF * buf;

		if( wk->shop_type == SHOP_TYPE_ITEM ){
			buf = STRBUF_Create( BUFLEN_ITEM_INFO, HEAPID_WORLD );
			ItemInfoGet( buf, (u16)param, HEAPID_WORLD );
		}else if( wk->shop_type == SHOP_TYPE_GOODS ){
			MSGDATA_MANAGER * man;
			man = MSGMAN_Create(
					MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_undergroundgoods_dat, HEAPID_WORLD );
			buf = MSGMAN_AllocString( man, UGGoods_e001+param-1 );
			MSGMAN_Delete( man );
		}else{
			MSGDATA_MANAGER * man;
			man = MSGMAN_Create(
					MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_seal_comment_dat, HEAPID_WORLD );
			buf = MSGMAN_AllocString( man, Seal_CommentGet((u8)param) );
			MSGMAN_Delete( man );
		}
		GF_STR_PrintColor(
			&wk->win[WIN_IDX_INFO], FONT_SYSTEM, buf, 0, 0, MSG_NO_PUT, SHOPCOL_N_WHITE, NULL );
		STRBUF_Delete( buf );

		ShopBuyItemIconChg( wk, (u16)param );
	}else{
		ShopBuyItemIconChg( wk, ITEM_RETURN_ID );
	}
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_IDX_INFO] );

	{
		u32	max;
		u16	scr, cur;

		BmpListPosGet( work, &scr, &cur );
		if( scr == 0 ){
			CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_U], 0 );
		}else{
			CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_U], 1 );
		}

		max = BmpListParamGet( work, BMPLIST_ID_COUNT );
		if( max > 7 && max > scr + 7 ){
			CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_D], 1 );
		}else{
			CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_D], 0 );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムリストコールバック関数（一列表示ごと）
 *
 * @param	work	BMPリストで設定したワーク
 * @param	index	BMPリストが使用しているウィンドウインデックス
 * @param	param	BMPリストのパラメータ
 * @param	y		Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	LIST_PRICE_BUFLEN	( 12 )
#define	LIST_PRICE_EX		( WIN_SHOP_LIST_SX * 8 )

static void CB_ItemListWrite( BMPLIST_WORK * work, u32 param, u8 y )
{
	SHOP_WORK * wk = (SHOP_WORK *)BmpListParamGet( work, BMPLIST_ID_WORK );

	if( param != BMPLIST_CANCEL ){
		STRBUF * expb;
		STRBUF * strb;
		u32	price;
		u32	siz;

		price = ShopBuyItemPriceGet( wk, (u16)param );
		expb  = STRBUF_Create( LIST_PRICE_BUFLEN, HEAPID_WORLD );
		strb  = MSGMAN_AllocString( wk->mman, mes_shop_02_07 );
		WORDSET_RegisterNumber(
			wk->wset, 0, price, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, expb, strb );
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, expb, 0 );
		GF_STR_PrintColor(
			&wk->win[WIN_IDX_LIST], FONT_SYSTEM, expb,
			LIST_PRICE_EX-siz, y, MSG_NO_PUT, SHOPCOL_N_BLACK, NULL );
		STRBUF_Delete( strb );
		STRBUF_Delete( expb );
	}
}

#define	GOLD_BUFLEN		( 16 )
#define	GOLD_EX			( WIN_SHOP_GOLD_SX * 8 )

static void ShopBuyGoldWinPut( SHOP_WORK * wk, u8 flg )
{
	STRBUF * expb;
	STRBUF * strb;
	u32	gold;
	u32	siz;

	if( flg == 0 ){
		GF_BGL_BmpWinDataFill( &wk->win[WIN_IDX_GOLD], 15 );
		BmpMenuWinWrite(
			&wk->win[WIN_IDX_GOLD], WINDOW_TRANS_OFF, SHOP_MENU_WIN_CGX, MENU_WIN_PAL );
		strb = MSGMAN_AllocString( wk->mman, mes_shop_05_01 );
		GF_STR_PrintSimple( &wk->win[WIN_IDX_GOLD], FONT_SYSTEM, strb, 0, 0, MSG_NO_PUT, NULL );
		STRBUF_Delete( strb );
	}else{
		GF_BGL_BmpWinFill( &wk->win[WIN_IDX_GOLD], 15, 0, 16, GOLD_EX, 16 );
	}

	expb = STRBUF_Create( GOLD_BUFLEN, HEAPID_WORLD );
	strb = MSGMAN_AllocString( wk->mman, mes_shop_05_02 );
	gold = MyStatus_GetGold( wk->my );
	WORDSET_RegisterNumber(
		wk->wset, 0, gold, 6, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, expb, strb );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, expb, 0 );
	GF_STR_PrintSimple(
		&wk->win[WIN_IDX_GOLD], FONT_SYSTEM, expb, GOLD_EX-siz, 16, MSG_NO_PUT, NULL );
	STRBUF_Delete( strb );
	STRBUF_Delete( expb );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_IDX_GOLD] );
}


//--------------------------------------------------------------------------------------------
/**
 * アイテム選択
 */
//--------------------------------------------------------------------------------------------
static u8 ShopBuySelectSeq( SHOP_WORK * wk )
{
	u32	ret;
	u16	cur1, cur2;

	BmpListPosGet( wk->lw, NULL, &cur1 );
	ret = BmpListMain( wk->lw );
	BmpListPosGet( wk->lw, NULL, &cur2 );

	if( cur1 != cur2 ){
		CATS_ObjectPosSet( wk->cwp[2], CURSOR_ACT_PX, CURSOR_ACT_PY + cur2 * 16 );
	}

	switch( ret ){
	case BMPLIST_NULL:
		break;
	case BMPLIST_CANCEL:
		BmpListExit( wk->lw, NULL, NULL );
		BMP_MENULIST_Delete( wk->ld );
		ShopBuyWinDel( wk );
		ShopBgPriorityReset( wk );
		GF_BGL_ScrClear( wk->bgl, SHOP_FRM_BG );
		Snd_SePlay( FD_SHOP_SE_CANCEL );
		return SHOP_SEQ_BUY_END;

	default:
		{
			STRBUF * str;
			u32	gold;

			wk->scr_draw[0] = (u16)CLACT_GetDrawFlag( wk->cwp[SHOP_CLA_ARROW_U] );
			wk->scr_draw[1] = (u16)CLACT_GetDrawFlag( wk->cwp[SHOP_CLA_ARROW_D] );

			CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_U], 0 );
			CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_D], 0 );

			ShopBuyCursorPalChg( wk, 1 );

			GF_BGL_BmpWinDataFill( &wk->win[WIN_IDX_TALK], 15 );
			BmpTalkWinWrite(
				&wk->win[WIN_IDX_TALK], WINDOW_TRANS_ON, SHOP_TALK_WIN_CGX, TALK_WIN_PAL );

			wk->sel_item  = (u16)ret;
			wk->sel_num   = 1;
			wk->sel_price = ShopBuyItemPriceGet( wk, wk->sel_item );

			gold = MyStatus_GetGold( wk->my );

			if( gold < wk->sel_price ){
				str = MSGMAN_AllocString( wk->mman, mes_shop_02_01 );
				WORDSET_ExpandStr( wk->wset, wk->msgb, str );
				STRBUF_Delete( str );
				wk->midx = FieldTalkMsgStart( &wk->win[WIN_IDX_TALK], wk->msgb, wk->cfg, 1 );
				return SHOP_SEQ_BUYCMP_WAIT;
			}

			if( wk->shop_type == SHOP_TYPE_GOODS ){
				return ShopBuyCmpCheck( wk );
			}

			wk->sel_max = gold / wk->sel_price;
			if( wk->sel_max > 99 ){ wk->sel_max = 99; }

//			WORDSET_RegisterItemName( wk->wset, 0, wk->sel_item );
			ShopBuyItemNameWordSet( wk, wk->sel_item, 0 );

			str = MSGMAN_AllocString( wk->mman, mes_shop_02_02 );
			WORDSET_ExpandStr( wk->wset, wk->msgb, str );
			STRBUF_Delete( str );
			wk->midx = FieldTalkMsgStart( &wk->win[WIN_IDX_TALK], wk->msgb, wk->cfg, 1 );

			ShopBuyScrCurPosChg( wk, 1 );

			Snd_SePlay( FD_SHOP_SE_DECIDE );
			return SHOP_SEQ_BUYSEL_WAIT;
		}
	}
	return SHOP_SEQ_BUY_SELECT;
}

static u8 ShopBuySelWaitSeq( SHOP_WORK * wk )
{
	if( FldTalkMsgEndCheck( wk->midx ) == 0 ){
		return SHOP_SEQ_BUYSEL_WAIT;
	}
	MyItemWinPut( wk );
	NumSelWinPut( wk, 0 );
	CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_U], 1 );
	CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_D], 1 );
	return SHOP_SEQ_BUYNUM_SEL;
}

#define	MYITEM_BUFLEN	( 12*2 )

static void MyItemWinPut( SHOP_WORK * wk )
{
	STRBUF * expb;
	STRBUF * strb;
	u16	num;

	if( wk->shop_type == SHOP_TYPE_ITEM ){
		num = MyItem_GetItemNum( wk->myitem, wk->sel_item, HEAPID_WORLD );
	}else if( wk->shop_type == SHOP_TYPE_SEAL ){
//		num = CB_SaveData_ItemNumGet( CB_SaveData_ItemDataGet(wk->myitem), wk->sel_item );
//		OS_Printf( "SEAL : id = %d, num = %d\n", wk->sel_item, num );
		num = CB_Tool_SealTotalNumGet( wk->myitem, wk->sel_item );
		OS_Printf( "SEAL : id = %d, num = %d\n", wk->sel_item, num );
	}else{
		num = 0;
	}

	GF_BGL_BmpWinDataFill( &wk->win[WIN_IDX_MINE], 15 );
	BmpMenuWinWrite(
		&wk->win[WIN_IDX_MINE], WINDOW_TRANS_OFF, SHOP_MENU_WIN_CGX, MENU_WIN_PAL );

	expb = STRBUF_Create( MYITEM_BUFLEN, HEAPID_WORLD );
	strb = MSGMAN_AllocString( wk->mman, mes_shop_06_01 );
	WORDSET_RegisterNumber(
		wk->wset, 0, num, 3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, expb, strb );
	GF_STR_PrintSimple( &wk->win[WIN_IDX_MINE], FONT_SYSTEM, expb, 0, 0, MSG_NO_PUT, NULL );
	STRBUF_Delete( strb );
	STRBUF_Delete( expb );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_IDX_MINE] );
}


static u8 ShopBuyNumSelSeq( SHOP_WORK * wk )
{
	if( NumSelectCheck( &wk->sel_num, wk->sel_max ) != APP_NUMSEL_NONE ){
		Snd_SePlay( FD_SHOP_SE_CURSOR_MOVE );
		NumSelWinPut( wk, 1 );
		return SHOP_SEQ_BUYNUM_SEL;
	}

	if( sys.trg & PAD_BUTTON_DECIDE ){
//		STRBUF * str;
//		BOOL	check;

		CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_U], 0 );
		CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_D], 0 );
		BmpMenuWinClear( &wk->win[WIN_IDX_MINE], WINDOW_TRANS_OFF );
		BmpMenuWinClear( &wk->win[WIN_IDX_NUM],  WINDOW_TRANS_OFF );
		GF_BGL_BmpWinDataFill( &wk->win[WIN_IDX_TALK], 15 );
		Snd_SePlay( FD_SHOP_SE_DECIDE );

		return ShopBuyCmpCheck( wk );

/*
		if( wk->shop_type == SHOP_TYPE_ITEM ){
			check = MyItem_AddCheck( wk->myitem, wk->sel_item, wk->sel_num, HEAPID_WORLD );
		}else if( wk->shop_type == SHOP_TYPE_GOODS ){
			if( UnderGroundGetNumGoodsPCItem( wk->myitem ) == UG_ITEM_PC_NUM_MAX ){
				check = FALSE;
			}else{
				check = TRUE;
			}
		}else{
// チェックまち
			check = TRUE;
		}

		if( check == FALSE ){
			str = MSGMAN_AllocString( wk->mman, mes_shop_02_05 );
			WORDSET_ExpandStr( wk->wset, wk->msgb, str );
			STRBUF_Delete( str );
			wk->midx = FieldTalkMsgStart( &wk->win[WIN_IDX_TALK], wk->msgb, wk->cfg, 1 );
			return SHOP_SEQ_BUYCMP_WAIT;
		}

		WORDSET_RegisterItemName( wk->wset, 0, wk->sel_item );
		WORDSET_RegisterNumber(
			wk->wset, 1, wk->sel_num, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_RegisterNumber(
			wk->wset, 2, wk->sel_price*wk->sel_num, 6,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		str = MSGMAN_AllocString( wk->mman, mes_shop_02_03 );
		WORDSET_ExpandStr( wk->wset, wk->msgb, str );
		STRBUF_Delete( str );
		wk->midx = FieldTalkMsgStart( &wk->win[WIN_IDX_TALK], wk->msgb, wk->cfg, 1 );
		return SHOP_SEQ_BUYNUM_WAIT;
*/
	}

	if( sys.trg & PAD_BUTTON_CANCEL ){
		BmpMenuWinClear( &wk->win[WIN_IDX_MINE], WINDOW_TRANS_OFF );
		BmpMenuWinClear( &wk->win[WIN_IDX_NUM],  WINDOW_TRANS_OFF );
		BmpTalkWinClear( &wk->win[WIN_IDX_TALK], WINDOW_TRANS_ON );

		ShopBuyScrCurPosChg( wk, 0 );
		CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_U], wk->scr_draw[0] );
		CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_D], wk->scr_draw[1] );
		ShopBuyCursorPalChg( wk, 0 );

		Snd_SePlay( FD_SHOP_SE_CANCEL );
		return SHOP_SEQ_BUY_SELECT;
	}
	return SHOP_SEQ_BUYNUM_SEL;
}

static u8 ShopBuyCmpCheck( SHOP_WORK * wk )
{
	STRBUF * str;
	BOOL	check;

	if( wk->shop_type == SHOP_TYPE_ITEM ){
		check = MyItem_AddCheck( wk->myitem, wk->sel_item, wk->sel_num, HEAPID_WORLD );
	}else if( wk->shop_type == SHOP_TYPE_GOODS ){
		if( UnderGroundGetNumGoodsPCItem( wk->myitem ) == UG_ITEM_PC_NUM_MAX ){
			check = FALSE;
		}else{
			check = TRUE;
		}
	}else{
		check = CB_SaveData_IsAddIt( wk->myitem, wk->sel_item, wk->sel_num );
	}

	if( check == FALSE ){
		wk->sel_num = 0;
		if( wk->shop_type == SHOP_TYPE_ITEM ){
			str = MSGMAN_AllocString( wk->mman, mes_shop_02_05 );
		}else if( wk->shop_type == SHOP_TYPE_GOODS ){
			str = MSGMAN_AllocString( wk->mman, mes_shop_03_02 );
		}else{
			str = MSGMAN_AllocString( wk->mman, mes_shop_03_04 );
		}
		WORDSET_ExpandStr( wk->wset, wk->msgb, str );
		STRBUF_Delete( str );
		wk->midx = FieldTalkMsgStart( &wk->win[WIN_IDX_TALK], wk->msgb, wk->cfg, 1 );
		return SHOP_SEQ_BUYCMP_WAIT;
	}

//	WORDSET_RegisterItemName( wk->wset, 0, wk->sel_item );
	ShopBuyItemNameWordSet( wk, wk->sel_item, 0 );
	WORDSET_RegisterNumber(
		wk->wset, 1, wk->sel_num, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber(
		wk->wset, 2, wk->sel_price*wk->sel_num, 6,
		NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	str = MSGMAN_AllocString( wk->mman, mes_shop_02_03 );
	WORDSET_ExpandStr( wk->wset, wk->msgb, str );
	STRBUF_Delete( str );
	wk->midx = FieldTalkMsgStart( &wk->win[WIN_IDX_TALK], wk->msgb, wk->cfg, 1 );
	return SHOP_SEQ_BUYNUM_WAIT;
}




#define	NUMSEL_BUFLEN	( 24 )
#define	NUMSEL_EX		( WIN_SHOP_NUM_SX * 8 )

static void NumSelWinPut( SHOP_WORK * wk, u8 flg )
{
	STRBUF * expb;
	STRBUF * strb;
	u32	siz;

	GF_BGL_BmpWinDataFill( &wk->win[WIN_IDX_NUM], 15 );

	if( flg == 0 ){
		BmpMenuWinWrite(
			&wk->win[WIN_IDX_NUM], WINDOW_TRANS_OFF, SHOP_MENU_WIN_CGX, MENU_WIN_PAL );
	}

	expb = STRBUF_Create( NUMSEL_BUFLEN, HEAPID_WORLD );
	strb = MSGMAN_AllocString( wk->mman, mes_shop_07_01 );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->sel_num, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, expb, strb );
	GF_STR_PrintSimple(
		&wk->win[WIN_IDX_NUM], FONT_SYSTEM, expb, 0, 8, MSG_NO_PUT, NULL );
	STRBUF_Delete( strb );

	strb = MSGMAN_AllocString( wk->mman, mes_shop_07_02 );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->sel_price*wk->sel_num, 6,
		NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, expb, strb );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, expb, 0 );
	GF_STR_PrintSimple(
		&wk->win[WIN_IDX_NUM], FONT_SYSTEM, expb, NUMSEL_EX-siz, 8, MSG_NO_PUT, NULL );
	STRBUF_Delete( strb );
	STRBUF_Delete( expb );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_IDX_NUM] );
}





static u8 ShopBuyNumWaitSeq( SHOP_WORK * wk )
{
	if( FldTalkMsgEndCheck( wk->midx ) == 0 ){
		return SHOP_SEQ_BUYNUM_WAIT;
	}
	wk->mw = BmpYesNoSelectInit(
				wk->bgl, &ShopBuyYesNoBmpWin, SHOP_MENU_WIN_CGX, MENU_WIN_PAL, HEAPID_WORLD );
	return SHOP_SEQ_BUY_YESNO;
}

static u8 ShopBuyYesNoSeq( SHOP_WORK * wk )
{
	switch( BmpYesNoSelectMain( wk->mw, HEAPID_WORLD ) ){
	case 0:
		{
			STRBUF * str;

			ShopBuyItemNameWordSet( wk, wk->sel_item, 0 );
			if( wk->shop_type == SHOP_TYPE_ITEM ){
				str = MSGMAN_AllocString( wk->mman, mes_shop_02_04 );
				WORDSET_RegisterItemPocketWithIcon(
					wk->wset, 1, ItemParamGet( wk->sel_item, ITEM_PRM_POCKET, HEAPID_WORLD ) );
			}else if( wk->shop_type == SHOP_TYPE_GOODS ){
				str = MSGMAN_AllocString( wk->mman, mes_shop_03_01 );
			}else{
				str = MSGMAN_AllocString( wk->mman, mes_shop_03_03 );
			}
			WORDSET_ExpandStr( wk->wset, wk->msgb, str );
			STRBUF_Delete( str );
		}
		GF_BGL_BmpWinDataFill( &wk->win[WIN_IDX_TALK], 15 );
		wk->midx = FieldTalkMsgStart( &wk->win[WIN_IDX_TALK], wk->msgb, wk->cfg, 1 );
		Snd_SePlay( SEQ_SE_DP_REGI );
		return SHOP_SEQ_BUY_CMP;

	case BMPMENU_CANCEL:
		BmpTalkWinClear( &wk->win[WIN_IDX_TALK], WINDOW_TRANS_ON );
		ShopBuyScrCurPosChg( wk, 0 );
		CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_U], wk->scr_draw[0] );
		CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_D], wk->scr_draw[1] );
		ShopBuyCursorPalChg( wk, 0 );
		return SHOP_SEQ_BUY_SELECT;
	}
	return SHOP_SEQ_BUY_YESNO;
}


static u8 ShopBuyCmpSeq( SHOP_WORK * wk )
{
	if( FldTalkMsgEndCheck( wk->midx ) == 0 ){
		return SHOP_SEQ_BUY_CMP;
	}

	if( wk->shop_type == SHOP_TYPE_ITEM ){
		MyItem_AddItem( wk->myitem, wk->sel_item, wk->sel_num, HEAPID_WORLD );
	}else if( wk->shop_type == SHOP_TYPE_GOODS ){
		UnderGroundAddGoodsPCItem( wk->myitem, wk->sel_item );
	}else{
		CB_SaveData_ItemNumAddCheck( wk->myitem, wk->sel_item, wk->sel_num );
	}

	Mystatus_SubGold( wk->my, wk->sel_price*wk->sel_num );
	RECORD_Add( wk->rec, RECID_SHOPPING_MONEY, wk->sel_price*wk->sel_num );
	ShopBuyGoldWinPut( wk, 1 );
	if( wk->sel_num > 1 ){
		wk->fnote_buy_cnt = 2;
	}else{
		if( wk->fnote_buy_cnt != 0xff ){
			wk->fnote_buy_cnt++;
		}
	}
	return SHOP_SEQ_BUYCMP_WAIT;
}










static u8 ShopBuyCmpWaitSeq( SHOP_WORK * wk )
{
	if( FldTalkMsgEndCheck( wk->midx ) == 0 ){
		return SHOP_SEQ_BUYCMP_WAIT;
	}
	if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) ){

		if( wk->dp_flg == TRUE ){
			SysWork_RegularCountPlus( wk->evwk );
		}

		if( wk->shop_type == SHOP_TYPE_ITEM &&
			wk->sel_item == ITEM_MONSUTAABOORU && wk->sel_num >= 10 ){
			if( MyItem_AddItem( wk->myitem, ITEM_PUREMIABOORU, 1, HEAPID_WORLD ) == TRUE ){
				STRBUF * str = MSGMAN_AllocString( wk->mman, mes_shop_02_08 );
				WORDSET_ExpandStr( wk->wset, wk->msgb, str );
				STRBUF_Delete( str );
				GF_BGL_BmpWinDataFill( &wk->win[WIN_IDX_TALK], 15 );
				wk->midx = FieldTalkMsgStart( &wk->win[WIN_IDX_TALK], wk->msgb, wk->cfg, 1 );
				return SHOP_SEQ_BUYOMAKE_WAIT;
			}
		}

		BmpTalkWinClear( &wk->win[WIN_IDX_TALK], WINDOW_TRANS_ON );

		ShopBuyScrCurPosChg( wk, 0 );
		CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_U], wk->scr_draw[0] );
		CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_D], wk->scr_draw[1] );
		ShopBuyCursorPalChg( wk, 0 );

		return SHOP_SEQ_BUY_SELECT;
	}
	return SHOP_SEQ_BUYCMP_WAIT;
}


static u8 ShopBuyOmakeWait( SHOP_WORK * wk )
{
	if( FldTalkMsgEndCheck( wk->midx ) == 0 ){
		return SHOP_SEQ_BUYOMAKE_WAIT;
	}
	if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) ){
		BmpTalkWinClear( &wk->win[WIN_IDX_TALK], WINDOW_TRANS_ON );

		ShopBuyScrCurPosChg( wk, 0 );
		CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_U], wk->scr_draw[0] );
		CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ARROW_D], wk->scr_draw[1] );
		ShopBuyCursorPalChg( wk, 0 );

		return SHOP_SEQ_BUY_SELECT;
	}
	return SHOP_SEQ_BUYOMAKE_WAIT;
}

static void ShopBuyItemNameWordSet( SHOP_WORK * wk, u16 item, u16 bufID )
{
	if( wk->shop_type == SHOP_TYPE_ITEM ){
		WORDSET_RegisterItemName( wk->wset, bufID, item );
	}else if( wk->shop_type == SHOP_TYPE_GOODS ){
		WORDSET_RegisterUGGoodsName( wk->wset, bufID, item );
	}else{
		WORDSET_RegisterSealName( wk->wset, bufID, Seal_NameGet((u8)item) );
	}
}

static u32 ShopBuyItemPriceGet( SHOP_WORK * wk, u16 item )
{
	if( wk->shop_type == SHOP_TYPE_ITEM ){
		return ItemParamGet( item, ITEM_PRM_PRICE, HEAPID_WORLD );
	}else if( wk->shop_type == SHOP_TYPE_GOODS ){
		return GOODS_GetGoodsMoney( (const int)item );
	}
	return Seal_PriceGet( (u8)item );
}



//--------------------------------------------------------------------------------------------
/**
 * 終了スクロール
 */
//--------------------------------------------------------------------------------------------
static u8 ShopBuyEndSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk )
{
	if( wk->cm_cnt != wk->cm_max ){
		VecFx32 move = {-8*FX32_ONE,0,0};
		GFC_ShiftCamera( &move, wk->camera );
		wk->cm_cnt++;
		return SHOP_SEQ_BUY_END;
	}
	wk->cm_cnt = 0;
	GFC_CopyCamera( wk->camera, fsys->camera_ptr );		// カメラ反映
	GFC_FreeCamera( wk->camera);						// カメラ削除
	GFC_AttachCamera( fsys->camera_ptr );				// カメラアタッチ
//	ShopMenuSet( wk );

	ShopBuyActExit( wk );

	FldTalkBmpAdd( fsys->bgl, &wk->win[WIN_IDX_FLDTALK], FLD_MBGFRM_FONT );
	FieldTalkWinPut( &wk->win[WIN_IDX_FLDTALK], wk->cfg );
	{
		STRBUF * str = MSGMAN_AllocString( wk->mman, mes_shop_01_03 );
		WORDSET_ExpandStr( wk->wset, wk->msgb, str );
		STRBUF_Delete( str );
	}
	wk->midx = FieldTalkMsgStart( &wk->win[WIN_IDX_FLDTALK], wk->msgb, wk->cfg, 1 );

	return SHOP_SEQ_MENU_RET;
}


static u8 ShopBuyMenuRetSeq( SHOP_WORK * wk )
{
	if( FldTalkMsgEndCheck( wk->midx ) == 0 ){
		return SHOP_SEQ_MENU_RET;
	}
	GF_BGL_BmpWinDel( &wk->win[WIN_IDX_FLDTALK] );
	ShopMenuSet( wk );
	return SHOP_SEQ_MENU;
}






static void ShopExitSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, mes_shop_01_02 );
	WORDSET_ExpandStr( wk->wset, wk->msgb, str );
	STRBUF_Delete( str );
	FldTalkBmpAdd( fsys->bgl, &wk->win[WIN_IDX_FLDTALK], FLD_MBGFRM_FONT );
	FieldTalkWinPut( &wk->win[WIN_IDX_FLDTALK], wk->cfg );
	wk->midx = FieldTalkMsgStart( &wk->win[WIN_IDX_FLDTALK], wk->msgb, wk->cfg, 1 );
}







enum {
	CLA_ID_ARROW = 0,
	CLA_ID_CURSOR,
	CLA_ID_ITEMICON,
};

#define	LIST_SCR_PX		( 177 )
#define	LIST_SCR_U_PY	( 8 )
#define	LIST_SCR_D_PY	( 132 )

#define	NUM_SCR_PX		( 162 )
#define	NUM_SCR_U_PY	( 108 )
#define	NUM_SCR_D_PY	( 132 )

#define	SHOP_ITEMICON_PX	( 22 )
#define	SHOP_ITEMICON_PY	( 172 )


static const TCATS_RESOURCE_FILE_LIST CatsFileList = {
	"data/shop_chr.resdat",		// キャラクタ
	"data/shop_pal.resdat",		// パレット
	"data/shop_cell.resdat",	// セル
	"data/shop_canm.resdat",	// セルアニメ
	NULL,						// マルチセル
	NULL,						// マルチセルアニメ
	"data/shop_h.cldat"			// ヘッダー

};

static const TCATS_OBJECT_ADD_PARAM	ActAddParam[] =
{
	{	// 上矢印カーソル
		CLA_ID_ARROW,
		LIST_SCR_PX, LIST_SCR_U_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{	// 下矢印カーソル
		CLA_ID_ARROW,
		LIST_SCR_PX, LIST_SCR_D_PY, 0,
		1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{	// カーソル
		CLA_ID_CURSOR,
		CURSOR_ACT_PX, CURSOR_ACT_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{	// アイテムアイコン
		CLA_ID_ITEMICON,
		SHOP_ITEMICON_PX, SHOP_ITEMICON_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
};


static void ShopBuyActSet( SHOP_WORK * wk )
{
	u32	i;

	FieldCellActSet( &wk->fcat, &CatsFileList, SHOP_CLA_MAX, HEAPID_WORLD );

	for( i=0; i<SHOP_CLA_MAX; i++ ){
		wk->cwp[i] = FieldCellActAdd( &wk->fcat, &ActAddParam[i] );
	}

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

static void ShopBuyActExit( SHOP_WORK * wk )
{
	u32	i;

	for( i=0; i<SHOP_CLA_MAX; i++ ){
		CLACT_Delete( wk->cwp[i] );
	}
	FieldCellActDelete( &wk->fcat );
}


static void ShopBuyScrCurPosChg( SHOP_WORK * wk, u8 flg )
{
	if( flg == 0 ){
		CATS_ObjectPosSet( wk->cwp[SHOP_CLA_ARROW_U], LIST_SCR_PX, LIST_SCR_U_PY );
		CATS_ObjectPosSet( wk->cwp[SHOP_CLA_ARROW_D], LIST_SCR_PX, LIST_SCR_D_PY );
	}else{
		CATS_ObjectPosSet( wk->cwp[SHOP_CLA_ARROW_U], NUM_SCR_PX, NUM_SCR_U_PY );
		CATS_ObjectPosSet( wk->cwp[SHOP_CLA_ARROW_D], NUM_SCR_PX, NUM_SCR_D_PY );
	}
}


static void ShopBuyItemIconChg( SHOP_WORK * wk, u16 item )
{
	CLACT_U_RES_OBJ_PTR	obj;

	if( wk->shop_type != SHOP_TYPE_ITEM ){
		CLACT_SetDrawFlag( wk->cwp[SHOP_CLA_ITEMICON], 0 );
		return;
	}

	// キャラ
	obj = CLACT_U_ResManagerGetIDResObjPtr( wk->fcat.resMan[0], 2 );
	CLACT_U_ResManagerResChgArcChar(
		wk->fcat.resMan[0], obj,
		ARC_ITEMICON, GetItemIndex(item,ITEM_GET_ICON_CGX), 0, HEAPID_WORLD );
	CLACT_U_CharManagerReTrans( obj );

	// パレット
	obj = CLACT_U_ResManagerGetIDResObjPtr( wk->fcat.resMan[1], 1 );
	CLACT_U_ResManagerResChgArcPltt(
		wk->fcat.resMan[1], obj,
		ARC_ITEMICON, GetItemIndex(item,ITEM_GET_ICON_PAL), 0, HEAPID_WORLD );
	CLACT_U_PlttManagerReTrans( obj );
}


static void ShopBuyCursorPalChg( SHOP_WORK * wk, u8 num )
{
	CATS_ObjectPaletteSet( wk->cwp[SHOP_CLA_CURSOR], num );
}




//============================================================================================
//	売る
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * フェードアウトセット ( -> バッグ画面へ )
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ShopSaleInitSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk )
{
	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );
	wk->seq = SHOP_SEQ_SALE_CALL;
}

//--------------------------------------------------------------------------------------------
/**
 * バッグ画面呼び出し
 *
 * @param	fsys	フィールドワーク
 * @param	wk		ショップワーク
 *
 * @return	移行するシーケンス
 */
//--------------------------------------------------------------------------------------------
static void ShopSaleCallSeq( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	SHOP_WORK * wk;

	if( WIPE_SYS_EndCheck() == FALSE ){ return; }

	fsys = FieldEvent_GetFieldSysWork(event);
	wk = FieldEvent_GetSpecialWork(event);

	ShopMenuExit( wk );

	{
		MYITEM * myitem;

		myitem = SaveData_GetMyItem( fsys->savedata );
		wk->bag_wk = MyItem_MakeBagData( myitem, BagList, HEAPID_WORLD );
		BAG_SysDataSet( wk->bag_wk, fsys->savedata, BAG_MODE_ITEMSALE, fsys->bag_cursor );
	}

	FieldBag_SubProcSet( fsys, wk->bag_wk );

	FieldEvent_Change( event, GMEVENT_ShopSale, wk );
	wk->seq = SHOP_SEQ_SALE_WAIT;
}

//--------------------------------------------------------------------------------------------
/**
 * バッグ画面終了待ち
 *
 * @param	fsys	フィールドワーク
 * @param	wk		ショップワーク
 *
 * @return	移行するシーケンス
 */
//--------------------------------------------------------------------------------------------
/*
static u8 ShopSaleWaitSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk )
{
	// サブプロセス終了待ち
	if( FieldEvent_Cmd_WaitSubProcEnd( fsys ) ) {
		return SHOP_SEQ_SALE_WAIT;
	}

	wk->fnote_sale_cnt = BagSysSaleCntGet( wk->bag_wk );

	sys_FreeMemoryEz( wk->bag_wk );

	FieldEvent_Cmd_SetMapProc( fsys );

	return SHOP_SEQ_SALE_RET;
}
*/

//--------------------------------------------------------------------------------------------
/**
 * ショップ復帰待ち
 *
 * @param	fsys	フィールドワーク
 *
 * @return	移行するシーケンス
 */
//--------------------------------------------------------------------------------------------
/*
static u8 ShopSaleRetSeq( FIELDSYS_WORK * fsys )
{
	// フィールドマッププロセス開始待ち
	if( FieldEvent_Cmd_WaitMapProcStart(fsys) ){
//		FieldOBJSys_MoveStopAll( fsys->fldobjsys );
		FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
		return SHOP_SEQ_SALE_MENU_RET;
	}
	return SHOP_SEQ_SALE_RET;
}
*/

//--------------------------------------------------------------------------------------------
/**
 * 復帰フェード待ち
 *
 * @param	fsys	フィールドワーク
 * @param	wk		ショップワーク
 *
 * @return	移行するシーケンス
 */
//--------------------------------------------------------------------------------------------
static u8 ShopSaleMenuRetSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk )
{
	if( WIPE_SYS_EndCheck() == FALSE ){
		return SHOP_SEQ_SALE_MENU_RET;
	}

	FldTalkBmpAdd( fsys->bgl, &wk->win[WIN_IDX_FLDTALK], FLD_MBGFRM_FONT );
	FieldTalkWinPut( &wk->win[WIN_IDX_FLDTALK], wk->cfg );
	{
		STRBUF * str = MSGMAN_AllocString( wk->mman, mes_shop_01_03 );
		WORDSET_ExpandStr( wk->wset, wk->msgb, str );
		STRBUF_Delete( str );
	}
	wk->midx = FieldTalkMsgStart( &wk->win[WIN_IDX_FLDTALK], wk->msgb, wk->cfg, 1 );
	return SHOP_SEQ_MENU_RET;
}
