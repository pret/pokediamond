#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "global.h"

struct ScriptContext;

typedef u8 (*ScrCmdFunc)(struct ScriptContext *);
typedef u8 Script[];

struct Unk21C48B8
{
    void (*unk0)(s32);
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    u8 filler3C[0xC];
    s32 unk48;
    u8 filler4C[0x20];
    s32 unk6C;
};

extern struct Unk21C48B8 gUnknown21C48B8;

struct UnkStruct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
};

struct UnkSubStruct90 {
    u16 unk0[4];
    u8 filler8[0x108];
}; // size = 0x110

struct UnkSubStructA8 {
    u8 filler0[0x90];
    struct UnkSubStruct90 unksubstruct[1]; // unk size
};

// TODO: What is this struct?
struct UnkStruct80 {
    u8 filler0[0xC];
    u32 unkC;
    u8 filler10[0x98];
    struct UnkSubStructA8 *unkA8;
};

struct ScriptContext
{
    u8 stackDepth;
    u8 mode;
    u8 comparisonResult;
    BOOL (*nativePtr)(struct ScriptContext *);
    const u8 *scriptPtr;
    const u8 *stack[20];
    ScrCmdFunc *cmdTable;
    ScrCmdFunc *cmdTableEnd;
    u32 data[4];
	u32 unk74;
	u32 unk78;
	u32 unk7C;
	struct UnkStruct80* unk80;
};

#define ScriptReadByte(ctx) (*(ctx->scriptPtr++))

void InitScriptContext(struct ScriptContext *ctx, void *cmdTable, void *cmdTableEnd);
u8 SetupBytecodeScript(struct ScriptContext *ctx, const u8 *ptr);
void SetupNativeScript(struct ScriptContext *ctx, BOOL (*ptr)(struct ScriptContext *));
void StopScript(struct ScriptContext *ctx);
void FUN_02038B6C(struct ScriptContext *ctx, s32 r1);
u8 RunScriptCommand(struct ScriptContext *ctx);
u8 ScriptPush(struct ScriptContext *ctx, const u8 *ptr);
const u8 *ScriptPop(struct ScriptContext *ctx);
void ScriptJump(struct ScriptContext *ctx, const u8 *ptr);
u8 ScriptCall(struct ScriptContext *ctx, const u8 *ptr);
void ScriptReturn(struct ScriptContext *ctx);
u16 ScriptReadHalfword(struct ScriptContext *ctx);
u32 ScriptReadWord(struct ScriptContext *ctx);

#endif // _SCRIPT_H_
