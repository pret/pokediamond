#ifndef POKEDIAMOND_OS_TICK_H
#define POKEDIAMOND_OS_TICK_H

#include "OS_timer.h"

void OS_InitTick(void);
u16 OS_IsTickAvailable(void);
void OSi_CountUpTick(void);
u64 OS_GetTick(void);

#endif
