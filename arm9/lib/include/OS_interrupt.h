#ifndef POKEDIAMOND_ARM9_OS_INTERRUPT_H
#define POKEDIAMOND_ARM9_OS_INTERRUPT_H

#include "consts.h"
#include "nitro/OS_interrupt_shared.h"

#define OS_IE_TIMER0        (1UL << REG_OS_IE_T0_SHIFT)
#define OS_IE_TIMER1        (1UL << REG_OS_IE_T1_SHIFT)

extern OSIrqFunction OS_IRQTable[];
extern OSIrqCallbackInfo OSi_IrqCallbackInfo[8];

void OS_InitIrqTable(void);
void OS_SetIrqFunction(OSIrqMask intrBit, OSIrqFunction function);
OSIrqFunction OS_GetIrqFunction(OSIrqMask intrBit);
void OSi_EnterDmaCallback(u32 dmaNo, void (*callback) (void *), void *arg);
void OSi_EnterTimerCallback(u32 timerNo, void (*callback) (void *), void *arg);
OSIrqMask OS_SetIrqMask(OSIrqMask mask);
OSIrqMask OS_EnableIrqMask(OSIrqMask mask);
OSIrqMask OS_DisableIrqMask(OSIrqMask mask);
OSIrqMask OS_ResetRequestIrqMask(OSIrqMask mask);
void OS_SetIrqStackChecker(void);

#endif //POKEDIAMOND_ARM9_OS_INTERRUPT_H
