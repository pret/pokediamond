#ifndef GUARD_GX_G2_H
#define GUARD_GX_G2_H

#include "fx.h"

void G2x_SetBGyAffine_(u32 *ptr, struct Mtx22 *mtx, fx32 a, fx32 b, fx32 c, fx32 d);
void G2x_SetBlendAlpha_(u32 *ptr, fx32 a, fx32 b, fx32 c, fx32 d);
void G2x_SetBlendBrightness_(u16 *ptr, fx32 a, fx32 brightness);
void G2x_SetBlendBrightnessExt_(u16 *ptr, fx32 a, fx32 b, fx32 c, fx32 d, fx32 brightness);
void *G2x_ChangeBlendBrightness_(u16 *ptr, fx32 brightness);

//The g2 and g2_oam headers contain a lot of inline functions and enums that may want to be ported over at some point

#endif //GUARD_GX_G2_H
