#include "global.h"
#include "heap.h"
#include "unk_0200CA44.h"
#include "mod21_02254854.h"

extern void MOD21_02254930(void *, void *);

extern void GF_RTC_CopyTime(u32 *param0);

extern void MOD21_02254D80();
extern void MOD21_02254974();
extern BOOL MOD21_02254A6C(u32 *param0, u32 *param1);
extern BOOL MOD20_02254130(void *param0, BOOL param1, void *param2, UnkStruct02254854 *param3, u32 param4);

extern void MOD21_02254B04(u32 param0);
extern void MOD20_02254198(BOOL param0);

THUMB_FUNC BOOL MOD21_02254854(UnkStruct02254854 **param0, u32 param1, u32 param2, u32 param3)
{
    UnkStruct02254854 *alloced = (UnkStruct02254854 *)AllocFromHeap(8, sizeof(UnkStruct02254854));
    if (alloced != NULL)
    {
        if (MOD21_0225489C(alloced, param1, param2, param3) && FUN_0200CA44(MOD21_02254930, alloced, (void *)1))
        {
            *param0 = alloced;
            return TRUE;
        }
        FreeToHeap(alloced);
    }
    return FALSE;
}

THUMB_FUNC BOOL MOD21_0225489C(UnkStruct02254854 *param0, u32 param1, u32 param2, u32 param3)
{
#pragma unused (param2, param3) //not sure, please check
    if (MOD21_02254A6C(&param0->Unk24, param0->Unk14))
    {
        param0->bytearray[0] = 0;
        param0->bytearray[1] = 0;
        param0->bytearray[2] = 0;
        param0->bytearray[3] = 1;
        param0->bytearray[6] = 0;
        param0->Unk20 = 0;
        GF_RTC_CopyTime(param0->Unk14);
        if (param0->Unk14[0] >= 0x18)
        {
            param0->Unk14[0] = param0->Unk14[0] % 0x18;
        }
        if (param0->Unk14[1] >= 0x3c)
        {
            param0->Unk14[0] = param0->Unk14[0] % 0x3c;
        }
        param0->bytearray[5] = (u8)param0->Unk14[1];
        param0->Unk10 = MOD20_02254130(MOD21_02254D80, TRUE, MOD21_02254974, param0, 8);
        if (param0->Unk10 == FALSE)
        {
            return FALSE;
        }
        param0->Unk28 = param1;
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC void MOD21_02254918(UnkStruct02254854 *param0)
{
    MOD21_02254B04(param0->Unk24);
    MOD20_02254198(param0->Unk10);
    FreeToHeap((void *)param0);
}
