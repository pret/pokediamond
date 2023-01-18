#ifndef POKEDIAMOND_MOD59_021D74E0_H
#define POKEDIAMOND_MOD59_021D74E0_H

#include "nitro/types.h"
#include "options.h"
#include "save_block_2.h"
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

typedef struct MOD59_OverlayData
{
    u32 heap_id;
    struct SaveBlock2 *sav2;
    struct Options *options;
    u32 controllerCounter;
    u32 nextControllerCounter;
    struct UnkStruct_02006234 *loadedOverlay;
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
    struct ScrStrBufs *strBufs;
    u32 unk68;
    u8 filler6C[0x4];
    struct MOD59_UnkPlayerStruct *playerStruct;
    struct MOD59_UnkPlayerStruct *rivalStruct;
    u32 fadeCounter;
    u32 unk7C;
    u32 unk80;
    GenderEnum selectedGender;
    u8 scrnDataIndex0;
    u8 spriteDataIndex0;
    u8 spriteDataIndex1;
    u8 scrnDataIndex1;
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
} MOD59_OverlayData;

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

BOOL MOD59_Init(struct UnkStruct_02006234 *param0);
BOOL MOD59_Main(struct UnkStruct_02006234 *param0, u32 *overlayStruct);
BOOL MOD59_021D76C0(struct UnkStruct_02006234 *param0);
void MOD59_021D7724(MOD59_OverlayData *data);
BOOL MOD59_021D7730(void);
void MOD59_SetupBg(MOD59_OverlayData *data);
void MOD59_DestroyBg(MOD59_OverlayData *data);
void MOD59_SetupMsg(MOD59_OverlayData *data);
void MOD59_DestroyMsg(MOD59_OverlayData *data);
void MOD59_021D7A4C(MOD59_OverlayData *data);
void MOD59_021D7A5C(MOD59_OverlayData *data);
BOOL MOD59_021D7A68(MOD59_OverlayData *data, u32 param1, u32 param2);
BOOL MOD59_021D7BEC(MOD59_OverlayData *data, s32 timer);
void MOD59_TilemapChangePalette(MOD59_OverlayData *data, u32 layer, u32 paletteNum);
BOOL MOD59_DisplayMessage(MOD59_OverlayData *data, u32 msgNo, u32 param2);
void MOD59_021D7D68(struct ListMenu *list, s32 index, u8 onInit);
BOOL MOD59_CreateListWithText(MOD59_OverlayData *data, u32 param1, u32 param2);
BOOL MOD59_DisplayControlAdventureMessage(MOD59_OverlayData *data, u32 msgNo, u32 param2, u32 tilemapTop, u32 height);
void MOD59_021D8058(MOD59_OverlayData *data);
void MOD59_021D80FC(MOD59_OverlayData *data);
void MOD59_021D8140(MOD59_OverlayData *data);
void MOD59_021D8234(MOD59_OverlayData *data);
void MOD59_021D82A0(MOD59_OverlayData *data);
void MOD59_021D83F8(MOD59_OverlayData *data);
BOOL MOD59_021D8460(MOD59_OverlayData *data, u32 layer, u32 param2);
void MOD59_021D84E8(MOD59_OverlayData *data);
void MOD59_021D8504(MOD59_OverlayData *data);
void MOD59_DisableBlend(MOD59_OverlayData *data);
void MOD59_021D8624(MOD59_OverlayData *data);
BOOL MOD59_021D8634(MOD59_OverlayData *data);
BOOL MOD59_021D86BC(MOD59_OverlayData *data, u32 *param1);
void MOD59_021D8914(MOD59_OverlayData *data);
BOOL MOD59_MasterController(MOD59_OverlayData *data);

#endif //POKEDIAMOND_MOD59_021D74E0_H
