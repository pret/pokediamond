	.include "asm/macros.inc"
	.include "global.inc"

	.public UNK_021C46B4

	.section .rodata

	.global UNK_020ECEF4
UNK_020ECEF4: ; 0x020ECEF4
	.word FUN_0200E850
	.word FUN_0200E86C
	.word FUN_0200E88C
	.word FUN_0200E8C8
	.word FUN_0200E900
	.word FUN_0200E93C
	.word FUN_0200E974
	.word FUN_0200E9A0
	.word FUN_0200E9CC
	.word FUN_0200EA08
	.word FUN_0200EA40
	.word FUN_0200EA7C
	.word FUN_0200EAB4
	.word FUN_0200EAE0
	.word FUN_0200EB0C
	.word FUN_0200EB40
	.word FUN_0200EB70
	.word FUN_0200EB9C
	.word FUN_0200EBC8
	.word FUN_0200EBF4
	.word FUN_0200EC20
	.word FUN_0200EC4C
	.word FUN_0200EC78
	.word FUN_0200ECA4
	.word FUN_0200ECD0
	.word FUN_0200ECFC
	.word FUN_0200ED28
	.word FUN_0200ED54
	.word FUN_0200ED80
	.word FUN_0200EDD4
	.word FUN_0200EE24
	.word FUN_0200EE60
	.word FUN_0200EE98
	.word FUN_0200EED8
	.word FUN_0200EF14
	.word FUN_0200EF54
	.word FUN_0200EF90
	.word FUN_0200EFBC
	.word FUN_0200EFE8
	.word FUN_0200F014
	.word FUN_0200F040
	.word FUN_0200F07C

	.text

	thumb_func_start FUN_0200E1D0
FUN_0200E1D0: ; 0x0200E1D0
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	ldr r0, [sp, #0x30]
	add r4, r1, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	cmp r0, #0x0
	bne _0200E1E6
	bl GF_AssertFail
_0200E1E6:
	ldr r0, [sp, #0x34]
	cmp r0, #0x0
	bne _0200E1F0
	bl GF_AssertFail
_0200E1F0:
	ldr r0, _0200E2AC ; =UNK_021C46B4 + 0x140
	ldrh r0, [r0, #0xc]
	cmp r0, #0x0
	beq _0200E1FC
	bl GF_AssertFail
_0200E1FC:
	ldr r0, _0200E2B0 ; =UNK_021C46B4
	bl FUN_0200E808
	ldr r1, _0200E2B0 ; =UNK_021C46B4
	add r0, r5, #0x0
	bl FUN_0200E558
	ldr r0, _0200E2B4 ; =UNK_021C46B4 + 0x74
	bl FUN_0200E5F4
	ldr r0, _0200E2B0 ; =UNK_021C46B4
	add r1, r6, #0x0
	bl FUN_0200E75C
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, _0200E2B8 ; =UNK_021C46B4 + 0x8C
	ldr r2, [sp, #0x30]
	str r0, [sp, #0xc]
	ldr r0, _0200E2B4 ; =UNK_021C46B4 + 0x74
	ldr r3, [sp, #0x34]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x38]
	add r1, r4, #0x0
	str r0, [sp, #0x14]
	ldr r0, _0200E2BC ; =UNK_021C46B4 + 0x14
	str r5, [sp, #0x18]
	bl FUN_0200E5C8
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	ldr r0, _0200E2B8 ; =UNK_021C46B4 + 0x8C
	ldr r2, [sp, #0x30]
	str r0, [sp, #0xc]
	ldr r0, _0200E2B4 ; =UNK_021C46B4 + 0x74
	ldr r3, [sp, #0x34]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x38]
	add r1, r7, #0x0
	str r0, [sp, #0x14]
	ldr r0, _0200E2C0 ; =UNK_021C46B4 + 0x44
	str r5, [sp, #0x18]
	bl FUN_0200E5C8
	ldr r0, _0200E2AC ; =UNK_021C46B4 + 0x140
	mov r1, #0x1
	strh r1, [r0, #0xc]
	ldr r0, _0200E2C4 ; =UNK_021C46B4 + 0x4
	ldr r1, _0200E2BC ; =UNK_021C46B4 + 0x14
	bl FUN_0200E528
	ldr r0, _0200E2C8 ; =UNK_021C46B4 + 0x8
	ldr r1, _0200E2C0 ; =UNK_021C46B4 + 0x44
	bl FUN_0200E528
	ldr r0, _0200E2CC ; =UNK_021C46B4
	ldr r0, [r0, #0xc]
	cmp r0, #0x0
	beq _0200E28E
	ldr r0, _0200E2B0 ; =UNK_021C46B4
	add r0, #0x14
	bl FUN_0200E7A8
	ldr r1, _0200E2D0 ; =0x0000014E
	ldr r0, _0200E2B0 ; =UNK_021C46B4
	mov r2, #0x1
	strb r2, [r0, r1]
_0200E28E:
	ldr r0, _0200E2B0 ; =UNK_021C46B4
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	beq _0200E2A6
	ldr r0, _0200E2B0 ; =UNK_021C46B4
	add r0, #0x44
	bl FUN_0200E7A8
	ldr r1, _0200E2D4 ; =0x0000014F
	ldr r0, _0200E2B0 ; =UNK_021C46B4
	mov r2, #0x1
	strb r2, [r0, r1]
_0200E2A6:
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_0200E2AC: .word UNK_021C46B4 + 0x140
_0200E2B0: .word UNK_021C46B4
_0200E2B4: .word UNK_021C46B4 + 0x74
_0200E2B8: .word UNK_021C46B4 + 0x8C
_0200E2BC: .word UNK_021C46B4 + 0x14
_0200E2C0: .word UNK_021C46B4 + 0x44
_0200E2C4: .word UNK_021C46B4 + 0x4
_0200E2C8: .word UNK_021C46B4 + 0x8
_0200E2CC: .word UNK_021C46B4
_0200E2D0: .word 0x0000014E
_0200E2D4: .word 0x0000014F

	thumb_func_start FUN_0200E2D8
FUN_0200E2D8: ; 0x0200E2D8
	push {r4, lr}
	ldr r0, _0200E300 ; =UNK_021C46B4 + 0x140
	ldr r4, _0200E304 ; =UNK_021C46B4
	ldrh r0, [r0, #0xc]
	cmp r0, #0x0
	beq _0200E2FC
	add r1, r4, #0x0
	add r2, r4, #0x0
	add r0, r4, #0x0
	add r1, #0x14
	add r2, #0x44
	bl FUN_0200E4B8
	cmp r0, #0x1
	bne _0200E2FC
	add r0, r4, #0x0
	bl FUN_0200E460
_0200E2FC:
	pop {r4, pc}
	nop
_0200E300: .word UNK_021C46B4 + 0x140
_0200E304: .word UNK_021C46B4

	thumb_func_start FUN_0200E308
FUN_0200E308: ; 0x0200E308
	ldr r0, _0200E318 ; =UNK_021C46B4 + 0x140
	ldrh r0, [r0, #0xc]
	cmp r0, #0x0
	bne _0200E314
	mov r0, #0x1
	bx lr
_0200E314:
	mov r0, #0x0
	bx lr
	.balign 4
_0200E318: .word UNK_021C46B4 + 0x140

	thumb_func_start FUN_0200E31C
FUN_0200E31C: ; 0x0200E31C
	push {r3, lr}
	ldr r0, _0200E368 ; =UNK_021C46B4 + 0x74
	mov r1, #0x0
	bl FUN_0200E6A0
	ldr r0, _0200E368 ; =UNK_021C46B4 + 0x74
	mov r1, #0x1
	bl FUN_0200E6A0
	ldr r0, _0200E36C ; =UNK_021C46B4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0200E33A
	mov r1, #0x2
	str r1, [r0, #0x20]
_0200E33A:
	ldr r0, _0200E36C ; =UNK_021C46B4
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	beq _0200E346
	mov r1, #0x2
	str r1, [r0, #0x50]
_0200E346:
	ldr r0, _0200E370 ; =UNK_021C46B4 + 0x4
	ldr r1, _0200E374 ; =UNK_021C46B4 + 0x14
	bl FUN_0200E528
	ldr r0, _0200E378 ; =UNK_021C46B4 + 0x8
	ldr r1, _0200E37C ; =UNK_021C46B4 + 0x44
	bl FUN_0200E528
	ldr r0, _0200E380 ; =UNK_021C46B4 + 0x140
	mov r1, #0x0
	strh r1, [r0, #0xc]
	strb r1, [r0, #0xe]
	strb r1, [r0, #0xf]
	ldr r0, _0200E384 ; =UNK_021C46B4
	bl FUN_0200E808
	pop {r3, pc}
	.balign 4
_0200E368: .word UNK_021C46B4 + 0x74
_0200E36C: .word UNK_021C46B4
_0200E370: .word UNK_021C46B4 + 0x4
_0200E374: .word UNK_021C46B4 + 0x14
_0200E378: .word UNK_021C46B4 + 0x8
_0200E37C: .word UNK_021C46B4 + 0x44
_0200E380: .word UNK_021C46B4 + 0x140
_0200E384: .word UNK_021C46B4

	thumb_func_start FUN_0200E388
FUN_0200E388: ; 0x0200E388
	ldr r3, _0200E390 ; =FUN_02011480
	add r1, r0, #0x0
	mov r0, #0x0
	bx r3
	.balign 4
_0200E390: .word FUN_02011480

	thumb_func_start SetMasterBrightnessNeutral
SetMasterBrightnessNeutral: ; 0x0200E394
	ldr r3, _0200E39C ; =FUN_0200E440
	mov r1, #0x0
	bx r3
	nop
_0200E39C: .word FUN_0200E440

	thumb_func_start FUN_0200E3A0
FUN_0200E3A0: ; 0x0200E3A0
	ldr r2, _0200E3B4 ; =0x00007FFF
	cmp r1, r2
	bne _0200E3AA
	mov r1, #0x10
	b _0200E3AE
_0200E3AA:
	mov r1, #0xf
	mvn r1, r1
_0200E3AE:
	ldr r3, _0200E3B8 ; =FUN_0200E440
	bx r3
	nop
_0200E3B4: .word 0x00007FFF
_0200E3B8: .word FUN_0200E440

	thumb_func_start FUN_0200E3BC
FUN_0200E3BC: ; 0x0200E3BC
	push {r0-r3}
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r0, sp, #0x1c
	bne _0200E3D2
	mov r1, #0x0
	mov r2, #0x2
	bl GX_LoadBGPltt
	b _0200E3DA
_0200E3D2:
	mov r1, #0x0
	mov r2, #0x2
	bl GXS_LoadBGPltt
_0200E3DA:
	ldr r0, _0200E41C ; =UNK_021C46B4 + 0x8C
	mov r1, #0x1
	add r2, r4, #0x0
	bl FUN_02011634
	mov r2, #0x0
	ldr r0, _0200E41C ; =UNK_021C46B4 + 0x8C
	mov r1, #0x3f
	add r3, r2, #0x0
	str r4, [sp, #0x0]
	bl FUN_02011650
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r0, _0200E41C ; =UNK_021C46B4 + 0x8C
	add r2, r1, #0x0
	add r3, r1, #0x0
	str r4, [sp, #0x8]
	bl FUN_02011698
	ldr r0, _0200E41C ; =UNK_021C46B4 + 0x8C
	mov r1, #0x20
	mov r2, #0x0
	add r3, r4, #0x0
	bl FUN_02011678
	add sp, #0xc
	pop {r3-r4}
	pop {r3}
	add sp, #0x10
	bx r3
	nop
_0200E41C: .word UNK_021C46B4 + 0x8C

	thumb_func_start FUN_0200E420
FUN_0200E420: ; 0x0200E420
	push {r0-r3}
	push {r3, lr}
	add r0, sp, #0x8
	mov r1, #0x0
	mov r2, #0x2
	bl GX_LoadBGPltt
	add r0, sp, #0x8
	mov r1, #0x0
	mov r2, #0x2
	bl GXS_LoadBGPltt
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3

	thumb_func_start FUN_0200E440
FUN_0200E440: ; 0x0200E440
	push {r3, lr}
	cmp r0, #0x0
	bne _0200E44E
	ldr r0, _0200E458 ; =0x0400006C
	bl GXx_SetMasterBrightness_
	pop {r3, pc}
_0200E44E:
	ldr r0, _0200E45C ; =0x0400106C
	bl GXx_SetMasterBrightness_
	pop {r3, pc}
	nop
_0200E458: .word 0x0400006C
_0200E45C: .word 0x0400106C

	thumb_func_start FUN_0200E460
FUN_0200E460: ; 0x0200E460
	push {r4, lr}
	mov r1, #0x53
	add r4, r0, #0x0
	mov r2, #0x0
	lsl r1, r1, #0x2
	strh r2, [r4, r1]
	bl FUN_0200E770
	mov r1, #0x15
	lsl r1, r1, #0x4
	strh r0, [r4, r1]
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	beq _0200E490
	add r0, r4, #0x0
	add r0, #0x14
	bl FUN_0200E7D8
	ldr r0, [r4, #0x3c]
	cmp r0, #0x0
	bne _0200E490
	ldr r0, _0200E4B4 ; =UNK_021C46B4 + 0x140
	mov r1, #0x0
	strb r1, [r0, #0xe]
_0200E490:
	ldr r0, [r4, #0x10]
	cmp r0, #0x0
	beq _0200E4AA
	add r0, r4, #0x0
	add r0, #0x44
	bl FUN_0200E7D8
	ldr r0, [r4, #0x3c]
	cmp r0, #0x0
	bne _0200E4AA
	ldr r0, _0200E4B4 ; =UNK_021C46B4 + 0x140
	mov r1, #0x0
	strb r1, [r0, #0xf]
_0200E4AA:
	add r0, r4, #0x0
	bl FUN_0200E808
	pop {r4, pc}
	nop
_0200E4B4: .word UNK_021C46B4 + 0x140

	thumb_func_start FUN_0200E4B8
FUN_0200E4B8: ; 0x0200E4B8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r2, #0x0
	cmp r0, #0x0
	beq _0200E4CE
	cmp r0, #0x1
	beq _0200E4E0
	cmp r0, #0x2
	beq _0200E4FA
	b _0200E512
_0200E4CE:
	add r0, r5, #0x4
	bl FUN_0200E528
	add r0, r5, #0x0
	add r0, #0x8
	add r1, r4, #0x0
	bl FUN_0200E528
	b _0200E512
_0200E4E0:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _0200E4EE
	add r0, r5, #0x4
	bl FUN_0200E528
	b _0200E512
_0200E4EE:
	add r0, r5, #0x0
	add r0, #0x8
	add r1, r4, #0x0
	bl FUN_0200E528
	b _0200E512
_0200E4FA:
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	beq _0200E50C
	add r0, r5, #0x0
	add r0, #0x8
	add r1, r4, #0x0
	bl FUN_0200E528
	b _0200E512
_0200E50C:
	add r0, r5, #0x4
	bl FUN_0200E528
_0200E512:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _0200E522
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	bne _0200E522
	mov r0, #0x1
	pop {r3-r5, pc}
_0200E522:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0200E528
FUN_0200E528: ; 0x0200E528
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0200E540
	add r0, r1, #0x0
	bl FUN_0200E544
	cmp r0, #0x1
	bne _0200E540
	mov r0, #0x0
	str r0, [r4, #0x0]
_0200E540:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200E544
FUN_0200E544: ; 0x0200E544
	push {r3, lr}
	ldr r1, [r0, #0x0]
	lsl r2, r1, #0x2
	ldr r1, _0200E554 ; =UNK_020ECEF4
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_0200E554: .word UNK_020ECEF4

	thumb_func_start FUN_0200E558
FUN_0200E558: ; 0x0200E558
	push {r3, lr}
	cmp r0, #0x4
	bhi _0200E5B8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0200E56A: ; jump table (using 16-bit offset)
	.short _0200E574 - _0200E56A - 2; case 0
	.short _0200E582 - _0200E56A - 2; case 1
	.short _0200E590 - _0200E56A - 2; case 2
	.short _0200E59E - _0200E56A - 2; case 3
	.short _0200E5AC - _0200E56A - 2; case 4
_0200E574:
	mov r2, #0x1
	add r0, r1, #0x0
	mov r1, #0x0
	add r3, r2, #0x0
	bl FUN_0200E5BC
	pop {r3, pc}
_0200E582:
	add r0, r1, #0x0
	mov r1, #0x1
	add r2, r1, #0x0
	add r3, r1, #0x0
	bl FUN_0200E5BC
	pop {r3, pc}
_0200E590:
	mov r2, #0x1
	add r0, r1, #0x0
	mov r1, #0x2
	add r3, r2, #0x0
	bl FUN_0200E5BC
	pop {r3, pc}
_0200E59E:
	add r0, r1, #0x0
	mov r1, #0x1
	add r2, r1, #0x0
	mov r3, #0x0
	bl FUN_0200E5BC
	pop {r3, pc}
_0200E5AC:
	add r0, r1, #0x0
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x1
	bl FUN_0200E5BC
_0200E5B8:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0200E5BC
FUN_0200E5BC: ; 0x0200E5BC
	str r1, [r0, #0x0]
	str r2, [r0, #0x4]
	str r3, [r0, #0x8]
	str r2, [r0, #0xc]
	str r3, [r0, #0x10]
	bx lr

	thumb_func_start FUN_0200E5C8
FUN_0200E5C8: ; 0x0200E5C8
	str r1, [r0, #0x0]
	str r2, [r0, #0x4]
	ldr r1, [sp, #0x0]
	str r3, [r0, #0x8]
	str r1, [r0, #0xc]
	ldr r1, [sp, #0x4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x8]
	str r1, [r0, #0x10]
	ldr r1, [sp, #0xc]
	str r1, [r0, #0x18]
	ldr r1, [sp, #0x10]
	str r1, [r0, #0x1c]
	ldr r1, [sp, #0x14]
	str r1, [r0, #0x20]
	ldr r1, _0200E5F0 ; =0xFFFFFFF0
	add r1, sp
	ldrh r1, [r1, #0x28]
	strh r1, [r0, #0x24]
	bx lr
	.balign 4
_0200E5F0: .word 0xFFFFFFF0

	thumb_func_start FUN_0200E5F4
FUN_0200E5F4: ; 0x0200E5F4
	mov r3, #0x0
	ldr r1, _0200E60C ; =FUN_0200E758
	add r2, r3, #0x0
_0200E5FA:
	str r2, [r0, #0x0]
	str r1, [r0, #0x8]
	str r2, [r0, #0x10]
	add r3, r3, #0x1
	add r0, r0, #0x4
	cmp r3, #0x2
	blt _0200E5FA
	bx lr
	nop
_0200E60C: .word FUN_0200E758

	thumb_func_start FUN_0200E610
FUN_0200E610: ; 0x0200E610
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_0200E616:
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x8]
	blx r1
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x2
	blt _0200E616
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0200E628
FUN_0200E628: ; 0x0200E628
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	str r0, [sp, #0x8]
	add r0, #0x10
	lsl r4, r3, #0x2
	str r0, [sp, #0x8]
	ldr r0, [r0, r4]
	add r7, r2, #0x0
	str r1, [sp, #0x0]
	cmp r0, #0x0
	beq _0200E64A
	bl GF_AssertFail
_0200E64A:
	add r6, r5, #0x0
	add r6, #0x8
	ldr r0, [r6, r4]
	cmp r0, #0x0
	bne _0200E658
	bl GF_AssertFail
_0200E658:
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	bne _0200E672
	ldr r0, [r5, #0x14]
	cmp r0, #0x0
	bne _0200E672
	ldr r0, _0200E698 ; =FUN_0200E610
	add r1, r5, #0x0
	bl Main_SetHBlankIntrCB
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4]
_0200E672:
	ldr r0, [sp, #0x4]
	cmp r0, #0x1
	beq _0200E67C
	bl GF_AssertFail
_0200E67C:
	ldr r0, [sp, #0x0]
	cmp r7, #0x0
	str r0, [r5, r4]
	beq _0200E688
	str r7, [r6, r4]
	b _0200E68C
_0200E688:
	ldr r0, _0200E69C ; =FUN_0200E758
	str r0, [r6, r4]
_0200E68C:
	ldr r0, [sp, #0x8]
	mov r1, #0x1
	str r1, [r0, r4]
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_0200E698: .word FUN_0200E610
_0200E69C: .word FUN_0200E758

	thumb_func_start FUN_0200E6A0
FUN_0200E6A0: ; 0x0200E6A0
	push {r3-r5, lr}
	lsl r4, r1, #0x2
	add r5, r0, #0x0
	mov r1, #0x0
	add r0, r5, r4
	str r1, [r0, #0x10]
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	bne _0200E6BC
	ldr r0, [r5, #0x14]
	cmp r0, #0x0
	bne _0200E6BC
	bl FUN_02015F1C
_0200E6BC:
	ldr r1, _0200E6C8 ; =FUN_0200E758
	add r0, r5, r4
	str r1, [r0, #0x8]
	mov r0, #0x0
	str r0, [r5, r4]
	pop {r3-r5, pc}
	.balign 4
_0200E6C8: .word FUN_0200E758

	thumb_func_start FUN_0200E6CC
FUN_0200E6CC: ; 0x0200E6CC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r0, [sp, #0x18]
	mov r1, #0x10
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl AllocFromHeapAtEnd
	add r1, r0, #0x0
	str r5, [r1, #0x0]
	str r4, [r1, #0x4]
	mov r2, #0x1
	str r6, [r1, #0x8]
	ldr r0, _0200E6F4 ; =FUN_0200E71C
	lsl r2, r2, #0xa
	str r7, [r1, #0xc]
	bl FUN_0200CA98
	pop {r3-r7, pc}
	.balign 4
_0200E6F4: .word FUN_0200E71C

	thumb_func_start FUN_0200E6F8
FUN_0200E6F8: ; 0x0200E6F8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x8
	bl AllocFromHeapAtEnd
	add r1, r0, #0x0
	mov r2, #0x1
	str r5, [r1, #0x0]
	ldr r0, _0200E718 ; =FUN_0200E73C
	lsl r2, r2, #0xa
	str r4, [r1, #0x4]
	bl FUN_0200CA98
	pop {r3-r5, pc}
	.balign 4
_0200E718: .word FUN_0200E73C

	thumb_func_start FUN_0200E71C
FUN_0200E71C: ; 0x0200E71C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	ldr r3, [r4, #0xc]
	bl FUN_0200E628
	add r0, r5, #0x0
	bl FUN_0200CAB4
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r3-r5, pc}

	thumb_func_start FUN_0200E73C
FUN_0200E73C: ; 0x0200E73C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	bl FUN_0200E6A0
	add r0, r5, #0x0
	bl FUN_0200CAB4
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r3-r5, pc}

	thumb_func_start FUN_0200E758
FUN_0200E758: ; 0x0200E758
	bx lr
	.balign 4

	thumb_func_start FUN_0200E75C
FUN_0200E75C: ; 0x0200E75C
	ldr r2, _0200E76C ; =0x0000FFFF
	cmp r1, r2
	bne _0200E768
	mov r1, #0x15
	lsl r1, r1, #0x4
	ldrh r1, [r0, r1]
_0200E768:
	add r0, r1, #0x0
	bx lr
	.balign 4
_0200E76C: .word 0x0000FFFF

	thumb_func_start FUN_0200E770
FUN_0200E770: ; 0x0200E770
	ldr r1, [r0, #0xc]
	cmp r1, #0x1
	bne _0200E77C
	add r2, r0, #0x0
	add r2, #0x14
	b _0200E780
_0200E77C:
	add r2, r0, #0x0
	add r2, #0x44
_0200E780:
	ldr r1, [r2, #0x28]
	cmp r1, #0x1
	bne _0200E78A
	ldrh r0, [r2, #0x24]
	bx lr
_0200E78A:
	mov r1, #0x15
	lsl r1, r1, #0x4
	ldrh r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start FUN_0200E794
FUN_0200E794: ; 0x0200E794
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r1, #0x10]
	mov r1, #0x0
	bl FUN_0200E440
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start FUN_0200E7A8
FUN_0200E7A8: ; 0x0200E7A8
	push {r3, lr}
	add r1, r0, #0x0
	ldr r0, [r1, #0x28]
	cmp r0, #0x0
	bne _0200E7CE
	ldrh r2, [r1, #0x24]
	ldr r0, _0200E7D0 ; =0x00007FFF
	cmp r2, r0
	beq _0200E7BE
	cmp r2, #0x0
	bne _0200E7CE
_0200E7BE:
	ldr r0, [r1, #0x2c]
	cmp r0, #0x0
	bne _0200E7CE
	mov r2, #0x1
	ldr r0, _0200E7D4 ; =FUN_0200E794
	lsl r2, r2, #0xa
	bl FUN_0200CA98
_0200E7CE:
	pop {r3, pc}
	.balign 4
_0200E7D0: .word 0x00007FFF
_0200E7D4: .word FUN_0200E794

	thumb_func_start FUN_0200E7D8
FUN_0200E7D8: ; 0x0200E7D8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x28]
	cmp r0, #0x1
	bne _0200E800
	ldrh r1, [r4, #0x24]
	ldr r0, _0200E804 ; =0x00007FFF
	cmp r1, r0
	beq _0200E7EE
	cmp r1, #0x0
	bne _0200E800
_0200E7EE:
	ldr r0, [r4, #0x2c]
	cmp r0, #0x0
	bne _0200E800
	ldr r0, [r4, #0x10]
	bl FUN_0200E3A0
	ldr r0, [r4, #0x10]
	bl FUN_0200E388
_0200E800:
	pop {r4, pc}
	nop
_0200E804: .word 0x00007FFF

	thumb_func_start FUN_0200E808
FUN_0200E808: ; 0x0200E808
	push {r4, lr}
	add r4, r0, #0x0
	add r2, r4, #0x0
	mov r1, #0x14
	mov r0, #0x0
_0200E812:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _0200E812
	add r0, r4, #0x0
	add r0, #0x14
	mov r1, #0x0
	mov r2, #0x30
	bl memset
	add r0, r4, #0x0
	add r0, #0x44
	mov r1, #0x0
	mov r2, #0x30
	bl memset
	add r2, r4, #0x0
	add r2, #0x74
	mov r1, #0x18
	mov r0, #0x0
_0200E83A:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _0200E83A
	add r4, #0x8c
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0xc0
	bl memset
	pop {r4, pc}
