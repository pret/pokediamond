#ifndef POKEDIAMOND_OS_ALARM_H
#define POKEDIAMOND_OS_ALARM_H

#include "nitro/types.h"
#include "OS_thread.h"
#include "OS_tick.h"

typedef void (*OSAlarmHandler) (void *);

struct OSiAlarm
{
    OSAlarmHandler handler;
    void *arg;

    u32 tag;
    OSTick fire;
    OSAlarm *prev;
    OSAlarm *next;

    OSTick period;
    OSTick start;
};

void OS_CancelAlarm(OSAlarm *alarm);
void OS_CreateAlarm(OSAlarm *alarm);
void OS_SetAlarm(OSAlarm *alarm, OSTick tick, OSAlarmHandler handler, void *arg);

#endif //POKEDIAMOND_OS_ALARM_H
