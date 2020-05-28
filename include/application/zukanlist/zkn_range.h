//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_range.h
 *	@brief		分布図
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
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	分布タイプ
//=====================================
enum{
	ZKN_RANGE_TYPE_MORNING,	// 朝
	ZKN_RANGE_TYPE_NOON,	// 昼
	ZKN_RANGE_TYPE_NIGHT,	// 夜
	ZKN_RANGE_TYPE_NUM,
};


//-------------------------------------
//	ポケグラ表示位置
//=====================================
#define ZKN_RANGE_POKEGRA_DRAW_X	( 40 )
#define ZKN_RANGE_POKEGRA_DRAW_Y	( 120 )


//-------------------------------------
//	フェードモード
//=====================================
enum{
	ZKN_RANGE_FADE_MODE_MY,
	ZKN_RANGE_FADE_MODE_OTHER,
};


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
GLOBAL void ZKN_RangeAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_RangeAplDelete( ZKN_APL_DATA* p_data );


// 分布タイプ設定
GLOBAL int ZKN_RangeTypeGet( const ZKN_APL_DATA* p_data );
GLOBAL void ZKN_RangeTypeSet( ZKN_APL_DATA* p_data, int type );

// フェードアウト時のポケグラ移動先
GLOBAL void ZKN_RangePokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y );
GLOBAL void ZKN_RangeFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode );
GLOBAL void ZKN_RangeFadeModeSync( ZKN_APL_DATA* p_data, int fade_sync );

#undef	GLOBAL
#endif		// __ZKN_RANGE_H__

