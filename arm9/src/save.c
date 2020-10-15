#include "global.h"
#include "MI_memory.h"
#include "save_block_2.h"
#include "heap.h"
#include "CARD_backup.h"

#pragma thumb on

// TODO: Migrate to headers

// unk_02015EA0.s
extern void FUN_02016444(u8 mask);
extern void FUN_02016454(u8 mask);

// unk_02089D90.s
extern void FUN_02089D90(int);

// unk_02089F24.s
extern void FUN_0208A0B8(int, int);

struct {
    struct SaveBlock2 * ptr;
    BOOL iswritten;
} UNK_021C59C8;

struct SaveBlock2 * SaveBlock2_new(void)
{
    struct SaveBlock2 * sav2 = AllocFromHeap(1, sizeof(struct SaveBlock2));
    MI_CpuClearFast(sav2, sizeof(struct SaveBlock2));
    UNK_021C59C8.ptr = sav2;
    sav2->flashOkay = SaveDetectFlash();
    sav2->unk_00004 = 0;
    sav2->unk_00008 = 1;
    sav2->largeSectorChanged = 1;
    MATH_CRC16InitTable(&sav2->crcTable);
    SaveBlock2_InitSubstructs(sav2->arrayHeaders);
    FUN_02023160(sav2->saveSlotSpecs, sav2->arrayHeaders);
    MI_CpuClearFast(sav2->unk_20218, 8);
    switch (sav2->unk_00010 = FUN_02022AD8(sav2))
    {
    case 1:
        sav2->largeSectorChanged = 0;
        // fallthrough
    case 2:
        Sav2_LoadDynamicRegion(sav2);
        sav2->unk_00004 = 1;
        sav2->unk_00008 = 0;
        break;
    case 0:
    case 3:
        Sav2_InitDynamicRegion(sav2);
        break;
    }
    return sav2;
}

struct SaveBlock2 * FUN_020225F8(void)
{
    GF_ASSERT(UNK_021C59C8.ptr != NULL);
    return UNK_021C59C8.ptr;
}

void * SavArray_get(struct SaveBlock2 * sav2, int idx)
{
    GF_ASSERT(idx < 36);
    return (void *)(sav2->dynamic_region + sav2->arrayHeaders[idx].offset);
}

void * FUN_02022634(struct SaveBlock2 * sav2, int idx)
{
    return SavArray_get(sav2, idx);
}

// Sets bits at 0x021C491
// Clears bits at 0x021C491

BOOL FUN_0202263C(struct SaveBlock2 * sav2)
{
    u8 * r6 = AllocFromHeapAtEnd(3, 0x1000);
    FUN_02016444(1);
    FlashClobberChunkFooter(sav2, 0, (u32)(sav2->unk_20220[0] == 0 ? 1 : 0));
    FlashClobberChunkFooter(sav2, 1, (u32)(sav2->unk_20220[1] == 0 ? 1 : 0));
    FlashClobberChunkFooter(sav2, 0, (u32)(sav2->unk_20220[0]));
    FlashClobberChunkFooter(sav2, 1, (u32)(sav2->unk_20220[1]));
    MIi_CpuClearFast(-1u, r6, 0x1000);
    for (int i = 0; i < 64; i++)
    {
        FlashWriteChunk((u32)(0x1000 * i), r6, 0x1000);
        FlashWriteChunk((u32)(0x1000 * (i + 0x40)), r6, 0x1000);
    }
    FreeToHeap(r6);
    Sav2_InitDynamicRegion(sav2);
    sav2->unk_00004 = 0;
    FUN_02016454(1);
    return TRUE;
}

BOOL FUN_020226FC(struct SaveBlock2 * sav2)
{
    if (sav2->flashOkay == 0)
        return FALSE;
    if (Sav2_LoadDynamicRegion(sav2))
    {
        sav2->unk_00004 = 1;
        sav2->unk_00008 = 0;
        return TRUE;
    }
    return FALSE;
}

int FUN_02022720(struct SaveBlock2 * sav2)
{
    if (sav2->flashOkay == 0)
        return 3;
    if (sav2->unk_00008)
    {
        FUN_02016444(1);
        FlashClobberChunkFooter(sav2, 0, (u32)(sav2->unk_20220[0] == 0 ? 1 : 0));
        FlashClobberChunkFooter(sav2, 1, (u32)(sav2->unk_20220[1] == 0 ? 1 : 0));
        FlashClobberChunkFooter(sav2, 0, (u32)(sav2->unk_20220[0]));
        FlashClobberChunkFooter(sav2, 1, (u32)(sav2->unk_20220[1]));
        FUN_02016454(1);
    }
    int ret = FUN_02023044(sav2);
    if (ret == 2)
    {
        sav2->unk_00004 = 1;
        sav2->unk_00008 = 0;
    }
    return ret;
}

void FUN_020227A0(struct SaveBlock2 * sav2, int a1)
{
    GF_ASSERT(a1 < 2);
    GF_ASSERT(sav2->unk_00008 == 0);
    GF_ASSERT(sav2->unk_00004 == 1);
    FUN_02022840(sav2, a1);
    int res;
    do
    {
        res = FUN_02022854(sav2);
    } while (res == 0 || res == 1);
}

void Sav2_InitDynamicRegion(struct SaveBlock2 * sav2)
{
    sav2->unk_00008 = 1;
    sav2->largeSectorChanged = 1;
    Sav2_InitDynamicRegion_Internal(sav2->dynamic_region, sav2->arrayHeaders);
}

int FUN_020227FC(struct SaveBlock2 * sav2)
{
    return sav2->flashOkay;
}

int FUN_02022800(struct SaveBlock2 * sav2)
{
    return sav2->unk_00010;
}

int FUN_02022804(struct SaveBlock2 * sav2)
{
    return sav2->unk_00004;
}

int FUN_02022808(struct SaveBlock2 * sav2)
{
    return sav2->unk_00008;
}

BOOL FUN_0202280C(struct SaveBlock2 * sav2)
{
    return (FUN_02022808(sav2) != 0 && FUN_02022804(sav2) != 0);
}

int SaveGetDirtyBit(struct SaveBlock2 * sav2)
{
    return sav2->largeSectorChanged;
}

void SaveSetDirtyBit(void)
{
    UNK_021C59C8.ptr->largeSectorChanged = 1;
}

void FUN_02022840(struct SaveBlock2 * sav2, int a1)
{
    FUN_02022DFC(sav2, &sav2->unk_2047C, a1);
}

int FUN_02022854(struct SaveBlock2 * sav2)
{
    int r4 = FUN_02022E78(sav2, &sav2->unk_2047C);
    if (r4 != 0 && r4 != 1)
    {
        FUN_02022F80(sav2, &sav2->unk_2047C, r4);
    }
    return r4;
}

void FUN_0202287C(struct SaveBlock2 * sav2)
{
    FUN_02022FF0(sav2, &sav2->unk_2047C);
}

void FUN_0202288C(struct UnkStruct_0202288C * header)
{
    header->unk_0 = 0;
    header->offset = 0;
    header->size = 0;
}

u16 FUN_02022898(struct SaveBlock2 * sav2, void * data, u32 size)
{
    return MATH_CalcCRC16CCITT(&sav2->crcTable, data, size - 20);
}

u32 GetChunkOffsetFromCurrentSaveSlot(u32 slot, struct SaveBlock2_Sub_20464 * header)
{
    u32 offset;
    if (slot == 0)
        offset = 0;
    else
        offset = 0x40000;
    return offset + header->offset;
}

struct SaveChunkFooter * FUN_020228B8(struct SaveBlock2 * sav2, u8 * offset, int idx)
{
    u8 * r4;
    struct SaveBlock2_Sub_20464 * sub20464;

    sub20464 = &sav2->saveSlotSpecs[idx];
    r4 = offset + sub20464->offset;
    GF_ASSERT(sub20464->size != 0);
    return (struct SaveChunkFooter *)(r4 + sub20464->size - 20);
}

BOOL FUN_020228E0(struct SaveBlock2 * sav2, void * data, int idx)
{
    struct SaveChunkFooter * r4;
    struct SaveBlock2_Sub_20464 * sub20464;

    sub20464 = &sav2->saveSlotSpecs[idx];
    r4 = FUN_020228B8(sav2, data, idx);
    u32 size = sub20464->size;
    u32 offset = sub20464->offset;
    if (r4->size != size)
        return FALSE;
    if (r4->magic != 0x20060623)
        return FALSE;
    if (r4->unk_10 != idx)
        return FALSE;
    return r4->crc == FUN_02022898(sav2, (u8 *)data + offset, size);
}

void FUN_0202293C(struct UnkStruct_0202288C * r5, struct SaveBlock2 * sav2, void * data, int idx)
{
    struct SaveChunkFooter * r4;
    r4 = FUN_020228B8(sav2, data, idx);
    r5->unk_0 = FUN_020228E0(sav2, data, idx);
    r5->offset = r4->unk_0;
    r5->size = r4->offset;
}

void FUN_02022968(struct SaveBlock2 * sav2, void * data, int idx)
{
    struct SaveChunkFooter * r4;
    struct SaveBlock2_Sub_20464 * sub20464;

    sub20464 = &sav2->saveSlotSpecs[idx];
    r4 = FUN_020228B8(sav2, data, idx);
    data = (void *)((u8 *)data + sub20464->offset);
    r4->unk_0 = sav2->unk_20214;
    r4->offset = sav2->unk_20218[idx];
    r4->size = sub20464->size;
    r4->magic = 0x20060623;
    r4->unk_10 = (u8)idx;
    r4->crc = FUN_02022898(sav2, data, sub20464->size);
}

int FUN_020229B8(u32 x, u32 y)
{
    if (x == -1u && y == 0)
        return -1;
    if (x == 0 && y == -1u)
        return 1;
    if (x > y)
        return 1;
    return -(x < y);
}

int FUN_020229F0(struct UnkStruct_0202288C * r7, struct UnkStruct_0202288C * r6, u32 * r5, u32 * r4)
{
    int sp0 = FUN_020229B8(r7->offset, r6->offset);
    int r0 = FUN_020229B8(r7->size, r6->size);
    if (r7->unk_0 != 0 && r6->unk_0 != 0)
    {
        if (sp0 > 0)
        {
            GF_ASSERT(r0 > 0);
            *r5 = 0;
            *r4 = 1;
        }
        else if (sp0 < 0)
        {
            GF_ASSERT(r0 < 0);
            *r5 = 1;
            *r4 = 0;
        }
        else if (r0 > 0)
        {
            *r5 = 0;
            *r4 = 1;
        }
        else if (r0 < 0)
        {
            *r5 = 1;
            *r4 = 0;
        }
        else
        {
            *r5 = 0;
            *r4 = 1;
        }
        return 2;
    }
    else if (r7->unk_0 != 0 && r6->unk_0 == 0)
    {
        *r5 = 0;
        *r4 = 2;
        return 1;
    }
    else if (r7->unk_0 == 0 && r6->unk_0 != 0)
    {
        *r5 = 1;
        *r4 = 2;
        return 1;
    }
    else
    {
        *r5 = 2;
        *r4 = 2;
        return 0;
    }
}

void FUN_02022AA0(struct SaveBlock2 * sav2, struct UnkStruct_0202288C * a1, struct UnkStruct_0202288C * a2, u32 a3, u32 a4)
{
    sav2->unk_20214 = a1[a3].offset;
    sav2->unk_20218[0] = a1[a3].size;
    sav2->unk_20218[1] = a2[a4].size;
    sav2->unk_20220[0] = (u8)a3;
    sav2->unk_20220[1] = (u8)a4;
}

int FUN_02022AD8(struct SaveBlock2 * sav2)
{
    struct UnkStruct_0202288C sp2C[2];
    struct UnkStruct_0202288C sp14[2];
    u32 sp10;
    u32 spC;
    u32 sp8;
    u32 sp4;
    {
        u8 *r6 = AllocFromHeapAtEnd(3, 0x20000);
        u8 *r4 = AllocFromHeapAtEnd(3, 0x20000);
        if (FlashLoadChunk(0, r6, 0x20000))
        {
            FUN_0202293C(&sp2C[0], sav2, r6, 0);
            FUN_0202293C(&sp14[0], sav2, r6, 1);
        }
        else
        {
            FUN_0202288C(&sp2C[0]);
            FUN_0202288C(&sp14[0]);
        }
        if (FlashLoadChunk(0x40000, r4, 0x20000))
        {
            FUN_0202293C(&sp2C[1], sav2, r4, 0);
            FUN_0202293C(&sp14[1], sav2, r4, 1);
        }
        else
        {
            FUN_0202288C(&sp2C[1]);
            FUN_0202288C(&sp14[1]);
        }
        FreeToHeap(r6);
        FreeToHeap(r4);
    }
    {
        int r4, r0;
        r4 = FUN_020229F0(&sp2C[0], &sp2C[1], &sp10, &sp8);
        r0 = FUN_020229F0(&sp14[0], &sp14[1], &spC, &sp4);
        if (r4 == 0 && r0 == 0)
            return 0;
        else if (r4 == 0 || r0 == 0)
            return 3;
        else if (r4 == 2 && r0 == 2)
        {
            if (sp2C[sp10].offset == sp14[spC].offset)
            {
                FUN_02022AA0(sav2, sp2C, sp14, sp10, spC);
                return 1;
            }
            else
            {
                FUN_02022AA0(sav2, sp2C, sp14, sp8, spC);
                return 2;
            }
        }
        else if (r4 == 1 && r0 == 2)
        {
            if (sp2C[sp10].offset == sp14[spC].offset)
            {
                FUN_02022AA0(sav2, sp2C, sp14, sp10, spC);
                return 2;
            }
            else if (sp2C[sp10].offset == sp14[sp4].offset)
            {
                FUN_02022AA0(sav2, sp2C, sp14, sp10, sp4);
                return 2;
            }
            else
            {
                return 3;
            }
        }
        else if (r4 == 2 && r0 == 1)
        {
            if (sp2C[sp10].offset == sp14[spC].offset)
            {
                FUN_02022AA0(sav2, sp2C, sp14, sp10, spC);
                return 1;
            }
            else
            {
                FUN_02022AA0(sav2, sp2C, sp14, sp8, spC);
                return 2;
            }
        }
        else if (r4 == 1 && r0 == 1 && sp10 == spC)
        {
            GF_ASSERT(sp2C[sp10].offset == sp14[spC].offset);
            FUN_02022AA0(sav2, sp2C, sp14, sp10, spC);
            return 1;
        }
        else
        {
            GF_ASSERT(sp2C[sp10].offset == sp14[spC].offset);
            FUN_02022AA0(sav2, sp2C, sp14, sp10, spC);
            return 2;
        }
    }
}

BOOL FlashLoadChunkIntoDynamicRegionFromHeader(u32 slot, struct SaveBlock2_Sub_20464 * header, u8 * dest)
{
    return FlashLoadChunk(GetChunkOffsetFromCurrentSaveSlot(slot, header), dest + header->offset, header->size);
}

BOOL Sav2_LoadDynamicRegion(struct SaveBlock2 * sav2)
{
    for (int i = 0; i < 2; i++)
    {
        if (!FlashLoadChunkIntoDynamicRegionFromHeader(sav2->unk_20220[i], &sav2->saveSlotSpecs[i], sav2->dynamic_region)) return FALSE;
        if (!FUN_020228E0(sav2, sav2->dynamic_region, i)) return FALSE;
    }
    return TRUE;
}

int FUN_02022D54(struct SaveBlock2 * sav2, int chunk, u8 slot)
{
    struct SaveBlock2_Sub_20464 * header = &sav2->saveSlotSpecs[chunk];
    FUN_02022968(sav2, sav2->dynamic_region, chunk);
    return FlashWriteChunkInternal(GetChunkOffsetFromCurrentSaveSlot(slot, header), sav2->dynamic_region + header->offset, header->size - 20);
}

int FUN_02022D94(struct SaveBlock2 * sav2, int chunk, u8 slot)
{
    struct SaveBlock2_Sub_20464 * header = &sav2->saveSlotSpecs[chunk];
    u32 size = header->size;
    return FlashWriteChunkInternal(GetChunkOffsetFromCurrentSaveSlot(slot, header) + size - 20, sav2->dynamic_region + header->offset + size - 20, 20);
}

int FUN_02022DC8(struct SaveBlock2 * sav2, int chunk, u8 slot)
{
    struct SaveBlock2_Sub_20464 * header = &sav2->saveSlotSpecs[chunk];
    u32 size = header->size;
    return FlashWriteChunkInternal(GetChunkOffsetFromCurrentSaveSlot(slot, header) + size - 12, sav2->dynamic_region + header->offset + size - 12, 8);
}

void FUN_02022DFC(struct SaveBlock2 * sav2, struct UnkSavSub_2047C * a1, int a2)
{
    for (int i = 0; i < 2; i++)
    {
        a1->unk_1C[i] = sav2->unk_20218[i];
        sav2->unk_20218[i]++;
    }
    a1->unk_14 = 0;
    a1->unk_0 = 0;
    if (a2 == 2)
    {
        if (sav2->largeSectorChanged)
        {
            a1->unk_0 = 1;
            a1->unk_18 = sav2->unk_20214;
            sav2->unk_20214++;
            a1->unk_4 = 0;
            a1->unk_8 = 0;
            a1->unk_C = 2;
        }
        else
        {
            a1->unk_4 = 0;
            a1->unk_8 = 0;
            a1->unk_C = 1;
        }
    }
    else
    {
        a1->unk_4 = a2;
        a1->unk_8 = a2;
        a1->unk_C = a2 + 1;
    }
    FUN_02016444(1);
}

int FUN_02022E78(struct SaveBlock2 * sav2, struct UnkSavSub_2047C * a1)
{
    BOOL sp0;
    switch (a1->unk_14)
    {
    case 0:
        a1->unk_10 = FUN_02022D54(sav2, a1->unk_8, (u8)(sav2->unk_20220[a1->unk_8] == 0));
        a1->unk_14++;
        // fallthrough
    case 1:
        if (!WaitFlashWrite(a1->unk_10, &sp0))
            break;
        if (sp0 == 0)
            return 3;
        a1->unk_14++;
        // fallthrough
    case 2:
        a1->unk_10 = FUN_02022DC8(sav2, a1->unk_8, (u8)(sav2->unk_20220[a1->unk_8] == 0));
        a1->unk_14++;
        // fallthrough
    case 3:
        if (!WaitFlashWrite(a1->unk_10, &sp0))
            break;
        if (sp0 == 0)
            return 3;
        a1->unk_14++;
        if (a1->unk_8 + 1 == a1->unk_C)
            return 1;
        // fallthrough
    case 4:
        a1->unk_10 = FUN_02022D94(sav2, a1->unk_8, (u8)(sav2->unk_20220[a1->unk_8] == 0));
        a1->unk_14++;
        // fallthrough
    case 5:
        if (!WaitFlashWrite(a1->unk_10, &sp0))
            break;
        if (sp0 == 0)
            return 3;
        a1->unk_8++;
        if (a1->unk_8 == a1->unk_C)
            return 2;
        a1->unk_14 = 0;
        break;
    }
    return 0;
}

void FUN_02022F80(struct SaveBlock2 * sav2, struct UnkSavSub_2047C * a1, int a2)
{
    int i;
    if (a2 == 3)
    {
        if (a1->unk_0)
        {
            sav2->unk_20214 = a1->unk_18;
        }
        for (i = 0; i < 2; i++)
        {
            sav2->unk_20218[i] = a1->unk_1C[i];
        }
    }
    else
    {
        for (i = a1->unk_4; i < a1->unk_C; i++)
        {
            sav2->unk_20220[i] = (u8)(sav2->unk_20220[i] == 0);
        }
        sav2->unk_00004 = 1;
        sav2->unk_00008 = 0;
        sav2->largeSectorChanged = 0;
    }
    FUN_02016454(1);
}

void FUN_02022FF0(struct SaveBlock2 * sav2, struct UnkSavSub_2047C * a1)
{
    if (a1->unk_0)
        sav2->unk_20214 = a1->unk_18;
    for (int i = 0; i < 2; i++)
    {
        sav2->unk_20218[i] = a1->unk_1C[i];
    }
    if (!CARD_TryWaitBackupAsync())
    {
        CARD_CancelBackupAsync();
        CARD_UnlockBackup((u16)a1->unk_10);
        OS_ReleaseLockID((u16)a1->unk_10);
    }
    FUN_02016454(1);
}

int FUN_02023044(struct SaveBlock2 * sav2)
{
    int r4;
    struct UnkSavSub_2047C sp0;
    FUN_02022DFC(sav2, &sp0, 2);
    do
    {
        r4 = FUN_02022E78(sav2, &sp0);
    } while (r4 == 0 || r4 == 1);
    FUN_02022F80(sav2, &sp0, r4);
    return r4;
}

int FlashClobberChunkFooter(struct SaveBlock2 * sav2, int x, u32 y)
{
    u8 sp0[20];
    struct SaveBlock2_Sub_20464 * r5 = &sav2->saveSlotSpecs[x];
    MI_CpuFill8(sp0, 0xFF, 20);
    return FlashWriteChunk((u32)(GetChunkOffsetFromCurrentSaveSlot(y, r5) + r5->size - 20), sp0, 20);
}

u32 SavArray_sizeof(int idx)
{
    const struct SaveChunkHeader * sch = UNK_020EE700;
    GF_ASSERT(idx < UNK_020EE6DC);
    s32 ret = (s32)sch[idx].sizeFunc();
    ret += (4 - (ret % 4));
    return (u32)ret;
}

void SaveBlock2_InitSubstructs(struct SavArrayHeader * headers)
{
    const struct SaveChunkHeader * sch = UNK_020EE700;
    s32 offset = 0;
    GF_ASSERT(UNK_020EE6DC == 36);
    for (int i = 0; i < UNK_020EE6DC; i++)
    {
        GF_ASSERT(i == sch[i].id);
        headers[i].id = sch[i].id;
        headers[i].size = SavArray_sizeof(i);
        headers[i].offset = (u32)offset;
        headers[i].field_C = 0;
        headers[i].field_E = (u16)sch[i].linkedId;
        offset += headers[i].size;
        if (i == UNK_020EE6DC - 1 || sch[i].linkedId != sch[i + 1].linkedId)
            offset += 20;
    }
    GF_ASSERT(offset <= 0x20000);
}

void FUN_02023160(struct SaveBlock2_Sub_20464 * spec, struct SavArrayHeader * headers)
{
    int i = 0;
    int sp4 = 0;
    u32 r12 = 0;
    int j = 0;
    for (i = 0; i < 2; i++)
    {
        spec[i].unk_0 = (u8)i;
        spec[i].size = 0;
        while (i == headers[j].field_E && j < UNK_020EE6DC)
        {
            spec[i].size += headers[j].size;
            j++;
        }
        spec[i].size += 20;
        spec[i].unk_1 = (u8)sp4;
        spec[i].offset = r12;
        spec[i].unk_2 = (u8)((spec[i].size + 0xFFF) / 0x1000);
        sp4 += spec[i].unk_2;
        r12 += spec[i].size;
    }
    GF_ASSERT(spec[1].unk_1 + spec[1].unk_2 == sp4);
    GF_ASSERT(sp4 <= 32);
}

void Sav2_InitDynamicRegion_Internal(u8 * dynamic_region, struct SavArrayHeader * headers)
{
    const struct SaveChunkHeader * sch = UNK_020EE700;
    MI_CpuClearFast(dynamic_region, 0x20000);
    for (int i = 0; i < UNK_020EE6DC; i++)
    {
        u32 offset = headers[i].offset;
        MI_CpuClearFast(dynamic_region + offset, headers[i].size);
        sch[i].initFunc((void *)(dynamic_region + offset));
    }
}

void CreateChunkFooter(struct SaveBlock2 * sav2, u8 * data, int id, u32 size)
{
    struct SavArrayFooter * footer = (struct SavArrayFooter *)(data + size);
    footer->magic = 0x20060623;
    footer->unk_4 = sav2->unk_204A4 + 1;
    footer->unk_8 = size;
    footer->unk_C = (u16)id;
    footer->crc = MATH_CalcCRC16CCITT(&sav2->crcTable, data, size + 14);
}

BOOL ValidateChunk(struct SaveBlock2 * sav2, u8 * data, int id, u32 size)
{
    struct SavArrayFooter * footer = (struct SavArrayFooter *)(data + size);
    if (footer->magic != 0x20060623)
        return FALSE;
    if (footer->unk_8 != size)
        return FALSE;
    if (footer->unk_C != id)
        return FALSE;
    return (footer->crc == MATH_CalcCRC16CCITT(&sav2->crcTable, data, size + 14));
}

u32 FUN_020232B4(u8 * data, u32 size)
{
    struct SavArrayFooter * footer = (struct SavArrayFooter *)(data + size);
    return footer->unk_4;
}

int WriteSaveFileToFlash(struct SaveBlock2 * sav2, int idx, u8 * data)
{
    FUN_02016444(1);
    GF_ASSERT(idx < UNK_020EE6D8);
    const struct SaveChunkHeader * sch = &UNK_020EE6E0[idx];
    GF_ASSERT(sch->id == idx);
    u32 sp4 = sch->sizeFunc() + 16;
    int sp0;
    if (sav2->unk_204A0 == 1)
    {
        CreateChunkFooter(sav2, data, idx, sch->sizeFunc());
        sp0 = FlashWriteChunk((u32)(sch->linkedId << 12), data, sp4);
        GF_ASSERT(ValidateChunk(sav2, data, idx, sch->sizeFunc()) == 1);
        CreateChunkFooter(sav2, data, idx, sch->sizeFunc());
        sp0 |= FlashWriteChunk((u32)((sch->linkedId + 0x40) << 12), data, sp4);
        GF_ASSERT(ValidateChunk(sav2, data, idx, sch->sizeFunc()) == 1);
    }
    else
    {
        CreateChunkFooter(sav2, data, idx, sch->sizeFunc());
        sp0 = FlashWriteChunk((u32)((sch->linkedId + 0x40) << 12), data, sp4);
        GF_ASSERT(ValidateChunk(sav2, data, idx, sch->sizeFunc()) == 1);
        CreateChunkFooter(sav2, data, idx, sch->sizeFunc());
        sp0 |= FlashWriteChunk((u32)(sch->linkedId << 12), data, sp4);
        GF_ASSERT(ValidateChunk(sav2, data, idx, sch->sizeFunc()) == 1);
    }
    if (sp0 == 1)
    {
        FUN_02016454(1);
        return 2;
    }
    FUN_02016454(1);
    return 3;
}

u8 * ReadSaveFileFromFlash(struct SaveBlock2 * sav2, u32 heap_id, int idx, int * ret_p)
{
    GF_ASSERT(idx < UNK_020EE6D8);
    const struct SaveChunkHeader * sch = &UNK_020EE6E0[idx];
    GF_ASSERT(sch->id == idx);
    u32 sp10 = sch->sizeFunc() + 16;
    int spC;
    u32 sp8;
    int r7;
    u32 sp4;
    u8 * r6 = AllocFromHeap(heap_id, sp10);
    FlashLoadChunk((u32)(sch->linkedId << 12), r6, sp10);
    spC = ValidateChunk(sav2, r6, idx, sch->sizeFunc());
    sp8 = FUN_020232B4(r6, sch->sizeFunc());
    FlashLoadChunk((u32)((sch->linkedId + 0x40) << 12), r6, sp10);
    r7 = ValidateChunk(sav2, r6, idx, sch->sizeFunc());
    sp4 = FUN_020232B4(r6, sch->sizeFunc());
    *ret_p = 1;
    if (spC == 1 && r7 == 0)
    {
        sav2->unk_204A0 = 0;
        sav2->unk_204A4 = sp8;
        FlashLoadChunk((u32)(sch->linkedId << 12), r6, sp10);
        return r6;
    }
    if (spC == 0 && r7 == 1)
    {
        sav2->unk_204A0 = 1;
        sav2->unk_204A4 = sp4;
        FlashLoadChunk((u32)((sch->linkedId + 0x40) << 12), r6, sp10);
        return r6;
    }
    if (spC == 1 && r7 == 1)
    {
        if (FUN_020229B8(sp8, sp4) != -1)
        {
            sav2->unk_204A0 = 0;
            sav2->unk_204A4 = sp8;
            FlashLoadChunk((u32)(sch->linkedId << 12), r6, sp10);
            return r6;
        }
        sav2->unk_204A0 = 1;
        sav2->unk_204A4 = sp4;
        FlashLoadChunk((u32)((sch->linkedId + 0x40) << 12), r6, sp10);
        return r6;
    }
    *ret_p = 2;
    sav2->unk_204A0 = 0;
    sav2->unk_204A4 = 0;
    return r6;
}

BOOL SaveDetectFlash(void)
{
    int lock = OS_GetLockID();
    GF_ASSERT(lock != -3);
    CARD_LockBackup((u16)lock);
    u16 flash_type;
    if (CARD_IdentifyBackup((CARDBackupType)0x1302))
        flash_type = 0x1302;
    else if (CARD_IdentifyBackup((CARDBackupType)0x1202))
        flash_type = 0x1202;
    else
        flash_type = 0;
    CARD_UnlockBackup((u16)lock);
    OS_ReleaseLockID((u16)lock);
    return flash_type != 0;
}

int FlashWriteChunk(u32 offset, u8 * data, u32 size)
{
    int ret;
    int id = FlashWriteChunkInternal(offset, data, size);
    while (!WaitFlashWrite(id, &ret))
        ;
    return ret;
}

BOOL FlashLoadChunk(u32 src, void * dest, u32 size)
{
    int lock = OS_GetLockID();
    GF_ASSERT(lock != -3);
    CARD_LockBackup((u16)lock);
    CARDi_ReadBackup(src, dest, size, NULL, NULL, TRUE);
    BOOL r5 = CARD_WaitBackupAsync();
    CARD_UnlockBackup((u16)lock);
    OS_ReleaseLockID((u16)lock);
    if (!r5)
    {
        FreeToHeap(UNK_021C59C8.ptr);
        FUN_02089D90(1);
    }
    return r5;
}

void FlashWriteCommandCallback(void * arg)
{
#pragma unused(arg)
    UNK_021C59C8.iswritten = TRUE;
}

int FlashWriteChunkInternal(u32 dest, void * src, u32 size)
{
    int lock = OS_GetLockID();
    GF_ASSERT(lock != -3);
    CARD_LockBackup((u16)lock);
    int sp14;
    if (!CARDi_ReadBackup(0, &sp14, 4, NULL, NULL, FALSE))
        SaveErrorHandling(lock, 1);
    UNK_021C59C8.iswritten = FALSE;
    CARDi_WriteAndVerifyBackup(dest, src, size, FlashWriteCommandCallback, NULL, TRUE);
    return lock;
}

BOOL WaitFlashWrite(int lock, BOOL * res)
{
    if (UNK_021C59C8.iswritten == TRUE)
    {
        CARD_UnlockBackup((u16)lock);
        OS_ReleaseLockID((u16)lock);
        switch (CARD_GetResultCode())
        {
        case CARD_RESULT_SUCCESS:
            *res = TRUE;
            break;
        default:
            GF_ASSERT(0);
        case CARD_RESULT_TIMEOUT:
            *res = FALSE;
            SaveErrorHandling(lock, 0);
        case CARD_RESULT_NO_RESPONSE:
            *res = FALSE;
            SaveErrorHandling(lock, 1);
        }
        return TRUE;
    }
    return FALSE;
}

void SaveErrorHandling(int lock, int errno)
{
    CARD_UnlockBackup((u16)lock);
    OS_ReleaseLockID((u16)lock);
    FreeToHeap(UNK_021C59C8.ptr);
    FUN_0208A0B8(1, errno);
}
