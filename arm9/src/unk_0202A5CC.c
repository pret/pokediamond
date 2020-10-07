#include "global.h"
#include "pokemon.h"
#include "proto.h"

#pragma thumb on

// Prototypes from other files
void FUN_02013960(void *arg0, u32 arg1);

struct Unk0202A5CC
{
    u32 b0;
    u32 b4;
};

// Prototypes for this file
void FUN_0202A5CC(struct Unk0202A5CC *unk, u32 arg1);
u32 FUN_0202A5D0(struct Unk0202A5CC *unk);
void FUN_0202A5D4(void *arg0, u32 arg1, u32 arg2);
void *FUN_0202A5F4(void *arg0, u32 arg1);

void FUN_0202A5CC(struct Unk0202A5CC *unk, u32 arg1)
{
    unk->b4 = arg1;
}

u32 FUN_0202A5D0(struct Unk0202A5CC *unk)
{
    return unk->b4;
}

void FUN_0202A5D4(void *arg0, u32 arg1, u32 arg2)
{
    void *ptr = FUN_02022610(arg0, 23);
    ptr += 0x69 * 4;
    ptr += arg1 * 8;
    FUN_02013960(ptr, arg2);

    // Seems to be something like this:
    // struct PlayerParty * ptr = FUN_02022610(arg0, 23);
    // FUN_02013960(ptr->mons[1].party.seal_something.filler_00[10+arg1], arg2);
}

void *FUN_0202A5F4(void *arg0, u32 arg1)
{
    void *ptr = FUN_02022610(arg0, 23);
    ptr += 0x69 * 4;
    ptr += arg1 * 8;
    return ptr;
}
