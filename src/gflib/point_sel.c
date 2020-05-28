//============================================================================================
/**
 * @file	point_sel.c
 * @brief	�ʒu�C���f�b�N�X�I������
 * @author	Hiroyuki Nakamura
 * @date	2004.11.12
 */
//============================================================================================
#define	POINT_SEL_H_GLOBAL

#include "system.h"
#include "point_sel.h"


//============================================================================================
//	�V���{����`
//============================================================================================


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================


//--------------------------------------------------------------------------------------------
/**
 * �p�����[�^�擾
 *
 * @param	pw		���[�N
 * @param	flg		�擾�t���O
 *
 * @return	�w��p�����[�^
 */
//--------------------------------------------------------------------------------------------
u8 PointerWorkGet( const POINTER_WORK * pw, u8 flg )
{
	switch( flg ){
	case POINT_WK_PX:
		return pw->px;
	case POINT_WK_PY:
		return pw->py;
	case POINT_WK_SX:
		return pw->sx;
	case POINT_WK_SY:
		return pw->sy;
	case POINT_WK_UP:
		return pw->up;
	case POINT_WK_DOWN:
		return pw->down;
	case POINT_WK_LEFT:
		return pw->left;
	case POINT_WK_RIGHT:
		return pw->right;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ���W�擾
 *
 * @param	pw		���[�N
 * @param	x		X���W�i�[�ꏊ
 * @param	y		Y���W�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PointerWkPosGet( const POINTER_WORK * pw, u8 * x, u8 * y )
{
	*x = pw->px;
	*y = pw->py;
}

//--------------------------------------------------------------------------------------------
/**
 * �T�C�Y�擾
 *
 * @param	pw		���[�N
 * @param	x		X�T�C�Y�i�[�ꏊ
 * @param	y		Y�T�C�Y�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PointerWkSizeGet( const POINTER_WORK * pw, u8 * x, u8 * y )
{
	*x = pw->sx;
	*y = pw->sy;
}

//--------------------------------------------------------------------------------------------
/**
 * �ړ��������w�肵�A���W�A�T�C�Y�A�C���f�b�N�X���擾����
 *
 * @param	pw		���[�N
 * @param	px		X���W�i�[�ꏊ
 * @param	py		Y���W�i�[�ꏊ
 * @param	sx		X�T�C�Y�i�[�ꏊ
 * @param	sy		Y�T�C�Y�i�[�ꏊ
 * @param	now		���݂̃C���f�b�N�X
 * @param	mv		�ړ�����
 *
 * @return	�ړ���̃C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u8 PointerWkMoveSel(
		const POINTER_WORK * pw, u8 * px, u8 * py, u8 * sx, u8 * sy, u8 now, u8 mv )
{
	u8	next = now;

	switch( mv ){
	case POINT_MV_UP:
		next = pw[now].up;
		break;
	case POINT_MV_DOWN:
		next = pw[now].down;
		break;
	case POINT_MV_LEFT:
		next = pw[now].left;
		break;
	case POINT_MV_RIGHT:
		next = pw[now].right;
		break;
	}
	if( px != NULL ){ *px = pw[next].px; }
	if( py != NULL ){ *py = pw[next].py; }
	if( sx != NULL ){ *sx = pw[next].sx; }
	if( sy != NULL ){ *sy = pw[next].sy; }

	return next;
}

//--------------------------------------------------------------------------------------------
/**
 * �\���L�[�̏�񂩂�A���W�A�T�C�Y�A�C���f�b�N�X���擾����
 *
 * @param	pw		���[�N
 * @param	px		X���W�i�[�ꏊ
 * @param	py		Y���W�i�[�ꏊ
 * @param	sx		X�T�C�Y�i�[�ꏊ
 * @param	sy		Y�T�C�Y�i�[�ꏊ
 * @param	now		���݂̃C���f�b�N�X
 *
 * @return	�ړ���̃C���f�b�N�X�i�\���L�[��������Ă��Ȃ��ꍇ��POINT_SEL_NOMOVE�j
 *
 * @li	sys.trg���g�p
 */
//--------------------------------------------------------------------------------------------
u8 PointerWkMoveSelTrg( const POINTER_WORK * pw, u8 * px, u8 * py, u8 * sx, u8 * sy, u8 now )
{
	if( sys.trg & PAD_KEY_UP ){
		return PointerWkMoveSel( pw, px, py, sx, sy, now, POINT_MV_UP );
	}
	if( sys.trg & PAD_KEY_DOWN ){
		return PointerWkMoveSel( pw, px, py, sx, sy, now, POINT_MV_DOWN );
	}
	if( sys.trg & PAD_KEY_LEFT ){
		return PointerWkMoveSel( pw, px, py, sx, sy, now, POINT_MV_LEFT );
	}
	if( sys.trg & PAD_KEY_RIGHT ){
		return PointerWkMoveSel( pw, px, py, sx, sy, now, POINT_MV_RIGHT );
	}
	return POINT_SEL_NOMOVE;
}

//--------------------------------------------------------------------------------------------
/**
 * ���W���w�肵�A�C���f�b�N�X���擾����
 *
 * @param	pw		���[�N
 * @param	px		X���W
 * @param	py		Y���W
 * @param	siz		�f�[�^�T�C�Y
 *
 * @return	�w����W�̃C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u8 PointerWkMovePos( const POINTER_WORK * pw, u8 px, u8 py, u8 siz )
{
	u16	i;

	for( i=0; i<siz; i++ ){
		if( pw[i].px <= px && pw[i].px+pw[i].sx > px &&
			pw[i].py <= py && pw[i].py+pw[i].sy > py ){
			break;
		}
	}
	return (u8)i;
}
