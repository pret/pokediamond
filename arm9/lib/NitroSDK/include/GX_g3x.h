#ifndef GUARD_GX_G3X_H
#define GUARD_GX_G3X_H

#include "fx.h"

#include "registers.h"

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

typedef enum
{
    GX_SHADING_TOON = 0,
    GX_SHADING_HIGHLIGHT = 1
}
GXShading;

typedef enum
{
    GX_FOGBLEND_COLOR_ALPHA = 0,
    GX_FOGBLEND_ALPHA = 1
}
GXFogBlend;

typedef enum
{
    GX_FOGSLOPE_0x8000 = 0,
    GX_FOGSLOPE_0x4000 = 1,
    GX_FOGSLOPE_0x2000 = 2,
    GX_FOGSLOPE_0x1000 = 3,
    GX_FOGSLOPE_0x0800 = 4,
    GX_FOGSLOPE_0x0400 = 5,
    GX_FOGSLOPE_0x0200 = 6,
    GX_FOGSLOPE_0x0100 = 7,
    GX_FOGSLOPE_0x0080 = 8,
    GX_FOGSLOPE_0x0040 = 9,
    GX_FOGSLOPE_0x0020 = 10
}
GXFogSlope;

typedef enum
{
    GX_FIFOINTR_COND_DISABLE = 0,
    GX_FIFOINTR_COND_UNDERHALF = 1,
    GX_FIFOINTR_COND_EMPTY = 2
}
GXFifoIntrCond;

typedef enum
{
    GX_FIFOSTAT_EMPTY = 6,
    GX_FIFOSTAT_UNDERHALF = 2,
    GX_FIFOSTAT_OVERHALF = 0,
    GX_FIFOSTAT_FULL = 1
}
GXFifoStat;

static inline void G3X_SetFifoIntrCond(GXFifoIntrCond cond)
{
    reg_G3X_GXSTAT = ((reg_G3X_GXSTAT & ~0xc0000000) |
                      (cond << 30));
}

static inline GXFifoStat G3X_GetCommandFifoStatus(void)
{
    return (GXFifoStat)((reg_G3X_GXSTAT & (0x01000000 |
                                           0x02000000 |
                                           0x04000000)) >> 24);
}

#endif //GUARD_GX_G3X_H
