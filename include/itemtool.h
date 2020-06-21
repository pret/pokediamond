#ifndef POKEDIAMOND_ITEMTOOL_H
#define POKEDIAMOND_ITEMTOOL_H

#include "global.h"
#include "filesystem.h"
#include "constants/items.h"

// Berries (nutdata)

struct NutData
{
    u16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
};

struct ItemSlot
{
    u16 id;
    u16 quantity;
};

struct ItemDataSub
{
    u8 unk0_0:1;
    u8 unk0_1:1;
    u8 unk0_2:1;
    u8 unk0_3:1;
    u8 unk0_4:1;
    u8 unk0_5:1;
    u8 unk0_6:1;
    u8 unk0_7:1;
    u8 unk1_0:1;
    u8 unk1_1:1;
    u8 unk1_2:1;
    u8 unk1_3:1;
    u8 unk1_4:4;
    u8 unk2_0:4;
    u8 unk2_4:4;
    u8 unk3_0:4;
    u8 unk3_4:4;
    u8 unk4_0:4;
    u8 unk4_4:2;
    u8 unk4_6:1;
    u8 unk4_7:1;
    u8 unk5_0:1;
    u8 unk5_1:1;
    u8 unk5_2:1;
    u8 unk5_3:1;
    u8 unk5_4:1;
    u8 unk5_5:1;
    u8 unk5_6:1;
    u8 unk5_7:1;
    u8 unk6_0:1;
    u8 unk6_1:1;
    u8 unk6_2:1;
    u8 unk6_3:1;
    s8 unk7;
    s8 unk8;
    s8 unk9;
    s8 unkA;
    s8 unkB;
    s8 unkC;
    u8 unkD;
    u8 unkE;
    s8 unkF;
    s8 unk10;
    s8 unk11;
    u8 paddding[4];
};

struct ItemData
{
    u16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u16 unk8_0:5;
    u16 unk8_5:1;
    u16 unk8_6:1;
    u16 unk8_7:4;
    u16 unk8_11:5;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
    union {
        u8 flat;
        struct ItemDataSub sub;
    } unkE;
};

NARC * OpenNutsDataNarc(u32 heap_id);
struct NutData * ReadNutDataFromNarc(NARC * narc, u32 berry_idx, u32 heap_id);
void CloseNutsDataNarc(NARC * narc);
struct NutData * LoadNutDataSingle(s32 berry_idx, u32 heap_id);
struct NutData * LoadNutDataSingleByItemId(s32 item_id, u32 heap_id);
u32 GetNutAttr(struct NutData * nut, u32 attr);
struct String * GetNutName(u32 berry_idx, u32 heap_id);
struct String * GetNutDesc(u32 berry_idx, u32 heap_id);

void FUN_0206E5B4(struct ItemSlot * itemSlots, u16 from, u16 to);
u16 FUN_0206E640(u16 a0, u16 a1);
u16 FUN_0206E6D8(u16 a0);
int FUN_0206E708();
int FUN_0206E70C();
void * FUN_0206E710(u16 a0, u16 a1, u32 heap_id);
void FUN_0206E768(struct String * dest, u16 item_id, u32 heap_no);
void FUN_0206E790(struct String * dest, u16 item_id, u32 heap_no);
u32 FUN_0206E7B8(u16 item, u32 attr, u32 heap_id);
u32 FUN_0206E7DC(struct ItemData * itemData, u32 attr);
u32 FUN_0206E878(struct ItemDataSub * sub, u32 attr);
u16 FUN_0206EA30(u16 a0);
BOOL FUN_0206EA54(u16 a0);
u8 FUN_0206EA7C(u16 a0);
BOOL FUN_0206EA98(u16 a0);
u8 FUN_0206EAB8(u16 a0);
u16 FUN_0206EAD8(u8 i);
BOOL FUN_0206EAEC(u16 a0);
u8 FUN_0206EB0C(u16 a0);
u16 FUN_0206EB1C(u8 a0);
u8 FUN_0206EB34(u16 a0);
struct ItemData * FUN_0206EB50(u16 a0);
struct ItemData * FUN_0206EB78(struct ItemData * a0, u16 a1);

#endif //POKEDIAMOND_ITEMTOOL_H
