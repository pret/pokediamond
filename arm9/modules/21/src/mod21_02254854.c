#include "global.h"
#include "heap.h"
#include "unk_0200CA44.h"
#include "mod21_02254854.h"

extern void GF_RTC_CopyTime(Time *param0);

u8 const MOD21_02254D80[] = { 0x10, 0xAF, 0x10, 0xCF };
extern BOOL MOD20_02254130(void *param0, BOOL param1, void *param2, UnkStruct02254854 *param3, u32 param4);
extern void MOD20_02252C14(u32 param0, BOOL param1);

extern void MOD20_02254198(BOOL param0);
extern void MOD20_022529A0(u32 param0);

extern void MOD20_0225298C(u32 param0);

extern void Poketch_InitApp(void *func1, void *func2);

THUMB_FUNC static void MOD21_02254840(void)
{
    Poketch_InitApp(MOD21_02254854, MOD21_0225496C);
}

#define NitroStaticInit MOD21_02254840
#include "sinit.h"

THUMB_FUNC BOOL MOD21_02254854(UnkStruct02254854 **param0, u32 param1, u32 param2, u32 param3)
{
    UnkStruct02254854 *alloced = (UnkStruct02254854 *)AllocFromHeap(8, sizeof(UnkStruct02254854));
    if (alloced != NULL)
    {
        if (MOD21_0225489C(alloced, param1, param2, param3) && FUN_0200CA44((void (*)(u32, struct TextPrinter *))MOD21_02254930, (struct TextPrinter *)alloced, 1))
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
    if (MOD21_02254A6C((UnkStruct02254A6C *)&param0->Unk24, &param0->time)) //todo fix
    {
        param0->bytearray[0] = 0;
        param0->bytearray[1] = 0;
        param0->bytearray[2] = 0;
        param0->bytearray[3] = 1;
        param0->bytearray[6] = 0;
        param0->Unk20 = 0;
        GF_RTC_CopyTime(&param0->time);
        if (param0->time.hour >= 0x18)
        {
            param0->time.hour = param0->time.hour % 0x18;
        }
        if (param0->time.minute >= 0x3c)
        {
            param0->time.hour = param0->time.hour % 0x3c;
        }
        param0->bytearray[5] = (u8)param0->time.minute;
        param0->Unk10 = MOD20_02254130((void *)MOD21_02254D80, TRUE, MOD21_02254974, param0, 8);
        if (param0->Unk10 == FALSE)
        {
            return FALSE;
        }
        param0->Unk28 = param1;
        return TRUE;
    }
    return FALSE;
}

BOOL (* const MOD21_02254D84[])(UnkStruct02254854 *) = { MOD21_022549A4, MOD21_022549E4, MOD21_02254A38 };

THUMB_FUNC void MOD21_02254918(UnkStruct02254854 *param0)
{
    MOD21_02254B04(param0->Unk24);
    MOD20_02254198(param0->Unk10);
    FreeToHeap((void *)param0);
}

THUMB_FUNC void MOD21_02254930(u32 param0, UnkStruct02254854 *param1)
{
    if (param1->bytearray[0] >= 3)
    {
        return;
    }
    MOD20_02252C14(param1->Unk28, param1->Unk10);
    if (!MOD21_02254D84[param1->bytearray[0]](param1))
    {
        return;
    }
    MOD21_02254918(param1);
    FUN_0200CAB4((s32)param0);
    MOD20_022529A0(param1->Unk28);
}

THUMB_FUNC void MOD21_0225496C(UnkStruct02254854 *param0)
{
    param0->bytearray[2] = 1;
}

THUMB_FUNC void MOD21_02254974(u32 param0, u32 param1, u32 param2, UnkStruct02254854 * param3)
{
#pragma unused (param0, param1)
    switch (param2)
    {
        case 1:
            param3->Unk20 = 1;
            param3->bytearray[6] = 1;
            return;
        case 0:
            param3->Unk20 = 0;
            param3->bytearray[6] = 1;
            return;
        default:
            return;
    }
}

THUMB_FUNC void MOD21_02254990(UnkStruct02254854 * param0, u8 param1)
{
    if (param0->bytearray[2] == 0)
    {
        param0->bytearray[0] = param1;
    }
    else
    {
        param0->bytearray[0] = 2;
    }
    param0->bytearray[1] = 0;
}

THUMB_FUNC BOOL MOD21_022549A4(UnkStruct02254854 * param0)
{
    switch (param0->bytearray[1])
    {
        case 0:
            MOD21_02254B10(param0->Unk24, 0);
            param0->bytearray[1]++;
            break;
        case 1:
            if (MOD21_02254B34(param0->Unk24, 0) == FALSE)
            {
                break;
            }
            MOD20_0225298C(param0->Unk28);
            MOD21_02254990(param0, 1);
            break;
        default:
            break;
    }
    return FALSE;
}

THUMB_FUNC BOOL MOD21_022549E4(UnkStruct02254854 * param0)
{
    if (param0->bytearray[2])
    {
        MOD21_02254990(param0, 2);
        return FALSE;
    }
    if (param0->bytearray[6])
    {
        param0->bytearray[6] = 0;
        MOD21_02254B10(param0->Unk24, 2);
    }
    if (MOD21_02254B34(param0->Unk24, 1))
    {
        param0->bytearray[5] = (u8)param0->time.minute;
        GF_RTC_CopyTime(&param0->time);
        if (param0->bytearray[5] != param0->time.minute)
        {
            MOD21_02254B10(param0->Unk24, 1);
        }
    }
    return FALSE;
}

THUMB_FUNC BOOL MOD21_02254A38(UnkStruct02254854 * param0)
{
    switch (param0->bytearray[1])
    {
        case 0:
            MOD21_02254B10(param0->Unk24, 3);
            param0->bytearray[1]++;
            break;
        case 1:
            if (MOD21_02254B40(param0->Unk24))
            {
                return TRUE;
            }
            break;
        default:
            break;
    }
    return FALSE;
}
