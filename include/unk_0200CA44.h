#ifndef POKEDIAMOND_UNK_0200CA44_H
#define POKEDIAMOND_UNK_0200CA44_H

// TODO: sys_task_api.h

#include "global.h"

typedef struct SysTask SysTask;

typedef void (*SysTaskFunc)(SysTask *task, void *data);

struct SysTask {      // todo move to sys_task.h
    u8 padding[0x1C]; // todo fill in
};

SysTask *SysTask_CreateOnMainQueue(SysTaskFunc func, void *data, u32 priority);
SysTask *sub_0200CA60(SysTaskFunc func, void *data, u32 priority);
SysTask *sub_0200CA7C(SysTaskFunc func, void *data, u32 priority);
SysTask *sub_0200CA98(SysTaskFunc func, void *data, u32 priority);
void SysTask_Destroy(SysTask *sysTask);

#endif // POKEDIAMOND_UNK_0200CA44_H
