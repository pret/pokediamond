#ifndef POKEDIAMOND_ARM9_OS_ALARM_H
#define POKEDIAMOND_ARM9_OS_ALARM_H

#include "nitro/types.h"
#include "OS_thread.h"
#include "OS_tick.h"
#include "nitro/OS_alarm_shared.h"

struct OSiAlarmQueue
{
    OSAlarm *head;
    OSAlarm *tail;
};

static void OSi_SetTimer(OSAlarm *alarm);
void OS_InitAlarm(void);
BOOL OS_IsAlarmAvailable(void);
void OS_CreateAlarm(OSAlarm *alarm);
static void OSi_InsertAlarm(OSAlarm *alarm, OSTick fire);
void OS_SetAlarm(OSAlarm *alarm, OSTick tick, OSAlarmHandler handler, void *arg);
void OS_CancelAlarm(OSAlarm *alarm);
void OSi_AlarmHandler(void *arg);
static void OSi_ArrangeTimer(void);

#endif //POKEDIAMOND_ARM9_OS_ALARM_H
