#include "field_move.h"

#include "global.h"

#include "constants/badge.h"
#include "constants/field_move_response.h"
#include "constants/global_fieldmap.h"
#include "constants/sprites.h"
#include "constants/std_script.h"
#include "constants/weather.h"

#include "field_move_environment.h"
#include "map_header.h"
#include "map_object.h"
#include "overlay_06.h"
#include "player_data.h"
#include "save_local_field_data.h"
#include "start_menu.h"
#include "unk_0205EC84.h"
#include "unk_0205F7A0.h"

static FieldUseMoveEnvironment *FieldMove_CreateUseEnvironment(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static void FieldMove_DeleteUseEnvironment(FieldUseMoveEnvironment *environment);
static u32 FieldMove_CheckCut(const FieldMoveCheckData *checkData);
static void FieldMove_UseCut(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseCutInField(TaskManager *taskManager);
static u32 FieldMove_CheckFly(const FieldMoveCheckData *checkData);
static void FieldMove_UseFly(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static u32 FieldMove_CheckSurf(const FieldMoveCheckData *checkData);
static void FieldMove_UseSurf(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseSurfInField(TaskManager *taskManager);
static u32 FieldMove_CheckStrength(const FieldMoveCheckData *checkData);
static void FieldMove_UseStrength(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseStrengthInField(TaskManager *taskManager);
static u32 FieldMove_CheckDefog(const FieldMoveCheckData *checkData);
static void FieldMove_UseDefog(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseDefogInField(TaskManager *taskManager);
static u32 FieldMove_CheckRockSmash(const FieldMoveCheckData *checkData);
static void FieldMove_UseRockSmash(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseRockSmashInField(TaskManager *taskManager);
static u32 FieldMove_CheckWaterfall(const FieldMoveCheckData *checkData);
static void FieldMove_UseWaterfall(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseWaterfallInField(TaskManager *taskManager);
static u32 FieldMove_CheckRockClimb(const FieldMoveCheckData *checkData);
static void FieldMove_UseRockClimb(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseRockClimbInField(TaskManager *taskManager);
static u32 FieldMove_CheckFlash(const FieldMoveCheckData *checkData);
static void FieldMove_UseFlash(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseFlashInField(TaskManager *taskManager);
static u32 FieldMove_CheckTeleport(const FieldMoveCheckData *checkData);
static void FieldMove_UseTeleport(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseTeleportInField(TaskManager *taskManager);
static u32 FieldMove_CheckDig(const FieldMoveCheckData *checkData);
static void FieldMove_UseDig(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseDigInField(TaskManager *taskManager);
static u32 FieldMove_CheckSweetScent(const FieldMoveCheckData *checkData);
static void FieldMove_UseSweetScent(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static u32 FieldMove_CheckChatter(const FieldMoveCheckData *checkData);
static void FieldMove_UseChatter(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseChatterInField(TaskManager *taskManager);

extern void FieldSystem_GetFacingObject(FieldSystem *fieldSystem, LocalMapObject **object);
extern u16 PlayerAvatar_GetXCoord(PlayerAvatar *playerAvatar);
extern u16 PlayerAvatar_GetZCoord(PlayerAvatar *playerAvatar);
extern u8 GetMetatileBehavior(FieldSystem *fieldSystem, s32 x, s32 z);
extern void PlayerAvatar_GetCoordsInFront(PlayerAvatar *playerAvatar, s32 *x, s32 *z);
extern BOOL Field_PlayerCanSurfOnTile(PlayerAvatar *fieldPlayerAvatar, u32 standingTile, u32 facingTile);
extern u32 PlayerAvatar_GetFacingDirection(PlayerAvatar *playerAvatar);
extern BOOL MetatileBehavior_IsRockClimbInDirection(u32 facingTile, u32 facingDirection);
extern BOOL MetatileBehavior_IsWaterfall(u8 facingTile);
extern LocalFieldData *Save_LocalFieldData_Get(SaveData *save);
extern u32 LocalFieldData_GetWeatherType(LocalFieldData *localFieldData);
extern void StartScriptFromMenu(TaskManager *taskManager, u16 script, LocalMapObject *object);
extern void FieldMove_SetArgs(FieldSystem *fieldSystem, u16 param1, u16 param2, u16 param3, u16 param4);
extern BOOL Task_UseFlyInField(TaskManager *taksManager);
extern void TownMap_Init(FieldSystem *fieldSystem, TownMapAppData *townMap, u32 param2);
extern void TownMap_Show(FieldSystem *fieldSystem, TownMapAppData *townMap);
extern void StartMenu_SetExitTaskFunc(StartMenuTaskData *startMenu, TaskFunc taskFunc);
extern u32 PlayerAvatar_GetState(PlayerAvatar *avatar);
extern FieldMoveTaskEnvironment *FieldMoveTask_CreateTeleportEnvironment(FieldSystem *fieldSystem, Pokemon *mon, HeapID heapId);
extern BOOL Task_FieldTeleport(TaskManager *taskManager);
extern FieldMoveTaskEnvironment *FieldMoveTask_CreateDigEnvironment(FieldSystem *fieldSystem, Pokemon *mon, HeapID heapId);
extern BOOL Task_FieldDig(TaskManager *taskManager);
extern void *sub_0202914C(u32 param0, u16 mapId, u32 param2);
extern void sub_02028AD4(u32 *param0, void *param1, u32 param2);
extern BOOL Task_UseSweetScentInField(TaskManager *taskManager);

static const FieldMoveFuncData sFieldMoveFuncTable[] = {
    { FieldMove_UseCut,        FieldMove_CheckCut        },
    { FieldMove_UseFly,        FieldMove_CheckFly        },
    { FieldMove_UseSurf,       FieldMove_CheckSurf       },
    { FieldMove_UseStrength,   FieldMove_CheckStrength   },
    { FieldMove_UseDefog,      FieldMove_CheckDefog      },
    { FieldMove_UseRockSmash,  FieldMove_CheckRockSmash  },
    { FieldMove_UseWaterfall,  FieldMove_CheckWaterfall  },
    { FieldMove_UseRockClimb,  FieldMove_CheckRockClimb  },
    { FieldMove_UseFlash,      FieldMove_CheckFlash      },
    { FieldMove_UseTeleport,   FieldMove_CheckTeleport   },
    { FieldMove_UseDig,        FieldMove_CheckDig        },
    { FieldMove_UseSweetScent, FieldMove_CheckSweetScent },
    { FieldMove_UseChatter,    FieldMove_CheckChatter    }
};

static inline BOOL FieldMove_CheckSafariOrPalPark(const FieldMoveCheckData *checkData) {
    if (Save_VarsFlags_CheckSafariSysFlag(Save_VarsFlags_Get(checkData->fieldSystem->saveData)) == TRUE || Save_VarsFlags_CheckPalParkSysFlag(Save_VarsFlags_Get(checkData->fieldSystem->saveData)) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static inline BOOL FieldMove_CheckPalPark(const FieldMoveCheckData *checkData) {
    if (Save_VarsFlags_CheckPalParkSysFlag(Save_VarsFlags_Get(checkData->fieldSystem->saveData)) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static inline BOOL FieldMove_CheckFlag(const FieldMoveCheckData *checkData, u32 flag) {
    if (checkData->flag & flag) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void *FieldMove_GetMoveFunc(FieldMoveFuncType funcType, u16 fieldMoveIndex) {
    if (funcType == FIELD_MOVE_FUNC_USE) {
        return sFieldMoveFuncTable[fieldMoveIndex].use;
    } else {
        return sFieldMoveFuncTable[fieldMoveIndex].check;
    }
}

void FieldMove_InitCheckData(FieldSystem *fieldSystem, FieldMoveCheckData *checkData) {
    checkData->fieldSystem = fieldSystem;
    checkData->mapId = fieldSystem->location->mapId;
    checkData->flag = 0;

    LocalMapObject *facingObject;

    FieldSystem_GetFacingObject(fieldSystem, &facingObject);
    checkData->facingObject = facingObject;

    if (facingObject != NULL) {
        switch (MapObject_GetSpriteID(facingObject)) {
        case SPRITE_ROCK:
            checkData->flag |= FIELD_MOVE_CHECK_ROCK;
            break;
        case SPRITE_BREAKROCK:
            checkData->flag |= FIELD_MOVE_CHECK_BREAKROCK;
            break;
        case SPRITE_TREE:
            checkData->flag |= FIELD_MOVE_CHECK_TREE;
            break;
        }
    }

    s32 x = PlayerAvatar_GetXCoord(fieldSystem->playerAvatar);
    s32 z = PlayerAvatar_GetZCoord(fieldSystem->playerAvatar);
    u32 standingTile = GetMetatileBehavior(fieldSystem, x, z);

    PlayerAvatar_GetCoordsInFront(fieldSystem->playerAvatar, &x, &z);
    u32 facingTile = GetMetatileBehavior(fieldSystem, x, z);

    if (Field_PlayerCanSurfOnTile(fieldSystem->playerAvatar, standingTile, facingTile)) {
        checkData->flag |= FIELD_MOVE_CHECK_WATER;
    }
    if (MetatileBehavior_IsRockClimbInDirection(facingTile, PlayerAvatar_GetFacingDirection(fieldSystem->playerAvatar))) {
        checkData->flag |= FIELD_MOVE_CHECK_ROCKCLIMB;
    }
    if (MetatileBehavior_IsWaterfall(facingTile)) {
        checkData->flag |= FIELD_MOVE_CHECK_WATERFALL;
    }
    switch (LocalFieldData_GetWeatherType(Save_LocalFieldData_Get(fieldSystem->saveData))) {
    case WEATHER_DEFOG:
        checkData->flag |= FIELD_MOVE_CHECK_DEFOG;
        break;
    case WEATHER_FLASH:
        checkData->flag |= FIELD_MOVE_CHECK_FLASH;
        break;
    }
}

static FieldUseMoveEnvironment *FieldMove_CreateUseEnvironment(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    FieldUseMoveEnvironment *environment = AllocFromHeap(HEAP_ID_32, sizeof(FieldUseMoveEnvironment));
    environment->magic = 0x19740205;
    environment->facingObject = checkData->facingObject;
    environment->useData = *useData;
    return environment;
}

static void FieldMove_DeleteUseEnvironment(FieldUseMoveEnvironment *environment) {
    GF_ASSERT(environment->magic == 0x19740205);
    FreeToHeap(environment);
}

static u32 FieldMove_CheckCut(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (!PlayerProfile_TestBadgeFlag(Save_PlayerData_GetProfile(checkData->fieldSystem->saveData), BADGE_FOREST)) {
        return FIELD_MOVE_RESPONSE_NEED_BADGE;
    }
    if (FieldMove_CheckFlag(checkData, FIELD_MOVE_CHECK_TREE)) {
        return FIELD_MOVE_RESPONSE_OK;
    }

    return FIELD_MOVE_RESPONSE_NOT_HERE;
}

static void FieldMove_UseCut(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldUseMoveEnvironment *useMoveEnvironment = FieldMove_CreateUseEnvironment(useData, checkData);
    FieldSystem_LoadFieldOverlay(checkData->fieldSystem);
    startMenu->exitTaskFunc = Task_UseCutInField;
    startMenu->exitTaskEnvironment = useMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
}

static BOOL Task_UseCutInField(TaskManager *taskManager) {
    FieldUseMoveEnvironment *environment = TaskManager_GetEnvironment(taskManager);
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    StartScriptFromMenu(taskManager, std_menu_cut, environment->facingObject);
    FieldMove_SetArgs(fieldSystem, environment->useData.partySlot, 0, 0, 0);
    FieldMove_DeleteUseEnvironment(environment);
    return FALSE;
}

static u32 FieldMove_CheckFly(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (!PlayerProfile_TestBadgeFlag(Save_PlayerData_GetProfile(checkData->fieldSystem->saveData), BADGE_COBBLE)) {
        return FIELD_MOVE_RESPONSE_NEED_BADGE;
    }
    if (!MapHeader_IsFlyAllowed(checkData->mapId)) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (Save_VarsFlags_CheckHaveFollower(Save_VarsFlags_Get(checkData->fieldSystem->saveData)) == TRUE) {
        return FIELD_MOVE_RESPONSE_HAVE_FOLLOWER;
    }
    if (FieldMove_CheckSafariOrPalPark(checkData) == TRUE) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }

    return FIELD_MOVE_RESPONSE_OK;
}

static void FieldMove_UseFly(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(useData->taskManager);
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldMoveData *fieldMoveData = AllocFromHeap(HEAP_ID_FIELD, sizeof(FieldMoveData));
    fieldMoveData->partySlot = useData->partySlot;
    startMenu->exitTaskEnvironment2 = fieldMoveData;
    TownMapAppData *townMap = AllocFromHeap(HEAP_ID_FIELD, sizeof(TownMapAppData));
    startMenu->exitTaskEnvironment = townMap;
    TownMap_Init(fieldSystem, startMenu->exitTaskEnvironment, 1);
    TownMap_Show(fieldSystem, startMenu->exitTaskEnvironment);
    StartMenu_SetExitTaskFunc(startMenu, Task_UseFlyInField);
}

static u32 FieldMove_CheckSurf(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (!PlayerProfile_TestBadgeFlag(Save_PlayerData_GetProfile(checkData->fieldSystem->saveData), BADGE_RELIC)) {
        return FIELD_MOVE_RESPONSE_NEED_BADGE;
    }
    if (PlayerAvatar_GetState(checkData->fieldSystem->playerAvatar) == PLAYER_STATE_SURFING) {
        return FIELD_MOVE_RESPONSE_ALREADY_SURFING;
    }
    if (!FieldMove_CheckFlag(checkData, FIELD_MOVE_CHECK_WATER)) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (Save_VarsFlags_CheckHaveFollower(Save_VarsFlags_Get(checkData->fieldSystem->saveData)) == TRUE) {
        return FIELD_MOVE_RESPONSE_HAVE_FOLLOWER;
    }

    return FIELD_MOVE_RESPONSE_OK;
}

static void FieldMove_UseSurf(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldUseMoveEnvironment *useMoveEnvironment = FieldMove_CreateUseEnvironment(useData, checkData);
    FieldSystem_LoadFieldOverlay(checkData->fieldSystem);
    startMenu->exitTaskFunc = Task_UseSurfInField;
    startMenu->exitTaskEnvironment = useMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
}

static BOOL Task_UseSurfInField(TaskManager *taskManager) {
    FieldUseMoveEnvironment *useMoveEnvironment = TaskManager_GetEnvironment(taskManager);
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    StartScriptFromMenu(taskManager, std_menu_surf, NULL);
    FieldMove_SetArgs(fieldSystem, useMoveEnvironment->useData.partySlot, 0, 0, 0);
    FieldMove_DeleteUseEnvironment(useMoveEnvironment);
    return FALSE;
}

static u32 FieldMove_CheckStrength(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (!PlayerProfile_TestBadgeFlag(Save_PlayerData_GetProfile(checkData->fieldSystem->saveData), BADGE_MINE)) {
        return FIELD_MOVE_RESPONSE_NEED_BADGE;
    }
    if (FieldMove_CheckFlag(checkData, FIELD_MOVE_CHECK_ROCK)) {
        return FIELD_MOVE_RESPONSE_OK;
    }

    return FIELD_MOVE_RESPONSE_NOT_HERE;
}

static void FieldMove_UseStrength(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldUseMoveEnvironment *useMoveEnvironment = FieldMove_CreateUseEnvironment(useData, checkData);
    FieldSystem_LoadFieldOverlay(checkData->fieldSystem);
    startMenu->exitTaskFunc = Task_UseStrengthInField;
    startMenu->exitTaskEnvironment = useMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
}

static BOOL Task_UseStrengthInField(TaskManager *taskManager) {
    FieldUseMoveEnvironment *useMoveEnvironment = TaskManager_GetEnvironment(taskManager);
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    StartScriptFromMenu(taskManager, std_menu_strength, useMoveEnvironment->facingObject);
    FieldMove_SetArgs(fieldSystem, useMoveEnvironment->useData.partySlot, 0, 0, 0);
    FieldMove_DeleteUseEnvironment(useMoveEnvironment);
    return FALSE;
}

static u32 FieldMove_CheckDefog(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (!PlayerProfile_TestBadgeFlag(Save_PlayerData_GetProfile(checkData->fieldSystem->saveData), BADGE_FEN)) {
        return FIELD_MOVE_RESPONSE_NEED_BADGE;
    }
    if (FieldMove_CheckFlag(checkData, FIELD_MOVE_CHECK_DEFOG)) {
        return FIELD_MOVE_RESPONSE_OK;
    }

    return FIELD_MOVE_RESPONSE_NOT_HERE;
}

static void FieldMove_UseDefog(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldUseMoveEnvironment *useMoveEnvironment = FieldMove_CreateUseEnvironment(useData, checkData);
    FieldSystem_LoadFieldOverlay(checkData->fieldSystem);
    startMenu->exitTaskFunc = Task_UseDefogInField;
    startMenu->exitTaskEnvironment = useMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
}

static BOOL Task_UseDefogInField(TaskManager *taskManager) {
    FieldUseMoveEnvironment *useMoveEnvironment = TaskManager_GetEnvironment(taskManager);
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    StartScriptFromMenu(taskManager, std_menu_defog, NULL);
    FieldMove_SetArgs(fieldSystem, useMoveEnvironment->useData.partySlot, 0, 0, 0);
    FieldMove_DeleteUseEnvironment(useMoveEnvironment);
    return FALSE;
}

static u32 FieldMove_CheckRockSmash(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (!PlayerProfile_TestBadgeFlag(Save_PlayerData_GetProfile(checkData->fieldSystem->saveData), BADGE_COAL)) {
        return FIELD_MOVE_RESPONSE_NEED_BADGE;
    }
    if (FieldMove_CheckFlag(checkData, FIELD_MOVE_CHECK_BREAKROCK)) {
        return FIELD_MOVE_RESPONSE_OK;
    }

    return FIELD_MOVE_RESPONSE_NOT_HERE;
}

static void FieldMove_UseRockSmash(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldUseMoveEnvironment *useMoveEnvironment = FieldMove_CreateUseEnvironment(useData, checkData);
    FieldSystem_LoadFieldOverlay(checkData->fieldSystem);
    startMenu->exitTaskFunc = Task_UseRockSmashInField;
    startMenu->exitTaskEnvironment = useMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
}

static BOOL Task_UseRockSmashInField(TaskManager *taskManager) {
    FieldUseMoveEnvironment *useMoveEnvironment = TaskManager_GetEnvironment(taskManager);
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    StartScriptFromMenu(taskManager, std_menu_rock_smash, useMoveEnvironment->facingObject);
    FieldMove_SetArgs(fieldSystem, useMoveEnvironment->useData.partySlot, 0, 0, 0);
    FieldMove_DeleteUseEnvironment(useMoveEnvironment);
    return FALSE;
}

static u32 FieldMove_CheckWaterfall(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (!PlayerProfile_TestBadgeFlag(Save_PlayerData_GetProfile(checkData->fieldSystem->saveData), BADGE_BEACON)) {
        return FIELD_MOVE_RESPONSE_NEED_BADGE;
    }
    if (FieldMove_CheckFlag(checkData, FIELD_MOVE_CHECK_WATERFALL)) {
        return FIELD_MOVE_RESPONSE_OK;
    }

    return FIELD_MOVE_RESPONSE_NOT_HERE;
}

static void FieldMove_UseWaterfall(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldUseMoveEnvironment *useMoveEnvironment = FieldMove_CreateUseEnvironment(useData, checkData);
    FieldSystem_LoadFieldOverlay(checkData->fieldSystem);
    startMenu->exitTaskFunc = Task_UseWaterfallInField;
    startMenu->exitTaskEnvironment = useMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
}

static BOOL Task_UseWaterfallInField(TaskManager *taskManager) {
    FieldUseMoveEnvironment *useMoveEnvironment = TaskManager_GetEnvironment(taskManager);
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    StartScriptFromMenu(taskManager, std_menu_waterfall, NULL);
    FieldMove_SetArgs(fieldSystem, useMoveEnvironment->useData.partySlot, 0, 0, 0);
    FieldMove_DeleteUseEnvironment(useMoveEnvironment);
    return FALSE;
}

static u32 FieldMove_CheckRockClimb(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (!PlayerProfile_TestBadgeFlag(Save_PlayerData_GetProfile(checkData->fieldSystem->saveData), BADGE_ICICLE)) {
        return FIELD_MOVE_RESPONSE_NEED_BADGE;
    }
    if (!FieldMove_CheckFlag(checkData, FIELD_MOVE_CHECK_ROCKCLIMB)) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (Save_VarsFlags_CheckHaveFollower(Save_VarsFlags_Get(checkData->fieldSystem->saveData)) == TRUE) {
        return FIELD_MOVE_RESPONSE_HAVE_FOLLOWER;
    }

    return FIELD_MOVE_RESPONSE_OK;
}

static void FieldMove_UseRockClimb(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldUseMoveEnvironment *useMoveEnvironment = FieldMove_CreateUseEnvironment(useData, checkData);
    FieldSystem_LoadFieldOverlay(checkData->fieldSystem);
    startMenu->exitTaskFunc = Task_UseRockClimbInField;
    startMenu->exitTaskEnvironment = useMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
}

static BOOL Task_UseRockClimbInField(TaskManager *taskManager) {
    FieldUseMoveEnvironment *useMoveEnvironment = TaskManager_GetEnvironment(taskManager);
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    StartScriptFromMenu(taskManager, std_menu_rock_climb, NULL);
    FieldMove_SetArgs(fieldSystem, useMoveEnvironment->useData.partySlot, 0, 0, 0);
    FieldMove_DeleteUseEnvironment(useMoveEnvironment);
    return FALSE;
}

static u32 FieldMove_CheckFlash(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (FieldMove_CheckFlag(checkData, FIELD_MOVE_CHECK_FLASH)) {
        return FIELD_MOVE_RESPONSE_OK;
    }

    return FIELD_MOVE_RESPONSE_NOT_HERE;
}

static void FieldMove_UseFlash(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldUseMoveEnvironment *useMoveEnvironment = FieldMove_CreateUseEnvironment(useData, checkData);
    FieldSystem_LoadFieldOverlay(checkData->fieldSystem);
    startMenu->exitTaskFunc = Task_UseFlashInField;
    startMenu->exitTaskEnvironment = useMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
}

static BOOL Task_UseFlashInField(TaskManager *taskManager) {
    FieldUseMoveEnvironment *useMoveEnvironment = TaskManager_GetEnvironment(taskManager);
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    StartScriptFromMenu(taskManager, std_menu_flash, NULL);
    FieldMove_SetArgs(fieldSystem, useMoveEnvironment->useData.partySlot, 0, 0, 0);
    FieldMove_DeleteUseEnvironment(useMoveEnvironment);
    return FALSE;
}

static u32 FieldMove_CheckTeleport(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (!MapHeader_IsTeleportAllowed(checkData->mapId)) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (Save_VarsFlags_CheckHaveFollower(Save_VarsFlags_Get(checkData->fieldSystem->saveData)) == TRUE) {
        return FIELD_MOVE_RESPONSE_HAVE_FOLLOWER;
    }
    if (FieldMove_CheckSafariOrPalPark(checkData) == TRUE) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }

    return FIELD_MOVE_RESPONSE_OK;
}

static void FieldMove_UseTeleport(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(useData->taskManager);
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldSystem_LoadFieldOverlay(fieldSystem);
    FieldMoveEnvironment *fieldMoveEnvironment = FieldMove_CreateEnvironment(HEAP_ID_FIELD, useData->partySlot, fieldSystem->saveData);
    startMenu->exitTaskFunc = Task_UseTeleportInField;
    startMenu->exitTaskEnvironment = fieldMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
}

static BOOL Task_UseTeleportInField(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    FieldMoveEnvironment *fieldMoveEnvironment = TaskManager_GetEnvironment(taskManager);
    FieldMoveTaskEnvironment *fieldMoveTaskEnvironment = FieldMoveTask_CreateTeleportEnvironment(fieldSystem, fieldMoveEnvironment->mon, HEAP_ID_4);
    FreeToHeap(fieldMoveEnvironment);
    TaskManager_Jump(taskManager, Task_FieldTeleport, fieldMoveTaskEnvironment);
    return FALSE;
}

static u32 FieldMove_CheckDig(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (MapHeader_IsCave(checkData->mapId) != TRUE || MapHeader_IsEscapeRopeAllowed(checkData->mapId) != TRUE) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (Save_VarsFlags_CheckHaveFollower(Save_VarsFlags_Get(checkData->fieldSystem->saveData)) == TRUE) {
        return FIELD_MOVE_RESPONSE_HAVE_FOLLOWER;
    }

    return FIELD_MOVE_RESPONSE_OK;
}

static void FieldMove_UseDig(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(useData->taskManager);
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldSystem_LoadFieldOverlay(fieldSystem);
    FieldMoveEnvironment *fieldMoveEnvironment = FieldMove_CreateEnvironment(HEAP_ID_FIELD, useData->partySlot, fieldSystem->saveData);
    startMenu->exitTaskFunc = Task_UseDigInField;
    startMenu->exitTaskEnvironment = fieldMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
}

static BOOL Task_UseDigInField(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    FieldMoveEnvironment *fieldMoveEnvironment = TaskManager_GetEnvironment(taskManager);
    FieldMoveTaskEnvironment *fieldMoveTaskEnvironment = FieldMoveTask_CreateDigEnvironment(fieldSystem, fieldMoveEnvironment->mon, HEAP_ID_FIELD);
    sub_02028AD4(fieldSystem->unk98, sub_0202914C(10, fieldSystem->location->mapId, 4), 1);
    FreeToHeap(fieldMoveEnvironment);
    TaskManager_Jump(taskManager, Task_FieldDig, fieldMoveTaskEnvironment);
    return FALSE;
}

static u32 FieldMove_CheckSweetScent(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (FieldMove_CheckPalPark(checkData) == TRUE) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }

    return FIELD_MOVE_RESPONSE_OK;
}

static void FieldMove_UseSweetScent(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(useData->taskManager);
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldMoveEnvironment *fieldMoveEnvironment = FieldMove_CreateEnvironment(HEAP_ID_FIELD, useData->partySlot, fieldSystem->saveData);
    FieldSystem_LoadFieldOverlay(fieldSystem);
    startMenu->exitTaskFunc = Task_UseSweetScentInField;
    startMenu->exitTaskEnvironment = fieldMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
    sub_02028AD4(fieldSystem->unk98, sub_0202914C(11, fieldSystem->location->mapId, 11), 1);
}

static u32 FieldMove_CheckChatter(const FieldMoveCheckData *checkData) {
    if (checkData->fieldSystem->unk6C == 2 || checkData->fieldSystem->unk6C == 3) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }

    return FIELD_MOVE_RESPONSE_OK;
}

static void FieldMove_UseChatter(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(useData->taskManager);
    StartMenuTaskData *startMenu = TaskManager_GetEnvironment(useData->taskManager);
    FieldUseMoveEnvironment *useMoveEnvironment = FieldMove_CreateUseEnvironment(useData, checkData);
    FieldSystem_LoadFieldOverlay(fieldSystem);
    startMenu->exitTaskFunc = Task_UseChatterInField;
    startMenu->exitTaskEnvironment = useMoveEnvironment;
    startMenu->state = START_MENU_STATE_10;
}

static BOOL Task_UseChatterInField(TaskManager *taskManager) {
    FieldUseMoveEnvironment *useMoveEnvironment = TaskManager_GetEnvironment(taskManager);
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    StartScriptFromMenu(taskManager, std_menu_chatter, NULL);
    FieldMove_SetArgs(fieldSystem, useMoveEnvironment->useData.partySlot, 0, 0, 0);
    FieldMove_DeleteUseEnvironment(useMoveEnvironment);
    return FALSE;
}
