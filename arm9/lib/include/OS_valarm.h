#ifndef POKEDIAMOND_OS_VALARM_H
#define POKEDIAMOND_OS_VALARM_H

#include "nitro/types.h"
#include "OS_alarm.h"

typedef struct OSiVAlarm OSVAlarm;
struct OSiVAlarm
{
    OSAlarmHandler handler;
    void *arg;
    u32 tag;
    u32 frame;
    s16 fire;
    s16 delay;
    OSVAlarm *prev;
    OSVAlarm *next;
    BOOL period;
    BOOL finish;
    BOOL canceled;
};

void OS_InitVAlarm(void);

#endif //POKEDIAMOND_OS_VALARM_H
