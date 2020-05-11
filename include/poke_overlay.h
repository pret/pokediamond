#ifndef GUARD_POKE_OVERLAY_H
#define GUARD_POKE_OVERLAY_H

#include "FS_overlay.h"

#define OVERLAY_LOAD_WRAM 0
#define OVERLAY_LOAD_ITCM 1
#define OVERLAY_LOAD_DTCM 2

void UnloadOverlayByID(FSOverlayID id);
BOOL HandleLoadOverlay(FSOverlayID id, int a1);

#endif //GUARD_POKE_OVERLAY_H
