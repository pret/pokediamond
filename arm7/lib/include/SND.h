#ifndef GUARD_SND_H
#define GUARD_SND_H

#include "nitro/types.h"

void SND_Enable(void);
void SND_SetOutputSelector(int leftOutputFrom, int rightOutputFrom, int outputCh1ToMixer, int outputCh3ToMixer);

#endif //GUARD_SND_H
