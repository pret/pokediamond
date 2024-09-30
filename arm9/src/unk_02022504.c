#include "unk_02022504.h"

#include "global.h"

#include "constants/save_arrays.h"

SafariZone *Save_SafariZone_Get(struct SaveData *save) {
    return SaveArray_Get(save, SAVE_SAFARI_ZONE);
}

struct PCStorage *SaveArray_PCStorage_Get(struct SaveData *save) {
    return SaveArray_Get(save, 35);
}

struct UnkStruct_0202AC20 *sub_0202251C(struct SaveData *save) {
    return SaveArray_Get(save, 31);
}

void *sub_02022528(struct SaveData *save) {
    return SaveArray_Get(save, 32);
}

HallOfFame *LoadHallOfFame(struct SaveData *save, HeapID heapId, int *ret_p) {
    return (HallOfFame *)ReadSaveFileFromFlash(save, heapId, 0, ret_p);
}

s32 SaveHallOfFame(struct SaveData *save, HallOfFame *data) {
    return WriteSaveFileToFlash(save, 0, (u8 *)data);
}
