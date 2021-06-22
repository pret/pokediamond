#include "global.h"
#include "font.h"
#include "gf_gfx_loader.h"
#include "render_text.h"
#include "string16.h"
#include "text.h"
#include "graphic/font.naix"

struct UnkStruct_02002C14 *UNK_02106FC8;

struct UnkStruct_02002C14 UNK_02106FCC;

const u16 UNK_020ECB54[4][2] = { {0, 0}, {1, 0}, {2, 0}, {3, 0} };

const struct FontInfo gFontInfos[5] = {
    { 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02 },
    { 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02 },
    { 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02 },
    { 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
};

extern u32 FUN_02021590(u32, u16, u32, u16, u32);
extern void FUN_020215E0(u32, u32, u32);
extern void FUN_020215C8(u32 param0);
extern void FUN_02021750(void *, u32);
extern u32 FUN_020218D8(void *, u16 *str, u32);

THUMB_FUNC void FUN_02002C14()
{
    UNK_02106FC8 = &UNK_02106FCC;

    for (u32 i = 0; i < 4; i++)
    {
        UNK_02106FC8->unk84[i] = NULL;
        UNK_02106FC8->unk94[i] = NULL;
    }

    SetFontsPointer(&gFontInfos[0]);
}

THUMB_FUNC void FUN_02002C50(u32 param0, u32 param1)
{
    UNK_02106FC8->unk94[param0] =
        FUN_02021590(14, UNK_020ECB54[param0][0], 1, UNK_020ECB54[param0][1], param1);
}

THUMB_FUNC void FUN_02002C84(s32 param0, u32 param1)
{
    GF_ASSERT(param0 < 4);
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    FUN_020215E0(UNK_02106FC8->unk94[param0], 0, param1);
}

THUMB_FUNC void FUN_02002CC0(s32 param0)
{
    GF_ASSERT(param0 < 4);
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    FUN_020215E0(UNK_02106FC8->unk94[param0], 1, 0);
}

THUMB_FUNC void FUN_02002CF8(int param0)
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
        FUN_020215C8(UNK_02106FC8->unk94[param0]);
        UNK_02106FC8->unk94[param0] = NULL;
    }
}

THUMB_FUNC struct UnkStruct_02002C14 *FUN_02002D94(u32 param0, u32 param1)
{
    FUN_02021750(UNK_02106FC8->unk94[param0], param1);

    return UNK_02106FC8;
}

THUMB_FUNC u32 FontFunc(u32 fontId, struct TextPrinter *printer)
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

THUMB_FUNC u32 FUN_02002DE0(u32 param0, u16 *str, u32 param2)
{
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    FUN_020218D8(UNK_02106FC8->unk94[param0], str, param2);
}

THUMB_FUNC u32 FUN_02002E14(u32 param0, struct String *str, u32 param2)
{
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    FUN_020218D8(UNK_02106FC8->unk94[param0], String_c_str(str), param2);
}

THUMB_FUNC s32 GetFontAttribute(u8 fontId, s32 attr)
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

THUMB_FUNC void FUN_02002ED0(u32 layer, u32 baseAddr, u32 heap_id)
{
    GfGfxLoader_GXLoadPal(NARC_GRAPHIC_FONT, NARC_font_narc_0006_NCLR, layer, baseAddr, 0x20, heap_id);
}

THUMB_FUNC void FUN_02002EEC(u32 layer, u32 baseAddr, u32 heap_id)
{
    GfGfxLoader_GXLoadPal(NARC_GRAPHIC_FONT, NARC_font_narc_0007_NCLR, layer, baseAddr, 0x20, heap_id);
}
