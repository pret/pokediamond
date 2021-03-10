#ifndef POKEDIAMOND_TEXT_H
#define POKEDIAMOND_TEXT_H

#include "global.h"

struct TextPrinterTemplate
{
    const u8* currentChar;
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

    void (*callback)(struct TextPrinterTemplate *, u16); // 0x10

    u8 subStructFields[7]; // always cast to struct TextPrinterSubStruct... so why bother
    u8 active;
    u8 state;       // 0x1C
    u8 textSpeed;
    u8 delayCounter;
    u8 scrollDistance;
    u8 minLetterSpacing;  // 0x20
    u8 japanese;
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
u8 FUN_0201BCC8(void *param0, u32 param1, u32 param2);
void FUN_0201BCFC(u32 param0);
BOOL FUN_0201BD44(u32 param0);
void FUN_0201BD5C(void);
u8 FUN_0201BD70(u32 param0);
void FUN_0201BCFC(u32 param0);
u16 AddTextPrinterParameterized(u32 windowId, u8 fontId, const u8 *str, u32 x, u32 y, u32 speed, void (*callback)(void *, u16));

#endif //POKEDIAMOND_TEXT_H
