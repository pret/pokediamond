#ifndef POKEDIAMOND_ARM7_OS_ALARM_H
#define POKEDIAMOND_ARM7_OS_ALARM_H

#include "nitro/OS_alarm_shared.h"

void OS_CreateAlarm(OSAlarm *alarm);
void OS_SetAlarm(OSAlarm *alarm, OSTick tick, OSAlarmHandler handler, void *arg);

#endif //POKEDIAMOND_ARM7_OS_ALARM_H
