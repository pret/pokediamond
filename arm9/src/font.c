#include "global.h"
#include "font.h"
#include "gf_gfx_loader.h"
#include "graphic/font.naix"
#include "render_text.h"
#include "string16.h"
#include "string_control_code.h"
#include "text.h"
#include "unk_02021590.h"

struct UnkStruct_02002C14 *UNK_02106FC8;

struct UnkStruct_02002C14 UNK_02106FCC;

const u16 UNK_020ECB54[4][2] = {
    { NARC_font_narc_0000_bin, FALSE },
    { NARC_font_narc_0001_bin, FALSE },
    { NARC_font_narc_0002_bin, FALSE },
    { NARC_font_narc_0003_bin, FALSE }
};

const struct FontInfo gFontInfos[5] = {
    { 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02 },
    { 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02 },
    { 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02 },
    { 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
};

void FUN_02002C14()
{
    UNK_02106FC8 = &UNK_02106FCC;

    for (u32 i = 0; i < 4; i++)
    {
        UNK_02106FC8->unk84[i] = NULL;
        UNK_02106FC8->unk94[i] = NULL;
    }

    SetFontsPointer(&gFontInfos[0]);
}

void FUN_02002C50(u32 font_id, u32 heap_id)
{
    UNK_02106FC8->unk94[font_id] =
        FontData_New(NARC_GRAPHIC_FONT, UNK_020ECB54[font_id][0], 1, UNK_020ECB54[font_id][1], heap_id);
}

void FUN_02002C84(s32 param0, u32 param1)
{
    GF_ASSERT(param0 < 4);
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    FontData_ModeSwitch(UNK_02106FC8->unk94[param0], 0, param1);
}

void FUN_02002CC0(s32 param0)
{
    GF_ASSERT(param0 < 4);
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    FontData_ModeSwitch(UNK_02106FC8->unk94[param0], 1, 0);
}

void FUN_02002CF8(int param0)
{

    GF_ASSERT(param0 < 4);

    if (UNK_02106FC8->unk84[param0] != NULL)
    {
        u32 i;
        for (i = 0; i < 4; i++)
        {
            if (i != param0 && UNK_020ECB54[i][0] == UNK_020ECB54[param0][0] &&
                UNK_02106FC8->unk94[i] != NULL)
            {
                UNK_02106FC8->unk84[i] = UNK_02106FC8->unk84[param0];
                break;
            }
        }

        if (i == 4)
        {
            FreeToHeap(UNK_02106FC8->unk84[param0]);
            UNK_02106FC8->unk84[param0] = NULL;
        }
    }

    if (UNK_02106FC8->unk94[param0] != NULL)
    {
        FontData_Delete(UNK_02106FC8->unk94[param0]);
        UNK_02106FC8->unk94[param0] = NULL;
    }
}

struct UnkStruct_02002C14_sub *FUN_02002D94(u32 param0, u32 param1)
{
    TryLoadGlyph(UNK_02106FC8->unk94[param0], param1, &UNK_02106FC8->unk00);

    return &UNK_02106FC8->unk00;
}

u32 FontFunc(u32 fontId, struct TextPrinter *printer)
{
    struct TextPrinterSubStruct *subStruct =
        (struct TextPrinterSubStruct *)(&printer->subStructFields);

    if (subStruct->hasGlyphIdBeenSet == 0)
    {
        subStruct->glyphId = fontId;
        subStruct->hasGlyphIdBeenSet = 1;
    }

    return RenderText(printer);
}

u32 FUN_02002DE0(u32 param0, u16 *str, u32 param2)
{
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    return GetStringWidth(UNK_02106FC8->unk94[param0], str, param2);
}

u32 FUN_02002E14(u32 param0, struct String *str, u32 param2)
{
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    return GetStringWidth(UNK_02106FC8->unk94[param0], String_c_str(str), param2);
}

s32 GetFontAttribute(u8 fontId, s32 attr)
{
    u8 ret = 0;
    switch (attr)
    {
        case 0:
            ret = gFontInfos[fontId].maxLetterWidth;
            break;
        case 1:
            ret = gFontInfos[fontId].maxLetterHeight;
            break;
        case 2:
            ret = gFontInfos[fontId].letterSpacing;
            break;
        case 3:
            ret = gFontInfos[fontId].lineSpacing;
            break;
        case 4:
            ret = gFontInfos[fontId].unk;
            break;
        case 5:
            ret = gFontInfos[fontId].fgColor;
            break;
        case 6:
            ret = gFontInfos[fontId].bgColor;
            break;
        case 7:
            ret = gFontInfos[fontId].shadowColor;
            break;
    }

    return ret;
}

void LoadFontPal0(enum GFPalLoadLocation location, enum GFPalSlotOffset palSlotOffset, u32 heap_id)
{
    GfGfxLoader_GXLoadPal(NARC_GRAPHIC_FONT, NARC_font_narc_0006_NCLR, location, palSlotOffset, 0x20, heap_id);
}

void FUN_02002EEC(enum GFPalLoadLocation location, enum GFPalSlotOffset palSlotOffset, u32 heap_id)
{
    GfGfxLoader_GXLoadPal(
        NARC_GRAPHIC_FONT, NARC_font_narc_0007_NCLR, location, palSlotOffset, 0x20, heap_id);
}

s32 FUN_02002F08(u32 param0, struct String *str, u32 param2)
{
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    return GetStringWidthMultiline(UNK_02106FC8->unk94[param0], String_c_str(str), param2);
}

u32 FUN_02002F40(u32 param0, struct String *str, u32 param2, u32 param3)
{
    u32 r0 = FUN_02002E14(param0, str, param2);
    if (r0 < param3)
    {
        return (param3 - r0) / 2;
    }

    return 0;
}

u32 FUN_02002F58(const u16 *str)
{
    u32 r5 = 1;
    while (*str != EOS)
    {
        if (*str == 0xFFFE)
        {
            str = MsgArray_SkipControlCode(str);
            continue;
        }

        if (*str == 0xE000)
        {
            r5++;
            str++;
            continue;
        }

        str++;
    }

    return r5;
}

u32 FUN_02002F90(struct String *str)
{
    return FUN_02002F58(String_c_str(str));
}

s32 FUN_02002F9C(u32 param0, struct String *str)
{
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    return StringGetWidth_SingleLine_HandleClearToControlCode(
        UNK_02106FC8->unk94[param0], String_c_str(str));
}
