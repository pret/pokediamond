//============================================================================================
/**
 * @file	tv_bcdata.c
 * @brief	�e���r�����p�f�[�^��舵��
 * @date	2006.05.20
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"

#include "savedata/tv_work.h"
#include "savedata/mystatus.h"

#include "field/tv_topic.h"

//#include "system/pm_rtc.h"
//#include "ev_time.h"

#include "tv.h"
//#include "scr_tv.h"

//#include "msgdata/msg.naix"



//#include "msgdata/msg_tv_program.h"
//#include "msgdata/msg_tvcm.h"
//#include "msgdata/msg_msg_tv_01.h"
//#include "msgdata/msg_msg_tv_02.h"
//#include "msgdata/msg_msg_tv_03.h"
//#include "msgdata/msg_msg_tv_04.h"

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�e���r�����p�f�[�^�̒�`
 */
//--------------------------------------------------------------------
struct TVBCD{
	u8 topic_id;					///<�g�s�b�N�w��ID
	u8 rom_ver;						///<�����o�[�W�����i�_�C�������h�E�p�[���E���̑��j
	u8 region_code;					///<����R�[�h
	u8 sex;							///<����
	STRCODE name[PERSON_NAME_SIZE + EOM_SIZE];		///<���O������
	TVTOPIC * topic;				///<�g�s�b�N�f�[�^�ւ̃|�C���^
};



//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�����p�f�[�^���[�N�̏�����
 * @param	bcd		�����p�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------------
static void TVBCD_Init(TVBCD * bcd)
{
	MI_CpuClear8(bcd, sizeof(TVBCD));
}


//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void TVBCD_SetSex(TVBCD * bcd, int sex)
{
	bcd->sex = sex;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void TVBCD_SetRegionCode(TVBCD * bcd, int region_code)
{
	bcd->region_code = region_code;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void TVBCD_SetRomVersion(TVBCD * bcd, int rom_ver)
{
	bcd->rom_ver = rom_ver;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void TVBCD_SetName(TVBCD * bcd, const STRCODE * name)
{
	PM_strncpy(bcd->name, name, PERSON_NAME_SIZE + EOM_SIZE);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void TVBCD_SetTopicData(TVBCD * bcd, TVTOPIC * topic)
{
	bcd->topic_id = TVTOPIC_GetTopicID(topic);
	bcd->topic = topic;
}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�����f�[�^�̃J�E���g�A�b�v����
 * @param	bcd		�����p�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------------
void TVBCD_CountUpBroadCast(TVBCD * bcd)
{
	if (bcd->topic != NULL) {
		TVTOPIC_CountUpBroadcast(bcd->topic);
	}
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
int TVBCD_GetSex(const TVBCD * bcd)
{
	return bcd->sex;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
int TVBCD_GetRegionCode(const TVBCD * bcd)
{
	return bcd->region_code;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
int TVBCD_GetRomVersion(const TVBCD * bcd)
{
	return bcd->rom_ver;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
const STRCODE * TVBCD_GetName(const TVBCD * bcd)
{
	return bcd->name;
}
//----------------------------------------------------------
//----------------------------------------------------------
void * TVBCD_GetTopicData(TVBCD * bcd)
{
	return TVTOPIC_GetData(bcd->topic);
}
//----------------------------------------------------------
//----------------------------------------------------------
int TVBCD_GetTopicID(const TVBCD * bcd)
{
	return bcd->topic_id;
}


//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���l�f�[�^��������p�f�[�^����
 */
//----------------------------------------------------------
static TVBCD * CreateOtherTVBCD(FIELDSYS_WORK * fsys,
		OTHER_TOPIC * othertopic)
{
	TVBCD * bcd = sys_AllocMemory(HEAPID_FIELD, sizeof(TVBCD));

	TVBCD_Init(bcd);
	TVBCD_SetName(bcd, OTHERTOPIC_GetName(othertopic));
	TVBCD_SetRegionCode(bcd, OTHERTOPIC_GetRegionCode(othertopic));
	TVBCD_SetRomVersion(bcd, OTHERTOPIC_GetRomVersion(othertopic));
	TVBCD_SetTopicData(bcd, OTHERTOPIC_GetTopicData(othertopic));
	return bcd;
}
//----------------------------------------------------------
/**
 * @brief	�����f�[�^��������p�f�[�^����
 */
//----------------------------------------------------------
static TVBCD * CreateMyTVBCD(FIELDSYS_WORK * fsys, MY_TOPIC * mytopic)
{
	MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);
	TVBCD * bcd = sys_AllocMemory(HEAPID_FIELD, sizeof(TVBCD));

	TVBCD_Init(bcd);
	TVBCD_SetName(bcd, MyStatus_GetMyName(my));
	TVBCD_SetSex(bcd, MyStatus_GetMySex(my));
	TVBCD_SetRegionCode(bcd, PM_LANG);
	TVBCD_SetRomVersion(bcd, PM_VERSION);
	TVBCD_SetTopicData(bcd, MYTOPIC_GetTopic(mytopic));
	return bcd;
}
//----------------------------------------------------------
/**
 * @brief	�_�~�[�ŕ����p�f�[�^�����i�C�x���g�^�g�s�b�N�p�j
 */
//----------------------------------------------------------
static TVBCD * CreateDmyTVBCD(FIELDSYS_WORK * fsys, int index)
{
	MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);
	TVBCD * bcd = sys_AllocMemory(HEAPID_FIELD, sizeof(TVBCD));

	TVBCD_Init(bcd);
	bcd->topic_id = index;
	TVBCD_SetName(bcd, MyStatus_GetMyName(my));
	TVBCD_SetSex(bcd, MyStatus_GetMySex(my));
	TVBCD_SetRegionCode(bcd, PM_LANG);
	TVBCD_SetRomVersion(bcd, PM_VERSION);
	//TVBCD_SetTopicData(bcd, NULL);
	bcd->topic = NULL;
	return bcd;
}

//----------------------------------------------------------
/**
 * @brief	�e���r�����p�f�[�^��������
 * @param	fsys			�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	topic_type		�g�s�b�N�̎��
 * @param	index			�f�[�^�C���f�b�N�X
 */
//----------------------------------------------------------
TVBCD * TVBCD_Create(FIELDSYS_WORK * fsys, TVTOPICTYPE topic_type, int index)
{
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);

	if (topic_type == TVTOPICTYPE_EVENT) {
		return CreateDmyTVBCD(fsys, index);
	}
	if (TVWORK_IsMineIndex(index) == FALSE) {
		OTHER_TOPIC * othertopic = TVWORK_GetOtherTopicByIndex(tvwk, topic_type, index);
		return CreateOtherTVBCD(fsys, othertopic);
	} else {
		MY_TOPIC * mytopic = TVWORK_GetMyTopicByIndex(tvwk, topic_type, index);
		return CreateMyTVBCD(fsys, mytopic);
	}
}

//----------------------------------------------------------
/**
 * @brief	�e���r�����p�f�[�^��������
 * @param	bcd		�����p�f�[�^�ւ̃|�C���^
 */
//----------------------------------------------------------
void TVBCD_Delete(TVBCD * bcd)
{
	sys_FreeMemoryEz(bcd);
}

