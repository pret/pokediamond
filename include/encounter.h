#ifndef POKEDIAMOND_ENCOUNTER_H
#define POKEDIAMOND_ENCOUNTER_H

#include "battle_setup.h"
#include "field_system.h"
#include "party.h"
#include "task.h"

typedef struct Encounter {
    u32 *winFlag;
    s32 effect;
    s32 bgm;
    s32 unkC;
    BattleSetup *setup;
} Encounter;

typedef struct WildEncounter {
    s32 state;
    s32 effect;
    s32 bgm;
    u32 *winFlag;
    BattleSetup *setup;
} WildEncounter;

void sub_02046948(TaskManager *taskManager, u32 param1, u32 *winFlag);
void sub_020469B8(FieldSystem *fieldSystem, BattleSetup *setup);
void sub_02046A20(FieldSystem *fieldSystem, TaskManager *taskManager, BattleSetup *setup);
void SetupAndStartHoneyTreeBattle(TaskManager *taskManager, u32 *winFlag);
void SetupAndStartWildBattle(TaskManager *taskManager, u16 species, u8 level, u32 *winFlag, BOOL canFlee);
void sub_02046F70(FieldSystem *fieldSystem, BattleSetup *setup);
void SetupAndStartFirstBattle(TaskManager *taskManager, u16 species, u8 level);
void SetupAndStartTutorialBattle(TaskManager *taskManager);
void SetupAndStartTrainerBattle(TaskManager *taskManager, u32 opponentTrainer1, u32 opponentTrainer2, u32 followerTrainerNum, HeapID heapId, u32 *winFlag);

#endif //POKEDIAMOND_ENCOUNTER_H