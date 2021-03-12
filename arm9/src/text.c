#include "text.h"
#include "heap.h"
#include "string16.h"

const struct FontInfo *gFonts = NULL;

u8 UNK_021C5734[0x200];
u32 UNK_021C5714[8];
u8 UNK_021C570C[8];

extern u32 FUN_0200CA7C(void *func, struct TextPrinter *printer, u32 param2);

extern struct TextPrinter *FUN_0201B6C8(void);
extern void FUN_0200CAB4(u32 param0);
extern void FUN_0201C238(struct TextPrinter *printer);

extern u32 RenderFont(struct TextPrinter *printer);
extern void FUN_0201C1A8(struct TextPrinter *printer);
extern FUN_0201BFDC(); //no idea what this is
extern void GenerateFontHalfRowLookupTable(u8 fgColor, u8 bgColor, u8 shadowColor);
extern void CopyWindowToVram(u32 windowId);

THUMB_FUNC void SetFontsPointer(const struct FontInfo *fonts)
{
    gFonts = fonts;
}

THUMB_FUNC u8 FUN_0201BCC8(void *func, struct TextPrinter *printer, u32 param2)
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

THUMB_FUNC u16 AddTextPrinterParameterized(u32 windowId, u8 fontId, const u16 *str, u32 x, u32 y, u32 speed, void (*callback)(struct TextPrinterTemplate *, u16))
{
    struct TextPrinterTemplate printerTemplate;

    printerTemplate.windowId = windowId;
    printerTemplate.currentChar = str;
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

THUMB_FUNC u16 AddTextPrinterParameterized2(u32 windowId, u8 fontId, const u16 *str, u32 x, u32 y, u32 speed, u32 colors, void (*callback)(struct TextPrinterTemplate *, u16))
{
    struct TextPrinterTemplate printerTemplate;

    printerTemplate.windowId = windowId;
    printerTemplate.currentChar = str;
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

THUMB_FUNC u16 AddTextPrinterParameterized3(u32 windowId, u8 fontId, const u16 *str, u32 x, u32 y, u32 speed, u32 colors, u32 letterSpacing, u32 lineSpacing, void (*callback)(struct TextPrinterTemplate *, u16))
{
    struct TextPrinterTemplate printerTemplate;

    printerTemplate.windowId = windowId;
    printerTemplate.currentChar = str;
    printerTemplate.fontId = fontId;
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

THUMB_FUNC u16 AddTextPrinter(struct TextPrinterTemplate *printerTemplate, u32 speed, void (*callback)(struct TextPrinterTemplate *, u16))
{
    if (!gFonts)
        return 0xff;

    struct TextPrinter *printer = (struct TextPrinter *)AllocFromHeap(0, sizeof(struct TextPrinter));

    printer->active = TRUE;
    printer->state = 0;
    printer->textSpeedBottom = (u8)speed;
    printer->delayCounter = 0;
    printer->scrollDistance = 0;
    printer->japanese = 0;

    for (s32 i = 0; i < 7; i++)
    {
        printer->subStructFields[i] = 0;
    }

    printer->printerTemplate = *printerTemplate;
    printer->printerTemplate.currentChar = String_c_str((struct String *)printer->printerTemplate.currentChar); //TODO clean up
    printer->callback = callback;
    UNK_021C570C[0] = 0;
    FUN_0201C1A8(printer);
    if (speed != 0xff && speed != 0)
    {
        printer->textSpeedBottom += 0xff;
        printer->textSpeedTop = 1;
        printer->minLetterSpacing = FUN_0201BCC8(FUN_0201BFDC, printer, 1);
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
            CopyWindowToVram(printer->printerTemplate.windowId); // CopyWindowToVram?
        }
        FUN_0201C238(printer);
        FreeToHeap((void *)printer);
        return 8;
    }
}
