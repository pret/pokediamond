#include "global.h"

#include "FS_overlay.h"
#include "poke_overlay.h"
#include "unk_02031734.h"

FS_EXTERN_OVERLAY(OVERLAY_16);

static void ov11_0222F284(void) {
    if (!sub_02033590()) {
        HandleLoadOverlay(FS_OVERLAY_ID(OVERLAY_16), 2);
    }
}

#define NitroStaticInit ov11_0222F284
#include "sinit.h"
