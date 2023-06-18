#include "global.h"
#include "unk_02022504.h"

void *FUN_02022504(struct SaveData *save)
{
    return SaveArray_Get(save, 27);
}

struct PCStorage *GetStoragePCPointer(struct SaveData *save)
{
    return SaveArray_Get(save, 35);
}

struct UnkStruct_0202AC20 * FUN_0202251C(struct SaveData *save)
{
    return SaveArray_Get(save, 31);
}

void *FUN_02022528(struct SaveData *save)
{
    return SaveArray_Get(save, 32);
}

u8 *LoadHallOfFame(struct SaveData *save, u32 heap_id, int *ret_p)
{
    return ReadSaveFileFromFlash(save, heap_id, 0, ret_p);
}

s32 SaveHallOfFame(struct SaveData *save, u8 *data)
{
    return WriteSaveFileToFlash(save, 0, data);
}
