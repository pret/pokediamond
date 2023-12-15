#include "blackout.h"
#include "bg_window.h"
#include "constants/maps.h"
#include "constants/rgb.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/narc_0328.h"
#include "graphic/font.naix"
#include "gf_gfx_loader.h"
#include "PAD_pad.h"
#include "render_window.h"

static void Blackout_InitDisplays(BgConfig *bgConfig);
/*static*/ void Blackout_DrawMessage(FieldSystem *fieldSystem, TaskManager *taskManager);
static BOOL Task_ShowPrintedBlackoutMessage(TaskManager *taskManager);

extern void sub_020482F4(BlackoutScreenEnvironment *environment, s32 msgNo, u8 x, u8 y);
extern void BeginNormalPaletteFade(u32 pattern, u32 typeTop, u32 typeBottom, u16 colour, u32 duration, u32 framesPer, HeapID heapId);
extern BOOL IsPaletteFadeFinished(void);

extern SaveData *FieldSystem_GetSaveData(FieldSystem *fieldSystem);

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
    GfGfxLoader_GXLoadPal(NARC_GRAPHIC_FONT, NARC_font_narc_0006_NCLR, GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_OFFSET_13, 0x20, HEAP_ID_FIELD);
}

/*static*/ void Blackout_DrawMessage(FieldSystem *fieldSystem, TaskManager *taskManager) {
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
        sub_020482F4(env, narc_0328_00004, 0, 0);
    } else {
        // {STRVAR_1 3, 0} scurried to\na Pokémon Center, protecting\nthe exhausted and fainted\nPokémon from further harm...
        sub_020482F4(env, narc_0328_00003, 0, 0);
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
