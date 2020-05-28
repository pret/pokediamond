//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_pokelist_sub.h
 *	@brief		ポケモンリストサブ画面
 *	@author		tomoya takahashi
 *	@data		2006.01.20	
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_POKELIST_SUB_H__
#define __ZKN_POKELIST_SUB_H__


#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_POKELIST_SUB_H_GLOBAL
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
// ホイール
GLOBAL void ZKN_PokeListSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_PokeListSubAplDelete( ZKN_APL_DATA* p_data );
#undef	GLOBAL
#endif		// __ZKN_POKELIST_SUB_H__

