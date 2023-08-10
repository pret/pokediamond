#ifndef POKEDIAMOND_SCRIPT_POKEMON_UTIL_H
#define POKEDIAMOND_SCRIPT_POKEMON_UTIL_H

BOOL MonNotFaintedOrEgg(struct Pokemon * pokemon);
BOOL GiveMon(HeapID heapId, struct SaveData * save, u16 species, u8 level, u16 item, u32 mapSec, u32 encounterType);
BOOL GiveEgg(HeapID heapId, struct SaveData * save, u16 species, int level, int metLocIndex, int a3);
void PartyMonSetMoveInSlot(struct Party * party, int partySlot, int moveSlot, u16 move);
int GetIdxOfFirstPartyMonWithMove(struct Party * party, int move);
int CountAlivePokemon(struct Party * party);
struct Pokemon * GetFirstAliveMonInParty_CrashIfNone(struct Party * party);
struct Pokemon * GetFirstNonEggInParty(struct Party * party);
BOOL HasEnoughAlivePokemonForDoubleBattle(struct Party * party);
void GiveAllMonsTheSinnohChampRibbon(struct Party * party);
int ApplyPoisonStep(struct Party * party, int location);
BOOL SurvivePoisoning(struct Pokemon * mon);

#endif //POKEDIAMOND_SCRIPT_POKEMON_UTIL_H
