//==============================================================================
/**
 * @file	battle_particle.h
 * @brief	戦闘用のパーティクル制御ツールのヘッダ
 * @author	matsuda
 * @date	2005.07.25(月)
 */
//==============================================================================
#ifndef __BATTLE_PARTICLE_H__
#define __BATTLE_PARTICLE_H__

#include "system/particle.h"


//==============================================================================
//	外部関数宣言
//==============================================================================
extern PTC_PTR BattleParticle_SystemSet(int heap_id);
extern PTC_PTR CB_Particle_SystemSet(int heap_id);
extern void BattleParticle_Exit(PTC_PTR ptc);
extern void BattleParticle_Main(void);


#endif	//__BATTLE_PARTICLE_H__

