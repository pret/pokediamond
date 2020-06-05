#include "global.h"
#include "fx.h"


ARM_FUNC fx32 FX_Div(fx32 numerator, fx32 denominator){
    FX_DivAsync(numerator, denominator);
    return FX_GetDivResult();
}

ARM_FUNC fx32 FX_Inv(fx32 x){
    FX_InvAsync(x);
    return FX_GetDivResult();
}

ARM_FUNC fx32 FX_Sqrt(fx32 x){
    if (x > 0)
    {
        reg_CP_SQRTCNT = 0x1;
        reg_CP_SQRT_PARAM = (u64)((fx64)x << 32);
        return FX_GetSqrtResult();
    }
    else
    {
        return 0;
    }
}

ARM_FUNC fx64c FX_GetDivResultFx64c(){
    while (reg_CP_DIVCNT & 0x8000) {}
    return (fx64c)reg_CP_DIV_RESULT;
}

ARM_FUNC fx32 FX_GetDivResult(){
    while (reg_CP_DIVCNT & 0x8000) {}
    return (fx32)((reg_CP_DIV_RESULT + (1 << (0x14 - 1))) >> 0x14);
}

ARM_FUNC void FX_InvAsync(fx32 x){
    reg_CP_DIVCNT = 0x1;
    reg_CP_DIV_NUMER = (fx64)0x00001000 << 32;
    reg_CP_DIV_DENOM = (u32)x;
}

ARM_FUNC fx32 FX_GetSqrtResult(){
    while (reg_CP_SQRTCNT & 0x8000) {}
    return (fx32)((reg_CP_SQRT_RESULT + (1 << (0xA - 1))) >> 0xA);
}

ARM_FUNC void FX_DivAsync(fx32 numerator, fx32 denominator){
    reg_CP_DIVCNT = 0x1;
    reg_CP_DIV_NUMER = (u64)((fx64)numerator << 32);
    reg_CP_DIV_DENOM = (u32)denominator;
}

ARM_FUNC fx32 FX_DivS32(fx32 numerator, fx32 denominator){
    reg_CP_DIVCNT = 0x0;
    *(REGType32v *)&reg_CP_DIV_NUMER = (u32)numerator; //32bit write for some reason
    reg_CP_DIV_DENOM = (u32)denominator;
    while (reg_CP_DIVCNT & 0x8000) {}
    return (fx32)(*(REGType32v *)&reg_CP_DIV_RESULT);
}

ARM_FUNC fx32 FX_ModS32(fx32 num, fx32 mod){
    reg_CP_DIVCNT = 0x0;
    *(REGType32v *)&reg_CP_DIV_NUMER = (u32)num; //32bit write for some reason
    reg_CP_DIV_DENOM = (u32)mod;
    while (reg_CP_DIVCNT & 0x8000) {}
    return (fx32)(*(REGType32v *)&reg_CP_DIVREM_RESULT);
}
