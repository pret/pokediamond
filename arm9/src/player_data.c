#include "global.h"
#include "save_block_2.h"
#include "player_data.h"
#include "MI_memory.h"
#include "heap.h"
#include "string16.h"
#include "options.h"
#include "coins.h"

#pragma thumb on

void PlayerProfile_init(struct PlayerData * data);

u32 Sav2_PlayerData_sizeof(void)
{
    return sizeof(struct PlayerDataSav);
}

void Sav2_PlayerData_init(struct PlayerDataSav * pds)
{
    MI_CpuClearFast(pds, sizeof(struct PlayerDataSav));
    Options_init(&pds->options);
    PlayerProfile_init(&pds->data);
    InitCoins(&pds->coins);
    InitIGT(&pds->igt);
}

struct PlayerData * Sav2_PlayerData_GetProfileAddr(struct SaveBlock2 * sav2)
{
    return &((struct PlayerDataSav *)SavArray_get(sav2, 1))->data;
}

struct Options * Sav2_PlayerData_GetOptionsAddr(struct SaveBlock2 * sav2)
{
    return &((struct PlayerDataSav *)SavArray_get(sav2, 1))->options;
}

u16 * Sav2_PlayerData_GetCoinsAddr(struct SaveBlock2 * sav2)
{
    return &((struct PlayerDataSav *)SavArray_get(sav2, 1))->coins;
}

struct IGT * Sav2_PlayerData_GetIGTAddr(struct SaveBlock2 * sav2)
{
    return &((struct PlayerDataSav *)SavArray_get(sav2, 1))->igt;
}

u32 PlayerProfile_sizeof(void)
{
    return sizeof(struct PlayerData);
}

struct PlayerData * PlayerProfile_new(u32 heap_id)
{
    struct PlayerData * ret = (struct PlayerData *)AllocFromHeap(heap_id, sizeof(struct PlayerData));
    PlayerProfile_init(ret);
    return ret;
}

void PlayerProfile_Copy(const struct PlayerData * src, struct PlayerData * dest)
{
    MI_CpuCopy8(src, dest, sizeof(struct PlayerData));
}

void PlayerProfile_init(struct PlayerData * data)
{
    memset(data, 0, sizeof(struct PlayerData));
    data->language = LANGUAGE_ENGLISH;
}

void CopyPlayerName(u16 * dest, struct PlayerData * data)
{
    GF_ASSERT((s32)StringLength(data->playerName) < OT_NAME_LENGTH + 1);
    CopyU16StringArray(dest, data->playerName);
}

void PlayerName_StringToFlat(struct PlayerData * data, struct String * str)
{
    CopyStringToU16Array(str, data->playerName, OT_NAME_LENGTH + 1);
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
    struct String * str = String_ctor(OT_NAME_LENGTH + 1, heap_id);
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
    return data->gender;
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
    if (amount > 999999)
        amount = 999999;
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
    if (amount > 999999)
        data->money = 999999;
    else
        data->money += amount;
    if (data->money > 999999)
        data->money = 999999;
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
    data->gameCleared = 1;
}

BOOL PlayerProfile_GetGameClearFlag(struct PlayerData * data)
{
    return data->gameCleared;
}

void PlayerProfile_SetNatDexFlag(struct PlayerData * data)
{
    data->nationalDex = 1;
}

BOOL PlayerProfile_GetNatDexFlag(struct PlayerData * data)
{
    return data->nationalDex;
}

BOOL PlayerProfile_NameAndOTIDMatchPlayer(struct PlayerData * a, struct PlayerData * b)
{
    return !StringNotEqualN(a->playerName, b->playerName, OT_NAME_LENGTH) && a->playerId == b->playerId;
}
