#ifndef POKEDIAMOND_POKEMON_H
#define POKEDIAMOND_POKEMON_H

#include "nitro/types.h"

// Enums

#include "constants/species.h"
#include "seals.h"

#define MON_DATA_PERSONALITY          0
#define MON_DATA_PARTY_LOCK           1
#define MON_DATA_BOX_LOCK             2
#define MON_DATA_CHECKSUM_FAILED      3
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
#define MON_DATA_SINNOH_RIBBON_26    26
#define MON_DATA_SINNOH_RIBBON_27    27
#define MON_DATA_SINNOH_RIBBON_28    28
#define MON_DATA_SINNOH_RIBBON_29    29
#define MON_DATA_SINNOH_RIBBON_30    30
#define MON_DATA_SINNOH_RIBBON_31    31
#define MON_DATA_SINNOH_RIBBON_32    32
#define MON_DATA_SINNOH_RIBBON_33    33
#define MON_DATA_SINNOH_RIBBON_34    34
#define MON_DATA_SINNOH_RIBBON_35    35
#define MON_DATA_SINNOH_RIBBON_36    36
#define MON_DATA_SINNOH_RIBBON_37    37
#define MON_DATA_SINNOH_RIBBON_38    38
#define MON_DATA_SINNOH_RIBBON_39    39
#define MON_DATA_SINNOH_RIBBON_40    40
#define MON_DATA_SINNOH_RIBBON_41    41
#define MON_DATA_SINNOH_RIBBON_42    42
#define MON_DATA_SINNOH_RIBBON_43    43
#define MON_DATA_SINNOH_RIBBON_44    44
#define MON_DATA_SINNOH_RIBBON_45    45
#define MON_DATA_SINNOH_RIBBON_46    46
#define MON_DATA_SINNOH_RIBBON_47    47
#define MON_DATA_SINNOH_RIBBON_48    48
#define MON_DATA_SINNOH_RIBBON_49    49
#define MON_DATA_SINNOH_RIBBON_50    50
#define MON_DATA_SINNOH_RIBBON_51    51
#define MON_DATA_SINNOH_RIBBON_52    52
#define MON_DATA_SINNOH_RIBBON_53    53
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
#define MON_DATA_HOENN_RIBBON_79     79
#define MON_DATA_HOENN_RIBBON_80     80
#define MON_DATA_HOENN_RIBBON_81     81
#define MON_DATA_HOENN_RIBBON_82     82
#define MON_DATA_HOENN_RIBBON_83     83
#define MON_DATA_HOENN_RIBBON_84     84
#define MON_DATA_HOENN_RIBBON_85     85
#define MON_DATA_HOENN_RIBBON_86     86
#define MON_DATA_HOENN_RIBBON_87     87
#define MON_DATA_HOENN_RIBBON_88     88
#define MON_DATA_HOENN_RIBBON_89     89
#define MON_DATA_HOENN_RIBBON_90     90
#define MON_DATA_HOENN_RIBBON_91     91
#define MON_DATA_HOENN_RIBBON_92     92
#define MON_DATA_HOENN_RIBBON_93     93
#define MON_DATA_HOENN_RIBBON_94     94
#define MON_DATA_HOENN_RIBBON_95     95
#define MON_DATA_HOENN_RIBBON_96     96
#define MON_DATA_HOENN_RIBBON_97     97
#define MON_DATA_HOENN_RIBBON_98     98
#define MON_DATA_HOENN_RIBBON_99     99
#define MON_DATA_HOENN_RIBBON_100   100
#define MON_DATA_HOENN_RIBBON_101   101
#define MON_DATA_HOENN_RIBBON_102   102
#define MON_DATA_HOENN_RIBBON_103   103
#define MON_DATA_HOENN_RIBBON_104   104
#define MON_DATA_HOENN_RIBBON_105   105
#define MON_DATA_HOENN_RIBBON_106   106
#define MON_DATA_HOENN_RIBBON_107   107
#define MON_DATA_HOENN_RIBBON_108   108
#define MON_DATA_HOENN_RIBBON_109   109
#define MON_DATA_FATEFUL_ENCOUNTER  110
#define MON_DATA_GENDER             111
#define MON_DATA_FORME              112
#define MON_DATA_RESERVED_113       113 // HGSS
#define MON_DATA_RESERVED_114       114 // Plat
#define MON_DATA_UNUSED_115         115
#define MON_DATA_NICKNAME           116
#define MON_DATA_NICKNAME_2         117
#define MON_DATA_NICKNAME_3         118 // ???
#define MON_DATA_NICKNAME_4         119 // ???
#define MON_DATA_UNK_120            120
#define MON_DATA_GAME_VERSION       121
#define MON_DATA_SINNOH_RIBBON_122  122
#define MON_DATA_SINNOH_RIBBON_123  123
#define MON_DATA_SINNOH_RIBBON_124  124
#define MON_DATA_SINNOH_RIBBON_125  125
#define MON_DATA_SINNOH_RIBBON_126  126
#define MON_DATA_SINNOH_RIBBON_127  127
#define MON_DATA_SINNOH_RIBBON_128  128
#define MON_DATA_SINNOH_RIBBON_129  129
#define MON_DATA_SINNOH_RIBBON_130  130
#define MON_DATA_SINNOH_RIBBON_131  131
#define MON_DATA_SINNOH_RIBBON_132  132
#define MON_DATA_SINNOH_RIBBON_133  133
#define MON_DATA_SINNOH_RIBBON_134  134
#define MON_DATA_SINNOH_RIBBON_135  135
#define MON_DATA_SINNOH_RIBBON_136  136
#define MON_DATA_SINNOH_RIBBON_137  137
#define MON_DATA_SINNOH_RIBBON_138  138
#define MON_DATA_SINNOH_RIBBON_139  139
#define MON_DATA_SINNOH_RIBBON_140  140
#define MON_DATA_SINNOH_RIBBON_141  141
#define MON_DATA_SINNOH_RIBBON_142  142
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
#define MON_DATA_SEAL_STRUCT        169
#define MON_DATA_SEAL_COORDS        170
#define MON_DATA_SPECIES_EXISTS     171
#define MON_DATA_SANITY_IS_EGG      172
#define MON_DATA_SPECIES2           173
#define MON_DATA_IVS_WORD           174
#define MON_DATA_UNK_175            175
#define MON_DATA_TYPE_1             176
#define MON_DATA_TYPE_2             177
#define MON_DATA_SPECIES_NAME       178

#define MON_RATIO_MALE           0
#define MON_RATIO_FEMALE       254
#define MON_RATIO_UNKNOWN      255

#define POKEMON_NAME_LENGTH 10
#define OT_NAME_LENGTH       7

enum MonGender
{
    MON_MALE = 0,
    MON_FEMALE = 1,
    MON_GENDERLESS = 2
};

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
    BASE_ITEM_1,
    BASE_ITEM_2,
    BASE_GENDER_RATIO,
    BASE_EGG_CYCLES,
    BASE_FRIENDSHIP,
    BASE_GROWTH_RATE,
    BASE_EGG_GROUP_1,
    GASE_EGG_GROUP_2,
    BASE_ABILITY_1,
    BASE_ABILITY_2,
    BASE_GREAT_MARSH_RATE,
    BASE_COLOR,
    BASE_FLIP,
    BASE_UNKNOWN_29,
    BASE_UNKNOWN_30,
    BASE_UNKNOWN_31,
    BASE_UNKNOWN_32,
};

struct BaseStats {
    /* 0x00 */ u8 hp;
    /* 0x01 */ u8 atk;
    /* 0x02 */ u8 def;
    /* 0x03 */ u8 speed;
    /* 0x04 */ u8 spatk;
    /* 0x05 */ u8 spdef;
    /* 0x06 */ u8 types[2];
    /* 0x08 */ u8 catchRate;
    /* 0x09 */ u8 expYield;
    /* 0x0A */ u16 hp_yield:2;
               u16 atk_yield:2;
               u16 def_yield:2;
               u16 speed_yield:2;
    /* 0x0B */ u16 spatk_yield:2;
               u16 spdef_yield:2;
               u16 padding_B_4:4;
    /* 0x0C */ u16 item1;
    /* 0x0E */ u16 item2;
    /* 0x10 */ u8 genderRatio;
    /* 0x11 */ u8 eggCycles;
    /* 0x12 */ u8 friendship;
    /* 0x13 */ u8 growthRate;
    /* 0x14 */ u8 eggGroups[2];
    /* 0x16 */ u8 abilities[2];
    /* 0x18 */ u8 greatMarshRate;
    /* 0x19 */ u8 color:7;
               u8 flip:1;
               u8 padding_1A[2];
    /* 0x1C */ u32 unk1C;
    /* 0x20 */ u32 unk20;
    /* 0x24 */ u32 unk24;
    /* 0x28 */ u32 unk28;
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
    ARCEUS_FIST = 1,
    ARCEUS_SKY = 2,
    ARCEUS_TOXIC = 3,
    ARCEUS_EARTH = 4,
    ARCEUS_STONE = 5,
    ARCEUS_INSECT = 6,
    ARCEUS_SPOOKY = 7,
    ARCEUS_IRON = 8,
    ARCEUS_FLAME = 9,
    ARCEUS_SPLASH = 10,
    ARCEUS_MEADOW = 11,
    ARCEUS_ZAP = 12,
    ARCEUS_MIND = 13,
    ARCEUS_ICICLE = 14,
    ARCEUS_DRACO = 15,
    ARCEUS_DREAD = 16,
    BURMY_PLANT = 0,
    BURMY_SANDY = 1,
    BURMY_TRASH = 2,
    DEOXYS_NORMAL = 0,
    DEOXYS_ATTACK = 1,
    DEOXYS_DEFENSE = 2,
    DEOXYS_SPEED = 3,
    GIRATINA_ALTERED = 0,
    GIRATINA_ORIGIN = 1,
    ROTOM_NORMAL = 0,
    ROTOM_HEAT = 1,
    ROTOM_WASH = 2,
    ROTOM_FROST = 3,
    ROTOM_FAN = 4,
    ROTOM_MOW = 5,
    SHAYMIN_LAND = 0,
    SHAYMIN_SKY = 1,
    SHELLOS_WEST = 0,
    SHELLOS_EAST = 1,
    UNOWN_A = 0,
    UNOWN_B = 1,
    UNOWN_C = 2,
    UNOWN_D = 3,
    UNOWN_E = 4,
    UNOWN_F = 5,
    UNOWN_G = 6,
    UNOWN_H = 7,
    UNOWN_I = 8,
    UNOWN_J = 9,
    UNOWN_K = 10,
    UNOWN_L = 11,
    UNOWN_M = 12,
    UNOWN_N = 13,
    UNOWN_O = 14,
    UNOWN_P = 15,
    UNOWN_Q = 16,
    UNOWN_R = 17,
    UNOWN_S = 18,
    UNOWN_T = 19,
    UNOWN_U = 20,
    UNOWN_V = 21,
    UNOWN_W = 22,
    UNOWN_X = 23,
    UNOWN_Y = 24,
    UNOWN_Z = 25,
    UNOWN_EXCLAMATION_MARK = 26,
    UNOWN_QUESTION_MARK = 27
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
    /* 0x18 */ u8 fatefulEncounter:1, gender:2, alternateForm:5;
    /* 0x19 */ u8 HGSS_shinyLeaves; // TODO: Turn into bitfield
    /* 0x1A */ u16 Unused;
    /* 0x1C */ u16 Platinum_EggLocation;
    /* 0x1E */ u16 Platinum_MetLocation;
} PokemonDataBlockB;

typedef struct {
    /* 0x00 */ u16 nickname[11];
    /* 0x16 */ u8 Unused;
    /* 0x17 */ u8 originGame;
    // TODO: Finish SinnohRibbonSet2
    /* 0x18 */ u64 sinnohRibbons2; // cool, ...
} PokemonDataBlockC;

typedef struct {
    /* 0x00 */ u16 otTrainerName[8];
    /* 0x10 */ u8 dateEggReceived[3];
    /* 0x13 */ u8 dateMet[3];
    /* 0x16 */ u16 DP_EggLocation;
    /* 0x18 */ u16 DP_MetLocation;
    /* 0x1A */ u8 pokerus;
    /* 0x1B */ u8 pokeball;
    /* 0x1C */ u8 metLevel:7;
               u8 metGender:1;
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
    /* 0x000 */ u32 pid;
    /* 0x004 */ u16 party_lock:1;
                u16 box_lock:1;
                u16 checksum_fail:1;
                u16 Unused:13;    // Might be used for validity checks
    /* 0x006 */ u16 checksum;  // Stored checksum of pokemon
    /* 0x008 */ PokemonDataBlock substructs[4];
};

struct PartyPokemon
{
    /* 0x088 */ u32 status; // slp:3, psn:1, brn:1, frz:1, prz:1, tox:1, ...
    /* 0x08C */ u8 level;
    /* 0x08D */ u8 capsule;
    /* 0x08E */ u16 hp;
    /* 0x090 */ u16 maxHp;
    /* 0x092 */ u16 atk;
    /* 0x094 */ u16 def;
    /* 0x096 */ u16 speed;
    /* 0x098 */ u16 spatk;
    /* 0x09A */ u16 spdef;
    /* 0x09C */ struct SealStruct seal_something; // a struct?
    /* 0x0D4 */ u8 sealCoords[0x18];     // u8 pairs?
};

struct Pokemon {
    /* 0x000 */ struct BoxPokemon box;
    /* 0x088 */ struct PartyPokemon party;
}; // size: 0xEC

void ZeroMonData(struct Pokemon * pokemon);
void ZeroBoxMonData(struct BoxPokemon * boxmon);
u32 SizeOfStructPokemon(void);
struct Pokemon * AllocMonZeroed(u32 heap_id);
BOOL AcquireMonLock(struct Pokemon * mon);
BOOL ReleaseMonLock(struct Pokemon * mon, BOOL decrypt_result);
BOOL AcquireBoxMonLock(struct BoxPokemon * mon);
BOOL ReleaseBoxMonLock(struct BoxPokemon * mon, BOOL decrypt_result);
void CreateMon(struct Pokemon * pokemon, int species, int level, int fixedIV, int hasFixedPersonality, int fixedPersonality, int otIdType, int fixedOtId);
void CreateBoxMon(struct BoxPokemon * boxPokemon, int species, int level, int fixedIV, int hasFixedPersonality, int fixedPersonality, int otIdType, int fixedOtId);
void CreateMonWithNature(struct Pokemon * pokemon, u16 species, u8 level, u8 fixedIv, u8 nature);
void CreateMonWithGenderNatureLetter(struct Pokemon * pokemon, u16 species, u8 level, u8 fixedIv, u8 gender, u8 nature, u8 letter);
u32 GenPersonalityByGenderAndNature(u16 species, u8 gender, u8 nature);
void CreateMonWithFixedIVs(struct Pokemon * pokemon, int species, int level, int ivs, int personality);
void CalcMonLevelAndStats(struct Pokemon * pokemon);
void CalcMonStats(struct Pokemon * pokemon);
#ifndef IN_POKEMON_C
u32 GetMonData();
u32 GetBoxMonData();
#else
u32 GetMonData(struct Pokemon * pokemon, int attr, void * ptr);
u32 GetBoxMonData(struct BoxPokemon * pokemon, int attr, void * ptr);
#endif
void SetMonData(struct Pokemon * pokemon, int attr, void * ptr);
void SetBoxMonData(struct BoxPokemon * pokemon, int attr, void * ptr);
void AddMonData(struct Pokemon * pokemon, int attr, int amount);
struct BaseStats * AllocAndLoadMonPersonal(int species, u32 heap_id);
int GetPersonalAttr(struct BaseStats * baseStats, enum BaseStat attr);
void FreeMonPersonal(struct BaseStats * personal);
int GetMonBaseStat_HandleFormeConversion(int species, int form, enum BaseStat stat_id);
int GetMonBaseStat(int species, enum BaseStat stat_id);
u8 GetPercentProgressTowardsNextLevel(struct Pokemon * pokemon);
u32 CalcMonExpToNextLevel(struct Pokemon * pokemon);
u32 GetMonBaseExperienceAtCurrentLevel(struct Pokemon * pokemon);
u32 GetMonExpBySpeciesAndLevel(int species, int level);
void LoadGrowthTable(int growthRate, u32 * table);
u32 GetExpByGrowthRateAndLevel(int rate, int level);
int CalcMonLevel(struct Pokemon * pokemon);
int CalcBoxMonLevel(struct BoxPokemon * boxmon);
int CalcLevelBySpeciesAndExp(u16 species, u32 experience);
int CalcLevelBySpeciesAndExp_PreloadedPersonal(struct BaseStats * personal, u16 species, u32 experience);
u8 GetBoxMonNature(struct BoxPokemon * boxmon);
u8 GetMonNature(struct Pokemon * mon);
u8 GetNatureFromPersonality(u32 pid);
void MonApplyFriendshipMod(struct Pokemon * pokemon, u32 kind, u32 location);
u8 GetMonGender(struct Pokemon * pokemon);
u8 GetBoxMonGender(struct BoxPokemon * boxmon);
u8 GetGenderBySpeciesAndPersonality(u16 species, u32 pid);
u8 MonIsShiny(struct Pokemon * pokemon);
u32 GenerateShinyPersonality(u32 otid);

#endif //POKEDIAMOND_POKEMON_H
