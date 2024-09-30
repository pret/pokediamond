#ifndef POKEDIAMOND_UNK_02085338_H
#define POKEDIAMOND_UNK_02085338_H

#include "easy_chat.h"
#include "pokedex.h"
#include "save.h"

struct UnkStruct_02085338 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u32 unk_08;
    struct Pokedex *unk_0c;
    struct SaveEasyChat *unk_10;
    struct MailMessage unk_14;
    u16 unk_1c[2];
    u8 padding_20[4];
};

struct UnkStruct_02085338 *sub_02085338(u8 r5, u8 r7, struct SaveData *save, HeapID heapId);
void sub_020853A8(struct UnkStruct_02085338 *ptr);
void sub_020853B0(struct UnkStruct_02085338 *ptr, u16 a1);
void sub_020853B4(struct UnkStruct_02085338 *ptr, u16 a1, u16 a2);
void sub_020853BC(struct UnkStruct_02085338 *ptr, const struct MailMessage *a1);
void sub_020853D0(struct UnkStruct_02085338 *ptr);
void sub_020853DC(struct UnkStruct_02085338 *ptr);
u8 sub_020853E4(struct UnkStruct_02085338 *ptr);
u8 sub_020853E8(struct UnkStruct_02085338 *ptr);
u16 sub_020853EC(struct UnkStruct_02085338 *ptr);
void sub_020853F0(struct UnkStruct_02085338 *ptr, u16 *a1);
void sub_020853FC(struct UnkStruct_02085338 *ptr, struct MailMessage *a1);
u8 sub_0208540C(struct UnkStruct_02085338 *ptr);
u8 sub_02085410(struct UnkStruct_02085338 *ptr);
u32 sub_02085414(struct UnkStruct_02085338 *ptr);
struct Pokedex *sub_02085418(struct UnkStruct_02085338 *ptr);
struct SaveEasyChat *sub_0208541C(struct UnkStruct_02085338 *ptr);
u8 sub_02085420(struct UnkStruct_02085338 *ptr);
u8 sub_02085424(struct UnkStruct_02085338 *ptr);
void sub_02085428(struct UnkStruct_02085338 *ptr, u16 *a1, struct MailMessage *a2);
BOOL sub_0208545C(struct UnkStruct_02085338 *ptr, const u16 *a1, const struct MailMessage *a2);
void sub_020854A0(struct UnkStruct_02085338 *r5, u16 *r4, struct MailMessage *r6);

#endif // POKEDIAMOND_UNK_02085338_H
