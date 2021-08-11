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
    struct UnkStruct1 *param9,
    struct UnkStruct1 *param10,
    struct UnkStruct1 *param11,
    struct UnkStruct1 *param12,
    struct UnkStruct1 *param13,
    struct UnkStruct1 *param14);
struct UnkStruct_02008AA4_1 *FUN_02008BE0(struct UnkStruct_02008AA4_2 *param0,
    u32 param1,
    struct UnkStruct1 *param2,
    struct UnkStruct1 *param3,
    struct UnkStruct1 *param4,
    struct UnkStruct1 *param5,
    struct UnkStruct1 *param6,
    struct UnkStruct1 *param7);
void FUN_02008C80(struct UnkStruct_02008AA4_1 *param0);
u32 FUN_02008C9C(u32 param0, void *param1, u32 param2);
void FUN_02008D04(u32 param0, u32 param1, u32 param2);
void FUN_02008D24(u32 param0, u32 param1, u32 param2);
void FUN_02008D44(u32 param0, u32 param1);
void FUN_02008DDC(u32 param0);

#endif // POKEDIAMOND_UNK_02008AA4_H
