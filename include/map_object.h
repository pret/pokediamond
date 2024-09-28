#ifndef POKEDIAMOND_MAP_OBJECT_H
#define POKEDIAMOND_MAP_OBJECT_H

#include "global.h"
#include "field_system.h"
#include "heap.h"

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
    u16 unk10;
    u16 spriteId;
    u16 type;
    u16 flagId;
    u16 script;
    s16 param[3];
    s16 initialX;
    s16 initialHeight;
    s16 initialY;
    s16 currentX;
    s16 currentHeight;
    s16 currentY;
    fx32 vecY;
    u8 unk30[16];
    u8 unk40[16];
} SavedMapObject;

typedef struct LocalMapObject {
    u8 padding[0x128]; //todo verify size
} LocalMapObject;

typedef struct ObjectEvent
{
    u8 padding[0x8];
    u16 flag;
    u8 padding2[0x16];
    //todo fill out
    //todo this should be in map_events_internal.h
} ObjectEvent;

typedef void (*LocalMapObject_UnkCallback)(LocalMapObject* object);

typedef enum MapObjectFlagBits {
    MAPOBJECTFLAG_ACTIVE = (1 << 0),
    MAPOBJECTFLAG_SINGLE_MOVEMENT = (1 << 1),
    MAPOBJECTFLAG_UNK2 = (1 << 2),
    MAPOBJECTFLAG_UNK3 = (1 << 3),
    MAPOBJECTFLAG_UNK4 = (1 << 4),
    MAPOBJECTFLAG_UNK5 = (1 << 5),
    MAPOBJECTFLAG_MOVEMENT_PAUSED = (1 << 6),
    MAPOBJECTFLAG_UNK7 = (1 << 7),
    MAPOBJECTFLAG_UNK8 = (1 << 8),
    MAPOBJECTFLAG_VISIBLE = (1 << 9),
    MAPOBJECTFLAG_UNK10 = (1 << 10),
    MAPOBJECTFLAG_UNK11 = (1 << 11),
    MAPOBJECTFLAG_UNK12 = (1 << 12),
    MAPOBJECTFLAG_UNK13 = (1 << 13),
    MAPOBJECTFLAG_UNK14 = (1 << 14),
    MAPOBJECTFLAG_UNK15 = (1 << 15),
    MAPOBJECTFLAG_UNK16 = (1 << 16),
    MAPOBJECTFLAG_UNK17 = (1 << 17),
    MAPOBJECTFLAG_UNK18 = (1 << 18),
    MAPOBJECTFLAG_UNK19 = (1 << 19),
    MAPOBJECTFLAG_UNK20 = (1 << 20),
    MAPOBJECTFLAG_UNK21 = (1 << 21),
    MAPOBJECTFLAG_UNK22 = (1 << 22),
    MAPOBJECTFLAG_IGNORE_HEIGHTS = (1 << 23),
    MAPOBJECTFLAG_UNK24 = (1 << 24),
    MAPOBJECTFLAG_UNK25 = (1 << 25),
    MAPOBJECTFLAG_UNK26 = (1 << 26),
    MAPOBJECTFLAG_UNK27 = (1 << 27),
    MAPOBJECTFLAG_UNK28 = (1 << 28),
    MAPOBJECTFLAG_UNK29 = (1 << 29),
    MAPOBJECTFLAG_UNK30 = (1 << 30),
    MAPOBJECTFLAG_UNK31 = (1 << 31),
} MapObjectFlagBits;

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

MapObjectManager *MapObjectManager_Init(FieldSystem *fieldSystem, u32 objectCount, u32 priority);
void MapObjectManager_Delete(MapObjectManager *manager);
void sub_020573C8(MapObjectManager *manager, u32 unused, u32 flagId, u32 objectCount, ObjectEvent *objectEvents);
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
u32 sub_0205829C(LocalMapObject *object, u32 param1);
BOOL sub_020582A8(LocalMapObject *object, u32 mapId, u32 flagId);

#endif //POKEDIAMOND_MAP_OBJECT_H
