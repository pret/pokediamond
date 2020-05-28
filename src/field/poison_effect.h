//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		poison_effect.h
 *	@brief		�Ŵ̪��
 *	@author		tomoya takahashi
 *	@data		2006.04.10
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __POISON_EFFECT_H__
#define __POISON_EFFECT_H__

#include "field_hblank.h"

#undef GLOBAL
#ifdef	__POISON_EFFECT_H_GLOBAL
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
//	�Ŵ̪�ď��
//=====================================
enum {
	POISON_EFFE_STANDBY,
	POISON_EFFE_DO,
} ;

// TCB�D�揇��
#define POISON_TCB_PRI	(1024)

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	���[�N	
//=====================================
typedef struct _POISON_EFFECT_WORK POISON_EFFECT_WORK;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL POISON_EFFECT_WORK* POISON_EFFE_Init( u32 heap, FIELD_HBLANK_SYS* p_sys );
GLOBAL void POISON_EFFE_Delete( POISON_EFFECT_WORK* p_poison );
GLOBAL void POISON_EFFE_Start( POISON_EFFECT_WORK* p_poison );
GLOBAL u32 POISON_EFFE_GetStatus( const POISON_EFFECT_WORK* cp_poison );

#undef	GLOBAL
#endif		// __POISON_EFFECT_H__

