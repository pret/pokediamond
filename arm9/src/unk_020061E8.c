#include "global.h"
#include "heap.h"
#include "unk_0200CA44.h"
#include "unk_020061E8.h"

extern struct TextPrinter *FUN_0201B6C8(void);

THUMB_FUNC BOOL FUN_020061E8(void (*r0)(u32, struct TextPrinter *), u32 r1, u32 r2, u32 r3)
{
    void * r4;
    if(r1 != 0)
    {
        r4 = AllocFromHeap(r3, r1);
        if(r4 == 0)
        {
            return FALSE;
        } // _02006202
        memset(r4, 0, r1);
    } // _0200620C
    else
    {
        r4 = NULL;
    } // _0200620E
    return FUN_0200CA44(r0, r4, r2);
}

THUMB_FUNC void FUN_0200621C(s32 r4)
{
    struct TextPrinter * r0 = FUN_0201B6C8();
    if(r0 != NULL)
    {
        FreeToHeap(r0);
    }
    FUN_0200CAB4(r4);
}
