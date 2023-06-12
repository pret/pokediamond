#include "global.h"
#include "gx.h"
#include "unk_0204AF24.h"

extern void FUN_02037394(struct FieldSystem *);
extern u32 FUN_0200E308(void);
extern void BeginNormalPaletteFade(u32 pattern, u32 typeTop, u32 typeBottom, u16 colour, u32 duration, u32 framesPer, u32 heapId);
extern void MOD05_021E331C(struct FieldSystem *);

BOOL FUN_0204AF24(struct TaskManager *taskManager)
{
    if(!FUN_0203739C(FUN_02046528(taskManager)))
    {
        return TRUE;
    }
    return FALSE;
}

void FUN_0204AF3C(struct TaskManager *taskManager)
{
    struct FieldSystem * fieldSystem= FUN_02046528(taskManager);
    if(!FUN_0203739C(fieldSystem))
    {
        GF_ASSERT(FALSE);
        return;
    }
    FUN_02037394(fieldSystem);
    FUN_0204640C(taskManager, &FUN_0204AF24, NULL);
}

BOOL FUN_0204AF6C(struct TaskManager *taskManager)
{
    if(FUN_020464A4(FUN_02046528(taskManager)))
    {
        return TRUE;
    }
    return FALSE;
}

void FUN_0204AF84(struct TaskManager *taskManager) //TODO: RestoreOverworld
{
    struct FieldSystem *fieldSystem = FUN_02046528(taskManager);
    if(FUN_0203739C(fieldSystem))
    {
        GF_ASSERT(FALSE);
        return;
    }
    FUN_0204649C(fieldSystem);
    FUN_0204640C(taskManager, &FUN_0204AF6C, NULL);
}

BOOL FUN_0204AFB4(struct TaskManager *taskManager)
{
#pragma unused(taskManager)
    if(FUN_0200E308())
    {
        return TRUE;
    }
    return FALSE;
}

void FUN_0204AFC8(struct TaskManager *taskManager)
{
    if(!FUN_0203739C(FUN_02046528(taskManager)))
    {
        GF_ASSERT(0);
        return;
    }
    BeginNormalPaletteFade(0, 0, 0, GX_RGB_BLACK, 6, 1, 4);
    FUN_0204640C(taskManager, &FUN_0204AFB4, 0);
}

void FUN_0204B00C(struct TaskManager *taskManager)
{
    if(!FUN_0203739C(FUN_02046528(taskManager)))
    {
        GF_ASSERT(0);
        return;
    }
    BeginNormalPaletteFade(0, 1, 1, GX_RGB_BLACK, 6, 1, 4);
    FUN_0204640C(taskManager, FUN_0204AFB4, 0);
}

BOOL FUN_0204B050(struct TaskManager *taskManager)
{
    u32 * r4 = FUN_02046530(taskManager);
    switch(r4[0])
    {
        case 0:
            FUN_0204AFC8(taskManager);
            r4[0]++;
            break;
        case 1:
            FUN_0204AF3C(taskManager);
            r4[0]++;
            break;
        case 2:
            return TRUE;
        default:
            break;
    }
    return FALSE;
}

void FUN_0204B090(struct TaskManager *taskManager)
{
    FUN_0204640C(taskManager, &FUN_0204B050, 0);
}

BOOL FUN_0204B0A0(struct TaskManager *taskManager)
{
    u32 * r4 = FUN_02046530(taskManager);
    struct FieldSystem *fieldSystem = FUN_02046528(taskManager);
    switch(r4[0])
    {
        case 0:
            FUN_0204AF84(taskManager);
            r4[0]++;
            break;
        case 1:
            MOD05_021E331C(fieldSystem);
            FUN_0204B00C(taskManager);
            r4[0]++;
            break;
        case 2:
            return TRUE;
        default:
            break;
    }
    return FALSE;
}

void FUN_0204B0E8(struct TaskManager *taskManager)
{
    FUN_0204640C(taskManager, &FUN_0204B0A0, 0);
}
