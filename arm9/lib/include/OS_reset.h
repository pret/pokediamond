#ifndef POKEDIAMOND_ARM9_OS_RESET_H
#define POKEDIAMOND_ARM9_OS_RESET_H

#include "nitro/OS_reset_shared.h"
#include "mmap.h"

void OS_InitReset(void);
void OS_ResetSystem(u32 parameter);
void OSi_DoBoot(void);

static inline u32 OS_GetResetParameter(void)
{
    return (u32)*(u32 *)HW_RESET_PARAMETER_BUF;
}

#endif //POKEDIAMOND_ARM9_OS_RESET_H
