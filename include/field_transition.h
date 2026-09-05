#ifndef POKEDIAMOND_FIELD_TRANSITION_H
#define POKEDIAMOND_FIELD_TRANSITION_H

#include "nitro/types.h"

#include "task.h"

BOOL FieldTask_WaitUntilMapFinished(struct TaskManager *taskManager);
void FieldTransition_FinishMap(struct TaskManager *taskManager);
BOOL FieldTask_WaitUntilMapStarted(struct TaskManager *taskManager);
void FieldTransition_StartMap(struct TaskManager *taskManager);
BOOL FieldTask_WaitUntilScreenTransitionDone(struct TaskManager *taskManager);
void FieldTransition_FadeOut(struct TaskManager *taskManager);
void FieldTransition_FadeIn(struct TaskManager *taskManager);
BOOL FieldTask_FadeOutAndFinishMap(struct TaskManager *taskManager);
void FieldTransition_FadeOutAndFinishMap(struct TaskManager *taskManager);
BOOL FieldTask_StartMapAndFadeIn(struct TaskManager *taskManager);
void FieldTransition_StartMapAndFadeIn(struct TaskManager *taskManager);

#endif // POKEDIAMOND_FIELD_TRANSITION_H
