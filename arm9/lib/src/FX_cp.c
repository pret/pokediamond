#include "global.h"
#include "main.h"
#include "fx.h"


fx32 FX_Div(fx32 numerator, fx32 denominator){
    FX_DivAsync(numerator, denominator);
    return FX_GetDivResult();
}

fx32 FX_Inv(fx32 x){
    FX_InvAsync(x);
    return FX_GetDivResult();
}

fx32 FX_Sqrt(fx32 x){
    if (x > 0)
    {
        SETREG16(HW_REG_SQRTCNT, 0x1);
        SETREG64(HW_REG_SQRT_PARAM, (fx64)x << 32);
        return FX_GetSqrtResult();
    }
    else
    {
        return 0;
    }
}

fx64c FX_GetDivResultFx64c(){
    while (READREG16(HW_REG_DIVCNT) & 0x8000);
    return READREG64(HW_REG_DIV_RESULT);
}

fx32 FX_GetDivResult(){
    while (READREG16(HW_REG_DIVCNT) & 0x8000);
    return (READREG64(HW_REG_DIV_RESULT) + (1 << (0x14 - 1))) >> 0x14;
}

void FX_InvAsync(fx32 x){
    SETREG16(HW_REG_DIVCNT, 0x1);
    SETREG64(HW_REG_DIV_NUMER, (fx64)0x00001000 << 32);
    SETREG64(HW_REG_DIV_DENOM, (u32)x);
}

fx32 FX_GetSqrtResult(){
    while (READREG16(HW_REG_SQRTCNT) & 0x8000);
    return (READREG32(HW_REG_SQRT_RESULT) + (1 << (0xA - 1))) >> 0xA;
}

void FX_DivAsync(fx32 numerator, fx32 denominator){
    SETREG16(HW_REG_DIVCNT, 0x1);
    SETREG64(HW_REG_DIV_NUMER, (fx64)numerator << 32);
    SETREG64(HW_REG_DIV_DENOM, (u32)denominator);
}

fx32 FX_Divfx32(fx32 numerator, fx32 denominator){
    SETREG16(HW_REG_DIVCNT, 0x0);
    SETREG32(HW_REG_DIV_NUMER, (u32)numerator); //32bit write for some reason
    SETREG64(HW_REG_DIV_DENOM, (u32)denominator);
    while (READREG16(HW_REG_DIVCNT) & 0x8000);
    return READREG32(HW_REG_DIV_RESULT);
}

fx32 FX_Modfx32(fx32 num, fx32 mod){
    SETREG16(HW_REG_DIVCNT, 0x0);
    SETREG32(HW_REG_DIV_NUMER, (u32)num); //32bit write for some reason
    SETREG64(HW_REG_DIV_DENOM, (u32)mod);
    while (READREG16(HW_REG_DIVCNT) & 0x8000);
    return READREG32(HW_REG_DIVREM_RESULT);
}
