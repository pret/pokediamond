#ifndef GUARD_POKE_OVERLAY_H
#define GUARD_POKE_OVERLAY_H

#include "FS_overlay.h"

#define OVERLAY_LOAD_WRAM 0
#define OVERLAY_LOAD_ITCM 1
#define OVERLAY_LOAD_DTCM 2

struct LoadedOverlay {
    FSOverlayID id;
    BOOL active;
};

void FreeOverlayAllocation(struct LoadedOverlay * loaded);
void UnloadOverlayByID(FSOverlayID id);
s32 GetOverlayLoadDestination(FSOverlayID id);
BOOL HandleLoadOverlay(FSOverlayID id, s32 a1);
BOOL CanOverlayBeLoaded(FSOverlayID id);
struct LoadedOverlay* GetLoadedOverlaysInRegion(s32 a0);
BOOL GetOverlayRamBounds(FSOverlayID id, void ** start, void ** end);
BOOL LoadOverlayNormal(MIProcessor target, FSOverlayID id);
BOOL LoadOverlayNoInit(MIProcessor target, FSOverlayID id);
BOOL LoadOverlayNoInitAsync(MIProcessor target, FSOverlayID id);

#endif //GUARD_POKE_OVERLAY_H
