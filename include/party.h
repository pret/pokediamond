#ifndef POKEDIAMOND_PARTY_H
#define POKEDIAMOND_PARTY_H

#include "pokemon.h"
#include "save.h"

BOOL PartyHasMon(struct Party * party_p, u16 species);
int GetPartyCount(struct Party * party_p);
struct Pokemon * GetPartyMonByIndex(struct Party * party_p, int idx);
u32 SaveArray_Party_sizeof(void);
struct Party * SaveArray_Party_Alloc(HeapID heapId);
void SaveArray_Party_Init(struct Party * party);
void InitPartyWithMaxSize(struct Party * party, int count);
BOOL AddMonToParty(struct Party * party, struct Pokemon * pokemon);
BOOL RemoveMonFromParty(struct Party * party, int pos);
void ReplacePartySlotWithMon(struct Party * party, int pos, struct Pokemon * pokemon);
BOOL SwapSlotsInParty(struct Party * party, int pos1, int pos2);
void CopyParty(struct Party * src, struct Party * dest);
struct Party * SaveArray_Party_Get(struct SaveData * ptr);

#endif //POKEDIAMOND_PARTY_H
