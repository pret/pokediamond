#ifndef POKEDIAMOND_TASK_H
#define POKEDIAMOND_TASK_H

//#include "script.h" - dirty hack while FieldSystem is still in script.h
#include "main.h"

typedef struct TaskManager TaskManager;

typedef BOOL (*TaskFunc)(TaskManager *taskManager);

struct FieldSystem; //FIXME: dirty hack

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
extern void sub_020373D4(struct FieldSystem *, struct OverlayManagerTemplate *, void*);
extern BOOL sub_020373AC(void *);
extern BOOL sub_0203739C(struct FieldSystem *fieldSystem);
extern BOOL sub_020373C4(struct FieldSystem *fieldSystem);

struct TaskManager *FieldSys_CreateTask(struct FieldSystem *fieldSystem, TaskFunc taskFunc, void *env);
void sub_020463CC(struct FieldSystem *fieldSystem, TaskFunc taskFunc, void *env);
void sub_020463EC(struct TaskManager *taskManager, TaskFunc taskFunc, void *env);
void sub_0204640C(struct TaskManager *taskManager, TaskFunc taskFunc, void *env);
BOOL sub_02046420(struct TaskManager *taskManager);
BOOL sub_0204646C(struct TaskManager *taskManager);
BOOL sub_0204647C(struct FieldSystem *fieldSystem);
void sub_0204649C(void * r0);
BOOL sub_020464A4(void * r0);
BOOL sub_020464B8(struct TaskManager *taskManager);
void sub_02046500(struct TaskManager *taskManager, u32 r5, u32 r4);
void * sub_0204652C(struct TaskManager *taskManager);
u32 * sub_02046530(struct TaskManager *taskManager);
u32 sub_02046534(struct TaskManager *taskManager);
struct FieldSystem *sub_02046528(struct TaskManager *taskManager);

#endif //POKEDIAMOND_TASK_H
