//============================================================================================
/**
 * @file	scr_kinomi.c
 * @brief
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.23
 *
 * scrcmd.c���c��オ���Ă����̂ł��̂݊֘A������Ɨ�������
 */
//============================================================================================

#include "common.h"
#include "script.h"
#include "scrcmd_def.h"
#include "scr_kinomi.h"

#include "fieldsys.h"
#include "itemtool/nuts.h"
#include "seedsys.h"

#include "system/wordset.h"
#include "savedata/record.h"

//--------------------------------------------------------------------------------------------
/**
 * @brief	���݂̂̏�Ԏ擾
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeedGetStatus(VM_MACHINE * core)
{
	FIELD_OBJ_PTR* fldobj;
	u16 * ret_wk = VMGetWork(core);
	fldobj = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TARGET_OBJ );
	*ret_wk = SeedSys_GetSeedStatus(core->fsys, *fldobj);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	���݂̂̎�ގ擾
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeedGetType(VM_MACHINE * core)
{
	FIELD_OBJ_PTR* fldobj = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TARGET_OBJ );
	u16 * ret_wk = VMGetWork(core);
	*ret_wk = SeedSys_GetSeedTypeItem(core->fsys, *fldobj);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�엿�̎�ގ擾
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeedGetCompost(VM_MACHINE * core)
{
	FIELD_OBJ_PTR* fldobj = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TARGET_OBJ );
	u16 * ret_wk = VMGetWork(core);
	*ret_wk = SeedSys_GetCompost(core->fsys, *fldobj);
	return 0;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief	�y�̏�Ԏ擾
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeedGetGroundStatus(VM_MACHINE * core)
{
	FIELD_OBJ_PTR* fldobj = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TARGET_OBJ );
	u16 * ret_wk = VMGetWork(core);
	*ret_wk = SeedSys_GetGroundStatus(core->fsys, *fldobj);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�����Ă�����̐����擾
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeedGetNutsCount(VM_MACHINE * core)
{
	FIELD_OBJ_PTR* fldobj = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TARGET_OBJ );
	u16 * ret_wk = VMGetWork(core);
	*ret_wk = SeedSys_GetSeedCount(core->fsys, *fldobj);
	return 0;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief		�엿���܂�
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeedSetCompost(VM_MACHINE * core)
{
	FIELD_OBJ_PTR* fldobj = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TARGET_OBJ );
	u16 compost_item = VMGetWorkValue(core);
	SeedSys_SetCompost(core->fsys, *fldobj, compost_item);
	return 0;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief		���݂̂�A����
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeedSetNuts(VM_MACHINE * core)
{
	FIELD_OBJ_PTR* fldobj = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TARGET_OBJ );
	RECORD * rec = SaveData_GetRecord(core->fsys->savedata);
	u16 nuts_item = VMGetWorkValue(core);
	SeedSys_SetNuts(core->fsys, *fldobj, nuts_item);
	//���݂̂�A�����񐔂��J�E���g�A�b�v
	RECORD_Inc(rec, RECID_NUTS_PLANT);
	return 0;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief		�����܂�
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeedSetWater(VM_MACHINE * core)
{
	switch (VMGetU16(core)) {
	case SEEDWATER_CMD_START:
		EventCall_SeedWater(core->fsys);
		break;
	case SEEDWATER_CMD_END:
		SeedSys_ResetPlayerForm(core->fsys);
		break;
	default:
		GF_ASSERT(0);
	}
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief		���݂̂����n
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeedTakeNuts(VM_MACHINE * core)
{
	u16 count;
	RECORD * rec = SaveData_GetRecord(core->fsys->savedata);
	FIELD_OBJ_PTR* fldobj = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TARGET_OBJ );
	SeedSys_TakeNuts(core->fsys, *fldobj);
	RECORD_Score_Add(rec, SCORE_ID_GET_NUTS);
	return 0;
}

