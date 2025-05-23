#include "global.h"

#include "pokedex.h"
#include "save_vars_flags.h"
#include "scrcmd.h"

extern PlayerSaveData *sub_02034E20(LocalFieldData *localFieldData);
extern LocalFieldData *Save_LocalFieldData_Get(SaveData *save);
extern void sub_0205ECD4(struct SaveVarsFlags *state);
extern BOOL sub_0205ECE0(struct SaveVarsFlags *state);
extern void sub_0205ECFC(struct SaveVarsFlags *state);
extern BOOL sub_0205ED0C(struct SaveVarsFlags *state);
extern void sub_0205ED1C(struct SaveVarsFlags *state);
extern void sub_0205ED2C(struct SaveVarsFlags *state);
extern BOOL Save_VarsFlags_CheckHaveFollower(struct SaveVarsFlags *state);
extern void sub_0205ED4C(struct SaveVarsFlags *state);
extern void sub_0205ED5C(struct SaveVarsFlags *state);
extern BOOL sub_0205ED6C(struct SaveVarsFlags *state);
extern BOOL sub_0205F264(struct SaveVarsFlags *state, u32);
extern void sub_0205F274(struct SaveVarsFlags *state);
extern void sub_0205F284(struct SaveVarsFlags *state);
extern BOOL sub_0205F294(struct SaveVarsFlags *state);
extern void sub_0205F2A4(struct SaveVarsFlags *state);
extern void sub_0205F2B4(struct SaveVarsFlags *state);
extern BOOL sub_0205F2C4(struct SaveVarsFlags *state);

const u8 UNK_020F457F[8] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
};

BOOL ScrCmd_HasSinnohDex(struct ScriptContext *ctx) // 0157
{
    struct Pokedex *pokedex = Save_Pokedex_Get(ctx->fieldSystem->saveData);
    u16 *ret_ptr = ScriptGetVarPointer(ctx);

    *ret_ptr = (u16)Pokedex_GetSinnohDexFlag(pokedex);

    return FALSE;
}

BOOL ScrCmd_GiveSinnohDex(struct ScriptContext *ctx) // 0158
{
    struct Pokedex *pokedex = Save_Pokedex_Get(ctx->fieldSystem->saveData);

    Pokedex_SetSinnohDexFlag(pokedex);

    return FALSE;
}

BOOL ScrCmd_HasRunningShoes(struct ScriptContext *ctx) // 0159
{
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    LocalFieldData *localFieldData = Save_LocalFieldData_Get(ctx->fieldSystem->saveData);
    PlayerSaveData *playerSaveData = sub_02034E20(localFieldData);

    *ret_ptr = (u16)PlayerSaveData_CheckRunningShoes(playerSaveData);

    return FALSE;
}

BOOL ScrCmd_GiveRunningShoes(struct ScriptContext *ctx) // 015A
{
    LocalFieldData *localFieldData = Save_LocalFieldData_Get(ctx->fieldSystem->saveData);
    PlayerSaveData *playerSaveData = sub_02034E20(localFieldData);

    PlayerSaveData_SetRunningShoesFlag(playerSaveData, TRUE);

    return FALSE;
}

BOOL ScrCmd_HasBadge(struct ScriptContext *ctx) // 015B
{
    u16 badge_no = ScriptGetVar(ctx);
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    GF_ASSERT(badge_no < 8);
    PlayerProfile *player = Save_PlayerData_GetProfile(ctx->fieldSystem->saveData);

    *ret_ptr = (u16)PlayerProfile_TestBadgeFlag(player, badge_no);

    return FALSE;
}

BOOL ScrCmd_GiveBadge(struct ScriptContext *ctx) // 015C
{
    u16 badge_no = ScriptGetVar(ctx);
    GF_ASSERT(badge_no < 8);
    PlayerProfile *player = Save_PlayerData_GetProfile(ctx->fieldSystem->saveData);

    PlayerProfile_SetBadgeFlag(player, badge_no);

    return FALSE;
}

BOOL ScrCmd_HasBag(struct ScriptContext *ctx) // 015E
{
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);

    *ret_ptr = (u16)sub_0205ECE0(state);

    return FALSE;
}

BOOL ScrCmd_GetTotalEarnedBadges(struct ScriptContext *ctx) // 015D - todo: CountBadges?
{
    u16 *ret_ptr = ScriptGetVarPointer(ctx);

    u16 i;
    u16 badges;
    for (i = 0, badges = 0; i < 8; i++) {
        PlayerProfile *player = Save_PlayerData_GetProfile(ctx->fieldSystem->saveData);
        BOOL has_badge = PlayerProfile_TestBadgeFlag(player, UNK_020F457F[i]);
        if (has_badge == TRUE) {
            badges++;
        }
    }

    *ret_ptr = badges;
    return FALSE;
}

BOOL ScrCmd_GiveBag(struct ScriptContext *ctx) // 015F
{
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);

    sub_0205ECD4(state);

    return FALSE;
}

BOOL ScrCmd_Unk0160(struct ScriptContext *ctx) // 0160 - todo: HasPartner? CheckPartner?
{
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);

    *ret_ptr = (u16)Save_VarsFlags_CheckHaveFollower(state);

    return FALSE;
}

BOOL ScrCmd_Unk0161(struct ScriptContext *ctx) // 0161 - todo: GivePartner? SetPartner?
{
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);

    sub_0205ED1C(state);

    return FALSE;
}

BOOL ScrCmd_Unk0162(struct ScriptContext *ctx) // 0162 - todo: RemovePartner? ClearPartner?
{
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);

    sub_0205ED2C(state);

    return FALSE;
}

BOOL ScrCmd_Unk0163(struct ScriptContext *ctx) // 0163 - todo: GetSteps? CheckSteps? GetStepFlag? CheckStepFlag?
{
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);

    *ret_ptr = (u16)sub_0205ED6C(state);

    return FALSE;
}

BOOL ScrCmd_Unk0164(struct ScriptContext *ctx) // 0164 - todo: SetStepFlag?
{
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);

    sub_0205ED4C(state);

    return 0;
}

BOOL ScrCmd_Unk0165(struct ScriptContext *ctx) // 0165 - todo: ClearStepFlag?
{
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);

    sub_0205ED5C(state);

    return 0;
}

BOOL ScrCmd_CheckGameCompleted(struct ScriptContext *ctx) // 0166
{
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);

    *ret_ptr = (u16)sub_0205ED0C(state);

    return FALSE;
}

BOOL ScrCmd_SetGameCompleted(struct ScriptContext *ctx) // 0167
{
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);

    sub_0205ECFC(state);

    return 0;
}

BOOL ScrCmd_GetSetStrength(struct ScriptContext *ctx) // 01CF - todo: Strength?
{
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);
    u8 option = ScriptReadByte(ctx);
    u16 *ret_ptr;

    switch (option) {
    case 1: // set strength to on
        sub_0205F264(state, 1);
        break;
    case 0: // set strength to off
        sub_0205F264(state, 0);
        break;
    case 2: // get whether strength is on or off
        ret_ptr = ScriptGetVarPointer(ctx);
        *ret_ptr = (u16)sub_0205F264(state, 2);
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return FALSE;
}

BOOL ScrCmd_GetSetFlash(struct ScriptContext *ctx) // 01D0 - todo Flash?
{
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);
    u8 option = ScriptReadByte(ctx);
    u16 *ret_ptr;

    switch (option) {
    case 1: // set flash to on
        sub_0205F274(state);
        break;
    case 0: // set flash to off
        sub_0205F284(state);
        break;
    case 2: // get whether flash is on or off
        ret_ptr = ScriptGetVarPointer(ctx);
        *ret_ptr = (u16)sub_0205F294(state);
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return FALSE;
}

BOOL ScrCmd_GetSetDefog(struct ScriptContext *ctx) // 01D1 - todo: Defog
{
    struct SaveVarsFlags *state = Save_VarsFlags_Get(ctx->fieldSystem->saveData);
    u8 option = ScriptReadByte(ctx);
    u16 *ret_ptr;

    switch (option) {
    case 1: // set defog to on
        sub_0205F2A4(state);
        break;
    case 0: // set defog to off
        sub_0205F2B4(state);
        break;
    case 2: // get whether defog is on or off
        ret_ptr = ScriptGetVarPointer(ctx);
        *ret_ptr = (u16)sub_0205F2C4(state);
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return FALSE;
}
