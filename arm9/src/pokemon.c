#include "global.h"
#define IN_POKEMON_C
#include "proto.h"
#include "pokemon.h"
#include "heap.h"
#include "MI_memory.h"
#include "math_util.h"
#include "move_data.h"
#include "string_util.h"
#include "text.h"
#include "constants/abilities.h"

#pragma thumb on

void MonEncryptSegment(void * datap, u32 size, u32 key);
void MonDecryptSegment(void * datap, u32 size, u32 key);
u16 MonEncryptionLCRNG(u32 * seed);
u16 CalcMonChecksum(void * datap, u32 size);
void InitBoxMonMoveset(struct BoxPokemon * boxmon);
u32 GetMonDataInternal(struct Pokemon * pokemon, int attr, void * ptr);
PokemonDataBlock * GetSubstruct(struct BoxPokemon * boxmon, u32 personality, u32 which_struct);
u32 GetBoxMonDataInternal(struct BoxPokemon * pokemon, int attr, void * ptr);
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

u32 GetMonData(struct Pokemon * pokemon, int attr, void * dest)
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

u32 GetMonDataInternal(struct Pokemon * pokemon, int attr, void * dest)
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

u32 GetBoxMonData(struct BoxPokemon * boxmon, int attr, void * dest)
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

u32 GetBoxMonDataInternal(struct BoxPokemon * boxmon, int attr, void * dest)
{
    u32 ret = 0;
    PokemonDataBlockA * blockA = &GetSubstruct(boxmon, boxmon->pid, 0)->blockA;
    PokemonDataBlockB * blockB = &GetSubstruct(boxmon, boxmon->pid, 1)->blockB;
    PokemonDataBlockC * blockC = &GetSubstruct(boxmon, boxmon->pid, 2)->blockC;
    PokemonDataBlockD * blockD = &GetSubstruct(boxmon, boxmon->pid, 3)->blockD;

    switch (attr)
    {
    default:
        ret = 0;
        break;
    case MON_DATA_PERSONALITY:
        ret = boxmon->pid;
        break;
    case MON_DATA_PARTY_LOCK:
        ret = boxmon->party_lock;
        break;
    case MON_DATA_BOX_LOCK:
        ret = boxmon->box_lock;
        break;
    case MON_DATA_CHECKSUM_FAILED:
        ret = boxmon->checksum_fail;
        break;
    case MON_DATA_CHECKSUM:
        ret = boxmon->checksum;
        break;
    case MON_DATA_SPECIES_EXISTS:
        if (blockA->species != SPECIES_NONE)
            ret = TRUE;
        else
            ret = FALSE;
        break;
    case MON_DATA_SANITY_IS_EGG:
        ret = boxmon->checksum_fail;
        if (!ret)
            ret = blockB->isEgg;
        break;
    case MON_DATA_SPECIES2:
        ret = blockA->species;
        if (ret != SPECIES_NONE && (blockB->isEgg || boxmon->checksum_fail))
            ret = SPECIES_EGG;
        break;
    case MON_DATA_LEVEL:
        ret = CalcLevelBySpeciesAndExp(blockA->species, blockA->exp);
        break;
    case MON_DATA_SPECIES:
        if (boxmon->checksum_fail)
            ret = SPECIES_EGG;
        else
            ret = blockA->species;
        break;
    case MON_DATA_HELD_ITEM:
        ret = blockA->heldItem;
        break;
    case MON_DATA_OTID:
        ret = blockA->otID;
        break;
    case MON_DATA_EXPERIENCE:
        ret = blockA->exp;
        break;
    case MON_DATA_FRIENDSHIP:
        ret = blockA->friendship;
        break;
    case MON_DATA_ABILITY:
        ret = blockA->ability;
        break;
    case MON_DATA_MARKINGS:
        ret = blockA->markings;
        break;
    case MON_DATA_GAME_LANGUAGE:
        ret = blockA->originLanguage;
        break;
    case MON_DATA_HP_EV:
        ret = blockA->hpEV;
        break;
    case MON_DATA_ATK_EV:
        ret = blockA->atkEV;
        break;
    case MON_DATA_DEF_EV:
        ret = blockA->defEV;
        break;
    case MON_DATA_SPEED_EV:
        ret = blockA->spdEV;
        break;
    case MON_DATA_SPATK_EV:
        ret = blockA->spatkEV;
        break;
    case MON_DATA_SPDEF_EV:
        ret = blockA->spdefEV;
        break;
    case MON_DATA_COOL:
        ret = blockA->coolStat;
        break;
    case MON_DATA_BEAUTY:
        ret = blockA->beautyStat;
        break;
    case MON_DATA_CUTE:
        ret = blockA->cuteStat;
        break;
    case MON_DATA_SMART:
        ret = blockA->smartStat;
        break;
    case MON_DATA_TOUGH:
        ret = blockA->toughStat;
        break;
    case MON_DATA_SHEEN:
        ret = blockA->sheen;
        break;
    case MON_DATA_SINNOH_CHAMP_RIBBON:
    case MON_DATA_SINNOH_RIBBON_26:
    case MON_DATA_SINNOH_RIBBON_27:
    case MON_DATA_SINNOH_RIBBON_28:
    case MON_DATA_SINNOH_RIBBON_29:
    case MON_DATA_SINNOH_RIBBON_30:
    case MON_DATA_SINNOH_RIBBON_31:
    case MON_DATA_SINNOH_RIBBON_32:
    case MON_DATA_SINNOH_RIBBON_33:
    case MON_DATA_SINNOH_RIBBON_34:
    case MON_DATA_SINNOH_RIBBON_35:
    case MON_DATA_SINNOH_RIBBON_36:
    case MON_DATA_SINNOH_RIBBON_37:
    case MON_DATA_SINNOH_RIBBON_38:
    case MON_DATA_SINNOH_RIBBON_39:
    case MON_DATA_SINNOH_RIBBON_40:
    case MON_DATA_SINNOH_RIBBON_41:
    case MON_DATA_SINNOH_RIBBON_42:
    case MON_DATA_SINNOH_RIBBON_43:
    case MON_DATA_SINNOH_RIBBON_44:
    case MON_DATA_SINNOH_RIBBON_45:
    case MON_DATA_SINNOH_RIBBON_46:
    case MON_DATA_SINNOH_RIBBON_47:
    case MON_DATA_SINNOH_RIBBON_48:
    case MON_DATA_SINNOH_RIBBON_49:
    case MON_DATA_SINNOH_RIBBON_50:
    case MON_DATA_SINNOH_RIBBON_51:
    case MON_DATA_SINNOH_RIBBON_52:
    case MON_DATA_SINNOH_RIBBON_53:
    {
        if (blockA->sinnohRibbons & (1ll << (attr - MON_DATA_SINNOH_CHAMP_RIBBON)))
        {
            ret = TRUE;
        }
        else
        {
            ret = FALSE;
        }
    }
        break;
    case MON_DATA_MOVE1:
    case MON_DATA_MOVE2:
    case MON_DATA_MOVE3:
    case MON_DATA_MOVE4:
        attr -= MON_DATA_MOVE1;
        ret = blockB->moves[attr];
        break;
    case MON_DATA_MOVE1PP:
    case MON_DATA_MOVE2PP:
    case MON_DATA_MOVE3PP:
    case MON_DATA_MOVE4PP:
        attr -= MON_DATA_MOVE1PP;
        ret = blockB->movePP[attr];
        break;
    case MON_DATA_MOVE1PPUP:
    case MON_DATA_MOVE2PPUP:
    case MON_DATA_MOVE3PPUP:
    case MON_DATA_MOVE4PPUP:
        attr -= MON_DATA_MOVE1PPUP;
        ret = blockB->movePpUps[attr];
        break;
    case MON_DATA_MOVE1MAXPP:
    case MON_DATA_MOVE2MAXPP:
    case MON_DATA_MOVE3MAXPP:
    case MON_DATA_MOVE4MAXPP:
        attr -= MON_DATA_MOVE1MAXPP;
        ret = FUN_0206AB30(blockB->moves[attr], blockB->movePpUps[attr]);
        break;
    case MON_DATA_HP_IV:
        ret = blockB->hpIV;
        break;
    case MON_DATA_ATK_IV:
        ret = blockB->atkIV;
        break;
    case MON_DATA_DEF_IV:
        ret = blockB->defIV;
        break;
    case MON_DATA_SPEED_IV:
        ret = blockB->spdIV;
        break;
    case MON_DATA_SPATK_IV:
        ret = blockB->spatkIV;
        break;
    case MON_DATA_SPDEF_IV:
        ret = blockB->spdefIV;
        break;
    case MON_DATA_IS_EGG:
        ret = boxmon->checksum_fail;
        if (!ret)
            ret = blockB->isEgg;
        break;
    case MON_DATA_HAS_NICKNAME:
        ret = blockB->isNicknamed;
        break;
    case MON_DATA_COOL_RIBBON:
    case MON_DATA_HOENN_RIBBON_79:
    case MON_DATA_HOENN_RIBBON_80:
    case MON_DATA_HOENN_RIBBON_81:
    case MON_DATA_HOENN_RIBBON_82:
    case MON_DATA_HOENN_RIBBON_83:
    case MON_DATA_HOENN_RIBBON_84:
    case MON_DATA_HOENN_RIBBON_85:
    case MON_DATA_HOENN_RIBBON_86:
    case MON_DATA_HOENN_RIBBON_87:
    case MON_DATA_HOENN_RIBBON_88:
    case MON_DATA_HOENN_RIBBON_89:
    case MON_DATA_HOENN_RIBBON_90:
    case MON_DATA_HOENN_RIBBON_91:
    case MON_DATA_HOENN_RIBBON_92:
    case MON_DATA_HOENN_RIBBON_93:
    case MON_DATA_HOENN_RIBBON_94:
    case MON_DATA_HOENN_RIBBON_95:
    case MON_DATA_HOENN_RIBBON_96:
    case MON_DATA_HOENN_RIBBON_97:
    case MON_DATA_HOENN_RIBBON_98:
    case MON_DATA_HOENN_RIBBON_99:
    case MON_DATA_HOENN_RIBBON_100:
    case MON_DATA_HOENN_RIBBON_101:
    case MON_DATA_HOENN_RIBBON_102:
    case MON_DATA_HOENN_RIBBON_103:
    case MON_DATA_HOENN_RIBBON_104:
    case MON_DATA_HOENN_RIBBON_105:
    case MON_DATA_HOENN_RIBBON_106:
    case MON_DATA_HOENN_RIBBON_107:
    case MON_DATA_HOENN_RIBBON_108:
    case MON_DATA_HOENN_RIBBON_109:
        if (blockB->ribbonFlags & (1ll << (attr - MON_DATA_COOL_RIBBON)))
            ret = TRUE;
        else
            ret = FALSE;
        break;
    case MON_DATA_FATEFUL_ENCOUNTER:
        ret = blockB->fatefulEncounter;
        break;
    case MON_DATA_GENDER:
        ret = blockB->gender;
        break;
    case MON_DATA_FORME:
        ret = blockB->alternateForm;
        break;
    case MON_DATA_RESERVED_113:
        ret = blockB->HGSS_shinyLeaves;
        break;
    case MON_DATA_RESERVED_114:
        ret = blockB->Unused;
        break;
    case MON_DATA_NICKNAME:
        if (boxmon->checksum_fail)
            GetSpeciesName(SPECIES_MANAPHY_EGG, 0, dest);
        else
        {
            u16 * dest16 = (u16 *)dest;
            for (ret = 0; ret < POKEMON_NAME_LENGTH; ret++)
            {
                dest16[ret] = blockC->nickname[ret];
            }
            dest16[ret] = EOS;
        }
        break;
    case MON_DATA_NICKNAME_3:
        ret = blockB->isNicknamed;
        // fallthrough
    case MON_DATA_NICKNAME_2:
        if (boxmon->checksum_fail)
        {
            u16 * buffer = FUN_0200AA50(SPECIES_MANAPHY_EGG, 0);
            FUN_02021A74(dest, buffer);
            FUN_02021A20(buffer);
        }
        else
        {
            FUN_02021E28(dest, blockC->nickname);
        }
        break;
    case MON_DATA_UNK_120:
        ret = blockC->Unused;
        break;
    case MON_DATA_GAME_VERSION:
        ret = blockC->originGame;
        break;
    case MON_DATA_SINNOH_RIBBON_122:
    case MON_DATA_SINNOH_RIBBON_123:
    case MON_DATA_SINNOH_RIBBON_124:
    case MON_DATA_SINNOH_RIBBON_125:
    case MON_DATA_SINNOH_RIBBON_126:
    case MON_DATA_SINNOH_RIBBON_127:
    case MON_DATA_SINNOH_RIBBON_128:
    case MON_DATA_SINNOH_RIBBON_129:
    case MON_DATA_SINNOH_RIBBON_130:
    case MON_DATA_SINNOH_RIBBON_131:
    case MON_DATA_SINNOH_RIBBON_132:
    case MON_DATA_SINNOH_RIBBON_133:
    case MON_DATA_SINNOH_RIBBON_134:
    case MON_DATA_SINNOH_RIBBON_135:
    case MON_DATA_SINNOH_RIBBON_136:
    case MON_DATA_SINNOH_RIBBON_137:
    case MON_DATA_SINNOH_RIBBON_138:
    case MON_DATA_SINNOH_RIBBON_139:
    case MON_DATA_SINNOH_RIBBON_140:
    case MON_DATA_SINNOH_RIBBON_141:
    case MON_DATA_SINNOH_RIBBON_142:
        if (blockC->sinnohRibbons2 & (1ll << (attr - MON_DATA_SINNOH_RIBBON_122)))
            ret = TRUE;
        else
            ret = FALSE;
        break;
    case MON_DATA_OT_NAME:
    {
        u16 * dest16 = (u16 *)dest;
        for (ret = 0; ret < OT_NAME_LENGTH; ret++)
            dest16[ret] = blockD->otTrainerName[ret];
        dest16[ret] = EOS;
    }
        break;
    case MON_DATA_OT_NAME_2:
        FUN_02021E28(dest, blockD->otTrainerName);
        break;
    case MON_DATA_EGG_MET_YEAR:
        ret = blockD->dateEggReceived[0];
        break;
    case MON_DATA_EGG_MET_MONTH:
        ret = blockD->dateEggReceived[1];
        break;
    case MON_DATA_EGG_MET_DAY:
        ret = blockD->dateEggReceived[2];
        break;
    case MON_DATA_MET_YEAR:
        ret = blockD->dateMet[0];
        break;
    case MON_DATA_MET_MONTH:
        ret = blockD->dateMet[1];
        break;
    case MON_DATA_MET_DAY:
        ret = blockD->dateMet[2];
        break;
    case MON_DATA_EGG_MET_LOCATION:
        ret = blockD->DP_EggLocation;
        break;
    case MON_DATA_MET_LOCATION:
        ret = blockD->DP_MetLocation;
        break;
    case MON_DATA_POKERUS:
        ret = blockD->pokerus;
        break;
    case MON_DATA_POKEBALL:
        ret = blockD->pokeball;
        break;
    case MON_DATA_MET_LEVEL:
        ret = blockD->metLevel;
        break;
    case MON_DATA_MET_GENDER:
        ret = blockD->metGender;
        break;
    case MON_DATA_ENCOUNTER_TYPE:
        ret = blockD->encounterType;
        break;
    case MON_DATA_RESERVED_158:
        ret = blockD->HGSS_Pokeball;
        break;
    case MON_DATA_IVS_WORD:
        ret = (blockB->hpIV) | \
                 (blockB->atkIV << 5) | \
                 (blockB->defIV << 10) | \
                 (blockB->spdIV << 15) | \
                 (blockB->spatkIV << 20) | \
                 (blockB->spdefIV << 25);
        break;
    case MON_DATA_UNK_175:
        if ((blockA->species == SPECIES_NIDORAN_F || blockA->species == SPECIES_NIDORAN_M) && !blockB->isNicknamed)
            ret = FALSE;
        else
            ret = TRUE;
        break;
    case MON_DATA_TYPE_1:
    case MON_DATA_TYPE_2:
        if (blockA->species == SPECIES_ARCEUS && blockA->ability == ABILITY_MULTITYPE)
            ret = GetArceusTypeByPlate(FUN_0206E7B8(blockA->heldItem, 1, 0));
        else
        {
            ret = GetMonBaseStat_HandleFormeConversion(blockA->species, blockB->alternateForm, attr - MON_DATA_TYPE_1 + BASE_TYPE1);
        }
        break;
    case MON_DATA_SPECIES_NAME:
        GetSpeciesName(blockA->species, 0, dest);
        break;
    }
    return ret;
}
