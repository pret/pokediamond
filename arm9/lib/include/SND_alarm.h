#ifndef GUARD_SND_ALARM_H
#define GUARD_SND_ALARM_H

#include "global.h"
#include "OS_alarm.h"

typedef void (*SNDAlarmCallback)(void *);

struct SNDAlarm {
    u8 enable;      // 0x00
    u8 id;          // 0x01
    u16 unk_2;      // 0x02
    OSTick tick;    // 0x04
    OSTick period;  // 0x0C
    OSAlarm alarm;  // 0x14
};  // size = 0x40

void SND_AlarmInit(void);
void SNDi_IncAlarmId(u32 idx);
u8 SNDi_SetAlarmHandler(u32 idx, SNDAlarmCallback cb, void *data);
void SNDi_CallAlarmHandler(s32 idx);

#define SND_ALARM_COUNT 8

#endif
