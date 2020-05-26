//
// Created by mart on 4/23/20.
//

#ifndef POKEDIAMOND_OS_SYSTEM_H
#define POKEDIAMOND_OS_SYSTEM_H

#include "function_target.h"
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

ENUMS_ALWAYS_INT_ON
typedef enum {
    OS_INTRMODE_DISABLE_IRQ = HW_PSR_DISABLE_IRQ,
    OS_INTRMODE_DISABLE_FIQ = HW_PSR_DISABLE_FIQ,
    OS_INTRMODE_ENABLE = 0
} OSIntrMode;
ENUMS_ALWAYS_INT_RESET

OSIntrMode OS_EnableInterrupts(void);
OSIntrMode OS_DisableInterrupts(void);
OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
OSIntrMode OS_DisableInterrupts_IrqAndFiq(void);
OSIntrMode OS_RestoreInterrupts_IrqAndFiq(OSIntrMode state);
OSIntrMode OS_GetCpsrIrq(void);
OSProcMode OS_GetProcMode(void);
void OS_SpinWait(void);
void OS_WaitVBlankIntr(void);
void OS_WaitIrq(BOOL, u32);

#endif //POKEDIAMOND_OS_SYSTEM_H
