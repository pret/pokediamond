#include "unk_02016B94.h"

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


extern u8 FUN_020177DC(u8 param0, u32 param1);
extern void FUN_020179E0(u32 param0, u32 param1, u32 param2, u32 val);

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


#ifdef NONMATCHING
THUMB_FUNC void FUN_02016C18(struct UnkStruct2 *param0, u8 param1, struct UnkStruct1 *param2, u8 param3)
{
    u8 res = FUN_020177DC(param2->unk10, param3);
    switch (param1)
    {
    case 0:
        GX_EngineAToggleLayers(1, GX_LAYER_TOGGLE_ON);

        reg_G2_BG0CNT = (reg_G2_BG0CNT & 0x43) |
                        (res << 14) | (param2->unk12 << 8) | (param2->unk11 << 7) | (param2->unk14 << 13) | (param2->unk13 << 2);
        reg_G2_BG0CNT = (reg_G2_BG0CNT & ~3) | (param2->unk15);

        if (param2->unk18 != 0)
        {
            reg_G2_BG0CNT |= 0x40;
        }
        else
        {
            reg_G2_BG0CNT &= ~0x40;
        }

        break;

    case 1:
        GX_EngineAToggleLayers(2, GX_LAYER_TOGGLE_ON);
        reg_G2_BG1CNT = (reg_G2_BG1CNT & 0x43) |
                        (res << 14) | (param2->unk12 << 8) | (param2->unk11 << 7) | (param2->unk14 << 13) | (param2->unk13 << 2);
        reg_G2_BG1CNT = (reg_G2_BG1CNT & ~3) | (param2->unk15);

        if (param2->unk18 != 0)
        {
            reg_G2_BG1CNT |= 0x40;
        }
        else
        {
            reg_G2_BG1CNT &= ~0x40;
        }

        break;

    case 2:
        GX_EngineAToggleLayers(4, GX_LAYER_TOGGLE_ON);
        switch (param3)
        {
        default:
        case 0:
            reg_G2_BG2CNT = (reg_G2_BG2CNT & 0x43) |
                            (res << 14) | (param2->unk12 << 8) | (param2->unk11 << 7) | (param2->unk13 << 2);
            break;
        case 1:
            reg_G2_BG2CNT = (reg_G2_BG2CNT & 0x43) |
                            (res << 14) | (param2->unk12 << 8) | (param2->unk16 << 13) | (param2->unk13 << 2);
            break;
        case 2:
            reg_G2_BG2CNT = (reg_G2_BG2CNT & 0x43) |
                            (res << 14) | (param2->unk12 << 8) | (param2->unk16 << 13) |  (param2->unk13 << 2);
            break;
        }

        reg_G2_BG2CNT = (reg_G2_BG2CNT & ~3) | (param2->unk15);

        if (param2->unk18 != 0)
        {
            reg_G2_BG2CNT |= 0x40;
        }
        else
        {
            reg_G2_BG2CNT &= ~0x40;
        }

        break;

    case 3:
        GX_EngineAToggleLayers(8, GX_LAYER_TOGGLE_ON);

        switch (param3)
        {
        default:
        case 0:
            reg_G2_BG3CNT = (reg_G2_BG3CNT & 0x43) |
                            (res << 14) | (param2->unk12 << 8) | (param2->unk11 << 7)  | (param2->unk13 << 2);
            break;
        case 1:
            reg_G2_BG3CNT = (reg_G2_BG3CNT & 0x43) |
                            (res << 14) | (param2->unk12 << 8) |  (param2->unk16 << 13) | (param2->unk13 << 2);
            break;
        case 2:
            reg_G2_BG3CNT = (reg_G2_BG3CNT & 0x43) |
                            (res << 14) | (param2->unk12 << 8) | (param2->unk16 << 13) | (param2->unk13 << 2);
            break;
        }

        reg_G2_BG3CNT = (reg_G2_BG3CNT & ~3) | (param2->unk15);
        if (param2->unk18 != 0)
        {
            reg_G2_BG3CNT |= 0x40;
        }
        else
        {
            reg_G2_BG3CNT &= ~0x40;
        }
        break;

    case 4:
        GX_EngineBToggleLayers(1, GX_LAYER_TOGGLE_ON);

        reg_G2S_DB_BG0CNT = (reg_G2S_DB_BG0CNT & 0x43) |
                        (res << 14) | (param2->unk12 << 8) | (param2->unk11 << 7) | (param2->unk14 << 13) | (param2->unk13 << 2);

        reg_G2S_DB_BG0CNT = (reg_G2S_DB_BG0CNT & ~3) | (param2->unk15);

        if (param2->unk18 != 0)
        {
            reg_G2S_DB_BG0CNT |= 0x40;
        }
        else
        {
            reg_G2S_DB_BG0CNT &= ~0x40;
        }

        break;

    case 5:
        GX_EngineBToggleLayers(2, GX_LAYER_TOGGLE_ON);

        reg_G2S_DB_BG1CNT = (reg_G2S_DB_BG1CNT & 0x43) |
                        (res << 14) | (param2->unk12 << 8) | (param2->unk11 << 7) | (param2->unk14 << 13) | (param2->unk13 << 2);

        reg_G2S_DB_BG1CNT = (reg_G2S_DB_BG1CNT & ~3) | (param2->unk15);

        if (param2->unk18 != 0)
        {
            reg_G2S_DB_BG1CNT |= 0x40;
        }
        else
        {
            reg_G2S_DB_BG1CNT &= ~0x40;
        }

        break;

    case 6:
        GX_EngineBToggleLayers(4, GX_LAYER_TOGGLE_ON);

        switch (param3)
        {
        default:
        case 0:
            reg_G2S_DB_BG2CNT = (reg_G2S_DB_BG2CNT & 0x43) |
                                (res << 14) | (param2->unk12 << 8) | (param2->unk11 << 7) | (param2->unk13 << 2);
            break;
        case 1:
            reg_G2S_DB_BG2CNT = (reg_G2S_DB_BG2CNT & 0x43) |
                                (res << 14) | (param2->unk12 << 8) | (param2->unk16 << 13) | (param2->unk13 << 2);
            break;
        case 2:
            reg_G2S_DB_BG2CNT = (reg_G2S_DB_BG2CNT & 0x43) |
                                (res << 14) | (param2->unk12 << 8) | (param2->unk16 << 13) | (param2->unk13 << 2);
            break;
        }

        reg_G2S_DB_BG2CNT = (reg_G2S_DB_BG2CNT & ~3) | (param2->unk15);

        if (param2->unk18 != 0)
        {
            reg_G2S_DB_BG2CNT |= 0x40;
        }
        else
        {
            reg_G2S_DB_BG2CNT &= ~0x40;
        }

        break;
    case 7:
        GX_EngineBToggleLayers(8, GX_LAYER_TOGGLE_ON);
        switch (param3)
        {
        default:
        case 0:
            reg_G2S_DB_BG3CNT = (reg_G2S_DB_BG3CNT & 0x43) |
                                (res << 14) | (param2->unk12 << 8) | (param2->unk11 << 7) | (param2->unk13 << 2);
            break;
        case 1:
            reg_G2S_DB_BG3CNT = (reg_G2S_DB_BG3CNT & 0x43) |
                                (res << 14) | (param2->unk12 << 8) | (param2->unk16 << 13) | (param2->unk13 << 2);
            break;
        case 2:
            reg_G2S_DB_BG3CNT = (reg_G2S_DB_BG3CNT & 0x43) |
                                (res << 14) | (param2->unk12 << 8) | (param2->unk16 << 13) | (param2->unk13 << 2);
            break;
        }

        reg_G2S_DB_BG3CNT = (reg_G2S_DB_BG3CNT & ~3) | (param2->unk15);
        if (param2->unk18 != 0)
        {
            reg_G2S_DB_BG3CNT |= 0x40;
        }
        else
        {
            reg_G2S_DB_BG3CNT &= ~0x40;
        }
        break;
    }

    param0->unk08[param1].unk20 = 0;
    param0->unk08[param1].unk24 = 0x1000;
    param0->unk08[param1].unk28 = 0x1000;
    param0->unk08[param1].unk2c = 0;
    param0->unk08[param1].unk30 = 0;

    if (param2->unk08 != 0)
    {
        param0->unk08[param1].unk08 = AllocFromHeap(param0->unk00, param2->unk08);

        MIi_CpuClear16(0, param0->unk08[param1].unk08, param2->unk08);

        param0->unk08[param1].unk0c = param2->unk08;
        param0->unk08[param1].unk10 = param2->unk0c;
    }
    else
    {
        param0->unk08[param1].unk08 = 0;
        param0->unk08[param1].unk0c = 0;
        param0->unk08[param1].unk10 = 0;
    }

    param0->unk08[param1].unk1d = param2->unk10;
    param0->unk08[param1].unk1c = param3;
    param0->unk08[param1].unk1e = param2->unk11;

    if (param3 == 0 && param2->unk11 == 0)
    {
        param0->unk08[param1].unk1f = 0x20;
    }
    else
    {
       param0->unk08[param1].unk1f = 0x40;
    }

    FUN_020179E0(param0, param1, 0, param2->unk00);
    FUN_020179E0(param0, param1, 3, param2->unk04);
}
#else
GLOBAL_ASM("asm/nonmatchings/FUN_02016C18.s")
#endif

