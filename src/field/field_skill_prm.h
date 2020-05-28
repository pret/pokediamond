//============================================================================================
/**
 * @file	field_skill_prm.h
 * @brief	�t�B�[���h�Z�����i��`�Z�Ȃǁj
 * @author	Nozomu Saito
 * @date	2006.05.31
 */
//============================================================================================
#ifndef __FIELD_SKILL_PRM_H__
#define __FIELD_SKILL_PRM_H__

#include "poketool/poke_tool.h"
#include "savedata/savedata.h"

typedef struct FLD_SKILL_PRM_tag
{
	POKEMON_PARAM *PokeParam;		//�|�P�����p�����|�C���^
	void *Work;						//���[�N
}FLD_SKILL_PRM;

extern FLD_SKILL_PRM *F_SkillPrm_AllocMemory(const int inHeapID, const u8 inPokePos, SAVEDATA* sv);

#endif	//__FIELD_SKILL_PRM_H__

