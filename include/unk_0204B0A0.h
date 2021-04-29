#ifndef POKEDIAMOND_UNK_0204B0A0_H
#define POKEDIAMOND_UNK_0204B0A0_H

#include "RTC_api.h"
#include "RTC_convert.h"
#include "sav_system_info.h"
#include "script.h"

void FUN_0204B0F8(struct UnkSavStruct80* unk);
void FUN_0204B130(struct UnkSavStruct80* unk, struct UnkSaveStruct_0202376C_sub* rtc_info, struct RTCDate* date);
void FUN_0204B158(struct UnkSavStruct80* unk, struct UnkSaveStruct_0202376C_sub* rtc_info, struct RTCDate* date, struct RTCTime* time);
void FUN_0204B1DC(struct UnkSavStruct80* unk, s32 a1);
void FUN_0204B270(struct UnkSavStruct80* unk, s32 a1, struct RTCTime* time);
u32 Script_GetTimeOfDay(struct UnkSavStruct80* unk);
u32 Script_GetMonth(struct UnkSavStruct80* unk);
u32 Script_GetDay(struct UnkSavStruct80* unk);
RTCWeek Script_GetWeekday(struct UnkSavStruct80* unk);
u32 Script_GetHour(struct UnkSavStruct80* unk);
u32 Script_GetMinute(struct UnkSavStruct80* unk);
void Script_SavRTC_x24toDateTime(struct UnkSavStruct80* unk, struct RTCDate* date, struct RTCTime* time);
void Script_SavRTC_x2CtoDateTime(struct UnkSavStruct80* unk, struct RTCDate* date, struct RTCTime* time);
void Script_SavRTC_DateTimeTox2C(struct UnkSavStruct80* unk);
BOOL FUN_0204B33C(struct UnkSavStruct80* unk);

#endif
