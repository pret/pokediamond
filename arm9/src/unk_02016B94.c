#include "global.h"
#include "unk_02016B94.h"
#include "GX_layers.h"
#include "gx.h"
#include "heap.h"

extern void FUN_020B0030(u32 param0, u32 param1);
extern void FUN_020B0138(u32 param0, u32 param1);

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

void (*const UNK_020EDB5C[])(struct Window *) = {
    FUN_020194C8,
    FUN_0201951C,
    FUN_020194C8,
};

void (*const UNK_020EDB50[])(struct Window *) = {
    FUN_020195A8,
    FUN_020195E4,
    FUN_020195A8,
};

void (*const UNK_020EDB44[])(struct Window *) = {
    FUN_020195D0,
    FUN_0201960C,
    FUN_020195D0,
};

void (*const UNK_020EDB38[])(struct Window *) = {
    FUN_020192D4,
    FUN_02019358,
    FUN_020192D4,
};

void (*const UNK_020EDB68[])(struct Window *) = {
    FUN_0201949C,
    FUN_020194E0,
    FUN_0201949C,
};

void (*const UNK_020EDB74[])(struct Window *) = {
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
THUMB_FUNC asm void FUN_02016C18(
    struct UnkStruct2 *param0, u8 param1, struct UnkStruct1 *param2, u8 param3)
{
    // clang-format off
    push {r3-r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x4]
	str r3, [sp, #0x8]
	add r4, r2, #0x0
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x10]
	ldr r1, [sp, #0x8]
	bl FUN_020177DC
	add r5, r0, #0x0
	ldr r0, [sp, #0x4]
	cmp r0, #0x7
	bls _02016C36
	b _0201705A
_02016C36:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02016C42:
    // jump table (using 16-bit offset)
	// .short _02016C52 - _02016C42 - 2; case 0
	// .short _02016CAA - _02016C42 - 2; case 1
	// .short _02016D02 - _02016C42 - 2; case 2
	// .short _02016DA4 - _02016C42 - 2; case 3
	// .short _02016E46 - _02016C42 - 2; case 4
	// .short _02016E9E - _02016C42 - 2; case 5
	// .short _02016EF6 - _02016C42 - 2; case 6
	// .short _02016F98 - _02016C42 - 2; case 7

    lsl r6, r1, #0
    lsl r6, r4, #1
    lsl r6, r7, #2
    lsl r0, r4, #5
    lsl r2, r0, #8
    lsl r2, r3, #9
    lsl r2, r6, #10
    lsl r4, r2, #13
_02016C52:
	mov r0, #0x1
	add r1, r0, #0x0
	bl GX_EngineAToggleLayers
	ldrb r3, [r4, #0x14]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x11]
	ldrb r2, [r4, #0x13]
	lsl r6, r3, #0xd
	lsl r0, r0, #0x7
	lsl r3, r2, #0x2
	str r0, [sp, #0xc]
	ldr r2, =0x04000008
	lsl r7, r1, #0x8
	ldrh r1, [r2, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r1, r0
	ldr r0, [sp, #0xc]
	orr r0, r1
	orr r0, r7
	orr r0, r3
	orr r0, r6
	strh r0, [r2, #0x0]
	ldrh r1, [r2, #0x0]
	mov r0, #0x3
	bic r1, r0
	ldrb r0, [r4, #0x15]
	orr r0, r1
	strh r0, [r2, #0x0]
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _02016CA0
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	orr r0, r1
	strh r0, [r2, #0x0]
	b _0201705A
_02016CA0:
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	bic r1, r0
	strh r1, [r2, #0x0]
	b _0201705A
_02016CAA:
	mov r0, #0x2
	mov r1, #0x1
	bl GX_EngineAToggleLayers
	ldrb r3, [r4, #0x14]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x11]
	ldrb r2, [r4, #0x13]
	lsl r6, r3, #0xd
	lsl r0, r0, #0x7
	lsl r3, r2, #0x2
	str r0, [sp, #0x10]
	ldr r2, =0x0400000A
	lsl r7, r1, #0x8
	ldrh r1, [r2, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r1, r0
	ldr r0, [sp, #0x10]
	orr r0, r1
	orr r0, r7
	orr r0, r3
	orr r0, r6
	strh r0, [r2, #0x0]
	ldrh r1, [r2, #0x0]
	mov r0, #0x3
	bic r1, r0
	ldrb r0, [r4, #0x15]
	orr r0, r1
	strh r0, [r2, #0x0]
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _02016CF8
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	orr r0, r1
	strh r0, [r2, #0x0]
	b _0201705A
_02016CF8:
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	bic r1, r0
	strh r1, [r2, #0x0]
	b _0201705A
_02016D02:
	mov r0, #0x4
	mov r1, #0x1
	bl GX_EngineAToggleLayers
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _02016D18
	cmp r0, #0x1
	beq _02016D3A
	cmp r0, #0x2
	beq _02016D5C
_02016D18:
	ldrb r1, [r4, #0x12]
	ldr r7, =0x0400000C
	ldrb r2, [r4, #0x13]
	lsl r3, r1, #0x8
	ldrb r0, [r4, #0x11]
	lsl r6, r2, #0x2
	ldrh r1, [r7, #0x0]
	lsl r2, r0, #0x7
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016D7C
_02016D3A:
	ldrb r2, [r4, #0x13]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x16]
	lsl r3, r2, #0x2
	ldr r7, =0x0400000C
	lsl r2, r1, #0x8
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016D7C
_02016D5C:
	ldrb r1, [r4, #0x12]
	ldr r7, =0x0400000C
	ldrb r0, [r4, #0x16]
	lsl r3, r1, #0x8
	ldrb r2, [r4, #0x13]
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	lsl r2, r2, #0x2
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
_02016D7C:
	ldr r0, =0x0400000C
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	ldrb r1, [r4, #0x15]
	orr r1, r2
	strh r1, [r0, #0x0]
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	beq _02016D9A
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0201705A
_02016D9A:
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	bic r2, r1
	strh r2, [r0, #0x0]
	b _0201705A
_02016DA4:
	mov r0, #0x8
	mov r1, #0x1
	bl GX_EngineAToggleLayers
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _02016DBA
	cmp r0, #0x1
	beq _02016DDC
	cmp r0, #0x2
	beq _02016DFE
_02016DBA:
	ldrb r1, [r4, #0x12]
	ldr r7, =0x0400000E
	ldrb r2, [r4, #0x13]
	lsl r3, r1, #0x8
	ldrb r0, [r4, #0x11]
	lsl r6, r2, #0x2
	ldrh r1, [r7, #0x0]
	lsl r2, r0, #0x7
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016E1E
_02016DDC:
	ldrb r2, [r4, #0x13]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x16]
	lsl r3, r2, #0x2
	ldr r7, =0x0400000E
	lsl r2, r1, #0x8
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016E1E
_02016DFE:
	ldrb r1, [r4, #0x12]
	ldr r7, =0x0400000E
	ldrb r0, [r4, #0x16]
	lsl r3, r1, #0x8
	ldrb r2, [r4, #0x13]
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	lsl r2, r2, #0x2
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
_02016E1E:
	ldr r0, =0x0400000E
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	ldrb r1, [r4, #0x15]
	orr r1, r2
	strh r1, [r0, #0x0]
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	beq _02016E3C
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0201705A
_02016E3C:
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	bic r2, r1
	strh r2, [r0, #0x0]
	b _0201705A
_02016E46:
	mov r0, #0x1
	add r1, r0, #0x0
	bl GX_EngineBToggleLayers
	ldrb r3, [r4, #0x14]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x11]
	ldrb r2, [r4, #0x13]
	lsl r6, r3, #0xd
	lsl r0, r0, #0x7
	lsl r3, r2, #0x2
	str r0, [sp, #0x14]
	ldr r2, =0x04001008
	lsl r7, r1, #0x8
	ldrh r1, [r2, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r1, r0
	ldr r0, [sp, #0x14]
	orr r0, r1
	orr r0, r7
	orr r0, r3
	orr r0, r6
	strh r0, [r2, #0x0]
	ldrh r1, [r2, #0x0]
	mov r0, #0x3
	bic r1, r0
	ldrb r0, [r4, #0x15]
	orr r0, r1
	strh r0, [r2, #0x0]
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _02016E94
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	orr r0, r1
	strh r0, [r2, #0x0]
	b _0201705A
_02016E94:
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	bic r1, r0
	strh r1, [r2, #0x0]
	b _0201705A
_02016E9E:
	mov r0, #0x2
	mov r1, #0x1
	bl GX_EngineBToggleLayers
	ldrb r2, [r4, #0x13]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x11]
	lsl r6, r2, #0x2
	ldrb r3, [r4, #0x14]
	lsl r0, r0, #0x7
	mov r12, r0
	ldr r2, =0x0400100A
	lsl r7, r1, #0x8
	ldrh r1, [r2, #0x0]
	mov r0, #0x43
	lsl r3, r3, #0xd
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	mov r1, r12
	orr r0, r1
	orr r0, r7
	orr r0, r6
	orr r0, r3
	strh r0, [r2, #0x0]
	ldrh r1, [r2, #0x0]
	mov r0, #0x3
	bic r1, r0
	ldrb r0, [r4, #0x15]
	orr r0, r1
	strh r0, [r2, #0x0]
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _02016EEC
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	orr r0, r1
	strh r0, [r2, #0x0]
	b _0201705A
_02016EEC:
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	bic r1, r0
	strh r1, [r2, #0x0]
	b _0201705A
_02016EF6:
	mov r0, #0x4
	mov r1, #0x1
	bl GX_EngineBToggleLayers
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _02016F0C
	cmp r0, #0x1
	beq _02016F2E
	cmp r0, #0x2
	beq _02016F50
_02016F0C:
	ldrb r1, [r4, #0x12]
	ldr r7, =0x0400100C
	ldrb r2, [r4, #0x13]
	lsl r3, r1, #0x8
	ldrb r0, [r4, #0x11]
	lsl r6, r2, #0x2
	ldrh r1, [r7, #0x0]
	lsl r2, r0, #0x7
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016F70
_02016F2E:
	ldrb r2, [r4, #0x13]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x16]
	lsl r3, r2, #0x2
	ldr r7, =0x0400100C
	lsl r2, r1, #0x8
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016F70
_02016F50:
	ldrb r1, [r4, #0x12]
	ldr r7, =0x0400100C
	ldrb r0, [r4, #0x16]
	lsl r3, r1, #0x8
	ldrb r2, [r4, #0x13]
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	lsl r2, r2, #0x2
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
_02016F70:
	ldr r0, =0x0400100C
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	ldrb r1, [r4, #0x15]
	orr r1, r2
	strh r1, [r0, #0x0]
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	beq _02016F8E
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0201705A
_02016F8E:
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	bic r2, r1
	strh r2, [r0, #0x0]
	b _0201705A
_02016F98:
	mov r0, #0x8
	mov r1, #0x1
	bl GX_EngineBToggleLayers
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _02016FAE
	cmp r0, #0x1
	beq _02016FF2
	cmp r0, #0x2
	beq _02017014
_02016FAE:
	ldrb r1, [r4, #0x12]
	ldr r7, =0x0400100E
	b _02016FD4
_02016FD4:
	ldrb r2, [r4, #0x13]
	lsl r3, r1, #0x8
	ldrb r0, [r4, #0x11]
	lsl r6, r2, #0x2
	ldrh r1, [r7, #0x0]
	lsl r2, r0, #0x7
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02017034
_02016FF2:
	ldrb r2, [r4, #0x13]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x16]
	lsl r3, r2, #0x2
	ldr r7, =0x0400100E
	lsl r2, r1, #0x8
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02017034
_02017014:
	ldrb r1, [r4, #0x12]
	ldr r7, =0x0400100E
	ldrb r0, [r4, #0x16]
	lsl r3, r1, #0x8
	ldrb r2, [r4, #0x13]
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	lsl r2, r2, #0x2
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
_02017034:
	ldr r0, =0x0400100E
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	ldrb r1, [r4, #0x15]
	orr r1, r2
	strh r1, [r0, #0x0]
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	beq _02017052
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0201705A
_02017052:
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	bic r2, r1
	strh r2, [r0, #0x0]
_0201705A:
	ldr r0, [sp, #0x4]
	mov r1, #0x2c
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	mul r5, r1
	add r2, r0, r5
	mov r3, #0x0
	mov r0, #0x1
	strh r3, [r2, #0x20]
	lsl r0, r0, #0xc
	str r0, [r2, #0x24]
	str r0, [r2, #0x28]
	str r3, [r2, #0x2c]
	str r3, [r2, #0x30]
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	beq _020170A2
	ldr r0, [sp, #0x0]
	ldr r6, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r6, #0x8
	bl AllocFromHeap
	str r0, [r6, r5]
	ldr r1, [r6, r5]
	ldr r2, [r4, #0x8]
	mov r0, #0x0
	bl MIi_CpuClear16
	ldr r0, [sp, #0x0]
	ldr r2, [r4, #0x8]
	add r1, r0, r5
	str r2, [r1, #0xc]
	ldr r0, [r4, #0xc]
	str r0, [r1, #0x10]
	b _020170A8
_020170A2:
	str r3, [r2, #0x8]
	str r3, [r2, #0xc]
	str r3, [r2, #0x10]
_020170A8:
	ldr r0, [sp, #0x0]
	ldrb r1, [r4, #0x10]
	add r0, r0, r5
	strb r1, [r0, #0x1d]
	ldr r1, [sp, #0x8]
	strb r1, [r0, #0x1c]
	ldrb r1, [r4, #0x11]
	strb r1, [r0, #0x1e]
	ldr r1, [sp, #0x8]
	cmp r1, #0x0
	bne _020170CA
	ldrb r1, [r4, #0x11]
	cmp r1, #0x0
	bne _020170CA
	mov r1, #0x20
	strb r1, [r0, #0x1f]
	b _020170D2
_020170CA:
	ldr r0, [sp, #0x0]
	mov r1, #0x40
	add r0, r0, r5
	strb r1, [r0, #0x1f]
_020170D2:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r3, [r4, #0x0]
	mov r2, #0x0
	bl FUN_020179E0
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r3, [r4, #0x4]
	mov r2, #0x3
	bl FUN_020179E0
	add sp, #0x18
	pop {r3-r7, pc}
    // clang-format on
}
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

THUMB_FUNC void FUN_02017CD0(struct UnkStruct2 *param0, u32 param1)
{
    FUN_02017CE8(param0,
        param1,
        param0->unk08[param1].unk08,
        param0->unk08[param1].unk0c,
        param0->unk08[param1].unk10);
}

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

THUMB_FUNC u16 FUN_02017FFC(u8 param0, u8 param1, u8 param2)
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

THUMB_FUNC u16 FUN_02018068(u8 param0, u8 param1, u8 param2, u8 param3)
{
    u8 r2 = 0;
    u16 r3 = 0;
    s16 r4 = param2 - 32;
    s16 r5 = param3 - 32;

    if (((u32)param0 >> 5) != 0)
    {
        r2++;
    }

    if (((u32)param1 >> 5) != 0)
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

THUMB_FUNC void FUN_02018148(
    struct UnkStruct2 *param0, u32 param1, u32 *param2, u8 param3, u8 param4, u8 param5, u8 param6)
{
    FUN_02018170(param0, param1, param3, param4, param5, param6, param2, 0, 0, param5, param6);
}

THUMB_FUNC void FUN_02018170(struct UnkStruct2 *param0,
    u32 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u32 *param6,
    u8 param7,
    u8 param8,
    u8 param9,
    u8 param10)
{
    if (param0->unk08[param1].unk1c != 1)
    {
        FUN_02018268(&param0->unk08[param1],
            param2,
            param3,
            param4,
            param5,
            param6,
            param7,
            param8,
            param9,
            param10,
            0);
    }
    else
    {
        FUN_020183DC(&param0->unk08[param1],
            param2,
            param3,
            param4,
            param5,
            param6,
            param7,
            param8,
            param9,
            param10,
            0);
    }
}

THUMB_FUNC void FUN_020181EC(struct UnkStruct2 *param0,
    u32 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u32 *param6,
    u8 param7,
    u8 param8,
    u8 param9,
    u8 param10)
{
    if (param0->unk08[param1].unk1c != 1)
    {
        FUN_02018268(&param0->unk08[param1],
            param2,
            param3,
            param4,
            param5,
            param6,
            param7,
            param8,
            param9,
            param10,
            1);
    }
    else
    {
        FUN_020183DC(&param0->unk08[param1],
            param2,
            param3,
            param4,
            param5,
            param6,
            param7,
            param8,
            param9,
            param10,
            1);
    }
}

THUMB_FUNC void FUN_02018268(struct InnerStruct *param0,
    u8 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u16 *param5,
    u8 param6,
    u8 param7,
    u8 param8,
    u8 param9,
    u8 param10)
{
    void *st2c = param0->unk08;

    if (st2c == 0)
    {
        return;
    }

    u8 st41;
    u8 st40;
    FUN_02017850(param0->unk1d, &st41, &st40);

    u8 i;
    u8 j;
    if (param10 == 0)
    {
        for (i = 0; i < param4; i++)
        {

            if (param2 + i >= st40)
            {
                break;
            }

            if (param7 + i >= param9)
            {
                break;
            }

            for (j = 0; j < param3; j++)
            {

                if (param1 + j >= st41)
                {
                    break;
                }

                if (param6 + j >= param8)
                {
                    break;
                }

                ((u16 *)st2c)[FUN_02017FFC(param1 + j, param2 + i, param0->unk1d)] =
                    param5[param6 + param8 * (param7 + i) + j];
            }
        }
    }
    else
    {
        for (i = 0; i < param4; i++)
        {

            if (param2 + i >= st40)
            {
                break;
            }

            if (param7 + i >= param9)
            {
                break;
            }

            for (j = 0; j < param3; j++)
            {

                if (param1 + j >= st41)
                {
                    break;
                }

                if (param6 + j >= param8)
                {
                    break;
                }

                ((u16 *)st2c)[FUN_02017FFC(param1 + j, param2 + i, param0->unk1d)] =
                    param5[FUN_02018068(param6 + j, param7 + i, param8, param9)];
            }
        }
    }
}

THUMB_FUNC void FUN_020183DC(struct InnerStruct *param0,
    u8 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 *param5,
    u8 param6,
    u8 param7,
    u8 param8,
    u8 param9,
    u8 param10)
{
    void *st2c = param0->unk08;

    if (st2c == 0)
    {
        return;
    }

    u8 st41;
    u8 st40;
    FUN_02017850(param0->unk1d, &st41, &st40);

    u8 i;
    u8 j;
    if (param10 == 0)
    {
        for (i = 0; i < param4; i++)
        {

            if (param2 + i >= st40)
            {
                break;
            }

            if (param7 + i >= param9)
            {
                break;
            }

            for (j = 0; j < param3; j++)
            {

                if (param1 + j >= st41)
                {
                    break;
                }

                if (param6 + j >= param8)
                {
                    break;
                }

                ((u8 *)st2c)[FUN_02017FFC(param1 + j, param2 + i, param0->unk1d)] =
                    param5[param6 + param8 * (param7 + i) + j];
            }
        }
    }
    else
    {
        for (i = 0; i < param4; i++)
        {

            if (param2 + i >= st40)
            {
                break;
            }

            if (param7 + i >= param9)
            {
                break;
            }

            for (j = 0; j < param3; j++)
            {

                if (param1 + j >= st41)
                {
                    break;
                }

                if (param6 + j >= param8)
                {
                    break;
                }

                ((u8 *)st2c)[FUN_02017FFC(param1 + j, param2 + i, param0->unk1d)] =
                    param5[FUN_02018068(param6 + j, param7 + i, param8, param9)];
            }
        }
    }
}

THUMB_FUNC void FUN_02018540(struct UnkStruct2 *param0,
    u32 param1,
    u16 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u8 param6,
    u8 param7)
{
    if (param0->unk08[param1].unk1c != 1)
    {

        FUN_02018590(&param0->unk08[param1], param2, param3, param4, param5, param6, param7);
    }
    else
    {
        FUN_02018640(&param0->unk08[param1], param2, param3, param4, param5, param6);
    }
}

THUMB_FUNC void FUN_02018590(
    struct InnerStruct *param0, u16 param1, u8 param2, u8 param3, u8 param4, u8 param5, u8 param6)
{
    void *r4 = param0->unk08;

    if (r4 != 0)
    {

        u8 st19;
        u8 st18;
        FUN_02017850(param0->unk1d, &st19, &st18);

        u8 i;
        u8 j;
        for (i = param3; i < param3 + param5; i++)
        {
            if (i >= st18)
            {
                break;
            }

            for (j = param2; j < param2 + param4; j++)
            {
                if (j >= st19)
                {
                    break;
                }

                u16 idx = FUN_02017FFC(j, i, param0->unk1d);

                if (param6 == 0x11)
                {
                    ((u16 *)r4)[idx] = param1;
                }
                else if (param6 == 0x10)
                {
                    ((u16 *)r4)[idx] = (((u16 *)r4)[idx] & 0xF000) + param1;
                }
                else
                {
                    ((u16 *)r4)[idx] = (param6 << 0xc) + param1;
                }
            }
        }
    }
}

THUMB_FUNC void FUN_02018640(
    struct InnerStruct *param0, u8 param1, u8 param2, u8 param3, u8 param4, u8 param5)
{
    void *r4 = param0->unk08;

    if (r4 != 0)
    {

        u8 st19;
        u8 st18;
        FUN_02017850(param0->unk1d, &st19, &st18);

        u8 i;
        u8 j;
        for (i = param3; i < param3 + param5; i++)
        {
            if (i >= st18)
            {
                break;
            }

            for (j = param2; j < param2 + param4; j++)
            {
                if (j >= st19)
                {
                    break;
                }

                ((u8 *)r4)[FUN_02017FFC(j, i, param0->unk1d)] = param1;
            }
        }
    }
}

THUMB_FUNC void FUN_020186B4(
    struct UnkStruct2 *param0, u32 param1, u8 param2, u8 param3, u8 param4, u8 param5, u8 param6)
{
    void *r4 = param0->unk08[param1].unk08;

    if (r4 != NULL)
    {
        u8 st11;
        u8 st10;
        FUN_02017850(param0->unk08[param1].unk1d, &st11, &st10);

        u8 i;
        u8 j;
        for (i = param3; i < param3 + param5; i++)
        {
            if (i >= st10)
            {
                break;
            }

            for (j = param2; j < param2 + param4; j++)
            {
                if (j >= st11)
                {
                    break;
                }

                u16 idx = FUN_02017FFC(j, i, param0->unk08[param1].unk1d);
                ((u16 *)r4)[idx] = (((u16 *)r4)[idx] & 0xfff) | (param6 << 0xc);
            }
        }
    }
}

THUMB_FUNC void FUN_02018744(struct UnkStruct2 *param0, u32 param1)
{
    if (param0->unk08[param1].unk08 != NULL)
    {
        MIi_CpuClear16(0, param0->unk08[param1].unk08, param0->unk08[param1].unk0c);
        FUN_02017CD0(param0, param1);
    }
}

THUMB_FUNC void FUN_02018768(struct UnkStruct2 *param0, u32 param1, u16 param2)
{
    if (param0->unk08[param1].unk08 != NULL)
    {
        MIi_CpuClear16(param2, param0->unk08[param1].unk08, param0->unk08[param1].unk0c);
        FUN_02017CD0(param0, param1);
    }
}

THUMB_FUNC void FUN_0201878C(struct UnkStruct2 *param0, u32 param1, u16 param2)
{
    if (param0->unk08[param1].unk08 != NULL)
    {
        MIi_CpuClear16(param2, param0->unk08[param1].unk08, param0->unk08[param1].unk0c);
        FUN_0201AC68(param0, param1);
    }
}

THUMB_FUNC void *FUN_020187B0(u32 param0)
{
    switch (param0)
    {
    case 0:
        return G2_GetBG0CharPtr();
    case 1:
        return G2_GetBG1CharPtr();
    case 2:
        return G2_GetBG2CharPtr();
    case 3:
        return G2_GetBG3CharPtr();
    case 4:
        return G2S_GetBG0CharPtr();
    case 5:
        return G2S_GetBG1CharPtr();
    case 6:
        return G2S_GetBG2CharPtr();
    case 7:
        return G2S_GetBG3CharPtr();
    }

    return NULL;
}

THUMB_FUNC void FUN_02018808(u8 *param0, u32 param1, u8 (*param2)[2], u8 param3)
{
    param3 = param3 << 4;
    for (int i = 0; i < param1; i++)
    {
        param2[i][0] = param0[i] & 0xf;
        if (param2[i][0] != 0)
        {
            param2[i][0] += param3;
        }

        param2[i][1] = (param0[i] >> 4) & 0xf;
        if (param2[i][1] != 0)
        {
            param2[i][1] += param3;
        }
    }
}

THUMB_FUNC u8 (*FUN_02018848(u8 *param0, u32 param1, u8 param2, u32 heap_id))[2]
{
    u8(*ptr)[2] = (u8(*)[2])AllocFromHeap(heap_id, param1 * 2);

    FUN_02018808(param0, param1, ptr, param2);

    return ptr;
}

THUMB_FUNC void *FUN_0201886C(struct UnkStruct2 *param0, u32 param1)
{
    return param0->unk08[param1].unk08;
}

THUMB_FUNC u16 FUN_02018878(struct UnkStruct2 *param0, u32 param1)
{
    return param0->unk08[param1].unk20;
}

#ifdef NONMATCHING
THUMB_FUNC u8 FUN_02018884(struct UnkStruct2 *param0, u32 param1)
{

    // the compiler keeps optimizing the stack away :(
    u16 st0[16];
    switch (param1)
    {
    case 0:
        st0[15] = reg_G2_BG0CNT;
        return (u32)(st0[15] << 0x1e) >> 0x1e;
    case 1:
        st0[14] = reg_G2_BG1CNT;
        return (u32)(st0[14] << 0x1e) >> 0x1e;

    case 2:
        switch (param0->unk08[param1].unk1c)
        {
        default:
        case 0:
            st0[13] = reg_G2_BG2CNT;
            return (u32)(st0[13] << 0x1e) >> 0x1e;
        case 1:
            st0[12] = reg_G2_BG2CNT;
            return (u32)(st0[12] << 0x1e) >> 0x1e;
        case 2:
            st0[11] = reg_G2_BG2CNT;
            return (u32)(st0[11] << 0x1e) >> 0x1e;
        }
        break;
    case 3:
        switch (param0->unk08[param1].unk1c)
        {
        default:
        case 0:
            st0[10] = reg_G2_BG3CNT;
            return (u32)(st0[10] << 0x1e) >> 0x1e;
        case 1:
            st0[9] = reg_G2_BG3CNT;
            return (u32)(st0[9] << 0x1e) >> 0x1e;
        case 2:
            st0[8] = reg_G2_BG3CNT;
            return (u32)(st0[8] << 0x1e) >> 0x1e;
        }
        break;

    case 4:
        st0[7] = reg_G2S_DB_BG0CNT;
        return (u32)(st0[7] << 0x1e) >> 0x1e;
    case 5:
        st0[6] = reg_G2S_DB_BG1CNT;
        return (u32)(st0[6] << 0x1e) >> 0x1e;

    case 6:
        switch (param0->unk08[param1].unk1c)
        {
        default:
        case 0:
            st0[5] = reg_G2S_DB_BG2CNT;
            return (u32)(st0[5] << 0x1e) >> 0x1e;
        case 1:
            st0[4] = reg_G2S_DB_BG2CNT;
            return (u32)(st0[4] << 0x1e) >> 0x1e;
        case 2:
            st0[3] = reg_G2S_DB_BG2CNT;
            return (u32)(st0[3] << 0x1e) >> 0x1e;
        }
        break;
    case 7:
        switch (param0->unk08[param1].unk1c)
        {
        default:
        case 0:
            st0[2] = reg_G2S_DB_BG3CNT;
            return (u32)(st0[2] << 0x1e) >> 0x1e;
        case 1:
            st0[1] = reg_G2S_DB_BG3CNT;
            return (u32)(st0[1] << 0x1e) >> 0x1e;
        case 2:
            st0[0] = reg_G2S_DB_BG3CNT;
            return (u32)(st0[0] << 0x1e) >> 0x1e;
        }
        break;
    }

    return 0;
}
#else
THUMB_FUNC asm u8 FUN_02018884(struct UnkStruct2 *param0, u32 param1)
{
    // clang-format off
	sub sp, #0x20
	cmp r1, #0x7
	bls _0201888C
	b _02018A38
_0201888C:
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02018898:
    // jump table (using 16-bit offset)
	// .short _020188A8 - _02018898 - 2; case 0
	// .short _020188BC - _02018898 - 2; case 1
	// .short _020188D0 - _02018898 - 2; case 2
	// .short _02018920 - _02018898 - 2; case 3
	// .short _02018970 - _02018898 - 2; case 4
	// .short _02018984 - _02018898 - 2; case 5
	// .short _02018998 - _02018898 - 2; case 6
	// .short _020189E8 - _02018898 - 2; case 7

    lsl r6, r1, #0
    lsl r2, r4, #0
    lsl r6, r6, #0
    lsl r6, r0, #2
    lsl r6, r2, #3
    lsl r2, r5, #3
    lsl r6, r7, #3
    lsl r6, r1, #5
_020188A8:
	ldr r0, =0x04000008
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x1e]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_020188BC:
	ldr r0, =0x0400000A
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x1c]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_020188D0:
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0x1c]
	cmp r0, #0x0
	beq _020188E4
	cmp r0, #0x1
	beq _020188F8
	cmp r0, #0x2
	beq _0201890C
_020188E4:
	ldr r0, =0x0400000C
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x1a]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_020188F8:
	ldr r0, =0x0400000C
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x18]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_0201890C:
	ldr r0, =0x0400000C
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x16]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_02018920:
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0x1c]
	cmp r0, #0x0
	beq _02018934
	cmp r0, #0x1
	beq _02018948
	cmp r0, #0x2
	beq _0201895C
_02018934:
	ldr r0, =0x0400000E
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x14]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_02018948:
	ldr r0, =0x0400000E
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x12]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_0201895C:
	ldr r0, =0x0400000E
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x10]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_02018970:
	ldr r0, =0x04001008
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0xe]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_02018984:
	ldr r0, =0x0400100A
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0xc]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_02018998:
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0x1c]
	cmp r0, #0x0
	beq _020189AC
	cmp r0, #0x1
	beq _020189C0
	cmp r0, #0x2
	beq _020189D4
_020189AC:
	ldr r0, =0x0400100C
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0xa]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_020189C0:
	ldr r0, =0x0400100C
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x8]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_020189D4:
	ldr r0, =0x0400100C
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x6]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_020189E8:
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0x1c]
	cmp r0, #0x0
	beq _020189FC
	cmp r0, #0x1
	beq _02018A10
	cmp r0, #0x2
	beq _02018A24
_020189FC:
	ldr r0, =0x0400100E
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x4]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_02018A10:
	ldr r0, =0x0400100E
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x2]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_02018A24:
	ldr r0, =0x0400100E
	ldrh r1, [r0, #0x0]
	add r0, sp, #0x0
	add sp, #0x20
	strh r1, [r0, #0x0]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_02018A38:
	mov r0, #0x0
	add sp, #0x20
	bx lr
    // clang-format on
}
#endif

#ifdef NONMATCHING
THUMB_FUNC void FUN_02018A60(struct UnkStruct3 *param0,
    struct UnkStruct3 *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8)
{

    u8 *unk1;
    u8 *unk2;

    int st50;
    if (param1->unk04 - param4 < param6)
    {
        st50 = param2 + param1->unk04 - param4;
    }
    else
    {
        st50 = param2 + param6;
    }

    int st4c;
    if (param1->unk06 - param5 < param7)
    {
        st4c = param3 + param1->unk06 - param5;
    }
    else
    {
        st4c = param3 + param7;
    }

    int st48 = (param0->unk04 + (param0->unk04 & 7)) >> 3;

    int st44 = (param1->unk04 + (param1->unk04 & 7)) >> 3;

    u32 i, i1;
    u32 j, j1;
    if (param8 == 0xFFFF)
    {
        i1 = param5;
        for (i = param3; i < st4c; i++)
        {
            j1 = param4;
            for (j = param2; j < st50; j++)
            {

                unk1 =
                    (u32)(param1->unk00) + (j1 >> 1) &
                    0x3 + ((j1 << 2) & 0x3fe0) + st44 * ((i1 << 2) & 0x3fe0) + ((i1 << 2) & 0x1c);
                unk2 = (u32)(param0->unk00) + (j >> 1) &
                       0x3 + ((j << 2) & 0x3fe0) + st48 * ((i << 2) & 0x3FE0) + ((i << 2) & 0x1c);

                u8 r1 = *unk2;

                u32 r2 = (j1 << 0x1f) >> 0x1d;
                u32 r7 = ((r1 >> ((j << 0x1f) >> 0x1d)) & 0xf) << r2;

                *unk1 = r7 | (*unk1 & (0xf0 >> r2));

                j1++;
            }
            i1++;
        }
    }
    else
    {

        i1 = param5;
        for (i = param3; i < st4c; i++)
        {
            j1 = param4;
            for (j = param2; j < st50; j++)
            {

                unk1 = (u32)param1->unk00 + ((j1 >> 1) & 3) + ((j1 << 2) & 0x3fe0) +
                           st44 * ((i1 << 2) & 0x3fe0) + (i1 << 2) &
                       0x1c;
                unk2 = (u32)param0->unk00 + ((j >> 1) & 3) + ((j << 2) & 0x3fe0) +
                       st48 * ((i << 2) & 0x3fe0) + ((i << 2) & 0x1c);
                u8 r0 = ((*unk2) >> ((j << 0x1f) >> 0x1d)) & 0xf;

                if (r0 != param8)
                {
                    u32 r7 = ((j1 << 0x1f) >> 0x1d);
                    *unk1 = (r0 << r7) | (*unk1 & (0xf0 >> r7));
                }

                j1++;
            }
            i1++;
        }
    }
}
#else
THUMB_FUNC asm void FUN_02018A60(struct UnkStruct3 *param0,
    struct UnkStruct3 *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8)
{
    // clang-format off
	push {r3-r7, lr}
	sub sp, #0x68
	str r2, [sp, #0x8]
	str r3, [sp, #0xc]
	add r2, sp, #0x70
	str r0, [sp, #0x0]
	ldrh r0, [r2, #0x10]
	str r1, [sp, #0x4]
	ldrh r2, [r2, #0x18]
	str r0, [sp, #0x10]
	add r0, r1, #0x0
	ldrh r1, [r0, #0x4]
	ldr r0, [sp, #0x10]
	sub r3, r1, r0
	cmp r3, r2
	bge _02018A88
	ldr r0, [sp, #0x8]
	add r0, r0, r3
	str r0, [sp, #0x50]
	b _02018A8E
_02018A88:
	ldr r0, [sp, #0x8]
	add r0, r2, r0
	str r0, [sp, #0x50]
_02018A8E:
	ldr r2, [sp, #0x4]
	add r3, sp, #0x70
	ldrh r0, [r3, #0x14]
	ldrh r2, [r2, #0x6]
	ldrh r3, [r3, #0x1c]
	sub r4, r2, r0
	cmp r4, r3
	bge _02018AA6
	ldr r2, [sp, #0xc]
	add r2, r2, r4
	str r2, [sp, #0x4c]
	b _02018AAC
_02018AA6:
	ldr r2, [sp, #0xc]
	add r2, r3, r2
	str r2, [sp, #0x4c]
_02018AAC:
	ldr r2, [sp, #0x0]
	mov r3, #0x7
	ldrh r4, [r2, #0x4]
	add r2, r4, #0x0
	and r2, r3
	add r2, r4, r2
	asr r2, r2, #0x3
	str r2, [sp, #0x48]
	add r2, r1, #0x0
	and r2, r3
	add r1, r1, r2
	asr r1, r1, #0x3
	str r1, [sp, #0x44]
	add r1, sp, #0x70
	ldrh r1, [r1, #0x20]
	ldr r2, =0x0000FFFF
	str r1, [sp, #0x38]
	cmp r1, r2
	bne _02018BB4
	ldr r2, [sp, #0xc]
	ldr r1, [sp, #0x4c]
	cmp r2, r1
	bge _02018ADE
	cmp r2, r1
	blt _02018AE0
_02018ADE:
	b _02018C92
_02018AE0:
	add r1, r2, #0x0
	lsl r1, r1, #0x2
	lsl r0, r0, #0x2
	str r1, [sp, #0x28]
	str r0, [sp, #0x24]
_02018AEA:
	ldr r3, [sp, #0x8]
	ldr r0, [sp, #0x50]
	add r1, r3, #0x0
	ldr r4, [sp, #0x10]
	cmp r1, r0
	bge _02018B96
	cmp r1, r0
	bge _02018B96
	add r0, r3, #0x0
	lsl r5, r0, #0x2
	add r0, r4, #0x0
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x48]
	and r1, r0
	mul r2, r1
	str r2, [sp, #0x20]
	ldr r2, [sp, #0x28]
	mov r1, #0x1c
	and r2, r1
	str r2, [sp, #0x1c]
	ldr r2, [sp, #0x24]
	and r0, r2
	ldr r2, [sp, #0x44]
	mul r2, r0
	ldr r0, [sp, #0x24]
	str r2, [sp, #0x18]
	and r0, r1
	str r0, [sp, #0x14]
_02018B26:
	ldr r0, [sp, #0x4]
	asr r2, r4, #0x1
	mov r1, #0x3
	ldr r0, [r0, #0x0]
	and r1, r2
	add r1, r0, r1
	ldr r0, =0x00003FE0
	and r0, r6
	add r1, r1, r0
	ldr r0, [sp, #0x18]
	add r6, r6, #0x4
	add r0, r1, r0
	str r0, [sp, #0x64]
	lsl r0, r4, #0x1f
	lsr r2, r0, #0x1d
	ldr r0, [sp, #0x0]
	asr r1, r3, #0x1
	ldr r7, [r0, #0x0]
	mov r0, #0x3
	and r0, r1
	ldr r1, =0x00003FE0
	add r4, r4, #0x1
	and r1, r5
	str r1, [sp, #0x54]
	add r1, r7, r0
	ldr r0, [sp, #0x54]
	add r5, r5, #0x4
	add r1, r0, r1
	ldr r0, [sp, #0x20]
	add r1, r0, r1
	ldr r0, [sp, #0x1c]
	ldrb r1, [r0, r1]
	lsl r0, r3, #0x1f
	lsr r0, r0, #0x1d
	asr r1, r0
	mov r0, #0xf
	and r0, r1
	add r7, r0, #0x0
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x64]
	lsl r7, r2
	ldrb r0, [r0, r1]
	add r3, r3, #0x1
	str r0, [sp, #0x58]
	mov r0, #0xf0
	asr r0, r2
	ldr r1, [sp, #0x58]
	add r2, r7, #0x0
	and r0, r1
	orr r2, r0
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x64]
	strb r2, [r0, r1]
	ldr r0, [sp, #0x50]
	cmp r3, r0
	blt _02018B26
_02018B96:
	ldr r0, [sp, #0x28]
	add r0, r0, #0x4
	str r0, [sp, #0x28]
	ldr r0, [sp, #0xc]
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0xc]
	add r0, r0, #0x4
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x4c]
	cmp r1, r0
	blt _02018AEA
	add sp, #0x68
	pop {r3-r7, pc}
_02018BB4:
	ldr r2, [sp, #0xc]
	ldr r1, [sp, #0x4c]
	cmp r2, r1
	bge _02018C92
	cmp r2, r1
	bge _02018C92
	add r1, r2, #0x0
	lsl r1, r1, #0x2
	lsl r0, r0, #0x2
	str r1, [sp, #0x40]
	str r0, [sp, #0x3c]
_02018BCA:
	ldr r3, [sp, #0x8]
	ldr r0, [sp, #0x50]
	add r1, r3, #0x0
	ldr r4, [sp, #0x10]
	cmp r1, r0
	bge _02018C78
	cmp r1, r0
	bge _02018C78
	add r0, r3, #0x0
	lsl r1, r0, #0x2
	add r0, r4, #0x0
	lsl r2, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x40]
	ldr r6, [sp, #0x48]
	and r5, r0
	mul r6, r5
	str r6, [sp, #0x34]
	ldr r6, [sp, #0x40]
	mov r5, #0x1c
	and r6, r5
	str r6, [sp, #0x30]
	ldr r6, [sp, #0x3c]
	and r0, r6
	ldr r6, [sp, #0x44]
	mul r6, r0
	ldr r0, [sp, #0x3c]
	str r6, [sp, #0x2c]
	and r0, r5
	str r0, [sp, #0x60]
_02018C06:
	ldr r0, [sp, #0x4]
	asr r6, r4, #0x1
	mov r5, #0x3
	and r5, r6
	ldr r0, [r0, #0x0]
	asr r6, r3, #0x1
	add r5, r0, r5
	ldr r0, =0x00003FE0
	and r0, r2
	add r5, r5, r0
	ldr r0, [sp, #0x2c]
	add r5, r5, r0
	ldr r0, [sp, #0x0]
	ldr r7, [r0, #0x0]
	mov r0, #0x3
	and r0, r6
	ldr r6, =0x00003FE0
	and r6, r1
	str r6, [sp, #0x5c]
	add r6, r7, r0
	ldr r0, [sp, #0x5c]
	add r6, r0, r6
	ldr r0, [sp, #0x34]
	add r6, r0, r6
	ldr r0, [sp, #0x30]
	ldrb r6, [r0, r6]
	lsl r0, r3, #0x1f
	lsr r0, r0, #0x1d
	asr r6, r0
	mov r0, #0xf
	and r0, r6
	ldr r6, [sp, #0x38]
	cmp r0, r6
	beq _02018C6A
	lsl r6, r4, #0x1f
	lsr r7, r6, #0x1d
	lsl r0, r7
	mov lr, r0
	ldr r0, [sp, #0x60]
	ldrb r0, [r5, r0]
	mov r12, r0
	mov r0, #0xf0
	add r6, r0, #0x0
	asr r6, r7
	mov r0, r12
	and r0, r6
	mov r6, lr
	orr r6, r0
	ldr r0, [sp, #0x60]
	strb r6, [r5, r0]
_02018C6A:
	ldr r0, [sp, #0x50]
	add r3, r3, #0x1
	add r1, r1, #0x4
	add r2, r2, #0x4
	add r4, r4, #0x1
	cmp r3, r0
	blt _02018C06
_02018C78:
	ldr r0, [sp, #0x40]
	add r0, r0, #0x4
	str r0, [sp, #0x40]
	ldr r0, [sp, #0xc]
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x3c]
	ldr r1, [sp, #0xc]
	add r0, r0, #0x4
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x4c]
	cmp r1, r0
	blt _02018BCA
_02018C92:
	add sp, #0x68
	pop {r3-r7, pc}
    // clang-format on
}
#endif

#ifdef NONMATCHING
THUMB_FUNC void FUN_02018CA0(struct UnkStruct3 *param0,
    struct UnkStruct3 *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8)
{
    // horrible for loops like the one above
}
#else
THUMB_FUNC asm void FUN_02018CA0(struct UnkStruct3 *param0,
    struct UnkStruct3 *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8)
{
    // clang-format off
	push {r3-r7, lr}
	sub sp, #0x50
	str r2, [sp, #0x8]
	str r3, [sp, #0xc]
	add r2, sp, #0x58
	str r0, [sp, #0x0]
	ldrh r0, [r2, #0x10]
	str r1, [sp, #0x4]
	ldrh r2, [r2, #0x18]
	str r0, [sp, #0x10]
	add r0, r1, #0x0
	ldrh r1, [r0, #0x4]
	ldr r0, [sp, #0x10]
	sub r3, r1, r0
	cmp r3, r2
	bge _02018CC6
	ldr r0, [sp, #0x8]
	add r0, r0, r3
	b _02018CCA
_02018CC6:
	ldr r0, [sp, #0x8]
	add r0, r2, r0
_02018CCA:
	ldr r2, [sp, #0x4]
	add r3, sp, #0x58
	mov r12, r0
	ldrh r0, [r3, #0x14]
	ldrh r2, [r2, #0x6]
	ldrh r3, [r3, #0x1c]
	sub r4, r2, r0
	cmp r4, r3
	bge _02018CE2
	ldr r2, [sp, #0xc]
	add r2, r2, r4
	b _02018CE6
_02018CE2:
	ldr r2, [sp, #0xc]
	add r2, r3, r2
_02018CE6:
	mov lr, r2
	ldr r2, [sp, #0x0]
	mov r3, #0x7
	ldrh r4, [r2, #0x4]
	add r2, r4, #0x0
	and r2, r3
	add r2, r4, r2
	asr r2, r2, #0x3
	str r2, [sp, #0x4c]
	add r2, r1, #0x0
	and r2, r3
	add r1, r1, r2
	asr r1, r1, #0x3
	str r1, [sp, #0x48]
	add r1, sp, #0x58
	ldrh r1, [r1, #0x20]
	ldr r2, =0x0000FFFF
	str r1, [sp, #0x3c]
	cmp r1, r2
	bne _02018DC6
	ldr r2, [sp, #0xc]
	mov r1, lr
	cmp r2, r1
	bge _02018D1C
	mov r1, lr
	cmp r2, r1
	blt _02018D1E
_02018D1C:
	b _02018E7C
_02018D1E:
	add r1, r2, #0x0
	lsl r1, r1, #0x3
	lsl r0, r0, #0x3
	str r1, [sp, #0x28]
	str r0, [sp, #0x24]
_02018D28:
	ldr r1, [sp, #0x8]
	mov r0, r12
	add r2, r1, #0x0
	ldr r7, [sp, #0x10]
	cmp r2, r0
	bge _02018DA8
	mov r0, r12
	cmp r2, r0
	bge _02018DA8
	add r0, r1, #0x0
	lsl r2, r0, #0x3
	add r0, r7, #0x0
	lsl r3, r0, #0x3
	ldr r6, =0x00007FC0
	ldr r0, [sp, #0x28]
	ldr r4, [sp, #0x4c]
	and r0, r6
	mul r4, r0
	str r4, [sp, #0x20]
	ldr r0, [sp, #0x28]
	mov r5, #0x38
	and r0, r5
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x24]
	ldr r4, [sp, #0x48]
	and r0, r6
	mul r4, r0
	ldr r0, [sp, #0x24]
	str r4, [sp, #0x18]
	and r0, r5
	str r0, [sp, #0x14]
_02018D66:
	ldr r0, [sp, #0x0]
	add r5, r1, #0x0
	mov r4, #0x7
	and r5, r4
	ldr r0, [r0, #0x0]
	ldr r4, =0x00007FC0
	add r0, r0, r5
	and r4, r2
	add r4, r4, r0
	ldr r0, [sp, #0x20]
	add r5, r7, #0x0
	add r4, r0, r4
	ldr r0, [sp, #0x1c]
	add r1, r1, #0x1
	ldrb r6, [r0, r4]
	ldr r0, [sp, #0x4]
	mov r4, #0x7
	and r5, r4
	ldr r0, [r0, #0x0]
	ldr r4, =0x00007FC0
	add r0, r0, r5
	and r4, r3
	add r4, r4, r0
	ldr r0, [sp, #0x18]
	add r2, #0x8
	add r4, r0, r4
	ldr r0, [sp, #0x14]
	add r3, #0x8
	strb r6, [r0, r4]
	mov r0, r12
	add r7, r7, #0x1
	cmp r1, r0
	blt _02018D66
_02018DA8:
	ldr r0, [sp, #0x28]
	add r0, #0x8
	str r0, [sp, #0x28]
	ldr r0, [sp, #0xc]
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0xc]
	add r0, #0x8
	str r0, [sp, #0x24]
	mov r0, lr
	cmp r1, r0
	blt _02018D28
	add sp, #0x50
	pop {r3-r7, pc}
_02018DC6:
	ldr r2, [sp, #0xc]
	mov r1, lr
	cmp r2, r1
	bge _02018E7C
	mov r1, lr
	cmp r2, r1
	bge _02018E7C
	add r1, r2, #0x0
	lsl r1, r1, #0x3
	lsl r0, r0, #0x3
	str r1, [sp, #0x44]
	str r0, [sp, #0x40]
_02018DDE:
	ldr r2, [sp, #0x8]
	mov r0, r12
	add r1, r2, #0x0
	ldr r3, [sp, #0x10]
	cmp r1, r0
	bge _02018E62
	mov r0, r12
	cmp r1, r0
	bge _02018E62
	add r0, r2, #0x0
	lsl r6, r0, #0x3
	add r0, r3, #0x0
	lsl r1, r0, #0x3
	ldr r7, =0x00007FC0
	ldr r0, [sp, #0x44]
	ldr r4, [sp, #0x4c]
	and r0, r7
	mul r4, r0
	str r4, [sp, #0x38]
	ldr r0, [sp, #0x44]
	mov r5, #0x38
	and r0, r5
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x40]
	ldr r4, [sp, #0x48]
	and r0, r7
	mul r4, r0
	ldr r0, [sp, #0x40]
	str r4, [sp, #0x30]
	and r0, r5
	str r0, [sp, #0x2c]
_02018E1C:
	ldr r0, [sp, #0x4]
	mov r4, #0x7
	ldr r0, [r0, #0x0]
	and r4, r3
	add r0, r0, r4
	ldr r4, =0x00007FC0
	add r5, r2, #0x0
	and r4, r1
	add r4, r0, r4
	ldr r0, [sp, #0x30]
	add r7, r4, r0
	ldr r0, [sp, #0x0]
	mov r4, #0x7
	and r5, r4
	ldr r0, [r0, #0x0]
	ldr r4, =0x00007FC0
	add r0, r0, r5
	and r4, r6
	add r4, r4, r0
	ldr r0, [sp, #0x38]
	add r4, r0, r4
	ldr r0, [sp, #0x34]
	ldrb r0, [r0, r4]
	ldr r4, [sp, #0x3c]
	cmp r0, r4
	beq _02018E54
	ldr r4, [sp, #0x2c]
	strb r0, [r7, r4]
_02018E54:
	add r2, r2, #0x1
	mov r0, r12
	add r6, #0x8
	add r1, #0x8
	add r3, r3, #0x1
	cmp r2, r0
	blt _02018E1C
_02018E62:
	ldr r0, [sp, #0x44]
	add r0, #0x8
	str r0, [sp, #0x44]
	ldr r0, [sp, #0xc]
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x40]
	ldr r1, [sp, #0xc]
	add r0, #0x8
	str r0, [sp, #0x40]
	mov r0, lr
	cmp r1, r0
	blt _02018DDE
_02018E7C:
	add sp, #0x50
	pop {r3-r7, pc}
    // clang-format on
}
#endif

THUMB_FUNC void FUN_02018E88(
    struct UnkStruct3 *param0, u16 param1, u16 param2, u16 param3, u16 param4, u8 param5)
{

    int r6 = param1 + param3;
    if (r6 > param0->unk04)
    {
        r6 = param0->unk04;
    }

    int r12 = param2 + param4;
    if (r12 > param0->unk06)
    {
        r12 = param0->unk06;
    }

    int lr = (((param0->unk04) + (param0->unk04 & 7)) >> 3);

    for (int i = param2; i < r12; i++)
    {

        for (int j = param1; j < r6; j++)
        {

            u8 *unk = (u8 *)((u8 *)param0->unk00 + ((j >> 1) & 3) + ((j << 2) & 0x3fe0) +
                             (((i << 2) & 0x3fe0) * lr) + ((i << 2) & 0x1c));

            if ((j & 1) != 0)
            {
                *unk &= 0xf;
                *unk |= (param5 << 4);
            }
            else
            {
                *unk &= 0xf0;
                *unk |= param5;
            }
        }
    }
}

THUMB_FUNC void FUN_02018F4C(
    struct UnkStruct3 *param0, u16 param1, u16 param2, u16 param3, u16 param4, u8 param5)
{

    int r6 = param1 + param3;
    if (r6 > param0->unk04)
    {
        r6 = param0->unk04;
    }

    int r12 = param2 + param4;
    if (r12 > param0->unk06)
    {
        r12 = param0->unk06;
    }

    int lr = (((param0->unk04) + (param0->unk04 & 7)) >> 3);

    for (int i = param2; i < r12; i++)
    {

        for (int j = param1; j < r6; j++)
        {

            u8 *unk = (u8 *)((u8 *)param0->unk00 + (j & 7) + ((j << 3) & 0x7fc0) +
                             (((i << 3) & 0x7fc0) * lr) + ((i << 3) & 0x38));

            *unk = param5;
        }
    }
}

THUMB_FUNC void *FUN_02018FF4(u32 heap_id, s32 size)
{
    struct Window *ptr = AllocFromHeap(heap_id, size << 4);

    for (u16 i = 0; i < size; i++)
    {
        FUN_0201901C(&ptr[i]);
    }

    return ptr;
}

THUMB_FUNC void FUN_0201901C(struct Window *param0)
{
    param0->unk00 = 0;
    param0->unk04 = 0xff;
    param0->unk05 = 0;
    param0->unk06 = 0;
    param0->unk07 = 0;
    param0->unk08 = 0;
    param0->unk09 = 0;

    param0->unk0a = 0;
    param0->unk0c = 0;

    param0->unk0b = 0;
}

THUMB_FUNC BOOL FUN_02019048(struct Window *param0)
{
    if (param0->unk00 == 0 || param0->unk04 == 0xff || param0->unk0c == 0)
    {
        return FALSE;
    }

    return TRUE;
}

enum UnkEnum1
{
    UnkEnum1_0 = 0,
    UnkEnum1_1 = 1
};

THUMB_FUNC void FUN_02019064(struct UnkStruct2 *param0,
    struct Window *param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u8 param6,
    u8 param7,
    u16 param8)
{
    if (param0->unk08[param2].unk08 == NULL)
    {
        return;
    }

    void *ptr = AllocFromHeap(param0->unk00, param5 * param6 * param0->unk08[param2].unk1f);

    if (ptr == NULL)
    {
        return;
    }
    param1->unk00 = param0;
    param1->unk04 = param2;
    param1->unk05 = param3;
    param1->unk06 = param4;
    param1->unk07 = param5;
    param1->unk08 = param6;
    param1->unk09 = param7;

    param1->unk0a = param8;
    param1->unk0c = ptr;

    enum UnkEnum1 r2;
    if (param0->unk08[param2].unk1e == 0)
    {
        r2 = UnkEnum1_0;
    }
    else
    {
        r2 = UnkEnum1_1;
    }

    param1->unk0b = r2;
}

THUMB_FUNC void FUN_020190EC(
    struct UnkStruct2 *param0, struct Window *param1, u8 param2, u8 param3, u16 param4, u8 param5)
{
    u32 size = param2 * param3 * 32;

    void *ptr = AllocFromHeap(param0->unk00, size);

    param5 |= (param5 * 16);
    memset(ptr, param5, size);

    if (ptr != NULL)
    {
        param1->unk00 = param0;
        param1->unk07 = param2;
        param1->unk08 = param3;
        param1->unk0a = param4;
        param1->unk0c = ptr;
        param1->unk0b = 0;
    }
}

THUMB_FUNC void FUN_02019150(
    struct UnkStruct2 *param0, struct Window *param1, struct UnkStruct4 *param2)
{

    FUN_02019064(param0,
        param1,
        param2->unk0,
        param2->unk1,
        param2->unk2,
        param2->unk3,
        param2->unk4,
        param2->unk5,
        param2->unk6);
}

THUMB_FUNC void FUN_02019178(struct Window *param0)
{
    FreeToHeap(param0->unk0c);

    param0->unk00 = 0;
    param0->unk04 = 0xff;
    param0->unk05 = 0;
    param0->unk06 = 0;
    param0->unk07 = 0;
    param0->unk08 = 0;
    param0->unk09 = 0;
    param0->unk0a = 0;
    param0->unk0c = 0;
}

THUMB_FUNC void FUN_020191A4(struct Window *param0, int param1)
{
    for (u16 i = 0; i < param1; i++)
    {
        if (param0[i].unk0c != NULL)
        {
            FreeToHeap(param0[i].unk0c);
        }
    }

    FreeToHeap(param0);
}

THUMB_FUNC void CopyWindowToVram(struct Window *param0)
{

    GF_ASSERT(param0);
    GF_ASSERT(param0->unk00);
    GF_ASSERT(param0->unk04 < 8);
    GF_ASSERT(param0->unk00->unk08[param0->unk04].unk1c < 3);

    UNK_020EDB68[param0->unk00->unk08[param0->unk04].unk1c](param0);
}

THUMB_FUNC void FUN_02019220(struct Window *param0)
{

    GF_ASSERT(param0);
    GF_ASSERT(param0->unk00);
    GF_ASSERT(param0->unk04 < 8);
    GF_ASSERT(param0->unk00->unk08[param0->unk04].unk1c < 3);

    UNK_020EDB5C[param0->unk00->unk08[param0->unk04].unk1c](param0);
}

THUMB_FUNC void FUN_02019270(struct Window *param0)
{
    UNK_020EDB38[param0->unk00->unk08[param0->unk04].unk1c](param0);
}

THUMB_FUNC void FUN_0201928C(struct Window *param0, u8 param1, u8 param2)
{
    u8 unk07 = param0->unk07;
    u8 unk08 = param0->unk08;

    param0->unk07 = param1;
    param0->unk08 = param2;
    UNK_020EDB38[param0->unk00->unk08[param0->unk04].unk1c](param0);

    param0->unk07 = unk07;
    param0->unk08 = unk08;
}

THUMB_FUNC void FUN_020192B8(struct Window *param0)
{
    UNK_020EDB74[param0->unk00->unk08[param0->unk04].unk1c](param0);
}

THUMB_FUNC void FUN_020192D4(struct Window *param0)
{
    u32 i, j;
    u32 r3;
    u32 iCount, jCount;
    u16 *st4 = param0->unk00->unk08[param0->unk04].unk08;

    if (st4 == NULL)
    {
        return;
    }

    r3 = param0->unk0a;
    jCount = param0->unk05 + param0->unk07;
    iCount = param0->unk06 + param0->unk08;

    for (i = param0->unk06; i < iCount; i++)
    {
        for (j = param0->unk05; j < jCount; j++)
        {
            st4[((i & 0x20) * 32) + ((j & 0x20) * 32) + ((i & 0x1f) << 5) + (j & 0x1f)] =
                (r3 | (param0->unk09 << 12));

            r3++;
        }
    }
}

THUMB_FUNC void FUN_02019358(struct Window *param0)
{
    int j, i;
    u8 *r4;

    int r5;
    int r6;

    if (param0->unk00->unk08[param0->unk04].unk08 == NULL)
    {
        return;
    }

    r6 = UNK_020EDB30[param0->unk00->unk08[param0->unk04].unk1d];

    r4 = param0->unk00->unk08[param0->unk04].unk08 + param0->unk06 * r6 + param0->unk05;
    r5 = param0->unk0a;

    for (i = 0; i < param0->unk08; i++)
    {
        for (j = 0; j < param0->unk07; j++)
        {
            r4[j] = r5;
            r5++;
        }
        r4 += r6;
    }
}

THUMB_FUNC void FUN_020193B4(struct Window *param0)
{

    u32 i, j;

    u32 iCount, jCount;
    u32 st8;

    u16 *st4;

    if (param0->unk00->unk08[param0->unk04].unk08 == NULL)
    {
        return;
    }
    st4 = param0->unk00->unk08[param0->unk04].unk08;

    st8 = UNK_020EDB30[param0->unk00->unk08[param0->unk04].unk1d];
    jCount = param0->unk05 + param0->unk07;
    iCount = param0->unk06 + param0->unk08;

    for (i = param0->unk06; i < iCount; i++)
    {
        for (j = param0->unk05; j < jCount; j++)
        {
            st4[((i & 0x20) * 32) + ((j & 0x20) * 32) + ((i & 0x1f) * st8) + (j & 0x1f)] = 0;
        }
    }
}

THUMB_FUNC void FUN_02019444(struct Window *param0)
{

    int j, i;
    u8 *r5;

    int r6;

    if (param0->unk00->unk08[param0->unk04].unk08 == NULL)
    {
        return;
    }

    r6 = UNK_020EDB30[param0->unk00->unk08[param0->unk04].unk1d];
    r5 = param0->unk00->unk08[param0->unk04].unk08 + param0->unk06 * r6 + param0->unk05;

    for (i = 0; i < param0->unk08; i++)
    {
        for (j = 0; j < param0->unk07; j++)
        {
            r5[j] = 0;
        }
        r5 += r6;
    }
}

THUMB_FUNC void FUN_0201949C(struct Window *window)
{
    FUN_020192D4(window);
    FUN_02019548(window);
    FUN_02017CE8(window->unk00,
        window->unk04,
        window->unk00->unk08[window->unk04].unk08,
        window->unk00->unk08[window->unk04].unk0c,
        window->unk00->unk08[window->unk04].unk10);
}

THUMB_FUNC void FUN_020194C8(struct Window *window)
{
    FUN_020192D4(window);
    FUN_0201AC68(window->unk00, window->unk04);
    FUN_02019548(window);
}

THUMB_FUNC void FUN_020194E0(struct Window *window)
{
    FUN_02019358(window);
    FUN_02017CE8(window->unk00,
        window->unk04,
        window->unk00->unk08[window->unk04].unk08,
        window->unk00->unk08[window->unk04].unk0c,
        window->unk00->unk08[window->unk04].unk10);

    FUN_02017E14(window->unk00,
        window->unk04,
        window->unk0c,
        window->unk07 * window->unk08 * 64,
        window->unk0a);
}

THUMB_FUNC void FUN_0201951C(struct Window *window)
{
    FUN_02019358(window);
    FUN_0201AC68(window->unk00, window->unk04);
    FUN_02017E14(window->unk00,
        window->unk04,
        window->unk0c,
        window->unk07 * window->unk08 * 64,
        window->unk0a);
}

THUMB_FUNC void FUN_02019548(struct Window *window)
{
    FUN_02017E14(window->unk00,
        window->unk04,
        window->unk0c,
        window->unk07 * window->unk08 * window->unk00->unk08[window->unk04].unk1f,
        window->unk0a);
}

THUMB_FUNC void FUN_02019570(struct Window *window)
{
    UNK_020EDB50[window->unk00->unk08[window->unk04].unk1c](window);
}

THUMB_FUNC void FUN_0201958C(struct Window *window)
{
    UNK_020EDB44[window->unk00->unk08[window->unk04].unk1c](window);
}

THUMB_FUNC void FUN_020195A8(struct Window *window)
{
    FUN_020193B4(window);
    FUN_02017CE8(window->unk00,
        window->unk04,
        window->unk00->unk08[window->unk04].unk08,
        window->unk00->unk08[window->unk04].unk0c,
        window->unk00->unk08[window->unk04].unk10);
}

THUMB_FUNC void FUN_020195D0(struct Window *window)
{
    FUN_020193B4(window);
    FUN_0201AC68(window->unk00, window->unk04);
}

THUMB_FUNC void FUN_020195E4(struct Window *window)
{
    FUN_02019444(window);
    FUN_02017CE8(window->unk00,
        window->unk04,
        window->unk00->unk08[window->unk04].unk08,
        window->unk00->unk08[window->unk04].unk0c,
        window->unk00->unk08[window->unk04].unk10);
}

THUMB_FUNC void FUN_0201960C(struct Window *window)
{
    FUN_02019444(window);
    FUN_0201AC68(window->unk00, window->unk04);
}

THUMB_FUNC void FUN_02019620(struct Window *window, u8 param1)
{
    if (window->unk00->unk08[window->unk04].unk1f == 0x20)
    {
        param1 |= param1 << 4;
    }

    MIi_CpuClearFast((param1 << 0x18) | (param1 << 0x10) | (param1 << 0x8) | param1,
        window->unk0c,
        window->unk00->unk08[window->unk04].unk1f * window->unk07 * window->unk08);
}

THUMB_FUNC void FUN_02019658(struct Window *window,
    void *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8,
    u16 param9)
{
    FUN_02019684(window, param1, param2, param3, param4, param5, param6, param7, param8, param9, 0);
}

THUMB_FUNC void FUN_02019684(struct Window *window,
    void *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8,
    u16 param9,
    u16 param10)
{
    struct UnkStruct3 st1c = { param1, param4, param5 };
    struct UnkStruct3 st14 = { window->unk0c, window->unk07 << 3, window->unk08 << 3 };

    if (window->unk00->unk08[window->unk04].unk1e == 0)
    {
        FUN_02018A60(&st1c, &st14, param2, param3, param6, param7, param8, param9, param10);
    }
    else
    {
        FUN_02018CA0(&st1c, &st14, param2, param3, param6, param7, param8, param9, param10);
    }
}

THUMB_FUNC void FUN_020196F4(
    struct Window *window, u8 param1, u16 param2, u16 param3, u16 param4, u16 param5)
{
    struct UnkStruct3 st8 = { window->unk0c, window->unk07 << 3, window->unk08 << 3 };

    if (window->unk00->unk08[window->unk04].unk1e == 0)
    {
        FUN_02018E88(&st8, param2, param3, param4, param5, param1);
    }
    else
    {
        FUN_02018F4C(&st8, param2, param3, param4, param5, param1);
    }
}

#ifdef NONMATCHING
THUMB_FUNC void FUN_0201974C(
    struct Window *window, u32 *param1, u32 param2, u32 param3, u16 param4, u16 param5, u32 param6)
{
    u32 str330 = param6;
    u32 *st0 = param1;
    u16 st5c = param4;

    void *st278 = window->unk0c;
    u16 st58 = window->unk07 << 3;

    int st8 = st58 - st5c;

    if (st8 >= param2)
    {
        st8 = param2;
    }

    int st4 = (u16)(window->unk08 << 3) - param5;
    u16 st48 = param5;

    if (st4 >= param3)
    {
        st4 = param3;
    }

    u8 r4 = 0;
    if (st8 > 8)
    {
        r4 |= 1;
    }

    if (st4 > 8)
    {
        r4 |= 2;
    }

    if (window->unk0b == 0)
    {
        switch (r4)
        {
        case 0:
            u8 st70 = param6;
            for (u32 st274 = 0; st274 < st4; st274++)
            {
                u32 st6c = (st58 + (st58 & 7)) >> 3;

                u32 st26c = st0[0];
                u8 st270 = (u8)((st70 >> st274) & 1);
                u32 r2 = st5c;

                for (u32 r1 = 0; r1 < st8; r1++)
                {
                    u32 r3 = st5c << 2;
                    u32 st68 = ((st48 << 2) & 0x3fe0) * st6c;
                    u32 r7 = (st48 << 2) & 0x1c;
                    u32 st64 = (((st48 + 1) << 2) & 0x3fe0) * st6c;
                    u32 st60 = ((st48 + 1) << 2) & 0x1c;
                    u32 r4 = r1;

                    void *st27c = st278 + ((r2 >> 1) & 3) + (r3 & 0x3fe0);
                    u8 *r0 = st27c + st68;

                    u8 r5 = (u8)((st26c >> r4) & 0xf);
                    if (r5 != 0)
                    {
                        u32 st280 = (r5 << ((r2 & 1) << 2));
                        u32 st284 = r0[r7];

                        u8 r5 = ((0xf0 >> ((r2 & 1) << 2)) & st284) | st280;
                        r0[r7] = r5;

                        if (st270 != 0)
                        {
                            *(u8 *)(st27c + st64 + st60) = r5;
                        }
                    }

                    r4 += 4;
                    r3 += 4;
                    r2 += 1;
                }

                if (st270 != 0)
                {
                    st48 += 2;
                }
                else
                {
                    st48++;
                }

                st0++;
            }

            break;

        case 1:
            u32 *st25c = st0;
            u32 st264 = st48;
            u8 st54 = param6;
            u8 st84 = param6;

            for (u32 st268 = 0; st268 < st4; st268++)
            {
                u32 st80 = (st58 + (st58 & 7)) >> 3;

                u32 st258 = *st25c;
                u32 r2 = st5c;
                u8 st260 = (st84 >> st268) & 1;
                u32 r3 = st5c << 2;
                u32 st7c = ((st264 << 2) & 0x3fe0) * st80;
                u32 r7 = (st264 << 2) & 0x1c;
                u32 st78 = (((st264 + 1) << 2) & 0x3fe0) * st80;
                u32 st74 = ((st264 + 1) << 2) & 0x1c;
                u32 r4 = 0;

                for (u32 r1 = 0; r1 < 8; r1++)
                {
                    void *st288 = st278 + ((r2 >> 1) & 3) + (r3 & 0x3fe0);
                    u8 *r0 = st288 + st7c;
                    u8 r5 = (st258 >> r4) & 0xf;
                    if (r5 != 0)
                    {
                        u32 st28c = r5 << ((r2 & 1) << 2);
                        u32 st290 = r0[r7];
                        u8 r5 = ((0xf0 >> ((r2 & 1) << 2)) & st290) | st28c;
                        r0[r7] = r5;

                        if (st260 != 0)
                        {
                            *(u8 *)(st288 + st78 + st74) = r5;
                        }
                    }

                    r4 += 4;
                    r3 += 4;
                    r2++;
                }

                if (st260 != 0)
                {
                    st264 += 2;
                }
                else
                {
                    st264++;
                }

                st25c++;
            }

            st0 += 0x20;
            u8 st98 = st54;

            for (u32 st254 = 0; st254 < st4; st254++)
            {
                st5c += 8;
                u32 st94 = (st58 + (st58 & 7)) >> 3;

                //_02019A00
            }

            break;

        case 2:
            // TODO
            break;
        case 3:
            // TODO
            break;
        }
    }
    else
    {
        // TODO: FUN_0201A12C
    }
}
#else
asm void FUN_0201974C(
    struct Window *window, u32 *param1, u32 param2, u32 param3, u16 param4, u16 param5, u32 param6)
{
    // clang-format off
	push {r4-r7, lr}
	sub sp, #0x1fc
	sub sp, #0x118
	add r5, r0, #0x0
	ldr r0, [sp, #0x330]
	str r1, [sp, #0x0]
	str r0, [sp, #0x330]
	add r1, sp, #0x318
	ldrh r1, [r1, #0x10]
	ldr r0, [r5, #0xc]
	str r1, [sp, #0x5c]
	ldrb r1, [r5, #0x7]
	str r0, [sp, #0x278]
	ldrb r0, [r5, #0x8]
	lsl r1, r1, #0x13
	lsr r4, r1, #0x10
	ldr r1, [sp, #0x5c]
	lsl r0, r0, #0x13
	sub r1, r4, r1
	lsr r0, r0, #0x10
	str r4, [sp, #0x58]
	str r1, [sp, #0x8]
	cmp r1, r2
	blt _0201977E
	str r2, [sp, #0x8]
_0201977E:
	add r1, sp, #0x318
	ldrh r1, [r1, #0x14]
	sub r0, r0, r1
	str r1, [sp, #0x48]
	str r0, [sp, #0x4]
	cmp r0, r3
	blt _0201978E
	str r3, [sp, #0x4]
_0201978E:
	ldr r0, [sp, #0x8]
	mov r4, #0x0
	cmp r0, #0x8
	ble _0201979E
	mov r0, #0x1
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_0201979E:
	ldr r0, [sp, #0x4]
	cmp r0, #0x8
	ble _020197AC
	mov r0, #0x2
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_020197AC:
	ldrh r0, [r5, #0xa]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1f
	beq _020197B8
	bl FUN_0201A12C
_020197B8:
	cmp r4, #0x3
	bls _020197C0
	bl FUN_0201A8BC
_020197C0:
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020197CC:
	lsl r6, r0, #0
	lsl r0, r1, #4
	lsl r0, r3, #12
	lsl r0, r7, #20
	// jump table (using 16-bit offset)
	// .short _020197D4 - _020197CC - 2; case 0
	// .short _020198D6 - _020197CC - 2; case 1
	// .short _02019AE6 - _020197CC - 2; case 2
	// .short _02019D06 - _020197CC - 2; case 3
_020197D4:
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x70]
	mov r0, #0x0
	str r0, [sp, #0x274]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bgt _020197EA
	bl FUN_0201A8BC
_020197EA:
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x6c]
_020197F6:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x70]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x26c]
	ldr r0, [sp, #0x274]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x270]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	cmp r0, #0x0
	ble _020198AA
	ble _020198AA
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x6c]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0x68]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x6c]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0x64]
	str r0, [sp, #0x60]
_02019848:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0x68]
	str r5, [sp, #0x27c]
	add r0, r5, r0
	ldr r5, [sp, #0x26c]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _0201989C
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x280]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x284]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x284]
	and r6, r5
	ldr r5, [sp, #0x280]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x270]
	cmp r0, #0x0
	beq _0201989C
	ldr r6, [sp, #0x27c]
	ldr r0, [sp, #0x64]
	add r6, r6, r0
	ldr r0, [sp, #0x60]
	strb r5, [r0, r6]
_0201989C:
	ldr r0, [sp, #0x8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019848
_020198AA:
	ldr r0, [sp, #0x270]
	cmp r0, #0x0
	beq _020198B8
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _020198BE
_020198B8:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_020198BE:
	ldr r0, [sp, #0x0]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x274]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x274]
	cmp r1, r0
	blt _020197F6
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
_020198D6:
	ldr r0, [sp, #0x0]
	str r0, [sp, #0x25c]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x264]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x54]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x84]
	mov r0, #0x0
	str r0, [sp, #0x268]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _020199D2
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x80]
_02019902:
	ldr r0, [sp, #0x25c]
	ldr r1, [sp, #0x84]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x258]
	ldr r0, [sp, #0x268]
	ldr r6, [sp, #0x80]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x260]
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x264]
	mov r1, #0x0
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x264]
	str r6, [sp, #0x7c]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x80]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0x78]
	str r0, [sp, #0x74]
_0201994C:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0x7c]
	str r5, [sp, #0x288]
	add r0, r5, r0
	ldr r5, [sp, #0x258]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _020199A0
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x28c]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x290]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x290]
	and r6, r5
	ldr r5, [sp, #0x28c]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x260]
	cmp r0, #0x0
	beq _020199A0
	ldr r6, [sp, #0x288]
	ldr r0, [sp, #0x78]
	add r6, r6, r0
	ldr r0, [sp, #0x74]
	strb r5, [r0, r6]
_020199A0:
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, #0x8
	blt _0201994C
	ldr r0, [sp, #0x260]
	cmp r0, #0x0
	beq _020199BA
	ldr r0, [sp, #0x264]
	add r0, r0, #0x2
	str r0, [sp, #0x264]
	b _020199C0
_020199BA:
	ldr r0, [sp, #0x264]
	add r0, r0, #0x1
	str r0, [sp, #0x264]
_020199C0:
	ldr r0, [sp, #0x25c]
	add r0, r0, #0x4
	str r0, [sp, #0x25c]
	ldr r0, [sp, #0x268]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x268]
	cmp r1, r0
	blt _02019902
_020199D2:
	ldr r0, [sp, #0x0]
	add r0, #0x20
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x54]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x98]
	mov r0, #0x0
	str r0, [sp, #0x254]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bgt _020199EE
	bl FUN_0201A8BC
_020199EE:
	ldr r0, [sp, #0x5c]
	mov r1, #0x7
	add r0, #0x8
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x94]
_02019A00:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x98]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x24c]
	ldr r0, [sp, #0x254]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x250]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	str r0, [sp, #0x294]
	sub r0, #0x8
	str r0, [sp, #0x294]
	cmp r0, #0x0
	ble _02019ABA
	ble _02019ABA
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x94]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0x90]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x94]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0x8c]
	str r0, [sp, #0x88]
_02019A58:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0x90]
	str r5, [sp, #0x298]
	add r0, r5, r0
	ldr r5, [sp, #0x24c]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019AAC
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x29c]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2a0]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2a0]
	and r6, r5
	ldr r5, [sp, #0x29c]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x250]
	cmp r0, #0x0
	beq _02019AAC
	ldr r6, [sp, #0x298]
	ldr r0, [sp, #0x8c]
	add r6, r6, r0
	ldr r0, [sp, #0x88]
	strb r5, [r0, r6]
_02019AAC:
	ldr r0, [sp, #0x294]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019A58
_02019ABA:
	ldr r0, [sp, #0x250]
	cmp r0, #0x0
	beq _02019AC8
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _02019ACE
_02019AC8:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_02019ACE:
	ldr r0, [sp, #0x0]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x254]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x254]
	cmp r1, r0
	blt _02019A00
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
_02019AE6:
	ldr r0, [sp, #0x0]
	mov r1, #0x7
	str r0, [sp, #0x23c]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x244]
	mov r0, #0x0
	str r0, [sp, #0x248]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xa8]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x40]
_02019B06:
	ldr r0, [sp, #0x23c]
	ldr r1, [sp, #0xa8]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x238]
	ldr r0, [sp, #0x248]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x240]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	cmp r0, #0x0
	ble _02019BC2
	ble _02019BC2
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x244]
	ldr r6, [sp, #0x40]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x244]
	str r6, [sp, #0xa4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x40]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xa0]
	str r0, [sp, #0x9c]
_02019B58:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
// 	b _02019B6C
// 	nop
// _02019B68: .word 0x00003FE0
// _02019B6C:
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xa4]
	str r5, [sp, #0x2a4]
	add r0, r5, r0
	ldr r5, [sp, #0x238]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019BB4
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2a8]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2ac]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2ac]
	and r6, r5
	ldr r5, [sp, #0x2a8]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x240]
	cmp r0, #0x0
	beq _02019BB4
	ldr r6, [sp, #0x2a4]
	ldr r0, [sp, #0xa0]
	add r6, r6, r0
	ldr r0, [sp, #0x9c]
	strb r5, [r0, r6]
_02019BB4:
	ldr r0, [sp, #0x8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019B58
_02019BC2:
	ldr r0, [sp, #0x240]
	cmp r0, #0x0
	beq _02019BD0
	ldr r0, [sp, #0x244]
	add r0, r0, #0x2
	str r0, [sp, #0x244]
	b _02019BD6
_02019BD0:
	ldr r0, [sp, #0x244]
	add r0, r0, #0x1
	str r0, [sp, #0x244]
_02019BD6:
	ldr r0, [sp, #0x23c]
	add r0, r0, #0x4
	str r0, [sp, #0x23c]
	ldr r0, [sp, #0x248]
	add r0, r0, #0x1
	str r0, [sp, #0x248]
	cmp r0, #0x8
	blt _02019B06
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	add r0, #0x40
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x48]
	mov r1, #0x1
	add r0, #0x8
	str r0, [sp, #0x48]
_02019BF6:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _02019C04
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_02019C04:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _02019BF6
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xb8]
	mov r0, #0x0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	bgt _02019C24
	bl FUN_0201A8BC
_02019C24:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0xb8]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x230]
	ldr r0, [sp, #0x20]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x234]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	cmp r0, #0x0
	ble _02019CD8
	ble _02019CD8
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x40]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0xb4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x40]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xb0]
	str r0, [sp, #0xac]
_02019C76:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xb4]
	str r5, [sp, #0x2b0]
	add r0, r5, r0
	ldr r5, [sp, #0x230]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019CCA
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2b4]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2b8]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2b8]
	and r6, r5
	ldr r5, [sp, #0x2b4]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x234]
	cmp r0, #0x0
	beq _02019CCA
	ldr r6, [sp, #0x2b0]
	ldr r0, [sp, #0xb0]
	add r6, r6, r0
	ldr r0, [sp, #0xac]
	strb r5, [r0, r6]
_02019CCA:
	ldr r0, [sp, #0x8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019C76
_02019CD8:
	ldr r0, [sp, #0x234]
	cmp r0, #0x0
	beq _02019CE6
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _02019CEC
_02019CE6:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_02019CEC:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x20]
	cmp r0, r1
	blt _02019C24
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
_02019D06:
	ldr r0, [sp, #0x0]
	str r0, [sp, #0x220]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x228]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x0
	str r0, [sp, #0x22c]
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x38]
_02019D2A:
	ldr r0, [sp, #0x220]
	ldr r1, [sp, #0x3c]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x21c]
	ldr r0, [sp, #0x22c]
	ldr r6, [sp, #0x38]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x224]
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x228]
	mov r1, #0x0
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x228]
	str r6, [sp, #0xc4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	str r3, [sp, #0x34]
	add r4, r1, #0x0
	str r5, [sp, #0xc0]
	str r0, [sp, #0xbc]
_02019D76:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xc4]
	str r5, [sp, #0x2bc]
	add r0, r5, r0
	ldr r5, [sp, #0x21c]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019DCA
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2c0]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2c4]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2c4]
	and r6, r5
	ldr r5, [sp, #0x2c0]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x224]
	cmp r0, #0x0
	beq _02019DCA
	ldr r6, [sp, #0x2bc]
	ldr r0, [sp, #0xc0]
	add r6, r6, r0
	ldr r0, [sp, #0xbc]
	strb r5, [r0, r6]
_02019DCA:
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, #0x8
	blt _02019D76
	ldr r0, [sp, #0x224]
	cmp r0, #0x0
	beq _02019DE4
	ldr r0, [sp, #0x228]
	add r0, r0, #0x2
	str r0, [sp, #0x228]
	b _02019DEA
_02019DE4:
	ldr r0, [sp, #0x228]
	add r0, r0, #0x1
	str r0, [sp, #0x228]
_02019DEA:
	ldr r0, [sp, #0x220]
	add r0, r0, #0x4
	str r0, [sp, #0x220]
	ldr r0, [sp, #0x22c]
	add r0, r0, #0x1
	str r0, [sp, #0x22c]
	cmp r0, #0x8
	blt _02019D2A
	ldr r0, [sp, #0x0]
	str r0, [sp, #0x20c]
	add r0, #0x20
	str r0, [sp, #0x20c]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x214]
	mov r0, #0x0
	str r0, [sp, #0x218]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0xd4]
	add r0, #0x8
	str r0, [sp, #0xd4]
_02019E12:
	ldr r0, [sp, #0x20c]
	ldr r1, [sp, #0x3c]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0xd4]
	str r0, [sp, #0x208]
	ldr r0, [sp, #0x218]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x210]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	str r0, [sp, #0x2c8]
	sub r0, #0x8
	str r0, [sp, #0x2c8]
	cmp r0, #0x0
	ble _02019ECC
	ble _02019ECC
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x214]
	ldr r6, [sp, #0x38]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x214]
	str r6, [sp, #0xd0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xcc]
	str r0, [sp, #0xc8]
_02019E6A:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xd0]
	str r5, [sp, #0x2cc]
	add r0, r5, r0
	ldr r5, [sp, #0x208]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019EBE
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2d0]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2d4]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2d4]
	and r6, r5
	ldr r5, [sp, #0x2d0]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x210]
	cmp r0, #0x0
	beq _02019EBE
	ldr r6, [sp, #0x2cc]
	ldr r0, [sp, #0xcc]
	add r6, r6, r0
	ldr r0, [sp, #0xc8]
	strb r5, [r0, r6]
_02019EBE:
	ldr r0, [sp, #0x2c8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019E6A
_02019ECC:
	ldr r0, [sp, #0x210]
	cmp r0, #0x0
	beq _02019EDA
	ldr r0, [sp, #0x214]
	add r0, r0, #0x2
	str r0, [sp, #0x214]
	b _02019EE0
_02019EDA:
	ldr r0, [sp, #0x214]
	add r0, r0, #0x1
	str r0, [sp, #0x214]
_02019EE0:
	ldr r0, [sp, #0x20c]
	add r0, r0, #0x4
	str r0, [sp, #0x20c]
	ldr r0, [sp, #0x218]
	add r0, r0, #0x1
	str r0, [sp, #0x218]
	cmp r0, #0x8
	blt _02019E12
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	str r0, [sp, #0x1fc]
	add r0, #0x40
	str r0, [sp, #0x1fc]
	ldr r0, [sp, #0x48]
	mov r1, #0x1
	add r0, #0x8
	str r0, [sp, #0x48]
	str r0, [sp, #0x204]
_02019F04:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _02019F12
	ldr r0, [sp, #0x204]
	add r0, r0, #0x1
	str r0, [sp, #0x204]
_02019F12:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _02019F04
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	str r0, [sp, #0x50]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xe4]
	mov r0, #0x0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A008
_02019F30:
	ldr r0, [sp, #0x1fc]
	ldr r1, [sp, #0xe4]
	ldr r0, [r0, #0x0]
	ldr r6, [sp, #0x38]
	str r0, [sp, #0x1f8]
	ldr r0, [sp, #0x1c]
	ldr r2, [sp, #0x5c]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x200]
	ldr r0, [sp, #0x204]
	mov r1, #0x0
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x204]
	str r6, [sp, #0xe0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	ldr r3, [sp, #0x34]
	add r4, r1, #0x0
	str r5, [sp, #0xdc]
	str r0, [sp, #0xd8]
_02019F78:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
// 	b _02019F8C
// 	nop
// _02019F88: .word 0x00003FE0
// _02019F8C:
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xe0]
	str r5, [sp, #0x2d8]
	add r0, r5, r0
	ldr r5, [sp, #0x1f8]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019FD4
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2dc]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2e0]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2e0]
	and r6, r5
	ldr r5, [sp, #0x2dc]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x200]
	cmp r0, #0x0
	beq _02019FD4
	ldr r6, [sp, #0x2d8]
	ldr r0, [sp, #0xdc]
	add r6, r6, r0
	ldr r0, [sp, #0xd8]
	strb r5, [r0, r6]
_02019FD4:
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, #0x8
	blt _02019F78
	ldr r0, [sp, #0x200]
	cmp r0, #0x0
	beq _02019FEE
	ldr r0, [sp, #0x204]
	add r0, r0, #0x2
	str r0, [sp, #0x204]
	b _02019FF4
_02019FEE:
	ldr r0, [sp, #0x204]
	add r0, r0, #0x1
	str r0, [sp, #0x204]
_02019FF4:
	ldr r0, [sp, #0x1fc]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x1fc]
	ldr r0, [sp, #0x1c]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x1c]
	cmp r0, r1
	blt _02019F30
_0201A008:
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	add r0, #0x60
	str r0, [sp, #0x0]
	mov r1, #0x1
_0201A012:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _0201A020
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A020:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _0201A012
	ldr r0, [sp, #0x50]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xf4]
	mov r0, #0x0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	bgt _0201A03E
	bl FUN_0201A8BC
_0201A03E:
	ldr r0, [sp, #0x5c]
	add r0, #0x8
	str r0, [sp, #0x5c]
_0201A044:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0xf4]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x1f0]
	ldr r0, [sp, #0x18]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1f4]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	str r0, [sp, #0x2e4]
	sub r0, #0x8
	str r0, [sp, #0x2e4]
	cmp r0, #0x0
	ble _0201A0FE
	ble _0201A0FE
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x38]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0xf0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xec]
	str r0, [sp, #0xe8]
_0201A09C:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xf0]
	str r5, [sp, #0x2e8]
	add r0, r5, r0
	ldr r5, [sp, #0x1f0]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _0201A0F0
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2ec]
	ldrb r5, [r0, r7]
	mov r12, r5
	mov r5, #0xf0
	asr r5, r6
	mov r6, r12
	and r6, r5
	ldr r5, [sp, #0x2ec]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x1f4]
	cmp r0, #0x0
	beq _0201A0F0
	ldr r6, [sp, #0x2e8]
	ldr r0, [sp, #0xec]
	add r6, r6, r0
	ldr r0, [sp, #0xe8]
	strb r5, [r0, r6]
_0201A0F0:
	ldr r0, [sp, #0x2e4]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _0201A09C
_0201A0FE:
	ldr r0, [sp, #0x1f4]
	cmp r0, #0x0
	beq _0201A10C
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A112
_0201A10C:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A112:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x18]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x18]
	cmp r0, r1
	blt _0201A044
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}

FUN_0201A12C: // 0x0201A12C
	lsl r1, r2, #0x2
	mul r1, r3
	ldr r3, [r5, #0x0]
	ldrb r2, [r5, #0x9]
	ldr r0, [sp, #0x0]
	ldr r3, [r3, #0x0]
	lsl r1, r1, #0x3
	bl FUN_02018848
	str r0, [sp, #0x1ec]
	cmp r4, #0x3
	bhi _0201A21E
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0201A150:

	lsl r6, r0, #0
	lsl r6, r1, #3
	lsl r0, r7, #9
	lsl r4, r3, #16
	// jump table (using 16-bit offset)
	// .short _0201A158 - _0201A150 - 2; case 0
	// .short _0201A220 - _0201A150 - 2; case 1
	// .short _0201A3CA - _0201A150 - 2; case 2
	// .short _0201A56E - _0201A150 - 2; case 3
_0201A158:
	ldr r0, [sp, #0x330]
	ldr r7, [sp, #0x1ec]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10c]
	mov r0, #0x0
	str r0, [sp, #0x1e8]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0201A21E
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x108]
_0201A178:
	ldr r1, [sp, #0x10c]
	ldr r0, [sp, #0x1e8]
	mov r4, #0x0
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x310]
	ldr r0, [sp, #0x8]
	ldr r5, [sp, #0x5c]
	cmp r0, #0x0
	ble _0201A1FC
	ble _0201A1FC
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x108]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x100]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x104]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x108]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0xfc]
	str r0, [sp, #0xf8]
_0201A1C4:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x104]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A1F0
	ldr r0, [sp, #0x100]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x310]
	cmp r0, #0x0
	beq _0201A1F0
	ldr r0, [sp, #0xfc]
	add r2, r3, r0
	ldr r0, [sp, #0xf8]
	strb r1, [r0, r2]
_0201A1F0:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r0
	blt _0201A1C4
_0201A1FC:
	ldr r0, [sp, #0x310]
	cmp r0, #0x0
	beq _0201A20A
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A210
_0201A20A:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A210:
	ldr r0, [sp, #0x1e8]
	add r7, #0x8
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x1e8]
	cmp r1, r0
	blt _0201A178
_0201A21E:
	b _0201A8B6
_0201A220:
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	str r0, [sp, #0x1e0]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x124]
	mov r0, #0x0
	str r0, [sp, #0x1e4]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0201A2E6
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x120]
_0201A24A:
	ldr r1, [sp, #0x124]
	ldr r0, [sp, #0x1e4]
	ldr r5, [sp, #0x5c]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x30c]
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1e0]
	ldr r2, [sp, #0x120]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x118]
	ldr r0, [sp, #0x1e0]
	str r2, [sp, #0x11c]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x120]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	mov r4, #0x0
	str r2, [sp, #0x114]
	str r0, [sp, #0x110]
_0201A28E:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x11c]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A2BA
	ldr r0, [sp, #0x118]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x30c]
	cmp r0, #0x0
	beq _0201A2BA
	ldr r0, [sp, #0x114]
	add r2, r3, r0
	ldr r0, [sp, #0x110]
	strb r1, [r0, r2]
_0201A2BA:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, #0x8
	blt _0201A28E
	ldr r0, [sp, #0x30c]
	cmp r0, #0x0
	beq _0201A2D2
	ldr r0, [sp, #0x1e0]
	add r0, r0, #0x2
	str r0, [sp, #0x1e0]
	b _0201A2D8
_0201A2D2:
	ldr r0, [sp, #0x1e0]
	add r0, r0, #0x1
	str r0, [sp, #0x1e0]
_0201A2D8:
	ldr r0, [sp, #0x1e4]
	add r7, #0x8
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x1e4]
	cmp r1, r0
	blt _0201A24A
_0201A2E6:
	ldr r0, [sp, #0x1ec]
	str r0, [sp, #0x308]
	add r0, #0x40
	str r0, [sp, #0x308]
	ldr r0, [sp, #0x4c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x13c]
	mov r0, #0x0
	str r0, [sp, #0x1dc]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0201A3C8
	ldr r0, [sp, #0x5c]
	mov r1, #0x7
	add r0, #0x8
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x138]
_0201A312:
	ldr r1, [sp, #0x13c]
	ldr r0, [sp, #0x1dc]
	ldr r7, [sp, #0x8]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r7, #0x8
	mov r4, #0x0
	str r0, [sp, #0x1d8]
	ldr r5, [sp, #0x5c]
	cmp r7, #0x0
	ble _0201A398
	ble _0201A398
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x138]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x130]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x134]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x138]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x12c]
	str r0, [sp, #0x128]
_0201A360:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x134]
	add r2, r3, r0
	ldr r0, [sp, #0x308]
	ldrb r1, [r0, r4]
	cmp r1, #0x0
	beq _0201A38E
	ldr r0, [sp, #0x130]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x1d8]
	cmp r0, #0x0
	beq _0201A38E
	ldr r0, [sp, #0x12c]
	add r2, r3, r0
	ldr r0, [sp, #0x128]
	strb r1, [r0, r2]
_0201A38E:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r7
	blt _0201A360
_0201A398:
	ldr r0, [sp, #0x1d8]
	cmp r0, #0x0
	beq _0201A3B0
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A3B6
// 	nop
// _0201A3A8: .word 0x00003FE0
// _0201A3AC: .word 0x00007FC0
_0201A3B0:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A3B6:
	ldr r0, [sp, #0x308]
	add r0, #0x8
	str r0, [sp, #0x308]
	ldr r0, [sp, #0x1dc]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x1dc]
	cmp r1, r0
	blt _0201A312
_0201A3C8:
	b _0201A8B6
_0201A3CA:
	ldr r0, [sp, #0x48]
	mov r1, #0x7
	str r0, [sp, #0x1d0]
	mov r0, #0x0
	str r0, [sp, #0x1d4]
	ldr r0, [sp, #0x330]
	ldr r7, [sp, #0x1ec]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x150]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x30]
_0201A3E8:
	ldr r1, [sp, #0x150]
	ldr r0, [sp, #0x1d4]
	mov r4, #0x0
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x304]
	ldr r0, [sp, #0x8]
	ldr r5, [sp, #0x5c]
	cmp r0, #0x0
	ble _0201A46C
	ble _0201A46C
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1d0]
	ldr r2, [sp, #0x30]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x148]
	ldr r0, [sp, #0x1d0]
	str r2, [sp, #0x14c]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x30]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x144]
	str r0, [sp, #0x140]
_0201A434:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x14c]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A460
	ldr r0, [sp, #0x148]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x304]
	cmp r0, #0x0
	beq _0201A460
	ldr r0, [sp, #0x144]
	add r2, r3, r0
	ldr r0, [sp, #0x140]
	strb r1, [r0, r2]
_0201A460:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r0
	blt _0201A434
_0201A46C:
	ldr r0, [sp, #0x304]
	cmp r0, #0x0
	beq _0201A47A
	ldr r0, [sp, #0x1d0]
	add r0, r0, #0x2
	str r0, [sp, #0x1d0]
	b _0201A480
_0201A47A:
	ldr r0, [sp, #0x1d0]
	add r0, r0, #0x1
	str r0, [sp, #0x1d0]
_0201A480:
	ldr r0, [sp, #0x1d4]
	add r7, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x1d4]
	cmp r0, #0x8
	blt _0201A3E8
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	add r0, #0x8
	str r0, [sp, #0x48]
	add r7, #0x80
	mov r0, #0x0
	mov r2, #0x1
_0201A49A:
	ldr r1, [sp, #0x330]
	asr r1, r0
	tst r1, r2
	beq _0201A4A8
	ldr r1, [sp, #0x48]
	add r1, r1, #0x1
	str r1, [sp, #0x48]
_0201A4A8:
	add r0, r0, #0x1
	cmp r0, #0x8
	blt _0201A49A
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x164]
	mov r0, #0x0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A56C
_0201A4C4:
	ldr r1, [sp, #0x164]
	ldr r0, [sp, #0x14]
	mov r4, #0x0
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x300]
	ldr r0, [sp, #0x8]
	ldr r5, [sp, #0x5c]
	cmp r0, #0x0
	ble _0201A548
	ble _0201A548
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x30]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x15c]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x160]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x30]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x158]
	str r0, [sp, #0x154]
_0201A510:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x160]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A53C
	ldr r0, [sp, #0x15c]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x300]
	cmp r0, #0x0
	beq _0201A53C
	ldr r0, [sp, #0x158]
	add r2, r3, r0
	ldr r0, [sp, #0x154]
	strb r1, [r0, r2]
_0201A53C:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r0
	blt _0201A510
_0201A548:
	ldr r0, [sp, #0x300]
	cmp r0, #0x0
	beq _0201A556
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A55C
_0201A556:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A55C:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x1
	sub r1, #0x8
	add r7, #0x8
	str r0, [sp, #0x14]
	cmp r0, r1
	blt _0201A4C4
_0201A56C:
	b _0201A8B6
_0201A56E:
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	str r0, [sp, #0x1c8]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x0
	str r0, [sp, #0x1cc]
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x28]
_0201A590:
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x1cc]
	ldr r5, [sp, #0x5c]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x2fc]
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1c8]
	ldr r2, [sp, #0x28]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x170]
	ldr r0, [sp, #0x1c8]
	str r2, [sp, #0x174]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	mov r4, #0x0
	str r6, [sp, #0x24]
	str r2, [sp, #0x16c]
	str r0, [sp, #0x168]
_0201A5D6:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x174]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A602
	ldr r0, [sp, #0x170]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x2fc]
	cmp r0, #0x0
	beq _0201A602
	ldr r0, [sp, #0x16c]
	add r2, r3, r0
	ldr r0, [sp, #0x168]
	strb r1, [r0, r2]
_0201A602:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, #0x8
	blt _0201A5D6
	ldr r0, [sp, #0x2fc]
	cmp r0, #0x0
	beq _0201A61A
	ldr r0, [sp, #0x1c8]
	add r0, r0, #0x2
	str r0, [sp, #0x1c8]
	b _0201A620
_0201A61A:
	ldr r0, [sp, #0x1c8]
	add r0, r0, #0x1
	str r0, [sp, #0x1c8]
_0201A620:
	ldr r0, [sp, #0x1cc]
	add r7, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x1cc]
	cmp r0, #0x8
	blt _0201A590
	ldr r0, [sp, #0x1ec]
	str r0, [sp, #0x2f8]
	add r0, #0x40
	str r0, [sp, #0x2f8]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x1c0]
	mov r0, #0x0
	str r0, [sp, #0x1c4]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0x188]
	add r0, #0x8
	str r0, [sp, #0x188]
_0201A644:
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x1c4]
	ldr r7, [sp, #0x8]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r7, #0x8
	mov r4, #0x0
	str r0, [sp, #0x1bc]
	ldr r5, [sp, #0x188]
	cmp r7, #0x0
	ble _0201A6CA
	ble _0201A6CA
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1c0]
	ldr r2, [sp, #0x28]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x180]
	ldr r0, [sp, #0x1c0]
	str r2, [sp, #0x184]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x17c]
	str r0, [sp, #0x178]
_0201A692:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x184]
	add r2, r3, r0
	ldr r0, [sp, #0x2f8]
	ldrb r1, [r0, r4]
	cmp r1, #0x0
	beq _0201A6C0
	ldr r0, [sp, #0x180]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x1bc]
	cmp r0, #0x0
	beq _0201A6C0
	ldr r0, [sp, #0x17c]
	add r2, r3, r0
	ldr r0, [sp, #0x178]
	strb r1, [r0, r2]
_0201A6C0:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r7
	blt _0201A692
_0201A6CA:
	ldr r0, [sp, #0x1bc]
	cmp r0, #0x0
	beq _0201A6D8
	ldr r0, [sp, #0x1c0]
	add r0, r0, #0x2
	str r0, [sp, #0x1c0]
	b _0201A6DE
_0201A6D8:
	ldr r0, [sp, #0x1c0]
	add r0, r0, #0x1
	str r0, [sp, #0x1c0]
_0201A6DE:
	ldr r0, [sp, #0x2f8]
	add r0, #0x8
	str r0, [sp, #0x2f8]
	ldr r0, [sp, #0x1c4]
	add r0, r0, #0x1
	str r0, [sp, #0x1c4]
	cmp r0, #0x8
	blt _0201A644
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	add r0, #0x8
	add r7, #0x80
	str r0, [sp, #0x48]
	str r0, [sp, #0x1b8]
	mov r0, #0x0
	mov r2, #0x1
_0201A6FE:
	ldr r1, [sp, #0x330]
	asr r1, r0
	tst r1, r2
	beq _0201A70C
	ldr r1, [sp, #0x1b8]
	add r1, r1, #0x1
	str r1, [sp, #0x1b8]
_0201A70C:
	add r0, r0, #0x1
	cmp r0, #0x8
	blt _0201A6FE
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	str r0, [sp, #0x44]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x19c]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A7CE
_0201A72A:
	ldr r1, [sp, #0x19c]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x28]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x2f4]
	ldr r0, [sp, #0x1b8]
	mov r3, #0x38
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
// 	b _0201A74C
// 	nop
// _0201A748: .word 0x00007FC0
// _0201A74C:
	ldr r5, [sp, #0x5c]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x194]
	ldr r0, [sp, #0x1b8]
	str r2, [sp, #0x198]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	ldr r6, [sp, #0x24]
	mov r4, #0x0
	str r2, [sp, #0x190]
	str r0, [sp, #0x18c]
_0201A774:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x198]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A7A0
	ldr r0, [sp, #0x194]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x2f4]
	cmp r0, #0x0
	beq _0201A7A0
	ldr r0, [sp, #0x190]
	add r2, r3, r0
	ldr r0, [sp, #0x18c]
	strb r1, [r0, r2]
_0201A7A0:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, #0x8
	blt _0201A774
	ldr r0, [sp, #0x2f4]
	cmp r0, #0x0
	beq _0201A7B8
	ldr r0, [sp, #0x1b8]
	add r0, r0, #0x2
	str r0, [sp, #0x1b8]
	b _0201A7BE
_0201A7B8:
	ldr r0, [sp, #0x1b8]
	add r0, r0, #0x1
	str r0, [sp, #0x1b8]
_0201A7BE:
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x1
	sub r1, #0x8
	add r7, #0x8
	str r0, [sp, #0x10]
	cmp r0, r1
	blt _0201A72A
_0201A7CE:
	ldr r0, [sp, #0x1ec]
	mov r2, #0x0
	str r0, [sp, #0x2f0]
	add r0, #0xc0
	str r0, [sp, #0x2f0]
	mov r1, #0x1
_0201A7DA:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _0201A7E8
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A7E8:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _0201A7DA
	ldr r0, [sp, #0x44]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1b0]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A8B6
	ldr r0, [sp, #0x5c]
	add r0, #0x8
	str r0, [sp, #0x5c]
_0201A808:
	ldr r1, [sp, #0x1b0]
	ldr r0, [sp, #0xc]
	ldr r7, [sp, #0x8]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r7, #0x8
	mov r4, #0x0
	str r0, [sp, #0x1b4]
	ldr r5, [sp, #0x5c]
	cmp r7, #0x0
	ble _0201A88E
	ble _0201A88E
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x28]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x1a8]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x1ac]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x1a4]
	str r0, [sp, #0x1a0]
_0201A856:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x1ac]
	add r2, r3, r0
	ldr r0, [sp, #0x2f0]
	ldrb r1, [r0, r4]
	cmp r1, #0x0
	beq _0201A884
	ldr r0, [sp, #0x1a8]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x1b4]
	cmp r0, #0x0
	beq _0201A884
	ldr r0, [sp, #0x1a4]
	add r2, r3, r0
	ldr r0, [sp, #0x1a0]
	strb r1, [r0, r2]
_0201A884:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r7
	blt _0201A856
_0201A88E:
	ldr r0, [sp, #0x1b4]
	cmp r0, #0x0
	beq _0201A89C
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A8A2
_0201A89C:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A8A2:
	ldr r0, [sp, #0x2f0]
	ldr r1, [sp, #0x4]
	add r0, #0x8
	str r0, [sp, #0x2f0]
	ldr r0, [sp, #0xc]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	cmp r0, r1
	blt _0201A808
_0201A8B6:
	ldr r0, [sp, #0x1ec]
	bl FreeToHeap

FUN_0201A8BC: // 0x0201A8BC
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
    // clang-format on
}
#endif

THUMB_FUNC void FUN_0201A8C8(struct Window *window, u32 param1, u8 param2, u8 param3)
{
    if (window->unk00->unk08[window->unk04].unk1e == 0)
    {
        FUN_0201A8E8(window, param1, param2, param3);
    }
    else
    {
        FUN_0201A9D4(window, param1, param2, param3);
    }
}

THUMB_FUNC void FUN_0201A8E8(struct Window *window, u32 param1, u8 param2, u8 param3)
{
    void *r2;
    int r5, r1, r3;
    int st4, stc;
    u32 st8;
    int i, j;

    r2 = window->unk0c;
    st4 = (param3 << 0x18) | (param3 << 0x10) | (param3 << 0x8) | param3;
    stc = window->unk08 * window->unk07 * 32;
    st8 = window->unk07;

    switch (param1)
    {
    case 0:
        for (i = 0; i < stc; i += 32)
        {
            r3 = param2;
            for (j = 0; j < 8; j++)
            {
                r5 = i + (j << 2);
                r1 = i + (((st8 * (r3 & ~7)) | (r3 & 7)) << 2);

                if (r1 < stc)
                {
                    *(u32 *)(r2 + r5) = *(u32 *)(r2 + r1);
                }
                else
                {
                    *(u32 *)(r2 + r5) = st4;
                }

                r3++;
            }
        }

        break;
    case 1:
        r2 += stc - 4;
        for (i = 0; i < stc; i += 32)
        {
            r3 = param2;
            for (j = 0; j < 8; j++)
            {
                r5 = i + (j << 2);
                r1 = i + (((st8 * (r3 & ~7)) | (r3 & 7)) << 2);

                if (r1 < stc)
                {
                    *(u32 *)(r2 - r5) = *(u32 *)(r2 - r1);
                }
                else
                {
                    *(u32 *)(r2 - r5) = st4;
                }

                r3++;
            }
        }

        break;
    case 2:
    case 3:
        break;
    }
}

THUMB_FUNC void FUN_0201A9D4(struct Window *window, u32 param1, u8 param2, u8 param3)
{

    void *r2;
    int r5, r1, r3;
    int st4, stc;
    u32 st8;
    int i, j;

    r2 = (u8 *)window->unk0c;
    st4 = (param3 << 0x18) | (param3 << 0x10) | (param3 << 0x8) | param3;
    stc = window->unk08 * window->unk07 * 64;
    st8 = window->unk07;

    switch (param1)
    {
    case 0:
        for (i = 0; i < stc; i += 64)
        {
            r3 = param2;
            for (j = 0; j < 8; j++)
            {
                r5 = i + (j << 3);
                r1 = i + (((st8 * (r3 & ~7)) | (r3 & 7)) << 3);

                if (r1 < stc)
                {
                    *(u32 *)(r2 + r5) = *(u32 *)(r2 + r1);
                }
                else
                {
                    *(u32 *)(r2 + r5) = st4;
                }

                r5 += 4;
                r1 += 4;
                if (r1 < stc + 4)
                {
                    *(u32 *)(r2 + r5) = *(u32 *)(r2 + r1);
                }
                else
                {
                    *(u32 *)(r2 + r5) = st4;
                }

                r3++;
            }
        }

        break;
    case 1:
        r2 += stc - 8;
        for (i = 0; i < stc; i += 64)
        {
            r3 = param2;
            for (j = 0; j < 8; j++)
            {
                r5 = i + (j << 3);
                r1 = i + (((st8 * (r3 & ~7)) | (r3 & 7)) << 3);

                if (r1 < stc)
                {
                    *(u32 *)(r2 - r5) = *(u32 *)(r2 - r1);
                }
                else
                {
                    *(u32 *)(r2 - r5) = st4;
                }

                r5 -= 4;
                r1 -= 4;
                if (r1 < stc - 4)
                {
                    *(u32 *)(r2 - r5) = *(u32 *)(r2 - r1);
                }
                else
                {
                    *(u32 *)(r2 - r5) = st4;
                }

                r3++;
            }
        }

        break;
    case 2:
    case 3:
        break;
    }
}

THUMB_FUNC u8 FUN_0201AB08(struct Window *window)
{
    return window->unk04;
}

THUMB_FUNC u8 FUN_0201AB0C(struct Window *window)
{
    return window->unk07;
}
THUMB_FUNC u8 FUN_0201AB10(struct Window *window)
{
    return window->unk08;
}
THUMB_FUNC u8 FUN_0201AB14(struct Window *window)
{
    return window->unk05;
}
THUMB_FUNC u8 FUN_0201AB18(struct Window *window)
{
    return window->unk06;
}
THUMB_FUNC void FUN_0201AB1C(struct Window *window, u8 param1)
{
    window->unk05 = param1;
}
THUMB_FUNC void FUN_0201AB20(struct Window *window, u8 param1)
{
    window->unk06 = param1;
}
THUMB_FUNC void FUN_0201AB24(struct Window *window, u8 param1)
{
    window->unk09 = param1;
}

THUMB_FUNC u32 FUN_0201AB28(struct Window *window, u32 heap_id, const char *path)
{
    void *ptr = FUN_020161A4(heap_id, path);
    window->unk00 = ptr;
    u32 st0;
    FUN_020B0030(ptr, &st0);

    return st0;
}

THUMB_FUNC u32 FUN_0201AB44(struct Window *window, u32 heap_id, const char *path)
{
    void *ptr = FUN_020161A4(heap_id, path);
    window->unk00 = ptr;
    u32 st0;
    FUN_020B0138(ptr, &st0);

    return st0;
}

THUMB_FUNC void FUN_0201AB60(struct UnkStruct2 *param0)
{
    FUN_0201AC78(param0);
    FUN_0201AB78(param0);

    param0->unk04 = 0;
    param0->unk06 = 0;
}

THUMB_FUNC void FUN_0201AB78(struct UnkStruct2 *param0)
{
    if ((param0->unk06 & 1) != 0)
    {
        FUN_02017D68(0, param0->unk08[0].unk08, param0->unk08[0].unk10 * 2, param0->unk08[0].unk0c);
    }

    if ((param0->unk06 & 2) != 0)
    {
        FUN_02017D68(1, param0->unk08[1].unk08, param0->unk08[1].unk10 * 2, param0->unk08[1].unk0c);
    }

    if ((param0->unk06 & 4) != 0)
    {
        FUN_02017D68(2, param0->unk08[2].unk08, param0->unk08[2].unk10 * 2, param0->unk08[2].unk0c);
    }

    if ((param0->unk06 & 8) != 0)
    {
        FUN_02017D68(3, param0->unk08[3].unk08, param0->unk08[3].unk10 * 2, param0->unk08[3].unk0c);
    }

    if ((param0->unk06 & 0x10) != 0)
    {
        FUN_02017D68(4, param0->unk08[4].unk08, param0->unk08[4].unk10 * 2, param0->unk08[4].unk0c);
    }

    if ((param0->unk06 & 0x20) != 0)
    {
        FUN_02017D68(5, param0->unk08[5].unk08, param0->unk08[5].unk10 * 2, param0->unk08[5].unk0c);
    }

    if ((param0->unk06 & 0x40) != 0)
    {
        FUN_02017D68(6, param0->unk08[6].unk08, param0->unk08[6].unk10 * 2, param0->unk08[6].unk0c);
    }

    if ((param0->unk06 & 0x80) != 0)
    {
        FUN_02017D68(7, param0->unk08[7].unk08, param0->unk08[7].unk10 * 2, param0->unk08[7].unk0c);
    }
}

THUMB_FUNC void FUN_0201AC68(struct UnkStruct2 *param0, u32 param1)
{
    param0->unk06 |= 1 << param1;
}

THUMB_FUNC void FUN_0201AC78(struct UnkStruct2 *param0)
{
    if ((param0->unk04 & 1) != 0)
    {
        reg_G2_BG0OFS =
            (param0->unk08[0].unk14 & 0x1ff) | ((param0->unk08[0].unk18 << 0x10) & 0x1ff0000);
    }

    if ((param0->unk04 & 2) != 0)
    {
        reg_G2_BG1OFS =
            (param0->unk08[1].unk14 & 0x1ff) | ((param0->unk08[1].unk18 << 0x10) & 0x1ff0000);
    }

    if ((param0->unk04 & 4) != 0)
    {
        if (param0->unk08[2].unk1c == 0)
        {
            reg_G2_BG2OFS =
                (param0->unk08[2].unk14 & 0x1ff) | ((param0->unk08[2].unk18 << 0x10) & 0x1ff0000);
        }
        else
        {
            struct Mtx22 st38;
            MTX22_2DAffine(
                &st38, param0->unk08[2].unk20, param0->unk08[2].unk24, param0->unk08[2].unk28, 2);
            G2x_SetBGyAffine_(0x04000020,
                &st38,
                param0->unk08[2].unk2c,
                param0->unk08[2].unk30,
                param0->unk08[2].unk14,
                param0->unk08[2].unk18);
        }
    }

    if ((param0->unk04 & 8) != 0)
    {
        if (param0->unk08[3].unk1c == 0)
        {
            reg_G2_BG3OFS =
                (param0->unk08[3].unk14 & 0x1ff) | ((param0->unk08[3].unk18 << 0x10) & 0x1ff0000);
        }
        else
        {
            struct Mtx22 st28;
            MTX22_2DAffine(
                &st28, param0->unk08[3].unk20, param0->unk08[3].unk24, param0->unk08[3].unk28, 2);
            G2x_SetBGyAffine_(0x04000030,
                &st28,
                param0->unk08[3].unk2c,
                param0->unk08[3].unk30,
                param0->unk08[3].unk14,
                param0->unk08[3].unk18);
        }
    }

    if ((param0->unk04 & 0x10) != 0)
    {
        reg_G2S_DB_BG0OFS =
            (param0->unk08[4].unk14 & 0x1ff) | ((param0->unk08[4].unk18 << 0x10) & 0x1ff0000);
    }

    if ((param0->unk04 & 0x20) != 0)
    {
        reg_G2S_DB_BG1OFS =
            (param0->unk08[5].unk14 & 0x1ff) | ((param0->unk08[5].unk18 << 0x10) & 0x1ff0000);
    }

    if ((param0->unk04 & 0x40) != 0)
    {
        if (param0->unk08[6].unk1c == 0)
        {
            reg_G2S_DB_BG2OFS =
                (param0->unk08[6].unk14 & 0x1ff) | ((param0->unk08[6].unk18 << 0x10) & 0x1ff0000);
        }
        else
        {
            struct Mtx22 st18;
            MTX22_2DAffine(
                &st18, param0->unk08[6].unk20, param0->unk08[6].unk24, param0->unk08[6].unk28, 2);
            G2x_SetBGyAffine_(0x04001020,
                &st18,
                param0->unk08[6].unk2c,
                param0->unk08[6].unk30,
                param0->unk08[6].unk14,
                param0->unk08[6].unk18);
        }
    }

    if ((param0->unk04 & 0x80) != 0)
    {
        if (param0->unk08[7].unk1c == 0)
        {
            reg_G2S_DB_BG3OFS =
                (param0->unk08[7].unk14 & 0x1ff) | ((param0->unk08[7].unk18 << 0x10) & 0x1ff0000);
        }
        else
        {
            struct Mtx22 st08;
            MTX22_2DAffine(
                &st08, param0->unk08[7].unk20, param0->unk08[7].unk24, param0->unk08[7].unk28, 2);
            G2x_SetBGyAffine_(0x04001030,
                &st08,
                param0->unk08[7].unk2c,
                param0->unk08[7].unk30,
                param0->unk08[7].unk14,
                param0->unk08[7].unk18);
        }
    }
}

THUMB_FUNC void FUN_0201AEE4(struct UnkStruct2 *param0, u32 param1, u32 param2, u32 param3)
{
    FUN_02017B8C(&param0->unk08[param1], param2, param3);
    param0->unk04 |= 1 << param1;
}

THUMB_FUNC void FUN_0201AF08(struct UnkStruct2 *param0, u32 param1, u32 param2, u32 param3)
{
    FUN_0201AF2C(&param0->unk08[param1], param2, param3);
    param0->unk04 |= 1 << param1;
}

THUMB_FUNC void FUN_0201AF2C(struct InnerStruct *param0, u32 param1, u32 val)
{
    switch (param1)
    {
    case 0:
        param0->unk20 = val;
        break;
    case 1:
        param0->unk20 += val;
        break;
    case 2:
        param0->unk20 -= val;
        break;
    }
}

THUMB_FUNC void FUN_0201AF50(struct UnkStruct2 *param0, u32 param1, u32 param2, u32 param3)
{
    FUN_0201AF74(&param0->unk08[param1], param2, param3);
    param0->unk04 |= 1 << param1;
}

THUMB_FUNC void FUN_0201AF74(struct InnerStruct *param0, u32 param1, u32 val)
{
    switch (param1 - 9)
    {
    case 0:
        param0->unk2c = val;
        break;
    case 1:
        param0->unk2c += val;
        break;
    case 2:
        param0->unk2c -= val;
        break;
    case 3:
        param0->unk30 = val;
        break;
    case 4:
        param0->unk30 += val;
        break;
    case 5:
        param0->unk30 -= val;
        break;
    }
}

THUMB_FUNC u32 FUN_0201AFBC(struct UnkStruct2 *param0, u8 param1, u8 param2, u8 param3, u16 *param4)
{
    void *st18;
    u16 r6;
    u8 st14;
    u8 st10;
    u8 r5;
    u8 i;

    if (param0->unk08[param1].unk08 == NULL)
    {
        return 0;
    }

    r6 = FUN_02017FFC(param2 >> 3, param3 >> 3, param0->unk08[param1].unk1d);
    st18 = FUN_020187B0(param1);

    st14 = param2 & 7;
    st10 = param3 & 7;

    if (param0->unk08[param1].unk1e == 0)
    {
        u16 *stc = param0->unk08[param1].unk08;
        u8 *ptr = AllocFromHeapAtEnd(param0->unk00, 0x40);

        st18 += ((stc[r6] & 0x3ff) << 5);
        for (i = 0; i < 0x20; i++)
        {
            ptr[(i << 1)] = ((u8 *)st18)[i] & 0xf;
            ptr[(i << 1) + 1] = ((u8 *)st18)[i] >> 4;
        }

        FUN_0201B118(param0, (stc[r6] >> 0xa) & 3, ptr);

        r5 = ptr[st14 + (st10 << 3)];
        FreeToHeap(ptr);

        if ((param4[0] & (1 << r5)) != 0)
        {
            return 1;
        }
    }
    else
    {
        if (param0->unk08[param1].unk1c != 1)
        {
            u16 *r4 = param0->unk08[param1].unk08;
            u8 *ptr = AllocFromHeapAtEnd(param0->unk00, 0x40);

            memcpy(ptr, st18 + ((r4[r6] & 0x3ff) << 6), 0x40);

            FUN_0201B118(param0, (r4[r6] >> 0xa) & 3, ptr);

            r5 = ptr[st14 + (st10 << 3)];
            FreeToHeap(ptr);
        }
        else
        {
            r5 = ((u8 *)st18)[(((u8 *)param0->unk08[param1].unk08)[r6] << 6) + st14 + (st10 << 3)];
        }

        while (TRUE)
        {
            if (param4[0] == 0xffff)
            {
                break;
            }
            if (r5 == (u8)(param4[0]))
            {
                return 1;
            }
        }
    }
    return 0;
}

THUMB_FUNC void FUN_0201B118(struct UnkStruct2 *param0, u8 param1, u8 *param2)
{
    u8 i, j;
    if (param1 != 0)
    {
        u8 *ptr = AllocFromHeapAtEnd(param0->unk00, 0x40);

        if ((param1 & 1) != 0)
        {
            for (i = 0; i < 8; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    ptr[i * 8 + j] = param2[i * 8 + (7 - j)];
                }
            }

            memcpy(param2, ptr, 0x40);
        }

        if ((param1 & 2) != 0)
        {
            for (i = 0; i < 8; i++)
            {
                u8 *r3 = &ptr[i * 8];
                u8 *r2 = &param2[(7 - i) * 8];
                for (u32 j = 8; j > 0; j--)
                {
                    *r3++ = *r2++;
                }
            }

            memcpy(param2, ptr, 0x40);
        }

        FreeToHeap(ptr);
    }
}
