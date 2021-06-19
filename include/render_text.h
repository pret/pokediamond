#include "global.h"
#include "text.h"

typedef struct
{
    u8 canABSpeedUpPrint : 1;
    u8 useAlternateDownArrow : 1;
    u8 autoScroll : 1;
    u8 forceMidTextSpeed : 1;
    u8 unk0_4 : 1;
    u8 unk0_5 : 1;
    u8 unk0_6 : 1;
    u8 unk0_7 : 1;
    u8 unk1;
} TextFlags;

struct TextPrinterSubStruct
{
    u8 glyphId : 4; // 0x14
    u8 hasPrintBeenSpedUp : 1;
    u8 unk : 3;
    u8 downArrowDelay : 5;
    u8 downArrowYPosIdx : 2;
    u8 hasGlyphIdBeenSet : 1;
    u8 autoScrollDelay : 8;
};

u32 RenderText(struct TextPrinter *printer);
void FUN_02002840(u16 flag);
void TextPrinterInitDownArrowCounters(struct TextPrinter *printer);
void TextPrinterDrawDownArrow(struct TextPrinter *printer);
void TextPrinterClearDownArrow(struct TextPrinter *printer);
BOOL TextPrinterContinue(struct TextPrinter *printer);
BOOL TextPrinterWaitAutoMode(struct TextPrinter *printer);
BOOL TextPrinterWaitWithDownArrow(struct TextPrinter *printer);
u8 TextPrinterWait(struct TextPrinter *printer);
void TextFlags_SetCanABSpeedUpPrint(BOOL param0);
void FUN_02002B7C(s32 param0);
void FUN_02002BB8(u32 param0);
u8 FUN_02002BD4();
void FUN_02002BE4();
u8 FUN_02002BF4();
void FUN_02002C04();
