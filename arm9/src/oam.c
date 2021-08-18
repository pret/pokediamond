#include "global.h"
#include "oam.h"
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

struct OamData *oamData;

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

    InitOamData(r0, param1, r2, param3, param4, param5, param6, param7, param8);
}

THUMB_FUNC void InitOamData(s32 param0,
    s32 param1,
    s32 param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    u32 heap_id)
{
    GF_ASSERT(oamData == NULL);
    oamData = AllocFromHeap(heap_id, sizeof(struct OamData));
    GF_ASSERT(oamData);

    oamData->heap_id = heap_id;

    GF_ASSERT(NNS_G2dGetNewOamManagerInstance(
        &oamData->oamManagers[0], (u16)param0, (u16)param1, (u16)param2, (u16)param3, 0));
    GF_ASSERT(NNS_G2dGetNewOamManagerInstance(
        &oamData->oamManagers[1], (u16)param4, (u16)param5, (u16)param6, (u16)param7, 1));
}

THUMB_FUNC void ApplyAndResetOamManagerBuffer(void)
{
    if (oamData != NULL)
    {
        NNS_G2dApplyAndResetOamManagerBuffer(&oamData->oamManagers[0]);
        NNS_G2dApplyAndResetOamManagerBuffer(&oamData->oamManagers[1]);
    }
}

THUMB_FUNC void DeinitOamData(void)
{
    GF_ASSERT(oamData);

    FUN_0200A064(oamData->heap_id);
    FUN_0200A06C(oamData->heap_id);

    FreeToHeap(oamData);
    oamData = NULL;
}

THUMB_FUNC void FUN_02009FD8(void *param0, u32 *param1, u32 param2, u32 param3)
{
    GF_ASSERT(oamData);

    if (param2 == 1)
    {
        FUN_0202135C(param0, param1, EntryOamManagerOamWithAffineIdxMainScreen, EntryOamManagerAffineMainScreen, FUN_020213A0, param2, param3);
        return;
    }

    FUN_0202135C(param0, param1, EntryOamManagerOamWithAffineIdxSubScreen, EntryOamManagerAffineSubScreen, FUN_020213A0, param2, param3);
}

THUMB_FUNC NNSG2dOamManager *GetOamManager(u32 screen)
{
    GF_ASSERT(oamData);
    if (screen == 0)
    {
        return &oamData->oamManagers[0];
    }
    else
    {
        return &oamData->oamManagers[1];
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

THUMB_FUNC u32 EntryOamManagerOamWithAffineIdxMainScreen(u32 param0, u32 param1)
{
    u32 res = NNS_G2dEntryOamManagerOamWithAffineIdx(&oamData->oamManagers[0], param0, param1);
    GF_ASSERT(res);

    return res;
}

THUMB_FUNC u32 EntryOamManagerOamWithAffineIdxSubScreen(u32 param0, u32 param1)
{
    u32 res = NNS_G2dEntryOamManagerOamWithAffineIdx(&oamData->oamManagers[1], param0, param1);
    GF_ASSERT(res);

    return res;
}

THUMB_FUNC u32 EntryOamManagerAffineMainScreen(u32 param0)
{
    u32 res = NNS_G2dEntryOamManagerAffine(&oamData->oamManagers[0], param0);
    GF_ASSERT(res != 0xFFFE);

    return res;
}

THUMB_FUNC u32 EntryOamManagerAffineSubScreen(u32 param0)
{
    u32 res = NNS_G2dEntryOamManagerAffine(&oamData->oamManagers[1], param0);
    GF_ASSERT(res != 0xFFFE);

    return res;
}
