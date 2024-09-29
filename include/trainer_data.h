#ifndef POKEDIAMOND_TRAINER_DATA_H
#define POKEDIAMOND_TRAINER_DATA_H

#include "global.h"

#include "constants/pokemon.h"

#include "heap.h"
#include "save.h"
#include "string16.h"

struct TrainerMonSpecies {
    u16 difficulty;
    u16 level;
    u16 species;
};

struct TrainerMonSpeciesMoves {
    u16 difficulty;
    u16 level;
    u16 species;
    u16 moves[MAX_MON_MOVES];
};

struct TrainerMonSpeciesItem {
    u16 difficulty;
    u16 level;
    u16 species;
    u16 item;
};

struct TrainerMonSpeciesItemMoves {
    u16 difficulty;
    u16 level;
    u16 species;
    u16 item;
    u16 moves[MAX_MON_MOVES];
};

union TrainerMon {
    struct TrainerMonSpecies species;
    struct TrainerMonSpeciesMoves species_moves;
    struct TrainerMonSpeciesItem species_item;
    struct TrainerMonSpeciesItemMoves species_item_moves;
};

#define TRTYPE_MON            0
#define TRTYPE_MON_MOVES      1
#define TRTYPE_MON_ITEM       2
#define TRTYPE_MON_ITEM_MOVES 3

typedef struct TrainerData {
    u8 trainerType;
    u8 trainerClass;
    u8 unk_2;
    u8 npoke;
    u16 items[4];
    u32 aiFlags;
    u32 doubleBattle;
} TrainerData;

typedef struct Trainer {
    struct TrainerData data;
    u16 name[PLAYER_NAME_LENGTH + 1];
    u8 padding[16];
} Trainer;

typedef struct BattleSetup BattleSetup;

void EnemyTrainerSet_Init(BattleSetup *setup, struct SaveData *r4, HeapID heapId);
s32 TrainerData_GetAttr(u32 tr_idx, u32 attr_no);
BOOL TrainerMessageWithIdPairExists(u32 pos, u32 idx, HeapID heapId);
void GetTrainerMessageByIdPair(u32 pos, u32 idx, struct String *str, HeapID heapId);
void TrainerData_ReadTrData(u32 idx, struct TrainerData *dest);
void TrainerData_ReadTrPoke(u32 idx, union TrainerMon *dest);
int TrainerClass_GetGenderOrTrainerCount(int a0);
void CreateNPCTrainerParty(BattleSetup *setup, s32 party_id, HeapID heapId);

#endif // POKEDIAMOND_TRAINER_DATA_H
