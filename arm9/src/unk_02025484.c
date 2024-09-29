#include "unk_02025484.h"

#include "global.h"

#include "MI_memory.h"
#include "error_handling.h"

void sub_02025484(struct unk_2025484 *r0) {
    MI_CpuFill8(r0, 0, sizeof(struct unk_2025484));
}

u32 *sub_02025490(struct unk_2025484 *r0, u32 r1) {
    sub_02025484(r0);
    r0->unk0 = r1;
    return &r0->unk4;
}

u32 *sub_020254A0(struct unk_2025484 *r0, u32 r1) {
    GF_ASSERT(r0->unk0 == r1);
    return &r0->unk4;
}

u32 sub_020254B4(struct unk_2025484 *r0) {
    return r0->unk0;
}
