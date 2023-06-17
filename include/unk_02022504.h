#ifndef POKEDIAMOND_UNK_02022504_H
#define POKEDIAMOND_UNK_02022504_H

#include "save.h"
#include "pokemon_storage_system.h"
#include "unk_0202AC20.h"

void *FUN_02022504(struct SaveData *save);
struct PCStorage *GetStoragePCPointer(struct SaveData *save);
struct UnkStruct_0202AC20 * FUN_0202251C(struct SaveData *save);
void *FUN_02022528(struct SaveData *save);
u8 *LoadHallOfFame(struct SaveData *save, u32 heap_id, int *ret_p);
s32 SaveHallOfFame(struct SaveData *save, u8 *data);

#endif //POKEDIAMOND_UNK_02022504_H
