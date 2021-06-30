#ifndef GUARD_SND_CHANNEL_H
#define GUARD_SND_CHANNEL_H

#include "nitro/types.h"

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

// TODO move this function to SND_exChannel.c
u16 CalcDecayCoeff(s32 value);

#endif //GUARD_SND_CHANNEL_H
