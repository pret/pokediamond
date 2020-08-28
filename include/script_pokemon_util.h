#ifndef POKEDIAMOND_SCRIPT_POKEMON_UTIL_H
#define POKEDIAMOND_SCRIPT_POKEMON_UTIL_H

BOOL MonNotFaintedOrEgg(struct Pokemon * pokemon);
BOOL GiveMon(u32 heap_id, struct SaveBlock2 * sav2, u16 species, u8 level, u16 item, u32 mapSec, u32 encounterType);
BOOL GiveEgg(u32 heapId, struct SaveBlock2 * sav2, u16 species, int level, int metLocIndex, int a3);
void PartyMonSetMoveInSlot(struct PlayerParty * party, int partySlot, int moveSlot, u16 move);
int GetIdxOfFirstPartyMonWithMove(struct PlayerParty * party, int move);
int CountAlivePokemon(struct PlayerParty * party);
struct Pokemon * GetFirstAliveMonInParty_CrashIfNone(struct PlayerParty * party);
struct Pokemon * GetFirstNonEggInParty(struct PlayerParty * party);
BOOL HasEnoughAlivePokemonForDoubleBattle(struct PlayerParty * party);
void GiveAllMonsTheSinnohChampRibbon(struct PlayerParty * party);
int ApplyPoisonStep(struct PlayerParty * party, int location);
BOOL SurvivePoisoning(struct Pokemon * mon);

#endif //POKEDIAMOND_SCRIPT_POKEMON_UTIL_H
