#ifndef GUARD_SND_CHANNEL_H
#define GUARD_SND_CHANNEL_H

#include "nitro/types.h"

void SND_SetupChannelPcm(int chnIdx,
    const void *data,
    int format,
    int loop,
    int loopStart,
    int loopLen,
    int volume,
    int volumeDiv,
    int timer,
    int pan);

void SND_SetupChannelPsg(int chnIdx, int waveDuty, int volume, int volumeDiv, int timer, int pan);

void SND_SetupChannelNoise(int chnIdx, int volume, int volumeDiv, int timer, int pan);

void SND_StopChannel(int chnIdx, int hold);

void SND_SetChannelVolume(int chnIdx, int volume, int volumeDiv);
void SND_SetChannelTimer(int chnIdx, int timer);
void SND_SetChannelPan(int chnIdx, int pan);

BOOL SND_IsChannelActive(int idx);
void SND_SetMasterPan(int pan);
u32 SND_GetChannelControl(int idx);
void SNDi_SetSurroundDecay(int decay);

#endif // GUARD_SND_CHANNEL_H
