#ifndef POKEDIAMOND_POKEMON_H
#define POKEDIAMOND_POKEMON_H

#include "nitro/types.h"

// Enums

#include "constants/species.h"

// TODO: Identify the rest of these
enum BaseStat {
    BASE_HP = 0,
    BASE_ATK,
    BASE_DEF,
    BASE_SPEED,
    BASE_SPATK,
    BASE_SPDEF,
    BASE_TYPE1,
    BASE_TYPE2,
    BASE_CATCH_RATE,
    BASE_EXP_YIELD,
    BASE_HP_YIELD,
    BASE_ATK_YIELD,
    BASE_DEF_YIELD,
    BASE_SPEED_YIELD,
    BASE_SPATK_YIELD,
    BASE_SPDEF_YIELD,
    BASE_GENDER_RATIO = 18,
    BASE_FIRENDSHIP = 20,
    BASE_GROWTH_RATE = 21,
    BASE_ABILITY_1 = 24,
    BASE_ABILITY_2,
};

struct BaseStats {
    u8 hp;
    u8 atk;
    u8 def;
    u8 speed;
    u8 spatk;
    u8 spdef;
    u8 types[2];
    u8 catchRate;
    u8 expYield;
    u16 hp_yield:2;
    u16 atk_yield:2;
    u16 def_yield:2;
    u16 speed_yield:2;
    u16 spatk_yield:2;
    u16 spdef_yield:2;
    u16 unkB_4:2;
    u16 padding_B_6:2;
    u16 unkC;
    u16 unkE;
    u8 genderRatio;
    u8 unk11;
    u8 friendship;
    u8 growthRate;
    u8 unk14;
    u8 unk15;
    u8 abilities[2];
    u8 unk18;
    u8 unk19_0:7;
    u8 unk19_7:1;
    u8 padding_1A[2];
    u32 unk1C;
    u32 unk20;
    u32 unk24;
    u32 unk28;
};

typedef enum {
    EGG = 0,
    EVENT = 0,
    HATCHED = 0,
    PAL_PARK = 0,
    TALL_GRASS = 2,
    DIALGA_GAME_EVENT = 4,
    PALKIA_GAME_EVENT = 4,
    CAVE = 5,
    HALL_OF_ORIGIN = 5,
    SURFING = 7,
    FISHING = 7,
    BUILDING = 9,
    SAFARI_ZONE = 10,
    STARTER = 12,
    FOSSIL = 12,
    GIFT_EEVEE = 12
} EncounterType;

typedef enum GameLanguage OriginLanguage;

typedef enum {
    ARCEUS_NORMAL = 0,
    ARCEUS_FIST = 8,
    ARCEUS_SKY = 16,
    ARCEUS_TOXIC = 24,
    ARCEUS_EARTH = 32,
    ARCEUS_STONE = 40,
    ARCEUS_INSECT = 48,
    ARCEUS_SPOOKY = 56,
    ARCEUS_IRON = 64,
    ARCEUS_FLAME = 72,
    ARCEUS_SPLASH = 80,
    ARCEUS_MEADOW = 88,
    ARCEUS_ZAP = 96,
    ARCEUS_MIND = 104,
    ARCEUS_ICICLE = 112,
    ARCEUS_DRACO = 120,
    ARCEUS_DREAD = 128,
    BURMY_PLANT = 0,
    BURMY_SANDY = 8,
    BURMY_TRASH = 16,
    DEOXYS_NORMAL = 0,
    DEOXYS_ATTACK = 8,
    DEOXYS_DEFENSE = 16,
    DEOXYS_SPEED = 24,
    GIRATINA_ALTERED = 0,
    GIRATINA_ORIGIN = 8,
    ROTOM_NORMAL = 0,
    ROTOM_HEAT = 8,
    ROTOM_WASH = 16,
    ROTOM_FROST = 24,
    ROTOM_FAN = 32,
    ROTOM_MOW = 40,
    SHAYMIN_LAND = 0,
    SHAYMIN_SKY = 8,
    SHELLOS_WEST = 0,
    SHELLOS_EAST = 8,
    UNOWN_A = 0,
    UNOWN_B = 8,
    UNOWN_C = 16,
    UNOWN_D = 24,
    UNOWN_E = 32,
    UNOWN_F = 40,
    UNOWN_G = 48,
    UNOWN_H = 56,
    UNOWN_I = 64,
    UNOWN_J = 72,
    UNOWN_K = 80,
    UNOWN_L = 88,
    UNOWN_M = 96,
    UNOWN_N = 104,
    UNOWN_O = 112,
    UNOWN_P = 120,
    UNOWN_Q = 128,
    UNOWN_R = 136,
    UNOWN_S = 144,
    UNOWN_T = 152,
    UNOWN_U = 160,
    UNOWN_V = 168,
    UNOWN_W = 176,
    UNOWN_X = 184,
    UNOWN_Y = 192,
    UNOWN_Z = 200,
    UNOWN_EXCLAMATION_MARK = 208,
    UNOWN_QUESTION_MARK = 216
} AlternateForms;

// Structs

typedef struct {
    u16 species;
    u16 heldItem;
    u16 otID;
    u16 otSecretID;
    u32 exp;
    u8 friendship;
    u8 ability;
    u8 circleMarking:1, triangleMarking:1, squareMarking:1, heartMarking:1, starMarking:1, diamondMarking:1;
    u8 padding;
    OriginLanguage originLanguage;
    u8 hpEV;
    u8 atkEV;
    u8 defEV;
    u8 spdEV;
    u8 spatkEV;
    u8 spdefEV;
    u8 coolStat;
    u8 beautyStat;
    u8 cuteStat;
    u8 smartStat;
    u8 toughStat;
    u8 sheen;
    // TODO: Finish SinnohRibbonSet1
    u8 sinnohChampRibbon:1, abilityRibbon:1;
    u8 field_0x1d;
    u8 gorgeousRoyalRibbon:1, footprintRibbon:1;
    u8 field_0x1f;
} PokemonDataBlockA;

typedef struct {
    u16 move1;
    u16 move2;
    u16 move3;
    u16 move4;
    u8 move1pp;
    u8 move2pp;
    u8 move3pp;
    u8 move4pp;
    u8 move1ppUps;
    u8 move2ppUps;
    u8 move3ppUps;
    u8 move4ppUps;
    u32 hpIV:5, atkIV:5, defIV:5, spdIV:5, spatkIV:5, spdefIV:5, isEgg:1, isNicknamed:1;
    // TODO: Finish HoennRibbonSet
    u8 coolRibbon:1;
    u8 field_0x15;
    u8 field_0x16;
    u8 field_0x17;
    u8 fatefulEncounter:1, female:1, genderless:1, alternateForm:5;
    u8 HGSS_shinyLeaves; // TODO: Turn into bitfield
    u16 Unused;
    u16 Platinum_EggLocation;
    u16 Platinum_MetLocation;
} PokemonDataBlockB;

typedef struct {
    u16 nickname[11];
    u8 Unused;
    u8 originGame;
    // TODO: Finish SinnohRibbonSet2
    u8 coolRibbon:1;
    u8 field_0x19;
    u8 field_0x1a;
    u8 field_0x1b;
    u32 Unused2;
} PokemonDataBlockC;

typedef struct {
    u16 otTrainerName[8];
    u8 dateEggReceived[3];
    u8 dateMet[3];
    u16 DP_EggLocation;
    u16 DP_MetLocation;
    u8 pokerus;
    u8 pokeball;
    u8 flags;
    u8 padding[3];
    EncounterType encounterType;
    u8 HGSS_Pokeball;
    u8 HGSS_Performance;
    u8 padding2[2];
} PokemonDataBlockD;

typedef union {
    PokemonDataBlockA blockA;
    PokemonDataBlockB blockB;
    PokemonDataBlockC blockC;
    PokemonDataBlockD blockD;
} PokemonDataBlock;

struct BoxPokemon {
    u32 personalityValue;
    u16 Unused;    // Might be used for validity checks
    u16 checksum;  // Stored checksum of pokemon
    PokemonDataBlock block1;  // Blocks A-D; Order based on personalityValue
    PokemonDataBlock block2;
    PokemonDataBlock block3;
    PokemonDataBlock block4;
};

struct Pokemon {
    u16 boxMonKey;
    u16 unused;
    u16 decrypted:1;
    u16 unkBitfield:15;
    u16 ramMonKey;
    struct BoxPokemon box;
    // TODO: RAM struct attributes
    u8 filler_88[100];
};

int GetMonBaseStat_HandleFormeConversion(int species, int form, int stat_id);
int GetMonBaseStat(int species, int stat_id);
int GetMonExpByLevel(int species, int level);
void LoadGrowthTable(int species, int * table);
int GetExpByGrowthRateAndLevel(int rate, int level);
int CalcMonLevel(int species, int experience);

#endif //POKEDIAMOND_POKEMON_H
