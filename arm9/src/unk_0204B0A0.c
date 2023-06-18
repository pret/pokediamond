#include "global.h"
#include "event_data.h"
#include "unk_0204B0A0.h"
#include "unk_0205FA2C.h"

extern void GF_RTC_CopyDateTime(struct RTCDate* date, struct RTCTime* time);
extern void FUN_02029C08(void*);
extern void FUN_0202B3C4(void*, s32, u32);
extern u8 GF_RTC_GetTimeOfDayByHour(u32 hour);
extern s64 GF_RTC_DateTimeToSec(void);
extern void* FUN_02029AFC(struct SaveData* save);
extern void* FUN_02022504(struct SaveData* save);
extern void FUN_02025B60(struct SaveData* save, s32, BOOL);
extern BOOL FUN_0205F668(struct SaveData* save);
extern void FUN_0202A9D0(struct SaveData* save, s32);
extern BOOL FUN_0205F618(struct SaveData* save, u16);
extern void FUN_0204B3D0(struct FieldSystem*, s32);
extern void FUN_0205F5A4(struct ScriptState* state, u16);
extern s32 FUN_0205F594(struct ScriptState* state);
extern void FUN_0202A988(void*, u32);
extern void* Save_Roamers_Get(struct SaveData* save);
extern void FUN_02060344(struct SaveData* save, s32);
extern void FUN_0203959C(struct FieldSystem*);
extern void FUN_02025A60(struct SaveData* save, s32);
extern struct SaveData* ScriptEnvironment_GetSavePtr(struct FieldSystem*);

void FUN_0204B0F8(struct FieldSystem *fieldSystem)
{
    RTCDate date;
    RTCTime time;

    struct UnkSaveStruct_0202376C_sub* rtc_info = Save_SysInfo_RTC_Get(fieldSystem->saveData);
    if (rtc_info->field_00 != 0)
    {
        GF_RTC_CopyDateTime(&date, &time);
        FUN_0204B130(fieldSystem, rtc_info, &date);
        FUN_0204B158(fieldSystem, rtc_info, &date, &time);
    }
}

void FUN_0204B130(struct FieldSystem *fieldSystem, struct UnkSaveStruct_0202376C_sub* rtc_info, struct RTCDate* date)
{
    u32 days = (u32)RTC_ConvertDateToDay(date);
    u32 days_since_nitro_epoch = (u32)rtc_info->daysSinceNitroEpoch;

    if (days < days_since_nitro_epoch)
    {
        rtc_info->daysSinceNitroEpoch = (s32)days;
    }
    else if (days > days_since_nitro_epoch)
    {
        FUN_0204B1DC(fieldSystem, (s32)(days - days_since_nitro_epoch));
        rtc_info->daysSinceNitroEpoch = (s32)days;
    }
}

void FUN_0204B158(struct FieldSystem *fieldSystem, struct UnkSaveStruct_0202376C_sub* rtc_info, struct RTCDate* date, struct RTCTime* time)
{
    s64 unk1 = RTC_ConvertDateTimeToSecond(date, time);
    s64 unk2 = RTC_ConvertDateTimeToSecond(&rtc_info->date, &rtc_info->time);

    if (unk2 > unk1)
    {
        rtc_info->date = *date;
        rtc_info->time = *time;
        return;
    }

    s32 minutes = (s32)((unk1 - unk2) / 60);
    if (minutes > 0)
    {
        FUN_02023884(rtc_info, (u32)minutes);
        FUN_0204B270(fieldSystem, minutes, time);

        rtc_info->date = *date;
        rtc_info->time = *time;
    }
}

void FUN_0204B1DC(struct FieldSystem *fieldSystem, s32 a1)
{
    struct SaveData* save = ScriptEnvironment_GetSavePtr(fieldSystem);
    FUN_02025A60(save, a1);
    FUN_0203959C(fieldSystem);
    FUN_02060344(fieldSystem->saveData, a1);

    void* unk_sav_ptr1 = FUN_0202881C(fieldSystem->saveData);
    FUN_02028754(unk_sav_ptr1, (u32)a1);

    void* unk_sav_ptr2 = Save_Roamers_Get(fieldSystem->saveData);
    unk_sav_ptr1 = FUN_0202881C(fieldSystem->saveData);
    u32 unk1 = FUN_020287A4(unk_sav_ptr1);
    FUN_0202A988(unk_sav_ptr2, unk1);

    struct PlayerParty* party = SaveArray_PlayerParty_Get(fieldSystem->saveData);
    Party_UpdatePokerus(party, a1);

    struct ScriptState* state = SaveArray_Flags_Get(fieldSystem->saveData);
    s32 unk2 = FUN_0205F594(state);

    u16 unk3;
    if (unk2 > a1)
    {
        unk3 = (u16)(unk2 - a1);
    }
    else
    {
        unk3 = 0;
    }

    FUN_0205F5A4(state, unk3);
    FUN_0205F618(fieldSystem->saveData, (u16)a1);
    FUN_0205F668(fieldSystem->saveData);
    FUN_0206007C(fieldSystem->saveData);

    void* unk_sav_ptr3 = FUN_02029AFC(fieldSystem->saveData);
    FUN_02029C08(unk_sav_ptr3);
}

void FUN_0204B270(struct FieldSystem *fieldSystem, s32 a1, struct RTCTime* time)
{
    FUN_0204B3D0(fieldSystem, a1);
    FUN_0202A9D0(fieldSystem->saveData, a1);
    BOOL unk_bool = FUN_0204B33C(fieldSystem);
    FUN_02025B60(fieldSystem->saveData, a1, unk_bool);
    void* unk_sav_ptr = FUN_02022504(fieldSystem->saveData);
    FUN_0202B3C4(unk_sav_ptr, a1, time->minute);
}

u32 Script_GetTimeOfDay(struct FieldSystem *fieldSystem)
{
    struct UnkSaveStruct_0202376C_sub* rtc_info = Save_SysInfo_RTC_Get(fieldSystem->saveData);

    return GF_RTC_GetTimeOfDayByHour(rtc_info->time.hour);
}

u32 Script_GetMonth(struct FieldSystem *fieldSystem)
{
    struct UnkSaveStruct_0202376C_sub* rtc_info = Save_SysInfo_RTC_Get(fieldSystem->saveData);

    return rtc_info->date.month;
}

u32 Script_GetDay(struct FieldSystem *fieldSystem)
{
    struct UnkSaveStruct_0202376C_sub* rtc_info = Save_SysInfo_RTC_Get(fieldSystem->saveData);

    return rtc_info->date.day;
}

RTCWeek Script_GetWeekday(struct FieldSystem *fieldSystem)
{
    struct UnkSaveStruct_0202376C_sub* rtc_info = Save_SysInfo_RTC_Get(fieldSystem->saveData);

    return rtc_info->date.week;
}

u32 Script_GetHour(struct FieldSystem *fieldSystem)
{
    struct UnkSaveStruct_0202376C_sub* rtc_info = Save_SysInfo_RTC_Get(fieldSystem->saveData);

    return rtc_info->time.hour;
}

u32 Script_GetMinute(struct FieldSystem *fieldSystem)
{
    struct UnkSaveStruct_0202376C_sub* rtc_info = Save_SysInfo_RTC_Get(fieldSystem->saveData);

    return rtc_info->time.minute;
}

void Script_SavRTC_x24toDateTime(struct FieldSystem *fieldSystem, struct RTCDate* date, struct RTCTime* time)
{
    struct UnkSaveStruct_0202376C_sub* rtc_info = Save_SysInfo_RTC_Get(fieldSystem->saveData);

    RTC_ConvertSecondToDateTime(date, time, rtc_info->secondsSinceNitroEpoch);
}

void Script_SavRTC_x2CtoDateTime(struct FieldSystem *fieldSystem, struct RTCDate* date, struct RTCTime* time)
{
    struct UnkSaveStruct_0202376C_sub* rtc_info = Save_SysInfo_RTC_Get(fieldSystem->saveData);

    RTC_ConvertSecondToDateTime(date, time, rtc_info->field_2C);
}

void Script_SavRTC_DateTimeTox2C(struct FieldSystem *fieldSystem)
{
    struct UnkSaveStruct_0202376C_sub* rtc_info = Save_SysInfo_RTC_Get(fieldSystem->saveData);

    rtc_info->field_2C = GF_RTC_DateTimeToSec();
}

BOOL FUN_0204B33C(struct FieldSystem *fieldSystem)
{
    struct UnkSaveStruct_0202376C_sub* rtc_info = Save_SysInfo_RTC_Get(fieldSystem->saveData);

    return FUN_02023874(rtc_info);
}
