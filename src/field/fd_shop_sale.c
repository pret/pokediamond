//============================================================================================
/**
 * @file	fd_shop.c
 * @brief	フレンドリィショップ バッグ制御
 * @author	Hiroyuki Nakamura
 * @date	2006.07.12
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/wordset.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "application/bag.h"

#include "fieldsys.h"
#include "fieldmap.h"
#include "field_clact.h"
#include "syswork.h"

#include "fd_shop_sys.h"
#include "fd_shop.h"


//=================================================================================================
//	プロトタイプ宣言
//=================================================================================================
static u8 ShopSaleWaitSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk );
static void ShopSaleRetSeq( GMEVENT_CONTROL * event );


//--------------------------------------------------------------------------------------------
/**
 * @brief	フィールドイベント：ショップ売却処理バッグ制御
 * @param	event	フィールドイベント用パラメータ
 * @retval	TRUE	イベント終了
 * @retval	FALSE	イベント継続
 */
//--------------------------------------------------------------------------------------------
BOOL GMEVENT_ShopSale( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	SHOP_WORK * wk;

	fsys = FieldEvent_GetFieldSysWork(event);
	wk = FieldEvent_GetSpecialWork(event);

	switch( wk->seq ){
	case SHOP_SEQ_SALE_WAIT:		// 「売る」終了待ち
		wk->seq = ShopSaleWaitSeq( fsys, wk );
		break;

	case SHOP_SEQ_SALE_RET:			// 「売る」終了 -> フェードイン
		ShopSaleRetSeq( event );
		break;
	}
	return FALSE;
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

//--------------------------------------------------------------------------------------------
/**
 * ショップ復帰待ち
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	移行するシーケンス
 */
//--------------------------------------------------------------------------------------------
static void ShopSaleRetSeq( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	SHOP_WORK * wk;

	fsys = FieldEvent_GetFieldSysWork(event);
	wk = FieldEvent_GetSpecialWork(event);

	// フィールドマッププロセス開始待ち
	if( FieldEvent_Cmd_WaitMapProcStart(fsys) ){
		FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
		FieldEvent_Change( event, GMEVENT_Shop, wk );
		wk->seq = SHOP_SEQ_SALE_MENU_RET;
	}
}
