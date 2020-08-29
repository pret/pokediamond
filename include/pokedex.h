#ifndef POKEDIAMOND_POKEDEX_H
#define POKEDIAMOND_POKEDEX_H

#include "global.h"

struct Pokedex
{
    /* 0x0000 */ u32 magic; // BEEFCAFE
    /* 0x0004 */ u8 field_0004[0x3C];
    /* 0x0040 */ u32 field_0040; // Deoxys forme plus top 13 dex flags
    /* 0x0044 */ u8 field_0044[0x3C];
    /* 0x0080 */ u32 field_0080; // Deoxys forme plus top 13 dex flags
    /* 0x0084 */ u8 field_0084[0x40]; // Genders
    /* 0x00C4 */ u8 field_00C4[0x40]; // Genders
    /* 0x0104 */ u32 field_0104; // spinda personality
    /* 0x0108 */ u8 field_0108[2]; // Shellos/Gastrodon
    /* 0x0108 */ u8 field_010A[2]; // Burmy/Wormadam
    /* 0x010C */ u8 field_010C[28]; // Unown
    /* 0x0128 */ u8 field_0128;
    /* 0x0129 */ u8 field_0129[14]; // Meister?
    /* 0x0137 */ u8 field_0137;
    /* 0x0138 */ u8 field_0138;
    /* 0x0139 */ u8 field_0139;
    /* 0x013A */ u8 padding_013A[2];
};

u32 Sav2_Pokedex_sizeof(void);
struct Pokedex * Sav2_Pokedex_new(u32 heap_id);
void Sav2_Pokedex_Copy(const struct Pokedex * src, struct Pokedex * dest);
s32 FUN_02023D8C(struct Pokedex * pokedex, u32 species);
BOOL FUN_02023DEC(struct Pokedex * pokedex, u32 species, u8 state);
void FUN_02023E70(struct Pokedex * pokedex, u32 species, u32 state);
s32 FUN_02023F2C(struct Pokedex * pokedex, u32 species);
BOOL FUN_02023F88(struct Pokedex * pokedex, u32 species, u8 state);
void FUN_02023FEC(struct Pokedex * pokedex, u32 species, s32 state);
void FUN_02024068(struct Pokedex * pokedex, u8 r4, u8 r6);
s32 FUN_020240D0(struct Pokedex * pokedex);
BOOL FUN_02024114(struct Pokedex * pokedex, u32 state);
void FUN_0202415C(struct Pokedex * pokedex, u16 species, struct Pokemon * pokemon);
void FUN_0202419C(struct Pokedex * pokedex);
void FUN_020241B8(struct Pokedex * pokedex, u16 species, struct Pokemon * pokemon);
void FUN_02024294(struct Pokedex * pokedex, u32 species, u32 language);
s32 FUN_020242C8(struct Pokedex * pokedex, u16 species, s32 r4);
BOOL FUN_02024340(u16 species);
BOOL FUN_02024364(u16 a0);
void Sav2_Pokedex_init(struct Pokedex * pokedex);
u16 FUN_020243C8(struct Pokedex * pokedex);
u16 FUN_02024404(struct Pokedex * pokedex);
u16 FUN_02024440(struct Pokedex * pokedex);
u16 FUN_0202445C(struct Pokedex * pokedex);
u16 FUN_020244A4(struct Pokedex * pokedex);
BOOL FUN_020244EC(struct Pokedex * pokedex);
BOOL FUN_02024504(struct Pokedex * pokedex);
u16 FUN_02024518(struct Pokedex * pokedex);
u16 FUN_02024550(struct Pokedex * pokedex);
BOOL FUN_02024594(struct Pokedex * pokedex, u16 species);
BOOL FUN_020245F0(struct Pokedex * pokedex, u16 species);
u32 FUN_02024648(struct Pokedex * pokedex, u32 a1);
s32 FUN_02024674(struct Pokedex * pokedex, u16 species, s32 r6);
s32 FUN_020246DC(struct Pokedex * pokedex, s32 a1);
s32 FUN_0202471C(struct Pokedex * pokedex);
BOOL FUN_02024748(struct Pokedex * pokedex, s32 a1);
s32 FUN_020247A4(struct Pokedex * pokedex);
BOOL FUN_020247C8(struct Pokedex * pokedex, s32 a1);
s32 FUN_02024828(struct Pokedex * pokedex);
s32 FUN_0202484C(struct Pokedex * pokedex, s32 a1);
s32 FUN_0202489C(struct Pokedex * pokedex);
s32 FUN_020248BC(struct Pokedex * pokedex, s32 a1);
s32 FUN_0202490C(struct Pokedex * pokedex);
s32 FUN_02024930(struct Pokedex * pokedex, s32 a1);
s32 FUN_02024970(struct Pokedex * pokedex);
void FUN_0202498C(struct Pokedex * pokedex, struct Pokemon * pokemon);
void FUN_02024AF0(struct Pokedex * pokedex, struct Pokemon * pokemon);
void Pokedex_SetNatDexFlag(struct Pokedex * pokedex);
BOOL Pokedex_GetNatDexFlag(struct Pokedex * pokedex);
BOOL FUN_02024CC4(struct Pokedex * pokedex);
void FUN_02024CE0(struct Pokedex * pokedex);
s32 FUN_02024D00(struct Pokedex * pokedex, u32 species, u32 language);
void FUN_02024D4C(struct Pokedex * pokedex);
BOOL FUN_02024D58(struct Pokedex * pokedex);
BOOL FUN_02024D64(struct Pokedex * pokedex);
void FUN_02024D80(struct Pokedex * pokedex);
struct Pokedex * FUN_02024DA0(struct SaveBlock2 * sav2);
s32 FUN_02024DAC(struct Pokedex * pokedex, s32 a1, u32 a2);

#endif //POKEDIAMOND_POKEDEX_H
