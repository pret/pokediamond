#ifndef POKEDIAMOND_UNK_0208A300_H
#define POKEDIAMOND_UNK_0208A300_H

#include "nitro/types.h"

#include "heap.h"

struct UnkStruct_0208A300 {
    u32 unk0;
    u32 unk4;
};

struct UnkStruct_0208A300 *sub_0208A300(HeapID heapId);
void sub_0208A320(struct UnkStruct_0208A300 *unk);
u32 sub_0208A328(struct UnkStruct_0208A300 *unk);
void sub_0208A32C(struct UnkStruct_0208A300 *unk, u32 a1);
u32 sub_0208A330(struct UnkStruct_0208A300 *unk);
void sub_0208A334(struct UnkStruct_0208A300 *unk, u32 a1);

#endif
