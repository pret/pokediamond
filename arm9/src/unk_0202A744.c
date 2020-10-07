#include "global.h"
#include "MI_memory.h"
#include "msgdata.h"

#pragma thumb on

u8 FUN_0202A744(void *ptr);
u8 FUN_0202A74C(void *ptr);
void FUN_0202A754(void *dest, void *src, u8 arg2, u8 arg3);
void FUN_0202A784(void *ptr0, void *ptr1);

u8 FUN_0202A744(void *ptr)
{
    return *(u8 *)(ptr + 0xfe);
}

u8 FUN_0202A74C(void *ptr)
{
    return *(u8 *)(ptr + 0xff);
}

void FUN_0202A754(void *dest, void *src, u8 arg2, u8 arg3)
{
    MI_CpuCopy8(src, (void *)(dest + 0x104), 0x63c);
    *(u8 *)(dest + 0x101) = arg2;
    *(u8 *)(dest + 0x100) = arg3;
    *(u8 *)(dest + 0xfe) = 1;
}

void FUN_0202A784(void *ptr0, void *ptr1)
{
    *(u8 *)ptr1 = *(u8 *)(ptr0 + 0x101);
    *(u8 *)(ptr1 + 1) = *(u8 *)(ptr0 + 0x100);
}
