#ifndef GUARD_SND_WORK_H
#define GUARD_SND_WORK_H

#include "global.h"

#include "SND_main.h"
#include "nitro/SND_work_shared.h"

struct SNDDriverInfo {
    struct SNDWork work;                    // 0x0000
    u32 channelControls[SND_CHANNEL_COUNT]; // 0x1180
    struct SNDWork *workPtr;                // 0x11C0
    u32 lockedChannels;                     // 0x11C4
    u8 unk_XXX[24];                         // 0x11C8
};  // size = 0x11E0

struct SNDChannelInfo {
    struct {
        BOOL active : 1;
        BOOL locked: 1;
    } flags;        // 0x0
    u16 volume;     // 0x4
    u8 pan;         // 0x6
    u8 unk_7;       // 0x7
    s32 envStatus;  // 0x8
};  // size = 0xC

struct SNDPlayerInfo {
    struct {
        BOOL active : 1;
        BOOL paused : 1;
    } flags;            // 0x0
    u16 trackBitMask;   // 0x4
    u16 tempo;          // 0x6
    u8 volume;          // 0x8
    u8 unk_9[3];        // 0x9
};  // size = 0xC

struct SNDTrackInfo {
    u16 program;        // 0x0
    u8 volume;          // 0x2
    u8 expression;      // 0x3

    s8 pitchBend;       // 0x4
    u8 bendRange;       // 0x5
    u8 pan;             // 0x6
    s8 transpose;       // 0x7

    u8 unk_8;           // 0x8
    u8 chnCount;        // 0x9
    u8 channel[SND_CHANNEL_COUNT];  // 0xA
};  // size = 0x1A

u32 SND_GetPlayerStatus(void);
u16 SND_GetChannelStatus(void);
//u16 SND_GetCaptureStatus(void);
u32 SND_GetPlayerTickCounter(u32 playerId);
//s16 SND_GetPlayerLocalVariable(u32 playerId, u32 var);
//s16 SND_GetPlayerGlobalVariable(u32 var);
//BOOL SND_ReadChannelInfo(const SNDDriverInfo *driverInfo, s32 chnId, SNDChannelInfo *chnInfo);
//BOOL SND_ReadPlayerInfo(const SNDDriverInfo *driverInfo, s32 playerId, s32 trackId, SNDPlayerInfo *playerInfo);
//BOOL SND_ReadTrackInfo(const SNDDriverInfo *driverInfo s32 playerId, s32 trackId, SNDTrackInfo *trackInfo);
u32 SNDi_GetFinishedCommandTag(void);
void SNDi_InitSharedWork(struct SNDSharedWork *sw);

extern struct SNDSharedWork *SNDi_SharedWork;

#endif // GUARD_SND_WORK_H
