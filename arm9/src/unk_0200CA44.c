#include "global.h"
#include "main.h"
#include "unk_0200CA44.h"

extern BOOL sub_0201B60C(void *, void (*)(u32, void *), void *, u32);
extern void sub_0201B6A0(s32);

BOOL sub_0200CA44(void (*r0)(u32, void *), void * r1, u32 r2)
{
    return sub_0201B60C(gSystem.unk18, r0, r1, r2);
}

BOOL sub_0200CA60(void (*r0)(u32, void *), void * r1, u32 r2)
{
    return sub_0201B60C(gSystem.unk1C, r0, r1, r2);
}

BOOL sub_0200CA7C(void (*r0)(u32, void *), void * r1, u32 r2)
{
    return sub_0201B60C(gSystem.unk24, r0, r1, r2);
}

BOOL sub_0200CA98(void (*r0)(u32, void *), void * r1, u32 r2)
{
    return sub_0201B60C(gSystem.unk20, r0, r1, r2);
}

void sub_0200CAB4(s32 unk1) //bool?
{
    sub_0201B6A0(unk1);
}
