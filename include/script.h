#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "global.h"
#include "msgdata.h"
#include "save_block_2.h"

struct ScriptContext;

typedef u8 (*ScrCmdFunc)(struct ScriptContext *);
typedef u8 Script[];

struct ScriptContext80
{
    u8 filler_00[12];
    struct SaveBlock2 * unkC;
    u8 filler_10[0xC];
    u32 * unk1C;
};

struct ScriptContext
{
    u8 stackDepth;
    u8 mode;
    u8 comparisonResult;
    u8 (*nativePtr)(struct ScriptContext *);
    const u8 *scriptPtr;
    const u8 *stack[20];
    ScrCmdFunc *cmdTable;
    u32 cmdCount;
    u32 data[4];
    struct UnkStruct_0204639C * unk74;
	struct MsgData * unk78;
	u8 *unk7C;
    struct ScriptContext80 * unk80;
};

#define ScriptReadByte(ctx) (*(ctx->scriptPtr++))

void InitScriptContext(struct ScriptContext *ctx, void *cmdTable, u32 cmdCount);
u8 SetupBytecodeScript(struct ScriptContext *ctx, const u8 *ptr);
void SetupNativeScript(struct ScriptContext *ctx, u8 (*ptr)(struct ScriptContext *));
void StopScript(struct ScriptContext *ctx);
void ScriptContext_SetField74(struct ScriptContext *ctx, struct UnkStruct_0204639C * r1);
u8 RunScriptCommand(struct ScriptContext *ctx);
u8 ScriptPush(struct ScriptContext *ctx, const u8 *ptr);
const u8 *ScriptPop(struct ScriptContext *ctx);
void ScriptJump(struct ScriptContext *ctx, const u8 *ptr);
u8 ScriptCall(struct ScriptContext *ctx, const u8 *ptr);
void ScriptReturn(struct ScriptContext *ctx);
u16 ScriptReadHalfword(struct ScriptContext *ctx);
u32 ScriptReadWord(struct ScriptContext *ctx);

#endif // _SCRIPT_H_
