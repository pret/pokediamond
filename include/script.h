#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "global.h"
#include "bg_window.h"
#include "camera.h"
#include "field_player_avatar.h"
#include "msgdata.h"
#include "render_window.h"
#include "save_block_2.h"
#include "task.h"

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

typedef struct LocalMapObject { //todo move to local_map_object.c
    u8 padding[0x12C]; //todo verify size
} LocalMapObject;

typedef struct PartyMenuAppData PartyMenuAppData; //todo move to own file

struct FieldSystem //todo move to field_system.c
{
    u32 *unk00;
    u8 padding[0x4];
    struct BgConfig *bgConfig;
    struct SaveBlock2 *saveBlock2; //0xC
    struct TaskManager *taskManager;
    u8 padding2[0x8];
    u32 *mapId; //0x1C
    struct Camera *camera;
    u32 unk24;
    u8 padding3[0xC];
    u32 unk34;
    struct PlayerAvatar *playerAvatar;
    u8 padding4[0x24];
    u32 unk60;
    u8 padding5[0x14];
    u32 unk78;
    u8 padding6[0x1C];
    void *unk98;
    u8 padding7[0xC];
    struct UnkStruct_02046444 * unkA8;
};

typedef struct ScriptContext
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
    struct TaskManager *taskManager;
    struct MsgData *msgData;
    u8 *mapScripts;
    struct FieldSystem *fieldSystem;
} ScriptContext;

typedef enum ScriptEnvField {
    SCRIPTENV_MENU_WINDOW,
    SCRIPTENV_WINDOW,
    SCRIPTENV_LIST_MENU_2D,
    SCRIPTENV_TEXT_PRINTER_NUMBER,
    SCRIPTENV_ACTIVE_MOVEMENT_COUNTER,
    SCRIPTENV_UNKNOWN_05,
    SCRIPTENV_UNKNOWN_06,
    SCRIPTENV_ACTIVE_SCRIPTCONTEXT_COUNT,
    SCRIPTENV_ACTIVE_SCRIPT_NUMBER,
    SCRIPTENV_FACING_DIRECTION,
    SCRIPTENV_LAST_INTERACTED,
    SCRIPTENV_CAMERA_TARGET,
    SCRIPTENV_UNKNOWN_12,
    SCRIPTENV_SCRIPT_CONTEXT_0,
    SCRIPTENV_SCRIPT_CONTEXT_1, //diamond does not appear to have SCRIPT_CONTEXT_2 like HG
    SCRIPTENV_MESSAGE_FORMAT,
    SCRIPTENV_STRING_BUFFER_0,
    SCRIPTENV_STRING_BUFFER_1,
    SCRIPTENV_WAITING_ICON,
    SCRIPTENV_RUNNING_APP_DATA,
    SCRIPTENV_MISC_DATA_PTR,
    SCRIPTENV_UNKNOWN_21,
    SCRIPTENV_UNKNOWN_22,
    SCRIPTENV_BATTLE_WIN_FLAG,
    SCRIPTENV_ENGAGED_TRAINER_0_FIELD_00,
    SCRIPTENV_ENGAGED_TRAINER_0_FIELD_04,
    SCRIPTENV_ENGAGED_TRAINER_0_FIELD_08,
    SCRIPTENV_ENGAGED_TRAINER_0_ID,
    SCRIPTENV_ENGAGED_TRAINER_0_ENCOUNTER_TYPE,
    SCRIPTENV_ENGAGED_TRAINER_0_EVENT,
    SCRIPTENV_ENGAGED_TRAINER_0_FIELD_18,
    SCRIPTENV_ENGAGED_TRAINER_1_FIELD_00,
    SCRIPTENV_ENGAGED_TRAINER_1_FIELD_04,
    SCRIPTENV_ENGAGED_TRAINER_1_FIELD_08,
    SCRIPTENV_ENGAGED_TRAINER_1_ID,
    SCRIPTENV_ENGAGED_TRAINER_1_ENCOUNTER_TYPE,
    SCRIPTENV_ENGAGED_TRAINER_1_EVENT,
    SCRIPTENV_ENGAGED_TRAINER_1_FIELD_18,
} ScriptEnvField;

#define ScriptReadByte(ctx) (*(ctx->scriptPtr++))

void InitScriptContext(struct ScriptContext *ctx, void *cmdTable, u32 cmdCount);
u8 SetupBytecodeScript(struct ScriptContext *ctx, const u8 *ptr);
void SetupNativeScript(struct ScriptContext *ctx, BOOL (*ptr)(struct ScriptContext *));
void StopScript(struct ScriptContext *ctx);
void FUN_02038B6C(struct ScriptContext *ctx, struct TaskManager *taskManger);
u8 RunScriptCommand(struct ScriptContext *ctx);
u8 ScriptPush(struct ScriptContext *ctx, const u8 *ptr);
const u8 *ScriptPop(struct ScriptContext *ctx);
void ScriptJump(struct ScriptContext *ctx, const u8 *ptr);
u8 ScriptCall(struct ScriptContext *ctx, const u8 *ptr);
void ScriptReturn(struct ScriptContext *ctx);
u16 ScriptReadHalfword(struct ScriptContext *ctx);
u32 ScriptReadWord(struct ScriptContext *ctx);

#endif // _SCRIPT_H_
