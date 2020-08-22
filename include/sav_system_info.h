#ifndef POKEDIAMOND_SAV_SYSTEM_INFO_H
#define POKEDIAMOND_SAV_SYSTEM_INFO_H

struct UnkSaveStruct_0202376C_sub
{
    u32 field_00;
    RTCDate date;
    RTCTime time;
    s32 daysSinceNitroEpoch;
    s64 secondsSinceNitroEpoch;
    u32 field_2C;
    u32 field_30;
    u32 field_34;
};

struct UnkSaveStruct_0202376C
{
    s64 rtcOffset;
    u8 macAddr[6];
    u8 birthMonth;
    u8 birthDay;
    struct UnkSaveStruct_0202376C_sub rtcInfo;
    u8 field_48;
    u8 filler_49[3];
    u32 field_4C;
    u8 padding_50[12];
};

u32 FUN_0202376C(void);
void FUN_02023770(struct UnkSaveStruct_0202376C * unk);
struct UnkSaveStruct_0202376C * FUN_02023788(struct SaveBlock2 * sav2);
struct UnkSaveStruct_0202376C_sub * FUN_02023794(struct SaveBlock2 * sav2);
void FUN_020237A0(struct UnkSaveStruct_0202376C * unk);
BOOL FUN_020237CC(struct UnkSaveStruct_0202376C * unk);
BOOL FUN_020237FC(struct UnkSaveStruct_0202376C * unk);
u8 FUN_02023818(struct UnkSaveStruct_0202376C * unk);
u8 FUN_0202381C(struct UnkSaveStruct_0202376C * unk);
u8 FUN_02023820(struct UnkSaveStruct_0202376C * unk);
void FUN_02023828(struct UnkSaveStruct_0202376C * unk, u8 val);
u32 FUN_02023830(struct UnkSaveStruct_0202376C * unk);
void FUN_02023834(struct UnkSaveStruct_0202376C * unk, u32 val);
void FUN_02023840(struct UnkSaveStruct_0202376C_sub * sub);
BOOL FUN_02023874(struct UnkSaveStruct_0202376C_sub * sub);
void FUN_02023884(struct UnkSaveStruct_0202376C_sub * sub, u32 a1);
void FUN_020238A4(struct UnkSaveStruct_0202376C_sub * sub);

#endif //POKEDIAMOND_SAV_SYSTEM_INFO_H
