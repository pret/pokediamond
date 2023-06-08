#include "global.h"
#include "main.h"
#include "unk_0200CA44.h"

extern BOOL FUN_0201B60C(void *, void (*)(u32, void *), void *, u32);
extern void FUN_0201B6A0(s32);

BOOL FUN_0200CA44(void (*r0)(u32, void *), void * r1, u32 r2)
{
    return FUN_0201B60C(gSystem.unk18, r0, r1, r2);
}

BOOL FUN_0200CA60(void (*r0)(u32, void *), void * r1, u32 r2)
{
    return FUN_0201B60C(gSystem.unk1C, r0, r1, r2);
}

BOOL FUN_0200CA7C(void (*r0)(u32, void *), void * r1, u32 r2)
{
    return FUN_0201B60C(gSystem.unk24, r0, r1, r2);
}

BOOL FUN_0200CA98(void (*r0)(u32, void *), void * r1, u32 r2)
{
    return FUN_0201B60C(gSystem.unk20, r0, r1, r2);
}

void FUN_0200CAB4(s32 unk1) //bool?
{
    FUN_0201B6A0(unk1);
}
