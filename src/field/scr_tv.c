//============================================================================================
/**
 * @file	scr_tv.c
 * @brief	�X�N���v�g�R�}���h�F�e���r�֘A
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.22
 */
//============================================================================================

#include "common.h"
#include "script.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "field_subproc.h"

#include "tv.h"
#include "tv_topic.h"
#include "field/tvtopic_extern.h"
#include "scrcmd_def.h"

#include "savedata/mystatus.h"
#include "savedata/randomgroup.h"
#include "savedata/imageclip_data.h"
#include "savedata/record.h"

#include "ev_pokemon.h"

#include "msgdata\msg.naix"			//NARC_msg_??_dat
#include "msgdata\msg_tv_interview.h"

#include "tv_define.h"

//============================================================================================
//============================================================================================
#include "scr_tv.h"

//============================================================================================
//
//
//		�X�N���v�g�R�}���h�F�e���r��������
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�e���r��������
 */
//-----------------------------------------------------------------------------
BOOL EvCmdBroadcastTV(VM_MACHINE * core)
{

	switch (VMGetU16(core)) {

	case TV_CMD_GET_STATUS:				//��Ԏ擾
		{
			u16 * ret_wk = VMGetWork(core);
			*ret_wk = TV_GetBroadcastStatus(core->fsys);
		}
		break;

	case TV_CMD_GET_PROG_MSG:			//���܂蕶��̃Z�b�g
		{
			u16 id = VMGetU16(core);
			u16 * arc_id = VMGetWork(core);
			u16 * msg_id = VMGetWork(core);
			*arc_id = NARC_msg_tv_program_dat;
			*msg_id = TV_GetProgramMsg(core->fsys, id);

		}
		break;
	case TV_CMD_GET_MSG:				//���b�Z�[�W�f�[�^����
		{
			WORDSET** wordset = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
			u16 idx = VMGetWorkValue(core);
			u16 * arc_id = VMGetWork(core);
			u16 * msg_id = VMGetWork(core);
			TV_GetProgramID(core->fsys, *wordset, idx, arc_id, msg_id);
		}
		break;

	case TV_CMD_SET_END_FLAG:			//�I���t���O�Z�b�g
		TV_SetEndFlag(core->fsys);
		break;

	case TV_CMD_GET_CM_MSG:				//�R�}�[�V�������b�Z�[�W�擾
		{
			u16 * arc_id = VMGetWork(core);
			u16 * msg_id = VMGetWork(core);
			*arc_id = NARC_msg_tvcm_dat;
			*msg_id = TVCM_ChooseID(core->fsys);
		}
		break;
	case TV_CMD_GET_DATA:				//�w��f�[�^�擾
		{
			u16 mine = VMGetWorkValue(core);
			u16 see = VMGetWorkValue(core);
			u16 * ret_wk = VMGetWork(core);
			*ret_wk = TV_ChooseBroadcastTopic(core->fsys, mine, see);
		}
		break;
	case TV_CMD_GET_DATA_TOTAL:			//�w��f�[�^�擾�i�S�p�^�[���j
		{
			u16 * ret_wk = VMGetWork(core);
			*ret_wk = TV_ChooseBroadcastTopicTotal(core->fsys);
		}
		break;
	}

	return 0;
}

//============================================================================================
//
//
//		�X�N���v�g�R�}���h�F�g�s�b�N����
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�B���A�C�e�������I
 */
//-----------------------------------------------------------------------------
BOOL EvCmdTVEntryWatchHideItem(VM_MACHINE * core)
{
	TVTOPIC_Entry_Watch_HideItem( core->fsys, VMGetWorkValue(core) );
	return 0;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�������f
 */
//-----------------------------------------------------------------------------
BOOL EvCmdTVEntryWatchChangeName(VM_MACHINE * core)
{
	POKEPARTY * party = SaveData_GetTemotiPokemon(core->fsys->savedata);
	POKEMON_PARAM * pp = PokeParty_GetMemberPointer(party, VMGetWorkValue(core));
	TVTOPIC_Entry_Watch_ChangeName(core->fsys, pp);
	return 0;
}

//============================================================================================
//
//
//		�X�N���v�g�R�}���h�F�e���r�C���^�r���[
//
//
//============================================================================================
static int GetInterviewMsg(int id, FIELDSYS_WORK * fsys, WORDSET * ws);
static void EntryInterviewTopic(FIELDSYS_WORK * fsys, int id, u16 ans1, u16 ans2);
static BOOL CheckInterviewReady(FIELDSYS_WORK * fsys, int id);

typedef void (*INTERVIEW_ENTRY_FUNC)(FIELDSYS_WORK * fsys, PMS_WORD word);
typedef void (*INTERVIEW_MSG_FUNC)(FIELDSYS_WORK * fsys, WORDSET * ws);
typedef BOOL (*INTERVIEW_CHECK_FUNC)(FIELDSYS_WORK * fsys);
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
typedef struct {
	INTERVIEW_ENTRY_FUNC entry_func;
	INTERVIEW_MSG_FUNC msg_func;
	INTERVIEW_CHECK_FUNC check_func;
	u32 msg_id;
}QANDA_DATA;

static const QANDA_DATA QandAData[TVTOPIC_INTERVIEW_TYPE_MAX - 1];
//-----------------------------------------------------------------------------
/**
 * @brief	�e���r�F�C���^�r���[����
 */
//-----------------------------------------------------------------------------
BOOL EvCmdTVInterview(VM_MACHINE * core)
{
	WORDSET ** wordset;
	wordset = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	switch (VMGetU16(core)) {
	case TV_INTERVIEW_CMD_GET_MSG:
		{
			int id;
			u16 * arc_id;
			u16 * msg_id;

			id = VMGetWorkValue(core);
			arc_id = VMGetWork(core);
			msg_id = VMGetWork(core);
			*arc_id = NARC_msg_tv_interview_dat;
			*msg_id = GetInterviewMsg(id, core->fsys, *wordset);
		}
		break;
	case TV_INTERVIEW_CMD_SET_TOPIC:
		{
			u16 id;
			u16 ans_wk1, ans_wk2;
			RECORD * rec = SaveData_GetRecord(core->fsys->savedata);
			id = VMGetWorkValue(core);
			ans_wk1 = VMGetWorkValue(core);
			ans_wk2 = VMGetWorkValue(core);
			EntryInterviewTopic(core->fsys, id, ans_wk1, ans_wk2);
			RECORD_Score_Add(rec, SCORE_ID_INTERVIEW);
		}
		break;
	}

	return 0;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�e���r�F�C���^�r���[�\���ǂ����̃`�F�b�N
 */
//-----------------------------------------------------------------------------
BOOL EvCmdTVInterviewerCheck(VM_MACHINE * core)
{
	u16 id;
	u16 * ret_wk;
	id = VMGetWorkValue(core);
	ret_wk = VMGetWork(core);
	*ret_wk = CheckInterviewReady(core->fsys, id);
	return 0;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�e���r�F�A����������p�f�[�^�o�^
 */
//-----------------------------------------------------------------------------
BOOL EvCmdTVEntryParkInfo(VM_MACHINE * core)
{
	TV_WORK * tvwk = SaveData_GetTvWork(core->fsys->savedata);

	switch (VMGetU16(core)) {
	case TV_ENTRYPARK_CMD_INIT:
		{
			POKEPARTY * party = SaveData_GetTemotiPokemon(core->fsys->savedata);
			POKEMON_PARAM * pp = PokeParty_GetMemberPointer(party, VMGetWorkValue(core));
			TVTOPIC_ParkTemp_Init(tvwk, pp, HEAPID_FIELD);
		}
		break;
	case TV_ENTRYPARK_CMD_ITEM:
		TVTOPIC_ParkTemp_SetKinomi(tvwk, VMGetWorkValue(core));
		break;
	case TV_ENTRYPARK_CMD_ACCE:
		TVTOPIC_ParkTemp_SetAccessories(tvwk, VMGetWorkValue(core));
		break;
	}
	return 0;
}


//============================================================================================
//============================================================================================

//--------------------------------------------------------------------
/**
 * @brief	����^�g�s�b�N���������̌Ăяo��
 * @param	id		�g�s�b�N�w��ID
 * @param	ans1	����̓����iPMS_WORD of u16)
 * @param	ans2	����A���݂͎g�p���Ă��Ȃ�
 */
//--------------------------------------------------------------------
static void EntryInterviewTopic(FIELDSYS_WORK * fsys, int id, u16 ans1, u16 ans2)
{
	INTERVIEW_ENTRY_FUNC func;
	func = QandAData[id - 1].entry_func;
	if (func != NULL) {
		func(fsys, ans1);
	}
}

//--------------------------------------------------------------------
/**
 * @brief	�C���^�r���[�J�n���b�Z�[�W�̐���
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	ws		WORDSET�ւ̃|�C���^
 * @return	int		MSG��ID
 *
 * ���b�Z�[�WID�ɂ���ẮA�����������̒P��⊮���s��
 */
//--------------------------------------------------------------------
static int GetInterviewMsg(int id, FIELDSYS_WORK * fsys, WORDSET * ws)
{
	INTERVIEW_MSG_FUNC func;
	func = QandAData[id - 1].msg_func;
	if (func != NULL) {
		func (fsys, ws);
	}
	return QandAData[id - 1].msg_id;
	//return msg_tv_interview_01 + id - 1;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL CheckInterviewReady(FIELDSYS_WORK * fsys, int id)
{
	INTERVIEW_CHECK_FUNC func;
	TV_WORK *tvwk = SaveData_GetTvWork(fsys->savedata);

	if (TVWORK_EnableMakeTopic(tvwk, TVTOPICTYPE_INTERVIEW, id) == FALSE) {
		//�g�s�b�N�����Ԃ��Ă��č쐬�ł��Ȃ��ꍇ
		return FALSE;
	}
	func = QandAData[id - 1].check_func;
	if (func == NULL) {
		//�`�F�b�N�֐����Ȃ��ꍇ�A��������OK
		return TRUE;
	}
	return func(fsys);
}

//============================================================================================
//
//
//
//============================================================================================


#include "gflib/strbuf_family.h"
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void WORDSET_RegisterSTRCODE(WORDSET * ws, int buf_id,
		const STRCODE * str, int sex, int region, int single)
{
	STRBUF * strbuf = STRBUF_Create(64, HEAPID_FIELD);
	STRBUF_SetStringCode(strbuf, str);
	WORDSET_RegisterWord(ws, buf_id, strbuf, sex, single, region);
	STRBUF_Delete(strbuf);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Interview04(FIELDSYS_WORK * fsys, WORDSET * ws)
{
	POKEPARTY * party = SaveData_GetTemotiPokemon(fsys->savedata);
	POKEMON_PARAM * pp = EvPoke_GetPokemonTop(party);
	WORDSET_RegisterPokeMonsName(ws, 0, PPPPointerGet(pp));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Interview06(FIELDSYS_WORK * fsys, WORDSET * ws)
{
	int id;
	id = Poketch_GetRunningApplication(fsys->fldmap->poketch);
	WORDSET_RegisterPoketchAppName(ws, 0, id);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Interview13(FIELDSYS_WORK * fsys, WORDSET * ws)
{
	STRCODE monsname[MONS_NAME_SIZE + EOM_SIZE];
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	TOPICTEMP_PARK * ptemp = TVWORK_GetParkTemp(tvwk);
	MSGDAT_MonsNameGet(ptemp->monsno, HEAPID_FIELD, monsname);
	WORDSET_RegisterSTRCODE(ws, 0, monsname, PM_MALE, PM_LANG, TRUE);
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL InterviewCheck02(FIELDSYS_WORK * fsys)
{
	TOPICTEMP_BTOWER * bt = TVWORK_GetBTowerTemp(SaveData_GetTvWork(fsys->savedata));
	return bt->exist_flag;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL InterviewCheck06(FIELDSYS_WORK * fsys)
{
	POKETCH_DATA* poketch_data = SaveData_GetPoketchData( fsys->savedata );
	return PoketchData_GetPoketchGetFlag( poketch_data );

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL InterviewCheck07(FIELDSYS_WORK * fsys)
{
	TOPICTEMP_CONTEST * ct = TVWORK_GetContestTemp(SaveData_GetTvWork(fsys->savedata));
	return ct->exist_flag;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL InterviewCheck09(FIELDSYS_WORK * fsys)
{
	IMC_SAVEDATA* iw = SaveData_GetImcSaveData(fsys->savedata);
	return ImcSaveData_CheckTelevisionSaveData(iw, 0);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL InterviewCheck11(FIELDSYS_WORK * fsys)
{
	TOPICTEMP_PORUTO * poruto = TVWORK_GetPorutoTemp(SaveData_GetTvWork(fsys->savedata));
	return poruto->exist_flag;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL InterviewCheck13(FIELDSYS_WORK * fsys)
{
	TOPICTEMP_PARK * park = TVWORK_GetParkTemp(SaveData_GetTvWork(fsys->savedata));
	return park->exist_flag;
}




//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static const QANDA_DATA QandAData[TVTOPIC_INTERVIEW_TYPE_MAX - 1] = {
	{//TVTOPIC_INTERVIEW_GYM_BADGE = 1,///<�W�����e�I	1	�W���̂���V�e�B	�W�����[�_�[��|��������
		NULL,
		NULL,
		NULL,
		msg_tv_interview_01,
	},
	{//TVTOPIC_INTERVIEW_BTOWER,		///<����I�o�g���^���[	1	�o�g���^���[	����I����
		TVTOPIC_Entry_QandA_BTower,
		NULL,
		InterviewCheck02,
		msg_tv_interview_02,
	},
	{//TVTOPIC_INTERVIEW_BFACTORY,		///<����I�t�@�N�g���[	1	�o�g���t�@�N�g���[	����I����
		NULL,
		NULL,
		NULL,
		msg_tv_interview_03,
	},
	{//TVTOPIC_INTERVIEW_POKEMON,		///<���Ȃ��̃|�P����	1	�|�P������D���N���u	
		TVTOPIC_Entry_QandA_Pokemon,
		Interview04,
		NULL,
		msg_tv_interview_04,
	},
	{//TVTOPIC_INTERVIEW_ITEM,			///<�������߂̂ǂ����I	2	�t�����h���B�V���b�v	
		NULL,
		NULL,
		NULL,
		msg_tv_interview_05,
	},
	{//TVTOPIC_INTERVIEW_POKETCH,		///<���C�ɓ���̃|�P�b�`	2	�J���p�j�[	
		TVTOPIC_Entry_QandA_Poketch,
		Interview06,
		InterviewCheck06,
		msg_tv_interview_06,
	},
	{//TVTOPIC_INTERVIEW_CONTEST,		///<����I�R���e�X�g		�R���e�X�g���	�R���e�X�g�I����
		TVTOPIC_Entry_QandA_Contest,
		NULL,
		InterviewCheck07,
		msg_tv_interview_07,
	},
	{//TVTOPIC_INTERVIEW_TATOE,		///<�|�P�����ɗႦ����H	2	��D���N���u	
		NULL,
		NULL,
		NULL,
		msg_tv_interview_08,
	},
	{//TVTOPIC_INTERVIEW_CLIP,			///<�|�P�����N���b�v�I	2	�N���b�v�����ꏊ	�N���b�v�����������
		TVTOPIC_Entry_QandA_Clip,
		NULL,
		InterviewCheck09,
		msg_tv_interview_09,
	},
	{//TVTOPIC_INTERVIEW_CHARACTOR,	///<���i�f�f�I	2		
		TVTOPIC_Entry_QandA_Character,
		NULL,
		NULL,
		msg_tv_interview_10,
	},
	{//TVTOPIC_INTERVIEW_PORUTO,		///<�|���g����		�|���g�����ꏊ	�|���g���������
		TVTOPIC_Entry_QandA_Poruto,
		NULL,
		InterviewCheck11,
		msg_tv_interview_11,
	},
	{//TVTOPIC_INTERVIEW_KOUKAN,		///<���������|�P����	1		
		NULL,
		NULL,
		NULL,
		msg_tv_interview_12,
	},
	{//TVTOPIC_INTERVIEW_TUREARUKI,	///<�A������𖞋i�I		���R�����Q�[�g	�A�������
		TVTOPIC_Entry_QandA_Park,
		Interview13,
		InterviewCheck13,
		msg_tv_interview_13,
	},
};

