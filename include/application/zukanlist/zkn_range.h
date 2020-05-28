//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_range.h
 *	@brief		���z�}
 *	@author		tomoya takahashi	
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_RANGE_H__
#define __ZKN_RANGE_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_RANGE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	���z�^�C�v
//=====================================
enum{
	ZKN_RANGE_TYPE_MORNING,	// ��
	ZKN_RANGE_TYPE_NOON,	// ��
	ZKN_RANGE_TYPE_NIGHT,	// ��
	ZKN_RANGE_TYPE_NUM,
};


//-------------------------------------
//	�|�P�O���\���ʒu
//=====================================
#define ZKN_RANGE_POKEGRA_DRAW_X	( 40 )
#define ZKN_RANGE_POKEGRA_DRAW_Y	( 120 )


//-------------------------------------
//	�t�F�[�h���[�h
//=====================================
enum{
	ZKN_RANGE_FADE_MODE_MY,
	ZKN_RANGE_FADE_MODE_OTHER,
};


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_RangeAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_RangeAplDelete( ZKN_APL_DATA* p_data );


// ���z�^�C�v�ݒ�
GLOBAL int ZKN_RangeTypeGet( const ZKN_APL_DATA* p_data );
GLOBAL void ZKN_RangeTypeSet( ZKN_APL_DATA* p_data, int type );

// �t�F�[�h�A�E�g���̃|�P�O���ړ���
GLOBAL void ZKN_RangePokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y );
GLOBAL void ZKN_RangeFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode );
GLOBAL void ZKN_RangeFadeModeSync( ZKN_APL_DATA* p_data, int fade_sync );

#undef	GLOBAL
#endif		// __ZKN_RANGE_H__

