/*
 * NOTE:
 * This file is shared between ARM9 and ARM7
 * DO NOT PUT PROC SPECIFIC CODE IN HERE
 * Thank You!
 */

/*
 * DO NOT INCLUDE THIS FILE DIRECTLY
 * Include SND_work.h from the specific proc's lib
 */

#ifndef POKEDIAMOND_SND_WORK_SHARED_H
#define POKEDIAMOND_SND_WORK_SHARED_H

#include "nitro/SND_alarm_shared.h"
#include "nitro/SND_main_shared.h"
 
#define SND_PLAYER_COUNT 16
#define SND_CHANNEL_COUNT 16
#define SND_TRACK_COUNT 32

struct SNDWork {
    struct SNDExChannel channels[SND_CHANNEL_COUNT];    // 0x00
    struct SNDPlayer players[SND_PLAYER_COUNT];         // 0x540
    struct SNDTrack tracks[SND_TRACK_COUNT];            // 0x780
    struct SNDAlarm alarms[SND_ALARM_COUNT];            // 0xF80
};  // size = 0x1180

struct SNDSharedWork {
    u32 finishedCommandTag;                 // 0x0
    u32 playerStatus;                       // 0x4
    u16 channelStatus;                      // 0x8
    u16 captureStatus;                      // 0xA
    u8 unk_C[0x14];                         // 0xC
    struct {
        s16 localVars[16];  // local 0x0
        u32 tickCounter;    // local 0x20
    } players[SND_PLAYER_COUNT];            // 0x20
    s16 globalVars[16];                     // 0x260
};  // size = 0x280

extern struct SNDWork SNDi_Work;
extern struct SNDSharedWork *SNDi_SharedWork;
 
 #endif //POKEDIAMOND_SND_WORK_SHARED_H
