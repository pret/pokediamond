//============================================================================================
/**
 * @file	ntag_dat.c
 * @brief	�؂̎��^�O��ʃf�[�^����
 * @author	Hiroyuki Nakamura
 * @date	06.03.29
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "itemtool/itemsym.h"
#include "itemtool/nuts.h"

#include "ntag_dat.h"
#include "application/nuts_tag.h"


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void TagPutFlagSet( u32 * flg, u16 id );


//--------------------------------------------------------------------------------------------
/**
 * �؂̎��^�O��ʂ̃f�[�^�̈�m��
 *
 * @param	heap	�q�[�v�h�c
 *
 * @return	�m�ۂ����̈�̃A�h���X
 */
//--------------------------------------------------------------------------------------------
NTAG_DATA * NutsTagSystemDataAlloc( u8 heap )
{
	NTAG_DATA * wk = (NTAG_DATA *)sys_AllocMemory( heap, sizeof(NTAG_DATA) );
	memset( wk, 0, sizeof(NTAG_DATA) );
	return wk;
}

u32 NutsTagSystemDataSizeGet(void)
{
	return sizeof(NTAG_DATA);
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎��^�O��ʂ̕\���^�O�ݒ�
 *
 * @param	dat		�f�[�^�ݒ�ꏊ
 * @param	item	�A�C�e���ԍ�
 * @param	flg		�����^�O�ݒ�t���O
 *
 * @return	none
 *
 * @li	flg = TAG_ON : �ŏ��ɕ\�������^�O�ɐݒ�
 */
//--------------------------------------------------------------------------------------------
void NutsTagPutDataSet( NTAG_DATA * dat, u16 item, u16 flg )
{
	u16	num = item - NUTS_START_ITEMNUM;

	TagPutFlagSet( dat->tag_flg, num );
	if( flg == TAG_ON ){
		dat->now_tag = num;
	}
}

void NutsTagBagCursorSet( NTAG_DATA * dat, u8 scr, u8 cur, u8 max )
{
	dat->scr = scr;
	dat->cur = cur;
	dat->max = max;
}

//--------------------------------------------------------------------------------------------
/**
 * �\���\�^�O�Z�b�g
 *
 * @param	flg		�t���O�ݒ�ꏊ
 * @param	id		�^�OID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TagPutFlagSet( u32 * flg, u16 id )
{
	flg[id/32] |= (1<<(id%32));
}

//--------------------------------------------------------------------------------------------
/**
 * �\���\�^�O�`�F�b�N
 *
 * @param	flg		�t���O�ݒ�ꏊ
 * @param	id		�^�OID
 *
 * @retval	"TRUE = ��"
 * @retval	"FALSE = �s��"
 */
//--------------------------------------------------------------------------------------------
u8 TagPutFlagGet( u32 * flg, u16 id )
{
	if( ( flg[id/32] & (1<<(id%32)) ) != 0 ){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ���݂̕\���ʒu�擾
 *
 * @param	dat		�f�[�^�ݒ�ꏊ
 *
 * @return	�\���ʒu
 */
//--------------------------------------------------------------------------------------------
void TagPosGet( NTAG_DATA * dat, u8 * scr, u8 * cur )
{
	*scr = dat->scr;
	*cur = dat->cur;
}


