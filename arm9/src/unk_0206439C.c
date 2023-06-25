#include "global.h"
#include "heap.h"
#include "party.h"
#include "save.h"
#include "unk_0206439C.h"

struct UnkStruct_0206439C* sub_0206439C(HeapID heapId, u8 mon_idx, struct SaveData* save)
{
    struct UnkStruct_0206439C* ret = AllocFromHeapAtEnd(heapId, sizeof(struct UnkStruct_0206439C));
    struct PlayerParty* party = SaveArray_PlayerParty_Get(save);

    ret->pokemon = GetPartyMonByIndex(party, mon_idx);
    ret->unk4 = NULL;

    return ret;
}
