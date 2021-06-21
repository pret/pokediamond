#include "global.h"
#include "font.h"
#include "gf_gfx_loader.h"
#include "render_text.h"
#include "string16.h"
#include "text.h"
#include "graphic/font.naix"

struct UnkStruct_02002C14 *UNK_02106FC8;

struct UnkStruct_02002C14 UNK_02106FCC;

const u16 UNK_020ECB54[] = { 0, 0, 1, 0, 2, 0, 3, 0 };

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
        FUN_02021590(14, UNK_020ECB54[param0 * 2], 1, UNK_020ECB54[param0 * 2 + 1], param1);
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

#ifdef NONMATCHING
THUMB_FUNC void FUN_02002CF8(s32 param0)
{
    /*
    param0 is used as a index to a u32[]. The original assembly computes param0<<2 several times
    in the function where the present attempt computes it once and keep it r6.
    */

    GF_ASSERT(param0 < 4);

    if (UNK_02106FC8->unk84[param0] != NULL)
    {
        u32 i;
        for (i = 0; i < 4; i++)
        {
            if (i == param0)
            {
                continue;
            }

            if (UNK_020ECB54[i * 2] != UNK_020ECB54[param0 * 2])
            {
                continue;
            }

            if (UNK_02106FC8->unk84[i] == NULL)
            {
                continue;
            }

            UNK_02106FC8->unk84[i] = UNK_02106FC8->unk84[param0];
            break;
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
#else
asm void FUN_02002CF8(s32 param0)
{
    // clang-format off
	push {r3-r7, lr}
	add r4, r0, #0x0
	cmp r4, #0x4
	blt _02002D04
	bl GF_AssertFail
_02002D04:
	ldr r0, =UNK_02106FC8
	lsl r6, r4, #0x2
	ldr r7, [r0, #0x0]
	add r0, r7, r6
	add r0, #0x84
	ldr r0, [r0, #0x0]
	mov r12, r0
	cmp r0, #0x0
	beq _02002D68
	ldr r2, =UNK_020ECB54
	mov r1, #0x0
	ldrh r0, [r2, r6]
	add r3, r7, #0x0
_02002D1E:
	cmp r1, r4
	beq _02002D3E
	ldrh r5, [r2, #0x0]
	cmp r5, r0
	bne _02002D3E
	add r5, r3, #0x0
	add r5, #0x94
	ldr r5, [r5, #0x0]
	cmp r5, #0x0
	beq _02002D3E
	lsl r0, r1, #0x2
	add r2, r7, r0
	add r2, #0x84
	mov r0, r12
	str r0, [r2, #0x0]
	b _02002D48
_02002D3E:
	add r1, r1, #0x1
	add r2, r2, #0x4
	add r3, r3, #0x4
	cmp r1, #0x4
	blo _02002D1E
_02002D48:
	cmp r1, #0x4
	bne _02002D68
	ldr r0, =UNK_02106FC8
	lsl r5, r4, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	add r0, #0x84
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	ldr r0, =UNK_02106FC8
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	add r0, #0x84
	str r1, [r0, #0x0]
_02002D68:
	ldr r0, =UNK_02106FC8
	ldr r0, [r0, #0x0]
	add r0, r0, r6
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02002D88
	bl FUN_020215C8
	ldr r0, =UNK_02106FC8
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x2
	add r0, r1, r0
	add r0, #0x94
	str r2, [r0, #0x0]
_02002D88:
	pop {r3-r7, pc}
    // clang-format on
}
#endif

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
