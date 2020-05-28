//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_big_sub.h
 *	@brief		おおきさくらべアプリケーション
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_BIG_SUB_H__
#define __ZKN_BIG_SUB_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_BIG_SUB_H_GLOBAL
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
GLOBAL void ZKN_BigSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_BigSubAplDelete( ZKN_APL_DATA* p_data );


//-------------------------------------
//	メイン画面アプリケーションデータ
//=====================================
enum{
	ZKN_BIGSUB_CONTROL_HEIGHT,
	ZKN_BIGSUB_CONTROL_GRAM,
	ZKN_BIGSUB_CONTROL_NUM,
};
GLOBAL int ZKN_BigSubNowAplTypeGet( ZKN_APL_DATA* p_data );

#undef	GLOBAL
#endif		// __ZKN_BIG_SUB_H__

