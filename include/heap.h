#ifndef POKEDIAMOND_HEAP_H
#define POKEDIAMOND_HEAP_H

#include "global.h"

struct UnkStruct_020166C8
{
    void **unk00;
    void **unk04;
    void **unk08;
    u16 *unk0c;
    u8 *unk10;
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1a;
};


void FUN_020166C8(u32 *param0, u32 param1, u32 param2, u32 pre_size);
s32 FUN_020167F4();
u32 FUN_0201681C(u32 param0, u32 heap_id, u32 param2);
u32 FUN_02016828(u32 param0, u32 param1, u32 param2);
u32 FUN_02016834(u32 param0, u32 param1, u32 param2, s32 param3);
void FUN_020168D0(u32 heap_id);
u32 *FUN_02016944(void *param0, u32 param1, s32 param2, u32 param3);
void FUN_02016988();
void *AllocFromHeap(u32 heap_id, u32 size);
void *AllocFromHeapAtEnd(u32 heap_id, u32 size);
void FreeToHeap(void *ptr);
void FreeToHeapExplicit(u32 heap_id, void * ptr);
u32 FUN_02016AF8(u32 param0);
void FUN_02016B20(u32 param0, u32 param1, u32 param2);
void FUN_02016B44(void *ptr, u32 param1);
u32 FUN_02016B90(u32 param0);

#endif //POKEDIAMOND_HEAP_H
