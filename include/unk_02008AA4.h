#ifndef POKEDIAMOND_UNK_02008AA4_H
#define POKEDIAMOND_UNK_02008AA4_H

#include "global.h"
#include "unk_0200BB14.h"

struct UnkStruct_02008AA4_1
{
    struct UnkStruct_0200BB14_sub *unk00;
    s32 unk04;
};

struct UnkStruct_02008AA4_2
{
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    u32 unk18;
    u32 unk1C;
};

void FUN_02008AA4(struct UnkStruct_0200BB14_sub *param0,
    s32 param1,
    s32 param2,
    s32 param3,
    s32 param4,
    s32 param5,
    s32 param6,
    u32 param7,
    u32 param8,
    u32 param9,
    u32 param10,
    u32 param11,
    u32 param12,
    u32 param13,
    u32 param14);
struct UnkStruct_02008AA4_1 *FUN_02008BE0(struct UnkStruct_02008AA4_2 *param0,
    u32 param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7);
void FUN_02008C80(struct UnkStruct_02008AA4_1 *param0);
u32 FUN_02008C9C(u32 param0, void *param1, u32 param2);
void FUN_02008D04(u32 param0, u32 param1, u32 param2);
void FUN_02008D24(u32 param0, u32 param1, u32 param2);
void FUN_02008D44(u32 param0, u32 param1);
void FUN_02008DDC(u32 param0);

#endif // POKEDIAMOND_UNK_02008AA4_H
