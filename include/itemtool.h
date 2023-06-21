#ifndef POKEDIAMOND_ITEMTOOL_H
#define POKEDIAMOND_ITEMTOOL_H

#include "global.h"
#include "filesystem.h"
#include "string16.h"
#include "constants/items.h"

#define ITEMDATA_DATA 0
#define ITEMDATA_NCGR 1
#define ITEMDATA_NCLR 2
#define ITEMDATA_3TO4 3

// Berries (nutdata)

struct ItemSlot
{
    u16 id;
    u16 quantity;
};

struct ItemPartyUseParam
{
    u8 slp_heal:1;
    u8 psn_heal:1;
    u8 brn_heal:1;
    u8 frz_heal:1;
    u8 prz_heal:1;
    u8 cfs_heal:1;
    u8 inf_heal:1;
    u8 guard_spec:1;
    u8 revive:1;
    u8 revive_all:1;
    u8 level_up:1;
    u8 evolve:1;
    u8 atk_stages:4;
    u8 def_stages:4;
    u8 spatk_stages:4;
    u8 spdef_stages:4;
    u8 speed_stages:4;
    u8 accuracy_stages:4;
    u8 critrate_stages:2;
    u8 pp_up:1;
    u8 pp_max:1;
    u8 pp_restore:1;
    u8 pp_restore_all:1;
    u8 hp_restore:1;
    u8 hp_ev_up:1;
    u8 atk_ev_up:1;
    u8 def_ev_up:1;
    u8 speed_ev_up:1;
    u8 spatk_ev_up:1;
    u8 spdef_ev_up:1;
    u8 friendship_mod_lo:1;
    u8 friendship_mod_med:1;
    u8 friendship_mod_hi:1;
    s8 hp_ev_up_param;
    s8 atk_ev_up_param;
    s8 def_ev_up_param;
    s8 speed_ev_up_param;
    s8 spatk_ev_up_param;
    s8 spdef_ev_up_param;
    u8 hp_restore_param;
    u8 pp_restore_param;
    s8 friendship_mod_lo_param;
    s8 friendship_mod_med_param;
    s8 friendship_mod_hi_param;
    u8 paddding[2];
};

struct ItemData
{
    u16 price;
    u8 holdEffect;
    u8 holdEffectParam;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 naturalGiftPower;
    u16 naturalGiftType:5;
    u16 prevent_toss:1;
    u16 selectable:1;
    u16 pocket:4;
    u16 unk8_B:5;
    u8 unkA;
    u8 unkB;
    u8 partyUse;
    u8 padding_0D;
    union {
        u8 flat;
        struct ItemPartyUseParam sub;
    } partyUseParam;
    u8 padding_22[2];
};

void MoveItemSlotInList(struct ItemSlot * itemSlots, u16 from, u16 to);
u16 GetItemIndexMapping(u16 a0, u16 a1);
u16 UpConvertItemId_Gen3to4(u16 a0);
int sub_0206E708();
int sub_0206E70C();
void * LoadItemDataOrGfx(u16 itemId, u16 which, u32 heap_id);
void GetItemNameIntoString(struct String * dest, u16 item_id, u32 heap_no);
void GetItemDescIntoString(struct String * dest, u16 item_id, u32 heap_no);
u32 GetItemAttr(u16 item, u32 attr, u32 heap_id);
u32 GetItemAttr_PreloadedItemData(struct ItemData * itemData, u32 attr);
u32 GetItemAttrSub(struct ItemPartyUseParam * sub, u32 attr);
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
