#include "player_avatar.h"

#include "global.h"

#include "map_object.h"

static PlayerAvatar *PlayerAvatar_Create(void);
static void PlayerAvatar_Setup(PlayerAvatar *avatar, u32 state, u32 gender, PlayerSaveData *playerSaveData);
static void PlayerAvatar_CreateMapObjectWithParams(PlayerAvatar *avatar, MapObjectManager *manager, u32 sprite, u32 direction, u32 x, s32 z);
static LocalMapObject *PlayerAvatar_GetActiveMapObjectWithMovement1(MapObjectManager *manager);

extern u32 PlayerAvatar_GetSpriteByStateAndGender(u32 state, u32 gender);
extern u32 PlayerSaveData_GetState(PlayerSaveData *playerSaveData);
extern void PlayerAvatar_SetMapObject(PlayerAvatar *avatar, LocalMapObject *mapObject);
extern LocalMapObject *PlayerAvatar_GetMapObject(PlayerAvatar *avatar);
extern void ov05_021EDBC8(PlayerAvatar *avatar);
extern u32 PlayerAvatar_GetState(PlayerAvatar *avatar);
extern u32 PlayerAvatar_GetXCoord(PlayerAvatar *avatar);
extern s32 PlayerAvatar_GetZCoord(PlayerAvatar *avatar);
extern u32 ov06_0224ABAC(LocalMapObject *mapObject, u32 x, s32 z, u32 direction, u32 param4);
extern void sub_02055450(PlayerAvatar *avatar, u32 param1);
extern void PlayerAvatar_SetPlayerSaveData(PlayerAvatar *avatar, PlayerSaveData *saveData);
extern void sub_0205536C(PlayerAvatar *avatar, u32 param1);
extern void sub_02055374(PlayerAvatar *avatar, u32 param1);
extern void PlayerAvatar_SetState(PlayerAvatar *avatar, u32 state);
extern void PlayerAvatar_SetGender(PlayerAvatar *avatar, u32 gender);
extern void PlayerAvatar_SetTransitionFlags(PlayerAvatar *avatar, u32 flags);
extern void sub_02055410(PlayerAvatar *avatar);
extern void sub_0205542C(PlayerAvatar *avatar, s32 param1);
extern void sub_02055434(PlayerAvatar *avatar, s32 param1);
extern void sub_02055460(PlayerAvatar *avatar, u32 param1);
extern void sub_020556C8(PlayerAvatar *avatar, u32 param1);
extern void sub_0205574C(PlayerAvatar *avatar, u32 param1);

PlayerAvatar *PlayerAvatar_CreateWithParams(MapObjectManager *manager, u32 x, s32 z, u32 direction, u32 state, u32 gender, PlayerSaveData *playerSaveData) {
    PlayerAvatar *avatar = PlayerAvatar_Create();
    PlayerAvatar_Setup(avatar, state, gender, playerSaveData);
    u32 sprite = PlayerAvatar_GetSpriteByStateAndGender(state, gender);
    PlayerAvatar_CreateMapObjectWithParams(avatar, manager, sprite, direction, x, z);
    return avatar;
}

PlayerAvatar *PlayerAvatar_CreateWithActiveMapObject(MapObjectManager *manager, PlayerSaveData *playerSaveData, u32 gender) {
    PlayerAvatar *avatar = PlayerAvatar_Create();
    u32 state = PlayerSaveData_GetState(playerSaveData);
    PlayerAvatar_Setup(avatar, state, gender, playerSaveData);
    LocalMapObject *mapObject = PlayerAvatar_GetActiveMapObjectWithMovement1(manager);
    MapObject_SetSpriteID(mapObject, PlayerAvatar_GetSpriteByStateAndGender(state, gender));
    MapObject_SetFlagsBits(mapObject, (MapObjectFlagBits)(MAPOBJECTFLAG_UNK13 | MAPOBJECTFLAG_KEEP));
    MapObject_ClearFlagsBits(mapObject, (MapObjectFlagBits)(MAPOBJECTFLAG_UNK8 | MAPOBJECTFLAG_UNK7));
    MapObject_SetFlag29(mapObject, TRUE);
    PlayerAvatar_SetMapObject(avatar, mapObject);
    return avatar;
}

void sub_02055108(PlayerAvatar *avatar) {
    LocalMapObject *mapObject = PlayerAvatar_GetMapObject(avatar);
    GF_ASSERT(mapObject != NULL);
    MapObject_GetManager(mapObject);
    ov05_021EDBC8(avatar);
    if (PlayerAvatar_GetState(avatar) == PLAYER_STATE_SURFING) {
        u32 x = PlayerAvatar_GetXCoord(avatar);
        s32 z = PlayerAvatar_GetZCoord(avatar);
        u32 direction = PlayerAvatar_GetFacingDirection(avatar);
        sub_02055450(avatar, ov06_0224ABAC(mapObject, x, z, direction, 1));
    }
}

void PlayerAvatar_FreeToHeap(PlayerAvatar *avatar) {
    FreeToHeap(avatar);
}

void PlayerAvatar_DeleteFromMap(PlayerAvatar *avatar) {
    MapObject_Remove(PlayerAvatar_GetMapObject(avatar));
    PlayerAvatar_FreeToHeap(avatar);
}

static PlayerAvatar *PlayerAvatar_Create(void) {
    PlayerAvatar *avatar = AllocFromHeap(HEAP_ID_FIELD, sizeof(PlayerAvatar));
    GF_ASSERT(avatar != NULL);
    memset(avatar, 0, sizeof(PlayerAvatar));
    return avatar;
}

static void PlayerAvatar_Setup(PlayerAvatar *avatar, u32 state, u32 gender, PlayerSaveData *playerSaveData) {
    PlayerAvatar_SetPlayerSaveData(avatar, playerSaveData);
    sub_0205536C(avatar, 0);
    sub_02055374(avatar, 0);
    PlayerAvatar_SetState(avatar, state);
    PlayerAvatar_SetGender(avatar, gender);
    PlayerAvatar_SetTransitionFlags(avatar, 0);
    sub_02055410(avatar);
    sub_0205542C(avatar, -1);
    sub_02055434(avatar, -1);
    sub_02055460(avatar, 255);
    sub_020556C8(avatar, 1);
    sub_0205574C(avatar, 1);
}

static void PlayerAvatar_CreateMapObjectWithParams(PlayerAvatar *avatar, MapObjectManager *manager, u32 sprite, u32 direction, u32 x, s32 z) {
    LocalMapObject *mapObject = MapObject_Create(manager, x, z, direction, sprite, 1, 1);
    GF_ASSERT(mapObject != NULL);
    MapObject_SetID(mapObject, 255);
    MapObject_SetType(mapObject, 0);
    MapObject_SetEventFlag(mapObject, 0);
    MapObject_SetScriptID(mapObject, 0);
    MapObject_SetParam(mapObject, 0, 0);
    MapObject_SetParam(mapObject, 0, 1);
    MapObject_SetParam(mapObject, 0, 2);
    MapObject_SetXRange(mapObject, -1);
    MapObject_SetYRange(mapObject, -1);
    MapObject_SetFlagsBits(mapObject, (MapObjectFlagBits)(MAPOBJECTFLAG_UNK13 | MAPOBJECTFLAG_KEEP));
    MapObject_ClearFlagsBits(mapObject, (MapObjectFlagBits)(MAPOBJECTFLAG_UNK8 | MAPOBJECTFLAG_UNK7));
    MapObject_SetFlag29(mapObject, TRUE);
    PlayerAvatar_SetMapObject(avatar, mapObject);
}

LocalMapObject *MapObjectManager_GetFirstActiveObjectWithMovement1(MapObjectManager *manager) {
    s32 index = 0;
    LocalMapObject *mapObject = NULL;
    while (MapObjectManager_GetNextObjectWithFlagFromIndex(manager, &mapObject, &index, MAPOBJECTFLAG_ACTIVE)) {
        if (MapObject_GetMovement(mapObject) == 1) {
            break;
        }
    }
    return mapObject;
}

static LocalMapObject *PlayerAvatar_GetActiveMapObjectWithMovement1(MapObjectManager *manager) {
    LocalMapObject *mapObject = MapObjectManager_GetFirstActiveObjectWithMovement1(manager);
    GF_ASSERT(mapObject != NULL);
    return mapObject;
}

u32 PlayerAvatar_GetFacingDirection(PlayerAvatar *avatar) {
    return MapObject_GetFacingDirection(PlayerAvatar_GetMapObject(avatar));
}

void PlayerAvatar_SetFacingDirection(PlayerAvatar *avatar, u32 direction) {
    MapObject_SetFacingDirection(PlayerAvatar_GetMapObject(avatar), direction);
}

u32 PlayerAvatar_GetNextFacingDirection(PlayerAvatar *avatar) {
    return MapObject_GetNextFacingDirection(PlayerAvatar_GetMapObject(avatar));
}
