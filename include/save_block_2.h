#ifndef POKEDIAMOND_SAVE_BLOCK_2_H
#define POKEDIAMOND_SAVE_BLOCK_2_H

#include "MATH_crc.h"
#include "player_data.h"

struct SavArrayHeader
{
    u32 id;
    u32 size;
    u32 offset;
    u16 field_C;
    u16 field_E;
};

struct SavArrayFooter
{
    u32 magic;
    u32 next;
    u32 size;
    u16 id;
    u16 crc;
};

struct SaveBlock2_Sub_20464 {
    u32 unk_0;
    u32 offset;
    u32 size;
};

struct SaveBlock2
{
    /* 0x00000 */ int unk_00000;
    /* 0x00004 */ int unk_00004;
    /* 0x00008 */ int unk_00008;
    /* 0x0000C */ int unk_0000C;
    /* 0x00010 */ int unk_00010;
    /* 0x00014 */ struct MATHCRC16Table unk_00014;
    /* 0x00214 */ u8 dynamic_region[0x20000];
    /* 0x20214 */ int unk_20214;
    /* 0x20218 */ u8 unk_20218[8];
    /* 0x20220 */ u8 unk_20220[2];
    /* 0x20222 */ u8 filler_20222[2];
    /* 0x20224 */ struct SavArrayHeader arrayHeaders[36];
    /* 0x20464 */ struct SaveBlock2_Sub_20464 unk_20464[2];
    /* 0x2047C */ u8 filler_2047C[0x28];
    /* 0x204A4 */ int unk_204A4;
    // TODO: finish this struct
}; // size: 0x204A8

void * SavArray_get(struct SaveBlock2 *, int);

#endif //POKEDIAMOND_SAVE_BLOCK_2_H
