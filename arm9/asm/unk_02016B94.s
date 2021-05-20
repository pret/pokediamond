    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020EDB30
UNK_020EDB30: ; 0x020EDB30
	.byte 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00

	.global UNK_020EDB38
UNK_020EDB38: ; 0x020EDB38
	.word FUN_020192D4
	.word FUN_02019358
	.word FUN_020192D4

	.global UNK_020EDB44
UNK_020EDB44: ; 0x020EDB44
	.word FUN_020195D0
	.word FUN_0201960C
	.word FUN_020195D0

	.global UNK_020EDB50
UNK_020EDB50: ; 0x020EDB50
	.word FUN_020195A8
	.word FUN_020195E4
	.word FUN_020195A8

	.global UNK_020EDB5C
UNK_020EDB5C: ; 0x020EDB5C
	.word FUN_020194C8
	.word FUN_0201951C
	.word FUN_020194C8

	.global UNK_020EDB68
UNK_020EDB68: ; 0x020EDB68
	.word FUN_0201949C
	.word FUN_020194E0
	.word FUN_0201949C

	.global UNK_020EDB74
UNK_020EDB74: ; 0x020EDB74
	.word FUN_020193B4
	.word FUN_02019444
	.word FUN_020193B4

	.text

	thumb_func_start FUN_02016B94
FUN_02016B94: ; 0x02016B94
	push {r3-r5, lr}
	mov r1, #0x5a
	lsl r1, r1, #0x2
	add r5, r0, #0x0
	bl AllocFromHeap
	mov r2, #0x5a
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r4, r0, #0x0
	bl memset
	str r5, [r4, #0x0]
	mov r0, #0x0
	strh r0, [r4, #0x4]
	strh r0, [r4, #0x6]
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02016BB8
FUN_02016BB8: ; 0x02016BB8
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02016BBC
FUN_02016BBC: ; 0x02016BBC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0xc]
	bl GX_SetGraphicsMode
	ldr r0, [r4, #0x8]
	bl GXS_SetGraphicsMode
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _02016BF0 ; =0xC7FFFFFF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r1, [r2, #0x0]
	asr r0, r0, #0x3
	and r0, r1
	str r0, [r2, #0x0]
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	pop {r4, pc}
	nop
_02016BF0: .word 0xC7FFFFFF

	thumb_func_start FUN_02016BF4
FUN_02016BF4: ; 0x02016BF4
	push {r3, lr}
	add r2, r0, #0x0
	cmp r1, #0x0
	bne _02016C0C
	ldr r0, [r2, #0x0]
	ldr r1, [r2, #0x4]
	ldr r2, [r2, #0xc]
	bl GX_SetGraphicsMode
	bl GX_DisableEngineALayers
	pop {r3, pc}
_02016C0C:
	ldr r0, [r2, #0x8]
	bl GXS_SetGraphicsMode
	bl GX_DisableEngineBLayers
	pop {r3, pc}

	thumb_func_start FUN_02016C18
FUN_02016C18: ; 0x02016C18
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
_02016C42: ; jump table (using 16-bit offset)
	.short _02016C52 - _02016C42 - 2; case 0
	.short _02016CAA - _02016C42 - 2; case 1
	.short _02016D02 - _02016C42 - 2; case 2
	.short _02016DA4 - _02016C42 - 2; case 3
	.short _02016E46 - _02016C42 - 2; case 4
	.short _02016E9E - _02016C42 - 2; case 5
	.short _02016EF6 - _02016C42 - 2; case 6
	.short _02016F98 - _02016C42 - 2; case 7
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
	ldr r2, _02016FB4 ; =0x04000008
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
	ldr r2, _02016FB8 ; =0x0400000A
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
	ldr r7, _02016FBC ; =0x0400000C
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
	ldr r7, _02016FBC ; =0x0400000C
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
	ldr r7, _02016FBC ; =0x0400000C
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
	ldr r0, _02016FBC ; =0x0400000C
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
	ldr r7, _02016FC0 ; =0x0400000E
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
	ldr r7, _02016FC0 ; =0x0400000E
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
	ldr r7, _02016FC0 ; =0x0400000E
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
	ldr r0, _02016FC0 ; =0x0400000E
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
	ldr r2, _02016FC4 ; =0x04001008
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
	ldr r2, _02016FC8 ; =0x0400100A
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
	ldr r7, _02016FCC ; =0x0400100C
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
	ldr r7, _02016FCC ; =0x0400100C
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
	ldr r7, _02016FCC ; =0x0400100C
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
	ldr r0, _02016FCC ; =0x0400100C
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
	ldr r7, _02016FD0 ; =0x0400100E
	b _02016FD4
	.balign 4
_02016FB4: .word 0x04000008
_02016FB8: .word 0x0400000A
_02016FBC: .word 0x0400000C
_02016FC0: .word 0x0400000E
_02016FC4: .word 0x04001008
_02016FC8: .word 0x0400100A
_02016FCC: .word 0x0400100C
_02016FD0: .word 0x0400100E
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
	ldr r7, _020170F0 ; =0x0400100E
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
	ldr r7, _020170F0 ; =0x0400100E
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
	ldr r0, _020170F0 ; =0x0400100E
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
	nop
_020170F0: .word 0x0400100E

	thumb_func_start FUN_020170F4
FUN_020170F4: ; 0x020170F4
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
_0201711E: ; jump table (using 16-bit offset)
	.short _0201712E - _0201711E - 2; case 0
	.short _0201719A - _0201711E - 2; case 1
	.short _02017206 - _0201711E - 2; case 2
	.short _0201733A - _0201711E - 2; case 3
	.short _0201746E - _0201711E - 2; case 4
	.short _020174F4 - _0201711E - 2; case 5
	.short _02017560 - _0201711E - 2; case 6
	.short _02017694 - _0201711E - 2; case 7
_0201712E:
	ldr r2, _02017480 ; =0x04000008
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x1e]
	bne _0201714A
	ldrh r3, [r2, #0x1e]
	ldr r1, _02017484 ; =0xFFFFE0FF
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
	ldr r0, _02017480 ; =0x04000008
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
	ldr r2, _02017488 ; =0x0400000A
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x1c]
	bne _020171B6
	ldrh r3, [r2, #0x1c]
	ldr r1, _02017484 ; =0xFFFFE0FF
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
	ldr r0, _02017488 ; =0x0400000A
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
	ldr r3, _0201748C ; =0x0400000C
	cmp r1, #0x1
	ldrh r4, [r3, #0x0]
	add r3, sp, #0x0
	strh r4, [r3, #0x1a]
	bne _02017236
	ldrh r4, [r3, #0x1a]
	ldr r1, _02017484 ; =0xFFFFE0FF
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
	ldr r6, _0201748C ; =0x0400000C
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
	ldr r2, _0201748C ; =0x0400000C
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x18]
	bne _02017296
	ldrh r3, [r2, #0x18]
	ldr r1, _02017484 ; =0xFFFFE0FF
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
	ldr r6, _0201748C ; =0x0400000C
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
	ldr r2, _0201748C ; =0x0400000C
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x16]
	bne _020172F6
	ldrh r3, [r2, #0x16]
	ldr r1, _02017484 ; =0xFFFFE0FF
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
	ldr r6, _0201748C ; =0x0400000C
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
	ldr r3, _02017490 ; =0x0400000E
	cmp r1, #0x1
	ldrh r4, [r3, #0x0]
	add r3, sp, #0x0
	strh r4, [r3, #0x14]
	bne _0201736A
	ldrh r4, [r3, #0x14]
	ldr r1, _02017484 ; =0xFFFFE0FF
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
	ldr r6, _02017490 ; =0x0400000E
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
	ldr r2, _02017490 ; =0x0400000E
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x12]
	bne _020173CA
	ldrh r3, [r2, #0x12]
	ldr r1, _02017484 ; =0xFFFFE0FF
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
	ldr r6, _02017490 ; =0x0400000E
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
	ldr r2, _02017490 ; =0x0400000E
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x10]
	bne _0201742A
	ldrh r3, [r2, #0x10]
	ldr r1, _02017484 ; =0xFFFFE0FF
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
	ldr r6, _02017490 ; =0x0400000E
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
	ldr r2, _02017494 ; =0x04001008
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0xe]
	bne _020174A4
	ldrh r3, [r2, #0xe]
	ldr r1, _02017484 ; =0xFFFFE0FF
	b _02017498
	.balign 4
_02017480: .word 0x04000008
_02017484: .word 0xFFFFE0FF
_02017488: .word 0x0400000A
_0201748C: .word 0x0400000C
_02017490: .word 0x0400000E
_02017494: .word 0x04001008
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
	ldr r0, _020177C8 ; =0x04001008
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
	ldr r2, _020177CC ; =0x0400100A
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0xc]
	bne _02017510
	ldrh r3, [r2, #0xc]
	ldr r1, _020177D0 ; =0xFFFFE0FF
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
	ldr r0, _020177CC ; =0x0400100A
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
	ldr r3, _020177D4 ; =0x0400100C
	cmp r1, #0x1
	ldrh r4, [r3, #0x0]
	add r3, sp, #0x0
	strh r4, [r3, #0xa]
	bne _02017590
	ldrh r4, [r3, #0xa]
	ldr r1, _020177D0 ; =0xFFFFE0FF
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
	ldr r6, _020177D4 ; =0x0400100C
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
	ldr r2, _020177D4 ; =0x0400100C
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x8]
	bne _020175F0
	ldrh r3, [r2, #0x8]
	ldr r1, _020177D0 ; =0xFFFFE0FF
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
	ldr r6, _020177D4 ; =0x0400100C
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
	ldr r2, _020177D4 ; =0x0400100C
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x6]
	bne _02017650
	ldrh r3, [r2, #0x6]
	ldr r1, _020177D0 ; =0xFFFFE0FF
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
	ldr r6, _020177D4 ; =0x0400100C
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
	ldr r3, _020177D8 ; =0x0400100E
	cmp r1, #0x1
	ldrh r4, [r3, #0x0]
	add r3, sp, #0x0
	strh r4, [r3, #0x4]
	bne _020176C4
	ldrh r4, [r3, #0x4]
	ldr r1, _020177D0 ; =0xFFFFE0FF
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
	ldr r6, _020177D8 ; =0x0400100E
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
	ldr r2, _020177D8 ; =0x0400100E
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x2]
	bne _02017724
	ldrh r3, [r2, #0x2]
	ldr r1, _020177D0 ; =0xFFFFE0FF
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
	ldr r6, _020177D8 ; =0x0400100E
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
	ldr r2, _020177D8 ; =0x0400100E
	cmp r1, #0x1
	ldrh r3, [r2, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x0]
	bne _02017784
	ldrh r3, [r2, #0x0]
	ldr r1, _020177D0 ; =0xFFFFE0FF
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
	ldr r6, _020177D8 ; =0x0400100E
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
	.balign 4
_020177C8: .word 0x04001008
_020177CC: .word 0x0400100A
_020177D0: .word 0xFFFFE0FF
_020177D4: .word 0x0400100C
_020177D8: .word 0x0400100E

	thumb_func_start FUN_020177DC
FUN_020177DC: ; 0x020177DC
	cmp r1, #0x0
	beq _020177EA
	cmp r1, #0x1
	beq _0201780A
	cmp r1, #0x2
	beq _0201782A
	b _0201784A
_020177EA:
	cmp r0, #0x1
	bne _020177F2
	mov r0, #0x0
	bx lr
_020177F2:
	cmp r0, #0x2
	bne _020177FA
	mov r0, #0x2
	bx lr
_020177FA:
	cmp r0, #0x3
	bne _02017802
	mov r0, #0x1
	bx lr
_02017802:
	cmp r0, #0x4
	bne _0201784A
	mov r0, #0x3
	bx lr
_0201780A:
	cmp r0, #0x0
	bne _02017812
	mov r0, #0x0
	bx lr
_02017812:
	cmp r0, #0x1
	bne _0201781A
	mov r0, #0x1
	bx lr
_0201781A:
	cmp r0, #0x4
	bne _02017822
	mov r0, #0x2
	bx lr
_02017822:
	cmp r0, #0x5
	bne _0201784A
	mov r0, #0x3
	bx lr
_0201782A:
	cmp r0, #0x0
	bne _02017832
	mov r0, #0x0
	bx lr
_02017832:
	cmp r0, #0x1
	bne _0201783A
	mov r0, #0x1
	bx lr
_0201783A:
	cmp r0, #0x4
	bne _02017842
	mov r0, #0x2
	bx lr
_02017842:
	cmp r0, #0x5
	bne _0201784A
	mov r0, #0x3
	bx lr
_0201784A:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02017850
FUN_02017850: ; 0x02017850
	cmp r0, #0x5
	bhi _0201789E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02017860: ; jump table (using 16-bit offset)
	.short _0201786C - _02017860 - 2; case 0
	.short _02017874 - _02017860 - 2; case 1
	.short _0201787C - _02017860 - 2; case 2
	.short _02017886 - _02017860 - 2; case 3
	.short _02017890 - _02017860 - 2; case 4
	.short _02017898 - _02017860 - 2; case 5
_0201786C:
	mov r0, #0x10
	strb r0, [r1, #0x0]
	strb r0, [r2, #0x0]
	bx lr
_02017874:
	mov r0, #0x20
	strb r0, [r1, #0x0]
	strb r0, [r2, #0x0]
	bx lr
_0201787C:
	mov r0, #0x20
	strb r0, [r1, #0x0]
	mov r0, #0x40
	strb r0, [r2, #0x0]
	bx lr
_02017886:
	mov r0, #0x40
	strb r0, [r1, #0x0]
	mov r0, #0x20
	strb r0, [r2, #0x0]
	bx lr
_02017890:
	mov r0, #0x40
	strb r0, [r1, #0x0]
	strb r0, [r2, #0x0]
	bx lr
_02017898:
	mov r0, #0x80
	strb r0, [r1, #0x0]
	strb r0, [r2, #0x0]
_0201789E:
	bx lr

	thumb_func_start FUN_020178A0
FUN_020178A0: ; 0x020178A0
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r2, #0x2c
	add r5, r1, #0x0
	mul r5, r2
	add r4, #0x8
	ldr r0, [r4, r5]
	cmp r0, #0x0
	beq _020178BA
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, r5]
_020178BA:
	pop {r3-r5, pc}

	thumb_func_start FUN_020178BC
FUN_020178BC: ; 0x020178BC
	cmp r0, #0x7
	bhi _0201795A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020178CC: ; jump table (using 16-bit offset)
	.short _020178DC - _020178CC - 2; case 0
	.short _020178EC - _020178CC - 2; case 1
	.short _020178FC - _020178CC - 2; case 2
	.short _0201790C - _020178CC - 2; case 3
	.short _0201791C - _020178CC - 2; case 4
	.short _0201792C - _020178CC - 2; case 5
	.short _0201793C - _020178CC - 2; case 6
	.short _0201794C - _020178CC - 2; case 7
_020178DC:
	ldr r2, _0201795C ; =0x04000008
	mov r0, #0x3
	ldrh r3, [r2, #0x0]
	bic r3, r0
	add r0, r3, #0x0
	orr r0, r1
	strh r0, [r2, #0x0]
	bx lr
_020178EC:
	ldr r2, _02017960 ; =0x0400000A
	mov r0, #0x3
	ldrh r3, [r2, #0x0]
	bic r3, r0
	add r0, r3, #0x0
	orr r0, r1
	strh r0, [r2, #0x0]
	bx lr
_020178FC:
	ldr r2, _02017964 ; =0x0400000C
	mov r0, #0x3
	ldrh r3, [r2, #0x0]
	bic r3, r0
	add r0, r3, #0x0
	orr r0, r1
	strh r0, [r2, #0x0]
	bx lr
_0201790C:
	ldr r2, _02017968 ; =0x0400000E
	mov r0, #0x3
	ldrh r3, [r2, #0x0]
	bic r3, r0
	add r0, r3, #0x0
	orr r0, r1
	strh r0, [r2, #0x0]
	bx lr
_0201791C:
	ldr r2, _0201796C ; =0x04001008
	mov r0, #0x3
	ldrh r3, [r2, #0x0]
	bic r3, r0
	add r0, r3, #0x0
	orr r0, r1
	strh r0, [r2, #0x0]
	bx lr
_0201792C:
	ldr r2, _02017970 ; =0x0400100A
	mov r0, #0x3
	ldrh r3, [r2, #0x0]
	bic r3, r0
	add r0, r3, #0x0
	orr r0, r1
	strh r0, [r2, #0x0]
	bx lr
_0201793C:
	ldr r2, _02017974 ; =0x0400100C
	mov r0, #0x3
	ldrh r3, [r2, #0x0]
	bic r3, r0
	add r0, r3, #0x0
	orr r0, r1
	strh r0, [r2, #0x0]
	bx lr
_0201794C:
	ldr r2, _02017978 ; =0x0400100E
	mov r0, #0x3
	ldrh r3, [r2, #0x0]
	bic r3, r0
	add r0, r3, #0x0
	orr r0, r1
	strh r0, [r2, #0x0]
_0201795A:
	bx lr
	.balign 4
_0201795C: .word 0x04000008
_02017960: .word 0x0400000A
_02017964: .word 0x0400000C
_02017968: .word 0x0400000E
_0201796C: .word 0x04001008
_02017970: .word 0x0400100A
_02017974: .word 0x0400100C
_02017978: .word 0x0400100E

	thumb_func_start FUN_0201797C
FUN_0201797C: ; 0x0201797C
	push {r3, lr}
	cmp r0, #0x7
	bhi _020179DC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0201798E: ; jump table (using 16-bit offset)
	.short _0201799E - _0201798E - 2; case 0
	.short _020179A6 - _0201798E - 2; case 1
	.short _020179AE - _0201798E - 2; case 2
	.short _020179B6 - _0201798E - 2; case 3
	.short _020179BE - _0201798E - 2; case 4
	.short _020179C6 - _0201798E - 2; case 5
	.short _020179CE - _0201798E - 2; case 6
	.short _020179D6 - _0201798E - 2; case 7
_0201799E:
	mov r0, #0x1
	bl GX_EngineAToggleLayers
	pop {r3, pc}
_020179A6:
	mov r0, #0x2
	bl GX_EngineAToggleLayers
	pop {r3, pc}
_020179AE:
	mov r0, #0x4
	bl GX_EngineAToggleLayers
	pop {r3, pc}
_020179B6:
	mov r0, #0x8
	bl GX_EngineAToggleLayers
	pop {r3, pc}
_020179BE:
	mov r0, #0x1
	bl GX_EngineBToggleLayers
	pop {r3, pc}
_020179C6:
	mov r0, #0x2
	bl GX_EngineBToggleLayers
	pop {r3, pc}
_020179CE:
	mov r0, #0x4
	bl GX_EngineBToggleLayers
	pop {r3, pc}
_020179D6:
	mov r0, #0x8
	bl GX_EngineBToggleLayers
_020179DC:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020179E0
FUN_020179E0: ; 0x020179E0
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	mov r0, #0x2c
	add r6, r5, #0x0
	mul r6, r0
	add r0, r4, #0x0
	add r0, #0x8
	add r1, r2, #0x0
	add r2, r3, #0x0
	add r0, r0, r6
	bl FUN_02017B8C
	add r0, r4, r6
	ldr r1, [r0, #0x14]
	ldr r0, [r0, #0x18]
	cmp r5, #0x7
	bls _02017A06
	b _02017B1C
_02017A06:
	add r2, r5, r5
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02017A12: ; jump table (using 16-bit offset)
	.short _02017A22 - _02017A12 - 2; case 0
	.short _02017A38 - _02017A12 - 2; case 1
	.short _02017A4E - _02017A12 - 2; case 2
	.short _02017A78 - _02017A12 - 2; case 3
	.short _02017AA2 - _02017A12 - 2; case 4
	.short _02017AB8 - _02017A12 - 2; case 5
	.short _02017ACE - _02017A12 - 2; case 6
	.short _02017AF6 - _02017A12 - 2; case 7
_02017A22:
	ldr r2, _02017B20 ; =0x000001FF
	add r3, r1, #0x0
	lsl r1, r0, #0x10
	lsl r0, r2, #0x10
	and r3, r2
	and r0, r1
	add r1, r3, #0x0
	orr r1, r0
	ldr r0, _02017B24 ; =0x04000010
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
_02017A38:
	ldr r2, _02017B20 ; =0x000001FF
	add r3, r1, #0x0
	lsl r1, r0, #0x10
	lsl r0, r2, #0x10
	and r3, r2
	and r0, r1
	add r1, r3, #0x0
	orr r1, r0
	ldr r0, _02017B28 ; =0x04000014
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
_02017A4E:
	add r2, r4, #0x0
	add r2, #0x74
	ldrb r2, [r2, #0x0]
	cmp r2, #0x0
	bne _02017A6E
	ldr r2, _02017B20 ; =0x000001FF
	add r3, r1, #0x0
	lsl r1, r0, #0x10
	lsl r0, r2, #0x10
	and r3, r2
	and r0, r1
	add r1, r3, #0x0
	orr r1, r0
	ldr r0, _02017B2C ; =0x04000018
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
_02017A6E:
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02017C6C
	pop {r4-r6, pc}
_02017A78:
	add r2, r4, #0x0
	add r2, #0xa0
	ldrb r2, [r2, #0x0]
	cmp r2, #0x0
	bne _02017A98
	ldr r2, _02017B20 ; =0x000001FF
	add r3, r1, #0x0
	lsl r1, r0, #0x10
	lsl r0, r2, #0x10
	and r3, r2
	and r0, r1
	add r1, r3, #0x0
	orr r1, r0
	ldr r0, _02017B30 ; =0x0400001C
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
_02017A98:
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_02017C6C
	pop {r4-r6, pc}
_02017AA2:
	ldr r2, _02017B20 ; =0x000001FF
	add r3, r1, #0x0
	lsl r1, r0, #0x10
	lsl r0, r2, #0x10
	and r3, r2
	and r0, r1
	add r1, r3, #0x0
	orr r1, r0
	ldr r0, _02017B34 ; =0x04001010
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
_02017AB8:
	ldr r2, _02017B20 ; =0x000001FF
	add r3, r1, #0x0
	lsl r1, r0, #0x10
	lsl r0, r2, #0x10
	and r3, r2
	and r0, r1
	add r1, r3, #0x0
	orr r1, r0
	ldr r0, _02017B38 ; =0x04001014
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
_02017ACE:
	mov r2, #0x49
	lsl r2, r2, #0x2
	ldrb r3, [r4, r2]
	cmp r3, #0x0
	bne _02017AEC
	add r2, #0xdb
	and r2, r1
	lsl r1, r0, #0x10
	ldr r0, _02017B3C ; =0x01FF0000
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, _02017B40 ; =0x04001018
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
_02017AEC:
	add r0, r4, #0x0
	mov r1, #0x6
	bl FUN_02017C6C
	pop {r4-r6, pc}
_02017AF6:
	mov r2, #0x15
	lsl r2, r2, #0x4
	ldrb r3, [r4, r2]
	cmp r3, #0x0
	bne _02017B14
	add r2, #0xaf
	and r2, r1
	lsl r1, r0, #0x10
	ldr r0, _02017B3C ; =0x01FF0000
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, _02017B44 ; =0x0400101C
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
_02017B14:
	add r0, r4, #0x0
	mov r1, #0x7
	bl FUN_02017C6C
_02017B1C:
	pop {r4-r6, pc}
	nop
_02017B20: .word 0x000001FF
_02017B24: .word 0x04000010
_02017B28: .word 0x04000014
_02017B2C: .word 0x04000018
_02017B30: .word 0x0400001C
_02017B34: .word 0x04001010
_02017B38: .word 0x04001014
_02017B3C: .word 0x01FF0000
_02017B40: .word 0x04001018
_02017B44: .word 0x0400101C

	thumb_func_start FUN_02017B48
FUN_02017B48: ; 0x02017B48
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	ldr r0, [r0, #0x14]
	bx lr
	.balign 4

	thumb_func_start FUN_02017B54
FUN_02017B54: ; 0x02017B54
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	ldr r0, [r0, #0x18]
	bx lr
	.balign 4

	thumb_func_start FUN_02017B60
FUN_02017B60: ; 0x02017B60
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x0
	mov r0, #0x2c
	add r1, #0x8
	mul r0, r4
	add r0, r1, r0
	add r1, r2, #0x0
	add r2, r3, #0x0
	bl FUN_02017B8C
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x10]
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x14]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02017BD0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02017B8C
FUN_02017B8C: ; 0x02017B8C
	cmp r1, #0x5
	bhi _02017BCE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02017B9C: ; jump table (using 16-bit offset)
	.short _02017BA8 - _02017B9C - 2; case 0
	.short _02017BAC - _02017B9C - 2; case 1
	.short _02017BB4 - _02017B9C - 2; case 2
	.short _02017BBC - _02017B9C - 2; case 3
	.short _02017BC0 - _02017B9C - 2; case 4
	.short _02017BC8 - _02017B9C - 2; case 5
_02017BA8:
	str r2, [r0, #0xc]
	bx lr
_02017BAC:
	ldr r1, [r0, #0xc]
	add r1, r1, r2
	str r1, [r0, #0xc]
	bx lr
_02017BB4:
	ldr r1, [r0, #0xc]
	sub r1, r1, r2
	str r1, [r0, #0xc]
	bx lr
_02017BBC:
	str r2, [r0, #0x10]
	bx lr
_02017BC0:
	ldr r1, [r0, #0x10]
	add r1, r1, r2
	str r1, [r0, #0x10]
	bx lr
_02017BC8:
	ldr r1, [r0, #0x10]
	sub r1, r1, r2
	str r1, [r0, #0x10]
_02017BCE:
	bx lr

	thumb_func_start FUN_02017BD0
FUN_02017BD0: ; 0x02017BD0
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	add r1, r2, #0x0
	add r2, r3, #0x0
	ldr r3, [sp, #0x18]
	cmp r4, #0x7
	bhi _02017C58
	add r5, r4, r4
	add r5, pc
	ldrh r5, [r5, #0x6]
	lsl r5, r5, #0x10
	asr r5, r5, #0x10
	add pc, r5
_02017BEC: ; jump table (using 16-bit offset)
	.short _02017C58 - _02017BEC - 2; case 0
	.short _02017C58 - _02017BEC - 2; case 1
	.short _02017BFC - _02017BEC - 2; case 2
	.short _02017C14 - _02017BEC - 2; case 3
	.short _02017C58 - _02017BEC - 2; case 4
	.short _02017C58 - _02017BEC - 2; case 5
	.short _02017C2C - _02017BEC - 2; case 6
	.short _02017C44 - _02017BEC - 2; case 7
_02017BFC:
	mov r5, #0x2c
	mul r5, r4
	add r4, r0, r5
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0x4]
	ldr r0, _02017C5C ; =0x04000020
	bl G2x_SetBGyAffine_
	add sp, #0x8
	pop {r3-r5, pc}
_02017C14:
	mov r5, #0x2c
	mul r5, r4
	add r4, r0, r5
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0x4]
	ldr r0, _02017C60 ; =0x04000030
	bl G2x_SetBGyAffine_
	add sp, #0x8
	pop {r3-r5, pc}
_02017C2C:
	mov r5, #0x2c
	mul r5, r4
	add r4, r0, r5
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0x4]
	ldr r0, _02017C64 ; =0x04001020
	bl G2x_SetBGyAffine_
	add sp, #0x8
	pop {r3-r5, pc}
_02017C44:
	mov r5, #0x2c
	mul r5, r4
	add r4, r0, r5
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0x4]
	ldr r0, _02017C68 ; =0x04001030
	bl G2x_SetBGyAffine_
_02017C58:
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_02017C5C: .word 0x04000020
_02017C60: .word 0x04000030
_02017C64: .word 0x04001020
_02017C68: .word 0x04001030

	thumb_func_start FUN_02017C6C
FUN_02017C6C: ; 0x02017C6C
	push {r4-r5, lr}
	sub sp, #0x14
	mov r2, #0x1
	lsl r2, r2, #0xc
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r1, #0x0
	add r0, sp, #0x4
	add r3, r2, #0x0
	str r1, [sp, #0x0]
	bl MTX22_2DAffine
	mov r3, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, sp, #0x4
	str r3, [sp, #0x0]
	bl FUN_02017BD0
	add sp, #0x14
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_02017C98
FUN_02017C98: ; 0x02017C98
	push {r3-r5, lr}
	cmp r2, #0x0
	bne _02017CA4
	bl MI_UncompressLZ8
	pop {r3-r5, pc}
_02017CA4:
	mov r4, #0x3
	add r3, r0, #0x0
	tst r3, r4
	bne _02017CCA
	add r3, r1, #0x0
	tst r3, r4
	bne _02017CCA
	lsl r3, r2, #0x10
	lsr r3, r3, #0x10
	lsr r4, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r4
	mov r3, #0x1e
	ror r5, r3
	add r3, r4, r5
	bne _02017CCA
	bl MIi_CpuCopy32
	pop {r3-r5, pc}
_02017CCA:
	bl MIi_CpuCopy16
	pop {r3-r5, pc}

	thumb_func_start FUN_02017CD0
FUN_02017CD0: ; 0x02017CD0
	push {r3, lr}
	mov r2, #0x2c
	mul r2, r1
	add r3, r0, r2
	ldr r2, [r3, #0x10]
	str r2, [sp, #0x0]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	bl FUN_02017CE8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02017CE8
FUN_02017CE8: ; 0x02017CE8
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	cmp r3, #0x0
	bne _02017D56
	mov r0, #0x2c
	add r7, r4, #0x0
	mul r7, r0
	add r0, r5, r7
	ldr r0, [r0, #0x8]
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _02017D26
	ldr r1, [sp, #0x4]
	add r0, r6, #0x0
	add r2, r3, #0x0
	bl FUN_02017C98
	add r3, r5, r7
	ldr r2, [r3, #0x10]
	ldr r1, [sp, #0x4]
	ldr r3, [r3, #0xc]
	add r0, r4, #0x0
	lsl r2, r2, #0x1
	bl FUN_02017D68
	add sp, #0x8
	pop {r3-r7, pc}
_02017D26:
	ldr r0, [r6, #0x0]
	lsr r7, r0, #0x8
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	bl AllocFromHeapAtEnd
	add r5, r0, #0x0
	ldr r2, [sp, #0x0]
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02017C98
	ldr r2, [sp, #0x20]
	add r0, r4, #0x0
	add r1, r5, #0x0
	lsl r2, r2, #0x1
	add r3, r7, #0x0
	bl FUN_02017D68
	add r0, r5, #0x0
	bl FreeToHeap
	add sp, #0x8
	pop {r3-r7, pc}
_02017D56:
	ldr r2, [sp, #0x20]
	add r0, r4, #0x0
	add r1, r6, #0x0
	lsl r2, r2, #0x1
	bl FUN_02017D68
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02017D68
FUN_02017D68: ; 0x02017D68
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r6, r3, #0x0
	add r7, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r5, r2, #0x0
	bl DC_FlushRange
	cmp r7, #0x7
	bhi _02017DF8
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02017D8A: ; jump table (using 16-bit offset)
	.short _02017D9A - _02017D8A - 2; case 0
	.short _02017DA6 - _02017D8A - 2; case 1
	.short _02017DB2 - _02017D8A - 2; case 2
	.short _02017DBE - _02017D8A - 2; case 3
	.short _02017DCA - _02017D8A - 2; case 4
	.short _02017DD6 - _02017D8A - 2; case 5
	.short _02017DE2 - _02017D8A - 2; case 6
	.short _02017DEE - _02017D8A - 2; case 7
_02017D9A:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GX_LoadBG0Scr
	pop {r3-r7, pc}
_02017DA6:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GX_LoadBG1Scr
	pop {r3-r7, pc}
_02017DB2:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GX_LoadBG2Scr
	pop {r3-r7, pc}
_02017DBE:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GX_LoadBG3Scr
	pop {r3-r7, pc}
_02017DCA:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GXS_LoadBG0Scr
	pop {r3-r7, pc}
_02017DD6:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GXS_LoadBG1Scr
	pop {r3-r7, pc}
_02017DE2:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GXS_LoadBG2Scr
	pop {r3-r7, pc}
_02017DEE:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GXS_LoadBG3Scr
_02017DF8:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02017DFC
FUN_02017DFC: ; 0x02017DFC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r2, #0x0
	mov r2, #0x2c
	mul r2, r1
	add r1, r4, r2
	ldr r1, [r1, #0x8]
	add r2, r3, #0x0
	bl FUN_02017C98
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02017E14
FUN_02017E14: ; 0x02017E14
	push {r3-r4, lr}
	sub sp, #0x4
	mov r4, #0x2c
	mul r4, r1
	add r4, r0, r4
	ldrb r4, [r4, #0x1e]
	cmp r4, #0x0
	bne _02017E32
	ldr r4, [sp, #0x10]
	lsl r4, r4, #0x5
	str r4, [sp, #0x0]
	bl FUN_02017E40
	add sp, #0x4
	pop {r3-r4, pc}
_02017E32:
	ldr r4, [sp, #0x10]
	lsl r4, r4, #0x6
	str r4, [sp, #0x0]
	bl FUN_02017E40
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02017E40
FUN_02017E40: ; 0x02017E40
	push {r3-r7, lr}
	add r7, r1, #0x0
	add r5, r2, #0x0
	str r3, [sp, #0x0]
	cmp r3, #0x0
	bne _02017E78
	ldr r1, [r5, #0x0]
	ldr r0, [r0, #0x0]
	lsr r4, r1, #0x8
	add r1, r4, #0x0
	bl AllocFromHeapAtEnd
	add r6, r0, #0x0
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02017C98
	ldr r2, [sp, #0x18]
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r3, r4, #0x0
	bl FUN_02017E84
	add r0, r6, #0x0
	bl FreeToHeap
	pop {r3-r7, pc}
_02017E78:
	ldr r2, [sp, #0x18]
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl FUN_02017E84
	pop {r3-r7, pc}

	thumb_func_start FUN_02017E84
FUN_02017E84: ; 0x02017E84
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r6, r3, #0x0
	add r7, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r5, r2, #0x0
	bl DC_FlushRange
	cmp r7, #0x7
	bhi _02017F14
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02017EA6: ; jump table (using 16-bit offset)
	.short _02017EB6 - _02017EA6 - 2; case 0
	.short _02017EC2 - _02017EA6 - 2; case 1
	.short _02017ECE - _02017EA6 - 2; case 2
	.short _02017EDA - _02017EA6 - 2; case 3
	.short _02017EE6 - _02017EA6 - 2; case 4
	.short _02017EF2 - _02017EA6 - 2; case 5
	.short _02017EFE - _02017EA6 - 2; case 6
	.short _02017F0A - _02017EA6 - 2; case 7
_02017EB6:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GX_LoadBG0Char
	pop {r3-r7, pc}
_02017EC2:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GX_LoadBG1Char
	pop {r3-r7, pc}
_02017ECE:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GX_LoadBG2Char
	pop {r3-r7, pc}
_02017EDA:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GX_LoadBG3Char
	pop {r3-r7, pc}
_02017EE6:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GXS_LoadBG0Char
	pop {r3-r7, pc}
_02017EF2:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GXS_LoadBG1Char
	pop {r3-r7, pc}
_02017EFE:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GXS_LoadBG2Char
	pop {r3-r7, pc}
_02017F0A:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl GXS_LoadBG3Char
_02017F14:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02017F18
FUN_02017F18: ; 0x02017F18
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r0, r3, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	mov r1, #0x0
	add r2, r5, #0x0
	bl memset
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	add r3, r5, #0x0
	bl FUN_02017E84
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	bl FUN_02016A8C
	pop {r3-r7, pc}

	thumb_func_start FUN_02017F48
FUN_02017F48: ; 0x02017F48
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r1, #0x0
	add r4, r0, #0x0
	mov r1, #0x2c
	add r6, r7, #0x0
	add r4, #0x1f
	mul r6, r1
	ldrb r1, [r4, r6]
	ldr r0, [r0, #0x0]
	add r5, r2, #0x0
	mul r1, r3
	str r1, [sp, #0x0]
	bl AllocFromHeapAtEnd
	str r0, [sp, #0x4]
	ldrb r0, [r4, r6]
	cmp r0, #0x20
	bne _02017F82
	lsl r2, r5, #0xc
	lsl r1, r5, #0x8
	lsl r0, r5, #0x4
	orr r1, r2
	orr r0, r1
	add r1, r5, #0x0
	orr r1, r0
	lsl r0, r1, #0x10
	add r5, r1, #0x0
	b _02017F8C
_02017F82:
	lsl r2, r5, #0x18
	lsl r1, r5, #0x10
	lsl r0, r5, #0x8
	orr r1, r2
	orr r0, r1
_02017F8C:
	orr r5, r0
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	bl MIi_CpuClearFast
	lsl r0, r7, #0x18
	ldrb r2, [r4, r6]
	ldr r3, [sp, #0x20]
	ldr r1, [sp, #0x4]
	mul r2, r3
	ldr r3, [sp, #0x0]
	lsr r0, r0, #0x18
	bl FUN_02017E84
	ldr r0, [sp, #0x4]
	bl FreeToHeap
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02017FB4
FUN_02017FB4: ; 0x02017FB4
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r7, r3, #0x0
	bl DC_FlushRange
	cmp r6, #0x4
	bhs _02017FD6
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, r4, #0x0
	bl GX_LoadBGPltt
	pop {r3-r7, pc}
_02017FD6:
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, r4, #0x0
	bl GXS_LoadBGPltt
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02017FE4
FUN_02017FE4: ; 0x02017FE4
	push {r0-r3}
	push {r3, lr}
	add r1, sp, #0xc
	mov r2, #0x2
	mov r3, #0x0
	bl FUN_02017FB4
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4

	thumb_func_start FUN_02017FFC
FUN_02017FFC: ; 0x02017FFC
	cmp r2, #0x5
	bhi _02018066
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0201800C: ; jump table (using 16-bit offset)
	.short _02018018 - _0201800C - 2; case 0
	.short _02018022 - _0201800C - 2; case 1
	.short _02018022 - _0201800C - 2; case 2
	.short _0201802C - _0201800C - 2; case 3
	.short _02018042 - _0201800C - 2; case 4
	.short _02018064 - _0201800C - 2; case 5
_02018018:
	lsl r1, r1, #0x4
	add r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
_02018022:
	lsl r1, r1, #0x5
	add r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
_0201802C:
	mov r2, #0x1f
	add r3, r0, #0x0
	and r3, r2
	mov r2, #0x1f
	bic r0, r2
	add r0, r1, r0
	lsl r0, r0, #0x5
	add r0, r3, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
_02018042:
	asr r2, r1, #0x5
	asr r3, r0, #0x5
	lsl r2, r2, #0x1
	add r2, r3, r2
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	lsl r2, r2, #0x1a
	lsr r3, r2, #0x10
	mov r2, #0x1f
	and r2, r0
	lsl r0, r1, #0x1b
	lsr r0, r0, #0x16
	add r0, r2, r0
	add r0, r3, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
_02018064:
	mov r0, #0x0
_02018066:
	bx lr

	thumb_func_start FUN_02018068
FUN_02018068: ; 0x02018068
	push {r3-r7}
	sub sp, #0x4
	str r3, [sp, #0x0]
	add r6, r2, #0x0
	ldr r5, [sp, #0x0]
	add r4, r6, #0x0
	sub r4, #0x20
	sub r5, #0x20
	mov r2, #0x0
	lsl r4, r4, #0x10
	lsl r5, r5, #0x10
	add r3, r2, #0x0
	asr r4, r4, #0x10
	asr r7, r5, #0x10
	lsr r5, r0, #0x5
	beq _0201808E
	add r2, r2, #0x1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
_0201808E:
	lsr r5, r1, #0x5
	beq _02018098
	add r2, r2, #0x2
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
_02018098:
	cmp r2, #0x3
	bhi _02018140
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_020180A8: ; jump table (using 16-bit offset)
	.short _020180B0 - _020180A8 - 2; case 0
	.short _020180CE - _020180A8 - 2; case 1
	.short _020180F4 - _020180A8 - 2; case 2
	.short _02018120 - _020180A8 - 2; case 3
_020180B0:
	cmp r4, #0x0
	blt _020180C0
	lsl r1, r1, #0x5
	add r0, r0, r1
	add r0, r3, r0
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	b _02018140
_020180C0:
	add r2, r1, #0x0
	mul r2, r6
	add r0, r0, r2
	add r0, r3, r0
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	b _02018140
_020180CE:
	cmp r7, #0x0
	blt _020180D8
	mov r2, #0x1
	lsl r2, r2, #0xa
	b _020180DC
_020180D8:
	ldr r2, [sp, #0x0]
	lsl r2, r2, #0x5
_020180DC:
	add r2, r3, r2
	lsl r2, r2, #0x10
	lsr r3, r2, #0x10
	mov r2, #0x1f
	and r2, r0
	add r0, r1, #0x0
	mul r0, r4
	add r0, r2, r0
	add r0, r3, r0
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	b _02018140
_020180F4:
	lsl r2, r6, #0x5
	add r2, r3, r2
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	cmp r4, #0x0
	blt _0201810E
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x16
	add r0, r0, r1
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	b _02018140
_0201810E:
	mov r3, #0x1f
	and r1, r3
	add r3, r1, #0x0
	mul r3, r6
	add r0, r0, r3
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	b _02018140
_02018120:
	add r2, r6, r7
	lsl r2, r2, #0x5
	add r2, r3, r2
	add r5, r0, #0x0
	mov r3, #0x1f
	add r0, r1, #0x0
	and r0, r3
	add r1, r0, #0x0
	lsl r2, r2, #0x10
	and r5, r3
	mul r1, r4
	lsr r2, r2, #0x10
	add r0, r5, r1
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
_02018140:
	add r0, r3, #0x0
	add sp, #0x4
	pop {r3-r7}
	bx lr

	thumb_func_start FUN_02018148
FUN_02018148: ; 0x02018148
	push {r3-r6, lr}
	sub sp, #0x1c
	add r6, sp, #0x20
	ldrb r5, [r6, #0x14]
	str r5, [sp, #0x0]
	ldrb r4, [r6, #0x18]
	str r4, [sp, #0x4]
	str r2, [sp, #0x8]
	mov r2, #0x0
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	str r5, [sp, #0x14]
	str r4, [sp, #0x18]
	add r2, r3, #0x0
	ldrb r3, [r6, #0x10]
	bl FUN_02018170
	add sp, #0x1c
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02018170
FUN_02018170: ; 0x02018170
	push {r4-r5, lr}
	sub sp, #0x1c
	add r4, r2, #0x0
	add r2, r3, #0x0
	mov r3, #0x2c
	add r5, r1, #0x0
	mul r5, r3
	add r1, r0, r5
	ldrb r1, [r1, #0x1c]
	add r3, sp, #0x18
	cmp r1, #0x1
	beq _020181BA
	ldrb r1, [r3, #0x14]
	add r0, #0x8
	add r0, r0, r5
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x30]
	str r1, [sp, #0x4]
	ldrb r1, [r3, #0x1c]
	str r1, [sp, #0x8]
	add r1, sp, #0x38
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0xc]
	add r1, sp, #0x3c
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0x10]
	add r1, sp, #0x40
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0x14]
	mov r1, #0x0
	str r1, [sp, #0x18]
	ldrb r3, [r3, #0x10]
	add r1, r4, #0x0
	bl FUN_02018268
	add sp, #0x1c
	pop {r4-r5, pc}
_020181BA:
	ldrb r1, [r3, #0x14]
	add r0, #0x8
	add r0, r0, r5
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x30]
	str r1, [sp, #0x4]
	ldrb r1, [r3, #0x1c]
	str r1, [sp, #0x8]
	add r1, sp, #0x38
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0xc]
	add r1, sp, #0x3c
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0x10]
	add r1, sp, #0x40
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0x14]
	mov r1, #0x0
	str r1, [sp, #0x18]
	ldrb r3, [r3, #0x10]
	add r1, r4, #0x0
	bl FUN_020183DC
	add sp, #0x1c
	pop {r4-r5, pc}

	thumb_func_start FUN_020181EC
FUN_020181EC: ; 0x020181EC
	push {r4-r5, lr}
	sub sp, #0x1c
	add r4, r2, #0x0
	add r2, r3, #0x0
	mov r3, #0x2c
	add r5, r1, #0x0
	mul r5, r3
	add r1, r0, r5
	ldrb r1, [r1, #0x1c]
	add r3, sp, #0x18
	cmp r1, #0x1
	beq _02018236
	ldrb r1, [r3, #0x14]
	add r0, #0x8
	add r0, r0, r5
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x30]
	str r1, [sp, #0x4]
	ldrb r1, [r3, #0x1c]
	str r1, [sp, #0x8]
	add r1, sp, #0x38
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0xc]
	add r1, sp, #0x3c
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0x10]
	add r1, sp, #0x40
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0x14]
	mov r1, #0x1
	str r1, [sp, #0x18]
	ldrb r3, [r3, #0x10]
	add r1, r4, #0x0
	bl FUN_02018268
	add sp, #0x1c
	pop {r4-r5, pc}
_02018236:
	ldrb r1, [r3, #0x14]
	add r0, #0x8
	add r0, r0, r5
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x30]
	str r1, [sp, #0x4]
	ldrb r1, [r3, #0x1c]
	str r1, [sp, #0x8]
	add r1, sp, #0x38
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0xc]
	add r1, sp, #0x3c
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0x10]
	add r1, sp, #0x40
	ldrb r1, [r1, #0x0]
	str r1, [sp, #0x14]
	mov r1, #0x1
	str r1, [sp, #0x18]
	ldrb r3, [r3, #0x10]
	add r1, r4, #0x0
	bl FUN_020183DC
	add sp, #0x1c
	pop {r4-r5, pc}

	thumb_func_start FUN_02018268
FUN_02018268: ; 0x02018268
	push {r4-r7, lr}
	sub sp, #0x44
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r7, r0, #0x0
	ldr r0, [sp, #0x58]
	add r6, r3, #0x0
	str r0, [sp, #0x58]
	ldr r0, [sp, #0x5c]
	ldr r4, [sp, #0x68]
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0x6c]
	str r0, [sp, #0x6c]
	ldr r0, [r7, #0x0]
	str r0, [sp, #0x2c]
	cmp r0, #0x0
	bne _0201828C
	b _020183D6
_0201828C:
	ldrb r0, [r7, #0x15]
	add r1, sp, #0x40
	add r1, #0x1
	add r2, sp, #0x40
	bl FUN_02017850
	add r0, sp, #0x70
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201833A
	mov r0, #0x0
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x58]
	cmp r0, #0x0
	bls _020182CA
	add r1, sp, #0x48
	ldrb r0, [r1, #0x1c]
	str r0, [sp, #0x1c]
	ldrb r0, [r1, #0x18]
	str r0, [sp, #0x18]
	lsl r1, r0, #0x1
	ldr r0, [sp, #0x5c]
	add r0, r0, r1
	str r0, [sp, #0x14]
_020182BC:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x28]
	add r0, r1, r0
	add r1, sp, #0x40
	ldrb r1, [r1, #0x0]
	cmp r0, r1
	blt _020182CC
_020182CA:
	b _020183D6
_020182CC:
	ldr r2, [sp, #0x1c]
	ldr r1, [sp, #0x28]
	add r2, r2, r1
	ldr r1, [sp, #0x6c]
	cmp r2, r1
	bge _020183D6
	mov r5, #0x0
	cmp r6, #0x0
	bls _02018326
	add r1, r4, #0x0
	mul r1, r2
	lsl r2, r1, #0x1
	ldr r1, [sp, #0x14]
	lsl r0, r0, #0x18
	add r1, r1, r2
	lsr r0, r0, #0x18
	str r1, [sp, #0x10]
	str r0, [sp, #0x30]
_020182F0:
	add r1, sp, #0x40
	ldr r0, [sp, #0x0]
	ldrb r1, [r1, #0x1]
	add r0, r0, r5
	cmp r0, r1
	bge _02018326
	ldr r1, [sp, #0x18]
	add r1, r1, r5
	cmp r1, r4
	bge _02018326
	ldrb r2, [r7, #0x15]
	lsl r0, r0, #0x18
	ldr r1, [sp, #0x30]
	lsr r0, r0, #0x18
	bl FUN_02017FFC
	ldr r1, [sp, #0x10]
	lsl r2, r5, #0x1
	ldrh r1, [r1, r2]
	lsl r2, r0, #0x1
	ldr r0, [sp, #0x2c]
	strh r1, [r0, r2]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r6
	blo _020182F0
_02018326:
	ldr r0, [sp, #0x28]
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	str r1, [sp, #0x28]
	ldr r0, [sp, #0x58]
	cmp r1, r0
	blo _020182BC
	add sp, #0x44
	pop {r4-r7, pc}
_0201833A:
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x58]
	cmp r0, #0x0
	bls _020183D6
	add r1, sp, #0x48
	ldrb r0, [r1, #0x1c]
	str r0, [sp, #0x24]
	ldrb r0, [r1, #0x18]
	str r0, [sp, #0x20]
_0201834E:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x8]
	add r1, r1, r0
	add r0, sp, #0x40
	ldrb r0, [r0, #0x0]
	cmp r1, r0
	bge _020183D6
	ldr r2, [sp, #0x24]
	ldr r0, [sp, #0x8]
	add r0, r2, r0
	ldr r2, [sp, #0x6c]
	cmp r0, r2
	bge _020183D6
	mov r5, #0x0
	cmp r6, #0x0
	bls _020183C6
	lsl r1, r1, #0x18
	lsl r0, r0, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	str r1, [sp, #0x34]
	str r0, [sp, #0x3c]
_0201837A:
	add r1, sp, #0x40
	ldr r0, [sp, #0x0]
	ldrb r1, [r1, #0x1]
	add r0, r0, r5
	cmp r0, r1
	bge _020183C6
	ldr r1, [sp, #0x20]
	add r1, r1, r5
	str r1, [sp, #0xc]
	cmp r1, r4
	bge _020183C6
	ldrb r2, [r7, #0x15]
	lsl r0, r0, #0x18
	ldr r1, [sp, #0x34]
	lsr r0, r0, #0x18
	bl FUN_02017FFC
	str r0, [sp, #0x38]
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x3c]
	lsl r0, r0, #0x18
	ldr r3, [sp, #0x6c]
	lsr r0, r0, #0x18
	add r2, r4, #0x0
	bl FUN_02018068
	lsl r1, r0, #0x1
	ldr r0, [sp, #0x5c]
	ldrh r0, [r0, r1]
	ldr r1, [sp, #0x38]
	lsl r2, r1, #0x1
	ldr r1, [sp, #0x2c]
	strh r0, [r1, r2]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r6
	blo _0201837A
_020183C6:
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	str r1, [sp, #0x8]
	ldr r0, [sp, #0x58]
	cmp r1, r0
	blo _0201834E
_020183D6:
	add sp, #0x44
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_020183DC
FUN_020183DC: ; 0x020183DC
	push {r4-r7, lr}
	sub sp, #0x44
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r7, r0, #0x0
	ldr r0, [sp, #0x58]
	add r6, r3, #0x0
	str r0, [sp, #0x58]
	ldr r0, [sp, #0x5c]
	ldr r4, [sp, #0x68]
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0x6c]
	str r0, [sp, #0x6c]
	ldr r0, [r7, #0x0]
	str r0, [sp, #0x2c]
	cmp r0, #0x0
	bne _02018400
	b _0201853C
_02018400:
	ldrb r0, [r7, #0x15]
	add r1, sp, #0x40
	add r1, #0x1
	add r2, sp, #0x40
	bl FUN_02017850
	add r0, sp, #0x70
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020184A4
	mov r0, #0x0
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x58]
	cmp r0, #0x0
	bhi _02018420
	b _0201853C
_02018420:
	add r1, sp, #0x48
	ldrb r0, [r1, #0x1c]
	str r0, [sp, #0x1c]
	ldrb r0, [r1, #0x18]
	ldr r1, [sp, #0x5c]
	str r0, [sp, #0x18]
	add r0, r1, r0
	str r0, [sp, #0x14]
_02018430:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x28]
	add r0, r1, r0
	add r1, sp, #0x40
	ldrb r1, [r1, #0x0]
	cmp r0, r1
	bge _0201853C
	ldr r2, [sp, #0x1c]
	ldr r1, [sp, #0x28]
	add r2, r2, r1
	ldr r1, [sp, #0x6c]
	cmp r2, r1
	bge _0201853C
	mov r5, #0x0
	cmp r6, #0x0
	bls _02018490
	ldr r1, [sp, #0x14]
	mul r2, r4
	lsl r0, r0, #0x18
	add r1, r1, r2
	lsr r0, r0, #0x18
	str r1, [sp, #0x10]
	str r0, [sp, #0x30]
_0201845E:
	add r1, sp, #0x40
	ldr r0, [sp, #0x0]
	ldrb r1, [r1, #0x1]
	add r0, r0, r5
	cmp r0, r1
	bge _02018490
	ldr r1, [sp, #0x18]
	add r1, r1, r5
	cmp r1, r4
	bge _02018490
	ldrb r2, [r7, #0x15]
	lsl r0, r0, #0x18
	ldr r1, [sp, #0x30]
	lsr r0, r0, #0x18
	bl FUN_02017FFC
	ldr r1, [sp, #0x10]
	ldrb r2, [r1, r5]
	ldr r1, [sp, #0x2c]
	strb r2, [r1, r0]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r6
	blo _0201845E
_02018490:
	ldr r0, [sp, #0x28]
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	str r1, [sp, #0x28]
	ldr r0, [sp, #0x58]
	cmp r1, r0
	blo _02018430
	add sp, #0x44
	pop {r4-r7, pc}
_020184A4:
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x58]
	cmp r0, #0x0
	bls _0201853C
	add r1, sp, #0x48
	ldrb r0, [r1, #0x1c]
	str r0, [sp, #0x24]
	ldrb r0, [r1, #0x18]
	str r0, [sp, #0x20]
_020184B8:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x8]
	add r1, r1, r0
	add r0, sp, #0x40
	ldrb r0, [r0, #0x0]
	cmp r1, r0
	bge _0201853C
	ldr r2, [sp, #0x24]
	ldr r0, [sp, #0x8]
	add r0, r2, r0
	ldr r2, [sp, #0x6c]
	cmp r0, r2
	bge _0201853C
	mov r5, #0x0
	cmp r6, #0x0
	bls _0201852C
	lsl r1, r1, #0x18
	lsl r0, r0, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	str r1, [sp, #0x34]
	str r0, [sp, #0x3c]
_020184E4:
	add r1, sp, #0x40
	ldr r0, [sp, #0x0]
	ldrb r1, [r1, #0x1]
	add r0, r0, r5
	cmp r0, r1
	bge _0201852C
	ldr r1, [sp, #0x20]
	add r1, r1, r5
	str r1, [sp, #0xc]
	cmp r1, r4
	bge _0201852C
	ldrb r2, [r7, #0x15]
	lsl r0, r0, #0x18
	ldr r1, [sp, #0x34]
	lsr r0, r0, #0x18
	bl FUN_02017FFC
	str r0, [sp, #0x38]
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x3c]
	lsl r0, r0, #0x18
	ldr r3, [sp, #0x6c]
	lsr r0, r0, #0x18
	add r2, r4, #0x0
	bl FUN_02018068
	ldr r1, [sp, #0x5c]
	ldrb r2, [r1, r0]
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x38]
	strb r2, [r1, r0]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r6
	blo _020184E4
_0201852C:
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	str r1, [sp, #0x8]
	ldr r0, [sp, #0x58]
	cmp r1, r0
	blo _020184B8
_0201853C:
	add sp, #0x44
	pop {r4-r7, pc}

	thumb_func_start FUN_02018540
FUN_02018540: ; 0x02018540
	push {r4-r5, lr}
	sub sp, #0xc
	add r4, r2, #0x0
	add r2, r3, #0x0
	mov r3, #0x2c
	add r5, r1, #0x0
	mul r5, r3
	add r1, r0, r5
	ldrb r1, [r1, #0x1c]
	add r3, sp, #0x8
	cmp r1, #0x1
	beq _02018574
	ldrb r1, [r3, #0x14]
	add r0, #0x8
	add r0, r0, r5
	str r1, [sp, #0x0]
	ldrb r1, [r3, #0x18]
	str r1, [sp, #0x4]
	ldrb r1, [r3, #0x1c]
	str r1, [sp, #0x8]
	ldrb r3, [r3, #0x10]
	add r1, r4, #0x0
	bl FUN_02018590
	add sp, #0xc
	pop {r4-r5, pc}
_02018574:
	ldrb r1, [r3, #0x14]
	add r0, #0x8
	add r0, r0, r5
	str r1, [sp, #0x0]
	ldrb r1, [r3, #0x18]
	str r1, [sp, #0x4]
	lsl r1, r4, #0x18
	ldrb r3, [r3, #0x10]
	lsr r1, r1, #0x18
	bl FUN_02018640
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_02018590
FUN_02018590: ; 0x02018590
	push {r4-r7, lr}
	sub sp, #0x1c
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	ldr r4, [r0, #0x0]
	add r7, r1, #0x0
	str r0, [sp, #0x0]
	ldr r6, [sp, #0x38]
	cmp r4, #0x0
	beq _0201863A
	ldrb r0, [r0, #0x15]
	add r1, sp, #0x18
	add r1, #0x1
	add r2, sp, #0x18
	bl FUN_02017850
	add r0, sp, #0x20
	ldrb r2, [r0, #0x14]
	ldr r1, [sp, #0x8]
	add r1, r1, r2
	ldr r2, [sp, #0x8]
	str r1, [sp, #0xc]
	cmp r2, r1
	bge _0201863A
	ldrb r2, [r0, #0x10]
	ldr r0, [sp, #0x4]
	lsl r1, r6, #0xc
	add r0, r0, r2
	add r1, r1, r7
	str r0, [sp, #0x10]
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x14]
_020185D2:
	add r0, sp, #0x18
	ldrb r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	cmp r0, r1
	bhs _0201863A
	ldr r5, [sp, #0x4]
	ldr r0, [sp, #0x10]
	add r1, r5, #0x0
	cmp r1, r0
	bge _0201862A
_020185E6:
	add r0, sp, #0x18
	ldrb r0, [r0, #0x1]
	cmp r5, r0
	bhs _0201862A
	ldr r2, [sp, #0x0]
	ldr r1, [sp, #0x8]
	ldrb r2, [r2, #0x15]
	add r0, r5, #0x0
	bl FUN_02017FFC
	cmp r6, #0x11
	bne _02018604
	lsl r0, r0, #0x1
	strh r7, [r4, r0]
	b _0201861E
_02018604:
	cmp r6, #0x10
	bne _02018618
	lsl r0, r0, #0x1
	ldrh r2, [r4, r0]
	mov r1, #0xf
	lsl r1, r1, #0xc
	and r1, r2
	add r1, r7, r1
	strh r1, [r4, r0]
	b _0201861E
_02018618:
	lsl r1, r0, #0x1
	ldr r0, [sp, #0x14]
	strh r0, [r4, r1]
_0201861E:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r0, [sp, #0x10]
	cmp r5, r0
	blt _020185E6
_0201862A:
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, [sp, #0xc]
	str r1, [sp, #0x8]
	cmp r1, r0
	blt _020185D2
_0201863A:
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02018640
FUN_02018640: ; 0x02018640
	push {r4-r7, lr}
	sub sp, #0x14
	str r1, [sp, #0x0]
	add r7, r0, #0x0
	str r2, [sp, #0x4]
	ldr r0, [r7, #0x0]
	add r5, r3, #0x0
	str r0, [sp, #0xc]
	cmp r0, #0x0
	beq _020186B0
	ldrb r0, [r7, #0x15]
	add r1, sp, #0x10
	add r1, #0x1
	add r2, sp, #0x10
	bl FUN_02017850
	add r1, sp, #0x18
	ldrb r0, [r1, #0x14]
	add r0, r5, r0
	str r0, [sp, #0x8]
	cmp r5, r0
	bge _020186B0
	ldrb r1, [r1, #0x10]
	ldr r0, [sp, #0x4]
	add r6, r0, r1
_02018672:
	add r0, sp, #0x10
	ldrb r0, [r0, #0x0]
	cmp r5, r0
	bhs _020186B0
	ldr r4, [sp, #0x4]
	add r0, r4, #0x0
	cmp r0, r6
	bge _020186A4
_02018682:
	add r0, sp, #0x10
	ldrb r0, [r0, #0x1]
	cmp r4, r0
	bhs _020186A4
	ldrb r2, [r7, #0x15]
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02017FFC
	ldr r2, [sp, #0x0]
	ldr r1, [sp, #0xc]
	strb r2, [r1, r0]
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, r6
	blt _02018682
_020186A4:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r0, [sp, #0x8]
	cmp r5, r0
	blt _02018672
_020186B0:
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_020186B4
FUN_020186B4: ; 0x020186B4
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	mov r0, #0x2c
	add r7, r1, #0x0
	mul r7, r0
	str r2, [sp, #0x0]
	add r0, r5, r7
	ldr r4, [r0, #0x8]
	add r6, r3, #0x0
	cmp r4, #0x0
	beq _0201873C
	ldrb r0, [r0, #0x1d]
	add r1, sp, #0x10
	add r1, #0x1
	add r2, sp, #0x10
	bl FUN_02017850
	add r0, sp, #0x18
	ldrb r1, [r0, #0x14]
	add r1, r6, r1
	str r1, [sp, #0x4]
	cmp r6, r1
	bge _0201873C
	add r1, r5, r7
	str r1, [sp, #0xc]
	ldrb r1, [r0, #0x18]
	lsl r1, r1, #0xc
	str r1, [sp, #0x8]
	ldrb r1, [r0, #0x10]
	ldr r0, [sp, #0x0]
	add r7, r0, r1
_020186F4:
	add r0, sp, #0x10
	ldrb r0, [r0, #0x0]
	cmp r6, r0
	bhs _0201873C
	ldr r5, [sp, #0x0]
	add r0, r5, #0x0
	cmp r0, r7
	bge _02018730
_02018704:
	add r0, sp, #0x10
	ldrb r0, [r0, #0x1]
	cmp r5, r0
	bhs _02018730
	ldr r2, [sp, #0xc]
	add r0, r5, #0x0
	ldrb r2, [r2, #0x1d]
	add r1, r6, #0x0
	bl FUN_02017FFC
	lsl r0, r0, #0x1
	ldrh r2, [r4, r0]
	ldr r1, _02018740 ; =0x00000FFF
	and r2, r1
	ldr r1, [sp, #0x8]
	orr r1, r2
	strh r1, [r4, r0]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r7
	blt _02018704
_02018730:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r0, [sp, #0x4]
	cmp r6, r0
	blt _020186F4
_0201873C:
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02018740: .word 0x00000FFF

	thumb_func_start FUN_02018744
FUN_02018744: ; 0x02018744
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x2c
	mul r0, r4
	add r2, r5, r0
	ldr r1, [r2, #0x8]
	cmp r1, #0x0
	beq _02018766
	ldr r2, [r2, #0xc]
	mov r0, #0x0
	bl MIi_CpuClear16
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02017CD0
_02018766:
	pop {r3-r5, pc}

	thumb_func_start FUN_02018768
FUN_02018768: ; 0x02018768
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x2c
	mul r0, r4
	add r3, r5, r0
	ldr r1, [r3, #0x8]
	cmp r1, #0x0
	beq _0201878A
	add r0, r2, #0x0
	ldr r2, [r3, #0xc]
	bl MIi_CpuClear16
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02017CD0
_0201878A:
	pop {r3-r5, pc}

	thumb_func_start FUN_0201878C
FUN_0201878C: ; 0x0201878C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x2c
	mul r0, r4
	add r3, r5, r0
	ldr r1, [r3, #0x8]
	cmp r1, #0x0
	beq _020187AE
	add r0, r2, #0x0
	ldr r2, [r3, #0xc]
	bl MIi_CpuClear16
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201AC68
_020187AE:
	pop {r3-r5, pc}

	thumb_func_start FUN_020187B0
FUN_020187B0: ; 0x020187B0
	push {r3, lr}
	cmp r0, #0x7
	bhi _02018802
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020187C2: ; jump table (using 16-bit offset)
	.short _020187D2 - _020187C2 - 2; case 0
	.short _020187D8 - _020187C2 - 2; case 1
	.short _020187DE - _020187C2 - 2; case 2
	.short _020187E4 - _020187C2 - 2; case 3
	.short _020187EA - _020187C2 - 2; case 4
	.short _020187F0 - _020187C2 - 2; case 5
	.short _020187F6 - _020187C2 - 2; case 6
	.short _020187FC - _020187C2 - 2; case 7
_020187D2:
	bl G2_GetBG0CharPtr
	pop {r3, pc}
_020187D8:
	bl G2_GetBG1CharPtr
	pop {r3, pc}
_020187DE:
	bl G2_GetBG2CharPtr
	pop {r3, pc}
_020187E4:
	bl G2_GetBG3CharPtr
	pop {r3, pc}
_020187EA:
	bl G2S_GetBG0CharPtr
	pop {r3, pc}
_020187F0:
	bl G2S_GetBG1CharPtr
	pop {r3, pc}
_020187F6:
	bl G2S_GetBG2CharPtr
	pop {r3, pc}
_020187FC:
	bl G2S_GetBG3CharPtr
	pop {r3, pc}
_02018802:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02018808
FUN_02018808: ; 0x02018808
	push {r4-r7}
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x18
	mov r4, #0x0
	cmp r1, #0x0
	bls _02018842
	mov r5, #0xf
	add r6, r5, #0x0
_02018818:
	ldrb r7, [r0, r4]
	and r7, r6
	strb r7, [r2, #0x0]
	ldrb r7, [r2, #0x0]
	cmp r7, #0x0
	beq _02018828
	add r7, r7, r3
	strb r7, [r2, #0x0]
_02018828:
	ldrb r7, [r0, r4]
	asr r7, r7, #0x4
	and r7, r5
	strb r7, [r2, #0x1]
	ldrb r7, [r2, #0x1]
	cmp r7, #0x0
	beq _0201883A
	add r7, r7, r3
	strb r7, [r2, #0x1]
_0201883A:
	add r4, r4, #0x1
	add r2, r2, #0x2
	cmp r4, r1
	blo _02018818
_02018842:
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_02018848
FUN_02018848: ; 0x02018848
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r0, r3, #0x0
	lsl r1, r5, #0x1
	add r7, r2, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02018808
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201886C
FUN_0201886C: ; 0x0201886C
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	ldr r0, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start FUN_02018878
FUN_02018878: ; 0x02018878
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	ldrh r0, [r0, #0x20]
	bx lr
	.balign 4

	thumb_func_start FUN_02018884
FUN_02018884: ; 0x02018884
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
_02018898: ; jump table (using 16-bit offset)
	.short _020188A8 - _02018898 - 2; case 0
	.short _020188BC - _02018898 - 2; case 1
	.short _020188D0 - _02018898 - 2; case 2
	.short _02018920 - _02018898 - 2; case 3
	.short _02018970 - _02018898 - 2; case 4
	.short _02018984 - _02018898 - 2; case 5
	.short _02018998 - _02018898 - 2; case 6
	.short _020189E8 - _02018898 - 2; case 7
_020188A8:
	ldr r0, _02018A40 ; =0x04000008
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
	ldr r0, _02018A44 ; =0x0400000A
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
	ldr r0, _02018A48 ; =0x0400000C
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
	ldr r0, _02018A48 ; =0x0400000C
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
	ldr r0, _02018A48 ; =0x0400000C
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
	ldr r0, _02018A4C ; =0x0400000E
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
	ldr r0, _02018A4C ; =0x0400000E
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
	ldr r0, _02018A4C ; =0x0400000E
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
	ldr r0, _02018A50 ; =0x04001008
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
	ldr r0, _02018A54 ; =0x0400100A
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
	ldr r0, _02018A58 ; =0x0400100C
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
	ldr r0, _02018A58 ; =0x0400100C
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
	ldr r0, _02018A58 ; =0x0400100C
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
	ldr r0, _02018A5C ; =0x0400100E
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
	ldr r0, _02018A5C ; =0x0400100E
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
	ldr r0, _02018A5C ; =0x0400100E
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
	nop
_02018A40: .word 0x04000008
_02018A44: .word 0x0400000A
_02018A48: .word 0x0400000C
_02018A4C: .word 0x0400000E
_02018A50: .word 0x04001008
_02018A54: .word 0x0400100A
_02018A58: .word 0x0400100C
_02018A5C: .word 0x0400100E

	thumb_func_start FUN_02018A60
FUN_02018A60: ; 0x02018A60
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
	ldr r2, _02018C98 ; =0x0000FFFF
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
	ldr r0, _02018C9C ; =0x00003FE0
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
	ldr r0, _02018C9C ; =0x00003FE0
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
	ldr r1, _02018C9C ; =0x00003FE0
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
	ldr r0, _02018C9C ; =0x00003FE0
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
	ldr r0, _02018C9C ; =0x00003FE0
	and r0, r2
	add r5, r5, r0
	ldr r0, [sp, #0x2c]
	add r5, r5, r0
	ldr r0, [sp, #0x0]
	ldr r7, [r0, #0x0]
	mov r0, #0x3
	and r0, r6
	ldr r6, _02018C9C ; =0x00003FE0
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
	nop
_02018C98: .word 0x0000FFFF
_02018C9C: .word 0x00003FE0

	thumb_func_start FUN_02018CA0
FUN_02018CA0: ; 0x02018CA0
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
	ldr r2, _02018E80 ; =0x0000FFFF
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
	ldr r6, _02018E84 ; =0x00007FC0
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
	ldr r4, _02018E84 ; =0x00007FC0
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
	ldr r4, _02018E84 ; =0x00007FC0
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
	ldr r7, _02018E84 ; =0x00007FC0
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
	ldr r4, _02018E84 ; =0x00007FC0
	add r5, r2, #0x0
	and r4, r1
	add r4, r0, r4
	ldr r0, [sp, #0x30]
	add r7, r4, r0
	ldr r0, [sp, #0x0]
	mov r4, #0x7
	and r5, r4
	ldr r0, [r0, #0x0]
	ldr r4, _02018E84 ; =0x00007FC0
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
	.balign 4
_02018E80: .word 0x0000FFFF
_02018E84: .word 0x00007FC0

	thumb_func_start FUN_02018E88
FUN_02018E88: ; 0x02018E88
	push {r4-r7, lr}
	sub sp, #0x14
	str r1, [sp, #0x4]
	str r2, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x4]
	add r6, r0, r3
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x4]
	cmp r6, r0
	ble _02018EA4
	add r6, r0, #0x0
_02018EA4:
	add r1, sp, #0x18
	ldrh r2, [r1, #0x10]
	ldr r1, [sp, #0x8]
	add r1, r1, r2
	mov r12, r1
	ldr r1, [sp, #0x0]
	ldrh r2, [r1, #0x6]
	mov r1, r12
	cmp r1, r2
	ble _02018EBA
	mov r12, r2
_02018EBA:
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	mov lr, r0
	ldr r1, [sp, #0x8]
	mov r0, r12
	cmp r1, r0
	bge _02018F44
	add r0, r1, #0x0
	lsl r0, r0, #0x2
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x2c]
	lsl r0, r0, #0x4
	str r0, [sp, #0x10]
_02018ED8:
	ldr r1, [sp, #0x4]
	add r0, r1, #0x0
	cmp r0, r6
	bge _02018F32
	lsl r5, r0, #0x2
	ldr r2, _02018F48 ; =0x00003FE0
	ldr r0, [sp, #0xc]
	and r0, r2
	add r7, r0, #0x0
	mov r2, lr
	mul r7, r2
	ldr r0, [sp, #0xc]
	mov r2, #0x1c
	and r2, r0
_02018EF4:
	ldr r0, [sp, #0x0]
	asr r3, r1, #0x1
	ldr r4, [r0, #0x0]
	mov r0, #0x3
	and r0, r3
	ldr r3, _02018F48 ; =0x00003FE0
	add r0, r4, r0
	and r3, r5
	add r0, r0, r3
	add r0, r0, r7
	mov r3, #0x1
	tst r3, r1
	ldrb r4, [r0, r2]
	beq _02018F1C
	mov r3, #0xf
	and r3, r4
	strb r3, [r0, r2]
	ldrb r4, [r0, r2]
	ldr r3, [sp, #0x10]
	b _02018F26
_02018F1C:
	mov r3, #0xf0
	and r3, r4
	strb r3, [r0, r2]
	ldrb r4, [r0, r2]
	ldr r3, [sp, #0x2c]
_02018F26:
	orr r3, r4
	add r1, r1, #0x1
	strb r3, [r0, r2]
	add r5, r5, #0x4
	cmp r1, r6
	blt _02018EF4
_02018F32:
	ldr r0, [sp, #0xc]
	add r0, r0, #0x4
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x8]
	add r1, r0, #0x1
	mov r0, r12
	str r1, [sp, #0x8]
	cmp r1, r0
	blt _02018ED8
_02018F44:
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02018F48: .word 0x00003FE0

	thumb_func_start FUN_02018F4C
FUN_02018F4C: ; 0x02018F4C
	push {r4-r7, lr}
	sub sp, #0x14
	str r1, [sp, #0x4]
	str r2, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x4]
	add r5, r0, r3
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x4]
	cmp r5, r0
	ble _02018F68
	add r5, r0, #0x0
_02018F68:
	add r1, sp, #0x18
	ldrh r2, [r1, #0x10]
	ldr r1, [sp, #0x8]
	add r1, r1, r2
	mov lr, r1
	ldr r1, [sp, #0x0]
	ldrh r2, [r1, #0x6]
	mov r1, lr
	cmp r1, r2
	ble _02018F7E
	mov lr, r2
_02018F7E:
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x8]
	mov r0, lr
	cmp r1, r0
	bge _02018FEA
	add r0, r1, #0x0
	lsl r0, r0, #0x3
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x4]
	lsl r0, r0, #0x3
	mov r12, r0
_02018F9C:
	ldr r2, [sp, #0x4]
	add r0, r2, #0x0
	cmp r0, r5
	bge _02018FD8
	ldr r1, [sp, #0xc]
	ldr r0, _02018FF0 ; =0x00007FC0
	mov r3, r12
	and r0, r1
	add r7, r0, #0x0
	ldr r1, [sp, #0x10]
	mov r0, #0x38
	mul r7, r1
	ldr r1, [sp, #0xc]
	add r6, r1, #0x0
	and r6, r0
_02018FBA:
	ldr r0, [sp, #0x0]
	ldr r4, _02018FF0 ; =0x00007FC0
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	and r0, r2
	and r4, r3
	add r0, r1, r0
	add r0, r4, r0
	add r1, r7, r0
	ldr r0, [sp, #0x2c]
	add r2, r2, #0x1
	strb r0, [r6, r1]
	add r3, #0x8
	cmp r2, r5
	blt _02018FBA
_02018FD8:
	ldr r0, [sp, #0xc]
	add r0, #0x8
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x8]
	add r1, r0, #0x1
	mov r0, lr
	str r1, [sp, #0x8]
	cmp r1, r0
	blt _02018F9C
_02018FEA:
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02018FF0: .word 0x00007FC0

	thumb_func_start FUN_02018FF4
FUN_02018FF4: ; 0x02018FF4
	push {r4-r6, lr}
	add r5, r1, #0x0
	lsl r1, r5, #0x4
	bl AllocFromHeap
	add r6, r0, #0x0
	mov r4, #0x0
	cmp r5, #0x0
	ble _02019018
_02019006:
	lsl r0, r4, #0x4
	add r0, r6, r0
	bl FUN_0201901C
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r5
	blt _02019006
_02019018:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0201901C
FUN_0201901C: ; 0x0201901C
	mov r3, #0x0
	str r3, [r0, #0x0]
	mov r1, #0xff
	strb r1, [r0, #0x4]
	strb r3, [r0, #0x5]
	strb r3, [r0, #0x6]
	strb r3, [r0, #0x7]
	strb r3, [r0, #0x8]
	strb r3, [r0, #0x9]
	ldrh r2, [r0, #0xa]
	ldr r1, _02019044 ; =0xFFFF8000
	and r2, r1
	strh r2, [r0, #0xa]
	str r3, [r0, #0xc]
	ldrh r2, [r0, #0xa]
	sub r1, r1, #0x1
	and r1, r2
	strh r1, [r0, #0xa]
	bx lr
	nop
_02019044: .word 0xFFFF8000

	thumb_func_start FUN_02019048
FUN_02019048: ; 0x02019048
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0201905A
	ldrb r1, [r0, #0x4]
	cmp r1, #0xff
	beq _0201905A
	ldr r0, [r0, #0xc]
	cmp r0, #0x0
	bne _0201905E
_0201905A:
	mov r0, #0x0
	bx lr
_0201905E:
	mov r0, #0x1
	bx lr
	.balign 4

	thumb_func_start FUN_02019064
FUN_02019064: ; 0x02019064
	push {r3-r7, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	mov r0, #0x2c
	add r7, r6, #0x0
	mul r7, r0
	add r4, r1, #0x0
	str r3, [sp, #0x0]
	add r1, r5, r7
	ldr r0, [r1, #0x8]
	cmp r0, #0x0
	beq _020190E0
	add r3, sp, #0x8
	ldrb r2, [r1, #0x1f]
	ldrb r1, [r3, #0x14]
	ldrb r3, [r3, #0x18]
	ldr r0, [r5, #0x0]
	mul r3, r1
	add r1, r2, #0x0
	mul r1, r3
	bl AllocFromHeap
	add r1, r0, #0x0
	beq _020190E0
	str r5, [r4, #0x0]
	strb r6, [r4, #0x4]
	ldr r0, [sp, #0x0]
	add r3, sp, #0x8
	strb r0, [r4, #0x5]
	ldrb r0, [r3, #0x10]
	ldr r2, _020190E4 ; =0xFFFF8000
	strb r0, [r4, #0x6]
	ldrb r0, [r3, #0x14]
	strb r0, [r4, #0x7]
	ldrb r0, [r3, #0x18]
	strb r0, [r4, #0x8]
	ldrb r0, [r3, #0x1c]
	strb r0, [r4, #0x9]
	ldrh r0, [r4, #0xa]
	ldrh r3, [r3, #0x20]
	and r0, r2
	lsr r2, r2, #0x11
	and r2, r3
	orr r0, r2
	strh r0, [r4, #0xa]
	str r1, [r4, #0xc]
	add r0, r5, r7
	ldrb r0, [r0, #0x1e]
	cmp r0, #0x0
	bne _020190CC
	mov r2, #0x0
	b _020190CE
_020190CC:
	mov r2, #0x1
_020190CE:
	ldrh r1, [r4, #0xa]
	ldr r0, _020190E8 ; =0xFFFF7FFF
	and r1, r0
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x10
	orr r0, r1
	strh r0, [r4, #0xa]
_020190E0:
	pop {r3-r7, pc}
	nop
_020190E4: .word 0xFFFF8000
_020190E8: .word 0xFFFF7FFF

	thumb_func_start FUN_020190EC
FUN_020190EC: ; 0x020190EC
	push {r3-r7, lr}
	sub sp, #0x8
	str r3, [sp, #0x0]
	add r5, r0, #0x0
	ldr r0, [sp, #0x24]
	add r6, r2, #0x0
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x0]
	add r4, r1, #0x0
	mul r0, r6
	lsl r0, r0, #0x5
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x4]
	bl AllocFromHeap
	ldr r1, [sp, #0x24]
	add r7, r0, #0x0
	lsl r2, r1, #0x4
	orr r1, r2
	lsl r1, r1, #0x18
	ldr r2, [sp, #0x4]
	lsr r1, r1, #0x18
	bl memset
	cmp r7, #0x0
	beq _02019148
	str r5, [r4, #0x0]
	strb r6, [r4, #0x7]
	ldr r0, [sp, #0x0]
	strb r0, [r4, #0x8]
	ldrh r1, [r4, #0xa]
	ldr r0, _0201914C ; =0xFFFF8000
	add r3, r1, #0x0
	add r1, sp, #0x10
	ldrh r2, [r1, #0x10]
	lsr r1, r0, #0x11
	and r3, r0
	and r1, r2
	orr r1, r3
	strh r1, [r4, #0xa]
	str r7, [r4, #0xc]
	ldrh r1, [r4, #0xa]
	sub r0, r0, #0x1
	and r0, r1
	strh r0, [r4, #0xa]
_02019148:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0201914C: .word 0xFFFF8000

	thumb_func_start FUN_02019150
FUN_02019150: ; 0x02019150
	push {lr}
	sub sp, #0x14
	add r3, r2, #0x0
	ldrb r2, [r3, #0x2]
	str r2, [sp, #0x0]
	ldrb r2, [r3, #0x3]
	str r2, [sp, #0x4]
	ldrb r2, [r3, #0x4]
	str r2, [sp, #0x8]
	ldrb r2, [r3, #0x5]
	str r2, [sp, #0xc]
	ldrh r2, [r3, #0x6]
	str r2, [sp, #0x10]
	ldrb r2, [r3, #0x0]
	ldrb r3, [r3, #0x1]
	bl FUN_02019064
	add sp, #0x14
	pop {pc}
	.balign 4

	thumb_func_start FUN_02019178
FUN_02019178: ; 0x02019178
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FreeToHeap
	mov r2, #0x0
	str r2, [r4, #0x0]
	mov r0, #0xff
	strb r0, [r4, #0x4]
	strb r2, [r4, #0x5]
	strb r2, [r4, #0x6]
	strb r2, [r4, #0x7]
	strb r2, [r4, #0x8]
	strb r2, [r4, #0x9]
	ldrh r1, [r4, #0xa]
	ldr r0, _020191A0 ; =0xFFFF8000
	and r0, r1
	strh r0, [r4, #0xa]
	str r2, [r4, #0xc]
	pop {r4, pc}
	.balign 4
_020191A0: .word 0xFFFF8000

	thumb_func_start FUN_020191A4
FUN_020191A4: ; 0x020191A4
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	mov r4, #0x0
	cmp r6, #0x0
	ble _020191C8
_020191B0:
	lsl r0, r4, #0x4
	add r0, r5, r0
	ldr r0, [r0, #0xc]
	cmp r0, #0x0
	beq _020191BE
	bl FreeToHeap
_020191BE:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r6
	blt _020191B0
_020191C8:
	add r0, r5, #0x0
	bl FreeToHeap
	pop {r4-r6, pc}

	thumb_func_start CopyWindowToVram
CopyWindowToVram: ; 0x020191D0
	push {r4, lr}
	add r4, r0, #0x0
	bne _020191DA
	bl ErrorHandling
_020191DA:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020191E4
	bl ErrorHandling
_020191E4:
	ldrb r0, [r4, #0x4]
	cmp r0, #0x8
	blo _020191EE
	bl ErrorHandling
_020191EE:
	ldrb r1, [r4, #0x4]
	mov r0, #0x2c
	ldr r2, [r4, #0x0]
	mul r0, r1
	add r0, r2, r0
	ldrb r0, [r0, #0x1c]
	cmp r0, #0x3
	blo _02019202
	bl ErrorHandling
_02019202:
	ldrb r2, [r4, #0x4]
	mov r1, #0x2c
	ldr r3, [r4, #0x0]
	mul r1, r2
	add r1, r3, r1
	ldrb r1, [r1, #0x1c]
	add r0, r4, #0x0
	lsl r2, r1, #0x2
	ldr r1, _0201921C ; =UNK_020EDB68
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_0201921C: .word UNK_020EDB68

	thumb_func_start FUN_02019220
FUN_02019220: ; 0x02019220
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201922A
	bl ErrorHandling
_0201922A:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02019234
	bl ErrorHandling
_02019234:
	ldrb r0, [r4, #0x4]
	cmp r0, #0x8
	blo _0201923E
	bl ErrorHandling
_0201923E:
	ldrb r1, [r4, #0x4]
	mov r0, #0x2c
	ldr r2, [r4, #0x0]
	mul r0, r1
	add r0, r2, r0
	ldrb r0, [r0, #0x1c]
	cmp r0, #0x3
	blo _02019252
	bl ErrorHandling
_02019252:
	ldrb r2, [r4, #0x4]
	mov r1, #0x2c
	ldr r3, [r4, #0x0]
	mul r1, r2
	add r1, r3, r1
	ldrb r1, [r1, #0x1c]
	add r0, r4, #0x0
	lsl r2, r1, #0x2
	ldr r1, _0201926C ; =UNK_020EDB5C
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_0201926C: .word UNK_020EDB5C

	thumb_func_start FUN_02019270
FUN_02019270: ; 0x02019270
	push {r3, lr}
	ldrb r2, [r0, #0x4]
	mov r1, #0x2c
	ldr r3, [r0, #0x0]
	mul r1, r2
	add r1, r3, r1
	ldrb r1, [r1, #0x1c]
	lsl r2, r1, #0x2
	ldr r1, _02019288 ; =UNK_020EDB38
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.balign 4
_02019288: .word UNK_020EDB38

	thumb_func_start FUN_0201928C
FUN_0201928C: ; 0x0201928C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrb r6, [r5, #0x7]
	ldrb r4, [r5, #0x8]
	strb r1, [r5, #0x7]
	strb r2, [r5, #0x8]
	ldrb r3, [r5, #0x4]
	mov r2, #0x2c
	ldr r1, [r5, #0x0]
	mul r2, r3
	add r1, r1, r2
	ldrb r1, [r1, #0x1c]
	lsl r2, r1, #0x2
	ldr r1, _020192B4 ; =UNK_020EDB38
	ldr r1, [r1, r2]
	blx r1
	strb r6, [r5, #0x7]
	strb r4, [r5, #0x8]
	pop {r4-r6, pc}
	nop
_020192B4: .word UNK_020EDB38

	thumb_func_start FUN_020192B8
FUN_020192B8: ; 0x020192B8
	push {r3, lr}
	ldrb r2, [r0, #0x4]
	mov r1, #0x2c
	ldr r3, [r0, #0x0]
	mul r1, r2
	add r1, r3, r1
	ldrb r1, [r1, #0x1c]
	lsl r2, r1, #0x2
	ldr r1, _020192D0 ; =UNK_020EDB74
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.balign 4
_020192D0: .word UNK_020EDB74

	thumb_func_start FUN_020192D4
FUN_020192D4: ; 0x020192D4
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldrb r1, [r5, #0x4]
	mov r0, #0x2c
	ldr r2, [r5, #0x0]
	mul r0, r1
	add r0, r2, r0
	ldr r0, [r0, #0x8]
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _02019354
	ldrh r0, [r5, #0xa]
	ldrb r1, [r5, #0x5]
	lsl r0, r0, #0x11
	lsr r3, r0, #0x11
	ldrb r0, [r5, #0x7]
	add r7, r1, r0
	ldrb r0, [r5, #0x6]
	ldrb r1, [r5, #0x8]
	mov r12, r0
	add r0, r0, r1
	mov r1, r12
	mov lr, r0
	cmp r1, r0
	bhs _02019354
_02019308:
	ldrb r2, [r5, #0x5]
	cmp r2, r7
	bhs _02019348
	mov r0, r12
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x16
	lsl r1, r0, #0x1
	ldr r0, [sp, #0x4]
	add r0, r0, r1
	mov r1, r12
	str r0, [sp, #0x0]
	mov r0, #0x20
	add r6, r1, #0x0
	and r6, r0
_02019324:
	ldrb r0, [r5, #0x9]
	mov r4, #0x20
	add r1, r3, #0x0
	lsl r0, r0, #0xc
	and r4, r2
	orr r1, r0
	mov r0, #0x1f
	add r4, r6, r4
	and r0, r2
	lsl r4, r4, #0x5
	add r0, r0, r4
	lsl r4, r0, #0x1
	ldr r0, [sp, #0x0]
	add r2, r2, #0x1
	strh r1, [r0, r4]
	add r3, r3, #0x1
	cmp r2, r7
	blo _02019324
_02019348:
	mov r0, r12
	add r1, r0, #0x1
	mov r0, lr
	mov r12, r1
	cmp r1, r0
	blo _02019308
_02019354:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02019358
FUN_02019358: ; 0x02019358
	push {r4-r7}
	ldrb r3, [r0, #0x4]
	mov r1, #0x2c
	add r2, r3, #0x0
	mul r2, r1
	ldr r1, [r0, #0x0]
	add r1, r1, r2
	ldr r3, [r1, #0x8]
	cmp r3, #0x0
	beq _020193AC
	ldrb r2, [r1, #0x1d]
	ldr r1, _020193B0 ; =UNK_020EDB30
	ldrb r6, [r1, r2]
	ldrb r1, [r0, #0x6]
	add r2, r1, #0x0
	mul r2, r6
	add r2, r3, r2
	ldrb r1, [r0, #0x5]
	mov r3, #0x0
	add r4, r2, r1
	ldrh r1, [r0, #0xa]
	lsl r1, r1, #0x11
	lsr r5, r1, #0x11
	ldrb r1, [r0, #0x8]
	cmp r1, #0x0
	ble _020193AC
	add r1, r3, #0x0
_0201938E:
	ldrb r7, [r0, #0x7]
	add r2, r1, #0x0
	cmp r7, #0x0
	ble _020193A2
_02019396:
	strb r5, [r4, r2]
	ldrb r7, [r0, #0x7]
	add r2, r2, #0x1
	add r5, r5, #0x1
	cmp r2, r7
	blt _02019396
_020193A2:
	ldrb r2, [r0, #0x8]
	add r3, r3, #0x1
	add r4, r4, r6
	cmp r3, r2
	blt _0201938E
_020193AC:
	pop {r4-r7}
	bx lr
	.balign 4
_020193B0: .word UNK_020EDB30

	thumb_func_start FUN_020193B4
FUN_020193B4: ; 0x020193B4
	push {r4-r7, lr}
	sub sp, #0xc
	ldrb r2, [r0, #0x4]
	str r0, [sp, #0x0]
	mov r0, #0x2c
	add r1, r2, #0x0
	mul r1, r0
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r1, r0, r1
	ldr r0, [r1, #0x8]
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0201943C
	ldrb r1, [r1, #0x1d]
	ldr r0, _02019440 ; =UNK_020EDB30
	ldrb r0, [r0, r1]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x0]
	ldrb r1, [r0, #0x5]
	ldrb r0, [r0, #0x7]
	add r2, r1, r0
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, #0x6]
	mov r12, r0
	ldr r0, [sp, #0x0]
	ldrb r1, [r0, #0x8]
	mov r0, r12
	add r0, r0, r1
	mov r1, r12
	mov lr, r0
	cmp r1, r0
	bhs _0201943C
	mov r6, #0x0
	mov r7, #0x20
_020193FA:
	ldr r0, [sp, #0x0]
	ldrb r1, [r0, #0x5]
	cmp r1, r2
	bhs _02019430
	mov r3, r12
	mov r0, #0x1f
	and r3, r0
	ldr r0, [sp, #0x8]
	mul r0, r3
	lsl r3, r0, #0x1
	ldr r0, [sp, #0x4]
	add r5, r0, r3
	mov r3, r12
	mov r0, #0x20
	and r3, r0
_02019418:
	add r4, r1, #0x0
	and r4, r7
	mov r0, #0x1f
	add r4, r3, r4
	and r0, r1
	lsl r4, r4, #0x5
	add r0, r0, r4
	lsl r0, r0, #0x1
	add r1, r1, #0x1
	strh r6, [r5, r0]
	cmp r1, r2
	blo _02019418
_02019430:
	mov r0, r12
	add r1, r0, #0x1
	mov r0, lr
	mov r12, r1
	cmp r1, r0
	blo _020193FA
_0201943C:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02019440: .word UNK_020EDB30

	thumb_func_start FUN_02019444
FUN_02019444: ; 0x02019444
	push {r4-r7}
	ldrb r3, [r0, #0x4]
	mov r1, #0x2c
	add r2, r3, #0x0
	mul r2, r1
	ldr r1, [r0, #0x0]
	add r1, r1, r2
	ldr r3, [r1, #0x8]
	cmp r3, #0x0
	beq _02019492
	ldrb r2, [r1, #0x1d]
	ldr r1, _02019498 ; =UNK_020EDB30
	mov r4, #0x0
	ldrb r6, [r1, r2]
	ldrb r1, [r0, #0x6]
	add r2, r1, #0x0
	mul r2, r6
	ldrb r1, [r0, #0x5]
	add r2, r3, r2
	add r5, r2, r1
	ldrb r1, [r0, #0x8]
	cmp r1, #0x0
	ble _02019492
	add r1, r4, #0x0
	add r2, r4, #0x0
_02019476:
	ldrb r7, [r0, #0x7]
	add r3, r2, #0x0
	cmp r7, #0x0
	ble _02019488
_0201947E:
	strb r1, [r5, r3]
	ldrb r7, [r0, #0x7]
	add r3, r3, #0x1
	cmp r3, r7
	blt _0201947E
_02019488:
	ldrb r3, [r0, #0x8]
	add r4, r4, #0x1
	add r5, r5, r6
	cmp r4, r3
	blt _02019476
_02019492:
	pop {r4-r7}
	bx lr
	nop
_02019498: .word UNK_020EDB30

	thumb_func_start FUN_0201949C
FUN_0201949C: ; 0x0201949C
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl FUN_020192D4
	add r0, r4, #0x0
	bl FUN_02019548
	ldrb r1, [r4, #0x4]
	mov r0, #0x2c
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [r4, #0x0]
	add r3, r0, r2
	ldr r2, [r3, #0x10]
	str r2, [sp, #0x0]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	bl FUN_02017CE8
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_020194C8
FUN_020194C8: ; 0x020194C8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020192D4
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0201AC68
	add r0, r4, #0x0
	bl FUN_02019548
	pop {r4, pc}

	thumb_func_start FUN_020194E0
FUN_020194E0: ; 0x020194E0
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02019358
	ldrb r1, [r4, #0x4]
	mov r0, #0x2c
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [r4, #0x0]
	add r3, r0, r2
	ldr r2, [r3, #0x10]
	str r2, [sp, #0x0]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	bl FUN_02017CE8
	ldrh r0, [r4, #0xa]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x11
	str r0, [sp, #0x0]
	ldrb r5, [r4, #0x7]
	ldrb r3, [r4, #0x8]
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	mul r3, r5
	ldr r2, [r4, #0xc]
	lsl r3, r3, #0x6
	bl FUN_02017E14
	pop {r3-r5, pc}

	thumb_func_start FUN_0201951C
FUN_0201951C: ; 0x0201951C
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02019358
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0201AC68
	ldrh r0, [r4, #0xa]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x11
	str r0, [sp, #0x0]
	ldrb r5, [r4, #0x7]
	ldrb r3, [r4, #0x8]
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	mul r3, r5
	ldr r2, [r4, #0xc]
	lsl r3, r3, #0x6
	bl FUN_02017E14
	pop {r3-r5, pc}

	thumb_func_start FUN_02019548
FUN_02019548: ; 0x02019548
	push {r3-r5, lr}
	add r3, r0, #0x0
	ldrh r2, [r3, #0xa]
	ldrb r1, [r3, #0x4]
	mov r4, #0x2c
	lsl r2, r2, #0x11
	ldr r0, [r3, #0x0]
	lsr r2, r2, #0x11
	str r2, [sp, #0x0]
	mul r4, r1
	add r4, r0, r4
	ldr r2, [r3, #0xc]
	ldrb r5, [r3, #0x7]
	ldrb r3, [r3, #0x8]
	ldrb r4, [r4, #0x1f]
	mul r3, r5
	mul r3, r4
	bl FUN_02017E14
	pop {r3-r5, pc}

	thumb_func_start FUN_02019570
FUN_02019570: ; 0x02019570
	push {r3, lr}
	ldrb r2, [r0, #0x4]
	mov r1, #0x2c
	ldr r3, [r0, #0x0]
	mul r1, r2
	add r1, r3, r1
	ldrb r1, [r1, #0x1c]
	lsl r2, r1, #0x2
	ldr r1, _02019588 ; =UNK_020EDB50
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.balign 4
_02019588: .word UNK_020EDB50

	thumb_func_start FUN_0201958C
FUN_0201958C: ; 0x0201958C
	push {r3, lr}
	ldrb r2, [r0, #0x4]
	mov r1, #0x2c
	ldr r3, [r0, #0x0]
	mul r1, r2
	add r1, r3, r1
	ldrb r1, [r1, #0x1c]
	lsl r2, r1, #0x2
	ldr r1, _020195A4 ; =UNK_020EDB44
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.balign 4
_020195A4: .word UNK_020EDB44

	thumb_func_start FUN_020195A8
FUN_020195A8: ; 0x020195A8
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl FUN_020193B4
	ldrb r1, [r4, #0x4]
	mov r0, #0x2c
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [r4, #0x0]
	add r3, r0, r2
	ldr r2, [r3, #0x10]
	str r2, [sp, #0x0]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	bl FUN_02017CE8
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_020195D0
FUN_020195D0: ; 0x020195D0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020193B4
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0201AC68
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020195E4
FUN_020195E4: ; 0x020195E4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl FUN_02019444
	ldrb r1, [r4, #0x4]
	mov r0, #0x2c
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [r4, #0x0]
	add r3, r0, r2
	ldr r2, [r3, #0x10]
	str r2, [sp, #0x0]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	bl FUN_02017CE8
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201960C
FUN_0201960C: ; 0x0201960C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02019444
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0201AC68
	pop {r4, pc}
	.balign 4

	thumb_func_start FillWindowPixelBuffer
FillWindowPixelBuffer: ; 0x02019620
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldrb r2, [r4, #0x4]
	mov r0, #0x2c
	ldr r3, [r4, #0x0]
	mul r0, r2
	add r0, r3, r0
	ldrb r2, [r0, #0x1f]
	cmp r2, #0x20
	bne _0201963C
	lsl r0, r1, #0x4
	orr r0, r1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
_0201963C:
	lsl r3, r1, #0x18
	lsl r0, r1, #0x10
	orr r0, r3
	lsl r5, r1, #0x8
	orr r0, r5
	orr r0, r1
	ldr r1, [r4, #0xc]
	ldrb r3, [r4, #0x8]
	ldrb r4, [r4, #0x7]
	mul r2, r4
	mul r2, r3
	bl MIi_CpuClearFast
	pop {r3-r5, pc}

	thumb_func_start FUN_02019658
FUN_02019658: ; 0x02019658
	push {r4-r5, lr}
	sub sp, #0x1c
	add r4, sp, #0x18
	ldrh r5, [r4, #0x10]
	str r5, [sp, #0x0]
	ldrh r5, [r4, #0x14]
	str r5, [sp, #0x4]
	ldrh r5, [r4, #0x18]
	str r5, [sp, #0x8]
	ldrh r5, [r4, #0x1c]
	str r5, [sp, #0xc]
	ldrh r5, [r4, #0x20]
	str r5, [sp, #0x10]
	ldrh r4, [r4, #0x24]
	str r4, [sp, #0x14]
	mov r4, #0x0
	str r4, [sp, #0x18]
	bl FUN_02019684
	add sp, #0x1c
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_02019684
FUN_02019684: ; 0x02019684
	push {r4-r5, lr}
	sub sp, #0x24
	str r1, [sp, #0x1c]
	add r4, sp, #0x20
	ldrh r5, [r4, #0x10]
	add r1, sp, #0x14
	strh r5, [r1, #0xc]
	ldrh r5, [r4, #0x14]
	strh r5, [r1, #0xe]
	ldr r5, [r0, #0xc]
	str r5, [sp, #0x14]
	ldrb r5, [r0, #0x7]
	lsl r5, r5, #0x3
	strh r5, [r1, #0x4]
	ldrb r5, [r0, #0x8]
	lsl r5, r5, #0x3
	strh r5, [r1, #0x6]
	ldrb r5, [r0, #0x4]
	ldr r1, [r0, #0x0]
	mov r0, #0x2c
	mul r0, r5
	add r0, r1, r0
	ldrb r0, [r0, #0x1e]
	add r1, sp, #0x14
	cmp r0, #0x0
	ldrh r0, [r4, #0x18]
	bne _020196D6
	str r0, [sp, #0x0]
	ldrh r0, [r4, #0x1c]
	str r0, [sp, #0x4]
	ldrh r0, [r4, #0x20]
	str r0, [sp, #0x8]
	ldrh r0, [r4, #0x24]
	str r0, [sp, #0xc]
	ldrh r0, [r4, #0x28]
	str r0, [sp, #0x10]
	add r0, sp, #0x1c
	bl FUN_02018A60
	add sp, #0x24
	pop {r4-r5, pc}
_020196D6:
	str r0, [sp, #0x0]
	ldrh r0, [r4, #0x1c]
	str r0, [sp, #0x4]
	ldrh r0, [r4, #0x20]
	str r0, [sp, #0x8]
	ldrh r0, [r4, #0x24]
	str r0, [sp, #0xc]
	ldrh r0, [r4, #0x28]
	str r0, [sp, #0x10]
	add r0, sp, #0x1c
	bl FUN_02018CA0
	add sp, #0x24
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_020196F4
FUN_020196F4: ; 0x020196F4
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r1, #0x0
	ldr r1, [r0, #0xc]
	add r4, r2, #0x0
	str r1, [sp, #0x8]
	ldrb r1, [r0, #0x7]
	add r2, r3, #0x0
	lsl r3, r1, #0x3
	add r1, sp, #0x8
	strh r3, [r1, #0x4]
	ldrb r3, [r0, #0x8]
	lsl r3, r3, #0x3
	strh r3, [r1, #0x6]
	ldrb r3, [r0, #0x4]
	ldr r1, [r0, #0x0]
	mov r0, #0x2c
	mul r0, r3
	add r0, r1, r0
	ldrb r0, [r0, #0x1e]
	add r3, sp, #0x10
	cmp r0, #0x0
	bne _02019736
	ldrh r0, [r3, #0x14]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldrh r3, [r3, #0x10]
	add r0, sp, #0x8
	bl FUN_02018E88
	add sp, #0x10
	pop {r3-r5, pc}
_02019736:
	ldrh r0, [r3, #0x14]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldrh r3, [r3, #0x10]
	add r0, sp, #0x8
	bl FUN_02018F4C
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201974C
FUN_0201974C: ; 0x0201974C
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
_020197CC: ; jump table (using 16-bit offset)
	.short _020197D4 - _020197CC - 2; case 0
	.short _020198D6 - _020197CC - 2; case 1
	.short _02019AE6 - _020197CC - 2; case 2
	.short _02019D06 - _020197CC - 2; case 3
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
	ldr r0, _02019B68 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0x68]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
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
	ldr r5, _02019B68 ; =0x00003FE0
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
	ldr r0, _02019B68 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x264]
	str r6, [sp, #0x7c]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
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
	ldr r5, _02019B68 ; =0x00003FE0
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
	ldr r0, _02019B68 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0x90]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
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
	ldr r5, _02019B68 ; =0x00003FE0
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
	ldr r0, _02019B68 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x244]
	str r6, [sp, #0xa4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
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
	ldr r5, _02019B68 ; =0x00003FE0
	b _02019B6C
	nop
_02019B68: .word 0x00003FE0
_02019B6C:
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
	ldr r0, _02019F88 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0xb4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
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
	ldr r5, _02019F88 ; =0x00003FE0
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
	ldr r0, _02019F88 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x228]
	str r6, [sp, #0xc4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
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
	ldr r5, _02019F88 ; =0x00003FE0
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
	ldr r0, _02019F88 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x214]
	str r6, [sp, #0xd0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
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
	ldr r5, _02019F88 ; =0x00003FE0
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
	ldr r0, _02019F88 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x204]
	str r6, [sp, #0xe0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
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
	ldr r5, _02019F88 ; =0x00003FE0
	b _02019F8C
	nop
_02019F88: .word 0x00003FE0
_02019F8C:
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
	ldr r0, _0201A3A8 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0xf0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _0201A3A8 ; =0x00003FE0
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
	ldr r5, _0201A3A8 ; =0x00003FE0
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

	thumb_func_start FUN_0201A12C
FUN_0201A12C: ; 0x0201A12C
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
_0201A150: ; jump table (using 16-bit offset)
	.short _0201A158 - _0201A150 - 2; case 0
	.short _0201A220 - _0201A150 - 2; case 1
	.short _0201A3CA - _0201A150 - 2; case 2
	.short _0201A56E - _0201A150 - 2; case 3
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
	ldr r0, _0201A3AC ; =0x00007FC0
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
	ldr r0, _0201A3AC ; =0x00007FC0
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
	ldr r0, _0201A3AC ; =0x00007FC0
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
	ldr r0, _0201A3AC ; =0x00007FC0
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
	ldr r0, _0201A3AC ; =0x00007FC0
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
	ldr r0, _0201A3AC ; =0x00007FC0
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
	ldr r0, _0201A3AC ; =0x00007FC0
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
	ldr r0, _0201A3AC ; =0x00007FC0
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
	ldr r0, _0201A3AC ; =0x00007FC0
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
	nop
_0201A3A8: .word 0x00003FE0
_0201A3AC: .word 0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
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
	ldr r0, _0201A748 ; =0x00007FC0
	b _0201A74C
	nop
_0201A748: .word 0x00007FC0
_0201A74C:
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
	ldr r0, _0201A8C4 ; =0x00007FC0
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
	ldr r0, _0201A8C4 ; =0x00007FC0
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
	ldr r0, _0201A8C4 ; =0x00007FC0
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
	ldr r0, _0201A8C4 ; =0x00007FC0
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
	ldr r0, _0201A8C4 ; =0x00007FC0
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

	thumb_func_start FUN_0201A8BC
FUN_0201A8BC: ; 0x0201A8BC
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
	nop
_0201A8C4: .word 0x00007FC0

	thumb_func_start FUN_0201A8C8
FUN_0201A8C8: ; 0x0201A8C8
	push {r4-r6, lr}
	ldrb r6, [r0, #0x4]
	mov r5, #0x2c
	ldr r4, [r0, #0x0]
	mul r5, r6
	add r4, r4, r5
	ldrb r4, [r4, #0x1e]
	cmp r4, #0x0
	bne _0201A8E0
	bl FUN_0201A8E8
	pop {r4-r6, pc}
_0201A8E0:
	bl FUN_0201A9D4
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0201A8E8
FUN_0201A8E8: ; 0x0201A8E8
	push {r3-r7, lr}
	sub sp, #0x10
	add r6, r3, #0x0
	add r4, r0, #0x0
	add r0, r1, #0x0
	lsl r3, r6, #0x18
	lsl r1, r6, #0x10
	str r2, [sp, #0x0]
	orr r1, r3
	lsl r5, r6, #0x8
	orr r1, r5
	orr r1, r6
	str r1, [sp, #0x4]
	ldrb r1, [r4, #0x7]
	ldrb r3, [r4, #0x8]
	ldr r2, [r4, #0xc]
	str r1, [sp, #0x8]
	mul r1, r3
	lsl r1, r1, #0x5
	str r1, [sp, #0xc]
	cmp r0, #0x3
	bhi _0201A9CE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0201A920: ; jump table (using 16-bit offset)
	.short _0201A928 - _0201A920 - 2; case 0
	.short _0201A976 - _0201A920 - 2; case 1
	.short _0201A9CE - _0201A920 - 2; case 2
	.short _0201A9CE - _0201A920 - 2; case 3
_0201A928:
	add r0, r1, #0x0
	mov r7, #0x0
	cmp r0, #0x0
	ble _0201A9CE
	mov r0, #0x7
	mov lr, r0
_0201A934:
	ldr r3, [sp, #0x0]
	mov r4, #0x0
	add r5, r7, #0x0
_0201A93A:
	mov r0, #0x7
	add r6, r3, #0x0
	and r6, r0
	add r1, r3, #0x0
	mov r0, lr
	bic r1, r0
	ldr r0, [sp, #0x8]
	mul r1, r0
	add r0, r6, #0x0
	orr r0, r1
	lsl r0, r0, #0x2
	add r1, r7, r0
	ldr r0, [sp, #0xc]
	cmp r1, r0
	bge _0201A95C
	ldr r0, [r2, r1]
	b _0201A95E
_0201A95C:
	ldr r0, [sp, #0x4]
_0201A95E:
	add r4, r4, #0x1
	str r0, [r2, r5]
	add r3, r3, #0x1
	add r5, r5, #0x4
	cmp r4, #0x8
	blt _0201A93A
	ldr r0, [sp, #0xc]
	add r7, #0x20
	cmp r7, r0
	blt _0201A934
	add sp, #0x10
	pop {r3-r7, pc}
_0201A976:
	add r0, r1, #0x0
	sub r0, r0, #0x4
	add r2, r2, r0
	add r0, r1, #0x0
	mov r7, #0x0
	cmp r0, #0x0
	ble _0201A9CE
	mov r0, #0x7
	mov r12, r0
_0201A988:
	ldr r4, [sp, #0x0]
	mov r5, #0x0
	add r3, r7, #0x0
_0201A98E:
	mov r0, #0x7
	add r6, r4, #0x0
	and r6, r0
	add r1, r4, #0x0
	mov r0, r12
	bic r1, r0
	ldr r0, [sp, #0x8]
	mul r1, r0
	add r0, r6, #0x0
	orr r0, r1
	lsl r0, r0, #0x2
	add r1, r7, r0
	ldr r0, [sp, #0xc]
	cmp r1, r0
	bge _0201A9B6
	sub r0, r2, r1
	ldr r1, [r0, #0x0]
	sub r0, r2, r3
	str r1, [r0, #0x0]
	b _0201A9BC
_0201A9B6:
	ldr r0, [sp, #0x4]
	sub r1, r2, r3
	str r0, [r1, #0x0]
_0201A9BC:
	add r5, r5, #0x1
	add r4, r4, #0x1
	add r3, r3, #0x4
	cmp r5, #0x8
	blt _0201A98E
	ldr r0, [sp, #0xc]
	add r7, #0x20
	cmp r7, r0
	blt _0201A988
_0201A9CE:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201A9D4
FUN_0201A9D4: ; 0x0201A9D4
	push {r3-r7, lr}
	sub sp, #0x20
	add r6, r3, #0x0
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	lsl r2, r6, #0x18
	lsl r0, r6, #0x10
	orr r0, r2
	ldrb r2, [r4, #0x7]
	ldr r3, [r4, #0xc]
	lsl r5, r6, #0x8
	orr r0, r5
	ldrb r4, [r4, #0x8]
	str r2, [sp, #0x10]
	orr r0, r6
	mul r2, r4
	lsl r2, r2, #0x6
	str r2, [sp, #0x1c]
	cmp r1, #0x3
	bls _0201A9FE
	b _0201AB04
_0201A9FE:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0201AA0A: ; jump table (using 16-bit offset)
	.short _0201AA12 - _0201AA0A - 2; case 0
	.short _0201AA80 - _0201AA0A - 2; case 1
	.short _0201AB04 - _0201AA0A - 2; case 2
	.short _0201AB04 - _0201AA0A - 2; case 3
_0201AA12:
	mov r1, #0x0
	str r1, [sp, #0xc]
	add r1, r2, #0x0
	cmp r1, #0x0
	ble _0201AB04
	add r1, r1, #0x4
	str r1, [sp, #0x14]
	mov r1, #0x7
	mov lr, r1
_0201AA24:
	ldr r4, [sp, #0x0]
	ldr r5, [sp, #0xc]
	mov r7, #0x0
_0201AA2A:
	mov r1, #0x7
	add r6, r4, #0x0
	and r6, r1
	add r2, r4, #0x0
	mov r1, lr
	bic r2, r1
	ldr r1, [sp, #0x10]
	mul r2, r1
	add r1, r6, #0x0
	orr r1, r2
	lsl r2, r1, #0x3
	ldr r1, [sp, #0xc]
	add r1, r1, r2
	ldr r2, [sp, #0x1c]
	cmp r1, r2
	bge _0201AA50
	ldr r2, [r3, r1]
	str r2, [r3, r5]
	b _0201AA52
_0201AA50:
	str r0, [r3, r5]
_0201AA52:
	add r2, r1, #0x4
	ldr r1, [sp, #0x14]
	cmp r2, r1
	bge _0201AA62
	ldr r2, [r3, r2]
	add r1, r5, #0x4
	str r2, [r3, r1]
	b _0201AA66
_0201AA62:
	add r1, r5, #0x4
	str r0, [r3, r1]
_0201AA66:
	add r7, r7, #0x1
	add r4, r4, #0x1
	add r5, #0x8
	cmp r7, #0x8
	blt _0201AA2A
	ldr r2, [sp, #0xc]
	ldr r1, [sp, #0x1c]
	add r2, #0x40
	str r2, [sp, #0xc]
	cmp r2, r1
	blt _0201AA24
	add sp, #0x20
	pop {r3-r7, pc}
_0201AA80:
	add r1, r2, #0x0
	sub r1, #0x8
	add r3, r3, r1
	mov r1, #0x0
	str r1, [sp, #0x8]
	add r1, r2, #0x0
	cmp r1, #0x0
	ble _0201AB04
_0201AA90:
	mov r1, #0x0
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x1c]
	ldr r5, [sp, #0x0]
	sub r1, r1, #0x4
	str r1, [sp, #0x18]
	mov r1, #0x7
	ldr r4, [sp, #0x8]
	mov r12, r1
_0201AAA2:
	mov r1, #0x7
	add r6, r5, #0x0
	and r6, r1
	add r2, r5, #0x0
	mov r1, r12
	bic r2, r1
	ldr r1, [sp, #0x10]
	mul r2, r1
	add r1, r6, #0x0
	orr r1, r2
	lsl r2, r1, #0x3
	ldr r1, [sp, #0x8]
	add r6, r1, r2
	ldr r1, [sp, #0x1c]
	cmp r6, r1
	bge _0201AACC
	sub r1, r3, r6
	ldr r2, [r1, #0x0]
	sub r1, r3, r4
	str r2, [r1, #0x0]
	b _0201AAD0
_0201AACC:
	sub r1, r3, r4
	str r0, [r1, #0x0]
_0201AAD0:
	ldr r1, [sp, #0x18]
	sub r2, r6, #0x4
	cmp r2, r1
	bge _0201AAE4
	sub r1, r3, r2
	sub r2, r4, #0x4
	ldr r1, [r1, #0x0]
	sub r2, r3, r2
	str r1, [r2, #0x0]
	b _0201AAEA
_0201AAE4:
	sub r1, r4, #0x4
	sub r1, r3, r1
	str r0, [r1, #0x0]
_0201AAEA:
	ldr r1, [sp, #0x4]
	add r5, r5, #0x1
	add r1, r1, #0x1
	add r4, #0x8
	str r1, [sp, #0x4]
	cmp r1, #0x8
	blt _0201AAA2
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0x1c]
	add r2, #0x40
	str r2, [sp, #0x8]
	cmp r2, r1
	blt _0201AA90
_0201AB04:
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_0201AB08
FUN_0201AB08: ; 0x0201AB08
	ldrb r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0201AB0C
FUN_0201AB0C: ; 0x0201AB0C
	ldrb r0, [r0, #0x7]
	bx lr

	thumb_func_start FUN_0201AB10
FUN_0201AB10: ; 0x0201AB10
	ldrb r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_0201AB14
FUN_0201AB14: ; 0x0201AB14
	ldrb r0, [r0, #0x5]
	bx lr

	thumb_func_start FUN_0201AB18
FUN_0201AB18: ; 0x0201AB18
	ldrb r0, [r0, #0x6]
	bx lr

	thumb_func_start FUN_0201AB1C
FUN_0201AB1C: ; 0x0201AB1C
	strb r1, [r0, #0x5]
	bx lr

	thumb_func_start FUN_0201AB20
FUN_0201AB20: ; 0x0201AB20
	strb r1, [r0, #0x6]
	bx lr

	thumb_func_start FUN_0201AB24
FUN_0201AB24: ; 0x0201AB24
	strb r1, [r0, #0x9]
	bx lr

	thumb_func_start FUN_0201AB28
FUN_0201AB28: ; 0x0201AB28
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	bl FUN_020161A4
	add r1, sp, #0x0
	str r0, [r4, #0x0]
	bl FUN_020B0030
	ldr r0, [sp, #0x0]
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_0201AB44
FUN_0201AB44: ; 0x0201AB44
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	bl FUN_020161A4
	add r1, sp, #0x0
	str r0, [r4, #0x0]
	bl FUN_020B0138
	ldr r0, [sp, #0x0]
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_0201AB60
FUN_0201AB60: ; 0x0201AB60
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201AC78
	add r0, r4, #0x0
	bl FUN_0201AB78
	mov r0, #0x0
	strh r0, [r4, #0x4]
	strh r0, [r4, #0x6]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201AB78
FUN_0201AB78: ; 0x0201AB78
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r1, [r4, #0x6]
	mov r0, #0x1
	tst r0, r1
	beq _0201AB92
	ldr r2, [r4, #0x10]
	ldr r1, [r4, #0x8]
	ldr r3, [r4, #0xc]
	mov r0, #0x0
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201AB92:
	ldrh r1, [r4, #0x6]
	mov r0, #0x2
	tst r0, r1
	beq _0201ABA8
	ldr r2, [r4, #0x3c]
	ldr r1, [r4, #0x34]
	ldr r3, [r4, #0x38]
	mov r0, #0x1
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201ABA8:
	ldrh r1, [r4, #0x6]
	mov r0, #0x4
	tst r0, r1
	beq _0201ABBE
	ldr r2, [r4, #0x68]
	ldr r1, [r4, #0x60]
	ldr r3, [r4, #0x64]
	mov r0, #0x2
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201ABBE:
	ldrh r1, [r4, #0x6]
	mov r0, #0x8
	tst r0, r1
	beq _0201ABE0
	add r2, r4, #0x0
	add r1, r4, #0x0
	add r2, #0x94
	add r3, r4, #0x0
	add r1, #0x8c
	ldr r2, [r2, #0x0]
	add r3, #0x90
	ldr r1, [r1, #0x0]
	ldr r3, [r3, #0x0]
	mov r0, #0x3
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201ABE0:
	ldrh r1, [r4, #0x6]
	mov r0, #0x10
	tst r0, r1
	beq _0201AC02
	add r2, r4, #0x0
	add r1, r4, #0x0
	add r2, #0xc0
	add r3, r4, #0x0
	add r1, #0xb8
	ldr r2, [r2, #0x0]
	add r3, #0xbc
	ldr r1, [r1, #0x0]
	ldr r3, [r3, #0x0]
	mov r0, #0x4
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201AC02:
	ldrh r1, [r4, #0x6]
	mov r0, #0x20
	tst r0, r1
	beq _0201AC24
	add r2, r4, #0x0
	add r1, r4, #0x0
	add r2, #0xec
	add r3, r4, #0x0
	add r1, #0xe4
	ldr r2, [r2, #0x0]
	add r3, #0xe8
	ldr r1, [r1, #0x0]
	ldr r3, [r3, #0x0]
	mov r0, #0x5
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201AC24:
	ldrh r0, [r4, #0x6]
	mov r3, #0x40
	tst r0, r3
	beq _0201AC44
	add r2, r3, #0x0
	add r1, r3, #0x0
	add r2, #0xd8
	add r1, #0xd0
	ldr r2, [r4, r2]
	add r3, #0xd4
	ldr r1, [r4, r1]
	ldr r3, [r4, r3]
	mov r0, #0x6
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201AC44:
	ldrh r0, [r4, #0x6]
	mov r3, #0x80
	tst r0, r3
	beq _0201AC64
	add r2, r3, #0x0
	add r1, r3, #0x0
	add r2, #0xc4
	add r1, #0xbc
	ldr r2, [r4, r2]
	add r3, #0xc0
	ldr r1, [r4, r1]
	ldr r3, [r4, r3]
	mov r0, #0x7
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201AC64:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201AC68
FUN_0201AC68: ; 0x0201AC68
	ldrh r3, [r0, #0x6]
	mov r2, #0x1
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strh r1, [r0, #0x6]
	bx lr
	.balign 4

	thumb_func_start FUN_0201AC78
FUN_0201AC78: ; 0x0201AC78
	push {r4, lr}
	sub sp, #0x48
	add r4, r0, #0x0
	ldrh r1, [r4, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201AC9E
	ldr r1, [r4, #0x14]
	ldr r0, _0201AEB0 ; =0x000001FF
	add r2, r1, #0x0
	ldr r1, [r4, #0x18]
	and r2, r0
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, _0201AEB4 ; =0x04000010
	str r1, [r0, #0x0]
_0201AC9E:
	ldrh r1, [r4, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201ACBE
	ldr r1, [r4, #0x40]
	ldr r0, _0201AEB0 ; =0x000001FF
	add r2, r1, #0x0
	ldr r1, [r4, #0x44]
	and r2, r0
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, _0201AEB8 ; =0x04000014
	str r1, [r0, #0x0]
_0201ACBE:
	ldrh r1, [r4, #0x4]
	mov r0, #0x4
	tst r0, r1
	beq _0201AD1E
	add r0, r4, #0x0
	add r0, #0x74
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201ACEA
	ldr r1, [r4, #0x6c]
	ldr r0, _0201AEB0 ; =0x000001FF
	add r2, r1, #0x0
	ldr r1, [r4, #0x70]
	and r2, r0
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, _0201AEBC ; =0x04000018
	str r1, [r0, #0x0]
	b _0201AD1E
_0201ACEA:
	mov r0, #0x2
	str r0, [sp, #0x0]
	add r1, r4, #0x0
	add r1, #0x78
	add r3, r4, #0x0
	add r3, #0x80
	ldrh r1, [r1, #0x0]
	ldr r2, [r4, #0x7c]
	ldr r3, [r3, #0x0]
	add r0, sp, #0x38
	bl MTX22_2DAffine
	ldr r0, [r4, #0x6c]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x70]
	add r3, r4, #0x0
	str r0, [sp, #0x4]
	add r2, #0x84
	add r3, #0x88
	ldr r0, _0201AEC0 ; =0x04000020
	ldr r2, [r2, #0x0]
	ldr r3, [r3, #0x0]
	add r1, sp, #0x38
	bl G2x_SetBGyAffine_
_0201AD1E:
	ldrh r1, [r4, #0x4]
	mov r0, #0x8
	tst r0, r1
	beq _0201AD8E
	add r0, r4, #0x0
	add r0, #0xa0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201AD4E
	add r0, r4, #0x0
	add r2, r4, #0x0
	add r0, #0x98
	add r2, #0x9c
	ldr r2, [r2, #0x0]
	ldr r0, [r0, #0x0]
	ldr r1, _0201AEB0 ; =0x000001FF
	lsl r2, r2, #0x10
	and r0, r1
	lsl r1, r1, #0x10
	and r1, r2
	orr r1, r0
	ldr r0, _0201AEC4 ; =0x0400001C
	str r1, [r0, #0x0]
	b _0201AD8E
_0201AD4E:
	mov r0, #0x2
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	add r1, #0xa4
	add r2, r4, #0x0
	add r3, r4, #0x0
	add r2, #0xa8
	add r3, #0xac
	ldrh r1, [r1, #0x0]
	ldr r2, [r2, #0x0]
	ldr r3, [r3, #0x0]
	add r0, sp, #0x28
	bl MTX22_2DAffine
	add r0, r4, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r0, #0x9c
	ldr r0, [r0, #0x0]
	add r3, r4, #0x0
	str r0, [sp, #0x4]
	add r2, #0xb0
	add r3, #0xb4
	ldr r0, _0201AEC8 ; =0x04000030
	ldr r2, [r2, #0x0]
	ldr r3, [r3, #0x0]
	add r1, sp, #0x28
	bl G2x_SetBGyAffine_
_0201AD8E:
	ldrh r1, [r4, #0x4]
	mov r0, #0x10
	tst r0, r1
	beq _0201ADB2
	add r0, r4, #0x0
	add r2, r4, #0x0
	add r0, #0xc4
	add r2, #0xc8
	ldr r2, [r2, #0x0]
	ldr r0, [r0, #0x0]
	ldr r1, _0201AEB0 ; =0x000001FF
	lsl r2, r2, #0x10
	and r0, r1
	lsl r1, r1, #0x10
	and r1, r2
	orr r1, r0
	ldr r0, _0201AECC ; =0x04001010
	str r1, [r0, #0x0]
_0201ADB2:
	ldrh r1, [r4, #0x4]
	mov r0, #0x20
	tst r0, r1
	beq _0201ADD6
	add r0, r4, #0x0
	add r2, r4, #0x0
	add r0, #0xf0
	add r2, #0xf4
	ldr r2, [r2, #0x0]
	ldr r0, [r0, #0x0]
	ldr r1, _0201AEB0 ; =0x000001FF
	lsl r2, r2, #0x10
	and r0, r1
	lsl r1, r1, #0x10
	and r1, r2
	orr r1, r0
	ldr r0, _0201AED0 ; =0x04001014
	str r1, [r0, #0x0]
_0201ADD6:
	ldrh r0, [r4, #0x4]
	mov r3, #0x40
	tst r0, r3
	beq _0201AE3E
	add r0, r3, #0x0
	add r0, #0xe4
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	bne _0201AE04
	ldr r1, _0201AEB0 ; =0x000001FF
	add r3, #0xdc
	add r2, r1, #0x0
	sub r2, #0xdf
	ldr r0, [r4, r3]
	ldr r2, [r4, r2]
	and r0, r1
	lsl r2, r2, #0x10
	lsl r1, r1, #0x10
	and r1, r2
	orr r1, r0
	ldr r0, _0201AED4 ; =0x04001018
	str r1, [r0, #0x0]
	b _0201AE3E
_0201AE04:
	mov r0, #0x2
	add r1, r3, #0x0
	add r2, r3, #0x0
	str r0, [sp, #0x0]
	add r1, #0xe8
	add r2, #0xec
	add r3, #0xf0
	ldrh r1, [r4, r1]
	ldr r2, [r4, r2]
	ldr r3, [r4, r3]
	add r0, sp, #0x18
	bl MTX22_2DAffine
	mov r3, #0x47
	lsl r3, r3, #0x2
	ldr r0, [r4, r3]
	add r2, r3, #0x0
	str r0, [sp, #0x0]
	add r0, r3, #0x4
	ldr r0, [r4, r0]
	add r2, #0x18
	str r0, [sp, #0x4]
	add r3, #0x1c
	ldr r0, _0201AED8 ; =0x04001020
	ldr r2, [r4, r2]
	ldr r3, [r4, r3]
	add r1, sp, #0x18
	bl G2x_SetBGyAffine_
_0201AE3E:
	ldrh r0, [r4, #0x4]
	mov r3, #0x80
	tst r0, r3
	beq _0201AEAC
	add r0, r3, #0x0
	add r0, #0xd0
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	bne _0201AE72
	add r3, #0xc8
	ldr r1, [r4, r3]
	ldr r0, _0201AEB0 ; =0x000001FF
	add r2, r1, #0x0
	add r1, r0, #0x0
	sub r1, #0xb3
	ldr r1, [r4, r1]
	and r2, r0
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, _0201AEDC ; =0x0400101C
	add sp, #0x48
	str r1, [r0, #0x0]
	pop {r4, pc}
_0201AE72:
	mov r0, #0x2
	add r1, r3, #0x0
	add r2, r3, #0x0
	str r0, [sp, #0x0]
	add r1, #0xd4
	add r2, #0xd8
	add r3, #0xdc
	ldrh r1, [r4, r1]
	ldr r2, [r4, r2]
	ldr r3, [r4, r3]
	add r0, sp, #0x8
	bl MTX22_2DAffine
	mov r3, #0x52
	lsl r3, r3, #0x2
	ldr r0, [r4, r3]
	add r2, r3, #0x0
	str r0, [sp, #0x0]
	add r0, r3, #0x4
	ldr r0, [r4, r0]
	add r2, #0x18
	str r0, [sp, #0x4]
	add r3, #0x1c
	ldr r0, _0201AEE0 ; =0x04001030
	ldr r2, [r4, r2]
	ldr r3, [r4, r3]
	add r1, sp, #0x8
	bl G2x_SetBGyAffine_
_0201AEAC:
	add sp, #0x48
	pop {r4, pc}
	.balign 4
_0201AEB0: .word 0x000001FF
_0201AEB4: .word 0x04000010
_0201AEB8: .word 0x04000014
_0201AEBC: .word 0x04000018
_0201AEC0: .word 0x04000020
_0201AEC4: .word 0x0400001C
_0201AEC8: .word 0x04000030
_0201AECC: .word 0x04001010
_0201AED0: .word 0x04001014
_0201AED4: .word 0x04001018
_0201AED8: .word 0x04001020
_0201AEDC: .word 0x0400101C
_0201AEE0: .word 0x04001030

	thumb_func_start FUN_0201AEE4
FUN_0201AEE4: ; 0x0201AEE4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x0
	mov r0, #0x2c
	add r1, #0x8
	mul r0, r4
	add r0, r1, r0
	add r1, r2, #0x0
	add r2, r3, #0x0
	bl FUN_02017B8C
	mov r0, #0x1
	ldrh r1, [r5, #0x4]
	lsl r0, r4
	orr r0, r1
	strh r0, [r5, #0x4]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201AF08
FUN_0201AF08: ; 0x0201AF08
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x0
	mov r0, #0x2c
	add r1, #0x8
	mul r0, r4
	add r0, r1, r0
	add r1, r2, #0x0
	add r2, r3, #0x0
	bl FUN_0201AF2C
	mov r0, #0x1
	ldrh r1, [r5, #0x4]
	lsl r0, r4
	orr r0, r1
	strh r0, [r5, #0x4]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201AF2C
FUN_0201AF2C: ; 0x0201AF2C
	cmp r1, #0x0
	beq _0201AF3A
	cmp r1, #0x1
	beq _0201AF3E
	cmp r1, #0x2
	beq _0201AF46
	bx lr
_0201AF3A:
	strh r2, [r0, #0x18]
	bx lr
_0201AF3E:
	ldrh r1, [r0, #0x18]
	add r1, r1, r2
	strh r1, [r0, #0x18]
	bx lr
_0201AF46:
	ldrh r1, [r0, #0x18]
	sub r1, r1, r2
	strh r1, [r0, #0x18]
	bx lr
	.balign 4

	thumb_func_start FUN_0201AF50
FUN_0201AF50: ; 0x0201AF50
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x0
	mov r0, #0x2c
	add r1, #0x8
	mul r0, r4
	add r0, r1, r0
	add r1, r2, #0x0
	add r2, r3, #0x0
	bl FUN_0201AF74
	mov r0, #0x1
	ldrh r1, [r5, #0x4]
	lsl r0, r4
	orr r0, r1
	strh r0, [r5, #0x4]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201AF74
FUN_0201AF74: ; 0x0201AF74
	sub r1, #0x9
	cmp r1, #0x5
	bhi _0201AFB8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0201AF86: ; jump table (using 16-bit offset)
	.short _0201AF92 - _0201AF86 - 2; case 0
	.short _0201AF96 - _0201AF86 - 2; case 1
	.short _0201AF9E - _0201AF86 - 2; case 2
	.short _0201AFA6 - _0201AF86 - 2; case 3
	.short _0201AFAA - _0201AF86 - 2; case 4
	.short _0201AFB2 - _0201AF86 - 2; case 5
_0201AF92:
	str r2, [r0, #0x24]
	bx lr
_0201AF96:
	ldr r1, [r0, #0x24]
	add r1, r1, r2
	str r1, [r0, #0x24]
	bx lr
_0201AF9E:
	ldr r1, [r0, #0x24]
	sub r1, r1, r2
	str r1, [r0, #0x24]
	bx lr
_0201AFA6:
	str r2, [r0, #0x28]
	bx lr
_0201AFAA:
	ldr r1, [r0, #0x28]
	add r1, r1, r2
	str r1, [r0, #0x28]
	bx lr
_0201AFB2:
	ldr r1, [r0, #0x28]
	sub r1, r1, r2
	str r1, [r0, #0x28]
_0201AFB8:
	bx lr
	.balign 4

	thumb_func_start FUN_0201AFBC
FUN_0201AFBC: ; 0x0201AFBC
	push {r4-r7, lr}
	sub sp, #0x1c
	str r1, [sp, #0x0]
	add r7, r0, #0x0
	str r2, [sp, #0x4]
	ldr r0, [sp, #0x30]
	str r3, [sp, #0x8]
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x0]
	add r4, r7, #0x0
	mov r1, #0x2c
	add r5, r0, #0x0
	mul r5, r1
	add r4, #0x8
	ldr r0, [r4, r5]
	cmp r0, #0x0
	bne _0201AFE4
	add sp, #0x1c
	mov r0, #0x0
	pop {r4-r7, pc}
_0201AFE4:
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x8]
	add r2, r7, r5
	lsl r0, r0, #0x15
	lsl r1, r1, #0x15
	ldrb r2, [r2, #0x1d]
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_02017FFC
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_020187B0
	str r0, [sp, #0x18]
	ldr r1, [sp, #0x4]
	mov r0, #0x7
	and r1, r0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldr r1, [sp, #0x8]
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r7, r5
	str r0, [sp, #0x10]
	ldrb r0, [r1, #0x1e]
	cmp r0, #0x0
	bne _0201B096
	ldr r0, [r4, r5]
	mov r1, #0x40
	str r0, [sp, #0xc]
	ldr r0, [r7, #0x0]
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	lsl r0, r6, #0x1
	ldr r1, [sp, #0xc]
	mov r12, r0
	ldrh r0, [r1, r0]
	mov r3, #0x0
	mov r6, #0xf
	lsl r0, r0, #0x16
	lsr r1, r0, #0x11
	ldr r0, [sp, #0x18]
	add r2, r0, r1
_0201B042:
	ldrb r5, [r2, r3]
	lsl r0, r3, #0x1
	add r1, r4, r0
	and r5, r6
	strb r5, [r4, r0]
	ldrb r0, [r2, r3]
	asr r0, r0, #0x4
	strb r0, [r1, #0x1]
	add r0, r3, #0x1
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	cmp r3, #0x20
	blo _0201B042
	ldr r2, [sp, #0xc]
	mov r1, r12
	ldrh r1, [r2, r1]
	add r0, r7, #0x0
	asr r2, r1, #0xa
	mov r1, #0x3
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r2, r4, #0x0
	bl FUN_0201B118
	ldr r0, [sp, #0x10]
	lsl r1, r0, #0x3
	ldr r0, [sp, #0x14]
	add r0, r0, r1
	ldrb r5, [r4, r0]
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r0, [sp, #0x30]
	ldrh r2, [r0, #0x0]
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r1, r5
	tst r1, r2
	beq _0201B10C
	add sp, #0x1c
	pop {r4-r7, pc}
_0201B096:
	ldrb r0, [r1, #0x1c]
	cmp r0, #0x1
	beq _0201B0E0
	ldr r0, [r7, #0x0]
	ldr r4, [r4, r5]
	mov r1, #0x40
	bl AllocFromHeapAtEnd
	lsl r6, r6, #0x1
	ldrh r1, [r4, r6]
	add r5, r0, #0x0
	lsl r1, r1, #0x16
	lsr r2, r1, #0x10
	ldr r1, [sp, #0x18]
	add r1, r1, r2
	mov r2, #0x40
	bl memcpy
	ldrh r1, [r4, r6]
	add r0, r7, #0x0
	asr r2, r1, #0xa
	mov r1, #0x3
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r2, r5, #0x0
	bl FUN_0201B118
	ldr r0, [sp, #0x10]
	lsl r1, r0, #0x3
	ldr r0, [sp, #0x14]
	add r0, r0, r1
	ldrb r4, [r5, r0]
	add r0, r5, #0x0
	bl FreeToHeap
	b _0201B0F4
_0201B0E0:
	ldr r1, [r4, r5]
	ldr r0, [sp, #0x10]
	ldrb r1, [r1, r6]
	lsl r0, r0, #0x3
	lsl r2, r1, #0x6
	ldr r1, [sp, #0x14]
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, [sp, #0x18]
	ldrb r4, [r0, r1]
_0201B0F4:
	ldr r0, [sp, #0x30]
	ldrh r2, [r0, #0x0]
	lsl r0, r2, #0x18
	lsr r1, r0, #0x18
	ldr r0, _0201B114 ; =0x0000FFFF
_0201B0FE:
	cmp r2, r0
	beq _0201B10C
	cmp r4, r1
	bne _0201B0FE
	add sp, #0x1c
	mov r0, #0x1
	pop {r4-r7, pc}
_0201B10C:
	mov r0, #0x0
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_0201B114: .word 0x0000FFFF

	thumb_func_start FUN_0201B118
FUN_0201B118: ; 0x0201B118
	push {r3-r7, lr}
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r7, r2, #0x0
	cmp r1, #0x0
	beq _0201B1A4
	ldr r0, [r0, #0x0]
	mov r1, #0x40
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	tst r0, r1
	beq _0201B166
	mov r0, #0x0
	mov r5, #0x7
_0201B13A:
	lsl r3, r0, #0x3
	add r2, r7, r3
	mov r1, #0x0
	add r3, r4, r3
_0201B142:
	sub r6, r5, r1
	ldrb r6, [r2, r6]
	strb r6, [r3, r1]
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #0x8
	blo _0201B142
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x8
	blo _0201B13A
	add r0, r7, #0x0
	add r1, r4, #0x0
	mov r2, #0x40
	bl memcpy
_0201B166:
	ldr r0, [sp, #0x0]
	mov r1, #0x2
	tst r0, r1
	beq _0201B19E
	mov r5, #0x0
	mov r6, #0x7
_0201B172:
	lsl r0, r5, #0x3
	add r3, r4, r0
	sub r0, r6, r5
	lsl r0, r0, #0x3
	add r2, r7, r0
	mov r1, #0x8
_0201B17E:
	ldrb r0, [r2, #0x0]
	add r2, r2, #0x1
	strb r0, [r3, #0x0]
	add r3, r3, #0x1
	sub r1, r1, #0x1
	bne _0201B17E
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x8
	blo _0201B172
	add r0, r7, #0x0
	add r1, r4, #0x0
	mov r2, #0x40
	bl memcpy
_0201B19E:
	add r0, r4, #0x0
	bl FreeToHeap
_0201B1A4:
	pop {r3-r7, pc}
	.balign 4
