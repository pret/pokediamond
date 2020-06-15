#ifndef POKEDIAMOND_PARTY_H
#define POKEDIAMOND_PARTY_H

#include "pokemon.h"

#define PARTY_SIZE 6

struct PlayerParty
{
    u32 maxCount;
    u32 curCount;
    struct Pokemon mons[PARTY_SIZE];
};

BOOL PartyHasMon(struct PlayerParty * party_p, u16 species);
int GetPartyCount(struct PlayerParty * party_p);
struct Pokemon * GetPartyMonByIndex(struct PlayerParty * party_p, int idx);

#endif //POKEDIAMOND_PARTY_H
