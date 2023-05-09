#ifndef POKEDIAMOND_TASK_H
#define POKEDIAMOND_TASK_H

#include "script.h"
#include "main.h"

struct TaskManager;

typedef BOOL (*TaskFunc)(struct TaskManager *taskManager);

struct TaskManager
{
    struct TaskManager *prev;
    TaskFunc func;
    u32 state;
    void *env;
    struct TaskManager *unk10;
    void *unk14;
    struct FieldSystem *fieldSystem;
    u32 *unk1C;
};

extern void LoadOverlay_MODULE_05(void *);
extern void FUN_020373D4(struct FieldSystem *, struct OverlayManagerTemplate *, void*);
extern BOOL FUN_020373AC(void *);
extern BOOL FUN_0203739C(void *);
extern BOOL FUN_020373C4(void *);

struct TaskManager *FieldSys_CreateTask(struct FieldSystem *fieldSystem, TaskFunc taskFunc, void *env);
void FUN_020463CC(struct FieldSystem *fieldSystem, TaskFunc taskFunc, void *env);
void FUN_020463EC(struct TaskManager *taskManager, TaskFunc taskFunc, void *env);
void FUN_0204640C(struct TaskManager *taskManager, TaskFunc taskFunc, void *env);
BOOL FUN_02046420(struct TaskManager *taskManager);
BOOL FUN_0204646C(struct TaskManager *taskManager);
BOOL FUN_0204647C(void * r4);
void FUN_0204649C(void * r0);
BOOL FUN_020464A4(void * r0);
BOOL FUN_020464B8(struct TaskManager *taskManager);
void FUN_02046500(struct TaskManager *taskManager, u32 r5, u32 r4);
void * FUN_0204652C(struct TaskManager *taskManager);
u32 * FUN_02046530(struct TaskManager *taskManager);
u32 FUN_02046534(struct TaskManager *taskManager);
struct FieldSystem *FUN_02046528(struct TaskManager *taskManager);

#endif //POKEDIAMOND_TASK_H
