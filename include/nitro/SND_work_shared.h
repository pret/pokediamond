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
#include "nitro/SND_bank_shared.h"
#include "nitro/SND_main_shared.h"
#include "nitro/SND_seq_shared.h"

#define SND_PLAYER_COUNT 16
#define SND_CHANNEL_COUNT 16
#define SND_TRACK_COUNT 32

struct SNDWork
{
    struct SNDExChannel channels[SND_CHANNEL_COUNT]; // 0x00
    struct SNDPlayer players[SND_PLAYER_COUNT]; // 0x540
    struct SNDTrack tracks[SND_TRACK_COUNT]; // 0x780
    struct SNDAlarm alarms[SND_ALARM_COUNT]; // 0xF80
}; // size = 0x1180

struct SNDSharedWork
{
    u32 finishedCommandTag; // 0x0
    u32 playerStatus; // 0x4
    u16 channelStatus; // 0x8
    u16 captureStatus; // 0xA
    u8 unk_C[0x14]; // 0xC
    struct
    {
        s16 localVars[16]; // local 0x0
        u32 tickCounter; // local 0x20
    } players[SND_PLAYER_COUNT]; // 0x20
    s16 globalVars[16]; // 0x260
}; // size = 0x280

struct SNDDriverInfo
{
    struct SNDWork work; // 0x0000
    u32 channelControls[SND_CHANNEL_COUNT]; // 0x1180
    struct SNDWork *workPtr; // 0x11C0
    u32 lockedChannels; // 0x11C4
    u8 unk_XXX[24]; // 0x11C8
}; // size = 0x11E0

struct SNDChannelInfo
{
    struct
    {
        BOOL active : 1;
        BOOL locked : 1;
    } flags; // 0x0
    u16 volume; // 0x4
    u8 pan; // 0x6
    u8 unk_7; // 0x7
    s32 envStatus; // 0x8
}; // size = 0xC

struct SNDPlayerInfo
{
    struct
    {
        BOOL active : 1;
        BOOL paused : 1;
    } flags; // 0x0
    u16 trackBitMask; // 0x4
    u16 tempo; // 0x6
    u8 volume; // 0x8
    u8 unk_9[3]; // 0x9
}; // size = 0xC

struct SNDTrackInfo
{
    u16 program; // 0x0
    u8 volume; // 0x2
    u8 expression; // 0x3

    s8 pitchBend; // 0x4
    u8 bendRange; // 0x5
    u8 pan; // 0x6
    s8 transpose; // 0x7

    u8 unk_8; // 0x8
    u8 chnCount; // 0x9
    u8 channel[SND_CHANNEL_COUNT]; // 0xA
}; // size = 0x1A

extern struct SNDWork SNDi_Work;
extern struct SNDSharedWork *SNDi_SharedWork;

#endif // POKEDIAMOND_SND_WORK_SHARED_H
