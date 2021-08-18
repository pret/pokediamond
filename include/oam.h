#ifndef POKEDIAMOND_UNK_02009EAC_H
#define POKEDIAMOND_UNK_02009EAC_H

#include "global.h"
#include "NNS_g2d.h"

struct OamData
{
    NNSG2dOamManager oamManagers[2];
    u32 heap_id;
};

void FUN_02009EAC(s32 param0,
    s32 param1,
    s32 param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    u32 param8);
void InitOamData(s32 param0,
    s32 param1,
    s32 param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    u32 heap_id);
void ApplyAndResetOamManagerBuffer(void);
void DeinitOamData(void);
void FUN_02009FD8(void *param0, u32 *param1, u32 param2, u32 param3);
NNSG2dOamManager *GetOamManager(u32 screen);
void FUN_0200A064(u32 heap_id);
void FUN_0200A06C(u32 heap_id);
u32 EntryOamManagerOamWithAffineIdxMainScreen(u32 param0, u32 param1);
u32 EntryOamManagerOamWithAffineIdxSubScreen(u32 param0, u32 param1);
u32 EntryOamManagerAffineMainScreen(u32 param0);
u32 EntryOamManagerAffineSubScreen(u32 param0);

#endif // POKEDIAMOND_UNK_02009EAC_H
