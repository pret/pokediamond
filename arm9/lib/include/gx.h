#ifndef GUARD_GX_H
#define GUARD_GX_H

#include "fx.h"
#include "MI_memory.h"

//temporary while other files aren't decompiled

void GXi_NopClearFifo128_(void *);
void MI_Copy16B(const void *, void *);
void MI_DmaFill32Async(u32, void *, u32, u32, u32, u32);
void MI_DmaFill32(u32, void *, u32, u32);
void MIi_CpuClear32(u32, void *, u32);
void MI_Copy64B(void *src, void *dst);
void MI_WaitDma(u32);
void MI_DmaCopy32Async(u32, const void *, void *, u32, void *, void *);
void MI_DmaCopy16(u32 unk, const void *src, void *dst, u32 size);
void MI_DmaCopy32(u32 unk, const void *src, void *dst, u32 size);
void MIi_CpuCopy32(const void *src, void *dst, u32 size);
void OSi_UnlockVram(u16, u16);
void MIi_CpuClear32(u32, void *, u32);

#include "GXcommon.h"
#include "GX_struct_2d.h"
#include "GX_g3.h"
#include "GX_g3_util.h"
#include "GX_g3x.h"
#include "GX_g3b.h"
#include "GX_asm.h"
#include "GX_vramcnt.h"
#include "GX_bgcnt.h"
#include "GX_load2d.h"
#include "GX_load3d.h"
#include "GX_g2.h"
#include "GX_state.h"
#include "GX_g3imm.h"
#include "GX_dma.h"

void GX_Init();
u32 GX_HBlankIntr(u32 enable);
u32 GX_VBlankIntr(u32 enable);
void GX_DispOff();
void GX_DispOn();
void GX_SetGraphicsMode(u32 mode1, u32 mode2, u32 mode3);
void GXS_SetGraphicsMode(u32 mode);
void GXx_SetMasterBrightness_(vu16 *dst, s32 brightness);

typedef union
{
    u32     raw;
    struct
    {
        u32     bgMode:3;
        u32     bg0_2d3d:1;
        u32     objMapChar:1;
        u32     objMapBmp:2;
        u32     blankScr:1;
        u32     visiblePlane:5;
        u32     visibleWnd:3;
        u32     dispMode:4;
        u32     extObjMapChar:2;
        u32     extObjMapBmp:1;
        u32     hBlankObjProc:1;
        u32     bgCharOffset:3;
        u32     bgScrOffset:3;
        u32     bgExtPltt:1;
        u32     objExtPltt:1;
    };
}
GXDispCnt;

typedef union
{
    u32     raw;
    struct
    {
        u32     bgMode:3;
        u32     _reserve1:1;
        u32     objMapChar:1;
        u32     objMapBmp:2;
        u32     blankScr:1;
        u32     visiblePlane:5;
        u32     visibleWnd:3;
        u32     dispMode:1;
        u32     _reserve2:3;
        u32     extObjMapChar:2;
        u32     _reserve3:1;
        u32     hBlankObjProc:1;
        u32     _reserve4:6;
        u32     bgExtPltt:1;
        u32     objExtPltt:1;
    };
}
GXSDispCnt;

typedef enum
{
    GX_BGMODE_0 = 0,
    GX_BGMODE_1 = 1,
    GX_BGMODE_2 = 2,
    GX_BGMODE_3 = 3,
    GX_BGMODE_4 = 4,
    GX_BGMODE_5 = 5,
    GX_BGMODE_6 = 6
}
GXBGMode;

typedef enum
{
    GX_BG0_AS_2D = 0,
    GX_BG0_AS_3D = 1
}
GXBG0As;

typedef enum
{
    GX_DISPMODE_GRAPHICS = 0x01,
    GX_DISPMODE_VRAM_A = 0x02,
    GX_DISPMODE_VRAM_B = 0x06,
    GX_DISPMODE_VRAM_C = 0x0a,
    GX_DISPMODE_VRAM_D = 0x0e,
    GX_DISPMODE_MMEM = 0x03
}
GXDispMode;

typedef enum
{
    GX_PLANEMASK_NONE = 0x00,
    GX_PLANEMASK_BG0 = 0x01,
    GX_PLANEMASK_BG1 = 0x02,
    GX_PLANEMASK_BG2 = 0x04,
    GX_PLANEMASK_BG3 = 0x08,
    GX_PLANEMASK_OBJ = 0x10
}
GXPlaneMask;

typedef enum
{
    GX_WNDMASK_NONE = 0x00,
    GX_WNDMASK_W0 = 0x01,
    GX_WNDMASK_W1 = 0x02,
    GX_WNDMASK_OW = 0x04
}
GXWndMask;

typedef enum
{
    GX_BGCHAROFFSET_0x00000 = 0x00,
    GX_BGCHAROFFSET_0x10000 = 0x01,
    GX_BGCHAROFFSET_0x20000 = 0x02,
    GX_BGCHAROFFSET_0x30000 = 0x03,
    GX_BGCHAROFFSET_0x40000 = 0x04,
    GX_BGCHAROFFSET_0x50000 = 0x05,
    GX_BGCHAROFFSET_0x60000 = 0x06,
    GX_BGCHAROFFSET_0x70000 = 0x07
}
GXBGCharOffset;

typedef enum
{
    GX_BGSCROFFSET_0x00000 = 0x00,
    GX_BGSCROFFSET_0x10000 = 0x01,
    GX_BGSCROFFSET_0x20000 = 0x02,
    GX_BGSCROFFSET_0x30000 = 0x03,
    GX_BGSCROFFSET_0x40000 = 0x04,
    GX_BGSCROFFSET_0x50000 = 0x05,
    GX_BGSCROFFSET_0x60000 = 0x06,
    GX_BGSCROFFSET_0x70000 = 0x07
}
GXBGScrOffset;

typedef enum
{
    GX_DISP_SELECT_SUB_MAIN = 0,
    GX_DISP_SELECT_MAIN_SUB = 1
}
GXDispSelect;

#endif //GUARD_GX_H
