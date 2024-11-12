#include "unk_0206439C.h"

#include "global.h"

#include "heap.h"
#include "party.h"
#include "save.h"

UnkStruct_0206439C *sub_0206439C(HeapID heapId, u8 mon_idx, SaveData *save) {
    UnkStruct_0206439C *ret = AllocFromHeapAtEnd(heapId, sizeof(UnkStruct_0206439C));
    Party *party = SaveArray_Party_Get(save);

    ret->pokemon = Party_GetMonByIndex(party, mon_idx);
    ret->unk4 = NULL;

    return ret;
}
