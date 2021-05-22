#ifndef POKEDIAMOND_TEXT_H
#define POKEDIAMOND_TEXT_H

#include "global.h"
#include "window.h"
#include "font.h"

struct TextPrinterTemplate
{
    const u16* currentChar; // 0
    struct Window * window; // 4
    u8 padding[1]; // 8
    u8 fontId; // 9
    u8 x; // a
    u8 y; // b
    u8 currentX; // c
    u8 currentY; // d
    u8 letterSpacing; // e
    u8 lineSpacing; // f
    u8 unk; // 10
    u8 fgColor; // 11
    u8 bgColor; // 12
    u8 shadowColor; // 13
    u16 unk2; // 14
    u8 unk3; // 16
    u8 unk4; // 17
};

struct Font
{
    u8 filler[20];
    void * unk20;
};

struct TextPrinter
{
    struct TextPrinterTemplate printerTemplate;

    u8 (*callback)(struct TextPrinterTemplate *, u16); // 0x18

    u8 subStructFields[7]; // always cast to struct TextPrinterSubStruct... so why bother
                           // 1c
    u8 active; // 23
    u8 state;       // 0x24
    u8 textSpeedBottom:7; // 25
    u8 textSpeedTop:1;
    u8 delayCounter; // 26
    u8 scrollDistance; // 27
    u8 minLetterSpacing;  // 0x28
    u8 Unk29; // used to be japanese, not sure about that anymore
    u16 Unk2A;
    u16 *Unk2C;
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
u16 AddTextPrinterParameterized(struct Window * window, u8 fontId, const u16 *str, u32 x, u32 y, u32 speed, u8 (*callback)(struct TextPrinterTemplate *, u16));
u16 AddTextPrinterParameterized2(struct Window * window, u8 fontId, const u16 *str, u32 x, u32 y, u32 speed, u32 colors, u8 (*callback)(struct TextPrinterTemplate *, u16));
u16 AddTextPrinterParameterized3(struct Window * window, u32 fontId, const u16 *str, u32 x, u32 y, u32 speed, u32 colors, u32 letterSpacing, u32 lineSpacing, u8 (*callback)(struct TextPrinterTemplate *, u16));
u16 AddTextPrinter(struct TextPrinterTemplate *printerTemplate, u32 speed, u8 (*callback)(struct TextPrinterTemplate *, u16));
void RunTextPrinter(u32 param0, struct TextPrinter *printer);
u32 RenderFont(struct TextPrinter *printer);
void GenerateFontHalfRowLookupTable(u8 fgColor, u8 bgColor, u8 shadowColor);
void DecompressGlyphTile(const u16 *src, u16 *dst);
void FUN_0201C1A8(struct TextPrinter *printer);
u16 *FUN_0201C1B0(void);
void FUN_0201C1EC(struct TextPrinter *printer, u32 param1, u32 param2, u32 param3);
void FUN_0201C238(struct TextPrinter *printer);

#endif //POKEDIAMOND_TEXT_H
