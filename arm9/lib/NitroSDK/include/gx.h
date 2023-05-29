#ifndef GUARD_GX_H
#define GUARD_GX_H

#include "fx.h"
#include "MI_memory.h"
#include "MI_dma.h"
#include "OS_vramExclusive.h"
#include "registers.h"

//temporary while other files aren't decompiled

void GXi_NopClearFifo128_(void *);

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

typedef enum
{
    GX_OBJVRAMMODE_CHAR_2D = (0 << REG_GX_DISPCNT_OBJMAP_SHIFT) | (0 << REG_GX_DISPCNT_EXOBJ_SHIFT),
    GX_OBJVRAMMODE_CHAR_1D_32K =
    (1 << REG_GX_DISPCNT_OBJMAP_SHIFT) | (0 << REG_GX_DISPCNT_EXOBJ_SHIFT),
    GX_OBJVRAMMODE_CHAR_1D_64K =
    (1 << REG_GX_DISPCNT_OBJMAP_SHIFT) | (1 << REG_GX_DISPCNT_EXOBJ_SHIFT),
    GX_OBJVRAMMODE_CHAR_1D_128K =
    (1 << REG_GX_DISPCNT_OBJMAP_SHIFT) | (2 << REG_GX_DISPCNT_EXOBJ_SHIFT),
    GX_OBJVRAMMODE_CHAR_1D_256K =
    (1 << REG_GX_DISPCNT_OBJMAP_SHIFT) | (3 << REG_GX_DISPCNT_EXOBJ_SHIFT)
}
    GXOBJVRamModeChar;

void GX_Init();
u32 GX_HBlankIntr(u32 enable);
u32 GX_VBlankIntr(u32 enable);
void GX_DispOff();
void GX_DispOn();
void GX_SetGraphicsMode(GXDispMode dispMode, GXBGMode bgMode, GXBG0As bg0_2d3d);
void GXS_SetGraphicsMode(GXBGMode mode);
void GXx_SetMasterBrightness_(vu16 *dst, s32 brightness);

static inline void GX_SetMasterBrightness(int brightness)
{
    GXx_SetMasterBrightness_(&reg_GX_MASTER_BRIGHT, brightness);
}

static inline void GX_SetVisiblePlane(int plane)
{
    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT & ~REG_GX_DISPCNT_DISPLAY_MASK) | (plane << REG_GX_DISPCNT_DISPLAY_SHIFT));
}

static inline void GXS_SetVisiblePlane(int plane)
{
    reg_GXS_DB_DISPCNT = (u32)((reg_GXS_DB_DISPCNT & ~REG_GXS_DB_DISPCNT_DISPLAY_MASK) | (plane << REG_GXS_DB_DISPCNT_DISPLAY_SHIFT));
}

static inline void GXS_DispOn(void)
{
    reg_GXS_DB_DISPCNT |= REG_GXS_DB_DISPCNT_MODE_MASK;
}

static inline void GX_SetDispSelect(GXDispSelect sel)
{
    reg_GX_POWCNT = (u16)((reg_GX_POWCNT & ~REG_GX_POWCNT_DSEL_MASK) | (sel << REG_GX_POWCNT_DSEL_SHIFT));
}

static inline void GX_SetBGScrOffset(GXBGScrOffset offset)
{
    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT & ~REG_GX_DISPCNT_BGSCREENOFFSET_MASK) | (offset << REG_GX_DISPCNT_BGSCREENOFFSET_SHIFT));
}

static inline void GX_SetBGCharOffset(GXBGCharOffset offset)
{
    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT & ~REG_GX_DISPCNT_BGCHAROFFSET_MASK) | (offset << REG_GX_DISPCNT_BGCHAROFFSET_SHIFT));
}

static inline void GX_SetVisibleWnd(int window)
{
    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT & ~(REG_GX_DISPCNT_W0_MASK | REG_GX_DISPCNT_W1_MASK | REG_GX_DISPCNT_OW_MASK)) | (window << REG_GX_DISPCNT_W0_SHIFT));
}

static inline void GXS_SetVisibleWnd(int window)
{
    reg_GXS_DB_DISPCNT = (u32)((reg_GXS_DB_DISPCNT & ~(REG_GXS_DB_DISPCNT_W0_MASK | REG_GXS_DB_DISPCNT_W1_MASK | REG_GXS_DB_DISPCNT_OW_MASK)) | (window << REG_GXS_DB_DISPCNT_W0_SHIFT));
}

static inline void GXS_SetOBJVRamModeChar(GXOBJVRamModeChar mode)
{
    reg_GXS_DB_DISPCNT = (u32)(reg_GXS_DB_DISPCNT & ~(REG_GXS_DB_DISPCNT_EXOBJ_CH_MASK | REG_GXS_DB_DISPCNT_OBJMAP_CH_MASK) | mode);
}

#define GX_DEFAULT_DMAID 3

#endif //GUARD_GX_H
