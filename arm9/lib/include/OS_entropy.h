//
// Created by red031000 on 2020-05-03.
//

#ifndef POKEDIAMOND_OS_ENTROPY_H
#define POKEDIAMOND_OS_ENTROPY_H

#include "consts.h"

void OS_GetLowEntropyData(u32 * arr);

typedef struct NVRAMConfig{
    u8 ncd[110]; // todo: typeof NVRAMConfigData
    u16 saveCount;
    u16 rc16;
} NVRAMConfig;

extern vu64 OSi_TickCounter;

extern u16 OS_GetTickLo();

static inline s32 GX_GetVCount()
{
    return reg_GX_VCOUNT;
}

#endif //POKEDIAMOND_OS_ENTROPY_H
