#include "global.h"
#include "unk_0207FC5C.h"
#include "constants/pokemon.h"

#pragma thumb on

struct UnkStruct_020FB788
{
    u32 monDataId;
    u16 gfxId;
    u16 palId;
    u16 nameIdx;
    u16 descIdx;
};

const struct UnkStruct_020FB788 UNK_020FB788[] = {
    {
        MON_DATA_HOENN_CHAMPION_RIBBON,
        72,
        0,
        RIBBON_HOENN_CHAMPION,
        80
    }, {
        MON_DATA_HOENN_COOL_RIBBON,
        73,
        0,
        RIBBON_HOENN_COOL,
        81
    }, {
        MON_DATA_HOENN_COOL_RIBBON_SUPER,
        74,
        0,
        RIBBON_HOENN_COOL_SUPER,
        82
    }, {
        MON_DATA_HOENN_COOL_RIBBON_HYPER,
        75,
        0,
        RIBBON_HOENN_COOL_HYPER,
        83
    }, {
        MON_DATA_HOENN_COOL_RIBBON_MASTER,
        76,
        0,
        RIBBON_HOENN_COOL_MASTER,
        84
    }, {
        MON_DATA_HOENN_BEAUTY_RIBBON,
        73,
        1,
        RIBBON_HOENN_BEAUTY,
        85
    }, {
        MON_DATA_HOENN_BEAUTY_RIBBON_SUPER,
        74,
        1,
        RIBBON_HOENN_BEAUTY_SUPER,
        86
    }, {
        MON_DATA_HOENN_BEAUTY_RIBBON_HYPER,
        75,
        1,
        RIBBON_HOENN_BEAUTY_HYPER,
        87
    }, {
        MON_DATA_HOENN_BEAUTY_RIBBON_MASTER,
        76,
        1,
        RIBBON_HOENN_BEAUTY_MASTER,
        88
    }, {
        MON_DATA_HOENN_CUTE_RIBBON,
        73,
        2,
        RIBBON_HOENN_CUTE,
        89
    }, {
        MON_DATA_HOENN_CUTE_RIBBON_SUPER,
        74,
        2,
        RIBBON_HOENN_CUTE_SUPER,
        90
    }, {
        MON_DATA_HOENN_CUTE_RIBBON_HYPER,
        75,
        2,
        RIBBON_HOENN_CUTE_HYPER,
        91
    }, {
        MON_DATA_HOENN_CUTE_RIBBON_MASTER,
        76,
        2,
        RIBBON_HOENN_CUTE_MASTER,
        92
    }, {
        MON_DATA_HOENN_SMART_RIBBON,
        73,
        3,
        RIBBON_HOENN_SMART,
        93
    }, {
        MON_DATA_HOENN_SMART_RIBBON_SUPER,
        74,
        3,
        RIBBON_HOENN_SMART_SUPER,
        94
    }, {
        MON_DATA_HOENN_SMART_RIBBON_HYPER,
        75,
        3,
        RIBBON_HOENN_SMART_HYPER,
        95
    }, {
        MON_DATA_HOENN_SMART_RIBBON_MASTER,
        76,
        3,
        RIBBON_HOENN_SMART_MASTER,
        96
    }, {
        MON_DATA_HOENN_TOUGH_RIBBON,
        73,
        4,
        RIBBON_HOENN_TOUGH,
        97
    }, {
        MON_DATA_HOENN_TOUGH_RIBBON_SUPER,
        74,
        4,
        RIBBON_HOENN_TOUGH_SUPER,
        98
    }, {
        MON_DATA_HOENN_TOUGH_RIBBON_HYPER,
        75,
        4,
        RIBBON_HOENN_TOUGH_HYPER,
        99
    }, {
        MON_DATA_HOENN_TOUGH_RIBBON_MASTER,
        76,
        4,
        RIBBON_HOENN_TOUGH_MASTER,
        100
    }, {
        MON_DATA_HOENN_WINNING_RIBBON,
        78,
        0,
        RIBBON_HOENN_WINNING,
        101
    }, {
        MON_DATA_HOENN_VICTORY_RIBBON,
        77,
        0,
        RIBBON_HOENN_VICTORY,
        102
    }, {
        MON_DATA_HOENN_ARTIST_RIBBON,
        79,
        1,
        RIBBON_HOENN_ARTIST,
        103
    }, {
        MON_DATA_HOENN_EFFORT_RIBBON,
        80,
        2,
        RIBBON_HOENN_EFFORT,
        104
    }, {
        MON_DATA_HOENN_MARINE_RIBBON,
        81,
        1,
        RIBBON_HOENN_MARINE,
        0 | 0x8000
    }, {
        MON_DATA_HOENN_LAND_RIBBON,
        81,
        3,
        RIBBON_HOENN_LAND,
        1 | 0x8000
    }, {
        MON_DATA_HOENN_SKY_RIBBON,
        81,
        4,
        RIBBON_HOENN_SKY,
        2 | 0x8000
    }, {
        MON_DATA_HOENN_COUNTRY_RIBBON,
        82,
        3,
        RIBBON_HOENN_COUNTRY,
        178
    }, {
        MON_DATA_HOENN_NATIONAL_RIBBON,
        82,
        4,
        RIBBON_HOENN_NATIONAL,
        190
    }, {
        MON_DATA_HOENN_EARTH_RIBBON,
        83,
        0,
        RIBBON_HOENN_EARTH,
        191
    }, {
        MON_DATA_HOENN_WORLD_RIBBON,
        83,
        1,
        RIBBON_HOENN_WORLD,
        178
    }, {
        MON_DATA_SINNOH_CHAMP_RIBBON,
        88,
        0,
        RIBBON_SINNOH_CHAMP,
        105
    }, {
        MON_DATA_COOL_RIBBON,
        89,
        0,
        RIBBON_COOL,
        106
    }, {
        MON_DATA_COOL_RIBBON_GREAT,
        90,
        0,
        RIBBON_COOL_GREAT,
        107
    }, {
        MON_DATA_COOL_RIBBON_ULTRA,
        91,
        0,
        RIBBON_COOL_ULTRA,
        108
    }, {
        MON_DATA_COOL_RIBBON_MASTER,
        92,
        0,
        RIBBON_COOL_MASTER,
        109
    }, {
        MON_DATA_BEAUTY_RIBBON,
        89,
        1,
        RIBBON_BEAUTY,
        110
    }, {
        MON_DATA_BEAUTY_RIBBON_GREAT,
        90,
        1,
        RIBBON_BEAUTY_GREAT,
        111
    }, {
        MON_DATA_BEAUTY_RIBBON_ULTRA,
        91,
        1,
        RIBBON_BEAUTY_ULTRA,
        112
    }, {
        MON_DATA_BEAUTY_RIBBON_MASTER,
        92,
        1,
        RIBBON_BEAUTY_MASTER,
        113
    }, {
        MON_DATA_CUTE_RIBBON,
        89,
        2,
        RIBBON_CUTE,
        114
    }, {
        MON_DATA_CUTE_RIBBON_GREAT,
        90,
        2,
        RIBBON_CUTE_GREAT,
        115
    }, {
        MON_DATA_CUTE_RIBBON_ULTRA,
        91,
        2,
        RIBBON_CUTE_ULTRA,
        116
    }, {
        MON_DATA_CUTE_RIBBON_MASTER,
        92,
        2,
        RIBBON_CUTE_MASTER,
        117
    }, {
        MON_DATA_SMART_RIBBON,
        89,
        3,
        RIBBON_SMART,
        118
    }, {
        MON_DATA_SMART_RIBBON_GREAT,
        90,
        3,
        RIBBON_SMART_GREAT,
        119
    }, {
        MON_DATA_SMART_RIBBON_ULTRA,
        91,
        3,
        RIBBON_SMART_ULTRA,
        120
    }, {
        MON_DATA_SMART_RIBBON_MASTER,
        92,
        3,
        RIBBON_SMART_MASTER,
        121
    }, {
        MON_DATA_TOUGH_RIBBON,
        89,
        4,
        RIBBON_TOUGH,
        122
    }, {
        MON_DATA_TOUGH_RIBBON_GREAT,
        90,
        4,
        RIBBON_TOUGH_GREAT,
        123
    }, {
        MON_DATA_TOUGH_RIBBON_ULTRA,
        91,
        4,
        RIBBON_TOUGH_ULTRA,
        124
    }, {
        MON_DATA_TOUGH_RIBBON_MASTER,
        92,
        4,
        RIBBON_TOUGH_MASTER,
        125
    }, {
        MON_DATA_ABILITY_RIBBON,
        93,
        0,
        RIBBON_ABILITY,
        126
    }, {
        MON_DATA_GREAT_ABILITY_RIBBON,
        94,
        0,
        RIBBON_GREAT_ABILITY,
        127
    }, {
        MON_DATA_DOUBLE_ABILITY_RIBBON,
        95,
        0,
        RIBBON_DOUBLE_ABILITY,
        128
    }, {
        MON_DATA_MULTI_ABILITY_RIBBON,
        96,
        0,
        RIBBON_MULTI_ABILITY,
        129
    }, {
        MON_DATA_PAIR_ABILITY_RIBBON,
        97,
        0,
        RIBBON_PAIR_ABILITY,
        130
    }, {
        MON_DATA_WORLD_ABILITY_RIBBON,
        98,
        0,
        RIBBON_WORLD_ABILITY,
        131
    }, {
        MON_DATA_ALERT_RIBBON,
        99,
        2,
        RIBBON_ALERT,
        132
    }, {
        MON_DATA_SHOCK_RIBBON,
        100,
        0,
        RIBBON_SHOCK,
        133
    }, {
        MON_DATA_DOWNCAST_RIBBON,
        101,
        1,
        RIBBON_DOWNCAST,
        134
    }, {
        MON_DATA_CARELESS_RIBBON,
        102,
        2,
        RIBBON_CARELESS,
        135
    }, {
        MON_DATA_RELAX_RIBBON,
        103,
        3,
        RIBBON_RELAX,
        136
    }, {
        MON_DATA_SNOOZE_RIBBON,
        104,
        0,
        RIBBON_SNOOZE,
        137
    }, {
        MON_DATA_SMILE_RIBBON,
        105,
        2,
        RIBBON_SMILE,
        138
    }, {
        MON_DATA_GORGEOUS_RIBBON,
        106,
        1,
        RIBBON_GORGEOUS,
        139
    }, {
        MON_DATA_ROYAL_RIBBON,
        107,
        3,
        RIBBON_ROYAL,
        140
    }, {
        MON_DATA_GORGEOUS_ROYAL_RIBBON,
        108,
        0,
        RIBBON_GORGEOUS_ROYAL,
        141
    }, {
        MON_DATA_FOOTPRINT_RIBBON,
        109,
        0,
        RIBBON_FOOTPRINT,
        142
    }, {
        MON_DATA_RECORD_RIBBON,
        110,
        1,
        RIBBON_RECORD,
        143
    }, {
        MON_DATA_HISTORY_RIBBON,
        111,
        3,
        RIBBON_HISTORY,
        144
    }, {
        MON_DATA_LEGEND_RIBBON,
        112,
        0,
        RIBBON_LEGEND,
        145
    }, {
        MON_DATA_RED_RIBBON,
        113,
        0,
        RIBBON_RED,
        7 | 0x8000
    }, {
        MON_DATA_GREEN_RIBBON,
        114,
        3,
        RIBBON_GREEN,
        8 | 0x8000
    }, {
        MON_DATA_BLUE_RIBBON,
        115,
        1,
        RIBBON_BLUE,
        9 | 0x8000
    }, {
        MON_DATA_FESTIVAL_RIBBON,
        116,
        1,
        RIBBON_FESTIVAL,
        10 | 0x8000
    }, {
        MON_DATA_CARNIVAL_RIBBON,
        117,
        0,
        RIBBON_CARNIVAL,
        11 | 0x8000
    }, {
        MON_DATA_CLASSIC_RIBBON,
        118,
        1,
        RIBBON_CLASSIC,
        12 | 0x8000
    }, {
        MON_DATA_PREMIER_RIBBON,
        119,
        0,
        RIBBON_PREMIER,
        13 | 0x8000
    }
};

u32 FUN_0207FC5C(u8 a0, u32 a1)
{
    switch (a1)
    {
    case 0:
        return UNK_020FB788[a0].monDataId;
    case 1:
        return UNK_020FB788[a0].gfxId;
    case 2:
        return UNK_020FB788[a0].palId;
    case 3:
        return UNK_020FB788[a0].nameIdx;
    case 4:
        return UNK_020FB788[a0].descIdx;
    default:
        return 0;
    }
}

int FUN_0207FCC0(u8 * a0, u32 a1)
{
    int ret = (int)UNK_020FB788[a1].descIdx;
    if (ret & 0x8000)
        ret = a0[(u8)ret] + 0x92;
    return ret;
}

u8 FUN_0207FCE0(u32 a0)
{
    int ret = (int)UNK_020FB788[a0].descIdx;
    if (ret & 0x8000)
        return (u8)ret;
    return 0xFF;
}
