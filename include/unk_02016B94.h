#ifndef POKEDIAMOND_UNK_02016B94_H
#define POKEDIAMOND_UNK_02016B94_H


#include "global.h"
#include "GX_layers.h"
#include "gx.h"
#include "heap.h"
#include "math_util.h"
#include "MI_uncompress.h"
#include "OS_cache.h"

struct UnkStruct1 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;

    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17; //probably paddding
    u32 unk18;
};



struct UnkStruct2 {
    u32 unk00;
    u16 unk04;
    u16 unk06;


    struct InnerStruct {
        void *unk08;
        u32 unk0c;
        u32 unk10;

        u32 unk14;
        u32 unk18;

        u8 unk1c;
        u8 unk1d;
        u8 unk1e;
        u8 unk1f;
        u16 unk20;
        u16 unk22; //probably padding
        u32 unk24;
        u32 unk28;
        u32 unk2c;
        u32 unk30;
    } unk08[8];
};


THUMB_FUNC void *FUN_02016B94(u32 heap_id);
THUMB_FUNC u32 FUN_02016BB8(u32 *param0);
THUMB_FUNC void FUN_02016BBC(u32 *param0);
THUMB_FUNC void FUN_02016BF4(u32 *param0, u32 param1);
THUMB_FUNC void FUN_02016C18(struct UnkStruct2 *param0, u8 param1, struct UnkStruct1 *param2, u8 param3);




#endif //POKEDIAMOND_UNK_02016B94_H
