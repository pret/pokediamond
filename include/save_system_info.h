#ifndef POKEDIAMOND_SAVE_SYSTEM_INFO_H
#define POKEDIAMOND_SAVE_SYSTEM_INFO_H

#include "RTC_api.h"
#include "nitro/types.h"

struct SaveData;

struct UnkSaveStruct_0202376C_sub
{
    /* 0x00 */ u32 field_00;
    /* 0x04 */ RTCDate date;
    /* 0x14 */ RTCTime time;
    /* 0x20 */ s32 daysSinceNitroEpoch;
    /* 0x24 */ s64 secondsSinceNitroEpoch;
    /* 0x2C */ s64 field_2C;
    /* 0x34 */ u32 field_34;
};

typedef struct SaveSysInfo
{
    /* 0x00 */ s64 rtcOffset;
    /* 0x08 */ u8 macAddr[6];
    /* 0x0E */ u8 birthMonth;
    /* 0x0F */ u8 birthDay;
    /* 0x10 */ struct UnkSaveStruct_0202376C_sub rtcInfo;
    /* 0x48 */ u8 mysteryGiftActive;
               u8 filler_49[3];
    /* 0x4C */ u32 field_4C;
               u8 padding_50[12];
} SaveSysInfo;

u32 Save_SysInfo_sizeof(void);
void Save_SysInfo_Init(struct SaveSysInfo * unk);
struct SaveSysInfo * Save_SysInfo_Get(struct SaveData * save);
struct UnkSaveStruct_0202376C_sub * Save_SysInfo_RTC_Get(struct SaveData * save);
void Save_SysInfo_InitFromSystem(struct SaveSysInfo * unk);
BOOL Save_SysInfo_MacAddressIsMine(struct SaveSysInfo * unk);
BOOL Save_SysInfo_RTCOffsetIsMine(struct SaveSysInfo * unk);
u8 Save_SysInfo_GetBirthMonth(struct SaveSysInfo * unk);
u8 Save_SysInfo_GetBirthDay(struct SaveSysInfo * unk);
u8 Save_SysInfo_GetMysteryGiftActive(struct SaveSysInfo * unk);
void Save_SysInfo_SetMysteryGiftActive(struct SaveSysInfo * unk, u8 val);
u32 sub_02023830(struct SaveSysInfo * unk);
void sub_02023834(struct SaveSysInfo * unk, u32 val);
void Save_SysInfo_RTC_Init(struct UnkSaveStruct_0202376C_sub * sub);
BOOL sub_02023874(struct UnkSaveStruct_0202376C_sub * sub);
void sub_02023884(struct UnkSaveStruct_0202376C_sub * sub, u32 a1);
void sub_020238A4(struct UnkSaveStruct_0202376C_sub * sub);

#endif //POKEDIAMOND_SAVE_SYSTEM_INFO_H
