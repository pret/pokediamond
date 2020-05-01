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

#pragma enumsalwaysint on
typedef enum {
    OS_INTRMODE_DISABLE_IRQ = HW_PSR_DISABLE_IRQ,
    OS_INTRMODE_DISABLE_FIQ = HW_PSR_DISABLE_FIQ,
    OS_INTRMODE_ENABLE = 0
} OSIntrMode;
#pragma enumsalwaysint reset

OSIntrMode OS_EnableInterrupts();
OSIntrMode OS_DisableInterrupts();
OSIntrMode OS_RestoreInterrupts(register OSIntrMode state);
OSIntrMode OS_DisableInterrupts_IrqAndFiq();
OSIntrMode OS_RestoreInterrupts_IrqAndFiq(register OSIntrMode state);
OSIntrMode OS_GetCpsrIrq();
OSProcMode OS_GetProcMode();
void OS_SpinWait();
void OS_WaitVBlankIntr();

#endif //POKEDIAMOND_OS_SYSTEM_H
