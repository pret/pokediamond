#include "global.h"
#include "bg_window.h"
#include "unk_0200CA44.h"
#include "gf_gfx_loader.h"
#include "overlay_24.h"

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
extern void ov20_022536F4(void*, u32);
extern u32 ov20_02252D34();
extern u32 ov20_02252D24();

BOOL ov24_02254CA0(MemoPadDisplayHandler** arg0, MemoPadDrawState* drawState) {
    MemoPadDisplayHandler* data = AllocFromHeap(HEAP_ID_POKETCH_APP, sizeof(MemoPadDisplayHandler));
    if (data != 0) {
        GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_MAIN));
        ov20_022536F4(&(data->unk8), 0x10);
        GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_MAIN));
        data->drawState = drawState;
        data->config = (BgConfig*)ov20_02252D34();
        data->unk50 = ov20_02252D24();
        GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_MAIN));
        arg0[0] = data;
        return TRUE;
    }
    return FALSE;
}

BOOL ov24_02254D00(MemoPadDisplayHandler* arg0) {
    static const WindowTemplate template = {
        .bgId = GF_BG_LYR_SUB_3,
        .left = 2,
        .top = 2,
        .width = 20,
        .height = 19,
        .palette = 0,
        .baseTile = 12,
    };
    arg0->window = AllocWindows(HEAP_ID_POKETCH_APP, 1);
    if (arg0->window) {
        AddWindow(arg0->config, arg0->window, &template);
        if (sub_0208946C(arg0->drawState->unk16E8, arg0->window->pixelBuffer, 0x2f80) == 0) {
            FillWindowPixelBuffer(arg0->window, MEMO_PAD_PIXEL_TYPE_EMPTY);
        }
        return TRUE;
    }
    return FALSE;
}

void ov24_02254D48(MemoPadDisplayHandler* arg0) {
    if (arg0) {
        GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_MAIN));
        if (arg0->window) {
            sub_02089444(arg0->drawState->unk16E8, arg0->window->pixelBuffer, 0x2f80);
            RemoveWindow(arg0->window);
            FreeToHeap(arg0->window);
        }
        FreeToHeap(arg0);
    }
}

void ov24_02254D8C(MemoPadDisplayHandler* arg0, u32 arg1) {
    // TODO: types
    static const u32 ov24_0225516C[] = {
        0x00, (u32)ov24_02254DDC, 0x00,
        0x01, (u32)ov24_02254EE0, 0x00,
        0x02, (u32)ov24_02254F28, 0x00,
        0x03, (u32)ov24_02254F40, 0x00,
        0x04, (u32)ov24_02255038, 0x00,
        0x05, (u32)ov24_02255050, 0x00,
        0x00, 0x00000000, 0x00,
    };
    ov20_022537E0(ov24_0225516C, arg1, arg0, arg0->drawState, &(arg0->unk8), 2, 8);
}

BOOL ov24_02254DB0(MemoPadDisplayHandler* arg0, u8 arg1) {
    return ov20_02253794(&(arg0->unk8), arg1);
}

BOOL ov24_02254DBC(MemoPadDisplayHandler* arg0) {
    return ov20_022537B8(&(arg0->unk8));
}

void ov24_02254DC8(void* arg0) {
    ov20_02253888(&(((MemoPadDisplayHandler*)ov20_022538A0(arg0))->unk8), arg0);
}

void ov24_02254DDC(void* arg0, void* arg1) {
    static const BgTemplate template_7000 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0,
        .baseTile = 0,
        .size = 1,
        .colorMode = 0,
        .screenBase = GX_BG_SCRBASE_0x7000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = 0,
        .priority = 2,
        .areaOver = 0,
        .dummy = 0,
        .mosaic = 0,
    };
    static const BgTemplate template_7800 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .size = 1,
        .colorMode = 0,
        .screenBase = GX_BG_SCRBASE_0x7800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = 0,
        .priority = 3,
        .areaOver = 0,
        .dummy = 0,
        .mosaic = 0,
    };
    GF_ASSERT(GF_heap_c_dummy_return_true(HEAP_ID_POKETCH_APP));
    GXSDispCnt dispcnt;
    MemoPadDisplayHandler* v0 = ov20_022538A0(arg1);
    InitBgFromTemplate(v0->config, 6, &template_7000, 0);
    InitBgFromTemplate(v0->config, 7, &template_7800, 0);
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
    MemoPadDisplayHandler* v0 = ov20_022538A0(arg1);
    if (v0->drawState->stylusType == STYLUS_TYPE_DRAW) {
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
    MemoPadDisplayHandler* a0 = ov20_022538A0(arg1);
    CopyWindowPixelsToVram_TextMode(a0->window);
    ov24_02254DC8(arg1);
}

void ov24_02254F40(u32 arg0, void* arg1) {
    MemoPadDisplayHandler *v0 = ov20_022538A0(arg1);
    MemoPadDrawState* drawState = v0->drawState;
    if (drawState->stylusType == STYLUS_TYPE_ERASE) {
        int width, height;
        height = 8;
        width = 8;
        int x = drawState->lastModifiedX * 2 - 4;
        int y = drawState->lastModifiedY * 2 - 4;
        if (x < 0) {
            width += x;
            x = 0;
        }
        if (y < 0) {
            height += y;
            y = 0;
        }
        FillWindowPixelRect(v0->window, MEMO_PAD_PIXEL_TYPE_EMPTY, x, y, width, height);
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
        int x = drawState->lastModifiedX * 2;
        int y = drawState->lastModifiedY * 2;
        int a = (x >> 3) + ((y >> 3) * 0x14);
        FillWindowPixelRect(v0->window, MEMO_PAD_PIXEL_TYPE_FILLED, x, y, width, height);
        GXS_LoadBG3Char((u8*)(v0->window->pixelBuffer) + a * 0x20, (a + 0xc) * 0x20, 0x20);
    }
    ov24_02254DC8(arg1);
}

void ov24_02255038(u32 arg0, void* arg1) {
    MemoPadDisplayHandler* v0 = ov20_022538A0(arg1);
    CopyWindowPixelsToVram_TextMode(v0->window);
    ov24_02254DC8(arg1);
}

void ov24_02255050(u32 arg0, void* arg1) {
    MemoPadDisplayHandler* v0 = ov20_022538A0(arg1);
    ov24_022550D4(v0);
    FreeBgTilemapBuffer(v0->config, 6);
    FreeBgTilemapBuffer(v0->config, 7);
    ov24_02254DC8(arg1);
}

void ov24_02255078(MemoPadDisplayHandler* arg0) {
    // TODO: types
    static const u32 ov24_0225514C[2][4] = {
        {
            0xC0000, 0x38000, 0x2000000, 0x0
        },
        {
            0xC0000, 0x88000, 0x2000003, 0x0
        }
    };
    GfGfxLoader_LoadWholePalette(NARC_GRAPHIC_POKETCH, 0x20, 1, 0, 0, 1, HEAP_ID_POKETCH_APP);
    if (ov20_02253FBC(&(arg0->unk54), NARC_GRAPHIC_POKETCH, 0x21, 0x22, HEAP_ID_POKETCH_APP)) {
        for (int i = 0; i < 2; i++) {
            arg0->unk68[i] = ov20_02253E74(arg0->unk50, &(ov24_0225514C[i]), &(arg0->unk54));
        }
    }
}

void ov24_022550D4(MemoPadDisplayHandler* arg0) {
    for (u32 i = 0; i < 2; i++) {
        ov20_02253F14(arg0->unk50, arg0->unk68[i]);
    }
    ov20_02254014(&(arg0->unk54));
}
