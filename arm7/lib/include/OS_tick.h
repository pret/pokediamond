#ifndef POKEDIAMOND_OS_TICK_H
#define POKEDIAMOND_OS_TICK_H

#include "nitro/OS_tick_shared.h"

void OS_InitTick(void);
u16 OS_IsTickAvailable(void);
void OSi_CountUpTick(void);
OSTick OS_GetTick(void);

#endif
