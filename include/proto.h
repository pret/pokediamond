#ifndef POKEDIAMOND_PROTO_H
#define POKEDIAMOND_PROTO_H

// For homeless function declarations

// Declare these here so that we don't have to include pokemon.h
struct UnkStruct_02069038;
struct PlayerParty;
struct BoxPokemon;
struct SaveBlock2;
struct String
{
    u16 len;
    u16 pos;
    u32 magic;
    u16 unk8;
    u16 data[0];
};

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

struct String * FUN_020239A0(struct SaveBlock2 *, u32 heap_id);
u32 FUN_020239BC(struct SaveBlock2 *);
u32 FUN_020239CC(struct SaveBlock2 *);
struct String * FUN_020219F4(u32 count, u32 heap_id);
int FUN_02021CE0(struct String *, struct String *);
int FUN_0206AE00(int x);

#endif //POKEDIAMOND_PROTO_H
