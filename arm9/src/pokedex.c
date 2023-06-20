#include "global.h"
#include "save.h"
#include "heap.h"
#include "MI_memory.h"
#include "pokemon.h"
#include "pokedex.h"
#include "unk_02087A1C.h"
#include "constants/species.h"

static inline BOOL CheckDexFlag(u8 * flagArray, u16 species)
{
    species--;
    return (flagArray[species >> 3] & (1 << (species & 7))) != 0;
}

static inline void UpdateDexFlag(u8 * flagArray, u16 species, u8 state)
{
    GF_ASSERT(state < 2);
    species--;
    flagArray[species >> 3] &= ~(1 << (species & 7));
    flagArray[species >> 3] |= (state << (species & 7));
}

static inline void SetDexFlag(u8 * flagArray, u16 species)
{
    species--;
    flagArray[species >> 3] |= (1 << (species & 7));
}

static inline s32 CheckDexFlagPair(u8 * flagArray, u16 offset)
{
    return (flagArray[offset >> 2] >> (2 * (offset & 3))) & 3;
}

static inline void UpdateDexFlagPair(u8 * flagArray, u16 offset, u8 state)
{
    GF_ASSERT(state < 4);
    flagArray[offset >> 2] &= ~(3 << (2 * (offset & 3)));
    flagArray[offset >> 2] |= (state << (2 * (offset & 3)));
}

u32 Save_Pokedex_sizeof(void)
{
    return sizeof(struct Pokedex);
}

struct Pokedex * Save_Pokedex_New(u32 heap_id)
{
    struct Pokedex * ret = (struct Pokedex *)AllocFromHeap(heap_id, sizeof(struct Pokedex));
    Save_Pokedex_Init(ret);
    return ret;
}

void Save_Pokedex_Copy(const struct Pokedex * src, struct Pokedex * dest)
{
    MI_CpuCopy8(src, dest, sizeof(struct Pokedex));
}

s32 Pokedex_CountSeenShellosOrGastrodon_Internal(struct Pokedex * pokedex, u32 species)
{
    GF_ASSERT(species == SPECIES_SHELLOS || species == SPECIES_GASTRODON);
    if (!Pokedex_CheckMonSeenFlag(pokedex, (u16)species))
        return 0;
    u8 *flags = species == SPECIES_SHELLOS ? &pokedex->shellosGastrodon[0] : &pokedex->shellosGastrodon[1];
    BOOL r2 = CheckDexFlag(flags, 1);
    BOOL r0 = CheckDexFlag(flags, 2);
    return (r2 == r0) ? 1 : 2;
}

BOOL Pokedex_HasSeenShellosOrGastrodonForme(struct Pokedex * pokedex, u32 species, u8 state)
{
    GF_ASSERT(species == SPECIES_SHELLOS || species == SPECIES_GASTRODON);
    if (!Pokedex_CheckMonSeenFlag(pokedex, (u16)species))
        return FALSE;
    u8 *flags = species == SPECIES_SHELLOS ? &pokedex->shellosGastrodon[0] : &pokedex->shellosGastrodon[1];
    u32 r0 = (u32)Pokedex_CountSeenShellosOrGastrodon_Internal(pokedex, species);
    for (int i = 0; i < r0; i++)
    {
        BOOL r2 = CheckDexFlag(flags, (u16)(i + 1));
        if (r2 == state)
            return TRUE;
    }
    return FALSE;
}

void Pokedex_SetSeenShellosOrGastrodonForme(struct Pokedex * pokedex, u32 species, u32 state)
{
    GF_ASSERT(species == SPECIES_SHELLOS || species == SPECIES_GASTRODON);
    if (Pokedex_HasSeenShellosOrGastrodonForme(pokedex, species, (u8)state))
        return;
    u8 *flags = species == SPECIES_SHELLOS ? &pokedex->shellosGastrodon[0] : &pokedex->shellosGastrodon[1];
    s32 r5 = Pokedex_CountSeenShellosOrGastrodon_Internal(pokedex, species);
    if (r5 < 2)
    {
        UpdateDexFlag(flags, (u16)(r5 + 1), (u8)state);
        if (r5 == 0)
        {
            UpdateDexFlag(flags, (u16)(r5 + 2), (u8)state);
        }
    }
}

s32 Pokedex_CountSeenBurmyOrWormadam_Internal(struct Pokedex * pokedex, u32 species)
{
    GF_ASSERT(species == SPECIES_BURMY || species == SPECIES_WORMADAM);
    if (!Pokedex_CheckMonSeenFlag(pokedex, (u16)species))
        return 0;
    u8 *flags = species == SPECIES_BURMY ? &pokedex->burmyWormadam[0] : &pokedex->burmyWormadam[1];
    s32 i;
    for (i = 0; i < 3; i++)
    {
        s32 r2 = CheckDexFlagPair(flags, (u16)i);
        if (r2 == 3)
            break;
    }
    return i;
}

BOOL Pokedex_HasSeenBurmyOrWormadamForme(struct Pokedex * pokedex, u32 species, u8 state)
{
    GF_ASSERT(species == SPECIES_BURMY || species == SPECIES_WORMADAM);
    if (!Pokedex_CheckMonSeenFlag(pokedex, (u16)species))
        return FALSE;
    u8 *flags = species == SPECIES_BURMY ? &pokedex->burmyWormadam[0] : &pokedex->burmyWormadam[1];
    s32 i;
    for (i = 0; i < 3; i++)
    {
        s32 r2 = CheckDexFlagPair(flags, (u16)i);
        if (r2 == state)
            return TRUE;
    }
    return FALSE;
}

void Pokedex_SetSeenBurmyOrWormadamForme(struct Pokedex * pokedex, u32 species, s32 state)
{
    GF_ASSERT(species == SPECIES_BURMY || species == SPECIES_WORMADAM);
    if (Pokedex_HasSeenBurmyOrWormadamForme(pokedex, species, (u8)state))
        return;
    u8 *flags = species == SPECIES_BURMY ? &pokedex->burmyWormadam[0] : &pokedex->burmyWormadam[1];
    s32 r5 = Pokedex_CountSeenBurmyOrWormadam_Internal(pokedex, species);
    if (r5 >= 3)
        return;
    UpdateDexFlagPair(flags, (u16)r5, (u8)state);
}

static inline void SetDeoxysFormeFlag(struct Pokedex * pokedex, u8 r4, u8 r6)
{
    GF_ASSERT(r6 < 4);
    GF_ASSERT(r4 <= 15);
    if (r6 < 2)
    {
        pokedex->caughtFlagsHi_Deoxys1 &= ~(15 << (24 + 4 * r6));
        pokedex->caughtFlagsHi_Deoxys1 |= r4 << (24 + 4 * r6);
    }
    else
    {
        r6 -= 2;
        pokedex->seenFlagsHi_Deoxys2 &= ~(15 << (24 + 4 * r6));
        pokedex->seenFlagsHi_Deoxys2 |= r4 << (24 + 4 * r6);
    }
}

void Pokedex_SetSeenDeoxysFormeAt(struct Pokedex * pokedex, u8 r4, u8 r6)
{
    SetDeoxysFormeFlag(pokedex, r4, r6);
}

static inline u32 GetDeoxysFormeFlag_Internal(struct Pokedex * pokedex, u8 r6)
{
    if (r6 < 2)
    {
        return (pokedex->caughtFlagsHi_Deoxys1 >> (24 + 4 * r6)) & 15;
    }
    else
    {
        r6 -= 2;
        return (pokedex->seenFlagsHi_Deoxys2 >> (24 + 4 * r6)) & 15;
    }
}

s32 Pokedex_CountSeenDeoxysFormes_Internal(struct Pokedex * pokedex)
{
    s32 i;
    for (i = 0; i < 4; i++)
    {
        u32 r2 = GetDeoxysFormeFlag_Internal(pokedex, (u8)i);
        if (r2 == 15)
            break;
    }
    return i;
}

BOOL Pokedex_HasSeenDeoxysForme(struct Pokedex * pokedex, u32 state)
{
    s32 i;
    for (i = 0; i < 4; i++)
    {
        u32 r4 = GetDeoxysFormeFlag_Internal(pokedex, (u8)i);
        if (state == r4)
            return TRUE;
    }
    return FALSE;
}

void Pokedex_TrySetSeenDeoxysForme(struct Pokedex * pokedex, u16 species, struct Pokemon * pokemon)
{
    u8 forme = (u8)GetMonData(pokemon, MON_DATA_FORME, NULL);
    if (species == SPECIES_DEOXYS && !Pokedex_HasSeenDeoxysForme(pokedex, forme))
    {
        s32 r2 = Pokedex_CountSeenDeoxysFormes_Internal(pokedex);
        Pokedex_SetSeenDeoxysFormeAt(pokedex, forme, (u8)r2);
    }
}

void Pokedex_InitSeenDeoxysFormesArray(struct Pokedex * pokedex)
{
    s32 i;
    for (i = 0; i < 4; i++)
    {
        Pokedex_SetSeenDeoxysFormeAt(pokedex, 15, (u8)i);
    }
}

static inline BOOL HasUnownLetterBeenSeen(struct Pokedex * pokedex, u8 letter)
{
    s32 i;
    u8 * arr;
    for (i = 0, arr = (u8 *)pokedex; i < 28; i++, arr++)
    {
        if (letter == *(arr + 0x10C))
            return TRUE;
    }
    return FALSE;
}

static inline s32 FindFirstAvailableUnownLetterSlot(struct Pokedex * pokedex)
{
    s32 i;
    u8 * arr;
    for (i = 0, arr = (u8 *)pokedex; i < 28; i++, arr++)
    {
        if (*(arr + 0x10C) == 0xFF)
            break;
    }
    return i;
}

static inline void SetSeenUnownLetter(struct Pokedex * pokedex, u32 species, s32 letter)
{
#pragma unused(species)
    s32 idx;
    if (HasUnownLetterBeenSeen(pokedex, (u8)letter))
        return;
    idx = FindFirstAvailableUnownLetterSlot(pokedex);
    if (idx >= 28)
        return;
    pokedex->seenUnown[idx] = (u8)letter;
}

void Pokedex_SetMonSeenForme(struct Pokedex * pokedex, u16 species, struct Pokemon * pokemon)
{
    if (species == SPECIES_UNOWN)
    {
        SetSeenUnownLetter(pokedex, species, GetMonUnownLetter(pokemon));
    }
    else if (species == SPECIES_BURMY)
    {
        Pokedex_SetSeenBurmyOrWormadamForme(pokedex, species, (s32)GetMonData(pokemon, MON_DATA_FORME, NULL));
    }
    else if (species == SPECIES_WORMADAM)
    {
        Pokedex_SetSeenBurmyOrWormadamForme(pokedex, species, (s32)GetMonData(pokemon, MON_DATA_FORME, NULL));
    }
    else if (species == SPECIES_SHELLOS)
    {
        Pokedex_SetSeenShellosOrGastrodonForme(pokedex, species, GetMonData(pokemon, MON_DATA_FORME, NULL));
    }
    else if (species == SPECIES_GASTRODON)
    {
        Pokedex_SetSeenShellosOrGastrodonForme(pokedex, species, GetMonData(pokemon, MON_DATA_FORME, NULL));
    }
    else if (species == SPECIES_DEOXYS)
    {
        Pokedex_TrySetSeenDeoxysForme(pokedex, species, pokemon);
    }
}

void Pokedex_SetMeisterFlagBySpeciesAndLanguage(struct Pokedex * pokedex, u32 species, u32 language)
{
    s32 r4 = GetMeisterSpeciesIdx(species);
    s32 r0 = GetMeisterLanguageIdx(language);
    if (r4 != 14 && r0 != 6)
    {
        pokedex->meister[r4] |= (1 << r0);
    }
}

s32 FUN_020242C8(struct Pokedex * pokedex, u16 species, s32 r4)
{
    u8 r0;
    u8 r1;
    if (GetMonBaseStat(species, BASE_GENDER_RATIO) == MON_RATIO_UNKNOWN)
    {
        return r4 == 0 ? 2 : -1;
    }
    r1 = (u8)CheckDexFlag(pokedex->field_0084, species);
    if (r4 == 1)
    {
        r0 = (u8)CheckDexFlag(pokedex->field_00C4, species);
        if (r0 == r1)
            return -1;
        else
            return r0;
    }
    return r1;
}

BOOL Pokedex_SpeciesIsNotMythical(u16 species)
{
    static const u16 sSinnohDexMythicalMons[] = {
        SPECIES_MANAPHY
    };

    static const u16 sNationalDexMythicalMons[] = {
        SPECIES_MEW,
        SPECIES_LUGIA,
        SPECIES_HO_OH,
        SPECIES_CELEBI,
        SPECIES_JIRACHI,
        SPECIES_DEOXYS,
        SPECIES_PHIONE,
        SPECIES_MANAPHY,
        SPECIES_DARKRAI,
        SPECIES_SHAYMIN,
        SPECIES_ARCEUS
    };

    s32 i;
    BOOL ret = TRUE;
    for (i = 0; i < (s32)NELEMS(sNationalDexMythicalMons); i++)
    {
        if (species == sNationalDexMythicalMons[i])
            ret = FALSE;
    }
    return ret;
}

BOOL Pokedex_SpeciesIsNotSinnohMythical(u16 species)
{
    BOOL ret = TRUE;
    if (species == SPECIES_MANAPHY)
        ret = FALSE;
    return ret;
}

void Save_Pokedex_Init(struct Pokedex * pokedex)
{
    memset(pokedex, 0, sizeof(struct Pokedex));
    pokedex->magic = 0xBEEFCAFE;
    pokedex->unlockedNationalDex = 0;
    memset(pokedex->seenUnown, 0xFF, 28);
    pokedex->shellosGastrodon[0] = 0xFF;
    pokedex->shellosGastrodon[1] = 0xFF;
    pokedex->burmyWormadam[0] = 0xFF;
    pokedex->burmyWormadam[1] = 0xFF;
    Pokedex_InitSeenDeoxysFormesArray(pokedex);
}

u16 Pokedex_CountNationalDexOwned(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 i;
    s32 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (Pokedex_CheckMonCaughtFlag(pokedex, (u16)i) == TRUE)
            count++;
    }
    return (u16)count;
}

u16 Pokedex_CountNationalDexSeen(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 i;
    s32 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (Pokedex_CheckMonSeenFlag(pokedex, (u16)i) == TRUE)
            count++;
    }
    return (u16)count;
}

u16 Pokedex_CountSeenMons(struct Pokedex * pokedex)
{
    if (Pokedex_GetNatDexFlag(pokedex))
        return Pokedex_CountNationalDexSeen(pokedex);
    else
        return Pokedex_CountSinnohDexSeen(pokedex);
}

u16 Pokedex_CountSinnohDexOwned(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 i;
    s32 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (Pokedex_CheckMonCaughtFlag(pokedex, (u16)i) == TRUE && SpeciesToSinnohDexNo((u16)i) != 0)
            count++;
    }
    return (u16)count;
}

u16 Pokedex_CountSinnohDexSeen(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 i;
    s32 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (Pokedex_CheckMonSeenFlag(pokedex, (u16)i) == TRUE && SpeciesToSinnohDexNo((u16)i) != 0)
            count++;
    }
    return (u16)count;
}

BOOL Pokedex_HasCompletedNationalDex(struct Pokedex * pokedex)
{
    return Pokedex_CountNationalDexOwned_OmitMythicals(pokedex) >= 482;
}

BOOL Pokedex_HasCompletedSinnohDex(struct Pokedex * pokedex)
{
    return Pokedex_CountSinnohDexSeen_OmitMythicals(pokedex) >= 150;
}

u16 Pokedex_CountNationalDexOwned_OmitMythicals(struct Pokedex * pokedex)
{
    s32 i;
    u16 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (Pokedex_CheckMonCaughtFlag(pokedex, (u16)i) == TRUE && Pokedex_SpeciesIsNotMythical((u16)i) == TRUE)
            count++;
    }
    return count;
}

u16 Pokedex_CountSinnohDexSeen_OmitMythicals(struct Pokedex * pokedex)
{
    s32 i;
    u16 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (Pokedex_CheckMonSeenFlag(pokedex, (u16)i) == TRUE && SpeciesToSinnohDexNo((u16)i) != 0 && Pokedex_SpeciesIsNotSinnohMythical((u16)i) == TRUE)
            count++;
    }
    return count;
}

static inline BOOL DexSpeciesIsInvalid(u16 species)
{
    if (species == SPECIES_NONE || species > NATIONAL_DEX_COUNT)
    {
        GF_ASSERT(0);
        return TRUE;
    }
    return FALSE;
}

BOOL Pokedex_CheckMonCaughtFlag(struct Pokedex * pokedex, u16 species)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (DexSpeciesIsInvalid(species))
        return FALSE;
    if (!CheckDexFlag(pokedex->caughtFlags, species) || !CheckDexFlag(pokedex->seenFlags, species))
        return FALSE;
    return TRUE;
}

BOOL Pokedex_CheckMonSeenFlag(struct Pokedex * pokedex, u16 species)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (DexSpeciesIsInvalid(species))
        return FALSE;
    return CheckDexFlag(pokedex->seenFlags, species);
}

u32 Pokedex_GetSeenSpindaPersonality(struct Pokedex * pokedex, u32 a1)
{
    u32 r6;
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (a1 == 0)
        r6 = (u32)pokedex->spindaPersonality;
    else
        GF_ASSERT(0); // r6 is not initialized because execution should halt here
    return r6;
}

s32 FUN_02024674(struct Pokedex * pokedex, u16 species, s32 r6)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (DexSpeciesIsInvalid(species))
        return -1;
    if (CheckDexFlag(pokedex->seenFlags, species))
        return FUN_020242C8(pokedex, species, r6);
    else
        return -1;
}

static inline s32 FindFirstAvailableUnownLetterSlot_2(struct Pokedex * pokedex)
{
    s32 i;
    for (i = 0; i < 28; i++)
    {
        if (pokedex->seenUnown[i] == 0xFF)
            break;
    }
    return i;
}

s32 Pokedex_GetSeenUnownI(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 i;
    i = FindFirstAvailableUnownLetterSlot_2(pokedex);
    if (i <= a1)
        return -1;
    return pokedex->seenUnown[a1];
}

s32 Pokedex_CountSeenUnown(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return FindFirstAvailableUnownLetterSlot_2(pokedex);
}

BOOL Pokedex_GetSeenShellosForme(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (Pokedex_CountSeenShellosOrGastrodon_Internal(pokedex, SPECIES_SHELLOS) <= a1)
        return -1;
    GF_ASSERT(a1 < 2);
    return CheckDexFlag(&pokedex->shellosGastrodon[0], (u16)(a1 + 1));
}

s32 Pokedex_CountSeenShellos(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return Pokedex_CountSeenShellosOrGastrodon_Internal(pokedex, SPECIES_SHELLOS);
}

BOOL Pokedex_GetSeenGastrodonForme(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (Pokedex_CountSeenShellosOrGastrodon_Internal(pokedex, SPECIES_GASTRODON) <= a1)
        return -1;
    GF_ASSERT(a1 < 2);
    return CheckDexFlag(&pokedex->shellosGastrodon[1], (u16)(a1 + 1));
}

s32 Pokedex_CountSeenGastrodon(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return Pokedex_CountSeenShellosOrGastrodon_Internal(pokedex, SPECIES_GASTRODON);
}

s32 Pokedex_GetSeenBurmyForme(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (Pokedex_CountSeenBurmyOrWormadam_Internal(pokedex, SPECIES_BURMY) <= a1)
        return -1;
    GF_ASSERT(a1 < 3);
    return CheckDexFlagPair(&pokedex->burmyWormadam[0], (u16)a1);
}

s32 Pokedex_CountSeenBurmy(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return Pokedex_CountSeenBurmyOrWormadam_Internal(pokedex, SPECIES_BURMY);
}

s32 Pokedex_GetSeenWormadamForme(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (Pokedex_CountSeenBurmyOrWormadam_Internal(pokedex, SPECIES_WORMADAM) <= a1)
        return -1;
    GF_ASSERT(a1 < 3);
    return CheckDexFlagPair(&pokedex->burmyWormadam[1], (u16)a1);
}

s32 Pokedex_CountSeenWormadam(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return Pokedex_CountSeenBurmyOrWormadam_Internal(pokedex, SPECIES_WORMADAM);
}

s32 Pokedex_GetSeenDeoxysForme(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return (s32)GetDeoxysFormeFlag_Internal(pokedex, (u8)a1);
}

s32 Pokedex_CountSeenDeoxys(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return Pokedex_CountSeenDeoxysFormes_Internal(pokedex);
}

static inline void SetSeenCaughtGender(struct Pokedex * pokedex, u16 species, u8 gender)
{
    GF_ASSERT(gender <= 2);
    if (gender == 2)
        gender = 0;
    UpdateDexFlag(pokedex->field_00C4, species, gender);
    UpdateDexFlag(pokedex->field_0084, species, gender);
}

static inline void SetSeenGender(struct Pokedex * pokedex, u16 species, u8 gender)
{
    GF_ASSERT(gender <= 2);
    if (gender == 2)
        gender = 0;
    UpdateDexFlag(pokedex->field_00C4, species, gender);
}

void Pokedex_SetMonSeenFlag(struct Pokedex * pokedex, struct Pokemon * pokemon)
{
    u16 species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, NULL);
    u32 personality = GetMonData(pokemon, MON_DATA_PERSONALITY, NULL);
    u32 gender = GetMonGender(pokemon);
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (DexSpeciesIsInvalid(species))
        return;
    if (!CheckDexFlag(pokedex->seenFlags, species))
    {
        if (species == SPECIES_SPINDA)
            pokedex->spindaPersonality = personality;
        SetSeenCaughtGender(pokedex, species, (u8)gender);
    }
    else
    {
        u8 seen_gender = (u8)CheckDexFlag(pokedex->field_0084, species);
        if (seen_gender != gender)
        {
            SetSeenGender(pokedex, species, (u8)gender);
        }
    }
    Pokedex_SetMonSeenForme(pokedex, species, pokemon);
    SetDexFlag(pokedex->seenFlags, species);
}

void Pokedex_SetMonCaughtFlag(struct Pokedex * pokedex, struct Pokemon * pokemon)
{
    u32 language; // sp08
    u32 personality; // sp04
    u32 gender; // r7
    u16 species; // r6

    species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, NULL);
    language = GetMonData(pokemon, MON_DATA_GAME_LANGUAGE, NULL);
    personality = GetMonData(pokemon, MON_DATA_PERSONALITY, NULL);
    gender = GetMonGender(pokemon);
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (DexSpeciesIsInvalid(species))
        return;
    if (!CheckDexFlag(pokedex->seenFlags, species))
    {
        if (species == SPECIES_SPINDA)
            pokedex->spindaPersonality = personality;
        SetSeenCaughtGender(pokedex, species, (u8)gender);
    }
    else
    {
        u8 seen_gender = (u8)CheckDexFlag(pokedex->field_0084, species);
        if (seen_gender != gender)
        {
            SetSeenGender(pokedex, species, (u8)gender);
        }
    }
    Pokedex_SetMonSeenForme(pokedex, species, pokemon);
    Pokedex_SetMeisterFlagBySpeciesAndLanguage(pokedex, species, language);
    SetDexFlag(pokedex->caughtFlags, species);
    SetDexFlag(pokedex->seenFlags, species);
}

void Pokedex_SetNatDexFlag(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    pokedex->unlockedNationalDex = 1;
}

BOOL Pokedex_GetNatDexFlag(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return pokedex->unlockedNationalDex;
}

BOOL FUN_02024CC4(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return pokedex->field_0128;
}

void FUN_02024CE0(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    pokedex->field_0128 = 1;
}

s32 Pokedex_GetMeisterFlagBySpeciesAndLanguage(struct Pokedex * pokedex, u32 species, u32 language)
{
    GF_ASSERT(language < 8);
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 r5 = GetMeisterSpeciesIdx(species);
    if (r5 == 14)
        return 0;
    s32 r0 = GetMeisterLanguageIdx(language);
    return pokedex->meister[r5] & (1 << r0);
}

void FUN_02024D4C(struct Pokedex * pokedex)
{
    pokedex->field_0137 = 1;
}

BOOL FUN_02024D58(struct Pokedex * pokedex)
{
    return pokedex->field_0137;
}

BOOL Pokedex_GetSinnohDexFlag(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return pokedex->unlockedSinnohDex;
}

void Pokedex_SetSinnohDexFlag(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    pokedex->unlockedSinnohDex = 1;
}

struct Pokedex * Save_Pokedex_Get(struct SaveData * save)
{
    return (struct Pokedex *)SaveArray_Get(save, 7);
}

s32 Pokedex_GetSeenMonForme(struct Pokedex * pokedex, s32 species, u32 forme)
{
    switch (species)
    {
    case SPECIES_UNOWN:
        if (forme < Pokedex_CountSeenUnown(pokedex))
            return Pokedex_GetSeenUnownI(pokedex, (s32)forme);
        break;
    case SPECIES_SHELLOS:
        if (forme < Pokedex_CountSeenShellos(pokedex))
            return Pokedex_GetSeenShellosForme(pokedex, (s32)forme);
        break;
    case SPECIES_GASTRODON:
        if (forme < Pokedex_CountSeenGastrodon(pokedex))
            return Pokedex_GetSeenGastrodonForme(pokedex, (s32)forme);
        break;
    case SPECIES_BURMY:
        if (forme < Pokedex_CountSeenBurmy(pokedex))
            return Pokedex_GetSeenBurmyForme(pokedex, (s32)forme);
        break;
    case SPECIES_WORMADAM:
        if (forme < Pokedex_CountSeenWormadam(pokedex))
            return Pokedex_GetSeenWormadamForme(pokedex, (s32)forme);
        break;
    case SPECIES_DEOXYS:
        if (forme < Pokedex_CountSeenDeoxys(pokedex))
            return Pokedex_GetSeenDeoxysForme(pokedex, (s32)forme);
        break;
    }
    return 0;
}
