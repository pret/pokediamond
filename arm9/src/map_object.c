#include "map_object.h"

#include "global.h"

#include "constants/sprites.h"

#include "field_system.h"
#include "heap.h"

extern UnkLMOCallbackStruct *UNK_020F6364[55];
extern UnkLMOCallbackStruct3 ov05_021F9494[210];

static MapObjectManager *MapObjectManager_New(u32 objectCount);
static LocalMapObject *MapObject_CreateFromObjectEvent(MapObjectManager *manager, ObjectEvent *objectEvent, u32 mapNo);
static void SavedMapObject_InitFromLocalMapObject(FieldSystem *fieldSystem, LocalMapObject *object, SavedMapObject *savedObject);
static void LocalMapObject_InitFromSavedMapObject(LocalMapObject *localObject, SavedMapObject *savedObject);
static void sub_02057AEC(MapObjectManager *manager, LocalMapObject *object);
static void sub_02057B34(LocalMapObject *object);
static void MapObject_ConvertXZToPositionVec(LocalMapObject *object);
static void MapObject_CreateFromInitArgs(MapObjectInitArgs *args);
static LocalMapObject *MapObjectManager_GetFirstInactiveObject(MapObjectManager *manager);
static LocalMapObject *sub_02057C98(MapObjectManager *manager, u32 id, u32 mapNo);
static void sub_02057CF0(MapObjectManager *manager, LocalMapObject *object);
static void MapObject_InitFromObjectEvent(LocalMapObject *object, ObjectEvent *objectEvent, FieldSystem *fieldSystem);
static void MapObject_SetPositionVectorFromObjectEvent(LocalMapObject *object, ObjectEvent *objectEvent);
static void sub_02057E90(LocalMapObject *object, MapObjectManager *manager);
/*static*/ void sub_02057EE0(LocalMapObject *object);
static void sub_02057F18(LocalMapObject *object);
static void MapObject_Clear(LocalMapObject *object);
static u32 sub_02057F90(LocalMapObject *object, u32 mapId, u32 objectEventCount, ObjectEvent *objectEvents);
static LocalMapObject *MapObjectManager_GetFirstObjectWithIDAndMap(MapObjectManager *manager, u32 objectId, u32 mapId);
static void sub_02058148(LocalMapObject *object);
/*static*/ void sub_0205815C(LocalMapObject *object);
static void MapObject_NoOp(LocalMapObject *object);
static u32 FieldSystem_ResolveObjectSpriteID(FieldSystem *fieldSystem, s32 spriteId);
static void sub_0205818C(LocalMapObject *object);
static void sub_020581A4(LocalMapObject *object);
static void sub_020581B4(LocalMapObject *object);
static BOOL MapObject_ScriptIDIsFFFF(LocalMapObject *object);
static void sub_02058214(LocalMapObject *object, ObjectEvent *objectEvent, u32 mapNo);
static void sub_02058258(LocalMapObject *object, u32 mapNo, ObjectEvent *objectEvent);
static void sub_0205832C(SysTask *task, LocalMapObject *object);
static void sub_02058348(LocalMapObject *object);
static MapObjectManager *MapObjectManager_Get(MapObjectManager *manager);
static void MapObjectManager_SetObjectCount(MapObjectManager *manager, u32 count);
static void sub_0205836C(MapObjectManager *manager);
static void sub_02058374(MapObjectManager *manager);
static void MapObjectManager_SetPriority(MapObjectManager *manager, u32 priority);
static void MapObjectManager_SetObjects(MapObjectManager *manager, LocalMapObject *objects);
static LocalMapObject *MapObjectManager_GetObjects3(MapObjectManager *manager);
static void MapObjectManager_SetFieldSystem(MapObjectManager *manager, FieldSystem *fieldSystem);
static FieldSystem *MapObjectManager_GetFieldSystem(MapObjectManager *manager);
static void MapObject_SetFlags(LocalMapObject *object, u32 flags);
static u32 MapObject_GetFlags(LocalMapObject *object);
static void MapObject_SetFlags2(LocalMapObject *object, u32 flags);
static u32 MapObject_GetFlags2(LocalMapObject *object);
static void MapObject_SetMapID(LocalMapObject *object, u32 mapId);
/*static*/ void MapObject_SetMovement(LocalMapObject *object, u32 movement);
static u32 MapObject_GetEventFlag(LocalMapObject *object);
static void MapObject_SetInitialFacingDirection(LocalMapObject *object, u32 initialFacing);
static void sub_02058554(LocalMapObject *object, SysTask *sysTask);
static SysTask *sub_0205855C(LocalMapObject *object);
static void sub_02058564(LocalMapObject *object);
static void MapObject_SetManager(LocalMapObject *object, MapObjectManager *manager);
static MapObjectManager *MapObject_GetManagerFromManager(LocalMapObject *object);
static void sub_02058630(LocalMapObject *object, LocalMapObject_UnkCallback callback);
static void sub_02058644(LocalMapObject *object, LocalMapObject_UnkCallback callback);
static void sub_02058658(LocalMapObject *object, LocalMapObject_UnkCallback callback);
/*static*/ void sub_02058660(LocalMapObject *object);
static void sub_0205866C(LocalMapObject *object);
static void sub_02058684(LocalMapObject *object, LocalMapObject_UnkCallback callback);
static void sub_0205868C(LocalMapObject *object);
static void sub_02058698(LocalMapObject *object, LocalMapObject_UnkCallback callback);
static void sub_020586AC(LocalMapObject *object, LocalMapObject_UnkCallback callback);
static void sub_020586B4(LocalMapObject *object);
static void sub_020586C0(LocalMapObject *object, LocalMapObject_UnkCallback callback);
static void sub_020586C8(LocalMapObject *object);
static void sub_020586D4(LocalMapObject *object, LocalMapObject_UnkCallback callback);
static void MapObject_SetFlag14(LocalMapObject *object);
static void MapObject_SetFlag25(LocalMapObject *object, BOOL set);
static void MapObject_SetInitialX(LocalMapObject *object, u32 initialX);
static void MapObject_SetInitialY(LocalMapObject *object, u32 initialY);
static void MapObject_SetInitialZ(LocalMapObject *object, u32 initialZ);
static void ObjectEvent_SetID(ObjectEvent *objectEvent, u16 id);
static u16 ObjectEvent_GetID(ObjectEvent *objectEvent);
static void ObjectEvent_SetSpriteID(ObjectEvent *objectEvent, u32 spriteId);
static u16 ObjectEvent_GetSpriteID(ObjectEvent *objectEvent);
static void ObjectEvent_SetMovement(ObjectEvent *objectEvent, u32 movement);
static u16 ObjectEvent_GetMovement(ObjectEvent *objectEvent);
static void ObjectEvent_SetType(ObjectEvent *objectEvent, u16 type);
static u16 ObjectEvent_GetType(ObjectEvent *objectEvent);
static void ObjectEvent_SetEventFlag(ObjectEvent *objectEvent, u16 eventFlag);
static u16 ObjectEvent_GetEventFlag(ObjectEvent *objectEvent);
static void ObjectEvent_SetScriptID(ObjectEvent *objectEvent, u16 scriptId);
static u16 ObjectEvent_GetScriptID(ObjectEvent *objectEvent);
static void ObjectEvent_SetFacingDirection(ObjectEvent *objectEvent, u32 facingDirection);
static s16 ObjectEvent_GetFacingDirection(ObjectEvent *objectEvent);
static void ObjectEvent_SetParam(ObjectEvent *objectEvent, s32 value, u32 param);
static u16 ObjectEvent_GetParam(ObjectEvent *objectEvent, u32 param);
static void ObjectEvent_SetXRange(ObjectEvent *objectEvent, s16 xRange);
static s16 ObjectEvent_GetXRange(ObjectEvent *objectEvent);
static void ObjectEvent_SetYRange(ObjectEvent *objectEvent, s16 yRange);
static s16 ObjectEvent_GetYRange(ObjectEvent *objectEvent);
static void ObjectEvent_SetXCoord(ObjectEvent *objectEvent, u32 x);
static u16 ObjectEvent_GetXCoord(ObjectEvent *template);
static void ObjectEvent_SetYCoord(ObjectEvent *objectEvent, u32 y);
static u32 ObjectEvent_GetYCoord(ObjectEvent *objectEvent);
static void ObjectEvent_SetZCoord(ObjectEvent *objectEvent, u32 z);
static u16 ObjectEvent_GetZCoord(ObjectEvent *objectEvent);
static ObjectEvent *ObjectEvent_GetByID(u16 id, s32 objectEventCount, ObjectEvent *objectEvents);
static BOOL ObjectEvent_ScriptIDIsUnset(ObjectEvent *objectEvent);
static u16 ObjectEvent_GetEventFlag_AssertScriptIDIsUnset(ObjectEvent *template);
static UnkLMOCallbackStruct *sub_02058D14(u32 movement);
static LocalMapObject_UnkCallback sub_02058D2C(UnkLMOCallbackStruct *callbackStruct);
static LocalMapObject_UnkCallback sub_02058D30(UnkLMOCallbackStruct *callbackStruct);
static LocalMapObject_UnkCallback sub_02058D34(UnkLMOCallbackStruct *callbackStruct);
static LocalMapObject_UnkCallback sub_02058D38(UnkLMOCallbackStruct2 *callbackStruct);
static LocalMapObject_UnkCallback sub_02058D3C(UnkLMOCallbackStruct2 *callbackStruct);
static LocalMapObject_UnkCallback sub_02058D40(UnkLMOCallbackStruct2 *callbackStruct);
static LocalMapObject_UnkCallback sub_02058D44(UnkLMOCallbackStruct2 *callbackStruct);
static LocalMapObject_UnkCallback sub_02058D48(UnkLMOCallbackStruct2 *callbackStruct);
static UnkLMOCallbackStruct2 *sub_02058D4C(u32 spriteId);

extern void ov05_021F2AF4(MapObjectManager *manager, void *param0);
extern BOOL ObjectEvent_ScriptIDIsUnset(ObjectEvent *objectEvent);
extern void sub_02057E90(LocalMapObject *object, MapObjectManager *manager);
extern u8 FieldSystem_FlagCheck(FieldSystem *fieldSystem, u16 flag);
extern MapObjectManager *MapObject_GetManagerFromManager(LocalMapObject *object);
extern void FieldSystem_FlagSet(FieldSystem *fieldSystem, u16 flag);
extern void sub_02058ED8(LocalMapObject *object);
extern void sub_02058EDC(LocalMapObject *object);
extern void sub_02058EE0(LocalMapObject *object);
extern void sub_02058EE4(LocalMapObject *object);
extern void sub_02057AEC(MapObjectManager *manager, LocalMapObject *object);
extern void sub_02059E60(s32 x, s32 y, VecFx32 *vector);
extern BOOL sub_02059EC8(FieldSystem *fieldSystem, VecFx32 *vector, BOOL flag);
extern void MapObject_ClearHeldMovement(LocalMapObject *object);
extern u16 FieldSystem_VarGetObjectEventGraphicsId(FieldSystem *fieldSystem, u16 spriteId);
extern u32 sub_02059D1C(LocalMapObject *object);
extern void sub_02058EE8(LocalMapObject *object);
extern void ov05_021F2E0C(LocalMapObject *object, BOOL set);
extern void sub_02058EF8(LocalMapObject *object);
extern void ov05_021F1D8C(LocalMapObject *object);
extern BOOL sub_0205C334(void);
extern u32 sub_0205C340(LocalMapObject *object);
extern void sub_02059C60(LocalMapObject *object);

MapObjectManager *MapObjectManager_Init(FieldSystem *fieldSystem, u32 objectCount, u32 priority) {
    MapObjectManager *ret = MapObjectManager_New(objectCount);
    MapObjectManager_SetFieldSystem(ret, fieldSystem);
    MapObjectManager_SetObjectCount(ret, objectCount);
    MapObjectManager_SetPriority(ret, priority);

    return ret;
}

void MapObjectManager_Delete(MapObjectManager *manager) {
    FreeToHeapExplicit(HEAP_ID_FIELD, MapObjectManager_GetObjects(manager));
    FreeToHeapExplicit(HEAP_ID_FIELD, manager);
}

void sub_020573C8(MapObjectManager *manager, u32 unused, u32 mapId, u32 objectCount, ObjectEvent *objectEvents) {
    u32 count               = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);

    for (; count != 0; count--) {
        if (MapObject_CheckActive(objects) == TRUE) {
            switch (sub_02057F90(objects, mapId, objectCount, objectEvents)) {
            case 0:
                if (MapObject_GetMapID(objects) != mapId && !MapObject_TestFlagsBits(objects, MAPOBJECTFLAG_KEEP)) {
                    MapObject_Remove(objects);
                }
                break;

            case 1:
            case 2:
                break;
            }
        }
        objects++;
    }

    ov05_021F2AF4(manager, sub_020583A0(manager));
}

static MapObjectManager *MapObjectManager_New(u32 objectCount) {
    LocalMapObject *objects;
    MapObjectManager *manager = AllocFromHeap(HEAP_ID_FIELD, sizeof(MapObjectManager));
    GF_ASSERT(manager != NULL);
    memset(manager, 0, sizeof(MapObjectManager));

    objects = AllocFromHeap(HEAP_ID_FIELD, objectCount * sizeof(LocalMapObject));
    GF_ASSERT(objects != NULL);
    memset(objects, 0, objectCount * sizeof(LocalMapObject));

    MapObjectManager_SetObjects(manager, objects);

    return manager;
}

static LocalMapObject *MapObject_CreateFromObjectEvent(MapObjectManager *manager, ObjectEvent *objectEvent, u32 mapNo) {
    LocalMapObject *ret;

    u32 objectId = ObjectEvent_GetID(objectEvent);
    if (!ObjectEvent_ScriptIDIsUnset(objectEvent)) {
        ret = sub_02057C98(manager, objectId, mapNo);
        if (ret != NULL) {
            sub_02058214(ret, objectEvent, mapNo);
            return ret;
        }
    } else {
        ret = MapObjectManager_GetFirstObjectWithIDAndMap(manager, objectId, ObjectEvent_GetEventFlag_AssertScriptIDIsUnset(objectEvent));
        if (ret != NULL) {
            sub_02058258(ret, mapNo, objectEvent);
            return ret;
        }
    }

    ret = MapObjectManager_GetFirstInactiveObject(manager);
    if (ret == NULL) {
        return ret;
    }

    MapObject_InitFromObjectEvent(ret, objectEvent, MapObjectManager_GetFieldSystem(manager));
    sub_02057E90(ret, manager);
    MapObject_SetMapID(ret, mapNo);
    sub_020581A4(ret);
    sub_020581B4(ret);
    MapObject_SetFlagsBits(ret, MAPOBJECTFLAG_UNK2);
    sub_02057CF0(manager, ret);
    sub_0205836C(MapObjectManager_Get(manager));
    return ret;
}

LocalMapObject *MapObject_Create(MapObjectManager *manager, u32 x, u32 y, u32 direction, u32 sprite, u32 movement, u32 mapNo) {
    ObjectEvent objectEvent;
    ObjectEvent_SetID(&objectEvent, 0);
    ObjectEvent_SetSpriteID(&objectEvent, sprite);
    ObjectEvent_SetMovement(&objectEvent, movement);
    ObjectEvent_SetType(&objectEvent, 0);
    ObjectEvent_SetEventFlag(&objectEvent, 0);
    ObjectEvent_SetScriptID(&objectEvent, 0);
    ObjectEvent_SetFacingDirection(&objectEvent, direction);
    ObjectEvent_SetParam(&objectEvent, 0, 0);
    ObjectEvent_SetParam(&objectEvent, 0, 1);
    ObjectEvent_SetParam(&objectEvent, 0, 2);
    ObjectEvent_SetXRange(&objectEvent, 0);
    ObjectEvent_SetYRange(&objectEvent, 0);
    ObjectEvent_SetXCoord(&objectEvent, x);
    ObjectEvent_SetZCoord(&objectEvent, y);
    ObjectEvent_SetYCoord(&objectEvent, 0);

    return MapObject_CreateFromObjectEvent(manager, &objectEvent, mapNo);
}

LocalMapObject *MapObject_CreateFromObjectEventWithId(MapObjectManager *manager, u16 id, u32 objectEventCount, u32 mapNo, const ObjectEvent *events) {
    LocalMapObject *ret      = NULL;
    ObjectEvent *objectEvent = ObjectEvent_GetByID(id, objectEventCount, (ObjectEvent *)events);
    if (objectEvent != NULL) {
        // casts and typing required to match
        u32 eventFlag            = ObjectEvent_GetEventFlag(objectEvent);
        FieldSystem *fieldSystem = MapObjectManager_GetFieldSystem(manager);
        if (FieldSystem_FlagCheck(fieldSystem, (u16)eventFlag) == FALSE) {
            ret = MapObject_CreateFromObjectEvent(manager, objectEvent, mapNo);
        }
    }

    return ret;
}

void sub_02057614(LocalMapObject *object, u32 sprite) {
    MapObject_SetSpriteID(object, sprite);
    sub_02058148(object);
    MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK14);
    sub_020581B4(object);
}

void sub_02057634(LocalMapObject *object, u32 sprite) {
    if (sub_02058934(object) == TRUE) {
        sub_020576A8(object);
    }
    sub_02057614(object, sprite);
}

void MapObject_Remove(LocalMapObject *object) {
    if (sub_020587E0(MapObject_GetManager(object)) == TRUE) {
        sub_020586B4(object);
    }
    sub_02058660(object);
    sub_02058564(object);
    sub_02058374(MapObject_GetManagerFromManager(object));
    MapObject_Clear(object);
}

void MapObject_Delete(LocalMapObject *object) {
    u32 eventFlag            = MapObject_GetEventFlag(object);
    FieldSystem *fieldSystem = MapObject_GetFieldSystem(object);
    FieldSystem_FlagSet(fieldSystem, eventFlag);
    MapObject_Remove(object);
}

void sub_020576A8(LocalMapObject *object) {
    if (sub_020587E0(MapObject_GetManager(object)) == TRUE) {
        if (MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_UNK14) != 0) {
            sub_020586B4(object);
        }
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK14);
    }
    MapObject_SetSpriteID(object, MAP_OBJECT_GFX_ID_INVALID);
    sub_02058684(object, sub_02058ED8);
    sub_02058698(object, sub_02058EDC);
    sub_020586AC(object, sub_02058EDC);
    sub_020586C0(object, sub_02058EE0);
    sub_020586D4(object, sub_02058EE4);
}

void MapObjectManager_RemoveAllActiveObjects(MapObjectManager *manager) {
    s32 i                   = 0;
    s32 count               = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);

    do { // BUG: does not check for if count is zero, and will always execute at least once
        if (MapObject_GetFlagsBitsMask(objects, MAPOBJECTFLAG_ACTIVE) != 0) {
            MapObject_Remove(objects);
        }

        i++;
        objects++;
    } while (i < count);
}

void sub_02057750(MapObjectManager *manager) {
    GF_ASSERT(sub_020587E0(manager) == TRUE);

    s32 i                   = 0;
    s32 count               = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);

    do {
        if (MapObject_GetFlagsBitsMask(objects, MAPOBJECTFLAG_ACTIVE) != 0 && MapObject_GetFlagsBitsMask(objects, MAPOBJECTFLAG_UNK14) != 0) {
            sub_020586C8(objects);
            MapObject_NoOp(objects);
        }

        i++;
        objects++;
    } while (i < count);
}

void sub_020577A8(MapObjectManager *manager) {
    GF_ASSERT(sub_020587E0(manager) == TRUE);

    s32 i                   = 0;
    s32 count               = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);

    do {
        if (MapObject_CheckActive(objects) == TRUE) {
            if (MapObject_CheckFlag14(objects) == TRUE) {
                sub_020586DC(objects);
            } else {
                sub_020581B4(objects);
            }

            sub_02058148(objects);
        }

        i++;
        objects++;
    } while (i < count);
}

void FieldSystem_SyncMapObjectsToSaveEx(FieldSystem *fieldSystem, MapObjectManager *manager, SavedMapObject *savedObjects, s32 count) {
    s32 index = 0;
    LocalMapObject *object;

    while (MapObjectManager_GetNextObjectWithFlagFromIndex(manager, &object, &index, MAPOBJECTFLAG_ACTIVE)) { // MapObjectManager_GetNextActiveObject? this is an iterator however
        SavedMapObject_InitFromLocalMapObject(fieldSystem, object, savedObjects);

        count--;
        savedObjects++;

        GF_ASSERT(count > 0);
    }

    if (count != 0) {
        memset(savedObjects, 0, count * sizeof(SavedMapObject));
    }
}

void MapObjectManager_RestoreFromSave(MapObjectManager *manager, SavedMapObject *savedObjects, u32 objectCount) {
    while (objectCount > 0) {
        if (savedObjects->flags & MAPOBJECTFLAG_ACTIVE) {
            LocalMapObject *localObject = MapObjectManager_GetFirstInactiveObject(manager);
            GF_ASSERT(localObject != NULL);

            LocalMapObject_InitFromSavedMapObject(localObject, savedObjects);
            sub_02057AEC(manager, localObject);
        }
        savedObjects++;
        objectCount--;
    }
}

static void SavedMapObject_InitFromLocalMapObject(FieldSystem *fieldSystem, LocalMapObject *localObject, SavedMapObject *savedObject) {
    savedObject->flags         = MapObject_GetFlags(localObject);
    savedObject->flags2        = MapObject_GetFlags2(localObject);
    savedObject->objId         = MapObject_GetID(localObject);
    savedObject->mapId         = MapObject_GetMapID(localObject);
    savedObject->spriteId      = MapObject_GetSpriteID(localObject);
    savedObject->movement      = MapObject_GetMovement(localObject);
    savedObject->type          = MapObject_GetType(localObject);
    savedObject->eventFlag     = MapObject_GetEventFlag(localObject);
    savedObject->script        = MapObject_GetScriptID(localObject);
    savedObject->initialFacing = MapObject_GetInitialFacingDirection(localObject);
    savedObject->currentFacing = MapObject_GetFacingDirection(localObject);
    savedObject->nextFacing    = MapObject_GetNextFacingDirection(localObject);
    savedObject->param[0]      = MapObject_GetParam(localObject, 0);
    savedObject->param[1]      = MapObject_GetParam(localObject, 1);
    savedObject->param[2]      = MapObject_GetParam(localObject, 2);
    savedObject->xRange        = MapObject_GetXRange(localObject);
    savedObject->yRange        = MapObject_GetYRange(localObject);
    savedObject->initialX      = MapObject_GetInitialX(localObject);
    savedObject->initialY      = MapObject_GetInitialY(localObject);
    savedObject->initialZ      = MapObject_GetInitialZ(localObject);
    savedObject->currentX      = MapObject_GetCurrentX(localObject);
    savedObject->currentY      = MapObject_GetCurrentY(localObject);
    savedObject->currentZ      = MapObject_GetCurrentZ(localObject);

    VecFx32 coords;
    sub_02059E60(savedObject->currentX, savedObject->currentZ, &coords); // some kind of x y vec copy with convertion between int and fx32
    coords.y = MapObject_GetPositionVectorYCoord(localObject);

    if (!sub_02059EC8(fieldSystem, &coords, MapObject_CheckFlag29(localObject))) {
        savedObject->vecY = MapObject_GetPositionVectorYCoord(localObject);
    } else {
        savedObject->vecY = coords.y;
    }

    memcpy(savedObject->unk30, sub_020585B0(localObject), 16);
    memcpy(savedObject->unk40, sub_020585D8(localObject), 16);
}

static void LocalMapObject_InitFromSavedMapObject(LocalMapObject *localObject, SavedMapObject *savedObject) {
    MapObject_SetFlags(localObject, savedObject->flags);
    MapObject_SetFlags2(localObject, savedObject->flags2);
    MapObject_SetID(localObject, savedObject->objId);
    MapObject_SetMapID(localObject, savedObject->mapId);
    MapObject_SetSpriteID(localObject, savedObject->spriteId);
    MapObject_SetMovement(localObject, savedObject->movement);
    MapObject_SetType(localObject, savedObject->type);
    MapObject_SetEventFlag(localObject, savedObject->eventFlag);
    MapObject_SetScriptID(localObject, savedObject->script);
    MapObject_SetInitialFacingDirection(localObject, savedObject->initialFacing);
    MapObject_SetFacingDirectionDirect(localObject, savedObject->currentFacing);
    MapObject_SetNextFacingDirection(localObject, savedObject->nextFacing);
    MapObject_SetParam(localObject, savedObject->param[0], 0);
    MapObject_SetParam(localObject, savedObject->param[1], 1);
    MapObject_SetParam(localObject, savedObject->param[2], 2);
    MapObject_SetXRange(localObject, savedObject->xRange);
    MapObject_SetYRange(localObject, savedObject->yRange);
    MapObject_SetInitialX(localObject, savedObject->initialX);
    MapObject_SetInitialY(localObject, savedObject->initialY);
    MapObject_SetInitialZ(localObject, savedObject->initialZ);
    MapObject_SetCurrentX(localObject, savedObject->currentX);
    MapObject_SetCurrentY(localObject, savedObject->currentY);
    MapObject_SetCurrentZ(localObject, savedObject->currentZ);

    VecFx32 coords = {};
    coords.y       = savedObject->vecY;
    MapObject_SetPositionVector(localObject, &coords);

    memcpy(sub_020585B0(localObject), savedObject->unk30, 16);
    memcpy(sub_020585D8(localObject), savedObject->unk40, 16);
}

static void sub_02057AEC(MapObjectManager *manager, LocalMapObject *object) {
    sub_02057B34(object);
    MapObject_ConvertXZToPositionVec(object);
    MapObject_SetManager(object, manager);
    sub_02057EE0(object);
    MapObject_ClearHeldMovement(object);
    sub_020581B4(object);
    sub_02057CF0(manager, object);
    sub_0205866C(object);
    sub_0205836C(MapObjectManager_Get(manager));
}

static void sub_02057B34(LocalMapObject *object) {
    MapObject_SetFlagsBits(object, (MapObjectFlagBits)(MAPOBJECTFLAG_UNK2 | MAPOBJECTFLAG_ACTIVE));
    MapObject_ClearFlagsBits(object, (MapObjectFlagBits)(MAPOBJECTFLAG_IGNORE_HEIGHTS | MAPOBJECTFLAG_UNK22 | MAPOBJECTFLAG_UNK21 | MAPOBJECTFLAG_UNK19 | MAPOBJECTFLAG_UNK18 | MAPOBJECTFLAG_UNK17 | MAPOBJECTFLAG_UNK16 | MAPOBJECTFLAG_UNK14 | MAPOBJECTFLAG_VISIBLE | MAPOBJECTFLAG_MOVEMENT_PAUSED | MAPOBJECTFLAG_UNK3));
    sub_0205815C(object);
}

static void MapObject_ConvertXZToPositionVec(LocalMapObject *object) {
    VecFx32 position;
    MapObject_CopyPositionVector(object, &position);

    u32 x      = MapObject_GetCurrentX(object);
    position.x = x * FX32_CONST(16) + FX32_CONST(8);
    MapObject_SetPreviousX(object, x);

    MapObject_SetPreviousY(object, MapObject_GetCurrentY(object));

    u32 z      = MapObject_GetCurrentZ(object);
    position.z = z * FX32_CONST(16) + FX32_CONST(8);
    MapObject_SetPreviousZ(object, z);

    MapObject_SetPositionVector(object, &position);
}

void MapObject_CreateFromMultipleObjectEvents(MapObjectManager *manager, u32 mapNo, u32 objectEventCount, ObjectEvent *objectEvents) {
    GF_ASSERT(objectEventCount != 0);

    ObjectEvent *objectEventsCopy = AllocFromHeapAtEnd(HEAP_ID_FIELD, objectEventCount * sizeof(ObjectEvent));
    GF_ASSERT(objectEventsCopy != NULL);
    memcpy(objectEventsCopy, objectEvents, objectEventCount * sizeof(ObjectEvent));

    MapObjectInitArgs *args = AllocFromHeapAtEnd(HEAP_ID_FIELD, sizeof(MapObjectInitArgs));
    GF_ASSERT(args != NULL);
    args->mapNo            = mapNo;
    args->objectEventCount = objectEventCount;
    args->index            = 0;
    args->manager          = manager;
    args->objectEvents     = objectEventsCopy;

    MapObject_CreateFromInitArgs(args);
}

static void MapObject_CreateFromInitArgs(MapObjectInitArgs *args) {
    FieldSystem *fieldSystem  = MapObjectManager_GetFieldSystem(args->manager);
    ObjectEvent *objectEvents = args->objectEvents;

    do {                                                                                                                                                                                                                             // must be do while due to initial check
        GF_ASSERT((ObjectEvent_ScriptIDIsUnset(objectEvents) != TRUE && FieldSystem_FlagCheck(fieldSystem, objectEvents->eventFlag) != FALSE) || MapObject_CreateFromObjectEvent(args->manager, objectEvents, args->mapNo) != NULL); // this is dumb, but is required to match

        objectEvents++;
        args->index++;
    } while (args->index < args->objectEventCount);

    FreeToHeapExplicit(HEAP_ID_FIELD, args->objectEvents);
    FreeToHeapExplicit(HEAP_ID_FIELD, args);
}

static LocalMapObject *MapObjectManager_GetFirstInactiveObject(MapObjectManager *manager) {
    s32 i                   = 0;
    s32 count               = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);

    do {
        if (MapObject_GetFlagsBitsMask(objects, MAPOBJECTFLAG_ACTIVE) == 0) {
            return objects;
        }

        i++;
        objects++;
    } while (i < count);

    return NULL;
}

static LocalMapObject *sub_02057C98(MapObjectManager *manager, u32 id, u32 mapNo) { // find corresponding LMO with ID and mapNo?
    s32 index = 0;
    LocalMapObject *object;

    while (MapObjectManager_GetNextObjectWithFlagFromIndex(manager, &object, &index, MAPOBJECTFLAG_ACTIVE) == TRUE) {
        if (MapObject_CheckFlag25(object) == TRUE && MapObject_GetID(object) == id && sub_02058750(object) == mapNo) {
            return object;
        }
    }

    return NULL;
}

static void sub_02057CF0(MapObjectManager *manager, LocalMapObject *object) {
    u32 priority = MapObjectManager_GetPriority(manager);
    u32 movement = MapObject_GetMovement(object);
    if (movement == 48 || movement == 50) {
        priority += 2;
    }

    SysTask *task = SysTask_CreateOnMainQueue((SysTaskFunc)sub_0205832C, object, priority);
    GF_ASSERT(task != NULL);

    sub_02058554(object, task);
}

static void MapObject_InitFromObjectEvent(LocalMapObject *object, ObjectEvent *objectEvent, FieldSystem *fieldSystem) {
    MapObject_SetID(object, ObjectEvent_GetID(objectEvent));
    MapObject_SetSpriteID(object, FieldSystem_ResolveObjectSpriteID(fieldSystem, ObjectEvent_GetSpriteID(objectEvent)));
    MapObject_SetMovement(object, ObjectEvent_GetMovement(objectEvent));
    MapObject_SetType(object, ObjectEvent_GetType(objectEvent));
    MapObject_SetEventFlag(object, ObjectEvent_GetEventFlag(objectEvent));
    MapObject_SetScriptID(object, ObjectEvent_GetScriptID(objectEvent));
    MapObject_SetInitialFacingDirection(object, ObjectEvent_GetFacingDirection(objectEvent));
    MapObject_SetParam(object, ObjectEvent_GetParam(objectEvent, 0), 0);
    MapObject_SetParam(object, ObjectEvent_GetParam(objectEvent, 1), 1);
    MapObject_SetParam(object, ObjectEvent_GetParam(objectEvent, 2), 2);
    MapObject_SetXRange(object, ObjectEvent_GetXRange(objectEvent));
    MapObject_SetYRange(object, ObjectEvent_GetYRange(objectEvent));

    MapObject_SetPositionVectorFromObjectEvent(object, objectEvent);
}

static void MapObject_SetPositionVectorFromObjectEvent(LocalMapObject *object, ObjectEvent *objectEvent) {
    VecFx32 coords;

    u16 x    = ObjectEvent_GetXCoord(objectEvent);
    coords.x = x * FX32_CONST(16) + FX32_CONST(8);
    MapObject_SetInitialX(object, x);
    MapObject_SetPreviousX(object, x);
    MapObject_SetCurrentX(object, x);

    coords.y = ObjectEvent_GetYCoord(objectEvent);
    u32 y    = (coords.y >> 3) / FX32_ONE;
    MapObject_SetInitialY(object, y);
    MapObject_SetPreviousY(object, y);
    MapObject_SetCurrentY(object, y);

    u16 z    = ObjectEvent_GetZCoord(objectEvent);
    coords.z = z * FX32_CONST(16) + FX32_CONST(8);
    MapObject_SetInitialZ(object, z);
    MapObject_SetPreviousZ(object, z);
    MapObject_SetCurrentZ(object, z);

    MapObject_SetPositionVector(object, &coords);
}

static void sub_02057E90(LocalMapObject *object, MapObjectManager *manager) { // setup facing and flags? also sets manager?
    MapObject_SetFlagsBits(object, (MapObjectFlagBits)(MAPOBJECTFLAG_UNK12 | MAPOBJECTFLAG_UNK11 | MAPOBJECTFLAG_ACTIVE));
    if (MapObject_ScriptIDIsFFFF(object) == TRUE) {
        MapObject_SetFlag25(object, TRUE);
    }
    MapObject_SetManager(object, manager);
    MapObject_SetFacingDirectionDirect(object, MapObject_GetInitialFacingDirection(object));
    MapObject_SetNextFacingDirection(object, MapObject_GetInitialFacingDirection(object));
    MapObject_ClearHeldMovement(object);
}

/*static*/ void sub_02057EE0(LocalMapObject *object) {
    UnkLMOCallbackStruct *unk = sub_02058D14(MapObject_GetMovement(object));
    sub_02058630(object, sub_02058D2C(unk));
    sub_02058644(object, sub_02058D30(unk));
    sub_02058658(object, sub_02058D34(unk));
}

extern const UnkLMOCallbackStruct2 ov05_021F9080;

static void sub_02057F18(LocalMapObject *object) {
    u32 spriteId               = MapObject_GetSpriteID(object);
    UnkLMOCallbackStruct2 *unk = (spriteId == SPRITE_CAMERA_FOCUS) ? (UnkLMOCallbackStruct2 *)&ov05_021F9080 : sub_02058D4C(spriteId);

    sub_02058684(object, sub_02058D38(unk));
    sub_02058698(object, sub_02058D3C(unk));
    sub_020586AC(object, sub_02058D40(unk));
    sub_020586C0(object, sub_02058D44(unk));
    sub_020586D4(object, sub_02058D48(unk));
}

static void MapObject_Clear(LocalMapObject *object) {
    memset(object, 0, sizeof(LocalMapObject));
}

static u32 sub_02057F90(LocalMapObject *object, u32 mapId, u32 objectEventCount, ObjectEvent *objectEvents) {
    for (; objectEventCount != 0; objectEventCount--, objectEvents++) {
        if (ObjectEvent_GetID(objectEvents) != MapObject_GetID(object)) {
            continue;
        }

        if (ObjectEvent_ScriptIDIsUnset(objectEvents) == TRUE) {
            u16 eventFlag = ObjectEvent_GetEventFlag_AssertScriptIDIsUnset(objectEvents);
            if (MapObject_CheckFlag25(object) == TRUE) { // this and the one below cannot be combined as it doesn't match
                if (sub_02058750(object) == eventFlag) {
                    return 1;
                }
                // I'm assume that sometimes the ObjectEvent flags equals the mapId to signify that
                // this is a map-wide event etc.
            } else if (MapObject_GetMapID(object) == eventFlag) {
                return 2;
            }
            // this is indeed a weird comparsion, but I checked, it's correct
        } else if (MapObject_CheckFlag25(object) == TRUE && sub_02058750(object) == mapId) {
            return 2;
        }
    }

    return 0;
}

static LocalMapObject *MapObjectManager_GetFirstObjectWithIDAndMap(MapObjectManager *manager, u32 objectId, u32 mapId) {
    s32 index = 0;
    LocalMapObject *object;

    while (MapObjectManager_GetNextObjectWithFlagFromIndex(manager, &object, &index, MAPOBJECTFLAG_ACTIVE) == TRUE) {
        if (MapObject_GetID(object) == objectId && MapObject_GetMapID(object) == mapId) {
            return object;
        }
    }

    return NULL;
}

LocalMapObject *MapObjectManager_GetFirstActiveObjectByID(MapObjectManager *manager, u32 id) {
    GF_ASSERT(manager != NULL);

    s32 count               = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects3(manager);
    do {
        if (MapObject_TestFlagsBits(objects, MAPOBJECTFLAG_ACTIVE) == TRUE && MapObject_CheckFlag25(objects) == FALSE && MapObject_GetID(objects) == id) {
            return objects;
        }

        count--;
        objects++;
    } while (count > 0);

    return NULL;
}

LocalMapObject *MapObjectManager_GetFirstActiveObjectWithMovement(MapObjectManager *manager, u32 movement) {
    s32 count               = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects3(manager);

    do {
        if (MapObject_TestFlagsBits(objects, MAPOBJECTFLAG_ACTIVE) == TRUE && MapObject_GetMovement(objects) == movement) {
            return objects;
        }

        count--;
        objects++;
    } while (count > 0);

    return NULL;
}

BOOL MapObjectManager_GetNextObjectWithFlagFromIndex(MapObjectManager *manager, LocalMapObject **objectDest, s32 *index, MapObjectFlagBits flag) {
    s32 count = MapObjectManager_GetObjectCount(manager);
    if (*index >= count) {
        return FALSE;
    }

    LocalMapObject *objects = MapObjectManager_GetObjects3(manager);
    LocalMapObject *object  = objects + *index;
    do {
        (*index)++;

        if (flag == (MapObjectFlagBits)MapObject_GetFlagsBitsMask(object, flag)) {
            *objectDest = object;
            return TRUE;
        }

        object++;
    } while (*index < count);

    return FALSE;
}

static void sub_02058148(LocalMapObject *object) {
    MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK2);
    sub_0205815C(object);
}

/*static*/ void sub_0205815C(LocalMapObject *object) {
    MapObject_ClearFlagsBits(object, (MapObjectFlagBits)(MAPOBJECTFLAG_UNK26 | MAPOBJECTFLAG_UNK24 | MAPOBJECTFLAG_UNK20 | MAPOBJECTFLAG_UNK15));
}

static void MapObject_NoOp(LocalMapObject *object) {
    // NoOp
}

static u32 FieldSystem_ResolveObjectSpriteID(FieldSystem *fieldSystem, s32 spriteId) {
    // BUG: index out of range, should be < not <=
    // TODO: check these with sprite constants, these should be variable sprites but this starts at 101 not 100
    if (spriteId >= 101 && spriteId <= 117) {
        spriteId = FieldSystem_VarGetObjectEventGraphicsId(fieldSystem, (u16)(spriteId - 101));
    }
    return spriteId;
}

static void sub_0205818C(LocalMapObject *object) {
    if (MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_UNK12) != 0) {
        sub_02059D1C(object);
    }
}

static void sub_020581A4(LocalMapObject *object) {
    sub_02057EE0(object);
    sub_02058EE8(object);
}

static void sub_020581B4(LocalMapObject *object) {
    if (!sub_020587E0(MapObject_GetManager(object))) {
        return;
    }

    sub_0205818C(object);
    sub_02058544(object, 0);
    ov05_021F2E0C(object, FALSE);
    if (!MapObject_CheckFlag14(object)) {
        sub_02057F18(object);
        sub_0205868C(object);
        MapObject_SetFlag14(object);
    }
}

static BOOL MapObject_ScriptIDIsFFFF(LocalMapObject *object) {
    u16 script = MapObject_GetScriptID(object);
    return script == 0xFFFF;
}

static void sub_02058214(LocalMapObject *object, ObjectEvent *objectEvent, u32 mapNo) {
    GF_ASSERT(MapObject_CheckFlag25(object) == TRUE);

    MapObject_SetFlag25(object, FALSE);
    MapObject_SetMapID(object, mapNo);
    MapObject_SetScriptID(object, ObjectEvent_GetScriptID(objectEvent));
    MapObject_SetEventFlag(object, ObjectEvent_GetEventFlag(objectEvent));
}

static void sub_02058258(LocalMapObject *object, u32 mapNo, ObjectEvent *objectEvent) {
    GF_ASSERT(ObjectEvent_ScriptIDIsUnset(objectEvent) == TRUE);

    MapObject_SetFlag25(object, TRUE);
    MapObject_SetScriptID(object, ObjectEvent_GetScriptID(objectEvent));
    MapObject_SetEventFlag(object, ObjectEvent_GetEventFlag_AssertScriptIDIsUnset(objectEvent));
    MapObject_SetMapID(object, mapNo);
}

u32 MapObject_GetPriorityPlusValue(LocalMapObject *object, u32 value) {
    return (u32)((void *)MapObject_GetPriority(object) + value); // MUST be cast to void * to match
}

BOOL sub_020582A8(LocalMapObject *object, u32 objectId, u32 mapId) {
    if (!MapObject_TestFlagsBits(object, MAPOBJECTFLAG_ACTIVE)) {
        return FALSE;
    }

    if (MapObject_GetID(object) != objectId) {
        return FALSE;
    }

    if (MapObject_GetMapID(object) != mapId) {
        if (!MapObject_CheckFlag25(object)) {
            return FALSE;
        }

        if (sub_02058750(object) != mapId) {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL sub_020582F8(LocalMapObject *object, u32 spriteId, u32 objectId, u32 mapId) {
    if (!MapObject_TestFlagsBits(object, MAPOBJECTFLAG_ACTIVE)) {
        return FALSE;
    }

    u32 objectSpriteId = sub_0205845C(object);
    if (objectSpriteId != spriteId) {
        return FALSE;
    }

    return sub_020582A8(object, objectId, mapId);
}

static void sub_0205832C(SysTask *task, LocalMapObject *object) {
    sub_02058EF8(object);
    if (MapObject_CheckActive(object)) {
        sub_02058348(object);
    }
}

static void sub_02058348(LocalMapObject *object) {
    if (sub_020587E0(MapObject_GetManager(object)) == TRUE) {
        ov05_021F1D8C(object);
    }
}

// Likely a scrubbed debug func, but WTF is GF smoking?
static MapObjectManager *MapObjectManager_Get(MapObjectManager *manager) {
    return manager;
}

static void MapObjectManager_SetObjectCount(MapObjectManager *manager, u32 count) {
    manager->objectCount = count;
}

u32 MapObjectManager_GetObjectCount(MapObjectManager *manager) {
    return manager->objectCount;
}

static void sub_0205836C(MapObjectManager *manager) {
    manager->unk8++;
}

static void sub_02058374(MapObjectManager *manager) {
    manager->unk8--;
}

void MapObjectManager_SetFlagsBits(MapObjectManager *manager, MapObjectManagerFlagBits bits) {
    manager->flags |= bits;
}

void MapObjectManager_ClearFlagsBits(MapObjectManager *manager, MapObjectManagerFlagBits bits) {
    manager->flags &= ~bits;
}

u32 MapObjectManager_GetFlagsBitsMask(MapObjectManager *manager, MapObjectManagerFlagBits bits) {
    return manager->flags & bits;
}

static void MapObjectManager_SetPriority(MapObjectManager *manager, u32 priority) {
    manager->priority = priority;
}

u32 MapObjectManager_GetPriority(MapObjectManager *manager) {
    return manager->priority;
}

// type of unk18 is unknown, it's a u32 in MapObjectManager, but unsure what it's supposed to be
// leaving return as a void * to reflect this
void *sub_020583A0(MapObjectManager *manager) {
    return &manager->unk18;
}

void sub_020583A4(MapObjectManager *manager, u32 param1) {
    manager->unk120 = param1;
}

u32 sub_020583AC(MapObjectManager *manager) {
    return manager->unk120;
}

static void MapObjectManager_SetObjects(MapObjectManager *manager, LocalMapObject *objects) {
    manager->objects = objects;
}

// the 2 here is bad, however this is *exactly* the same as the lower GetObjects
LocalMapObject *MapObjectManager_GetObjects2(MapObjectManager *manager) {
    return manager->objects;
}

// same as above
static LocalMapObject *MapObjectManager_GetObjects3(MapObjectManager *manager) {
    return manager->objects;
}

// this one is the original because it's used the most
LocalMapObject *MapObjectManager_GetObjects(MapObjectManager *manager) {
    return manager->objects;
}

void MapObjectArray_NextObject(LocalMapObject **objects) {
    (*objects)++;
}

static void MapObjectManager_SetFieldSystem(MapObjectManager *manager, FieldSystem *fieldSystem) {
    manager->fieldSystem = fieldSystem;
}

static FieldSystem *MapObjectManager_GetFieldSystem(MapObjectManager *manager) {
    return manager->fieldSystem;
}

void MapObjectManager_SetMapModelNarc(MapObjectManager *manager, NARC *mapModelNarc) {
    manager->mapModelNarc = mapModelNarc;
}

NARC *MapObjectManager_GetMapModelNarc(MapObjectManager *manager) {
    GF_ASSERT(manager->mapModelNarc != NULL);
    return manager->mapModelNarc;
}

static void MapObject_SetFlags(LocalMapObject *object, u32 flags) {
    object->flags = flags;
}

static u32 MapObject_GetFlags(LocalMapObject *object) {
    return object->flags;
}

void MapObject_SetFlagsBits(LocalMapObject *object, MapObjectFlagBits bits) {
    object->flags |= bits;
}

void MapObject_ClearFlagsBits(LocalMapObject *object, MapObjectFlagBits bits) {
    object->flags &= ~bits;
}

u32 MapObject_GetFlagsBitsMask(LocalMapObject *object, MapObjectFlagBits bits) {
    return object->flags & bits;
}

BOOL MapObject_TestFlagsBits(LocalMapObject *object, MapObjectFlagBits bits) {
    return (object->flags & bits) != 0;
}

static void MapObject_SetFlags2(LocalMapObject *object, u32 flags) {
    object->flags2 = flags;
}

static u32 MapObject_GetFlags2(LocalMapObject *object) {
    return object->flags2;
}

void MapObject_SetID(LocalMapObject *object, u32 id) {
    object->id = id;
}

u32 MapObject_GetID(LocalMapObject *object) {
    return object->id;
}

static void MapObject_SetMapID(LocalMapObject *object, u32 mapId) {
    object->mapId = mapId;
}

u32 MapObject_GetMapID(LocalMapObject *object) {
    return object->mapId;
}

void MapObject_SetSpriteID(LocalMapObject *object, u32 spriteId) {
    object->spriteId = spriteId;
}

u32 MapObject_GetSpriteID(LocalMapObject *object) {
    return object->spriteId;
}

u32 sub_0205845C(LocalMapObject *object) {
    u32 spriteId = MapObject_GetSpriteID(object);
    if (sub_0205C334() == TRUE) {
        return sub_0205C340(object);
    }
    return spriteId;
}

/*static*/ void MapObject_SetMovement(LocalMapObject *object, u32 movement) {
    object->movement = movement;
}

u32 MapObject_GetMovement(LocalMapObject *object) {
    return object->movement;
}

void MapObject_SetType(LocalMapObject *object, u32 type) {
    object->type = type;
}

u32 MapObject_GetType(LocalMapObject *object) {
    return object->type;
}

void MapObject_SetEventFlag(LocalMapObject *object, u32 eventFlag) {
    object->eventFlag = eventFlag;
}

static u32 MapObject_GetEventFlag(LocalMapObject *object) {
    return object->eventFlag;
}

void MapObject_SetScriptID(LocalMapObject *object, u32 scriptId) {
    object->scriptId = scriptId;
}

u32 MapObject_GetScriptID(LocalMapObject *object) {
    return object->scriptId;
}

static void MapObject_SetInitialFacingDirection(LocalMapObject *object, u32 initialFacing) {
    object->initialFacing = initialFacing;
}

u32 MapObject_GetInitialFacingDirection(LocalMapObject *object) {
    return object->initialFacing;
}

void MapObject_SetFacingDirectionDirect(LocalMapObject *object, u32 direction) {
    object->previousFacing = object->currentFacing;
    object->currentFacing  = direction;
}

void MapObject_SetFacingDirection(LocalMapObject *object, u32 direction) {
    if (MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_UNK7) == 0) {
        object->previousFacing = object->currentFacing;
        object->currentFacing  = direction;
    }
}

u32 MapObject_GetFacingDirection(LocalMapObject *object) {
    return object->currentFacing;
}

u32 MapObject_GetPreviousFacingDirection(LocalMapObject *object) {
    return object->previousFacing;
}

void MapObject_SetNextFacingDirection(LocalMapObject *object, u32 direction) {
    object->nextFacingBackup = object->nextFacing;
    object->nextFacing       = direction;
}

u32 MapObject_GetNextFacingDirection(LocalMapObject *object) {
    return object->nextFacing;
}

void MapObject_SetOrQueueFacing(LocalMapObject *object, u32 direction) {
    MapObject_SetFacingDirection(object, direction);
    MapObject_SetNextFacingDirection(object, direction);
}

void MapObject_SetParam(LocalMapObject *object, s32 value, u32 param) {
    switch (param) {
    case 0:
        object->param[0] = value;
        return;
    case 1:
        object->param[1] = value;
        return;
    case 2:
        object->param[2] = value;
        return;
    default:
        GF_ASSERT(FALSE);
        return;
    }
}

s32 MapObject_GetParam(LocalMapObject *object, u32 param) {
    switch (param) {
    case 0:
        return object->param[0];
    case 1:
        return object->param[1];
    case 2:
        return object->param[2];
    default:
        GF_ASSERT(FALSE);
        return 0;
    }
}

void MapObject_SetXRange(LocalMapObject *object, s32 xRange) {
    object->xRange = xRange;
}

s32 MapObject_GetXRange(LocalMapObject *object) {
    return object->xRange;
}

void MapObject_SetYRange(LocalMapObject *object, s32 yRange) {
    object->yRange = yRange;
}

s32 MapObject_GetYRange(LocalMapObject *object) {
    return object->yRange;
}

void sub_02058544(LocalMapObject *object, u32 param1) {
    object->unkA0 = param1;
}

u32 sub_0205854C(LocalMapObject *object) {
    return object->unkA0;
}

static void sub_02058554(LocalMapObject *object, SysTask *sysTask) {
    object->unkB0 = sysTask;
}

static SysTask *sub_0205855C(LocalMapObject *object) {
    return object->unkB0;
}

static void sub_02058564(LocalMapObject *object) {
    SysTask_Destroy(sub_0205855C(object));
}

static void MapObject_SetManager(LocalMapObject *object, MapObjectManager *manager) {
    object->manager = manager;
}

MapObjectManager *MapObject_GetManager(LocalMapObject *object) {
    return object->manager;
}

static MapObjectManager *MapObject_GetManagerFromManager(LocalMapObject *object) {
    return MapObjectManager_Get(object->manager);
}

u8 *sub_0205858C(LocalMapObject *object, s32 size) {
    GF_ASSERT(size <= 16);

    u8 *ret = sub_020585B0(object);
    memset(ret, 0, size);
    return ret;
}

u8 *sub_020585B0(LocalMapObject *object) {
    return object->unkD8;
}

u8 *sub_020585B4(LocalMapObject *object, s32 size) {
    GF_ASSERT(size <= 16);

    u8 *ret = sub_020585D8(object);
    memset(ret, 0, size);
    return ret;
}

u8 *sub_020585D8(LocalMapObject *object) {
    return object->unkE8;
}

u8 *sub_020585DC(LocalMapObject *object, s32 size) {
    GF_ASSERT(size <= 16);

    u8 *ret = sub_02058600(object);
    memset(ret, 0, size);
    return ret;
}

u8 *sub_02058600(LocalMapObject *object) {
    return object->unkF8;
}

u8 *sub_02058604(LocalMapObject *object, s32 size) {
    GF_ASSERT(size <= 32);

    u8 *ret = sub_02058628(object);
    memset(ret, 0, size);
    return ret;
}

u8 *sub_02058628(LocalMapObject *object) {
    return object->unk108;
}

static void sub_02058630(LocalMapObject *object, LocalMapObject_UnkCallback callback) {
    object->unkB8 = callback;
}

void sub_02058638(LocalMapObject *object) {
    object->unkB8(object);
}

static void sub_02058644(LocalMapObject *object, LocalMapObject_UnkCallback callback) {
    object->unkBC = callback;
}

void sub_0205864C(LocalMapObject *object) {
    object->unkBC(object);
}

static void sub_02058658(LocalMapObject *object, LocalMapObject_UnkCallback callback) {
    object->unkC0 = callback;
}

/*static*/ void sub_02058660(LocalMapObject *object) {
    object->unkC0(object);
}

static void sub_0205866C(LocalMapObject *object) {
    UnkLMOCallbackStruct *unk = sub_02058D14(MapObject_GetMovement(object));
    unk->unk10(object);
}

static void sub_02058684(LocalMapObject *object, LocalMapObject_UnkCallback callback) {
    object->unkC4 = callback;
}

static void sub_0205868C(LocalMapObject *object) {
    object->unkC4(object);
}

static void sub_02058698(LocalMapObject *object, LocalMapObject_UnkCallback callback) {
    object->unkC8 = callback;
}

void sub_020586A0(LocalMapObject *object) {
    object->unkC8(object);
}

static void sub_020586AC(LocalMapObject *object, LocalMapObject_UnkCallback callback) {
    object->unkCC = callback;
}

static void sub_020586B4(LocalMapObject *object) {
    object->unkCC(object);
}

static void sub_020586C0(LocalMapObject *object, LocalMapObject_UnkCallback callback) {
    object->unkD0 = callback;
}

static void sub_020586C8(LocalMapObject *object) {
    object->unkD0(object);
}

static void sub_020586D4(LocalMapObject *object, LocalMapObject_UnkCallback callback) {
    object->unkD4 = callback;
}

void sub_020586DC(LocalMapObject *object) {
    object->unkD4(object);
}

void MapObject_SetMovementCommand(LocalMapObject *object, u32 command) {
    object->movementCmd = command;
}

u32 MapObject_GetMovementCommand(LocalMapObject *object) {
    return object->movementCmd;
}

void MapObject_SetMovementStep(LocalMapObject *object, u32 step) {
    object->movementStep = step;
}

void MapObject_IncrementMovementStep(LocalMapObject *object) {
    object->movementStep++;
}

u32 MapObject_GetMovementStep(LocalMapObject *object) {
    return object->movementStep;
}

void sub_02058718(LocalMapObject *object, u16 param1) {
    object->unkAC = param1;
}

u16 sub_02058720(LocalMapObject *object) {
    return object->unkAC;
}

void sub_02058728(LocalMapObject *object, u16 param1) {
    object->unkAE = param1;
}

u16 sub_02058730(LocalMapObject *object) {
    return object->unkAE;
}

FieldSystem *MapObject_GetFieldSystem(LocalMapObject *object) {
    return MapObjectManager_GetFieldSystem(MapObject_GetManagerFromManager(object));
}

u32 MapObject_GetPriority(LocalMapObject *object) {
    return MapObjectManager_GetPriority(MapObject_GetManager(object));
}

u32 sub_02058750(LocalMapObject *object) {
    GF_ASSERT(MapObject_CheckFlag25(object) == TRUE);
    return MapObject_GetEventFlag(object);
}

void sub_02058768(MapObjectManager *manager) {
    MapObjectManager_SetFlagsBits(manager, (MapObjectManagerFlagBits)(MAPOBJECTMANAGERFLAG_UNK2 | MAPOBJECTMANAGERFLAG_UNK1));
}

void sub_02058774(MapObjectManager *manager) {
    MapObjectManager_ClearFlagsBits(manager, (MapObjectManagerFlagBits)(MAPOBJECTMANAGERFLAG_UNK2 | MAPOBJECTMANAGERFLAG_UNK1));
}

void MapObjectManager_PauseAllMovement(MapObjectManager *manager) {
    u32 count               = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);
    do {
        if (MapObject_CheckActive(objects)) {
            MapObject_PauseMovement(objects);
        }

        objects++;
        count--;
    } while (count > 0);
}

void MapObjectManager_UnpauseAllMovement(MapObjectManager *manager) {
    u32 count               = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);
    do {
        if (MapObject_CheckActive(objects)) {
            MapObject_UnpauseMovement(objects);
        }

        objects++;
        count--;
    } while (count > 0);
}

BOOL sub_020587E0(MapObjectManager *manager) {
    return MapObjectManager_GetFlagsBitsMask(manager, MAPOBJECTMANAGERFLAG_UNK0) != 0;
}

u32 sub_020587F4(LocalMapObject *object, MapObjectManagerFlagBits bits) {
    return MapObjectManager_GetFlagsBitsMask(MapObject_GetManager(object), bits);
}

void sub_02058804(MapObjectManager *manager, BOOL clear) {
    if (clear == FALSE) {
        MapObjectManager_SetFlagsBits(manager, MAPOBJECTMANAGERFLAG_UNK3);
    } else {
        MapObjectManager_ClearFlagsBits(manager, MAPOBJECTMANAGERFLAG_UNK3);
    }
}

BOOL sub_0205881C(MapObjectManager *manager) {
    return MapObjectManager_GetFlagsBitsMask(manager, MAPOBJECTMANAGERFLAG_UNK3) == 0;
}

BOOL MapObject_CheckActive(LocalMapObject *object) {
    return MapObject_TestFlagsBits(object, MAPOBJECTFLAG_ACTIVE);
}

void MapObject_SetSingleMovement(LocalMapObject *object) {
    MapObject_SetFlagsBits(object, MAPOBJECTFLAG_SINGLE_MOVEMENT);
}

void MapObject_ClearSingleMovement(LocalMapObject *object) {
    MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_SINGLE_MOVEMENT);
}

BOOL MapObject_CheckSingleMovement(LocalMapObject *object) {
    return MapObject_TestFlagsBits(object, MAPOBJECTFLAG_SINGLE_MOVEMENT);
}

void MapObject_SetFlag2(LocalMapObject *object) {
    MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK2);
}

void MapObject_ClearFlag3(LocalMapObject *object) {
    MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK3);
}

static void MapObject_SetFlag14(LocalMapObject *object) {
    MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK14);
}

BOOL MapObject_CheckFlag14(LocalMapObject *object) {
    return MapObject_TestFlagsBits(object, MAPOBJECTFLAG_UNK14);
}

BOOL MapObject_CheckVisible(LocalMapObject *object) {
    return MapObject_TestFlagsBits(object, MAPOBJECTFLAG_VISIBLE);
}

void MapObject_SetVisible(LocalMapObject *object, BOOL set) {
    if (set == TRUE) {
        MapObject_SetFlagsBits(object, MAPOBJECTFLAG_VISIBLE);
    } else {
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_VISIBLE);
    }
}

void MapObject_ClearFlag18(LocalMapObject *object, BOOL clear) {
    if (clear == TRUE) {
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK18);
    } else {
        MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK18);
    }
}

BOOL MapObject_CheckFlag19Disabled(LocalMapObject *object) {
    return MapObject_TestFlagsBits(object, MAPOBJECTFLAG_UNK19) != TRUE;
}

void MapObject_SetFlag19(LocalMapObject *object, BOOL set) {
    if (set == TRUE) {
        MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK19);
    } else {
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK19);
    }
}

void MapObject_PauseMovement(LocalMapObject *object) {
    MapObject_SetFlagsBits(object, MAPOBJECTFLAG_MOVEMENT_PAUSED);
}

void MapObject_UnpauseMovement(LocalMapObject *object) {
    MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_MOVEMENT_PAUSED);
}

BOOL MapObject_CheckMovementPaused(LocalMapObject *object) {
    return MapObject_TestFlagsBits(object, MAPOBJECTFLAG_MOVEMENT_PAUSED) == TRUE;
}

BOOL sub_02058934(LocalMapObject *object) {
    if (!sub_020587E0(MapObject_GetManager(object))) {
        return FALSE;
    }

    if (MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_UNK14) != 0) {
        return TRUE;
    }

    return FALSE;
}

void MapObject_SetIgnoreHeights(LocalMapObject *object, BOOL set) {
    if (set == TRUE) {
        MapObject_SetFlagsBits(object, MAPOBJECTFLAG_IGNORE_HEIGHTS);
    } else {
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_IGNORE_HEIGHTS);
    }
}

BOOL MapObject_CheckIgnoreHeights(LocalMapObject *object) {
    return MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_IGNORE_HEIGHTS) != 0;
}

void MapObject_SetKeep(LocalMapObject *object, BOOL set) {
    if (set == TRUE) {
        MapObject_SetFlagsBits(object, MAPOBJECTFLAG_KEEP);
    } else {
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_KEEP);
    }
}

static void MapObject_SetFlag25(LocalMapObject *object, BOOL set) {
    if (set == TRUE) {
        MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK25);
    } else {
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK25);
    }
}

BOOL MapObject_CheckFlag25(LocalMapObject *object) {
    return MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_UNK25) != 0;
}

void MapObject_SetFlag26(LocalMapObject *object, BOOL set) {
    if (set == TRUE) {
        MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK26);
    } else {
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK26);
    }
}

BOOL MapObject_CheckFlag26(LocalMapObject *object) {
    return MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_UNK26) != 0;
}

void MapObject_SetFlag27(LocalMapObject *object, BOOL set) {
    if (set == TRUE) {
        MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK27);
    } else {
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK27);
    }
}

BOOL MapObject_CheckFlag27(LocalMapObject *object) {
    return MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_UNK27) != 0;
}

void MapObject_SetFlag28(LocalMapObject *object, BOOL set) {
    if (set == TRUE) {
        MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK28);
    } else {
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK28);
    }
}

BOOL MapObject_CheckFlag28(LocalMapObject *object) {
    return MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_UNK28) != 0;
}

void MapObject_SetFlag24(LocalMapObject *object, BOOL set) {
    if (set == TRUE) {
        MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK24);
    } else {
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK24);
    }
}

BOOL MapObject_CheckFlag24(LocalMapObject *object) {
    return MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_UNK24) != 0;
}

BOOL MapObject_CheckFlag4(LocalMapObject *object) {
    return MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_UNK4) != 0;
}

void MapObject_SetFlag29(LocalMapObject *object, BOOL set) {
    if (set == TRUE) {
        MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK29);
    } else {
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK29);
    }
}

BOOL MapObject_CheckFlag29(LocalMapObject *object) {
    return MapObject_GetFlagsBitsMask(object, MAPOBJECTFLAG_UNK29) != 0;
}

u32 MapObject_GetInitialX(LocalMapObject *object) {
    return object->initialX;
}

static void MapObject_SetInitialX(LocalMapObject *object, u32 initialX) {
    object->initialX = initialX;
}

u32 MapObject_GetInitialY(LocalMapObject *object) {
    return object->initialY;
}

static void MapObject_SetInitialY(LocalMapObject *object, u32 initialY) {
    object->initialY = initialY;
}

u32 MapObject_GetInitialZ(LocalMapObject *object) {
    return object->initialZ;
}

static void MapObject_SetInitialZ(LocalMapObject *object, u32 initialY) {
    object->initialZ = initialY;
}

u32 MapObject_GetPreviousX(LocalMapObject *object) {
    return object->previousX;
}

void MapObject_SetPreviousX(LocalMapObject *object, u32 previousX) {
    object->previousX = previousX;
}

u32 MapObject_GetPreviousY(LocalMapObject *object) {
    return object->previousY;
}

void MapObject_SetPreviousY(LocalMapObject *object, u32 previousY) {
    object->previousY = previousY;
}

u32 MapObject_GetPreviousZ(LocalMapObject *object) {
    return object->previousZ;
}

void MapObject_SetPreviousZ(LocalMapObject *object, u32 previousZ) {
    object->previousZ = previousZ;
}

u32 MapObject_GetCurrentX(LocalMapObject *object) {
    return object->currentX;
}

void MapObject_SetCurrentX(LocalMapObject *object, u32 currentX) {
    object->currentX = currentX;
}

void MapObject_AddCurrentX(LocalMapObject *object, u32 currentX) {
    object->currentX += currentX;
}

s32 MapObject_GetCurrentY(LocalMapObject *object) {
    return object->currentY;
}

void MapObject_SetCurrentY(LocalMapObject *object, s32 currentY) {
    object->currentY = currentY;
}

void MapObject_AddCurrentY(LocalMapObject *object, s32 currentY) {
    object->currentY += currentY;
}

u32 MapObject_GetCurrentZ(LocalMapObject *object) {
    return object->currentZ;
}

void MapObject_SetCurrentZ(LocalMapObject *object, u32 currentZ) {
    object->currentZ = currentZ;
}

void MapObject_AddCurrentZ(LocalMapObject *object, u32 currentZ) {
    object->currentZ += currentZ;
}

void MapObject_CopyPositionVector(LocalMapObject *object, VecFx32 *positionVector) {
    *positionVector = object->positionVector;
}

void MapObject_SetPositionVector(LocalMapObject *object, VecFx32 *positionVector) {
    object->positionVector = *positionVector;
}

VecFx32 *MapObject_GetPositionVector(LocalMapObject *object) {
    return &object->positionVector;
}

fx32 MapObject_GetPositionVectorYCoord(LocalMapObject *object) {
    return object->positionVector.y;
}

void MapObject_CopyFacingVector(LocalMapObject *object, VecFx32 *facingVector) {
    *facingVector = object->facingVector;
}

void MapObject_SetFacingVector(LocalMapObject *object, VecFx32 *facingVector) {
    object->facingVector = *facingVector;
}

void sub_02058BA4(LocalMapObject *object, VecFx32 *vector) {
    *vector = object->unk88;
}

void sub_02058BB4(LocalMapObject *object, VecFx32 *vector) {
    object->unk88 = *vector;
}

void sub_02058BC4(LocalMapObject *object, VecFx32 *vector) {
    *vector = object->unk94;
}

void sub_02058BD4(LocalMapObject *object, VecFx32 *vector) {
    object->unk94 = *vector;
}

u32 MapObject_GetPositionVectorYCoordUInt(LocalMapObject *object) {
    fx32 y = MapObject_GetPositionVectorYCoord(object);
    return (y >> 3) / FX32_ONE;
}

static void ObjectEvent_SetID(ObjectEvent *objectEvent, u16 id) {
    objectEvent->id = id;
}

static u16 ObjectEvent_GetID(ObjectEvent *objectEvent) {
    return objectEvent->id;
}

static void ObjectEvent_SetSpriteID(ObjectEvent *objectEvent, u32 spriteId) {
    objectEvent->spriteId = spriteId;
}

static u16 ObjectEvent_GetSpriteID(ObjectEvent *objectEvent) {
    return objectEvent->spriteId;
}

static void ObjectEvent_SetMovement(ObjectEvent *objectEvent, u32 movement) {
    objectEvent->movement = movement;
}

static u16 ObjectEvent_GetMovement(ObjectEvent *objectEvent) {
    return objectEvent->movement;
}

static void ObjectEvent_SetType(ObjectEvent *objectEvent, u16 type) {
    objectEvent->type = type;
}

static u16 ObjectEvent_GetType(ObjectEvent *objectEvent) {
    return objectEvent->type;
}

static void ObjectEvent_SetEventFlag(ObjectEvent *objectEvent, u16 eventFlag) {
    objectEvent->eventFlag = eventFlag;
}

static u16 ObjectEvent_GetEventFlag(ObjectEvent *objectEvent) {
    return objectEvent->eventFlag;
}

static void ObjectEvent_SetScriptID(ObjectEvent *objectEvent, u16 scriptId) {
    objectEvent->scriptId = scriptId;
}

static u16 ObjectEvent_GetScriptID(ObjectEvent *objectEvent) {
    return objectEvent->scriptId;
}

static void ObjectEvent_SetFacingDirection(ObjectEvent *objectEvent, u32 facingDirection) {
    objectEvent->facingDirection = facingDirection;
}

static s16 ObjectEvent_GetFacingDirection(ObjectEvent *objectEvent) {
    return objectEvent->facingDirection;
}

static void ObjectEvent_SetParam(ObjectEvent *objectEvent, s32 value, u32 param) {
    switch (param) {
    case 0:
        objectEvent->param[0] = value;
        return;
    case 1:
        objectEvent->param[1] = value;
        return;
    case 2:
        objectEvent->param[2] = value;
        return;
    default:
        GF_ASSERT(FALSE);
        return;
    }
}

static u16 ObjectEvent_GetParam(ObjectEvent *objectEvent, u32 param) {
    switch (param) {
    case 0:
        return objectEvent->param[0];
    case 1:
        return objectEvent->param[1];
    case 2:
        return objectEvent->param[2];
    default:
        GF_ASSERT(FALSE);
        return 0;
    }
}

static void ObjectEvent_SetXRange(ObjectEvent *objectEvent, s16 xRange) {
    objectEvent->xRange = xRange;
}

static s16 ObjectEvent_GetXRange(ObjectEvent *objectEvent) {
    return objectEvent->xRange;
}

static void ObjectEvent_SetYRange(ObjectEvent *objectEvent, s16 yRange) {
    objectEvent->yRange = yRange;
}

static s16 ObjectEvent_GetYRange(ObjectEvent *objectEvent) {
    return objectEvent->yRange;
}

static void ObjectEvent_SetXCoord(ObjectEvent *objectEvent, u32 x) {
    objectEvent->x = x;
}

static u16 ObjectEvent_GetXCoord(ObjectEvent *objectEvent) {
    return objectEvent->x;
}

static void ObjectEvent_SetYCoord(ObjectEvent *objectEvent, u32 y) {
    objectEvent->y = y;
}

static u32 ObjectEvent_GetYCoord(ObjectEvent *objectEvent) {
    return objectEvent->y;
}

static void ObjectEvent_SetZCoord(ObjectEvent *objectEvent, u32 z) {
    objectEvent->z = z;
}

static u16 ObjectEvent_GetZCoord(ObjectEvent *objectEvent) {
    return objectEvent->z;
}

static ObjectEvent *ObjectEvent_GetByID(u16 id, s32 objectEventCount, ObjectEvent *objectEvents) {
    s32 i                    = 0;
    ObjectEvent *objectEvent = objectEvents;
    do {
        if (!ObjectEvent_ScriptIDIsUnset(objectEvent) && id == ObjectEvent_GetID(objectEvent)) {
            return objectEvents + i;
        }

        i++;
        objectEvent++;
    } while (i < objectEventCount);

    return NULL;
}

static BOOL ObjectEvent_ScriptIDIsUnset(ObjectEvent *objectEvent) {
    // casts required to match
    u16 script = (u16)(u32)ObjectEvent_GetScriptID(objectEvent);
    return script == 0xFFFF;
}

static u16 ObjectEvent_GetEventFlag_AssertScriptIDIsUnset(ObjectEvent *template) {
    GF_ASSERT(ObjectEvent_ScriptIDIsUnset(template) == TRUE);
    return ObjectEvent_GetEventFlag(template);
}

static UnkLMOCallbackStruct *sub_02058D14(u32 movement) {
    GF_ASSERT(movement < NELEMS(UNK_020F6364));
    return UNK_020F6364[movement];
}

static LocalMapObject_UnkCallback sub_02058D2C(UnkLMOCallbackStruct *callbackStruct) {
    return callbackStruct->unk4;
}

static LocalMapObject_UnkCallback sub_02058D30(UnkLMOCallbackStruct *callbackStruct) {
    return callbackStruct->unk8;
}

static LocalMapObject_UnkCallback sub_02058D34(UnkLMOCallbackStruct *callbackStruct) {
    return callbackStruct->unkC;
}

static LocalMapObject_UnkCallback sub_02058D38(UnkLMOCallbackStruct2 *callbackStruct) {
    return callbackStruct->unk0;
}

static LocalMapObject_UnkCallback sub_02058D3C(UnkLMOCallbackStruct2 *callbackStruct) {
    return callbackStruct->unk4;
}

static LocalMapObject_UnkCallback sub_02058D40(UnkLMOCallbackStruct2 *callbackStruct) {
    return callbackStruct->unk8;
}

static LocalMapObject_UnkCallback sub_02058D44(UnkLMOCallbackStruct2 *callbackStruct) {
    return callbackStruct->unkC;
}

static LocalMapObject_UnkCallback sub_02058D48(UnkLMOCallbackStruct2 *callbackStruct) {
    return callbackStruct->unk10;
}

static UnkLMOCallbackStruct2 *sub_02058D4C(u32 spriteId) {
    UnkLMOCallbackStruct3 *array = ov05_021F9494;
    do {
        if (array[0].spriteId == spriteId) {
            return array[0].callbackStruct;
        }
        array++;
    } while (array[0].spriteId != 0xFFFF);

    GF_ASSERT(FALSE);
    return NULL;
}

LocalMapObject *MapObjectManager_GetFirstObjectWithXAndZ(MapObjectManager *manager, u32 x, u32 z) {
    u32 count               = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);

    do {
        if (MapObject_GetFlagsBitsMask(objects, MAPOBJECTFLAG_ACTIVE) != 0) {
            if (x == MapObject_GetCurrentX(objects) && z == MapObject_GetCurrentZ(objects)) {
                return objects;
            }
        }

        objects++;
        count--;
    } while (count > 0);

    return NULL;
}

void LocalMapObject_SetPositionFromVectorAndDirection(LocalMapObject *object, VecFx32 *positionVector, u32 direction) {
    MapObject_SetCurrentX(object, (positionVector->x >> 4) / FX32_ONE);
    MapObject_SetCurrentY(object, (positionVector->y >> 3) / FX32_ONE);
    MapObject_SetCurrentZ(object, (positionVector->z >> 4) / FX32_ONE);
    MapObject_SetPositionVector(object, positionVector);
    sub_02059C60(object);
    MapObject_SetFacingDirectionDirect(object, direction);
    MapObject_ClearHeldMovement(object);
    MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK2);
    MapObject_ClearFlagsBits(object, (MapObjectFlagBits)(MAPOBJECTFLAG_UNK3 | MAPOBJECTFLAG_SINGLE_MOVEMENT));
}

void MapObject_SetPositionFromXYZAndDirection(LocalMapObject *object, u32 x, u32 y, u32 z, u32 direction) {
    VecFx32 positionVector;
    positionVector.x = x * (16 * FX32_ONE) + (8 * FX32_ONE);
    MapObject_SetCurrentX(object, x);
    positionVector.y = y * (8 * FX32_ONE);
    MapObject_SetCurrentY(object, y);
    positionVector.z = z * (16 * FX32_ONE) + (8 * FX32_ONE);
    MapObject_SetCurrentZ(object, z);

    MapObject_SetPositionVector(object, &positionVector);
    sub_02059C60(object);
    MapObject_SetFacingDirectionDirect(object, direction);
    MapObject_SetFlagsBits(object, MAPOBJECTFLAG_UNK2);
    MapObject_ClearFlagsBits(object, (MapObjectFlagBits)(MAPOBJECTFLAG_UNK3 | MAPOBJECTFLAG_SINGLE_MOVEMENT));
    MapObject_ClearHeldMovement(object);
}

void sub_02058E90(LocalMapObject *object, u32 movement) {
    sub_02058660(object);
    MapObject_SetMovement(object, movement);
    sub_02057EE0(object);
    sub_02058EE8(object);
}

void sub_02058EB0(LocalMapObject *object, u32 id) {
    MapObject_SetID(object, id);
    MapObject_SetFlag2(object);
    sub_0205815C(object);
}

void sub_02058EC8(LocalMapObject *object) {
}

void sub_02058ECC(LocalMapObject *object) {
}

void sub_02058ED0(LocalMapObject *object) {
}

void sub_02058ED4(LocalMapObject *object) {
}

void sub_02058ED8(LocalMapObject *object) {
}

void sub_02058EDC(LocalMapObject *object) {
}

void sub_02058EE0(LocalMapObject *object) {
}

void sub_02058EE4(LocalMapObject *object) {
}
