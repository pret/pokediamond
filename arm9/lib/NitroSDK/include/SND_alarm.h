#ifndef GUARD_SND_ALARM_H
#define GUARD_SND_ALARM_H

#include "nitro/types.h"
#include "nitro/SND_alarm_shared.h"

typedef void (*SNDAlarmCallback)(void *);

void SND_AlarmInit(void);
void SNDi_IncAlarmId(u32 idx);
u8 SNDi_SetAlarmHandler(u32 idx, SNDAlarmCallback cb, void *data);
void SNDi_CallAlarmHandler(s32 idx);

#endif
