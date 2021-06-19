#include "global.h"
#include "game_init.h"
#include "string_util.h"
#include "text.h"
#include "unk_0201B8B8.h"

u16 unk00;

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

TextFlags gTextFlags;

const u8 UNK_020ECB50[] = { 0x00, 0x01, 0x02, 0x01 };

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

extern void FUN_0200284C(struct TextPrinter *printer);
extern const char *FUN_02002D94(u8, u16);
extern u8 FUN_02002B3C(struct TextPrinter *printer);
extern void FUN_02002A00(struct TextPrinter *printer);
extern u32 FUN_02002B18(struct TextPrinter *printer);

THUMB_FUNC u32 RenderText(struct TextPrinter *printer)
{

    struct TextPrinterSubStruct *subStruct =
        (struct TextPrinterSubStruct *)(&printer->subStructFields);
    u16 currentChar;
    u16 field;

    switch (printer->state)
    {
    case 0:
        if (((gMain.heldKeys & 3) != 0 && subStruct->hasPrintBeenSpedUp != 0) ||
            (gMain.touchHeld != 0 && gTextFlags.unk0_4 != 0))
        {
            printer->delayCounter = 0;
            if (printer->textSpeedBottom != 0)
            {
                gTextFlags.unk0_6 = 1;
            }
        }

        if (printer->delayCounter && printer->textSpeedBottom)
        {
            printer->delayCounter--;

            if (gTextFlags.canABSpeedUpPrint != 0)
            {
                if ((gMain.newKeys & 3) || (gMain.touchNew != 0 && gTextFlags.unk0_4))
                {
                    subStruct->hasPrintBeenSpedUp = 1;
                    printer->delayCounter = 0;
                }
            }

            return 3;
        }

        printer->delayCounter = printer->textSpeedBottom;
        currentChar = *printer->printerTemplate.currentChar.raw;
        printer->printerTemplate.currentChar.raw++;

        GF_ASSERT(currentChar != 0xF100);

        switch (currentChar)
        {
        case EOS:
            return 1;
        case 0xE000:
            printer->printerTemplate.currentX = printer->printerTemplate.x;
            s32 fontAttribute = GetFontAttribute(printer->printerTemplate.fontId, 1);

            printer->printerTemplate.currentY +=
                printer->printerTemplate.lineSpacing + fontAttribute;

            return 2;

        case 0xF0FD:
            printer->printerTemplate.currentChar.raw++;
            return 2;
        case 0xFFFE:
            printer->printerTemplate.currentChar.raw--;
            switch ((u16)MsgArray_GetControlCode(printer->printerTemplate.currentChar.raw))
            {
            case 0xFF00:
                u16 field =
                    MsgArray_ControlCodeGetField(printer->printerTemplate.currentChar.raw, 0);
                if (field == 0xff)
                {
                    u8 r2 = printer->printerTemplate.unk4;
                    printer->printerTemplate.unk4 =
                        (printer->printerTemplate.fgColor - 1) / 2 + 0x64;

                    if (!(r2 >= 0x64 && r2 < 0x6b))
                    {
                        break;
                    }

                    field = r2 - 0x64;
                }
                else
                {
                    if (field >= 0x64)
                    {
                        printer->printerTemplate.unk4 = field;
                        break;
                    }
                }

                printer->printerTemplate.fgColor = field * 2 + 1;
                printer->printerTemplate.shadowColor = field * 2 + 2;

                GenerateFontHalfRowLookupTable(printer->printerTemplate.fgColor,
                    printer->printerTemplate.bgColor,
                    printer->printerTemplate.shadowColor);

                break;

            case 0x200:
                field = MsgArray_ControlCodeGetField(printer->printerTemplate.currentChar.raw, 0);

                FUN_0201C1EC(printer,
                    printer->printerTemplate.currentX,
                    printer->printerTemplate.currentY,
                    field);
                if (printer->textSpeedTop != 0)
                {
                    CopyWindowToVram(printer->printerTemplate.window);
                }

                break;
            case 0x201:
                printer->delayCounter =
                    MsgArray_ControlCodeGetField(printer->printerTemplate.currentChar.raw, 0);
                printer->printerTemplate.currentChar.raw =
                    MsgArray_SkipControlCode(printer->printerTemplate.currentChar.raw);
                printer->state = 6;

                return 3;
            case 0x202:
                printer->Unk2A =
                    MsgArray_ControlCodeGetField(printer->printerTemplate.currentChar.raw, 0);
                printer->printerTemplate.currentChar.raw =
                    MsgArray_SkipControlCode(printer->printerTemplate.currentChar.raw);

                return 3;
            case 0x203:
                printer->printerTemplate.currentX =
                    MsgArray_ControlCodeGetField(printer->printerTemplate.currentChar.raw, 0);
                break;
            case 0x204:
                printer->printerTemplate.currentY =
                    MsgArray_ControlCodeGetField(printer->printerTemplate.currentChar.raw, 0);
                break;

            case 0xFF01:
                field = MsgArray_ControlCodeGetField(printer->printerTemplate.currentChar.raw, 0);

                switch (field)
                {
                case 100:
                    printer->printerTemplate.unk2 = 0;
                    printer->printerTemplate.unk3 = 0;
                    break;
                case 200:
                    printer->printerTemplate.unk2 = 0xFFFC;
                    printer->printerTemplate.unk3 = 0;
                    break;
                }

                break;

            case 0xFE06:
                field = MsgArray_ControlCodeGetField(printer->printerTemplate.currentChar.raw, 0);
                if (field != 0xFE00)
                {
                    if (field != 0xFE01)
                    {
                        break;
                    }

                    printer->state = 2;
                    FUN_0200284C(printer);
                    printer->printerTemplate.currentChar.raw =
                        MsgArray_SkipControlCode(printer->printerTemplate.currentChar.raw);

                    return 3;
                }

                printer->state = 3;
                FUN_0200284C(printer);
                printer->printerTemplate.currentChar.raw =
                    MsgArray_SkipControlCode(printer->printerTemplate.currentChar.raw);

                return 3;
            }

            printer->printerTemplate.currentChar.raw =
                MsgArray_SkipControlCode(printer->printerTemplate.currentChar.raw);
            return 2;

        case 0x25BC:
            printer->state = 2;
            FUN_0200284C(printer);
            return 3;

        case 0x25BD:
            printer->state = 3;
            FUN_0200284C(printer);
            return 3;
        }

        const char *r5 = FUN_02002D94(subStruct->glyphId, currentChar);
        CopyGlyphToWindow(printer->printerTemplate.window,
            r5,
            r5[0x80],
            r5[0x81],
            printer->printerTemplate.currentX,
            printer->printerTemplate.currentY,
            printer->printerTemplate.unk2);

        printer->printerTemplate.currentX += r5[0x80] + printer->printerTemplate.letterSpacing;

        return 0;
    case 1:
        if (FUN_02002B3C(printer) != 0)
        {
            FUN_02002A00(printer);

            printer->state = 0;
        }

        return 3;
    case 2:
        if (FUN_02002B18(printer) != 0)
        {
            FUN_02002A00(printer);
            FillWindowPixelBuffer(
                printer->printerTemplate.window, printer->printerTemplate.bgColor);
            printer->printerTemplate.currentX = printer->printerTemplate.x;
            printer->printerTemplate.currentY = printer->printerTemplate.y;
            printer->state = 0;
        }

        return 3;
    case 3:
        if (FUN_02002B18(printer) != 0)
        {
            FUN_02002A00(printer);
            printer->scrollDistance = GetFontAttribute(printer->printerTemplate.fontId, 1) +
                                      printer->printerTemplate.lineSpacing;
            printer->printerTemplate.currentX = printer->printerTemplate.x;
            printer->state = 4;
        }

        return 3;
    case 4:
        if (printer->scrollDistance != 0)
        {
            printer->printerTemplate.bgColor;
            if ((int)printer->scrollDistance < 4)
            {
                ScrollWindow(printer->printerTemplate.window,
                    0,
                    printer->scrollDistance,
                    (printer->printerTemplate.bgColor | (printer->printerTemplate.bgColor << 4)));
                printer->scrollDistance = 0;
            }
            else
            {
                ScrollWindow(printer->printerTemplate.window,
                    0,
                    4,
                    (printer->printerTemplate.bgColor | (printer->printerTemplate.bgColor << 4)));

                printer->scrollDistance -= 4;
            }

            CopyWindowToVram(printer->printerTemplate.window);
        }
        else
        {
            printer->state = 0;
        }

        return 3;
    case 5:
        printer->state = 0;
        return 3;
    case 6:
        if (printer->delayCounter != 0)
        {
            printer->delayCounter--;
        }
        else
        {
            printer->state = 0;
        }

        return 3;
    }

    return 1;
}

THUMB_FUNC void FUN_02002840(u16 flag)
{
    unk00 = flag;
}

THUMB_FUNC void FUN_0200284C(struct TextPrinter *printer)
{
    struct TextPrinterSubStruct *subStruct =
        (struct TextPrinterSubStruct *)(&printer->subStructFields);

    if (gTextFlags.autoScroll)
    {
        subStruct->autoScrollDelay = 0;
        return;
    }

    subStruct->downArrowYPosIdx = 0;
    subStruct->downArrowDelay = 0;
}

THUMB_FUNC void FUN_02002878(struct TextPrinter *printer)
{
    struct TextPrinterSubStruct *subStruct =
        (struct TextPrinterSubStruct *)(&printer->subStructFields);

    if (gTextFlags.autoScroll)
    {
        return;
    }

    if (subStruct->downArrowDelay != 0)
    {
        subStruct->downArrowDelay--;
        return;
    }

    u8 bg_id = GetWindowBgId(printer->printerTemplate.window);
    u8 x = GetWindowX(printer->printerTemplate.window);
    u8 y = GetWindowY(printer->printerTemplate.window);
    u8 width = GetWindowWidth(printer->printerTemplate.window);
    u16 r6 = unk00;

    FillBgTilemapRect(printer->printerTemplate.window->bgConfig,
        bg_id,
        r6 + 18 + UNK_020ECB50[subStruct->downArrowYPosIdx] * 4,
        x + width + 1,
        y + 2,
        1,
        1,
        0x10);

    FillBgTilemapRect(printer->printerTemplate.window->bgConfig,
        bg_id,
        r6 + 19 + UNK_020ECB50[subStruct->downArrowYPosIdx] * 4,
        x + width + 2,
        y + 2,
        1,
        1,
        0x10);
    FillBgTilemapRect(printer->printerTemplate.window->bgConfig,
        bg_id,
        r6 + 20 + UNK_020ECB50[subStruct->downArrowYPosIdx] * 4,
        x + width + 1,
        y + 3,
        1,
        1,
        0x10);
    FillBgTilemapRect(printer->printerTemplate.window->bgConfig,
        bg_id,
        r6 + 21 + UNK_020ECB50[subStruct->downArrowYPosIdx] * 4,
        x + width + 2,
        y + 3,
        1,
        1,
        0x10);

    BgCommitTilemapBufferToVram(printer->printerTemplate.window->bgConfig, bg_id);
    subStruct->downArrowDelay = 8;
    subStruct->downArrowYPosIdx++;
}

THUMB_FUNC void FUN_02002A00(struct TextPrinter *printer)
{
    u8 bg_id = GetWindowBgId(printer->printerTemplate.window);
    u8 x = GetWindowX(printer->printerTemplate.window);
    u8 y = GetWindowY(printer->printerTemplate.window);
    u8 width = GetWindowWidth(printer->printerTemplate.window);
    u16 r6 = unk00;

    FillBgTilemapRect(printer->printerTemplate.window->bgConfig,
        bg_id,
        r6 + 10,
        x + width + 1,
        y + 2,
        1,
        2,
        0x10);
    FillBgTilemapRect(printer->printerTemplate.window->bgConfig,
        bg_id,
        r6 + 11,
        x + width + 2,
        y + 2,
        1,
        2,
        0x10);
    BgCommitTilemapBufferToVram(printer->printerTemplate.window->bgConfig, bg_id);
}

extern void FUN_020054C8(u16);

THUMB_FUNC u32 FUN_02002A94(struct TextPrinter *printer)
{
    if ((gMain.newKeys & 3) != 0 || (gMain.touchNew != 0 && gTextFlags.unk0_4 != 0))
    {
        FUN_020054C8(0x5DC);

        gTextFlags.unk0_7 = 1;

        return 1;
    }

    return 0;
}

THUMB_FUNC u32 FUN_02002ADC(struct TextPrinter *printer)
{
    struct TextPrinterSubStruct *subStruct =
        (struct TextPrinterSubStruct *)(&printer->subStructFields);

    if (subStruct->autoScrollDelay == 100)
    {
        return 1;
    }

    subStruct->autoScrollDelay++;
    if (gTextFlags.unk0_5)
    {
        return FUN_02002A94(printer);
    }

    return 0;
}

THUMB_FUNC u32 FUN_02002B18(struct TextPrinter *printer)
{
    if (gTextFlags.autoScroll)
    {
        return FUN_02002ADC(printer);
    }
    FUN_02002878(printer);

    return FUN_02002A94(printer);
}

THUMB_FUNC u8 FUN_02002B3C(struct TextPrinter *printer)
{
    if (gTextFlags.autoScroll)
    {
        return FUN_02002ADC(printer);
    }

    return FUN_02002A94(printer);
}

THUMB_FUNC void FUN_02002B60(u32 param0)
{
    gTextFlags.canABSpeedUpPrint = param0;
}

THUMB_FUNC void FUN_02002B7C(s32 param0)
{
    gTextFlags.autoScroll = param0 & 1;
    gTextFlags.unk0_5 = (param0 >> 1) & 1;
}

THUMB_FUNC void FUN_02002BB8(u32 param0)
{
    gTextFlags.unk0_4 = param0;
}

THUMB_FUNC u8 FUN_02002BD4()
{
    return gTextFlags.unk0_6;
}

THUMB_FUNC void FUN_02002BE4()
{
    gTextFlags.unk0_6 = 0;
}

THUMB_FUNC u8 FUN_02002BF4()
{
    return gTextFlags.unk0_7;
}

THUMB_FUNC void FUN_02002C04()
{
    gTextFlags.unk0_7 = 0;
}
