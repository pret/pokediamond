//============================================================================================
/**
 * @file	field_skill_prm.c
 * @brief	フィールド技処理（秘伝技など）
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
 * @brief	技使用共通構造体のメモリ確保
 *
 * @param	inHeapID		ヒープＩＤ
 *
 * @retval	FLD_SKILL_PRM *		確保したメモリのポインタ
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
