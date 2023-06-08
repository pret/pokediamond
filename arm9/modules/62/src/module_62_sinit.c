#include "global.h"
#include "poke_overlay.h"
#include "FS_overlay.h"

FS_EXTERN_OVERLAY(MODULE_08);

static void MOD62_0222D5C0(void)
{
    HandleLoadOverlay(FS_OVERLAY_ID(MODULE_08), 2);
}

#define NitroStaticInit MOD62_0222D5C0
#include "sinit.h"
