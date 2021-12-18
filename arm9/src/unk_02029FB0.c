#include "global.h"
#include "pokedex.h"
#include "unk_02029FB0.h"

const u16 UNK_020EEA7C[] = {
    0x0001, // 00
    0x0001, // 01
    0x0001, // 02
    0x0001, // 03
    0x0001, // 04
    0x0001, // 05
    0x0002, // 06
    0x0002, // 07
    0x0002, // 08
    0x0002, // 09
    0x0003, // 10
    0x0003, // 11
    0x0003, // 12
    0x0007, // 13
    0x0007, // 14
    0x0007, // 15
    0x000A, // 16
    0x000A, // 17
    0x000B, // 18
    0x000B, // 19
    0x000B, // 20
    0x000B, // 21
    0x0014, // 22
    0x001E, // 23
    0x0023, // 24
    0x0028, // 25
    0x01F4, // 26
    0x2710, // 27
    0x001E, // 28
    0x001E, // 29
    0x0002, // 30
    0x0005, // 31
    0x0001, // 32
    0x0001, // 33
    0x0005, // 34
    0x0003, // 35
    0x0001, // 36
    0x0001, // 37
};

u8 UNK_02105CD8[] = {
    TRUE,  // 000
    TRUE,  // 001
    FALSE, // 002
    TRUE,  // 003
    TRUE,  // 004
    TRUE,  // 005
    TRUE,  // 006
    TRUE,  // 007
    TRUE,  // 008
    FALSE, // 009
    FALSE, // 010
    FALSE, // 011
    TRUE,  // 012
    TRUE,  // 013
    TRUE,  // 014
    TRUE,  // 015
    TRUE,  // 016
    TRUE,  // 017
    TRUE,  // 018
    TRUE,  // 019
    TRUE,  // 020
    TRUE,  // 021
    TRUE,  // 022
    TRUE,  // 023
    TRUE,  // 024
    TRUE,  // 025
    TRUE,  // 026
    TRUE,  // 027
    TRUE,  // 028
    TRUE,  // 029
    TRUE,  // 030
    TRUE,  // 031
    TRUE,  // 032
    TRUE,  // 033
    TRUE,  // 034
    TRUE,  // 035
    TRUE,  // 036
    TRUE,  // 037
    TRUE,  // 038
    TRUE,  // 039
    TRUE,  // 040
    FALSE, // 041
    FALSE, // 042
    FALSE, // 043

    TRUE,  // 044
    TRUE,  // 045
    FALSE, // 046
    TRUE,  // 047
    TRUE,  // 048
    FALSE, // 049
    FALSE, // 050
    FALSE, // 051
    FALSE, // 052
    FALSE, // 053
    FALSE, // 054
    FALSE, // 055
    FALSE, // 056
    FALSE, // 057
    FALSE, // 058
    FALSE, // 059
    FALSE, // 060
    FALSE, // 061
    FALSE, // 062
    FALSE, // 063
    FALSE, // 064
    FALSE, // 065
    FALSE, // 066
    TRUE,  // 067
    FALSE, // 068
    FALSE, // 069
    FALSE, // 070
    FALSE, // 071
    FALSE, // 072
    FALSE, // 073
    FALSE, // 074
    FALSE, // 075
    FALSE, // 076
    FALSE, // 077
    FALSE, // 078
    FALSE, // 079
    FALSE, // 080
    FALSE, // 081
    FALSE, // 082
    FALSE, // 083
    FALSE, // 084
    TRUE,  // 085
    FALSE, // 086
    FALSE, // 087
    FALSE, // 088
    FALSE, // 089
    FALSE, // 090
    FALSE, // 091
    FALSE, // 092
    FALSE, // 093
    FALSE, // 094
    FALSE, // 095
    FALSE, // 096
    FALSE, // 097
    FALSE, // 098
    FALSE, // 099
    FALSE, // 100
    FALSE, // 101
    FALSE, // 102
    FALSE, // 103
    FALSE, // 104
    FALSE, // 105
    FALSE, // 106
    FALSE, // 107
    FALSE, // 108
    FALSE, // 109
    FALSE, // 110
    FALSE, // 111
    FALSE, // 112
    FALSE, // 113
    FALSE, // 114
    FALSE, // 115
    FALSE, // 116
    FALSE, // 117
    FALSE, // 118
    FALSE, // 119
    FALSE, // 120
    FALSE, // 121
};

static inline s32 GetOffsetToUnk00(s32 a0)
{
    return a0;
}

static inline s32 GetOffsetToUnkB0(s32 a0)
{
    return a0 - 44;
}

THUMB_FUNC u32 Sav2_GameStats_sizeof(void)
{
    return sizeof(struct GameStats);
}

THUMB_FUNC void Sav2_GameStats_init(struct GameStats * ptr)
{
    MI_CpuClear32(ptr, sizeof(struct GameStats));
}

THUMB_FUNC struct GameStats * Sav2_GameStats_get(struct SaveBlock2 * sav2)
{
    return SavArray_get(sav2, 20);
}

THUMB_FUNC u32 GameStats_GetValue(struct GameStats * ptr, s32 a1)
{
    if (a1 < 44)
    {
        return ptr->unk_00[GetOffsetToUnk00(a1)];
    }
    else if (a1 < 121)
    {
        return ptr->unk_B0[GetOffsetToUnkB0(a1)];
    }
    else
    {
        GF_ASSERT(0);
        return 0;
    }
}

THUMB_FUNC u32 GameStats_SetValue(struct GameStats * ptr, s32 a1, u32 a2)
{
    if (a1 < 44)
    {
        ptr->unk_00[GetOffsetToUnk00(a1)] = a2;
    }
    else if (a1 < 121)
    {
        ptr->unk_B0[GetOffsetToUnkB0(a1)] = a2;
    }
    else
    {
        GF_ASSERT(0);
    }
    return GameStats_GetValue(ptr, a1);
}

THUMB_FUNC u32 GameStats_GetMaxValue(s32 a0)
{
    if (a0 < 44)
    {
        if (UNK_02105CD8[a0])
            return 999999999;
        else
            return 999999;
    }
    else if (a0 < 121)
    {
        if (UNK_02105CD8[a0])
            return 0xFFFF;
        else
            return 9999;
    }
    else
    {
        GF_ASSERT(0);
        return 0;
    }
}

THUMB_FUNC u16 GameStats_GetStdInc(s32 a0)
{
    return UNK_020EEA7C[a0];
}

THUMB_FUNC u32 GameStats_SetCapped(struct GameStats * ptr, s32 a1, u32 a2)
{
    u32 r2 = GameStats_GetMaxValue(a1);
    if (a2 < r2)
    {
        return GameStats_SetValue(ptr, a1, a2);
    }
    else
    {
        return GameStats_SetValue(ptr, a1, r2);
    }
}

THUMB_FUNC u32 GameStats_UpdateBounded(struct GameStats * ptr, s32 a1, u32 a2)
{
    u32 r4 = GameStats_GetMaxValue(a1);
    u32 r0 = GameStats_GetValue(ptr, a1);
    if (a2 > r4)
    {
        a2 = r4;
    }
    if (r0 < a2)
    {
        return GameStats_SetValue(ptr, a1, a2);
    }
    else if (r0 > r4)
    {
        return GameStats_SetValue(ptr, a1, r4);
    }
    else
    {
        return r0;
    }
}

THUMB_FUNC u32 GameStats_Inc(struct GameStats * ptr, s32 a1)
{
    u32 r4 = GameStats_GetMaxValue(a1);
    u32 r2 = GameStats_GetValue(ptr, a1) + 1;
    if (r2 < r4)
    {
        return GameStats_SetValue(ptr, a1, r2);
    }
    else
    {
        return GameStats_SetValue(ptr, a1, r4);
    }
}

THUMB_FUNC u32 GameStats_Add(struct GameStats * ptr, s32 a1, u32 a2)
{
    u32 r6 = GameStats_GetMaxValue(a1);
    u32 r2 = GameStats_GetValue(ptr, a1);
    r2 += a2;
    if (r2 < r6)
    {
        return GameStats_SetValue(ptr, a1, r2);
    }
    else
    {
        return GameStats_SetValue(ptr, a1, r6);
    }
}

THUMB_FUNC u32 GameStats_GetCapped(struct GameStats * ptr, s32 a1)
{
    u32 r4 = GameStats_GetMaxValue(a1);
    u32 r0 = GameStats_GetValue(ptr, a1);
    if (r0 <= r4)
        r4 = r0;
    return r4;
}

THUMB_FUNC u32 GameStats_AddSpecial(struct GameStats * ptr, s32 a1)
{
    GF_ASSERT(a1 < 38);
    u32 r0 = GameStats_GetCapped(ptr, 0) + GameStats_GetStdInc(a1);
    if (r0 > 99999999)
    {
        return GameStats_SetCapped(ptr, 0, 99999999);
    }
    else
    {
        return GameStats_Add(ptr, 0, GameStats_GetStdInc(a1));
    }
}

THUMB_FUNC u32 GameStats_GetStat0(struct GameStats * ptr)
{
    return GameStats_GetCapped(ptr, 0);
}

THUMB_FUNC void GameStats_IncSpeciesCaught(struct GameStats * ptr, struct Pokedex * pokedex, u16 species)
{
    if (!Pokedex_CheckMonCaughtFlag(pokedex, species))
    {
        GameStats_AddSpecial(ptr, 22);
    }
}
