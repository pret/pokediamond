#ifndef GUARD_GX_VRAMCNT_H
#define GUARD_GX_VRAMCNT_H

//some of the symbols don't match what the function does
void GX_VRAMCNT_SetLCDC_(u32 mask);
void GX_SetBankForBG(s32 bg);
void GX_SetBankForOBJ(s32 obj);
void GX_SetBankForBGExtPltt(s32 bgextpltt);
void GX_SetBankForOBJExtPltt(s32 objextpltt);
void GX_SetBankForTex(s32 tex);
void GX_SetBankForTexPltt(s32 texpltt);
void GX_SetBankForClearImage(s32 clearimage);
void GX_SetBankForARM7(s32 arm7);
void GX_SetBankForLCDC(s32 lcdc);
void GX_SetBankForSubBG(s32 subbg);
void GX_SetBankForSubOBJ(s32 subobj);
void GX_SetBankForSubBGExtPltt(s32 subbgextpltt);
void GX_SetBankForSubOBJExtPltt(s32 subobjextpltt);
u32 resetBankForX_(u16 *ptr);
u32 GX_ResetBankForBG();
u32 GX_ResetBankForOBJ();
u32 GX_ResetBankForBGExtPltt();
u32 GX_ResetBankForOBJExtPltt();
u32 GX_ResetBankForTex();
u32 GX_ResetBankForTexPltt();
u32 GX_ResetBankForClearImage();
u32 GX_ResetBankForSubBG();
u32 GX_ResetBankForSubOBJ();
u32 GX_ResetBankForSubBGExtPltt();
u32 GX_ResetBankForSubOBJExtPltt();
u32 disableBankForX_(u16 *ptr);
u32 GX_DisableBankForBG();
u32 GX_DisableBankForOBJ();
u32 GX_DisableBankForBGExtPltt();
u32 GX_DisableBankForOBJExtPltt();
u32 GX_DisableBankForTex();
u32 GX_DisableBankForTexPltt();
u32 GX_DisableBankForClearImage();
u32 GX_DisableBankForARM7();
u32 GX_DisableBankForLCDC();
u32 GX_DisableBankForSubBG();
u32 GX_DisableBankForSubOBJ();
u32 GX_DisableBankForSubBGExtPltt();
u32 GX_DisableBankForSubOBJExtPltt();
u32 GX_GetBankForBG();
u32 GX_GetBankForOBJ();
u32 GX_GetBankForBGExtPltt();
u32 GX_GetBankForOBJExtPltt();
u32 GX_GetBankForTex();
u32 GX_GetBankForTexPltt();
u32 GX_GetBankForLCDC();
u32 GX_GetBankForSubBG();
u32 GX_GetBankForSubOBJ();
u32 GX_GetBankForSubBGExtPltt();
u32 GX_GetBankForSubOBJExtPltt();

#endif //GUARD_GX_VRAMCNT_H
