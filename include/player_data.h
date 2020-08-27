#ifndef POKEDIAMOND_PLAYER_DATA_H
#define POKEDIAMOND_PLAYER_DATA_H

#include "options.h"
#include "igt.h"
#include "string16.h"

struct SaveBlock2;

struct PlayerData
{
    /* 0x00 */ u16 playerName[OT_NAME_LENGTH + 1];
    /* 0x10 */ u32 playerId;
    /* 0x14 */ u32 money;
    /* 0x18 */ u8 gender;
    /* 0x19 */ u8 language;
    /* 0x1A */ u8 badges;
    /* 0x1B */ u8 avatar;
    /* 0x1C */ u8 version;
    /* 0x1D */ u8 gameCleared:1;
               u8 nationalDex:1;
               u8 field_1D_pad:6;
    /* 0x1E */ u8 padding_1E[2];
};

struct PlayerDataSav
{
    struct Options options;
    u8 padding[2];
    struct PlayerData data;
    u16 coins;
    struct IGT igt;
    u8 padding2[2];
};

u32 Sav2_PlayerData_sizeof(void);
void Sav2_PlayerData_init(struct PlayerDataSav * pds);
struct PlayerData * Sav2_PlayerData_GetProfileAddr(struct SaveBlock2 * sav2);
struct Options * Sav2_PlayerData_GetOptionsAddr(struct SaveBlock2 * sav2);
u16 * Sav2_PlayerData_GetCoinsAddr(struct SaveBlock2 * sav2);
struct IGT * Sav2_PlayerData_GetIGTAddr(struct SaveBlock2 * sav2);
u32 PlayerProfile_sizeof(void);
struct PlayerData * PlayerProfile_new(u32 heap_id);
void PlayerProfile_Copy(const struct PlayerData * src, struct PlayerData * dest);
void PlayerProfile_init(struct PlayerData * data);
void CopyPlayerName(u16 * dest, struct PlayerData * data);
void PlayerName_StringToFlat(struct PlayerData * data, struct String * str);
u16 * PlayerProfile_GetNamePtr(struct PlayerData * data);
void PlayerName_FlatToString(struct PlayerData * data, struct String * str);
struct String * PlayerProfile_GetPlayerName_NewString(struct PlayerData * data, u32 heap_id);
void PlayerProfile_SetTrainerID(struct PlayerData * data, u32 otid);
u32 PlayerProfile_GetTrainerID(struct PlayerData * data);
u16 PlayerProfile_GetTrainerID_VisibleHalf(struct PlayerData * data);
void PlayerProfile_SetTrainerGender(struct PlayerData * data, u8 gender);
u32 PlayerProfile_GetTrainerGender(struct PlayerData * data);
BOOL PlayerProfile_TestBadgeFlag(struct PlayerData * data, u32 badgeno);
void PlayerProfile_SetBadgeFlag(struct PlayerData * data, u32 badgeno);
u32 PlayerProfile_CountBadges(struct PlayerData * data);
u32 PlayerProfile_GetMoney(struct PlayerData * data);
u32 PlayerProfile_SetMoney(struct PlayerData * data, u32 amount);
u8 PlayerProfile_GetAvatar(struct PlayerData * data);
void PlayerProfile_SetAvatar(struct PlayerData * data, u8 avatar);
u32 PlayerProfile_AddMoney(struct PlayerData * data, u32 amount);
u32 PlayerProfile_SubMoney(struct PlayerData * data, u32 amount);
u8 PlayerProfile_GetVersion(struct PlayerData * data);
void PlayerProfile_SetVersion(struct PlayerData * data, u8 a1);
u8 PlayerProfile_GetLanguage(struct PlayerData * data);
void PlayerProfile_SetLanguage(struct PlayerData * data, u8 language);
void PlayerProfile_SetGameClearFlag(struct PlayerData * data);
BOOL PlayerProfile_GetGameClearFlag(struct PlayerData * data);
void PlayerProfile_SetNatDexFlag(struct PlayerData * data);
BOOL PlayerProfile_GetNatDexFlag(struct PlayerData * data);
BOOL PlayerProfile_NameAndOTIDMatchPlayer(struct PlayerData * a, struct PlayerData * b);

#endif //POKEDIAMOND_PLAYER_DATA_H
