#ifndef POKEDIAMOND_OS_IRQHANDLER_H
#define POKEDIAMOND_OS_IRQHANDLER_H

#include "consts.h"
#include "OS_interrupt.h"

static inline void OS_ClearIrqCheckFlag(OSIrqMask intr)
{
    *(vu32 *)HW_INTR_CHECK_BUF &= (u32)~intr;
}

static inline OSIrqMask OS_GetIrqCheckFlag(void)
{
    return *(OSIrqMask *)HW_INTR_CHECK_BUF;
}

void OS_WaitIrq(BOOL param1, u32 param2);

#endif //POKEDIAMOND_OS_IRQHANDLER_H
