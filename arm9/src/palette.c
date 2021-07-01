#include "global.h"
#include "palette.h"
#include "MI_memory.h"
#include "gf_gfx_loader.h"
#include "unk_0200CA44.h"
#include "unk_020222E8.h"

extern int abs(int);

THUMB_FUNC struct PaletteData *FUN_02002FD0(u32 heap_id)
{
    struct PaletteData *ptr = AllocFromHeap(heap_id, sizeof(struct PaletteData));
    MI_CpuFill8(ptr, 0, sizeof(struct PaletteData));

    return ptr;
}

THUMB_FUNC void FUN_02002FEC(struct PaletteData *ptr)
{
    FreeToHeap(ptr);
}

THUMB_FUNC void PaletteData_SetBuffers(
    struct PaletteData *paletteData, u32 index, void *unfadedBuf, void *fadedBuf, u32 size)
{
    paletteData->pltt[index].unfadedBuf = unfadedBuf;
    paletteData->pltt[index].fadedBuf = fadedBuf;
    paletteData->pltt[index].bufSize = size;
}

THUMB_FUNC void PaletteData_AllocBuffers(
    struct PaletteData *paletteData, u32 index, u32 size, u32 heap_id)
{
    void *ptr = AllocFromHeap(heap_id, size);
    void *ptr2 = AllocFromHeap(heap_id, size);

    PaletteData_SetBuffers(paletteData, index, ptr, ptr2, size);
}

THUMB_FUNC void PaletteData_FreeBuffers(struct PaletteData *paletteData, u32 index)
{
    FreeToHeap(paletteData->pltt[index].unfadedBuf);
    FreeToHeap(paletteData->pltt[index].fadedBuf);
}

THUMB_FUNC void PaletteData_LoadPalette(
    struct PaletteData *paletteData, const void *src, u32 index, u32 offset, u16 size)
{
    MIi_CpuCopy16(src, paletteData->pltt[index].unfadedBuf + offset, size);
    MIi_CpuCopy16(src, paletteData->pltt[index].fadedBuf + offset, size);
}

THUMB_FUNC void PaletteData_LoadFromNarc(struct PaletteData *paletteData,
    NarcId narcId,
    s32 memberId,
    u32 heap_id,
    u32 index,
    u32 size,
    u16 offset,
    u16 param7)
{
    NNSG2dPaletteData *pltData;
    void *ptr = GfGfxLoader_GetPlttData(narcId, memberId, &pltData, heap_id);

    GF_ASSERT(ptr != NULL);

    if (size == 0)
    {
        size = pltData->szByte;
    }

    GF_ASSERT(size + offset * 2 <= paletteData->pltt[index].bufSize);

    PaletteData_LoadPalette(paletteData, pltData->pRawData + param7 * 2, index, offset, (u16)size);
    FreeToHeap(ptr);
}

THUMB_FUNC void PaletteData_LoadNarc(struct PaletteData *paletteData,
    NarcId narcId,
    s32 memberId,
    u32 heap_id,
    u32 index,
    u32 size,
    u16 offset)
{
    PaletteData_LoadFromNarc(paletteData, narcId, memberId, heap_id, index, size, offset, 0);
}

THUMB_FUNC void FUN_02003108(struct PaletteData *paletteData, u32 index, u16 offset, u32 size)
{
    GF_ASSERT(offset * 2 + size <= paletteData->pltt[index].bufSize);

    u16 *ptr;
    switch (index)
    {
        case 0:
            ptr = FUN_020222E8();
            break;
        case 1:
            ptr = FUN_020222F8();
            break;
        case 2:
            ptr = FUN_02022308();
            break;
        case 3:
            ptr = FUN_02022310();
            break;
        default:
            GF_ASSERT(FALSE);
            return;
    }

    PaletteData_LoadPalette(paletteData, ptr + offset, index, offset, (u16)size);
}

THUMB_FUNC void CopyPaletteFromNarc(
    NarcId narcId, s32 memberId, u32 heap_id, u32 size, u16 offset, void *dest)
{
    NNSG2dPaletteData *pltData;

    void *ptr = GfGfxLoader_GetPlttData(narcId, memberId, &pltData, heap_id);
    GF_ASSERT(ptr != NULL);

    if (size == 0)
    {
        size = pltData->szByte;
    }

    MI_CpuCopy16(pltData->pRawData + offset * 2, dest, size);

    FreeToHeap(ptr);
}

THUMB_FUNC void PaletteData_CopyPalette(struct PaletteData *paletteData,
    u32 srcIdx,
    u16 srcOffset,
    u32 destIdx,
    u16 destOffset,
    u16 size)
{

    MI_CpuCopy16(paletteData->pltt[srcIdx].unfadedBuf + srcOffset,
        paletteData->pltt[destIdx].unfadedBuf + destOffset,
        size);
    MI_CpuCopy16(paletteData->pltt[srcIdx].unfadedBuf + srcOffset,
        paletteData->pltt[destIdx].fadedBuf + destOffset,
        size);
}

THUMB_FUNC u16 *PaletteData_GetUnfadedBuf(struct PaletteData *paletteData, u32 index)
{
    return paletteData->pltt[index].unfadedBuf;
}

THUMB_FUNC u16 *PaletteData_GetFadedBuf(struct PaletteData *paletteData, u32 index)
{
    return paletteData->pltt[index].fadedBuf;
}

THUMB_FUNC u32 FUN_02003210(struct PaletteData *paletteData,
    u16 param1,
    u16 param2,
    s16 delay,
    u8 startY,
    u8 targetY,
    u16 color)
{

    u16 stc = param2;
    u32 r6 = 0;

    for (u8 i = 0; i < 14; i++)
    {
        if (IsPaletteSelected(param1, i) != 1)
        {
            continue;
        }

        if (IsPaletteSelected(paletteData->activeFadePalettes, i) != 0)
        {
            continue;
        }

        FUN_02003368(i, &paletteData->pltt[i], &param2);

        FUN_020033A4(&paletteData->pltt[i].fadeCtrl, param2, delay, startY, targetY, color);

        FUN_02003328(paletteData, i);

        if (i >= 4)
        {
            FUN_0200359C(paletteData, i, 0x100);
        }
        else
        {
            FUN_0200359C(paletteData, i, 0x10);
        }

        param2 = stc;
        r6 = 1;
    }

    if (r6 == 1)
    {
        paletteData->activeFadePalettes |= param1;
        if (paletteData->unk11a_e == 0)
        {
            paletteData->unk11a_e = 1;

            paletteData->unk118_0 = 1;
            paletteData->unk11c = 0;

            // wtf is that?
            FUN_0200CA44((void (*)(u32, struct TextPrinter *))FUN_02003464,
                (struct TextPrinter *)paletteData,
                (u32)(-2));
        }
    }

    return r6;
}

THUMB_FUNC u8 IsPaletteSelected(u16 selectedPalettes, u16 index)
{
    u32 r3 = 1;
    if ((selectedPalettes & (1 << index)) == 0)
    {
        r3 = 0;
    }

    return (u8)r3;
}

THUMB_FUNC void FUN_02003328(struct PaletteData *param0, u16 param1)
{
    if (IsPaletteSelected(param0->unk11a_0, param1) != 1)
    {
        param0->unk11a_0 |= 1 << param1;
    }
}

THUMB_FUNC void FUN_02003368(s32 param0, struct Palette *param1, u16 *param2)
{
    u8 r0;
    if (param0 < 4)
    {
        r0 = (u8)(param1->bufSize >> 5);
    }
    else
    {
        r0 = (u8)(param1->bufSize >> 9);
    }

    u16 r4 = 0;
    for (u8 i = 0; i < r0; i++)
    {
        r4 += 1 << i;
    }

    *param2 &= r4;
}

THUMB_FUNC void FUN_020033A4(struct PaletteFadeControl *paletteFade,
    u16 selectedPalettes,
    s16 delay,
    u8 startY,
    u8 targetY,
    u16 color)
{
    if (delay < 0)
    {
        paletteFade->deltaY = abs(delay) + 2;
        paletteFade->delay = 0;
    }
    else
    {
        paletteFade->deltaY = 2;
        paletteFade->delay = delay;
    }

    paletteFade->selectedPalettes = selectedPalettes;
    paletteFade->y = startY;
    paletteFade->targetY = targetY;
    paletteFade->blendColor = color;

    paletteFade->delayCounter = paletteFade->delay;

    if (startY < targetY)
    {
        paletteFade->yDec = 0;
        return;
    }
    paletteFade->yDec = 1;
}

THUMB_FUNC void FUN_02003464(u32 param0, struct PaletteData *param1)
{
    if (param1->unk11c == 1)
    {
        param1->unk11c = 0;
        param1->unk11a_0 = 0;
        param1->activeFadePalettes = 0;
        param1->unk11a_e = 0;
        FUN_0200CAB4((s32)param0);
        return;
    }

    if (param1->unk118_0 == 1)
    {
        param1->unk11a_0 = param1->activeFadePalettes;
        FUN_02003500(param1);
        FUN_02003520(param1);

        if (param1->activeFadePalettes == 0)
        {
            param1->unk11a_e = 0;
            FUN_0200CAB4((s32)param0);
        }
    }
}

THUMB_FUNC void FUN_02003500(struct PaletteData *param0)
{
    for (u8 i = 0; i < 4; i++)
    {
        FUN_02003540(param0, i, 0x10);
    }
}

THUMB_FUNC void FUN_02003520(struct PaletteData *param0)
{
    for (u8 i = 4; i < 14; i++)
    {
        FUN_02003540(param0, i, 0x100);
    }
}

THUMB_FUNC void FUN_02003540(struct PaletteData *paletteData, u8 index, u32 param2)
{
    if (IsPaletteSelected(paletteData->activeFadePalettes, index) != 0)
    {
        if (paletteData->pltt[index].fadeCtrl.delayCounter <
            paletteData->pltt[index].fadeCtrl.delay)
        {
            paletteData->pltt[index].fadeCtrl.delayCounter++;
            return;
        }

        paletteData->pltt[index].fadeCtrl.delayCounter = 0;
        FUN_0200359C(paletteData, index, param2);
    }
}

THUMB_FUNC void FUN_0200359C(struct PaletteData *paletteData, u32 index, u32 param2)
{

    for (u32 i = 0; i < 0x10; i++)
    {
        if (IsPaletteSelected(paletteData->pltt[index].fadeCtrl.selectedPalettes, (u16)i) != 0)
        {
            FUN_020035F8(paletteData->pltt[index].unfadedBuf + param2 * i,
                paletteData->pltt[index].fadedBuf + param2 * i,
                &paletteData->pltt[index].fadeCtrl,
                param2);
        }
    }

    FUN_02003684(paletteData, (u8)index, &paletteData->pltt[index].fadeCtrl);
}

THUMB_FUNC void FUN_020035F8(
    u16 *src, u16 *dest, struct PaletteFadeControl *fadeCtrl, u32 numEntries)
{
    for (u32 i = 0; i < numEntries; i++)
    {
        u8 lo = (u8)((src[i] & 0x1f) +
                     ((((fadeCtrl->blendColor & 0x1f) - (src[i] & 0x1f)) * fadeCtrl->y) >> 4));

        u8 hi = (u8)(((src[i] >> 10) & 0x1f) +
                     (((((fadeCtrl->blendColor >> 10) & 0x1f) - ((src[i] >> 10) & 0x1f)) *
                          fadeCtrl->y) >>
                         4));
        u8 mid =
            (u8)(((src[i] >> 5) & 0x1f) +
                 (((((fadeCtrl->blendColor >> 5) & 0x1f) - ((src[i] >> 5) & 0x1f)) * fadeCtrl->y) >>
                     4));

        dest[i] = (u16)((hi << 10) | (mid << 5) | lo);
    }
}

THUMB_FUNC void FUN_02003684(
    struct PaletteData *paletteData, u8 index, struct PaletteFadeControl *fadeCtrl)
{
    if (fadeCtrl->y == fadeCtrl->targetY)
    {
        if ((paletteData->activeFadePalettes & (1 << index)) == 0)
        {
            return;
        }

        paletteData->activeFadePalettes ^= (1 << index);

        return;
    }

    s16 val;
    if (fadeCtrl->yDec == 0)
    {
        val = (s16)fadeCtrl->y;
        val += fadeCtrl->deltaY;
        if (val > fadeCtrl->targetY)
        {
            val = (s16)fadeCtrl->targetY;
        }

        fadeCtrl->y = val;
        return;
    }

    val = (s16)fadeCtrl->y;
    val -= fadeCtrl->deltaY;
    if (val < fadeCtrl->targetY)
    {
        val = (s16)fadeCtrl->targetY;
    }

    fadeCtrl->y = val;
}

THUMB_FUNC void FUN_0200372C(struct PaletteData *paletteData)
{
    if (paletteData->unk11a_f == 0 && paletteData->unk118_0 != 1)
    {
        return;
    }

    for (s32 i = 0; i < 14; i++)
    {
        if (paletteData->unk11a_f != 0 ||
            (paletteData->pltt[i].fadedBuf != 0 &&
                IsPaletteSelected(paletteData->unk11a_0, (u16)i) != 0))
        {
            DC_FlushRange(paletteData->pltt[i].fadedBuf, paletteData->pltt[i].bufSize);

            switch (i)
            {
                case 0:
                    GX_LoadBGPltt(paletteData->pltt[i].fadedBuf, 0, paletteData->pltt[i].bufSize);
                    break;
                case 1:
                    GXS_LoadBGPltt(paletteData->pltt[i].fadedBuf, 0, paletteData->pltt[i].bufSize);
                    break;
                case 2:
                    GX_LoadOBJPltt(paletteData->pltt[i].fadedBuf, 0, paletteData->pltt[i].bufSize);
                    break;
                case 3:
                    GXS_LoadOBJPltt(paletteData->pltt[i].fadedBuf, 0, paletteData->pltt[i].bufSize);
                    break;
                case 4:
                    GX_BeginLoadBGExtPltt();
                    GX_LoadBGExtPltt(
                        paletteData->pltt[i].fadedBuf, 0, paletteData->pltt[i].bufSize);
                    GX_EndLoadBGExtPltt();
                    break;
                case 5:
                    GX_BeginLoadBGExtPltt();
                    GX_LoadBGExtPltt(
                        paletteData->pltt[i].fadedBuf, 0x2000, paletteData->pltt[i].bufSize);
                    GX_EndLoadBGExtPltt();
                    break;
                case 6:
                    GX_BeginLoadBGExtPltt();
                    GX_LoadBGExtPltt(
                        paletteData->pltt[i].fadedBuf, 0x4000, paletteData->pltt[i].bufSize);
                    GX_EndLoadBGExtPltt();
                    break;
                case 7:
                    GX_BeginLoadBGExtPltt();
                    GX_LoadBGExtPltt(
                        paletteData->pltt[i].fadedBuf, 0x6000, paletteData->pltt[i].bufSize);
                    GX_EndLoadBGExtPltt();
                    break;
                case 8:
                    GXS_BeginLoadBGExtPltt();
                    GXS_LoadBGExtPltt(
                        paletteData->pltt[i].fadedBuf, 0, paletteData->pltt[i].bufSize);
                    GXS_EndLoadBGExtPltt();
                    break;
                case 9:
                    GXS_BeginLoadBGExtPltt();
                    GXS_LoadBGExtPltt(
                        paletteData->pltt[i].fadedBuf, 0x2000, paletteData->pltt[i].bufSize);
                    GXS_EndLoadBGExtPltt();
                    break;
                case 10:
                    GXS_BeginLoadBGExtPltt();
                    GXS_LoadBGExtPltt(
                        paletteData->pltt[i].fadedBuf, 0x4000, paletteData->pltt[i].bufSize);
                    GXS_EndLoadBGExtPltt();
                    break;
                case 11:
                    GXS_BeginLoadBGExtPltt();
                    GXS_LoadBGExtPltt(
                        paletteData->pltt[i].fadedBuf, 0x6000, paletteData->pltt[i].bufSize);
                    GXS_EndLoadBGExtPltt();
                    break;
                case 12:
                    GX_BeginLoadOBJExtPltt();
                    GX_LoadOBJExtPltt(
                        paletteData->pltt[i].fadedBuf, 0, paletteData->pltt[i].bufSize);
                    GX_EndLoadOBJExtPltt();
                    break;
                case 13:
                    GXS_BeginLoadOBJExtPltt();
                    GXS_LoadOBJExtPltt(
                        paletteData->pltt[i].fadedBuf, 0, paletteData->pltt[i].bufSize);
                    GXS_EndLoadOBJExtPltt();
                    break;
            }
        }
    }

    paletteData->unk11a_0 = paletteData->activeFadePalettes;
    if (paletteData->unk11a_0 == 0)
    {
        paletteData->unk118_0 = 0;
    }
}

THUMB_FUNC u16 FUN_020038E4(struct PaletteData *paletteData)
{
    return paletteData->activeFadePalettes;
}

THUMB_FUNC void FUN_020038F0(struct PaletteData *paletteData, u32 param1)
{
    paletteData->unk11a_f = param1;
}

THUMB_FUNC void PaletteData_FillPalette(struct PaletteData *paletteData,
    u32 index,
    u32 selection,
    u16 value,
    u16 startOffset,
    u16 endOffset)
{
    GF_ASSERT(endOffset * 2 <= paletteData->pltt[index].bufSize);
    if (selection == 1 || selection == 2)
    {
        MI_CpuFill16(&paletteData->pltt[index].unfadedBuf[startOffset],
            value,
            (u32)((endOffset - startOffset) * 2));
    }

    if (selection == 0 || selection == 2)
    {
        MI_CpuFill16(&paletteData->pltt[index].fadedBuf[startOffset],
            value,
            (u32)((endOffset - startOffset) * 2));
    }
}

THUMB_FUNC void BlendPalette(u16 *src, u16 *dest, u16 numEntries, u8 coeff, u16 blendColor)
{
    s32 r2 = ((struct PlttData *)&blendColor)->r;
    s32 g2 = ((struct PlttData *)&blendColor)->g;
    s32 b2 = ((struct PlttData *)&blendColor)->b;
    for (u16 i = 0; i < numEntries; i++)
    {
        s32 r = ((struct PlttData *)&src[i])->r;
        s32 g = ((struct PlttData *)&src[i])->g;
        s32 b = ((struct PlttData *)&src[i])->b;

        dest[i] =
            (u16)(((r + (((r2 - r) * coeff) >> 4)) << 0) | ((g + (((g2 - g) * coeff) >> 4)) << 5) |
                  ((b + (((b2 - b) * coeff) >> 4)) << 10));
    }
}

THUMB_FUNC void BlendPaletteUnfaded(struct PaletteData *paletteData,
    u32 index,
    u16 offset,
    u16 numEntries,
    u8 coeff,
    u16 blendColor)
{
    BOOL r0 = FALSE;
    if (paletteData->pltt[index].unfadedBuf != 0 && paletteData->pltt[index].fadedBuf != 0)
    {
        r0 = TRUE;
    }

    GF_ASSERT(r0);

    BlendPalette(paletteData->pltt[index].unfadedBuf + offset,
        paletteData->pltt[index].fadedBuf + offset,
        numEntries,
        coeff,
        blendColor);
}

THUMB_FUNC void BlendPalettes(u16 *src, u16 *dest, u16 selectedPalettes, u8 coeff, u16 blendColor)
{
    while (selectedPalettes != 0)
    {
        if ((selectedPalettes & 1) != 0)
        {
            BlendPalette(src, dest, 0x10, coeff, blendColor);
        }

        selectedPalettes >>= 1;
        dest += 0x10;
        src += 0x10;
    }
}

THUMB_FUNC void BlendPalettesUnfaded(
    struct PaletteData *paletteData, u32 index, u16 selectedPalettes, u8 coeff, u16 blendColor)
{
    u32 r4 = 0;
    BOOL r0 = FALSE;
    if (paletteData->pltt[index].unfadedBuf != 0 && paletteData->pltt[index].fadedBuf != 0)
    {
        r0 = TRUE;
    }

    GF_ASSERT(r0);

    while (selectedPalettes != 0)
    {
        if ((selectedPalettes & 1) != 0)
        {
            BlendPaletteUnfaded(paletteData, index, (u16)r4, 0x10, coeff, blendColor);
        }

        selectedPalettes >>= 1;
        r4 += 0x10;
    }
}

THUMB_FUNC void TintPalette_CustomTone(u16 *palette, s32 count, s32 rTone, s32 gTone, s32 bTone)
{
    s32 r, g, b, i;
    u32 gray;

    for (i = 0; i < count; i++)
    {
        r = (*palette >> 0) & 0x1F;
        g = (*palette >> 5) & 0x1F;
        b = (*palette >> 10) & 0x1F;

        gray = (u32)((r * 76 + g * 151 + b * 29) >> 8);

        r = (u16)((rTone * gray)) >> 8;
        g = (u16)((gTone * gray)) >> 8;
        b = (u16)((bTone * gray)) >> 8;

        if (r > 31)
            r = 31;
        if (g > 31)
            g = 31;
        if (b > 31)
            b = 31;

        *palette++ = (u16)((b << 10) | (g << 5) | (r << 0));
    }
}

THUMB_FUNC void FUN_02003B40(struct PaletteData *paletteData,
    NarcId narcId,
    s32 memberId,
    u32 heap_id,
    u32 index,
    u32 size,
    u16 offset,
    s32 rTone,
    s32 gTone,
    s32 bTone)
{
    NNSG2dPaletteData *pltData;
    void *ptr = GfGfxLoader_GetPlttData(narcId, memberId, &pltData, heap_id);
    GF_ASSERT(ptr != NULL);

    if (size == 0)
    {
        size = pltData->szByte;
    }

    TintPalette_CustomTone(pltData->pRawData, 0x10, rTone, gTone, bTone);
    PaletteData_LoadPalette(paletteData, pltData->pRawData, index, offset, (u16)size);

    FreeToHeap(ptr);
}
