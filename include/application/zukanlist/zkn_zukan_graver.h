//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_graver.h
 *	@brief		図鑑グラフィックバージョン
 *	@author		tomoya takahashi
 *	@data		2006.02.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_ZUKAN_GRAVER_H__
#define __ZKN_ZUKAN_GRAVER_H__

#undef GLOBAL
#ifdef	__ZKN_ZUKAN_GRAVER_H_GLOBAL
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
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_ZukanGraverAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_ZukanGraverAplDelete( ZKN_APL_DATA* p_data );


// 描画タイプを変更する
GLOBAL BOOL ZKN_ZukanGraverDrawTypeAdd( ZKN_APL_DATA* p_data, int num );

#undef	GLOBAL
#endif		// __ZKN_ZUKAN_GRAVER_H__

