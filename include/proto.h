#ifndef POKEDIAMOND_PROTO_H
#define POKEDIAMOND_PROTO_H

// For homeless function declarations

#include "pokemon.h" // for struct definitions

u16 * FUN_0200AA50(u16 species, u32 heap_id);
void FUN_02021A74(u16 * dest, u16 * src);
void FUN_02021A20(void * ptr);
void FUN_02021E28(u16 * dest, u16 * src);
void FUN_02021EF0(const u16 * src, u16 * dest, u32 count);
u32 FUN_0206E7B8(u16 item, u32 a1, u32 a2);
int FUN_02014C3C(u8);
void FUN_02014C54(int, int, struct UnkStruct_02069038 *, u8);
u32 IsNighttime(void); // is day or night
int FUN_02005F14(int);
void FUN_02005E80(int);
void FUN_02005E90(int, int, int, int);
void FUN_020056AC(int, int, int, int, int);
void FUN_020808AC(struct BoxPokemon *, int, int, int, int);
void * FUN_02022610(void *, int);

#endif //POKEDIAMOND_PROTO_H
