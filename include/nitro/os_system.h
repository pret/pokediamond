//
// Created by mart on 4/23/20.
//

#ifndef POKEDIAMOND_OS_SYSTEM_H
#define POKEDIAMOND_OS_SYSTEM_H

#include "consts.h"

typedef enum {
    OS_PROCMODE_USER=16,
    OS_PROCMODE_FIQ=17,
    OS_PROCMODE_IRQ=18,
    OS_PROCMODE_SVC=19,
    OS_PROCMODE_ABORT=23,
    OS_PROCMODE_UNDEF=27,
    OS_PROCMODE_SYS=31
} OSProcMode;

typedef enum {
    OS_INTRMODE_IRQ_DISABLE = HW_PSR_IRQ_DISABLE,
    OS_INTRMODE_IRQ_ENABLE = 0
} OSIntrMode_Irq;

typedef enum {
    OS_INTRMODE_FIQ_DISABLE = HW_PSR_FIQ_DISABLE,
    OS_INTRMODE_FIQ_ENABLE = 0
} OSIntrMode_Fiq;

typedef union {
    OSIntrMode_Fiq mode_fiq;
    OSIntrMode_Irq mode_irq;
} OSIntrMode;

OSProcMode OS_GetProcMode();
OSIntrMode OS_DisableInterrupts();
OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

#endif //POKEDIAMOND_OS_SYSTEM_H
