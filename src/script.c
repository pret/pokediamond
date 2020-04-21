#include "nitro.h"
#include "script.h"

void InitScriptContext(struct ScriptContext *ctx, void *cmdTable, void *cmdTableEnd)
{
    u32 i;

    ctx->mode = 0;
    ctx->scriptPtr = 0;
    ctx->stackDepth = 0;
    ctx->nativePtr = 0;
    ctx->cmdTable = cmdTable;
    ctx->cmdTableEnd = cmdTableEnd;

    for (i = 0; i < 4; i++)
        ctx->data[i] = 0;

    for (i = 0; i < 20; i++)
        ctx->stack[i] = 0;

    ctx->unk74 = 0;
}

u8 SetupBytecodeScript(struct ScriptContext *ctx, const u8 *ptr)
{
    ctx->scriptPtr = ptr;
    ctx->mode = 1;
    return 1;
}

void SetupNativeScript(struct ScriptContext *ctx, u8 (*ptr)(void))
{
    ctx->mode = 2;
    ctx->nativePtr = ptr;
}

void StopScript(struct ScriptContext *ctx)
{
    ctx->mode = 0;
    ctx->scriptPtr = 0;
}

void FUN_02038B6C(struct ScriptContext *ctx, int r1)
{
    ctx->unk74 = r1;
}

extern void ErrorHandling(void);

#ifdef NONMATCHING
u8 RunScriptCommand(struct ScriptContext *ctx)
{
    struct ScriptContext *localCtx = ctx;

    if (localCtx->mode == 0)
        return FALSE;

    switch (localCtx->mode)
    {
    case 0:
        return FALSE;
    case 2:
        if (localCtx->nativePtr)
        {
            if (localCtx->nativePtr() == TRUE)
                localCtx->mode = 1;
            return TRUE;
        }
        localCtx->mode = 1;
    case 1:
        while (1)
        {
            u16 cmdCode;
            ScrCmdFunc *func;

            if (!localCtx->scriptPtr)
            {
                localCtx->mode = 0;
                return FALSE;
            }

            cmdCode = ScriptReadHalfword(localCtx);
            if ((u32)localCtx->cmdTableEnd >= cmdCode)
            {
                ErrorHandling();
				localCtx->mode = 0;
                return FALSE;
            }

            func = &localCtx->cmdTable[cmdCode];

            if ((*func)(localCtx) == 1)
                break;
        }
    }

    return TRUE;
}
#else
u8 RunScriptCommand(struct ScriptContext *ctx)
{
    __asm {
    	add r4, r0, #0x0
    	ldrb r1, [r4, #0x1]
    	cmp r1, #0x0
    	bne _02038B7E
    	mov r0, #0x0
    	pop {r4, pc}
    _02038B7E:
    	beq _02038B8A
    	cmp r1, #0x1
    	beq _02038BA6
    	cmp r1, #0x2
    	beq _02038B8E
    	b _02038BD8
    _02038B8A:
    	mov r0, #0x0
    	pop {r4, pc}
    _02038B8E:
    	ldr r1, [r4, #0x4]
    	cmp r1, #0x0
    	beq _02038BA2
    	blx r1
    	cmp r0, #0x1
    	bne _02038B9E
    	mov r0, #0x1
    	strb r0, [r4, #0x1]
    _02038B9E:
    	mov r0, #0x1
    	pop {r4, pc}
    _02038BA2:
    	mov r0, #0x1
    	strb r0, [r4, #0x1]
        // for some reason it adds a b _02038BA6 here
    _02038BA6:
    	ldr r0, [r4, #0x8]
    	cmp r0, #0x0
    	bne _02038BB2
    	mov r0, #0x0
    	strb r0, [r4, #0x1]
    	pop {r4, pc}
    _02038BB2:
    	add r0, r4, #0x0
    	bl ScriptReadHalfword
    	add r1, r0, #0x0
    	ldr r0, [r4, #0x60]
    	cmp r1, r0
    	blo _02038BCA
    	bl ErrorHandling
    	mov r0, #0x0
    	strb r0, [r4, #0x1]
    	pop {r4, pc}
    _02038BCA:
    	ldr r2, [r4, #0x5c]
    	lsl r1, r1, #0x2
    	ldr r1, [r2, r1]
    	add r0, r4, #0x0
    	blx r1
    	cmp r0, #0x1
    	bne _02038BA6
    _02038BD8:
    	mov r0, #0x1
    }
}
#endif

u8 ScriptPush(struct ScriptContext *ctx, const u8 *ptr)
{
    if (ctx->stackDepth + 1 >= 20)
    {
        return 1;
    }
    else
    {
        ctx->stack[ctx->stackDepth] = ptr;
        ctx->stackDepth++;
        return 0;
    }
}

const u8 *ScriptPop(struct ScriptContext *ctx)
{
    if (ctx->stackDepth == 0)
        return NULL;

    ctx->stackDepth--;
    return ctx->stack[ctx->stackDepth];
}

void ScriptJump(struct ScriptContext *ctx, const u8 *ptr)
{
    ctx->scriptPtr = ptr;
}

void ScriptCall(struct ScriptContext *ctx, const u8 *ptr)
{
    ScriptPush(ctx, ctx->scriptPtr);
    ctx->scriptPtr = ptr;
}

void ScriptReturn(struct ScriptContext *ctx)
{
    ctx->scriptPtr = ScriptPop(ctx);
}

u16 ScriptReadHalfword(struct ScriptContext *ctx)
{
    u16 value = *(ctx->scriptPtr++);
    value += *(ctx->scriptPtr++) << 8;
    return value;
}

u32 ScriptReadWord(struct ScriptContext *ctx)
{
    u32 value0 = *(ctx->scriptPtr++);
    u32 value1 = *(ctx->scriptPtr++);
    u32 value2 = *(ctx->scriptPtr++);
    u32 value3 = *(ctx->scriptPtr++);
    u32 retVal = 0;

    retVal += value3;
    retVal <<= 8;
    retVal += value2;
    retVal <<= 8;
    retVal += value1;
    retVal <<= 8;
    retVal += value0;
    return retVal;
}
