#ifndef POKEDIAMOND_ARM9_OS_INTERRUPT_H
#define POKEDIAMOND_ARM9_OS_INTERRUPT_H

#include "registers.h"
#include "mmap.h"
#include "nitro/OS_interrupt_shared.h"

#define REG_OS_IME_IME_SHIFT                               0

#define OS_IME_DISABLE      (0UL << REG_OS_IME_IME_SHIFT)
#define OS_IME_ENABLE       (1UL << REG_OS_IME_IME_SHIFT)

#define OS_IE_V_COUNT       (1UL << REG_OS_IE_VE_SHIFT)
#define OS_IE_TIMER0        (1UL << REG_OS_IE_T0_SHIFT)
#define OS_IE_TIMER1        (1UL << REG_OS_IE_T1_SHIFT)
#define OS_IE_TIMER2        (1UL << REG_OS_IE_T2_SHIFT)
#define OS_IE_TIMER3        (1UL << REG_OS_IE_T3_SHIFT)
#define OS_IE_SPFIFO_RECV   (1UL << REG_OS_IE_IFN_SHIFT)
#define OS_IE_CARD_DATA     (1UL << REG_OS_IE_MC_SHIFT)

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

static inline BOOL OS_DisableIrq(void)
{
    u16     prep = reg_OS_IME;
    reg_OS_IME = OS_IME_DISABLE;
    return (BOOL)prep;
}

static inline BOOL OS_EnableIrq(void)
{
    u16     prep = reg_OS_IME;
    reg_OS_IME = OS_IME_ENABLE;
    return (BOOL)prep;
}

static inline BOOL OS_RestoreIrq(BOOL enable)
{
    u16     prep = reg_OS_IME;
    reg_OS_IME = (u16)enable;
    return (BOOL)prep;
}

static inline OSIrqMask OS_GetIrqMask(void)
{
    return reg_OS_IE;
}

#endif //POKEDIAMOND_ARM9_OS_INTERRUPT_H
