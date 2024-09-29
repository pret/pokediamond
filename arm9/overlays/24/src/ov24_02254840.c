#include "global.h"

#include "bg_window.h"
#include "gf_gfx_loader.h"
#include "overlay_24.h"
#include "unk_0200CA44.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern u32 ov20_02254130(void *arg0, u32 arg1, void *arg2, void *arg3, u32 arg4);
extern void ov20_02254198(u32 arg0);
extern void ov20_02252C14(u32 arg0, u32 arg1);
extern void ov20_022529A0(u32 arg0);
extern void ov20_0225298C(u32 arg0);
extern BOOL ov20_02252C08(u32 arg0);
extern BOOL TouchScreen_GetTapState(u32 *arg0, u32 *arg1);

static void ov24_02254840(void) {
    Poketch_InitApp(ov24_02254854, ov24_02254990);
}

#define NitroStaticInit ov24_02254840
#include "sinit.h"

BOOL ov24_02254854(MemoPadAppHandler **appHandlerOut, s32 arg1, s32 arg2, s32 arg3) {
    MemoPadAppHandler *appHandler = AllocFromHeap(HEAP_ID_POKETCH_APP, sizeof(MemoPadAppHandler));
    if (appHandler != NULL) {
        if (ov24_0225489C(appHandler, arg1, arg2, arg3)) {
            if (SysTask_CreateOnMainQueue((SysTaskFunc)ov24_02254918, appHandler, 1) != NULL) {
                *appHandlerOut = appHandler;
                return TRUE;
            }
        }
        FreeToHeap(appHandler);
    }
    return FALSE;
}

BOOL ov24_0225489C(MemoPadAppHandler *appHandler, u32 arg1, u32 arg2, u32 arg3) {
    static const u8 ov24_022550F8[] = {
        0x18, 0x58, 0xB4, 0xCC, 0x68, 0xA8, 0xB4, 0xCC
    };
    appHandler->drawState.unk16E8   = arg3;
    appHandler->drawState.touchType = TOUCH_TYPE_DRAW;
    if (ov24_02254CA0(&(appHandler->displayHandler), &(appHandler->drawState))) {
        appHandler->unk0      = 0;
        appHandler->unk1      = 0;
        appHandler->unk2      = 0;
        appHandler->touchHeld = FALSE;
        appHandler->unk16FC   = ov20_02254130(ov24_022550F8, 2, ov24_02254960, appHandler, 8);
        appHandler->unk16F8   = arg1;
        return TRUE;
    }
    return FALSE;
}

void ov24_022548F4(MemoPadAppHandler *appHandler) {
    ov20_02254198(appHandler->unk16FC);
    ov24_02254D48(appHandler->displayHandler);
    FreeToHeap(appHandler);
}

void ov24_02254918(void *arg0, MemoPadAppHandler *appHandler) {
    static BOOL (*const ov24_02255100[3])(MemoPadAppHandler *) = {
        ov24_022549AC, ov24_022549F8, ov24_02254C64
    };
    if (appHandler->unk0 < 3) {
        ov20_02252C14(appHandler->unk16F8, appHandler->unk16FC);
        if (ov24_02255100[appHandler->unk0](appHandler)) {
            ov24_022548F4(appHandler);
            sub_0200CAB4((s32)arg0);
            ov20_022529A0(appHandler->unk16F8);
        }
    }
}

void ov24_02254960(s32 arg0, s32 arg1, s32 arg2, MemoPadAppHandler *appHandler) {
    if (arg2 == 1) {
        if (
            (appHandler->drawState.touchType == TOUCH_TYPE_DRAW && arg0 == 0)
            || (appHandler->drawState.touchType == TOUCH_TYPE_ERASE && arg0 == 1)) {
            appHandler->drawState.touchType ^= 1;
            ov24_02254D8C(appHandler->displayHandler, 1);
        }
    }
}

void ov24_02254990(MemoPadAppHandler *appHandler) {
    appHandler->unk2 = 1;
}

void ov24_02254998(MemoPadAppHandler *appHandler, u8 arg1) {
    if (appHandler->unk2 == 0) {
        appHandler->unk0 = arg1;
    } else {
        appHandler->unk0 = 2;
    }
    appHandler->unk1 = 0;
}

BOOL ov24_022549AC(MemoPadAppHandler *appHandler) {
    switch (appHandler->unk1) {
    case 0:
        ov24_02254D8C(appHandler->displayHandler, 0);
        appHandler->unk1++;
        break;
    case 1:
        if (ov24_02254DB0(appHandler->displayHandler, 0)) {
            ov20_0225298C(appHandler->unk16F8);
            ov24_02254998(appHandler, 1);
        }
        break;
    default:
        break;
    }
    return FALSE;
}

BOOL ov24_022549F8(MemoPadAppHandler *appHandler) {
    if (appHandler->unk2 != 0) {
        ov24_02254998(appHandler, 2);
    }
    switch (appHandler->unk1) {
    case 0:
        if (ov20_02252C08(appHandler->unk16F8)) {
            break;
        }
        if (appHandler->touchHeld) {
            u32 x = appHandler->drawState.lastModifiedX;
            u32 y = appHandler->drawState.lastModifiedY;
            if (ov24_02254AD4(appHandler)) {
                ov24_02254B20(appHandler, x, y, appHandler->drawState.lastModifiedX, appHandler->drawState.lastModifiedY);
            } else {
                appHandler->touchHeld = FALSE;
            }
        } else {
            if (ov24_02254A70(appHandler)) {
                ov24_02254D8C(appHandler->displayHandler, 3);
                appHandler->touchHeld = TRUE;
            }
        }
        break;
    }
    return FALSE;
}

BOOL ov24_02254A70(MemoPadAppHandler *appHandler) {
    u32 x, y;
    if (TouchScreen_GetTapState(&x, &y)) {
        if (((x - 16) < 156) & ((y - 16) < 150)) {
            x = (x - 16) >> 1;
            y = (y - 16) >> 1;
            if (appHandler->drawState.pixelData[x][y] != appHandler->drawState.touchType) {
                appHandler->drawState.pixelData[x][y] = appHandler->drawState.touchType;
                appHandler->drawState.lastModifiedX   = x;
                appHandler->drawState.lastModifiedY   = y;
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL ov24_02254AD4(MemoPadAppHandler *appHandler) {
    u32 x, y;
    if (TouchScreen_GetTapState(&x, &y)) {
        if (((x - 16) < 156) & ((y - 16) < 150)) {
            x                                   = (x - 16) >> 1;
            y                                   = (y - 16) >> 1;
            appHandler->drawState.lastModifiedX = x;
            appHandler->drawState.lastModifiedY = y;
            return TRUE;
        }
    }
    return FALSE;
}

void ov24_02254B20(MemoPadAppHandler *appHandler, u32 x0, u32 y0, u32 x1, u32 y1) {
    if (y0 == y1 && x0 == x1) {
        return;
    }
    u32 dx = x1 > x0 ? x1 - x0 : x0 - x1;
    u32 dy = y1 > y0 ? y1 - y0 : y0 - y1;
    s32 direction, offset;
    fx32 f, g;
    if (dx > dy) {
        direction = (x1 > x0) ? 1 : -1;
        if (dx != 0) {
            f = ((y1 - y0) * 0x1000);
            f /= (s32)dx;
        } else {
            f = 0;
        }
        g = (y0 << 12) + f;
        x0 += direction;
        while (x0 != x1) {
            offset = g >> 12;
            if ((x0 < 0x4e) && ((u32)offset < 0x4b)) {
                if (appHandler->drawState.touchType != appHandler->drawState.pixelData[x0][offset]) {
                    appHandler->drawState.pixelData[x0][offset] = appHandler->drawState.touchType;
                    appHandler->drawState.lastModifiedX         = x0;
                    appHandler->drawState.lastModifiedY         = offset;
                    ov24_02254D8C(appHandler->displayHandler, 3);
                }
            }
            x0 += direction;
            g += f;
        }
    } else {
        direction = (y1 > y0) ? 1 : -1;
        if (dy != 0) {
            f = ((x1 - x0) * 0x1000);
            f /= (s32)dy;
        } else {
            f = 0;
        }
        g = (x0 << 12) + f;
        y0 += direction;
        while (y0 != y1) {
            offset = g >> 12;
            if ((y0 < 0x4b) && ((u32)offset < 0x4e)) {
                if (appHandler->drawState.touchType != appHandler->drawState.pixelData[offset][y0]) {
                    appHandler->drawState.pixelData[offset][y0] = appHandler->drawState.touchType;
                    appHandler->drawState.lastModifiedX         = offset;
                    appHandler->drawState.lastModifiedY         = y0;
                    ov24_02254D8C(appHandler->displayHandler, 3);
                }
            }
            y0 += direction;
            g += f;
        }
    }
    if ((y1 < 75) && (x1 < 78)) {
        appHandler->drawState.lastModifiedX = x1;
        appHandler->drawState.lastModifiedY = y1;
        ov24_02254D8C(appHandler->displayHandler, 3);
    }
}

BOOL ov24_02254C64(MemoPadAppHandler *appHandler) {
    switch (appHandler->unk1) {
    case 0:
        ov24_02254D8C(appHandler->displayHandler, 5);
        appHandler->unk1++;
        break;
    case 1:
        if (ov24_02254DBC(appHandler->displayHandler)) {
            return TRUE;
        }
        break;
    }
    return FALSE;
}
