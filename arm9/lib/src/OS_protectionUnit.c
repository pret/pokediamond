//
// Created by red031000 on 2020-05-24.
//

#include "function_target.h"

ARM_FUNC asm void OS_EnableProtectionUnit(void)
{
    mrc p15, 0x0, r0, c1, c0, 0x0
    orr r0, r0, #0x1
    mcr p15, 0x0, r0, c1, c0, 0x0
    bx lr
}

ARM_FUNC asm void OS_DisableProtectionUnit(void)
{
    mrc p15, 0x0, r0, c1, c0, 0x0
    bic r0, r0, #0x1
    mcr p15, 0x0, r0, c1, c0, 0x0
    bx lr
}
