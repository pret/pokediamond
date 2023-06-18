#ifndef POKEDIAMOND_POKEDEX_H
#define POKEDIAMOND_POKEDEX_H

#include "global.h"
#include "pokemon.h"
#include "save.h"

struct Pokedex
{
    /* 0x0000 */ u32 magic; // BEEFCAFE
    /* 0x0004 */ u8 caughtFlags[0x3C];
    /* 0x0040 */ u32 caughtFlagsHi_Deoxys1; // Deoxys forme plus top 13 dex flags
    /* 0x0044 */ u8 seenFlags[0x3C];
    /* 0x0080 */ u32 seenFlagsHi_Deoxys2; // Deoxys forme plus top 13 dex flags
    /* 0x0084 */ u8 field_0084[0x40]; // Genders
    /* 0x00C4 */ u8 field_00C4[0x40]; // Genders
    /* 0x0104 */ u32 spindaPersonality; // spinda personality
    /* 0x0108 */ u8 shellosGastrodon[2]; // Shellos/Gastrodon
    /* 0x0108 */ u8 burmyWormadam[2]; // Burmy/Wormadam
    /* 0x010C */ u8 seenUnown[28]; // Unown
    /* 0x0128 */ u8 field_0128;
    /* 0x0129 */ u8 meister[14]; // Meister?
    /* 0x0137 */ u8 field_0137;
    /* 0x0138 */ u8 unlockedSinnohDex;
    /* 0x0139 */ u8 unlockedNationalDex;
    /* 0x013A */ u8 padding_013A[2];
};

u32 Save_Pokedex_sizeof(void);
struct Pokedex * Save_Pokedex_New(u32 heap_id);
void Save_Pokedex_Copy(const struct Pokedex * src, struct Pokedex * dest);
s32 Pokedex_CountSeenShellosOrGastrodon_Internal(struct Pokedex * pokedex, u32 species);
BOOL Pokedex_HasSeenShellosOrGastrodonForme(struct Pokedex * pokedex, u32 species, u8 state);
void Pokedex_SetSeenShellosOrGastrodonForme(struct Pokedex * pokedex, u32 species, u32 state);
s32 Pokedex_CountSeenBurmyOrWormadam_Internal(struct Pokedex * pokedex, u32 species);
BOOL Pokedex_HasSeenBurmyOrWormadamForme(struct Pokedex * pokedex, u32 species, u8 state);
void Pokedex_SetSeenBurmyOrWormadamForme(struct Pokedex * pokedex, u32 species, s32 state);
void Pokedex_SetSeenDeoxysFormeAt(struct Pokedex * pokedex, u8 r4, u8 r6);
s32 Pokedex_CountSeenDeoxysFormes_Internal(struct Pokedex * pokedex);
BOOL Pokedex_HasSeenDeoxysForme(struct Pokedex * pokedex, u32 state);
void Pokedex_TrySetSeenDeoxysForme(struct Pokedex * pokedex, u16 species, struct Pokemon * pokemon);
void Pokedex_InitSeenDeoxysFormesArray(struct Pokedex * pokedex);
void Pokedex_SetMonSeenForme(struct Pokedex * pokedex, u16 species, struct Pokemon * pokemon);
void Pokedex_SetMeisterFlagBySpeciesAndLanguage(struct Pokedex * pokedex, u32 species, u32 language);
s32 FUN_020242C8(struct Pokedex * pokedex, u16 species, s32 r4);
BOOL Pokedex_SpeciesIsNotMythical(u16 species);
BOOL Pokedex_SpeciesIsNotSinnohMythical(u16 species);
void Save_Pokedex_Init(struct Pokedex * pokedex);
u16 Pokedex_CountNationalDexCaughtMons(struct Pokedex * pokedex);
u16 Pokedex_CountNationalDexSeenMons(struct Pokedex * pokedex);
u16 Pokedex_CountSeenMons(struct Pokedex * pokedex);
u16 Pokedex_CountSinnohDexCaughtMons(struct Pokedex * pokedex);
u16 Pokedex_CountSinnohDexSeenMons(struct Pokedex * pokedex);
BOOL Pokedex_HasCompletedNationalDex(struct Pokedex * pokedex);
BOOL Pokedex_HasCompletedSinnohDex(struct Pokedex * pokedex);
u16 Pokedex_CountNationalDexCaughtMons_OmitMythicals(struct Pokedex * pokedex);
u16 Pokedex_CountSinnohDexSeenMons_OmitMythicals(struct Pokedex * pokedex);
BOOL Pokedex_CheckMonCaughtFlag(struct Pokedex * pokedex, u16 species);
BOOL Pokedex_CheckMonSeenFlag(struct Pokedex * pokedex, u16 species);
u32 Pokedex_GetSeenSpindaPersonality(struct Pokedex * pokedex, u32 a1);
s32 FUN_02024674(struct Pokedex * pokedex, u16 species, s32 r6);
s32 Pokedex_GetSeenUnownI(struct Pokedex * pokedex, s32 a1);
s32 Pokedex_CountSeenUnown(struct Pokedex * pokedex);
BOOL Pokedex_GetSeenShellosForme(struct Pokedex * pokedex, s32 a1);
s32 Pokedex_CountSeenShellos(struct Pokedex * pokedex);
BOOL Pokedex_GetSeenGastrodonForme(struct Pokedex * pokedex, s32 a1);
s32 Pokedex_CountSeenGastrodon(struct Pokedex * pokedex);
s32 Pokedex_GetSeenBurmyForme(struct Pokedex * pokedex, s32 a1);
s32 Pokedex_CountSeenBurmy(struct Pokedex * pokedex);
s32 Pokedex_GetSeenWormadamForme(struct Pokedex * pokedex, s32 a1);
s32 Pokedex_CountSeenWormadam(struct Pokedex * pokedex);
s32 Pokedex_GetSeenDeoxysForme(struct Pokedex * pokedex, s32 a1);
s32 Pokedex_CountSeenDeoxys(struct Pokedex * pokedex);
void Pokedex_SetMonSeenFlag(struct Pokedex * pokedex, struct Pokemon * pokemon);
void Pokedex_SetMonCaughtFlag(struct Pokedex * pokedex, struct Pokemon * pokemon);
void Pokedex_SetNatDexFlag(struct Pokedex * pokedex);
BOOL Pokedex_GetNatDexFlag(struct Pokedex * pokedex);
BOOL FUN_02024CC4(struct Pokedex * pokedex);
void FUN_02024CE0(struct Pokedex * pokedex);
s32 Pokedex_GetMeisterFlagBySpeciesAndLanguage(struct Pokedex * pokedex, u32 species, u32 language);
void FUN_02024D4C(struct Pokedex * pokedex);
BOOL FUN_02024D58(struct Pokedex * pokedex);
BOOL Pokedex_GetSinnohDexFlag(struct Pokedex * pokedex);
void Pokedex_SetSinnohDexFlag(struct Pokedex * pokedex);
struct Pokedex * Save_Pokedex_Get(struct SaveData * save);
s32 Pokedex_GetSeenMonForme(struct Pokedex * pokedex, s32 a1, u32 a2);

#endif //POKEDIAMOND_POKEDEX_H
