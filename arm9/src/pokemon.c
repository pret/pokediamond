#include "global.h"
#define IN_POKEMON_C
#include "proto.h"
#include "party.h"
#include "player_data.h"
#include "pokemon.h"
#include "filesystem.h"
#include "heap.h"
#include "MI_memory.h"
#include "math_util.h"
#include "move_data.h"
#include "string_util.h"
#include "seal.h"
#include "msgdata.h"
#include "itemtool.h"
#include "constants/abilities.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/sinnoh_dex.h"
#include "constants/trainer_classes.h"
#include "unk_020051F4.h"
#include "sound_chatot.h"


#pragma thumb on

u32 GetMonDataInternal(struct Pokemon * pokemon, int attr, void * ptr);
u32 GetBoxMonDataInternal(struct BoxPokemon * pokemon, int attr, void * ptr);
void SetMonDataInternal(struct Pokemon * pokemon, int attr, void * ptr);
void SetBoxMonDataInternal(struct BoxPokemon * pokemon, int attr, void * ptr);
void AddMonDataInternal(struct Pokemon * pokemon, int attr, int amount);
void AddBoxMonData(struct BoxPokemon * pokemon, int attr, int amount);
u32 CalcBoxMonExpToNextLevel(struct BoxPokemon * boxmon);
u16 ModifyStatByNature(u8 nature, u16 statval, u8 statno);
u8 GetGenderBySpeciesAndPersonality_PreloadedPersonal(struct BaseStats * personal, u16 species, u32 pid);
u8 BoxMonIsShiny(struct BoxPokemon * boxmon);
u8 CalcShininessByOtIdAndPersonality(u32 otid, u32 pid);
void InitBoxMonMoveset(struct BoxPokemon * boxmon);
u32 FUN_020696A8(struct BoxPokemon * boxmon, u16 move);
void FUN_02069718(struct BoxPokemon * boxmon, u16 move);
void BoxMonSetMoveInSlot(struct BoxPokemon * boxmon, u16 move, u8 slot);
void FUN_020698E8(struct BoxPokemon * boxmon, int slot1, int slot2);
s8 BoxMonGetFlavorPreference(struct BoxPokemon * boxmon, int flavor);
s8 GetFlavorPreferenceFromPID(u32 personality, int flavor);
u8 Party_MaskMonsWithPokerus(struct PlayerParty * party_p, u8 mask);
BOOL BoxMon_HasPokerus(struct BoxPokemon * boxmon);
BOOL BoxMon_IsImmuneToPokerus(struct BoxPokemon * boxmon);
void BoxMon_UpdateArceusForme(struct BoxPokemon * boxmon);
void LoadWotbl_HandleAlternateForme(int species, int forme, u16 * wotbl);
void FUN_0206A054(struct BoxPokemon *  boxmon, struct PlayerData * a1, u32 pokeball, u32 a3, u32 encounterType, u32 heap_id);
BOOL MonHasMove(struct Pokemon * pokemon, u16 move);
BOOL FUN_0206A144(struct BoxPokemon * boxmon, u32 a1);
BOOL FUN_0206A16C(u16 species, int forme, u32 a2);
void FUN_0206A1CC(struct BoxPokemon * boxmon);
u32 MaskOfFlagNo(int flagno);
void LoadMonPersonal(int species, struct BaseStats * personal);
void LoadMonEvolutionTable(u16 species, struct Evolution * dest);

int ResolveMonForme(int species, int forme);
void MonEncryptSegment(u16 * datap, u32 size, u32 key);
void MonDecryptSegment(u16 * datap, u32 size, u32 key);
u16 MonEncryptionLCRNG(u32 * seed);
u16 CalcMonChecksum(u16 * datap, u32 size);
PokemonDataBlock * GetSubstruct(struct BoxPokemon * boxmon, u32 personality, u8 which_struct);
void LoadMonBaseStats_HandleAlternateForme(int species, int forme, struct BaseStats * baseStats);
u8 GetBoxMonUnownLetter(struct BoxPokemon * boxmon);

#define ENCRY_ARGS_PTY(mon) (u16 *)&(mon)->party, sizeof((mon)->party), (mon)->box.pid
#define ENCRY_ARGS_BOX(boxmon) (u16 *)&(boxmon)->substructs, sizeof((boxmon)->substructs), (boxmon)->checksum
#define ENCRYPT_PTY(mon) MonEncryptSegment(ENCRY_ARGS_PTY(mon))
#define ENCRYPT_BOX(boxmon) MonEncryptSegment(ENCRY_ARGS_BOX(boxmon))
#define DECRYPT_PTY(mon) MonDecryptSegment(ENCRY_ARGS_PTY(mon))
#define DECRYPT_BOX(boxmon) MonDecryptSegment(ENCRY_ARGS_BOX(boxmon))
#define CHECKSUM(boxmon) CalcMonChecksum((u16 *)(boxmon)->substructs, sizeof((boxmon)->substructs))
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

const s8 sFlavorPreferencesByNature[][5] = {
    // Spicy, Dry, Sweet, Bitter, Sour
    {      0,   0,     0,      0,    0 }, // NATURE_HARDY
    {      1,   0,     0,      0,   -1 }, // NATURE_LONELY
    {      1,   0,    -1,      0,    0 }, // NATURE_BRAVE
    {      1,  -1,     0,      0,    0 }, // NATURE_ADAMANT
    {      1,   0,     0,     -1,    0 }, // NATURE_NAUGHTY
    {     -1,   0,     0,      0,    1 }, // NATURE_BOLD
    {      0,   0,     0,      0,    0 }, // NATURE_DOCILE
    {      0,   0,    -1,      0,    1 }, // NATURE_RELAXED
    {      0,  -1,     0,      0,    1 }, // NATURE_IMPISH
    {      0,   0,     0,     -1,    1 }, // NATURE_LAX
    {     -1,   0,     1,      0,    0 }, // NATURE_TIMID
    {      0,   0,     1,      0,   -1 }, // NATURE_HASTY
    {      0,   0,     0,      0,    0 }, // NATURE_SERIOUS
    {      0,  -1,     1,      0,    0 }, // NATURE_JOLLY
    {      0,   0,     1,     -1,    0 }, // NATURE_NAIVE
    {     -1,   1,     0,      0,    0 }, // NATURE_MODEST
    {      0,   1,     0,      0,   -1 }, // NATURE_MILD
    {      0,   1,    -1,      0,    0 }, // NATURE_QUIET
    {      0,   0,     0,      0,    0 }, // NATURE_BASHFUL
    {      0,   1,     0,     -1,    0 }, // NATURE_RASH
    {     -1,   0,     0,      1,    0 }, // NATURE_CALM
    {      0,   0,     0,      1,   -1 }, // NATURE_GENTLE
    {      0,   0,    -1,      1,    0 }, // NATURE_SASSY
    {      0,  -1,     0,      1,    0 }, // NATURE_CAREFUL
    {      0,   0,     0,      0,    0 }, // NATURE_QUIRKY
};

const s8 sNatureStatMods[][5] = {
    // Atk, Def, Speed, SpAtk, SpDef
    {    0,   0,     0,     0,     0 }, // NATURE_HARDY
    {    1,  -1,     0,     0,     0 }, // NATURE_LONELY
    {    1,   0,    -1,     0,     0 }, // NATURE_BRAVE
    {    1,   0,     0,    -1,     0 }, // NATURE_ADAMANT
    {    1,   0,     0,     0,    -1 }, // NATURE_NAUGHTY
    {   -1,   1,     0,     0,     0 }, // NATURE_BOLD
    {    0,   0,     0,     0,     0 }, // NATURE_DOCILE
    {    0,   1,    -1,     0,     0 }, // NATURE_RELAXED
    {    0,   1,     0,    -1,     0 }, // NATURE_IMPISH
    {    0,   1,     0,     0,    -1 }, // NATURE_LAX
    {   -1,   0,     1,     0,     0 }, // NATURE_TIMID
    {    0,  -1,     1,     0,     0 }, // NATURE_HASTY
    {    0,   0,     0,     0,     0 }, // NATURE_SERIOUS
    {    0,   0,     1,    -1,     0 }, // NATURE_JOLLY
    {    0,   0,     1,     0,    -1 }, // NATURE_NAIVE
    {   -1,   0,     0,     1,     0 }, // NATURE_MODEST
    {    0,  -1,     0,     1,     0 }, // NATURE_MILD
    {    0,   0,    -1,     1,     0 }, // NATURE_QUIET
    {    0,   0,     0,     0,     0 }, // NATURE_BASHFUL
    {    0,   0,     0,     1,    -1 }, // NATURE_RASH
    {   -1,   0,     0,     0,     1 }, // NATURE_CALM
    {    0,  -1,     0,     0,     1 }, // NATURE_GENTLE
    {    0,   0,    -1,     0,     1 }, // NATURE_SASSY
    {    0,   0,     0,    -1,     1 }, // NATURE_CAREFUL
    {    0,   0,     0,     0,     0 }, // NATURE_QUIRKY
};

void ZeroMonData(struct Pokemon * pokemon)
{
    MI_CpuClearFast(pokemon, sizeof(struct Pokemon));
    ENCRYPT_BOX(&pokemon->box);
    ENCRYPT_PTY(pokemon);
}

void ZeroBoxMonData(struct BoxPokemon * boxmon)
{
    MI_CpuClearFast(boxmon, sizeof(struct BoxPokemon));
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

BOOL AcquireMonLock(struct Pokemon * mon)
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

BOOL ReleaseMonLock(struct Pokemon * mon, BOOL decrypt_result)
{
    BOOL ret = FALSE;
    if (mon->box.party_lock == TRUE && decrypt_result == TRUE)
    {
        ret = TRUE;
        mon->box.party_lock = FALSE;
        mon->box.box_lock = FALSE;
        ENCRYPT_PTY(mon);
        mon->box.checksum = CHECKSUM(&mon->box);
        ENCRYPT_BOX(&mon->box);
    }
    return ret;
}

BOOL AcquireBoxMonLock(struct BoxPokemon * mon)
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

BOOL ReleaseBoxMonLock(struct BoxPokemon * mon, BOOL decrypt_result)
{
    BOOL ret = FALSE;
    if (mon->box_lock == TRUE && decrypt_result == TRUE)
    {
        ret = TRUE;
        mon->box_lock = FALSE;
        mon->checksum = CHECKSUM(mon);
        ENCRYPT_BOX(mon);
    }
    return ret;
}

void CreateMon(struct Pokemon * pokemon, int species, int level, int fixedIV, int hasFixedPersonality, int fixedPersonality, int otIdType, int fixedOtId)
{
    struct Mail * mail;
    u32 capsule;
    u8 seal_coords[0x18];
    ZeroMonData(pokemon);
    CreateBoxMon(&pokemon->box, species, level, fixedIV, hasFixedPersonality, fixedPersonality, otIdType, fixedOtId);
    // Not your average encryption call
    MonEncryptSegment((u16 *)&pokemon->party, sizeof(pokemon->party), 0);
    ENCRYPT_PTY(pokemon);
    SetMonData(pokemon, MON_DATA_LEVEL, &level);
    mail = Mail_new(0);
    SetMonData(pokemon, MON_DATA_MAIL_STRUCT, mail);
    FreeToHeap(mail);
    capsule = 0;
    SetMonData(pokemon, MON_DATA_CAPSULE, &capsule);
    MI_CpuClearFast(seal_coords, sizeof(seal_coords));
    SetMonData(pokemon, MON_DATA_SEAL_COORDS, seal_coords);
    CalcMonLevelAndStats(pokemon);
}

void CreateBoxMon(struct BoxPokemon * boxPokemon, int species, int level, int fixedIV, int hasFixedPersonality, int fixedPersonality, int otIdType, int fixedOtId)
{
    BOOL decry;
    u32 exp;
    u32 iv;
    ZeroBoxMonData(boxPokemon);
    decry = AcquireBoxMonLock(boxPokemon);
    if (hasFixedPersonality == 0)
    {
        fixedPersonality = (LCRandom() | (LCRandom() << 16));
    }
    SetBoxMonData(boxPokemon, MON_DATA_PERSONALITY, &fixedPersonality);
    if (otIdType == 2)
    {
        do
        {
            fixedOtId = (LCRandom() | (LCRandom() << 16));
        } while (SHINY_CHECK(fixedOtId, fixedPersonality));
    }
    else if (otIdType != 1)
        fixedOtId = 0;
    SetBoxMonData(boxPokemon, MON_DATA_OTID, &fixedOtId);
    SetBoxMonData(boxPokemon, MON_DATA_GAME_LANGUAGE, (void *)&gGameLanguage);
    SetBoxMonData(boxPokemon, MON_DATA_SPECIES, &species);
    SetBoxMonData(boxPokemon, MON_DATA_SPECIES_NAME, NULL);
    exp = GetMonExpBySpeciesAndLevel(species, level);
    SetBoxMonData(boxPokemon, MON_DATA_EXPERIENCE, &exp);
    exp = (u32)GetMonBaseStat(species, BASE_FRIENDSHIP);
    SetBoxMonData(boxPokemon, MON_DATA_FRIENDSHIP, &exp);
    SetBoxMonData(boxPokemon, MON_DATA_MET_LEVEL, &level);
    SetBoxMonData(boxPokemon, MON_DATA_GAME_VERSION, (void *)&gGameVersion);
    exp = ITEM_POKE_BALL;
    SetBoxMonData(boxPokemon, MON_DATA_POKEBALL, &exp);
    if (fixedIV < 0x20)
    {
        SetBoxMonData(boxPokemon, MON_DATA_HP_IV, &fixedIV);
        SetBoxMonData(boxPokemon, MON_DATA_ATK_IV, &fixedIV);
        SetBoxMonData(boxPokemon, MON_DATA_DEF_IV, &fixedIV);
        SetBoxMonData(boxPokemon, MON_DATA_SPEED_IV, &fixedIV);
        SetBoxMonData(boxPokemon, MON_DATA_SPATK_IV, &fixedIV);
        SetBoxMonData(boxPokemon, MON_DATA_SPDEF_IV, &fixedIV);
    }
    else
    {
        exp = LCRandom();
        iv = exp & 0x1F;
        SetBoxMonData(boxPokemon, MON_DATA_HP_IV, &iv);
        iv = (exp & 0x3E0) >> 5;
        SetBoxMonData(boxPokemon, MON_DATA_ATK_IV, &iv);
        iv = (exp & 0x7C00) >> 10;
        SetBoxMonData(boxPokemon, MON_DATA_DEF_IV, &iv);
        exp = LCRandom();
        iv = exp & 0x1F;
        SetBoxMonData(boxPokemon, MON_DATA_SPEED_IV, &iv);
        iv = (exp & 0x3E0) >> 5;
        SetBoxMonData(boxPokemon, MON_DATA_SPATK_IV, &iv);
        iv = (exp & 0x7C00) >> 10;
        SetBoxMonData(boxPokemon, MON_DATA_SPDEF_IV, &iv);
    }
    exp = (u32)GetMonBaseStat(species, BASE_ABILITY_1);
    iv = (u32)GetMonBaseStat(species, BASE_ABILITY_2);
    if (iv != 0)
    {
        if (fixedPersonality & 1)
            SetBoxMonData(boxPokemon, MON_DATA_ABILITY, &iv);
        else
            SetBoxMonData(boxPokemon, MON_DATA_ABILITY, &exp);
    }
    else
        SetBoxMonData(boxPokemon, MON_DATA_ABILITY, &exp);
    exp = GetBoxMonGender(boxPokemon);
    SetBoxMonData(boxPokemon, MON_DATA_GENDER, &exp);
    InitBoxMonMoveset(boxPokemon);
    ReleaseBoxMonLock(boxPokemon, decry);
}

void CreateMonWithNature(struct Pokemon * pokemon, u16 species, u8 level, u8 fixedIv, u8 nature)
{
    u32 personality;
    do
    {
        personality = (u32)(LCRandom() | (LCRandom() << 16));
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
            pid = (u32)(LCRandom() | (LCRandom() << 16));
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
    BOOL decry = AcquireMonLock(pokemon);
    u32 level = (u32)CalcMonLevel(pokemon);
    SetMonData(pokemon, MON_DATA_LEVEL, &level);
    CalcMonStats(pokemon);
    ReleaseMonLock(pokemon, decry);
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
    BOOL decry = AcquireMonLock(pokemon);
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
    newAtk = ModifyStatByNature(GetMonNature(pokemon), (u16)newAtk, 1);
    SetMonData(pokemon, MON_DATA_ATK, &newAtk);

    newDef = (baseStats->def * 2 + defIv + defEv / 4) * level / 100 + 5;
    newDef = ModifyStatByNature(GetMonNature(pokemon), (u16)newDef, 2);
    SetMonData(pokemon, MON_DATA_DEF, &newDef);

    newSpeed = (baseStats->speed * 2 + speedIv + speedEv / 4) * level / 100 + 5;
    newSpeed = ModifyStatByNature(GetMonNature(pokemon), (u16)newSpeed, 3);
    SetMonData(pokemon, MON_DATA_SPEED, &newSpeed);

    newSpatk = (baseStats->spatk * 2 + spatkIv + spatkEv / 4) * level / 100 + 5;
    newSpatk = ModifyStatByNature(GetMonNature(pokemon), (u16)newSpatk, 4);
    SetMonData(pokemon, MON_DATA_SPATK, &newSpatk);

    newSpdef = (baseStats->spdef * 2 + spdefIv + spdefEv / 4) * level / 100 + 5;
    newSpdef = ModifyStatByNature(GetMonNature(pokemon), (u16)newSpdef, 5);
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
    ReleaseMonLock(pokemon, decry);
}

u32 GetMonData(struct Pokemon * pokemon, int attr, void * dest)
{
    u32 ret;
    u32 checksum;
    if (!pokemon->box.party_lock)
    {
        DECRYPT_PTY(pokemon);
        DECRYPT_BOX(&pokemon->box);
        checksum = CHECKSUM(&pokemon->box);
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
    case MON_DATA_MAIL_STRUCT:
        Mail_copy(&pokemon->party.mail, dest);
        return 1;
    case MON_DATA_SEAL_COORDS:
        CapsuleArray_copy(&pokemon->party.sealCoords, dest);
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
        checksum = CHECKSUM(boxmon);
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
        ret = (u32)CalcLevelBySpeciesAndExp(blockA->species, blockA->exp);
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
    case MON_DATA_ABILITY_RIBBON:
    case MON_DATA_GREAT_ABILITY_RIBBON:
    case MON_DATA_DOUBLE_ABILITY_RIBBON:
    case MON_DATA_MULTI_ABILITY_RIBBON:
    case MON_DATA_PAIR_ABILITY_RIBBON:
    case MON_DATA_WORLD_ABILITY_RIBBON:
    case MON_DATA_ALERT_RIBBON:
    case MON_DATA_SHOCK_RIBBON:
    case MON_DATA_DOWNCAST_RIBBON:
    case MON_DATA_CARELESS_RIBBON:
    case MON_DATA_RELAX_RIBBON:
    case MON_DATA_SNOOZE_RIBBON:
    case MON_DATA_SMILE_RIBBON:
    case MON_DATA_GORGEOUS_RIBBON:
    case MON_DATA_ROYAL_RIBBON:
    case MON_DATA_GORGEOUS_ROYAL_RIBBON:
    case MON_DATA_FOOTPRINT_RIBBON:
    case MON_DATA_RECORD_RIBBON:
    case MON_DATA_HISTORY_RIBBON:
    case MON_DATA_LEGEND_RIBBON:
    case MON_DATA_RED_RIBBON:
    case MON_DATA_GREEN_RIBBON:
    case MON_DATA_BLUE_RIBBON:
    case MON_DATA_FESTIVAL_RIBBON:
    case MON_DATA_CARNIVAL_RIBBON:
    case MON_DATA_CLASSIC_RIBBON:
    case MON_DATA_PREMIER_RIBBON:
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
        ret = blockB->moves[attr - MON_DATA_MOVE1];
        break;
    case MON_DATA_MOVE1PP:
    case MON_DATA_MOVE2PP:
    case MON_DATA_MOVE3PP:
    case MON_DATA_MOVE4PP:
        ret = blockB->movePP[attr - MON_DATA_MOVE1PP];
        break;
    case MON_DATA_MOVE1PPUP:
    case MON_DATA_MOVE2PPUP:
    case MON_DATA_MOVE3PPUP:
    case MON_DATA_MOVE4PPUP:
        ret = blockB->movePpUps[attr - MON_DATA_MOVE1PPUP];
        break;
    case MON_DATA_MOVE1MAXPP:
    case MON_DATA_MOVE2MAXPP:
    case MON_DATA_MOVE3MAXPP:
    case MON_DATA_MOVE4MAXPP:
        ret = (u32)WazaGetMaxPp(blockB->moves[attr - MON_DATA_MOVE1MAXPP], blockB->movePpUps[attr - MON_DATA_MOVE1MAXPP]);
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
    case MON_DATA_HOENN_COOL_RIBBON:
    case MON_DATA_HOENN_COOL_RIBBON_SUPER:
    case MON_DATA_HOENN_COOL_RIBBON_HYPER:
    case MON_DATA_HOENN_COOL_RIBBON_MASTER:
    case MON_DATA_HOENN_BEAUTY_RIBBON:
    case MON_DATA_HOENN_BEAUTY_RIBBON_SUPER:
    case MON_DATA_HOENN_BEAUTY_RIBBON_HYPER:
    case MON_DATA_HOENN_BEAUTY_RIBBON_MASTER:
    case MON_DATA_HOENN_CUTE_RIBBON:
    case MON_DATA_HOENN_CUTE_RIBBON_SUPER:
    case MON_DATA_HOENN_CUTE_RIBBON_HYPER:
    case MON_DATA_HOENN_CUTE_RIBBON_MASTER:
    case MON_DATA_HOENN_SMART_RIBBON:
    case MON_DATA_HOENN_SMART_RIBBON_SUPER:
    case MON_DATA_HOENN_SMART_RIBBON_HYPER:
    case MON_DATA_HOENN_SMART_RIBBON_MASTER:
    case MON_DATA_HOENN_TOUGH_RIBBON:
    case MON_DATA_HOENN_TOUGH_RIBBON_SUPER:
    case MON_DATA_HOENN_TOUGH_RIBBON_HYPER:
    case MON_DATA_HOENN_TOUGH_RIBBON_MASTER:
    case MON_DATA_HOENN_CHAMPION_RIBBON:
    case MON_DATA_HOENN_WINNING_RIBBON:
    case MON_DATA_HOENN_VICTORY_RIBBON:
    case MON_DATA_HOENN_ARTIST_RIBBON:
    case MON_DATA_HOENN_EFFORT_RIBBON:
    case MON_DATA_HOENN_MARINE_RIBBON:
    case MON_DATA_HOENN_LAND_RIBBON:
    case MON_DATA_HOENN_SKY_RIBBON:
    case MON_DATA_HOENN_COUNTRY_RIBBON:
    case MON_DATA_HOENN_NATIONAL_RIBBON:
    case MON_DATA_HOENN_EARTH_RIBBON:
    case MON_DATA_HOENN_WORLD_RIBBON:
        if (blockB->ribbonFlags & (1ll << (attr - MON_DATA_HOENN_COOL_RIBBON)))
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
            GetSpeciesNameIntoArray(SPECIES_MANAPHY_EGG, 0, dest);
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
    case MON_DATA_NICKNAME_4:
        ret = blockB->isNicknamed;
        // fallthrough
    case MON_DATA_NICKNAME_3:
        if (boxmon->checksum_fail)
        {
            struct String * buffer = GetSpeciesName(SPECIES_MANAPHY_EGG, 0);
            StringCopy(dest, buffer);
            String_dtor(buffer);
        }
        else
        {
            CopyU16ArrayToString(dest, blockC->nickname);
        }
        break;
    case MON_DATA_UNK_120:
        ret = blockC->Unused;
        break;
    case MON_DATA_GAME_VERSION:
        ret = blockC->originGame;
        break;
    case MON_DATA_COOL_RIBBON:
    case MON_DATA_COOL_RIBBON_GREAT:
    case MON_DATA_COOL_RIBBON_ULTRA:
    case MON_DATA_COOL_RIBBON_MASTER:
    case MON_DATA_BEAUTY_RIBBON:
    case MON_DATA_BEAUTY_RIBBON_GREAT:
    case MON_DATA_BEAUTY_RIBBON_ULTRA:
    case MON_DATA_BEAUTY_RIBBON_MASTER:
    case MON_DATA_CUTE_RIBBON:
    case MON_DATA_CUTE_RIBBON_GREAT:
    case MON_DATA_CUTE_RIBBON_ULTRA:
    case MON_DATA_CUTE_RIBBON_MASTER:
    case MON_DATA_SMART_RIBBON:
    case MON_DATA_SMART_RIBBON_GREAT:
    case MON_DATA_SMART_RIBBON_ULTRA:
    case MON_DATA_SMART_RIBBON_MASTER:
    case MON_DATA_TOUGH_RIBBON:
    case MON_DATA_TOUGH_RIBBON_GREAT:
    case MON_DATA_TOUGH_RIBBON_ULTRA:
    case MON_DATA_TOUGH_RIBBON_MASTER:
    case MON_DATA_SINNOH_RIBBON_142:
        if (blockC->sinnohRibbons2 & (1ll << (attr - MON_DATA_COOL_RIBBON)))
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
        CopyU16ArrayToString(dest, blockD->otTrainerName);
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
            ret = (u32)GetArceusTypeByHeldItemEffect((u16)GetItemAttr(blockA->heldItem, 1, 0));
        else
        {
            ret = (u32)GetMonBaseStat_HandleFormeConversion(blockA->species, blockB->alternateForm, (enum BaseStat)(attr - MON_DATA_TYPE_1 + BASE_TYPE1));
        }
        break;
    case MON_DATA_SPECIES_NAME:
        GetSpeciesNameIntoArray(blockA->species, 0, dest);
        break;
    }
    return ret;
}

void SetMonData(struct Pokemon * pokemon, int attr, void * value)
{
    u16 checksum;
    if (!pokemon->box.party_lock)
    {
        DECRYPT_PTY(pokemon);
        DECRYPT_BOX(&pokemon->box);
        checksum = CHECKSUM(&pokemon->box);
        if (checksum != pokemon->box.checksum)
        {
            GF_ASSERT(checksum == pokemon->box.checksum);
            pokemon->box.checksum_fail = TRUE;
            ENCRYPT_BOX(&pokemon->box);
            return;
        }
    }
    SetMonDataInternal(pokemon, attr, value);
    if (!pokemon->box.party_lock)
    {
        ENCRYPT_PTY(pokemon);
        pokemon->box.checksum = CHECKSUM(&pokemon->box);
        ENCRYPT_BOX(&pokemon->box);
    }
}

void SetMonDataInternal(struct Pokemon * pokemon, int attr, void * value)
{
#define VALUE(type) (*(const type *)value)
    switch (attr)
    {
    case MON_DATA_STATUS:
        pokemon->party.status = VALUE(u32);
        break;
    case MON_DATA_LEVEL:
        pokemon->party.level = VALUE(u8);
        break;
    case MON_DATA_CAPSULE:
        pokemon->party.capsule = VALUE(u8);
        break;
    case MON_DATA_HP:
        pokemon->party.hp = VALUE(u16);
        break;
    case MON_DATA_MAXHP:
        pokemon->party.maxHp = VALUE(u16);
        break;
    case MON_DATA_ATK:
        pokemon->party.atk = VALUE(u16);
        break;
    case MON_DATA_DEF:
        pokemon->party.def = VALUE(u16);
        break;
    case MON_DATA_SPEED:
        pokemon->party.speed = VALUE(u16);
        break;
    case MON_DATA_SPATK:
        pokemon->party.spatk = VALUE(u16);
        break;
    case MON_DATA_SPDEF:
        pokemon->party.spdef = VALUE(u16);
        break;
    case MON_DATA_MAIL_STRUCT:
        Mail_copy((const struct Mail *)value, &pokemon->party.mail);
        break;
    case MON_DATA_SEAL_COORDS:
        CapsuleArray_copy((CapsuleArray *)value, &pokemon->party.sealCoords);
        break;
    default:
        SetBoxMonDataInternal(&pokemon->box, attr, value);
        break;
    }
#undef VALUE
}

void SetBoxMonData(struct BoxPokemon * boxmon, int attr, void * value)
{
    u16 checksum;
    if (!boxmon->box_lock)
    {
        DECRYPT_BOX(boxmon);
        checksum = CHECKSUM(boxmon);
        if (checksum != boxmon->checksum)
        {
            GF_ASSERT(checksum == boxmon->checksum);
            boxmon->checksum_fail = TRUE;
            ENCRYPT_BOX(boxmon);
            return;
        }
    }
    SetBoxMonDataInternal(boxmon, attr, value);
    if (!boxmon->box_lock)
    {
        boxmon->checksum = CHECKSUM(boxmon);
        ENCRYPT_BOX(boxmon);
    }
}


void SetBoxMonDataInternal(struct BoxPokemon * boxmon, int attr, void * value)
{
#define VALUE(type) (*(const type *)value)
    u8 flag;
    u64 mask;
    u32 i;
    u16 namebuf[POKEMON_NAME_LENGTH + 1];
    u16 namebuf2[POKEMON_NAME_LENGTH + 1];
    u16 namebuf3[POKEMON_NAME_LENGTH + 1];
    struct String * speciesName;

    PokemonDataBlockA *blockA = &GetSubstruct(boxmon, boxmon->pid, 0)->blockA;
    PokemonDataBlockB *blockB = &GetSubstruct(boxmon, boxmon->pid, 1)->blockB;
    PokemonDataBlockC *blockC = &GetSubstruct(boxmon, boxmon->pid, 2)->blockC;
    PokemonDataBlockD *blockD = &GetSubstruct(boxmon, boxmon->pid, 3)->blockD;

    switch (attr)
    {
    case MON_DATA_PERSONALITY:
        boxmon->pid = VALUE(u32);
        break;
    case MON_DATA_PARTY_LOCK:
        GF_ASSERT(0);
        boxmon->party_lock = VALUE(u8);
        break;
    case MON_DATA_BOX_LOCK:
        GF_ASSERT(0);
        boxmon->box_lock = VALUE(u8);
        break;
    case MON_DATA_CHECKSUM_FAILED:
        boxmon->checksum_fail = VALUE(u8);
        break;
    case MON_DATA_CHECKSUM:
        boxmon->checksum = VALUE(u16);
        break;
    case MON_DATA_SPECIES:
        blockA->species = VALUE(u16);
        break;
    case MON_DATA_HELD_ITEM:
        blockA->heldItem = VALUE(u16);
        break;
    case MON_DATA_OTID:
        blockA->otID = VALUE(u32);
        break;
    case MON_DATA_EXPERIENCE:
        blockA->exp = VALUE(u32);
        break;
    case MON_DATA_FRIENDSHIP:
        blockA->friendship = VALUE(u8);
        break;
    case MON_DATA_ABILITY:
        blockA->ability = VALUE(u8);
        break;
    case MON_DATA_MARKINGS:
        blockA->markings = VALUE(u8);
        break;
    case MON_DATA_GAME_LANGUAGE:
        blockA->originLanguage = VALUE(u8);
        break;
    case MON_DATA_HP_EV:
        blockA->hpEV = VALUE(u8);
        break;
    case MON_DATA_ATK_EV:
        blockA->atkEV = VALUE(u8);
        break;
    case MON_DATA_DEF_EV:
        blockA->defEV = VALUE(u8);
        break;
    case MON_DATA_SPEED_EV:
        blockA->spdEV = VALUE(u8);
        break;
    case MON_DATA_SPATK_EV:
        blockA->spatkEV = VALUE(u8);
        break;
    case MON_DATA_SPDEF_EV:
        blockA->spdefEV = VALUE(u8);
        break;
    case MON_DATA_COOL:
        blockA->coolStat = VALUE(u8);
        break;
    case MON_DATA_BEAUTY:
        blockA->beautyStat = VALUE(u8);
        break;
    case MON_DATA_CUTE:
        blockA->cuteStat = VALUE(u8);
        break;
    case MON_DATA_SMART:
        blockA->smartStat = VALUE(u8);
        break;
    case MON_DATA_TOUGH:
        blockA->toughStat = VALUE(u8);
        break;
    case MON_DATA_SHEEN:
        blockA->sheen = VALUE(u8);
        break;
    case MON_DATA_SINNOH_CHAMP_RIBBON:
    case MON_DATA_ABILITY_RIBBON:
    case MON_DATA_GREAT_ABILITY_RIBBON:
    case MON_DATA_DOUBLE_ABILITY_RIBBON:
    case MON_DATA_MULTI_ABILITY_RIBBON:
    case MON_DATA_PAIR_ABILITY_RIBBON:
    case MON_DATA_WORLD_ABILITY_RIBBON:
    case MON_DATA_ALERT_RIBBON:
    case MON_DATA_SHOCK_RIBBON:
    case MON_DATA_DOWNCAST_RIBBON:
    case MON_DATA_CARELESS_RIBBON:
    case MON_DATA_RELAX_RIBBON:
    case MON_DATA_SNOOZE_RIBBON:
    case MON_DATA_SMILE_RIBBON:
    case MON_DATA_GORGEOUS_RIBBON:
    case MON_DATA_ROYAL_RIBBON:
    case MON_DATA_GORGEOUS_ROYAL_RIBBON:
    case MON_DATA_FOOTPRINT_RIBBON:
    case MON_DATA_RECORD_RIBBON:
    case MON_DATA_HISTORY_RIBBON:
    case MON_DATA_LEGEND_RIBBON:
    case MON_DATA_RED_RIBBON:
    case MON_DATA_GREEN_RIBBON:
    case MON_DATA_BLUE_RIBBON:
    case MON_DATA_FESTIVAL_RIBBON:
    case MON_DATA_CARNIVAL_RIBBON:
    case MON_DATA_CLASSIC_RIBBON:
    case MON_DATA_PREMIER_RIBBON:
    case MON_DATA_SINNOH_RIBBON_53:
        flag = VALUE(u8);
        mask = (u64)flag << (attr - MON_DATA_SINNOH_CHAMP_RIBBON);
        if (flag)
            blockA->sinnohRibbons |= mask;
        else
            blockA->sinnohRibbons &= -1ull ^ mask;
        break;
    case MON_DATA_MOVE1:
    case MON_DATA_MOVE2:
    case MON_DATA_MOVE3:
    case MON_DATA_MOVE4:
        blockB->moves[attr - MON_DATA_MOVE1] = VALUE(u16);
        break;
    case MON_DATA_MOVE1PP:
    case MON_DATA_MOVE2PP:
    case MON_DATA_MOVE3PP:
    case MON_DATA_MOVE4PP:
        blockB->movePP[attr - MON_DATA_MOVE1PP] = VALUE(u8);
        break;
    case MON_DATA_MOVE1PPUP:
    case MON_DATA_MOVE2PPUP:
    case MON_DATA_MOVE3PPUP:
    case MON_DATA_MOVE4PPUP:
        blockB->movePpUps[attr - MON_DATA_MOVE1PPUP] = VALUE(u8);
        break;
    case MON_DATA_HP_IV:
        blockB->hpIV = VALUE(u8);
        break;
    case MON_DATA_ATK_IV:
        blockB->atkIV = VALUE(u8);
        break;
    case MON_DATA_DEF_IV:
        blockB->defIV = VALUE(u8);
        break;
    case MON_DATA_SPEED_IV:
        blockB->spdIV = VALUE(u8);
        break;
    case MON_DATA_SPATK_IV:
        blockB->spatkIV = VALUE(u8);
        break;
    case MON_DATA_SPDEF_IV:
        blockB->spdefIV = VALUE(u8);
        break;
    case MON_DATA_IS_EGG:
        blockB->isEgg = VALUE(u8);
        break;
    case MON_DATA_HAS_NICKNAME:
        blockB->isNicknamed = VALUE(u8);
        break;
    case MON_DATA_HOENN_COOL_RIBBON:
    case MON_DATA_HOENN_COOL_RIBBON_SUPER:
    case MON_DATA_HOENN_COOL_RIBBON_HYPER:
    case MON_DATA_HOENN_COOL_RIBBON_MASTER:
    case MON_DATA_HOENN_BEAUTY_RIBBON:
    case MON_DATA_HOENN_BEAUTY_RIBBON_SUPER:
    case MON_DATA_HOENN_BEAUTY_RIBBON_HYPER:
    case MON_DATA_HOENN_BEAUTY_RIBBON_MASTER:
    case MON_DATA_HOENN_CUTE_RIBBON:
    case MON_DATA_HOENN_CUTE_RIBBON_SUPER:
    case MON_DATA_HOENN_CUTE_RIBBON_HYPER:
    case MON_DATA_HOENN_CUTE_RIBBON_MASTER:
    case MON_DATA_HOENN_SMART_RIBBON:
    case MON_DATA_HOENN_SMART_RIBBON_SUPER:
    case MON_DATA_HOENN_SMART_RIBBON_HYPER:
    case MON_DATA_HOENN_SMART_RIBBON_MASTER:
    case MON_DATA_HOENN_TOUGH_RIBBON:
    case MON_DATA_HOENN_TOUGH_RIBBON_SUPER:
    case MON_DATA_HOENN_TOUGH_RIBBON_HYPER:
    case MON_DATA_HOENN_TOUGH_RIBBON_MASTER:
    case MON_DATA_HOENN_CHAMPION_RIBBON:
    case MON_DATA_HOENN_WINNING_RIBBON:
    case MON_DATA_HOENN_VICTORY_RIBBON:
    case MON_DATA_HOENN_ARTIST_RIBBON:
    case MON_DATA_HOENN_EFFORT_RIBBON:
    case MON_DATA_HOENN_MARINE_RIBBON:
    case MON_DATA_HOENN_LAND_RIBBON:
    case MON_DATA_HOENN_SKY_RIBBON:
    case MON_DATA_HOENN_COUNTRY_RIBBON:
    case MON_DATA_HOENN_NATIONAL_RIBBON:
    case MON_DATA_HOENN_EARTH_RIBBON:
    case MON_DATA_HOENN_WORLD_RIBBON:
        flag = VALUE(u8);
        mask = (u64)flag << (attr - MON_DATA_HOENN_COOL_RIBBON);
        if (flag)
            blockB->ribbonFlags |= mask;
        else
            blockB->ribbonFlags &= -1ull ^ mask;
        break;
    case MON_DATA_FATEFUL_ENCOUNTER:
        blockB->fatefulEncounter = VALUE(u8);
        break;
    case MON_DATA_GENDER:
        blockB->gender = VALUE(u8);
        break;
    case MON_DATA_FORME:
        blockB->alternateForm = VALUE(u8);
        break;
    case MON_DATA_RESERVED_113:
        blockB->HGSS_shinyLeaves = VALUE(u8);
        break;
    case MON_DATA_RESERVED_114:
        blockB->Unused = VALUE(u16);
        break;
    case MON_DATA_NICKNAME_2:
        GetSpeciesNameIntoArray(blockA->species, 0, namebuf);
        blockB->isNicknamed = StringNotEqual(namebuf, value);
        // fallthrough
    case MON_DATA_NICKNAME:
        for (i = 0; i < POKEMON_NAME_LENGTH + 1; i++)
        {
            blockC->nickname[i] = VALUE(u16); value = (void *const )((char *)value + 2);
        }
        break;
    case MON_DATA_NICKNAME_4:
        GetSpeciesNameIntoArray(blockA->species, 0, namebuf2);
        CopyStringToU16Array(value, namebuf3, POKEMON_NAME_LENGTH + 1);
        blockB->isNicknamed = StringNotEqual(namebuf2, namebuf3);
        // fallthrough
    case MON_DATA_NICKNAME_3:
        CopyStringToU16Array(value, blockC->nickname, POKEMON_NAME_LENGTH + 1);
        break;
    case MON_DATA_UNK_120:
        blockC->Unused = VALUE(u8);
        break;
    case MON_DATA_GAME_VERSION:
        blockC->originGame = VALUE(u8);
        break;
    case MON_DATA_COOL_RIBBON:
    case MON_DATA_COOL_RIBBON_GREAT:
    case MON_DATA_COOL_RIBBON_ULTRA:
    case MON_DATA_COOL_RIBBON_MASTER:
    case MON_DATA_BEAUTY_RIBBON:
    case MON_DATA_BEAUTY_RIBBON_GREAT:
    case MON_DATA_BEAUTY_RIBBON_ULTRA:
    case MON_DATA_BEAUTY_RIBBON_MASTER:
    case MON_DATA_CUTE_RIBBON:
    case MON_DATA_CUTE_RIBBON_GREAT:
    case MON_DATA_CUTE_RIBBON_ULTRA:
    case MON_DATA_CUTE_RIBBON_MASTER:
    case MON_DATA_SMART_RIBBON:
    case MON_DATA_SMART_RIBBON_GREAT:
    case MON_DATA_SMART_RIBBON_ULTRA:
    case MON_DATA_SMART_RIBBON_MASTER:
    case MON_DATA_TOUGH_RIBBON:
    case MON_DATA_TOUGH_RIBBON_GREAT:
    case MON_DATA_TOUGH_RIBBON_ULTRA:
    case MON_DATA_TOUGH_RIBBON_MASTER:
    case MON_DATA_SINNOH_RIBBON_142:
        flag = VALUE(u8);
        mask = (u64)flag << (attr - MON_DATA_COOL_RIBBON);
        if (flag)
            blockC->sinnohRibbons2 |= mask;
        else
            blockC->sinnohRibbons2 &= -1ull ^ mask;
        break;
    case MON_DATA_OT_NAME:
        for (i = 0; i < OT_NAME_LENGTH + 1; i++)
        {
            blockD->otTrainerName[i] = VALUE(u16); value = (void *)((char *)value + 2);
        }
        break;
    case MON_DATA_OT_NAME_2:
        CopyStringToU16Array(value, blockD->otTrainerName, OT_NAME_LENGTH + 1);
        break;
    case MON_DATA_EGG_MET_YEAR:
        blockD->dateEggReceived[0] = VALUE(u8);
        break;
    case MON_DATA_EGG_MET_MONTH:
        blockD->dateEggReceived[1] = VALUE(u8);
        break;
    case MON_DATA_EGG_MET_DAY:
        blockD->dateEggReceived[2] = VALUE(u8);
        break;
    case MON_DATA_MET_YEAR:
        blockD->dateMet[0] = VALUE(u8);
        break;
    case MON_DATA_MET_MONTH:
        blockD->dateMet[1] = VALUE(u8);
        break;
    case MON_DATA_MET_DAY:
        blockD->dateMet[2] = VALUE(u8);
        break;
    case MON_DATA_EGG_MET_LOCATION:
        blockD->DP_EggLocation = VALUE(u16);
        break;
    case MON_DATA_MET_LOCATION:
        blockD->DP_MetLocation = VALUE(u16);
        break;
    case MON_DATA_POKERUS:
        blockD->pokerus = VALUE(u8);
        break;
    case MON_DATA_POKEBALL:
        blockD->pokeball = VALUE(u8);
        break;
    case MON_DATA_MET_LEVEL:
        blockD->metLevel = VALUE(u8);
        break;
    case MON_DATA_MET_GENDER:
        blockD->metGender = VALUE(u8);
        break;
    case MON_DATA_ENCOUNTER_TYPE:
        blockD->encounterType = VALUE(u8);
        break;
    case MON_DATA_RESERVED_158:
        blockD->HGSS_Pokeball = VALUE(u16);
        break;
    case MON_DATA_IVS_WORD:
        blockB->hpIV    = (VALUE(u32) >>  0) & 0x1F;
        blockB->atkIV   = (VALUE(u32) >>  5) & 0x1F;
        blockB->defIV   = (VALUE(u32) >> 10) & 0x1F;
        blockB->spdIV   = (VALUE(u32) >> 15) & 0x1F;
        blockB->spatkIV = (VALUE(u32) >> 20) & 0x1F;
        blockB->spdefIV = (VALUE(u32) >> 25) & 0x1F;
        break;
    case MON_DATA_SPECIES_NAME:
        speciesName = GetSpeciesName(blockA->species, 0);
        CopyStringToU16Array(speciesName, blockC->nickname, POKEMON_NAME_LENGTH + 1);
        String_dtor(speciesName);
        break;
    }
#undef VALUE
}

void AddMonData(struct Pokemon * pokemon, int attr, int value)
{
    u16 checksum;
    if (!pokemon->box.party_lock)
    {
        DECRYPT_PTY(pokemon);
        DECRYPT_BOX(&pokemon->box);
        checksum = CHECKSUM(&pokemon->box);
        if (checksum != pokemon->box.checksum)
        {
            GF_ASSERT(checksum == pokemon->box.checksum);
            ENCRYPT_BOX(&pokemon->box);
            return;
        }
    }
    AddMonDataInternal(pokemon, attr, value);
    if (!pokemon->box.party_lock)
    {
        ENCRYPT_PTY(pokemon);
        pokemon->box.checksum = CHECKSUM(&pokemon->box);
        ENCRYPT_BOX(&pokemon->box);
    }
}

void AddMonDataInternal(struct Pokemon * pokemon, int attr, int value)
{
    s32 maxHp;
    switch (attr)
    {
    case MON_DATA_HP:
        maxHp = pokemon->party.maxHp;
        if ((s32)(pokemon->party.hp + value) > maxHp)
            pokemon->party.hp = (u16)maxHp;
        else
            pokemon->party.hp += value;
        break;
    case MON_DATA_STATUS:
    case MON_DATA_LEVEL:
    case MON_DATA_CAPSULE:
    case MON_DATA_MAXHP:
    case MON_DATA_ATK:
    case MON_DATA_DEF:
    case MON_DATA_SPEED:
    case MON_DATA_SPATK:
    case MON_DATA_SPDEF:
    case MON_DATA_MAIL_STRUCT:
    // case MON_DATA_SEAL_COORDS:
        GF_ASSERT(0);
        break;
    default:
        AddBoxMonData(&pokemon->box, attr, value);
        break;
    }
}

void AddBoxMonData(struct BoxPokemon * boxmon, int attr, int value)
{
    PokemonDataBlockA *blockA = &GetSubstruct(boxmon, boxmon->pid, 0)->blockA;
    PokemonDataBlockB *blockB = &GetSubstruct(boxmon, boxmon->pid, 1)->blockB;
    PokemonDataBlockC *blockC = &GetSubstruct(boxmon, boxmon->pid, 2)->blockC;
    PokemonDataBlockD *blockD = &GetSubstruct(boxmon, boxmon->pid, 3)->blockD;

    switch (attr)
    {
    case MON_DATA_EXPERIENCE:
        if (blockA->exp + value > GetMonExpBySpeciesAndLevel(blockA->species, 100))
            blockA->exp = GetMonExpBySpeciesAndLevel(blockA->species, 100);
        else
            blockA->exp += value;
        break;
    case MON_DATA_FRIENDSHIP:
        if (blockA->friendship + value > 255)
            blockA->friendship = 255;
        else
            blockA->friendship += value;
        break;
    case MON_DATA_HP_EV:
        blockA->hpEV += value;
        break;
    case MON_DATA_ATK_EV:
        blockA->atkEV += value;
        break;
    case MON_DATA_DEF_EV:
        blockA->defEV += value;
        break;
    case MON_DATA_SPEED_EV:
        blockA->spdEV += value;
        break;
    case MON_DATA_SPATK_EV:
        blockA->spatkEV += value;
        break;
    case MON_DATA_SPDEF_EV:
        blockA->spdefEV += value;
        break;
    case MON_DATA_COOL:
        if (blockA->coolStat + value > 255)
            blockA->coolStat = 255;
        else
            blockA->coolStat += value;
        break;
    case MON_DATA_BEAUTY:
        if (blockA->beautyStat + value > 255)
            blockA->beautyStat = 255;
        else
            blockA->beautyStat += value;
        break;
    case MON_DATA_CUTE:
        if (blockA->cuteStat + value > 255)
            blockA->cuteStat = 255;
        else
            blockA->cuteStat += value;
        break;
    case MON_DATA_SMART:
        if (blockA->smartStat + value > 255)
            blockA->smartStat = 255;
        else
            blockA->smartStat += value;
        break;
    case MON_DATA_TOUGH:
        if (blockA->toughStat + value > 255)
            blockA->toughStat = 255;
        else
            blockA->toughStat += value;
        break;
    case MON_DATA_SHEEN:
        if (blockA->sheen + value > 255)
            blockA->sheen = 255;
        else
            blockA->sheen += value;
        break;
    case MON_DATA_MOVE1PP:
    case MON_DATA_MOVE2PP:
    case MON_DATA_MOVE3PP:
    case MON_DATA_MOVE4PP:
        if (blockB->movePP[attr - MON_DATA_MOVE1PP] + value > WazaGetMaxPp(blockB->moves[attr - MON_DATA_MOVE1PP], blockB->movePpUps[attr - MON_DATA_MOVE1PP]))
            blockB->movePP[attr - MON_DATA_MOVE1PP] = (u8)WazaGetMaxPp(blockB->moves[attr - MON_DATA_MOVE1PP], blockB->movePpUps[attr - MON_DATA_MOVE1PP]);
        else
            blockB->movePP[attr - MON_DATA_MOVE1PP] += value;
        break;
    case MON_DATA_MOVE1PPUP:
    case MON_DATA_MOVE2PPUP:
    case MON_DATA_MOVE3PPUP:
    case MON_DATA_MOVE4PPUP:
        if (blockB->movePpUps[attr - MON_DATA_MOVE1PPUP] + value > 3)
            blockB->movePpUps[attr - MON_DATA_MOVE1PPUP] = 3;
        else
            blockB->movePpUps[attr - MON_DATA_MOVE1PPUP] += value;
        break;
    case MON_DATA_MOVE1MAXPP:
    case MON_DATA_MOVE2MAXPP:
    case MON_DATA_MOVE3MAXPP:
    case MON_DATA_MOVE4MAXPP:
        break;
    case MON_DATA_HP_IV:
        if (blockB->hpIV + value > 31)
            blockB->hpIV = 31;
        else
            blockB->hpIV += value;
        break;
    case MON_DATA_ATK_IV:
        if (blockB->atkIV + value > 31)
            blockB->atkIV = 31;
        else
            blockB->atkIV += value;
        break;
    case MON_DATA_DEF_IV:
        if (blockB->defIV + value > 31)
            blockB->defIV = 31;
        else
            blockB->defIV += value;
        break;
    case MON_DATA_SPEED_IV:
        if (blockB->spdIV + value > 31)
            blockB->spdIV = 31;
        else
            blockB->spdIV += value;
        break;
    case MON_DATA_SPATK_IV:
        if (blockB->spatkIV + value > 31)
            blockB->spatkIV = 31;
        else
            blockB->spatkIV += value;
        break;
    case MON_DATA_SPDEF_IV:
        if (blockB->spdefIV + value > 31)
            blockB->spdefIV = 31;
        else
            blockB->spdefIV += value;
        break;
    case MON_DATA_PERSONALITY:
    case MON_DATA_PARTY_LOCK:
    case MON_DATA_BOX_LOCK:
    case MON_DATA_CHECKSUM_FAILED:
    case MON_DATA_CHECKSUM:
    case MON_DATA_SPECIES:
    case MON_DATA_HELD_ITEM:
    case MON_DATA_OTID:
    case MON_DATA_ABILITY:
    case MON_DATA_MARKINGS:
    case MON_DATA_GAME_LANGUAGE:
    case MON_DATA_SINNOH_CHAMP_RIBBON:
    case MON_DATA_ABILITY_RIBBON:
    case MON_DATA_GREAT_ABILITY_RIBBON:
    case MON_DATA_DOUBLE_ABILITY_RIBBON:
    case MON_DATA_MULTI_ABILITY_RIBBON:
    case MON_DATA_PAIR_ABILITY_RIBBON:
    case MON_DATA_WORLD_ABILITY_RIBBON:
    case MON_DATA_ALERT_RIBBON:
    case MON_DATA_SHOCK_RIBBON:
    case MON_DATA_DOWNCAST_RIBBON:
    case MON_DATA_CARELESS_RIBBON:
    case MON_DATA_RELAX_RIBBON:
    case MON_DATA_SNOOZE_RIBBON:
    case MON_DATA_SMILE_RIBBON:
    case MON_DATA_GORGEOUS_RIBBON:
    case MON_DATA_ROYAL_RIBBON:
    case MON_DATA_GORGEOUS_ROYAL_RIBBON:
    case MON_DATA_FOOTPRINT_RIBBON:
    case MON_DATA_RECORD_RIBBON:
    case MON_DATA_HISTORY_RIBBON:
    case MON_DATA_LEGEND_RIBBON:
    case MON_DATA_RED_RIBBON:
    case MON_DATA_GREEN_RIBBON:
    case MON_DATA_BLUE_RIBBON:
    case MON_DATA_FESTIVAL_RIBBON:
    case MON_DATA_CARNIVAL_RIBBON:
    case MON_DATA_CLASSIC_RIBBON:
    case MON_DATA_PREMIER_RIBBON:
    case MON_DATA_SINNOH_RIBBON_53:
    case MON_DATA_MOVE1:
    case MON_DATA_MOVE2:
    case MON_DATA_MOVE3:
    case MON_DATA_MOVE4:
    case MON_DATA_IS_EGG:
    case MON_DATA_HAS_NICKNAME:
    case MON_DATA_HOENN_COOL_RIBBON:
    case MON_DATA_HOENN_COOL_RIBBON_SUPER:
    case MON_DATA_HOENN_COOL_RIBBON_HYPER:
    case MON_DATA_HOENN_COOL_RIBBON_MASTER:
    case MON_DATA_HOENN_BEAUTY_RIBBON:
    case MON_DATA_HOENN_BEAUTY_RIBBON_SUPER:
    case MON_DATA_HOENN_BEAUTY_RIBBON_HYPER:
    case MON_DATA_HOENN_BEAUTY_RIBBON_MASTER:
    case MON_DATA_HOENN_CUTE_RIBBON:
    case MON_DATA_HOENN_CUTE_RIBBON_SUPER:
    case MON_DATA_HOENN_CUTE_RIBBON_HYPER:
    case MON_DATA_HOENN_CUTE_RIBBON_MASTER:
    case MON_DATA_HOENN_SMART_RIBBON:
    case MON_DATA_HOENN_SMART_RIBBON_SUPER:
    case MON_DATA_HOENN_SMART_RIBBON_HYPER:
    case MON_DATA_HOENN_SMART_RIBBON_MASTER:
    case MON_DATA_HOENN_TOUGH_RIBBON:
    case MON_DATA_HOENN_TOUGH_RIBBON_SUPER:
    case MON_DATA_HOENN_TOUGH_RIBBON_HYPER:
    case MON_DATA_HOENN_TOUGH_RIBBON_MASTER:
    case MON_DATA_HOENN_CHAMPION_RIBBON:
    case MON_DATA_HOENN_WINNING_RIBBON:
    case MON_DATA_HOENN_VICTORY_RIBBON:
    case MON_DATA_HOENN_ARTIST_RIBBON:
    case MON_DATA_HOENN_EFFORT_RIBBON:
    case MON_DATA_HOENN_MARINE_RIBBON:
    case MON_DATA_HOENN_LAND_RIBBON:
    case MON_DATA_HOENN_SKY_RIBBON:
    case MON_DATA_HOENN_COUNTRY_RIBBON:
    case MON_DATA_HOENN_NATIONAL_RIBBON:
    case MON_DATA_HOENN_EARTH_RIBBON:
    case MON_DATA_HOENN_WORLD_RIBBON:
    case MON_DATA_FATEFUL_ENCOUNTER:
    case MON_DATA_GENDER:
    case MON_DATA_FORME:
    case MON_DATA_RESERVED_113:
    case MON_DATA_RESERVED_114:
    case MON_DATA_UNUSED_115:
    case MON_DATA_NICKNAME:
    case MON_DATA_NICKNAME_2:
    case MON_DATA_NICKNAME_3:
    case MON_DATA_NICKNAME_4:
    case MON_DATA_UNK_120:
    case MON_DATA_GAME_VERSION:
    case MON_DATA_COOL_RIBBON:
    case MON_DATA_COOL_RIBBON_GREAT:
    case MON_DATA_COOL_RIBBON_ULTRA:
    case MON_DATA_COOL_RIBBON_MASTER:
    case MON_DATA_BEAUTY_RIBBON:
    case MON_DATA_BEAUTY_RIBBON_GREAT:
    case MON_DATA_BEAUTY_RIBBON_ULTRA:
    case MON_DATA_BEAUTY_RIBBON_MASTER:
    case MON_DATA_CUTE_RIBBON:
    case MON_DATA_CUTE_RIBBON_GREAT:
    case MON_DATA_CUTE_RIBBON_ULTRA:
    case MON_DATA_CUTE_RIBBON_MASTER:
    case MON_DATA_SMART_RIBBON:
    case MON_DATA_SMART_RIBBON_GREAT:
    case MON_DATA_SMART_RIBBON_ULTRA:
    case MON_DATA_SMART_RIBBON_MASTER:
    case MON_DATA_TOUGH_RIBBON:
    case MON_DATA_TOUGH_RIBBON_GREAT:
    case MON_DATA_TOUGH_RIBBON_ULTRA:
    case MON_DATA_TOUGH_RIBBON_MASTER:
    case MON_DATA_SINNOH_RIBBON_142:
    case MON_DATA_OT_NAME:
    case MON_DATA_OT_NAME_2:
    case MON_DATA_EGG_MET_YEAR:
    case MON_DATA_EGG_MET_MONTH:
    case MON_DATA_EGG_MET_DAY:
    case MON_DATA_MET_YEAR:
    case MON_DATA_MET_MONTH:
    case MON_DATA_MET_DAY:
    case MON_DATA_EGG_MET_LOCATION:
    case MON_DATA_MET_LOCATION:
    case MON_DATA_POKERUS:
    case MON_DATA_POKEBALL:
    case MON_DATA_MET_LEVEL:
    case MON_DATA_MET_GENDER:
    case MON_DATA_ENCOUNTER_TYPE:
    case MON_DATA_RESERVED_158:
    case MON_DATA_STATUS:
    case MON_DATA_LEVEL:
    case MON_DATA_CAPSULE:
    case MON_DATA_HP:
    case MON_DATA_MAXHP:
    case MON_DATA_ATK:
    case MON_DATA_DEF:
    case MON_DATA_SPEED:
    case MON_DATA_SPATK:
    case MON_DATA_SPDEF:
    case MON_DATA_MAIL_STRUCT:
    case MON_DATA_SEAL_COORDS:
    case MON_DATA_SPECIES_EXISTS:
    case MON_DATA_SANITY_IS_EGG:
    case MON_DATA_SPECIES2:
    case MON_DATA_IVS_WORD:
    case MON_DATA_UNK_175:
    case MON_DATA_TYPE_1:
    case MON_DATA_TYPE_2:
    case MON_DATA_SPECIES_NAME:
    default:
        GF_ASSERT(0);
    }
}

struct BaseStats * AllocAndLoadMonPersonal(int species, u32 heap_id)
{
    struct BaseStats * baseStats = (struct BaseStats *)AllocFromHeap(heap_id, sizeof(struct BaseStats));
    LoadMonPersonal(species, baseStats);
    return baseStats;
}

int GetPersonalAttr(struct BaseStats * baseStats, enum BaseStat attr)
{
    int ret;
    GF_ASSERT(baseStats != NULL);
    switch (attr)
    {
    case BASE_HP:
        ret = baseStats->hp;
        break;
    case BASE_ATK:
        ret = baseStats->atk;
        break;
    case BASE_DEF:
        ret = baseStats->def;
        break;
    case BASE_SPEED:
        ret = baseStats->speed;
        break;
    case BASE_SPATK:
        ret = baseStats->spatk;
        break;
    case BASE_SPDEF:
        ret = baseStats->spdef;
        break;
    case BASE_TYPE1:
        ret = baseStats->types[0];
        break;
    case BASE_TYPE2:
        ret = baseStats->types[1];
        break;
    case BASE_CATCH_RATE:
        ret = baseStats->catchRate;
        break;
    case BASE_EXP_YIELD:
        ret = baseStats->expYield;
        break;
    case BASE_HP_YIELD:
        ret = baseStats->hp_yield;
        break;
    case BASE_ATK_YIELD:
        ret = baseStats->atk_yield;
        break;
    case BASE_DEF_YIELD:
        ret = baseStats->def_yield;
        break;
    case BASE_SPEED_YIELD:
        ret = baseStats->speed_yield;
        break;
    case BASE_SPATK_YIELD:
        ret = baseStats->spatk_yield;
        break;
    case BASE_SPDEF_YIELD:
        ret = baseStats->spdef_yield;
        break;
    case BASE_ITEM_1:
        ret = baseStats->item1;
        break;
    case BASE_ITEM_2:
        ret = baseStats->item2;
        break;
    case BASE_GENDER_RATIO:
        ret = baseStats->genderRatio;
        break;
    case BASE_EGG_CYCLES:
        ret = baseStats->eggCycles;
        break;
    case BASE_FRIENDSHIP:
        ret = baseStats->friendship;
        break;
    case BASE_GROWTH_RATE:
        ret = baseStats->growthRate;
        break;
    case BASE_EGG_GROUP_1:
        ret = baseStats->eggGroups[0];
        break;
    case GASE_EGG_GROUP_2:
        ret = baseStats->eggGroups[1];
        break;
    case BASE_ABILITY_1:
        ret = baseStats->abilities[0];
        break;
    case BASE_ABILITY_2:
        ret = baseStats->abilities[1];
        break;
    case BASE_GREAT_MARSH_RATE:
        ret = baseStats->greatMarshRate;
        break;
    case BASE_COLOR:
        ret = baseStats->color;
        break;
    case BASE_FLIP:
        ret = baseStats->flip;
        break;
    case BASE_TMHM_1:
        ret = (int)baseStats->unk1C;
        break;
    case BASE_TMHM_2:
        ret = (int)baseStats->unk20;
        break;
    case BASE_TMHM_3:
        ret = (int)baseStats->unk24;
        break;
    case BASE_TMHM_4:
        ret = (int)baseStats->unk28;
        break;
    }
    return ret;
}

void FreeMonPersonal(struct BaseStats * personal)
{
    GF_ASSERT(personal != NULL);
    FreeToHeap(personal);
}

int GetMonBaseStat_HandleFormeConversion(int species, int forme, enum BaseStat attr)
{
    int ret;
    struct BaseStats * personal = AllocAndLoadMonPersonal(ResolveMonForme(species, forme), 0);
    ret = GetPersonalAttr(personal, attr);
    FreeMonPersonal(personal);
    return ret;
}

int GetMonBaseStat(int species, enum BaseStat attr)
{
    int ret;
    struct BaseStats * personal = AllocAndLoadMonPersonal(species, 0);
    ret = GetPersonalAttr(personal, attr);
    FreeMonPersonal(personal);
    return ret;
}

u8 GetPercentProgressTowardsNextLevel(struct Pokemon * pokemon)
{
    BOOL decry = AcquireMonLock(pokemon);
    u16 species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, NULL);
    u8 level = (u8)GetMonData(pokemon, MON_DATA_LEVEL, NULL);
    u32 lo = GetMonExpBySpeciesAndLevel(species, level);
    u32 hi = GetMonExpBySpeciesAndLevel(species, level + 1);
    u32 cur = GetMonData(pokemon, MON_DATA_EXPERIENCE, NULL);
    ReleaseMonLock(pokemon, decry);
    return (u8)(100 * (cur - lo) / (hi - lo));
}

u32 CalcMonExpToNextLevel(struct Pokemon * pokemon)
{
    return CalcBoxMonExpToNextLevel(&pokemon->box);
}

u32 CalcBoxMonExpToNextLevel(struct BoxPokemon * boxmon)
{
    u16 species = (u16)GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL);
    u16 level = (u16)(CalcBoxMonLevel(boxmon) + 1);
    u32 cur = GetBoxMonData(boxmon, MON_DATA_EXPERIENCE, NULL);
    u32 hi = GetMonExpBySpeciesAndLevel(species, level);
    return hi - cur;
}

u32 GetMonBaseExperienceAtCurrentLevel(struct Pokemon * pokemon)
{
    int species = (int)GetMonData(pokemon, MON_DATA_SPECIES, NULL);
    int level = (int)GetMonData(pokemon, MON_DATA_LEVEL, NULL);
    return GetMonExpBySpeciesAndLevel(species, level);
}

u32 GetMonExpBySpeciesAndLevel(int species, int level)
{
    return GetExpByGrowthRateAndLevel(GetMonBaseStat(species, BASE_GROWTH_RATE), level);
}

void LoadGrowthTable(int growthRate, u32 * dest)
{
    GF_ASSERT(growthRate < 8);
    ReadWholeNarcMemberByIdPair(dest, NARC_POKETOOL_PERSONAL_GROWTBL, growthRate);
}

u32 GetExpByGrowthRateAndLevel(int growthRate, int level)
{
    u32 * table;
    u32 ret;
    GF_ASSERT(growthRate < 8);
    GF_ASSERT(level <= 101);
    table = (u32 *)AllocFromHeap(0, 101 * sizeof(u32));
    LoadGrowthTable(growthRate, table);
    ret = table[level];
    FreeToHeap(table);
    return ret;
}

int CalcMonLevel(struct Pokemon * pokemon)
{
    return CalcBoxMonLevel(&pokemon->box);
}

int CalcBoxMonLevel(struct BoxPokemon * boxmon)
{
    BOOL decry = AcquireBoxMonLock(boxmon);
    int species = (int)GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL);
    int exp = (int)GetBoxMonData(boxmon, MON_DATA_EXPERIENCE, NULL);
    ReleaseBoxMonLock(boxmon, decry);
    return CalcLevelBySpeciesAndExp((u16)species, (u32)exp);
}

int CalcLevelBySpeciesAndExp(u16 species, u32 exp)
{
    int level;
    struct BaseStats * personal = AllocAndLoadMonPersonal(species, 0);
    level = CalcLevelBySpeciesAndExp_PreloadedPersonal(personal, species, exp);
    FreeMonPersonal(personal);
    return level;
}

int CalcLevelBySpeciesAndExp_PreloadedPersonal(struct BaseStats * personal, u16 species, u32 exp)
{
#pragma unused(species)
    static u32 table[101];
    int i;
    LoadGrowthTable(GetPersonalAttr(personal, BASE_GROWTH_RATE), table);
    for (i = 1; i < 101; i++)
    {
        if (table[i] > exp)
            break;
    }
    return i - 1;
}

u8 GetMonNature(struct Pokemon * pokemon)
{
    return GetBoxMonNature(&pokemon->box);
}

u8 GetBoxMonNature(struct BoxPokemon * boxmon)
{
    BOOL decry = AcquireBoxMonLock(boxmon);
    u32 personality = GetBoxMonData(boxmon, MON_DATA_PERSONALITY, NULL);
    ReleaseBoxMonLock(boxmon, decry);
    return GetNatureFromPersonality(personality);
}

u8 GetNatureFromPersonality(u32 pid)
{
    return (u8)(pid % 25);
}

u16 ModifyStatByNature(u8 nature, u16 n, u8 statIndex)
{
    u16 retVal;

    // Dont modify HP, Accuracy, or Evasion by nature
    if (statIndex < 1 || statIndex > 5)
        return n;

    switch (sNatureStatMods[nature][statIndex - 1])
    {
    case 1:
        retVal = (u16)((u16)(n * 110) / 100); // NOTE: will overflow for n > 595 because the intermediate value is cast to u16 before the division. Fix by removing (u16) cast
        break;
    case -1:
        retVal = (u16)((u16)(n * 90) / 100); // NOTE: will overflow for n > 728, see above
        break;
    default:
        retVal = n;
        break;
    }
    return retVal;
}

void MonApplyFriendshipMod(struct Pokemon * pokemon, u32 kind, u32 location)
{
    u16 species;
    u8 effect;
    u8 r4;
    s16 friendship;
    s8 mod;

    if (kind == 5 && (LCRandom() & 1))
        return;

    species = (u16)GetMonData(pokemon, MON_DATA_SPECIES2, NULL);
    if (species == SPECIES_NONE || species == SPECIES_EGG)
        return;

    effect = (u8)GetItemAttr((u16)GetMonData(pokemon, MON_DATA_HELD_ITEM, NULL), 1, 0);
    r4 = 0;
    friendship = (s16)GetMonData(pokemon, MON_DATA_FRIENDSHIP, NULL);
    if (friendship >= 100)
        r4++;
    if (friendship >= 200)
        r4++;
    mod = sFriendshipModTable[kind][r4];
    if (mod > 0 && GetMonData(pokemon, MON_DATA_POKEBALL, NULL) == ITEM_LUXURY_BALL)
        mod++;
    if (mod > 0 && GetMonData(pokemon, MON_DATA_EGG_MET_LOCATION, NULL) == location)
        mod++;
    if (mod > 0 && effect == 52) // Soothe Bell effect?
        mod = (s8)(mod * 150 / 100);
    friendship += mod;
    if (friendship < 0)
        friendship = 0;
    if (friendship > 255)
        friendship = 255;
    SetMonData(pokemon, MON_DATA_FRIENDSHIP, &friendship);
}

u8 GetMonGender(struct Pokemon * pokemon)
{
    return GetBoxMonGender(&pokemon->box);
}

u8 GetBoxMonGender(struct BoxPokemon * boxmon)
{
    BOOL decry = AcquireBoxMonLock(boxmon);
    u16 species = (u16)GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL);
    u32 personality = GetBoxMonData(boxmon, MON_DATA_PERSONALITY, NULL);
    ReleaseBoxMonLock(boxmon, decry);
    return GetGenderBySpeciesAndPersonality(species, personality);
}

u8 GetGenderBySpeciesAndPersonality(u16 species, u32 pid)
{
    struct BaseStats * personal = AllocAndLoadMonPersonal(species, 0);
    u8 gender = GetGenderBySpeciesAndPersonality_PreloadedPersonal(personal, species, pid);
    FreeMonPersonal(personal);
    return gender;
}

u8 GetGenderBySpeciesAndPersonality_PreloadedPersonal(struct BaseStats * personal, u16 species, u32 pid)
{
#pragma unused(species)
    u8 ratio = (u8)GetPersonalAttr(personal, BASE_GENDER_RATIO);
    switch (ratio)
    {
    case MON_RATIO_MALE:
        return MON_MALE;
    case MON_RATIO_FEMALE:
        return MON_FEMALE;
    case MON_RATIO_UNKNOWN:
        return MON_GENDERLESS;
    default:
        if (ratio > (u8)pid)
            return MON_FEMALE;
        else
            return MON_MALE;
    }
}

u8 MonIsShiny(struct Pokemon * pokemon)
{
    return BoxMonIsShiny(&pokemon->box);
}

u8 BoxMonIsShiny(struct BoxPokemon * boxmon)
{
    u32 otid = GetBoxMonData(boxmon, MON_DATA_OTID, NULL);
    u32 pid = GetBoxMonData(boxmon, MON_DATA_PERSONALITY, NULL);
    return CalcShininessByOtIdAndPersonality(otid, pid);
}

u8 CalcShininessByOtIdAndPersonality(u32 otid, u32 pid)
{
    return SHINY_CHECK(otid, pid);
}

u32 GenerateShinyPersonality(u32 otid)
{
    int r4;
    u16 r6;
    u16 r5;
    otid = (u32)((((otid & 0xFFFF0000) >> 16) ^ (otid & 0xFFFF)) >> 3u);
    r6 = (u16)(LCRandom() & 7);
    r5 = (u16)(LCRandom() & 7);
    for (r4 = 0; r4 < 13; r4++)
    {
        if (MaskOfFlagNo(r4) & otid)
        {
            if (LCRandom() & 1)
                r6 |= MaskOfFlagNo(r4 + 3);
            else
                r5 |= MaskOfFlagNo(r4 + 3);
        }
        else if (LCRandom() & 1)
        {
            r6 |= MaskOfFlagNo(r4 + 3);
            r5 |= MaskOfFlagNo(r4 + 3);
        }
    }
    return (u32)((r5 << 16) | r6);
}

void FUN_02068B68(struct SomeDrawPokemonStruct * spC, struct Pokemon * pokemon, u8 sp10)
{
    FUN_02068B70(spC, &pokemon->box, sp10);
}

void FUN_02068B70(struct SomeDrawPokemonStruct * spC, struct BoxPokemon * boxmon, u8 sp10)
{
    BOOL decry = AcquireBoxMonLock(boxmon);
    u16 species = (u16)GetBoxMonData(boxmon, MON_DATA_SPECIES2, NULL);
    u8 gender = GetBoxMonGender(boxmon);
    u8 shiny = BoxMonIsShiny(boxmon);
    u32 personality = GetBoxMonData(boxmon, MON_DATA_PERSONALITY, NULL);
    u8 forme;
    if (species == SPECIES_EGG)
    {
        if (GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL) == SPECIES_MANAPHY)
            forme = 1;
        else
            forme = 0;
    }
    else
        forme = (u8)GetBoxMonData(boxmon, MON_DATA_FORME, NULL);
    FUN_02068C00(spC, species, gender, sp10, shiny, forme, personality);
    ReleaseBoxMonLock(boxmon, decry);
}

void FUN_02068C00(struct SomeDrawPokemonStruct * spC, int species, u8 gender, u8 sp10, u8 shiny, u8 forme, u32 personality)
{
    spC->unk6 = 0;
    spC->unk8 = 0;
    spC->unkC = 0;
    switch (species)
    {
    case SPECIES_BURMY:
        if (forme > 2)
            forme = 0;
        spC->unk0 = NARC_POKETOOL_POKEGRA_OTHERPOKE;
        spC->unk2 = (u16)(sp10 / 2 + 0x48 + forme * 2);
        spC->unk4 = (u16)(shiny + 0x92 + forme * 2);
        break;
    case SPECIES_WORMADAM:
        if (forme > 2)
            forme = 0;
        spC->unk0 = NARC_POKETOOL_POKEGRA_OTHERPOKE;
        spC->unk2 = (u16)(sp10 / 2 + 0x4E + forme * 2);
        spC->unk4 = (u16)(shiny + 0x98 + forme * 2);
        break;
    case SPECIES_SHELLOS:
        if (forme > 1)
            forme = 0;
        spC->unk0 = NARC_POKETOOL_POKEGRA_OTHERPOKE;
        spC->unk2 = (u16)(sp10 + 0x54 + forme);
        spC->unk4 = (u16)(shiny + 0x9E + forme * 2);
        break;
    case SPECIES_GASTRODON:
        if (forme > 1)
            forme = 0;
        spC->unk0 = NARC_POKETOOL_POKEGRA_OTHERPOKE;
        spC->unk2 = (u16)(sp10 + 0x58 + forme);
        spC->unk4 = (u16)(shiny + 0xA2 + forme * 2);
        break;
    case SPECIES_CHERRIM:
        if (forme > 1)
            forme = 0;
        spC->unk0 = NARC_POKETOOL_POKEGRA_OTHERPOKE;
        spC->unk2 = (u16)(sp10 + 0x5C + forme);
        spC->unk4 = (u16)(shiny * 2 + 0xA6 + forme);
        break;
    case SPECIES_ARCEUS:
        if (forme > 17)
            forme = 0;
        spC->unk0 = NARC_POKETOOL_POKEGRA_OTHERPOKE;
        spC->unk2 = (u16)(sp10 / 2 + 0x60 + forme * 2);
        spC->unk4 = (u16)(shiny + 0xAA + forme * 2);
        break;
    case SPECIES_CASTFORM:
        if (forme > 3)
            forme = 0;
        spC->unk0 = NARC_POKETOOL_POKEGRA_OTHERPOKE;
        spC->unk2 = (u16)(sp10 * 2 + 0x40 + forme);
        spC->unk4 = (u16)(shiny * 4 + 0x8A + forme);
        break;
    case SPECIES_DEOXYS:
        if (forme > 3)
            forme = 0;
        spC->unk0 = NARC_POKETOOL_POKEGRA_OTHERPOKE;
        spC->unk2 = (u16)(sp10 / 2 + forme * 2);
        spC->unk4 = (u16)(shiny + 0x86);
        break;
    case SPECIES_UNOWN:
        if (forme >= 28)
            forme = 0;
        spC->unk0 = NARC_POKETOOL_POKEGRA_OTHERPOKE;
        spC->unk2 = (u16)(sp10 / 2 + 0x8 + forme * 2);
        spC->unk4 = (u16)(shiny + 0x88);
        break;
    case SPECIES_EGG:
        if (forme > 1)
            forme = 0;
        spC->unk0 = NARC_POKETOOL_POKEGRA_OTHERPOKE;
        spC->unk2 = (u16)(0x84 + forme);
        spC->unk4 = (u16)(0xCE + forme);
        break;
    case SPECIES_MANAPHY_EGG:
        spC->unk0 = NARC_POKETOOL_POKEGRA_OTHERPOKE;
        spC->unk2 = 0x84;
        spC->unk4 = 0xCE;
        break;
    default:
        spC->unk0 = 0x4;
        spC->unk2 = (u16)(species * 6 + sp10 + (gender == MON_FEMALE ? 0 : 1));
        spC->unk4 = (u16)(shiny + (species * 6 + 4));
        if (species == SPECIES_SPINDA && sp10 == 2)
        {
            spC->unk6 = SPECIES_SPINDA;
            spC->unk8 = 0;
            spC->unkC = personality;
        }
        break;
    }
}

u8 FUN_02068E14(struct Pokemon * pokemon, u32 a1)
{
    return FUN_02068E1C(&pokemon->box, a1);
}

u8 FUN_02068E1C(struct BoxPokemon * boxmon, u32 a1)
{
    u16 species = (u16)GetBoxMonData(boxmon, MON_DATA_SPECIES2, NULL);
    u8 gender = GetBoxMonGender(boxmon);
    u32 pid = GetBoxMonData(boxmon, MON_DATA_PERSONALITY, NULL);
    u8 forme;
    if (species == SPECIES_EGG)
    {
        if (GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL) == SPECIES_MANAPHY)
            forme = 1;
        else
            forme = 0;
    }
    else
        forme = (u8)GetBoxMonData(boxmon, MON_DATA_FORME, NULL);
    return FUN_02068E88(species, gender, a1, forme, pid);
}

u8 FUN_02068E88(int species, u8 gender, u32 a1, u8 forme, u32 pid)
{
#pragma unused(pid)
    u8 ret;
    s32 fileId;
    enum NarcId narc;
    switch (species)
    {
    case SPECIES_BURMY:
        if (forme > 2)
            forme = 0;
        narc = NARC_POKETOOL_POKEGRA_HEIGHT_O;
        fileId = (s32)(a1 / 2 + 0x48 + forme * 2);
        break;
    case SPECIES_WORMADAM:
        if (forme > 2)
            forme = 0;
        narc = NARC_POKETOOL_POKEGRA_HEIGHT_O;
        fileId = (s32)(a1 / 2 + 0x4E + forme * 2);
        break;
    case SPECIES_SHELLOS:
        if (forme > 1)
            forme = 0;
        narc = NARC_POKETOOL_POKEGRA_HEIGHT_O;
        fileId = (s32)(a1 + 0x54 + forme);
        break;
    case SPECIES_GASTRODON:
        if (forme > 1)
            forme = 0;
        narc = NARC_POKETOOL_POKEGRA_HEIGHT_O;
        fileId = (s32)(a1 + 0x58 + forme);
        break;
    case SPECIES_CHERRIM:
        if (forme > 1)
            forme = 0;
        narc = NARC_POKETOOL_POKEGRA_HEIGHT_O;
        fileId = (s32)(a1 + 0x5C + forme);
        break;
    case SPECIES_ARCEUS:
        if (forme > 17)
            forme = 0;
        narc = NARC_POKETOOL_POKEGRA_HEIGHT_O;
        fileId = (s32)(a1 / 2 + 0x60 + 2 * forme);
        break;
    case SPECIES_CASTFORM:
        if (forme > 3)
            forme = 0;
        narc = NARC_POKETOOL_POKEGRA_HEIGHT_O;
        fileId = (s32)(a1 * 2 + 0x40 + forme);
        break;
    case SPECIES_DEOXYS:
        if (forme > 3)
            forme = 0;
        narc = NARC_POKETOOL_POKEGRA_HEIGHT_O;
        fileId = (s32)(a1 / 2 + forme * 2);
        break;
    case SPECIES_UNOWN:
        if (forme >= 28)
            forme = 0;
        narc = NARC_POKETOOL_POKEGRA_HEIGHT_O;
        fileId = (s32)(a1 / 2 + 0x8 + forme * 2);
        break;
    case SPECIES_EGG:
        if (forme > 1)
            forme = 0;
        narc = NARC_POKETOOL_POKEGRA_HEIGHT_O;
        fileId = (s32)(0x84 + forme);
        break;
    case SPECIES_MANAPHY_EGG:
        narc = NARC_POKETOOL_POKEGRA_HEIGHT_O;
        fileId = 0x84;
        break;
    default:
        narc = NARC_POKETOOL_POKEGRA_HEIGHT;
        fileId = (s32)(4 * species + a1 + (gender != MON_FEMALE ? 1 : 0));
        break;
    }
    ReadWholeNarcMemberByIdPair(&ret, narc, fileId);
    return ret;
}

void FUN_02068FE0(struct SomeDrawPokemonStruct * a0, u16 a1, int a2)
{
    if (a2 == 2)
        a0->unk0 = NARC_POKETOOL_TRGRA_TRFGRA;
    else
    {
        a0->unk0 = NARC_POKETOOL_TRGRA_TRBGRA;
        a1 = (u16)FUN_0206AA30(a1);
    }
    a0->unk2 = (u16)(a1 * 2);
    a0->unk4 = (u16)(a1 * 2 + 1);
    a0->unk6 = 0;
    a0->unk8 = 0;
    a0->unkC = 0;
}

void FUN_02069010(void * dest, int a1)
{
    struct Pokeanm buffer;
    ReadFromNarcMemberByIdPair(&buffer, NARC_POKETOOL_POKEANM_POKEANM, 0, (u32)(28 * a1), 28);
    MI_CpuCopy8(buffer.unk8, dest, 20);
}

void FUN_02069038(u32 a0, u32 a1, u32 a2, s32 a3, u32 a4, u32 a5, u32 a6)
{
    struct UnkStruct_02069038 sp4;
    ReadFromNarcMemberByIdPair(&sp4.anim, NARC_POKETOOL_POKEANM_POKEANM, 0, (u32)(a2 * 28), 28);
    if (a3 == 2)
    {
        sp4.unk0 = sp4.anim.unk0[0].unk0;
        sp4.unk2 = sp4.anim.unk0[0].unk1;
        sp4.unk4 = (u8)a5;
    }
    else
    {
        a3 = FUN_02014C3C((u8)a4);
        GF_ASSERT(a3 < 3);
        sp4.unk0 = sp4.anim.unk0[a3 + 1].unk0;
        sp4.unk2 = sp4.anim.unk0[a3 + 1].unk1;
        sp4.unk4 = (u8)a5;
    }
    FUN_02014C54((int)a0, (int)a1, &sp4, (u8)a6);
}

void FUN_020690AC(struct SomeDrawPokemonStruct * a0, u32 a1)
{
    a0->unk0 = NARC_POKETOOL_TRGRA_TRFGRA;
    a0->unk2 = (u16)(a1 * 2);
    a0->unk4 = (u16)(a1 * 2 + 1);
    a0->unk6 = 0;
    a0->unk8 = 0;
    a0->unkC = 0;
}

u32 FUN_020690C4(void)
{
    return sizeof(struct Pokemon);
}

u32 FUN_020690C8(void)
{
    return sizeof(struct BoxPokemon);
}

u8 GetMonUnownLetter(struct Pokemon * pokemon)
{
    return GetBoxMonUnownLetter(&pokemon->box);
}

u8 GetBoxMonUnownLetter(struct BoxPokemon * boxmon)
{
    return (u8)GetBoxMonData(boxmon, MON_DATA_FORME, NULL);
}

struct BoxPokemon * FUN_020690E4(struct Pokemon * pokemon)
{
    return &pokemon->box;
}

BOOL FUN_020690E8(struct Pokemon * pokemon)
{
    u16 species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, NULL);
    u8 level = (u8)(GetMonData(pokemon, MON_DATA_LEVEL, NULL) + 1);
    u32 exp = GetMonData(pokemon, MON_DATA_EXPERIENCE, NULL);
    u32 growthrate = (u32)GetMonBaseStat(species, BASE_GROWTH_RATE);
    u32 maxexp = GetExpByGrowthRateAndLevel((int)growthrate, 100);
    if (exp > maxexp)
    {
        exp = maxexp;
        SetMonData(pokemon, MON_DATA_EXPERIENCE, &exp);
    }
    if (level > 100)
        return FALSE;
    if (exp >= GetExpByGrowthRateAndLevel((int)growthrate, level))
    {
        SetMonData(pokemon, MON_DATA_LEVEL, &level);
        return TRUE;
    }
    return FALSE;
}

u16 GetMonEvolution(struct PlayerParty * party, struct Pokemon * pokemon, u32 context, u32 usedItem, u32 * method_ret)
{
    u16 target = SPECIES_NONE;
    u32 sp40;
    u16 species;
    u16 heldItem;
    u32 personality;
    int i;
    u8 beauty;
    u8 level;
    u16 friendship;
    u16 pid_hi;
    struct Evolution * evoTable;
    u8 r1;

    species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, NULL);
    heldItem = (u16)GetMonData(pokemon, MON_DATA_HELD_ITEM, NULL);
    personality = GetMonData(pokemon, MON_DATA_PERSONALITY, NULL);
    beauty = (u8)GetMonData(pokemon, MON_DATA_BEAUTY, NULL);
    pid_hi = (u16)((personality & 0xFFFF0000) >> 16);
    r1 = (u8)GetItemAttr(heldItem, 1, 0);
    if (species != SPECIES_KADABRA && r1 == HOLD_EFFECT_NO_EVOLVE && context != 3)
        return SPECIES_NONE;
    if (method_ret == NULL)
        method_ret = &sp40;
    evoTable = AllocFromHeap(0, 7 * sizeof(struct Evolution));
    LoadMonEvolutionTable(species, evoTable);
    switch (context)
    {
    case 0:
        level = (u8)GetMonData(pokemon, MON_DATA_LEVEL, NULL);
        friendship = (u16)GetMonData(pokemon, MON_DATA_FRIENDSHIP, NULL);
        for (i = 0; i < 7; i++)
        {
            switch (evoTable[i].method)
            {
            case EVO_NONE:
                break;
            case EVO_FRIENDSHIP:
                if (friendship >= 220)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_FRIENDSHIP;
                }
                break;
            case EVO_FRIENDSHIP_DAY:
                if (IsNighttime() == 0 && friendship >= 220)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_FRIENDSHIP_DAY;
                }
                break;
            case EVO_FRIENDSHIP_NIGHT:
                if (IsNighttime() == 1 && friendship >= 220)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_FRIENDSHIP_NIGHT;
                }
                break;
            case EVO_LEVEL:
                if (evoTable[i].param <= level)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_LEVEL;
                }
                break;
            case EVO_TRADE:
                break;
            case EVO_TRADE_ITEM:
                break;
            case EVO_STONE:
                break;
            case EVO_LEVEL_ATK_GT_DEF:
                if (evoTable[i].param <= level && GetMonData(pokemon, MON_DATA_ATK, NULL) > GetMonData(pokemon, MON_DATA_DEF, NULL))
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_LEVEL_ATK_GT_DEF;
                }
                break;
            case EVO_LEVEL_ATK_EQ_DEF:
                if (evoTable[i].param <= level && GetMonData(pokemon, MON_DATA_ATK, NULL) == GetMonData(pokemon, MON_DATA_DEF, NULL))
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_LEVEL_ATK_EQ_DEF;
                }
                break;
            case EVO_LEVEL_ATK_LT_DEF:
                if (evoTable[i].param <= level && GetMonData(pokemon, MON_DATA_ATK, NULL) < GetMonData(pokemon, MON_DATA_DEF, NULL))
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_LEVEL_ATK_LT_DEF;
                }
                break;
            case EVO_LEVEL_PID_LO:
                if (evoTable[i].param <= level && pid_hi % 10 < 5)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_LEVEL_PID_LO;
                }
                break;
            case EVO_LEVEL_PID_HI:
                if (evoTable[i].param <= level && pid_hi % 10 >= 5)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_LEVEL_PID_HI;
                }
                break;
            case EVO_LEVEL_NINJASK:
                if (evoTable[i].param <= level)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_LEVEL_NINJASK;
                }
                break;
            case EVO_LEVEL_SHEDINJA:
                *method_ret = EVO_LEVEL_SHEDINJA;
                break;
            case EVO_BEAUTY:
                if (evoTable[i].param <= beauty)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_BEAUTY;
                }
                break;
            case EVO_STONE_MALE:
                break;
            case EVO_STONE_FEMALE:
                break;
            case EVO_ITEM_DAY:
                if (IsNighttime() == 0 && evoTable[i].param == heldItem)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_ITEM_DAY;
                }
                break;
            case EVO_ITEM_NIGHT:
                if (IsNighttime() == 1 && evoTable[i].param == heldItem)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_ITEM_NIGHT;
                }
                break;
            case EVO_HAS_MOVE:
                if (MonHasMove(pokemon, evoTable[i].param) == TRUE)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_HAS_MOVE;
                }
                break;
            case EVO_OTHER_PARTY_MON:
                if (party != NULL && PartyHasMon(party, evoTable[i].param) == 1)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_OTHER_PARTY_MON;
                }
                break;
            case EVO_LEVEL_MALE:
                if (GetMonData(pokemon, MON_DATA_GENDER, NULL) == MON_MALE && evoTable[i].param <= level)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_LEVEL_MALE;
                }
                break;
            case EVO_LEVEL_FEMALE:
                if (GetMonData(pokemon, MON_DATA_GENDER, NULL) == MON_FEMALE && evoTable[i].param <= level)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_LEVEL_FEMALE;
                }
                break;
            case EVO_CORONET:
                if (usedItem == evoTable[i].method)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_CORONET;
                }
                break;
            case EVO_ETERNA:
                if (usedItem == evoTable[i].method)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_ETERNA;
                }
                break;
            case EVO_ROUTE217:
                if (usedItem == evoTable[i].method)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_ROUTE217;
                }
                break;
            }
            if (target != SPECIES_NONE)
                break;
        }
        break;
    case 1:
        for (i = 0; i < 7; i++)
        {
            switch (evoTable[i].method)
            {
            case EVO_TRADE:
                target = evoTable[i].target;
                *method_ret = EVO_TRADE;
                break;
            case EVO_TRADE_ITEM:
                if (heldItem == evoTable[i].param)
                {
                    target = evoTable[i].target;
                    *method_ret = EVO_TRADE_ITEM;
                }
                break;
            }
            if (target != SPECIES_NONE)
                break;
        }
        break;
    case 2:
    case 3:
        for (i = 0; i < 7; i++)
        {
            if (evoTable[i].method == EVO_STONE && usedItem == evoTable[i].param)
            {
                target = evoTable[i].target;
                *method_ret = 0;
                break;
            }
            if (evoTable[i].method == EVO_STONE_MALE && GetMonData(pokemon, MON_DATA_GENDER, NULL) == MON_MALE && usedItem == evoTable[i].param)
            {
                target = evoTable[i].target;
                *method_ret = 0;
                break;
            }
            if (evoTable[i].method == EVO_STONE_FEMALE && GetMonData(pokemon, MON_DATA_GENDER, NULL) == MON_FEMALE && usedItem == evoTable[i].param)
            {
                target = evoTable[i].target;
                *method_ret = 0;
                break;
            }
        }
        break;
    }
    FreeToHeap(evoTable);
    return target;
}

u16 ReadFromPersonalPmsNarc(u16 species)
{
    u16 ret = SPECIES_NONE;
    GF_ASSERT(species < SPECIES_EGG);
    {
    FSFile file;
    FS_InitFile(&file);
    FS_OpenFile(&file, "poketool/personal/pms.narc");
    FS_SeekFile(&file, (s32)(species * sizeof(u16)), FS_SEEK_SET);
    FS_ReadFile(&file, &ret, sizeof(u16));
    FS_CloseFile(&file);
    }
    return ret;
}

u16 GetEggSpecies(u16 species)
{
    switch (species)
    {
    case SPECIES_SUDOWOODO:
    case SPECIES_MARILL:
    case SPECIES_MR_MIME:
    case SPECIES_CHANSEY:
    case SPECIES_SNORLAX:
    case SPECIES_MANTINE:
    case SPECIES_WOBBUFFET:
    case SPECIES_ROSELIA:
    case SPECIES_CHIMECHO:
        return species;
    default:
        return ReadFromPersonalPmsNarc(species);
    }
}

#define WOTBL_END           0xFFFF
#define WOTBL_MOVE_MASK     0x01FF
#define WOTBL_MOVE_SHIFT         0
#define WOTBL_LVL_MASK      0xFE00
#define WOTBL_LVL_SHIFT          9
#define WOTBL_MOVE(x) ((u16)(((x) & WOTBL_MOVE_MASK) >> WOTBL_MOVE_SHIFT))
#define WOTBL_LVL(x) ((u8)(((x) & WOTBL_LVL_MASK) >> WOTBL_LVL_SHIFT))

void InitBoxMonMoveset(struct BoxPokemon * boxmon)
{
    BOOL decry;
    u16 * wotbl;
    int i;
    u16 species;
    u32 forme;
    u8 level;
    u16 move;
    wotbl = AllocFromHeap(0, 22 * sizeof(u16));
    decry = AcquireBoxMonLock(boxmon);
    species = (u16)GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL);
    forme = GetBoxMonData(boxmon, MON_DATA_FORME, NULL);
    level = (u8)CalcBoxMonLevel(boxmon);
    LoadWotbl_HandleAlternateForme(species, (int)forme, wotbl);
    for (i = 0; wotbl[i] != WOTBL_END; i++)
    {
        if ((wotbl[i] & WOTBL_LVL_MASK) > (level << WOTBL_LVL_SHIFT))
            break;
        move = WOTBL_MOVE(wotbl[i]);
        if (FUN_020696A8(boxmon, move) == 0xFFFF)
            FUN_02069718(boxmon, move);
    }
    FreeToHeap(wotbl);
    ReleaseBoxMonLock(boxmon, decry);
}

u32 FUN_02069698(struct Pokemon * pokemon, u16 move)
{
    return FUN_020696A8(FUN_020690E4(pokemon), move);
}

u32 FUN_020696A8(struct BoxPokemon * boxmon, u16 move)
{
    u32 ret = 0xFFFF;
    int i;
    BOOL decry = AcquireBoxMonLock(boxmon);
    u16 cur_move;
    for (i = 0; i < 4; i++)
    {
        cur_move = (u16)GetBoxMonData(boxmon, MON_DATA_MOVE1 + i, NULL);
        if (cur_move == MOVE_NONE)
        {
            BoxMonSetMoveInSlot(boxmon, move, (u8)i);
            ret = move;
            break;
        }
        if (cur_move == move)
        {
            ret = 0xFFFE;
            break;
        }
    }
    ReleaseBoxMonLock(boxmon, decry);
    return ret;
}

void FUN_02069708(struct Pokemon * pokemon, u16 move)
{
    FUN_02069718(FUN_020690E4(pokemon), move);
}

void FUN_02069718(struct BoxPokemon * boxmon, u16 move)
{
    BOOL decry = AcquireBoxMonLock(boxmon);
    int i;
    u16 moves[4];
    u8 pp[4];
    u8 ppUp[4];

    for (i = 0; i < 3; i++)
    {
        moves[i] = (u16)GetBoxMonData(boxmon, MON_DATA_MOVE1 + i + 1, NULL);
        pp[i] = (u8)GetBoxMonData(boxmon, MON_DATA_MOVE1PP + i + 1, NULL);
        ppUp[i] = (u8)GetBoxMonData(boxmon, MON_DATA_MOVE1PPUP + i + 1, NULL);
    }

    moves[3] = move;
    pp[3] = (u8)GetWazaAttr(move, MOVEATTR_PP);
    ppUp[3] = 0;

    for (i = 0; i < 4; i++)
    {
        SetBoxMonData(boxmon, MON_DATA_MOVE1 + i, &moves[i]);
        SetBoxMonData(boxmon, MON_DATA_MOVE1PP + i, &pp[i]);
        SetBoxMonData(boxmon, MON_DATA_MOVE1PPUP + i, &ppUp[i]);
    }

    ReleaseBoxMonLock(boxmon, decry);
}

void MonSetMoveInSlot(struct Pokemon * pokemon, u16 move, u8 slot)
{
    BoxMonSetMoveInSlot(&pokemon->box, move, slot);
}

void BoxMonSetMoveInSlot(struct BoxPokemon * boxmon, u16 move, u8 slot)
{
    u8 ppUp;
    u8 pp;

    SetBoxMonData(boxmon, MON_DATA_MOVE1 + slot, &move);
    ppUp = (u8)GetBoxMonData(boxmon, MON_DATA_MOVE1PPUP + slot, NULL);
    pp = (u8)WazaGetMaxPp(move, ppUp);
    SetBoxMonData(boxmon, MON_DATA_MOVE1PP + slot, &pp);
}

u32 FUN_02069818(struct Pokemon * pokemon, u32 * r5, u16 * sp0)
{
    u32 ret = 0;
    u16 * wotbl = AllocFromHeap(0, 22 * sizeof(u16));
    u16 species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, NULL);
    u32 forme = GetMonData(pokemon, MON_DATA_FORME, NULL);
    u8 level = (u8)GetMonData(pokemon, MON_DATA_LEVEL, NULL);
    LoadWotbl_HandleAlternateForme(species, (int)forme, wotbl);


    if (wotbl[*r5] == 0xFFFF)
    {
        FreeToHeap(wotbl);
        return 0;
    }
    while ((wotbl[*r5] & WOTBL_LVL_MASK) != (level << WOTBL_LVL_SHIFT))
    {
        (*r5)++;
        if (wotbl[*r5] == 0xFFFF)
        {
            FreeToHeap(wotbl);
            return 0;
        }
    }
    if ((wotbl[*r5] & WOTBL_LVL_MASK) == (level << WOTBL_LVL_SHIFT))
    {
        *sp0 = WOTBL_MOVE(wotbl[*r5]);
        (*r5)++;
        ret = FUN_02069698(pokemon, *sp0);
    }
    FreeToHeap(wotbl);
    return ret;
}

void FUN_020698E0(struct Pokemon * pokemon, int slot1, int slot2)
{
    FUN_020698E8(&pokemon->box, slot1, slot2);
}

void FUN_020698E8(struct BoxPokemon * boxmon, int slot1, int slot2)
{
    u16 moves[2];
    u8 pp[2];
    u8 ppUp[2];

    moves[0] = (u16)GetBoxMonData(boxmon, MON_DATA_MOVE1 + slot1, NULL);
    pp[0] = (u8)GetBoxMonData(boxmon, MON_DATA_MOVE1PP + slot1, NULL);
    ppUp[0] = (u8)GetBoxMonData(boxmon, MON_DATA_MOVE1PPUP + slot1, NULL);
    moves[1] = (u16)GetBoxMonData(boxmon, MON_DATA_MOVE1 + slot2, NULL);
    pp[1] = (u8)GetBoxMonData(boxmon, MON_DATA_MOVE1PP + slot2, NULL);
    ppUp[1] = (u8)GetBoxMonData(boxmon, MON_DATA_MOVE1PPUP + slot2, NULL);

    SetBoxMonData(boxmon, MON_DATA_MOVE1 + slot1, &moves[1]);
    SetBoxMonData(boxmon, MON_DATA_MOVE1PP + slot1, &pp[1]);
    SetBoxMonData(boxmon, MON_DATA_MOVE1PPUP + slot1, &ppUp[1]);
    SetBoxMonData(boxmon, MON_DATA_MOVE1 + slot2, &moves[0]);
    SetBoxMonData(boxmon, MON_DATA_MOVE1PP + slot2, &pp[0]);
    SetBoxMonData(boxmon, MON_DATA_MOVE1PPUP + slot2, &ppUp[0]);
}

void FUN_020699A4(struct Pokemon * pokemon, u32 slot)
{
    u16 move;
    u8 pp;
    u8 ppUp;
    for (; slot < 3; slot++)
    {
        move = (u16)GetMonData(pokemon, (int)(MON_DATA_MOVE1 + slot + 1), NULL);
        pp = (u8)GetMonData(pokemon, (int)(MON_DATA_MOVE1PP + slot + 1), NULL);
        ppUp = (u8)GetMonData(pokemon, (int)(MON_DATA_MOVE1PPUP + slot + 1), NULL);
        SetMonData(pokemon, (int)(MON_DATA_MOVE1 + slot), &move);
        SetMonData(pokemon, (int)(MON_DATA_MOVE1PP + slot), &pp);
        SetMonData(pokemon, (int)(MON_DATA_MOVE1PPUP + slot), &ppUp);
    }
    move = MOVE_NONE;
    pp = 0;
    ppUp = 0;
    SetMonData(pokemon, MON_DATA_MOVE1 + 3, &move);
    SetMonData(pokemon, MON_DATA_MOVE1PP + 3, &pp);
    SetMonData(pokemon, MON_DATA_MOVE1PPUP + 3, &ppUp);
}

BOOL MonHasMove(struct Pokemon * pokemon, u16 move)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (GetMonData(pokemon, MON_DATA_MOVE1 + i, NULL) == move)
            break;
    }
    if (i != 4)
        return TRUE;
    else
        return FALSE;
}

void CopyBoxPokemonToPokemon(struct BoxPokemon * src, struct Pokemon * dest)
{
    u32 sp0 = 0;
    CapsuleArray sp4;
    struct Mail * mail;
    dest->box = *src;
    if (dest->box.box_lock)
        dest->box.party_lock = TRUE;
    SetMonData(dest, MON_DATA_STATUS, &sp0);
    SetMonData(dest, MON_DATA_HP, &sp0);
    SetMonData(dest, MON_DATA_MAXHP, &sp0);
    mail = Mail_new(0);
    SetMonData(dest, MON_DATA_MAIL_STRUCT, mail);
    FreeToHeap(mail);
    SetMonData(dest, MON_DATA_CAPSULE, &sp0);
    MI_CpuClearFast(&sp4, sizeof(sp4));
    SetMonData(dest, MON_DATA_SEAL_COORDS, &sp4);
    CalcMonLevelAndStats(dest);
}

u8 Party_GetMaxLevel(struct PlayerParty * party)
{
    int i;
    int r7 = GetPartyCount(party);
    u8 ret = 1;
    u8 level;
    for (i = 0; i < r7; i++)
    {
        struct Pokemon * pokemon = GetPartyMonByIndex(party, i);
        if (GetMonData(pokemon, MON_DATA_SPECIES, NULL) != SPECIES_NONE
         && !GetMonData(pokemon, MON_DATA_IS_EGG, NULL))
        {
            level = (u8)GetMonData(pokemon, MON_DATA_LEVEL, NULL);
            if (level > ret)
                ret = level;
        }
    }
    return ret;
}

u16 SpeciesToSinnohDexNo(u16 species)
{
    u16 ret;
    ReadFromNarcMemberByIdPair(&ret, NARC_POKETOOL_POKEZUKAN, 0, species * sizeof(u16), sizeof(u16));
    return ret;
}

u16 SinnohDexNoToSpecies(u16 sinnoh_dex)
{
    u16 ret = SPECIES_NONE;
    if (sinnoh_dex <= SINNOH_DEX_COUNT)
        ReadFromNarcMemberByIdPair(&ret, NARC_POKETOOL_SHINZUKAN, 0, sinnoh_dex * sizeof(u16), sizeof(u16));
    return ret;
}

void CopyPokemonToPokemon(struct Pokemon * src, struct Pokemon * dest)
{
    *dest = *src;
}

void CopyPokemonToBoxPokemon(struct Pokemon * src, struct BoxPokemon * dest)
{
    *dest = src->box;
}

void CopyBoxPokemonToBoxPokemon(struct BoxPokemon * src, struct BoxPokemon * dest)
{
    *dest = *src;
}

s8 MonGetFlavorPreference(struct Pokemon * pokemon, int flavor)
{
    return BoxMonGetFlavorPreference(&pokemon->box, flavor);
}

s8 BoxMonGetFlavorPreference(struct BoxPokemon * boxmon, int flavor)
{
    u32 personality = GetBoxMonData(boxmon, MON_DATA_PERSONALITY, NULL);
    return GetFlavorPreferenceFromPID(personality, flavor);
}

s8 GetFlavorPreferenceFromPID(u32 personality, int flavor)
{
    return sFlavorPreferencesByNature[GetNatureFromPersonality(personality)][flavor];
}

int Species_LoadLearnsetTable(u16 species, u32 forme, u16 * dest)
{
    int i;
    u16 * wotbl = AllocFromHeap(0, 22 * sizeof(u16));
    LoadWotbl_HandleAlternateForme(species, (int)forme, wotbl);
    for (i = 0; wotbl[i] != WOTBL_END; i++)
    {
        dest[i] = WOTBL_MOVE(wotbl[i]);
    }
    FreeToHeap(wotbl);
    return i;
}

void Party_GivePokerusAtRandom(struct PlayerParty * party)
{
    int count = GetPartyCount(party);
    int idx;
    struct Pokemon * pokemon;
    u8 sp0;
    switch (LCRandom())
    {
    case 0x4000:
    case 0x8000:
    case 0xC000:
        do
        {
            idx = LCRandom() % count;
            pokemon = GetPartyMonByIndex(party, idx);
        } while (GetMonData(pokemon, MON_DATA_SPECIES, NULL) == SPECIES_NONE || GetMonData(pokemon, MON_DATA_IS_EGG, NULL));
        if (!Party_MaskMonsWithPokerus(party, (u8)MaskOfFlagNo(idx)))
        {
            do
            {
                sp0 = (u8)LCRandom();
            } while (!(sp0 & 7));
            if (sp0 & 0xF0)
                sp0 &= 7;
            sp0 |= sp0 << 4;
            sp0 &= 0xF3;
            sp0++;
            SetMonData(pokemon, MON_DATA_POKERUS, &sp0);
        }
    }
}

u8 Party_MaskMonsWithPokerus(struct PlayerParty * party, u8 mask)
{
    int i = 0;
    u32 flag = 1;
    u8 ret = 0;
    struct Pokemon * pokemon;
    if (mask != 0)
    {
        do
        {
            if (mask & 1)
            {
                pokemon = GetPartyMonByIndex(party, i);
                if (GetMonData(pokemon, MON_DATA_POKERUS, NULL))
                    ret |= flag;
            }
            i++;
            flag <<= 1;
            mask >>= 1;
        }
        while (mask != 0);
    }
    else
    {
        pokemon = GetPartyMonByIndex(party, 0);
        if (GetMonData(pokemon, MON_DATA_POKERUS, NULL))
            ret++;
    }
    return ret;
}

void Party_UpdatePokerus(struct PlayerParty * party, int r5)
{
    int i;
    u8 pokerus;
    struct Pokemon * pokemon;
    int count = GetPartyCount(party);
    for (i = 0; i < count; i++)
    {
        pokemon = GetPartyMonByIndex(party, i);
        if (GetMonData(pokemon, MON_DATA_SPECIES, NULL) != SPECIES_NONE)
        {
            pokerus = (u8)GetMonData(pokemon, MON_DATA_POKERUS, NULL);
            if (pokerus & 0xF)
            {
                if ((pokerus & 0xF) < r5 || r5 > 4)
                    pokerus &= 0xF0;
                else
                    pokerus -= r5;
                if (pokerus == 0)
                    pokerus = 0x10; // immune
                SetMonData(pokemon, MON_DATA_POKERUS, &pokerus);
            }
        }
    }
}

void Party_SpreadPokerus(struct PlayerParty * party)
{
    int count = GetPartyCount(party);
    int i;
    struct Pokemon * pokemon;
    u8 pokerus;
    if ((LCRandom() % 3) == 0)
    {
        for (i = 0; i < count; i++)
        {
            pokemon = GetPartyMonByIndex(party, i);
            if (GetMonData(pokemon, MON_DATA_SPECIES, NULL) != SPECIES_NONE)
            {
                pokerus = (u8)GetMonData(pokemon, MON_DATA_POKERUS, NULL);
                if (pokerus & 0xF)
                {
                    if (i != 0)
                    {
                        pokemon = GetPartyMonByIndex(party, i - 1);
                        if (!(GetMonData(pokemon, MON_DATA_POKERUS, NULL) & 0xF0))
                            SetMonData(pokemon, MON_DATA_POKERUS, &pokerus);
                    }
                    if (i < count - 1)
                    {
                        pokemon = GetPartyMonByIndex(party, i + 1);
                        if (!(GetMonData(pokemon, MON_DATA_POKERUS, NULL) & 0xF0))
                        {
                            SetMonData(pokemon, MON_DATA_POKERUS, &pokerus);
                            i++; // don't infect the rest of the party
                        }
                    }
                }
            }
        }
    }
}

BOOL Pokemon_HasPokerus(struct Pokemon * pokemon)
{
    return BoxMon_HasPokerus(&pokemon->box);
}

BOOL BoxMon_HasPokerus(struct BoxPokemon * boxmon)
{
    return !!(GetBoxMonData(boxmon, MON_DATA_POKERUS, NULL) & 0xF);
}

BOOL Pokemon_IsImmuneToPokerus(struct Pokemon * pokemon)
{
    return BoxMon_IsImmuneToPokerus(&pokemon->box);
}

BOOL BoxMon_IsImmuneToPokerus(struct BoxPokemon * boxmon)
{
    u8 pokerus = (u8)GetBoxMonData(boxmon, MON_DATA_POKERUS, NULL);
    if (pokerus & 0xF)
        return FALSE;
    if (pokerus & 0xF0)
        return TRUE;
    return FALSE;
}

void Pokemon_UpdateArceusForme(struct Pokemon * pokemon)
{
    BoxMon_UpdateArceusForme(&pokemon->box);
}

void BoxMon_UpdateArceusForme(struct BoxPokemon * boxmon)
{
    u32 species = GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL);
    u32 ability = GetBoxMonData(boxmon, MON_DATA_ABILITY, NULL);
    u32 heldItem = GetBoxMonData(boxmon, MON_DATA_HELD_ITEM, NULL);
    u32 forme;
    if (species == SPECIES_ARCEUS && ability == ABILITY_MULTITYPE)
    {
        forme = GetArceusTypeByHeldItemEffect((u16)GetItemAttr((u16)heldItem, 1, 0));
        SetBoxMonData(boxmon, MON_DATA_FORME, &forme);
    }
}

u32 GetArceusTypeByHeldItemEffect(u16 heldEffect)
{
    switch (heldEffect)
    {
    case HOLD_EFFECT_ARCEUS_FIRE:
        return TYPE_FIRE;
    case HOLD_EFFECT_ARCEUS_WATER:
        return TYPE_WATER;
    case HOLD_EFFECT_ARCEUS_ELECTRIC:
        return TYPE_ELECTRIC;
    case HOLD_EFFECT_ARCEUS_GRASS:
        return TYPE_GRASS;
    case HOLD_EFFECT_ARCEUS_ICE:
        return TYPE_ICE;
    case HOLD_EFFECT_ARCEUS_FIGHT:
        return TYPE_FIGHTING;
    case HOLD_EFFECT_ARCEUS_POISON:
        return TYPE_POISON;
    case HOLD_EFFECT_ARCEUS_GROUND:
        return TYPE_GROUND;
    case HOLD_EFFECT_ARCEUS_FLYING:
        return TYPE_FLYING;
    case HOLD_EFFECT_ARCEUS_PSYCHIC:
        return TYPE_PSYCHIC;
    case HOLD_EFFECT_ARCEUS_BUG:
        return TYPE_BUG;
    case HOLD_EFFECT_ARCEUS_ROCK:
        return TYPE_ROCK;
    case HOLD_EFFECT_ARCEUS_GHOST:
        return TYPE_GHOST;
    case HOLD_EFFECT_ARCEUS_DRAGON:
        return TYPE_DRAGON;
    case HOLD_EFFECT_ARCEUS_DARK:
        return TYPE_DARK;
    case HOLD_EFFECT_ARCEUS_STEEL:
        return TYPE_STEEL;
    default:
        return TYPE_NORMAL;
    }
}

void LoadWotbl_HandleAlternateForme(int species, int forme, u16 * wotbl)
{
    ReadWholeNarcMemberByIdPair(wotbl, NARC_POKETOOL_PERSONAL_WOTBL, ResolveMonForme(species, forme));
}

void FUN_02069FB0(struct SaveChatotSoundClip *r7, u32 r5, u16 r4, s32 r6, s32 sp18, u32 sp1C, u32 sp20)
{
    if (r4 == SPECIES_CHATOT)
    {
        if (!FUN_02005F14((int)r5))
        {
            FUN_02005E80(1);
            FUN_020056AC(r5, r4, r6, sp18, sp20);
        }
        else
        {
            if (sp1C)
                FUN_02005E80(1);
            FUN_02005E90(r7, 0, sp18, r6);
        }
    }
    else
    {
        FUN_020056AC(r5, r4, r6, sp18, sp20);
    }
}

void FUN_0206A014(struct Pokemon * pokemon, struct PlayerData * a1, u32 pokeball, u32 a3, u32 encounterType, u32 heap_id)
{
    u32 hp;
    FUN_0206A054(&pokemon->box, a1, pokeball, a3, encounterType, heap_id);
    if (pokeball == ITEM_HEAL_BALL)
    {
        hp = GetMonData(pokemon, MON_DATA_MAXHP, NULL);
        SetMonData(pokemon, MON_DATA_HP, &hp);
        hp = 0;
        SetMonData(pokemon, MON_DATA_STATUS, &hp);
    }
}

void FUN_0206A054(struct BoxPokemon * boxmon, struct PlayerData * a1, u32 pokeball, u32 a3, u32 encounterType, u32 heap_id)
{
    FUN_020808AC(boxmon, a1, 0, a3, heap_id);
    SetBoxMonData(boxmon, MON_DATA_GAME_VERSION, (void *)&gGameVersion);
    SetBoxMonData(boxmon, MON_DATA_POKEBALL, &pokeball);
    SetBoxMonData(boxmon, MON_DATA_ENCOUNTER_TYPE, &encounterType);
}

void FUN_0206A094(struct Pokemon * pokemon, u32 a1, u32 a2)
{
    u32 chance;
    u16 species;
    u16 forme;
    u16 item1;
    u16 item2;
    if (!(a1 & 0x81)) {
        chance = (u32)(LCRandom() % 100);
        species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, 0);
        forme = (u16)GetMonData(pokemon, MON_DATA_FORME, 0);
        item1 = (u16)GetMonBaseStat_HandleFormeConversion(species, forme, BASE_ITEM_1);
        item2 = (u16)GetMonBaseStat_HandleFormeConversion(species, forme, BASE_ITEM_2);
        if (item1 == item2 && item1 != ITEM_NONE)
        {
            SetMonData(pokemon, MON_DATA_HELD_ITEM, &item1);
        }
        else
        {
            if (chance >= sItemOdds[a2][0])
            {
                if (chance < sItemOdds[a2][1])
                {
                    SetMonData(pokemon, MON_DATA_HELD_ITEM, &item1);
                }
                else
                {
                    SetMonData(pokemon, MON_DATA_HELD_ITEM, &item2);
                }
            }
        }
    }
}

BOOL FUN_0206A13C(struct Pokemon * pokemon, u32 a1)
{
    return FUN_0206A144(&pokemon->box, a1);
}

BOOL FUN_0206A144(struct BoxPokemon * boxmon, u32 a1)
{
    u16 species = (u16)GetBoxMonData(boxmon, MON_DATA_SPECIES2, NULL);
    int forme = (int)GetBoxMonData(boxmon, MON_DATA_FORME, NULL);
    return FUN_0206A16C(species, forme, a1);
}

BOOL FUN_0206A16C(u16 species, int forme, u32 a2)
{
    u32 r4;
    enum BaseStat r2;
    if (species == SPECIES_EGG)
        return FALSE;
    if (a2 < 32)
    {
        r4 = 1ul << a2;
        r2 = BASE_TMHM_1;
    }
    else if (a2 < 64)
    {
        r4 = 1ul << (a2 - 32);
        r2 = BASE_TMHM_2;
    }
    else if (a2 < 96)
    {
        r4 = 1ul << (a2 - 64);
        r2 = BASE_TMHM_3;
    }
    else
    {
        r4 = 1ul << (a2 - 96);
        r2 = BASE_TMHM_4;
    }
    return !!(GetMonBaseStat_HandleFormeConversion(species, forme, r2) & r4);
}

void FUN_0206A1C4(struct Pokemon * pokemon)
{
    FUN_0206A1CC(&pokemon->box);
}

void FUN_0206A1CC(struct BoxPokemon * boxmon)
{
    BOOL decry = AcquireBoxMonLock(boxmon);
    int species = (int)GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL);
    int pid = (int)GetBoxMonData(boxmon, MON_DATA_PERSONALITY, NULL);
    int ability1 = (int)GetMonBaseStat(species, BASE_ABILITY_1);
    int ability2 = (int)GetMonBaseStat(species, BASE_ABILITY_2);

    if (ability2 != ABILITY_NONE)
    {
        if (pid & 1)
            SetBoxMonData(boxmon, MON_DATA_ABILITY, &ability2);
        else
            SetBoxMonData(boxmon, MON_DATA_ABILITY, &ability1);
    }
    else
        SetBoxMonData(boxmon, MON_DATA_ABILITY, &ability1);
    ReleaseBoxMonLock(boxmon, decry);
}

void FUN_0206A23C(struct Pokemon * r5, u32 personality)
{
    PokemonDataBlockA * r4;
    PokemonDataBlockB * r6;
    PokemonDataBlockC * r7;
    PokemonDataBlockD * sp8;
    PokemonDataBlockA * spC;
    PokemonDataBlockB * sp10;
    PokemonDataBlockC * sp14;
    PokemonDataBlockD * sp18;
    struct Pokemon * sp4;

    sp4 = AllocMonZeroed(0);
    CopyPokemonToPokemon(r5, sp4);
    r4 = &GetSubstruct(&sp4->box, r5->box.pid, 0)->blockA;
    r6 = &GetSubstruct(&sp4->box, r5->box.pid, 1)->blockB;
    r7 = &GetSubstruct(&sp4->box, r5->box.pid, 2)->blockC;
    sp8 = &GetSubstruct(&sp4->box, r5->box.pid, 3)->blockD;
    spC = &GetSubstruct(&r5->box, personality, 0)->blockA;
    sp10 = &GetSubstruct(&r5->box, personality, 1)->blockB;
    sp14 = &GetSubstruct(&r5->box, personality, 2)->blockC;
    sp18 = &GetSubstruct(&r5->box, personality, 3)->blockD;

    DECRYPT_BOX(&sp4->box);
    DECRYPT_PTY(r5);
    DECRYPT_BOX(&r5->box);
    r5->box.pid = personality;
    *spC = *r4;
    *sp10 = *r6;
    *sp14 = *r7;
    *sp18 = *sp8;
    r5->box.checksum = CHECKSUM(&r5->box);
    ENCRYPT_BOX(&r5->box);
    ENCRYPT_PTY(r5);
    FreeToHeap(sp4);
}

void LoadMonPersonal(int species, struct BaseStats * personal)
{
    ReadWholeNarcMemberByIdPair(personal, NARC_POKETOOL_PERSONAL_PERSONAL, species);
}

void LoadMonBaseStats_HandleAlternateForme(int species, int forme, struct BaseStats * personal)
{
    ReadWholeNarcMemberByIdPair(personal, NARC_POKETOOL_PERSONAL_PERSONAL, ResolveMonForme(species, forme));
}

void LoadMonEvolutionTable(u16 species, struct Evolution * evo)
{
    ReadWholeNarcMemberByIdPair(evo, NARC_POKETOOL_PERSONAL_EVO, species);
}


void MonEncryptSegment(u16 * data, u32 size, u32 seed) {
    int i;
    for (i = 0; i < size / 2; i++)
    {
        data[i] ^= MonEncryptionLCRNG(&seed);
    }
}

void MonDecryptSegment(u16 * data, u32 size, u32 seed) {
    MonEncryptSegment(data, size, seed);
}

u16 MonEncryptionLCRNG(u32 * seed)
{
    *seed = *seed * 1103515245 + 24691;
    return (u16)(*seed >> 16);
}

u16 CalcMonChecksum(u16 * data, u32 size)
{
    int i;
    u16 ret = 0;
    for (i = 0; i < size / 2; i++)
    {
        ret += data[i];
    }
    return ret;
}

#define SUBSTRUCT_CASE(v1, v2, v3, v4)                                  \
{                                                                       \
        PokemonDataBlock *substructs = boxMon->substructs;              \
        switch (substructType)                                          \
        {                                                               \
        case 0:                                                         \
            result = &substructs[v1];                                   \
            break;                                                      \
        case 1:                                                         \
            result = &substructs[v2];                                   \
            break;                                                      \
        case 2:                                                         \
            result = &substructs[v3];                                   \
            break;                                                      \
        case 3:                                                         \
            result = &substructs[v4];                                   \
            break;                                                      \
        }                                                               \
                                                                        \
        break;                                                          \
}

PokemonDataBlock *GetSubstruct(struct BoxPokemon *boxMon, u32 personality, u8 substructType)
{
    PokemonDataBlock *result;

    switch ((personality & 0x3E000) >> 13)
    {
    case  0:
    case 24:
        SUBSTRUCT_CASE(0,1,2,3)
    case  1:
    case 25:
        SUBSTRUCT_CASE(0,1,3,2)
    case  2:
    case 26:
        SUBSTRUCT_CASE(0,2,1,3)
    case  3:
    case 27:
        SUBSTRUCT_CASE(0,3,1,2)
    case  4:
    case 28:
        SUBSTRUCT_CASE(0,2,3,1)
    case  5:
    case 29:
        SUBSTRUCT_CASE(0,3,2,1)
    case  6:
    case 30:
        SUBSTRUCT_CASE(1,0,2,3)
    case  7:
    case 31:
        SUBSTRUCT_CASE(1,0,3,2)
    case  8:
        SUBSTRUCT_CASE(2,0,1,3)
    case  9:
        SUBSTRUCT_CASE(3,0,1,2)
    case 10:
        SUBSTRUCT_CASE(2,0,3,1)
    case 11:
        SUBSTRUCT_CASE(3,0,2,1)
    case 12:
        SUBSTRUCT_CASE(1,2,0,3)
    case 13:
        SUBSTRUCT_CASE(1,3,0,2)
    case 14:
        SUBSTRUCT_CASE(2,1,0,3)
    case 15:
        SUBSTRUCT_CASE(3,1,0,2)
    case 16:
        SUBSTRUCT_CASE(2,3,0,1)
    case 17:
        SUBSTRUCT_CASE(3,2,0,1)
    case 18:
        SUBSTRUCT_CASE(1,2,3,0)
    case 19:
        SUBSTRUCT_CASE(1,3,2,0)
    case 20:
        SUBSTRUCT_CASE(2,1,3,0)
    case 21:
        SUBSTRUCT_CASE(3,1,2,0)
    case 22:
        SUBSTRUCT_CASE(2,3,1,0)
    case 23:
        SUBSTRUCT_CASE(3,2,1,0)
    }
    return result;
}

int ResolveMonForme(int species, int forme)
{
    switch (species)
    {
    case SPECIES_DEOXYS:
        if (forme != 0 && forme <= 3)
            return SPECIES_DEOXYS_ATK + forme - 1;
        break;
    case SPECIES_WORMADAM:
        if (forme != 0 && forme <= 2)
            return SPECIES_WORMADAM_SANDY + forme - 1;
        break;
    }
    return species;
}

u32 MaskOfFlagNo(int flagno)
{
    // This is completely inane.
    int i;
    u32 ret = 1;
    GF_ASSERT(flagno < 32);
    for (i = 0; i < flagno; i++)
        ret <<= 1;
    return ret;
}

int LowestFlagNo(u32 mask)
{
    int i;
    u32 bit = 1;
    for (i = 0; i < 32; i++)
    {
        if (mask & bit)
            break;
        bit <<= 1;
    }
    return i;
}

BOOL IsPokemonLegendaryOrMythical(u16 species)
{
    int i;
    for (i = 0; i < NELEMS(sLegendaryMonsList); i++)
    {
        if (species == sLegendaryMonsList[i])
            return TRUE;
    }
    return FALSE;
}

u16 GetLegendaryMon(u32 idx)
{
    if (idx >= NELEMS(sLegendaryMonsList))
        idx = 0;
    return sLegendaryMonsList[idx];
}

BOOL FUN_0206A998(struct Pokemon * pokemon)
{
    u16 species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, NULL);
    return IsPokemonLegendaryOrMythical(species);
}

BOOL FUN_0206A9AC(struct BoxPokemon * boxmon, struct PlayerData * sb2, u32 heap_id)
{
    u32 myId = PlayerProfile_GetTrainerID(sb2);
    u32 otId = GetBoxMonData(boxmon, MON_DATA_OTID, NULL);
    u32 myGender = PlayerProfile_GetTrainerGender(sb2);
    u32 otGender = GetBoxMonData(boxmon, MON_DATA_MET_GENDER, NULL);
    struct String * r7 = PlayerProfile_GetPlayerName_NewString(sb2, heap_id);
    struct String * r6 = String_ctor(OT_NAME_LENGTH + 1, heap_id);
    BOOL ret = FALSE;
    GetBoxMonData(boxmon, MON_DATA_OT_NAME_2, r6);
    if (myId == otId && myGender == otGender && StringCompare(r7, r6) == 0)
        ret = TRUE;
    String_dtor(r6);
    String_dtor(r7);
    return ret;
}

int FUN_0206AA30(int x)
{
    switch (x)
    {
    case TRAINER_CLASS_PKMN_TRAINER_BARRY:
        return TRAINER_BACKPIC_BARRY;
    case TRAINER_CLASS_PKMN_TRAINER_CHERYL:
    case TRAINER_CLASS_PKMN_TRAINER_RILEY:
    case TRAINER_CLASS_PKMN_TRAINER_MARLEY:
    case TRAINER_CLASS_PKMN_TRAINER_BUCK:
    case TRAINER_CLASS_PKMN_TRAINER_MIRA:
        return x - TRAINER_CLASS_PKMN_TRAINER_CHERYL + TRAINER_BACKPIC_CHERYL;
    default:
        if (TrainerClass_GetGenderOrTrainerCount(x) == 1)
            return TRAINER_BACKPIC_DAWN;
        else
            return TRAINER_BACKPIC_LUCAS;
    case TRAINER_CLASS_PKMN_TRAINER_M:
    case TRAINER_CLASS_PKMN_TRAINER_F:
        return x - TRAINER_CLASS_PKMN_TRAINER_M + TRAINER_BACKPIC_LUCAS;
    }
}

void Pokemon_RemoveCapsule(struct Pokemon * pokemon)
{
    u8 sp0 = 0;
    CapsuleArray sp1;
    MI_CpuClearFast(&sp1, sizeof(sp1));
    SetMonData(pokemon, MON_DATA_CAPSULE, &sp0);
    SetMonData(pokemon, MON_DATA_SEAL_COORDS, &sp1);
}

void RestoreBoxMonPP(struct BoxPokemon * boxmon)
{
    int i;
    u8 pp;
    BOOL decry = AcquireBoxMonLock(boxmon);
    for (i = 0; i < 4; i++)
    {
        if (GetBoxMonData(boxmon, MON_DATA_MOVE1 + i, NULL) != MOVE_NONE)
        {
            pp = (u8)GetBoxMonData(boxmon, MON_DATA_MOVE1MAXPP + i, NULL);
            SetBoxMonData(boxmon, MON_DATA_MOVE1PP + i, &pp);
        }
    }
    ReleaseBoxMonLock(boxmon, decry);
}
