//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sound.h
 *	@brief		泣き声アプリケーション
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_SOUND_H__
#define __ZKN_SOUND_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_SOUND_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
// 鳴き声画面用フェードカウント数
#define ZKN_SOUND_FADE_SYNC	( 3 )


//-------------------------------------
//	ポケグラ表示位置
//=====================================
#define ZKN_SOUND_POKEGRA_DRAW_X	( 48 )
#define ZKN_SOUND_POKEGRA_DRAW_Y	( 64 )


//-------------------------------------
//	フェードモード
//=====================================
enum{
	ZKN_SOUND_FADE_MODE_MY,
	ZKN_SOUND_FADE_MODE_OTHER,
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
GLOBAL void ZKN_SoundAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_SoundAplDelete( ZKN_APL_DATA* p_data );


// フェードアウト時のポケグラ移動先
GLOBAL void ZKN_SoundPokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y );
GLOBAL void ZKN_SoundFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode );
GLOBAL void ZKN_SoundFadeModeSync( ZKN_APL_DATA* p_data, int fade_sync );


#undef	GLOBAL
#endif		// __ZKN_SOUND_H__

