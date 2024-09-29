#ifndef POKEDIAMOND_UNK_020286F8_H
#define POKEDIAMOND_UNK_020286F8_H

#include "nitro/types.h"

#include "save.h"
#include "string16.h"

struct UnkSaveStruct_020286F8 {
    u16 unk_0[8];
    u16 unk_10[8];
    u8 unk_20;
    u8 unk_21;
    u8 filler_22[2];
    u32 unk_24;
    u32 unk_28;
};

u32 sub_020286F8(void);
void sub_02028700(struct UnkSaveStruct_020286F8 *ptr, int a, int b);
void sub_02028724(struct UnkSaveStruct_020286F8 *ptr);
void sub_02028754(struct UnkSaveStruct_020286F8 *ptr, u32 n);
u32 sub_0202877C(struct UnkSaveStruct_020286F8 *ptr, u32 i);
void sub_02028788(struct UnkSaveStruct_020286F8 *ptr, u32 i, u32 j);
u32 sub_020287A4(struct UnkSaveStruct_020286F8 *ptr);
u16 *sub_020287A8(struct UnkSaveStruct_020286F8 *ptr, u32 i, u32 j);
void sub_020287C0(struct UnkSaveStruct_020286F8 *ptr, u32 i, u32 j, struct String *k);
void sub_020287EC(struct UnkSaveStruct_020286F8 *ptr, u32 i, u32 j);
u8 sub_020287F8(struct UnkSaveStruct_020286F8 *ptr, u32 i);
u8 sub_02028804(struct UnkSaveStruct_020286F8 *ptr, u32 i);
void sub_02028810(struct UnkSaveStruct_020286F8 *ptr, u32 i, u32 j);
struct UnkSaveStruct_020286F8 *sub_0202881C(struct SaveData *save);
BOOL sub_02028828(struct UnkSaveStruct_020286F8 *ptr, u32 i);
BOOL sub_02028840(struct UnkSaveStruct_020286F8 *ptr, int i);
BOOL sub_02028854(struct UnkSaveStruct_020286F8 *ptr, const u16 *str);
BOOL sub_0202888C(struct UnkSaveStruct_020286F8 *ptr);
BOOL sub_020288AC(struct UnkSaveStruct_020286F8 *ptr, struct UnkSaveStruct_020286F8 *ptr2);

#endif // POKEDIAMOND_UNK_020286F8_H
