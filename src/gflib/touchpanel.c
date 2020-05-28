//****************************************************************************
/**
 *
 *@file		touchpanel.c
 *@brief	��`�ƃ^�b�`�p�l���V�X�e�����Ƃ̓����蔻�菈��
 *@author	taya
 *@data		2005.07.29
 *
 */
//****************************************************************************

#include "common.h"

#define __TOUCHPANEL_H_GLOBAL__
#include "gflib/touchpanel.h"


//==============================================================
// Prototype
//==============================================================
static int recthit( const RECT_HIT_TBL* pTbl, u32 x, u32 y );
static BOOL circle_hitcheck( const TP_HIT_TBL *tbl, u32 x, u32 y );
static BOOL rect_hitcheck( const TP_HIT_TBL *tbl, u32 x, u32 y );


//----------------------------------------------------------------------------
/**
 *
 *@brief	��`�̓����蔻��	
 *
 *@param	pTbl		�����蔻��e�[�u��
 *@param	u32	x		�^�b�`�p�l��x���W
 *@param	u32 y		�^�b�`�p�l��y���W
 *
 *@return	int	�q�b�g�����e�[�u���̃C���f�b�N�X�i���o�[
 *				�q�b�g����f�[�^�������Ƃ���RECT_HIT_NONE
 *
 */
//-----------------------------------------------------------------------------
static int recthit( const RECT_HIT_TBL* pTbl, u32 x, u32 y )
{
	int c;

	for(c = 0; pTbl[c].rect.top != RECT_HIT_END; c++)
	{
		if( ((u32)( x - pTbl[c].rect.left) < (u32)(pTbl[c].rect.right - pTbl[c].rect.left))
		&	((u32)( y - pTbl[c].rect.top) < (u32)(pTbl[c].rect.bottom - pTbl[c].rect.top))
		){
			return c;
		}
	}

	return RECT_HIT_NONE;
}

//------------------------------------------------------------------
/**
 * �~�`�Ƃ��Ă̓����蔻��i�P���j
 *
 * @param   tbl		�����蔻��e�[�u��
 * @param   x		X���W
 * @param   y		Y���W
 *
 * @retval  BOOL	TRUE�œ�����
 */
//------------------------------------------------------------------
static BOOL circle_hitcheck( const TP_HIT_TBL *tbl, u32 x, u32 y )
{
	x = (tbl->circle.x - x) * (tbl->circle.x - x);
	y = (tbl->circle.y - y) * (tbl->circle.y - y);

	if( x + y < (tbl->circle.r * tbl->circle.r) )
	{
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * ��`�Ƃ��Ă̓����蔻��i�P���j
 *
 * @param   tbl		�����蔻��e�[�u��
 * @param   x		�w���W
 * @param   y		�x���W
 *
 * @retval  BOOL		TRUE�œ�����
 */
//------------------------------------------------------------------
static BOOL rect_hitcheck( const TP_HIT_TBL *tbl, u32 x, u32 y )
{
	if( ((u32)( x - tbl->rect.left) < (u32)(tbl->rect.right - tbl->rect.left))
	&	((u32)( y - tbl->rect.top) < (u32)(tbl->rect.bottom - tbl->rect.top))
	){
		return TRUE;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * ��`�����蔻��i�e�[�u���g�p�A�x�^���́j
 *
 * @param   pRectTbl		�����蔻��e�[�u���i�I�[�R�[�h����j
 *
 * @retval  int		�e�[�u�����A�q�b�g�����v�f�̃C���f�b�N�X�i���o�[
 *					�q�b�g���Ȃ���� RECT_HIT_NONE
 */
//------------------------------------------------------------------
int GF_TP_RectHitCont( const RECT_HIT_TBL* pRectTbl )
{
	if( sys.tp_cont ){
		return recthit( pRectTbl, sys.tp_x, sys.tp_y );
	}
	return RECT_HIT_NONE;
}
//------------------------------------------------------------------
/**
 * ��`�����蔻��i�e�[�u���g�p�A�g���K���́j
 *
 * @param   pRectTbl		�����蔻��e�[�u���i�I�[�R�[�h����j
 *
 * @retval  int		�e�[�u�����A�q�b�g�����v�f�̃C���f�b�N�X�i���o�[
 *					�q�b�g���Ȃ���� RECT_HIT_NONE
 */
//------------------------------------------------------------------
int GF_TP_RectHitTrg( const RECT_HIT_TBL *pRectTbl )
{
	if( sys.tp_trg ){
		return recthit( pRectTbl, sys.tp_x, sys.tp_y );
	}
	return RECT_HIT_NONE;
}
//------------------------------------------------------------------
/**
 * ���^�C�v�i��`�E�~�`�j�����Ȃ��画�肷��i�x�^���́j
 *
 * @param   tbl		�����蔻��e�[�u���i�I�[�R�[�h����j
 *
 * @retval  int		�����肪����΂��̗v�f�ԍ��A�Ȃ���� TP_HIT_NONE
 */
//------------------------------------------------------------------
int GF_TP_HitCont( const TP_HIT_TBL *tbl )
{
	if( sys.tp_cont ){
		int i;

		for(i = 0; i < tbl[i].circle.code != TP_HIT_END; i++)
		{
			if( tbl[i].circle.code == TP_USE_CIRCLE )
			{
				if( circle_hitcheck( &tbl[i], sys.tp_x, sys.tp_y ) ){
					return i;
				}
			}
			else
			{
				if( rect_hitcheck( &tbl[i], sys.tp_x, sys.tp_y ) ){
					return i;
				}
			}
		}
	}
	return TP_HIT_NONE;
}
//------------------------------------------------------------------
/**
 * ���^�C�v�i��`�E�~�`�j�����Ȃ��画�肷��i�g���K���́j
 *
 * @param   tbl		�����蔻��e�[�u���i�I�[�R�[�h����j
 *
 * @retval  int		�����肪����΂��̗v�f�ԍ��A�Ȃ���� TP_HIT_NONE
 */
//------------------------------------------------------------------
int GF_TP_HitTrg( const TP_HIT_TBL *tbl )
{
	if( sys.tp_trg ){
		int i;

		for(i = 0; i < tbl[i].circle.code != TP_HIT_END; i++)
		{
			if( tbl[i].circle.code == TP_USE_CIRCLE )
			{
				if( circle_hitcheck( &tbl[i], sys.tp_x, sys.tp_y ) ){
					return i;
				}
			}
			else
			{
				if( rect_hitcheck( &tbl[i], sys.tp_x, sys.tp_y ) ){
					return i;
				}
			}
		}
	}
	return TP_HIT_NONE;
}

//------------------------------------------------------------------
/**
 * ���^�C�v�i��`�E�~�`�j�����Ȃ��画�肷��i�x�^���́j
 *
 * @param   tbl		�����蔻��e�[�u���i�P���j
 *
 * @retval  BOOL	������Ȃ�TRUE
 */
//------------------------------------------------------------------
BOOL GF_TP_SingleHitCont( const TP_HIT_TBL *tbl )
{
	if( sys.tp_cont ){
		if( tbl->circle.code == TP_USE_CIRCLE )
		{
			return circle_hitcheck( tbl, sys.tp_x, sys.tp_y );
		}
		else
		{
			return rect_hitcheck( tbl, sys.tp_x, sys.tp_y );
		}
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * ���^�C�v�i��`�E�~�`�j�����Ȃ��画�肷��i�g���K���́j
 *
 * @param   tbl		�����蔻��e�[�u���i�P���j
 *
 * @retval  BOOL	������Ȃ�TRUE
 */
//------------------------------------------------------------------
BOOL GF_TP_SingleHitTrg( const TP_HIT_TBL *tbl )
{
	if( sys.tp_trg ){
		if( tbl->circle.code == TP_USE_CIRCLE )
		{
			return circle_hitcheck( tbl, sys.tp_x, sys.tp_y );
		}
		else
		{
			return rect_hitcheck( tbl, sys.tp_x, sys.tp_y );
		}
	}
	return FALSE;
}


//------------------------------------------------------------------
/**
 * �^�b�`�p�l���ɐG��Ă��邩
 *
 * @retval  BOOL		TRUE�ŐG��Ă���
 */
//------------------------------------------------------------------
BOOL GF_TP_GetCont( void )
{
	return sys.tp_cont;
}
//------------------------------------------------------------------
/**
 * �^�b�`�p�l���ɐG��Ă��邩�i�g���K�j
 *
 * @retval  BOOL		TRUE�ŐG�ꂽ
 */
//------------------------------------------------------------------
BOOL GF_TP_GetTrg( void )
{
	return sys.tp_trg;
}

//------------------------------------------------------------------
/**
 * �^�b�`�p�l���ɐG��Ă���Ȃ炻�̍��W�擾�i�x�^���́j
 *
 * @param   x		�w���W�󂯎��ϐ��A�h���X
 * @param   y		�x���W�󂯎��ϐ��A�h���X
 *
 * @retval  BOOL	TRUE�ŐG��Ă���BFALSE���Ԃ����ꍇ�A�����ɂ͉������Ȃ��B
 */
//------------------------------------------------------------------
BOOL GF_TP_GetPointCont( u32* x, u32* y )
{
	if( sys.tp_cont )
	{
		*x = sys.tp_x;
		*y = sys.tp_y;
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * �^�b�`�p�l���ɐG��Ă���Ȃ炻�̍��W�擾�i�g���K���́j
 *
 * @param   x		�w���W�󂯎��ϐ��A�h���X
 * @param   y		�x���W�󂯎��ϐ��A�h���X
 *
 * @retval  BOOL	TRUE�ŐG��Ă���BFALSE���Ԃ����ꍇ�A�����ɂ͉������Ȃ��B
 */
//------------------------------------------------------------------
BOOL GF_TP_GetPointTrg( u32* x, u32* y )
{
	if( sys.tp_trg )
	{
		*x = sys.tp_x;
		*y = sys.tp_y;
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w�肵�����W�ŁA�����蔻����s���܂��B	����
 *
 *	@param	tbl		�����蔻��e�[�u���i�z��j
 *	@param	x		���肘���W
 *	@param	y		���肙���W
 *
 *	@retval  int		�����肪����΂��̗v�f�ԍ��A�Ȃ���� TP_HIT_NONE
 *
 *
 */
//-----------------------------------------------------------------------------
int GF_TP_HitSelf( const TP_HIT_TBL *tbl, u32 x, u32 y )
{
	int i;
	
	for(i = 0; i < tbl[i].circle.code != TP_HIT_END; i++)
	{
		if( tbl[i].circle.code == TP_USE_CIRCLE )
		{
			if( circle_hitcheck( &tbl[i], x, y ) ){
				return i;
			}
		}
		else
		{
			if( rect_hitcheck( &tbl[i], x, y ) ){
				return i;
			}
		}
	}
	return TP_HIT_NONE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����Ŏw�肵�����W�œ����蔻����s���܂��B�@�P��
 *
 *	@param	tbl		�����蔻��e�[�u���i�P���j
 *	@param	x		�����蔻�肘���W
 *	@param	y		�����蔻�肙���W
 *
 *	@retval	TURE	��������
 *	@retval	FALSE	������Ȃ�����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL GF_TP_SingleHitSelf( const TP_HIT_TBL *tbl, u32 x, u32 y )
{
	if( tbl->circle.code == TP_USE_CIRCLE )
	{
		return circle_hitcheck( tbl, x, y );
	}
	else
	{
		return rect_hitcheck( tbl, x, y );
	}

	return FALSE;
}

