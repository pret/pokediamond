#include "function_target.h"
#include "OS_protectionRegion.h"

ARM_FUNC asm void OS_SetDPermissionsForProtectionRegion(register u32 setMask, register u32 flags)
{
    mrc p15, 0x0, r2, c5, c0, 0x2 //Extended Access Permission Data Protection Region
    bic r2, r2, r0
    orr r2, r2, r1
    mcr p15, 0x0, r2, c5, c0, 0x2 //Extended Access Permission Data Protection Region
    bx lr
}

ARM_FUNC asm void OS_SetProtectionRegion1(u32 param)
{
    mcr p15, 0x0, r0, c6, c1, 0x0 //Protection Unit Data Region 1
    bx lr
}

ARM_FUNC asm void OS_SetProtectionRegion2(u32 param)
{
    mcr p15, 0x0, r0, c6, c2, 0x0 //Protection Unit Data Region 2
    bx lr
}
