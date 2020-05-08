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
extern OSIrqCallbackInfo OSi_IrqCallbackInfo[7+1];

void OS_InitIrqTable();
void OS_SetIrqFunction(OSIrqMask intrBit, OSIrqFunction function);
OSIrqFunction OS_GetIrqFunction(OSIrqMask intrBit);
void OSi_EnterDmaCallback(u32 dmaNo, void (*callback) (void *), void *arg);

#endif //POKEDIAMOND_OS_INTERRUPT_H
