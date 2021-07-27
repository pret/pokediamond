#include "global.h"
#include "sound_chatot.h"
#include "SPI_mic.h"
#include "math_util.h"
#include "proto.h"
#include "sav_chatot.h"
#include "sound.h"
#include "unk_020040F4.h"
#include "unk_020051F4.h"

THUMB_FUNC BOOL FUN_02005CFC()
{
    if (*(u8 *)FUN_02003D38(29) == 1 && FUN_02004ABC(14) == 0)
    {
        FUN_02005DFC();

        return TRUE;
    }

    return FALSE;
}

THUMB_FUNC BOOL FUN_02005D20(struct SaveChatotSoundClip *param0)
{
    u8 *r4 = FUN_02003D38(30);

    if (!Chatot_exists(param0))
    {
        return FALSE;
    }

    if (*r4 != 1)
    {
        return TRUE;
    }

    return FALSE;
}

THUMB_FUNC u32 FUN_02005D48(struct SaveChatotSoundClip *param0, u32 param1, s32 param2, s32 param3)
{
#pragma unused(param1)

    s8 *st0 = FUN_02004DB4();
    u8 *st4 = FUN_02003D38(29);

    if (!FUN_02005D20(param0))
    {
        return 0;
    }

    FUN_02005614(0);
    FUN_02005DFC();
    FUN_02004984(14);
    u16 r4 = (u16)(LCRandom() % 8192);

    Chatot_Decode(st0, Chatot_GetData(param0));

    struct UnkStruct_020040F4_1 st8;

    st8.unk00 = FUN_02004930(14);
    st8.unk04 = 0;
    st8.unk08 = FUN_02004DB4();
    st8.unk0c = 0;
    st8.unk10 = 0;
    st8.unk14 = 2000;
    st8.unk18 = 2000;
    st8.unk20 = (u32)(r4 + 0x8000);
    st8.unk24 = param3 / 2 + 64;
    st8.unk1c = param2;

    u32 res = FUN_02004A6C(&st8, 14);
    FUN_02004AF8(14, param2);
    *st4 = 1;
    FUN_02005E80(0);

    return res;
}

THUMB_FUNC void FUN_02005DFC()
{
    u8 *r5 = FUN_02003D38(15);
    u8 *r4 = FUN_02003D38(29);

    if (*r5 == 1)
    {
        FUN_02004C3C(14);
        FUN_02004A04(14);
    }

    *r4 = 0;
}

THUMB_FUNC u32 Chatot_startRecording()
{
    struct MIC_SamplingData st0;

    st0.unk00 = 2;
    st0.unk04 = FUN_02004DB4();
    st0.unk08 = 2000;
    if ((st0.unk08 & 0x1f) != 0)
    {
        st0.unk08 &= ~0x1f;
    }
    st0.unk0c = 0x4174;
    st0.unk10 = 0;
    st0.unk14 = 0;
    st0.unk18 = 0;

    return GF_MIC_StartAutoSampling(&st0);
}

THUMB_FUNC void Chatot_stopRecording()
{
    GF_MIC_StopAutoSampling();
}

THUMB_FUNC void Chatot_saveRecording(struct SaveChatotSoundClip *param0)
{
    Chatot_Encode(param0, FUN_02004DB4());
}

THUMB_FUNC void FUN_02005E80(u8 param0)
{
    *(u8 *)FUN_02003D38(30) = param0;
}

THUMB_FUNC void FUN_02005E90(struct SaveChatotSoundClip *param0, u32 param1, s32 param2, s32 param3)
{
    struct SaveChatotSoundClip **r0 = FUN_02003D38(35);
    u32 ret;
    if (param0 == 0)
    {
        ret = FUN_02005D48(*r0, param1, param2, param3);
    }
    else
    {
        ret = FUN_02005D48(param0, param1, param2, param3);
    }

    if (ret == 0)
    {
        FUN_02005E80(1);
        FUN_020056AC(0, SPECIES_CHATOT, param3, param2, 11);
    }
}

THUMB_FUNC u32 FUN_02005EE0(struct SaveChatotSoundClip *param0)
{
    if (!Chatot_exists(param0))
    {
        return 0;
    }

    s8 r0 = Chatot_GetData(param0)[15];
    if (r0 < -30)
    {
        return 1;
    }
    else if (r0 >= 30 && r0 < 128)
    {
        return 2;
    }

    return 0;
}

THUMB_FUNC u32 FUN_02005F14(s32 param0)
{
    switch (param0)
    {
        case 0:
        case 1:
        case 5:
        case 11:
        case 12:
            return 1;
        default:
            return 0;
    }
}
