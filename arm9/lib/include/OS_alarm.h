#ifndef POKEDIAMOND_ARM9_OS_ALARM_H
#define POKEDIAMOND_ARM9_OS_ALARM_H

#include "nitro/types.h"
#include "OS_thread.h"
#include "OS_tick.h"
#include "nitro/OS_alarm_shared.h"

void OS_CancelAlarm(OSAlarm *alarm);
void OS_CreateAlarm(OSAlarm *alarm);
void OS_SetAlarm(OSAlarm *alarm, OSTick tick, OSAlarmHandler handler, void *arg);

#endif //POKEDIAMOND_ARM9_OS_ALARM_H
