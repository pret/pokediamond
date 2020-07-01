#include "global.h"
#include "main.h"
#include "unk_0200CA44.h"

extern void FUN_0201B60C(s32, u16, u16, u16);
extern void FUN_0201B6A0(s32);

THUMB_FUNC void FUN_0200CA44(u16 r0, u16 r1, u16 r2)
{
    FUN_0201B60C(gUnknown21C48B8.unk18,r0,r1,r2);
}

THUMB_FUNC void FUN_0200CA60(u16 r0, u16 r1, u16 r2)
{
    FUN_0201B60C(gUnknown21C48B8.unk1C,r0,r1,r2);
}

THUMB_FUNC void FUN_0200CA7C(u16 r0, u16 r1, u16 r2)
{
    FUN_0201B60C(gUnknown21C48B8.unk24,r0,r1,r2);
}

THUMB_FUNC void FUN_0200CA98(u16 r0, u16 r1, u16 r2)
{
    FUN_0201B60C(gUnknown21C48B8.unk20,r0,r1,r2);
}

THUMB_FUNC void FUN_0200CAB4(s32 unk1)
{
    FUN_0201B6A0(unk1);
}
