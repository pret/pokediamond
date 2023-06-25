#include "global.h"
#include "oam.h"
#include "GX_g2.h"
#include "MI_memory.h"
#include "heap.h"

extern void sub_020213A0(void);
extern void sub_0202135C(void *param0,
    u32 *param1,
    u32 (*param2)(u32, u32),
    u32 (*param3)(u32),
    void (*param4)(void),
    u32 param5,
    u32 param6);
extern void sub_020203CC(HeapID heapId);
extern void sub_02020404(HeapID heapId);

struct OamData *oamData;

void sub_02009EAC(s32 param0,
    s32 param1,
    s32 param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    HeapID heapId)
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

    InitOamData(r0, param1, r2, param3, param4, param5, param6, param7, heapId);
}

void InitOamData(s32 param0,
    s32 param1,
    s32 param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    HeapID heapId)
{
    GF_ASSERT(oamData == NULL);
    oamData = AllocFromHeap(heapId, sizeof(struct OamData));
    GF_ASSERT(oamData);

    oamData->heapId = heapId;

    GF_ASSERT(NNS_G2dGetNewOamManagerInstance(
        &oamData->oamManagers[0], (u16)param0, (u16)param1, (u16)param2, (u16)param3, 0));
    GF_ASSERT(NNS_G2dGetNewOamManagerInstance(
        &oamData->oamManagers[1], (u16)param4, (u16)param5, (u16)param6, (u16)param7, 1));
}

void ApplyAndResetOamManagerBuffer(void)
{
    if (oamData != NULL)
    {
        NNS_G2dApplyAndResetOamManagerBuffer(&oamData->oamManagers[0]);
        NNS_G2dApplyAndResetOamManagerBuffer(&oamData->oamManagers[1]);
    }
}

void DeinitOamData(void)
{
    GF_ASSERT(oamData);

    sub_0200A064(oamData->heapId);
    sub_0200A06C(oamData->heapId);

    FreeToHeap(oamData);
    oamData = NULL;
}

void sub_02009FD8(void *param0, u32 *param1, u32 param2, u32 param3)
{
    GF_ASSERT(oamData);

    if (param2 == 1)
    {
        sub_0202135C(param0, param1, EntryOamManagerOamWithAffineIdxMainScreen, EntryOamManagerAffineMainScreen, sub_020213A0, param2, param3);
        return;
    }

    sub_0202135C(param0, param1, EntryOamManagerOamWithAffineIdxSubScreen, EntryOamManagerAffineSubScreen, sub_020213A0, param2, param3);
}

NNSG2dOamManager *GetOamManager(u32 screen)
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

void sub_0200A064(HeapID heapId)
{
    sub_020203CC(heapId);
}

void sub_0200A06C(HeapID heapId)
{
    sub_02020404(heapId);
}

u32 EntryOamManagerOamWithAffineIdxMainScreen(u32 param0, u32 param1)
{
    u32 res = NNS_G2dEntryOamManagerOamWithAffineIdx(&oamData->oamManagers[0], param0, param1);
    GF_ASSERT(res);

    return res;
}

u32 EntryOamManagerOamWithAffineIdxSubScreen(u32 param0, u32 param1)
{
    u32 res = NNS_G2dEntryOamManagerOamWithAffineIdx(&oamData->oamManagers[1], param0, param1);
    GF_ASSERT(res);

    return res;
}

u32 EntryOamManagerAffineMainScreen(u32 param0)
{
    u32 res = NNS_G2dEntryOamManagerAffine(&oamData->oamManagers[0], param0);
    GF_ASSERT(res != 0xFFFE);

    return res;
}

u32 EntryOamManagerAffineSubScreen(u32 param0)
{
    u32 res = NNS_G2dEntryOamManagerAffine(&oamData->oamManagers[1], param0);
    GF_ASSERT(res != 0xFFFE);

    return res;
}
