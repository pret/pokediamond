#ifndef POKEDIAMOND_PROTO_H
#define POKEDIAMOND_PROTO_H

// For homeless function declarations

// Declare these here so that we don't have to include pokemon.h
struct UnkStruct_02069038;
struct PlayerParty;

u16 * FUN_0200AA50(u16 species, u32 heap_id);
void FUN_02021A74(u16 * dest, u16 * src);
void FUN_02021A20(void * ptr);
void FUN_02021E28(u16 * dest, u16 * src);
void FUN_02021EF0(const u16 * src, u16 * dest, u32 count);
u32 FUN_0206E7B8(u16 item, u32 a1, u32 a2);
u32 GetArceusTypeByPlate(u16 plate);
int FUN_02014C3C(u8);
void FUN_02014C54(int, int, struct UnkStruct_02069038 *, u8);
u32 IsNighttime(void); // is day or night

#endif //POKEDIAMOND_PROTO_H
