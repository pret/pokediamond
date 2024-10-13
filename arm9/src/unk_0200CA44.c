#include "unk_0200CA44.h"

#include "global.h"

#include "main.h"

extern SysTask *sub_0201B60C(void *queue, SysTaskFunc func, void *data, u32 priority);
extern void sub_0201B6A0(SysTask *sysTask);

SysTask *SysTask_CreateOnMainQueue(SysTaskFunc func, void *data, u32 priority) {
    return sub_0201B60C(gSystem.unk18, func, data, priority);
}

SysTask *sub_0200CA60(SysTaskFunc func, void *data, u32 priority) {
    return sub_0201B60C(gSystem.unk1C, func, data, priority);
}

SysTask *sub_0200CA7C(SysTaskFunc func, void *data, u32 priority) {
    return sub_0201B60C(gSystem.unk24, func, data, priority);
}

SysTask *sub_0200CA98(SysTaskFunc func, void *data, u32 priority) {
    return sub_0201B60C(gSystem.unk20, func, data, priority);
}

void SysTask_Destroy(SysTask *sysTask) {
    sub_0201B6A0(sysTask);
}
