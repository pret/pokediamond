//============================================================================================
/**
 * @file	field_skill_prm.c
 * @brief	�t�B�[���h�Z�����i��`�Z�Ȃǁj
 * @author	Nozomu Saito
 * @date	2006.05.31
 */
//============================================================================================
#include "common.h"
#include "savedata/savedata.h"
#include "field_skill_prm.h"
#include "poketool/pokeparty.h"

//--------------------------------------------------------------------------------------------
/**
 * @brief	�Z�g�p���ʍ\���̂̃������m��
 *
 * @param	inHeapID		�q�[�v�h�c
 *
 * @retval	FLD_SKILL_PRM *		�m�ۂ����������̃|�C���^
 */
//--------------------------------------------------------------------------------------------
FLD_SKILL_PRM *F_SkillPrm_AllocMemory(const int inHeapID, const u8 inPokePos, SAVEDATA* sv)
{
	FLD_SKILL_PRM *param;
	param = sys_AllocMemoryLo(inHeapID, sizeof(FLD_SKILL_PRM));
	param->PokeParam =  PokeParty_GetMemberPointer(
	SaveData_GetTemotiPokemon(sv), inPokePos );
	param->Work = NULL;

	return param;
}
