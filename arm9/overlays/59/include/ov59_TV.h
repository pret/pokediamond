#ifndef POKEDIAMOND_ov59_TV_H
#define POKEDIAMOND_ov59_TV_H

#include "nitro/types.h"
#include "main.h"
#include "bg_window.h"
#include "msgdata.h"

typedef struct ov59_TVOverlayData2
{
    u32 heap_id;
    struct BgConfig *bgConfig;
    struct MsgData *msgData;
    u32 unk0C;
    struct Window window;
    s32 unk20;
    u32 unk24;
} ov59_TVOverlayData;

BOOL ov59_TVInit(struct OverlayManager *overlayManager, u32 *status);
BOOL ov59_TVMain(struct OverlayManager *overlayManager, u32 *status);
BOOL ov59_TVExit(struct OverlayManager *overlayManager, u32 *status);
void ov59_TVDoGpuBgUpdate(ov59_TVOverlayData *data);
void ov59_TVSetupGraphics(ov59_TVOverlayData *data);
void ov59_TVDestroyGraphics(ov59_TVOverlayData *data);
void ov59_TVSetupMsg(ov59_TVOverlayData *data);
void ov59_TVDestroyMsg(ov59_TVOverlayData *data);
BOOL ov59_021D9C74(ov59_TVOverlayData *data, u32 msgNo, u32 param2, u32 param3);
void ov59_021D9D78(ov59_TVOverlayData *data);

#endif // POKEDIAMOND_ov59_TV_H
