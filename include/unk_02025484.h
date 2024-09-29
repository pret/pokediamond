#ifndef POKEDIAMOND_UNK_02025484_H
#define POKEDIAMOND_UNK_02025484_H

#include "nitro/types.h"

struct unk_2025484 {
    // size: 0x24
    u32 unk0;
    u32 unk4;
    u8 padding[0x1C];
};

void sub_02025484(struct unk_2025484 *r0);
u32 *sub_02025490(struct unk_2025484 *r0, u32 r1);
u32 *sub_020254A0(struct unk_2025484 *r0, u32 r1);
u32 sub_020254B4(struct unk_2025484 *r0);

#endif POKEDIAMOND_UNK_02025484_H
