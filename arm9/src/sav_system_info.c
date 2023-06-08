#include "global.h"
#include "save_block_2.h"
#include "MI_memory.h"
#include "OS_ownerInfo.h"
#include "RTC_api.h"
#include "RTC_convert.h"
#include "sav_system_info.h"

extern void GF_RTC_CopyDateTime(RTCDate *, RTCTime *);

u32 Save_SysInfo_sizeof(void)
{
    return sizeof(struct SavSysInfo);
}

void Save_SysInfo_Init(struct SavSysInfo * unk)
{
    MI_CpuClearFast(unk, sizeof(struct SavSysInfo));
    Save_SysInfo_RTC_Init(&unk->rtcInfo);
}

struct SavSysInfo * Save_SysInfo_Get(struct SaveBlock2 * sav2)
{
    return (struct SavSysInfo *)SaveArray_Get(sav2, 0);
}

struct UnkSaveStruct_0202376C_sub * Save_SysInfo_RTC_Get(struct SaveBlock2 * sav2)
{
    return &Save_SysInfo_Get(sav2)->rtcInfo;
}

void Save_SysInfo_InitFromSystem(struct SavSysInfo * unk)
{
    OSOwnerInfo info;
    unk->rtcOffset = OS_GetOwnerRtcOffset();
    OS_GetMacAddress(unk->macAddr);
    OS_GetOwnerInfo(&info);
    unk->birthMonth = info.birthday.month;
    unk->birthDay = info.birthday.day;
}

BOOL Save_SysInfo_MacAddressIsMine(struct SavSysInfo * unk)
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

BOOL Save_SysInfo_RTCOffsetIsMine(struct SavSysInfo * unk)
{
    return OS_GetOwnerRtcOffset() == unk->rtcOffset;
}

u8 Save_SysInfo_GetBirthMonth(struct SavSysInfo * unk)
{
    return unk->birthMonth;
}

u8 Save_SysInfo_GetBirthDay(struct SavSysInfo * unk)
{
    return unk->birthDay;
}

u8 FUN_02023820(struct SavSysInfo * unk)
{
    return unk->field_48;
}

void FUN_02023828(struct SavSysInfo * unk, u8 val)
{
    unk->field_48 = val;
}

u32 FUN_02023830(struct SavSysInfo * unk)
{
    return unk->field_4C;
}

void FUN_02023834(struct SavSysInfo * unk, u32 val)
{
    if (unk->field_4C == 0)
        unk->field_4C = val;
}

void Save_SysInfo_RTC_Init(struct UnkSaveStruct_0202376C_sub * sub)
{
    sub->field_00 = 1;
    GF_RTC_CopyDateTime(&sub->date, &sub->time);
    sub->daysSinceNitroEpoch = RTC_ConvertDateToDay(&sub->date);
    sub->secondsSinceNitroEpoch = RTC_ConvertDateTimeToSecond(&sub->date, &sub->time);
    sub->field_2C = 0;
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
    GF_RTC_CopyDateTime(&sub->date, &sub->time);
    sub->daysSinceNitroEpoch = RTC_ConvertDateToDay(&sub->date);
}
