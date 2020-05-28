//============================================================================================
/**
 * @file	b_bag_item.c
 * @brief	�퓬�p�o�b�O��� �A�C�e������֘A
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
 * �O��g�p�����A�C�e�����`�F�b�N
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = ����"
 * @retval	"FALSE = �Ȃ�"
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
 * �Ō�Ɏg��������̃J�[�\���ʒu�Đݒ�
 *
 * @param	wk		���[�N
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
 * �A�C�e����퓬�|�P�b�g�ɐU�蕪����
 *
 * @param	wk		���[�N
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
 * �w��ʒu�ɃA�C�e�������邩
 *
 * @param	wk		���[�N
 * @param	pos		�ʒu�i�O�`�T�j
 *
 * @retval	"���� = �A�C�e���ԍ�"
 * @retval	"�Ȃ� = 0"
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
 * �A�C�e���@�\���擾
 *
 * @param	wk		���[�N
 *
 * @return	�A�C�e���@�\
 */
//--------------------------------------------------------------------------------------------
u8 BattleBag_ItemUseCheck( BBAG_WORK * wk )
{
	return (u8)ItemParamGet( wk->dat->ret_item, ITEM_PRM_BATTLE, wk->dat->heap );
}
