#ifndef POKEDIAMOND_PARTY_H
#define POKEDIAMOND_PARTY_H

#include "pokemon.h"

BOOL PartyHasMon(struct PlayerParty * party_p, u16 species);
int GetPartyCount(struct PlayerParty * party_p);
struct Pokemon * GetPartyMonByIndex(struct PlayerParty * party_p, int idx);
u32 FUN_0206B8A4(void);
struct PlayerParty * FUN_0206B8AC(u32 heap_id);
void FUN_0206B8C0(struct PlayerParty * party);
void FUN_0206B8CC(struct PlayerParty * party, int count);
BOOL FUN_0206B900(struct PlayerParty * party, struct Pokemon * pokemon);
BOOL FUN_0206B938(struct PlayerParty * party, int pos);
void FUN_0206B9DC(struct PlayerParty * party, int pos, struct Pokemon * pokemon);
BOOL FUN_0206BA38(struct PlayerParty * party, int pos1, int pos2);
void FUN_0206BAD0(struct PlayerParty * src, struct PlayerParty * dest);
struct PlayerParty * FUN_0206BB1C(void * ptr);

#endif //POKEDIAMOND_PARTY_H
