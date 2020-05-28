//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_acce_hand.h
 *	@brief		イメージクリップ アクセサリハンド システム	
 *	@author		tomoya takahashi
 *	@data		2005.09.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_ACCE_HAND_H__
#define __IMC_ACCE_HAND_H__

#include <nnsys.h>
#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_hand.h"
#include "include/application/imageClip/imc_right_box.h"
#include "include/application/imageClip/imc_left_box.h"
#include "include/application/imageClip/imc_drawsys.h"
#include "include/application/imageClip/imc_subwin.h"

#undef GLOBAL
#ifdef	__IMC_ACCE_HAND_H_GLOBAL
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
//	
//	元いた場所定数
//	
//=====================================
enum{
	IMC_ACCE_HAND_FROM_LBOX,		// 左ボックス
	IMC_ACCE_HAND_FROM_RBOX,		// 右ボックス
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
//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリハンド作成
 *
 *	@param	hand		ハンド構造体
 *	@param	rbox		右ボックス構造体
 *	@param	lbox		左ボックス構造体
 *	@param	drawData	描画データ構造体
 *	@param	subwin		サブウィンドウ構造体
 *	@param	poketouch	ポケモンにふれるかどうか
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_HAND_Init( IMC_HAND* hand, IMC_RIGHT_BOX* rbox, IMC_LEFT_BOX* lbox, IMC_DRAW_DATA* drawData, IMC_SUBWIN* subwin, BOOL poketouch );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリハンド破棄
 *
 *	@param	hand	ハンド構造体
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_HAND_Delete( IMC_HAND* hand );

#undef	GLOBAL
#endif		// __IMC_ACCE_HAND_H__

