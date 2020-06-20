#ifndef POKEDIAMOND_ITEMTOOL_H
#define POKEDIAMOND_ITEMTOOL_H

#include "global.h"
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

NARC * OpenNutsDataNarc(u32 heap_id);
struct NutData * ReadNutDataFromNarc(NARC * narc, u32 berry_idx, u32 heap_id);
void CloseNutsDataNarc(NARC * narc);
struct NutData * LoadNutDataSingle(s32 berry_idx, u32 heap_id);
struct NutData * LoadNutDataSingleByItemId(s32 item_id, u32 heap_id);
u32 GetNutAttr(struct NutData * nut, u32 attr);
struct String * GetNutName(u32 berry_idx, u32 heap_id);
struct String * GetNutDesc(u32 berry_idx, u32 heap_id);

#endif //POKEDIAMOND_ITEMTOOL_H
