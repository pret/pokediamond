#include "global.h"
#include "main.h"
#include "unk_0200CA44.h"

extern BOOL FUN_0201B60C(void *, void (*)(u32, void *), void *, void *);
extern void FUN_0201B6A0(s32);

THUMB_FUNC BOOL FUN_0200CA44(void (*r0)(u32, void *), void * r1, void * r2)
{
    return FUN_0201B60C(gMain.unk18, r0, r1, r2);
}

THUMB_FUNC BOOL FUN_0200CA60(void (*r0)(u32, void *), void * r1, void * r2)
{
    return FUN_0201B60C(gMain.unk1C, r0, r1, r2);
}

THUMB_FUNC BOOL FUN_0200CA7C(void (*r0)(u32, void *), void * r1, void * r2)
{
    return FUN_0201B60C(gMain.unk24, r0, r1, r2);
}

THUMB_FUNC BOOL FUN_0200CA98(void (*r0)(u32, void *), void * r1, void * r2)
{
    return FUN_0201B60C(gMain.unk20, r0, r1, r2);
}

THUMB_FUNC void FUN_0200CAB4(s32 unk1) //bool?
{
    FUN_0201B6A0(unk1);
}
