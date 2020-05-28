//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		fieldobj_draw_legendpoke.h
 *	@brief		�`���|�P�����`��֌W
 *	@author		tomoya takahashi
 *	@data		2006.04.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FIELDOBJ_DRAW_LEGENDPOKE_H__
#define __FIELDOBJ_DRAW_LEGENDPOKE_H__

#include "fieldobj.h"

#undef GLOBAL
#ifdef	__FIELDOBJ_DRAW_LEGENDPOKE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	LEGENDPOKE_WORK�\����
//=====================================
typedef struct _LEGENDPOKE_WORK LEGENDPOKE_WORK;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL LEGENDPOKE_WORK* FieldOBJ_DrawLegend_GetWrokPtr( FIELD_OBJ_PTR fldobj );
GLOBAL BLACT_WORK_PTR FieldOBJ_DrawLegend_GetBlActWorkPtr( FIELD_OBJ_PTR fldobj );
GLOBAL BLACT_WORK_PTR FieldOBJ_DrawLegend_GetBlactPtr( LEGENDPOKE_WORK* p_obj );

GLOBAL void FieldOBJ_DrawLegend_SetDrawOfs( LEGENDPOKE_WORK* p_obj, VecFx32* p_mat );

#undef	GLOBAL
#endif		// __FIELDOBJ_DRAW_LEGENDPOKE_H__

