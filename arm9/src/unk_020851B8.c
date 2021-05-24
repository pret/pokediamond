#include "global.h"
#include "heap.h"
#include "unk_020851B8.h"

THUMB_FUNC struct UnkStruct_020851B8 *FUN_020851B8(u32 heap_id)
{
    struct UnkStruct_020851B8 *ret = (struct UnkStruct_020851B8 *) AllocFromHeap(heap_id, sizeof(struct UnkStruct_020851B8));
    ret->unk00[0x0] = 0;
    ret->unk00[0x1] = 0;
    ret->unk00[0x2] = 0;
    ret->unk00[0x3] = 0;
    ret->unk00[0x4] = 0;
    ret->unk00[0x5] = 0;
    ret->unk00[0x6] = 0;
    ret->unk00[0x7] = 0;
    ret->unk00[0x8] = 0;
    ret->unk00[0x9] = 0;
    ret->unk00[0xA] = 0;
    ret->unk00[0xB] = 0;

    return ret;
}

THUMB_FUNC void FUN_020851DC(struct UnkStruct_020851B8 *param0, u32 param1, BOOL param2)
{
    u16 flag = param1 - 0x95;
    FUN_02085200((u32*) param0, flag);

    if (param2 == TRUE)
    {
        param0->unk00[0x8] = flag;
    }
}

THUMB_FUNC void FUN_020851F8(struct UnkStruct_020851B8 *param0, u8 param1, u8 param2, u8 param3)
{
    param0->unk00[0x9] = param1;
    param0->unk00[0xA] = param2;
    param0->unk00[0xB] = param3;
}

THUMB_FUNC void FUN_02085200(u32 *param0, u16 param1)
{
    u32 index = param1 / 32;
    u32 tag = 1 << (param1 % 32);
    u32 value = *(param0 + index);
    *(param0 + index) = value | tag;
}

THUMB_FUNC u32 FUN_02085224(u32 *param0, u16 param1) {
    u32 r2 = 1;
    u32 index = param1 / 32;
    u32 tag = 1 << (param1 % 32);

    if (*(param0 + index) & tag)
    {
        r2 = 0;
    }

    return (r2 << 0x18) >> 0x18;
}

THUMB_FUNC void FUN_0208524C(struct UnkStruct_020851B8 *param0, u8 *param1, u8 *param2)
{
    *param1 = param0->unk00[0x9];
    *param2 = param0->unk00[0xA];
}
