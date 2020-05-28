//============================================================================================
/**
 * @file	tv_cm.c
 * @brief	���f����CM�̌���
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.17
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"

#include "savedata/tv_work.h"
#include "savedata/zukanwork.h"
#include "savedata/mystatus.h"
#include "field/eventflag.h"

#include "field/tv_topic.h"

#include "system/pm_rtc.h"
#include "ev_time.h"
#include "sysflag.h"

#include "tv.h"

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	CM�`�F�b�N�p�֐��^��`
 */
//--------------------------------------------------------------------
typedef BOOL (*CHECK_CM_FUNC)(FIELDSYS_WORK *);

static BOOL AnytimeEnable(FIELDSYS_WORK * fsys);
static BOOL AnytimeDisable(FIELDSYS_WORK * fsys);
static BOOL C01Check(FIELDSYS_WORK * fsys);
static BOOL T03Check(FIELDSYS_WORK * fsys);
static BOOL C03Check(FIELDSYS_WORK * fsys);
static BOOL C04Check(FIELDSYS_WORK * fsys);
static BOOL C05Check(FIELDSYS_WORK * fsys);
static BOOL C11Check(FIELDSYS_WORK * fsys);
static BOOL GTCOpenCheck(FIELDSYS_WORK * fsys);
static BOOL Get5BadgeCheck(FIELDSYS_WORK * fsys);
static BOOL SinouZukanCompleteCheck(FIELDSYS_WORK * fsys);
static BOOL GingaCMCheck(FIELDSYS_WORK * fsys);
static BOOL ZukanGetCheck(FIELDSYS_WORK * fsys);
static BOOL BattleTowerOpenCheck(FIELDSYS_WORK * fsys);
static BOOL WiFiBattleTowerOpenCheck(FIELDSYS_WORK * fsys);
static BOOL ShipEnableCheck(FIELDSYS_WORK * fsys);
static BOOL GameClearCheck(FIELDSYS_WORK * fsys);



//--------------------------------------------------------------------
/**
 * @brief	�������`�F�b�NID
 *
 * AllConditionFuncTable�ƕ��т���v�����Ă����K�v������
 */
//--------------------------------------------------------------------
enum {
	FLAG_AnytimeEnable,				///<�ŏ�����
	FLAG_T03Check,					///<�\�m�I����
	FLAG_C01Check,					///<�R�g�u�L����
	FLAG_C03Check,					///<�N���K�l����
	FLAG_C04Check,					///<�n�N�^�C����
	FLAG_C05Check,					///<���X�K����
	FLAG_C11Check,					///<C11����
	FLAG_Get5BadgeCheck,			///<�W���o�b�W�T��
	FLAG_SinouZukanCompleteCheck,	///<�V���I�E�}�ӃR���v
	FLAG_ZukanGetCheck,				///<�}�ӎ擾��
	FLAG_GameClearCheck,			///<�a�������

	FLAG_CMCHECK_MAX,
};
//--------------------------------------------------------------------
/**
 * @brief	�������`�F�b�N�֐��̃e�[�u��
 */
//--------------------------------------------------------------------
static const CHECK_CM_FUNC AllConditionFuncTable[] = {
	AnytimeEnable,				///<�ŏ�����
	T03Check,					///<�\�m�I����
	C01Check,					///<�R�g�u�L����
	C03Check,					///<�N���K�l����
	C04Check,					///<�n�N�^�C����
	C05Check,					///<���X�K����
	C11Check,					///<C11����
	Get5BadgeCheck,				///<�W���o�b�W�T��
	SinouZukanCompleteCheck,	///<�V���I�E�}�ӃR���v
	ZukanGetCheck,				///<�}�ӎ擾��
	GameClearCheck,				///<�a�������
};

//============================================================================================
//
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�eCM���Ƃ̕����������e�[�u��
 */
//--------------------------------------------------------------------
static u8 CheckCMTable[] = {
	FLAG_AnytimeEnable,				///<�|�P�����Z���^�[	�ŏ�����
	FLAG_AnytimeEnable,				///<�t�����h���B�V���b�v	�ŏ�����
	FLAG_AnytimeEnable,				///<�s�u��	�ŏ�����
	FLAG_AnytimeEnable,				///<�g���[�i�[�X�N�[��	�ŏ�����
	FLAG_AnytimeEnable,				///<�|�P�b�`	�ŏ�����
	FLAG_C01Check,					///<�|�P�b�`�\�t�g	
	FLAG_T03Check,					///<�ԉ�	�\�m�I����
	FLAG_C04Check,					///<���]�ԉ�	�n�N�^�C����
	FLAG_C04Check,					///<�R���e�X�g�b�l	�n�N�^�C����
	FLAG_C05Check,					///<�Q�[���R�[�i�[	���X�K����
	FLAG_C05Check,					///<���R����	���X�K����
	FLAG_C05Check,					///<�g�o���f�p�[�g	���X�K����
	FLAG_C05Check,					///<��ĉ�	���X�K����
	FLAG_C05Check,					///<�z�e��	���X�K����
	FLAG_C05Check,					///<�厼��	���X�K����
	FLAG_Get5BadgeCheck,				///<�L�b�T�L�V�e�B	�W���o�b�W�T��
	FLAG_Get5BadgeCheck,				///<�i�M�T�s��	�W���o�b�W�T��
	FLAG_C03Check,					///<�f�s�b	�N���K�l����
	FLAG_SinouZukanCompleteCheck,	///<�|�P�����p�[�N	�V���I�E�}�ӃR���v
	FLAG_GameClearCheck,			///<�L�b�T�L�V�e�B�̑D	�V���I�E�}�ӃR���v
	FLAG_GameClearCheck,			///<�o�g���]�[��	�V���I�E�}�ӃR���v
	FLAG_SinouZukanCompleteCheck,	///<������̌���	�V���I�E�}�ӃR���v
	FLAG_C05Check,					///<�M���K�c�P	���X�K����
	FLAG_C05Check,					///<�M���K�c�Q	���X�K����
	FLAG_ZukanGetCheck,				///<�|�P�����Z���^�[�ʐM��	�}�ӎ擾��
	FLAG_ZukanGetCheck,				///<�|�P�����Z���^�[Wi-Fi��	�}�ӎ擾��
	FLAG_C11Check,					///<�o�g���^���[	C11����
	FLAG_C11Check,					///< Wi-Fi�o�g���^���[	C11����
	FLAG_GameClearCheck,				///<��蕨�b�l�i�D�j	�a�������
};

//============================================================================================
//============================================================================================

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL AnytimeEnable(FIELDSYS_WORK * fsys)
{
	return TRUE;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL AnytimeDisable(FIELDSYS_WORK * fsys)
{
	return FALSE;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL C01Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_C01);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL T03Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_T03);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL C03Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_C03);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL C04Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_C04);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL C05Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_C05);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL C11Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_C11);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL GTCOpenCheck(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_GTCOpenCheck(ev);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL Get5BadgeCheck(FIELDSYS_WORK * fsys)
{
	MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);
	if (MyStatus_GetBadgeCount(my) >= 5) {
		return TRUE;
	} else {
		return FALSE;
	}
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL SinouZukanCompleteCheck(FIELDSYS_WORK * fsys)
{
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
	return ZukanWork_CheckShinouComp(zw);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL GingaCMCheck(FIELDSYS_WORK * fsys)
{
	return FALSE;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL ZukanGetCheck(FIELDSYS_WORK * fsys)
{
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
	return ZukanWork_GetZukanGetFlag(zw);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL BattleTowerOpenCheck(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_BTowerOpenCheck(ev);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL WiFiBattleTowerOpenCheck(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_BTowerOpenCheck(ev);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL ShipEnableCheck(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ShipCheck(ev);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL GameClearCheck(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_GameClearCheck(ev);
}



//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	���f�\��CM�̒��o����
 */
//--------------------------------------------------------------------
static int ChooseEnableCMID(FIELDSYS_WORK * fsys, u8 * cm_array)
{
	int i,n;
	BOOL check_list[NELEMS(AllConditionFuncTable)];

	GF_ASSERT(NELEMS(AllConditionFuncTable) == FLAG_CMCHECK_MAX);
	//������S�`�F�b�N
	for (i = 0; i < NELEMS(AllConditionFuncTable); i++) {
		check_list[i] = AllConditionFuncTable[i](fsys);
	}
	//CM���Ƃɏ������������Ă��邩�`�F�b�N
	for (i = 0, n = 0; i < NELEMS(CheckCMTable); i++) {
		if (check_list[CheckCMTable[i]]) {
			cm_array[n] = i;
			n ++;
		}
	}
	return n;
}

//--------------------------------------------------------------------
/**
 * @brief	CM�𒊏o�A���̒����烉���_����ID���擾����
 */
//--------------------------------------------------------------------
int TVCM_ChooseID(FIELDSYS_WORK * fsys)
{
	u8 cm_id[32];
	int max;
	MI_CpuClear8(cm_id, 32);
	max = ChooseEnableCMID(fsys, cm_id);
	if (max == 0) {
		return 0;
	}
	return cm_id[gf_mtRand() % max];
}






