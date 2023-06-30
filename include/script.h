#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "global.h"
#include "bg_window.h"
#include "camera.h"
#include "fashion_case.h"
#include "field_player_avatar.h"
#include "msgdata.h"
#include "render_window.h"
#include "save.h"
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
} PCBoxAppData; //todo move to own file

typedef struct FashionAppData {
    SaveFashionData *fashionData;
    u32 portraitSlot;
    BOOL isContest;
} FashionAppData;

typedef struct TownMapAppData { //todo fill out
    u8 padding[0x140];
} TownMapAppData; //todo move to own file

typedef struct ScrCmdUnkStruct01D9 {
    struct SaveData *save;
    u16 unk04;
    u16 unk06;
} ScrCmdUnkStruct01D9; //todo identify and move to own file

typedef struct StarterSelectionData {
    s32 state;
    struct Options *options;
} StarterSelectionData; //todo move to own file

typedef struct BagScreenAppData {

} BagScreenAppData; //todo fill out and move to own file

typedef struct ScrCmdUnkStruct00F4 {
    u8 padding[0x2C];
    u32 unk2C;
} ScrCmdUnkStruct00F4; //todo identify and move to own file

typedef struct Location {
    u32 mapId;
    u32 warpId;
    u32 x;
    u32 y;
    u32 direction;
} Location;

typedef struct UnkFieldStruct04 {
    u8 padding[0xC];
    u32 unk0C;
} UnkFieldStruct04;

typedef struct LocalFieldData {

} LocalFieldData; //todo fill out and move to own file

typedef struct RoamerSaveData {

} RoamerSaveData; //todo: fill out and move to own file

typedef struct MapObjectManager {

} MapObjectManager; //todo: fill out

typedef struct PokedexAppData {
    
} PokedexAppData; //todo: fill out and move to own file

typedef struct NPCTradeAppData {

} NPCTradeAppData; //todo: fill out and move to own file

typedef struct Poffin {

} Poffin; //todo: fill out and move to own file

typedef struct SavePoffinData {

} SavePoffinData; //todo: fill out and move to own file

typedef struct SaveStatsPrinter {

} SaveStatsPrinter; //todo: fill out and move to own file

typedef struct FieldSystem //todo move to field_system.c
{
    u32 *unk00;
    UnkFieldStruct04 *unk04;
    struct BgConfig *bgConfig;
    struct SaveData *saveData; //0xC
    TaskManager *taskManager;
    u8 padding2[0x8];
    Location *location;
    struct Camera *camera;
    u32 unk24;
    u8 padding3[0xC];
    MapObjectManager *mapObjectManager;
    struct PlayerAvatar *playerAvatar;
    u8 padding4[0x24];
    u32 unk60;
    u8 padding5[0x14];
    u32 unk78;
    u32 unk7C;
    u8 padding6[0x10];
    u32 unk90;
    u8 padding7[0x4];
    u32 *unk98;
    u8 padding8[0xC];
    struct UnkStruct_02046444 * unkA8;
} FieldSystem;

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
    SCRIPTENV_COIN_BOX, //differs from heartgold due to athlete points
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
