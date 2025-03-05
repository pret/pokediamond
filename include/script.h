#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "global.h"

#include "bg_window.h"
#include "camera.h"
#include "fashion_case.h"
#include "field_system.h"
#include "map_object.h"
#include "msgdata.h"
#include "player_avatar.h"
#include "render_window.h"
#include "save.h"
#include "save_local_field_data.h"
#include "task.h"
#include "unk_0205F7A0.h"

struct ScriptContext;

typedef u8 (*ScrCmdFunc)(struct ScriptContext *);
typedef u8 Script[];

typedef struct PartyMenuAppData PartyMenuAppData; // todo move to own file

enum PCBoxOperation {
    PC_BOX_OPERATION_DEPOSIT_MON,
    PC_BOX_OPERATION_WITHDRAW_MON,
    PC_BOX_OPERATION_MOVE_MONS,
    PC_BOX_OPERATION_MOVE_ITEMS,
    PC_BOX_OPERATION_COMPARE_MONS,
};

typedef struct PCBoxAppData {
    struct SaveData *save;
    enum PCBoxOperation operation;
    BOOL unk08;
} PCBoxAppData; // todo move to own file

typedef struct FashionAppData {
    SaveFashionData *fashionData;
    u32 portraitSlot;
    BOOL isContest;
} FashionAppData;

typedef struct ScrCmdUnkStruct01D9 {
    struct SaveData *save;
    u16 unk04;
    u16 unk06;
} ScrCmdUnkStruct01D9; // todo identify and move to own file

typedef struct StarterSelectionData {
    s32 state;
    struct Options *options;
} StarterSelectionData; // todo move to own file

typedef struct BagScreenAppData {

} BagScreenAppData; // todo fill out and move to own file

typedef struct ScrCmdUnkStruct00F4 {
    u8 padding[0x2C];
    void *unk2C;
} ScrCmdUnkStruct00F4; // todo identify and move to own file

typedef struct RoamerSaveData {

} RoamerSaveData; // todo: fill out and move to own file

typedef struct PokedexAppData {

} PokedexAppData; // todo: fill out and move to own file

typedef struct NPCTradeAppData {

} NPCTradeAppData; // todo: fill out and move to own file

typedef struct Poffin {

} Poffin; // todo: fill out and move to own file

typedef struct SavePoffinData {

} SavePoffinData; // todo: fill out and move to own file

typedef struct SaveStatsPrinter {

} SaveStatsPrinter; // todo: fill out and move to own file

typedef struct ScriptContext {
    u8 stackDepth;
    u8 mode;
    u8 comparisonResult;
    BOOL (*nativePtr)(struct ScriptContext *);
    const u8 *scriptPtr;
    const u8 *stack[20];
    ScrCmdFunc *cmdTable;
    u32 cmdCount;
    u32 data[4];
    TaskManager *taskManager;
    struct MsgData *msgData;
    u8 *mapScripts;
    FieldSystem *fieldSystem;
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
    SCRIPTENV_SCRIPT_CONTEXT_1, // diamond does not appear to have SCRIPT_CONTEXT_2 like HG
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
    SCRIPTENV_COIN_BOX, // differs from heartgold due to athlete points
    SCRIPTENV_MONEY_BOX,
    SCRIPTENV_SAVE_STATS_PRINTER,
    SCRIPTENV_SPECIAL_VAR_8000,
    SCRIPTENV_SPECIAL_VAR_8001,
    SCRIPTENV_SPECIAL_VAR_8002,
    SCRIPTENV_SPECIAL_VAR_8003,
    SCRIPTENV_SPECIAL_VAR_8004,
    SCRIPTENV_SPECIAL_VAR_8005,
    SCRIPTENV_SPECIAL_VAR_8006,
    SCRIPTENV_SPECIAL_VAR_8007,
    SCRIPTENV_SPECIAL_VAR_8008,
    SCRIPTENV_SPECIAL_VAR_8009,
    SCRIPTENV_SPECIAL_VAR_800A,
    SCRIPTENV_SPECIAL_VAR_800B,
    SCRIPTENV_SPECIAL_VAR_RESULT,
    SCRIPTENV_SPECIAL_VAR_LAST_INTERACTED
} ScriptEnvField;

#define ScriptReadByte(ctx) (*(ctx->scriptPtr++))

void InitScriptContext(struct ScriptContext *ctx, void *cmdTable, u32 cmdCount);
u8 SetupBytecodeScript(struct ScriptContext *ctx, const u8 *ptr);
void SetupNativeScript(struct ScriptContext *ctx, BOOL (*ptr)(struct ScriptContext *));
void StopScript(struct ScriptContext *ctx);
void sub_02038B6C(struct ScriptContext *ctx, struct TaskManager *taskManger);
u8 RunScriptCommand(struct ScriptContext *ctx);
u8 ScriptPush(struct ScriptContext *ctx, const u8 *ptr);
const u8 *ScriptPop(struct ScriptContext *ctx);
void ScriptJump(struct ScriptContext *ctx, const u8 *ptr);
u8 ScriptCall(struct ScriptContext *ctx, const u8 *ptr);
void ScriptReturn(struct ScriptContext *ctx);
u16 ScriptReadHalfword(struct ScriptContext *ctx);
u32 ScriptReadWord(struct ScriptContext *ctx);

#endif // _SCRIPT_H_
