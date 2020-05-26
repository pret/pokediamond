#include "global.h"
#include "main.h"
#include "fx.h"

const fx16 FX_AtanTable_[] = {
    FX16_CONST(0.0),
    FX16_CONST(0.019775390625),
    FX16_CONST(0.039794921875),
    FX16_CONST(0.0595703125),
    FX16_CONST(0.07958984375),
    FX16_CONST(0.099365234375),
    FX16_CONST(0.119384765625),
    FX16_CONST(0.13916015625),
    FX16_CONST(0.158935546875),
    FX16_CONST(0.1787109375),
    FX16_CONST(0.198486328125),
    FX16_CONST(0.21826171875),
    FX16_CONST(0.238037109375),
    FX16_CONST(0.2578125),
    FX16_CONST(0.27734375),
    FX16_CONST(0.297119140625),
    FX16_CONST(0.316650390625),
    FX16_CONST(0.336181640625),
    FX16_CONST(0.355712890625),
    FX16_CONST(0.375244140625),
    FX16_CONST(0.394775390625),
    FX16_CONST(0.4140625),
    FX16_CONST(0.433349609375),
    FX16_CONST(0.45263671875),
    FX16_CONST(0.471923828125),
    FX16_CONST(0.4912109375),
    FX16_CONST(0.51025390625),
    FX16_CONST(0.529296875),
    FX16_CONST(0.54833984375),
    FX16_CONST(0.5673828125),
    FX16_CONST(0.586181640625),
    FX16_CONST(0.60498046875),
    FX16_CONST(0.623779296875),
    FX16_CONST(0.642578125),
    FX16_CONST(0.6611328125),
    FX16_CONST(0.6796875),
    FX16_CONST(0.6982421875),
    FX16_CONST(0.716552734375),
    FX16_CONST(0.73486328125),
    FX16_CONST(0.753173828125),
    FX16_CONST(0.771240234375),
    FX16_CONST(0.789306640625),
    FX16_CONST(0.807373046875),
    FX16_CONST(0.8251953125),
    FX16_CONST(0.843017578125),
    FX16_CONST(0.86083984375),
    FX16_CONST(0.878662109375),
    FX16_CONST(0.89599609375),
    FX16_CONST(0.91357421875),
    FX16_CONST(0.930908203125),
    FX16_CONST(0.9482421875),
    FX16_CONST(0.965576171875),
    FX16_CONST(0.982666015625),
    FX16_CONST(0.999755859375),
    FX16_CONST(1.0166015625),
    FX16_CONST(1.033447265625),
    FX16_CONST(1.05029296875),
    FX16_CONST(1.06689453125),
    FX16_CONST(1.08349609375),
    FX16_CONST(1.099853515625),
    FX16_CONST(1.1162109375),
    FX16_CONST(1.132568359375),
    FX16_CONST(1.148681640625),
    FX16_CONST(1.164794921875),
    FX16_CONST(1.1806640625),
    FX16_CONST(1.196533203125),
    FX16_CONST(1.21240234375),
    FX16_CONST(1.22802734375),
    FX16_CONST(1.24365234375),
    FX16_CONST(1.259033203125),
    FX16_CONST(1.2744140625),
    FX16_CONST(1.28955078125),
    FX16_CONST(1.3046875),
    FX16_CONST(1.31982421875),
    FX16_CONST(1.334716796875),
    FX16_CONST(1.349609375),
    FX16_CONST(1.364501953125),
    FX16_CONST(1.379150390625),
    FX16_CONST(1.3935546875),
    FX16_CONST(1.408203125),
    FX16_CONST(1.42236328125),
    FX16_CONST(1.436767578125),
    FX16_CONST(1.450927734375),
    FX16_CONST(1.46484375),
    FX16_CONST(1.47900390625),
    FX16_CONST(1.49267578125),
    FX16_CONST(1.506591796875),
    FX16_CONST(1.520263671875),
    FX16_CONST(1.53369140625),
    FX16_CONST(1.547119140625),
    FX16_CONST(1.560546875),
    FX16_CONST(1.57373046875),
    FX16_CONST(1.5869140625),
    FX16_CONST(1.60009765625),
    FX16_CONST(1.613037109375),
    FX16_CONST(1.6259765625),
    FX16_CONST(1.638671875),
    FX16_CONST(1.6513671875),
    FX16_CONST(1.663818359375),
    FX16_CONST(1.676513671875),
    FX16_CONST(1.688720703125),
    FX16_CONST(1.701171875),
    FX16_CONST(1.71337890625),
    FX16_CONST(1.7255859375),
    FX16_CONST(1.737548828125),
    FX16_CONST(1.74951171875),
    FX16_CONST(1.76123046875),
    FX16_CONST(1.77294921875),
    FX16_CONST(1.78466796875),
    FX16_CONST(1.79638671875),
    FX16_CONST(1.807861328125),
    FX16_CONST(1.819091796875),
    FX16_CONST(1.83056640625),
    FX16_CONST(1.841796875),
    FX16_CONST(1.852783203125),
    FX16_CONST(1.864013671875),
    FX16_CONST(1.874755859375),
    FX16_CONST(1.8857421875),
    FX16_CONST(1.896484375),
    FX16_CONST(1.9072265625),
    FX16_CONST(1.91796875),
    FX16_CONST(1.928466796875),
    FX16_CONST(1.93896484375),
    FX16_CONST(1.94921875),
    FX16_CONST(1.95947265625),
    FX16_CONST(1.9697265625),
    FX16_CONST(1.97998046875),
    FX16_CONST(1.989990234375),
    FX16_CONST(2.0),
};

ARM_FUNC u16 FX_Atan(fx32 x){
    if (x >= 0)
    {
        if (x > 0x1000)
        {
            x = FX_Inv(x);
            fx16 y = FX_AtanTable_[x >> 5];
            return (u16)(0x4000 - y);
        }
        else if (x < 0x1000)
        {
            return (u16)FX_AtanTable_[x >> 5];
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
            return (u16)(y - 0x4000);
        }
        else if (x > -0x1000)
        {
            return (u16)(-FX_AtanTable_[-x >> 5]);
        }
        else
        {
            return (u16)(-0x2000);
        }
    }
}

ARM_FUNC u16 FX_Atan2(fx32 x, fx32 y){
    u32 positive, bias, denominator, numerator;
    if (x > 0)
    {
        if (y > 0)
        {
            if (y > x)
            {
                numerator = (u32)x;
                denominator = (u32)y;
                bias = 0;
                positive = TRUE;
            }
            else if (y < x)
            {
                numerator = (u32)y;
                denominator = (u32)x;
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
                numerator = (u32)y;
                denominator = (u32)x;
                bias = 0x4000;
                positive = TRUE;
            }
            else if (y > x)
            {
                numerator = (u32)x;
                denominator = (u32)y;
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
                numerator = (u32)x;
                denominator = (u32)y;
                bias = (u32)(-0x8000);
                positive = TRUE;
            }
            else if (y < x)
            {
                numerator = (u32)y;
                denominator = (u32)x;
                bias = (u32)(-0x4000);
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
                numerator = (u32)y;
                denominator = (u32)x;
                bias = (u32)(-0x4000);
                positive = TRUE;
            }
            else if (y > x)
            {
                numerator = (u32)x;
                denominator = (u32)y;
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
        return (u16)(bias + FX_AtanTable_[FX_Div((fx32)numerator, (fx32)denominator) >> 5]);
    else
        return (u16)(bias - FX_AtanTable_[FX_Div((fx32)numerator, (fx32)denominator) >> 5]);
}
