#include "global.h"
#include "map_object.h"
#include "field_system.h"
#include "heap.h"

static MapObjectManager *MapObjectManager_New(u32 objectCount);
/*static*/ LocalMapObject *MapObject_CreateFromObjectEvent(MapObjectManager *manager, ObjectEvent *objectEvent, u32 mapNo);
static void SavedMapObject_InitFromLocalMapObject(FieldSystem *fieldSystem, LocalMapObject *object, SavedMapObject *savedObject);

extern BOOL sub_020580F4(MapObjectManager *manager, LocalMapObject **object, s32 *index, MapObjectFlagBits bits);

extern void MapObjectManager_SetFieldSystemPtr(MapObjectManager *manager, FieldSystem *fieldSystem);
extern void MapObjectManager_SetObjectCount(MapObjectManager *manager, u32 objectCount);
extern void MapObjectManager_SetHeapID(MapObjectManager *manager, HeapID heapId);
extern LocalMapObject *MapObjectManager_GetObjects(MapObjectManager *manager);
extern u32 MapObjectManager_GetObjectCount(MapObjectManager *manager);
extern BOOL MapObject_IsInUse(LocalMapObject *object);
extern void ov05_021F2AF4(MapObjectManager *manager, void *param0);
extern void *sub_020583A0(MapObjectManager *manager);
extern u32 sub_02058450(LocalMapObject *object);
extern BOOL MapObject_TestFlagsBits(LocalMapObject *object, MapObjectFlagBits flags);
extern u32 sub_02057F90(LocalMapObject *object, u32 a2, u32 objectCount, ObjectEvent *objectEvents);
extern void MapObjectManager_SetObjects(MapObjectManager *manager, LocalMapObject *objects);
extern u32 ObjectEvent_GetID(ObjectEvent *objectEvent);
extern BOOL ObjectEvent_ScriptIdIsUnset(ObjectEvent *objectEvent);
extern LocalMapObject *sub_02057C98(MapObjectManager *manager, u32 objectId, u32 mapNo);
extern void sub_02058214(LocalMapObject *object, ObjectEvent *objectEvent, u32 mapNo);
extern u16 ObjectEvent_GetFlagID_AssertScriptIdIsUnset(ObjectEvent *objectEvent);
extern LocalMapObject *sub_02058010(MapObjectManager *manager, u32 objectId, u16 flagId);
extern void sub_02058258(LocalMapObject *object, u32 mapNo, ObjectEvent *objectEvent);
extern LocalMapObject *MapObjectManager_GetFirstInactiveObject(MapObjectManager *manager);
extern FieldSystem *MapObjectManager_GetFieldSystemPtr(MapObjectManager *manager);
extern void MapObject_InitFromObjectEvent(LocalMapObject *object, ObjectEvent *objectEvent, FieldSystem *fieldSystem);
extern void sub_02057E90(LocalMapObject *object, MapObjectManager *manager);
extern void sub_0205844C(LocalMapObject *object, u32 mapNo);
extern void sub_020581A4(LocalMapObject *object);
extern void sub_020581B4(LocalMapObject *object);
extern void MapObject_SetFlagsBits(LocalMapObject *object, MapObjectFlagBits bits);
extern void sub_02057CF0(MapObjectManager *manager, LocalMapObject *object);
extern MapObjectManager *MapObjectManager_GetMapObjectManager(MapObjectManager *manager);
extern void sub_0205836C(MapObjectManager *manager);
extern void ObjectEvent_SetId(ObjectEvent *objectEvent, u32 id);
extern void ObjectEvent_SetSprite(ObjectEvent *objectEvent, u32 sprite);
extern void ObjectEvent_SetMovement(ObjectEvent *objectEvent, u32 movement);
extern void ObjectEvent_SetType(ObjectEvent *objectEvent, u32 type);
extern void ObjectEvent_SetFlagId(ObjectEvent *objectEvent, u32 flagId);
extern void ObjectEvent_SetScript(ObjectEvent *objectEvent, u32 script);
extern void ObjectEvent_SetFacing(ObjectEvent *objectEvent, u32 direction);
extern void ObjectEvent_SetParam(ObjectEvent *objectEvent, u32 value, u32 param);
extern void ObjectEvent_SetXRange(ObjectEvent *objectEvent, u32 xRange);
extern void ObjectEvent_SetYRange(ObjectEvent *objectEvent, u32 yRange);
extern void ObjectEvent_SetXCoord(ObjectEvent *objectEvent, u32 xCoord);
extern void ObjectEvent_SetYCoord(ObjectEvent *objectEvent, u32 yCoord);
extern void ObjectEvent_SetHeight(ObjectEvent *objectEvent, u32 height);
extern u32 ObjectEvent_GetFlagId(ObjectEvent *objectEvent);
extern ObjectEvent *ObjectEvent_GetById(u32 id, u32 objectEventCount, ObjectEvent *events);
extern u8 FieldSystem_FlagCheck(FieldSystem *fieldSystem, u16 flag);
extern void MapObject_SetGfxId(LocalMapObject *object, u32 sprite);
extern void sub_02058148(LocalMapObject *object);
extern void MapObject_ClearFlagsBits(LocalMapObject *object, MapObjectFlagBits bits);
extern BOOL sub_02058934(LocalMapObject *object);
extern MapObjectManager *MapObject_GetManager(LocalMapObject *object);
extern BOOL sub_020587E0(MapObjectManager *manager);
extern void sub_020586B4(LocalMapObject *object);
extern void sub_02058660(LocalMapObject *object);
extern void sub_02058564(LocalMapObject *object);
extern MapObjectManager *sub_02058580(LocalMapObject *object);
extern void sub_02058374(MapObjectManager *manager);
extern void sub_02057F80(LocalMapObject *object);
extern u32 MapObject_GetFlagID(LocalMapObject *object);
extern FieldSystem *MapObject_GetFieldSystemPtr(LocalMapObject *object);
extern void FieldSystem_FlagSet(FieldSystem *fieldSystem, u16 flag);
extern void sub_02058ED8(LocalMapObject *object);
extern void sub_02058EDC(LocalMapObject *object);
extern void sub_02058EE0(LocalMapObject *object);
extern void sub_02058EE4(LocalMapObject *object);
extern u32 MapObject_GetFlagsBits(LocalMapObject *object, MapObjectFlagBits bits);
extern void sub_02058684(LocalMapObject *object, LocalMapObject_UnkCallback callback);
extern void sub_02058698(LocalMapObject *object, LocalMapObject_UnkCallback callback);
extern void sub_020586AC(LocalMapObject *object, LocalMapObject_UnkCallback callback);
extern void sub_020586C0(LocalMapObject *object, LocalMapObject_UnkCallback callback);
extern void sub_020586D4(LocalMapObject *object, LocalMapObject_UnkCallback callback);
extern void sub_020586C8(LocalMapObject *object);
extern void sub_0205816C(LocalMapObject *object);
extern BOOL MapObject_CheckFlag14(LocalMapObject *object);
extern void sub_020586DC(LocalMapObject *object);
extern void sub_020579C4(LocalMapObject *object, SavedMapObject *savedObject);
extern void sub_02057AEC(MapObjectManager *manager, LocalMapObject *object);
extern u32 MapObject_GetFlagsWord(LocalMapObject *object);
extern u32 MapObject_GetFlags2Word(LocalMapObject *object);
extern u32 MapObject_GetID(LocalMapObject *object);
extern u32 MapObject_GetGfxID(LocalMapObject *object);
extern u32 MapObject_GetMovement(LocalMapObject *object);
extern u32 MapObject_GetType(LocalMapObject *object);
extern u32 MapObject_GetScript(LocalMapObject *object);
extern u32 MapObject_GetInitialFacingDirection(LocalMapObject *object);
extern u32 MapObject_GetFacingDirection(LocalMapObject *object);
extern u32 MapObject_GetNextFacingDirection(LocalMapObject *object);
extern u32 MapObject_GetParam(LocalMapObject *object, u32 param);
extern u32 MapObject_GetXRange(LocalMapObject *object);
extern u32 MapObject_GetYRange(LocalMapObject *object);
extern u32 MapObject_GetInitialX(LocalMapObject *object);
extern u32 MapObject_GetInitialHeight(LocalMapObject *object);
extern u32 MapObject_GetInitialY(LocalMapObject *object);
extern u32 MapObject_GetCurrentX(LocalMapObject *object);
extern u32 MapObject_GetCurrentHeight(LocalMapObject *object);
extern u32 MapObject_GetCurrentY(LocalMapObject *object);
extern void sub_02059E60(s32 x, s32 y, VecFx32 *vector);
extern u32 MapObject_GetPosVecYCoord(LocalMapObject *object);
extern u32 MapObject_CheckFlag29(LocalMapObject *object);
extern u8 *sub_020585B0(LocalMapObject *object);
extern u8 *sub_020585D8(LocalMapObject *object);
extern BOOL sub_02059EC8(FieldSystem *fieldSystem, VecFx32 *vector, BOOL flag);

MapObjectManager *MapObjectManager_Init(FieldSystem *fieldSystem, u32 objectCount, HeapID heapId) {
    MapObjectManager *ret = MapObjectManager_New(objectCount);
    MapObjectManager_SetFieldSystemPtr(ret, fieldSystem);
    MapObjectManager_SetObjectCount(ret, objectCount);
    MapObjectManager_SetHeapID(ret, heapId);

    return ret;
}

void MapObjectManager_Delete(MapObjectManager *manager) {
    FreeToHeapExplicit(HEAP_ID_FIELD, MapObjectManager_GetObjects(manager));
    FreeToHeapExplicit(HEAP_ID_FIELD, manager);
}

void sub_020573C8(MapObjectManager *manager, u32 unused, u32 a2, u32 objectCount, ObjectEvent *objectEvents) {
    u32 count = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);

    for (; count != 0; count--) {
        if (MapObject_IsInUse(objects) == TRUE) {
            switch (sub_02057F90(objects, a2, objectCount, objectEvents)) {
                case 0:
                    if (sub_02058450(objects) != a2 && !MapObject_TestFlagsBits(objects, MAPOBJECTFLAG_UNK10)) {
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

/*static*/ LocalMapObject *MapObject_CreateFromObjectEvent(MapObjectManager *manager, ObjectEvent *objectEvent, u32 mapNo) {
    LocalMapObject *ret;

    u32 objectId = ObjectEvent_GetID(objectEvent);
    if (!ObjectEvent_ScriptIdIsUnset(objectEvent)) {
        ret = sub_02057C98(manager, objectId, mapNo);
        if (ret != NULL) {
            sub_02058214(ret, objectEvent, mapNo);
            return ret;
        }
    } else {
        ret = sub_02058010(manager, objectId, ObjectEvent_GetFlagID_AssertScriptIdIsUnset(objectEvent));
        if (ret != NULL) {
            sub_02058258(ret, mapNo, objectEvent);
            return ret;
        }
    }
    
    ret = MapObjectManager_GetFirstInactiveObject(manager);
    if (ret == NULL) {
        return ret;
    }

    MapObject_InitFromObjectEvent(ret, objectEvent, MapObjectManager_GetFieldSystemPtr(manager));
    sub_02057E90(ret, manager);
    sub_0205844C(ret, mapNo);
    sub_020581A4(ret);
    sub_020581B4(ret);
    MapObject_SetFlagsBits(ret, MAPOBJECTFLAG_UNK2);
    sub_02057CF0(manager, ret);
    sub_0205836C(MapObjectManager_GetMapObjectManager(manager));
    return ret;
}

LocalMapObject *MapObject_Create(MapObjectManager *manager, u32 x, u32 y, u32 direction, u32 sprite, u32 movement, u32 mapNo) {
    ObjectEvent objectEvent;
    ObjectEvent_SetId(&objectEvent, 0);
    ObjectEvent_SetSprite(&objectEvent, sprite);
    ObjectEvent_SetMovement(&objectEvent, movement);
    ObjectEvent_SetType(&objectEvent, 0);
    ObjectEvent_SetFlagId(&objectEvent, 0);
    ObjectEvent_SetScript(&objectEvent, 0);
    ObjectEvent_SetFacing(&objectEvent, direction);
    ObjectEvent_SetParam(&objectEvent, 0, 0);
    ObjectEvent_SetParam(&objectEvent, 0, 1);
    ObjectEvent_SetParam(&objectEvent, 0, 2);
    ObjectEvent_SetXRange(&objectEvent, 0);
    ObjectEvent_SetYRange(&objectEvent, 0);
    ObjectEvent_SetXCoord(&objectEvent, x);
    ObjectEvent_SetYCoord(&objectEvent, y);
    ObjectEvent_SetHeight(&objectEvent, 0);

    return MapObject_CreateFromObjectEvent(manager, &objectEvent, mapNo);
}

LocalMapObject *MapObject_CreateFromObjectEventWithId(MapObjectManager *manager, u16 id, u32 objectEventCount, u32 mapNo, const ObjectEvent *events) {
    LocalMapObject *ret = NULL;
    ObjectEvent *objectEvent = ObjectEvent_GetById(id, objectEventCount, (ObjectEvent *)events);
    if (objectEvent != NULL) {
        u32 flagId = ObjectEvent_GetFlagId(objectEvent);
        FieldSystem* fieldSystem = MapObjectManager_GetFieldSystemPtr(manager);
        if (FieldSystem_FlagCheck(fieldSystem, (u16)flagId) == FALSE) {
            ret = MapObject_CreateFromObjectEvent(manager, objectEvent, mapNo);
        }
    }

    return ret;
}

void sub_02057614(LocalMapObject *object, u32 sprite) {
    MapObject_SetGfxId(object, sprite);
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
    sub_02058374(sub_02058580(object));
    sub_02057F80(object);
}

void MapObject_Delete(LocalMapObject *object) {
    u32 flagId = MapObject_GetFlagID(object);
    FieldSystem *fieldSystem = MapObject_GetFieldSystemPtr(object);
    FieldSystem_FlagSet(fieldSystem, (u16)flagId);
    MapObject_Remove(object);
}

void sub_020576A8(LocalMapObject *object) {
    if (sub_020587E0(MapObject_GetManager(object)) == TRUE) {
        if (MapObject_GetFlagsBits(object, MAPOBJECTFLAG_UNK14) != 0) {
            sub_020586B4(object);
        }
        MapObject_ClearFlagsBits(object, MAPOBJECTFLAG_UNK14);
    }
    MapObject_SetGfxId(object, MAP_OBJECT_GFX_ID_INVALID);
    sub_02058684(object, sub_02058ED8);
    sub_02058698(object, sub_02058EDC);
    sub_020586AC(object, sub_02058EDC);
    sub_020586C0(object, sub_02058EE0);
    sub_020586D4(object, sub_02058EE4);
}

void MapObjectManager_RemoveAllActiveObjects(MapObjectManager *manager) {
    s32 i = 0;
    s32 count = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);

    do { //BUG: does not check for if count is zero, and will always execute at least once
        if (MapObject_GetFlagsBits(objects, MAPOBJECTFLAG_ACTIVE) != 0) {
            MapObject_Remove(objects);
        }

        i++;
        objects++;
    } while (i < count);
}

void sub_02057750(MapObjectManager *manager) {
    GF_ASSERT(sub_020587E0(manager) == TRUE);

    s32 i = 0;
    s32 count = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);

    do {
        if (MapObject_GetFlagsBits(objects, MAPOBJECTFLAG_ACTIVE) != 0 && MapObject_GetFlagsBits(objects, MAPOBJECTFLAG_UNK14) != 0) {
            sub_020586C8(objects);
            sub_0205816C(objects);
        }

        i++;
        objects++;
    } while (i < count);
}

void sub_020577A8(MapObjectManager *manager) {
    GF_ASSERT(sub_020587E0(manager) == TRUE);

    s32 i = 0;
    s32 count = MapObjectManager_GetObjectCount(manager);
    LocalMapObject *objects = MapObjectManager_GetObjects(manager);

    do {
        if (MapObject_IsInUse(objects) == TRUE) {
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

    while (sub_020580F4(manager, &object, &index, MAPOBJECTFLAG_ACTIVE)) { //MapObjectManager_GetNextActiveObject? this is an iterator however
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
        if ((savedObjects->flags & MAPOBJECTFLAG_ACTIVE)) {
            LocalMapObject* localObject = MapObjectManager_GetFirstInactiveObject(manager);
            GF_ASSERT(localObject != NULL);

            sub_020579C4(localObject, savedObjects);
            sub_02057AEC(manager, localObject);
        }
        savedObjects++;
        objectCount--;
    }
}

static void SavedMapObject_InitFromLocalMapObject(FieldSystem *fieldSystem, LocalMapObject *localObject, SavedMapObject *savedObject) {
    savedObject->flags = MapObject_GetFlagsWord(localObject);
    savedObject->flags2 = MapObject_GetFlags2Word(localObject);
    savedObject->objId = MapObject_GetID(localObject);
    savedObject->unk10 = sub_02058450(localObject);
    savedObject->gfxId = MapObject_GetGfxID(localObject);
    savedObject->movement = MapObject_GetMovement(localObject);
    savedObject->type = MapObject_GetType(localObject);
    savedObject->flagId = MapObject_GetFlagID(localObject);
    savedObject->script = MapObject_GetScript(localObject);
    savedObject->initialFacing = MapObject_GetInitialFacingDirection(localObject);
    savedObject->currentFacing = MapObject_GetFacingDirection(localObject);
    savedObject->nextFacing = MapObject_GetNextFacingDirection(localObject);
    savedObject->param[0] = MapObject_GetParam(localObject, 0);
    savedObject->param[1] = MapObject_GetParam(localObject, 1);
    savedObject->param[2] = MapObject_GetParam(localObject, 2);
    savedObject->xRange = MapObject_GetXRange(localObject);
    savedObject->yRange = MapObject_GetYRange(localObject);
    savedObject->initialX = MapObject_GetInitialX(localObject);
    savedObject->initialHeight = MapObject_GetInitialHeight(localObject);
    savedObject->initialY = MapObject_GetInitialY(localObject);
    savedObject->currentX = MapObject_GetCurrentX(localObject);
    savedObject->currentHeight = MapObject_GetCurrentHeight(localObject);
    savedObject->currentY = MapObject_GetCurrentY(localObject);

    VecFx32 coords;
    sub_02059E60(savedObject->currentX, savedObject->currentY, &coords); //some kind of x y vec copy with convertion between int and fx32
    coords.y = MapObject_GetPosVecYCoord(localObject);

    if (!sub_02059EC8(fieldSystem, &coords, MapObject_CheckFlag29(localObject))) {
        savedObject->vecY = MapObject_GetPosVecYCoord(localObject);
    } else {
        savedObject->vecY = coords.y;
    }
    
    memcpy(savedObject->unk30, sub_020585B0(localObject), 16);
    memcpy(savedObject->unk40, sub_020585D8(localObject), 16);
}
