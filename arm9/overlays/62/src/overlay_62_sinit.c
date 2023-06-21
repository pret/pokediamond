#include "global.h"
#include "poke_overlay.h"
#include "FS_overlay.h"

FS_EXTERN_OVERLAY(OVERLAY_08);

static void ov62_0222D5C0(void)
{
    HandleLoadOverlay(FS_OVERLAY_ID(OVERLAY_08), 2);
}

#define NitroStaticInit ov62_0222D5C0
#include "sinit.h"
