#include "global.h"
#define IN_POKEMON_C
#include "pokemon.h"
#include "heap.h"
#include "MI_memory.h"

#pragma thumb on

void MonEncryptSegment(void * datap, u32 size, u32 key, ...);
void MonDecryptSegment(void * datap, u32 size, u32 key, ...);
u16 MonEncryptionLCRNG(u32 * seed);

#define ENCRY_ARGS_PTY(mon) &(mon)->party, sizeof((mon)->party), (mon)->box.pid
#define ENCRY_ARGS_BOX(boxmon) &(boxmon)->substructs, sizeof((boxmon)->substructs), (boxmon)->checksum
#define ENCRYPT_PTY(mon) MonEncryptSegment(ENCRY_ARGS_PTY(mon))
#define ENCRYPT_BOX(boxmon) MonEncryptSegment(ENCRY_ARGS_BOX(boxmon))
#define DECRYPT_PTY(mon) MonDecryptSegment(ENCRY_ARGS_PTY(mon))
#define DECRYPT_BOX(boxmon) MonDecryptSegment(ENCRY_ARGS_BOX(boxmon))

void ZeroMonData(struct Pokemon * pokemon)
{
    MIi_CpuClearFast(0, pokemon, sizeof(struct Pokemon));
    ENCRYPT_BOX(&pokemon->box);
    ENCRYPT_PTY(pokemon);
}

void ZeroBoxMonData(struct BoxPokemon * boxmon)
{
    MIi_CpuClearFast(0, boxmon, sizeof(struct BoxPokemon));
    ENCRYPT_BOX(boxmon);
}

u32 SizeOfStructPokemon(void)
{
    return sizeof(struct Pokemon);
}

struct Pokemon * AllocMonZeroed(u32 heap_id)
{
    struct Pokemon * pokemon = (struct Pokemon *)AllocFromHeap(heap_id, sizeof(struct Pokemon));
    ZeroMonData(pokemon);
    return pokemon;
}

BOOL TryDecryptMon(struct Pokemon * mon)
{
    BOOL ret = FALSE;

    if (!mon->box.no_encrypt)
    {
        ret = TRUE;
        GF_ASSERT(!mon->box.control_4_1);
        mon->box.no_encrypt = TRUE;
        mon->box.control_4_1 = TRUE;
        DECRYPT_PTY(mon);
        DECRYPT_BOX(&mon->box);
    }
    return ret;
}
