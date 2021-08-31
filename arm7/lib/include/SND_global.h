#ifndef GUARD_SND_GLOBAL_H
#define GUARD_SND_GLOBAL_H

#include "nitro/types.h"

void SND_Enable(void);
void SND_Disable(void);
void SND_Shutdown(void);
void SND_BeginSleep(void);
void SND_EndSleep(void);
void SND_SetMasterVolume(int vol);
void SND_SetOutputSelector(
    int leftOutputFrom, int rightOutputFrom, int outputCh1ToMixer, int outputCh3ToMixer);

#endif // GUARD_SND_GLOBAL_H
