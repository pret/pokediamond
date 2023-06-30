#include "global.h"
#include "save.h"
#include "MI_memory.h"
#include "OS_ownerInfo.h"
#include "RTC_api.h"
#include "RTC_convert.h"
#include "save_system_info.h"

extern void GF_RTC_CopyDateTime(RTCDate *, RTCTime *);

u32 Save_SysInfo_sizeof(void)
{
    return sizeof(struct SaveSysInfo);
}

void Save_SysInfo_Init(struct SaveSysInfo * unk)
{
    MI_CpuClearFast(unk, sizeof(struct SaveSysInfo));
    Save_SysInfo_RTC_Init(&unk->rtcInfo);
}

struct SaveSysInfo * Save_SysInfo_Get(struct SaveData * save)
{
    return (struct SaveSysInfo *)SaveArray_Get(save, 0);
}

struct UnkSaveStruct_0202376C_sub * Save_SysInfo_RTC_Get(struct SaveData * save)
{
    return &Save_SysInfo_Get(save)->rtcInfo;
}

void Save_SysInfo_InitFromSystem(struct SaveSysInfo * unk)
{
    OSOwnerInfo info;
    unk->rtcOffset = OS_GetOwnerRtcOffset();
    OS_GetMacAddress(unk->macAddr);
    OS_GetOwnerInfo(&info);
    unk->birthMonth = info.birthday.month;
    unk->birthDay = info.birthday.day;
}

BOOL Save_SysInfo_MacAddressIsMine(struct SaveSysInfo * unk)
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

BOOL Save_SysInfo_RTCOffsetIsMine(struct SaveSysInfo * unk)
{
    return OS_GetOwnerRtcOffset() == unk->rtcOffset;
}

u8 Save_SysInfo_GetBirthMonth(struct SaveSysInfo * unk)
{
    return unk->birthMonth;
}

u8 Save_SysInfo_GetBirthDay(struct SaveSysInfo * unk)
{
    return unk->birthDay;
}

u8 sub_02023820(struct SaveSysInfo * unk)
{
    return unk->field_48;
}

void sub_02023828(struct SaveSysInfo * unk, u8 val)
{
    unk->field_48 = val;
}

u32 sub_02023830(struct SaveSysInfo * unk)
{
    return unk->field_4C;
}

void sub_02023834(struct SaveSysInfo * unk, u32 val)
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

BOOL sub_02023874(struct UnkSaveStruct_0202376C_sub * sub)
{
    return sub->field_34 != 0;
}

void sub_02023884(struct UnkSaveStruct_0202376C_sub * sub, u32 a1)
{
    if (sub->field_34 > 1440)
        sub->field_34 = 1440;
    if (sub->field_34 < a1)
        sub->field_34 = 0;
    else
        sub->field_34 -= a1;
}

void sub_020238A4(struct UnkSaveStruct_0202376C_sub * sub)
{
    sub->field_34 = 1440;
    GF_RTC_CopyDateTime(&sub->date, &sub->time);
    sub->daysSinceNitroEpoch = RTC_ConvertDateToDay(&sub->date);
}
