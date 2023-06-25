#include "global.h"
#include "save.h"
#include "player_data.h"
#include "MI_memory.h"
#include "heap.h"
#include "string16.h"
#include "options.h"
#include "coins.h"

void PlayerProfile_Init(PlayerProfile *data);

u32 Save_PlayerData_sizeof(void)
{
    return sizeof(PlayerData);
}

void Save_PlayerData_Init(PlayerData * pds)
{
    MI_CpuClearFast(pds, sizeof(PlayerData));
    Options_Init(&pds->options);
    PlayerProfile_Init(&pds->profile);
    InitCoins(&pds->coins);
    InitIGT(&pds->igt);
}

PlayerProfile * Save_PlayerData_GetProfileAddr(struct SaveData * save)
{
    return &((PlayerData *)SaveArray_Get(save, 1))->profile;
}

struct Options * Save_PlayerData_GetOptionsAddr(struct SaveData * save)
{
    return &((PlayerData *)SaveArray_Get(save, 1))->options;
}

u16 * Save_PlayerData_GetCoinsAddr(struct SaveData * save)
{
    return &((PlayerData *)SaveArray_Get(save, 1))->coins;
}

struct IGT * Save_PlayerData_GetIGTAddr(struct SaveData * save)
{
    return &((PlayerData *)SaveArray_Get(save, 1))->igt;
}

u32 PlayerProfile_sizeof(void)
{
    return sizeof(PlayerProfile);
}

PlayerProfile * PlayerProfile_New(HeapID heapId)
{
    PlayerProfile * ret = (PlayerProfile *)AllocFromHeap(heapId, sizeof(PlayerProfile));
    PlayerProfile_Init(ret);
    return ret;
}

void PlayerProfile_Copy(const PlayerProfile * src, PlayerProfile * dest)
{
    MI_CpuCopy8(src, dest, sizeof(PlayerProfile));
}

void PlayerProfile_Init(PlayerProfile * data)
{
    memset(data, 0, sizeof(PlayerProfile));
    data->language = LANGUAGE_ENGLISH;
}

void CopyPlayerName(u16 * dest, PlayerProfile * data)
{
    GF_ASSERT((s32)StringLength(data->playerName) < PLAYER_NAME_LENGTH + 1);
    CopyU16StringArray(dest, data->playerName);
}

void PlayerName_StringToFlat(PlayerProfile * data, struct String * str)
{
    CopyStringToU16Array(str, data->playerName, PLAYER_NAME_LENGTH + 1);
}

u16 * PlayerProfile_GetNamePtr(PlayerProfile * data)
{
    return data->playerName;
}

void PlayerName_FlatToString(PlayerProfile * data, struct String * str)
{
    CopyU16ArrayToString(str, data->playerName);
}

struct String * PlayerProfile_GetPlayerName_NewString(PlayerProfile * data, HeapID heapId)
{
    struct String * str = String_New(PLAYER_NAME_LENGTH + 1, heapId);
    PlayerName_FlatToString(data, str);
    return str;
}

void PlayerProfile_SetTrainerID(PlayerProfile * data, u32 otid)
{
    data->playerId = otid;
}

u32 PlayerProfile_GetTrainerID(PlayerProfile * data)
{
    return data->playerId;
}

u16 PlayerProfile_GetTrainerID_VisibleHalf(PlayerProfile * data)
{
    return (u16)data->playerId;
}

void PlayerProfile_SetTrainerGender(PlayerProfile * data, PlayerGender gender)
{
    data->gender = gender;
}

PlayerGender PlayerProfile_GetTrainerGender(PlayerProfile * data)
{
    return (PlayerGender)data->gender;
}

BOOL PlayerProfile_TestBadgeFlag(PlayerProfile * data, u32 badgeno)
{
    return (data->badges & (1 << badgeno)) != 0;
}

void PlayerProfile_SetBadgeFlag(PlayerProfile * data, u32 badgeno)
{
    data->badges |= (1 << badgeno);
}

u32 PlayerProfile_CountBadges(PlayerProfile * data)
{
    u32 count;
    u32 badges;
    for (count = 0, badges = data->badges; badges != 0; badges >>= 1)
    {
        if (badges & 1)
            count++;
    }
    return count;
}

u32 PlayerProfile_GetMoney(PlayerProfile * data)
{
    return data->money;
}

u32 PlayerProfile_SetMoney(PlayerProfile * data, u32 amount)
{
    if (amount > MAX_MONEY)
        amount = MAX_MONEY;
    data->money = amount;
    return amount;
}

u8 PlayerProfile_GetAvatar(PlayerProfile * data)
{
    return data->avatar;
}

void PlayerProfile_SetAvatar(PlayerProfile * data, u8 avatar)
{
    data->avatar = avatar;
}

u32 PlayerProfile_AddMoney(PlayerProfile * data, u32 amount)
{
    if (amount > MAX_MONEY)
        data->money = MAX_MONEY;
    else
        data->money += amount;
    if (data->money > MAX_MONEY)
        data->money = MAX_MONEY;
    return data->money;
}

u32 PlayerProfile_SubMoney(PlayerProfile * data, u32 amount)
{
    if (data->money < amount)
        data->money = 0;
    else
        data->money -= amount;
    return data->money;
}

u8 PlayerProfile_GetVersion(PlayerProfile * data)
{
    return data->version;
}

void PlayerProfile_SetVersion(PlayerProfile * data, u8 a1)
{
    data->version = a1;
}

u8 PlayerProfile_GetLanguage(PlayerProfile * data)
{
    return data->language;
}

void PlayerProfile_SetLanguage(PlayerProfile * data, u8 language)
{
    data->language = language;
}

void PlayerProfile_SetGameClearFlag(PlayerProfile * data)
{
    data->gameCleared = TRUE;
}

BOOL PlayerProfile_GetGameClearFlag(PlayerProfile * data)
{
    return data->gameCleared;
}

void PlayerProfile_SetNatDexFlag(PlayerProfile * data)
{
    data->nationalDex = TRUE;
}

BOOL PlayerProfile_GetNatDexFlag(PlayerProfile * data)
{
    return data->nationalDex;
}

BOOL PlayerProfile_NameAndOTIDMatchPlayer(PlayerProfile * a, PlayerProfile * b)
{
    return !StringNotEqualN(a->playerName, b->playerName, PLAYER_NAME_LENGTH) && a->playerId == b->playerId;
}
