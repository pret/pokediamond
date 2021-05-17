#ifndef POKEDIAMOND_OVERLAY_MANAGER_H
#define POKEDIAMOND_OVERLAY_MANAGER_H

#include "nitro/types.h"

struct Unk21DBE18;

struct UnkStruct_02006234 * OverlayManager_new(const struct Unk21DBE18 * ovly_mgr, s32 * a1, u32 heap_id);
void OverlayManager_delete(struct UnkStruct_02006234 * a0);
void * OverlayManager_CreateAndGetData(struct UnkStruct_02006234 * a0, u32 size, u32 heap_id);
void * OverlayManager_GetData(struct UnkStruct_02006234 * a0);
void OverlayManager_FreeData(struct UnkStruct_02006234 * a0);
s32 * OverlayManager_GetField18(struct UnkStruct_02006234 * a0);
BOOL OverlayManager_Run(struct UnkStruct_02006234 * a0);

#endif //POKEDIAMOND_OVERLAY_MANAGER_H
