#include "global.h"
#include "gx.h"
#include "unk_0204AF24.h"

extern void sub_02037394(struct FieldSystem *);
extern u32 IsPaletteFadeFinished(void);
extern void BeginNormalPaletteFade(u32 pattern, u32 typeTop, u32 typeBottom, u16 colour, u32 duration, u32 framesPer, HeapID heapId);
extern void ov05_021E331C(struct FieldSystem *);

BOOL sub_0204AF24(struct TaskManager *taskManager)
{
    if(!sub_0203739C(TaskManager_GetFieldSystem(taskManager)))
    {
        return TRUE;
    }
    return FALSE;
}

void sub_0204AF3C(struct TaskManager *taskManager)
{
    struct FieldSystem * fieldSystem= TaskManager_GetFieldSystem(taskManager);
    if(!sub_0203739C(fieldSystem))
    {
        GF_ASSERT(FALSE);
        return;
    }
    sub_02037394(fieldSystem);
    TaskManager_Call(taskManager, &sub_0204AF24, NULL);
}

BOOL sub_0204AF6C(struct TaskManager *taskManager)
{
    if(sub_020464A4(TaskManager_GetFieldSystem(taskManager)))
    {
        return TRUE;
    }
    return FALSE;
}

void sub_0204AF84(struct TaskManager *taskManager) //TODO: RestoreOverworld
{
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    if(sub_0203739C(fieldSystem))
    {
        GF_ASSERT(FALSE);
        return;
    }
    sub_0204649C(fieldSystem);
    TaskManager_Call(taskManager, &sub_0204AF6C, NULL);
}

BOOL sub_0204AFB4(struct TaskManager *taskManager)
{
#pragma unused(taskManager)
    if(IsPaletteFadeFinished())
    {
        return TRUE;
    }
    return FALSE;
}

void sub_0204AFC8(struct TaskManager *taskManager)
{
    if(!sub_0203739C(TaskManager_GetFieldSystem(taskManager)))
    {
        GF_ASSERT(0);
        return;
    }
    BeginNormalPaletteFade(0, 0, 0, GX_RGB_BLACK, 6, 1, HEAP_ID_4);
    TaskManager_Call(taskManager, &sub_0204AFB4, 0);
}

void sub_0204B00C(struct TaskManager *taskManager)
{
    if(!sub_0203739C(TaskManager_GetFieldSystem(taskManager)))
    {
        GF_ASSERT(0);
        return;
    }
    BeginNormalPaletteFade(0, 1, 1, GX_RGB_BLACK, 6, 1, HEAP_ID_4);
    TaskManager_Call(taskManager, sub_0204AFB4, 0);
}

BOOL sub_0204B050(struct TaskManager *taskManager)
{
    u32 * r4 = sub_02046530(taskManager);
    switch(r4[0])
    {
        case 0:
            sub_0204AFC8(taskManager);
            r4[0]++;
            break;
        case 1:
            sub_0204AF3C(taskManager);
            r4[0]++;
            break;
        case 2:
            return TRUE;
        default:
            break;
    }
    return FALSE;
}

void sub_0204B090(struct TaskManager *taskManager)
{
    TaskManager_Call(taskManager, &sub_0204B050, 0);
}

BOOL sub_0204B0A0(struct TaskManager *taskManager)
{
    u32 * r4 = sub_02046530(taskManager);
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    switch(r4[0])
    {
        case 0:
            sub_0204AF84(taskManager);
            r4[0]++;
            break;
        case 1:
            ov05_021E331C(fieldSystem);
            sub_0204B00C(taskManager);
            r4[0]++;
            break;
        case 2:
            return TRUE;
        default:
            break;
    }
    return FALSE;
}

void sub_0204B0E8(struct TaskManager *taskManager)
{
    TaskManager_Call(taskManager, &sub_0204B0A0, 0);
}
