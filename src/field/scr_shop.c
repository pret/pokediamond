//============================================================================================
/**
 * @file	scr_shop.c
 * @bfief	�X�N���v�g�R�}���h�F�V���b�v�֘A
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
//	�\����
//
//============================================================================================
//�V���b�v�A�C�e���f�[�^�^
typedef struct{
	u16 itemno;		//�A�C�e���i���o�[
	u16 level;		//�i�K
}SHOP_ITEM_DATA;


//============================================================================================
//
//	�f�[�^
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
//	�R�}���h
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �ϓ��t�����h���V���b�v�Ăяo��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdShopCall( VM_MACHINE * core )
{
	u16 list[64];
	u8 level,badge,count,i;
	u16 id	= VMGetWorkValue(core);

	//������
	count = 0;
	badge = 0;
	level = 0;

	//�o�b�W���擾
	for( i=0; i < BADGE_MAX ;i++ ){
		if( MyStatus_GetBadgeFlag(SaveData_GetMyStatus(core->fsys->savedata), i) == TRUE ){
			badge++;
		}
	}

	//�i�K���擾
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
		if( level >= shop_item_data[i].level ){			//�i�K���r
			list[count] = shop_item_data[i].itemno;		//�f�[�^�Z�b�g
			count++;
		}
	}
	list[count] = 0xffff;								//�I���R�[�h�Z�b�g

	//�C�x���g�R�[���Ȃ̂ŁA�X�N���v�g�ɕ��A���܂��B
	ShopInit( core->event_work, core->fsys, list, SHOP_TYPE_ITEM, FALSE );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �Œ�t�����h���V���b�v�Ăяo��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
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

	//�C�x���g�R�[���Ȃ̂ŁA�X�N���v�g�ɕ��A���܂��B
	ShopInit( core->event_work, core->fsys, (u16*)fs_item_data[id], SHOP_TYPE_ITEM, dp_flg );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �Œ�O�b�Y�V���b�v�Ăяo��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
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

	//�C�x���g�R�[���Ȃ̂ŁA�X�N���v�g�ɕ��A���܂��B
	ShopInit( core->event_work, core->fsys, (u16*)fs_goods_data[id], SHOP_TYPE_GOODS, dp_flg );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �Œ�V�[���V���b�v�Ăяo��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdFixSealCall( VM_MACHINE * core )
{
	u16 id	= VMGetWorkValue(core);

	//�C�x���g�R�[���Ȃ̂ŁA�X�N���v�g�ɕ��A���܂��B
	ShopInit( core->event_work, core->fsys, (u16*)fs_seal_data[id], SHOP_TYPE_SEAL, FALSE );
	return 1;
}


//--------------------------------------------------------------------------------------------
/**
 * �A�N�Z�T���[�V���b�v�Ăяo��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAcceShopCall( VM_MACHINE * core )
{
	//�C�x���g�R�[���Ȃ̂ŁA�X�N���v�g�ɕ��A���܂��B
	EventCmd_AcceShop(core->fsys->event);
	return 1;
}

