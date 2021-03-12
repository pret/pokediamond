#ifndef POKEDIAMOND_SCRCMD_H
#define POKEDIAMOND_SCRCMD_H

#include "global.h"
#include "script.h"

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

//scrcmd_18.c
BOOL ScrCmd_GiveMon(struct ScriptContext* ctx);

#endif //POKEDIAMOND_SCRCMD_H
