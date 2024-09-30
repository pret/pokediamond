#ifndef POKEDIAMOND_UNK_02021FF8_H
#define POKEDIAMOND_UNK_02021FF8_H

#include "nitro/types.h"

#include "heap.h"

struct UnkStruct_020220C4_sub {
    u8 field_0;
    u8 field_1;
    u16 field_2;
};

struct UnkStruct_020220C4 {
    u8 *field_0;
    u32 field_4;
    void (*field_8)(s32, s32, u32);
    u32 field_C;
    struct UnkStruct_020220C4_sub *field_10;
};

struct UnkStruct_020220C4 *sub_020220C4(u8 *a0, u32 a1, void (*a2)(s32, s32, u32), u32 a3, HeapID heapId);
void sub_02022120(struct UnkStruct_020220C4_sub *sub);
void sub_0202212C(struct UnkStruct_020220C4 *unk);
void sub_02022144(struct UnkStruct_020220C4 *unk);
s32 sub_020221EC(struct UnkStruct_020220C4_sub *a0, u32 a1, u32 a2);
s32 sub_02022208(struct UnkStruct_020220C4_sub *a0, u32 a1, u32 a2);
void sub_0202223C(struct UnkStruct_020220C4_sub *a0, u8 a1);

#endif // POKEDIAMOND_UNK_02021FF8_H
