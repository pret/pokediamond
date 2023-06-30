#ifndef POKEDIAMOND_UNK_02022504_H
#define POKEDIAMOND_UNK_02022504_H

#include "hall_of_fame.h"
#include "safari_zone.h"
#include "save.h"
#include "pokemon_storage_system.h"
#include "unk_0202AC20.h"

SafariZone *Save_SafariZone_Get(struct SaveData *save);
struct PCStorage *GetStoragePCPointer(struct SaveData *save);
struct UnkStruct_0202AC20 * sub_0202251C(struct SaveData *save);
void *sub_02022528(struct SaveData *save);
HallOfFame *LoadHallOfFame(struct SaveData *save, HeapID heapId, int *ret_p);
s32 SaveHallOfFame(struct SaveData *save, HallOfFame *data);

#endif //POKEDIAMOND_UNK_02022504_H
