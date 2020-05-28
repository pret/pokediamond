//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		fieldobj_draw_legendpoke.h
 *	@brief		伝説ポケモン描画関係
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
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	LEGENDPOKE_WORK構造体
//=====================================
typedef struct _LEGENDPOKE_WORK LEGENDPOKE_WORK;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL LEGENDPOKE_WORK* FieldOBJ_DrawLegend_GetWrokPtr( FIELD_OBJ_PTR fldobj );
GLOBAL BLACT_WORK_PTR FieldOBJ_DrawLegend_GetBlActWorkPtr( FIELD_OBJ_PTR fldobj );
GLOBAL BLACT_WORK_PTR FieldOBJ_DrawLegend_GetBlactPtr( LEGENDPOKE_WORK* p_obj );

GLOBAL void FieldOBJ_DrawLegend_SetDrawOfs( LEGENDPOKE_WORK* p_obj, VecFx32* p_mat );

#undef	GLOBAL
#endif		// __FIELDOBJ_DRAW_LEGENDPOKE_H__

