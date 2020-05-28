//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		fld_motion_bl.h
 *@brief	フィールド専門モーションブラー
 *@author	tomoya takahashi
 *@data		2005.07.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FLD_MOTION_BL_H__
#define __FLD_MOTION_BL_H__

#include "motion_bl.h"

#undef GLOBAL
#ifdef	__FLD_MOTION_BL_H_GLOBAL
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
typedef struct _FLD_MOTION_BL_DATA* FLD_MOTION_BL_DATA_PTR;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL FLD_MOTION_BL_DATA_PTR FLDMotionBl_Init(int eva, int evb);	// モーションブラーを使用する準備をする
GLOBAL void FLDMotionBl_Delete(FLD_MOTION_BL_DATA_PTR* data);		// モーションブラーを使用する準備をする
GLOBAL void FLDMotionBl_ParamChg(FLD_MOTION_BL_DATA_PTR data, int eva, int evb); // パラメーターChange

#undef	GLOBAL
#endif		// __FLD_MOTION_BL_H__

