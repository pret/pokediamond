#ifndef POKEDIAMOND_TASK_H
#define POKEDIAMOND_TASK_H

#include "field_types_def.h"
#include "main.h"

typedef BOOL (*TaskFunc)(TaskManager *taskManager);

struct TaskManager {
    struct TaskManager *prev;
    TaskFunc func;
    u32 state;
    void *env;
    struct TaskManager *unk10;
    void *unk14;
    FieldSystem *fieldSystem;
    u32 *unk1C;
};

extern void FieldSystem_LoadFieldOverlayInternal(FieldSystem *fieldSystem);
extern void sub_020373D4(FieldSystem *, struct OverlayManagerTemplate *, void *);
extern BOOL sub_020373AC(void *);
extern BOOL sub_0203739C(FieldSystem *fieldSystem);
extern BOOL sub_020373C4(FieldSystem *fieldSystem);

struct TaskManager *Task_New(FieldSystem *fieldSystem, TaskFunc taskFunc, void *env);
void FieldSystem_CreateTask(FieldSystem *fieldSystem, TaskFunc taskFunc, void *env);
void TaskManager_Jump(struct TaskManager *taskManager, TaskFunc taskFunc, void *env);
void TaskManager_Call(struct TaskManager *taskManager, TaskFunc taskFunc, void *env);
BOOL sub_02046420(struct TaskManager *taskManager);
BOOL sub_0204646C(struct TaskManager *taskManager);
BOOL FieldSystem_ApplicationIsRunning(FieldSystem *fieldSystem);
void FieldSystem_LoadFieldOverlay(FieldSystem *fieldSystem);
BOOL sub_020464A4(void *r0);
BOOL sub_020464B8(struct TaskManager *taskManager);
void sub_02046500(struct TaskManager *taskManager, u32 r5, u32 r4);
void *TaskManager_GetEnvironment(struct TaskManager *taskManager);
u32 *TaskManager_GetStatePtr(struct TaskManager *taskManager);
u32 sub_02046534(struct TaskManager *taskManager);
FieldSystem *TaskManager_GetFieldSystem(struct TaskManager *taskManager);

#endif // POKEDIAMOND_TASK_H
