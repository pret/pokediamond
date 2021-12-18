#ifndef POKEDIAMOND_UNK_02022504_H
#define POKEDIAMOND_UNK_02022504_H

#include "save_block_2.h"
#include "pokemon_storage_system.h"
#include "unk_0202AC20.h"

void *FUN_02022504(struct SaveBlock2 *sav2);
struct PCStorage *GetStoragePCPointer(struct SaveBlock2 *sav2);
struct UnkStruct_0202AC20 * FUN_0202251C(struct SaveBlock2 *sav2);
void *FUN_02022528(struct SaveBlock2 *sav2);
u8 *LoadHallOfFame(struct SaveBlock2 *sav2, u32 heap_id, int *ret_p);
s32 SaveHallOfFame(struct SaveBlock2 *sav2, u8 *data);

#endif //POKEDIAMOND_UNK_02022504_H
