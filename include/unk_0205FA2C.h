#ifndef POKEDIAMOND_UNK_0205FA2C_H
#define POKEDIAMOND_UNK_0205FA2C_H

#include "global.h"
#include "MI_memory.h"
#include "bag.h"
#include "battle_setup.h"
#include "heap.h"
#include "party.h"
#include "player_data.h"
#include "script.h"
#include "task.h"
#include "unk_020286F8.h"
#include "unk_02029FB0.h"
#include "unk_0202A8F4.h"
#include "unk_02031480.h"
#include "unk_0206BB28.h"

struct UnkPlayerStruct1_0205FA2C
{
    /* 0x00 */ struct Party *player_party;
    /* 0x04 */ struct Bag *bag;
    u32 unk08;
    /* 0x0c */ struct Options *options;
    u32 unk10[4];
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    u32 unk24[2];
    u8 unk2c[6];
    u8 unk32 : 4;
    u8 unk322 : 4;
    u8 unk33;
    u32 unk34[3];
};

struct UnkPlayerStruct2_0205FA2C
{
    /* 0x00 */ struct Party *player_party;
    /* 0x04 */ struct Options *options;
    u32 unk08;
    u32 unk0c;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    /* 0x04 */ u8 party_count;
    u8 unk14;
    u8 unk15[3];
    u16 unk18;
    u16 unk1a;
    /* 0x1c */ BOOL IsNatDex;
    void *unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2c;
};

struct UnkCallbackStruct1_0205FA2C
{
    u32 unk00;
    u32 unk04;
    u8 unk08;
    u8 unk09;
    u8 unk0a;
    u8 unk0b;
    u8 unk0c;
    u8 unk0d;
    u8 unk0e[6];
    void **unk14;
};

struct UnkCallbackStruct2_0205FA2C
{
    u32 unk00;
    u32 unk04;
    u32 *unk08;
    u32 unk0c;
    u16 unk10;
    u16 unk12;
    u16 unk14;
};

u32 sub_0205FA2C(
    struct UnkCallbackStruct1_0205FA2C *param0, struct FieldSystem *fieldSystem, HeapID heapId);
u32 sub_0205FAD8(
    struct UnkCallbackStruct1_0205FA2C *param0, struct FieldSystem *fieldSystem);
u32 sub_0205FB34(
    struct UnkCallbackStruct1_0205FA2C *param0, struct FieldSystem *fieldSystem, HeapID heapId);
u32 sub_0205FBC0(
    struct UnkCallbackStruct1_0205FA2C *param0, struct FieldSystem *fieldSystem);
BOOL sub_0205FBE8(struct TaskManager *taskManager);
void sub_0205FC50(struct TaskManager *taskManager,
    void **param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u8 param6,
    u8 param7);

u32 sub_0205FC9C(
    struct UnkCallbackStruct2_0205FA2C *param0, struct FieldSystem *fieldSystem);
u32 sub_0205FCC4(
    struct UnkCallbackStruct2_0205FA2C *param0, struct FieldSystem *fieldSystem);
BOOL sub_0205FCE8(struct TaskManager *taskManager);
void sub_0205FD38(struct TaskManager *taskManager, u16 param1, u16 param2, u16 param3);

BOOL sub_0205FD70(struct TaskManager *taskManager);
void sub_0205FDDC(struct TaskManager *taskManager, u16 param1, u16 param2);

u32 sub_0205FE10(struct SaveData *save);
u32 sub_0205FF5C(struct SaveData *save);
void sub_02060044(FieldSystem *fieldSystem, BattleSetupUnkSub138 *battleSetupSub);
u32 sub_02060064(u32 param0);
u32 sub_02060070(u32 param0);
u32 sub_0206007C(struct SaveData *save);
u32 sub_020600A0(struct SaveData *save);
u32 sub_020600DC(struct SaveData *save);
BOOL sub_02060144(u32 **param0);

#endif // POKEDIAMOND_UNK_0205FA2C_H
