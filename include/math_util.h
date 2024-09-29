#ifndef POKEDIAMOND_MATH_UTIL_H
#define POKEDIAMOND_MATH_UTIL_H
#include "fx.h"

/*
 * Trigonometric functions
 */
s32 Sin(u16 degrees);
s32 Cos(u16 degrees);
s32 Sin_Wrap(u16 degrees);
s32 Cos_Wrap(u16 degrees);
u16 MathUtil_0201B9A0(u16 x);
s32 Sin32(s32 degrees);

/*
 * Random number generators
 */
u32 GetLCRNGSeed();
void SetLCRNGSeed(u32 seed);
u16 LCRandom(void);

u32 PRandom(u32 seed);

void SetMTRNGSeed(u32 seed);
u32 MTRandom(void);

/*
 * Nitro FX specific functions
 */
void MTX22_2DAffine(struct Mtx22 *mtx, u16 radians, fx32 x, fx32 y, u8 type);

/*
 * Vector functions
 */
s32 CircularDistance(s32 x1, s32 y1, s32 x2, s32 y2);
s32 MathUtil_0201BC84(u16 arg0, s32 arg1);

s32 CALC_SomeDeadstrippedFunction(s32 arg);

#endif // POKEDIAMOND_MATH_UTIL_H
