#ifndef POKEDIAMOND_PARTY_H
#define POKEDIAMOND_PARTY_H

#include "pokemon.h"
#include "save.h"

BOOL Party_HasMon(struct Party *party_p, u16 species);
int Party_GetCount(struct Party *party_p);
struct Pokemon *Party_GetMonByIndex(struct Party *party_p, int idx);
u32 SaveArray_Party_sizeof(void);
struct Party *SaveArray_Party_Alloc(HeapID heapId);
void SaveArray_Party_Init(struct Party *party);
void Party_InitWithMaxSize(struct Party *party, int count);
BOOL Party_AddMon(struct Party *party, struct Pokemon *pokemon);
BOOL Party_RemoveMon(struct Party *party, int pos);
void ReplacePartySlotWithMon(struct Party *party, int pos, struct Pokemon *pokemon);
BOOL SwapSlotsInParty(struct Party *party, int pos1, int pos2);
void CopyParty(struct Party *src, struct Party *dest);
struct Party *SaveArray_Party_Get(struct SaveData *ptr);

#endif // POKEDIAMOND_PARTY_H
