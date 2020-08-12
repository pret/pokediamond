#include "global.h"
#include "party.h"
#include "heap.h"
#include "proto.h"

#pragma thumb on

void FUN_0206B8C0(struct PlayerParty * party);
void FUN_0206B8CC(struct PlayerParty * party, int count);

u32 FUN_0206B8A4(void)
{
    return sizeof(struct PlayerParty);
}

struct PlayerParty * FUN_0206B8AC(u32 heap_id)
{
    struct PlayerParty * ret = (struct PlayerParty *)AllocFromHeap(heap_id, sizeof(struct PlayerParty));
    FUN_0206B8C0(ret);
    return ret;
}

void FUN_0206B8C0(struct PlayerParty * party)
{
    FUN_0206B8CC(party, PARTY_SIZE);
}

void FUN_0206B8CC(struct PlayerParty * party, int count)
{
    int i;
    GF_ASSERT(count <= PARTY_SIZE);
    memset(party, 0, sizeof(struct PlayerParty));
    party->curCount = 0;
    party->maxCount = count;
    for (i = 0; i < 6; i++)
        ZeroMonData(&party->mons[i]);
}

BOOL FUN_0206B900(struct PlayerParty * party, struct Pokemon * pokemon)
{
    if (party->curCount >= party->maxCount)
        return FALSE;
    party->mons[party->curCount] = *pokemon;
    party->curCount++;
    return TRUE;
}

BOOL FUN_0206B938(struct PlayerParty * party, int pos)
{
    int i;

    GF_ASSERT(pos >= 0);
    GF_ASSERT(pos < party->curCount);
    GF_ASSERT(pos < party->maxCount);
    GF_ASSERT(party->curCount > 0);

    for (i = pos; i < party->curCount - 1; i++)
    {
        party->mons[i] = party->mons[i + 1];
    }

    ZeroMonData(&party->mons[i]);
    party->curCount--;
    return TRUE;
}

int GetPartyCount(struct PlayerParty * party)
{
    return party->curCount;
}

struct Pokemon * GetPartyMonByIndex(struct PlayerParty * party, int pos)
{
    GF_ASSERT(pos >= 0);
    GF_ASSERT(pos < party->curCount);
    GF_ASSERT(pos < party->maxCount);
    return &party->mons[pos];
}

void FUN_0206B9DC(struct PlayerParty * party, int pos, struct Pokemon * pokemon)
{
    int r2;
    GF_ASSERT(pos >= 0);
    GF_ASSERT(pos < party->curCount);
    GF_ASSERT(pos < party->maxCount);
    r2 = (int)(GetMonData(&party->mons[pos], MON_DATA_SPECIES_EXISTS, NULL) - GetMonData(pokemon, MON_DATA_SPECIES_EXISTS, NULL));
    party->mons[pos] = *pokemon;
    party->curCount += r2;
}

BOOL FUN_0206BA38(struct PlayerParty * party, int pos1, int pos2)
{
    struct Pokemon * buffer;
    GF_ASSERT(pos1 >= 0);
    GF_ASSERT(pos1 < party->curCount);
    GF_ASSERT(pos1 < party->maxCount);
    GF_ASSERT(pos2 >= 0);
    GF_ASSERT(pos2 < party->curCount);
    GF_ASSERT(pos2 < party->maxCount);
    buffer = AllocFromHeap(0, sizeof(struct Pokemon));
    *buffer = party->mons[pos1];
    party->mons[pos1] = party->mons[pos2];
    party->mons[pos2] = *buffer;
    FreeToHeap(buffer);
    return FALSE;
}

void FUN_0206BAD0(struct PlayerParty * src, struct PlayerParty * dest)
{
    *dest = *src;
}

BOOL PartyHasMon(struct PlayerParty * party, u16 species)
{
    int i;
    for (i = 0; i < party->curCount; i++)
    {
        if (species == GetMonData(&party->mons[i], MON_DATA_SPECIES, NULL))
            break;
    }
    return i != party->curCount;
}

struct PlayerParty * FUN_0206BB1C(void * ptr)
{
    return (struct PlayerParty *)SavArray_get(ptr, 2);
}
