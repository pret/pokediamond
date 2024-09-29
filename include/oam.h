#ifndef POKEDIAMOND_UNK_02009EAC_H
#define POKEDIAMOND_UNK_02009EAC_H

#include "global.h"

#include "NNS_g2d.h"
#include "heap.h"

struct OamData {
    NNSG2dOamManager oamManagers[2];
    HeapID heapId;
};

void sub_02009EAC(s32 param0,
    s32 param1,
    s32 param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    HeapID heapId);
void InitOamData(s32 param0,
    s32 param1,
    s32 param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    HeapID heapId);
void ApplyAndResetOamManagerBuffer(void);
void DeinitOamData(void);
void sub_02009FD8(void *param0, u32 *param1, u32 param2, u32 param3);
NNSG2dOamManager *GetOamManager(u32 screen);
void sub_0200A064(HeapID heapId);
void sub_0200A06C(HeapID heapId);
u32 EntryOamManagerOamWithAffineIdxMainScreen(u32 param0, u32 param1);
u32 EntryOamManagerOamWithAffineIdxSubScreen(u32 param0, u32 param1);
u32 EntryOamManagerAffineMainScreen(u32 param0);
u32 EntryOamManagerAffineSubScreen(u32 param0);

#endif // POKEDIAMOND_UNK_02009EAC_H
