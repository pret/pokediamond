#include "global.h"

#include "blackout.h"
#include "encounter.h"
#include "scrcmd.h"
#include "script_pokemon_util.h"
#include "unk_0205EC84.h"

extern void *FieldSysGetAttrAddr(FieldSystem *fieldSystem, u8 idx);
extern SaveFashionData *Save_FashionData_Get(SaveData *save);
extern void TrainerFieldSystem_FlagSet(FieldSystem *fieldSystem, u16 flag);
extern u8 TrainerFieldSystem_FlagCheck(FieldSystem *fieldSystem, u16 flag);

extern void *sub_0205CA4C(void *event, PlayerAvatar *playerAvatar, void *param3, void *param4, int param5, void *encounterType, u16 param7);
extern int sub_0205CA64(void);
extern void sub_0205CA78(void *param1);
extern u16 sub_020395F4(u16 scriptNumber);
extern int sub_0205F368(SaveVarsFlags *saveVarFlags);
extern BOOL TrainerIsDoubleBattle(u16 param1);
extern BOOL sub_02039618(u16 scriptNumber);
extern BOOL IsBattleResultWin(u32 winFlag);
extern int sub_0204AD0C(u16 param1);
extern void sub_02004724(int param1);
extern int sub_020480C8(int param1);
extern int sub_020480D8(int param1);

BOOL ScrCmd_Unk00B6(ScriptContext *ctx) {
    FieldSystem *field = ctx->fieldSystem;
    void **trainer0;
    void **trainer8;
    void **trainerId;
    void **trainerEncounterType;
    void **trainer4;
    void **trainer18;
    u16 var = ScriptGetVar(ctx);
    void **trainerEvent;

    if (var == 0) {
        trainer0 = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_0_FIELD_00);
        trainer4 = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_0_FIELD_04);
        trainer8 = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_0_FIELD_08);
        trainerId = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_0_ID);
        trainerEncounterType = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_0_ENCOUNTER_TYPE);
        trainerEvent = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_0_EVENT);
        trainer18 = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_0_FIELD_18);
    } else {
        trainer0 = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_1_FIELD_00);
        trainer4 = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_1_FIELD_04);
        trainer8 = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_1_FIELD_08);
        trainerId = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_1_ID);
        trainerEncounterType = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_1_ENCOUNTER_TYPE);
        trainerEvent = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_1_EVENT);
        trainer18 = FieldSysGetAttrAddr(field, SCRIPTENV_ENGAGED_TRAINER_1_FIELD_18);
    }

    *trainer18 = sub_0205CA4C(*trainerEvent, field->playerAvatar, *trainer4, *trainer0, 0, *trainerEncounterType, var);

    return FALSE;
}

BOOL ScrCmd_Unk00B7(ScriptContext *ctx) {
    u16 var1 = ScriptGetVar(ctx);
    u16 *var2 = ScriptGetVarPointer(ctx);
    void **trainer18;

    *var2 = 0;

    trainer18 = var1 == 0 ? FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_ENGAGED_TRAINER_0_FIELD_18) : FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_ENGAGED_TRAINER_1_FIELD_18);

    if (*trainer18 == NULL) {
        *var2 = 1;

        return TRUE;
    } else if (sub_0205CA64() == 1) {
        sub_0205CA78(*trainer18);
        *trainer18 = NULL;
        *var2 = 1;
    }

    return TRUE;
}

BOOL ScrCmd_Unk00B8(ScriptContext *ctx) {
    u16 *trainerEncounterType = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_ENGAGED_TRAINER_0_ENCOUNTER_TYPE);
    u16 *encounterTypePtr = ScriptGetVarPointer(ctx);

    *encounterTypePtr = *trainerEncounterType;

    return FALSE;
}

BOOL ScrCmd_Unk00B9(ScriptContext *ctx) {
    u16 *trainer0Id = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_ENGAGED_TRAINER_0_ID);
    u16 *trainer1Id = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_ENGAGED_TRAINER_1_ID);
    u16 var1 = ScriptGetVar(ctx);
    u16 *trainerId = ScriptGetVarPointer(ctx);
    u16 id = var1 == 0 ? *trainer0Id : *trainer1Id;

    *trainerId = id;

    return FALSE;
}

BOOL ScrCmd_Unk00E4(ScriptContext *ctx) {
    u16 *scriptNumber = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_ACTIVE_SCRIPT_NUMBER);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_020395F4(*scriptNumber);

    return FALSE;
}

BOOL ScrCmd_Unk00E5(ScriptContext *ctx) {
    FieldSystem *field = ctx->fieldSystem;
    u16 *scriptNumber = FieldSysGetAttrAddr(field, SCRIPTENV_ACTIVE_SCRIPT_NUMBER);
    u32 *winFlag = FieldSysGetAttrAddr(field, SCRIPTENV_BATTLE_WIN_FLAG);
    u16 opponentTrainer1 = ScriptGetVar(ctx);
    u16 opponentTrainer2 = ScriptGetVar(ctx);
    u32 followerTrainerNum = 0;

    if (Save_VarsFlags_CheckHaveFollower(Save_VarsFlags_Get(ctx->fieldSystem->saveData)) == TRUE) {
        followerTrainerNum = sub_0205F368(Save_VarsFlags_Get(field->saveData));
    }

    SetupAndStartTrainerBattle(ctx->taskManager, opponentTrainer1, opponentTrainer2, followerTrainerNum, HEAP_ID_FIELD, winFlag);

    return TRUE;
}

BOOL ScrCmd_Unk02A0(ScriptContext *ctx) {
    FieldSystem *field = ctx->fieldSystem;
    u32 *winFlag = FieldSysGetAttrAddr(field, SCRIPTENV_BATTLE_WIN_FLAG);
    u16 followerTrainerNum = ScriptGetVar(ctx);
    u16 opponentTrainer1 = ScriptGetVar(ctx);
    u16 opponentTrainer2 = ScriptGetVar(ctx);

    SetupAndStartTrainerBattle(ctx->taskManager, opponentTrainer1, opponentTrainer2, followerTrainerNum, HEAP_ID_FIELD, winFlag);

    return TRUE;
}

BOOL ScrCmd_Unk00E7(ScriptContext *ctx) {
    FieldSystem *field = ctx->fieldSystem;
    u16 *scriptNumber = FieldSysGetAttrAddr(field, SCRIPTENV_ACTIVE_SCRIPT_NUMBER);
    u16 *var1 = ScriptGetVarPointer(ctx);
    u16 *var2 = ScriptGetVarPointer(ctx);
    u16 *var3 = ScriptGetVarPointer(ctx);
    int var4;
    int var5;
    int var6;

    if ((u16)TrainerIsDoubleBattle(sub_020395F4(*scriptNumber)) == FALSE) {
        var4 = 0;
        var5 = 2;
        var6 = 0;
    } else if ((u16)sub_02039618(*scriptNumber) == FALSE) {
        var4 = 3;
        var5 = 5;
        var6 = 6;
    } else {
        var4 = 7;
        var5 = 9;
        var6 = 10;
    }

    *var1 = var4;
    *var2 = var5;
    *var3 = var6;

    return FALSE;
}

BOOL ScrCmd_Unk00E8(ScriptContext *ctx) {
    FieldSystem *field = ctx->fieldSystem;
    u16 *scriptNumber = FieldSysGetAttrAddr(field, SCRIPTENV_ACTIVE_SCRIPT_NUMBER);
    u16 *var1 = ScriptGetVarPointer(ctx);
    u16 *var2 = ScriptGetVarPointer(ctx);
    u16 *var3 = ScriptGetVarPointer(ctx);
    int var4;
    int var5;
    int var6;

    if ((u16)TrainerIsDoubleBattle(sub_020395F4(*scriptNumber)) == FALSE) {
        var4 = 17;
        var5 = 0;
        var6 = 0;
    } else if ((u16)sub_02039618(*scriptNumber) == FALSE) {
        var4 = 18;
        var5 = 0;
        var6 = 6;
    } else {
        var4 = 19;
        var5 = 0;
        var6 = 10;
    }

    *var1 = var4;
    *var2 = var5;
    *var3 = var6;

    return FALSE;
}

BOOL ScrCmd_Unk00E9(ScriptContext *ctx) {
    FieldSystem *field = ctx->fieldSystem;
    u16 *scriptNumber = FieldSysGetAttrAddr(field, SCRIPTENV_ACTIVE_SCRIPT_NUMBER);
    u16 *var1 = ScriptGetVarPointer(ctx);

    *var1 = TrainerIsDoubleBattle(sub_020395F4(*scriptNumber));

    return FALSE;
}

BOOL ScrCmd_Unk00EA(ScriptContext *ctx) {
    sub_02004724(sub_0204AD0C(ScriptGetVar(ctx)));

    return TRUE;
}

BOOL ScrCmd_Unk00EB(ScriptContext *ctx) {
    CallTask_Blackout(ctx->taskManager);

    return TRUE;
}

BOOL ScrCmd_Unk00EC(ScriptContext *ctx) {
    FieldSystem *field = ctx->fieldSystem;
    u32 *winFlag = FieldSysGetAttrAddr(field, SCRIPTENV_BATTLE_WIN_FLAG);
    u16 *var1 = ScriptGetVarPointer(ctx);

    *var1 = IsBattleResultWin(*winFlag);

    return TRUE;
}

BOOL ScrCmd_Unk00ED(ScriptContext *ctx) {
    FieldSystem *field = ctx->fieldSystem;
    u32 *var1 = FieldSysGetAttrAddr(field, SCRIPTENV_BATTLE_WIN_FLAG);
    u16 *var2 = ScriptGetVarPointer(ctx);

    *var2 = sub_020480C8(*var1);

    return TRUE;
}

BOOL ScrCmd_Unk02BC(ScriptContext *ctx) {
    FieldSystem *field = ctx->fieldSystem;
    u32 *var1 = FieldSysGetAttrAddr(field, SCRIPTENV_BATTLE_WIN_FLAG);
    u16 *var2 = ScriptGetVarPointer(ctx);

    *var2 = sub_020480D8(*var1);

    return TRUE;
}

BOOL ScrCmd_Unk00EE(ScriptContext *ctx) {
    FieldSystem *field = ctx->fieldSystem;
    u16 *var2 = ScriptGetVarPointer(ctx);

    *var2 = HasEnoughAlivePokemonForDoubleBattle(SaveArray_Party_Get(ctx->fieldSystem->saveData));

    return FALSE;
}

BOOL ScrCmd_Unk00EF(ScriptContext *ctx) {
    FieldSystem *field = ctx->fieldSystem;
    u32 *winFlag = FieldSysGetAttrAddr(field, SCRIPTENV_BATTLE_WIN_FLAG);

    SetupAndStartTrainerBattle(ctx->taskManager, 1, 0, 0, HEAP_ID_FIELD, winFlag);

    return TRUE;
}

BOOL ScrCmd_Unk00F0(ScriptContext *ctx) {
    LocalMapObject **lastInteracted = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    FieldSystem *field = MapObject_GetFieldSystem(*lastInteracted);

    TrainerFieldSystem_FlagSet(field, MapObject_GetID(*lastInteracted));

    return FALSE;
}

BOOL ScrCmd_Unk00F1(ScriptContext *ctx) {
    LocalMapObject **lastInteracted = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    u32 ptr = ScriptReadWord(ctx);
    FieldSystem *field = MapObject_GetFieldSystem(*lastInteracted);

    if (TrainerFieldSystem_FlagCheck(field, MapObject_GetID(*lastInteracted)) == TRUE) {
        u8 *scriptPtr = (u8 *)ctx->scriptPtr;

        scriptPtr += ptr;

        ScriptJump(ctx, scriptPtr);

        return TRUE;
    }

    return FALSE;
}
