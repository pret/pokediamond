#include "text_02054590.h"
#include "text.h"
#include "unk_02016B94.h"

extern void FUN_0201BD5C(void);
extern void FUN_02002ED0(u32 param0, u32 param1, u32 param2);
extern void FUN_02002EEC(u32 param0, u32 param1, u32 param2);

extern void FUN_0200CD68(
    struct UnkStruct_02016B94_2 *param0, u32 param1, u32 param2, u32 param3, u8 param4, u32 param5);
extern void FUN_0200D0BC(struct Window *param0, u32 param1, u32 param2, u32 param3);

extern void FUN_02002B60(u8 param0);
extern void FUN_02002B7C(u32 param0);
extern void FUN_02002BB8(u32 param0);

extern void FUN_0200D300(struct UnkStruct_02016B94_2 *param0,
    u32 param1,
    u32 param2,
    u32 param3,
    u8 param4,
    u32 param5,
    u32 param6);
extern void FUN_0200D6F8(struct Window *param0, u32 param1, u32 param2, u32 param3, u8 param4);

THUMB_FUNC void FUN_02054590(u32 param0, u32 param1)
{
    if (param1 == 1)
    {
        FUN_0201BD5C();
    }
    FUN_02002ED0(param0, 416, 4);
    FUN_02002EEC(param0, 384, 4);
}

THUMB_FUNC void FUN_020545B8(struct UnkStruct_02016B94_2 *param0, struct Window *param1, u32 param2)
{
    if (param2 == 3)
    {
        FUN_02019064(param0, param1, 3, 2, 19, 27, 4, 12, 813);
    }
    else
    {
        FUN_02019064(param0, param1, 7, 2, 19, 27, 4, 12, 404);
    }
}

THUMB_FUNC void FUN_02054608(struct Window *param0, struct Options *options)
{
    FUN_0200CD68(param0->unk00, FUN_0201AB08(param0), 994, 10, (u8)Options_GetFrame(options), 4);
    FUN_0205464C(param0);
    FUN_0200D0BC(param0, 0, 994, 10);
}

THUMB_FUNC void FUN_0205464C(struct Window *param0)
{
    FillWindowPixelBuffer(param0, 15);
}

THUMB_FUNC u16 FUN_02054658(struct Window * window, const u16 *str, struct Options *options, u8 param3)
{
    FUN_02002B60(param3);
    FUN_02002B7C(0);
    FUN_02002BB8(0);
    return AddTextPrinterParameterized(window, 1, str, 0, 0, (u32)Options_GetTextFrameDelay(options), NULL);
}

THUMB_FUNC u16 DrawFieldMessage(struct Window * window, const u16 *str, u8 fontId, u32 speed, u8 a4, u32 a5)
{
    FUN_02002B60(a4);
    FUN_02002B7C(a5);
    FUN_02002BB8(0);
    return AddTextPrinterParameterized(window, fontId, str, 0, 0, speed, NULL);
}

THUMB_FUNC u8 FUN_020546C8(u32 param0) // bool8?
{
    return !FUN_0201BD70(param0);
}

THUMB_FUNC void FUN_020546E0(
    struct UnkStruct_02016B94_2 *param0, struct Window *param1, u32 param2, u32 param3)
{
    u32 r4 = 0;
    u32 r5 = 0;
    if (param2 <= 1)
    {
        r4 = 9;
        r5 = 20;
    }
    else
    {
        r4 = 2;
        r5 = 27;
    }
    if (param3 == 3)
    {
        FUN_02019064(param0, param1, 3, (u8)r4, 19, (u8)r5, 4, 9, 813);
    }
    else
    {
        FUN_02019064(param0, param1, 7, (u8)r4, 19, (u8)r5, 4, 9, 404);
    }
}

THUMB_FUNC void FUN_02054744(struct Window *param0, u32 param1, u32 param2)
{
    FUN_0200D300(param0->unk00, FUN_0201AB08(param0), 0x399, 9, (u8)param1, param2, 4);
    FillWindowPixelBuffer(param0, 15);
    FUN_0200D6F8(param0, 0, 0x399, 9, (u8)param1);
}
