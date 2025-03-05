#ifndef POKEDIAMOND_PLAYER_AVATAR_H
#define POKEDIAMOND_PLAYER_AVATAR_H

#include "global.h"

#include "field_types_def.h"

typedef struct PlayerSaveData {
    u8 padding[0x8];
} PlayerSaveData;

struct PlayerAvatar {
    u8 padding0[0x3C];
}; // TODO: populate once we know more

PlayerAvatar *PlayerAvatar_CreateWithParams(MapObjectManager *mapObjectManager, u32 x, s32 z, u32 direction, u32 state, u32 gender, PlayerSaveData *playerSaveData);
PlayerAvatar *PlayerAvatar_CreateWithActiveMapObject(MapObjectManager *mapObjectManager, PlayerSaveData *playerSaveData, u32 gender);
void sub_02055108(PlayerAvatar *avatar);
void PlayerAvatar_FreeToHeap(PlayerAvatar *avatar);
void PlayerAvatar_DeleteFromMap(PlayerAvatar *avatar);
LocalMapObject *MapObjectManager_GetFirstActiveObjectWithMovement1(MapObjectManager *manager);
u32 PlayerAvatar_GetFacingDirection(PlayerAvatar *avatar);
void PlayerAvatar_SetFacingDirection(PlayerAvatar *avatar, u32 direction);
u32 PlayerAvatar_GetNextFacingDirection(PlayerAvatar *avatar);

#endif // POKEDIAMOND_PLAYER_AVATAR_H
