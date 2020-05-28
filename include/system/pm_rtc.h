//============================================================================================
/**
 * @file	pm_rtc.h
 * @brief	RTCアクセスラッパー用ヘッダ
 * @author	tamada	GAME FREAK inc.
 * @date	2005.11.21
 *
 * 直接のRTCライブラリ使用は禁止する。
 * この関数経由でのアクセスを行う。
 */
//============================================================================================
#ifndef	__PM_RTC_H__
#define	__PM_RTC_H__

#include <nitro.h>
#include <nnsys.h>

#include "system/timezone.h"
//--------------------------------------------------------------
//	初期化＆メイン
//--------------------------------------------------------------
extern void GF_RTC_Init(void);
extern void GF_RTC_Main(void);

//--------------------------------------------------------------
//	取得用関数
//--------------------------------------------------------------
extern void GF_RTC_GetDateTime(RTCDate * date, RTCTime * time);
extern void GF_RTC_GetTime(RTCTime * time);
extern void GF_RTC_GetDate(RTCDate * date);
extern int GF_RTC_GetTimeBySecond(void);
extern s64 GF_RTC_GetDateTimeBySecond(void);

//経過時間の取得
extern s64 GF_RTC_GetPassTime(s64 start_sec, s64 end_sec);

//--------------------------------------------------------------
//	ツール関数
//--------------------------------------------------------------
extern int GF_RTC_ConvertHourToTimeZone(int hour);
extern int GF_RTC_GetTimeZone(void);
extern int GF_RTC_GetDaysOffset(const RTCDate * date);
//夜かどうかチェック
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
//	デバッグ用関数
//--------------------------------------------------------------
extern void DEBUG_StartFakeTime(int rate);
extern void DEBUG_StopFakeTime(void);
extern void DEBUG_StartFakeFixTime(int hour, int minute);

#endif

#endif	//__PM_RTC_H__
