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
    u16 price;
    u8 holdEffect;
    u8 holdEffectParam;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u16 unk8_0:5;
    u16 unk8_5:1;
    u16 unk8_6:1;
    u16 pocket:4;
    u16 unk8_B:5;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 padding;
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

void MoveItemSlotInList(struct ItemSlot * itemSlots, u16 from, u16 to);
u16 GetItemIndexMapping(u16 a0, u16 a1);
u16 UpConvertItemId_Gen3to4(u16 a0);
int FUN_0206E708();
int FUN_0206E70C();
void * LoadItemDataOrGfx(u16 a0, u16 a1, u32 heap_id);
void GetItemNameIntoString(struct String * dest, u16 item_id, u32 heap_no);
void GetItemDescIntoString(struct String * dest, u16 item_id, u32 heap_no);
u32 GetItemAttr(u16 item, u32 attr, u32 heap_id);
u32 GetItemAttr_PreloadedItemData(struct ItemData * itemData, u32 attr);
u32 GetItemAttrSub(struct ItemDataSub * sub, u32 attr);
u16 TMHMGetMove(u16 a0);
BOOL MoveIsHM(u16 a0);
u8 ItemToTMHMId(u16 a0);
BOOL ItemIdIsMail(u16 a0);
u8 ItemToMailId(u16 item_id);
u16 MailToItemId(u8 i);
BOOL ItemIdIsBerry(u16 item_id);
u8 ItemToBerryId(u16 item_id);
u16 BerryToItemId(u8 a0);
u8 ItemIsBitter(u16 item_id);
struct ItemData * LoadAllItemData(u32 heap_id);
struct ItemData * GetItemDataPtrFromArray(struct ItemData * a0, u16 item_id);

#endif //POKEDIAMOND_ITEMTOOL_H
