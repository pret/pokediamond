#ifndef POKEDIAMOND_FIELDMAP_H
#define POKEDIAMOND_FIELDMAP_H

#include "save_block_2.h"

struct FieldContext
{
    u32 magic; // 0x0003643F
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    u8 unk08;
    u8 unk09;
    u16 unk0A;
    struct SaveBlock2 * unk0C;
    struct UnkStruct_0204639C * unk10;
    u8 filler_14[0xC8]; // to be identified
}; // size: 0xDC

#endif //POKEDIAMOND_FIELDMAP_H
