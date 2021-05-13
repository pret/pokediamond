#include "unk_02016B94.h"
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

extern u8 FUN_020177DC(u8 param0, u32 param1);
extern void FUN_020179E0(struct UnkStruct2 *param0, u32 param1, u32 param2, u32 val);

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
THUMB_FUNC void FUN_02016C18(
    struct UnkStruct2 *param0, u8 param1, struct UnkStruct1 *param2, u8 param3)
{
    u8 res = FUN_020177DC(param2->unk10, param3);
    switch (param1)
    {
    case 0:
        GX_EngineAToggleLayers(1, GX_LAYER_TOGGLE_ON);

        reg_G2_BG0CNT = (reg_G2_BG0CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                        (param2->unk11 << 7) | (param2->unk14 << 13) | (param2->unk13 << 2);
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
        reg_G2_BG1CNT = (reg_G2_BG1CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                        (param2->unk11 << 7) | (param2->unk14 << 13) | (param2->unk13 << 2);
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
            reg_G2_BG2CNT = (reg_G2_BG2CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                            (param2->unk11 << 7) | (param2->unk13 << 2);
            break;
        case 1:
            reg_G2_BG2CNT = (reg_G2_BG2CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                            (param2->unk16 << 13) | (param2->unk13 << 2);
            break;
        case 2:
            reg_G2_BG2CNT = (reg_G2_BG2CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                            (param2->unk16 << 13) | (param2->unk13 << 2);
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
            reg_G2_BG3CNT = (reg_G2_BG3CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                            (param2->unk11 << 7) | (param2->unk13 << 2);
            break;
        case 1:
            reg_G2_BG3CNT = (reg_G2_BG3CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                            (param2->unk16 << 13) | (param2->unk13 << 2);
            break;
        case 2:
            reg_G2_BG3CNT = (reg_G2_BG3CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                            (param2->unk16 << 13) | (param2->unk13 << 2);
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

        reg_G2S_DB_BG0CNT = (reg_G2S_DB_BG0CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                            (param2->unk11 << 7) | (param2->unk14 << 13) | (param2->unk13 << 2);

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

        reg_G2S_DB_BG1CNT = (reg_G2S_DB_BG1CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                            (param2->unk11 << 7) | (param2->unk14 << 13) | (param2->unk13 << 2);

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
            reg_G2S_DB_BG2CNT = (reg_G2S_DB_BG2CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                                (param2->unk11 << 7) | (param2->unk13 << 2);
            break;
        case 1:
            reg_G2S_DB_BG2CNT = (reg_G2S_DB_BG2CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                                (param2->unk16 << 13) | (param2->unk13 << 2);
            break;
        case 2:
            reg_G2S_DB_BG2CNT = (reg_G2S_DB_BG2CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                                (param2->unk16 << 13) | (param2->unk13 << 2);
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
            reg_G2S_DB_BG3CNT = (reg_G2S_DB_BG3CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                                (param2->unk11 << 7) | (param2->unk13 << 2);
            break;
        case 1:
            reg_G2S_DB_BG3CNT = (reg_G2S_DB_BG3CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                                (param2->unk16 << 13) | (param2->unk13 << 2);
            break;
        case 2:
            reg_G2S_DB_BG3CNT = (reg_G2S_DB_BG3CNT & 0x43) | (res << 14) | (param2->unk12 << 8) |
                                (param2->unk16 << 13) | (param2->unk13 << 2);
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



#ifdef NONMATCHING
THUMB_FUNC void FUN_020170F4(struct UnkStruct2 *param0, u8 param1, u32 param2, u8 param3)
{
    if (param2 == 0)
    {
        param0->unk08[param1].unk1e = param3;
    }

    switch (param1)
    {
    case 0:
        u16 bg0cnt = reg_G2_BG0CNT;
        if (param2 == 1)
        {
            bg0cnt = bg0cnt & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
        }
        else if (param2 == 2)
        {
            bg0cnt = bg0cnt & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
        }

        reg_G2_BG0CNT = (reg_G2_BG0CNT & 0x43) | ((u32)(bg0cnt << 0x10) >> 0x1e) << 0xe |
                        param0->unk08[param1].unk1e << 7 | ((u32)(bg0cnt << 0x13) >> 0x1b) << 8 |
                        ((u32)(bg0cnt << 0x1a) >> 0x1c) << 2 |
                        ((u32)(bg0cnt << 0x12) >> 0x1f) << 0xd;

        break;
    case 1:
        u16 bg1cnt = reg_G2_BG1CNT;
        if (param2 == 1)
        {
            bg1cnt = bg1cnt & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
        }
        else if (param2 == 2)
        {
            bg1cnt = bg1cnt & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
        }

        reg_G2_BG1CNT = (reg_G2_BG1CNT & 0x43) | (((u32)bg1cnt << 0x10) >> 0x1e) << 0xe |
                        param0->unk08[param1].unk1e << 7 | ((u32)(bg1cnt << 0x13) >> 0x1b) << 8 |
                        ((u32)(bg1cnt << 0x1a) >> 0x1c) << 2 |
                        ((u32)(bg1cnt << 0x12) >> 0x1f) << 0xd;

        break;
    case 2:
        switch (param0->unk08[param1].unk1c)
        {
        default:
        case 0:
            u16 bg2cnt_0 = reg_G2_BG2CNT;
            if (param2 == 1)
            {
                bg2cnt_0 = bg2cnt_0 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                bg2cnt_0 = bg2cnt_0 & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
            }

            reg_G2_BG2CNT = (reg_G2_BG2CNT & 0x43) | ((u32)(bg2cnt_0 << 0x10) >> 0x1e) << 0xe |
                            param0->unk08[param1].unk1e << 7 |
                            ((u32)(bg2cnt_0 << 0x13) >> 0x1b) << 8 |
                            ((u32)(bg2cnt_0 << 0x1a) >> 0x1c) << 2;

            break;
        case 1:
            u16 bg2cnt_1 = reg_G2_BG2CNT;
            if (param2 == 1)
            {
                bg2cnt_1 = bg2cnt_1 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                bg2cnt_1 = bg2cnt_1 & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
            }

            reg_G2_BG2CNT = (reg_G2_BG2CNT & 0x43) | ((u32)(bg2cnt_1 << 0x10) >> 0x1e) << 0xe |
                            ((u32)(bg2cnt_1 << 0x13) >> 0x1b) << 8 |
                            ((u32)(bg2cnt_1 << 0x1a) >> 0x1c) << 2 |
                            ((u32)(bg2cnt_1 << 0x12) >> 0x1f) << 0xd;
            break;
        case 2:
            u16 bg2cnt_2 = reg_G2_BG2CNT;
            if (param2 == 1)
            {
                bg2cnt_2 = bg2cnt_2 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                bg2cnt_2 = bg2cnt_2 & ~0x38 | ((u32)(param3 << 0x1d) >> 0x1a);
            }

            reg_G2_BG2CNT = (reg_G2_BG2CNT & 0x43) | ((u32)(bg2cnt_2 << 0x10) >> 0x1e) << 0xe |
                            ((u32)(bg2cnt_2 << 0x13) >> 0x1b) << 8 |
                            ((u32)(bg2cnt_2 << 0x1a) >> 0x1d) << 2 |
                            ((u32)(bg2cnt_2 << 0x12) >> 0x1f) << 0xd;
            break;
        }
        break;
    case 3:
        switch (param0->unk08[param1].unk1c)
        {
        default:
        case 0:
            u16 bg3cnt_0 = reg_G2_BG3CNT;
            if (param2 == 1)
            {
                bg3cnt_0 = bg3cnt_0 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                bg3cnt_0 = bg3cnt_0 & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
            }

            reg_G2_BG3CNT = (reg_G2_BG3CNT & 0x43) | ((u32)(bg3cnt_0 << 0x10) >> 0x1e) << 0xe |
                            param0->unk08[param1].unk1e << 7 |
                            ((u32)(bg3cnt_0 << 0x13) >> 0x1b) << 8 |
                            ((u32)(bg3cnt_0 << 0x1a) >> 0x1c) << 2;

            break;
        case 1:
            u16 bg3cnt_1 = reg_G2_BG3CNT;
            if (param2 == 1)
            {
                bg3cnt_1 = bg3cnt_1 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                bg3cnt_1 = bg3cnt_1 & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
            }

            reg_G2_BG3CNT = (reg_G2_BG3CNT & 0x43) | ((u32)(bg3cnt_1 << 0x10) >> 0x1e) << 0xe |
                            ((u32)(bg3cnt_1 << 0x13) >> 0x1b) << 8 |
                            ((u32)(bg3cnt_1 << 0x1a) >> 0x1c) << 2 |
                            ((u32)(bg3cnt_1 << 0x12) >> 0x1f) << 0xd;
            break;
        case 2:
            u16 bg3cnt_2 = reg_G2_BG3CNT;
            if (param2 == 1)
            {
                bg3cnt_2 = bg3cnt_2 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                bg3cnt_2 = bg3cnt_2 & ~0x38 | ((u32)(param3 << 0x1d) >> 0x1a);
            }

            reg_G2_BG3CNT = (reg_G2_BG3CNT & 0x43) | ((u32)(bg3cnt_2 << 0x10) >> 0x1e) << 0xe |
                            ((u32)(bg3cnt_2 << 0x13) >> 0x1b) << 8 |
                            ((u32)(bg3cnt_2 << 0x1a) >> 0x1d) << 2 |
                            ((u32)(bg3cnt_2 << 0x12) >> 0x1f) << 0xd;
            break;
        }
        break;
    case 4:
        u16 db_bg0cnt = reg_G2S_DB_BG0CNT;
        if (param2 == 1)
        {
            db_bg0cnt = db_bg0cnt & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
        }
        else if (param2 == 2)
        {
            db_bg0cnt = db_bg0cnt & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
        }

        reg_G2S_DB_BG0CNT =
            (reg_G2S_DB_BG0CNT & 0x43) | ((u32)(db_bg0cnt << 0x10) >> 0x1e) << 0xe |
            param0->unk08[param1].unk1e << 7 | ((u32)(db_bg0cnt << 0x13) >> 0x1b) << 8 |
            ((u32)(db_bg0cnt << 0x1a) >> 0x1c) << 2 | ((u32)(db_bg0cnt << 0x12) >> 0x1f) << 0xd;

        break;
    case 5:
        u16 db_bg1cnt = reg_G2S_DB_BG1CNT;
        if (param2 == 1)
        {
            db_bg1cnt = db_bg1cnt & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
        }
        else if (param2 == 2)
        {
            db_bg1cnt = db_bg1cnt & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
        }

        reg_G2S_DB_BG1CNT =
            (reg_G2S_DB_BG1CNT & 0x43) | ((u32)(db_bg1cnt << 0x10) >> 0x1e) << 0xe |
            param0->unk08[param1].unk1e << 7 | ((u32)(db_bg1cnt << 0x13) >> 0x1b) << 8 |
            ((u32)(db_bg1cnt << 0x1a) >> 0x1c) << 2 | ((u32)(db_bg1cnt << 0x12) >> 0x1f) << 0xd;

        break;
    case 6:
        switch (param0->unk08[param1].unk1c)
        {
        default:
        case 0:
            u16 db_bg2cnt_0 = reg_G2S_DB_BG2CNT;
            if (param2 == 1)
            {
                db_bg2cnt_0 = db_bg2cnt_0 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                db_bg2cnt_0 = db_bg2cnt_0 & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
            }

            reg_G2S_DB_BG2CNT =
                (reg_G2S_DB_BG2CNT & 0x43) | ((u32)(db_bg2cnt_0 << 0x10) >> 0x1e) << 0xe |
                param0->unk08[param1].unk1e << 7 | ((u32)(db_bg2cnt_0 << 0x13) >> 0x1b) << 8 |
                ((u32)(db_bg2cnt_0 << 0x1a) >> 0x1c) << 2;

            break;
        case 1:
            u16 db_bg2cnt_1 = reg_G2S_DB_BG2CNT;
            if (param2 == 1)
            {
                db_bg2cnt_1 = db_bg2cnt_1 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                db_bg2cnt_1 = db_bg2cnt_1 & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
            }

            reg_G2S_DB_BG2CNT = (reg_G2S_DB_BG2CNT & 0x43) |
                                ((u32)(db_bg2cnt_1 << 0x10) >> 0x1e) << 0xe |
                                ((u32)(db_bg2cnt_1 << 0x13) >> 0x1b) << 8 |
                                ((u32)(db_bg2cnt_1 << 0x1a) >> 0x1c) << 2 |
                                ((u32)(db_bg2cnt_1 << 0x12) >> 0x1f) << 0xd;
            break;
        case 2:
            u16 db_bg2cnt_2 = reg_G2S_DB_BG2CNT;
            if (param2 == 1)
            {
                db_bg2cnt_2 = db_bg2cnt_2 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                db_bg2cnt_2 = db_bg2cnt_2 & ~0x38 | ((u32)(param3 << 0x1d) >> 0x1a);
            }

            reg_G2S_DB_BG2CNT = (reg_G2S_DB_BG2CNT & 0x43) |
                                ((u32)(db_bg2cnt_2 << 0x10) >> 0x1e) << 0xe |
                                ((u32)(db_bg2cnt_2 << 0x13) >> 0x1b) << 8 |
                                ((u32)(db_bg2cnt_2 << 0x1a) >> 0x1d) << 2 |
                                ((u32)(db_bg2cnt_2 << 0x12) >> 0x1f) << 0xd;
            break;
        }
        break;
    case 7:
        switch (param0->unk08[param1].unk1c)
        {
        default:
        case 0:
            u16 db_bg3cnt_0 = reg_G2S_DB_BG3CNT;
            if (param2 == 1)
            {
                db_bg3cnt_0 = db_bg3cnt_0 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                db_bg3cnt_0 = db_bg3cnt_0 & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
            }

            reg_G2S_DB_BG3CNT =
                (reg_G2S_DB_BG3CNT & 0x43) | ((u32)(db_bg3cnt_0 << 0x10) >> 0x1e) << 0xe |
                param0->unk08[param1].unk1e << 7 | ((u32)(db_bg3cnt_0 << 0x13) >> 0x1b) << 8 |
                ((u32)(db_bg3cnt_0 << 0x1a) >> 0x1c) << 2;

            break;
        case 1:
            u16 db_bg3cnt_1 = reg_G2S_DB_BG3CNT;
            if (param2 == 1)
            {
                db_bg3cnt_1 = db_bg3cnt_1 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                db_bg3cnt_1 = db_bg3cnt_1 & ~0x3c | ((u32)(param3 << 0x1c) >> 0x1a);
            }

            reg_G2S_DB_BG3CNT = (reg_G2S_DB_BG3CNT & 0x43) |
                                ((u32)(db_bg3cnt_1 << 0x10) >> 0x1e) << 0xe |
                                ((u32)(db_bg3cnt_1 << 0x13) >> 0x1b) << 8 |
                                ((u32)(db_bg3cnt_1 << 0x1a) >> 0x1c) << 2 |
                                ((u32)(db_bg3cnt_1 << 0x12) >> 0x1f) << 0xd;
            break;
        case 2:
            u16 db_bg3cnt_2 = reg_G2S_DB_BG3CNT;
            if (param2 == 1)
            {
                db_bg3cnt_2 = db_bg3cnt_2 & 0xFFFFE0FF | ((u32)(param3 << 0x1b) >> 0x13);
            }
            else if (param2 == 2)
            {
                db_bg3cnt_2 = db_bg3cnt_2 & ~0x38 | ((u32)(param3 << 0x1d) >> 0x1a);
            }

            reg_G2S_DB_BG3CNT = (reg_G2S_DB_BG3CNT & 0x43) |
                                ((u32)(db_bg3cnt_2 << 0x10) >> 0x1e) << 0xe |
                                ((u32)(db_bg3cnt_2 << 0x13) >> 0x1b) << 8 |
                                ((u32)(db_bg3cnt_2 << 0x1a) >> 0x1d) << 2 |
                                ((u32)(db_bg3cnt_2 << 0x12) >> 0x1f) << 0xd;
            break;
        }
        break;
    }
}
#else
THUMB_FUNC asm void FUN_020170F4(struct UnkStruct2 *param0, u8 param1, u32 param2, u8 param3)
{
    // clang-format off
	push {r3-r7, lr}
	sub sp, #0x20
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r1, r2, #0x0
	add r0, r3, #0x0
	cmp r1, #0x0
	bne _0201710C
	mov r2, #0x2c
	mul r2, r4
	add r2, r5, r2
	strb r0, [r2, #0x1e]
_0201710C:
	cmp r4, #0x7
	bls _02017112
	b _020177C4
_02017112:
	add r2, r4, r4
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0201711E: //; jump table (using 16-bit offset)
	// .short _0201712E - _0201711E - 2; case 0
	// .short _0201719A - _0201711E - 2; case 1
	// .short _02017206 - _0201711E - 2; case 2
	// .short _0201733A - _0201711E - 2; case 3
	// .short _0201746E - _0201711E - 2; case 4
	// .short _020174F4 - _0201711E - 2; case 5
	// .short _02017560 - _0201711E - 2; case 6
	// .short _02017694 - _0201711E - 2; case 7

    lsl    r6, r1, #0
    lsl    r2, r7, #1
    lsl    r6, r4, #3
    lsl    r2, r3, #8
    lsl    r6, r1, #13
    lsl    r4, r2, #15
    lsl    r0, r0, #17
    lsl    r4, r6, #21
_0201712E:
	ldr r2, =0x04000008
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x1e]
	bne _0201714A
	ldrh r3, [r2, #0x1e]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0x1e]
	b _0201715C
_0201714A:
	cmp r1, #0x2
	bne _0201715C
	ldrh r3, [r2, #0x1e]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0x1e]
_0201715C:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x1e]
	add sp, #0x20
	lsl r0, r3, #0x12
	lsr r6, r0, #0x1f
	lsl r0, r3, #0x1a
	lsr r2, r0, #0x1c
	lsl r0, r3, #0x13
	lsr r1, r0, #0x1b
	mov r0, #0x2c
	mul r0, r4
	add r0, r5, r0
	lsl r3, r3, #0x10
	lsr r5, r3, #0x1e
	lsl r3, r2, #0x2
	ldrb r0, [r0, #0x1e]
	lsl r2, r1, #0x8
	lsl r4, r6, #0xd
	lsl r1, r0, #0x7
	ldr r0, =0x04000008
	mov r6, #0x43
	ldrh r7, [r0, #0x0]
	lsl r5, r5, #0xe
	and r6, r7
	orr r5, r6
	orr r1, r5
	orr r1, r2
	orr r1, r3
	orr r1, r4
	strh r1, [r0, #0x0]
	pop {r3-r7, pc}
_0201719A:
	ldr r2, =0x0400000A
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x1c]
	bne _020171B6
	ldrh r3, [r2, #0x1c]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0x1c]
	b _020171C8
_020171B6:
	cmp r1, #0x2
	bne _020171C8
	ldrh r3, [r2, #0x1c]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0x1c]
_020171C8:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x1c]
	add sp, #0x20
	lsl r0, r3, #0x12
	lsr r6, r0, #0x1f
	lsl r0, r3, #0x1a
	lsr r2, r0, #0x1c
	lsl r0, r3, #0x13
	lsr r1, r0, #0x1b
	mov r0, #0x2c
	mul r0, r4
	add r0, r5, r0
	lsl r3, r3, #0x10
	lsr r5, r3, #0x1e
	lsl r3, r2, #0x2
	ldrb r0, [r0, #0x1e]
	lsl r2, r1, #0x8
	lsl r4, r6, #0xd
	lsl r1, r0, #0x7
	ldr r0, =0x0400000A
	mov r6, #0x43
	ldrh r7, [r0, #0x0]
	lsl r5, r5, #0xe
	and r6, r7
	orr r5, r6
	orr r1, r5
	orr r1, r2
	orr r1, r3
	orr r1, r4
	strh r1, [r0, #0x0]
	pop {r3-r7, pc}
_02017206:
	mov r2, #0x2c
	mul r2, r4
	add r3, r5, r2
	ldrb r3, [r3, #0x1c]
	cmp r3, #0x0
	beq _0201721A
	cmp r3, #0x1
	beq _0201727A
	cmp r3, #0x2
	beq _020172DA
_0201721A:
	ldr r3, =0x0400000C
	cmp r1, #0x1
	ldrh r4, [r3, #0x0]
	add r3, sp, #0x0
	strh r4, [r3, #0x1a]
	bne _02017236
	ldrh r4, [r3, #0x1a]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r4
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r3, #0x1a]
	b _02017248
_02017236:
	cmp r1, #0x2
	bne _02017248
	ldrh r4, [r3, #0x1a]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r4, r1
	lsr r0, r0, #0x1a
	orr r0, r4
	strh r0, [r3, #0x1a]
_02017248:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x1a]
	add r2, r5, r2
	ldr r6, =0x0400000C
	lsl r0, r3, #0x1a
	ldrb r4, [r2, #0x1e]
	lsr r1, r0, #0x1c
	lsl r0, r3, #0x13
	lsl r2, r3, #0x10
	lsr r3, r2, #0x1e
	ldrh r5, [r6, #0x0]
	lsr r0, r0, #0x1b
	lsl r2, r1, #0x2
	lsl r1, r0, #0x8
	lsl r0, r4, #0x7
	mov r4, #0x43
	and r4, r5
	lsl r3, r3, #0xe
	orr r3, r4
	orr r0, r3
	orr r0, r1
	orr r0, r2
	add sp, #0x20
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_0201727A:
	ldr r2, =0x0400000C
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x18]
	bne _02017296
	ldrh r3, [r2, #0x18]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0x18]
	b _020172A8
_02017296:
	cmp r1, #0x2
	bne _020172A8
	ldrh r3, [r2, #0x18]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0x18]
_020172A8:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x18]
	ldr r6, =0x0400000C
	add sp, #0x20
	lsl r1, r3, #0x13
	lsl r0, r3, #0x1a
	lsr r4, r1, #0x1b
	lsl r1, r3, #0x12
	lsr r2, r1, #0x1f
	lsl r1, r3, #0x10
	lsr r3, r1, #0x1e
	lsr r0, r0, #0x1c
	lsl r1, r0, #0x2
	lsl r0, r4, #0x8
	ldrh r5, [r6, #0x0]
	mov r4, #0x43
	lsl r3, r3, #0xe
	and r4, r5
	orr r3, r4
	orr r0, r3
	lsl r2, r2, #0xd
	orr r0, r1
	orr r0, r2
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_020172DA:
	ldr r2, =0x0400000C
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x16]
	bne _020172F6
	ldrh r3, [r2, #0x16]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0x16]
	b _02017308
_020172F6:
	cmp r1, #0x2
	bne _02017308
	ldrh r3, [r2, #0x16]
	mov r1, #0x38
	lsl r0, r0, #0x1d
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0x16]
_02017308:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x16]
	ldr r6, =0x0400000C
	add sp, #0x20
	lsl r1, r3, #0x13
	lsr r4, r1, #0x1b
	lsl r1, r3, #0x12
	lsr r2, r1, #0x1f
	lsl r0, r3, #0x1a
	lsl r1, r3, #0x10
	lsr r3, r1, #0x1e
	lsl r1, r4, #0x8
	lsr r0, r0, #0x1d
	ldrh r5, [r6, #0x0]
	mov r4, #0x43
	lsl r3, r3, #0xe
	and r4, r5
	lsl r0, r0, #0x2
	orr r3, r4
	orr r0, r3
	lsl r2, r2, #0xd
	orr r0, r1
	orr r0, r2
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_0201733A:
	mov r2, #0x2c
	mul r2, r4
	add r3, r5, r2
	ldrb r3, [r3, #0x1c]
	cmp r3, #0x0
	beq _0201734E
	cmp r3, #0x1
	beq _020173AE
	cmp r3, #0x2
	beq _0201740E
_0201734E:
	ldr r3, =0x0400000E
	cmp r1, #0x1
	ldrh r4, [r3, #0x0]
	add r3, sp, #0x0
	strh r4, [r3, #0x14]
	bne _0201736A
	ldrh r4, [r3, #0x14]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r4
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r3, #0x14]
	b _0201737C
_0201736A:
	cmp r1, #0x2
	bne _0201737C
	ldrh r4, [r3, #0x14]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r4, r1
	lsr r0, r0, #0x1a
	orr r0, r4
	strh r0, [r3, #0x14]
_0201737C:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x14]
	add r2, r5, r2
	ldr r6, =0x0400000E
	lsl r0, r3, #0x1a
	ldrb r4, [r2, #0x1e]
	lsr r1, r0, #0x1c
	lsl r0, r3, #0x13
	lsl r2, r3, #0x10
	lsr r3, r2, #0x1e
	ldrh r5, [r6, #0x0]
	lsr r0, r0, #0x1b
	lsl r2, r1, #0x2
	lsl r1, r0, #0x8
	lsl r0, r4, #0x7
	mov r4, #0x43
	and r4, r5
	lsl r3, r3, #0xe
	orr r3, r4
	orr r0, r3
	orr r0, r1
	orr r0, r2
	add sp, #0x20
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_020173AE:
	ldr r2, =0x0400000E
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x12]
	bne _020173CA
	ldrh r3, [r2, #0x12]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0x12]
	b _020173DC
_020173CA:
	cmp r1, #0x2
	bne _020173DC
	ldrh r3, [r2, #0x12]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0x12]
_020173DC:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x12]
	ldr r6, =0x0400000E
	add sp, #0x20
	lsl r1, r3, #0x13
	lsl r0, r3, #0x1a
	lsr r4, r1, #0x1b
	lsl r1, r3, #0x12
	lsr r2, r1, #0x1f
	lsl r1, r3, #0x10
	lsr r3, r1, #0x1e
	lsr r0, r0, #0x1c
	lsl r1, r0, #0x2
	lsl r0, r4, #0x8
	ldrh r5, [r6, #0x0]
	mov r4, #0x43
	lsl r3, r3, #0xe
	and r4, r5
	orr r3, r4
	orr r0, r3
	lsl r2, r2, #0xd
	orr r0, r1
	orr r0, r2
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_0201740E:
	ldr r2, =0x0400000E
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x10]
	bne _0201742A
	ldrh r3, [r2, #0x10]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0x10]
	b _0201743C
_0201742A:
	cmp r1, #0x2
	bne _0201743C
	ldrh r3, [r2, #0x10]
	mov r1, #0x38
	lsl r0, r0, #0x1d
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0x10]
_0201743C:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x10]
	ldr r6, =0x0400000E
	add sp, #0x20
	lsl r1, r3, #0x13
	lsr r4, r1, #0x1b
	lsl r1, r3, #0x12
	lsr r2, r1, #0x1f
	lsl r0, r3, #0x1a
	lsl r1, r3, #0x10
	lsr r3, r1, #0x1e
	lsl r1, r4, #0x8
	lsr r0, r0, #0x1d
	ldrh r5, [r6, #0x0]
	mov r4, #0x43
	lsl r3, r3, #0xe
	and r4, r5
	lsl r0, r0, #0x2
	orr r3, r4
	orr r0, r3
	lsl r2, r2, #0xd
	orr r0, r1
	orr r0, r2
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_0201746E:
	ldr r2, =0x04001008
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0xe]
	bne _020174A4
	ldrh r3, [r2, #0xe]
	ldr r1, =0xFFFFE0FF
	b _02017498
_02017498:
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0xe]
	b _020174B6
_020174A4:
	cmp r1, #0x2
	bne _020174B6
	ldrh r3, [r2, #0xe]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0xe]
_020174B6:
	add r0, sp, #0x0
	ldrh r3, [r0, #0xe]
	add sp, #0x20
	lsl r0, r3, #0x12
	lsr r6, r0, #0x1f
	lsl r0, r3, #0x1a
	lsr r2, r0, #0x1c
	lsl r0, r3, #0x13
	lsr r1, r0, #0x1b
	mov r0, #0x2c
	mul r0, r4
	add r0, r5, r0
	lsl r3, r3, #0x10
	lsr r5, r3, #0x1e
	lsl r3, r2, #0x2
	ldrb r0, [r0, #0x1e]
	lsl r2, r1, #0x8
	lsl r4, r6, #0xd
	lsl r1, r0, #0x7
	ldr r0, =0x04001008
	mov r6, #0x43
	ldrh r7, [r0, #0x0]
	lsl r5, r5, #0xe
	and r6, r7
	orr r5, r6
	orr r1, r5
	orr r1, r2
	orr r1, r3
	orr r1, r4
	strh r1, [r0, #0x0]
	pop {r3-r7, pc}
_020174F4:
	ldr r2, =0x0400100A
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0xc]
	bne _02017510
	ldrh r3, [r2, #0xc]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0xc]
	b _02017522
_02017510:
	cmp r1, #0x2
	bne _02017522
	ldrh r3, [r2, #0xc]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0xc]
_02017522:
	add r0, sp, #0x0
	ldrh r3, [r0, #0xc]
	add sp, #0x20
	lsl r0, r3, #0x12
	lsr r6, r0, #0x1f
	lsl r0, r3, #0x1a
	lsr r2, r0, #0x1c
	lsl r0, r3, #0x13
	lsr r1, r0, #0x1b
	mov r0, #0x2c
	mul r0, r4
	add r0, r5, r0
	lsl r3, r3, #0x10
	lsr r5, r3, #0x1e
	lsl r3, r2, #0x2
	ldrb r0, [r0, #0x1e]
	lsl r2, r1, #0x8
	lsl r4, r6, #0xd
	lsl r1, r0, #0x7
	ldr r0, =0x0400100A
	mov r6, #0x43
	ldrh r7, [r0, #0x0]
	lsl r5, r5, #0xe
	and r6, r7
	orr r5, r6
	orr r1, r5
	orr r1, r2
	orr r1, r3
	orr r1, r4
	strh r1, [r0, #0x0]
	pop {r3-r7, pc}
_02017560:
	mov r2, #0x2c
	mul r2, r4
	add r3, r5, r2
	ldrb r3, [r3, #0x1c]
	cmp r3, #0x0
	beq _02017574
	cmp r3, #0x1
	beq _020175D4
	cmp r3, #0x2
	beq _02017634
_02017574:
	ldr r3, =0x0400100C
	cmp r1, #0x1
	ldrh r4, [r3, #0x0]
	add r3, sp, #0x0
	strh r4, [r3, #0xa]
	bne _02017590
	ldrh r4, [r3, #0xa]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r4
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r3, #0xa]
	b _020175A2
_02017590:
	cmp r1, #0x2
	bne _020175A2
	ldrh r4, [r3, #0xa]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r4, r1
	lsr r0, r0, #0x1a
	orr r0, r4
	strh r0, [r3, #0xa]
_020175A2:
	add r0, sp, #0x0
	ldrh r3, [r0, #0xa]
	add r2, r5, r2
	ldr r6, =0x0400100C
	lsl r0, r3, #0x1a
	ldrb r4, [r2, #0x1e]
	lsr r1, r0, #0x1c
	lsl r0, r3, #0x13
	lsl r2, r3, #0x10
	lsr r3, r2, #0x1e
	ldrh r5, [r6, #0x0]
	lsr r0, r0, #0x1b
	lsl r2, r1, #0x2
	lsl r1, r0, #0x8
	lsl r0, r4, #0x7
	mov r4, #0x43
	and r4, r5
	lsl r3, r3, #0xe
	orr r3, r4
	orr r0, r3
	orr r0, r1
	orr r0, r2
	add sp, #0x20
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_020175D4:
	ldr r2, =0x0400100C
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x8]
	bne _020175F0
	ldrh r3, [r2, #0x8]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0x8]
	b _02017602
_020175F0:
	cmp r1, #0x2
	bne _02017602
	ldrh r3, [r2, #0x8]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0x8]
_02017602:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x8]
	ldr r6, =0x0400100C
	add sp, #0x20
	lsl r1, r3, #0x13
	lsl r0, r3, #0x1a
	lsr r4, r1, #0x1b
	lsl r1, r3, #0x12
	lsr r2, r1, #0x1f
	lsl r1, r3, #0x10
	lsr r3, r1, #0x1e
	lsr r0, r0, #0x1c
	lsl r1, r0, #0x2
	lsl r0, r4, #0x8
	ldrh r5, [r6, #0x0]
	mov r4, #0x43
	lsl r3, r3, #0xe
	and r4, r5
	orr r3, r4
	orr r0, r3
	lsl r2, r2, #0xd
	orr r0, r1
	orr r0, r2
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_02017634:
	ldr r2, =0x0400100C
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x6]
	bne _02017650
	ldrh r3, [r2, #0x6]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0x6]
	b _02017662
_02017650:
	cmp r1, #0x2
	bne _02017662
	ldrh r3, [r2, #0x6]
	mov r1, #0x38
	lsl r0, r0, #0x1d
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0x6]
_02017662:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x6]
	ldr r6, =0x0400100C
	add sp, #0x20
	lsl r1, r3, #0x13
	lsr r4, r1, #0x1b
	lsl r1, r3, #0x12
	lsr r2, r1, #0x1f
	lsl r0, r3, #0x1a
	lsl r1, r3, #0x10
	lsr r3, r1, #0x1e
	lsl r1, r4, #0x8
	lsr r0, r0, #0x1d
	ldrh r5, [r6, #0x0]
	mov r4, #0x43
	lsl r3, r3, #0xe
	and r4, r5
	lsl r0, r0, #0x2
	orr r3, r4
	orr r0, r3
	lsl r2, r2, #0xd
	orr r0, r1
	orr r0, r2
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_02017694:
	mov r2, #0x2c
	mul r2, r4
	add r3, r5, r2
	ldrb r3, [r3, #0x1c]
	cmp r3, #0x0
	beq _020176A8
	cmp r3, #0x1
	beq _02017708
	cmp r3, #0x2
	beq _02017768
_020176A8:
	ldr r3, =0x0400100E
	cmp r1, #0x1
	ldrh r4, [r3, #0x0]
	add r3, sp, #0x0
	strh r4, [r3, #0x4]
	bne _020176C4
	ldrh r4, [r3, #0x4]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r4
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r3, #0x4]
	b _020176D6
_020176C4:
	cmp r1, #0x2
	bne _020176D6
	ldrh r4, [r3, #0x4]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r4, r1
	lsr r0, r0, #0x1a
	orr r0, r4
	strh r0, [r3, #0x4]
_020176D6:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x4]
	add r2, r5, r2
	ldr r6, =0x0400100E
	lsl r0, r3, #0x1a
	ldrb r4, [r2, #0x1e]
	lsr r1, r0, #0x1c
	lsl r0, r3, #0x13
	lsl r2, r3, #0x10
	lsr r3, r2, #0x1e
	ldrh r5, [r6, #0x0]
	lsr r0, r0, #0x1b
	lsl r2, r1, #0x2
	lsl r1, r0, #0x8
	lsl r0, r4, #0x7
	mov r4, #0x43
	and r4, r5
	lsl r3, r3, #0xe
	orr r3, r4
	orr r0, r3
	orr r0, r1
	orr r0, r2
	add sp, #0x20
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_02017708:
	ldr r2, =0x0400100E
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x2]
	bne _02017724
	ldrh r3, [r2, #0x2]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0x2]
	b _02017736
_02017724:
	cmp r1, #0x2
	bne _02017736
	ldrh r3, [r2, #0x2]
	mov r1, #0x3c
	lsl r0, r0, #0x1c
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0x2]
_02017736:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x2]
	ldr r6, =0x0400100E
	add sp, #0x20
	lsl r1, r3, #0x13
	lsl r0, r3, #0x1a
	lsr r4, r1, #0x1b
	lsl r1, r3, #0x12
	lsr r2, r1, #0x1f
	lsl r1, r3, #0x10
	lsr r3, r1, #0x1e
	lsr r0, r0, #0x1c
	lsl r1, r0, #0x2
	lsl r0, r4, #0x8
	ldrh r5, [r6, #0x0]
	mov r4, #0x43
	lsl r3, r3, #0xe
	and r4, r5
	orr r3, r4
	orr r0, r3
	lsl r2, r2, #0xd
	orr r0, r1
	orr r0, r2
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_02017768:
	ldr r2, =0x0400100E
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x0]
	bne _02017784
	ldrh r3, [r2, #0x0]
	ldr r1, =0xFFFFE0FF
	lsl r0, r0, #0x1b
	and r1, r3
	lsr r0, r0, #0x13
	orr r0, r1
	strh r0, [r2, #0x0]
	b _02017796
_02017784:
	cmp r1, #0x2
	bne _02017796
	ldrh r3, [r2, #0x0]
	mov r1, #0x38
	lsl r0, r0, #0x1d
	bic r3, r1
	lsr r0, r0, #0x1a
	orr r0, r3
	strh r0, [r2, #0x0]
_02017796:
	add r0, sp, #0x0
	ldrh r3, [r0, #0x0]
	ldr r6, =0x0400100E
	lsl r1, r3, #0x13
	lsr r4, r1, #0x1b
	lsl r1, r3, #0x12
	lsr r2, r1, #0x1f
	lsl r0, r3, #0x1a
	lsl r1, r3, #0x10
	lsr r3, r1, #0x1e
	lsl r1, r4, #0x8
	lsr r0, r0, #0x1d
	ldrh r5, [r6, #0x0]
	mov r4, #0x43
	lsl r3, r3, #0xe
	and r4, r5
	lsl r0, r0, #0x2
	orr r3, r4
	orr r0, r3
	lsl r2, r2, #0xd
	orr r0, r1
	orr r0, r2
	strh r0, [r6, #0x0]
_020177C4:
	add sp, #0x20
	pop {r3-r7, pc}
    // clang-format on
}
#endif

THUMB_FUNC u8 FUN_020177DC(u8 param0, u32 param1)
{
    switch (param1)
    {
    case 0:

        if (param0 == 1)
        {
            return 0;
        }
        else if (param0 == 2)
        {
            return 2;
        }
        else if (param0 == 3)
        {
            return 1;
        }
        else if (param0 == 4)
        {
            return 3;
        }
        break;

    case 1:

        if (param0 == 0)
        {
            return 0;
        }
        else if (param0 == 1)
        {
            return 1;
        }
        else if (param0 == 4)
        {
            return 2;
        }
        else if (param0 == 5)
        {
            return 3;
        }
        break;

    case 2:

        if (param0 == 0)
        {
            return 0;
        }
        else if (param0 == 1)
        {
            return 1;
        }
        else if (param0 == 4)
        {
            return 2;
        }
        else if (param0 == 5)
        {
            return 3;
        }
        break;
    }

    return 0;
}

THUMB_FUNC void FUN_02017850(u32 param0, u8 *param1, u8 *param2)
{
    switch (param0)
    {
    case 0:
        *param1 = 0x10;
        *param2 = 0x10;
        break;
    case 1:
        *param1 = 0x20;
        *param2 = 0x20;
        break;
    case 2:
        *param1 = 0x20;
        *param2 = 0x40;
        break;
    case 3:
        *param1 = 0x40;
        *param2 = 0x20;
        break;
    case 4:
        *param1 = 0x40;
        *param2 = 0x40;
        break;
    case 5:
        *param1 = 0x80;
        *param2 = 0x80;
        break;
    }
}

THUMB_FUNC void FUN_020178A0(struct UnkStruct2 *param0, u32 param1)
{
    if (param0->unk08[param1].unk08 != NULL)
    {
        FreeToHeap(param0->unk08[param1].unk08);
        param0->unk08[param1].unk08 = NULL;
    }
}

THUMB_FUNC void FUN_020178BC(u32 param0, u32 param1)
{
    switch (param0)
    {
    case 0:
        reg_G2_BG0CNT = reg_G2_BG0CNT & ~3 | param1;
        break;
    case 1:
        reg_G2_BG1CNT = reg_G2_BG1CNT & ~3 | param1;
        break;
    case 2:
        reg_G2_BG2CNT = reg_G2_BG2CNT & ~3 | param1;
        break;
    case 3:
        reg_G2_BG3CNT = reg_G2_BG3CNT & ~3 | param1;
        break;
    case 4:
        reg_G2S_DB_BG0CNT = reg_G2S_DB_BG0CNT & ~3 | param1;
        break;
    case 5:
        reg_G2S_DB_BG1CNT = reg_G2S_DB_BG1CNT & ~3 | param1;
        break;
    case 6:
        reg_G2S_DB_BG2CNT = reg_G2S_DB_BG2CNT & ~3 | param1;
        break;
    case 7:
        reg_G2S_DB_BG3CNT = reg_G2S_DB_BG3CNT & ~3 | param1;
        break;
    }
}

THUMB_FUNC void FUN_0201797C(u32 param0, GX_LayerToggle toggle)
{
    switch (param0)
    {
    case 0:
        GX_EngineAToggleLayers(1, toggle);
        break;
    case 1:
        GX_EngineAToggleLayers(2, toggle);
        break;
    case 2:
        GX_EngineAToggleLayers(4, toggle);
        break;
    case 3:
        GX_EngineAToggleLayers(8, toggle);
        break;
    case 4:
        GX_EngineBToggleLayers(1, toggle);
        break;
    case 5:
        GX_EngineBToggleLayers(2, toggle);
        break;
    case 6:
        GX_EngineBToggleLayers(4, toggle);
        break;
    case 7:
        GX_EngineBToggleLayers(8, toggle);
        break;
    }
}

extern void FUN_02017B8C(struct InnerStruct *param0, u32 param2, u32 val);
extern void FUN_02017C6C(struct UnkStruct2 *param0, u32 param1);

THUMB_FUNC void FUN_020179E0(struct UnkStruct2 *param0, u32 param1, u32 param2, u32 val)
{
    FUN_02017B8C(&param0->unk08[param1], param2, val);

    u32 r1 = param0->unk08[param1].unk14;
    u32 r0 = param0->unk08[param1].unk18;
    switch (param1)
    {
    case 0:

        reg_G2_BG0OFS = (r1 & 0x1FF) | ((r0 << 16) & 0x1FF0000);
        break;
    case 1:

        reg_G2_BG1OFS = (r1 & 0x1FF) | ((r0 << 16) & 0x1FF0000);
        break;

    case 2:
        if (param0->unk08[2].unk1c == 0)
        {
            reg_G2_BG2OFS = (r1 & 0x1FF) | ((r0 << 16) & 0x1FF0000);
        }
        else
        {
            FUN_02017C6C(param0, 2);
        }

        break;

    case 3:
        if (param0->unk08[3].unk1c == 0)
        {
            reg_G2_BG3OFS = (r1 & 0x1FF) | ((r0 << 16) & 0x1FF0000);
        }
        else
        {
            FUN_02017C6C(param0, 3);
        }

        break;

    case 4:

        reg_G2S_DB_BG0OFS = (r1 & 0x1FF) | ((r0 << 16) & 0x1FF0000);
        break;
    case 5:

        reg_G2S_DB_BG1OFS = (r1 & 0x1FF) | ((r0 << 16) & 0x1FF0000);
        break;

    case 6:
        if (param0->unk08[6].unk1c == 0)
        {
            reg_G2S_DB_BG2OFS = (r1 & 0x1FF) | ((r0 << 16) & 0x1FF0000);
        }
        else
        {
            FUN_02017C6C(param0, 6);
        }

        break;

    case 7:
        if (param0->unk08[7].unk1c == 0)
        {
            reg_G2S_DB_BG3OFS = (r1 & 0x1FF) | ((r0 << 16) & 0x1FF0000);
        }
        else
        {
            FUN_02017C6C(param0, 7);
        }

        break;
    }
}

THUMB_FUNC u32 FUN_02017B48(struct UnkStruct2 *param0, u32 param1)
{
    return param0->unk08[param1].unk14;
}

THUMB_FUNC u32 FUN_02017B54(struct UnkStruct2 *param0, u32 param1)
{
    return param0->unk08[param1].unk18;
}

extern void FUN_02017BD0(
    struct UnkStruct2 *param0, u32 param1, struct Mtx22 *param2, fx32 param3, fx32 param4);

THUMB_FUNC void FUN_02017B60(struct UnkStruct2 *param0,
    u32 param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    u32 param6)
{
    FUN_02017B8C(&param0->unk08[param1], param2, param3);
    FUN_02017BD0(param0, param1, param4, param5, param6);
}

THUMB_FUNC void FUN_02017B8C(struct InnerStruct *param0, u32 param1, u32 val)
{
    switch (param1)
    {
    case 0:
        param0->unk14 = val;
        break;
    case 1:
        param0->unk14 += val;
        break;
    case 2:
        param0->unk14 -= val;
        break;
    case 3:
        param0->unk18 = val;
        break;
    case 4:
        param0->unk18 += val;
        break;
    case 5:
        param0->unk18 -= val;
        break;
    }
}

THUMB_FUNC void FUN_02017BD0(
    struct UnkStruct2 *param0, u32 param1, struct Mtx22 *param2, fx32 param3, fx32 param4)
{
    switch (param1)
    {
    case 2:
        G2x_SetBGyAffine_(0x04000020,
            param2,
            param3,
            param4,
            param0->unk08[param1].unk14,
            param0->unk08[param1].unk18);
        break;
    case 3:
        G2x_SetBGyAffine_(0x04000030,
            param2,
            param3,
            param4,
            param0->unk08[param1].unk14,
            param0->unk08[param1].unk18);
        break;
    case 6:
        G2x_SetBGyAffine_(0x04001020,
            param2,
            param3,
            param4,
            param0->unk08[param1].unk14,
            param0->unk08[param1].unk18);
        break;
    case 7:
        G2x_SetBGyAffine_(0x04001030,
            param2,
            param3,
            param4,
            param0->unk08[param1].unk14,
            param0->unk08[param1].unk18);
        break;
    }
}

THUMB_FUNC void FUN_02017C6C(struct UnkStruct2 *param0, u32 param1)
{
    struct Mtx22 mtx;
    MTX22_2DAffine(&mtx, 0, 0x1000, 0x1000, 0);
    FUN_02017BD0(param0, param1, &mtx, 0, 0);
}

THUMB_FUNC void FUN_02017C98(const void *param0, void *param1, u32 param2)
{
    if (param2 == 0)
    {
        MI_UncompressLZ8(param0, param1);
        return;
    }

    if (((u32)param0 % 4) == 0 && ((u32)param1 % 4) == 0 && ((u16)param2 % 4) == 0)
    {
        MIi_CpuCopy32(param0, param1, param2);
        return;
    }

    MIi_CpuCopy16(param0, param1, param2);
}

extern void FUN_02017CE8(
    struct UnkStruct2 *param0, u32 param1, u32 *param2, u32 param3, u32 param4);

THUMB_FUNC void FUN_02017CD0(struct UnkStruct2 *param0, u32 param1)
{
    FUN_02017CE8(param0,
        param1,
        param0->unk08[param1].unk08,
        param0->unk08[param1].unk0c,
        param0->unk08[param1].unk10);
}

extern void FUN_02017D68(u32 param0, void *param1, u32 param2, u32 param3);

THUMB_FUNC void FUN_02017CE8(
    struct UnkStruct2 *param0, u32 param1, u32 *param2, u32 param3, u32 param4)
{
    u32 st0 = param3;
    if (param3 == 0)
    {
        void *st4 = param0->unk08[param1].unk08;
        if (st4 != 0)
        {
            FUN_02017C98(param2, st4, param3);
            FUN_02017D68(param1, st4, param0->unk08[param1].unk10 * 2, param0->unk08[param1].unk0c);
            return;
        }

        u32 r7 = param2[0] >> 8;
        void *ptr = AllocFromHeapAtEnd(param0->unk00, r7);
        FUN_02017C98(param2, ptr, st0);
        FUN_02017D68(param1, ptr, param4 * 2, r7);
        FreeToHeap(ptr);
        return;
    }

    FUN_02017D68(param1, param2, param4 * 2, param3);
}

THUMB_FUNC void FUN_02017D68(u32 param0, void *param1, u32 offset, u32 size)
{
    DC_FlushRange(param1, size);

    switch (param0)
    {
    case 0:
        GX_LoadBG0Scr(param1, offset, size);
        break;
    case 1:
        GX_LoadBG1Scr(param1, offset, size);
        break;
    case 2:
        GX_LoadBG2Scr(param1, offset, size);
        break;
    case 3:
        GX_LoadBG3Scr(param1, offset, size);
        break;
    case 4:
        GXS_LoadBG0Scr(param1, offset, size);
        break;
    case 5:
        GXS_LoadBG1Scr(param1, offset, size);
        break;
    case 6:
        GXS_LoadBG2Scr(param1, offset, size);
        break;
    case 7:
        GXS_LoadBG3Scr(param1, offset, size);
        break;
    }
}

THUMB_FUNC void FUN_02017DFC(struct UnkStruct2 *param0, u32 param1, void *param2, u32 param3)
{
    FUN_02017C98(param2, param0->unk08[param1].unk08, param3);
}

extern void FUN_02017E40(
    struct UnkStruct2 *param0, u32 param1, u32 *param2, u32 param3, u32 param4);

THUMB_FUNC void FUN_02017E14(
    struct UnkStruct2 *param0, u32 param1, u32 param2, u32 param3, u32 param4)
{
    if (param0->unk08[param1].unk1e == 0)
    {
        FUN_02017E40(param0, param1, param2, param3, param4 << 5);
        return;
    }
    FUN_02017E40(param0, param1, param2, param3, param4 << 6);
}

extern void FUN_02017E84(u32 param0, void *param1, u32 param2, u32 param3);

THUMB_FUNC void FUN_02017E40(
    struct UnkStruct2 *param0, u32 param1, u32 *param2, u32 param3, u32 param4)
{
    u32 st0 = param3;
    if (param3 == 0)
    {

        u32 r4 = param2[0] >> 8;
        void *ptr = AllocFromHeapAtEnd(param0->unk00, r4);
        FUN_02017C98(param2, ptr, st0);
        FUN_02017E84(param1, ptr, param4, r4);
        FreeToHeap(ptr);
        return;
    }

    FUN_02017E84(param1, param2, param4, param3);
}

THUMB_FUNC void FUN_02017E84(u32 param0, void *param1, u32 offset, u32 size)
{
    DC_FlushRange(param1, size);

    switch (param0)
    {
    case 0:
        GX_LoadBG0Char(param1, offset, size);
        break;
    case 1:
        GX_LoadBG1Char(param1, offset, size);
        break;
    case 2:
        GX_LoadBG2Char(param1, offset, size);
        break;
    case 3:
        GX_LoadBG3Char(param1, offset, size);
        break;
    case 4:
        GXS_LoadBG0Char(param1, offset, size);
        break;
    case 5:
        GXS_LoadBG1Char(param1, offset, size);
        break;
    case 6:
        GXS_LoadBG2Char(param1, offset, size);
        break;
    case 7:
        GXS_LoadBG3Char(param1, offset, size);
        break;
    }
}

THUMB_FUNC void FUN_02017F18(u32 param0, u32 size, u32 offset, u32 heap_id)
{
    void *ptr = AllocFromHeapAtEnd(heap_id, size);
    memset(ptr, 0, size);

    FUN_02017E84(param0, ptr, offset, size);
    FUN_02016A8C(heap_id, ptr);
}

THUMB_FUNC void FUN_02017F48(
    struct UnkStruct2 *param0, u32 param1, u32 *param2, u32 param3, u32 param4)
{
    void *st4;
    u32 st0 = param3 * param0->unk08[param1].unk1f;
    u32 r5 = param2;
    st4 = AllocFromHeapAtEnd(param0->unk00, st0);

    if (param0->unk08[param1].unk1f == 0x20)
    {
        r5 = (r5 << 0xc | r5 << 0x8 | r5 << 0x4 | r5);
        r5 |= r5 << 0x10;
    }
    else
    {
        r5 = r5 << 0x18 | r5 << 0x10 | r5 << 8 | r5;
    }

    MIi_CpuClearFast(r5, st4, st0);

    FUN_02017E84((u8)param1, st4, param0->unk08[param1].unk1f * param4, st0);
    FreeToHeap(st4);
}

THUMB_FUNC void FUN_02017FB4(u32 param0, void *param1, u32 offset, u32 size)
{
    DC_FlushRange(param1, offset);
    if (param0 < 4)
    {
        GX_LoadBGPltt(param1, size, offset);
        return;
    }

    GXS_LoadBGPltt(param1, size, offset);
}

THUMB_FUNC void FUN_02017FE4(u32 param0, u32 param1)
{
    FUN_02017FB4(param0, &param1, 2, 0);
}

THUMB_FUNC u16 FUN_02017FFC(s32 param0, s32 param1, u32 param2)
{
    switch (param2)
    {
    case 0:
        return param0 + (param1 << 4);
    case 1:
    case 2:
        return param0 + (param1 << 5);
    case 3:
        return (param0 & 0x1f) + ((param1 + (param0 & ~0x1f)) << 5);
    case 4:
        u16 res = ((u16)((param0 >> 5) + (param1 >> 5) * 2)) << 10;
        res += (param0 & 0x1f) + ((param1 & 0x1f) << 5);
        return res;
    case 5:
        return 0;
    }
}

THUMB_FUNC u16 FUN_02018068(u32 param0, u32 param1, u32 param2, u32 param3)
{
    u8 r2 = 0;
    u16 r3 = 0;
    s16 r4 = param2 - 32;
    s16 r5 = param3 - 32;

    if ((param0 >> 5) != 0)
    {
        r2++;
    }

    if ((param1 >> 5) != 0)
    {
        r2 += 2;
    }

    switch (r2)
    {
    case 0:
        if (r4 >= 0)
        {
            r3 += param0 + (param1 << 5);
        }
        else
        {
            r3 += param0 + param1 * param2;
        }
        break;
    case 1:
        if (r5 >= 0)
        {
            r3 += (1 << 0xa);
        }
        else
        {
            r3 += (param3 << 5);
        }

        r3 += (param0 & 0x1f) + param1 * r4;
        break;
    case 2:
        r3 += param2 << 5;
        if (r4 >= 0)
        {
            r3 += param0 + ((param1 & 0x1f) << 5);
        }
        else
        {
            r3 += param0 + (param1 & 0x1f) * param2;
        }
        break;
    case 3:
        r3 += (param2 + r5) << 5;
        r3 += (param0 & 0x1f) + (param1 & 0x1f) * r4;
        break;
    }

    return r3;
}


extern void FUN_02018170(struct UnkStruct2 *param0, u32 param1, u8 param2, u8 param3, u8 param4, u8 param5, u32 *param6, u8 param7, u8 param8, u8 param9, u8 param10);


THUMB_FUNC void FUN_02018148(struct UnkStruct2 *param0, u32 param1, u32 *param2, u8 param3, u8 param4, u8 param5, u8 param6) {
    FUN_02018170(param0, param1, param3, param4, param5, param6, param2, 0, 0, param5, param6);
}



extern void FUN_02018268(struct InnerStruct *param0, u8 param1, u8 param2, u8 param3, u8 param4, u32 *param5, u8 param6, u8 param7, u8 param8, u8 param9, u8 param10);
extern void FUN_020183DC(struct InnerStruct *param0, u8 param1, u8 param2, u8 param3, u8 param4, u32 *param5, u8 param6, u8 param7, u8 param8, u8 param9, u8 param10);

THUMB_FUNC void FUN_02018170(struct UnkStruct2 *param0, u32 param1, u8 param2, u8 param3, u8 param4, u8 param5, u32 *param6, u8 param7, u8 param8, u8 param9, u8 param10) {
    if (param0->unk08[param1].unk1c != 1) {
        FUN_02018268(&param0->unk08[param1], param2, param3, param4, param5, param6, param7, param8, param9, param10, 0);
    } else {
        FUN_020183DC(&param0->unk08[param1], param2, param3, param4, param5, param6, param7, param8, param9, param10, 0);
    }
}



THUMB_FUNC void FUN_020181EC(struct UnkStruct2 *param0, u32 param1, u8 param2, u8 param3, u8 param4, u8 param5, u32 *param6, u8 param7, u8 param8, u8 param9, u8 param10) {
    if (param0->unk08[param1].unk1c != 1) {
        FUN_02018268(&param0->unk08[param1], param2, param3, param4, param5, param6, param7, param8, param9, param10, 1);
    } else {
        FUN_020183DC(&param0->unk08[param1], param2, param3, param4, param5, param6, param7, param8, param9, param10, 1);
    }
}
