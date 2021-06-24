#ifndef GUARD_SND_ALARM_H
#define GUARD_SND_ALARM_H

#include "global.h"
#include "SND_alarm_shared.h"

void SND_StopAlarm(u32 idx);
void SND_StartAlarm(u32 idx);
void SND_SetupAlarm();
void SND_AlarmInit();

#endif //GUARD_SND_ALARM_H