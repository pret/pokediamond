#include "global.h"
#include "task.h"
#include "script.h"
#include "heap.h"

struct TaskManager *Task_New(struct FieldSystem * fieldSystem, TaskFunc taskFunc, void *env)
{
    struct TaskManager *taskManager = AllocFromHeapAtEnd(HEAP_ID_32, sizeof(struct TaskManager));
    taskManager->prev = NULL;
    taskManager->func = taskFunc;
    taskManager->state = 0;
    taskManager->env = env;
    taskManager->unk10 = NULL;
    taskManager->unk14 = NULL;
    taskManager->fieldSystem = fieldSystem;
    taskManager->unk1C = AllocFromHeapAtEnd(HEAP_ID_32, 4);
    return taskManager;
}

void FieldSystem_CreateTask(struct FieldSystem * fieldSystem, TaskFunc taskFunc, void *env)
{
    GF_ASSERT(fieldSystem->taskManager == NULL);
    fieldSystem->taskManager = Task_New(fieldSystem, taskFunc, env);
}

void TaskManager_Jump(struct TaskManager *taskManager, TaskFunc taskFunc, void *env)
{
    taskManager->func = taskFunc;
    taskManager->state = 0;
    taskManager->env = env;
    if (taskManager->unk14 != NULL || taskManager->unk14 != NULL)
    {
        FreeToHeap(taskManager->unk14);
        taskManager->unk10 = NULL;
        taskManager->unk14 = NULL;
    }
}

void TaskManager_Call(struct TaskManager *taskManager, TaskFunc taskFunc, void *env)
{
    struct TaskManager *taskManager2 = Task_New(taskManager->fieldSystem, taskFunc, env);
    taskManager2->prev = taskManager;
    taskManager->fieldSystem->taskManager = taskManager2;
}

BOOL sub_02046420(struct TaskManager *taskManager)
{
    if (taskManager->unk10 == NULL)
        return FALSE;
    while (taskManager->unk10->func(taskManager->unk10) == TRUE)
    {
        struct TaskManager *taskManager2 = taskManager->unk10->prev;
        if (taskManager->unk10->unk14 != NULL)
            FreeToHeap(taskManager->unk10->unk14);
        FreeToHeap(taskManager->unk10->unk1C);
        FreeToHeap(taskManager->unk10);
        taskManager->unk10 = taskManager2;
        if (taskManager2 == NULL)
            return TRUE;
    }
    return FALSE;
}

BOOL sub_0204646C(struct TaskManager *taskManager)
{
    return (taskManager->unk10 != NULL);
}

BOOL FieldSystem_ApplicationIsRunning(struct FieldSystem *fieldSystem)
{
    return (sub_0203739C(fieldSystem) || sub_020373C4(fieldSystem));
}

void sub_0204649C(void * r0)
{
    LoadOverlay_OVERLAY_05(r0);
}

BOOL sub_020464A4(void * r0)
{
    return (sub_020373AC(r0) != FALSE);
}

BOOL sub_020464B8(struct TaskManager *taskManager)
{
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    u32 * r4_2 = TaskManager_GetEnvironment(taskManager);
    switch (r4_2[0])
    {
    case 0:
        sub_020373D4(fieldSystem, (struct OverlayManagerTemplate *)r4_2[1], (void *)r4_2[2]); //FIXME: typing is wrong
        r4_2[0]++;
        break;
    case 1:
        if (!FieldSystem_ApplicationIsRunning(fieldSystem))
        {
            FreeToHeap(r4_2);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

void sub_02046500(struct TaskManager *taskManager, u32 r5, u32 r4)
{
    u32 * r2 = AllocFromHeapAtEnd(HEAP_ID_32, 3 * sizeof(u32));
    r2[0] = 0;
    r2[1] = r5;
    r2[2] = r4;
    TaskManager_Call(taskManager, sub_020464B8, r2);
}

struct FieldSystem *TaskManager_GetFieldSystem(struct TaskManager *taskManager)
{
    return taskManager->fieldSystem;
}

void * TaskManager_GetEnvironment(struct TaskManager *taskManager)
{
    return taskManager->env;
}

u32 * TaskManager_GetStatePtr(struct TaskManager *taskManager)
{
    return &taskManager->state;
}

u32 sub_02046534(struct TaskManager *taskManager)
{
    return *taskManager->unk1C;
}
