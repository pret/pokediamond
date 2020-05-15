#include "global.h"
#include "main.h"
#include "gx.h"

extern u16 gUnk021D33BC;
extern u16 gUnk021D33C0;
extern u32 gUnk02106814;
extern u16 gUnk02106810;

ARM_FUNC void GX_Init(){
    SETREG16(HW_REG_POWCNT1, READREG16(HW_REG_POWCNT1) | 0x8000);
    SETREG16(HW_REG_POWCNT1, (READREG16(HW_REG_POWCNT1) & ~0x20E) | 0x20E);
    SETREG16(HW_REG_POWCNT1, READREG16(HW_REG_POWCNT1) | 0x1);
    GX_InitGXState();
    u32 temp;
    while (gUnk021D33BC == 0)
    {
        temp = OS_GetLockID();
        if (temp == -3)
        {
            OS_Terminate();
        }
        gUnk021D33BC = temp;
    }
    SETREG16(HW_REG_DISPSTAT, 0x0);
    SETREG32(HW_REG_DISPCNT, 0x0);
    if (gUnk02106814 != -1)
    {
        MI_DmaFill32(gUnk02106814, (void *)HW_REG_BG0CNT_A, 0x0, 0x60);
        SETREG16(HW_REG_MASTER_BRIGHT, 0x0);
        MI_DmaFill32(gUnk02106814, (void *)HW_REG_DISPCNT_2D, 0x0, 0x70);
    }
    else
    {
        MIi_CpuClear32(0x0, (void *)HW_REG_BG0CNT_A, 0x60);
        SETREG16(HW_REG_MASTER_BRIGHT, 0x0);
        MIi_CpuClear32(0x0, (void *)HW_REG_DISPCNT_2D, 0x70);
    }
    SETREG16(HW_REG_BG2PA_A, 0x100);
    SETREG16(HW_REG_BG2PD_A, 0x100);
    SETREG16(HW_REG_BG3PA_A, 0x100);
    SETREG16(HW_REG_BG3PD_A, 0x100);
    SETREG16(HW_REG_BG2PA_B, 0x100);
    SETREG16(HW_REG_BG2PD_B, 0x100);
    SETREG16(HW_REG_BG3PA_B, 0x100);
    SETREG16(HW_REG_BG3PD_B, 0x100);
}

ARM_FUNC u32 GX_HBlankIntr(u32 enable){
    u32 temp = READREG16(HW_REG_DISPSTAT) & 0x10;
    if (enable)
    {
        SETREG16(HW_REG_DISPSTAT, READREG16(HW_REG_DISPSTAT) | 0x10);
    }
    else
    {
        SETREG16(HW_REG_DISPSTAT, READREG16(HW_REG_DISPSTAT) & ~0x10);
    }
    return temp;
}

ARM_FUNC u32 GX_VBlankIntr(u32 enable){
    u32 temp = READREG16(HW_REG_DISPSTAT) & 0x8;
    if (enable)
    {
        SETREG16(HW_REG_DISPSTAT, READREG16(HW_REG_DISPSTAT) | 0x8);
    }
    else
    {
        SETREG16(HW_REG_DISPSTAT, READREG16(HW_REG_DISPSTAT) & ~0x8);
    }
    return temp;
}

ARM_FUNC void GX_DispOff(){
    u32 temp = READREG32(HW_REG_DISPCNT);
    gUnk02106810 = 0x0;
    gUnk021D33C0 = (temp & 0x30000) >> 0x10;
    SETREG32(HW_REG_DISPCNT, temp & ~0x30000);
}

ARM_FUNC void GX_DispOn(){
    gUnk02106810 = 0x1;
    if (gUnk021D33C0)
    {
        SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) & ~0x30000 | (gUnk021D33C0 << 0x10));

    }
    else
    {
        SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) | 0x10000);
    }
}

ARM_FUNC void GX_SetGraphicsMode(u32 mode1, u32 mode2, u32 mode3){
    u32 temp2 = READREG32(HW_REG_DISPCNT);
    gUnk021D33C0 = mode1;
    if (!gUnk02106810)
        mode1 = 0;
    SETREG32(HW_REG_DISPCNT, (mode2 | ((temp2 & 0xFFF0FFF0) | (mode1 << 0x10))) | (mode3 << 0x3));
    if (!gUnk021D33C0)
        gUnk02106810 = 0x0;
}

ARM_FUNC void GXS_SetGraphicsMode(u32 mode){
    SETREG32(HW_REG_DISPCNT_2D, READREG32(HW_REG_DISPCNT_2D) & ~0x7 | mode);
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
