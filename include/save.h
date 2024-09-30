#ifndef POKEDIAMOND_SAVE_H
#define POKEDIAMOND_SAVE_H

#include "constants/save_arrays.h"

#include "MATH_crc.h"
#include "heap.h"

struct SaveArrayHeader {
    int id;
    u32 size;
    u32 offset;
    u16 crc;
    u16 slot;
};

struct SaveArrayFooter {
    u32 magic;
    u32 saveno;
    u32 size;
    u16 idx;
    u16 crc;
};

struct SaveChunkFooter {
    u32 unk_0;
    u32 offset;
    u32 size;
    u32 magic;
    u8 unk_10;
    u8 padding_11;
    u16 crc;
};

struct SaveSlotSpec {
    u8 id;
    u8 firstPage;
    u8 numPages;
    u8 padding_3;
    u32 offset;
    u32 size;
};

struct AsyncWriteManager {
    int rollbackCounter;
    int unk_4;
    int curSector;
    int numSectors;
    int lockId;
    u32 state;
    u32 count;
    u32 unk_1C[2]; // differes from HG
};

struct UnkStruct_0202288C {
    BOOL unk_0;
    u32 offset;
    u32 size;
};

typedef struct SaveData {
    /* 0x00000 */ BOOL flashOkay;
    /* 0x00004 */ u32 saveFileExists;
    /* 0x00008 */ u32 isNewGame;
    /* 0x0000C */ int largeSectorChanged;
    /* 0x00010 */ int unk_00010;
    /* 0x00014 */ struct MATHCRC16Table crcTable;
    /* 0x00214 */ u8 dynamic_region[SAVE_PAGE_MAX * SAVE_SECTOR_SIZE];
    /* 0x20214 */ u32 unk_20214;
    /* 0x20218 */ u32 unk_20218[2];
    /* 0x20220 */ u8 unk_20220[2];
    /* 0x20222 */ u8 filler_20222[2];
    /* 0x20224 */ struct SaveArrayHeader arrayHeaders[SAVE_BLOCK_NUM];
    /* 0x20464 */ struct SaveSlotSpec saveSlotSpecs[2];
    /* 0x2047C */ struct AsyncWriteManager asyncWriteMan;
    /* 0x204A0 */ u32 unk_204A0;
    /* 0x204A4 */ u32 unk_204A4;
} SaveData; // size: 0x204A8

typedef u32 (*SAVSIZEFN)(void);
typedef void (*SAVINITFN)(void *);

struct SaveChunkHeader {
    int id;
    int linkedId;
    SAVSIZEFN sizeFunc;
    SAVINITFN initFunc;
};

extern const struct SaveChunkHeader UNK_020EE6E0[];
extern const struct SaveChunkHeader UNK_020EE700[];
extern const int UNK_020EE6DC;
extern const int UNK_020EE6D8;

struct SaveData *SaveData_New(void);
struct SaveData *sub_020225F8(void);
void *SaveArray_Get(struct SaveData *save, int idx);
void *sub_02022634(struct SaveData *save, int idx);
BOOL sub_0202263C(struct SaveData *save);
BOOL sub_020226FC(struct SaveData *save);
int SaveGame(struct SaveData *save);
void sub_020227A0(struct SaveData *save, int a1);
void Save_InitDynamicRegion(struct SaveData *save);
int sub_020227FC(struct SaveData *save);
int sub_02022800(struct SaveData *save);
u32 Save_FileExists(struct SaveData *save);
u32 Save_IsNewGame(struct SaveData *save);
BOOL Save_FileDoesNotBelongToPlayer(struct SaveData *save);
int Save_GetDirtyBit(struct SaveData *save);
void Save_SetDirtyBit(void);
void sub_02022840(struct SaveData *save, int a1);
int sub_02022854(struct SaveData *save);
void sub_0202287C(struct SaveData *save);
void sub_0202288C(struct UnkStruct_0202288C *header);
u16 sub_02022898(struct SaveData *save, void *data, u32 size);
u32 GetChunkOffsetFromCurrentSaveSlot(u32 slot, struct SaveSlotSpec *header);
struct SaveChunkFooter *sub_020228B8(struct SaveData *save, u8 *offset, int idx);
BOOL sub_020228E0(struct SaveData *save, void *data, int idx);
void sub_0202293C(struct UnkStruct_0202288C *r5, struct SaveData *save, void *data, int idx);
void sub_02022968(struct SaveData *save, void *data, int idx);
int sub_020229B8(u32 x, u32 y);
int sub_020229F0(struct UnkStruct_0202288C *r7, struct UnkStruct_0202288C *r6, u32 *r5, u32 *r4);
void sub_02022AA0(struct SaveData *save, struct UnkStruct_0202288C *a1, struct UnkStruct_0202288C *a2, u32 a3, u32 a4);
int sub_02022AD8(struct SaveData *save);
BOOL FlashLoadChunkIntoDynamicRegionFromHeader(u32 slot, struct SaveSlotSpec *header, u8 *dest);
BOOL Save_LoadDynamicRegion(struct SaveData *save);
int sub_02022D54(struct SaveData *save, int chunk, u8 slot);
int sub_02022D94(struct SaveData *save, int chunk, u8 slot);
int sub_02022DC8(struct SaveData *save, int chunk, u8 slot);
void sub_02022DFC(struct SaveData *save, struct AsyncWriteManager *a1, int a2);
int sub_02022E78(struct SaveData *save, struct AsyncWriteManager *a1);
void sub_02022F80(struct SaveData *save, struct AsyncWriteManager *a1, int a2);
void sub_02022FF0(struct SaveData *save, struct AsyncWriteManager *a1);
int sub_02023044(struct SaveData *save);
int FlashClobberChunkFooter(struct SaveData *save, int x, u32 y);
u32 SaveArray_sizeof(int idx);
void SaveData_InitSubstructs(struct SaveArrayHeader *headers);
void sub_02023160(struct SaveSlotSpec *spec, struct SaveArrayHeader *headers);
void Save_InitDynamicRegion_Internal(u8 *dynamic_region, struct SaveArrayHeader *headers);
void CreateChunkFooter(struct SaveData *save, u8 *data, int id, u32 size);
BOOL ValidateChunk(struct SaveData *save, u8 *data, int id, u32 size);
u32 sub_020232B4(u8 *data, u32 size);
int WriteSaveFileToFlash(struct SaveData *save, int idx, u8 *data);
u8 *ReadSaveFileFromFlash(struct SaveData *save, HeapID heapId, int idx, int *ret_p);
BOOL SaveDetectFlash(void);
int FlashWriteChunk(u32 offset, u8 *data, u32 size);
BOOL FlashLoadChunk(u32 src, void *dest, u32 size);
void FlashWriteCommandCallback(void *arg);
int FlashWriteChunkInternal(u32 dest, void *src, u32 size);
BOOL WaitFlashWrite(int lock, BOOL *res);
void SaveErrorHandling(int lock, u32 errno);

#endif // POKEDIAMOND_SAVE_H
