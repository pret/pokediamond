//============================================================================================
/**
 * @file	scr_shop.c
 * @bfief	スクリプトコマンド：ショップ関連
 * @author	Satoshi Nohara
 * @date	06.06.23
 */
//============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "fd_shop.h"
#include "itemtool/itemsym.h"

#include "../fielddata/shopdata/fs_item_def.h"
#include "../fielddata/shopdata/fs_goods_def.h"

#include "scr_shop.h"

//============================================================================================
//
//	構造体
//
//============================================================================================
//ショップアイテムデータ型
typedef struct{
	u16 itemno;		//アイテムナンバー
	u16 level;		//段階
}SHOP_ITEM_DATA;


//============================================================================================
//
//	データ
//
//============================================================================================
#include "..\fielddata\shopdata\shop_item.dat"
#include "..\fielddata\shopdata\fs_item.dat"
#include "..\fielddata\base_goods\goods_id_def.h"
#include "..\fielddata\shopdata\fs_goods.dat"
#include "application\seal_id.h"
#include "..\fielddata\shopdata\fs_seal.dat"


//============================================================================================
//
//	コマンド
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 変動フレンドリショップ呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdShopCall( VM_MACHINE * core )
{
	u16 list[64];
	u8 level,badge,count,i;
	u16 id	= VMGetWorkValue(core);

	//初期化
	count = 0;
	badge = 0;
	level = 0;

	//バッジ数取得
	for( i=0; i < BADGE_MAX ;i++ ){
		if( MyStatus_GetBadgeFlag(SaveData_GetMyStatus(core->fsys->savedata), i) == TRUE ){
			badge++;
		}
	}

	//段階を取得
	switch( badge ){
	case 0:
		level = 1;
		break;
	case 1:
	case 2:
		level = 2;
		break;
	case 3:
	case 4:
		level = 3;
		break;
	case 5:
	case 6:
		level = 4;
		break;
	case 7:
		level = 5;
		break;
	case 8:
		level = 6;
		break;
	default:
		level = 1;
		break;
	};

	for( i=0; i < SHOP_ITEM_DATA_MAX ;i++ ){
		if( level >= shop_item_data[i].level ){			//段階を比較
			list[count] = shop_item_data[i].itemno;		//データセット
			count++;
		}
	}
	list[count] = 0xffff;								//終了コードセット

	//イベントコールなので、スクリプトに復帰します。
	ShopInit( core->event_work, core->fsys, list, SHOP_TYPE_ITEM, FALSE );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 固定フレンドリショップ呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdFixShopCall( VM_MACHINE * core )
{
	u16 id	= VMGetWorkValue(core);
	BOOL dp_flg;

	if( id == ID_SHOP_ITEM_C07_DEPT_01_01 || id == ID_SHOP_ITEM_C07_DEPT_01_02 ||
		id == ID_SHOP_ITEM_C07_DEPT_02_01 || id == ID_SHOP_ITEM_C07_DEPT_02_02 ||
		id == ID_SHOP_ITEM_C07_DEPT_03_01 || id == ID_SHOP_ITEM_C07_DEPT_03_02 ){
		dp_flg = TRUE;
	}else{
		dp_flg = FALSE;
	}

	//イベントコールなので、スクリプトに復帰します。
	ShopInit( core->event_work, core->fsys, (u16*)fs_item_data[id], SHOP_TYPE_ITEM, dp_flg );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 固定グッズショップ呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdFixGoodsCall( VM_MACHINE * core )
{
	u16 id	= VMGetWorkValue(core);
	BOOL dp_flg;

	if( id == ID_SHOP_GOODS_C07_DEPT_04_01 || id == ID_SHOP_GOODS_C07_DEPT_04_02 ){
		dp_flg = TRUE;
	}else{
		dp_flg = FALSE;
	}

	//イベントコールなので、スクリプトに復帰します。
	ShopInit( core->event_work, core->fsys, (u16*)fs_goods_data[id], SHOP_TYPE_GOODS, dp_flg );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 固定シールショップ呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdFixSealCall( VM_MACHINE * core )
{
	u16 id	= VMGetWorkValue(core);

	//イベントコールなので、スクリプトに復帰します。
	ShopInit( core->event_work, core->fsys, (u16*)fs_seal_data[id], SHOP_TYPE_SEAL, FALSE );
	return 1;
}


//--------------------------------------------------------------------------------------------
/**
 * アクセサリーショップ呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAcceShopCall( VM_MACHINE * core )
{
	//イベントコールなので、スクリプトに復帰します。
	EventCmd_AcceShop(core->fsys->event);
	return 1;
}

