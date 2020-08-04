#ifndef POKEDIAMOND_PROTO_H
#define POKEDIAMOND_PROTO_H

// For homeless function declarations

#include "pokemon.h" // for struct definitions
#include "string16.h" // for struct definitions

void StringCopy(u16 * dest, struct String * src);
void String_dtor(void * ptr);
void FUN_02021E28(u16 * dest, u16 * src);
void FUN_02021EF0(const struct String * src, u16 * dest, u32 count);
u32 GetItemAttr(u16 item, u32 a1, u32 a2);
int FUN_02014C3C(u8);
void FUN_02014C54(int, int, struct UnkStruct_02069038 *, u8);
u32 IsNighttime(void); // is day or night
int FUN_02005F14(int);
void FUN_02005E80(int);
void FUN_02005E90(int, int, int, int);
void FUN_020056AC(int, int, int, int, int);
void FUN_020808AC(struct BoxPokemon *, int, int, int, int);
void * FUN_02022610(void *, int);
void FUN_0200B7B8(u32 *, struct String *, struct String *);

#endif //POKEDIAMOND_PROTO_H
