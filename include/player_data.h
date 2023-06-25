#ifndef POKEDIAMOND_PLAYER_DATA_H
#define POKEDIAMOND_PLAYER_DATA_H

#include "options.h"
#include "igt.h"
#include "string16.h"

struct SaveData;

#define MAX_MONEY 999999

typedef enum PlayerGender
{
    PLAYER_GENDER_MALE = 0,
    PLAYER_GENDER_FEMALE = 1
} PlayerGender;

typedef struct PlayerProfile
{
    /* 0x00 */ u16 playerName[PLAYER_NAME_LENGTH + 1];
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
} PlayerProfile;

typedef struct PlayerData
{
    struct Options options;
    u8 padding[2];
    PlayerProfile profile;
    u16 coins;
    struct IGT igt;
    u8 padding2[2];
} PlayerData;

u32 Save_PlayerData_sizeof(void);
void Save_PlayerData_Init(PlayerData * data);
PlayerProfile * Save_PlayerData_GetProfileAddr(struct SaveData * save);
struct Options * Save_PlayerData_GetOptionsAddr(struct SaveData * save);
u16 * Save_PlayerData_GetCoinsAddr(struct SaveData * save);
struct IGT * Save_PlayerData_GetIGTAddr(struct SaveData * save);
u32 PlayerProfile_sizeof(void);
PlayerProfile * PlayerProfile_New(HeapID heapId);
void PlayerProfile_Copy(const PlayerProfile * src, PlayerProfile * dest);
void PlayerProfile_Init(PlayerProfile * data);
void CopyPlayerName(u16 * dest, PlayerProfile * data);
void PlayerName_StringToFlat(PlayerProfile * data, struct String * str);
u16 * PlayerProfile_GetNamePtr(PlayerProfile * data);
void PlayerName_FlatToString(PlayerProfile * data, struct String * str);
struct String * PlayerProfile_GetPlayerName_NewString(PlayerProfile * data, HeapID heapId);
void PlayerProfile_SetTrainerID(PlayerProfile *playerProfile, u32 otid);
u32 PlayerProfile_GetTrainerID(PlayerProfile * data);
u16 PlayerProfile_GetTrainerID_VisibleHalf(PlayerProfile * data);
void PlayerProfile_SetTrainerGender(PlayerProfile * data, PlayerGender gender);
PlayerGender PlayerProfile_GetTrainerGender(PlayerProfile * data);
BOOL PlayerProfile_TestBadgeFlag(PlayerProfile * data, u32 badgeno);
void PlayerProfile_SetBadgeFlag(PlayerProfile * data, u32 badgeno);
u32 PlayerProfile_CountBadges(PlayerProfile * data);
u32 PlayerProfile_GetMoney(PlayerProfile * data);
u32 PlayerProfile_SetMoney(PlayerProfile * data, u32 amount);
u8 PlayerProfile_GetAvatar(PlayerProfile * data);
void PlayerProfile_SetAvatar(PlayerProfile * data, u8 avatar);
u32 PlayerProfile_AddMoney(PlayerProfile * data, u32 amount);
u32 PlayerProfile_SubMoney(PlayerProfile * data, u32 amount);
u8 PlayerProfile_GetVersion(PlayerProfile * data);
void PlayerProfile_SetVersion(PlayerProfile * data, u8 a1);
u8 PlayerProfile_GetLanguage(PlayerProfile * data);
void PlayerProfile_SetLanguage(PlayerProfile * data, u8 language);
void PlayerProfile_SetGameClearFlag(PlayerProfile * data);
BOOL PlayerProfile_GetGameClearFlag(PlayerProfile * data);
void PlayerProfile_SetNatDexFlag(PlayerProfile * data);
BOOL PlayerProfile_GetNatDexFlag(PlayerProfile * data);
BOOL PlayerProfile_NameAndOTIDMatchPlayer(PlayerProfile * a, PlayerProfile * b);

#endif //POKEDIAMOND_PLAYER_DATA_H
