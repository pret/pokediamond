#ifndef GUARD_SND_H
#define GUARD_SND_H

#include "nitro/types.h"

void SND_Enable(void);
void SND_SetOutputSelector(u8 leftOutputFrom, u8 rightOutputFrom, u8 outputCh1ToMixer, u8 outputCh3ToMixer);
void SND_SetMasterVolume(u8 vol);
void SND_StopChannel(s32 idx, BOOL hold);

#endif //GUARD_SND_H
