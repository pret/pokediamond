#include "global.h"
#include "fx.h"
#include "unk_0201CBEC.h"

THUMB_FUNC int FUN_0201CBEC(int x1, int y1, int x2, int y2) 
{
    // Calculate distance between two points with pythagoras
    int x_delta = x1 - x2;
    int y_delta = y1 - y2;

    return FX_Sqrt((x_delta * x_delta + y_delta * y_delta) << 0xc) >> 0xc;
}
