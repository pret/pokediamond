#include "global.h"

struct UnkStruct_020166C8
{
    u32 *unk_ptr1;
    u32 *unk_ptr2;
    void **unk_ptr3;
    u16 *unk_ptr4;
    u8 *unk_ptr5;
    u16 unk_half1;
    u16 unk_half2;
    u16 unk_half3;
    u16 unk_half4;
};

struct UnkStruct_020166C8 UNK_021C4D28;

extern void *tempName_NNS_FndCreateExpHeapEx(void *param0, u32 param1, u32 param2);
extern void *tempName_NNS_FndAllocFromExpHeapEx(void *param0, u32 param1, s32 param2);
u32 FUN_02016834(u32 param0, u32 param1, u32 param2, s32 param3);
extern void thunk_FUN_020adc8c();
extern void FUN_020ADDF0(u32 param0, void *param1);

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

THUMB_FUNC u32 FUN_0201681C(u32 param0, u32 param1, u32 param2)
{
    return FUN_02016834(param0, param1, param2, 4);
}

THUMB_FUNC u32 FUN_02016828(u32 param0, u32 param1, u32 param2)
{
    return FUN_02016834(param0, param1, param2, -4);
}


THUMB_FUNC u32 FUN_02016834(u32 param0, u32 param1, u32 param2, s32 param3)
{
    if (OS_GetProcMode() == OS_PROCMODE_IRQ)
    {
        ErrorHandling();
    }

    u8 *ptr = UNK_021C4D28.unk_ptr5;
    if (UNK_021C4D28.unk_half4 == ptr[param1])
    {
        u32 r6 = UNK_021C4D28.unk_ptr1[ptr[param0]];
        if (r6 != 0)
        {
            void *res = tempName_NNS_FndAllocFromExpHeapEx(r6, param2, param3);
            if (res != 0)
            {
                param3 = FUN_020167F4();
                if (param3 >= 0)
                {
                    UNK_021C4D28.unk_ptr1[param3] = tempName_NNS_FndCreateExpHeapEx(res, param2, 0);

                    if (UNK_021C4D28.unk_ptr1[param3] != 0)
                    {
                        UNK_021C4D28.unk_ptr2[param3] = r6;
                        UNK_021C4D28.unk_ptr3[param3] = res;
                        UNK_021C4D28.unk_ptr5[param1] = param3;

                        return 1;
                    }
                    else
                    {
                        ErrorHandling();
                    }
                }
                else
                {
                    ErrorHandling();
                }
            }
            else
            {
                ErrorHandling();
            }
        }
        else
        {
            ErrorHandling();
        }
    }
    else
    {
        ErrorHandling();
    }
    return 0;
}


THUMB_FUNC void FUN_020168D0(u32 param0) {
    if (OS_GetProcMode() == OS_PROCMODE_IRQ) {
        ErrorHandling();
    }

    if (UNK_021C4D28.unk_ptr1[UNK_021C4D28.unk_ptr5[param0]] != 0) {
        thunk_FUN_020adc8c();

        u8 index = UNK_021C4D28.unk_ptr5[param0];
        u32 arg1 = UNK_021C4D28.unk_ptr2[index];
        void *arg2 = UNK_021C4D28.unk_ptr3[index];
        if (arg1 != 0 && arg2 != 0) {
            FUN_020ADDF0(arg1, arg2);
        } else {
            ErrorHandling();
        }



        UNK_021C4D28.unk_ptr1[UNK_021C4D28.unk_ptr5[param0]] = 0;
        UNK_021C4D28.unk_ptr2[UNK_021C4D28.unk_ptr5[param0]] = 0;
        UNK_021C4D28.unk_ptr3[UNK_021C4D28.unk_ptr5[param0]] = 0;

        UNK_021C4D28.unk_ptr5[param0] = UNK_021C4D28.unk_half4;
    }
}


THUMB_FUNC u32 FUN_02016944(void *param0, u32 param1, u32 param2, u8 param3) {
    if (param0 == 0) {
        ErrorHandling();
    }
    OSIntrMode os_mode = OS_DisableInterrupts();
    param1+=16;
    u32 *ptr = (u32 *) tempName_NNS_FndAllocFromExpHeapEx(param0, param1, param2);

    OS_RestoreInterrupts(os_mode);
    if (ptr != 0) {
        ptr[3] = (ptr[3] & ~0xff) | (param3 & 0xff);

        ptr+=4;
    }

    return ptr;
}