#include "global.h"
#include "save_block_2.h"
#include "heap.h"
#include "MI_memory.h"
#include "pokemon.h"
#include "pokedex.h"
#include "unk_02087A1C.h"
#include "constants/species.h"

#pragma thumb on

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

u32 Sav2_Pokedex_sizeof(void)
{
    return sizeof(struct Pokedex);
}

struct Pokedex * Sav2_Pokedex_new(u32 heap_id)
{
    struct Pokedex * ret = (struct Pokedex *)AllocFromHeap(heap_id, sizeof(struct Pokedex));
    Sav2_Pokedex_init(ret);
    return ret;
}

void Sav2_Pokedex_Copy(const struct Pokedex * src, struct Pokedex * dest)
{
    MI_CpuCopy8(src, dest, sizeof(struct Pokedex));
}

s32 FUN_02023D8C(struct Pokedex * pokedex, u32 species)
{
    GF_ASSERT(species == SPECIES_SHELLOS || species == SPECIES_GASTRODON);
    if (!FUN_020245F0(pokedex, (u16)species))
        return 0;
    u8 *flags = species == SPECIES_SHELLOS ? &pokedex->field_0108[0] : &pokedex->field_0108[1];
    BOOL r2 = CheckDexFlag(flags, 1);
    BOOL r0 = CheckDexFlag(flags, 2);
    return (r2 == r0) ? 1 : 2;
}

BOOL FUN_02023DEC(struct Pokedex * pokedex, u32 species, u8 state)
{
    GF_ASSERT(species == SPECIES_SHELLOS || species == SPECIES_GASTRODON);
    if (!FUN_020245F0(pokedex, (u16)species))
        return FALSE;
    u8 *flags = species == SPECIES_SHELLOS ? &pokedex->field_0108[0] : &pokedex->field_0108[1];
    u32 r0 = (u32)FUN_02023D8C(pokedex, species);
    for (int i = 0; i < r0; i++)
    {
        BOOL r2 = CheckDexFlag(flags, (u16)(i + 1));
        if (r2 == state)
            return TRUE;
    }
    return FALSE;
}

void FUN_02023E70(struct Pokedex * pokedex, u32 species, u32 state)
{
    GF_ASSERT(species == SPECIES_SHELLOS || species == SPECIES_GASTRODON);
    if (FUN_02023DEC(pokedex, species, (u8)state))
        return;
    u8 *flags = species == SPECIES_SHELLOS ? &pokedex->field_0108[0] : &pokedex->field_0108[1];
    s32 r5 = FUN_02023D8C(pokedex, species);
    if (r5 < 2)
    {
        UpdateDexFlag(flags, (u16)(r5 + 1), (u8)state);
        if (r5 == 0)
        {
            UpdateDexFlag(flags, (u16)(r5 + 2), (u8)state);
        }
    }
}

s32 FUN_02023F2C(struct Pokedex * pokedex, u32 species)
{
    GF_ASSERT(species == SPECIES_BURMY || species == SPECIES_WORMADAM);
    if (!FUN_020245F0(pokedex, (u16)species))
        return 0;
    u8 *flags = species == SPECIES_BURMY ? &pokedex->field_010A[0] : &pokedex->field_010A[1];
    s32 i;
    for (i = 0; i < 3; i++)
    {
        s32 r2 = CheckDexFlagPair(flags, (u16)i);
        if (r2 == 3)
            break;
    }
    return i;
}

BOOL FUN_02023F88(struct Pokedex * pokedex, u32 species, u8 state)
{
    GF_ASSERT(species == SPECIES_BURMY || species == SPECIES_WORMADAM);
    if (!FUN_020245F0(pokedex, (u16)species))
        return FALSE;
    u8 *flags = species == SPECIES_BURMY ? &pokedex->field_010A[0] : &pokedex->field_010A[1];
    s32 i;
    for (i = 0; i < 3; i++)
    {
        s32 r2 = CheckDexFlagPair(flags, (u16)i);
        if (r2 == state)
            return TRUE;
    }
    return FALSE;
}

void FUN_02023FEC(struct Pokedex * pokedex, u32 species, s32 state)
{
    GF_ASSERT(species == SPECIES_BURMY || species == SPECIES_WORMADAM);
    if (FUN_02023F88(pokedex, species, (u8)state))
        return;
    u8 *flags = species == SPECIES_BURMY ? &pokedex->field_010A[0] : &pokedex->field_010A[1];
    s32 r5 = FUN_02023F2C(pokedex, species);
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
        pokedex->field_0040 &= ~(15 << (24 + 4 * r6));
        pokedex->field_0040 |= r4 << (24 + 4 * r6);
    }
    else
    {
        r6 -= 2;
        pokedex->field_0080 &= ~(15 << (24 + 4 * r6));
        pokedex->field_0080 |= r4 << (24 + 4 * r6);
    }
}

void FUN_02024068(struct Pokedex * pokedex, u8 r4, u8 r6)
{
    SetDeoxysFormeFlag(pokedex, r4, r6);
}

static inline u32 GetDeoxysFormeFlag(struct Pokedex * pokedex, u8 r6)
{
    if (r6 < 2)
    {
        return (pokedex->field_0040 >> (24 + 4 * r6)) & 15;
    }
    else
    {
        r6 -= 2;
        return (pokedex->field_0080 >> (24 + 4 * r6)) & 15;
    }
}

s32 FUN_020240D0(struct Pokedex * pokedex)
{
    s32 i;
    for (i = 0; i < 4; i++)
    {
        u32 r2 = GetDeoxysFormeFlag(pokedex, (u8)i);
        if (r2 == 15)
            break;
    }
    return i;
}

BOOL FUN_02024114(struct Pokedex * pokedex, u32 state)
{
    s32 i;
    for (i = 0; i < 4; i++)
    {
        u32 r4 = GetDeoxysFormeFlag(pokedex, (u8)i);
        if (state == r4)
            return TRUE;
    }
    return FALSE;
}

void FUN_0202415C(struct Pokedex * pokedex, u16 species, struct Pokemon * pokemon)
{
    u8 forme = (u8)GetMonData(pokemon, MON_DATA_FORME, NULL);
    if (species == SPECIES_DEOXYS && !FUN_02024114(pokedex, forme))
    {
        s32 r2 = FUN_020240D0(pokedex);
        FUN_02024068(pokedex, forme, (u8)r2);
    }
}

void FUN_0202419C(struct Pokedex * pokedex)
{
    s32 i;
    for (i = 0; i < 4; i++)
    {
        FUN_02024068(pokedex, 15, (u8)i);
    }
}

static inline BOOL HasUnownLetterBeenSeen(struct Pokedex * pokedex, u8 letter)
{
    u8 * arr;
    s32 i;
    for (i = 0, arr = (u8 *)pokedex; i < 28; i++, arr++)
    {
        u8 val = arr[0x010C];
        if (letter == val)
            return TRUE;
    }
    return FALSE;
}

static inline s32 FindFirstAvailableUnownLetterSlot(struct Pokedex * pokedex)
{
    u8 * arr;
    s32 i;
    for (i = 0, arr = (u8 *)pokedex; i < 28; i++, arr++)
    {
        u8 val = arr[0x010C];
        if (val == 0xFF)
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
    pokedex->field_010C[idx] = (u8)letter;
}

void FUN_020241B8(struct Pokedex * pokedex, u16 species, struct Pokemon * pokemon)
{
    if (species == SPECIES_UNOWN)
    {
        SetSeenUnownLetter(pokedex, species, GetMonUnownLetter(pokemon));
    }
    else if (species == SPECIES_BURMY)
    {
        FUN_02023FEC(pokedex, species, (s32)GetMonData(pokemon, MON_DATA_FORME, NULL));
    }
    else if (species == SPECIES_WORMADAM)
    {
        FUN_02023FEC(pokedex, species, (s32)GetMonData(pokemon, MON_DATA_FORME, NULL));
    }
    else if (species == SPECIES_SHELLOS)
    {
        FUN_02023E70(pokedex, species, GetMonData(pokemon, MON_DATA_FORME, NULL));
    }
    else if (species == SPECIES_GASTRODON)
    {
        FUN_02023E70(pokedex, species, GetMonData(pokemon, MON_DATA_FORME, NULL));
    }
    else if (species == SPECIES_DEOXYS)
    {
        FUN_0202415C(pokedex, species, pokemon);
    }
}

void FUN_02024294(struct Pokedex * pokedex, u32 species, u32 language)
{
    s32 r4 = FUN_02087A50(species);
    s32 r0 = FUN_02087A1C(language);
    if (r4 != 14 && r0 != 6)
    {
        pokedex->field_0129[r4] |= (1 << r0);
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

const u16 UNK_020EE940 = SPECIES_MANAPHY;

const u16 UNK_020EE942[] = {
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

BOOL FUN_02024340(u16 species)
{
    s32 i;
    BOOL ret = TRUE;
    for (i = 0; i < (s32)NELEMS(UNK_020EE942); i++)
    {
        if (species == UNK_020EE942[i])
            ret = FALSE;
    }
    return ret;
}

BOOL FUN_02024364(u16 a0)
{
    BOOL ret = TRUE;
    if (a0 == SPECIES_MANAPHY)
        ret = FALSE;
    return ret;
}

void Sav2_Pokedex_init(struct Pokedex * pokedex)
{
    memset(pokedex, 0, sizeof(struct Pokedex));
    pokedex->magic = 0xBEEFCAFE;
    pokedex->field_0139 = 0;
    memset(pokedex->field_010C, 0xFF, 28);
    pokedex->field_0108[0] = 0xFF;
    pokedex->field_0108[1] = 0xFF;
    pokedex->field_010A[0] = 0xFF;
    pokedex->field_010A[1] = 0xFF;
    FUN_0202419C(pokedex);
}

u16 FUN_020243C8(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 i;
    s32 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (FUN_02024594(pokedex, (u16)i) == TRUE)
            count++;
    }
    return (u16)count;
}

u16 FUN_02024404(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 i;
    s32 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (FUN_020245F0(pokedex, (u16)i) == TRUE)
            count++;
    }
    return (u16)count;
}

u16 FUN_02024440(struct Pokedex * pokedex)
{
    if (Pokedex_GetNatDexFlag(pokedex))
        return FUN_02024404(pokedex);
    else
        return FUN_020244A4(pokedex);
}

u16 FUN_0202445C(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 i;
    s32 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (FUN_02024594(pokedex, (u16)i) == TRUE && SpeciesToSinnohDexNo((u16)i) != 0)
            count++;
    }
    return (u16)count;
}

u16 FUN_020244A4(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 i;
    s32 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (FUN_020245F0(pokedex, (u16)i) == TRUE && SpeciesToSinnohDexNo((u16)i) != 0)
            count++;
    }
    return (u16)count;
}

BOOL FUN_020244EC(struct Pokedex * pokedex)
{
    return FUN_02024518(pokedex) >= 482;
}

BOOL FUN_02024504(struct Pokedex * pokedex)
{
    return FUN_02024550(pokedex) >= 150;
}

u16 FUN_02024518(struct Pokedex * pokedex)
{
    s32 i;
    u16 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (FUN_02024594(pokedex, (u16)i) == TRUE && FUN_02024340((u16)i) == TRUE)
            count++;
    }
    return count;
}

u16 FUN_02024550(struct Pokedex * pokedex)
{
    s32 i;
    u16 count = 0;
    for (i = 1; i <= NATIONAL_DEX_COUNT; i++)
    {
        if (FUN_020245F0(pokedex, (u16)i) == TRUE && SpeciesToSinnohDexNo((u16)i) != 0 && FUN_02024364((u16)i) == TRUE)
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

BOOL FUN_02024594(struct Pokedex * pokedex, u16 species)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (DexSpeciesIsInvalid(species))
        return FALSE;
    if (!CheckDexFlag(pokedex->field_0004, species) || !CheckDexFlag(pokedex->field_0044, species))
        return FALSE;
    return TRUE;
}

BOOL FUN_020245F0(struct Pokedex * pokedex, u16 species)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (DexSpeciesIsInvalid(species))
        return FALSE;
    return CheckDexFlag(pokedex->field_0044, species);
}

u32 FUN_02024648(struct Pokedex * pokedex, u32 a1)
{
    u32 r6;
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (a1 == 0)
        r6 = (u32)pokedex->field_0104;
    else
        GF_ASSERT(0); // r6 is not initialized because execution should halt here
    return r6;
}

s32 FUN_02024674(struct Pokedex * pokedex, u16 species, s32 r6)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (DexSpeciesIsInvalid(species))
        return -1;
    if (CheckDexFlag(pokedex->field_0044, species))
        return FUN_020242C8(pokedex, species, r6);
    else
        return -1;
}

static inline s32 FindFirstAvailableUnownLetterSlot_2(struct Pokedex * pokedex)
{
    s32 i;
    for (i = 0; i < 28; i++)
    {
        if (pokedex->field_010C[i] == 0xFF)
            break;
    }
    return i;
}

s32 FUN_020246DC(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 i;
    i = FindFirstAvailableUnownLetterSlot_2(pokedex);
    if (i <= a1)
        return -1;
    return pokedex->field_010C[a1];
}

s32 FUN_0202471C(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return FindFirstAvailableUnownLetterSlot_2(pokedex);
}

BOOL FUN_02024748(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (FUN_02023D8C(pokedex, SPECIES_SHELLOS) <= a1)
        return -1;
    GF_ASSERT(a1 < 2);
    return CheckDexFlag(&pokedex->field_0108[0], (u16)(a1 + 1));
}

s32 FUN_020247A4(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return FUN_02023D8C(pokedex, SPECIES_SHELLOS);
}

BOOL FUN_020247C8(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (FUN_02023D8C(pokedex, SPECIES_GASTRODON) <= a1)
        return -1;
    GF_ASSERT(a1 < 2);
    return CheckDexFlag(&pokedex->field_0108[1], (u16)(a1 + 1));
}

s32 FUN_02024828(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return FUN_02023D8C(pokedex, SPECIES_GASTRODON);
}

s32 FUN_0202484C(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (FUN_02023F2C(pokedex, SPECIES_BURMY) <= a1)
        return -1;
    GF_ASSERT(a1 < 3);
    return CheckDexFlagPair(&pokedex->field_010A[0], (u16)a1);
}

s32 FUN_0202489C(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return FUN_02023F2C(pokedex, SPECIES_BURMY);
}

s32 FUN_020248BC(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (FUN_02023F2C(pokedex, SPECIES_WORMADAM) <= a1)
        return -1;
    GF_ASSERT(a1 < 3);
    return CheckDexFlagPair(&pokedex->field_010A[1], (u16)a1);
}

s32 FUN_0202490C(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return FUN_02023F2C(pokedex, SPECIES_WORMADAM);
}

s32 FUN_02024930(struct Pokedex * pokedex, s32 a1)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return (s32)GetDeoxysFormeFlag(pokedex, (u8)a1);
}

s32 FUN_02024970(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return FUN_020240D0(pokedex);
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

void FUN_0202498C(struct Pokedex * pokedex, struct Pokemon * pokemon)
{
    u16 species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, NULL);
    u32 personality = GetMonData(pokemon, MON_DATA_PERSONALITY, NULL);
    u32 gender = GetMonGender(pokemon);
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    if (DexSpeciesIsInvalid(species))
        return;
    if (!CheckDexFlag(pokedex->field_0044, species))
    {
        if (species == SPECIES_SPINDA)
            pokedex->field_0104 = personality;
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
    FUN_020241B8(pokedex, species, pokemon);
    SetDexFlag(pokedex->field_0044, species);
}

void FUN_02024AF0(struct Pokedex * pokedex, struct Pokemon * pokemon)
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
    if (!CheckDexFlag(pokedex->field_0044, species))
    {
        if (species == SPECIES_SPINDA)
            pokedex->field_0104 = personality;
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
    FUN_020241B8(pokedex, species, pokemon);
    FUN_02024294(pokedex, species, language);
    SetDexFlag(pokedex->field_0004, species);
    SetDexFlag(pokedex->field_0044, species);
}

void Pokedex_SetNatDexFlag(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    pokedex->field_0139 = 1;
}

BOOL Pokedex_GetNatDexFlag(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return pokedex->field_0139;
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

s32 FUN_02024D00(struct Pokedex * pokedex, u32 species, u32 language)
{
    GF_ASSERT(language < 8);
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    s32 r5 = FUN_02087A50(species);
    if (r5 == 14)
        return 0;
    s32 r0 = FUN_02087A1C(language);
    return pokedex->field_0129[r5] & (1 << r0);
}

void FUN_02024D4C(struct Pokedex * pokedex)
{
    pokedex->field_0137 = 1;
}

BOOL FUN_02024D58(struct Pokedex * pokedex)
{
    return pokedex->field_0137;
}

BOOL FUN_02024D64(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    return pokedex->field_0138;
}

void FUN_02024D80(struct Pokedex * pokedex)
{
    GF_ASSERT(pokedex->magic == 0xBEEFCAFE);
    pokedex->field_0138 = 1;
}

struct Pokedex * FUN_02024DA0(struct SaveBlock2 * sav2)
{
    return (struct Pokedex *)SavArray_get(sav2, 7);
}

s32 FUN_02024DAC(struct Pokedex * pokedex, s32 a1, u32 a2)
{
    switch (a1)
    {
    case SPECIES_UNOWN:
        if (a2 < FUN_0202471C(pokedex))
            return FUN_020246DC(pokedex, (s32)a2);
        break;
    case SPECIES_SHELLOS:
        if (a2 < FUN_020247A4(pokedex))
            return FUN_02024748(pokedex, (s32)a2);
        break;
    case SPECIES_GASTRODON:
        if (a2 < FUN_02024828(pokedex))
            return FUN_020247C8(pokedex, (s32)a2);
        break;
    case SPECIES_BURMY:
        if (a2 < FUN_0202489C(pokedex))
            return FUN_0202484C(pokedex, (s32)a2);
        break;
    case SPECIES_WORMADAM:
        if (a2 < FUN_0202490C(pokedex))
            return FUN_020248BC(pokedex, (s32)a2);
        break;
    case SPECIES_DEOXYS:
        if (a2 < FUN_02024970(pokedex))
            return FUN_02024930(pokedex, (s32)a2);
        break;
    }
    return 0;
}
