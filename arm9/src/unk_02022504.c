#include "global.h"
#include "constants/save_arrays.h"
#include "unk_02022504.h"

SafariZone *Save_SafariZone_Get(struct SaveData *save)
{
    return SaveArray_Get(save, SAVE_SAFARI_ZONE);
}

struct PCStorage *GetStoragePCPointer(struct SaveData *save)
{
    return SaveArray_Get(save, 35);
}

struct UnkStruct_0202AC20 * sub_0202251C(struct SaveData *save)
{
    return SaveArray_Get(save, 31);
}

void *sub_02022528(struct SaveData *save)
{
    return SaveArray_Get(save, 32);
}

u8 *LoadHallOfFame(struct SaveData *save, HeapID heapId, int *ret_p)
{
    return ReadSaveFileFromFlash(save, heapId, 0, ret_p);
}

s32 SaveHallOfFame(struct SaveData *save, u8 *data)
{
    return WriteSaveFileToFlash(save, 0, data);
}
