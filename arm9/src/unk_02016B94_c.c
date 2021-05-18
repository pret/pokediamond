#include "global.h"
#include "GX_layers.h"
#include "gx.h"
#include "heap.h"
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

extern void FUN_02018170(struct UnkStruct2 *param0,
    u32 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u32 *param6,
    u8 param7,
    u8 param8,
    u8 param9,
    u8 param10);

THUMB_FUNC void FUN_02018148(
    struct UnkStruct2 *param0, u32 param1, u32 *param2, u8 param3, u8 param4, u8 param5, u8 param6)
{
    FUN_02018170(param0, param1, param3, param4, param5, param6, param2, 0, 0, param5, param6);
}

extern void FUN_02018268(struct InnerStruct *param0,
    u8 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u16 *param5,
    u8 param6,
    u8 param7,
    u8 param8,
    u8 param9,
    u8 param10);
extern void FUN_020183DC(struct InnerStruct *param0,
    u8 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 *param5,
    u8 param6,
    u8 param7,
    u8 param8,
    u8 param9,
    u8 param10);

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

extern void FUN_02018590(
    struct InnerStruct *param0, u16 param1, u8 param2, u8 param3, u8 param4, u8 param5, u8 param6);
extern void FUN_02018640(
    struct InnerStruct *param0, u8 param1, u8 param2, u8 param3, u8 param4, u8 param5);

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

extern void FUN_0201AC68(struct UnkStruct2 *param0, u32 param1);

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
THUMB_FUNC void FUN_02018A60(u16 *param0,
    u16 *param1,
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
    if (param1[2] - param4 < param6)
    {
        st50 = param2 + param1[2] - param4;
    }
    else
    {
        st50 = param2 + param6;
    }

    int st4c;
    if (param1[3] - param5 < param7)
    {
        st4c = param3 + param1[3] - param5;
    }
    else
    {
        st4c = param3 + param7;
    }

    int st48 = (param0[2] + (param0[2] & 7)) >> 3;

    int st44 = (param1[2] + (param1[2] & 7)) >> 3;

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
                    *(u32 *)param1 + (j1 >> 1) &
                    0x3 + ((j1 << 2) & 0x3fe0) + st44 * ((i1 << 2) & 0x3fe0) + ((i1 << 2) & 0x1c);
                unk2 = *(u32 *)param0 + (j >> 1) &
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

                unk1 = *(u32 *)param1 + ((j1 >> 1) & 3) + ((j1 << 2) & 0x3fe0) +
                           st44 * ((i1 << 2) & 0x3fe0) + (i1 << 2) &
                       0x1c;
                unk2 = *(u32 *)param0 + ((j >> 1) & 3) + ((j << 2) & 0x3fe0) +
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
THUMB_FUNC asm void FUN_02018A60(u16 *param0,
    u16 *param1,
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
THUMB_FUNC void FUN_02018CA0(u16 *param0,
    u16 *param1,
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
THUMB_FUNC asm void FUN_02018CA0(u16 *param0,
    u16 *param1,
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

THUMB_FUNC void FUN_02018E88(u16 *param0, u16 param1, u16 param2, u16 param3, u16 param4, u8 param5)
{

    int r6 = param1 + param3;
    if (r6 > param0[2])
    {
        r6 = param0[2];
    }

    int r12 = param2 + param4;
    if (r12 > param0[3])
    {
        r12 = param0[3];
    }

    int lr = (((param0[2]) + (param0[2] & 7)) >> 3);

    for (int i = param2; i < r12; i++)
    {

        for (int j = param1; j < r6; j++)
        {

            u8 *unk = (u8 *)(*(u8 **)param0 + ((j >> 1) & 3) + ((j << 2) & 0x3fe0) +
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

THUMB_FUNC void FUN_02018F4C(u16 *param0, u16 param1, u16 param2, u16 param3, u16 param4, u8 param5)
{

    int r6 = param1 + param3;
    if (r6 > param0[2])
    {
        r6 = param0[2];
    }

    int r12 = param2 + param4;
    if (r12 > param0[3])
    {
        r12 = param0[3];
    }

    int lr = (((param0[2]) + (param0[2] & 7)) >> 3);

    for (int i = param2; i < r12; i++)
    {

        for (int j = param1; j < r6; j++)
        {

            u8 *unk = (u8 *)(*(u8 **)param0 + (j & 7) + ((j << 3) & 0x7fc0) +
                             (((i << 3) & 0x7fc0) * lr) + ((i << 3) & 0x38));

            *unk = param5;
        }
    }
}

struct Window
{
    struct UnkStruct2 *unk00;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    u8 unk08;
    u8 unk09;
    u16 unk0a : 15;
    u16 unk0b : 1;
    void *unk0c;
};

extern void FUN_0201901C(struct Window *ptr);

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

struct UnkStruct4
{
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u16 unk6;
};

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

	for ( i = 0; i < param0->unk08; i++)
	{
		for ( j = 0; j < param0->unk07; j++)
		{
			r5[j] = 0;
		}
		r5 += r6;
		
	}

}
