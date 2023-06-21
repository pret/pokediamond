#include "global.h"
#include "fx.h"
#include "unk_0201CBEC.h"

s32 sub_0201CBEC(s32 x1, s32 y1, s32 x2, s32 y2) 
{
    // Calculate distance between two points with pythagoras
    s32 x_delta = x1 - x2;
    s32 y_delta = y1 - y2;

    return FX_Sqrt((x_delta * x_delta + y_delta * y_delta) << 0xc) >> 0xc;
}
