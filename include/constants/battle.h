#ifndef POKEDIAMOND_CONSTANTS_BATTLE_H
#define POKEDIAMOND_CONSTANTS_BATTLE_H

// Battler IDs
#define BATTLER_NONE    0xFF
#define BATTLER_PLAYER  0
#define BATTLER_ENEMY   1
#define BATTLER_PLAYER2 2
#define BATTLER_ENEMY2  3

// Battle outcome
// Used with BattleSetup::winFlag
#define BATTLE_OUTCOME_NONE        0
#define BATTLE_OUTCOME_WIN         1
#define BATTLE_OUTCOME_LOSE        2
#define BATTLE_OUTCOME_DRAW        3
#define BATTLE_OUTCOME_MON_CAUGHT  4
#define BATTLE_OUTCOME_PLAYER_FLED 5
#define BATTLE_OUTCOME_FOE_FLED    6

// Battle Type
#define BATTLE_TYPE_NONE           0
#define BATTLE_TYPE_TRAINER        (1 << 0)
#define BATTLE_TYPE_DOUBLES        (1 << 1)
#define BATTLE_TYPE_LINK           (1 << 2)
#define BATTLE_TYPE_MULTI          (1 << 3)
#define BATTLE_TYPE_INGAME_PARTNER (1 << 4)
#define BATTLE_TYPE_SAFARI         (1 << 5)
#define BATTLE_TYPE_6              (1 << 6)
#define BATTLE_TYPE_TOWER          (1 << 7)
#define BATTLE_TYPE_8              (1 << 8)
#define BATTLE_TYPE_PAL_PARK       (1 << 9)
#define BATTLE_TYPE_TUTORIAL       (1 << 10)
#define BATTLE_TYPE_11             (1 << 11)
#define BATTLE_TYPE_DEBUG          (1 << 31)

#define BATTLE_TYPE_NO_EXP (BATTLE_TYPE_LINK | BATTLE_TYPE_SAFARI | BATTLE_TYPE_TOWER | BATTLE_TYPE_PAL_PARK)

#define MOVE_EFFECT_NORMAL_HIT            0
#define MOVE_EFFECT_SLEEP                 1
#define MOVE_EFFECT_POISON_HIT            2
#define MOVE_EFFECT_DRAIN_HP              3
#define MOVE_EFFECT_BURN_HIT              4
#define MOVE_EFFECT_FREEZE_HIT            5
#define MOVE_EFFECT_PARALYZE_HIT          6
#define MOVE_EFFECT_EXPLOSION             7
#define MOVE_EFFECT_DREAM_EATER           8
#define MOVE_EFFECT_MIRROR_MOVE           9
#define MOVE_EFFECT_ATTACK_UP             10
#define MOVE_EFFECT_DEFENSE_UP            11
#define MOVE_EFFECT_SPEED_UP              12 // unused
#define MOVE_EFFECT_SPATK_UP              13
#define MOVE_EFFECT_SPDEF_UP              14 // unused
#define MOVE_EFFECT_ACCURACY_UP           15 // unused
#define MOVE_EFFECT_EVASION_UP            16
#define MOVE_EFFECT_ALWAYS_HIT            17
#define MOVE_EFFECT_ATTACK_DOWN           18
#define MOVE_EFFECT_DEFENSE_DOWN          19
#define MOVE_EFFECT_SPEED_DOWN            20
#define MOVE_EFFECT_SPATK_DOWN            21 // unused
#define MOVE_EFFECT_SPDEF_DOWN            22 // unused
#define MOVE_EFFECT_ACCURACY_DOWN         23
#define MOVE_EFFECT_EVASION_DOWN          24
#define MOVE_EFFECT_STATS_RESET           25
#define MOVE_EFFECT_BIDE                  26
#define MOVE_EFFECT_RAMPAGE               27
#define MOVE_EFFECT_SWITCH_FOE            28
#define MOVE_EFFECT_MULTIHIT_2_5          29
#define MOVE_EFFECT_CONVERSION            30
#define MOVE_EFFECT_FLINCH_HIT            31
#define MOVE_EFFECT_RESTORE_HP            32
#define MOVE_EFFECT_TOXIC                 33
#define MOVE_EFFECT_PAYDAY                34
#define MOVE_EFFECT_LIGHT_SCREEN          35
#define MOVE_EFFECT_TRI_ATTACK            36
#define MOVE_EFFECT_SLEEP_USER            37
#define MOVE_EFFECT_OHKO                  38
#define MOVE_EFFECT_RAZOR_WIND            39
#define MOVE_EFFECT_SUPER_FANG            40
#define MOVE_EFFECT_FIXED_40              41
#define MOVE_EFFECT_TRAP_HIT              42
#define MOVE_EFFECT_HIGH_CRIT             43
#define MOVE_EFFECT_DOUBLE_HIT            44
#define MOVE_EFFECT_JUMP_KICK             45
#define MOVE_EFFECT_MIST                  46
#define MOVE_EFFECT_CRIT_CHANCE_UP        47
#define MOVE_EFFECT_RECOIL_HIT            48
#define MOVE_EFFECT_CONFUSE               49
#define MOVE_EFFECT_ATTACK_2UP            50
#define MOVE_EFFECT_DEFENSE_2UP           51
#define MOVE_EFFECT_SPEED_2UP             52
#define MOVE_EFFECT_SPATK_2UP             53
#define MOVE_EFFECT_SPDEF_2UP             54
#define MOVE_EFFECT_ACCURACY_2UP          55 // unused
#define MOVE_EFFECT_EVASION_2UP           56 // unused
#define MOVE_EFFECT_TRANSFORM             57
#define MOVE_EFFECT_ATTACK_2DOWN          58
#define MOVE_EFFECT_DEFENSE_2DOWN         59
#define MOVE_EFFECT_SPEED_2DOWN           60
#define MOVE_EFFECT_SPATK_2DOWN           61 // unused
#define MOVE_EFFECT_SPDEF_2DOWN           62
#define MOVE_EFFECT_ACCURACY_2DOWN        63 // unused
#define MOVE_EFFECT_EVASION_2DOWN         64 // unused
#define MOVE_EFFECT_REFLECT               65
#define MOVE_EFFECT_POISON                66
#define MOVE_EFFECT_PARALYZE              67
#define MOVE_EFFECT_ATTACK_DOWN_HIT       68
#define MOVE_EFFECT_DEFENSE_DOWN_HIT      69
#define MOVE_EFFECT_SPEED_DOWN_HIT        70
#define MOVE_EFFECT_SPATK_DOWN_HIT        71
#define MOVE_EFFECT_SPDEF_DOWN_HIT        72
#define MOVE_EFFECT_ACCURACY_DOWN_HIT     73
#define MOVE_EFFECT_EVASION_DOWN_HIT      74 // unused
#define MOVE_EFFECT_SKY_ATTACK            75
#define MOVE_EFFECT_CONFUSE_HIT           76
#define MOVE_EFFECT_POISON_DOUBLE_HIT     77
#define MOVE_EFFECT_VITAL_THROW           78
#define MOVE_EFFECT_SUBSTITUTE            79
#define MOVE_EFFECT_HIT_RECHARGE          80
#define MOVE_EFFECT_RAGE                  81
#define MOVE_EFFECT_MIMIC                 82
#define MOVE_EFFECT_METRONOME             83
#define MOVE_EFFECT_LEECH_SEED            84
#define MOVE_EFFECT_NONE                  85
#define MOVE_EFFECT_DISABLE               86
#define MOVE_EFFECT_LEVEL_DAMAGE          87
#define MOVE_EFFECT_RANDOM_DAMAGE         88
#define MOVE_EFFECT_COUNTER               89
#define MOVE_EFFECT_ENCORE                90
#define MOVE_EFFECT_PAIN_SPLIT            91
#define MOVE_EFFECT_SNORE                 92
#define MOVE_EFFECT_CONVERSION_2          93
#define MOVE_EFFECT_ENSURE_NEXT_HIT       94
#define MOVE_EFFECT_SKETCH                95
#define MOVE_EFFECT_UNK096                96 // unused
#define MOVE_EFFECT_SLEEP_TALK            97
#define MOVE_EFFECT_DESTINY_BOND          98
#define MOVE_EFFECT_STRONGER_LOW_HP       99
#define MOVE_EFFECT_SPITE                 100
#define MOVE_EFFECT_FALSE_SWIPE           101
#define MOVE_EFFECT_HEAL_ALL_STATUS       102
#define MOVE_EFFECT_PRIORITY_HIT          103
#define MOVE_EFFECT_TRIPLE_KICK           104
#define MOVE_EFFECT_STEAL_ITEM            105
#define MOVE_EFFECT_PREVENT_ESCAPE        106
#define MOVE_EFFECT_NIGHTMARE             107
#define MOVE_EFFECT_MINIMIZE              108
#define MOVE_EFFECT_CURSE                 109
#define MOVE_EFFECT_UNK110                110 // unused
#define MOVE_EFFECT_PROTECT               111
#define MOVE_EFFECT_SPIKES                112
#define MOVE_EFFECT_IDENTIFY              113
#define MOVE_EFFECT_PERISH_SONG           114
#define MOVE_EFFECT_SANDSTORM             115
#define MOVE_EFFECT_ENDURE                116
#define MOVE_EFFECT_INCREASING_HIT        117
#define MOVE_EFFECT_SWAGGER               118
#define MOVE_EFFECT_FURY_CUTTER           119
#define MOVE_EFFECT_ATTRACT               120
#define MOVE_EFFECT_RETURN                121
#define MOVE_EFFECT_PRESENT               122
#define MOVE_EFFECT_FRUSTRATION           123
#define MOVE_EFFECT_SAFEGUARD             124
#define MOVE_EFFECT_BURN_HIT_THAW         125
#define MOVE_EFFECT_MAGNITUDE             126
#define MOVE_EFFECT_BATON_PASS            127
#define MOVE_EFFECT_PURSUIT               128
#define MOVE_EFFECT_RAPID_SPIN            129
#define MOVE_EFFECT_FIXED_20              130
#define MOVE_EFFECT_UNK131                131 // unused
#define MOVE_EFFECT_RESTORE_HP_DAYTIME    132
#define MOVE_EFFECT_UNK133                133 // unused
#define MOVE_EFFECT_UNK134                134 // unused
#define MOVE_EFFECT_HIDDEN_POWER          135 // unused
#define MOVE_EFFECT_RAIN                  136
#define MOVE_EFFECT_SUNNY                 137
#define MOVE_EFFECT_DEFENSE_UP_HIT        138
#define MOVE_EFFECT_ATTACK_UP_HIT         139
#define MOVE_EFFECT_STATS_UP_HIT          140
#define MOVE_EFFECT_UNK141                141 // unused
#define MOVE_EFFECT_BELLY_DRUM            142
#define MOVE_EFFECT_PSYCH_UP              143
#define MOVE_EFFECT_MIRROR_COAT           144
#define MOVE_EFFECT_SKULL_BASH            145
#define MOVE_EFFECT_TWISTER               146
#define MOVE_EFFECT_EARTHQUAKE            147
#define MOVE_EFFECT_HIT_LATER             148
#define MOVE_EFFECT_GUST                  149
#define MOVE_EFFECT_STOMP                 150
#define MOVE_EFFECT_SOLAR_BEAM            151
#define MOVE_EFFECT_THUNDER               152
#define MOVE_EFFECT_TELEPORT              153
#define MOVE_EFFECT_BEAT_UP               154
#define MOVE_EFFECT_FLY                   155
#define MOVE_EFFECT_DEFENSE_CURL          156
#define MOVE_EFFECT_UNK157                157 // unused
#define MOVE_EFFECT_FAKE_OUT              158
#define MOVE_EFFECT_UPROAR                159
#define MOVE_EFFECT_STOCKPILE             160
#define MOVE_EFFECT_SPIT_UP               161
#define MOVE_EFFECT_SWALLOW               162
#define MOVE_EFFECT_UNK163                163 // unused
#define MOVE_EFFECT_HAIL                  164
#define MOVE_EFFECT_TORMENT               165
#define MOVE_EFFECT_FLATTER               166
#define MOVE_EFFECT_BURN                  167
#define MOVE_EFFECT_MEMENTO               168
#define MOVE_EFFECT_FACADE                169
#define MOVE_EFFECT_FOCUS_PUNCH           170
#define MOVE_EFFECT_SMELLING_SALTS        171
#define MOVE_EFFECT_FOLLOW_ME             172
#define MOVE_EFFECT_NATURE_POWER          173
#define MOVE_EFFECT_CHARGE                174
#define MOVE_EFFECT_TAUNT                 175
#define MOVE_EFFECT_HELPING_HAND          176
#define MOVE_EFFECT_SWAP_ITEMS            177
#define MOVE_EFFECT_ROLE_PLAY             178
#define MOVE_EFFECT_WISH                  179
#define MOVE_EFFECT_ASSIST                180
#define MOVE_EFFECT_INGRAIN               181
#define MOVE_EFFECT_SUPERPOWER            182
#define MOVE_EFFECT_MAGIC_COAT            183
#define MOVE_EFFECT_RECYCLE               184
#define MOVE_EFFECT_REVENGE               185
#define MOVE_EFFECT_BRICK_BREAK           186
#define MOVE_EFFECT_YAWN                  187
#define MOVE_EFFECT_KNOCK_OFF             188
#define MOVE_EFFECT_ENDEAVOR              189
#define MOVE_EFFECT_STRONGER_HIGH_HP      190
#define MOVE_EFFECT_SKILL_SWAP            191
#define MOVE_EFFECT_IMPRISON              192
#define MOVE_EFFECT_REFRESH               193
#define MOVE_EFFECT_GRUDGE                194
#define MOVE_EFFECT_SNATCH                195
#define MOVE_EFFECT_STRONGER_HEAVIER      196
#define MOVE_EFFECT_SECRET_POWER          197
#define MOVE_EFFECT_RECOIL_HIT_HARD       198
#define MOVE_EFFECT_CONFUSE_ALL           199
#define MOVE_EFFECT_BURN_HIT_HIGH_CRIT    200
#define MOVE_EFFECT_MUD_SPORT             201
#define MOVE_EFFECT_TOXIC_HIT             202
#define MOVE_EFFECT_WEATHER_BALL          203
#define MOVE_EFFECT_HIT_USER_SPATK_2_DOWN 204
#define MOVE_EFFECT_ATTACK_DEFENSE_DOWN   205
#define MOVE_EFFECT_DEFENSE_SPDEF_UP      206
#define MOVE_EFFECT_SKY_UPPERCUT          207
#define MOVE_EFFECT_ATTACK_DEFENSE_UP     208
#define MOVE_EFFECT_POISON_HIT_HIGH_CRIT  209
#define MOVE_EFFECT_WATER_SPORT           210
#define MOVE_EFFECT_SPATK_SPDEF_UP        211
#define MOVE_EFFECT_ATTACK_SPEED_UP       212
#define MOVE_EFFECT_CAMOUFLAGE            213
#define MOVE_EFFECT_ROOST                 214
#define MOVE_EFFECT_GRAVITY               215
#define MOVE_EFFECT_MIRACLE_EYE           216
#define MOVE_EFFECT_WAKE_UP_SLAP          217
#define MOVE_EFFECT_HAMMER_ARM            218
#define MOVE_EFFECT_GYRO_BALL             219
#define MOVE_EFFECT_HEALING_WISH          220
#define MOVE_EFFECT_BRINE                 221
#define MOVE_EFFECT_NATURAL_GIFT          222
#define MOVE_EFFECT_FEINT                 223
#define MOVE_EFFECT_BUG_BITE              224
#define MOVE_EFFECT_TAILWIND              225
#define MOVE_EFFECT_ACUPRESSURE           226
#define MOVE_EFFECT_METAL_BURST           227
#define MOVE_EFFECT_U_TURN                228
#define MOVE_EFFECT_CLOSE_COMBAT          229
#define MOVE_EFFECT_PAYBACK               230
#define MOVE_EFFECT_ASSURANCE             231
#define MOVE_EFFECT_EMBARGO               232
#define MOVE_EFFECT_FLING                 233
#define MOVE_EFFECT_PSYCHO_SHIFT          234
#define MOVE_EFFECT_TRUMP_CARD            235
#define MOVE_EFFECT_HEAL_BLOCK            236
#define MOVE_EFFECT_CRUSH_GRIP            237
#define MOVE_EFFECT_POWER_TRICK           238
#define MOVE_EFFECT_GASTRO_ACID           239
#define MOVE_EFFECT_LUCKY_CHANT           240
#define MOVE_EFFECT_ME_FIRST              241
#define MOVE_EFFECT_COPYCAT               242
#define MOVE_EFFECT_POWER_SWAP            243
#define MOVE_EFFECT_GUARD_SWAP            244
#define MOVE_EFFECT_PUNISHMENT            245
#define MOVE_EFFECT_LAST_RESORT           246
#define MOVE_EFFECT_WORRY_SEED            247
#define MOVE_EFFECT_SUCKER_PUNCH          248
#define MOVE_EFFECT_TOXIC_SPIKES          249
#define MOVE_EFFECT_HEART_SWAP            250
#define MOVE_EFFECT_AQUA_RING             251
#define MOVE_EFFECT_MAGNET_RISE           252
#define MOVE_EFFECT_FLARE_BLITZ           253
#define MOVE_EFFECT_STRUGGLE              254
#define MOVE_EFFECT_DIVE                  255
#define MOVE_EFFECT_DIG                   256
#define MOVE_EFFECT_SURF                  257
#define MOVE_EFFECT_DEFOG                 258
#define MOVE_EFFECT_TRICK_ROOM            259
#define MOVE_EFFECT_BLIZZARD              260
#define MOVE_EFFECT_WHIRLPOOL             261
#define MOVE_EFFECT_VOLT_TACKLE           262
#define MOVE_EFFECT_BOUNCE                263
#define MOVE_EFFECT_UNK264                264 // unused
#define MOVE_EFFECT_CAPTIVATE             265
#define MOVE_EFFECT_STEALTH_ROCK          266
#define MOVE_EFFECT_CHATTER               267
#define MOVE_EFFECT_JUDGMENT              268
#define MOVE_EFFECT_HEAD_SMASH            269
#define MOVE_EFFECT_LUNAR_DANCE           270
#define MOVE_EFFECT_SEED_FLARE            271
#define MOVE_EFFECT_SHADOW_FORCE          272
#define MOVE_EFFECT_FIRE_FANG             273
#define MOVE_EFFECT_ICE_FANG              274
#define MOVE_EFFECT_THUNDER_FANG          275
#define MOVE_EFFECT_CHARGE_BEAM           276

#endif // POKEDIAMOND_CONSTANTS_BATTLE_H
