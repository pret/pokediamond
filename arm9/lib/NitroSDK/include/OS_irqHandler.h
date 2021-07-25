#ifndef POKEDIAMOND_OS_IRQHANDLER_H
#define POKEDIAMOND_OS_IRQHANDLER_H

#include "OS_interrupt.h"
#include "mmap.h"

static inline void OS_ClearIrqCheckFlag(OSIrqMask intr)
{
    *(vu32 *)HW_INTR_CHECK_BUF &= (u32)~intr;
}

static inline OSIrqMask OS_GetIrqCheckFlag(void)
{
    return *(OSIrqMask *)HW_INTR_CHECK_BUF;
}

void OS_IrqHandler(void);
void OS_IrqHandler_ThreadSwitch(void);
void OS_WaitIrq(BOOL clear, OSIrqMask irqFlags);

#endif //POKEDIAMOND_OS_IRQHANDLER_H
