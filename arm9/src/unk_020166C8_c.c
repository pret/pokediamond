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


THUMB_FUNC void FUN_020166C8(u32 *param0, u32 param1, u32 param2, u32 pre_size)
{
    u32 r7;
    u32 saved_in_stack;
    
    saved_in_stack = param1 + 0x18;
    
    if (param2 < saved_in_stack)
    {
        param2 = saved_in_stack;
    }
    if (pre_size != 0)
    {
        while (pre_size % 4 != 0)
        {
            pre_size++;
        }

        OS_AllocFromArenaLo(0, pre_size, 4);
    }

    r7 = param2 * 2;
    void *ptr = OS_AllocFromArenaLo(0, (saved_in_stack * 3 + 1) * 4 + r7 + param2, 4);
    UNK_021C4D28.unk_ptr1 = ptr;
    ptr += (saved_in_stack + 1) * 4;
    UNK_021C4D28.unk_ptr2 = ptr;
    ptr += saved_in_stack * 4;
    UNK_021C4D28.unk_ptr3 = ptr;
    ptr += saved_in_stack * 4;
    UNK_021C4D28.unk_ptr4 = ptr;
    ptr += r7;
    UNK_021C4D28.unk_ptr5 = ptr;
    UNK_021C4D28.unk_half1 = param2;
    UNK_021C4D28.unk_half2 = param1;

    r7 = 0;
    UNK_021C4D28.unk_half4 = (u16)saved_in_stack;
    UNK_021C4D28.unk_half3 = (u16)saved_in_stack;

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

    while (param1 < saved_in_stack + 1)
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
