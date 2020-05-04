#include "global.h"
#include "main.h"
#include "fx.h"

extern fx16 FX_AtanTable_[];

u16 FX_Atan(fx32 x){
    if (x >= 0)
    {
        if (x > 0x1000)
        {
            x = FX_Inv(x);
            fx16 y = FX_AtanTable_[x >> 5];
            return 0x4000 - y;
        }
        else if (x < 0x1000)
        {
            return FX_AtanTable_[x >> 5];
        }
        else
        {
            return 0x2000;
        }
    }
    else
    {
        if (x < -0x1000)
        {
            x = FX_Inv(-x);
            fx16 y = FX_AtanTable_[x >> 5];
            return y - 0x4000;
        }
        else if (x > -0x1000)
        {
            return -FX_AtanTable_[-x >> 5];
        }
        else
        {
            return -0x2000;
        }
    }
}

u16 FX_Atan2(fx32 x, fx32 y){
    fx32 result;
    u32 positive, bias, denominator, numerator;
    if (x > 0)
    {
        if (y > 0)
        {
            if (y > x)
            {
                numerator = x;
                denominator = y;
                bias = 0;
                positive = TRUE;
            }
            else if (y < x)
            {
                numerator = y;
                denominator = x;
                bias = 0x4000;
                positive = FALSE;
            }
            else
            {
                return 0x2000;
            }
        }
        else if (y < 0)
        {
            y = -y;
            if (y < x)
            {
                numerator = y;
                denominator = x;
                bias = 0x4000;
                positive = TRUE;
            }
            else if (y > x)
            {
                numerator = x;
                denominator = y;
                bias = 0x8000;
                positive = FALSE;
            }
            else
            {
                return 0x6000;
            }
        }
        else
        {
            return 0x4000;
        }
    }
    else if (x < 0)
    {
        x = -x;
        if (y < 0)
        {
            y = -y;
            if (y > x)
            {
                numerator = x;
                denominator = y;
                bias = -0x8000;
                positive = TRUE;
            }
            else if (y < x)
            {
                numerator = y;
                denominator = x;
                bias = -0x4000;
                positive = FALSE;
            }
            else
            {
                return 0xA000;
            }
        }
        else if (y > 0)
        {
            if (y < x)
            {
                numerator = y;
                denominator = x;
                bias = -0x4000;
                positive = TRUE;
            }
            else if (y > x)
            {
                numerator = x;
                denominator = y;
                bias = 0x0;
                positive = FALSE;
            }
            else
            {
                return 0xE000;
            }
        }
        else
        {
            return 0xC000;
        }
    }
    else
    {
        if (y >= 0)
            return 0x0;
        else
            return 0x8000;
    }
    if (denominator == 0x0)
        return 0x0;
    if (positive)
        return bias + FX_AtanTable_[FX_Div(numerator, denominator) >> 5];
    else
        return bias - FX_AtanTable_[FX_Div(numerator, denominator) >> 5];
}
