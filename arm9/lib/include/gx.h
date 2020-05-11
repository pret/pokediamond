#ifndef GUARD_GX_H
#define GUARD_GX_H

#include "fx.h"

//Todos before PR
//TODO: Add defines for GX commands, add structs/unions for HW registers
//TODO: Add ARM_FUNC attributes

#define HW_REG_END_VTXS        0x04000504
#define HW_REG_GXSTAT          0x04000600
#define HW_REG_DISP3DCNT       0x04000060
#define HW_REG_BG0HOFS         0x04000010
#define HW_REG_CLEAR_COLOR     0x04000350
#define HW_REG_CLEAR_DEPTH     0x04000354
#define HW_REG_CLRIMAGE_OFFSET 0x04000356
#define HW_REG_FOG_COLOR       0x04000358
#define HW_REG_FOG_OFFSET      0x0400035C
#define HW_REG_BG0CNT          0x04000008
#define HW_REG_POLYGON_ATTR    0x040004A4
#define HW_REG_TEXIMAGE_PARAM  0x040004A8
#define HW_REG_PLTT_BASE       0x040004AC

#define HW_REG_GXFIFO          0x04000400
#define HW_REG_MTX_IDENTITY    0x04000454
#define HW_REG_MTX_POP         0x04000448
#define HW_REG_MTX_MODE        0x04000440

#define HW_REG_CLIPMTX_RESULT  0x04000640
#define HW_REG_VECMTX_RESULT   0x04000680

#define HW_REG_EDGE_COLOR      0x04000330
#define HW_REG_FOG_TABLE       0x04000360

#define HW_REG_SHININESS       0x040004D0


#define HW_REG_VRAMCNT_A       0x04000240
#define HW_REG_VRAMCNT_B       0x04000241
#define HW_REG_VRAMCNT_C       0x04000242
#define HW_REG_VRAMCNT_D       0x04000243
#define HW_REG_VRAMCNT_E       0x04000244
#define HW_REG_VRAMCNT_F       0x04000245
#define HW_REG_VRAMCNT_G       0x04000246
#define HW_REG_WRAMCNT         0x04000247
#define HW_REG_VRAMCNT_H       0x04000248
#define HW_REG_VRAMCNT_I       0x04000249

#define HW_REG_DISPCNT         0x04000000
#define HW_REG_DISPCNT_2D      0x04001000

#define HW_REG_DISP3DCNT       0x04000060

#define HW_REG_BG0CNT_A 0x04000008
#define HW_REG_BG1CNT_A 0x0400000A
#define HW_REG_BG2CNT_A 0x0400000C
#define HW_REG_BG3CNT_A 0x0400000E

#define HW_REG_BG0CNT_B 0x04001008
#define HW_REG_BG1CNT_B 0x0400100A
#define HW_REG_BG2CNT_B 0x0400100C
#define HW_REG_BG3CNT_B 0x0400100E

#define HW_REG_DISPCNT_A 0x04000000
#define HW_REG_DISPCNT_B 0x04001000

//TODO: wait for register commit and replace these
#define SETREG8(x, y) ((*(vu8 *)x) = y)
#define SETREG16(x, y) ((*(vu16 *)x) = y)
#define SETREG32(x, y) ((*(vu32 *)x) = y)
#define SETREG64(x, y) ((*(vu64 *)x) = y)

#define READREG8(x) (*(vu8 *)x)
#define READREG16(x) (*(vu16 *)x)
#define READREG32(x) (*(vu32 *)x)
#define READREG64(x) (*(vu64 *)x)

//TODO: add SDK signatures and symbols
//TODO: add arm function attributes


struct DL
{
    u8 *var00; //end pointer
    u32 *var04; //aligned end pointer, used to write data
    u8 *var08; //start pointer
    u32 var0C;
    u32 var10; //pad end with zero bool
};

struct VRAM_banks
{
    u16 var00; //lcdc
    u16 var02; //bg
    u16 var04; //obj
    u16 var06; //arm7
    u16 var08; //tex
    u16 var0A; //texpltt
    u16 var0C; //clearimage
    u16 var0E; //bgextpltt
    u16 var10; //objextpltt
    u16 var12; //subbg
    u16 var14; //subobj
    u16 var16; //subbgextpltt
    u16 var18; //subobjextpltt
};

//GX_g3
void G3_BeginMakeDL(struct DL *displaylist, void *r1, u32 r2);
s32 G3_EndMakeDL(struct DL *displaylist);

//GX_g3_util
void G3i_PerspectiveW_(fx32 fovsin, fx32 fovcos, fx32 ratio, fx32 near, fx32 far, fx32 scale, u32 load, struct Mtx44 *mtx);
void G3i_OrthoW_(fx32 top, fx32 bottom, fx32 left, fx32 right, fx32 near, fx32 far, fx32 scale, u32 load, struct Mtx44 *mtx);
void G3i_LookAt_(struct Vecx32 *a, struct Vecx32 *b, struct Vecx32 *c, u32 load, struct Mtx44 *mtx);
void G3_RotX(fx32 sinphi, fx32 cosphi);
void G3_RotY(fx32 sinphi, fx32 cosphi);
void G3_RotZ(fx32 sinphi, fx32 cosphi);

//GX_g3x
void GXi_NopClearFifo128_(void *reg);
void G3X_Init();
void G3X_ResetMtxStack();
void G3X_ClearFifo();
void G3X_InitMtxStack();
void G3X_ResetMtxStack_2();
void G3X_SetFog(u32 enable, u32 alphamode, u32 depth, s32 offset);
u32 G3X_GetClipMtx(struct Mtx44 *dst);
u32 G3X_GetVectorMtx(struct Mtx33 *dst);
void G3X_SetEdgeColorTable(void *tbl_ptr);
void G3X_SetFogTable(void *tbl_ptr);
void G3X_SetClearColor(u32 col, u32 alpha, u32 depth, u32 polygon_id, u32 enable_fog);
void G3X_InitTable();
u32 G3X_GetMtxStackLevelPV(u32 *level);
u32 G3X_GetMtxStackLevelPJ(u32 *level);
u32 G3X_GetBoxTestResult(u32 *result);
void G3X_SetHOffset(u32 offset);


//GX_g3b
void G3BS_LoadMtx44(struct DL *displaylist, struct Mtx44 *mtx);
void G3B_PushMtx(struct DL *displaylist);
void G3B_PopMtx(struct DL *displaylist, void *mtx);
void G3B_LoadMtx44(struct DL *displaylist, struct Mtx44 *mtx);
void G3B_Color(struct DL * displaylist, u32 vtx_col);
void G3B_Normal(struct DL * displaylist, fx16 x, fx16 y, fx16 z);
void G3B_Vtx(struct DL * displaylist, fx32 x, fx32 y, fx32 z);
void G3B_PolygonAttr(struct DL *displaylist, u32 r1, u32 r2, u32 r3, u32 r4, u32 r5, u32 r6);
void G3B_MaterialColorDiffAmb(struct DL *displaylist, u32 diffuse_col, u32 ambient_col, u32 replace);
void G3B_MaterialColorSpecEmi(struct DL *displaylist, u32 specular_col, u32 emission_col, u32 shiny_table);
void G3B_LightVector(struct DL * displaylist, u32 light_num, fx16 x, fx16 y, fx16 z);
void G3B_LightColor(struct DL * displaylist, u32 light_num, u32 col);
void G3B_Begin(struct DL * displaylist, u32 type);
void G3B_End(struct DL * displaylist);

//GX_asm
void GX_SendFifo48B(void *src, void *dst);

//GX_vramcnt
//some of the symbols don't match what the function does
void GX_VRAMCNT_SetLCDC_(u32 mask);
void GX_SetBankForBG(u16 bg);
void GX_SetBankForOBJ(u16 obj);
void GX_SetBankForBGExtPltt(u16 bgextpltt);
void GX_SetBankForOBJExtPltt(u16 objextpltt);
void GX_SetBankForTex(u16 tex);
void GX_SetBankForTexPltt(u16 texpltt);
void GX_SetBankForClearImage(u16 clearimage);
void GX_SetBankForARM7(u16 arm7);
void GX_SetBankForLCDC(u16 lcdc);
void GX_SetBankForSubBG(u16 subbg);
void GX_SetBankForSubOBJ(u16 subobj);
void GX_SetBankForSubBGExtPltt(u16 subbgextpltt);
void GX_SetBankForSubOBJExtPltt(u16 subobjextpltt);
u32 FUN_020C6130(u16 *ptr);
u32 GX_ResetBankForBG();
u32 GX_ResetBankForOBJ();
u32 GX_ResetBankForBGExtPltt();
u32 GX_ResetBankForOBJExtPltt();
u32 GX_ResetBankForTex();
u32 GX_ResetBankForTexPltt();
u32 GX_ResetBankForClearImage();
u32 GX_ResetBankForSubBG();
u32 FUN_020C605C();
u32 FUN_020C6034();
u32 GX_ResetBankForSubOBJ();
u32 FUN_020C5F28(u16 *ptr);
u32 disableBankForX_();
u32 GX_DisableBankForOBJExtPltt_2();
u32 GX_DisableBankForBGExtPltt();
u32 GX_DisableBankForOBJExtPltt();
u32 GX_DisableBankForTexPltt_2();
u32 GX_DisableBankForTexPltt();
u32 GX_DisableBankForClearImage();
u32 GX_DisableBankForARM7();
u32 GX_DisableBankForLCDC();
u32 GX_DisableBankForSubBGExtPltt();
u32 GX_DisableBankForSubOBJExtPltt_2();
u32 FUN_020C5E04();
u32 GX_DisableBankForSubOBJExtPltt();
u32 GX_GetBankForBGExtPltt_2();
u32 GX_GetBankForOBJ();
u32 GX_GetBankForBGExtPltt();
u32 GX_GetBankForOBJExtPltt();
u32 FUN_020C5D8C();
u32 GX_GetBankForTexPltt();
u32 GX_GetBankForLCDC();
u32 GX_GetBankForSubBGExtPltt_2();
u32 GX_GetBankForSubOBJ();
u32 GX_GetBankForSubBGExtPltt();
u32 GX_GetBankForSubOBJExtPltt();

//GX_bgcnt
void *G2_GetBG0ScrPtr();
void *G2S_GetBG0ScrPtr();
void *G2_GetBG1ScrPtr();
void *G2S_GetBG1ScrPtr();
void *G2_GetBG2ScrPtr();
void *G2S_GetBG2ScrPtr();
void *G2_GetBG3ScrPtr();
void *G2S_GetBG3ScrPtr();
void *G2_GetBG0CharPtr();
void *G2S_GetBG0CharPtr();
void *G2_GetBG1CharPtr();
void *G2S_GetBG1CharPtr();
void *G2_GetBG2CharPtr();
void *G2S_GetBG2CharPtr();
void *G2_GetBG3CharPtr();
void *G2S_GetBG3CharPtr();


//GXi_NopClearFifo128_ probably asm

#endif //GUARD_GX_H
