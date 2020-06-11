#ifndef POKEDIAMOND_POKEMON_H
#define POKEDIAMOND_POKEMON_H

#include "nitro/types.h"

// Enums

#include "constants/species.h"

#define MON_DATA_PERSONALITY          0
#define MON_DATA_IS_ENCRYPTED         1
#define MON_DATA_CONTROL_4_1          2
#define MON_DATA_CONTROL_4_2          3
#define MON_DATA_CHECKSUM             4
#define MON_DATA_SPECIES              5
#define MON_DATA_HELD_ITEM            6
#define MON_DATA_OTID                 7
#define MON_DATA_EXPERIENCE           8
#define MON_DATA_FRIENDSHIP           9
#define MON_DATA_ABILITY             10
#define MON_DATA_MARKINGS            11
#define MON_DATA_GAME_LANGUAGE       12
#define MON_DATA_HP_EV               13
#define MON_DATA_ATK_EV              14
#define MON_DATA_DEF_EV              15
#define MON_DATA_SPEED_EV            16
#define MON_DATA_SPATK_EV            17
#define MON_DATA_SPDEF_EV            18
#define MON_DATA_COOL                19
#define MON_DATA_BEAUTY              20
#define MON_DATA_CUTE                21
#define MON_DATA_SMART               22
#define MON_DATA_TOUGH               23
#define MON_DATA_SHEEN               24
#define MON_DATA_SINNOH_CHAMP_RIBBON 25
// TODO: ribbon flags through 53
#define MON_DATA_MOVE1               54
#define MON_DATA_MOVE2               55
#define MON_DATA_MOVE3               56
#define MON_DATA_MOVE4               57
#define MON_DATA_MOVE1PP             58
#define MON_DATA_MOVE2PP             59
#define MON_DATA_MOVE3PP             60
#define MON_DATA_MOVE4PP             61
#define MON_DATA_MOVE1PPUP           62
#define MON_DATA_MOVE2PPUP           63
#define MON_DATA_MOVE3PPUP           64
#define MON_DATA_MOVE4PPUP           65
#define MON_DATA_MOVE1MAXPP          66
#define MON_DATA_MOVE2MAXPP          67
#define MON_DATA_MOVE3MAXPP          68
#define MON_DATA_MOVE4MAXPP          69
#define MON_DATA_HP_IV               70
#define MON_DATA_ATK_IV              71
#define MON_DATA_DEF_IV              72
#define MON_DATA_SPEED_IV            73
#define MON_DATA_SPATK_IV            74
#define MON_DATA_SPDEF_IV            75
#define MON_DATA_IS_EGG              76
#define MON_DATA_HAS_NICKNAME        77
#define MON_DATA_COOL_RIBBON         78
// TODO: ribbon flags through 109
#define MON_DATA_FATEFUL_ENCOUNTER  110
#define MON_DATA_GENDER             111
#define MON_DATA_FORME              112
#define MON_DATA_RESERVED_113       113 // HGSS
#define MON_DATA_RESERVED_114       114 // Plat
#define MON_DATA_UNUSED_115         115
#define MON_DATA_NICKNAME           116
#define MON_DATA_UNUSED_117         117
#define MON_DATA_NICKNAME_2         118 // ???
#define MON_DATA_NICKNAME_3         119 // ???
#define MON_DATA_UNK_120            120
#define MON_DATA_GAME_VERSION       121
// TODO: ribbon flags 122-142
#define MON_DATA_OT_NAME            143
#define MON_DATA_OT_NAME_2          144 // ???
#define MON_DATA_EGG_MET_YEAR       145
#define MON_DATA_EGG_MET_MONTH      146
#define MON_DATA_EGG_MET_DAY        147
#define MON_DATA_MET_YEAR           148
#define MON_DATA_MET_MONTH          149
#define MON_DATA_MET_DAY            150
#define MON_DATA_EGG_MET_LOCATION   151
#define MON_DATA_MET_LOCATION       152
#define MON_DATA_POKERUS            153
#define MON_DATA_POKEBALL           154
#define MON_DATA_MET_LEVEL          155
#define MON_DATA_MET_GENDER         156
#define MON_DATA_ENCOUNTER_TYPE     157
#define MON_DATA_RESERVED_158       158 // HGSS
#define MON_DATA_STATUS             159
#define MON_DATA_LEVEL              160
#define MON_DATA_CAPSULE            161
#define MON_DATA_HP                 162
#define MON_DATA_MAXHP              163
#define MON_DATA_ATK                164
#define MON_DATA_DEF                165
#define MON_DATA_SPEED              166
#define MON_DATA_SPATK              167
#define MON_DATA_SPDEF              168
#define MON_DATA_SEAL_TYPES_MAYBE   169
#define MON_DATA_SEAL_COORDS        170
#define MON_DATA_SPECIES_EXISTS     171
#define MON_DATA_SANITY_CHECK_172   172
#define MON_DATA_SANITY_CHECK_173   173
#define MON_DATA_IVS_WORD           174
#define MON_DATA_IS_FEMALE          175
#define MON_DATA_TYPE_1             176
#define MON_DATA_TYPE_2             177
#define MON_DATA_SPECIES_NAME       178

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
    BASE_ITEM_1 = 16,
    BASE_ITEM_2,
    BASE_GENDER_RATIO,
    BASE_EGG_CYCLES,
    BASE_FIRENDSHIP,
    BASE_GROWTH_RATE,
    BASE_EGG_GROUP_1,
    GASE_EGG_GROUP_2,
    BASE_ABILITY_1,
    BASE_ABILITY_2,
    BASE_GREAT_MARSH_RATE,
    BASE_COLOR,
    BASE_FLIP,
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
    u16 item1;
    u16 item2;
    u8 genderRatio;
    u8 eggCycles;
    u8 friendship;
    u8 growthRate;
    u8 eggGroups[2];
    u8 abilities[2];
    u8 greatMarshRate;
    u8 color:7;
    u8 flip:1;
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
    /* 0x00 */ u16 species;
    /* 0x02 */ u16 heldItem;
    /* 0x04 */ u32 otID; // low 16: visible; high 16: secret
    /* 0x08 */ u32 exp;
    /* 0x0C */ u8 friendship;
    /* 0x0D */ u8 ability;
    /* 0x0E */ u8 markings; // circle, triangle, square, heart, star, diamond
    /* 0x0F */ u8 originLanguage;
    /* 0x10 */ u8 hpEV;
    /* 0x11 */ u8 atkEV;
    /* 0x12 */ u8 defEV;
    /* 0x13 */ u8 spdEV;
    /* 0x14 */ u8 spatkEV;
    /* 0x15 */ u8 spdefEV;
    /* 0x16 */ u8 coolStat;
    /* 0x17 */ u8 beautyStat;
    /* 0x18 */ u8 cuteStat;
    /* 0x19 */ u8 smartStat;
    /* 0x1A */ u8 toughStat;
    /* 0x1B */ u8 sheen;
    // TODO: Finish SinnohRibbonSet1
    /* 0x1C */ u32 sinnohRibbons;
//    u8 sinnohChampRibbon:1, abilityRibbon:1;
//    u8 field_0x1d;
//    u8 gorgeousRoyalRibbon:1, footprintRibbon:1;
//    u8 field_0x1f;
} PokemonDataBlockA;

typedef struct {
    /* 0x00 */ u16 moves[4];
    /* 0x08 */ u8 movePP[4];
    /* 0x0C */ u8 movePpUps[4];
    /* 0x10 */ u32 hpIV:5, atkIV:5, defIV:5, spdIV:5, spatkIV:5, spdefIV:5, isEgg:1, isNicknamed:1;
    // TODO: Finish HoennRibbonSet
    /* 0x14 */ u32 ribbonFlags; // cool, ...
    /* 0x18 */ u8 fatefulEncounter:1, female:1, genderless:1, alternateForm:5;
    /* 0x19 */ u8 HGSS_shinyLeaves; // TODO: Turn into bitfield
    /* 0x1A */ u16 Unused;
    /* 0x1C */ u16 Platinum_EggLocation;
    /* 0x1E */ u16 Platinum_MetLocation;
} PokemonDataBlockB;

typedef struct {
    /* 0x00 */ u16 nickname[11];
    /* 0x1A */ u8 Unused;
    /* 0x1B */ u8 originGame;
    // TODO: Finish SinnohRibbonSet2
    /* 0x1C */ u32 sinnohRibbons2; // cool, ...
} PokemonDataBlockC;

typedef struct {
    /* 0x00 */ u16 otTrainerName[8];
    /* 0x10 */ u8 dateEggReceived[3];
    /* 0x13 */ u8 dateMet[3];
    /* 0x16 */ u16 DP_EggLocation;
    /* 0x18 */ u16 DP_MetLocation;
    /* 0x1A */ u8 pokerus;
    /* 0x1B */ u8 pokeball;
    /* 0x1C */ u8 flags;
    /* 0x1D */ u8 encounterType;
    /* 0x1E */ u16 HGSS_Pokeball;
} PokemonDataBlockD;

typedef union {
    PokemonDataBlockA blockA;
    PokemonDataBlockB blockB;
    PokemonDataBlockC blockC;
    PokemonDataBlockD blockD;
} PokemonDataBlock;

struct BoxPokemon {
    /* 0x000 */ u32 personalityValue;
    /* 0x004 */ u16 no_encrypt:1;
                u16 control_4_1:1;
                u16 control_4_2:1;
                u16 Unused:13;    // Might be used for validity checks
    /* 0x006 */ u16 checksum;  // Stored checksum of pokemon
    /* 0x008 */ PokemonDataBlock box[4];
};

struct PartyPokemon
{
    /* 0x000 */ struct BoxPokemon box;
    /* 0x088 */ u8 slp:3;
                u8 psn:1;
                u8 brn:1;
                u8 frz:1;
                u8 prz:1;
                u8 tox:1;
    /* 0x089 */ u8 unk89;
    /* 0x08A */ u8 filler8A[2];
    /* 0x08C */ u8 level;
    /* 0x08D */ u8 capsule;
    /* 0x08E */ u16 hp;
    /* 0x090 */ u16 maxHp;
    /* 0x092 */ u16 atk;
    /* 0x094 */ u16 def;
    /* 0x096 */ u16 speed;
    /* 0x098 */ u16 spatk;
    /* 0x09A */ u16 spdef;
    /* 0x09C */ u8 seal_something[0x38]; // a struct?
    /* 0x0D4 */ u8 sealCoords[0x18];     // u8 pairs?
};

struct Pokemon {
    /* 0x000 */ struct BoxPokemon box;
    /* 0x088 */ struct PartyPokemon party;
}; // size: 0xEC

int GetMonBaseStat_HandleFormeConversion(int species, int form, int stat_id);
int GetMonBaseStat(int species, int stat_id);
int GetMonExpByLevel(int species, int level);
void LoadGrowthTable(int species, int * table);
int GetExpByGrowthRateAndLevel(int rate, int level);
int CalcLevelBySpeciesAndExp(int species, int experience);

#endif //POKEDIAMOND_POKEMON_H
