//============================================================================================
/**
 * @file	ev_time.c
 * @brief	�Q�[�������Ԑ���֘A
 * @author	tamada
 * @date	2006.02.03
 */
//============================================================================================

#include "common.h"

#include "system/pm_rtc.h"

#include "fieldsys.h"

#include "savedata/savedata.h"
#include "savedata/seedbed.h"
#include "savedata/undergrounddata.h"  // UnderGroundDataDayUpdate
#include "savedata/randomgroup.h"
#include "savedata/honeytree_data.h"
#include "savedata/encount.h"
#include "savedata/tv_work.h"
#include "savedata/b_tower.h"
#include "savedata/wifihistory.h"

#include "situation_local.h"


#include "ev_time.h"

#include "savedata/gametime.h"

#include "system/timezone.h"

#include "seedsys.h"

#include "script.h"

#include "tr_card_time.h"

#include "poketool/poke_tool.h"

#include "syswork.h"

#include "b_tower_ev.h"

//============================================================================================
//============================================================================================

//============================================================================================
//============================================================================================
static void UpdateDayEvent(FIELDSYS_WORK * fsys, s32 diff_days);
static void UpdateMinuteEvent(FIELDSYS_WORK * fsys, s32 diff_minute, const RTCTime * now);

static void UpdateDateCheck(FIELDSYS_WORK * fsys, GMTIME * tm, const RTCDate * now_date);
static void UpdateMinuteCheck(FIELDSYS_WORK * fsys, GMTIME * tm,
		const RTCDate * now_date, const RTCTime * now_time);

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 */
//------------------------------------------------------------------
void EVTIME_Update(FIELDSYS_WORK * fsys)
{
	RTCDate now_date;
	RTCTime now_time;
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);

	if (tm->use_flag == FALSE) {
		return;
	}

	GF_RTC_GetDateTime(&now_date, &now_time);

	UpdateDateCheck(fsys, tm, &now_date);
	UpdateMinuteCheck(fsys, tm, &now_date, &now_time);
}

//------------------------------------------------------------------
///�����o�߂�����
//------------------------------------------------------------------
static void UpdateDateCheck(FIELDSYS_WORK * fsys, GMTIME * tm, const RTCDate * now_date)
{
	s32 now_day;
	now_day = RTC_ConvertDateToDay(now_date);

	if (now_day < tm->sv_day) {
		//���݁@���@�ߋ��@�c���肦�Ȃ��͂�
		//���ݎ��Ԃ��Z�b�g���邾���Ŗ߂�
		tm->sv_day = now_day;
		return;
	}
	if (now_day > tm->sv_day) {
		UpdateDayEvent(fsys, now_day - tm->sv_day);
		tm->sv_day = now_day;
	}
}

//------------------------------------------------------------------
///�b���o�߂�����
//------------------------------------------------------------------
static void UpdateMinuteCheck(FIELDSYS_WORK * fsys, GMTIME * tm,
		const RTCDate * now_date, const RTCTime * now_time)
{
	s64 now, sv;
	s32 diff_minute;
	now = RTC_ConvertDateTimeToSecond(now_date, now_time);
	sv = RTC_ConvertDateTimeToSecond(&tm->sv_date, &tm->sv_time);
	if (now < sv) {
		//���݁@���@�ߋ��@�c���肦�Ȃ��͂�
		//���ݎ��Ԃ��Z�b�g���邾���Ŗ߂�
		tm->sv_date = *now_date;
		tm->sv_time = *now_time;
		return;
	}
	diff_minute = (now - sv) / 60;
	if (diff_minute > 0) {
		GMTIME_CountDownPenaltyTime(tm, diff_minute);
		UpdateMinuteEvent(fsys, diff_minute, now_time);

		tm->sv_date = *now_date;
		tm->sv_time = *now_time;
	}
}

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	���Ԃɂ��f�[�^�X�V�F�����P��
 * @param	fsys			�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	diff_days		�o�߂������ԁi�����j
 *
 * ������FIELDSYS_WORK���Ƃ��Ă��邪�A��{�I�ɂ�SAVEDATA�݂̂�
 * �X�V�ł���悤�Ȏd�g�݂̊֐����ĂԂׂ��B
 */
//------------------------------------------------------------------
static void UpdateDayEvent(FIELDSYS_WORK * fsys, s32 diff_days)
{
	
	//���L�̂悤�Ȋ����Ŏ��Ԋ֘A�C�x���g�X�V������ǉ�����
	//
	//TVData_Update(fsys, diff_days);
	//ZukanHyouka_Update
	//�c

    // �n���̓����o�߂Ɋ֘A��������
    UnderGroundDataDayUpdate(GameSystem_GetSaveData(fsys), diff_days);

	//1�����ɃN���A����t���O
	TimeEventFlagClear(fsys);

	//�g���[�i�[�P�[�X�̃o�b�W�𕅂点��
	TRCTIME_CorrodeBadge(fsys->savedata, diff_days);	

	// �����̎�O���[�v�X�V
	RandomGroup_Update(SaveData_GetRandomGroup(fsys->savedata), diff_days);

	//�G���J�E���g�֘A�����_���̎�X�V
	EncDataSave_UpdateRandSeed(EncDataSave_GetSaveDataPtr( fsys->savedata ),
			RandomGroup_GetDefaultRandom( SaveData_GetRandomGroup(fsys->savedata) ) );

	//�|�P���X�����̌o�߂����� by soga 2006.05.16
	{
		POKEPARTY *ppt;

		ppt=SaveData_GetTemotiPokemon(fsys->savedata);
		PokerusCounterDec(ppt,diff_days);
	}

	//�V���ЃC�x���g�p�B���߂���������X�V by tomo 2006.5.17
	{
		EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
		u16 onedaywork = SysWork_NewsDaysCountGet( ev );
		if (onedaywork > diff_days) {
			onedaywork -= diff_days;
		} else {
			onedaywork = 0;
		}
		SysWork_NewsDaysCountSet( ev , onedaywork );
	}

	//�|�P�����N�W
	{
		SysWorkUpdatePokeLot(fsys->savedata, diff_days);
	}

	//�A�C�e����������
	{
		SysWorkUpdatePokeLevelNo(fsys->savedata);
	}


	//�o�g���^���[Day�����_���V�[�h������̍X�V����
	BtlTower_UpdateDayRndSeed(fsys->savedata);

	//WIFI�ʐM�����f�[�^�̍X�V����
	WIFIHISTORY_Update(SaveData_GetWifiHistory(fsys->savedata));
}

//------------------------------------------------------------------
/**
 * @brief	���Ԃɂ��f�[�^�X�V�F���P��
 * @param	fsys			�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	diff_minute		�o�߂������ԁi���P�ʁj
 *
 * ������FIELDSYS_WORK���Ƃ��Ă��邪�A��{�I�ɂ�SAVEDATA�݂̂�
 * �X�V�ł���悤�Ȏd�g�݂̊֐����ĂԂׂ��B
 */
//------------------------------------------------------------------
static void UpdateMinuteEvent(FIELDSYS_WORK * fsys, s32 diff_minute, const RTCTime * now)
{
	SeedSys_Growth(fsys, diff_minute);
///	HTE_UpdateHoneyTreeTime(fsys, diff_minute);
	HTSave_UpdateHoneyTreeTime(fsys->savedata, diff_minute);
    UnderGroundDataMinUpdate(fsys->savedata, diff_minute, EVTIME_IsPenaltyMode(fsys));

	{
		TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
		TVWORK_UpdateMinuteCount(tvwk, diff_minute, now->minute);
	}
}




//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	���ԑт̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	int		���ԑсifield/timezone.h���Q�Ɓj
 */
//------------------------------------------------------------------
int EVTIME_GetTimeZone(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return GF_RTC_ConvertHourToTimeZone(tm->sv_time.hour);

}
//------------------------------------------------------------------
/**
 * @brief	�C�x���g���ԁi���j�̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	int		��
 */
//------------------------------------------------------------------
int EVTIME_GetMonth(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return tm->sv_date.month;
}
//------------------------------------------------------------------
/**
 * @brief	�C�x���g���ԁi���j�̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	int		��
 */
//------------------------------------------------------------------
int EVTIME_GetDay(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return tm->sv_date.day;
}
//------------------------------------------------------------------
/**
 * @brief	�C�x���g���ԁi�j���j�̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	int		�j��
 */
//------------------------------------------------------------------
int EVTIME_GetWeek(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return tm->sv_date.week;
}
//------------------------------------------------------------------
/**
 * @brief	�C�x���g���ԁi���j�̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	int		����
 */
//------------------------------------------------------------------
int EVTIME_GetHour(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return tm->sv_time.hour;
}
//------------------------------------------------------------------
/**
 * @brief	�C�x���g���ԁi���j�̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	int		��
 */
//------------------------------------------------------------------
int EVTIME_GetMinute(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return tm->sv_time.minute;
}


//------------------------------------------------------------------
/**
 * @brief	�Q�[���J�n�̓��t�����Ԏ擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	date	�Q�[���J�n�̓��t���󂯎�邽�߂�RTCDate�^�ւ̃|�C���^
 * @param	time	�Q�[���J�n�̎��Ԃ��󂯎�邽�߂�RTCTime�^�ւ̃|�C���^
 */
//------------------------------------------------------------------
void EVTIME_GetGameStartDateTime(const FIELDSYS_WORK * fsys, RTCDate * date, RTCTime * time)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	RTC_ConvertSecondToDateTime(date, time, tm->start_sec);
}

//------------------------------------------------------------------
/**
 * @brief	�Q�[���N���A�̓��t�����Ԏ擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	date	�Q�[���J�n�̓��t���󂯎�邽�߂�RTCDate�^�ւ̃|�C���^
 * @param	time	�Q�[���J�n�̎��Ԃ��󂯎�邽�߂�RTCTime�^�ւ̃|�C���^
 */
//------------------------------------------------------------------
void EVTIME_GetGameClearDateTime(const FIELDSYS_WORK * fsys, RTCDate * date, RTCTime * time)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	RTC_ConvertSecondToDateTime(date, time, tm->clear_sec);
}

//------------------------------------------------------------------
/**
 * @brief	�Q�[���N���A�̓��t�����ԃZ�b�g
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void EVTIME_SetGameClearDateTime(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	tm->clear_sec = GF_RTC_GetDateTimeBySecond();

}

//------------------------------------------------------------------
/**
 * @brief	DS�ݒ�ύX�̃y�i���e�B���[�h���ǂ����̔���
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ��A�y�i���e�B��
 */
//------------------------------------------------------------------
BOOL EVTIME_IsPenaltyMode(FIELDSYS_WORK * fsys)
{
	GMTIME * gt = SaveData_GetGameTime(fsys->savedata);
	return GMTIME_IsPenaltyMode(gt);
}


