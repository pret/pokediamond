#include "global.h"
#include "poke_overlay.h"
#include "FS_overlay.h"

extern u32 FUN_02033590(void);
FS_EXTERN_OVERLAY(MODULE_16);

THUMB_FUNC static void MOD11_0222F284(void)
{
    if (!FUN_02033590())
    {
        HandleLoadOverlay(FS_OVERLAY_ID(MODULE_16), 2);
    }
}

#define NitroStaticInit MOD11_0222F284
#include "sinit.h"
