#ifndef GUARD_SND_UTIL_H
#define GUARD_SND_UTIL_H

#include "nitro/types.h"

void SND_CalcTimer(void);
u16 SND_CalcChannelVolume(s32 x);

extern const s16 SNDi_DecibelTable[0x80];

// not used in pokediamond
//extern const s16 SNDi_DecibelSquareTable[0x80];

#endif // GUARD_SND_UTIL_H
