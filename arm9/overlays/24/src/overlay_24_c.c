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

// TODO: rodata
extern const FnType02254918 ov24_02255100[3];
extern const u32 ov24_0225514C[2][4];
extern const u32 ov24_0225516C[];
extern const u8 ov24_022550F8[];
extern const WindowTemplate ov24_0225510C;
extern const BgTemplate ov24_02255114;
extern const BgTemplate ov24_02255130;

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

void asm ov24_02254B20(UnkStructOverlay24*, u32, u32, u32, u32) {
    push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [sp, #0x28]
	add r4, r2, #0
	add r6, r1, #0
	str r3, [sp]
	str r0, [sp, #0x28]
	cmp r4, r0
	bne _02254B3C
	add r0, r3, #0
	cmp r6, r0
	bne _02254B3C
	b _02254C5C
_02254B3C:
	ldr r0, [sp]
	cmp r0, r6
	bls _02254B46
	sub r1, r0, r6
	b _02254B48
_02254B46:
	sub r1, r6, r0
_02254B48:
	ldr r0, [sp, #0x28]
	cmp r0, r4
	bls _02254B52
	sub r2, r0, r4
	b _02254B54
_02254B52:
	sub r2, r4, r0
_02254B54:
	cmp r1, r2
	bls _02254BD6
	ldr r0, [sp]
	cmp r0, r6
	bls _02254B64
	mov r0, #1
	str r0, [sp, #4]
	b _02254B6A
_02254B64:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #4]
_02254B6A:
	cmp r1, #0
	beq _02254B7C
	ldr r0, [sp, #0x28]
	sub r0, r0, r4
	lsl r0, r0, #0xc
	bl _s32_div_f
	str r0, [sp, #0x10]
	b _02254B80
_02254B7C:
	mov r0, #0
	str r0, [sp, #0x10]
_02254B80:
	ldr r0, [sp, #0x10]
	lsl r1, r4, #0xc
	add r7, r1, r0
	ldr r0, [sp, #4]
	add r6, r6, r0
	ldr r0, [sp]
	cmp r6, r0
	beq _02254C40
	mov r1, #0x4b
	add r0, r6, #0
	mul r0, r1
	add r4, r5, r0
	ldr r0, [sp, #4]
	mul r1, r0
	str r1, [sp, #0xc]
_02254B9E:
	asr r2, r7, #0xc
	cmp r6, #0x4e
	bhs _02254BC2
	cmp r2, #0x4b
	bhs _02254BC2
	add r1, r4, r2
	ldrb r0, [r1, #0x14]
	ldr r3, [r5, #8]
	cmp r3, r0
	beq _02254BC2
	strb r3, [r1, #0x14]
	str r6, [r5, #0xc]
	ldr r0, =0x000016F4
	str r2, [r5, #0x10]
	ldr r0, [r5, r0]
	mov r1, #3
	bl ov24_02254D8C
_02254BC2:
	ldr r0, [sp, #0xc]
	add r4, r4, r0
	ldr r0, [sp, #4]
	add r6, r6, r0
	ldr r0, [sp, #0x10]
	add r7, r7, r0
	ldr r0, [sp]
	cmp r6, r0
	bne _02254B9E
	b _02254C40
_02254BD6:
	ldr r0, [sp, #0x28]
	cmp r0, r4
	bls _02254BE0
	mov r7, #1
	b _02254BE4
_02254BE0:
	mov r7, #0
	mvn r7, r7
_02254BE4:
	cmp r2, #0
	beq _02254BF8
	ldr r0, [sp]
	add r1, r2, #0
	sub r0, r0, r6
	lsl r0, r0, #0xc
	bl _s32_div_f
	str r0, [sp, #8]
	b _02254BFC
_02254BF8:
	mov r0, #0
	str r0, [sp, #8]
_02254BFC:
	ldr r0, [sp, #8]
	lsl r1, r6, #0xc
	add r6, r1, r0
	ldr r0, [sp, #0x28]
	add r4, r4, r7
	cmp r4, r0
	beq _02254C40
_02254C0A:
	asr r3, r6, #0xc
	cmp r4, #0x4b
	bhs _02254C34
	cmp r3, #0x4e
	bhs _02254C34
	mov r0, #0x4b
	mul r0, r3
	add r0, r5, r0
	add r2, r0, r4
	ldrb r0, [r2, #0x14]
	ldr r1, [r5, #8]
	cmp r1, r0
	beq _02254C34
	strb r1, [r2, #0x14]
	str r3, [r5, #0xc]
	ldr r0, =0x000016F4
	str r4, [r5, #0x10]
	ldr r0, [r5, r0]
	mov r1, #3
	bl ov24_02254D8C
_02254C34:
	ldr r0, [sp, #8]
	add r4, r4, r7
	add r6, r6, r0
	ldr r0, [sp, #0x28]
	cmp r4, r0
	bne _02254C0A
_02254C40:
	ldr r0, [sp, #0x28]
	cmp r0, #0x4b
	bhs _02254C5C
	ldr r0, [sp]
	cmp r0, #0x4e
	bhs _02254C5C
	str r0, [r5, #0xc]
	ldr r0, [sp, #0x28]
	mov r1, #3
	str r0, [r5, #0x10]
	ldr r0, =0x000016F4
	ldr r0, [r5, r0]
	bl ov24_02254D8C
_02254C5C:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
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