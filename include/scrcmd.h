#ifndef POKEDIAMOND_SCRCMD_H
#define POKEDIAMOND_SCRCMD_H

#include "global.h"
#include "script.h"

struct UnkStruct_0203A288 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 padding[1];
};

//scrcmd.c
BOOL ScrCmd_Nop(struct ScriptContext* ctx);
BOOL ScrCmd_Dummy(struct ScriptContext* ctx);
BOOL ScrCmd_End(struct ScriptContext* ctx);
BOOL ScrCmd_Wait(struct ScriptContext* ctx);
BOOL ScrCmd_DebugWatch(struct ScriptContext* ctx);
BOOL ScrCmd_LoadByte(struct ScriptContext* ctx);
BOOL ScrCmd_LoadWord(struct ScriptContext* ctx);
BOOL ScrCmd_LoadByteFromAddr(struct ScriptContext* ctx);
BOOL ScrCmd_WriteByteToAddr(struct ScriptContext* ctx);
BOOL ScrCmd_SetPtrByte(struct ScriptContext* ctx);
BOOL ScrCmd_CopyLocal(struct ScriptContext* ctx);
BOOL ScrCmd_CopyByte(struct ScriptContext* ctx);
BOOL ScrCmd_CompareLocalToLocal(struct ScriptContext* ctx);
BOOL ScrCmd_CompareLocalToValue(struct ScriptContext* ctx);
BOOL ScrCmd_CompareLocalToAddr(struct ScriptContext* ctx);
BOOL ScrCmd_CompareAddrToLocal(struct ScriptContext* ctx);
BOOL ScrCmd_CompareAddrToValue(struct ScriptContext* ctx);
BOOL ScrCmd_CompareAddrToAddr(struct ScriptContext* ctx);
BOOL ScrCmd_CompareVarToValue(struct ScriptContext* ctx);
BOOL ScrCmd_CompareVarToVar(struct ScriptContext* ctx);
BOOL ScrCmd_RunScript(struct ScriptContext* ctx);
BOOL ScrCmd_RunScriptWait(struct ScriptContext* ctx);
BOOL ScrCmd_RestartCurrentScript(struct ScriptContext* ctx);
BOOL ScrCmd_GoTo(struct ScriptContext* ctx);
BOOL ScrCmd_ObjectGoTo(struct ScriptContext* ctx);
BOOL ScrCmd_BgGoTo(struct ScriptContext* ctx);
BOOL ScrCmd_DirectionGoTo(struct ScriptContext* ctx);
BOOL ScrCmd_Call(struct ScriptContext* ctx);
BOOL ScrCmd_Return(struct ScriptContext* ctx);
BOOL ScrCmd_GoToIf(struct ScriptContext* ctx);
BOOL ScrCmd_CallIf(struct ScriptContext* ctx);
BOOL ScrCmd_SetFlag(struct ScriptContext* ctx);
BOOL ScrCmd_ClearFlag(struct ScriptContext* ctx);
BOOL ScrCmd_CheckFlag(struct ScriptContext* ctx);
BOOL ScrCmd_CheckFlagVar(struct ScriptContext* ctx);
BOOL ScrCmd_SetFlagVar(struct ScriptContext* ctx);
BOOL ScrCmd_SetTrainerFlag(struct ScriptContext* ctx);
BOOL ScrCmd_ClearTrainerFlag(struct ScriptContext* ctx);
BOOL ScrCmd_CheckTrainerFlag(struct ScriptContext* ctx);
BOOL ScrCmd_AddVar(struct ScriptContext* ctx);
BOOL ScrCmd_SubVar(struct ScriptContext* ctx);
BOOL ScrCmd_SetVar(struct ScriptContext* ctx);
BOOL ScrCmd_CopyVar(struct ScriptContext* ctx);
BOOL ScrCmd_SetOrCopyVar(struct ScriptContext* ctx);
BOOL ScrCmd_Message(struct ScriptContext* ctx);
BOOL ScrCmd_MessageFrom(struct ScriptContext* ctx);
BOOL ScrCmd_MessageFrom2(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01FC(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01FD(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01FE(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01FF(struct ScriptContext* ctx);
BOOL ScrCmd_Unk026D(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002C(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002D(struct ScriptContext* ctx);
BOOL ScrCmd_Unk02C0(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002E(struct ScriptContext* ctx);
BOOL ScrCmd_Unk020C(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002F(struct ScriptContext* ctx);
BOOL ScrCmd_WaitButtonAB(struct ScriptContext* ctx);
BOOL ScrCmd_WaitButtonABTime(struct ScriptContext *ctx);
BOOL ScrCmd_WaitButton(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0032(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0033(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0034(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0035(struct ScriptContext* ctx);
BOOL ScrCmd_ScrollBg(struct ScriptContext* ctx);
BOOL ScrCmd_CreateMessageBox(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0037(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0038(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0039(struct ScriptContext* ctx);
BOOL ScrCmd_Unk003A(struct ScriptContext* ctx);

//scrcmd_18.c
BOOL ScrCmd_GiveMon(struct ScriptContext* ctx);

#endif //POKEDIAMOND_SCRCMD_H
