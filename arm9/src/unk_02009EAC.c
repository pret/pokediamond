#include "global.h"
#include "unk_02009EAC.h"
#include "GX_g2.h"
#include "MI_memory.h"
#include "heap.h"


extern void FUN_020213A0(void);
extern void FUN_0202135C(void *param0,
    u32 *param1,
    u32 (*param2)(u32, u32),
    u32 (*param3)(u32),
    void (*param4)(void),
    u32 param5,
    u32 param6);
extern void FUN_020203CC(u32 heap_id);
extern void FUN_02020404(u32 heap_id);

struct UnkStruct_02009EAC *UNK_021C4670;

THUMB_FUNC void FUN_02009EAC(s32 param0,
    s32 param1,
    s32 param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    u32 param8)
{
    s32 r0;
    if (param0 < 4)
    {
        r0 = 4;
        if (param1 > 0x7c)
        {
            param1 = param1 - (4 - param0);
        }
    }
    else
    {
        r0 = param0;
    }

    s32 r2;
    if (param2 < 1)
    {
        r2 = 1;
        if (param3 > 0x1e)
        {
            param3 = param3 - (1 - param2);
        }
    }
    else
    {
        r2 = param2;
    }

    FUN_02009EF0(r0, param1, r2, param3, param4, param5, param6, param7, param8);
}

THUMB_FUNC void FUN_02009EF0(u32 param0,
    u32 param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    u32 param8)
{
    GF_ASSERT(UNK_021C4670 == NULL);
    UNK_021C4670 = AllocFromHeap(param8, sizeof(struct UnkStruct_02009EAC));
    GF_ASSERT(UNK_021C4670);

    UNK_021C4670->heap_id = param8;

    GF_ASSERT(NNS_G2dGetNewOamManagerInstance(
        &UNK_021C4670->oamManagers[0], param0, param1, param2, param3, 0));
    GF_ASSERT(NNS_G2dGetNewOamManagerInstance(
        &UNK_021C4670->oamManagers[1], param4, param5, param6, param7, 1));
}

THUMB_FUNC void FUN_02009F80(void)
{
    if (UNK_021C4670 != NULL)
    {
        NNS_G2dApplyAndResetOamManagerBuffer(&UNK_021C4670->oamManagers[0]);
        NNS_G2dApplyAndResetOamManagerBuffer(&UNK_021C4670->oamManagers[1]);
    }
}

THUMB_FUNC void FUN_02009FA0(void)
{
    GF_ASSERT(UNK_021C4670);

    FUN_0200A064(UNK_021C4670->heap_id);
    FUN_0200A06C(UNK_021C4670->heap_id);

    FreeToHeap(UNK_021C4670);
    UNK_021C4670 = NULL;
}

THUMB_FUNC void FUN_02009FD8(void *param0, u32 *param1, u32 param2, u32 param3)
{
    GF_ASSERT(UNK_021C4670);

    if (param2 == 1)
    {
        FUN_0202135C(param0, param1, FUN_0200A074, FUN_0200A0B8, FUN_020213A0, param2, param3);
        return;
    }

    FUN_0202135C(param0, param1, FUN_0200A094, FUN_0200A0DC, FUN_020213A0, param2, param3);
}

THUMB_FUNC NNSG2dOamManager *FUN_0200A03C(u32 param0)
{
    GF_ASSERT(UNK_021C4670);
    if (param0 == 0)
    {
        return &UNK_021C4670->oamManagers[0];
    }
    else
    {
        return &UNK_021C4670->oamManagers[1];
    }
}

THUMB_FUNC void FUN_0200A064(u32 heap_id)
{
    FUN_020203CC(heap_id);
}

THUMB_FUNC void FUN_0200A06C(u32 heap_id)
{
    FUN_02020404(heap_id);
}

THUMB_FUNC u32 FUN_0200A074(u32 param0, u32 param1)
{
    u32 res = NNS_G2dEntryOamManagerOamWithAffineIdx(&UNK_021C4670->oamManagers[0], param0, param1);
    GF_ASSERT(res);

    return res;
}

THUMB_FUNC u32 FUN_0200A094(u32 param0, u32 param1)
{
    u32 res = NNS_G2dEntryOamManagerOamWithAffineIdx(&UNK_021C4670->oamManagers[1], param0, param1);
    GF_ASSERT(res);

    return res;
}

THUMB_FUNC u32 FUN_0200A0B8(u32 param0)
{
    u32 res = NNS_G2dEntryOamManagerAffine(&UNK_021C4670->oamManagers[0], param0);
    GF_ASSERT(res != 0xFFFE);

    return res;
}

THUMB_FUNC u32 FUN_0200A0DC(u32 param0)
{
    u32 res = NNS_G2dEntryOamManagerAffine(&UNK_021C4670->oamManagers[1], param0);
    GF_ASSERT(res != 0xFFFE);

    return res;
}
