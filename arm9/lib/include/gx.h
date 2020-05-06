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

struct DL
{
    u8 *var00; //end pointer
    u32 *var04; //aligned end pointer, used to write data
    u8 *var08; //start pointer
    u32 var0C;
    u32 var10; //pad end with zero bool
};

//GX_g3
void G3_BeginMakeDL(struct DL *displaylist, void *r1, u32 r2);
s32 G3_EndMakeDL(struct DL *displaylist);

//GX_g3x
asm void GXi_NopClearFifo128_(void *reg);
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


//GXi_NopClearFifo128_ probably asm

#endif //GUARD_GX_H
