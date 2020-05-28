//==============================================================================
/**
 * @file	d_we.h
 * @brief	�f�o�b�O�p�Z�G�t�F�N�g
 * @author	goto
 * @date	2005.08.08(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
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
//	�f�o�b�O�Ăяo��
//
// -----------------------------------------
extern BOOL	DebugWazaEffectInit(int heap, BATTLE_WORK* bw, TCB_PTR tcb, TCB_FUNC func);

// -----------------------------------------
//
//	�f�o�b�O�I��
//
// -----------------------------------------
extern void DebugWazaEffectDelete(void);

#endif