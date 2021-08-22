#include "text.h"
#include "heap.h"
#include "string16.h"
#include "MI_memory.h"
#include "filesystem.h"
#include "script_buffers.h"
#include "unk_0200CA44.h"
#include "font.h"
#include "graphic/font.naix"

const struct FontInfo *gFonts = NULL;

u16 sFontHalfRowLookupTable[0x100];
BOOL UNK_021C5714[8];
u16 UNK_021C570E;
u16 UNK_021C5710;
u16 UNK_021C5712;
u8 UNK_021C570C;

extern struct TextPrinter *FUN_0201B6C8(void);

extern void FUN_0201C1A8(struct TextPrinter *printer);


extern void * GfGfxLoader_GetCharData(NarcId, s32, s32, struct UnkStruct_0200B870_sub **, u32);


THUMB_FUNC void SetFontsPointer(const struct FontInfo *fonts)
{
    gFonts = fonts;
}

THUMB_FUNC u8 FUN_0201BCC8(void (*func)(u32, void *), void *printer, u32 param2)
{
    u32 *r4 = UNK_021C5714;
    s32 i;
    for (i = 0; i < 8; i++, r4++)
    {
        if (r4[0] != 0)
        {
            continue;
        }
        UNK_021C5714[i] = FUN_0200CA7C(func, printer, param2);
        if (UNK_021C5714[i] != 0)
        {
            break;
        }
        i = 8;
        break;
    }
    return (u8)i;
}

THUMB_FUNC void FUN_0201BCFC(u32 param0)
{
    GF_ASSERT(param0 < 8);
    GF_ASSERT(UNK_021C5714[param0] != 0);
    if (param0 >= 8)
    {
        return;
    }
    if (UNK_021C5714[param0] == 0)
    {
        return;
    }
    struct TextPrinter *printer = FUN_0201B6C8();
    if (printer)
    {
        FUN_0201C238(printer);
        FreeToHeap((void *)printer);
    }
    FUN_0200CAB4(UNK_021C5714[param0]);
    UNK_021C5714[param0] = 0;
}

THUMB_FUNC BOOL FUN_0201BD44(u32 param0)
{
    return UNK_021C5714[param0] ? TRUE : FALSE;
}

THUMB_FUNC void FUN_0201BD5C(void)
{
    for (s32 i = 0; i < 8; i++)
    {
        UNK_021C5714[i] = 0;
    }
}

THUMB_FUNC u8 FUN_0201BD70(u32 param0)
{
    return (u8)FUN_0201BD44(param0);
}

THUMB_FUNC void FUN_0201BD7C(u32 param0)
{
    FUN_0201BCFC(param0);
}

THUMB_FUNC u16 AddTextPrinterParameterized(struct Window * window, u8 fontId, struct String *str, u32 x, u32 y, u32 speed, u8 (*callback)(struct TextPrinterTemplate *, u16))
{
    struct TextPrinterTemplate printerTemplate;

    printerTemplate.window = window;
    printerTemplate.currentChar.wrapped = str;
    printerTemplate.fontId = fontId;
    printerTemplate.x = (u8)x;
    printerTemplate.y = (u8)y;
    printerTemplate.currentX = (u8)x;
    printerTemplate.currentY = (u8)y;
    printerTemplate.letterSpacing = gFonts[fontId].letterSpacing;
    printerTemplate.lineSpacing = gFonts[fontId].lineSpacing;
    printerTemplate.unk = gFonts[fontId].unk;
    printerTemplate.fgColor = gFonts[fontId].fgColor;
    printerTemplate.bgColor = gFonts[fontId].bgColor;
    printerTemplate.shadowColor = gFonts[fontId].shadowColor;
    printerTemplate.unk2 = 0;
    printerTemplate.unk3 = 0;
    printerTemplate.unk4 = 255;
    return AddTextPrinter(&printerTemplate, speed, callback);
}

THUMB_FUNC u16 AddTextPrinterParameterized2(struct Window * window, u8 fontId, struct String *str, u32 x, u32 y, u32 speed, u32 colors, u8 (*callback)(struct TextPrinterTemplate *, u16))
{
    struct TextPrinterTemplate printerTemplate;

    printerTemplate.window = window;
    printerTemplate.currentChar.wrapped = str;
    printerTemplate.fontId = fontId;
    printerTemplate.x = (u8)x;
    printerTemplate.y = (u8)y;
    printerTemplate.currentX = (u8)x;
    printerTemplate.currentY = (u8)y;
    printerTemplate.letterSpacing = gFonts[fontId].letterSpacing;
    printerTemplate.lineSpacing = gFonts[fontId].lineSpacing;
    printerTemplate.unk = gFonts[fontId].unk;
    printerTemplate.fgColor = (u8)(colors >> 16);
    printerTemplate.shadowColor = (u8)(colors >> 8);
    printerTemplate.bgColor = (u8)colors;
    printerTemplate.unk2 = 0;
    printerTemplate.unk3 = 0;
    printerTemplate.unk4 = 255;
    return AddTextPrinter(&printerTemplate, speed, callback);
}

THUMB_FUNC u16 AddTextPrinterParameterized3(struct Window * window, u32 fontId, struct String *str, u32 x, u32 y, u32 speed, u32 colors, u32 letterSpacing, u32 lineSpacing, u8 (*callback)(struct TextPrinterTemplate *, u16))
{
    struct TextPrinterTemplate printerTemplate;

    printerTemplate.window = window;
    printerTemplate.currentChar.wrapped = str;
    printerTemplate.fontId = (u8)fontId;
    printerTemplate.x = (u8)x;
    printerTemplate.y = (u8)y;
    printerTemplate.currentX = (u8)x;
    printerTemplate.currentY = (u8)y;
    printerTemplate.letterSpacing = (u8)letterSpacing;
    printerTemplate.lineSpacing = (u8)lineSpacing;
    printerTemplate.unk = gFonts[fontId].unk;
    printerTemplate.fgColor = (u8)(colors >> 16);
    printerTemplate.shadowColor = (u8)(colors >> 8);
    printerTemplate.bgColor = (u8)colors;
    printerTemplate.unk2 = 0;
    printerTemplate.unk3 = 0;
    printerTemplate.unk4 = 255;
    return AddTextPrinter(&printerTemplate, speed, callback);
}

THUMB_FUNC u16 AddTextPrinter(struct TextPrinterTemplate *printerTemplate, u32 speed, u8 (*callback)(struct TextPrinterTemplate *, u16))
{
    if (!gFonts)
        return 0xff;

    struct TextPrinter *printer = (struct TextPrinter *)AllocFromHeap(0, sizeof(struct TextPrinter));

    printer->active = TRUE;
    printer->state = 0;
    printer->textSpeedBottom = (u8)speed;
    printer->delayCounter = 0;
    printer->scrollDistance = 0;
    printer->Unk29 = 0;

    for (s32 i = 0; i < 7; i++)
    {
        printer->subStructFields[i] = 0;
    }

    printer->printerTemplate = *printerTemplate;
    printer->printerTemplate.currentChar.raw = String_c_str(printer->printerTemplate.currentChar.wrapped);
    printer->callback = callback;
    UNK_021C570C = 0;
    FUN_0201C1A8(printer);
    if (speed != 0xff && speed != 0)
    {
        printer->textSpeedBottom--;
        printer->textSpeedTop = 1;
        printer->minLetterSpacing = FUN_0201BCC8((void (*)(u32, void *))RunTextPrinter, printer, 1);
        return printer->minLetterSpacing;
    }
    else
    {
        u32 j = 0;
        printer->textSpeedBottom = 0;
        printer->textSpeedTop = 0;
        GenerateFontHalfRowLookupTable(printerTemplate->fgColor, printerTemplate->bgColor, printerTemplate->shadowColor);
        for (; j < 0x400; ++j)
        {
            if (RenderFont(printer) == 1)
            {
                break;
            }
        }
        if (speed != 0xff)
        {
            CopyWindowToVram(printer->printerTemplate.window);
        }
        FUN_0201C238(printer);
        FreeToHeap((void *)printer);
        return 8;
    }
}

THUMB_FUNC void RunTextPrinter(u32 param0, struct TextPrinter *printer)
{
#pragma unused(param0)
    if (UNK_021C570C == 0)
    {
        if (printer->Unk29 == 0)
        {
            printer->Unk2A = 0;
            GenerateFontHalfRowLookupTable(printer->printerTemplate.fgColor, printer->printerTemplate.bgColor, printer->printerTemplate.shadowColor);
            u32 temp = RenderFont(printer);
            switch (temp)
            {
                case 0:
                    CopyWindowToVram(printer->printerTemplate.window);
                    //fallthrough
                case 3:
                    if (printer->callback == NULL)
                    {
                        return;
                    }
                    printer->Unk29 = printer->callback(&printer->printerTemplate, printer->Unk2A);
                    return;
                case 1:
                    FUN_0201BCFC(printer->minLetterSpacing);
                    return;
                default:
                    return;
            }
        }
        else
        {
            printer->Unk29 = printer->callback(&printer->printerTemplate, printer->Unk2A);
        }
    }
}

THUMB_FUNC u32 RenderFont(struct TextPrinter *printer)
{
    u32 ret;
    while (TRUE)
    {
        ret = FontFunc(printer->printerTemplate.fontId, printer);
        if (ret != 2)
        {
            return ret;
        }
    }
}

THUMB_FUNC void GenerateFontHalfRowLookupTable(u8 fgColor, u8 bgColor, u8 shadowColor)
{
    s32 r5 = 0;
    u32 sp20[4];
    s32 i; // sp14
    s32 j; // sp10
    s32 k; // spC
    s32 l; // r3

    sp20[0] = 0;
    sp20[1] = fgColor;
    sp20[2] = shadowColor;
    sp20[3] = bgColor;

    // These are accessed by a pointer to UNK_021C570C due to -ipa file
    UNK_021C5712 = bgColor;
    UNK_021C570E = fgColor;
    UNK_021C5710 = shadowColor;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 4; k++)
            {
                for (l = 0; l < 4; l++)
                {
                    sFontHalfRowLookupTable[r5++] = (u16)((sp20[l] << 12) | (sp20[k] << 8) | (sp20[j] << 4) | (sp20[i] << 0));
                }
            }
        }
    }
}

THUMB_FUNC void DecompressGlyphTile(const u16 *src, u16 *dst)
{
    dst[0] = sFontHalfRowLookupTable[(u32)src[0] >> 8];
    dst[1] = sFontHalfRowLookupTable[(u8)src[0]];
    dst[2] = sFontHalfRowLookupTable[(u32)src[1] >> 8];
    dst[3] = sFontHalfRowLookupTable[(u8)src[1]];
    dst[4] = sFontHalfRowLookupTable[(u32)src[2] >> 8];
    dst[5] = sFontHalfRowLookupTable[(u8)src[2]];
    dst[6] = sFontHalfRowLookupTable[(u32)src[3] >> 8];
    dst[7] = sFontHalfRowLookupTable[(u8)src[3]];
    dst[8] = sFontHalfRowLookupTable[(u32)src[4] >> 8];
    dst[9] = sFontHalfRowLookupTable[(u8)src[4]];
    dst[10] = sFontHalfRowLookupTable[(u32)src[5] >> 8];
    dst[11] = sFontHalfRowLookupTable[(u8)src[5]];
    dst[12] = sFontHalfRowLookupTable[(u32)src[6] >> 8];
    dst[13] = sFontHalfRowLookupTable[(u8)src[6]];
    dst[14] = sFontHalfRowLookupTable[(u32)src[7] >> 8];
    dst[15] = sFontHalfRowLookupTable[(u8)src[7]];
}

THUMB_FUNC void FUN_0201C1A8(struct TextPrinter *printer)
{
    printer->Unk2C = NULL;
}

THUMB_FUNC u16 *FUN_0201C1B0(void)
{
    void *res = AllocFromHeap(0, 32 * 24 * sizeof(u16));
    struct UnkStruct_0200B870_sub * var;
    void *tmp = GfGfxLoader_GetCharData(NARC_GRAPHIC_FONT, NARC_font_narc_0005_NCGR, 0, &var, 0);
    MI_CpuCopy32(var->unk_14, res, 32 * 24 * sizeof(u16));
    FreeToHeap(tmp);
    return res;
}

THUMB_FUNC void FUN_0201C1EC(struct TextPrinter *printer, u32 param1, u32 param2, u32 param3)
{
#pragma unused (param1, param2)
    struct Window * window = printer->printerTemplate.window;
    if (printer->Unk2C == NULL)
    {
        printer->Unk2C = FUN_0201C1B0();
    }
    u16 * r6 = printer->Unk2C + param3 * 24 * 8;
    u16 r2 = (u16)((GetWindowWidth(window) - 3) * 8);
    BlitBitmapRectToWindow(window, r6, 0, 0, 24, 32, r2, 0, 24, 32);
}

THUMB_FUNC void FUN_0201C238(struct TextPrinter *printer)
{
    if (printer->Unk2C == NULL)
    {
        return;
    }
    FreeToHeap(printer->Unk2C);
    printer->Unk2C = NULL;
}
