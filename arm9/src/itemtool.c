#include "global.h"
#include "itemtool.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "heap.h"
#include "constants/moves.h"

static const u16 sMailIdxs[] = {
    ITEM_GRASS_MAIL,
    ITEM_FLAME_MAIL,
    ITEM_BUBBLE_MAIL,
    ITEM_BLOOM_MAIL,
    ITEM_TUNNEL_MAIL,
    ITEM_STEEL_MAIL,
    ITEM_HEART_MAIL,
    ITEM_SNOW_MAIL,
    ITEM_SPACE_MAIL,
    ITEM_AIR_MAIL,
    ITEM_MOSAIC_MAIL,
    ITEM_BRICK_MAIL,
};

static const u16 sBerryIdxs[] = {
    ITEM_CHERI_BERRY,
    ITEM_CHESTO_BERRY,
    ITEM_PECHA_BERRY,
    ITEM_RAWST_BERRY,
    ITEM_ASPEAR_BERRY,
    ITEM_LEPPA_BERRY,
    ITEM_ORAN_BERRY,
    ITEM_PERSIM_BERRY,
    ITEM_LUM_BERRY,
    ITEM_SITRUS_BERRY,
    ITEM_FIGY_BERRY,
    ITEM_WIKI_BERRY,
    ITEM_MAGO_BERRY,
    ITEM_AGUAV_BERRY,
    ITEM_IAPAPA_BERRY,
    ITEM_RAZZ_BERRY,
    ITEM_BLUK_BERRY,
    ITEM_NANAB_BERRY,
    ITEM_WEPEAR_BERRY,
    ITEM_PINAP_BERRY,
    ITEM_POMEG_BERRY,
    ITEM_KELPSY_BERRY,
    ITEM_QUALOT_BERRY,
    ITEM_HONDEW_BERRY,
    ITEM_GREPA_BERRY,
    ITEM_TAMATO_BERRY,
    ITEM_CORNN_BERRY,
    ITEM_MAGOST_BERRY,
    ITEM_RABUTA_BERRY,
    ITEM_NOMEL_BERRY,
    ITEM_SPELON_BERRY,
    ITEM_PAMTRE_BERRY,
    ITEM_WATMEL_BERRY,
    ITEM_DURIN_BERRY,
    ITEM_BELUE_BERRY,
    ITEM_OCCA_BERRY,
    ITEM_PASSHO_BERRY,
    ITEM_WACAN_BERRY,
    ITEM_RINDO_BERRY,
    ITEM_YACHE_BERRY,
    ITEM_CHOPLE_BERRY,
    ITEM_KEBIA_BERRY,
    ITEM_SHUCA_BERRY,
    ITEM_COBA_BERRY,
    ITEM_PAYAPA_BERRY,
    ITEM_TANGA_BERRY,
    ITEM_CHARTI_BERRY,
    ITEM_KASIB_BERRY,
    ITEM_HABAN_BERRY,
    ITEM_COLBUR_BERRY,
    ITEM_BABIRI_BERRY,
    ITEM_CHILAN_BERRY,
    ITEM_LIECHI_BERRY,
    ITEM_GANLON_BERRY,
    ITEM_SALAC_BERRY,
    ITEM_PETAYA_BERRY,
    ITEM_APICOT_BERRY,
    ITEM_LANSAT_BERRY,
    ITEM_STARF_BERRY,
    ITEM_ENIGMA_BERRY,
    ITEM_MICLE_BERRY,
    ITEM_CUSTAP_BERRY,
    ITEM_JABOCA_BERRY,
    ITEM_ROWAP_BERRY,
};

static const u16 sTMHMMoves[] = {
    MOVE_FOCUS_PUNCH,
    MOVE_DRAGON_CLAW,
    MOVE_WATER_PULSE,
    MOVE_CALM_MIND,
    MOVE_ROAR,
    MOVE_TOXIC,
    MOVE_HAIL,
    MOVE_BULK_UP,
    MOVE_BULLET_SEED,
    MOVE_HIDDEN_POWER,
    MOVE_SUNNY_DAY,
    MOVE_TAUNT,
    MOVE_ICE_BEAM,
    MOVE_BLIZZARD,
    MOVE_HYPER_BEAM,
    MOVE_LIGHT_SCREEN,
    MOVE_PROTECT,
    MOVE_RAIN_DANCE,
    MOVE_GIGA_DRAIN,
    MOVE_SAFEGUARD,
    MOVE_FRUSTRATION,
    MOVE_SOLAR_BEAM,
    MOVE_IRON_TAIL,
    MOVE_THUNDERBOLT,
    MOVE_THUNDER,
    MOVE_EARTHQUAKE,
    MOVE_RETURN,
    MOVE_DIG,
    MOVE_PSYCHIC,
    MOVE_SHADOW_BALL,
    MOVE_BRICK_BREAK,
    MOVE_DOUBLE_TEAM,
    MOVE_REFLECT,
    MOVE_SHOCK_WAVE,
    MOVE_FLAMETHROWER,
    MOVE_SLUDGE_BOMB,
    MOVE_SANDSTORM,
    MOVE_FIRE_BLAST,
    MOVE_ROCK_TOMB,
    MOVE_AERIAL_ACE,
    MOVE_TORMENT,
    MOVE_FACADE,
    MOVE_SECRET_POWER,
    MOVE_REST,
    MOVE_ATTRACT,
    MOVE_THIEF,
    MOVE_STEEL_WING,
    MOVE_SKILL_SWAP,
    MOVE_SNATCH,
    MOVE_OVERHEAT,
    MOVE_ROOST,
    MOVE_FOCUS_BLAST,
    MOVE_ENERGY_BALL,
    MOVE_FALSE_SWIPE,
    MOVE_BRINE,
    MOVE_FLING,
    MOVE_CHARGE_BEAM,
    MOVE_ENDURE,
    MOVE_DRAGON_PULSE,
    MOVE_DRAIN_PUNCH,
    MOVE_WILL_O_WISP,
    MOVE_SILVER_WIND,
    MOVE_EMBARGO,
    MOVE_EXPLOSION,
    MOVE_SHADOW_CLAW,
    MOVE_PAYBACK,
    MOVE_RECYCLE,
    MOVE_GIGA_IMPACT,
    MOVE_ROCK_POLISH,
    MOVE_FLASH,
    MOVE_STONE_EDGE,
    MOVE_AVALANCHE,
    MOVE_THUNDER_WAVE,
    MOVE_GYRO_BALL,
    MOVE_SWORDS_DANCE,
    MOVE_STEALTH_ROCK,
    MOVE_PSYCH_UP,
    MOVE_CAPTIVATE,
    MOVE_DARK_PULSE,
    MOVE_ROCK_SLIDE,
    MOVE_X_SCISSOR,
    MOVE_SLEEP_TALK,
    MOVE_NATURAL_GIFT,
    MOVE_POISON_JAB,
    MOVE_DREAM_EATER,
    MOVE_GRASS_KNOT,
    MOVE_SWAGGER,
    MOVE_PLUCK,
    MOVE_U_TURN,
    MOVE_SUBSTITUTE,
    MOVE_FLASH_CANNON,
    MOVE_TRICK_ROOM,
    MOVE_CUT,
    MOVE_FLY,
    MOVE_SURF,
    MOVE_STRENGTH,
    MOVE_DEFOG,
    MOVE_ROCK_SMASH,
    MOVE_WATERFALL,
    MOVE_ROCK_CLIMB,
};

//TODO: use narc constants
static const u16 sItemIndexMappings[][4] = {
    /* Col 1: Offset in item_data.narc
     * Col 2: Gfx offset in item_icon.narc
     * Col 3: Pal offset in item_icon.narc
     * Col 4: Gen 3 item index (for Pal Park conversion)
     */
    {     0,   699,   700,     0 },
    {     1,     2,     3,     1 },
    {     2,     4,     5,     2 },
    {     3,     6,     7,     3 },
    {     4,     8,     9,     4 },
    {     5,    10,    11,     5 },
    {     6,    12,    13,     6 },
    {     7,    14,    15,     7 },
    {     8,    16,    17,     8 },
    {     9,    18,    19,     9 },
    {    10,    20,    19,    10 },
    {    11,    21,    22,    11 },
    {    12,    23,    22,    12 },
    {    13,   663,   664,     0 },
    {    14,   665,   666,     0 },
    {    15,   667,   668,     0 },
    {    16,   669,   670,     0 },
    {    17,    24,    25,    13 },
    {    18,    26,    27,    14 },
    {    19,    30,    28,    15 },
    {    20,    30,    29,    16 },
    {    21,    30,    31,    17 },
    {    22,    30,    32,    18 },
    {    23,    33,    34,    19 },
    {    24,    33,    35,    20 },
    {    25,    24,    36,    21 },
    {    26,    24,    37,    22 },
    {    27,    38,    39,    23 },
    {    28,    40,    42,    24 },
    {    29,    41,    42,    25 },
    {    30,    43,    44,    26 },
    {    31,    45,    46,    27 },
    {    32,    47,    48,    28 },
    {    33,    49,    50,    29 },
    {    34,    51,    52,    30 },
    {    35,    53,    54,    31 },
    {    36,    51,    55,    32 },
    {    37,    56,    57,    33 },
    {    38,    58,    59,    34 },
    {    39,    58,    60,    35 },
    {    40,    58,    61,    36 },
    {    41,    58,    62,    37 },
    {    42,    63,    64,    38 },
    {    43,    71,    72,    44 },
    {    44,    73,    74,    45 },
    {    45,    83,    84,    63 },
    {    46,    85,    86,    64 },
    {    47,    85,    87,    65 },
    {    48,    85,    88,    66 },
    {    49,    85,    89,    67 },
    {    50,    90,    91,    68 },
    {    51,    92,    93,    69 },
    {    52,    85,    94,    70 },
    {    53,    95,    96,    71 },
    {    54,   466,   467,     0 },
    {    55,   100,    97,    73 },
    {    56,   100,    98,    74 },
    {    57,   100,    99,    75 },
    {    58,   100,   101,    76 },
    {    59,   100,   102,    77 },
    {    60,   100,   103,    78 },
    {    61,   100,   104,    79 },
    {    62,   100,   469,     0 },
    {    63,   105,   106,    80 },
    {    64,   107,   108,    81 },
    {    65,    65,    66,    39 },
    {    66,    65,    67,    40 },
    {    67,    65,    68,    41 },
    {    68,    65,    69,    42 },
    {    69,    65,    70,    43 },
    {    70,    51,    75,    46 },
    {    71,    76,    77,    47 },
    {    72,    78,    79,    48 },
    {    73,    78,    80,    49 },
    {    74,    78,    81,    50 },
    {    75,    78,    82,    51 },
    {    76,   109,   110,    83 },
    {    77,   109,   111,    84 },
    {    78,   112,   113,    85 },
    {    79,   109,   114,    86 },
    {    80,   115,   116,    93 },
    {    81,   117,   118,    94 },
    {    82,   119,   120,    95 },
    {    83,   121,   122,    96 },
    {    84,   123,   124,    97 },
    {    85,   125,   126,    98 },
    {    86,   127,   129,   103 },
    {    87,   128,   129,   104 },
    {    88,   130,   131,   106 },
    {    89,   132,   131,   107 },
    {    90,   133,   134,   108 },
    {    91,   135,   134,   109 },
    {    92,   136,   137,   110 },
    {    93,   138,   139,   111 },
    {    94,   470,   471,     0 },
    {    95,   472,   473,     0 },
    {    96,   474,   475,     0 },
    {    97,   476,   477,     0 },
    {    98,   478,   479,     0 },
    {    99,   392,   393,   286 },
    {   100,   394,   393,   287 },
    {   101,   431,   432,   357 },
    {   102,   433,   432,   358 },
    {   103,   425,   426,   354 },
    {   104,   617,   618,     0 },
    {   105,   615,   616,     0 },
    {   106,   337,   338,     0 },
    {   107,   480,   481,     0 },
    {   108,   482,   483,     0 },
    {   109,   484,   485,     0 },
    {   110,   486,   487,     0 },
    {   111,   488,   489,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {     0,   699,   700,     0 },
    {   112,   648,   649,     0 },
    {   113,   646,   647,     0 },
    {   114,   140,   141,     0 },
    {   115,   142,   143,     0 },
    {   116,   144,   145,     0 },
    {   117,   146,   147,     0 },
    {   118,   148,   149,     0 },
    {   119,   150,   151,     0 },
    {   120,   152,   153,     0 },
    {   121,   154,   155,     0 },
    {   122,   156,   157,     0 },
    {   123,   158,   159,     0 },
    {   124,   160,   161,     0 },
    {   125,   162,   163,     0 },
    {   126,   164,   165,   133 },
    {   127,   166,   167,   134 },
    {   128,   168,   169,   135 },
    {   129,   170,   171,   136 },
    {   130,   172,   173,   137 },
    {   131,   174,   175,   138 },
    {   132,   176,   177,   139 },
    {   133,   178,   179,   140 },
    {   134,   180,   181,   141 },
    {   135,   182,   183,   142 },
    {   136,   184,   185,   143 },
    {   137,   186,   187,   144 },
    {   138,   188,   189,   145 },
    {   139,   190,   191,   146 },
    {   140,   192,   193,   147 },
    {   141,   194,   195,   148 },
    {   142,   196,   197,   149 },
    {   143,   198,   199,   150 },
    {   144,   200,   201,   151 },
    {   145,   202,   203,   152 },
    {   146,   204,   205,   153 },
    {   147,   206,   207,   154 },
    {   148,   208,   209,   155 },
    {   149,   210,   211,   156 },
    {   150,   212,   213,   157 },
    {   151,   214,   215,   158 },
    {   152,   216,   217,   159 },
    {   153,   218,   219,   160 },
    {   154,   220,   221,   161 },
    {   155,   222,   223,   162 },
    {   156,   224,   225,   163 },
    {   157,   226,   227,   164 },
    {   158,   228,   229,   165 },
    {   159,   230,   231,   166 },
    {   160,   232,   233,   167 },
    {   161,   554,   555,     0 },
    {   162,   556,   557,     0 },
    {   163,   558,   559,     0 },
    {   164,   560,   561,     0 },
    {   165,   562,   563,     0 },
    {   166,   564,   565,     0 },
    {   167,   566,   567,     0 },
    {   168,   568,   569,     0 },
    {   169,   570,   571,     0 },
    {   170,   572,   573,     0 },
    {   171,   574,   575,     0 },
    {   172,   576,   577,     0 },
    {   173,   578,   579,     0 },
    {   174,   580,   581,     0 },
    {   175,   582,   583,     0 },
    {   176,   584,   585,     0 },
    {   177,   586,   587,     0 },
    {   178,   234,   235,   168 },
    {   179,   236,   237,   169 },
    {   180,   238,   239,   170 },
    {   181,   240,   241,   171 },
    {   182,   242,   243,   172 },
    {   183,   244,   245,   173 },
    {   184,   246,   247,   174 },
    {   185,   248,   249,   175 },
    {   186,   588,   589,     0 },
    {   187,   590,   591,     0 },
    {   188,   592,   593,     0 },
    {   189,   594,   595,     0 },
    {   190,   250,   251,   179 },
    {   191,   252,   253,   180 },
    {   192,   254,   255,   181 },
    {   193,   256,   257,   182 },
    {   194,   258,   259,   183 },
    {   195,   260,   261,   184 },
    {   196,   252,   262,   185 },
    {   197,   263,   264,   186 },
    {   198,   265,   266,   187 },
    {   199,   267,   268,   188 },
    {   200,   269,   270,   189 },
    {   201,   271,   272,   190 },
    {   202,   273,   274,   191 },
    {   203,   275,   276,   192 },
    {   204,   277,   278,   193 },
    {   205,   279,   280,   194 },
    {   206,   281,   282,   195 },
    {   207,   283,   284,   196 },
    {   208,   285,   286,   197 },
    {   209,   287,   288,   198 },
    {   210,   289,   290,   199 },
    {   211,   291,   292,   200 },
    {   212,   293,   294,   201 },
    {   213,   295,   296,   202 },
    {   214,   297,   298,   203 },
    {   215,   299,   300,   204 },
    {   216,   301,   302,   205 },
    {   217,   303,   304,   206 },
    {   218,   305,   304,   207 },
    {   219,   306,   307,   208 },
    {   220,   308,   309,   209 },
    {   221,   310,   311,   210 },
    {   222,   312,   313,   211 },
    {   223,   314,   315,   212 },
    {   224,   316,   317,   213 },
    {   225,   318,   319,   214 },
    {   226,   320,   321,   215 },
    {   227,   322,   323,   216 },
    {   228,   324,   325,   217 },
    {   229,   326,   327,   218 },
    {   230,   328,    77,   219 },
    {   231,   329,   330,   220 },
    {   232,   331,   332,   221 },
    {   233,   333,   334,   222 },
    {   234,   335,   336,   223 },
    {   235,   337,   338,   224 },
    {   236,   339,   340,   225 },
    {   237,   341,   342,   254 },
    {   238,   341,   343,   255 },
    {   239,   341,   344,   256 },
    {   240,   341,   345,   257 },
    {   241,   341,   346,   258 },
    {   242,   490,   491,     0 },
    {   243,   492,   493,     0 },
    {   244,   494,   495,     0 },
    {   245,   496,   497,     0 },
    {   246,   611,   612,     0 },
    {   247,   498,   499,     0 },
    {   248,   500,   501,     0 },
    {   249,   502,   503,     0 },
    {   250,   504,   505,     0 },
    {   251,   335,   658,     0 },
    {   252,   659,   660,     0 },
    {   253,   506,   507,     0 },
    {   254,   508,   509,     0 },
    {   255,   613,   614,     0 },
    {   256,   650,   651,     0 },
    {   257,   654,   655,     0 },
    {   258,   510,   511,     0 },
    {   259,   636,   637,     0 },
    {   260,   638,   639,     0 },
    {   261,   640,   641,     0 },
    {   262,   642,   643,     0 },
    {   263,   652,   653,     0 },
    {   264,   512,   513,     0 },
    {   265,   514,   515,     0 },
    {   266,   683,   684,     0 },
    {   267,   691,   692,     0 },
    {   268,   693,   694,     0 },
    {   269,   685,   686,     0 },
    {   270,   687,   688,     0 },
    {   271,   689,   690,     0 },
    {   272,   516,   517,     0 },
    {   273,   518,   519,     0 },
    {   274,   520,   521,     0 },
    {   275,   619,   620,     0 },
    {   276,   619,   621,     0 },
    {   277,   619,   622,     0 },
    {   278,   619,   623,     0 },
    {   279,   619,   624,     0 },
    {   280,   619,   625,     0 },
    {   281,   619,   626,     0 },
    {   282,   619,   627,     0 },
    {   283,   619,   628,     0 },
    {   284,   619,   629,     0 },
    {   285,   619,   630,     0 },
    {   286,   619,   631,     0 },
    {   287,   619,   632,     0 },
    {   288,   619,   633,     0 },
    {   289,   619,   634,     0 },
    {   290,   619,   635,     0 },
    {   291,   522,   523,     0 },
    {   292,   524,   525,     0 },
    {   293,   526,   527,     0 },
    {   294,   528,   529,     0 },
    {   295,   530,   531,     0 },
    {   296,   532,   533,     0 },
    {   297,   534,   535,     0 },
    {   298,   695,   696,     0 },
    {   299,   536,   537,     0 },
    {   300,   538,   539,     0 },
    {   301,   540,   541,     0 },
    {   302,   542,   543,     0 },
    {   303,   544,   545,     0 },
    {   304,   546,   547,     0 },
    {   305,   397,   398,   289 },
    {   306,   397,   399,   290 },
    {   307,   397,   400,   291 },
    {   308,   397,   401,   292 },
    {   309,   397,   402,   293 },
    {   310,   397,   403,   294 },
    {   311,   397,   404,   295 },
    {   312,   397,   398,   296 },
    {   313,   397,   405,   297 },
    {   314,   397,   402,   298 },
    {   315,   397,   406,   299 },
    {   316,   397,   407,   300 },
    {   317,   397,   404,   301 },
    {   318,   397,   404,   302 },
    {   319,   397,   402,   303 },
    {   320,   397,   401,   304 },
    {   321,   397,   402,   305 },
    {   322,   397,   400,   306 },
    {   323,   397,   405,   307 },
    {   324,   397,   402,   308 },
    {   325,   397,   402,   309 },
    {   326,   397,   405,   310 },
    {   327,   397,   408,   311 },
    {   328,   397,   409,   312 },
    {   329,   397,   409,   313 },
    {   330,   397,   410,   314 },
    {   331,   397,   402,   315 },
    {   332,   397,   410,   316 },
    {   333,   397,   401,   317 },
    {   334,   397,   411,   318 },
    {   335,   397,   398,   319 },
    {   336,   397,   402,   320 },
    {   337,   397,   401,   321 },
    {   338,   397,   409,   322 },
    {   339,   397,   406,   323 },
    {   340,   397,   403,   324 },
    {   341,   397,   412,   325 },
    {   342,   397,   406,   326 },
    {   343,   397,   412,   327 },
    {   344,   397,   413,   328 },
    {   345,   397,   407,   329 },
    {   346,   397,   402,   330 },
    {   347,   397,   402,   331 },
    {   348,   397,   401,   332 },
    {   349,   397,   402,   333 },
    {   350,   397,   407,   334 },
    {   351,   397,   408,   335 },
    {   352,   397,   401,   336 },
    {   353,   397,   407,   337 },
    {   354,   397,   406,   338 },
    {   355,   397,   413,     0 },
    {   356,   397,   398,     0 },
    {   357,   397,   405,     0 },
    {   358,   397,   402,     0 },
    {   359,   397,   400,     0 },
    {   360,   397,   407,     0 },
    {   361,   397,   409,     0 },
    {   362,   397,   402,     0 },
    {   363,   397,   399,     0 },
    {   364,   397,   398,     0 },
    {   365,   397,   406,     0 },
    {   366,   397,   610,     0 },
    {   367,   397,   407,     0 },
    {   368,   397,   402,     0 },
    {   369,   397,   411,     0 },
    {   370,   397,   407,     0 },
    {   371,   397,   402,     0 },
    {   372,   397,   402,     0 },
    {   373,   397,   412,     0 },
    {   374,   397,   402,     0 },
    {   375,   397,   412,     0 },
    {   376,   397,   404,     0 },
    {   377,   397,   409,     0 },
    {   378,   397,   408,     0 },
    {   379,   397,   402,     0 },
    {   380,   397,   412,     0 },
    {   381,   397,   402,     0 },
    {   382,   397,   402,     0 },
    {   383,   397,   407,     0 },
    {   384,   397,   412,     0 },
    {   385,   397,   610,     0 },
    {   386,   397,   402,     0 },
    {   387,   397,   402,     0 },
    {   388,   397,   403,     0 },
    {   389,   397,   401,     0 },
    {   390,   397,   405,     0 },
    {   391,   397,   402,     0 },
    {   392,   397,   413,     0 },
    {   393,   397,   610,     0 },
    {   394,   397,   402,     0 },
    {   395,   397,   408,     0 },
    {   396,   397,   401,     0 },
    {   397,   414,   402,   339 },
    {   398,   414,   413,   340 },
    {   399,   414,   400,   341 },
    {   400,   414,   402,   342 },
    {   401,   414,   400,   343 },
    {   402,   414,   398,   344 },
    {   403,   414,   400,   345 },
    {   404,   414,   402,   346 },
    {   405,   548,   549,     0 },
    {   406,   550,   551,     0 },
    {   407,   552,   553,     0 },
    {   408,   697,   698,     0 },
    {   409,   681,   682,     0 },
    {   410,   606,   607,     0 },
    {   411,   671,   672,     0 },
    {   412,   675,   676,     0 },
    {   413,   673,   674,     0 },
    {   414,   661,   662,     0 },
    {   415,   644,   645,     0 },
    {   416,   604,   605,     0 },
    {   417,   656,   657,     0 },
    {   418,   679,   680,     0 },
    {   419,   439,   440,   361 },
    {   420,   441,   442,   362 },
    {   421,   349,   350,   260 },
    {   422,   353,   354,   262 },
    {   423,   355,   356,   263 },
    {   424,   357,   358,   264 },
    {   425,   363,   364,     0 },
    {   426,   373,   374,     0 },
    {   427,   437,   438,   360 },
    {   428,   429,   430,     0 },
    {   429,   375,    64,     0 },
    {   430,   602,   603,     0 },
    {   431,   608,   609,     0 },
    {   432,   677,   678,     0 },
    {   433,   359,   360,   265 },
    {   434,   361,   362,   266 },
    {   435,   596,   597,     0 },
    {   436,   415,   416,   349 },
    {   437,   417,   418,     0 },
    {   438,   419,   420,     0 },
    {   439,   421,   422,     0 },
    {   440,   598,   599,   285 },
    {   441,   600,   601,     0 },
};

void MoveItemSlotInList(struct ItemSlot * itemSlots, u16 from, u16 to)
{
    if (from != to)
    {
        s16 i;
        struct ItemSlot firstSlot = itemSlots[from];
        if (to > from)
        {
            to--;
            for (i = (s16)from; i < (s16)to; i++)
            {
                itemSlots[i] = itemSlots[i + 1];
            }
        }
        else
        {
            for (i = (s16)from; i > (s16)to; i--)
            {
                itemSlots[i] = itemSlots[i - 1];
            }
        }
        itemSlots[to] = firstSlot;
    }
}

u16 GetItemIndexMapping(u16 a0, u16 a1)
{
    switch (a1)
    {
    case 0:
        if (a0 == 0)
            break;
        if (a0 == 0xFFFF)
            break;
        return sItemIndexMappings[a0][0];
    case 1:
        if (a0 == 0)
            return 699;
        if (a0 == 0xFFFF)
            return 701;
        return sItemIndexMappings[a0][1];
    case 2:
        if (a0 == 0)
            return 700;
        if (a0 == 0xFFFF)
            return 702;
        return sItemIndexMappings[a0][2];
    case 3:
        if (a0 == 0)
            break;
        if (a0 == 0xFFFF)
            break;
        return sItemIndexMappings[a0][3];
    }
    return 0;
}

u16 UpConvertItemId_Gen3to4(u16 a0)
{
    u16 i;
    for (i = 1; i <= NELEMS(sItemIndexMappings) - 1; i++)
    {
        if (a0 == sItemIndexMappings[i][3])
            return i;
    }
    return 0;
}

int sub_0206E708()
{
    return 1;
}

int sub_0206E70C()
{
    return 0;
}

void * LoadItemDataOrGfx(u16 a0, u16 a1, u32 heap_id)
{
    if (a0 > NELEMS(sItemIndexMappings) - 1)
        a0 = 0;
    switch (a1)
    {
    case 0:
        return AllocAndReadWholeNarcMemberByIdPair(NARC_ITEMTOOL_ITEMDATA_ITEM_DATA, sItemIndexMappings[a0][0], heap_id);
    case 1:
        return AllocAndReadWholeNarcMemberByIdPair(NARC_ITEMTOOL_ITEMDATA_ITEM_ICON, sItemIndexMappings[a0][1], heap_id);
    case 2:
        return AllocAndReadWholeNarcMemberByIdPair(NARC_ITEMTOOL_ITEMDATA_ITEM_ICON, sItemIndexMappings[a0][2], heap_id);
    default:
        return NULL;
    }
}

void GetItemNameIntoString(struct String * dest, u16 item_id, u32 heap_no)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0344_bin, heap_no);
    ReadMsgDataIntoString(msgData, item_id, dest);
    DestroyMsgData(msgData);
}

void GetItemDescIntoString(struct String * dest, u16 item_id, u32 heap_no)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0343_bin, heap_no);
    ReadMsgDataIntoString(msgData, item_id, dest);
    DestroyMsgData(msgData);
}

u32 GetItemAttr(u16 item, u32 attr, u32 heap_id)
{
    u32 ret;
    struct ItemData * itemData = (struct ItemData *)LoadItemDataOrGfx(item, 0, heap_id);
    ret = GetItemAttr_PreloadedItemData(itemData, attr);
    FreeToHeapExplicit(heap_id, itemData);
    return ret;
}

u32 GetItemAttr_PreloadedItemData(struct ItemData * itemData, u32 attr)
{
    switch (attr)
    {
    case ITEMATTR_PRICE:
        return itemData->price;
    case ITEMATTR_HOLD_EFFECT:
        return itemData->holdEffect;
    case ITEMATTR_HOLD_EFFECT_PARAM:
        return itemData->holdEffectParam;
    case ITEMATTR_PREVENT_TOSS:
        return itemData->prevent_toss;
    case ITEMATTR_SELECTABLE:
        return itemData->selectable;
    case ITEMATTR_POCKET:
        return itemData->pocket;
    case ITEMATTR_UNKA:
        return itemData->unkA;
    case ITEMATTR_UNKB:
        return itemData->unkB;
    case ITEMATTR_UNK4:
        return itemData->unk4;
    case ITEMATTR_UNK5:
        return itemData->unk5;
    case ITEMATTR_UNK6:
        return itemData->unk6;
    case ITEMATTR_NATURAL_GIFT_POWER:
        return itemData->naturalGiftPower;
    case ITEMATTR_NATURAL_GIFT_TYPE:
        return itemData->naturalGiftType;
    case ITEMATTR_UNK8_B:
        return itemData->unk8_B;
    case ITEMATTR_PARTY_USE:
        return itemData->partyUse;
    default:
        switch (itemData->partyUse)
        {
        case 0:
            return itemData->partyUseParam.flat;
        case 1:
            return GetItemAttrSub(&itemData->partyUseParam.sub, attr);
        default:
            return 0;
        }
    }
}

u32 GetItemAttrSub(struct ItemPartyUseParam * sub, u32 attr)
{
    switch (attr)
    {
    case ITEMATTR_SLP_HEAL:
        return sub->slp_heal;
    case ITEMATTR_PSN_HEAL:
        return sub->psn_heal;
    case ITEMATTR_BRN_HEAL:
        return sub->brn_heal;
    case ITEMATTR_FRZ_HEAL:
        return sub->frz_heal;
    case ITEMATTR_PRZ_HEAL:
        return sub->prz_heal;
    case ITEMATTR_CFS_HEAL:
        return sub->cfs_heal;
    case ITEMATTR_INF_HEAL:
        return sub->inf_heal;
    case ITEMATTR_GUARD_SPEC:
        return sub->guard_spec;
    case ITEMATTR_REVIVE:
        return sub->revive;
    case ITEMATTR_REVIVE_ALL:
        return sub->revive_all;
    case ITEMATTR_LEVEL_UP:
        return sub->level_up;
    case ITEMATTR_EVOLVE:
        return sub->evolve;
    case ITEMATTR_ATK_STAGES:
        return sub->atk_stages;
    case ITEMATTR_DEF_STAGES:
        return sub->def_stages;
    case ITEMATTR_SPATK_STAGES:
        return sub->spatk_stages;
    case ITEMATTR_SPDEF_STAGES:
        return sub->spdef_stages;
    case ITEMATTR_SPEED_STAGES:
        return sub->speed_stages;
    case ITEMATTR_ACCURACY_STAGES:
        return sub->accuracy_stages;
    case ITEMATTR_CRITRATE_STAGES:
        return sub->critrate_stages;
    case ITEMATTR_PP_UP:
        return sub->pp_up;
    case ITEMATTR_PP_MAX:
        return sub->pp_max;
    case ITEMATTR_PP_RESTORE:
        return sub->pp_restore;
    case ITEMATTR_PP_RESTORE_ALL:
        return sub->pp_restore_all;
    case ITEMATTR_HP_RESTORE:
        return sub->hp_restore;
    case ITEMATTR_HP_EV_UP:
        return sub->hp_ev_up;
    case ITEMATTR_ATK_EV_UP:
        return sub->atk_ev_up;
    case ITEMATTR_DEF_EV_UP:
        return sub->def_ev_up;
    case ITEMATTR_SPEED_EV_UP:
        return sub->speed_ev_up;
    case ITEMATTR_SPATK_EV_UP:
        return sub->spatk_ev_up;
    case ITEMATTR_SPDEF_EV_UP:
        return sub->spdef_ev_up;
    case ITEMATTR_FRIENDSHIP_MOD_LO:
        return sub->friendship_mod_lo;
    case ITEMATTR_FRIENDSHIP_MOD_MED:
        return sub->friendship_mod_med;
    case ITEMATTR_FRIENDSHIP_MOD_HI:
        return sub->friendship_mod_hi;
    case ITEMATTR_HP_EV_UP_PARAM:
        return sub->hp_ev_up_param;
    case ITEMATTR_ATK_EV_UP_PARAM:
        return sub->atk_ev_up_param;
    case ITEMATTR_DEF_EV_UP_PARAM:
        return sub->def_ev_up_param;
    case ITEMATTR_SPEED_EV_UP_PARAM:
        return sub->speed_ev_up_param;
    case ITEMATTR_SPATK_EV_UP_PARAM:
        return sub->spatk_ev_up_param;
    case ITEMATTR_SPDEF_EV_UP_PARAM:
        return sub->spdef_ev_up_param;
    case ITEMATTR_HP_RESTORE_PARAM:
        return sub->hp_restore_param;
    case ITEMATTR_PP_RESTORE_PARAM:
        return sub->pp_restore_param;
    case ITEMATTR_FRIENDSHIP_MOD_LO_PARAM:
        return sub->friendship_mod_lo_param;
    case ITEMATTR_FRIENDSHIP_MOD_MED_PARAM:
        return sub->friendship_mod_med_param;
    case ITEMATTR_FRIENDSHIP_MOD_HI_PARAM:
        return sub->friendship_mod_hi_param;
    default:
        return 0;
    }
}

u16 TMHMGetMove(u16 a0)
{
    if (a0 < ITEM_TM01 || a0 > ITEM_HM08)
        return MOVE_NONE;
    a0 -= ITEM_TM01;
    return sTMHMMoves[a0];
}

BOOL MoveIsHM(u16 a0)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        if (a0 == sTMHMMoves[i + NUM_TMS])
            return TRUE;
    }

    return FALSE;
}

u8 ItemToTMHMId(u16 a0)
{
    if (a0 < ITEM_TM01 || a0 > ITEM_HM08)
        return 0;
    return (u8)(a0 - ITEM_TM01);
}

BOOL ItemIdIsMail(u16 a0)
{
    u32 i;
    for (i = 0; i < 12; i++)
    {
        if (a0 == sMailIdxs[i])
            return TRUE;
    }
    return FALSE;
}

u8 ItemToMailId(u16 a0)
{
    u32 i;
    for (i = 0; i < 12; i++)
    {
        if (a0 == sMailIdxs[i])
            return (u8)i;
    }
    return 0;
}

u16 MailToItemId(u8 i)
{
    if (i >= 12)
        return 0;
    return sMailIdxs[i];
}

BOOL ItemIdIsBerry(u16 a0)
{
    u32 i;
    for (i = 0; i < 64; i++)
    {
        if (a0 == sBerryIdxs[i])
            return TRUE;
    }
    return FALSE;
}

u8 ItemToBerryId(u16 item_id)
{
    if (item_id < FIRST_BERRY_IDX)
        return 0xFF;
    return (u8)(item_id - FIRST_BERRY_IDX);
}

u16 BerryToItemId(u8 a0)
{
    if (a0 >= NUM_BERRIES)
        return 0xFFFF;
    return sBerryIdxs[a0];
}

u8 ItemIsBitter(u16 item_id)
{
    return item_id == ITEM_ENERGYPOWDER ||
           item_id == ITEM_ENERGY_ROOT  ||
           item_id == ITEM_HEAL_POWDER  ||
           item_id == ITEM_REVIVAL_HERB;
}

struct ItemData * LoadAllItemData(u32 heap_id)
{
    return AllocAndReadFromNarcMemberByIdPair(NARC_ITEMTOOL_ITEMDATA_ITEM_DATA, 0, heap_id, 0, sizeof(struct ItemData) * GetItemIndexMapping(ITEM_SECRETPOTION, 0));
}

struct ItemData * GetItemDataPtrFromArray(struct ItemData * a0, u16 item_id)
{
    return a0 + item_id;
}
