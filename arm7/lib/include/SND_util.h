#ifndef GUARD_SND_UTIL_H
#define GUARD_SND_UTIL_H

#include "nitro/types.h"

#define SND_DECIBEL_SQUARE_TABLE_COUNT 

u16 SND_CalcRandom(void);
s8 SND_SinIdx(s32 index);

u16 SND_CalcChannelVolume(s32 value);
u16 SND_CalcTimer(s32 timer, s32 pitch);

extern const s16 SNDi_DecibelSquareTable[128];

#endif //GUARD_SND_UTIL_H
