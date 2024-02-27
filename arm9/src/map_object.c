#include "global.h"
#include "map_object.h"
#include "field_system.h"
#include "heap.h"

extern MapObjectManager *MapObjectManager_New(u32 objectCount);
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
