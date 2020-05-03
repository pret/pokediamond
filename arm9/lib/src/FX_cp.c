#include "global.h"
#include "main.h"
#include "fx.h"
 

s32 FX_Div(s32 numerator, s32 denominator){
    FX_DivAsync(numerator, denominator);
    return FX_GetDivResult();
}

s32 FX_Inv(s32 x){
    FX_InvAsync(x);
    return FX_GetDivResult();
}

s32 FX_Sqrt(s32 x){
    if (x > 0)
    {
        SETREG16(HW_REG_SQRTCNT, 0x1);
        SETREG64(HW_REG_SQRT_PARAM, (s64)x << 32);
        return FX_GetSqrtResult();
    }
    else
    {
        return 0;
    }
}

s64 FX_GetDivResultFx64c(){
    while (READREG16(HW_REG_DIVCNT) & 0x8000);
    return READREG64(HW_REG_DIV_RESULT);
}

s32 FX_GetDivResult(){
    while (READREG16(HW_REG_DIVCNT) & 0x8000);
    return (READREG64(HW_REG_DIV_RESULT) + (1 << (0x14 - 1))) >> 0x14;
}

void FX_InvAsync(s32 x){
    SETREG16(HW_REG_DIVCNT, 0x1);
    SETREG64(HW_REG_DIV_NUMER, (s64)0x00001000 << 32);
    SETREG64(HW_REG_DIV_DENOM, (u32)x);
}

s32 FX_GetSqrtResult(){
    while (READREG16(HW_REG_SQRTCNT) & 0x8000);
    return (READREG32(HW_REG_SQRT_RESULT) + (1 << (0xA - 1))) >> 0xA;
}

void FX_DivAsync(s32 numerator, s32 denominator){
    SETREG16(HW_REG_DIVCNT, 0x1);
    SETREG64(HW_REG_DIV_NUMER, (s64)numerator << 32);
    SETREG64(HW_REG_DIV_DENOM, (u32)denominator);
}

s32 FX_DivS32(s32 numerator, s32 denominator){
    SETREG16(HW_REG_DIVCNT, 0x0);
    SETREG32(HW_REG_DIV_NUMER, (u32)numerator); //32bit write for some reason
    SETREG64(HW_REG_DIV_DENOM, (u32)denominator);
    while (READREG16(HW_REG_DIVCNT) & 0x8000);
    return READREG32(HW_REG_DIV_RESULT);
}

s32 FX_ModS32(s32 num, s32 mod){
    SETREG16(HW_REG_DIVCNT, 0x0);
    SETREG32(HW_REG_DIV_NUMER, (u32)num); //32bit write for some reason
    SETREG64(HW_REG_DIV_DENOM, (u32)mod);
    while (READREG16(HW_REG_DIVCNT) & 0x8000);
    return READREG32(HW_REG_DIVREM_RESULT);
}
