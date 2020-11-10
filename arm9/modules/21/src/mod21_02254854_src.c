#include "global.h"
#include "heap.h"
#include "unk_0200CA44.h"
#include "mod21_02254854.h"

extern BOOL MOD21_0225489C(void *param0, u32 param1, u32 param2, u32 param3);
extern void MOD21_02254930(void *, void *);

THUMB_FUNC BOOL MOD21_02254854(u32 *param0, u32 param1, u32 param2, u32 param3) //param0 is likely actually a struct
{
    void * alloced =  AllocFromHeap(8, 0x2c);
    if (alloced != NULL)
    {
        if (MOD21_0225489C(alloced, param1, param2, param3) && FUN_0200CA44(MOD21_02254930, alloced, (void *)1))
        {
            *param0 = (u32)alloced;
            return TRUE;
        }
        FreeToHeap(alloced);
    }
    return FALSE;
}
