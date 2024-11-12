#ifndef POKEDIAMOND_UNK_02006D98_H
#define POKEDIAMOND_UNK_02006D98_H

#include "global.h"

#include "NNS_g2d.h"
#include "heap.h"

struct UnkStruct_02006D98_4 {
    u16 field_00;
    u16 field_02;
    u16 field_04;
    u16 field_06;
    u32 field_08;
    u32 field_0C;
};

struct UnkStruct_02006D98_sub {
    s8 unk0;
    u8 unk1;
};
struct UnkStruct_02006D98_sub2 {
    u16 unk0_0 : 2;
    u16 unk0_2 : 1;
    u16 unk0_3 : 1;
    u16 unk0_4 : 1;
    u16 unk0_5 : 2;
    s8 unk2;
    u8 unk3;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unka;
};

struct UnkStruct_02006D98_2 {
    u32 unk00_0 : 1;
    u32 unk00_1 : 6;
    u32 unk00_7 : 1;
    u32 unk00_8 : 1;
    struct UnkStruct_02006D98_4 unk04;
    struct UnkStruct_02006D98_4 unk14;
    s16 unk24;
    s16 unk26;
    u32 unk28;
    s16 unk2C;
    s16 unk2E;
    u32 unk30;
    s16 unk34;
    s16 unk36;
    u16 unk38;
    u16 unk3A;
    u16 unk3C;
    u16 unk3E;
    s16 unk40;
    s16 unk42;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u32 unk4C;
    u32 unk50_0 : 5;
    u32 unk50_5 : 5;
    u32 unk50_a : 5;
    u32 unk50_f : 5;
    u32 unk50_14 : 5;
    u32 unk50_19 : 5;
    u32 unk50_1E : 2;
    u32 unk54_0 : 1;
    u32 unk54_1 : 1;
    u32 unk54_2 : 5;
    u32 unk54_7 : 2;
    u32 unk54_9 : 1;
    u32 unk54_A : 1;
    u32 unk54_B : 1;
    u32 unk54_C : 1;
    u32 unk54_D : 4;
    u8 unk58;
    u8 unk59;
    u8 unk5A;
    u8 unk5B;
    u8 unk5C[10];
    void (*unk68)(struct UnkStruct_02006D98_2 *, void *);
    struct UnkStruct_02006D98_sub2 unk6C;
    struct UnkStruct_02006D98_sub2 unk78;
    struct UnkStruct_02006D98_sub unk84[10];
};

struct UnkStruct_02006D98 {
    struct UnkStruct_02006D98_2 unk000[4];
    NNSG2dImageProxy unk260;
    NNSG2dImagePaletteProxy unk284;
    HeapID heapId;
    u32 unk29C;
    u32 unk2A0;
    u32 unk2A4;
    u32 unk2A8;
    u8 *unk2AC;
    u16 *unk2B0;
    u16 *unk2B4;
    NNSG2dCharacterData unk2B8;
    NNSG2dPaletteData unk2D0;
    u8 unk2E0;
    u8 unk2E1;
    u8 unk2E2;
    u8 unk2E3;
    u32 unk2E4;
};

struct UnkStruct_02006D98_3 {
    u8 unk0;
    u8 unk1;
};

struct UnkStruct_02006D98_5 {
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    u8 unk04[10];
    struct UnkStruct_02006D98_sub *unk10;
};

struct UnkStruct_02006D98 *sub_02006D98(HeapID heapId);
void sub_02006ED4(struct UnkStruct_02006D98 *param0);
void sub_020072E8(struct UnkStruct_02006D98 *param0);
void sub_02007314(struct UnkStruct_02006D98_2 *param0);
void sub_0200737C(struct UnkStruct_02006D98_2 *param0, struct UnkStruct_02006D98_sub *param1);
BOOL sub_02007390(struct UnkStruct_02006D98_2 *param0);
struct UnkStruct_02006D98_2 *sub_020073A0(struct UnkStruct_02006D98 *param0,
    struct UnkStruct_02006D98_4 *param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    const void *param6,
    void (*param7)(struct UnkStruct_02006D98_2 *, void *));
struct UnkStruct_02006D98_2 *sub_020073E8(struct UnkStruct_02006D98 *param0,
    struct UnkStruct_02006D98_4 *param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    s32 param6,
    const void *param7,
    void (*param8)(struct UnkStruct_02006D98_2 *, void *));
void sub_02007534(struct UnkStruct_02006D98_2 *param0);
void sub_02007540(struct UnkStruct_02006D98 *param0);
void sub_02007558(struct UnkStruct_02006D98_2 *param0, u32 param1, u32 param2);
u32 sub_0200782C(struct UnkStruct_02006D98_2 *param0, u32 param1);
void sub_020079E0(struct UnkStruct_02006D98_2 *param0, u32 param1, u32 param2);
void sub_02007E40(
    struct UnkStruct_02006D98_2 *param0, u32 param1, u32 param2, u32 param3, u32 param4);
void sub_02007E68(
    struct UnkStruct_02006D98_2 *param0, u32 param1, u32 param2, u32 param3, u32 param4);
void sub_02007E98(
    struct UnkStruct_02006D98 *param0, u32 param1, u32 param2, u32 param3, u32 param4);
void sub_02007EEC(struct UnkStruct_02006D98_2 *param0);
BOOL sub_02007F20(struct UnkStruct_02006D98_2 *param0);
void sub_02007F34(struct UnkStruct_02006D98_2 *param0, s32 param1);
void sub_02007F48(struct UnkStruct_02006D98_2 *param0);
void sub_02008010(struct UnkStruct_02006D98_5 *param0, struct UnkStruct_02006D98_sub *param1);
s32 sub_02008030(struct UnkStruct_02006D98_5 *param0);
void sub_020080D0(struct UnkStruct_02006D98_2 *param0);
void sub_020080E0(struct UnkStruct_02006D98_2 *param0);
void sub_0200813C(struct UnkStruct_02006D98_2 *param0);
void sub_020081A8(struct UnkStruct_02006D98 *param0, u32 param1, u32 param2);
void sub_020081B4(struct UnkStruct_02006D98 *param0, u32 param1, u32 param2);
u32 sub_020081C0(u32 param0);
void sub_020081C4(struct UnkStruct_02006D98 *param0);
void sub_0200825C(struct UnkStruct_02006D98 *param0, u8 param1);
BOOL sub_02008268(struct UnkStruct_02006D98_2 *param0);
void sub_02008284(struct UnkStruct_02006D98 *param0, u32 param1);
void sub_02008290(struct UnkStruct_02006D98 *param0, u32 param1);
void sub_020082A8(struct UnkStruct_02006D98 *param0);
void sub_020086F4(struct UnkStruct_02006D98 *param0);
u8 sub_020088D8(u8 param0);
void sub_020088EC(struct UnkStruct_02006D98_2 *param0, u8 *param1);
void sub_02008904(u8 *param0, u32 param1, u32 param2);
u16 sub_02008A54(u32 *param0);
void sub_02008A74(u8 *param0);

#endif // POKEDIAMOND_UNK_02006D98_H
