#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "global.h"
#include "camera.h"
#include "msgdata.h"
#include "save_block_2.h"
#include "bg_window.h"


struct ScriptContext;

typedef u8 (*ScrCmdFunc)(struct ScriptContext *);
typedef u8 Script[];


struct UnkStruct_020464D4
{
    u16 unk0[4];
    u8 padding[0x108];
};

struct UnkStruct_02046444
{
    u8 padding[0x90];
    struct UnkStruct_020464D4 unk90[1]; //todo find size
};

struct UnkSavStruct80
{
    u32 *unk00;
    u8 padding[0x4];
    struct BgConfig *unk08;
    struct SaveBlock2 *saveBlock2; //0xC
    struct UnkStruct_0204639C *unk10;
    u8 padding2[0x8];
    u32 *mapId; //0x1C
    struct CameraWork *cameraWork;
    u32 unk24;
    u8 padding3[0xC];
    u32 unk34;
    u32 unk38;
    u8 padding4[0x24];
    u32 unk60;
    u8 padding5[0x14];
    u32 unk78;
    u8 padding6[0x1C];
    void *unk98;
    u8 padding7[0xC];
    struct UnkStruct_02046444 * unkA8;
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
    u32 cmdCount;
    u32 data[4];
    struct UnkStruct_0204639C *unk74;
    struct MsgData *msgData;
    u8 *unk7C;
    struct UnkSavStruct80 *unk80;
};

#define ScriptReadByte(ctx) (*(ctx->scriptPtr++))

void InitScriptContext(struct ScriptContext *ctx, void *cmdTable, u32 cmdCount);
u8 SetupBytecodeScript(struct ScriptContext *ctx, const u8 *ptr);
void SetupNativeScript(struct ScriptContext *ctx, BOOL (*ptr)(struct ScriptContext *));
void StopScript(struct ScriptContext *ctx);
void FUN_02038B6C(struct ScriptContext *ctx, struct UnkStruct_0204639C *r1);
u8 RunScriptCommand(struct ScriptContext *ctx);
u8 ScriptPush(struct ScriptContext *ctx, const u8 *ptr);
const u8 *ScriptPop(struct ScriptContext *ctx);
void ScriptJump(struct ScriptContext *ctx, const u8 *ptr);
u8 ScriptCall(struct ScriptContext *ctx, const u8 *ptr);
void ScriptReturn(struct ScriptContext *ctx);
u16 ScriptReadHalfword(struct ScriptContext *ctx);
u32 ScriptReadWord(struct ScriptContext *ctx);

#endif // _SCRIPT_H_
