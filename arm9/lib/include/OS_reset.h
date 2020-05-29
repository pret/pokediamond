//
// Created by red031000 on 2020-05-06.
//

#ifndef POKEDIAMOND_OS_RESET_H
#define POKEDIAMOND_OS_RESET_H

#include "consts.h"
#include "PXI_fifo.h"

#define OS_PXI_COMMAND_MASK 0x7f00
#define OS_PXI_COMMAND_SHIFT 8
#define OS_PXI_COMMAND_RESET 0x10

void OS_InitReset(void);
static void OSi_CommonCallback(PXIFifoTag tag, u32 data, BOOL err);
static void OSi_SendToPxi(u16 data);
void OS_ResetSystem(u32 parameter);

static inline u32 OS_GetResetParameter(void)
{
    return (u32)*(u32 *)HW_RESET_PARAMETER_BUF;
}

#endif //POKEDIAMOND_OS_RESET_H
