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
    OS_INTRMODE_DISABLE = HW_PSR_IRQ_DISABLE,
    OS_INTRMODE_ENABLE = 0
} OSIntrMode;

OSIntrMode OS_EnableInterrupts();
OSIntrMode OS_DisableInterrupts();
OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
OSIntrMode OS_DisableInterrupts_IrqAndFiq();
OSIntrMode OS_RestoreInterrupts_IrqAndFiq(OSIntrMode state);
OSProcMode OS_GetProcMode();


#endif //POKEDIAMOND_OS_SYSTEM_H
