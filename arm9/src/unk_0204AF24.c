#include "global.h"
#include "constants/rgb.h"
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
    struct FieldSystem * fieldSystem = TaskManager_GetFieldSystem(taskManager);
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

void CallTask_RestoreOverworld(struct TaskManager *taskManager) //TODO: RestoreOverworld
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

BOOL Task_ProcessFade(struct TaskManager *taskManager)
{
#pragma unused(taskManager)
    if(IsPaletteFadeFinished())
    {
        return TRUE;
    }
    return FALSE;
}

void CallTask_FadeToBlack(struct TaskManager *taskManager)
{
    if(!sub_0203739C(TaskManager_GetFieldSystem(taskManager)))
    {
        GF_ASSERT(0);
        return;
    }
    BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 6, 1, HEAP_ID_4); //TODO: find constants for palette fade
    TaskManager_Call(taskManager, Task_ProcessFade, 0);
}

void CallTask_FadeFromBlack(struct TaskManager *taskManager)
{
    if(!sub_0203739C(TaskManager_GetFieldSystem(taskManager)))
    {
        GF_ASSERT(0);
        return;
    }
    BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 6, 1, HEAP_ID_4);
    TaskManager_Call(taskManager, Task_ProcessFade, 0);
}

BOOL sub_0204B050(struct TaskManager *taskManager)
{
    u32 * r4 = TaskManager_GetStatePtr(taskManager);
    switch(r4[0])
    {
        case 0:
            CallTask_FadeToBlack(taskManager);
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
    u32 * r4 = TaskManager_GetStatePtr(taskManager);
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    switch(r4[0])
    {
        case 0:
            CallTask_RestoreOverworld(taskManager);
            r4[0]++;
            break;
        case 1:
            ov05_021E331C(fieldSystem);
            CallTask_FadeFromBlack(taskManager);
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
