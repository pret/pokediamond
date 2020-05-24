#ifndef POKEDIAMOND_STRUCTS_H
#define POKEDIAMOND_STRUCTS_H

#include "pokemon.h"
#include "map.h"

// MATH
typedef u16 MATHCRC16Table[256];

struct UnkStruct_021C59C8_Sub20224 {
    int unk_0;
    int unk_4;
    int unk_8;
    u16 unk_C;
    u16 unk_E;
};

struct UnkStruct_021C59C8_Sub_20464 {
    u8 unk_0;
    u8 padding[3];
    int unk_4;
    int unk_8;
    u8 unk_C;
    u8 unk_D;
    u8 unk_E;
    u8 padding2;
};

struct UnkStruct_021C59C8 {
    /* 0x00000 */ int unk_00000;
    /* 0x00004 */ int unk_00004;
    /* 0x00008 */ int unk_00008;
    /* 0x0000C */ int unk_0000C;
    /* 0x00010 */ int unk_00010;
    /* 0x00014 */ MATHCRC16Table unk_00014;
    /* 0x00214 */ u8 filler_00214[0x2004];
    /* 0x20218 */ u8 unk_20218[8];
    /* 0x20220 */ int unk_20220;
    /* 0x20224 */ struct UnkStruct_021C59C8_Sub20224 unk_20224[36];
    /* 0x20464 */ struct UnkStruct_021C59C8_Sub_20464 unk_20464[4];
    /* 0x204A4 */ int unk_204A4;
};

#endif //POKEDIAMOND_STRUCTS_H
