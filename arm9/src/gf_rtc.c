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

void GF_RTC_GetDateTime(GF_RTC_Work * work);

THUMB_FUNC void GF_InitRTCWork(void)
{
    RTC_Init();
    __builtin__clear(&sGFRTCWork, sizeof(sGFRTCWork));
    sGFRTCWork.getDateTimeSuccess = FALSE;
    sGFRTCWork.getDateTimeLock = FALSE;
    sGFRTCWork.getDateTimeSleep = 0;
    GF_RTC_GetDateTime(&sGFRTCWork);
}

THUMB_FUNC void GF_RTC_UpdateOnFrame(void)
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

THUMB_FUNC void GF_RTC_GetDateTime_Callback(RTCResult result, void * data)
{
    GF_RTC_Work * work = (GF_RTC_Work *)data;
    work->getDateTimeErrorCode = result;
    GF_ASSERT(result == RTC_RESULT_SUCCESS);
    work->getDateTimeSuccess = TRUE;
    work->date = work->date_async;
    work->time = work->time_async;
    work->getDateTimeLock = FALSE;
}

THUMB_FUNC void GF_RTC_GetDateTime(GF_RTC_Work * work)
{
    work->getDateTimeLock = TRUE;
    RTCResult result = RTC_GetDateTimeAsync(&work->date_async, &work->time_async, GF_RTC_GetDateTime_Callback, work);
    work->getDateTimeErrorCode = result;
    GF_ASSERT(result == RTC_RESULT_SUCCESS);
}

THUMB_FUNC void GF_RTC_CopyDateTime(RTCDate * date, RTCTime * time)
{
    GF_ASSERT(sGFRTCWork.getDateTimeSuccess == TRUE);
    *date = sGFRTCWork.date;
    *time = sGFRTCWork.time;
}

THUMB_FUNC void GF_RTC_CopyTime(RTCTime * time)
{
    GF_ASSERT(sGFRTCWork.getDateTimeSuccess == TRUE);
    *time = sGFRTCWork.time;
}

THUMB_FUNC void GF_RTC_CopyDate(RTCDate * date)
{
    GF_ASSERT(sGFRTCWork.getDateTimeSuccess == TRUE);
    *date = sGFRTCWork.date;
}

THUMB_FUNC s32 GF_RTC_TimeToSec(void)
{
    RTCTime* time = &sGFRTCWork.time;
    return 60 * time->minute + 3600 * time->hour + time->second;
}

THUMB_FUNC s64 GF_RTC_DateTimeToSec(void)
{
    return RTC_ConvertDateTimeToSecond(&sGFRTCWork.date, &sGFRTCWork.time);
}

static inline BOOL IsLeapYear(s32 year)
{
    return ((year % 4) == 0 && (year % 100) != 0) || ((year % 400) == 0);
}

THUMB_FUNC s32 FUN_02012710(const RTCDate * date)
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

enum RTC_TimeOfDay GF_RTC_GetTimeOfDay(void);
enum RTC_TimeOfDay GF_RTC_GetTimeOfDayByHour(s32 hour);

THUMB_FUNC BOOL IsNighttime(void)
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

THUMB_FUNC enum RTC_TimeOfDay GF_RTC_GetTimeOfDay(void)
{
    RTCTime time;
    GF_RTC_CopyTime(&time);
    return GF_RTC_GetTimeOfDayByHour(time.hour);
}

THUMB_FUNC enum RTC_TimeOfDay GF_RTC_GetTimeOfDayByHour(s32 hour)
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
    return sTimeOfDayByHour[hour];
}

THUMB_FUNC s64 FUN_020127C0(s64 r4r7, s64 r5r6)
{
    RTCDate maxDate = { 99, 12, 31, 0 };
    RTCTime maxTime = { 23, 59, 59 };

    s64 r2r3 = RTC_ConvertDateTimeToSecond(&maxDate, &maxTime);
    GF_ASSERT(r2r3 == 3155759999ll);
    if (r4r7 < r5r6)
        return r5r6 - r4r7;
    else
        return r5r6 + (3155759999ll - r4r7);
}
