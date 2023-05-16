#include "scrcmd.h"
#include "message_format.h"
#include "math_util.h"
#include "unk_020286F8.h"

extern void* FieldSysGetAttrAddr(struct FieldSystem*, u8 idx);

extern void FUN_020385CC(struct TaskManager *, u32, u32, u32, u32, u16*, u16* ret_ptr);
extern BOOL FUN_020612EC(struct FieldSystem*);
extern BOOL FUN_020612F8(struct FieldSystem*);

THUMB_FUNC BOOL ScrCmd_UnionGroup(struct ScriptContext* ctx) //021D
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    struct UnkSaveStruct_020286F8* unk_sav_ptr = FUN_0202881C(ctx->fieldSystem->saveBlock2);
    struct SaveBlock2* sav2 = ctx->fieldSystem->saveBlock2;

    u16 option = ScriptReadHalfword(ctx);
    switch (option)
    {
    case 0: { //check if group ID exists
        u16 unk_var = ScriptGetVar(ctx);
        u16* ret_ptr = ScriptGetVarPointer(ctx);

        *ret_ptr = (u16)FUN_02028828(unk_sav_ptr, unk_var);
        return FALSE;
    }
    case 1: { //check if group ID is accessible
        u16 unk_var = ScriptGetVar(ctx);
        u16* ret_ptr = ScriptGetVarPointer(ctx);

        *ret_ptr = (u16)FUN_02028840(unk_sav_ptr, unk_var);
        return FALSE;
    }
    case 2: { //writes group ID to string buffer
        u16 unk_var = ScriptGetVar(ctx);
        u16 idx = ScriptGetVar(ctx);

        BufferEasyChatWord(*messageFormat, sav2, unk_var, idx, 0);
        break;
    }
    case 3: { //writes group leader name to string buffer
        u16 unk_var = ScriptGetVar(ctx);
        u16 idx = ScriptGetVar(ctx);

        BufferEasyChatWord(*messageFormat, sav2, unk_var, idx, 1);
        break;
    }
    case 4: { //opens keyboard, 2 if group id exists, 1 if cancel, 0 otherwise
        u16* unk_str_ptr = FUN_020287A8(unk_sav_ptr, 0, 0);
        u16* ret_ptr = ScriptGetVarPointer(ctx);

        FUN_020385CC(ctx->taskManager, 5, 0, 7, 0, unk_str_ptr, ret_ptr);
        return TRUE;
    }
    case 5: { //enter in group id (whatever this means, needs more investigation)
        u16 src_idx = ScriptGetVar(ctx);
        BOOL unk_bool = FUN_02028828(unk_sav_ptr, 1);

        FUN_02028700(unk_sav_ptr, src_idx, 1);
        if (unk_bool != FALSE)
        {
            FUN_020612F8(ctx->fieldSystem);
        }

        return FALSE;
    }
    case 6: { //create a group
        struct String* player_name = String_ctor(64, 32);
        struct PlayerData* player = Sav2_PlayerData_GetProfileAddr(ctx->fieldSystem->saveBlock2);

        PlayerName_FlatToString(player, player_name);
        FUN_020287C0(unk_sav_ptr, 0, 1, player_name);
        FUN_020287EC(unk_sav_ptr, 0, PlayerProfile_GetTrainerGender(player));
        FUN_02028810(unk_sav_ptr, 0, 2);
        FUN_02028788(unk_sav_ptr, 0, MTRandom());

        String_dtor(player_name);

        FUN_02028700(unk_sav_ptr, 0, 1);
        FUN_020612EC(ctx->fieldSystem);

        break;
    }
    }

    return FALSE;
}
