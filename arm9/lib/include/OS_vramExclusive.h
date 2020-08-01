#ifndef POKEDIAMOND_OS_VRAMEXCLUSIVE_H
#define POKEDIAMOND_OS_VRAMEXCLUSIVE_H

#include "nitro/types.h"

void OSi_InitVramExclusive(void);
BOOL OSi_TryLockVram(u16 bank, u16 lockId);
void OSi_UnlockVram(u16 bank, u16 lockId);

#endif //POKEDIAMOND_OS_VRAMEXCLUSIVE_H
