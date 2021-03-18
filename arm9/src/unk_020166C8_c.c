#include "global.h"

struct UnkStruct_020166C8
{
    u32 *unk_ptr1;
    void *unk_ptr2;
    void *unk_ptr3;
    u16 *unk_ptr4;
    u8 *unk_ptr5;
    u16 unk_half1;
    u16 unk_half2;
    u16 unk_half3;
    u16 unk_half4;
};

struct UnkStruct_020166C8 UNK_021C4D28;

extern void *tempName_NNS_FndCreateExpHeapEx(void *param0, u32 param1, u32 param2);
extern u32 FUN_02016834(u32 param0, u32 param1, u32 param2, u32 param3);

THUMB_FUNC void FUN_020166C8(u32 *param0, u32 param1, u32 param2, u32 pre_size)
{
    u32 unk_size = param1 + 24;

    if (param2 < unk_size)
    {
        param2 = unk_size;
    }
    if (pre_size != 0)
    {
        while (pre_size % 4 != 0)
        {
            pre_size++;
        }

        OS_AllocFromArenaLo(0, pre_size, 4);
    }

    u32 r7 = param2 * 2;

    void *ptr = OS_AllocFromArenaLo(0, (unk_size * 3 + 1) * sizeof(u32) + r7 + param2, 4);
    UNK_021C4D28.unk_ptr1 = ptr;
    ptr += (unk_size + 1) * 4;
    UNK_021C4D28.unk_ptr2 = ptr;
    ptr += unk_size * 4;
    UNK_021C4D28.unk_ptr3 = ptr;
    ptr += unk_size * 4;
    UNK_021C4D28.unk_ptr4 = ptr;
    ptr += r7;
    UNK_021C4D28.unk_ptr5 = ptr;
    UNK_021C4D28.unk_half1 = param2;
    UNK_021C4D28.unk_half2 = param1;

    r7 = 0;
    UNK_021C4D28.unk_half4 = (u16)unk_size;
    UNK_021C4D28.unk_half3 = (u16)unk_size;

    while (r7 < param1)
    {
        void *ptr;
        if (param0[1] == 0 || param0[1] != 2)
        {
            ptr = OS_AllocFromArenaLo(0, param0[0], 4);
        }
        else
        {
            ptr = OS_AllocFromArenaHi(2, param0[0], 4);
        }

        if (ptr != 0)
        {
            void *res = tempName_NNS_FndCreateExpHeapEx(ptr, param0[0], 0);
            UNK_021C4D28.unk_ptr1[r7] = res;
            UNK_021C4D28.unk_ptr5[r7] = (u8)r7;
        }
        else
        {
            ErrorHandling();
        }

        param0 += 2;
        r7++;
    }

    while (param1 < unk_size + 1)
    {
        UNK_021C4D28.unk_ptr1[param1] = 0;
        UNK_021C4D28.unk_ptr5[param1] = (u8)UNK_021C4D28.unk_half4;

        param1++;
    }

    while (param1 < param2)
    {
        UNK_021C4D28.unk_ptr5[param1] = (u8)UNK_021C4D28.unk_half4;

        param1++;
    }

    for (param1 = 0; param1 < param2; param1++)
    {
        UNK_021C4D28.unk_ptr4[param1] = 0;
    }
}

THUMB_FUNC s32 FUN_020167F4()
{
    s32 i = UNK_021C4D28.unk_half2;
    s32 j = UNK_021C4D28.unk_half3;

    if (i < j)
    {
        u32 *ptr = UNK_021C4D28.unk_ptr1 + i;
        do
        {
            if (*ptr == 0)
            {
                return i;
            }
            i++;
            ptr++;
        } while (i < j);
    }

    return -1;
}


THUMB_FUNC u32 FUN_0201681C(u32 param0, u32 param1, u32 param2) {
    return FUN_02016834(param0, param1, param2, 4);
}


THUMB_FUNC u32 FUN_02016828(u32 param0, u32 param1, u32 param2) {
    return FUN_02016834(param0, param1, param2, -4);
}