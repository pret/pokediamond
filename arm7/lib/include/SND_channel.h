#ifndef GUARD_SND_CHANNEL_H
#define GUARD_SND_CHANNEL_H

#include "nitro/types.h"

#include "SND_exChannel.h"

void SNDi_SetSurroundDecay(int decay);

void SND_SetupChannelPcm(
    s32 chnIdx,
    const void *data,
    s32 format,
    s32 loop,
    s32 loopStart,
    s32 loopLen,
    s32 volume,
    s32 volumeDiv,
    s32 timer,
    s32 pan
);

void SND_SetupChannelPsg(
    s32 chnIdx,
    s32 waveDuty,
    s32 volume,
    s32 volumeDiv,
    s32 timer,
    s32 pan
);

void SND_SetupChannelNoise(
    s32 chnIdx,
    s32 volume,
    s32 volumeDiv,
    s32 timer,
    s32 pan
);

void SND_StopChannel(s32 chnIdx, s32 hold);

void SND_SetChannelVolume(s32 chnIdx, s32 volume, s32 volumeDiv);
void SND_SetChannelPan(s32 chnIdx, s32 pan);
void SND_SetChannelTimer(s32 chnIdx, s32 timer);

u32 SND_GetChannelControl(int idx);

// TODO move this function to SND_exChannel.c
u16 CalcDecayCoeff(int value);

#endif //GUARD_SND_CHANNEL_H
