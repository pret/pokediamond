#include "gx.h"

#include "nitro/types.h"
#include "OS_spinLock.h"
#include "OS_terminate_proc.h"
#include "code32.h"

u32 GXi_DmaId = 3;
vu16 GXi_VRamLockId = 0;

static u16 sDispMode = 0;
static u16 sIsDispOn = TRUE;

#define _powcnt_init_mask (REG_GX_POWCNT_E2DGB_MASK | REG_GX_POWCNT_E2DG_MASK | REG_GX_POWCNT_RE_MASK | REG_GX_POWCNT_GE_MASK)

void GX_Init(){
    reg_GX_POWCNT |= REG_GX_POWCNT_DSEL_MASK;
    reg_GX_POWCNT = (u16)((reg_GX_POWCNT & ~_powcnt_init_mask) | _powcnt_init_mask);
    reg_GX_POWCNT = (u16)(reg_GX_POWCNT | REG_GX_POWCNT_LCD_MASK);
    GX_InitGXState();
    s32 temp;
    while (GXi_VRamLockId == 0)
    {
        temp = OS_GetLockID();
        if (temp == OS_LOCK_ID_ERROR)
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

u32 GX_HBlankIntr(u32 enable){
    u32 temp = (u32)(reg_GX_DISPSTAT & REG_GX_DISPSTAT_HBI_MASK);
    if (enable)
    {
        reg_GX_DISPSTAT |= REG_GX_DISPSTAT_HBI_MASK;
    }
    else
    {
        reg_GX_DISPSTAT &= ~REG_GX_DISPSTAT_HBI_MASK;
    }
    return temp;
}

u32 GX_VBlankIntr(u32 enable){
    u32 temp = (u32)(reg_GX_DISPSTAT & REG_GX_DISPSTAT_VBI_MASK);
    if (enable)
    {
        reg_GX_DISPSTAT |= REG_GX_DISPSTAT_VBI_MASK;
    }
    else
    {
        reg_GX_DISPSTAT &= ~REG_GX_DISPSTAT_VBI_MASK;
    }
    return temp;
}

void GX_DispOff(){
    u32 temp = reg_GX_DISPCNT;
    sIsDispOn = FALSE;
    sDispMode = (u16)((temp & REG_GX_DISPCNT_MODE_MASK) >> REG_GX_DISPCNT_MODE_SHIFT);
    reg_GX_DISPCNT = temp & ~REG_GX_DISPCNT_MODE_MASK;
}

void GX_DispOn(){
    sIsDispOn = TRUE;
    if (sDispMode)
    {
        reg_GX_DISPCNT = (reg_GX_DISPCNT & ~REG_GX_DISPCNT_MODE_MASK) | (sDispMode << REG_GX_DISPCNT_MODE_SHIFT);
    }
    else
    {
        reg_GX_DISPCNT = reg_GX_DISPCNT | (GX_DISPMODE_GRAPHICS << REG_GX_DISPCNT_MODE_SHIFT);
    }
}

void GX_SetGraphicsMode(GXDispMode dispMode, GXBGMode bgMode, GXBG0As bg0_2d3d){
    u32 temp2 = reg_GX_DISPCNT;
    sDispMode = (u16)dispMode;
    if (!sIsDispOn)
        dispMode = (GXDispMode)0;
    reg_GX_DISPCNT = ((bgMode << REG_GX_DISPCNT_BGMODE_SHIFT) | ((temp2 & ~(REG_GX_DISPCNT_BGMODE_MASK | REG_GX_DISPCNT_MODE_MASK | REG_GX_DISPCNT_BG02D3D_MASK | REG_GX_DISPCNT_VRAM_MASK)) | (dispMode << REG_GX_DISPCNT_MODE_SHIFT))) | (bg0_2d3d << REG_GX_DISPCNT_BG02D3D_SHIFT);
    if (!sDispMode)
        sIsDispOn = FALSE;
}

void GXS_SetGraphicsMode(GXBGMode mode){
    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & ~REG_GXS_DB_DISPCNT_BGMODE_MASK) | mode;
}

void GXx_SetMasterBrightness_(vu16 *dst, s32 brightness){
    if (!brightness)
    {
        *dst = 0x0;
    }
    else if (brightness > 0)
    {
        *dst = (u16)((1 << REG_GX_MASTER_BRIGHT_E_MOD_SHIFT) | brightness);
    }
    else
    {
        *dst = (u16)((2 << REG_GX_MASTER_BRIGHT_E_MOD_SHIFT) | -brightness);
    }
}
