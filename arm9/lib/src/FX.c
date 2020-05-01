#include "global.h"
#include "main.h"
#include "fx.h"

void FX_Init(){
    return;
}

s32 FX_Modf(s32 x, s32 *iptr){
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
