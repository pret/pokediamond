#include "global.h"
#include "heap.h"
#include "party.h"
#include "save_block_2.h"
#include "unk_0206439C.h"

struct UnkStruct_0206439C* FUN_0206439C(u32 heap_id, u8 mon_idx, struct SaveBlock2* sav2)
{
    struct UnkStruct_0206439C* ret = AllocFromHeapAtEnd(heap_id, sizeof(struct UnkStruct_0206439C));
    struct PlayerParty* party = SaveArray_PlayerParty_Get(sav2);

    ret->pokemon = GetPartyMonByIndex(party, mon_idx);
    ret->unk4 = NULL;

    return ret;
}
