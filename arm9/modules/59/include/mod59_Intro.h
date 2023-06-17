#ifndef POKEDIAMOND_MOD59_INTRO_H
#define POKEDIAMOND_MOD59_INTRO_H

#include "nitro/types.h"
#include "options.h"
#include "save.h"
#include "main.h"
#include "player_data.h"
#include "list_menu_items.h"
#include "list_menu.h"

struct MOD59_UnkPlayerStruct
{
    u8 padding[0x4];
    GenderEnum gender;
    u8 padding2[0x10];
    struct String *name;
};

typedef struct MOD59_IntroOverlayData
{
    u32 heap_id;
    struct SaveData *save;
    struct Options *options;
    u32 controllerCounter;
    u32 nextControllerCounter;
    struct OverlayManager *loadedOverlay;
    struct BgConfig *bgConfig;
    struct Window window;
    u32 createListCounter;
    struct Window listWindow;
    struct ListMenu *listMenu;
    struct ListMenuItem *listMenuItem;
    s32 listMenuInput;
    struct MsgData *msgData;
    u32 displayMessageCounter;
    u32 displayControlMessageCounter;
    u32 minTextSpacing;
    struct String *string;
    u32 unk60; // unknown if this is the right type, possibly a pointer instead?
    MessageFormat *messageFormat;
    u32 unk68;
    u8 filler6C[0x4];
    struct MOD59_UnkPlayerStruct *playerStruct;
    struct MOD59_UnkPlayerStruct *rivalStruct;
    u32 fadeCounter;
    fx32 alphaBlend1;
    fx32 alphaBlend2;
    GenderEnum selectedGender;
    u8 scrnDataIndexMain;
    u8 spriteDataIndex0;
    u8 spriteDataIndex1;
    u8 scrnDataIndexSub;
    u8 maleAnimCounter;
    volatile u8 maleAnimTimer;
    u8 femaleAnimCounter;
    volatile u8 femaleAnimTimer;
    s32 tickTimer;
    u32 spriteDataIndex2;
    volatile u32 spriteData2Timer;
    u8 filler9C[0xC];
    s32 unkA8;
    u32 unkAC;
    u32 unkB0;
} MOD59_IntroOverlayData;

struct MOD59_ListStruct021D9E0C
{
    u32 msgNo;
    s32 val;
};

struct MOD59_WindowTemplateGroup
{
    struct WindowTemplate template1;
    struct WindowTemplate template2;
};

struct MOD59_GraphicsPaletteMapSubstruct021D9F90
{
    u32 charNum;
    u32 palNum;
};
struct MOD59_GraphicsPaletteMap021D9F90
{
    struct MOD59_GraphicsPaletteMapSubstruct021D9F90 map[11];
};

struct MOD59_UnkStruct021D9E30
{
    u32 scrnIds[5];
};

struct MOD59_CharStruct021D9DEC
{
    u32 narcId[4];
};

struct MOD59_CharStruct021D9E70
{
    u32 charData[6];
};

BOOL MOD59_IntroInit(struct OverlayManager *overlayManager, u32 *status);
BOOL MOD59_IntroMain(struct OverlayManager *overlayManager, u32 *status);
BOOL MOD59_IntroExit(struct OverlayManager *overlayManager, u32 *status);
void MOD59_IntroDoGpuBgUpdate(MOD59_IntroOverlayData *data);
BOOL MOD59_TestPokeballTouchLocation(void);
void MOD59_IntroSetupBg(MOD59_IntroOverlayData *data);
void MOD59_IntroDestroyBg(MOD59_IntroOverlayData *data);
void MOD59_IntroSetupMsg(MOD59_IntroOverlayData *data);
void MOD59_IntroDestroyMsg(MOD59_IntroOverlayData *data);
void MOD59_021D7A4C(MOD59_IntroOverlayData *data);
void MOD59_021D7A5C(MOD59_IntroOverlayData *data);
BOOL MOD59_FadeController(MOD59_IntroOverlayData *data, u32 param1, u32 param2);
BOOL MOD59_Timer(MOD59_IntroOverlayData *data, s32 timer);
void MOD59_TilemapChangePalette(MOD59_IntroOverlayData *data, u32 layer, u32 paletteNum);
BOOL MOD59_DisplayMessage(MOD59_IntroOverlayData *data, u32 msgNo, BOOL autoAdvance);
void MOD59_PlaySelectSound(struct ListMenu *list, s32 index, u8 onInit);
BOOL MOD59_CreateListWithText(MOD59_IntroOverlayData *data, u32 param1, u32 param2);
BOOL MOD59_DisplayControlAdventureMessage(MOD59_IntroOverlayData *data, u32 msgNo, u32 param2, u32 tilemapTop, u32 height);
void MOD59_LoadInitialTilemap(MOD59_IntroOverlayData *data);
void MOD59_LoadMainScrnData(MOD59_IntroOverlayData *data);
void MOD59_LoadCharDataFromIndex(MOD59_IntroOverlayData *data);
void MOD59_LoadSubScrnData(MOD59_IntroOverlayData *data);
void MOD59_DrawMunchlax(MOD59_IntroOverlayData *data);
void MOD59_LoadPokeballButton(MOD59_IntroOverlayData *data);
BOOL MOD59_MoveSprite(MOD59_IntroOverlayData *data, u32 layer, u32 param2);
void MOD59_ResetPlayerAnimation(MOD59_IntroOverlayData *data);
void MOD59_AnimatePlayerSprite(MOD59_IntroOverlayData *data);
void MOD59_DisableBlend(MOD59_IntroOverlayData *data);
void MOD59_ResetPlayerShrinkAnimation(MOD59_IntroOverlayData *data);
BOOL MOD59_PlayerShrinkAnimation(MOD59_IntroOverlayData *data);
BOOL MOD59_MunchlaxJumpAnimation(MOD59_IntroOverlayData *data, u32 *param1);
void MOD59_ResetMunchlaxPriority(MOD59_IntroOverlayData *data);
BOOL MOD59_MasterController(MOD59_IntroOverlayData *data);

#endif // POKEDIAMOND_MOD59_INTRO_H
