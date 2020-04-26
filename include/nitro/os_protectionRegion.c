//
// Created by red031000 on 2020-04-24.
//

#include "os_protectionRegion.h"

asm void OS_SetProtectionRegion1(u32 param)
{
    mcr p15, 0x0, r0, c6, c1, 0x0
    bx lr
}

asm void OS_SetProtectionRegion2(u32 param)
{
    mcr p15, 0x0, r0, c6, c2, 0x0
    bx lr
}