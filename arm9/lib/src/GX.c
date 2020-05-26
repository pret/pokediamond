#include "global.h"
#include "main.h"
#include "GX.h"

u32 GXi_DmaId = 3;
vu16 GXi_VRamLockId = 0;

static u16 sDispMode = 0;
static u16 sIsDispOn = TRUE;

ARM_FUNC void GX_Init(){
    reg_GX_POWCNT |= 0x8000;
    reg_GX_POWCNT = (u16)((reg_GX_POWCNT & ~0x20E) | 0x20E);
    reg_GX_POWCNT = (u16)(reg_GX_POWCNT | 0x1);
    GX_InitGXState();
    s32 temp;
    while (GXi_VRamLockId == 0)
    {
        temp = OS_GetLockID();
        if (temp == -3)
        {
            OS_Terminate();
        }
        GXi_VRamLockId = (vu16)temp;
    }
    reg_GX_DISPSTAT = 0x0;
    reg_GX_DISPCNT = 0x0;
    if (GXi_DmaId != -1)
    {
        MI_DmaFill32(GXi_DmaId, (void *)&reg_G2_BG0CNT, 0x0, 0x60);
        reg_GX_MASTER_BRIGHT = 0x0;
        MI_DmaFill32(GXi_DmaId, (void *)&reg_GXS_DB_DISPCNT, 0x0, 0x70);
    }
    else
    {
        MIi_CpuClear32(0x0, (void *)&reg_G2_BG0CNT, 0x60);
        reg_GX_MASTER_BRIGHT = 0x0;
        MIi_CpuClear32(0x0, (void *)&reg_GXS_DB_DISPCNT, 0x70);
    }
    reg_G2_BG2PA = 0x100;
    reg_G2_BG2PD = 0x100;
    reg_G2_BG3PA = 0x100;
    reg_G2_BG3PD = 0x100;
    reg_G2S_DB_BG2PA = 0x100;
    reg_G2S_DB_BG2PD = 0x100;
    reg_G2S_DB_BG3PA = 0x100;
    reg_G2S_DB_BG3PD = 0x100;
}

ARM_FUNC u32 GX_HBlankIntr(u32 enable){
    u32 temp = (u32)(reg_GX_DISPSTAT & 0x10);
    if (enable)
    {
        reg_GX_DISPSTAT |= 0x10;
    }
    else
    {
        reg_GX_DISPSTAT &= ~0x10;
    }
    return temp;
}

ARM_FUNC u32 GX_VBlankIntr(u32 enable){
    u32 temp = (u32)(reg_GX_DISPSTAT & 0x8);
    if (enable)
    {
        reg_GX_DISPSTAT |= 0x8;
    }
    else
    {
        reg_GX_DISPSTAT &= ~0x8;
    }
    return temp;
}

ARM_FUNC void GX_DispOff(){
    u32 temp = reg_GX_DISPCNT;
    sIsDispOn = 0x0;
    sDispMode = (u16)((temp & 0x30000) >> 0x10);
    reg_GX_DISPCNT = temp & ~0x30000;
}

ARM_FUNC void GX_DispOn(){
    sIsDispOn = 0x1;
    if (sDispMode)
    {
        reg_GX_DISPCNT = reg_GX_DISPCNT & ~0x30000 | (sDispMode << 0x10);
    }
    else
    {
        reg_GX_DISPCNT = reg_GX_DISPCNT | 0x10000;
    }
}

ARM_FUNC void GX_SetGraphicsMode(u32 mode1, u32 mode2, u32 mode3){
    u32 temp2 = reg_GX_DISPCNT;
    sDispMode = (u16)mode1;
    if (!sIsDispOn)
        mode1 = 0;
    reg_GX_DISPCNT = (mode2 | ((temp2 & 0xFFF0FFF0) | (mode1 << 0x10))) | (mode3 << 0x3);
    if (!sDispMode)
        sIsDispOn = 0x0;
}

ARM_FUNC void GXS_SetGraphicsMode(u32 mode){
    reg_GXS_DB_DISPCNT = reg_GXS_DB_DISPCNT & ~0x7 | mode;
}

ARM_FUNC void GXx_SetMasterBrightness_(vu16 *dst, s32 brightness){
    if (!brightness)
    {
        *dst = 0x0;
    }
    else if (brightness > 0)
    {
        *dst = (u16)(0x4000 | brightness);
    }
    else
    {
        *dst = (u16)(0x8000 | -brightness);
    }
}
