//==============================================================================
/**
 * @file	battle_particle.h
 * @brief	�퓬�p�̃p�[�e�B�N������c�[���̃w�b�_
 * @author	matsuda
 * @date	2005.07.25(��)
 */
//==============================================================================
#ifndef __BATTLE_PARTICLE_H__
#define __BATTLE_PARTICLE_H__

#include "system/particle.h"


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern PTC_PTR BattleParticle_SystemSet(int heap_id);
extern PTC_PTR CB_Particle_SystemSet(int heap_id);
extern void BattleParticle_Exit(PTC_PTR ptc);
extern void BattleParticle_Main(void);


#endif	//__BATTLE_PARTICLE_H__

