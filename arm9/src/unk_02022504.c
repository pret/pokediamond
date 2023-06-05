#include "global.h"
#include "unk_02022504.h"

THUMB_FUNC void *FUN_02022504(struct SaveBlock2 *sav2)
{
    return SaveArray_Get(sav2, 27);
}

THUMB_FUNC struct PCStorage *GetStoragePCPointer(struct SaveBlock2 *sav2)
{
    return SaveArray_Get(sav2, 35);
}

THUMB_FUNC struct UnkStruct_0202AC20 * FUN_0202251C(struct SaveBlock2 *sav2)
{
    return SaveArray_Get(sav2, 31);
}

THUMB_FUNC void *FUN_02022528(struct SaveBlock2 *sav2)
{
    return SaveArray_Get(sav2, 32);
}

THUMB_FUNC u8 *LoadHallOfFame(struct SaveBlock2 *sav2, u32 heap_id, int *ret_p)
{
    return ReadSaveFileFromFlash(sav2, heap_id, 0, ret_p);
}

THUMB_FUNC s32 SaveHallOfFame(struct SaveBlock2 *sav2, u8 *data)
{
    return WriteSaveFileToFlash(sav2, 0, data);
}
