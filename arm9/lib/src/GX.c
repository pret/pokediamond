#include "global.h"
#include "main.h"
#include "gx.h"

extern u16 UNK_021D33BC;
extern u16 UNK_021D33C0;
extern u32 UNK_02106814;
extern u16 UNK_02106810;

ARM_FUNC void GX_Init(){
    reg_GX_POWCNT |= 0x8000;
    reg_GX_POWCNT = (reg_GX_POWCNT & ~0x20E) | 0x20E;
    reg_GX_POWCNT = reg_GX_POWCNT | 0x1;
    GX_InitGXState();
    u32 temp;
    while (UNK_021D33BC == 0)
    {
        temp = OS_GetLockID();
        if (temp == -3)
        {
            OS_Terminate();
        }
        UNK_021D33BC = temp;
    }
    reg_GX_DISPSTAT = 0x0;
    reg_GX_DISPCNT = 0x0;
    if (UNK_02106814 != -1)
    {
        MI_DmaFill32(UNK_02106814, (void *)&reg_G2_BG0CNT, 0x0, 0x60);
        reg_GX_MASTER_BRIGHT = 0x0;
        MI_DmaFill32(UNK_02106814, (void *)&reg_GXS_DB_DISPCNT, 0x0, 0x70);
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
    u32 temp = reg_GX_DISPSTAT & 0x10;
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
    u32 temp = reg_GX_DISPSTAT & 0x8;
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
    UNK_02106810 = 0x0;
    UNK_021D33C0 = (temp & 0x30000) >> 0x10;
    reg_GX_DISPCNT = temp & ~0x30000;
}

ARM_FUNC void GX_DispOn(){
    UNK_02106810 = 0x1;
    if (UNK_021D33C0)
    {
        reg_GX_DISPCNT = reg_GX_DISPCNT & ~0x30000 | (UNK_021D33C0 << 0x10);
    }
    else
    {
        reg_GX_DISPCNT = reg_GX_DISPCNT | 0x10000;
    }
}

ARM_FUNC void GX_SetGraphicsMode(u32 mode1, u32 mode2, u32 mode3){
    u32 temp2 = reg_GX_DISPCNT;
    UNK_021D33C0 = mode1;
    if (!UNK_02106810)
        mode1 = 0;
    reg_GX_DISPCNT = (mode2 | ((temp2 & 0xFFF0FFF0) | (mode1 << 0x10))) | (mode3 << 0x3);
    if (!UNK_021D33C0)
        UNK_02106810 = 0x0;
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
        *dst = 0x4000 | brightness;
    }
    else
    {
        *dst = 0x8000 | -brightness;
    }
}
