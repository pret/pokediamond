#include "global.h"
#include "constants/items.h"
#include "constants/seal_constants.h"
#include "constants/decorations.h"
#include "scrcmd.h"
#include "module_06.h"

extern void FUN_02038AD0(struct TaskManager *);

static const u16 UNK_020F40A6[] = {
    ITEM_AIR_MAIL,
    ITEM_HEAL_BALL,
    0xFFFF
};

static const u16 UNK_020F40A0[] = {
    ITEM_STEEL_MAIL,
    ITEM_LUXURY_BALL,
    0xFFFF
};

static const u16 UNK_020F40B4[] = {
    ITEM_TUNNEL_MAIL,
    ITEM_HEAL_BALL,
    ITEM_NET_BALL,
    0xFFFF
};

static const u16 UNK_020F40AC[] = {
    ITEM_BLOOM_MAIL,
    ITEM_HEAL_BALL,
    ITEM_NET_BALL,
    0xFFFF
};

static const u16 UNK_020F40BC[] = {
    ITEM_AIR_MAIL,
    ITEM_HEAL_BALL,
    ITEM_NET_BALL,
    ITEM_NEST_BALL,
    0xFFFF
};

static const u16 UNK_020F40F8[] = {
    ITEM_HEART_MAIL,
    ITEM_HEAL_BALL,
    ITEM_NET_BALL,
    ITEM_NEST_BALL,
    0xFFFF
};

static const u16 UNK_020F4102[] = {
    ITEM_AIR_MAIL,
    ITEM_QUICK_BALL,
    ITEM_TIMER_BALL,
    ITEM_REPEAT_BALL,
    0xFFFF
};

static const u16 UNK_020F40DA[] = {
    ITEM_AIR_MAIL,
    ITEM_NET_BALL,
    ITEM_NEST_BALL,
    ITEM_DUSK_BALL,
    0xFFFF
};

static const u16 UNK_020F40EE[] = {
    ITEM_AIR_MAIL,
    ITEM_DUSK_BALL,
    ITEM_QUICK_BALL,
    ITEM_TIMER_BALL,
    0xFFFF
};

static const u16 UNK_020F40D0[] = {
    ITEM_SNOW_MAIL,
    ITEM_DUSK_BALL,
    ITEM_QUICK_BALL,
    ITEM_TIMER_BALL,
    0xFFFF
};

static const u16 UNK_020F40C6[] = {
    ITEM_HEAL_POWDER,
    ITEM_ENERGYPOWDER,
    ITEM_ENERGY_ROOT,
    ITEM_REVIVAL_HERB,
    0xFFFF
};

static const u16 UNK_020F40E4[] = {
    ITEM_AIR_MAIL,
    ITEM_NEST_BALL,
    ITEM_DUSK_BALL,
    ITEM_QUICK_BALL,
    0xFFFF
};

static const u16 UNK_020F410C[] = {
    DECORATION_YELLOW_CUSHION,
    DECORATION_CUPBOARD,
    DECORATION_TV,
    DECORATION_REFRIGERATOR,
    DECORATION_PRETTY_SINK,
    0xFFFF
};

static const u16 UNK_020F4118[] = {
    DECORATION_MUNCHLAX_DOLL,
    DECORATION_BONSLY_DOLL,
    DECORATION_MIME_JR__DOLL,
    DECORATION_MANTYKE_DOLL,
    DECORATION_BUIZEL_DOLL,
    DECORATION_CHATOT_DOLL,
    0xFFFF
};

static const u16 UNK_020F4126[] = {
    ITEM_PROTEIN,
    ITEM_IRON,
    ITEM_CALCIUM,
    ITEM_ZINC,
    ITEM_CARBOS,
    ITEM_HP_UP,
    0xFFFF
};

static const u16 UNK_020F4134[] = {
    ITEM_TM38,
    ITEM_TM25,
    ITEM_TM14,
    ITEM_TM22,
    ITEM_TM52,
    ITEM_TM15,
    0xFFFF
};

static const u16 UNK_020F41B2[] = {
    SEAL_STAR_A,
    SEAL_A,
    SEAL_FIRE_A,
    SEAL_SONG_A,
    SEAL_LINE_B,
    SEAL_ELE_B,
    SEAL_PARTY_D,
    0xFFFF
};

static const u16 UNK_020F4142[] = {
    SEAL_HEART_B,
    SEAL_STAR_C,
    SEAL_FIRE_C,
    SEAL_FLORA_B,
    SEAL_SONG_C,
    SEAL_SMOKE_A,
    SEAL_ELE_D,
    0xFFFF
};

static const u16 UNK_020F4152[] = {
    SEAL_FOAMY_D,
    SEAL_PARTY_C,
    SEAL_FLORA_F,
    SEAL_SONG_G,
    SEAL_HEART_F,
    SEAL_LINE_A,
    SEAL_ELE_A,
    0xFFFF
};

static const u16 UNK_020F4162[] = {
    SEAL_HEART_C,
    SEAL_STAR_D,
    SEAL_FIRE_D,
    SEAL_FLORA_C,
    SEAL_SONG_D,
    SEAL_SMOKE_B,
    SEAL_FOAMY_A,
    0xFFFF
};

static const u16 UNK_020F4172[] = {
    SEAL_HEART_D,
    SEAL_FOAMY_B,
    SEAL_PARTY_A,
    SEAL_FLORA_D,
    SEAL_SONG_E,
    SEAL_STAR_E,
    SEAL_SMOKE_C,
    0xFFFF
};

static const u16 UNK_020F4182[] = {
    ITEM_TM83,
    ITEM_TM17,
    ITEM_TM54,
    ITEM_TM20,
    ITEM_TM33,
    ITEM_TM16,
    ITEM_TM70,
    0xFFFF
};

static const u16 UNK_020F4192[] = {
    SEAL_HEART_A,
    SEAL_STAR_B,
    SEAL_FIRE_B,
    SEAL_SONG_B,
    SEAL_LINE_C,
    SEAL_ELE_C,
    SEAL_FLORA_A,
    0xFFFF
};

static const u16 UNK_020F41A2[] = {
    SEAL_FOAMY_C,
    SEAL_PARTY_B,
    SEAL_FLORA_E,
    SEAL_SONG_F,
    SEAL_HEART_E,
    SEAL_STAR_F,
    SEAL_SMOKE_D,
    0xFFFF
};

static const u16 UNK_020F41D4[] = {
    ITEM_X_SPEED,
    ITEM_X_ATTACK,
    ITEM_X_DEFENSE,
    ITEM_GUARD_SPEC_,
    ITEM_DIRE_HIT,
    ITEM_X_ACCURACY,
    ITEM_X_SPECIAL,
    ITEM_X_SP__DEF,
    0xFFFF
};

static const u16 UNK_020F41C2[] = {
    ITEM_HEAL_BALL,
    ITEM_NET_BALL,
    ITEM_NEST_BALL,
    ITEM_DUSK_BALL,
    ITEM_QUICK_BALL,
    ITEM_TIMER_BALL,
    ITEM_REPEAT_BALL,
    ITEM_LUXURY_BALL,
    0xFFFF
};

static const u16 UNK_020F41E6[] = {
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_MAX_POTION,
    ITEM_REVIVE,
    ITEM_ANTIDOTE,
    ITEM_PARLYZ_HEAL,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_FULL_HEAL,
    0xFFFF
};

static const u16 UNK_020F41FE[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_ESCAPE_ROPE,
    ITEM_POKE_DOLL,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_MAX_REPEL,
    ITEM_GRASS_MAIL,
    ITEM_FLAME_MAIL,
    ITEM_BUBBLE_MAIL,
    ITEM_SPACE_MAIL,
    0xFFFF
};

static const u16 sNormalMartBadgeThresholds[][2] = {
    // Balls
    {ITEM_POKE_BALL,    1},
    {ITEM_GREAT_BALL,   3},
    {ITEM_ULTRA_BALL,   4},
    // Potions
    {ITEM_POTION,       1},
    {ITEM_SUPER_POTION, 2},
    {ITEM_HYPER_POTION, 4},
    {ITEM_MAX_POTION,   5},
    {ITEM_FULL_RESTORE, 6},
    // Revives
    {ITEM_REVIVE,       3},
    // Status heal
    {ITEM_ANTIDOTE,     1},
    {ITEM_PARLYZ_HEAL,  1},
    {ITEM_AWAKENING,    2},
    {ITEM_BURN_HEAL,    2},
    {ITEM_ICE_HEAL,     2},
    {ITEM_FULL_HEAL,    4},
    // Dungeon items
    {ITEM_ESCAPE_ROPE,  2},
    // Repels
    {ITEM_REPEL,        2},
    {ITEM_SUPER_REPEL,  3},
    {ITEM_MAX_REPEL,    4},
};

const u16 *sDecorationMartPointers[] = {
    UNK_020F410C,
    UNK_020F4118,
};

const u16 *sSpecialMartPointers[] = {
    UNK_020F40A6,
    UNK_020F40B4,
    UNK_020F40AC,
    UNK_020F40BC,
    UNK_020F40C6,
    UNK_020F40F8,
    UNK_020F40DA,
    UNK_020F40E4,
    UNK_020F41E6,
    UNK_020F41FE,
    UNK_020F41D4,
    UNK_020F4126,
    UNK_020F4182,
    UNK_020F4134,
    UNK_020F40EE,
    UNK_020F40D0,
    UNK_020F4102,
    UNK_020F40A0,
    UNK_020F41C2,
};

const u16 *sSealsMartPointers[] = {
    UNK_020F4192,
    UNK_020F4142,
    UNK_020F4162,
    UNK_020F4172,
    UNK_020F41A2,
    UNK_020F4152,
    UNK_020F41B2,
};

THUMB_FUNC BOOL ScrCmd_NormalMart(struct ScriptContext * ctx) //0147 - todo: Pokemart?
{
    u16 whichMart = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    s32 param;
    u16 martItems[64];
    u8 martIdx = 0;
    u8 badgeCount = 0;
    u8 i;

    for (i = 0; i < 8; i++)
    {
        if (PlayerProfile_TestBadgeFlag(Sav2_PlayerData_GetProfileAddr(ctx->fieldSystem->saveBlock2), i) == TRUE)
            badgeCount++;
    }
    switch (badgeCount)
    {
        case 0:
            param = 1;
            break;
        case 1:
        case 2:
            param = 2;
            break;
        case 3:
        case 4:
            param = 3;
            break;
        case 5:
        case 6:
            param = 4;
            break;
        case 7:
            param = 5;
            break;
        case 8:
            param = 6;
            break;
        default:
            param = 1;
            break;
    }
    for (i = 0; i < NELEMS(sNormalMartBadgeThresholds); i++)
    {
        if (param >= sNormalMartBadgeThresholds[i][1])
        {
            martItems[martIdx] = sNormalMartBadgeThresholds[i][0];
            martIdx++;
        }
    }
    martItems[martIdx] = 0xFFFF; // terminator
    MOD06_0223D3D0(ctx->taskManager, ctx->fieldSystem, martItems, MART_ITEMS, 0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_SpecialMart(struct ScriptContext * ctx) //0148
{
    u16 whichMart = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u32 sp0;

    // Fakematch?
    if ((u16)(whichMart + (u16)(-8u)) <= 5)
        sp0 = 1;
    else
        sp0 = 0;

    MOD06_0223D3D0(ctx->taskManager, ctx->fieldSystem, sSpecialMartPointers[whichMart], MART_ITEMS, sp0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_GoodsMart(struct ScriptContext * ctx) //0149
{
    u16 whichMart = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u32 sp0;

    if (whichMart <= 1)
        sp0 = 1;
    else
        sp0 = 0;

    MOD06_0223D3D0(ctx->taskManager, ctx->fieldSystem, sDecorationMartPointers[whichMart], MART_DECORATIONS, sp0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_SealsMart(struct ScriptContext * ctx) //014A
{
    u16 whichMart = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));

    MOD06_0223D3D0(ctx->taskManager, ctx->fieldSystem, sSealsMartPointers[whichMart], MART_SEALS, 0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_AccessoriesShop(struct ScriptContext * ctx) //0257 - todo: Unsure if this is correct, SDSME has it as SprtSave?
{
    FUN_02038AD0(ctx->fieldSystem->taskManager);
    return TRUE;
}
