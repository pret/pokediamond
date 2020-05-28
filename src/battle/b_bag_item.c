//============================================================================================
/**
 * @file	b_bag_item.c
 * @brief	戦闘用バッグ画面 アイテム制御関連
 * @author	Hiroyuki Nakamura
 * @date	05.02.10
 */
//============================================================================================
#include "common.h"
#include "system/palanm.h"
//#include "system/window.h"
//#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
//#include "system/pmfprint.h"
//#include "system/buflen.h"
#include "battle/battle_common.h"
#include "itemtool/myitem.h"
#include "itemtool/item.h"
#include "b_app_tool.h"

#define	B_BAG_ITEM_H_GLOBAL
#include "b_bag.h"
#include "b_bag_main.h"
#include "b_bag_item.h"







//--------------------------------------------------------------------------------------------
/**
 * 前回使用したアイテムをチェック
 *
 * @param	wk		ワーク
 *
 * @retval	"TRUE = あり"
 * @retval	"FALSE = なし"
 */
//--------------------------------------------------------------------------------------------
u8 BattleBag_UsedItemChack( BBAG_WORK * wk )
{
	if( wk->dat->used_item == 0 ){ return FALSE; }

	if( MyItem_CheckItem( wk->dat->myitem, wk->dat->used_item, 1, wk->dat->heap ) == FALSE ){
		wk->dat->used_item = 0;
		wk->dat->used_poke = 0;
		return FALSE;
	}

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * 最後に使った道具のカーソル位置再設定
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_CorsorReset( BBAG_WORK * wk )
{
	u32	i;

	for( i=0; i<BBAG_POCKET_IN_MAX; i++ ){
		if( wk->dat->used_item == wk->pocket[wk->poke_id][i].id ){
			wk->dat->item_pos[wk->poke_id] = i%6;
			wk->dat->item_scr[wk->poke_id] = i/6;
			break;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムを戦闘ポケットに振り分ける
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static const u8 PocketNum[] = {
	2, 3, 0, 1, 0
};

void BattleBag_PocketInit( BBAG_WORK * wk )
{
	MINEITEM * item;
	u32	i, j, k;
	s32	prm;

	for( i=0; i<BAG_POKE_MAX; i++ ){
		j = 0;
		while(1){
			item = MyItem_PosItemGet( wk->dat->myitem, i, j );
			if( item == NULL ){ break; }
			if( !( item->id == 0 || item->no == 0 ) ){
				prm = ItemParamGet( item->id, ITEM_PRM_BTL_POCKET, wk->dat->heap );
				for( k=0; k<5; k++ ){
					if( ( prm & (1<<k) ) == 0 ){ continue; }
					wk->pocket[ PocketNum[k] ][wk->item_max[ PocketNum[k] ]] = *item;
					wk->item_max[ PocketNum[k] ]++;
				}
			}
			j++;
		}
	}

	for( i=0; i<5; i++ ){
		if( wk->item_max[i] == 0 ){
			wk->scr_max[i] = 0;
		}else{
			wk->scr_max[i] = (wk->item_max[i]-1) / 6;
		}
		if( wk->scr_max[i] < wk->dat->item_scr[i] ){
			wk->dat->item_scr[i] = wk->scr_max[i];
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 指定位置にアイテムがあるか
 *
 * @param	wk		ワーク
 * @param	pos		位置（０～５）
 *
 * @retval	"あり = アイテム番号"
 * @retval	"なし = 0"
 */
//--------------------------------------------------------------------------------------------
u16 BattleBag_PosItemCheck( BBAG_WORK * wk, u32 pos )
{
	if( wk->pocket[wk->poke_id][wk->dat->item_scr[wk->poke_id]*6+pos].id != 0 &&
		wk->pocket[wk->poke_id][wk->dat->item_scr[wk->poke_id]*6+pos].no != 0 ){
		return wk->pocket[wk->poke_id][wk->dat->item_scr[wk->poke_id]*6+pos].id;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム機能を取得
 *
 * @param	wk		ワーク
 *
 * @return	アイテム機能
 */
//--------------------------------------------------------------------------------------------
u8 BattleBag_ItemUseCheck( BBAG_WORK * wk )
{
	return (u8)ItemParamGet( wk->dat->ret_item, ITEM_PRM_BATTLE, wk->dat->heap );
}
