#ifndef _SCRIPT_H_
#define _SCRIPT_H_

struct ScriptContext;

typedef u8 (*ScrCmdFunc)(struct ScriptContext *);
typedef u8 Script[];

struct ScriptContext
{
    u8 stackDepth;
    u8 mode;
    u8 comparisonResult;
    u8 (*nativePtr)(struct ScriptContext *);
    const u8 *scriptPtr;
    const u8 *stack[20];
    ScrCmdFunc *cmdTable;
    ScrCmdFunc *cmdTableEnd;
    u32 data[4];
	u32 unk74;
};

#define ScriptReadByte(ctx) (*(ctx->scriptPtr++))

u16 ScriptReadHalfword(struct ScriptContext *ctx);

#endif // _SCRIPT_H_
