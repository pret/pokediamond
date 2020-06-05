#include "global.h"
#include "fx.h"

ARM_FUNC void FX_Init(){
    return;
}

ARM_FUNC fx32 FX_Modf(fx32 x, fx32 *iptr){
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
