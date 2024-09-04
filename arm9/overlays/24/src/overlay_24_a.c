#include "global.h"
#include "bg_window.h"
#include "unk_0200CA44.h"
#include "gf_gfx_loader.h"
#include "overlay_24.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern u32 ov20_02254130(void *, u32, void *, void*, u32);
extern void ov20_02254198(u32);
extern void ov20_02252C14(u32, u32);
extern void ov20_022529A0(u32);
extern void ov20_0225298C(u32);
extern BOOL ov20_02252C08(u32);
extern BOOL TouchScreen_GetTapState(u32*, u32*);
extern _s32_div_f(void);
extern void ov20_022536F4(void*, u32);
extern u32 ov20_02252D34();
extern u32 ov20_02252D24();
extern BOOL sub_0208946C(u32, void*, u32);
extern void sub_02089444(u32, void*, u32);
extern void ov20_02252D7C(u32, u32);
extern void ov20_02253F28(u32*, u32);
extern void Poketch_PlaySoundEffect(u32);
extern void* ov20_022538A0(void*);
extern void ov20_02253888(u32*, void*);
extern BOOL ov20_022537B8(void*);
extern BOOL ov20_02253794(void*, u8);
extern void ov20_022537E0(const u32*, u32, void*, void*, void*, u32, u32);
extern BOOL ov20_02253FBC(void*, NarcId, u32, u32, HeapID);
extern u32* ov20_02253E74(u32, void*, void*);
extern void ov20_02254014(void*);
extern void ov20_02253F14(u32, void*);

extern const WindowTemplate ov24_0225510C;
extern const BgTemplate ov24_02255114;
extern const BgTemplate ov24_02255130;
extern const u32 ov24_0225514C[2][4];
extern const u32 ov24_0225516C[];

static void ov24_02254840(void)
{
    Poketch_InitApp(ov24_02254854, ov24_02254990);
}

#define NitroStaticInit ov24_02254840
#include "sinit.h"

BOOL ov24_02254854(UnkStructOverlay24** arg0, int arg1, int arg2, int arg3) {
    UnkStructOverlay24* data = AllocFromHeap(HEAP_ID_POKETCH_APP, sizeof(UnkStructOverlay24));
    if (data != 0) {
        if (ov24_0225489C(data, arg1, arg2, arg3) != 0) {
            if (SysTask_CreateOnMainQueue((SysTaskFunc)ov24_02254918, data, 1) != 0) {
                *arg0 = data;
                return TRUE;
            }
        }
        FreeToHeap(data);
    }
    return FALSE;
}

BOOL ov24_0225489C(UnkStructOverlay24* arg0, u32 arg1, u32 arg2, u32 arg3) {
    static const u8 ov24_022550F8[] = {
        0x18, 0x58, 0xB4, 0xCC, 0x68, 0xA8, 0xB4, 0xCC
    };
    arg0->unk8.unk16E8 = arg3;
    arg0->unk8.unk0 = 1;
    if (ov24_02254CA0(&(arg0->unk16F4), &(arg0->unk8))) {
        arg0->unk0 = 0;
        arg0->unk1 = 0;
        arg0->unk2 = 0;
        arg0->unk3 = 0;
        arg0->unk16FC = ov20_02254130(ov24_022550F8, 2, ov24_02254960, arg0, 8);
        arg0->unk16F8 = arg1;
        return TRUE;
    }
    return FALSE;
}

void ov24_022548F4(UnkStructOverlay24* arg0) {
    ov20_02254198(arg0->unk16FC);
    ov24_02254D48(arg0->unk16F4);
    FreeToHeap(arg0);
}

void ov24_02254918(void* arg0, UnkStructOverlay24* arg1) {
    static BOOL (*const ov24_02255100[3])(UnkStructOverlay24*) = {
        ov24_022549AC, ov24_022549F8, ov24_02254C64
    };
    if (arg1->unk0 < 3) {
        ov20_02252C14(arg1->unk16F8, arg1->unk16FC);
        if (ov24_02255100[arg1->unk0](arg1)) {
            ov24_022548F4(arg1);
            sub_0200CAB4((s32)arg0);
            ov20_022529A0(arg1->unk16F8);
        }
    }
}

void ov24_02254960(int arg0, int arg1, int arg2, UnkStructOverlay24* arg3) {
    if (arg2 == 1) {
        if ((arg3->unk8.unk0 == 1 && arg0 == 0) || (arg3->unk8.unk0 == 0 && arg0 == 1)) {
            arg3->unk8.unk0 ^= 1;
            ov24_02254D8C(arg3->unk16F4, 1);
        }
    }
}

void ov24_02254990(UnkStructOverlay24* arg0) {
    arg0->unk2 = 1;
}

void ov24_02254998(UnkStructOverlay24* arg0, u8 arg1) {
    if (arg0->unk2 == 0) {
        arg0->unk0 = arg1;
    }
    else {
        arg0->unk0 = 2;
    }
    arg0->unk1 = 0;
}

BOOL ov24_022549AC(UnkStructOverlay24* arg0) {
    switch (arg0->unk1) {
        case 0:
            ov24_02254D8C(arg0->unk16F4, 0);
            arg0->unk1++;
            break;
        case 1:
            if (ov24_02254DB0(arg0->unk16F4, 0)) {
                ov20_0225298C(arg0->unk16F8);
                ov24_02254998(arg0, 1);
            }
            break;
        default:
            break;
    }
    return FALSE;
}

BOOL ov24_022549F8(UnkStructOverlay24* arg0) {
    if (arg0->unk2 != 0) {
        ov24_02254998(arg0, 2);
    }
    switch (arg0->unk1) {
    case 0:
        if (ov20_02252C08(arg0->unk16F8)) {
            break;
        }
        if (arg0->unk3) {
            u32 x = arg0->unk8.lastModifiedX;
            u32 y = arg0->unk8.lastModifiedY;
            if (ov24_02254AD4(arg0)) {
                ov24_02254B20(arg0, x, y, arg0->unk8.lastModifiedX, arg0->unk8.lastModifiedY);
            } else {
                arg0->unk3 = 0;
            }
        } else {
            if (ov24_02254A70(arg0)) {
                ov24_02254D8C(arg0->unk16F4, 3);
                arg0->unk3 = 1;
            }
        }
        break;
    }
    return FALSE;
}

BOOL ov24_02254A70(UnkStructOverlay24* arg0) {
    u32 x, y;
    if (TouchScreen_GetTapState(&x, &y)) {
        if (((x - 16) < 156) & ((y - 16) < 150)) {
            x = (x - 16) >> 1;
            y = (y - 16) >> 1;
            if (arg0->unk8.pixelData[x][y] != arg0->unk8.unk0) {
                arg0->unk8.pixelData[x][y] = arg0->unk8.unk0;
                arg0->unk8.lastModifiedX = x;
                arg0->unk8.lastModifiedY = y;
                return TRUE;
            }
         }
    }
    return FALSE;
}

BOOL ov24_02254AD4(UnkStructOverlay24* arg0) {
    u32 x, y;
    if (TouchScreen_GetTapState(&x, &y)) {
        if (((x - 16) < 156) & ((y - 16) < 150)) {
            x = (x - 16) >> 1;
            y = (y - 16) >> 1;
            arg0->unk8.lastModifiedX = x;
            arg0->unk8.lastModifiedY = y;
            return TRUE;
        }
    }
    return FALSE;
}

void ov24_02254B20(UnkStructOverlay24* arg0, u32 x0, u32 y0, u32 x1, u32 y1) {
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
                if (arg0->unk8.unk0 != arg0->unk8.pixelData[x0][offset]) {
                    arg0->unk8.pixelData[x0][offset] = arg0->unk8.unk0;
                    arg0->unk8.lastModifiedX = x0;
                    arg0->unk8.lastModifiedY = offset;
                    ov24_02254D8C(arg0->unk16F4, 3);
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
                if (arg0->unk8.unk0 != arg0->unk8.pixelData[offset][y0]) {
                    arg0->unk8.pixelData[offset][y0] = arg0->unk8.unk0;
                    arg0->unk8.lastModifiedX = offset;
                    arg0->unk8.lastModifiedY = y0;
                    ov24_02254D8C(arg0->unk16F4, 3);
                }
            }
            y0 += direction;
            g += f;
        }
    }
    if ((y1 < 75) && (x1 < 78)) {
        arg0->unk8.lastModifiedX = x1;
        arg0->unk8.lastModifiedY = y1;
        ov24_02254D8C(arg0->unk16F4, 3);
    }
}

BOOL ov24_02254C64(UnkStructOverlay24* arg0) {
    switch (arg0->unk1) {
    case 0:
        ov24_02254D8C(arg0->unk16F4, 5);
        arg0->unk1++;
        break;
    case 1:
        if (ov24_02254DBC(arg0->unk16F4)) {
            return TRUE;
        }
        break;
    }
    return FALSE;
}

BOOL ov24_02254CA0(UnkSubStructOverlay24** arg0, UnkSubStructOverlay24_1* arg1) {
    UnkSubStructOverlay24* data = AllocFromHeap(HEAP_ID_POKETCH_APP, sizeof(UnkSubStructOverlay24));
    if (data != 0) {
        GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_MAIN));
        ov20_022536F4(&(data->unk8), 0x10);
        GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_MAIN));
        data->unk0 = arg1;
        data->config = (BgConfig*)ov20_02252D34();
        data->unk50 = ov20_02252D24();
        GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_MAIN));
        arg0[0] = data;
        return TRUE;
    }
    return FALSE;
}

BOOL ov24_02254D00(UnkSubStructOverlay24* arg0) {
    arg0->window = AllocWindows(HEAP_ID_POKETCH_APP, 1);
    if (arg0->window) {
        AddWindow(arg0->config, arg0->window, &ov24_0225510C);
        if (sub_0208946C(arg0->unk0->unk16E8, arg0->window->pixelBuffer, 0x2f80) == 0) {
            FillWindowPixelBuffer(arg0->window, 4);
        }
        return TRUE;
    }
    return FALSE;
}

void ov24_02254D48(UnkSubStructOverlay24* arg0) {
    if (arg0) {
        GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_MAIN));
        if (arg0->window) {
            sub_02089444(arg0->unk0->unk16E8, arg0->window->pixelBuffer, 0x2f80);
            RemoveWindow(arg0->window);
            FreeToHeap(arg0->window);
        }
        FreeToHeap(arg0);
    }
}

void ov24_02254D8C(UnkSubStructOverlay24* arg0, u32 arg1) {
    ov20_022537E0(ov24_0225516C, arg1, arg0, arg0->unk0, &(arg0->unk8), 2, 8);
}

BOOL ov24_02254DB0(UnkSubStructOverlay24* arg0, u8 arg1) {
    return (*ov20_02253794)(&(arg0->unk8), arg1);
}

BOOL ov24_02254DBC(UnkSubStructOverlay24* arg0) {
    return (*ov20_022537B8)(&(arg0->unk8));
}

void ov24_02254DC8(void* arg0) {
    ov20_02253888(&(((UnkSubStructOverlay24*)ov20_022538A0(arg0))->unk8), arg0);
}

void ov24_02254DDC(void* arg0, void* arg1) {
    GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_APP));
    GXSDispCnt dispcnt;
    UnkSubStructOverlay24* v0 = ov20_022538A0(arg1);
    InitBgFromTemplate(v0->config, 6, &ov24_02255114, 0);
    InitBgFromTemplate(v0->config, 7, &ov24_02255130, 0);
    GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_APP));   
    GfGfxLoader_LoadCharData(NARC_GRAPHIC_POKETCH,0x1e,v0->config,6,0,0,1,HEAP_ID_POKETCH_APP);
    GfGfxLoader_LoadScrnData(NARC_GRAPHIC_POKETCH,0x1f,v0->config,6,0,0,1,HEAP_ID_POKETCH_APP);
    ov20_02252D7C(0,0);
    GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_APP));
    ov24_02254D00(v0);
    CopyWindowToVram(v0->window);
    GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_APP));
    ov24_02255078(v0);
    GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_APP));
    BgCommitTilemapBufferToVram(v0->config, 7);
    dispcnt.raw = reg_GXS_DB_DISPCNT;
    GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    ov24_02254DC8(arg1);
    GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_APP));
}

void ov24_02254EE0(u32 arg0, void* arg1) {
    UnkSubStructOverlay24* v0 = ov20_022538A0(arg1);
    if (v0->unk0->unk0 == 1) {
        ov20_02253F28(v0->unk68[0], 0);
        ov20_02253F28(v0->unk68[1], 3);
    } else {
        ov20_02253F28(v0->unk68[0], 1);
        ov20_02253F28(v0->unk68[1], 2);
    }
    Poketch_PlaySoundEffect(1635);
    ov24_02254DC8(arg1);
}

void ov24_02254F28(int arg0, void* arg1) {
    UnkSubStructOverlay24* a0 = ov20_022538A0(arg1);
    CopyWindowPixelsToVram_TextMode(a0->window);
    ov24_02254DC8(arg1);
}

void ov24_02254F40(u32 arg0, void* arg1) {
    UnkSubStructOverlay24 *v0 = ov20_022538A0(arg1);
    UnkSubStructOverlay24_1* v1 = v0->unk0;
    if (v1->unk0 == 0) {
        int width, height;
        height = 8;
        width = 8;
        int x = v1->lastModifiedX * 2 - 4;
        int y = v1->lastModifiedY * 2 - 4;
        if (x < 0) {
            width += x;
            x = 0;
        }
        if (y < 0) {
            height += y;
            y = 0;
        }
        FillWindowPixelRect(v0->window, 4, x, y, width, height);
        int a = (x >> 3) + (y >> 3) * 0x14;
        int e = ((x + width - 1) >> 3) - (x >> 3) + 1;
        int b = ((y + height - 1) >> 3) - (y >> 3) + 1;
        while (b--) {
            GXS_LoadBG3Char((u8*)(v0->window->pixelBuffer) + (a * 0x20), (a + 0xc) * 0x20, e * 0x20);
            a += 0x14;
        }
    } else {
        int height = 2;
        int width = 2;
        int x = v1->lastModifiedX * 2;
        int y = v1->lastModifiedY * 2;
        int a = (x >> 3) + ((y >> 3) * 0x14);
        FillWindowPixelRect(v0->window, 1, x, y, width, height);
        GXS_LoadBG3Char((u8*)(v0->window->pixelBuffer) + a * 0x20, (a + 0xc) * 0x20, 0x20);
    }
    ov24_02254DC8(arg1);
}

void ov24_02255038(u32 arg0, void* arg1) {
    UnkSubStructOverlay24* v0 = ov20_022538A0(arg1);
    CopyWindowPixelsToVram_TextMode(v0->window);
    ov24_02254DC8(arg1);
}

void ov24_02255050(u32 arg0, void* arg1) {
    UnkSubStructOverlay24* v0 = ov20_022538A0(arg1);
    ov24_022550D4(v0);
    FreeBgTilemapBuffer(v0->config, 6);
    FreeBgTilemapBuffer(v0->config, 7);
    ov24_02254DC8(arg1);
}

void ov24_02255078(UnkSubStructOverlay24* arg0) {
    GfGfxLoader_LoadWholePalette(NARC_GRAPHIC_POKETCH, 0x20, 1, 0, 0, 1, HEAP_ID_POKETCH_APP);
    if (ov20_02253FBC(&(arg0->unk54), NARC_GRAPHIC_POKETCH, 0x21, 0x22, HEAP_ID_POKETCH_APP)) {
        for (int i = 0; i < 2; i++) {
            arg0->unk68[i] = ov20_02253E74(arg0->unk50, &(ov24_0225514C[i]), &(arg0->unk54));
        }
    }
}

void ov24_022550D4(UnkSubStructOverlay24* arg0) {
    for (u32 i = 0; i < 2; i++) {
        ov20_02253F14(arg0->unk50, arg0->unk68[i]);
    }
    ov20_02254014(&(arg0->unk54));
}