#include "global.h"
#include "string_util.h"
#include "save_block_2.h"
#include "heap.h"
#include "unk_020254B8.h"

u32 FUN_020254B8(void)
{
    return 16 * sizeof(struct UnkStruct_020254B8);
}

struct UnkStruct_020254B8 * FUN_020254C0(struct SaveBlock2 * sav2)
{
    return (struct UnkStruct_020254B8 *)SaveArray_Get(sav2, 9);
}

void FUN_020254CC(struct UnkStruct_020254B8 * arr)
{
    s32 i;

    for (i = 0; i < 16; i++)
    {
        memset(&arr[i], 0, sizeof(struct UnkStruct_020254B8));
        arr[i].field_00[0] = EOS;
    }
}

u16 * FUN_020254F0(struct UnkStruct_020254B8 * arr, s32 i)
{
    return arr[i].field_00;
}

u8 FUN_020254F8(struct UnkStruct_020254B8 * unk, s32 i)
{
    return unk->field_68[i];
}

BOOL FUN_02025500(struct UnkStruct_020254B8 * a, struct UnkStruct_020254B8 * b)
{
    return !StringNotEqual(a->field_00, b->field_00) && a->field_10 == b->field_10;
}

void FUN_02025520(struct UnkStruct_020254B8 * sp0, struct UnkStruct_020254B8 * sp4, s32 n, u32 heap_id)
{
    s32 sp18[5];
    s32 sp14;
    struct UnkStruct_020254B8 * sp10;
    s32 r12;
    s32 spC;
    s32 r4;
    s32 r4_2;

    // auto buffer = new UnkStruct_020254B8[16]
    sp10 = AllocFromHeap(heap_id, 16 * sizeof(struct UnkStruct_020254B8));
    FUN_020254CC(sp10);

    // Look up each element of sp4 in sp0
    for (sp14 = 0; sp14 < n; sp14++)
    {
        sp18[sp14] = -1;
        for (r4_2 = 0; r4_2 < 16; r4_2++)
        {
            if (FUN_02025500(&sp0[r4_2], &sp4[sp14]))
                sp18[sp14] = r4_2;
        }
    }

    // Copy sp4 to buffer and mask matching entries in sp0
    r4 = 0;
    for (spC = 0; spC < n; spC++)
    {
        sp10[r4] = sp4[spC];
        if (sp18[spC] >= 0)
            sp0[sp18[spC]].field_00[0] = EOS;
        r4++;
    }

    // Copy unmasked entries from sp0 to buffer
    for (r12 = 0; r12 < 16; r12++)
    {
        if (sp0[r12].field_00[0] != EOS)
        {
            sp10[r4] = sp0[r12];
            r4++;
            if (r4 >= 16)
                break;
        }
    }
    // Copy buffer to sp0 and destroy buffer
    memcpy(sp0, sp10, 16 * sizeof(struct UnkStruct_020254B8));
    FreeToHeap(sp10);
}

s32 FUN_02025614(struct UnkStruct_020254B8 * a0, u32 a1)
{
    s32 i, j;

    for (i = 0; i < 16; i++)
    {
        if (a1 == a0[i].field_10)
            return 1;
    }
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
        {
            if (a1 == a0[i].field_18[j])
                return i + 2;
        }
    }
    return 0;
}
