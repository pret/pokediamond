#ifndef POKEDIAMOND_ov59_INTRO_H
#define POKEDIAMOND_ov59_INTRO_H

#include "nitro/types.h"
#include "heap.h"
#include "options.h"
#include "save.h"
#include "main.h"
#include "player_data.h"
#include "list_menu_items.h"
#include "list_menu.h"

struct ov59_UnkPlayerStruct
{
    u8 padding[0x4];
    PlayerGender gender;
    u8 padding2[0x10];
    struct String *name;
};

typedef struct ov59_IntroOverlayData
{
    HeapID heapId;
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
    struct ov59_UnkPlayerStruct *playerStruct;
    struct ov59_UnkPlayerStruct *rivalStruct;
    u32 fadeCounter;
    fx32 alphaBlend1;
    fx32 alphaBlend2;
    PlayerGender selectedGender;
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
} ov59_IntroOverlayData;

struct ov59_ListStruct021D9E0C
{
    u32 msgNo;
    s32 val;
};

struct ov59_WindowTemplateGroup
{
    struct WindowTemplate template1;
    struct WindowTemplate template2;
};

struct ov59_GraphicsPaletteMapSubstruct021D9F90
{
    u32 charNum;
    u32 palNum;
};
struct ov59_GraphicsPaletteMap021D9F90
{
    struct ov59_GraphicsPaletteMapSubstruct021D9F90 map[11];
};

struct ov59_UnkStruct021D9E30
{
    u32 scrnIds[5];
};

struct ov59_CharStruct021D9DEC
{
    u32 narcId[4];
};

struct ov59_CharStruct021D9E70
{
    u32 charData[6];
};

BOOL ov59_IntroInit(struct OverlayManager *overlayManager, u32 *status);
BOOL ov59_IntroMain(struct OverlayManager *overlayManager, u32 *status);
BOOL ov59_IntroExit(struct OverlayManager *overlayManager, u32 *status);
void ov59_IntroDoGpuBgUpdate(ov59_IntroOverlayData *data);
BOOL ov59_TestPokeballTouchLocation(void);
void ov59_IntroSetupBg(ov59_IntroOverlayData *data);
void ov59_IntroDestroyBg(ov59_IntroOverlayData *data);
void ov59_IntroSetupMsg(ov59_IntroOverlayData *data);
void ov59_IntroDestroyMsg(ov59_IntroOverlayData *data);
void ov59_021D7A4C(ov59_IntroOverlayData *data);
void ov59_021D7A5C(ov59_IntroOverlayData *data);
BOOL ov59_FadeController(ov59_IntroOverlayData *data, u32 param1, u32 param2);
BOOL ov59_Timer(ov59_IntroOverlayData *data, s32 timer);
void ov59_TilemapChangePalette(ov59_IntroOverlayData *data, u32 layer, u32 paletteNum);
BOOL ov59_DisplayMessage(ov59_IntroOverlayData *data, u32 msgNo, BOOL autoAdvance);
void ov59_PlaySelectSound(struct ListMenu *list, s32 index, u8 onInit);
BOOL ov59_CreateListWithText(ov59_IntroOverlayData *data, u32 param1, u32 param2);
BOOL ov59_DisplayControlAdventureMessage(ov59_IntroOverlayData *data, u32 msgNo, u32 param2, u32 tilemapTop, u32 height);
void ov59_LoadInitialTilemap(ov59_IntroOverlayData *data);
void ov59_LoadMainScrnData(ov59_IntroOverlayData *data);
void ov59_LoadCharDataFromIndex(ov59_IntroOverlayData *data);
void ov59_LoadSubScrnData(ov59_IntroOverlayData *data);
void ov59_DrawMunchlax(ov59_IntroOverlayData *data);
void ov59_LoadPokeballButton(ov59_IntroOverlayData *data);
BOOL ov59_MoveSprite(ov59_IntroOverlayData *data, enum GFBgLayer layer, u32 param2);
void ov59_ResetPlayerAnimation(ov59_IntroOverlayData *data);
void ov59_AnimatePlayerSprite(ov59_IntroOverlayData *data);
void ov59_DisableBlend(ov59_IntroOverlayData *data);
void ov59_ResetPlayerShrinkAnimation(ov59_IntroOverlayData *data);
BOOL ov59_PlayerShrinkAnimation(ov59_IntroOverlayData *data);
BOOL ov59_MunchlaxJumpAnimation(ov59_IntroOverlayData *data, u32 *param1);
void ov59_ResetMunchlaxPriority(ov59_IntroOverlayData *data);
BOOL ov59_MasterController(ov59_IntroOverlayData *data);

#endif // POKEDIAMOND_ov59_INTRO_H
