#ifndef POKEDIAMOND_UNK_02002F08_H
#define POKEDIAMOND_UNK_02002F08_H

#include "global.h"
#include "gf_gfx_loader.h"
#include "string16.h"


struct UnkStruct_02002F08_sub_sub {
    u16 unk00;

    u16 unk02_0: 6;
    u16 unk02_6: 5;
    u16 unk02_b: 5;

    u16 unk04_0: 15;
    u16 unk04_f: 1;

    u16 unk06_0: 4;
    u16 unk06_4: 6;
    u16 unk06_a: 6;
};

struct UnkStruct_02002F08_sub
{
    u16 *unk00;
    u16 *unk04;
    u32 unk08;
    struct UnkStruct_02002F08_sub_sub unk0c;
};

struct UnkStruct_02002F08
{
    struct UnkStruct_02002F08_sub unk000[14];

    u16 unk118_0 : 2;
    u16 unk118_2 : 14;
    u16 unk11a_0 : 14;
    u16 unk11a_e : 1;
    u16 unk11a_f : 1;
    u8 unk11c;
    u8 unk11d;
    u16 unk11e;
};

s32 FUN_02002F08(u32 param0, struct String *str, u32 param2);
u32 FUN_02002F40(u32 param0, struct String *str, u32 param2, u32 param3);
u32 FUN_02002F58(const u16 *str);
u32 FUN_02002F90(struct String *str);
s32 FUN_02002F9C(u32 param0, struct String *str);
struct UnkStruct_02002F08 *FUN_02002FD0(u32 heap_id);
void FUN_02002FEC(struct UnkStruct_02002F08 *ptr);
void FUN_02002FF4(
    struct UnkStruct_02002F08 *param0, u32 param1, void *param2, void *param3, u32 size);
void FUN_02003008(struct UnkStruct_02002F08 *param0, u32 param1, u32 size, u32 heap_id);
void FUN_02003038(struct UnkStruct_02002F08 *param0, u32 param1);
void FUN_02003054(
    struct UnkStruct_02002F08 *param0, const void *param1, u32 param2, u32 offset, u16 size);
void FUN_02003084(struct UnkStruct_02002F08 *param0,
    NarcId narcId,
    s32 memberId,
    u32 heap_id,
    u32 param4,
    u32 size,
    u16 offset,
    u16 param7);
void FUN_020030E8(struct UnkStruct_02002F08 *param0,
    NarcId narcId,
    s32 memberId,
    u32 heap_id,
    u32 param4,
    u32 size,
    u16 offset);

#endif // POKEDIAMOND_UNK_02002F08_H
