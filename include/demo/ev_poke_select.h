//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		ev_poke_select.h
 *	@brief		開始ポケモン選択処理
 *	@author		tomoya takahashi	
 *	@data		2006.03.13
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __EV_POKE_SELECT_H__
#define __EV_POKE_SELECT_H__


#include "include/system/procsys.h"
#include "include/savedata/config.h"

#undef GLOBAL
#ifdef	__EV_POKE_SELECT_H_GLOBAL
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
//	ペアレントデータワーク
//=====================================
typedef struct {
	int select_monsno;			// 選択されたポケモンﾅﾝﾊﾞｰ格納先
	const CONFIG* cp_config;
} EV_POKESELECT_PEARENT_DATA;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL PROC_RESULT EV_PokeSelect_ProcInit( PROC* proc, int* seq );
GLOBAL PROC_RESULT EV_PokeSelect_ProcMain( PROC* proc, int* seq );
GLOBAL PROC_RESULT EV_PokeSelect_ProcEnd( PROC* proc, int* seq );



#undef	GLOBAL
#endif		// __EV_POKE_SELECT_H__

