#include "global.h"
#include "unk_02002F08.h"
#include "font.h"
#include "gf_gfx_loader.h"
#include "string16.h"
#include "unk_0201B8B8.h"

THUMB_FUNC int FUN_02002F08(u32 param0, struct String *str, u32 param2)
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

THUMB_FUNC int FUN_02002F9C(u32 param0, struct String *str)
{
    GF_ASSERT(UNK_02106FC8->unk94[param0] != NULL);

    return StringGetWidth_SingleLine_HandleClearToControlCode(
        UNK_02106FC8->unk94[param0], String_c_str(str));
}

THUMB_FUNC struct UnkStruct_02002F08 *FUN_02002FD0(u32 heap_id)
{
    struct UnkStruct_02002F08 *ptr = AllocFromHeap(heap_id, sizeof(struct UnkStruct_02002F08));
    MI_CpuFill8(ptr, 0, sizeof(struct UnkStruct_02002F08));

    return ptr;
}

THUMB_FUNC void FUN_02002FEC(struct UnkStruct_02002F08 *ptr)
{
    FreeToHeap(ptr);
}

THUMB_FUNC void FUN_02002FF4(
    struct UnkStruct_02002F08 *param0, u32 param1, void *param2, void *param3, u32 size)
{
    param0->unk000[param1].unk00 = param2;
    param0->unk000[param1].unk04 = param3;
    param0->unk000[param1].unk08 = size;
}

THUMB_FUNC void FUN_02003008(struct UnkStruct_02002F08 *param0, u32 param1, u32 size, u32 heap_id)
{
    void *ptr = AllocFromHeap(heap_id, size);
    void *ptr2 = AllocFromHeap(heap_id, size);

    FUN_02002FF4(param0, param1, ptr, ptr2, size);
}

THUMB_FUNC void FUN_02003038(struct UnkStruct_02002F08 *param0, u32 param1)
{
    FreeToHeap(param0->unk000[param1].unk00);
    FreeToHeap(param0->unk000[param1].unk04);
}

THUMB_FUNC void FUN_02003054(
    struct UnkStruct_02002F08 *param0, const void *param1, u32 param2, u32 offset, u16 size)
{
    MIi_CpuCopy16(param1, param0->unk000[param2].unk00 + offset, size);
    MIi_CpuCopy16(param1, param0->unk000[param2].unk04 + offset, size);
}

THUMB_FUNC void FUN_02003084(struct UnkStruct_02002F08 *param0,
    NarcId narcId,
    s32 memberId,
    u32 heap_id,
    u32 param4,
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

    GF_ASSERT(size + offset * 2 <= param0->unk000[param4].unk08);

    FUN_02003054(param0, pltData->pRawData + param7 * 2, param4, offset, (u16)size);
    FreeToHeap(ptr);
}

THUMB_FUNC void FUN_020030E8(struct UnkStruct_02002F08 *param0,
    NarcId narcId,
    s32 memberId,
    u32 heap_id,
    u32 param4,
    u32 size,
    u16 offset)
{
    FUN_02003084(param0, narcId, memberId, heap_id, param4, size, offset, 0);
}
