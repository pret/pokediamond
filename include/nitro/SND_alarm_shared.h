/*
 * NOTE:
 * This file is shared between ARM9 and ARM7
 * DO NOT PUT PROC SPECIFIC CODE IN HERE
 * Thank You!
 */

/*
 * DO NOT INCLUDE THIS FILE DIRECTLY
 * Include SND_alarm.h from the specific proc's lib
 */

#ifndef POKEDIAMOND_SND_ALARM_SHARED_H
#define POKEDIAMOND_SND_ALARM_SHARED_H

#include "nitro/OS_alarm_shared.h"
#include "nitro/OS_tick_shared.h"

struct SNDAlarm
{
    u8 enable; // 0x00
    u8 id; // 0x01
    u16 unk_2; // 0x02
    OSTick tick; // 0x04
    OSTick period; // 0x0C
    OSAlarm alarm; // 0x14
}; // size = 0x40

#define SND_ALARM_COUNT 8

#endif // POKEDIAMOND_SND_ALARM_SHARED_H
