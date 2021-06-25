#ifndef GUARD_SND_ALARM_H
#define GUARD_SND_ALARM_H

#include "global.h"
#include "nitro/SND_alarm_shared.h"

void SND_AlarmInit(void);
void SND_SetupAlarm(s32 idx, OSTick tick, OSTick period, u32 id);
void SND_StartAlarm(s32 idx);
void SND_StopAlarm(s32 idx);

#endif //GUARD_SND_ALARM_H
