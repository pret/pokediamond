#ifndef POKEDIAMOND_UNK_020139D8_H
#define POKEDIAMOND_UNK_020139D8_H

struct UnkStruct_020139D8
{
    u32 heap_id;
    struct MsgData * msgDatas[11];
};

struct UnkStruct_02013B28
{
    u32 unk_0;
    u32 unk_4;
};

struct UnkStruct_020139D8 * EasyChatManager_New(u32 heap_id);
void EasyChatManager_Delete(struct UnkStruct_020139D8 * unk);
void EasyChatManager_ReadWordIntoString(struct UnkStruct_020139D8 * unk, u16 a1, struct String * str);
void GetECWordIntoStringByIndex(u16 a0, struct String * a1);
u16 GetECWordIndexByPair(u16 a0, u16 a1);
void GetCategoryAndMsgNoByECWordIdx(u32 a0, s32 * a1, s32 * a2);
u32 FUN_02013B28(void);
void FUN_02013B2C(struct UnkStruct_02013B28 * unk);
struct UnkStruct_02013B28 * FUN_02013B5C(struct SaveBlock2 * sav2);
BOOL FUN_02013B68(struct UnkStruct_02013B28 * unk, u32 a1);
s32 FUN_02013B74(struct UnkStruct_02013B28 * unk);
BOOL FUN_02013BC8(struct UnkStruct_02013B28 * unk);
u16 FUN_02013BE4(u16 a0);
BOOL FUN_02013C0C(struct UnkStruct_02013B28 * unk, u32 a1);
void FUN_02013C18(struct UnkStruct_02013B28 * unk, u32 a1);
s32 FUN_02013C28(u16 a0);
u16 FUN_02013C6C(u16 a0, s32 a1);

#endif //POKEDIAMOND_UNK_020139D8_H
