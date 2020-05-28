//============================================================================================
/**
 * @file	pm_rtc.h
 * @brief	RTC�A�N�Z�X���b�p�[�p�w�b�_
 * @author	tamada	GAME FREAK inc.
 * @date	2005.11.21
 *
 * ���ڂ�RTC���C�u�����g�p�͋֎~����B
 * ���̊֐��o�R�ł̃A�N�Z�X���s���B
 */
//============================================================================================
#ifndef	__PM_RTC_H__
#define	__PM_RTC_H__

#include <nitro.h>
#include <nnsys.h>

#include "system/timezone.h"
//--------------------------------------------------------------
//	�����������C��
//--------------------------------------------------------------
extern void GF_RTC_Init(void);
extern void GF_RTC_Main(void);

//--------------------------------------------------------------
//	�擾�p�֐�
//--------------------------------------------------------------
extern void GF_RTC_GetDateTime(RTCDate * date, RTCTime * time);
extern void GF_RTC_GetTime(RTCTime * time);
extern void GF_RTC_GetDate(RTCDate * date);
extern int GF_RTC_GetTimeBySecond(void);
extern s64 GF_RTC_GetDateTimeBySecond(void);

//�o�ߎ��Ԃ̎擾
extern s64 GF_RTC_GetPassTime(s64 start_sec, s64 end_sec);

//--------------------------------------------------------------
//	�c�[���֐�
//--------------------------------------------------------------
extern int GF_RTC_ConvertHourToTimeZone(int hour);
extern int GF_RTC_GetTimeZone(void);
extern int GF_RTC_GetDaysOffset(const RTCDate * date);
//�邩�ǂ����`�F�b�N
extern BOOL GF_RTC_IsNightTime(void);

static inline BOOL GF_RTC_IsLeapYear(u32 year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

#ifdef	PM_DEBUG
//--------------------------------------------------------------
//	�f�o�b�O�p�֐�
//--------------------------------------------------------------
extern void DEBUG_StartFakeTime(int rate);
extern void DEBUG_StopFakeTime(void);
extern void DEBUG_StartFakeFixTime(int hour, int minute);

#endif

#endif	//__PM_RTC_H__
