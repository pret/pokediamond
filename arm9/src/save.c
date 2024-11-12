#include "save.h"

#include "global.h"

#include "CARD_backup.h"
#include "MI_memory.h"
#include "OS_spinLock.h"
#include "heap.h"
#include "save_data_read_error.h"
#include "save_data_write_error.h"

// TODO: Migrate to headers

// unk_02015EA0.s
extern void sub_02016444(u8 mask);
extern void sub_02016454(u8 mask);

static BOOL saveWritten;
static SaveData *sSaveDataPtr;

struct SaveData *SaveData_New(void) {
    struct SaveData *save = AllocFromHeap(HEAP_ID_1, sizeof(struct SaveData));
    MI_CpuClearFast(save, sizeof(struct SaveData));
    sSaveDataPtr = save;
    save->flashOkay = SaveDetectFlash();
    save->saveFileExists = 0;
    save->isNewGame = 1;
    save->largeSectorChanged = 1;
    MATH_CRC16InitTable(&save->crcTable);
    SaveData_InitSubstructs(save->arrayHeaders);
    sub_02023160(save->saveSlotSpecs, save->arrayHeaders);
    MI_CpuClearFast(save->unk_20218, 8);
    switch (save->unk_00010 = sub_02022AD8(save)) {
    case 1:
        save->largeSectorChanged = 0;
        // fallthrough
    case 2:
        Save_LoadDynamicRegion(save);
        save->saveFileExists = 1;
        save->isNewGame = 0;
        break;
    case 0:
    case 3:
        Save_InitDynamicRegion(save);
        break;
    }
    return save;
}

struct SaveData *sub_020225F8(void) {
    GF_ASSERT(sSaveDataPtr != NULL);
    return sSaveDataPtr;
}

void *SaveArray_Get(struct SaveData *save, int idx) {
    GF_ASSERT(idx < 36);
    return (void *)(save->dynamic_region + save->arrayHeaders[idx].offset);
}

void *sub_02022634(struct SaveData *save, int idx) {
    return SaveArray_Get(save, idx);
}

// Sets bits at 0x021C491
// Clears bits at 0x021C491

BOOL sub_0202263C(struct SaveData *save) {
    u8 *r6 = AllocFromHeapAtEnd(HEAP_ID_MAIN, 0x1000);
    sub_02016444(1);
    FlashClobberChunkFooter(save, 0, (u32)(save->unk_20220[0] == 0 ? 1 : 0));
    FlashClobberChunkFooter(save, 1, (u32)(save->unk_20220[1] == 0 ? 1 : 0));
    FlashClobberChunkFooter(save, 0, (u32)(save->unk_20220[0]));
    FlashClobberChunkFooter(save, 1, (u32)(save->unk_20220[1]));
    MI_CpuFillFast(r6, -1u, 0x1000);
    for (int i = 0; i < 64; i++) {
        FlashWriteChunk((u32)(0x1000 * i), r6, 0x1000);
        FlashWriteChunk((u32)(0x1000 * (i + 0x40)), r6, 0x1000);
    }
    FreeToHeap(r6);
    Save_InitDynamicRegion(save);
    save->saveFileExists = 0;
    sub_02016454(1);
    return TRUE;
}

BOOL sub_020226FC(struct SaveData *save) {
    if (save->flashOkay == 0) {
        return FALSE;
    }
    if (Save_LoadDynamicRegion(save)) {
        save->saveFileExists = 1;
        save->isNewGame = 0;
        return TRUE;
    }
    return FALSE;
}

int SaveGame(struct SaveData *save) {
    if (save->flashOkay == 0) {
        return 3;
    }
    if (save->isNewGame) {
        sub_02016444(1);
        FlashClobberChunkFooter(save, 0, (u32)(save->unk_20220[0] == 0 ? 1 : 0));
        FlashClobberChunkFooter(save, 1, (u32)(save->unk_20220[1] == 0 ? 1 : 0));
        FlashClobberChunkFooter(save, 0, (u32)(save->unk_20220[0]));
        FlashClobberChunkFooter(save, 1, (u32)(save->unk_20220[1]));
        sub_02016454(1);
    }
    int ret = sub_02023044(save);
    if (ret == 2) {
        save->saveFileExists = 1;
        save->isNewGame = 0;
    }
    return ret;
}

void sub_020227A0(struct SaveData *save, int a1) {
    GF_ASSERT(a1 < 2);
    GF_ASSERT(save->isNewGame == 0);
    GF_ASSERT(save->saveFileExists == 1);
    sub_02022840(save, a1);
    int res;
    do {
        res = sub_02022854(save);
    } while (res == 0 || res == 1);
}

void Save_InitDynamicRegion(struct SaveData *save) {
    save->isNewGame = 1;
    save->largeSectorChanged = 1;
    Save_InitDynamicRegion_Internal(save->dynamic_region, save->arrayHeaders);
}

int sub_020227FC(struct SaveData *save) {
    return save->flashOkay;
}

int sub_02022800(struct SaveData *save) {
    return save->unk_00010;
}

u32 Save_FileExists(struct SaveData *save) {
    return save->saveFileExists;
}

u32 Save_IsNewGame(struct SaveData *save) {
    return save->isNewGame;
}

BOOL Save_FileDoesNotBelongToPlayer(struct SaveData *save) {
    return Save_IsNewGame(save) != 0 && Save_FileExists(save) != 0;
}

int Save_GetDirtyBit(struct SaveData *save) {
    return save->largeSectorChanged;
}

void Save_SetDirtyBit(void) {
    sSaveDataPtr->largeSectorChanged = 1;
}

void sub_02022840(struct SaveData *save, int a1) {
    sub_02022DFC(save, &save->asyncWriteMan, a1);
}

int sub_02022854(struct SaveData *save) {
    int r4 = sub_02022E78(save, &save->asyncWriteMan);
    if (r4 != 0 && r4 != 1) {
        sub_02022F80(save, &save->asyncWriteMan, r4);
    }
    return r4;
}

void sub_0202287C(struct SaveData *save) {
    sub_02022FF0(save, &save->asyncWriteMan);
}

void sub_0202288C(struct UnkStruct_0202288C *header) {
    header->unk_0 = 0;
    header->offset = 0;
    header->size = 0;
}

u16 sub_02022898(struct SaveData *save, void *data, u32 size) {
    return MATH_CalcCRC16CCITT(&save->crcTable, data, size - 20);
}

u32 GetChunkOffsetFromCurrentSaveSlot(u32 slot, struct SaveSlotSpec *header) {
    u32 offset;
    if (slot == 0) {
        offset = 0;
    } else {
        offset = 0x40000;
    }
    return offset + header->offset;
}

struct SaveChunkFooter *sub_020228B8(struct SaveData *save, u8 *offset, int idx) {
    u8 *r4;
    struct SaveSlotSpec *spec;

    spec = &save->saveSlotSpecs[idx];
    r4 = offset + spec->offset;
    GF_ASSERT(spec->size != 0);
    return (struct SaveChunkFooter *)(r4 + spec->size - 20);
}

BOOL sub_020228E0(struct SaveData *save, void *data, int idx) {
    struct SaveChunkFooter *r4;
    struct SaveSlotSpec *spec;

    spec = &save->saveSlotSpecs[idx];
    r4 = sub_020228B8(save, data, idx);
    u32 size = spec->size;
    u32 offset = spec->offset;
    if (r4->size != size) {
        return FALSE;
    }
    if (r4->magic != 0x20060623) {
        return FALSE;
    }
    if (r4->unk_10 != idx) {
        return FALSE;
    }
    return r4->crc == sub_02022898(save, (u8 *)data + offset, size);
}

void sub_0202293C(struct UnkStruct_0202288C *r5, struct SaveData *save, void *data, int idx) {
    struct SaveChunkFooter *r4;
    r4 = sub_020228B8(save, data, idx);
    r5->unk_0 = sub_020228E0(save, data, idx);
    r5->offset = r4->unk_0;
    r5->size = r4->offset;
}

void sub_02022968(struct SaveData *save, void *data, int idx) {
    struct SaveChunkFooter *r4;
    struct SaveSlotSpec *spec;

    spec = &save->saveSlotSpecs[idx];
    r4 = sub_020228B8(save, data, idx);
    data = (void *)((u8 *)data + spec->offset);
    r4->unk_0 = save->unk_20214;
    r4->offset = save->unk_20218[idx];
    r4->size = spec->size;
    r4->magic = 0x20060623;
    r4->unk_10 = (u8)idx;
    r4->crc = sub_02022898(save, data, spec->size);
}

int sub_020229B8(u32 x, u32 y) {
    if (x == -1u && y == 0) {
        return -1;
    }
    if (x == 0 && y == -1u) {
        return 1;
    }
    if (x > y) {
        return 1;
    }
    return -(x < y);
}

int sub_020229F0(struct UnkStruct_0202288C *r7, struct UnkStruct_0202288C *r6, u32 *r5, u32 *r4) {
    int sp0 = sub_020229B8(r7->offset, r6->offset);
    int r0 = sub_020229B8(r7->size, r6->size);
    if (r7->unk_0 != 0 && r6->unk_0 != 0) {
        if (sp0 > 0) {
            GF_ASSERT(r0 > 0);
            *r5 = 0;
            *r4 = 1;
        } else if (sp0 < 0) {
            GF_ASSERT(r0 < 0);
            *r5 = 1;
            *r4 = 0;
        } else if (r0 > 0) {
            *r5 = 0;
            *r4 = 1;
        } else if (r0 < 0) {
            *r5 = 1;
            *r4 = 0;
        } else {
            *r5 = 0;
            *r4 = 1;
        }
        return 2;
    } else if (r7->unk_0 != 0 && r6->unk_0 == 0) {
        *r5 = 0;
        *r4 = 2;
        return 1;
    } else if (r7->unk_0 == 0 && r6->unk_0 != 0) {
        *r5 = 1;
        *r4 = 2;
        return 1;
    } else {
        *r5 = 2;
        *r4 = 2;
        return 0;
    }
}

void sub_02022AA0(struct SaveData *save, struct UnkStruct_0202288C *a1, struct UnkStruct_0202288C *a2, u32 a3, u32 a4) {
    save->unk_20214 = a1[a3].offset;
    save->unk_20218[0] = a1[a3].size;
    save->unk_20218[1] = a2[a4].size;
    save->unk_20220[0] = (u8)a3;
    save->unk_20220[1] = (u8)a4;
}

int sub_02022AD8(struct SaveData *save) {
    struct UnkStruct_0202288C sp2C[2];
    struct UnkStruct_0202288C sp14[2];
    u32 sp10;
    u32 spC;
    u32 sp8;
    u32 sp4;
    {
        u8 *r6 = AllocFromHeapAtEnd(HEAP_ID_MAIN, 0x20000);
        u8 *r4 = AllocFromHeapAtEnd(HEAP_ID_MAIN, 0x20000);
        if (FlashLoadChunk(0, r6, 0x20000)) {
            sub_0202293C(&sp2C[0], save, r6, 0);
            sub_0202293C(&sp14[0], save, r6, 1);
        } else {
            sub_0202288C(&sp2C[0]);
            sub_0202288C(&sp14[0]);
        }
        if (FlashLoadChunk(0x40000, r4, 0x20000)) {
            sub_0202293C(&sp2C[1], save, r4, 0);
            sub_0202293C(&sp14[1], save, r4, 1);
        } else {
            sub_0202288C(&sp2C[1]);
            sub_0202288C(&sp14[1]);
        }
        FreeToHeap(r6);
        FreeToHeap(r4);
    }
    {
        int r4, r0;
        r4 = sub_020229F0(&sp2C[0], &sp2C[1], &sp10, &sp8);
        r0 = sub_020229F0(&sp14[0], &sp14[1], &spC, &sp4);
        if (r4 == 0 && r0 == 0) {
            return 0;
        } else if (r4 == 0 || r0 == 0) {
            return 3;
        } else if (r4 == 2 && r0 == 2) {
            if (sp2C[sp10].offset == sp14[spC].offset) {
                sub_02022AA0(save, sp2C, sp14, sp10, spC);
                return 1;
            } else {
                sub_02022AA0(save, sp2C, sp14, sp8, spC);
                return 2;
            }
        } else if (r4 == 1 && r0 == 2) {
            if (sp2C[sp10].offset == sp14[spC].offset) {
                sub_02022AA0(save, sp2C, sp14, sp10, spC);
                return 2;
            } else if (sp2C[sp10].offset == sp14[sp4].offset) {
                sub_02022AA0(save, sp2C, sp14, sp10, sp4);
                return 2;
            } else {
                return 3;
            }
        } else if (r4 == 2 && r0 == 1) {
            if (sp2C[sp10].offset == sp14[spC].offset) {
                sub_02022AA0(save, sp2C, sp14, sp10, spC);
                return 1;
            } else {
                sub_02022AA0(save, sp2C, sp14, sp8, spC);
                return 2;
            }
        } else if (r4 == 1 && r0 == 1 && sp10 == spC) {
            GF_ASSERT(sp2C[sp10].offset == sp14[spC].offset);
            sub_02022AA0(save, sp2C, sp14, sp10, spC);
            return 1;
        } else {
            GF_ASSERT(sp2C[sp10].offset == sp14[spC].offset);
            sub_02022AA0(save, sp2C, sp14, sp10, spC);
            return 2;
        }
    }
}

BOOL FlashLoadChunkIntoDynamicRegionFromHeader(u32 slot, struct SaveSlotSpec *header, u8 *dest) {
    return FlashLoadChunk(GetChunkOffsetFromCurrentSaveSlot(slot, header), dest + header->offset, header->size);
}

BOOL Save_LoadDynamicRegion(struct SaveData *save) {
    for (int i = 0; i < 2; i++) {
        if (!FlashLoadChunkIntoDynamicRegionFromHeader(save->unk_20220[i], &save->saveSlotSpecs[i], save->dynamic_region)) {
            return FALSE;
        }
        if (!sub_020228E0(save, save->dynamic_region, i)) {
            return FALSE;
        }
    }
    return TRUE;
}

int sub_02022D54(struct SaveData *save, int chunk, u8 slot) {
    struct SaveSlotSpec *header = &save->saveSlotSpecs[chunk];
    sub_02022968(save, save->dynamic_region, chunk);
    return FlashWriteChunkInternal(GetChunkOffsetFromCurrentSaveSlot(slot, header), save->dynamic_region + header->offset, header->size - 20);
}

int sub_02022D94(struct SaveData *save, int chunk, u8 slot) {
    struct SaveSlotSpec *header = &save->saveSlotSpecs[chunk];
    u32 size = header->size;
    return FlashWriteChunkInternal(GetChunkOffsetFromCurrentSaveSlot(slot, header) + size - 20, save->dynamic_region + header->offset + size - 20, 20);
}

int sub_02022DC8(struct SaveData *save, int chunk, u8 slot) {
    struct SaveSlotSpec *header = &save->saveSlotSpecs[chunk];
    u32 size = header->size;
    return FlashWriteChunkInternal(GetChunkOffsetFromCurrentSaveSlot(slot, header) + size - 12, save->dynamic_region + header->offset + size - 12, 8);
}

void sub_02022DFC(struct SaveData *save, struct AsyncWriteManager *a1, int a2) {
    for (int i = 0; i < 2; i++) {
        a1->unk_1C[i] = save->unk_20218[i];
        save->unk_20218[i]++;
    }
    a1->state = 0;
    a1->rollbackCounter = 0;
    if (a2 == 2) {
        if (save->largeSectorChanged) {
            a1->rollbackCounter = 1;
            a1->count = save->unk_20214;
            save->unk_20214++;
            a1->unk_4 = 0;
            a1->curSector = 0;
            a1->numSectors = 2;
        } else {
            a1->unk_4 = 0;
            a1->curSector = 0;
            a1->numSectors = 1;
        }
    } else {
        a1->unk_4 = a2;
        a1->curSector = a2;
        a1->numSectors = a2 + 1;
    }
    sub_02016444(1);
}

int sub_02022E78(struct SaveData *save, struct AsyncWriteManager *a1) {
    BOOL sp0;
    switch (a1->state) {
    case 0:
        a1->lockId = sub_02022D54(save, a1->curSector, (u8)(save->unk_20220[a1->curSector] == 0));
        a1->state++;
        // fallthrough
    case 1:
        if (!WaitFlashWrite(a1->lockId, &sp0)) {
            break;
        }
        if (sp0 == 0) {
            return 3;
        }
        a1->state++;
        // fallthrough
    case 2:
        a1->lockId = sub_02022DC8(save, a1->curSector, (u8)(save->unk_20220[a1->curSector] == 0));
        a1->state++;
        // fallthrough
    case 3:
        if (!WaitFlashWrite(a1->lockId, &sp0)) {
            break;
        }
        if (sp0 == 0) {
            return 3;
        }
        a1->state++;
        if (a1->curSector + 1 == a1->numSectors) {
            return 1;
        }
        // fallthrough
    case 4:
        a1->lockId = sub_02022D94(save, a1->curSector, (u8)(save->unk_20220[a1->curSector] == 0));
        a1->state++;
        // fallthrough
    case 5:
        if (!WaitFlashWrite(a1->lockId, &sp0)) {
            break;
        }
        if (sp0 == 0) {
            return 3;
        }
        a1->curSector++;
        if (a1->curSector == a1->numSectors) {
            return 2;
        }
        a1->state = 0;
        break;
    }
    return 0;
}

void sub_02022F80(struct SaveData *save, struct AsyncWriteManager *a1, int a2) {
    int i;
    if (a2 == 3) {
        if (a1->rollbackCounter) {
            save->unk_20214 = a1->count;
        }
        for (i = 0; i < 2; i++) {
            save->unk_20218[i] = a1->unk_1C[i];
        }
    } else {
        for (i = a1->unk_4; i < a1->numSectors; i++) {
            save->unk_20220[i] = (u8)(save->unk_20220[i] == 0);
        }
        save->saveFileExists = 1;
        save->isNewGame = 0;
        save->largeSectorChanged = 0;
    }
    sub_02016454(1);
}

void sub_02022FF0(struct SaveData *save, struct AsyncWriteManager *a1) {
    if (a1->rollbackCounter) {
        save->unk_20214 = a1->count;
    }
    for (int i = 0; i < 2; i++) {
        save->unk_20218[i] = a1->unk_1C[i];
    }
    if (!CARD_TryWaitBackupAsync()) {
        CARD_CancelBackupAsync();
        CARD_UnlockBackup((u16)a1->lockId);
        OS_ReleaseLockID((u16)a1->lockId);
    }
    sub_02016454(1);
}

int sub_02023044(struct SaveData *save) {
    int r4;
    struct AsyncWriteManager sp0;
    sub_02022DFC(save, &sp0, 2);
    do {
        r4 = sub_02022E78(save, &sp0);
    } while (r4 == 0 || r4 == 1);
    sub_02022F80(save, &sp0, r4);
    return r4;
}

int FlashClobberChunkFooter(struct SaveData *save, int x, u32 y) {
    u8 sp0[20];
    struct SaveSlotSpec *spec = &save->saveSlotSpecs[x];
    MI_CpuFill8(sp0, 0xFF, 20);
    return FlashWriteChunk((u32)(GetChunkOffsetFromCurrentSaveSlot(y, spec) + spec->size - 20), sp0, 20);
}

u32 SaveArray_sizeof(int idx) {
    const struct SaveChunkHeader *sch = UNK_020EE700;
    GF_ASSERT(idx < UNK_020EE6DC);
    s32 ret = (s32)sch[idx].sizeFunc();
    ret += (4 - (ret % 4));
    return (u32)ret;
}

void SaveData_InitSubstructs(struct SaveArrayHeader *headers) {
    const struct SaveChunkHeader *sch = UNK_020EE700;
    s32 offset = 0;
    GF_ASSERT(UNK_020EE6DC == 36);
    for (int i = 0; i < UNK_020EE6DC; i++) {
        GF_ASSERT(i == sch[i].id);
        headers[i].id = sch[i].id;
        headers[i].size = SaveArray_sizeof(i);
        headers[i].offset = (u32)offset;
        headers[i].crc = 0;
        headers[i].slot = (u16)sch[i].linkedId;
        offset += headers[i].size;
        if (i == UNK_020EE6DC - 1 || sch[i].linkedId != sch[i + 1].linkedId) {
            offset += 20;
        }
    }
    GF_ASSERT(offset <= 0x20000);
}

void sub_02023160(struct SaveSlotSpec *spec, struct SaveArrayHeader *headers) {
    int i = 0;
    int sp4 = 0;
    u32 r12 = 0;
    int j = 0;
    for (i = 0; i < 2; i++) {
        spec[i].id = (u8)i;
        spec[i].size = 0;
        while (i == headers[j].slot && j < UNK_020EE6DC) {
            spec[i].size += headers[j].size;
            j++;
        }
        spec[i].size += 20;
        spec[i].firstPage = (u8)sp4;
        spec[i].offset = r12;
        spec[i].numPages = (u8)((spec[i].size + 0xFFF) / 0x1000);
        sp4 += spec[i].numPages;
        r12 += spec[i].size;
    }
    GF_ASSERT(spec[1].firstPage + spec[1].numPages == sp4);
    GF_ASSERT(sp4 <= 32);
}

void Save_InitDynamicRegion_Internal(u8 *dynamic_region, struct SaveArrayHeader *headers) {
    const struct SaveChunkHeader *sch = UNK_020EE700;
    MI_CpuClearFast(dynamic_region, 0x20000);
    for (int i = 0; i < UNK_020EE6DC; i++) {
        u32 offset = headers[i].offset;
        MI_CpuClearFast(dynamic_region + offset, headers[i].size);
        sch[i].initFunc((void *)(dynamic_region + offset));
    }
}

void CreateChunkFooter(struct SaveData *save, u8 *data, int id, u32 size) {
    struct SaveArrayFooter *footer = (struct SaveArrayFooter *)(data + size);
    footer->magic = 0x20060623;
    footer->saveno = save->unk_204A4 + 1;
    footer->size = size;
    footer->idx = (u16)id;
    footer->crc = MATH_CalcCRC16CCITT(&save->crcTable, data, size + 14);
}

BOOL ValidateChunk(struct SaveData *save, u8 *data, int id, u32 size) {
    struct SaveArrayFooter *footer = (struct SaveArrayFooter *)(data + size);
    if (footer->magic != 0x20060623) {
        return FALSE;
    }
    if (footer->size != size) {
        return FALSE;
    }
    if (footer->idx != id) {
        return FALSE;
    }
    return footer->crc == MATH_CalcCRC16CCITT(&save->crcTable, data, size + 14);
}

u32 sub_020232B4(u8 *data, u32 size) {
    struct SaveArrayFooter *footer = (struct SaveArrayFooter *)(data + size);
    return footer->saveno;
}

int WriteSaveFileToFlash(struct SaveData *save, int idx, u8 *data) {
    sub_02016444(1);
    GF_ASSERT(idx < UNK_020EE6D8);
    const struct SaveChunkHeader *sch = &UNK_020EE6E0[idx];
    GF_ASSERT(sch->id == idx);
    u32 sp4 = sch->sizeFunc() + 16;
    int sp0;
    if (save->unk_204A0 == 1) {
        CreateChunkFooter(save, data, idx, sch->sizeFunc());
        sp0 = FlashWriteChunk((u32)(sch->linkedId << 12), data, sp4);
        GF_ASSERT(ValidateChunk(save, data, idx, sch->sizeFunc()) == 1);
        CreateChunkFooter(save, data, idx, sch->sizeFunc());
        sp0 |= FlashWriteChunk((u32)((sch->linkedId + 0x40) << 12), data, sp4);
        GF_ASSERT(ValidateChunk(save, data, idx, sch->sizeFunc()) == 1);
    } else {
        CreateChunkFooter(save, data, idx, sch->sizeFunc());
        sp0 = FlashWriteChunk((u32)((sch->linkedId + 0x40) << 12), data, sp4);
        GF_ASSERT(ValidateChunk(save, data, idx, sch->sizeFunc()) == 1);
        CreateChunkFooter(save, data, idx, sch->sizeFunc());
        sp0 |= FlashWriteChunk((u32)(sch->linkedId << 12), data, sp4);
        GF_ASSERT(ValidateChunk(save, data, idx, sch->sizeFunc()) == 1);
    }
    if (sp0 == 1) {
        sub_02016454(1);
        return 2;
    }
    sub_02016454(1);
    return 3;
}

u8 *ReadSaveFileFromFlash(struct SaveData *save, HeapID heapId, int idx, int *ret_p) {
    GF_ASSERT(idx < UNK_020EE6D8);
    const struct SaveChunkHeader *sch = &UNK_020EE6E0[idx];
    GF_ASSERT(sch->id == idx);
    u32 sp10 = sch->sizeFunc() + 16;
    int spC;
    u32 sp8;
    int r7;
    u32 sp4;
    u8 *r6 = AllocFromHeap(heapId, sp10);
    FlashLoadChunk((u32)(sch->linkedId << 12), r6, sp10);
    spC = ValidateChunk(save, r6, idx, sch->sizeFunc());
    sp8 = sub_020232B4(r6, sch->sizeFunc());
    FlashLoadChunk((u32)((sch->linkedId + 0x40) << 12), r6, sp10);
    r7 = ValidateChunk(save, r6, idx, sch->sizeFunc());
    sp4 = sub_020232B4(r6, sch->sizeFunc());
    *ret_p = 1;
    if (spC == 1 && r7 == 0) {
        save->unk_204A0 = 0;
        save->unk_204A4 = sp8;
        FlashLoadChunk((u32)(sch->linkedId << 12), r6, sp10);
        return r6;
    }
    if (spC == 0 && r7 == 1) {
        save->unk_204A0 = 1;
        save->unk_204A4 = sp4;
        FlashLoadChunk((u32)((sch->linkedId + 0x40) << 12), r6, sp10);
        return r6;
    }
    if (spC == 1 && r7 == 1) {
        if (sub_020229B8(sp8, sp4) != -1) {
            save->unk_204A0 = 0;
            save->unk_204A4 = sp8;
            FlashLoadChunk((u32)(sch->linkedId << 12), r6, sp10);
            return r6;
        }
        save->unk_204A0 = 1;
        save->unk_204A4 = sp4;
        FlashLoadChunk((u32)((sch->linkedId + 0x40) << 12), r6, sp10);
        return r6;
    }
    *ret_p = 2;
    save->unk_204A0 = 0;
    save->unk_204A4 = 0;
    return r6;
}

BOOL SaveDetectFlash(void) {
    int lock = OS_GetLockID();
    GF_ASSERT(lock != -3);
    CARD_LockBackup((u16)lock);
    u16 flash_type;
    if (CARD_IdentifyBackup(CARD_BACKUP_TYPE_FLASH_4MBITS)) {
        flash_type = CARD_BACKUP_TYPE_FLASH_4MBITS;
    } else if (CARD_IdentifyBackup(CARD_BACKUP_TYPE_FLASH_2MBITS)) {
        flash_type = CARD_BACKUP_TYPE_FLASH_2MBITS;
    } else {
        flash_type = 0;
    }
    CARD_UnlockBackup((u16)lock);
    OS_ReleaseLockID((u16)lock);
    return flash_type != 0;
}

int FlashWriteChunk(u32 offset, u8 *data, u32 size) {
    int ret;
    int id = FlashWriteChunkInternal(offset, data, size);
    while (!WaitFlashWrite(id, &ret))
        ;
    return ret;
}

BOOL FlashLoadChunk(u32 src, void *dest, u32 size) {
    int lock = OS_GetLockID();
    GF_ASSERT(lock != -3);
    CARD_LockBackup((u16)lock);
    CARDi_ReadBackup(src, dest, size, NULL, NULL, TRUE);
    BOOL r5 = CARD_WaitBackupAsync();
    CARD_UnlockBackup((u16)lock);
    OS_ReleaseLockID((u16)lock);
    if (!r5) {
        FreeToHeap(sSaveDataPtr);
        ShowSaveDataReadError(HEAP_ID_1);
    }
    return r5;
}

void FlashWriteCommandCallback(void *arg) {
#pragma unused(arg)
    saveWritten = TRUE;
}

int FlashWriteChunkInternal(u32 dest, void *src, u32 size) {
    int lock = OS_GetLockID();
    GF_ASSERT(lock != -3);
    CARD_LockBackup((u16)lock);
    int sp14;
    if (!CARDi_ReadBackup(0, &sp14, 4, NULL, NULL, FALSE)) {
        SaveErrorHandling(lock, 1);
    }
    saveWritten = FALSE;
    CARDi_WriteAndVerifyBackup(dest, src, size, FlashWriteCommandCallback, NULL, TRUE);
    return lock;
}

BOOL WaitFlashWrite(int lock, BOOL *res) {
    if (saveWritten == TRUE) {
        CARD_UnlockBackup((u16)lock);
        OS_ReleaseLockID((u16)lock);
        switch (CARD_GetResultCode()) {
        case CARD_RESULT_SUCCESS:
            *res = TRUE;
            break;
        default:
            GF_ASSERT(FALSE);
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

void SaveErrorHandling(int lock, u32 errno) {
    CARD_UnlockBackup((u16)lock);
    OS_ReleaseLockID((u16)lock);
    FreeToHeap(sSaveDataPtr);
    ShowSaveDataWriteError(HEAP_ID_1, errno);
}
