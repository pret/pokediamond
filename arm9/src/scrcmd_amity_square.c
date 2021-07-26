#include "scrcmd.h"
#include "constants/pokemon.h"
#include "event_data.h"

extern void FUN_0205F54C(struct ScriptState* state);
extern u16 FUN_0205F55C(struct ScriptState* state);

static const u16 sAmitySquarePossibleAccessoriesByPokemon[6][10] = {
    // TODO: accessory constants
    { 0, 5, 21, 11, 26, 13, 25, 31, 16, 33 }, // Clefairy and Skitty
    { 2, 19, 20, 24, 17, 0, 23, 29, 28, 15 }, // Torchic and Drifloon
    { 8, 9, 3, 11, 22, 30, 17, 6, 14, 32 },   // Psyduck and Pachirisu
    { 12, 18, 21, 13, 31, 9, 25, 24, 27, 6 }, // Jigglypuff and Shroomish
    { 5, 3, 26, 19, 20, 1, 7, 16, 22, 15 },   // Pikachu
    { 12, 30, 2, 20, 29, 4, 8, 27, 14, 10 },  // Buneary and Happiny
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
