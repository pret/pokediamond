#ifndef POKEDIAMOND_ARM9_OS_TICK_H
#define POKEDIAMOND_ARM9_OS_TICK_H

#include "consts.h"
#include "OS_timer.h"
#include "nitro/OS_tick_shared.h"

#define OSi_TICK_TIMERCONTROL        (REG_OS_TM0CNT_H_E_MASK | REG_OS_TM0CNT_H_I_MASK | OS_TIMER_PRESCALER_64)

void OS_InitTick(void);
BOOL OS_IsTickAvailable(void);
OSTick OS_GetTick(void);
u16 OS_GetTickLo(void);

#endif //POKEDIAMOND_ARM9_OS_TICK_H
