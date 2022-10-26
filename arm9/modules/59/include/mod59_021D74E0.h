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
    u32 unk0C;
    u32 unk10;
    struct UnkStruct_02006234 *unk14;
    struct BgConfig *bgConfig;
    struct Window window;
    u32 unk2C;
    struct Window window2; // why are there two of these
    struct ListMenu *listMenu;
    struct ListMenuItem *listMenuItem;
    s32 listMenuInput;
    struct MsgData *msgData;
    u32 unk50;
    u32 unk54;
    u32 minTextSpacing;
    struct String *string;
    u32 unk60; // unknown if this is the right type, possibly a pointer instead?
    struct ScrStrBufs *strBufs;
    u32 unk68;
    u8 filler6C[0x4];
    struct MOD59_UnkPlayerStruct *playerStruct;
    struct MOD59_UnkPlayerStruct *rivalStruct;
    u32 unk78;
    u32 unk7C;
    u32 unk80;
    u32 unk84;
    u8 unk88;
    u8 unk89;
    u8 unk8A;
    u8 unk8B;
    u8 filler8C[4];
    s32 unk90;
    u8 filler94[32];
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

BOOL MOD59_Init(struct UnkStruct_02006234 *param0);
BOOL MOD59_021D7564(struct UnkStruct_02006234 *param0, u32 *param1);
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
BOOL MOD59_021D7BEC(MOD59_OverlayData *data, s32 param1);
void MOD59_TilemapChangePalette(MOD59_OverlayData *data, u32 bgId, u32 paletteNum);
BOOL MOD59_021D7C44(MOD59_OverlayData *data, u32 msgNo, u32 param2);
void MOD59_021D7D68(struct ListMenu *list, s32 index, u8 onInit);
BOOL MOD59_021D7D7C(MOD59_OverlayData *data, u32 param1, u32 param2, u32 param3);

#endif //POKEDIAMOND_MOD59_021D74E0_H
