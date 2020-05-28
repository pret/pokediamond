//==============================================================================
/**
 * @file	d_we.h
 * @brief	デバッグ用技エフェクト
 * @author	goto
 * @date	2005.08.08(月)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#ifndef	_D_WE_H_
#define _D_WE_H_

#include "battle/battle_common.h"
#include "battle/fight_tool.h"

typedef struct _TDWE_SYS * DWE_SYS_PTR;

// -----------------------------------------
//
//	デバッグ呼び出し
//
// -----------------------------------------
extern BOOL	DebugWazaEffectInit(int heap, BATTLE_WORK* bw, TCB_PTR tcb, TCB_FUNC func);

// -----------------------------------------
//
//	デバッグ終了
//
// -----------------------------------------
extern void DebugWazaEffectDelete(void);

#endif