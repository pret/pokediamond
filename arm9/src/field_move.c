#include "field_move.h"

#include "global.h"

#include "constants/badge.h"
#include "constants/field_move_response.h"
#include "constants/global_fieldmap.h"
#include "constants/sprites.h"
#include "constants/std_script.h"
#include "constants/weather.h"

#include "map_header.h"
#include "map_object.h"
#include "player_data.h"
#include "save_local_field_data.h"
#include "start_menu.h"
#include "unk_0205EC84.h"
#include "unk_0205F7A0.h"

/*static*/ FieldUseMoveEnvironment *FieldMove_CreateUseEnvironment(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
/*static*/ void FieldMove_DeleteUseEnvironment(FieldUseMoveEnvironment *environment);
static u32 FieldMove_CheckCut(const FieldMoveCheckData *checkData);
static void FieldMove_UseCut(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static BOOL Task_UseCutInField(TaskManager *taskManager);
static u32 FieldMove_CheckFly(const FieldMoveCheckData *checkData);
static void FieldMove_UseFly(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
static u32 FieldMove_CheckSurf(const FieldMoveCheckData *checkData);

extern void sub_02063C70(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
extern void sub_02063D18(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
extern u32 sub_02063CE0(const FieldMoveCheckData *checkData);
extern void sub_02063DC0(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
extern u32 sub_02063D88(const FieldMoveCheckData *checkData);
extern void sub_02063E68(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
extern u32 sub_02063E30(const FieldMoveCheckData *checkData);
extern void sub_02063F10(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
extern u32 sub_02063ED8(const FieldMoveCheckData *checkData);
extern void sub_02063FCC(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
extern u32 sub_02063F80(const FieldMoveCheckData *checkData);
extern void sub_0206405C(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
extern u32 sub_0206403C(const FieldMoveCheckData *checkData);
extern void sub_02064134(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
extern u32 sub_020640CC(const FieldMoveCheckData *checkData);
extern void sub_020641F0(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
extern u32 sub_020641AC(const FieldMoveCheckData *checkData);
extern void sub_020642B4(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
extern u32 sub_02064284(const FieldMoveCheckData *checkData);
extern void sub_02064324(FieldMoveUseData *useData, const FieldMoveCheckData *checkData);
extern u32 sub_02064310(const FieldMoveCheckData *checkData);
extern void FieldSystem_GetFacingObject(FieldSystem *fieldSystem, LocalMapObject **object);
extern u16 GetPlayerXCoord(PlayerAvatar *playerAvatar);
extern u16 GetPlayerZCoord(PlayerAvatar *playerAvatar);
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

static const FieldMoveFuncData sFieldMoveFuncTable[] = {
    { FieldMove_UseCut, FieldMove_CheckCut  },
    { FieldMove_UseFly, FieldMove_CheckFly  },
    { sub_02063C70,     FieldMove_CheckSurf },
    { sub_02063D18,     sub_02063CE0        },
    { sub_02063DC0,     sub_02063D88        },
    { sub_02063E68,     sub_02063E30        },
    { sub_02063F10,     sub_02063ED8        },
    { sub_02063FCC,     sub_02063F80        },
    { sub_0206405C,     sub_0206403C        },
    { sub_02064134,     sub_020640CC        },
    { sub_020641F0,     sub_020641AC        },
    { sub_020642B4,     sub_02064284        },
    { sub_02064324,     sub_02064310        }
};

static inline BOOL FieldMove_CheckSafariOrPalPark(const FieldMoveCheckData *checkData) {
    if (Save_VarsFlags_CheckSafariSysFlag(Save_VarsFlags_Get(checkData->fieldSystem->saveData)) == TRUE || Save_VarsFlags_CheckPalParkSysFlag(Save_VarsFlags_Get(checkData->fieldSystem->saveData)) == TRUE) {
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

    s32 x = GetPlayerXCoord(fieldSystem->playerAvatar);
    s32 z = GetPlayerZCoord(fieldSystem->playerAvatar);
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

/*static*/ FieldUseMoveEnvironment *FieldMove_CreateUseEnvironment(FieldMoveUseData *useData, const FieldMoveCheckData *checkData) {
    FieldUseMoveEnvironment *environment = AllocFromHeap(HEAP_ID_32, sizeof(FieldUseMoveEnvironment));
    environment->magic = 0x19740205;
    environment->facingObject = checkData->facingObject;
    environment->useData = *useData;
    return environment;
}

/*static*/ void FieldMove_DeleteUseEnvironment(FieldUseMoveEnvironment *environment) {
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
    if (checkData->flag & FIELD_MOVE_CHECK_TREE) {
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
    if (!(checkData->flag & FIELD_MOVE_CHECK_WATER)) {
        return FIELD_MOVE_RESPONSE_NOT_HERE;
    }
    if (Save_VarsFlags_CheckHaveFollower(Save_VarsFlags_Get(checkData->fieldSystem->saveData)) == TRUE) {
        return FIELD_MOVE_RESPONSE_HAVE_FOLLOWER;
    }

    return FIELD_MOVE_RESPONSE_OK;
}
