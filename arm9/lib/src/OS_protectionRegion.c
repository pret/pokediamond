//
// Created by red031000 on 2020-04-24.
//

#include "OS_protectionRegion.h"

asm void OS_SetDPermissionsForProtectionRegion(register u32 setMask, register u32 flags)
{
    mrc p15, 0x0, r2, c5, c0, 0x2
    bic r2, r2, r0
    orr r2, r2, r1
    mcr p15, 0x0, r2, c5, c0, 0x2
    bx lr
}

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