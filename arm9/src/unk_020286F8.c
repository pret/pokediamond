#include "global.h"
#include "save.h"
#include "MI_memory.h"
#include "string_util.h"
#include "math_util.h"
#include "string16.h"
#include "unk_020286F8.h"

struct UnkSaveStruct_020286F8 * UNK_021C59D0;

u32 FUN_020286F8(void)
{
    return 6 * sizeof(struct UnkSaveStruct_020286F8);
}

void FUN_02028700(struct UnkSaveStruct_020286F8 * ptr, int a, int b)
{
    ptr[b] = ptr[a];
}

void FUN_02028724(struct UnkSaveStruct_020286F8 * ptr)
{
    MI_CpuClearFast(ptr, 6 * sizeof(struct UnkSaveStruct_020286F8));
    for (int i = 0; i < 6; i++)
    {
        ptr[i].unk_0[0] = EOS;
        ptr[i].unk_10[0] = EOS;
    }
    UNK_021C59D0 = ptr;
}

void FUN_02028754(struct UnkSaveStruct_020286F8 * ptr, u32 n)
{
    u32 i, j;
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < n; j++)
        {
            ptr[i].unk_28 = PRandom(ptr[i].unk_28);
        }
    }
}

u32 FUN_0202877C(struct UnkSaveStruct_020286F8 * ptr, u32 i)
{
    return ptr[i].unk_24;
}

void FUN_02028788(struct UnkSaveStruct_020286F8 * ptr, u32 i, u32 j)
{
    ptr[i].unk_24 = j;
    ptr[i].unk_28 = PRandom(j);
}

u32 FUN_020287A4(struct UnkSaveStruct_020286F8 * ptr)
{
    return ptr[1].unk_28;
}

u16 * FUN_020287A8(struct UnkSaveStruct_020286F8 * ptr, u32 i, u32 j)
{
    if (j == 0)
        return ptr[i].unk_0;
    else
        return ptr[i].unk_10;
}

void FUN_020287C0(struct UnkSaveStruct_020286F8 * ptr, u32 i, u32 j, struct String * k)
{
    if (j == 0)
        CopyStringToU16Array(k, ptr[i].unk_0, 8);
    else
        CopyStringToU16Array(k, ptr[i].unk_10, 8);
}

void FUN_020287EC(struct UnkSaveStruct_020286F8 * ptr, u32 i, u32 j)
{
    ptr[i].unk_20 = (u8)j;
}

u8 FUN_020287F8(struct UnkSaveStruct_020286F8 * ptr, u32 i)
{
    return ptr[i].unk_20;
}

u8 FUN_02028804(struct UnkSaveStruct_020286F8 * ptr, u32 i)
{
    return ptr[i].unk_21;
}

void FUN_02028810(struct UnkSaveStruct_020286F8 * ptr, u32 i, u32 j)
{
    ptr[i].unk_21 = (u8)j;
}

struct UnkSaveStruct_020286F8 * FUN_0202881C(struct SaveData * save)
{
    return (struct UnkSaveStruct_020286F8 *)SaveArray_Get(save, 17);
}

BOOL FUN_0202888C(struct UnkSaveStruct_020286F8 * ptr);

BOOL FUN_02028828(struct UnkSaveStruct_020286F8 * ptr, u32 i)
{
    return !FUN_0202888C(&ptr[i]);
}

BOOL FUN_020288AC(struct UnkSaveStruct_020286F8 * ptr, struct UnkSaveStruct_020286F8 * ptr2);

BOOL FUN_02028840(struct UnkSaveStruct_020286F8 * ptr, int i)
{
    return FUN_020288AC(&ptr[1], &ptr[i]);
}

BOOL FUN_02028854(struct UnkSaveStruct_020286F8 * ptr, const u16 * str)
{
    if (str[0] == EOS)
        return FALSE;
    for (int i = 0; i < 6; i++)
    {
        if (!StringNotEqualN(str, ptr[i].unk_0, 8))
            return TRUE;
    }
    return FALSE;
}

BOOL FUN_0202888C(struct UnkSaveStruct_020286F8 * ptr)
{
    if (ptr->unk_0[0] == EOS)
        return TRUE;
    if (ptr->unk_10[0] == EOS)
        return TRUE;
    return FALSE;
}

BOOL FUN_020288AC(struct UnkSaveStruct_020286F8 * ptr, struct UnkSaveStruct_020286F8 * ptr2)
{
    if (StringNotEqualN(ptr->unk_10, ptr2->unk_10, 8))
        return FALSE;
    if (StringNotEqualN(ptr->unk_0, ptr2->unk_0, 8))
        return FALSE;
    if (ptr->unk_20 != ptr2->unk_20)
        return FALSE;
    if (ptr->unk_21 != ptr2->unk_21)
        return FALSE;
    return ptr->unk_24 == ptr2->unk_24;
}
