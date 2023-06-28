#include "global.h"
#include "MI_memory.h"
#include "gf_rtc.h"
#include "RTC_convert.h"

typedef struct GF_RTC_Work
{
    BOOL getDateTimeSuccess;
    BOOL getDateTimeLock;
    s32 getDateTimeSleep;
    RTCResult getDateTimeErrorCode;
    RTCDate date; // 10
    RTCTime time; // 20
    RTCDate date_async; // 2C
    RTCTime time_async; // 3C
} GF_RTC_Work;

GF_RTC_Work sGFRTCWork;

#define MAX_SECONDS     (3155759999ll)

void GF_RTC_GetDateTime(GF_RTC_Work * work);

void GF_InitRTCWork(void)
{
    RTC_Init();
    memset(&sGFRTCWork, 0, sizeof(sGFRTCWork)); //todo: figure out how to use memset
    sGFRTCWork.getDateTimeSuccess = FALSE;
    sGFRTCWork.getDateTimeLock = FALSE;
    sGFRTCWork.getDateTimeSleep = 0;
    GF_RTC_GetDateTime(&sGFRTCWork);
}

void GF_RTC_UpdateOnFrame(void)
{
    if (!sGFRTCWork.getDateTimeLock)
    {
        if (++sGFRTCWork.getDateTimeSleep > 10)
        {
            sGFRTCWork.getDateTimeSleep = 0;
            GF_RTC_GetDateTime(&sGFRTCWork);
        }
    }
}

void GF_RTC_GetDateTime_Callback(RTCResult result, void * data)
{
    GF_RTC_Work * work = (GF_RTC_Work *)data;
    work->getDateTimeErrorCode = result;
    GF_ASSERT(result == RTC_RESULT_SUCCESS);
    work->getDateTimeSuccess = TRUE;
    work->date = work->date_async;
    work->time = work->time_async;
    work->getDateTimeLock = FALSE;
}

void GF_RTC_GetDateTime(GF_RTC_Work * work)
{
    work->getDateTimeLock = TRUE;
    RTCResult result = RTC_GetDateTimeAsync(&work->date_async, &work->time_async, GF_RTC_GetDateTime_Callback, work);
    work->getDateTimeErrorCode = result;
    GF_ASSERT(result == RTC_RESULT_SUCCESS);
}

void GF_RTC_CopyDateTime(RTCDate * date, RTCTime * time)
{
    GF_ASSERT(sGFRTCWork.getDateTimeSuccess == TRUE);
    *date = sGFRTCWork.date;
    *time = sGFRTCWork.time;
}

void GF_RTC_CopyTime(RTCTime * time)
{
    GF_ASSERT(sGFRTCWork.getDateTimeSuccess == TRUE);
    *time = sGFRTCWork.time;
}

void GF_RTC_CopyDate(RTCDate * date)
{
    GF_ASSERT(sGFRTCWork.getDateTimeSuccess == TRUE);
    *date = sGFRTCWork.date;
}

s32 GF_RTC_TimeToSec(void)
{
    RTCTime* time = &sGFRTCWork.time;
    return 60 * time->minute + 3600 * time->hour + time->second;
}

s64 GF_RTC_DateTimeToSec(void)
{
    return RTC_ConvertDateTimeToSecond(&sGFRTCWork.date, &sGFRTCWork.time);
}

static inline BOOL IsLeapYear(s32 year)
{
    return ((year % 4) == 0 && (year % 100) != 0) || ((year % 400) == 0);
}

s32 GF_RTC_GetDayOfYear(const RTCDate * date)
{
    RTCDate date_stack;
    s32 days;
    static const u16 sGF_DaysPerMonth[] = {
        0,   // Jan
        31,  // Feb
        59,  // Mar
        90,  // Apr
        120, // May
        151, // Jun
        181, // Jul
        212, // Aug
        243, // Sep
        273, // Oct
        304, // Nov
        334, // Dec
    };

    days = date->day;
    days += sGF_DaysPerMonth[date->month - 1];
    if (date->month >= RTC_MONTH_MARCH && IsLeapYear(date->year))
        days++;
    date_stack = *date;
    date_stack.month = RTC_MONTH_JANUARY;
    date_stack.day = 1;
    RTC_ConvertDateToDay(&date_stack);
    RTC_ConvertDateToDay(date);
    return days;
}

BOOL IsNighttime(void)
{
    switch (GF_RTC_GetTimeOfDay())
    {
        case RTC_TIMEOFDAY_NITE:
        case RTC_TIMEOFDAY_LATE:
            return TRUE;
        default:
            return FALSE;
    }
}

enum RTC_TimeOfDay GF_RTC_GetTimeOfDay(void)
{
    RTCTime time;
    GF_RTC_CopyTime(&time);
    return GF_RTC_GetTimeOfDayByHour(time.hour);
}

enum RTC_TimeOfDay GF_RTC_GetTimeOfDayByHour(s32 hour)
{
    static const u8 sTimeOfDayByHour[] = {
        // 00:00 - 03:59
        RTC_TIMEOFDAY_LATE, RTC_TIMEOFDAY_LATE, RTC_TIMEOFDAY_LATE, RTC_TIMEOFDAY_LATE,
        // 04:00 - 09:59
        RTC_TIMEOFDAY_MORN, RTC_TIMEOFDAY_MORN, RTC_TIMEOFDAY_MORN, RTC_TIMEOFDAY_MORN, RTC_TIMEOFDAY_MORN, RTC_TIMEOFDAY_MORN,
        // 10:00 - 16:59
        RTC_TIMEOFDAY_DAY, RTC_TIMEOFDAY_DAY, RTC_TIMEOFDAY_DAY, RTC_TIMEOFDAY_DAY, RTC_TIMEOFDAY_DAY, RTC_TIMEOFDAY_DAY, RTC_TIMEOFDAY_DAY,
        // 17:00 - 19:59
        RTC_TIMEOFDAY_EVE, RTC_TIMEOFDAY_EVE, RTC_TIMEOFDAY_EVE,
        // 20:00 - 23:59
        RTC_TIMEOFDAY_NITE, RTC_TIMEOFDAY_NITE, RTC_TIMEOFDAY_NITE, RTC_TIMEOFDAY_NITE,
    };

    GF_ASSERT(hour >= 0 && hour < 24);
    return (enum RTC_TimeOfDay)sTimeOfDayByHour[hour];
}

s64 GF_RTC_TimeDelta(s64 first, s64 last)
{
    RTCDate maxDate = { 99, 12, 31, RTC_WEEK_SUNDAY };
    RTCTime maxTime = { 23, 59, 59 };

    s64 check = RTC_ConvertDateTimeToSecond(&maxDate, &maxTime);
    GF_ASSERT(check == MAX_SECONDS);
    if (first < last)
        return last - first;
    else
        return last + (MAX_SECONDS - first);
}
