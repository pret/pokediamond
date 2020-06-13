#ifndef POKEDIAMOND_OS_TICK_H
#define POKEDIAMOND_OS_TICK_H

#include "consts.h"
#include "OS_timer.h"

typedef u64 OSTick;

#define OS_SYSTEM_CLOCK HW_SYSTEM_CLOCK

#define OS_MilliSecondsToTicks(msec) ((OSTick)(((OS_SYSTEM_CLOCK/1000) * (u64)(msec)) / 64))

#define OSi_TICK_TIMERCONTROL        (REG_OS_TM0CNT_H_E_MASK | REG_OS_TM0CNT_H_I_MASK | OS_TIMER_PRESCALER_64)

void OS_InitTick(void);
BOOL OS_IsTickAvailable(void);
static void OSi_CountUpTick(void);
OSTick OS_GetTick(void);
u16 OS_GetTickLo(void);

#endif //POKEDIAMOND_OS_TICK_H
