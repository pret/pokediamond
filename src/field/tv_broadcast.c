//============================================================================================
/**
 * @file	tv_broadcast.c
 * @brief
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.17
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"

#include "savedata/tv_work.h"
#include "tv_define.h"


#include "system/pm_rtc.h"
#include "ev_time.h"

#include "tv.h"
#include "scr_tv.h"

#include "msgdata/msg.naix"

#include "system/pm_rtc.h"

#include "system/arc_tool.h"
#include "../arc/tv.naix"

#include "msgdata/msg_tv_program.h"
#include "msgdata/msg_tvcm.h"
#include "msgdata/msg_tv_interview.h"
#include "msgdata/msg_msg_tv_01.h"
#include "msgdata/msg_msg_tv_02.h"
#include "msgdata/msg_msg_tv_03.h"
#include "msgdata/msg_msg_tv_04.h"

#include "system/debug_flag.h"

#ifdef	PM_DEBUG
#define	TV_BROADCAST_DEBUG
#endif
//============================================================================================
//
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�P�ԑg�ŕ����\�ȃg�s�b�N��ނ̍ő�l
 */
//--------------------------------------------------------------------
#define	PROG_TOPIC_MAX		8

#define	TOPIC_ARRAY_MAX		16

//--------------------------------------------------------------------
/**
 * @brief	�ԑg���e�f�[�^�̒���
 *
 * topic_type���P�o�C�g�Atopic_id�P�o�C�g��PROG_TOPIC_MAX�̍��v9�o�C�g�ō\������Ă��܂��B
 * 9�o�C�g��8�ԑg��72�o�C�g�̃o�C�i���f�[�^����擾���Ă��܂��B
 */
//--------------------------------------------------------------------
#define	CONTENTS_DATA_LEN	(1 + PROG_TOPIC_MAX)

//--------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------
typedef struct {
	u8 morning_id;
	u8 noon_id;
	u8 night_id;
	u8 first_intro_id;
	u8 next_intro_id;
	u8 end_id;
	u8 make_id;
}TVPROG_MSG;

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static const TVPROG_MSG TVProgramMsg[] = {
	{	//01	���������@�g���[�i�[
		msg_tv_00_01_01,
		msg_tv_00_01_02,
		msg_tv_00_01_03,
		msg_tv_00_01_04,
		msg_tv_00_01_05,
		msg_tv_00_01_06,
		msg_tv_00_01_07,
	},
	{	//02	�g���[�i�[���T�[�`
		msg_tv_00_02_01,
		msg_tv_00_02_02,
		msg_tv_00_02_03,
		msg_tv_00_02_04,
		msg_tv_00_02_05,
		msg_tv_00_02_06,
		msg_tv_00_02_07,
	},
	{	//03	�o�g���E�H�b�`
		msg_tv_00_03_01,
		msg_tv_00_03_02,
		msg_tv_00_03_03,
		msg_tv_00_03_04,
		msg_tv_00_03_05,
		msg_tv_00_03_06,
		msg_tv_00_03_07,
	},
	{	//04	�g���[�i�[�́@�ɂ����傤
		msg_tv_00_04_01,
		msg_tv_00_04_02,
		msg_tv_00_04_03,
		msg_tv_00_04_04,
		msg_tv_00_04_05,
		msg_tv_00_04_06,
		msg_tv_00_04_07,
	},
	{	//05	�V���I�E�@�j���[�X�@�l�b�g
		msg_tv_00_05_01,
		msg_tv_00_05_02,
		msg_tv_00_05_03,
		msg_tv_00_05_04,
		msg_tv_00_05_05,
		msg_tv_00_05_06,
		msg_tv_00_05_07,
	},
	{	//06	���낭�ŃS���I
		msg_tv_00_06_01,
		msg_tv_00_06_02,
		msg_tv_00_06_03,
		msg_tv_00_06_04,
		msg_tv_00_06_05,
		msg_tv_00_06_06,
		msg_tv_00_06_07,
	},
	{	//07	�V���I�E�E�i�E�I
		msg_tv_00_07_01,
		msg_tv_00_07_02,
		msg_tv_00_07_03,
		msg_tv_00_07_04,
		msg_tv_00_07_05,
		msg_tv_00_07_06,
		msg_tv_00_07_07,
	},
	{	//08	�g�����h�΂񂮂�
		msg_tv_00_08_01,
		msg_tv_00_08_02,
		msg_tv_00_08_03,
		msg_tv_00_08_04,
		msg_tv_00_08_05,
		msg_tv_00_08_06,
		msg_tv_00_08_07,
	},
};
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------
/**
 * @brief	�ԑg���I����Ԃɂ���
 * @param	fsys
 *
 * ���X�N���v�g����Ă΂��
 */
//--------------------------------------------------------------------
void TV_SetEndFlag(FIELDSYS_WORK * fsys)
{
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	TVWORK_SetProgramEnd(tvwk, TRUE);
}

//--------------------------------------------------------------------
/**
 * @brief	�ԑg�̏�Ԃ��擾����
 * @param	fsys
 * @retval	TV_STATUS_PROGRAM_END
 * @retval	TV_STATUS_TOPIC_END
 * @retval	TV_STATUS_START
 * @retval	TV_STATUS_ONAIR
 * @retval	TV_STATUS_NO_TOPIC
 *
 * ���X�N���v�g����Ă΂��
 */
//--------------------------------------------------------------------
int TV_GetBroadcastStatus(FIELDSYS_WORK * fsys)
{
	int num;
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);

#ifdef	TV_BROADCAST_DEBUG
	TVWORK_DEBUG_Info(tvwk);
#endif
	if (TVWORK_IsProgramEnd(tvwk) == TRUE) {
		return	TV_STATUS_PROGRAM_END;	//�ԑg�I�����
	}
	num = TVWORK_GetUsedTopicNumber(tvwk);
	if (num == 0) {
		return TV_STATUS_START;			//�ԑg�J�n����
	}
	if (num == 4) {
		return TV_STATUS_TOPIC_END;		//�S�g�s�b�N���������
	}
	return TV_STATUS_ONAIR;			//�ԑg�������i2�ڈȍ~�j
}


//============================================================================================
//============================================================================================
#ifdef	TV_BROADCAST_DEBUG
static void DebugPutList(const char * name, const u8 * list, int max)
{
	int i;
	OS_Printf("%s", name);
	for (i = 0; i < PROG_TOPIC_MAX; i++) {
		OS_TPrintf("%02d ", list[i]);
	}
	OS_PutString("\n");
}
#endif

//--------------------------------------------------------------------
/**
 * @brief	���݂̔ԑgID���擾
 * @param	fsys
 * @return	int		�ԑgID
 */
//--------------------------------------------------------------------
static TV_PROGRAM_ID GetNowProgramID(FIELDSYS_WORK * fsys)
{
	u8 id;
	u8 plist[7];
	int week, hour, min;
	int ofs;
	week = (EVTIME_GetWeek(fsys) + 6) % 7;
	hour = EVTIME_GetHour(fsys);
	min = EVTIME_GetMinute(fsys);
	ofs = (((19 + hour) % 24) * 4 + (min / 15)) * 7;
	ArchiveDataLoadOfs(plist, ARC_TV, NARC_tv_list_bin, ofs, sizeof(u8) * 7);
	id = plist[week];
#ifdef	TV_BROADCAST_DEBUG
	if (DebugFlagData.tv_program_id != 0) {
		id = DebugFlagData.tv_program_id;
	}
#endif
#ifdef	DEBUG_ONLY_FOR_tamada
	{
		int i;
		OS_TPrintf("TVID:%d week=%d %02d:%02d\n",id, EVTIME_GetWeek(fsys), hour, min);
		for (i = 0; i < 7; i++) {
			OS_TPrintf(" %02d",plist[i]);
		}
		OS_PutString("\n");
	}
#endif
	GF_ASSERT(0 < id && id < TV_PROGRAM_ID_MAX);
	return id;
}

//============================================================================================
//
//
//		�ԑg���e�f�[�^�̎擾
//
//
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N��ʂ̎擾
 * @param	prog_id
 * @return	TVTOPICTYPE
 */
//--------------------------------------------------------------------
static TVTOPICTYPE GetTopicType(TV_PROGRAM_ID prog_id)
{
	u8 type;
	int ofs = CONTENTS_DATA_LEN * (prog_id - 1);
	ArchiveDataLoadOfs(&type, ARC_TV, NARC_tv_contents_bin, ofs, sizeof(u8));
	OS_TPrintf("TV TOPIC TYPE %d\n", type);
	GF_ASSERT(type < TVTOPICTYPE_MAX);
	return type;
}
//--------------------------------------------------------------------
/**
 * @brief	�ԑg���g�s�b�NID�̎擾
 * @param	prog_id
 * @param	list	�g�s�b�NID���R�s�[���郏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------------
static void GetTopicList(TV_PROGRAM_ID prog_id, u8 * list)
{
	u8 type;
	int ofs = CONTENTS_DATA_LEN * (prog_id - 1) + 1;
	ArchiveDataLoadOfs(list, ARC_TV, NARC_tv_contents_bin, ofs, sizeof(u8) * PROG_TOPIC_MAX);
#ifdef TV_BROADCAST_DEBUG
	DebugPutList("TOPIC_ID:", list, PROG_TOPIC_MAX);
#endif
}

//============================================================================================
//============================================================================================

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N������������
 * @param	fsys
 * @param	prog_id
 * @param	topic_id
 * @retval	TRUE
 * @retval	FALSE
 */
//--------------------------------------------------------------------
static BOOL IsEnableBroadcast(FIELDSYS_WORK * fsys, TV_PROGRAM_ID prog_id, int topic_id)
{
	return TRUE;
}

//--------------------------------------------------------------------
/**
 * @brief	���������̂Ȃ��g�s�b�N�̃��X�g���쐬
 */
//--------------------------------------------------------------------
static void MakeTopicTypeList(TV_PROGRAM_ID prog_id, FIELDSYS_WORK * fsys, u8 * type_array)
{
	u8 tlist[PROG_TOPIC_MAX];
	int i, n;
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	GetTopicList(prog_id, tlist);

	MI_CpuClear8(type_array, sizeof(u8) * PROG_TOPIC_MAX);

	//���������̂������Ă��Ȃ��g�s�b�N�𒊏o
	for (i = 0, n = 0; i < PROG_TOPIC_MAX; i++) {
		if (tlist[i] == 0) {
			break;
		}
		if (IsEnableBroadcast(fsys,prog_id,tlist[i]) == TRUE) {
			type_array[n] = tlist[i];
			n ++;
		}
	}
}

//--------------------------------------------------------------------
/**
 * @brief	�����_���ŃC���f�b�N�X��I������
 */
//--------------------------------------------------------------------
static int SelectRandomTopicData(FIELDSYS_WORK * fsys, const u8 * t_array)
{
	u8 array[PROG_TOPIC_MAX];
	int i,n;
	MI_CpuClear8(array, sizeof(u8) * PROG_TOPIC_MAX);
	for (i = 0, n = 0; i < PROG_TOPIC_MAX; i++) {
		if (t_array[i] != 0) {
			array[n] = t_array[i];
			n ++;
		}
	}
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return array[0];
	}
	return array[gf_mtRand() % n];
}

//--------------------------------------------------------------------
/**
 * @brief	�w��g�s�b�N�̒��o
 * @param	tvwk	�e���r���[�N�ւ̃|�C���^
 * @param	topic_type	�g�s�b�N�̎��
 * @param	topic_id	�g�s�b�NID
 * @param	mine	�����f�[�^���ǂ���
 * @param	see		�������ǂ���
 * @param	array	�g�s�b�N�C���f�b�N�X�i�[�̂��߂̔z��ւ̃|�C���^
 */
//--------------------------------------------------------------------
static int SelectExistTopic(TV_WORK * tvwk, TVTOPICTYPE topic_type,
		int topic_id, BOOL mine, BOOL see, u8 * array)
{
	if (topic_type != TVTOPICTYPE_EVENT) {
		return TVWORK_SearchTopics(tvwk, topic_type, topic_id, mine, see, array);
	}
	if (see) {	//�������ǂ������o���Ă����Ȃ��̂łƂ肠����
		return 0;
	}
	if (!mine) {
		return 0;
	}
	if (TVWORK_IsUsedTopicIndex(tvwk, topic_id) == FALSE) {
		array[0] = topic_id;
		return 1;
	}
	return 0;
	
}

//--------------------------------------------------------------------
/**
 * @brief	
 * @param	fsys	�t�B�[���h����ւ̃|�C���^
 * @param	mine	�����f�[�^���ǂ���
 * @param	see		�������ǂ���
 * @param	type_array	�g�s�b�NID�̔z��ւ̃|�C���^
 * @param	topic_array	�g�s�b�N�C���f�b�N�X�i�[�̂��߂̔z��ւ̃|�C���^
 */
//--------------------------------------------------------------------
static int SelectExistTopicData(TVTOPICTYPE topic_type,
		FIELDSYS_WORK * fsys, BOOL mine, BOOL see, const u8 * type_array, u8 * topic_array)
{
	u8 array[TOPIC_ARRAY_MAX];
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	int i,j;
	int n = 0;

	while (*type_array != 0) {
		MI_CpuClear8(array, TOPIC_ARRAY_MAX);
		if (SelectExistTopic(tvwk, topic_type, *type_array, mine, see, array)) {
			for (j = 0; array[j] != 0 && j < TOPIC_ARRAY_MAX; j++) {
				topic_array[n] = array[j];
				n ++;
			}
		}
		type_array ++;
	}
	return n;
}

//--------------------------------------------------------------------
/**
 * @brief	���f�ł��Ȃ��g�s�b�N���폜
 * @param	fsys		�t�B�[���h����ւ̃|�C���^
 * @param	topic_type	�g�s�b�N�̎��
 * @param	topic_array	�g�s�b�N�C���f�b�N�X�i�[�̂��߂̔z��ւ̃|�C���^
 */
//--------------------------------------------------------------------
static void SelectEnableTopicData(FIELDSYS_WORK * fsys, TVTOPICTYPE topic_type, u8 * topic_array)
{
	int i;
	TVBCD * bcd;
	for (i = 0; *topic_array != 0 && i < TOPIC_ARRAY_MAX; topic_array ++, i++) {
		bcd = TVBCD_Create(fsys, topic_type, *topic_array);
		if (!TVTOPIC_CheckLimit(topic_type, fsys, bcd)) {
			*topic_array = 0;
		}
		TVBCD_Delete(bcd);
	}
}

//--------------------------------------------------------------------
/**
 * @brief	�ԑg���ŕ��������g�s�b�N���폜
 * @param	fsys		�t�B�[���h����ւ̃|�C���^
 * @param	topic_array	�g�s�b�N�C���f�b�N�X�i�[�̂��߂̔z��ւ̃|�C���^
 */
//--------------------------------------------------------------------
static void DeleteUsedTopicData(FIELDSYS_WORK * fsys, u8 * topic_array)
{
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	while (*topic_array != 0) {
		if (TVWORK_IsUsedTopicIndex(tvwk, *topic_array)) {
			*topic_array = 0;
		}
		topic_array ++;
	}
}

//--------------------------------------------------------------------
/**
 * @brief	��������g�s�b�N�𒊏o����
 * @param	fsys
 * @param	mine
 * @param	see
 * @return	int		0�̂Ƃ��A�f�[�^�Ȃ�
 */
//--------------------------------------------------------------------
int TV_ChooseBroadcastTopic(FIELDSYS_WORK * fsys, BOOL mine, BOOL see)
{
	u8 type_array[PROG_TOPIC_MAX];
	u8 topic_array[TOPIC_ARRAY_MAX];
	int result;
	TV_PROGRAM_ID prog_id;
	int topic_type;
	
	prog_id = GetNowProgramID(fsys);
	topic_type = GetTopicType(prog_id);

	MI_CpuClear8(type_array, PROG_TOPIC_MAX);
	MI_CpuClear8(topic_array, TOPIC_ARRAY_MAX);

	//���������̂Ȃ��g�s�b�N�̃��X�g����
	MakeTopicTypeList(prog_id, fsys, type_array);
#ifdef	TV_BROADCAST_DEBUG
	DebugPutList("TOPIC_ID:", type_array, PROG_TOPIC_MAX);
#endif

	//�f�[�^���݃`�F�b�N�őI��
	result = SelectExistTopicData(topic_type, fsys, mine, see, type_array, topic_array);
#ifdef	TV_BROADCAST_DEBUG
	DebugPutList("EXIST  INDEX:",topic_array, TOPIC_ARRAY_MAX);
#endif
	if (result == 0) {
		return 0;			//�f�[�^���Ȃ�����
	}
	// �����ł��Ȃ��g�s�b�N���폜
	SelectEnableTopicData(fsys, topic_type, topic_array);
#ifdef	TV_BROADCAST_DEBUG
	DebugPutList("ENABLE INDEX:",topic_array, TOPIC_ARRAY_MAX);
#endif

	//�����ς݃g�s�b�N��r��
	DeleteUsedTopicData(fsys, topic_array);
#ifdef	TV_BROADCAST_DEBUG
	DebugPutList("NOTUSE INDEX:",topic_array, TOPIC_ARRAY_MAX);
#endif

	//�c�������̂��痐���őI��
	result = SelectRandomTopicData(fsys, topic_array);

	return result;
}

//--------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------
int TV_ChooseBroadcastTopicTotal(FIELDSYS_WORK * fsys)
{
	int result;
	result = TV_ChooseBroadcastTopic(fsys, TV_OTHER_TOPIC, TV_NEW_TOPIC);
	if (result) {
		return result;
	}
	result = TV_ChooseBroadcastTopic(fsys, TV_MINE_TOPIC, TV_NEW_TOPIC);
	if (result) {
		return result;
	}
	result = TV_ChooseBroadcastTopic(fsys, TV_OTHER_TOPIC, TV_OLD_TOPIC);
	if (result) {
		return result;
	}
	result = TV_ChooseBroadcastTopic(fsys, TV_MINE_TOPIC, TV_OLD_TOPIC);
	return result;
}

//============================================================================================
//============================================================================================

//--------------------------------------------------------------------
/**
 * @brief	�ԑg�ɂ��킹�ă��b�Z�[�W�\���̂��擾
 */
//--------------------------------------------------------------------
static const TVPROG_MSG * GetNowProgramMsgData(FIELDSYS_WORK * fsys)
{
	TV_PROGRAM_ID prog_id = GetNowProgramID(fsys);
	GF_ASSERT(prog_id <= NELEMS(TVProgramMsg));
	return &TVProgramMsg[prog_id - 1];
}

//--------------------------------------------------------------------
/**
 * @brief	�ԑg���ƂɌ��܂��Ă��郁�b�Z�[�WID���擾�i7��ށA�O�t����I���Ȃǁj
 * @param	fsys
 * @param	prog_msg_id		TV_PRO_MSG_�`�iscr_tv.h�Q�Ɓj
 * @return	int				���b�Z�[�WID�iNARC_msg_tv_program_dat���j
 *
 * ���X�N���v�g����Ă΂��
 */
//--------------------------------------------------------------------
int TV_GetProgramMsg(FIELDSYS_WORK * fsys, int prog_msg_id)
{
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	const TVPROG_MSG * pmsg = GetNowProgramMsgData(fsys);

	switch (prog_msg_id) {
	default:
		GF_ASSERT(0);
		/* FALL THROUGH */
	case TV_PROG_MSG_OPENING:
		switch (GF_RTC_GetTimeZone()) {
		case TIMEZONE_MORNING:
			return pmsg->morning_id;
		case TIMEZONE_NOON:
			return pmsg->noon_id;
		default:
			return pmsg->night_id;
		}
	case TV_PROG_MSG_INTRO:
		if (TVWORK_GetUsedTopicNumber(tvwk) == 0) {
			return pmsg->first_intro_id;
		} else {
			return pmsg->next_intro_id;
		}
	case TV_PROG_MSG_ENDING:
		return pmsg->end_id;
	case TV_PROG_MSG_PLEASE:
		return pmsg->make_id;
	}
}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�ԑg�g�s�b�N��������
 * @param	fsys		�t�B�[���h����ւ̃|�C���^
 * @param	ws			WORDSET�ւ̃|�C���^
 * @param	idx			�g�s�b�N�C���f�b�N�X�w��
 * @param	arc_id		�A�[�J�C�u�w����󂯎�邽�߂̃|�C���^
 * @param	msg_id		���b�Z�[�W�w����󂯎�邽�߂̃|�C���^
 */
//--------------------------------------------------------------------
BOOL TV_GetProgramID(FIELDSYS_WORK * fsys, WORDSET * ws, int idx, u16 * arc_id, u16 * msg_id)
{
	TV_PROGRAM_ID prog_id = GetNowProgramID(fsys);
	int topic_type = GetTopicType(prog_id);
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	TVBCD * bcd;

	TVWORK_SetUsedTopicIndex(tvwk, idx);

	bcd = TVBCD_Create(fsys, topic_type, idx);
	//TVWORK_DEBUG_Info(tvwk);

	TVBCD_CountUpBroadCast(bcd);
	*msg_id = TVTOPIC_Make(topic_type, fsys, ws, bcd, arc_id);

	TVBCD_Delete(bcd);
	return TRUE;
}



