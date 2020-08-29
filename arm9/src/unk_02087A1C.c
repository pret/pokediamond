#include "global.h"
#include "constants/species.h"
#include "unk_02087A1C.h"

#pragma thumb on

struct MeisterRodata
{
    u16 species[14];
    u8 languages[6];
};

static const struct MeisterRodata sMeister = {
    {
        SPECIES_EKANS,
        SPECIES_PIKACHU,
        SPECIES_PSYDUCK,
        SPECIES_PONYTA,
        SPECIES_STARYU,
        SPECIES_MAGIKARP,
        SPECIES_WOBBUFFET,
        SPECIES_HERACROSS,
        SPECIES_SNEASEL,
        SPECIES_TEDDIURSA,
        SPECIES_HOUNDOUR,
        SPECIES_WINGULL,
        SPECIES_SLAKOTH,
        SPECIES_ROSELIA
    },
    {
        LANGUAGE_JAPANESE,
        LANGUAGE_ENGLISH,
        LANGUAGE_FRENCH,
        LANGUAGE_GERMAN,
        LANGUAGE_ITALIAN,
        LANGUAGE_SPANISH
    }
};

s32 GetMeisterLanguageIdx(u32 language)
{
    s32 i;
    const u8 * ptr = sMeister.languages;
    for (i = 0; i < 6; i++, ptr++)
    {
        if (language == *ptr)
            break;
    }
    return i;
}

u8 GetMeisterLanguage(s32 idx)
{
    GF_ASSERT(idx < 6);
    const u8 * ptr = sMeister.languages;
    return ptr[idx];
}

s32 GetMeisterSpeciesIdx(u32 species)
{
    s32 i;
    const u16 * ptr = sMeister.species;
    for (i = 0; i < 14; i++, ptr++)
    {
        if (species == *ptr)
            break;
    }
    return i;
}
