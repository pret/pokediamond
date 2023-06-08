#include "global.h"
#include "pokemon.h"
#include "unk_0206B688.h"

u16 BoxMon_GetAlternateForme(struct BoxPokemon * boxmon);
u32 FUN_0206B6D4(u32 species, u32 is_egg, u32 forme);

u32 FUN_0206B688(struct BoxPokemon * boxmon)
{
    BOOL decry = AcquireBoxMonLock(boxmon);
    u32 species = GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL);
    u32 is_egg = GetBoxMonData(boxmon, MON_DATA_IS_EGG, NULL);
    u32 forme = BoxMon_GetAlternateForme(boxmon);
    u32 ret = FUN_0206B6D4(species, is_egg, forme);
    ReleaseBoxMonLock(boxmon, decry);
    return ret;
}

u32 FUN_0206B6C8(struct Pokemon * pokemon)
{
    return FUN_0206B688(FUN_020690E4(pokemon));
}

u32 FUN_0206B6D4(u32 species, u32 is_egg, u32 forme)
{
    if (is_egg == TRUE)
    {
        if (species == SPECIES_MANAPHY)
            return 502;
        else
            return 501;
    }
    if (forme != 0)
    {
        if (species == SPECIES_DEOXYS)
            return 502 + forme;
        if (species == SPECIES_UNOWN)
            return 506 + forme;
        if (species == SPECIES_BURMY)
            return 533 + forme;
        if (species == SPECIES_WORMADAM)
            return 535 + forme;
        if (species == SPECIES_SHELLOS)
            return 537 + forme;
        if (species == SPECIES_GASTRODON)
            return 538 + forme;
    }
    return (species <= SPECIES_ARCEUS ? species : 0) + 7;
}

u16 BoxMon_GetAlternateForme(struct BoxPokemon * boxmon)
{
    u32 species = GetBoxMonData(boxmon, MON_DATA_SPECIES2, NULL);
    switch (species)
    {
    case SPECIES_UNOWN:
        return GetBoxMonUnownLetter(boxmon);
    case SPECIES_DEOXYS:
    case SPECIES_BURMY:
    case SPECIES_WORMADAM:
    case SPECIES_SHELLOS:
    case SPECIES_GASTRODON:
        return (u16) GetBoxMonData(boxmon, MON_DATA_FORME, NULL);
    default:
        return 0;
    }
}

const u8 UNK_020F8074[] = {
    0, 1, 1, 1, 0, 0, 0, 0, 2, 2, 1, 1, 0, 1, 2, 2,
    0, 0, 0, 2, 1, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2,
    2, 2, 2, 0, 0, 2, 1, 0, 0, 2, 2, 1, 0, 0, 0, 0,
    0, 2, 2, 2, 1, 1, 1, 2, 1, 2, 0, 0, 0, 0, 0, 2,
    2, 2, 0, 2, 0, 1, 1, 1, 2, 2, 1, 1, 1, 0, 0, 0,
    0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 1, 2, 2, 0, 0, 0, 1, 1, 1, 2, 2, 1, 2, 2, 1,
    1, 0, 0, 1, 0, 0, 0, 0, 2, 2, 0, 1, 2, 1, 0, 2,
    2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1,
    0, 0, 0, 0, 0, 2, 2, 0, 1, 1, 1, 1, 1, 1, 2, 2,
    2, 2, 2, 2, 2, 0, 0, 1, 0, 2, 2, 0, 0, 0, 1, 2,
    2, 0, 0, 2, 0, 0, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1,
    1, 1, 0, 0, 2, 2, 2, 0, 0, 0, 0, 1, 0, 2, 2, 2,
    0, 0, 2, 0, 0, 1, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 2, 1, 1,
    1, 1, 1, 0, 2, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0,
    0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 2, 0, 2, 1, 1, 1,
    1, 1, 1, 0, 2, 2, 0, 0, 1, 1, 1, 2, 0, 1, 1, 2,
    2, 1, 1, 1, 1, 0, 2, 2, 2, 1, 2, 0, 0, 2, 2, 2,
    2, 2, 2, 0, 0, 1, 0, 0, 0, 0, 2, 0, 1, 2, 0, 0,
    2, 0, 1, 0, 1, 0, 2, 1, 1, 1, 1, 1, 1, 0, 0, 0,
    2, 1, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 2, 0, 0,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0,
    0, 1, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0,
    1, 0, 0, 1, 1, 1, 1, 0, 0, 2, 2, 0, 0, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 2, 2, 2, 2, 2, 0, 1, 0,
    2, 0, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2,
    2, 1, 1, 0, 2, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1,
    0, 2, 1, 0, 2, 1, 1, 0, 2, 2, 0, 1, 0, 2, 2, 0,
    0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 1, 0, 0, 0, 0, 0, 0
};

u32 FUN_0206B7BC(u32 species, u32 forme, u32 is_egg)
{
    if (is_egg == TRUE)
    {
        if (species == SPECIES_MANAPHY)
            species = 495;
        else
            species = 494;
    }
    else if (species > SPECIES_ARCEUS)
        species = 0;
    else if (forme != 0)
    {
        if (species == SPECIES_DEOXYS)
            species = 495 + forme;
        else if (species == SPECIES_UNOWN)
            species = 498 + forme;
        else if (species == SPECIES_BURMY)
            species = 526 + forme;
        else if (species == SPECIES_WORMADAM)
            species = 528 + forme;
        else if (species == SPECIES_SHELLOS)
            species = 530 + forme;
        else if (species == SPECIES_GASTRODON)
            species = 531 + forme;
    }
    return UNK_020F8074[species];
}

u32 FUN_0206B83C(struct BoxPokemon * boxmon)
{
    BOOL decry = AcquireBoxMonLock(boxmon);
    u32 forme = BoxMon_GetAlternateForme(boxmon);
    u32 species = GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL);
    u32 is_egg = GetBoxMonData(boxmon, MON_DATA_IS_EGG, NULL);
    ReleaseBoxMonLock(boxmon, decry);
    return FUN_0206B7BC(species, forme, is_egg);
}

u32 FUN_0206B87C(struct Pokemon * pokemon)
{
    return FUN_0206B83C(FUN_020690E4(pokemon));
}

u32 FUN_0206B888(void)
{
    return 0;
}

u32 FUN_0206B88C(void)
{
    return 2;
}

u32 FUN_0206B890(void)
{
    return 4;
}

u32 FUN_0206B894(void)
{
    return 6;
}

u32 FUN_0206B898(void)
{
    return 1;
}

u32 FUN_0206B89C(void)
{
    return 3;
}

u32 FUN_0206B8A0(void)
{
    return 5;
}
