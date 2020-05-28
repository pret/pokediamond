//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_item_buff.h
 *	@brief		アイテム数保持バッファ
 *	@author		tomoya takahashi
 *	@data		2006.03.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_ITEM_BUFF_H__
#define __IMC_ITEM_BUFF_H__

#include "include/savedata/imageclip_data.h"

#undef GLOBAL
#ifdef	__IMC_ITEM_BUFF_H_GLOBAL
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
//	アイテム保持バッファ
//=====================================
typedef struct {
	u32 Acce[ IMC_ACCE_MAX ];	// アクセサリナンバーindex保持数
	u32 Bg[ IMC_BG_RIGHT_MAX ];	// BG見つけた順indexBGナンバー
} IMC_ITEM_BUFF;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL void IMC_ITEM_BUFF_Make( const IMC_ITEM_SAVEDATA* cp_imc_item, IMC_ITEM_BUFF* p_buff );

GLOBAL BOOL IMC_ITEM_BUFF_AcceDec( IMC_ITEM_BUFF* p_buff, u32 acce_no, int num );
GLOBAL u32 IMC_ITEM_BUFF_AcceGetNum( const IMC_ITEM_BUFF* p_buff, u32 acce_no );

u32 IMC_ITEM_BUFF_TurnBgNoGet( const IMC_ITEM_BUFF* p_buff, u32 turn );
u32 IMC_ITEM_BUFF_BgNoTurnGet( const IMC_ITEM_BUFF* p_buff, u32 bgno );

#undef	GLOBAL
#endif		// __IMC_ITEM_BUFF_H__

