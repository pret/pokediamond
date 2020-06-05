#ifndef POKEDIAMOND_ARM9_OS_SYSTEM_H
#define POKEDIAMOND_ARM9_OS_SYSTEM_H

#include "function_target.h"
#include "consts.h"
#include "nitro/OS_system_shared.h"

OSIntrMode OS_EnableInterrupts(void);
OSIntrMode OS_DisableInterrupts(void);
OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
OSIntrMode OS_DisableInterrupts_IrqAndFiq(void);
OSIntrMode OS_RestoreInterrupts_IrqAndFiq(OSIntrMode state);
OSIntrMode OS_GetCpsrIrq(void);
OSProcMode OS_GetProcMode(void);
void OS_SpinWait(u32 cycles);
void OS_WaitVBlankIntr(void);

#endif //POKEDIAMOND_ARM9_OS_SYSTEM_H
