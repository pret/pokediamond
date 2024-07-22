#include "global.h"
#include "main.h"
#include "unk_0200CA44.h"

extern SysTask *sub_0201B60C(void *queue, SysTaskFunc func, void *data, u32 priority);
extern void sub_0201B6A0(s32);

SysTask *SysTask_CreateOnMainQueue(SysTaskFunc func, void *data, u32 priority)
{
    return sub_0201B60C(gSystem.unk18, func, data, priority);
}

BOOL sub_0200CA60(void (*r0)(u32, void *), void * r1, u32 r2)
{
    return (BOOL)sub_0201B60C(gSystem.unk1C, (SysTaskFunc)r0, r1, r2); //TODO: this is wrong
}

BOOL sub_0200CA7C(void (*r0)(u32, void *), void * r1, u32 r2)
{
    return (BOOL)sub_0201B60C(gSystem.unk24, (SysTaskFunc)r0, r1, r2);
}

BOOL sub_0200CA98(void (*r0)(u32, void *), void * r1, u32 r2)
{
    return (BOOL)sub_0201B60C(gSystem.unk20, (SysTaskFunc)r0, r1, r2);
}

void sub_0200CAB4(s32 unk1) //todo: SysTask
{
    sub_0201B6A0(unk1);
}
