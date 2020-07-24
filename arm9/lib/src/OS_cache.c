#include "OS_cache.h"
#include "nitro/types.h"
#include "function_target.h"

ARM_FUNC asm void DC_InvalidateAll(void)
{
    mov r0, #0
    mcr p15, 0, r0, c7, c6, 0 //Invalidate Entire Data Cache
    bx lr
}

ARM_FUNC asm void DC_StoreAll(void)
{
    mov r1, #0

_020CC0C8:
    mov r0, #0

_020CC0CC:
    orr r2, r1, r0
    mcr p15, 0, r2, c7, c10, 2 //Clean Data Cache Line Set/Index
    add r0, r0, #32
    cmp r0, #0x400
    blt _020CC0CC

    add r1, r1, #0x40000000
    cmp r1, #0
    bne _020CC0C8

    bx lr
}

ARM_FUNC asm void DC_FlushAll(void)
{
    mov r12, #0
    mov r1, #0

_020CC0F8:
    mov r0, #0

_020CC0FC:
    orr r2, r1, r0
    mcr p15, 0, r12, c7, c10, 4 //Drain Write Buffer
    mcr p15, 0, r2, c7, c14, 2 //Clean and Invalidate Data Cache Line Set/Index
    add r0, r0, #32
    cmp r0, #0x400
    blt _020CC0FC

    add r1, r1, #0x40000000
    cmp r1, #0
    bne _020CC0F8

    bx lr
}

ARM_FUNC asm void DC_InvalidateRange(register void *startAddr, register u32 nBytes)
{
    add r1, r1, r0
    bic r0, r0, #31

_020CC12C:
    mcr p15, 0, r0, c7, c6, 1 //Invalidated Data Cache Line Virtual Address
    add r0, r0, #32
    cmp r0, r1
    blt _020CC12C

    bx lr
}

ARM_FUNC asm void DC_StoreRange(register void *startAddr, register u32 nBytes)
{
    add r1, r1, r0
    bic r0, r0, #31

_020CC148:
    mcr p15, 0, r0, c7, c10, 1 //Clean Data Cache Line Virtual Address
    add r0, r0, #32
    cmp r0, r1
    blt _020CC148

    bx lr
}

ARM_FUNC asm void DC_FlushRange(register const void *startAddr, register u32 nBytes)
{
    mov r12, #0
    add r1, r1, r0
    bic r0, r0, #31

_020CC168:
    mcr p15, 0, r12, c7, c10, 4 //Drain Write Buffer
    mcr p15, 0, r0, c7, c14, 1 //Clean and Invalidate Data Cache Line Virtual Address
    add r0, r0, #32
    cmp r0, r1
    blt _020CC168

    bx lr
}

ARM_FUNC asm void DC_WaitWriteBufferEmpty(void)
{
    mov r0, #0
    mcr p15, 0, r0, c7, c10, 4 //Drain Write Buffer
    bx lr
}

ARM_FUNC asm void IC_InvalidateAll(void)
{
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0 //Invalidate Entire Instruction Cache
    bx lr
}

ARM_FUNC asm void IC_InvalidateRange(register void *startAddr, register u32 nBytes)
{
    add r1, r1, r0
    bic r0, r0, #31

_020CC1A0:
    mcr p15, 0, r0, c7, c5, 1 //Invalidate Instruction Cache Line Virtual Address
    add r0, r0, #32
    cmp r0, r1
    blt _020CC1A0

    bx lr
}
