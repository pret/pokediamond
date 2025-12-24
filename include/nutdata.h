#ifndef POKEDIAMOND_NUTDATA_H
#define POKEDIAMOND_NUTDATA_H

#include "filesystem.h"

#define FIRMNESS_VERY_SOFT  1
#define FIRMNESS_SOFT       2
#define FIRMNESS_HARD       3
#define FIRMNESS_VERY_HARD  4
#define FIRMNESS_SUPER_HARD 5

struct NutData {
    u16 size;
    u8 firmness;
    u8 yieldCategory;
    u8 stageDuration;
    u8 unk5;
    u8 spicy;
    u8 dry;
    u8 sweet;
    u8 bitter;
    u8 sour;
    u8 smoothness;
};

NARC *OpenNutsDataNarc(enum HeapID heapID);
struct NutData *ReadNutDataFromNarc(NARC *narc, u32 berry_idx, enum HeapID heapID);
void CloseNutsDataNarc(NARC *narc);
struct NutData *LoadNutDataSingle(s32 berry_idx, enum HeapID heapID);
struct NutData *LoadNutDataSingleByItemId(s32 item_id, enum HeapID heapID);
u32 GetNutAttr(struct NutData *nut, u32 attr);
struct String *GetNutName(u32 berry_idx, enum HeapID heapID);
struct String *GetNutDesc(u32 berry_idx, enum HeapID heapID);

#endif // POKEDIAMOND_NUTDATA_H
