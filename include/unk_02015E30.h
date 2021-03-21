#ifndef POKEDIAMOND_UNK_02015E30_H
#define POKEDIAMOND_UNK_02015E30_H

#include "global.h"
#include "igt.h"

struct UnkStruct_02015E30
{
    u32 unk00;
    struct IGT *unk04;
    u64 unk08;
    u32 unk10;
    u32 unk14;
    u64 unk18;
};

THUMB_FUNC void FUN_02015E30();
THUMB_FUNC void FUN_02015E3C(struct IGT *igt);
THUMB_FUNC void FUN_02015E60();

#endif //POKEDIAMOND_UNK_02015E30_H
