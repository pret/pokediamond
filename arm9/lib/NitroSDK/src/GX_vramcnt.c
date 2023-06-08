#include "nitro/types.h"
#include "gx.h"
#include "code32.h"

extern u16 GXi_VRamLockId;
extern struct GX_State gGXState;

void GX_VRAMCNT_SetLCDC_(u32 mask) {
    if (mask & (0x1 << 0))
        reg_GX_VRAMCNT_A = 0x80;
    if (mask & (0x1 << 1))
        reg_GX_VRAMCNT_B = 0x80;
    if (mask & (0x1 << 2))
        reg_GX_VRAMCNT_C = 0x80;
    if (mask & (0x1 << 3))
        reg_GX_VRAMCNT_D = 0x80;
    if (mask & (0x1 << 4))
        reg_GX_VRAMCNT_E = 0x80;
    if (mask & (0x1 << 5))
        reg_GX_VRAMCNT_F = 0x80;
    if (mask & (0x1 << 6))
        reg_GX_VRAMCNT_G = 0x80;
    if (mask & (0x1 << 7))
        reg_GX_VRAMCNT_H = 0x80;
    if (mask & (0x1 << 8))
        reg_GX_VRAMCNT_I = 0x80;
}

void GX_SetBankForBG(s32 bg){
    gGXState.lcdc = (u16)(~bg & (gGXState.lcdc | gGXState.bg));
    gGXState.bg = (u16)bg;
    switch (bg)
    {
    case 8:
        reg_GX_VRAMCNT_D = 0x81;
        break;
    case 12:
        reg_GX_VRAMCNT_D = 0x89;
    case 4:
        reg_GX_VRAMCNT_C = 0x81;
        break;
    case 14:
        reg_GX_VRAMCNT_D = 0x91;
    case 6:
        reg_GX_VRAMCNT_C = 0x89;
    case 2:
        reg_GX_VRAMCNT_B = 0x81;
        break;
    case 15:
        reg_GX_VRAMCNT_D = 0x99;
    case 7:
        reg_GX_VRAMCNT_C = 0x91;
    case 3:
        reg_GX_VRAMCNT_B = 0x89;
    case 1:
        reg_GX_VRAMCNT_A = 0x81;
        break;
    case 11:
        reg_GX_VRAMCNT_A = 0x81;
        reg_GX_VRAMCNT_B = 0x89;
        reg_GX_VRAMCNT_D = 0x91;
        break;
    case 13:
        reg_GX_VRAMCNT_D = 0x91;
    case 5:
        reg_GX_VRAMCNT_A = 0x81;
        reg_GX_VRAMCNT_C = 0x89;
        break;
    case 9:
        reg_GX_VRAMCNT_A = 0x81;
        reg_GX_VRAMCNT_D = 0x89;
        break;
    case 10:
        reg_GX_VRAMCNT_B = 0x81;
        reg_GX_VRAMCNT_D = 0x89;
        break;
    case 112:
        reg_GX_VRAMCNT_G = 0x99;
    case 48:
        reg_GX_VRAMCNT_F = 0x91;
    case 16:
        reg_GX_VRAMCNT_E = 0x81;
        break;
    case 80:
        reg_GX_VRAMCNT_G = 0x91;
        reg_GX_VRAMCNT_E = 0x81;
        break;
    case 96:
        reg_GX_VRAMCNT_G = 0x89;
    case 32:
        reg_GX_VRAMCNT_F = 0x81;
        break;
    case 64:
        reg_GX_VRAMCNT_G = 0x81;
        break;
    default:
        break;
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}

void GX_SetBankForOBJ(s32 obj){
    gGXState.lcdc = (u16)(~obj & (gGXState.lcdc | gGXState.obj));
    gGXState.obj = (u16)obj;
    switch (obj)
    {
    case 3:
        reg_GX_VRAMCNT_B = 0x8A;
    case 1:
        reg_GX_VRAMCNT_A = 0x82;
    case 0:  //needed to match
        break;
    case 2:
        reg_GX_VRAMCNT_B = 0x82;
        break;
    case 112:
        reg_GX_VRAMCNT_G = 0x9A;
    case 48:
        reg_GX_VRAMCNT_F = 0x92;
    case 16:
        reg_GX_VRAMCNT_E = 0x82;
        break;
    case 80:
        reg_GX_VRAMCNT_G = 0x92;
        reg_GX_VRAMCNT_E = 0x82;
        break;
    case 96:
        reg_GX_VRAMCNT_G = 0x8A;
    case 32:
        reg_GX_VRAMCNT_F = 0x82;
        break;
    case 64:
        reg_GX_VRAMCNT_G = 0x82;
        break;
    default:
        break;
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}

void GX_SetBankForBGExtPltt(s32 bgextpltt){
    gGXState.lcdc = (u16)(~bgextpltt & (gGXState.lcdc | gGXState.bgExtPltt));
    gGXState.bgExtPltt = (u16)bgextpltt;
    switch (bgextpltt)
    {
    case 0x10:
        reg_GX_DISPCNT |= 0x40000000;
        reg_GX_VRAMCNT_E = 0x84;
        break;
    case 0x40:
        reg_GX_DISPCNT |= 0x40000000;
        reg_GX_VRAMCNT_G = 0x8C;
        break;
    case 0x60:
        reg_GX_VRAMCNT_G = 0x8C;
    case 0x20:
        reg_GX_VRAMCNT_F = 0x84;
        reg_GX_DISPCNT |= 0x40000000;
        break;
    case 0:
        reg_GX_DISPCNT &= ~0x40000000;
        break;
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}

void GX_SetBankForOBJExtPltt(s32 objextpltt){
    gGXState.lcdc = (u16)(~objextpltt & (gGXState.lcdc | gGXState.objExtPltt));
    gGXState.objExtPltt = (u16)objextpltt;
    switch (objextpltt)
    {
    case 32:
        reg_GX_DISPCNT |= 0x80000000;
        reg_GX_VRAMCNT_F = 0x85;
        break;
    case 64:
        reg_GX_DISPCNT |= 0x80000000;
        reg_GX_VRAMCNT_G = 0x85;
        break;
    case 0:
        reg_GX_DISPCNT &= ~0x80000000;
        break;
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}

void GX_SetBankForTex(s32 tex){
    gGXState.lcdc = (u16)(~tex & (gGXState.lcdc | gGXState.tex));
    gGXState.tex = (u16)tex;
    if (tex == 0)
    {
        reg_G3X_DISP3DCNT &= 0x0000CFFE;
    }
    else
    {
        reg_G3X_DISP3DCNT = (u16)((reg_G3X_DISP3DCNT & ~0x3000) | 0x1);
        switch (tex)
        {
        case 5:
            reg_GX_VRAMCNT_A = 0x83;
            reg_GX_VRAMCNT_C = 0x8B;
            break;
        case 9:
            reg_GX_VRAMCNT_A = 0x83;
            reg_GX_VRAMCNT_D = 0x8B;
            break;
        case 10:
            reg_GX_VRAMCNT_B = 0x83;
            reg_GX_VRAMCNT_D = 0x8B;
            break;
        case 11:
            reg_GX_VRAMCNT_A = 0x83;
            reg_GX_VRAMCNT_B = 0x8B;
            reg_GX_VRAMCNT_D = 0x93;
            break;
        case 13:
            reg_GX_VRAMCNT_A = 0x83;
            reg_GX_VRAMCNT_C = 0x8B;
            reg_GX_VRAMCNT_D = 0x93;
            break;
        case 8:
            reg_GX_VRAMCNT_D = 0x83;
            break;
        case 12:
            reg_GX_VRAMCNT_D = 0x8B;
        case 4:
            reg_GX_VRAMCNT_C = 0x83;
            break;
        case 14:
            reg_GX_VRAMCNT_D = 0x93;
        case 6:
            reg_GX_VRAMCNT_C = 0x8B;
        case 2:
            reg_GX_VRAMCNT_B = 0x83;
            break;
        case 15:
            reg_GX_VRAMCNT_D = 0x9B;
        case 7:
            reg_GX_VRAMCNT_C = 0x93;
        case 3:
            reg_GX_VRAMCNT_B = 0x8B;
        case 1:
            reg_GX_VRAMCNT_A = 0x83;
            break;
        }
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}

void GX_SetBankForTexPltt(s32 texpltt){
    gGXState.lcdc = (u16)(~texpltt & (gGXState.lcdc | gGXState.texPltt));
    gGXState.texPltt = (u16)texpltt;
    switch (texpltt)
    {
    case 0: //needed to match
        break;
    case 96:
        reg_GX_VRAMCNT_G = 0x8B;
    case 32:
        reg_GX_VRAMCNT_F = 0x83;
        break;
    case 112:
        reg_GX_VRAMCNT_G = 0x9B;
    case 48:
        reg_GX_VRAMCNT_F = 0x93;
    case 16:
        reg_GX_VRAMCNT_E = 0x83;
        break;
    case 64:
        reg_GX_VRAMCNT_G = 0x83;
        break;
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}

void GX_SetBankForClearImage(s32 clearimage){
    gGXState.lcdc = (u16)(~clearimage & (gGXState.lcdc | gGXState.clrImg));
    gGXState.clrImg = (u16)clearimage;
    switch (clearimage)
    {
    case 3:
        reg_GX_VRAMCNT_A = 0x93;
    case 2:
        reg_GX_VRAMCNT_B = 0x9B;
        reg_G3X_DISP3DCNT |= 0x4000;
        break;
    case 12:
        reg_GX_VRAMCNT_C = 0x93;
    case 8:
        reg_GX_VRAMCNT_D = 0x9B;
        reg_G3X_DISP3DCNT |= 0x4000;
        break;
    case 0:
        reg_G3X_DISP3DCNT &= ~0x4000;
        break;
    case 1:
        reg_GX_VRAMCNT_A = 0x9B;
        reg_G3X_DISP3DCNT |= 0x4000;
        break;
    case 4:
        reg_GX_VRAMCNT_C = 0x9B;
        reg_G3X_DISP3DCNT |= 0x4000;
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}

void GX_SetBankForARM7(s32 arm7){
    gGXState.lcdc = (u16)(~arm7 & (gGXState.lcdc | gGXState.arm7));
    gGXState.arm7 = (u16)arm7;
    switch (arm7)
    {
    case 0: //needed to match
        break;
    case 12:
        reg_GX_VRAMCNT_D = 0x8A;
        reg_GX_VRAMCNT_C = 0x82;
        break;
    case 4:
        reg_GX_VRAMCNT_C = 0x82;
        break;
    case 8:
        reg_GX_VRAMCNT_D = 0x82;
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}

void GX_SetBankForLCDC(s32 lcdc){
    gGXState.lcdc |= lcdc;
    GX_VRAMCNT_SetLCDC_((u32)lcdc);
}

void GX_SetBankForSubBG(s32 subbg){
    gGXState.lcdc = (u16)(~subbg & (gGXState.lcdc | gGXState.sub_bg));
    gGXState.sub_bg = (u16)subbg;
    switch (subbg)
    {
    case 0: //needed to match
        break;
    case 4:
        reg_GX_VRAMCNT_C = 0x84;
        break;
    case 384:
        reg_GX_VRAMCNT_I = 0x81;
    case 128:
        reg_GX_VRAMCNT_H = 0x81;
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}


void GX_SetBankForSubOBJ(s32 subobj){
    gGXState.lcdc = (u16)(~subobj & (gGXState.lcdc | gGXState.sub_obj));
    gGXState.sub_obj = (u16)subobj;
    switch (subobj)
    {
    case 8:
        reg_GX_VRAMCNT_D = 0x84;
        break;
    case 256:
        reg_GX_VRAMCNT_I = 0x82;
        break;
    case 0: //needed to match
        break;
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}

void GX_SetBankForSubBGExtPltt(s32 subbgextpltt){
    gGXState.lcdc = (u16)(~subbgextpltt & (gGXState.lcdc | gGXState.sub_bgExtPltt));
    gGXState.sub_bgExtPltt = (u16)subbgextpltt;
    switch (subbgextpltt)
    {
        case 128:
            reg_GXS_DB_DISPCNT |= 0x40000000;
            reg_GX_VRAMCNT_H = 0x82;
            break;
        case 0:
            reg_GXS_DB_DISPCNT &= ~0x40000000;
            break;
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}

void GX_SetBankForSubOBJExtPltt(s32 subobjextpltt){
    gGXState.lcdc = (u16)(~subobjextpltt & (gGXState.lcdc | gGXState.sub_objExtPltt));
    gGXState.sub_objExtPltt = (u16)subobjextpltt;
    switch (subobjextpltt)
    {
        case 256:
            reg_GXS_DB_DISPCNT |= 0x80000000;
            reg_GX_VRAMCNT_I = 0x83;
            break;
        case 0:
            reg_GXS_DB_DISPCNT &= ~0x80000000;
            break;
    }
    GX_VRAMCNT_SetLCDC_(gGXState.lcdc);
}

u32 resetBankForX_(u16 *ptr){
    u16 temp = *ptr;
    *ptr = 0;
    gGXState.lcdc |= temp;
    GX_VRAMCNT_SetLCDC_(temp);
    return temp;
}

u32 GX_ResetBankForBG(){
    return resetBankForX_(&gGXState.bg);
}

u32 GX_ResetBankForOBJ(){
    return resetBankForX_(&gGXState.obj);
}

u32 GX_ResetBankForBGExtPltt(){
    reg_GX_DISPCNT &= ~0x40000000;
    return resetBankForX_(&gGXState.bgExtPltt);
}

u32 GX_ResetBankForOBJExtPltt(){
    reg_GX_DISPCNT &= ~0x80000000;
    return resetBankForX_(&gGXState.objExtPltt);
}

u32 GX_ResetBankForTex(){
    return resetBankForX_(&gGXState.tex);
}

u32 GX_ResetBankForTexPltt(){
    return resetBankForX_(&gGXState.texPltt);
}

u32 GX_ResetBankForClearImage(){
    return resetBankForX_(&gGXState.clrImg);
}

u32 GX_ResetBankForSubBG(){
    return resetBankForX_(&gGXState.sub_bg);
}

u32 GX_ResetBankForSubOBJ(){
    return resetBankForX_(&gGXState.sub_obj);
}

u32 GX_ResetBankForSubBGExtPltt(){
    reg_GXS_DB_DISPCNT &= ~REG_GXS_DB_DISPCNT_BG_MASK;
    return resetBankForX_(&gGXState.sub_bgExtPltt);
}

u32 GX_ResetBankForSubOBJExtPltt(){
    reg_GXS_DB_DISPCNT &= ~REG_GXS_DB_DISPCNT_O_MASK;
    return resetBankForX_(&gGXState.sub_objExtPltt);
}

u32 disableBankForX_(u16 *ptr){
    u32 temp = *ptr;
    *ptr = 0;
    if (temp & (0x1 << 0))
        reg_GX_VRAMCNT_A = 0x0;
    if (temp & (0x1 << 1))
        reg_GX_VRAMCNT_B = 0x0;
    if (temp & (0x1 << 2))
        reg_GX_VRAMCNT_C = 0x0;
    if (temp & (0x1 << 3))
        reg_GX_VRAMCNT_D = 0x0;
    if (temp & (0x1 << 4))
        reg_GX_VRAMCNT_E = 0x0;
    if (temp & (0x1 << 5))
        reg_GX_VRAMCNT_F = 0x0;
    if (temp & (0x1 << 6))
        reg_GX_VRAMCNT_G = 0x0;
    if (temp & (0x1 << 7))
        reg_GX_VRAMCNT_H = 0x0;
    if (temp & (0x1 << 8))
        reg_GX_VRAMCNT_I = 0x0;
    OSi_UnlockVram((u16)temp, GXi_VRamLockId);
    return temp;
}

u32 GX_DisableBankForBG(){
    return disableBankForX_(&gGXState.bg);
}

u32 GX_DisableBankForOBJ(){
    return disableBankForX_(&gGXState.obj);
}

u32 GX_DisableBankForBGExtPltt(){
    reg_GX_DISPCNT &= ~REG_GX_DISPCNT_BG_MASK;
    return disableBankForX_(&gGXState.bgExtPltt);
}

u32 GX_DisableBankForOBJExtPltt(){
    reg_GX_DISPCNT &= ~REG_GX_DISPCNT_O_MASK;
    return disableBankForX_(&gGXState.objExtPltt);
}

u32 GX_DisableBankForTex(){
    return disableBankForX_(&gGXState.tex);
}

u32 GX_DisableBankForTexPltt(){
    return disableBankForX_(&gGXState.texPltt);
}

u32 GX_DisableBankForClearImage(){
    return disableBankForX_(&gGXState.clrImg);
}

u32 GX_DisableBankForARM7(){
    return disableBankForX_(&gGXState.arm7);
}

u32 GX_DisableBankForLCDC(){
    return disableBankForX_(&gGXState.lcdc);
}

u32 GX_DisableBankForSubBG(){
    return disableBankForX_(&gGXState.sub_bg);
}

u32 GX_DisableBankForSubOBJ(){
    return disableBankForX_(&gGXState.sub_obj);
}

u32 GX_DisableBankForSubBGExtPltt(){
    reg_GXS_DB_DISPCNT &= ~REG_GX_DISPCNT_BG_MASK;
    return disableBankForX_(&gGXState.sub_bgExtPltt);
}

u32 GX_DisableBankForSubOBJExtPltt(){
    reg_GXS_DB_DISPCNT &= ~REG_GX_DISPCNT_O_MASK;
    return disableBankForX_(&gGXState.sub_objExtPltt);
}

u32 GX_GetBankForBG(){
    return gGXState.bg;
}

u32 GX_GetBankForOBJ(){
    return gGXState.obj;
}

u32 GX_GetBankForBGExtPltt(){
    return gGXState.bgExtPltt;
}

u32 GX_GetBankForOBJExtPltt(){
    return gGXState.objExtPltt;
}

u32 GX_GetBankForTex(){
    return gGXState.tex;
}

u32 GX_GetBankForTexPltt(){
    return gGXState.texPltt;
}

u32 GX_GetBankForLCDC(){
    return gGXState.lcdc;
}

u32 GX_GetBankForSubBG(){
    return gGXState.sub_bg;
}

u32 GX_GetBankForSubOBJ(){
    return gGXState.sub_obj;
}

u32 GX_GetBankForSubBGExtPltt(){
    return gGXState.sub_bgExtPltt;
}

u32 GX_GetBankForSubOBJExtPltt(){
    return gGXState.sub_objExtPltt;
}
