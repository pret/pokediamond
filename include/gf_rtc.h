#ifndef POKEDIAMOND_GF_RTC_H
#define POKEDIAMOND_GF_RTC_H

#include "RTC_api.h"
#include "nitro/types.h"

enum RTC_Month
{
    RTC_MONTH_JANUARY = 1,
    RTC_MONTH_FEBRUARY,
    RTC_MONTH_MARCH,
    RTC_MONTH_APRIL,
    RTC_MONTH_MAY,
    RTC_MONTH_JUNE,
    RTC_MONTH_JULY,
    RTC_MONTH_AUGUST,
    RTC_MONTH_SEPTEMBER,
    RTC_MONTH_OCTOBER,
    RTC_MONTH_NOVEMBER,
    RTC_MONTH_DECEMBER,
};

enum RTC_TimeOfDay
{
    RTC_TIMEOFDAY_MORN = 0,
    RTC_TIMEOFDAY_DAY,
    RTC_TIMEOFDAY_EVE,
    RTC_TIMEOFDAY_NITE,
    RTC_TIMEOFDAY_LATE,
};

void GF_InitRTCWork(void);
void GF_RTC_UpdateOnFrame(void);
void GF_RTC_GetDateTime_Callback(RTCResult result, void * data);
void GF_RTC_CopyDateTime(RTCDate * date, RTCTime * time);
void GF_RTC_CopyTime(RTCTime * time);
void GF_RTC_CopyDate(RTCDate * date);
s32 GF_RTC_TimeToSec(void);
s64 GF_RTC_DateTimeToSec(void);
s32 GF_RTC_GetDayOfYear(const RTCDate * date);
BOOL IsNighttime(void);
enum RTC_TimeOfDay GF_RTC_GetTimeOfDay(void);
enum RTC_TimeOfDay GF_RTC_GetTimeOfDayByHour(s32 hour);
s64 GF_RTC_TimeDelta(s64 first, s64 last);

#endif //POKEDIAMOND_GF_RTC_H
