#ifndef POKEDIAMOND_PARTY_H
#define POKEDIAMOND_PARTY_H

#include "pokemon.h"
#include "save_block_2.h"

BOOL PartyHasMon(struct PlayerParty * party_p, u16 species);
int GetPartyCount(struct PlayerParty * party_p);
struct Pokemon * GetPartyMonByIndex(struct PlayerParty * party_p, int idx);
u32 SaveArray_Party_sizeof(void);
struct PlayerParty * SaveArray_Party_Alloc(u32 heap_id);
void SaveArray_Party_Init(struct PlayerParty * party);
void InitPartyWithMaxSize(struct PlayerParty * party, int count);
BOOL AddMonToParty(struct PlayerParty * party, struct Pokemon * pokemon);
BOOL RemoveMonFromParty(struct PlayerParty * party, int pos);
void ReplacePartySlotWithMon(struct PlayerParty * party, int pos, struct Pokemon * pokemon);
BOOL SwapSlotsInParty(struct PlayerParty * party, int pos1, int pos2);
void CopyPlayerParty(struct PlayerParty * src, struct PlayerParty * dest);
struct PlayerParty * SaveArray_PlayerParty_Get(struct SaveBlock2 * ptr);

#endif //POKEDIAMOND_PARTY_H
