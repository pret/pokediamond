#include "global.h"
#include "GX_layers.h"
#include "gx.h"
#include "heap.h"

extern void FUN_020192D4();
extern void FUN_02019358();

extern void FUN_020195D0();
extern void FUN_0201960C();

extern void FUN_020195A8();
extern void FUN_020195E4();

extern void FUN_020194C8();
extern void FUN_0201951C();

extern void FUN_0201949C();
extern void FUN_020194E0();

extern void FUN_020193B4();
extern void FUN_02019444();

const u8 UNK_020EDB30[8] = {
    0x10,
    0x20,
    0x20,
    0x20,
    0x20,
    0x20,
    0x00,
    0x00,
};

void (*const UNK_020EDB5C[])() = {
    FUN_020194C8,
    FUN_0201951C,
    FUN_020194C8,
};

void (*const UNK_020EDB50[])() = {
    FUN_020195A8,
    FUN_020195E4,
    FUN_020195A8,
};

void (*const UNK_020EDB44[])() = {
    FUN_020195D0,
    FUN_0201960C,
    FUN_020195D0,
};

void (*const UNK_020EDB38[])() = {
    FUN_020192D4,
    FUN_02019358,
    FUN_020192D4,
};

void (*const UNK_020EDB68[])() = {
    FUN_0201949C,
    FUN_020194E0,
    FUN_0201949C,
};

void (*const UNK_020EDB74[])() = {
    FUN_020193B4,
    FUN_02019444,
    FUN_020193B4,
};


THUMB_FUNC void *FUN_02016B94(u32 heap_id)
{
    void *ptr = AllocFromHeap(heap_id, 0x5a << 2);
    memset(ptr, 0, 0x5a << 2);
    *(u32 *)ptr = heap_id;
    *(u16 *)(ptr + 4) = 0;
    *(u16 *)(ptr + 6) = 0;

    return ptr;
}

THUMB_FUNC u32 FUN_02016BB8(u32 *param0)
{
    return *param0;
}

THUMB_FUNC void FUN_02016BBC(u32 *param0)
{
    GX_SetGraphicsMode(param0[0], param0[1], param0[3]);
    GXS_SetGraphicsMode(param0[2]);
    reg_GX_DISPCNT &= 0xC7FFFFFF;
    reg_GX_DISPCNT &= 0xF8FFFFFF;

    GX_DisableEngineALayers();
    GX_DisableEngineBLayers();
}

THUMB_FUNC void FUN_02016BF4(u32 *param0, u32 param1)
{
    if (param1 == 0)
    {
        GX_SetGraphicsMode(param0[0], param0[1], param0[3]);
        GX_DisableEngineALayers();
    }
    else
    {
        GXS_SetGraphicsMode(param0[2]);
        GX_DisableEngineBLayers();
    }
}
