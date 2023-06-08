#ifndef GUARD_SND_MAIN_H
#define GUARD_SND_MAIN_H

#include "nitro/types.h"

#include "nitro/SND_main_shared.h"

void SNDi_UnlockMutex(void);
void SNDi_LockMutex(void);
void SND_Init(void);

#endif // GUARD_SND_MAIN_H
