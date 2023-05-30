#ifndef GUARD_GX_VRAMCNT_H
#define GUARD_GX_VRAMCNT_H

#include "vramExclusive.h"

typedef enum {
    GX_VRAM_A = OS_VRAM_BANK_ID_A,// VRAM-A
    GX_VRAM_B = OS_VRAM_BANK_ID_B,// VRAM-B
    GX_VRAM_C = OS_VRAM_BANK_ID_C,// VRAM-C
    GX_VRAM_D = OS_VRAM_BANK_ID_D,// VRAM-D
    GX_VRAM_E = OS_VRAM_BANK_ID_E,// VRAM-E
    GX_VRAM_F = OS_VRAM_BANK_ID_F,// VRAM-F
    GX_VRAM_G = OS_VRAM_BANK_ID_G,// VRAM-G
    GX_VRAM_H = OS_VRAM_BANK_ID_H,// VRAM-H
    GX_VRAM_I = OS_VRAM_BANK_ID_I,// VRAM-I
    GX_VRAM_ALL = OS_VRAM_BANK_ID_ALL
} GXVRam;

typedef enum {
    GX_VRAM_LCDC_NONE = 0x0000,
    GX_VRAM_LCDC_A = GX_VRAM_A,
    GX_VRAM_LCDC_B = GX_VRAM_B,
    GX_VRAM_LCDC_C = GX_VRAM_C,
    GX_VRAM_LCDC_D = GX_VRAM_D,
    GX_VRAM_LCDC_E = GX_VRAM_E,
    GX_VRAM_LCDC_F = GX_VRAM_F,
    GX_VRAM_LCDC_G = GX_VRAM_G,
    GX_VRAM_LCDC_H = GX_VRAM_H,
    GX_VRAM_LCDC_I = GX_VRAM_I,
    GX_VRAM_LCDC_ALL = GX_VRAM_ALL
} GXVRamLCDC;

typedef enum {
    GX_VRAM_BG_NONE = 0x0000,
    GX_VRAM_BG_16_F = GX_VRAM_F,
    GX_VRAM_BG_16_G = GX_VRAM_G,
    GX_VRAM_BG_32_FG = GX_VRAM_F | GX_VRAM_G,
    GX_VRAM_BG_64_E = GX_VRAM_E,
    GX_VRAM_BG_80_EF = GX_VRAM_E | GX_VRAM_F,
    GX_VRAM_BG_96_EFG = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G,
    GX_VRAM_BG_128_A = GX_VRAM_A,
    GX_VRAM_BG_128_B = GX_VRAM_B,
    GX_VRAM_BG_128_C = GX_VRAM_C,
    GX_VRAM_BG_128_D = GX_VRAM_D,
    GX_VRAM_BG_256_AB = GX_VRAM_A | GX_VRAM_B,
    GX_VRAM_BG_256_BC = GX_VRAM_B | GX_VRAM_C,
    GX_VRAM_BG_256_CD = GX_VRAM_C | GX_VRAM_D,
    GX_VRAM_BG_384_ABC = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C,
    GX_VRAM_BG_384_BCD = GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
    GX_VRAM_BG_512_ABCD = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
    GX_VRAM_BG_80_EG = GX_VRAM_E | GX_VRAM_G,
    GX_VRAM_BG_256_AC = GX_VRAM_A | GX_VRAM_C,
    GX_VRAM_BG_256_AD = GX_VRAM_A | GX_VRAM_D,
    GX_VRAM_BG_256_BD = GX_VRAM_B | GX_VRAM_D,
    GX_VRAM_BG_384_ABD = GX_VRAM_A | GX_VRAM_B | GX_VRAM_D,
    GX_VRAM_BG_384_ACD = GX_VRAM_A | GX_VRAM_C | GX_VRAM_D
} GXVRamBG;

typedef enum {
    GX_VRAM_OBJ_NONE = 0x0000,
    GX_VRAM_OBJ_16_F = GX_VRAM_F,
    GX_VRAM_OBJ_16_G = GX_VRAM_G,
    GX_VRAM_OBJ_32_FG = GX_VRAM_F | GX_VRAM_G,
    GX_VRAM_OBJ_64_E = GX_VRAM_E,
    GX_VRAM_OBJ_80_EF = GX_VRAM_E | GX_VRAM_F,
    GX_VRAM_OBJ_80_EG = GX_VRAM_E | GX_VRAM_G,
    GX_VRAM_OBJ_96_EFG = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G,
    GX_VRAM_OBJ_128_A = GX_VRAM_A,
    GX_VRAM_OBJ_128_B = GX_VRAM_B,
    GX_VRAM_OBJ_256_AB = GX_VRAM_A | GX_VRAM_B
} GXVRamOBJ;

typedef enum {
    GX_VRAM_TEX_NONE = 0x0000,
    GX_VRAM_TEX_0_A = GX_VRAM_A,
    GX_VRAM_TEX_0_B = GX_VRAM_B,
    GX_VRAM_TEX_0_C = GX_VRAM_C,
    GX_VRAM_TEX_0_D = GX_VRAM_D,
    GX_VRAM_TEX_01_AB = GX_VRAM_A | GX_VRAM_B,
    GX_VRAM_TEX_01_BC = GX_VRAM_B | GX_VRAM_C,
    GX_VRAM_TEX_01_CD = GX_VRAM_C | GX_VRAM_D,
    GX_VRAM_TEX_012_ABC = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C,
    GX_VRAM_TEX_012_BCD = GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
    GX_VRAM_TEX_0123_ABCD = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
    GX_VRAM_TEX_01_AC = GX_VRAM_A | GX_VRAM_C,
    GX_VRAM_TEX_01_AD = GX_VRAM_A | GX_VRAM_D,
    GX_VRAM_TEX_01_BD = GX_VRAM_B | GX_VRAM_D,
    GX_VRAM_TEX_012_ABD = GX_VRAM_A | GX_VRAM_B | GX_VRAM_D,
    GX_VRAM_TEX_012_ACD = GX_VRAM_A | GX_VRAM_C | GX_VRAM_D
} GXVRamTex;

typedef enum {
    GX_VRAM_CLEARIMAGE_NONE = 0x0000,
    GX_VRAM_CLEARIMAGE_256_AB = GX_VRAM_A | GX_VRAM_B,
    GX_VRAM_CLEARIMAGE_256_CD = GX_VRAM_C | GX_VRAM_D,
    GX_VRAM_CLEARDEPTH_128_A = GX_VRAM_A,
    GX_VRAM_CLEARDEPTH_128_B = GX_VRAM_B,
    GX_VRAM_CLEARDEPTH_128_C = GX_VRAM_C,
    GX_VRAM_CLEARDEPTH_128_D = GX_VRAM_D
} GXVRamClearImage;

typedef enum {
    GX_VRAM_TEXPLTT_NONE = 0x0000,
    GX_VRAM_TEXPLTT_0_F = GX_VRAM_F,
    GX_VRAM_TEXPLTT_0_G = GX_VRAM_G,
    GX_VRAM_TEXPLTT_01_FG = GX_VRAM_F | GX_VRAM_G,
    GX_VRAM_TEXPLTT_0123_E = GX_VRAM_E,
    GX_VRAM_TEXPLTT_01234_EF = GX_VRAM_E | GX_VRAM_F,
    GX_VRAM_TEXPLTT_012345_EFG = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G
} GXVRamTexPltt;

typedef enum {
    GX_VRAM_BGEXTPLTT_NONE = 0x0000,
    GX_VRAM_BGEXTPLTT_01_F = GX_VRAM_F,
    GX_VRAM_BGEXTPLTT_23_G = GX_VRAM_G,
    GX_VRAM_BGEXTPLTT_0123_E = GX_VRAM_E,
    GX_VRAM_BGEXTPLTT_0123_FG = GX_VRAM_F | GX_VRAM_G
} GXVRamBGExtPltt;

typedef enum {
    GX_VRAM_OBJEXTPLTT_NONE = 0,
    GX_VRAM_OBJEXTPLTT_0_F = GX_VRAM_F,
    GX_VRAM_OBJEXTPLTT_0_G = GX_VRAM_G
} GXVRamOBJExtPltt;

typedef enum {
    GX_VRAM_SUB_BG_NONE = 0x0000,
    GX_VRAM_SUB_BG_128_C = GX_VRAM_C,
    GX_VRAM_SUB_BG_32_H = GX_VRAM_H,
    GX_VRAM_SUB_BG_48_HI = GX_VRAM_H | GX_VRAM_I
} GXVRamSubBG;

typedef enum {
    GX_VRAM_SUB_OBJ_NONE = 0x0000,
    GX_VRAM_SUB_OBJ_128_D = GX_VRAM_D,
    GX_VRAM_SUB_OBJ_16_I = GX_VRAM_I
} GXVRamSubOBJ;

typedef enum {
    GX_VRAM_SUB_BGEXTPLTT_NONE = 0x0000,
    GX_VRAM_SUB_BGEXTPLTT_0123_H = GX_VRAM_H
} GXVRamSubBGExtPltt;

typedef enum {
    GX_VRAM_SUB_OBJEXTPLTT_NONE = 0x0000,
    GX_VRAM_SUB_OBJEXTPLTT_0_I = GX_VRAM_I
} GXVRamSubOBJExtPltt;

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
