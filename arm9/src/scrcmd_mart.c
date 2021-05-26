#include "global.h"
#include "constants/items.h"
#include "scrcmd.h"
#include "module_06.h"

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
    ITEM_DIVE_BALL,
    ITEM_PARLYZ_HEAL,
    ITEM_HYPER_POTION,
    ITEM_SUPER_POTION,
    ITEM_FULL_HEAL,
    0xFFFF
};

static const u16 UNK_020F4118[] = {
    115,
    116,
    117,
    119,
    120,
    121,
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
    ITEM_DIVE_BALL,
    ITEM_CALCIUM,
    ITEM_REVIVE,
    ITEM_LAVA_COOKIE,
    ITEM_HEAL_BALL,
    ITEM_AWAKENING,
    ITEM_ENERGY_ROOT,
    0xFFFF
};

static const u16 UNK_020F4142[] = {
    ITEM_ULTRA_BALL,
    ITEM_REPEAT_BALL,
    ITEM_FRESH_WATER,
    ITEM_REVIVAL_HERB,
    ITEM_SACRED_ASH,
    ITEM_CHERISH_BALL,
    ITEM_FULL_RESTORE,
    0xFFFF
};

static const u16 UNK_020F4152[] = {
    ITEM_FULL_HEAL,
    ITEM_ENERGYPOWDER,
    ITEM_MAX_ELIXIR,
    ITEM_CARBOS,
    ITEM_NET_BALL,
    ITEM_DUSK_BALL,
    ITEM_ICE_HEAL,
    0xFFFF
};

static const u16 UNK_020F4162[] = {
    ITEM_GREAT_BALL,
    ITEM_TIMER_BALL,
    ITEM_SODA_POP,
    ITEM_ETHER,
    ITEM_HP_UP,
    ITEM_POTION,
    ITEM_MAX_POTION,
    0xFFFF
};

static const u16 UNK_020F4172[] = {
    ITEM_POKE_BALL,
    ITEM_HYPER_POTION,
    ITEM_LEMONADE,
    ITEM_MAX_ETHER,
    ITEM_PROTEIN,
    ITEM_LUXURY_BALL,
    ITEM_ANTIDOTE,
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
    ITEM_MASTER_BALL,
    ITEM_NEST_BALL,
    ITEM_MAX_REVIVE,
    ITEM_BERRY_JUICE,
    ITEM_QUICK_BALL,
    ITEM_PARLYZ_HEAL,
    ITEM_HEAL_POWDER,
    0xFFFF
};

static const u16 UNK_020F41A2[] = {
    ITEM_SUPER_POTION,
    ITEM_MOOMOO_MILK,
    ITEM_ELIXIR,
    ITEM_IRON,
    ITEM_SAFARI_BALL,
    ITEM_PREMIER_BALL,
    ITEM_BURN_HEAL,
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

static const u16 UNK_020F4218[][2] = {
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

const u16 *UNK_02105DEC[] = {
    UNK_020F410C,
    UNK_020F4118,
};

const u16 *UNK_02105DF4[] = {
    UNK_020F4192,
    UNK_020F4142,
    UNK_020F4162,
    UNK_020F4172,
    UNK_020F41A2,
    UNK_020F4152,
    UNK_020F41B2,
};

const u16 *UNK_02105E10[] = {
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

THUMB_FUNC BOOL FUN_0203FCF4(struct ScriptContext * ctx)
{
    u16 whichMart = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    s32 param;
    u16 martItems[64];
    u8 martIdx = 0;
    u8 badgeCount = 0;
    u8 i;

    for (i = 0; i < 8; i++)
    {
        if (PlayerProfile_TestBadgeFlag(Sav2_PlayerData_GetProfileAddr(ctx->unk80->saveBlock2), i) == TRUE)
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
    for (i = 0; i < NELEMS(UNK_020F4218); i++)
    {
        if (param >= UNK_020F4218[i][1])
        {
            martItems[martIdx] = UNK_020F4218[i][0];
            martIdx++;
        }
    }
    martItems[martIdx] = 0xFFFF; // terminator
    MOD06_0223D3D0(ctx->unk74, ctx->unk80, martItems, 0, 0);
    return TRUE;
}
