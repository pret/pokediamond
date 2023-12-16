#include "global.h"
#include "encounter.h"
#include "constants/battle.h"
#include "constants/game_stats.h"
#include "save_vars_flags.h"
#include "field_system.h"
#include "igt.h"
#include "task.h"
#include "unk_020040F4.h"
#include "unk_02022504.h"
#include "unk_02029FB0.h"
#include "unk_0204AEA8.h"
#include "unk_0204AF24.h"
#include "unk_0205EC84.h"
#include "unk_0205FA2C.h"
#include "use_item_on_mon.h"

extern void sub_0203780C(FieldSystem *fieldSystem, BattleSetup *battleSetup);
extern void BattleSetup_Delete(BattleSetup *setup);
extern BOOL IsBattleResultWin(u32 winFlag);
extern void sub_02047F38(BattleSetup *setup, FieldSystem *fieldSystem);
extern void sub_02061080(FieldSystem *fieldSystem, u32 param1, u32 winFlag);
extern void MapObjectManager_PauseAllMovement(MapObjectManager *mapObjectManager);
extern void MapObjectManager_UnpauseAllMovement(MapObjectManager *mapObjectManager);
extern void sub_0202E25C(SaveData *saveData, s32 param1);
extern void sub_02047FA4(BattleSetup *setup, FieldSystem *fieldSystem);
extern BattleSetup *ov06_02244558(u32 param0, FieldSystem *fieldSystem);
extern s32 sub_020475A0(BattleSetup *battleSetup);
extern s32 sub_020475B0(BattleSetup *battleSetup);
extern BOOL Task_BlackOut(TaskManager *taskManager);
extern void sub_0205DD40(u32 param0);
extern u32 sub_0205E128(u32 param0);
extern void sub_0205DED4(FieldSystem *fieldSystem, u32 winFlag, u32 param2);
extern void sub_0205DF44(FieldSystem *fieldSystem, u32 param1);
extern BOOL sub_0205DF9C(u32 param0);
extern u32 sub_0205E0A4(u32 param0);
extern void ov06_02248724(FieldSystem *fieldSystem, BattleSetup *setup);
extern void sub_02060FE0(SafariZone *safariZone, Pokemon *pokemon);
extern LocalFieldData *Save_LocalFieldData_Get(SaveData *save);
extern u16 *LocalFieldData_GetSafariBallsCounter(LocalFieldData *localFieldData);
extern Location *LocalFieldData_GetDynamicWarp(LocalFieldData *localFieldData);
extern void sub_02049160(TaskManager *taskManager, Location *location);
extern void QueueScript(TaskManager *taskManager, u16 script, LocalMapObject *lastInteracted, void *param3);
extern BattleSetup *BattleSetup_New(HeapID heapId, u32 flags);
extern void BattleSetup_InitFromFieldSystem(BattleSetup *setup, FieldSystem *fieldSystem);
extern void ov06_0223CCDC(FieldSystem *fieldSystem, BattleSetup *setup);
extern void ov06_0223CD7C(FieldSystem *fieldSystem, u16 species, u8 level, BattleSetup *setup);
extern void PalPark_HandleBattleEnd(FieldSystem *fieldSystem, BattleSetup *setup);
extern u32 PalPark_CountMonsNotCaught(FieldSystem *fieldSystem);
extern void StartScriptFromMenu(TaskManager *taskManager, u16 script, LocalMapObject *lastInteracted);
extern BattleSetup *sub_02047814(HeapID heapId, FieldSystem *fieldSystem);
extern void sub_02047F1C(BattleSetup *setup, FieldSystem *fieldSystem, void *param2);
extern void sub_02047BC0(BattleSetup *setup, FieldSystem *fieldSystem, s32 maxLevel);
extern void sub_0204FF5C(FieldSystem *fieldSystem);
extern void sub_02047D48(BattleSetup *setup, FieldSystem *fieldSystem, Party *party, void *param3);
extern void *sub_0202920C(IGT *igt, u16 species, u8 gender, u8 param3, HeapID heapId);
extern void *sub_0202918C(IGT *igt, u16 species, u8 gender, u8 param3, HeapID heapId);
extern void sub_02028AD4(u32 *param0, void *param1, u32 param2);
extern void sub_020299DC(u32 *param0, u16 mapId, u16 trainerId, HeapID heapId);

static BOOL Task_StartBattle(TaskManager *taskManager);
static void CallTask_StartBattle(TaskManager *taskManager, BattleSetup *setup);
static Encounter *Encounter_New(BattleSetup *setup, s32 effect, s32 bgm, u32 *winFlag);
static void Encounter_Delete(Encounter *encounter);
static BOOL Encounter_GetResult(Encounter *encounter);
static void sub_020465E4(BattleSetup *setup, FieldSystem *fieldSystem);
static BOOL Task_StartEncounter(TaskManager *taskManager);
static void CallTask_StartEncounter(TaskManager *taskManager, BattleSetup *setup, s32 effect, s32 bgm, u32 *winFlag);
static void sub_0204671C(s32 flag, FieldSystem *fieldSystem);
static BOOL Task_02046758(TaskManager *taskManager);
static BOOL Task_020467FC(TaskManager *taskManager);
static BOOL Task_02046878(TaskManager *taskManager);
static void CallTask_02046878(TaskManager *taskManager, BattleSetup *battleSetup, s32 effect, s32 bgm, u32 *winFlag);
static WildEncounter *WildEncounter_New(BattleSetup *setup, s32 effect, s32 bgm, u32 *winFlag);
static void WildEncounter_Delete(WildEncounter *encounter);
static BOOL Task_WildEncounter(TaskManager *taskManager);
static BOOL Task_SafariEncounter(TaskManager *taskManager);
static BOOL Task_PalParkEncounter(TaskManager *taskManager);
static BOOL Task_TutorialBattle(TaskManager *taskManager);
static BOOL sub_02047220(TaskManager *taskManager);
static void sub_020472F4(FieldSystem *fieldSystem, BattleSetup *setup);
static void sub_020473CC(FieldSystem *fieldSystem, BattleSetup *setup);

static BOOL Task_StartBattle(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    BattleSetup *battleSetup = TaskManager_GetEnvironment(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);

    switch (*state) {
        case 0:
            sub_0203780C(fieldSystem, battleSetup);
            (*state)++;
            break;
        case 1:
            if (!FieldSystem_ApplicationIsRunning(fieldSystem)) {
                return TRUE;
            }
            break;
    }

    return FALSE;
}

static void CallTask_StartBattle(TaskManager *taskManager, BattleSetup *setup) {
    TaskManager_Call(taskManager, Task_StartBattle, setup);
}

static Encounter *Encounter_New(BattleSetup *setup, s32 effect, s32 bgm, u32 *winFlag) {
    Encounter *encounter = AllocFromHeapAtEnd(HEAP_ID_FIELD, sizeof(Encounter));
    encounter->winFlag = winFlag;
    if (winFlag != NULL) {
        *winFlag = BATTLE_OUTCOME_NONE;
    }
    encounter->effect = effect;
    encounter->bgm = bgm;
    encounter->setup = setup;
    return encounter;
}

static void Encounter_Delete(Encounter *encounter) {
    BattleSetup_Delete(encounter->setup);
    FreeToHeap(encounter);
}

static BOOL Encounter_GetResult(Encounter *encounter) {
    if (encounter->winFlag != NULL) {
        *(encounter->winFlag) = encounter->setup->winFlag;
    }
    return IsBattleResultWin(encounter->setup->winFlag);
}

static void sub_020465E4(BattleSetup *setup, FieldSystem *fieldSystem) {
    if (!(setup->flags & BATTLE_TYPE_DEBUG)) {
        sub_02047F38(setup, fieldSystem);
    }
}

static BOOL Task_StartEncounter(TaskManager *taskManager) { //todo: better name
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    Encounter *encounter = TaskManager_GetEnvironment(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);

    switch (*state) {
        case 0:
            MapObjectManager_PauseAllMovement(fieldSystem->mapObjectManager);
            sub_0204AEF8(taskManager, encounter->effect, encounter->bgm);
            (*state)++;
            break;
        case 1:
            sub_0204AF3C(taskManager);
            (*state)++;
            break;
        case 2:
            CallTask_StartBattle(taskManager, encounter->setup);
            (*state)++;
            break;
        case 3:
            sub_020465E4(encounter->setup, fieldSystem);
            if (encounter->setup->flags == BATTLE_TYPE_NONE || encounter->setup->flags == BATTLE_TYPE_8 || encounter->setup->flags == (BATTLE_TYPE_DOUBLES | BATTLE_TYPE_MULTI | BATTLE_TYPE_6)) {
                sub_02061080(fieldSystem, encounter->setup->unk134, encounter->setup->winFlag);
            }

            if (Encounter_GetResult(encounter) == FALSE) {
                Encounter_Delete(encounter);
                return TRUE;
            }

            if (Save_VarsFlags_CheckHaveFollower(Save_VarsFlags_Get(fieldSystem->saveData))) {
                HealParty(SaveArray_Party_Get(fieldSystem->saveData));
            }

            sub_020472F4(fieldSystem, encounter->setup);
            sub_020473CC(fieldSystem, encounter->setup);
            CallTask_RestoreOverworld(taskManager);
            (*state)++;
            break;
        case 4:
            MapObjectManager_UnpauseAllMovement(fieldSystem->mapObjectManager);
            CallTask_FadeFromBlack(taskManager);
            (*state)++;
            break;
        case 5:
            Encounter_Delete(encounter);
            return TRUE;
            break;
    }

    return FALSE;
}

static void CallTask_StartEncounter(TaskManager *taskManager, BattleSetup *setup, s32 effect, s32 bgm, u32 *winFlag) {
    Encounter *encounter = Encounter_New(setup, effect, bgm, winFlag);
    TaskManager_Call(taskManager, Task_StartEncounter, encounter);
}

static void sub_0204671C(s32 flag, FieldSystem *fieldSystem) {
    switch(flag & 0xF) {
        case 1:
        case 6:
            sub_0202E25C(fieldSystem->saveData, 1);
            break;
        case 2:
        case 5:
            sub_0202E25C(fieldSystem->saveData, -1);
            break;
    }
}

static BOOL Task_02046758(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    Encounter *encounter = TaskManager_GetEnvironment(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);
    switch (*state) {
        case 0:
            sub_0204AEF8(taskManager, encounter->effect, encounter->bgm);
            (*state)++;
            break;
        case 1:
            sub_0204AF3C(taskManager);
            (*state)++;
            break;
        case 2:
            CallTask_StartBattle(taskManager, encounter->setup);
            (*state)++;
            break;
        case 3:
            sub_0204671C(encounter->setup->winFlag, fieldSystem);
            sub_02047FA4(encounter->setup, fieldSystem);
            GameStats_AddSpecial(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK21);
            CallTask_RestoreOverworld(taskManager);
            (*state)++;
            break;
        case 4:
        case 5: //??
            Encounter_Delete(encounter);
            return TRUE;
    }
    return FALSE;
}

static BOOL Task_020467FC(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    Encounter *encounter = TaskManager_GetEnvironment(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);

    switch (*state) {
        case 0:
            sub_0200433C(5, encounter->bgm, 1);
            CallTask_StartBattle(taskManager, encounter->setup);
            (*state)++;
            break;
        case 1:
            sub_0204671C(encounter->setup->winFlag, fieldSystem);
            sub_02047FA4(encounter->setup, fieldSystem);
            GameStats_AddSpecial(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK21);
            (*state)++;
            break;
        case 2:
            Encounter_Delete(encounter);
            return TRUE;
    }
    return FALSE;
}

static BOOL Task_02046878(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    Encounter *encounter = TaskManager_GetEnvironment(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);

    switch (*state) {
        case 0:
            sub_0204AEF8(taskManager, encounter->effect, encounter->bgm);
            (*state)++;
            break;
        case 1:
            sub_0204AF3C(taskManager);
            (*state)++;
            break;
        case 2:
            CallTask_StartBattle(taskManager, encounter->setup);
            (*state)++;
            break;
        case 3:
            sub_02047FA4(encounter->setup, fieldSystem);
            sub_02060044(fieldSystem, &encounter->setup->unk138);
            Encounter_GetResult(encounter);
            CallTask_RestoreOverworld(taskManager);
            (*state)++;
            break;
        case 4:
            CallTask_FadeFromBlack(taskManager);
            (*state)++;
            break;
        case 5:
            Encounter_Delete(encounter);
            return TRUE;
    }
    return FALSE;
}

static void CallTask_02046878(TaskManager *taskManager, BattleSetup *battleSetup, s32 effect, s32 bgm, u32 *winFlag) { //CallTask_02046878
    Encounter *encounter = Encounter_New(battleSetup, effect, bgm, winFlag);
    TaskManager_Call(taskManager, Task_02046878, encounter);
}

void sub_02046948(TaskManager *taskManager, u32 param1, u32 *winFlag) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    BattleSetup *battleSetup = ov06_02244558(param1, fieldSystem);
    s32 effect = sub_020475A0(battleSetup);
    s32 bgm = sub_020475B0(battleSetup);
    CallTask_02046878(taskManager, battleSetup, effect, bgm, winFlag);
}

static WildEncounter *WildEncounter_New(BattleSetup *setup, s32 effect, s32 bgm, u32 *winFlag) {
    WildEncounter *encounter = AllocFromHeapAtEnd(HEAP_ID_FIELD, sizeof(WildEncounter));
    encounter->winFlag = winFlag;
    if (winFlag != NULL) {
        *winFlag = BATTLE_OUTCOME_NONE;
    }
    encounter->effect = effect;
    encounter->bgm = bgm;
    encounter->setup = setup;
    encounter->state = 0;
    return encounter;
}

static void WildEncounter_Delete(WildEncounter *encounter) {
    BattleSetup_Delete(encounter->setup);
    FreeToHeap(encounter);
}

void sub_020469B8(FieldSystem *fieldSystem, BattleSetup *setup) {
    SaveVarsFlags *flags = Save_VarsFlags_Get(fieldSystem->saveData);

    if (Save_VarsFlags_CheckSafariSysFlag(flags)) {
        Encounter *encounter = Encounter_New(setup, sub_020475A0(setup), sub_020475B0(setup), NULL);
        FieldSystem_CreateTask(fieldSystem, Task_SafariEncounter, encounter);
    } else {
        WildEncounter *encounter = WildEncounter_New(setup, sub_020475A0(setup), sub_020475B0(setup), NULL);
        FieldSystem_CreateTask(fieldSystem, Task_WildEncounter, encounter);
    }
}

void sub_02046A20(FieldSystem *fieldSystem, TaskManager *taskManager, BattleSetup *setup) {
    SaveVarsFlags *flags = Save_VarsFlags_Get(fieldSystem->saveData);

    if (Save_VarsFlags_CheckSafariSysFlag(flags)) {
        Encounter *encounter = Encounter_New(setup, sub_020475A0(setup), sub_020475B0(setup), NULL);
        TaskManager_Jump(taskManager, Task_SafariEncounter, encounter);
    } else {
        WildEncounter *encounter = WildEncounter_New(setup, sub_020475A0(setup), sub_020475B0(setup), NULL);
        TaskManager_Jump(taskManager, Task_WildEncounter, encounter);
    }
}

static BOOL Task_WildEncounter(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    WildEncounter *encounter = TaskManager_GetEnvironment(taskManager);

    switch (encounter->state) {
        case 0:
            MapObjectManager_PauseAllMovement(fieldSystem->mapObjectManager);
            GameStats_Inc(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK7);
            sub_0204AEF8(taskManager, encounter->effect, encounter->bgm);
            encounter->state++;
            break;
        case 1:
            sub_0204AF3C(taskManager);
            encounter->state++;
            break;
        case 2:
            CallTask_StartBattle(taskManager, encounter->setup);
            encounter->state++;
            break;
        case 3:
            sub_020465E4(encounter->setup, fieldSystem);
            sub_02061080(fieldSystem, encounter->setup->unk134, encounter->setup->winFlag);

            if (IsBattleResultWin(encounter->setup->winFlag) == FALSE) {
                WildEncounter_Delete(encounter);
                sub_0205DD40(fieldSystem->unk90);
                TaskManager_Jump(taskManager, Task_BlackOut, NULL);
                return FALSE;
            }

            if (Save_VarsFlags_CheckHaveFollower(Save_VarsFlags_Get(fieldSystem->saveData))) {
                HealParty(SaveArray_Party_Get(fieldSystem->saveData));
            }

            sub_020472F4(fieldSystem, encounter->setup);
            sub_020473CC(fieldSystem, encounter->setup);
            
            if (sub_0205E128(fieldSystem->unk90) != 0) {
                if (sub_0205E0A4(fieldSystem->unk90) != 0) {
                    if (encounter->setup->winFlag != BATTLE_OUTCOME_WIN && encounter->setup->winFlag != BATTLE_OUTCOME_MON_CAUGHT) {
                        sub_0205DD40(fieldSystem->unk90);
                    }
                } else {
                    sub_0205DD40(fieldSystem->unk90);
                }
            } 
            CallTask_RestoreOverworld(taskManager);
            encounter->state++;
            break;
        case 4:
            ov06_02248724(fieldSystem, encounter->setup);
            CallTask_FadeFromBlack(taskManager);
            encounter->state++;
            break;
        case 5:
            if (sub_0205E128(fieldSystem->unk90) != 0) {
                sub_0205DED4(fieldSystem, encounter->setup->winFlag, fieldSystem->unk90);
                sub_0205DF44(fieldSystem, fieldSystem->unk90);
            }
            encounter->state++;
            break;
        case 6:
            if (sub_0205DF9C(fieldSystem->unk90)) {
                MapObjectManager_UnpauseAllMovement(fieldSystem->mapObjectManager);
                WildEncounter_Delete(encounter);
                return TRUE;
            }
            break;
    }
    return FALSE;
}

static BOOL Task_SafariEncounter(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    Encounter *encounter = TaskManager_GetEnvironment(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);
    u16 *safariBalls = LocalFieldData_GetSafariBallsCounter(Save_LocalFieldData_Get(fieldSystem->saveData));

    switch (*state) {
        case 0:
            MapObjectManager_PauseAllMovement(fieldSystem->mapObjectManager);
            GameStats_Inc(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK7);
            sub_0204AEF8(taskManager, encounter->effect, encounter->bgm);
            (*state)++;
            break;
        case 1:
            sub_0204AF3C(taskManager);
            (*state)++;
            break;
        case 2:
            CallTask_StartBattle(taskManager, encounter->setup);
            (*state)++;
            break;
        case 3:
            sub_020465E4(encounter->setup, fieldSystem);
            if (encounter->setup->winFlag == BATTLE_OUTCOME_MON_CAUGHT) {
                SafariZone *safariZone = Save_SafariZone_Get(fieldSystem->saveData);
                Pokemon *pokemon = Party_GetMonByIndex(encounter->setup->party[BATTLER_ENEMY], 0);
                sub_02060FE0(safariZone, pokemon);
            }

            sub_020472F4(fieldSystem, encounter->setup);

            if (*safariBalls == 0 && encounter->setup->winFlag != BATTLE_OUTCOME_MON_CAUGHT) {
                Location *location = LocalFieldData_GetDynamicWarp(Save_LocalFieldData_Get(fieldSystem->saveData));
                sub_02049160(taskManager, location);
            }
            sub_020473CC(fieldSystem, encounter->setup);
            (*state)++;
            break;
        case 4:
            CallTask_RestoreOverworld(taskManager);
            (*state)++;
            break;
        case 5:
            MapObjectManager_UnpauseAllMovement(fieldSystem->mapObjectManager);
            CallTask_FadeFromBlack(taskManager);
            (*state)++;
            break;
        case 6:
            if (*safariBalls == 0) {
                if (encounter->setup->winFlag == BATTLE_OUTCOME_MON_CAUGHT) {
                    QueueScript(taskManager, 0x2262, NULL, NULL);
                } else {
                    QueueScript(taskManager, 0x2269, NULL, NULL);
                }
            } else {
                PCStorage *pc = SaveArray_PCStorage_Get(fieldSystem->saveData);
                Party *party = SaveArray_Party_Get(fieldSystem->saveData);
                if (PCStorage_FindFirstBoxWithEmptySlot(pc) == NUM_BOXES && Party_GetCount(party) == PARTY_SIZE) {
                    QueueScript(taskManager, 0x2276, NULL, NULL);
                }
            }
            (*state)++;
            break;
        case 7:
            Encounter_Delete(encounter);
            return TRUE;
    }
    return FALSE;
}

void SetupAndStartHoneyTreeBattle(TaskManager *taskManager, u32 *winFlag) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    sub_0205DD40(fieldSystem->unk90);
    BattleSetup *setup = BattleSetup_New(HEAP_ID_FIELD, BATTLE_TYPE_NONE);
    BattleSetup_InitFromFieldSystem(setup, fieldSystem);

    setup->unk150 = 0;
    setup->unk154 = 0;
    ov06_0223CCDC(fieldSystem, setup);

    GameStats_Inc(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK7);

    CallTask_StartEncounter(taskManager, setup, sub_020475A0(setup), sub_020475B0(setup), winFlag);
}

void SetupAndStartWildBattle(TaskManager *taskManager, u16 species, u8 level, u32 *winFlag, BOOL canFlee) {
    BattleSetup *setup;
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    sub_0205DD40(fieldSystem->unk90);
    setup = BattleSetup_New(HEAP_ID_FIELD, BATTLE_TYPE_NONE);
    BattleSetup_InitFromFieldSystem(setup, fieldSystem);
    ov06_0223CD7C(fieldSystem, species, level, setup);

    if (canFlee) {
        setup->unk18C |= 8;
    }

    GameStats_Inc(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK7);

    CallTask_StartEncounter(taskManager, setup, sub_020475A0(setup), sub_020475B0(setup), winFlag);
}

static BOOL Task_PalParkEncounter(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    Encounter *encounter = TaskManager_GetEnvironment(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);

    switch (*state) {
        case 0:
            MapObjectManager_PauseAllMovement(fieldSystem->mapObjectManager);
            GameStats_Inc(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK7);
            sub_0204AEF8(taskManager, encounter->effect, encounter->bgm);
            (*state)++;
            break;
        case 1:
            sub_0204AF3C(taskManager);
            (*state)++;
            break;
        case 2:
            CallTask_StartBattle(taskManager, encounter->setup);
            (*state)++;
            break;
        case 3:
            sub_020465E4(encounter->setup, fieldSystem);
            PalPark_HandleBattleEnd(fieldSystem, encounter->setup);
            sub_020472F4(fieldSystem, encounter->setup);
            (*state)++;
            break;
        case 4:
            CallTask_RestoreOverworld(taskManager);
            (*state)++;
            break;
        case 5:
            MapObjectManager_UnpauseAllMovement(fieldSystem->mapObjectManager);
            CallTask_FadeFromBlack(taskManager);
            (*state)++;
            break;
        case 6:
            Encounter_Delete(encounter);
            if (PalPark_CountMonsNotCaught(fieldSystem) == 0) {
                StartScriptFromMenu(taskManager, 3, NULL);
                return FALSE;
            }
            return TRUE;
    }

    return FALSE;
}

void sub_02046F70(FieldSystem *fieldSystem, BattleSetup *setup) {
    Encounter *encounter = Encounter_New(setup, sub_020475A0(setup), sub_020475B0(setup), NULL);
    FieldSystem_CreateTask(fieldSystem, Task_PalParkEncounter, encounter);
}

void SetupAndStartFirstBattle(TaskManager *taskManager, u16 species, u8 level) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    BattleSetup *setup = BattleSetup_New(HEAP_ID_FIELD, BATTLE_TYPE_NONE);
    BattleSetup_InitFromFieldSystem(setup, fieldSystem);

    ov06_0223CD7C(fieldSystem, species, level, setup);

    setup->unk18C = 1;

    GameStats_Inc(Save_GameStats_Get(fieldSystem->saveData),  GAME_STAT_UNK7);

    CallTask_StartEncounter(taskManager, setup, sub_020475A0(setup), sub_020475B0(setup), NULL);
}

static BOOL Task_TutorialBattle(TaskManager *taskManager) {
    Encounter *encounter = TaskManager_GetEnvironment(taskManager);
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);

    switch (*state) {
        case 0:
            MapObjectManager_PauseAllMovement(fieldSystem->mapObjectManager);
            sub_0204AEF8(taskManager, encounter->effect, encounter->bgm);
            (*state)++;
            break;
        case 1:
            sub_0204AF3C(taskManager);
            (*state)++;
            break;
        case 2:
            CallTask_StartBattle(taskManager, encounter->setup);
            (*state)++;
            break;
        case 3:
            (*state)++;
            break;
        case 4:
            CallTask_RestoreOverworld(taskManager);
            (*state)++;
            break;
        case 5:
            MapObjectManager_UnpauseAllMovement(fieldSystem->mapObjectManager);
            CallTask_FadeFromBlack(taskManager);
            (*state)++;
            break;
        case 6:
            Encounter_Delete(encounter);
            return TRUE;
    }
    return FALSE;
}

void SetupAndStartTutorialBattle(TaskManager *taskManager) {
    Encounter *encounter;
    BattleSetup *setup;
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    
    setup = sub_02047814(HEAP_ID_FIELD, fieldSystem);
    encounter = Encounter_New(setup, sub_020475A0(setup), sub_020475B0(setup), NULL);

    TaskManager_Call(taskManager, Task_TutorialBattle, encounter);
}

void SetupAndStartTrainerBattle(TaskManager *taskManager, u32 opponentTrainer1, u32 opponentTrainer2, u32 followerTrainerNum, HeapID heapId, u32 *winFlag) {
    u32 battleType;
    BattleSetup *setup;
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    
    if (opponentTrainer2 != 0 && opponentTrainer1 != opponentTrainer2) {
        if (followerTrainerNum == 0) {
            battleType = (BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLES | BATTLE_TYPE_INGAME_PARTNER);
        } else {
            battleType = (BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLES | BATTLE_TYPE_MULTI | BATTLE_TYPE_6);
        }
    } else if (opponentTrainer1 == opponentTrainer2) {
        battleType = (BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLES);
    } else {
        battleType = BATTLE_TYPE_TRAINER;
    }
    sub_0205DD40(fieldSystem->unk90);

    setup = BattleSetup_New(HEAP_ID_FIELD, battleType);
    BattleSetup_InitFromFieldSystem(setup, fieldSystem);

    setup->trainerId[BATTLER_ENEMY] = opponentTrainer1;
    setup->trainerId[BATTLER_ENEMY2] = opponentTrainer2;
    setup->trainerId[BATTLER_PLAYER2] = followerTrainerNum;

    EnemyTrainerSet_Init(setup, fieldSystem->saveData, heapId);

    GameStats_Inc(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK8);
    
    CallTask_StartEncounter(taskManager, setup, sub_020475A0(setup), sub_020475B0(setup), winFlag);
}

void sub_02047174(TaskManager *taskManager, void *param1, u32 battleType) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    Encounter *encounter;
    BattleSetup *setup;

    setup = BattleSetup_New(HEAP_ID_FIELD, battleType);

    sub_02047F1C(setup, fieldSystem, param1);

    encounter = Encounter_New(setup, sub_020475A0(setup), sub_020475B0(setup), NULL);

    TaskManager_Call(taskManager, Task_02046758, encounter);
}

void sub_020471C0(TaskManager *taskManager, s32 target, s32 maxLevel, u32 flag) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    Encounter *encounter;
    BattleSetup *setup;

    if (flag != 0) {
        setup = BattleSetup_New(HEAP_ID_FIELD, (BATTLE_TYPE_LINK | BATTLE_TYPE_TRAINER));
    } else {
        setup = BattleSetup_New(HEAP_ID_FIELD, (BATTLE_TYPE_LINK | BATTLE_TYPE_DOUBLES | BATTLE_TYPE_TRAINER));
    }

    sub_02047BC0(setup, fieldSystem, maxLevel);

    encounter = Encounter_New(setup, sub_020475A0(setup), sub_020475B0(setup), NULL);
    encounter->unkC = target;

    TaskManager_Call(taskManager, Task_020467FC, encounter);
}

static BOOL sub_02047220(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    Encounter *encounter = TaskManager_GetEnvironment(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);

    switch (*state) {
        case 0:
            TaskManager_Call(taskManager, Task_02046758, encounter);
            (*state)++;
            break;
        case 1:
            sub_0204FF5C(fieldSystem);
            return TRUE;
    }
    return FALSE;
}

void sub_0204726C(FieldSystem *fieldSystem, void *param1, s32 battleType) {
    Encounter *encounter;
    BattleSetup *setup = BattleSetup_New(HEAP_ID_FIELD, battleType);

    sub_02047F1C(setup, fieldSystem, param1);

    encounter = Encounter_New(setup, sub_020475A0(setup), sub_020475B0(setup), NULL);

    FieldSystem_CreateTask(fieldSystem, sub_02047220, encounter);
}

void sub_020472B0(FieldSystem *fieldSystem, Party *party, s32 battleType) {
    Encounter *encounter;
    BattleSetup *setup = BattleSetup_New(HEAP_ID_FIELD, battleType);

    sub_02047D48(setup, fieldSystem, party, NULL);

    encounter = Encounter_New(setup, sub_020475A0(setup), sub_020475B0(setup), NULL);

    FieldSystem_CreateTask(fieldSystem, sub_02047220, encounter);
}

static void sub_020472F4(FieldSystem *fieldSystem, BattleSetup *setup) {
    Pokemon *mon;
    u32 battleType = setup->flags;
    u32 winFlag = setup->winFlag;

    if (battleType & BATTLE_TYPE_LINK || battleType & BATTLE_TYPE_TOWER) {
        return;
    }
    
    if (battleType == BATTLE_TYPE_NONE || battleType == BATTLE_TYPE_8 || battleType == (BATTLE_TYPE_DOUBLES | BATTLE_TYPE_MULTI | BATTLE_TYPE_6)) {
        if (winFlag == BATTLE_OUTCOME_WIN) {
            GameStats_AddSpecial(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK8);
        } else if (winFlag == BATTLE_OUTCOME_MON_CAUGHT) {
            mon = Party_GetMonByIndex(setup->party[BATTLER_ENEMY], 0);
            if (Pokedex_ConvertToCurrentDexNo(FALSE, GetMonData(mon, MON_DATA_SPECIES, NULL)) != 0) {
                GameStats_AddSpecial(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK9);
            } else {
                GameStats_AddSpecial(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK10);
            }
        }
    } else if ((battleType & BATTLE_TYPE_TRAINER) || (battleType & BATTLE_TYPE_INGAME_PARTNER)) {
        if (winFlag == BATTLE_OUTCOME_WIN) {
            GameStats_AddSpecial(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK11);
        }
    } else if ((battleType & BATTLE_TYPE_SAFARI || battleType & BATTLE_TYPE_PAL_PARK) && winFlag == BATTLE_OUTCOME_MON_CAUGHT) {
        mon = Party_GetMonByIndex(setup->party[BATTLER_ENEMY], 0);
        if (Pokedex_ConvertToCurrentDexNo(FALSE, GetMonData(mon, MON_DATA_SPECIES, NULL)) != 0) {
            GameStats_AddSpecial(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK9);
        } else {
            GameStats_AddSpecial(Save_GameStats_Get(fieldSystem->saveData), GAME_STAT_UNK10);
        }
    }
}

static void sub_020473CC(FieldSystem *fieldSystem, BattleSetup *setup) {
    Pokemon *mon;
    u32 battleType = setup->flags;
    u32 winFlag = setup->winFlag;

    if (battleType & BATTLE_TYPE_LINK || battleType & BATTLE_TYPE_TOWER || battleType & BATTLE_TYPE_PAL_PARK) {
        return;
    }
    if (battleType == BATTLE_TYPE_NONE || battleType == BATTLE_TYPE_8 || battleType == (BATTLE_TYPE_DOUBLES | BATTLE_TYPE_MULTI | BATTLE_TYPE_6) || battleType == BATTLE_TYPE_SAFARI) {
        if (winFlag == BATTLE_OUTCOME_WIN) {
            fieldSystem->unk76++;
            if (fieldSystem->unk76 < 5) {
                return;
            }
            mon = Party_GetMonByIndex(setup->party[BATTLER_ENEMY], 0);
            sub_02028AD4(fieldSystem->unk98, sub_0202920C(Save_PlayerData_GetIGTAddr(fieldSystem->saveData), GetMonData(mon, MON_DATA_SPECIES, NULL), GetMonData(mon, MON_DATA_GENDER, NULL), setup->unk160, HEAP_ID_FIELD), 2);
        } else if (winFlag == BATTLE_OUTCOME_MON_CAUGHT) {
            mon = Party_GetMonByIndex(setup->party[setup->unk170], 0);
            sub_02028AD4(fieldSystem->unk98, sub_0202918C(Save_PlayerData_GetIGTAddr(fieldSystem->saveData), GetMonData(mon, MON_DATA_SPECIES, NULL), GetMonData(mon, MON_DATA_GENDER, NULL), setup->unk160, HEAP_ID_FIELD), 2);
        }
    } else if ((battleType & BATTLE_TYPE_TRAINER) || (battleType & BATTLE_TYPE_INGAME_PARTNER)) {
        if (winFlag == BATTLE_OUTCOME_WIN) {
            sub_020299DC(fieldSystem->unk98, fieldSystem->location->mapId, setup->trainerId[BATTLER_ENEMY], HEAP_ID_FIELD);
        }
    }
}
