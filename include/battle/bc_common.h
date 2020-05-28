//==============================================================================
/**
 * @file	bc_common.h
 * @brief	戦闘・コンテスト共通で使用されるソースのヘッダ
 * @author	matsuda
 * @date	2006.05.26(金)
 */
//==============================================================================
#ifndef __BC_COMMON_H__
#define __BC_COMMON_H__


#include "wazaeffect/we_mana.h"


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void	HenshinChrSet(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id);
extern void	YokodoriChrSet(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id);
extern void	HenshinChrPop(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id);
extern void	MigawariChrSet(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id);

//==============================================================================
//	外部データ宣言
//==============================================================================
extern const	s16	EncountPosTable[][3];
extern const	s16	AppearPosTable[][2];
extern const	s16	SlideInPosTable[][3];


#endif	//__BC_COMMON_H__

