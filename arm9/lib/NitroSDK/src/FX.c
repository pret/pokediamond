#include "nitro/types.h"
#include "fx.h"
#include "code32.h"

void FX_Init() {
    return;
}

fx32 FX_Modf(fx32 x, fx32 *iptr) {
    if (x >= 0)
    {
        *iptr = x & 0x7FFFF000;
        return x & 0xFFF;
    }
    else
    {
        *iptr = -(-x & 0x7FFFF000);
        return -(-x & 0xFFF);
    }
}
