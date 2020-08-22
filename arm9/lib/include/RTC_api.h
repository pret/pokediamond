#ifndef NITRO_RTC_API_H_
#define NITRO_RTC_API_H_

typedef enum RTCWeek
{
    RTC_WEEK_SUNDAY = 0,
    RTC_WEEK_MONDAY,
    RTC_WEEK_TUESDAY,
    RTC_WEEK_WEDNESDAY,
    RTC_WEEK_THURSDAY,
    RTC_WEEK_FRIDAY,
    RTC_WEEK_SATURDAY,
    RTC_WEEK_MAX
}
    RTCWeek;

typedef struct RTCDate
{
    u32 year;
    u32 month;
    u32 day;
    RTCWeek week;
}
    RTCDate;

typedef struct RTCTime
{
    u32 hour;
    u32 minute;
    u32 second;
}
    RTCTime;

#endif //NITRO_RTC_API_H_
