#ifndef POKEDIAMOND_UNK_0204B0A0_H
#define POKEDIAMOND_UNK_0204B0A0_H

#include "RTC_api.h"
#include "RTC_convert.h"
#include "save_system_info.h"
#include "script.h"

void sub_0204B0F8(struct FieldSystem *fieldSystem);
void sub_0204B130(struct FieldSystem *fieldSystem, SysInfo_RTC* rtc_info, struct RTCDate* date);
void sub_0204B158(struct FieldSystem *fieldSystem, SysInfo_RTC* rtc_info, struct RTCDate* date, struct RTCTime* time);
void sub_0204B1DC(struct FieldSystem *fieldSystem, s32 a1);
void sub_0204B270(struct FieldSystem *fieldSystem, s32 a1, struct RTCTime* time);
u32 Script_GetTimeOfDay(struct FieldSystem *fieldSystem);
u32 Script_GetMonth(struct FieldSystem *fieldSystem);
u32 Script_GetDay(struct FieldSystem *fieldSystem);
RTCWeek Script_GetWeekday(struct FieldSystem *fieldSystem);
u32 Script_GetHour(struct FieldSystem *fieldSystem);
u32 Script_GetMinute(struct FieldSystem *fieldSystem);
void Script_SavRTC_x24toDateTime(struct FieldSystem *fieldSystem, struct RTCDate* date, struct RTCTime* time);
void Script_SavRTC_x2CtoDateTime(struct FieldSystem *fieldSystem, struct RTCDate* date, struct RTCTime* time);
void Script_SavRTC_DateTimeTox2C(struct FieldSystem *fieldSystem);
BOOL sub_0204B33C(struct FieldSystem *fieldSystem);

#endif
