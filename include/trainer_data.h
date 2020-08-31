#ifndef POKEDIAMOND_TRAINER_DATA_H
#define POKEDIAMOND_TRAINER_DATA_H

#include "global.h"
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
    u32 unk_10;
};

struct EnemyTrainerSet
{
    u32 flags;
    struct PlayerParty * parties[4];
    u16 field_14[4];
    u32 trainer_idxs[4];
    struct TrainerData datas[4];
};

#endif //POKEDIAMOND_TRAINER_DATA_H
