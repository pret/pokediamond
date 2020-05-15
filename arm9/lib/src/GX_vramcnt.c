#include "global.h"
#include "main.h"
#include "gx.h"

extern u16 gUnk021D33BC;
extern struct VRAM_banks gUnk021D33C4;

ARM_FUNC void GX_VRAMCNT_SetLCDC_(u32 mask){
    if (mask & (0x1 << 0))
        SETREG8(HW_REG_VRAMCNT_A, 0x80);
    if (mask & (0x1 << 1))
        SETREG8(HW_REG_VRAMCNT_B, 0x80);
    if (mask & (0x1 << 2))
        SETREG8(HW_REG_VRAMCNT_C, 0x80);
    if (mask & (0x1 << 3))
        SETREG8(HW_REG_VRAMCNT_D, 0x80);
    if (mask & (0x1 << 4))
        SETREG8(HW_REG_VRAMCNT_E, 0x80);
    if (mask & (0x1 << 5))
        SETREG8(HW_REG_VRAMCNT_F, 0x80);
    if (mask & (0x1 << 6))
        SETREG8(HW_REG_VRAMCNT_G, 0x80);
    if (mask & (0x1 << 7))
        SETREG8(HW_REG_VRAMCNT_H, 0x80);
    if (mask & (0x1 << 8))
        SETREG8(HW_REG_VRAMCNT_I, 0x80);
}

ARM_FUNC void GX_SetBankForBG(s32 bg){
    gUnk021D33C4.var00 = (u16)(~bg & (gUnk021D33C4.var00 | gUnk021D33C4.var02));
    gUnk021D33C4.var02 = bg;
    switch (bg)
    {
    case 8:
        SETREG8(HW_REG_VRAMCNT_D, 0x81);
        break;
    case 12:
        SETREG8(HW_REG_VRAMCNT_D, 0x89);
    case 4:
        SETREG8(HW_REG_VRAMCNT_C, 0x81);
        break;
    case 14:
        SETREG8(HW_REG_VRAMCNT_D, 0x91);
    case 6:
        SETREG8(HW_REG_VRAMCNT_C, 0x89);
    case 2:
        SETREG8(HW_REG_VRAMCNT_B, 0x81);
        break;
    case 15:
        SETREG8(HW_REG_VRAMCNT_D, 0x99);
    case 7:
        SETREG8(HW_REG_VRAMCNT_C, 0x91);
    case 3:
        SETREG8(HW_REG_VRAMCNT_B, 0x89);
    case 1:
        SETREG8(HW_REG_VRAMCNT_A, 0x81);
        break;
    case 11:
        SETREG8(HW_REG_VRAMCNT_A, 0x81);
        SETREG8(HW_REG_VRAMCNT_B, 0x89);
        SETREG8(HW_REG_VRAMCNT_D, 0x91);
        break;
    case 13:
        SETREG8(HW_REG_VRAMCNT_D, 0x91);
    case 5:
        SETREG8(HW_REG_VRAMCNT_A, 0x81);
        SETREG8(HW_REG_VRAMCNT_C, 0x89);
        break;
    case 9:
        SETREG8(HW_REG_VRAMCNT_A, 0x81);
        SETREG8(HW_REG_VRAMCNT_D, 0x89);
        break;
    case 10:
        SETREG8(HW_REG_VRAMCNT_B, 0x81);
        SETREG8(HW_REG_VRAMCNT_D, 0x89);
        break;
    case 112:
        SETREG8(HW_REG_VRAMCNT_G, 0x99);
    case 48:
        SETREG8(HW_REG_VRAMCNT_F, 0x91);
    case 16:
        SETREG8(HW_REG_VRAMCNT_E, 0x81);
        break;
    case 80:
        SETREG8(HW_REG_VRAMCNT_G, 0x91);
        SETREG8(HW_REG_VRAMCNT_E, 0x81);
        break;
    case 96:
        SETREG8(HW_REG_VRAMCNT_G, 0x89);
    case 32:
        SETREG8(HW_REG_VRAMCNT_F, 0x81);
        break;
    case 64:
        SETREG8(HW_REG_VRAMCNT_G, 0x81);
        break;
    default:
        break;
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}

ARM_FUNC void GX_SetBankForOBJ(s32 obj){
    gUnk021D33C4.var00 = (u16)(~obj & (gUnk021D33C4.var00 | gUnk021D33C4.var04));
    gUnk021D33C4.var04 = obj;
    switch (obj)
    {
    case 3:
        SETREG8(HW_REG_VRAMCNT_B, 0x8A);
    case 1:
        SETREG8(HW_REG_VRAMCNT_A, 0x82);
    case 0:  //needed to match
        break;
    case 2:
        SETREG8(HW_REG_VRAMCNT_B, 0x82);
        break;
    case 112:
        SETREG8(HW_REG_VRAMCNT_G, 0x9A);
    case 48:
        SETREG8(HW_REG_VRAMCNT_F, 0x92);
    case 16:
        SETREG8(HW_REG_VRAMCNT_E, 0x82);
        break;
    case 80:
        SETREG8(HW_REG_VRAMCNT_G, 0x92);
        SETREG8(HW_REG_VRAMCNT_E, 0x82);
        break;
    case 96:
        SETREG8(HW_REG_VRAMCNT_G, 0x8A);
    case 32:
        SETREG8(HW_REG_VRAMCNT_F, 0x82);
        break;
    case 64:
        SETREG8(HW_REG_VRAMCNT_G, 0x82);
        break;
    default:
        break;
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}

ARM_FUNC void GX_SetBankForBGExtPltt(s32 bgextpltt){
    gUnk021D33C4.var00 = (u16)(~bgextpltt & (gUnk021D33C4.var00 | gUnk021D33C4.var0E));
    gUnk021D33C4.var0E = bgextpltt;
    switch (bgextpltt)
    {
    case 0x10:
        SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) | 0x40000000);
        SETREG8(HW_REG_VRAMCNT_E, 0x84);
        break;
    case 0x40:
        SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) | 0x40000000);
        SETREG8(HW_REG_VRAMCNT_G, 0x8C);
        break;
    case 0x60:
        SETREG8(HW_REG_VRAMCNT_G, 0x8C);
    case 0x20:
        SETREG8(HW_REG_VRAMCNT_F, 0x84);
        SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) | 0x40000000);
        break;
    case 0:
        SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) & ~0x40000000);
        break;
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}

ARM_FUNC void GX_SetBankForOBJExtPltt(s32 objextpltt){
    gUnk021D33C4.var00 = (u16)(~objextpltt & (gUnk021D33C4.var00 | gUnk021D33C4.var10));
    gUnk021D33C4.var10 = objextpltt;
    switch (objextpltt)
    {
    case 32:
        SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) | 0x80000000);
        SETREG8(HW_REG_VRAMCNT_F, 0x85);
        break;
    case 64:
        SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) | 0x80000000);
        SETREG8(HW_REG_VRAMCNT_G, 0x85);
        break;
    case 0:
        SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) & ~0x80000000);
        break;
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}

ARM_FUNC void GX_SetBankForTex(s32 tex){
    gUnk021D33C4.var00 = (u16)(~tex & (gUnk021D33C4.var00 | gUnk021D33C4.var08));
    gUnk021D33C4.var08 = tex;
    if (tex == 0)
    {
        SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) & 0x0000CFFE);
    }
    else
    {
        SETREG16(HW_REG_DISP3DCNT, (READREG16(HW_REG_DISP3DCNT) & ~0x3000) | 0x1);
        switch (tex)
        {
        case 5:
            SETREG8(HW_REG_VRAMCNT_A, 0x83);
            SETREG8(HW_REG_VRAMCNT_C, 0x8B);
            break;
        case 9:
            SETREG8(HW_REG_VRAMCNT_A, 0x83);
            SETREG8(HW_REG_VRAMCNT_D, 0x8B);
            break;
        case 10:
            SETREG8(HW_REG_VRAMCNT_B, 0x83);
            SETREG8(HW_REG_VRAMCNT_D, 0x8B);
            break;
        case 11:
            SETREG8(HW_REG_VRAMCNT_A, 0x83);
            SETREG8(HW_REG_VRAMCNT_B, 0x8B);
            SETREG8(HW_REG_VRAMCNT_D, 0x93);
            break;
        case 13:
            SETREG8(HW_REG_VRAMCNT_A, 0x83);
            SETREG8(HW_REG_VRAMCNT_C, 0x8B);
            SETREG8(HW_REG_VRAMCNT_D, 0x93);
            break;
        case 8:
            SETREG8(HW_REG_VRAMCNT_D, 0x83);
            break;
        case 12:
            SETREG8(HW_REG_VRAMCNT_D, 0x8B);
        case 4:
            SETREG8(HW_REG_VRAMCNT_C, 0x83);
            break;
        case 14:
            SETREG8(HW_REG_VRAMCNT_D, 0x93);
        case 6:
            SETREG8(HW_REG_VRAMCNT_C, 0x8B);
        case 2:
            SETREG8(HW_REG_VRAMCNT_B, 0x83);
            break;
        case 15:
            SETREG8(HW_REG_VRAMCNT_D, 0x9B);
        case 7:
            SETREG8(HW_REG_VRAMCNT_C, 0x93);
        case 3:
            SETREG8(HW_REG_VRAMCNT_B, 0x8B);
        case 1:
            SETREG8(HW_REG_VRAMCNT_A, 0x83);
            break;
        }
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}

ARM_FUNC void GX_SetBankForTexPltt(s32 texpltt){
    gUnk021D33C4.var00 = (u16)(~texpltt & (gUnk021D33C4.var00 | gUnk021D33C4.var0A));
    gUnk021D33C4.var0A = texpltt;
    switch (texpltt)
    {
    case 0: //needed to match
        break;
    case 96:
        SETREG8(HW_REG_VRAMCNT_G, 0x8B);
    case 32:
        SETREG8(HW_REG_VRAMCNT_F, 0x83);
        break;
    case 112:
        SETREG8(HW_REG_VRAMCNT_G, 0x9B);
    case 48:
        SETREG8(HW_REG_VRAMCNT_F, 0x93);
    case 16:
        SETREG8(HW_REG_VRAMCNT_E, 0x83);
        break;
    case 64:
        SETREG8(HW_REG_VRAMCNT_G, 0x83);
        break;
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}

ARM_FUNC void GX_SetBankForClearImage(s32 clearimage){
    gUnk021D33C4.var00 = (u16)(~clearimage & (gUnk021D33C4.var00 | gUnk021D33C4.var0C));
    gUnk021D33C4.var0C = clearimage;
    switch (clearimage)
    {
    case 3:
        SETREG8(HW_REG_VRAMCNT_A, 0x93);
    case 2:
        SETREG8(HW_REG_VRAMCNT_B, 0x9B);
        SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) | 0x4000);
        break;
    case 12:
        SETREG8(HW_REG_VRAMCNT_C, 0x93);
    case 8:
        SETREG8(HW_REG_VRAMCNT_D, 0x9B);
        SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) | 0x4000);
        break;
    case 0:
        SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) & ~0x4000);
        break;
    case 1:
        SETREG8(HW_REG_VRAMCNT_A, 0x9B);
        SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) | 0x4000);
        break;
    case 4:
        SETREG8(HW_REG_VRAMCNT_C, 0x9B);
        SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) | 0x4000);
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}

ARM_FUNC void GX_SetBankForARM7(s32 arm7){
    gUnk021D33C4.var00 = (u16)(~arm7 & (gUnk021D33C4.var00 | gUnk021D33C4.var06));
    gUnk021D33C4.var06 = arm7;
    switch (arm7)
    {
    case 0: //needed to match
        break;
    case 12:
        SETREG8(HW_REG_VRAMCNT_D, 0x8A);
        SETREG8(HW_REG_VRAMCNT_C, 0x82);
        break;
    case 4:
        SETREG8(HW_REG_VRAMCNT_C, 0x82);
        break;
    case 8:
        SETREG8(HW_REG_VRAMCNT_D, 0x82);
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}

ARM_FUNC void GX_SetBankForLCDC(s32 lcdc){
    gUnk021D33C4.var00 |= lcdc;
    GX_VRAMCNT_SetLCDC_(lcdc);
}

ARM_FUNC void GX_SetBankForSubBG(s32 subbg){
    gUnk021D33C4.var00 = (u16)(~subbg & (gUnk021D33C4.var00 | gUnk021D33C4.var12));
    gUnk021D33C4.var12 = subbg;
    switch (subbg)
    {
    case 0: //needed to match
        break;
    case 4:
        SETREG8(HW_REG_VRAMCNT_C, 0x84);
        break;
    case 384:
        SETREG8(HW_REG_VRAMCNT_I, 0x81);
    case 128:
        SETREG8(HW_REG_VRAMCNT_H, 0x81);
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}


ARM_FUNC void GX_SetBankForSubOBJ(s32 subobj){
    gUnk021D33C4.var00 = (u16)(~subobj & (gUnk021D33C4.var00 | gUnk021D33C4.var14));
    gUnk021D33C4.var14 = subobj;
    switch (subobj)
    {
    case 8:
        SETREG8(HW_REG_VRAMCNT_D, 0x84);
        break;
    case 256:
        SETREG8(HW_REG_VRAMCNT_I, 0x82);
        break;
    case 0: //needed to match
        break;
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}

ARM_FUNC void GX_SetBankForSubBGExtPltt(s32 subbgextpltt){
    gUnk021D33C4.var00 = (u16)(~subbgextpltt & (gUnk021D33C4.var00 | gUnk021D33C4.var16));
    gUnk021D33C4.var16 = subbgextpltt;
    switch (subbgextpltt)
    {
        case 128:
            SETREG32(HW_REG_DISPCNT_2D, READREG32(HW_REG_DISPCNT_2D) | 0x40000000);
            SETREG8(HW_REG_VRAMCNT_H, 0x82);
            break;
        case 0:
            SETREG32(HW_REG_DISPCNT_2D, READREG32(HW_REG_DISPCNT_2D) & ~0x40000000);
            break;
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}

ARM_FUNC void GX_SetBankForSubOBJExtPltt(s32 subobjextpltt){
    gUnk021D33C4.var00 = (u16)(~subobjextpltt & (gUnk021D33C4.var00 | gUnk021D33C4.var18));
    gUnk021D33C4.var18 = subobjextpltt;
    switch (subobjextpltt)
    {
        case 256:
            SETREG32(HW_REG_DISPCNT_2D, READREG32(HW_REG_DISPCNT_2D) | 0x80000000);
            SETREG8(HW_REG_VRAMCNT_I, 0x83);
            break;
        case 0:
            SETREG32(HW_REG_DISPCNT_2D, READREG32(HW_REG_DISPCNT_2D) & ~0x80000000);
            break;
    }
    GX_VRAMCNT_SetLCDC_(gUnk021D33C4.var00);
}

ARM_FUNC u32 FUN_020C6130(u16 *ptr){
    u16 temp = *ptr;
    *ptr = 0;
    gUnk021D33C4.var00 |= temp;
    GX_VRAMCNT_SetLCDC_(temp);
    return temp;
}

ARM_FUNC u32 GX_ResetBankForBG(){
    return FUN_020C6130(&gUnk021D33C4.var02);
}

ARM_FUNC u32 GX_ResetBankForOBJ(){
    return FUN_020C6130(&gUnk021D33C4.var04);
}

ARM_FUNC u32 GX_ResetBankForBGExtPltt(){
    SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) & ~0x40000000);
    return FUN_020C6130(&gUnk021D33C4.var0E);
}

ARM_FUNC u32 GX_ResetBankForOBJExtPltt(){
    SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) & ~0x80000000);
    return FUN_020C6130(&gUnk021D33C4.var10);
}

ARM_FUNC u32 GX_ResetBankForTex(){
    return FUN_020C6130(&gUnk021D33C4.var08);
}

ARM_FUNC u32 GX_ResetBankForTexPltt(){
    return FUN_020C6130(&gUnk021D33C4.var0A);
}

ARM_FUNC u32 GX_ResetBankForClearImage(){
    return FUN_020C6130(&gUnk021D33C4.var0C);
}

ARM_FUNC u32 GX_ResetBankForSubBG(){
    return FUN_020C6130(&gUnk021D33C4.var12);
}

ARM_FUNC u32 FUN_020C605C(){
    return FUN_020C6130(&gUnk021D33C4.var14);
}

ARM_FUNC u32 FUN_020C6034(){
    SETREG32(HW_REG_DISPCNT_2D, READREG32(HW_REG_DISPCNT_2D) & ~0x40000000);
    return FUN_020C6130(&gUnk021D33C4.var16);
}

ARM_FUNC u32 GX_ResetBankForSubOBJ(){
    SETREG32(HW_REG_DISPCNT_2D, READREG32(HW_REG_DISPCNT_2D) & ~0x80000000);
    return FUN_020C6130(&gUnk021D33C4.var18);
}

ARM_FUNC u32 FUN_020C5F28(u16 *ptr){
    u32 temp = *ptr;
    *ptr = 0;
    if (temp & (0x1 << 0))
        SETREG8(HW_REG_VRAMCNT_A, 0x0);
    if (temp & (0x1 << 1))
        SETREG8(HW_REG_VRAMCNT_B, 0x0);
    if (temp & (0x1 << 2))
        SETREG8(HW_REG_VRAMCNT_C, 0x0);
    if (temp & (0x1 << 3))
        SETREG8(HW_REG_VRAMCNT_D, 0x0);
    if (temp & (0x1 << 4))
        SETREG8(HW_REG_VRAMCNT_E, 0x0);
    if (temp & (0x1 << 5))
        SETREG8(HW_REG_VRAMCNT_F, 0x0);
    if (temp & (0x1 << 6))
        SETREG8(HW_REG_VRAMCNT_G, 0x0);
    if (temp & (0x1 << 7))
        SETREG8(HW_REG_VRAMCNT_H, 0x0);
    if (temp & (0x1 << 8))
        SETREG8(HW_REG_VRAMCNT_I, 0x0);
    OSi_UnlockVram((u16)temp, gUnk021D33BC);
    return temp;
}

ARM_FUNC u32 disableBankForX_(){
    return FUN_020C5F28(&gUnk021D33C4.var02);
}

ARM_FUNC u32 GX_DisableBankForOBJExtPltt_2(){
    return FUN_020C5F28(&gUnk021D33C4.var04);
}

ARM_FUNC u32 GX_DisableBankForBGExtPltt(){
    SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) & ~0x40000000);
    return FUN_020C5F28(&gUnk021D33C4.var0E);
}

ARM_FUNC u32 GX_DisableBankForOBJExtPltt(){
    SETREG32(HW_REG_DISPCNT, READREG32(HW_REG_DISPCNT) & ~0x80000000);
    return FUN_020C5F28(&gUnk021D33C4.var10);
}

ARM_FUNC u32 GX_DisableBankForTexPltt_2(){
    return FUN_020C5F28(&gUnk021D33C4.var08);
}

ARM_FUNC u32 GX_DisableBankForTexPltt(){
    return FUN_020C5F28(&gUnk021D33C4.var0A);
}

ARM_FUNC u32 GX_DisableBankForClearImage(){
    return FUN_020C5F28(&gUnk021D33C4.var0C);
}

ARM_FUNC u32 GX_DisableBankForARM7(){
    return FUN_020C5F28(&gUnk021D33C4.var06);
}

ARM_FUNC u32 GX_DisableBankForLCDC(){
    return FUN_020C5F28(&gUnk021D33C4.var00);
}

ARM_FUNC u32 GX_DisableBankForSubBGExtPltt(){
    return FUN_020C5F28(&gUnk021D33C4.var12);
}

ARM_FUNC u32 GX_DisableBankForSubOBJExtPltt_2(){
    return FUN_020C5F28(&gUnk021D33C4.var14);
}

ARM_FUNC u32 FUN_020C5E04(){
    SETREG32(HW_REG_DISPCNT_2D, READREG32(HW_REG_DISPCNT_2D) & ~0x40000000);
    return FUN_020C5F28(&gUnk021D33C4.var16);
}

ARM_FUNC u32 GX_DisableBankForSubOBJExtPltt(){
    SETREG32(HW_REG_DISPCNT_2D, READREG32(HW_REG_DISPCNT_2D) & ~0x80000000);
    return FUN_020C5F28(&gUnk021D33C4.var18);
}

ARM_FUNC u32 GX_GetBankForBGExtPltt_2(){
    return gUnk021D33C4.var02;
}

ARM_FUNC u32 GX_GetBankForOBJ(){
    return gUnk021D33C4.var04;
}

ARM_FUNC u32 GX_GetBankForBGExtPltt(){
    return gUnk021D33C4.var0E;
}

ARM_FUNC u32 GX_GetBankForOBJExtPltt(){
    return gUnk021D33C4.var10;
}

ARM_FUNC u32 FUN_020C5D8C(){
    return gUnk021D33C4.var08;
}

ARM_FUNC u32 GX_GetBankForTexPltt(){
    return gUnk021D33C4.var0A;
}

ARM_FUNC u32 GX_GetBankForLCDC(){
    return gUnk021D33C4.var00;
}

ARM_FUNC u32 GX_GetBankForSubBGExtPltt_2(){
    return gUnk021D33C4.var12;
}

ARM_FUNC u32 GX_GetBankForSubOBJ(){
    return gUnk021D33C4.var14;
}

ARM_FUNC u32 GX_GetBankForSubBGExtPltt(){
    return gUnk021D33C4.var16;
}

ARM_FUNC u32 GX_GetBankForSubOBJExtPltt(){
    return gUnk021D33C4.var18;
}
