#include "global.h"
#include "unk_0200A104.h"
#include "GX_g2.h"
#include "MI_memory.h"

struct UnkStruct_0200A104 UNK_021C4694;

struct UnkStruct_0200A104 UNK_021C4674;

THUMB_FUNC void FUN_0200A104(struct UnkStruct_0200A104 *param0)
{
    u32 r4 = 0;

    if (param0->unk0a != param0->unk1a + param0->unk10 * param0->unk14 &&
        param0->unk1a != param0->unk0a)
    {
        param0->unk1a += param0->unk10 * param0->unk14;
        param0->unk18 += param0->unk16;

        if (param0->unk18 >= param0->unk08)
        {
            param0->unk1a += param0->unk10;
            if (param0->unk1a != param0->unk0a)
            {
                param0->unk18 -= param0->unk08;
            }
            else
            {
                r4 = 1;
            }
        }
    }
    else
    {
        param0->unk1a = param0->unk0a;
        r4 = 1;
    }

    if ((param0->unk04 & 1) != 0)
    {
        G2x_SetBlendBrightness_(0x04000050, param0->unk00, param0->unk1a);
    }
    else if ((param0->unk04 & 2) != 0)
    {
        G2x_SetBlendBrightness_(0x04001050, param0->unk00, param0->unk1a);
    }

    if (r4 == 1)
    {
        param0->unk1c = 0;
    }
}

THUMB_FUNC void FUN_0200A1A0(
    struct UnkStruct_0200A104 *param0, u16 param1, s16 param2, s16 param3, u32 param4, u32 param5)
{
    GF_ASSERT(param0->unk1c == 0);

    param0->unk1c = 1;
    param0->unk00 = (u8)param4;
    param0->unk04 = (u8)param5;
    param0->unk08 = param1;
    param0->unk0a = param2;
    param0->unk1a = param3;
    param0->unk12 = param3 - param2;

    if (param0->unk12 > 0)
    {
        param0->unk10 = -1;
    }
    else
    {
        param0->unk10 = 1;
        param0->unk12 *= -1;
    }

    param0->unk14 = param0->unk12 / param1;
    param0->unk16 = param0->unk12 % param1;
    param0->unk18 = 0;
}

THUMB_FUNC void FUN_0200A208(u16 param0, s16 param1, s16 param2, u32 param3, u32 param4)
{
    if (param0 != 0)
    {
        if ((param4 & 1) != 0)
        {
            G2x_SetBlendBrightness_(0x04000050, param3, param2);
            FUN_0200A1A0(&UNK_021C4694, param0, param1, param2, param3, 1);
        }

        if ((param4 & 2) != 0)
        {
            G2x_SetBlendBrightness_(0x04001050, param3, param2);
            FUN_0200A1A0(&UNK_021C4674, param0, param1, param2, param3, 2);
        }
    }
}

THUMB_FUNC void FUN_0200A274(fx32 brightness, fx32 param1, u32 param2)
{

    if ((param2 & 1) != 0)
    {
        G2x_SetBlendBrightness_(0x04000050, param1, brightness);
    }

    if ((param2 & 2) != 0)
    {
        G2x_SetBlendBrightness_(0x04001050, param1, brightness);
    }

    FUN_0200A2D8(param2);
}

THUMB_FUNC void FUN_0200A2AC(void)
{
    MI_CpuFill8(&UNK_021C4694, 0, sizeof(struct UnkStruct_0200A104));
    MI_CpuFill8(&UNK_021C4674, 0, sizeof(struct UnkStruct_0200A104));

    UNK_021C4694.unk1c = 0;
    UNK_021C4674.unk1c = 0;
}

THUMB_FUNC void FUN_0200A2D8(u32 param0)
{
    if (param0 & 1)
    {
        MI_CpuFill8(&UNK_021C4694, 0, sizeof(struct UnkStruct_0200A104));
        UNK_021C4694.unk1c = 0;
    }

    if (param0 & 2)
    {
        MI_CpuFill8(&UNK_021C4674, 0, sizeof(struct UnkStruct_0200A104));
        UNK_021C4674.unk1c = 0;
    }
}

THUMB_FUNC void FUN_0200A318(void)
{
    if (UNK_021C4694.unk1c)
    {
        FUN_0200A104(&UNK_021C4694);
    }

    if (UNK_021C4674.unk1c)
    {
        FUN_0200A104(&UNK_021C4674);
    }
}

THUMB_FUNC u32 FUN_0200A344(u32 param0)
{
    if (param0 == 3)
    {
        if (UNK_021C4694.unk1c == 0 && UNK_021C4674.unk1c == 0)
        {
            return 1;
        }
    }
    else if (param0 == 1)
    {
        if (UNK_021C4694.unk1c == 0)
        {
            return 1;
        }
    }
    else if (param0 == 2)
    {
        if (UNK_021C4674.unk1c == 0)
        {
            return 1;
        }
    }

    return 0;
}
