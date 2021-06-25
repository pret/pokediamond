#include "SND_alarm.h"

#include "SND_work.h"
#include "OS_alarm.h"
#include "OS_tick.h"
#include "PXI_fifo.h"

static void AlarmHandler(void *msg);

void SND_AlarmInit(void) {
    for (s32 i = 0; i < SND_ALARM_COUNT; i++) {
        SNDi_Work.alarms[i].enable = 0;
        SNDi_Work.alarms[i].id = 0;
    }
}

void SND_SetupAlarm(s32 idx, OSTick tick, OSTick period, u32 id) {
    struct SNDAlarm *alarm = &SNDi_Work.alarms[idx];

    if (alarm->enable) {
        OS_CancelAlarm(&alarm->alarm);
        alarm->enable = 0;
    }

    alarm->tick = tick;
    alarm->period = period;
    alarm->id = (u8)id;
}

void SND_StartAlarm(s32 idx) {
    OSTick tick;
    OSTick period;
    
    struct SNDAlarm *alarm = &SNDi_Work.alarms[idx];

    if (alarm->enable != 0) {
        OS_CancelAlarm(&alarm->alarm);
        alarm->enable = 0;
    }

    tick = alarm->tick;
    period = alarm->period;
    s32 arg = idx | (alarm->id << 8);

    OS_CreateAlarm(&alarm->alarm);

    if (period == 0) {
        OS_SetAlarm(&alarm->alarm, tick, AlarmHandler, (void *)arg);
    } else {
        OS_SetPeriodicAlarm(&alarm->alarm, tick + OS_GetTick(), period, AlarmHandler, (void *)arg);
    }

    alarm->enable = 1;
}

void SND_StopAlarm(s32 idx) {
    struct SNDAlarm *alarm = &SNDi_Work.alarms[idx];

    if (alarm->enable != 0) {
        OS_CancelAlarm(&alarm->alarm);
        alarm->id++;
        alarm->enable = 0;
    }
}

static void AlarmHandler(void *msg) {
    while (PXI_SendWordByFifo(7, (u32)msg, 0) < 0) {
        // nothing
    }
}
