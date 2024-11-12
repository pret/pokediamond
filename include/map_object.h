#ifndef POKEDIAMOND_MAP_OBJECT_H
#define POKEDIAMOND_MAP_OBJECT_H

#include "global.h"

#include "field_system.h"
#include "field_types_def.h"
#include "filesystem.h"
#include "heap.h"
#include "unk_0200CA44.h"

typedef void (*LocalMapObject_UnkCallback)(LocalMapObject *object);

typedef struct SavedMapObject {
    u32 flags;
    u32 flags2;
    u8 objId;
    u8 movement;
    s8 xRange;
    s8 yRange;
    s8 initialFacing;
    s8 currentFacing;
    s8 nextFacing;
    u16 mapId;
    u16 spriteId;
    u16 type;
    u16 eventFlag;
    u16 script;
    s16 param[3];
    s16 initialX;
    s16 initialY;
    s16 initialZ;
    s16 currentX;
    s16 currentY;
    s16 currentZ;
    fx32 vecY;
    u8 unk30[16];
    u8 unk40[16];
} SavedMapObject;

struct MapObjectManager {
    u32 flags;
    u32 objectCount;
    u32 unk8;
    u32 priority;
    u8 padding[0x4];
    NARC *mapModelNarc;
    u32 unk18;
    u8 padding2[0x104];
    u32 unk120;
    LocalMapObject *objects;
    FieldSystem *fieldSystem;
};

struct LocalMapObject {
    u32 flags;
    u32 flags2;
    u32 id;
    u32 mapId;
    u32 spriteId;
    u32 movement;
    u32 type;
    u32 eventFlag;
    u32 scriptId;
    u32 initialFacing;
    u32 currentFacing;
    u32 nextFacing;
    u32 previousFacing;
    u32 nextFacingBackup;
    s32 param[3];
    s32 xRange;
    s32 yRange;
    u32 initialX;
    u32 initialY;
    u32 initialZ;
    u32 previousX;
    u32 previousY;
    u32 previousZ;
    u32 currentX;
    s32 currentY;
    u32 currentZ;
    VecFx32 positionVector;
    VecFx32 facingVector;
    VecFx32 unk88;
    VecFx32 unk94;
    u32 unkA0;
    u32 movementCmd;
    u32 movementStep;
    u16 unkAC;
    u16 unkAE;
    SysTask *unkB0;
    MapObjectManager *manager;
    LocalMapObject_UnkCallback unkB8;
    LocalMapObject_UnkCallback unkBC;
    LocalMapObject_UnkCallback unkC0;
    LocalMapObject_UnkCallback unkC4;
    LocalMapObject_UnkCallback unkC8;
    LocalMapObject_UnkCallback unkCC;
    LocalMapObject_UnkCallback unkD0;
    LocalMapObject_UnkCallback unkD4;
    u8 unkD8[0x10];
    u8 unkE8[0x10];
    u8 unkF8[0x10];
    u8 unk108[0x20];
};

struct ObjectEvent {
    u16 id;
    u16 spriteId;
    u16 movement;
    u16 type;
    u16 eventFlag;
    u16 scriptId;
    s16 facingDirection;
    u16 param[3];
    s16 xRange;
    s16 yRange;
    u16 x;
    u16 z;
    s32 y;
    // todo this should be in map_events_internal.h
};

typedef enum MapObjectFlagBits {
    MAPOBJECTFLAG_ACTIVE          = (1 << 0),
    MAPOBJECTFLAG_SINGLE_MOVEMENT = (1 << 1),
    MAPOBJECTFLAG_UNK2            = (1 << 2),
    MAPOBJECTFLAG_UNK3            = (1 << 3),
    MAPOBJECTFLAG_UNK4            = (1 << 4),
    MAPOBJECTFLAG_UNK5            = (1 << 5),
    MAPOBJECTFLAG_MOVEMENT_PAUSED = (1 << 6),
    MAPOBJECTFLAG_UNK7            = (1 << 7),
    MAPOBJECTFLAG_UNK8            = (1 << 8),
    MAPOBJECTFLAG_VISIBLE         = (1 << 9),
    MAPOBJECTFLAG_KEEP            = (1 << 10),
    MAPOBJECTFLAG_UNK11           = (1 << 11),
    MAPOBJECTFLAG_UNK12           = (1 << 12),
    MAPOBJECTFLAG_UNK13           = (1 << 13),
    MAPOBJECTFLAG_UNK14           = (1 << 14),
    MAPOBJECTFLAG_UNK15           = (1 << 15),
    MAPOBJECTFLAG_UNK16           = (1 << 16),
    MAPOBJECTFLAG_UNK17           = (1 << 17),
    MAPOBJECTFLAG_UNK18           = (1 << 18),
    MAPOBJECTFLAG_UNK19           = (1 << 19),
    MAPOBJECTFLAG_UNK20           = (1 << 20),
    MAPOBJECTFLAG_UNK21           = (1 << 21),
    MAPOBJECTFLAG_UNK22           = (1 << 22),
    MAPOBJECTFLAG_IGNORE_HEIGHTS  = (1 << 23),
    MAPOBJECTFLAG_UNK24           = (1 << 24),
    MAPOBJECTFLAG_UNK25           = (1 << 25),
    MAPOBJECTFLAG_UNK26           = (1 << 26),
    MAPOBJECTFLAG_UNK27           = (1 << 27),
    MAPOBJECTFLAG_UNK28           = (1 << 28),
    MAPOBJECTFLAG_UNK29           = (1 << 29),
    MAPOBJECTFLAG_UNK30           = (1 << 30),
    MAPOBJECTFLAG_UNK31           = (1 << 31),
} MapObjectFlagBits;

// this may be the same as above, I don't know
typedef enum MapObjectManagerFlagBits {
    MAPOBJECTMANAGERFLAG_NONE = 0,
    MAPOBJECTMANAGERFLAG_UNK0 = (1 << 0),
    MAPOBJECTMANAGERFLAG_UNK1 = (1 << 1),
    MAPOBJECTMANAGERFLAG_UNK2 = (1 << 2),
    MAPOBJECTMANAGERFLAG_UNK3 = (1 << 3),
} MapObjectManagerFlagBits;

#define MAP_OBJECT_GFX_ID_INVALID 0xFFFF

typedef struct MapObjectInitArgs {
    u32 mapNo;
    int objectEventCount;
    int index;
    MapObjectManager *manager;
    ObjectEvent *objectEvents;
} MapObjectInitArgs;

typedef struct UnkLMOCallbackStruct {
    u32 unk0;
    LocalMapObject_UnkCallback unk4;
    LocalMapObject_UnkCallback unk8;
    LocalMapObject_UnkCallback unkC;
    LocalMapObject_UnkCallback unk10;
} UnkLMOCallbackStruct;

typedef struct UnkLMOCallbackStruct2 {
    LocalMapObject_UnkCallback unk0;
    LocalMapObject_UnkCallback unk4;
    LocalMapObject_UnkCallback unk8;
    LocalMapObject_UnkCallback unkC;
    LocalMapObject_UnkCallback unk10;
} UnkLMOCallbackStruct2;

typedef struct UnkLMOCallbackStruct3 {
    u32 spriteId;
    UnkLMOCallbackStruct2 *callbackStruct;
} UnkLMOCallbackStruct3;

MapObjectManager *MapObjectManager_Init(FieldSystem *fieldSystem, u32 objectCount, u32 priority);
void MapObjectManager_Delete(MapObjectManager *manager);
void sub_020573C8(MapObjectManager *manager, u32 unused, u32 mapId, u32 objectCount, ObjectEvent *objectEvents);
LocalMapObject *MapObject_Create(MapObjectManager *manager, u32 x, u32 y, u32 direction, u32 sprite, u32 movement, u32 mapNo);
LocalMapObject *MapObject_CreateFromObjectEventWithId(MapObjectManager *manager, u16 id, u32 objectEventCount, u32 mapNo, const ObjectEvent *events);
void sub_02057614(LocalMapObject *object, u32 sprite);
void sub_02057634(LocalMapObject *object, u32 sprite);
void MapObject_Remove(LocalMapObject *object);
void MapObject_Delete(LocalMapObject *object);
void sub_020576A8(LocalMapObject *object);
void MapObjectManager_RemoveAllActiveObjects(MapObjectManager *manager);
void sub_02057750(MapObjectManager *manager);
void sub_020577A8(MapObjectManager *manager);
void FieldSystem_SyncMapObjectsToSaveEx(FieldSystem *fieldSystem, MapObjectManager *manager, SavedMapObject *savedObjects, s32 count);
void MapObjectManager_RestoreFromSave(MapObjectManager *manager, SavedMapObject *savedObjects, u32 objectCount);
void MapObject_CreateFromMultipleObjectEvents(MapObjectManager *manager, u32 mapNo, u32 objectEventCount, ObjectEvent *objectEvents);
LocalMapObject *MapObjectManager_GetFirstActiveObjectByID(MapObjectManager *manager, u32 id);
LocalMapObject *MapObjectManager_GetFirstActiveObjectWithMovement(MapObjectManager *manager, u32 movement);
BOOL MapObjectManager_GetNextObjectWithFlagFromIndex(MapObjectManager *manager, LocalMapObject **objectDest, s32 *index, MapObjectFlagBits flag);
u32 MapObject_GetPriorityPlusValue(LocalMapObject *object, u32 value);
BOOL sub_020582A8(LocalMapObject *object, u32 objectId, u32 mapId);
BOOL sub_020582F8(LocalMapObject *object, u32 spriteId, u32 objectId, u32 mapId);
u32 MapObjectManager_GetObjectCount(MapObjectManager *manager);
void MapObjectManager_SetFlagsBits(MapObjectManager *manager, MapObjectManagerFlagBits bits);
void MapObjectManager_ClearFlagsBits(MapObjectManager *manager, MapObjectManagerFlagBits bits);
u32 MapObjectManager_GetFlagsBitsMask(MapObjectManager *manager, MapObjectManagerFlagBits bits);
u32 MapObjectManager_GetPriority(MapObjectManager *manager);
void *sub_020583A0(MapObjectManager *manager);
void sub_020583A4(MapObjectManager *manager, u32 param1);
u32 sub_020583AC(MapObjectManager *manager);
LocalMapObject *MapObjectManager_GetObjects2(MapObjectManager *manager);
LocalMapObject *MapObjectManager_GetObjects(MapObjectManager *manager);
void MapObjectArray_NextObject(LocalMapObject **objects);
void MapObjectManager_SetMapModelNarc(MapObjectManager *manager, NARC *mapModelNarc);
NARC *MapObjectManager_GetMapModelNarc(MapObjectManager *manager);
void MapObject_SetFlagsBits(LocalMapObject *object, MapObjectFlagBits bits);
void MapObject_ClearFlagsBits(LocalMapObject *object, MapObjectFlagBits bits);
u32 MapObject_GetFlagsBitsMask(LocalMapObject *object, MapObjectFlagBits bits);
BOOL MapObject_TestFlagsBits(LocalMapObject *object, MapObjectFlagBits bits);
void MapObject_SetID(LocalMapObject *object, u32 id);
u32 MapObject_GetID(LocalMapObject *object);
u32 MapObject_GetMapID(LocalMapObject *object);
void MapObject_SetSpriteID(LocalMapObject *object, u32 spriteId);
u32 MapObject_GetSpriteID(LocalMapObject *object);
u32 sub_0205845C(LocalMapObject *object);
u32 MapObject_GetMovement(LocalMapObject *object);
void MapObject_SetType(LocalMapObject *object, u32 type);
u32 MapObject_GetType(LocalMapObject *object);
void MapObject_SetEventFlag(LocalMapObject *object, u32 eventFlag);
void MapObject_SetScriptID(LocalMapObject *object, u32 scriptId);
u32 MapObject_GetScriptID(LocalMapObject *object);
u32 MapObject_GetInitialFacingDirection(LocalMapObject *object);
void MapObject_SetFacingDirectionDirect(LocalMapObject *object, u32 direction);
void MapObject_SetFacingDirection(LocalMapObject *object, u32 direction);
u32 MapObject_GetFacingDirection(LocalMapObject *object);
u32 MapObject_GetPreviousFacingDirection(LocalMapObject *object);
void MapObject_SetNextFacingDirection(LocalMapObject *object, u32 direction);
u32 MapObject_GetNextFacingDirection(LocalMapObject *object);
void MapObject_SetOrQueueFacing(LocalMapObject *object, u32 direction);
void MapObject_SetParam(LocalMapObject *object, s32 value, u32 param);
s32 MapObject_GetParam(LocalMapObject *object, u32 param);
void MapObject_SetXRange(LocalMapObject *object, s32 xRange);
s32 MapObject_GetXRange(LocalMapObject *object);
void MapObject_SetYRange(LocalMapObject *object, s32 yRange);
s32 MapObject_GetYRange(LocalMapObject *object);
void sub_02058544(LocalMapObject *object, u32 param1);
u32 sub_0205854C(LocalMapObject *object);
MapObjectManager *MapObject_GetManager(LocalMapObject *object);
u8 *sub_0205858C(LocalMapObject *object, s32 size);
u8 *sub_020585B0(LocalMapObject *object);
u8 *sub_020585B4(LocalMapObject *object, s32 size);
u8 *sub_020585D8(LocalMapObject *object);
u8 *sub_020585DC(LocalMapObject *object, s32 size);
u8 *sub_02058600(LocalMapObject *object);
u8 *sub_02058604(LocalMapObject *object, s32 size);
u8 *sub_02058628(LocalMapObject *object);
void sub_02058638(LocalMapObject *object);
void sub_0205864C(LocalMapObject *object);
void sub_020586A0(LocalMapObject *object);
void sub_020586DC(LocalMapObject *object);
void MapObject_SetMovementCommand(LocalMapObject *object, u32 command);
u32 MapObject_GetMovementCommand(LocalMapObject *object);
void MapObject_SetMovementStep(LocalMapObject *object, u32 step);
void MapObject_IncrementMovementStep(LocalMapObject *object);
u32 MapObject_GetMovementStep(LocalMapObject *object);
void sub_02058718(LocalMapObject *object, u16 param1);
u16 sub_02058720(LocalMapObject *object);
void sub_02058728(LocalMapObject *object, u16 param1);
u16 sub_02058730(LocalMapObject *object);
FieldSystem *MapObject_GetFieldSystem(LocalMapObject *object);
u32 MapObject_GetPriority(LocalMapObject *object);
u32 sub_02058750(LocalMapObject *object);
void sub_02058768(MapObjectManager *manager);
void sub_02058774(MapObjectManager *manager);
void MapObjectManager_PauseAllMovement(MapObjectManager *manager);
void MapObjectManager_UnpauseAllMovement(MapObjectManager *manager);
BOOL sub_020587E0(MapObjectManager *manager);
u32 sub_020587F4(LocalMapObject *object, MapObjectManagerFlagBits bits);
void sub_02058804(MapObjectManager *manager, BOOL clear);
BOOL sub_0205881C(MapObjectManager *manager);
BOOL MapObject_CheckActive(LocalMapObject *object);
void MapObject_SetSingleMovement(LocalMapObject *object);
void MapObject_ClearSingleMovement(LocalMapObject *object);
BOOL MapObject_CheckSingleMovement(LocalMapObject *object);
void MapObject_SetFlag2(LocalMapObject *object);
void MapObject_ClearFlag3(LocalMapObject *object);
BOOL MapObject_CheckFlag14(LocalMapObject *object);
BOOL MapObject_CheckVisible(LocalMapObject *object);
void MapObject_SetVisible(LocalMapObject *object, BOOL set);
void MapObject_ClearFlag18(LocalMapObject *object, BOOL clear);
BOOL MapObject_CheckFlag19Disabled(LocalMapObject *object);
void MapObject_SetFlag19(LocalMapObject *object, BOOL set);
void MapObject_PauseMovement(LocalMapObject *object);
void MapObject_UnpauseMovement(LocalMapObject *object);
BOOL MapObject_CheckMovementPaused(LocalMapObject *object);
BOOL sub_02058934(LocalMapObject *object);
void MapObject_SetIgnoreHeights(LocalMapObject *object, BOOL set);
BOOL MapObject_CheckIgnoreHeights(LocalMapObject *object);
void MapObject_SetKeep(LocalMapObject *object, BOOL set);
BOOL MapObject_CheckFlag25(LocalMapObject *object);
void MapObject_SetFlag26(LocalMapObject *object, BOOL set);
BOOL MapObject_CheckFlag26(LocalMapObject *object);
void MapObject_SetFlag27(LocalMapObject *object, BOOL set);
BOOL MapObject_CheckFlag27(LocalMapObject *object);
void MapObject_SetFlag28(LocalMapObject *object, BOOL set);
BOOL MapObject_CheckFlag28(LocalMapObject *object);
void MapObject_SetFlag24(LocalMapObject *object, BOOL set);
BOOL MapObject_CheckFlag24(LocalMapObject *object);
BOOL MapObject_CheckFlag4(LocalMapObject *object);
void MapObject_SetFlag29(LocalMapObject *object, BOOL set);
BOOL MapObject_CheckFlag29(LocalMapObject *object);
u32 MapObject_GetInitialX(LocalMapObject *object);
u32 MapObject_GetInitialY(LocalMapObject *object);
u32 MapObject_GetInitialZ(LocalMapObject *object);
u32 MapObject_GetPreviousX(LocalMapObject *object);
void MapObject_SetPreviousX(LocalMapObject *object, u32 previousX);
u32 MapObject_GetPreviousY(LocalMapObject *object);
void MapObject_SetPreviousY(LocalMapObject *object, u32 previousY);
u32 MapObject_GetPreviousZ(LocalMapObject *object);
void MapObject_SetPreviousZ(LocalMapObject *object, u32 previousZ);
u32 MapObject_GetCurrentX(LocalMapObject *object);
void MapObject_SetCurrentX(LocalMapObject *object, u32 currentX);
void MapObject_AddCurrentX(LocalMapObject *object, u32 currentX);
s32 MapObject_GetCurrentY(LocalMapObject *object);
void MapObject_SetCurrentY(LocalMapObject *object, s32 currentY);
void MapObject_AddCurrentY(LocalMapObject *object, s32 currentY);
u32 MapObject_GetCurrentZ(LocalMapObject *object);
void MapObject_SetCurrentZ(LocalMapObject *object, u32 currentZ);
void MapObject_AddCurrentZ(LocalMapObject *object, u32 currentZ);
void MapObject_CopyPositionVector(LocalMapObject *object, VecFx32 *positionVector);
void MapObject_SetPositionVector(LocalMapObject *object, VecFx32 *positionVector);
VecFx32 *MapObject_GetPositionVector(LocalMapObject *object);
fx32 MapObject_GetPositionVectorYCoord(LocalMapObject *object);
void MapObject_CopyFacingVector(LocalMapObject *object, VecFx32 *facingVector);
void MapObject_SetFacingVector(LocalMapObject *object, VecFx32 *facingVector);
void sub_02058BA4(LocalMapObject *object, VecFx32 *vector);
void sub_02058BB4(LocalMapObject *object, VecFx32 *vector);
void sub_02058BC4(LocalMapObject *object, VecFx32 *vector);
void sub_02058BD4(LocalMapObject *object, VecFx32 *vector);
u32 MapObject_GetPositionVectorYCoordUInt(LocalMapObject *object);
LocalMapObject *MapObjectManager_GetFirstObjectWithXAndZ(MapObjectManager *manager, u32 x, u32 z);
void LocalMapObject_SetPositionFromVectorAndDirection(LocalMapObject *object, VecFx32 *positionVector, u32 direction);
void MapObject_SetPositionFromXYZAndDirection(LocalMapObject *object, u32 x, u32 y, u32 z, u32 direction);
void sub_02058E90(LocalMapObject *object, u32 movement);
void sub_02058EB0(LocalMapObject *object, u32 id);
void sub_02058EC8(LocalMapObject *object);
void sub_02058ECC(LocalMapObject *object);
void sub_02058ED0(LocalMapObject *object);
void sub_02058ED4(LocalMapObject *object);
void sub_02058ED8(LocalMapObject *object);
void sub_02058EDC(LocalMapObject *object);
void sub_02058EE0(LocalMapObject *object);
void sub_02058EE4(LocalMapObject *object);

#endif // POKEDIAMOND_MAP_OBJECT_H
