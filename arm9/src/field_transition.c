#include "field_transition.h"

#include "global.h"

#include "constants/rgb.h"

#include "gx.h"

extern void sub_02037394(struct FieldSystem *);
extern u32 IsPaletteFadeFinished(void);
extern void BeginNormalPaletteFade(u32 pattern, u32 typeTop, u32 typeBottom, u16 colour, u32 duration, u32 framesPer, enum HeapID heapID);
extern void ov05_021E331C(struct FieldSystem *);

BOOL FieldTask_WaitUntilMapFinished(struct TaskManager *taskManager) {
    if (!sub_0203739C(TaskManager_GetFieldSystem(taskManager))) {
        return TRUE;
    }
    return FALSE;
}

void FieldTransition_FinishMap(struct TaskManager *taskManager) {
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    if (!sub_0203739C(fieldSystem)) {
        GF_ASSERT(FALSE);
        return;
    }
    sub_02037394(fieldSystem);
    TaskManager_Call(taskManager, &FieldTask_WaitUntilMapFinished, NULL);
}

BOOL FieldTask_WaitUntilMapStarted(struct TaskManager *taskManager) {
    if (sub_020464A4(TaskManager_GetFieldSystem(taskManager))) {
        return TRUE;
    }
    return FALSE;
}

void FieldTransition_StartMap(struct TaskManager *taskManager) {
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    if (sub_0203739C(fieldSystem)) {
        GF_ASSERT(FALSE);
        return;
    }
    FieldSystem_LoadFieldOverlay(fieldSystem);
    TaskManager_Call(taskManager, &FieldTask_WaitUntilMapStarted, NULL);
}

BOOL FieldTask_WaitUntilScreenTransitionDone(struct TaskManager *taskManager) {
#pragma unused(taskManager)
    if (IsPaletteFadeFinished()) {
        return TRUE;
    }
    return FALSE;
}

void FieldTransition_FadeOut(struct TaskManager *taskManager) {
    if (!sub_0203739C(TaskManager_GetFieldSystem(taskManager))) {
        GF_ASSERT(0);
        return;
    }
    BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 6, 1, HEAP_ID_4); // TODO: find constants for palette fade
    TaskManager_Call(taskManager, FieldTask_WaitUntilScreenTransitionDone, 0);
}

void FieldTransition_FadeIn(struct TaskManager *taskManager) {
    if (!sub_0203739C(TaskManager_GetFieldSystem(taskManager))) {
        GF_ASSERT(0);
        return;
    }
    BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 6, 1, HEAP_ID_4);
    TaskManager_Call(taskManager, FieldTask_WaitUntilScreenTransitionDone, 0);
}

BOOL FieldTask_FadeOutAndFinishMap(struct TaskManager *taskManager) {
    u32 *r4 = TaskManager_GetStatePtr(taskManager);
    switch (r4[0]) {
    case 0:
        FieldTransition_FadeOut(taskManager);
        r4[0]++;
        break;
    case 1:
        FieldTransition_FinishMap(taskManager);
        r4[0]++;
        break;
    case 2:
        return TRUE;
    default:
        break;
    }
    return FALSE;
}

void FieldTransition_FadeOutAndFinishMap(struct TaskManager *taskManager) {
    TaskManager_Call(taskManager, &FieldTask_FadeOutAndFinishMap, 0);
}

BOOL FieldTask_StartMapAndFadeIn(struct TaskManager *taskManager) {
    u32 *r4 = TaskManager_GetStatePtr(taskManager);
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    switch (r4[0]) {
    case 0:
        FieldTransition_StartMap(taskManager);
        r4[0]++;
        break;
    case 1:
        ov05_021E331C(fieldSystem);
        FieldTransition_FadeIn(taskManager);
        r4[0]++;
        break;
    case 2:
        return TRUE;
    default:
        break;
    }
    return FALSE;
}

void FieldTransition_StartMapAndFadeIn(struct TaskManager *taskManager) {
    TaskManager_Call(taskManager, &FieldTask_StartMapAndFadeIn, 0);
}
