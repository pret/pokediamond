#ifndef POKEDIAMOND_PLAYER_DATA_H
#define POKEDIAMOND_PLAYER_DATA_H

#include "options.h"
#include "igt.h"

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
    /* 0x1C */ u8 field_1C;
    /* 0x1D */ u8 field_1D_0:1;
               u8 field_1D_1:1;
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

struct Options * LoadPlayerDataAddress(struct SaveBlock2 *);
struct String * PlayerData_GetPlayerName_NewString(struct PlayerData *, u32 heap_id);
u32 PlayerData_GetTrainerID(struct PlayerData *);
u32 PlayerData_GetTrainerGender(struct PlayerData *);

#endif //POKEDIAMOND_PLAYER_DATA_H
