//
// Created by red031000 on 2020-05-07.
//

#ifndef POKEDIAMOND_OS_INTERRUPT_H
#define POKEDIAMOND_OS_INTERRUPT_H

#include "types.h"

typedef void (*OSIrqFunction) (void);

typedef struct
{
    void (*func) (void *);
    u32 enable;
    void* arg;
} OSIrqCallbackInfo;

typedef u32 OSIrqMask;

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

#endif //POKEDIAMOND_OS_INTERRUPT_H
