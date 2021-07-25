//
// Created by red031000 on 2020-05-03.
//

#ifndef POKEDIAMOND_OS_ENTROPY_H
#define POKEDIAMOND_OS_ENTROPY_H

#include "registers.h"

void OS_GetLowEntropyData(u32 * arr);

extern vu64 OSi_TickCounter;

extern u16 OS_GetTickLo(void);

static inline s32 GX_GetVCount(void)
{
    return reg_GX_VCOUNT;
}

#endif //POKEDIAMOND_OS_ENTROPY_H
