#include "global.h"
#include "heap.h"
#include "unk_0208A300.h"

struct UnkStruct_0208A300* FUN_0208A300(u32 heap_id)
{
    struct UnkStruct_0208A300* ret = AllocFromHeap(heap_id, sizeof(struct UnkStruct_0208A300));

    __builtin__clear(ret, sizeof(struct UnkStruct_0208A300));
    ret->unk4 = 2;

    return ret;
}

void FUN_0208A320(struct UnkStruct_0208A300* unk)
{
    FreeToHeap(unk);
}

u32 FUN_0208A328(struct UnkStruct_0208A300* unk)
{
    return unk->unk0;
}

void FUN_0208A32C(struct UnkStruct_0208A300* unk, u32 a1)
{
    unk->unk0 = a1;
}

u32 FUN_0208A330(struct UnkStruct_0208A300* unk)
{
    return unk->unk4;
}

void FUN_0208A334(struct UnkStruct_0208A300* unk, u32 a1)
{
    unk->unk4 = a1;
}
