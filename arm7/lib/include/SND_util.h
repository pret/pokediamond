#ifndef GUARD_SND_UTIL_H
#define GUARD_SND_UTIL_H

#include "nitro/types.h"

#define SND_VOL_DB_MIN (-723)

u16 SND_CalcRandom(void);
s8 SND_SinIdx(int index);

u16 SND_CalcChannelVolume(int value);
u16 SND_CalcTimer(int timer, int pitch);

extern const s16 SNDi_DecibelSquareTable[128];

#endif //GUARD_SND_UTIL_H
