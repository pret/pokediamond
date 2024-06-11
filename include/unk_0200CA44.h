#ifndef POKEDIAMOND_UNK_0200CA44_H
#define POKEDIAMOND_UNK_0200CA44_H

//TODO: sys_task_api.h

#include "text.h"

typedef struct SysTask SysTask;

typedef void (*SysTaskFunc)(SysTask *task, void *data);

struct SysTask { //todo move to sys_task.h
    u8 padding[0x1C]; //todo fill in
};

SysTask *SysTask_CreateOnMainQueue(SysTaskFunc func, void *data, u32 priority);
BOOL sub_0200CA60(void (*r0)(u32, void *), void * r1, u32 r2);
BOOL sub_0200CA7C(void (*r0)(u32, void *), void * r1, u32 r2);
BOOL sub_0200CA98(void (*r0)(u32, void *), void * r1, u32 r2);
void sub_0200CAB4(s32 unk1);

#endif //POKEDIAMOND_UNK_0200CA44_H
