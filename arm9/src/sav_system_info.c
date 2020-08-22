#include "global.h"
#include "save_block_2.h"
#include "MI_memory.h"
#include "OS_ownerInfo.h"
#include "RTC_api.h"
#include "RTC_convert.h"
#include "sav_system_info.h"

#pragma thumb on

extern void CopyRtcBuffersTo(RTCDate *, RTCTime *);

u32 FUN_0202376C(void)
{
    return sizeof(struct UnkSaveStruct_0202376C);
}

void FUN_02023770(struct UnkSaveStruct_0202376C * unk)
{
    MI_CpuClearFast(unk, sizeof(struct UnkSaveStruct_0202376C));
    FUN_02023840(&unk->rtcInfo);
}

struct UnkSaveStruct_0202376C * FUN_02023788(struct SaveBlock2 * sav2)
{
    return (struct UnkSaveStruct_0202376C *)SavArray_get(sav2, 0);
}

struct UnkSaveStruct_0202376C_sub * FUN_02023794(struct SaveBlock2 * sav2)
{
    return &FUN_02023788(sav2)->rtcInfo;
}

void FUN_020237A0(struct UnkSaveStruct_0202376C * unk)
{
    OSOwnerInfo info;
    unk->rtcOffset = OS_GetOwnerRtcOffset();
    OS_GetMacAddress(unk->macAddr);
    OS_GetOwnerInfo(&info);
    unk->birthMonth = info.birthday.month;
    unk->birthDay = info.birthday.day;
}

BOOL FUN_020237CC(struct UnkSaveStruct_0202376C * unk)
{
    u8 macAddr[6];
    OS_GetMacAddress(macAddr);
    for (int i = 0; i < 6; i++)
    {
        if (macAddr[i] != unk->macAddr[i])
            return FALSE;
    }
    return TRUE;
}

BOOL FUN_020237FC(struct UnkSaveStruct_0202376C * unk)
{
    return OS_GetOwnerRtcOffset() == unk->rtcOffset;
}

u8 FUN_02023818(struct UnkSaveStruct_0202376C * unk)
{
    return unk->birthMonth;
}

u8 FUN_0202381C(struct UnkSaveStruct_0202376C * unk)
{
    return unk->birthDay;
}

u8 FUN_02023820(struct UnkSaveStruct_0202376C * unk)
{
    return unk->field_48;
}

void FUN_02023828(struct UnkSaveStruct_0202376C * unk, u8 val)
{
    unk->field_48 = val;
}

u32 FUN_02023830(struct UnkSaveStruct_0202376C * unk)
{
    return unk->field_4C;
}

void FUN_02023834(struct UnkSaveStruct_0202376C * unk, u32 val)
{
    if (unk->field_4C == 0)
        unk->field_4C = val;
}

void FUN_02023840(struct UnkSaveStruct_0202376C_sub * sub)
{
    sub->field_00 = 1;
    CopyRtcBuffersTo(&sub->date, &sub->time);
    sub->daysSinceNitroEpoch = RTC_ConvertDateToDay(&sub->date);
    sub->secondsSinceNitroEpoch = RTC_ConvertDateTimeToSecond(&sub->date, &sub->time);
    sub->field_2C = 0;
    sub->field_30 = 0;
    sub->field_34 = 0;
}

BOOL FUN_02023874(struct UnkSaveStruct_0202376C_sub * sub)
{
    return sub->field_34 != 0;
}

void FUN_02023884(struct UnkSaveStruct_0202376C_sub * sub, u32 a1)
{
    if (sub->field_34 > 1440)
        sub->field_34 = 1440;
    if (sub->field_34 < a1)
        sub->field_34 = 0;
    else
        sub->field_34 -= a1;
}

void FUN_020238A4(struct UnkSaveStruct_0202376C_sub * sub)
{
    sub->field_34 = 1440;
    CopyRtcBuffersTo(&sub->date, &sub->time);
    sub->daysSinceNitroEpoch = RTC_ConvertDateToDay(&sub->date);
}
