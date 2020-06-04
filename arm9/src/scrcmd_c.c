
#include "function_target.h"
#include "script.h"
#include "types.h"

// External data
extern u8 ConditionLookup[6][3];

// External funcs
extern u16* FUN_020394B8(u32 arg, u16 wk);
extern u16 FUN_020394F0(u32 arg, u16 wk);
extern void* FUN_02039438(u32 arg, u16 id);
extern void* FUN_02038EB0(u32 arg, u16 id);
extern u8 FUN_02058448(u32 arg);
extern u32 FUN_02046534(u32 arg);
extern void FUN_0203953C(u32 arg, u16 flag);
extern void FUN_02039550(u32 arg, u16 flag);
extern BOOL FUN_02039528(u32 arg, u16 flag);
extern void FUN_0203965C(u32 arg, u16 wk);
extern void FUN_02039678(u32 arg, u16 wk);
extern BOOL FUN_02039640(u32 arg, u16 wk);
extern void MOD05_021E2C24(struct ScriptContext* ctx, u32 arg, u16 id);
extern void MOD05_021E2BD0(struct ScriptContext* ctx, u32 arg, u16 id, u8 unk1, u32 unk2);
extern void MOD05_021E2C58(struct ScriptContext* ctx, u16 typ, u16 id, u16 word1, s16 word2, u8 unk);
extern u32 FUN_0200A86C(u32 a, u32 b, u32 id, u32 d);
extern void FUN_0200A8B8(u32 arg);
extern BOOL FUN_020546C8(u8 arg);

// Early definitions
BOOL FUN_020399E8(struct ScriptContext* ctx);
BOOL FUN_02039CC8(struct ScriptContext* ctx);
extern BOOL FUN_0203A2F0(struct ScriptContext* ctx);

// Functions
// Names taken from
// https://docs.google.com/spreadsheets/d/16OKEM1UjX8BWE3Gab1DCRChs4jOIPXj06CA5aHee9KQ/edit?usp=sharing

THUMB_FUNC BOOL ScrCmd_Nop(struct ScriptContext* ctx) {
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Dummy(struct ScriptContext* ctx) {
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_End(struct ScriptContext* ctx) {
    StopScript(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TimeWait(struct ScriptContext* ctx) {
    u32 unk80 = ctx->unk80;
    u16 num = ScriptReadHalfword(ctx);
    u16 wk = ScriptReadHalfword(ctx);
    u16* unk = FUN_020394B8(unk80, wk);
    *unk = num;
    ctx->data[0] = wk;
    SetupNativeScript(ctx, FUN_020399E8);
    return TRUE;
}

THUMB_FUNC BOOL FUN_020399E8(struct ScriptContext* ctx) {
    u16* unk = FUN_020394B8(ctx->unk80, ctx->data[0]);
    *unk = *unk - 1;
    if (*unk == 0) {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_DebugWatch(struct ScriptContext* ctx) {
    u16 unk = ScriptReadHalfword(ctx);
    FUN_020394F0(ctx->unk80, unk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadRegValue(struct ScriptContext* ctx) {
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = ScriptReadByte(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadRegWData(struct ScriptContext* ctx) {
    u8 index = ScriptReadByte(ctx);
    u32 val = ScriptReadWord(ctx);
    ctx->data[index] = val;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadRegAdrs(struct ScriptContext* ctx) {
    u8 index = ScriptReadByte(ctx);
    u8* ptr = (u8*)ScriptReadWord(ctx);
    ctx->data[index] = *ptr;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadAdrsValue(struct ScriptContext* ctx) {
    u8* ptr = (u8*)ScriptReadWord(ctx);
    u8 val = ScriptReadByte(ctx);
    *ptr = val;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadAdrsReg(struct ScriptContext* ctx) {
    u8* ptr = (u8*)ScriptReadWord(ctx);
    u8 index = ScriptReadByte(ctx);
    *ptr = ctx->data[index];
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadRegReg(struct ScriptContext* ctx) {
    u8 index_store = ScriptReadByte(ctx);
    u8 index_load = ScriptReadByte(ctx);
    ctx->data[index_store] = ctx->data[index_load];
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadAdrsAdrs(struct ScriptContext* ctx) {
    u8* target = (u8*)ScriptReadWord(ctx);
    u8* source = (u8*)ScriptReadWord(ctx);
    *target = *source;
    return FALSE;
}

THUMB_FUNC u32 CompareUtil(u16 a, u16 b) {
    if (a < b) {
        return 0;
    } else if (a == b) {
        return 1;
    } else {
        return 2;
    }
}

THUMB_FUNC BOOL ScrCmd_CmpRegReg(struct ScriptContext* ctx) {
    u8 a = ctx->data[ScriptReadByte(ctx)];
    u8 b = ctx->data[ScriptReadByte(ctx)];
    ctx->comparisonResult = CompareUtil(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CmpRegValue(struct ScriptContext* ctx) {
    u8 a = ctx->data[ScriptReadByte(ctx)];
    u8 b = ScriptReadByte(ctx);
    ctx->comparisonResult = CompareUtil(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CmpRegAdrs(struct ScriptContext* ctx) {
    u8 a = ctx->data[ScriptReadByte(ctx)];
    u8 b = *(u8*)ScriptReadWord(ctx);
    ctx->comparisonResult = CompareUtil(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CmpAdrsReg(struct ScriptContext* ctx) {
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = ctx->data[ScriptReadByte(ctx)];
    ctx->comparisonResult = CompareUtil(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CmpAdrsValue(struct ScriptContext* ctx) {
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = ScriptReadByte(ctx);
    ctx->comparisonResult = CompareUtil(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CmpAdrsAdrs(struct ScriptContext* ctx) {
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = *(u8*)ScriptReadWord(ctx);
    ctx->comparisonResult = CompareUtil(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CmpWkValue(struct ScriptContext* ctx) {
    u16* wk = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    u16 a = *wk;
    u16 b = ScriptReadHalfword(ctx);
    ctx->comparisonResult = CompareUtil(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CmpWkWk(struct ScriptContext* ctx) {
    u16* wk1 = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    u16* wk2 = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    ctx->comparisonResult = CompareUtil(*wk1, *wk2);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_VMMachineAdd(struct ScriptContext* ctx) {
    u32 unk80 = ctx->unk80;
    u8* unk1 = FUN_02039438(unk80, 0x7);
    u32** unk2 = FUN_02039438(unk80, 0xe);
    u16 id = ScriptReadHalfword(ctx);

    *unk2 = FUN_02038EB0(unk80, id);
    *unk1 = *unk1 + 1;
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_ChangeCommonScr(struct ScriptContext* ctx) {
    u32 unk80 = ctx->unk80;
    u8* unk_flag_0x5 = FUN_02039438(unk80, 0x5);
    u8* unk2 = FUN_02039438(unk80, 0x7);
    u32** unk3 = FUN_02039438(unk80, 0xe);

    u16 id = ScriptReadHalfword(ctx);
    *unk_flag_0x5 = 1;
    *unk3 = FUN_02038EB0(unk80, id);
    *unk2 = *unk2 + 1;

    SetupNativeScript(ctx, FUN_02039CC8);
    return TRUE;
}

THUMB_FUNC BOOL FUN_02039CC8(struct ScriptContext* ctx) {
    u8* unk_flag_0x5 = FUN_02039438(ctx->unk80, 0x5);

    if (*unk_flag_0x5 == 0) {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ChangeLocalScr(struct ScriptContext* ctx) {
    u8* unk_flag_0x5 = FUN_02039438(ctx->unk80, 0x5);
    *unk_flag_0x5 = 0;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GlobalJump(struct ScriptContext* ctx) {
    s32 offset = (s32)ScriptReadWord(ctx);  // Using s32 since it's also used negative
    ScriptJump(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ObjIDJump(struct ScriptContext* ctx) {
    u32* unk = FUN_02039438(ctx->unk80, 0xa);
    u8 id = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);
    if (FUN_02058448(*unk) == id) {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_BgIDJump(struct ScriptContext* ctx) {
    u32 unk = FUN_02046534(ctx->unk74);
    u8 id = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (unk == id) {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_PlayerDirJump(struct ScriptContext* ctx) {
    u32* unk = FUN_02039438(ctx->unk80, 0x9);
    u8 dir = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (*unk == dir) {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GlobalCall(struct ScriptContext* ctx) {
    s32 offset = (s32)ScriptReadWord(ctx);
    ScriptCall(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Ret(struct ScriptContext* ctx) {
    ScriptReturn(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_IfJump(struct ScriptContext* ctx) {
    u8 compareType = ScriptReadByte(ctx);
    s32 offset = (s32) ScriptReadWord(ctx);

    // ConditionLookup[compareType][ctx->comparisonResult]
    if (ConditionLookup[compareType][ctx->comparisonResult] == TRUE) {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_IfCall(struct ScriptContext* ctx) {
    u8 compareType = ScriptReadByte(ctx);
    s32 offset = (s32) ScriptReadWord(ctx);

    // ConditionLookup[compareType][ctx->comparisonResult]
    if (ConditionLookup[compareType][ctx->comparisonResult] == TRUE) {
        ScriptCall(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_FlagSet(struct ScriptContext* ctx) {
    u32 unk80 = ctx->unk80;
    u16 flag = ScriptReadHalfword(ctx);
    FUN_0203953C(unk80, flag);
    return FALSE;
}


THUMB_FUNC BOOL ScrCmd_FlagReset(struct ScriptContext* ctx) {
    u32 unk80 = ctx->unk80;
    u16 flag = ScriptReadHalfword(ctx);
    FUN_02039550(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_FlagCheck(struct ScriptContext* ctx) {
    u32 unk80 = ctx->unk80;
    u16 flag = ScriptReadHalfword(ctx);
    ctx->comparisonResult = FUN_02039528(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_FlagCheckWk(struct ScriptContext* ctx) {
    u32 unk80 = ctx->unk80;
    u16* wk1 = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    u16* wk2 = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    *wk2 = FUN_02039528(unk80, *wk1);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_FlagSetWk(struct ScriptContext* ctx) {
    u32 unk80 = ctx->unk80;
    u16* wk = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    FUN_0203953C(unk80, *wk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TrainerFlagSet(struct ScriptContext* ctx) {
    u32 unk80 = ctx->unk80;
    u16 wk = FUN_020394F0(ctx->unk80, ScriptReadHalfword(ctx));
    FUN_0203965C(unk80,  wk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TrainerFlagReset(struct ScriptContext* ctx) {
    u32 unk80 = ctx->unk80;
    u16 wk = FUN_020394F0(ctx->unk80, ScriptReadHalfword(ctx));
    FUN_02039678(unk80,  wk);
    return FALSE;
}


THUMB_FUNC BOOL ScrCmd_TrainerFlagCheck(struct ScriptContext* ctx) {
    u32 unk80 = ctx->unk80;
    u16 wk = FUN_020394F0(ctx->unk80, ScriptReadHalfword(ctx));
    ctx->comparisonResult = FUN_02039640(unk80,  wk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_WkAdd(struct ScriptContext* ctx) {
    u16* wk1 = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    u16 wk2 = FUN_020394F0(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = *wk1 + wk2;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_WkSub(struct ScriptContext* ctx) {
    u16* wk1 = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    u16 wk2 = FUN_020394F0(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = *wk1 - wk2;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadWkValue(struct ScriptContext* ctx) {
    u16* wk1 = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = ScriptReadHalfword(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadWkWk(struct ScriptContext* ctx) {
    u16* wk1 = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    u16* wk2 = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = *wk2;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadWkWkValue(struct ScriptContext* ctx) {
    u16* wk1 = FUN_020394B8(ctx->unk80, ScriptReadHalfword(ctx));
    u16 wk2 = FUN_020394F0(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = wk2;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TalkMsgAllPut(struct ScriptContext* ctx) {
    u8 id = ScriptReadByte(ctx);
    MOD05_021E2C24(ctx, ctx->unk78, id);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TalkMsgAllPutOtherArc(struct ScriptContext* ctx) {
    u16 arc = FUN_020394F0(ctx->unk80, ScriptReadHalfword(ctx));
    u16 msg = FUN_020394F0(ctx->unk80, ScriptReadHalfword(ctx));
    u32 unk = FUN_0200A86C(0x1, 0x1a, arc, 0x20);
    MOD05_021E2C24(ctx, unk, msg);
    FUN_0200A8B8(unk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TalkMsgOtherArc(struct ScriptContext* ctx) {
    u16 arc = FUN_020394F0(ctx->unk80, ScriptReadHalfword(ctx));
    u16 msg = FUN_020394F0(ctx->unk80, ScriptReadHalfword(ctx));
    u32 unk = FUN_0200A86C(0x1, 0x1a, arc, 0x20);
    MOD05_021E2BD0(ctx, unk, msg, 1, 0);
    FUN_0200A8B8(unk);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_TalkMsgAllPutPMS(struct ScriptContext* ctx) {
    u16 typ = ScriptReadHalfword(ctx);
    u16 id = ScriptReadHalfword(ctx);
    u16 word1 = ScriptReadHalfword(ctx);
    u16 word2 = ScriptReadHalfword(ctx);

    MOD05_021E2C58(ctx, typ, id, word1, word2, 0xff);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TalkMsgPMS(struct ScriptContext* ctx) {
    u16 typ = ScriptReadHalfword(ctx);
    u16 id = ScriptReadHalfword(ctx);
    u16 word1 = ScriptReadHalfword(ctx);
    u16 word2 = ScriptReadHalfword(ctx);

    MOD05_021E2C58(ctx, typ, id, word1, word2, 0x1);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

/*
// Commented out as it comes later in the file
BOOL FUN_0203A2F0(struct ScriptContext* ctx) {
    u8* unk = FUN_02039438(ctx->unk80, 0x3);
    return FUN_020546C8(*unk);
}
*/
