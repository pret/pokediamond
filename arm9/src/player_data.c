#include "global.h"
#include "save.h"
#include "player_data.h"
#include "MI_memory.h"
#include "heap.h"
#include "string16.h"
#include "options.h"
#include "coins.h"

void PlayerProfile_Init(struct PlayerData * data);

u32 Save_PlayerData_sizeof(void)
{
    return sizeof(struct PlayerDataSav);
}

void Save_PlayerData_Init(struct PlayerDataSav * pds)
{
    MI_CpuClearFast(pds, sizeof(struct PlayerDataSav));
    Options_Init(&pds->options);
    PlayerProfile_Init(&pds->data);
    InitCoins(&pds->coins);
    InitIGT(&pds->igt);
}

struct PlayerData * Save_PlayerData_GetProfileAddr(struct SaveData * save)
{
    return &((struct PlayerDataSav *)SaveArray_Get(save, 1))->data;
}

struct Options * Save_PlayerData_GetOptionsAddr(struct SaveData * save)
{
    return &((struct PlayerDataSav *)SaveArray_Get(save, 1))->options;
}

u16 * Save_PlayerData_GetCoinsAddr(struct SaveData * save)
{
    return &((struct PlayerDataSav *)SaveArray_Get(save, 1))->coins;
}

struct IGT * Save_PlayerData_GetIGTAddr(struct SaveData * save)
{
    return &((struct PlayerDataSav *)SaveArray_Get(save, 1))->igt;
}

u32 PlayerProfile_sizeof(void)
{
    return sizeof(struct PlayerData);
}

struct PlayerData * PlayerProfile_New(u32 heap_id)
{
    struct PlayerData * ret = (struct PlayerData *)AllocFromHeap(heap_id, sizeof(struct PlayerData));
    PlayerProfile_Init(ret);
    return ret;
}

void PlayerProfile_Copy(const struct PlayerData * src, struct PlayerData * dest)
{
    MI_CpuCopy8(src, dest, sizeof(struct PlayerData));
}

void PlayerProfile_Init(struct PlayerData * data)
{
    memset(data, 0, sizeof(struct PlayerData));
    data->language = LANGUAGE_ENGLISH;
}

void CopyPlayerName(u16 * dest, struct PlayerData * data)
{
    GF_ASSERT((s32)StringLength(data->playerName) < PLAYER_NAME_LENGTH + 1);
    CopyU16StringArray(dest, data->playerName);
}

void PlayerName_StringToFlat(struct PlayerData * data, struct String * str)
{
    CopyStringToU16Array(str, data->playerName, PLAYER_NAME_LENGTH + 1);
}

u16 * PlayerProfile_GetNamePtr(struct PlayerData * data)
{
    return data->playerName;
}

void PlayerName_FlatToString(struct PlayerData * data, struct String * str)
{
    CopyU16ArrayToString(str, data->playerName);
}

struct String * PlayerProfile_GetPlayerName_NewString(struct PlayerData * data, u32 heap_id)
{
    struct String * str = String_New(PLAYER_NAME_LENGTH + 1, heap_id);
    PlayerName_FlatToString(data, str);
    return str;
}

void PlayerProfile_SetTrainerID(struct PlayerData * data, u32 otid)
{
    data->playerId = otid;
}

u32 PlayerProfile_GetTrainerID(struct PlayerData * data)
{
    return data->playerId;
}

u16 PlayerProfile_GetTrainerID_VisibleHalf(struct PlayerData * data)
{
    return (u16)data->playerId;
}

void PlayerProfile_SetTrainerGender(struct PlayerData * data, GenderEnum gender)
{
    data->gender = gender;
}

GenderEnum PlayerProfile_GetTrainerGender(struct PlayerData * data)
{
    return (GenderEnum)data->gender;
}

BOOL PlayerProfile_TestBadgeFlag(struct PlayerData * data, u32 badgeno)
{
    return (data->badges & (1 << badgeno)) != 0;
}

void PlayerProfile_SetBadgeFlag(struct PlayerData * data, u32 badgeno)
{
    data->badges |= (1 << badgeno);
}

u32 PlayerProfile_CountBadges(struct PlayerData * data)
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

u32 PlayerProfile_GetMoney(struct PlayerData * data)
{
    return data->money;
}

u32 PlayerProfile_SetMoney(struct PlayerData * data, u32 amount)
{
    if (amount > MAX_MONEY)
        amount = MAX_MONEY;
    data->money = amount;
    return amount;
}

u8 PlayerProfile_GetAvatar(struct PlayerData * data)
{
    return data->avatar;
}

void PlayerProfile_SetAvatar(struct PlayerData * data, u8 avatar)
{
    data->avatar = avatar;
}

u32 PlayerProfile_AddMoney(struct PlayerData * data, u32 amount)
{
    if (amount > MAX_MONEY)
        data->money = MAX_MONEY;
    else
        data->money += amount;
    if (data->money > MAX_MONEY)
        data->money = MAX_MONEY;
    return data->money;
}

u32 PlayerProfile_SubMoney(struct PlayerData * data, u32 amount)
{
    if (data->money < amount)
        data->money = 0;
    else
        data->money -= amount;
    return data->money;
}

u8 PlayerProfile_GetVersion(struct PlayerData * data)
{
    return data->version;
}

void PlayerProfile_SetVersion(struct PlayerData * data, u8 a1)
{
    data->version = a1;
}

u8 PlayerProfile_GetLanguage(struct PlayerData * data)
{
    return data->language;
}

void PlayerProfile_SetLanguage(struct PlayerData * data, u8 language)
{
    data->language = language;
}

void PlayerProfile_SetGameClearFlag(struct PlayerData * data)
{
    data->gameCleared = TRUE;
}

BOOL PlayerProfile_GetGameClearFlag(struct PlayerData * data)
{
    return data->gameCleared;
}

void PlayerProfile_SetNatDexFlag(struct PlayerData * data)
{
    data->nationalDex = TRUE;
}

BOOL PlayerProfile_GetNatDexFlag(struct PlayerData * data)
{
    return data->nationalDex;
}

BOOL PlayerProfile_NameAndOTIDMatchPlayer(struct PlayerData * a, struct PlayerData * b)
{
    return !StringNotEqualN(a->playerName, b->playerName, PLAYER_NAME_LENGTH) && a->playerId == b->playerId;
}
