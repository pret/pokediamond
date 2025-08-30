#ifndef POKEDIAMOND_PLAYER_AVATAR_H
#define POKEDIAMOND_PLAYER_AVATAR_H

#include "nitro/FX_types.h"

#include "global.h"

#include "field_types_def.h"

typedef enum PlayerAvatarFlags {
    AVATAR_FLAG_UNK0 = (1 << 0),
    AVATAR_FLAG_UNK1 = (1 << 1),
    AVATAR_FLAG_UNK2 = (1 << 2),
    AVATAR_FLAG_LOCK_BIKE_STATE = (1 << 3), // Blocks the player from mounting/dismounting their bike (though this was intended to stop dismounting during Cycling Road)
    AVATAR_FLAG_UNK4 = (1 << 4),
    AVATAR_FLAG_UNK5 = (1 << 5),
    AVATAR_FLAG_UNK6 = (1 << 6),
    AVATAR_FLAG_UNK7 = (1 << 7),
} PlayerAvatarFlags; // TODO: check if this is right

typedef struct PlayerSaveData {
    u16 unk0;
    u16 hasRunningShoes; // bool16
    s32 state;
} PlayerSaveData; // TODO: copied from heartgold, check if this is correct

struct PlayerAvatar {
    PlayerAvatarFlags flags;
    u32 transitionFlags;
    u32 unk8;
    u8 padding0[0x4];
    u32 unk10;
    u32 unk14;
    s32 state;
    u32 gender;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    LocalMapObject *mapObject;
    u32 unk30;
    PlayerSaveData *playerSaveData;
    u8 padding2[0x4];
}; // TODO: populate once we know more

PlayerAvatar *PlayerAvatar_CreateWithParams(MapObjectManager *mapObjectManager, u32 x, u32 z, u32 direction, s32 state, u32 gender, PlayerSaveData *playerSaveData);
PlayerAvatar *PlayerAvatar_CreateWithActiveMapObject(MapObjectManager *mapObjectManager, PlayerSaveData *playerSaveData, u32 gender);
void sub_02055108(PlayerAvatar *avatar);
void PlayerAvatar_FreeToHeap(PlayerAvatar *avatar);
void PlayerAvatar_DeleteFromMap(PlayerAvatar *avatar);
LocalMapObject *MapObjectManager_GetFirstActiveObjectWithMovement1(MapObjectManager *manager);
u32 PlayerAvatar_GetFacingDirection(PlayerAvatar *avatar);
void PlayerAvatar_SetFacingDirection(PlayerAvatar *avatar, u32 direction);
u32 PlayerAvatar_GetNextFacingDirection(PlayerAvatar *avatar);
u32 PlayerAvatar_GetXCoord(PlayerAvatar *avatar);
u32 PlayerAvatar_GetZCoord(PlayerAvatar *avatar);
u32 PlayerAvatar_GetPreviousXCoord(PlayerAvatar *avatar);
u32 PlayerAvatar_GetPreviousZCoord(PlayerAvatar *avatar);
void PlayerAvatar_CopyPositionVector(PlayerAvatar *avatar, VecFx32 *vector);
VecFx32 *PlayerAvatar_GetPositionVectorConst(PlayerAvatar *avatar);
void PlayerAvatar_SetUnk10(PlayerAvatar *avatar, u32 param1);
u32 PlayerAvatar_GetUnk10(PlayerAvatar *avatar);
void PlayerAvatar_SetUnk14(PlayerAvatar *avatar, u32 param1);
u32 PlayerAvatar_GetUnk14(PlayerAvatar *avatar);
void PlayerAvatar_ToggleVisible(PlayerAvatar *avatar, BOOL invisible);
void PlayerAvatar_SetMapObject(PlayerAvatar *avatar, LocalMapObject *mapObject);
LocalMapObject *PlayerAvatar_GetMapObject(PlayerAvatar *avatar);
void PlayerAvatar_SetState(PlayerAvatar *avatar, s32 state);
s32 PlayerAvatar_GetState(PlayerAvatar *avatar);
void PlayerAvatar_SetTransitionFlagsBits(PlayerAvatar *avatar, u32 flags);
void PlayerAvatar_SetTransitionFlags(PlayerAvatar *avatar, u32 flags);
u32 PlayerAvatar_GetTransitionFlags(PlayerAvatar *avatar);
u32 PlayerAvatar_GetGender(PlayerAvatar *avatar);
s32 PlayerAvatar_GetUnk20(PlayerAvatar *avatar);
void PlayerAvatar_SetUnk20(PlayerAvatar *avatar, s32 param1);
void PlayerAvatar_ClearUnk20ClearFlag2(PlayerAvatar *avatar);
s32 PlayerAvatar_Unk20AddWithCeiling(PlayerAvatar *avatar, s32 param1, s32 param2);
s32 PlayerAvatar_GetUnk24(PlayerAvatar *avatar);
s32 PlayerAvatar_GetUnk28(PlayerAvatar *avatar);
void PlayerAvatar_SetUnk24Unk28(PlayerAvatar *avatar, s32 unk24, s32 unk28);
void PlayerAvatar_SetUnk30(PlayerAvatar *avatar, u32 param1);
u32 PlayerAvatar_GetUnk30(PlayerAvatar *avatar);
PlayerSaveData *PlayerAvatar_GetPlayerSaveData(PlayerAvatar *avatar);
void PlayerAvatar_SetUnk8(PlayerAvatar *avatar, u32 param1);
u32 PlayerAvatar_GetUnk8(PlayerAvatar *avatar);
void PlayerSaveData_Init(PlayerSaveData *playerSaveData);
BOOL PlayerSaveData_CheckRunningShoes(PlayerSaveData *playerSaveData);
void PlayerSaveData_SetRunningShoesFlag(PlayerSaveData *playerSaveData, BOOL flag);
void PlayerAvatar_SetPlayerSaveDataUnk0(PlayerAvatar *playerAvatar, u16 unk0);
u16 PlayerAvatar_GetPlayerSaveDataUnk0(PlayerAvatar *playerAvatar);
void sub_020554EC(PlayerAvatar *avatar, VecFx32 *position, u32 direction);
void sub_02055514(PlayerAvatar *avatar, u32 x, u32 z, u32 direction);
void PlayerAvatar_SetMapObjectYPosition(PlayerAvatar *avatar, fx32 yVal);
void PlayerAvatar_ToggleAutomaticHeightUpdating(PlayerAvatar *avatar, u8 flag);
void PlayerAvatar_ToggleAutomaticHeightUpdatingImmediate(PlayerAvatar *avatar, BOOL flag);
u32 PlayerAvatar_GetSpriteByStateAndGender(s32 state, u32 gender);
u32 PlayerAvatar_GetTransitionBits(s32 state);
PlayerAvatar *FieldSystem_GetPlayerAvatar(FieldSystem *fieldSystem);
void PlayerAvatar_SetFlag0(PlayerAvatar *avatar, BOOL set);
BOOL PlayerAvatar_CheckFlag0(PlayerAvatar *avatar);
void PlayerAvatar_SetFlag1(PlayerAvatar *avatar, BOOL set);
BOOL PlayerAvatar_CheckFlag1(PlayerAvatar *avatar);
void PlayerAvatar_SetFlag2(PlayerAvatar *avatar, BOOL set);
BOOL PlayerAvatar_CheckFlag2(PlayerAvatar *avatar);
void PlayerAvatar_SetBikeStateLock(PlayerAvatar *avatar, BOOL lock);
BOOL PlayerAvatar_CheckBikeStateLocked(PlayerAvatar *avatar);
void PlayerAvatar_SetFlag4(PlayerAvatar *avatar, BOOL set);
BOOL PlayerAvatar_CheckFlag4(PlayerAvatar *avatar);
void PlayerAvatar_SetFlag5(PlayerAvatar *avatar, BOOL set);
BOOL PlayerAvatar_CheckFlag5(PlayerAvatar *avatar);
void PlayerAvatar_SetFlag6(PlayerAvatar *avatar);
void PlayerAvatar_ClearFlag6(PlayerAvatar *avatar);
BOOL PlayerAvatar_CheckFlag6(PlayerAvatar *avatar);
void PlayerAvatar_SetFlag7(PlayerAvatar *avatar, BOOL set);
BOOL PlayerAvatar_CheckFlag7(PlayerAvatar *avatar);

#endif // POKEDIAMOND_PLAYER_AVATAR_H
