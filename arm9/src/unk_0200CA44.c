#include "global.h"
#include "main.h"
#include "unk_0200CA44.h"

extern void FUN_0201B60C(s32, void (*)(void *, void *), void *, void *);
extern void FUN_0201B6A0(s32);

THUMB_FUNC void FUN_0200CA44(void (*r0)(void *, void *), void * r1, void * r2)
{
    FUN_0201B60C(gMain.unk18, r0, r1, r2);
}

THUMB_FUNC void FUN_0200CA60(void (*r0)(void *, void *), void * r1, void * r2)
{
    FUN_0201B60C(gMain.unk1C, r0, r1, r2);
}

THUMB_FUNC void FUN_0200CA7C(void (*r0)(void *, void *), void * r1, void * r2)
{
    FUN_0201B60C(gMain.unk24, r0, r1, r2);
}

THUMB_FUNC void FUN_0200CA98(void (*r0)(void *, void *), void * r1, void * r2)
{
    FUN_0201B60C(gMain.unk20, r0, r1, r2);
}

THUMB_FUNC void FUN_0200CAB4(s32 unk1)
{
    FUN_0201B6A0(unk1);
}
