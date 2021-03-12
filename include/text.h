#ifndef POKEDIAMOND_TEXT_H
#define POKEDIAMOND_TEXT_H

#include "global.h"

struct TextPrinterTemplate
{
    const u16* currentChar;
    u32 windowId;
    u8 padding[1];
    u8 fontId;
    u8 x;
    u8 y;
    u8 currentX;
    u8 currentY;
    u8 letterSpacing;
    u8 lineSpacing;
    u8 unk;
    u8 fgColor;
    u8 bgColor;
    u8 shadowColor;
    u16 unk2;
    u8 unk3;
    u8 unk4;
};

struct TextPrinter
{
    struct TextPrinterTemplate printerTemplate;

    u8 (*callback)(struct TextPrinterTemplate *, u16); // 0x10

    u8 subStructFields[7]; // always cast to struct TextPrinterSubStruct... so why bother
    u8 active;
    u8 state;       // 0x1C
    u8 textSpeedBottom:7;
    u8 textSpeedTop:1;
    u8 delayCounter;
    u8 scrollDistance;
    u8 minLetterSpacing;  // 0x20
    u8 Unk29; // used to be japanese, not sure about that anymore
    u16 Unk2A;
    u8 padding[4];
};

struct FontInfo
{
    u8 maxLetterWidth;
    u8 maxLetterHeight;
    u8 letterSpacing;
    u8 lineSpacing;
    u8 unk;
    u8 fgColor;
    u8 bgColor;
    u8 shadowColor;
};

void SetFontsPointer(const struct FontInfo *fonts);
u8 FUN_0201BCC8(void (*func)(u32, struct TextPrinter *), struct TextPrinter *printer, u32 param2);
void FUN_0201BCFC(u32 param0);
BOOL FUN_0201BD44(u32 param0);
void FUN_0201BD5C(void);
u8 FUN_0201BD70(u32 param0);
void FUN_0201BD7C(u32 param0);
u16 AddTextPrinterParameterized(u32 windowId, u8 fontId, const u16 *str, u32 x, u32 y, u32 speed, u8 (*callback)(struct TextPrinterTemplate *, u16));
u16 AddTextPrinterParameterized2(u32 windowId, u8 fontId, const u16 *str, u32 x, u32 y, u32 speed, u32 colors, u8 (*callback)(struct TextPrinterTemplate *, u16));
u16 AddTextPrinterParameterized3(u32 windowId, u8 fontId, const u16 *str, u32 x, u32 y, u32 speed, u32 colors, u32 letterSpacing, u32 lineSpacing, u8 (*callback)(struct TextPrinterTemplate *, u16));
u16 AddTextPrinter(struct TextPrinterTemplate *printerTemplate, u32 speed, u8 (*callback)(struct TextPrinterTemplate *, u16));
void RunTextPrinter(u32 param0, struct TextPrinter *printer);
u32 RenderFont(struct TextPrinter *printer);
void GenerateFontHalfRowLookupTable(u8 fgColor, u8 bgColor, u8 shadowColor);

#endif //POKEDIAMOND_TEXT_H
