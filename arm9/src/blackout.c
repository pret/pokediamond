#include "blackout.h"
#include "bg_window.h"
#include "brightness.h"
#include "constants/maps.h"
#include "constants/rgb.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/narc_0328.h"
#include "graphic/font.naix"
#include "gf_gfx_loader.h"
#include "PAD_pad.h"
#include "render_window.h"
#include "save_local_field_data.h"
#include "script.h" //TODO: temp include, remove when structs are split
#include "text.h"
#include "unk_020051F4.h"
#include "unk_0204AF24.h"

static void Blackout_InitDisplays(BgConfig *bgConfig);
static void Blackout_DrawMessage(FieldSystem *fieldSystem, TaskManager *taskManager);
static BOOL Task_ShowPrintedBlackoutMessage(TaskManager *taskManager);
static void Blackout_PrintMessage(BlackoutScreenEnvironment *environment, s32 msgNo, u8 x, u8 y);

extern void BeginNormalPaletteFade(u32 pattern, u32 typeTop, u32 typeBottom, u16 colour, u32 duration, u32 framesPer, HeapID heapId);
extern BOOL IsPaletteFadeFinished(void);
extern SaveData *FieldSystem_GetSaveData(FieldSystem *fieldSystem);
extern LocalFieldData *Save_LocalFieldData_Get(SaveData *save);
extern u16 LocalFieldData_GetBlackoutSpawn(LocalFieldData *localFieldData);
extern void GetDeathWarpData(u16 spawnId, Location *dest);
extern void GetSpecialSpawnWarpData(u16 spawnId, Location *dest);
extern Location *LocalFieldData_GetSpecialSpawnWarpPtr(LocalFieldData *localFieldData);
extern void sub_02049160(TaskManager *taskManager, Location *location);
extern void FieldSystem_ClearFollowingTrainer(FieldSystem *fieldSystem);
extern void QueueScript(TaskManager *taskManager, u16 script, LocalMapObject *lastInteracted, void *param3);
extern void sub_0204AB0C(void);
extern u16 GetMomSpawnId(void);

static const struct GraphicsBanks Blackout_GraphicsBanks = {
    .bg = GX_VRAM_BG_128_B,
    .bgextpltt = GX_VRAM_BGEXTPLTT_NONE,
    .subbg = GX_VRAM_SUB_BG_128_C,
    .subbgextpltt = GX_VRAM_SUB_BGEXTPLTT_NONE,
    .obj = GX_VRAM_OBJ_64_E,
    .objextpltt = GX_VRAM_OBJEXTPLTT_NONE,
    .subobj = GX_VRAM_SUB_OBJ_16_I,
    .subobjextpltt = GX_VRAM_SUB_OBJEXTPLTT_NONE,
    .tex = GX_VRAM_TEX_0_A,
    .texpltt = GX_VRAM_TEXPLTT_01_FG,
};

static const struct GraphicsModes Blackout_GraphicsModes = {
    .dispMode = GX_DISPMODE_GRAPHICS,
    .bgMode = GX_BGMODE_0,
    .subMode = GX_BGMODE_0,
    ._2d3dMode = GX_BG0_AS_2D,
};

static const BgTemplate Blackout_BgTemplate = {
    .x = 0,
    .y = 0,
    .bufferSize = 0x800,
    .baseTile = 0,
    .size = GF_BG_SCR_SIZE_256x256,
    .colorMode = GX_BG_COLORMODE_16,
    .screenBase = GX_BG_SCRBASE_0xf800,
    .charBase = GX_BG_CHARBASE_0x00000,
    .bgExtPltt = GX_BG_EXTPLTT_01,
    .priority = 1,
    .areaOver = GX_BG_AREAOVER_XLU,
    .dummy = 0,
    .mosaic = FALSE
};

static const WindowTemplate Blackout_WindowTemplate = {
    .bgId = GF_BG_LYR_MAIN_3,
    .left = 4,
    .top = 5,
    .width = 25,
    .height = 15,
    .palette = 13,
    .baseTile = 0x01
};

static void Blackout_InitDisplays(BgConfig *bgConfig) {
    GfGfx_SetBanks(&Blackout_GraphicsBanks);
    SetBothScreensModesAndDisable(&Blackout_GraphicsModes);
    InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_3, &Blackout_BgTemplate, GF_BG_TYPE_TEXT);
    GfGfxLoader_GXLoadPal(NARC_GRAPHIC_FONT, NARC_font_narc_0006_NCLR, GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_13_OFFSET, 0x20, HEAP_ID_FIELD);
}

static void Blackout_DrawMessage(FieldSystem *fieldSystem, TaskManager *taskManager) {
    BlackoutScreenEnvironment *env = AllocFromHeap(HEAP_ID_FIELD, sizeof(BlackoutScreenEnvironment));

    GF_ASSERT(env != NULL);
    memset(env, 0, sizeof(BlackoutScreenEnvironment));
    env->state = 0;
    env->fieldSystem = fieldSystem;
    env->bgConfig = BgConfig_Alloc(HEAP_ID_FIELD);

    Blackout_InitDisplays(env->bgConfig);
    env->msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0328_bin, HEAP_ID_FIELD);
    env->msgFmt = MessageFormat_New(HEAP_ID_FIELD);

    AddWindow(env->bgConfig, &env->window, &Blackout_WindowTemplate);

    BufferPlayersName(env->msgFmt, 0, Save_PlayerData_GetProfileAddr(FieldSystem_GetSaveData(fieldSystem)));
    if (fieldSystem->location->mapId == MAP_T01R0201) {
        // {STRVAR_1 3, 0} scurried back\nhome, protecting the exhausted\nand fainted Pokémon from further\nharm...
        Blackout_PrintMessage(env, narc_0328_00004, 0, 0);
    } else {
        // {STRVAR_1 3, 0} scurried to\na Pokémon Center, protecting\nthe exhausted and fainted\nPokémon from further harm...
        Blackout_PrintMessage(env, narc_0328_00003, 0, 0);
    }
    CopyWindowToVram(&env->window);
    TaskManager_Call(taskManager, Task_ShowPrintedBlackoutMessage, env);
}

static BOOL Task_ShowPrintedBlackoutMessage(TaskManager *taskManager) {
    BlackoutScreenEnvironment *env = TaskManager_GetEnvironment(taskManager);
    switch (env->state) {
        case 0:
            BeginNormalPaletteFade(3, 1, 42, RGB_BLACK, 8, 1, HEAP_ID_32);
            env->state++;
            break;
        case 1:
            if (IsPaletteFadeFinished()) {
                env->state++;
            }
            break;
        case 2:
            if (gSystem.newKeys & PAD_BUTTON_A || gSystem.newKeys & PAD_BUTTON_B) {
                BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 8, 1, HEAP_ID_32);
                env->state++;
            }
            break;
        case 3:
            if (IsPaletteFadeFinished()) {
                FillWindowPixelBuffer(&env->window, 0);
                env->state++;
            }
            break;
        case 4:
            ClearFrameAndWindow2(&env->window, FALSE);
            RemoveWindow(&env->window);
            MessageFormat_Delete(env->msgFmt);
            DestroyMsgData(env->msgData);
            FreeBgTilemapBuffer(env->bgConfig, GF_BG_LYR_MAIN_3);
            FreeToHeap(env->bgConfig);
            FreeToHeap(env);
            return TRUE;
    }

    return FALSE;
}

static void Blackout_PrintMessage(BlackoutScreenEnvironment *environment, s32 msgNo, u8 x, u8 y) {
    String *tmpStr = String_New(1024, HEAP_ID_FIELD);
    String *finStr = String_New(1024, HEAP_ID_FIELD);

    FillWindowPixelBuffer(&environment->window, 0);
    ReadMsgDataIntoString(environment->msgData, msgNo, tmpStr);
    StringExpandPlaceholders(environment->msgFmt, finStr, tmpStr);
        
    u32 width = FontID_String_GetWidthMultiline(0, finStr, 0);
    x = (environment->window.width * 8 - width);
    x /= 2;
    x -= 4;

    AddTextPrinterParameterized2(&environment->window, 0, finStr, x, y, TEXT_SPEED_NOTRANSFER, MAKE_TEXT_COLOR(15, 2, 0), NULL);

    String_Delete(tmpStr);
    String_Delete(finStr);
}

BOOL Task_BlackOut(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);
    LocalFieldData *localFieldData;
    Location deathWarp;
    u16 deathSpawn;

    switch (*state) {
        case 0:
            localFieldData = Save_LocalFieldData_Get(fieldSystem->saveData);
            deathSpawn = LocalFieldData_GetBlackoutSpawn(localFieldData);
            GetDeathWarpData(deathSpawn, &deathWarp);
            GetSpecialSpawnWarpData(deathSpawn, LocalFieldData_GetSpecialSpawnWarpPtr(localFieldData));
            sub_02049160(taskManager, &deathWarp);
            FieldSystem_ClearFollowingTrainer(fieldSystem);
            (*state)++;
            break;
        case 1:
            GF_SndStartFadeOutBGM(0, 20);
            (*state)++;
            break;
        case 2:
            if (GF_SndGetFadeTimer() == 0) {
                sub_0204AB0C();
                (*state)++;
            }
            break;
        case 3:
            SetBlendBrightness(-16, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BD | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG0), SCREEN_MASK_MAIN);
            SetBlendBrightness(-16, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BD | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG0), SCREEN_MASK_SUB);
            Blackout_DrawMessage(fieldSystem, taskManager);
            (*state)++;
            break;
        case 4:
            CallTask_RestoreOverworld(taskManager);
            (*state)++;
            break;
        case 5:
            SetBlendBrightness(0, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BD | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG0), SCREEN_MASK_MAIN | SCREEN_MASK_SUB);
            if (GetMomSpawnId() == LocalFieldData_GetBlackoutSpawn(Save_LocalFieldData_Get(fieldSystem->saveData))) {
                QueueScript(taskManager, 0x7E4, NULL, NULL);
            } else {
                QueueScript(taskManager, 0x7E5, NULL, NULL);
            }
            (*state)++;
            break;
        case 6:
            return TRUE;
    }

    return FALSE;
}

void CallTask_BlackOut(TaskManager *taskManager) {
    TaskManager_Call(taskManager, Task_BlackOut, NULL);
}
