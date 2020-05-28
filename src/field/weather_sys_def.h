//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		weather_sys_def.h
 *@brief	お天気システム構造体の宣言
 *@author	tomoya takahashi
 *@data		2005.07.29
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __WEATHER_SYS_DEF_H__
#define __WEATHER_SYS_DEF_H__

#undef GLOBAL
#ifdef	__WEATHER_SYS_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
// 各天気の制御
typedef struct _WEATHER_SYS_CONTROL* WEATHER_CONT_PTR;		// 天気制御データポインタ

// 今実行中の天気　次の天気へのフェード処理を管理
typedef struct _WEATHER_MANAGER* WEATHER_MANAGER_PTR;		// 天気システム制御マネージャ

#undef	GLOBAL
#endif		// __WEATHER_SYS_DEF_H__

