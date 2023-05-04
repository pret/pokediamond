#ifndef POKEDIAMOND_MOD59_TV_H
#define POKEDIAMOND_MOD59_TV_H

#include "nitro/types.h"
#include "main.h"
#include "bg_window.h"
#include "msgdata.h"

typedef struct MOD59_TVOverlayData2
{
    u32 heap_id;
    struct BgConfig *bgConfig;
    struct MsgData *msgData;
    u32 unk0C;
    struct Window window;
    s32 unk20;
    u32 unk24;
} MOD59_TVOverlayData;

BOOL MOD59_TVInit(struct UnkStruct_02006234 *param0, u32 *param1);
BOOL MOD59_TVMain(struct UnkStruct_02006234 *overlayStruct, u32 *param1);
BOOL MOD59_TVExit(struct UnkStruct_02006234 *overlayStruct, u32 *param1);
void MOD59_TVDoGpuBgUpdate(MOD59_TVOverlayData *data);
void MOD59_TVSetupGraphics(MOD59_TVOverlayData *data);
void MOD59_TVDestroyGraphics(MOD59_TVOverlayData *data);
void MOD59_TVSetupMsg(MOD59_TVOverlayData *data);
void MOD59_TVDestroyMsg(MOD59_TVOverlayData *data);
BOOL MOD59_021D9C74(MOD59_TVOverlayData *data, u32 msgNo, u32 param2, u32 param3);
void MOD59_021D9D78(MOD59_TVOverlayData *data);

#endif // POKEDIAMOND_MOD59_TV_H
