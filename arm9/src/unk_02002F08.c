#include "global.h"
#include "unk_02002F08.h"
#include "font.h"
#include "gf_gfx_loader.h"
#include "string16.h"
#include "unk_0201B8B8.h"

THUMB_FUNC s32 FUN_02002F08(u32 param0, struct String *str, u32 param2)
{
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    return StringGetWidth(UNK_02106FC8->unk94[param0], String_c_str(str), param2);
}

THUMB_FUNC u32 FUN_02002F40(u32 param0, struct String *str, u32 param2, u32 param3)
{
    u32 r0 = FUN_02002E14(param0, str, param2);
    if (r0 < param3)
    {
        return (param3 - r0) / 2;
    }

    return 0;
}

THUMB_FUNC u32 FUN_02002F58(const u16 *str)
{
    u32 r5 = 1;
    while (*str != EOS)
    {
        if (*str == 0xFFFE)
        {
            str = MsgArray_SkipControlCode(str);
            continue;
        }

        if (*str == 0xE000)
        {
            r5++;
            str++;
            continue;
        }

        str++;
    }

    return r5;
}

THUMB_FUNC u32 FUN_02002F90(struct String *str)
{
    return FUN_02002F58(String_c_str(str));
}

THUMB_FUNC s32 FUN_02002F9C(u32 param0, struct String *str)
{
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    return StringGetWidth_SingleLine_HandleClearToControlCode(
        UNK_02106FC8->unk94[param0], String_c_str(str));
}

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

THUMB_FUNC void PaletteData_AllocBuffers(struct PaletteData *paletteData, u32 index, u32 size, u32 heap_id)
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
