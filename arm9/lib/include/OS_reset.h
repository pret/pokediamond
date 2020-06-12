#ifndef POKEDIAMOND_ARM9_OS_RESET_H
#define POKEDIAMOND_ARM9_OS_RESET_H

#include "consts.h"
#include "nitro/OS_reset_shared.h"
#include "PXI_fifo.h"

void OS_InitReset(void);
static void OSi_CommonCallback(PXIFifoTag tag, u32 data, BOOL err);
static void OSi_SendToPxi(u16 data);
void OS_ResetSystem(u32 parameter);
static void OSi_DoResetSystem(void);
void OSi_DoBoot(void);
static void OSi_CpuClear32(register u32 data, register void *destp, register u32 size);
static void OSi_ReloadRomData(void);
static void OSi_ReadCardRom32(u32 src, void *dst, s32 len);

static inline u32 OS_GetResetParameter(void)
{
    return (u32)*(u32 *)HW_RESET_PARAMETER_BUF;
}

#endif //POKEDIAMOND_ARM9_OS_RESET_H
