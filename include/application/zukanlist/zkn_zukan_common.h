//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_common.h
 *	@brief		図鑑共通アプリケーション
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_ZUKAN_COMMON_H__
#define __ZKN_ZUKAN_COMMON_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_ZUKAN_COMMON_H_GLOBAL
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

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_ZukanCommonAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_ZukanCommonAplDelete( ZKN_APL_DATA* p_data );

GLOBAL void ZKN_ZukanCommonSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_ZukanCommonSubAplDelete( ZKN_APL_DATA* p_data );


GLOBAL BOOL ZKN_ZukanCommonBrightnessOnFlagGet( const ZKN_APL_DATA* cp_glb );

GLOBAL BOOL ZKN_ZukanCommonSubBrightnessOnFlagGet( const ZKN_APL_DATA* cp_glb );
GLOBAL BOOL ZKN_ZukanCommonSubMoveFlagGet( const ZKN_APL_DATA* cp_glb );

// カーソル操作有効無効
GLOBAL BOOL ZKN_ZukanCommonSubCursorFlagGet( const ZKN_APL_DATA* cp_glb );

#undef	GLOBAL
#endif		// __ZKN_ZUKAN_COMMON_H__

