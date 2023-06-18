#ifndef POKEDIAMOND_TRAINER_DATA_H
#define POKEDIAMOND_TRAINER_DATA_H

#include "global.h"
#include "save.h"
#include "string16.h"
#include "constants/pokemon.h"

struct TrainerMonSpecies
{
    u16 difficulty;
    u16 level;
    u16 species;
};

struct TrainerMonSpeciesMoves
{
    u16 difficulty;
    u16 level;
    u16 species;
    u16 moves[MON_MOVES];
};

struct TrainerMonSpeciesItem
{
    u16 difficulty;
    u16 level;
    u16 species;
    u16 item;
};

struct TrainerMonSpeciesItemMoves
{
    u16 difficulty;
    u16 level;
    u16 species;
    u16 item;
    u16 moves[MON_MOVES];
};

union TrainerMon
{
    struct TrainerMonSpecies species;
    struct TrainerMonSpeciesMoves species_moves;
    struct TrainerMonSpeciesItem species_item;
    struct TrainerMonSpeciesItemMoves species_item_moves;
};

#define TRTYPE_MON 0
#define TRTYPE_MON_MOVES 1
#define TRTYPE_MON_ITEM 2
#define TRTYPE_MON_ITEM_MOVES 3

struct TrainerData
{
    u8 trainerType;
    u8 trainerClass;
    u8 unk_2;
    u8 npoke;
    u16 items[4];
    u32 unk_C;
    u32 doubleBattle;
};

struct TrainerDataLoaded
{
    struct TrainerData data;
    u16 name[PLAYER_NAME_LENGTH + 1];
    u8 padding[16];
};

struct BattleSetupStruct
{
    u32 flags;
    struct PlayerParty * parties[4];
    u16 field_14[2];
    u32 trainer_idxs[4];
    struct TrainerDataLoaded datas[4];
};

void EnemyTrainerSet_Init(struct BattleSetupStruct * sp0, struct SaveData * r4, u32 sp4);
s32 TrainerData_GetAttr(u32 tr_idx, u32 attr_no);
BOOL TrainerMessageWithIdPairExists(u32 pos, u32 idx, u32 heap_id);
void GetTrainerMessageByIdPair(u32 pos, u32 idx, struct String * str, u32 heap_id);
void TrainerData_ReadTrData(u32 idx, struct TrainerData * dest);
void TrainerData_ReadTrPoke(u32 idx, union TrainerMon * dest);
int TrainerClass_GetGenderOrTrainerCount(int a0);
void CreateNPCTrainerParty(struct BattleSetupStruct * enemies, s32 party_id, u32 heap_id);

#endif //POKEDIAMOND_TRAINER_DATA_H
