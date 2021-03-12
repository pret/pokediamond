#include "text.h"
#include "heap.h"
#include "string16.h"

const struct FontInfo *gFonts = NULL;

u8 UNK_021C5734[0x200];
u32 UNK_021C5714[8];
u8 UNK_021C570C[8];

extern u32 FUN_0200CA7C(void (*func)(u32, struct TextPrinter *), struct TextPrinter *printer, u32 param2);

extern struct TextPrinter *FUN_0201B6C8(void);
extern void FUN_0200CAB4(u32 param0);
extern void FUN_0201C238(struct TextPrinter *printer);

extern void FUN_0201C1A8(struct TextPrinter *printer);
extern void CopyWindowToVram(u32 windowId);

extern u32 FontFunc(u8 fontId, struct TextPrinter *printer);

THUMB_FUNC void SetFontsPointer(const struct FontInfo *fonts)
{
    gFonts = fonts;
}

THUMB_FUNC u8 FUN_0201BCC8(void (*func)(u32, struct TextPrinter *), struct TextPrinter *printer, u32 param2)
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

THUMB_FUNC u16 AddTextPrinterParameterized(u32 windowId, u8 fontId, const u16 *str, u32 x, u32 y, u32 speed, u8 (*callback)(struct TextPrinterTemplate *, u16))
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

THUMB_FUNC u16 AddTextPrinterParameterized2(u32 windowId, u8 fontId, const u16 *str, u32 x, u32 y, u32 speed, u32 colors, u8 (*callback)(struct TextPrinterTemplate *, u16))
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

THUMB_FUNC u16 AddTextPrinterParameterized3(u32 windowId, u8 fontId, const u16 *str, u32 x, u32 y, u32 speed, u32 colors, u32 letterSpacing, u32 lineSpacing, u8 (*callback)(struct TextPrinterTemplate *, u16))
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
    printer->printerTemplate.currentChar = String_c_str((struct String *)printer->printerTemplate.currentChar); //TODO clean up
    printer->callback = callback;
    UNK_021C570C[0] = 0;
    FUN_0201C1A8(printer);
    if (speed != 0xff && speed != 0)
    {
        printer->textSpeedBottom += 0xff;
        printer->textSpeedTop = 1;
        printer->minLetterSpacing = FUN_0201BCC8(RunTextPrinter, printer, 1);
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

THUMB_FUNC void RunTextPrinter(u32 param0, struct TextPrinter *printer)
{
#pragma unused(param0)
    if (UNK_021C570C[0] == 0)
    {
        if (printer->Unk29 == 0)
        {
            printer->Unk2A = 0;
            GenerateFontHalfRowLookupTable(printer->printerTemplate.fgColor, printer->printerTemplate.bgColor, printer->printerTemplate.shadowColor);
            u32 temp = RenderFont(printer);
            switch (temp)
            {
                case 0:
                    CopyWindowToVram(printer->printerTemplate.windowId);
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

#ifdef NONMATCHING
THUMB_FUNC void GenerateFontHalfRowLookupTable(u8 fgColor, u8 bgColor, u8 shadowColor)
{
    u32 fg12, bg12, shadow12;
    u32 temp;

    u16 *current = UNK_021C570C;

    bg12 = bgColor << 12;
    fg12 = fgColor << 12;
    shadow12 = shadowColor << 12;

    temp = (bgColor << 8) | (bgColor << 4) | bgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (fgColor << 8) | (bgColor << 4) | bgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (shadowColor << 8) | (bgColor << 4) | bgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (bgColor << 8) | (fgColor << 4) | bgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (fgColor << 8) | (fgColor << 4) | bgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (shadowColor << 8) | (fgColor << 4) | bgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (bgColor << 8) | (shadowColor << 4) | bgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (fgColor << 8) | (shadowColor << 4) | bgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (shadowColor << 8) | (shadowColor << 4) | bgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (bgColor << 8) | (bgColor << 4) | fgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (fgColor << 8) | (bgColor << 4) | fgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (shadowColor << 8) | (bgColor << 4) | fgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (bgColor << 8) | (fgColor << 4) | fgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (fgColor << 8) | (fgColor << 4) | fgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (shadowColor << 8) | (fgColor << 4) | fgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (bgColor << 8) | (shadowColor << 4) | fgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (fgColor << 8) | (shadowColor << 4) | fgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (shadowColor << 8) | (shadowColor << 4) | fgColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (bgColor << 8) | (bgColor << 4) | shadowColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (fgColor << 8) | (bgColor << 4) | shadowColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (shadowColor << 8) | (bgColor << 4) | shadowColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (bgColor << 8) | (fgColor << 4) | shadowColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (fgColor << 8) | (fgColor << 4) | shadowColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (shadowColor << 8) | (fgColor << 4) | shadowColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (bgColor << 8) | (shadowColor << 4) | shadowColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (fgColor << 8) | (shadowColor << 4) | shadowColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;

    temp = (shadowColor << 8) | (shadowColor << 4) | shadowColor;
    *(current++) = (bg12) | temp;
    *(current++) = (fg12) | temp;
    *(current++) = (shadow12) | temp;
}
#else
THUMB_FUNC void GenerateFontHalfRowLookupTable(u8 fgColor, u8 bgColor, u8 shadowColor) //TODO use asm preprocessor
{
    asm {
    // push {r3-r7, lr}
    sub sp, #0x30
    ldr r3, =UNK_021C570C
    mov r5, #0x0
    str r5, [sp, #0x20]
    str r0, [sp, #0x24]
    str r2, [sp, #0x28]
    str r1, [sp, #0x2c]
    strh r1, [r3, #0x6]
    strh r0, [r3, #0x2]
    add r0, sp, #0x20
    strh r2, [r3, #0x4]
    str r5, [sp, #0x14]
    str r0, [sp, #0x8]
    mov r12, r0
    mov lr, r0
    str r0, [sp, #0x18]
    _0201C07E:
    mov r0, #0x0
    str r0, [sp, #0x10]
    ldr r0, [sp, #0x18]
    str r0, [sp, #0x4]
    ldr r0, [sp, #0x8]
    ldr r0, [r0, #0x0]
    str r0, [sp, #0x1c]
    _0201C08C:
    mov r0, #0x0
    str r0, [sp, #0xc]
    mov r0, lr
    str r0, [sp, #0x0]
    ldr r0, [sp, #0x4]
    ldr r0, [r0, #0x0]
    lsl r7, r0, #0x4
    _0201C09A:
    ldr r0, [sp, #0x0]
    mov r3, #0x0
    ldr r0, [r0, #0x0]
    mov r4, r12
    lsl r6, r0, #0x8
    _0201C0A4:
    ldr r0, [r4, #0x0]
    add r1, r7, #0x0
    lsl r0, r0, #0xc
    orr r0, r6
    orr r1, r0
    ldr r0, [sp, #0x1c]
    add r3, r3, #0x1
    add r2, r0, #0x0
    orr r2, r1
    lsl r1, r5, #0x1
    ldr r0, =UNK_021C5734
    add r5, r5, #0x1
    add r4, r4, #0x4
    strh r2, [r0, r1]
    cmp r3, #0x4
    blt _0201C0A4
    ldr r0, [sp, #0x0]
    add r0, r0, #0x4
    str r0, [sp, #0x0]
    ldr r0, [sp, #0xc]
    add r0, r0, #0x1
    str r0, [sp, #0xc]
    cmp r0, #0x4
    blt _0201C09A
    ldr r0, [sp, #0x4]
    add r0, r0, #0x4
    str r0, [sp, #0x4]
    ldr r0, [sp, #0x10]
    add r0, r0, #0x1
    str r0, [sp, #0x10]
    cmp r0, #0x4
    blt _0201C08C
    ldr r0, [sp, #0x8]
    add r0, r0, #0x4
    str r0, [sp, #0x8]
    ldr r0, [sp, #0x14]
    add r0, r0, #0x1
    str r0, [sp, #0x14]
    cmp r0, #0x4
    blt _0201C07E
    add sp, #0x30
    // pop {r3-r7, pc}
    }
}
#endif
