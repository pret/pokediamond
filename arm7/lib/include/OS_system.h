#ifndef POKEDIAMOND_ARM7_OS_SYSTEM_H
#define POKEDIAMOND_ARM7_OS_SYSTEM_H

#include "types.h"

//todo consts.h
#define HW_PSR_CPU_MODE_MASK       0x1f // CPU mode

#define HW_PSR_DISABLE_FIQ         0x40 // Disable FIQ
#define HW_PSR_DISABLE_IRQ         0x80 // Disable IRQ
#define HW_PSR_DISABLE_IRQ_FIQ     0xc0 // Disable FIQ and IRQ

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
    OS_INTRMODE_DISABLE_IRQ = HW_PSR_DISABLE_IRQ,
    OS_INTRMODE_DISABLE_FIQ = HW_PSR_DISABLE_FIQ,
    OS_INTRMODE_ENABLE = 0
} OSIntrMode;

OSIntrMode OS_EnableInterrupts(void);
OSIntrMode OS_DisableInterrupts(void);
OSIntrMode OS_RestoreInterrupts(register OSIntrMode state);
OSIntrMode OS_DisableInterrupts_IrqAndFiq(void);
OSIntrMode OS_RestoreInterrupts_IrqAndFiq(register OSIntrMode state);
OSProcMode OS_GetProcMode(void);
void OS_SpinWait(u32 cycle);

#endif //POKEDIAMOND_ARM7_OS_SYSTEM_H
