#include "heap.h"
#include "error_message_reset.h"
#include "unk_02031734.h"
#include "NNS_FND_expheap.h"
#include "NNS_FND_allocator.h"

struct UnkStruct_020166C8 UNK_021C4D28;

THUMB_FUNC void FUN_020166C8(const struct UnkStruct_020EDB10 *templates, u32 nTemplates, u32 totalNumHeaps, u32 pre_size)
{
    void * ptr;
    u32 unk_size, r7;

    unk_size = nTemplates + 24;

    if (totalNumHeaps < unk_size)
    {
        totalNumHeaps = unk_size;
    }
    if (pre_size != 0)
    {
        while (pre_size % 4 != 0)
        {
            pre_size++;
        }

        OS_AllocFromArenaLo(OS_ARENA_MAIN, pre_size, 4);
    }

    UNK_021C4D28.heapHandles = (NNSFndHeapHandle*) OS_AllocFromArenaLo(
        OS_ARENA_MAIN,
        (unk_size + 1) * sizeof(NNSFndHeapHandle)
      + unk_size * sizeof(NNSFndHeapHandle)
      + unk_size * sizeof(void *)
      + totalNumHeaps * sizeof(u16)
      + totalNumHeaps,
      4
    );
    UNK_021C4D28.unk04 = UNK_021C4D28.heapHandles + (unk_size + 1);
    UNK_021C4D28.unk08 = (void **)(UNK_021C4D28.unk04 + unk_size);
    UNK_021C4D28.unk0c = (u16 *)(UNK_021C4D28.unk08 + unk_size);
    UNK_021C4D28.heapIdxs = (u8 *)(UNK_021C4D28.unk0c + totalNumHeaps);
    UNK_021C4D28.totalNumHeaps = (u16)totalNumHeaps;
    UNK_021C4D28.nTemplates = (u16)nTemplates;

    UNK_021C4D28.unk1a = (u16)unk_size;
    UNK_021C4D28.unk18 = (u16)unk_size;

    for (r7 = 0; r7 < nTemplates; r7++)
    {
        switch (templates[r7].arena)
        {
        case OS_ARENA_MAIN:
        default:
            ptr = OS_AllocFromArenaLo(OS_ARENA_MAIN, templates[r7].size, 4);
            break;
        case OS_ARENA_MAINEX:
            ptr = OS_AllocFromArenaHi(OS_ARENA_MAINEX, templates[r7].size, 4);
            break;
        }

        if (ptr != NULL)
        {

            UNK_021C4D28.heapHandles[r7] = NNS_FndCreateExpHeap(ptr, templates[r7].size);
            UNK_021C4D28.heapIdxs[r7] = (u8)r7;
        }
        else
        {
            GF_ASSERT(0);
        }
    }

    while (nTemplates < unk_size + 1)
    {
        UNK_021C4D28.heapHandles[nTemplates] = NULL;
        UNK_021C4D28.heapIdxs[nTemplates] = (u8)UNK_021C4D28.unk1a;

        nTemplates++;
    }

    while (nTemplates < totalNumHeaps)
    {
        UNK_021C4D28.heapIdxs[nTemplates] = (u8)UNK_021C4D28.unk1a;

        nTemplates++;
    }

    for (nTemplates = 0; nTemplates < totalNumHeaps; nTemplates++)
    {
        UNK_021C4D28.unk0c[nTemplates] = 0;
    }
}

THUMB_FUNC s32 FUN_020167F4()
{
    s32 i;
    s32 j;

    for (i = UNK_021C4D28.nTemplates; i < UNK_021C4D28.unk18; i++)
    {
        if (UNK_021C4D28.heapHandles[i] == NULL)
            return i;
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

THUMB_FUNC u32 FUN_02016834(u32 param0, u32 param1, u32 size, s32 alignment)
{
    GF_ASSERT(OS_GetProcMode() != OS_PROCMODE_IRQ);

    u8 *ptr = UNK_021C4D28.heapIdxs;
    if (UNK_021C4D28.unk1a == ptr[param1])
    {
        NNSFndHeapHandle ptr2 = UNK_021C4D28.heapHandles[ptr[param0]];
        if (ptr2 != NULL)
        {
            void *ptr3 = NNS_FndAllocFromExpHeapEx(ptr2, size, alignment);
            if (ptr3 != NULL)
            {
                s32 i = FUN_020167F4();
                if (i >= 0)
                {
                    UNK_021C4D28.heapHandles[i] = NNS_FndCreateExpHeap(ptr3, size);


                    if (UNK_021C4D28.heapHandles[i] != 0)
                    {
                        UNK_021C4D28.unk04[i] = ptr2;
                        UNK_021C4D28.unk08[i] = ptr3;
                        UNK_021C4D28.heapIdxs[param1] = (u8)i;

                        return TRUE;
                    }
                    else
                    {
                        GF_ASSERT(0);
                    }
                }
                else
                {
                    GF_ASSERT(0);
                }
            }
            else
            {
                GF_ASSERT(0);
            }
        }
        else
        {
            GF_ASSERT(0);
        }
    }
    else
    {
        GF_ASSERT(0);
    }
    return 0;
}

THUMB_FUNC void FUN_020168D0(u32 heap_id)
{
    GF_ASSERT (OS_GetProcMode() != OS_PROCMODE_IRQ);

    NNSFndHeapHandle handle = UNK_021C4D28.heapHandles[UNK_021C4D28.heapIdxs[heap_id]];

    if (handle != NULL)
    {
        NNS_FndDestroyExpHeap(handle);

        u8 index = UNK_021C4D28.heapIdxs[heap_id];
        NNSFndHeapHandle ptr1 = UNK_021C4D28.unk04[index];
        void *ptr2 = UNK_021C4D28.unk08[index];
        if (ptr1 != NULL && ptr2 != NULL)
        {
            NNS_FndFreeToExpHeap(ptr1, ptr2);
        }
        else
        {
            GF_ASSERT(0);
        }

        UNK_021C4D28.heapHandles[UNK_021C4D28.heapIdxs[heap_id]] = NULL;
        UNK_021C4D28.unk04[UNK_021C4D28.heapIdxs[heap_id]] = NULL;
        UNK_021C4D28.unk08[UNK_021C4D28.heapIdxs[heap_id]] = NULL;

        UNK_021C4D28.heapIdxs[heap_id] = (u8)UNK_021C4D28.unk1a;
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
    if (heap_id < UNK_021C4D28.totalNumHeaps)
    {
        u8 index = UNK_021C4D28.heapIdxs[heap_id];
        ptr = FUN_02016944(UNK_021C4D28.heapHandles[index], size, 4, heap_id);
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
    if (heap_id < UNK_021C4D28.totalNumHeaps)
    {
        u8 index = UNK_021C4D28.heapIdxs[heap_id];
        ptr = FUN_02016944(UNK_021C4D28.heapHandles[index], size, -4, heap_id);
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

    if ((u16)heap_id < UNK_021C4D28.totalNumHeaps)
    {
        u8 index = UNK_021C4D28.heapIdxs[heap_id];
        void *ptr2 = UNK_021C4D28.heapHandles[index];
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

    GF_ASSERT(0);
}

void FreeToHeapExplicit(u32 param0, void *param1)
{
    GF_ASSERT (OS_GetProcMode() != OS_PROCMODE_IRQ);

    if (param0 < UNK_021C4D28.totalNumHeaps)
    {
        u8 index = UNK_021C4D28.heapIdxs[param0];
        void *ptr = UNK_021C4D28.heapHandles[index];
        GF_ASSERT (ptr );

        u8 heap_id = (u8)((u32 *)param1)[-1];
        GF_ASSERT (heap_id == param0);

        NNS_FndFreeToExpHeap(ptr, param1 - 16);
        GF_ASSERT (UNK_021C4D28.unk0c[param0]);

        UNK_021C4D28.unk0c[param0]--;
        return;
    }

    GF_ASSERT(0);
}

THUMB_FUNC u32 GF_ExpHeap_FndGetTotalFreeSize(u32 heap_id)
{
    if (heap_id < UNK_021C4D28.totalNumHeaps)
    {
        u8 index = UNK_021C4D28.heapIdxs[heap_id];
        return NNS_FndGetTotalFreeSizeForExpHeap(UNK_021C4D28.heapHandles[index]);
    }

    GF_ASSERT(0);
    return 0;
}

THUMB_FUNC void GF_ExpHeap_FndInitAllocator(NNSFndAllocator * pAllocator, u32 heap_id, int alignment)
{
    if (heap_id < UNK_021C4D28.totalNumHeaps)
    {

        u8 index = UNK_021C4D28.heapIdxs[heap_id];
        NNS_FndInitAllocatorForExpHeap(pAllocator, UNK_021C4D28.heapHandles[index], alignment);
        return;
    }

    GF_ASSERT(0);
}

THUMB_FUNC void ReallocFromHeap(void *ptr, u32 newSize)
{
    GF_ASSERT (OS_GetProcMode() != OS_PROCMODE_IRQ);

    newSize += 16;
    if (NNS_FndGetSizeForMBlockExpHeap(ptr - 16) >= newSize)
    {
        u8 heap_id = (u8)((u32 *)ptr)[-1];

        u8 index = UNK_021C4D28.heapIdxs[heap_id];

        NNS_FndResizeForMBlockExpHeap(UNK_021C4D28.heapHandles[index], ptr - 16, newSize);
        return;
    }
    GF_ASSERT(0);
}

THUMB_FUNC u32 FUN_02016B90(u32 param0)
{
#pragma unused(param0)
    return 1;
}
