#include "global.h"
#include "script.h"
#include "party.h"
#include "save_block_2.h"
#include "unk_0204639C.h"
#include "map_header.h"

extern u16 VarGet(struct UnkStruct_0204639C* arg, u16 wk);
extern u16 *GetVarPointer(struct UnkStruct_0204639C* arg, u16);
extern BOOL GiveMon(u32 heap_id, struct SaveBlock2 * sav2, u16 species, u8 level, u16 item, u32 mapSec, u8 encounterType);

THUMB_FUNC BOOL ScrCmd_givemon(struct ScriptContext* ctx)
{
    u32 mapSec = FUN_02034824(*(ctx->unk80->unk1C));
    struct UnkStruct_0204639C *savePtr = ctx->unk80;
    u16 species = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 level = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 item = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 * varPtr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    struct PlayerParty * party = SavArray_PlayerParty_get((struct SaveBlock2 *) savePtr->unkC);
    *varPtr = GiveMon(11, (struct SaveBlock2 *) savePtr->unkC, species, level, item, mapSec, 12);
    return FALSE;
}