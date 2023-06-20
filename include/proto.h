#ifndef POKEDIAMOND_PROTO_H
#define POKEDIAMOND_PROTO_H

// For homeless function declarations

#include "pokemon.h" // for struct definitions
#include "string16.h" // for struct definitions
#include "player_data.h" // for struct definitions

int TrainerClass_GetGenderOrTrainerCount(int x);
int FUN_02014C3C(u8);
void FUN_02014C54(int, int, struct UnkStruct_02069038 *, u8);
u32 IsNighttime(void); // is day or night
void FUN_020808AC(struct BoxPokemon *, PlayerProfile *, int, u32, u32);

#endif //POKEDIAMOND_PROTO_H
