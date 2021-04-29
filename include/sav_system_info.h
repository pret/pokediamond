#ifndef POKEDIAMOND_SAV_SYSTEM_INFO_H
#define POKEDIAMOND_SAV_SYSTEM_INFO_H

#include "RTC_api.h"

struct SaveBlock2;

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

struct SavSysInfo
{
    /* 0x00 */ s64 rtcOffset;
    /* 0x08 */ u8 macAddr[6];
    /* 0x0E */ u8 birthMonth;
    /* 0x0F */ u8 birthDay;
    /* 0x10 */ struct UnkSaveStruct_0202376C_sub rtcInfo;
    /* 0x48 */ u8 field_48;
               u8 filler_49[3];
    /* 0x4C */ u32 field_4C;
               u8 padding_50[12];
};

u32 Sav2_SysInfo_sizeof(void);
void Sav2_SysInfo_init(struct SavSysInfo * unk);
struct SavSysInfo * Sav2_SysInfo_get(struct SaveBlock2 * sav2);
struct UnkSaveStruct_0202376C_sub * Sav2_SysInfo_RTC_get(struct SaveBlock2 * sav2);
void Sav2_SysInfo_InitFromSystem(struct SavSysInfo * unk);
BOOL Sav2_SysInfo_MacAddressIsMine(struct SavSysInfo * unk);
BOOL Sav2_SysInfo_RTCOffsetIsMine(struct SavSysInfo * unk);
u8 Sav2_SysInfo_GetBirthMonth(struct SavSysInfo * unk);
u8 Sav2_SysInfo_GetBirthDay(struct SavSysInfo * unk);
u8 FUN_02023820(struct SavSysInfo * unk);
void FUN_02023828(struct SavSysInfo * unk, u8 val);
u32 FUN_02023830(struct SavSysInfo * unk);
void FUN_02023834(struct SavSysInfo * unk, u32 val);
void Sav2_SysInfo_RTC_init(struct UnkSaveStruct_0202376C_sub * sub);
BOOL FUN_02023874(struct UnkSaveStruct_0202376C_sub * sub);
void FUN_02023884(struct UnkSaveStruct_0202376C_sub * sub, u32 a1);
void FUN_020238A4(struct UnkSaveStruct_0202376C_sub * sub);

#endif //POKEDIAMOND_SAV_SYSTEM_INFO_H
