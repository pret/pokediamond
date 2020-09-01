#include "global.h"
#include "msgdata.h"
#include "heap.h"
#include "save_block_2.h"
#include "math_util.h"
#include "unk_020139D8.h"

#pragma thumb on

const u8 UNK_020ED5B4[][2] = {
    { LANGUAGE_JAPANESE, 0 },
    { LANGUAGE_ENGLISH,  1 },
    { LANGUAGE_FRENCH,   2 },
    { LANGUAGE_ITALIAN,  3 },
    { LANGUAGE_GERMAN,   4 },
    { LANGUAGE_SPANISH,  5 },
};

const u16 UNK_020ED5C0[] = {
    362,
    589,
    565,
    553,
    388,
    389,
    390,
    391,
    392,
    393,
    394
};

const u16 UNK_020ED5D6[] = {
    496,
    468,
    18,
    124,
    38,
    38,
    107,
    104,
    47,
    32,
    23
};

const u16 UNK_020ED580[] = { 0x04C0, 0x04F0 };
const u16 UNK_020ED5A8[] = { 0x04A7, 0x04E1 };
const u16 UNK_020ED5AC[] = { 0x0479, 0x0498, 0x049B, 0x049C };
const u16 UNK_020ED5A0[] = { 0x048F, 0x0497 };
const u16 UNK_020ED59C[] = { 0x04FC, 0x0596 };
const u16 UNK_020ED594[] = { 0x047A, 0x048D };
const u16 UNK_020ED58C[] = { 0x0441, 0x0599 };
const u16 UNK_020ED590[] = { 0x042C, 0x059D };
const u16 UNK_020ED5A4[] = { 0x04B0, 0x04FF };
const u16 UNK_020ED598[] = { 0x04B6, 0x0505 };
const u16 UNK_020ED584[] = { 0x024E, 0x03D2 };
const u16 UNK_020ED588[] = { 0x04BB, 0x0500 };

const struct UnkStruct_020ED5EC
{
    const u16 * data;
    s32 count;
} UNK_020ED5EC[] = {
    { UNK_020ED58C, NELEMS(UNK_020ED58C) },
    { UNK_020ED580, NELEMS(UNK_020ED580) },
    { UNK_020ED5A8, NELEMS(UNK_020ED5A8) },
    { UNK_020ED5AC, NELEMS(UNK_020ED5AC) },
    { UNK_020ED5A0, NELEMS(UNK_020ED5A0) },
    { UNK_020ED59C, NELEMS(UNK_020ED59C) },
    { UNK_020ED588, NELEMS(UNK_020ED588) },
    { UNK_020ED584, NELEMS(UNK_020ED584) },
    { UNK_020ED590, NELEMS(UNK_020ED590) },
    { UNK_020ED5A4, NELEMS(UNK_020ED5A4) },
    { UNK_020ED598, NELEMS(UNK_020ED598) },
    { UNK_020ED594, NELEMS(UNK_020ED594) },
};

struct UnkStruct_020139D8 * FUN_020139D8(u32 heap_id)
{
    struct UnkStruct_020139D8 * ret = (struct UnkStruct_020139D8 *)AllocFromHeap(heap_id, sizeof(struct UnkStruct_020139D8));
    s32 i;
    for (i = 0; i < 11; i++)
    {
        ret->heap_id = heap_id; // inadvertently inside the loop
        ret->msgDatas[i] = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, UNK_020ED5C0[i], heap_id);
    }
    return ret;
}

void FUN_02013A10(struct UnkStruct_020139D8 * unk)
{
    s32 i;
    for (i = 0; i < 11; i++)
    {
        DestroyMsgData(unk->msgDatas[i]);
    }
    FreeToHeap(unk);
}

void FUN_02013A30(struct UnkStruct_020139D8 * unk, u16 a1, struct String * str)
{
    s32 sp4;
    s32 sp0;
    FUN_02013AEC(a1, &sp4, &sp0);
    ReadMsgDataIntoString(unk->msgDatas[sp4], (u32)sp0, str);
}

void FUN_02013A58(u16 a0, struct String * a1)
{
    s32 sp8;
    s32 sp4;
    if (a0 != 0xFFFF)
    {
        FUN_02013AEC(a0, &sp8, &sp4);
        sp8 = UNK_020ED5C0[sp8];
        ReadMsgData_NewNarc_ExistingString(NARC_MSGDATA_MSG, (u32)sp8, (u32)sp4, 0, a1);
    }
    else
        StringSetEmpty(a1);
}

u16 FUN_02013A9C(u16 a0, u16 a1)
{
    u32 i;
    u16 k;
    u16 j;
    for (i = 0; i < 11; i++)
    {
        if (a0 == UNK_020ED5C0[i])
        {
            for (j = 0, k = 0; j < i; j++)
                k += UNK_020ED5D6[j];
            return (u16)(k + a1);
        }
    }
    return 0xFFFF;
}

void FUN_02013AEC(u32 a0, s32 * a1, s32 * a2)
{
    s32 i;
    s32 j;
    u32 r3;

    r3 = a0 & 0xFFF;
    j = 0;

    for (i = 0; i < NELEMS(UNK_020ED5D6); i++)
    {
        j += UNK_020ED5D6[i];
        if (r3 < j)
        {
            *a1 = i;
            *a2 = (s32)(r3 - (j - UNK_020ED5D6[i]));
            return;
        }
    }
}

u32 FUN_02013B28(void)
{
    return sizeof(struct UnkStruct_02013B28);
}

void FUN_02013B2C(struct UnkStruct_02013B28 * unk)
{
    u32 i;
    unk->unk_0 = 0;
    unk->unk_4 = 0;
    for (i = 0; i < 6; i++)
    {
        if (UNK_020ED5B4[i][0] == GAME_LANGUAGE)
        {
            FUN_02013C18(unk, UNK_020ED5B4[i][1]);
            break;
        }
    }
}

struct UnkStruct_02013B28 * FUN_02013B5C(struct SaveBlock2 * sav2)
{
    return (struct UnkStruct_02013B28 *)SavArray_get(sav2, 34);
}

BOOL FUN_02013B68(struct UnkStruct_02013B28 * unk, u32 a1)
{
    return (BOOL)((unk->unk_4 >> a1) & 1);
}

s32 FUN_02013B74(struct UnkStruct_02013B28 * unk)
{
    u32 i;
    u32 count;
    u32 which_bit;
    for (i = 0, count = 0; i < 32; i++)
    {
        if (!((unk->unk_4 >> i) & 1))
            count++;
    }
    if (count != 0)
    {
        which_bit = LCRandom() % count;
        for (i = 0; i < 32; i++)
        {
            if (!((unk->unk_4 >> i) & 1))
            {
                if (which_bit == 0)
                {
                    unk->unk_4 |= (1 << i);
                    return (s32)i;
                }
                which_bit--;
            }
        }
    }
    return 32;
}

BOOL FUN_02013BC8(struct UnkStruct_02013B28 * unk)
{
    u32 i;
    for (i = 0; i < 32; i++)
    {
        if (!((unk->unk_4 >> i) & 1))
            return FALSE;
    }
    return TRUE;
}

u16 FUN_02013BE4(u16 a0)
{
    s32 i;
    u16 skip = 0;
    for (i = 0; i < 9; i++)
        skip += UNK_020ED5D6[i];
    return (u16)(skip + a0);
}

BOOL FUN_02013C0C(struct UnkStruct_02013B28 * unk, u32 a1)
{
    return (BOOL)((unk->unk_0 >> a1) & 1);
}

void FUN_02013C18(struct UnkStruct_02013B28 * unk, u32 a1)
{
    unk->unk_0 |= (1 << a1);
}

s32 FUN_02013C28(u16 a0)
{
    s32 r3;
    s32 r4;

    for (r3 = 0; r3 < NELEMS(UNK_020ED5EC); r3++)
    {
        for (r4 = 0; r4 < UNK_020ED5EC[r3].count; r4++)
        {
            if (a0 == UNK_020ED5EC[r3].data[r4])
                return UNK_020ED5EC[r3].count - 1;
        }
    }
    return 0;
}

u16 FUN_02013C6C(u16 a0, s32 a1)
{
    s32 r7;
    s32 r2;
    s32 r0;

    for (r7 = 0; r7 < NELEMS(UNK_020ED5EC); r7++)
    {
        for (r2 = 0; r2 < UNK_020ED5EC[r7].count; r2++)
        {
            if (a0 == UNK_020ED5EC[r7].data[r2])
            {
                // ERROR: Infinite loop when reached
                for (r0 = 0; /*r0 <*/ UNK_020ED5EC[r7].count; r0++)
                {
                    if (a1 == 0)
                        return UNK_020ED5EC[r7].data[r0];
                    a1--;
                }
                GF_ASSERT(0);
                return 0xFFFF;
            }
        }
    }
    return a0;
}
