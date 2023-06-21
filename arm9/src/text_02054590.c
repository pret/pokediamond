#include "global.h"
#include "text_02054590.h"
#include "text.h"
#include "bg_window.h"
#include "font.h"
#include "render_text.h"
#include "render_window.h"

void sub_02054590(enum GFPalLoadLocation location, u32 param1)
{
    if (param1 == 1)
    {
        ResetAllTextPrinters();
    }
    LoadFontPal0(location, GF_PAL_SLOT_OFFSET_13, 4);
    LoadFontPal1(location, GF_PAL_SLOT_OFFSET_12, 4);
}

void sub_020545B8(struct BgConfig *param0, struct Window *param1, u32 param2)
{
    if (param2 == 3)
    {
        AddWindowParameterized(param0, param1, 3, 2, 19, 27, 4, 12, 813);
    }
    else
    {
        AddWindowParameterized(param0, param1, 7, 2, 19, 27, 4, 12, 404);
    }
}

void sub_02054608(struct Window *param0, struct Options *options)
{
    sub_0200CD68(param0->bgConfig, GetWindowBgId(param0), 994, 10, (u8)Options_GetFrame(options), 4);
    sub_0205464C(param0);
    DrawFrameAndWindow2(param0, 0, 994, 10);
}

void sub_0205464C(struct Window *param0)
{
    FillWindowPixelBuffer(param0, 15);
}

u16 sub_02054658(struct Window * window, struct String *str, struct Options *options, u8 param3)
{
    TextFlags_SetCanABSpeedUpPrint(param3);
    sub_02002B7C(0);
    sub_02002BB8(0);
    return AddTextPrinterParameterized(window, 1, str, 0, 0, (u32)Options_GetTextFrameDelay(options), NULL);
}

u16 DrawFieldMessage(struct Window * window, struct String *str, u8 fontId, u32 speed, u8 a4, s32 a5)
{
    TextFlags_SetCanABSpeedUpPrint(a4);
    sub_02002B7C(a5);
    sub_02002BB8(0);
    return AddTextPrinterParameterized(window, fontId, str, 0, 0, speed, NULL);
}

u8 sub_020546C8(u8 textPrinterNumber) // bool8?
{
    return !sub_0201BD70(textPrinterNumber);
}

void sub_020546E0(
    struct BgConfig *param0, struct Window *param1, u32 param2, u32 param3)
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
        AddWindowParameterized(param0, param1, 3, (u8) r4, 19, (u8) r5, 4, 9, 813);
    }
    else
    {
        AddWindowParameterized(param0, param1, 7, (u8) r4, 19, (u8) r5, 4, 9, 404);
    }
}

void sub_02054744(struct Window *param0, u32 param1, u16 param2)
{
    sub_0200D300(param0->bgConfig, GetWindowBgId(param0), 0x399, 9, (u8)param1, param2, 4);
    FillWindowPixelBuffer(param0, 15);
    DrawFrameAndWindow3(param0, 0, 0x399, 9, (u8)param1);
}
