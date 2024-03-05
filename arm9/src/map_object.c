#include "global.h"
#include "map_object.h"
#include "field_system.h"
#include "heap.h"

static MapObjectManager *MapObjectManager_New(u32 objectCount);
/*static*/ LocalMapObject *MapObject_CreateFromObjectEventInternal(MapObjectManager *manager, ObjectEvent *objectEvent, u32 mapNo);

extern void MapObjectManager_SetFieldSystemPtr(MapObjectManager *manager, FieldSystem *fieldSystem);
extern void MapObjectManager_SetObjectCount(MapObjectManager *manager, u32 objectCount);
extern void MapObjectManager_SetHeapID(MapObjectManager *manager, HeapID heapId);
extern LocalMapObject *MapObjectManager_GetObjects(MapObjectManager *manager);
extern u32 MapObjectManager_GetObjectCount(MapObjectManager *manager);
extern BOOL MapObject_IsInUse(LocalMapObject *object);
extern void MapObject_Remove(LocalMapObject *object);
extern void ov05_021F2AF4(MapObjectManager *manager, void *param0);
extern void *sub_020583A0(MapObjectManager *manager);
extern u32 sub_02058450(LocalMapObject *object);
extern BOOL MapObject_TestFlagsBits(LocalMapObject *object, u32 flags);
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
extern void MapObject_SetFlagsBits(LocalMapObject *object, u32 flag);
extern void sub_02057CF0(MapObjectManager *manager, LocalMapObject *object);
extern MapObjectManager *MapObjectManager_GetMapObjectManager(MapObjectManager *manager);
extern void sub_0205836C(MapObjectManager *manager);

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

/*static*/ LocalMapObject *MapObject_CreateFromObjectEventInternal(MapObjectManager *manager, ObjectEvent *objectEvent, u32 mapNo) {
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
