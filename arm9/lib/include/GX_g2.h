#ifndef GUARD_GX_G2_H
#define GUARD_GX_G2_H

#include "fx.h"
#include "registers.h"

void G2x_SetBGyAffine_(u32 *ptr, struct Mtx22 *mtx, fx32 a, fx32 b, fx32 c, fx32 d);
void G2x_SetBlendAlpha_(u32 *ptr, fx32 a, fx32 b, fx32 c, fx32 d);
void G2x_SetBlendBrightness_(u16 *ptr, fx32 a, fx32 brightness);
void G2x_SetBlendBrightnessExt_(u16 *ptr, fx32 a, fx32 b, fx32 c, fx32 d, fx32 brightness);
void G2x_ChangeBlendBrightness_(u16 *ptr, fx32 brightness);

typedef struct
{
    u8      planeMask:5;
    u8      effect:1;
    u8      _reserve:2;
}
        GXWndPlane;

typedef enum
{
    GX_WND_PLANEMASK_NONE = 0x0000,
    GX_WND_PLANEMASK_BG0 = 0x0001,
    GX_WND_PLANEMASK_BG1 = 0x0002,
    GX_WND_PLANEMASK_BG2 = 0x0004,
    GX_WND_PLANEMASK_BG3 = 0x0008,
    GX_WND_PLANEMASK_OBJ = 0x0010
}
        GXWndPlaneMask;

static inline void G2_SetWndOutsidePlane(int wnd, BOOL effect)
{
    u32     tmp;

    tmp = ((reg_G2_WINOUT & ~REG_G2_WINOUT_WINOUT_MASK) | ((u32)wnd << REG_G2_WINOUT_WINOUT_SHIFT));

    if (effect)
    {
        tmp |= (0x20 << REG_G2_WINOUT_WINOUT_SHIFT);    // EFCT
    }

    reg_G2_WINOUT = (u16)tmp;
}

//The g2 and g2_oam headers contain a lot of inline functions and enums that may want to be ported over at some point

#endif //GUARD_GX_G2_H
