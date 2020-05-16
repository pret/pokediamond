#ifndef GUARD_GX_H
#define GUARD_GX_H

#include "fx.h"

//temporary while other files aren't decompiled
void MIi_CpuCopy16(void *, void *, u32);
void GXi_NopClearFifo128_(void *);
void MI_Copy16B(void *, void *);
void MI_DmaFill32Async(u32, void *, u32, u32, u32, u32);
void MI_DmaFill32(u32, void *, u32, u32);
void MIi_CpuClear32(u32, void *, u32);
void MI_Copy64B(void *src, void *dst);
void MI_WaitDma(u32);
void MI_DmaCopy32Async(u32, void *, void *, u32, void *, void *);
void MI_DmaCopy16(u32 unk, void *src, void *dst, u32 size);
void MIi_CpuCopy16(void *src, void *dst, u32 size);
void MI_DmaCopy32(u32 unk, void *src, void *dst, u32 size);
void MIi_CpuCopy32(void *src, void *dst, u32 size);
void OSi_UnlockVram(u16, u16);
void MIi_CpuClear32(u32, void *, u32);

//TODO: Add defines for GX commands, add structs/unions for HW registers
//TODO: structs
//TODO: useful macros
//TODO: inline functions
//TODO: enums
//TODO: function signatures


static inline void _GX_Load_16(u32 var, void *src, void *dst, u32 size){
    if (var != -1 && size > 0x1C)
    {
        MI_DmaCopy16(var, src, dst, size);
    }
    else
    {
        MIi_CpuCopy16(src, dst, size);
    }
}

static inline void _GX_Load_32(u32 var, void *src, void *dst, u32 size){
    if (var != -1 && size > 0x30)
    {
        MI_DmaCopy32(var, src, dst, size);
    }
    else
    {
        MIi_CpuCopy32(src, dst, size);
    }
}

static inline void _GX_Load_32_Async(u32 var, void *src, void *dst, u32 size, void *func, void *ptr){
    if (var != -1)
    {
        MI_DmaCopy32Async(var, src, dst, size, func, ptr);
    }
    else
    {
        MIi_CpuCopy32(src, dst, size);
    }
}

struct GXDLInfo
{
    u8     *curr_cmd;
    u32    *curr_param;
    u32    *bottom;
    u32     length;
    BOOL    param0_cmd_flg;
};


struct GX_State
{
    u16     lcdc;
    u16     bg;
    u16     obj;
    u16     arm7;
    u16     tex;
    u16     texPltt;
    u16     clrImg;
    u16     bgExtPltt;
    u16     objExtPltt;

    u16     sub_bg;
    u16     sub_obj;
    u16     sub_bgExtPltt;
    u16     sub_objExtPltt;
};

//GX_g3
void G3_BeginMakeDL(struct GXDLInfo *displaylist, void *r1, u32 r2);
s32 G3_EndMakeDL(struct GXDLInfo *displaylist);

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
void G3BS_LoadMtx44(struct GXDLInfo *displaylist, struct Mtx44 *mtx);
void G3B_PushMtx(struct GXDLInfo *displaylist);
void G3B_PopMtx(struct GXDLInfo *displaylist, void *mtx);
void G3B_LoadMtx44(struct GXDLInfo *displaylist, struct Mtx44 *mtx);
void G3B_Color(struct GXDLInfo * displaylist, u32 vtx_col);
void G3B_Normal(struct GXDLInfo * displaylist, fx16 x, fx16 y, fx16 z);
void G3B_Vtx(struct GXDLInfo * displaylist, fx32 x, fx32 y, fx32 z);
void G3B_PolygonAttr(struct GXDLInfo *displaylist, u32 r1, u32 r2, u32 r3, u32 r4, u32 r5, u32 r6);
void G3B_MaterialColorDiffAmb(struct GXDLInfo *displaylist, u32 diffuse_col, u32 ambient_col, u32 replace);
void G3B_MaterialColorSpecEmi(struct GXDLInfo *displaylist, u32 specular_col, u32 emission_col, u32 shiny_table);
void G3B_LightVector(struct GXDLInfo * displaylist, u32 light_num, fx16 x, fx16 y, fx16 z);
void G3B_LightColor(struct GXDLInfo * displaylist, u32 light_num, u32 col);
void G3B_Begin(struct GXDLInfo * displaylist, u32 type);
void G3B_End(struct GXDLInfo * displaylist);

//GX_asm
void GX_SendFifo48B(void *src, void *dst);

//GX_vramcnt
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

//GX_load2d
void GX_LoadBGPltt(void *src, u32 offset, u32 size);
void GXS_LoadBGPltt(void *src, u32 offset, u32 size);
void GX_LoadOBJPltt(void *src, u32 offset, u32 size);
void GXS_LoadOBJPltt(void *src, u32 offset, u32 size);
void GX_LoadOAM(void *src, u32 offset, u32 size);
void GXS_LoadOAM(void *src, u32 offset, u32 size);
void GX_LoadOBJ(void *src, u32 offset, u32 size);
void GXS_LoadOBJ(void *src, u32 offset, u32 size);
void GX_LoadBG0Scr(void *src, u32 offset, u32 size);
void GXS_LoadBG0Scr(void *src, u32 offset, u32 size);
void GX_LoadBG1Scr(void *src, u32 offset, u32 size);
void GXS_LoadBG1Scr(void *src, u32 offset, u32 size);
void GX_LoadBG2Scr(void *src, u32 offset, u32 size);
void GXS_LoadBG2Scr(void *src, u32 offset, u32 size);
void GX_LoadBG3Scr(void *src, u32 offset, u32 size);
void GXS_LoadBG3Scr(void *src, u32 offset, u32 size);
void GX_LoadBG0Char(void *src, u32 offset, u32 size);
void GXS_LoadBG0Char(void *src, u32 offset, u32 size);
void GX_LoadBG1Char(void *src, u32 offset, u32 size);
void GXS_LoadBG1Char(void *src, u32 offset, u32 size);
void GX_LoadBG2Char(void *src, u32 offset, u32 size);
void GXS_LoadBG2Char(void *src, u32 offset, u32 size);
void GX_LoadBG3Char(void *src, u32 offset, u32 size);
void GXS_LoadBG3Char(void *src, u32 offset, u32 size);
void GX_BeginLoadBGExtPltt();
void GX_LoadBGExtPltt(void *src, u32 offset, u32 size);
void GX_EndLoadBGExtPltt();
void GX_BeginLoadOBJExtPltt();
void GX_LoadOBJExtPltt(void *src, u32 offset, u32 size);
void GX_EndLoadOBJExtPltt();
void GXS_BeginLoadBGExtPltt();
void GXS_LoadBGExtPltt(void *src, u32 offset, u32 size);
void GXS_EndLoadBGExtPltt();
void GXS_BeginLoadOBJExtPltt();
void GXS_LoadOBJExtPltt(void *src, u32 offset, u32 size);
void GXS_EndLoadOBJExtPltt();

//GX_load3d
void GX_BeginLoadTex();
void GX_LoadTex(void *src, u32 offset, u32 size);
void GX_EndLoadTex();
void GX_BeginLoadTexPltt();
void GX_LoadTexPltt(void *src, u32 offset, u32 size);
void GX_EndLoadTexPltt();
void GX_BeginLoadClearImage();
void GX_LoadClearImageColor(void *src, u32 size);
void GX_LoadClearImageDepth(void *src, u32 size);
void GX_EndLoadClearImage();

//GX
void GX_Init();
u32 GX_HBlankIntr(u32 enable);
u32 GX_VBlankIntr(u32 enable);
void GX_DispOff();
void GX_DispOn();
void GX_SetGraphicsMode(u32 mode1, u32 mode2, u32 mode3);
void GXS_SetGraphicsMode(u32 mode);
void GXx_SetMasterBrightness_(vu16 *dst, s32 brightness);

//GX_g2
void G2x_SetBGyAffine_(u32 *ptr, struct Mtx22 *mtx, fx32 a, fx32 b, fx32 c, fx32 d);
void G2x_SetBlendAlpha_(u32 *ptr, fx32 a, fx32 b, fx32 c, fx32 d);
void G2x_SetBlendBrightness_(u16 *ptr, fx32 a, fx32 brightness);
void G2x_SetBlendBrightnessExt_(u16 *ptr, fx32 a, fx32 b, fx32 c, fx32 d, fx32 brightness);
void *G2x_ChangeBlendBrightness_(u16 *ptr, fx32 brightness);

//GX_state
void GX_InitGXState();

//GX_g3imm
void G3_LoadMtx43(struct Mtx43 *mtx);
void G3_MultMtx43(struct Mtx43 *mtx);
void G3_MultMtx33(struct Mtx33 *mtx);

#endif //GUARD_GX_H
