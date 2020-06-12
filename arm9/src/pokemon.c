#include "global.h"
#define IN_POKEMON_C
#include "pokemon.h"
#include "heap.h"
#include "MI_memory.h"
#include "math_util.h"

#pragma thumb on

void MonEncryptSegment(void * datap, u32 size, u32 key);
void MonDecryptSegment(void * datap, u32 size, u32 key);
u16 MonEncryptionLCRNG(u32 * seed);
u16 CalcMonChecksum(void * datap, u32 size);
void InitBoxMonMoveset(struct BoxPokemon * boxmon);
u32 GetMonDataInternal(struct Pokemon * pokemon, u32 attr, void * ptr);
u32 GetBoxMonDataInternal(struct BoxPokemon * pokemon, u32 attr, void * ptr);
void LoadMonBaseStats_HandleAlternateForme(u32 species, u32 forme, struct BaseStats * baseStats);
int ApplyNatureModToStat(u8 nature, u16 statval, u32 statno);

#define ENCRY_ARGS_PTY(mon) &(mon)->party, sizeof((mon)->party), (mon)->box.pid
#define ENCRY_ARGS_BOX(boxmon) &(boxmon)->substructs, sizeof((boxmon)->substructs), (boxmon)->checksum
#define ENCRYPT_PTY(mon) MonEncryptSegment(ENCRY_ARGS_PTY(mon))
#define ENCRYPT_BOX(boxmon) MonEncryptSegment(ENCRY_ARGS_BOX(boxmon))
#define DECRYPT_PTY(mon) MonDecryptSegment(ENCRY_ARGS_PTY(mon))
#define DECRYPT_BOX(boxmon) MonDecryptSegment(ENCRY_ARGS_BOX(boxmon))
#define SHINY_CHECK(otid, pid) (( \
    ((((otid) & 0xFFFF0000u) >> 16u)) ^ \
    (((otid) & 0xFFFFu)) ^ \
    ((((pid) & 0xFFFF0000u) >> 16u))^ \
    (((pid) & 0xFFFFu))) \
    < 8u)
#define CALC_UNOWN_LETTER(pid) ((u32)((((pid) & 0x3000000) >> 18) | (((pid) & 0x30000) >> 12) | (((pid) & 0x300) >> 6) | (((pid) & 0x3) >> 0)) % 28u)

const u16 sItemOdds[2][2] = {
    { 45, 95 },
    { 20, 80 },
};

const s8 sFriendshipModTable[][3] = {
    {  5,  3,   2 },
    {  5,  3,   2 },
    {  1,  1,   0 },
    {  3,  2,   1 },
    {  1,  1,   0 },
    {  1,  1,   1 },
    { -1, -1,  -1 },
    { -5, -5, -10 },
    { -5, -5, -10 },
    {  3,  2,   1 },
};

const u16 sLegendaryMonsList[] = {
    SPECIES_MEWTWO,
    SPECIES_MEW,
    SPECIES_HO_OH,
    SPECIES_LUGIA,
    SPECIES_CELEBI,
    SPECIES_KYOGRE,
    SPECIES_GROUDON,
    SPECIES_RAYQUAZA,
    SPECIES_JIRACHI,
    SPECIES_DEOXYS,
    SPECIES_DIALGA,
    SPECIES_PALKIA,
    SPECIES_GIRATINA,
    SPECIES_PHIONE,
    SPECIES_MANAPHY,
    SPECIES_DARKRAI,
    SPECIES_SHAYMIN,
    SPECIES_ARCEUS,
};

const s8 UNK_020F7F16[][5] = {
    // Atk, Def, Spd, SpA, SpD
    {    0,   0,   0,   0,   0},
    {    1,   0,   0,   0,  -1},
    {    1,   0,  -1,   0,   0},
    {    1,  -1,   0,   0,   0},
    {    1,   0,   0,  -1,   0},
    {   -1,   0,   0,   0,   1},
    {    0,   0,   0,   0,   0},
    {    0,   0,  -1,   0,   1},
    {    0,  -1,   0,   0,   1},
    {    0,   0,   0,  -1,   1},
    {   -1,   0,   1,   0,   0},
    {    0,   0,   1,   0,  -1},
    {    0,   0,   0,   0,   0},
    {    0,  -1,   1,   0,   0},
    {    0,   0,   1,  -1,   0},
    {   -1,   1,   0,   0,   0},
    {    0,   1,   0,   0,  -1},
    {    0,   1,  -1,   0,   0},
    {    0,   0,   0,   0,   0},
    {    0,   1,   0,  -1,   0},
    {   -1,   0,   0,   1,   0},
    {    0,   0,   0,   1,  -1},
    {    0,   0,  -1,   1,   0},
    {    0,  -1,   0,   1,   0},
    {    0,   0,   0,   0,   0},
};

const u8 sNatureStatMods[][5] = {
    {  0,  0,  0,  0,  0 },
    {  1, -1,  0,  0,  0 },
    {  1,  0, -1,  0,  0 },
    {  1,  0,  0, -1,  0 },
    {  1,  0,  0,  0, -1 },
    { -1,  1,  0,  0,  0 },
    {  0,  0,  0,  0,  0 },
    {  0,  1, -1,  0,  0 },
    {  0,  1,  0, -1,  0 },
    {  0,  1,  0,  0, -1 },
    { -1,  0,  1,  0,  0 },
    {  0, -1,  1,  0,  0 },
    {  0,  0,  0,  0,  0 },
    {  0,  0,  1, -1,  0 },
    {  0,  0,  1,  0, -1 },
    { -1,  0,  0,  1,  0 },
    {  0, -1,  0,  1,  0 },
    {  0,  0, -1,  1,  0 },
    {  0,  0,  0,  0,  0 },
    {  0,  0,  0,  1, -1 },
    { -1,  0,  0,  0,  1 },
    {  0, -1,  0,  0,  1 },
    {  0,  0, -1,  0,  1 },
    {  0,  0,  0, -1,  1 },
    {  0,  0,  0,  0,  0 },
};

void ZeroMonData(struct Pokemon * pokemon)
{
    MIi_CpuClearFast(0, pokemon, sizeof(struct Pokemon));
    ENCRYPT_BOX(&pokemon->box);
    ENCRYPT_PTY(pokemon);
}

void ZeroBoxMonData(struct BoxPokemon * boxmon)
{
    MIi_CpuClearFast(0, boxmon, sizeof(struct BoxPokemon));
    ENCRYPT_BOX(boxmon);
}

u32 SizeOfStructPokemon(void)
{
    return sizeof(struct Pokemon);
}

struct Pokemon * AllocMonZeroed(u32 heap_id)
{
    struct Pokemon * pokemon = (struct Pokemon *)AllocFromHeap(heap_id, sizeof(struct Pokemon));
    ZeroMonData(pokemon);
    return pokemon;
}

BOOL TryDecryptMon(struct Pokemon * mon)
{
    BOOL ret = FALSE;

    if (!mon->box.party_lock)
    {
        ret = TRUE;
        GF_ASSERT(!mon->box.box_lock);
        mon->box.party_lock = TRUE;
        mon->box.box_lock = TRUE;
        DECRYPT_PTY(mon);
        DECRYPT_BOX(&mon->box);
    }
    return ret;
}

BOOL TryEncryptMon(struct Pokemon * mon, BOOL decrypt_result)
{
    BOOL ret = FALSE;
    if (mon->box.party_lock == TRUE && decrypt_result == TRUE)
    {
        ret = TRUE;
        mon->box.party_lock = FALSE;
        mon->box.box_lock = FALSE;
        ENCRYPT_PTY(mon);
        mon->box.checksum = CalcMonChecksum(&mon->box.substructs, sizeof(mon->box.substructs));
        ENCRYPT_BOX(&mon->box);
    }
    return ret;
}

BOOL TryDecryptBoxMon(struct BoxPokemon * mon)
{
    BOOL ret = FALSE;

    if (!mon->box_lock)
    {
        ret = TRUE;
        mon->box_lock = TRUE;
        DECRYPT_BOX(mon);
    }
    return ret;
}

BOOL TryEncryptBoxMon(struct BoxPokemon * mon, BOOL decrypt_result)
{
    BOOL ret = FALSE;
    if (mon->box_lock == TRUE && decrypt_result == TRUE)
    {
        ret = TRUE;
        mon->box_lock = FALSE;
        mon->checksum = CalcMonChecksum(&mon->substructs, sizeof(mon->substructs));
        ENCRYPT_BOX(mon);
    }
    return ret;
}

void CreateMon(struct Pokemon * pokemon, int species, int level, int fixedIV, int hasFixedPersonality, int fixedPersonality, int otIdType, int fixedOtId)
{
    struct SealStruct * seal;
    u32 capsule;
    u8 seal_coords[0x18];
    ZeroMonData(pokemon);
    CreateBoxMon(&pokemon->box, species, level, fixedIV, hasFixedPersonality, fixedPersonality, otIdType, fixedOtId);
    // Not your average encryption call
    MonEncryptSegment(&pokemon->party, sizeof(pokemon->party), 0);
    ENCRYPT_PTY(pokemon);
    SetMonData(pokemon, MON_DATA_LEVEL, &level);
    seal = CreateNewSealsObject(0);
    SetMonData(pokemon, MON_DATA_SEAL_STRUCT, seal);
    FreeToHeap(seal);
    capsule = 0;
    SetMonData(pokemon, MON_DATA_CAPSULE, &capsule);
    MIi_CpuClearFast(0, seal_coords, sizeof(seal_coords));
    SetMonData(pokemon, MON_DATA_SEAL_COORDS, seal_coords);
    CalcMonLevelAndStats(pokemon);
}

void CreateBoxMon(struct BoxPokemon * boxPokemon, int species, int level, int fixedIV, int hasFixedPersonality, int fixedPersonality, int otIdType, int fixedOtId)
{
    BOOL decry;
    u32 exp;
    u32 iv;
    ZeroBoxMonData(boxPokemon);
    decry = TryDecryptBoxMon(boxPokemon);
    if (hasFixedPersonality == 0)
    {
        fixedPersonality = (rand_LC() | (rand_LC() << 16));
    }
    SetBoxMonDataEncrypted(boxPokemon, MON_DATA_PERSONALITY, &fixedPersonality);
    if (otIdType == 2)
    {
        do
        {
            fixedOtId = (rand_LC() | (rand_LC() << 16));
        } while (SHINY_CHECK(fixedOtId, fixedPersonality));
    }
    else if (otIdType != 1)
        fixedOtId = 0;
    SetBoxMonDataEncrypted(boxPokemon, MON_DATA_OTID, &fixedOtId);
    SetBoxMonDataEncrypted(boxPokemon, MON_DATA_GAME_LANGUAGE, &gGameLanguage);
    SetBoxMonDataEncrypted(boxPokemon, MON_DATA_SPECIES, &species);
    SetBoxMonDataEncrypted(boxPokemon, MON_DATA_SPECIES_NAME, NULL);
    exp = GetMonExpBySpeciesAndLevel(species, level);
    SetBoxMonDataEncrypted(boxPokemon, MON_DATA_EXPERIENCE, &exp);
    exp = GetMonBaseStat(species, BASE_FRIENDSHIP);
    SetBoxMonDataEncrypted(boxPokemon, MON_DATA_FRIENDSHIP, &exp);
    SetBoxMonDataEncrypted(boxPokemon, MON_DATA_MET_LEVEL, &level);
    SetBoxMonDataEncrypted(boxPokemon, MON_DATA_GAME_VERSION, &gGameVersion);
    exp = 4;
    SetBoxMonDataEncrypted(boxPokemon, MON_DATA_POKEBALL, &exp);
    if (fixedIV < 0x20)
    {
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_HP_IV, &fixedIV);
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_ATK_IV, &fixedIV);
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_DEF_IV, &fixedIV);
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_SPEED_IV, &fixedIV);
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_SPATK_IV, &fixedIV);
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_SPDEF_IV, &fixedIV);
    }
    else
    {
        exp = rand_LC();
        iv = exp & 0x1F;
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_HP_IV, &iv);
        iv = (exp & 0x3E0) >> 5;
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_ATK_IV, &iv);
        iv = (exp & 0x7C00) >> 10;
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_DEF_IV, &iv);
        exp = rand_LC();
        iv = exp & 0x1F;
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_SPEED_IV, &iv);
        iv = (exp & 0x3E0) >> 5;
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_SPATK_IV, &iv);
        iv = (exp & 0x7C00) >> 10;
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_SPDEF_IV, &iv);
    }
    exp = GetMonBaseStat(species, BASE_ABILITY_1);
    iv = GetMonBaseStat(species, BASE_ABILITY_2);
    if (iv != 0)
    {
        if (fixedPersonality & 1)
            SetBoxMonDataEncrypted(boxPokemon, MON_DATA_ABILITY, &iv);
        else
            SetBoxMonDataEncrypted(boxPokemon, MON_DATA_ABILITY, &exp);
    }
    else
        SetBoxMonDataEncrypted(boxPokemon, MON_DATA_ABILITY, &exp);
    exp = GetBoxMonGenderEncrypted(boxPokemon);
    SetBoxMonDataEncrypted(boxPokemon, MON_DATA_GENDER, &exp);
    InitBoxMonMoveset(boxPokemon);
    TryEncryptBoxMon(boxPokemon, decry);
}

void CreateMonWithNature(struct Pokemon * pokemon, u16 species, u8 level, u8 fixedIv, u8 nature)
{
    u32 personality;
    do
    {
        personality = (u32)(rand_LC() | (rand_LC() << 16));
    } while (nature != GetNatureFromPersonality(personality));
    CreateMon(pokemon, (int)species, (int)level, (int)fixedIv, 1, (int)personality, (int)0, (int)0);
}

// FIXME: stack storage of pokemon, fixedIv swapped
void CreateMonWithGenderNatureLetter(struct Pokemon * pokemon, u16 species, u8 level, u8 fixedIv, u8 gender, u8 nature, u8 letter)
{
    u32 pid = 0;
    u16 test = 0;
    if (letter != 0 && letter < 29)
    {
        do {
            pid = (u32)(rand_LC() | (rand_LC() << 16));
            test = (u16)CALC_UNOWN_LETTER(pid);
        } while (nature != GetNatureFromPersonality(pid) || gender != GetGenderBySpeciesAndPersonality(species, pid) || test != letter - 1);
    }
    else
    {
        pid = GenPersonalityByGenderAndNature(species, gender, nature);
    }
    CreateMon(pokemon, (int)species, (int)level, (int)fixedIv, 1, (int)pid, 0, 0);
}

u32 GenPersonalityByGenderAndNature(u16 species, u8 gender, u8 nature)
{
    int pid = nature;
    u8 ratio = (u8)GetMonBaseStat(species, BASE_GENDER_RATIO);
    switch (ratio)
    {
    case MON_RATIO_MALE:
    case MON_RATIO_FEMALE:
    case MON_RATIO_UNKNOWN:
        break;
    default:
        if (gender == MON_MALE)
        {
            // Smallest increment that forces the low byte to exceed the
            // gender ratio, thus making the mon male
            pid = 25 * ((ratio / 25) + 1);
            pid += nature;
        }
        break;
    }
    return (u32)pid;
}

void CreateMonWithFixedIVs(struct Pokemon * pokemon, int species, int level, int ivs, int personality)
{
    CreateMon(pokemon, species, level, 0, 1, personality, 0, 0);
    SetMonData(pokemon, MON_DATA_IVS_WORD, &ivs);
    CalcMonLevelAndStats(pokemon);
}

void CalcMonLevelAndStats(struct Pokemon * pokemon)
{
    BOOL decry = TryDecryptMon(pokemon);
    u32 level = CalcMonLevelEncrypted(pokemon);
    SetMonData(pokemon, MON_DATA_LEVEL, &level);
    CalcMonStats(pokemon);
    TryEncryptMon(pokemon, decry);
}

void CalcMonStats(struct Pokemon * pokemon)
{
    struct BaseStats * baseStats;
    int level;
    int maxHp;
    int hpIv;
    int hpEv;
    int atkIv;
    int defIv;
    int speedIv;
    int spatkIv;
    int spdefIv;
    int atkEv;
    int defEv;
    int speedEv;
    int spatkEv;
    int spdefEv;
    int forme;
    int hp;
    int species;
    int newMaxHp;
    int newAtk;
    int newDef;
    int newSpeed;
    int newSpatk;
    int newSpdef;
    BOOL decry = TryDecryptMon(pokemon);
    level = (int)GetMonData(pokemon, MON_DATA_LEVEL, NULL);
    maxHp = (int)GetMonData(pokemon, MON_DATA_MAXHP, NULL);
    hp = (int)GetMonData(pokemon, MON_DATA_HP, NULL);
    hpIv = (int)GetMonData(pokemon, MON_DATA_HP_IV, NULL);
    hpEv = (int)GetMonData(pokemon, MON_DATA_HP_EV, NULL);
    atkIv = (int)GetMonData(pokemon, MON_DATA_ATK_IV, NULL);
    atkEv = (int)GetMonData(pokemon, MON_DATA_ATK_EV, NULL);
    defIv = (int)GetMonData(pokemon, MON_DATA_DEF_IV, NULL);
    defEv = (int)GetMonData(pokemon, MON_DATA_DEF_EV, NULL);
    speedIv = (int)GetMonData(pokemon, MON_DATA_SPEED_IV, NULL);
    speedEv = (int)GetMonData(pokemon, MON_DATA_SPEED_EV, NULL);
    spatkIv = (int)GetMonData(pokemon, MON_DATA_SPATK_IV, NULL);
    spatkEv = (int)GetMonData(pokemon, MON_DATA_SPATK_EV, NULL);
    spdefIv = (int)GetMonData(pokemon, MON_DATA_SPDEF_IV, NULL);
    spdefEv = (int)GetMonData(pokemon, MON_DATA_SPDEF_EV, NULL);
    forme = (int)GetMonData(pokemon, MON_DATA_FORME, NULL);
    species = (int)GetMonData(pokemon, MON_DATA_SPECIES, NULL);

    baseStats = (struct BaseStats *)AllocFromHeap(0, sizeof(struct BaseStats));
    LoadMonBaseStats_HandleAlternateForme(species, forme, baseStats);

    if (species == SPECIES_SHEDINJA)
        newMaxHp = 1;
    else
    {
        newMaxHp = (baseStats->hp * 2 + hpIv + hpEv / 4) * level / 100 + level + 10;
    }
    SetMonData(pokemon, MON_DATA_MAXHP, &newMaxHp);

    newAtk = (baseStats->atk * 2 + atkIv + atkEv / 4) * level / 100 + 5;
    newAtk = ApplyNatureModToStat(GetMonNature(pokemon), newAtk, 1);
    SetMonData(pokemon, MON_DATA_ATK, &newAtk);

    newDef = (baseStats->def * 2 + defIv + defEv / 4) * level / 100 + 5;
    newDef = ApplyNatureModToStat(GetMonNature(pokemon), newDef, 2);
    SetMonData(pokemon, MON_DATA_DEF, &newDef);

    newSpeed = (baseStats->speed * 2 + speedIv + speedEv / 4) * level / 100 + 5;
    newSpeed = ApplyNatureModToStat(GetMonNature(pokemon), newSpeed, 3);
    SetMonData(pokemon, MON_DATA_SPEED, &newSpeed);

    newSpatk = (baseStats->spatk * 2 + spatkIv + spatkEv / 4) * level / 100 + 5;
    newSpatk = ApplyNatureModToStat(GetMonNature(pokemon), newSpatk, 4);
    SetMonData(pokemon, MON_DATA_SPATK, &newSpatk);

    newSpdef = (baseStats->spdef * 2 + spdefIv + spdefEv / 4) * level / 100 + 5;
    newSpdef = ApplyNatureModToStat(GetMonNature(pokemon), newSpdef, 5);
    SetMonData(pokemon, MON_DATA_SPDEF, &newSpdef);

    FreeToHeap(baseStats);

    if (hp != 0 || maxHp == 0)
    {
        if (species == SPECIES_SHEDINJA)
            hp = 1;
        else if (hp == 0)
            hp = newMaxHp;
        else
            hp += newMaxHp - maxHp;
    }
    if (hp != 0)
        SetMonData(pokemon, MON_DATA_HP, &hp);
    TryEncryptMon(pokemon, decry);
}

u32 GetMonData(struct Pokemon * pokemon, u32 attr, void * dest)
{
    u32 ret;
    u32 checksum;
    if (!pokemon->box.party_lock)
    {
        DECRYPT_PTY(pokemon);
        DECRYPT_BOX(&pokemon->box);
        checksum = CalcMonChecksum(&pokemon->box.substructs, sizeof(pokemon->box.substructs));
        if (checksum != pokemon->box.checksum)
        {
            GF_ASSERT(checksum == pokemon->box.checksum);
            pokemon->box.checksum_fail = TRUE;
        }
    }
    ret = GetMonDataInternal(pokemon, attr, dest);
    if (!pokemon->box.party_lock)
    {
        ENCRYPT_PTY(pokemon);
        ENCRYPT_BOX(&pokemon->box);
    }
    return ret;
}

u32 GetMonDataInternal(struct Pokemon * pokemon, u32 attr, void * dest)
{
    switch (attr)
    {
    case MON_DATA_STATUS:
        return pokemon->party.status;
    case MON_DATA_LEVEL:
        return pokemon->party.level;
    case MON_DATA_CAPSULE:
        return pokemon->party.capsule;
    case MON_DATA_HP:
        return pokemon->party.hp;
    case MON_DATA_MAXHP:
        return pokemon->party.maxHp;
    case MON_DATA_ATK:
        return pokemon->party.atk;
    case MON_DATA_DEF:
        return pokemon->party.def;
    case MON_DATA_SPEED:
        return pokemon->party.speed;
    case MON_DATA_SPATK:
        return pokemon->party.spatk;
    case MON_DATA_SPDEF:
        return pokemon->party.spdef;
    case MON_DATA_SEAL_STRUCT:
        CopySealsObject(&pokemon->party.seal_something, dest);
        return 1;
    case MON_DATA_SEAL_COORDS:
        FUN_02029C74(pokemon->party.sealCoords, dest);
        return 1;
    default:
        return GetBoxMonDataInternal(&pokemon->box, attr, dest);
    }
}

u32 GetBoxMonData(struct BoxPokemon * boxmon, u32 attr, void * dest)
{
    u32 ret;
    u32 checksum;
    if (!boxmon->box_lock)
    {
        DECRYPT_BOX(boxmon);
        checksum = CalcMonChecksum(&boxmon->substructs, sizeof(boxmon->substructs));
        if (checksum != boxmon->checksum)
        {
            GF_ASSERT(checksum == boxmon->checksum);
            boxmon->checksum_fail = TRUE;
        }
    }
    ret = GetBoxMonDataInternal(boxmon, attr, dest);
    if (!boxmon->box_lock)
    {
        ENCRYPT_BOX(boxmon);
    }
    return ret;
}
