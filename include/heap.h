#ifndef POKEDIAMOND_HEAP_H
#define POKEDIAMOND_HEAP_H

#include "global.h"

struct UnkStruct_020166C8
{
    u32 *unk_ptr1;
    u32 *unk_ptr2;
    void **unk_ptr3;
    u16 *unk_ptr4;
    u8 *unk_ptr5;
    u16 unk_half1;
    u16 unk_half2;
    u16 unk_half3;
    u16 unk_half4;
};


THUMB_FUNC void FUN_020166C8(u32 *param0, u32 param1, u32 param2, u32 pre_size);
THUMB_FUNC s32 FUN_020167F4();
THUMB_FUNC u32 FUN_0201681C(u32 param0, u32 heap_id, u32 param2);
THUMB_FUNC u32 FUN_02016828(u32 param0, u32 param1, u32 param2);
THUMB_FUNC u32 FUN_02016834(u32 param0, u32 param1, u32 param2, s32 param3);
THUMB_FUNC void FUN_020168D0(u32 heap_id);
THUMB_FUNC u32 FUN_02016944(void *param0, u32 param1, u32 param2, u32 param3);
THUMB_FUNC void FUN_02016988();
void *AllocFromHeap(u32 heap_id, u32 size);
void *AllocFromHeapAtEnd(u32 heap_id, u32 size);
void FreeToHeap(void *ptr);
void FUN_02016A8C(u32 heap_id, void * ptr);
THUMB_FUNC u32 FUN_02016AF8(u32 param0);
THUMB_FUNC void FUN_02016B20(u32 param0, u32 param1, u32 param2);
THUMB_FUNC void FUN_02016B44(void *ptr, u32 param1);
THUMB_FUNC u32 FUN_02016B90(u32 param0);

#endif //POKEDIAMOND_HEAP_H
