#include "global.h"
#include "heap.h"
#include "mod21_02254A6C.h"

extern void MOD20_022536F4(u32 *param0, u32 param1);
extern u32 MOD20_02252D34(void);
extern void *FUN_02006BDC(u32 param0, u32 param1, u32 param2, void *param3, u32 param4);
extern void MOD21_02254AD4(u32 param0, u32 *param1);

THUMB_FUNC BOOL MOD21_02254A6C(UnkStruct02254A6C *param0, void *param1)
{
    UnkStruct02254A6C *strct = (UnkStruct02254A6C *)AllocFromHeap(8, 3 << 8);
    u32 sp4;
    if (strct != NULL)
    {
        MOD20_022536F4(strct->Unk08, 8);
        strct->Unk00 = param1;
        strct->Unk04 = MOD20_02252D34();
        void *res = FUN_02006BDC(12, 0x19, 1, &sp4, 8);
        if (res == 0)
        {
            FreeToHeap(strct);
            return FALSE;
        }
        MOD21_02254AD4(sp4 + 0xc, strct->Unk30);
        FreeToHeap(res);
        param0->Unk00 = strct;
        return TRUE;
    }
    return FALSE;
}