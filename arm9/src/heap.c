#include "heap.h"
#include "error_message_reset.h"
#include "unk_02031734.h"


extern void *NNS_FndCreateExpHeapEx(void *param0, u32 param1, u32 param2);
extern void *NNS_FndAllocFromExpHeapEx(void *param0, u32 param1, s32 param2);
extern void NNS_FndDestroyExpHeap();
extern void NNS_FndFreeToExpHeap(void *ptr1, void *ptr2);
extern u32 NNS_FndGetTotalFreeSizeForExpHeap(void *param0);
extern void NNS_FndInitAllocatorForExpHeap(u32 param0, void *param1, u32 param2);
extern u32 NNS_FndGetSizeForMBlockExpHeap(void *param0);
extern void NNS_FndResizeForMBlockExpHeap(void *ptr1, void *ptr2, u32 param2);


struct UnkStruct_020166C8 UNK_021C4D28;


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

        OS_AllocFromArenaLo(OS_ARENA_MAIN, pre_size, 4);
    }

    u32 r7 = param2 * 2;

    void *ptr = OS_AllocFromArenaLo(OS_ARENA_MAIN, (unk_size * 3 + 1) * sizeof(u32) + r7 + param2, 4);
    UNK_021C4D28.unk00 = ptr;
    ptr += (unk_size + 1) * 4;
    UNK_021C4D28.unk04 = ptr;
    ptr += unk_size * 4;
    UNK_021C4D28.unk08 = ptr;
    ptr += unk_size * 4;
    UNK_021C4D28.unk0c = ptr;
    ptr += r7;
    UNK_021C4D28.unk10 = ptr;
    UNK_021C4D28.unk14 = (u16)param2;
    UNK_021C4D28.unk16 = (u16)param1;

    r7 = 0;
    UNK_021C4D28.unk1a = (u16)unk_size;
    UNK_021C4D28.unk18 = (u16)unk_size;

    while (r7 < param1)
    {
        void *ptr;
        if (param0[1] == 0 || param0[1] != 2)
        {
            ptr = OS_AllocFromArenaLo(OS_ARENA_MAIN, param0[0], 4);
        }
        else
        {
            ptr = OS_AllocFromArenaHi(OS_ARENA_MAINEX, param0[0], 4);
        }

        if (ptr != 0)
        {

            UNK_021C4D28.unk00[r7] = NNS_FndCreateExpHeapEx(ptr, param0[0], 0);
            UNK_021C4D28.unk10[r7] = (u8)r7;
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
        UNK_021C4D28.unk00[param1] = 0;
        UNK_021C4D28.unk10[param1] = (u8)UNK_021C4D28.unk1a;

        param1++;
    }

    while (param1 < param2)
    {
        UNK_021C4D28.unk10[param1] = (u8)UNK_021C4D28.unk1a;

        param1++;
    }

    for (param1 = 0; param1 < param2; param1++)
    {
        UNK_021C4D28.unk0c[param1] = 0;
    }
}

THUMB_FUNC s32 FUN_020167F4()
{
    s32 i = UNK_021C4D28.unk16;
    s32 j = UNK_021C4D28.unk18;

    if (i < j)
    {
        void **ptr = UNK_021C4D28.unk00 + i;
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
    GF_ASSERT(OS_GetProcMode() != OS_PROCMODE_IRQ);

    u8 *ptr = UNK_021C4D28.unk10;
    if (UNK_021C4D28.unk1a == ptr[param1])
    {
        void *ptr2 = UNK_021C4D28.unk00[ptr[param0]];
        if (ptr2 != 0)
        {
            void *ptr3 = NNS_FndAllocFromExpHeapEx(ptr2, param2, param3);
            if (ptr3 != 0)
            {
                param3 = FUN_020167F4();
                if (param3 >= 0)
                {
                    UNK_021C4D28.unk00[param3] = NNS_FndCreateExpHeapEx(ptr3, param2, 0);


                    if (UNK_021C4D28.unk00[param3] != 0)
                    {
                        UNK_021C4D28.unk04[param3] = ptr2;
                        UNK_021C4D28.unk08[param3] = ptr3;
                        UNK_021C4D28.unk10[param1] = (u8)param3;

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

THUMB_FUNC void FUN_020168D0(u32 heap_id)
{
    GF_ASSERT (OS_GetProcMode() != OS_PROCMODE_IRQ);

    if (UNK_021C4D28.unk00[UNK_021C4D28.unk10[heap_id]] != 0)
    {
        NNS_FndDestroyExpHeap();

        u8 index = UNK_021C4D28.unk10[heap_id];
        void *ptr1 = UNK_021C4D28.unk04[index];
        void *ptr2 = UNK_021C4D28.unk08[index];
        if (ptr1 != 0 && ptr2 != 0)
        {
            NNS_FndFreeToExpHeap(ptr1, ptr2);
        }
        else
        {
            ErrorHandling();
        }

        UNK_021C4D28.unk00[UNK_021C4D28.unk10[heap_id]] = 0;
        UNK_021C4D28.unk04[UNK_021C4D28.unk10[heap_id]] = 0;
        UNK_021C4D28.unk08[UNK_021C4D28.unk10[heap_id]] = 0;

        UNK_021C4D28.unk10[heap_id] = (u8)UNK_021C4D28.unk1a;
    }
}

THUMB_FUNC u32 *FUN_02016944(void *param0, u32 param1, s32 param2, u32 param3)
{
    GF_ASSERT(param0);

    OSIntrMode intr_mode = OS_DisableInterrupts();
    param1 += 16;
    u32 *ptr = (u32 *)NNS_FndAllocFromExpHeapEx(param0, param1, param2);

    OS_RestoreInterrupts(intr_mode);
    if (ptr != 0)
    {
        ptr[3] = (ptr[3] & ~0xff) | (param3 & 0xff);

        ptr += 4;
    }

    return ptr;
}

THUMB_FUNC void FUN_02016988()
{
    if (FUN_02031810() != 0)
    {
        PrintErrorMessageAndReset();
    }
}

void *AllocFromHeap(u32 heap_id, u32 size)
{
    void *ptr = 0;
    if (heap_id < UNK_021C4D28.unk14)
    {
        u8 index = UNK_021C4D28.unk10[heap_id];
        ptr = FUN_02016944(UNK_021C4D28.unk00[index], size, 4, heap_id);
    }
    if (ptr != 0)
    {
        UNK_021C4D28.unk0c[heap_id]++;
    }
    else
    {
        FUN_02016988();
    }

    return ptr;
}

void *AllocFromHeapAtEnd(u32 heap_id, u32 size)
{
    void *ptr = 0;
    if (heap_id < UNK_021C4D28.unk14)
    {
        u8 index = UNK_021C4D28.unk10[heap_id];
        ptr = FUN_02016944(UNK_021C4D28.unk00[index], size, -4, heap_id);
    }

    if (ptr != 0)
    {
        UNK_021C4D28.unk0c[heap_id]++;
    }
    else
    {
        FUN_02016988();
    }

    return ptr;
}

void FreeToHeap(void *ptr)
{
    u8 heap_id = (u8)((u32 *)ptr)[-1];

    if ((u16)heap_id < UNK_021C4D28.unk14)
    {
        u8 index = UNK_021C4D28.unk10[heap_id];
        void *ptr2 = UNK_021C4D28.unk00[index];
        GF_ASSERT(ptr2);

        if (UNK_021C4D28.unk0c[heap_id] == 0)
        {
            FUN_02016B90(heap_id);
        }
        GF_ASSERT(UNK_021C4D28.unk0c[heap_id]);

        UNK_021C4D28.unk0c[heap_id]--;
        OSIntrMode intr_mode = OS_DisableInterrupts();
        NNS_FndFreeToExpHeap(ptr2, ptr - 16);
        OS_RestoreInterrupts(intr_mode);
        return;
    }

    ErrorHandling();
}

void FreeToHeapExplicit(u32 param0, void *param1)
{
    GF_ASSERT (OS_GetProcMode() != OS_PROCMODE_IRQ);

    if (param0 < UNK_021C4D28.unk14)
    {
        u8 index = UNK_021C4D28.unk10[param0];
        void *ptr = UNK_021C4D28.unk00[index];
        GF_ASSERT (ptr );

        u8 heap_id = (u8)((u32 *)param1)[-1];
        GF_ASSERT (heap_id == param0);

        NNS_FndFreeToExpHeap(ptr, param1 - 16);
        GF_ASSERT (UNK_021C4D28.unk0c[param0]);

        UNK_021C4D28.unk0c[param0]--;
        return;
    }

    ErrorHandling();
}

THUMB_FUNC u32 FUN_02016AF8(u32 param0)
{
    if (param0 < UNK_021C4D28.unk14)
    {
        u8 index = UNK_021C4D28.unk10[param0];
        return NNS_FndGetTotalFreeSizeForExpHeap(UNK_021C4D28.unk00[index]);
    }

    ErrorHandling();
    return 0;
}

THUMB_FUNC void FUN_02016B20(u32 param0, u32 param1, u32 param2)
{
    if (param1 < UNK_021C4D28.unk14)
    {

        u8 index = UNK_021C4D28.unk10[param1];
        NNS_FndInitAllocatorForExpHeap(param0, UNK_021C4D28.unk00[index], param2);
        return;
    }

    ErrorHandling();
}

THUMB_FUNC void FUN_02016B44(void *ptr, u32 param1)
{
    GF_ASSERT (OS_GetProcMode() != OS_PROCMODE_IRQ);

    param1 += 16;
    if (NNS_FndGetSizeForMBlockExpHeap(ptr - 16) >= param1)
    {
        u8 heap_id = (u8)((u32 *)ptr)[-1];

        u8 index = UNK_021C4D28.unk10[heap_id];

        NNS_FndResizeForMBlockExpHeap(UNK_021C4D28.unk00[index], ptr - 16, param1);
        return;
    }
    ErrorHandling();
}

THUMB_FUNC u32 FUN_02016B90(u32 param0)
{
#pragma unused(param0)
    return 1;
}
