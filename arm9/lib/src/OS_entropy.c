//
// Created by red031000 on 2020-05-03.
//

#include "function_target.h"
#include "consts.h"
#include "OS_entropy.h"

u32 * const HW_REG_006 = (u32 *) 0x04000006;
u32 * const HW_REG_130 = (u32 *) 0x04000130;
u32 * const HW_REG_600 = (u32 *) 0x04000600;

u32 * const OSi_TickCounter = (u32 *) 0x021D37B4;

ARM_FUNC void OS_GetLowEntropyData(u32 * arr)
{
    OSSystemWork* work = OS_GetSystemWork();
    u16 x = *((u16 *)HW_REG_006);
    u8 * nvramUserInfo = work->nvramUserInfo;
    u8 r5 = nvramUserInfo[0x74];
    arr[0] = (OS_GetTickLo()<<0x10) | x ;
    arr[1] = (OSi_TickCounter[0]<<0x10) ^ r5[2];
    u32 what = OSi_TickCounter[0];
    what = OSi_TickCounter[1];
    arr[2] = *((u32 *)r4) ^ what ^ *(u32 *)((u8 *)work+0x3c);
    arr[2] ^= *HW_REG_600;
    // ...
}