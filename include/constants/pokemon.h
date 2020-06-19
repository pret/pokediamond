#ifndef POKEDIAMOND_CONSTANTS_POKEMON_H
#define POKEDIAMOND_CONSTANTS_POKEMON_H


// Pokemon types
#define TYPE_NONE             255
#define TYPE_NORMAL           0
#define TYPE_FIGHTING         1
#define TYPE_FLYING           2
#define TYPE_POISON           3
#define TYPE_GROUND           4
#define TYPE_ROCK             5
#define TYPE_BUG              6
#define TYPE_GHOST            7
#define TYPE_STEEL            8
#define TYPE_MYSTERY          9
#define TYPE_FIRE             10
#define TYPE_WATER            11
#define TYPE_GRASS            12
#define TYPE_ELECTRIC         13
#define TYPE_PSYCHIC          14
#define TYPE_ICE              15
#define TYPE_DRAGON           16
#define TYPE_DARK             17
#define NUMBER_OF_MON_TYPES   18

// Pokemon egg groups
#define EGG_GROUP_NONE          0
#define EGG_GROUP_MONSTER       1
#define EGG_GROUP_WATER_1       2
#define EGG_GROUP_BUG           3
#define EGG_GROUP_FLYING        4
#define EGG_GROUP_FIELD         5
#define EGG_GROUP_FAIRY         6
#define EGG_GROUP_GRASS         7
#define EGG_GROUP_HUMAN_LIKE    8
#define EGG_GROUP_WATER_3       9
#define EGG_GROUP_MINERAL       10
#define EGG_GROUP_AMORPHOUS     11
#define EGG_GROUP_WATER_2       12
#define EGG_GROUP_DITTO         13
#define EGG_GROUP_DRAGON        14
#define EGG_GROUP_UNDISCOVERED  15

#define EGG_GROUPS_PER_MON      2

// Pokemon natures
#define NATURE_HARDY    0
#define NATURE_LONELY   1
#define NATURE_BRAVE    2
#define NATURE_ADAMANT  3
#define NATURE_NAUGHTY  4
#define NATURE_BOLD     5
#define NATURE_DOCILE   6
#define NATURE_RELAXED  7
#define NATURE_IMPISH   8
#define NATURE_LAX      9
#define NATURE_TIMID    10
#define NATURE_HASTY    11
#define NATURE_SERIOUS  12
#define NATURE_JOLLY    13
#define NATURE_NAIVE    14
#define NATURE_MODEST   15
#define NATURE_MILD     16
#define NATURE_QUIET    17
#define NATURE_BASHFUL  18
#define NATURE_RASH     19
#define NATURE_CALM     20
#define NATURE_GENTLE   21
#define NATURE_SASSY    22
#define NATURE_CAREFUL  23
#define NATURE_QUIRKY   24

// Pokemon Stats
#define STAT_HP      0
#define STAT_ATK     1
#define STAT_DEF     2
#define STAT_SPEED   3
#define STAT_SPATK   4
#define STAT_SPDEF   5
#define STAT_ACC     6 // Only in battles.
#define STAT_EVASION 7 // Only in battles.

#define NUM_EV_STATS     NUM_STATS - 1 // excludes HP
#define NUM_BATTLE_STATS NUM_STATS + 2 // includes Accuracy and Evasion

// Shiny odds
#define SHINY_ODDS 8 // Actual probability is SHINY_ODDS/65536


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

typedef enum EvoMethod
{
    EVO_NONE = 0,
    EVO_FRIENDSHIP,
    EVO_FRIENDSHIP_DAY,
    EVO_FRIENDSHIP_NIGHT,
    EVO_LEVEL,
    EVO_TRADE,
    EVO_TRADE_ITEM,
    EVO_STONE,
    EVO_LEVEL_ATK_GT_DEF,
    EVO_LEVEL_ATK_EQ_DEF,
    EVO_LEVEL_ATK_LT_DEF,
    EVO_LEVEL_PID_LO,
    EVO_LEVEL_PID_HI,
    EVO_LEVEL_NINJASK,
    EVO_LEVEL_SHEDINJA,
    EVO_BEAUTY,
    EVO_STONE_MALE,
    EVO_STONE_FEMALE,
    EVO_ITEM_DAY,
    EVO_ITEM_NIGHT,
    EVO_HAS_MOVE,
    EVO_OTHER_PARTY_MON,
    EVO_LEVEL_MALE,
    EVO_LEVEL_FEMALE,
    EVO_CORONET,
    EVO_ETERNA,
    EVO_ROUTE217,
} EvoMethod;

enum GrowthRate
{
    GROWTH_MEDIUM_FAST = 0,
    GROWTH_ERRATIC,
    GROWTH_FLUCTUATING,
    GROWTH_MEDIUM_SLOW,
    GROWTH_FAST,
    GROWTH_SLOW,
};

#endif //POKEDIAMOND_CONSTANTS_POKEMON_H
