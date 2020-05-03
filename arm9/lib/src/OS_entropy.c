//
// Created by red031000 on 2020-05-03.
//

#include "function_target.h"
#include "consts.h"
#include "OS_entropy.h"

ARM_FUNC void OS_GetLowEntropyData(u32 * arr)
{
    const OSSystemWork* work = OS_GetSystemWork();
    const u8 * macAddress = (u8 *)((u32)(work->nvramUserInfo) + ((sizeof(NVRAMConfig) + 3) & ~3));
    arr[0] = (u32)((GX_GetVCount() << 16) | OS_GetTickLo());
    arr[1] = (u32)(*(u16 *)(macAddress + 4) << 16) ^ (u32)(OSi_TickCounter);
    arr[2] = (u32)(OSi_TickCounter >> 32) ^ *(u32 *)macAddress ^ work->vblankCount;
    arr[2] ^= reg_G3X_GXSTAT;
    arr[3] = *(u32 *)(&work->real_time_clock[0]);
    arr[4] = *(u32 *)(&work->real_time_clock[4]);
    arr[5] = (((u32)work->mic_sampling_data) << 16) ^ work->mic_last_address;
    arr[6] = (u32) ((*(u16 *)(&work->touch_panel[0]) << 16) | *(u16 *)(&work->touch_panel[2]));
    arr[7] = (u32)((work->wm_rssi_pool << 16) | (reg_PAD_KEYINPUT | *(vu16 *)HW_BUTTON_XY_BUF));
}
