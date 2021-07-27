#include "scrcmd.h"
#include "constants/accessories.h"
#include "constants/pokemon.h"
#include "event_data.h"

extern void FUN_0205F54C(struct ScriptState* state);
extern u16 FUN_0205F55C(struct ScriptState* state);

static const u16 sAmitySquarePossibleAccessoriesByPokemon[6][10] = {
    { // Clefairy and Skitty
        ACCESSORY_WHITE_FLUFF,
        ACCESSORY_ORANGE_FLUFF,
        ACCESSORY_WHITE_FEATHER,
        ACCESSORY_MINI_PEBBLE,
        ACCESSORY_SMALL_LEAF,
        ACCESSORY_BLUE_SCALE,

        ACCESSORY_WHITE_BEARD,
        ACCESSORY_THIN_MUSHROOM,
        ACCESSORY_BIG_SCALE,

        ACCESSORY_STUMP
    },

    { // Torchic and Drifloon
        ACCESSORY_PINK_FLUFF,
        ACCESSORY_RED_FEATHER,
        ACCESSORY_YELLOW_FEATHER,
        ACCESSORY_BLACK_BEARD,
        ACCESSORY_NARROW_SCALE,
        ACCESSORY_WHITE_FLUFF,

        ACCESSORY_WHITE_MOUSTACHE,
        ACCESSORY_SHED_CLAW,
        ACCESSORY_NARROW_LEAF,

        ACCESSORY_PURPLE_SCALE
    },

    { // Psyduck and Pachirisu
        ACCESSORY_SNAGGY_PEBBLE,
        ACCESSORY_JAGGED_BOULDER,
        ACCESSORY_BROWN_FLUFF,
        ACCESSORY_MINI_PEBBLE,
        ACCESSORY_BLACK_MOUSTACHE,
        ACCESSORY_SHED_HORN,

        ACCESSORY_NARROW_SCALE,
        ACCESSORY_ROUND_PEBBLE,
        ACCESSORY_GREEN_SCALE,

        ACCESSORY_THICK_MUSHROOM
    },

    { // Jigglypuff and Shroomish
        ACCESSORY_PINK_SCALE,
        ACCESSORY_BLUE_FEATHER,
        ACCESSORY_WHITE_FEATHER,
        ACCESSORY_BLUE_SCALE,
        ACCESSORY_THIN_MUSHROOM,
        ACCESSORY_JAGGED_BOULDER,

        ACCESSORY_WHITE_BEARD,
        ACCESSORY_BLACK_BEARD,
        ACCESSORY_BIG_LEAF,

        ACCESSORY_ROUND_PEBBLE
    },

    { // Pikachu
        ACCESSORY_ORANGE_FLUFF,
        ACCESSORY_BROWN_FLUFF,
        ACCESSORY_SMALL_LEAF,
        ACCESSORY_RED_FEATHER,
        ACCESSORY_YELLOW_FEATHER,
        ACCESSORY_YELLOW_FLUFF,

        ACCESSORY_GLITTER_BOULDER,
        ACCESSORY_BIG_SCALE,
        ACCESSORY_BLACK_MOUSTACHE,

        ACCESSORY_PURPLE_SCALE
    },

    { // Buneary and Happiny
        ACCESSORY_PINK_SCALE,
        ACCESSORY_SHED_HORN,
        ACCESSORY_PINK_FLUFF,
        ACCESSORY_YELLOW_FEATHER,
        ACCESSORY_SHED_CLAW,
        ACCESSORY_BLACK_FLUFF,

        ACCESSORY_SNAGGY_PEBBLE,
        ACCESSORY_BIG_LEAF,
        ACCESSORY_GREEN_SCALE,

        ACCESSORY_BLACK_PEBBLE
    },
};

THUMB_FUNC BOOL ScrCmd_ClearAmitySquareSteps(struct ScriptContext* ctx)
{
    struct ScriptState* state = SavArray_Flags_get(ctx->unk80->saveBlock2);

    FUN_0205F54C(state);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckAmitySquareSteps(struct ScriptContext* ctx)
{
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    struct ScriptState* state = SavArray_Flags_get(ctx->unk80->saveBlock2);

    *ret_ptr = FUN_0205F55C(state);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetAmitySquareAccessory(struct ScriptContext* ctx)
{
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 species = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 rand = (u16)(LCRandom() % 100);

    u32 j;
    if (rand < 15)
    {
        j = 0;
    }
    else if (rand < 30)
    {
        j = 1;
    }
    else if (rand < 45)
    {
        j = 2;
    }
    else if (rand < 60)
    {
        j = 3;
    }
    else if (rand < 70)
    {
        j = 4;
    }
    else if (rand < 80)
    {
        j = 5;
    }
    else if (rand < 88)
    {
        j = 6;
    }
    else if (rand < 93)
    {
        j = 7;
    }
    else if (rand < 98)
    {
        j = 8;
    }
    else
    {
        j = 9;
    }

    u32 i;
    switch (species)
    {
        case SPECIES_CLEFAIRY:
        case SPECIES_SKITTY:
            i = 0;
            break;
        case SPECIES_TORCHIC:
        case SPECIES_DRIFLOON:
            i = 1;
            break;
        case SPECIES_PSYDUCK:
        case SPECIES_PACHIRISU:
            i = 2;
            break;
        case SPECIES_JIGGLYPUFF:
        case SPECIES_SHROOMISH:
            i = 3;
            break;
        case SPECIES_PIKACHU:
            i = 4;
            break;
        case SPECIES_BUNEARY:
        case SPECIES_HAPPINY:
            i = 5;
            break;
        default:
            i = 0;
            break;
    }

    *ret_ptr = sAmitySquarePossibleAccessoriesByPokemon[i][j];
    return FALSE;
}
