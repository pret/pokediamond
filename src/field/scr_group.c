//============================================================================================
/**
 * @file	scr_group.c
 * @brief	スクリプトコマンド：ランダムグループ関連
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.22
 */
//
//============================================================================================

#include "common.h"
#include "script.h"
#include "fieldsys.h"
#include "field_subproc.h"

#include "scrcmd_def.h"
#include "scr_group.h"
#include "strbuf_family.h"

#include "savedata/mystatus.h"
#include "savedata/randomgroup.h"
#include "application/namein.h"			//NAMEIN_RANDOMGROUP
#include "tv_topic.h"

//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	ランダムグループ用共通コマンド
 */
//-----------------------------------------------------------------------------
BOOL EvCmdRandomGroup(VM_MACHINE * core)
{
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	RANDOM_GROUP * rg = SaveData_GetRandomGroup(core->fsys->savedata);
	SAVEDATA * sv = core->fsys->savedata;

	switch (VMGetU16(core)) {
	case GROUP_COMMAND_EXIST_CHECK:
		{
			u16 gid;
			u16 * ret_wk;
			gid = VMGetWorkValue(core);
			ret_wk = VMGetWork(core);
			*ret_wk = RandomGroup_ExistCheck(rg, gid);
			return 0;
		}
		break;
	case GROUP_COMMAND_ENTRY_CHECK:
		{
			u16 gid;
			u16 * ret_wk;
			gid = VMGetWorkValue(core);
			ret_wk = VMGetWork(core);
			*ret_wk = RandomGroup_EntryCheck(rg, gid);
			return 0;
		}
		break;
	case GROUP_COMMAND_GET_GROUP_NAME:
		{
			u16 gid, idx;
			gid = VMGetWorkValue(core);
			idx = VMGetWorkValue(core);
			WORDSET_RegisterGroupName(*wordset, sv, gid, idx, RANDOMGROUP_NAME_GROUP);
		}
		break;
	case GROUP_COMMAND_GET_LEADER_NAME:
		{
			u16 gid, idx;
			gid = VMGetWorkValue(core);
			idx = VMGetWorkValue(core);
			WORDSET_RegisterGroupName(*wordset, sv, gid, idx, RANDOMGROUP_NAME_LEADER);
		}
		break;

	case GROUP_COMMAND_NAMEIN:
		{
			const STRCODE *org;
			org = RandomGroup_GetNamePtr(rg, RANDOMGROUP_MINE, RANDOMGROUP_NAME_GROUP);
			EventCmd_NameIn(core->event_work, NAMEIN_RANDOMGROUP, 0, 
					NAMEIN_GROUP_LENGTH, 0, org, VMGetWork(core));
		}
		return 1;

	case GROUP_COMMAND_ENTRY:
		{
			u16 select = VMGetWorkValue(core);
			BOOL entry = RandomGroup_ExistCheck(rg, RANDOMGROUP_MYUSE);

			RandomGroup_Copy(rg, select, RANDOMGROUP_MYUSE);
			if (entry) {
				//すでにグループに所属している場合のみ、トピックを生成する
				TVTOPIC_Entry_Watch_ChangeGroup(core->fsys);
			}
		}
		return 0;

	case GROUP_COMMAND_MAKEGROUP:
		{
			STRBUF * strbuf = STRBUF_Create(64, HEAPID_EVENT);
			MYSTATUS * my = SaveData_GetMyStatus(core->fsys->savedata);

			//グループ生成処理・グループ名のみ、EventCmd_NameIn内でセットされている
			MyStatus_CopyNameString(my, strbuf);
			RandomGroup_SetName(rg, RANDOMGROUP_MINE, RANDOMGROUP_NAME_LEADER, strbuf);
			RandomGroup_SetSex(rg, RANDOMGROUP_MINE, MyStatus_GetMySex(my));
			RandomGroup_SetRegionCode(rg, RANDOMGROUP_MINE, PM_LANG);
			RandomGroup_SetRandomSeed(rg, RANDOMGROUP_MINE, gf_mtRand());
			STRBUF_Delete(strbuf);
			RandomGroup_Copy(rg, RANDOMGROUP_MINE, RANDOMGROUP_MYUSE);
			TVTOPIC_Entry_Watch_MakeGroup(core->fsys);
		}
		break;

	}
	return 0;
}


