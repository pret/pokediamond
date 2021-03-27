#include "global.h"
#include "MI_memory.h"
#include "error_handling.h"
#include "unk_02025484.h"

THUMB_FUNC void FUN_02025484(struct unk_2025484 *r0, u32 r1)
{
    MI_CpuFill8(r0, 0, sizeof(struct unk_2025484));
}

THUMB_FUNC u32 *FUN_02025490(struct unk_2025484 *r0, u32 r1)
{
    FUN_02025484(r0, r1);
    r0->unk0 = r1;
    return &r0->unk4;
}

THUMB_FUNC u32 *FUN_020254A0(struct unk_2025484 *r0, u32 r1)
{
    GF_ASSERT(r0->unk0 == r1);
    return &r0->unk4;
}

THUMB_FUNC u32 FUN_020254B4(struct unk_2025484 *r0)
{
    return r0->unk0;
}
