//============================================================================================
/**
 * @file	bag.c
 * @brief	�o�b�O��ʏ��� �O���Q�Ə���
 * @author	Hiroyuki Nakamura
 * @date	05.07.14
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/clact_tool.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "savedata/config.h"
#include "savedata/coin.h"
#include "savedata/custom_ball.h"
#include "savedata/b_tower.h"
#include "savedata/imageclip_data.h"
#include "itemtool/itemsym.h"
#include "field/itemuse.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_bag.h"
#include "msgdata/msg_common_scr.h"

#define	BAG_H_GLOBAL
#include "application/bag.h"
#include "bag_main.h"


//============================================================================================
//	�萔��`
//============================================================================================


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static u32 BAG_CoinValGet( SAVEDATA * sv );
static u32 BAG_SealValGet( SAVEDATA * sv );
static u32 BAG_AccessoryValGet( SAVEDATA * sv );
static u32 BAG_WallpaperValGet( SAVEDATA * sv );
static u32 BAG_BattlePointGet( SAVEDATA * sv );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================


//--------------------------------------------------------------------------------------------
/**
 * �o�b�O��ʂ̃f�[�^�̈�m��
 *
 * @param	mode	�������擾���[�h
 *
 * @return	�m�ۂ����̈�̃A�h���X
 */
//--------------------------------------------------------------------------------------------
BAG_DATA * BagSystemDataAlloc( u8 mode )
{
	BAG_DATA * wk = (BAG_DATA *)sys_AllocMemory( mode, sizeof(BAG_DATA) );
	memset( wk, 0, sizeof(BAG_DATA) );
	return wk;
}

u32 BagSystemDataSizeGet(void)
{
	return sizeof(BAG_DATA);
}



//--------------------------------------------------------------------------------------------
/**
 * �o�b�O��ʂ̏����y�[�W�ݒ�
 *
 * @param	dat		�f�[�^�ݒ�ꏊ
 * @param	page	�����y�[�W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BAG_InitPageSet( BAG_DATA * dat, u8 page )
{
	dat->p_now = page;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�O��ʂ̃��[�h�ݒ�
 *
 * @param	dat		�f�[�^�ݒ�ꏊ
 * @param	mode	�o�b�O��ʂ̖���
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BAG_ModeSet( BAG_DATA * dat, u8 mode )
{
	dat->mode  = mode;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�O��ʂ̏����f�[�^�쐬
 *
 * @param	dat		�f�[�^�ݒ�ꏊ
 * @param	sv		�Z�[�u�f�[�^
 * @param	mode	�o�b�O��ʂ̖���
 * @param	cur		�J�[�\���L���ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BAG_SysDataSet( BAG_DATA * dat, SAVEDATA * sv, u8 mode, void * cur )
{
	BAG_ModeSet( dat, mode );
	dat->sv = sv;
	dat->bag_cursor = cur;
	dat->ret_item = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g�f�[�^�쐬
 *
 * @param	dat		�o�b�O��ʂ̃f�[�^
 * @param	item	�Q�Ƃ���A�C�e���f�[�^
 * @param	type	�|�P�b�g�^�C�v
 * @param	poke	�|�P�b�g�ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BagPocketDataMake( BAG_DATA * dat, MINEITEM * item, u8 type, u8 poke )
{
	dat->p_data[poke].item = item;		// �Q�Ƃ���A�C�e���f�[�^
	dat->p_data[poke].type = type;		// �|�P�b�g�^�C�v
}

//--------------------------------------------------------------------------------------------
/**
 * ���]�ԃt���O�Z�b�g
 *
 * @param	dat		�o�b�O��ʂ̃f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BagCycleFlagSet( BAG_DATA * dat )
{
	dat->cycle_flg = 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�`�F�b�N���[�N�Z�b�g
 *
 * @param	dat		�o�b�O��ʂ̃f�[�^
 * @param	icwk	�A�C�e���g�p�`�F�b�N���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_ItemUseCheckSet( BAG_DATA * dat, void * icwk )
{
	dat->icwk = icwk;
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e�����g�p�����|�P�����ʒu�ݒ�
 *
 * @param	dat			�o�b�O��ʂ̃f�[�^
 * @param	use_poke	�g�p�����|�P�����ʒu
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_UsePokeSet( BAG_DATA * dat, u8 use_poke )
{
	dat->use_poke = use_poke;
}

//--------------------------------------------------------------------------------------------
/**
 * �}�b�v���[�h�ݒ�
 *
 * @param	dat			�o�b�O��ʂ̃f�[�^
 * @param	map_mode	�}�b�v���[�h
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BAG_SysMapModeSet( BAG_DATA * dat, u16 map_mode )
{
	dat->map_mode = map_mode;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾�F���݂̃|�P�b�g�ԍ�
 *
 * @param	dat		�o�b�O��ʂ̃f�[�^
 *
 * @return	���݂̃|�P�b�g�ԍ�
 */
//--------------------------------------------------------------------------------------------
u8 BagSysNowPocketNumGet( BAG_DATA * dat )
{
	return dat->p_now;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾�F�o�b�O��ʂ̖���
 *
 * @param	dat		�o�b�O��ʂ̃f�[�^
 *
 * @return	�o�b�O��ʂ̖���
 */
//--------------------------------------------------------------------------------------------
u8 BagSysModeGet( BAG_DATA * dat )
{
	return dat->mode;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾�F�o�b�O�Ŏ擾�����A�C�e��
 *
 * @param	dat		�o�b�O��ʂ̃f�[�^
 *
 * @return	�o�b�O�Ŏ擾�����A�C�e��
 */
//--------------------------------------------------------------------------------------------
u16 BagSysReturnItemGet( BAG_DATA * dat )
{
	return dat->ret_item;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾�F�o�b�O�̖߂�l
 *
 * @param	dat		�o�b�O��ʂ̃f�[�^
 *
 * @return	�o�b�O�̖߂�l
 */
//--------------------------------------------------------------------------------------------
u16 BagSysReturnModeGet( BAG_DATA * dat )
{
	return dat->ret_mode;
}

//--------------------------------------------------------------------------------------------
/**
 * �O��A�C�e�����g�p�����|�P�����ʒu���擾
 *
 * @param	dat			�o�b�O��ʂ̃f�[�^
 *
 * @return	�A�C�e�����g�p�����|�P�����ʒu
 */
//--------------------------------------------------------------------------------------------
u8 Bag_UsePokeGet( BAG_DATA * dat )
{
	return dat->use_poke;
}


//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾�F�J�[�\���ʒu�A�X�N���[���J�E���^
 *
 * @param	dat		�o�b�O��ʂ̃f�[�^
 * @param	poke	�|�P�b�g�ԍ�
 * @param	cur		�J�[�\���ʒu
 * @param	scr		�X�N���[���J�E���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BagCursorPosGet( BAG_DATA * dat, u8 poke, u16 * cur, u16 * scr )
{
	if( cur != NULL ){
		*cur = dat->p_data[poke].cur;
	}
	if( scr != NULL ){
		*scr = dat->p_data[poke].scr;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾�F���������J�E���^�i�`���m�[�g�p�j
 *
 * @param	dat		�o�b�O��ʂ̃f�[�^
 *
 * @return	���݂̃|�P�b�g�ԍ�
 */
//--------------------------------------------------------------------------------------------
u8 BagSysSaleCntGet( BAG_DATA * dat )
{
	return dat->fnote_sale_cnt;
}



// �R�C�����擾
static u32 BAG_CoinValGet( SAVEDATA * sv )
{
	return COIN_GetValue( SaveData_GetMyCoin(sv) );
}

// �V�[�����擾
static u32 BAG_SealValGet( SAVEDATA * sv )
{
	CB_SAVE_DATA * csd;
	u32	i, max;

	csd = CB_SaveData_AllDataGet( sv );
	max = 0;

	for( i=1; i<=CB_DEF_ITEM_DATA_NUM_MAX; i++ ){
		max += CB_Tool_SealTotalNumGet( csd, i );
	}
	return max;
}

// �A�N�Z�T���[���擾
static u32 BAG_AccessoryValGet( SAVEDATA * sv )
{
	IMC_ITEM_SAVEDATA * imci = ImcSaveData_GetItemSaveData( SaveData_GetImcSaveData(sv) );

	return ImcSaveData_GetAcceAllNum( imci );
}

// �ǎ����擾
static u32 BAG_WallpaperValGet( SAVEDATA * sv )
{
	IMC_ITEM_SAVEDATA * imci = ImcSaveData_GetItemSaveData( SaveData_GetImcSaveData(sv) );

	return ImcSaveData_GetBGAllNum( imci );
}

// �o�g���|�C���g�擾
static u32 BAG_BattlePointGet( SAVEDATA * sv )
{
	return (u32)BattlePoint_Get( sv );
}

BOOL BAG_ItemUseMsgSet( SAVEDATA * sv, STRBUF * buf, u16 item, u32 heap )
{
	MSGDATA_MANAGER * mman;
	WORDSET * wset;
	STRBUF * str;

	mman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_bag_dat, heap );
	wset = WORDSET_Create( heap );

	if( item == ITEM_DUMMY_DATA ){
		str = MSGMAN_AllocString( mman, mes_bag_108 );
	}else if( item == ITEM_POINTOKAADO ){
		str = MSGMAN_AllocString( mman, mes_bag_106 );
		WORDSET_RegisterNumber(
			wset, 0, BAG_BattlePointGet(sv), 4, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}else if( item == ITEM_SIIRUIRE ){
		str = MSGMAN_AllocString( mman, mes_bag_101 );
		WORDSET_RegisterNumber(
			wset, 0, BAG_SealValGet(sv), 4, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}else if( item == ITEM_AKUSESARIIIRE ){
		str = MSGMAN_AllocString( mman, mes_bag_102 );
		WORDSET_RegisterNumber(
			wset, 0, BAG_AccessoryValGet(sv), 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_RegisterNumber(
			wset, 1, BAG_WallpaperValGet(sv), 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}else if( item == ITEM_KOINKEESU ){
		str = MSGMAN_AllocString( mman, msg_bag_062 );
		WORDSET_RegisterNumber(
			wset, 0, BAG_CoinValGet(sv), 5, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}else{
		WORDSET_Delete( wset );
		MSGMAN_Delete( mman );
		return FALSE;
	}

	WORDSET_ExpandStr( wset, buf, str );
	STRBUF_Delete( str );
	WORDSET_Delete( wset );
	MSGMAN_Delete( mman );

	return TRUE;
}

// �G���[���b�Z�[�W�Z�b�g
void BAG_ItemUseErrorMsgSet( void * myst, STRBUF * buf, u16 item, u32 err, u32 heap )
{
	MSGDATA_MANAGER * mman;
	WORDSET * wset;
	STRBUF * str;

//	wset = WORDSET_Create( heap );

	switch( err ){
	case ITEMCHECK_ERR_CYCLE_OFF:		// ���]�Ԃ��~���Ȃ�
		mman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_bag_dat, heap );
		MSGMAN_GetString( mman, msg_bag_058, buf );
		MSGMAN_Delete( mman );
		break;

	case ITEMCHECK_ERR_COMPANION:		// �g�p�s�E�A�����
		mman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_bag_dat, heap );
		MSGMAN_GetString( mman, msg_bag_err_01, buf );
		MSGMAN_Delete( mman );
		break;

	default:							// �g�p�s�E���m�̌��t
		mman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_common_scr_dat, heap );
		wset = WORDSET_Create( heap );
		str  = MSGMAN_AllocString( mman, msg_item_ng_01 );
		WORDSET_RegisterPlayerName( wset, 0, myst );
		WORDSET_ExpandStr( wset, buf, str );
		STRBUF_Delete( str );
		WORDSET_Delete( wset );
		MSGMAN_Delete( mman );
	}

/*
	WORDSET_ExpandStr( wset, buf, str );
	STRBUF_Delete( str );
	WORDSET_Delete( wset );
	MSGMAN_Delete( mman );
*/

}
