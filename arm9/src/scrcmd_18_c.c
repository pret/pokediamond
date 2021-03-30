#include "global.h"
#include "script.h"
#include "party.h"
#include "save_block_2.h"
#include "unk_0204639C.h"
#include "map_header.h"
#include "scrcmd.h"

extern BOOL GiveMon(u32 heap_id, struct SaveBlock2 * sav2, u16 species, u8 level, u16 item, u32 mapSec, u8 encounterType);

THUMB_FUNC BOOL ScrCmd_GiveMon(struct ScriptContext* ctx)
{
    u32 mapSec = MapHeader_GetMapSec(*(ctx->unk80->mapId));
    struct UnkSavStruct80 *savePtr = ctx->unk80;
    u16 species = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 level = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 item = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 * varPtr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    struct PlayerParty * party = SavArray_PlayerParty_get(savePtr->saveBlock2);
    *varPtr = (u16)GiveMon(11, savePtr->saveBlock2, species, (u8)level, item, mapSec, 12);
    return FALSE;
}
