#ifndef POKEDIAMOND_SAVE_BLOCK_2_H
#define POKEDIAMOND_SAVE_BLOCK_2_H

#include "MATH_crc.h"

struct SavArrayHeader
{
    int id;
    u32 size;
    u32 offset;
    u16 field_C;
    u16 field_E;
};

struct SavArrayFooter
{
    u32 magic;
    u32 unk_4;
    u32 unk_8;
    u16 unk_C;
    u16 crc;
};

struct SaveChunkFooter
{
    u32 unk_0;
    u32 offset;
    u32 size;
    u32 magic;
    u8 unk_10;
    u8 padding_11;
    u16 crc;
};

struct SaveBlock2_Sub_20464 {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2;
    u8 padding_3;
    u32 offset;
    u32 size;
};

struct UnkSavSub_2047C
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_C;
    int unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C[2];
};

struct UnkStruct_0202288C
{
    BOOL unk_0;
    u32 offset;
    u32 size;
};

struct SaveBlock2
{
    /* 0x00000 */ BOOL flashOkay;
    /* 0x00004 */ int unk_00004;
    /* 0x00008 */ int unk_00008;
    /* 0x0000C */ int largeSectorChanged;
    /* 0x00010 */ int unk_00010;
    /* 0x00014 */ struct MATHCRC16Table crcTable;
    /* 0x00214 */ u8 dynamic_region[0x20000];
    /* 0x20214 */ u32 unk_20214;
    /* 0x20218 */ u32 unk_20218[2];
    /* 0x20220 */ u8 unk_20220[2];
    /* 0x20222 */ u8 filler_20222[2];
    /* 0x20224 */ struct SavArrayHeader arrayHeaders[36];
    /* 0x20464 */ struct SaveBlock2_Sub_20464 saveSlotSpecs[2];
    /* 0x2047C */ struct UnkSavSub_2047C unk_2047C;
    /* 0x204A0 */ u32 unk_204A0;
    /* 0x204A4 */ u32 unk_204A4;
}; // size: 0x204A8

typedef u32 (*SAVSIZEFN)(void);
typedef void (*SAVINITFN)(void *);

struct SaveChunkHeader
{
    int id;
    int linkedId;
    SAVSIZEFN sizeFunc;
    SAVINITFN initFunc;
};

extern const struct SaveChunkHeader UNK_020EE6E0[];
extern const struct SaveChunkHeader UNK_020EE700[];
extern const int UNK_020EE6DC;
extern const int UNK_020EE6D8;

struct SaveBlock2 * SaveBlock2_new(void);
struct SaveBlock2 * FUN_020225F8(void);
void * SavArray_get(struct SaveBlock2 * sav2, int idx);
void * FUN_02022634(struct SaveBlock2 * sav2, int idx);
BOOL FUN_0202263C(struct SaveBlock2 * sav2);
BOOL FUN_020226FC(struct SaveBlock2 * sav2);
int FUN_02022720(struct SaveBlock2 * sav2);
void FUN_020227A0(struct SaveBlock2 * sav2, int a1);
void Sav2_InitDynamicRegion(struct SaveBlock2 * sav2);
int FUN_020227FC(struct SaveBlock2 * sav2);
int FUN_02022800(struct SaveBlock2 * sav2);
int FUN_02022804(struct SaveBlock2 * sav2);
int FUN_02022808(struct SaveBlock2 * sav2);
BOOL FUN_0202280C(struct SaveBlock2 * sav2);
int SaveGetDirtyBit(struct SaveBlock2 * sav2);
void SaveSetDirtyBit(void);
void FUN_02022840(struct SaveBlock2 * sav2, int a1);
int FUN_02022854(struct SaveBlock2 * sav2);
void FUN_0202287C(struct SaveBlock2 * sav2);
void FUN_0202288C(struct UnkStruct_0202288C * header);
u16 FUN_02022898(struct SaveBlock2 * sav2, void * data, u32 size);
u32 GetChunkOffsetFromCurrentSaveSlot(u32 slot, struct SaveBlock2_Sub_20464 * header);
struct SaveChunkFooter * FUN_020228B8(struct SaveBlock2 * sav2, u8 * offset, int idx);
BOOL FUN_020228E0(struct SaveBlock2 * sav2, void * data, int idx);
void FUN_0202293C(struct UnkStruct_0202288C * r5, struct SaveBlock2 * sav2, void * data, int idx);
void FUN_02022968(struct SaveBlock2 * sav2, void * data, int idx);
int FUN_020229B8(u32 x, u32 y);
int FUN_020229F0(struct UnkStruct_0202288C * r7, struct UnkStruct_0202288C * r6, u32 * r5, u32 * r4);
void FUN_02022AA0(struct SaveBlock2 * sav2, struct UnkStruct_0202288C * a1, struct UnkStruct_0202288C * a2, u32 a3, u32 a4);
int FUN_02022AD8(struct SaveBlock2 * sav2);
BOOL FlashLoadChunkIntoDynamicRegionFromHeader(u32 slot, struct SaveBlock2_Sub_20464 * header, u8 * dest);
BOOL Sav2_LoadDynamicRegion(struct SaveBlock2 * sav2);
int FUN_02022D54(struct SaveBlock2 * sav2, int chunk, u8 slot);
int FUN_02022D94(struct SaveBlock2 * sav2, int chunk, u8 slot);
int FUN_02022DC8(struct SaveBlock2 * sav2, int chunk, u8 slot);
void FUN_02022DFC(struct SaveBlock2 * sav2, struct UnkSavSub_2047C * a1, int a2);
int FUN_02022E78(struct SaveBlock2 * sav2, struct UnkSavSub_2047C * a1);
void FUN_02022F80(struct SaveBlock2 * sav2, struct UnkSavSub_2047C * a1, int a2);
void FUN_02022FF0(struct SaveBlock2 * sav2, struct UnkSavSub_2047C * a1);
int FUN_02023044(struct SaveBlock2 * sav2);
int FlashClobberChunkFooter(struct SaveBlock2 * sav2, int x, u32 y);
u32 SavArray_sizeof(int idx);
void SaveBlock2_InitSubstructs(struct SavArrayHeader * headers);
void FUN_02023160(struct SaveBlock2_Sub_20464 * spec, struct SavArrayHeader * headers);
void Sav2_InitDynamicRegion_Internal(u8 * dynamic_region, struct SavArrayHeader * headers);
void CreateChunkFooter(struct SaveBlock2 * sav2, u8 * data, int id, u32 size);
BOOL ValidateChunk(struct SaveBlock2 * sav2, u8 * data, int id, u32 size);
u32 FUN_020232B4(u8 * data, u32 size);
int WriteSaveFileToFlash(struct SaveBlock2 * sav2, int idx, u8 * data);
u8 * ReadSaveFileFromFlash(struct SaveBlock2 * sav2, u32 heap_id, int idx, int * ret_p);
BOOL SaveDetectFlash(void);
int FlashWriteChunk(u32 offset, u8 * data, u32 size);
BOOL FlashLoadChunk(u32 src, void * dest, u32 size);
void FlashWriteCommandCallback(void * arg);
int FlashWriteChunkInternal(u32 dest, void * src, u32 size);
BOOL WaitFlashWrite(int lock, BOOL * res);
void SaveErrorHandling(int lock, u32 errno);

#endif //POKEDIAMOND_SAVE_BLOCK_2_H
