#ifndef POKEDIAMOND_ARM7_OS_RESET_H
#define POKEDIAMOND_ARM7_OS_RESET_H

#include "nitro/types.h"
#include "nitro/OS_reset_shared.h"
#include "PXI_fifo.h"

void OS_InitReset(void);
BOOL OS_IsResetOccurred(void);
static void OSi_CommonCallback(PXIFifoTag tag, u32 data, BOOL err);
static void OSi_SendToPxi(u16 data);
void OS_ResetSystem(void);

#endif //POKEDIAMOND_ARM7_OS_RESET_H
