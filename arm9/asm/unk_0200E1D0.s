    .include "asm/macros.inc"
    .include "global.inc"

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
	bl ErrorHandling
_0200E1E6:
	ldr r0, [sp, #0x34]
	cmp r0, #0x0
	bne _0200E1F0
	bl ErrorHandling
_0200E1F0:
	ldr r0, _0200E2AC ; =0x021C47F4
	ldrh r0, [r0, #0xc]
	cmp r0, #0x0
	beq _0200E1FC
	bl ErrorHandling
_0200E1FC:
	ldr r0, _0200E2B0 ; =0x021C46B4
	bl FUN_0200E808
	ldr r1, _0200E2B0 ; =0x021C46B4
	add r0, r5, #0x0
	bl FUN_0200E558
	ldr r0, _0200E2B4 ; =0x021C4728
	bl FUN_0200E5F4
	ldr r0, _0200E2B0 ; =0x021C46B4
	add r1, r6, #0x0
	bl FUN_0200E75C
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, _0200E2B8 ; =0x021C4740
	ldr r2, [sp, #0x30]
	str r0, [sp, #0xc]
	ldr r0, _0200E2B4 ; =0x021C4728
	ldr r3, [sp, #0x34]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x38]
	add r1, r4, #0x0
	str r0, [sp, #0x14]
	ldr r0, _0200E2BC ; =0x021C46C8
	str r5, [sp, #0x18]
	bl FUN_0200E5C8
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	ldr r0, _0200E2B8 ; =0x021C4740
	ldr r2, [sp, #0x30]
	str r0, [sp, #0xc]
	ldr r0, _0200E2B4 ; =0x021C4728
	ldr r3, [sp, #0x34]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x38]
	add r1, r7, #0x0
	str r0, [sp, #0x14]
	ldr r0, _0200E2C0 ; =0x021C46F8
	str r5, [sp, #0x18]
	bl FUN_0200E5C8
	ldr r0, _0200E2AC ; =0x021C47F4
	mov r1, #0x1
	strh r1, [r0, #0xc]
	ldr r0, _0200E2C4 ; =0x021C46B8
	ldr r1, _0200E2BC ; =0x021C46C8
	bl FUN_0200E528
	ldr r0, _0200E2C8 ; =0x021C46BC
	ldr r1, _0200E2C0 ; =0x021C46F8
	bl FUN_0200E528
	ldr r0, _0200E2CC ; =0x021C46B4
	ldr r0, [r0, #0xc]
	cmp r0, #0x0
	beq _0200E28E
	ldr r0, _0200E2B0 ; =0x021C46B4
	add r0, #0x14
	bl FUN_0200E7A8
	ldr r1, _0200E2D0 ; =0x0000014E
	ldr r0, _0200E2B0 ; =0x021C46B4
	mov r2, #0x1
	strb r2, [r0, r1]
_0200E28E:
	ldr r0, _0200E2B0 ; =0x021C46B4
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	beq _0200E2A6
	ldr r0, _0200E2B0 ; =0x021C46B4
	add r0, #0x44
	bl FUN_0200E7A8
	ldr r1, _0200E2D4 ; =0x0000014F
	ldr r0, _0200E2B0 ; =0x021C46B4
	mov r2, #0x1
	strb r2, [r0, r1]
_0200E2A6:
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_0200E2AC: .word 0x021C47F4
_0200E2B0: .word 0x021C46B4
_0200E2B4: .word 0x021C4728
_0200E2B8: .word 0x021C4740
_0200E2BC: .word 0x021C46C8
_0200E2C0: .word 0x021C46F8
_0200E2C4: .word 0x021C46B8
_0200E2C8: .word 0x021C46BC
_0200E2CC: .word 0x021C46B4
_0200E2D0: .word 0x0000014E
_0200E2D4: .word 0x0000014F

	thumb_func_start FUN_0200E2D8
FUN_0200E2D8: ; 0x0200E2D8
	push {r4, lr}
	ldr r0, _0200E300 ; =0x021C47F4
	ldr r4, _0200E304 ; =0x021C46B4
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
_0200E300: .word 0x021C47F4
_0200E304: .word 0x021C46B4

	thumb_func_start FUN_0200E308
FUN_0200E308: ; 0x0200E308
	ldr r0, _0200E318 ; =0x021C47F4
	ldrh r0, [r0, #0xc]
	cmp r0, #0x0
	bne _0200E314
	mov r0, #0x1
	bx lr
_0200E314:
	mov r0, #0x0
	bx lr
	.balign 4
_0200E318: .word 0x021C47F4

	thumb_func_start FUN_0200E31C
FUN_0200E31C: ; 0x0200E31C
	push {r3, lr}
	ldr r0, _0200E368 ; =0x021C4728
	mov r1, #0x0
	bl FUN_0200E6A0
	ldr r0, _0200E368 ; =0x021C4728
	mov r1, #0x1
	bl FUN_0200E6A0
	ldr r0, _0200E36C ; =0x021C46B4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0200E33A
	mov r1, #0x2
	str r1, [r0, #0x20]
_0200E33A:
	ldr r0, _0200E36C ; =0x021C46B4
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	beq _0200E346
	mov r1, #0x2
	str r1, [r0, #0x50]
_0200E346:
	ldr r0, _0200E370 ; =0x021C46B8
	ldr r1, _0200E374 ; =0x021C46C8
	bl FUN_0200E528
	ldr r0, _0200E378 ; =0x021C46BC
	ldr r1, _0200E37C ; =0x021C46F8
	bl FUN_0200E528
	ldr r0, _0200E380 ; =0x021C47F4
	mov r1, #0x0
	strh r1, [r0, #0xc]
	strb r1, [r0, #0xe]
	strb r1, [r0, #0xf]
	ldr r0, _0200E384 ; =0x021C46B4
	bl FUN_0200E808
	pop {r3, pc}
	.balign 4
_0200E368: .word 0x021C4728
_0200E36C: .word 0x021C46B4
_0200E370: .word 0x021C46B8
_0200E374: .word 0x021C46C8
_0200E378: .word 0x021C46BC
_0200E37C: .word 0x021C46F8
_0200E380: .word 0x021C47F4
_0200E384: .word 0x021C46B4

	thumb_func_start FUN_0200E388
FUN_0200E388: ; 0x0200E388
	ldr r3, _0200E390 ; =FUN_02011480
	add r1, r0, #0x0
	mov r0, #0x0
	bx r3
	.balign 4
_0200E390: .word FUN_02011480

	thumb_func_start FUN_0200E394
FUN_0200E394: ; 0x0200E394
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
	ldr r0, _0200E41C ; =0x021C4740
	mov r1, #0x1
	add r2, r4, #0x0
	bl FUN_02011634
	mov r2, #0x0
	ldr r0, _0200E41C ; =0x021C4740
	mov r1, #0x3f
	add r3, r2, #0x0
	str r4, [sp, #0x0]
	bl FUN_02011650
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r0, _0200E41C ; =0x021C4740
	add r2, r1, #0x0
	add r3, r1, #0x0
	str r4, [sp, #0x8]
	bl FUN_02011698
	ldr r0, _0200E41C ; =0x021C4740
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
_0200E41C: .word 0x021C4740

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
	ldr r0, _0200E4B4 ; =0x021C47F4
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
	ldr r0, _0200E4B4 ; =0x021C47F4
	mov r1, #0x0
	strb r1, [r0, #0xf]
_0200E4AA:
	add r0, r4, #0x0
	bl FUN_0200E808
	pop {r4, pc}
	nop
_0200E4B4: .word 0x021C47F4

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
	ldr r1, _0200E554 ; =0x020ECEF4
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_0200E554: .word 0x020ECEF4

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
	bl ErrorHandling
_0200E64A:
	add r6, r5, #0x0
	add r6, #0x8
	ldr r0, [r6, r4]
	cmp r0, #0x0
	bne _0200E658
	bl ErrorHandling
_0200E658:
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	bne _0200E672
	ldr r0, [r5, #0x14]
	cmp r0, #0x0
	bne _0200E672
	ldr r0, _0200E698 ; =FUN_0200E610
	add r1, r5, #0x0
	bl FUN_02015F34
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4]
_0200E672:
	ldr r0, [sp, #0x4]
	cmp r0, #0x1
	beq _0200E67C
	bl ErrorHandling
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
	bl FUN_020169D8
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
	bl FUN_020169D8
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
	bl FUN_02016A18
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
	bl FUN_02016A18
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
	bl Call_FillMemWithValue
	add r0, r4, #0x0
	add r0, #0x44
	mov r1, #0x0
	mov r2, #0x30
	bl Call_FillMemWithValue
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
	bl Call_FillMemWithValue
	pop {r4, pc}

	thumb_func_start FUN_0200E850
FUN_0200E850: ; 0x0200E850
	push {r3, lr}
	ldr r1, [r0, #0xc]
	cmp r1, #0x0
	bne _0200E866
	mov r1, #0x1
	str r1, [r0, #0x28]
	str r1, [r0, #0x2c]
	bl FUN_0200F20C
	mov r0, #0x0
	pop {r3, pc}
_0200E866:
	bl FUN_0200F2AC
	pop {r3, pc}

	thumb_func_start FUN_0200E86C
FUN_0200E86C: ; 0x0200E86C
	push {r3, lr}
	ldr r1, [r0, #0xc]
	cmp r1, #0x0
	bne _0200E884
	mov r1, #0x0
	str r1, [r0, #0x28]
	mov r2, #0x1
	str r2, [r0, #0x2c]
	bl FUN_0200F20C
	mov r0, #0x0
	pop {r3, pc}
_0200E884:
	bl FUN_0200F2AC
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0200E88C
FUN_0200E88C: ; 0x0200E88C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E8B4
	ldr r1, _0200E8BC ; =0x020ECF9F
	ldr r0, _0200E8C0 ; =0x02105AF8
	str r1, [r0, #0x30]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E8C4 ; =0x02105B28
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E8B4:
	bl FUN_02010F70
	pop {r4, pc}
	nop
_0200E8BC: .word 0x020ECF9F
_0200E8C0: .word 0x02105AF8
_0200E8C4: .word 0x02105B28

	thumb_func_start FUN_0200E8C8
FUN_0200E8C8: ; 0x0200E8C8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E8EE
	ldr r1, _0200E8F4 ; =0x020ECF9C
	ldr r0, _0200E8F8 ; =0x02105AF8
	str r1, [r0, #0x40]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E8FC ; =0x02105B38
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E8EE:
	bl FUN_02010F70
	pop {r4, pc}
	.balign 4
_0200E8F4: .word 0x020ECF9C
_0200E8F8: .word 0x02105AF8
_0200E8FC: .word 0x02105B38

	thumb_func_start FUN_0200E900
FUN_0200E900: ; 0x0200E900
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E928
	ldr r1, _0200E930 ; =0x020ECFA5
	ldr r0, _0200E934 ; =0x02105AF8
	str r1, [r0, #0x48]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E938 ; =0x02105B40
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E928:
	bl FUN_02010F70
	pop {r4, pc}
	nop
_0200E930: .word 0x020ECFA5
_0200E934: .word 0x02105AF8
_0200E938: .word 0x02105B40

	thumb_func_start FUN_0200E93C
FUN_0200E93C: ; 0x0200E93C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E962
	ldr r1, _0200E968 ; =0x020ECFA2
	ldr r0, _0200E96C ; =0x02105AF8
	str r1, [r0, #0x38]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E970 ; =0x02105B30
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E962:
	bl FUN_02010F70
	pop {r4, pc}
	.balign 4
_0200E968: .word 0x020ECFA2
_0200E96C: .word 0x02105AF8
_0200E970: .word 0x02105B30

	thumb_func_start FUN_0200E974
FUN_0200E974: ; 0x0200E974
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E996
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E99C ; =0x020ED0E8
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E996:
	bl FUN_0200FD1C
	pop {r4, pc}
	.balign 4
_0200E99C: .word 0x020ED0E8

	thumb_func_start FUN_0200E9A0
FUN_0200E9A0: ; 0x0200E9A0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E9C0
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E9C8 ; =0x020ED154
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E9C0:
	bl FUN_0200FD1C
	pop {r4, pc}
	nop
_0200E9C8: .word 0x020ED154

	thumb_func_start FUN_0200E9CC
FUN_0200E9CC: ; 0x0200E9CC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E9F4
	ldr r1, _0200E9FC ; =0x020ECFC0
	ldr r0, _0200EA00 ; =0x02105AF8
	str r1, [r0, #0x20]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EA04 ; =0x02105B18
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E9F4:
	bl FUN_02010F70
	pop {r4, pc}
	nop
_0200E9FC: .word 0x020ECFC0
_0200EA00: .word 0x02105AF8
_0200EA04: .word 0x02105B18

	thumb_func_start FUN_0200EA08
FUN_0200EA08: ; 0x0200EA08
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EA2E
	ldr r1, _0200EA34 ; =0x020ECFC6
	ldr r0, _0200EA38 ; =0x02105AF8
	str r1, [r0, #0x28]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EA3C ; =0x02105B20
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EA2E:
	bl FUN_02010F70
	pop {r4, pc}
	.balign 4
_0200EA34: .word 0x020ECFC6
_0200EA38: .word 0x02105AF8
_0200EA3C: .word 0x02105B20

	thumb_func_start FUN_0200EA40
FUN_0200EA40: ; 0x0200EA40
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EA68
	ldr r1, _0200EA70 ; =0x020ECFA8
	ldr r0, _0200EA74 ; =0x02105AF8
	str r1, [r0, #0x10]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EA78 ; =0x02105B08
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EA68:
	bl FUN_02010F70
	pop {r4, pc}
	nop
_0200EA70: .word 0x020ECFA8
_0200EA74: .word 0x02105AF8
_0200EA78: .word 0x02105B08

	thumb_func_start FUN_0200EA7C
FUN_0200EA7C: ; 0x0200EA7C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EAA2
	ldr r1, _0200EAA8 ; =0x020ECFB4
	ldr r0, _0200EAAC ; =0x02105AF8
	str r1, [r0, #0x18]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EAB0 ; =0x02105B10
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EAA2:
	bl FUN_02010F70
	pop {r4, pc}
	.balign 4
_0200EAA8: .word 0x020ECFB4
_0200EAAC: .word 0x02105AF8
_0200EAB0: .word 0x02105B10

	thumb_func_start FUN_0200EAB4
FUN_0200EAB4: ; 0x0200EAB4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EAD6
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EADC ; =0x020ED1C0
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EAD6:
	bl FUN_0200FD1C
	pop {r4, pc}
	.balign 4
_0200EADC: .word 0x020ED1C0

	thumb_func_start FUN_0200EAE0
FUN_0200EAE0: ; 0x0200EAE0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EB00
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EB08 ; =0x020ED1E4
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EB00:
	bl FUN_0200FD1C
	pop {r4, pc}
	nop
_0200EB08: .word 0x020ED1E4

	thumb_func_start FUN_0200EB0C
FUN_0200EB0C: ; 0x0200EB0C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EB30
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EB38 ; =0x020ED208
	ldr r2, _0200EB3C ; =0x020ED22C
	add r0, r4, #0x0
	bl FUN_0200FD6C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EB30:
	bl FUN_0200FDC4
	pop {r4, pc}
	nop
_0200EB38: .word 0x020ED208
_0200EB3C: .word 0x020ED22C

	thumb_func_start FUN_0200EB40
FUN_0200EB40: ; 0x0200EB40
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EB62
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EB68 ; =0x020ED250
	ldr r2, _0200EB6C ; =0x020ED274
	add r0, r4, #0x0
	bl FUN_0200FD6C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EB62:
	bl FUN_0200FDC4
	pop {r4, pc}
	.balign 4
_0200EB68: .word 0x020ED250
_0200EB6C: .word 0x020ED274

	thumb_func_start FUN_0200EB70
FUN_0200EB70: ; 0x0200EB70
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EB92
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EB98 ; =0x020ED090
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EB92:
	bl FUN_0200FF50
	pop {r4, pc}
	.balign 4
_0200EB98: .word 0x020ED090

	thumb_func_start FUN_0200EB9C
FUN_0200EB9C: ; 0x0200EB9C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EBBC
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EBC4 ; =0x020ED040
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EBBC:
	bl FUN_0200FF50
	pop {r4, pc}
	nop
_0200EBC4: .word 0x020ED040

	thumb_func_start FUN_0200EBC8
FUN_0200EBC8: ; 0x0200EBC8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EBEA
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EBF0 ; =0x020ED050
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EBEA:
	bl FUN_0200FF50
	pop {r4, pc}
	.balign 4
_0200EBF0: .word 0x020ED050

	thumb_func_start FUN_0200EBF4
FUN_0200EBF4: ; 0x0200EBF4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EC14
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EC1C ; =0x020ED060
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EC14:
	bl FUN_0200FF50
	pop {r4, pc}
	nop
_0200EC1C: .word 0x020ED060

	thumb_func_start FUN_0200EC20
FUN_0200EC20: ; 0x0200EC20
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EC42
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EC48 ; =0x020ECFE0
	add r0, r4, #0x0
	bl FUN_020101EC
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EC42:
	bl FUN_02010224
	pop {r4, pc}
	.balign 4
_0200EC48: .word 0x020ECFE0

	thumb_func_start FUN_0200EC4C
FUN_0200EC4C: ; 0x0200EC4C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EC6C
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EC74 ; =0x020ECFEC
	add r0, r4, #0x0
	bl FUN_020101EC
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EC6C:
	bl FUN_02010224
	pop {r4, pc}
	nop
_0200EC74: .word 0x020ECFEC

	thumb_func_start FUN_0200EC78
FUN_0200EC78: ; 0x0200EC78
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EC9A
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ECA0 ; =0x020ED0A0
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EC9A:
	bl FUN_0200FD1C
	pop {r4, pc}
	.balign 4
_0200ECA0: .word 0x020ED0A0

	thumb_func_start FUN_0200ECA4
FUN_0200ECA4: ; 0x0200ECA4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200ECC4
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ECCC ; =0x020ED0C4
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200ECC4:
	bl FUN_0200FD1C
	pop {r4, pc}
	nop
_0200ECCC: .word 0x020ED0C4

	thumb_func_start FUN_0200ECD0
FUN_0200ECD0: ; 0x0200ECD0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200ECF2
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ECF8 ; =0x020ED10C
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200ECF2:
	bl FUN_0200FD1C
	pop {r4, pc}
	.balign 4
_0200ECF8: .word 0x020ED10C

	thumb_func_start FUN_0200ECFC
FUN_0200ECFC: ; 0x0200ECFC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200ED1C
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ED24 ; =0x020ED178
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200ED1C:
	bl FUN_0200FD1C
	pop {r4, pc}
	nop
_0200ED24: .word 0x020ED178

	thumb_func_start FUN_0200ED28
FUN_0200ED28: ; 0x0200ED28
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200ED4A
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ED50 ; =0x020ED004
	add r0, r4, #0x0
	bl FUN_020103F0
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200ED4A:
	bl FUN_02010428
	pop {r4, pc}
	.balign 4
_0200ED50: .word 0x020ED004

	thumb_func_start FUN_0200ED54
FUN_0200ED54: ; 0x0200ED54
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200ED74
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ED7C ; =0x020ED010
	add r0, r4, #0x0
	bl FUN_020103F0
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200ED74:
	bl FUN_02010428
	pop {r4, pc}
	nop
_0200ED7C: .word 0x020ED010

	thumb_func_start FUN_0200ED80
FUN_0200ED80: ; 0x0200ED80
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EDC4
	ldr r0, _0200EDCC ; =0x020ED298
	mov r1, #0x4
	str r0, [sp, #0x0]
	ldr r0, _0200EDD0 ; =0x020ED2D8
	str r0, [sp, #0x4]
	add r0, sp, #0x0
	strb r1, [r0, #0x8]
	mov r1, #0x0
	strb r1, [r0, #0x9]
	mov r1, #0x3f
	strb r1, [r0, #0xa]
	mov r1, #0x20
	strb r1, [r0, #0xb]
	mov r1, #0x1
	strb r1, [r0, #0xc]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010688
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	add sp, #0x10
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EDC4:
	bl FUN_020106C0
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_0200EDCC: .word 0x020ED298
_0200EDD0: .word 0x020ED2D8

	thumb_func_start FUN_0200EDD4
FUN_0200EDD4: ; 0x0200EDD4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EE14
	ldr r0, _0200EE1C ; =0x020ED318
	mov r1, #0x4
	str r0, [sp, #0x0]
	ldr r0, _0200EE20 ; =0x020ED358
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x0
	strb r1, [r0, #0x8]
	strb r2, [r0, #0x9]
	mov r1, #0x3f
	strb r1, [r0, #0xa]
	mov r1, #0x20
	strb r1, [r0, #0xb]
	strb r2, [r0, #0xc]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010688
	mov r0, #0x0
	str r0, [r4, #0x28]
	add sp, #0x10
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EE14:
	bl FUN_020106C0
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_0200EE1C: .word 0x020ED318
_0200EE20: .word 0x020ED358

	thumb_func_start FUN_0200EE24
FUN_0200EE24: ; 0x0200EE24
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EE4C
	ldr r1, _0200EE54 ; =0x020ECFD5
	ldr r0, _0200EE58 ; =0x02105AF8
	str r1, [r0, #0x0]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EE5C ; =0x02105AF8
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EE4C:
	bl FUN_02010F70
	pop {r4, pc}
	nop
_0200EE54: .word 0x020ECFD5
_0200EE58: .word 0x02105AF8
_0200EE5C: .word 0x02105AF8

	thumb_func_start FUN_0200EE60
FUN_0200EE60: ; 0x0200EE60
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EE86
	ldr r1, _0200EE8C ; =0x020ECFCC
	ldr r0, _0200EE90 ; =0x02105AF8
	str r1, [r0, #0x8]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EE94 ; =0x02105B00
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EE86:
	bl FUN_02010F70
	pop {r4, pc}
	.balign 4
_0200EE8C: .word 0x020ECFCC
_0200EE90: .word 0x02105AF8
_0200EE94: .word 0x02105B00

	thumb_func_start FUN_0200EE98
FUN_0200EE98: ; 0x0200EE98
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EECA
	ldr r3, _0200EED4 ; =0x020ECFF8
	add r2, sp, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010948
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	add sp, #0xc
	str r0, [r4, #0x2c]
	pop {r3-r4, pc}
_0200EECA:
	bl FUN_02010988
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_0200EED4: .word 0x020ECFF8

	thumb_func_start FUN_0200EED8
FUN_0200EED8: ; 0x0200EED8
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EF08
	ldr r3, _0200EF10 ; =0x020ED034
	add r2, sp, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010948
	mov r0, #0x0
	str r0, [r4, #0x28]
	add sp, #0xc
	str r0, [r4, #0x2c]
	pop {r3-r4, pc}
_0200EF08:
	bl FUN_02010988
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4
_0200EF10: .word 0x020ED034

	thumb_func_start FUN_0200EF14
FUN_0200EF14: ; 0x0200EF14
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EF46
	ldr r3, _0200EF50 ; =0x020ED01C
	add r2, sp, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010C7C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	add sp, #0xc
	str r0, [r4, #0x2c]
	pop {r3-r4, pc}
_0200EF46:
	bl FUN_02010CBC
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_0200EF50: .word 0x020ED01C

	thumb_func_start FUN_0200EF54
FUN_0200EF54: ; 0x0200EF54
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EF84
	ldr r3, _0200EF8C ; =0x020ED028
	add r2, sp, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010C7C
	mov r0, #0x0
	str r0, [r4, #0x28]
	add sp, #0xc
	str r0, [r4, #0x2c]
	pop {r3-r4, pc}
_0200EF84:
	bl FUN_02010CBC
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4
_0200EF8C: .word 0x020ED028

	thumb_func_start FUN_0200EF90
FUN_0200EF90: ; 0x0200EF90
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EFB2
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EFB8 ; =0x020ED080
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EFB2:
	bl FUN_0200FF50
	pop {r4, pc}
	.balign 4
_0200EFB8: .word 0x020ED080

	thumb_func_start FUN_0200EFBC
FUN_0200EFBC: ; 0x0200EFBC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EFDC
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EFE4 ; =0x020ED070
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EFDC:
	bl FUN_0200FF50
	pop {r4, pc}
	nop
_0200EFE4: .word 0x020ED070

	thumb_func_start FUN_0200EFE8
FUN_0200EFE8: ; 0x0200EFE8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200F00A
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200F010 ; =0x020ED130
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200F00A:
	bl FUN_0200FD1C
	pop {r4, pc}
	.balign 4
_0200F010: .word 0x020ED130

	thumb_func_start FUN_0200F014
FUN_0200F014: ; 0x0200F014
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200F034
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200F03C ; =0x020ED19C
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200F034:
	bl FUN_0200FD1C
	pop {r4, pc}
	nop
_0200F03C: .word 0x020ED19C

	thumb_func_start FUN_0200F040
FUN_0200F040: ; 0x0200F040
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200F068
	ldr r1, _0200F070 ; =0x020ECFAE
	ldr r0, _0200F074 ; =0x02105AF8
	str r1, [r0, #0x74]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200F078 ; =0x02105B48
	add r0, r4, #0x0
	bl FUN_020111AC
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200F068:
	bl FUN_02011214
	pop {r4, pc}
	nop
_0200F070: .word 0x020ECFAE
_0200F074: .word 0x02105AF8
_0200F078: .word 0x02105B48

	thumb_func_start FUN_0200F07C
FUN_0200F07C: ; 0x0200F07C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200F0A2
	ldr r1, _0200F0A8 ; =0x020ECFBA
	ldr r0, _0200F0AC ; =0x02105B78
	str r1, [r0, #0x24]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200F0B0 ; =0x02105B78
	add r0, r4, #0x0
	bl FUN_020111AC
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200F0A2:
	bl FUN_02011214
	pop {r4, pc}
	.balign 4
_0200F0A8: .word 0x020ECFBA
_0200F0AC: .word 0x02105B78
_0200F0B0: .word 0x02105B78

	thumb_func_start FUN_0200F0B4
FUN_0200F0B4: ; 0x0200F0B4
	asr r0, r0, #0x4
	lsl r1, r0, #0x1
	lsl r0, r1, #0x1
	ldr r2, _0200F0C8 ; =0x020FFA38
	add r1, r1, #0x1
	lsl r1, r1, #0x1
	ldr r3, _0200F0CC ; =FX_Div
	ldrsh r0, [r2, r0]
	ldrsh r1, [r2, r1]
	bx r3
	.balign 4
_0200F0C8: .word 0x020FFA38
_0200F0CC: .word FX_Div

	thumb_func_start FUN_0200F0D0
FUN_0200F0D0: ; 0x0200F0D0
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0200F0B4
	lsl r2, r4, #0xc
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	asr r0, r1, #0xc
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200F0F8
FUN_0200F0F8: ; 0x0200F0F8
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	bl FUN_0200F0B4
	cmp r6, r7
	bge _0200F142
	lsl r1, r6, #0x2
	str r0, [sp, #0x0]
	asr r0, r0, #0x1f
	lsl r4, r6, #0xc
	add r5, r5, r1
	str r0, [sp, #0x4]
_0200F116:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	asr r3, r4, #0x1f
	add r2, r4, #0x0
	bl _ll_mul
	mov r2, #0x2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _0200F148 ; =0x00000000
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r0, r0, #0xc
	stmia r5!, {r0}
	mov r0, #0x1
	lsl r0, r0, #0xc
	add r6, r6, #0x1
	add r4, r4, r0
	cmp r6, r7
	blt _0200F116
_0200F142:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0200F148: .word 0x00000000

	thumb_func_start FUN_0200F14C
FUN_0200F14C: ; 0x0200F14C
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0200F0B4
	add r1, r0, #0x0
	lsr r0, r4, #0x1f
	add r0, r4, r0
	asr r0, r0, #0x1
	lsl r0, r0, #0xc
	bl FX_Div
	pop {r4, pc}

	thumb_func_start FUN_0200F164
FUN_0200F164: ; 0x0200F164
	ldr r3, _0200F170 ; =_s32_div_f
	sub r0, r1, r0
	lsl r0, r0, #0x7
	add r1, r2, #0x0
	bx r3
	nop
_0200F170: .word _s32_div_f

	thumb_func_start FUN_0200F174
FUN_0200F174: ; 0x0200F174
	add r0, r0, r1
	bpl _0200F17A
	mov r0, #0x0
_0200F17A:
	cmp r0, #0xff
	ble _0200F180
	mov r0, #0xff
_0200F180:
	bx lr
	.balign 4

	thumb_func_start FUN_0200F184
FUN_0200F184: ; 0x0200F184
	ldr r3, [r0, #0x0]
	ldr r2, [r1, #0x0]
	add r2, r3, r2
	str r2, [r0, #0x0]
	ldr r3, [r0, #0x4]
	ldr r2, [r1, #0x4]
	add r2, r3, r2
	str r2, [r0, #0x4]
	ldr r3, [r0, #0x8]
	ldr r2, [r1, #0x8]
	add r2, r3, r2
	str r2, [r0, #0x8]
	ldr r2, [r0, #0xc]
	ldr r1, [r1, #0xc]
	add r1, r2, r1
	str r1, [r0, #0xc]
	bx lr
	.balign 4

	thumb_func_start FUN_0200F1A8
FUN_0200F1A8: ; 0x0200F1A8
	push {r3-r7, lr}
	add r7, r1, #0x0
	ldr r1, [sp, #0x1c]
	add r5, r3, #0x0
	str r1, [sp, #0x1c]
	ldr r1, [r5, #0x0]
	ldr r4, [sp, #0x18]
	lsl r1, r1, #0x7
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x4]
	add r6, r2, #0x0
	lsl r1, r1, #0x7
	str r1, [r0, #0x4]
	ldr r1, [r5, #0x8]
	add r2, r4, #0x0
	lsl r1, r1, #0x7
	str r1, [r0, #0x8]
	ldr r1, [r5, #0xc]
	lsl r1, r1, #0x7
	str r1, [r0, #0xc]
	ldmia r2!, {r0-r1}
	stmia r7!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r7!, {r0-r1}
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	ldr r2, [sp, #0x1c]
	bl FUN_0200F164
	str r0, [r6, #0x0]
	ldr r0, [r5, #0x4]
	ldr r1, [r4, #0x4]
	ldr r2, [sp, #0x1c]
	bl FUN_0200F164
	str r0, [r6, #0x4]
	ldr r0, [r5, #0x8]
	ldr r1, [r4, #0x8]
	ldr r2, [sp, #0x1c]
	bl FUN_0200F164
	str r0, [r6, #0x8]
	ldr r0, [r5, #0xc]
	ldr r1, [r4, #0xc]
	ldr r2, [sp, #0x1c]
	bl FUN_0200F164
	str r0, [r6, #0xc]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200F20C
FUN_0200F20C: ; 0x0200F20C
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r6, r1, #0x0
	mov r1, #0x1c
	bl FUN_02016998
	str r0, [r5, #0x14]
	mov r2, #0x1c
	mov r1, #0x0
_0200F220:
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _0200F220
	ldr r4, [r5, #0x14]
	cmp r6, #0x0
	ldrh r1, [r5, #0x24]
	ldr r0, _0200F2A8 ; =0x00007FFF
	bne _0200F254
	cmp r1, r0
	bne _0200F23C
	mov r7, #0x10
	mov r6, #0x0
	b _0200F274
_0200F23C:
	cmp r1, #0x0
	bne _0200F248
	mov r7, #0xf
	mvn r7, r7
	mov r6, #0x0
	b _0200F274
_0200F248:
	mov r7, #0xf
	mvn r7, r7
	mov r6, #0x0
	bl ErrorHandling
	b _0200F274
_0200F254:
	cmp r1, r0
	bne _0200F25E
	mov r7, #0x0
	mov r6, #0x10
	b _0200F274
_0200F25E:
	cmp r1, #0x0
	bne _0200F26A
	mov r7, #0x0
	add r6, r7, #0x0
	sub r6, #0x10
	b _0200F274
_0200F26A:
	mov r7, #0x0
	add r6, r7, #0x0
	sub r6, #0x10
	bl ErrorHandling
_0200F274:
	ldr r0, [r5, #0x10]
	add r1, r7, #0x0
	bl FUN_0200E440
	ldr r0, [r5, #0x4]
	add r1, r6, #0x0
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x8]
	str r0, [r4, #0x4]
	mov r0, #0x0
	str r0, [r4, #0x8]
	lsl r0, r7, #0x7
	str r0, [r4, #0xc]
	lsl r0, r6, #0x7
	str r0, [r4, #0x10]
	ldr r2, [r5, #0x4]
	add r0, r7, #0x0
	bl FUN_0200F164
	str r0, [r4, #0x14]
	ldr r0, [r5, #0x10]
	str r0, [r4, #0x18]
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	pop {r3-r7, pc}
	.balign 4
_0200F2A8: .word 0x00007FFF

	thumb_func_start FUN_0200F2AC
FUN_0200F2AC: ; 0x0200F2AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0xc]
	mov r4, #0x0
	ldr r0, [r5, #0x14]
	cmp r1, #0x1
	beq _0200F2C4
	cmp r1, #0x2
	beq _0200F2D4
	cmp r1, #0x3
	beq _0200F2E6
	b _0200F2E8
_0200F2C4:
	bl FUN_0200F2EC
	cmp r0, #0x1
	bne _0200F2E8
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200F2E8
_0200F2D4:
	bl FUN_02016A18
	add r0, r4, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r4, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200F2E8
_0200F2E6:
	mov r4, #0x1
_0200F2E8:
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0200F2EC
FUN_0200F2EC: ; 0x0200F2EC
	push {r4, lr}
	add r1, r0, #0x0
	ldr r0, [r1, #0x8]
	mov r4, #0x0
	add r2, r0, #0x1
	str r2, [r1, #0x8]
	ldr r0, [r1, #0x4]
	cmp r2, r0
	blt _0200F32A
	str r4, [r1, #0x8]
	ldr r0, [r1, #0x0]
	sub r0, r0, #0x1
	cmp r0, #0x0
	ble _0200F314
	str r0, [r1, #0x0]
	ldr r2, [r1, #0xc]
	ldr r0, [r1, #0x14]
	add r0, r2, r0
	str r0, [r1, #0xc]
	b _0200F31A
_0200F314:
	ldr r0, [r1, #0x10]
	mov r4, #0x1
	str r0, [r1, #0xc]
_0200F31A:
	ldr r2, [r1, #0xc]
	ldr r0, [r1, #0x18]
	asr r1, r2, #0x6
	lsr r1, r1, #0x19
	add r1, r2, r1
	asr r1, r1, #0x7
	bl FUN_0200E440
_0200F32A:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200F330
FUN_0200F330: ; 0x0200F330
	push {r4-r6, lr}
	add r4, r0, #0x0
	bne _0200F33A
	bl ErrorHandling
_0200F33A:
	ldr r0, _0200F54C ; =0x04000006
	ldrh r0, [r0, #0x0]
	cmp r0, #0xc0
	bge _0200F3E0
	add r5, r0, #0x1
	cmp r5, #0xbf
	ble _0200F34A
	sub r5, #0xc0
_0200F34A:
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _0200F3FA
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	ldr r3, [r4, #0x8]
	lsl r5, r5, #0x1
	mov r4, #0x6
	add r1, r0, r5
	lsl r4, r4, #0x6
	ldrsh r2, [r1, r4]
	lsl r4, r4, #0x2
	ldrsh r1, [r0, r5]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	ldr r0, _0200F550 ; =0x04000004
	bne _0200F3B4
	cmp r3, #0x0
	bne _0200F394
	ldrh r4, [r0, #0x0]
	mov r3, #0x2
	tst r3, r4
	beq _0200F3E0
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3c]
	mov r1, #0xc0
	add r0, #0x40
	strh r1, [r0, #0x0]
	pop {r4-r6, pc}
_0200F394:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	beq _0200F3E0
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F554 ; =0x04001040
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
	pop {r4-r6, pc}
_0200F3B4:
	cmp r3, #0x0
	bne _0200F3D8
	ldrh r4, [r0, #0x0]
	mov r3, #0x2
	tst r3, r4
	beq _0200F3E0
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3e]
	mov r1, #0xc0
	add r0, #0x42
	strh r1, [r0, #0x0]
	pop {r4-r6, pc}
_0200F3D8:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	bne _0200F3E2
_0200F3E0:
	b _0200F548
_0200F3E2:
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F558 ; =0x04001042
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
	pop {r4-r6, pc}
_0200F3FA:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	add r3, r0, #0x0
	lsl r5, r5, #0x1
	mov r6, #0x6
	add r1, r3, r5
	lsl r6, r6, #0x6
	ldrsh r2, [r1, r6]
	lsl r6, r6, #0x2
	ldrsh r1, [r3, r5]
	ldr r3, [r3, r6]
	ldr r0, [r4, #0x8]
	cmp r3, #0x0
	bne _0200F460
	cmp r0, #0x0
	ldr r0, _0200F550 ; =0x04000004
	bne _0200F440
	ldrh r6, [r0, #0x0]
	mov r3, #0x2
	tst r3, r6
	beq _0200F4A4
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3c]
	mov r1, #0xc0
	add r0, #0x40
	strh r1, [r0, #0x0]
	b _0200F4A4
_0200F440:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	beq _0200F4A4
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F554 ; =0x04001040
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
	b _0200F4A4
_0200F460:
	cmp r0, #0x0
	ldr r0, _0200F550 ; =0x04000004
	bne _0200F486
	ldrh r6, [r0, #0x0]
	mov r3, #0x2
	tst r3, r6
	beq _0200F4A4
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3e]
	mov r1, #0xc0
	add r0, #0x42
	strh r1, [r0, #0x0]
	b _0200F4A4
_0200F486:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	beq _0200F4A4
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F558 ; =0x04001042
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
_0200F4A4:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0200F5D8
	ldr r3, [r4, #0x8]
	mov r4, #0x6
	add r1, r0, r5
	lsl r4, r4, #0x6
	ldrsh r2, [r1, r4]
	lsl r4, r4, #0x2
	ldrsh r1, [r0, r5]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	ldr r0, _0200F550 ; =0x04000004
	bne _0200F506
	cmp r3, #0x0
	bne _0200F4E6
	ldrh r4, [r0, #0x0]
	mov r3, #0x2
	tst r3, r4
	beq _0200F548
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3c]
	mov r1, #0xc0
	add r0, #0x40
	strh r1, [r0, #0x0]
	pop {r4-r6, pc}
_0200F4E6:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	beq _0200F548
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F554 ; =0x04001040
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
	pop {r4-r6, pc}
_0200F506:
	cmp r3, #0x0
	bne _0200F52A
	ldrh r4, [r0, #0x0]
	mov r3, #0x2
	tst r3, r4
	beq _0200F548
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3e]
	mov r1, #0xc0
	add r0, #0x42
	strh r1, [r0, #0x0]
	pop {r4-r6, pc}
_0200F52A:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	beq _0200F548
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F558 ; =0x04001042
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
_0200F548:
	pop {r4-r6, pc}
	nop
_0200F54C: .word 0x04000006
_0200F550: .word 0x04000004
_0200F554: .word 0x04001040
_0200F558: .word 0x04001042

	thumb_func_start FUN_0200F55C
FUN_0200F55C: ; 0x0200F55C
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x0
	beq _0200F572
	cmp r4, #0x1
	beq _0200F572
	cmp r4, #0x2
	beq _0200F58C
	pop {r4-r6, pc}
_0200F572:
	ldr r1, _0200F5B8 ; =0x00000604
	add r0, r3, #0x0
	bl FUN_02016998
	str r0, [r5, #0x0]
	mov r0, #0x1
	str r0, [r5, #0x4]
	str r6, [r5, #0x8]
	mov r0, #0x6
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x8
	str r4, [r1, r0]
	pop {r4-r6, pc}
_0200F58C:
	ldr r1, _0200F5BC ; =0x00000C08
	add r0, r3, #0x0
	bl FUN_02016998
	str r0, [r5, #0x0]
	mov r0, #0x2
	str r0, [r5, #0x4]
	mov r0, #0x6
	mov r3, #0x0
	lsl r0, r0, #0x8
	str r6, [r5, #0x8]
	add r4, r3, #0x0
	add r1, r0, #0x4
_0200F5A6:
	ldr r2, [r5, #0x0]
	add r2, r2, r4
	str r3, [r2, r0]
	add r3, r3, #0x1
	add r4, r4, r1
	cmp r3, #0x2
	blt _0200F5A6
	pop {r4-r6, pc}
	nop
_0200F5B8: .word 0x00000604
_0200F5BC: .word 0x00000C08

	thumb_func_start FUN_0200F5C0
FUN_0200F5C0: ; 0x0200F5C0
	ldr r3, _0200F5C4 ; =FUN_0200F5C8
	bx r3
	.balign 4
_0200F5C4: .word FUN_0200F5C8

	thumb_func_start FUN_0200F5C8
FUN_0200F5C8: ; 0x0200F5C8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_0200F5D8
FUN_0200F5D8: ; 0x0200F5D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	add r4, r1, #0x0
	cmp r0, r4
	bgt _0200F5E8
	bl ErrorHandling
_0200F5E8:
	ldr r0, _0200F5F4 ; =0x00000604
	ldr r1, [r5, #0x0]
	mul r0, r4
	add r0, r1, r0
	pop {r3-r5, pc}
	nop
_0200F5F4: .word 0x00000604

	thumb_func_start FUN_0200F5F8
FUN_0200F5F8: ; 0x0200F5F8
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x4]
	mov r4, #0x0
	cmp r0, #0x0
	ble _0200F624
	mov r7, #0x3
	lsl r7, r7, #0x8
	add r6, r7, #0x0
_0200F60C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0200F5D8
	add r1, r0, r6
	add r2, r7, #0x0
	bl memcpy
	ldr r0, [r5, #0x4]
	add r4, r4, #0x1
	cmp r4, r0
	blt _0200F60C
_0200F624:
	ldr r0, [sp, #0x0]
	bl FUN_0200CAB4
	pop {r3-r7, pc}

	thumb_func_start FUN_0200F62C
FUN_0200F62C: ; 0x0200F62C
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r1, #0x0
	add r4, r2, #0x0
	cmp r0, #0x0
	bne _0200F644
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02011634
	add sp, #0xc
	pop {r4-r5, pc}
_0200F644:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02011634
	mov r2, #0x0
	add r0, r5, #0x0
	mov r1, #0x3f
	add r3, r2, #0x0
	str r4, [sp, #0x0]
	bl FUN_02011650
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, r5, #0x0
	add r2, r1, #0x0
	add r3, r1, #0x0
	str r4, [sp, #0x8]
	bl FUN_02011698
	add r0, r5, #0x0
	mov r1, #0x20
	mov r2, #0x0
	add r3, r4, #0x0
	bl FUN_02011678
	add sp, #0xc
	pop {r4-r5, pc}

	thumb_func_start FUN_0200F67C
FUN_0200F67C: ; 0x0200F67C
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r2, #0x0
	ldr r2, [sp, #0x34]
	add r6, r0, #0x0
	add r5, r3, #0x0
	ldr r4, [sp, #0x20]
	cmp r2, #0x0
	bne _0200F6B8
	add r0, r1, #0x0
	mov r1, #0x0
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl FUN_020114AC
	add r0, r7, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_02011534
	str r5, [sp, #0x0]
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	str r4, [sp, #0x4]
	bl FUN_02011574
	add sp, #0xc
	pop {r4-r7, pc}
_0200F6B8:
	mov r2, #0x0
	str r4, [sp, #0x0]
	bl FUN_02011650
	add r0, r6, #0x0
	add r1, r7, #0x0
	mov r2, #0x0
	add r3, r4, #0x0
	bl FUN_02011678
	ldr r0, [sp, #0x30]
	ldr r1, [sp, #0x24]
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	add r0, r6, #0x0
	str r4, [sp, #0x8]
	bl FUN_02011698
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0200F6E4
FUN_0200F6E4: ; 0x0200F6E4
	push {r3, lr}
	cmp r3, #0x0
	bne _0200F6F4
	add r0, r1, #0x0
	add r1, r2, #0x0
	bl FUN_02011480
	pop {r3, pc}
_0200F6F4:
	bl FUN_02011634
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0200F6FC
FUN_0200F6FC: ; 0x0200F6FC
	push {r3-r7, lr}
	add r4, r2, #0x0
	mov r2, #0xc3
	add r6, r1, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r5, r0, #0x0
	add r7, r3, #0x0
	bl Call_FillMemWithValue
	cmp r4, #0x1
	bne _0200F726
	mov r0, #0x6
	lsl r0, r0, #0x6
	str r7, [r5, r0]
	mov r0, #0xc2
	lsl r0, r0, #0x2
	strb r4, [r5, r0]
	add r0, r0, #0x1
	strb r6, [r5, r0]
	pop {r3-r7, pc}
_0200F726:
	mov r0, #0x6
	lsl r0, r0, #0x6
	str r7, [r5, r0]
	mov r0, #0xc1
	ldr r1, [sp, #0x18]
	lsl r0, r0, #0x2
	str r1, [r5, r0]
	add r1, r0, #0x4
	strb r4, [r5, r1]
	add r0, r0, #0x5
	strb r6, [r5, r0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200F740
FUN_0200F740: ; 0x0200F740
	ldr r3, _0200F74C ; =FUN_0200CA98
	add r1, r0, #0x0
	ldr r0, _0200F750 ; =FUN_0200F780
	ldr r2, _0200F754 ; =0x000003FF
	bx r3
	nop
_0200F74C: .word FUN_0200CA98
_0200F750: .word FUN_0200F780
_0200F754: .word 0x000003FF

	thumb_func_start FUN_0200F758
FUN_0200F758: ; 0x0200F758
	push {r3, lr}
	ldr r3, _0200F768 ; =0x00000309
	str r2, [sp, #0x0]
	ldrb r3, [r1, r3]
	ldr r2, _0200F76C ; =FUN_0200F7AC
	bl FUN_0200E6CC
	pop {r3, pc}
	.balign 4
_0200F768: .word 0x00000309
_0200F76C: .word FUN_0200F7AC

	thumb_func_start FUN_0200F770
FUN_0200F770: ; 0x0200F770
	ldr r3, _0200F778 ; =0x00000309
	ldrb r1, [r1, r3]
	ldr r3, _0200F77C ; =FUN_0200E6F8
	bx r3
	.balign 4
_0200F778: .word 0x00000309
_0200F77C: .word FUN_0200E6F8

	thumb_func_start FUN_0200F780
FUN_0200F780: ; 0x0200F780
	push {r3-r7, lr}
	mov r7, #0xc0
	add r6, r7, #0x0
	str r0, [sp, #0x0]
	add r5, r1, #0x0
	mov r4, #0x0
	add r6, #0xc4
_0200F78E:
	add r0, r5, #0x0
	add r0, #0xc0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl memcpy
	add r4, r4, #0x1
	add r5, r5, r6
	cmp r4, #0x2
	blt _0200F78E
	ldr r0, [sp, #0x0]
	bl FUN_0200CAB4
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200F7AC
FUN_0200F7AC: ; 0x0200F7AC
	push {r3-r5, lr}
	add r4, r0, #0x0
	bne _0200F7B6
	bl ErrorHandling
_0200F7B6:
	ldr r0, _0200FAC0 ; =0x04000006
	ldrh r0, [r0, #0x0]
	cmp r0, #0xc0
	bge _0200F838
	add r0, r0, #0x1
	cmp r0, #0xbf
	ble _0200F7C6
	sub r0, #0xc0
_0200F7C6:
	mov r2, #0xc2
	lsl r2, r2, #0x2
	ldrb r1, [r4, r2]
	cmp r1, #0x1
	beq _0200F7D2
	b _0200F96C
_0200F7D2:
	add r0, r4, r0
	add r0, #0xc0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0200F8A2
	add r0, r2, #0x1
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, _0200FAC4 ; =0x04000004
	bne _0200F802
	ldrh r2, [r0, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200F81C
	add r0, #0x46
	ldrh r2, [r0, #0x0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x3f
	orr r2, r1
	mov r1, #0x20
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0200F81C
_0200F802:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200F81C
	ldr r1, _0200FAC8 ; =0x0400104A
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x3f
	orr r2, r0
	mov r0, #0x20
	orr r0, r2
	strh r0, [r1, #0x0]
_0200F81C:
	ldr r0, _0200FACC ; =0x00000309
	ldrb r1, [r4, r0]
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	cmp r0, #0x0
	bne _0200F868
	cmp r1, #0x0
	bne _0200F84C
	ldr r2, _0200FAC4 ; =0x04000004
	mov r0, #0x2
	ldrh r1, [r2, #0x0]
	tst r0, r1
	bne _0200F83A
_0200F838:
	b _0200FCB0
_0200F83A:
	add r2, #0x44
	ldrh r1, [r2, #0x0]
	mov r0, #0x3f
	bic r1, r0
	mov r0, #0x20
	orr r1, r0
	orr r0, r1
	strh r0, [r2, #0x0]
	pop {r3-r5, pc}
_0200F84C:
	ldr r0, _0200FAC4 ; =0x04000004
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200F954
	ldr r1, _0200FAD0 ; =0x04001048
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x20
	orr r2, r0
	orr r0, r2
	strh r0, [r1, #0x0]
	pop {r3-r5, pc}
_0200F868:
	cmp r1, #0x0
	ldr r0, _0200FAC4 ; =0x04000004
	bne _0200F888
	ldrh r1, [r0, #0x0]
	mov r2, #0x2
	tst r1, r2
	beq _0200F954
	add r0, #0x44
	ldrh r3, [r0, #0x0]
	ldr r1, _0200FAD4 ; =0xFFFFC0FF
	and r3, r1
	lsl r1, r2, #0xc
	orr r3, r1
	orr r1, r3
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200F888:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200F954
	ldr r2, _0200FAD0 ; =0x04001048
	ldr r0, _0200FAD4 ; =0xFFFFC0FF
	ldrh r1, [r2, #0x0]
	and r1, r0
	lsr r0, r2, #0xd
	orr r1, r0
	orr r0, r1
	strh r0, [r2, #0x0]
	pop {r3-r5, pc}
_0200F8A2:
	add r0, r2, #0x1
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, _0200FAC4 ; =0x04000004
	bne _0200F8C6
	ldrh r2, [r0, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200F8DE
	add r0, #0x46
	ldrh r2, [r0, #0x0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x20
	orr r2, r1
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0200F8DE
_0200F8C6:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200F8DE
	ldr r1, _0200FAC8 ; =0x0400104A
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x20
	orr r2, r0
	orr r0, r2
	strh r0, [r1, #0x0]
_0200F8DE:
	ldr r0, _0200FACC ; =0x00000309
	ldrb r1, [r4, r0]
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, _0200FAC4 ; =0x04000004
	bne _0200F92A
	cmp r1, #0x0
	bne _0200F90E
	ldrh r2, [r0, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200F954
	add r0, #0x44
	ldrh r2, [r0, #0x0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x3f
	orr r2, r1
	mov r1, #0x20
	orr r1, r2
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200F90E:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200F954
	ldr r1, _0200FAD0 ; =0x04001048
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x3f
	orr r2, r0
	mov r0, #0x20
	orr r0, r2
	strh r0, [r1, #0x0]
	pop {r3-r5, pc}
_0200F92A:
	cmp r1, #0x0
	bne _0200F94C
	ldrh r1, [r0, #0x0]
	mov r2, #0x2
	tst r1, r2
	beq _0200F954
	add r0, #0x44
	ldrh r3, [r0, #0x0]
	ldr r1, _0200FAD4 ; =0xFFFFC0FF
	and r3, r1
	mov r1, #0x3f
	lsl r1, r1, #0x8
	orr r3, r1
	lsl r1, r2, #0xc
	orr r1, r3
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200F94C:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	bne _0200F956
_0200F954:
	b _0200FCB0
_0200F956:
	ldr r2, _0200FAD0 ; =0x04001048
	ldr r0, _0200FAD4 ; =0xFFFFC0FF
	ldrh r1, [r2, #0x0]
	and r1, r0
	mov r0, #0x3f
	lsl r0, r0, #0x8
	orr r1, r0
	lsr r0, r2, #0xd
	orr r0, r1
	strh r0, [r2, #0x0]
	pop {r3-r5, pc}
_0200F96C:
	add r1, r4, r0
	add r1, #0xc0
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _0200FA38
	add r1, r2, #0x1
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	ldr r1, _0200FAC4 ; =0x04000004
	bne _0200F99C
	ldrh r3, [r1, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200F9B6
	add r1, #0x46
	ldrh r3, [r1, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x3f
	orr r3, r2
	mov r2, #0x20
	orr r2, r3
	strh r2, [r1, #0x0]
	b _0200F9B6
_0200F99C:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200F9B6
	ldr r2, _0200FAC8 ; =0x0400104A
	mov r1, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r1
	mov r1, #0x3f
	orr r3, r1
	mov r1, #0x20
	orr r1, r3
	strh r1, [r2, #0x0]
_0200F9B6:
	ldr r1, _0200FACC ; =0x00000309
	ldrb r2, [r4, r1]
	mov r1, #0x6
	lsl r1, r1, #0x6
	ldr r1, [r4, r1]
	cmp r1, #0x0
	ldr r1, _0200FAC4 ; =0x04000004
	bne _0200F9FE
	cmp r2, #0x0
	bne _0200F9E4
	ldrh r3, [r1, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200FA0A
	add r1, #0x44
	ldrh r3, [r1, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x20
	orr r3, r2
	orr r2, r3
	strh r2, [r1, #0x0]
	b _0200FB16
_0200F9E4:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FA0A
	ldr r2, _0200FAD0 ; =0x04001048
	mov r1, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r1
	mov r1, #0x20
	orr r3, r1
	orr r1, r3
	strh r1, [r2, #0x0]
	b _0200FB16
_0200F9FE:
	cmp r2, #0x0
	bne _0200FA1E
	ldrh r2, [r1, #0x0]
	mov r3, #0x2
	tst r2, r3
	bne _0200FA0C
_0200FA0A:
	b _0200FB16
_0200FA0C:
	add r1, #0x44
	ldrh r5, [r1, #0x0]
	ldr r2, _0200FAD4 ; =0xFFFFC0FF
	and r5, r2
	lsl r2, r3, #0xc
	orr r5, r2
	orr r2, r5
	strh r2, [r1, #0x0]
	b _0200FB16
_0200FA1E:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FB16
	ldr r3, _0200FAD0 ; =0x04001048
	ldr r1, _0200FAD4 ; =0xFFFFC0FF
	ldrh r2, [r3, #0x0]
	and r2, r1
	lsr r1, r3, #0xd
	orr r2, r1
	orr r1, r2
	strh r1, [r3, #0x0]
	b _0200FB16
_0200FA38:
	add r1, r2, #0x1
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	ldr r1, _0200FAC4 ; =0x04000004
	bne _0200FA5C
	ldrh r3, [r1, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200FA74
	add r1, #0x46
	ldrh r3, [r1, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x20
	orr r3, r2
	orr r2, r3
	strh r2, [r1, #0x0]
	b _0200FA74
_0200FA5C:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FA74
	ldr r2, _0200FAC8 ; =0x0400104A
	mov r1, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r1
	mov r1, #0x20
	orr r3, r1
	orr r1, r3
	strh r1, [r2, #0x0]
_0200FA74:
	ldr r1, _0200FACC ; =0x00000309
	ldrb r2, [r4, r1]
	mov r1, #0x6
	lsl r1, r1, #0x6
	ldr r1, [r4, r1]
	cmp r1, #0x0
	ldr r1, _0200FAC4 ; =0x04000004
	bne _0200FAD8
	cmp r2, #0x0
	bne _0200FAA4
	ldrh r3, [r1, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200FB16
	add r1, #0x44
	ldrh r3, [r1, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x3f
	orr r3, r2
	mov r2, #0x20
	orr r2, r3
	strh r2, [r1, #0x0]
	b _0200FB16
_0200FAA4:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FB16
	ldr r2, _0200FAD0 ; =0x04001048
	mov r1, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r1
	mov r1, #0x3f
	orr r3, r1
	mov r1, #0x20
	orr r1, r3
	strh r1, [r2, #0x0]
	b _0200FB16
	.balign 4
_0200FAC0: .word 0x04000006
_0200FAC4: .word 0x04000004
_0200FAC8: .word 0x0400104A
_0200FACC: .word 0x00000309
_0200FAD0: .word 0x04001048
_0200FAD4: .word 0xFFFFC0FF
_0200FAD8:
	cmp r2, #0x0
	bne _0200FAFA
	ldrh r2, [r1, #0x0]
	mov r3, #0x2
	tst r2, r3
	beq _0200FB16
	add r1, #0x44
	ldrh r5, [r1, #0x0]
	ldr r2, _0200FCB4 ; =0xFFFFC0FF
	and r5, r2
	mov r2, #0x3f
	lsl r2, r2, #0x8
	orr r5, r2
	lsl r2, r3, #0xc
	orr r2, r5
	strh r2, [r1, #0x0]
	b _0200FB16
_0200FAFA:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FB16
	ldr r3, _0200FCB8 ; =0x04001048
	ldr r1, _0200FCB4 ; =0xFFFFC0FF
	ldrh r2, [r3, #0x0]
	and r2, r1
	mov r1, #0x3f
	lsl r1, r1, #0x8
	orr r2, r1
	lsr r1, r3, #0xd
	orr r1, r2
	strh r1, [r3, #0x0]
_0200FB16:
	mov r1, #0x61
	lsl r1, r1, #0x2
	add r1, r4, r1
	add r0, r1, r0
	add r0, #0xc0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	ldr r0, _0200FCBC ; =0x00000309
	bne _0200FBEC
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, _0200FCC0 ; =0x04000004
	bne _0200FB4C
	ldrh r3, [r0, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200FB66
	add r0, #0x46
	ldrh r3, [r0, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x3f
	orr r3, r2
	mov r2, #0x20
	orr r2, r3
	strh r2, [r0, #0x0]
	b _0200FB66
_0200FB4C:
	ldrh r2, [r0, #0x0]
	mov r0, #0x2
	tst r0, r2
	beq _0200FB66
	ldr r2, _0200FCC4 ; =0x0400104A
	mov r0, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r0
	mov r0, #0x3f
	orr r3, r0
	mov r0, #0x20
	orr r0, r3
	strh r0, [r2, #0x0]
_0200FB66:
	ldr r0, _0200FCBC ; =0x00000309
	ldrb r2, [r4, r0]
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r0, [r1, r0]
	cmp r0, #0x0
	bne _0200FBB2
	cmp r2, #0x0
	bne _0200FB94
	ldr r2, _0200FCC0 ; =0x04000004
	mov r0, #0x2
	ldrh r1, [r2, #0x0]
	tst r0, r1
	beq _0200FB9E
	add r2, #0x44
	ldrh r1, [r2, #0x0]
	mov r0, #0x3f
	bic r1, r0
	mov r0, #0x20
	orr r1, r0
	orr r0, r1
	strh r0, [r2, #0x0]
	pop {r3-r5, pc}
_0200FB94:
	ldr r0, _0200FCC0 ; =0x04000004
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	bne _0200FBA0
_0200FB9E:
	b _0200FCB0
_0200FBA0:
	ldr r1, _0200FCB8 ; =0x04001048
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x20
	orr r2, r0
	orr r0, r2
	strh r0, [r1, #0x0]
	pop {r3-r5, pc}
_0200FBB2:
	cmp r2, #0x0
	ldr r0, _0200FCC0 ; =0x04000004
	bne _0200FBD2
	ldrh r1, [r0, #0x0]
	mov r2, #0x2
	tst r1, r2
	beq _0200FCB0
	add r0, #0x44
	ldrh r3, [r0, #0x0]
	ldr r1, _0200FCB4 ; =0xFFFFC0FF
	and r3, r1
	lsl r1, r2, #0xc
	orr r3, r1
	orr r1, r3
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200FBD2:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200FCB0
	ldr r2, _0200FCB8 ; =0x04001048
	ldr r0, _0200FCB4 ; =0xFFFFC0FF
	ldrh r1, [r2, #0x0]
	and r1, r0
	lsr r0, r2, #0xd
	orr r1, r0
	orr r0, r1
	strh r0, [r2, #0x0]
	pop {r3-r5, pc}
_0200FBEC:
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, _0200FCC0 ; =0x04000004
	bne _0200FC0E
	ldrh r3, [r0, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200FC26
	add r0, #0x46
	ldrh r3, [r0, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x20
	orr r3, r2
	orr r2, r3
	strh r2, [r0, #0x0]
	b _0200FC26
_0200FC0E:
	ldrh r2, [r0, #0x0]
	mov r0, #0x2
	tst r0, r2
	beq _0200FC26
	ldr r2, _0200FCC4 ; =0x0400104A
	mov r0, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r0
	mov r0, #0x20
	orr r3, r0
	orr r0, r3
	strh r0, [r2, #0x0]
_0200FC26:
	ldr r0, _0200FCBC ; =0x00000309
	ldrb r2, [r4, r0]
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r0, [r1, r0]
	cmp r0, #0x0
	ldr r0, _0200FCC0 ; =0x04000004
	bne _0200FC72
	cmp r2, #0x0
	bne _0200FC56
	ldrh r2, [r0, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FCB0
	add r0, #0x44
	ldrh r2, [r0, #0x0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x3f
	orr r2, r1
	mov r1, #0x20
	orr r1, r2
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200FC56:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200FCB0
	ldr r1, _0200FCB8 ; =0x04001048
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x3f
	orr r2, r0
	mov r0, #0x20
	orr r0, r2
	strh r0, [r1, #0x0]
	pop {r3-r5, pc}
_0200FC72:
	cmp r2, #0x0
	bne _0200FC94
	ldrh r1, [r0, #0x0]
	mov r2, #0x2
	tst r1, r2
	beq _0200FCB0
	add r0, #0x44
	ldrh r3, [r0, #0x0]
	ldr r1, _0200FCB4 ; =0xFFFFC0FF
	and r3, r1
	mov r1, #0x3f
	lsl r1, r1, #0x8
	orr r3, r1
	lsl r1, r2, #0xc
	orr r1, r3
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200FC94:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200FCB0
	ldr r2, _0200FCB8 ; =0x04001048
	ldr r0, _0200FCB4 ; =0xFFFFC0FF
	ldrh r1, [r2, #0x0]
	and r1, r0
	mov r0, #0x3f
	lsl r0, r0, #0x8
	orr r1, r0
	lsr r0, r2, #0xd
	orr r0, r1
	strh r0, [r2, #0x0]
_0200FCB0:
	pop {r3-r5, pc}
	nop
_0200FCB4: .word 0xFFFFC0FF
_0200FCB8: .word 0x04001048
_0200FCBC: .word 0x00000309
_0200FCC0: .word 0x04000004
_0200FCC4: .word 0x0400104A

	thumb_func_start FUN_0200FCC8
FUN_0200FCC8: ; 0x0200FCC8
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r6, r1, #0x0
	mov r1, #0x4c
	bl FUN_02016998
	str r0, [r5, #0x14]
	add r4, r0, #0x0
	ldr r0, [r5, #0x10]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	add r0, r4, #0x0
	bl FUN_0200FE20
	add r6, #0x20
	ldrb r0, [r6, #0x0]
	cmp r0, #0x0
	ldr r0, [r5, #0x18]
	bne _0200FD06
	ldr r2, [r4, #0x30]
	ldr r3, [r4, #0x44]
	mov r1, #0x1
	bl FUN_0200F6E4
	b _0200FD10
_0200FD06:
	ldr r2, [r4, #0x30]
	ldr r3, [r4, #0x44]
	mov r1, #0x2
	bl FUN_0200F6E4
_0200FD10:
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200FD1C
FUN_0200FD1C: ; 0x0200FD1C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _0200FD34
	cmp r0, #0x2
	beq _0200FD50
	cmp r0, #0x3
	beq _0200FD64
	b _0200FD66
_0200FD34:
	add r0, r4, #0x0
	bl FUN_0200FE90
	cmp r0, #0x1
	bne _0200FD66
	ldr r0, [r4, #0x44]
	ldr r1, [r5, #0x18]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FD66
_0200FD50:
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FD66
_0200FD64:
	mov r6, #0x1
_0200FD66:
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200FD6C
FUN_0200FD6C: ; 0x0200FD6C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r6, r1, #0x0
	mov r1, #0x98
	add r7, r2, #0x0
	bl FUN_02016998
	str r0, [r5, #0x14]
	add r4, r0, #0x0
	ldr r0, [r5, #0x10]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	add r0, r4, #0x0
	bl FUN_0200FE20
	ldr r0, [r5, #0x10]
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	add r0, #0x4c
	bl FUN_0200FE20
	ldr r0, [r5, #0x18]
	ldr r2, [r5, #0x10]
	ldr r3, [r4, #0x44]
	mov r1, #0x3
	bl FUN_0200F6E4
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200FDC4
FUN_0200FDC4: ; 0x0200FDC4
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _0200FDDC
	cmp r0, #0x2
	beq _0200FE04
	cmp r0, #0x3
	beq _0200FE18
	b _0200FE1A
_0200FDDC:
	add r0, r4, #0x0
	bl FUN_0200FE90
	add r7, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x4c
	bl FUN_0200FE90
	add r0, r7, r0
	cmp r0, #0x2
	bne _0200FE1A
	ldr r0, [r4, #0x44]
	ldr r1, [r5, #0x18]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FE1A
_0200FE04:
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FE1A
_0200FE18:
	mov r6, #0x1
_0200FE1A:
	add r0, r6, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200FE20
FUN_0200FE20: ; 0x0200FE20
	push {r3-r7, lr}
	sub sp, #0x18
	add r4, r1, #0x0
	add r1, #0x10
	add r7, r3, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	str r1, [sp, #0x0]
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r1, #0x20
	add r2, #0x10
	add r3, r4, #0x0
	str r6, [sp, #0x4]
	bl FUN_0200F1A8
	ldr r1, [sp, #0x30]
	add r0, r4, #0x0
	add r2, r4, #0x0
	str r1, [r5, #0x30]
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	add r2, #0x23
	str r0, [r5, #0x34]
	str r6, [r5, #0x38]
	str r7, [r5, #0x3c]
	mov r0, #0x0
	str r0, [r5, #0x40]
	ldr r0, [sp, #0x34]
	str r0, [r5, #0x48]
	ldrb r2, [r2, #0x0]
	str r2, [r5, #0x44]
	str r1, [sp, #0x0]
	ldr r1, [r4, #0x0]
	add r2, r4, #0x0
	str r1, [sp, #0x4]
	ldr r1, [r4, #0x4]
	add r2, #0x22
	str r1, [sp, #0x8]
	ldr r1, [r4, #0x8]
	str r1, [sp, #0xc]
	ldr r1, [r4, #0xc]
	str r1, [sp, #0x10]
	ldr r1, [r5, #0x44]
	str r1, [sp, #0x14]
	add r1, r4, #0x0
	add r1, #0x21
	add r4, #0x20
	ldrb r1, [r1, #0x0]
	ldrb r2, [r2, #0x0]
	ldrb r3, [r4, #0x0]
	bl FUN_0200F67C
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200FE90
FUN_0200FE90: ; 0x0200FE90
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0x40]
	add r2, r1, #0x1
	str r2, [r4, #0x40]
	ldr r1, [r4, #0x3c]
	cmp r2, r1
	blt _0200FF10
	mov r1, #0x0
	str r1, [r4, #0x40]
	ldr r1, [r4, #0x38]
	sub r1, r1, #0x1
	cmp r1, #0x0
	ble _0200FEBA
	str r1, [r4, #0x38]
	add r1, r4, #0x0
	add r1, #0x10
	bl FUN_0200F184
	b _0200FED8
_0200FEBA:
	ldr r0, [r4, #0x2c]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x34]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x30]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x48]
	ldr r1, [r4, #0x20]
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	bl FUN_02011698
	add sp, #0xc
	mov r0, #0x1
	pop {r3-r4, pc}
_0200FED8:
	ldr r1, [r4, #0xc]
	asr r0, r1, #0x6
	lsr r0, r0, #0x19
	add r0, r1, r0
	asr r0, r0, #0x7
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x34]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x30]
	str r0, [sp, #0x8]
	ldr r2, [r4, #0x0]
	ldr r3, [r4, #0x4]
	asr r1, r2, #0x6
	lsr r1, r1, #0x19
	add r1, r2, r1
	ldr r0, [r4, #0x48]
	asr r2, r3, #0x6
	lsr r2, r2, #0x19
	add r2, r3, r2
	ldr r4, [r4, #0x8]
	asr r1, r1, #0x7
	asr r3, r4, #0x6
	lsr r3, r3, #0x19
	add r3, r4, r3
	asr r2, r2, #0x7
	asr r3, r3, #0x7
	bl FUN_02011698
_0200FF10:
	mov r0, #0x0
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0200FF18
FUN_0200FF18: ; 0x0200FF18
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x38
	bl FUN_02016998
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_0200FFAC
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_0200FF50
FUN_0200FF50: ; 0x0200FF50
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _0200FF68
	cmp r0, #0x2
	beq _0200FF84
	cmp r0, #0x3
	beq _0200FF9E
	b _0200FFA2
_0200FF68:
	add r0, r4, #0x0
	bl FUN_02010084
	cmp r0, #0x1
	bne _0200FFA6
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x30]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FFA6
_0200FF84:
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FFA6
_0200FF9E:
	mov r6, #0x1
	b _0200FFA6
_0200FFA2:
	bl ErrorHandling
_0200FFA6:
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200FFAC
FUN_0200FFAC: ; 0x0200FFAC
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	str r2, [sp, #0x18]
	str r3, [sp, #0x1c]
	ldr r6, [sp, #0x38]
	ldr r7, [sp, #0x3c]
	bl FUN_0200F164
	str r0, [sp, #0x20]
	ldrb r1, [r4, #0xc]
	ldr r3, [sp, #0x44]
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl FUN_0200F55C
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x7
	str r0, [r5, #0xc]
	mov r0, #0x8
	ldrsh r0, [r4, r0]
	str r0, [r5, #0x10]
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	str r0, [r5, #0x14]
	ldr r0, [sp, #0x20]
	str r0, [r5, #0x18]
	ldr r0, [sp, #0x18]
	str r0, [r5, #0x1c]
	ldr r0, [sp, #0x1c]
	str r0, [r5, #0x20]
	mov r0, #0x0
	str r0, [r5, #0x24]
	ldr r0, [sp, #0x40]
	str r7, [r5, #0x30]
	str r0, [r5, #0x34]
	ldr r0, [sp, #0x44]
	str r0, [r5, #0x28]
	ldrb r0, [r4, #0xf]
	str r0, [r5, #0x2c]
	add r0, r5, #0x0
	bl FUN_02010168
	ldr r0, _02010078 ; =FUN_0200F5F8
	ldr r2, _0201007C ; =0x000003FF
	add r1, r5, #0x0
	bl FUN_0200CA98
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	mov r1, #0x3
	str r6, [sp, #0x0]
	lsl r1, r1, #0x8
	ldrsh r1, [r0, r1]
	str r1, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	mov r1, #0x12
	lsl r1, r1, #0x6
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x2c]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xe]
	ldrb r3, [r4, #0xc]
	add r0, r7, #0x0
	bl FUN_0200F67C
	ldrb r0, [r4, #0xc]
	cmp r0, #0x0
	bne _02010058
	ldr r3, [r5, #0x2c]
	add r0, r7, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_0200F6E4
	b _02010064
_02010058:
	ldr r3, [r5, #0x2c]
	add r0, r7, #0x0
	mov r1, #0x2
	add r2, r6, #0x0
	bl FUN_0200F6E4
_02010064:
	ldr r0, [sp, #0x44]
	ldr r2, _02010080 ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x34]
	add r1, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0200E6CC
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_02010078: .word FUN_0200F5F8
_0201007C: .word 0x000003FF
_02010080: .word FUN_0200F330

	thumb_func_start FUN_02010084
FUN_02010084: ; 0x02010084
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x24]
	add r2, r1, #0x1
	str r2, [r4, #0x24]
	ldr r1, [r4, #0x20]
	cmp r2, r1
	blt _020100C8
	mov r1, #0x0
	str r1, [r4, #0x24]
	ldr r1, [r4, #0x1c]
	sub r1, r1, #0x1
	cmp r1, #0x0
	ble _020100BA
	str r1, [r4, #0x1c]
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #0x18]
	add r1, r2, r1
	str r1, [r4, #0xc]
	bl FUN_02010168
	ldr r0, _020100CC ; =FUN_0200F5F8
	ldr r2, _020100D0 ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _020100C8
_020100BA:
	ldr r0, [r4, #0x34]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x28]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_020100C8:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_020100CC: .word FUN_0200F5F8
_020100D0: .word 0x000003FF

	thumb_func_start FUN_020100D4
FUN_020100D4: ; 0x020100D4
	push {r4-r7, lr}
	sub sp, #0xc
	str r1, [sp, #0x0]
	asr r1, r0, #0x6
	lsr r1, r1, #0x19
	add r1, r0, r1
	asr r1, r1, #0x7
	ldr r5, [sp, #0x20]
	ldr r4, [sp, #0x24]
	sub r0, r3, r2
	bpl _020100EC
	neg r0, r0
_020100EC:
	cmp r0, r1
	blt _020100FA
	mov r0, #0x0
	str r0, [r5, #0x0]
	add sp, #0xc
	str r0, [r4, #0x0]
	pop {r4-r7, pc}
_020100FA:
	lsl r0, r0, #0xc
	str r0, [sp, #0x4]
	asr r7, r0, #0x1f
	lsl r0, r1, #0xc
	asr r1, r0, #0x1f
	add r2, r0, #0x0
	add r3, r1, #0x0
	bl _ll_mul
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r6, r1, #0x0
	add r1, r7, #0x0
	add r2, r0, #0x0
	add r3, r7, #0x0
	bl _ll_mul
	add r2, r0, #0x0
	add r3, r1, #0x0
	mov r0, #0x2
	ldr r1, [sp, #0x8]
	mov r7, #0x0
	lsl r0, r0, #0xa
	add r0, r1, r0
	adc r6, r7
	lsl r1, r6, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	mov r1, #0x2
	lsl r1, r1, #0xa
	add r2, r2, r1
	adc r3, r7
	lsl r1, r3, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	sub r0, r0, r2
	bl FX_Sqrt
	asr r2, r0, #0xc
	ldr r0, [sp, #0x0]
	sub r0, r0, r2
	str r0, [r5, #0x0]
	bpl _02010154
	add r0, r7, #0x0
	str r0, [r5, #0x0]
_02010154:
	ldr r1, [r5, #0x0]
	lsl r0, r2, #0x1
	add r0, r1, r0
	str r0, [r4, #0x0]
	cmp r0, #0xff
	ble _02010164
	mov r0, #0xff
	str r0, [r4, #0x0]
_02010164:
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02010168
FUN_02010168: ; 0x02010168
	push {r3-r7, lr}
	sub sp, #0x10
	mov r1, #0x0
	add r5, r0, #0x0
	bl FUN_0200F5D8
	add r7, r0, #0x0
	mov r4, #0x0
	add r6, r7, #0x0
_0201017A:
	ldr r2, [r5, #0x14]
	cmp r4, r2
	bgt _02010194
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	ldr r0, [r5, #0xc]
	ldr r1, [r5, #0x10]
	add r3, r4, #0x0
	bl FUN_020100D4
	b _020101CE
_02010194:
	lsl r0, r2, #0x1
	cmp r4, r0
	bgt _020101BC
	sub r0, r0, r4
	lsl r0, r0, #0x1
	add r1, r7, r0
	mov r0, #0x3
	lsl r0, r0, #0x8
	ldrsh r0, [r1, r0]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	lsl r0, r0, #0x1
	sub r0, r0, r4
	lsl r0, r0, #0x1
	add r1, r7, r0
	mov r0, #0x12
	lsl r0, r0, #0x6
	ldrsh r0, [r1, r0]
	str r0, [sp, #0x8]
	b _020101CE
_020101BC:
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	ldr r0, [r5, #0xc]
	ldr r1, [r5, #0x10]
	add r3, r4, #0x0
	bl FUN_020100D4
_020101CE:
	mov r0, #0x3
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0x8
	strh r1, [r6, r0]
	mov r0, #0x12
	ldr r1, [sp, #0x8]
	lsl r0, r0, #0x6
	strh r1, [r6, r0]
	add r4, r4, #0x1
	add r6, r6, #0x2
	cmp r4, #0xc0
	blt _0201017A
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020101EC
FUN_020101EC: ; 0x020101EC
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x30
	bl FUN_02016998
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_02010280
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02010224
FUN_02010224: ; 0x02010224
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _0201023C
	cmp r0, #0x2
	beq _02010258
	cmp r0, #0x3
	beq _02010272
	b _02010276
_0201023C:
	add r0, r4, #0x0
	bl FUN_02010348
	cmp r0, #0x1
	bne _0201027A
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x24]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0201027A
_02010258:
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0201027A
_02010272:
	mov r6, #0x1
	b _0201027A
_02010276:
	bl ErrorHandling
_0201027A:
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02010280
FUN_02010280: ; 0x02010280
	push {r3-r7, lr}
	sub sp, #0x20
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	str r2, [sp, #0x18]
	str r3, [sp, #0x1c]
	ldr r6, [sp, #0x38]
	ldr r7, [sp, #0x3c]
	bl FUN_0200F164
	str r0, [r5, #0x10]
	ldrb r1, [r4, #0x8]
	ldr r3, [sp, #0x44]
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl FUN_0200F55C
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x7
	str r0, [r5, #0xc]
	ldr r0, [sp, #0x18]
	str r0, [r5, #0x14]
	ldr r0, [sp, #0x1c]
	str r0, [r5, #0x18]
	mov r0, #0x0
	str r0, [r5, #0x1c]
	ldr r0, [sp, #0x40]
	str r7, [r5, #0x24]
	str r0, [r5, #0x28]
	ldr r0, [sp, #0x44]
	str r0, [r5, #0x2c]
	ldrb r0, [r4, #0xb]
	str r0, [r5, #0x20]
	add r0, r5, #0x0
	bl FUN_02010398
	ldr r0, _0201033C ; =FUN_0200F5F8
	ldr r2, _02010340 ; =0x000003FF
	add r1, r5, #0x0
	bl FUN_0200CA98
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	mov r1, #0x3
	str r6, [sp, #0x0]
	lsl r1, r1, #0x8
	ldrsh r1, [r0, r1]
	str r1, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	mov r1, #0x12
	lsl r1, r1, #0x6
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x9]
	ldrb r2, [r4, #0xa]
	ldrb r3, [r4, #0x8]
	add r0, r7, #0x0
	bl FUN_0200F67C
	ldrb r0, [r4, #0x8]
	cmp r0, #0x0
	bne _0201031C
	ldr r3, [r5, #0x20]
	add r0, r7, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_0200F6E4
	b _02010328
_0201031C:
	ldr r3, [r5, #0x20]
	add r0, r7, #0x0
	mov r1, #0x2
	add r2, r6, #0x0
	bl FUN_0200F6E4
_02010328:
	ldr r0, [sp, #0x44]
	ldr r2, _02010344 ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x28]
	add r1, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0200E6CC
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_0201033C: .word FUN_0200F5F8
_02010340: .word 0x000003FF
_02010344: .word FUN_0200F330

	thumb_func_start FUN_02010348
FUN_02010348: ; 0x02010348
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x1c]
	add r2, r1, #0x1
	str r2, [r4, #0x1c]
	ldr r1, [r4, #0x18]
	cmp r2, r1
	blt _0201038C
	mov r1, #0x0
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x14]
	sub r1, r1, #0x1
	cmp r1, #0x0
	ble _0201037E
	str r1, [r4, #0x14]
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r1, r2, r1
	str r1, [r4, #0xc]
	bl FUN_02010398
	ldr r0, _02010390 ; =FUN_0200F5F8
	ldr r2, _02010394 ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _0201038C
_0201037E:
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x2c]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_0201038C:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_02010390: .word FUN_0200F5F8
_02010394: .word 0x000003FF

	thumb_func_start FUN_02010398
FUN_02010398: ; 0x02010398
	push {r3-r7, lr}
	sub sp, #0x1fc
	sub sp, #0x104
	add r4, r0, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	ldr r1, [r4, #0xc]
	add r5, r0, #0x0
	asr r0, r1, #0x6
	lsr r0, r0, #0x19
	add r0, r1, r0
	asr r0, r0, #0x7
	add r1, sp, #0x0
	mov r2, #0xc0
	mov r3, #0x0
	bl FUN_0200F0F8
	mov r7, #0x12
	mov r6, #0x0
	add r4, sp, #0x0
	lsl r7, r7, #0x6
_020103C4:
	ldr r1, [r4, #0x0]
	mov r0, #0x80
	neg r1, r1
	bl FUN_0200F174
	mov r1, #0x3
	lsl r1, r1, #0x8
	strh r0, [r5, r1]
	ldr r1, [r4, #0x0]
	mov r0, #0x80
	bl FUN_0200F174
	strh r0, [r5, r7]
	add r6, r6, #0x1
	add r4, r4, #0x4
	add r5, r5, #0x2
	cmp r6, #0xc0
	blt _020103C4
	add sp, #0x1fc
	add sp, #0x104
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020103F0
FUN_020103F0: ; 0x020103F0
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x34
	bl FUN_02016998
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_0201047C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02010428
FUN_02010428: ; 0x02010428
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _02010440
	cmp r0, #0x2
	beq _0201045C
	cmp r0, #0x3
	beq _02010476
	b _02010478
_02010440:
	add r0, r4, #0x0
	bl FUN_02010550
	cmp r0, #0x1
	bne _02010478
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010478
_0201045C:
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010478
_02010476:
	mov r6, #0x1
_02010478:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0201047C
FUN_0201047C: ; 0x0201047C
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	str r2, [sp, #0x18]
	sub r0, r1, r0
	add r1, r2, #0x0
	str r3, [sp, #0x1c]
	ldr r6, [sp, #0x38]
	ldr r7, [sp, #0x3c]
	bl _s32_div_f
	str r0, [sp, #0x20]
	ldrb r1, [r4, #0x8]
	ldr r3, [sp, #0x44]
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl FUN_0200F55C
	mov r0, #0x2
	lsl r0, r0, #0x12
	str r0, [r5, #0xc]
	ldr r0, [r4, #0x0]
	str r0, [r5, #0x10]
	ldr r0, [sp, #0x20]
	str r0, [r5, #0x14]
	ldr r0, [sp, #0x18]
	str r0, [r5, #0x18]
	ldr r0, [sp, #0x1c]
	str r0, [r5, #0x1c]
	mov r0, #0x0
	str r0, [r5, #0x20]
	ldr r0, [sp, #0x40]
	str r7, [r5, #0x28]
	str r0, [r5, #0x2c]
	ldr r0, [sp, #0x44]
	str r0, [r5, #0x30]
	ldrb r0, [r4, #0xb]
	str r0, [r5, #0x24]
	add r0, r5, #0x0
	bl FUN_020105A0
	ldr r0, _02010544 ; =FUN_0200F5F8
	ldr r2, _02010548 ; =0x000003FF
	add r1, r5, #0x0
	bl FUN_0200CA98
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	mov r1, #0xf
	str r6, [sp, #0x0]
	lsl r1, r1, #0x6
	ldrsh r1, [r0, r1]
	str r1, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	mov r1, #0x15
	lsl r1, r1, #0x6
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x24]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x9]
	ldrb r2, [r4, #0xa]
	ldrb r3, [r4, #0x8]
	add r0, r7, #0x0
	bl FUN_0200F67C
	ldrb r0, [r4, #0x8]
	cmp r0, #0x0
	bne _02010524
	ldr r3, [r5, #0x24]
	add r0, r7, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_0200F6E4
	b _02010530
_02010524:
	ldr r3, [r5, #0x24]
	add r0, r7, #0x0
	mov r1, #0x2
	add r2, r6, #0x0
	bl FUN_0200F6E4
_02010530:
	ldr r0, [sp, #0x44]
	ldr r2, _0201054C ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x2c]
	add r1, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0200E6CC
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_02010544: .word FUN_0200F5F8
_02010548: .word 0x000003FF
_0201054C: .word FUN_0200F330

	thumb_func_start FUN_02010550
FUN_02010550: ; 0x02010550
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x20]
	add r2, r1, #0x1
	str r2, [r4, #0x20]
	ldr r1, [r4, #0x1c]
	cmp r2, r1
	blt _02010594
	mov r1, #0x0
	str r1, [r4, #0x20]
	ldr r1, [r4, #0x18]
	sub r1, r1, #0x1
	cmp r1, #0x0
	ble _02010586
	str r1, [r4, #0x18]
	ldr r2, [r4, #0x10]
	ldr r1, [r4, #0x14]
	add r1, r2, r1
	str r1, [r4, #0x10]
	bl FUN_020105A0
	ldr r0, _02010598 ; =FUN_0200F5F8
	ldr r2, _0201059C ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _02010594
_02010586:
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x30]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_02010594:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_02010598: .word FUN_0200F5F8
_0201059C: .word 0x000003FF

	thumb_func_start FUN_020105A0
FUN_020105A0: ; 0x020105A0
	push {r4-r7, lr}
	sub sp, #0x1fc
	sub sp, #0x110
	add r4, r0, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x10]
	ldr r2, [r4, #0xc]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02010680 ; =0x020FFA38
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	asr r7, r1, #0xc
	lsl r0, r7, #0x1
	mov r1, #0x15
	bl _s32_div_f
	add r0, r0, #0x1
	lsl r0, r0, #0x1
	mov r1, #0xb4
	sub r2, r1, r0
	ldr r0, _02010684 ; =0x0000FFFF
	add r1, #0xb4
	mul r0, r2
	bl _s32_div_f
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r4, r1, #0x1
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0x8
	bl FUN_0200F14C
	asr r0, r0, #0xc
	str r0, [sp, #0x4]
	cmp r0, #0xc0
	blt _0201060C
	bl ErrorHandling
_0201060C:
	ldr r2, [sp, #0x4]
	add r0, r4, #0x0
	add r1, sp, #0xc
	mov r3, #0x0
	bl FUN_0200F0F8
	ldr r5, [sp, #0x0]
	mov r4, #0x0
_0201061C:
	ldr r0, [sp, #0x4]
	add r1, r4, #0x1
	sub r0, r0, r1
	add r6, r7, #0x0
	cmp r0, #0x0
	ble _02010634
	lsl r1, r0, #0x2
	add r0, sp, #0xc
	ldr r0, [r0, r1]
	cmp r0, r7
	ble _02010634
	add r6, r0, #0x0
_02010634:
	mov r0, #0x80
	neg r1, r6
	bl FUN_0200F174
	str r0, [sp, #0x8]
	mov r0, #0x80
	add r1, r6, #0x0
	bl FUN_0200F174
	ldr r1, [sp, #0x8]
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	asr r2, r1, #0x10
	mov r1, #0x3
	lsl r1, r1, #0x8
	strh r2, [r5, r1]
	asr r1, r0, #0x10
	mov r0, #0x12
	lsl r0, r0, #0x6
	strh r1, [r5, r0]
	mov r0, #0xbf
	sub r0, r0, r4
	lsl r3, r0, #0x1
	ldr r0, [sp, #0x0]
	add r4, r4, #0x1
	add r0, r0, r3
	mov r3, #0x3
	lsl r3, r3, #0x8
	strh r2, [r0, r3]
	mov r2, #0x12
	lsl r2, r2, #0x6
	add r5, r5, #0x2
	strh r1, [r0, r2]
	cmp r4, #0x60
	blt _0201061C
	add sp, #0x1fc
	add sp, #0x110
	pop {r4-r7, pc}
	.balign 4
_02010680: .word 0x020FFA38
_02010684: .word 0x0000FFFF

	thumb_func_start FUN_02010688
FUN_02010688: ; 0x02010688
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x30
	bl FUN_02016998
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_02010720
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_020106C0
FUN_020106C0: ; 0x020106C0
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _020106D8
	cmp r0, #0x2
	beq _020106F4
	cmp r0, #0x3
	beq _02010714
	b _02010718
_020106D8:
	add r0, r4, #0x0
	bl FUN_02010834
	cmp r0, #0x1
	bne _0201071C
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x24]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0201071C
_020106F4:
	add r0, r4, #0x0
	bl FUN_02010884
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0201071C
_02010714:
	mov r6, #0x1
	b _0201071C
_02010718:
	bl ErrorHandling
_0201071C:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02010720
FUN_02010720: ; 0x02010720
	push {r4-r7, lr}
	sub sp, #0x24
	add r5, r1, #0x0
	add r7, r0, #0x0
	str r2, [sp, #0x18]
	ldr r0, [sp, #0x38]
	ldrb r2, [r5, #0x8]
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x44]
	mov r1, #0x30
	mul r1, r2
	str r3, [sp, #0x1c]
	str r0, [sp, #0x44]
	bl FUN_02016998
	str r0, [r7, #0xc]
	cmp r0, #0x0
	bne _02010748
	bl ErrorHandling
_02010748:
	ldrb r0, [r5, #0x8]
	str r0, [r7, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x20]
	ldrb r0, [r5, #0x8]
	cmp r0, #0x0
	ble _02010788
	ldr r6, [sp, #0x20]
	add r4, r6, #0x0
_0201075A:
	ldr r0, [r5, #0x4]
	ldr r2, [r7, #0xc]
	add r0, r0, r6
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x4]
	add r0, r2, r4
	ldr r3, [r5, #0x0]
	add r1, r0, #0x0
	add r2, r2, r4
	add r1, #0x20
	add r2, #0x10
	add r3, r3, r6
	bl FUN_0200F1A8
	ldr r0, [sp, #0x20]
	ldrb r1, [r5, #0x8]
	add r0, r0, #0x1
	add r6, #0x10
	add r4, #0x30
	str r0, [sp, #0x20]
	cmp r0, r1
	blt _0201075A
_02010788:
	ldrb r1, [r5, #0x9]
	ldr r2, [sp, #0x38]
	ldr r3, [sp, #0x44]
	add r0, r7, #0x0
	bl FUN_0200F55C
	ldr r0, [sp, #0x18]
	str r0, [r7, #0x14]
	ldr r0, [sp, #0x1c]
	str r0, [r7, #0x18]
	mov r0, #0x0
	str r0, [r7, #0x1c]
	ldr r0, [sp, #0x3c]
	str r0, [r7, #0x24]
	ldr r0, [sp, #0x40]
	str r0, [r7, #0x28]
	ldr r0, [sp, #0x44]
	str r0, [r7, #0x2c]
	ldrb r0, [r5, #0xc]
	str r0, [r7, #0x20]
	add r0, r7, #0x0
	bl FUN_02010894
	ldr r0, _02010828 ; =FUN_0200F5F8
	ldr r2, _0201082C ; =0x000003FF
	add r1, r7, #0x0
	bl FUN_0200CA98
	add r0, r7, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	ldr r1, [sp, #0x38]
	str r1, [sp, #0x0]
	mov r1, #0x3
	lsl r1, r1, #0x8
	ldrsh r1, [r0, r1]
	str r1, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	mov r1, #0x12
	lsl r1, r1, #0x6
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r7, #0x20]
	str r0, [sp, #0x14]
	ldrb r1, [r5, #0xa]
	ldrb r2, [r5, #0xb]
	ldrb r3, [r5, #0x9]
	ldr r0, [sp, #0x3c]
	bl FUN_0200F67C
	ldrb r0, [r5, #0x9]
	cmp r0, #0x0
	ldr r0, [r7, #0x24]
	bne _02010808
	ldr r2, [sp, #0x38]
	ldr r3, [r7, #0x20]
	mov r1, #0x1
	bl FUN_0200F6E4
	b _02010812
_02010808:
	ldr r2, [sp, #0x38]
	ldr r3, [r7, #0x20]
	mov r1, #0x2
	bl FUN_0200F6E4
_02010812:
	ldr r0, [sp, #0x44]
	ldr r2, _02010830 ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r7, #0x28]
	ldr r3, [sp, #0x38]
	add r1, r7, #0x0
	bl FUN_0200E6CC
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_02010828: .word FUN_0200F5F8
_0201082C: .word 0x000003FF
_02010830: .word FUN_0200F330

	thumb_func_start FUN_02010834
FUN_02010834: ; 0x02010834
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x1c]
	add r2, r1, #0x1
	str r2, [r4, #0x1c]
	ldr r1, [r4, #0x18]
	cmp r2, r1
	blt _02010876
	mov r1, #0x0
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x14]
	sub r1, r1, #0x1
	cmp r1, #0x0
	ble _02010868
	str r1, [r4, #0x14]
	bl FUN_02010920
	add r0, r4, #0x0
	bl FUN_02010894
	ldr r0, _0201087C ; =FUN_0200F5F8
	ldr r2, _02010880 ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _02010876
_02010868:
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x2c]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_02010876:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0201087C: .word FUN_0200F5F8
_02010880: .word 0x000003FF

	thumb_func_start FUN_02010884
FUN_02010884: ; 0x02010884
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0xc]
	pop {r4, pc}

	thumb_func_start FUN_02010894
FUN_02010894: ; 0x02010894
	push {r4-r6, lr}
	mov r1, #0x0
	add r6, r0, #0x0
	bl FUN_0200F5D8
	mov r2, #0x3
	lsl r2, r2, #0x8
	add r0, r0, r2
	mov r1, #0x0
	bl Call_FillMemWithValue
	ldr r0, [r6, #0x10]
	sub r4, r0, #0x1
	bmi _020108C6
	mov r0, #0x30
	add r5, r4, #0x0
	mul r5, r0
_020108B6:
	ldr r1, [r6, #0xc]
	add r0, r6, #0x0
	add r1, r1, r5
	bl FUN_020108C8
	sub r5, #0x30
	sub r4, r4, #0x1
	bpl _020108B6
_020108C6:
	pop {r4-r6, pc}

	thumb_func_start FUN_020108C8
FUN_020108C8: ; 0x020108C8
	push {r4-r6, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	ldr r2, [r4, #0x0]
	ldr r3, [r4, #0x8]
	asr r1, r2, #0x6
	lsr r1, r1, #0x19
	add r1, r2, r1
	asr r2, r1, #0x7
	asr r1, r3, #0x6
	ldr r5, [r4, #0xc]
	lsr r1, r1, #0x19
	add r1, r3, r1
	asr r3, r5, #0x6
	lsr r3, r3, #0x19
	add r3, r5, r3
	ldr r4, [r4, #0x4]
	asr r5, r3, #0x7
	asr r3, r4, #0x6
	lsr r3, r3, #0x19
	add r3, r4, r3
	asr r3, r3, #0x7
	asr r1, r1, #0x7
	cmp r3, r5
	bge _0201091E
	lsl r4, r3, #0x1
	lsl r1, r1, #0x10
	add r4, r0, r4
	lsl r0, r2, #0x10
	asr r6, r1, #0x10
	mov r1, #0x3
	mov r2, #0x12
	asr r0, r0, #0x10
	lsl r1, r1, #0x8
	lsl r2, r2, #0x6
_02010912:
	strh r0, [r4, r1]
	strh r6, [r4, r2]
	add r3, r3, #0x1
	add r4, r4, #0x2
	cmp r3, r5
	blt _02010912
_0201091E:
	pop {r4-r6, pc}

	thumb_func_start FUN_02010920
FUN_02010920: ; 0x02010920
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x10]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02010944
	add r4, r6, #0x0
_0201092E:
	ldr r1, [r5, #0xc]
	add r0, r1, r4
	add r1, r1, r4
	add r1, #0x10
	bl FUN_0200F184
	ldr r0, [r5, #0x10]
	add r6, r6, #0x1
	add r4, #0x30
	cmp r6, r0
	blt _0201092E
_02010944:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02010948
FUN_02010948: ; 0x02010948
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x38
	bl FUN_02016998
	str r0, [r5, #0x14]
	mov r1, #0x0
	mov r2, #0x38
	bl Call_FillMemWithValue
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_020109E8
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02010988
FUN_02010988: ; 0x02010988
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _020109A0
	cmp r0, #0x2
	beq _020109BC
	cmp r0, #0x3
	beq _020109DC
	b _020109E0
_020109A0:
	add r0, r4, #0x0
	bl FUN_02010AE4
	cmp r0, #0x1
	bne _020109E4
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x30]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _020109E4
_020109BC:
	add r0, r4, #0x0
	bl FUN_02010B3C
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _020109E4
_020109DC:
	mov r6, #0x1
	b _020109E4
_020109E0:
	bl ErrorHandling
_020109E4:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020109E8
FUN_020109E8: ; 0x020109E8
	push {r3-r7, lr}
	sub sp, #0x28
	add r4, r1, #0x0
	add r5, r0, #0x0
	mov r1, #0x0
	str r1, [r5, #0xc]
	ldr r1, [r4, #0x0]
	str r2, [sp, #0x18]
	str r1, [r5, #0x10]
	str r3, [sp, #0x1c]
	ldr r2, [r4, #0x4]
	ldr r1, [r4, #0x0]
	ldr r6, [sp, #0x40]
	sub r1, r2, r1
	str r1, [r5, #0x14]
	ldr r3, [sp, #0x4c]
	mov r1, #0x2
	add r2, r6, #0x0
	ldr r7, [sp, #0x44]
	bl FUN_0200F55C
	ldr r0, [sp, #0x18]
	mov r1, #0x0
	str r0, [r5, #0x18]
	ldr r0, [sp, #0x1c]
	str r1, [r5, #0x1c]
	str r0, [r5, #0x20]
	str r1, [r5, #0x24]
	ldr r0, [sp, #0x48]
	str r7, [r5, #0x30]
	str r0, [r5, #0x34]
	ldr r0, [sp, #0x4c]
	str r0, [r5, #0x2c]
	ldrb r0, [r4, #0xa]
	str r0, [r5, #0x28]
	add r0, r5, #0x0
	ldr r1, [r5, #0x1c]
	ldr r2, [r5, #0x18]
	add r0, #0xc
	bl FUN_02010C64
	add r0, r5, #0x0
	bl FUN_02010B40
	ldr r0, _02010AD8 ; =FUN_0200F5F8
	ldr r2, _02010ADC ; =0x000003FF
	add r1, r5, #0x0
	bl FUN_0200CA98
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	str r0, [sp, #0x20]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200F5D8
	str r0, [sp, #0x24]
	mov r1, #0x3
	ldr r0, [sp, #0x20]
	str r6, [sp, #0x0]
	lsl r1, r1, #0x8
	ldrsh r0, [r0, r1]
	mov r1, #0x12
	mov r3, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x20]
	str r3, [sp, #0x8]
	lsl r1, r1, #0x6
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x8]
	ldrb r2, [r4, #0x9]
	add r0, r7, #0x0
	bl FUN_0200F67C
	mov r1, #0x3
	ldr r0, [sp, #0x24]
	str r6, [sp, #0x0]
	lsl r1, r1, #0x8
	ldrsh r0, [r0, r1]
	mov r1, #0x12
	lsl r1, r1, #0x6
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x24]
	mov r3, #0x1
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x8]
	ldrb r2, [r4, #0x9]
	add r0, r7, #0x0
	bl FUN_0200F67C
	ldr r3, [r5, #0x28]
	add r0, r7, #0x0
	mov r1, #0x3
	add r2, r6, #0x0
	bl FUN_0200F6E4
	ldr r0, [sp, #0x4c]
	ldr r2, _02010AE0 ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x34]
	add r1, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0200E6CC
	add sp, #0x28
	pop {r3-r7, pc}
	.balign 4
_02010AD8: .word FUN_0200F5F8
_02010ADC: .word 0x000003FF
_02010AE0: .word FUN_0200F330

	thumb_func_start FUN_02010AE4
FUN_02010AE4: ; 0x02010AE4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x24]
	add r1, r0, #0x1
	str r1, [r4, #0x24]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	blt _02010B2E
	mov r0, #0x0
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x1c]
	add r1, r0, #0x1
	ldr r0, [r4, #0x18]
	cmp r1, r0
	bgt _02010B20
	str r1, [r4, #0x1c]
	add r0, r4, #0x0
	ldr r2, [r4, #0x18]
	add r0, #0xc
	bl FUN_02010C64
	add r0, r4, #0x0
	bl FUN_02010B40
	ldr r0, _02010B34 ; =FUN_0200F5F8
	ldr r2, _02010B38 ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _02010B2E
_02010B20:
	ldr r0, [r4, #0x34]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x2c]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_02010B2E:
	mov r0, #0x0
	pop {r4, pc}
	nop
_02010B34: .word FUN_0200F5F8
_02010B38: .word 0x000003FF

	thumb_func_start FUN_02010B3C
FUN_02010B3C: ; 0x02010B3C
	bx lr
	.balign 4

	thumb_func_start FUN_02010B40
FUN_02010B40: ; 0x02010B40
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	ldr r0, [r0, #0xc]
	ldr r1, _02010C60 ; =0x00003FFF
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	bl FUN_0200F5D8
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	bl FUN_0200F5D8
	add r4, r0, #0x0
	mov r6, #0x0
	add r5, r4, #0x0
_02010B6C:
	ldr r0, [sp, #0x0]
	ldr r1, [r0, #0xc]
	ldr r0, _02010C60 ; =0x00003FFF
	cmp r1, r0
	bge _02010BB0
	mov r1, #0x60
	ldr r0, [sp, #0x4]
	sub r1, r1, r6
	bl FUN_0200F0D0
	cmp r0, #0x7f
	ble _02010B86
	mov r0, #0x7f
_02010B86:
	mov r1, #0xbf
	sub r1, r1, r6
	lsl r1, r1, #0x1
	add r3, r7, r1
	mov r1, #0x80
	sub r2, r1, r0
	mov r1, #0x3
	lsl r1, r1, #0x8
	strh r2, [r3, r1]
	mov r1, #0x12
	mov r2, #0x80
	lsl r1, r1, #0x6
	strh r2, [r3, r1]
	mov r1, #0x3
	lsl r1, r1, #0x8
	strh r2, [r5, r1]
	mov r1, #0x12
	add r0, #0x80
	lsl r1, r1, #0x6
	strh r0, [r5, r1]
	b _02010BD8
_02010BB0:
	mov r0, #0xbf
	sub r0, r0, r6
	lsl r0, r0, #0x1
	mov r1, #0x3
	add r0, r7, r0
	mov r2, #0x0
	lsl r1, r1, #0x8
	strh r2, [r0, r1]
	mov r1, #0x12
	mov r2, #0x80
	lsl r1, r1, #0x6
	strh r2, [r0, r1]
	mov r0, #0x3
	add r1, r2, #0x0
	lsl r0, r0, #0x8
	strh r1, [r5, r0]
	mov r0, #0x12
	mov r1, #0xff
	lsl r0, r0, #0x6
	strh r1, [r5, r0]
_02010BD8:
	add r6, r6, #0x1
	add r5, r5, #0x2
	cmp r6, #0x60
	blt _02010B6C
	ldr r1, _02010C60 ; =0x00003FFF
	ldr r0, [sp, #0x4]
	mov r5, #0x60
	add r4, #0xc0
	sub r6, r1, r0
_02010BEA:
	ldr r0, [sp, #0x0]
	ldr r1, [r0, #0xc]
	ldr r0, _02010C60 ; =0x00003FFF
	cmp r1, r0
	bge _02010C1A
	mov r0, #0xbf
	sub r0, r0, r5
	lsl r0, r0, #0x1
	mov r1, #0x3
	add r0, r7, r0
	mov r2, #0x80
	lsl r1, r1, #0x8
	strh r2, [r0, r1]
	mov r1, #0x12
	lsl r1, r1, #0x6
	strh r2, [r0, r1]
	mov r0, #0x3
	add r1, r2, #0x0
	lsl r0, r0, #0x8
	strh r1, [r4, r0]
	mov r0, #0x12
	lsl r0, r0, #0x6
	strh r1, [r4, r0]
	b _02010C54
_02010C1A:
	add r1, r5, #0x0
	add r0, r6, #0x0
	sub r1, #0x60
	bl FUN_0200F0D0
	add r1, r0, #0x0
	cmp r1, #0x7f
	ble _02010C2C
	mov r1, #0x7f
_02010C2C:
	mov r0, #0xbf
	sub r0, r0, r5
	lsl r0, r0, #0x1
	mov r2, #0x3
	add r0, r7, r0
	mov r3, #0x0
	lsl r2, r2, #0x8
	strh r3, [r0, r2]
	mov r2, #0x80
	sub r3, r2, r1
	mov r2, #0x12
	lsl r2, r2, #0x6
	strh r3, [r0, r2]
	mov r0, #0x3
	add r1, #0x80
	lsl r0, r0, #0x8
	strh r1, [r4, r0]
	mov r1, #0xff
	add r0, r2, #0x0
	strh r1, [r4, r0]
_02010C54:
	add r5, r5, #0x1
	add r4, r4, #0x2
	cmp r5, #0xc0
	blt _02010BEA
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02010C60: .word 0x00003FFF

	thumb_func_start FUN_02010C64
FUN_02010C64: ; 0x02010C64
	push {r4, lr}
	add r4, r0, #0x0
	ldr r3, [r4, #0x8]
	add r0, r3, #0x0
	mul r0, r1
	add r1, r2, #0x0
	bl _s32_div_f
	ldr r1, [r4, #0x4]
	add r0, r0, r1
	str r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02010C7C
FUN_02010C7C: ; 0x02010C7C
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x38
	bl FUN_02016998
	str r0, [r5, #0x14]
	mov r1, #0x0
	mov r2, #0x38
	bl Call_FillMemWithValue
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_02010D1C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02010CBC
FUN_02010CBC: ; 0x02010CBC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _02010CD4
	cmp r0, #0x2
	beq _02010CF0
	cmp r0, #0x3
	beq _02010D10
	b _02010D14
_02010CD4:
	add r0, r4, #0x0
	bl FUN_02010DEC
	cmp r0, #0x1
	bne _02010D18
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x30]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010D18
_02010CF0:
	add r0, r4, #0x0
	bl FUN_02010E44
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010D18
_02010D10:
	mov r6, #0x1
	b _02010D18
_02010D14:
	bl ErrorHandling
_02010D18:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02010D1C
FUN_02010D1C: ; 0x02010D1C
	push {r3-r7, lr}
	sub sp, #0x20
	add r4, r1, #0x0
	ldr r1, [r4, #0x0]
	add r5, r0, #0x0
	str r1, [r5, #0xc]
	ldr r1, [r4, #0x0]
	str r3, [sp, #0x1c]
	str r1, [r5, #0x10]
	str r2, [sp, #0x18]
	ldr r2, [r4, #0x4]
	ldr r1, [r4, #0x0]
	ldr r6, [sp, #0x38]
	sub r1, r2, r1
	str r1, [r5, #0x14]
	ldr r3, [sp, #0x44]
	mov r1, #0x2
	add r2, r6, #0x0
	ldr r7, [sp, #0x3c]
	bl FUN_0200F55C
	ldr r0, [sp, #0x18]
	mov r1, #0x0
	str r0, [r5, #0x18]
	ldr r0, [sp, #0x1c]
	str r1, [r5, #0x1c]
	str r0, [r5, #0x20]
	str r1, [r5, #0x24]
	ldr r0, [sp, #0x40]
	str r7, [r5, #0x30]
	str r0, [r5, #0x34]
	ldr r0, [sp, #0x44]
	str r0, [r5, #0x2c]
	ldrb r0, [r4, #0xa]
	str r0, [r5, #0x28]
	add r0, r5, #0x0
	bl FUN_02010E48
	ldr r0, _02010DE0 ; =FUN_0200F5F8
	ldr r2, _02010DE4 ; =0x000003FF
	add r1, r5, #0x0
	bl FUN_0200CA98
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200F5D8
	str r6, [sp, #0x0]
	mov r3, #0x0
	str r3, [sp, #0x4]
	str r3, [sp, #0x8]
	mov r0, #0xff
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x8]
	ldrb r2, [r4, #0x9]
	add r0, r7, #0x0
	bl FUN_0200F67C
	str r6, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0xff
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	mov r3, #0x1
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x8]
	ldrb r2, [r4, #0x9]
	add r0, r7, #0x0
	bl FUN_0200F67C
	ldr r3, [r5, #0x28]
	add r0, r7, #0x0
	mov r1, #0x3
	add r2, r6, #0x0
	bl FUN_0200F6E4
	ldr r0, [sp, #0x44]
	ldr r2, _02010DE8 ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x34]
	add r1, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0200E6CC
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_02010DE0: .word FUN_0200F5F8
_02010DE4: .word 0x000003FF
_02010DE8: .word FUN_0200F330

	thumb_func_start FUN_02010DEC
FUN_02010DEC: ; 0x02010DEC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x24]
	add r1, r0, #0x1
	str r1, [r4, #0x24]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	blt _02010E36
	mov r0, #0x0
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x1c]
	add r1, r0, #0x1
	ldr r0, [r4, #0x18]
	cmp r1, r0
	bgt _02010E28
	str r1, [r4, #0x1c]
	add r0, r4, #0x0
	ldr r2, [r4, #0x18]
	add r0, #0xc
	bl FUN_02010F14
	add r0, r4, #0x0
	bl FUN_02010E48
	ldr r0, _02010E3C ; =FUN_0200F5F8
	ldr r2, _02010E40 ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _02010E36
_02010E28:
	ldr r0, [r4, #0x34]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x2c]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_02010E36:
	mov r0, #0x0
	pop {r4, pc}
	nop
_02010E3C: .word FUN_0200F5F8
_02010E40: .word 0x000003FF

	thumb_func_start FUN_02010E44
FUN_02010E44: ; 0x02010E44
	bx lr
	.balign 4

	thumb_func_start FUN_02010E48
FUN_02010E48: ; 0x02010E48
	push {r4-r7, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	str r1, [sp, #0x8]
	mov r1, #0x0
	bl FUN_0200F5D8
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0200F5D8
	str r0, [sp, #0xc]
	add r5, r0, #0x0
	ldr r1, _02010F10 ; =0x00003FFF
	ldr r0, [sp, #0x8]
	ldr r6, [sp, #0x10]
	sub r0, r1, r0
	mov r7, #0x0
	str r0, [sp, #0x4]
_02010E76:
	mov r0, #0x60
	sub r0, r0, r7
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x0]
	bl FUN_0200F0D0
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x0]
	bl FUN_0200F0D0
	cmp r4, #0x7f
	ble _02010E94
	mov r4, #0x7f
_02010E94:
	cmp r0, #0x7f
	ble _02010E9A
	mov r0, #0x7f
_02010E9A:
	mov r1, #0x80
	sub r1, r1, r0
	lsl r1, r1, #0x10
	mov r2, #0x3
	asr r1, r1, #0x10
	lsl r2, r2, #0x8
	str r1, [sp, #0x14]
	strh r1, [r6, r2]
	mov r1, #0x80
	sub r1, r1, r4
	lsl r1, r1, #0x10
	asr r2, r1, #0x10
	mov r1, #0x12
	lsl r1, r1, #0x6
	strh r2, [r6, r1]
	mov r1, #0xbf
	sub r1, r1, r7
	mov r12, r2
	lsl r1, r1, #0x1
	ldr r2, [sp, #0x10]
	add r0, #0x80
	add r3, r2, r1
	str r1, [sp, #0x18]
	mov r2, #0x3
	ldr r1, [sp, #0x14]
	lsl r2, r2, #0x8
	strh r1, [r3, r2]
	mov r1, #0x12
	mov r2, r12
	lsl r1, r1, #0x6
	strh r2, [r3, r1]
	add r4, #0x80
	lsl r1, r4, #0x10
	asr r2, r1, #0x10
	mov r1, #0x3
	lsl r1, r1, #0x8
	lsl r0, r0, #0x10
	strh r2, [r5, r1]
	asr r1, r0, #0x10
	mov r0, #0x12
	lsl r0, r0, #0x6
	strh r1, [r5, r0]
	ldr r3, [sp, #0xc]
	ldr r0, [sp, #0x18]
	add r7, r7, #0x1
	add r0, r3, r0
	mov r3, #0x3
	lsl r3, r3, #0x8
	strh r2, [r0, r3]
	mov r2, #0x12
	lsl r2, r2, #0x6
	strh r1, [r0, r2]
	add r6, r6, #0x2
	add r5, r5, #0x2
	cmp r7, #0x60
	blt _02010E76
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_02010F10: .word 0x00003FFF

	thumb_func_start FUN_02010F14
FUN_02010F14: ; 0x02010F14
	push {r4, lr}
	add r4, r0, #0x0
	ldr r3, [r4, #0x8]
	add r0, r3, #0x0
	mul r0, r1
	add r1, r2, #0x0
	bl _s32_div_f
	ldr r1, [r4, #0x4]
	add r0, r0, r1
	str r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02010F2C
FUN_02010F2C: ; 0x02010F2C
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r1, #0xcd
	ldr r0, [r5, #0x20]
	lsl r1, r1, #0x2
	bl FUN_02016998
	mov r2, #0xcd
	str r0, [r5, #0x14]
	mov r1, #0x0
	lsl r2, r2, #0x2
	bl Call_FillMemWithValue
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_02010FD0
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02010F70
FUN_02010F70: ; 0x02010F70
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _02010F88
	cmp r0, #0x2
	beq _02010FAA
	cmp r0, #0x3
	beq _02010FC4
	b _02010FC8
_02010F88:
	add r0, r4, #0x0
	bl FUN_020110BC
	cmp r0, #0x1
	bne _02010FCC
	mov r1, #0xc9
	lsl r1, r1, #0x2
	ldr r0, [r4, r1]
	add r1, #0x8
	ldr r1, [r4, r1]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010FCC
_02010FAA:
	add r0, r4, #0x0
	bl FUN_0201111C
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010FCC
_02010FC4:
	mov r6, #0x1
	b _02010FCC
_02010FC8:
	bl ErrorHandling
_02010FCC:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02010FD0
FUN_02010FD0: ; 0x02010FD0
	push {r3-r7, lr}
	sub sp, #0x20
	ldr r7, [sp, #0x38]
	str r3, [sp, #0x1c]
	mov r3, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x18]
	str r3, [sp, #0x0]
	add r1, r7, #0x0
	mov r2, #0x1
	add r5, r0, #0x0
	ldr r6, [sp, #0x3c]
	bl FUN_0200F6FC
	ldrb r0, [r4, #0x5]
	cmp r0, #0x0
	bne _0201100A
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0xc0
	bl Call_FillMemWithValue
	add r0, r5, #0x0
	add r0, #0xc0
	mov r1, #0x1
	mov r2, #0xc0
	bl Call_FillMemWithValue
	b _02011020
_0201100A:
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0xc0
	bl Call_FillMemWithValue
	add r0, r5, #0x0
	add r0, #0xc0
	mov r1, #0x0
	mov r2, #0xc0
	bl Call_FillMemWithValue
_02011020:
	mov r1, #0xc3
	lsl r1, r1, #0x2
	ldr r0, [r4, #0x0]
	add r3, r1, #0x0
	str r0, [r5, r1]
	ldrb r2, [r4, #0x4]
	add r0, r1, #0x4
	add r3, #0x8
	str r2, [r5, r0]
	add r0, r1, #0x0
	ldrb r2, [r4, #0x5]
	add r0, #0x18
	str r2, [r5, r0]
	add r0, r1, #0x0
	ldr r2, [sp, #0x44]
	add r0, #0x1c
	str r2, [r5, r0]
	ldr r0, [sp, #0x18]
	str r0, [r5, r3]
	add r3, r1, #0x0
	add r3, #0xc
	mov r0, #0x0
	str r0, [r5, r3]
	add r3, r1, #0x0
	ldr r0, [sp, #0x1c]
	add r3, #0x10
	str r0, [r5, r3]
	add r3, r1, #0x0
	add r3, #0x14
	mov r0, #0x0
	str r0, [r5, r3]
	add r0, r1, #0x0
	add r0, #0x20
	str r6, [r5, r0]
	ldr r0, [sp, #0x40]
	add r1, #0x24
	str r0, [r5, r1]
	add r1, r5, #0x0
	bl FUN_0200F758
	ldrb r0, [r4, #0x5]
	cmp r0, #0x1
	str r7, [sp, #0x0]
	bne _02011090
	mov r3, #0x0
	str r3, [sp, #0x4]
	str r3, [sp, #0x8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r6, #0x0
	mov r1, #0x20
	mov r2, #0x3f
	bl FUN_0200F67C
	b _020110A6
_02011090:
	mov r3, #0x0
	str r3, [sp, #0x4]
	str r3, [sp, #0x8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r6, #0x0
	mov r1, #0x3f
	mov r2, #0x20
	bl FUN_0200F67C
_020110A6:
	mov r3, #0xc9
	lsl r3, r3, #0x2
	ldr r3, [r5, r3]
	add r0, r6, #0x0
	mov r1, #0x1
	add r2, r7, #0x0
	bl FUN_0200F6E4
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020110BC
FUN_020110BC: ; 0x020110BC
	push {r4, lr}
	mov r2, #0x32
	add r4, r0, #0x0
	lsl r2, r2, #0x4
	ldr r1, [r4, r2]
	add r1, r1, #0x1
	str r1, [r4, r2]
	sub r1, r2, #0x4
	ldr r3, [r4, r2]
	ldr r1, [r4, r1]
	cmp r3, r1
	blt _02011116
	mov r1, #0x0
	str r1, [r4, r2]
	add r1, r2, #0x0
	sub r1, #0x8
	ldr r1, [r4, r1]
	add r3, r1, #0x1
	add r1, r2, #0x0
	sub r1, #0xc
	ldr r1, [r4, r1]
	cmp r3, r1
	bgt _02011102
	add r1, r2, #0x0
	sub r1, #0x8
	ldr r1, [r4, r1]
	sub r2, #0x8
	add r1, r1, #0x1
	str r1, [r4, r2]
	bl FUN_02011120
	add r0, r4, #0x0
	bl FUN_0200F740
	b _02011116
_02011102:
	add r0, r2, #0x0
	add r0, #0x10
	add r2, #0x8
	ldr r0, [r4, r0]
	ldr r2, [r4, r2]
	add r1, r4, #0x0
	bl FUN_0200F770
	mov r0, #0x1
	pop {r4, pc}
_02011116:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201111C
FUN_0201111C: ; 0x0201111C
	bx lr
	.balign 4

	thumb_func_start FUN_02011120
FUN_02011120: ; 0x02011120
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x31
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0201115A
	mov r7, #0x31
	add r4, r6, #0x0
	lsl r7, r7, #0x4
_02011136:
	mov r0, #0xc3
	lsl r0, r0, #0x2
	mov r2, #0xc6
	mov r3, #0xc5
	ldr r0, [r5, r0]
	lsl r2, r2, #0x2
	lsl r3, r3, #0x2
	ldr r2, [r5, r2]
	ldr r3, [r5, r3]
	add r0, r0, r4
	add r1, r5, #0x0
	bl FUN_0201115C
	ldr r0, [r5, r7]
	add r6, r6, #0x1
	add r4, r4, #0x3
	cmp r6, r0
	blt _02011136
_0201115A:
	pop {r3-r7, pc}

	thumb_func_start FUN_0201115C
FUN_0201115C: ; 0x0201115C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldrb r6, [r7, #0x0]
	ldrb r4, [r7, #0x1]
	add r5, r1, #0x0
	add r1, r3, #0x0
	sub r0, r4, r6
	mul r0, r2
	bl _s32_div_f
	add r0, r0, r6
	cmp r6, r4
	bhi _0201117C
	add r1, r6, #0x0
	ldrb r6, [r7, #0x2]
	b _0201118C
_0201117C:
	ldrb r2, [r7, #0x2]
	add r1, r4, #0x0
	add r4, r6, #0x0
	cmp r2, #0x0
	bne _0201118A
	mov r6, #0x1
	b _0201118C
_0201118A:
	mov r6, #0x0
_0201118C:
	cmp r1, r4
	bge _020111AA
	mov r2, #0x0
	mov r3, #0x1
_02011194:
	cmp r1, r0
	bne _020111A2
	cmp r6, #0x0
	bne _020111A0
	add r6, r3, #0x0
	b _020111A2
_020111A0:
	add r6, r2, #0x0
_020111A2:
	strb r6, [r5, r1]
	add r1, r1, #0x1
	cmp r1, r4
	blt _02011194
_020111AA:
	pop {r3-r7, pc}

	thumb_func_start FUN_020111AC
FUN_020111AC: ; 0x020111AC
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r1, #0xe2
	ldr r0, [r5, #0x20]
	lsl r1, r1, #0x2
	bl FUN_02016998
	mov r2, #0xe2
	mov r1, #0x0
	lsl r2, r2, #0x2
	str r0, [r5, #0x14]
	bl Call_FillMemWithValue
	add r1, r4, #0x0
	add r1, #0x23
	ldrb r1, [r1, #0x0]
	ldr r0, [r5, #0x14]
	cmp r1, #0x0
	ldr r1, [r5, #0x10]
	bne _020111F2
	str r1, [sp, #0x0]
	ldr r1, [r5, #0x18]
	str r1, [sp, #0x4]
	ldr r1, [r5, #0x1c]
	str r1, [sp, #0x8]
	ldr r1, [r5, #0x20]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	add r1, r4, #0x0
	bl FUN_0201127C
	b _0201120A
_020111F2:
	str r1, [sp, #0x0]
	ldr r1, [r5, #0x18]
	str r1, [sp, #0x4]
	ldr r1, [r5, #0x1c]
	str r1, [sp, #0x8]
	ldr r1, [r5, #0x20]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	add r1, r4, #0x0
	bl FUN_0201137C
_0201120A:
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02011214
FUN_02011214: ; 0x02011214
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0xc]
	mov r4, #0x0
	ldr r0, [r5, #0x14]
	cmp r1, #0x1
	beq _0201122C
	cmp r1, #0x2
	beq _02011258
	cmp r1, #0x3
	beq _0201126A
	b _0201126E
_0201122C:
	ldr r1, _02011278 ; =0x00000386
	ldrb r1, [r0, r1]
	cmp r1, #0x0
	bne _0201123C
	add r1, r5, #0x0
	bl FUN_02011308
	b _02011242
_0201123C:
	add r1, r5, #0x0
	bl FUN_020113EC
_02011242:
	cmp r0, #0x1
	bne _02011272
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x18]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02011272
_02011258:
	bl FUN_02016A18
	add r0, r4, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r4, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02011272
_0201126A:
	mov r4, #0x1
	b _02011272
_0201126E:
	bl ErrorHandling
_02011272:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_02011278: .word 0x00000386

	thumb_func_start FUN_0201127C
FUN_0201127C: ; 0x0201127C
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r5, r0, #0x0
	lsl r0, r6, #0xc
	ldr r2, [r4, #0x2c]
	add r7, r3, #0x0
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	add r2, r0, #0x0
	mov r0, #0x2
	mov r3, #0x0
	lsl r0, r0, #0xa
	add r0, r2, r0
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r2, r0, #0xc
	mov r0, #0xe1
	sub r1, r6, r2
	lsl r0, r0, #0x2
	strb r1, [r5, r0]
	sub r1, r0, #0x4
	str r4, [r5, r1]
	add r1, r4, #0x0
	add r1, #0x23
	ldrb r1, [r1, #0x0]
	add r0, r0, #0x2
	add r3, r7, #0x0
	strb r1, [r5, r0]
	ldr r0, [sp, #0x20]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_0200FE20
	add r0, r4, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020112EA
	add r4, #0x23
	ldrb r3, [r4, #0x0]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x20]
	mov r1, #0x1
	bl FUN_0200F6E4
	b _020112F8
_020112EA:
	add r4, #0x23
	ldrb r3, [r4, #0x0]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x20]
	mov r1, #0x2
	bl FUN_0200F6E4
_020112F8:
	ldr r0, _02011304 ; =0x00000385
	mov r1, #0x0
	strb r1, [r5, r0]
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02011304: .word 0x00000385

	thumb_func_start FUN_02011308
FUN_02011308: ; 0x02011308
	push {r4-r6, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	ldr r1, _02011378 ; =0x00000385
	add r5, r0, #0x0
	ldrb r1, [r5, r1]
	mov r6, #0x0
	cmp r1, #0x0
	beq _02011324
	cmp r1, #0x1
	beq _0201135A
	cmp r1, #0x2
	beq _02011370
	b _02011372
_02011324:
	bl FUN_0200FE90
	cmp r0, #0x1
	bne _02011372
	ldr r2, _02011378 ; =0x00000385
	ldrb r0, [r5, r2]
	sub r1, r2, #0x5
	add r0, r0, #0x1
	strb r0, [r5, r2]
	ldr r0, [r4, #0x10]
	sub r2, r2, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x20]
	str r0, [sp, #0xc]
	ldr r1, [r5, r1]
	add r0, r5, #0x0
	ldrb r2, [r5, r2]
	ldr r3, [r4, #0x8]
	add r0, #0x4c
	add r1, #0x24
	bl FUN_02010FD0
	b _02011372
_0201135A:
	add r0, #0x4c
	bl FUN_020110BC
	cmp r0, #0x1
	bne _02011372
	ldr r0, _02011378 ; =0x00000385
	mov r6, #0x1
	ldrb r1, [r5, r0]
	add r1, r1, #0x1
	strb r1, [r5, r0]
	b _02011372
_02011370:
	mov r6, #0x1
_02011372:
	add r0, r6, #0x0
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_02011378: .word 0x00000385

	thumb_func_start FUN_0201137C
FUN_0201137C: ; 0x0201137C
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r5, r0, #0x0
	lsl r0, r6, #0xc
	ldr r2, [r4, #0x2c]
	add r7, r3, #0x0
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	add r2, r0, #0x0
	mov r0, #0x2
	mov r3, #0x0
	lsl r0, r0, #0xa
	add r0, r2, r0
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	mov r1, #0xe1
	asr r0, r0, #0xc
	lsl r1, r1, #0x2
	strb r0, [r5, r1]
	ldrb r0, [r5, r1]
	sub r2, r6, r0
	sub r0, r1, #0x4
	str r4, [r5, r0]
	add r4, #0x23
	add r0, r1, #0x2
	ldrb r3, [r4, #0x0]
	sub r1, r1, #0x4
	strb r3, [r5, r0]
	ldr r0, [sp, #0x28]
	add r3, r7, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x30]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x34]
	str r0, [sp, #0xc]
	ldr r1, [r5, r1]
	add r0, r5, #0x0
	add r0, #0x4c
	add r1, #0x24
	bl FUN_02010FD0
	ldr r0, _020113E8 ; =0x00000385
	mov r1, #0x0
	strb r1, [r5, r0]
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_020113E8: .word 0x00000385

	thumb_func_start FUN_020113EC
FUN_020113EC: ; 0x020113EC
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	ldr r1, _0201147C ; =0x00000385
	add r5, r0, #0x0
	ldrb r1, [r5, r1]
	mov r6, #0x0
	cmp r1, #0x0
	beq _02011408
	cmp r1, #0x1
	beq _02011460
	cmp r1, #0x2
	beq _02011474
	b _02011476
_02011408:
	add r0, #0x4c
	bl FUN_020110BC
	cmp r0, #0x1
	bne _02011476
	ldr r2, _0201147C ; =0x00000385
	ldrb r0, [r5, r2]
	sub r1, r2, #0x5
	add r0, r0, #0x1
	strb r0, [r5, r2]
	ldr r0, [r4, #0x10]
	sub r2, r2, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0x4]
	ldrb r2, [r5, r2]
	ldr r1, [r5, r1]
	ldr r3, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_0200FE20
	mov r0, #0xe
	lsl r0, r0, #0x6
	ldr r3, [r5, r0]
	add r0, r3, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	ldr r0, [r4, #0x18]
	bne _02011452
	add r3, #0x23
	ldrb r3, [r3, #0x0]
	ldr r2, [r4, #0x10]
	mov r1, #0x1
	bl FUN_0200F6E4
	b _02011476
_02011452:
	add r3, #0x23
	ldrb r3, [r3, #0x0]
	ldr r2, [r4, #0x10]
	mov r1, #0x2
	bl FUN_0200F6E4
	b _02011476
_02011460:
	bl FUN_0200FE90
	cmp r0, #0x1
	bne _02011476
	ldr r0, _0201147C ; =0x00000385
	mov r6, #0x1
	ldrb r1, [r5, r0]
	add r1, r1, #0x1
	strb r1, [r5, r0]
	b _02011476
_02011474:
	mov r6, #0x1
_02011476:
	add r0, r6, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_0201147C: .word 0x00000385

	thumb_func_start FUN_02011480
FUN_02011480: ; 0x02011480
	cmp r1, #0x0
	ldr r1, _020114A4 ; =0xFFFF1FFF
	bne _02011496
	mov r3, #0x1
	lsl r3, r3, #0x1a
	ldr r2, [r3, #0x0]
	lsl r0, r0, #0xd
	and r1, r2
	orr r0, r1
	str r0, [r3, #0x0]
	bx lr
_02011496:
	ldr r3, _020114A8 ; =0x04001000
	lsl r0, r0, #0xd
	ldr r2, [r3, #0x0]
	and r1, r2
	orr r0, r1
	str r0, [r3, #0x0]
	bx lr
	.balign 4
_020114A4: .word 0xFFFF1FFF
_020114A8: .word 0x04001000

	thumb_func_start FUN_020114AC
FUN_020114AC: ; 0x020114AC
	push {r3-r4}
	cmp r2, #0x0
	bne _020114EE
	cmp r3, #0x0
	bne _020114D2
	ldr r2, _02011528 ; =0x04000048
	ldrh r3, [r2, #0x0]
	mov r2, #0x3f
	bic r3, r2
	add r2, r3, #0x0
	orr r2, r0
	cmp r1, #0x0
	beq _020114CA
	mov r0, #0x20
	orr r2, r0
_020114CA:
	ldr r0, _02011528 ; =0x04000048
	strh r2, [r0, #0x0]
	pop {r3-r4}
	bx lr
_020114D2:
	ldr r2, _0201152C ; =0x04001048
	ldrh r3, [r2, #0x0]
	mov r2, #0x3f
	bic r3, r2
	add r2, r3, #0x0
	orr r2, r0
	cmp r1, #0x0
	beq _020114E6
	mov r0, #0x20
	orr r2, r0
_020114E6:
	ldr r0, _0201152C ; =0x04001048
	strh r2, [r0, #0x0]
	pop {r3-r4}
	bx lr
_020114EE:
	cmp r3, #0x0
	ldr r2, _02011530 ; =0xFFFFC0FF
	bne _0201150E
	ldr r4, _02011528 ; =0x04000048
	lsl r0, r0, #0x8
	ldrh r3, [r4, #0x0]
	and r2, r3
	orr r2, r0
	cmp r1, #0x0
	beq _02011506
	lsr r0, r4, #0xd
	orr r2, r0
_02011506:
	ldr r0, _02011528 ; =0x04000048
	strh r2, [r0, #0x0]
	pop {r3-r4}
	bx lr
_0201150E:
	ldr r4, _0201152C ; =0x04001048
	lsl r0, r0, #0x8
	ldrh r3, [r4, #0x0]
	and r2, r3
	orr r2, r0
	cmp r1, #0x0
	beq _02011520
	lsr r0, r4, #0xd
	orr r2, r0
_02011520:
	ldr r0, _0201152C ; =0x04001048
	strh r2, [r0, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4
_02011528: .word 0x04000048
_0201152C: .word 0x04001048
_02011530: .word 0xFFFFC0FF

	thumb_func_start FUN_02011534
FUN_02011534: ; 0x02011534
	cmp r2, #0x0
	bne _02011552
	ldr r2, _0201156C ; =0x0400004A
	ldrh r3, [r2, #0x0]
	mov r2, #0x3f
	bic r3, r2
	add r2, r3, #0x0
	orr r2, r0
	cmp r1, #0x0
	beq _0201154C
	mov r0, #0x20
	orr r2, r0
_0201154C:
	ldr r0, _0201156C ; =0x0400004A
	strh r2, [r0, #0x0]
	bx lr
_02011552:
	ldr r2, _02011570 ; =0x0400104A
	ldrh r3, [r2, #0x0]
	mov r2, #0x3f
	bic r3, r2
	add r2, r3, #0x0
	orr r2, r0
	cmp r1, #0x0
	beq _02011566
	mov r0, #0x20
	orr r2, r0
_02011566:
	ldr r0, _02011570 ; =0x0400104A
	strh r2, [r0, #0x0]
	bx lr
	.balign 4
_0201156C: .word 0x0400004A
_02011570: .word 0x0400104A

	thumb_func_start FUN_02011574
FUN_02011574: ; 0x02011574
	push {r4-r5}
	add r4, r2, #0x0
	add r2, r3, #0x0
	ldr r3, [sp, #0x8]
	cmp r3, #0x0
	bne _020115D2
	ldr r3, [sp, #0xc]
	cmp r3, #0x0
	bne _020115AC
	lsl r0, r0, #0x8
	mov r3, #0xff
	add r5, r0, #0x0
	lsl r3, r3, #0x8
	lsl r0, r4, #0x18
	and r5, r3
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	add r4, r5, #0x0
	orr r4, r0
	ldr r0, _02011624 ; =0x04000040
	orr r1, r3
	strh r4, [r0, #0x0]
	strh r1, [r0, #0x4]
	pop {r4-r5}
	bx lr
_020115AC:
	lsl r0, r0, #0x8
	mov r3, #0xff
	add r5, r0, #0x0
	lsl r3, r3, #0x8
	lsl r0, r4, #0x18
	and r5, r3
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	add r4, r5, #0x0
	orr r4, r0
	ldr r0, _02011628 ; =0x04001040
	orr r1, r3
	strh r4, [r0, #0x0]
	strh r1, [r0, #0x4]
	pop {r4-r5}
	bx lr
_020115D2:
	ldr r3, [sp, #0xc]
	cmp r3, #0x0
	bne _020115FE
	lsl r0, r0, #0x8
	mov r3, #0xff
	add r5, r0, #0x0
	lsl r3, r3, #0x8
	lsl r0, r4, #0x18
	and r5, r3
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	add r4, r5, #0x0
	orr r4, r0
	ldr r0, _0201162C ; =0x04000042
	orr r1, r3
	strh r4, [r0, #0x0]
	strh r1, [r0, #0x4]
	pop {r4-r5}
	bx lr
_020115FE:
	lsl r0, r0, #0x8
	mov r3, #0xff
	add r5, r0, #0x0
	lsl r3, r3, #0x8
	lsl r0, r4, #0x18
	and r5, r3
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	add r4, r5, #0x0
	orr r4, r0
	ldr r0, _02011630 ; =0x04001042
	orr r1, r3
	strh r4, [r0, #0x0]
	strh r1, [r0, #0x4]
	pop {r4-r5}
	bx lr
	.balign 4
_02011624: .word 0x04000040
_02011628: .word 0x04001040
_0201162C: .word 0x04000042
_02011630: .word 0x04001042

	thumb_func_start FUN_02011634
FUN_02011634: ; 0x02011634
	push {r4, lr}
	lsl r3, r2, #0x3
	add r4, r0, r3
	str r1, [r0, r3]
	str r2, [r4, #0x4]
	ldr r0, _0201164C ; =FUN_020116CC
	add r1, r4, #0x0
	mov r2, #0x1
	bl FUN_0200CA98
	pop {r4, pc}
	nop
_0201164C: .word FUN_020116CC

	thumb_func_start FUN_02011650
FUN_02011650: ; 0x02011650
	push {r4-r6, lr}
	ldr r5, [sp, #0x10]
	add r0, #0x10
	lsl r4, r5, #0x5
	add r6, r0, r4
	lsl r0, r3, #0x4
	add r4, r6, r0
	str r1, [r6, r0]
	str r2, [r4, #0x4]
	str r3, [r4, #0x8]
	ldr r0, _02011674 ; =FUN_020116E0
	add r1, r4, #0x0
	mov r2, #0x1
	str r5, [r4, #0xc]
	bl FUN_0200CA98
	pop {r4-r6, pc}
	nop
_02011674: .word FUN_020116E0

	thumb_func_start FUN_02011678
FUN_02011678: ; 0x02011678
	push {r3-r5, lr}
	mov r4, #0xc
	add r0, #0x68
	mul r4, r3
	add r5, r0, r4
	str r1, [r0, r4]
	str r2, [r5, #0x4]
	ldr r0, _02011694 ; =FUN_020116FC
	add r1, r5, #0x0
	mov r2, #0x1
	str r3, [r5, #0x8]
	bl FUN_0200CA98
	pop {r3-r5, pc}
	.balign 4
_02011694: .word FUN_020116FC

	thumb_func_start FUN_02011698
FUN_02011698: ; 0x02011698
	push {r3-r7, lr}
	ldr r5, [sp, #0x20]
	add r7, r1, #0x0
	add r0, #0x80
	lsl r1, r5, #0x5
	add r6, r0, r1
	add r4, r2, #0x0
	ldr r0, [sp, #0x1c]
	add r2, r3, #0x0
	lsl r3, r0, #0x4
	add r1, r6, r3
	strh r7, [r6, r3]
	strh r4, [r1, #0x2]
	strh r2, [r1, #0x4]
	ldr r2, [sp, #0x18]
	strh r2, [r1, #0x6]
	str r0, [r1, #0x8]
	ldr r0, _020116C8 ; =FUN_02011714
	mov r2, #0x1
	str r5, [r1, #0xc]
	bl FUN_0200CA98
	pop {r3-r7, pc}
	nop
_020116C8: .word FUN_02011714

	thumb_func_start FUN_020116CC
FUN_020116CC: ; 0x020116CC
	push {r4, lr}
	add r4, r0, #0x0
	ldmia r1!, {r0-r1}
	bl FUN_02011480
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020116E0
FUN_020116E0: ; 0x020116E0
	push {r4, lr}
	add r3, r1, #0x0
	add r4, r0, #0x0
	ldr r0, [r3, #0x0]
	ldr r1, [r3, #0x4]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	bl FUN_020114AC
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020116FC
FUN_020116FC: ; 0x020116FC
	push {r4, lr}
	add r2, r1, #0x0
	add r4, r0, #0x0
	ldr r0, [r2, #0x0]
	ldr r1, [r2, #0x4]
	ldr r2, [r2, #0x8]
	bl FUN_02011534
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start FUN_02011714
FUN_02011714: ; 0x02011714
	push {r3-r5, lr}
	sub sp, #0x8
	add r3, r1, #0x0
	add r4, r0, #0x0
	ldr r0, [r3, #0x8]
	mov r1, #0x2
	str r0, [sp, #0x0]
	ldr r0, [r3, #0xc]
	mov r2, #0x4
	str r0, [sp, #0x4]
	mov r0, #0x0
	mov r5, #0x6
	ldrsh r0, [r3, r0]
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldrsh r3, [r3, r5]
	bl FUN_02011574
	add r0, r4, #0x0
	bl FUN_0200CAB4
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02011744
FUN_02011744: ; 0x02011744
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r1, #0x0
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r1, #0x68
	bl FUN_02016998
	str r0, [sp, #0x8]
	cmp r0, #0x0
	bne _0201175E
	bl ErrorHandling
_0201175E:
	ldr r4, [sp, #0x8]
	ldr r5, [sp, #0x8]
	mov r6, #0x0
	add r4, #0x30
_02011766:
	mov r0, #0x23
	add r1, r6, #0x0
	mov r2, #0x0
	add r3, r4, #0x0
	str r7, [sp, #0x0]
	bl FUN_02006C30
	str r0, [r5, #0x0]
	cmp r0, #0x0
	bne _0201177E
	bl ErrorHandling
_0201177E:
	add r6, r6, #0x1
	add r4, r4, #0x4
	add r5, r5, #0x4
	cmp r6, #0xc
	blt _02011766
	ldr r0, [sp, #0x4]
	mov r1, #0x14
	add r4, r0, #0x0
	mul r4, r1
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_02016998
	ldr r1, [sp, #0x8]
	cmp r0, #0x0
	str r0, [r1, #0x60]
	bne _020117A4
	bl ErrorHandling
_020117A4:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x8]
	add r2, r4, #0x0
	str r1, [r0, #0x64]
	ldr r0, [r0, #0x60]
	mov r1, #0x0
	bl Call_FillMemWithValue
	ldr r0, [sp, #0x8]
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_020117BC
FUN_020117BC: ; 0x020117BC
	push {r4-r6, lr}
	add r6, r0, #0x0
	bne _020117C6
	bl ErrorHandling
_020117C6:
	mov r4, #0x0
	add r5, r6, #0x0
_020117CA:
	ldr r0, [r5, #0x0]
	bl FUN_02016A18
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0xc
	blt _020117CA
	ldr r0, [r6, #0x60]
	bl FUN_02016A18
	add r0, r6, #0x0
	bl FUN_02016A18
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020117E8
FUN_020117E8: ; 0x020117E8
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	bne _020117F4
	bl ErrorHandling
_020117F4:
	ldr r0, [r5, #0x0]
	bl FUN_02011BA0
	add r4, r0, #0x0
	bne _02011802
	bl ErrorHandling
_02011802:
	ldr r0, [r5, #0x10]
	add r3, sp, #0x8
	str r0, [r4, #0x8]
	ldr r0, [r5, #0x18]
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x1c]
	str r0, [r4, #0x10]
	str r3, [sp, #0x14]
	str r3, [sp, #0x18]
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x2c]
	ldrb r0, [r1, #0x7]
	ldrb r1, [r1, #0x8]
	bl FUN_02011CA4
	add r6, r0, #0x0
	mov r1, #0x24
	ldr r0, [r5, #0x2c]
	mul r1, r6
	bl FUN_020169D8
	add r7, r0, #0x0
	mov r1, #0xc
	ldr r0, [r5, #0x2c]
	mul r1, r6
	bl FUN_02016998
	str r0, [r4, #0x0]
	str r6, [r4, #0x4]
	ldr r0, [r5, #0x28]
	add r1, sp, #0x8
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x2c]
	add r2, r7, #0x0
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x4]
	ldr r3, [r5, #0x14]
	bl FUN_02011D2C
	add r0, r5, #0x0
	add r1, sp, #0x8
	add r2, r7, #0x0
	add r3, r4, #0x0
	bl FUN_02011EAC
	add r0, r7, #0x0
	bl FUN_02016A18
	add r0, sp, #0x8
	bl FUN_02011FDC
	add r0, r4, #0x0
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02011870
FUN_02011870: ; 0x02011870
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201187A
	bl ErrorHandling
_0201187A:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02011884
	bl ErrorHandling
_02011884:
	add r0, r4, #0x0
	bl FUN_02011F00
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02011B90
	pop {r4, pc}

	thumb_func_start FUN_02011898
FUN_02011898: ; 0x02011898
	push {r4-r5, lr}
	sub sp, #0x14
	add r3, sp, #0x0
	add r5, r0, #0x0
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	add r4, r1, #0x0
	ldrb r0, [r5, #0x7]
	ldrb r1, [r5, #0x8]
	bl FUN_02011CA4
	add r0, sp, #0x0
	add r1, r4, #0x0
	bl FUN_02011E58
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_02011FDC
	add r0, r4, #0x0
	add sp, #0x14
	pop {r4-r5, pc}

	thumb_func_start FUN_020118C4
FUN_020118C4: ; 0x020118C4
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r7, r2, #0x0
	str r1, [sp, #0x0]
	cmp r5, #0x0
	bne _020118D6
	bl ErrorHandling
_020118D6:
	ldr r0, [sp, #0x0]
	str r0, [r5, #0xc]
	str r7, [r5, #0x10]
	lsl r0, r0, #0xc
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x8]
	lsl r7, r7, #0xc
	cmp r0, #0x0
	beq _020118F8
	bl FUN_0202011C
	ldr r2, [r0, #0x0]
	ldr r1, [sp, #0x0]
	ldr r0, [r0, #0x4]
	add r1, r1, r2
	str r1, [sp, #0x0]
	add r7, r7, r0
_020118F8:
	mov r6, #0x0
	str r6, [sp, #0xc]
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	ble _02011932
	add r4, r6, #0x0
_02011904:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x4]
	lsl r1, r0, #0xc
	ldr r0, [sp, #0x0]
	add r0, r0, r1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r1, sp, #0x4
	add r0, r0, r4
	ldr r0, [r0, #0x8]
	lsl r0, r0, #0xc
	add r0, r7, r0
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	bl FUN_02020044
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011904
_02011932:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011938
FUN_02011938: ; 0x02011938
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	bne _02011944
	bl ErrorHandling
_02011944:
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	beq _0201199E
	ldr r1, [r5, #0xc]
	lsl r1, r1, #0xc
	str r1, [sp, #0x0]
	ldr r1, [r5, #0x10]
	lsl r7, r1, #0xc
	bl FUN_0202011C
	ldr r2, [r0, #0x0]
	ldr r0, [r0, #0x4]
	mov r6, #0x0
	ldr r1, [sp, #0x0]
	str r6, [sp, #0xc]
	add r7, r7, r0
	add r1, r1, r2
	ldr r0, [r5, #0x4]
	str r1, [sp, #0x0]
	cmp r0, #0x0
	ble _0201199E
	add r4, r6, #0x0
_02011970:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x4]
	lsl r1, r0, #0xc
	ldr r0, [sp, #0x0]
	add r0, r0, r1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r1, sp, #0x4
	add r0, r0, r4
	ldr r0, [r0, #0x8]
	lsl r0, r0, #0xc
	add r0, r7, r0
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	bl FUN_02020044
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011970
_0201199E:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020119A4
FUN_020119A4: ; 0x020119A4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	cmp r5, #0x0
	bne _020119B4
	bl ErrorHandling
_020119B4:
	cmp r4, #0x0
	bne _020119BC
	bl ErrorHandling
_020119BC:
	cmp r6, #0x0
	bne _020119C4
	bl ErrorHandling
_020119C4:
	ldr r0, [r5, #0xc]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x10]
	str r0, [r6, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020119D0
FUN_020119D0: ; 0x020119D0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _020119DE
	bl ErrorHandling
_020119DE:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _020119FC
	add r4, r6, #0x0
_020119E8:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_020200A0
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _020119E8
_020119FC:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011A00
FUN_02011A00: ; 0x02011A00
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011A0E
	bl ErrorHandling
_02011A0E:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011A2C
	add r4, r6, #0x0
_02011A18:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_02020238
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011A18
_02011A2C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011A30
FUN_02011A30: ; 0x02011A30
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011A3E
	bl ErrorHandling
_02011A3E:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011A5C
	add r4, r6, #0x0
_02011A48:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_02020310
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011A48
_02011A5C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011A60
FUN_02011A60: ; 0x02011A60
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011A6E
	bl ErrorHandling
_02011A6E:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011A8C
	add r4, r6, #0x0
_02011A78:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_02020248
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011A78
_02011A8C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011A90
FUN_02011A90: ; 0x02011A90
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011A9E
	bl ErrorHandling
_02011A9E:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011ABC
	add r4, r6, #0x0
_02011AA8:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_020202A8
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011AA8
_02011ABC:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011AC0
FUN_02011AC0: ; 0x02011AC0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011ACE
	bl ErrorHandling
_02011ACE:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011AEC
	add r4, r6, #0x0
_02011AD8:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_020202DC
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011AD8
_02011AEC:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011AF0
FUN_02011AF0: ; 0x02011AF0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011AFE
	bl ErrorHandling
_02011AFE:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011B1C
	add r4, r6, #0x0
_02011B08:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_02020398
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011B08
_02011B1C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011B20
FUN_02011B20: ; 0x02011B20
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	ldr r0, [sp, #0x20]
	add r7, r1, #0x0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x24]
	ldrb r1, [r6, #0x7]
	str r0, [sp, #0x24]
	add r0, r3, #0x0
	add r0, r7, r0
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	cmp r1, r0
	bge _02011B42
	bl ErrorHandling
_02011B42:
	ldrb r2, [r6, #0x8]
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x20]
	add r0, r1, r0
	cmp r2, r0
	bge _02011B52
	bl ErrorHandling
_02011B52:
	ldr r0, [sp, #0x0]
	mov r4, #0x0
	cmp r0, #0x0
	ble _02011B8A
	lsl r0, r7, #0x5
	add r5, r4, #0x0
	str r0, [sp, #0x8]
_02011B60:
	ldrb r1, [r6, #0x7]
	ldr r0, [sp, #0x20]
	add r2, r1, #0x0
	add r0, r4, r0
	mul r2, r0
	ldr r0, [sp, #0x4]
	lsl r1, r5, #0x5
	add r2, r2, r0
	ldr r0, [sp, #0x24]
	lsl r2, r2, #0x5
	add r0, r0, r1
	ldr r1, [r6, #0xc]
	add r1, r1, r2
	ldr r2, [sp, #0x8]
	bl memcpy
	ldr r0, [sp, #0x0]
	add r4, r4, #0x1
	add r5, r5, r7
	cmp r4, r0
	blt _02011B60
_02011B8A:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02011B90
FUN_02011B90: ; 0x02011B90
	mov r2, #0x14
	mov r1, #0x0
_02011B94:
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _02011B94
	bx lr
	.balign 4

	thumb_func_start FUN_02011BA0
FUN_02011BA0: ; 0x02011BA0
	ldr r1, [r0, #0x64]
	mov r2, #0x0
	cmp r1, #0x0
	ble _02011BC4
	ldr r3, [r0, #0x60]
_02011BAA:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	bne _02011BBA
	ldr r1, [r0, #0x60]
	mov r0, #0x14
	mul r0, r2
	add r0, r1, r0
	bx lr
_02011BBA:
	ldr r1, [r0, #0x64]
	add r2, r2, #0x1
	add r3, #0x14
	cmp r2, r1
	blt _02011BAA
_02011BC4:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02011BC8
FUN_02011BC8: ; 0x02011BC8
	push {r3-r4}
	ldr r4, _02011BF0 ; =0x020ED398
	mov r3, #0x0
_02011BCE:
	ldrb r2, [r4, #0x0]
	cmp r2, r0
	bgt _02011BE0
	ldrb r2, [r4, #0x1]
	cmp r2, r1
	bgt _02011BE0
	add r0, r3, #0x0
	pop {r3-r4}
	bx lr
_02011BE0:
	add r3, r3, #0x1
	add r4, r4, #0x2
	cmp r3, #0xc
	blt _02011BCE
	mov r0, #0xc
	pop {r3-r4}
	bx lr
	nop
_02011BF0: .word 0x020ED398

	thumb_func_start FUN_02011BF4
FUN_02011BF4: ; 0x02011BF4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r2, #0x0
	bl FUN_02011FAC
	ldr r1, [r6, #0x10]
	add r4, r0, #0x0
	bl FUN_02011FF4
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	bl FUN_02011BC8
	str r0, [r4, #0x8]
	ldr r0, [r5, #0x4]
	ldr r1, _02011C9C ; =0x020ED398
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	ldr r6, _02011CA0 ; =0x020ED399
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x8]
	ldr r2, [r5, #0x8]
	lsl r3, r0, #0x1
	ldrb r0, [r1, r3]
	ldrb r3, [r6, r3]
	sub r2, r2, r0
	ldr r0, [r5, #0xc]
	sub r6, r0, r3
	cmp r2, #0x0
	ble _02011C5C
	str r0, [r5, #0x1c]
	str r2, [r5, #0x18]
	ldr r0, [r5, #0x0]
	str r0, [r5, #0x10]
	ldr r2, [r4, #0x8]
	ldr r0, [r5, #0x4]
	lsl r2, r2, #0x1
	ldrb r1, [r1, r2]
	add r0, r0, r1
	str r0, [r5, #0x14]
	add r0, r5, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02011C54
	bl ErrorHandling
_02011C54:
	add r0, r5, #0x0
	mov r1, #0x1
	add r0, #0x20
	strb r1, [r0, #0x0]
_02011C5C:
	cmp r6, #0x0
	ble _02011C72
	ldr r0, [r4, #0x8]
	ldr r2, [r5, #0x0]
	lsl r1, r0, #0x1
	ldr r0, _02011CA0 ; =0x020ED399
	ldrb r0, [r0, r1]
	add r0, r2, r0
	str r0, [r5, #0x0]
	str r6, [r5, #0xc]
	b _02011C96
_02011C72:
	add r0, r5, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02011C92
	add r3, r5, #0x0
	add r3, #0x10
	add r2, r5, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0x0
	add r5, #0x20
	strb r0, [r5, #0x0]
	b _02011C96
_02011C92:
	mov r0, #0x1
	pop {r4-r6, pc}
_02011C96:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_02011C9C: .word 0x020ED398
_02011CA0: .word 0x020ED399

	thumb_func_start FUN_02011CA4
FUN_02011CA4: ; 0x02011CA4
	push {r3-r7, lr}
	sub sp, #0x38
	add r7, r0, #0x0
	str r1, [sp, #0x0]
	add r5, r2, #0x0
	add r6, r3, #0x0
	cmp r7, #0x0
	bne _02011CB8
	bl ErrorHandling
_02011CB8:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02011CC2
	bl ErrorHandling
_02011CC2:
	ldr r0, [sp, #0x0]
	mov r4, #0x0
	str r0, [sp, #0x10]
	str r4, [sp, #0x4]
	str r4, [sp, #0x8]
	str r7, [sp, #0xc]
	add r0, sp, #0x24
	strb r4, [r0, #0x0]
	ldr r0, [sp, #0x0]
	str r4, [sp, #0x2c]
	str r7, [sp, #0x30]
	cmp r0, #0x0
	beq _02011D20
	add r7, sp, #0x4
_02011CDE:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x0]
	bl FUN_02011BC8
	lsl r1, r0, #0x1
	ldr r0, _02011D28 ; =0x020ED398
	add r0, r0, r1
	ldrb r0, [r0, #0x1]
	ldr r1, [sp, #0x4]
	add r1, r1, r0
	str r1, [sp, #0x28]
	ldr r1, [sp, #0x10]
	sub r1, r1, r0
	str r1, [sp, #0x34]
	str r0, [sp, #0x10]
_02011CFC:
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	add r4, r4, #0x1
	bl FUN_02011BF4
	cmp r0, #0x0
	beq _02011CFC
	add r3, sp, #0x28
	add r2, sp, #0x4
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [sp, #0x10]
	str r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02011CDE
_02011D20:
	add r0, r4, #0x0
	add sp, #0x38
	pop {r3-r7, pc}
	nop
_02011D28: .word 0x020ED398

	thumb_func_start FUN_02011D2C
FUN_02011D2C: ; 0x02011D2C
	push {r4-r7, lr}
	sub sp, #0x1c
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x30]
	str r1, [sp, #0x14]
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x34]
	add r5, r2, #0x0
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x30]
	add r6, r3, #0x0
	cmp r0, #0x1
	bne _02011D4E
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r1, [r0, #0x0]
	b _02011D52
_02011D4E:
	ldr r0, _02011D98 ; =0x04001000
	ldr r1, [r0, #0x0]
_02011D52:
	ldr r0, _02011D9C ; =0x00300010
	add r7, r1, #0x0
	and r7, r0
	add r0, r7, #0x0
	bl FUN_0201DED0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	ldr r4, [r0, #0xc]
	cmp r4, r0
	beq _02011D92
_02011D68:
	add r0, r5, #0x0
	bl FUN_020B1A24
	str r7, [sp, #0x0]
	ldr r0, [sp, #0x30]
	str r6, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x34]
	ldr r3, [sp, #0x18]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FUN_02011DA0
	add r6, r0, #0x0
	ldr r4, [r4, #0xc]
	ldr r0, [sp, #0x14]
	add r5, #0x24
	cmp r4, r0
	bne _02011D68
_02011D92:
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_02011D98: .word 0x04001000
_02011D9C: .word 0x00300010

	thumb_func_start FUN_02011DA0
FUN_02011DA0: ; 0x02011DA0
	push {r4-r7, lr}
	sub sp, #0x14
	add r6, r1, #0x0
	str r0, [sp, #0x8]
	ldr r0, [r6, #0x8]
	add r5, r2, #0x0
	lsl r1, r0, #0x1
	ldr r0, _02011E44 ; =0x020ED398
	ldrb r0, [r0, r1]
	str r0, [sp, #0x10]
	ldr r0, _02011E48 ; =0x020ED399
	ldrb r0, [r0, r1]
	ldr r1, [sp, #0x10]
	add r4, r1, #0x0
	mul r4, r0
	str r0, [sp, #0xc]
	cmp r4, r3
	bge _02011DC6
	add r4, r3, #0x0
_02011DC6:
	lsl r4, r4, #0x5
	ldr r0, [sp, #0x34]
	add r1, r4, #0x0
	bl FUN_020169D8
	add r7, r0, #0x0
	ldr r0, [r6, #0x4]
	ldr r1, [sp, #0x10]
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0xc]
	ldr r3, [r6, #0x0]
	bl FUN_02011B20
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl DC_FlushRange
	ldr r0, [sp, #0x30]
	cmp r0, #0x1
	bne _02011E08
	ldr r6, [sp, #0x2c]
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl GX_LoadOBJ
	mov r0, #0x1
	str r6, [r5, #0x4]
	lsl r0, r0, #0x1a
	ldr r1, [r0, #0x0]
	b _02011E1A
_02011E08:
	ldr r6, [sp, #0x2c]
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl GXS_LoadOBJ
	ldr r0, _02011E4C ; =0x04001000
	str r6, [r5, #0x8]
	ldr r1, [r0, #0x0]
_02011E1A:
	ldr r0, _02011E50 ; =0x00300010
	and r0, r1
	str r0, [r5, #0x20]
	ldr r0, _02011E54 ; =0x0000FFFF
	str r0, [r5, #0xc]
	str r0, [r5, #0x10]
	mov r0, #0x3
	str r0, [r5, #0x14]
	mov r0, #0x0
	str r0, [r5, #0x18]
	mov r0, #0x1
	str r0, [r5, #0x1c]
	ldr r0, [sp, #0x28]
	str r0, [r5, #0x20]
	add r0, r7, #0x0
	bl FUN_02016A18
	ldr r0, [sp, #0x2c]
	add r0, r0, r4
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02011E44: .word 0x020ED398
_02011E48: .word 0x020ED399
_02011E4C: .word 0x04001000
_02011E50: .word 0x00300010
_02011E54: .word 0x0000FFFF

	thumb_func_start FUN_02011E58
FUN_02011E58: ; 0x02011E58
	push {r3-r7, lr}
	add r4, r0, #0x0
	cmp r1, #0x1
	bne _02011E68
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r1, [r0, #0x0]
	b _02011E6C
_02011E68:
	ldr r0, _02011EA0 ; =0x04001000
	ldr r1, [r0, #0x0]
_02011E6C:
	ldr r0, _02011EA4 ; =0x00300010
	and r0, r1
	bl FUN_0201DED0
	ldr r2, [r4, #0xc]
	mov r3, #0x0
	cmp r2, r4
	beq _02011E9A
	ldr r1, _02011EA8 ; =0x020ED398
_02011E7E:
	ldr r5, [r2, #0x8]
	lsl r5, r5, #0x1
	add r7, r1, r5
	ldrb r6, [r1, r5]
	ldrb r5, [r7, #0x1]
	mul r5, r6
	cmp r5, r0
	bge _02011E90
	add r5, r0, #0x0
_02011E90:
	ldr r2, [r2, #0xc]
	lsl r5, r5, #0x5
	add r3, r3, r5
	cmp r2, r4
	bne _02011E7E
_02011E9A:
	add r0, r3, #0x0
	pop {r3-r7, pc}
	nop
_02011EA0: .word 0x04001000
_02011EA4: .word 0x00300010
_02011EA8: .word 0x020ED398

	thumb_func_start FUN_02011EAC
FUN_02011EAC: ; 0x02011EAC
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r0, r1, #0x0
	ldr r4, [r0, #0xc]
	str r1, [sp, #0x4]
	add r7, r2, #0x0
	add r6, r3, #0x0
	cmp r4, r0
	beq _02011EFC
	mov r5, #0x0
_02011EC2:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl FUN_02011F24
	ldr r1, [r6, #0x0]
	str r0, [r1, r5]
	ldr r0, [r6, #0x0]
	ldr r0, [r0, r5]
	cmp r0, #0x0
	bne _02011EDC
	bl ErrorHandling
_02011EDC:
	ldr r0, [r4, #0x0]
	add r7, #0x24
	lsl r1, r0, #0x3
	ldr r0, [r6, #0x0]
	add r0, r0, r5
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x4]
	lsl r1, r0, #0x3
	ldr r0, [r6, #0x0]
	add r0, r0, r5
	str r1, [r0, #0x8]
	ldr r4, [r4, #0xc]
	ldr r0, [sp, #0x4]
	add r5, #0xc
	cmp r4, r0
	bne _02011EC2
_02011EFC:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02011F00
FUN_02011F00: ; 0x02011F00
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011F20
	add r4, r6, #0x0
_02011F0E:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	bl FUN_0201FFC8
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011F0E
_02011F20:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02011F24
FUN_02011F24: ; 0x02011F24
	push {r4-r5, lr}
	sub sp, #0x44
	add r5, r0, #0x0
	mov r0, #0x0
	str r2, [sp, #0x0]
	str r0, [sp, #0x4]
	add r4, r1, #0x0
	ldr r1, [r5, #0xc]
	str r1, [sp, #0x8]
	ldr r1, [r4, #0x8]
	ldr r2, [r5, #0x0]
	lsl r1, r1, #0x2
	add r1, r2, r1
	ldr r1, [r1, #0x30]
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	ldr r2, [r5, #0x20]
	add r1, sp, #0x20
	strb r2, [r1, #0x0]
	ldr r1, [r5, #0x8]
	str r1, [sp, #0x24]
	add r1, sp, #0x0
	str r1, [sp, #0x28]
	ldr r1, [r5, #0x24]
	str r1, [sp, #0x38]
	ldr r1, [r5, #0x28]
	str r1, [sp, #0x3c]
	ldr r1, [r5, #0x2c]
	str r1, [sp, #0x40]
	str r0, [sp, #0x2c]
	str r0, [sp, #0x30]
	str r0, [sp, #0x34]
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	beq _02011F80
	bl FUN_0202011C
	add r3, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, sp, #0x2c
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
_02011F80:
	ldr r1, [r4, #0x0]
	ldr r2, [r5, #0x18]
	lsl r1, r1, #0x3
	add r1, r2, r1
	ldr r0, [sp, #0x2c]
	lsl r1, r1, #0xc
	add r0, r0, r1
	str r0, [sp, #0x2c]
	ldr r1, [r4, #0x4]
	ldr r2, [r5, #0x1c]
	lsl r1, r1, #0x3
	add r1, r2, r1
	ldr r0, [sp, #0x30]
	lsl r1, r1, #0xc
	add r0, r0, r1
	str r0, [sp, #0x30]
	add r0, sp, #0x24
	bl FUN_0201FF84
	add sp, #0x44
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_02011FAC
FUN_02011FAC: ; 0x02011FAC
	push {r4, lr}
	mov r1, #0x14
	bl FUN_020169D8
	add r4, r0, #0x0
	bne _02011FBC
	bl ErrorHandling
_02011FBC:
	mov r0, #0x0
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02011FC8
FUN_02011FC8: ; 0x02011FC8
	push {r4, lr}
	add r4, r0, #0x0
	bne _02011FD2
	bl ErrorHandling
_02011FD2:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02011FDC
FUN_02011FDC: ; 0x02011FDC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	cmp r0, r5
	beq _02011FF2
_02011FE6:
	ldr r4, [r0, #0xc]
	bl FUN_02011FC8
	add r0, r4, #0x0
	cmp r4, r5
	bne _02011FE6
_02011FF2:
	pop {r3-r5, pc}

	thumb_func_start FUN_02011FF4
FUN_02011FF4: ; 0x02011FF4
	ldr r2, [r1, #0xc]
	str r2, [r0, #0xc]
	str r1, [r0, #0x10]
	ldr r2, [r1, #0xc]
	str r0, [r2, #0x10]
	str r0, [r1, #0xc]
	bx lr
	.balign 4

	thumb_func_start FUN_02012004
FUN_02012004: ; 0x02012004
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	ldr r6, [sp, #0x20]
	str r1, [sp, #0x4]
	add r5, r2, #0x0
	add r4, r3, #0x0
	str r0, [sp, #0x24]
	mov r7, #0x0
_02012018:
	ldr r1, [r4, #0x0]
	ldr r0, [sp, #0x4]
	ldr r2, [r5, #0x0]
	add r0, r0, r1
	ldr r1, [sp, #0x0]
	add r1, r1, r2
	add r2, r6, #0x0
	bl memcpy
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0x24]
	add r7, r7, #0x1
	add r0, r1, r0
	str r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	add r0, r0, r6
	str r0, [r4, #0x0]
	cmp r7, #0x8
	blt _02012018
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02012044
FUN_02012044: ; 0x02012044
	push {r4-r6, lr}
	add r5, r3, #0x0
	bl LoadFromNarc_2
	add r4, r0, #0x0
	bne _02012054
	bl ErrorHandling
_02012054:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020B0088
	add r6, r0, #0x0
	cmp r5, #0x0
	bne _02012066
	bl ErrorHandling
_02012066:
	cmp r6, #0x0
	bne _0201206E
	bl ErrorHandling
_0201206E:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02012078
FUN_02012078: ; 0x02012078
	push {r4-r7, lr}
	sub sp, #0x2c
	ldr r4, [sp, #0x40]
	str r0, [sp, #0x8]
	add r6, r0, r2
	ldrh r0, [r4, #0x2]
	str r1, [sp, #0xc]
	add r5, r3, #0x0
	cmp r0, r6
	bge _02012090
	bl ErrorHandling
_02012090:
	ldr r0, [sp, #0xc]
	ldrh r1, [r4, #0x0]
	add r0, r0, r5
	str r0, [sp, #0x14]
	cmp r1, r0
	bge _020120A0
	bl ErrorHandling
_020120A0:
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x44]
	str r0, [sp, #0x1c]
	ldrh r0, [r4, #0x2]
	lsl r7, r0, #0x2
	ldr r0, [sp, #0xc]
	add r1, r0, #0x0
	mul r1, r7
	ldr r0, [sp, #0x8]
	str r1, [sp, #0x18]
	lsl r1, r0, #0x2
	ldr r0, [sp, #0x18]
	str r1, [sp, #0x10]
	add r0, r1, r0
	str r0, [sp, #0x28]
	mov r0, #0x0
	str r0, [sp, #0x24]
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bge _0201210A
_020120CC:
	ldr r4, [sp, #0x8]
	add r0, r4, #0x0
	cmp r0, r6
	bge _020120F8
	ldr r0, [sp, #0x18]
	lsl r1, r0, #0x3
	ldr r0, [sp, #0x10]
	add r5, r0, r1
_020120DC:
	str r5, [sp, #0x28]
	mov r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x1c]
	add r2, sp, #0x28
	add r3, sp, #0x24
	str r7, [sp, #0x4]
	bl FUN_02012004
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r6
	blt _020120DC
_020120F8:
	ldr r0, [sp, #0x18]
	add r0, r0, r7
	str r0, [sp, #0x18]
	ldr r0, [sp, #0xc]
	add r1, r0, #0x1
	ldr r0, [sp, #0x14]
	str r1, [sp, #0xc]
	cmp r1, r0
	blt _020120CC
_0201210A:
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02012110
FUN_02012110: ; 0x02012110
	push {r4-r5}
	sub sp, #0x8
	ldr r2, _02012148 ; =0x020ED3B0
	add r1, sp, #0x0
	ldr r3, [r2, #0x0]
	ldr r2, [r2, #0x4]
	str r3, [sp, #0x0]
	str r2, [sp, #0x4]
	ldr r2, _0201214C ; =0x000001EF
	mov r5, #0x0
	add r3, r2, #0x0
_02012126:
	ldr r4, [r1, #0x0]
	cmp r4, r3
	beq _02012140
	cmp r4, r0
	bne _02012138
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02012138:
	add r5, r5, #0x1
	add r1, r1, #0x4
	cmp r5, r2
	blt _02012126
_02012140:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r5}
	bx lr
	.balign 4
_02012148: .word 0x020ED3B0
_0201214C: .word 0x000001EF

	thumb_func_start FUN_02012150
FUN_02012150: ; 0x02012150
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r3, #0x0
	mov r3, #0x0
	str r3, [sp, #0x8]
	add r3, sp, #0x8
	bl FUN_02012044
	ldr r0, [sp, #0x8]
	ldr r0, [r0, #0x14]
	bl FUN_02008A74
	ldr r0, [sp, #0x34]
	bl FUN_02012110
	ldr r1, [sp, #0x30]
	cmp r1, #0x2
	bne _02012184
	cmp r0, #0x1
	bne _02012184
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x28]
	ldr r0, [r0, #0x14]
	ldr r2, [sp, #0x2c]
	bl FUN_02008904
_02012184:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x18]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x1c]
	str r0, [sp, #0x4]
	ldr r3, [sp, #0x20]
	add r0, r4, #0x0
	bl FUN_02012078
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0201219C
FUN_0201219C: ; 0x0201219C
	push {r4-r7, lr}
	sub sp, #0x24
	add r7, r1, #0x0
	add r5, r2, #0x0
	ldr r2, [sp, #0x3c]
	ldr r1, [sp, #0x40]
	add r6, r0, #0x0
	mul r1, r2
	add r0, r5, #0x0
	lsl r1, r1, #0x5
	str r3, [sp, #0x20]
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [sp, #0x38]
	ldr r3, [sp, #0x20]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x3c]
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x40]
	add r2, r5, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x44]
	str r4, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x4c]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x50]
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	bl FUN_02012150
	add r0, r4, #0x0
	add sp, #0x24
	pop {r4-r7, pc}

	thumb_func_start FUN_020121E8
FUN_020121E8: ; 0x020121E8
	push {r3-r7, lr}
	sub sp, #0x30
	str r3, [sp, #0x8]
	ldr r3, [sp, #0x48]
	str r3, [sp, #0x48]
	mov r3, #0x0
	str r3, [sp, #0x2c]
	bl LoadFromNarc_2
	str r0, [sp, #0x20]
	cmp r0, #0x0
	bne _02012204
	bl ErrorHandling
_02012204:
	ldr r0, [sp, #0x20]
	add r1, sp, #0x2c
	bl FUN_020B0088
	cmp r0, #0x0
	bne _02012214
	bl ErrorHandling
_02012214:
	ldr r1, [sp, #0x4c]
	ldr r0, [sp, #0x8]
	add r6, r0, r1
	ldr r0, [sp, #0x2c]
	ldrh r0, [r0, #0x2]
	cmp r0, r6
	bge _02012226
	bl ErrorHandling
_02012226:
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x48]
	add r0, r0, r1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x2c]
	ldrh r1, [r0, #0x0]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bge _0201223C
	bl ErrorHandling
_0201223C:
	ldr r0, [sp, #0x2c]
	ldr r0, [r0, #0x14]
	str r0, [sp, #0x1c]
	bl FUN_02008A74
	ldr r0, [sp, #0x54]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x2c]
	ldrh r0, [r0, #0x2]
	lsl r7, r0, #0x2
	ldr r0, [sp, #0x48]
	add r1, r0, #0x0
	mul r1, r7
	ldr r0, [sp, #0x8]
	str r1, [sp, #0x14]
	lsl r1, r0, #0x2
	ldr r0, [sp, #0x14]
	str r1, [sp, #0xc]
	add r0, r1, r0
	str r0, [sp, #0x28]
	mov r0, #0x0
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x48]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bge _020122AE
_02012270:
	ldr r4, [sp, #0x8]
	add r0, r4, #0x0
	cmp r0, r6
	bge _0201229C
	ldr r0, [sp, #0x14]
	lsl r1, r0, #0x3
	ldr r0, [sp, #0xc]
	add r5, r0, r1
_02012280:
	str r5, [sp, #0x28]
	mov r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r2, sp, #0x28
	add r3, sp, #0x24
	str r7, [sp, #0x4]
	bl FUN_02012004
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r6
	blt _02012280
_0201229C:
	ldr r0, [sp, #0x14]
	add r0, r0, r7
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x48]
	add r1, r0, #0x1
	ldr r0, [sp, #0x10]
	str r1, [sp, #0x48]
	cmp r1, r0
	blt _02012270
_020122AE:
	ldr r0, [sp, #0x20]
	bl FUN_02016A18
	add sp, #0x30
	pop {r3-r7, pc}

	thumb_func_start FUN_020122B8
FUN_020122B8: ; 0x020122B8
	push {r4-r7, lr}
	sub sp, #0x14
	add r7, r1, #0x0
	add r5, r2, #0x0
	ldr r2, [sp, #0x2c]
	ldr r1, [sp, #0x30]
	add r6, r0, #0x0
	mul r1, r2
	add r0, r5, #0x0
	lsl r1, r1, #0x5
	str r3, [sp, #0x10]
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [sp, #0x28]
	ldr r3, [sp, #0x10]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x2c]
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x30]
	add r2, r5, #0x0
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	str r4, [sp, #0xc]
	bl FUN_020121E8
	add r0, r4, #0x0
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_020122F4
FUN_020122F4: ; 0x020122F4
	push {r3-r7, lr}
	sub sp, #0x20
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x44]
	ldr r1, [sp, #0x38]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x4]
	str r0, [sp, #0x14]
	add r0, r2, #0x0
	add r7, r0, r1
	ldr r1, [sp, #0x3c]
	add r0, r3, #0x0
	add r0, r0, r1
	add r1, r3, #0x0
	str r3, [sp, #0x8]
	ldr r5, [sp, #0x40]
	str r0, [sp, #0x10]
	cmp r1, r0
	bge _0201236C
	add r0, r3, #0x0
	lsl r0, r0, #0x5
	str r0, [sp, #0xc]
	add r0, r2, #0x0
	lsl r0, r0, #0x5
	str r0, [sp, #0x1c]
_02012328:
	ldr r6, [sp, #0x4]
	add r0, r6, #0x0
	cmp r0, r7
	bge _0201235A
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0xc]
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [sp, #0x1c]
	add r4, r0, r2
_0201233C:
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0x14]
	mov r2, #0x20
	add r0, r0, r1
	ldr r1, [sp, #0x18]
	add r1, r1, r4
	bl memcpy
	ldr r0, [r5, #0x0]
	add r6, r6, #0x1
	add r0, #0x20
	str r0, [r5, #0x0]
	add r4, #0x20
	cmp r6, r7
	blt _0201233C
_0201235A:
	ldr r0, [sp, #0xc]
	add r0, #0x20
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x8]
	add r1, r0, #0x1
	ldr r0, [sp, #0x10]
	str r1, [sp, #0x8]
	cmp r1, r0
	blt _02012328
_0201236C:
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_02012370
FUN_02012370: ; 0x02012370
	push {r3-r4, lr}
	sub sp, #0x14
	add r4, r2, #0x0
	ldr r2, [r4, #0x8]
	str r2, [sp, #0x0]
	ldr r2, [r4, #0xc]
	str r2, [sp, #0x4]
	ldr r2, [sp, #0x20]
	str r3, [sp, #0x8]
	str r2, [sp, #0xc]
	ldr r2, [sp, #0x24]
	str r2, [sp, #0x10]
	ldr r2, [r4, #0x0]
	ldr r3, [r4, #0x4]
	bl FUN_020122F4
	add sp, #0x14
	pop {r3-r4, pc}

	thumb_func_start FUN_02012394
FUN_02012394: ; 0x02012394
	push {r4-r7, lr}
	sub sp, #0x7c
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x9c]
	mov r12, r3
	add r5, r2, #0x0
	ldr r6, [sp, #0x94]
	ldr r7, [sp, #0x98]
	ldr r3, _020123FC ; =0x020ED3D8
	str r1, [sp, #0x10]
	str r0, [sp, #0x9c]
	add r2, sp, #0x1c
	mov r4, #0xc
_020123AE:
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	sub r4, r4, #0x1
	bne _020123AE
	mov r0, #0x0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x90]
	ldr r1, [sp, #0x10]
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	ldr r0, [sp, #0xc]
	add r2, r5, #0x0
	mov r3, r12
	str r7, [sp, #0x8]
	bl FUN_020122B8
	str r0, [sp, #0x14]
	mov r4, #0x0
	add r5, sp, #0x1c
_020123D4:
	ldr r0, [sp, #0x14]
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x9c]
	add r2, r5, #0x0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r3, sp, #0x18
	bl FUN_02012370
	add r4, r4, #0x1
	add r5, #0x10
	cmp r4, #0x6
	blt _020123D4
	ldr r0, [sp, #0x14]
	bl FUN_02016A18
	add sp, #0x7c
	pop {r4-r7, pc}
	nop
_020123FC: .word 0x020ED3D8

	thumb_func_start FUN_02012400
FUN_02012400: ; 0x02012400
	push {r4, lr}
	sub sp, #0x10
	ldr r4, [r3, #0x4]
	str r4, [sp, #0x0]
	ldr r4, [r3, #0x8]
	str r4, [sp, #0x4]
	ldr r4, [r3, #0xc]
	str r4, [sp, #0x8]
	ldr r4, [sp, #0x18]
	str r4, [sp, #0xc]
	ldr r3, [r3, #0x0]
	bl FUN_02012394
	add sp, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02012420
FUN_02012420: ; 0x02012420
	push {r4-r7, lr}
	sub sp, #0x14
	ldr r4, _02012448 ; =0x020ED3B8
	add r5, r3, #0x0
	add r3, sp, #0x4
	add r7, r0, #0x0
	mov r12, r1
	add r6, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r7, #0x0
	mov r1, r12
	add r3, r6, #0x0
	str r5, [sp, #0x0]
	bl FUN_02012400
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02012448: .word 0x020ED3B8

	thumb_func_start FUN_0201244C
FUN_0201244C: ; 0x0201244C
	push {r3-r7, lr}
	add r6, r1, #0x0
	mov r1, #0x32
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r0, r7, #0x0
	lsl r1, r1, #0x6
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	add r3, r4, #0x0
	bl FUN_02012420
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02012470
FUN_02012470: ; 0x02012470
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r7, #0x0
	mov r1, #0x20
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl LoadFromNarc_2
	add r1, sp, #0x0
	add r5, r0, #0x0
	bl FUN_020B0138
	cmp r0, #0x1
	beq _0201249C
	bl ErrorHandling
_0201249C:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0xc]
	mov r2, #0x20
	bl MIi_CpuCopy16
	add r0, r5, #0x0
	bl FUN_02016A18
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020124B4
FUN_020124B4: ; 0x020124B4
	push {r4-r7, lr}
	sub sp, #0x8c
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0xac]
	mov r12, r3
	add r5, r2, #0x0
	ldr r6, [sp, #0xa4]
	ldr r7, [sp, #0xa8]
	ldr r3, _0201252C ; =0x020ED438
	str r1, [sp, #0x20]
	str r0, [sp, #0xac]
	add r2, sp, #0x2c
	mov r4, #0xc
_020124CE:
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	sub r4, r4, #0x1
	bne _020124CE
	mov r0, #0x0
	str r0, [sp, #0x28]
	ldr r0, [sp, #0xa0]
	ldr r1, [sp, #0x20]
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	ldr r0, [sp, #0xb0]
	str r7, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0xb4]
	add r2, r5, #0x0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xb8]
	mov r3, r12
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xbc]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	bl FUN_0201219C
	str r0, [sp, #0x24]
	mov r4, #0x0
	add r5, sp, #0x2c
_02012504:
	ldr r0, [sp, #0x24]
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xac]
	add r2, r5, #0x0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r3, sp, #0x28
	bl FUN_02012370
	add r4, r4, #0x1
	add r5, #0x10
	cmp r4, #0x6
	blt _02012504
	ldr r0, [sp, #0x24]
	bl FUN_02016A18
	add sp, #0x8c
	pop {r4-r7, pc}
	nop
_0201252C: .word 0x020ED438

	thumb_func_start FUN_02012530
FUN_02012530: ; 0x02012530
	push {r4, lr}
	sub sp, #0x20
	ldr r4, [r3, #0x4]
	str r4, [sp, #0x0]
	ldr r4, [r3, #0x8]
	str r4, [sp, #0x4]
	ldr r4, [r3, #0xc]
	str r4, [sp, #0x8]
	ldr r4, [sp, #0x28]
	str r4, [sp, #0xc]
	ldr r4, [sp, #0x2c]
	str r4, [sp, #0x10]
	ldr r4, [sp, #0x30]
	str r4, [sp, #0x14]
	ldr r4, [sp, #0x34]
	str r4, [sp, #0x18]
	ldr r4, [sp, #0x38]
	str r4, [sp, #0x1c]
	ldr r3, [r3, #0x0]
	bl FUN_020124B4
	add sp, #0x20
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02012560
FUN_02012560: ; 0x02012560
	push {r4-r7, lr}
	sub sp, #0x24
	ldr r4, _02012598 ; =0x020ED3C8
	add r5, r3, #0x0
	add r3, sp, #0x14
	add r7, r0, #0x0
	mov r12, r1
	add r6, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [sp, #0x38]
	str r5, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x3c]
	mov r1, r12
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x40]
	add r3, r6, #0x0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x44]
	str r0, [sp, #0x10]
	add r0, r7, #0x0
	bl FUN_02012530
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_02012598: .word 0x020ED3C8

	thumb_func_start FUN_0201259C
FUN_0201259C: ; 0x0201259C
	push {r3, lr}
	bl RTC_Init
	ldr r3, _020125CC ; =0x021C4808
	mov r0, #0x0
	add r2, r3, #0x0
	add r1, r0, #0x0
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r1, _020125D0 ; =0x021C4808
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	str r0, [r1, #0x8]
	add r0, r3, #0x0
	bl FUN_02012634
	pop {r3, pc}
	.balign 4
_020125CC: .word 0x021C4808
_020125D0: .word 0x021C4808

	thumb_func_start FUN_020125D4
FUN_020125D4: ; 0x020125D4
	push {r3, lr}
	ldr r0, _020125F4 ; =0x021C4808
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	bne _020125F2
	ldr r1, [r0, #0x8]
	add r1, r1, #0x1
	str r1, [r0, #0x8]
	cmp r1, #0xa
	ble _020125F2
	mov r1, #0x0
	str r1, [r0, #0x8]
	ldr r0, _020125F8 ; =0x021C4808
	bl FUN_02012634
_020125F2:
	pop {r3, pc}
	.balign 4
_020125F4: .word 0x021C4808
_020125F8: .word 0x021C4808

	thumb_func_start FUN_020125FC
FUN_020125FC: ; 0x020125FC
	push {r4, lr}
	add r4, r1, #0x0
	str r0, [r4, #0xc]
	cmp r0, #0x0
	beq _0201260A
	bl ErrorHandling
_0201260A:
	add r3, r4, #0x0
	mov r0, #0x1
	add r2, r4, #0x0
	add r3, #0x2c
	str r0, [r4, #0x0]
	ldmia r3!, {r0-r1}
	add r2, #0x10
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	add r3, r4, #0x0
	add r3, #0x3c
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x20
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	pop {r4, pc}

	thumb_func_start FUN_02012634
FUN_02012634: ; 0x02012634
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	add r1, r4, #0x0
	ldr r2, _02012658 ; =FUN_020125FC
	add r0, #0x2c
	add r1, #0x3c
	add r3, r4, #0x0
	bl RTC_GetDateTimeAsync
	str r0, [r4, #0xc]
	cmp r0, #0x0
	beq _02012656
	bl ErrorHandling
_02012656:
	pop {r4, pc}
	.balign 4
_02012658: .word FUN_020125FC

	thumb_func_start FUN_0201265C
FUN_0201265C: ; 0x0201265C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02012684 ; =0x021C4808
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _0201266E
	bl ErrorHandling
_0201266E:
	ldr r2, _02012688 ; =0x021C4818
	ldmia r2!, {r0-r1}
	stmia r5!, {r0-r1}
	ldmia r2!, {r0-r1}
	ldr r2, _0201268C ; =0x021C4828
	stmia r5!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4
_02012684: .word 0x021C4808
_02012688: .word 0x021C4818
_0201268C: .word 0x021C4828

	thumb_func_start FUN_02012690
FUN_02012690: ; 0x02012690
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020126AC ; =0x021C4808
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _020126A0
	bl ErrorHandling
_020126A0:
	ldr r2, _020126B0 ; =0x021C4828
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4
_020126AC: .word 0x021C4808
_020126B0: .word 0x021C4828

	thumb_func_start FUN_020126B4
FUN_020126B4: ; 0x020126B4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020126D0 ; =0x021C4808
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _020126C4
	bl ErrorHandling
_020126C4:
	ldr r2, _020126D4 ; =0x021C4818
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	pop {r4, pc}
	.balign 4
_020126D0: .word 0x021C4808
_020126D4: .word 0x021C4818

	thumb_func_start FUN_020126D8
FUN_020126D8: ; 0x020126D8
	push {r3-r4}
	ldr r4, _020126F8 ; =0x021C4828
	mov r0, #0x3c
	ldr r1, [r4, #0x4]
	ldr r3, [r4, #0x8]
	add r2, r1, #0x0
	mul r2, r0
	mov r0, #0xe1
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x4
	mul r0, r1
	add r0, r2, r0
	add r0, r3, r0
	pop {r3-r4}
	bx lr
	nop
_020126F8: .word 0x021C4828

	thumb_func_start FUN_020126FC
FUN_020126FC: ; 0x020126FC
	ldr r3, _02012704 ; =RTC_ConvertDateTimeToSecond
	ldr r0, _02012708 ; =0x021C4818
	ldr r1, _0201270C ; =0x021C4828
	bx r3
	.balign 4
_02012704: .word RTC_ConvertDateTimeToSecond
_02012708: .word 0x021C4818
_0201270C: .word 0x021C4828

	thumb_func_start FUN_02012710
FUN_02012710: ; 0x02012710
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r2, [r5, #0x4]
	ldr r0, _02012778 ; =0x020ED4B2
	lsl r1, r2, #0x1
	ldrh r0, [r0, r1]
	ldr r3, [r5, #0x8]
	add r4, r3, r0
	cmp r2, #0x3
	blo _02012752
	ldr r6, [r5, #0x0]
	mov r0, #0x1e
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1e
	sub r1, r1, r2
	ror r1, r0
	add r0, r2, r1
	bne _02012742
	add r0, r6, #0x0
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, #0x0
	bne _02012750
_02012742:
	mov r1, #0x19
	add r0, r6, #0x0
	lsl r1, r1, #0x4
	bl _s32_div_f
	cmp r1, #0x0
	bne _02012752
_02012750:
	add r4, r4, #0x1
_02012752:
	add r6, r5, #0x0
	add r3, sp, #0x0
	add r2, r3, #0x0
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r0, r2, #0x0
	bl RTC_ConvertDateToDay
	add r0, r5, #0x0
	bl RTC_ConvertDateToDay
	add r0, r4, #0x0
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_02012778: .word 0x020ED4B2

	thumb_func_start FUN_0201277C
FUN_0201277C: ; 0x0201277C
	push {r3, lr}
	bl FUN_02012794
	cmp r0, #0x3
	beq _0201278A
	cmp r0, #0x4
	bne _0201278E
_0201278A:
	mov r0, #0x1
	pop {r3, pc}
_0201278E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02012794
FUN_02012794: ; 0x02012794
	push {lr}
	sub sp, #0xc
	add r0, sp, #0x0
	bl FUN_02012690
	ldr r0, [sp, #0x0]
	bl FUN_020127A8
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_020127A8
FUN_020127A8: ; 0x020127A8
	push {r4, lr}
	add r4, r0, #0x0
	bmi _020127B2
	cmp r4, #0x18
	blt _020127B6
_020127B2:
	bl ErrorHandling
_020127B6:
	ldr r0, _020127BC ; =0x020ED4CC
	ldrb r0, [r0, r4]
	pop {r4, pc}
	.balign 4
_020127BC: .word 0x020ED4CC

	thumb_func_start FUN_020127C0
FUN_020127C0: ; 0x020127C0
	push {r4-r7, lr}
	sub sp, #0x24
	add r6, r3, #0x0
	ldr r3, _0201282C ; =0x020ED4A4
	add r4, r0, #0x0
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r2, sp, #0x14
	ldmia r3!, {r0-r1}
	str r2, [sp, #0x0]
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r3, _02012830 ; =0x020ED498
	add r2, sp, #0x8
	ldmia r3!, {r0-r1}
	str r2, [sp, #0x4]
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	ldr r1, [sp, #0x4]
	str r0, [r2, #0x0]
	ldr r0, [sp, #0x0]
	bl RTC_ConvertDateTimeToSecond
	add r2, r1, #0x0
	add r3, r0, #0x0
	mov r1, #0x0
	ldr r0, _02012834 ; =0xBC19137F
	eor r1, r2
	eor r0, r3
	orr r0, r1
	beq _02012804
	bl ErrorHandling
_02012804:
	sub r0, r4, r5
	mov r12, r7
	mov r0, r12
	sbc r0, r6
	bge _02012818
	sub r0, r5, r4
	sbc r6, r7
	add sp, #0x24
	add r1, r6, #0x0
	pop {r4-r7, pc}
_02012818:
	ldr r0, _02012834 ; =0xBC19137F
	mov r1, #0x0
	sub r0, r0, r4
	sbc r1, r7
	add r0, r5, r0
	adc r6, r1
	add r1, r6, #0x0
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0201282C: .word 0x020ED4A4
_02012830: .word 0x020ED498
_02012834: .word 0xBC19137F

	thumb_func_start FUN_02012838
FUN_02012838: ; 0x02012838
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0x3
	bl FUN_02016998
	cmp r0, #0x0
	beq _0201286E
	mov r2, #0x0
	cmp r5, #0x0
	bls _02012862
	add r3, r0, #0x0
	add r1, r2, #0x0
_02012856:
	str r1, [r3, #0x0]
	str r1, [r3, #0x4]
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, r5
	blo _02012856
_02012862:
	mov r1, #0x0
	lsl r2, r2, #0x3
	mvn r1, r1
	str r1, [r0, r2]
	add r1, r0, r2
	str r4, [r1, #0x4]
_0201286E:
	pop {r3-r5, pc}

	thumb_func_start FUN_02012870
FUN_02012870: ; 0x02012870
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201291C
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_02012880
FUN_02012880: ; 0x02012880
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r1, sp, #0x0
	add r7, r2, #0x0
	add r5, r3, #0x0
	bl FUN_020128E0
	add r4, r0, #0x0
	beq _0201289E
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_0200A914
	str r0, [r4, #0x0]
	str r5, [r4, #0x4]
_0201289E:
	pop {r3-r7, pc}

	thumb_func_start FUN_020128A0
FUN_020128A0: ; 0x020128A0
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r1, #0x0
	add r1, sp, #0x0
	add r5, r2, #0x0
	bl FUN_020128E0
	add r4, r0, #0x0
	beq _020128BE
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl FUN_02021ACC
	str r0, [r4, #0x0]
	str r5, [r4, #0x4]
_020128BE:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_020128C4
FUN_020128C4: ; 0x020128C4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r1, #0x0
	add r1, sp, #0x0
	bl FUN_020128E0
	cmp r0, #0x0
	beq _020128DC
	ldr r1, [r4, #0x0]
	str r1, [r0, #0x0]
	ldr r1, [r4, #0x4]
	str r1, [r0, #0x4]
_020128DC:
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_020128E0
FUN_020128E0: ; 0x020128E0
	push {r4, lr}
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	beq _02012900
	mov r2, #0x0
	mvn r2, r2
_020128EC:
	cmp r3, r2
	bne _020128F8
	bl ErrorHandling
	mov r0, #0x0
	pop {r4, pc}
_020128F8:
	add r0, #0x8
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	bne _020128EC
_02012900:
	mov r2, #0x0
	mvn r2, r2
	add r4, r0, #0x0
	cmp r3, r2
	beq _02012912
_0201290A:
	add r0, #0x8
	ldr r3, [r0, #0x0]
	cmp r3, r2
	bne _0201290A
_02012912:
	ldr r0, [r0, #0x4]
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201291C
FUN_0201291C: ; 0x0201291C
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0x0
	ldr r1, [r5, #0x0]
	mvn r0, r0
	cmp r1, r0
	beq _02012942
	mov r4, #0x0
	add r6, r0, #0x0
_0201292E:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02012942
	bl FUN_02021A20
	str r4, [r5, #0x0]
	add r5, #0x8
	ldr r0, [r5, #0x0]
	cmp r0, r6
	bne _0201292E
_02012942:
	pop {r4-r6, pc}

	thumb_func_start FUN_02012944
FUN_02012944: ; 0x02012944
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0xc
	add r4, r2, #0x0
	bl FUN_02016998
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	strb r1, [r0, #0x8]
	strb r1, [r0, #0x9]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	mov r1, #0x1
	strb r1, [r0, #0x9]
	str r5, [r0, #0x0]
	str r4, [r0, #0x4]
	pop {r3-r5, pc}

	thumb_func_start FUN_02012974
FUN_02012974: ; 0x02012974
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201297E
	bl ErrorHandling
_0201297E:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02012988
FUN_02012988: ; 0x02012988
	push {r4, lr}
	add r4, r0, #0x0
	bne _02012992
	bl ErrorHandling
_02012992:
	ldrb r0, [r4, #0x8]
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201299C
FUN_0201299C: ; 0x0201299C
	push {r4, lr}
	add r4, r0, #0x0
	bne _020129A6
	bl ErrorHandling
_020129A6:
	ldrb r1, [r4, #0x8]
	mov r0, #0x1
	eor r0, r1
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020129B4
FUN_020129B4: ; 0x020129B4
	cmp r0, #0x0
	beq _020129C6
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _020129C6
	ldrb r2, [r0, #0x8]
	mov r1, #0x1
	eor r1, r2
	strb r1, [r0, #0x8]
_020129C6:
	bx lr

	thumb_func_start FUN_020129C8
FUN_020129C8: ; 0x020129C8
	push {r3, lr}
	mov r0, #0x0
	bl MI_StopDma
	mov r0, #0x0
	bl MI_WaitDma
	pop {r3, pc}

	thumb_func_start FUN_020129D8
FUN_020129D8: ; 0x020129D8
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	cmp r3, #0x1
	bne _020129F2
	mov r0, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl MI_HBlankDmaCopy32
	pop {r4-r6, pc}
_020129F2:
	mov r0, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl MI_HBlankDmaCopy16
	pop {r4-r6, pc}

	thumb_func_start FUN_02012A00
FUN_02012A00: ; 0x02012A00
	push {r3-r5, lr}
	ldr r1, _02012A2C ; =0x0000079C
	add r5, r0, #0x0
	bl FUN_02016998
	ldr r2, _02012A2C ; =0x0000079C
	mov r1, #0x0
	add r4, r0, #0x0
	bl Call_FillMemWithValue
	mov r2, #0x3
	lsl r2, r2, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r4, r2
	bl FUN_02012944
	mov r1, #0x6
	lsl r1, r1, #0x8
	str r0, [r4, r1]
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02012A2C: .word 0x0000079C

	thumb_func_start FUN_02012A30
FUN_02012A30: ; 0x02012A30
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r5, #0x0
	bne _02012A42
	bl ErrorHandling
_02012A42:
	ldr r0, _02012AB0 ; =0x00000604
	ldr r0, [r5, r0]
	cmp r0, #0x0
	beq _02012A4E
	bl ErrorHandling
_02012A4E:
	ldr r0, _02012AB4 ; =0x0000078C
	mov r2, #0x0
	strb r4, [r5, r0]
	add r1, r0, #0x1
	strb r6, [r5, r1]
	add r1, r0, #0x0
	add r1, #0xc
	strh r2, [r5, r1]
	add r2, sp, #0x8
	mov r1, #0x14
	ldrsh r2, [r2, r1]
	add r1, r0, #0x0
	add r1, #0xe
	strh r2, [r5, r1]
	add r1, r0, #0x4
	ldr r2, [sp, #0x20]
	add r0, #0x8
	str r2, [r5, r1]
	ldr r1, [sp, #0x24]
	ldr r3, [sp, #0x18]
	str r1, [r5, r0]
	ldr r0, _02012AB8 ; =0x0000060C
	mov r1, #0xc0
	add r0, r5, r0
	add r2, r7, #0x0
	bl FUN_02012B88
	ldr r0, _02012ABC ; =FUN_02012BE4
	ldr r2, [sp, #0x28]
	add r1, r5, #0x0
	bl FUN_0200CA44
	ldr r1, _02012AB0 ; =0x00000604
	mov r2, #0x3
	str r0, [r5, r1]
	ldr r0, _02012AC0 ; =0x00000794
	add r1, r5, #0x0
	ldr r0, [r5, r0]
	lsl r2, r2, #0x8
	bl MIi_CpuClear32
	ldr r0, _02012AC0 ; =0x00000794
	mov r2, #0x3
	lsl r2, r2, #0x8
	ldr r0, [r5, r0]
	add r1, r5, r2
	bl MIi_CpuClear32
	pop {r3-r7, pc}
	.balign 4
_02012AB0: .word 0x00000604
_02012AB4: .word 0x0000078C
_02012AB8: .word 0x0000060C
_02012ABC: .word FUN_02012BE4
_02012AC0: .word 0x00000794

	thumb_func_start FUN_02012AC4
FUN_02012AC4: ; 0x02012AC4
	push {r4, lr}
	add r4, r0, #0x0
	bne _02012ACE
	bl ErrorHandling
_02012ACE:
	ldr r0, _02012AF8 ; =0x00000604
	ldr r0, [r4, r0]
	cmp r0, #0x0
	beq _02012AF4
	bl FUN_0200CAB4
	ldr r0, _02012AF8 ; =0x00000604
	mov r1, #0x0
	str r1, [r4, r0]
	sub r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_02012988
	ldr r1, _02012AFC ; =0x00000794
	mov r2, #0x3
	ldr r1, [r4, r1]
	lsl r2, r2, #0x8
	bl Call_FillMemWithValue
_02012AF4:
	pop {r4, pc}
	nop
_02012AF8: .word 0x00000604
_02012AFC: .word 0x00000794

	thumb_func_start FUN_02012B00
FUN_02012B00: ; 0x02012B00
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02012AC4
	bl FUN_02012C90
	mov r0, #0x6
	lsl r0, r0, #0x8
	ldr r0, [r4, r0]
	bl FUN_02012974
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02012B20
FUN_02012B20: ; 0x02012B20
	mov r1, #0x6
	lsl r1, r1, #0x8
	ldr r3, _02012B2C ; =FUN_02012988
	ldr r0, [r0, r1]
	bx r3
	nop
_02012B2C: .word FUN_02012988

	thumb_func_start FUN_02012B30
FUN_02012B30: ; 0x02012B30
	push {r4, lr}
	add r4, r0, #0x0
	beq _02012B5E
	ldr r0, _02012B60 ; =0x00000604
	ldr r1, [r4, r0]
	cmp r1, #0x0
	beq _02012B5E
	sub r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_020129B4
	mov r0, #0x6
	lsl r0, r0, #0x8
	ldr r0, [r4, r0]
	bl FUN_02012988
	add r1, r0, #0x0
	ldr r0, _02012B64 ; =0x00000794
	mov r2, #0x3
	ldr r0, [r4, r0]
	lsl r2, r2, #0x8
	bl MIi_CpuClear32
_02012B5E:
	pop {r4, pc}
	.balign 4
_02012B60: .word 0x00000604
_02012B64: .word 0x00000794

	thumb_func_start FUN_02012B68
FUN_02012B68: ; 0x02012B68
	push {r4, lr}
	add r4, r0, #0x0
	beq _02012B80
	ldr r0, _02012B84 ; =0x00000604
	ldr r0, [r4, r0]
	cmp r0, #0x0
	beq _02012B80
	bl FUN_02012C90
	add r0, r4, #0x0
	bl FUN_02012C98
_02012B80:
	pop {r4, pc}
	nop
_02012B84: .word 0x00000604

	thumb_func_start FUN_02012B88
FUN_02012B88: ; 0x02012B88
	push {r4-r7, lr}
	sub sp, #0xc
	mov r4, #0x0
	add r7, r1, #0x0
	add r5, r0, #0x0
	add r6, r4, #0x0
	str r2, [sp, #0x0]
	cmp r7, #0x0
	bls _02012BD6
	asr r0, r3, #0x1f
	str r3, [sp, #0x4]
	str r0, [sp, #0x8]
_02012BA0:
	asr r0, r4, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02012BDC ; =0x020FFA38
	ldr r2, [sp, #0x4]
	ldrsh r0, [r0, r1]
	ldr r3, [sp, #0x8]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _02012BE0 ; =0x00000000
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r0, r0, #0xc
	strh r0, [r5, #0x0]
	ldr r0, [sp, #0x0]
	add r6, r6, #0x1
	add r0, r4, r0
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r5, r5, #0x2
	cmp r6, r7
	blo _02012BA0
_02012BD6:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02012BDC: .word 0x020FFA38
_02012BE0: .word 0x00000000

	thumb_func_start FUN_02012BE4
FUN_02012BE4: ; 0x02012BE4
	push {r3-r7, lr}
	mov r0, #0x6
	add r6, r1, #0x0
	lsl r0, r0, #0x8
	ldr r0, [r6, r0]
	bl FUN_02012988
	add r5, r0, #0x0
	ldr r0, _02012C80 ; =0x00000798
	mov r1, #0x64
	ldrsh r0, [r6, r0]
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	ldr r0, _02012C84 ; =0x0000078C
	ldrb r4, [r6, r0]
	add r0, r0, #0x1
	ldrb r0, [r6, r0]
	cmp r4, r0
	bgt _02012C4C
	lsl r0, r4, #0x2
	add r5, r5, r0
_02012C12:
	ldr r2, [r5, #0x0]
	lsl r0, r2, #0x10
	asr r7, r0, #0x10
	lsl r0, r3, #0x1
	add r1, r6, r0
	ldr r0, _02012C88 ; =0x0000060C
	ldrsh r0, [r1, r0]
	add r0, r7, r0
	lsl r0, r0, #0x10
	asr r1, r0, #0x10
	lsr r0, r2, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	lsr r1, r1, #0x10
	orr r0, r1
	stmia r5!, {r0}
	add r0, r3, #0x1
	mov r1, #0xc0
	bl _s32_div_f
	lsl r0, r1, #0x18
	lsr r3, r0, #0x18
	ldr r0, _02012C8C ; =0x0000078D
	add r4, r4, #0x1
	ldrb r0, [r6, r0]
	cmp r4, r0
	ble _02012C12
_02012C4C:
	ldr r1, _02012C80 ; =0x00000798
	add r0, r1, #0x2
	ldrsh r2, [r6, r1]
	ldrsh r0, [r6, r0]
	add r4, r6, r1
	add r0, r2, r0
	strh r0, [r4, #0x0]
	ldrsh r0, [r6, r1]
	mov r1, #0x4b
	lsl r1, r1, #0x8
	cmp r0, r1
	blt _02012C70
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	bl _s32_div_f
	strh r1, [r4, #0x0]
	pop {r3-r7, pc}
_02012C70:
	cmp r0, #0x0
	bge _02012C7C
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	add r0, r0, r1
	strh r0, [r4, #0x0]
_02012C7C:
	pop {r3-r7, pc}
	nop
_02012C80: .word 0x00000798
_02012C84: .word 0x0000078C
_02012C88: .word 0x0000060C
_02012C8C: .word 0x0000078D

	thumb_func_start FUN_02012C90
FUN_02012C90: ; 0x02012C90
	ldr r3, _02012C94 ; =FUN_020129C8
	bx r3
	.balign 4
_02012C94: .word FUN_020129C8

	thumb_func_start FUN_02012C98
FUN_02012C98: ; 0x02012C98
	push {r3-r5, lr}
	add r4, r0, #0x0
	bne _02012CA2
	bl ErrorHandling
_02012CA2:
	mov r0, #0x6
	lsl r0, r0, #0x8
	ldr r0, [r4, r0]
	bl FUN_0201299C
	mov r1, #0x3
	lsl r1, r1, #0x8
	add r5, r0, #0x0
	bl DC_FlushRange
	mov r1, #0x79
	lsl r1, r1, #0x4
	ldr r1, [r4, r1]
	add r0, r5, #0x0
	mov r2, #0x4
	mov r3, #0x1
	bl FUN_020129D8
	pop {r3-r5, pc}

	thumb_func_start FUN_02012CC8
FUN_02012CC8: ; 0x02012CC8
	mov r1, #0x0
	ldr r2, _02012CD8 ; =0x021C4858
	add r0, r1, #0x0
_02012CCE:
	add r1, r1, #0x1
	stmia r2!, {r0}
	cmp r1, #0x10
	blt _02012CCE
	bx lr
	.balign 4
_02012CD8: .word 0x021C4858

	thumb_func_start FUN_02012CDC
FUN_02012CDC: ; 0x02012CDC
	push {r3-r7, lr}
	sub sp, #0x10
	str r1, [sp, #0x8]
	ldr r1, _02012DD0 ; =0x021C4858
	add r7, r0, #0x0
	add r6, r2, #0x0
	str r3, [sp, #0xc]
	mov r5, #0x0
_02012CEC:
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _02012CFA
	add r5, r5, #0x1
	add r1, r1, #0x4
	cmp r5, #0x10
	blt _02012CEC
_02012CFA:
	cmp r5, #0x10
	blt _02012D04
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_02012D04:
	ldr r0, [sp, #0x2c]
	mov r1, #0xdc
	bl FUN_02016998
	add r4, r0, #0x0
	bne _02012D14
	bl ErrorHandling
_02012D14:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0xdc
	bl Call_FillMemWithValue
	add r2, r4, #0x0
	ldr r0, [sp, #0x8]
	str r7, [r4, #0x18]
	ldr r3, _02012DD4 ; =0x020ED4FC
	str r0, [r4, #0x1c]
	ldmia r3!, {r0-r1}
	add r2, #0x34
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	ldr r3, _02012DD8 ; =0x020ED4E4
	str r0, [r2, #0x0]
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x40
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	ldr r3, _02012DDC ; =0x020ED4F0
	str r0, [r2, #0x0]
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x4c
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	mov r1, #0x0
	str r0, [r2, #0x0]
	ldr r2, [sp, #0xc]
	add r0, r6, #0x0
	bl Call_FillMemWithValue
	ldr r0, [sp, #0xc]
	str r6, [r4, #0xc]
	str r6, [r4, #0x10]
	add r0, r6, r0
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	add r0, #0xda
	strb r5, [r0, #0x0]
	ldr r0, _02012DD0 ; =0x021C4858
	lsl r5, r5, #0x2
	str r4, [r0, r5]
	ldr r0, [sp, #0x28]
	cmp r0, #0x1
	bne _02012DA8
	ldr r0, [sp, #0x2c]
	bl FUN_0201EB64
	str r0, [r4, #0x20]
	mov r3, #0x0
	str r3, [r4, #0x24]
	str r3, [r4, #0x28]
	mov r0, #0x2
	str r3, [r4, #0x2c]
	lsl r0, r0, #0xc
	strh r0, [r4, #0x30]
	str r3, [sp, #0x0]
	ldr r0, [r4, #0x20]
	ldr r1, _02012DD4 ; =0x020ED4FC
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x30]
	ldr r0, _02012DDC ; =0x020ED4F0
	bl FUN_0201ED5C
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0xdb
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x20]
	bl FUN_0201EB8C
_02012DA8:
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x3f
	str r0, [sp, #0x4]
	ldr r0, _02012DE0 ; =0x020ED508
	mov r1, #0x14
	ldr r0, [r0, r5]
	mov r2, #0xc8
	mov r3, #0x5
	bl FUN_0208B4A0
	str r0, [r4, #0x0]
	ldr r1, _02012DD8 ; =0x020ED4E4
	add r0, r4, #0x0
	bl FUN_020133FC
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_02012DD0: .word 0x021C4858
_02012DD4: .word 0x020ED4FC
_02012DD8: .word 0x020ED4E4
_02012DDC: .word 0x020ED4F0
_02012DE0: .word 0x020ED508

	thumb_func_start FUN_02012DE4
FUN_02012DE4: ; 0x02012DE4
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020133D0
	add r0, r5, #0x0
	add r0, #0xd8
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	tst r0, r1
	beq _02012E02
	add r0, r5, #0x0
	add r0, #0x58
	bl FUN_020AE8CC
	b _02012E22
_02012E02:
	mov r0, #0x2
	tst r0, r1
	beq _02012E22
	mov r6, #0x0
	add r4, r5, #0x0
	add r7, r6, #0x0
_02012E0E:
	ldr r0, [r4, #0x58]
	cmp r0, #0x0
	beq _02012E1A
	bl FUN_020AF894
	str r7, [r4, #0x58]
_02012E1A:
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, #0x10
	blt _02012E0E
_02012E22:
	add r0, r5, #0x0
	add r0, #0xd8
	ldrb r1, [r0, #0x0]
	mov r0, #0x4
	tst r0, r1
	beq _02012E38
	add r0, r5, #0x0
	add r0, #0x98
	bl FUN_020AEC7C
	b _02012E60
_02012E38:
	mov r0, #0x8
	tst r0, r1
	beq _02012E60
	mov r6, #0x0
	add r4, r5, #0x0
	add r7, r6, #0x0
_02012E44:
	add r0, r4, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02012E58
	bl FUN_020AFA80
	add r0, r4, #0x0
	add r0, #0x98
	str r7, [r0, #0x0]
_02012E58:
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, #0x10
	blt _02012E44
_02012E60:
	add r0, r5, #0x0
	mov r1, #0x0
	add r0, #0xd8
	strb r1, [r0, #0x0]
	str r1, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _02012E78
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r5, #0x4]
_02012E78:
	ldr r2, _02012EA8 ; =0x021C4858
	mov r1, #0x0
_02012E7C:
	ldr r0, [r2, #0x0]
	cmp r0, r5
	bne _02012E8C
	ldr r0, _02012EA8 ; =0x021C4858
	mov r2, #0x0
	lsl r1, r1, #0x2
	str r2, [r0, r1]
	b _02012E94
_02012E8C:
	add r1, r1, #0x1
	add r2, r2, #0x4
	cmp r1, #0x10
	blt _02012E7C
_02012E94:
	ldr r0, [r5, #0x20]
	cmp r0, #0x0
	beq _02012E9E
	bl FUN_0201EB70
_02012E9E:
	add r0, r5, #0x0
	bl FUN_02016A18
	pop {r3-r7, pc}
	nop
_02012EA8: .word 0x021C4858

	thumb_func_start FUN_02012EAC
FUN_02012EAC: ; 0x02012EAC
	push {r3-r5, lr}
	ldr r5, _02012EC8 ; =0x021C4858
	mov r4, #0x0
_02012EB2:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02012EBC
	bl FUN_02012DE4
_02012EBC:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x10
	blt _02012EB2
	pop {r3-r5, pc}
	nop
_02012EC8: .word 0x021C4858

	thumb_func_start FUN_02012ECC
FUN_02012ECC: ; 0x02012ECC
	push {r4, lr}
	ldr r1, _02012EF4 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x8]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012EE4
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012EE4:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012EF0
	bl ErrorHandling
_02012EF0:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012EF4: .word 0x021C4850

	thumb_func_start FUN_02012EF8
FUN_02012EF8: ; 0x02012EF8
	push {r4, lr}
	ldr r1, _02012F20 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0xc]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012F10
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012F10:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012F1C
	bl ErrorHandling
_02012F1C:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012F20: .word 0x021C4850

	thumb_func_start FUN_02012F24
FUN_02012F24: ; 0x02012F24
	push {r4, lr}
	ldr r1, _02012F4C ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x10]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012F3C
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012F3C:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012F48
	bl ErrorHandling
_02012F48:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012F4C: .word 0x021C4850

	thumb_func_start FUN_02012F50
FUN_02012F50: ; 0x02012F50
	push {r4, lr}
	ldr r1, _02012F78 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x14]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012F68
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012F68:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012F74
	bl ErrorHandling
_02012F74:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012F78: .word 0x021C4850

	thumb_func_start FUN_02012F7C
FUN_02012F7C: ; 0x02012F7C
	push {r4, lr}
	ldr r1, _02012FA4 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x18]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012F94
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012F94:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012FA0
	bl ErrorHandling
_02012FA0:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012FA4: .word 0x021C4850

	thumb_func_start FUN_02012FA8
FUN_02012FA8: ; 0x02012FA8
	push {r4, lr}
	ldr r1, _02012FD0 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x1c]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012FC0
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012FC0:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012FCC
	bl ErrorHandling
_02012FCC:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012FD0: .word 0x021C4850

	thumb_func_start FUN_02012FD4
FUN_02012FD4: ; 0x02012FD4
	push {r4, lr}
	ldr r1, _02012FFC ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x20]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012FEC
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012FEC:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012FF8
	bl ErrorHandling
_02012FF8:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012FFC: .word 0x021C4850

	thumb_func_start FUN_02013000
FUN_02013000: ; 0x02013000
	push {r4, lr}
	ldr r1, _02013028 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x24]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02013018
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02013018:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02013024
	bl ErrorHandling
_02013024:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013028: .word 0x021C4850

	thumb_func_start FUN_0201302C
FUN_0201302C: ; 0x0201302C
	push {r4, lr}
	ldr r1, _02013054 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x28]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02013044
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02013044:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02013050
	bl ErrorHandling
_02013050:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013054: .word 0x021C4850

	thumb_func_start FUN_02013058
FUN_02013058: ; 0x02013058
	push {r4, lr}
	ldr r1, _02013080 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x2c]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02013070
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02013070:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _0201307C
	bl ErrorHandling
_0201307C:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013080: .word 0x021C4850

	thumb_func_start FUN_02013084
FUN_02013084: ; 0x02013084
	push {r4, lr}
	ldr r1, _020130AC ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x30]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _0201309C
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_0201309C:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _020130A8
	bl ErrorHandling
_020130A8:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_020130AC: .word 0x021C4850

	thumb_func_start FUN_020130B0
FUN_020130B0: ; 0x020130B0
	push {r4, lr}
	ldr r1, _020130D8 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x34]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _020130C8
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_020130C8:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _020130D4
	bl ErrorHandling
_020130D4:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_020130D8: .word 0x021C4850

	thumb_func_start FUN_020130DC
FUN_020130DC: ; 0x020130DC
	push {r4, lr}
	ldr r1, _02013104 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x38]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _020130F4
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_020130F4:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02013100
	bl ErrorHandling
_02013100:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013104: .word 0x021C4850

	thumb_func_start FUN_02013108
FUN_02013108: ; 0x02013108
	push {r4, lr}
	ldr r1, _02013130 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x3c]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02013120
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02013120:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _0201312C
	bl ErrorHandling
_0201312C:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013130: .word 0x021C4850

	thumb_func_start FUN_02013134
FUN_02013134: ; 0x02013134
	push {r4, lr}
	ldr r1, _0201315C ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x40]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _0201314C
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_0201314C:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02013158
	bl ErrorHandling
_02013158:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_0201315C: .word 0x021C4850

	thumb_func_start FUN_02013160
FUN_02013160: ; 0x02013160
	push {r4, lr}
	ldr r1, _02013188 ; =0x021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x44]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02013178
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02013178:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02013184
	bl ErrorHandling
_02013184:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013188: .word 0x021C4850

	thumb_func_start FUN_0201318C
FUN_0201318C: ; 0x0201318C
	ldr r3, _02013190 ; =LoadFromNarc_2
	bx r3
	.balign 4
_02013190: .word LoadFromNarc_2

	thumb_func_start FUN_02013194
FUN_02013194: ; 0x02013194
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	add r4, r2, #0x0
	add r7, r3, #0x0
	cmp r0, #0x0
	bne _020131A8
	bl ErrorHandling
_020131A8:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _020131B2
	bl ErrorHandling
_020131B2:
	add r0, r5, #0x0
	add r0, #0xd8
	strb r4, [r0, #0x0]
	mov r0, #0x1
	tst r0, r4
	beq _020131C8
	add r0, r5, #0x0
	add r0, #0x58
	bl FUN_020AE918
	b _020131DE
_020131C8:
	mov r0, #0x2
	tst r0, r4
	beq _020131DE
	mov r1, #0x0
	add r2, r5, #0x0
	add r0, r1, #0x0
_020131D4:
	add r1, r1, #0x1
	str r0, [r2, #0x58]
	add r2, r2, #0x4
	cmp r1, #0x10
	blt _020131D4
_020131DE:
	mov r0, #0x4
	tst r0, r4
	beq _020131EE
	add r0, r5, #0x0
	add r0, #0x98
	bl FUN_020AEC98
	b _02013208
_020131EE:
	mov r0, #0x8
	tst r0, r4
	beq _02013208
	mov r2, #0x0
	add r3, r5, #0x0
	add r1, r2, #0x0
_020131FA:
	add r0, r3, #0x0
	add r0, #0x98
	add r2, r2, #0x1
	add r3, r3, #0x4
	str r1, [r0, #0x0]
	cmp r2, #0x10
	blt _020131FA
_02013208:
	str r6, [r5, #0x4]
	cmp r7, #0x1
	bne _02013216
	add r0, r5, #0x0
	bl FUN_02013228
	pop {r3-r7, pc}
_02013216:
	ldr r0, _02013224 ; =FUN_02013268
	add r1, r5, #0x0
	mov r2, #0x5
	bl FUN_0200CA98
	pop {r3-r7, pc}
	nop
_02013224: .word FUN_02013268

	thumb_func_start FUN_02013228
FUN_02013228: ; 0x02013228
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	bl FUN_0208B128
	ldr r0, _02013264 ; =0x021C4850
	str r4, [r0, #0x0]
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x0]
	cmp r1, #0x0
	bne _02013246
	bl FUN_0208AF94
	b _0201324A
_02013246:
	bl FUN_0208B05C
_0201324A:
	ldr r1, [r4, #0x1c]
	ldr r0, [r4, #0x0]
	cmp r1, #0x0
	bne _02013258
	bl FUN_0208AF80
	b _0201325C
_02013258:
	bl FUN_0208AFA8
_0201325C:
	ldr r0, _02013264 ; =0x021C4850
	mov r1, #0x0
	str r1, [r0, #0x0]
	pop {r4, pc}
	.balign 4
_02013264: .word 0x021C4850

	thumb_func_start FUN_02013268
FUN_02013268: ; 0x02013268
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02013228
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201327C
FUN_0201327C: ; 0x0201327C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02013286
	bl ErrorHandling
_02013286:
	ldr r0, _020132B8 ; =0x021C4850
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02013292
	bl ErrorHandling
_02013292:
	ldr r0, _020132B8 ; =0x021C4850
	mov r1, #0x0
	ldr r3, [r0, #0x0]
	add r2, r3, #0x0
_0201329A:
	ldr r0, [r2, #0x58]
	cmp r0, #0x0
	bne _020132A8
	lsl r0, r1, #0x2
	add r0, r3, r0
	str r4, [r0, #0x58]
	pop {r4, pc}
_020132A8:
	add r1, r1, #0x1
	add r2, r2, #0x4
	cmp r1, #0x10
	blt _0201329A
	bl ErrorHandling
	pop {r4, pc}
	nop
_020132B8: .word 0x021C4850

	thumb_func_start FUN_020132BC
FUN_020132BC: ; 0x020132BC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020132C6
	bl ErrorHandling
_020132C6:
	ldr r0, _020132FC ; =0x021C4850
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020132D2
	bl ErrorHandling
_020132D2:
	ldr r0, _020132FC ; =0x021C4850
	mov r1, #0x0
	ldr r3, [r0, #0x0]
	add r2, r3, #0x0
_020132DA:
	add r0, r2, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020132EE
	lsl r0, r1, #0x2
	add r0, r3, r0
	add r0, #0x98
	str r4, [r0, #0x0]
	pop {r4, pc}
_020132EE:
	add r1, r1, #0x1
	add r2, r2, #0x4
	cmp r1, #0x10
	blt _020132DA
	bl ErrorHandling
	pop {r4, pc}
	.balign 4
_020132FC: .word 0x021C4850

	thumb_func_start FUN_02013300
FUN_02013300: ; 0x02013300
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x20]
	cmp r1, #0x0
	beq _0201331C
	add r0, #0xdb
	ldrb r0, [r0, #0x0]
	bl FUN_0201EE2C
	ldr r0, [r4, #0x20]
	bl FUN_0201EB8C
	bl FUN_0201EBA4
_0201331C:
	bl FUN_020B849C
	ldr r0, [r4, #0x0]
	ldr r1, _02013338 ; =0x021CED64
	bl FUN_0208AD80
	ldr r0, [r4, #0x20]
	cmp r0, #0x0
	beq _02013332
	bl FUN_0201EB98
_02013332:
	bl FUN_020B849C
	pop {r4, pc}
	.balign 4
_02013338: .word 0x021CED64

	thumb_func_start FUN_0201333C
FUN_0201333C: ; 0x0201333C
	ldr r3, _02013344 ; =0x0208AE48
	ldr r0, [r0, #0x0]
	bx r3
	nop
_02013344: .word 0x0208AE48

	thumb_func_start FUN_02013348
FUN_02013348: ; 0x02013348
	mov r0, #0x0
	ldr r3, _02013360 ; =0x021C4858
	add r2, r0, #0x0
_0201334E:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _02013356
	add r0, r0, #0x1
_02013356:
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, #0x10
	blt _0201334E
	bx lr
	.balign 4
_02013360: .word 0x021C4858

	thumb_func_start FUN_02013364
FUN_02013364: ; 0x02013364
	push {r4-r6, lr}
	mov r4, #0x0
	ldr r5, _02013384 ; =0x021C4858
	add r6, r4, #0x0
_0201336C:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02013378
	bl FUN_02013300
	add r4, r4, #0x1
_02013378:
	add r6, r6, #0x1
	add r5, r5, #0x4
	cmp r6, #0x10
	blt _0201336C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02013384: .word 0x021C4858

	thumb_func_start FUN_02013388
FUN_02013388: ; 0x02013388
	push {r4-r6, lr}
	mov r4, #0x0
	ldr r5, _020133A8 ; =0x021C4858
	add r6, r4, #0x0
_02013390:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0201339C
	bl FUN_0201333C
	add r4, r4, #0x1
_0201339C:
	add r6, r6, #0x1
	add r5, r5, #0x4
	cmp r6, #0x10
	blt _02013390
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_020133A8: .word 0x021C4858

	thumb_func_start FUN_020133AC
FUN_020133AC: ; 0x020133AC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020133C4 ; =0x021C4850
	str r3, [r0, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0208ACEC
	ldr r1, _020133C4 ; =0x021C4850
	mov r2, #0x0
	str r2, [r1, #0x4]
	str r0, [r4, #0x8]
	pop {r4, pc}
	.balign 4
_020133C4: .word 0x021C4850

	thumb_func_start FUN_020133C8
FUN_020133C8: ; 0x020133C8
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start FUN_020133D0
FUN_020133D0: ; 0x020133D0
	ldr r3, _020133D8 ; =0x0208AC14
	ldr r0, [r0, #0x0]
	bx r3
	nop
_020133D8: .word 0x0208AC14

	thumb_func_start FUN_020133DC
FUN_020133DC: ; 0x020133DC
	ldr r3, _020133E4 ; =0x0208AC58
	ldr r0, [r0, #0x0]
	bx r3
	nop
_020133E4: .word 0x0208AC58

	thumb_func_start FUN_020133E8
FUN_020133E8: ; 0x020133E8
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_020133EC
FUN_020133EC: ; 0x020133EC
	add r2, r0, #0x0
	add r2, #0x40
	add r3, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start FUN_020133FC
FUN_020133FC: ; 0x020133FC
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r3, r4, #0x0
	add r2, r5, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x40
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldr r1, [r5, #0x20]
	add r0, r4, #0x0
	bl FUN_0201EC58
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201341C
FUN_0201341C: ; 0x0201341C
	ldr r0, _02013424 ; =0x021C4850
	ldr r0, [r0, #0x4]
	bx lr
	nop
_02013424: .word 0x021C4850

	thumb_func_start FUN_02013428
FUN_02013428: ; 0x02013428
	ldr r2, _02013438 ; =0x020ED4E4
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr
	nop
_02013438: .word 0x020ED4E4

	thumb_func_start FUN_0201343C
FUN_0201343C: ; 0x0201343C
	ldr r0, [r0, #0x20]
	bx lr

	thumb_func_start FUN_02013440
FUN_02013440: ; 0x02013440
	add r0, #0xdb
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02013448
FUN_02013448: ; 0x02013448
	add r0, #0xdb
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02013450
FUN_02013450: ; 0x02013450
	ldr r0, [r0, #0x20]
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start FUN_02013458
FUN_02013458: ; 0x02013458
	push {r4-r7}
	ldr r0, [r0, #0x20]
	add r4, r1, #0x0
	ldrh r2, [r0, #0x1c]
	cmp r2, #0x0
	bne _0201346A
	mov r0, #0x0
	pop {r4-r7}
	bx lr
_0201346A:
	mov r1, #0x0
	cmp r2, #0x0
	ble _020134F4
	ldr r3, [r0, #0x18]
	ldr r7, _020134FC ; =0x020908DC
	ldr r0, _02013500 ; =0x020909A4
_02013476:
	cmp r3, #0x0
	beq _020134EC
	cmp r4, #0x5
	bhi _020134E6
	add r5, r4, r4
	add r5, pc
	ldrh r5, [r5, #0x6]
	lsl r5, r5, #0x10
	asr r5, r5, #0x10
	add pc, r5
_0201348A: ; jump table (using 16-bit offset)
	.short _02013496 - _0201348A - 2; case 0
	.short _020134A2 - _0201348A - 2; case 1
	.short _020134AE - _0201348A - 2; case 2
	.short _020134BC - _0201348A - 2; case 3
	.short _020134CA - _0201348A - 2; case 4
	.short _020134D8 - _0201348A - 2; case 5
_02013496:
	ldr r5, [r3, #0x0]
	cmp r5, r0
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134A2:
	ldr r5, [r3, #0x0]
	cmp r5, r7
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134AE:
	ldr r6, [r3, #0x0]
	ldr r5, _02013504 ; =0x02090858
	cmp r6, r5
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134BC:
	ldr r6, [r3, #0x0]
	ldr r5, _02013508 ; =0x02090780
	cmp r6, r5
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134CA:
	ldr r6, [r3, #0x0]
	ldr r5, _0201350C ; =0x02090664
	cmp r6, r5
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134D8:
	ldr r6, [r3, #0x0]
	ldr r5, _02013510 ; =0x020905D0
	cmp r6, r5
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134E6:
	mov r0, #0x0
	pop {r4-r7}
	bx lr
_020134EC:
	add r1, r1, #0x1
	add r3, #0x8
	cmp r1, r2
	blt _02013476
_020134F4:
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	nop
_020134FC: .word 0x020908DC
_02013500: .word 0x020909A4
_02013504: .word 0x02090858
_02013508: .word 0x02090780
_0201350C: .word 0x02090664
_02013510: .word 0x020905D0

	thumb_func_start FUN_02013514
FUN_02013514: ; 0x02013514
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	bl FUN_02013458
	cmp r0, #0x0
	beq _0201352E
	ldrh r1, [r4, #0x0]
	strh r1, [r0, #0x0]
	ldrh r1, [r4, #0x2]
	strh r1, [r0, #0x2]
	ldrh r1, [r4, #0x4]
	strh r1, [r0, #0x4]
_0201352E:
	pop {r4, pc}

	thumb_func_start FUN_02013530
FUN_02013530: ; 0x02013530
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x2
	bl FUN_02013458
	add r2, r0, #0x0
	beq _02013546
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r2, #0x0]
_02013546:
	pop {r4, pc}

	thumb_func_start FUN_02013548
FUN_02013548: ; 0x02013548
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	mov r1, #0x2
	bl FUN_02013458
	add r2, r0, #0x0
	bne _0201356E
	add r2, sp, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	str r0, [r2, #0x4]
	str r0, [r2, #0x8]
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	add sp, #0xc
	str r0, [r4, #0x0]
	pop {r3-r4, pc}
_0201356E:
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r4, #0x0]
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201357C
FUN_0201357C: ; 0x0201357C
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x2
	bl FUN_02013458
	cmp r0, #0x0
	beq _02013590
	mov r1, #0x0
	ldrsh r1, [r4, r1]
	strh r1, [r0, #0xc]
_02013590:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02013594
FUN_02013594: ; 0x02013594
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x2
	bl FUN_02013458
	cmp r0, #0x0
	bne _020135A8
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4, pc}
_020135A8:
	mov r1, #0xc
	ldrsh r0, [r0, r1]
	strh r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_020135B0
FUN_020135B0: ; 0x020135B0
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x3
	bl FUN_02013458
	cmp r0, #0x0
	beq _020135C2
	ldrh r1, [r4, #0x0]
	strh r1, [r0, #0x0]
_020135C2:
	pop {r4, pc}

	thumb_func_start FUN_020135C4
FUN_020135C4: ; 0x020135C4
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x3
	bl FUN_02013458
	cmp r0, #0x0
	bne _020135D8
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4, pc}
_020135D8:
	ldrh r0, [r0, #0x0]
	strh r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020135E0
FUN_020135E0: ; 0x020135E0
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x3
	bl FUN_02013458
	cmp r0, #0x0
	beq _020135F2
	ldrh r1, [r4, #0x0]
	strh r1, [r0, #0x2]
_020135F2:
	pop {r4, pc}

	thumb_func_start FUN_020135F4
FUN_020135F4: ; 0x020135F4
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x3
	bl FUN_02013458
	cmp r0, #0x0
	bne _02013608
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4, pc}
_02013608:
	ldrh r0, [r0, #0x2]
	strh r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02013610
FUN_02013610: ; 0x02013610
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x5
	bl FUN_02013458
	add r2, r0, #0x0
	beq _02013626
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r2, #0x0]
_02013626:
	pop {r4, pc}

	thumb_func_start FUN_02013628
FUN_02013628: ; 0x02013628
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	mov r1, #0x5
	bl FUN_02013458
	add r2, r0, #0x0
	bne _0201364E
	add r2, sp, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	str r0, [r2, #0x4]
	str r0, [r2, #0x8]
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	add sp, #0xc
	str r0, [r4, #0x0]
	pop {r3-r4, pc}
_0201364E:
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r4, #0x0]
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201365C
FUN_0201365C: ; 0x0201365C
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x5
	bl FUN_02013458
	cmp r0, #0x0
	beq _02013670
	mov r1, #0x0
	ldrsh r1, [r4, r1]
	strh r1, [r0, #0xc]
_02013670:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02013674
FUN_02013674: ; 0x02013674
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x5
	bl FUN_02013458
	cmp r0, #0x0
	bne _02013688
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4, pc}
_02013688:
	mov r1, #0xc
	ldrsh r0, [r0, r1]
	strh r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02013690
FUN_02013690: ; 0x02013690
	push {r3-r5, lr}
	mov r1, #0x8
	add r5, r0, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	beq _020136B2
	ldr r0, _020136B8 ; =0x0001020F
	add r1, r5, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x4
	bl FUN_020219F4
	ldr r1, _020136BC ; =0x020ED548
	str r0, [r4, #0x4]
	bl FUN_02021E28
_020136B2:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_020136B8: .word 0x0001020F
_020136BC: .word 0x020ED548

	thumb_func_start FUN_020136C0
FUN_020136C0: ; 0x020136C0
	push {r4, lr}
	add r4, r0, #0x0
	bne _020136CA
	bl ErrorHandling
_020136CA:
	cmp r4, #0x0
	beq _020136DE
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _020136D8
	bl FUN_02021A20
_020136D8:
	add r0, r4, #0x0
	bl FUN_02016A18
_020136DE:
	pop {r4, pc}

	thumb_func_start FUN_020136E0
FUN_020136E0: ; 0x020136E0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020136EE
	bl ErrorHandling
_020136EE:
	cmp r5, #0x0
	beq _020136F4
	str r4, [r5, #0x0]
_020136F4:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020136F8
FUN_020136F8: ; 0x020136F8
	push {r4-r6, lr}
	sub sp, #0x10
	add r6, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, [r6, #0x0]
	add r5, r1, #0x0
	str r0, [sp, #0x8]
	mov r1, #0x0
	add r4, r2, #0x0
	str r1, [sp, #0xc]
	ldr r2, [r6, #0x4]
	add r0, r5, #0x0
	add r3, r4, #0x0
	bl FUN_0201BDE0
	add r0, r5, #0x0
	bl FUN_02019548
	add sp, #0x10
	pop {r4-r6, pc}

	thumb_func_start FUN_02013724
FUN_02013724: ; 0x02013724
	ldr r1, _02013738 ; =0x0000FFFF
	mov r2, #0x0
	strh r1, [r0, #0x0]
_0201372A:
	add r2, r2, #0x1
	strh r1, [r0, #0x4]
	add r0, r0, #0x2
	cmp r2, #0x2
	blt _0201372A
	bx lr
	nop
_02013738: .word 0x0000FFFF

	thumb_func_start FUN_0201373C
FUN_0201373C: ; 0x0201373C
	strh r1, [r0, #0x0]
	mov r2, #0x0
	ldr r1, _02013750 ; =0x0000FFFF
	strh r2, [r0, #0x2]
_02013744:
	add r2, r2, #0x1
	strh r1, [r0, #0x4]
	add r0, r0, #0x2
	cmp r2, #0x2
	blt _02013744
	bx lr
	.balign 4
_02013750: .word 0x0000FFFF

	thumb_func_start FUN_02013754
FUN_02013754: ; 0x02013754
	push {r4, lr}
	mov r1, #0x4
	add r4, r0, #0x0
	bl FUN_0201373C
	mov r0, #0x5
	strh r0, [r4, #0x2]
	pop {r4, pc}

	thumb_func_start FUN_02013764
FUN_02013764: ; 0x02013764
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	cmp r6, #0x4
	blo _02013772
	bl ErrorHandling
_02013772:
	cmp r6, #0x4
	bhs _020137B8
	mov r0, #0xa
	add r4, r6, #0x0
	mul r4, r0
	ldr r1, _020137BC ; =0x020ED556
	add r0, r5, #0x0
	ldrb r1, [r1, r4]
	bl FUN_0201373C
	ldr r0, _020137C0 ; =0x020ED557
	mov r1, #0x0
	ldrb r0, [r0, r4]
	mvn r1, r1
	strh r0, [r5, #0x2]
	ldr r0, _020137C4 ; =0x020ED558
	ldrsh r0, [r0, r4]
	cmp r0, r1
	beq _020137A2
	ldr r1, _020137C8 ; =0x020ED55A
	ldrh r1, [r1, r4]
	bl FUN_02013A9C
	strh r0, [r5, #0x4]
_020137A2:
	ldr r0, _020137CC ; =0x020ED55C
	mov r1, #0x0
	ldrsh r0, [r0, r4]
	mvn r1, r1
	cmp r0, r1
	beq _020137B8
	ldr r1, _020137D0 ; =0x020ED55E
	ldrh r1, [r1, r4]
	bl FUN_02013A9C
	strh r0, [r5, #0x6]
_020137B8:
	pop {r4-r6, pc}
	nop
_020137BC: .word 0x020ED556
_020137C0: .word 0x020ED557
_020137C4: .word 0x020ED558
_020137C8: .word 0x020ED55A
_020137CC: .word 0x020ED55C
_020137D0: .word 0x020ED55E

	thumb_func_start FUN_020137D4
FUN_020137D4: ; 0x020137D4
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r0, r1, #0x0
	str r1, [sp, #0x4]
	bl FUN_0200AA80
	ldr r5, [sp, #0x0]
	ldr r7, _02013838 ; =0x0000FFFF
	add r6, r0, #0x0
	mov r4, #0x0
_020137EA:
	ldrh r2, [r5, #0x4]
	cmp r2, r7
	beq _02013800
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0200B518
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, #0x2
	blt _020137EA
_02013800:
	ldr r2, [sp, #0x0]
	mov r0, #0x1
	ldrh r2, [r2, #0x0]
	mov r1, #0x1a
	lsl r3, r2, #0x1
	ldr r2, _0201383C ; =0x020ED54C
	ldrh r2, [r2, r3]
	ldr r3, [sp, #0x4]
	bl FUN_0200A86C
	add r5, r0, #0x0
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0x4]
	ldrh r2, [r2, #0x2]
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0200A9C4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200A8B8
	add r0, r6, #0x0
	bl FUN_0200AB18
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02013838: .word 0x0000FFFF
_0201383C: .word 0x020ED54C

	thumb_func_start FUN_02013840
FUN_02013840: ; 0x02013840
	push {r4, lr}
	add r4, r0, #0x0
	add r3, r1, #0x0
	ldrh r1, [r4, #0x0]
	mov r0, #0x1a
	lsl r2, r1, #0x1
	ldr r1, _02013858 ; =0x020ED54C
	ldrh r1, [r1, r2]
	ldrh r2, [r4, #0x2]
	bl FUN_0200A738
	pop {r4, pc}
	.balign 4
_02013858: .word 0x020ED54C

	thumb_func_start FUN_0201385C
FUN_0201385C: ; 0x0201385C
	ldrh r1, [r0, #0x0]
	ldr r0, _0201386C ; =0x0000FFFF
	cmp r1, r0
	beq _02013868
	mov r0, #0x1
	bx lr
_02013868:
	mov r0, #0x0
	bx lr
	.balign 4
_0201386C: .word 0x0000FFFF

	thumb_func_start FUN_02013870
FUN_02013870: ; 0x02013870
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x0]
	ldrh r1, [r4, #0x2]
	bl FUN_020138A0
	mov r3, #0x0
	cmp r0, #0x0
	bls _02013896
	ldr r1, _0201389C ; =0x0000FFFF
_02013884:
	ldrh r2, [r4, #0x4]
	cmp r2, r1
	bne _0201388E
	mov r0, #0x0
	pop {r4, pc}
_0201388E:
	add r3, r3, #0x1
	add r4, r4, #0x2
	cmp r3, r0
	blo _02013884
_02013896:
	mov r0, #0x1
	pop {r4, pc}
	nop
_0201389C: .word 0x0000FFFF

	thumb_func_start FUN_020138A0
FUN_020138A0: ; 0x020138A0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x5
	blo _020138AE
	bl ErrorHandling
_020138AE:
	add r0, r5, #0x0
	bl FUN_02013974
	cmp r4, r0
	blo _020138BC
	bl ErrorHandling
_020138BC:
	ldr r1, _02013910 ; =0x020ED54C
	lsl r2, r5, #0x1
	ldrh r1, [r1, r2]
	mov r0, #0x1a
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_0200A738
	str r0, [sp, #0x0]
	bl FUN_02021F2C
	add r4, r0, #0x0
	ldrh r1, [r4, #0x0]
	ldr r0, _02013914 ; =0x0000FFFF
	mov r5, #0x0
	cmp r1, r0
	beq _02013904
	add r7, r0, #0x0
	sub r6, r0, #0x1
_020138E2:
	cmp r1, r6
	bne _020138FC
	add r0, r4, #0x0
	bl FUN_0201B8F8
	cmp r0, #0x0
	beq _020138F2
	add r5, r5, #0x1
_020138F2:
	add r0, r4, #0x0
	bl FUN_0201B8B8
	add r4, r0, #0x0
	b _020138FE
_020138FC:
	add r4, r4, #0x2
_020138FE:
	ldrh r1, [r4, #0x0]
	cmp r1, r7
	bne _020138E2
_02013904:
	ldr r0, [sp, #0x0]
	bl FUN_02021A20
	add r0, r5, #0x0
	pop {r3-r7, pc}
	nop
_02013910: .word 0x020ED54C
_02013914: .word 0x0000FFFF

	thumb_func_start FUN_02013918
FUN_02013918: ; 0x02013918
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02013920
FUN_02013920: ; 0x02013920
	ldrh r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02013924
FUN_02013924: ; 0x02013924
	ldrh r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02013928
FUN_02013928: ; 0x02013928
	push {r3-r4}
	ldrh r3, [r0, #0x0]
	ldrh r2, [r1, #0x0]
	cmp r3, r2
	bne _0201393A
	ldrh r3, [r0, #0x2]
	ldrh r2, [r1, #0x2]
	cmp r3, r2
	beq _02013940
_0201393A:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
_02013940:
	mov r4, #0x0
_02013942:
	ldrh r3, [r0, #0x4]
	ldrh r2, [r1, #0x4]
	cmp r3, r2
	beq _02013950
	mov r0, #0x0
	pop {r3-r4}
	bx lr
_02013950:
	add r4, r4, #0x1
	add r1, r1, #0x2
	add r0, r0, #0x2
	cmp r4, #0x2
	blt _02013942
	mov r0, #0x1
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02013960
FUN_02013960: ; 0x02013960
	ldrh r2, [r1, #0x0]
	strh r2, [r0, #0x0]
	ldrh r2, [r1, #0x2]
	strh r2, [r0, #0x2]
	ldrh r2, [r1, #0x4]
	strh r2, [r0, #0x4]
	ldrh r1, [r1, #0x6]
	strh r1, [r0, #0x6]
	bx lr
	.balign 4

	thumb_func_start FUN_02013974
FUN_02013974: ; 0x02013974
	cmp r0, #0x5
	bhs _0201397C
	mov r0, #0x14
	bx lr
_0201397C:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02013980
FUN_02013980: ; 0x02013980
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x5
	blo _02013990
	bl ErrorHandling
_02013990:
	strh r4, [r5, #0x0]
	strh r6, [r5, #0x2]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02013998
FUN_02013998: ; 0x02013998
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x2
	blo _020139A8
	bl ErrorHandling
_020139A8:
	lsl r0, r4, #0x1
	add r0, r5, r0
	strh r6, [r0, #0x4]
	pop {r4-r6, pc}

	thumb_func_start FUN_020139B0
FUN_020139B0: ; 0x020139B0
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x0]
	ldrh r1, [r4, #0x2]
	bl FUN_020138A0
	cmp r0, #0x2
	bhs _020139D0
	lsl r1, r0, #0x1
	add r2, r4, r1
	ldr r1, _020139D4 ; =0x0000FFFF
_020139C6:
	add r0, r0, #0x1
	strh r1, [r2, #0x4]
	add r2, r2, #0x2
	cmp r0, #0x2
	blo _020139C6
_020139D0:
	pop {r4, pc}
	nop
_020139D4: .word 0x0000FFFF

	thumb_func_start FUN_020139D8
FUN_020139D8: ; 0x020139D8
	push {r3-r7, lr}
	mov r1, #0x30
	add r6, r0, #0x0
	bl FUN_02016998
	ldr r4, _02013A0C ; =0x020ED5C0
	str r0, [sp, #0x0]
	mov r7, #0x0
	add r5, r0, #0x0
_020139EA:
	ldr r0, [sp, #0x0]
	mov r1, #0x1a
	str r6, [r0, #0x0]
	ldrh r2, [r4, #0x0]
	mov r0, #0x1
	add r3, r6, #0x0
	bl FUN_0200A86C
	str r0, [r5, #0x4]
	add r7, r7, #0x1
	add r4, r4, #0x2
	add r5, r5, #0x4
	cmp r7, #0xb
	blt _020139EA
	ldr r0, [sp, #0x0]
	pop {r3-r7, pc}
	nop
_02013A0C: .word 0x020ED5C0

	thumb_func_start FUN_02013A10
FUN_02013A10: ; 0x02013A10
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r4, #0x0
	add r5, r6, #0x0
_02013A18:
	ldr r0, [r5, #0x4]
	bl FUN_0200A8B8
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0xb
	blt _02013A18
	add r0, r6, #0x0
	bl FUN_02016A18
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02013A30
FUN_02013A30: ; 0x02013A30
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r2, #0x0
	add r0, r1, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	bl FUN_02013AEC
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x0]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x4]
	add r2, r4, #0x0
	bl FUN_0200A8E0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02013A58
FUN_02013A58: ; 0x02013A58
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	ldr r1, _02013A94 ; =0x0000FFFF
	cmp r0, r1
	beq _02013A88
	add r1, sp, #0x8
	add r2, sp, #0x4
	bl FUN_02013AEC
	ldr r0, [sp, #0x8]
	mov r3, #0x0
	lsl r1, r0, #0x1
	ldr r0, _02013A98 ; =0x020ED5C0
	ldrh r0, [r0, r1]
	str r0, [sp, #0x8]
	str r4, [sp, #0x0]
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0x4]
	mov r0, #0x1a
	bl FUN_0200A648
	add sp, #0xc
	pop {r3-r4, pc}
_02013A88:
	add r0, r4, #0x0
	bl FUN_02021A4C
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_02013A94: .word 0x0000FFFF
_02013A98: .word 0x020ED5C0

	thumb_func_start FUN_02013A9C
FUN_02013A9C: ; 0x02013A9C
	push {r4-r5}
	ldr r4, _02013AE0 ; =0x020ED5C0
	mov r2, #0x0
_02013AA2:
	ldrh r3, [r4, #0x0]
	cmp r0, r3
	bne _02013AD0
	mov r4, #0x0
	add r3, r4, #0x0
	cmp r2, #0x0
	bls _02013AC6
	ldr r0, _02013AE4 ; =0x020ED5D6
_02013AB2:
	lsl r5, r4, #0x1
	ldrh r5, [r0, r5]
	add r4, r4, #0x1
	lsl r4, r4, #0x10
	add r3, r3, r5
	lsl r3, r3, #0x10
	lsr r4, r4, #0x10
	lsr r3, r3, #0x10
	cmp r4, r2
	blo _02013AB2
_02013AC6:
	add r0, r3, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r4-r5}
	bx lr
_02013AD0:
	add r2, r2, #0x1
	add r4, r4, #0x2
	cmp r2, #0xb
	blo _02013AA2
	ldr r0, _02013AE8 ; =0x0000FFFF
	pop {r4-r5}
	bx lr
	nop
_02013AE0: .word 0x020ED5C0
_02013AE4: .word 0x020ED5D6
_02013AE8: .word 0x0000FFFF

	thumb_func_start FUN_02013AEC
FUN_02013AEC: ; 0x02013AEC
	push {r3-r6}
	ldr r3, _02013B20 ; =0x00000FFF
	ldr r6, _02013B24 ; =0x020ED5D6
	and r3, r0
	mov r0, #0x0
	add r5, r0, #0x0
_02013AF8:
	ldrh r4, [r6, #0x0]
	add r0, r0, r4
	cmp r3, r0
	bhs _02013B12
	str r5, [r1, #0x0]
	ldr r1, _02013B24 ; =0x020ED5D6
	lsl r4, r5, #0x1
	ldrh r1, [r1, r4]
	sub r0, r0, r1
	sub r0, r3, r0
	str r0, [r2, #0x0]
	pop {r3-r6}
	bx lr
_02013B12:
	add r5, r5, #0x1
	add r6, r6, #0x2
	cmp r5, #0xb
	blo _02013AF8
	pop {r3-r6}
	bx lr
	nop
_02013B20: .word 0x00000FFF
_02013B24: .word 0x020ED5D6

	thumb_func_start FUN_02013B28
FUN_02013B28: ; 0x02013B28
	mov r0, #0x8
	bx lr

	thumb_func_start FUN_02013B2C
FUN_02013B2C: ; 0x02013B2C
	push {r3, lr}
	mov r2, #0x0
	str r2, [r0, #0x0]
	ldr r3, _02013B54 ; =0x020ED5B4
	str r2, [r0, #0x4]
_02013B36:
	ldrb r1, [r3, #0x0]
	cmp r1, #0x2
	bne _02013B48
	ldr r1, _02013B58 ; =0x020ED5B5
	lsl r2, r2, #0x1
	ldrb r1, [r1, r2]
	bl FUN_02013C18
	pop {r3, pc}
_02013B48:
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0x6
	blo _02013B36
	pop {r3, pc}
	nop
_02013B54: .word 0x020ED5B4
_02013B58: .word 0x020ED5B5

	thumb_func_start FUN_02013B5C
FUN_02013B5C: ; 0x02013B5C
	ldr r3, _02013B64 ; =FUN_02022610
	mov r1, #0x22
	bx r3
	nop
_02013B64: .word FUN_02022610

	thumb_func_start FUN_02013B68
FUN_02013B68: ; 0x02013B68
	ldr r0, [r0, #0x4]
	add r2, r0, #0x0
	lsr r2, r1
	mov r0, #0x1
	and r0, r2
	bx lr

	thumb_func_start FUN_02013B74
FUN_02013B74: ; 0x02013B74
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r2, #0x0
	ldr r3, [r5, #0x4]
	add r4, r2, #0x0
	mov r0, #0x1
_02013B80:
	add r1, r3, #0x0
	lsr r1, r2
	tst r1, r0
	bne _02013B8A
	add r4, r4, #0x1
_02013B8A:
	add r2, r2, #0x1
	cmp r2, #0x20
	blo _02013B80
	cmp r4, #0x0
	beq _02013BC4
	bl FUN_0201B9EC
	add r1, r4, #0x0
	bl _u32_div_f
	ldr r4, [r5, #0x4]
	mov r0, #0x0
	mov r2, #0x1
_02013BA4:
	add r3, r4, #0x0
	lsr r3, r0
	tst r3, r2
	bne _02013BBE
	cmp r1, #0x0
	bne _02013BBC
	mov r1, #0x1
	ldr r2, [r5, #0x4]
	lsl r1, r0
	orr r1, r2
	str r1, [r5, #0x4]
	pop {r3-r5, pc}
_02013BBC:
	sub r1, r1, #0x1
_02013BBE:
	add r0, r0, #0x1
	cmp r0, #0x20
	blo _02013BA4
_02013BC4:
	mov r0, #0x20
	pop {r3-r5, pc}

	thumb_func_start FUN_02013BC8
FUN_02013BC8: ; 0x02013BC8
	ldr r3, [r0, #0x4]
	mov r2, #0x0
	mov r0, #0x1
_02013BCE:
	add r1, r3, #0x0
	lsr r1, r2
	tst r1, r0
	bne _02013BDA
	mov r0, #0x0
	bx lr
_02013BDA:
	add r2, r2, #0x1
	cmp r2, #0x20
	blo _02013BCE
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_02013BE4
FUN_02013BE4: ; 0x02013BE4
	push {r3-r4}
	mov r3, #0x0
	ldr r4, _02013C08 ; =0x020ED5D6
	add r2, r3, #0x0
_02013BEC:
	ldrh r1, [r4, #0x0]
	add r2, r2, #0x1
	add r4, r4, #0x2
	add r1, r3, r1
	lsl r1, r1, #0x10
	lsr r3, r1, #0x10
	cmp r2, #0x9
	blt _02013BEC
	add r0, r3, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3-r4}
	bx lr
	nop
_02013C08: .word 0x020ED5D6

	thumb_func_start FUN_02013C0C
FUN_02013C0C: ; 0x02013C0C
	ldr r0, [r0, #0x0]
	add r2, r0, #0x0
	lsr r2, r1
	mov r0, #0x1
	and r0, r2
	bx lr

	thumb_func_start FUN_02013C18
FUN_02013C18: ; 0x02013C18
	mov r2, #0x1
	ldr r3, [r0, #0x0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02013C28
FUN_02013C28: ; 0x02013C28
	push {r4-r7}
	mov r3, #0x0
	ldr r5, _02013C64 ; =0x020ED5EC
	add r2, r3, #0x0
_02013C30:
	ldr r7, [r5, #0x4]
	add r4, r2, #0x0
	cmp r7, #0x0
	ble _02013C54
	ldr r6, [r5, #0x0]
_02013C3A:
	ldrh r1, [r6, #0x0]
	cmp r0, r1
	bne _02013C4C
	ldr r0, _02013C68 ; =0x020ED5F0
	lsl r1, r3, #0x3
	ldr r0, [r0, r1]
	sub r0, r0, #0x1
	pop {r4-r7}
	bx lr
_02013C4C:
	add r4, r4, #0x1
	add r6, r6, #0x2
	cmp r4, r7
	blt _02013C3A
_02013C54:
	add r3, r3, #0x1
	add r5, #0x8
	cmp r3, #0xc
	blo _02013C30
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	nop
_02013C64: .word 0x020ED5EC
_02013C68: .word 0x020ED5F0

	thumb_func_start FUN_02013C6C
FUN_02013C6C: ; 0x02013C6C
	push {r3-r7, lr}
	ldr r3, _02013CC8 ; =0x020ED5EC
	add r6, r1, #0x0
	mov r7, #0x0
_02013C74:
	ldr r5, [r3, #0x4]
	mov r2, #0x0
	cmp r5, #0x0
	ble _02013CBC
	ldr r4, [r3, #0x0]
_02013C7E:
	ldrh r1, [r4, #0x0]
	cmp r0, r1
	bne _02013CB4
	ldr r2, _02013CCC ; =0x020ED5F0
	lsl r1, r7, #0x3
	ldr r2, [r2, r1]
	mov r0, #0x0
	cmp r2, #0x0
	beq _02013CAC
	ldr r2, _02013CC8 ; =0x020ED5EC
	add r2, r2, r1
	ldr r2, [r2, #0x4]
_02013C96:
	cmp r6, #0x0
	bne _02013CA4
	ldr r2, _02013CC8 ; =0x020ED5EC
	lsl r0, r0, #0x1
	ldr r1, [r2, r1]
	ldrh r0, [r1, r0]
	pop {r3-r7, pc}
_02013CA4:
	sub r6, r6, #0x1
	add r0, r0, #0x1
	cmp r2, #0x0
	bne _02013C96
_02013CAC:
	bl ErrorHandling
	ldr r0, _02013CD0 ; =0x0000FFFF
	pop {r3-r7, pc}
_02013CB4:
	add r2, r2, #0x1
	add r4, r4, #0x2
	cmp r2, r5
	blt _02013C7E
_02013CBC:
	add r7, r7, #0x1
	add r3, #0x8
	cmp r7, #0xc
	blo _02013C74
	pop {r3-r7, pc}
	nop
_02013CC8: .word 0x020ED5EC
_02013CCC: .word 0x020ED5F0
_02013CD0: .word 0x0000FFFF

	thumb_func_start FUN_02013CD4
FUN_02013CD4: ; 0x02013CD4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r1, #0x18
	bl FUN_02016998
	add r4, r0, #0x0
	bne _02013CE8
	bl ErrorHandling
_02013CE8:
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0xc]
	bl FUN_02013F68
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x4]
	ldr r0, [r5, #0x4]
	ldr r1, [r5, #0xc]
	bl FUN_02013F98
	str r0, [r4, #0x8]
	ldr r0, [r5, #0x4]
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	bl FUN_02013FC8
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x8]
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02013D18
FUN_02013D18: ; 0x02013D18
	push {r4, lr}
	add r4, r0, #0x0
	bne _02013D22
	bl ErrorHandling
_02013D22:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02013D2C
	bl ErrorHandling
_02013D2C:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	bne _02013D36
	bl ErrorHandling
_02013D36:
	ldr r0, [r4, #0x10]
	cmp r0, #0x0
	bne _02013D40
	bl ErrorHandling
_02013D40:
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	ldr r0, [r4, #0x8]
	bl FUN_02016A18
	ldr r0, [r4, #0x10]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02013D5C
FUN_02013D5C: ; 0x02013D5C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _02013D90 ; =0x04000444
	mov r6, #0x0
	str r6, [r0, #0x0]
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	ble _02013D86
	add r4, r6, #0x0
_02013D6E:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	ldr r1, [r0, #0x20]
	cmp r1, #0x0
	beq _02013D7C
	bl FUN_020140D8
_02013D7C:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0x40
	cmp r6, r0
	blt _02013D6E
_02013D86:
	ldr r0, _02013D94 ; =0x04000448
	mov r1, #0x1
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
	nop
_02013D90: .word 0x04000444
_02013D94: .word 0x04000448

	thumb_func_start FUN_02013D98
FUN_02013D98: ; 0x02013D98
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02014024
	add r4, r0, #0x0
	bne _02013DAA
	bl ErrorHandling
_02013DAA:
	ldr r0, [r5, #0x4]
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _02013DB6
	bl ErrorHandling
_02013DB6:
	ldr r0, [r5, #0x4]
	bl FUN_0201407C
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02013DC6
	bl ErrorHandling
_02013DC6:
	ldr r0, [r5, #0x4]
	ldr r1, [r4, #0x0]
	add r2, r4, #0x4
	bl FUN_020140A4
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02013DD4
FUN_02013DD4: ; 0x02013DD4
	push {r4, lr}
	ldr r1, _02013DE8 ; =0x021064BC
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	blx r1
	add r0, r4, #0x0
	bl FUN_02013F50
	pop {r4, pc}
	.balign 4
_02013DE8: .word 0x021064BC

	thumb_func_start FUN_02013DEC
FUN_02013DEC: ; 0x02013DEC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02013E12
	add r4, r6, #0x0
_02013DFA:
	ldr r1, [r5, #0x8]
	ldr r0, [r1, r4]
	cmp r0, #0x0
	beq _02013E08
	add r0, r1, r4
	bl FUN_02013DD4
_02013E08:
	ldr r0, [r5, #0xc]
	add r6, r6, #0x1
	add r4, #0x28
	cmp r6, r0
	blt _02013DFA
_02013E12:
	pop {r4-r6, pc}

	thumb_func_start FUN_02013E14
FUN_02013E14: ; 0x02013E14
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02014050
	add r4, r0, #0x0
	bne _02013E26
	bl ErrorHandling
_02013E26:
	ldr r0, [r5, #0x8]
	bl FUN_02014090
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02013E36
	bl ErrorHandling
_02013E36:
	ldr r0, [r5, #0x4]
	ldr r1, [r4, #0x0]
	add r2, r4, #0x4
	bl FUN_020140B4
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02013E44
FUN_02013E44: ; 0x02013E44
	push {r4, lr}
	ldr r1, _02013E58 ; =0x021064C4
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	blx r1
	add r0, r4, #0x0
	bl FUN_02013F5C
	pop {r4, pc}
	.balign 4
_02013E58: .word 0x021064C4

	thumb_func_start FUN_02013E5C
FUN_02013E5C: ; 0x02013E5C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x14]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02013E82
	add r4, r6, #0x0
_02013E6A:
	ldr r1, [r5, #0x10]
	ldr r0, [r1, r4]
	cmp r0, #0x0
	beq _02013E78
	add r0, r1, r4
	bl FUN_02013E44
_02013E78:
	ldr r0, [r5, #0x14]
	add r6, r6, #0x1
	add r4, #0x18
	cmp r6, r0
	blt _02013E6A
_02013E82:
	pop {r4-r6, pc}

	thumb_func_start FUN_02013E84
FUN_02013E84: ; 0x02013E84
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02013FF8
	add r4, r0, #0x0
	bne _02013E96
	bl ErrorHandling
_02013E96:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02014218
	mov r0, #0x1
	str r0, [r4, #0x1c]
	str r0, [r4, #0x20]
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02013EA8
FUN_02013EA8: ; 0x02013EA8
	ldr r3, _02013EAC ; =FUN_02013F30
	bx r3
	.balign 4
_02013EAC: .word FUN_02013F30

	thumb_func_start FUN_02013EB0
FUN_02013EB0: ; 0x02013EB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02013EBE
	bl ErrorHandling
_02013EBE:
	str r4, [r5, #0x20]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02013EC4
FUN_02013EC4: ; 0x02013EC4
	strh r1, [r0, #0x0]
	strh r2, [r0, #0x2]
	bx lr
	.balign 4

	thumb_func_start FUN_02013ECC
FUN_02013ECC: ; 0x02013ECC
	ldrh r1, [r0, #0x2]
	ldrh r0, [r0, #0x0]
	lsl r1, r1, #0x10
	orr r0, r1
	bx lr
	.balign 4

	thumb_func_start FUN_02013ED8
FUN_02013ED8: ; 0x02013ED8
	strh r1, [r0, #0x4]
	strh r2, [r0, #0x6]
	bx lr
	.balign 4

	thumb_func_start FUN_02013EE0
FUN_02013EE0: ; 0x02013EE0
	str r1, [r0, #0xc]
	str r2, [r0, #0x10]
	bx lr
	.balign 4

	thumb_func_start FUN_02013EE8
FUN_02013EE8: ; 0x02013EE8
	strh r1, [r0, #0x8]
	strh r2, [r0, #0xa]
	bx lr
	.balign 4

	thumb_func_start FUN_02013EF0
FUN_02013EF0: ; 0x02013EF0
	ldrh r1, [r0, #0xa]
	ldrh r0, [r0, #0x8]
	lsl r1, r1, #0x10
	orr r0, r1
	bx lr
	.balign 4

	thumb_func_start FUN_02013EFC
FUN_02013EFC: ; 0x02013EFC
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start FUN_02013F00
FUN_02013F00: ; 0x02013F00
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start FUN_02013F04
FUN_02013F04: ; 0x02013F04
	add r0, #0x3e
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02013F0C
FUN_02013F0C: ; 0x02013F0C
	strh r1, [r0, #0x3c]
	bx lr

	thumb_func_start FUN_02013F10
FUN_02013F10: ; 0x02013F10
	str r1, [r0, #0x24]
	bx lr

	thumb_func_start FUN_02013F14
FUN_02013F14: ; 0x02013F14
	str r1, [r0, #0x28]
	bx lr

	thumb_func_start FUN_02013F18
FUN_02013F18: ; 0x02013F18
	str r1, [r0, #0x2c]
	bx lr

	thumb_func_start FUN_02013F1C
FUN_02013F1C: ; 0x02013F1C
	str r1, [r0, #0x30]
	bx lr

	thumb_func_start FUN_02013F20
FUN_02013F20: ; 0x02013F20
	cmp r1, #0x0
	bne _02013F28
	str r2, [r0, #0x34]
	bx lr
_02013F28:
	str r2, [r0, #0x38]
	bx lr

	thumb_func_start FUN_02013F2C
FUN_02013F2C: ; 0x02013F2C
	str r1, [r0, #0x18]
	bx lr

	thumb_func_start FUN_02013F30
FUN_02013F30: ; 0x02013F30
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x40
	bl Call_FillMemWithValue
	add r0, r4, #0x0
	mov r1, #0x1f
	add r0, #0x3e
	strb r1, [r0, #0x0]
	ldr r0, _02013F4C ; =0x00007FFF
	strh r0, [r4, #0x3c]
	pop {r4, pc}
	nop
_02013F4C: .word 0x00007FFF

	thumb_func_start FUN_02013F50
FUN_02013F50: ; 0x02013F50
	ldr r3, _02013F58 ; =FUN_020B1A24
	mov r1, #0x0
	stmia r0!, {r1}
	bx r3
	.balign 4
_02013F58: .word FUN_020B1A24

	thumb_func_start FUN_02013F5C
FUN_02013F5C: ; 0x02013F5C
	ldr r3, _02013F64 ; =FUN_020B19DC
	mov r1, #0x0
	stmia r0!, {r1}
	bx r3
	.balign 4
_02013F64: .word FUN_020B19DC

	thumb_func_start FUN_02013F68
FUN_02013F68: ; 0x02013F68
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r0, r1, #0x0
	lsl r1, r6, #0x6
	bl FUN_02016998
	add r7, r0, #0x0
	bne _02013F7C
	bl ErrorHandling
_02013F7C:
	mov r4, #0x0
	cmp r6, #0x0
	ble _02013F92
	add r5, r7, #0x0
_02013F84:
	add r0, r5, #0x0
	bl FUN_02013F30
	add r4, r4, #0x1
	add r5, #0x40
	cmp r4, r6
	blt _02013F84
_02013F92:
	add r0, r7, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02013F98
FUN_02013F98: ; 0x02013F98
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x28
	mul r1, r6
	bl FUN_02016998
	add r7, r0, #0x0
	bne _02013FAE
	bl ErrorHandling
_02013FAE:
	mov r4, #0x0
	cmp r6, #0x0
	ble _02013FC4
	add r5, r7, #0x0
_02013FB6:
	add r0, r5, #0x0
	bl FUN_02013F50
	add r4, r4, #0x1
	add r5, #0x28
	cmp r4, r6
	blt _02013FB6
_02013FC4:
	add r0, r7, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02013FC8
FUN_02013FC8: ; 0x02013FC8
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x18
	mul r1, r6
	bl FUN_02016998
	add r7, r0, #0x0
	bne _02013FDE
	bl ErrorHandling
_02013FDE:
	mov r4, #0x0
	cmp r6, #0x0
	ble _02013FF4
	add r5, r7, #0x0
_02013FE6:
	add r0, r5, #0x0
	bl FUN_02013F5C
	add r4, r4, #0x1
	add r5, #0x18
	cmp r4, r6
	blt _02013FE6
_02013FF4:
	add r0, r7, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02013FF8
FUN_02013FF8: ; 0x02013FF8
	push {r3-r4}
	ldr r4, [r0, #0x4]
	mov r1, #0x0
	cmp r4, #0x0
	ble _0201401C
	ldr r3, [r0, #0x0]
	add r2, r3, #0x0
_02014006:
	ldr r0, [r2, #0x1c]
	cmp r0, #0x0
	bne _02014014
	lsl r0, r1, #0x6
	add r0, r3, r0
	pop {r3-r4}
	bx lr
_02014014:
	add r1, r1, #0x1
	add r2, #0x40
	cmp r1, r4
	blt _02014006
_0201401C:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_02014024
FUN_02014024: ; 0x02014024
	push {r3-r4}
	ldr r4, [r0, #0x4]
	mov r1, #0x0
	cmp r4, #0x0
	ble _0201404A
	ldr r3, [r0, #0x8]
	add r2, r3, #0x0
_02014032:
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _02014042
	mov r0, #0x28
	mul r0, r1
	add r0, r3, r0
	pop {r3-r4}
	bx lr
_02014042:
	add r1, r1, #0x1
	add r2, #0x28
	cmp r1, r4
	blt _02014032
_0201404A:
	mov r0, #0x0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02014050
FUN_02014050: ; 0x02014050
	push {r3-r4}
	ldr r4, [r0, #0x4]
	mov r1, #0x0
	cmp r4, #0x0
	ble _02014076
	ldr r3, [r0, #0x10]
	add r2, r3, #0x0
_0201405E:
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _0201406E
	mov r0, #0x18
	mul r0, r1
	add r0, r3, r0
	pop {r3-r4}
	bx lr
_0201406E:
	add r1, r1, #0x1
	add r2, #0x18
	cmp r1, r4
	blt _0201405E
_02014076:
	mov r0, #0x0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201407C
FUN_0201407C: ; 0x0201407C
	push {r3, lr}
	ldr r3, _0201408C ; =0x021064B8
	mov r1, #0x0
	ldr r0, [r0, #0x10]
	ldr r3, [r3, #0x0]
	add r2, r1, #0x0
	blx r3
	pop {r3, pc}
	.balign 4
_0201408C: .word 0x021064B8

	thumb_func_start FUN_02014090
FUN_02014090: ; 0x02014090
	push {r3, lr}
	ldr r3, _020140A0 ; =0x021064C0
	mov r1, #0x0
	ldr r3, [r3, #0x0]
	lsl r0, r0, #0x5
	add r2, r1, #0x0
	blx r3
	pop {r3, pc}
	.balign 4
_020140A0: .word 0x021064C0

	thumb_func_start FUN_020140A4
FUN_020140A4: ; 0x020140A4
	push {r3, lr}
	lsl r1, r1, #0x10
	add r3, r2, #0x0
	lsr r1, r1, #0xd
	mov r2, #0x0
	bl FUN_020B1528
	pop {r3, pc}

	thumb_func_start FUN_020140B4
FUN_020140B4: ; 0x020140B4
	push {r3-r5, lr}
	add r3, r2, #0x0
	ldr r2, _020140D4 ; =0xFFFF0000
	add r5, r0, #0x0
	and r2, r1
	lsr r2, r2, #0x10
	lsl r1, r1, #0x10
	ldr r4, [r5, #0x8]
	lsl r2, r2, #0x3
	str r2, [r5, #0x8]
	lsr r1, r1, #0xd
	mov r2, #0x0
	bl FUN_020B1240
	str r4, [r5, #0x8]
	pop {r3-r5, pc}
	.balign 4
_020140D4: .word 0xFFFF0000

	thumb_func_start FUN_020140D8
FUN_020140D8: ; 0x020140D8
	push {r3-r7, lr}
	sub sp, #0x18
	ldr r7, _020141F8 ; =0x04000444
	mov r6, #0x0
	add r5, r0, #0x0
	str r6, [r7, #0x0]
	ldrh r1, [r5, #0x3c]
	ldr r0, _020141FC ; =0x7FFF8000
	orr r0, r1
	str r0, [r7, #0x7c]
	add r0, r7, #0x0
	ldr r1, _02014200 ; =0x00004210
	add r0, #0x80
	str r1, [r0, #0x0]
	ldr r3, [r5, #0x24]
	ldr r4, [r3, #0x8]
	ldr r2, [r3, #0x10]
	ldr r1, [r3, #0x4]
	ldr r0, [r3, #0x0]
	lsl r3, r2, #0x1d
	lsl r2, r1, #0x17
	lsl r1, r0, #0x14
	ldr r0, [r5, #0x28]
	lsl r4, r4, #0x1a
	lsr r0, r0, #0x3
	orr r4, r0
	mov r0, #0x1
	lsl r0, r0, #0x1e
	orr r0, r4
	orr r0, r1
	orr r0, r2
	orr r0, r3
	str r0, [r7, #0x64]
	ldr r0, [r5, #0x24]
	ldr r0, [r0, #0x8]
	cmp r0, #0x2
	bne _02014124
	mov r6, #0x1
_02014124:
	ldr r0, [r5, #0x30]
	ldr r1, [r5, #0x2c]
	lsl r0, r0, #0x5
	add r1, r1, r0
	mov r0, #0x4
	sub r0, r0, r6
	lsr r1, r0
	ldr r2, _02014204 ; =0x040004AC
	add r0, r5, #0x0
	str r1, [r2, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	sub r2, #0x8
	lsl r1, r0, #0x10
	mov r0, #0xc0
	orr r0, r1
	str r0, [r2, #0x0]
	ldr r0, [r5, #0x34]
	cmp r0, #0x0
	beq _02014156
	mov r0, #0x8
	ldrsh r0, [r5, r0]
	mov r7, #0x0
	str r0, [sp, #0x14]
	b _0201415E
_02014156:
	mov r0, #0x8
	ldrsh r7, [r5, r0]
	mov r0, #0x0
	str r0, [sp, #0x14]
_0201415E:
	ldr r0, [r5, #0x38]
	cmp r0, #0x0
	beq _0201416C
	mov r0, #0xa
	ldrsh r6, [r5, r0]
	mov r4, #0x0
	b _02014172
_0201416C:
	mov r0, #0xa
	ldrsh r4, [r5, r0]
	mov r6, #0x0
_02014172:
	ldr r0, [r5, #0x14]
	mov r1, #0x6
	lsl r2, r0, #0xc
	mov r0, #0x2
	ldrsh r0, [r5, r0]
	ldrsh r1, [r5, r1]
	mov r3, #0x4
	ldrsh r3, [r5, r3]
	add r0, r0, r1
	lsl r1, r0, #0xc
	mov r0, #0x0
	ldrsh r0, [r5, r0]
	add r0, r0, r3
	ldr r3, _02014208 ; =0x04000470
	lsl r0, r0, #0xc
	str r0, [r3, #0x0]
	str r1, [r3, #0x0]
	str r2, [r3, #0x0]
	ldr r0, [r5, #0x18]
	ldr r1, _0201420C ; =0x020FFA38
	asr r0, r0, #0x4
	lsl r2, r0, #0x1
	lsl r0, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r0, [r1, r0]
	ldrsh r1, [r1, r2]
	bl G3_RotZ
	ldr r2, [r5, #0x10]
	ldr r0, [r5, #0xc]
	ldr r1, _02014210 ; =0x0400046C
	mov r3, #0x8
	str r0, [r1, #0x0]
	str r2, [r1, #0x0]
	lsr r0, r1, #0xe
	str r0, [r1, #0x0]
	mov r2, #0x4
	mov r0, #0x6
	ldrsh r2, [r5, r2]
	ldrsh r0, [r5, r0]
	neg r2, r2
	neg r0, r0
	lsl r2, r2, #0xc
	lsl r0, r0, #0xc
	str r2, [r1, #0x4]
	str r0, [r1, #0x4]
	mov r0, #0x0
	str r0, [r1, #0x4]
	mov r1, #0xa
	ldrsh r1, [r5, r1]
	add r2, r0, #0x0
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x14]
	str r1, [sp, #0x4]
	str r6, [sp, #0x8]
	str r7, [sp, #0xc]
	str r4, [sp, #0x10]
	ldrsh r3, [r5, r3]
	add r1, r0, #0x0
	bl FUN_020B0250
	ldr r0, _02014214 ; =0x04000448
	mov r1, #0x1
	str r1, [r0, #0x0]
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_020141F8: .word 0x04000444
_020141FC: .word 0x7FFF8000
_02014200: .word 0x00004210
_02014204: .word 0x040004AC
_02014208: .word 0x04000470
_0201420C: .word 0x020FFA38
_02014210: .word 0x0400046C
_02014214: .word 0x04000448

	thumb_func_start FUN_02014218
FUN_02014218: ; 0x02014218
	push {r3-r7, lr}
	add r5, r1, #0x0
	ldr r1, [r5, #0x4]
	add r7, r0, #0x0
	ldr r2, [r1, #0x10]
	mov r6, #0x8
	mov r0, #0x0
	cmp r2, #0x0
	ble _02014236
_0201422A:
	ldr r2, [r5, #0x4]
	add r0, r0, #0x1
	ldr r2, [r2, #0x10]
	lsl r6, r6, #0x1
	cmp r0, r2
	blt _0201422A
_02014236:
	ldr r1, [r1, #0x14]
	mov r4, #0x8
	mov r0, #0x0
	cmp r1, #0x0
	ble _0201424C
_02014240:
	ldr r1, [r5, #0x4]
	add r0, r0, #0x1
	ldr r1, [r1, #0x14]
	lsl r4, r4, #0x1
	cmp r0, r1
	blt _02014240
_0201424C:
	mov r1, #0xc
	mov r2, #0xe
	ldrsh r1, [r5, r1]
	ldrsh r2, [r5, r2]
	add r0, r7, #0x0
	bl FUN_02013EC4
	lsr r1, r6, #0x1f
	lsr r2, r4, #0x1f
	add r1, r6, r1
	add r2, r4, r2
	lsl r1, r1, #0xf
	lsl r2, r2, #0xf
	add r0, r7, #0x0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_02013ED8
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [r7, #0xc]
	str r0, [r7, #0x10]
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02013EE8
	ldr r1, [r5, #0x18]
	add r0, r7, #0x0
	bl FUN_02013EFC
	ldr r1, [r5, #0x14]
	add r0, r7, #0x0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02013F04
	ldr r1, [r5, #0x4]
	add r0, r7, #0x0
	add r1, #0x10
	bl FUN_02013F10
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	add r0, r0, #0x4
	bl FUN_020B1A14
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02013F14
	ldr r0, [r5, #0x8]
	mov r1, #0x0
	add r0, r0, #0x4
	bl FUN_020B19C4
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02013F18
	ldrh r1, [r5, #0x1c]
	add r0, r7, #0x0
	bl FUN_02013F1C
	mov r1, #0x0
	add r0, r7, #0x0
	add r2, r1, #0x0
	bl FUN_02013F20
	add r0, r7, #0x0
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_02013F20
	ldrh r1, [r5, #0x10]
	add r0, r7, #0x0
	bl FUN_02013F2C
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020142EC
FUN_020142EC: ; 0x020142EC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	ldr r0, _02014394 ; =FUN_020143DC
	mov r1, #0x50
	mov r2, #0x0
	bl FUN_020061E8
	str r0, [sp, #0x4]
	bl FUN_0201B6C8
	add r4, r0, #0x0
	cmp r5, #0x0
	beq _02014330
	cmp r6, #0x0
	bne _02014320
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020031FC
	str r0, [sp, #0x0]
	ldr r0, _02014398 ; =FUN_020144E0
	str r0, [r4, #0x4]
	b _0201434A
_02014320:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020031FC
	str r0, [sp, #0x0]
	ldr r0, _0201439C ; =FUN_020144FC
	str r0, [r4, #0x4]
	b _0201434A
_02014330:
	cmp r6, #0x0
	bne _02014340
	bl FUN_020222E8
	str r0, [sp, #0x0]
	ldr r0, _020143A0 ; =FUN_020144B0
	str r0, [r4, #0x4]
	b _0201434A
_02014340:
	bl FUN_020222F8
	str r0, [sp, #0x0]
	ldr r0, _020143A4 ; =FUN_020144C8
	str r0, [r4, #0x4]
_0201434A:
	ldr r1, [sp, #0x0]
	lsl r0, r7, #0x5
	str r0, [sp, #0x8]
	add r0, r1, r0
	add r1, r4, #0x0
	add r1, #0xc
	mov r2, #0x20
	bl MIi_CpuCopy16
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x8]
	mov r2, #0x20
	add r0, r1, r0
	add r1, r4, #0x0
	add r1, #0x2c
	bl MIi_CpuCopy16
	ldr r0, [sp, #0x4]
	mov r1, #0x1
	str r0, [r4, #0x0]
	add r0, r4, #0x0
	str r5, [r4, #0x8]
	add r0, #0x4c
	strb r6, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x4d
	strb r7, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x4e
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x4f
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02014394: .word FUN_020143DC
_02014398: .word FUN_020144E0
_0201439C: .word FUN_020144FC
_020143A0: .word FUN_020144B0
_020143A4: .word FUN_020144C8

	thumb_func_start FUN_020143A8
FUN_020143A8: ; 0x020143A8
	cmp r1, #0x0
	beq _020143B6
	cmp r1, #0x1
	beq _020143BE
	cmp r1, #0x2
	beq _020143C6
	bx lr
_020143B6:
	mov r1, #0x0
	add r0, #0x4e
	strb r1, [r0, #0x0]
	bx lr
_020143BE:
	mov r1, #0x2
	add r0, #0x4e
	strb r1, [r0, #0x0]
	bx lr
_020143C6:
	mov r1, #0x3
	add r0, #0x4e
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020143D0
FUN_020143D0: ; 0x020143D0
	ldr r3, _020143D8 ; =FUN_0200621C
	ldr r0, [r0, #0x0]
	bx r3
	nop
_020143D8: .word FUN_0200621C

	thumb_func_start FUN_020143DC
FUN_020143DC: ; 0x020143DC
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x4e
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	bhi _02014452
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020143F8: ; jump table (using 16-bit offset)
	.short _02014400 - _020143F8 - 2; case 0
	.short _02014410 - _020143F8 - 2; case 1
	.short _02014452 - _020143F8 - 2; case 2
	.short _02014444 - _020143F8 - 2; case 3
_02014400:
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x4f
	strb r1, [r0, #0x0]
	mov r0, #0x1
	add r4, #0x4e
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
_02014410:
	add r0, r4, #0x0
	bl FUN_02014454
	cmp r0, #0x1
	bne _02014424
	add r1, r4, #0x0
	ldr r2, [r4, #0x4]
	add r0, r4, #0x0
	add r1, #0x2c
	blx r2
_02014424:
	add r0, r4, #0x0
	add r0, #0x4f
	ldrb r0, [r0, #0x0]
	add r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x4f
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x4f
	ldrb r0, [r0, #0x0]
	cmp r0, #0x20
	bne _02014452
	mov r0, #0x0
	add r4, #0x4f
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
_02014444:
	ldr r2, [r4, #0x4]
	add r0, r4, #0x0
	add r1, #0xc
	blx r2
	add r0, r5, #0x0
	bl FUN_0200621C
_02014452:
	pop {r3-r5, pc}

	thumb_func_start FUN_02014454
FUN_02014454: ; 0x02014454
	push {r4-r5}
	add r1, r0, #0x0
	add r1, #0x4f
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02014482
	mov r1, #0x1e
	mov r4, #0x0
	mov r3, #0x1
	lsl r1, r1, #0xa
_02014468:
	add r2, r3, #0x0
	lsl r2, r4
	tst r2, r1
	beq _02014474
	ldrh r2, [r0, #0xc]
	strh r2, [r0, #0x2c]
_02014474:
	add r4, r4, #0x1
	add r0, r0, #0x2
	cmp r4, #0x10
	blo _02014468
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02014482:
	cmp r1, #0x18
	bne _020144AA
	mov r1, #0x1e
	mov r5, #0x0
	add r4, r0, #0x0
	mov r3, #0x1
	lsl r1, r1, #0xa
_02014490:
	add r2, r3, #0x0
	lsl r2, r5
	tst r2, r1
	beq _0201449C
	ldrh r2, [r0, #0x2a]
	strh r2, [r4, #0x2c]
_0201449C:
	add r5, r5, #0x1
	add r4, r4, #0x2
	cmp r5, #0x10
	blo _02014490
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_020144AA:
	mov r0, #0x0
	pop {r4-r5}
	bx lr

	thumb_func_start FUN_020144B0
FUN_020144B0: ; 0x020144B0
	push {r3, lr}
	add r3, r0, #0x0
	add r3, #0x4d
	ldrb r3, [r3, #0x0]
	mov r0, #0x0
	mov r2, #0x20
	lsl r3, r3, #0x15
	lsr r3, r3, #0x10
	bl FUN_02017FB4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020144C8
FUN_020144C8: ; 0x020144C8
	push {r3, lr}
	add r3, r0, #0x0
	add r3, #0x4d
	ldrb r3, [r3, #0x0]
	mov r0, #0x4
	mov r2, #0x20
	lsl r3, r3, #0x15
	lsr r3, r3, #0x10
	bl FUN_02017FB4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020144E0
FUN_020144E0: ; 0x020144E0
	push {r3, lr}
	add r3, r0, #0x0
	mov r0, #0x20
	str r0, [sp, #0x0]
	ldr r0, [r3, #0x8]
	add r3, #0x4d
	ldrb r3, [r3, #0x0]
	mov r2, #0x0
	lsl r3, r3, #0x14
	lsr r3, r3, #0x10
	bl FUN_02003054
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020144FC
FUN_020144FC: ; 0x020144FC
	push {r3, lr}
	add r3, r0, #0x0
	mov r0, #0x20
	str r0, [sp, #0x0]
	ldr r0, [r3, #0x8]
	add r3, #0x4d
	ldrb r3, [r3, #0x0]
	mov r2, #0x1
	lsl r3, r3, #0x14
	lsr r3, r3, #0x10
	bl FUN_02003054
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02014518
FUN_02014518: ; 0x02014518
	push {r3-r7, lr}
	mov r1, #0x78
	add r7, r0, #0x0
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x78
	add r6, r0, #0x0
	bl MI_CpuFill8
	ldr r2, _02014560 ; =0x0000019E
	mov r0, #0x0
	mov r1, #0x1a
	add r3, r7, #0x0
	bl FUN_0200A86C
	str r0, [r6, #0x0]
	mov r4, #0x0
	add r5, r6, #0x0
_0201453E:
	mov r0, #0x16
	add r1, r7, #0x0
	bl FUN_020219F4
	str r0, [r5, #0x4]
	ldr r0, [r6, #0x0]
	ldr r2, [r5, #0x4]
	add r1, r4, #0x0
	bl FUN_0200A8E0
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x1d
	blt _0201453E
	add r0, r6, #0x0
	pop {r3-r7, pc}
	nop
_02014560: .word 0x0000019E

	thumb_func_start FUN_02014564
FUN_02014564: ; 0x02014564
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r6, #0x0
	mov r4, #0x1c
	add r5, #0x70
_0201456E:
	ldr r0, [r5, #0x4]
	bl FUN_02021A20
	sub r5, r5, #0x4
	sub r4, r4, #0x1
	bpl _0201456E
	ldr r0, [r6, #0x0]
	bl FUN_0200A8B8
	add r0, r6, #0x0
	bl FUN_02016A18
	pop {r4-r6, pc}

	thumb_func_start FUN_02014588
FUN_02014588: ; 0x02014588
	lsl r1, r1, #0x2
	add r0, r0, r1
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02014590
FUN_02014590: ; 0x02014590
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0x9c
	bl FUN_02016998
	add r1, r5, #0x0
	add r4, r0, #0x0
	bl FUN_020146F0
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020145A8
FUN_020145A8: ; 0x020145A8
	push {r4, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x9b
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	cmp r1, #0x1
	bne _020145BE
	bl FUN_020146C4
_020145BE:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020145C8
FUN_020145C8: ; 0x020145C8
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r2, [r4, #0x0]
	add r5, r0, #0x0
	str r2, [r5, #0x7c]
	add r2, r5, #0x0
	ldr r3, [r4, #0x4]
	add r2, #0x80
	str r3, [r2, #0x0]
	add r2, r5, #0x0
	ldrb r3, [r4, #0x10]
	add r2, #0x98
	strb r3, [r2, #0x0]
	add r2, r5, #0x0
	ldrb r3, [r4, #0x11]
	add r2, #0x99
	strb r3, [r2, #0x0]
	bl FUN_02014730
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02014754
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02014784
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02014814
	add r0, r5, #0x0
	add r0, #0x9b
	ldrb r1, [r0, #0x0]
	mov r0, #0xf
	bic r1, r0
	mov r0, #0x1
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x9b
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x9b
	ldrb r1, [r0, #0x0]
	mov r0, #0xf0
	add r5, #0x9b
	bic r1, r0
	mov r0, #0x80
	orr r0, r1
	strb r0, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02014630
FUN_02014630: ; 0x02014630
	push {r4, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x9b
	ldrb r2, [r1, #0x0]
	mov r1, #0xf0
	bic r2, r1
	mov r1, #0x80
	orr r2, r1
	add r1, r4, #0x0
	add r1, #0x9b
	strb r2, [r1, #0x0]
	bl FUN_0201466C
	cmp r0, #0x0
	bne _0201466A
	add r1, r4, #0x0
	add r1, #0x9b
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	bne _0201466A
	add r4, #0x9a
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02014668
	mov r0, #0x3
	pop {r4, pc}
_02014668:
	mov r0, #0x4
_0201466A:
	pop {r4, pc}

	thumb_func_start FUN_0201466C
FUN_0201466C: ; 0x0201466C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x9b
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #0x1
	beq _02014680
	bl ErrorHandling
_02014680:
	add r0, r4, #0x0
	add r0, #0x9a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	bne _02014690
	ldr r0, [r4, #0x0]
	bl FUN_02022144
_02014690:
	add r1, r4, #0x0
	add r1, #0x9a
	ldrb r2, [r1, #0x0]
	mov r0, #0x0
	cmp r2, #0x3
	beq _020146AA
	add r1, r4, #0x0
	mov r0, #0x38
	add r1, #0xc
	mul r0, r2
	add r0, r1, r0
	bl FUN_02014930
_020146AA:
	cmp r0, #0x1
	bne _020146BE
	add r4, #0x9a
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020146BA
	mov r0, #0x1
	pop {r4, pc}
_020146BA:
	mov r0, #0x2
	pop {r4, pc}
_020146BE:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020146C4
FUN_020146C4: ; 0x020146C4
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_0202212C
	add r5, r6, #0x0
	mov r4, #0x0
	add r5, #0xc
_020146D4:
	add r0, r5, #0x0
	bl FUN_02014970
	add r4, r4, #0x1
	add r5, #0x38
	cmp r4, #0x2
	blt _020146D4
	add r0, r6, #0x0
	add r6, #0x84
	ldr r1, [r6, #0x0]
	bl FUN_020146F0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020146F0
FUN_020146F0: ; 0x020146F0
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	mov r1, #0x0
	mov r2, #0x9c
	bl Call_FillMemWithValue
	add r0, r5, #0x0
	add r0, #0x9b
	ldrb r1, [r0, #0x0]
	mov r0, #0xf
	bic r1, r0
	add r0, r5, #0x0
	add r0, #0x9b
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x84
	str r4, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x3
	add r0, #0x9a
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x9b
	ldrb r1, [r0, #0x0]
	mov r0, #0xf0
	add r5, #0x9b
	bic r1, r0
	mov r0, #0x80
	orr r0, r1
	strb r0, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02014730
FUN_02014730: ; 0x02014730
	push {r3, lr}
	sub sp, #0x8
	add r3, r0, #0x0
	ldr r0, [r1, #0x8]
	mov r1, #0x1
	str r0, [sp, #0x0]
	add r0, r3, #0x0
	add r0, #0x84
	ldr r0, [r0, #0x0]
	str r0, [sp, #0x4]
	ldr r2, [r3, #0x7c]
	add r3, #0x80
	ldr r3, [r3, #0x0]
	mov r0, #0x54
	bl FUN_02014A3C
	add sp, #0x8
	pop {r3, pc}

	thumb_func_start FUN_02014754
FUN_02014754: ; 0x02014754
	push {r3, lr}
	sub sp, #0x8
	add r3, r1, #0x0
	add r1, r0, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	cmp r1, #0x4
	bhs _02014768
	mov r2, #0x0
	b _0201476A
_02014768:
	mov r2, #0x4
_0201476A:
	mov r1, #0x40
	str r1, [sp, #0x0]
	add r0, #0x84
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	str r0, [sp, #0x4]
	ldr r3, [r3, #0xc]
	mov r0, #0x54
	lsl r3, r3, #0x5
	bl FUN_02014A8C
	add sp, #0x8
	pop {r3, pc}

	thumb_func_start FUN_02014784
FUN_02014784: ; 0x02014784
	push {r3-r7, lr}
	sub sp, #0x30
	add r7, r0, #0x0
	mov r3, #0x0
	add r4, r7, #0x0
_0201478E:
	add r0, r4, #0x0
	add r3, r3, #0x1
	lsl r2, r3, #0xc
	add r0, #0x88
	add r4, r4, #0x4
	str r2, [r0, #0x0]
	cmp r3, #0x4
	blt _0201478E
	ldr r0, [r7, #0x7c]
	mov r5, #0x0
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r4, r7, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x54
	str r0, [sp, #0x8]
	ldr r0, [r1, #0x8]
	add r6, r5, #0x0
	str r0, [sp, #0x1c]
	ldr r0, [r1, #0xc]
	add r4, #0xc
	str r0, [sp, #0x20]
	add r0, r7, #0x0
	add r0, #0x88
	str r0, [sp, #0x24]
	mov r0, #0x4
	str r0, [sp, #0x28]
	add r0, r7, #0x0
	add r0, #0x98
	ldrb r1, [r0, #0x0]
	add r0, sp, #0x20
	strb r1, [r0, #0xc]
_020147D2:
	mov r1, #0x0
	mov r2, #0x2
	add r3, sp, #0x0
_020147D8:
	add r0, r5, r2
	str r0, [r3, #0xc]
	add r1, r1, #0x1
	add r2, r2, #0x2
	add r3, r3, #0x4
	cmp r1, #0x4
	blt _020147D8
	add r0, r7, #0x0
	add r0, #0x99
	ldrb r0, [r0, #0x0]
	add r2, r7, #0x0
	add r2, #0x84
	add r1, r0, r6
	add r0, sp, #0x20
	strb r1, [r0, #0xd]
	ldr r0, [sp, #0x20]
	add r1, sp, #0x0
	add r0, r0, r5
	str r0, [sp, #0x20]
	ldr r2, [r2, #0x0]
	add r0, r4, #0x0
	bl FUN_020148A8
	add r5, r5, #0x1
	add r6, r6, #0x4
	add r4, #0x38
	cmp r5, #0x2
	blt _020147D2
	add sp, #0x30
	pop {r3-r7, pc}

	thumb_func_start FUN_02014814
FUN_02014814: ; 0x02014814
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r4, #0x0
_02014820:
	add r3, r4, #0x0
	add r3, #0x99
	ldrb r3, [r3, #0x0]
	add r0, r0, #0x1
	lsl r3, r3, #0x3
	add r3, r3, r1
	strb r3, [r2, #0x4]
	add r3, r4, #0x0
	add r3, #0x99
	ldrb r3, [r3, #0x0]
	lsl r3, r3, #0x3
	add r3, r3, r1
	add r3, #0x20
	strb r3, [r2, #0x5]
	add r3, r4, #0x0
	add r3, #0x98
	ldrb r3, [r3, #0x0]
	add r1, #0x20
	lsl r3, r3, #0x3
	strb r3, [r2, #0x6]
	add r3, r4, #0x0
	add r3, #0x98
	ldrb r3, [r3, #0x0]
	lsl r3, r3, #0x3
	add r3, #0x30
	strb r3, [r2, #0x7]
	add r2, r2, #0x4
	cmp r0, #0x2
	blt _02014820
	add r0, r4, #0x0
	add r0, #0x84
	ldr r0, [r0, #0x0]
	ldr r2, _02014874 ; =FUN_02014878
	str r0, [sp, #0x0]
	add r0, r4, #0x4
	mov r1, #0x2
	add r3, r4, #0x0
	bl FUN_020220C4
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_02014874: .word FUN_02014878

	thumb_func_start FUN_02014878
FUN_02014878: ; 0x02014878
	push {r4, lr}
	add r3, r2, #0x0
	add r3, #0x9b
	ldrb r3, [r3, #0x0]
	mov r4, #0xf0
	bic r3, r4
	lsl r4, r1, #0x18
	lsr r4, r4, #0x18
	lsl r4, r4, #0x1c
	lsr r4, r4, #0x18
	orr r4, r3
	add r3, r2, #0x0
	add r3, #0x9b
	strb r4, [r3, #0x0]
	cmp r1, #0x0
	bne _020148A2
	add r2, #0x9a
	strb r0, [r2, #0x0]
	ldr r0, _020148A4 ; =0x000005E4
	bl FUN_020054C8
_020148A2:
	pop {r4, pc}
	.balign 4
_020148A4: .word 0x000005E4

	thumb_func_start FUN_020148A8
FUN_020148A8: ; 0x020148A8
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r1, #0x0
	str r2, [sp, #0x8]
	str r0, [sp, #0x4]
	ldr r1, [r5, #0x24]
	ldr r2, [r5, #0x28]
	add r0, #0x28
	bl FUN_020149FC
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0x4]
	ldr r6, [sp, #0x4]
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x4]
	ldr r4, [sp, #0x4]
	str r1, [r0, #0x4]
	add r0, r5, #0x0
	add r0, #0x2c
	ldrb r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	add r6, #0x18
	add r0, #0x34
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x2d
	ldrb r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	add r7, r5, #0x0
	add r0, #0x35
	strb r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [sp, #0xc]
_020148EA:
	ldr r0, [sp, #0x8]
	mov r2, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x8]
	ldr r1, [r7, #0xc]
	add r3, r6, #0x0
	bl FUN_02006BDC
	str r0, [r4, #0x8]
	ldr r0, [r4, #0x18]
	ldr r1, [r5, #0x1c]
	bl FUN_02014BA4
	ldr r0, [r4, #0x18]
	ldr r1, [r5, #0x20]
	bl FUN_02014BC4
	ldr r0, [sp, #0xc]
	add r6, r6, #0x4
	add r0, r0, #0x1
	add r7, r7, #0x4
	add r4, r4, #0x4
	str r0, [sp, #0xc]
	cmp r0, #0x4
	blt _020148EA
	ldr r0, [sp, #0x4]
	bl FUN_020149D0
	ldr r0, [sp, #0x4]
	mov r1, #0x0
	add r0, #0x36
	str r0, [sp, #0x4]
	strb r1, [r0, #0x0]
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_02014930
FUN_02014930: ; 0x02014930
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x28
	bl FUN_02014A10
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x36
	ldrb r0, [r0, #0x0]
	cmp r0, r4
	beq _02014952
	add r0, r5, #0x0
	bl FUN_020149D0
	add r0, r5, #0x0
	add r0, #0x36
	strb r4, [r0, #0x0]
_02014952:
	ldr r0, [r5, #0x2c]
	sub r0, r0, #0x1
	cmp r4, r0
	bne _0201495E
	mov r0, #0x1
	pop {r3-r5, pc}
_0201495E:
	add r5, #0x28
	mov r1, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0xc
	bl FUN_02014A08
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02014970
FUN_02014970: ; 0x02014970
	push {r4-r6, lr}
	sub sp, #0x10
	add r6, r0, #0x0
	add r0, #0x35
	ldrb r0, [r0, #0x0]
	ldr r1, [r6, #0x18]
	add r3, r6, #0x0
	str r0, [sp, #0x0]
	ldrh r0, [r1, #0x0]
	mov r2, #0x0
	add r3, #0x34
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x4]
	ldrh r0, [r1, #0x2]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	str r2, [sp, #0xc]
	ldr r1, [r6, #0x4]
	ldrb r3, [r3, #0x0]
	lsl r1, r1, #0x18
	ldr r0, [r6, #0x0]
	lsr r1, r1, #0x18
	bl FUN_02018540
	ldr r1, [r6, #0x4]
	ldr r0, [r6, #0x0]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_0201AC68
	mov r4, #0x0
	add r5, r6, #0x0
_020149B4:
	ldr r0, [r5, #0x8]
	bl FUN_02016A18
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blt _020149B4
	add r0, r6, #0x0
	mov r1, #0x0
	mov r2, #0x38
	bl Call_FillMemWithValue
	add sp, #0x10
	pop {r4-r6, pc}

	thumb_func_start FUN_020149D0
FUN_020149D0: ; 0x020149D0
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r0, #0x28
	bl FUN_02014A10
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x35
	ldrb r0, [r0, #0x0]
	lsl r2, r2, #0x2
	add r2, r4, r2
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	add r4, #0x34
	ldrb r3, [r4, #0x0]
	ldr r2, [r2, #0x18]
	bl FUN_02014B58
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_020149FC
FUN_020149FC: ; 0x020149FC
	str r1, [r0, #0x0]
	str r2, [r0, #0x4]
	mov r1, #0x0
	str r1, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start FUN_02014A08
FUN_02014A08: ; 0x02014A08
	ldr r2, [r0, #0x8]
	add r1, r2, r1
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02014A10
FUN_02014A10: ; 0x02014A10
	push {r4-r5}
	ldr r5, [r0, #0x4]
	mov r2, #0x0
	cmp r5, #0x0
	bls _02014A34
	ldr r3, [r0, #0x0]
	ldr r4, [r0, #0x8]
_02014A1E:
	ldr r1, [r3, #0x0]
	cmp r1, r4
	blt _02014A2A
	add r0, r2, #0x0
	pop {r4-r5}
	bx lr
_02014A2A:
	ldr r1, [r0, #0x4]
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, r1
	blo _02014A1E
_02014A34:
	sub r0, r5, #0x1
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_02014A3C
FUN_02014A3C: ; 0x02014A3C
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	str r1, [sp, #0x4]
	ldr r0, [sp, #0x24]
	mov r1, #0x14
	add r5, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	add r2, r4, #0x0
	mov r1, #0x14
	mov r0, #0x0
_02014A58:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _02014A58
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x4]
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	mov r2, #0x1
	add r3, r4, #0x4
	bl FUN_02006BB0
	str r0, [r4, #0x8]
	str r5, [r4, #0x0]
	ldr r0, [sp, #0x20]
	str r6, [r4, #0xc]
	str r0, [r4, #0x10]
	ldr r0, _02014A88 ; =FUN_02014AD4
	add r1, r4, #0x0
	mov r2, #0x80
	bl FUN_0200CA98
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02014A88: .word FUN_02014AD4

	thumb_func_start FUN_02014A8C
FUN_02014A8C: ; 0x02014A8C
	push {r3-r7, lr}
	add r7, r0, #0x0
	str r1, [sp, #0x0]
	ldr r0, [sp, #0x1c]
	mov r1, #0x14
	add r5, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	add r2, r4, #0x0
	mov r1, #0x14
	mov r0, #0x0
_02014AA6:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _02014AA6
	ldr r1, [sp, #0x0]
	ldr r3, [sp, #0x1c]
	add r0, r7, #0x0
	add r2, r4, #0x0
	bl FUN_02006C08
	str r0, [r4, #0x4]
	str r5, [r4, #0x8]
	ldr r0, [sp, #0x18]
	str r6, [r4, #0xc]
	str r0, [r4, #0x10]
	ldr r0, _02014AD0 ; =FUN_02014B10
	add r1, r4, #0x0
	mov r2, #0x80
	bl FUN_0200CA98
	pop {r3-r7, pc}
	.balign 4
_02014AD0: .word FUN_02014B10

	thumb_func_start FUN_02014AD4
FUN_02014AD4: ; 0x02014AD4
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, [r4, #0x4]
	add r5, r0, #0x0
	ldr r0, [r1, #0x14]
	ldr r1, [r1, #0x10]
	bl DC_FlushRange
	ldr r3, [r4, #0x4]
	ldr r0, [r4, #0x10]
	str r0, [sp, #0x0]
	ldr r1, [r4, #0xc]
	ldr r2, [r3, #0x14]
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x0]
	ldr r3, [r3, #0x10]
	lsr r1, r1, #0x18
	bl FUN_02017E14
	add r0, r5, #0x0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x8]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02014B10
FUN_02014B10: ; 0x02014B10
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x10]
	ldr r0, [r0, #0xc]
	bl DC_FlushRange
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	bne _02014B34
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0xc]
	ldr r0, [r0, #0xc]
	ldr r2, [r4, #0x10]
	bl GX_LoadBGPltt
	b _02014B44
_02014B34:
	cmp r0, #0x4
	bne _02014B44
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0xc]
	ldr r0, [r0, #0xc]
	ldr r2, [r4, #0x10]
	bl GXS_LoadBGPltt
_02014B44:
	add r0, r5, #0x0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x4]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r3-r5, pc}

	thumb_func_start FUN_02014B58
FUN_02014B58: ; 0x02014B58
	push {r3-r6, lr}
	sub sp, #0x1c
	add r4, r1, #0x0
	add r1, r2, #0x0
	add r2, r3, #0x0
	ldrh r6, [r1, #0x0]
	ldrh r3, [r1, #0x2]
	lsl r2, r2, #0x18
	lsl r6, r6, #0x15
	lsr r6, r6, #0x18
	lsl r3, r3, #0x15
	str r6, [sp, #0x0]
	lsr r3, r3, #0x18
	str r3, [sp, #0x4]
	add r1, #0xc
	str r1, [sp, #0x8]
	mov r1, #0x0
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	str r6, [sp, #0x14]
	str r3, [sp, #0x18]
	ldr r3, [sp, #0x30]
	lsl r1, r4, #0x18
	lsl r3, r3, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	add r5, r0, #0x0
	bl FUN_02018170
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_0201AC68
	add sp, #0x1c
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02014BA4
FUN_02014BA4: ; 0x02014BA4
	push {r3-r4}
	ldr r2, [r0, #0x8]
	add r0, #0xc
	lsr r4, r2, #0x1
	mov r3, #0x0
	cmp r4, #0x0
	ble _02014BC0
_02014BB2:
	ldrh r2, [r0, #0x0]
	add r3, r3, #0x1
	add r2, r2, r1
	strh r2, [r0, #0x0]
	add r0, r0, #0x2
	cmp r3, r4
	blt _02014BB2
_02014BC0:
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02014BC4
FUN_02014BC4: ; 0x02014BC4
	push {r4-r5}
	ldr r2, [r0, #0x8]
	add r0, #0xc
	lsr r3, r2, #0x1
	mov r2, #0x0
	cmp r3, #0x0
	ble _02014BEA
	ldr r4, _02014BF0 ; =0x00000FFF
	lsl r1, r1, #0xc
_02014BD6:
	ldrh r5, [r0, #0x0]
	add r2, r2, #0x1
	and r5, r4
	strh r5, [r0, #0x0]
	ldrh r5, [r0, #0x0]
	orr r5, r1
	strh r5, [r0, #0x0]
	add r0, r0, #0x2
	cmp r2, r3
	blt _02014BD6
_02014BEA:
	pop {r4-r5}
	bx lr
	nop
_02014BF0: .word 0x00000FFF

	thumb_func_start FUN_02014BF4
FUN_02014BF4: ; 0x02014BF4
	push {r3-r7, lr}
	add r7, r1, #0x0
	mov r1, #0xc
	add r5, r0, #0x0
	add r6, r2, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	strb r6, [r4, #0x8]
	mov r0, #0x1d
	strb r7, [r4, #0x9]
	lsl r0, r0, #0x4
	add r6, r7, #0x0
	mul r6, r0
	add r0, r5, #0x0
	add r1, r6, #0x0
	str r5, [r4, #0x4]
	bl FUN_02016998
	mov r1, #0x0
	add r2, r6, #0x0
	str r0, [r4, #0x0]
	bl MI_CpuFill8
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02014C28
FUN_02014C28: ; 0x02014C28
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02014C3C
FUN_02014C3C: ; 0x02014C3C
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x19
	blo _02014C48
	bl ErrorHandling
_02014C48:
	ldr r0, _02014C50 ; =0x020ED64C
	ldrb r0, [r0, r4]
	pop {r4, pc}
	nop
_02014C50: .word 0x020ED64C

	thumb_func_start FUN_02014C54
FUN_02014C54: ; 0x02014C54
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	str r3, [sp, #0x4]
	add r0, r2, #0x0
	ldrh r6, [r0, #0x0]
	ldrh r0, [r0, #0x2]
	add r7, r1, #0x0
	ldrb r1, [r5, #0x9]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4]
	str r2, [sp, #0x0]
	cmp r0, r1
	blo _02014C74
	bl ErrorHandling
_02014C74:
	ldr r0, [sp, #0x4]
	mov r1, #0x1d
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r5, #0x0]
	mul r4, r1
	add r0, r0, r4
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	beq _02014C8C
	bl ErrorHandling
_02014C8C:
	ldr r0, [r5, #0x0]
	mov r2, #0x1d
	add r0, r0, r4
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl MI_CpuFill8
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	add r0, r0, r4
	str r1, [r0, #0x10]
	ldr r0, [r5, #0x0]
	cmp r6, #0x86
	str r7, [r0, r4]
	blt _02014CAE
	mov r6, #0x0
	str r6, [sp, #0x8]
_02014CAE:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	str r6, [r0, #0x14]
	ldrb r0, [r5, #0x8]
	cmp r0, #0x0
	beq _02014CC0
	ldr r0, [sp, #0x0]
	ldrb r2, [r0, #0x4]
	b _02014CC2
_02014CC0:
	mov r2, #0x0
_02014CC2:
	ldr r0, [r5, #0x0]
	add r1, r0, r4
	mov r0, #0x73
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	ldr r1, [r5, #0x0]
	ldr r2, [r5, #0x4]
	add r1, r1, r4
	ldr r1, [r1, #0x14]
	mov r0, #0x5e
	bl FUN_02006528
	ldr r1, [r5, #0x0]
	mov r2, #0x0
	add r1, r1, r4
	str r0, [r1, #0x8]
	ldr r0, [r5, #0x0]
	mov r6, #0x1c
	add r1, r0, r4
	ldr r0, [r1, #0x8]
	str r0, [r1, #0xc]
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	str r2, [r0, #0x1c]
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	str r2, [r0, #0x20]
	ldr r0, [r5, #0x0]
	add r1, r0, r4
	ldr r0, _02014D74 ; =0x000001CD
	strb r2, [r1, r0]
	ldr r1, [r5, #0x0]
	add r3, r1, r4
	add r1, r0, #0x1
	strb r6, [r3, r1]
	ldr r1, [r5, #0x0]
	add r0, r0, #0x2
	add r1, r1, r4
	strb r2, [r1, r0]
	ldr r1, [r5, #0x0]
	ldr r0, _02014D78 ; =FUN_02014DD8
	add r1, r1, r4
	bl FUN_0200CA44
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x4]
	ldr r0, [r5, #0x0]
	add r1, r0, r4
	ldr r0, [sp, #0x8]
	str r0, [r1, #0x54]
	add r0, r7, #0x0
	mov r1, #0x0
	bl FUN_0200782C
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x58]
	add r0, r7, #0x0
	mov r1, #0x1
	bl FUN_0200782C
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x5c]
	ldr r1, [r5, #0x0]
	mov r0, #0x0
	add r1, r1, r4
	str r0, [r1, #0x60]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x64]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x68]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x6c]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x70]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x74]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x78]
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02014D74: .word 0x000001CD
_02014D78: .word FUN_02014DD8

	thumb_func_start FUN_02014D7C
FUN_02014D7C: ; 0x02014D7C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0x9]
	add r4, r1, #0x0
	cmp r4, r0
	blo _02014D8C
	bl ErrorHandling
_02014D8C:
	mov r0, #0x1d
	lsl r0, r0, #0x4
	ldr r1, [r5, #0x0]
	mul r0, r4
	add r0, r1, r0
	ldr r0, [r0, #0x20]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02014D9C
FUN_02014D9C: ; 0x02014D9C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x1d
	lsl r0, r0, #0x4
	add r4, r1, #0x0
	mul r4, r0
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _02014DD6
	bl FUN_0200CAB4
	ldr r1, [r5, #0x0]
	mov r0, #0x0
	add r1, r1, r4
	str r0, [r1, #0x4]
	ldr r1, [r5, #0x0]
	mov r2, #0x1
	add r1, r1, r4
	str r2, [r1, #0x20]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x10]
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x8]
	bl FUN_02016A18
_02014DD6:
	pop {r3-r5, pc}

	thumb_func_start FUN_02014DD8
FUN_02014DD8: ; 0x02014DD8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x54]
	cmp r0, #0x0
	bne _02014DEC
	add r0, r4, #0x0
	bl FUN_02014E10
	b _02014DF0
_02014DEC:
	sub r0, r0, #0x1
	str r0, [r4, #0x54]
_02014DF0:
	ldr r0, [r4, #0x1c]
	cmp r0, #0x0
	beq _02014E0E
	mov r0, #0x1
	str r0, [r4, #0x20]
	mov r0, #0x0
	str r0, [r4, #0x10]
	add r0, r5, #0x0
	bl FUN_0200CAB4
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x8]
	bl FUN_02016A18
_02014E0E:
	pop {r3-r5, pc}

	thumb_func_start FUN_02014E10
FUN_02014E10: ; 0x02014E10
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r6, #0x0
	str r6, [r5, #0x18]
	add r7, r5, #0x0
	str r6, [r5, #0x44]
	add r4, r6, #0x0
	add r7, #0x7c
_02014E20:
	mov r0, #0x54
	add r1, r4, #0x0
	mul r1, r0
	add r0, r7, r1
	ldr r1, [r7, r1]
	cmp r1, #0x0
	beq _02014E4E
	add r1, r0, #0x0
	add r1, #0x2d
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02014E40
	ldr r2, [r0, #0x50]
	add r1, r5, #0x0
	blx r2
	b _02014E54
_02014E40:
	add r1, r0, #0x0
	add r1, #0x2d
	ldrb r1, [r1, #0x0]
	add r0, #0x2d
	sub r1, r1, #0x1
	strb r1, [r0, #0x0]
	b _02014E54
_02014E4E:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_02014E54:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x4
	blo _02014E20
	cmp r6, #0x4
	bne _02014E68
	ldr r0, _02014EFC ; =0x000001CD
	mov r1, #0x0
	strb r1, [r5, r0]
_02014E68:
	ldr r0, _02014EFC ; =0x000001CD
	ldrb r1, [r5, r0]
	cmp r1, #0x0
	beq _02014E7E
	add r0, r5, #0x0
	bl FUN_020156E8
	add r0, r5, #0x0
	bl FUN_02015730
	pop {r3-r7, pc}
_02014E7E:
	add r0, r0, #0x2
	ldrb r0, [r5, r0]
	cmp r0, #0x0
	beq _02014E96
	ldr r0, [r5, #0x0]
	bl FUN_02007F20
	cmp r0, #0x0
	bne _02014EF8
	ldr r0, _02014F00 ; =0x000001CF
	mov r1, #0x0
	strb r1, [r5, r0]
_02014E96:
	add r6, r5, #0x0
	add r4, r5, #0x0
	ldr r7, _02014F04 ; =0x020ED6A4
	add r6, #0xc
	add r4, #0x44
_02014EA0:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x0]
	cmp r0, #0x22
	blo _02014EB2
	bl ErrorHandling
_02014EB2:
	ldr r1, [r5, #0xc]
	add r0, r5, #0x0
	ldr r1, [r1, #0x0]
	lsl r1, r1, #0x2
	ldr r1, [r7, r1]
	blx r1
	ldr r0, [r5, #0x1c]
	cmp r0, #0x0
	bne _02014EF8
	ldr r0, [r6, #0x0]
	add r0, r0, #0x4
	str r0, [r6, #0x0]
	ldr r0, [r5, #0x18]
	cmp r0, #0x0
	bne _02014EF8
	ldr r0, _02014EFC ; =0x000001CD
	ldrb r0, [r5, r0]
	cmp r0, #0x0
	beq _02014EE6
	add r0, r5, #0x0
	bl FUN_020156E8
	add r0, r5, #0x0
	bl FUN_02015730
	pop {r3-r7, pc}
_02014EE6:
	mov r0, #0x1
	ldr r1, [r5, #0x44]
	lsl r0, r0, #0x8
	cmp r1, r0
	blt _02014EA0
	bl ErrorHandling
	mov r0, #0x1
	str r0, [r5, #0x1c]
_02014EF8:
	pop {r3-r7, pc}
	nop
_02014EFC: .word 0x000001CD
_02014F00: .word 0x000001CF
_02014F04: .word 0x020ED6A4

	thumb_func_start FUN_02014F08
FUN_02014F08: ; 0x02014F08
	push {r4, lr}
	lsl r1, r1, #0x2
	ldr r4, [r0, r1]
	cmp r2, #0x1
	beq _02014F16
	bl ErrorHandling
_02014F16:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02014F1C
FUN_02014F1C: ; 0x02014F1C
	ldr r3, _02014F24 ; =FUN_02014F08
	add r2, r1, #0x0
	mov r1, #0x0
	bx r3
	.balign 4
_02014F24: .word FUN_02014F08

	thumb_func_start FUN_02014F28
FUN_02014F28: ; 0x02014F28
	ldr r3, _02014F30 ; =FUN_02014F1C
	mov r1, #0x1
	bx r3
	nop
_02014F30: .word FUN_02014F1C

	thumb_func_start FUN_02014F34
FUN_02014F34: ; 0x02014F34
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r3, #0x0
	add r0, #0x7c
	mov r2, #0x54
_02014F3E:
	add r1, r3, #0x0
	mul r1, r2
	add r4, r0, r1
	ldr r1, [r0, r1]
	cmp r1, #0x0
	bne _02014F68
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x54
	bl MI_CpuFill8
	mov r0, #0x1
	str r0, [r4, #0x0]
	mov r0, #0xc
	add r1, r5, #0x0
	mul r1, r0
	ldr r0, _02014F7C ; =0x020ED668
	ldr r0, [r0, r1]
	str r0, [r4, #0x50]
	add r0, r4, #0x0
	pop {r3-r5, pc}
_02014F68:
	add r1, r3, #0x1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0x4
	blo _02014F3E
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_02014F7C: .word 0x020ED668

	thumb_func_start FUN_02014F80
FUN_02014F80: ; 0x02014F80
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, [r0, #0xc]
	add r1, r1, #0x4
	str r1, [r0, #0xc]
	add r0, r1, #0x0
	bl FUN_02014F28
	str r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02014F94
FUN_02014F94: ; 0x02014F94
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, [r0, #0xc]
	add r1, r1, #0x4
	str r1, [r0, #0xc]
	add r0, r1, #0x0
	bl FUN_02014F28
	strb r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02014FA8
FUN_02014FA8: ; 0x02014FA8
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, [r0, #0xc]
	add r1, r1, #0x4
	str r1, [r0, #0xc]
	add r0, r1, #0x0
	bl FUN_02014F28
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x0]
	cmp r0, #0x8
	blo _02014FC4
	bl ErrorHandling
_02014FC4:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02014FC8
FUN_02014FC8: ; 0x02014FC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02014FA8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02014FA8
	pop {r3-r5, pc}

	thumb_func_start FUN_02014FDC
FUN_02014FDC: ; 0x02014FDC
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02014FA8
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x12
	bne _0201501C
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x2
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	add r1, r6, #0x0
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02014F80
	add sp, #0x4
	pop {r3-r6, pc}
_0201501C:
	cmp r0, #0x13
	bne _02015048
	add r1, sp, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x2
	add r2, #0x1
	bl FUN_02014FC8
	add r0, sp, #0x0
	ldrb r1, [r0, #0x2]
	add sp, #0x4
	lsl r1, r1, #0x2
	add r1, r5, r1
	ldr r1, [r1, #0x24]
	str r1, [r4, #0x0]
	ldrb r0, [r0, #0x1]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [r6, #0x0]
	pop {r3-r6, pc}
_02015048:
	bl ErrorHandling
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start FUN_02015050
FUN_02015050: ; 0x02015050
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02014FA8
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x1
	bl FUN_02014F94
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	cmp r0, #0x12
	bne _02015082
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02014F80
	b _020150A2
_02015082:
	cmp r0, #0x13
	bne _0201509E
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x3]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x0]
	b _020150A2
_0201509E:
	bl ErrorHandling
_020150A2:
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x12
	bne _020150B6
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02014F80
	add sp, #0x4
	pop {r3-r6, pc}
_020150B6:
	cmp r0, #0x13
	bne _020150D4
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x2
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [r6, #0x0]
	pop {r3-r6, pc}
_020150D4:
	bl ErrorHandling
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start FUN_020150DC
FUN_020150DC: ; 0x020150DC
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r2, #0x0
	add r2, sp, #0x0
	add r2, #0x3
	add r5, r0, #0x0
	add r6, r3, #0x0
	bl FUN_02014FC8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x3]
	add r1, sp, #0x0
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r7, [r0, #0x24]
	add r0, r5, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x14
	bne _02015112
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02014F80
	b _02015132
_02015112:
	cmp r0, #0x15
	bne _0201512E
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x2
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [r6, #0x0]
	b _02015132
_0201512E:
	bl ErrorHandling
_02015132:
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x14
	bne _0201514C
	add r0, r5, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	b _0201516C
_0201514C:
	cmp r0, #0x15
	bne _02015168
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x1
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x4]
	b _0201516C
_02015168:
	bl ErrorHandling
_0201516C:
	ldr r0, [sp, #0x4]
	add r0, r7, r0
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x10
	sub r1, r1, r2
	mov r0, #0x10
	ror r1, r0
	add r0, r2, r1
	str r0, [r4, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02015184
FUN_02015184: ; 0x02015184
	ldr r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	sub r0, r2, r0
	bpl _02015190
	mov r0, #0xf
	bx lr
_02015190:
	cmp r0, #0x0
	ble _02015198
	mov r0, #0x10
	bx lr
_02015198:
	mov r0, #0x11
	bx lr

	thumb_func_start FUN_0201519C
FUN_0201519C: ; 0x0201519C
	add r2, r0, #0x0
	ldr r0, [r2, #0x0]
	ldr r2, [r2, #0x74]
	mov r1, #0x1
	neg r3, r2
	asr r2, r3, #0x2
	lsr r2, r2, #0x1d
	add r2, r3, r2
	ldr r3, _020151B4 ; =FUN_020079E0
	asr r2, r2, #0x3
	bx r3
	nop
_020151B4: .word FUN_020079E0

	thumb_func_start FUN_020151B8
FUN_020151B8: ; 0x020151B8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020151D0
	mov r0, #0x1
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	pop {r4, pc}

	thumb_func_start FUN_020151C8
FUN_020151C8: ; 0x020151C8
	mov r1, #0x1
	str r1, [r0, #0x18]
	bx lr
	.balign 4

	thumb_func_start FUN_020151D0
FUN_020151D0: ; 0x020151D0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r2, [r4, #0x58]
	mov r1, #0x0
	bl FUN_02007558
	ldr r0, [r4, #0x0]
	ldr r2, [r4, #0x5c]
	mov r1, #0x1
	bl FUN_02007558
	ldr r0, [r4, #0x0]
	mov r1, #0x9
	mov r2, #0x0
	bl FUN_02007558
	ldr r0, [r4, #0x0]
	mov r1, #0xa
	mov r2, #0x0
	bl FUN_02007558
	mov r1, #0xc
	add r2, r1, #0x0
	ldr r0, [r4, #0x0]
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0x0
	ldr r0, [r4, #0x0]
	add r2, #0xf3
	bl FUN_02007558
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02015218
FUN_02015218: ; 0x02015218
	push {r3-r4, lr}
	sub sp, #0x4
	add r1, sp, #0x0
	add r1, #0x1
	add r2, sp, #0x0
	add r4, r0, #0x0
	bl FUN_02014FC8
	add r0, sp, #0x0
	ldrb r1, [r0, #0x0]
	ldrb r0, [r0, #0x1]
	lsl r1, r1, #0x2
	add r1, r4, r1
	lsl r0, r0, #0x2
	ldr r1, [r1, #0x24]
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02015240
FUN_02015240: ; 0x02015240
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_02014FDC
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r1, r1, r0
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_02015264
FUN_02015264: ; 0x02015264
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_02014FDC
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r2, r1, #0x0
	mul r2, r0
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r2, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201528C
FUN_0201528C: ; 0x0201528C
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_02015050
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0x4]
	sub r1, r1, r0
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_020152B0
FUN_020152B0: ; 0x020152B0
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_02015050
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	bl _s32_div_f
	add r1, sp, #0x0
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x2
	add r1, r4, r1
	str r0, [r1, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_020152D8
FUN_020152D8: ; 0x020152D8
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_02015050
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	bl _s32_div_f
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02015300
FUN_02015300: ; 0x02015300
	push {r3-r5, lr}
	sub sp, #0x10
	add r1, sp, #0x0
	add r5, r0, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x14
	bne _02015334
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x3]
	add r1, sp, #0x8
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl FUN_02014F80
	b _02015362
_02015334:
	cmp r0, #0x15
	bne _0201535E
	add r1, sp, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3
	add r2, #0x2
	bl FUN_02014FC8
	add r0, sp, #0x0
	ldrb r1, [r0, #0x3]
	lsl r1, r1, #0x2
	add r1, r5, r1
	ldr r1, [r1, #0x24]
	str r1, [sp, #0xc]
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x8]
	b _02015362
_0201535E:
	bl ErrorHandling
_02015362:
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x1
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	cmp r0, #0x11
	bls _02015378
	bl ErrorHandling
_02015378:
	add r0, sp, #0xc
	add r1, sp, #0x8
	bl FUN_02015184
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x14
	bne _020153A6
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3
	bl FUN_02014FA8
	add r0, r5, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	b _020153CA
_020153A6:
	cmp r0, #0x15
	bne _020153C6
	add r1, sp, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3
	add r2, #0x2
	bl FUN_02014FC8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x4]
	b _020153CA
_020153C6:
	bl ErrorHandling
_020153CA:
	add r0, sp, #0x0
	ldrb r1, [r0, #0x1]
	cmp r1, r4
	bne _020153DC
	ldrb r0, [r0, #0x3]
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x2
	add r0, r5, r0
	str r1, [r0, #0x24]
_020153DC:
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_020153E0
FUN_020153E0: ; 0x020153E0
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r1, sp, #0x0
	bl FUN_02014FA8
	ldr r0, [r4, #0xc]
	add r0, r0, #0x4
	str r0, [r4, #0xc]
	bl FUN_02014F28
	add r1, sp, #0x0
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x2
	add r1, r4, r1
	str r0, [r1, #0x24]
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02015404
FUN_02015404: ; 0x02015404
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x50]
	cmp r0, #0x0
	beq _02015412
	bl ErrorHandling
_02015412:
	ldr r0, [r4, #0xc]
	add r0, r0, #0x4
	str r0, [r4, #0xc]
	str r0, [r4, #0x50]
	ldr r0, [r4, #0xc]
	bl FUN_02014F28
	str r0, [r4, #0x48]
	mov r0, #0x0
	str r0, [r4, #0x4c]
	pop {r4, pc}

	thumb_func_start FUN_02015428
FUN_02015428: ; 0x02015428
	ldr r1, [r0, #0x4c]
	add r2, r1, #0x1
	str r2, [r0, #0x4c]
	ldr r1, [r0, #0x48]
	cmp r2, r1
	blt _0201543E
	mov r1, #0x0
	str r1, [r0, #0x50]
	str r1, [r0, #0x4c]
	str r1, [r0, #0x48]
	bx lr
_0201543E:
	ldr r1, [r0, #0x50]
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start FUN_02015444
FUN_02015444: ; 0x02015444
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02014FA8
	add r2, sp, #0x0
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, [sp, #0x4]
	lsl r2, r2, #0x2
	add r2, r4, r2
	ldr r2, [r2, #0x24]
	bl FUN_02007558
	add sp, #0x8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02015470
FUN_02015470: ; 0x02015470
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02014FA8
	add r2, sp, #0x0
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, [sp, #0x4]
	lsl r2, r2, #0x2
	add r2, r4, r2
	ldr r2, [r2, #0x24]
	bl FUN_020079E0
	add sp, #0x8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201549C
FUN_0201549C: ; 0x0201549C
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x8
	add r4, r0, #0x0
	bl FUN_02014F80
	add r1, sp, #0x0
	add r0, r4, #0x0
	add r1, #0x1
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	cmp r0, #0x14
	bne _020154C4
	add r0, r4, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	b _020154E4
_020154C4:
	cmp r0, #0x15
	bne _020154E0
	add r1, sp, #0x0
	add r0, r4, #0x0
	add r1, #0x2
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x4]
	b _020154E4
_020154E0:
	bl ErrorHandling
_020154E4:
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x16
	bne _02015502
	ldr r0, [r4, #0x0]
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0x4]
	bl FUN_02007558
	add sp, #0xc
	pop {r3-r4, pc}
_02015502:
	cmp r0, #0x17
	bne _02015514
	ldr r0, [r4, #0x0]
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0x4]
	bl FUN_020079E0
	add sp, #0xc
	pop {r3-r4, pc}
_02015514:
	bl ErrorHandling
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0201551C
FUN_0201551C: ; 0x0201551C
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_020150DC
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x4]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _0201554C ; =0x020FFA38
	ldrsh r0, [r0, r1]
	mul r0, r2
	asr r1, r0, #0xc
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_0201554C: .word 0x020FFA38

	thumb_func_start FUN_02015550
FUN_02015550: ; 0x02015550
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_020150DC
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0x4]
	asr r1, r1, #0x4
	lsl r1, r1, #0x1
	add r1, r1, #0x1
	lsl r2, r1, #0x1
	ldr r1, _02015584 ; =0x020FFA38
	ldrsh r1, [r1, r2]
	mul r1, r0
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	asr r1, r1, #0xc
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_02015584: .word 0x020FFA38

	thumb_func_start FUN_02015588
FUN_02015588: ; 0x02015588
	push {r3-r4, lr}
	sub sp, #0x4
	add r1, sp, #0x0
	add r4, r0, #0x0
	add r1, #0x1
	bl FUN_02014FA8
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r1, [r0, #0x0]
	cmp r1, #0x8
	bne _020155B4
	ldrb r0, [r0, #0x1]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x60]
	pop {r3-r4, pc}
_020155B4:
	cmp r1, #0x9
	bne _020155C6
	ldrb r0, [r0, #0x1]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x64]
	pop {r3-r4, pc}
_020155C6:
	bl ErrorHandling
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_020155D0
FUN_020155D0: ; 0x020155D0
	push {r3-r4, lr}
	sub sp, #0x4
	add r1, sp, #0x0
	add r4, r0, #0x0
	add r1, #0x1
	bl FUN_02014FA8
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r1, [r0, #0x0]
	cmp r1, #0x8
	bne _02015600
	ldrb r0, [r0, #0x1]
	ldr r1, [r4, #0x60]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	add r0, r1, r0
	str r0, [r4, #0x60]
	pop {r3-r4, pc}
_02015600:
	cmp r1, #0x9
	bne _02015616
	ldrb r0, [r0, #0x1]
	ldr r1, [r4, #0x64]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	add r0, r1, r0
	str r0, [r4, #0x64]
	pop {r3-r4, pc}
_02015616:
	bl ErrorHandling
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02015620
FUN_02015620: ; 0x02015620
	push {r3-r5, lr}
	sub sp, #0x8
	add r1, sp, #0x0
	add r1, #0x3
	add r5, r0, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x3]
	cmp r0, #0x8
	bne _0201563C
	add r4, r5, #0x0
	add r4, #0x60
	b _0201567C
_0201563C:
	cmp r0, #0x9
	bne _02015646
	add r4, r5, #0x0
	add r4, #0x64
	b _0201567C
_02015646:
	cmp r0, #0xa
	bne _02015650
	add r4, r5, #0x0
	add r4, #0x68
	b _0201567C
_02015650:
	cmp r0, #0xb
	bne _0201565A
	add r4, r5, #0x0
	add r4, #0x6c
	b _0201567C
_0201565A:
	cmp r0, #0xc
	bne _02015664
	add r4, r5, #0x0
	add r4, #0x70
	b _0201567C
_02015664:
	cmp r0, #0xd
	bne _0201566E
	add r4, r5, #0x0
	add r4, #0x74
	b _0201567C
_0201566E:
	cmp r0, #0xe
	bne _02015678
	add r4, r5, #0x0
	add r4, #0x78
	b _0201567C
_02015678:
	bl ErrorHandling
_0201567C:
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x1
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	cmp r0, #0x14
	bne _02015698
	add r0, r5, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	b _020156B8
_02015698:
	cmp r0, #0x15
	bne _020156B4
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x2
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x4]
	b _020156B8
_020156B4:
	bl ErrorHandling
_020156B8:
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x16
	bne _020156D0
	ldr r0, [sp, #0x4]
	add sp, #0x8
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
_020156D0:
	cmp r0, #0x17
	bne _020156E0
	ldr r0, [sp, #0x4]
	ldr r1, [r4, #0x0]
	add sp, #0x8
	add r0, r1, r0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
_020156E0:
	bl ErrorHandling
	add sp, #0x8
	pop {r3-r5, pc}

	thumb_func_start FUN_020156E8
FUN_020156E8: ; 0x020156E8
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r0, #0x73
	lsl r0, r0, #0x2
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, [r4, #0x0]
	beq _0201570A
	ldr r3, [r4, #0x60]
	ldr r2, [r4, #0x68]
	ldr r5, [r4, #0x58]
	add r2, r3, r2
	mov r1, #0x0
	sub r2, r5, r2
	bl FUN_02007558
	b _0201571A
_0201570A:
	ldr r3, [r4, #0x58]
	ldr r2, [r4, #0x60]
	ldr r5, [r4, #0x68]
	add r2, r3, r2
	mov r1, #0x0
	add r2, r5, r2
	bl FUN_02007558
_0201571A:
	ldr r3, [r4, #0x5c]
	ldr r2, [r4, #0x64]
	ldr r5, [r4, #0x6c]
	add r2, r3, r2
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	add r2, r5, r2
	bl FUN_02007558
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02015730
FUN_02015730: ; 0x02015730
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0xc
	add r2, r1, #0x0
	ldr r3, [r4, #0x70]
	add r2, #0xf4
	ldr r0, [r4, #0x0]
	add r2, r3, r2
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0x0
	ldr r3, [r4, #0x74]
	add r2, #0xf3
	ldr r0, [r4, #0x0]
	add r2, r3, r2
	bl FUN_02007558
	ldr r2, [r4, #0x78]
	ldr r0, [r4, #0x0]
	lsl r2, r2, #0x10
	mov r1, #0x9
	lsr r2, r2, #0x10
	bl FUN_02007558
	ldr r0, _02015794 ; =0x000001CE
	ldrb r0, [r4, r0]
	cmp r0, #0x1b
	bne _02015778
	ldr r0, [r4, #0x74]
	cmp r0, #0x0
	bge _02015792
	add r0, r4, #0x0
	bl FUN_0201519C
	pop {r4, pc}
_02015778:
	cmp r0, #0x1d
	bne _0201578A
	ldr r0, [r4, #0x74]
	cmp r0, #0x0
	beq _02015792
	add r0, r4, #0x0
	bl FUN_0201519C
	pop {r4, pc}
_0201578A:
	cmp r0, #0x1c
	beq _02015792
	bl ErrorHandling
_02015792:
	pop {r4, pc}
	.balign 4
_02015794: .word 0x000001CE

	thumb_func_start FUN_02015798
FUN_02015798: ; 0x02015798
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r1, sp, #0x0
	bl FUN_02014FA8
	ldr r0, [r4, #0xc]
	add r0, r0, #0x4
	str r0, [r4, #0xc]
	bl FUN_02014F28
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x8
	beq _020157BA
	cmp r0, #0xa
	bne _020157CA
_020157BA:
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x68]
	pop {r3-r4, pc}
_020157CA:
	cmp r0, #0x9
	beq _020157D2
	cmp r0, #0xb
	bne _020157E2
_020157D2:
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x6c]
	pop {r3-r4, pc}
_020157E2:
	bl ErrorHandling
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_020157EC
FUN_020157EC: ; 0x020157EC
	push {r4, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x54
	bl FUN_02014F80
	mov r0, #0x1
	str r0, [r4, #0x18]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02015800
FUN_02015800: ; 0x02015800
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x4
	add r1, #0x2
	add r4, r0, #0x0
	bl FUN_02014F94
	add r1, sp, #0x4
	add r0, r4, #0x0
	add r1, #0x1
	bl FUN_02014F94
	add r0, r4, #0x0
	add r1, sp, #0x4
	bl FUN_02014F94
	add r0, r4, #0x0
	add r1, sp, #0x8
	bl FUN_02014F80
	ldr r0, [sp, #0x8]
	add r3, sp, #0x4
	str r0, [sp, #0x0]
	ldrb r1, [r3, #0x2]
	ldrb r2, [r3, #0x1]
	ldrb r3, [r3, #0x0]
	ldr r0, [r4, #0x0]
	bl FUN_02007E68
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02015840
FUN_02015840: ; 0x02015840
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02007F20
	cmp r0, #0x0
	beq _02015856
	ldr r0, _02015858 ; =0x000001CF
	mov r1, #0x1
	strb r1, [r4, r0]
	str r1, [r4, #0x18]
_02015856:
	pop {r4, pc}
	.balign 4
_02015858: .word 0x000001CF

	thumb_func_start FUN_0201585C
FUN_0201585C: ; 0x0201585C
	ldr r1, _02015864 ; =0x000001CD
	mov r2, #0x1
	strb r2, [r0, r1]
	bx lr
	.balign 4
_02015864: .word 0x000001CD

	thumb_func_start FUN_02015868
FUN_02015868: ; 0x02015868
	push {r4, lr}
	ldr r1, _0201589C ; =0x000001CE
	add r4, r0, #0x0
	add r1, r4, r1
	bl FUN_02014F94
	ldr r0, _0201589C ; =0x000001CE
	mov r1, #0x1
	ldrb r0, [r4, r0]
	add r2, r1, #0x0
	cmp r0, #0x1b
	beq _02015886
	cmp r0, #0x1d
	beq _02015886
	mov r2, #0x0
_02015886:
	cmp r2, #0x0
	bne _02015890
	cmp r0, #0x1c
	beq _02015890
	mov r1, #0x0
_02015890:
	cmp r1, #0x0
	bne _02015898
	bl ErrorHandling
_02015898:
	pop {r4, pc}
	nop
_0201589C: .word 0x000001CE

	thumb_func_start FUN_020158A0
FUN_020158A0: ; 0x020158A0
	ldr r3, _020158A8 ; =FUN_0201598C
	mov r1, #0x0
	bx r3
	nop
_020158A8: .word FUN_0201598C

	thumb_func_start FUN_020158AC
FUN_020158AC: ; 0x020158AC
	ldr r3, _020158B4 ; =FUN_0201598C
	mov r1, #0x1
	bx r3
	nop
_020158B4: .word FUN_0201598C

	thumb_func_start FUN_020158B8
FUN_020158B8: ; 0x020158B8
	ldr r3, _020158C0 ; =FUN_0201598C
	mov r1, #0x2
	bx r3
	nop
_020158C0: .word FUN_0201598C

	thumb_func_start FUN_020158C4
FUN_020158C4: ; 0x020158C4
	ldr r3, _020158CC ; =FUN_0201598C
	mov r1, #0x3
	bx r3
	nop
_020158CC: .word FUN_0201598C

	thumb_func_start FUN_020158D0
FUN_020158D0: ; 0x020158D0
	ldr r3, _020158D8 ; =FUN_0201598C
	mov r1, #0x4
	bx r3
	nop
_020158D8: .word FUN_0201598C

	thumb_func_start FUN_020158DC
FUN_020158DC: ; 0x020158DC
	push {r3, lr}
	cmp r0, #0x18
	bne _020158E8
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	pop {r3, pc}
_020158E8:
	cmp r0, #0x19
	bne _020158F6
	ldr r1, [r1, #0x0]
	ldr r0, [r2, #0x0]
	add r0, r1, r0
	str r0, [r3, #0x0]
	pop {r3, pc}
_020158F6:
	cmp r0, #0x1a
	bne _02015904
	ldr r1, [r3, #0x0]
	ldr r0, [r2, #0x0]
	add r0, r1, r0
	str r0, [r3, #0x0]
	pop {r3, pc}
_02015904:
	bl ErrorHandling
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201590C
FUN_0201590C: ; 0x0201590C
	push {r3, lr}
	sub r0, #0x23
	cmp r0, #0x4
	bhi _02015984
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02015920: ; jump table (using 16-bit offset)
	.short _0201592A - _02015920 - 2; case 0
	.short _0201593C - _02015920 - 2; case 1
	.short _0201594E - _02015920 - 2; case 2
	.short _02015960 - _02015920 - 2; case 3
	.short _02015972 - _02015920 - 2; case 4
_0201592A:
	add r0, r1, #0x0
	add r0, #0x3c
	str r0, [r1, #0x24]
	add r0, r2, #0x0
	add r0, #0x68
	str r0, [r1, #0x28]
	ldr r0, [r2, #0x68]
	str r0, [r1, #0x30]
	pop {r3, pc}
_0201593C:
	add r0, r1, #0x0
	add r0, #0x40
	str r0, [r1, #0x24]
	add r0, r2, #0x0
	add r0, #0x6c
	str r0, [r1, #0x28]
	ldr r0, [r2, #0x6c]
	str r0, [r1, #0x30]
	pop {r3, pc}
_0201594E:
	add r0, r1, #0x0
	add r0, #0x44
	str r0, [r1, #0x24]
	add r0, r2, #0x0
	add r0, #0x70
	str r0, [r1, #0x28]
	ldr r0, [r2, #0x70]
	str r0, [r1, #0x30]
	pop {r3, pc}
_02015960:
	add r0, r1, #0x0
	add r0, #0x48
	str r0, [r1, #0x24]
	add r0, r2, #0x0
	add r0, #0x74
	str r0, [r1, #0x28]
	ldr r0, [r2, #0x74]
	str r0, [r1, #0x30]
	pop {r3, pc}
_02015972:
	add r0, r1, #0x0
	add r0, #0x4c
	str r0, [r1, #0x24]
	add r0, r2, #0x0
	add r0, #0x78
	str r0, [r1, #0x28]
	ldr r0, [r2, #0x78]
	str r0, [r1, #0x30]
	pop {r3, pc}
_02015984:
	bl ErrorHandling
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201598C
FUN_0201598C: ; 0x0201598C
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r1, #0x0
	lsl r1, r6, #0x18
	lsr r1, r1, #0x18
	add r5, r0, #0x0
	bl FUN_02014F34
	str r0, [sp, #0x4]
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	add r1, #0x2c
	bl FUN_02014F94
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	add r1, #0x2d
	bl FUN_02014F94
	mov r0, #0xc
	mul r0, r6
	ldr r1, _02015A28 ; =0x020ED66C
	str r0, [sp, #0x0]
	ldr r0, [r1, r0]
	mov r4, #0x0
	cmp r0, #0x0
	ble _020159E2
	ldr r1, _02015A2C ; =0x020ED668
	ldr r0, [sp, #0x0]
	add r6, r1, r0
	ldr r0, [sp, #0x4]
	add r7, r0, #0x4
_020159CC:
	lsl r1, r4, #0x2
	add r0, r5, #0x0
	add r1, r7, r1
	bl FUN_02014F80
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [r6, #0x4]
	cmp r4, r0
	blt _020159CC
_020159E2:
	ldr r1, _02015A30 ; =0x020ED670
	ldr r0, [sp, #0x0]
	add r2, r5, #0x0
	ldr r0, [r1, r0]
	lsl r1, r0, #0x2
	ldr r0, [sp, #0x4]
	add r0, r0, r1
	ldr r0, [r0, #0x4]
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201590C
	ldr r0, [sp, #0x4]
	add r0, #0x2d
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02015A14
	ldr r0, [sp, #0x4]
	add r1, r5, #0x0
	add r2, r0, #0x0
	ldr r2, [r2, #0x50]
	blx r2
	add sp, #0x8
	pop {r3-r7, pc}
_02015A14:
	ldr r0, [sp, #0x4]
	add r0, #0x2d
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	ldr r0, [sp, #0x4]
	add r0, #0x2d
	str r0, [sp, #0x4]
	strb r1, [r0, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02015A28: .word 0x020ED66C
_02015A2C: .word 0x020ED668
_02015A30: .word 0x020ED670

	thumb_func_start FUN_02015A34
FUN_02015A34: ; 0x02015A34
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x10]
	add r0, r0, #0x1
	ldr r2, [r4, #0x14]
	mul r0, r1
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [r4, #0x4]
	sub r0, #0x1e
	cmp r0, #0x3
	bhi _02015AC0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02015A5C: ; jump table (using 16-bit offset)
	.short _02015A64 - _02015A5C - 2; case 0
	.short _02015A78 - _02015A5C - 2; case 1
	.short _02015A90 - _02015A5C - 2; case 2
	.short _02015AA6 - _02015A5C - 2; case 3
_02015A64:
	asr r0, r1, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02015AE8 ; =0x020FFA38
	ldr r2, [r4, #0xc]
	ldrsh r0, [r0, r1]
	mul r0, r2
	asr r1, r0, #0xc
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015AC4
_02015A78:
	asr r1, r1, #0x4
	lsl r1, r1, #0x1
	add r1, r1, #0x1
	lsl r2, r1, #0x1
	ldr r1, _02015AE8 ; =0x020FFA38
	ldr r0, [r4, #0xc]
	ldrsh r1, [r1, r2]
	mul r1, r0
	ldr r0, [r4, #0x24]
	asr r1, r1, #0xc
	str r1, [r0, #0x0]
	b _02015AC4
_02015A90:
	asr r0, r1, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02015AE8 ; =0x020FFA38
	ldr r2, [r4, #0xc]
	ldrsh r0, [r0, r1]
	mul r0, r2
	asr r0, r0, #0xc
	neg r1, r0
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015AC4
_02015AA6:
	asr r1, r1, #0x4
	lsl r1, r1, #0x1
	add r1, r1, #0x1
	lsl r2, r1, #0x1
	ldr r1, _02015AE8 ; =0x020FFA38
	ldr r0, [r4, #0xc]
	ldrsh r1, [r1, r2]
	mul r1, r0
	asr r0, r1, #0xc
	neg r1, r0
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015AC4
_02015AC0:
	bl ErrorHandling
_02015AC4:
	add r0, r4, #0x0
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	add r1, #0x30
	bl FUN_020158DC
	ldr r0, [r4, #0x1c]
	add r1, r0, #0x1
	str r1, [r4, #0x1c]
	ldr r0, [r4, #0x18]
	cmp r1, r0
	blt _02015AE6
	mov r0, #0x0
	str r0, [r4, #0x0]
_02015AE6:
	pop {r4, pc}
	.balign 4
_02015AE8: .word 0x020FFA38

	thumb_func_start FUN_02015AEC
FUN_02015AEC: ; 0x02015AEC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x10]
	add r0, r0, #0x1
	mul r0, r1
	ldr r1, [r4, #0x18]
	bl _s32_div_f
	ldr r1, [r4, #0x14]
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [r4, #0x4]
	sub r0, #0x1e
	cmp r0, #0x3
	bhi _02015B7E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02015B1A: ; jump table (using 16-bit offset)
	.short _02015B22 - _02015B1A - 2; case 0
	.short _02015B36 - _02015B1A - 2; case 1
	.short _02015B4E - _02015B1A - 2; case 2
	.short _02015B64 - _02015B1A - 2; case 3
_02015B22:
	asr r0, r1, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02015BA8 ; =0x020FFA38
	ldr r2, [r4, #0xc]
	ldrsh r0, [r0, r1]
	mul r0, r2
	asr r1, r0, #0xc
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015B82
_02015B36:
	asr r1, r1, #0x4
	lsl r1, r1, #0x1
	add r1, r1, #0x1
	lsl r2, r1, #0x1
	ldr r1, _02015BA8 ; =0x020FFA38
	ldr r0, [r4, #0xc]
	ldrsh r1, [r1, r2]
	mul r1, r0
	ldr r0, [r4, #0x24]
	asr r1, r1, #0xc
	str r1, [r0, #0x0]
	b _02015B82
_02015B4E:
	asr r0, r1, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02015BA8 ; =0x020FFA38
	ldr r2, [r4, #0xc]
	ldrsh r0, [r0, r1]
	mul r0, r2
	asr r0, r0, #0xc
	neg r1, r0
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015B82
_02015B64:
	asr r1, r1, #0x4
	lsl r1, r1, #0x1
	add r1, r1, #0x1
	lsl r2, r1, #0x1
	ldr r1, _02015BA8 ; =0x020FFA38
	ldr r0, [r4, #0xc]
	ldrsh r1, [r1, r2]
	mul r1, r0
	asr r0, r1, #0xc
	neg r1, r0
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015B82
_02015B7E:
	bl ErrorHandling
_02015B82:
	add r0, r4, #0x0
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	add r1, #0x30
	bl FUN_020158DC
	ldr r0, [r4, #0x1c]
	add r1, r0, #0x1
	str r1, [r4, #0x1c]
	ldr r0, [r4, #0x18]
	cmp r1, r0
	blt _02015BA4
	mov r0, #0x0
	str r0, [r4, #0x0]
_02015BA4:
	pop {r4, pc}
	nop
_02015BA8: .word 0x020FFA38

	thumb_func_start FUN_02015BAC
FUN_02015BAC: ; 0x02015BAC
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x24]
	ldr r3, [r4, #0xc]
	ldr r2, [r4, #0x14]
	ldr r5, [r4, #0x8]
	mul r2, r3
	ldr r0, [r1, #0x0]
	add r2, r5, r2
	add r0, r0, r2
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x2c
	add r1, r4, #0x0
	ldrb r0, [r0, #0x0]
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	add r1, #0x30
	bl FUN_020158DC
	ldr r0, [r4, #0x14]
	add r1, r0, #0x1
	str r1, [r4, #0x14]
	ldr r0, [r4, #0x10]
	cmp r1, r0
	blt _02015BE4
	mov r0, #0x0
	str r0, [r4, #0x0]
_02015BE4:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02015BE8
FUN_02015BE8: ; 0x02015BE8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x10]
	add r1, r0, #0x1
	ldr r0, [r4, #0x8]
	mul r0, r1
	ldr r1, [r4, #0xc]
	bl _s32_div_f
	ldr r1, [r4, #0x24]
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x2c
	add r1, r4, #0x0
	ldrb r0, [r0, #0x0]
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	add r1, #0x30
	bl FUN_020158DC
	ldr r0, [r4, #0x10]
	add r1, r0, #0x1
	str r1, [r4, #0x10]
	ldr r0, [r4, #0xc]
	cmp r1, r0
	blt _02015C20
	mov r0, #0x0
	str r0, [r4, #0x0]
_02015C20:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02015C24
FUN_02015C24: ; 0x02015C24
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x14]
	ldr r2, [r4, #0x8]
	mul r0, r1
	ldr r1, [r4, #0x24]
	add r2, r2, r0
	ldr r0, [r1, #0x0]
	add r0, r0, r2
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x18
	beq _02015C48
	cmp r0, #0x1a
	bne _02015C6E
_02015C48:
	cmp r2, #0x0
	ldr r2, [r4, #0x10]
	bge _02015C5E
	ldr r1, [r4, #0x24]
	ldr r0, [r1, #0x0]
	cmp r0, r2
	bgt _02015CA4
	str r2, [r1, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02015CA4
_02015C5E:
	ldr r1, [r4, #0x24]
	ldr r0, [r1, #0x0]
	cmp r0, r2
	blt _02015CA4
	str r2, [r1, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02015CA4
_02015C6E:
	cmp r0, #0x19
	bne _02015CA0
	ldr r1, [r4, #0x24]
	ldr r3, [r4, #0x30]
	ldr r0, [r1, #0x0]
	add r3, r3, r0
	cmp r2, #0x0
	ldr r2, [r4, #0x10]
	bge _02015C90
	cmp r3, r2
	bgt _02015CA4
	sub r2, r2, r3
	add r0, r0, r2
	str r0, [r1, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02015CA4
_02015C90:
	cmp r3, r2
	blt _02015CA4
	sub r2, r3, r2
	sub r0, r0, r2
	str r0, [r1, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02015CA4
_02015CA0:
	bl ErrorHandling
_02015CA4:
	add r0, r4, #0x0
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	add r1, #0x30
	bl FUN_020158DC
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02015CC0
FUN_02015CC0: ; 0x02015CC0
	ldr r3, _02015CDC ; =0x020ED72C
	mov r2, #0x0
_02015CC4:
	ldrh r1, [r3, #0x2]
	cmp r0, r1
	bhs _02015CCE
	add r0, r2, #0x0
	bx lr
_02015CCE:
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0x2
	blt _02015CC4
	add r0, r2, #0x0
	bx lr
	nop
_02015CDC: .word 0x020ED72C

	thumb_func_start FUN_02015CE0
FUN_02015CE0: ; 0x02015CE0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02015CC0
	lsl r1, r0, #0x1
	ldr r0, _02015CF4 ; =0x020ED72C
	ldrh r0, [r0, r1]
	sub r0, r4, r0
	pop {r4, pc}
	nop
_02015CF4: .word 0x020ED72C

	thumb_func_start FUN_02015CF8
FUN_02015CF8: ; 0x02015CF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x3
	blt _02015D06
	bl ErrorHandling
_02015D06:
	ldr r0, _02015D10 ; =0x020ED72C
	lsl r1, r5, #0x1
	ldrh r0, [r0, r1]
	add r0, r4, r0
	pop {r3-r5, pc}
	.balign 4
_02015D10: .word 0x020ED72C

	thumb_func_start FUN_02015D14
FUN_02015D14: ; 0x02015D14
	cmp r0, #0x7
	bhi _02015D34
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02015D24: ; jump table (using 16-bit offset)
	.short _02015D34 - _02015D24 - 2; case 0
	.short _02015D34 - _02015D24 - 2; case 1
	.short _02015D38 - _02015D24 - 2; case 2
	.short _02015D3E - _02015D24 - 2; case 3
	.short _02015D38 - _02015D24 - 2; case 4
	.short _02015D42 - _02015D24 - 2; case 5
	.short _02015D34 - _02015D24 - 2; case 6
	.short _02015D38 - _02015D24 - 2; case 7
_02015D34:
	mov r0, #0xea
	bx lr
_02015D38:
	mov r0, #0x6d
	lsl r0, r0, #0x2
	bx lr
_02015D3E:
	ldr r0, _02015D48 ; =0x000001B7
	bx lr
_02015D42:
	ldr r0, _02015D4C ; =0x000001B6
	bx lr
	nop
_02015D48: .word 0x000001B7
_02015D4C: .word 0x000001B6

	thumb_func_start FUN_02015D50
FUN_02015D50: ; 0x02015D50
	cmp r0, #0x7
	bhi _02015D70
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02015D60: ; jump table (using 16-bit offset)
	.short _02015D70 - _02015D60 - 2; case 0
	.short _02015D70 - _02015D60 - 2; case 1
	.short _02015D74 - _02015D60 - 2; case 2
	.short _02015D78 - _02015D60 - 2; case 3
	.short _02015D74 - _02015D60 - 2; case 4
	.short _02015D7E - _02015D60 - 2; case 5
	.short _02015D70 - _02015D60 - 2; case 6
	.short _02015D74 - _02015D60 - 2; case 7
_02015D70:
	mov r0, #0xeb
	bx lr
_02015D74:
	ldr r0, _02015D84 ; =0x000001B5
	bx lr
_02015D78:
	mov r0, #0x6e
	lsl r0, r0, #0x2
	bx lr
_02015D7E:
	mov r0, #0x6d
	lsl r0, r0, #0x2
	bx lr
	.balign 4
_02015D84: .word 0x000001B5

	thumb_func_start FUN_02015D88
FUN_02015D88: ; 0x02015D88
	push {r3-r7, lr}
	sub sp, #0x10
	add r6, r3, #0x0
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	str r2, [sp, #0x8]
	cmp r6, #0x1
	beq _02015D9C
	mov r2, #0x1
	b _02015D9E
_02015D9C:
	mov r2, #0x0
_02015D9E:
	ldr r0, [sp, #0x8]
	mov r4, #0x0
	sub r0, r0, #0x1
	str r0, [sp, #0xc]
	beq _02015E18
	ldr r1, _02015E28 ; =0x020ED734
	lsl r0, r2, #0x1
	ldr r5, [sp, #0x4]
	add r7, r1, r0
_02015DB0:
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, r4]
	cmp r0, #0xff
	beq _02015E18
	cmp r0, #0xf7
	blo _02015DEA
	ldr r0, [sp, #0x8]
	sub r3, r0, #0x1
	cmp r3, #0xa
	blo _02015DC6
	mov r3, #0xa
_02015DC6:
	mov r1, #0x0
	cmp r3, #0x0
	ble _02015DDC
	mov r0, #0x6b
	ldr r2, [sp, #0x4]
	lsl r0, r0, #0x2
_02015DD2:
	add r1, r1, #0x1
	strh r0, [r2, #0x0]
	add r2, r2, #0x2
	cmp r1, r3
	blt _02015DD2
_02015DDC:
	ldr r0, [sp, #0x4]
	ldr r2, _02015E2C ; =0x0000FFFF
	lsl r1, r1, #0x1
	strh r2, [r0, r1]
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_02015DEA:
	lsl r0, r0, #0x2
	ldrh r0, [r7, r0]
	cmp r0, #0xea
	beq _02015DF8
	cmp r0, #0xeb
	beq _02015E02
	b _02015E0C
_02015DF8:
	add r0, r6, #0x0
	bl FUN_02015D14
	strh r0, [r5, #0x0]
	b _02015E0E
_02015E02:
	add r0, r6, #0x0
	bl FUN_02015D50
	strh r0, [r5, #0x0]
	b _02015E0E
_02015E0C:
	strh r0, [r5, #0x0]
_02015E0E:
	ldr r0, [sp, #0xc]
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, r0
	blo _02015DB0
_02015E18:
	ldr r2, _02015E2C ; =0x0000FFFF
	ldr r0, [sp, #0x4]
	lsl r1, r4, #0x1
	strh r2, [r0, r1]
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_02015E28: .word 0x020ED734
_02015E2C: .word 0x0000FFFF

	thumb_func_start FUN_02015E30
FUN_02015E30: ; 0x02015E30
	ldr r0, _02015E38 ; =0x021C4898
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_02015E38: .word 0x021C4898

	thumb_func_start FUN_02015E3C
FUN_02015E3C: ; 0x02015E3C
	push {r3, lr}
	ldr r1, _02015E5C ; =0x021C4898
	mov r2, #0x1
	str r2, [r1, #0x0]
	mov r2, #0x0
	str r2, [r1, #0x10]
	str r2, [r1, #0x14]
	str r2, [r1, #0x8]
	str r2, [r1, #0xc]
	str r0, [r1, #0x4]
	bl FUN_02020BF4
	ldr r2, _02015E5C ; =0x021C4898
	str r0, [r2, #0x18]
	str r1, [r2, #0x1c]
	pop {r3, pc}
	.balign 4
_02015E5C: .word 0x021C4898

	thumb_func_start FUN_02015E60
FUN_02015E60: ; 0x02015E60
	push {r3-r5, lr}
	ldr r0, _02015E9C ; =0x021C4898
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02015E9A
	bl FUN_02020BF4
	ldr r2, _02015E9C ; =0x021C4898
	ldr r3, [r2, #0x18]
	ldr r2, [r2, #0x1c]
	sub r0, r0, r3
	sbc r1, r2
	bl FUN_02020C14
	add r5, r1, #0x0
	ldr r1, _02015E9C ; =0x021C4898
	add r4, r0, #0x0
	ldr r3, [r1, #0x8]
	ldr r2, [r1, #0xc]
	sub r0, r3, r4
	sbc r2, r5
	bhs _02015E9A
	ldr r0, [r1, #0x4]
	sub r1, r4, r3
	bl FUN_02029E54
	ldr r0, _02015E9C ; =0x021C4898
	str r4, [r0, #0x8]
	str r5, [r0, #0xc]
_02015E9A:
	pop {r3-r5, pc}
	.balign 4
_02015E9C: .word 0x021C4898

	thumb_func_start FUN_02015EA0
FUN_02015EA0: ; 0x02015EA0
	push {r3, lr}
	ldr r3, _02015EC8 ; =0x027E0000
	ldr r1, _02015ECC ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	mov r0, #0x3
	bl MI_WaitDma
	ldr r0, _02015ED0 ; =0x021C48B8
	ldr r0, [r0, #0x1c]
	bl FUN_0201B5CC
	ldr r0, _02015ED0 ; =0x021C48B8
	ldr r1, [r0, #0x30]
	add r1, r1, #0x1
	str r1, [r0, #0x30]
	pop {r3, pc}
	nop
_02015EC8: .word 0x027E0000
_02015ECC: .word 0x00003FF8
_02015ED0: .word 0x021C48B8

	thumb_func_start FUN_02015ED4
FUN_02015ED4: ; 0x02015ED4
	ldr r3, _02015EE8 ; =0x027E0000
	ldr r1, _02015EEC ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	ldr r3, _02015EF0 ; =MI_WaitDma
	mov r0, #0x3
	bx r3
	nop
_02015EE8: .word 0x027E0000
_02015EEC: .word 0x00003FF8
_02015EF0: .word MI_WaitDma

	thumb_func_start FUN_02015EF4
FUN_02015EF4: ; 0x02015EF4
	push {r3, lr}
	mov r0, #0x1
	bl OS_DisableIrqMask
	ldr r1, _02015F0C ; =FUN_02015ED4
	mov r0, #0x1
	bl OS_SetIrqFunction
	mov r0, #0x1
	bl OS_EnableIrqMask
	pop {r3, pc}
	.balign 4
_02015F0C: .word FUN_02015ED4

	thumb_func_start FUN_02015F10
FUN_02015F10: ; 0x02015F10
	ldr r2, _02015F18 ; =0x021C48B8
	str r0, [r2, #0x0]
	str r1, [r2, #0x4]
	bx lr
	.balign 4
_02015F18: .word 0x021C48B8

	thumb_func_start FUN_02015F1C
FUN_02015F1C: ; 0x02015F1C
	push {r3, lr}
	mov r0, #0x0
	bl FUN_02015F80
	ldr r0, _02015F30 ; =0x021C48B8
	mov r1, #0x0
	str r1, [r0, #0x8]
	str r1, [r0, #0xc]
	pop {r3, pc}
	nop
_02015F30: .word 0x021C48B8

	thumb_func_start FUN_02015F34
FUN_02015F34: ; 0x02015F34
	push {r3, lr}
	cmp r0, #0x0
	bne _02015F4C
	mov r0, #0x0
	bl FUN_02015F80
	ldr r0, _02015F68 ; =0x021C48B8
	mov r1, #0x0
	str r1, [r0, #0x8]
	str r1, [r0, #0xc]
	mov r0, #0x1
	pop {r3, pc}
_02015F4C:
	ldr r2, _02015F68 ; =0x021C48B8
	ldr r3, [r2, #0x8]
	cmp r3, #0x0
	bne _02015F62
	str r1, [r2, #0xc]
	str r0, [r2, #0x8]
	mov r0, #0x1
	bl FUN_02015F80
	mov r0, #0x1
	pop {r3, pc}
_02015F62:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02015F68: .word 0x021C48B8

	thumb_func_start FUN_02015F6C
FUN_02015F6C: ; 0x02015F6C
	push {r3, lr}
	ldr r0, _02015F7C ; =0x021C48B8
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	beq _02015F7A
	ldr r0, [r0, #0xc]
	blx r1
_02015F7A:
	pop {r3, pc}
	.balign 4
_02015F7C: .word 0x021C48B8

	thumb_func_start FUN_02015F80
FUN_02015F80: ; 0x02015F80
	push {r3, lr}
	ldr r2, _02015FC0 ; =0x04000208
	ldrh r1, [r2, #0x0]
	mov r1, #0x0
	strh r1, [r2, #0x0]
	cmp r0, #0x0
	bne _02015F9E
	ldr r0, [r2, #0x8]
	mov r0, #0x2
	bl OS_DisableIrqMask
	mov r0, #0x0
	bl GX_HBlankIntr
	b _02015FB4
_02015F9E:
	ldr r0, [r2, #0x8]
	ldr r1, _02015FC4 ; =FUN_02015F6C
	mov r0, #0x2
	bl OS_SetIrqFunction
	mov r0, #0x2
	bl OS_EnableIrqMask
	mov r0, #0x1
	bl GX_HBlankIntr
_02015FB4:
	ldr r1, _02015FC0 ; =0x04000208
	ldrh r0, [r1, #0x0]
	mov r0, #0x1
	strh r0, [r1, #0x0]
	pop {r3, pc}
	nop
_02015FC0: .word 0x04000208
_02015FC4: .word FUN_02015F6C

	thumb_func_start FUN_02015FC8
FUN_02015FC8: ; 0x02015FC8
	push {r3, lr}
	sub sp, #0x30
	add r0, sp, #0x10
	bl OS_GetLowEntropyData
	add r0, sp, #0x0
	add r1, sp, #0x10
	mov r2, #0x20
	bl MATH_CalcMD5
	mov r3, #0x0
	add r1, r3, #0x0
	add r2, sp, #0x0
_02015FE2:
	ldrb r0, [r2, #0x0]
	add r1, r1, #0x1
	add r2, r2, #0x1
	add r3, r3, r0
	cmp r1, #0x10
	blo _02015FE2
	lsl r0, r3, #0x18
	lsr r3, r0, #0x18
	mov r0, #0x3
	tst r0, r3
	beq _02016002
	mov r0, #0x3
_02015FFA:
	add r3, r3, #0x1
	add r1, r3, #0x0
	tst r1, r0
	bne _02015FFA
_02016002:
	ldr r0, _02016010 ; =0x020EDB10
	mov r1, #0x4
	mov r2, #0x5c
	bl FUN_020166C8
	add sp, #0x30
	pop {r3, pc}
	.balign 4
_02016010: .word 0x020EDB10

	thumb_func_start InitSystemForTheGame
InitSystemForTheGame: ; 0x02016014
	push {r3-r5, lr}
	bl OS_Init
	bl FX_Init
	ldr r2, _02016124 ; =0x04000304
	ldr r0, _02016128 ; =0xFFFFFDF1
	ldrh r1, [r2, #0x0]
	and r1, r0
	ldr r0, _0201612C ; =0x0000020E
	orr r0, r1
	strh r0, [r2, #0x0]
	bl GX_Init
	bl OS_InitTick
	bl FUN_02015FC8
	mov r0, #0xa0
	bl FUN_0201B578
	add r1, r0, #0x0
	mov r0, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	add r1, r0, #0x0
	mov r0, #0xa0
	bl FUN_0201B580
	ldr r1, _02016130 ; =0x021C48B8
	str r0, [r1, #0x18]
	mov r0, #0x10
	bl FUN_0201B578
	add r1, r0, #0x0
	mov r0, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	add r1, r0, #0x0
	mov r0, #0x10
	bl FUN_0201B580
	ldr r1, _02016130 ; =0x021C48B8
	str r0, [r1, #0x1c]
	mov r0, #0x20
	bl FUN_0201B578
	add r1, r0, #0x0
	mov r0, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	add r1, r0, #0x0
	mov r0, #0x20
	bl FUN_0201B580
	ldr r1, _02016130 ; =0x021C48B8
	str r0, [r1, #0x20]
	mov r0, #0x4
	bl FUN_0201B578
	add r1, r0, #0x0
	mov r0, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	add r1, r0, #0x0
	mov r0, #0x4
	bl FUN_0201B580
	ldr r1, _02016130 ; =0x021C48B8
	str r0, [r1, #0x24]
	bl GX_DispOff
	ldr r2, _02016134 ; =0x04001000
	ldr r0, _02016138 ; =0xFFFEFFFF
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	ldr r2, _02016124 ; =0x04000304
	ldrh r1, [r2, #0x0]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2, #0x0]
	ldr r1, _0201613C ; =FUN_02015EA0
	mov r0, #0x1
	bl OS_SetIrqFunction
	mov r0, #0x1
	bl OS_EnableIrqMask
	mov r0, #0x1
	lsl r0, r0, #0x12
	bl OS_EnableIrqMask
	ldr r1, _02016140 ; =0x04000208
	ldrh r0, [r1, #0x0]
	mov r0, #0x1
	strh r0, [r1, #0x0]
	bl GX_VBlankIntr
	mov r0, #0x1
	bl FS_Init
	bl FUN_02022450
	mov r0, #0x0
	add r1, r0, #0x0
	bl FS_TryLoadTable
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	add r5, r0, #0x0
	bne _02016108
	bl ErrorHandling
_02016108:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FS_TryLoadTable
	ldr r0, _02016130 ; =0x021C48B8
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x8]
	str r1, [r0, #0x10]
	str r1, [r0, #0x14]
	str r1, [r0, #0x2c]
	ldr r0, _02016144 ; =0x021C4918
	strb r1, [r0, #0x5]
	pop {r3-r5, pc}
	.balign 4
_02016124: .word 0x04000304
_02016128: .word 0xFFFFFDF1
_0201612C: .word 0x0000020E
_02016130: .word 0x021C48B8
_02016134: .word 0x04001000
_02016138: .word 0xFFFEFFFF
_0201613C: .word FUN_02015EA0
_02016140: .word 0x04000208
_02016144: .word 0x021C4918

	thumb_func_start InitGraphicMemory
InitGraphicMemory: ; 0x02016148
	push {r3, lr}
	ldr r0, _02016198 ; =0x000001FF
	bl GX_SetBankForLCDC
	mov r1, #0x1a
	mov r2, #0x29
	mov r0, #0x0
	lsl r1, r1, #0x16
	lsl r2, r2, #0xe
	bl MIi_CpuClearFast
	bl GX_DisableBankForLCDC
	mov r1, #0x7
	mov r2, #0x1
	mov r0, #0xc0
	lsl r1, r1, #0x18
	lsl r2, r2, #0xa
	bl MIi_CpuClearFast
	mov r2, #0x1
	ldr r1, _0201619C ; =0x07000400
	mov r0, #0xc0
	lsl r2, r2, #0xa
	bl MIi_CpuClearFast
	mov r1, #0x5
	mov r2, #0x1
	mov r0, #0x0
	lsl r1, r1, #0x18
	lsl r2, r2, #0xa
	bl MIi_CpuClearFast
	mov r2, #0x1
	ldr r1, _020161A0 ; =0x05000400
	mov r0, #0x0
	lsl r2, r2, #0xa
	bl MIi_CpuClearFast
	pop {r3, pc}
	.balign 4
_02016198: .word 0x000001FF
_0201619C: .word 0x07000400
_020161A0: .word 0x05000400

	thumb_func_start FUN_020161A4
FUN_020161A4: ; 0x020161A4
	push {r4-r6, lr}
	sub sp, #0x48
	add r6, r0, #0x0
	add r4, r1, #0x0
	add r0, sp, #0x0
	bl FS_InitFile
	add r0, sp, #0x0
	add r1, r4, #0x0
	bl FS_OpenFile
	cmp r0, #0x0
	beq _020161F0
	ldr r1, [sp, #0x28]
	ldr r0, [sp, #0x24]
	sub r5, r1, r0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	beq _020161E8
	add r0, sp, #0x0
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FS_ReadFile
	cmp r5, r0
	beq _020161E8
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02016A8C
	mov r4, #0x0
_020161E8:
	add r0, sp, #0x0
	bl FS_CloseFile
	b _020161F2
_020161F0:
	mov r4, #0x0
_020161F2:
	add r0, r4, #0x0
	add sp, #0x48
	pop {r4-r6, pc}

	thumb_func_start FUN_020161F8
FUN_020161F8: ; 0x020161F8
	push {r3-r5, lr}
	sub sp, #0x48
	add r5, r0, #0x0
	add r0, sp, #0x0
	add r4, r1, #0x0
	bl FS_InitFile
	add r0, sp, #0x0
	add r1, r5, #0x0
	bl FS_OpenFile
	cmp r0, #0x0
	beq _0201622A
	ldr r1, [sp, #0x28]
	ldr r0, [sp, #0x24]
	sub r2, r1, r0
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02016224
	add r0, sp, #0x0
	bl FS_ReadFile
_02016224:
	add r0, sp, #0x0
	bl FS_CloseFile
_0201622A:
	add sp, #0x48
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02016230
FUN_02016230: ; 0x02016230
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	bl strlen
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	lsr r2, r3, #0x1f
	lsl r1, r3, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	beq _02016258
	lsr r0, r3, #0x2
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	b _0201625E
_02016258:
	lsl r0, r3, #0xe
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
_0201625E:
	ldr r0, [sp, #0x4]
	mov r7, #0x0
	mov r12, r7
	cmp r0, #0x0
	ble _0201629A
	add r6, r7, #0x0
	add r4, r7, #0x0
_0201626C:
	ldr r2, [sp, #0x0]
	mov r1, #0x0
	add r0, r1, #0x0
	add r2, r2, r6
	add r3, r1, #0x0
_02016276:
	ldrsb r5, [r2, r4]
	cmp r5, #0x0
	beq _0201628A
	lsl r5, r3
	add r0, r0, #0x1
	orr r1, r5
	add r2, r2, #0x1
	add r3, #0x8
	cmp r0, #0x4
	blt _02016276
_0201628A:
	mov r0, r12
	eor r7, r1
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	add r6, r6, #0x4
	mov r12, r1
	cmp r1, r0
	blt _0201626C
_0201629A:
	add r0, r7, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_020162A0
FUN_020162A0: ; 0x020162A0
	ldr r3, _020162C4 ; =0x021C4928
	mov r2, #0x0
_020162A4:
	ldr r1, [r3, #0x4]
	cmp r0, r1
	bne _020162B4
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _020162B4
	add r0, r2, #0x0
	bx lr
_020162B4:
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, #0x80
	blt _020162A4
	mov r0, #0x0
	mvn r0, r0
	bx lr
	nop
_020162C4: .word 0x021C4928

	thumb_func_start FUN_020162C8
FUN_020162C8: ; 0x020162C8
	push {r3-r4}
	ldr r3, _020162F4 ; =0x021C4928
	mov r4, #0x0
_020162CE:
	ldr r2, [r3, #0x0]
	cmp r2, #0x0
	bne _020162E4
	ldr r2, _020162F4 ; =0x021C4928
	lsl r3, r4, #0x3
	str r0, [r2, r3]
	ldr r0, _020162F8 ; =0x021C492C
	str r1, [r0, r3]
	add r0, r4, #0x0
	pop {r3-r4}
	bx lr
_020162E4:
	add r4, r4, #0x1
	add r3, #0x8
	cmp r4, #0x80
	blt _020162CE
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r4}
	bx lr
	.balign 4
_020162F4: .word 0x021C4928
_020162F8: .word 0x021C492C

	thumb_func_start FUN_020162FC
FUN_020162FC: ; 0x020162FC
	push {r3-r7, lr}
	mov r6, #0x0
	ldr r5, _02016320 ; =0x021C4D20
	mov r4, #0x7f
	sub r7, r6, #0x1
_02016306:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02016314
	bl FUN_02016A18
	str r6, [r5, #0x0]
	str r6, [r5, #0x4]
_02016314:
	sub r4, r4, #0x1
	sub r5, #0x8
	cmp r4, r7
	bgt _02016306
	pop {r3-r7, pc}
	nop
_02016320: .word 0x021C4D20

	thumb_func_start FUN_02016324
FUN_02016324: ; 0x02016324
	push {r3-r7, lr}
	sub sp, #0x68
	add r2, r0, #0x0
	mov r5, #0x0
	ldrsb r0, [r2, r5]
	add r4, r1, #0x0
	cmp r0, #0x21
	add r0, sp, #0x0
	bne _02016340
	add r1, r2, #0x1
	bl strcpy
	mov r5, #0x1
	b _02016346
_02016340:
	add r1, r2, #0x0
	bl strcpy
_02016346:
	add r0, sp, #0x0
	bl FUN_02016230
	add r7, r0, #0x0
	bl FUN_020162A0
	cmp r0, #0x0
	blt _02016362
	cmp r5, #0x0
	bne _02016362
	lsl r1, r0, #0x3
	ldr r0, _020163B8 ; =0x021C4928
	ldr r4, [r0, r1]
	b _020163B2
_02016362:
	add r0, sp, #0x20
	bl FS_InitFile
	add r0, sp, #0x20
	add r1, sp, #0x0
	bl FS_OpenFile
	cmp r0, #0x0
	beq _020163B0
	ldr r1, [sp, #0x48]
	ldr r0, [sp, #0x44]
	sub r6, r1, r0
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	beq _0201639C
	add r0, sp, #0x20
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FS_ReadFile
	cmp r6, r0
	beq _0201639C
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r4, #0x0
_0201639C:
	add r0, sp, #0x20
	bl FS_CloseFile
	cmp r5, #0x0
	bne _020163B2
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_020162C8
	b _020163B2
_020163B0:
	mov r4, #0x0
_020163B2:
	add r0, r4, #0x0
	add sp, #0x68
	pop {r3-r7, pc}
	.balign 4
_020163B8: .word 0x021C4928

	thumb_func_start FUN_020163BC
FUN_020163BC: ; 0x020163BC
	push {r3, lr}
	sub sp, #0x8
	ldr r0, _0201641C ; =0x021C48B8
	mov r2, #0x0
	str r2, [r0, #0x34]
	str r2, [r0, #0x38]
	str r2, [r0, #0x3c]
	str r2, [r0, #0x40]
	str r2, [r0, #0x44]
	str r2, [r0, #0x48]
	str r2, [r0, #0x4c]
	str r2, [r0, #0x50]
	mov r1, #0x8
	str r1, [r0, #0x54]
	mov r1, #0xf
	str r1, [r0, #0x58]
	ldr r0, _02016420 ; =0x021C48F8
	strh r2, [r0, #0x1c]
	strh r2, [r0, #0x1e]
	strh r2, [r0, #0x20]
	strh r2, [r0, #0x22]
	ldr r0, _02016424 ; =0x021C4918
	strb r2, [r0, #0x4]
	bl TP_Init
	add r0, sp, #0x0
	bl TP_GetUserInfo
	cmp r0, #0x1
	add r0, sp, #0x0
	bne _02016402
	bl TP_SetCalibrateParam
	add sp, #0x8
	pop {r3, pc}
_02016402:
	ldr r1, _02016428 ; =0x000002AE
	strh r1, [r0, #0x0]
	ldr r1, _0201642C ; =0x0000058C
	strh r1, [r0, #0x2]
	ldr r1, _02016430 ; =0x00000E25
	strh r1, [r0, #0x4]
	ldr r1, _02016434 ; =0x00001208
	strh r1, [r0, #0x6]
	add r0, sp, #0x0
	bl TP_SetCalibrateParam
	add sp, #0x8
	pop {r3, pc}
	.balign 4
_0201641C: .word 0x021C48B8
_02016420: .word 0x021C48F8
_02016424: .word 0x021C4918
_02016428: .word 0x000002AE
_0201642C: .word 0x0000058C
_02016430: .word 0x00000E25
_02016434: .word 0x00001208

	thumb_func_start FUN_02016438
FUN_02016438: ; 0x02016438
	ldr r1, _02016440 ; =0x021C4918
	strb r0, [r1, #0x6]
	bx lr
	nop
_02016440: .word 0x021C4918

	thumb_func_start FUN_02016444
FUN_02016444: ; 0x02016444
	ldr r1, _02016450 ; =0x021C4918
	ldrb r2, [r1, #0x7]
	orr r0, r2
	strb r0, [r1, #0x7]
	bx lr
	nop
_02016450: .word 0x021C4918

	thumb_func_start FUN_02016454
FUN_02016454: ; 0x02016454
	ldr r1, _02016460 ; =0x021C4918
	mvn r0, r0
	ldrb r2, [r1, #0x7]
	and r0, r2
	strb r0, [r1, #0x7]
	bx lr
	.balign 4
_02016460: .word 0x021C4918

	thumb_func_start FUN_02016464
FUN_02016464: ; 0x02016464
	push {r4, lr}
	sub sp, #0x10
	ldr r2, _02016550 ; =0x027FFFA8
	mov r0, #0x2
	ldrh r1, [r2, #0x0]
	lsl r0, r0, #0xe
	and r0, r1
	asr r0, r0, #0xf
	beq _0201648A
	ldr r0, _02016554 ; =0x021C48B8
	mov r1, #0x0
	str r1, [r0, #0x48]
	str r1, [r0, #0x44]
	str r1, [r0, #0x4c]
	ldr r0, _02016558 ; =0x021C48F8
	add sp, #0x10
	strh r1, [r0, #0x20]
	strh r1, [r0, #0x22]
	pop {r4, pc}
_0201648A:
	ldr r0, _0201655C ; =0x04000130
	ldrh r1, [r0, #0x0]
	ldrh r0, [r2, #0x0]
	orr r1, r0
	ldr r0, _02016560 ; =0x00002FFF
	eor r1, r0
	and r0, r1
	ldr r1, _02016554 ; =0x021C48B8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	ldr r2, [r1, #0x38]
	add r3, r0, #0x0
	eor r3, r2
	and r3, r0
	str r3, [r1, #0x3c]
	str r3, [r1, #0x40]
	cmp r0, #0x0
	beq _020164C2
	cmp r2, r0
	bne _020164C2
	ldr r2, [r1, #0x50]
	sub r2, r2, #0x1
	str r2, [r1, #0x50]
	bne _020164C8
	str r0, [r1, #0x40]
	ldr r2, [r1, #0x54]
	str r2, [r1, #0x50]
	b _020164C8
_020164C2:
	ldr r1, _02016554 ; =0x021C48B8
	ldr r2, [r1, #0x58]
	str r2, [r1, #0x50]
_020164C8:
	ldr r1, _02016554 ; =0x021C48B8
	str r0, [r1, #0x38]
	ldr r2, [r1, #0x3c]
	str r2, [r1, #0x48]
	str r0, [r1, #0x44]
	ldr r0, [r1, #0x40]
	str r0, [r1, #0x4c]
	bl FUN_02016568
	ldr r0, _02016564 ; =0x021C4918
	ldrb r0, [r0, #0x4]
	cmp r0, #0x0
	bne _020164F4
	add r4, sp, #0x8
_020164E4:
	bl TP_RequestSamplingAsync
	add r0, r4, #0x0
	bl TP_WaitRawResult
	cmp r0, #0x0
	bne _020164E4
	b _020164FA
_020164F4:
	add r0, sp, #0x8
	bl TP_GetLatestRawPointInAuto
_020164FA:
	add r0, sp, #0x0
	add r1, sp, #0x8
	bl TP_GetCalibratedPoint
	add r1, sp, #0x0
	ldrh r3, [r1, #0x6]
	cmp r3, #0x0
	bne _02016516
	ldrh r2, [r1, #0x0]
	ldr r0, _02016558 ; =0x021C48F8
	strh r2, [r0, #0x1c]
	ldrh r1, [r1, #0x2]
	strh r1, [r0, #0x1e]
	b _0201653A
_02016516:
	ldr r0, _02016558 ; =0x021C48F8
	ldrh r2, [r0, #0x22]
	cmp r2, #0x0
	beq _02016536
	cmp r3, #0x1
	beq _0201652A
	cmp r3, #0x2
	beq _02016530
	cmp r3, #0x3
	b _0201653A
_0201652A:
	ldrh r1, [r1, #0x2]
	strh r1, [r0, #0x1e]
	b _0201653A
_02016530:
	ldrh r1, [r1, #0x0]
	strh r1, [r0, #0x1c]
	b _0201653A
_02016536:
	mov r0, #0x0
	strh r0, [r1, #0x4]
_0201653A:
	add r0, sp, #0x0
	ldrh r2, [r0, #0x4]
	ldr r0, _02016558 ; =0x021C48F8
	ldrh r1, [r0, #0x22]
	eor r1, r2
	and r1, r2
	strh r1, [r0, #0x20]
	strh r2, [r0, #0x22]
	add sp, #0x10
	pop {r4, pc}
	nop
_02016550: .word 0x027FFFA8
_02016554: .word 0x021C48B8
_02016558: .word 0x021C48F8
_0201655C: .word 0x04000130
_02016560: .word 0x00002FFF
_02016564: .word 0x021C4918

	thumb_func_start FUN_02016568
FUN_02016568: ; 0x02016568
	ldr r0, _02016690 ; =0x021C48B8
	ldr r1, [r0, #0x34]
	cmp r1, #0x3
	bls _02016572
	b _0201668C
_02016572:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0201657E: ; jump table (using 16-bit offset)
	.short _0201668C - _0201657E - 2; case 0
	.short _02016586 - _0201657E - 2; case 1
	.short _020165BC - _0201657E - 2; case 2
	.short _02016642 - _0201657E - 2; case 3
_02016586:
	ldr r2, [r0, #0x48]
	mov r1, #0x8
	add r3, r2, #0x0
	tst r3, r1
	beq _02016596
	lsl r1, r1, #0x7
	orr r1, r2
	str r1, [r0, #0x48]
_02016596:
	ldr r1, _02016690 ; =0x021C48B8
	mov r0, #0x8
	ldr r2, [r1, #0x44]
	add r3, r2, #0x0
	tst r3, r0
	beq _020165A8
	lsl r0, r0, #0x7
	orr r0, r2
	str r0, [r1, #0x44]
_020165A8:
	ldr r1, _02016690 ; =0x021C48B8
	mov r0, #0x8
	ldr r2, [r1, #0x4c]
	add r3, r2, #0x0
	tst r3, r0
	beq _0201668C
	lsl r0, r0, #0x7
	orr r0, r2
	str r0, [r1, #0x4c]
	bx lr
_020165BC:
	ldr r3, [r0, #0x48]
	mov r0, #0x1
	lsl r0, r0, #0xa
	add r2, r3, #0x0
	mov r1, #0x0
	tst r2, r0
	beq _020165CE
	lsl r0, r0, #0x1
	orr r1, r0
_020165CE:
	mov r0, #0x2
	lsl r0, r0, #0xa
	add r2, r3, #0x0
	tst r2, r0
	beq _020165DC
	lsr r0, r0, #0x1
	orr r1, r0
_020165DC:
	ldr r2, _02016690 ; =0x021C48B8
	ldr r0, _02016694 ; =0x0000F3FF
	ldr r3, [r2, #0x48]
	and r0, r3
	orr r0, r1
	str r0, [r2, #0x48]
	ldr r3, [r2, #0x44]
	mov r1, #0x1
	lsl r1, r1, #0xa
	add r2, r3, #0x0
	mov r0, #0x0
	tst r2, r1
	beq _020165FA
	lsl r1, r1, #0x1
	orr r0, r1
_020165FA:
	mov r1, #0x2
	lsl r1, r1, #0xa
	add r2, r3, #0x0
	tst r2, r1
	beq _02016608
	lsr r1, r1, #0x1
	orr r0, r1
_02016608:
	ldr r2, _02016690 ; =0x021C48B8
	ldr r1, _02016694 ; =0x0000F3FF
	ldr r3, [r2, #0x44]
	and r1, r3
	orr r0, r1
	str r0, [r2, #0x44]
	ldr r3, [r2, #0x4c]
	mov r1, #0x1
	lsl r1, r1, #0xa
	add r2, r3, #0x0
	mov r0, #0x0
	tst r2, r1
	beq _02016626
	lsl r1, r1, #0x1
	orr r0, r1
_02016626:
	mov r1, #0x2
	lsl r1, r1, #0xa
	add r2, r3, #0x0
	tst r2, r1
	beq _02016634
	lsr r1, r1, #0x1
	orr r0, r1
_02016634:
	ldr r2, _02016690 ; =0x021C48B8
	ldr r1, _02016694 ; =0x0000F3FF
	ldr r3, [r2, #0x4c]
	and r1, r3
	orr r0, r1
	str r0, [r2, #0x4c]
	bx lr
_02016642:
	mov r1, #0x2
	ldr r2, [r0, #0x48]
	lsl r1, r1, #0x8
	tst r1, r2
	beq _02016652
	mov r1, #0x1
	orr r1, r2
	str r1, [r0, #0x48]
_02016652:
	ldr r1, _02016690 ; =0x021C48B8
	mov r0, #0x2
	ldr r2, [r1, #0x44]
	lsl r0, r0, #0x8
	tst r0, r2
	beq _02016664
	mov r0, #0x1
	orr r0, r2
	str r0, [r1, #0x44]
_02016664:
	ldr r1, _02016690 ; =0x021C48B8
	mov r0, #0x2
	ldr r2, [r1, #0x4c]
	lsl r0, r0, #0x8
	tst r0, r2
	beq _02016676
	mov r0, #0x1
	orr r0, r2
	str r0, [r1, #0x4c]
_02016676:
	ldr r1, _02016690 ; =0x021C48B8
	ldr r0, _02016698 ; =0x0000FCFF
	ldr r2, [r1, #0x48]
	and r2, r0
	str r2, [r1, #0x48]
	ldr r2, [r1, #0x44]
	and r2, r0
	str r2, [r1, #0x44]
	ldr r2, [r1, #0x4c]
	and r0, r2
	str r0, [r1, #0x4c]
_0201668C:
	bx lr
	nop
_02016690: .word 0x021C48B8
_02016694: .word 0x0000F3FF
_02016698: .word 0x0000FCFF

	thumb_func_start FUN_0201669C
FUN_0201669C: ; 0x0201669C
	ldr r2, _020166A4 ; =0x021C48B8
	str r0, [r2, #0x54]
	str r1, [r2, #0x58]
	bx lr
	.balign 4
_020166A4: .word 0x021C48B8

	thumb_func_start FUN_020166A8
FUN_020166A8: ; 0x020166A8
	ldr r1, _020166B4 ; =0x021C4918
	ldrb r2, [r1, #0x8]
	orr r0, r2
	strb r0, [r1, #0x8]
	bx lr
	nop
_020166B4: .word 0x021C4918

	thumb_func_start FUN_020166B8
FUN_020166B8: ; 0x020166B8
	ldr r1, _020166C4 ; =0x021C4918
	mvn r0, r0
	ldrb r2, [r1, #0x8]
	and r0, r2
	strb r0, [r1, #0x8]
	bx lr
	.balign 4
_020166C4: .word 0x021C4918

	thumb_func_start FUN_020166C8
FUN_020166C8: ; 0x020166C8
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	str r0, [sp, #0x4]
	add r0, #0x18
	add r6, r2, #0x0
	str r0, [sp, #0x4]
	cmp r6, r0
	bhs _020166E0
	add r6, r0, #0x0
_020166E0:
	cmp r3, #0x0
	beq _020166FE
	mov r0, #0x3
	tst r0, r3
	beq _020166F4
	mov r0, #0x3
_020166EC:
	add r3, r3, #0x1
	add r1, r3, #0x0
	tst r1, r0
	bne _020166EC
_020166F4:
	mov r0, #0x0
	add r1, r3, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
_020166FE:
	ldr r1, [sp, #0x4]
	lsl r7, r6, #0x1
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r1, #0x1
	lsl r1, r1, #0x2
	add r1, r7, r1
	mov r0, #0x0
	add r1, r6, r1
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	ldr r1, _020167F0 ; =0x021C4D28
	str r0, [r1, #0x0]
	ldr r1, [sp, #0x4]
	add r1, r1, #0x1
	lsl r1, r1, #0x2
	add r1, r0, r1
	ldr r0, _020167F0 ; =0x021C4D28
	str r1, [r0, #0x4]
	ldr r0, [sp, #0x4]
	lsl r0, r0, #0x2
	add r2, r1, r0
	ldr r1, _020167F0 ; =0x021C4D28
	str r2, [r1, #0x8]
	add r1, r2, r0
	ldr r0, _020167F0 ; =0x021C4D28
	str r1, [r0, #0xc]
	add r1, r1, r7
	str r1, [r0, #0x10]
	strh r6, [r0, #0x14]
	strh r4, [r0, #0x16]
	ldr r0, [sp, #0x4]
	mov r7, #0x0
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, _020167F0 ; =0x021C4D28
	cmp r4, #0x0
	strh r1, [r0, #0x1a]
	strh r1, [r0, #0x18]
	bls _020167A0
	str r7, [sp, #0x0]
_02016752:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _0201675C
	cmp r0, #0x2
	beq _02016768
_0201675C:
	ldr r1, [r5, #0x0]
	mov r0, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	b _02016772
_02016768:
	ldr r1, [r5, #0x0]
	mov r0, #0x2
	mov r2, #0x4
	bl OS_AllocFromArenaHi
_02016772:
	cmp r0, #0x0
	beq _0201678E
	ldr r1, [r5, #0x0]
	mov r2, #0x0
	bl tempName_NNS_FndCreateExpHeapEx
	ldr r1, _020167F0 ; =0x021C4D28
	ldr r2, [r1, #0x0]
	ldr r1, [sp, #0x0]
	str r0, [r2, r1]
	ldr r0, _020167F0 ; =0x021C4D28
	ldr r0, [r0, #0x10]
	strb r7, [r0, r7]
	b _02016792
_0201678E:
	bl ErrorHandling
_02016792:
	ldr r0, [sp, #0x0]
	add r7, r7, #0x1
	add r0, r0, #0x4
	add r5, #0x8
	str r0, [sp, #0x0]
	cmp r7, r4
	blo _02016752
_020167A0:
	ldr r0, [sp, #0x4]
	add r1, r0, #0x1
	cmp r4, r1
	bhs _020167C0
	ldr r3, _020167F0 ; =0x021C4D28
	lsl r2, r4, #0x2
	mov r0, #0x0
_020167AE:
	ldr r5, [r3, #0x0]
	str r0, [r5, r2]
	ldrh r7, [r3, #0x1a]
	ldr r5, [r3, #0x10]
	add r2, r2, #0x4
	strb r7, [r5, r4]
	add r4, r4, #0x1
	cmp r4, r1
	blo _020167AE
_020167C0:
	cmp r4, r6
	bhs _020167D2
	ldr r0, _020167F0 ; =0x021C4D28
_020167C6:
	ldrh r2, [r0, #0x1a]
	ldr r1, [r0, #0x10]
	strb r2, [r1, r4]
	add r4, r4, #0x1
	cmp r4, r6
	blo _020167C6
_020167D2:
	mov r4, #0x0
	cmp r6, #0x0
	bls _020167EA
	ldr r0, _020167F0 ; =0x021C4D28
	add r3, r4, #0x0
	add r2, r4, #0x0
_020167DE:
	ldr r1, [r0, #0xc]
	add r4, r4, #0x1
	strh r2, [r1, r3]
	add r3, r3, #0x2
	cmp r4, r6
	blo _020167DE
_020167EA:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_020167F0: .word 0x021C4D28

	thumb_func_start FUN_020167F4
FUN_020167F4: ; 0x020167F4
	ldr r1, _02016818 ; =0x021C4D28
	ldrh r0, [r1, #0x16]
	ldrh r3, [r1, #0x18]
	cmp r0, r3
	bge _02016812
	ldr r2, [r1, #0x0]
	lsl r1, r0, #0x2
	add r2, r2, r1
_02016804:
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	beq _02016816
	add r0, r0, #0x1
	add r2, r2, #0x4
	cmp r0, r3
	blt _02016804
_02016812:
	mov r0, #0x0
	mvn r0, r0
_02016816:
	bx lr
	.balign 4
_02016818: .word 0x021C4D28

	thumb_func_start FUN_0201681C
FUN_0201681C: ; 0x0201681C
	push {r3, lr}
	mov r3, #0x4
	bl FUN_02016834
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02016828
FUN_02016828: ; 0x02016828
	push {r3, lr}
	mov r3, #0x3
	mvn r3, r3
	bl FUN_02016834
	pop {r3, pc}

	thumb_func_start FUN_02016834
FUN_02016834: ; 0x02016834
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r5, r1, #0x0
	str r2, [sp, #0x0]
	add r7, r3, #0x0
	bl OS_GetProcMode
	cmp r0, #0x12
	bne _0201684C
	bl ErrorHandling
_0201684C:
	ldr r1, _020168CC ; =0x021C4D28
	ldr r0, [r1, #0x10]
	ldrh r3, [r1, #0x1a]
	ldrb r2, [r0, r5]
	cmp r3, r2
	bne _020168C2
	ldrb r0, [r0, r4]
	ldr r1, [r1, #0x0]
	lsl r0, r0, #0x2
	ldr r6, [r1, r0]
	cmp r6, #0x0
	beq _020168BC
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	add r2, r7, #0x0
	bl tempName_NNS_FndAllocFromExpHeapEx
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020168B6
	bl FUN_020167F4
	add r7, r0, #0x0
	bmi _020168B0
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x0]
	mov r2, #0x0
	lsl r4, r7, #0x2
	bl tempName_NNS_FndCreateExpHeapEx
	ldr r1, _020168CC ; =0x021C4D28
	ldr r2, [r1, #0x0]
	str r0, [r2, r4]
	ldr r0, [r1, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _020168AA
	ldr r0, [r1, #0x4]
	str r6, [r0, r4]
	ldr r0, [sp, #0x4]
	ldr r2, [r1, #0x8]
	add sp, #0x8
	str r0, [r2, r4]
	ldr r0, [r1, #0x10]
	strb r7, [r0, r5]
	mov r0, #0x1
	pop {r3-r7, pc}
_020168AA:
	bl ErrorHandling
	b _020168C6
_020168B0:
	bl ErrorHandling
	b _020168C6
_020168B6:
	bl ErrorHandling
	b _020168C6
_020168BC:
	bl ErrorHandling
	b _020168C6
_020168C2:
	bl ErrorHandling
_020168C6:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020168CC: .word 0x021C4D28

	thumb_func_start FUN_020168D0
FUN_020168D0: ; 0x020168D0
	push {r4, lr}
	add r4, r0, #0x0
	bl OS_GetProcMode
	cmp r0, #0x12
	bne _020168E0
	bl ErrorHandling
_020168E0:
	ldr r0, _02016940 ; =0x021C4D28
	ldr r1, [r0, #0x0]
	ldr r0, [r0, #0x10]
	ldrb r0, [r0, r4]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0201693E
	bl thunk_FUN_020adc8c
	ldr r1, _02016940 ; =0x021C4D28
	ldr r0, [r1, #0x10]
	ldrb r0, [r0, r4]
	lsl r2, r0, #0x2
	ldr r0, [r1, #0x4]
	ldr r1, [r1, #0x8]
	ldr r0, [r0, r2]
	ldr r1, [r1, r2]
	cmp r0, #0x0
	beq _02016912
	cmp r1, #0x0
	beq _02016912
	bl FUN_020ADDF0
	b _02016916
_02016912:
	bl ErrorHandling
_02016916:
	ldr r1, _02016940 ; =0x021C4D28
	mov r0, #0x0
	ldr r2, [r1, #0x10]
	ldr r3, [r1, #0x0]
	ldrb r2, [r2, r4]
	lsl r2, r2, #0x2
	str r0, [r3, r2]
	ldr r2, [r1, #0x10]
	ldr r3, [r1, #0x4]
	ldrb r2, [r2, r4]
	lsl r2, r2, #0x2
	str r0, [r3, r2]
	ldr r2, [r1, #0x10]
	ldr r3, [r1, #0x8]
	ldrb r2, [r2, r4]
	lsl r2, r2, #0x2
	str r0, [r3, r2]
	ldrh r2, [r1, #0x1a]
	ldr r0, [r1, #0x10]
	strb r2, [r0, r4]
_0201693E:
	pop {r4, pc}
	.balign 4
_02016940: .word 0x021C4D28

	thumb_func_start FUN_02016944
FUN_02016944: ; 0x02016944
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	cmp r5, #0x0
	bne _02016956
	bl ErrorHandling
_02016956:
	bl OS_DisableInterrupts
	add r4, #0x10
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl tempName_NNS_FndAllocFromExpHeapEx
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	bl OS_RestoreInterrupts
	cmp r4, #0x0
	beq _02016984
	ldr r1, [r4, #0xc]
	mov r0, #0xff
	bic r1, r0
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	str r0, [r4, #0xc]
	add r4, #0x10
_02016984:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02016988
FUN_02016988: ; 0x02016988
	push {r3, lr}
	bl FUN_02031810
	cmp r0, #0x0
	beq _02016996
	bl FUN_0208A9B8
_02016996:
	pop {r3, pc}

	thumb_func_start FUN_02016998
FUN_02016998: ; 0x02016998
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _020169D4 ; =0x021C4D28
	mov r4, #0x0
	ldrh r2, [r0, #0x14]
	cmp r5, r2
	bhs _020169BA
	ldr r2, [r0, #0x0]
	ldr r0, [r0, #0x10]
	add r3, r5, #0x0
	ldrb r0, [r0, r5]
	lsl r0, r0, #0x2
	ldr r0, [r2, r0]
	mov r2, #0x4
	bl FUN_02016944
	add r4, r0, #0x0
_020169BA:
	cmp r4, #0x0
	beq _020169CC
	ldr r0, _020169D4 ; =0x021C4D28
	lsl r1, r5, #0x1
	ldr r2, [r0, #0xc]
	ldrh r0, [r2, r1]
	add r0, r0, #0x1
	strh r0, [r2, r1]
	b _020169D0
_020169CC:
	bl FUN_02016988
_020169D0:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_020169D4: .word 0x021C4D28

	thumb_func_start FUN_020169D8
FUN_020169D8: ; 0x020169D8
	push {r3-r5, lr}
	ldr r2, _02016A14 ; =0x021C4D28
	add r5, r0, #0x0
	ldrh r0, [r2, #0x14]
	mov r4, #0x0
	cmp r5, r0
	bhs _020169FA
	ldr r0, [r2, #0x0]
	ldr r2, [r2, #0x10]
	add r3, r5, #0x0
	ldrb r2, [r2, r5]
	lsl r2, r2, #0x2
	ldr r0, [r0, r2]
	sub r2, r4, #0x4
	bl FUN_02016944
	add r4, r0, #0x0
_020169FA:
	cmp r4, #0x0
	beq _02016A0C
	ldr r0, _02016A14 ; =0x021C4D28
	lsl r1, r5, #0x1
	ldr r2, [r0, #0xc]
	ldrh r0, [r2, r1]
	add r0, r0, #0x1
	strh r0, [r2, r1]
	b _02016A10
_02016A0C:
	bl FUN_02016988
_02016A10:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02016A14: .word 0x021C4D28

	thumb_func_start FUN_02016A18
FUN_02016A18: ; 0x02016A18
	push {r3-r7, lr}
	add r6, r0, #0x0
	sub r0, r6, #0x4
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, _02016A88 ; =0x021C4D28
	ldrh r1, [r0, #0x14]
	cmp r4, r1
	bhs _02016A80
	ldr r1, [r0, #0x0]
	ldr r0, [r0, #0x10]
	ldrb r0, [r0, r4]
	lsl r0, r0, #0x2
	ldr r7, [r1, r0]
	cmp r7, #0x0
	bne _02016A3E
	bl ErrorHandling
_02016A3E:
	ldr r0, _02016A88 ; =0x021C4D28
	lsl r5, r4, #0x1
	ldr r0, [r0, #0xc]
	ldrh r0, [r0, r5]
	cmp r0, #0x0
	bne _02016A50
	add r0, r4, #0x0
	bl FUN_02016B90
_02016A50:
	ldr r0, _02016A88 ; =0x021C4D28
	ldr r0, [r0, #0xc]
	ldrh r0, [r0, r5]
	cmp r0, #0x0
	bne _02016A5E
	bl ErrorHandling
_02016A5E:
	ldr r0, _02016A88 ; =0x021C4D28
	ldr r1, [r0, #0xc]
	ldrh r0, [r1, r5]
	sub r0, r0, #0x1
	strh r0, [r1, r5]
	bl OS_DisableInterrupts
	sub r6, #0x10
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_020ADDF0
	add r0, r4, #0x0
	bl OS_RestoreInterrupts
	pop {r3-r7, pc}
_02016A80:
	bl ErrorHandling
	pop {r3-r7, pc}
	nop
_02016A88: .word 0x021C4D28

	thumb_func_start FUN_02016A8C
FUN_02016A8C: ; 0x02016A8C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl OS_GetProcMode
	cmp r0, #0x12
	bne _02016A9E
	bl ErrorHandling
_02016A9E:
	ldr r0, _02016AF4 ; =0x021C4D28
	ldrh r1, [r0, #0x14]
	cmp r5, r1
	bhs _02016AEE
	ldr r1, [r0, #0x0]
	ldr r0, [r0, #0x10]
	ldrb r0, [r0, r5]
	lsl r0, r0, #0x2
	ldr r6, [r1, r0]
	cmp r6, #0x0
	bne _02016AB8
	bl ErrorHandling
_02016AB8:
	sub r0, r4, #0x4
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, r5
	beq _02016AC8
	bl ErrorHandling
_02016AC8:
	sub r4, #0x10
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_020ADDF0
	ldr r0, _02016AF4 ; =0x021C4D28
	lsl r4, r5, #0x1
	ldr r0, [r0, #0xc]
	ldrh r0, [r0, r4]
	cmp r0, #0x0
	bne _02016AE2
	bl ErrorHandling
_02016AE2:
	ldr r0, _02016AF4 ; =0x021C4D28
	ldr r1, [r0, #0xc]
	ldrh r0, [r1, r4]
	sub r0, r0, #0x1
	strh r0, [r1, r4]
	pop {r4-r6, pc}
_02016AEE:
	bl ErrorHandling
	pop {r4-r6, pc}
	.balign 4
_02016AF4: .word 0x021C4D28

	thumb_func_start FUN_02016AF8
FUN_02016AF8: ; 0x02016AF8
	push {r3, lr}
	ldr r1, _02016B1C ; =0x021C4D28
	ldrh r2, [r1, #0x14]
	cmp r0, r2
	bhs _02016B12
	ldr r2, [r1, #0x0]
	ldr r1, [r1, #0x10]
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x2
	ldr r0, [r2, r0]
	bl FUN_020ADDC8
	pop {r3, pc}
_02016B12:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	nop
_02016B1C: .word 0x021C4D28

	thumb_func_start FUN_02016B20
FUN_02016B20: ; 0x02016B20
	push {r4, lr}
	ldr r4, _02016B40 ; =0x021C4D28
	ldrh r3, [r4, #0x14]
	cmp r1, r3
	bhs _02016B3A
	ldr r3, [r4, #0x0]
	ldr r4, [r4, #0x10]
	ldrb r1, [r4, r1]
	lsl r1, r1, #0x2
	ldr r1, [r3, r1]
	bl FUN_020AE82C
	pop {r4, pc}
_02016B3A:
	bl ErrorHandling
	pop {r4, pc}
	.balign 4
_02016B40: .word 0x021C4D28

	thumb_func_start FUN_02016B44
FUN_02016B44: ; 0x02016B44
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl OS_GetProcMode
	cmp r0, #0x12
	bne _02016B56
	bl ErrorHandling
_02016B56:
	add r0, r5, #0x0
	sub r0, #0x10
	bl FUN_020ADDC0
	add r4, #0x10
	cmp r0, r4
	blo _02016B84
	sub r2, r5, #0x4
	ldr r0, _02016B8C ; =0x021C4D28
	ldr r2, [r2, #0x0]
	ldr r1, [r0, #0x0]
	lsl r2, r2, #0x18
	ldr r0, [r0, #0x10]
	lsr r2, r2, #0x18
	ldrb r0, [r0, r2]
	sub r5, #0x10
	add r2, r4, #0x0
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	add r1, r5, #0x0
	bl FUN_020ADE2C
	pop {r3-r5, pc}
_02016B84:
	bl ErrorHandling
	pop {r3-r5, pc}
	nop
_02016B8C: .word 0x021C4D28

	thumb_func_start FUN_02016B90
FUN_02016B90: ; 0x02016B90
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_02016B94
FUN_02016B94: ; 0x02016B94
	push {r3-r5, lr}
	mov r1, #0x5a
	lsl r1, r1, #0x2
	add r5, r0, #0x0
	bl FUN_02016998
	mov r2, #0x5a
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r4, r0, #0x0
	bl Call_FillMemWithValue
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
	bl FUN_0201E6D8
	bl FUN_0201E740
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
	bl FUN_0201E6D8
	pop {r3, pc}
_02016C0C:
	ldr r0, [r2, #0x8]
	bl GXS_SetGraphicsMode
	bl FUN_0201E740
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
	bl FUN_0201E6E4
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
	bl FUN_0201E6E4
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
	bl FUN_0201E6E4
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
	bl FUN_0201E6E4
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
	bl FUN_0201E74C
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
	bl FUN_0201E74C
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
	bl FUN_0201E74C
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
	bl FUN_0201E74C
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
	bl FUN_02016998
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
	bl FUN_02016A18
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
	bl FUN_0201E6E4
	pop {r3, pc}
_020179A6:
	mov r0, #0x2
	bl FUN_0201E6E4
	pop {r3, pc}
_020179AE:
	mov r0, #0x4
	bl FUN_0201E6E4
	pop {r3, pc}
_020179B6:
	mov r0, #0x8
	bl FUN_0201E6E4
	pop {r3, pc}
_020179BE:
	mov r0, #0x1
	bl FUN_0201E74C
	pop {r3, pc}
_020179C6:
	mov r0, #0x2
	bl FUN_0201E74C
	pop {r3, pc}
_020179CE:
	mov r0, #0x4
	bl FUN_0201E74C
	pop {r3, pc}
_020179D6:
	mov r0, #0x8
	bl FUN_0201E74C
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
	bl FUN_0201BB74
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
	bl FUN_020169D8
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
	bl FUN_02016A18
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
	bl FUN_020169D8
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
	bl FUN_02016A18
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
	bl FUN_020169D8
	add r4, r0, #0x0
	mov r1, #0x0
	add r2, r5, #0x0
	bl Call_FillMemWithValue
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
	bl FUN_020169D8
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
	bl FUN_02016A18
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
	bl FUN_02016998
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
	bl FUN_02016998
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
	bl FUN_02016998
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
	bl FUN_02016998
	ldr r1, [sp, #0x24]
	add r7, r0, #0x0
	lsl r2, r1, #0x4
	orr r1, r2
	lsl r1, r1, #0x18
	ldr r2, [sp, #0x4]
	lsr r1, r1, #0x18
	bl Call_FillMemWithValue
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
	bl FUN_02016A18
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
	bl FUN_02016A18
_020191BE:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r6
	blt _020191B0
_020191C8:
	add r0, r5, #0x0
	bl FUN_02016A18
	pop {r4-r6, pc}

	thumb_func_start FUN_020191D0
FUN_020191D0: ; 0x020191D0
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
	ldr r1, _0201921C ; =0x020EDB68
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_0201921C: .word 0x020EDB68

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
	ldr r1, _0201926C ; =0x020EDB5C
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_0201926C: .word 0x020EDB5C

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
	ldr r1, _02019288 ; =0x020EDB38
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.balign 4
_02019288: .word 0x020EDB38

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
	ldr r1, _020192B4 ; =0x020EDB38
	ldr r1, [r1, r2]
	blx r1
	strb r6, [r5, #0x7]
	strb r4, [r5, #0x8]
	pop {r4-r6, pc}
	nop
_020192B4: .word 0x020EDB38

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
	ldr r1, _020192D0 ; =0x020EDB74
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.balign 4
_020192D0: .word 0x020EDB74

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
	ldr r1, _020193B0 ; =0x020EDB30
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
_020193B0: .word 0x020EDB30

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
	ldr r0, _02019440 ; =0x020EDB30
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
_02019440: .word 0x020EDB30

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
	ldr r1, _02019498 ; =0x020EDB30
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
_02019498: .word 0x020EDB30

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
	ldr r1, _02019588 ; =0x020EDB50
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.balign 4
_02019588: .word 0x020EDB50

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
	ldr r1, _020195A4 ; =0x020EDB44
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.balign 4
_020195A4: .word 0x020EDB44

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

	thumb_func_start FUN_02019620
FUN_02019620: ; 0x02019620
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
	bl FUN_02016A18

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
	bl FUN_0201BB74
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
	bl FUN_0201BB74
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
	bl FUN_0201BB74
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
	bl FUN_0201BB74
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
	bl FUN_020169D8
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
	bl FUN_02016A18
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
	bl FUN_020169D8
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
	bl FUN_02016A18
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
	bl FUN_020169D8
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
	bl FUN_02016A18
_0201B1A4:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201B1A8
FUN_0201B1A8: ; 0x0201B1A8
	push {r3-r5, lr}
	add r5, r3, #0x0
	add r4, r2, #0x0
	bl FUN_020161A4
	str r0, [r5, #0x0]
	bl FUN_020BC0FC
	cmp r0, #0x0
	beq _0201B1D2
	bl FUN_0201B254
	cmp r0, #0x0
	bne _0201B1D2
	ldr r0, [r5, #0x0]
	ldr r1, [r0, #0x8]
	bl DC_FlushRange
	ldr r0, [r5, #0x0]
	bl FUN_020BB59C
_0201B1D2:
	ldr r0, [r5, #0x0]
	bl FUN_020BC13C
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201B1E4
FUN_0201B1E4: ; 0x0201B1E4
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020BC0FC
	cmp r0, #0x0
	beq _0201B20A
	bl FUN_0201B254
	cmp r0, #0x0
	bne _0201B20A
	ldr r0, [r5, #0x0]
	ldr r1, [r0, #0x8]
	bl DC_FlushRange
	ldr r0, [r5, #0x0]
	bl FUN_020BB59C
_0201B20A:
	ldr r0, [r5, #0x0]
	bl FUN_020BC13C
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201B21C
FUN_0201B21C: ; 0x0201B21C
	push {r3-r5, lr}
	add r4, r3, #0x0
	add r5, r2, #0x0
	ldr r3, [sp, #0x10]
	add r2, r4, #0x0
	bl FUN_0201B1A8
	ldr r1, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_020B80B4
	pop {r3-r5, pc}

	thumb_func_start FUN_0201B234
FUN_0201B234: ; 0x0201B234
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, r2, #0x0
	bl FUN_0201B1E4
	cmp r4, #0x0
	bne _0201B24A
	bl ErrorHandling
_0201B24A:
	ldr r1, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_020B80B4
	pop {r3-r5, pc}

	thumb_func_start FUN_0201B254
FUN_0201B254: ; 0x0201B254
	ldrh r2, [r0, #0x10]
	mov r1, #0x1
	tst r2, r1
	bne _0201B262
	ldrh r0, [r0, #0x20]
	tst r0, r1
	beq _0201B266
_0201B262:
	mov r0, #0x1
	bx lr
_0201B266:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0201B26C
FUN_0201B26C: ; 0x0201B26C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_020B8474
	ldr r1, _0201B2A0 ; =0x021CEDD4
	add r0, r4, #0x0
	bl MI_Copy36B
	ldr r1, _0201B2A4 ; =0x021CED98
	mov r0, #0xa4
	ldr r2, [r1, #0x7c]
	bic r2, r0
	add r0, r6, #0x0
	str r2, [r1, #0x7c]
	bl FUN_020B844C
	bl FUN_020B849C
	add r0, r5, #0x0
	bl FUN_020BAC98
	pop {r4-r6, pc}
	nop
_0201B2A0: .word 0x021CEDD4
_0201B2A4: .word 0x021CED98

	thumb_func_start FUN_0201B2A8
FUN_0201B2A8: ; 0x0201B2A8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_020B8474
	ldr r1, _0201B2E4 ; =0x021CEDD4
	add r0, r4, #0x0
	bl MI_Copy36B
	ldr r1, _0201B2E8 ; =0x021CED98
	mov r0, #0xa4
	ldr r2, [r1, #0x7c]
	bic r2, r0
	str r2, [r1, #0x7c]
	add r0, r6, #0x0
	bl FUN_020B844C
	bl FUN_020B849C
	mov r1, #0x0
	ldr r0, [r5, #0x4]
	add r2, r1, #0x0
	mov r3, #0x1
	bl FUN_020BAFB8
	bl FUN_020BB394
	pop {r4-r6, pc}
	.balign 4
_0201B2E4: .word 0x021CEDD4
_0201B2E8: .word 0x021CED98

	thumb_func_start FUN_0201B2EC
FUN_0201B2EC: ; 0x0201B2EC
	push {r3, lr}
	sub sp, #0x8
	mov r1, #0x4
	str r1, [sp, #0x0]
	ldr r1, _0201B30C ; =FUN_0201B314
	mov r2, #0x2
	str r1, [sp, #0x4]
	mov r1, #0x0
	add r3, r1, #0x0
	bl FUN_02022318
	ldr r1, _0201B310 ; =0x021C4D44
	str r0, [r1, #0x0]
	add sp, #0x8
	pop {r3, pc}
	nop
_0201B30C: .word FUN_0201B314
_0201B310: .word 0x021C4D44

	thumb_func_start FUN_0201B314
FUN_0201B314: ; 0x0201B314
	push {r3, lr}
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_0201E6E4
	ldr r0, _0201B380 ; =0x04000008
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	mov r1, #0x1
	orr r1, r2
	strh r1, [r0, #0x0]
	add r0, #0x58
	ldrh r2, [r0, #0x0]
	ldr r1, _0201B384 ; =0xFFFFCFFD
	and r2, r1
	strh r2, [r0, #0x0]
	add r2, r1, #0x2
	ldrh r3, [r0, #0x0]
	add r1, r1, #0x2
	and r3, r2
	mov r2, #0x10
	orr r2, r3
	strh r2, [r0, #0x0]
	ldrh r3, [r0, #0x0]
	ldr r2, _0201B388 ; =0x0000CFFB
	and r3, r2
	strh r3, [r0, #0x0]
	ldrh r3, [r0, #0x0]
	sub r2, #0x1c
	and r3, r1
	mov r1, #0x8
	orr r1, r3
	strh r1, [r0, #0x0]
	ldrh r1, [r0, #0x0]
	and r1, r2
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl G3X_SetFog
	mov r0, #0x0
	ldr r2, _0201B38C ; =0x00007FFF
	add r1, r0, #0x0
	mov r3, #0x3f
	str r0, [sp, #0x0]
	bl G3X_SetClearColor
	ldr r1, _0201B390 ; =0xBFFF0000
	ldr r0, _0201B394 ; =0x04000580
	str r1, [r0, #0x0]
	pop {r3, pc}
	.balign 4
_0201B380: .word 0x04000008
_0201B384: .word 0xFFFFCFFD
_0201B388: .word 0x0000CFFB
_0201B38C: .word 0x00007FFF
_0201B390: .word 0xBFFF0000
_0201B394: .word 0x04000580

	thumb_func_start FUN_0201B398
FUN_0201B398: ; 0x0201B398
	ldr r0, _0201B3A0 ; =0x021C4D44
	ldr r3, _0201B3A4 ; =FUN_020223BC
	ldr r0, [r0, #0x0]
	bx r3
	.balign 4
_0201B3A0: .word 0x021C4D44
_0201B3A4: .word FUN_020223BC

	thumb_func_start FUN_0201B3A8
FUN_0201B3A8: ; 0x0201B3A8
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020BC13C
	cmp r4, #0x0
	beq _0201B3BE
	add r1, r4, #0x0
	bl FUN_020B7790
	mov r0, #0x1
	pop {r4, pc}
_0201B3BE:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201B3C4
FUN_0201B3C4: ; 0x0201B3C4
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	bne _0201B3D2
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0201B3D2:
	mov r1, #0x0
	str r1, [r5, #0x8]
	mov r1, #0x1
	str r1, [sp, #0x8]
	str r1, [sp, #0x4]
	str r1, [sp, #0x0]
	cmp r5, #0x0
	beq _0201B4D0
	bl FUN_020B7E1C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020B7E10
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020B7CE4
	str r0, [sp, #0xc]
	cmp r6, #0x0
	beq _0201B412
	ldr r3, _0201B4D8 ; =0x021064B8
	mov r1, #0x0
	ldr r3, [r3, #0x0]
	add r0, r6, #0x0
	add r2, r1, #0x0
	blx r3
	add r7, r0, #0x0
	bne _0201B414
	mov r0, #0x0
	str r0, [sp, #0x8]
	b _0201B414
_0201B412:
	mov r7, #0x0
_0201B414:
	cmp r4, #0x0
	beq _0201B42E
	ldr r3, _0201B4D8 ; =0x021064B8
	add r0, r4, #0x0
	ldr r3, [r3, #0x0]
	mov r1, #0x1
	mov r2, #0x0
	blx r3
	add r6, r0, #0x0
	bne _0201B430
	mov r0, #0x0
	str r0, [sp, #0x4]
	b _0201B430
_0201B42E:
	mov r6, #0x0
_0201B430:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	beq _0201B450
	ldr r3, _0201B4DC ; =0x021064C0
	mov r1, #0x2
	ldrh r2, [r5, #0x20]
	lsl r1, r1, #0xe
	ldr r3, [r3, #0x0]
	and r1, r2
	mov r2, #0x0
	blx r3
	add r4, r0, #0x0
	bne _0201B452
	mov r0, #0x0
	str r0, [sp, #0x0]
	b _0201B452
_0201B450:
	mov r4, #0x0
_0201B452:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bne _0201B46E
	ldr r1, _0201B4E0 ; =0x021064BC
	add r0, r7, #0x0
	ldr r1, [r1, #0x0]
	blx r1
	cmp r0, #0x0
	beq _0201B468
	bl ErrorHandling
_0201B468:
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0201B46E:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _0201B48A
	ldr r1, _0201B4E0 ; =0x021064BC
	add r0, r6, #0x0
	ldr r1, [r1, #0x0]
	blx r1
	cmp r0, #0x0
	beq _0201B484
	bl ErrorHandling
_0201B484:
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0201B48A:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _0201B4A6
	ldr r1, _0201B4E4 ; =0x021064C4
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	blx r1
	cmp r0, #0x0
	beq _0201B4A0
	bl ErrorHandling
_0201B4A0:
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0201B4A6:
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_020B7DFC
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020B7CDC
	ldr r1, [r5, #0x4]
	add r0, r5, #0x0
	bl DC_FlushRange
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020B7D28
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020B7C78
_0201B4D0:
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_0201B4D8: .word 0x021064B8
_0201B4DC: .word 0x021064C0
_0201B4E0: .word 0x021064BC
_0201B4E4: .word 0x021064C4

	thumb_func_start FUN_0201B4E8
FUN_0201B4E8: ; 0x0201B4E8
	str r0, [r1, #0x0]
	add r0, r0, #0x4
	str r0, [r1, #0x8]
	str r0, [r1, #0x4]
	mov r0, #0x0
	str r0, [r1, #0xc]
	str r0, [r1, #0x10]
	str r0, [r1, #0x14]
	bx lr
	.balign 4

	thumb_func_start FUN_0201B4FC
FUN_0201B4FC: ; 0x0201B4FC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x0]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0201B52A
	add r4, r7, #0x0
	add r6, r7, #0x0
_0201B50C:
	ldr r1, [r5, #0x24]
	add r0, r5, #0x0
	add r1, r1, r4
	bl FUN_0201B4E8
	ldr r0, [r5, #0x24]
	add r7, r7, #0x1
	add r1, r0, r4
	ldr r0, [r5, #0x20]
	add r4, #0x1c
	str r1, [r0, r6]
	ldrh r0, [r5, #0x0]
	add r6, r6, #0x4
	cmp r7, r0
	blt _0201B50C
_0201B52A:
	mov r0, #0x0
	strh r0, [r5, #0x2]
	pop {r3-r7, pc}

	thumb_func_start FUN_0201B530
FUN_0201B530: ; 0x0201B530
	ldrh r3, [r0, #0x2]
	ldrh r1, [r0, #0x0]
	cmp r3, r1
	bne _0201B53C
	mov r0, #0x0
	bx lr
_0201B53C:
	ldr r2, [r0, #0x20]
	lsl r1, r3, #0x2
	ldr r2, [r2, r1]
	add r1, r3, #0x1
	strh r1, [r0, #0x2]
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0201B54C
FUN_0201B54C: ; 0x0201B54C
	ldrh r2, [r0, #0x2]
	cmp r2, #0x0
	bne _0201B556
	mov r0, #0x0
	bx lr
_0201B556:
	str r0, [r1, #0x0]
	add r2, r0, #0x4
	str r2, [r1, #0x8]
	str r2, [r1, #0x4]
	mov r2, #0x0
	str r2, [r1, #0xc]
	str r2, [r1, #0x10]
	str r2, [r1, #0x14]
	ldrh r2, [r0, #0x2]
	sub r2, r2, #0x1
	strh r2, [r0, #0x2]
	ldr r2, [r0, #0x20]
	ldrh r0, [r0, #0x2]
	lsl r0, r0, #0x2
	str r1, [r2, r0]
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0201B578
FUN_0201B578: ; 0x0201B578
	lsl r0, r0, #0x5
	add r0, #0x34
	bx lr
	.balign 4

	thumb_func_start FUN_0201B580
FUN_0201B580: ; 0x0201B580
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bne _0201B58C
	bl ErrorHandling
_0201B58C:
	add r1, r4, #0x0
	add r1, #0x34
	lsl r0, r5, #0x2
	str r1, [r4, #0x20]
	add r0, r1, r0
	str r0, [r4, #0x24]
	strh r5, [r4, #0x0]
	mov r0, #0x0
	strh r0, [r4, #0x2]
	str r0, [r4, #0x28]
	add r0, r4, #0x0
	bl FUN_0201B5AC
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201B5AC
FUN_0201B5AC: ; 0x0201B5AC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201B4FC
	str r4, [r4, #0x4]
	add r0, r4, #0x4
	str r0, [r4, #0xc]
	str r0, [r4, #0x8]
	mov r0, #0x0
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	ldr r0, [r4, #0xc]
	str r0, [r4, #0x2c]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201B5CC
FUN_0201B5CC: ; 0x0201B5CC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x28]
	cmp r0, #0x0
	bne _0201B608
	ldr r1, [r5, #0xc]
	add r4, r5, #0x4
	str r1, [r5, #0x2c]
	cmp r1, r4
	beq _0201B604
	mov r6, #0x0
_0201B5E2:
	ldr r0, [r1, #0x8]
	str r0, [r5, #0x30]
	ldr r0, [r5, #0x2c]
	ldr r1, [r0, #0x18]
	cmp r1, #0x0
	bne _0201B5FA
	ldr r2, [r0, #0x14]
	cmp r2, #0x0
	beq _0201B5FC
	ldr r1, [r0, #0x10]
	blx r2
	b _0201B5FC
_0201B5FA:
	str r6, [r0, #0x18]
_0201B5FC:
	ldr r1, [r5, #0x30]
	str r1, [r5, #0x2c]
	cmp r1, r4
	bne _0201B5E2
_0201B604:
	mov r0, #0x0
	str r0, [r1, #0x14]
_0201B608:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0201B60C
FUN_0201B60C: ; 0x0201B60C
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r5, #0x1
	str r5, [r4, #0x28]
	bl FUN_0201B620
	mov r1, #0x0
	str r1, [r4, #0x28]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201B620
FUN_0201B620: ; 0x0201B620
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	bl FUN_0201B530
	cmp r0, #0x0
	bne _0201B636
	mov r0, #0x0
	pop {r3-r7, pc}
_0201B636:
	str r4, [r0, #0xc]
	str r7, [r0, #0x10]
	str r6, [r0, #0x14]
	ldr r2, [r5, #0x2c]
	ldr r1, [r2, #0x14]
	cmp r1, #0x0
	beq _0201B656
	ldr r1, [r2, #0xc]
	cmp r1, r4
	bhi _0201B650
	mov r1, #0x1
	str r1, [r0, #0x18]
	b _0201B65A
_0201B650:
	mov r1, #0x0
	str r1, [r0, #0x18]
	b _0201B65A
_0201B656:
	mov r1, #0x0
	str r1, [r0, #0x18]
_0201B65A:
	ldr r3, [r5, #0xc]
	add r2, r5, #0x4
	cmp r3, r2
	beq _0201B686
	ldr r4, [r0, #0xc]
_0201B664:
	ldr r1, [r3, #0xc]
	cmp r1, r4
	bls _0201B680
	ldr r1, [r3, #0x4]
	str r1, [r0, #0x4]
	str r3, [r0, #0x8]
	ldr r1, [r3, #0x4]
	str r0, [r1, #0x8]
	str r0, [r3, #0x4]
	ldr r1, [r5, #0x30]
	cmp r3, r1
	bne _0201B69E
	str r0, [r5, #0x30]
	pop {r3-r7, pc}
_0201B680:
	ldr r3, [r3, #0x8]
	cmp r3, r2
	bne _0201B664
_0201B686:
	ldr r2, [r5, #0x30]
	add r1, r5, #0x4
	cmp r2, r1
	bne _0201B690
	str r0, [r5, #0x30]
_0201B690:
	ldr r1, [r5, #0x8]
	str r1, [r0, #0x4]
	add r1, r5, #0x4
	str r1, [r0, #0x8]
	ldr r1, [r5, #0x8]
	str r0, [r1, #0x8]
	str r0, [r5, #0x8]
_0201B69E:
	pop {r3-r7, pc}

	thumb_func_start FUN_0201B6A0
FUN_0201B6A0: ; 0x0201B6A0
	add r1, r0, #0x0
	ldr r2, [r1, #0x0]
	ldr r0, [r2, #0x30]
	cmp r0, r1
	bne _0201B6AE
	ldr r0, [r1, #0x8]
	str r0, [r2, #0x30]
_0201B6AE:
	ldr r2, [r1, #0x8]
	ldr r0, [r1, #0x4]
	ldr r3, _0201B6C0 ; =0x0201B54D
	str r2, [r0, #0x8]
	ldr r2, [r1, #0x4]
	ldr r0, [r1, #0x8]
	str r2, [r0, #0x4]
	ldr r0, [r1, #0x0]
	bx r3
	.balign 4
_0201B6C0: .word 0x0201B54D

	thumb_func_start FUN_0201B6C4
FUN_0201B6C4: ; 0x0201B6C4
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start FUN_0201B6C8
FUN_0201B6C8: ; 0x0201B6C8
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start FUN_0201B6CC
FUN_0201B6CC: ; 0x0201B6CC
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_0201B6D0
FUN_0201B6D0: ; 0x0201B6D0
	push {r4-r7, lr}
	sub sp, #0x34
	add r6, r1, #0x0
	add r4, r0, #0x0
	add r5, r2, #0x0
	ldmia r6!, {r0-r1}
	add r2, sp, #0x1c
	stmia r2!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r4, #0x14
	str r0, [r2, #0x0]
	mov r0, #0x20
	ldrsh r0, [r4, r0]
	add r7, r3, #0x0
	mov r1, #0x1a
	str r0, [sp, #0x0]
	mov r0, #0x22
	ldrsh r0, [r4, r0]
	mov r2, #0x1c
	mov r3, #0x1e
	str r0, [sp, #0x4]
	add r0, sp, #0x28
	str r0, [sp, #0x8]
	mov r0, #0x18
	ldrsh r0, [r4, r0]
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	bl FUN_0201B808
	add r0, sp, #0x1c
	bl FUN_020B8474
	ldr r1, _0201B764 ; =0x021CEDD4
	add r0, r5, #0x0
	bl MI_Copy36B
	ldr r1, _0201B768 ; =0x021CED98
	mov r0, #0xa4
	ldr r2, [r1, #0x7c]
	bic r2, r0
	add r0, r7, #0x0
	str r2, [r1, #0x7c]
	bl FUN_020B844C
	bl FUN_020B849C
	mov r1, #0x0
	mov r0, #0x11
	add r2, r1, #0x0
	bl FUN_020BB1C0
	ldr r0, [r4, #0x24]
	add r1, sp, #0x10
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	mov r0, #0x1b
	mov r2, #0x3
	bl FUN_020BB1C0
	add r0, sp, #0x28
	bl FUN_0201B82C
	add r4, r0, #0x0
	mov r2, #0x1
	mov r0, #0x12
	add r1, sp, #0xc
	str r2, [sp, #0xc]
	bl FUN_020BB1C0
	add r0, r4, #0x0
	add sp, #0x34
	pop {r4-r7, pc}
	.balign 4
_0201B764: .word 0x021CEDD4
_0201B768: .word 0x021CED98

	thumb_func_start FUN_0201B76C
FUN_0201B76C: ; 0x0201B76C
	push {r3-r5, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x2
	ldrsh r0, [r4, r0]
	str r0, [sp, #0x0]
	mov r0, #0x4
	ldrsh r0, [r4, r0]
	str r0, [sp, #0x4]
	add r0, sp, #0x1c
	str r0, [sp, #0x8]
	mov r0, #0x0
	ldrsh r3, [r4, r0]
	add r1, r0, #0x0
	add r2, r0, #0x0
	bl FUN_0201B808
	add r0, r5, #0x0
	bl FUN_020B8474
	bl FUN_020B849C
	mov r1, #0x0
	mov r0, #0x11
	add r2, r1, #0x0
	bl FUN_020BB1C0
	ldr r0, [r4, #0x10]
	lsl r2, r0, #0xc
	ldr r0, [r4, #0xc]
	lsl r1, r0, #0xc
	ldr r0, [r4, #0x8]
	lsl r0, r0, #0xc
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	str r2, [sp, #0x18]
	mov r0, #0x1b
	add r1, sp, #0x10
	mov r2, #0x3
	bl FUN_020BB1C0
	add r0, sp, #0x1c
	bl FUN_0201B82C
	add r4, r0, #0x0
	mov r2, #0x1
	mov r0, #0x12
	add r1, sp, #0xc
	str r2, [sp, #0xc]
	bl FUN_020BB1C0
	add r0, r4, #0x0
	add sp, #0x28
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201B7DC
FUN_0201B7DC: ; 0x0201B7DC
	push {r4-r6, lr}
	add r6, r3, #0x0
	add r4, r2, #0x0
	add r2, r6, #0x0
	add r5, r1, #0x0
	add r1, r6, #0x0
	add r2, #0x8
	bl FUN_0201B880
	add r2, r6, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x2
	add r2, #0xc
	bl FUN_0201B880
	add r1, r6, #0x4
	add r6, #0x10
	add r0, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0201B880
	pop {r4-r6, pc}

	thumb_func_start FUN_0201B808
FUN_0201B808: ; 0x0201B808
	push {r3-r4}
	ldr r4, [sp, #0x10]
	strh r0, [r4, #0x0]
	strh r1, [r4, #0x2]
	ldr r1, _0201B828 ; =0xFFFFFFF8
	strh r2, [r4, #0x4]
	strh r3, [r4, #0x6]
	add r1, sp
	mov r0, #0x10
	ldrsh r0, [r1, r0]
	strh r0, [r4, #0x8]
	mov r0, #0x14
	ldrsh r0, [r1, r0]
	strh r0, [r4, #0xa]
	pop {r3-r4}
	bx lr
	.balign 4
_0201B828: .word 0xFFFFFFF8

	thumb_func_start FUN_0201B82C
FUN_0201B82C: ; 0x0201B82C
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r0, _0201B87C ; =0x000030C1
	mov r2, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x29
	add r1, sp, #0x4
	str r2, [sp, #0x8]
	bl FUN_020BB1C0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x40
	add r1, sp, #0x0
	mov r2, #0x1
	bl FUN_020BB1C0
	mov r1, #0x0
	mov r0, #0x41
	add r2, r1, #0x0
	bl FUN_020BB1C0
	mov r0, #0x70
	add r1, r4, #0x0
	mov r2, #0x3
	bl FUN_020BB1C0
	bl FUN_020BB394
	add r4, sp, #0x8
_0201B86A:
	add r0, r4, #0x0
	bl G3X_GetBoxTestResult
	cmp r0, #0x0
	bne _0201B86A
	ldr r0, [sp, #0x8]
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_0201B87C: .word 0x000030C1

	thumb_func_start FUN_0201B880
FUN_0201B880: ; 0x0201B880
	push {r3-r4}
	ldr r4, _0201B8B4 ; =0x00007FFF
	mov r3, #0x0
	cmp r0, r4
	blo _0201B896
_0201B88A:
	add r3, r3, #0x1
	lsl r3, r3, #0x18
	lsr r0, r0, #0x1
	lsr r3, r3, #0x18
	cmp r0, r4
	bhs _0201B88A
_0201B896:
	strh r0, [r1, #0x0]
	mov r0, #0x1
	mov r1, #0x0
	str r0, [r2, #0x0]
	cmp r3, #0x0
	ble _0201B8AE
_0201B8A2:
	ldr r0, [r2, #0x0]
	add r1, r1, #0x1
	lsl r0, r0, #0x1
	str r0, [r2, #0x0]
	cmp r1, r3
	blt _0201B8A2
_0201B8AE:
	pop {r3-r4}
	bx lr
	nop
_0201B8B4: .word 0x00007FFF

	thumb_func_start FUN_0201B8B8
FUN_0201B8B8: ; 0x0201B8B8
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r1, [r4, #0x0]
	ldr r0, _0201B8DC ; =0x0000FFFE
	cmp r1, r0
	beq _0201B8C8
	bl ErrorHandling
_0201B8C8:
	ldrh r1, [r4, #0x0]
	ldr r0, _0201B8DC ; =0x0000FFFE
	cmp r1, r0
	bne _0201B8D8
	ldrh r0, [r4, #0x4]
	add r1, r4, #0x6
	lsl r0, r0, #0x1
	add r4, r1, r0
_0201B8D8:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_0201B8DC: .word 0x0000FFFE

	thumb_func_start FUN_0201B8E0
FUN_0201B8E0: ; 0x0201B8E0
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r1, [r4, #0x0]
	ldr r0, _0201B8F4 ; =0x0000FFFE
	cmp r1, r0
	beq _0201B8F0
	bl ErrorHandling
_0201B8F0:
	ldrh r0, [r4, #0x2]
	pop {r4, pc}
	.balign 4
_0201B8F4: .word 0x0000FFFE

	thumb_func_start FUN_0201B8F8
FUN_0201B8F8: ; 0x0201B8F8
	push {r3, lr}
	bl FUN_0201B8E0
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r1, r0
	mov r0, #0x1
	lsl r0, r0, #0x8
	cmp r1, r0
	bne _0201B910
	mov r0, #0x1
	pop {r3, pc}
_0201B910:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0201B914
FUN_0201B914: ; 0x0201B914
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldrh r1, [r5, #0x0]
	ldr r0, _0201B938 ; =0x0000FFFE
	cmp r1, r0
	beq _0201B926
	bl ErrorHandling
_0201B926:
	ldrh r0, [r5, #0x4]
	cmp r4, r0
	blo _0201B930
	bl ErrorHandling
_0201B930:
	lsl r0, r4, #0x1
	add r0, r5, r0
	ldrh r0, [r0, #0x6]
	pop {r3-r5, pc}
	.balign 4
_0201B938: .word 0x0000FFFE

	thumb_func_start FUN_0201B93C
FUN_0201B93C: ; 0x0201B93C
	mov r1, #0x5a
	lsl r1, r1, #0x2
	cmp r0, r1
	blo _0201B948
	mov r0, #0x0
	bx lr
_0201B948:
	lsl r1, r0, #0x2
	ldr r0, _0201B950 ; =0x020EDF50
	ldr r0, [r0, r1]
	bx lr
	.balign 4
_0201B950: .word 0x020EDF50

	thumb_func_start FUN_0201B954
FUN_0201B954: ; 0x0201B954
	mov r1, #0x5a
	lsl r1, r1, #0x2
	cmp r0, r1
	blo _0201B960
	mov r0, #0x0
	bx lr
_0201B960:
	add r0, #0x5a
	lsl r1, r0, #0x2
	ldr r0, _0201B96C ; =0x020EDF50
	ldr r0, [r0, r1]
	bx lr
	nop
_0201B96C: .word 0x020EDF50

	thumb_func_start FUN_0201B970
FUN_0201B970: ; 0x0201B970
	push {r3, lr}
	mov r1, #0x5a
	lsl r1, r1, #0x2
	bl _s32_div_f
	ldr r0, _0201B984 ; =0x020EDF50
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	pop {r3, pc}
	nop
_0201B984: .word 0x020EDF50

	thumb_func_start FUN_0201B988
FUN_0201B988: ; 0x0201B988
	push {r3, lr}
	mov r1, #0x5a
	lsl r1, r1, #0x2
	bl _s32_div_f
	add r1, #0x5a
	ldr r0, _0201B99C ; =0x020EDF50
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_0201B99C: .word 0x020EDF50

	thumb_func_start FUN_0201B9A0
FUN_0201B9A0: ; 0x0201B9A0
	push {r3, lr}
	mov r1, #0x5a
	lsl r1, r1, #0x2
	bl _s32_div_f
	ldr r0, _0201B9B4 ; =0x020EDC7E
	lsl r1, r1, #0x1
	ldrh r0, [r0, r1]
	pop {r3, pc}
	nop
_0201B9B4: .word 0x020EDC7E

	thumb_func_start FUN_0201B9B8
FUN_0201B9B8: ; 0x0201B9B8
	push {r3, lr}
	lsl r0, r0, #0x4
	mov r1, #0x5a
	lsr r0, r0, #0x10
	lsl r1, r1, #0x2
	bl _s32_div_f
	ldr r0, _0201B9D0 ; =0x020EDF50
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	pop {r3, pc}
	nop
_0201B9D0: .word 0x020EDF50

	thumb_func_start FUN_0201B9D4
FUN_0201B9D4: ; 0x0201B9D4
	ldr r0, _0201B9DC ; =0x021C4D48
	ldr r0, [r0, #0x0]
	bx lr
	nop
_0201B9DC: .word 0x021C4D48

	thumb_func_start FUN_0201B9E0
FUN_0201B9E0: ; 0x0201B9E0
	ldr r1, _0201B9E8 ; =0x021C4D48
	str r0, [r1, #0x0]
	bx lr
	nop
_0201B9E8: .word 0x021C4D48

	thumb_func_start FUN_0201B9EC
FUN_0201B9EC: ; 0x0201B9EC
	ldr r1, _0201BA04 ; =0x021C4D48
	ldr r0, _0201BA08 ; =0x41C64E6D
	ldr r2, [r1, #0x0]
	add r3, r2, #0x0
	mul r3, r0
	ldr r0, _0201BA0C ; =0x00006073
	add r0, r3, r0
	str r0, [r1, #0x0]
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
	.balign 4
_0201BA04: .word 0x021C4D48
_0201BA08: .word 0x41C64E6D
_0201BA0C: .word 0x00006073

	thumb_func_start FUN_0201BA10
FUN_0201BA10: ; 0x0201BA10
	ldr r1, _0201BA18 ; =0x6C078965
	mul r1, r0
	add r0, r1, #0x1
	bx lr
	.balign 4
_0201BA18: .word 0x6C078965

	thumb_func_start FUN_0201BA1C
FUN_0201BA1C: ; 0x0201BA1C
	push {r4-r5}
	ldr r1, _0201BA50 ; =0x021C4D48
	mov r4, #0x27
	str r0, [r1, #0x4]
	ldr r1, _0201BA54 ; =0x02105BA8
	mov r0, #0x1
	str r0, [r1, #0x0]
	ldr r1, _0201BA58 ; =0x021C4D50
	ldr r3, _0201BA5C ; =0x6C078965
	lsl r4, r4, #0x4
_0201BA30:
	sub r2, r1, #0x4
	ldr r5, [r2, #0x0]
	lsr r2, r5, #0x1e
	eor r2, r5
	add r5, r2, #0x0
	mul r5, r3
	add r2, r0, r5
	add r0, r0, #0x1
	stmia r1!, {r2}
	cmp r0, r4
	blt _0201BA30
	ldr r1, _0201BA54 ; =0x02105BA8
	str r0, [r1, #0x0]
	pop {r4-r5}
	bx lr
	nop
_0201BA50: .word 0x021C4D48
_0201BA54: .word 0x02105BA8
_0201BA58: .word 0x021C4D50
_0201BA5C: .word 0x6C078965

	thumb_func_start FUN_0201BA60
FUN_0201BA60: ; 0x0201BA60
	push {r3-r7, lr}
	ldr r0, _0201BB44 ; =0x02105BA8
	ldr r1, [r0, #0x0]
	mov r0, #0x27
	lsl r0, r0, #0x4
	cmp r1, r0
	blt _0201BB18
	add r0, r0, #0x1
	cmp r1, r0
	bne _0201BA7A
	ldr r0, _0201BB48 ; =0x00001571
	bl FUN_0201BA1C
_0201BA7A:
	ldr r4, _0201BB4C ; =0x021C4D4C
	ldr r1, _0201BB50 ; =0x02105BAC
	ldr r5, _0201BB54 ; =0x7FFFFFFF
	ldr r6, _0201BB58 ; =0x00000634
	mov r0, #0x0
_0201BA84:
	mov r2, #0x2
	ldr r3, [r4, #0x0]
	lsl r2, r2, #0x1e
	and r3, r2
	ldr r2, [r4, #0x4]
	add r0, r0, #0x1
	and r2, r5
	orr r3, r2
	lsr r7, r3, #0x1
	lsl r3, r3, #0x1f
	ldr r2, [r4, r6]
	lsr r3, r3, #0x1d
	ldr r3, [r1, r3]
	eor r2, r7
	eor r2, r3
	stmia r4!, {r2}
	cmp r0, #0xe3
	blt _0201BA84
	ldr r1, _0201BB5C ; =0x0000026F
	cmp r0, r1
	bge _0201BAE4
	ldr r2, _0201BB4C ; =0x021C4D4C
	lsl r1, r0, #0x2
	add r1, r2, r1
	mov r2, #0xe3
	ldr r4, _0201BB50 ; =0x02105BAC
	ldr r3, _0201BB5C ; =0x0000026F
	lsl r2, r2, #0x2
_0201BABC:
	mov r5, #0x2
	ldr r6, [r1, #0x0]
	lsl r5, r5, #0x1e
	and r5, r6
	ldr r7, [r1, #0x4]
	ldr r6, _0201BB54 ; =0x7FFFFFFF
	add r0, r0, #0x1
	and r6, r7
	orr r6, r5
	lsr r5, r6, #0x1
	sub r7, r1, r2
	lsl r6, r6, #0x1f
	ldr r7, [r7, #0x0]
	lsr r6, r6, #0x1d
	ldr r6, [r4, r6]
	eor r5, r7
	eor r5, r6
	stmia r1!, {r5}
	cmp r0, r3
	blt _0201BABC
_0201BAE4:
	ldr r2, _0201BB60 ; =0x021C56C8
	mov r0, #0x2
	ldr r1, [r2, #0x40]
	lsl r0, r0, #0x1e
	add r3, r1, #0x0
	ldr r1, _0201BB64 ; =0x021C4D48
	and r3, r0
	ldr r1, [r1, #0x4]
	sub r0, r0, #0x1
	and r0, r1
	add r4, r3, #0x0
	orr r4, r0
	ldr r0, _0201BB68 ; =0x021C5348
	ldr r1, [r0, #0x34]
	lsr r0, r4, #0x1
	add r3, r1, #0x0
	eor r3, r0
	lsl r0, r4, #0x1f
	lsr r1, r0, #0x1d
	ldr r0, _0201BB50 ; =0x02105BAC
	ldr r0, [r0, r1]
	mov r1, #0x0
	eor r0, r3
	str r0, [r2, #0x40]
	ldr r0, _0201BB44 ; =0x02105BA8
	str r1, [r0, #0x0]
_0201BB18:
	ldr r0, _0201BB44 ; =0x02105BA8
	ldr r2, [r0, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x0]
	ldr r0, _0201BB4C ; =0x021C4D4C
	lsl r1, r2, #0x2
	ldr r1, [r0, r1]
	lsr r0, r1, #0xb
	add r2, r1, #0x0
	eor r2, r0
	ldr r0, _0201BB6C ; =0x9D2C5680
	lsl r1, r2, #0x7
	and r0, r1
	eor r2, r0
	ldr r0, _0201BB70 ; =0xEFC60000
	lsl r1, r2, #0xf
	and r0, r1
	add r1, r2, #0x0
	eor r1, r0
	lsr r0, r1, #0x12
	eor r0, r1
	pop {r3-r7, pc}
	.balign 4
_0201BB44: .word 0x02105BA8
_0201BB48: .word 0x00001571
_0201BB4C: .word 0x021C4D4C
_0201BB50: .word 0x02105BAC
_0201BB54: .word 0x7FFFFFFF
_0201BB58: .word 0x00000634
_0201BB5C: .word 0x0000026F
_0201BB60: .word 0x021C56C8
_0201BB64: .word 0x021C4D48
_0201BB68: .word 0x021C5348
_0201BB6C: .word 0x9D2C5680
_0201BB70: .word 0xEFC60000

	thumb_func_start FUN_0201BB74
FUN_0201BB74: ; 0x0201BB74
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, sp, #0x0
	ldrb r0, [r0, #0x10]
	add r4, r2, #0x0
	add r6, r3, #0x0
	cmp r0, #0x1
	bne _0201BB8E
	ldr r0, _0201BBC8 ; =0x0000FFFF
	mul r0, r1
	lsl r0, r0, #0x8
	lsr r1, r0, #0x10
	b _0201BBA2
_0201BB8E:
	cmp r0, #0x2
	bne _0201BBA2
	ldr r0, _0201BBC8 ; =0x0000FFFF
	mul r0, r1
	mov r1, #0x5a
	lsl r1, r1, #0x2
	bl _u32_div_f
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
_0201BBA2:
	asr r0, r1, #0x4
	lsl r3, r0, #0x1
	lsl r1, r3, #0x1
	ldr r2, _0201BBCC ; =0x020FFA38
	add r3, r3, #0x1
	lsl r3, r3, #0x1
	ldrsh r1, [r2, r1]
	ldrsh r2, [r2, r3]
	add r0, r5, #0x0
	bl MTX_Rot22_
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl MTX_ScaleApply22
	pop {r4-r6, pc}
	nop
_0201BBC8: .word 0x0000FFFF
_0201BBCC: .word 0x020FFA38

	thumb_func_start FUN_0201BBD0
FUN_0201BBD0: ; 0x0201BBD0
	push {r3-r7, lr}
	sub sp, #0x38
	lsl r5, r0, #0xc
	lsl r4, r1, #0xc
	mov r1, #0x0
	lsl r0, r2, #0xc
	lsl r6, r3, #0xc
	str r1, [sp, #0x34]
	str r0, [sp, #0x0]
	str r0, [sp, #0x20]
	str r1, [sp, #0x28]
	str r1, [sp, #0x8]
	str r1, [sp, #0xc]
	asr r1, r5, #0x1f
	add r0, r5, #0x0
	asr r3, r6, #0x1f
	add r2, r6, #0x0
	str r5, [sp, #0x2c]
	str r4, [sp, #0x30]
	str r6, [sp, #0x24]
	bl _ll_mul
	str r0, [sp, #0x4]
	add r2, r4, #0x0
	ldr r0, [sp, #0x20]
	add r7, r1, #0x0
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	ldr r3, [sp, #0x4]
	lsl r2, r2, #0xa
	add r3, r3, r2
	ldr r2, _0201BC80 ; =0x00000000
	str r4, [sp, #0x2c]
	adc r7, r2
	lsl r2, r7, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	mov r2, #0x2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _0201BC80 ; =0x00000000
	str r5, [sp, #0x30]
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	sub r2, r3, r0
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	str r2, [sp, #0x10]
	add r0, r1, r0
	add r7, r2, r0
	mov r0, #0x0
	str r0, [sp, #0x34]
	add r0, sp, #0x2c
	add r1, sp, #0x14
	bl VEC_Normalize
	mov r1, #0x0
	ldr r0, [sp, #0x0]
	str r1, [sp, #0x34]
	str r0, [sp, #0x20]
	str r1, [sp, #0x28]
	add r0, sp, #0x20
	add r1, sp, #0x2c
	add r2, sp, #0x8
	str r5, [sp, #0x2c]
	str r4, [sp, #0x30]
	str r6, [sp, #0x24]
	bl VEC_Subtract
	add r0, sp, #0x14
	add r1, sp, #0x8
	bl VEC_DotProduct
	asr r0, r0, #0xc
	bpl _0201BC72
	neg r0, r0
_0201BC72:
	cmp r7, #0x0
	bgt _0201BC7C
	mov r1, #0x0
	mvn r1, r1
	mul r0, r1
_0201BC7C:
	add sp, #0x38
	pop {r3-r7, pc}
	.balign 4
_0201BC80: .word 0x00000000

	thumb_func_start FUN_0201BC84
FUN_0201BC84: ; 0x0201BC84
	push {r3-r5, lr}
	lsl r0, r0, #0xd
	add r4, r1, #0x0
	ldr r2, _0201BCB4 ; =0x0000323D
	asr r1, r0, #0x1f
	mov r3, #0x0
	bl _ll_mul
	add r5, r0, #0x0
	ldr r0, _0201BCB8 ; =0x0000FFFF
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	mul r0, r4
	add r2, r5, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	asr r1, r2, #0xc
	bl _s32_div_f
	pop {r3-r5, pc}
	nop
_0201BCB4: .word 0x0000323D
_0201BCB8: .word 0x0000FFFF

	thumb_func_start FUN_0201BCBC
FUN_0201BCBC: ; 0x0201BCBC
	ldr r1, _0201BCC4 ; =0x02105BB4
	str r0, [r1, #0x0]
	bx lr
	nop
_0201BCC4: .word 0x02105BB4

	thumb_func_start FUN_0201BCC8
FUN_0201BCC8: ; 0x0201BCC8
	push {r4-r6, lr}
	ldr r4, _0201BCF8 ; =0x021C5714
	mov r5, #0x0
_0201BCCE:
	ldr r3, [r4, #0x0]
	cmp r3, #0x0
	bne _0201BCE8
	ldr r6, _0201BCF8 ; =0x021C5714
	lsl r4, r5, #0x2
	bl FUN_0200CA7C
	str r0, [r6, r4]
	ldr r0, [r6, r4]
	cmp r0, #0x0
	bne _0201BCF0
	mov r5, #0x8
	b _0201BCF0
_0201BCE8:
	add r5, r5, #0x1
	add r4, r4, #0x4
	cmp r5, #0x8
	blt _0201BCCE
_0201BCF0:
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	pop {r4-r6, pc}
	nop
_0201BCF8: .word 0x021C5714

	thumb_func_start FUN_0201BCFC
FUN_0201BCFC: ; 0x0201BCFC
	push {r4-r6, lr}
	add r5, r0, #0x0
	cmp r5, #0x8
	blo _0201BD08
	bl ErrorHandling
_0201BD08:
	ldr r6, _0201BD40 ; =0x021C5714
	lsl r4, r5, #0x2
	ldr r0, [r6, r4]
	cmp r0, #0x0
	bne _0201BD16
	bl ErrorHandling
_0201BD16:
	cmp r5, #0x8
	bhs _0201BD3C
	ldr r0, [r6, r4]
	cmp r0, #0x0
	beq _0201BD3C
	bl FUN_0201B6C8
	add r5, r0, #0x0
	beq _0201BD32
	bl FUN_0201C238
	add r0, r5, #0x0
	bl FUN_02016A18
_0201BD32:
	ldr r0, [r6, r4]
	bl FUN_0200CAB4
	mov r0, #0x0
	str r0, [r6, r4]
_0201BD3C:
	pop {r4-r6, pc}
	nop
_0201BD40: .word 0x021C5714

	thumb_func_start FUN_0201BD44
FUN_0201BD44: ; 0x0201BD44
	lsl r1, r0, #0x2
	ldr r0, _0201BD58 ; =0x021C5714
	ldr r0, [r0, r1]
	cmp r0, #0x0
	beq _0201BD52
	mov r0, #0x1
	bx lr
_0201BD52:
	mov r0, #0x0
	bx lr
	nop
_0201BD58: .word 0x021C5714

	thumb_func_start FUN_0201BD5C
FUN_0201BD5C: ; 0x0201BD5C
	mov r1, #0x0
	ldr r2, _0201BD6C ; =0x021C5714
	add r0, r1, #0x0
_0201BD62:
	add r1, r1, #0x1
	stmia r2!, {r0}
	cmp r1, #0x8
	blt _0201BD62
	bx lr
	.balign 4
_0201BD6C: .word 0x021C5714

	thumb_func_start FUN_0201BD70
FUN_0201BD70: ; 0x0201BD70
	push {r3, lr}
	bl FUN_0201BD44
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}

	thumb_func_start FUN_0201BD7C
FUN_0201BD7C: ; 0x0201BD7C
	ldr r3, _0201BD80 ; =FUN_0201BCFC
	bx r3
	.balign 4
_0201BD80: .word FUN_0201BCFC

	thumb_func_start FUN_0201BD84
FUN_0201BD84: ; 0x0201BD84
	push {r3, lr}
	sub sp, #0x18
	str r0, [sp, #0x4]
	lsl r0, r3, #0x18
	lsr r3, r0, #0x18
	ldr r0, [sp, #0x20]
	str r2, [sp, #0x0]
	add r2, sp, #0x0
	strb r1, [r2, #0x9]
	lsl r0, r0, #0x18
	strb r3, [r2, #0xa]
	lsr r0, r0, #0x18
	strb r0, [r2, #0xb]
	strb r3, [r2, #0xc]
	strb r0, [r2, #0xd]
	ldr r0, _0201BDDC ; =0x02105BB4
	lsl r1, r1, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r1
	ldrb r0, [r1, #0x2]
	strb r0, [r2, #0xe]
	ldrb r0, [r1, #0x3]
	strb r0, [r2, #0xf]
	ldrb r0, [r1, #0x4]
	strb r0, [r2, #0x10]
	ldrb r0, [r1, #0x5]
	strb r0, [r2, #0x11]
	ldrb r0, [r1, #0x6]
	strb r0, [r2, #0x12]
	ldrb r0, [r1, #0x7]
	ldr r1, [sp, #0x24]
	strb r0, [r2, #0x13]
	mov r0, #0x0
	strh r0, [r2, #0x14]
	strb r0, [r2, #0x16]
	mov r0, #0xff
	strb r0, [r2, #0x17]
	ldr r2, [sp, #0x28]
	add r0, sp, #0x0
	bl FUN_0201BE98
	add sp, #0x18
	pop {r3, pc}
	nop
_0201BDDC: .word 0x02105BB4

	thumb_func_start FUN_0201BDE0
FUN_0201BDE0: ; 0x0201BDE0
	push {r3, lr}
	sub sp, #0x18
	str r0, [sp, #0x4]
	lsl r0, r3, #0x18
	lsr r3, r0, #0x18
	ldr r0, [sp, #0x20]
	str r2, [sp, #0x0]
	add r2, sp, #0x0
	strb r1, [r2, #0x9]
	lsl r0, r0, #0x18
	strb r3, [r2, #0xa]
	lsr r0, r0, #0x18
	strb r0, [r2, #0xb]
	strb r3, [r2, #0xc]
	strb r0, [r2, #0xd]
	ldr r0, _0201BE38 ; =0x02105BB4
	lsl r1, r1, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r1
	ldrb r0, [r1, #0x2]
	strb r0, [r2, #0xe]
	ldrb r0, [r1, #0x3]
	strb r0, [r2, #0xf]
	ldrb r0, [r1, #0x4]
	ldr r1, [sp, #0x28]
	strb r0, [r2, #0x10]
	lsr r0, r1, #0x10
	strb r0, [r2, #0x11]
	lsr r0, r1, #0x8
	strb r0, [r2, #0x13]
	strb r1, [r2, #0x12]
	mov r0, #0x0
	strh r0, [r2, #0x14]
	strb r0, [r2, #0x16]
	mov r0, #0xff
	strb r0, [r2, #0x17]
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x2c]
	add r0, sp, #0x0
	bl FUN_0201BE98
	add sp, #0x18
	pop {r3, pc}
	nop
_0201BE38: .word 0x02105BB4

	thumb_func_start FUN_0201BE3C
FUN_0201BE3C: ; 0x0201BE3C
	push {r3, lr}
	sub sp, #0x18
	str r0, [sp, #0x4]
	lsl r0, r3, #0x18
	lsr r3, r0, #0x18
	ldr r0, [sp, #0x20]
	str r2, [sp, #0x0]
	add r2, sp, #0x0
	strb r1, [r2, #0x9]
	lsl r0, r0, #0x18
	strb r3, [r2, #0xa]
	lsr r0, r0, #0x18
	strb r0, [r2, #0xb]
	strb r3, [r2, #0xc]
	strb r0, [r2, #0xd]
	ldr r0, [sp, #0x2c]
	strb r0, [r2, #0xe]
	ldr r0, [sp, #0x30]
	strb r0, [r2, #0xf]
	ldr r0, _0201BE94 ; =0x02105BB4
	ldr r3, [r0, #0x0]
	lsl r0, r1, #0x3
	add r0, r3, r0
	ldrb r0, [r0, #0x4]
	ldr r1, [sp, #0x28]
	strb r0, [r2, #0x10]
	lsr r0, r1, #0x10
	strb r0, [r2, #0x11]
	lsr r0, r1, #0x8
	strb r0, [r2, #0x13]
	strb r1, [r2, #0x12]
	mov r0, #0x0
	strh r0, [r2, #0x14]
	strb r0, [r2, #0x16]
	mov r0, #0xff
	strb r0, [r2, #0x17]
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x34]
	add r0, sp, #0x0
	bl FUN_0201BE98
	add sp, #0x18
	pop {r3, pc}
	nop
_0201BE94: .word 0x02105BB4

	thumb_func_start FUN_0201BE98
FUN_0201BE98: ; 0x0201BE98
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _0201BFD0 ; =0x02105BB4
	add r6, r1, #0x0
	ldr r0, [r0, #0x0]
	add r5, r2, #0x0
	cmp r0, #0x0
	bne _0201BEAC
	mov r0, #0xff
	pop {r3-r7, pc}
_0201BEAC:
	mov r0, #0x0
	mov r1, #0x30
	bl FUN_02016998
	add r4, r0, #0x0
	mov r1, #0x1
	add r0, #0x23
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	add r0, #0x24
	strb r3, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r2, [r0, #0x0]
	mov r0, #0x7f
	bic r2, r0
	lsl r0, r6, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x7f
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x25
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x26
	strb r3, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x27
	strb r3, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x29
	strb r3, [r0, #0x0]
	add r1, r3, #0x0
_0201BEF4:
	add r0, r4, r3
	add r3, r3, #0x1
	strb r1, [r0, #0x1c]
	cmp r3, #0x7
	blt _0201BEF4
	add r3, r7, #0x0
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	bl FUN_02021F2C
	str r0, [r4, #0x0]
	ldr r0, _0201BFD4 ; =0x021C570C
	str r5, [r4, #0x18]
	mov r1, #0x0
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0201C1A8
	cmp r6, #0xff
	beq _0201BF74
	cmp r6, #0x0
	beq _0201BF74
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r2, [r0, #0x0]
	mov r1, #0x7f
	add r0, r2, #0x0
	bic r0, r1
	lsl r1, r2, #0x19
	lsr r1, r1, #0x19
	add r1, #0xff
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	mov r1, #0x7f
	and r1, r2
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x25
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r1, [r0, #0x0]
	mov r0, #0x80
	mov r2, #0x1
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x25
	strb r1, [r0, #0x0]
	ldr r0, _0201BFD8 ; =FUN_0201BFDC
	add r1, r4, #0x0
	bl FUN_0201BCC8
	add r1, r4, #0x0
	add r1, #0x28
	strb r0, [r1, #0x0]
	add r4, #0x28
	ldrb r0, [r4, #0x0]
	pop {r3-r7, pc}
_0201BF74:
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r1, [r0, #0x0]
	mov r0, #0x7f
	mov r5, #0x0
	bic r1, r0
	add r0, r4, #0x0
	add r0, #0x25
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r1, [r0, #0x0]
	mov r0, #0x80
	bic r1, r0
	add r0, r4, #0x0
	add r0, #0x25
	strb r1, [r0, #0x0]
	ldrb r0, [r7, #0x11]
	ldrb r1, [r7, #0x12]
	ldrb r2, [r7, #0x13]
	bl FUN_0201C05C
	mov r7, #0x1
	lsl r7, r7, #0xa
_0201BFA4:
	add r0, r4, #0x0
	bl FUN_0201C048
	cmp r0, #0x1
	beq _0201BFB4
	add r5, r5, #0x1
	cmp r5, r7
	blo _0201BFA4
_0201BFB4:
	cmp r6, #0xff
	beq _0201BFBE
	ldr r0, [r4, #0x4]
	bl FUN_020191D0
_0201BFBE:
	add r0, r4, #0x0
	bl FUN_0201C238
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x8
	pop {r3-r7, pc}
	nop
_0201BFD0: .word 0x02105BB4
_0201BFD4: .word 0x021C570C
_0201BFD8: .word FUN_0201BFDC

	thumb_func_start FUN_0201BFDC
FUN_0201BFDC: ; 0x0201BFDC
	push {r4, lr}
	ldr r0, _0201C044 ; =0x021C570C
	add r4, r1, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201C042
	add r0, r4, #0x0
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201C036
	mov r0, #0x0
	strh r0, [r4, #0x2a]
	ldrb r0, [r4, #0x11]
	ldrb r1, [r4, #0x12]
	ldrb r2, [r4, #0x13]
	bl FUN_0201C05C
	add r0, r4, #0x0
	bl FUN_0201C048
	cmp r0, #0x0
	beq _0201C014
	cmp r0, #0x1
	beq _0201C02C
	cmp r0, #0x3
	beq _0201C01A
	pop {r4, pc}
_0201C014:
	ldr r0, [r4, #0x4]
	bl FUN_020191D0
_0201C01A:
	ldr r2, [r4, #0x18]
	cmp r2, #0x0
	beq _0201C042
	ldrh r1, [r4, #0x2a]
	add r0, r4, #0x0
	blx r2
	add r4, #0x29
	strb r0, [r4, #0x0]
	pop {r4, pc}
_0201C02C:
	add r4, #0x28
	ldrb r0, [r4, #0x0]
	bl FUN_0201BCFC
	pop {r4, pc}
_0201C036:
	ldrh r1, [r4, #0x2a]
	ldr r2, [r4, #0x18]
	add r0, r4, #0x0
	blx r2
	add r4, #0x29
	strb r0, [r4, #0x0]
_0201C042:
	pop {r4, pc}
	.balign 4
_0201C044: .word 0x021C570C

	thumb_func_start FUN_0201C048
FUN_0201C048: ; 0x0201C048
	push {r4, lr}
	add r4, r0, #0x0
_0201C04C:
	ldrb r0, [r4, #0x9]
	add r1, r4, #0x0
	bl FUN_02002DB0
	cmp r0, #0x2
	beq _0201C04C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201C05C
FUN_0201C05C: ; 0x0201C05C
	push {r3-r7, lr}
	sub sp, #0x30
	ldr r3, _0201C0F8 ; =0x021C570C
	mov r5, #0x0
	str r5, [sp, #0x20]
	str r0, [sp, #0x24]
	str r2, [sp, #0x28]
	str r1, [sp, #0x2c]
	strh r1, [r3, #0x6]
	strh r0, [r3, #0x2]
	add r0, sp, #0x20
	strh r2, [r3, #0x4]
	str r5, [sp, #0x14]
	str r0, [sp, #0x8]
	mov r12, r0
	mov lr, r0
	str r0, [sp, #0x18]
_0201C07E:
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x8]
	ldr r0, [r0, #0x0]
	str r0, [sp, #0x1c]
_0201C08C:
	mov r0, #0x0
	str r0, [sp, #0xc]
	mov r0, lr
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0x0]
	lsl r7, r0, #0x4
_0201C09A:
	ldr r0, [sp, #0x0]
	mov r3, #0x0
	ldr r0, [r0, #0x0]
	mov r4, r12
	lsl r6, r0, #0x8
_0201C0A4:
	ldr r0, [r4, #0x0]
	add r1, r7, #0x0
	lsl r0, r0, #0xc
	orr r0, r6
	orr r1, r0
	ldr r0, [sp, #0x1c]
	add r3, r3, #0x1
	add r2, r0, #0x0
	orr r2, r1
	lsl r1, r5, #0x1
	ldr r0, _0201C0FC ; =0x021C5734
	add r5, r5, #0x1
	add r4, r4, #0x4
	strh r2, [r0, r1]
	cmp r3, #0x4
	blt _0201C0A4
	ldr r0, [sp, #0x0]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xc]
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	cmp r0, #0x4
	blt _0201C09A
	ldr r0, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x10]
	add r0, r0, #0x1
	str r0, [sp, #0x10]
	cmp r0, #0x4
	blt _0201C08C
	ldr r0, [sp, #0x8]
	add r0, r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x14]
	add r0, r0, #0x1
	str r0, [sp, #0x14]
	cmp r0, #0x4
	blt _0201C07E
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_0201C0F8: .word 0x021C570C
_0201C0FC: .word 0x021C5734

	thumb_func_start FUN_0201C100
FUN_0201C100: ; 0x0201C100
	ldrh r2, [r0, #0x0]
	lsr r2, r2, #0x8
	lsl r3, r2, #0x1
	ldr r2, _0201C1A4 ; =0x021C5734
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x0]
	ldrh r3, [r0, #0x0]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x2]
	ldrh r3, [r0, #0x2]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x4]
	ldrh r3, [r0, #0x2]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x6]
	ldrh r3, [r0, #0x4]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x8]
	ldrh r3, [r0, #0x4]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0xa]
	ldrh r3, [r0, #0x6]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0xc]
	ldrh r3, [r0, #0x6]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0xe]
	ldrh r3, [r0, #0x8]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x10]
	ldrh r3, [r0, #0x8]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x12]
	ldrh r3, [r0, #0xa]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x14]
	ldrh r3, [r0, #0xa]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x16]
	ldrh r3, [r0, #0xc]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x18]
	ldrh r3, [r0, #0xc]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x1a]
	ldrh r3, [r0, #0xe]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x1c]
	ldrh r0, [r0, #0xe]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x17
	ldrh r0, [r2, r0]
	strh r0, [r1, #0x1e]
	bx lr
	.balign 4
_0201C1A4: .word 0x021C5734

	thumb_func_start FUN_0201C1A8
FUN_0201C1A8: ; 0x0201C1A8
	mov r1, #0x0
	str r1, [r0, #0x2c]
	bx lr
	.balign 4

	thumb_func_start FUN_0201C1B0
FUN_0201C1B0: ; 0x0201C1B0
	push {r3-r5, lr}
	sub sp, #0x8
	mov r1, #0x6
	mov r0, #0x0
	lsl r1, r1, #0x8
	bl FUN_02016998
	mov r2, #0x0
	add r5, r0, #0x0
	str r2, [sp, #0x0]
	mov r0, #0xe
	mov r1, #0x5
	add r3, sp, #0x4
	bl FUN_02006BB0
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	mov r2, #0x6
	ldr r0, [r0, #0x14]
	add r1, r5, #0x0
	lsl r2, r2, #0x8
	bl MIi_CpuCopy32
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201C1EC
FUN_0201C1EC: ; 0x0201C1EC
	push {r3-r7, lr}
	sub sp, #0x18
	add r4, r0, #0x0
	ldr r0, [r4, #0x2c]
	add r7, r3, #0x0
	ldr r5, [r4, #0x4]
	cmp r0, #0x0
	bne _0201C202
	bl FUN_0201C1B0
	str r0, [r4, #0x2c]
_0201C202:
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r6, r7, #0x0
	mul r6, r0
	add r0, r5, #0x0
	ldr r4, [r4, #0x2c]
	bl FUN_0201AB0C
	sub r0, r0, #0x3
	lsl r0, r0, #0x13
	mov r1, #0x18
	lsr r2, r0, #0x10
	str r1, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	mov r2, #0x0
	str r2, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	add r1, r4, r6
	add r3, r2, #0x0
	bl FUN_02019658
	add sp, #0x18
	pop {r3-r7, pc}

	thumb_func_start FUN_0201C238
FUN_0201C238: ; 0x0201C238
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x2c]
	cmp r0, #0x0
	beq _0201C24A
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x2c]
_0201C24A:
	pop {r4, pc}

	thumb_func_start FUN_0201C24C
FUN_0201C24C: ; 0x0201C24C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0201C298 ; =0x021C5934
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201C25E
	bl ErrorHandling
_0201C25E:
	add r0, r4, #0x0
	mov r1, #0xc
	bl FUN_02016998
	ldr r1, _0201C298 ; =0x021C5934
	cmp r0, #0x0
	str r0, [r1, #0x0]
	bne _0201C272
	bl ErrorHandling
_0201C272:
	add r0, r4, #0x0
	lsl r1, r5, #0x4
	bl FUN_02016998
	ldr r1, _0201C298 ; =0x021C5934
	ldr r2, [r1, #0x0]
	str r0, [r2, #0x8]
	ldr r0, [r1, #0x0]
	mov r2, #0x0
	str r5, [r0, #0x0]
	ldr r0, [r1, #0x0]
	str r2, [r0, #0x4]
	ldr r1, [r1, #0x0]
	ldr r0, [r1, #0x8]
	ldr r1, [r1, #0x0]
	bl FUN_020AEF1C
	pop {r3-r5, pc}
	nop
_0201C298: .word 0x021C5934

	thumb_func_start FUN_0201C29C
FUN_0201C29C: ; 0x0201C29C
	push {r3, lr}
	ldr r0, _0201C2C4 ; =0x021C5934
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201C2AA
	bl ErrorHandling
_0201C2AA:
	ldr r0, _0201C2C4 ; =0x021C5934
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x8]
	bl FUN_02016A18
	ldr r0, _0201C2C4 ; =0x021C5934
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _0201C2C4 ; =0x021C5934
	mov r1, #0x0
	str r1, [r0, #0x0]
	pop {r3, pc}
	.balign 4
_0201C2C4: .word 0x021C5934

	thumb_func_start FUN_0201C2C8
FUN_0201C2C8: ; 0x0201C2C8
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _0201C308 ; =0x021C5934
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r0, #0x0
	bne _0201C2DE
	bl ErrorHandling
_0201C2DE:
	ldr r1, _0201C308 ; =0x021C5934
	ldr r0, [r1, #0x0]
	ldr r2, [r0, #0x4]
	add r2, r2, #0x1
	str r2, [r0, #0x4]
	ldr r0, [r1, #0x0]
	ldr r1, [r0, #0x4]
	ldr r0, [r0, #0x0]
	cmp r1, r0
	blo _0201C2FA
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}
_0201C2FA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl FUN_020AEE40
	pop {r3-r7, pc}
	.balign 4
_0201C308: .word 0x021C5934

	thumb_func_start FUN_0201C30C
FUN_0201C30C: ; 0x0201C30C
	push {r3, lr}
	ldr r0, _0201C324 ; =0x021C5934
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201C322
	bl FUN_020AEEB8
	ldr r0, _0201C324 ; =0x021C5934
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x4]
_0201C322:
	pop {r3, pc}
	.balign 4
_0201C324: .word 0x021C5934

	thumb_func_start FUN_0201C328
FUN_0201C328: ; 0x0201C328
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x30
	mul r1, r4
	bl FUN_02016998
	ldr r2, _0201C344 ; =FUN_0201C358
	add r1, r4, #0x0
	add r5, r0, #0x0
	bl FUN_020B4568
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4
_0201C344: .word FUN_0201C358

	thumb_func_start FUN_0201C348
FUN_0201C348: ; 0x0201C348
	ldr r3, _0201C34C ; =FUN_020B442C
	bx r3
	.balign 4
_0201C34C: .word FUN_020B442C

	thumb_func_start FUN_0201C350
FUN_0201C350: ; 0x0201C350
	ldr r3, _0201C354 ; =FUN_02016A18
	bx r3
	.balign 4
_0201C354: .word FUN_02016A18

	thumb_func_start FUN_0201C358
FUN_0201C358: ; 0x0201C358
	push {r3, lr}
	bl FUN_0201C2C8
	pop {r3, pc}

	thumb_func_start FUN_0201C360
FUN_0201C360: ; 0x0201C360
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x8
	bl FUN_02016998
	mov r1, #0x14
	add r4, r0, #0x0
	add r0, r6, #0x0
	mul r1, r5
	bl FUN_02016998
	str r0, [r4, #0x0]
	mov r6, #0x0
	str r5, [r4, #0x4]
	cmp r5, #0x0
	ble _0201C398
	add r5, r6, #0x0
_0201C386:
	ldr r0, [r4, #0x0]
	add r0, r0, r5
	bl FUN_0201C444
	ldr r0, [r4, #0x4]
	add r6, r6, #0x1
	add r5, #0x14
	cmp r6, r0
	blt _0201C386
_0201C398:
	add r0, r4, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0201C39C
FUN_0201C39C: ; 0x0201C39C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201C414
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201C3B4
FUN_0201C3B4: ; 0x0201C3B4
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r4, #0x0
	add r7, r2, #0x0
	mov r12, r1
	add r6, r3, #0x0
	add r2, r4, #0x0
	cmp r0, #0x0
	ble _0201C3E2
	ldr r5, [r5, #0x0]
	add r3, r5, #0x0
_0201C3CC:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	bne _0201C3DA
	mov r0, #0x14
	mul r0, r2
	add r4, r5, r0
	b _0201C3E2
_0201C3DA:
	add r2, r2, #0x1
	add r3, #0x14
	cmp r2, r0
	blt _0201C3CC
_0201C3E2:
	cmp r4, #0x0
	bne _0201C3EA
	mov r0, #0x0
	pop {r3-r7, pc}
_0201C3EA:
	mov r0, r12
	str r0, [r4, #0x0]
	str r7, [r4, #0x4]
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	str r6, [r4, #0x8]
	str r0, [r4, #0xc]
	mov r0, #0xff
	strb r0, [r4, #0x10]
	lsl r1, r1, #0x4
	strb r0, [r4, #0x11]
	add r0, r4, #0x0
	lsr r1, r1, #0x10
	bl FUN_0201C454
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0201C40C
FUN_0201C40C: ; 0x0201C40C
	ldr r3, _0201C410 ; =FUN_0201C444
	bx r3
	.balign 4
_0201C410: .word FUN_0201C444

	thumb_func_start FUN_0201C414
FUN_0201C414: ; 0x0201C414
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0201C434
	add r4, r6, #0x0
_0201C422:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	bl FUN_0201C444
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0x14
	cmp r6, r0
	blt _0201C422
_0201C434:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0201C438
FUN_0201C438: ; 0x0201C438
	ldr r3, _0201C440 ; =FUN_0201C454
	lsl r1, r1, #0x4
	lsr r1, r1, #0x10
	bx r3
	.balign 4
_0201C440: .word FUN_0201C454

	thumb_func_start FUN_0201C444
FUN_0201C444: ; 0x0201C444
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	str r1, [r0, #0xc]
	strb r1, [r0, #0x10]
	strb r1, [r0, #0x11]
	bx lr

	thumb_func_start FUN_0201C454
FUN_0201C454: ; 0x0201C454
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02022244
	add r2, sp, #0x0
	strb r0, [r2, #0x0]
	lsr r0, r0, #0x8
	strb r0, [r2, #0x1]
	ldrb r0, [r2, #0x0]
	add r1, sp, #0x0
	add r1, #0x2
	strb r0, [r2, #0x2]
	ldrb r0, [r2, #0x1]
	strb r0, [r2, #0x3]
	ldrb r3, [r4, #0x10]
	ldrb r0, [r2, #0x2]
	cmp r3, r0
	beq _0201C482
	add r0, r4, #0x0
	bl FUN_0201C49C
_0201C482:
	add r0, sp, #0x0
	ldrb r1, [r4, #0x11]
	ldrb r0, [r0, #0x3]
	cmp r1, r0
	beq _0201C496
	add r1, sp, #0x0
	add r0, r4, #0x0
	add r1, #0x2
	bl FUN_0201C4C8
_0201C496:
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201C49C
FUN_0201C49C: ; 0x0201C49C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0201C4F4
	ldr r3, [r5, #0x8]
	add r2, r0, #0x0
	lsl r1, r3, #0x10
	ldr r6, _0201C4C4 ; =0x7FFF0000
	mov r0, #0x0
	and r3, r6
	lsr r3, r3, #0x10
	lsr r1, r1, #0xd
	lsl r3, r3, #0x4
	bl FUN_0201C2C8
	ldrb r0, [r4, #0x0]
	strb r0, [r5, #0x10]
	pop {r4-r6, pc}
	nop
_0201C4C4: .word 0x7FFF0000

	thumb_func_start FUN_0201C4C8
FUN_0201C4C8: ; 0x0201C4C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0201C500
	ldr r3, [r5, #0xc]
	add r2, r0, #0x0
	lsl r1, r3, #0x10
	ldr r6, _0201C4F0 ; =0xFFFF0000
	mov r0, #0x1
	and r3, r6
	lsr r3, r3, #0x10
	lsr r1, r1, #0xd
	lsl r3, r3, #0x3
	bl FUN_0201C2C8
	ldrb r0, [r4, #0x1]
	strb r0, [r5, #0x11]
	pop {r4-r6, pc}
	nop
_0201C4F0: .word 0xFFFF0000

	thumb_func_start FUN_0201C4F4
FUN_0201C4F4: ; 0x0201C4F4
	ldr r3, _0201C4FC ; =FUN_0201C50C
	ldr r0, [r0, #0x4]
	ldrb r1, [r1, #0x0]
	bx r3
	.balign 4
_0201C4FC: .word FUN_0201C50C

	thumb_func_start FUN_0201C500
FUN_0201C500: ; 0x0201C500
	ldr r3, _0201C508 ; =FUN_0201C540
	ldr r0, [r0, #0x4]
	ldrb r1, [r1, #0x1]
	bx r3
	.balign 4
_0201C508: .word FUN_0201C540

	thumb_func_start FUN_0201C50C
FUN_0201C50C: ; 0x0201C50C
	push {r3-r4}
	add r2, r0, #0x0
	add r2, #0x42
	ldrh r2, [r2, #0x0]
	add r4, r0, #0x0
	add r4, #0x3c
	add r3, r4, r2
	ldrh r2, [r4, r2]
	add r3, r3, #0x4
	mul r1, r2
	add r3, r3, r1
	bne _0201C52A
	mov r0, #0x0
	pop {r3-r4}
	bx lr
_0201C52A:
	ldr r1, [r0, #0x14]
	add r2, r0, r1
	ldr r1, [r3, #0x0]
	ldr r0, [r0, #0x8]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	add r0, r1, r0
	lsl r0, r0, #0x3
	add r0, r2, r0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201C540
FUN_0201C540: ; 0x0201C540
	push {r3-r4}
	ldrh r2, [r0, #0x34]
	add r4, r0, r2
	ldrh r2, [r4, #0x6]
	add r3, r4, r2
	ldrh r2, [r4, r2]
	add r3, r3, #0x4
	mul r1, r2
	add r2, r3, r1
	bne _0201C55A
	mov r0, #0x0
	pop {r3-r4}
	bx lr
_0201C55A:
	ldr r1, [r0, #0x38]
	add r1, r0, r1
	ldrh r0, [r2, #0x0]
	lsl r0, r0, #0x3
	add r0, r1, r0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201C568
FUN_0201C568: ; 0x0201C568
	ldr r1, [r1, #0x0]
	ldr r0, [r0, #0x8]
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	lsr r1, r1, #0xd
	lsr r0, r0, #0xd
	add r0, r1, r0
	bx lr

	thumb_func_start FUN_0201C578
FUN_0201C578: ; 0x0201C578
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_0201C750
	add r0, r4, #0x0
	add r0, #0x3c
	add r1, sp, #0x0
	bl FUN_020BC2A0
	add r1, r0, #0x0
	bne _0201C598
	add sp, #0x10
	mov r0, #0x0
	pop {r4, pc}
_0201C598:
	add r0, r4, #0x0
	bl FUN_0201C568
	add sp, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201C5A4
FUN_0201C5A4: ; 0x0201C5A4
	push {r3, lr}
	ldr r0, [r1, #0x0]
	mov r1, #0x7
	lsl r1, r1, #0x1a
	and r1, r0
	lsr r1, r1, #0x1a
	cmp r1, #0x4
	bhi _0201C5DA
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0201C5C0: ; jump table (using 16-bit offset)
	.short _0201C5DA - _0201C5C0 - 2; case 0
	.short _0201C5D6 - _0201C5C0 - 2; case 1
	.short _0201C5CA - _0201C5C0 - 2; case 2
	.short _0201C5CE - _0201C5C0 - 2; case 3
	.short _0201C5D2 - _0201C5C0 - 2; case 4
_0201C5CA:
	mov r1, #0x4
	b _0201C5DE
_0201C5CE:
	mov r1, #0x2
	b _0201C5DE
_0201C5D2:
	mov r1, #0x1
	b _0201C5DE
_0201C5D6:
	mov r1, #0x1
	b _0201C5DE
_0201C5DA:
	mov r0, #0x0
	pop {r3, pc}
_0201C5DE:
	mov r3, #0x7
	lsl r3, r3, #0x14
	add r2, r0, #0x0
	and r2, r3
	lsl r3, r3, #0x3
	and r0, r3
	lsr r2, r2, #0x14
	lsr r0, r0, #0x17
	lsl r2, r2, #0x4
	lsl r0, r0, #0x4
	mul r0, r2
	bl _u32_div_f
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201C5FC
FUN_0201C5FC: ; 0x0201C5FC
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_0201C750
	add r0, r4, #0x0
	add r0, #0x3c
	add r1, sp, #0x0
	bl FUN_020BC2A0
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0201C5A4
	add sp, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201C620
FUN_0201C620: ; 0x0201C620
	ldrb r3, [r0, #0x0]
	strb r3, [r1, #0x0]
	ldrb r0, [r0, #0x1]
	strb r0, [r2, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0201C62C
FUN_0201C62C: ; 0x0201C62C
	ldrb r3, [r0, #0x2]
	strb r3, [r1, #0x0]
	ldrb r0, [r0, #0x3]
	strb r0, [r2, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0201C638
FUN_0201C638: ; 0x0201C638
	push {r4-r5}
	ldr r5, _0201C6B0 ; =0xFFFFFFF8
	ldr r4, [sp, #0xc]
	add r5, sp
	ldrb r5, [r5, #0x18]
	cmp r5, #0x3
	bhi _0201C678
	add r5, r5, r5
	add r5, pc
	ldrh r5, [r5, #0x6]
	lsl r5, r5, #0x10
	asr r5, r5, #0x10
	add pc, r5
_0201C652: ; jump table (using 16-bit offset)
	.short _0201C65A - _0201C652 - 2; case 0
	.short _0201C662 - _0201C652 - 2; case 1
	.short _0201C66A - _0201C652 - 2; case 2
	.short _0201C672 - _0201C652 - 2; case 3
_0201C65A:
	lsl r4, r4, #0x3
	add r4, r0, r4
	ldrb r4, [r4, #0x4]
	b _0201C678
_0201C662:
	lsl r4, r4, #0x3
	add r4, r0, r4
	ldrb r4, [r4, #0x5]
	b _0201C678
_0201C66A:
	lsl r4, r4, #0x3
	add r4, r0, r4
	ldrb r4, [r4, #0x6]
	b _0201C678
_0201C672:
	lsl r4, r4, #0x3
	add r4, r0, r4
	ldrb r4, [r4, #0x7]
_0201C678:
	cmp r1, #0x0
	beq _0201C682
	lsl r5, r4, #0x3
	ldrb r5, [r0, r5]
	strb r5, [r1, #0x0]
_0201C682:
	cmp r2, #0x0
	beq _0201C68E
	lsl r1, r4, #0x3
	add r1, r0, r1
	ldrb r1, [r1, #0x1]
	strb r1, [r2, #0x0]
_0201C68E:
	cmp r3, #0x0
	beq _0201C69A
	lsl r1, r4, #0x3
	add r1, r0, r1
	ldrb r1, [r1, #0x2]
	strb r1, [r3, #0x0]
_0201C69A:
	ldr r2, [sp, #0x8]
	cmp r2, #0x0
	beq _0201C6A8
	lsl r1, r4, #0x3
	add r0, r0, r1
	ldrb r0, [r0, #0x3]
	strb r0, [r2, #0x0]
_0201C6A8:
	add r0, r4, #0x0
	pop {r4-r5}
	bx lr
	nop
_0201C6B0: .word 0xFFFFFFF8

	thumb_func_start FUN_0201C6B4
FUN_0201C6B4: ; 0x0201C6B4
	mov r2, #0x0
	ldrsb r1, [r0, r2]
	cmp r1, #0x0
	beq _0201C6C4
_0201C6BC:
	add r2, r2, #0x1
	ldrsb r1, [r0, r2]
	cmp r1, #0x0
	bne _0201C6BC
_0201C6C4:
	add r0, r2, #0x0
	bx lr

	thumb_func_start FUN_0201C6C8
FUN_0201C6C8: ; 0x0201C6C8
	push {r4-r5}
	mov r4, #0x1
	mov r3, #0x0
	lsl r4, r4, #0x8
_0201C6D0:
	ldrsb r5, [r0, r3]
	strb r5, [r1, r3]
	ldrsb r5, [r0, r3]
	cmp r2, r5
	beq _0201C6DE
	cmp r5, #0x0
	bne _0201C6FE
_0201C6DE:
	mov r4, #0x0
	strb r4, [r1, r3]
	cmp r2, #0xd
	bne _0201C6F6
	add r1, r3, #0x1
	ldrsb r1, [r0, r1]
	cmp r1, #0xa
	bne _0201C6F6
	add r1, r3, #0x2
	add r0, r0, r1
	pop {r4-r5}
	bx lr
_0201C6F6:
	add r1, r3, #0x1
	add r0, r0, r1
	pop {r4-r5}
	bx lr
_0201C6FE:
	add r3, r3, #0x1
	cmp r3, r4
	blt _0201C6D0
	mov r0, #0x0
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_0201C70C
FUN_0201C70C: ; 0x0201C70C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl FUN_0201C6B4
	mov r5, #0x1
	mov r6, #0x0
	sub r3, r0, #0x1
	bmi _0201C74A
	sub r1, r6, #0x1
	mov r0, #0xa
_0201C720:
	ldrsb r2, [r4, r3]
	cmp r2, #0x30
	blt _0201C732
	cmp r2, #0x39
	bgt _0201C732
	sub r2, #0x30
	mul r2, r5
	add r6, r6, r2
	b _0201C744
_0201C732:
	cmp r3, #0x0
	bne _0201C73E
	cmp r2, #0x2d
	bne _0201C744
	mul r6, r1
	b _0201C744
_0201C73E:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_0201C744:
	mul r5, r0
	sub r3, r3, #0x1
	bpl _0201C720
_0201C74A:
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0201C750
FUN_0201C750: ; 0x0201C750
	push {r3-r5, lr}
	mov r2, #0x0
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r1, r2, #0x0
_0201C75A:
	lsl r0, r2, #0x2
	str r1, [r5, r0]
	add r0, r2, #0x1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, #0x4
	blo _0201C75A
	add r0, r4, #0x0
	bl FUN_0201C6B4
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r2, _0201C788 ; =0x00000000
	beq _0201C784
_0201C776:
	ldrsb r0, [r4, r2]
	strb r0, [r5, r2]
	add r0, r2, #0x1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, r1
	blo _0201C776
_0201C784:
	pop {r3-r5, pc}
	nop
_0201C788: .word 0x00000000

	thumb_func_start FUN_0201C78C
FUN_0201C78C: ; 0x0201C78C
	ldr r1, _0201C79C ; =0x00000121
	cmp r0, r1
	bhs _0201C796
	mov r0, #0x1
	bx lr
_0201C796:
	mov r0, #0x0
	bx lr
	nop
_0201C79C: .word 0x00000121

	thumb_func_start FUN_0201C7A0
FUN_0201C7A0: ; 0x0201C7A0
	cmp r0, r1
	blt _0201C7A6
	add r0, r1, #0x0
_0201C7A6:
	bx lr

	thumb_func_start FUN_0201C7A8
FUN_0201C7A8: ; 0x0201C7A8
	cmp r0, r1
	bgt _0201C7AE
	add r0, r1, #0x0
_0201C7AE:
	bx lr

	thumb_func_start FUN_0201C7B0
FUN_0201C7B0: ; 0x0201C7B0
	push {r3-r7, lr}
	sub sp, #0x30
	add r4, r1, #0x0
	add r1, sp, #0x24
	bl VEC_Normalize
	add r0, r4, #0x0
	add r1, sp, #0x18
	bl VEC_Normalize
	ldr r0, [sp, #0x24]
	ldr r4, [sp, #0x18]
	str r0, [sp, #0x0]
	asr r0, r0, #0x1f
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x20]
	asr r6, r4, #0x1f
	str r0, [sp, #0x8]
	asr r0, r0, #0x1f
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x2c]
	ldr r2, [sp, #0x8]
	asr r7, r0, #0x1f
	ldr r3, [sp, #0xc]
	add r1, r7, #0x0
	str r0, [sp, #0x10]
	bl _ll_mul
	str r0, [sp, #0x14]
	add r5, r1, #0x0
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl _ll_mul
	mov r2, #0x2
	ldr r3, [sp, #0x14]
	lsl r2, r2, #0xa
	add r3, r3, r2
	ldr r2, _0201C874 ; =0x00000000
	adc r5, r2
	lsl r2, r5, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	mov r2, #0x2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _0201C874 ; =0x00000000
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	add r5, r3, r0
	ldr r0, [sp, #0x10]
	add r1, r7, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl _ll_mul
	add r6, r0, #0x0
	add r4, r1, #0x0
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r6, r6, r2
	adc r4, r3
	lsl r4, r4, #0x14
	lsr r6, r6, #0xc
	orr r6, r4
	add r4, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r4, #0xc
	orr r1, r0
	sub r0, r6, r1
	cmp r5, #0x0
	bne _0201C86A
	cmp r0, #0x0
	ble _0201C862
	add sp, #0x30
	lsl r0, r2, #0x3
	pop {r3-r7, pc}
_0201C862:
	mov r0, #0x3
	add sp, #0x30
	lsl r0, r0, #0xe
	pop {r3-r7, pc}
_0201C86A:
	add r1, r5, #0x0
	bl FX_Atan2
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_0201C874: .word 0x00000000

	thumb_func_start FUN_0201C878
FUN_0201C878: ; 0x0201C878
	push {r0-r3}
	push {r4-r7, lr}
	sub sp, #0x54
	ldr r0, [sp, #0x7c]
	ldr r2, [sp, #0x80]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x94]
	ldr r1, [sp, #0x8c]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x88]
	ldr r4, [sp, #0x70]
	str r0, [sp, #0x10]
	sub r0, r2, r1
	str r0, [sp, #0x14]
	asr r0, r0, #0x1f
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x8]
	asr r0, r0, #0x1f
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x74]
	sub r3, r0, r2
	sub r0, r1, r0
	str r3, [sp, #0x20]
	asr r3, r3, #0x1f
	str r3, [sp, #0x24]
	ldr r3, [sp, #0xc]
	str r0, [sp, #0x2c]
	asr r0, r0, #0x1f
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x10]
	asr r3, r3, #0x1f
	str r3, [sp, #0x28]
	asr r0, r0, #0x1f
	ldr r3, [sp, #0x68]
	str r0, [sp, #0x34]
	asr r0, r4, #0x1f
	str r0, [sp, #0x38]
	sub r2, r2, r3
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x1c]
	asr r3, r2, #0x1f
	bl _ll_mul
	add r7, r0, #0x0
	add r6, r1, #0x0
	ldr r3, [sp, #0x68]
	ldr r2, [sp, #0x74]
	ldr r0, [sp, #0x10]
	sub r2, r3, r2
	ldr r1, [sp, #0x34]
	asr r3, r2, #0x1f
	bl _ll_mul
	add r5, r1, #0x0
	str r0, [sp, #0x3c]
	ldr r1, [sp, #0x38]
	ldr r2, [sp, #0x20]
	ldr r3, [sp, #0x24]
	add r0, r4, #0x0
	bl _ll_mul
	mov r2, #0x2
	str r0, [sp, #0x4c]
	add r0, r1, #0x0
	mov r1, #0x0
	lsl r2, r2, #0xa
	add r3, r7, r2
	adc r6, r1
	lsl r2, r6, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	mov r2, #0x2
	ldr r6, [sp, #0x3c]
	lsl r2, r2, #0xa
	add r2, r6, r2
	adc r5, r1
	mov r6, #0x2
	lsl r5, r5, #0x14
	lsr r2, r2, #0xc
	orr r2, r5
	ldr r5, [sp, #0x4c]
	lsl r6, r6, #0xa
	add r5, r5, r6
	adc r0, r1
	lsl r0, r0, #0x14
	lsr r1, r5, #0xc
	orr r1, r0
	add r0, r2, r1
	add r0, r3, r0
	str r0, [sp, #0x4]
	ldr r3, [sp, #0x8c]
	ldr r2, [sp, #0x68]
	ldr r0, [sp, #0x10]
	sub r2, r3, r2
	ldr r1, [sp, #0x34]
	asr r3, r2, #0x1f
	bl _ll_mul
	add r7, r0, #0x0
	add r6, r1, #0x0
	ldr r3, [sp, #0x68]
	ldr r2, [sp, #0x80]
	ldr r0, [sp, #0xc]
	sub r2, r3, r2
	ldr r1, [sp, #0x28]
	asr r3, r2, #0x1f
	bl _ll_mul
	str r0, [sp, #0x40]
	add r5, r1, #0x0
	ldr r1, [sp, #0x38]
	ldr r2, [sp, #0x14]
	ldr r3, [sp, #0x18]
	add r0, r4, #0x0
	bl _ll_mul
	mov r2, #0x2
	str r0, [sp, #0x50]
	add r0, r1, #0x0
	mov r1, #0x0
	lsl r2, r2, #0xa
	add r3, r7, r2
	adc r6, r1
	lsl r2, r6, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	mov r2, #0x2
	ldr r6, [sp, #0x40]
	lsl r2, r2, #0xa
	add r2, r6, r2
	adc r5, r1
	mov r6, #0x2
	lsl r5, r5, #0x14
	lsr r2, r2, #0xc
	orr r2, r5
	ldr r5, [sp, #0x50]
	lsl r6, r6, #0xa
	add r5, r5, r6
	adc r0, r1
	lsl r0, r0, #0x14
	lsr r1, r5, #0xc
	orr r1, r0
	add r0, r2, r1
	add r0, r3, r0
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x74]
	ldr r2, [sp, #0x68]
	ldr r0, [sp, #0xc]
	sub r2, r3, r2
	ldr r1, [sp, #0x28]
	asr r3, r2, #0x1f
	bl _ll_mul
	add r7, r0, #0x0
	add r6, r1, #0x0
	ldr r3, [sp, #0x68]
	ldr r2, [sp, #0x8c]
	ldr r0, [sp, #0x8]
	sub r2, r3, r2
	ldr r1, [sp, #0x1c]
	asr r3, r2, #0x1f
	bl _ll_mul
	add r5, r1, #0x0
	str r0, [sp, #0x44]
	ldr r1, [sp, #0x38]
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	add r0, r4, #0x0
	bl _ll_mul
	mov r3, #0x2
	mov r2, #0x0
	lsl r3, r3, #0xa
	add r4, r7, r3
	adc r6, r2
	lsl r3, r6, #0x14
	lsr r4, r4, #0xc
	orr r4, r3
	mov r3, #0x2
	ldr r6, [sp, #0x44]
	lsl r3, r3, #0xa
	add r3, r6, r3
	adc r5, r2
	lsl r5, r5, #0x14
	lsr r3, r3, #0xc
	orr r3, r5
	mov r5, #0x2
	lsl r5, r5, #0xa
	add r5, r0, r5
	adc r1, r2
	lsl r0, r1, #0x14
	lsr r1, r5, #0xc
	orr r1, r0
	add r0, r3, r1
	add r6, r4, r0
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x34]
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	bl _ll_mul
	add r7, r0, #0x0
	add r5, r1, #0x0
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x20]
	ldr r3, [sp, #0x24]
	bl _ll_mul
	str r0, [sp, #0x48]
	add r4, r1, #0x0
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x14]
	ldr r3, [sp, #0x18]
	bl _ll_mul
	mov r12, r0
	mov r0, #0x2
	add r2, r1, #0x0
	mov r1, #0x0
	lsl r0, r0, #0xa
	add r0, r7, r0
	adc r5, r1
	lsl r3, r5, #0x14
	lsr r0, r0, #0xc
	orr r0, r3
	mov r3, #0x2
	ldr r5, [sp, #0x48]
	lsl r3, r3, #0xa
	add r3, r5, r3
	adc r4, r1
	lsl r4, r4, #0x14
	lsr r3, r3, #0xc
	orr r3, r4
	mov r4, #0x2
	lsl r4, r4, #0xa
	mov r5, r12
	add r4, r5, r4
	adc r2, r1
	lsl r2, r2, #0x14
	lsr r4, r4, #0xc
	orr r4, r2
	add r2, r3, r4
	add r0, r0, r2
	bpl _0201CA72
	add sp, #0x54
	add r0, r1, #0x0
	pop {r4-r7}
	pop {r3}
	add sp, #0x10
	bx r3
_0201CA72:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bge _0201CA84
	add sp, #0x54
	add r0, r1, #0x0
	pop {r4-r7}
	pop {r3}
	add sp, #0x10
	bx r3
_0201CA84:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bge _0201CA96
	add sp, #0x54
	add r0, r1, #0x0
	pop {r4-r7}
	pop {r3}
	add sp, #0x10
	bx r3
_0201CA96:
	cmp r6, #0x0
	blt _0201CA9C
	mov r1, #0x1
_0201CA9C:
	add r0, r1, #0x0
	add sp, #0x54
	pop {r4-r7}
	pop {r3}
	add sp, #0x10
	bx r3

	thumb_func_start FUN_0201CAA8
FUN_0201CAA8: ; 0x0201CAA8
	push {r4-r5, lr}
	sub sp, #0x24
	add r4, r1, #0x0
	ldr r1, [r4, #0x0]
	ldr r3, _0201CB1C ; =0x020FFA38
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	asr r1, r1, #0x4
	lsl r2, r1, #0x1
	lsl r1, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r5, r0, #0x0
	bl MTX_RotX33_
	ldr r0, [r4, #0x4]
	ldr r3, _0201CB1C ; =0x020FFA38
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #0x4
	lsl r2, r0, #0x1
	lsl r1, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0x0
	bl MTX_RotY33_
	add r0, r5, #0x0
	add r1, sp, #0x0
	add r2, r5, #0x0
	bl MTX_Concat33
	ldr r0, [r4, #0x8]
	ldr r3, _0201CB1C ; =0x020FFA38
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #0x4
	lsl r2, r0, #0x1
	lsl r1, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0x0
	bl MTX_RotZ33_
	add r0, r5, #0x0
	add r1, sp, #0x0
	add r2, r5, #0x0
	bl MTX_Concat33
	add sp, #0x24
	pop {r4-r5, pc}
	nop
_0201CB1C: .word 0x020FFA38

	thumb_func_start FUN_0201CB20
FUN_0201CB20: ; 0x0201CB20
	push {r4-r7, lr}
	sub sp, #0x24
	add r6, r1, #0x0
	add r5, r2, #0x0
	lsl r1, r6, #0x2
	ldr r2, _0201CB78 ; =0x020EDF50
	add r6, #0x5a
	add r4, r3, #0x0
	lsl r3, r6, #0x2
	ldr r1, [r2, r1]
	ldr r2, [r2, r3]
	add r7, r0, #0x0
	bl MTX_RotX33_
	lsl r1, r5, #0x2
	ldr r3, _0201CB78 ; =0x020EDF50
	add r5, #0x5a
	lsl r2, r5, #0x2
	ldr r1, [r3, r1]
	ldr r2, [r3, r2]
	add r0, sp, #0x0
	bl MTX_RotY33_
	add r0, r7, #0x0
	add r1, sp, #0x0
	add r2, r7, #0x0
	bl MTX_Concat33
	lsl r1, r4, #0x2
	ldr r3, _0201CB78 ; =0x020EDF50
	add r4, #0x5a
	lsl r2, r4, #0x2
	ldr r1, [r3, r1]
	ldr r2, [r3, r2]
	add r0, sp, #0x0
	bl MTX_RotZ33_
	add r0, r7, #0x0
	add r1, sp, #0x0
	add r2, r7, #0x0
	bl MTX_Concat33
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_0201CB78: .word 0x020EDF50

	thumb_func_start FUN_0201CB7C
FUN_0201CB7C: ; 0x0201CB7C
	push {r3-r7, lr}
	asr r0, r0, #0x4
	add r7, r2, #0x0
	lsl r2, r0, #0x1
	add r6, r1, #0x0
	lsl r0, r2, #0x1
	ldr r1, _0201CBE8 ; =0x020FFA38
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r0, [r1, r0]
	ldrsh r1, [r1, r2]
	add r5, r3, #0x0
	ldr r4, [sp, #0x18]
	bl FX_Div
	add r2, r0, #0x0
	asr r1, r6, #0x1f
	add r0, r6, #0x0
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r6, #0x2
	mov r2, #0x0
	lsl r6, r6, #0xa
	add r0, r0, r6
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r3, r0, #0x1f
	lsr r1, r0, #0x13
	lsl r3, r3, #0xd
	orr r3, r1
	lsl r0, r0, #0xd
	add r0, r0, r6
	adc r3, r2
	lsl r1, r3, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r1, r0, #0x1f
	asr r3, r7, #0x1f
	add r2, r7, #0x0
	str r0, [r4, #0x0]
	bl _ll_mul
	mov r3, #0x0
	add r2, r6, #0x0
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	str r1, [r5, #0x0]
	pop {r3-r7, pc}
	.balign 4
_0201CBE8: .word 0x020FFA38

	thumb_func_start FUN_0201CBEC
FUN_0201CBEC: ; 0x0201CBEC
	push {r3, lr}
	sub r0, r0, r2
	sub r2, r1, r3
	add r1, r0, #0x0
	mul r1, r0
	add r0, r2, #0x0
	mul r0, r2
	add r0, r1, r0
	lsl r0, r0, #0xc
	bl FX_Sqrt
	asr r0, r0, #0xc
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201CC08
FUN_0201CC08: ; 0x0201CC08
	push {r3, lr}
	ldr r0, _0201CC20 ; =0x021C5978
	ldrh r0, [r0, #0x1a]
	cmp r0, #0x0
	beq _0201CC16
	bl ErrorHandling
_0201CC16:
	ldr r0, _0201CC20 ; =0x021C5978
	mov r1, #0x0
	strh r1, [r0, #0x18]
	strh r1, [r0, #0x1a]
	pop {r3, pc}
	.balign 4
_0201CC20: .word 0x021C5978

	thumb_func_start FUN_0201CC24
FUN_0201CC24: ; 0x0201CC24
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldr r0, _0201CC74 ; =0x021C5978
	ldrh r0, [r0, #0x1a]
	cmp r0, #0x0
	beq _0201CC36
	bl ErrorHandling
_0201CC36:
	cmp r4, #0x5
	bhs _0201CC3E
	cmp r4, #0x0
	bne _0201CC44
_0201CC3E:
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_0201CC44:
	ldr r0, _0201CC74 ; =0x021C5978
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0201CC52
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_0201CC52:
	add r0, r4, #0x0
	bl FUN_0201CE2C
	cmp r0, #0x1
	bne _0201CC70
	mov r2, #0x0
	str r2, [sp, #0x0]
	lsl r0, r4, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x2
	mov r1, #0x1
	add r3, r2, #0x0
	bl FUN_0201CC78
	mov r0, #0x1
_0201CC70:
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_0201CC74: .word 0x021C5978

	thumb_func_start FUN_0201CC78
FUN_0201CC78: ; 0x0201CC78
	push {r4, lr}
	ldr r4, _0201CC9C ; =0x021C5978
	strh r0, [r4, #0x18]
	ldr r0, _0201CCA0 ; =0x021C4918
	strb r1, [r0, #0x4]
	ldr r0, _0201CCA4 ; =0x021C5938
	ldr r1, [sp, #0xc]
	str r2, [r0, #0x0]
	str r3, [r0, #0x4]
	str r1, [r0, #0x8]
	ldr r1, [sp, #0x8]
	str r1, [r0, #0x54]
	ldr r0, _0201CCA8 ; =0x021C5944
	mov r1, #0x9
	bl FUN_0201CCAC
	pop {r4, pc}
	nop
_0201CC9C: .word 0x021C5978
_0201CCA0: .word 0x021C4918
_0201CCA4: .word 0x021C5938
_0201CCA8: .word 0x021C5944

	thumb_func_start FUN_0201CCAC
FUN_0201CCAC: ; 0x0201CCAC
	mov r3, #0x0
	cmp r1, #0x0
	ble _0201CCBE
	add r2, r3, #0x0
_0201CCB4:
	add r3, r3, #0x1
	strh r2, [r0, #0x4]
	add r0, #0x8
	cmp r3, r1
	blt _0201CCB4
_0201CCBE:
	bx lr

	thumb_func_start FUN_0201CCC0
FUN_0201CCC0: ; 0x0201CCC0
	push {r4-r6, lr}
	ldr r0, _0201CD00 ; =0x021C5978
	mov r5, #0x0
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	bne _0201CCD0
	mov r0, #0x1
	pop {r4-r6, pc}
_0201CCD0:
	mov r4, #0x4
	add r6, r4, #0x0
_0201CCD4:
	bl TP_RequestAutoSamplingStopAsync
	add r0, r4, #0x0
	bl TP_WaitBusy
	add r0, r6, #0x0
	bl TP_CheckError
	cmp r0, #0x0
	beq _0201CCEA
	add r5, r5, #0x1
_0201CCEA:
	cmp r0, #0x0
	beq _0201CCF2
	cmp r5, #0x5
	bls _0201CCD4
_0201CCF2:
	cmp r5, #0x5
	bls _0201CCFA
	mov r0, #0x2
	pop {r4-r6, pc}
_0201CCFA:
	mov r0, #0x1
	pop {r4-r6, pc}
	nop
_0201CD00: .word 0x021C5978

	thumb_func_start FUN_0201CD04
FUN_0201CD04: ; 0x0201CD04
	push {r4, lr}
	sub sp, #0x8
	ldr r0, _0201CD34 ; =0x021C5978
	ldrh r0, [r0, #0x1a]
	cmp r0, #0x0
	beq _0201CD14
	bl ErrorHandling
_0201CD14:
	bl FUN_0201CCC0
	add r4, r0, #0x0
	cmp r4, #0x1
	bne _0201CD2E
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	str r0, [sp, #0x4]
	bl FUN_0201CC78
_0201CD2E:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_0201CD34: .word 0x021C5978

	thumb_func_start FUN_0201CD38
FUN_0201CD38: ; 0x0201CD38
	push {r3-r7, lr}
	add r4, r0, #0x0
	ldr r0, _0201CD8C ; =0x021C5978
	add r6, r1, #0x0
	ldrh r0, [r0, #0x1a]
	add r7, r2, #0x0
	mov r5, #0x3
	cmp r0, #0x0
	beq _0201CD4E
	bl ErrorHandling
_0201CD4E:
	ldr r0, _0201CD8C ; =0x021C5978
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0201CD88
	bl TP_GetLatestIndexInAuto
	add r5, r0, #0x0
	ldr r0, _0201CD90 ; =0x021C5944
	mov r1, #0x9
	bl FUN_0201CD94
	cmp r4, #0x0
	beq _0201CD70
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0201CFD0
_0201CD70:
	ldr r0, _0201CD8C ; =0x021C5978
	ldrh r0, [r0, #0x18]
	cmp r0, #0x1
	bne _0201CD86
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl FUN_0201CE70
	add r5, r0, #0x0
	b _0201CD88
_0201CD86:
	mov r5, #0x1
_0201CD88:
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4
_0201CD8C: .word 0x021C5978
_0201CD90: .word 0x021C5944

	thumb_func_start FUN_0201CD94
FUN_0201CD94: ; 0x0201CD94
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r7, #0x0
	str r1, [sp, #0x0]
	add r0, r1, #0x0
	beq _0201CDCA
	add r4, r5, #0x0
	add r6, sp, #0x4
_0201CDA6:
	add r0, sp, #0x4
	add r1, r5, #0x0
	bl TP_GetCalibratedPoint
	ldrh r0, [r6, #0x0]
	add r7, r7, #0x1
	add r5, #0x8
	strh r0, [r4, #0x0]
	ldrh r0, [r6, #0x2]
	strh r0, [r4, #0x2]
	ldrh r0, [r6, #0x4]
	strh r0, [r4, #0x4]
	ldrh r0, [r6, #0x6]
	strh r0, [r4, #0x6]
	ldr r0, [sp, #0x0]
	add r4, #0x8
	cmp r7, r0
	blo _0201CDA6
_0201CDCA:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0201CDD0
FUN_0201CDD0: ; 0x0201CDD0
	push {r3, lr}
	ldr r0, _0201CDFC ; =0x021C5978
	ldrh r1, [r0, #0x1a]
	cmp r1, #0x0
	beq _0201CDF8
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0201CDF8
	ldr r0, _0201CE00 ; =0x021C5938
	ldr r0, [r0, #0x8]
	lsr r0, r0, #0x1
	bl FUN_0201CE2C
	cmp r0, #0x1
	beq _0201CDF2
	bl ErrorHandling
_0201CDF2:
	ldr r0, _0201CDFC ; =0x021C5978
	mov r1, #0x0
	strh r1, [r0, #0x1a]
_0201CDF8:
	pop {r3, pc}
	nop
_0201CDFC: .word 0x021C5978
_0201CE00: .word 0x021C5938

	thumb_func_start FUN_0201CE04
FUN_0201CE04: ; 0x0201CE04
	push {r3, lr}
	ldr r0, _0201CE28 ; =0x021C5978
	ldrh r1, [r0, #0x1a]
	cmp r1, #0x1
	beq _0201CE26
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0201CE26
	bl FUN_0201CCC0
	cmp r0, #0x1
	beq _0201CE20
	bl ErrorHandling
_0201CE20:
	ldr r0, _0201CE28 ; =0x021C5978
	mov r1, #0x1
	strh r1, [r0, #0x1a]
_0201CE26:
	pop {r3, pc}
	.balign 4
_0201CE28: .word 0x021C5978

	thumb_func_start FUN_0201CE2C
FUN_0201CE2C: ; 0x0201CE2C
	push {r3-r7, lr}
	mov r5, #0x0
	lsl r0, r0, #0x10
	ldr r7, _0201CE6C ; =0x021C5944
	add r6, r5, #0x0
	lsr r4, r0, #0x10
_0201CE38:
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	mov r3, #0x9
	bl TP_RequestAutoSamplingStartAsync
	mov r0, #0x2
	bl TP_WaitBusy
	mov r0, #0x2
	bl TP_CheckError
	cmp r0, #0x0
	beq _0201CE56
	add r5, r5, #0x1
_0201CE56:
	cmp r0, #0x0
	beq _0201CE5E
	cmp r5, #0x5
	ble _0201CE38
_0201CE5E:
	cmp r5, #0x5
	ble _0201CE66
	mov r0, #0x2
	pop {r3-r7, pc}
_0201CE66:
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_0201CE6C: .word 0x021C5944

	thumb_func_start FUN_0201CE70
FUN_0201CE70: ; 0x0201CE70
	push {r3, lr}
	cmp r0, #0x5
	bhi _0201CE9A
	add r3, r0, r0
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0201CE82: ; jump table (using 16-bit offset)
	.short _0201CE9A - _0201CE82 - 2; case 0
	.short _0201CE8E - _0201CE82 - 2; case 1
	.short _0201CE9A - _0201CE82 - 2; case 2
	.short _0201CE8E - _0201CE82 - 2; case 3
	.short _0201CE94 - _0201CE82 - 2; case 4
	.short _0201CE94 - _0201CE82 - 2; case 5
_0201CE8E:
	bl FUN_0201CEA0
	pop {r3, pc}
_0201CE94:
	bl FUN_0201CF58
	pop {r3, pc}
_0201CE9A:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201CEA0
FUN_0201CEA0: ; 0x0201CEA0
	push {r3-r7, lr}
	sub sp, #0x8
	ldr r5, _0201CF50 ; =0x021C5938
	str r1, [sp, #0x4]
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x0]
	add r7, r2, #0x0
	mov r4, #0x0
	cmp r1, #0x0
	bls _0201CF46
_0201CEB4:
	ldr r0, [sp, #0x4]
	sub r0, r0, r1
	add r0, r4, r0
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	bpl _0201CEC8
	add r0, #0x9
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
_0201CEC8:
	lsl r1, r0, #0x3
	ldr r0, _0201CF54 ; =0x021C5938
	add r1, r0, r1
	ldrh r0, [r1, #0x10]
	cmp r0, #0x1
	bne _0201CF3E
	ldrh r0, [r1, #0x12]
	cmp r0, #0x0
	bne _0201CF3E
	ldr r2, [r5, #0x54]
	ldr r0, [r5, #0x0]
	lsl r2, r2, #0x3
	add r2, r0, r2
	add r0, r2, #0x0
	sub r0, #0x8
	ldrh r3, [r1, #0xc]
	ldrh r0, [r0, #0x0]
	cmp r0, r3
	blt _0201CEF2
	sub r3, r0, r3
	b _0201CEF4
_0201CEF2:
	sub r3, r3, r0
_0201CEF4:
	sub r6, r2, #0x6
	ldrh r0, [r1, #0xe]
	ldrh r6, [r6, #0x0]
	cmp r6, r0
	blt _0201CF02
	sub r0, r6, r0
	b _0201CF04
_0201CF02:
	sub r0, r0, r6
_0201CF04:
	cmp r3, r7
	bhs _0201CF0C
	cmp r0, r7
	blo _0201CF3E
_0201CF0C:
	ldrh r0, [r1, #0xc]
	strh r0, [r2, #0x0]
	ldrh r0, [r1, #0xe]
	strh r0, [r2, #0x2]
	ldrh r0, [r1, #0x10]
	strh r0, [r2, #0x4]
	ldrh r0, [r1, #0x12]
	strh r0, [r2, #0x6]
	ldr r0, [r5, #0x54]
	add r0, r0, #0x1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x4]
	cmp r0, r1
	blo _0201CF3E
	ldr r2, [sp, #0x0]
	cmp r2, #0x1
	bne _0201CF36
	bl _u32_div_f
	str r1, [r5, #0x54]
	b _0201CF3E
_0201CF36:
	mov r0, #0x0
	add sp, #0x8
	mvn r0, r0
	pop {r3-r7, pc}
_0201CF3E:
	ldr r1, [r5, #0x8]
	add r4, r4, #0x1
	cmp r4, r1
	blo _0201CEB4
_0201CF46:
	ldr r0, _0201CF50 ; =0x021C5938
	ldr r0, [r0, #0x54]
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0201CF50: .word 0x021C5938
_0201CF54: .word 0x021C5938

	thumb_func_start FUN_0201CF58
FUN_0201CF58: ; 0x0201CF58
	push {r3-r7, lr}
	ldr r5, _0201CFC8 ; =0x021C5938
	str r1, [sp, #0x0]
	ldr r1, [r5, #0x8]
	add r7, r0, #0x0
	mov r4, #0x0
	cmp r1, #0x0
	bls _0201CFC0
_0201CF68:
	ldr r0, [sp, #0x0]
	sub r0, r0, r1
	add r0, r4, r0
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	asr r1, r0, #0x10
	bpl _0201CF7C
	add r1, #0x9
	lsl r0, r1, #0x10
	asr r1, r0, #0x10
_0201CF7C:
	ldr r0, [r5, #0x54]
	lsl r1, r1, #0x3
	lsl r3, r0, #0x3
	ldr r0, _0201CFCC ; =0x021C5938
	ldr r6, [r5, #0x0]
	add r2, r0, r1
	ldrh r0, [r2, #0xc]
	add r1, r6, r3
	strh r0, [r6, r3]
	ldrh r0, [r2, #0xe]
	strh r0, [r1, #0x2]
	ldrh r0, [r2, #0x10]
	strh r0, [r1, #0x4]
	ldrh r0, [r2, #0x12]
	strh r0, [r1, #0x6]
	ldr r0, [r5, #0x54]
	add r0, r0, #0x1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x4]
	cmp r0, r1
	blo _0201CFB8
	cmp r7, #0x4
	bne _0201CFB2
	bl _u32_div_f
	str r1, [r5, #0x54]
	b _0201CFB8
_0201CFB2:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0201CFB8:
	ldr r1, [r5, #0x8]
	add r4, r4, #0x1
	cmp r4, r1
	blo _0201CF68
_0201CFC0:
	ldr r0, _0201CFC8 ; =0x021C5938
	ldr r0, [r0, #0x54]
	pop {r3-r7, pc}
	nop
_0201CFC8: .word 0x021C5938
_0201CFCC: .word 0x021C5938

	thumb_func_start FUN_0201CFD0
FUN_0201CFD0: ; 0x0201CFD0
	push {r4-r7}
	mov r2, #0x0
	strh r2, [r0, #0x0]
	add r3, r0, #0x0
	add r6, r2, #0x0
_0201CFDA:
	strh r6, [r3, #0x8]
	strh r6, [r3, #0x6]
	strh r6, [r3, #0x2]
	strh r6, [r3, #0x4]
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, #0x8
	blt _0201CFDA
	ldr r2, _0201D038 ; =0x021C5938
	ldr r3, [r2, #0x8]
	cmp r3, #0x0
	bls _0201D034
	ldr r4, _0201D03C ; =0x021C5938
_0201CFF4:
	sub r3, r1, r3
	add r3, r6, r3
	add r3, r3, #0x1
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	bpl _0201D006
	add r3, #0x9
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
_0201D006:
	lsl r3, r3, #0x3
	add r5, r4, r3
	ldrh r3, [r5, #0x12]
	cmp r3, #0x0
	bne _0201D02C
	ldrh r3, [r0, #0x0]
	ldrh r7, [r5, #0xc]
	lsl r3, r3, #0x3
	add r3, r0, r3
	strh r7, [r3, #0x2]
	ldrh r7, [r5, #0xe]
	strh r7, [r3, #0x4]
	ldrh r7, [r5, #0x10]
	strh r7, [r3, #0x6]
	ldrh r5, [r5, #0x12]
	strh r5, [r3, #0x8]
	ldrh r3, [r0, #0x0]
	add r3, r3, #0x1
	strh r3, [r0, #0x0]
_0201D02C:
	ldr r3, [r2, #0x8]
	add r6, r6, #0x1
	cmp r6, r3
	blo _0201CFF4
_0201D034:
	pop {r4-r7}
	bx lr
	.balign 4
_0201D038: .word 0x021C5938
_0201D03C: .word 0x021C5938

	thumb_func_start FUN_0201D040
FUN_0201D040: ; 0x0201D040
	ldr r1, _0201D054 ; =0x04001000
	ldr r2, [r1, #0x0]
	ldr r1, _0201D058 ; =0x00300010
	lsl r3, r1, #0x16
	ldr r3, [r3, #0x0]
	and r2, r1
	and r1, r3
	ldr r3, _0201D05C ; =FUN_0201D060
	bx r3
	nop
_0201D054: .word 0x04001000
_0201D058: .word 0x00300010
_0201D05C: .word FUN_0201D060

	thumb_func_start FUN_0201D060
FUN_0201D060: ; 0x0201D060
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, _0201D120 ; =0x021C5994
	str r1, [sp, #0x0]
	ldr r0, [r0, #0x0]
	str r2, [sp, #0x4]
	cmp r0, #0x0
	bne _0201D11A
	ldr r0, [r5, #0xc]
	mov r1, #0x3c
	bl FUN_02016998
	add r1, r0, #0x0
	ldr r0, _0201D120 ; =0x021C5994
	mov r2, #0x3c
	str r1, [r0, #0x0]
	mov r0, #0x0
	bl MIi_CpuClear32
	ldr r1, _0201D120 ; =0x021C5994
	ldr r2, [r5, #0x0]
	ldr r0, [r1, #0x0]
	str r2, [r0, #0x4]
	ldr r1, [r1, #0x0]
	ldr r0, [r5, #0xc]
	ldr r2, [r1, #0x4]
	mov r1, #0x54
	mul r1, r2
	bl FUN_02016998
	ldr r7, _0201D120 ; =0x021C5994
	mov r6, #0x0
	ldr r1, [r7, #0x0]
	str r0, [r1, #0x0]
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	ble _0201D0C2
	add r4, r6, #0x0
_0201D0AE:
	ldr r0, [r7, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	bl FUN_0201D690
	ldr r0, [r5, #0x0]
	add r6, r6, #0x1
	add r4, #0x54
	cmp r6, r0
	blt _0201D0AE
_0201D0C2:
	ldr r0, [sp, #0x0]
	bl FUN_0201DED0
	ldr r1, _0201D120 ; =0x021C5994
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x2c]
	ldr r0, [sp, #0x4]
	bl FUN_0201DED0
	ldr r2, _0201D120 ; =0x021C5994
	mov r3, #0x1
	ldr r1, [r2, #0x0]
	lsl r3, r3, #0x1a
	str r0, [r1, #0x30]
	ldr r0, [r3, #0x0]
	ldr r1, _0201D124 ; =0xFFCFFFEF
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	and r4, r1
	orr r0, r4
	str r0, [r3, #0x0]
	ldr r3, _0201D128 ; =0x04001000
	ldr r0, [r3, #0x0]
	and r1, r0
	ldr r0, [sp, #0x4]
	orr r0, r1
	str r0, [r3, #0x0]
	ldr r1, [r2, #0x0]
	ldr r0, [r5, #0x4]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	ldr r1, _0201D120 ; =0x021C5994
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r0, [r5, #0x8]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	add r1, r0, #0x0
	ldr r2, [r5, #0xc]
	add r0, r4, #0x0
	bl FUN_0201DC58
_0201D11A:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0201D120: .word 0x021C5994
_0201D124: .word 0xFFCFFFEF
_0201D128: .word 0x04001000

	thumb_func_start FUN_0201D12C
FUN_0201D12C: ; 0x0201D12C
	push {r3, lr}
	ldr r0, _0201D164 ; =0x021C5994
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201D162
	ldr r0, [r0, #0x34]
	bl FUN_0201DCC0
	ldr r0, _0201D164 ; =0x021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_0201DCC0
	bl FUN_0201D374
	ldr r0, _0201D164 ; =0x021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _0201D164 ; =0x021C5994
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _0201D164 ; =0x021C5994
	mov r1, #0x0
	str r1, [r0, #0x0]
_0201D162:
	pop {r3, pc}
	.balign 4
_0201D164: .word 0x021C5994

	thumb_func_start FUN_0201D168
FUN_0201D168: ; 0x0201D168
	push {r3, lr}
	ldr r0, _0201D190 ; =0x021C5994
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	str r2, [r1, #0xc]
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x10]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_0201DD00
	ldr r0, _0201D190 ; =0x021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_0201DD00
	bl FUN_0201DAE8
	pop {r3, pc}
	nop
_0201D190: .word 0x021C5994

	thumb_func_start FUN_0201D194
FUN_0201D194: ; 0x0201D194
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r3, r1, #0x0
	cmp r2, #0x1
	add r0, sp, #0x4
	bne _0201D1CA
	str r0, [sp, #0x0]
	ldr r0, _0201D1F4 ; =0x021C5994
	add r2, r3, #0x0
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x1c]
	add r3, sp, #0x8
	bl FUN_0201DFF0
	ldr r3, [sp, #0x4]
	cmp r3, #0x0
	ble _0201D1F0
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldr r1, [sp, #0x8]
	mov r0, #0x1
	bl FUN_0201D948
	add sp, #0xc
	pop {r3-r4, pc}
_0201D1CA:
	str r0, [sp, #0x0]
	ldr r0, _0201D1F4 ; =0x021C5994
	add r2, r3, #0x0
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x20]
	add r3, sp, #0x8
	bl FUN_0201DFF0
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0201D1F0
	str r0, [sp, #0x0]
	mov r1, #0x0
	ldr r2, [sp, #0x8]
	mov r0, #0x2
	add r3, r1, #0x0
	bl FUN_0201D948
_0201D1F0:
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4
_0201D1F4: .word 0x021C5994

	thumb_func_start FUN_0201D1F8
FUN_0201D1F8: ; 0x0201D1F8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x8]
	bl FUN_0201D2AC
	cmp r0, #0x1
	bne _0201D20A
	bl ErrorHandling
_0201D20A:
	bl FUN_0201DAAC
	add r4, r0, #0x0
	bne _0201D21A
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D21A:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201D6B4
	cmp r0, #0x0
	bne _0201D22A
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D22A:
	add r0, r4, #0x0
	bl FUN_0201D724
	cmp r0, #0x0
	bne _0201D23E
	ldr r0, [r4, #0xc]
	bl FUN_0201D324
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D23E:
	ldr r0, _0201D24C ; =0x021C5994
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x8]
	add r0, r0, #0x1
	str r0, [r1, #0x8]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0201D24C: .word 0x021C5994

	thumb_func_start FUN_0201D250
FUN_0201D250: ; 0x0201D250
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x8]
	bl FUN_0201D2AC
	cmp r0, #0x1
	bne _0201D262
	bl ErrorHandling
_0201D262:
	bl FUN_0201DAAC
	add r4, r0, #0x0
	bne _0201D272
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D272:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201D6B4
	cmp r0, #0x0
	bne _0201D282
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D282:
	mov r0, #0x1
	str r0, [r4, #0x40]
	add r0, r4, #0x0
	bl FUN_0201D724
	cmp r0, #0x0
	bne _0201D29A
	ldr r0, [r4, #0xc]
	bl FUN_0201D324
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D29A:
	ldr r0, _0201D2A8 ; =0x021C5994
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x8]
	add r0, r0, #0x1
	str r0, [r1, #0x8]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0201D2A8: .word 0x021C5994

	thumb_func_start FUN_0201D2AC
FUN_0201D2AC: ; 0x0201D2AC
	push {r3-r4}
	ldr r1, _0201D2D8 ; =0x021C5994
	mov r2, #0x0
	ldr r4, [r1, #0x0]
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	ble _0201D2D2
	ldr r3, [r4, #0x0]
_0201D2BC:
	ldr r1, [r3, #0xc]
	cmp r0, r1
	bne _0201D2C8
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_0201D2C8:
	ldr r1, [r4, #0x4]
	add r2, r2, #0x1
	add r3, #0x54
	cmp r2, r1
	blt _0201D2BC
_0201D2D2:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4
_0201D2D8: .word 0x021C5994

	thumb_func_start FUN_0201D2DC
FUN_0201D2DC: ; 0x0201D2DC
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	bne _0201D2E8
	bl ErrorHandling
_0201D2E8:
	add r0, r4, #0x0
	bl FUN_0201D7F8
	add r4, r0, #0x0
	bne _0201D2F6
	bl ErrorHandling
_0201D2F6:
	str r5, [r4, #0x0]
	ldr r1, [r4, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201D30C
	ldr r1, [r4, #0x34]
	ldr r2, [r5, #0x14]
	ldr r3, [r5, #0x10]
	mov r0, #0x13
	bl FUN_0201C2C8
_0201D30C:
	ldr r1, [r4, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201D320
	ldr r1, [r4, #0x38]
	ldr r2, [r5, #0x14]
	ldr r3, [r5, #0x10]
	mov r0, #0x23
	bl FUN_0201C2C8
_0201D320:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201D324
FUN_0201D324: ; 0x0201D324
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r5, #0x1
	mov r7, #0x0
_0201D32C:
	add r0, r6, #0x0
	bl FUN_0201D7F8
	add r4, r0, #0x0
	bne _0201D33A
	bl ErrorHandling
_0201D33A:
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x4
	bne _0201D34E
	add r0, r4, #0x0
	add r0, #0x10
	bl FUN_0201D4F0
	b _0201D350
_0201D34E:
	add r5, r7, #0x0
_0201D350:
	cmp r5, #0x0
	bne _0201D32C
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201D36E
	add r0, r4, #0x0
	bl FUN_0201D7E0
	ldr r0, _0201D370 ; =0x021C5994
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x8]
	sub r0, r0, #0x1
	str r0, [r1, #0x8]
_0201D36E:
	pop {r3-r7, pc}
	.balign 4
_0201D370: .word 0x021C5994

	thumb_func_start FUN_0201D374
FUN_0201D374: ; 0x0201D374
	push {r4-r6, lr}
	ldr r6, _0201D3AC ; =0x021C5994
	mov r4, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, [r1, #0x4]
	cmp r0, #0x0
	ble _0201D3AA
	add r5, r4, #0x0
_0201D384:
	ldr r1, [r1, #0x0]
	add r0, r1, r5
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201D39E
	add r0, r1, r5
	bl FUN_0201D7E0
	ldr r1, [r6, #0x0]
	ldr r0, [r1, #0x8]
	sub r0, r0, #0x1
	str r0, [r1, #0x8]
_0201D39E:
	ldr r1, [r6, #0x0]
	add r4, r4, #0x1
	ldr r0, [r1, #0x4]
	add r5, #0x54
	cmp r4, r0
	blt _0201D384
_0201D3AA:
	pop {r4-r6, pc}
	.balign 4
_0201D3AC: .word 0x021C5994

	thumb_func_start FUN_0201D3B0
FUN_0201D3B0: ; 0x0201D3B0
	push {r4, lr}
	bl FUN_0201D7F8
	add r4, r0, #0x0
	bne _0201D3BE
	bl ErrorHandling
_0201D3BE:
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201D3CC
	mov r0, #0x0
	pop {r4, pc}
_0201D3CC:
	add r4, #0x10
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201D3D4
FUN_0201D3D4: ; 0x0201D3D4
	push {r3-r5, lr}
	sub sp, #0x18
	add r5, r1, #0x0
	bl FUN_0201D7F8
	add r4, r0, #0x0
	bne _0201D3E6
	bl ErrorHandling
_0201D3E6:
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201D3F6
	add sp, #0x18
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D3F6:
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x4]
	add r1, sp, #0x14
	add r2, sp, #0x10
	add r3, r5, #0x0
	bl FUN_0201D86C
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	bne _0201D41A
	add sp, #0x18
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D41A:
	add r0, r4, #0x0
	mov r1, #0x3
	add r0, #0x3c
	strb r1, [r0, #0x0]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	add r0, r4, #0x0
	bl FUN_0201D918
	mov r0, #0x1
	str r0, [r4, #0x48]
	ldr r0, [sp, #0xc]
	str r0, [r4, #0x4c]
	ldr r0, [sp, #0x8]
	str r0, [r4, #0x50]
	add r0, r4, #0x0
	bl FUN_0201DA38
	ldr r0, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x4]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	bl FUN_0201D948
	add r4, #0x10
	add r0, r4, #0x0
	add sp, #0x18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201D458
FUN_0201D458: ; 0x0201D458
	push {r3-r5, lr}
	sub sp, #0x18
	bl FUN_0201D6D8
	add r4, r0, #0x0
	bne _0201D468
	bl ErrorHandling
_0201D468:
	bl FUN_0201DAAC
	add r5, r0, #0x0
	bne _0201D474
	bl ErrorHandling
_0201D474:
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	beq _0201D484
	add sp, #0x18
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D484:
	add r3, r5, #0x0
	mov r2, #0xa
_0201D488:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0201D488
	ldr r0, [r4, #0x0]
	mov r1, #0x4
	str r0, [r3, #0x0]
	add r0, r5, #0x0
	add r0, #0x3c
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	tst r1, r0
	beq _0201D4A8
	ldr r3, [r5, #0x4c]
	b _0201D4AA
_0201D4A8:
	ldr r3, [r5, #0x50]
_0201D4AA:
	add r1, sp, #0xc
	str r1, [sp, #0x0]
	add r1, sp, #0x8
	str r1, [sp, #0x4]
	add r1, sp, #0x14
	add r2, sp, #0x10
	bl FUN_0201D86C
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	add r0, r5, #0x0
	bl FUN_0201D918
	mov r0, #0x1
	str r0, [r5, #0x48]
	ldr r0, [sp, #0xc]
	str r0, [r5, #0x4c]
	ldr r0, [sp, #0x8]
	str r0, [r5, #0x50]
	add r0, r5, #0x0
	bl FUN_0201DA38
	ldr r0, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x4]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	bl FUN_0201D948
	add r5, #0x10
	add r0, r5, #0x0
	add sp, #0x18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201D4F0
FUN_0201D4F0: ; 0x0201D4F0
	push {r4-r6, lr}
	ldr r2, _0201D564 ; =0x021C5994
	mov r1, #0x0
	ldr r5, [r2, #0x0]
	ldr r4, [r5, #0x4]
	cmp r4, #0x0
	ble _0201D52E
	ldr r2, [r5, #0x0]
	add r3, r1, #0x0
_0201D502:
	add r6, r2, #0x0
	add r6, #0x3c
	ldrb r6, [r6, #0x0]
	cmp r6, #0x3
	beq _0201D518
	ldr r6, [r5, #0x0]
	add r6, r6, r3
	add r6, #0x3c
	ldrb r6, [r6, #0x0]
	cmp r6, #0x4
	bne _0201D522
_0201D518:
	ldr r6, [r5, #0x0]
	add r6, r6, r3
	add r6, #0x10
	cmp r6, r0
	beq _0201D52E
_0201D522:
	ldr r6, [r5, #0x4]
	add r1, r1, #0x1
	add r2, #0x54
	add r3, #0x54
	cmp r1, r6
	blt _0201D502
_0201D52E:
	cmp r1, r4
	bge _0201D562
	mov r0, #0x54
	add r4, r1, #0x0
	mul r4, r0
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	bl FUN_0201DE4C
	ldr r0, _0201D564 ; =0x021C5994
	ldr r1, [r0, #0x0]
	ldr r2, [r1, #0x0]
	add r2, #0x3c
	ldrb r1, [r2, r4]
	cmp r1, #0x3
	bne _0201D554
	mov r0, #0x2
	strb r0, [r2, r4]
	pop {r4-r6, pc}
_0201D554:
	mov r1, #0x0
	strb r1, [r2, r4]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	bl FUN_0201D690
_0201D562:
	pop {r4-r6, pc}
	.balign 4
_0201D564: .word 0x021C5994

	thumb_func_start FUN_0201D568
FUN_0201D568: ; 0x0201D568
	push {r3-r7, lr}
	sub sp, #0x18
	add r6, r0, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	cmp r1, #0x0
	bne _0201D5A0
	add r1, r5, #0x0
	add r2, sp, #0x14
	add r3, sp, #0x10
	bl FUN_0201DF44
	add r7, r0, #0x0
	beq _0201D5E0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0201DF94
	str r5, [r4, #0x8]
	str r6, [r4, #0x0]
	cmp r5, #0x1
	bne _0201D59A
	ldr r0, [sp, #0x14]
	str r0, [r4, #0x4]
	b _0201D5E0
_0201D59A:
	ldr r0, [sp, #0x10]
	str r0, [r4, #0x4]
	b _0201D5E0
_0201D5A0:
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, sp, #0x14
	add r2, sp, #0x10
	add r3, r6, #0x0
	bl FUN_0201D86C
	add r7, r0, #0x0
	beq _0201D5E0
	ldr r0, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	add r0, r5, #0x0
	bl FUN_0201D948
	str r5, [r4, #0x8]
	cmp r5, #0x1
	bne _0201D5D8
	ldr r0, [sp, #0xc]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x14]
	str r0, [r4, #0x4]
	b _0201D5E0
_0201D5D8:
	ldr r0, [sp, #0x8]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x10]
	str r0, [r4, #0x4]
_0201D5E0:
	add r0, r7, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201D5E8
FUN_0201D5E8: ; 0x0201D5E8
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x8]
	mov r0, #0x1
	tst r0, r1
	beq _0201D61E
	ldr r1, _0201D654 ; =0x021C5994
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	add r5, r0, #0x0
	ldr r0, _0201D654 ; =0x021C5994
	ldr r1, [r4, #0x4]
	ldr r2, [r0, #0x0]
	ldr r0, [r2, #0x1c]
	sub r0, r1, r0
	ldr r1, [r2, #0x2c]
	bl FUN_0201DF2C
	ldr r2, _0201D654 ; =0x021C5994
	add r1, r5, #0x0
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x34]
	bl FUN_0201DDFC
_0201D61E:
	ldr r1, [r4, #0x8]
	mov r0, #0x2
	tst r0, r1
	beq _0201D650
	ldr r1, _0201D654 ; =0x021C5994
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	add r5, r0, #0x0
	ldr r0, _0201D654 ; =0x021C5994
	ldr r1, [r4, #0x4]
	ldr r2, [r0, #0x0]
	ldr r0, [r2, #0x20]
	sub r0, r1, r0
	ldr r1, [r2, #0x30]
	bl FUN_0201DF2C
	ldr r2, _0201D654 ; =0x021C5994
	add r1, r5, #0x0
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x38]
	bl FUN_0201DDFC
_0201D650:
	pop {r3-r5, pc}
	nop
_0201D654: .word 0x021C5994

	thumb_func_start FUN_0201D658
FUN_0201D658: ; 0x0201D658
	push {r3, lr}
	ldr r0, _0201D670 ; =0x021C5994
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201D666
	bl ErrorHandling
_0201D666:
	ldr r1, _0201D670 ; =0x021C5994
	mov r2, #0x0
	ldr r0, [r1, #0x0]
	str r2, [r1, #0x0]
	pop {r3, pc}
	.balign 4
_0201D670: .word 0x021C5994

	thumb_func_start FUN_0201D674
FUN_0201D674: ; 0x0201D674
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0201D68C ; =0x021C5994
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201D684
	bl ErrorHandling
_0201D684:
	ldr r0, _0201D68C ; =0x021C5994
	str r4, [r0, #0x0]
	pop {r4, pc}
	nop
_0201D68C: .word 0x021C5994

	thumb_func_start FUN_0201D690
FUN_0201D690: ; 0x0201D690
	mov r2, #0x0
	str r2, [r0, #0x0]
	str r2, [r0, #0x4]
	strb r2, [r0, #0x8]
	sub r1, r2, #0x1
	str r1, [r0, #0xc]
	str r2, [r0, #0x34]
	add r1, r0, #0x0
	str r2, [r0, #0x38]
	add r1, #0x3c
	strb r2, [r1, #0x0]
	str r2, [r0, #0x40]
	ldr r3, _0201D6B0 ; =FUN_020B1A24
	add r0, #0x10
	bx r3
	nop
_0201D6B0: .word FUN_020B1A24

	thumb_func_start FUN_0201D6B4
FUN_0201D6B4: ; 0x0201D6B4
	ldr r2, [r0, #0x0]
	str r2, [r1, #0x0]
	ldr r2, [r0, #0x8]
	str r2, [r1, #0xc]
	ldr r2, [r0, #0x4]
	str r2, [r1, #0x4]
	ldr r2, [r1, #0x0]
	ldr r2, [r2, #0xc]
	lsr r2, r2, #0x8
	strb r2, [r1, #0x8]
	ldr r0, [r0, #0xc]
	str r0, [r1, #0x44]
	mov r0, #0x0
	str r0, [r1, #0x48]
	str r0, [r1, #0x4c]
	str r0, [r1, #0x50]
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0201D6D8
FUN_0201D6D8: ; 0x0201D6D8
	push {r3-r6}
	ldr r2, _0201D720 ; =0x021C5994
	mov r1, #0x0
	ldr r5, [r2, #0x0]
	ldr r4, [r5, #0x4]
	cmp r4, #0x0
	ble _0201D70A
	ldr r2, [r5, #0x0]
	add r3, r1, #0x0
_0201D6EA:
	add r6, r2, #0x0
	add r6, #0x3c
	ldrb r6, [r6, #0x0]
	cmp r6, #0x0
	beq _0201D6FE
	ldr r6, [r5, #0x0]
	add r6, r6, r3
	add r6, #0x10
	cmp r6, r0
	beq _0201D70A
_0201D6FE:
	ldr r6, [r5, #0x4]
	add r1, r1, #0x1
	add r2, #0x54
	add r3, #0x54
	cmp r1, r6
	blt _0201D6EA
_0201D70A:
	cmp r1, r4
	blt _0201D714
	mov r0, #0x0
	pop {r3-r6}
	bx lr
_0201D714:
	mov r0, #0x54
	ldr r2, [r5, #0x0]
	mul r0, r1
	add r0, r2, r0
	pop {r3-r6}
	bx lr
	.balign 4
_0201D720: .word 0x021C5994

	thumb_func_start FUN_0201D724
FUN_0201D724: ; 0x0201D724
	push {r3, lr}
	ldrb r1, [r0, #0x8]
	mov r2, #0x1
	cmp r1, #0x0
	beq _0201D736
	mov r1, #0x2
	add r0, #0x3c
	strb r1, [r0, #0x0]
	b _0201D750
_0201D736:
	add r1, r0, #0x0
	add r1, #0x3c
	strb r2, [r1, #0x0]
	ldr r1, [r0, #0x44]
	cmp r1, #0x0
	bne _0201D74A
	bl FUN_0201D754
	add r2, r0, #0x0
	b _0201D750
_0201D74A:
	bl FUN_0201D788
	add r2, r0, #0x0
_0201D750:
	add r0, r2, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0201D754
FUN_0201D754: ; 0x0201D754
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	ldr r0, [r0, #0x10]
	add r2, sp, #0x4
	add r3, sp, #0x0
	bl FUN_0201DF44
	add r4, r0, #0x0
	beq _0201D780
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_0201D858
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	ldr r0, [r0, #0x10]
	bl FUN_0201DF94
_0201D780:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201D788
FUN_0201D788: ; 0x0201D788
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0x0
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	ldr r3, [r4, #0x0]
	ldr r0, [r4, #0x4]
	ldr r3, [r3, #0x10]
	add r1, sp, #0x14
	add r2, sp, #0x10
	bl FUN_0201D86C
	cmp r0, #0x0
	bne _0201D7AE
	add sp, #0x18
	mov r0, #0x0
	pop {r4, pc}
_0201D7AE:
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	add r0, r4, #0x0
	bl FUN_0201D918
	mov r0, #0x1
	str r0, [r4, #0x48]
	ldr r0, [sp, #0xc]
	str r0, [r4, #0x4c]
	ldr r0, [sp, #0x8]
	str r0, [r4, #0x50]
	add r0, r4, #0x0
	bl FUN_0201D9B0
	ldr r0, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x4]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	bl FUN_0201D948
	mov r0, #0x1
	add sp, #0x18
	pop {r4, pc}

	thumb_func_start FUN_0201D7E0
FUN_0201D7E0: ; 0x0201D7E0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x48]
	cmp r1, #0x0
	beq _0201D7EE
	bl FUN_0201DE4C
_0201D7EE:
	add r0, r4, #0x0
	bl FUN_0201D690
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201D7F8
FUN_0201D7F8: ; 0x0201D7F8
	push {r4-r5}
	ldr r2, _0201D82C ; =0x021C5994
	mov r1, #0x0
	ldr r5, [r2, #0x0]
	ldr r2, [r5, #0x4]
	cmp r2, #0x0
	ble _0201D824
	ldr r2, [r5, #0x0]
	add r4, r2, #0x0
_0201D80A:
	ldr r3, [r4, #0xc]
	cmp r0, r3
	bne _0201D81A
	mov r0, #0x54
	mul r0, r1
	add r0, r2, r0
	pop {r4-r5}
	bx lr
_0201D81A:
	ldr r3, [r5, #0x4]
	add r1, r1, #0x1
	add r4, #0x54
	cmp r1, r3
	blt _0201D80A
_0201D824:
	mov r0, #0x0
	pop {r4-r5}
	bx lr
	nop
_0201D82C: .word 0x021C5994

	thumb_func_start FUN_0201D830
FUN_0201D830: ; 0x0201D830
	cmp r1, #0x1
	bne _0201D83C
	mov r1, #0x1
	lsl r1, r1, #0x1a
	ldr r2, [r1, #0x0]
	b _0201D840
_0201D83C:
	ldr r1, _0201D850 ; =0x04001000
	ldr r2, [r1, #0x0]
_0201D840:
	ldr r1, _0201D854 ; =0x00300010
	and r2, r1
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x8]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x8]
	bx lr
	nop
_0201D850: .word 0x04001000
_0201D854: .word 0x00300010

	thumb_func_start FUN_0201D858
FUN_0201D858: ; 0x0201D858
	push {r3, lr}
	str r1, [r0, #0x34]
	str r2, [r0, #0x38]
	ldrb r1, [r0, #0x8]
	cmp r1, #0x0
	bne _0201D868
	bl FUN_0201D9B0
_0201D868:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201D86C
FUN_0201D86C: ; 0x0201D86C
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [sp, #0x1c]
	add r6, r2, #0x0
	str r0, [sp, #0x1c]
	mov r2, #0x1
	add r0, r5, #0x0
	add r4, r1, #0x0
	str r3, [sp, #0x0]
	ldr r7, [sp, #0x18]
	tst r0, r2
	beq _0201D8C4
	ldr r1, _0201D914 ; =0x021C5994
	add r0, r3, #0x0
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF10
	ldr r1, _0201D914 ; =0x021C5994
	str r0, [r7, #0x0]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	ldr r1, _0201D914 ; =0x021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x34]
	bl FUN_0201DD74
	mov r1, #0x0
	mvn r1, r1
	str r0, [r4, #0x0]
	cmp r0, r1
	bne _0201D8B8
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}
_0201D8B8:
	ldr r1, _0201D914 ; =0x021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF3C
	str r0, [r4, #0x0]
_0201D8C4:
	mov r0, #0x2
	tst r0, r5
	beq _0201D90E
	ldr r1, _0201D914 ; =0x021C5994
	ldr r0, [sp, #0x0]
	ldr r1, [r1, #0x0]
	mov r2, #0x1
	ldr r1, [r1, #0x30]
	bl FUN_0201DF10
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r1, _0201D914 ; =0x021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	ldr r1, _0201D914 ; =0x021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x38]
	bl FUN_0201DD74
	mov r1, #0x0
	mvn r1, r1
	str r0, [r6, #0x0]
	cmp r0, r1
	bne _0201D902
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}
_0201D902:
	ldr r1, _0201D914 ; =0x021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF3C
	str r0, [r6, #0x0]
_0201D90E:
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_0201D914: .word 0x021C5994

	thumb_func_start FUN_0201D918
FUN_0201D918: ; 0x0201D918
	push {r3-r4}
	ldr r4, [r0, #0x4]
	mov r3, #0x1
	tst r3, r4
	beq _0201D92C
	ldr r3, _0201D944 ; =0x021C5994
	ldr r3, [r3, #0x0]
	ldr r3, [r3, #0x1c]
	add r1, r1, r3
	str r1, [r0, #0x34]
_0201D92C:
	ldr r3, [r0, #0x4]
	mov r1, #0x2
	tst r1, r3
	beq _0201D93E
	ldr r1, _0201D944 ; =0x021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x20]
	add r1, r2, r1
	str r1, [r0, #0x38]
_0201D93E:
	pop {r3-r4}
	bx lr
	nop
_0201D944: .word 0x021C5994

	thumb_func_start FUN_0201D948
FUN_0201D948: ; 0x0201D948
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x1
	add r4, r1, #0x0
	add r6, r2, #0x0
	tst r0, r5
	beq _0201D97C
	ldr r1, _0201D9AC ; =0x021C5994
	add r0, r3, #0x0
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	ldr r1, _0201D9AC ; =0x021C5994
	add r7, r0, #0x0
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	ldr r2, _0201D9AC ; =0x021C5994
	add r1, r7, #0x0
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x34]
	bl FUN_0201DD18
_0201D97C:
	mov r0, #0x2
	tst r0, r5
	beq _0201D9A8
	ldr r1, _0201D9AC ; =0x021C5994
	ldr r0, [sp, #0x18]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	ldr r1, _0201D9AC ; =0x021C5994
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	add r0, r6, #0x0
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	ldr r2, _0201D9AC ; =0x021C5994
	add r1, r4, #0x0
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x38]
	bl FUN_0201DD18
_0201D9A8:
	pop {r3-r7, pc}
	nop
_0201D9AC: .word 0x021C5994

	thumb_func_start FUN_0201D9B0
FUN_0201D9B0: ; 0x0201D9B0
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x10
	bl FUN_020B1A24
	ldr r1, [r4, #0x4]
	cmp r1, #0x3
	beq _0201D9C8
	add r0, r4, #0x0
	bl FUN_0201D9DC
	pop {r4, pc}
_0201D9C8:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0201D9DC
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0201D9DC
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201D9DC
FUN_0201D9DC: ; 0x0201D9DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x40]
	add r4, r1, #0x0
	cmp r2, #0x0
	beq _0201D9EE
	bl FUN_0201D830
	b _0201D9F0
_0201D9EE:
	add r0, r4, #0x0
_0201D9F0:
	cmp r4, #0x1
	bne _0201D9FE
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r5, #0x34]
	ldr r2, [r2, #0x0]
	b _0201DA04
_0201D9FE:
	ldr r2, _0201DA34 ; =0x04001000
	ldr r1, [r5, #0x38]
	ldr r2, [r2, #0x0]
_0201DA04:
	cmp r0, #0x0
	ldr r0, [r5, #0x0]
	bne _0201DA16
	add r5, #0x10
	add r2, r4, #0x0
	add r3, r5, #0x0
	bl FUN_020B1528
	b _0201DA20
_0201DA16:
	add r5, #0x10
	add r2, r4, #0x0
	add r3, r5, #0x0
	bl FUN_020B1768
_0201DA20:
	cmp r4, #0x1
	bne _0201DA2C
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
_0201DA2C:
	ldr r0, _0201DA34 ; =0x04001000
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
	nop
_0201DA34: .word 0x04001000

	thumb_func_start FUN_0201DA38
FUN_0201DA38: ; 0x0201DA38
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x10
	bl FUN_020B1A24
	ldr r1, [r4, #0x4]
	cmp r1, #0x3
	beq _0201DA50
	add r0, r4, #0x0
	bl FUN_0201DA64
	pop {r4, pc}
_0201DA50:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0201DA64
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0201DA64
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201DA64
FUN_0201DA64: ; 0x0201DA64
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x40]
	add r4, r1, #0x0
	cmp r2, #0x0
	beq _0201DA74
	bl FUN_0201D830
_0201DA74:
	cmp r4, #0x1
	bne _0201DA82
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r1, [r5, #0x34]
	ldr r0, [r0, #0x0]
	b _0201DA88
_0201DA82:
	ldr r0, _0201DAA8 ; =0x04001000
	ldr r1, [r5, #0x38]
	ldr r0, [r0, #0x0]
_0201DA88:
	ldr r0, [r5, #0x0]
	add r5, #0x10
	add r2, r4, #0x0
	add r3, r5, #0x0
	bl FUN_020B1340
	cmp r4, #0x1
	bne _0201DAA0
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
_0201DAA0:
	ldr r0, _0201DAA8 ; =0x04001000
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
	nop
_0201DAA8: .word 0x04001000

	thumb_func_start FUN_0201DAAC
FUN_0201DAAC: ; 0x0201DAAC
	push {r3-r4}
	ldr r1, _0201DAE4 ; =0x021C5994
	mov r0, #0x0
	ldr r4, [r1, #0x0]
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	ble _0201DADC
	ldr r1, [r4, #0x0]
	add r3, r1, #0x0
_0201DABE:
	add r2, r3, #0x0
	add r2, #0x3c
	ldrb r2, [r2, #0x0]
	cmp r2, #0x0
	bne _0201DAD2
	mov r2, #0x54
	mul r2, r0
	add r0, r1, r2
	pop {r3-r4}
	bx lr
_0201DAD2:
	ldr r2, [r4, #0x4]
	add r0, r0, #0x1
	add r3, #0x54
	cmp r0, r2
	blt _0201DABE
_0201DADC:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	nop
_0201DAE4: .word 0x021C5994

	thumb_func_start FUN_0201DAE8
FUN_0201DAE8: ; 0x0201DAE8
	push {r3, lr}
	bl GX_GetBankForOBJ
	cmp r0, #0x30
	bgt _0201DB18
	bge _0201DB60
	cmp r0, #0x10
	bgt _0201DB12
	bge _0201DB54
	cmp r0, #0x3
	bhi _0201DB90
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0201DB0A: ; jump table (using 16-bit offset)
	.short _0201DB32 - _0201DB0A - 2; case 0
	.short _0201DB78 - _0201DB0A - 2; case 1
	.short _0201DB78 - _0201DB0A - 2; case 2
	.short _0201DB84 - _0201DB0A - 2; case 3
_0201DB12:
	cmp r0, #0x20
	beq _0201DB3C
	b _0201DB90
_0201DB18:
	cmp r0, #0x50
	bgt _0201DB24
	bge _0201DB60
	cmp r0, #0x40
	beq _0201DB3C
	b _0201DB90
_0201DB24:
	cmp r0, #0x60
	bgt _0201DB2C
	beq _0201DB48
	b _0201DB90
_0201DB2C:
	cmp r0, #0x70
	beq _0201DB6C
	b _0201DB90
_0201DB32:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB3C:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB48:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB54:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x10
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB60:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x5
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB6C:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x6
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB78:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x10
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB84:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x12
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB90:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x14]
_0201DB98:
	bl GX_GetBankForSubOBJ
	cmp r0, #0x0
	beq _0201DBAE
	cmp r0, #0x8
	beq _0201DBC2
	mov r1, #0x1
	lsl r1, r1, #0x8
	cmp r0, r1
	beq _0201DBB8
	b _0201DBCE
_0201DBAE:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x18]
	b _0201DBD6
_0201DBB8:
	ldr r0, _0201DC38 ; =0x021C5994
	lsl r1, r1, #0x6
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x18]
	b _0201DBD6
_0201DBC2:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x10
	str r1, [r0, #0x18]
	b _0201DBD6
_0201DBCE:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x18]
_0201DBD6:
	ldr r0, _0201DC38 ; =0x021C5994
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x24]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF3C
	ldr r1, _0201DC38 ; =0x021C5994
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x14]
	sub r0, r2, r0
	str r0, [r3, #0x1c]
	ldr r1, [r1, #0x0]
	ldr r0, [r1, #0x28]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF3C
	ldr r1, _0201DC38 ; =0x021C5994
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x18]
	sub r0, r2, r0
	str r0, [r3, #0x20]
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	ldr r0, [r1, #0x1c]
	cmp r0, #0x0
	blt _0201DC12
	ldr r0, [r1, #0x20]
	cmp r0, #0x0
	blt _0201DC12
	mov r2, #0x1
_0201DC12:
	cmp r2, #0x0
	bne _0201DC1A
	bl ErrorHandling
_0201DC1A:
	ldr r0, _0201DC38 ; =0x021C5994
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x1c]
	cmp r0, #0x0
	blt _0201DC2E
	ldr r0, [r1, #0x20]
	cmp r0, #0x0
	blt _0201DC2E
	mov r2, #0x1
_0201DC2E:
	cmp r2, #0x0
	bne _0201DC36
	bl ErrorHandling
_0201DC36:
	pop {r3, pc}
	.balign 4
_0201DC38: .word 0x021C5994

	thumb_func_start FUN_0201DC3C
FUN_0201DC3C: ; 0x0201DC3C
	push {r3, lr}
	ldr r0, _0201DC54 ; =0x021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_0201DD00
	ldr r0, _0201DC54 ; =0x021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_0201DD00
	pop {r3, pc}
	.balign 4
_0201DC54: .word 0x021C5994

	thumb_func_start FUN_0201DC58
FUN_0201DC58: ; 0x0201DC58
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _0201DCBC ; =0x021C5994
	add r4, r1, #0x0
	ldr r1, [r0, #0x0]
	add r6, r2, #0x0
	str r5, [r1, #0x24]
	ldr r1, [r0, #0x0]
	str r4, [r1, #0x28]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	cmp r0, #0x0
	beq _0201DC76
	bl FUN_02016A18
_0201DC76:
	ldr r0, _0201DCBC ; =0x021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	cmp r0, #0x0
	beq _0201DC84
	bl FUN_02016A18
_0201DC84:
	ldr r0, _0201DCBC ; =0x021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x24]
	cmp r0, #0x0
	beq _0201DC9C
	add r0, r6, #0x0
	lsr r1, r5, #0x3
	bl FUN_02016998
	ldr r1, _0201DCBC ; =0x021C5994
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x34]
_0201DC9C:
	ldr r0, _0201DCBC ; =0x021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	cmp r0, #0x0
	beq _0201DCB4
	add r0, r6, #0x0
	lsr r1, r4, #0x3
	bl FUN_02016998
	ldr r1, _0201DCBC ; =0x021C5994
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x38]
_0201DCB4:
	bl FUN_0201DC3C
	pop {r4-r6, pc}
	nop
_0201DCBC: .word 0x021C5994

	thumb_func_start FUN_0201DCC0
FUN_0201DCC0: ; 0x0201DCC0
	push {r3, lr}
	cmp r0, #0x0
	beq _0201DCE2
	ldr r1, _0201DCE4 ; =0x021C5994
	ldr r2, [r1, #0x0]
	ldr r1, [r2, #0x34]
	cmp r0, r1
	bne _0201DCDA
	mov r1, #0x0
	str r1, [r2, #0x24]
	bl FUN_02016A18
	pop {r3, pc}
_0201DCDA:
	mov r1, #0x0
	str r1, [r2, #0x28]
	bl FUN_02016A18
_0201DCE2:
	pop {r3, pc}
	.balign 4
_0201DCE4: .word 0x021C5994

	thumb_func_start FUN_0201DCE8
FUN_0201DCE8: ; 0x0201DCE8
	ldr r1, _0201DCFC ; =0x021C5994
	ldr r2, [r1, #0x0]
	ldr r1, [r2, #0x34]
	cmp r0, r1
	bne _0201DCF6
	ldr r0, [r2, #0x24]
	bx lr
_0201DCF6:
	ldr r0, [r2, #0x28]
	bx lr
	nop
_0201DCFC: .word 0x021C5994

	thumb_func_start FUN_0201DD00
FUN_0201DD00: ; 0x0201DD00
	push {r4, lr}
	add r4, r0, #0x0
	beq _0201DD16
	bl FUN_0201DCE8
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x0
	lsr r2, r2, #0x3
	bl Call_FillMemWithValue
_0201DD16:
	pop {r4, pc}

	thumb_func_start FUN_0201DD18
FUN_0201DD18: ; 0x0201DD18
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	beq _0201DD6E
	add r0, r4, #0x0
	bl FUN_0201DCE8
	add r6, r5, r6
	add r7, r0, #0x0
	cmp r5, r6
	bhs _0201DD6E
_0201DD32:
	cmp r5, r7
	bhs _0201DD6E
	add r0, r5, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	bl FUN_0201DFE4
	add r0, sp, #0x0
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	lsl r0, r1
	ldr r1, [sp, #0x4]
	ldrb r1, [r4, r1]
	tst r0, r1
	beq _0201DD54
	bl ErrorHandling
_0201DD54:
	add r2, sp, #0x0
	ldrb r3, [r2, #0x0]
	ldr r1, [sp, #0x4]
	mov r2, #0x1
	lsl r2, r3
	lsl r2, r2, #0x18
	ldrb r0, [r4, r1]
	lsr r2, r2, #0x18
	add r5, r5, #0x1
	orr r0, r2
	strb r0, [r4, r1]
	cmp r5, r6
	blo _0201DD32
_0201DD6E:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201DD74
FUN_0201DD74: ; 0x0201DD74
	push {r3-r7, lr}
	sub sp, #0x10
	add r7, r0, #0x0
	str r1, [sp, #0x0]
	cmp r1, #0x0
	beq _0201DDF2
	add r0, r1, #0x0
	bl FUN_0201DCE8
	mov r6, #0x0
	str r0, [sp, #0x4]
	cmp r0, #0x0
	bls _0201DDF2
_0201DD8E:
	add r0, r6, #0x0
	add r1, sp, #0xc
	add r2, sp, #0x8
	bl FUN_0201DFE4
	add r0, sp, #0x8
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	mov r4, #0x0
	lsl r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	b _0201DDD0
_0201DDA8:
	add r5, r6, r4
	add r0, r5, #0x0
	add r1, sp, #0xc
	add r2, sp, #0x8
	bl FUN_0201DFE4
	add r0, sp, #0x8
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	lsl r0, r1
	lsl r0, r0, #0x18
	ldr r1, [sp, #0x4]
	lsr r0, r0, #0x18
	cmp r5, r1
	blo _0201DDCE
	mov r0, #0x0
	add sp, #0x10
	mvn r0, r0
	pop {r3-r7, pc}
_0201DDCE:
	add r4, r4, #0x1
_0201DDD0:
	ldr r2, [sp, #0xc]
	ldr r1, [sp, #0x0]
	ldrb r1, [r1, r2]
	tst r0, r1
	bne _0201DDDE
	cmp r4, r7
	bls _0201DDA8
_0201DDDE:
	cmp r4, r7
	bls _0201DDE8
	add sp, #0x10
	add r0, r6, #0x0
	pop {r3-r7, pc}
_0201DDE8:
	add r0, r6, r4
	add r6, r0, #0x1
	ldr r0, [sp, #0x4]
	cmp r6, r0
	blo _0201DD8E
_0201DDF2:
	mov r0, #0x0
	mvn r0, r0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201DDFC
FUN_0201DDFC: ; 0x0201DDFC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r2, #0x0
	beq _0201DE46
	add r6, r5, r1
	cmp r5, r6
	bhs _0201DE46
	add r7, sp, #0x0
_0201DE0E:
	add r0, r5, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	bl FUN_0201DFE4
	ldrb r1, [r7, #0x0]
	mov r0, #0x1
	lsl r0, r1
	ldr r1, [sp, #0x4]
	ldrb r1, [r4, r1]
	tst r0, r1
	bne _0201DE2A
	bl ErrorHandling
_0201DE2A:
	ldrb r0, [r7, #0x0]
	mov r1, #0x1
	ldr r3, [sp, #0x4]
	lsl r1, r0
	mov r0, #0xff
	eor r0, r1
	lsl r0, r0, #0x18
	ldrb r2, [r4, r3]
	lsr r0, r0, #0x18
	add r5, r5, #0x1
	and r0, r2
	strb r0, [r4, r3]
	cmp r5, r6
	blo _0201DE0E
_0201DE46:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201DE4C
FUN_0201DE4C: ; 0x0201DE4C
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	mov r1, #0x1
	tst r0, r1
	beq _0201DE8A
	add r0, r4, #0x0
	add r0, #0x10
	bl FUN_020B1A14
	ldr r1, _0201DECC ; =0x021C5994
	ldr r2, [r1, #0x0]
	ldr r1, [r2, #0x1c]
	sub r0, r0, r1
	ldr r1, [r2, #0x2c]
	bl FUN_0201DF2C
	ldr r1, _0201DECC ; =0x021C5994
	add r5, r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r0, [r4, #0x4c]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	ldr r2, _0201DECC ; =0x021C5994
	add r1, r0, #0x0
	ldr r2, [r2, #0x0]
	add r0, r5, #0x0
	ldr r2, [r2, #0x34]
	bl FUN_0201DDFC
_0201DE8A:
	ldr r0, [r4, #0x4]
	mov r1, #0x2
	tst r0, r1
	beq _0201DEC4
	add r0, r4, #0x0
	add r0, #0x10
	bl FUN_020B1A14
	ldr r1, _0201DECC ; =0x021C5994
	ldr r2, [r1, #0x0]
	ldr r1, [r2, #0x20]
	sub r0, r0, r1
	ldr r1, [r2, #0x30]
	bl FUN_0201DF2C
	ldr r1, _0201DECC ; =0x021C5994
	add r5, r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r0, [r4, #0x50]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	ldr r2, _0201DECC ; =0x021C5994
	add r1, r0, #0x0
	ldr r2, [r2, #0x0]
	add r0, r5, #0x0
	ldr r2, [r2, #0x38]
	bl FUN_0201DDFC
_0201DEC4:
	mov r0, #0x0
	str r0, [r4, #0x48]
	pop {r3-r5, pc}
	nop
_0201DECC: .word 0x021C5994

	thumb_func_start FUN_0201DED0
FUN_0201DED0: ; 0x0201DED0
	ldr r1, _0201DF04 ; =0x00100010
	cmp r0, r1
	bgt _0201DEDE
	bge _0201DEF4
	cmp r0, #0x10
	beq _0201DEF0
	b _0201DF00
_0201DEDE:
	ldr r1, _0201DF08 ; =0x00200010
	cmp r0, r1
	bgt _0201DEE8
	beq _0201DEF8
	b _0201DF00
_0201DEE8:
	ldr r1, _0201DF0C ; =0x00300010
	cmp r0, r1
	beq _0201DEFC
	b _0201DF00
_0201DEF0:
	mov r0, #0x1
	bx lr
_0201DEF4:
	mov r0, #0x2
	bx lr
_0201DEF8:
	mov r0, #0x4
	bx lr
_0201DEFC:
	mov r0, #0x8
	bx lr
_0201DF00:
	mov r0, #0x1
	bx lr
	.balign 4
_0201DF04: .word 0x00100010
_0201DF08: .word 0x00200010
_0201DF0C: .word 0x00300010

	thumb_func_start FUN_0201DF10
FUN_0201DF10: ; 0x0201DF10
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl _s32_div_f
	cmp r1, #0x0
	beq _0201DF28
	sub r5, r5, r1
	cmp r6, #0x1
	bne _0201DF28
	add r5, r5, r4
_0201DF28:
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0201DF2C
FUN_0201DF2C: ; 0x0201DF2C
	asr r2, r0, #0x4
	lsr r2, r2, #0x1b
	add r2, r0, r2
	ldr r3, _0201DF38 ; =_s32_div_f
	asr r0, r2, #0x5
	bx r3
	.balign 4
_0201DF38: .word _s32_div_f

	thumb_func_start FUN_0201DF3C
FUN_0201DF3C: ; 0x0201DF3C
	mul r1, r0
	lsl r0, r1, #0x5
	bx lr
	.balign 4

	thumb_func_start FUN_0201DF44
FUN_0201DF44: ; 0x0201DF44
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r1, r2, #0x0
	mov r0, #0x1
	add r2, r4, #0x0
	add r7, r3, #0x0
	tst r2, r0
	beq _0201DF6E
	ldr r2, _0201DF90 ; =0x021C5994
	ldr r2, [r2, #0x0]
	ldr r6, [r2, #0xc]
	ldr r2, [r2, #0x1c]
	add r3, r6, r5
	cmp r3, r2
	bls _0201DF6C
	bl ErrorHandling
	mov r0, #0x0
	b _0201DF6E
_0201DF6C:
	str r6, [r1, #0x0]
_0201DF6E:
	mov r1, #0x2
	tst r1, r4
	beq _0201DF8C
	ldr r1, _0201DF90 ; =0x021C5994
	ldr r1, [r1, #0x0]
	ldr r3, [r1, #0x10]
	ldr r1, [r1, #0x20]
	add r2, r3, r5
	cmp r2, r1
	bls _0201DF8A
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}
_0201DF8A:
	str r3, [r7, #0x0]
_0201DF8C:
	pop {r3-r7, pc}
	nop
_0201DF90: .word 0x021C5994

	thumb_func_start FUN_0201DF94
FUN_0201DF94: ; 0x0201DF94
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	mov r2, #0x1
	add r0, r4, #0x0
	tst r0, r2
	beq _0201DFBC
	ldr r0, _0201DFE0 ; =0x021C5994
	ldr r3, [r0, #0x0]
	ldr r1, [r3, #0xc]
	add r1, r1, r5
	str r1, [r3, #0xc]
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0xc]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF10
	ldr r1, _0201DFE0 ; =0x021C5994
	ldr r1, [r1, #0x0]
	str r0, [r1, #0xc]
_0201DFBC:
	mov r0, #0x2
	tst r0, r4
	beq _0201DFDE
	ldr r0, _0201DFE0 ; =0x021C5994
	ldr r2, [r0, #0x0]
	ldr r1, [r2, #0x10]
	add r1, r1, r5
	str r1, [r2, #0x10]
	ldr r1, [r0, #0x0]
	mov r2, #0x1
	ldr r0, [r1, #0x10]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF10
	ldr r1, _0201DFE0 ; =0x021C5994
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x10]
_0201DFDE:
	pop {r3-r5, pc}
	.balign 4
_0201DFE0: .word 0x021C5994

	thumb_func_start FUN_0201DFE4
FUN_0201DFE4: ; 0x0201DFE4
	asr r3, r0, #0x3
	str r3, [r1, #0x0]
	mov r1, #0x7
	and r0, r1
	strb r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_0201DFF0
FUN_0201DFF0: ; 0x0201DFF0
	push {r3-r4}
	sub r0, r1, r0
	ldr r4, [sp, #0x8]
	str r0, [r3, #0x0]
	bpl _0201E006
	add r0, r2, r0
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_0201E006:
	str r2, [r4, #0x0]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201E00C
FUN_0201E00C: ; 0x0201E00C
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, _0201E064 ; =0x021C5998
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201E060
	add r0, r4, #0x0
	mov r1, #0x28
	bl FUN_02016998
	add r1, r0, #0x0
	ldr r0, _0201E064 ; =0x021C5998
	mov r2, #0x28
	str r1, [r0, #0x0]
	mov r0, #0x0
	bl MIi_CpuClear32
	ldr r0, _0201E064 ; =0x021C5998
	mov r1, #0x30
	ldr r0, [r0, #0x0]
	mul r1, r6
	str r6, [r0, #0x4]
	add r0, r4, #0x0
	bl FUN_02016998
	ldr r7, _0201E064 ; =0x021C5998
	mov r4, #0x0
	ldr r1, [r7, #0x0]
	cmp r6, #0x0
	str r0, [r1, #0x0]
	ble _0201E060
	add r5, r4, #0x0
_0201E04E:
	ldr r0, [r7, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	bl FUN_0201E2F8
	add r4, r4, #0x1
	add r5, #0x30
	cmp r4, r6
	blt _0201E04E
_0201E060:
	pop {r3-r7, pc}
	nop
_0201E064: .word 0x021C5998

	thumb_func_start FUN_0201E068
FUN_0201E068: ; 0x0201E068
	cmp r1, #0x1
	bne _0201E078
	ldr r1, _0201E088 ; =0x021C5998
	ldr r2, [r1, #0x0]
	ldrh r1, [r2, #0x24]
	orr r0, r1
	strh r0, [r2, #0x24]
	bx lr
_0201E078:
	cmp r1, #0x2
	bne _0201E086
	ldr r1, _0201E088 ; =0x021C5998
	ldr r2, [r1, #0x0]
	ldrh r1, [r2, #0x26]
	orr r0, r1
	strh r0, [r2, #0x26]
_0201E086:
	bx lr
	.balign 4
_0201E088: .word 0x021C5998

	thumb_func_start FUN_0201E08C
FUN_0201E08C: ; 0x0201E08C
	push {r3, lr}
	ldr r0, _0201E0B4 ; =0x021C5998
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201E0B2
	bl FUN_0201E1F0
	ldr r0, _0201E0B4 ; =0x021C5998
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _0201E0B4 ; =0x021C5998
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _0201E0B4 ; =0x021C5998
	mov r1, #0x0
	str r1, [r0, #0x0]
_0201E0B2:
	pop {r3, pc}
	.balign 4
_0201E0B4: .word 0x021C5998

	thumb_func_start FUN_0201E0B8
FUN_0201E0B8: ; 0x0201E0B8
	bx lr
	.balign 4

	thumb_func_start FUN_0201E0BC
FUN_0201E0BC: ; 0x0201E0BC
	push {r3, lr}
	ldr r0, _0201E0E0 ; =0x021C5998
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	str r2, [r1, #0xc]
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x10]
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x14]
	ldr r0, [r0, #0x0]
	str r2, [r0, #0x18]
	bl FUN_0201E464
	ldr r0, _0201E0E0 ; =0x021C5998
	ldr r0, [r0, #0x0]
	bl FUN_0201E574
	pop {r3, pc}
	.balign 4
_0201E0E0: .word 0x021C5998

	thumb_func_start FUN_0201E0E4
FUN_0201E0E4: ; 0x0201E0E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0201E428
	add r4, r0, #0x0
	bne _0201E0F8
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E0F8:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201E2C4
	cmp r0, #0x0
	bne _0201E108
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E108:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201E314
	cmp r0, #0x0
	bne _0201E11E
	ldr r0, [r5, #0xc]
	bl FUN_0201E1C8
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E11E:
	add r0, r4, #0x0
	bl FUN_0201E57C
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0201E128
FUN_0201E128: ; 0x0201E128
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0201E428
	add r4, r0, #0x0
	bne _0201E13C
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E13C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201E2C4
	cmp r0, #0x0
	bne _0201E14C
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E14C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201E36C
	cmp r0, #0x0
	bne _0201E162
	ldr r0, [r5, #0xc]
	bl FUN_0201E1C8
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E162:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201E168
FUN_0201E168: ; 0x0201E168
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	bne _0201E174
	bl ErrorHandling
_0201E174:
	add r0, r4, #0x0
	bl FUN_0201E3F0
	add r4, r0, #0x0
	bne _0201E182
	bl ErrorHandling
_0201E182:
	str r5, [r4, #0x0]
	ldr r1, [r4, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201E19A
	ldr r3, [r4, #0x8]
	ldr r1, [r4, #0x24]
	ldr r2, [r5, #0xc]
	mov r0, #0xe
	lsl r3, r3, #0x5
	bl FUN_0201C2C8
_0201E19A:
	ldr r1, [r4, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201E1B0
	ldr r3, [r4, #0x8]
	ldr r1, [r4, #0x28]
	ldr r2, [r5, #0xc]
	mov r0, #0x1e
	lsl r3, r3, #0x5
	bl FUN_0201C2C8
_0201E1B0:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201E1B4
FUN_0201E1B4: ; 0x0201E1B4
	push {r3, lr}
	bl FUN_0201E3F0
	cmp r0, #0x0
	beq _0201E1C2
	mov r0, #0x1
	pop {r3, pc}
_0201E1C2:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201E1C8
FUN_0201E1C8: ; 0x0201E1C8
	push {r4, lr}
	bl FUN_0201E3F0
	add r4, r0, #0x0
	bne _0201E1D6
	bl ErrorHandling
_0201E1D6:
	add r0, r4, #0x0
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0201E1EC
	add r0, r4, #0x0
	bl FUN_0201E5B8
	add r0, r4, #0x0
	bl FUN_0201E2BC
_0201E1EC:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201E1F0
FUN_0201E1F0: ; 0x0201E1F0
	push {r4-r6, lr}
	ldr r6, _0201E22C ; =0x021C5998
	mov r4, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, [r1, #0x4]
	cmp r0, #0x0
	ble _0201E228
	add r5, r4, #0x0
_0201E200:
	ldr r1, [r1, #0x0]
	add r0, r1, r5
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0201E21C
	add r0, r1, r5
	bl FUN_0201E5B8
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	bl FUN_0201E2BC
_0201E21C:
	ldr r1, [r6, #0x0]
	add r4, r4, #0x1
	ldr r0, [r1, #0x4]
	add r5, #0x30
	cmp r4, r0
	blt _0201E200
_0201E228:
	pop {r4-r6, pc}
	nop
_0201E22C: .word 0x021C5998

	thumb_func_start FUN_0201E230
FUN_0201E230: ; 0x0201E230
	push {r3, lr}
	bl FUN_0201E3F0
	cmp r0, #0x0
	bne _0201E244
	bne _0201E240
	bl ErrorHandling
_0201E240:
	mov r0, #0x0
	pop {r3, pc}
_0201E244:
	add r1, r0, #0x0
	add r1, #0x2c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	bne _0201E252
	add r0, #0x10
	pop {r3, pc}
_0201E252:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201E258
FUN_0201E258: ; 0x0201E258
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0201E3F0
	cmp r0, #0x0
	bne _0201E26E
	bne _0201E26A
	bl ErrorHandling
_0201E26A:
	mov r0, #0x0
	pop {r4, pc}
_0201E26E:
	add r1, r0, #0x0
	add r1, #0x2c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	beq _0201E27C
	mov r0, #0x0
	pop {r4, pc}
_0201E27C:
	ldr r1, [r0, #0x0]
	ldr r1, [r1, #0x4]
	cmp r1, #0x0
	beq _0201E288
	mov r1, #0x1
	str r1, [r4, #0x18]
_0201E288:
	add r0, #0x10
	pop {r4, pc}

	thumb_func_start FUN_0201E28C
FUN_0201E28C: ; 0x0201E28C
	push {r4, lr}
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	beq _0201E29A
	mov r4, #0x2
	lsl r4, r4, #0x8
	b _0201E2A6
_0201E29A:
	ldr r2, [r0, #0x0]
	cmp r2, #0x4
	bne _0201E2A4
	mov r4, #0x0
	b _0201E2A6
_0201E2A4:
	mov r4, #0x20
_0201E2A6:
	cmp r4, #0x0
	beq _0201E2B6
	bl FUN_020B19C4
	add r1, r4, #0x0
	bl _u32_div_f
	pop {r4, pc}
_0201E2B6:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201E2BC
FUN_0201E2BC: ; 0x0201E2BC
	ldr r3, _0201E2C0 ; =FUN_0201E2F8
	bx r3
	.balign 4
_0201E2C0: .word FUN_0201E2F8

	thumb_func_start FUN_0201E2C4
FUN_0201E2C4: ; 0x0201E2C4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_0201E1B4
	cmp r0, #0x1
	bne _0201E2E0
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E2E0:
	ldr r0, [r5, #0xc]
	add r1, r4, #0x0
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x4]
	add r1, #0x2c
	str r0, [r4, #0x4]
	mov r0, #0x1
	strb r0, [r1, #0x0]
	ldr r1, [r5, #0x8]
	str r1, [r4, #0x8]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201E2F8
FUN_0201E2F8: ; 0x0201E2F8
	push {r4, lr}
	mov r1, #0x0
	mov r2, #0x30
	add r4, r0, #0x0
	bl Call_FillMemWithValue
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0xc]
	add r4, #0x10
	add r0, r4, #0x0
	bl FUN_020B19DC
	pop {r4, pc}

	thumb_func_start FUN_0201E314
FUN_0201E314: ; 0x0201E314
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r1, #0x0
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0201E334
	ldr r0, _0201E368 ; =0x021C5998
	ldr r0, [r0, #0x0]
	add r4, r0, #0x0
	add r5, r0, #0x0
	ldr r3, [r0, #0x1c]
	add r4, #0x14
	add r5, #0x18
	ldr r0, [r0, #0x20]
	b _0201E344
_0201E334:
	ldr r0, _0201E368 ; =0x021C5998
	mov r3, #0x2
	ldr r5, [r0, #0x0]
	lsl r3, r3, #0x8
	add r4, r5, #0x0
	add r4, #0xc
	add r5, #0x10
	add r0, r3, #0x0
_0201E344:
	str r0, [sp, #0x0]
	ldr r1, [r4, #0x0]
	ldr r2, [r5, #0x0]
	add r0, r6, #0x0
	bl FUN_0201E5F4
	add r0, r6, #0x0
	bl FUN_0201E4AC
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FUN_0201E640
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_0201E368: .word 0x021C5998

	thumb_func_start FUN_0201E36C
FUN_0201E36C: ; 0x0201E36C
	push {r4-r6, lr}
	add r5, r1, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0201E37C
	bl ErrorHandling
_0201E37C:
	ldr r1, [r5, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201E39E
	ldr r0, _0201E3EC ; =0x021C5998
	ldr r1, [r5, #0x8]
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x24]
	bl FUN_0201E534
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r6, r0
	bne _0201E39E
	mov r0, #0x0
	pop {r4-r6, pc}
_0201E39E:
	ldr r1, [r5, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201E3C0
	ldr r0, _0201E3EC ; =0x021C5998
	ldr r1, [r5, #0x8]
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x26]
	bl FUN_0201E534
	add r4, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	bne _0201E3C0
	mov r0, #0x0
	pop {r4-r6, pc}
_0201E3C0:
	ldr r1, [r5, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201E3CA
	str r6, [r5, #0x24]
_0201E3CA:
	ldr r1, [r5, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201E3D4
	str r4, [r5, #0x28]
_0201E3D4:
	ldr r0, [r5, #0x8]
	lsl r1, r0, #0x5
	ldr r0, [r5, #0x0]
	str r1, [r0, #0x8]
	add r0, r5, #0x0
	bl FUN_0201E4BC
	add r0, r5, #0x0
	bl FUN_0201E57C
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0201E3EC: .word 0x021C5998

	thumb_func_start FUN_0201E3F0
FUN_0201E3F0: ; 0x0201E3F0
	push {r4-r5}
	ldr r2, _0201E424 ; =0x021C5998
	mov r1, #0x0
	ldr r5, [r2, #0x0]
	ldr r2, [r5, #0x4]
	cmp r2, #0x0
	ble _0201E41C
	ldr r2, [r5, #0x0]
	add r4, r2, #0x0
_0201E402:
	ldr r3, [r4, #0xc]
	cmp r0, r3
	bne _0201E412
	mov r0, #0x30
	mul r0, r1
	add r0, r2, r0
	pop {r4-r5}
	bx lr
_0201E412:
	ldr r3, [r5, #0x4]
	add r1, r1, #0x1
	add r4, #0x30
	cmp r1, r3
	blt _0201E402
_0201E41C:
	mov r0, #0x0
	pop {r4-r5}
	bx lr
	nop
_0201E424: .word 0x021C5998

	thumb_func_start FUN_0201E428
FUN_0201E428: ; 0x0201E428
	push {r3-r4}
	ldr r1, _0201E460 ; =0x021C5998
	mov r0, #0x0
	ldr r4, [r1, #0x0]
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	ble _0201E458
	ldr r1, [r4, #0x0]
	add r3, r1, #0x0
_0201E43A:
	add r2, r3, #0x0
	add r2, #0x2c
	ldrb r2, [r2, #0x0]
	cmp r2, #0x0
	bne _0201E44E
	mov r2, #0x30
	mul r2, r0
	add r0, r1, r2
	pop {r3-r4}
	bx lr
_0201E44E:
	ldr r2, [r4, #0x4]
	add r0, r0, #0x1
	add r3, #0x30
	cmp r0, r2
	blt _0201E43A
_0201E458:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	nop
_0201E460: .word 0x021C5998

	thumb_func_start FUN_0201E464
FUN_0201E464: ; 0x0201E464
	push {r3, lr}
	bl GX_GetBankForOBJExtPltt
	cmp r0, #0x20
	beq _0201E472
	cmp r0, #0x40
	bne _0201E47E
_0201E472:
	ldr r0, _0201E4A8 ; =0x021C5998
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xc
	str r1, [r0, #0x1c]
	b _0201E486
_0201E47E:
	ldr r0, _0201E4A8 ; =0x021C5998
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x1c]
_0201E486:
	bl GX_GetBankForSubOBJExtPltt
	mov r1, #0x1
	lsl r1, r1, #0x8
	cmp r0, r1
	bne _0201E49C
	ldr r0, _0201E4A8 ; =0x021C5998
	lsl r1, r1, #0x5
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x20]
	pop {r3, pc}
_0201E49C:
	ldr r0, _0201E4A8 ; =0x021C5998
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x20]
	pop {r3, pc}
	nop
_0201E4A8: .word 0x021C5998

	thumb_func_start FUN_0201E4AC
FUN_0201E4AC: ; 0x0201E4AC
	ldr r1, [r0, #0x8]
	ldr r3, _0201E4B8 ; =FUN_0201E4BC
	lsl r2, r1, #0x5
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x8]
	bx r3
	.balign 4
_0201E4B8: .word FUN_0201E4BC

	thumb_func_start FUN_0201E4BC
FUN_0201E4BC: ; 0x0201E4BC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x10
	bl FUN_020B19DC
	ldr r0, [r4, #0x4]
	mov r2, #0x1
	tst r0, r2
	beq _0201E4DA
	add r3, r4, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x24]
	add r3, #0x10
	bl FUN_020B1240
_0201E4DA:
	ldr r0, [r4, #0x4]
	mov r2, #0x2
	tst r0, r2
	beq _0201E4EE
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x28]
	add r4, #0x10
	add r3, r4, #0x0
	bl FUN_020B1240
_0201E4EE:
	pop {r4, pc}

	thumb_func_start FUN_0201E4F0
FUN_0201E4F0: ; 0x0201E4F0
	push {r4-r7}
	mov r3, #0x0
	cmp r1, #0x0
	ble _0201E50E
	mov r5, #0x1
_0201E4FA:
	ldrh r7, [r0, #0x0]
	add r4, r2, r3
	add r6, r5, #0x0
	lsl r6, r4
	add r4, r7, #0x0
	orr r4, r6
	add r3, r3, #0x1
	strh r4, [r0, #0x0]
	cmp r3, r1
	blt _0201E4FA
_0201E50E:
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_0201E514
FUN_0201E514: ; 0x0201E514
	push {r4-r7}
	mov r4, #0x0
	cmp r1, #0x0
	ble _0201E530
	mov r6, #0x1
_0201E51E:
	add r5, r2, r4
	add r7, r6, #0x0
	ldrh r3, [r0, #0x0]
	lsl r7, r5
	bic r3, r7
	add r4, r4, #0x1
	strh r3, [r0, #0x0]
	cmp r4, r1
	blt _0201E51E
_0201E530:
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_0201E534
FUN_0201E534: ; 0x0201E534
	push {r4-r7}
	mov r3, #0x0
	mov r6, #0x1
	add r2, r3, #0x0
_0201E53C:
	add r4, r2, #0x0
	b _0201E546
_0201E540:
	cmp r5, #0x10
	bge _0201E554
	add r4, r4, #0x1
_0201E546:
	add r5, r3, r4
	add r7, r6, #0x0
	lsl r7, r5
	tst r7, r0
	bne _0201E554
	cmp r4, r1
	blt _0201E540
_0201E554:
	cmp r4, r1
	bge _0201E560
	add r3, r3, r4
	add r3, r3, #0x1
	cmp r3, #0x10
	blt _0201E53C
_0201E560:
	cmp r3, #0x10
	blt _0201E56C
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r7}
	bx lr
_0201E56C:
	lsl r0, r3, #0x5
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_0201E574
FUN_0201E574: ; 0x0201E574
	mov r1, #0x0
	strh r1, [r0, #0x24]
	strh r1, [r0, #0x26]
	bx lr

	thumb_func_start FUN_0201E57C
FUN_0201E57C: ; 0x0201E57C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201E598
	ldr r0, _0201E5B4 ; =0x021C5998
	ldr r2, [r4, #0x24]
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x8]
	add r0, #0x24
	lsr r2, r2, #0x5
	bl FUN_0201E4F0
_0201E598:
	ldr r1, [r4, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201E5B0
	ldr r0, _0201E5B4 ; =0x021C5998
	ldr r2, [r4, #0x28]
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x8]
	add r0, #0x26
	lsr r2, r2, #0x5
	bl FUN_0201E4F0
_0201E5B0:
	pop {r4, pc}
	nop
_0201E5B4: .word 0x021C5998

	thumb_func_start FUN_0201E5B8
FUN_0201E5B8: ; 0x0201E5B8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201E5D4
	ldr r0, _0201E5F0 ; =0x021C5998
	ldr r2, [r4, #0x24]
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x8]
	add r0, #0x24
	lsr r2, r2, #0x5
	bl FUN_0201E514
_0201E5D4:
	ldr r1, [r4, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201E5EC
	ldr r0, _0201E5F0 ; =0x021C5998
	ldr r2, [r4, #0x28]
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x8]
	add r0, #0x26
	lsr r2, r2, #0x5
	bl FUN_0201E514
_0201E5EC:
	pop {r4, pc}
	nop
_0201E5F0: .word 0x021C5998

	thumb_func_start FUN_0201E5F4
FUN_0201E5F4: ; 0x0201E5F4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	ldr r2, [r5, #0x4]
	mov r0, #0x1
	tst r2, r0
	beq _0201E61A
	ldr r2, [r5, #0x8]
	lsl r2, r2, #0x5
	add r2, r1, r2
	cmp r2, r3
	bls _0201E618
	bl ErrorHandling
	bl FUN_0201E0B8
	mov r0, #0x0
	b _0201E61A
_0201E618:
	str r1, [r5, #0x24]
_0201E61A:
	ldr r2, [r5, #0x4]
	mov r1, #0x2
	tst r1, r2
	beq _0201E63C
	ldr r1, [r5, #0x8]
	lsl r1, r1, #0x5
	add r2, r4, r1
	ldr r1, [sp, #0x10]
	cmp r2, r1
	bls _0201E63A
	bl ErrorHandling
	bl FUN_0201E0B8
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E63A:
	str r4, [r5, #0x28]
_0201E63C:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201E640
FUN_0201E640: ; 0x0201E640
	push {r3-r4}
	ldr r4, [r0, #0x4]
	mov r3, #0x1
	tst r3, r4
	beq _0201E654
	ldr r3, [r0, #0x8]
	ldr r4, [r1, #0x0]
	lsl r3, r3, #0x5
	add r3, r4, r3
	str r3, [r1, #0x0]
_0201E654:
	ldr r3, [r0, #0x4]
	mov r1, #0x2
	tst r1, r3
	beq _0201E666
	ldr r0, [r0, #0x8]
	ldr r1, [r2, #0x0]
	lsl r0, r0, #0x5
	add r0, r1, r0
	str r0, [r2, #0x0]
_0201E666:
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0201E66C
FUN_0201E66C: ; 0x0201E66C
	push {r4, lr}
	add r4, r0, #0x0
	bl GX_ResetBankForBG
	bl GX_ResetBankForBGExtPltt
	bl GX_ResetBankForSubBG
	bl FUN_020C6034
	bl GX_ResetBankForOBJ
	bl GX_ResetBankForOBJExtPltt
	bl FUN_020C605C
	bl GX_ResetBankForSubOBJ
	bl GX_ResetBankForTex
	bl GX_ResetBankForTexPltt
	ldr r0, [r4, #0x0]
	bl GX_SetBankForBG
	ldr r0, [r4, #0x4]
	bl GX_SetBankForBGExtPltt
	ldr r0, [r4, #0x8]
	bl GX_SetBankForSubBG
	ldr r0, [r4, #0xc]
	bl GX_SetBankForSubBGExtPltt
	ldr r0, [r4, #0x10]
	bl GX_SetBankForOBJ
	ldr r0, [r4, #0x14]
	bl GX_SetBankForOBJExtPltt
	ldr r0, [r4, #0x18]
	bl GX_SetBankForSubOBJ
	ldr r0, [r4, #0x1c]
	bl GX_SetBankForSubOBJExtPltt
	ldr r0, [r4, #0x20]
	bl GX_SetBankForTex
	ldr r0, [r4, #0x24]
	bl GX_SetBankForTexPltt
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201E6D8
FUN_0201E6D8: ; 0x0201E6D8
	ldr r0, _0201E6E0 ; =0x021C599C
	mov r1, #0x0
	str r1, [r0, #0x4]
	bx lr
	.balign 4
_0201E6E0: .word 0x021C599C

	thumb_func_start FUN_0201E6E4
FUN_0201E6E4: ; 0x0201E6E4
	cmp r1, #0x1
	bne _0201E6F2
	ldr r1, _0201E718 ; =0x021C599C
	ldr r1, [r1, #0x4]
	tst r1, r0
	beq _0201E6FA
	bx lr
_0201E6F2:
	ldr r1, _0201E718 ; =0x021C599C
	ldr r1, [r1, #0x4]
	tst r1, r0
	beq _0201E714
_0201E6FA:
	ldr r1, _0201E718 ; =0x021C599C
	ldr r2, [r1, #0x4]
	add r3, r2, #0x0
	eor r3, r0
	mov r2, #0x1
	lsl r2, r2, #0x1a
	str r3, [r1, #0x4]
	ldr r1, [r2, #0x0]
	ldr r0, _0201E71C ; =0xFFFFE0FF
	and r1, r0
	lsl r0, r3, #0x8
	orr r0, r1
	str r0, [r2, #0x0]
_0201E714:
	bx lr
	nop
_0201E718: .word 0x021C599C
_0201E71C: .word 0xFFFFE0FF

	thumb_func_start FUN_0201E720
FUN_0201E720: ; 0x0201E720
	ldr r1, _0201E738 ; =0x021C599C
	mov r3, #0x1
	str r0, [r1, #0x4]
	lsl r3, r3, #0x1a
	ldr r2, [r3, #0x0]
	ldr r1, _0201E73C ; =0xFFFFE0FF
	lsl r0, r0, #0x8
	and r1, r2
	orr r0, r1
	str r0, [r3, #0x0]
	bx lr
	nop
_0201E738: .word 0x021C599C
_0201E73C: .word 0xFFFFE0FF

	thumb_func_start FUN_0201E740
FUN_0201E740: ; 0x0201E740
	ldr r0, _0201E748 ; =0x021C599C
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_0201E748: .word 0x021C599C

	thumb_func_start FUN_0201E74C
FUN_0201E74C: ; 0x0201E74C
	cmp r1, #0x1
	bne _0201E75A
	ldr r1, _0201E77C ; =0x021C599C
	ldr r1, [r1, #0x0]
	tst r1, r0
	beq _0201E762
	bx lr
_0201E75A:
	ldr r1, _0201E77C ; =0x021C599C
	ldr r1, [r1, #0x0]
	tst r1, r0
	beq _0201E77A
_0201E762:
	ldr r1, _0201E77C ; =0x021C599C
	ldr r2, [r1, #0x0]
	add r3, r2, #0x0
	eor r3, r0
	ldr r2, _0201E780 ; =0x04001000
	str r3, [r1, #0x0]
	ldr r1, [r2, #0x0]
	ldr r0, _0201E784 ; =0xFFFFE0FF
	and r1, r0
	lsl r0, r3, #0x8
	orr r0, r1
	str r0, [r2, #0x0]
_0201E77A:
	bx lr
	.balign 4
_0201E77C: .word 0x021C599C
_0201E780: .word 0x04001000
_0201E784: .word 0xFFFFE0FF

	thumb_func_start FUN_0201E788
FUN_0201E788: ; 0x0201E788
	push {r3, lr}
	bl GX_DispOn
	ldr r2, _0201E79C ; =0x04001000
	mov r0, #0x1
	ldr r1, [r2, #0x0]
	lsl r0, r0, #0x10
	orr r0, r1
	str r0, [r2, #0x0]
	pop {r3, pc}
	.balign 4
_0201E79C: .word 0x04001000

	thumb_func_start FUN_0201E7A0
FUN_0201E7A0: ; 0x0201E7A0
	ldr r0, _0201E7C0 ; =0x021C4918
	ldr r2, _0201E7C4 ; =0x04000304
	ldrb r0, [r0, #0x5]
	cmp r0, #0x0
	bne _0201E7B4
	ldrh r1, [r2, #0x0]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2, #0x0]
	bx lr
_0201E7B4:
	ldrh r1, [r2, #0x0]
	ldr r0, _0201E7C8 ; =0xFFFF7FFF
	and r0, r1
	strh r0, [r2, #0x0]
	bx lr
	nop
_0201E7C0: .word 0x021C4918
_0201E7C4: .word 0x04000304
_0201E7C8: .word 0xFFFF7FFF

	thumb_func_start FUN_0201E7CC
FUN_0201E7CC: ; 0x0201E7CC
	ldr r0, _0201E7D4 ; =0x021C599C
	ldr r0, [r0, #0x4]
	bx lr
	nop
_0201E7D4: .word 0x021C599C

	thumb_func_start FUN_0201E7D8
FUN_0201E7D8: ; 0x0201E7D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x3e]
	ldr r2, [r5, #0x38]
	ldrh r4, [r5, #0x3c]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _0201E8B4 ; =0x020FFA38
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	asr r2, r4, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r3, r2, #0x1
	ldr r2, _0201E8B4 ; =0x020FFA38
	lsl r1, r1, #0x14
	ldrsh r2, [r2, r3]
	lsr r0, r0, #0xc
	orr r0, r1
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	str r1, [r5, #0x14]
	ldrh r0, [r5, #0x3e]
	ldr r2, [r5, #0x38]
	asr r0, r0, #0x4
	lsl r0, r0, #0x1
	add r0, r0, #0x1
	lsl r1, r0, #0x1
	ldr r0, _0201E8B4 ; =0x020FFA38
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	lsl r2, r2, #0xa
	mov r3, #0x0
	add r0, r0, r2
	adc r1, r3
	ldrh r2, [r5, #0x3c]
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	asr r2, r2, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r3, r2, #0x1
	ldr r2, _0201E8B4 ; =0x020FFA38
	orr r0, r1
	ldrsh r2, [r2, r3]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	neg r0, r4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r1, [r5, #0x1c]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _0201E8B4 ; =0x020FFA38
	ldr r2, [r5, #0x38]
	ldrsh r0, [r0, r1]
	asr r3, r2, #0x1f
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	add r0, r5, #0x0
	str r1, [r5, #0x18]
	add r0, #0x14
	add r5, #0x20
	add r1, r5, #0x0
	add r2, r0, #0x0
	bl VEC_Add
	pop {r3-r5, pc}
	nop
_0201E8B4: .word 0x020FFA38

	thumb_func_start FUN_0201E8B8
FUN_0201E8B8: ; 0x0201E8B8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x3e]
	ldr r2, [r5, #0x38]
	ldrh r4, [r5, #0x3c]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _0201E998 ; =0x020FFA38
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	asr r2, r4, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r3, r2, #0x1
	ldr r2, _0201E998 ; =0x020FFA38
	lsl r1, r1, #0x14
	ldrsh r2, [r2, r3]
	lsr r0, r0, #0xc
	orr r0, r1
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	neg r0, r1
	str r0, [r5, #0x20]
	ldrh r0, [r5, #0x3e]
	ldr r2, [r5, #0x38]
	asr r0, r0, #0x4
	lsl r0, r0, #0x1
	add r0, r0, #0x1
	lsl r1, r0, #0x1
	ldr r0, _0201E998 ; =0x020FFA38
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	lsl r2, r2, #0xa
	mov r3, #0x0
	add r0, r0, r2
	adc r1, r3
	ldrh r2, [r5, #0x3c]
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	asr r2, r2, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r3, r2, #0x1
	ldr r2, _0201E998 ; =0x020FFA38
	orr r0, r1
	ldrsh r2, [r2, r3]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	neg r0, r1
	str r0, [r5, #0x28]
	neg r0, r4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _0201E998 ; =0x020FFA38
	ldr r2, [r5, #0x38]
	ldrsh r0, [r0, r1]
	asr r3, r2, #0x1f
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	neg r0, r1
	str r0, [r5, #0x24]
	add r0, r5, #0x0
	add r0, #0x20
	add r5, #0x14
	add r1, r5, #0x0
	add r2, r0, #0x0
	bl VEC_Add
	pop {r3-r5, pc}
	.balign 4
_0201E998: .word 0x020FFA38

	thumb_func_start FUN_0201E99C
FUN_0201E99C: ; 0x0201E99C
	add r2, r1, #0x0
	add r2, #0x46
	strh r0, [r2, #0x0]
	asr r0, r0, #0x4
	lsl r3, r0, #0x1
	ldr r2, _0201E9E0 ; =0x020FFA38
	lsl r0, r3, #0x1
	ldrsh r0, [r2, r0]
	str r0, [r1, #0x0]
	add r0, r3, #0x1
	lsl r0, r0, #0x1
	ldrsh r0, [r2, r0]
	mov r2, #0x0
	str r0, [r1, #0x4]
	ldr r0, _0201E9E4 ; =0x00001555
	str r0, [r1, #0x8]
	mov r0, #0x96
	lsl r0, r0, #0xc
	str r0, [r1, #0xc]
	mov r0, #0xe1
	lsl r0, r0, #0xe
	str r0, [r1, #0x10]
	mov r0, #0x1
	str r2, [r1, #0x2c]
	lsl r0, r0, #0xc
	str r0, [r1, #0x30]
	str r2, [r1, #0x34]
	str r2, [r1, #0x54]
	str r2, [r1, #0x58]
	str r2, [r1, #0x5c]
	str r2, [r1, #0x60]
	str r2, [r1, #0x64]
	bx lr
	nop
_0201E9E0: .word 0x020FFA38
_0201E9E4: .word 0x00001555

	thumb_func_start FUN_0201E9E8
FUN_0201E9E8: ; 0x0201E9E8
	ldr r2, [r0, #0x58]
	cmp r2, #0x0
	bne _0201E9F2
	mov r2, #0x0
	str r2, [r1, #0x0]
_0201E9F2:
	ldr r2, [r0, #0x5c]
	cmp r2, #0x0
	bne _0201E9FC
	mov r2, #0x0
	str r2, [r1, #0x4]
_0201E9FC:
	ldr r0, [r0, #0x60]
	cmp r0, #0x0
	bne _0201EA06
	mov r0, #0x0
	str r0, [r1, #0x8]
_0201EA06:
	bx lr

	thumb_func_start FUN_0201EA08
FUN_0201EA08: ; 0x0201EA08
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r7, [r5, #0x64]
	add r4, r1, #0x0
	add r6, r2, #0x0
	cmp r7, #0x0
	bne _0201EA20
	ldmia r4!, {r0-r1}
	stmia r6!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r6, #0x0]
	pop {r3-r7, pc}
_0201EA20:
	add r0, r7, #0x0
	str r0, [sp, #0x0]
	add r0, #0x8
	str r0, [sp, #0x0]
	ldr r0, [r7, #0x10]
	cmp r0, #0x0
	bne _0201EA48
	add r3, r4, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldr r0, [r5, #0x64]
	ldr r2, [r7, #0x4]
	ldr r1, [r0, #0xc]
	cmp r2, r1
	bne _0201EA5C
	mov r1, #0x1
	str r1, [r0, #0x10]
	b _0201EA5C
_0201EA48:
	ldr r2, [r7, #0x4]
	mov r1, #0xc
	mul r1, r2
	ldr r0, [r7, #0x20]
	add r2, r6, #0x0
	add r3, r0, r1
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
_0201EA5C:
	ldr r1, [r5, #0x64]
	ldr r0, [r7, #0x4]
	ldr r1, [r1, #0x0]
	add r0, r0, #0x1
	bl _s32_div_f
	str r1, [r7, #0x4]
	ldr r1, [sp, #0x0]
	ldr r0, [r5, #0x64]
	ldr r2, [r1, #0x0]
	mov r1, #0xc
	ldr r0, [r0, #0x20]
	mul r1, r2
	add r3, r4, #0x0
	add r2, r0, r1
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldr r0, [sp, #0x0]
	ldr r1, [r5, #0x64]
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0x0]
	add r0, r0, #0x1
	bl _s32_div_f
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x0]
	ldr r0, [r5, #0x64]
	ldr r0, [r0, #0x14]
	cmp r0, #0x0
	bne _0201EAA0
	ldr r0, [r4, #0x0]
	str r0, [r6, #0x0]
_0201EAA0:
	ldr r0, [r5, #0x64]
	ldr r0, [r0, #0x18]
	cmp r0, #0x0
	bne _0201EAAC
	ldr r0, [r4, #0x4]
	str r0, [r6, #0x4]
_0201EAAC:
	ldr r0, [r5, #0x64]
	ldr r0, [r0, #0x1c]
	cmp r0, #0x0
	bne _0201EAB8
	ldr r0, [r4, #0x8]
	str r0, [r6, #0x8]
_0201EAB8:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201EABC
FUN_0201EABC: ; 0x0201EABC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [sp, #0x18]
	add r7, r1, #0x0
	str r0, [sp, #0x18]
	ldr r0, [r0, #0x54]
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	cmp r0, #0x0
	beq _0201EB46
	add r0, r7, #0x1
	cmp r0, r5
	ble _0201EADA
	bl ErrorHandling
_0201EADA:
	ldr r0, [sp, #0x0]
	mov r1, #0x24
	bl FUN_02016998
	add r4, r0, #0x0
	mov r1, #0xc
	ldr r0, [sp, #0x0]
	mul r1, r5
	bl FUN_02016998
	mov r1, #0x0
	str r0, [r4, #0x20]
	cmp r5, #0x0
	ble _0201EB12
	add r2, r1, #0x0
	add r0, r1, #0x0
_0201EAFA:
	ldr r3, [r4, #0x20]
	add r1, r1, #0x1
	str r0, [r3, r2]
	ldr r3, [r4, #0x20]
	add r3, r3, r2
	str r0, [r3, #0x4]
	ldr r3, [r4, #0x20]
	add r3, r3, r2
	str r0, [r3, #0x8]
	add r2, #0xc
	cmp r1, r5
	blt _0201EAFA
_0201EB12:
	str r5, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	str r7, [r4, #0x8]
	str r7, [r4, #0xc]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	mov r0, #0x1
	add r1, r6, #0x0
	tst r1, r0
	beq _0201EB2E
	str r0, [r4, #0x14]
_0201EB2E:
	mov r0, #0x2
	tst r0, r6
	beq _0201EB38
	mov r0, #0x1
	str r0, [r4, #0x18]
_0201EB38:
	mov r0, #0x4
	tst r0, r6
	beq _0201EB42
	mov r0, #0x1
	str r0, [r4, #0x1c]
_0201EB42:
	ldr r0, [sp, #0x18]
	str r4, [r0, #0x64]
_0201EB46:
	pop {r3-r7, pc}

	thumb_func_start FUN_0201EB48
FUN_0201EB48: ; 0x0201EB48
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x64]
	cmp r0, #0x0
	beq _0201EB62
	ldr r0, [r0, #0x20]
	bl FUN_02016A18
	ldr r0, [r4, #0x64]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x64]
_0201EB62:
	pop {r4, pc}

	thumb_func_start FUN_0201EB64
FUN_0201EB64: ; 0x0201EB64
	ldr r3, _0201EB6C ; =FUN_02016998
	mov r1, #0x68
	bx r3
	nop
_0201EB6C: .word FUN_02016998

	thumb_func_start FUN_0201EB70
FUN_0201EB70: ; 0x0201EB70
	ldr r3, _0201EB74 ; =FUN_02016A18
	bx r3
	.balign 4
_0201EB74: .word FUN_02016A18

	thumb_func_start FUN_0201EB78
FUN_0201EB78: ; 0x0201EB78
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0xd
_0201EB80:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0201EB80
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201EB8C
FUN_0201EB8C: ; 0x0201EB8C
	ldr r1, _0201EB94 ; =0x021C59A4
	str r0, [r1, #0x0]
	bx lr
	nop
_0201EB94: .word 0x021C59A4

	thumb_func_start FUN_0201EB98
FUN_0201EB98: ; 0x0201EB98
	ldr r0, _0201EBA0 ; =0x021C59A4
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_0201EBA0: .word 0x021C59A4

	thumb_func_start FUN_0201EBA4
FUN_0201EBA4: ; 0x0201EBA4
	push {r3-r6, lr}
	sub sp, #0x1c
	ldr r0, _0201EC40 ; =0x021C59A4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0201EC3A
	ldr r0, [r1, #0x54]
	cmp r0, #0x0
	beq _0201EBEE
	add r1, #0x48
	add r2, sp, #0x10
	bl VEC_Subtract
	ldr r0, _0201EC40 ; =0x021C59A4
	add r1, sp, #0x10
	ldr r0, [r0, #0x0]
	bl FUN_0201E9E8
	ldr r0, _0201EC40 ; =0x021C59A4
	add r1, sp, #0x10
	ldr r0, [r0, #0x0]
	add r2, sp, #0x4
	bl FUN_0201EA08
	ldr r1, _0201EC40 ; =0x021C59A4
	add r0, sp, #0x4
	ldr r1, [r1, #0x0]
	bl FUN_0201EF70
	ldr r0, _0201EC40 ; =0x021C59A4
	ldr r3, [r0, #0x0]
	ldr r2, [r3, #0x54]
	add r3, #0x48
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
_0201EBEE:
	ldr r0, _0201EC40 ; =0x021C59A4
	ldr r5, _0201EC44 ; =0x021CEF58
	ldr r4, [r0, #0x0]
	add r3, r4, #0x0
	add r2, r4, #0x0
	add r4, #0x14
	add r6, r4, #0x0
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r2, #0x2c
	str r0, [r5, #0x0]
	add r6, r2, #0x0
	ldr r5, _0201EC48 ; =0x021CEF64
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r3, #0x20
	str r0, [r5, #0x0]
	add r6, r3, #0x0
	ldr r5, _0201EC4C ; =0x021CEF70
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r1, r2, #0x0
	str r0, [r5, #0x0]
	ldr r0, _0201EC50 ; =0x021CED64
	add r2, r3, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl G3i_LookAt_
	ldr r1, _0201EC54 ; =0x021CED98
	mov r0, #0xe8
	ldr r2, [r1, #0x7c]
	bic r2, r0
	str r2, [r1, #0x7c]
_0201EC3A:
	add sp, #0x1c
	pop {r3-r6, pc}
	nop
_0201EC40: .word 0x021C59A4
_0201EC44: .word 0x021CEF58
_0201EC48: .word 0x021CEF64
_0201EC4C: .word 0x021CEF70
_0201EC50: .word 0x021CED64
_0201EC54: .word 0x021CED98

	thumb_func_start FUN_0201EC58
FUN_0201EC58: ; 0x0201EC58
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x2c
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_0201EC68
FUN_0201EC68: ; 0x0201EC68
	push {r3-r4}
	add r3, r1, #0x0
	add r4, r0, #0x0
	str r4, [r3, #0x54]
	add r2, r3, #0x0
	ldmia r4!, {r0-r1}
	add r2, #0x48
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r2, #0x0]
	mov r0, #0x1
	str r0, [r3, #0x58]
	str r0, [r3, #0x5c]
	str r0, [r3, #0x60]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201EC88
FUN_0201EC88: ; 0x0201EC88
	mov r1, #0x0
	str r1, [r0, #0x54]
	str r1, [r0, #0x58]
	str r1, [r0, #0x5c]
	str r1, [r0, #0x60]
	bx lr

	thumb_func_start FUN_0201EC94
FUN_0201EC94: ; 0x0201EC94
	str r0, [r2, #0xc]
	add r0, r2, #0x0
	str r1, [r2, #0x10]
	add r0, #0x44
	ldr r3, _0201ECA4 ; =FUN_0201EE2C
	ldrb r0, [r0, #0x0]
	add r1, r2, #0x0
	bx r3
	.balign 4
_0201ECA4: .word FUN_0201EE2C

	thumb_func_start FUN_0201ECA8
FUN_0201ECA8: ; 0x0201ECA8
	push {r3-r7, lr}
	ldr r4, [sp, #0x20]
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r0, r3, #0x0
	add r1, r4, #0x0
	add r6, r2, #0x0
	bl FUN_0201E99C
	add r3, r5, #0x0
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x20
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	str r7, [r4, #0x38]
	ldrh r0, [r6, #0x0]
	strh r0, [r4, #0x3c]
	ldrh r0, [r6, #0x2]
	strh r0, [r4, #0x3e]
	add r0, r4, #0x0
	ldrh r1, [r6, #0x4]
	add r0, #0x40
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	ldrh r1, [r6, #0x6]
	add r0, #0x42
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0201E7D8
	add r0, sp, #0x8
	ldrb r0, [r0, #0x10]
	add r1, r4, #0x0
	bl FUN_0201EE2C
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	beq _0201ED0E
	str r5, [r4, #0x54]
	add r2, r4, #0x0
	ldmia r5!, {r0-r1}
	add r2, #0x48
	stmia r2!, {r0-r1}
	ldr r0, [r5, #0x0]
	str r0, [r2, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x58]
	str r0, [r4, #0x5c]
	str r0, [r4, #0x60]
_0201ED0E:
	pop {r3-r7, pc}

	thumb_func_start FUN_0201ED10
FUN_0201ED10: ; 0x0201ED10
	push {r3-r7, lr}
	ldr r4, [sp, #0x1c]
	add r6, r0, #0x0
	add r7, r1, #0x0
	add r0, r3, #0x0
	add r1, r4, #0x0
	add r5, r2, #0x0
	bl FUN_0201E99C
	add r2, r4, #0x0
	ldmia r6!, {r0-r1}
	add r2, #0x14
	stmia r2!, {r0-r1}
	ldr r0, [r6, #0x0]
	str r0, [r2, #0x0]
	str r7, [r4, #0x38]
	ldrh r0, [r5, #0x0]
	strh r0, [r4, #0x3c]
	ldrh r0, [r5, #0x2]
	strh r0, [r4, #0x3e]
	add r0, r4, #0x0
	ldrh r1, [r5, #0x4]
	add r0, #0x40
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	ldrh r1, [r5, #0x6]
	add r0, #0x42
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0201E8B8
	add r0, sp, #0x8
	ldrb r0, [r0, #0x10]
	add r1, r4, #0x0
	bl FUN_0201EE2C
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201ED5C
FUN_0201ED5C: ; 0x0201ED5C
	push {r4-r7, lr}
	sub sp, #0x3c
	ldr r4, [sp, #0x54]
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r2, #0x0
	add r1, r4, #0x0
	add r7, r3, #0x0
	bl FUN_0201E99C
	add r3, r5, #0x0
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x20
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r3, r6, #0x0
	str r0, [r2, #0x0]
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x14
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r1, r5, #0x0
	str r0, [r2, #0x0]
	add r0, r6, #0x0
	add r2, sp, #0x30
	bl VEC_Subtract
	add r0, sp, #0x30
	bl VEC_Mag
	str r0, [r4, #0x38]
	mov r6, #0x0
	add r0, sp, #0x24
	str r6, [r0, #0x0]
	str r6, [r0, #0x4]
	str r6, [r0, #0x8]
	add r0, sp, #0x18
	str r6, [r0, #0x0]
	str r6, [r0, #0x4]
	str r6, [r0, #0x8]
	add r0, sp, #0xc
	str r6, [r0, #0x0]
	str r6, [r0, #0x4]
	str r6, [r0, #0x8]
	mov r0, #0x1
	lsl r0, r0, #0xc
	add r3, sp, #0x30
	str r0, [sp, #0x8]
	ldmia r3!, {r0-r1}
	add r2, sp, #0xc
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r6, [sp, #0x0]
	str r0, [r2, #0x0]
	str r6, [sp, #0x4]
	str r6, [sp, #0x10]
	add r0, sp, #0x0
	add r1, sp, #0xc
	bl FUN_0201C7B0
	strh r0, [r4, #0x3e]
	add r1, r6, #0x0
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x38]
	str r1, [sp, #0x4]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x34]
	str r1, [sp, #0x8]
	str r0, [sp, #0x14]
	str r1, [sp, #0x10]
	add r0, sp, #0x0
	add r1, sp, #0xc
	bl FUN_0201C7B0
	strh r0, [r4, #0x3c]
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r0, #0x40
	strh r1, [r0, #0x0]
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_0201EE2C
	ldr r0, [sp, #0x50]
	cmp r0, #0x0
	beq _0201EE26
	str r5, [r4, #0x54]
	add r2, r4, #0x0
	ldmia r5!, {r0-r1}
	add r2, #0x48
	stmia r2!, {r0-r1}
	ldr r0, [r5, #0x0]
	str r0, [r2, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x58]
	str r0, [r4, #0x5c]
	str r0, [r4, #0x60]
_0201EE26:
	add sp, #0x3c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0201EE2C
FUN_0201EE2C: ; 0x0201EE2C
	push {r3-r6, lr}
	sub sp, #0x14
	add r5, r1, #0x0
	cmp r0, #0x0
	bne _0201EE6C
	ldr r0, [r5, #0x10]
	str r0, [sp, #0x0]
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r0, _0201EEE4 ; =0x021CED20
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	ldr r3, [r5, #0xc]
	bl G3i_PerspectiveW_
	ldr r1, _0201EEE8 ; =0x021CED98
	mov r0, #0x50
	ldr r2, [r1, #0x7c]
	add r5, #0x44
	bic r2, r0
	str r2, [r1, #0x7c]
	mov r1, #0x0
	ldr r0, _0201EEEC ; =0x02105BB8
	strb r1, [r5, #0x0]
	str r1, [r0, #0x0]
	add sp, #0x14
	pop {r3-r6, pc}
_0201EE6C:
	ldr r4, [r5, #0x38]
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	bl FX_Div
	asr r1, r0, #0x1f
	asr r3, r4, #0x1f
	add r2, r4, #0x0
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsr r4, r2, #0xc
	lsl r0, r1, #0x14
	orr r4, r0
	ldr r2, [r5, #0x8]
	asr r1, r4, #0x1f
	add r0, r4, #0x0
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r6, #0x2
	mov r2, #0x0
	lsl r6, r6, #0xa
	add r3, r0, r6
	adc r1, r2
	lsl r0, r1, #0x14
	lsr r3, r3, #0xc
	orr r3, r0
	ldr r0, [r5, #0xc]
	neg r1, r4
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x10]
	str r0, [sp, #0x4]
	lsl r0, r6, #0x1
	str r0, [sp, #0x8]
	str r2, [sp, #0xc]
	ldr r0, _0201EEE4 ; =0x021CED20
	neg r2, r3
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	bl G3i_OrthoW_
	ldr r1, _0201EEE8 ; =0x021CED98
	mov r0, #0x50
	ldr r2, [r1, #0x7c]
	add r5, #0x44
	bic r2, r0
	str r2, [r1, #0x7c]
	mov r0, #0x1
	strb r0, [r5, #0x0]
	ldr r0, _0201EEEC ; =0x02105BB8
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, #0x14
	pop {r3-r6, pc}
	nop
_0201EEE4: .word 0x021CED20
_0201EEE8: .word 0x021CED98
_0201EEEC: .word 0x02105BB8

	thumb_func_start FUN_0201EEF0
FUN_0201EEF0: ; 0x0201EEF0
	add r2, r1, #0x0
	add r2, #0x46
	strh r0, [r2, #0x0]
	add r0, r1, #0x0
	add r0, #0x46
	ldrh r0, [r0, #0x0]
	ldr r3, _0201EF24 ; =FUN_0201EE2C
	asr r0, r0, #0x4
	lsl r2, r0, #0x2
	ldr r0, _0201EF28 ; =0x020FFA38
	ldrsh r2, [r0, r2]
	str r2, [r1, #0x0]
	add r2, r1, #0x0
	add r2, #0x46
	ldrh r2, [r2, #0x0]
	asr r2, r2, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r0, [r0, r2]
	str r0, [r1, #0x4]
	add r0, r1, #0x0
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	bx r3
	nop
_0201EF24: .word FUN_0201EE2C
_0201EF28: .word 0x020FFA38

	thumb_func_start FUN_0201EF2C
FUN_0201EF2C: ; 0x0201EF2C
	add r2, r1, #0x0
	add r2, #0x46
	ldrh r2, [r2, #0x0]
	ldr r3, _0201EF68 ; =FUN_0201EE2C
	add r2, r2, r0
	add r0, r1, #0x0
	add r0, #0x46
	strh r2, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0x46
	ldrh r0, [r0, #0x0]
	asr r0, r0, #0x4
	lsl r2, r0, #0x2
	ldr r0, _0201EF6C ; =0x020FFA38
	ldrsh r2, [r0, r2]
	str r2, [r1, #0x0]
	add r2, r1, #0x0
	add r2, #0x46
	ldrh r2, [r2, #0x0]
	asr r2, r2, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r0, [r0, r2]
	str r0, [r1, #0x4]
	add r0, r1, #0x0
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	bx r3
	nop
_0201EF68: .word FUN_0201EE2C
_0201EF6C: .word 0x020FFA38

	thumb_func_start FUN_0201EF70
FUN_0201EF70: ; 0x0201EF70
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x14
	add r1, r5, #0x0
	add r2, r0, #0x0
	bl VEC_Add
	add r4, #0x20
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl VEC_Add
	pop {r3-r5, pc}

	thumb_func_start FUN_0201EF90
FUN_0201EF90: ; 0x0201EF90
	ldrh r2, [r0, #0x0]
	strh r2, [r1, #0x3c]
	ldrh r2, [r0, #0x2]
	strh r2, [r1, #0x3e]
	add r2, r1, #0x0
	ldrh r3, [r0, #0x4]
	add r2, #0x40
	strh r3, [r2, #0x0]
	ldrh r2, [r0, #0x6]
	add r0, r1, #0x0
	add r0, #0x42
	strh r2, [r0, #0x0]
	ldr r3, _0201EFB0 ; =FUN_0201E7D8
	add r0, r1, #0x0
	bx r3
	nop
_0201EFB0: .word FUN_0201E7D8

	thumb_func_start FUN_0201EFB4
FUN_0201EFB4: ; 0x0201EFB4
	ldrh r3, [r1, #0x3c]
	ldrh r2, [r0, #0x0]
	add r2, r3, r2
	strh r2, [r1, #0x3c]
	ldrh r3, [r1, #0x3e]
	ldrh r2, [r0, #0x2]
	add r2, r3, r2
	strh r2, [r1, #0x3e]
	add r2, r1, #0x0
	add r2, #0x40
	ldrh r2, [r2, #0x0]
	ldrh r0, [r0, #0x4]
	ldr r3, _0201EFDC ; =FUN_0201E8B8
	add r2, r2, r0
	add r0, r1, #0x0
	add r0, #0x40
	strh r2, [r0, #0x0]
	add r0, r1, #0x0
	bx r3
	nop
_0201EFDC: .word FUN_0201E8B8

	thumb_func_start FUN_0201EFE0
FUN_0201EFE0: ; 0x0201EFE0
	ldr r3, _0201EFE8 ; =FUN_0201E7D8
	str r0, [r1, #0x38]
	add r0, r1, #0x0
	bx r3
	.balign 4
_0201EFE8: .word FUN_0201E7D8

	thumb_func_start FUN_0201EFEC
FUN_0201EFEC: ; 0x0201EFEC
	push {r4, lr}
	add r3, r1, #0x0
	add r4, r0, #0x0
	add r2, r3, #0x0
	ldmia r4!, {r0-r1}
	add r2, #0x20
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r2, #0x0]
	add r0, r3, #0x0
	bl FUN_0201E7D8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201F008
FUN_0201F008: ; 0x0201F008
	add r0, #0x46
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0201F010
FUN_0201F010: ; 0x0201F010
	ldr r0, [r0, #0x38]
	bx lr

	thumb_func_start FUN_0201F014
FUN_0201F014: ; 0x0201F014
	ldrh r2, [r1, #0x3c]
	strh r2, [r0, #0x0]
	ldrh r2, [r1, #0x3e]
	strh r2, [r0, #0x2]
	add r2, r1, #0x0
	add r2, #0x40
	ldrh r2, [r2, #0x0]
	add r1, #0x42
	strh r2, [r0, #0x4]
	ldrh r1, [r1, #0x0]
	strh r1, [r0, #0x6]
	bx lr

	thumb_func_start FUN_0201F02C
FUN_0201F02C: ; 0x0201F02C
	add r2, r1, #0x0
	add r2, #0x20
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start FUN_0201F03C
FUN_0201F03C: ; 0x0201F03C
	add r2, r1, #0x0
	add r2, #0x14
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start FUN_0201F04C
FUN_0201F04C: ; 0x0201F04C
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x20
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_0201F05C
FUN_0201F05C: ; 0x0201F05C
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x14
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_0201F06C
FUN_0201F06C: ; 0x0201F06C
	mov r2, #0x0
	strb r2, [r0, #0x0]
	strb r2, [r0, #0x1]
	str r2, [r0, #0x4]
	add r1, r0, #0x0
	str r2, [r0, #0x8]
	add r1, #0xc4
	str r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0xc8
	str r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0xcc
	str r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0xd0
	str r2, [r1, #0x0]
	strb r2, [r0, #0x3]
	bx lr
	.balign 4

	thumb_func_start FUN_0201F094
FUN_0201F094: ; 0x0201F094
	mov r3, #0x0
	str r3, [r0, #0x1c]
	str r3, [r0, #0x20]
	str r3, [r0, #0x78]
	add r1, r0, #0x0
	str r3, [r0, #0x7c]
	add r1, #0x80
	str r3, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x84
	add r2, r0, #0x0
	str r3, [r1, #0x0]
	add r2, #0x94
	mov r1, #0x10
_0201F0B0:
	strb r3, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _0201F0B0
	add r2, r0, #0x0
	mov r1, #0x0
	add r2, #0x88
	str r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0x8c
	str r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0x90
	str r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xa4
	str r1, [r2, #0x0]
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	mov r2, #0x1
	str r1, [r0, #0x8]
	lsl r2, r2, #0xc
	str r2, [r0, #0xc]
	str r2, [r0, #0x10]
	str r2, [r0, #0x14]
	add r2, r0, #0x0
	add r2, #0xaa
	strh r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xa8
	strb r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xb0
	str r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xb4
	str r1, [r2, #0x0]
	strb r1, [r0, #0x18]
	bx lr
	.balign 4

	thumb_func_start FUN_0201F100
FUN_0201F100: ; 0x0201F100
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, _0201F13C ; =0x021C59A8
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201F112
	bl ErrorHandling
_0201F112:
	mov r1, #0xd4
	add r0, r4, #0x0
	mul r1, r6
	bl FUN_02016998
	ldr r7, _0201F13C ; =0x021C59A8
	mov r4, #0x0
	str r0, [r7, #0x0]
	str r6, [r7, #0x4]
	cmp r6, #0x0
	ble _0201F13A
	add r5, r4, #0x0
_0201F12A:
	ldr r0, [r7, #0x0]
	add r0, r0, r5
	bl FUN_0201F06C
	add r4, r4, #0x1
	add r5, #0xd4
	cmp r4, r6
	blt _0201F12A
_0201F13A:
	pop {r3-r7, pc}
	.balign 4
_0201F13C: .word 0x021C59A8

	thumb_func_start FUN_0201F140
FUN_0201F140: ; 0x0201F140
	push {r4-r6, lr}
	ldr r6, _0201F174 ; =0x021C59A8
	mov r4, #0x0
	ldr r0, [r6, #0x4]
	cmp r0, #0x0
	ble _0201F160
	add r5, r4, #0x0
_0201F14E:
	ldr r0, [r6, #0x0]
	add r0, r0, r5
	bl FUN_0201F23C
	ldr r0, [r6, #0x4]
	add r4, r4, #0x1
	add r5, #0xd4
	cmp r4, r0
	blt _0201F14E
_0201F160:
	ldr r0, _0201F174 ; =0x021C59A8
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _0201F174 ; =0x021C59A8
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	pop {r4-r6, pc}
	nop
_0201F174: .word 0x021C59A8

	thumb_func_start FUN_0201F178
FUN_0201F178: ; 0x0201F178
	push {r3-r7, lr}
	ldr r6, _0201F1B0 ; =0x021C59A8
	mov r4, #0x0
	ldr r0, [r6, #0x4]
	cmp r0, #0x0
	ble _0201F1AC
	add r5, r4, #0x0
	mov r7, #0x2
_0201F188:
	ldr r0, [r6, #0x0]
	add r0, r0, r5
	ldrb r1, [r0, #0x1]
	cmp r1, #0x1
	bne _0201F196
	bl FUN_0201F318
_0201F196:
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	ldrb r0, [r1, #0x3]
	cmp r0, #0x1
	bne _0201F1A2
	strb r7, [r1, #0x3]
_0201F1A2:
	ldr r0, [r6, #0x4]
	add r4, r4, #0x1
	add r5, #0xd4
	cmp r4, r0
	blt _0201F188
_0201F1AC:
	pop {r3-r7, pc}
	nop
_0201F1B0: .word 0x021C59A8

	thumb_func_start FUN_0201F1B4
FUN_0201F1B4: ; 0x0201F1B4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0201F2E4
	add r4, r0, #0x0
	bne _0201F1C8
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0201F1C8:
	mov r0, #0x1
	strb r0, [r4, #0x0]
	strb r0, [r4, #0x1]
	ldr r2, [r5, #0x0]
	mov r1, #0xb8
	ldr r0, [r5, #0x4]
	mul r1, r2
	bl FUN_02016998
	str r0, [r4, #0x4]
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x8]
	add r0, r4, #0x0
	add r0, #0xc
	bl FUN_0201F094
	add r1, r4, #0x0
	add r0, r4, #0x0
	add r1, #0xc
	add r0, #0xbc
	str r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0xc0
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x0]
	ldr r0, [r5, #0x4]
	lsl r1, r1, #0x2
	bl FUN_02016998
	add r1, r4, #0x0
	add r1, #0xc4
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_0201FABC
	ldr r0, [r5, #0x4]
	mov r1, #0x10
	bl FUN_02016998
	add r1, r4, #0x0
	add r1, #0xcc
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0xcc
	ldr r0, [r0, #0x0]
	ldr r1, [r5, #0x4]
	mov r2, #0x4
	bl FUN_02016B20
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	bl FUN_0201C360
	add r1, r4, #0x0
	add r1, #0xd0
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0201F23C
FUN_0201F23C: ; 0x0201F23C
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F24A
	bl ErrorHandling
	mov r0, #0x0
	pop {r4, pc}
_0201F24A:
	ldrb r1, [r4, #0x0]
	cmp r1, #0x0
	beq _0201F27E
	bl FUN_0201F284
	ldr r0, [r4, #0x4]
	bl FUN_02016A18
	add r0, r4, #0x0
	add r0, #0xc4
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	add r0, #0xcc
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	bl FUN_0201C39C
	add r0, r4, #0x0
	bl FUN_0201F06C
_0201F27E:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201F284
FUN_0201F284: ; 0x0201F284
	push {r3-r5, lr}
	cmp r0, #0x0
	bne _0201F294
	bne _0201F290
	bl ErrorHandling
_0201F290:
	mov r0, #0x0
	pop {r3-r5, pc}
_0201F294:
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0201F2BA
	add r1, r0, #0x0
	add r1, #0xbc
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	add r4, #0xc
	cmp r1, r4
	beq _0201F2BA
_0201F2A8:
	add r0, r1, #0x0
	add r0, #0xb0
	ldr r5, [r0, #0x0]
	add r0, r1, #0x0
	bl FUN_0201F744
	add r1, r5, #0x0
	cmp r5, r4
	bne _0201F2A8
_0201F2BA:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201F2C0
FUN_0201F2C0: ; 0x0201F2C0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F2CA
	bl ErrorHandling
_0201F2CA:
	ldrb r0, [r4, #0x3]
	cmp r0, #0x0
	bne _0201F2D4
	mov r0, #0x0
	pop {r4, pc}
_0201F2D4:
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0201F2D8
FUN_0201F2D8: ; 0x0201F2D8
	ldrb r1, [r0, #0x3]
	cmp r1, #0x2
	bne _0201F2E2
	mov r1, #0x0
	strb r1, [r0, #0x3]
_0201F2E2:
	bx lr

	thumb_func_start FUN_0201F2E4
FUN_0201F2E4: ; 0x0201F2E4
	push {r3-r4}
	ldr r0, _0201F314 ; =0x021C59A8
	mov r1, #0x0
	ldr r3, [r0, #0x4]
	cmp r3, #0x0
	ble _0201F30C
	ldr r4, [r0, #0x0]
	add r2, r4, #0x0
_0201F2F4:
	ldrb r0, [r2, #0x0]
	cmp r0, #0x0
	bne _0201F304
	mov r0, #0xd4
	mul r0, r1
	add r0, r4, r0
	pop {r3-r4}
	bx lr
_0201F304:
	add r1, r1, #0x1
	add r2, #0xd4
	cmp r1, r3
	blt _0201F2F4
_0201F30C:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	nop
_0201F314: .word 0x021C59A8

	thumb_func_start FUN_0201F318
FUN_0201F318: ; 0x0201F318
	push {r3-r6, lr}
	sub sp, #0x24
	add r5, r0, #0x0
	bne _0201F324
	bl ErrorHandling
_0201F324:
	add r0, sp, #0x0
	bl MTX_Identity33_
	add r0, r5, #0x0
	add r0, #0xbc
	ldr r4, [r0, #0x0]
	add r5, #0xc
	cmp r4, r5
	beq _0201F37E
	add r6, sp, #0x0
_0201F338:
	ldrb r0, [r4, #0x18]
	cmp r0, #0x1
	bne _0201F376
	add r0, r4, #0x0
	bl FUN_0201FC54
	add r0, r4, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	bne _0201F356
	add r0, r4, #0x0
	bl FUN_0201F90C
	b _0201F360
_0201F356:
	cmp r0, #0x2
	bne _0201F360
	add r0, r4, #0x0
	bl FUN_0201F8F0
_0201F360:
	add r0, r4, #0x0
	add r3, r4, #0x0
	add r0, #0x24
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, #0xc
	bl FUN_0201B26C
	add r0, r4, #0x0
	bl FUN_0201FC70
_0201F376:
	add r4, #0xb0
	ldr r4, [r4, #0x0]
	cmp r4, r5
	bne _0201F338
_0201F37E:
	add sp, #0x24
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_0201F384
FUN_0201F384: ; 0x0201F384
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r6, [r5, #0x1c]
	add r4, r1, #0x0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0201F5B8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201F5D4
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0201F648
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0201F3BA
	add r6, #0xc
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0201FB58
_0201F3BA:
	add r0, r5, #0x0
	mov r1, #0x2
	add r0, #0xa8
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	str r0, [r5, #0x20]
	add r0, r5, #0x0
	add r0, #0xaa
	strh r1, [r0, #0x0]
	add r5, #0xac
	str r1, [r5, #0x0]
	pop {r4-r6, pc}

	thumb_func_start FUN_0201F3D4
FUN_0201F3D4: ; 0x0201F3D4
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r6, [r5, #0x1c]
	add r4, r1, #0x0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0201F5B8
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0201F3FE
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r0, #0x88
	add r1, #0x8c
	add r2, #0x90
	bl FUN_0201F524
_0201F3FE:
	add r0, r5, #0x0
	ldr r1, [r4, #0x1c]
	add r0, #0x88
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	ldr r1, [r4, #0x20]
	add r0, #0x8c
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	ldr r1, [r4, #0x24]
	add r0, #0x90
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201F69C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201F6C8
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0201F43A
	add r6, #0xc
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0201FB58
_0201F43A:
	add r0, r5, #0x0
	mov r1, #0x3
	add r0, #0xa8
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	str r0, [r5, #0x20]
	add r0, r5, #0x0
	add r0, #0xaa
	strh r1, [r0, #0x0]
	add r5, #0xac
	str r1, [r5, #0x0]
	pop {r4-r6, pc}

	thumb_func_start FUN_0201F454
FUN_0201F454: ; 0x0201F454
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_020B7E1C
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl FUN_020B7E10
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_020B7CE4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _0201F492
	ldr r3, _0201F4E4 ; =0x021064B8
	mov r1, #0x0
	ldr r3, [r3, #0x0]
	add r2, r1, #0x0
	blx r3
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0201F496
	bl ErrorHandling
	b _0201F496
_0201F492:
	mov r0, #0x0
	str r0, [r4, #0x0]
_0201F496:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0201F4B2
	ldr r3, _0201F4E4 ; =0x021064B8
	mov r1, #0x1
	ldr r3, [r3, #0x0]
	mov r2, #0x0
	blx r3
	str r0, [r6, #0x0]
	cmp r0, #0x0
	bne _0201F4B6
	bl ErrorHandling
	b _0201F4B6
_0201F4B2:
	mov r0, #0x0
	str r0, [r6, #0x0]
_0201F4B6:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _0201F4DA
	ldr r3, _0201F4E8 ; =0x021064C0
	mov r1, #0x2
	ldrh r2, [r5, #0x20]
	lsl r1, r1, #0xe
	ldr r3, [r3, #0x0]
	and r1, r2
	mov r2, #0x0
	blx r3
	str r0, [r7, #0x0]
	cmp r0, #0x0
	bne _0201F4DE
	bl ErrorHandling
	add sp, #0xc
	pop {r4-r7, pc}
_0201F4DA:
	mov r0, #0x0
	str r0, [r7, #0x0]
_0201F4DE:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_0201F4E4: .word 0x021064B8
_0201F4E8: .word 0x021064C0

	thumb_func_start FUN_0201F4EC
FUN_0201F4EC: ; 0x0201F4EC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r3, #0x0
	bl FUN_020B7CF0
	add r0, r5, #0x0
	bl FUN_020B7C58
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201F500
FUN_0201F500: ; 0x0201F500
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, [r2, #0x0]
	ldr r2, [r3, #0x0]
	add r5, r0, #0x0
	bl FUN_020B7DFC
	ldr r1, [sp, #0x10]
	add r0, r5, #0x0
	ldr r1, [r1, #0x0]
	bl FUN_020B7CDC
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020B7790
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201F524
FUN_0201F524: ; 0x0201F524
	push {r3-r5, lr}
	ldr r0, [r0, #0x0]
	add r5, r1, #0x0
	add r4, r2, #0x0
	cmp r0, #0x0
	beq _0201F536
	ldr r1, _0201F550 ; =0x021064BC
	ldr r1, [r1, #0x0]
	blx r1
_0201F536:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0201F542
	ldr r1, _0201F550 ; =0x021064BC
	ldr r1, [r1, #0x0]
	blx r1
_0201F542:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0201F54E
	ldr r1, _0201F554 ; =0x021064C4
	ldr r1, [r1, #0x0]
	blx r1
_0201F54E:
	pop {r3-r5, pc}
	.balign 4
_0201F550: .word 0x021064BC
_0201F554: .word 0x021064C4

	thumb_func_start FUN_0201F558
FUN_0201F558: ; 0x0201F558
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x0
	beq _0201F568
	cmp r5, #0x0
	bne _0201F56E
_0201F568:
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0201F56E:
	bl FUN_020B7E1C
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_020B7E10
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_020B7CE4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020B7E1C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020B7E10
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020B7CE4
	ldr r1, [sp, #0x0]
	cmp r1, r6
	bne _0201F5AA
	ldr r1, [sp, #0x4]
	cmp r1, r7
	bne _0201F5AA
	cmp r4, r0
	beq _0201F5B0
_0201F5AA:
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0201F5B0:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201F5B8
FUN_0201F5B8: ; 0x0201F5B8
	push {r4, lr}
	add r4, r1, #0x0
	add r0, r4, #0x0
	add r0, #0xa4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201F5D0
	bl FUN_0201C40C
	mov r0, #0x0
	add r4, #0xa4
	str r0, [r4, #0x0]
_0201F5D0:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201F5D4
FUN_0201F5D4: ; 0x0201F5D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	add r0, r1, #0x0
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r1, #0x7c
	add r2, #0x80
	bl FUN_0201FB9C
	str r0, [r5, #0x78]
	add r0, r5, #0x0
	ldr r1, [r5, #0x7c]
	add r0, #0x24
	bl FUN_020B80B4
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	beq _0201F60E
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_0201F558
	b _0201F610
_0201F60E:
	mov r0, #0x0
_0201F610:
	cmp r0, #0x0
	bne _0201F644
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0201F62E
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r0, #0x88
	add r1, #0x8c
	add r2, #0x90
	bl FUN_0201F524
_0201F62E:
	add r0, r5, #0x0
	add r0, #0x80
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r5, #0x90
	ldr r0, [r0, #0x0]
	add r1, #0x88
	add r2, #0x8c
	add r3, r5, #0x0
	bl FUN_0201F454
_0201F644:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201F648
FUN_0201F648: ; 0x0201F648
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r2, #0x0
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r0, r4, #0x0
	bl FUN_0201FBCC
	add r1, r5, #0x0
	add r1, #0x84
	add r3, r5, #0x0
	add r3, #0x94
	str r0, [r1, #0x0]
	add r4, #0xc
	add r2, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r5, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	add r1, r2, #0x0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r0, #0xac
	ldr r0, [r0, #0x0]
	add r2, r5, #0x0
	add r3, r5, #0x0
	str r0, [sp, #0x4]
	add r6, #0xd0
	add r2, #0x84
	add r3, #0x88
	ldr r0, [r6, #0x0]
	ldr r2, [r2, #0x0]
	ldr r3, [r3, #0x0]
	bl FUN_0201C3B4
	add r5, #0xa4
	str r0, [r5, #0x0]
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_0201F69C
FUN_0201F69C: ; 0x0201F69C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r0, r4, #0x0
	add r1, #0x7c
	add r2, #0x80
	bl FUN_0201FB9C
	str r0, [r5, #0x78]
	add r0, r5, #0x0
	ldr r1, [r5, #0x7c]
	add r0, #0x24
	bl FUN_020B80B4
	add r0, r4, #0x0
	bl FUN_0201FBCC
	add r5, #0x84
	str r0, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201F6C8
FUN_0201F6C8: ; 0x0201F6C8
	push {r3-r4}
	add r4, r0, #0x0
	add r2, r4, #0x0
	add r3, r1, #0x0
	add r3, #0xc
	add r2, #0x94
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0x0
	add r4, #0xa4
	str r0, [r4, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0201F6E8
FUN_0201F6E8: ; 0x0201F6E8
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r6, [r5, #0x0]
	cmp r6, #0x0
	bne _0201F6F6
	mov r0, #0x0
	pop {r4-r6, pc}
_0201F6F6:
	add r0, r6, #0x0
	bl FUN_0201FAF4
	add r4, r0, #0x0
	bne _0201F704
	mov r0, #0x0
	pop {r4-r6, pc}
_0201F704:
	add r3, r5, #0x0
	str r6, [r4, #0x1c]
	add r3, #0x8
	ldmia r3!, {r0-r1}
	add r2, r4, #0x0
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r3, r5, #0x0
	str r0, [r2, #0x0]
	add r3, #0x14
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0xc
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	mov r1, #0x0
	str r0, [r2, #0x0]
	add r0, r4, #0x0
	add r0, #0xaa
	strh r1, [r0, #0x0]
	mov r1, #0x1
	add r0, r4, #0x0
	strb r1, [r4, #0x18]
	add r0, #0xa8
	strb r1, [r0, #0x0]
	ldr r1, [r5, #0x4]
	add r0, r4, #0x0
	bl FUN_0201FBD8
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0201F744
FUN_0201F744: ; 0x0201F744
	push {r3-r5, lr}
	add r5, r0, #0x0
	bne _0201F74E
	bl ErrorHandling
_0201F74E:
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0201F75C
	bl ErrorHandling
_0201F75C:
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	ldr r4, [r5, #0x1c]
	cmp r0, #0x0
	bne _0201F76C
	mov r0, #0x0
	pop {r3-r5, pc}
_0201F76C:
	add r0, r5, #0x0
	bl FUN_0201FB7C
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0201F78C
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r0, #0x88
	add r1, #0x8c
	add r2, #0x90
	bl FUN_0201F524
_0201F78C:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0201F5B8
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0201FB20
	mov r0, #0x1
	strb r0, [r4, #0x3]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201F7A4
FUN_0201F7A4: ; 0x0201F7A4
	push {r3-r4}
	add r4, r0, #0x0
	str r1, [r4, #0x0]
	str r2, [r4, #0x4]
	str r3, [r4, #0x8]
	ldr r3, [sp, #0x8]
	add r2, r4, #0x0
	add r2, #0xc
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0x0
	str r0, [r4, #0x1c]
	str r0, [r4, #0x20]
	str r0, [r4, #0x24]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201F7C8
FUN_0201F7C8: ; 0x0201F7C8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x0
	bne _0201F7D6
	bl ErrorHandling
_0201F7D6:
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201F7E0
FUN_0201F7E0: ; 0x0201F7E0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F7EA
	bl ErrorHandling
_0201F7EA:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201F7F0
FUN_0201F7F0: ; 0x0201F7F0
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x0
	bne _0201F7FE
	bl ErrorHandling
_0201F7FE:
	ldmia r5!, {r0-r1}
	add r4, #0xc
	stmia r4!, {r0-r1}
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201F80C
FUN_0201F80C: ; 0x0201F80C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0201F81A
	bl ErrorHandling
_0201F81A:
	strb r4, [r5, #0x18]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201F820
FUN_0201F820: ; 0x0201F820
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F82A
	bl ErrorHandling
_0201F82A:
	ldrb r0, [r4, #0x18]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201F830
FUN_0201F830: ; 0x0201F830
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0201F83E
	bl ErrorHandling
_0201F83E:
	add r5, #0xaa
	strh r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201F844
FUN_0201F844: ; 0x0201F844
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F84E
	bl ErrorHandling
_0201F84E:
	add r4, #0xaa
	ldrh r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_0201F854
FUN_0201F854: ; 0x0201F854
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0201F862
	bl ErrorHandling
_0201F862:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201FBFC
	pop {r3-r5, pc}

	thumb_func_start FUN_0201F86C
FUN_0201F86C: ; 0x0201F86C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0201F87A
	bl ErrorHandling
_0201F87A:
	add r5, #0xac
	str r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201F880
FUN_0201F880: ; 0x0201F880
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F88A
	bl ErrorHandling
_0201F88A:
	add r4, #0xac
	ldr r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_0201F890
FUN_0201F890: ; 0x0201F890
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0201F89E
	bl ErrorHandling
_0201F89E:
	add r1, r5, #0x0
	add r1, #0xaa
	ldrh r1, [r1, #0x0]
	add r0, r5, #0x0
	bl FUN_0201FBEC
	add r1, r5, #0x0
	add r1, #0xac
	str r0, [r1, #0x0]
	add r0, r5, #0x0
	add r0, #0xac
	ldr r0, [r0, #0x0]
	add r5, #0xac
	add r0, r0, r4
	str r0, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201F8C0
FUN_0201F8C0: ; 0x0201F8C0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F8CA
	bl ErrorHandling
_0201F8CA:
	add r1, r4, #0x0
	add r1, #0xaa
	ldrh r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_0201FBEC
	add r4, #0xac
	ldr r1, [r4, #0x0]
	sub r0, r1, r0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201F8E0
FUN_0201F8E0: ; 0x0201F8E0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F8EA
	bl ErrorHandling
_0201F8EA:
	ldr r0, [r4, #0x7c]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201F8F0
FUN_0201F8F0: ; 0x0201F8F0
	push {r3, lr}
	add r1, r0, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0201F90A
	add r0, r1, #0x0
	add r0, #0xa4
	add r1, #0xac
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0x0]
	bl FUN_0201C438
_0201F90A:
	pop {r3, pc}

	thumb_func_start FUN_0201F90C
FUN_0201F90C: ; 0x0201F90C
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0xac
	ldr r1, [r1, #0x0]
	add r0, #0x94
	lsl r1, r1, #0x4
	lsr r1, r1, #0x10
	bl FUN_02022244
	add r2, sp, #0x0
	strb r0, [r2, #0x0]
	lsr r0, r0, #0x8
	strb r0, [r2, #0x1]
	ldrb r0, [r2, #0x0]
	add r1, r4, #0x0
	add r1, #0x84
	strb r0, [r2, #0x2]
	ldrb r0, [r2, #0x1]
	strb r0, [r2, #0x3]
	ldrb r2, [r2, #0x2]
	ldr r0, [r4, #0x7c]
	ldr r1, [r1, #0x0]
	bl FUN_0201F954
	add r2, sp, #0x0
	ldr r0, [r4, #0x7c]
	add r4, #0x84
	ldrb r2, [r2, #0x3]
	ldr r1, [r4, #0x0]
	bl FUN_0201FA04
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201F954
FUN_0201F954: ; 0x0201F954
	push {r3-r7, lr}
	ldr r3, [r0, #0x8]
	mov r5, #0x0
	add r6, r0, r3
	ldrh r0, [r0, r3]
	add r3, r1, #0x0
	add r1, #0x42
	ldrh r1, [r1, #0x0]
	add r3, #0x3c
	add r4, r6, r0
	add r0, r3, r1
	ldrh r1, [r3, r1]
	mul r2, r1
	add r0, r0, r2
	ldr r0, [r0, #0x4]
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	ldrb r0, [r4, #0x1]
	cmp r0, #0x0
	ble _0201F9A2
_0201F97C:
	ldrh r0, [r4, #0x6]
	add r1, r4, r0
	ldrh r0, [r4, r0]
	add r2, r1, #0x4
	add r1, r0, #0x0
	mul r1, r5
	add r1, r2, r1
	ldrb r2, [r1, #0x3]
	mov r0, #0x1
	tst r0, r2
	beq _0201F99A
	add r0, r6, #0x0
	add r2, r7, #0x0
	bl FUN_0201F9A4
_0201F99A:
	ldrb r0, [r4, #0x1]
	add r5, r5, #0x1
	cmp r5, r0
	blt _0201F97C
_0201F9A2:
	pop {r3-r7, pc}

	thumb_func_start FUN_0201F9A4
FUN_0201F9A4: ; 0x0201F9A4
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	add r0, r1, #0x0
	ldrh r0, [r0, #0x0]
	str r1, [sp, #0x0]
	add r7, r2, #0x0
	add r0, r6, r0
	str r0, [sp, #0x4]
	add r0, r1, #0x0
	ldrb r0, [r0, #0x2]
	mov r4, #0x0
	cmp r0, #0x0
	ble _0201F9FC
	add r0, r6, #0x4
	str r0, [sp, #0x8]
_0201F9C4:
	ldrh r2, [r6, #0xa]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x8]
	add r0, r0, r2
	ldrh r2, [r1, r2]
	ldr r1, [sp, #0x4]
	ldrb r1, [r1, r4]
	mul r1, r2
	add r0, r0, r1
	ldr r0, [r0, #0x4]
	add r5, r6, r0
	ldr r0, [r5, #0x14]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r1, r0, r7
	ldr r0, _0201FA00 ; =0x0000FFFF
	cmp r1, r0
	bls _0201F9EC
	bl ErrorHandling
_0201F9EC:
	ldr r0, [r5, #0x14]
	add r4, r4, #0x1
	add r0, r0, r7
	str r0, [r5, #0x14]
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, #0x2]
	cmp r4, r0
	blt _0201F9C4
_0201F9FC:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0201FA00: .word 0x0000FFFF

	thumb_func_start FUN_0201FA04
FUN_0201FA04: ; 0x0201FA04
	push {r3-r7, lr}
	ldr r3, [r0, #0x8]
	add r7, r0, r3
	ldrh r0, [r7, #0x2]
	add r4, r7, r0
	ldrh r0, [r1, #0x34]
	add r5, r1, r0
	ldrh r0, [r5, #0x6]
	add r1, r5, r0
	ldrh r0, [r5, r0]
	add r3, r1, #0x4
	add r1, r0, #0x0
	mul r1, r2
	add r0, r3, r1
	ldrh r6, [r3, r1]
	ldrh r1, [r0, #0x2]
	mov r0, #0x1
	tst r0, r1
	bne _0201FA2C
	lsr r6, r6, #0x1
_0201FA2C:
	ldrb r0, [r4, #0x1]
	mov r5, #0x0
	cmp r0, #0x0
	bls _0201FA5A
_0201FA34:
	ldrh r0, [r4, #0x6]
	add r1, r4, r0
	ldrh r0, [r4, r0]
	add r2, r1, #0x4
	add r1, r0, #0x0
	mul r1, r5
	add r1, r2, r1
	ldrb r2, [r1, #0x3]
	mov r0, #0x1
	tst r0, r2
	beq _0201FA52
	add r0, r7, #0x0
	add r2, r6, #0x0
	bl FUN_0201FA5C
_0201FA52:
	ldrb r0, [r4, #0x1]
	add r5, r5, #0x1
	cmp r5, r0
	blo _0201FA34
_0201FA5A:
	pop {r3-r7, pc}

	thumb_func_start FUN_0201FA5C
FUN_0201FA5C: ; 0x0201FA5C
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	add r0, r1, #0x0
	ldrh r0, [r0, #0x0]
	str r1, [sp, #0x0]
	add r7, r2, #0x0
	add r0, r6, r0
	str r0, [sp, #0x4]
	add r0, r1, #0x0
	ldrb r0, [r0, #0x2]
	mov r4, #0x0
	cmp r0, #0x0
	bls _0201FAB4
	add r0, r6, #0x4
	str r0, [sp, #0x8]
_0201FA7C:
	ldrh r2, [r6, #0xa]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x8]
	add r0, r0, r2
	ldrh r2, [r1, r2]
	ldr r1, [sp, #0x4]
	ldrb r1, [r1, r4]
	mul r1, r2
	add r0, r0, r1
	ldr r0, [r0, #0x4]
	add r5, r6, r0
	ldrh r1, [r5, #0x1c]
	ldr r0, _0201FAB8 ; =0x00001FFF
	and r0, r1
	add r1, r0, r7
	ldr r0, _0201FAB8 ; =0x00001FFF
	cmp r1, r0
	bls _0201FAA4
	bl ErrorHandling
_0201FAA4:
	ldrh r0, [r5, #0x1c]
	add r4, r4, #0x1
	add r0, r0, r7
	strh r0, [r5, #0x1c]
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, #0x2]
	cmp r4, r0
	blo _0201FA7C
_0201FAB4:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0201FAB8: .word 0x00001FFF

	thumb_func_start FUN_0201FABC
FUN_0201FABC: ; 0x0201FABC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0201FAEC
	add r4, r7, #0x0
	add r6, r7, #0x0
_0201FACC:
	ldr r0, [r5, #0x4]
	add r0, r0, r4
	bl FUN_0201F094
	ldr r0, [r5, #0x4]
	add r7, r7, #0x1
	add r1, r0, r4
	add r0, r5, #0x0
	add r0, #0xc4
	ldr r0, [r0, #0x0]
	add r4, #0xb8
	str r1, [r0, r6]
	ldr r0, [r5, #0x8]
	add r6, r6, #0x4
	cmp r7, r0
	blt _0201FACC
_0201FAEC:
	mov r0, #0x0
	add r5, #0xc8
	str r0, [r5, #0x0]
	pop {r3-r7, pc}

	thumb_func_start FUN_0201FAF4
FUN_0201FAF4: ; 0x0201FAF4
	add r1, r0, #0x0
	add r1, #0xc8
	ldr r3, [r1, #0x0]
	ldr r1, [r0, #0x8]
	cmp r3, r1
	blt _0201FB04
	mov r0, #0x0
	bx lr
_0201FB04:
	add r1, r0, #0x0
	add r1, #0xc4
	ldr r2, [r1, #0x0]
	lsl r1, r3, #0x2
	ldr r2, [r2, r1]
	add r1, r0, #0x0
	add r1, #0xc8
	ldr r1, [r1, #0x0]
	add r0, #0xc8
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0201FB20
FUN_0201FB20: ; 0x0201FB20
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0xc8
	ldr r0, [r0, #0x0]
	add r4, r1, #0x0
	cmp r0, #0x0
	bgt _0201FB32
	mov r0, #0x0
	pop {r3-r5, pc}
_0201FB32:
	add r0, r4, #0x0
	bl FUN_0201F094
	add r0, r5, #0x0
	add r0, #0xc8
	ldr r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r5, #0x0
	add r0, #0xc8
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0xc4
	add r5, #0xc8
	ldr r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	lsl r0, r0, #0x2
	str r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0201FB58
FUN_0201FB58: ; 0x0201FB58
	add r2, r0, #0x0
	add r2, #0xb4
	ldr r3, [r2, #0x0]
	add r2, r1, #0x0
	add r2, #0xb4
	str r3, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xb4
	ldr r2, [r2, #0x0]
	add r2, #0xb0
	str r1, [r2, #0x0]
	add r2, r1, #0x0
	add r2, #0xb0
	str r0, [r2, #0x0]
	add r0, #0xb4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0201FB7C
FUN_0201FB7C: ; 0x0201FB7C
	add r1, r0, #0x0
	add r1, #0xb0
	ldr r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0xb4
	ldr r1, [r1, #0x0]
	add r1, #0xb0
	str r2, [r1, #0x0]
	add r1, r0, #0x0
	add r0, #0xb0
	add r1, #0xb4
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0x0]
	add r0, #0xb4
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0201FB9C
FUN_0201FB9C: ; 0x0201FB9C
	push {r3-r7, lr}
	add r6, r1, #0x0
	mov r1, #0x0
	add r5, r2, #0x0
	bl FUN_0201FC90
	add r7, r0, #0x0
	bl FUN_020BC13C
	add r4, r0, #0x0
	ldrh r0, [r4, #0xe]
	add r0, r4, r0
	ldr r0, [r0, #0xc]
	add r0, r4, r0
	str r0, [r6, #0x0]
	cmp r5, #0x0
	beq _0201FBC6
	add r0, r7, #0x0
	bl FUN_020BC0FC
	str r0, [r5, #0x0]
_0201FBC6:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201FBCC
FUN_0201FBCC: ; 0x0201FBCC
	ldr r3, _0201FBD4 ; =FUN_0201FC90
	mov r1, #0x1
	bx r3
	nop
_0201FBD4: .word FUN_0201FC90

	thumb_func_start FUN_0201FBD8
FUN_0201FBD8: ; 0x0201FBD8
	push {r3, lr}
	ldr r2, [r1, #0x1c]
	cmp r2, #0x0
	bne _0201FBE6
	bl FUN_0201F384
	pop {r3, pc}
_0201FBE6:
	bl FUN_0201F3D4
	pop {r3, pc}

	thumb_func_start FUN_0201FBEC
FUN_0201FBEC: ; 0x0201FBEC
	push {r3, lr}
	ldr r0, [r0, #0x20]
	bl FUN_0201FCA8
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201FBFC
FUN_0201FBFC: ; 0x0201FBFC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x0
	add r1, #0xaa
	ldrh r1, [r1, #0x0]
	ldr r0, [r5, #0x20]
	bl FUN_0201FCA8
	add r5, #0xac
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0201FC1C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201FC1C
FUN_0201FC1C: ; 0x0201FC1C
	push {r3-r6}
	ldr r4, [r0, #0x0]
	ldr r6, [r1, #0x0]
	lsl r4, r4, #0xc
	mov r3, #0x0
	cmp r4, r6
	bgt _0201FC32
	ldr r5, [r0, #0x4]
	lsl r5, r5, #0xc
	cmp r5, r6
	bge _0201FC36
_0201FC32:
	str r4, [r1, #0x0]
	b _0201FC4E
_0201FC36:
	add r2, r6, r2
	cmp r5, r2
	bge _0201FC4C
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	bne _0201FC46
	str r4, [r1, #0x0]
	b _0201FC4E
_0201FC46:
	mov r3, #0x1
	str r5, [r1, #0x0]
	b _0201FC4E
_0201FC4C:
	str r2, [r1, #0x0]
_0201FC4E:
	add r0, r3, #0x0
	pop {r3-r6}
	bx lr

	thumb_func_start FUN_0201FC54
FUN_0201FC54: ; 0x0201FC54
	push {r3, lr}
	add r3, r0, #0x0
	add r0, #0x90
	str r0, [sp, #0x0]
	add r0, r3, #0x0
	add r0, #0x80
	add r2, r3, #0x0
	ldr r1, [r3, #0x78]
	ldr r0, [r0, #0x0]
	add r2, #0x88
	add r3, #0x8c
	bl FUN_0201F500
	pop {r3, pc}

	thumb_func_start FUN_0201FC70
FUN_0201FC70: ; 0x0201FC70
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r0, [r4, #0x78]
	bl FUN_020B772C
	add r4, #0x80
	ldr r0, [r4, #0x0]
	add r1, sp, #0x4
	add r2, sp, #0x8
	add r3, sp, #0x0
	bl FUN_0201F4EC
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201FC90
FUN_0201FC90: ; 0x0201FC90
	cmp r1, #0x0
	beq _0201FC9A
	cmp r1, #0x1
	beq _0201FC9E
	b _0201FCA2
_0201FC9A:
	ldr r0, [r0, #0x0]
	bx lr
_0201FC9E:
	ldr r0, [r0, #0x4]
	bx lr
_0201FCA2:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0201FCA8
FUN_0201FCA8: ; 0x0201FCA8
	mov r2, #0xc
	mul r2, r1
	add r0, r0, r2
	bx lr

	thumb_func_start FUN_0201FCB0
FUN_0201FCB0: ; 0x0201FCB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bne _0201FCBA
	bl ErrorHandling
_0201FCBA:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _0201FCC4
	bl ErrorHandling
_0201FCC4:
	mov r1, #0x49
	ldr r0, [r5, #0x8]
	lsl r1, r1, #0x2
	bl FUN_02016998
	add r4, r0, #0x0
	bne _0201FCD6
	bl ErrorHandling
_0201FCD6:
	add r0, r4, #0x0
	bl FUN_0201FE44
	ldr r2, [r5, #0x0]
	ldr r0, [r5, #0x8]
	lsl r1, r2, #0x6
	add r1, r2, r1
	lsl r1, r1, #0x2
	bl FUN_02016998
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0201FCF4
	bl ErrorHandling
_0201FCF4:
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x4]
	ldr r1, [r5, #0x0]
	ldr r0, [r5, #0x8]
	lsl r1, r1, #0x2
	bl FUN_02016998
	str r0, [r4, #0x8]
	cmp r0, #0x0
	bne _0201FD0C
	bl ErrorHandling
_0201FD0C:
	add r0, r4, #0x0
	bl FUN_0202083C
	add r0, r4, #0x0
	add r0, #0x10
	bl FUN_0201FE6C
	add r2, r4, #0x0
	mov r1, #0x43
	lsl r1, r1, #0x2
	add r2, #0x10
	str r2, [r4, r1]
	add r0, r1, #0x4
	str r2, [r4, r0]
	ldr r0, [r5, #0x4]
	add r1, #0x8
	str r0, [r4, r1]
	ldr r0, [r5, #0x8]
	ldr r1, _0201FD54 ; =0x02105BBC
	bl FUN_020161A4
	mov r1, #0x46
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	add r1, r4, r1
	bl thunk_FUN_020afda0_2
	mov r0, #0x12
	mov r1, #0x1
	lsl r0, r0, #0x4
	str r1, [r4, r0]
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_0201FD54: .word 0x02105BBC

	thumb_func_start FUN_0201FD58
FUN_0201FD58: ; 0x0201FD58
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201FD62
	mov r0, #0x0
	pop {r4, pc}
_0201FD62:
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	bne _0201FD6C
	mov r0, #0x1
	pop {r4, pc}
_0201FD6C:
	bl FUN_0201FDB4
	mov r0, #0x46
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02016A18
	ldr r0, [r4, #0x8]
	bl FUN_02016A18
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_0201FE44
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201FD98
FUN_0201FD98: ; 0x0201FD98
	cmp r0, #0x0
	bne _0201FDA0
	mov r0, #0x0
	bx lr
_0201FDA0:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	bne _0201FDAA
	mov r0, #0x0
	bx lr
_0201FDAA:
	mov r2, #0x12
	lsl r2, r2, #0x4
	str r1, [r0, r2]
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0201FDB4
FUN_0201FDB4: ; 0x0201FDB4
	push {r4-r6, lr}
	cmp r0, #0x0
	bne _0201FDBE
	mov r0, #0x0
	pop {r4-r6, pc}
_0201FDBE:
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	bne _0201FDC8
	mov r0, #0x1
	pop {r4-r6, pc}
_0201FDC8:
	mov r1, #0x11
	lsl r1, r1, #0x4
	add r4, r0, #0x0
	ldr r1, [r0, r1]
	add r4, #0x10
	cmp r1, r4
	beq _0201FDE8
	mov r6, #0x1
	lsl r6, r6, #0x8
_0201FDDA:
	ldr r5, [r1, r6]
	add r0, r1, #0x0
	bl FUN_0201FFC8
	add r1, r5, #0x0
	cmp r5, r4
	bne _0201FDDA
_0201FDE8:
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_0201FDEC
FUN_0201FDEC: ; 0x0201FDEC
	push {r3-r7, lr}
	add r5, r0, #0x0
	bne _0201FDF6
	bl ErrorHandling
_0201FDF6:
	mov r0, #0x12
	lsl r0, r0, #0x4
	ldr r1, [r5, r0]
	cmp r1, #0x0
	beq _0201FE38
	sub r0, #0x10
	add r6, r5, #0x0
	ldr r4, [r5, r0]
	add r6, #0x10
	cmp r4, r6
	beq _0201FE38
	ldr r7, _0201FE3C ; =0x020EE658
_0201FE0E:
	add r2, r4, #0x0
	add r2, #0x34
	ldrb r2, [r2, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	ldr r2, [r7, r2]
	blx r2
	add r1, r4, #0x0
	add r1, #0x35
	ldrb r1, [r1, #0x0]
	add r0, r4, #0x0
	lsl r2, r1, #0x2
	ldr r1, _0201FE40 ; =0x020EE660
	ldr r1, [r1, r2]
	blx r1
	mov r0, #0x1
	lsl r0, r0, #0x8
	ldr r4, [r4, r0]
	cmp r4, r6
	bne _0201FE0E
_0201FE38:
	pop {r3-r7, pc}
	nop
_0201FE3C: .word 0x020EE658
_0201FE40: .word 0x020EE660

	thumb_func_start FUN_0201FE44
FUN_0201FE44: ; 0x0201FE44
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	str r1, [r4, #0x0]
	str r1, [r4, #0x4]
	str r1, [r4, #0x8]
	mov r0, #0x45
	str r1, [r4, #0xc]
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, r4, #0x0
	add r0, #0x10
	bl FUN_0201FE6C
	mov r0, #0x12
	mov r1, #0x0
	lsl r0, r0, #0x4
	str r1, [r4, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201FE6C
FUN_0201FE6C: ; 0x0201FE6C
	push {r4, lr}
	mov r2, #0x41
	add r4, r0, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	str r1, [r4, #0x3c]
	bl Call_FillMemWithValue
	add r0, r4, #0x0
	add r0, #0xb4
	bl FUN_020B1A24
	add r0, r4, #0x0
	add r0, #0xd8
	bl FUN_020B19DC
	mov r0, #0x0
	str r0, [r4, #0x30]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201FE94
FUN_0201FE94: ; 0x0201FE94
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02020874
	add r4, r0, #0x0
	bne _0201FEA6
	mov r0, #0x0
	pop {r4-r6, pc}
_0201FEA6:
	ldr r0, [r5, #0x0]
	add r6, r5, #0x0
	str r0, [r4, #0x3c]
	add r0, r4, #0x0
	mov r2, #0x0
	add r0, #0xf0
	add r6, #0x8
	strh r2, [r0, #0x0]
	ldmia r6!, {r0-r1}
	add r3, r4, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r6, r5, #0x0
	str r0, [r3, #0x0]
	add r6, #0x14
	add r3, r4, #0x0
	ldmia r6!, {r0-r1}
	add r3, #0x18
	stmia r3!, {r0-r1}
	ldr r0, [r6, #0x0]
	str r0, [r3, #0x0]
	ldrh r0, [r5, #0x20]
	strh r0, [r4, #0x24]
	add r0, r4, #0x0
	ldr r1, [r5, #0x28]
	add r0, #0xf8
	str r1, [r0, #0x0]
	add r0, r4, #0x0
	ldr r1, [r5, #0x24]
	add r0, #0xf4
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x26
	strb r2, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x27
	strb r2, [r0, #0x0]
	str r2, [r4, #0x2c]
	add r0, r4, #0x0
	str r2, [r4, #0x30]
	mov r1, #0x11
	add r0, #0x28
	strb r1, [r0, #0x0]
	mov r0, #0x45
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	add r1, r4, #0x0
	add r1, #0x26
	ldrb r1, [r1, #0x0]
	bl FUN_020B502C
	add r0, r4, #0x0
	add r0, #0x27
	ldrb r2, [r0, #0x0]
	mov r0, #0x45
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	mov r1, #0x1
	mov r3, #0x2
	and r1, r2
	and r2, r3
	bl FUN_020B4F38
	add r0, r4, #0x0
	mov r2, #0x1
	add r0, #0x34
	strb r2, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x35
	strb r1, [r0, #0x0]
	lsl r0, r2, #0xd
	str r0, [r4, #0x38]
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	ldr r3, [r5, #0x2c]
	add r2, r4, #0x0
	bl FUN_02020434
	cmp r0, #0x0
	bne _0201FF56
	add r0, r4, #0x0
	bl FUN_0201FFC8
	mov r0, #0x0
	pop {r4-r6, pc}
_0201FF56:
	add r1, r4, #0x0
	add r1, #0xf8
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	add r0, #0xd8
	bl FUN_020205E8
	add r1, r4, #0x0
	add r1, #0x2a
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x2a
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x29
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02020788
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0201FF84
FUN_0201FF84: ; 0x0201FF84
	push {r4, lr}
	sub sp, #0x30
	add r2, r0, #0x0
	ldr r0, [r2, #0x0]
	add r4, r2, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r2, #0x4]
	add r4, #0x8
	str r0, [sp, #0x4]
	ldmia r4!, {r0-r1}
	add r3, sp, #0x8
	stmia r3!, {r0-r1}
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	str r0, [r3, #0x0]
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	add r0, sp, #0x0
	strh r1, [r0, #0x20]
	ldr r0, [r2, #0x14]
	str r0, [sp, #0x24]
	ldr r0, [r2, #0x18]
	str r0, [sp, #0x28]
	ldr r0, [r2, #0x1c]
	str r0, [sp, #0x2c]
	add r0, sp, #0x0
	bl FUN_0201FE94
	add sp, #0x30
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201FFC8
FUN_0201FFC8: ; 0x0201FFC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0xec
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _02020040
	add r1, r5, #0x0
	add r1, #0xfc
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0201FFE4
	bl FUN_02020820
_0201FFE4:
	add r0, r5, #0x0
	add r0, #0xec
	ldr r0, [r0, #0x0]
	cmp r0, #0x3
	bne _0202000E
	add r1, r5, #0x0
	add r1, #0xf8
	add r0, r5, #0x0
	add r4, r5, #0x0
	ldr r1, [r1, #0x0]
	add r0, #0xb4
	add r4, #0x40
	bl FUN_020B1A14
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _0202000E
	ldr r0, [r4, #0x5c]
	bl FUN_020B4358
_0202000E:
	add r0, r5, #0x0
	add r0, #0xec
	ldr r0, [r0, #0x0]
	cmp r0, #0x2
	bne _02020030
	add r4, r5, #0x0
	add r4, #0x40
	ldr r0, [r4, #0x70]
	cmp r0, #0x0
	beq _02020026
	bl FUN_02016A18
_02020026:
	ldr r0, [r4, #0x74]
	cmp r0, #0x0
	beq _02020030
	bl FUN_02016A18
_02020030:
	add r0, r5, #0x0
	mov r1, #0x0
	add r0, #0xec
	str r1, [r0, #0x0]
	ldr r0, [r5, #0x3c]
	add r1, r5, #0x0
	bl FUN_02020890
_02020040:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02020044
FUN_02020044: ; 0x02020044
	add r2, r1, #0x0
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02020054
FUN_02020054: ; 0x02020054
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0xc
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_02020064
FUN_02020064: ; 0x02020064
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x18
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_02020074
FUN_02020074: ; 0x02020074
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02020064
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020200EC
	pop {r3-r5, pc}

	thumb_func_start FUN_02020088
FUN_02020088: ; 0x02020088
	strh r1, [r0, #0x24]
	bx lr

	thumb_func_start FUN_0202008C
FUN_0202008C: ; 0x0202008C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02020088
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020200EC
	pop {r3-r5, pc}

	thumb_func_start FUN_020200A0
FUN_020200A0: ; 0x020200A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020200AE
	bl ErrorHandling
_020200AE:
	cmp r4, #0x2
	blt _020200B6
	bl ErrorHandling
_020200B6:
	add r5, #0x34
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_020200BC
FUN_020200BC: ; 0x020200BC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020200CA
	bl ErrorHandling
_020200CA:
	cmp r4, #0x2
	blt _020200D2
	bl ErrorHandling
_020200D2:
	add r5, #0x35
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_020200D8
FUN_020200D8: ; 0x020200D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020200E6
	bl ErrorHandling
_020200E6:
	str r4, [r5, #0x38]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020200EC
FUN_020200EC: ; 0x020200EC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020200FA
	bl ErrorHandling
_020200FA:
	add r5, #0x26
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02020100
FUN_02020100: ; 0x02020100
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0202010E
	bl ErrorHandling
_0202010E:
	add r0, r5, #0x0
	add r0, #0x27
	strb r4, [r0, #0x0]
	mov r0, #0x0
	add r5, #0x26
	strb r0, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0202011C
FUN_0202011C: ; 0x0202011C
	bx lr
	.balign 4

	thumb_func_start FUN_02020120
FUN_02020120: ; 0x02020120
	add r0, #0x18
	bx lr

	thumb_func_start FUN_02020124
FUN_02020124: ; 0x02020124
	ldrh r0, [r0, #0x24]
	bx lr

	thumb_func_start FUN_02020128
FUN_02020128: ; 0x02020128
	add r0, #0x34
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02020130
FUN_02020130: ; 0x02020130
	push {r4, lr}
	lsl r2, r1, #0x10
	lsr r3, r2, #0x10
	add r2, r0, #0x0
	add r2, #0xf0
	strh r3, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xec
	ldr r2, [r2, #0x0]
	cmp r2, #0x1
	beq _0202014A
	cmp r2, #0x3
	bne _02020168
_0202014A:
	add r4, r0, #0x0
	add r4, #0x40
	lsl r1, r1, #0x10
	ldr r0, [r4, #0x4]
	lsr r1, r1, #0x10
	bl FUN_020AFC04
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x8
	bl FUN_020B1EE4
	mov r0, #0x1
	str r0, [r4, #0x10]
	pop {r4, pc}
_02020168:
	add r4, r0, #0x0
	add r4, #0x40
	ldr r0, [r4, #0x6c]
	add r1, r3, #0x0
	bl FUN_020AFC04
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x8
	bl FUN_020B242C
	mov r0, #0x1
	str r0, [r4, #0x10]
	pop {r4, pc}

	thumb_func_start FUN_02020184
FUN_02020184: ; 0x02020184
	push {r3, lr}
	add r2, r0, #0x0
	add r2, #0xf0
	ldrh r2, [r2, #0x0]
	cmp r2, r1
	beq _02020194
	bl FUN_02020130
_02020194:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02020198
FUN_02020198: ; 0x02020198
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0xec
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _020201A8
	cmp r0, #0x3
	bne _020201C2
_020201A8:
	add r5, r4, #0x0
	add r5, #0x40
	add r0, r5, #0x0
	add r0, #0x8
	bl FUN_020B0448
	mov r0, #0x1
	str r0, [r5, #0x10]
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02020208
	pop {r3-r5, pc}
_020201C2:
	add r5, r4, #0x0
	add r5, #0x40
	add r0, r5, #0x0
	add r0, #0x8
	bl FUN_020B0448
	mov r0, #0x1
	str r0, [r5, #0x10]
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02020208
	pop {r3-r5, pc}

	thumb_func_start FUN_020201DC
FUN_020201DC: ; 0x020201DC
	add r0, #0xf0
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020201E4
FUN_020201E4: ; 0x020201E4
	push {r3, lr}
	add r2, r0, #0x0
	add r2, #0xec
	ldr r2, [r2, #0x0]
	cmp r2, #0x1
	beq _020201F4
	cmp r2, #0x3
	bne _020201FE
_020201F4:
	add r0, #0x40
	add r0, #0x8
	bl FUN_020B1EC4
	pop {r3, pc}
_020201FE:
	add r0, #0x40
	add r0, #0x8
	bl FUN_020B224C
	pop {r3, pc}

	thumb_func_start FUN_02020208
FUN_02020208: ; 0x02020208
	push {r3, lr}
	add r2, r0, #0x0
	add r2, #0xec
	ldr r2, [r2, #0x0]
	cmp r2, #0x1
	beq _02020218
	cmp r2, #0x3
	bne _02020222
_02020218:
	add r0, #0x40
	add r0, #0x8
	bl FUN_020B1EA4
	pop {r3, pc}
_02020222:
	add r0, #0x40
	add r0, #0x8
	bl FUN_020B2194
	pop {r3, pc}

	thumb_func_start FUN_0202022C
FUN_0202022C: ; 0x0202022C
	ldr r3, _02020234 ; =0x020B04FC
	add r0, #0x40
	add r0, #0x8
	bx r3
	.balign 4
_02020234: .word 0x020B04FC

	thumb_func_start FUN_02020238
FUN_02020238: ; 0x02020238
	add r0, #0xf2
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02020240
FUN_02020240: ; 0x02020240
	add r0, #0xf2
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02020248
FUN_02020248: ; 0x02020248
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020256
	bl ErrorHandling
_02020256:
	add r0, r5, #0x0
	add r0, #0x29
	strb r4, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x2
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x28
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x10
	add r5, #0x28
	bic r1, r0
	strb r1, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0202027C
FUN_0202027C: ; 0x0202027C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02020248
	add r1, r4, #0x0
	add r1, #0xf8
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	add r0, #0xd8
	bl FUN_020205E8
	add r1, r4, #0x0
	add r1, #0x29
	ldrb r1, [r1, #0x0]
	add r4, #0x29
	add r0, r1, r0
	strb r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_020202A0
FUN_020202A0: ; 0x020202A0
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020202A8
FUN_020202A8: ; 0x020202A8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020202B6
	bl ErrorHandling
_020202B6:
	add r0, r5, #0x0
	add r0, #0x2a
	strb r4, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x10
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x28
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x2
	add r5, #0x28
	bic r1, r0
	strb r1, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_020202DC
FUN_020202DC: ; 0x020202DC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020202A8
	add r1, r4, #0x0
	add r1, #0xf8
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	add r0, #0xd8
	bl FUN_020205E8
	add r1, r4, #0x0
	add r1, #0x2a
	ldrb r1, [r1, #0x0]
	add r4, #0x2a
	add r0, r1, r0
	strb r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02020300
FUN_02020300: ; 0x02020300
	push {r4, lr}
	add r4, r0, #0x0
	bne _0202030A
	bl ErrorHandling
_0202030A:
	add r4, #0x2a
	ldrb r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02020310
FUN_02020310: ; 0x02020310
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r2, r5, #0x0
	ldr r4, [r5, #0x3c]
	add r2, #0xf4
	strh r1, [r2, #0x0]
	bl FUN_02020820
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02020788
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202032C
FUN_0202032C: ; 0x0202032C
	add r0, #0xf4
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02020334
FUN_02020334: ; 0x02020334
	push {r3-r4}
	add r3, r0, #0x0
	add r4, r1, #0x0
	add r3, #0xb4
	mov r2, #0x4
_0202033E:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0202033E
	ldr r0, [r4, #0x0]
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_02020350
FUN_02020350: ; 0x02020350
	add r0, #0xb4
	bx lr

	thumb_func_start FUN_02020354
FUN_02020354: ; 0x02020354
	add r0, #0xd8
	bx lr

	thumb_func_start FUN_02020358
FUN_02020358: ; 0x02020358
	str r1, [r0, #0x2c]
	cmp r1, #0x1
	bne _0202036E
	add r1, r0, #0x0
	add r1, #0x28
	ldrb r2, [r1, #0x0]
	mov r1, #0x4
	add r0, #0x28
	orr r1, r2
	strb r1, [r0, #0x0]
	bx lr
_0202036E:
	add r1, r0, #0x0
	add r1, #0x28
	ldrb r2, [r1, #0x0]
	mov r1, #0x4
	eor r1, r2
	add r0, #0x28
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02020380
FUN_02020380: ; 0x02020380
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02020388
FUN_02020388: ; 0x02020388
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020392
	bl ErrorHandling
_02020392:
	ldr r0, [r4, #0x50]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02020398
FUN_02020398: ; 0x02020398
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x0
	bne _020203A6
	bl ErrorHandling
_020203A6:
	str r5, [r4, #0x30]
	cmp r5, #0x0
	bne _020203BC
	add r0, r4, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x8
	add r4, #0x28
	eor r0, r1
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
_020203BC:
	add r0, r4, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x8
	orr r0, r1
	add r4, #0x28
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_020203CC
FUN_020203CC: ; 0x020203CC
	push {r4, lr}
	mov r1, #0x1
	lsl r1, r1, #0xa
	bl FUN_02016998
	add r4, r0, #0x0
	mov r0, #0xb
	mov r2, #0x1
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	lsl r2, r2, #0xa
	bl MIi_CpuClear16
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0xa
	bl DC_FlushRange
	mov r2, #0x1
	add r0, r4, #0x0
	mov r1, #0x0
	lsl r2, r2, #0xa
	bl GX_LoadOAM
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_02020404
FUN_02020404: ; 0x02020404
	push {r4, lr}
	mov r1, #0x1
	lsl r1, r1, #0xa
	bl FUN_02016998
	add r4, r0, #0x0
	mov r0, #0xb
	mov r2, #0x1
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	lsl r2, r2, #0xa
	bl MIi_CpuClear16
	mov r2, #0x1
	add r0, r4, #0x0
	mov r1, #0x0
	lsl r2, r2, #0xa
	bl GXS_LoadOAM
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02020434
FUN_02020434: ; 0x02020434
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	add r4, r2, #0x0
	add r0, r5, #0x0
	add r7, r3, #0x0
	bl FUN_020204DC
	add r1, r4, #0x0
	add r1, #0xec
	str r0, [r1, #0x0]
	add r3, r4, #0x0
	ldr r6, [r5, #0x0]
	add r3, #0xb4
	mov r2, #0x4
_02020452:
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02020452
	ldr r0, [r6, #0x0]
	add r2, r4, #0x0
	str r0, [r3, #0x0]
	ldr r3, [r5, #0x8]
	add r2, #0xd8
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r1, r4, #0x0
	str r0, [r2, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_020204F4
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	beq _02020486
	add r1, r4, #0x0
	bl FUN_020204F8
	b _02020494
_02020486:
	mov r1, #0x47
	ldr r0, [sp, #0x0]
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	add r1, r4, #0x0
	bl FUN_020204F8
_02020494:
	add r0, r4, #0x0
	add r0, #0xec
	ldr r0, [r0, #0x0]
	cmp r0, #0x2
	bne _020204B8
	ldr r0, [r5, #0x14]
	add r1, r4, #0x0
	bl FUN_020204FC
	ldr r0, [r5, #0x18]
	add r1, r4, #0x0
	bl FUN_02020504
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_02020588
	b _020204D0
_020204B8:
	cmp r0, #0x3
	bne _020204C8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl FUN_0202052C
	b _020204D0
_020204C8:
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_0202050C
_020204D0:
	add r5, #0x20
	ldrb r0, [r5, #0x0]
	add r4, #0xf2
	strb r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start FUN_020204DC
FUN_020204DC: ; 0x020204DC
	ldr r1, [r0, #0x14]
	cmp r1, #0x0
	beq _020204E6
	mov r0, #0x2
	bx lr
_020204E6:
	ldr r0, [r0, #0x1c]
	cmp r0, #0x1
	bne _020204F0
	mov r0, #0x3
	bx lr
_020204F0:
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_020204F4
FUN_020204F4: ; 0x020204F4
	str r0, [r1, #0x40]
	bx lr

	thumb_func_start FUN_020204F8
FUN_020204F8: ; 0x020204F8
	str r0, [r1, #0x44]
	bx lr

	thumb_func_start FUN_020204FC
FUN_020204FC: ; 0x020204FC
	add r1, #0xa8
	str r0, [r1, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02020504
FUN_02020504: ; 0x02020504
	add r1, #0xac
	str r0, [r1, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202050C
FUN_0202050C: ; 0x0202050C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r5, #0x0
	add r4, #0x40
	ldr r0, [r4, #0x4]
	mov r1, #0x0
	bl FUN_020AFC04
	add r4, #0x8
	add r1, r0, #0x0
	ldr r2, [r5, #0x40]
	add r0, r4, #0x0
	bl FUN_020B1F80
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202052C
FUN_0202052C: ; 0x0202052C
	push {r4-r7, lr}
	sub sp, #0x1c
	add r6, r1, #0x0
	add r4, r6, #0x0
	add r4, #0x40
	add r5, r0, #0x0
	bl FUN_020B43A4
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x4]
	mov r1, #0x0
	ldr r5, [r5, #0x4]
	bl FUN_020AFC04
	str r0, [sp, #0x18]
	add r0, r6, #0x0
	add r0, #0xb4
	mov r1, #0x1
	bl FUN_020B1A14
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r0, #0xb4
	mov r1, #0x2
	bl FUN_020B1A14
	mov r1, #0x0
	mvn r1, r1
	str r1, [sp, #0x0]
	str r7, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x14]
	ldr r1, [sp, #0x18]
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x10]
	str r0, [sp, #0x14]
	add r0, r4, #0x0
	ldr r2, [r6, #0x40]
	ldr r3, [r4, #0x5c]
	add r0, #0x8
	bl FUN_020B1EFC
	add sp, #0x1c
	pop {r4-r7, pc}

	thumb_func_start FUN_02020588
FUN_02020588: ; 0x02020588
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r5, #0x0
	add r4, #0x40
	ldr r0, [r4, #0x6c]
	add r7, r1, #0x0
	mov r1, #0x0
	bl FUN_020AFC04
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x68]
	bl FUN_020B23D8
	add r6, r0, #0x0
	mov r1, #0x28
	add r0, r7, #0x0
	mul r1, r6
	bl FUN_02016998
	mov r1, #0x54
	str r0, [r4, #0x70]
	add r0, r7, #0x0
	mul r1, r6
	bl FUN_02016998
	str r0, [r4, #0x74]
	ldr r0, [r4, #0x4]
	add r3, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x40]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x68]
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	ldr r1, [r4, #0x70]
	ldr r2, [r4, #0x74]
	add r0, #0x8
	bl FUN_020B20C8
	add r4, #0x8
	ldr r1, [sp, #0xc]
	add r0, r4, #0x0
	bl FUN_020B242C
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020205E8
FUN_020205E8: ; 0x020205E8
	push {r4, lr}
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	beq _020205F6
	mov r4, #0x2
	lsl r4, r4, #0x8
	b _02020602
_020205F6:
	ldr r2, [r0, #0x0]
	cmp r2, #0x4
	bne _02020600
	mov r4, #0x0
	b _02020602
_02020600:
	mov r4, #0x20
_02020602:
	cmp r4, #0x0
	beq _02020612
	bl FUN_020B19C4
	add r1, r4, #0x0
	bl _u32_div_f
	pop {r4, pc}
_02020612:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02020618
FUN_02020618: ; 0x02020618
	push {r3-r6, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r3, r4, #0x0
	add r5, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, sp, #0x0
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r1, r4, #0x0
	str r0, [r2, #0x0]
	mov r0, #0x45
	lsl r0, r0, #0x2
	add r2, r4, #0x0
	ldr r0, [r5, r0]
	add r1, #0xb4
	add r2, #0xd8
	bl thunk_FUN_020b5040
	mov r0, #0x45
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_020B326C
	bl FUN_020B2B58
	add r1, r4, #0x0
	mov r0, #0x45
	add r1, #0x26
	lsl r0, r0, #0x2
	ldrb r1, [r1, #0x0]
	ldr r0, [r5, r0]
	bl FUN_020B502C
	add r0, r4, #0x0
	add r0, #0x26
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02020680
	add r0, r4, #0x0
	add r0, #0x27
	ldrb r2, [r0, #0x0]
	mov r0, #0x45
	lsl r0, r0, #0x2
	mov r1, #0x1
	ldr r0, [r5, r0]
	mov r3, #0x2
	and r1, r2
	and r2, r3
	bl FUN_020B4F38
	b _0202068E
_02020680:
	mov r0, #0x45
	lsl r0, r0, #0x2
	mov r1, #0x0
	ldr r0, [r5, r0]
	add r2, r1, #0x0
	bl FUN_020B4F38
_0202068E:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x8]
	bl FUN_020B2A08
	add r0, r4, #0x0
	add r0, #0x26
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020206DC
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x14]
	bl FUN_020B2A08
	ldr r0, [r4, #0x18]
	ldr r1, [r4, #0x1c]
	ldr r2, [r4, #0x20]
	bl FUN_020B28B4
	ldrh r0, [r4, #0x24]
	ldr r2, _02020770 ; =0x020FFA38
	asr r0, r0, #0x4
	lsl r1, r0, #0x1
	lsl r0, r1, #0x1
	add r1, r1, #0x1
	lsl r1, r1, #0x1
	ldrsh r0, [r2, r0]
	ldrsh r1, [r2, r1]
	bl FUN_020B2794
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x14]
	neg r0, r0
	neg r1, r1
	neg r2, r2
	bl FUN_020B2A08
_020206DC:
	add r0, r4, #0x0
	add r0, #0x28
	ldrb r3, [r0, #0x0]
	mov r0, #0x45
	lsl r0, r0, #0x2
	ldr r2, [r5, r0]
	add r1, r2, #0x0
	add r1, #0x84
	ldr r1, [r1, #0x0]
	add r2, #0x84
	orr r1, r3
	str r1, [r2, #0x0]
	add r1, r4, #0x0
	add r1, #0x28
	ldrb r1, [r1, #0x0]
	mvn r6, r1
	ldr r1, [r5, r0]
	add r2, r1, #0x0
	add r2, #0x84
	ldr r3, [r2, #0x0]
	mvn r2, r6
	and r2, r3
	add r1, #0x84
	str r2, [r1, #0x0]
	add r1, r4, #0x0
	add r1, #0x29
	ldrb r2, [r1, #0x0]
	ldr r1, [r5, r0]
	add r1, #0x8a
	strh r2, [r1, #0x0]
	add r1, r4, #0x0
	add r1, #0x2a
	ldrb r2, [r1, #0x0]
	ldr r1, [r5, r0]
	add r1, #0x94
	strh r2, [r1, #0x0]
	ldr r1, [r5, r0]
	ldr r2, [r4, #0x2c]
	add r1, #0x90
	str r2, [r1, #0x0]
	ldr r1, [r5, r0]
	ldr r2, [r4, #0x30]
	add r1, #0x8c
	str r2, [r1, #0x0]
	add r1, r4, #0x0
	add r1, #0xf2
	ldr r0, [r5, r0]
	ldrb r1, [r1, #0x0]
	add r0, #0x88
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0xec
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _0202074E
	cmp r0, #0x3
	bne _0202075A
_0202074E:
	add r4, #0x40
	add r4, #0x8
	add r0, r4, #0x0
	bl FUN_020B317C
	b _02020764
_0202075A:
	add r4, #0x40
	add r4, #0x8
	add r0, r4, #0x0
	bl FUN_020B2D9C
_02020764:
	bl FUN_020B2B08
	bl FUN_020B31F0
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4
_02020770: .word 0x020FFA38

	thumb_func_start FUN_02020774
FUN_02020774: ; 0x02020774
	bx lr
	.balign 4

	thumb_func_start FUN_02020778
FUN_02020778: ; 0x02020778
	ldr r3, _02020780 ; =FUN_020201E4
	ldr r1, [r0, #0x38]
	bx r3
	nop
_02020780: .word FUN_020201E4

	thumb_func_start FUN_02020784
FUN_02020784: ; 0x02020784
	bx lr
	.balign 4

	thumb_func_start FUN_02020788
FUN_02020788: ; 0x02020788
	push {r4-r7}
	mov r2, #0x11
	lsl r2, r2, #0x4
	add r4, r0, #0x0
	ldr r5, [r0, r2]
	add r4, #0x10
	cmp r5, r4
	bne _020207AC
	str r1, [r0, r2]
	sub r3, r2, #0x4
	str r1, [r0, r3]
	add r0, r1, #0x0
	add r0, #0xfc
	str r4, [r0, #0x0]
	sub r2, #0x10
	str r4, [r1, r2]
	pop {r4-r7}
	bx lr
_020207AC:
	add r3, r1, #0x0
	add r3, #0xf4
	ldrh r6, [r3, #0x0]
	sub r3, r2, #0x4
	ldr r3, [r0, r3]
	add r7, r3, #0x0
	add r7, #0xf4
	ldrh r7, [r7, #0x0]
	cmp r7, r6
	bhi _020207DE
	add r5, r1, #0x0
	add r5, #0xfc
	str r3, [r5, #0x0]
	sub r3, r2, #0x4
	ldr r5, [r0, r3]
	add r3, r2, #0x0
	sub r3, #0x10
	str r1, [r5, r3]
	add r3, r2, #0x0
	sub r3, #0x10
	str r4, [r1, r3]
	sub r2, r2, #0x4
	str r1, [r0, r2]
	pop {r4-r7}
	bx lr
_020207DE:
	cmp r5, r4
	beq _0202081A
	add r0, r2, #0x0
	sub r0, #0x10
_020207E6:
	add r2, r5, #0x0
	add r2, #0xf4
	ldrh r2, [r2, #0x0]
	cmp r2, r6
	bls _02020814
	add r0, r5, #0x0
	add r0, #0xfc
	mov r2, #0x1
	ldr r0, [r0, #0x0]
	lsl r2, r2, #0x8
	str r1, [r0, r2]
	add r0, r5, #0x0
	add r0, #0xfc
	ldr r3, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0xfc
	str r3, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0xfc
	str r1, [r0, #0x0]
	str r5, [r1, r2]
	pop {r4-r7}
	bx lr
_02020814:
	ldr r5, [r5, r0]
	cmp r5, r4
	bne _020207E6
_0202081A:
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_02020820
FUN_02020820: ; 0x02020820
	mov r2, #0x1
	add r1, r0, #0x0
	lsl r2, r2, #0x8
	add r1, #0xfc
	ldr r3, [r0, r2]
	ldr r1, [r1, #0x0]
	str r3, [r1, r2]
	add r1, r0, #0x0
	add r1, #0xfc
	ldr r0, [r0, r2]
	ldr r1, [r1, #0x0]
	add r0, #0xfc
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202083C
FUN_0202083C: ; 0x0202083C
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0202086C
	add r4, r7, #0x0
	add r6, r7, #0x0
_0202084C:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	bl FUN_0201FE6C
	ldr r0, [r5, #0x0]
	add r7, r7, #0x1
	add r1, r0, r4
	ldr r0, [r5, #0x8]
	str r1, [r0, r6]
	mov r0, #0x41
	lsl r0, r0, #0x2
	add r4, r4, r0
	ldr r0, [r5, #0x4]
	add r6, r6, #0x4
	cmp r7, r0
	blt _0202084C
_0202086C:
	mov r0, #0x0
	str r0, [r5, #0xc]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02020874
FUN_02020874: ; 0x02020874
	ldr r3, [r0, #0xc]
	ldr r1, [r0, #0x4]
	cmp r3, r1
	blt _02020880
	mov r0, #0x0
	bx lr
_02020880:
	ldr r2, [r0, #0x8]
	lsl r1, r3, #0x2
	ldr r2, [r2, r1]
	add r1, r3, #0x1
	str r1, [r0, #0xc]
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02020890
FUN_02020890: ; 0x02020890
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	cmp r0, #0x0
	bgt _020208A0
	mov r0, #0x0
	pop {r3-r5, pc}
_020208A0:
	add r0, r4, #0x0
	bl FUN_0201FE6C
	ldr r0, [r5, #0xc]
	sub r0, r0, #0x1
	str r0, [r5, #0xc]
	ldr r1, [r5, #0x8]
	lsl r0, r0, #0x2
	str r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020208B8
FUN_020208B8: ; 0x020208B8
	push {r4-r7}
	ldrb r3, [r0, #0x0]
	mov r4, #0x0
	cmp r3, #0xff
	beq _020208FA
_020208C2:
	ldrb r7, [r0, #0x2]
	ldrb r3, [r0, #0x3]
	ldrb r5, [r0, #0x0]
	sub r6, r1, r7
	sub r3, r3, r7
	cmp r6, r3
	bhs _020208D4
	mov r6, #0x1
	b _020208D6
_020208D4:
	mov r6, #0x0
_020208D6:
	ldrb r7, [r0, #0x1]
	sub r3, r2, r5
	sub r5, r7, r5
	cmp r3, r5
	bhs _020208E4
	mov r3, #0x1
	b _020208E6
_020208E4:
	mov r3, #0x0
_020208E6:
	tst r3, r6
	beq _020208F0
	add r0, r4, #0x0
	pop {r4-r7}
	bx lr
_020208F0:
	add r0, r0, #0x4
	ldrb r3, [r0, #0x0]
	add r4, r4, #0x1
	cmp r3, #0xff
	bne _020208C2
_020208FA:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_02020904
FUN_02020904: ; 0x02020904
	push {r3-r4}
	ldrb r3, [r0, #0x1]
	sub r4, r3, r1
	ldrb r1, [r0, #0x2]
	sub r3, r1, r2
	ldrb r2, [r0, #0x3]
	add r1, r4, #0x0
	add r0, r3, #0x0
	mul r1, r4
	mul r0, r3
	add r1, r1, r0
	add r0, r2, #0x0
	mul r0, r2
	cmp r1, r0
	bhs _02020928
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_02020928:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_02020930
FUN_02020930: ; 0x02020930
	push {r4-r5}
	ldrb r5, [r0, #0x2]
	ldrb r3, [r0, #0x0]
	sub r4, r1, r5
	ldrb r1, [r0, #0x3]
	sub r1, r1, r5
	cmp r4, r1
	bhs _02020944
	mov r4, #0x1
	b _02020946
_02020944:
	mov r4, #0x0
_02020946:
	ldrb r0, [r0, #0x1]
	sub r1, r2, r3
	sub r0, r0, r3
	cmp r1, r0
	bhs _02020954
	mov r0, #0x1
	b _02020956
_02020954:
	mov r0, #0x0
_02020956:
	tst r0, r4
	beq _02020960
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02020960:
	mov r0, #0x0
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_02020968
FUN_02020968: ; 0x02020968
	push {r3, lr}
	ldr r2, _02020984 ; =0x021C48F8
	ldrh r1, [r2, #0x22]
	cmp r1, #0x0
	beq _0202097C
	ldrh r1, [r2, #0x1c]
	ldrh r2, [r2, #0x1e]
	bl FUN_020208B8
	pop {r3, pc}
_0202097C:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}
	nop
_02020984: .word 0x021C48F8

	thumb_func_start FUN_02020988
FUN_02020988: ; 0x02020988
	push {r3, lr}
	ldr r2, _020209A4 ; =0x021C48F8
	ldrh r1, [r2, #0x20]
	cmp r1, #0x0
	beq _0202099C
	ldrh r1, [r2, #0x1c]
	ldrh r2, [r2, #0x1e]
	bl FUN_020208B8
	pop {r3, pc}
_0202099C:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}
	nop
_020209A4: .word 0x021C48F8

	thumb_func_start FUN_020209A8
FUN_020209A8: ; 0x020209A8
	push {r3-r7, lr}
	ldr r7, _020209F0 ; =0x021C48F8
	add r5, r0, #0x0
	ldrh r0, [r7, #0x22]
	cmp r0, #0x0
	beq _020209EA
	mov r6, #0x0
	add r4, r5, #0x0
_020209B8:
	ldrb r0, [r5, #0x0]
	cmp r0, #0xfe
	bne _020209D0
	ldrh r1, [r7, #0x1c]
	ldrh r2, [r7, #0x1e]
	add r0, r4, #0x0
	bl FUN_02020904
	cmp r0, #0x0
	beq _020209E2
	add r0, r6, #0x0
	pop {r3-r7, pc}
_020209D0:
	ldrh r1, [r7, #0x1c]
	ldrh r2, [r7, #0x1e]
	add r0, r4, #0x0
	bl FUN_02020930
	cmp r0, #0x0
	beq _020209E2
	add r0, r6, #0x0
	pop {r3-r7, pc}
_020209E2:
	add r5, r5, #0x4
	add r4, r4, #0x4
	add r6, r6, #0x1
	b _020209B8
_020209EA:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
	.balign 4
_020209F0: .word 0x021C48F8

	thumb_func_start FUN_020209F4
FUN_020209F4: ; 0x020209F4
	push {r3-r7, lr}
	ldr r7, _02020A3C ; =0x021C48F8
	add r5, r0, #0x0
	ldrh r0, [r7, #0x20]
	cmp r0, #0x0
	beq _02020A36
	mov r6, #0x0
	add r4, r5, #0x0
_02020A04:
	ldrb r0, [r5, #0x0]
	cmp r0, #0xfe
	bne _02020A1C
	ldrh r1, [r7, #0x1c]
	ldrh r2, [r7, #0x1e]
	add r0, r4, #0x0
	bl FUN_02020904
	cmp r0, #0x0
	beq _02020A2E
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02020A1C:
	ldrh r1, [r7, #0x1c]
	ldrh r2, [r7, #0x1e]
	add r0, r4, #0x0
	bl FUN_02020930
	cmp r0, #0x0
	beq _02020A2E
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02020A2E:
	add r5, r5, #0x4
	add r4, r4, #0x4
	add r6, r6, #0x1
	b _02020A04
_02020A36:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
	.balign 4
_02020A3C: .word 0x021C48F8

	thumb_func_start FUN_02020A40
FUN_02020A40: ; 0x02020A40
	push {r3, lr}
	ldr r2, _02020A68 ; =0x021C48F8
	ldrh r1, [r2, #0x22]
	cmp r1, #0x0
	beq _02020A62
	ldrb r1, [r0, #0x0]
	cmp r1, #0xfe
	ldrh r1, [r2, #0x1c]
	bne _02020A5A
	ldrh r2, [r2, #0x1e]
	bl FUN_02020904
	pop {r3, pc}
_02020A5A:
	ldrh r2, [r2, #0x1e]
	bl FUN_02020930
	pop {r3, pc}
_02020A62:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02020A68: .word 0x021C48F8

	thumb_func_start FUN_02020A6C
FUN_02020A6C: ; 0x02020A6C
	push {r3, lr}
	ldr r2, _02020A94 ; =0x021C48F8
	ldrh r1, [r2, #0x20]
	cmp r1, #0x0
	beq _02020A8E
	ldrb r1, [r0, #0x0]
	cmp r1, #0xfe
	ldrh r1, [r2, #0x1c]
	bne _02020A86
	ldrh r2, [r2, #0x1e]
	bl FUN_02020904
	pop {r3, pc}
_02020A86:
	ldrh r2, [r2, #0x1e]
	bl FUN_02020930
	pop {r3, pc}
_02020A8E:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02020A94: .word 0x021C48F8

	thumb_func_start FUN_02020A98
FUN_02020A98: ; 0x02020A98
	ldr r0, _02020AA0 ; =0x021C48F8
	ldrh r0, [r0, #0x22]
	bx lr
	nop
_02020AA0: .word 0x021C48F8

	thumb_func_start FUN_02020AA4
FUN_02020AA4: ; 0x02020AA4
	ldr r0, _02020AAC ; =0x021C48F8
	ldrh r0, [r0, #0x20]
	bx lr
	nop
_02020AAC: .word 0x021C48F8

	thumb_func_start FUN_02020AB0
FUN_02020AB0: ; 0x02020AB0
	ldr r2, _02020AC8 ; =0x021C48F8
	ldrh r3, [r2, #0x22]
	cmp r3, #0x0
	beq _02020AC4
	ldrh r3, [r2, #0x1c]
	str r3, [r0, #0x0]
	ldrh r0, [r2, #0x1e]
	str r0, [r1, #0x0]
	mov r0, #0x1
	bx lr
_02020AC4:
	mov r0, #0x0
	bx lr
	.balign 4
_02020AC8: .word 0x021C48F8

	thumb_func_start FUN_02020ACC
FUN_02020ACC: ; 0x02020ACC
	ldr r2, _02020AE4 ; =0x021C48F8
	ldrh r3, [r2, #0x20]
	cmp r3, #0x0
	beq _02020AE0
	ldrh r3, [r2, #0x1c]
	str r3, [r0, #0x0]
	ldrh r0, [r2, #0x1e]
	str r0, [r1, #0x0]
	mov r0, #0x1
	bx lr
_02020AE0:
	mov r0, #0x0
	bx lr
	.balign 4
_02020AE4: .word 0x021C48F8

	thumb_func_start FUN_02020AE8
FUN_02020AE8: ; 0x02020AE8
	push {r3, lr}
	ldrb r3, [r0, #0x0]
	cmp r3, #0xfe
	bne _02020AF6
	bl FUN_02020904
	pop {r3, pc}
_02020AF6:
	bl FUN_02020930
	pop {r3, pc}

	thumb_func_start FUN_02020AFC
FUN_02020AFC: ; 0x02020AFC
	push {r3, lr}
	ldr r0, _02020B24 ; =0x021C59B0
	mov r2, #0x0
	str r2, [r0, #0x4]
	str r2, [r0, #0x8]
	ldr r1, _02020B28 ; =0x0400010E
	str r2, [r0, #0x0]
	strh r2, [r1, #0x0]
	sub r0, r1, #0x2
	strh r2, [r0, #0x0]
	mov r0, #0xc1
	strh r0, [r1, #0x0]
	ldr r1, _02020B2C ; =FUN_02020B30
	mov r0, #0x40
	bl OS_SetIrqFunction
	mov r0, #0x40
	bl OS_EnableIrqMask
	pop {r3, pc}
	.balign 4
_02020B24: .word 0x021C59B0
_02020B28: .word 0x0400010E
_02020B2C: .word FUN_02020B30

	thumb_func_start FUN_02020B30
FUN_02020B30: ; 0x02020B30
	ldr r0, _02020B68 ; =0x021C59B0
	mov r3, #0x0
	ldr r1, [r0, #0x4]
	ldr r2, [r0, #0x8]
	add r1, r1, #0x1
	adc r2, r3
	str r1, [r0, #0x4]
	str r2, [r0, #0x8]
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02020B54
	ldr r2, _02020B6C ; =0x0400010E
	strh r3, [r2, #0x0]
	sub r1, r2, #0x2
	strh r3, [r1, #0x0]
	mov r1, #0xc1
	strh r1, [r2, #0x0]
	str r3, [r0, #0x0]
_02020B54:
	ldr r3, _02020B70 ; =0x027E0000
	ldr r1, _02020B74 ; =0x00003FF8
	mov r0, #0x40
	ldr r2, [r3, r1]
	orr r2, r0
	str r2, [r3, r1]
	ldr r3, _02020B78 ; =OS_SetIrqFunction
	ldr r1, _02020B7C ; =FUN_02020B30
	bx r3
	nop
_02020B68: .word 0x021C59B0
_02020B6C: .word 0x0400010E
_02020B70: .word 0x027E0000
_02020B74: .word 0x00003FF8
_02020B78: .word OS_SetIrqFunction
_02020B7C: .word FUN_02020B30

	thumb_func_start FUN_02020B80
FUN_02020B80: ; 0x02020B80
	push {r4-r5, lr}
	sub sp, #0xc
	bl OS_DisableInterrupts
	ldr r1, _02020BE4 ; =0x0400010C
	add r3, sp, #0x0
	ldrh r1, [r1, #0x0]
	ldr r2, _02020BE8 ; =0x0000FFFF
	strh r1, [r3, #0x0]
	ldr r1, _02020BEC ; =0x021C59B0
	ldr r5, [r1, #0x4]
	ldr r4, [r1, #0x8]
	mov r1, #0x0
	mvn r1, r1
	and r1, r5
	str r1, [sp, #0x4]
	and r2, r4
	ldr r1, _02020BF0 ; =0x04000214
	str r2, [sp, #0x8]
	ldr r2, [r1, #0x0]
	mov r1, #0x40
	tst r2, r1
	beq _02020BC4
	ldrh r2, [r3, #0x0]
	lsl r1, r1, #0x9
	tst r1, r2
	bne _02020BC4
	ldr r2, [sp, #0x4]
	mov r1, #0x0
	ldr r3, [sp, #0x8]
	add r2, r2, #0x1
	adc r3, r1
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
_02020BC4:
	bl OS_RestoreInterrupts
	ldr r2, [sp, #0x4]
	ldr r1, [sp, #0x8]
	lsr r0, r2, #0x10
	lsl r1, r1, #0x10
	orr r1, r0
	add r0, sp, #0x0
	lsl r3, r2, #0x10
	ldrh r2, [r0, #0x0]
	asr r0, r2, #0x1f
	orr r1, r0
	add r0, r3, #0x0
	orr r0, r2
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4
_02020BE4: .word 0x0400010C
_02020BE8: .word 0x0000FFFF
_02020BEC: .word 0x021C59B0
_02020BF0: .word 0x04000214

	thumb_func_start FUN_02020BF4
FUN_02020BF4: ; 0x02020BF4
	ldr r3, _02020BF8 ; =FUN_02020B80
	bx r3
	.balign 4
_02020BF8: .word FUN_02020B80

	thumb_func_start FUN_02020BFC
FUN_02020BFC: ; 0x02020BFC
	push {r3, lr}
	lsr r2, r0, #0x1a
	lsl r1, r1, #0x6
	orr r1, r2
	ldr r2, _02020C10 ; =0x000082EA
	lsl r0, r0, #0x6
	mov r3, #0x0
	bl _ll_udiv
	pop {r3, pc}
	.balign 4
_02020C10: .word 0x000082EA

	thumb_func_start FUN_02020C14
FUN_02020C14: ; 0x02020C14
	push {r3, lr}
	lsr r2, r0, #0x1a
	lsl r1, r1, #0x6
	orr r1, r2
	ldr r2, _02020C28 ; =0x01FF6210
	lsl r0, r0, #0x6
	mov r3, #0x0
	bl _ll_udiv
	pop {r3, pc}
	.balign 4
_02020C28: .word 0x01FF6210

	thumb_func_start ErrorHandling
ErrorHandling: ; 0x02020C2C
	push {r3, lr}
	bl FUN_02031810
	cmp r0, #0x0
	beq _02020C42
	bl OS_GetProcMode
	cmp r0, #0x12
	beq _02020C42
	bl FUN_0208A9B8
_02020C42:
	pop {r3, pc}

	thumb_func_start FUN_02020C44
FUN_02020C44: ; 0x02020C44
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xc
	bl FUN_02016998
	add r6, r0, #0x0
	bne _02020C5A
	bl ErrorHandling
_02020C5A:
	add r0, r4, #0x0
	lsl r1, r7, #0x3
	bl FUN_02016998
	str r0, [r6, #0x0]
	cmp r0, #0x0
	bne _02020C6C
	bl ErrorHandling
_02020C6C:
	mov r4, #0x0
	cmp r7, #0x0
	ble _02020C84
	add r5, r4, #0x0
_02020C74:
	ldr r0, [r6, #0x0]
	add r0, r0, r5
	bl FUN_02020E78
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, r7
	blt _02020C74
_02020C84:
	str r7, [r6, #0x4]
	mov r0, #0x0
	str r0, [r6, #0x8]
	add r0, r6, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02020C90
FUN_02020C90: ; 0x02020C90
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020C9A
	bl ErrorHandling
_02020C9A:
	add r0, r4, #0x0
	bl FUN_02020D9C
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02020CB0
FUN_02020CB0: ; 0x02020CB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020CBE
	bl ErrorHandling
_02020CBE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02020DD8
	cmp r0, #0x0
	bne _02020CCE
	mov r0, #0x1
	pop {r3-r5, pc}
_02020CCE:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02020CD4
FUN_02020CD4: ; 0x02020CD4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r6, r2, #0x0
	cmp r5, #0x0
	bne _02020CE4
	bl ErrorHandling
_02020CE4:
	add r0, r5, #0x0
	bl FUN_02020E48
	add r4, r0, #0x0
	bne _02020CF2
	bl ErrorHandling
_02020CF2:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02020CB0
	cmp r0, #0x1
	beq _02020D02
	bl ErrorHandling
_02020D02:
	str r7, [r4, #0x4]
	str r6, [r4, #0x0]
	ldr r0, [r5, #0x8]
	add r0, r0, #0x1
	str r0, [r5, #0x8]
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02020D10
FUN_02020D10: ; 0x02020D10
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	cmp r5, #0x0
	bne _02020D22
	bl ErrorHandling
_02020D22:
	cmp r6, #0x0
	bne _02020D2A
	bl ErrorHandling
_02020D2A:
	add r0, r5, #0x0
	bl FUN_02020E48
	add r4, r0, #0x0
	bne _02020D38
	bl ErrorHandling
_02020D38:
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02020CB0
	cmp r0, #0x1
	beq _02020D48
	bl ErrorHandling
_02020D48:
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl FUN_020161A4
	str r0, [r4, #0x4]
	cmp r0, #0x0
	bne _02020D5A
	bl ErrorHandling
_02020D5A:
	str r7, [r4, #0x0]
	ldr r0, [r5, #0x8]
	add r0, r0, #0x1
	str r0, [r5, #0x8]
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02020D68
FUN_02020D68: ; 0x02020D68
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020D76
	bl ErrorHandling
_02020D76:
	cmp r4, #0x0
	bne _02020D7E
	bl ErrorHandling
_02020D7E:
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _02020D8C
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x4]
_02020D8C:
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x8]
	sub r0, r0, #0x1
	str r0, [r5, #0x8]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02020D9C
FUN_02020D9C: ; 0x02020D9C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bne _02020DA6
	bl ErrorHandling
_02020DA6:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	bne _02020DB0
	bl ErrorHandling
_02020DB0:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02020DD6
	add r4, r6, #0x0
	sub r7, r6, #0x1
_02020DBC:
	ldr r1, [r5, #0x0]
	ldr r0, [r1, r4]
	cmp r0, r7
	beq _02020DCC
	add r0, r5, #0x0
	add r1, r1, r4
	bl FUN_02020D68
_02020DCC:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0x8
	cmp r6, r0
	blt _02020DBC
_02020DD6:
	pop {r3-r7, pc}

	thumb_func_start FUN_02020DD8
FUN_02020DD8: ; 0x02020DD8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020DE6
	bl ErrorHandling
_02020DE6:
	ldr r6, [r5, #0x4]
	mov r1, #0x0
	cmp r6, #0x0
	ble _02020E06
	ldr r3, [r5, #0x0]
	add r2, r3, #0x0
_02020DF2:
	ldr r0, [r2, #0x0]
	cmp r4, r0
	bne _02020DFE
	lsl r0, r1, #0x3
	add r0, r3, r0
	pop {r4-r6, pc}
_02020DFE:
	add r1, r1, #0x1
	add r2, #0x8
	cmp r1, r6
	blt _02020DF2
_02020E06:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02020E0C
FUN_02020E0C: ; 0x02020E0C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020E16
	bl ErrorHandling
_02020E16:
	ldr r0, [r4, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02020E1C
FUN_02020E1C: ; 0x02020E1C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020E2A
	bl ErrorHandling
_02020E2A:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _02020E34
	bl FUN_02016A18
_02020E34:
	str r4, [r5, #0x4]
	pop {r3-r5, pc}

	thumb_func_start FUN_02020E38
FUN_02020E38: ; 0x02020E38
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020E42
	bl ErrorHandling
_02020E42:
	ldr r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02020E48
FUN_02020E48: ; 0x02020E48
	push {r3-r5, lr}
	add r4, r0, #0x0
	bne _02020E52
	bl ErrorHandling
_02020E52:
	ldr r5, [r4, #0x4]
	mov r2, #0x0
	cmp r5, #0x0
	ble _02020E74
	ldr r4, [r4, #0x0]
	sub r0, r2, #0x1
	add r3, r4, #0x0
_02020E60:
	ldr r1, [r3, #0x0]
	cmp r1, r0
	bne _02020E6C
	lsl r0, r2, #0x3
	add r0, r4, r0
	pop {r3-r5, pc}
_02020E6C:
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, r5
	blt _02020E60
_02020E74:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02020E78
FUN_02020E78: ; 0x02020E78
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020E82
	bl ErrorHandling
_02020E82:
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02020E90
FUN_02020E90: ; 0x02020E90
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02016998
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02020C44
	mov r1, #0x18
	str r0, [r7, #0x0]
	add r0, r4, #0x0
	mul r1, r6
	bl FUN_02016998
	mov r4, #0x0
	str r0, [r7, #0x4]
	cmp r6, #0x0
	ble _02020ECE
	add r5, r4, #0x0
_02020EBE:
	ldr r0, [r7, #0x4]
	add r0, r0, r5
	bl FUN_0202120C
	add r4, r4, #0x1
	add r5, #0x18
	cmp r4, r6
	blt _02020EBE
_02020ECE:
	add r0, r7, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02020ED4
FUN_02020ED4: ; 0x02020ED4
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020EDE
	bl ErrorHandling
_02020EDE:
	add r0, r4, #0x0
	bl FUN_02021010
	ldr r0, [r4, #0x0]
	bl FUN_02020C90
	ldr r0, [r4, #0x4]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_02020EF8
FUN_02020EF8: ; 0x02020EF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020F06
	bl ErrorHandling
_02020F06:
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02020CB0
	pop {r3-r5, pc}

	thumb_func_start FUN_02020F10
FUN_02020F10: ; 0x02020F10
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r3, #0x0
	str r2, [sp, #0x0]
	cmp r5, #0x0
	bne _02020F22
	bl ErrorHandling
_02020F22:
	add r0, r5, #0x0
	bl FUN_020211DC
	add r4, r0, #0x0
	strh r7, [r4, #0x16]
	ldrh r0, [r4, #0x16]
	cmp r0, #0x1
	bne _02020F40
	ldr r1, [sp, #0x18]
	add r0, r6, #0x0
	bl FUN_02021310
	add r1, r0, #0x0
	str r6, [r4, #0x10]
	b _02020F46
_02020F40:
	mov r0, #0x0
	add r1, r6, #0x0
	str r0, [r4, #0x10]
_02020F46:
	ldr r0, [r5, #0x0]
	ldr r2, [sp, #0x0]
	bl FUN_02020CD4
	str r0, [r4, #0x0]
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02020F54
FUN_02020F54: ; 0x02020F54
	push {r3-r4, lr}
	sub sp, #0x4
	ldr r4, [sp, #0x10]
	str r4, [sp, #0x0]
	bl FUN_02020F10
	add r4, r0, #0x0
	bl FUN_02021174
	add r0, r4, #0x0
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02020F6C
FUN_02020F6C: ; 0x02020F6C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020F7A
	bl ErrorHandling
_02020F7A:
	cmp r4, #0x0
	bne _02020F82
	bl ErrorHandling
_02020F82:
	ldrh r0, [r4, #0x16]
	cmp r0, #0x1
	bne _02020F98
	ldrh r0, [r4, #0x14]
	cmp r0, #0x0
	bne _02020F98
	ldr r0, [r4, #0x10]
	bl FUN_02016A18
	mov r0, #0x0
	strh r0, [r4, #0x16]
_02020F98:
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02020FA4
	ldr r0, [r5, #0x0]
	bl FUN_02020D68
_02020FA4:
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _02020FB8
	ldr r1, _02020FE8 ; =0x021064BC
	ldr r1, [r1, #0x0]
	blx r1
	cmp r0, #0x0
	beq _02020FB8
	bl ErrorHandling
_02020FB8:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _02020FCC
	ldr r1, _02020FE8 ; =0x021064BC
	ldr r1, [r1, #0x0]
	blx r1
	cmp r0, #0x0
	beq _02020FCC
	bl ErrorHandling
_02020FCC:
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	beq _02020FE0
	ldr r1, _02020FEC ; =0x021064C4
	ldr r1, [r1, #0x0]
	blx r1
	cmp r0, #0x0
	beq _02020FE0
	bl ErrorHandling
_02020FE0:
	add r0, r4, #0x0
	bl FUN_0202120C
	pop {r3-r5, pc}
	.balign 4
_02020FE8: .word 0x021064BC
_02020FEC: .word 0x021064C4

	thumb_func_start FUN_02020FF0
FUN_02020FF0: ; 0x02020FF0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020FFE
	bl ErrorHandling
_02020FFE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02021050
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02020F6C
	pop {r3-r5, pc}

	thumb_func_start FUN_02021010
FUN_02021010: ; 0x02021010
	push {r4-r6, lr}
	add r5, r0, #0x0
	bne _0202101A
	bl ErrorHandling
_0202101A:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _02021024
	bl ErrorHandling
_02021024:
	ldr r0, [r5, #0x0]
	mov r6, #0x0
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	ble _0202104C
	add r4, r6, #0x0
_02021030:
	ldr r1, [r5, #0x4]
	ldr r0, [r1, r4]
	cmp r0, #0x0
	beq _02021040
	add r0, r5, #0x0
	add r1, r1, r4
	bl FUN_02020F6C
_02021040:
	ldr r0, [r5, #0x0]
	add r6, r6, #0x1
	ldr r0, [r0, #0x4]
	add r4, #0x18
	cmp r6, r0
	blt _02021030
_0202104C:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02021050
FUN_02021050: ; 0x02021050
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r7, r1, #0x0
	cmp r6, #0x0
	bne _0202105E
	bl ErrorHandling
_0202105E:
	ldr r0, [r6, #0x0]
	mov r4, #0x0
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	ble _02021092
	add r5, r4, #0x0
_0202106A:
	ldr r1, [r6, #0x4]
	ldr r0, [r1, r5]
	cmp r0, #0x0
	beq _02021086
	add r0, r1, r5
	bl FUN_02021098
	cmp r0, r7
	bne _02021086
	mov r0, #0x18
	ldr r1, [r6, #0x4]
	mul r0, r4
	add r0, r1, r0
	pop {r3-r7, pc}
_02021086:
	ldr r0, [r6, #0x0]
	add r4, r4, #0x1
	ldr r0, [r0, #0x4]
	add r5, #0x18
	cmp r4, r0
	blt _0202106A
_02021092:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02021098
FUN_02021098: ; 0x02021098
	push {r4, lr}
	add r4, r0, #0x0
	bne _020210A2
	bl ErrorHandling
_020210A2:
	ldr r0, [r4, #0x0]
	bl FUN_02020E38
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020210AC
FUN_020210AC: ; 0x020210AC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020210B6
	bl ErrorHandling
_020210B6:
	add r0, r4, #0x0
	bl FUN_02021220
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020210C0
FUN_020210C0: ; 0x020210C0
	push {r4, lr}
	add r4, r0, #0x0
	bne _020210CA
	bl ErrorHandling
_020210CA:
	ldrh r0, [r4, #0x14]
	cmp r0, #0x0
	beq _020210D4
	bl ErrorHandling
_020210D4:
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	bne _020210E0
	bl ErrorHandling
	pop {r4, pc}
_020210E0:
	add r0, r4, #0x0
	bl FUN_02021230
	add r1, r4, #0x0
	bl FUN_020212B8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020210F0
FUN_020210F0: ; 0x020210F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020210FE
	bl ErrorHandling
_020210FE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02021050
	bl FUN_020210C0
	pop {r3-r5, pc}

	thumb_func_start FUN_0202110C
FUN_0202110C: ; 0x0202110C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02021116
	bl ErrorHandling
_02021116:
	ldrh r0, [r4, #0x16]
	cmp r0, #0x0
	bne _02021122
	bl ErrorHandling
	pop {r4, pc}
_02021122:
	ldrh r0, [r4, #0x14]
	cmp r0, #0x0
	beq _0202112E
	bl ErrorHandling
	pop {r4, pc}
_0202112E:
	add r0, r4, #0x0
	bl FUN_02021230
	bl FUN_020212F8
	add r0, r4, #0x0
	bl FUN_02021220
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	ldr r3, [r4, #0xc]
	bl FUN_020212E4
	ldr r0, [r4, #0x10]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x10]
	mov r0, #0x1
	strh r0, [r4, #0x14]
	pop {r4, pc}

	thumb_func_start FUN_02021158
FUN_02021158: ; 0x02021158
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021166
	bl ErrorHandling
_02021166:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02021050
	bl FUN_0202110C
	pop {r3-r5, pc}

	thumb_func_start FUN_02021174
FUN_02021174: ; 0x02021174
	push {r4, lr}
	add r4, r0, #0x0
	bne _0202117E
	bl ErrorHandling
_0202117E:
	ldrh r0, [r4, #0x14]
	cmp r0, #0x0
	beq _02021188
	bl ErrorHandling
_02021188:
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	beq _02021194
	bl ErrorHandling
	pop {r4, pc}
_02021194:
	add r0, r4, #0x0
	bl FUN_02021230
	add r2, r4, #0x0
	add r1, r4, #0x4
	add r4, #0xc
	add r2, #0x8
	add r3, r4, #0x0
	bl FUN_02021248
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020211AC
FUN_020211AC: ; 0x020211AC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020211B6
	bl ErrorHandling
_020211B6:
	ldr r0, [r4, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020211BC
FUN_020211BC: ; 0x020211BC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020211C6
	bl ErrorHandling
_020211C6:
	ldr r0, [r4, #0x8]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020211CC
FUN_020211CC: ; 0x020211CC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020211D6
	bl ErrorHandling
_020211D6:
	ldr r0, [r4, #0xc]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020211DC
FUN_020211DC: ; 0x020211DC
	push {r3-r4}
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	ldr r4, [r1, #0x4]
	cmp r4, #0x0
	ble _02021204
	ldr r3, [r0, #0x4]
_020211EA:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	bne _020211FC
	ldr r1, [r0, #0x4]
	mov r0, #0x18
	mul r0, r2
	add r0, r1, r0
	pop {r3-r4}
	bx lr
_020211FC:
	add r2, r2, #0x1
	add r3, #0x18
	cmp r2, r4
	blt _020211EA
_02021204:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0202120C
FUN_0202120C: ; 0x0202120C
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	str r1, [r0, #0xc]
	strh r1, [r0, #0x14]
	str r1, [r0, #0x10]
	strh r1, [r0, #0x14]
	bx lr
	.balign 4

	thumb_func_start FUN_02021220
FUN_02021220: ; 0x02021220
	push {r3, lr}
	ldr r0, [r0, #0x0]
	bl FUN_02020E0C
	bl FUN_020BC0FC
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02021230
FUN_02021230: ; 0x02021230
	push {r3, lr}
	ldrh r1, [r0, #0x16]
	cmp r1, #0x0
	bne _02021240
	ldr r0, [r0, #0x0]
	bl FUN_02020E0C
	b _02021242
_02021240:
	ldr r0, [r0, #0x10]
_02021242:
	bl FUN_020BC0FC
	pop {r3, pc}

	thumb_func_start FUN_02021248
FUN_02021248: ; 0x02021248
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	bl FUN_020B7E1C
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020B7E10
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020B7CE4
	add r4, r0, #0x0
	cmp r7, #0x0
	beq _0202127E
	ldr r3, _020212B0 ; =0x021064B8
	mov r1, #0x0
	ldr r3, [r3, #0x0]
	add r0, r7, #0x0
	add r2, r1, #0x0
	blx r3
	ldr r1, [sp, #0x0]
	str r0, [r1, #0x0]
_0202127E:
	cmp r6, #0x0
	beq _02021292
	ldr r3, _020212B0 ; =0x021064B8
	add r0, r6, #0x0
	ldr r3, [r3, #0x0]
	mov r1, #0x1
	mov r2, #0x0
	blx r3
	ldr r1, [sp, #0x4]
	str r0, [r1, #0x0]
_02021292:
	cmp r4, #0x0
	beq _020212AC
	ldr r3, _020212B4 ; =0x021064C0
	mov r1, #0x2
	ldrh r2, [r5, #0x20]
	lsl r1, r1, #0xe
	ldr r3, [r3, #0x0]
	and r1, r2
	add r0, r4, #0x0
	mov r2, #0x0
	blx r3
	ldr r1, [sp, #0x8]
	str r0, [r1, #0x0]
_020212AC:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_020212B0: .word 0x021064B8
_020212B4: .word 0x021064C0

	thumb_func_start FUN_020212B8
FUN_020212B8: ; 0x020212B8
	push {r4, lr}
	add r3, r1, #0x0
	ldr r1, [r3, #0x4]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	add r4, r0, #0x0
	bl FUN_020212E4
	ldr r1, [r4, #0x4]
	add r0, r4, #0x0
	bl DC_FlushRange
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020B7D28
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020B7C78
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020212E4
FUN_020212E4: ; 0x020212E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r3, #0x0
	bl FUN_020B7DFC
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020B7CDC
	pop {r3-r5, pc}

	thumb_func_start FUN_020212F8
FUN_020212F8: ; 0x020212F8
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	bl FUN_020B7CF0
	add r0, r4, #0x0
	bl FUN_020B7C58
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_02021310
FUN_02021310: ; 0x02021310
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02021334
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02016998
	add r1, r6, #0x0
	add r2, r5, #0x0
	add r4, r0, #0x0
	bl memcpy
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02021334
FUN_02021334: ; 0x02021334
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020BC0FC
	add r4, r0, #0x0
	bne _02021344
	bl ErrorHandling
_02021344:
	ldr r0, [r4, #0x14]
	add r0, r4, r0
	sub r0, r0, r5
	pop {r3-r5, pc}

	thumb_func_start FUN_0202134C
FUN_0202134C: ; 0x0202134C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020B33A0
	add r5, #0x80
	str r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0202135C
FUN_0202135C: ; 0x0202135C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_020B3334
	add r2, r5, #0x0
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	str r6, [r5, #0x28]
	ldr r0, [sp, #0x18]
	str r7, [r5, #0x2c]
	str r0, [r5, #0x34]
	ldr r0, [sp, #0x1c]
	str r0, [r5, #0x14]
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	beq _0202138C
	add r1, r5, #0x0
	bl FUN_020B3390
_0202138C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02021390
FUN_02021390: ; 0x02021390
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	bx lr
	.balign 4

	thumb_func_start FUN_020213A0
FUN_020213A0: ; 0x020213A0
	push {r3-r7, lr}
	sub sp, #0x60
	add r5, r1, #0x0
	add r6, r2, #0x0
	ldr r4, [r5, #0x10]
	ldr r3, [r6, #0x0]
	add r2, r0, #0x0
	sub r3, r4, r3
	ldrh r1, [r0, #0x2]
	mov r0, #0x3f
	str r3, [sp, #0x18]
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1a
	ldr r4, [r5, #0x14]
	ldr r3, [r6, #0x4]
	add r2, #0x8
	sub r3, r4, r3
	str r3, [sp, #0x14]
	asr r3, r1, #0xb
	mov r1, #0x1
	and r1, r3
	lsr r0, r0, #0x18
	cmp r1, #0x1
	bne _020213F4
	mov r0, #0x6
	ldrsh r0, [r2, r0]
	lsl r4, r0, #0xc
	mov r0, #0x2
	ldrsh r0, [r2, r0]
	lsl r0, r0, #0xc
	str r0, [sp, #0x10]
	mov r0, #0x4
	ldrsh r0, [r2, r0]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	mov r0, #0x0
	ldrsh r0, [r2, r0]
	lsl r0, r0, #0xc
	str r0, [sp, #0x8]
	b _02021400
_020213F4:
	neg r1, r0
	lsl r0, r0, #0xc
	lsl r4, r1, #0xc
	str r0, [sp, #0x10]
	str r4, [sp, #0xc]
	str r0, [sp, #0x8]
_02021400:
	ldr r0, [r5, #0xc]
	str r0, [sp, #0x1c]
	asr r0, r0, #0x1f
	str r0, [sp, #0x20]
	asr r0, r4, #0x1f
	str r0, [sp, #0x24]
	ldr r0, [r5, #0x4]
	ldr r1, [sp, #0x24]
	str r0, [sp, #0x28]
	asr r0, r0, #0x1f
	str r0, [sp, #0x2c]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	add r0, r4, #0x0
	bl _ll_mul
	add r7, r1, #0x0
	str r0, [sp, #0x30]
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	add r0, r4, #0x0
	bl _ll_mul
	add r2, r0, #0x0
	add r3, r1, #0x0
	mov r0, #0x2
	ldr r1, [sp, #0x30]
	mov r4, #0x0
	lsl r0, r0, #0xa
	add r0, r1, r0
	adc r7, r4
	lsl r1, r7, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	mov r1, #0x2
	lsl r1, r1, #0xa
	add r2, r2, r1
	adc r3, r4
	lsl r1, r3, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	add r1, r0, r2
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x28]
	add r0, r0, r1
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0x10]
	ldr r3, [sp, #0x2c]
	asr r0, r0, #0x1f
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x34]
	bl _ll_mul
	str r0, [sp, #0x38]
	add r4, r1, #0x0
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x34]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	bl _ll_mul
	mov r2, #0x2
	ldr r3, [sp, #0x38]
	lsl r2, r2, #0xa
	add r2, r3, r2
	ldr r3, _0202158C ; =0x00000000
	adc r4, r3
	lsl r3, r4, #0x14
	lsr r2, r2, #0xc
	orr r2, r3
	mov r3, #0x2
	lsl r3, r3, #0xa
	add r3, r0, r3
	ldr r0, _0202158C ; =0x00000000
	adc r1, r0
	lsl r0, r1, #0x14
	lsr r1, r3, #0xc
	orr r1, r0
	ldr r0, [sp, #0x14]
	add r1, r2, r1
	add r4, r0, r1
	ldr r0, [r5, #0x8]
	str r0, [sp, #0x3c]
	asr r0, r0, #0x1f
	str r0, [sp, #0x40]
	ldr r0, [sp, #0xc]
	asr r0, r0, #0x1f
	str r0, [sp, #0x44]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x44]
	str r0, [sp, #0x48]
	asr r0, r0, #0x1f
	str r0, [sp, #0x4c]
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x48]
	ldr r3, [sp, #0x4c]
	bl _ll_mul
	str r0, [sp, #0x50]
	add r5, r1, #0x0
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x44]
	ldr r2, [sp, #0x3c]
	ldr r3, [sp, #0x40]
	bl _ll_mul
	mov r2, #0x2
	ldr r3, [sp, #0x50]
	lsl r2, r2, #0xa
	add r2, r3, r2
	ldr r3, _0202158C ; =0x00000000
	adc r5, r3
	lsl r3, r5, #0x14
	lsr r2, r2, #0xc
	orr r2, r3
	mov r3, #0x2
	lsl r3, r3, #0xa
	add r3, r0, r3
	ldr r0, _0202158C ; =0x00000000
	adc r1, r0
	lsl r0, r1, #0x14
	lsr r1, r3, #0xc
	orr r1, r0
	ldr r0, [sp, #0x18]
	add r1, r2, r1
	add r5, r0, r1
	ldr r0, [sp, #0x8]
	asr r0, r0, #0x1f
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x54]
	ldr r2, [sp, #0x48]
	ldr r3, [sp, #0x4c]
	bl _ll_mul
	str r0, [sp, #0x58]
	str r1, [sp, #0x4]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x54]
	ldr r2, [sp, #0x3c]
	ldr r3, [sp, #0x40]
	bl _ll_mul
	mov r12, r0
	add r2, r1, #0x0
	mov r0, #0x2
	ldr r1, [sp, #0x58]
	lsl r0, r0, #0xa
	add r3, r1, r0
	ldr r1, [sp, #0x4]
	ldr r0, _0202158C ; =0x00000000
	adc r1, r0
	str r1, [sp, #0x4]
	lsl r0, r1, #0x14
	lsr r1, r3, #0xc
	orr r1, r0
	mov r0, #0x2
	lsl r0, r0, #0xa
	mov r3, r12
	add r0, r3, r0
	ldr r3, _0202158C ; =0x00000000
	adc r2, r3
	lsl r2, r2, #0x14
	lsr r0, r0, #0xc
	orr r0, r2
	add r1, r1, r0
	ldr r0, [sp, #0x18]
	add r0, r0, r1
	ldr r1, [sp, #0x5c]
	cmp r4, r1
	bge _02021560
	add r1, r4, #0x0
	ldr r4, [sp, #0x5c]
	str r1, [sp, #0x5c]
_02021560:
	cmp r0, r5
	bge _0202156A
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r5, r1, #0x0
_0202156A:
	cmp r4, #0x0
	ble _02021586
	ldr r2, [r6, #0xc]
	ldr r1, [sp, #0x5c]
	cmp r1, r2
	bge _02021586
	cmp r0, #0x0
	ble _02021586
	ldr r0, [r6, #0x8]
	cmp r5, r0
	bge _02021586
	add sp, #0x60
	mov r0, #0x1
	pop {r3-r7, pc}
_02021586:
	mov r0, #0x0
	add sp, #0x60
	pop {r3-r7, pc}
	.balign 4
_0202158C: .word 0x00000000

	thumb_func_start FUN_02021590
FUN_02021590: ; 0x02021590
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r6, r1, #0x0
	ldr r0, [sp, #0x20]
	mov r1, #0x78
	add r7, r2, #0x0
	str r3, [sp, #0x4]
	bl FUN_02016998
	add r4, r0, #0x0
	beq _020215C0
	ldr r1, [sp, #0x20]
	ldr r3, [sp, #0x4]
	str r1, [sp, #0x0]
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_02021600
	ldr r2, [sp, #0x20]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_020216D4
_020215C0:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020215C8
FUN_020215C8: ; 0x020215C8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02021728
	add r0, r4, #0x0
	bl FUN_020216B8
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020215E0
FUN_020215E0: ; 0x020215E0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	add r6, r2, #0x0
	cmp r1, r4
	beq _020215FC
	bl FUN_02021728
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020216D4
_020215FC:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02021600
FUN_02021600: ; 0x02021600
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r0, r1, #0x0
	ldr r1, [sp, #0x18]
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02006670
	str r0, [r5, #0x54]
	cmp r0, #0x0
	beq _020216A6
	add r1, r5, #0x0
	add r1, #0x5c
	str r1, [sp, #0x0]
	add r1, r4, #0x0
	mov r2, #0x0
	mov r3, #0x10
	bl FUN_02006814
	str r6, [r5, #0x6c]
	cmp r6, #0x0
	beq _02021638
	mov r0, #0x0
	str r0, [r5, #0x74]
	ldr r0, _020216AC ; =FUN_0202192C
	str r0, [r5, #0x70]
	b _02021660
_02021638:
	ldr r0, [r5, #0x60]
	cmp r0, #0x0
	bne _02021642
	bl ErrorHandling
_02021642:
	ldr r0, [sp, #0x18]
	ldr r1, [r5, #0x64]
	bl FUN_02016998
	str r0, [r5, #0x74]
	ldr r0, _020216B0 ; =FUN_02021924
	add r1, r4, #0x0
	str r0, [r5, #0x70]
	ldr r0, [r5, #0x74]
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x54]
	ldr r2, [r5, #0x60]
	ldr r3, [r5, #0x64]
	bl FUN_02006814
_02021660:
	add r0, r5, #0x0
	add r0, #0x6a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bhi _02021674
	add r0, r5, #0x0
	add r0, #0x6b
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bls _02021678
_02021674:
	bl ErrorHandling
_02021678:
	add r0, r5, #0x0
	add r0, #0x6a
	ldrb r0, [r0, #0x0]
	ldr r2, _020216B4 ; =0x020EE668
	sub r0, r0, #0x1
	lsl r3, r0, #0x1
	add r0, r5, #0x0
	add r0, #0x6b
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r2, r3
	ldrb r0, [r1, r0]
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	add r0, #0x6b
	ldrb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x6a
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x4
	mul r0, r1
	str r0, [r5, #0xc]
	str r4, [r5, #0x58]
_020216A6:
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_020216AC: .word FUN_0202192C
_020216B0: .word FUN_02021924
_020216B4: .word 0x020EE668

	thumb_func_start FUN_020216B8
FUN_020216B8: ; 0x020216B8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x74]
	cmp r0, #0x0
	beq _020216C6
	bl FUN_02016A18
_020216C6:
	ldr r0, [r4, #0x54]
	cmp r0, #0x0
	beq _020216D0
	bl FUN_020066F4
_020216D0:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020216D4
FUN_020216D4: ; 0x020216D4
	push {r3, lr}
	add r3, r1, #0x0
	add r1, r2, #0x0
	str r3, [r0, #0x0]
	ldr r2, _020216E8 ; =0x020EE66C
	lsl r3, r3, #0x2
	ldr r2, [r2, r3]
	blx r2
	pop {r3, pc}
	nop
_020216E8: .word 0x020EE66C

	thumb_func_start FUN_020216EC
FUN_020216EC: ; 0x020216EC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0xc]
	ldr r0, [r5, #0x64]
	add r4, r2, #0x0
	mul r4, r0
	add r0, r1, #0x0
	add r1, r4, #0x0
	bl FUN_02016998
	str r0, [r5, #0x10]
	ldr r0, _02021718 ; =FUN_02021774
	add r3, r4, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x10]
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r2, [r5, #0x5c]
	bl FUN_02006814
	pop {r3-r5, pc}
	.balign 4
_02021718: .word FUN_02021774

	thumb_func_start FUN_0202171C
FUN_0202171C: ; 0x0202171C
	ldr r1, _02021724 ; =FUN_0202181C
	str r1, [r0, #0x4]
	bx lr
	nop
_02021724: .word FUN_0202181C

	thumb_func_start FUN_02021728
FUN_02021728: ; 0x02021728
	push {r3, lr}
	ldr r1, [r0, #0x0]
	lsl r2, r1, #0x2
	ldr r1, _02021738 ; =0x020EE674
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_02021738: .word 0x020EE674

	thumb_func_start FUN_0202173C
FUN_0202173C: ; 0x0202173C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x10]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x10]
	pop {r4, pc}

	thumb_func_start FUN_0202174C
FUN_0202174C: ; 0x0202174C
	bx lr
	.balign 4

	thumb_func_start FUN_02021750
FUN_02021750: ; 0x02021750
	push {r3, lr}
	ldr r3, [r0, #0x64]
	cmp r1, r3
	bhi _02021764
	sub r1, r1, #0x1
	lsl r1, r1, #0x10
	ldr r3, [r0, #0x4]
	lsr r1, r1, #0x10
	blx r3
	pop {r3, pc}
_02021764:
	add r0, r2, #0x0
	mov r1, #0x0
	add r0, #0x80
	strb r1, [r0, #0x0]
	add r2, #0x81
	strb r1, [r2, #0x0]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02021774
FUN_02021774: ; 0x02021774
	push {r3-r7, lr}
	str r1, [sp, #0x0]
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r1, [r7, #0xc]
	add r5, r0, #0x0
	ldr r0, [r7, #0x8]
	add r6, r2, #0x0
	mul r5, r1
	ldr r4, [r7, #0x10]
	cmp r0, #0x3
	bhi _02021802
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02021798: ; jump table (using 16-bit offset)
	.short _020217A0 - _02021798 - 2; case 0
	.short _020217AA - _02021798 - 2; case 1
	.short _020217C0 - _02021798 - 2; case 2
	.short _020217D6 - _02021798 - 2; case 3
_020217A0:
	add r0, r4, r5
	add r1, r6, #0x0
	bl FUN_0201C100
	b _02021802
_020217AA:
	add r0, r4, r5
	add r1, r6, #0x0
	bl FUN_0201C100
	add r0, r4, r5
	add r1, r6, #0x0
	add r0, #0x10
	add r1, #0x40
	bl FUN_0201C100
	b _02021802
_020217C0:
	add r0, r4, r5
	add r1, r6, #0x0
	bl FUN_0201C100
	add r0, r4, r5
	add r1, r6, #0x0
	add r0, #0x10
	add r1, #0x20
	bl FUN_0201C100
	b _02021802
_020217D6:
	add r0, r4, r5
	add r1, r6, #0x0
	bl FUN_0201C100
	add r0, r4, r5
	add r1, r6, #0x0
	add r0, #0x10
	add r1, #0x20
	bl FUN_0201C100
	add r0, r4, r5
	add r1, r6, #0x0
	add r0, #0x20
	add r1, #0x40
	bl FUN_0201C100
	add r0, r4, r5
	add r1, r6, #0x0
	add r0, #0x30
	add r1, #0x60
	bl FUN_0201C100
_02021802:
	ldr r1, [sp, #0x0]
	ldr r2, [r7, #0x70]
	add r0, r7, #0x0
	blx r2
	add r1, r6, #0x0
	add r1, #0x80
	add r7, #0x69
	strb r0, [r1, #0x0]
	ldrb r0, [r7, #0x0]
	add r6, #0x81
	strb r0, [r6, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202181C
FUN_0202181C: ; 0x0202181C
	push {r3-r7, lr}
	add r4, r0, #0x0
	ldr r6, [r4, #0xc]
	add r0, #0x14
	str r0, [sp, #0x0]
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r2, r7, #0x0
	ldr r3, [r4, #0x5c]
	mul r2, r6
	add r2, r3, r2
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	add r3, r6, #0x0
	bl FUN_02006814
	ldr r0, [r4, #0x8]
	cmp r0, #0x3
	bhi _020218C0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202184E: ; jump table (using 16-bit offset)
	.short _02021856 - _0202184E - 2; case 0
	.short _02021862 - _0202184E - 2; case 1
	.short _0202187A - _0202184E - 2; case 2
	.short _02021892 - _0202184E - 2; case 3
_02021856:
	add r0, r4, #0x0
	add r0, #0x14
	add r1, r5, #0x0
	bl FUN_0201C100
	b _020218C0
_02021862:
	add r0, r4, #0x0
	add r0, #0x14
	add r1, r5, #0x0
	bl FUN_0201C100
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r0, #0x24
	add r1, #0x40
	bl FUN_0201C100
	b _020218C0
_0202187A:
	add r0, r4, #0x0
	add r0, #0x14
	add r1, r5, #0x0
	bl FUN_0201C100
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r0, #0x24
	add r1, #0x20
	bl FUN_0201C100
	b _020218C0
_02021892:
	add r0, r4, #0x0
	add r0, #0x14
	add r1, r5, #0x0
	bl FUN_0201C100
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r0, #0x24
	add r1, #0x20
	bl FUN_0201C100
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r0, #0x34
	add r1, #0x40
	bl FUN_0201C100
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r0, #0x44
	add r1, #0x60
	bl FUN_0201C100
_020218C0:
	ldr r2, [r4, #0x70]
	add r0, r4, #0x0
	add r1, r7, #0x0
	blx r2
	add r1, r5, #0x0
	add r1, #0x80
	add r4, #0x69
	strb r0, [r1, #0x0]
	ldrb r0, [r4, #0x0]
	add r5, #0x81
	strb r0, [r5, #0x0]
	pop {r3-r7, pc}

	thumb_func_start FUN_020218D8
FUN_020218D8: ; 0x020218D8
	push {r3-r7, lr}
	add r4, r1, #0x0
	ldrh r1, [r4, #0x0]
	add r5, r0, #0x0
	ldr r0, _0202191C ; =0x0000FFFF
	add r7, r2, #0x0
	mov r6, #0x0
	cmp r1, r0
	beq _02021916
_020218EA:
	ldr r0, _02021920 ; =0x0000FFFE
	cmp r1, r0
	bne _02021900
	add r0, r4, #0x0
	bl FUN_0201B8B8
	add r4, r0, #0x0
	ldrh r1, [r4, #0x0]
	ldr r0, _0202191C ; =0x0000FFFF
	cmp r1, r0
	beq _02021916
_02021900:
	ldr r2, [r5, #0x70]
	add r0, r5, #0x0
	sub r1, r1, #0x1
	blx r2
	add r4, r4, #0x2
	add r0, r7, r0
	add r6, r6, r0
	ldrh r1, [r4, #0x0]
	ldr r0, _0202191C ; =0x0000FFFF
	cmp r1, r0
	bne _020218EA
_02021916:
	sub r0, r6, r7
	pop {r3-r7, pc}
	nop
_0202191C: .word 0x0000FFFF
_02021920: .word 0x0000FFFE

	thumb_func_start FUN_02021924
FUN_02021924: ; 0x02021924
	ldr r0, [r0, #0x74]
	ldrb r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start FUN_0202192C
FUN_0202192C: ; 0x0202192C
	add r0, #0x68
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02021934
FUN_02021934: ; 0x02021934
	push {r3-r7, lr}
	add r5, r1, #0x0
	ldrh r1, [r5, #0x0]
	add r7, r0, #0x0
	mov r4, #0x0
	ldr r0, _02021994 ; =0x0000FFFF
	add r6, r2, #0x0
	str r4, [sp, #0x0]
	cmp r1, r0
	beq _02021986
_02021948:
	ldr r0, _02021998 ; =0x0000FFFE
	cmp r1, r0
	bne _02021958
	add r0, r5, #0x0
	bl FUN_0201B8B8
	add r5, r0, #0x0
	b _0202197E
_02021958:
	mov r0, #0xe
	lsl r0, r0, #0xc
	cmp r1, r0
	bne _02021970
	ldr r0, [sp, #0x0]
	sub r1, r4, r6
	cmp r0, r1
	bhs _0202196A
	str r1, [sp, #0x0]
_0202196A:
	mov r4, #0x0
	add r5, r5, #0x2
	b _0202197E
_02021970:
	ldr r2, [r7, #0x70]
	add r0, r7, #0x0
	sub r1, r1, #0x1
	blx r2
	add r0, r6, r0
	add r4, r4, r0
	add r5, r5, #0x2
_0202197E:
	ldrh r1, [r5, #0x0]
	ldr r0, _02021994 ; =0x0000FFFF
	cmp r1, r0
	bne _02021948
_02021986:
	ldr r0, [sp, #0x0]
	sub r1, r4, r6
	cmp r0, r1
	bhs _02021990
	str r1, [sp, #0x0]
_02021990:
	ldr r0, [sp, #0x0]
	pop {r3-r7, pc}
	.balign 4
_02021994: .word 0x0000FFFF
_02021998: .word 0x0000FFFE

	thumb_func_start FUN_0202199C
FUN_0202199C: ; 0x0202199C
	push {r3-r7, lr}
	add r5, r1, #0x0
	ldrh r1, [r5, #0x0]
	add r6, r0, #0x0
	ldr r0, _020219EC ; =0x0000FFFF
	mov r4, #0x0
	cmp r1, r0
	beq _020219E8
	sub r7, r0, #0x1
_020219AE:
	cmp r1, r7
	bne _020219D4
	add r0, r5, #0x0
	bl FUN_0201B8E0
	ldr r1, _020219F0 ; =0x00000203
	cmp r0, r1
	bne _020219CA
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0201B914
	add r4, r0, #0x0
	sub r4, #0xc
_020219CA:
	add r0, r5, #0x0
	bl FUN_0201B8B8
	add r5, r0, #0x0
	b _020219E0
_020219D4:
	ldr r2, [r6, #0x70]
	add r0, r6, #0x0
	sub r1, r1, #0x1
	blx r2
	add r4, r4, r0
	add r5, r5, #0x2
_020219E0:
	ldrh r1, [r5, #0x0]
	ldr r0, _020219EC ; =0x0000FFFF
	cmp r1, r0
	bne _020219AE
_020219E8:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_020219EC: .word 0x0000FFFF
_020219F0: .word 0x00000203

	thumb_func_start FUN_020219F4
FUN_020219F4: ; 0x020219F4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	lsl r1, r4, #0x1
	add r1, #0xa
	bl FUN_02016998
	cmp r0, #0x0
	beq _02021A14
	ldr r1, _02021A18 ; =0xB6F8D2EC
	str r1, [r0, #0x4]
	strh r4, [r0, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x2]
	ldr r1, _02021A1C ; =0x0000FFFF
	strh r1, [r0, #0x8]
_02021A14:
	pop {r4, pc}
	nop
_02021A18: .word 0xB6F8D2EC
_02021A1C: .word 0x0000FFFF

	thumb_func_start FUN_02021A20
FUN_02021A20: ; 0x02021A20
	push {r4, lr}
	add r4, r0, #0x0
	bne _02021A2A
	bl ErrorHandling
_02021A2A:
	ldr r1, [r4, #0x4]
	ldr r0, _02021A44 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021A36
	bl ErrorHandling
_02021A36:
	ldr r0, _02021A48 ; =0xB6F8D2ED
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	nop
_02021A44: .word 0xB6F8D2EC
_02021A48: .word 0xB6F8D2ED

	thumb_func_start FUN_02021A4C
FUN_02021A4C: ; 0x02021A4C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02021A56
	bl ErrorHandling
_02021A56:
	ldr r1, [r4, #0x4]
	ldr r0, _02021A6C ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021A62
	bl ErrorHandling
_02021A62:
	mov r0, #0x0
	strh r0, [r4, #0x2]
	ldr r0, _02021A70 ; =0x0000FFFF
	strh r0, [r4, #0x8]
	pop {r4, pc}
	.balign 4
_02021A6C: .word 0xB6F8D2EC
_02021A70: .word 0x0000FFFF

	thumb_func_start FUN_02021A74
FUN_02021A74: ; 0x02021A74
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021A82
	bl ErrorHandling
_02021A82:
	ldr r1, [r5, #0x4]
	ldr r0, _02021AC8 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021A8E
	bl ErrorHandling
_02021A8E:
	cmp r4, #0x0
	bne _02021A96
	bl ErrorHandling
_02021A96:
	ldr r1, [r4, #0x4]
	ldr r0, _02021AC8 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021AA2
	bl ErrorHandling
_02021AA2:
	ldrh r2, [r4, #0x2]
	ldrh r0, [r5, #0x0]
	cmp r0, r2
	bls _02021AC0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r2, #0x1
	add r0, #0x8
	add r1, #0x8
	lsl r2, r2, #0x1
	bl memcpy
	ldrh r0, [r4, #0x2]
	strh r0, [r5, #0x2]
	pop {r3-r5, pc}
_02021AC0:
	bl ErrorHandling
	pop {r3-r5, pc}
	nop
_02021AC8: .word 0xB6F8D2EC

	thumb_func_start FUN_02021ACC
FUN_02021ACC: ; 0x02021ACC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021ADA
	bl ErrorHandling
_02021ADA:
	ldr r1, [r5, #0x4]
	ldr r0, _02021B00 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021AE6
	bl ErrorHandling
_02021AE6:
	ldrh r0, [r5, #0x2]
	add r1, r4, #0x0
	add r0, r0, #0x1
	bl FUN_020219F4
	add r4, r0, #0x0
	beq _02021AFA
	add r1, r5, #0x0
	bl FUN_02021A74
_02021AFA:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_02021B00: .word 0xB6F8D2EC

	thumb_func_start FUN_02021B04
FUN_02021B04: ; 0x02021B04
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [sp, #0x20]
	add r6, r1, #0x0
	add r7, r3, #0x0
	str r2, [sp, #0x0]
	str r0, [sp, #0x20]
	cmp r5, #0x0
	bne _02021B1C
	bl ErrorHandling
_02021B1C:
	ldr r1, [r5, #0x4]
	ldr r0, _02021C1C ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021B28
	bl ErrorHandling
_02021B28:
	cmp r6, #0x0
	bge _02021B30
	mov r4, #0x1
	b _02021B32
_02021B30:
	mov r4, #0x0
_02021B32:
	ldr r0, [sp, #0x0]
	ldrh r1, [r5, #0x0]
	add r0, r0, r4
	cmp r1, r0
	bls _02021C14
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	bne _02021B48
	ldr r0, _02021C20 ; =0x020EE67C
	str r0, [sp, #0x4]
	b _02021B4C
_02021B48:
	ldr r0, _02021C24 ; =0x020EE690
	str r0, [sp, #0x4]
_02021B4C:
	add r0, r5, #0x0
	bl FUN_02021A4C
	cmp r4, #0x0
	beq _02021B74
	mov r0, #0x0
	mvn r0, r0
	mul r6, r0
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	bne _02021B66
	mov r0, #0xf1
	b _02021B68
_02021B66:
	ldr r0, _02021C28 ; =0x000001BE
_02021B68:
	ldrh r2, [r5, #0x2]
	add r1, r2, #0x1
	strh r1, [r5, #0x2]
	lsl r1, r2, #0x1
	add r1, r5, r1
	strh r0, [r1, #0x8]
_02021B74:
	ldr r0, [sp, #0x0]
	lsl r1, r0, #0x2
	ldr r0, _02021C2C ; =0x020EE6A0
	ldr r4, [r0, r1]
	cmp r4, #0x0
	beq _02021C06
_02021B80:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl _u32_div_f
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r0, r4, #0x0
	mul r0, r1
	sub r6, r6, r0
	cmp r7, #0x2
	bne _02021BB4
	cmp r1, #0xa
	bhs _02021BA2
	ldr r0, [sp, #0x4]
	lsl r1, r1, #0x1
	ldrh r1, [r0, r1]
	b _02021BA4
_02021BA2:
	mov r1, #0xe2
_02021BA4:
	ldrh r0, [r5, #0x2]
	add r2, r0, #0x0
	add r2, r2, #0x1
	lsl r0, r0, #0x1
	strh r2, [r5, #0x2]
	add r0, r5, r0
	strh r1, [r0, #0x8]
	b _02021BFA
_02021BB4:
	cmp r1, #0x0
	bne _02021BBC
	cmp r4, #0x1
	bne _02021BDC
_02021BBC:
	mov r7, #0x2
	cmp r1, #0xa
	bhs _02021BCA
	ldr r0, [sp, #0x4]
	lsl r1, r1, #0x1
	ldrh r1, [r0, r1]
	b _02021BCC
_02021BCA:
	mov r1, #0xe2
_02021BCC:
	ldrh r0, [r5, #0x2]
	add r2, r0, #0x0
	add r2, r2, #0x1
	lsl r0, r0, #0x1
	strh r2, [r5, #0x2]
	add r0, r5, r0
	strh r1, [r0, #0x8]
	b _02021BFA
_02021BDC:
	cmp r7, #0x1
	bne _02021BFA
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	bne _02021BEA
	mov r1, #0x1
	b _02021BEC
_02021BEA:
	ldr r1, _02021C30 ; =0x000001E2
_02021BEC:
	ldrh r0, [r5, #0x2]
	add r2, r0, #0x0
	add r2, r2, #0x1
	lsl r0, r0, #0x1
	strh r2, [r5, #0x2]
	add r0, r5, r0
	strh r1, [r0, #0x8]
_02021BFA:
	add r0, r4, #0x0
	mov r1, #0xa
	bl _u32_div_f
	add r4, r0, #0x0
	bne _02021B80
_02021C06:
	ldrh r0, [r5, #0x2]
	ldr r1, _02021C34 ; =0x0000FFFF
	add sp, #0x8
	lsl r0, r0, #0x1
	add r0, r5, r0
	strh r1, [r0, #0x8]
	pop {r3-r7, pc}
_02021C14:
	bl ErrorHandling
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02021C1C: .word 0xB6F8D2EC
_02021C20: .word 0x020EE67C
_02021C24: .word 0x020EE690
_02021C28: .word 0x000001BE
_02021C2C: .word 0x020EE6A0
_02021C30: .word 0x000001E2
_02021C34: .word 0x0000FFFF

	thumb_func_start FUN_02021C38
FUN_02021C38: ; 0x02021C38
	push {r3-r7, lr}
	sub sp, #0x10
	str r1, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x8]
	str r1, [sp, #0xc]
	add r5, r1, #0x0
	ldrh r1, [r0, #0x2]
	mov r7, #0x1
	cmp r1, #0x12
	bls _02021C56
	ldr r0, [sp, #0x8]
	add sp, #0x10
	add r1, r0, #0x0
	pop {r3-r7, pc}
_02021C56:
	sub r1, r1, #0x1
	str r1, [sp, #0x4]
	bmi _02021CCC
	lsl r1, r1, #0x1
	add r4, r0, r1
_02021C60:
	ldrh r6, [r4, #0x8]
	mov r3, #0xa
	mov r0, #0x0
	add r1, r6, #0x0
	sub r1, #0xa2
	asr r2, r1, #0x1f
	sub r3, r1, r3
	mov r12, r2
	mov r3, r12
	sbc r3, r0
	blo _02021C98
	ldr r0, _02021CDC ; =0x00000121
	mov r3, #0xa
	sub r1, r6, r0
	asr r2, r1, #0x1f
	mov r0, #0x0
	sub r3, r1, r3
	mov r12, r2
	mov r3, r12
	sbc r3, r0
	blo _02021C98
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	add sp, #0x10
	pop {r3-r7, pc}
_02021C98:
	add r0, r1, #0x0
	add r1, r2, #0x0
	add r2, r7, #0x0
	add r3, r5, #0x0
	bl _ll_mul
	add r2, r1, #0x0
	ldr r1, [sp, #0x8]
	add r0, r1, r0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0xc]
	adc r0, r2
	str r0, [sp, #0xc]
	add r0, r7, #0x0
	add r1, r5, #0x0
	mov r2, #0xa
	mov r3, #0x0
	bl _ll_mul
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	add r5, r1, #0x0
	sub r4, r4, #0x2
	sub r0, r0, #0x1
	str r0, [sp, #0x4]
	bpl _02021C60
_02021CCC:
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_02021CDC: .word 0x00000121

	thumb_func_start FUN_02021CE0
FUN_02021CE0: ; 0x02021CE0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021CEE
	bl ErrorHandling
_02021CEE:
	ldr r1, [r5, #0x4]
	ldr r0, _02021D34 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021CFA
	bl ErrorHandling
_02021CFA:
	cmp r4, #0x0
	bne _02021D02
	bl ErrorHandling
_02021D02:
	ldr r1, [r4, #0x4]
	ldr r0, _02021D34 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021D0E
	bl ErrorHandling
_02021D0E:
	ldrh r1, [r5, #0x8]
	ldrh r0, [r4, #0x8]
	cmp r1, r0
	bne _02021D2E
	ldr r0, _02021D38 ; =0x0000FFFF
_02021D18:
	ldrh r1, [r5, #0x8]
	cmp r1, r0
	bne _02021D22
	mov r0, #0x0
	pop {r3-r5, pc}
_02021D22:
	add r5, r5, #0x2
	add r4, r4, #0x2
	ldrh r2, [r5, #0x8]
	ldrh r1, [r4, #0x8]
	cmp r2, r1
	beq _02021D18
_02021D2E:
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_02021D34: .word 0xB6F8D2EC
_02021D38: .word 0x0000FFFF

	thumb_func_start FUN_02021D3C
FUN_02021D3C: ; 0x02021D3C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02021D46
	bl ErrorHandling
_02021D46:
	ldr r1, [r4, #0x4]
	ldr r0, _02021D58 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021D52
	bl ErrorHandling
_02021D52:
	ldrh r0, [r4, #0x2]
	pop {r4, pc}
	nop
_02021D58: .word 0xB6F8D2EC

	thumb_func_start FUN_02021D5C
FUN_02021D5C: ; 0x02021D5C
	push {r3-r5, lr}
	add r4, r0, #0x0
	bne _02021D66
	bl ErrorHandling
_02021D66:
	ldr r1, [r4, #0x4]
	ldr r0, _02021D98 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021D72
	bl ErrorHandling
_02021D72:
	ldrh r1, [r4, #0x2]
	mov r3, #0x0
	mov r0, #0x1
	cmp r1, #0x0
	ble _02021D94
	mov r1, #0xe
	add r5, r4, #0x0
	lsl r1, r1, #0xc
_02021D82:
	ldrh r2, [r5, #0x8]
	cmp r2, r1
	bne _02021D8A
	add r0, r0, #0x1
_02021D8A:
	ldrh r2, [r4, #0x2]
	add r3, r3, #0x1
	add r5, r5, #0x2
	cmp r3, r2
	blt _02021D82
_02021D94:
	pop {r3-r5, pc}
	nop
_02021D98: .word 0xB6F8D2EC

	thumb_func_start FUN_02021D9C
FUN_02021D9C: ; 0x02021D9C
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r7, r0, #0x0
	add r6, r2, #0x0
	cmp r5, #0x0
	bne _02021DAC
	bl ErrorHandling
_02021DAC:
	ldr r1, [r5, #0x4]
	ldr r0, _02021E24 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021DB8
	bl ErrorHandling
_02021DB8:
	cmp r7, #0x0
	bne _02021DC0
	bl ErrorHandling
_02021DC0:
	ldr r1, [r7, #0x4]
	ldr r0, _02021E24 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021DCC
	bl ErrorHandling
_02021DCC:
	mov r4, #0x0
	cmp r6, #0x0
	beq _02021DF6
	ldrh r0, [r5, #0x2]
	cmp r0, #0x0
	ble _02021DF6
	mov r1, #0xe
	add r0, r5, #0x0
	lsl r1, r1, #0xc
_02021DDE:
	ldrh r2, [r0, #0x8]
	cmp r2, r1
	bne _02021DEC
	sub r6, r6, #0x1
	bne _02021DEC
	add r4, r4, #0x1
	b _02021DF6
_02021DEC:
	ldrh r2, [r5, #0x2]
	add r4, r4, #0x1
	add r0, r0, #0x2
	cmp r4, r2
	blt _02021DDE
_02021DF6:
	add r0, r7, #0x0
	bl FUN_02021A4C
	ldrh r0, [r5, #0x2]
	cmp r4, r0
	bge _02021E20
	lsl r0, r4, #0x1
	add r6, r5, r0
_02021E06:
	ldrh r1, [r6, #0x8]
	mov r0, #0xe
	lsl r0, r0, #0xc
	cmp r1, r0
	beq _02021E20
	add r0, r7, #0x0
	bl FUN_02021FB0
	ldrh r0, [r5, #0x2]
	add r4, r4, #0x1
	add r6, r6, #0x2
	cmp r4, r0
	blt _02021E06
_02021E20:
	pop {r3-r7, pc}
	nop
_02021E24: .word 0xB6F8D2EC

	thumb_func_start FUN_02021E28
FUN_02021E28: ; 0x02021E28
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021E36
	bl ErrorHandling
_02021E36:
	ldr r1, [r5, #0x4]
	ldr r0, _02021E84 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021E42
	bl ErrorHandling
_02021E42:
	mov r0, #0x0
	strh r0, [r5, #0x2]
	ldrh r1, [r4, #0x0]
	ldr r0, _02021E88 ; =0x0000FFFF
	cmp r1, r0
	beq _02021E76
	add r1, r0, #0x0
_02021E50:
	ldrh r2, [r5, #0x0]
	ldrh r0, [r5, #0x2]
	sub r2, r2, #0x1
	cmp r0, r2
	blt _02021E60
	bl ErrorHandling
	b _02021E76
_02021E60:
	add r2, r0, #0x0
	add r2, r2, #0x1
	strh r2, [r5, #0x2]
	ldrh r2, [r4, #0x0]
	lsl r0, r0, #0x1
	add r0, r5, r0
	add r4, r4, #0x2
	strh r2, [r0, #0x8]
	ldrh r0, [r4, #0x0]
	cmp r0, r1
	bne _02021E50
_02021E76:
	ldrh r0, [r5, #0x2]
	ldr r1, _02021E88 ; =0x0000FFFF
	lsl r0, r0, #0x1
	add r0, r5, r0
	strh r1, [r0, #0x8]
	pop {r3-r5, pc}
	nop
_02021E84: .word 0xB6F8D2EC
_02021E88: .word 0x0000FFFF

	thumb_func_start FUN_02021E8C
FUN_02021E8C: ; 0x02021E8C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r2, #0x0
	cmp r5, #0x0
	bne _02021E9C
	bl ErrorHandling
_02021E9C:
	ldr r1, [r5, #0x4]
	ldr r0, _02021EE8 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021EA8
	bl ErrorHandling
_02021EA8:
	ldrh r0, [r5, #0x0]
	cmp r4, r0
	bhi _02021EE2
	lsl r6, r4, #0x1
	add r0, r5, #0x0
	add r0, #0x8
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl memcpy
	mov r2, #0x0
	cmp r4, #0x0
	bls _02021ED4
	ldr r0, _02021EEC ; =0x0000FFFF
	add r3, r5, #0x0
_02021EC6:
	ldrh r1, [r3, #0x8]
	cmp r1, r0
	beq _02021ED4
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, r4
	blo _02021EC6
_02021ED4:
	strh r2, [r5, #0x2]
	cmp r2, r4
	bne _02021EE6
	ldr r1, _02021EEC ; =0x0000FFFF
	add r0, r5, r6
	strh r1, [r0, #0x6]
	pop {r3-r7, pc}
_02021EE2:
	bl ErrorHandling
_02021EE6:
	pop {r3-r7, pc}
	.balign 4
_02021EE8: .word 0xB6F8D2EC
_02021EEC: .word 0x0000FFFF

	thumb_func_start FUN_02021EF0
FUN_02021EF0: ; 0x02021EF0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	cmp r5, #0x0
	bne _02021F00
	bl ErrorHandling
_02021F00:
	ldr r1, [r5, #0x4]
	ldr r0, _02021F28 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021F0C
	bl ErrorHandling
_02021F0C:
	ldrh r0, [r5, #0x2]
	add r2, r0, #0x1
	cmp r2, r4
	bhi _02021F22
	add r5, #0x8
	add r0, r6, #0x0
	add r1, r5, #0x0
	lsl r2, r2, #0x1
	bl memcpy
	pop {r4-r6, pc}
_02021F22:
	bl ErrorHandling
	pop {r4-r6, pc}
	.balign 4
_02021F28: .word 0xB6F8D2EC

	thumb_func_start FUN_02021F2C
FUN_02021F2C: ; 0x02021F2C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02021F36
	bl ErrorHandling
_02021F36:
	ldr r1, [r4, #0x4]
	ldr r0, _02021F48 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021F42
	bl ErrorHandling
_02021F42:
	add r4, #0x8
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02021F48: .word 0xB6F8D2EC

	thumb_func_start FUN_02021F4C
FUN_02021F4C: ; 0x02021F4C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021F5A
	bl ErrorHandling
_02021F5A:
	ldr r1, [r5, #0x4]
	ldr r0, _02021FAC ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021F66
	bl ErrorHandling
_02021F66:
	cmp r4, #0x0
	bne _02021F6E
	bl ErrorHandling
_02021F6E:
	ldr r1, [r4, #0x4]
	ldr r0, _02021FAC ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021F7A
	bl ErrorHandling
_02021F7A:
	ldrh r2, [r4, #0x2]
	ldrh r0, [r5, #0x2]
	add r1, r0, r2
	add r3, r1, #0x1
	ldrh r1, [r5, #0x0]
	cmp r3, r1
	bgt _02021FA6
	add r1, r5, #0x0
	add r1, #0x8
	lsl r0, r0, #0x1
	add r0, r1, r0
	add r1, r4, #0x0
	add r2, r2, #0x1
	add r1, #0x8
	lsl r2, r2, #0x1
	bl memcpy
	ldrh r1, [r5, #0x2]
	ldrh r0, [r4, #0x2]
	add r0, r1, r0
	strh r0, [r5, #0x2]
	pop {r3-r5, pc}
_02021FA6:
	bl ErrorHandling
	pop {r3-r5, pc}
	.balign 4
_02021FAC: .word 0xB6F8D2EC

	thumb_func_start FUN_02021FB0
FUN_02021FB0: ; 0x02021FB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021FBE
	bl ErrorHandling
_02021FBE:
	ldr r1, [r5, #0x4]
	ldr r0, _02021FF0 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021FCA
	bl ErrorHandling
_02021FCA:
	ldrh r2, [r5, #0x2]
	ldrh r0, [r5, #0x0]
	add r1, r2, #0x1
	cmp r1, r0
	bge _02021FE8
	lsl r0, r2, #0x1
	strh r1, [r5, #0x2]
	add r0, r5, r0
	strh r4, [r0, #0x8]
	ldrh r0, [r5, #0x2]
	ldr r1, _02021FF4 ; =0x0000FFFF
	lsl r0, r0, #0x1
	add r0, r5, r0
	strh r1, [r0, #0x8]
	pop {r3-r5, pc}
_02021FE8:
	bl ErrorHandling
	pop {r3-r5, pc}
	nop
_02021FF0: .word 0xB6F8D2EC
_02021FF4: .word 0x0000FFFF

	thumb_func_start FUN_02021FF8
FUN_02021FF8: ; 0x02021FF8
	push {r4, lr}
	add r4, r0, #0x0
	bne _02022002
	bl ErrorHandling
_02022002:
	ldr r1, [r4, #0x4]
	ldr r0, _02022028 ; =0xB6F8D2EC
	cmp r1, r0
	beq _0202200E
	bl ErrorHandling
_0202200E:
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _02022026
	ldrh r1, [r4, #0x8]
	ldr r0, _0202202C ; =0x00000145
	cmp r1, r0
	blo _02022026
	add r0, #0x19
	cmp r1, r0
	bhi _02022026
	sub r1, #0x1a
	strh r1, [r4, #0x8]
_02022026:
	pop {r4, pc}
	.balign 4
_02022028: .word 0xB6F8D2EC
_0202202C: .word 0x00000145

	thumb_func_start FUN_02022030
FUN_02022030: ; 0x02022030
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	beq _02022044
	ldrh r1, [r0, #0x8]
	mov r0, #0xf1
	lsl r0, r0, #0x8
	cmp r1, r0
	bne _02022044
	mov r0, #0x1
	bx lr
_02022044:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02022048
FUN_02022048: ; 0x02022048
	push {r3-r7, lr}
	add r4, r1, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_02022030
	cmp r0, #0x0
	beq _020220B2
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	ldrh r0, [r0, #0x2]
	add r1, #0x8
	ldr r7, _020220BC ; =0x000001FF
	lsl r0, r0, #0x1
	add r3, r1, r0
	mov r0, #0x0
	add r4, #0xa
	add r1, r0, #0x0
_0202206C:
	ldrh r2, [r4, #0x0]
	asr r2, r0
	and r2, r7
	lsl r2, r2, #0x10
	add r0, #0x9
	lsr r2, r2, #0x10
	cmp r0, #0xf
	blt _02022094
	add r4, r4, #0x2
	sub r0, #0xf
	beq _02022094
	ldrh r6, [r4, #0x0]
	mov r5, #0x9
	sub r5, r5, r0
	lsl r6, r5
	ldr r5, _020220BC ; =0x000001FF
	and r5, r6
	orr r2, r5
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
_02022094:
	ldr r5, _020220BC ; =0x000001FF
	cmp r2, r5
	beq _020220A2
	strh r2, [r3, #0x0]
	add r3, r3, #0x2
	add r1, r1, #0x1
	b _0202206C
_020220A2:
	ldr r0, _020220C0 ; =0x0000FFFF
	strh r0, [r3, #0x0]
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x2]
	add r1, r0, r1
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x2]
	pop {r3-r7, pc}
_020220B2:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	bl FUN_02021F4C
	pop {r3-r7, pc}
	.balign 4
_020220BC: .word 0x000001FF
_020220C0: .word 0x0000FFFF

	thumb_func_start FUN_020220C4
FUN_020220C4: ; 0x020220C4
	push {r3-r7, lr}
	add r7, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	cmp r7, #0x0
	bne _020220D6
	bl ErrorHandling
_020220D6:
	ldr r0, [sp, #0x18]
	mov r1, #0x14
	bl FUN_02016998
	add r4, r0, #0x0
	beq _0202211C
	str r5, [r4, #0x0]
	str r7, [r4, #0x4]
	ldr r0, [sp, #0x0]
	str r6, [r4, #0x8]
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x18]
	lsl r1, r7, #0x2
	bl FUN_02016998
	str r0, [r4, #0x10]
	cmp r0, #0x0
	beq _02022114
	mov r6, #0x0
	cmp r7, #0x0
	bls _0202211C
	add r5, r6, #0x0
_02022102:
	ldr r0, [r4, #0x10]
	add r0, r0, r5
	bl FUN_02022120
	add r6, r6, #0x1
	add r5, r5, #0x4
	cmp r6, r7
	blo _02022102
	b _0202211C
_02022114:
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r4, #0x0
_0202211C:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02022120
FUN_02022120: ; 0x02022120
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strh r1, [r0, #0x2]
	bx lr
	.balign 4

	thumb_func_start FUN_0202212C
FUN_0202212C: ; 0x0202212C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02022136
	bl ErrorHandling
_02022136:
	ldr r0, [r4, #0x10]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_02022144
FUN_02022144: ; 0x02022144
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl FUN_02020A98
	str r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02022190
	bl FUN_02020AA4
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	bls _020221AE
	add r4, r6, #0x0
_02022164:
	ldr r0, [r5, #0x10]
	add r0, r0, r4
	ldrb r0, [r0, #0x1]
	cmp r0, #0x0
	ldr r0, [r5, #0x0]
	beq _02022178
	add r0, r0, r4
	bl FUN_02020A40
	b _0202217E
_02022178:
	add r0, r0, r4
	bl FUN_02020A6C
_0202217E:
	ldr r1, [r5, #0x10]
	add r6, r6, #0x1
	add r1, r1, r4
	strb r0, [r1, #0x1]
	ldr r0, [r5, #0x4]
	add r4, r4, #0x4
	cmp r6, r0
	blo _02022164
	b _020221AE
_02022190:
	ldr r0, [r5, #0x4]
	mov r3, #0x0
	str r3, [sp, #0x4]
	cmp r0, #0x0
	bls _020221AE
	add r2, r3, #0x0
	add r1, r3, #0x0
_0202219E:
	ldr r0, [r5, #0x10]
	add r3, r3, #0x1
	add r0, r0, r2
	strb r1, [r0, #0x1]
	ldr r0, [r5, #0x4]
	add r2, r2, #0x4
	cmp r3, r0
	blo _0202219E
_020221AE:
	mov r4, #0x0
	cmp r0, #0x0
	bls _020221E4
	add r7, r4, #0x0
_020221B6:
	ldr r3, [r5, #0x10]
	ldr r1, [sp, #0x0]
	add r0, r3, r7
	ldrb r3, [r3, r7]
	ldr r2, [sp, #0x4]
	lsl r6, r3, #0x2
	ldr r3, _020221E8 ; =0x020EE6CC
	ldr r3, [r3, r6]
	blx r3
	add r1, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	beq _020221DA
	ldr r2, [r5, #0xc]
	ldr r3, [r5, #0x8]
	add r0, r4, #0x0
	blx r3
_020221DA:
	ldr r0, [r5, #0x4]
	add r4, r4, #0x1
	add r7, r7, #0x4
	cmp r4, r0
	blo _020221B6
_020221E4:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020221E8: .word 0x020EE6CC

	thumb_func_start FUN_020221EC
FUN_020221EC: ; 0x020221EC
	push {r3, lr}
	ldrb r1, [r0, #0x1]
	cmp r1, #0x0
	beq _02022202
	cmp r2, #0x0
	beq _02022202
	mov r1, #0x1
	bl FUN_0202223C
	mov r0, #0x0
	pop {r3, pc}
_02022202:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}

	thumb_func_start FUN_02022208
FUN_02022208: ; 0x02022208
	push {r3, lr}
	ldrb r2, [r0, #0x1]
	cmp r2, #0x0
	beq _02022220
	ldrh r2, [r0, #0x2]
	ldr r1, _02022238 ; =0x0000FFFF
	cmp r2, r1
	bhs _0202221C
	add r1, r2, #0x1
	strh r1, [r0, #0x2]
_0202221C:
	mov r0, #0x2
	pop {r3, pc}
_02022220:
	cmp r1, #0x0
	beq _0202222E
	mov r1, #0x0
	bl FUN_0202223C
	mov r0, #0x3
	pop {r3, pc}
_0202222E:
	mov r1, #0x0
	bl FUN_0202223C
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_02022238: .word 0x0000FFFF

	thumb_func_start FUN_0202223C
FUN_0202223C: ; 0x0202223C
	strb r1, [r0, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02022244
FUN_02022244: ; 0x02022244
	push {r3-r4}
	ldr r3, [r0, #0xc]
	mov r2, #0x0
	sub r3, r3, #0x1
	beq _02022262
	ldr r4, [r0, #0x0]
_02022250:
	ldrh r3, [r4, #0x2]
	cmp r3, r1
	bhi _02022262
	ldr r3, [r0, #0xc]
	add r2, r2, #0x1
	sub r3, r3, #0x1
	add r4, r4, #0x2
	cmp r2, r3
	blo _02022250
_02022262:
	ldr r1, [r0, #0x4]
	ldrb r3, [r1, r2]
	add r1, sp, #0x0
	strb r3, [r1, #0x0]
	ldr r0, [r0, #0x8]
	ldrb r2, [r0, r2]
	strb r2, [r1, #0x1]
	ldrb r0, [r1, #0x0]
	lsl r1, r2, #0x8
	orr r0, r1
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0202227C
FUN_0202227C: ; 0x0202227C
	ldr r2, [r0, #0x0]
	str r2, [r1, #0xc]
	add r2, r0, #0x4
	str r2, [r1, #0x0]
	ldr r0, [r1, #0xc]
	lsl r0, r0, #0x1
	add r2, r2, r0
	str r2, [r1, #0x4]
	ldr r0, [r1, #0xc]
	add r0, r2, r0
	str r0, [r1, #0x8]
	bx lr

	thumb_func_start FUN_02022294
FUN_02022294: ; 0x02022294
	ldr r0, _020222A4 ; =0x021C59BC
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	ldr r0, _020222A8 ; =0x021C59BC
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020222A4: .word 0x021C59BC
_020222A8: .word 0x021C59BC

	thumb_func_start FUN_020222AC
FUN_020222AC: ; 0x020222AC
	ldr r3, _020222B0 ; =G3X_ResetMtxStack
	bx r3
	.balign 4
_020222B0: .word G3X_ResetMtxStack

	thumb_func_start FUN_020222B4
FUN_020222B4: ; 0x020222B4
	ldr r2, _020222C0 ; =0x021C59BC
	str r0, [r2, #0x4]
	str r1, [r2, #0x8]
	mov r0, #0x1
	str r0, [r2, #0x0]
	bx lr
	.balign 4
_020222C0: .word 0x021C59BC

	thumb_func_start FUN_020222C4
FUN_020222C4: ; 0x020222C4
	ldr r0, _020222E0 ; =0x021C59BC
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _020222DC
	ldr r1, [r0, #0x8]
	ldr r2, [r0, #0x4]
	lsl r1, r1, #0x1
	orr r2, r1
	ldr r1, _020222E4 ; =0x04000540
	str r2, [r1, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
_020222DC:
	bx lr
	nop
_020222E0: .word 0x021C59BC
_020222E4: .word 0x04000540

	thumb_func_start FUN_020222E8
FUN_020222E8: ; 0x020222E8
	mov r0, #0x5
	lsl r0, r0, #0x18
	bx lr
	.balign 4

	thumb_func_start FUN_020222F0
FUN_020222F0: ; 0x020222F0
	mov r0, #0x2
	lsl r0, r0, #0x8
	bx lr
	.balign 4

	thumb_func_start FUN_020222F8
FUN_020222F8: ; 0x020222F8
	ldr r0, _020222FC ; =0x05000400
	bx lr
	.balign 4
_020222FC: .word 0x05000400

	thumb_func_start FUN_02022300
FUN_02022300: ; 0x02022300
	mov r0, #0x2
	lsl r0, r0, #0x8
	bx lr
	.balign 4

	thumb_func_start FUN_02022308
FUN_02022308: ; 0x02022308
	ldr r0, _0202230C ; =0x05000200
	bx lr
	.balign 4
_0202230C: .word 0x05000200

	thumb_func_start FUN_02022310
FUN_02022310: ; 0x02022310
	ldr r0, _02022314 ; =0x05000600
	bx lr
	.balign 4
_02022314: .word 0x05000600

	thumb_func_start FUN_02022318
FUN_02022318: ; 0x02022318
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r1, #0x0
	mov r1, #0xc
	add r6, r0, #0x0
	add r5, r2, #0x0
	str r3, [sp, #0x4]
	bl FUN_02016998
	add r4, r0, #0x0
	str r6, [r4, #0x0]
	bl FUN_020BB7F4
	bl G3X_InitMtxStack
	mov r1, #0x2
	ldr r0, _020223B8 ; =0x04000540
	cmp r7, #0x0
	str r1, [r0, #0x0]
	bne _02022364
	lsl r0, r5, #0x7
	bl FUN_020AFA28
	add r6, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	bl FUN_02016998
	str r0, [r4, #0x8]
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r2, [r4, #0x8]
	lsl r0, r5, #0x11
	mov r1, #0x0
	add r3, r6, #0x0
	bl FUN_020AF9C4
	b _0202236E
_02022364:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x1
	bl FUN_020AEB70
_0202236E:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _02022398
	ldr r0, [sp, #0x20]
	lsl r0, r0, #0x8
	bl FUN_020AFBFC
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r5, #0x0
	bl FUN_02016998
	str r0, [r4, #0x4]
	ldr r0, [sp, #0x20]
	ldr r1, [r4, #0x4]
	lsl r0, r0, #0xd
	add r2, r5, #0x0
	mov r3, #0x1
	bl FUN_020AFBA8
	b _020223A4
_02022398:
	ldr r0, [sp, #0x20]
	mov r1, #0x1
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x10
	bl FUN_020AEB70
_020223A4:
	ldr r0, [sp, #0x24]
	cmp r0, #0x0
	beq _020223AE
	blx r0
	b _020223B2
_020223AE:
	bl FUN_020223D4
_020223B2:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020223B8: .word 0x04000540

	thumb_func_start FUN_020223BC
FUN_020223BC: ; 0x020223BC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	bl FUN_02016A18
	ldr r0, [r4, #0x8]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_020223D4
FUN_020223D4: ; 0x020223D4
	push {r3, lr}
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_0201E6E4
	ldr r0, _02022438 ; =0x04000008
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	strh r2, [r0, #0x0]
	add r0, #0x58
	ldrh r2, [r0, #0x0]
	ldr r1, _0202243C ; =0xFFFFCFFD
	and r1, r2
	strh r1, [r0, #0x0]
	ldrh r1, [r0, #0x0]
	ldr r2, _02022440 ; =0x0000CFEF
	and r1, r2
	strh r1, [r0, #0x0]
	add r1, r2, #0x0
	ldrh r3, [r0, #0x0]
	add r1, #0xc
	and r1, r3
	strh r1, [r0, #0x0]
	add r1, r2, #0x0
	ldrh r3, [r0, #0x0]
	add r1, #0x8
	sub r2, #0x10
	and r1, r3
	strh r1, [r0, #0x0]
	ldrh r1, [r0, #0x0]
	and r1, r2
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl G3X_SetFog
	mov r0, #0x0
	ldr r2, _02022444 ; =0x00007FFF
	add r1, r0, #0x0
	mov r3, #0x3f
	str r0, [sp, #0x0]
	bl G3X_SetClearColor
	ldr r1, _02022448 ; =0xBFFF0000
	ldr r0, _0202244C ; =0x04000580
	str r1, [r0, #0x0]
	pop {r3, pc}
	.balign 4
_02022438: .word 0x04000008
_0202243C: .word 0xFFFFCFFD
_02022440: .word 0x0000CFEF
_02022444: .word 0x00007FFF
_02022448: .word 0xBFFF0000
_0202244C: .word 0x04000580

	thumb_func_start FUN_02022450
FUN_02022450: ; 0x02022450
	push {r3, lr}
	bl FS_IsAvailable
	cmp r0, #0x0
	bne _02022460
	bl OS_Terminate
	pop {r3, pc}
_02022460:
	ldr r0, _020224BC ; =0x027FF00C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0202248A
	bl CARD_Init
	mov r2, #0x16
	ldr r0, _020224C0 ; =0x027FFE00
	ldr r1, _020224C4 ; =0x027FF000
	lsl r2, r2, #0x4
	bl MI_CpuCopy8
	mov r2, #0x16
	ldr r0, _020224C0 ; =0x027FFE00
	ldr r1, _020224C8 ; =0x027FFA80
	lsl r2, r2, #0x4
	bl MI_CpuCopy8
	ldr r1, _020224CC ; =0x4A414441
	ldr r0, _020224BC ; =0x027FF00C
	str r1, [r0, #0x0]
_0202248A:
	ldr r0, _020224D0 ; =0x020EE6D4
	mov r1, #0x3
	bl FS_FindArchive
	ldr r1, _020224C4 ; =0x027FF000
	ldr r2, [r1, #0x48]
	str r2, [r0, #0x2c]
	ldr r2, [r1, #0x4c]
	str r2, [r0, #0x30]
	ldr r2, [r1, #0x40]
	str r2, [r0, #0x34]
	ldr r2, [r1, #0x44]
	str r2, [r0, #0x38]
	ldr r2, [r1, #0xc]
	ldr r0, _020224CC ; =0x4A414441
	cmp r2, r0
	bne _020224B4
	ldrh r1, [r1, #0x10]
	ldr r0, _020224D4 ; =0x00003130
	cmp r1, r0
	beq _020224B8
_020224B4:
	bl OS_Terminate
_020224B8:
	pop {r3, pc}
	nop
_020224BC: .word 0x027FF00C
_020224C0: .word 0x027FFE00
_020224C4: .word 0x027FF000
_020224C8: .word 0x027FFA80
_020224CC: .word 0x4A414441
_020224D0: .word 0x020EE6D4
_020224D4: .word 0x00003130

	thumb_func_start FUN_020224D8
FUN_020224D8: ; 0x020224D8
	push {r4, lr}
	sub sp, #0x48
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FS_InitFile
	add r0, sp, #0x0
	add r1, r4, #0x0
	bl FS_OpenFile
	cmp r0, #0x0
	beq _020224FC
	ldr r1, [sp, #0x24]
	ldr r0, _02022500 ; =0x027FFC2C
	str r1, [r0, #0x0]
	mov r0, #0x0
	bl OS_ResetSystem
_020224FC:
	add sp, #0x48
	pop {r4, pc}
	.balign 4
_02022500: .word 0x027FFC2C

	thumb_func_start FUN_02022504
FUN_02022504: ; 0x02022504
	ldr r3, _0202250C ; =FUN_02022610
	mov r1, #0x1b
	bx r3
	nop
_0202250C: .word FUN_02022610

	thumb_func_start FUN_02022510
FUN_02022510: ; 0x02022510
	ldr r3, _02022518 ; =FUN_02022610
	mov r1, #0x23
	bx r3
	nop
_02022518: .word FUN_02022610

	thumb_func_start FUN_0202251C
FUN_0202251C: ; 0x0202251C
	ldr r3, _02022524 ; =FUN_02022610
	mov r1, #0x1f
	bx r3
	nop
_02022524: .word FUN_02022610

	thumb_func_start FUN_02022528
FUN_02022528: ; 0x02022528
	ldr r3, _02022530 ; =FUN_02022610
	mov r1, #0x20
	bx r3
	nop
_02022530: .word FUN_02022610

	thumb_func_start FUN_02022534
FUN_02022534: ; 0x02022534
	push {r3, lr}
	add r3, r2, #0x0
	mov r2, #0x0
	bl FUN_02023408
	pop {r3, pc}

	thumb_func_start FUN_02022540
FUN_02022540: ; 0x02022540
	ldr r3, _02022548 ; =FUN_020232BC
	add r2, r1, #0x0
	mov r1, #0x0
	bx r3
	.balign 4
_02022548: .word FUN_020232BC

	thumb_func_start FUN_0202254C
FUN_0202254C: ; 0x0202254C
	push {r4, lr}
	ldr r1, _020225E0 ; =0x000204A8
	mov r0, #0x1
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r2, _020225E0 ; =0x000204A8
	mov r0, #0x0
	add r1, r4, #0x0
	bl MIi_CpuClearFast
	ldr r0, _020225E4 ; =0x021C59C8
	str r4, [r0, #0x0]
	bl FUN_02023570
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	mov r0, #0x1
	str r0, [r4, #0x8]
	str r0, [r4, #0xc]
	add r0, r4, #0x0
	ldr r1, _020225E8 ; =0x00001021
	add r0, #0x14
	bl MATHi_CRC16InitTable
	ldr r0, _020225EC ; =0x00020224
	add r0, r4, r0
	bl FUN_020230E4
	ldr r0, _020225F0 ; =0x00020464
	ldr r1, _020225EC ; =0x00020224
	add r0, r4, r0
	add r1, r4, r1
	bl FUN_02023160
	ldr r1, _020225F4 ; =0x00020218
	mov r0, #0x0
	add r1, r4, r1
	mov r2, #0x8
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	bl FUN_02022AD8
	str r0, [r4, #0x10]
	cmp r0, #0x3
	bhi _020225DA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020225B8: ; jump table (using 16-bit offset)
	.short _020225D4 - _020225B8 - 2; case 0
	.short _020225C0 - _020225B8 - 2; case 1
	.short _020225C4 - _020225B8 - 2; case 2
	.short _020225D4 - _020225B8 - 2; case 3
_020225C0:
	mov r0, #0x0
	str r0, [r4, #0xc]
_020225C4:
	add r0, r4, #0x0
	bl FUN_02022D08
	mov r0, #0x1
	str r0, [r4, #0x4]
	mov r0, #0x0
	str r0, [r4, #0x8]
	b _020225DA
_020225D4:
	add r0, r4, #0x0
	bl FUN_020227DC
_020225DA:
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_020225E0: .word 0x000204A8
_020225E4: .word 0x021C59C8
_020225E8: .word 0x00001021
_020225EC: .word 0x00020224
_020225F0: .word 0x00020464
_020225F4: .word 0x00020218

	thumb_func_start FUN_020225F8
FUN_020225F8: ; 0x020225F8
	push {r3, lr}
	ldr r0, _0202260C ; =0x021C59C8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02022606
	bl ErrorHandling
_02022606:
	ldr r0, _0202260C ; =0x021C59C8
	ldr r0, [r0, #0x0]
	pop {r3, pc}
	.balign 4
_0202260C: .word 0x021C59C8

	thumb_func_start FUN_02022610
FUN_02022610: ; 0x02022610
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x24
	blt _0202261E
	bl ErrorHandling
_0202261E:
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r2, r5, r0
	lsl r0, r4, #0x4
	add r1, r5, r0
	ldr r0, _02022630 ; =0x0002022C
	ldr r0, [r1, r0]
	add r0, r2, r0
	pop {r3-r5, pc}
	.balign 4
_02022630: .word 0x0002022C

	thumb_func_start FUN_02022634
FUN_02022634: ; 0x02022634
	ldr r3, _02022638 ; =FUN_02022610
	bx r3
	.balign 4
_02022638: .word FUN_02022610

	thumb_func_start FUN_0202263C
FUN_0202263C: ; 0x0202263C
	push {r3-r7, lr}
	mov r1, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x3
	lsl r1, r1, #0xc
	bl FUN_020169D8
	add r6, r0, #0x0
	mov r0, #0x1
	bl FUN_02016444
	ldr r1, _020226F4 ; =0x00020220
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, r1]
	cmp r0, #0x0
	bne _02022660
	mov r2, #0x1
	b _02022662
_02022660:
	mov r2, #0x0
_02022662:
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	bl FUN_02023074
	ldr r1, _020226F8 ; =0x00020221
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, r1]
	cmp r0, #0x0
	bne _02022678
	mov r2, #0x1
	b _0202267A
_02022678:
	mov r2, #0x0
_0202267A:
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	bl FUN_02023074
	ldr r0, [sp, #0x0]
	ldr r3, _020226F4 ; =0x00020220
	add r2, r0, #0x0
	ldrb r2, [r2, r3]
	mov r1, #0x0
	bl FUN_02023074
	ldr r0, [sp, #0x0]
	ldr r3, _020226F8 ; =0x00020221
	add r2, r0, #0x0
	ldrb r2, [r2, r3]
	mov r1, #0x1
	bl FUN_02023074
	mov r0, #0x0
	mov r2, #0x1
	mvn r0, r0
	add r1, r6, #0x0
	lsl r2, r2, #0xc
	bl MIi_CpuClearFast
	mov r4, #0x0
	mov r7, #0x1
	add r5, r4, #0x0
	lsl r7, r7, #0xc
_020226B4:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020235D0
	add r0, r4, #0x0
	add r0, #0x40
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020235D0
	mov r0, #0x1
	lsl r0, r0, #0xc
	add r4, r4, #0x1
	add r5, r5, r0
	cmp r4, #0x40
	blt _020226B4
	add r0, r6, #0x0
	bl FUN_02016A18
	ldr r0, [sp, #0x0]
	bl FUN_020227DC
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	mov r0, #0x1
	bl FUN_02016454
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_020226F4: .word 0x00020220
_020226F8: .word 0x00020221

	thumb_func_start FUN_020226FC
FUN_020226FC: ; 0x020226FC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	bne _0202270A
	mov r0, #0x0
	pop {r4, pc}
_0202270A:
	bl FUN_02022D08
	cmp r0, #0x0
	beq _0202271C
	mov r0, #0x1
	str r0, [r4, #0x4]
	mov r1, #0x0
	str r1, [r4, #0x8]
	pop {r4, pc}
_0202271C:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02022720
FUN_02022720: ; 0x02022720
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0202272E
	mov r0, #0x3
	pop {r4, pc}
_0202272E:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _02022784
	mov r0, #0x1
	bl FUN_02016444
	ldr r0, _02022798 ; =0x00020220
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	bne _02022746
	mov r2, #0x1
	b _02022748
_02022746:
	mov r2, #0x0
_02022748:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02023074
	ldr r0, _0202279C ; =0x00020221
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	bne _0202275C
	mov r2, #0x1
	b _0202275E
_0202275C:
	mov r2, #0x0
_0202275E:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02023074
	ldr r2, _02022798 ; =0x00020220
	add r0, r4, #0x0
	ldrb r2, [r4, r2]
	mov r1, #0x0
	bl FUN_02023074
	ldr r2, _0202279C ; =0x00020221
	add r0, r4, #0x0
	ldrb r2, [r4, r2]
	mov r1, #0x1
	bl FUN_02023074
	mov r0, #0x1
	bl FUN_02016454
_02022784:
	add r0, r4, #0x0
	bl FUN_02023044
	cmp r0, #0x2
	bne _02022796
	mov r1, #0x1
	str r1, [r4, #0x4]
	mov r1, #0x0
	str r1, [r4, #0x8]
_02022796:
	pop {r4, pc}
	.balign 4
_02022798: .word 0x00020220
_0202279C: .word 0x00020221

	thumb_func_start FUN_020227A0
FUN_020227A0: ; 0x020227A0
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x2
	blt _020227AE
	bl ErrorHandling
_020227AE:
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	beq _020227B8
	bl ErrorHandling
_020227B8:
	ldr r0, [r5, #0x4]
	cmp r0, #0x1
	beq _020227C2
	bl ErrorHandling
_020227C2:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02022840
_020227CA:
	add r0, r5, #0x0
	bl FUN_02022854
	cmp r0, #0x0
	beq _020227CA
	cmp r0, #0x1
	beq _020227CA
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020227DC
FUN_020227DC: ; 0x020227DC
	add r2, r0, #0x0
	mov r0, #0x1
	str r0, [r2, #0x8]
	str r0, [r2, #0xc]
	mov r0, #0x85
	ldr r1, _020227F4 ; =0x00020224
	lsl r0, r0, #0x2
	ldr r3, _020227F8 ; =FUN_020231F4
	add r0, r2, r0
	add r1, r2, r1
	bx r3
	nop
_020227F4: .word 0x00020224
_020227F8: .word FUN_020231F4

	thumb_func_start FUN_020227FC
FUN_020227FC: ; 0x020227FC
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02022800
FUN_02022800: ; 0x02022800
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start FUN_02022804
FUN_02022804: ; 0x02022804
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02022808
FUN_02022808: ; 0x02022808
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_0202280C
FUN_0202280C: ; 0x0202280C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02022808
	cmp r0, #0x0
	beq _02022826
	add r0, r4, #0x0
	bl FUN_02022804
	cmp r0, #0x0
	beq _02022826
	mov r0, #0x1
	pop {r4, pc}
_02022826:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202282C
FUN_0202282C: ; 0x0202282C
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_02022830
FUN_02022830: ; 0x02022830
	ldr r0, _0202283C ; =0x021C59C8
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	str r1, [r0, #0xc]
	bx lr
	nop
_0202283C: .word 0x021C59C8

	thumb_func_start FUN_02022840
FUN_02022840: ; 0x02022840
	add r2, r1, #0x0
	ldr r1, _0202284C ; =0x0002047C
	ldr r3, _02022850 ; =FUN_02022DFC
	add r1, r0, r1
	bx r3
	nop
_0202284C: .word 0x0002047C
_02022850: .word FUN_02022DFC

	thumb_func_start FUN_02022854
FUN_02022854: ; 0x02022854
	push {r3-r5, lr}
	ldr r1, _02022878 ; =0x0002047C
	add r5, r0, #0x0
	add r1, r5, r1
	bl FUN_02022E78
	add r4, r0, #0x0
	beq _02022874
	cmp r4, #0x1
	beq _02022874
	ldr r1, _02022878 ; =0x0002047C
	add r0, r5, #0x0
	add r1, r5, r1
	add r2, r4, #0x0
	bl FUN_02022F80
_02022874:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02022878: .word 0x0002047C

	thumb_func_start FUN_0202287C
FUN_0202287C: ; 0x0202287C
	ldr r1, _02022884 ; =0x0002047C
	ldr r3, _02022888 ; =FUN_02022FF0
	add r1, r0, r1
	bx r3
	.balign 4
_02022884: .word 0x0002047C
_02022888: .word FUN_02022FF0

	thumb_func_start FUN_0202288C
FUN_0202288C: ; 0x0202288C
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start FUN_02022898
FUN_02022898: ; 0x02022898
	ldr r3, _020228A0 ; =MATH_CalcCRC16CCITT
	add r0, #0x14
	sub r2, #0x14
	bx r3
	.balign 4
_020228A0: .word MATH_CalcCRC16CCITT

	thumb_func_start FUN_020228A4
FUN_020228A4: ; 0x020228A4
	cmp r0, #0x0
	bne _020228AC
	mov r2, #0x0
	b _020228B0
_020228AC:
	mov r2, #0x1
	lsl r2, r2, #0x12
_020228B0:
	ldr r0, [r1, #0x4]
	add r0, r2, r0
	bx lr
	.balign 4

	thumb_func_start FUN_020228B8
FUN_020228B8: ; 0x020228B8
	push {r3-r5, lr}
	ldr r3, _020228DC ; =0x00020464
	add r3, r0, r3
	mov r0, #0xc
	mul r0, r2
	add r5, r3, r0
	ldr r0, [r5, #0x4]
	add r4, r1, r0
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	bne _020228D2
	bl ErrorHandling
_020228D2:
	ldr r0, [r5, #0x8]
	add r0, r4, r0
	sub r0, #0x14
	pop {r3-r5, pc}
	nop
_020228DC: .word 0x00020464

	thumb_func_start FUN_020228E0
FUN_020228E0: ; 0x020228E0
	push {r3-r7, lr}
	ldr r4, _02022934 ; =0x00020464
	add r3, r0, #0x0
	add r3, r3, r4
	add r5, r2, #0x0
	mov r4, #0xc
	mul r4, r5
	str r0, [sp, #0x0]
	add r7, r1, #0x0
	add r6, r3, r4
	bl FUN_020228B8
	add r4, r0, #0x0
	ldr r2, [r6, #0x8]
	ldr r0, [r4, #0x8]
	ldr r1, [r6, #0x4]
	cmp r0, r2
	beq _02022908
	mov r0, #0x0
	pop {r3-r7, pc}
_02022908:
	ldr r3, [r4, #0xc]
	ldr r0, _02022938 ; =0x20060623
	cmp r3, r0
	beq _02022914
	mov r0, #0x0
	pop {r3-r7, pc}
_02022914:
	ldrb r0, [r4, #0x10]
	cmp r0, r5
	beq _0202291E
	mov r0, #0x0
	pop {r3-r7, pc}
_0202291E:
	ldr r0, [sp, #0x0]
	add r1, r7, r1
	bl FUN_02022898
	ldrh r1, [r4, #0x12]
	cmp r1, r0
	bne _02022930
	mov r0, #0x1
	pop {r3-r7, pc}
_02022930:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02022934: .word 0x00020464
_02022938: .word 0x20060623

	thumb_func_start FUN_0202293C
FUN_0202293C: ; 0x0202293C
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r6, r1, #0x0
	add r5, r0, #0x0
	str r3, [sp, #0x0]
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r2, r3, #0x0
	bl FUN_020228B8
	add r4, r0, #0x0
	ldr r2, [sp, #0x0]
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_020228E0
	str r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	str r0, [r5, #0x4]
	ldr r0, [r4, #0x4]
	str r0, [r5, #0x8]
	pop {r3-r7, pc}

	thumb_func_start FUN_02022968
FUN_02022968: ; 0x02022968
	push {r3-r7, lr}
	ldr r3, _020229AC ; =0x00020464
	add r5, r0, #0x0
	add r7, r2, #0x0
	mov r4, #0xc
	add r3, r5, r3
	mul r4, r7
	str r1, [sp, #0x0]
	add r6, r3, r4
	bl FUN_020228B8
	ldr r2, _020229B0 ; =0x00020214
	add r4, r0, #0x0
	ldr r0, [r5, r2]
	ldr r1, [r6, #0x4]
	add r2, r2, #0x4
	str r0, [r4, #0x0]
	lsl r0, r7, #0x2
	add r0, r5, r0
	ldr r0, [r0, r2]
	ldr r2, [sp, #0x0]
	str r0, [r4, #0x4]
	ldr r0, [r6, #0x8]
	add r1, r2, r1
	str r0, [r4, #0x8]
	ldr r0, _020229B4 ; =0x20060623
	str r0, [r4, #0xc]
	strb r7, [r4, #0x10]
	ldr r2, [r6, #0x8]
	add r0, r5, #0x0
	bl FUN_02022898
	strh r0, [r4, #0x12]
	pop {r3-r7, pc}
	.balign 4
_020229AC: .word 0x00020464
_020229B0: .word 0x00020214
_020229B4: .word 0x20060623

	thumb_func_start FUN_020229B8
FUN_020229B8: ; 0x020229B8
	mov r2, #0x0
	mvn r2, r2
	cmp r0, r2
	bne _020229C8
	cmp r1, #0x0
	bne _020229C8
	add r0, r2, #0x0
	bx lr
_020229C8:
	cmp r0, #0x0
	bne _020229D8
	mov r2, #0x0
	mvn r2, r2
	cmp r1, r2
	bne _020229D8
	mov r0, #0x1
	bx lr
_020229D8:
	cmp r0, r1
	bls _020229E0
	mov r0, #0x1
	bx lr
_020229E0:
	cmp r0, r1
	bhs _020229E8
	mov r0, #0x1
	b _020229EA
_020229E8:
	mov r0, #0x0
_020229EA:
	neg r0, r0
	bx lr
	.balign 4

	thumb_func_start FUN_020229F0
FUN_020229F0: ; 0x020229F0
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r6, r1, #0x0
	ldr r0, [r7, #0x4]
	ldr r1, [r6, #0x4]
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_020229B8
	str r0, [sp, #0x0]
	ldr r0, [r7, #0x8]
	ldr r1, [r6, #0x8]
	bl FUN_020229B8
	ldr r2, [r7, #0x0]
	cmp r2, #0x0
	beq _02022A6A
	ldr r1, [r6, #0x0]
	cmp r1, #0x0
	beq _02022A6A
	ldr r1, [sp, #0x0]
	cmp r1, #0x0
	ble _02022A30
	cmp r0, #0x0
	bgt _02022A26
	bl ErrorHandling
_02022A26:
	mov r0, #0x0
	str r0, [r5, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _02022A66
_02022A30:
	bge _02022A44
	cmp r0, #0x0
	blt _02022A3A
	bl ErrorHandling
_02022A3A:
	mov r0, #0x1
	str r0, [r5, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02022A66
_02022A44:
	cmp r0, #0x0
	ble _02022A52
	mov r0, #0x0
	str r0, [r5, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _02022A66
_02022A52:
	bge _02022A5E
	mov r0, #0x1
	str r0, [r5, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02022A66
_02022A5E:
	mov r0, #0x0
	str r0, [r5, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x0]
_02022A66:
	mov r0, #0x2
	pop {r3-r7, pc}
_02022A6A:
	cmp r2, #0x0
	beq _02022A80
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	bne _02022A80
	mov r0, #0x0
	str r0, [r5, #0x0]
	mov r0, #0x2
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_02022A80:
	cmp r2, #0x0
	bne _02022A94
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _02022A94
	mov r0, #0x1
	str r0, [r5, #0x0]
	mov r1, #0x2
	str r1, [r4, #0x0]
	pop {r3-r7, pc}
_02022A94:
	mov r0, #0x2
	str r0, [r5, #0x0]
	str r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02022AA0
FUN_02022AA0: ; 0x02022AA0
	push {r3-r6}
	mov r4, #0xc
	add r5, r3, #0x0
	mul r5, r4
	add r6, r1, r5
	ldr r5, [r6, #0x4]
	ldr r1, _02022AD4 ; =0x00020214
	str r5, [r0, r1]
	ldr r6, [r6, #0x8]
	add r5, r1, #0x4
	str r6, [r0, r5]
	ldr r5, [sp, #0x10]
	mul r4, r5
	add r2, r2, r4
	ldr r4, [r2, #0x8]
	add r2, r1, #0x0
	add r2, #0x8
	str r4, [r0, r2]
	add r2, r1, #0x0
	add r2, #0xc
	strb r3, [r0, r2]
	add r1, #0xd
	strb r5, [r0, r1]
	pop {r3-r6}
	bx lr
	nop
_02022AD4: .word 0x00020214

	thumb_func_start FUN_02022AD8
FUN_02022AD8: ; 0x02022AD8
	push {r3-r6, lr}
	sub sp, #0x44
	mov r1, #0x2
	add r5, r0, #0x0
	mov r0, #0x3
	lsl r1, r1, #0x10
	bl FUN_020169D8
	mov r1, #0x2
	add r6, r0, #0x0
	mov r0, #0x3
	lsl r1, r1, #0x10
	bl FUN_020169D8
	mov r2, #0x2
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r6, #0x0
	lsl r2, r2, #0x10
	bl FUN_020235EC
	cmp r0, #0x0
	add r0, sp, #0x2c
	beq _02022B20
	add r1, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0x0
	bl FUN_0202293C
	add r0, sp, #0x14
	add r1, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0x1
	bl FUN_0202293C
	b _02022B2A
_02022B20:
	bl FUN_0202288C
	add r0, sp, #0x14
	bl FUN_0202288C
_02022B2A:
	mov r0, #0x1
	lsl r0, r0, #0x12
	add r1, r4, #0x0
	lsr r2, r0, #0x1
	bl FUN_020235EC
	cmp r0, #0x0
	add r0, sp, #0x38
	beq _02022B54
	add r1, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_0202293C
	add r0, sp, #0x20
	add r1, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x1
	bl FUN_0202293C
	b _02022B5E
_02022B54:
	bl FUN_0202288C
	add r0, sp, #0x20
	bl FUN_0202288C
_02022B5E:
	add r0, r6, #0x0
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, sp, #0x2c
	add r1, sp, #0x38
	add r2, sp, #0x10
	add r3, sp, #0x8
	bl FUN_020229F0
	add r4, r0, #0x0
	add r0, sp, #0x14
	add r1, sp, #0x20
	add r2, sp, #0xc
	add r3, sp, #0x4
	bl FUN_020229F0
	cmp r4, #0x0
	bne _02022B92
	cmp r0, #0x0
	bne _02022B92
	add sp, #0x44
	mov r0, #0x0
	pop {r3-r6, pc}
_02022B92:
	cmp r4, #0x0
	beq _02022B9A
	cmp r0, #0x0
	bne _02022BA0
_02022B9A:
	add sp, #0x44
	mov r0, #0x3
	pop {r3-r6, pc}
_02022BA0:
	cmp r4, #0x2
	bne _02022BE4
	cmp r0, #0x2
	bne _02022BE4
	ldr r3, [sp, #0x10]
	ldr r1, [sp, #0xc]
	mov r2, #0xc
	add r4, r3, #0x0
	mul r4, r2
	add r0, sp, #0x30
	ldr r0, [r0, r4]
	add r4, r1, #0x0
	mul r4, r2
	add r2, sp, #0x18
	ldr r2, [r2, r4]
	cmp r0, r2
	str r1, [sp, #0x0]
	add r1, sp, #0x2c
	bne _02022BD4
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x1
	pop {r3-r6, pc}
_02022BD4:
	ldr r3, [sp, #0x8]
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x2
	pop {r3-r6, pc}
_02022BE4:
	cmp r4, #0x1
	bne _02022C3A
	cmp r0, #0x2
	bne _02022C3A
	ldr r3, [sp, #0x10]
	ldr r0, [sp, #0xc]
	mov r4, #0xc
	add r2, r3, #0x0
	add r6, r0, #0x0
	mul r2, r4
	add r1, sp, #0x30
	ldr r2, [r1, r2]
	mul r6, r4
	add r1, sp, #0x18
	ldr r6, [r1, r6]
	cmp r2, r6
	bne _02022C18
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, sp, #0x2c
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x2
	pop {r3-r6, pc}
_02022C18:
	ldr r0, [sp, #0x4]
	mul r4, r0
	ldr r1, [r1, r4]
	cmp r2, r1
	bne _02022C34
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, sp, #0x2c
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x2
	pop {r3-r6, pc}
_02022C34:
	add sp, #0x44
	mov r0, #0x3
	pop {r3-r6, pc}
_02022C3A:
	cmp r4, #0x2
	bne _02022C7E
	cmp r0, #0x1
	bne _02022C7E
	ldr r3, [sp, #0x10]
	ldr r1, [sp, #0xc]
	mov r2, #0xc
	add r4, r3, #0x0
	mul r4, r2
	add r0, sp, #0x30
	ldr r0, [r0, r4]
	add r4, r1, #0x0
	mul r4, r2
	add r2, sp, #0x18
	ldr r2, [r2, r4]
	cmp r0, r2
	str r1, [sp, #0x0]
	add r1, sp, #0x2c
	bne _02022C6E
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x1
	pop {r3-r6, pc}
_02022C6E:
	ldr r3, [sp, #0x8]
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x2
	pop {r3-r6, pc}
_02022C7E:
	cmp r4, #0x1
	bne _02022CBC
	cmp r0, #0x1
	bne _02022CBC
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x10]
	cmp r2, r0
	bne _02022CBC
	add r3, r2, #0x0
	mov r1, #0xc
	mul r3, r1
	add r2, sp, #0x30
	mul r1, r0
	add r0, sp, #0x18
	ldr r2, [r2, r3]
	ldr r0, [r0, r1]
	cmp r2, r0
	beq _02022CA6
	bl ErrorHandling
_02022CA6:
	ldr r0, [sp, #0xc]
	add r1, sp, #0x2c
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x10]
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x1
	pop {r3-r6, pc}
_02022CBC:
	ldr r1, [sp, #0x10]
	mov r0, #0xc
	add r2, r1, #0x0
	mul r2, r0
	add r1, sp, #0x30
	ldr r3, [r1, r2]
	ldr r1, [sp, #0xc]
	add r2, r1, #0x0
	mul r2, r0
	add r0, sp, #0x18
	ldr r0, [r0, r2]
	cmp r3, r0
	beq _02022CDA
	bl ErrorHandling
_02022CDA:
	ldr r0, [sp, #0xc]
	add r1, sp, #0x2c
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x10]
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	mov r0, #0x2
	add sp, #0x44
	pop {r3-r6, pc}

	thumb_func_start FUN_02022CF0
FUN_02022CF0: ; 0x02022CF0
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_020228A4
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	add r1, r4, r1
	bl FUN_020235EC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02022D08
FUN_02022D08: ; 0x02022D08
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _02022D4C ; =0x00020464
	mov r7, #0x85
	mov r4, #0x0
	add r6, r5, r0
	lsl r7, r7, #0x2
_02022D16:
	ldr r0, _02022D50 ; =0x00020220
	add r1, r5, r4
	ldrb r0, [r1, r0]
	add r1, r6, #0x0
	add r2, r5, r7
	bl FUN_02022CF0
	cmp r0, #0x0
	bne _02022D2C
	mov r0, #0x0
	pop {r3-r7, pc}
_02022D2C:
	add r0, r5, #0x0
	add r1, r5, r7
	add r2, r4, #0x0
	bl FUN_020228E0
	cmp r0, #0x0
	bne _02022D3E
	mov r0, #0x0
	pop {r3-r7, pc}
_02022D3E:
	add r4, r4, #0x1
	add r6, #0xc
	cmp r4, #0x2
	blt _02022D16
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_02022D4C: .word 0x00020464
_02022D50: .word 0x00020220

	thumb_func_start FUN_02022D54
FUN_02022D54: ; 0x02022D54
	push {r4-r6, lr}
	add r3, r1, #0x0
	ldr r1, _02022D90 ; =0x00020464
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r2, r5, r1
	mov r1, #0xc
	mul r1, r3
	add r4, r2, r1
	mov r1, #0x85
	lsl r1, r1, #0x2
	add r1, r5, r1
	add r2, r3, #0x0
	bl FUN_02022968
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_020228A4
	mov r1, #0x85
	lsl r1, r1, #0x2
	add r2, r5, r1
	ldr r1, [r4, #0x4]
	add r1, r2, r1
	ldr r2, [r4, #0x8]
	sub r2, #0x14
	bl FUN_02023668
	pop {r4-r6, pc}
	nop
_02022D90: .word 0x00020464

	thumb_func_start FUN_02022D94
FUN_02022D94: ; 0x02022D94
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldr r0, _02022DC4 ; =0x00020464
	add r3, r6, r0
	mov r0, #0xc
	mul r0, r1
	add r4, r3, r0
	add r0, r2, #0x0
	add r1, r4, #0x0
	ldr r5, [r4, #0x8]
	bl FUN_020228A4
	mov r1, #0x2
	lsl r1, r1, #0x8
	add r2, r6, r1
	ldr r1, [r4, #0x4]
	add r0, r5, r0
	add r1, r2, r1
	sub r0, #0x14
	add r1, r1, r5
	mov r2, #0x14
	bl FUN_02023668
	pop {r4-r6, pc}
	.balign 4
_02022DC4: .word 0x00020464

	thumb_func_start FUN_02022DC8
FUN_02022DC8: ; 0x02022DC8
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldr r0, _02022DF8 ; =0x00020464
	add r3, r6, r0
	mov r0, #0xc
	mul r0, r1
	add r4, r3, r0
	add r0, r2, #0x0
	add r1, r4, #0x0
	ldr r5, [r4, #0x8]
	bl FUN_020228A4
	mov r1, #0x82
	lsl r1, r1, #0x2
	add r2, r6, r1
	ldr r1, [r4, #0x4]
	add r0, r5, r0
	add r1, r2, r1
	sub r0, #0xc
	add r1, r1, r5
	mov r2, #0x8
	bl FUN_02023668
	pop {r4-r6, pc}
	.balign 4
_02022DF8: .word 0x00020464

	thumb_func_start FUN_02022DFC
FUN_02022DFC: ; 0x02022DFC
	push {r3-r7, lr}
	ldr r7, _02022E70 ; =0x00020218
	add r4, r1, #0x0
	mov r12, r2
	mov r1, #0x0
	add r2, r0, #0x0
	add r3, r4, #0x0
	add r6, r7, #0x0
_02022E0C:
	ldr r5, _02022E70 ; =0x00020218
	add r1, r1, #0x1
	ldr r5, [r2, r5]
	str r5, [r3, #0x1c]
	ldr r5, [r2, r7]
	add r3, r3, #0x4
	add r5, r5, #0x1
	str r5, [r2, r6]
	add r2, r2, #0x4
	cmp r1, #0x2
	blt _02022E0C
	mov r1, #0x0
	str r1, [r4, #0x14]
	mov r2, r12
	str r1, [r4, #0x0]
	cmp r2, #0x2
	bne _02022E58
	ldr r2, [r0, #0xc]
	cmp r2, #0x0
	beq _02022E4E
	mov r2, #0x1
	str r2, [r4, #0x0]
	ldr r2, _02022E74 ; =0x00020214
	ldr r3, [r0, r2]
	str r3, [r4, #0x18]
	ldr r3, [r0, r2]
	add r3, r3, #0x1
	str r3, [r0, r2]
	str r1, [r4, #0x4]
	str r1, [r4, #0x8]
	mov r0, #0x2
	str r0, [r4, #0xc]
	b _02022E66
_02022E4E:
	str r1, [r4, #0x4]
	str r1, [r4, #0x8]
	mov r0, #0x1
	str r0, [r4, #0xc]
	b _02022E66
_02022E58:
	mov r0, r12
	str r0, [r4, #0x4]
	mov r0, r12
	str r0, [r4, #0x8]
	mov r0, r12
	add r0, r0, #0x1
	str r0, [r4, #0xc]
_02022E66:
	mov r0, #0x1
	bl FUN_02016444
	pop {r3-r7, pc}
	nop
_02022E70: .word 0x00020218
_02022E74: .word 0x00020214

	thumb_func_start FUN_02022E78
FUN_02022E78: ; 0x02022E78
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x14]
	cmp r0, #0x5
	bhi _02022F78
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02022E90: ; jump table (using 16-bit offset)
	.short _02022E9C - _02022E90 - 2; case 0
	.short _02022EC0 - _02022E90 - 2; case 1
	.short _02022EDC - _02022E90 - 2; case 2
	.short _02022F00 - _02022E90 - 2; case 3
	.short _02022F2A - _02022E90 - 2; case 4
	.short _02022F4E - _02022E90 - 2; case 5
_02022E9C:
	ldr r1, [r4, #0x8]
	ldr r0, _02022F7C ; =0x00020220
	add r2, r5, r1
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	bne _02022EAC
	mov r2, #0x1
	b _02022EAE
_02022EAC:
	mov r2, #0x0
_02022EAE:
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02022D54
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
_02022EC0:
	ldr r0, [r4, #0x10]
	add r1, sp, #0x0
	bl FUN_020236E4
	cmp r0, #0x0
	beq _02022F78
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02022ED6
	mov r0, #0x3
	pop {r3-r5, pc}
_02022ED6:
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
_02022EDC:
	ldr r1, [r4, #0x8]
	ldr r0, _02022F7C ; =0x00020220
	add r2, r5, r1
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	bne _02022EEC
	mov r2, #0x1
	b _02022EEE
_02022EEC:
	mov r2, #0x0
_02022EEE:
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02022DC8
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
_02022F00:
	ldr r0, [r4, #0x10]
	add r1, sp, #0x0
	bl FUN_020236E4
	cmp r0, #0x0
	beq _02022F78
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02022F16
	mov r0, #0x3
	pop {r3-r5, pc}
_02022F16:
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x8]
	add r1, r0, #0x1
	ldr r0, [r4, #0xc]
	cmp r1, r0
	bne _02022F2A
	mov r0, #0x1
	pop {r3-r5, pc}
_02022F2A:
	ldr r1, [r4, #0x8]
	ldr r0, _02022F7C ; =0x00020220
	add r2, r5, r1
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	bne _02022F3A
	mov r2, #0x1
	b _02022F3C
_02022F3A:
	mov r2, #0x0
_02022F3C:
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02022D94
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
_02022F4E:
	ldr r0, [r4, #0x10]
	add r1, sp, #0x0
	bl FUN_020236E4
	cmp r0, #0x0
	beq _02022F78
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02022F64
	mov r0, #0x3
	pop {r3-r5, pc}
_02022F64:
	ldr r0, [r4, #0x8]
	add r1, r0, #0x1
	str r1, [r4, #0x8]
	ldr r0, [r4, #0xc]
	cmp r1, r0
	bne _02022F74
	mov r0, #0x2
	pop {r3-r5, pc}
_02022F74:
	mov r0, #0x0
	str r0, [r4, #0x14]
_02022F78:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02022F7C: .word 0x00020220

	thumb_func_start FUN_02022F80
FUN_02022F80: ; 0x02022F80
	push {r3-r7, lr}
	add r3, r0, #0x0
	add r0, r1, #0x0
	cmp r2, #0x3
	bne _02022FAA
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02022F96
	ldr r2, [r0, #0x18]
	ldr r1, _02022FE4 ; =0x00020214
	str r2, [r3, r1]
_02022F96:
	ldr r1, _02022FE8 ; =0x00020218
	mov r4, #0x0
_02022F9A:
	ldr r2, [r0, #0x1c]
	add r4, r4, #0x1
	str r2, [r3, r1]
	add r0, r0, #0x4
	add r3, r3, #0x4
	cmp r4, #0x2
	blt _02022F9A
	b _02022FDA
_02022FAA:
	ldr r6, [r0, #0x4]
	ldr r1, [r0, #0xc]
	cmp r6, r1
	bge _02022FD0
	ldr r1, _02022FEC ; =0x00020220
	mov r7, #0x1
	add r2, r1, #0x0
_02022FB8:
	add r5, r3, r6
	ldrb r4, [r5, r2]
	cmp r4, #0x0
	bne _02022FC4
	add r4, r7, #0x0
	b _02022FC6
_02022FC4:
	mov r4, #0x0
_02022FC6:
	strb r4, [r5, r1]
	ldr r4, [r0, #0xc]
	add r6, r6, #0x1
	cmp r6, r4
	blt _02022FB8
_02022FD0:
	mov r0, #0x1
	str r0, [r3, #0x4]
	mov r0, #0x0
	str r0, [r3, #0x8]
	str r0, [r3, #0xc]
_02022FDA:
	mov r0, #0x1
	bl FUN_02016454
	pop {r3-r7, pc}
	nop
_02022FE4: .word 0x00020214
_02022FE8: .word 0x00020218
_02022FEC: .word 0x00020220

	thumb_func_start FUN_02022FF0
FUN_02022FF0: ; 0x02022FF0
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02023000
	ldr r2, [r4, #0x18]
	ldr r1, _0202303C ; =0x00020214
	str r2, [r0, r1]
_02023000:
	ldr r1, _02023040 ; =0x00020218
	mov r3, #0x0
	add r5, r4, #0x0
_02023006:
	ldr r2, [r5, #0x1c]
	add r3, r3, #0x1
	str r2, [r0, r1]
	add r5, r5, #0x4
	add r0, r0, #0x4
	cmp r3, #0x2
	blt _02023006
	bl CARD_TryWaitBackupAsync
	cmp r0, #0x0
	bne _02023034
	bl CARD_CancelBackupAsync
	ldr r0, [r4, #0x10]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl CARD_UnlockBackup
	ldr r0, [r4, #0x10]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl OS_ReleaseLockID
_02023034:
	mov r0, #0x1
	bl FUN_02016454
	pop {r3-r5, pc}
	.balign 4
_0202303C: .word 0x00020214
_02023040: .word 0x00020218

	thumb_func_start FUN_02023044
FUN_02023044: ; 0x02023044
	push {r3-r6, lr}
	sub sp, #0x24
	add r1, sp, #0x0
	mov r2, #0x2
	add r5, r0, #0x0
	bl FUN_02022DFC
	add r6, sp, #0x0
_02023054:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02022E78
	add r4, r0, #0x0
	beq _02023054
	cmp r4, #0x1
	beq _02023054
	add r0, r5, #0x0
	add r1, sp, #0x0
	add r2, r4, #0x0
	bl FUN_02022F80
	add r0, r4, #0x0
	add sp, #0x24
	pop {r3-r6, pc}

	thumb_func_start FUN_02023074
FUN_02023074: ; 0x02023074
	push {r4-r5, lr}
	sub sp, #0x14
	add r4, r2, #0x0
	ldr r2, _020230A8 ; =0x00020464
	add r2, r0, r2
	mov r0, #0xc
	mul r0, r1
	add r5, r2, r0
	add r0, sp, #0x0
	mov r1, #0xff
	mov r2, #0x14
	bl MI_CpuFill8
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020228A4
	ldr r1, [r5, #0x8]
	mov r2, #0x14
	add r0, r1, r0
	sub r0, #0x14
	add r1, sp, #0x0
	bl FUN_020235D0
	add sp, #0x14
	pop {r4-r5, pc}
	.balign 4
_020230A8: .word 0x00020464

	thumb_func_start FUN_020230AC
FUN_020230AC: ; 0x020230AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _020230DC ; =0x020EE6DC
	ldr r4, _020230E0 ; =0x020EE700
	ldr r0, [r0, #0x0]
	cmp r5, r0
	blt _020230BE
	bl ErrorHandling
_020230BE:
	lsl r0, r5, #0x4
	add r0, r4, r0
	ldr r0, [r0, #0x8]
	blx r0
	lsr r3, r0, #0x1f
	lsl r2, r0, #0x1e
	sub r2, r2, r3
	mov r1, #0x1e
	ror r2, r1
	add r2, r3, r2
	mov r1, #0x4
	sub r1, r1, r2
	add r0, r0, r1
	pop {r3-r5, pc}
	nop
_020230DC: .word 0x020EE6DC
_020230E0: .word 0x020EE700

	thumb_func_start FUN_020230E4
FUN_020230E4: ; 0x020230E4
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, _02023158 ; =0x020EE6DC
	ldr r4, _0202315C ; =0x020EE700
	ldr r0, [r0, #0x0]
	mov r7, #0x0
	str r0, [sp, #0x0]
	cmp r0, #0x24
	beq _020230FC
	bl ErrorHandling
_020230FC:
	ldr r0, [sp, #0x0]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02023148
	sub r0, r0, #0x1
	str r0, [sp, #0x4]
_02023108:
	ldr r0, [r4, #0x0]
	cmp r6, r0
	beq _02023112
	bl ErrorHandling
_02023112:
	ldr r0, [r4, #0x0]
	str r0, [r5, #0x0]
	add r0, r6, #0x0
	bl FUN_020230AC
	str r0, [r5, #0x4]
	str r7, [r5, #0x8]
	mov r0, #0x0
	strh r0, [r5, #0xc]
	ldr r0, [r4, #0x4]
	strh r0, [r5, #0xe]
	ldr r0, [r5, #0x4]
	add r7, r7, r0
	ldr r0, [sp, #0x4]
	cmp r6, r0
	beq _0202313A
	ldr r1, [r4, #0x4]
	ldr r0, [r4, #0x14]
	cmp r1, r0
	beq _0202313C
_0202313A:
	add r7, #0x14
_0202313C:
	ldr r0, [sp, #0x0]
	add r6, r6, #0x1
	add r4, #0x10
	add r5, #0x10
	cmp r6, r0
	blt _02023108
_02023148:
	mov r0, #0x2
	lsl r0, r0, #0x10
	cmp r7, r0
	ble _02023154
	bl ErrorHandling
_02023154:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02023158: .word 0x020EE6DC
_0202315C: .word 0x020EE700

	thumb_func_start FUN_02023160
FUN_02023160: ; 0x02023160
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	mov r12, r0
	add r3, r0, #0x0
	add r6, r0, #0x0
	ldr r0, _020231EC ; =0x020EE6DC
	ldr r4, [sp, #0x0]
	ldr r7, [r0, #0x0]
	add r5, r1, #0x0
_02023178:
	add r2, r4, #0x0
	strb r6, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x8]
	add r2, #0x8
	b _02023190
_02023184:
	ldr r0, [r5, #0x4]
	ldr r1, [r2, #0x0]
	add r5, #0x10
	add r0, r1, r0
	str r0, [r2, #0x0]
	add r3, r3, #0x1
_02023190:
	ldrh r0, [r5, #0xe]
	cmp r6, r0
	bne _0202319A
	cmp r3, r7
	blt _02023184
_0202319A:
	ldr r0, [r4, #0x8]
	add r6, r6, #0x1
	add r0, #0x14
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x4]
	strb r0, [r4, #0x1]
	mov r0, r12
	str r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	ldr r0, _020231F0 ; =0x00000FFF
	add r0, r1, r0
	lsr r0, r0, #0xc
	strb r0, [r4, #0x2]
	ldrb r1, [r4, #0x2]
	ldr r0, [sp, #0x4]
	add r0, r0, r1
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x8]
	mov r1, r12
	add r0, r1, r0
	add r4, #0xc
	mov r12, r0
	cmp r6, #0x2
	blt _02023178
	ldr r0, [sp, #0x0]
	ldrb r1, [r0, #0xd]
	ldrb r0, [r0, #0xe]
	add r1, r1, r0
	ldr r0, [sp, #0x4]
	cmp r0, r1
	beq _020231DC
	bl ErrorHandling
_020231DC:
	ldr r0, [sp, #0x4]
	cmp r0, #0x20
	ble _020231E6
	bl ErrorHandling
_020231E6:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_020231EC: .word 0x020EE6DC
_020231F0: .word 0x00000FFF

	thumb_func_start FUN_020231F4
FUN_020231F4: ; 0x020231F4
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r0, #0x0
	mov r2, #0x2
	add r5, r1, #0x0
	mov r0, #0x0
	add r1, r6, #0x0
	lsl r2, r2, #0x10
	ldr r4, _02023240 ; =0x020EE700
	bl MIi_CpuClearFast
	ldr r0, _02023244 ; =0x020EE6DC
	mov r7, #0x0
	ldr r0, [r0, #0x0]
	str r0, [sp, #0x0]
	cmp r0, #0x0
	ble _0202323A
_02023216:
	ldr r0, [r5, #0x8]
	ldr r2, [r5, #0x4]
	str r0, [sp, #0x4]
	ldr r1, [sp, #0x4]
	mov r0, #0x0
	add r1, r6, r1
	bl MIi_CpuClearFast
	ldr r0, [sp, #0x4]
	ldr r1, [r4, #0xc]
	add r0, r6, r0
	blx r1
	ldr r0, [sp, #0x0]
	add r7, r7, #0x1
	add r5, #0x10
	add r4, #0x10
	cmp r7, r0
	blt _02023216
_0202323A:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02023240: .word 0x020EE700
_02023244: .word 0x020EE6DC

	thumb_func_start FUN_02023248
FUN_02023248: ; 0x02023248
	push {r3-r5, lr}
	ldr r5, _0202326C ; =0x20060623
	add r4, r1, r3
	str r5, [r1, r3]
	ldr r5, _02023270 ; =0x000204A4
	ldr r5, [r0, r5]
	add r0, #0x14
	add r5, r5, #0x1
	str r5, [r4, #0x4]
	str r3, [r4, #0x8]
	add r3, #0xe
	strh r2, [r4, #0xc]
	add r2, r3, #0x0
	bl MATH_CalcCRC16CCITT
	strh r0, [r4, #0xe]
	pop {r3-r5, pc}
	nop
_0202326C: .word 0x20060623
_02023270: .word 0x000204A4

	thumb_func_start FUN_02023274
FUN_02023274: ; 0x02023274
	push {r4-r6, lr}
	ldr r6, [r1, r3]
	ldr r5, _020232B0 ; =0x20060623
	add r4, r1, r3
	cmp r6, r5
	beq _02023284
	mov r0, #0x0
	pop {r4-r6, pc}
_02023284:
	ldr r5, [r4, #0x8]
	cmp r5, r3
	beq _0202328E
	mov r0, #0x0
	pop {r4-r6, pc}
_0202328E:
	ldrh r5, [r4, #0xc]
	cmp r5, r2
	beq _02023298
	mov r0, #0x0
	pop {r4-r6, pc}
_02023298:
	add r3, #0xe
	add r0, #0x14
	add r2, r3, #0x0
	bl MATH_CalcCRC16CCITT
	ldrh r1, [r4, #0xe]
	cmp r1, r0
	bne _020232AC
	mov r0, #0x1
	pop {r4-r6, pc}
_020232AC:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_020232B0: .word 0x20060623

	thumb_func_start FUN_020232B4
FUN_020232B4: ; 0x020232B4
	add r0, r0, r1
	ldr r0, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start FUN_020232BC
FUN_020232BC: ; 0x020232BC
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	mov r0, #0x1
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02016444
	ldr r0, _020233FC ; =0x020EE6D8
	ldr r0, [r0, #0x0]
	cmp r5, r0
	blt _020232D8
	bl ErrorHandling
_020232D8:
	ldr r1, _02023400 ; =0x020EE6E0
	lsl r0, r5, #0x4
	add r4, r1, r0
	ldr r0, [r1, r0]
	cmp r0, r5
	beq _020232E8
	bl ErrorHandling
_020232E8:
	ldr r0, [r4, #0x8]
	blx r0
	str r0, [sp, #0x4]
	add r0, #0x10
	str r0, [sp, #0x4]
	ldr r0, _02023404 ; =0x000204A0
	ldr r0, [r7, r0]
	cmp r0, #0x1
	ldr r0, [r4, #0x8]
	bne _0202336E
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023248
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x4]
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235D0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023274
	cmp r0, #0x1
	beq _02023330
	bl ErrorHandling
_02023330:
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023248
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x4]
	add r0, #0x40
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235D0
	ldr r1, [sp, #0x0]
	orr r0, r1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023274
	cmp r0, #0x1
	beq _020233DE
	bl ErrorHandling
	b _020233DE
_0202336E:
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023248
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x4]
	add r0, #0x40
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235D0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023274
	cmp r0, #0x1
	beq _020233A4
	bl ErrorHandling
_020233A4:
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023248
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x4]
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235D0
	ldr r1, [sp, #0x0]
	orr r0, r1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023274
	cmp r0, #0x1
	beq _020233DE
	bl ErrorHandling
_020233DE:
	ldr r0, [sp, #0x0]
	cmp r0, #0x1
	bne _020233F0
	mov r0, #0x1
	bl FUN_02016454
	add sp, #0x8
	mov r0, #0x2
	pop {r3-r7, pc}
_020233F0:
	mov r0, #0x1
	bl FUN_02016454
	mov r0, #0x3
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020233FC: .word 0x020EE6D8
_02023400: .word 0x020EE6E0
_02023404: .word 0x000204A0

	thumb_func_start FUN_02023408
FUN_02023408: ; 0x02023408
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	ldr r0, _02023564 ; =0x020EE6D8
	add r7, r2, #0x0
	ldr r0, [r0, #0x0]
	add r6, r1, #0x0
	str r3, [sp, #0x0]
	cmp r7, r0
	blt _02023420
	bl ErrorHandling
_02023420:
	ldr r1, _02023568 ; =0x020EE6E0
	lsl r0, r7, #0x4
	add r4, r1, r0
	ldr r0, [r1, r0]
	cmp r0, r7
	beq _02023430
	bl ErrorHandling
_02023430:
	ldr r0, [r4, #0x8]
	blx r0
	str r0, [sp, #0x10]
	add r0, #0x10
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x10]
	add r0, r6, #0x0
	bl FUN_02016998
	add r6, r0, #0x0
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x10]
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235EC
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02023274
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x8]
	blx r0
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020232B4
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x10]
	add r0, #0x40
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235EC
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02023274
	add r7, r0, #0x0
	ldr r0, [r4, #0x8]
	blx r0
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020232B4
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [r0, #0x0]
	ldr r0, [sp, #0xc]
	cmp r0, #0x1
	bne _020234CC
	cmp r7, #0x0
	bne _020234CC
	ldr r0, _0202356C ; =0x000204A0
	mov r1, #0x0
	str r1, [r5, r0]
	add r1, r0, #0x4
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x10]
	str r0, [r5, r1]
	ldr r0, [r4, #0x4]
	add r1, r6, #0x0
	lsl r0, r0, #0xc
	bl FUN_020235EC
	add sp, #0x14
	add r0, r6, #0x0
	pop {r4-r7, pc}
_020234CC:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _020234F6
	cmp r7, #0x1
	bne _020234F6
	ldr r0, _0202356C ; =0x000204A0
	mov r1, #0x1
	str r1, [r5, r0]
	add r1, r0, #0x4
	ldr r0, [sp, #0x4]
	ldr r2, [sp, #0x10]
	str r0, [r5, r1]
	ldr r0, [r4, #0x4]
	add r1, r6, #0x0
	add r0, #0x40
	lsl r0, r0, #0xc
	bl FUN_020235EC
	add sp, #0x14
	add r0, r6, #0x0
	pop {r4-r7, pc}
_020234F6:
	ldr r0, [sp, #0xc]
	cmp r0, #0x1
	bne _0202354C
	cmp r7, #0x1
	bne _0202354C
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	bl FUN_020229B8
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	ldr r0, _0202356C ; =0x000204A0
	beq _0202352E
	mov r1, #0x0
	str r1, [r5, r0]
	add r1, r0, #0x4
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x10]
	str r0, [r5, r1]
	ldr r0, [r4, #0x4]
	add r1, r6, #0x0
	lsl r0, r0, #0xc
	bl FUN_020235EC
	add sp, #0x14
	add r0, r6, #0x0
	pop {r4-r7, pc}
_0202352E:
	mov r1, #0x1
	str r1, [r5, r0]
	add r1, r0, #0x4
	ldr r0, [sp, #0x4]
	ldr r2, [sp, #0x10]
	str r0, [r5, r1]
	ldr r0, [r4, #0x4]
	add r1, r6, #0x0
	add r0, #0x40
	lsl r0, r0, #0xc
	bl FUN_020235EC
	add sp, #0x14
	add r0, r6, #0x0
	pop {r4-r7, pc}
_0202354C:
	ldr r0, [sp, #0x0]
	mov r1, #0x2
	str r1, [r0, #0x0]
	ldr r0, _0202356C ; =0x000204A0
	mov r1, #0x0
	str r1, [r5, r0]
	add r0, r0, #0x4
	str r1, [r5, r0]
	add r0, r6, #0x0
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02023564: .word 0x020EE6D8
_02023568: .word 0x020EE6E0
_0202356C: .word 0x000204A0

	thumb_func_start FUN_02023570
FUN_02023570: ; 0x02023570
	push {r3-r5, lr}
	bl OS_GetLockID
	add r4, r0, #0x0
	mov r0, #0x2
	mvn r0, r0
	cmp r4, r0
	bne _02023584
	bl ErrorHandling
_02023584:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl CARD_LockBackup
	ldr r0, _020235C8 ; =0x00001302
	bl CARD_IdentifyBackup
	cmp r0, #0x0
	beq _0202359A
	ldr r5, _020235C8 ; =0x00001302
	b _020235AA
_0202359A:
	ldr r0, _020235CC ; =0x00001202
	bl CARD_IdentifyBackup
	cmp r0, #0x0
	beq _020235A8
	ldr r5, _020235CC ; =0x00001202
	b _020235AA
_020235A8:
	mov r5, #0x0
_020235AA:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl CARD_UnlockBackup
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl OS_ReleaseLockID
	cmp r5, #0x0
	beq _020235C2
	mov r0, #0x1
	pop {r3-r5, pc}
_020235C2:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_020235C8: .word 0x00001302
_020235CC: .word 0x00001202

	thumb_func_start FUN_020235D0
FUN_020235D0: ; 0x020235D0
	push {r3-r5, lr}
	bl FUN_02023668
	add r5, r0, #0x0
	add r4, sp, #0x0
_020235DA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020236E4
	cmp r0, #0x0
	beq _020235DA
	ldr r0, [sp, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020235EC
FUN_020235EC: ; 0x020235EC
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl OS_GetLockID
	add r4, r0, #0x0
	mov r0, #0x2
	mvn r0, r0
	cmp r4, r0
	bne _02023608
	bl ErrorHandling
_02023608:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl CARD_LockBackup
	mov r3, #0x0
	str r3, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r0, #0x6
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	str r3, [sp, #0x10]
	bl CARDi_RequestStreamCommand
	bl CARD_WaitBackupAsync
	add r5, r0, #0x0
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl CARD_UnlockBackup
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl OS_ReleaseLockID
	cmp r5, #0x0
	bne _02023652
	ldr r0, _02023658 ; =0x021C59C8
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	mov r0, #0x1
	bl FUN_02089D90
_02023652:
	add r0, r5, #0x0
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02023658: .word 0x021C59C8

	thumb_func_start FUN_0202365C
FUN_0202365C: ; 0x0202365C
	ldr r0, _02023664 ; =0x021C59C8
	mov r1, #0x1
	str r1, [r0, #0x4]
	bx lr
	.balign 4
_02023664: .word 0x021C59C8

	thumb_func_start FUN_02023668
FUN_02023668: ; 0x02023668
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl OS_GetLockID
	add r4, r0, #0x0
	mov r0, #0x2
	mvn r0, r0
	cmp r4, r0
	bne _02023684
	bl ErrorHandling
_02023684:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl CARD_LockBackup
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r1, #0x6
	str r1, [sp, #0x8]
	mov r1, #0x1
	str r1, [sp, #0xc]
	add r1, sp, #0x14
	mov r2, #0x4
	add r3, r0, #0x0
	str r0, [sp, #0x10]
	bl CARDi_RequestStreamCommand
	cmp r0, #0x0
	bne _020236B2
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02023740
_020236B2:
	ldr r0, _020236DC ; =0x021C59C8
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x7
	str r0, [sp, #0x8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	mov r0, #0x2
	str r0, [sp, #0x10]
	ldr r3, _020236E0 ; =FUN_0202365C
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl CARDi_RequestStreamCommand
	add r0, r4, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_020236DC: .word 0x021C59C8
_020236E0: .word FUN_0202365C

	thumb_func_start FUN_020236E4
FUN_020236E4: ; 0x020236E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0202373C ; =0x021C59C8
	add r4, r1, #0x0
	ldr r0, [r0, #0x4]
	cmp r0, #0x1
	bne _02023738
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl CARD_UnlockBackup
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl OS_ReleaseLockID
	bl CARD_GetResultCode
	cmp r0, #0x0
	beq _02023714
	cmp r0, #0x4
	beq _0202371E
	cmp r0, #0x6
	beq _02023728
	b _0202371A
_02023714:
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _02023734
_0202371A:
	bl ErrorHandling
_0202371E:
	mov r1, #0x0
	add r0, r5, #0x0
	str r1, [r4, #0x0]
	bl FUN_02023740
_02023728:
	mov r0, #0x0
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02023740
_02023734:
	mov r0, #0x1
	pop {r3-r5, pc}
_02023738:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0202373C: .word 0x021C59C8

	thumb_func_start FUN_02023740
FUN_02023740: ; 0x02023740
	push {r3-r5, lr}
	add r5, r0, #0x0
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	add r4, r1, #0x0
	bl CARD_UnlockBackup
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl OS_ReleaseLockID
	ldr r0, _02023768 ; =0x021C59C8
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	mov r0, #0x1
	add r1, r4, #0x0
	bl FUN_0208A0B8
	pop {r3-r5, pc}
	.balign 4
_02023768: .word 0x021C59C8

	thumb_func_start FUN_0202376C
FUN_0202376C: ; 0x0202376C
	mov r0, #0x5c
	bx lr

	thumb_func_start FUN_02023770
FUN_02023770: ; 0x02023770
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x5c
	bl MIi_CpuClearFast
	add r4, #0x10
	add r0, r4, #0x0
	bl FUN_02023840
	pop {r4, pc}

	thumb_func_start FUN_02023788
FUN_02023788: ; 0x02023788
	ldr r3, _02023790 ; =FUN_02022610
	mov r1, #0x0
	bx r3
	nop
_02023790: .word FUN_02022610

	thumb_func_start FUN_02023794
FUN_02023794: ; 0x02023794
	push {r3, lr}
	bl FUN_02023788
	add r0, #0x10
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020237A0
FUN_020237A0: ; 0x020237A0
	push {r4, lr}
	sub sp, #0x50
	add r4, r0, #0x0
	bl OS_GetOwnerRtcOffset
	str r0, [r4, #0x0]
	add r0, r4, #0x0
	add r0, #0x8
	str r1, [r4, #0x4]
	bl OS_GetMacAddress
	add r0, sp, #0x0
	bl OS_GetOwnerInfo
	add r0, sp, #0x0
	ldrb r1, [r0, #0x2]
	strb r1, [r4, #0xe]
	ldrb r0, [r0, #0x3]
	strb r0, [r4, #0xf]
	add sp, #0x50
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020237CC
FUN_020237CC: ; 0x020237CC
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl OS_GetMacAddress
	mov r2, #0x0
	add r3, sp, #0x0
_020237DC:
	add r0, r4, r2
	ldrb r1, [r3, #0x0]
	ldrb r0, [r0, #0x8]
	cmp r1, r0
	beq _020237EC
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_020237EC:
	add r2, r2, #0x1
	add r3, r3, #0x1
	cmp r2, #0x6
	blt _020237DC
	mov r0, #0x1
	add sp, #0x8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020237FC
FUN_020237FC: ; 0x020237FC
	push {r4, lr}
	add r4, r0, #0x0
	bl OS_GetOwnerRtcOffset
	ldr r3, [r4, #0x0]
	ldr r2, [r4, #0x4]
	eor r0, r3
	eor r1, r2
	orr r0, r1
	bne _02023814
	mov r0, #0x1
	pop {r4, pc}
_02023814:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02023818
FUN_02023818: ; 0x02023818
	ldrb r0, [r0, #0xe]
	bx lr

	thumb_func_start FUN_0202381C
FUN_0202381C: ; 0x0202381C
	ldrb r0, [r0, #0xf]
	bx lr

	thumb_func_start FUN_02023820
FUN_02023820: ; 0x02023820
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023828
FUN_02023828: ; 0x02023828
	add r0, #0x48
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023830
FUN_02023830: ; 0x02023830
	ldr r0, [r0, #0x4c]
	bx lr

	thumb_func_start FUN_02023834
FUN_02023834: ; 0x02023834
	ldr r2, [r0, #0x4c]
	cmp r2, #0x0
	bne _0202383C
	str r1, [r0, #0x4c]
_0202383C:
	bx lr
	.balign 4

	thumb_func_start FUN_02023840
FUN_02023840: ; 0x02023840
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1
	add r1, r4, #0x0
	str r0, [r4, #0x0]
	add r0, r4, #0x4
	add r1, #0x14
	bl FUN_0201265C
	add r0, r4, #0x4
	bl RTC_ConvertDateToDay
	add r1, r4, #0x0
	str r0, [r4, #0x20]
	add r0, r4, #0x4
	add r1, #0x14
	bl RTC_ConvertDateTimeToSecond
	str r0, [r4, #0x24]
	str r1, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	str r0, [r4, #0x30]
	str r0, [r4, #0x34]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02023874
FUN_02023874: ; 0x02023874
	ldr r0, [r0, #0x34]
	cmp r0, #0x0
	beq _0202387E
	mov r0, #0x1
	bx lr
_0202387E:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02023884
FUN_02023884: ; 0x02023884
	mov r2, #0x5a
	ldr r3, [r0, #0x34]
	lsl r2, r2, #0x4
	cmp r3, r2
	bls _02023890
	str r2, [r0, #0x34]
_02023890:
	ldr r2, [r0, #0x34]
	cmp r2, r1
	bhs _0202389C
	mov r1, #0x0
	str r1, [r0, #0x34]
	bx lr
_0202389C:
	sub r1, r2, r1
	str r1, [r0, #0x34]
	bx lr
	.balign 4

	thumb_func_start FUN_020238A4
FUN_020238A4: ; 0x020238A4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x5a
	lsl r0, r0, #0x4
	add r1, r4, #0x0
	str r0, [r4, #0x34]
	add r0, r4, #0x4
	add r1, #0x14
	bl FUN_0201265C
	add r0, r4, #0x4
	bl RTC_ConvertDateToDay
	str r0, [r4, #0x20]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020238C4
FUN_020238C4: ; 0x020238C4
	mov r0, #0x2c
	bx lr

	thumb_func_start FUN_020238C8
FUN_020238C8: ; 0x020238C8
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x2c
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	bl FUN_02024F50
	add r0, r4, #0x4
	bl FUN_02023948
	add r0, r4, #0x0
	add r0, #0x24
	bl FUN_02028910
	add r4, #0x26
	add r0, r4, #0x0
	bl FUN_02029E48
	pop {r4, pc}

	thumb_func_start FUN_020238F4
FUN_020238F4: ; 0x020238F4
	push {r3, lr}
	mov r1, #0x1
	bl FUN_02022610
	add r0, r0, #0x4
	pop {r3, pc}

	thumb_func_start LoadPlayerDataAddress
LoadPlayerDataAddress: ; 0x02023900
	ldr r3, _02023908 ; =FUN_02022610
	mov r1, #0x1
	bx r3
	nop
_02023908: .word FUN_02022610

	thumb_func_start FUN_0202390C
FUN_0202390C: ; 0x0202390C
	push {r3, lr}
	mov r1, #0x1
	bl FUN_02022610
	add r0, #0x24
	pop {r3, pc}

	thumb_func_start FUN_02023918
FUN_02023918: ; 0x02023918
	push {r3, lr}
	mov r1, #0x1
	bl FUN_02022610
	add r0, #0x26
	pop {r3, pc}

	thumb_func_start FUN_02023924
FUN_02023924: ; 0x02023924
	mov r0, #0x20
	bx lr

	thumb_func_start FUN_02023928
FUN_02023928: ; 0x02023928
	push {r4, lr}
	mov r1, #0x20
	bl FUN_02016998
	add r4, r0, #0x0
	bl FUN_02023948
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202393C
FUN_0202393C: ; 0x0202393C
	ldr r3, _02023944 ; =MI_CpuCopy8
	mov r2, #0x20
	bx r3
	nop
_02023944: .word MI_CpuCopy8

	thumb_func_start FUN_02023948
FUN_02023948: ; 0x02023948
	push {r4, lr}
	mov r1, #0x0
	mov r2, #0x20
	add r4, r0, #0x0
	bl Call_FillMemWithValue
	mov r0, #0x2
	strb r0, [r4, #0x19]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202395C
FUN_0202395C: ; 0x0202395C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl StringLength
	cmp r0, #0x8
	blt _02023970
	bl ErrorHandling
_02023970:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl StringCopy
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202397C
FUN_0202397C: ; 0x0202397C
	ldr r3, _02023988 ; =FUN_02021EF0
	add r2, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	mov r2, #0x8
	bx r3
	.balign 4
_02023988: .word FUN_02021EF0

	thumb_func_start FUN_0202398C
FUN_0202398C: ; 0x0202398C
	bx lr
	.balign 4

	thumb_func_start FUN_02023990
FUN_02023990: ; 0x02023990
	ldr r3, _0202399C ; =FUN_02021E28
	add r2, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	bx r3
	nop
_0202399C: .word FUN_02021E28

	thumb_func_start FUN_020239A0
FUN_020239A0: ; 0x020239A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x8
	bl FUN_020219F4
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02023990
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_020239B8
FUN_020239B8: ; 0x020239B8
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start FUN_020239BC
FUN_020239BC: ; 0x020239BC
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start FUN_020239C0
FUN_020239C0: ; 0x020239C0
	ldr r0, [r0, #0x10]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr

	thumb_func_start FUN_020239C8
FUN_020239C8: ; 0x020239C8
	strb r1, [r0, #0x18]
	bx lr

	thumb_func_start FUN_020239CC
FUN_020239CC: ; 0x020239CC
	ldrb r0, [r0, #0x18]
	bx lr

	thumb_func_start FUN_020239D0
FUN_020239D0: ; 0x020239D0
	ldrb r3, [r0, #0x1a]
	mov r0, #0x1
	add r2, r0, #0x0
	lsl r2, r1
	add r1, r3, #0x0
	tst r1, r2
	bne _020239E0
	mov r0, #0x0
_020239E0:
	bx lr
	.balign 4

	thumb_func_start FUN_020239E4
FUN_020239E4: ; 0x020239E4
	ldrb r3, [r0, #0x1a]
	mov r2, #0x1
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strb r1, [r0, #0x1a]
	bx lr
	.balign 4

	thumb_func_start FUN_020239F4
FUN_020239F4: ; 0x020239F4
	ldrb r3, [r0, #0x1a]
	mov r2, #0x0
	cmp r3, #0x0
	beq _02023A0A
	mov r0, #0x1
_020239FE:
	add r1, r3, #0x0
	tst r1, r0
	beq _02023A06
	add r2, r2, #0x1
_02023A06:
	lsr r3, r3, #0x1
	bne _020239FE
_02023A0A:
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02023A10
FUN_02023A10: ; 0x02023A10
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start FUN_02023A14
FUN_02023A14: ; 0x02023A14
	ldr r2, _02023A24 ; =0x000F423F
	cmp r1, r2
	bls _02023A1C
	add r1, r2, #0x0
_02023A1C:
	str r1, [r0, #0x14]
	add r0, r1, #0x0
	bx lr
	nop
_02023A24: .word 0x000F423F

	thumb_func_start FUN_02023A28
FUN_02023A28: ; 0x02023A28
	ldrb r0, [r0, #0x1b]
	bx lr

	thumb_func_start FUN_02023A2C
FUN_02023A2C: ; 0x02023A2C
	strb r1, [r0, #0x1b]
	bx lr

	thumb_func_start FUN_02023A30
FUN_02023A30: ; 0x02023A30
	ldr r2, _02023A50 ; =0x000F423F
	cmp r1, r2
	bls _02023A3A
	str r2, [r0, #0x14]
	b _02023A40
_02023A3A:
	ldr r2, [r0, #0x14]
	add r1, r2, r1
	str r1, [r0, #0x14]
_02023A40:
	ldr r2, [r0, #0x14]
	ldr r1, _02023A50 ; =0x000F423F
	cmp r2, r1
	bls _02023A4A
	str r1, [r0, #0x14]
_02023A4A:
	ldr r0, [r0, #0x14]
	bx lr
	nop
_02023A50: .word 0x000F423F

	thumb_func_start FUN_02023A54
FUN_02023A54: ; 0x02023A54
	ldr r2, [r0, #0x14]
	cmp r2, r1
	bhs _02023A5E
	mov r1, #0x0
	b _02023A60
_02023A5E:
	sub r1, r2, r1
_02023A60:
	str r1, [r0, #0x14]
	ldr r0, [r0, #0x14]
	bx lr
	.balign 4

	thumb_func_start FUN_02023A68
FUN_02023A68: ; 0x02023A68
	ldrb r0, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_02023A6C
FUN_02023A6C: ; 0x02023A6C
	strb r1, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_02023A70
FUN_02023A70: ; 0x02023A70
	ldrb r0, [r0, #0x19]
	bx lr

	thumb_func_start FUN_02023A74
FUN_02023A74: ; 0x02023A74
	strb r1, [r0, #0x19]
	bx lr

	thumb_func_start FUN_02023A78
FUN_02023A78: ; 0x02023A78
	ldrb r2, [r0, #0x1d]
	mov r1, #0x1
	bic r2, r1
	mov r1, #0x1
	orr r1, r2
	strb r1, [r0, #0x1d]
	bx lr
	.balign 4

	thumb_func_start FUN_02023A88
FUN_02023A88: ; 0x02023A88
	ldrb r0, [r0, #0x1d]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_02023A90
FUN_02023A90: ; 0x02023A90
	ldrb r2, [r0, #0x1d]
	mov r1, #0x2
	orr r1, r2
	strb r1, [r0, #0x1d]
	bx lr
	.balign 4

	thumb_func_start FUN_02023A9C
FUN_02023A9C: ; 0x02023A9C
	ldrb r0, [r0, #0x1d]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_02023AA4
FUN_02023AA4: ; 0x02023AA4
	push {r3-r5, lr}
	mov r2, #0x7
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl StringNotEqualN
	cmp r0, #0x0
	bne _02023AC0
	ldr r1, [r5, #0x10]
	ldr r0, [r4, #0x10]
	cmp r1, r0
	bne _02023AC0
	mov r0, #0x1
	pop {r3-r5, pc}
_02023AC0:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02023AC4
FUN_02023AC4: ; 0x02023AC4
	mov r0, #0x20
	bx lr

	thumb_func_start FUN_02023AC8
FUN_02023AC8: ; 0x02023AC8
	mov r0, #0x20
	bx lr

	thumb_func_start FUN_02023ACC
FUN_02023ACC: ; 0x02023ACC
	ldr r3, _02023AD4 ; =MI_CpuCopy8
	mov r2, #0x20
	bx r3
	nop
_02023AD4: .word MI_CpuCopy8

	thumb_func_start FUN_02023AD8
FUN_02023AD8: ; 0x02023AD8
	ldr r3, _02023AE0 ; =Call_FillMemWithValue
	mov r1, #0x0
	mov r2, #0x20
	bx r3
	.balign 4
_02023AE0: .word Call_FillMemWithValue

	thumb_func_start FUN_02023AE4
FUN_02023AE4: ; 0x02023AE4
	ldr r3, _02023AF0 ; =FUN_02021E8C
	add r2, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	mov r2, #0xc
	bx r3
	.balign 4
_02023AF0: .word FUN_02021E8C

	thumb_func_start FUN_02023AF4
FUN_02023AF4: ; 0x02023AF4
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x18
	bl FUN_020219F4
	add r1, r5, #0x0
	add r4, r0, #0x0
	bl FUN_02021E28
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02023B0C
FUN_02023B0C: ; 0x02023B0C
	mov r2, #0x0
	cmp r1, #0xc
	bhi _02023B9E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02023B1E: ; jump table (using 16-bit offset)
	.short _02023B9E - _02023B1E - 2; case 0
	.short _02023B38 - _02023B1E - 2; case 1
	.short _02023B3C - _02023B1E - 2; case 2
	.short _02023B40 - _02023B1E - 2; case 3
	.short _02023B44 - _02023B1E - 2; case 4
	.short _02023B4C - _02023B1E - 2; case 5
	.short _02023B52 - _02023B1E - 2; case 6
	.short _02023B66 - _02023B1E - 2; case 7
	.short _02023B6C - _02023B1E - 2; case 8
	.short _02023B80 - _02023B1E - 2; case 9
	.short _02023B88 - _02023B1E - 2; case 10
	.short _02023B90 - _02023B1E - 2; case 11
	.short _02023B98 - _02023B1E - 2; case 12
_02023B38:
	ldrb r2, [r0, #0x1a]
	b _02023B9E
_02023B3C:
	ldrb r2, [r0, #0x1b]
	b _02023B9E
_02023B40:
	ldrh r2, [r0, #0x18]
	b _02023B9E
_02023B44:
	ldrb r0, [r0, #0x1e]
	lsl r0, r0, #0x1f
	lsr r2, r0, #0x1f
	b _02023B9E
_02023B4C:
	mov r1, #0x1c
	ldrsb r2, [r0, r1]
	b _02023B9E
_02023B52:
	mov r1, #0x1c
	ldrsb r0, [r0, r1]
	cmp r0, #0x0
	ble _02023B5E
	mov r2, #0x1
	b _02023B9E
_02023B5E:
	bge _02023B9E
	add r2, r1, #0x0
	sub r2, #0x1d
	b _02023B9E
_02023B66:
	mov r1, #0x1d
	ldrsb r2, [r0, r1]
	b _02023B9E
_02023B6C:
	mov r1, #0x1d
	ldrsb r0, [r0, r1]
	cmp r0, #0x0
	ble _02023B78
	mov r2, #0x1
	b _02023B9E
_02023B78:
	bge _02023B9E
	add r2, r1, #0x0
	sub r2, #0x1e
	b _02023B9E
_02023B80:
	ldrb r0, [r0, #0x1e]
	lsl r0, r0, #0x1c
	lsr r2, r0, #0x1f
	b _02023B9E
_02023B88:
	ldrb r0, [r0, #0x1e]
	lsl r0, r0, #0x1d
	lsr r2, r0, #0x1f
	b _02023B9E
_02023B90:
	ldrb r0, [r0, #0x1e]
	lsl r0, r0, #0x1e
	lsr r2, r0, #0x1f
	b _02023B9E
_02023B98:
	ldrb r0, [r0, #0x1e]
	lsl r0, r0, #0x1b
	lsr r2, r0, #0x1f
_02023B9E:
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02023BA4
FUN_02023BA4: ; 0x02023BA4
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x1
	blt _02023BB2
	bl ErrorHandling
_02023BB2:
	add r0, r4, #0x0
	mov r1, #0xd
	bl FUN_02022610
	add r4, r0, #0x0
	lsl r5, r5, #0x5
	add r0, r4, r5
	mov r1, #0x1
	bl FUN_02023B0C
	cmp r0, #0x0
	beq _02023BCE
	add r0, r4, r5
	pop {r3-r5, pc}
_02023BCE:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02023BD4
FUN_02023BD4: ; 0x02023BD4
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0xd
	bl FUN_02022610
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02023ACC
	pop {r4, pc}

	thumb_func_start FUN_02023BE8
FUN_02023BE8: ; 0x02023BE8
	push {r3, lr}
	cmp r1, #0x5
	bhs _02023BF6
	ldr r2, _02023C00 ; =0x02105BD4
	lsl r0, r1, #0x5
	add r0, r2, r0
	pop {r3, pc}
_02023BF6:
	mov r1, #0xd
	bl FUN_02022610
	pop {r3, pc}
	nop
_02023C00: .word 0x02105BD4

	thumb_func_start FUN_02023C04
FUN_02023C04: ; 0x02023C04
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	cmp r5, #0x5
	bhs _02023C2C
	ldr r2, _02023C3C ; =0x0000013A
	mov r0, #0x0
	mov r1, #0x1a
	bl FUN_0200A86C
	add r5, #0x38
	add r6, r0, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0200A8E0
	add r0, r6, #0x0
	bl FUN_0200A8B8
	pop {r4-r6, pc}
_02023C2C:
	mov r1, #0x0
	bl FUN_02023BA4
	add r1, r4, #0x0
	bl FUN_02023AE4
	pop {r4-r6, pc}
	nop
_02023C3C: .word 0x0000013A

	thumb_func_start FUN_02023C40
FUN_02023C40: ; 0x02023C40
	mov r0, #0x1e
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02023C48
FUN_02023C48: ; 0x02023C48
	push {r4, lr}
	mov r2, #0x1e
	add r4, r0, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl Call_FillMemWithValue
	add r0, r4, #0x0
	bl FUN_020669A0
	add r0, r4, #0x0
	add r0, #0xec
	bl FUN_020669A0
	mov r0, #0x76
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, r0, #0x4
	strb r1, [r4, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02023C74
FUN_02023C74: ; 0x02023C74
	mov r2, #0xec
	mul r2, r1
	add r0, r0, r2
	bx lr

	thumb_func_start FUN_02023C7C
FUN_02023C7C: ; 0x02023C7C
	bx lr
	.balign 4

	thumb_func_start FUN_02023C80
FUN_02023C80: ; 0x02023C80
	add r0, #0x88
	bx lr

	thumb_func_start FUN_02023C84
FUN_02023C84: ; 0x02023C84
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023C8C
FUN_02023C8C: ; 0x02023C8C
	bx lr
	.balign 4

	thumb_func_start FUN_02023C90
FUN_02023C90: ; 0x02023C90
	mov r1, #0x76
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start FUN_02023C98
FUN_02023C98: ; 0x02023C98
	mov r1, #0x77
	lsl r1, r1, #0x2
	ldrb r0, [r0, r1]
	bx lr

	thumb_func_start FUN_02023CA0
FUN_02023CA0: ; 0x02023CA0
	add r0, #0xe8
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023CA8
FUN_02023CA8: ; 0x02023CA8
	add r2, r0, #0x0
	add r2, #0xe8
	ldr r2, [r2, #0x0]
	add r0, #0xe8
	add r1, r2, r1
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023CB8
FUN_02023CB8: ; 0x02023CB8
	mov r2, #0x76
	lsl r2, r2, #0x2
	str r1, [r0, r2]
	bx lr

	thumb_func_start FUN_02023CC0
FUN_02023CC0: ; 0x02023CC0
	mov r2, #0x77
	lsl r2, r2, #0x2
	strb r1, [r0, r2]
	bx lr

	thumb_func_start FUN_02023CC8
FUN_02023CC8: ; 0x02023CC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0xc
	mov r2, #0x0
	bl FUN_020672BC
	add r5, #0xec
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xc
	mov r2, #0x0
	bl FUN_020672BC
	cmp r4, r0
	beq _02023CEA
	mov r0, #0x1
	pop {r3-r5, pc}
_02023CEA:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02023CF0
FUN_02023CF0: ; 0x02023CF0
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0x1d
_02023CF8:
	ldmia r3!, {r0-r1}
	stmia r4!, {r0-r1}
	sub r2, r2, #0x1
	bne _02023CF8
	ldr r0, [r3, #0x0]
	str r0, [r4, #0x0]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02023D08
FUN_02023D08: ; 0x02023D08
	push {r3-r4}
	mov r1, #0x0
	add r2, r0, #0x0
	add r4, r1, #0x0
_02023D10:
	add r1, r1, #0x1
	strh r4, [r2, #0x38]
	add r2, r2, #0x2
	cmp r1, #0x8
	blt _02023D10
	add r3, r0, #0x0
	mov r2, #0x0
_02023D1E:
	add r1, r3, #0x0
	add r1, #0x48
	add r4, r4, #0x1
	add r3, r3, #0x2
	strh r2, [r1, #0x0]
	cmp r4, #0xb
	blt _02023D1E
	ldr r1, _02023D38 ; =0x0000FFFF
	strh r1, [r0, #0x38]
	add r0, #0x48
	strh r1, [r0, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4
_02023D38: .word 0x0000FFFF

	thumb_func_start FUN_02023D3C
FUN_02023D3C: ; 0x02023D3C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020669A0
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0xe8
	add r4, #0x88
	str r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_02023D08
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02023D58
FUN_02023D58: ; 0x02023D58
	ldr r3, _02023D60 ; =FUN_02022610
	mov r1, #0x8
	bx r3
	nop
_02023D60: .word FUN_02022610

	thumb_func_start FUN_02023D64
FUN_02023D64: ; 0x02023D64
	mov r0, #0x4f
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_02023D6C
FUN_02023D6C: ; 0x02023D6C
	push {r4, lr}
	mov r1, #0x4f
	lsl r1, r1, #0x2
	bl FUN_02016998
	add r4, r0, #0x0
	bl FUN_02024378
	add r0, r4, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02023D80
FUN_02023D80: ; 0x02023D80
	ldr r3, _02023D88 ; =MI_CpuCopy8
	mov r2, #0x4f
	lsl r2, r2, #0x2
	bx r3
	.balign 4
_02023D88: .word MI_CpuCopy8

	thumb_func_start FUN_02023D8C
FUN_02023D8C: ; 0x02023D8C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02023DE8 ; =0x000001A6
	add r4, r1, #0x0
	cmp r4, r0
	beq _02023DA2
	add r0, r0, #0x1
	cmp r4, r0
	beq _02023DA2
	bl ErrorHandling
_02023DA2:
	lsl r1, r4, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x0
	bne _02023DB4
	mov r0, #0x0
	pop {r3-r5, pc}
_02023DB4:
	ldr r0, _02023DE8 ; =0x000001A6
	cmp r4, r0
	bne _02023DBE
	sub r0, #0x9e
	b _02023DC0
_02023DBE:
	sub r0, #0x9d
_02023DC0:
	add r0, r5, r0
	ldrb r1, [r0, #0x0]
	mov r2, #0x1
	add r0, r1, #0x0
	tst r0, r2
	bne _02023DCE
	mov r2, #0x0
_02023DCE:
	mov r0, #0x2
	tst r0, r1
	beq _02023DD8
	mov r0, #0x1
	b _02023DDA
_02023DD8:
	mov r0, #0x0
_02023DDA:
	cmp r2, r0
	bne _02023DE2
	mov r0, #0x1
	pop {r3-r5, pc}
_02023DE2:
	mov r0, #0x2
	pop {r3-r5, pc}
	nop
_02023DE8: .word 0x000001A6

	thumb_func_start FUN_02023DEC
FUN_02023DEC: ; 0x02023DEC
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _02023E6C ; =0x000001A6
	add r6, r1, #0x0
	add r5, r2, #0x0
	cmp r6, r0
	beq _02023E04
	add r0, r0, #0x1
	cmp r6, r0
	beq _02023E04
	bl ErrorHandling
_02023E04:
	lsl r1, r6, #0x10
	add r0, r7, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x0
	bne _02023E16
	mov r0, #0x0
	pop {r3-r7, pc}
_02023E16:
	ldr r0, _02023E6C ; =0x000001A6
	cmp r6, r0
	bne _02023E20
	sub r0, #0x9e
	b _02023E22
_02023E20:
	sub r0, #0x9d
_02023E22:
	add r4, r7, r0
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_02023D8C
	mov r6, #0x0
	cmp r0, #0x0
	bls _02023E66
	mov r1, #0x1
_02023E34:
	add r2, r6, #0x1
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	sub r2, r2, #0x1
	lsl r2, r2, #0x10
	lsr r3, r2, #0x10
	add r7, r3, #0x0
	mov r2, #0x7
	asr r3, r3, #0x3
	and r7, r2
	add r2, r1, #0x0
	ldrb r3, [r4, r3]
	lsl r2, r7
	tst r2, r3
	beq _02023E56
	add r2, r1, #0x0
	b _02023E58
_02023E56:
	mov r2, #0x0
_02023E58:
	cmp r2, r5
	bne _02023E60
	mov r0, #0x1
	pop {r3-r7, pc}
_02023E60:
	add r6, r6, #0x1
	cmp r6, r0
	blo _02023E34
_02023E66:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02023E6C: .word 0x000001A6

	thumb_func_start FUN_02023E70
FUN_02023E70: ; 0x02023E70
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, _02023F28 ; =0x000001A6
	add r5, r1, #0x0
	add r7, r2, #0x0
	cmp r5, r0
	beq _02023E88
	add r0, r0, #0x1
	cmp r5, r0
	beq _02023E88
	bl ErrorHandling
_02023E88:
	lsl r2, r7, #0x18
	add r0, r6, #0x0
	add r1, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02023DEC
	cmp r0, #0x0
	bne _02023F26
	ldr r0, _02023F28 ; =0x000001A6
	cmp r5, r0
	bne _02023EA2
	sub r0, #0x9e
	b _02023EA4
_02023EA2:
	sub r0, #0x9d
_02023EA4:
	add r4, r6, r0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02023D8C
	add r5, r0, #0x0
	cmp r5, #0x2
	bge _02023F26
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x2
	blo _02023EC6
	bl ErrorHandling
_02023EC6:
	sub r0, r6, #0x1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r2, r1, #0x0
	mov r0, #0x7
	and r2, r0
	asr r1, r1, #0x3
	mov r3, #0x1
	lsl r3, r2
	ldrb r0, [r4, r1]
	mvn r3, r3
	and r0, r3
	strb r0, [r4, r1]
	lsl r0, r7, #0x18
	lsr r6, r0, #0x18
	add r0, r6, #0x0
	ldrb r3, [r4, r1]
	lsl r0, r2
	orr r0, r3
	strb r0, [r4, r1]
	cmp r5, #0x0
	bne _02023F26
	add r0, r5, #0x2
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r6, #0x2
	blo _02023F00
	bl ErrorHandling
_02023F00:
	sub r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r0, #0x7
	add r1, r2, #0x0
	and r1, r0
	asr r0, r2, #0x3
	mov r2, #0x1
	lsl r2, r1
	ldrb r3, [r4, r0]
	mvn r2, r2
	and r2, r3
	strb r2, [r4, r0]
	add r2, r6, #0x0
	ldrb r3, [r4, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strb r1, [r4, r0]
_02023F26:
	pop {r3-r7, pc}
	.balign 4
_02023F28: .word 0x000001A6

	thumb_func_start FUN_02023F2C
FUN_02023F2C: ; 0x02023F2C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x67
	add r4, r1, #0x0
	lsl r0, r0, #0x2
	cmp r4, r0
	beq _02023F44
	add r0, r0, #0x1
	cmp r4, r0
	beq _02023F44
	bl ErrorHandling
_02023F44:
	lsl r1, r4, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x0
	bne _02023F56
	mov r0, #0x0
	pop {r3-r5, pc}
_02023F56:
	mov r0, #0x67
	lsl r0, r0, #0x2
	cmp r4, r0
	bne _02023F62
	sub r0, #0x92
	b _02023F64
_02023F62:
	sub r0, #0x91
_02023F64:
	add r1, r5, r0
	mov r0, #0x0
	mov r3, #0x3
_02023F6A:
	lsl r2, r0, #0x10
	lsr r5, r2, #0x10
	asr r2, r5, #0x2
	ldrb r4, [r1, r2]
	lsl r2, r5, #0x1e
	lsr r2, r2, #0x1d
	asr r4, r2
	add r2, r4, #0x0
	and r2, r3
	cmp r2, #0x3
	beq _02023F86
	add r0, r0, #0x1
	cmp r0, #0x3
	blt _02023F6A
_02023F86:
	pop {r3-r5, pc}

	thumb_func_start FUN_02023F88
FUN_02023F88: ; 0x02023F88
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r0, #0x67
	add r5, r1, #0x0
	lsl r0, r0, #0x2
	add r4, r2, #0x0
	cmp r5, r0
	beq _02023FA2
	add r0, r0, #0x1
	cmp r5, r0
	beq _02023FA2
	bl ErrorHandling
_02023FA2:
	lsl r1, r5, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x0
	bne _02023FB4
	mov r0, #0x0
	pop {r4-r6, pc}
_02023FB4:
	mov r0, #0x67
	lsl r0, r0, #0x2
	cmp r5, r0
	bne _02023FC0
	sub r0, #0x92
	b _02023FC2
_02023FC0:
	sub r0, #0x91
_02023FC2:
	add r1, r6, r0
	mov r0, #0x0
	mov r3, #0x3
_02023FC8:
	lsl r2, r0, #0x10
	lsr r6, r2, #0x10
	asr r2, r6, #0x2
	ldrb r5, [r1, r2]
	lsl r2, r6, #0x1e
	lsr r2, r2, #0x1d
	asr r5, r2
	add r2, r5, #0x0
	and r2, r3
	cmp r2, r4
	bne _02023FE2
	mov r0, #0x1
	pop {r4-r6, pc}
_02023FE2:
	add r0, r0, #0x1
	cmp r0, #0x3
	blt _02023FC8
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02023FEC
FUN_02023FEC: ; 0x02023FEC
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r0, #0x67
	add r5, r1, #0x0
	lsl r0, r0, #0x2
	add r7, r2, #0x0
	cmp r5, r0
	beq _02024006
	add r0, r0, #0x1
	cmp r5, r0
	beq _02024006
	bl ErrorHandling
_02024006:
	lsl r2, r7, #0x18
	add r0, r6, #0x0
	add r1, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02023F88
	cmp r0, #0x0
	bne _02024064
	mov r0, #0x67
	lsl r0, r0, #0x2
	cmp r5, r0
	bne _02024022
	sub r0, #0x92
	b _02024024
_02024022:
	sub r0, #0x91
_02024024:
	add r4, r6, r0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02023F2C
	add r5, r0, #0x0
	cmp r5, #0x3
	bge _02024064
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x4
	blo _02024040
	bl ErrorHandling
_02024040:
	lsl r0, r5, #0x10
	lsr r2, r0, #0x10
	lsl r0, r2, #0x1e
	lsr r1, r0, #0x1d
	asr r0, r2, #0x2
	mov r2, #0x3
	lsl r2, r1
	ldrb r3, [r4, r0]
	mvn r2, r2
	and r2, r3
	strb r2, [r4, r0]
	lsl r2, r7, #0x18
	lsr r2, r2, #0x18
	ldrb r3, [r4, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strb r1, [r4, r0]
_02024064:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02024068
FUN_02024068: ; 0x02024068
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r6, #0x4
	blo _02024078
	bl ErrorHandling
_02024078:
	cmp r4, #0xf
	bls _02024080
	bl ErrorHandling
_02024080:
	cmp r6, #0x2
	bhs _0202409E
	lsl r0, r6, #0x2
	add r0, #0x18
	mov r1, #0xf
	lsl r1, r0
	ldr r2, [r5, #0x40]
	mvn r1, r1
	and r2, r1
	add r1, r4, #0x0
	lsl r1, r0
	add r0, r2, #0x0
	orr r0, r1
	str r0, [r5, #0x40]
	pop {r4-r6, pc}
_0202409E:
	sub r0, r6, #0x2
	lsl r0, r0, #0x18
	add r1, r5, #0x0
	lsr r0, r0, #0x16
	add r1, #0x80
	ldr r2, [r1, #0x0]
	add r0, #0x18
	mov r1, #0xf
	lsl r1, r0
	mvn r1, r1
	and r2, r1
	add r1, r5, #0x0
	add r1, #0x80
	str r2, [r1, #0x0]
	add r1, r5, #0x0
	add r1, #0x80
	ldr r2, [r1, #0x0]
	add r1, r4, #0x0
	lsl r1, r0
	add r0, r2, #0x0
	orr r0, r1
	add r5, #0x80
	str r0, [r5, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020240D0
FUN_020240D0: ; 0x020240D0
	push {r3-r6}
	mov r3, #0xf
	mov r1, #0x0
	add r4, r3, #0x0
_020240D8:
	lsl r2, r1, #0x18
	lsr r6, r2, #0x18
	cmp r6, #0x2
	bhs _020240EE
	lsl r2, r6, #0x2
	ldr r5, [r0, #0x40]
	add r2, #0x18
	lsr r5, r2
	add r2, r5, #0x0
	and r2, r4
	b _02024102
_020240EE:
	add r2, r0, #0x0
	add r2, #0x80
	ldr r5, [r2, #0x0]
	sub r2, r6, #0x2
	lsl r2, r2, #0x18
	lsr r2, r2, #0x16
	add r2, #0x18
	lsr r5, r2
	add r2, r5, #0x0
	and r2, r3
_02024102:
	cmp r2, #0xf
	beq _0202410C
	add r1, r1, #0x1
	cmp r1, #0x4
	blt _020240D8
_0202410C:
	add r0, r1, #0x0
	pop {r3-r6}
	bx lr
	.balign 4

	thumb_func_start FUN_02024114
FUN_02024114: ; 0x02024114
	push {r4-r7}
	mov r2, #0xf
	mov r6, #0x0
	add r3, r2, #0x0
_0202411C:
	lsl r4, r6, #0x18
	lsr r5, r4, #0x18
	cmp r5, #0x2
	bhs _02024134
	ldr r7, [r0, #0x40]
	lsl r4, r5, #0x2
	add r4, #0x18
	add r5, r7, #0x0
	lsr r5, r4
	add r4, r5, #0x0
	and r4, r3
	b _02024146
_02024134:
	add r4, r0, #0x0
	sub r5, r5, #0x2
	add r4, #0x80
	lsl r5, r5, #0x18
	lsr r5, r5, #0x16
	ldr r4, [r4, #0x0]
	add r5, #0x18
	lsr r4, r5
	and r4, r2
_02024146:
	cmp r1, r4
	bne _02024150
	mov r0, #0x1
	pop {r4-r7}
	bx lr
_02024150:
	add r6, r6, #0x1
	cmp r6, #0x4
	blt _0202411C
	mov r0, #0x0
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_0202415C
FUN_0202415C: ; 0x0202415C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, _02024198 ; =0x00000182
	cmp r6, r0
	bne _02024196
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02024114
	cmp r0, #0x0
	bne _02024196
	add r0, r5, #0x0
	bl FUN_020240D0
	add r2, r0, #0x0
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	bl FUN_02024068
_02024196:
	pop {r4-r6, pc}
	.balign 4
_02024198: .word 0x00000182

	thumb_func_start FUN_0202419C
FUN_0202419C: ; 0x0202419C
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r4, #0x0
	mov r6, #0xf
_020241A4:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl FUN_02024068
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _020241A4
	pop {r4-r6, pc}

	thumb_func_start FUN_020241B8
FUN_020241B8: ; 0x020241B8
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xc9
	bne _02024210
	add r0, r2, #0x0
	bl FUN_020690CC
	lsl r1, r0, #0x18
	lsr r3, r1, #0x18
	mov r1, #0x43
	mov r4, #0x0
	add r6, r5, #0x0
	lsl r1, r1, #0x2
_020241D4:
	ldrb r2, [r6, r1]
	cmp r3, r2
	bne _020241DE
	mov r1, #0x1
	b _020241E8
_020241DE:
	add r4, r4, #0x1
	add r6, r6, #0x1
	cmp r4, #0x1c
	blt _020241D4
	mov r1, #0x0
_020241E8:
	cmp r1, #0x0
	bne _02024290
	mov r1, #0x43
	mov r3, #0x0
	add r4, r5, #0x0
	lsl r1, r1, #0x2
_020241F4:
	ldrb r2, [r4, r1]
	cmp r2, #0xff
	beq _02024202
	add r3, r3, #0x1
	add r4, r4, #0x1
	cmp r3, #0x1c
	blt _020241F4
_02024202:
	cmp r3, #0x1c
	bge _02024290
	mov r1, #0x43
	add r2, r5, r3
	lsl r1, r1, #0x2
	strb r0, [r2, r1]
	pop {r4-r6, pc}
_02024210:
	mov r6, #0x67
	lsl r6, r6, #0x2
	cmp r4, r6
	bne _0202422E
	add r0, r2, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02023FEC
	pop {r4-r6, pc}
_0202422E:
	add r3, r6, #0x1
	cmp r4, r3
	bne _0202424A
	add r0, r2, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02023FEC
	pop {r4-r6, pc}
_0202424A:
	add r3, r6, #0x0
	add r3, #0xa
	cmp r4, r3
	bne _02024268
	add r0, r2, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02023E70
	pop {r4-r6, pc}
_02024268:
	add r3, r6, #0x0
	add r3, #0xb
	cmp r4, r3
	bne _02024286
	add r0, r2, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02023E70
	pop {r4-r6, pc}
_02024286:
	sub r6, #0x1a
	cmp r4, r6
	bne _02024290
	bl FUN_0202415C
_02024290:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02024294
FUN_02024294: ; 0x02024294
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r0, r1, #0x0
	bl FUN_02087A50
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02087A1C
	cmp r4, #0xe
	beq _020242C0
	cmp r0, #0x6
	beq _020242C0
	ldr r1, _020242C4 ; =0x00000129
	add r3, r5, r1
	ldrb r2, [r3, r4]
	mov r1, #0x1
	lsl r1, r0
	add r0, r2, #0x0
	orr r0, r1
	strb r0, [r3, r4]
_020242C0:
	pop {r4-r6, pc}
	nop
_020242C4: .word 0x00000129

	thumb_func_start FUN_020242C8
FUN_020242C8: ; 0x020242C8
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x12
	add r4, r2, #0x0
	bl FUN_02068678
	cmp r0, #0xff
	bne _020242EA
	cmp r4, #0x0
	bne _020242E4
	mov r0, #0x2
	pop {r4-r6, pc}
_020242E4:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_020242EA:
	sub r0, r6, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r1, #0x1
	mov r0, #0x7
	add r3, r2, #0x0
	and r3, r0
	add r0, r1, #0x0
	lsl r0, r3
	asr r3, r2, #0x3
	add r3, r5, r3
	add r3, #0x84
	ldrb r3, [r3, #0x0]
	tst r0, r3
	bne _0202430A
	mov r1, #0x0
_0202430A:
	lsl r0, r1, #0x18
	lsr r1, r0, #0x18
	cmp r4, #0x1
	bne _0202433A
	add r4, r2, #0x0
	asr r2, r2, #0x3
	add r2, r5, r2
	mov r0, #0x7
	add r2, #0xc4
	mov r3, #0x1
	and r4, r0
	add r0, r3, #0x0
	ldrb r2, [r2, #0x0]
	lsl r0, r4
	tst r0, r2
	bne _0202432C
	mov r3, #0x0
_0202432C:
	lsl r0, r3, #0x18
	lsr r0, r0, #0x18
	cmp r0, r1
	bne _0202433C
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_0202433A:
	add r0, r1, #0x0
_0202433C:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02024340
FUN_02024340: ; 0x02024340
	push {r4-r5}
	mov r3, #0x0
	ldr r5, _02024360 ; =0x020EE942
	mov r4, #0x1
	add r1, r3, #0x0
_0202434A:
	ldrh r2, [r5, #0x0]
	cmp r0, r2
	bne _02024352
	add r4, r1, #0x0
_02024352:
	add r3, r3, #0x1
	add r5, r5, #0x2
	cmp r3, #0xb
	blt _0202434A
	add r0, r4, #0x0
	pop {r4-r5}
	bx lr
	.balign 4
_02024360: .word 0x020EE942

	thumb_func_start FUN_02024364
FUN_02024364: ; 0x02024364
	ldr r1, _02024374 ; =0x000001EA
	mov r2, #0x1
	cmp r0, r1
	bne _0202436E
	mov r2, #0x0
_0202436E:
	add r0, r2, #0x0
	bx lr
	nop
_02024374: .word 0x000001EA

	thumb_func_start FUN_02024378
FUN_02024378: ; 0x02024378
	push {r4, lr}
	mov r2, #0x4f
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r4, r0, #0x0
	bl Call_FillMemWithValue
	ldr r0, _020243C0 ; =0xBEEFCAFE
	mov r1, #0x0
	str r0, [r4, #0x0]
	ldr r0, _020243C4 ; =0x00000139
	mov r2, #0x1c
	strb r1, [r4, r0]
	sub r0, #0x2d
	add r0, r4, r0
	mov r1, #0xff
	bl Call_FillMemWithValue
	mov r1, #0xff
	add r0, r1, #0x0
	add r0, #0x9
	strb r1, [r4, r0]
	add r0, r1, #0x0
	add r0, #0xa
	strb r1, [r4, r0]
	add r0, r1, #0x0
	add r0, #0xb
	strb r1, [r4, r0]
	add r0, r1, #0x0
	add r0, #0xc
	strb r1, [r4, r0]
	add r0, r4, #0x0
	bl FUN_0202419C
	pop {r4, pc}
	nop
_020243C0: .word 0xBEEFCAFE
_020243C4: .word 0x00000139

	thumb_func_start FUN_020243C8
FUN_020243C8: ; 0x020243C8
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, _020243FC ; =0xBEEFCAFE
	cmp r1, r0
	beq _020243D8
	bl ErrorHandling
_020243D8:
	ldr r7, _02024400 ; =0x000001ED
	mov r5, #0x0
	mov r4, #0x1
_020243DE:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_02024594
	cmp r0, #0x1
	bne _020243EE
	add r5, r5, #0x1
_020243EE:
	add r4, r4, #0x1
	cmp r4, r7
	ble _020243DE
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	pop {r3-r7, pc}
	nop
_020243FC: .word 0xBEEFCAFE
_02024400: .word 0x000001ED

	thumb_func_start FUN_02024404
FUN_02024404: ; 0x02024404
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, _02024438 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024414
	bl ErrorHandling
_02024414:
	ldr r7, _0202443C ; =0x000001ED
	mov r5, #0x0
	mov r4, #0x1
_0202441A:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x1
	bne _0202442A
	add r5, r5, #0x1
_0202442A:
	add r4, r4, #0x1
	cmp r4, r7
	ble _0202441A
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	pop {r3-r7, pc}
	nop
_02024438: .word 0xBEEFCAFE
_0202443C: .word 0x000001ED

	thumb_func_start FUN_02024440
FUN_02024440: ; 0x02024440
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02024CA4
	cmp r0, #0x0
	beq _02024454
	add r0, r4, #0x0
	bl FUN_02024404
	pop {r4, pc}
_02024454:
	add r0, r4, #0x0
	bl FUN_020244A4
	pop {r4, pc}

	thumb_func_start FUN_0202445C
FUN_0202445C: ; 0x0202445C
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, _0202449C ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202446C
	bl ErrorHandling
_0202446C:
	ldr r7, _020244A0 ; =0x000001ED
	mov r5, #0x0
	mov r4, #0x1
_02024472:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_02024594
	cmp r0, #0x1
	bne _0202448E
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02069B40
	cmp r0, #0x0
	beq _0202448E
	add r5, r5, #0x1
_0202448E:
	add r4, r4, #0x1
	cmp r4, r7
	ble _02024472
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	pop {r3-r7, pc}
	nop
_0202449C: .word 0xBEEFCAFE
_020244A0: .word 0x000001ED

	thumb_func_start FUN_020244A4
FUN_020244A4: ; 0x020244A4
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, _020244E4 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020244B4
	bl ErrorHandling
_020244B4:
	ldr r7, _020244E8 ; =0x000001ED
	mov r5, #0x0
	mov r4, #0x1
_020244BA:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x1
	bne _020244D6
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02069B40
	cmp r0, #0x0
	beq _020244D6
	add r5, r5, #0x1
_020244D6:
	add r4, r4, #0x1
	cmp r4, r7
	ble _020244BA
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	pop {r3-r7, pc}
	nop
_020244E4: .word 0xBEEFCAFE
_020244E8: .word 0x000001ED

	thumb_func_start FUN_020244EC
FUN_020244EC: ; 0x020244EC
	push {r3, lr}
	bl FUN_02024518
	ldr r1, _02024500 ; =0x000001E2
	cmp r0, r1
	blo _020244FC
	mov r0, #0x1
	pop {r3, pc}
_020244FC:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02024500: .word 0x000001E2

	thumb_func_start FUN_02024504
FUN_02024504: ; 0x02024504
	push {r3, lr}
	bl FUN_02024550
	cmp r0, #0x96
	blo _02024512
	mov r0, #0x1
	pop {r3, pc}
_02024512:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02024518
FUN_02024518: ; 0x02024518
	push {r3-r7, lr}
	ldr r7, _0202454C ; =0x000001ED
	add r6, r0, #0x0
	mov r5, #0x0
	mov r4, #0x1
_02024522:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_02024594
	cmp r0, #0x1
	bne _02024542
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02024340
	cmp r0, #0x1
	bne _02024542
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_02024542:
	add r4, r4, #0x1
	cmp r4, r7
	ble _02024522
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4
_0202454C: .word 0x000001ED

	thumb_func_start FUN_02024550
FUN_02024550: ; 0x02024550
	push {r3-r7, lr}
	ldr r7, _02024590 ; =0x000001ED
	add r6, r0, #0x0
	mov r5, #0x0
	mov r4, #0x1
_0202455A:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x1
	bne _02024586
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02069B40
	cmp r0, #0x0
	beq _02024586
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02024364
	cmp r0, #0x1
	bne _02024586
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_02024586:
	add r4, r4, #0x1
	cmp r4, r7
	ble _0202455A
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4
_02024590: .word 0x000001ED

	thumb_func_start FUN_02024594
FUN_02024594: ; 0x02024594
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020245E8 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020245A6
	bl ErrorHandling
_020245A6:
	cmp r4, #0x0
	beq _020245B0
	ldr r0, _020245EC ; =0x000001ED
	cmp r4, r0
	bls _020245B8
_020245B0:
	bl ErrorHandling
	mov r0, #0x1
	b _020245BA
_020245B8:
	mov r0, #0x0
_020245BA:
	cmp r0, #0x0
	beq _020245C2
	mov r0, #0x0
	pop {r3-r5, pc}
_020245C2:
	sub r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r0, #0x1
	mov r1, #0x7
	and r1, r2
	add r3, r0, #0x0
	lsl r3, r1
	asr r1, r2, #0x3
	add r2, r5, r1
	ldrb r1, [r2, #0x4]
	tst r1, r3
	beq _020245E4
	add r2, #0x44
	ldrb r1, [r2, #0x0]
	tst r1, r3
	bne _020245E6
_020245E4:
	mov r0, #0x0
_020245E6:
	pop {r3-r5, pc}
	.balign 4
_020245E8: .word 0xBEEFCAFE
_020245EC: .word 0x000001ED

	thumb_func_start FUN_020245F0
FUN_020245F0: ; 0x020245F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024640 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024602
	bl ErrorHandling
_02024602:
	cmp r4, #0x0
	beq _0202460C
	ldr r0, _02024644 ; =0x000001ED
	cmp r4, r0
	bls _02024614
_0202460C:
	bl ErrorHandling
	mov r0, #0x1
	b _02024616
_02024614:
	mov r0, #0x0
_02024616:
	cmp r0, #0x0
	beq _0202461E
	mov r0, #0x0
	pop {r3-r5, pc}
_0202461E:
	sub r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	mov r0, #0x1
	mov r1, #0x7
	and r1, r3
	add r2, r0, #0x0
	lsl r2, r1
	asr r1, r3, #0x3
	add r1, r5, r1
	add r1, #0x44
	ldrb r1, [r1, #0x0]
	tst r1, r2
	bne _0202463C
	mov r0, #0x0
_0202463C:
	pop {r3-r5, pc}
	nop
_02024640: .word 0xBEEFCAFE
_02024644: .word 0x000001ED

	thumb_func_start FUN_02024648
FUN_02024648: ; 0x02024648
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024670 ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202465A
	bl ErrorHandling
_0202465A:
	cmp r4, #0x0
	bne _02024666
	mov r0, #0x41
	lsl r0, r0, #0x2
	ldr r6, [r5, r0]
	b _0202466A
_02024666:
	bl ErrorHandling
_0202466A:
	add r0, r6, #0x0
	pop {r4-r6, pc}
	nop
_02024670: .word 0xBEEFCAFE

	thumb_func_start FUN_02024674
FUN_02024674: ; 0x02024674
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020246D4 ; =0xBEEFCAFE
	add r6, r2, #0x0
	cmp r1, r0
	beq _02024688
	bl ErrorHandling
_02024688:
	cmp r4, #0x0
	beq _02024692
	ldr r0, _020246D8 ; =0x000001ED
	cmp r4, r0
	bls _0202469A
_02024692:
	bl ErrorHandling
	mov r0, #0x1
	b _0202469C
_0202469A:
	mov r0, #0x0
_0202469C:
	cmp r0, #0x0
	beq _020246A6
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_020246A6:
	sub r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	add r3, r2, #0x0
	asr r2, r2, #0x3
	add r2, r5, r2
	mov r0, #0x7
	add r2, #0x44
	mov r1, #0x1
	and r3, r0
	ldrb r2, [r2, #0x0]
	lsl r1, r3
	tst r1, r2
	beq _020246CE
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020242C8
	pop {r4-r6, pc}
_020246CE:
	sub r0, #0x8
	pop {r4-r6, pc}
	nop
_020246D4: .word 0xBEEFCAFE
_020246D8: .word 0x000001ED

	thumb_func_start FUN_020246DC
FUN_020246DC: ; 0x020246DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024718 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020246EE
	bl ErrorHandling
_020246EE:
	mov r0, #0x43
	mov r2, #0x0
	lsl r0, r0, #0x2
_020246F4:
	add r1, r5, r2
	ldrb r1, [r1, r0]
	cmp r1, #0xff
	beq _02024702
	add r2, r2, #0x1
	cmp r2, #0x1c
	blt _020246F4
_02024702:
	cmp r2, r4
	bgt _0202470C
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0202470C:
	mov r0, #0x43
	add r1, r5, r4
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	pop {r3-r5, pc}
	nop
_02024718: .word 0xBEEFCAFE

	thumb_func_start FUN_0202471C
FUN_0202471C: ; 0x0202471C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024744 ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202472C
	bl ErrorHandling
_0202472C:
	mov r1, #0x43
	mov r0, #0x0
	lsl r1, r1, #0x2
_02024732:
	add r2, r4, r0
	ldrb r2, [r2, r1]
	cmp r2, #0xff
	beq _02024740
	add r0, r0, #0x1
	cmp r0, #0x1c
	blt _02024732
_02024740:
	pop {r4, pc}
	nop
_02024744: .word 0xBEEFCAFE

	thumb_func_start FUN_02024748
FUN_02024748: ; 0x02024748
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202479C ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202475A
	bl ErrorHandling
_0202475A:
	ldr r1, _020247A0 ; =0x000001A6
	add r0, r5, #0x0
	bl FUN_02023D8C
	cmp r0, r4
	bgt _0202476C
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0202476C:
	cmp r4, #0x2
	blt _02024774
	bl ErrorHandling
_02024774:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	sub r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r0, #0x1
	mov r1, #0x7
	and r1, r2
	add r3, r0, #0x0
	lsl r3, r1
	asr r1, r2, #0x3
	add r2, r5, r1
	mov r1, #0x42
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	tst r1, r3
	bne _0202479A
	mov r0, #0x0
_0202479A:
	pop {r3-r5, pc}
	.balign 4
_0202479C: .word 0xBEEFCAFE
_020247A0: .word 0x000001A6

	thumb_func_start FUN_020247A4
FUN_020247A4: ; 0x020247A4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _020247C0 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020247B4
	bl ErrorHandling
_020247B4:
	ldr r1, _020247C4 ; =0x000001A6
	add r0, r4, #0x0
	bl FUN_02023D8C
	pop {r4, pc}
	nop
_020247C0: .word 0xBEEFCAFE
_020247C4: .word 0x000001A6

	thumb_func_start FUN_020247C8
FUN_020247C8: ; 0x020247C8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202481C ; =0xBEEFCAFE
	cmp r1, r0
	beq _020247DA
	bl ErrorHandling
_020247DA:
	ldr r1, _02024820 ; =0x000001A7
	add r0, r5, #0x0
	bl FUN_02023D8C
	cmp r0, r4
	bgt _020247EC
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_020247EC:
	cmp r4, #0x2
	blt _020247F4
	bl ErrorHandling
_020247F4:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	sub r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r0, #0x1
	mov r1, #0x7
	and r1, r2
	add r3, r0, #0x0
	lsl r3, r1
	asr r1, r2, #0x3
	add r2, r5, r1
	ldr r1, _02024824 ; =0x00000109
	ldrb r1, [r2, r1]
	tst r1, r3
	bne _02024818
	mov r0, #0x0
_02024818:
	pop {r3-r5, pc}
	nop
_0202481C: .word 0xBEEFCAFE
_02024820: .word 0x000001A7
_02024824: .word 0x00000109

	thumb_func_start FUN_02024828
FUN_02024828: ; 0x02024828
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024844 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024838
	bl ErrorHandling
_02024838:
	ldr r1, _02024848 ; =0x000001A7
	add r0, r4, #0x0
	bl FUN_02023D8C
	pop {r4, pc}
	nop
_02024844: .word 0xBEEFCAFE
_02024848: .word 0x000001A7

	thumb_func_start FUN_0202484C
FUN_0202484C: ; 0x0202484C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024894 ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202485E
	bl ErrorHandling
_0202485E:
	mov r1, #0x67
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	bl FUN_02023F2C
	cmp r0, r4
	bgt _02024872
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_02024872:
	cmp r4, #0x3
	blt _0202487A
	bl ErrorHandling
_0202487A:
	lsl r0, r4, #0x10
	lsr r2, r0, #0x10
	asr r0, r2, #0x2
	add r1, r5, r0
	ldr r0, _02024898 ; =0x0000010A
	ldrb r1, [r1, r0]
	lsl r0, r2, #0x1e
	lsr r0, r0, #0x1d
	asr r1, r0
	mov r0, #0x3
	and r0, r1
	pop {r3-r5, pc}
	nop
_02024894: .word 0xBEEFCAFE
_02024898: .word 0x0000010A

	thumb_func_start FUN_0202489C
FUN_0202489C: ; 0x0202489C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _020248B8 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020248AC
	bl ErrorHandling
_020248AC:
	mov r1, #0x67
	add r0, r4, #0x0
	lsl r1, r1, #0x2
	bl FUN_02023F2C
	pop {r4, pc}
	.balign 4
_020248B8: .word 0xBEEFCAFE

	thumb_func_start FUN_020248BC
FUN_020248BC: ; 0x020248BC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024900 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020248CE
	bl ErrorHandling
_020248CE:
	ldr r1, _02024904 ; =0x0000019D
	add r0, r5, #0x0
	bl FUN_02023F2C
	cmp r0, r4
	bgt _020248E0
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_020248E0:
	cmp r4, #0x3
	blt _020248E8
	bl ErrorHandling
_020248E8:
	lsl r0, r4, #0x10
	lsr r2, r0, #0x10
	asr r0, r2, #0x2
	add r1, r5, r0
	ldr r0, _02024908 ; =0x0000010B
	ldrb r1, [r1, r0]
	lsl r0, r2, #0x1e
	lsr r0, r0, #0x1d
	asr r1, r0
	mov r0, #0x3
	and r0, r1
	pop {r3-r5, pc}
	.balign 4
_02024900: .word 0xBEEFCAFE
_02024904: .word 0x0000019D
_02024908: .word 0x0000010B

	thumb_func_start FUN_0202490C
FUN_0202490C: ; 0x0202490C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024928 ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202491C
	bl ErrorHandling
_0202491C:
	ldr r1, _0202492C ; =0x0000019D
	add r0, r4, #0x0
	bl FUN_02023F2C
	pop {r4, pc}
	nop
_02024928: .word 0xBEEFCAFE
_0202492C: .word 0x0000019D

	thumb_func_start FUN_02024930
FUN_02024930: ; 0x02024930
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202496C ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024942
	bl ErrorHandling
_02024942:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x2
	bhs _02024958
	lsl r0, r0, #0x2
	ldr r1, [r5, #0x40]
	add r0, #0x18
	lsr r1, r0
	mov r0, #0xf
	and r0, r1
	pop {r3-r5, pc}
_02024958:
	add r5, #0x80
	sub r0, r0, #0x2
	lsl r0, r0, #0x18
	ldr r1, [r5, #0x0]
	lsr r0, r0, #0x16
	add r0, #0x18
	lsr r1, r0
	mov r0, #0xf
	and r0, r1
	pop {r3-r5, pc}
	.balign 4
_0202496C: .word 0xBEEFCAFE

	thumb_func_start FUN_02024970
FUN_02024970: ; 0x02024970
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024988 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024980
	bl ErrorHandling
_02024980:
	add r0, r4, #0x0
	bl FUN_020240D0
	pop {r4, pc}
	.balign 4
_02024988: .word 0xBEEFCAFE

	thumb_func_start FUN_0202498C
FUN_0202498C: ; 0x0202498C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	add r0, r1, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	mov r1, #0x0
	ldr r0, [sp, #0x0]
	add r2, r1, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_020689E0
	add r6, r0, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024AE4 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020249C4
	bl ErrorHandling
_020249C4:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020249D0
	ldr r1, _02024AE8 ; =0x000001ED
	cmp r0, r1
	bls _020249D8
_020249D0:
	bl ErrorHandling
	mov r0, #0x1
	b _020249DA
_020249D8:
	mov r0, #0x0
_020249DA:
	cmp r0, #0x0
	bne _02024ADE
	ldr r0, [sp, #0x4]
	mov r2, #0x1
	sub r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	mov r0, #0x7
	and r0, r4
	add r1, r2, #0x0
	lsl r1, r0
	asr r0, r4, #0x3
	add r3, r5, r0
	add r3, #0x44
	ldrb r3, [r3, #0x0]
	tst r3, r1
	bne _02024A70
	ldr r1, _02024AEC ; =0x00000147
	ldr r0, [sp, #0x4]
	cmp r0, r1
	bne _02024A08
	sub r1, #0x43
	str r7, [r5, r1]
_02024A08:
	lsl r0, r6, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x2
	bls _02024A14
	bl ErrorHandling
_02024A14:
	cmp r6, #0x2
	bne _02024A1A
	mov r6, #0x0
_02024A1A:
	cmp r6, #0x2
	blo _02024A22
	bl ErrorHandling
_02024A22:
	add r2, r5, #0x0
	mov r0, #0x7
	add r3, r4, #0x0
	and r3, r0
	mov r0, #0x1
	lsl r0, r3
	add r2, #0xc4
	asr r1, r4, #0x3
	ldrb r7, [r2, r1]
	mvn r0, r0
	and r0, r7
	strb r0, [r2, r1]
	add r0, r6, #0x0
	ldrb r7, [r2, r1]
	lsl r0, r3
	orr r0, r7
	strb r0, [r2, r1]
	cmp r6, #0x2
	blo _02024A4C
	bl ErrorHandling
_02024A4C:
	add r1, r5, #0x0
	mov r0, #0x7
	add r2, r4, #0x0
	and r2, r0
	mov r3, #0x1
	lsl r3, r2
	add r1, #0x84
	asr r0, r4, #0x3
	ldrb r7, [r1, r0]
	mvn r3, r3
	lsl r6, r2
	and r3, r7
	strb r3, [r1, r0]
	ldrb r3, [r1, r0]
	add r2, r3, #0x0
	orr r2, r6
	strb r2, [r1, r0]
	b _02024AC0
_02024A70:
	add r0, r5, r0
	add r0, #0x84
	ldrb r0, [r0, #0x0]
	tst r0, r1
	bne _02024A7C
	mov r2, #0x0
_02024A7C:
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	cmp r0, r6
	beq _02024AC0
	lsl r0, r6, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x2
	bls _02024A90
	bl ErrorHandling
_02024A90:
	cmp r6, #0x2
	bne _02024A96
	mov r6, #0x0
_02024A96:
	cmp r6, #0x2
	blo _02024A9E
	bl ErrorHandling
_02024A9E:
	add r1, r5, #0x0
	mov r0, #0x7
	add r2, r4, #0x0
	and r2, r0
	mov r3, #0x1
	lsl r3, r2
	add r1, #0xc4
	asr r0, r4, #0x3
	ldrb r7, [r1, r0]
	mvn r3, r3
	lsl r6, r2
	and r3, r7
	strb r3, [r1, r0]
	ldrb r3, [r1, r0]
	add r2, r3, #0x0
	orr r2, r6
	strb r2, [r1, r0]
_02024AC0:
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_020241B8
	mov r1, #0x7
	add r5, #0x44
	asr r0, r4, #0x3
	ldrb r3, [r5, r0]
	mov r2, #0x1
	and r1, r4
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strb r1, [r5, r0]
_02024ADE:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02024AE4: .word 0xBEEFCAFE
_02024AE8: .word 0x000001ED
_02024AEC: .word 0x00000147

	thumb_func_start FUN_02024AF0
FUN_02024AF0: ; 0x02024AF0
	push {r4-r7, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	str r1, [sp, #0x0]
	add r0, r1, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp, #0x0]
	mov r1, #0xc
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x8]
	mov r1, #0x0
	ldr r0, [sp, #0x0]
	add r2, r1, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	bl FUN_020689E0
	add r7, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024C78 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024B32
	bl ErrorHandling
_02024B32:
	cmp r6, #0x0
	beq _02024B3C
	ldr r0, _02024C7C ; =0x000001ED
	cmp r6, r0
	bls _02024B44
_02024B3C:
	bl ErrorHandling
	mov r0, #0x1
	b _02024B46
_02024B44:
	mov r0, #0x0
_02024B46:
	cmp r0, #0x0
	beq _02024B4C
	b _02024C72
_02024B4C:
	sub r0, r6, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	mov r0, #0x1
	mov r1, #0x7
	and r1, r5
	add r2, r0, #0x0
	asr r3, r5, #0x3
	lsl r2, r1
	add r1, r4, r3
	add r1, #0x44
	ldrb r1, [r1, #0x0]
	tst r1, r2
	bne _02024BEA
	ldr r1, _02024C80 ; =0x00000147
	cmp r6, r1
	bne _02024B74
	ldr r0, [sp, #0x4]
	sub r1, #0x43
	str r0, [r4, r1]
_02024B74:
	lsl r0, r7, #0x18
	lsr r7, r0, #0x18
	cmp r7, #0x2
	bls _02024B80
	bl ErrorHandling
_02024B80:
	cmp r7, #0x2
	bne _02024B86
	mov r7, #0x0
_02024B86:
	cmp r7, #0x2
	blo _02024B8E
	bl ErrorHandling
_02024B8E:
	mov r0, #0x7
	and r0, r5
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	add r0, #0xc4
	asr r3, r5, #0x3
	ldrb r1, [r0, r3]
	mov r2, #0x1
	str r1, [sp, #0xc]
	ldr r1, [sp, #0x10]
	lsl r2, r1
	ldr r1, [sp, #0xc]
	mvn r2, r2
	and r1, r2
	strb r1, [r0, r3]
	ldrb r1, [r0, r3]
	add r2, r7, #0x0
	mov r12, r1
	ldr r1, [sp, #0x10]
	lsl r2, r1
	mov r1, r12
	orr r1, r2
	strb r1, [r0, r3]
	cmp r7, #0x2
	blo _02024BC4
	bl ErrorHandling
_02024BC4:
	add r1, r4, #0x0
	mov r0, #0x7
	add r2, r5, #0x0
	and r2, r0
	mov r3, #0x1
	lsl r3, r2
	add r1, #0x84
	asr r0, r5, #0x3
	ldrb r5, [r1, r0]
	mvn r3, r3
	and r3, r5
	strb r3, [r1, r0]
	add r5, r7, #0x0
	ldrb r3, [r1, r0]
	lsl r5, r2
	add r2, r3, #0x0
	orr r2, r5
	strb r2, [r1, r0]
	b _02024C3C
_02024BEA:
	add r1, r4, r3
	add r1, #0x84
	ldrb r1, [r1, #0x0]
	tst r1, r2
	bne _02024BF6
	mov r0, #0x0
_02024BF6:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, r7
	beq _02024C3C
	lsl r0, r7, #0x18
	lsr r7, r0, #0x18
	cmp r7, #0x2
	bls _02024C0A
	bl ErrorHandling
_02024C0A:
	cmp r7, #0x2
	bne _02024C10
	mov r7, #0x0
_02024C10:
	cmp r7, #0x2
	blo _02024C18
	bl ErrorHandling
_02024C18:
	add r1, r4, #0x0
	mov r0, #0x7
	add r2, r5, #0x0
	and r2, r0
	mov r3, #0x1
	lsl r3, r2
	add r1, #0xc4
	asr r0, r5, #0x3
	ldrb r5, [r1, r0]
	mvn r3, r3
	and r3, r5
	strb r3, [r1, r0]
	add r5, r7, #0x0
	ldrb r3, [r1, r0]
	lsl r5, r2
	add r2, r3, #0x0
	orr r2, r5
	strb r2, [r1, r0]
_02024C3C:
	ldr r2, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020241B8
	ldr r2, [sp, #0x8]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_02024294
	sub r0, r6, #0x1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r1, r4, #0x4
	asr r0, r6, #0x3
	mov r2, #0x7
	ldrb r5, [r1, r0]
	mov r3, #0x1
	and r2, r6
	lsl r3, r2
	add r2, r5, #0x0
	orr r2, r3
	add r4, #0x44
	strb r2, [r1, r0]
	ldrb r1, [r4, r0]
	orr r1, r3
	strb r1, [r4, r0]
_02024C72:
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02024C78: .word 0xBEEFCAFE
_02024C7C: .word 0x000001ED
_02024C80: .word 0x00000147

	thumb_func_start FUN_02024C84
FUN_02024C84: ; 0x02024C84
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024C9C ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024C94
	bl ErrorHandling
_02024C94:
	ldr r0, _02024CA0 ; =0x00000139
	mov r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
	.balign 4
_02024C9C: .word 0xBEEFCAFE
_02024CA0: .word 0x00000139

	thumb_func_start FUN_02024CA4
FUN_02024CA4: ; 0x02024CA4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024CBC ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024CB4
	bl ErrorHandling
_02024CB4:
	ldr r0, _02024CC0 ; =0x00000139
	ldrb r0, [r4, r0]
	pop {r4, pc}
	nop
_02024CBC: .word 0xBEEFCAFE
_02024CC0: .word 0x00000139

	thumb_func_start FUN_02024CC4
FUN_02024CC4: ; 0x02024CC4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024CDC ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024CD4
	bl ErrorHandling
_02024CD4:
	mov r0, #0x4a
	lsl r0, r0, #0x2
	ldrb r0, [r4, r0]
	pop {r4, pc}
	.balign 4
_02024CDC: .word 0xBEEFCAFE

	thumb_func_start FUN_02024CE0
FUN_02024CE0: ; 0x02024CE0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024CFC ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024CF0
	bl ErrorHandling
_02024CF0:
	mov r0, #0x4a
	mov r1, #0x1
	lsl r0, r0, #0x2
	strb r1, [r4, r0]
	pop {r4, pc}
	nop
_02024CFC: .word 0xBEEFCAFE

	thumb_func_start FUN_02024D00
FUN_02024D00: ; 0x02024D00
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r6, #0x8
	blo _02024D10
	bl ErrorHandling
_02024D10:
	ldr r1, [r4, #0x0]
	ldr r0, _02024D44 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024D1C
	bl ErrorHandling
_02024D1C:
	add r0, r5, #0x0
	bl FUN_02087A50
	add r5, r0, #0x0
	cmp r5, #0xe
	bne _02024D2C
	mov r0, #0x0
	pop {r4-r6, pc}
_02024D2C:
	add r0, r6, #0x0
	bl FUN_02087A1C
	mov r1, #0x1
	add r2, r1, #0x0
	lsl r2, r0
	ldr r0, _02024D48 ; =0x00000129
	add r1, r4, r5
	ldrb r0, [r1, r0]
	and r0, r2
	pop {r4-r6, pc}
	nop
_02024D44: .word 0xBEEFCAFE
_02024D48: .word 0x00000129

	thumb_func_start FUN_02024D4C
FUN_02024D4C: ; 0x02024D4C
	ldr r1, _02024D54 ; =0x00000137
	mov r2, #0x1
	strb r2, [r0, r1]
	bx lr
	.balign 4
_02024D54: .word 0x00000137

	thumb_func_start FUN_02024D58
FUN_02024D58: ; 0x02024D58
	ldr r1, _02024D60 ; =0x00000137
	ldrb r0, [r0, r1]
	bx lr
	nop
_02024D60: .word 0x00000137

	thumb_func_start FUN_02024D64
FUN_02024D64: ; 0x02024D64
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024D7C ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024D74
	bl ErrorHandling
_02024D74:
	mov r0, #0x4e
	lsl r0, r0, #0x2
	ldrb r0, [r4, r0]
	pop {r4, pc}
	.balign 4
_02024D7C: .word 0xBEEFCAFE

	thumb_func_start FUN_02024D80
FUN_02024D80: ; 0x02024D80
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024D9C ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024D90
	bl ErrorHandling
_02024D90:
	mov r0, #0x4e
	mov r1, #0x1
	lsl r0, r0, #0x2
	strb r1, [r4, r0]
	pop {r4, pc}
	nop
_02024D9C: .word 0xBEEFCAFE

	thumb_func_start FUN_02024DA0
FUN_02024DA0: ; 0x02024DA0
	ldr r3, _02024DA8 ; =FUN_02022610
	mov r1, #0x7
	bx r3
	nop
_02024DA8: .word FUN_02022610

	thumb_func_start FUN_02024DAC
FUN_02024DAC: ; 0x02024DAC
	push {r3-r5, lr}
	add r4, r2, #0x0
	ldr r2, _02024E60 ; =0x0000019D
	add r5, r0, #0x0
	cmp r1, r2
	bgt _02024DD6
	sub r3, r2, #0x1
	cmp r1, r3
	blt _02024DC6
	beq _02024E24
	cmp r1, r2
	beq _02024E36
	b _02024E5A
_02024DC6:
	cmp r1, #0xc9
	bgt _02024DCE
	beq _02024DEE
	b _02024E5A
_02024DCE:
	sub r2, #0x1b
	cmp r1, r2
	beq _02024E48
	b _02024E5A
_02024DD6:
	add r3, r2, #0x0
	add r3, #0x9
	cmp r1, r3
	bgt _02024DE6
	add r2, #0x9
	cmp r1, r2
	beq _02024E00
	b _02024E5A
_02024DE6:
	add r2, #0xa
	cmp r1, r2
	beq _02024E12
	b _02024E5A
_02024DEE:
	bl FUN_0202471C
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020246DC
	pop {r3-r5, pc}
_02024E00:
	bl FUN_020247A4
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02024748
	pop {r3-r5, pc}
_02024E12:
	bl FUN_02024828
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020247C8
	pop {r3-r5, pc}
_02024E24:
	bl FUN_0202489C
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202484C
	pop {r3-r5, pc}
_02024E36:
	bl FUN_0202490C
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020248BC
	pop {r3-r5, pc}
_02024E48:
	bl FUN_02024970
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02024930
	pop {r3-r5, pc}
_02024E5A:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_02024E60: .word 0x0000019D

	thumb_func_start FUN_02024E64
FUN_02024E64: ; 0x02024E64
	ldr r0, _02024E68 ; =0x0000074C
	bx lr
	.balign 4
_02024E68: .word 0x0000074C

	thumb_func_start FUN_02024E6C
FUN_02024E6C: ; 0x02024E6C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r2, _02024EA4 ; =0x0000074C
	mov r0, #0x0
	add r1, r4, #0x0
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	bl FUN_020250A4
	mov r0, #0x7
	lsl r0, r0, #0x8
	add r0, r4, r0
	bl FUN_02025484
	ldr r1, _02024EA8 ; =0x00000724
	ldr r0, _02024EAC ; =0x0000FFFF
	add r1, r4, r1
	mov r2, #0x8
	bl MIi_CpuClear16
	ldr r1, _02024EB0 ; =0x00000734
	ldr r0, _02024EAC ; =0x0000FFFF
	add r1, r4, r1
	mov r2, #0xb
	bl MIi_CpuClear16
	pop {r4, pc}
	.balign 4
_02024EA4: .word 0x0000074C
_02024EA8: .word 0x00000724
_02024EAC: .word 0x0000FFFF
_02024EB0: .word 0x00000734

	thumb_func_start FUN_02024EB4
FUN_02024EB4: ; 0x02024EB4
	ldr r3, _02024EBC ; =FUN_02022610
	mov r1, #0xa
	bx r3
	nop
_02024EBC: .word FUN_02022610

	thumb_func_start FUN_02024EC0
FUN_02024EC0: ; 0x02024EC0
	ldr r3, _02024EC8 ; =FUN_02022634
	mov r1, #0xa
	bx r3
	nop
_02024EC8: .word FUN_02022634

	thumb_func_start FUN_02024ECC
FUN_02024ECC: ; 0x02024ECC
	ldr r3, _02024ED4 ; =FUN_02022610
	mov r1, #0xa
	bx r3
	nop
_02024ED4: .word FUN_02022610

	thumb_func_start FUN_02024ED8
FUN_02024ED8: ; 0x02024ED8
	push {r3, lr}
	mov r1, #0xa
	bl FUN_02022610
	mov r1, #0x7
	lsl r1, r1, #0x8
	add r0, r0, r1
	pop {r3, pc}

	thumb_func_start FUN_02024EE8
FUN_02024EE8: ; 0x02024EE8
	ldr r1, _02024EF0 ; =0x00000724
	add r0, r0, r1
	bx lr
	nop
_02024EF0: .word 0x00000724

	thumb_func_start FUN_02024EF4
FUN_02024EF4: ; 0x02024EF4
	add r2, r0, #0x0
	add r0, r1, #0x0
	ldr r1, _02024F04 ; =0x00000724
	ldr r3, _02024F08 ; =FUN_02021EF0
	add r1, r2, r1
	mov r2, #0x8
	bx r3
	nop
_02024F04: .word 0x00000724
_02024F08: .word FUN_02021EF0

	thumb_func_start FUN_02024F0C
FUN_02024F0C: ; 0x02024F0C
	ldr r1, _02024F14 ; =0x00000734
	add r0, r0, r1
	bx lr
	nop
_02024F14: .word 0x00000734

	thumb_func_start FUN_02024F18
FUN_02024F18: ; 0x02024F18
	add r2, r0, #0x0
	add r0, r1, #0x0
	ldr r1, _02024F28 ; =0x00000734
	ldr r3, _02024F2C ; =FUN_02021EF0
	add r1, r2, r1
	mov r2, #0xb
	bx r3
	nop
_02024F28: .word 0x00000734
_02024F2C: .word FUN_02021EF0

	thumb_func_start FUN_02024F30
FUN_02024F30: ; 0x02024F30
	push {r4, lr}
	mov r1, #0x2
	bl FUN_02016998
	add r4, r0, #0x0
	bl FUN_02024F50
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02024F44
FUN_02024F44: ; 0x02024F44
	ldr r3, _02024F4C ; =MI_CpuCopy8
	mov r2, #0x2
	bx r3
	nop
_02024F4C: .word MI_CpuCopy8

	thumb_func_start FUN_02024F50
FUN_02024F50: ; 0x02024F50
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x2
	bl MI_CpuFill8
	ldrh r1, [r4, #0x0]
	mov r0, #0xf
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strh r0, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	mov r0, #0x30
	bic r1, r0
	strh r1, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	mov r0, #0x40
	bic r1, r0
	strh r1, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	mov r0, #0x80
	bic r1, r0
	strh r1, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r0, _02024F94 ; =0xFFFFFCFF
	and r0, r1
	strh r0, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r0, _02024F98 ; =0xFFFF83FF
	and r0, r1
	strh r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02024F94: .word 0xFFFFFCFF
_02024F98: .word 0xFFFF83FF

	thumb_func_start FUN_02024F9C
FUN_02024F9C: ; 0x02024F9C
	push {r3, lr}
	cmp r0, #0x0
	beq _02024FAC
	bl LoadPlayerDataAddress
	bl FUN_02025064
	add r1, r0, #0x0
_02024FAC:
	cmp r1, #0x0
	beq _02024FCA
	cmp r1, #0x1
	beq _02024FBA
	cmp r1, #0x2
	beq _02024FC2
	b _02024FCA
_02024FBA:
	ldr r0, _02024FD4 ; =0x021C48B8
	mov r1, #0x1
	str r1, [r0, #0x34]
	pop {r3, pc}
_02024FC2:
	ldr r0, _02024FD4 ; =0x021C48B8
	mov r1, #0x3
	str r1, [r0, #0x34]
	pop {r3, pc}
_02024FCA:
	ldr r0, _02024FD4 ; =0x021C48B8
	mov r1, #0x0
	str r1, [r0, #0x34]
	pop {r3, pc}
	nop
_02024FD4: .word 0x021C48B8

	thumb_func_start FUN_02024FD8
FUN_02024FD8: ; 0x02024FD8
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bx lr

	thumb_func_start FUN_02024FE0
FUN_02024FE0: ; 0x02024FE0
	ldrh r3, [r0, #0x0]
	mov r2, #0xf
	lsl r1, r1, #0x10
	bic r3, r2
	lsr r2, r1, #0x10
	mov r1, #0xf
	and r1, r2
	orr r1, r3
	strh r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02024FF4
FUN_02024FF4: ; 0x02024FF4
	push {r3, lr}
	bl FUN_02024FD8
	cmp r0, #0x0
	bne _02025002
	mov r0, #0x8
	pop {r3, pc}
_02025002:
	cmp r0, #0x1
	bne _0202500A
	mov r0, #0x4
	pop {r3, pc}
_0202500A:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02025010
FUN_02025010: ; 0x02025010
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1e
	bx lr

	thumb_func_start FUN_02025018
FUN_02025018: ; 0x02025018
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1e
	ldrh r3, [r0, #0x0]
	mov r2, #0x30
	lsr r1, r1, #0x1a
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202502C
FUN_0202502C: ; 0x0202502C
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_02025034
FUN_02025034: ; 0x02025034
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1f
	ldrh r3, [r0, #0x0]
	mov r2, #0x80
	lsr r1, r1, #0x18
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02025048
FUN_02025048: ; 0x02025048
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_02025050
FUN_02025050: ; 0x02025050
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1f
	ldrh r3, [r0, #0x0]
	mov r2, #0x40
	lsr r1, r1, #0x19
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02025064
FUN_02025064: ; 0x02025064
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1e
	bx lr

	thumb_func_start FUN_0202506C
FUN_0202506C: ; 0x0202506C
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1e
	ldrh r3, [r0, #0x0]
	ldr r2, _02025080 ; =0xFFFFFCFF
	lsr r1, r1, #0x16
	and r2, r3
	orr r1, r2
	strh r1, [r0, #0x0]
	bx lr
	.balign 4
_02025080: .word 0xFFFFFCFF

	thumb_func_start FUN_02025084
FUN_02025084: ; 0x02025084
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1b
	bx lr

	thumb_func_start FUN_0202508C
FUN_0202508C: ; 0x0202508C
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1b
	ldrh r3, [r0, #0x0]
	ldr r2, _020250A0 ; =0xFFFF83FF
	lsr r1, r1, #0x11
	and r2, r3
	orr r1, r2
	strh r1, [r0, #0x0]
	bx lr
	.balign 4
_020250A0: .word 0xFFFF83FF

	thumb_func_start FUN_020250A4
FUN_020250A4: ; 0x020250A4
	push {r4, lr}
	mov r2, #0x7
	mov r1, #0x0
	lsl r2, r2, #0x8
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r1, #0x0
	add r0, r1, #0x0
_020250B6:
	strb r0, [r4, #0x1]
	strb r0, [r4, #0x0]
	add r1, r1, #0x1
	add r4, #0xe
	cmp r1, #0x80
	blt _020250B6
	pop {r4, pc}

	thumb_func_start FUN_020250C4
FUN_020250C4: ; 0x020250C4
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, r1, #0x0
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	bl FUN_02025128
	mov r4, #0x0
	str r0, [sp, #0x8]
	add r6, r4, #0x0
	b _02025112
_020250DC:
	add r0, r5, #0x0
	bl FUN_02025184
	ldr r0, [sp, #0x0]
	lsl r1, r6, #0x1
	add r7, r0, r1
	ldrh r0, [r0, r1]
	sub r0, #0x94
	strb r0, [r5, #0x0]
	mov r0, #0x5
	strb r0, [r5, #0x1]
	ldrb r1, [r5, #0x0]
	ldrb r2, [r5, #0xc]
	ldr r0, [sp, #0x8]
	bl FUN_020251B0
	lsl r0, r0, #0x2
	strh r0, [r5, #0x2]
	ldrh r0, [r7, #0x2]
	add r6, r6, #0x2
	add r4, r4, #0x1
	strh r0, [r5, #0x8]
	mov r0, #0x64
	strb r0, [r5, #0xa]
	mov r0, #0x3
	strb r0, [r5, #0xb]
	add r5, #0xe
_02025112:
	cmp r4, #0x80
	blt _020250DC
	ldr r0, [sp, #0x4]
	cmp r4, r0
	blt _020250DC
	ldr r0, [sp, #0x8]
	bl FUN_02016A18
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02025128
FUN_02025128: ; 0x02025128
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	bl FUN_02085258
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	mov r1, #0xc0
	bl FUN_02016998
	str r0, [sp, #0x4]
	mov r6, #0x0
	add r5, r0, #0x0
_02025142:
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02085264
	add r4, r0, #0x0
	mov r1, #0x3
	bl FUN_02085290
	strb r0, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_02085290
	strb r0, [r5, #0x1]
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02085290
	strb r0, [r5, #0x2]
	add r0, r4, #0x0
	bl FUN_02016A18
	add r6, r6, #0x1
	add r5, r5, #0x3
	cmp r6, #0x40
	blt _02025142
	ldr r0, [sp, #0x0]
	bl FUN_0208526C
	ldr r0, [sp, #0x4]
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02025184
FUN_02025184: ; 0x02025184
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strh r1, [r0, #0x2]
	strh r1, [r0, #0x4]
	strb r1, [r0, #0x6]
	strh r1, [r0, #0x8]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	strb r1, [r0, #0xc]
	strb r1, [r0, #0xd]
	bx lr

	thumb_func_start FUN_0202519C
FUN_0202519C: ; 0x0202519C
	ldrb r2, [r0, #0xb]
	ldrb r0, [r0, #0x0]
	sub r3, r0, #0x1
	lsl r0, r3, #0x1
	add r0, r3, r0
	add r0, r1, r0
	ldrb r0, [r0, #0x2]
	mul r0, r2
	bx lr
	.balign 4

	thumb_func_start FUN_020251B0
FUN_020251B0: ; 0x020251B0
	sub r3, r1, #0x1
	lsl r1, r3, #0x1
	add r1, r3, r1
	ldrb r1, [r0, r1]
	mov r0, #0x3c
	mul r0, r1
	cmp r2, #0x1
	bne _020251CE
	lsl r1, r0, #0x1
	add r1, r0, r1
	asr r0, r1, #0x1
	lsr r0, r0, #0x1e
	add r0, r1, r0
	asr r0, r0, #0x2
	bx lr
_020251CE:
	cmp r2, #0x2
	bne _020251DA
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r1, r1, #0x1
	add r0, r0, r1
_020251DA:
	bx lr

	thumb_func_start FUN_020251DC
FUN_020251DC: ; 0x020251DC
	sub r3, r1, #0x1
	lsl r1, r3, #0x1
	add r1, r3, r1
	add r0, r0, r1
	ldrb r0, [r0, #0x1]
	cmp r2, #0x2
	bne _020251F2
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r0, r1, #0x1
	bx lr
_020251F2:
	cmp r2, #0x1
	bne _020251FE
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r1, r1, #0x1
	add r0, r0, r1
_020251FE:
	bx lr

	thumb_func_start FUN_02025200
FUN_02025200: ; 0x02025200
	ldrb r0, [r0, #0xc]
	cmp r0, #0x3
	bne _0202520A
	mov r0, #0x6
	bx lr
_0202520A:
	mov r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02025210
FUN_02025210: ; 0x02025210
	ldrb r0, [r0, #0xc]
	cmp r0, #0x4
	bne _0202521A
	mov r0, #0xf
	bx lr
_0202521A:
	mov r0, #0xa
	bx lr
	.balign 4

	thumb_func_start FUN_02025220
FUN_02025220: ; 0x02025220
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02025200
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02025210
	add r1, r4, #0x3
	mul r0, r1
	add r0, r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_02025238
FUN_02025238: ; 0x02025238
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0x1]
	bx lr
	.balign 4

	thumb_func_start FUN_02025244
FUN_02025244: ; 0x02025244
	mov r2, #0xe
	mul r2, r1
	ldrb r0, [r0, r2]
	bx lr

	thumb_func_start FUN_0202524C
FUN_0202524C: ; 0x0202524C
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0xa]
	cmp r0, #0x0
	bne _0202525C
	mov r0, #0x0
	bx lr
_0202525C:
	cmp r0, #0x32
	bgt _02025264
	mov r0, #0x1
	bx lr
_02025264:
	mov r0, #0x2
	bx lr

	thumb_func_start FUN_02025268
FUN_02025268: ; 0x02025268
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0xb]
	bx lr
	.balign 4

	thumb_func_start FUN_02025274
FUN_02025274: ; 0x02025274
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0xe
	mul r4, r0
	strb r3, [r5, r4]
	mov r0, #0x1
	add r6, r5, r4
	strb r0, [r6, #0x1]
	add r0, r2, #0x0
	ldrb r2, [r6, #0xc]
	add r1, r3, #0x0
	bl FUN_020251B0
	add r1, r6, #0x0
	strh r0, [r1, #0x2]
	mov r0, #0x0
	strh r0, [r1, #0x4]
	strb r0, [r1, #0x6]
	strh r0, [r1, #0x8]
	mov r0, #0x64
	strb r0, [r1, #0xa]
	mov r0, #0x5
	strb r0, [r1, #0xb]
	mov r0, #0x1
	strb r0, [r1, #0xd]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020252AC
FUN_020252AC: ; 0x020252AC
	mov r2, #0xe
	mul r2, r1
	mov r3, #0x64
	add r0, r0, r2
	strb r3, [r0, #0xa]
	bx lr

	thumb_func_start FUN_020252B8
FUN_020252B8: ; 0x020252B8
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0xd]
	bx lr
	.balign 4

	thumb_func_start FUN_020252C4
FUN_020252C4: ; 0x020252C4
	mov r3, #0xe
	mul r3, r1
	add r0, r0, r3
	strb r2, [r0, #0xd]
	bx lr
	.balign 4

	thumb_func_start FUN_020252D0
FUN_020252D0: ; 0x020252D0
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0xc]
	bx lr
	.balign 4

	thumb_func_start FUN_020252DC
FUN_020252DC: ; 0x020252DC
	mov r3, #0xe
	mul r3, r1
	add r0, r0, r3
	strb r2, [r0, #0xc]
	bx lr
	.balign 4

	thumb_func_start FUN_020252E8
FUN_020252E8: ; 0x020252E8
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrh r0, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start FUN_020252F4
FUN_020252F4: ; 0x020252F4
	push {r4, lr}
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrh r4, [r0, #0x8]
	bl FUN_02025184
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02025308
FUN_02025308: ; 0x02025308
	push {r4, lr}
	add r4, r0, #0x0
	ldrb r2, [r4, #0x1]
	cmp r2, #0x5
	bhi _02025370
	add r3, r2, r2
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0202531E: ; jump table (using 16-bit offset)
	.short _0202532A - _0202531E - 2; case 0
	.short _02025330 - _0202531E - 2; case 1
	.short _02025330 - _0202531E - 2; case 2
	.short _02025330 - _0202531E - 2; case 3
	.short _02025336 - _0202531E - 2; case 4
	.short _0202534E - _0202531E - 2; case 5
_0202532A:
	bl ErrorHandling
	pop {r4, pc}
_02025330:
	add r0, r2, #0x1
	strb r0, [r4, #0x1]
	pop {r4, pc}
_02025336:
	bl FUN_0202519C
	strh r0, [r4, #0x8]
	ldrh r0, [r4, #0x8]
	cmp r0, #0x2
	bhs _02025346
	mov r0, #0x2
	strh r0, [r4, #0x8]
_02025346:
	ldrb r0, [r4, #0x1]
	add r0, r0, #0x1
	strb r0, [r4, #0x1]
	pop {r4, pc}
_0202534E:
	mov r1, #0x0
	strh r1, [r4, #0x8]
	mov r1, #0x2
	strb r1, [r4, #0x1]
	mov r1, #0x5
	strb r1, [r4, #0xb]
	ldrb r1, [r4, #0x6]
	add r1, r1, #0x1
	strb r1, [r4, #0x6]
	bl FUN_02025210
	ldrb r1, [r4, #0x6]
	cmp r1, r0
	bne _02025370
	add r0, r4, #0x0
	bl FUN_02025184
_02025370:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02025374
FUN_02025374: ; 0x02025374
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0x1]
	add r7, r2, #0x0
	cmp r0, #0x5
	beq _020253DE
	add r0, r1, #0x0
	ldrb r1, [r5, #0x0]
	ldrb r2, [r5, #0xc]
	bl FUN_020251DC
	add r6, r0, #0x0
	ldrh r0, [r5, #0x4]
	mov r1, #0x3c
	str r0, [sp, #0x0]
	add r0, r7, r0
	bl _s32_div_f
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r1, #0x3c
	add r0, r7, r0
	bl _s32_div_f
	strh r1, [r5, #0x4]
	cmp r4, #0x0
	beq _020253DE
	ldrb r1, [r5, #0xa]
	add r0, r6, #0x0
	mul r0, r4
	cmp r1, r0
	blt _020253BA
	sub r0, r1, r0
	strb r0, [r5, #0xa]
	pop {r3-r7, pc}
_020253BA:
	cmp r1, #0x0
	beq _020253CE
	sub r0, r6, #0x1
	add r0, r1, r0
	add r1, r6, #0x0
	bl _s32_div_f
	sub r4, r4, r0
	mov r0, #0x0
	strb r0, [r5, #0xa]
_020253CE:
	ldrb r0, [r5, #0xb]
	cmp r0, r4
	ble _020253DA
	sub r0, r0, r4
	strb r0, [r5, #0xb]
	pop {r3-r7, pc}
_020253DA:
	mov r0, #0x0
	strb r0, [r5, #0xb]
_020253DE:
	pop {r3-r7, pc}

	thumb_func_start FUN_020253E0
FUN_020253E0: ; 0x020253E0
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r0, [sp, #0x0]
_020253EC:
	ldrb r1, [r5, #0x0]
	cmp r1, #0x0
	beq _02025474
	ldrb r0, [r5, #0x1]
	cmp r0, #0x0
	beq _02025474
	ldrb r0, [r5, #0xd]
	cmp r0, #0x0
	beq _02025474
	ldrb r2, [r5, #0xc]
	add r0, r6, #0x0
	bl FUN_020251B0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02025220
	mul r0, r4
	cmp r7, r0
	blt _0202541C
	add r0, r5, #0x0
	bl FUN_02025184
	b _02025474
_0202541C:
	add r4, r7, #0x0
	b _0202546A
_02025420:
	ldrh r2, [r5, #0x2]
	cmp r2, r4
	ble _02025438
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02025374
	ldrh r0, [r5, #0x2]
	sub r0, r0, r4
	strh r0, [r5, #0x2]
	b _02025474
_02025438:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02025374
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02025308
	ldrh r0, [r5, #0x2]
	ldrb r1, [r5, #0x0]
	ldrb r2, [r5, #0xc]
	sub r4, r4, r0
	add r0, r6, #0x0
	bl FUN_020251B0
	strh r0, [r5, #0x2]
	ldrb r0, [r5, #0x1]
	cmp r0, #0x5
	bne _0202546A
	add r0, r5, #0x0
	bl FUN_02025200
	ldrh r1, [r5, #0x2]
	mul r0, r1
	strh r0, [r5, #0x2]
_0202546A:
	ldrb r0, [r5, #0x1]
	cmp r0, #0x0
	beq _02025474
	cmp r4, #0x0
	bne _02025420
_02025474:
	ldr r0, [sp, #0x0]
	add r5, #0xe
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	cmp r0, #0x80
	blt _020253EC
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02025484
FUN_02025484: ; 0x02025484
	ldr r3, _0202548C ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x24
	bx r3
	.balign 4
_0202548C: .word MI_CpuFill8

	thumb_func_start FUN_02025490
FUN_02025490: ; 0x02025490
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02025484
	str r4, [r5, #0x0]
	add r0, r5, #0x4
	pop {r3-r5, pc}

	thumb_func_start FUN_020254A0
FUN_020254A0: ; 0x020254A0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, r1
	beq _020254AE
	bl ErrorHandling
_020254AE:
	add r0, r4, #0x4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020254B4
FUN_020254B4: ; 0x020254B4
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_020254B8
FUN_020254B8: ; 0x020254B8
	mov r0, #0x22
	lsl r0, r0, #0x6
	bx lr
	.balign 4

	thumb_func_start FUN_020254C0
FUN_020254C0: ; 0x020254C0
	ldr r3, _020254C8 ; =FUN_02022610
	mov r1, #0x9
	bx r3
	nop
_020254C8: .word FUN_02022610

	thumb_func_start FUN_020254CC
FUN_020254CC: ; 0x020254CC
	push {r3-r7, lr}
	mov r4, #0x0
	ldr r6, _020254EC ; =0x0000FFFF
	add r5, r0, #0x0
	add r7, r4, #0x0
_020254D6:
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x88
	bl Call_FillMemWithValue
	strh r6, [r5, #0x0]
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x10
	blt _020254D6
	pop {r3-r7, pc}
	.balign 4
_020254EC: .word 0x0000FFFF

	thumb_func_start FUN_020254F0
FUN_020254F0: ; 0x020254F0
	mov r2, #0x88
	mul r2, r1
	add r0, r0, r2
	bx lr

	thumb_func_start FUN_020254F8
FUN_020254F8: ; 0x020254F8
	add r0, r0, r1
	add r0, #0x68
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02025500
FUN_02025500: ; 0x02025500
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl StringNotEqual
	cmp r0, #0x0
	bne _0202551A
	ldr r1, [r5, #0x10]
	ldr r0, [r4, #0x10]
	cmp r1, r0
	bne _0202551A
	mov r0, #0x1
	pop {r3-r5, pc}
_0202551A:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02025520
FUN_02025520: ; 0x02025520
	push {r4-r7, lr}
	sub sp, #0x2c
	str r1, [sp, #0x4]
	mov r1, #0x22
	str r0, [sp, #0x0]
	add r0, r3, #0x0
	lsl r1, r1, #0x6
	str r2, [sp, #0x8]
	bl FUN_02016998
	str r0, [sp, #0x10]
	bl FUN_020254CC
	mov r0, #0x0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	ble _02025578
	ldr r7, [sp, #0x4]
	add r6, sp, #0x18
_02025548:
	mov r0, #0x0
	mvn r0, r0
	ldr r5, [sp, #0x0]
	str r0, [r6, #0x0]
	mov r4, #0x0
_02025552:
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02025500
	cmp r0, #0x0
	beq _02025560
	str r4, [r6, #0x0]
_02025560:
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x10
	blt _02025552
	ldr r0, [sp, #0x14]
	add r6, r6, #0x4
	add r1, r0, #0x1
	ldr r0, [sp, #0x8]
	add r7, #0x88
	str r1, [sp, #0x14]
	cmp r1, r0
	blt _02025548
_02025578:
	ldr r0, [sp, #0x8]
	mov r4, #0x0
	str r4, [sp, #0xc]
	cmp r0, #0x0
	ble _020255BE
	ldr r5, [sp, #0x10]
	add r6, sp, #0x18
_02025586:
	ldr r3, [sp, #0x4]
	add r7, r5, #0x0
	mov r2, #0x11
_0202558C:
	ldmia r3!, {r0-r1}
	stmia r7!, {r0-r1}
	sub r2, r2, #0x1
	bne _0202558C
	ldr r1, [r6, #0x0]
	cmp r1, #0x0
	blt _020255A6
	add r2, r1, #0x0
	mov r0, #0x88
	mul r2, r0
	ldr r1, _02025610 ; =0x0000FFFF
	ldr r0, [sp, #0x0]
	strh r1, [r0, r2]
_020255A6:
	ldr r0, [sp, #0x4]
	add r5, #0x88
	add r0, #0x88
	str r0, [sp, #0x4]
	ldr r0, [sp, #0xc]
	add r4, r4, #0x1
	add r1, r0, #0x1
	ldr r0, [sp, #0x8]
	add r6, r6, #0x4
	str r1, [sp, #0xc]
	cmp r1, r0
	blt _02025586
_020255BE:
	mov r0, #0x0
	mov r12, r0
	mov r0, #0x88
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, [sp, #0x10]
	ldr r3, [sp, #0x0]
	add r5, r0, r1
_020255CE:
	ldrh r1, [r3, #0x0]
	ldr r0, _02025610 ; =0x0000FFFF
	cmp r1, r0
	beq _020255EC
	add r6, r3, #0x0
	add r7, r5, #0x0
	mov r2, #0x11
_020255DC:
	ldmia r6!, {r0-r1}
	stmia r7!, {r0-r1}
	sub r2, r2, #0x1
	bne _020255DC
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x10
	bge _020255F8
_020255EC:
	mov r0, r12
	add r0, r0, #0x1
	add r3, #0x88
	mov r12, r0
	cmp r0, #0x10
	blt _020255CE
_020255F8:
	mov r2, #0x22
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x10]
	lsl r2, r2, #0x6
	bl memcpy
	ldr r0, [sp, #0x10]
	bl FUN_02016A18
	add sp, #0x2c
	pop {r4-r7, pc}
	nop
_02025610: .word 0x0000FFFF

	thumb_func_start FUN_02025614
FUN_02025614: ; 0x02025614
	push {r3-r6}
	mov r3, #0x0
	add r4, r0, #0x0
_0202561A:
	ldr r2, [r4, #0x10]
	cmp r1, r2
	bne _02025626
	mov r0, #0x1
	pop {r3-r6}
	bx lr
_02025626:
	add r3, r3, #0x1
	add r4, #0x88
	cmp r3, #0x10
	blt _0202561A
	mov r6, #0x0
	add r3, r6, #0x0
_02025632:
	add r4, r3, #0x0
	add r5, r0, #0x0
_02025636:
	ldr r2, [r5, #0x18]
	cmp r1, r2
	bne _02025642
	add r0, r6, #0x2
	pop {r3-r6}
	bx lr
_02025642:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x10
	blt _02025636
	add r6, r6, #0x1
	add r0, #0x88
	cmp r6, #0x10
	blt _02025632
	mov r0, #0x0
	pop {r3-r6}
	bx lr

	thumb_func_start FUN_02025658
FUN_02025658: ; 0x02025658
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [r4, #0x0]
	strb r0, [r4, #0x4]
	ldr r0, _020256A0 ; =0x020ECAC4
	mov r1, #0x8
	ldrb r0, [r0, #0x0]
	strb r0, [r4, #0x5]
	ldr r0, _020256A4 ; =0x020ECAC0
	ldrb r0, [r0, #0x0]
	strb r0, [r4, #0x6]
	mov r0, #0xff
	strb r0, [r4, #0x7]
	add r0, r4, #0x0
	add r0, #0x8
	bl StringFillEOS
	ldr r0, _020256A8 ; =0x0000FFFF
	mov r1, #0x0
	add r2, r4, #0x0
_02025682:
	add r1, r1, #0x1
	strh r0, [r2, #0x18]
	add r2, r2, #0x2
	cmp r1, #0x3
	blt _02025682
	mov r5, #0x0
	add r4, #0x20
_02025690:
	add r0, r4, #0x0
	bl FUN_02013724
	add r5, r5, #0x1
	add r4, #0x8
	cmp r5, #0x3
	blt _02025690
	pop {r3-r5, pc}
	.balign 4
_020256A0: .word 0x020ECAC4
_020256A4: .word 0x020ECAC0
_020256A8: .word 0x0000FFFF

	thumb_func_start FUN_020256AC
FUN_020256AC: ; 0x020256AC
	ldrb r0, [r0, #0x7]
	cmp r0, #0xb
	bhi _020256B6
	mov r0, #0x1
	bx lr
_020256B6:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_020256BC
FUN_020256BC: ; 0x020256BC
	push {r4, lr}
	mov r1, #0x38
	bl FUN_020169D8
	add r4, r0, #0x0
	bl FUN_02025658
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020256D0
FUN_020256D0: ; 0x020256D0
	ldr r3, _020256D8 ; =MI_CpuCopy8
	mov r2, #0x38
	bx r3
	nop
_020256D8: .word MI_CpuCopy8

	thumb_func_start FUN_020256DC
FUN_020256DC: ; 0x020256DC
	push {r4-r7, lr}
	sub sp, #0x14
	add r7, r3, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02025658
	add r0, r7, #0x0
	strb r6, [r5, #0x7]
	bl FUN_0206BB1C
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	bl FUN_020238F4
	add r6, r0, #0x0
	bl FUN_0202398C
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x8
	bl StringCopy
	add r0, r6, #0x0
	bl FUN_020239CC
	strb r0, [r5, #0x4]
	add r0, r6, #0x0
	bl FUN_020239BC
	str r0, [r5, #0x0]
	ldr r0, [sp, #0x0]
	mov r6, #0x0
	bl FUN_0206B9AC
	cmp r4, r0
	bge _020257AE
	add r5, #0x18
_0202572A:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r7, r0, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x8]
	add r0, r7, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0xc]
	add r0, r7, #0x0
	bl FUN_0206B6C8
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x8]
	bl FUN_0206B7BC
	lsl r3, r6, #0x1
	ldrh r1, [r5, r3]
	add r7, r0, #0x0
	ldr r0, _020257B4 ; =0xFFFFF000
	add r2, r1, #0x0
	and r2, r0
	ldr r0, [sp, #0x10]
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, _020257B8 ; =0x00000FFF
	and r0, r1
	orr r0, r2
	strh r0, [r5, r3]
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldrh r1, [r5, r3]
	ldr r0, _020257BC ; =0xFFFF0FFF
	and r0, r1
	lsl r1, r7, #0x1c
	lsr r1, r1, #0x10
	orr r0, r1
	strh r0, [r5, r3]
	cmp r6, #0x3
	bhs _020257AE
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x0]
	bl FUN_0206B9AC
	cmp r4, r0
	blt _0202572A
_020257AE:
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_020257B4: .word 0xFFFFF000
_020257B8: .word 0x00000FFF
_020257BC: .word 0xFFFF0FFF

	thumb_func_start FUN_020257C0
FUN_020257C0: ; 0x020257C0
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_020257C4
FUN_020257C4: ; 0x020257C4
	add r0, #0x8
	bx lr

	thumb_func_start FUN_020257C8
FUN_020257C8: ; 0x020257C8
	ldrb r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_020257CC
FUN_020257CC: ; 0x020257CC
	ldrb r0, [r0, #0x7]
	bx lr

	thumb_func_start FUN_020257D0
FUN_020257D0: ; 0x020257D0
	cmp r1, #0xc
	bhs _020257D6
	strb r1, [r0, #0x7]
_020257D6:
	bx lr

	thumb_func_start FUN_020257D8
FUN_020257D8: ; 0x020257D8
	ldrb r0, [r0, #0x5]
	bx lr

	thumb_func_start FUN_020257DC
FUN_020257DC: ; 0x020257DC
	ldrb r0, [r0, #0x6]
	bx lr

	thumb_func_start FUN_020257E0
FUN_020257E0: ; 0x020257E0
	cmp r1, #0x3
	bhs _02025810
	cmp r2, #0x0
	beq _020257F0
	cmp r2, #0x1
	beq _020257FC
	cmp r2, #0x2
	b _02025808
_020257F0:
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, #0x18]
	lsl r0, r0, #0x14
	lsr r0, r0, #0x14
	bx lr
_020257FC:
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, #0x18]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1c
	bx lr
_02025808:
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, #0x18]
	bx lr
_02025810:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02025814
FUN_02025814: ; 0x02025814
	cmp r1, #0x3
	bhs _02025820
	add r0, #0x20
	lsl r1, r1, #0x3
	add r0, r0, r1
	bx lr
_02025820:
	add r0, #0x20
	bx lr

	thumb_func_start FUN_02025824
FUN_02025824: ; 0x02025824
	push {r3, lr}
	cmp r2, #0x3
	bhs _02025834
	add r0, #0x20
	lsl r2, r2, #0x3
	add r0, r0, r2
	bl FUN_02013960
_02025834:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02025838
FUN_02025838: ; 0x02025838
	ldr r3, _02025840 ; =FUN_02022610
	mov r1, #0xf
	bx r3
	nop
_02025840: .word FUN_02022610

	thumb_func_start FUN_02025844
FUN_02025844: ; 0x02025844
	mov r0, #0x46
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_0202584C
FUN_0202584C: ; 0x0202584C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_02025852:
	add r0, r5, #0x0
	bl FUN_02025658
	add r4, r4, #0x1
	add r5, #0x38
	cmp r4, #0x14
	blt _02025852
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02025864
FUN_02025864: ; 0x02025864
	push {r3, lr}
	cmp r1, #0x0
	bne _02025872
	mov r1, #0x14
	bl FUN_020258F0
	pop {r3, pc}
_02025872:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}

	thumb_func_start FUN_02025878
FUN_02025878: ; 0x02025878
	push {r3, lr}
	bl FUN_02025940
	cmp r0, #0x0
	beq _02025886
	bl FUN_02025658
_02025886:
	pop {r3, pc}

	thumb_func_start FUN_02025888
FUN_02025888: ; 0x02025888
	push {r4, lr}
	add r4, r3, #0x0
	bl FUN_02025940
	add r1, r0, #0x0
	beq _0202589A
	add r0, r4, #0x0
	bl FUN_020256D0
_0202589A:
	pop {r4, pc}

	thumb_func_start FUN_0202589C
FUN_0202589C: ; 0x0202589C
	push {r3, lr}
	cmp r1, #0x0
	bne _020258AA
	mov r1, #0x14
	bl FUN_02025918
	pop {r3, pc}
_020258AA:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020258B0
FUN_020258B0: ; 0x020258B0
	push {r3-r5, lr}
	add r5, r3, #0x0
	bl FUN_02025940
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020256BC
	add r5, r0, #0x0
	cmp r4, #0x0
	beq _020258CE
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020256D0
_020258CE:
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020258D4
FUN_020258D4: ; 0x020258D4
	push {r4, lr}
	add r4, r3, #0x0
	bl FUN_02025940
	cmp r0, #0x0
	bne _020258E8
	add r0, r4, #0x0
	bl FUN_02025658
	pop {r4, pc}
_020258E8:
	add r1, r4, #0x0
	bl FUN_020256D0
	pop {r4, pc}

	thumb_func_start FUN_020258F0
FUN_020258F0: ; 0x020258F0
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	mov r4, #0x0
	cmp r6, #0x0
	ble _02025912
_020258FC:
	add r0, r5, #0x0
	bl FUN_020256AC
	cmp r0, #0x0
	bne _0202590A
	add r0, r4, #0x0
	pop {r4-r6, pc}
_0202590A:
	add r4, r4, #0x1
	add r5, #0x38
	cmp r4, r6
	blt _020258FC
_02025912:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}

	thumb_func_start FUN_02025918
FUN_02025918: ; 0x02025918
	push {r3-r7, lr}
	mov r4, #0x0
	add r7, r1, #0x0
	add r5, r0, #0x0
	add r6, r4, #0x0
	cmp r7, #0x0
	ble _0202593A
_02025926:
	add r0, r5, #0x0
	bl FUN_020256AC
	cmp r0, #0x0
	beq _02025932
	add r4, r4, #0x1
_02025932:
	add r6, r6, #0x1
	add r5, #0x38
	cmp r6, r7
	blt _02025926
_0202593A:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02025940
FUN_02025940: ; 0x02025940
	mov r3, #0x0
	cmp r1, #0x0
	bne _02025950
	cmp r2, #0x14
	bge _02025950
	mov r1, #0x38
	mul r1, r2
	add r3, r0, r1
_02025950:
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_02025954
FUN_02025954: ; 0x02025954
	ldr r0, _02025958 ; =0x000009B4
	bx lr
	.balign 4
_02025958: .word 0x000009B4

	thumb_func_start FUN_0202595C
FUN_0202595C: ; 0x0202595C
	mov r0, #0x94
	bx lr

	thumb_func_start FUN_02025960
FUN_02025960: ; 0x02025960
	mov r0, #0x3c
	bx lr

	thumb_func_start FUN_02025964
FUN_02025964: ; 0x02025964
	push {r4, lr}
	mov r1, #0x3c
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x3c
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202597C
FUN_0202597C: ; 0x0202597C
	push {r4-r7, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	add r0, sp, #0xc
	add r1, sp, #0x0
	bl FUN_0201265C
	ldr r0, _020259D8 ; =0x021C48B8
	ldr r6, [sp, #0xc]
	ldr r1, [sp, #0x8]
	ldr r0, [r0, #0x2c]
	lsl r6, r6, #0x5
	add r5, r1, r0
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r0, r0, r6
	lsl r0, r0, #0x5
	add r0, r1, r0
	mov r7, #0x0
	ldr r2, [sp, #0x0]
	lsl r0, r0, #0x5
	add r0, r2, r0
	ldr r3, [sp, #0x4]
	lsl r0, r0, #0x5
	add r0, r3, r0
	lsl r0, r0, #0x5
	add r5, r5, r0
	ldr r2, _020259DC ; =0x000009B4
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl MI_CpuFill8
	add r0, r4, #0x0
	add r0, #0x94
	mov r1, #0x9b
	str r5, [r0, #0x0]
	lsl r1, r1, #0x4
	ldrb r2, [r4, r1]
	mov r0, #0xf
	bic r2, r0
	mov r0, #0x1
	orr r0, r2
	strb r0, [r4, r1]
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_020259D8: .word 0x021C48B8
_020259DC: .word 0x000009B4

	thumb_func_start FUN_020259E0
FUN_020259E0: ; 0x020259E0
	mov r1, #0x9
	mov r3, #0x0
	lsl r1, r1, #0x8
_020259E6:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _020259F2
	add r0, r3, #0x0
	bx lr
_020259F2:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _020259E6
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4

	thumb_func_start FUN_02025A00
FUN_02025A00: ; 0x02025A00
	mov r1, #0x95
	mov r3, #0x0
	lsl r1, r1, #0x4
_02025A06:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025A12
	add r0, r3, #0x0
	bx lr
_02025A12:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025A06
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4

	thumb_func_start FUN_02025A20
FUN_02025A20: ; 0x02025A20
	ldr r1, _02025A3C ; =0x00000928
	mov r3, #0x0
_02025A24:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025A30
	add r0, r3, #0x0
	bx lr
_02025A30:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025A24
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4
_02025A3C: .word 0x00000928

	thumb_func_start FUN_02025A40
FUN_02025A40: ; 0x02025A40
	ldr r1, _02025A5C ; =0x000008D8
	mov r3, #0x0
_02025A44:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025A50
	add r0, r3, #0x0
	bx lr
_02025A50:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025A44
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4
_02025A5C: .word 0x000008D8

	thumb_func_start FUN_02025A60
FUN_02025A60: ; 0x02025A60
	push {r4-r7, lr}
	sub sp, #0x14
	str r1, [sp, #0x0]
	bl FUN_02026CC4
	ldr r1, _02025B50 ; =0x020EE958
	add r6, r0, #0x0
	ldrb r2, [r1, #0x0]
	add r0, sp, #0x8
	strb r2, [r0, #0x6]
	ldrb r2, [r1, #0x1]
	strb r2, [r0, #0x7]
	ldrb r2, [r1, #0x2]
	strb r2, [r0, #0x8]
	ldrb r2, [r1, #0x3]
	strb r2, [r0, #0x9]
	ldrb r2, [r1, #0x4]
	strb r2, [r0, #0xa]
	ldrb r2, [r1, #0x5]
	strb r2, [r0, #0xb]
	ldrb r2, [r1, #0x6]
	strb r2, [r0, #0x0]
	ldrb r2, [r1, #0x7]
	strb r2, [r0, #0x1]
	ldrb r2, [r1, #0x8]
	strb r2, [r0, #0x2]
	ldrb r2, [r1, #0x9]
	strb r2, [r0, #0x3]
	ldrb r2, [r1, #0xa]
	strb r2, [r0, #0x4]
	ldrb r1, [r1, #0xb]
	strb r1, [r0, #0x5]
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	ble _02025B4C
	str r0, [sp, #0x4]
	cmp r0, #0x63
	ble _02025AB0
	mov r0, #0x63
	str r0, [sp, #0x4]
_02025AB0:
	add r0, r6, #0x0
	add r0, #0x94
	ldr r3, [r0, #0x0]
	mov r0, #0x0
	mov r12, r0
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _02025B28
	add r7, sp, #0xc
	add r7, #0x2
_02025AC4:
	mov r2, #0x0
_02025AC6:
	ldr r0, _02025B54 ; =0x0000055C
	add r4, r6, r2
	ldrb r5, [r4, r0]
	cmp r5, #0x0
	beq _02025B16
	ldr r0, _02025B58 ; =0x5D588B65
	ldrb r1, [r7, r5]
	mul r0, r3
	ldr r3, _02025B5C ; =0x00269EC3
	add r3, r0, r3
	cmp r1, #0x0
	bne _02025AE2
	lsr r0, r3, #0x10
	b _02025AE8
_02025AE2:
	lsr r0, r3, #0x10
	mul r1, r0
	lsr r0, r1, #0x10
_02025AE8:
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r0, sp, #0x8
	ldrb r0, [r0, r5]
	add r0, r0, r1
	mov r1, #0x17
	lsl r1, r1, #0x6
	ldrb r1, [r4, r1]
	add r1, r0, r1
	cmp r1, #0x63
	bge _02025B0E
	mov r1, #0x17
	lsl r1, r1, #0x6
	ldrb r1, [r4, r1]
	add r1, r1, r0
	mov r0, #0x17
	lsl r0, r0, #0x6
	strb r1, [r4, r0]
	b _02025B16
_02025B0E:
	mov r0, #0x17
	mov r1, #0x63
	lsl r0, r0, #0x6
	strb r1, [r4, r0]
_02025B16:
	add r2, r2, #0x1
	cmp r2, #0x64
	blt _02025AC6
	mov r0, r12
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	mov r12, r1
	cmp r1, r0
	blt _02025AC4
_02025B28:
	add r0, r6, #0x0
	add r0, #0x94
	ldr r1, [r0, #0x0]
	ldr r0, [sp, #0x0]
	add r0, r1, r0
	bl FUN_0201BA10
	add r1, r6, #0x0
	add r1, #0x94
	str r0, [r1, #0x0]
	mov r1, #0x9b
	lsl r1, r1, #0x4
	ldrb r2, [r6, r1]
	mov r0, #0xf
	bic r2, r0
	mov r0, #0x1
	orr r0, r2
	strb r0, [r6, r1]
_02025B4C:
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02025B50: .word 0x020EE958
_02025B54: .word 0x0000055C
_02025B58: .word 0x5D588B65
_02025B5C: .word 0x00269EC3

	thumb_func_start FUN_02025B60
FUN_02025B60: ; 0x02025B60
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r2, #0x0
	bl FUN_02026CC4
	cmp r4, #0x0
	blt _02025B90
	cmp r5, #0x0
	bne _02025B90
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	cmp r1, r4
	bge _02025B84
	mov r1, #0x0
	add r0, #0x98
	str r1, [r0, #0x0]
	pop {r3-r5, pc}
_02025B84:
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	add r0, #0x98
	sub r1, r1, r4
	str r1, [r0, #0x0]
_02025B90:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02025B94
FUN_02025B94: ; 0x02025B94
	push {r3, lr}
	bl FUN_02026CC4
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02025BB6
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x2
	bne _02025BB6
	add r1, r0, #0x0
	mov r2, #0x0
	add r1, #0x9c
	strb r2, [r1, #0x0]
_02025BB6:
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02025BD4
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	bne _02025BD4
	mov r2, #0x5a
	add r1, r0, #0x0
	lsl r2, r2, #0x4
	add r1, #0x98
	str r2, [r1, #0x0]
_02025BD4:
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	bne _02025BE4
	mov r1, #0x2
	add r0, #0x9c
	strb r1, [r0, #0x0]
_02025BE4:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02025BE8
FUN_02025BE8: ; 0x02025BE8
	push {r3, lr}
	bl FUN_02026CC4
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02025BFE
	mov r1, #0x1
	add r0, #0x9c
	strb r1, [r0, #0x0]
_02025BFE:
	pop {r3, pc}

	thumb_func_start FUN_02025C00
FUN_02025C00: ; 0x02025C00
	push {r3, lr}
	bl FUN_02026CC4
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	bne _02025C16
	mov r1, #0x0
	add r0, #0x9c
	strb r1, [r0, #0x0]
_02025C16:
	pop {r3, pc}

	thumb_func_start FUN_02025C18
FUN_02025C18: ; 0x02025C18
	push {r3, lr}
	bl FUN_02026CC4
	add r0, #0x9c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	beq _02025C2A
	mov r0, #0x1
	pop {r3, pc}
_02025C2A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02025C30
FUN_02025C30: ; 0x02025C30
	mov r1, #0x1
	add r0, #0x9d
	strb r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02025C38
FUN_02025C38: ; 0x02025C38
	add r0, #0x9d
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025C40
FUN_02025C40: ; 0x02025C40
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _02025CD0 ; =0x0000010E
	add r6, r1, #0x0
	ldrb r0, [r7, r0]
	mov r4, #0x0
	add r5, r7, #0x0
	str r0, [sp, #0x0]
_02025C50:
	add r0, r6, #0x0
	bl FUN_020239BC
	add r1, r5, #0x0
	add r1, #0xa0
	ldr r1, [r1, #0x0]
	cmp r1, r0
	beq _02025CCC
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x5
	blt _02025C50
	ldr r0, [sp, #0x0]
	cmp r0, #0x5
	blt _02025C72
	bl ErrorHandling
_02025C72:
	add r0, r6, #0x0
	bl FUN_0202398C
	ldr r1, [sp, #0x0]
	add r2, r7, #0x0
	add r2, #0xb4
	lsl r1, r1, #0x4
	add r1, r2, r1
	mov r2, #0x10
	bl MI_CpuCopy8
	add r0, r6, #0x0
	bl FUN_020239BC
	ldr r1, [sp, #0x0]
	lsl r1, r1, #0x2
	add r1, r7, r1
	add r1, #0xa0
	str r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_02023A70
	ldr r1, [sp, #0x0]
	add r2, r7, r1
	mov r1, #0x41
	lsl r1, r1, #0x2
	strb r0, [r2, r1]
	add r0, r6, #0x0
	bl FUN_02023A68
	ldr r1, [sp, #0x0]
	add r2, r7, r1
	ldr r1, _02025CD4 ; =0x00000109
	strb r0, [r2, r1]
	add r0, r1, #0x5
	ldrb r0, [r7, r0]
	add r2, r0, #0x1
	add r0, r1, #0x5
	strb r2, [r7, r0]
	ldrb r0, [r7, r0]
	cmp r0, #0x5
	blo _02025CCC
	mov r2, #0x0
	add r0, r1, #0x5
	strb r2, [r7, r0]
_02025CCC:
	pop {r3-r7, pc}
	nop
_02025CD0: .word 0x0000010E
_02025CD4: .word 0x00000109

	thumb_func_start FUN_02025CD8
FUN_02025CD8: ; 0x02025CD8
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _02025D38 ; =0x0000010E
	ldrb r0, [r5, r0]
	sub r0, r0, r2
	sub r4, r0, #0x1
	bpl _02025CE8
	add r4, r4, #0x5
_02025CE8:
	add r7, r5, #0x0
	lsl r0, r4, #0x4
	add r7, #0xb4
	str r0, [sp, #0x0]
	ldrh r0, [r7, r0]
	cmp r0, #0x0
	beq _02025D32
	add r0, r1, #0x0
	bl FUN_02023928
	ldr r1, [sp, #0x0]
	add r6, r0, #0x0
	add r1, r7, r1
	bl FUN_0202395C
	ldr r1, _02025D3C ; =0x00000109
	add r2, r5, r4
	ldrb r1, [r2, r1]
	add r0, r6, #0x0
	bl FUN_02023A6C
	mov r1, #0x41
	add r2, r5, r4
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	add r0, r6, #0x0
	bl FUN_02023A74
	lsl r1, r4, #0x2
	add r1, r5, r1
	add r1, #0xa0
	ldr r1, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_020239B8
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02025D32:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02025D38: .word 0x0000010E
_02025D3C: .word 0x00000109

	thumb_func_start FUN_02025D40
FUN_02025D40: ; 0x02025D40
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025D48
FUN_02025D48: ; 0x02025D48
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0xb
	bge _02025D54
	bl ErrorHandling
_02025D54:
	cmp r4, #0x3c
	blt _02025D5C
	bl ErrorHandling
_02025D5C:
	sub r4, #0xb
	ldr r0, _02025D68 ; =0x02105C74
	lsl r1, r4, #0x1
	ldrh r0, [r0, r1]
	pop {r4, pc}
	nop
_02025D68: .word 0x02105C74

	thumb_func_start FUN_02025D6C
FUN_02025D6C: ; 0x02025D6C
	push {r4-r5}
	mov r2, #0x81
	mov r5, #0x0
	lsl r2, r2, #0x4
_02025D74:
	add r4, r0, r5
	ldrb r3, [r4, r2]
	cmp r3, #0x0
	bne _02025D88
	mov r0, #0x81
	lsl r0, r0, #0x4
	strb r1, [r4, r0]
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02025D88:
	add r5, r5, #0x1
	cmp r5, #0xc8
	blt _02025D74
	mov r0, #0x0
	pop {r4-r5}
	bx lr

	thumb_func_start FUN_02025D94
FUN_02025D94: ; 0x02025D94
	mov r1, #0x81
	mov r3, #0x0
	lsl r1, r1, #0x4
_02025D9A:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025DA6
	mov r0, #0x1
	bx lr
_02025DA6:
	add r3, r3, #0x1
	cmp r3, #0xc8
	blt _02025D9A
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02025DB0
FUN_02025DB0: ; 0x02025DB0
	mov r1, #0x81
	mov r3, #0x0
	lsl r1, r1, #0x4
_02025DB6:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _02025DC4
	add r3, r3, #0x1
	cmp r3, #0xc8
	blt _02025DB6
_02025DC4:
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_02025DC8
FUN_02025DC8: ; 0x02025DC8
	add r1, r0, r1
	mov r0, #0x81
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025DD4
FUN_02025DD4: ; 0x02025DD4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02025F0C
	cmp r0, #0x0
	beq _02025DE6
	bl ErrorHandling
_02025DE6:
	mov r0, #0x81
	add r1, r5, r4
	lsl r0, r0, #0x4
	add r6, r4, #0x0
	ldrb r7, [r1, r0]
	cmp r4, #0xc7
	bge _02025E06
	mov r1, #0x81
	add r0, r0, #0x1
	lsl r1, r1, #0x4
_02025DFA:
	add r3, r5, r6
	ldrb r2, [r3, r0]
	add r6, r6, #0x1
	cmp r6, #0xc7
	strb r2, [r3, r1]
	blt _02025DFA
_02025E06:
	ldr r0, _02025E1C ; =0x000008D7
	mov r2, #0x0
	strb r2, [r5, r0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	sub r2, r2, #0x1
	bl FUN_02025F58
	add r0, r7, #0x0
	pop {r3-r7, pc}
	nop
_02025E1C: .word 0x000008D7

	thumb_func_start FUN_02025E20
FUN_02025E20: ; 0x02025E20
	push {r4-r7, lr}
	sub sp, #0xd4
	mov r4, #0x0
	add r5, r0, #0x0
	sub r0, r4, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x81
	lsl r0, r0, #0x4
	str r1, [sp, #0x8]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0xc
	mov r2, #0xc8
	bl MI_CpuCopy8
	ldr r2, [sp, #0x8]
	add r1, sp, #0xc
	add r0, r4, #0x0
	add r7, r1, r2
_02025E46:
	ldr r2, [sp, #0x8]
	cmp r0, r2
	beq _02025E58
	ldrb r6, [r1, #0x0]
	mov r2, #0x81
	add r3, r5, r4
	lsl r2, r2, #0x4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02025E58:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _02025E6A
	ldrb r6, [r7, #0x0]
	mov r2, #0x81
	add r3, r5, r4
	lsl r2, r2, #0x4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02025E6A:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0xc8
	blt _02025E46
	ldr r0, [sp, #0x8]
	mov r3, #0x0
	add r2, r0, #0x1
	mov r0, #0x9a
	lsl r0, r0, #0x4
_02025E7C:
	add r1, r5, r3
	ldrb r1, [r1, r0]
	cmp r2, r1
	bne _02025E88
	str r3, [sp, #0x4]
	b _02025E8E
_02025E88:
	add r3, r3, #0x1
	cmp r3, #0xf
	blt _02025E7C
_02025E8E:
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02025F58
	mov r2, #0x0
	ldr r1, [sp, #0x8]
	add r0, r5, #0x0
	mvn r2, r2
	bl FUN_02025F58
	mov r1, #0x0
	ldr r0, [sp, #0x4]
	mvn r1, r1
	cmp r0, r1
	beq _02025ED6
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x8]
	cmp r0, r1
	bge _02025EC8
	add r0, r1, #0x0
	add r2, r0, #0x1
	ldr r0, [sp, #0x4]
	add sp, #0xd4
	add r1, r5, r0
	mov r0, #0x9a
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
	pop {r4-r7, pc}
_02025EC8:
	add r0, r1, #0x0
	add r2, r0, #0x2
	ldr r0, [sp, #0x4]
	add r1, r5, r0
	mov r0, #0x9a
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
_02025ED6:
	add sp, #0xd4
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02025EDC
FUN_02025EDC: ; 0x02025EDC
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r6, #0x1
	bge _02025EEC
	bl ErrorHandling
_02025EEC:
	cmp r6, #0xf
	ble _02025EF4
	bl ErrorHandling
_02025EF4:
	sub r0, r6, #0x1
	add r1, r5, r0
	mov r0, #0x9a
	add r2, r4, #0x1
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
	mov r0, #0x81
	add r1, r5, r4
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02025F0C
FUN_02025F0C: ; 0x02025F0C
	push {r3-r4}
	add r3, r1, #0x1
	mov r1, #0x9a
	mov r4, #0x0
	lsl r1, r1, #0x4
_02025F16:
	add r2, r0, r4
	ldrb r2, [r2, r1]
	cmp r3, r2
	bne _02025F24
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_02025F24:
	add r4, r4, #0x1
	cmp r4, #0xf
	blt _02025F16
	mov r0, #0x0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02025F30
FUN_02025F30: ; 0x02025F30
	sub r1, r1, #0x1
	cmp r1, #0xf
	bge _02025F40
	add r1, r0, r1
	mov r0, #0x9a
	mov r2, #0x0
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
_02025F40:
	bx lr
	.balign 4

	thumb_func_start FUN_02025F44
FUN_02025F44: ; 0x02025F44
	mov r1, #0x9a
	lsl r1, r1, #0x4
	add r0, r0, r1
	ldr r3, _02025F54 ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0xf
	bx r3
	nop
_02025F54: .word MI_CpuFill8

	thumb_func_start FUN_02025F58
FUN_02025F58: ; 0x02025F58
	push {r4-r7}
	mov r6, #0x9a
	lsl r6, r6, #0x4
	mov r4, #0x0
	add r1, r1, #0x1
	add r7, r6, #0x0
_02025F64:
	add r3, r0, r4
	ldrb r5, [r3, r7]
	cmp r5, r1
	ble _02025F76
	mov r5, #0x9a
	lsl r5, r5, #0x4
	ldrb r5, [r3, r5]
	add r5, r5, r2
	strb r5, [r3, r6]
_02025F76:
	add r4, r4, #0x1
	cmp r4, #0xf
	blt _02025F64
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_02025F80
FUN_02025F80: ; 0x02025F80
	mov r1, #0x9
	mov r3, #0x0
	lsl r1, r1, #0x8
_02025F86:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _02025F94
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025F86
_02025F94:
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_02025F98
FUN_02025F98: ; 0x02025F98
	add r1, r0, r1
	mov r0, #0x9
	lsl r0, r0, #0x8
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025FA4
FUN_02025FA4: ; 0x02025FA4
	push {r3-r6}
	mov r2, #0x9
	add r3, r0, r1
	lsl r2, r2, #0x8
	ldrb r2, [r3, r2]
	cmp r1, #0x27
	bge _02025FC2
	ldr r3, _02025FD0 ; =0x00000901
	sub r4, r3, #0x1
_02025FB6:
	add r6, r0, r1
	ldrb r5, [r6, r3]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r5, [r6, r4]
	blt _02025FB6
_02025FC2:
	ldr r1, _02025FD4 ; =0x00000927
	mov r3, #0x0
	strb r3, [r0, r1]
	add r0, r2, #0x0
	pop {r3-r6}
	bx lr
	nop
_02025FD0: .word 0x00000901
_02025FD4: .word 0x00000927

	thumb_func_start FUN_02025FD8
FUN_02025FD8: ; 0x02025FD8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020259E0
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02025FF6
	add r1, r5, r0
	mov r0, #0x9
	lsl r0, r0, #0x8
	strb r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}
_02025FF6:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02025FFC
FUN_02025FFC: ; 0x02025FFC
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	mov r0, #0x9
	lsl r0, r0, #0x8
	str r1, [sp, #0x4]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0x8
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r2, [sp, #0x4]
	add r1, sp, #0x8
	add r0, r4, #0x0
	add r7, r1, r2
_0202601E:
	ldr r2, [sp, #0x4]
	cmp r0, r2
	beq _02026030
	ldrb r6, [r1, #0x0]
	mov r2, #0x9
	add r3, r5, r4
	lsl r2, r2, #0x8
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02026030:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _02026042
	ldrb r6, [r7, #0x0]
	mov r2, #0x9
	add r3, r5, r4
	lsl r2, r2, #0x8
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02026042:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0x28
	blt _0202601E
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026050
FUN_02026050: ; 0x02026050
	mov r1, #0x95
	mov r3, #0x0
	lsl r1, r1, #0x4
_02026056:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _02026064
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02026056
_02026064:
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_02026068
FUN_02026068: ; 0x02026068
	add r1, r0, r1
	mov r0, #0x95
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026074
FUN_02026074: ; 0x02026074
	add r1, r0, r1
	ldr r0, _0202607C ; =0x00000978
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_0202607C: .word 0x00000978

	thumb_func_start FUN_02026080
FUN_02026080: ; 0x02026080
	push {r4-r7}
	add r2, r0, #0x0
	mov r0, #0x95
	add r3, r2, r1
	lsl r0, r0, #0x4
	ldrb r0, [r3, r0]
	cmp r1, #0x27
	mov r12, r0
	bge _020260AE
	ldr r7, _020260BC ; =0x00000951
	add r4, r7, #0x0
	add r5, r7, #0x0
	sub r3, r7, #0x1
	add r4, #0x28
	add r5, #0x27
_0202609E:
	add r0, r2, r1
	ldrb r6, [r0, r7]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r6, [r0, r3]
	ldrb r6, [r0, r4]
	strb r6, [r0, r5]
	blt _0202609E
_020260AE:
	ldr r0, _020260C0 ; =0x00000977
	mov r1, #0x0
	strb r1, [r2, r0]
	mov r0, r12
	pop {r4-r7}
	bx lr
	nop
_020260BC: .word 0x00000951
_020260C0: .word 0x00000977

	thumb_func_start FUN_020260C4
FUN_020260C4: ; 0x020260C4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02025A00
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020260E8
	add r1, r5, r0
	mov r0, #0x95
	lsl r0, r0, #0x4
	strb r4, [r1, r0]
	add r0, #0x28
	strb r6, [r1, r0]
	mov r0, #0x1
	pop {r4-r6, pc}
_020260E8:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020260EC
FUN_020260EC: ; 0x020260EC
	push {r4-r7, lr}
	sub sp, #0x5c
	add r7, r0, #0x0
	mov r0, #0x95
	lsl r0, r0, #0x4
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r0, r7, r0
	add r1, sp, #0x34
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r0, _02026168 ; =0x00000978
	add r1, sp, #0xc
	add r0, r7, r0
	mov r2, #0x28
	bl MI_CpuCopy8
	ldr r3, [sp, #0x0]
	add r1, sp, #0x34
	add r3, r1, r3
	mov r12, r3
	ldr r3, [sp, #0x0]
	add r2, sp, #0xc
	add r3, r2, r3
	add r0, r4, #0x0
	str r3, [sp, #0x8]
_02026124:
	ldr r3, [sp, #0x0]
	cmp r0, r3
	beq _0202613C
	ldrb r5, [r1, #0x0]
	mov r3, #0x95
	add r6, r7, r4
	lsl r3, r3, #0x4
	strb r5, [r6, r3]
	ldrb r5, [r2, #0x0]
	add r3, #0x28
	add r4, r4, #0x1
	strb r5, [r6, r3]
_0202613C:
	ldr r3, [sp, #0x4]
	cmp r0, r3
	bne _02026158
	mov r3, r12
	ldrb r5, [r3, #0x0]
	mov r3, #0x95
	add r6, r7, r4
	lsl r3, r3, #0x4
	strb r5, [r6, r3]
	ldr r3, [sp, #0x8]
	add r4, r4, #0x1
	ldrb r5, [r3, #0x0]
	ldr r3, _02026168 ; =0x00000978
	strb r5, [r6, r3]
_02026158:
	add r0, r0, #0x1
	add r1, r1, #0x1
	add r2, r2, #0x1
	cmp r0, #0x28
	blt _02026124
	add sp, #0x5c
	pop {r4-r7, pc}
	nop
_02026168: .word 0x00000978

	thumb_func_start FUN_0202616C
FUN_0202616C: ; 0x0202616C
	ldr r1, _02026184 ; =0x00000928
	mov r3, #0x0
_02026170:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _0202617E
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02026170
_0202617E:
	add r0, r3, #0x0
	bx lr
	nop
_02026184: .word 0x00000928

	thumb_func_start FUN_02026188
FUN_02026188: ; 0x02026188
	add r1, r0, r1
	ldr r0, _02026190 ; =0x00000928
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026190: .word 0x00000928

	thumb_func_start FUN_02026194
FUN_02026194: ; 0x02026194
	push {r3-r6}
	ldr r2, _020261BC ; =0x00000928
	add r3, r0, r1
	ldrb r2, [r3, r2]
	cmp r1, #0x27
	bge _020261B0
	ldr r3, _020261C0 ; =0x00000929
	sub r4, r3, #0x1
_020261A4:
	add r6, r0, r1
	ldrb r5, [r6, r3]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r5, [r6, r4]
	blt _020261A4
_020261B0:
	ldr r1, _020261C4 ; =0x0000094F
	mov r3, #0x0
	strb r3, [r0, r1]
	add r0, r2, #0x0
	pop {r3-r6}
	bx lr
	.balign 4
_020261BC: .word 0x00000928
_020261C0: .word 0x00000929
_020261C4: .word 0x0000094F

	thumb_func_start FUN_020261C8
FUN_020261C8: ; 0x020261C8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02025A20
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020261E4
	add r1, r5, r0
	ldr r0, _020261E8 ; =0x00000928
	strb r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}
_020261E4:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_020261E8: .word 0x00000928

	thumb_func_start FUN_020261EC
FUN_020261EC: ; 0x020261EC
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	ldr r0, _02026238 ; =0x00000928
	str r1, [sp, #0x4]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0x8
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r2, [sp, #0x4]
	add r1, sp, #0x8
	add r0, r4, #0x0
	add r7, r1, r2
_0202620C:
	ldr r2, [sp, #0x4]
	cmp r0, r2
	beq _0202621C
	ldrb r6, [r1, #0x0]
	ldr r2, _02026238 ; =0x00000928
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_0202621C:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _0202622C
	ldrb r6, [r7, #0x0]
	ldr r2, _02026238 ; =0x00000928
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_0202622C:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0x28
	blt _0202620C
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_02026238: .word 0x00000928

	thumb_func_start FUN_0202623C
FUN_0202623C: ; 0x0202623C
	ldr r1, _02026254 ; =0x000008D8
	mov r3, #0x0
_02026240:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _0202624E
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02026240
_0202624E:
	add r0, r3, #0x0
	bx lr
	nop
_02026254: .word 0x000008D8

	thumb_func_start FUN_02026258
FUN_02026258: ; 0x02026258
	add r1, r0, r1
	ldr r0, _02026260 ; =0x000008D8
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026260: .word 0x000008D8

	thumb_func_start FUN_02026264
FUN_02026264: ; 0x02026264
	push {r3-r6}
	ldr r2, _0202628C ; =0x000008D8
	add r3, r0, r1
	ldrb r2, [r3, r2]
	cmp r1, #0x27
	bge _02026280
	ldr r3, _02026290 ; =0x000008D9
	sub r4, r3, #0x1
_02026274:
	add r6, r0, r1
	ldrb r5, [r6, r3]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r5, [r6, r4]
	blt _02026274
_02026280:
	ldr r1, _02026294 ; =0x000008FF
	mov r3, #0x0
	strb r3, [r0, r1]
	add r0, r2, #0x0
	pop {r3-r6}
	bx lr
	.balign 4
_0202628C: .word 0x000008D8
_02026290: .word 0x000008D9
_02026294: .word 0x000008FF

	thumb_func_start FUN_02026298
FUN_02026298: ; 0x02026298
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02025A40
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020262B4
	add r1, r5, r0
	ldr r0, _020262B8 ; =0x000008D8
	strb r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}
_020262B4:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_020262B8: .word 0x000008D8

	thumb_func_start FUN_020262BC
FUN_020262BC: ; 0x020262BC
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	ldr r0, _02026308 ; =0x000008D8
	str r1, [sp, #0x4]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0x8
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r2, [sp, #0x4]
	add r1, sp, #0x8
	add r0, r4, #0x0
	add r7, r1, r2
_020262DC:
	ldr r2, [sp, #0x4]
	cmp r0, r2
	beq _020262EC
	ldrb r6, [r1, #0x0]
	ldr r2, _02026308 ; =0x000008D8
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_020262EC:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _020262FC
	ldrb r6, [r7, #0x0]
	ldr r2, _02026308 ; =0x000008D8
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_020262FC:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0x28
	blt _020262DC
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_02026308: .word 0x000008D8

	thumb_func_start FUN_0202630C
FUN_0202630C: ; 0x0202630C
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r6, r3, #0x0
	cmp r4, #0x40
	blt _0202631E
	bl ErrorHandling
_0202631E:
	ldr r0, _02026350 ; =0x0000010F
	add r1, r5, r4
	strb r7, [r1, r0]
	lsl r1, r4, #0x1
	add r1, r4, r1
	add r2, r0, #0x0
	add r1, r5, r1
	add r2, #0x40
	strb r6, [r1, r2]
	mov r2, #0xf
	lsl r2, r2, #0x8
	add r3, r6, #0x0
	and r3, r2
	asr r4, r3, #0x8
	ldr r3, [sp, #0x18]
	and r2, r3
	asr r2, r2, #0x4
	add r4, r4, r2
	add r2, r0, #0x0
	add r2, #0x41
	strb r4, [r1, r2]
	add r0, #0x42
	strb r3, [r1, r0]
	pop {r3-r7, pc}
	nop
_02026350: .word 0x0000010F

	thumb_func_start FUN_02026354
FUN_02026354: ; 0x02026354
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _02026362
	bl ErrorHandling
_02026362:
	ldr r0, _0202636C ; =0x0000010F
	add r1, r5, r4
	ldrb r0, [r1, r0]
	pop {r3-r5, pc}
	nop
_0202636C: .word 0x0000010F

	thumb_func_start FUN_02026370
FUN_02026370: ; 0x02026370
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _0202637E
	bl ErrorHandling
_0202637E:
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r1, r5, r0
	ldr r0, _02026398 ; =0x0000014F
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	pop {r3-r5, pc}
	.balign 4
_02026398: .word 0x0000014F

	thumb_func_start FUN_0202639C
FUN_0202639C: ; 0x0202639C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _020263AA
	bl ErrorHandling
_020263AA:
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r1, r5, r0
	ldr r0, _020263C4 ; =0x00000151
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	pop {r3-r5, pc}
	.balign 4
_020263C4: .word 0x00000151

	thumb_func_start FUN_020263C8
FUN_020263C8: ; 0x020263C8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _020263D6
	bl ErrorHandling
_020263D6:
	ldr r0, _020263F0 ; =0x0000010F
	mov r1, #0x0
	add r2, r5, r4
	strb r1, [r2, r0]
	add r0, #0x40
	add r2, r5, r0
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r0, r2, r0
	mov r2, #0x3
	bl MI_CpuFill8
	pop {r3-r5, pc}
	.balign 4
_020263F0: .word 0x0000010F

	thumb_func_start FUN_020263F4
FUN_020263F4: ; 0x020263F4
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r6, r3, #0x0
	cmp r4, #0x10
	blt _02026406
	bl ErrorHandling
_02026406:
	lsl r2, r4, #0x1
	ldr r1, _02026440 ; =0x0000050C
	add r0, r5, r4
	add r2, r4, r2
	add r4, r5, r2
	add r2, r1, #0x0
	mov r5, #0xf
	strb r7, [r0, r1]
	add r2, #0x10
	strb r6, [r4, r2]
	lsl r5, r5, #0x8
	add r2, r6, #0x0
	and r2, r5
	asr r3, r2, #0x8
	ldr r2, [sp, #0x18]
	and r5, r2
	asr r5, r5, #0x4
	add r5, r3, r5
	add r3, r1, #0x0
	add r3, #0x11
	strb r5, [r4, r3]
	add r3, r1, #0x0
	add r3, #0x12
	strb r2, [r4, r3]
	ldr r2, [sp, #0x1c]
	add r1, #0x40
	strb r2, [r0, r1]
	pop {r3-r7, pc}
	nop
_02026440: .word 0x0000050C

	thumb_func_start FUN_02026444
FUN_02026444: ; 0x02026444
	add r1, r0, r1
	ldr r0, _0202644C ; =0x0000050C
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_0202644C: .word 0x0000050C

	thumb_func_start FUN_02026450
FUN_02026450: ; 0x02026450
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _0202646C ; =0x0000051C
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_0202646C: .word 0x0000051C

	thumb_func_start FUN_02026470
FUN_02026470: ; 0x02026470
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _0202648C ; =0x0000051E
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_0202648C: .word 0x0000051E

	thumb_func_start FUN_02026490
FUN_02026490: ; 0x02026490
	add r1, r0, r1
	ldr r0, _02026498 ; =0x0000054C
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026498: .word 0x0000054C

	thumb_func_start FUN_0202649C
FUN_0202649C: ; 0x0202649C
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r3, #0x0
	cmp r4, #0x64
	blt _020264AE
	bl ErrorHandling
_020264AE:
	ldr r1, _020264E8 ; =0x0000055C
	add r0, r5, r4
	strb r6, [r0, r1]
	lsl r1, r4, #0x1
	add r1, r4, r1
	add r4, r5, r1
	mov r5, #0xf
	lsl r5, r5, #0x8
	add r2, r7, #0x0
	and r2, r5
	asr r3, r2, #0x8
	ldr r2, [sp, #0x18]
	ldr r1, _020264EC ; =0x00000688
	and r5, r2
	asr r5, r5, #0x4
	add r5, r3, r5
	strb r7, [r4, r1]
	add r3, r1, #0x1
	strb r5, [r4, r3]
	add r3, r1, #0x2
	strb r2, [r4, r3]
	add r2, r1, #0x0
	ldr r3, [sp, #0x1c]
	sub r2, #0x64
	strb r3, [r0, r2]
	ldr r2, [sp, #0x20]
	sub r1, #0xc8
	strb r2, [r0, r1]
	pop {r3-r7, pc}
	.balign 4
_020264E8: .word 0x0000055C
_020264EC: .word 0x00000688

	thumb_func_start FUN_020264F0
FUN_020264F0: ; 0x020264F0
	add r1, r0, r1
	ldr r0, _020264F8 ; =0x0000055C
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_020264F8: .word 0x0000055C

	thumb_func_start FUN_020264FC
FUN_020264FC: ; 0x020264FC
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _02026518 ; =0x00000688
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_02026518: .word 0x00000688

	thumb_func_start FUN_0202651C
FUN_0202651C: ; 0x0202651C
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _02026538 ; =0x0000068A
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_02026538: .word 0x0000068A

	thumb_func_start FUN_0202653C
FUN_0202653C: ; 0x0202653C
	add r1, r0, r1
	ldr r0, _02026544 ; =0x00000624
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026544: .word 0x00000624

	thumb_func_start FUN_02026548
FUN_02026548: ; 0x02026548
	add r1, r0, r1
	mov r0, #0x17
	lsl r0, r0, #0x6
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026554
FUN_02026554: ; 0x02026554
	push {r4-r7}
	ldr r3, _020265B0 ; =0x00000211
	add r7, r0, #0x0
	mov r12, r1
	mov r0, #0x0
	add r1, r7, #0x0
	sub r4, r3, #0x1
	sub r5, r3, #0x2
_02026564:
	ldrb r6, [r1, r5]
	cmp r6, #0x0
	bne _020265A0
	ldrb r6, [r1, r4]
	cmp r6, #0x0
	bne _020265A0
	ldrb r6, [r1, r3]
	cmp r6, #0x0
	bne _020265A0
	lsl r1, r0, #0x1
	add r1, r0, r1
	mov r5, #0xf
	ldr r4, _020265B4 ; =0x0000020F
	add r1, r7, r1
	mov r3, r12
	strb r3, [r1, r4]
	lsl r5, r5, #0x8
	mov r3, r12
	and r3, r5
	asr r6, r3, #0x8
	add r3, r2, #0x0
	and r3, r5
	asr r3, r3, #0x4
	add r5, r6, r3
	add r3, r4, #0x1
	strb r5, [r1, r3]
	add r3, r4, #0x2
	strb r2, [r1, r3]
	pop {r4-r7}
	bx lr
_020265A0:
	add r0, r0, #0x1
	add r1, r1, #0x3
	cmp r0, #0xff
	blt _02026564
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	nop
_020265B0: .word 0x00000211
_020265B4: .word 0x0000020F

	thumb_func_start FUN_020265B8
FUN_020265B8: ; 0x020265B8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xff
	blt _020265C6
	bl ErrorHandling
_020265C6:
	ldr r0, _020265DC ; =0x0000020F
	mov r2, #0x3
	add r1, r5, r0
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r0, r1, r0
	mov r1, #0x0
	bl MI_CpuFill8
	pop {r3-r5, pc}
	nop
_020265DC: .word 0x0000020F

	thumb_func_start FUN_020265E0
FUN_020265E0: ; 0x020265E0
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _020265FC ; =0x0000020F
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_020265FC: .word 0x0000020F

	thumb_func_start FUN_02026600
FUN_02026600: ; 0x02026600
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _0202661C ; =0x00000211
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_0202661C: .word 0x00000211

	thumb_func_start FUN_02026620
FUN_02026620: ; 0x02026620
	mov r1, #0x9b
	lsl r1, r1, #0x4
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	bne _02026630
	mov r0, #0x1
	bx lr
_02026630:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02026634
FUN_02026634: ; 0x02026634
	mov r2, #0x9b
	lsl r2, r2, #0x4
	ldrb r3, [r0, r2]
	mov r1, #0xf0
	bic r3, r1
	mov r1, #0x10
	orr r1, r3
	strb r1, [r0, r2]
	bx lr
	.balign 4

	thumb_func_start FUN_02026648
FUN_02026648: ; 0x02026648
	mov r1, #0x9b
	lsl r1, r1, #0x4
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bx lr

	thumb_func_start FUN_02026654
FUN_02026654: ; 0x02026654
	mov r2, #0x9b
	lsl r2, r2, #0x4
	ldrb r3, [r0, r2]
	mov r1, #0xf
	bic r3, r1
	strb r3, [r0, r2]
	bx lr
	.balign 4

	thumb_func_start FUN_02026664
FUN_02026664: ; 0x02026664
	push {r3-r4}
	cmp r1, #0x2c
	blt _0202667E
	cmp r1, #0x3b
	bgt _0202667E
	ldr r2, _02026684 ; =0x0000080C
	mov r3, #0x1
	sub r1, #0x2c
	ldr r4, [r0, r2]
	lsl r3, r1
	add r1, r4, #0x0
	orr r1, r3
	str r1, [r0, r2]
_0202667E:
	pop {r3-r4}
	bx lr
	nop
_02026684: .word 0x0000080C

	thumb_func_start FUN_02026688
FUN_02026688: ; 0x02026688
	cmp r1, #0x2c
	blt _02026690
	cmp r1, #0x3b
	ble _02026694
_02026690:
	mov r0, #0x1
	bx lr
_02026694:
	ldr r2, _020266AC ; =0x0000080C
	sub r1, #0x2c
	ldr r3, [r0, r2]
	mov r0, #0x1
	add r2, r0, #0x0
	lsl r2, r1
	add r1, r3, #0x0
	tst r1, r2
	beq _020266A8
	mov r0, #0x0
_020266A8:
	bx lr
	nop
_020266AC: .word 0x0000080C

	thumb_func_start FUN_020266B0
FUN_020266B0: ; 0x020266B0
	ldr r1, _020266C4 ; =0x000009AF
	ldrb r2, [r0, r1]
	cmp r2, #0x63
	blo _020266BE
	mov r2, #0x0
	strb r2, [r0, r1]
	bx lr
_020266BE:
	add r2, r2, #0x1
	strb r2, [r0, r1]
	bx lr
	.balign 4
_020266C4: .word 0x000009AF

	thumb_func_start FUN_020266C8
FUN_020266C8: ; 0x020266C8
	ldr r1, _020266D0 ; =0x000009AF
	ldrb r0, [r0, r1]
	bx lr
	nop
_020266D0: .word 0x000009AF

	thumb_func_start FUN_020266D4
FUN_020266D4: ; 0x020266D4
	ldr r3, _020266DC ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x94
	bx r3
	.balign 4
_020266DC: .word MI_CpuFill8

	thumb_func_start FUN_020266E0
FUN_020266E0: ; 0x020266E0
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x2d
	bl MI_CpuFill8
	add r0, r4, #0x0
	add r0, #0x2d
	mov r1, #0x0
	mov r2, #0x20
	bl MI_CpuFill8
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x8c
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x8e
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x90
	strb r1, [r0, #0x0]
	add r4, #0x91
	strb r1, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02026714
FUN_02026714: ; 0x02026714
	mov r1, #0x0
	add r0, #0x91
	strb r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202671C
FUN_0202671C: ; 0x0202671C
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	cmp r4, #0x20
	blt _0202672E
	bl ErrorHandling
_0202672E:
	cmp r6, #0x20
	blt _02026736
	bl ErrorHandling
_02026736:
	ldr r0, [sp, #0x18]
	cmp r0, #0x20
	blt _02026740
	bl ErrorHandling
_02026740:
	cmp r5, #0x0
	bne _02026748
	bl ErrorHandling
_02026748:
	cmp r4, #0x0
	beq _02026774
	cmp r4, #0x10
	bge _02026762
	sub r1, r4, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	strb r6, [r5, r0]
	ldr r1, [sp, #0x18]
	add r0, r5, r0
	strb r1, [r0, #0x1]
	strb r7, [r0, #0x2]
	pop {r3-r7, pc}
_02026762:
	sub r4, #0x10
	lsl r2, r4, #0x1
	add r0, r5, r2
	add r0, #0x2d
	strb r6, [r0, #0x0]
	add r0, r5, r2
	ldr r1, [sp, #0x18]
	add r0, #0x2e
	strb r1, [r0, #0x0]
_02026774:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026778
FUN_02026778: ; 0x02026778
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	bl FUN_020267C4
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r3, r7, #0x0
	str r4, [sp, #0x0]
	bl FUN_0202671C
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026798
FUN_02026798: ; 0x02026798
	add r0, #0x88
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blt _020267A8
	mov r0, #0x5
	bx lr
_020267A8:
	cmp r0, #0xa
	blt _020267B0
	mov r0, #0x4
	bx lr
_020267B0:
	cmp r0, #0x3
	blt _020267B8
	mov r0, #0x3
	bx lr
_020267B8:
	cmp r0, #0x1
	blt _020267C0
	mov r0, #0x2
	bx lr
_020267C0:
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_020267C4
FUN_020267C4: ; 0x020267C4
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x20
	blt _020267D2
	bl ErrorHandling
_020267D2:
	cmp r5, #0x0
	bne _020267DE
	add r0, r4, #0x0
	bl FUN_02026798
	pop {r3-r5, pc}
_020267DE:
	cmp r5, #0x10
	bge _020267EE
	sub r1, r5, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	add r0, r4, r0
	ldrb r0, [r0, #0x2]
	pop {r3-r5, pc}
_020267EE:
	sub r5, #0x10
	lsl r1, r5, #0x1
	add r0, r4, r1
	add r0, #0x2d
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202680A
	add r0, r4, r1
	add r0, #0x2e
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202680A
	mov r0, #0x6
	pop {r3-r5, pc}
_0202680A:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026810
FUN_02026810: ; 0x02026810
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x20
	blt _0202681E
	bl ErrorHandling
_0202681E:
	cmp r5, #0x0
	bne _02026826
	mov r0, #0xf
	pop {r3-r5, pc}
_02026826:
	cmp r5, #0x10
	bge _02026834
	sub r1, r5, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	ldrb r0, [r4, r0]
	pop {r3-r5, pc}
_02026834:
	sub r5, #0x10
	lsl r0, r5, #0x1
	add r0, r4, r0
	add r0, #0x2d
	ldrb r0, [r0, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02026840
FUN_02026840: ; 0x02026840
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x20
	blt _0202684E
	bl ErrorHandling
_0202684E:
	cmp r5, #0x0
	bne _02026856
	mov r0, #0xc
	pop {r3-r5, pc}
_02026856:
	cmp r5, #0x10
	bge _02026866
	sub r1, r5, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	add r0, r4, r0
	ldrb r0, [r0, #0x1]
	pop {r3-r5, pc}
_02026866:
	sub r5, #0x10
	lsl r0, r5, #0x1
	add r0, r4, r0
	add r0, #0x2e
	ldrb r0, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026874
FUN_02026874: ; 0x02026874
	add r0, #0x88
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blo _02026884
	mov r0, #0x0
	bx lr
_02026884:
	cmp r0, #0xa
	blo _0202688C
	mov r0, #0x6
	bx lr
_0202688C:
	cmp r0, #0x3
	blo _02026894
	mov r0, #0xb
	bx lr
_02026894:
	cmp r0, #0x1
	blo _0202689C
	mov r0, #0xf
	bx lr
_0202689C:
	mov r0, #0x10
	bx lr

	thumb_func_start FUN_020268A0
FUN_020268A0: ; 0x020268A0
	add r0, #0x88
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blo _020268B0
	mov r0, #0xf
	bx lr
_020268B0:
	cmp r0, #0xa
	blo _020268B8
	mov r0, #0xf
	bx lr
_020268B8:
	cmp r0, #0x3
	blo _020268C0
	mov r0, #0xf
	bx lr
_020268C0:
	cmp r0, #0x1
	blo _020268C8
	mov r0, #0xc
	bx lr
_020268C8:
	mov r0, #0xa
	bx lr

	thumb_func_start FUN_020268CC
FUN_020268CC: ; 0x020268CC
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_020268D4
FUN_020268D4: ; 0x020268D4
	push {r3, lr}
	bl FUN_020269A0
	cmp r0, #0x4
	bne _020268E2
	mov r0, #0x1
	pop {r3, pc}
_020268E2:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020268E8
FUN_020268E8: ; 0x020268E8
	ldr r3, [r0, #0x0]
	ldr r2, _020268F8 ; =0xFFF00000
	and r3, r2
	ldr r2, _020268FC ; =0x000FFFFF
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020268F8: .word 0xFFF00000
_020268FC: .word 0x000FFFFF

	thumb_func_start FUN_02026900
FUN_02026900: ; 0x02026900
	ldr r0, [r0, #0x4]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026908
FUN_02026908: ; 0x02026908
	push {r3-r4}
	ldr r2, [r0, #0x4]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _0202692C ; =0x000F423F
	cmp r4, r1
	bhs _02026926
	ldr r1, _02026930 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026934 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x4]
_02026926:
	pop {r3-r4}
	bx lr
	nop
_0202692C: .word 0x000F423F
_02026930: .word 0xFFF00000
_02026934: .word 0x000FFFFF

	thumb_func_start FUN_02026938
FUN_02026938: ; 0x02026938
	ldr r0, [r0, #0x8]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026940
FUN_02026940: ; 0x02026940
	push {r3-r4}
	ldr r2, [r0, #0x8]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026964 ; =0x000F423F
	cmp r4, r1
	bhs _0202695E
	ldr r1, _02026968 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _0202696C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x8]
_0202695E:
	pop {r3-r4}
	bx lr
	nop
_02026964: .word 0x000F423F
_02026968: .word 0xFFF00000
_0202696C: .word 0x000FFFFF

	thumb_func_start FUN_02026970
FUN_02026970: ; 0x02026970
	push {r3-r4}
	ldr r2, [r0, #0xc]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026994 ; =0x000F423F
	cmp r4, r1
	bhs _0202698E
	ldr r1, _02026998 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _0202699C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0xc]
_0202698E:
	pop {r3-r4}
	bx lr
	nop
_02026994: .word 0x000F423F
_02026998: .word 0xFFF00000
_0202699C: .word 0x000FFFFF

	thumb_func_start FUN_020269A0
FUN_020269A0: ; 0x020269A0
	ldr r0, [r0, #0x38]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blt _020269AE
	mov r0, #0x4
	bx lr
_020269AE:
	cmp r0, #0xa
	blt _020269B6
	mov r0, #0x3
	bx lr
_020269B6:
	cmp r0, #0x3
	blt _020269BE
	mov r0, #0x2
	bx lr
_020269BE:
	cmp r0, #0x1
	blt _020269C6
	mov r0, #0x1
	bx lr
_020269C6:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_020269CC
FUN_020269CC: ; 0x020269CC
	ldr r0, [r0, #0x38]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_020269D4
FUN_020269D4: ; 0x020269D4
	push {r3-r4}
	ldr r2, [r0, #0x38]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _020269F8 ; =0x000F423F
	cmp r4, r1
	bhs _020269F2
	ldr r1, _020269FC ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026A00 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x38]
_020269F2:
	pop {r3-r4}
	bx lr
	nop
_020269F8: .word 0x000F423F
_020269FC: .word 0xFFF00000
_02026A00: .word 0x000FFFFF

	thumb_func_start FUN_02026A04
FUN_02026A04: ; 0x02026A04
	ldr r0, [r0, #0x10]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026A0C
FUN_02026A0C: ; 0x02026A0C
	push {r4-r5}
	cmp r1, #0x0
	ble _02026A2C
	ldr r4, [r0, #0x10]
	lsl r2, r4, #0xc
	lsr r5, r2, #0xc
	ldr r2, _02026A44 ; =0x000F423F
	sub r3, r2, r1
	cmp r5, r3
	bls _02026A2C
	ldr r1, _02026A48 ; =0xFFF00000
	and r1, r4
	orr r1, r2
	str r1, [r0, #0x10]
	pop {r4-r5}
	bx lr
_02026A2C:
	ldr r3, [r0, #0x10]
	ldr r2, _02026A48 ; =0xFFF00000
	and r2, r3
	lsl r3, r3, #0xc
	lsr r3, r3, #0xc
	add r3, r3, r1
	ldr r1, _02026A4C ; =0x000FFFFF
	and r1, r3
	orr r1, r2
	str r1, [r0, #0x10]
	pop {r4-r5}
	bx lr
	.balign 4
_02026A44: .word 0x000F423F
_02026A48: .word 0xFFF00000
_02026A4C: .word 0x000FFFFF

	thumb_func_start FUN_02026A50
FUN_02026A50: ; 0x02026A50
	ldr r0, [r0, #0x14]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026A58
FUN_02026A58: ; 0x02026A58
	push {r4-r5}
	cmp r1, #0x0
	ble _02026A78
	ldr r4, [r0, #0x14]
	lsl r2, r4, #0xc
	lsr r5, r2, #0xc
	ldr r2, _02026A90 ; =0x000F423F
	sub r3, r2, r1
	cmp r5, r3
	bls _02026A78
	ldr r1, _02026A94 ; =0xFFF00000
	and r1, r4
	orr r1, r2
	str r1, [r0, #0x14]
	pop {r4-r5}
	bx lr
_02026A78:
	ldr r3, [r0, #0x14]
	ldr r2, _02026A94 ; =0xFFF00000
	and r2, r3
	lsl r3, r3, #0xc
	lsr r3, r3, #0xc
	add r3, r3, r1
	ldr r1, _02026A98 ; =0x000FFFFF
	and r1, r3
	orr r1, r2
	str r1, [r0, #0x14]
	pop {r4-r5}
	bx lr
	.balign 4
_02026A90: .word 0x000F423F
_02026A94: .word 0xFFF00000
_02026A98: .word 0x000FFFFF

	thumb_func_start FUN_02026A9C
FUN_02026A9C: ; 0x02026A9C
	push {r4-r5}
	cmp r1, #0x0
	ble _02026ABC
	ldr r4, [r0, #0x18]
	lsl r2, r4, #0xc
	lsr r5, r2, #0xc
	ldr r2, _02026AD4 ; =0x000F423F
	sub r3, r2, r1
	cmp r5, r3
	bls _02026ABC
	ldr r1, _02026AD8 ; =0xFFF00000
	and r1, r4
	orr r1, r2
	str r1, [r0, #0x18]
	pop {r4-r5}
	bx lr
_02026ABC:
	ldr r3, [r0, #0x18]
	ldr r2, _02026AD8 ; =0xFFF00000
	and r2, r3
	lsl r3, r3, #0xc
	lsr r3, r3, #0xc
	add r3, r3, r1
	ldr r1, _02026ADC ; =0x000FFFFF
	and r1, r3
	orr r1, r2
	str r1, [r0, #0x18]
	pop {r4-r5}
	bx lr
	.balign 4
_02026AD4: .word 0x000F423F
_02026AD8: .word 0xFFF00000
_02026ADC: .word 0x000FFFFF

	thumb_func_start FUN_02026AE0
FUN_02026AE0: ; 0x02026AE0
	ldr r0, [r0, #0x1c]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026AE8
FUN_02026AE8: ; 0x02026AE8
	push {r3-r4}
	ldr r2, [r0, #0x1c]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026B0C ; =0x000F423F
	cmp r4, r1
	bhs _02026B06
	ldr r1, _02026B10 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026B14 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x1c]
_02026B06:
	pop {r3-r4}
	bx lr
	nop
_02026B0C: .word 0x000F423F
_02026B10: .word 0xFFF00000
_02026B14: .word 0x000FFFFF

	thumb_func_start FUN_02026B18
FUN_02026B18: ; 0x02026B18
	ldr r0, [r0, #0x20]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026B20
FUN_02026B20: ; 0x02026B20
	push {r3-r4}
	ldr r2, [r0, #0x20]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026B44 ; =0x000F423F
	cmp r4, r1
	bhs _02026B3E
	ldr r1, _02026B48 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026B4C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x20]
_02026B3E:
	pop {r3-r4}
	bx lr
	nop
_02026B44: .word 0x000F423F
_02026B48: .word 0xFFF00000
_02026B4C: .word 0x000FFFFF

	thumb_func_start FUN_02026B50
FUN_02026B50: ; 0x02026B50
	ldr r0, [r0, #0x24]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026B58
FUN_02026B58: ; 0x02026B58
	push {r3-r4}
	ldr r2, [r0, #0x24]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026B7C ; =0x000F423F
	cmp r4, r1
	bhs _02026B76
	ldr r1, _02026B80 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026B84 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x24]
_02026B76:
	pop {r3-r4}
	bx lr
	nop
_02026B7C: .word 0x000F423F
_02026B80: .word 0xFFF00000
_02026B84: .word 0x000FFFFF

	thumb_func_start FUN_02026B88
FUN_02026B88: ; 0x02026B88
	ldr r0, [r0, #0x28]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026B90
FUN_02026B90: ; 0x02026B90
	push {r3-r4}
	ldr r2, [r0, #0x28]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026BB4 ; =0x000F423F
	cmp r4, r1
	bhs _02026BAE
	ldr r1, _02026BB8 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026BBC ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x28]
_02026BAE:
	pop {r3-r4}
	bx lr
	nop
_02026BB4: .word 0x000F423F
_02026BB8: .word 0xFFF00000
_02026BBC: .word 0x000FFFFF

	thumb_func_start FUN_02026BC0
FUN_02026BC0: ; 0x02026BC0
	ldr r0, [r0, #0x2c]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026BC8
FUN_02026BC8: ; 0x02026BC8
	push {r3-r4}
	ldr r2, [r0, #0x2c]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026BEC ; =0x000F423F
	cmp r4, r1
	bhs _02026BE6
	ldr r1, _02026BF0 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026BF4 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x2c]
_02026BE6:
	pop {r3-r4}
	bx lr
	nop
_02026BEC: .word 0x000F423F
_02026BF0: .word 0xFFF00000
_02026BF4: .word 0x000FFFFF

	thumb_func_start FUN_02026BF8
FUN_02026BF8: ; 0x02026BF8
	ldr r0, [r0, #0x30]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026C00
FUN_02026C00: ; 0x02026C00
	push {r3-r4}
	ldr r2, [r0, #0x30]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026C24 ; =0x000F423F
	cmp r4, r1
	bhs _02026C1E
	ldr r1, _02026C28 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026C2C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x30]
_02026C1E:
	pop {r3-r4}
	bx lr
	nop
_02026C24: .word 0x000F423F
_02026C28: .word 0xFFF00000
_02026C2C: .word 0x000FFFFF

	thumb_func_start FUN_02026C30
FUN_02026C30: ; 0x02026C30
	ldr r0, [r0, #0x34]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026C38
FUN_02026C38: ; 0x02026C38
	push {r3-r4}
	ldr r2, [r0, #0x34]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026C5C ; =0x000F423F
	cmp r4, r1
	bhs _02026C56
	ldr r1, _02026C60 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026C64 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x34]
_02026C56:
	pop {r3-r4}
	bx lr
	nop
_02026C5C: .word 0x000F423F
_02026C60: .word 0xFFF00000
_02026C64: .word 0x000FFFFF

	thumb_func_start FUN_02026C68
FUN_02026C68: ; 0x02026C68
	push {r3-r4}
	add r4, r0, #0x0
	add r4, #0x8c
	strh r1, [r4, #0x0]
	add r1, r0, #0x0
	add r1, #0x8e
	strh r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x90
	strb r3, [r1, #0x0]
	mov r1, #0x1
	add r0, #0x91
	strb r1, [r0, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_02026C88
FUN_02026C88: ; 0x02026C88
	add r0, #0x8c
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026C90
FUN_02026C90: ; 0x02026C90
	add r0, #0x8e
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026C98
FUN_02026C98: ; 0x02026C98
	add r0, #0x90
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026CA0
FUN_02026CA0: ; 0x02026CA0
	add r0, #0x91
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026CA8
FUN_02026CA8: ; 0x02026CA8
	ldr r3, _02026CB0 ; =FUN_02022610
	mov r1, #0xc
	bx r3
	nop
_02026CB0: .word FUN_02022610

	thumb_func_start FUN_02026CB4
FUN_02026CB4: ; 0x02026CB4
	push {r3, lr}
	mov r1, #0xc
	bl FUN_02022610
	add r0, #0x50
	pop {r3, pc}

	thumb_func_start FUN_02026CC0
FUN_02026CC0: ; 0x02026CC0
	add r0, #0x50
	bx lr

	thumb_func_start FUN_02026CC4
FUN_02026CC4: ; 0x02026CC4
	ldr r3, _02026CCC ; =FUN_02022610
	mov r1, #0xc
	bx r3
	nop
_02026CCC: .word FUN_02022610

	thumb_func_start FUN_02026CD0
FUN_02026CD0: ; 0x02026CD0
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	add r7, r3, #0x0
	bl FUN_020671BC
	add r2, r5, #0x0
	strh r0, [r5, #0x8]
	add r0, r4, #0x0
	mov r1, #0x74
	add r2, #0xa
	bl FUN_020671BC
	mov r1, #0x0
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl FUN_020671BC
	str r0, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [r5, #0x4]
	add r0, r4, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x33
	strb r0, [r1, #0x0]
	add r0, r5, #0x0
	add r0, #0x31
	strb r6, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x32
	strb r7, [r0, #0x0]
	add r1, sp, #0x8
	mov r0, #0x10
	ldrsb r0, [r1, r0]
	add r5, #0x30
	strb r0, [r5, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026D34
FUN_02026D34: ; 0x02026D34
	push {r3-r6, lr}
	sub sp, #0xc
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r4, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x8
	bl MOD17_021DB858
	add r0, r4, #0x0
	bl MOD17_021DB7E8
	add r4, r0, #0x0
	mov r0, #0x1
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x8
	cmp r1, r0
	blt _02026D5E
	bl ErrorHandling
_02026D5E:
	mov r0, #0x1
	ldr r1, [sp, #0x8]
	lsl r0, r0, #0x8
	cmp r1, r0
	blt _02026D6C
	bl ErrorHandling
_02026D6C:
	mov r0, #0x7f
	mvn r0, r0
	cmp r4, r0
	bgt _02026D78
	bl ErrorHandling
_02026D78:
	lsl r0, r4, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02026CD0
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02026D98
FUN_02026D98: ; 0x02026D98
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r1, r5, #0x0
	add r4, r2, #0x0
	add r1, #0x20
	mov r2, #0x8
	bl FUN_02021EF0
	add r5, #0x34
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02026DB0
FUN_02026DB0: ; 0x02026DB0
	strb r1, [r0, #0x0]
	ldr r1, _02026DC0 ; =0xFFFFFFF0
	strb r2, [r0, #0x1]
	strb r3, [r0, #0x2]
	add r1, sp
	ldrb r1, [r1, #0x10]
	strb r1, [r0, #0x3]
	bx lr
	.balign 4
_02026DC0: .word 0xFFFFFFF0

	thumb_func_start FUN_02026DC4
FUN_02026DC4: ; 0x02026DC4
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	cmp r4, #0x3d
	blo _02026DD4
	bl ErrorHandling
_02026DD4:
	lsr r2, r4, #0x1f
	lsl r1, r4, #0x1d
	sub r1, r1, r2
	mov r0, #0x1d
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1a
	lsr r1, r0, #0x18
	lsr r0, r4, #0x3
	lsl r0, r0, #0x18
	mov r2, #0xf
	lsr r0, r0, #0x16
	lsl r2, r1
	ldr r3, [r5, r0]
	mvn r2, r2
	and r2, r3
	str r2, [r5, r0]
	add r2, r6, #0x0
	ldr r3, [r5, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r5, r0]
	pop {r4-r6, pc}

	thumb_func_start FUN_02026E08
FUN_02026E08: ; 0x02026E08
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3d
	blo _02026E16
	bl ErrorHandling
_02026E16:
	lsr r3, r4, #0x1f
	lsl r2, r4, #0x1d
	lsr r0, r4, #0x3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x16
	sub r2, r2, r3
	mov r1, #0x1d
	ror r2, r1
	add r1, r3, r2
	lsl r1, r1, #0x18
	ldr r0, [r5, r0]
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1a
	add r2, r0, #0x0
	lsr r1, r1, #0x18
	lsr r2, r1
	mov r0, #0xf
	and r0, r2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x9
	bls _02026E44
	mov r0, #0x9
_02026E44:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026E48
FUN_02026E48: ; 0x02026E48
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x2
	blo _02026E58
	bl ErrorHandling
_02026E58:
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1b
	sub r1, r1, r2
	mov r0, #0x1b
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	lsr r0, r6, #0x5
	lsl r0, r0, #0x18
	mov r2, #0x1
	lsr r0, r0, #0x16
	lsl r2, r1
	ldr r3, [r5, r0]
	mvn r2, r2
	and r2, r3
	str r2, [r5, r0]
	add r2, r4, #0x0
	ldr r3, [r5, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r5, r0]
	pop {r4-r6, pc}

	thumb_func_start FUN_02026E88
FUN_02026E88: ; 0x02026E88
	lsr r2, r1, #0x5
	lsl r2, r2, #0x18
	lsr r2, r2, #0x16
	ldr r3, [r0, r2]
	lsr r2, r1, #0x1f
	lsl r1, r1, #0x1b
	sub r1, r1, r2
	mov r0, #0x1b
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r3, #0x0
	lsr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
	.balign 4

	thumb_func_start FUN_02026EB0
FUN_02026EB0: ; 0x02026EB0
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x12
	bls _02026EC0
	bl ErrorHandling
_02026EC0:
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1b
	lsr r1, r0, #0x18
	lsr r0, r6, #0x2
	lsl r0, r0, #0x18
	mov r2, #0xff
	lsr r0, r0, #0x16
	lsl r2, r1
	ldr r3, [r5, r0]
	mvn r2, r2
	and r2, r3
	str r2, [r5, r0]
	add r2, r4, #0x0
	ldr r3, [r5, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r5, r0]
	pop {r4-r6, pc}

	thumb_func_start FUN_02026EF4
FUN_02026EF4: ; 0x02026EF4
	lsr r2, r1, #0x2
	lsl r2, r2, #0x18
	lsr r2, r2, #0x16
	ldr r0, [r0, r2]
	lsr r3, r1, #0x1f
	lsl r2, r1, #0x1e
	sub r2, r2, r3
	mov r1, #0x1e
	ror r2, r1
	add r1, r3, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x18
	lsr r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr

	thumb_func_start FUN_02026F18
FUN_02026F18: ; 0x02026F18
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_02026F20:
	lsl r1, r4, #0x18
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026EF4
	cmp r0, #0x12
	beq _02026F30
	add r5, r5, #0x1
_02026F30:
	add r4, r4, #0x1
	cmp r4, #0x12
	blt _02026F20
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	pop {r4-r6, pc}

	thumb_func_start FUN_02026F3C
FUN_02026F3C: ; 0x02026F3C
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0x2
	add r4, r2, #0x0
	bl FUN_02068E14
	mov r1, #0x80
	strb r1, [r5, #0x0]
	mov r1, #0x28
	sub r1, r1, r0
	mov r0, #0x8d
	sub r0, r0, r1
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x0]
	add r0, #0x28
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026F60
FUN_02026F60: ; 0x02026F60
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r6, _02026FC8 ; =0x00001234
	mov r4, #0x0
	add r5, r7, #0x0
_02026F6A:
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0x74
	bl Call_FillMemWithValue
	str r6, [r5, #0x0]
	add r4, r4, #0x1
	add r5, #0x74
	cmp r4, #0xb
	blt _02026F6A
	ldr r0, _02026FCC ; =0x000004FC
	mov r6, #0x0
	add r4, r7, r0
	add r5, r7, #0x0
_02026F86:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x98
	bl Call_FillMemWithValue
	ldr r1, _02026FC8 ; =0x00001234
	ldr r0, _02026FCC ; =0x000004FC
	add r6, r6, #0x1
	str r1, [r5, r0]
	add r4, #0x98
	add r5, #0x98
	cmp r6, #0x5
	blt _02026F86
	ldr r0, _02026FD0 ; =0x000007F4
	mov r1, #0x0
	add r0, r7, r0
	mov r2, #0x40
	bl Call_FillMemWithValue
	ldr r5, _02026FD4 ; =0x0000081C
	mov r4, #0x0
	mov r6, #0x12
_02026FB2:
	lsl r2, r4, #0x18
	add r0, r7, r5
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026EB0
	add r4, r4, #0x1
	cmp r4, #0x12
	blt _02026FB2
	pop {r3-r7, pc}
	nop
_02026FC8: .word 0x00001234
_02026FCC: .word 0x000004FC
_02026FD0: .word 0x000007F4
_02026FD4: .word 0x0000081C

	thumb_func_start FUN_02026FD8
FUN_02026FD8: ; 0x02026FD8
	ldr r0, _02026FDC ; =0x00000834
	bx lr
	.balign 4
_02026FDC: .word 0x00000834

	thumb_func_start FUN_02026FE0
FUN_02026FE0: ; 0x02026FE0
	mov r0, #0x74
	bx lr

	thumb_func_start FUN_02026FE4
FUN_02026FE4: ; 0x02026FE4
	mov r0, #0x98
	bx lr

	thumb_func_start FUN_02026FE8
FUN_02026FE8: ; 0x02026FE8
	push {r4, lr}
	mov r1, #0x98
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x98
	add r4, r0, #0x0
	bl Call_FillMemWithValue
	ldr r0, _02027004 ; =0x00001234
	str r0, [r4, #0x0]
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_02027004: .word 0x00001234

	thumb_func_start FUN_02027008
FUN_02027008: ; 0x02027008
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	cmp r6, #0xb
	blt _02027016
	bl ErrorHandling
_02027016:
	mov r0, #0x74
	add r4, r6, #0x0
	mul r4, r0
	ldr r1, [r5, r4]
	ldr r0, _0202703C ; =0x00001234
	cmp r1, r0
	beq _0202702A
	ldr r0, _02027040 ; =0x00002345
	cmp r1, r0
	bne _0202702E
_0202702A:
	mov r0, #0x1
	b _02027030
_0202702E:
	mov r0, #0x0
_02027030:
	cmp r0, #0x0
	bne _02027038
	bl ErrorHandling
_02027038:
	add r0, r5, r4
	pop {r4-r6, pc}
	.balign 4
_0202703C: .word 0x00001234
_02027040: .word 0x00002345

	thumb_func_start FUN_02027044
FUN_02027044: ; 0x02027044
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	cmp r6, #0x5
	blt _02027052
	bl ErrorHandling
_02027052:
	mov r0, #0x98
	add r4, r6, #0x0
	mul r4, r0
	ldr r0, _02027080 ; =0x000004FC
	add r1, r5, r4
	ldr r1, [r1, r0]
	ldr r0, _02027084 ; =0x00001234
	cmp r1, r0
	beq _0202706A
	ldr r0, _02027088 ; =0x00002345
	cmp r1, r0
	bne _0202706E
_0202706A:
	mov r0, #0x1
	b _02027070
_0202706E:
	mov r0, #0x0
_02027070:
	cmp r0, #0x0
	bne _02027078
	bl ErrorHandling
_02027078:
	ldr r0, _02027080 ; =0x000004FC
	add r0, r5, r0
	add r0, r0, r4
	pop {r4-r6, pc}
	.balign 4
_02027080: .word 0x000004FC
_02027084: .word 0x00001234
_02027088: .word 0x00002345

	thumb_func_start FUN_0202708C
FUN_0202708C: ; 0x0202708C
	ldr r1, _02027094 ; =0x000007F4
	add r0, r0, r1
	bx lr
	nop
_02027094: .word 0x000007F4

	thumb_func_start FUN_02027098
FUN_02027098: ; 0x02027098
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xb
	blt _020270A6
	bl ErrorHandling
_020270A6:
	mov r0, #0x74
	mul r0, r4
	add r0, r5, r0
	bl FUN_0202729C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020270B4
FUN_020270B4: ; 0x020270B4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x5
	blt _020270C2
	bl ErrorHandling
_020270C2:
	ldr r0, _020270D4 ; =0x000004FC
	add r1, r5, r0
	mov r0, #0x98
	mul r0, r4
	add r0, r1, r0
	bl FUN_020276D8
	pop {r3-r5, pc}
	nop
_020270D4: .word 0x000004FC

	thumb_func_start FUN_020270D8
FUN_020270D8: ; 0x020270D8
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r2, #0x0
	mov r4, #0x1
	bl FUN_02027114
	cmp r6, #0x3d
	bhs _020270F2
	add r0, r0, r5
	cmp r0, #0x9
	bls _020270FA
	mov r4, #0x0
	b _020270FA
_020270F2:
	add r0, r0, r5
	cmp r0, #0x1
	bls _020270FA
	mov r4, #0x0
_020270FA:
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02027100
FUN_02027100: ; 0x02027100
	push {r3, lr}
	bl FUN_0202714C
	cmp r0, #0x12
	beq _0202710E
	mov r0, #0x1
	pop {r3, pc}
_0202710E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02027114
FUN_02027114: ; 0x02027114
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x64
	blo _02027122
	bl ErrorHandling
_02027122:
	cmp r5, #0x3d
	bhs _02027132
	lsl r1, r5, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E08
	pop {r3-r5, pc}
_02027132:
	bhs _02027138
	bl ErrorHandling
_02027138:
	sub r5, #0x3d
	lsl r0, r5, #0x18
	lsr r1, r0, #0x18
	add r4, #0x20
	lsl r1, r1, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E88
	pop {r3-r5, pc}

	thumb_func_start FUN_0202714C
FUN_0202714C: ; 0x0202714C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x12
	blo _0202715A
	bl ErrorHandling
_0202715A:
	add r5, #0x28
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026EF4
	pop {r3-r5, pc}

	thumb_func_start FUN_02027168
FUN_02027168: ; 0x02027168
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_02027170:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02027114
	add r4, r4, #0x1
	add r5, r5, r0
	cmp r4, #0x64
	blt _02027170
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02027184
FUN_02027184: ; 0x02027184
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_0202718C:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0202714C
	cmp r0, #0x12
	beq _0202719A
	add r5, r5, #0x1
_0202719A:
	add r4, r4, #0x1
	cmp r4, #0x12
	blt _0202718C
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020271A4
FUN_020271A4: ; 0x020271A4
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x64
	blo _020271B4
	bl ErrorHandling
_020271B4:
	cmp r4, #0x3d
	bhs _020271DA
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E08
	add r0, r0, r6
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, #0x9
	bls _020271CE
	mov r1, #0x9
_020271CE:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026DC4
	pop {r4-r6, pc}
_020271DA:
	add r0, r5, #0x0
	lsl r1, r4, #0x18
	add r0, #0x20
	lsr r1, r1, #0x18
	bl FUN_02026E88
	add r0, r0, r6
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x1
	bls _020271F2
	mov r6, #0x1
_020271F2:
	cmp r4, #0x3d
	bhs _020271FA
	bl ErrorHandling
_020271FA:
	sub r4, #0x3d
	lsl r0, r4, #0x18
	lsr r2, r0, #0x18
	add r5, #0x20
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026E48
	pop {r4-r6, pc}

	thumb_func_start FUN_02027210
FUN_02027210: ; 0x02027210
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x64
	blo _02027220
	bl ErrorHandling
_02027220:
	cmp r4, #0x3d
	bhs _02027248
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E08
	cmp r0, r6
	bls _0202723A
	sub r0, r0, r6
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	b _0202723C
_0202723A:
	mov r1, #0x0
_0202723C:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026DC4
	pop {r4-r6, pc}
_02027248:
	bhs _0202724E
	bl ErrorHandling
_0202724E:
	sub r4, #0x3d
	lsl r0, r4, #0x18
	lsr r2, r0, #0x18
	add r5, #0x20
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	mov r1, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026E48
	pop {r4-r6, pc}

	thumb_func_start FUN_02027264
FUN_02027264: ; 0x02027264
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x12
	blo _02027272
	bl ErrorHandling
_02027272:
	add r0, r5, #0x0
	lsl r1, r4, #0x18
	add r0, #0x28
	lsr r1, r1, #0x18
	bl FUN_02026EF4
	cmp r0, #0x12
	bne _02027298
	add r0, r5, #0x0
	add r0, #0x28
	bl FUN_02026F18
	lsl r2, r4, #0x18
	add r5, #0x28
	add r1, r0, #0x0
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026EB0
_02027298:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202729C
FUN_0202729C: ; 0x0202729C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _020272CC ; =0x00001234
	cmp r1, r0
	beq _020272AE
	ldr r0, _020272D0 ; =0x00002345
	cmp r1, r0
	bne _020272B2
_020272AE:
	mov r0, #0x1
	b _020272B4
_020272B2:
	mov r0, #0x0
_020272B4:
	cmp r0, #0x0
	bne _020272BC
	bl ErrorHandling
_020272BC:
	ldr r1, [r4, #0x0]
	ldr r0, _020272D0 ; =0x00002345
	cmp r1, r0
	bne _020272C8
	mov r0, #0x1
	pop {r4, pc}
_020272C8:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_020272CC: .word 0x00001234
_020272D0: .word 0x00002345

	thumb_func_start FUN_020272D4
FUN_020272D4: ; 0x020272D4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027304 ; =0x00001234
	cmp r1, r0
	beq _020272E6
	ldr r0, _02027308 ; =0x00002345
	cmp r1, r0
	bne _020272EA
_020272E6:
	mov r0, #0x1
	b _020272EC
_020272EA:
	mov r0, #0x0
_020272EC:
	cmp r0, #0x0
	bne _020272F4
	bl ErrorHandling
_020272F4:
	ldr r0, _02027308 ; =0x00002345
	str r0, [r4, #0x0]
	ldr r0, _0202730C ; =0x020ECAC4
	add r4, #0x71
	ldrb r0, [r0, #0x0]
	strb r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02027304: .word 0x00001234
_02027308: .word 0x00002345
_0202730C: .word 0x020ECAC4

	thumb_func_start FUN_02027310
FUN_02027310: ; 0x02027310
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027340 ; =0x00001234
	cmp r1, r0
	beq _02027322
	ldr r0, _02027344 ; =0x00002345
	cmp r1, r0
	bne _02027326
_02027322:
	mov r0, #0x1
	b _02027328
_02027326:
	mov r0, #0x0
_02027328:
	cmp r0, #0x0
	bne _02027330
	bl ErrorHandling
_02027330:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x74
	bl Call_FillMemWithValue
	ldr r0, _02027340 ; =0x00001234
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4
_02027340: .word 0x00001234
_02027344: .word 0x00002345

	thumb_func_start FUN_02027348
FUN_02027348: ; 0x02027348
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027378 ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _0202735E
	ldr r0, _0202737C ; =0x00002345
	cmp r1, r0
	bne _02027362
_0202735E:
	mov r0, #0x1
	b _02027364
_02027362:
	mov r0, #0x0
_02027364:
	cmp r0, #0x0
	bne _0202736C
	bl ErrorHandling
_0202736C:
	add r0, r5, #0x4
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D34
	pop {r4-r6, pc}
	.balign 4
_02027378: .word 0x00001234
_0202737C: .word 0x00002345

	thumb_func_start FUN_02027380
FUN_02027380: ; 0x02027380
	push {r4-r7, lr}
	sub sp, #0x14
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x4]
	add r6, r2, #0x0
	bl FUN_02013ECC
	add r1, sp, #0xc
	strh r0, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x2]
	ldrh r0, [r1, #0x0]
	strh r0, [r1, #0x4]
	ldrh r0, [r1, #0x2]
	strh r0, [r1, #0x6]
	ldr r0, [r4, #0x4]
	bl FUN_02013F00
	str r0, [sp, #0x8]
	cmp r6, #0xa
	blt _020273B0
	bl ErrorHandling
_020273B0:
	add r1, sp, #0xc
	mov r0, #0x4
	ldrsh r1, [r1, r0]
	add r0, #0xfc
	cmp r1, r0
	blt _020273C0
	bl ErrorHandling
_020273C0:
	add r1, sp, #0xc
	mov r0, #0x6
	ldrsh r7, [r1, r0]
	add r0, #0xfa
	cmp r7, r0
	blt _020273D0
	bl ErrorHandling
_020273D0:
	mov r1, #0x7f
	ldr r0, [sp, #0x8]
	mvn r1, r1
	cmp r0, r1
	bgt _020273DE
	bl ErrorHandling
_020273DE:
	mov r0, #0x1
	lsl r0, r6
	ldr r1, [r5, #0x3c]
	str r0, [sp, #0x4]
	tst r0, r1
	beq _020273EE
	bl ErrorHandling
_020273EE:
	ldr r1, [r5, #0x0]
	ldr r0, _02027440 ; =0x00001234
	cmp r1, r0
	beq _020273FC
	ldr r0, _02027444 ; =0x00002345
	cmp r1, r0
	bne _02027400
_020273FC:
	mov r0, #0x1
	b _02027402
_02027400:
	mov r0, #0x0
_02027402:
	cmp r0, #0x0
	bne _0202740A
	bl ErrorHandling
_0202740A:
	ldr r0, [sp, #0x8]
	add r1, r5, #0x0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r3, sp, #0xc
	mov r2, #0x4
	ldrsh r2, [r3, r2]
	lsl r3, r7, #0x18
	add r1, #0x48
	lsl r0, r6, #0x2
	add r0, r1, r0
	ldr r1, [r4, #0x0]
	lsl r2, r2, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02026DB0
	ldr r1, [r5, #0x3c]
	ldr r0, [sp, #0x4]
	orr r0, r1
	str r0, [r5, #0x3c]
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02027440: .word 0x00001234
_02027444: .word 0x00002345

	thumb_func_start FUN_02027448
FUN_02027448: ; 0x02027448
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027470 ; =0x00001234
	cmp r1, r0
	beq _0202745C
	ldr r0, _02027474 ; =0x00002345
	cmp r1, r0
	bne _02027460
_0202745C:
	mov r0, #0x1
	b _02027462
_02027460:
	mov r0, #0x0
_02027462:
	cmp r0, #0x0
	bne _0202746A
	bl ErrorHandling
_0202746A:
	add r5, #0x70
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4
_02027470: .word 0x00001234
_02027474: .word 0x00002345

	thumb_func_start FUN_02027478
FUN_02027478: ; 0x02027478
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020274B0 ; =0x00001234
	cmp r1, r0
	beq _0202748C
	ldr r0, _020274B4 ; =0x00002345
	cmp r1, r0
	bne _02027490
_0202748C:
	mov r0, #0x1
	b _02027492
_02027490:
	mov r0, #0x0
_02027492:
	cmp r0, #0x0
	bne _0202749A
	bl ErrorHandling
_0202749A:
	add r0, r5, #0x0
	add r0, #0x40
	bl FUN_02013724
	add r5, #0x40
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_02013998
	pop {r3-r5, pc}
	.balign 4
_020274B0: .word 0x00001234
_020274B4: .word 0x00002345

	thumb_func_start FUN_020274B8
FUN_020274B8: ; 0x020274B8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020274E8 ; =0x00001234
	cmp r1, r0
	beq _020274CC
	ldr r0, _020274EC ; =0x00002345
	cmp r1, r0
	bne _020274D0
_020274CC:
	mov r0, #0x1
	b _020274D2
_020274D0:
	mov r0, #0x0
_020274D2:
	cmp r0, #0x0
	bne _020274DA
	bl ErrorHandling
_020274DA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x74
	bl memcpy
	pop {r3-r5, pc}
	nop
_020274E8: .word 0x00001234
_020274EC: .word 0x00002345

	thumb_func_start FUN_020274F0
FUN_020274F0: ; 0x020274F0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027520 ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _02027506
	ldr r0, _02027524 ; =0x00002345
	cmp r1, r0
	bne _0202750A
_02027506:
	mov r0, #0x1
	b _0202750C
_0202750A:
	mov r0, #0x0
_0202750C:
	cmp r0, #0x0
	bne _02027514
	bl ErrorHandling
_02027514:
	add r0, r5, #0x4
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D98
	pop {r4-r6, pc}
	.balign 4
_02027520: .word 0x00001234
_02027524: .word 0x00002345

	thumb_func_start FUN_02027528
FUN_02027528: ; 0x02027528
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xa
	blt _02027536
	bl ErrorHandling
_02027536:
	ldr r1, [r5, #0x0]
	ldr r0, _0202755C ; =0x00001234
	cmp r1, r0
	beq _02027544
	ldr r0, _02027560 ; =0x00002345
	cmp r1, r0
	bne _02027548
_02027544:
	mov r0, #0x1
	b _0202754A
_02027548:
	mov r0, #0x0
_0202754A:
	cmp r0, #0x0
	bne _02027552
	bl ErrorHandling
_02027552:
	mov r0, #0x1
	ldr r1, [r5, #0x3c]
	lsl r0, r4
	and r0, r1
	pop {r3-r5, pc}
	.balign 4
_0202755C: .word 0x00001234
_02027560: .word 0x00002345

	thumb_func_start FUN_02027564
FUN_02027564: ; 0x02027564
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027588 ; =0x00001234
	cmp r1, r0
	beq _02027576
	ldr r0, _0202758C ; =0x00002345
	cmp r1, r0
	bne _0202757A
_02027576:
	mov r0, #0x1
	b _0202757C
_0202757A:
	mov r0, #0x0
_0202757C:
	cmp r0, #0x0
	bne _02027584
	bl ErrorHandling
_02027584:
	add r0, r4, #0x4
	pop {r4, pc}
	.balign 4
_02027588: .word 0x00001234
_0202758C: .word 0x00002345

	thumb_func_start FUN_02027590
FUN_02027590: ; 0x02027590
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xa
	blt _0202759E
	bl ErrorHandling
_0202759E:
	mov r0, #0x1
	ldr r1, [r5, #0x3c]
	lsl r0, r4
	tst r0, r1
	bne _020275AC
	bl ErrorHandling
_020275AC:
	ldr r1, [r5, #0x0]
	ldr r0, _020275D0 ; =0x00001234
	cmp r1, r0
	beq _020275BA
	ldr r0, _020275D4 ; =0x00002345
	cmp r1, r0
	bne _020275BE
_020275BA:
	mov r0, #0x1
	b _020275C0
_020275BE:
	mov r0, #0x0
_020275C0:
	cmp r0, #0x0
	bne _020275C8
	bl ErrorHandling
_020275C8:
	add r5, #0x48
	lsl r0, r4, #0x2
	add r0, r5, r0
	pop {r3-r5, pc}
	.balign 4
_020275D0: .word 0x00001234
_020275D4: .word 0x00002345

	thumb_func_start FUN_020275D8
FUN_020275D8: ; 0x020275D8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027600 ; =0x00001234
	cmp r1, r0
	beq _020275EA
	ldr r0, _02027604 ; =0x00002345
	cmp r1, r0
	bne _020275EE
_020275EA:
	mov r0, #0x1
	b _020275F0
_020275EE:
	mov r0, #0x0
_020275F0:
	cmp r0, #0x0
	bne _020275F8
	bl ErrorHandling
_020275F8:
	add r0, r4, #0x4
	bl FUN_02027C84
	pop {r4, pc}
	.balign 4
_02027600: .word 0x00001234
_02027604: .word 0x00002345

	thumb_func_start FUN_02027608
FUN_02027608: ; 0x02027608
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027634 ; =0x00001234
	cmp r1, r0
	beq _0202761C
	ldr r0, _02027638 ; =0x00002345
	cmp r1, r0
	bne _02027620
_0202761C:
	mov r0, #0x1
	b _02027622
_02027620:
	mov r0, #0x0
_02027622:
	cmp r0, #0x0
	bne _0202762A
	bl ErrorHandling
_0202762A:
	add r0, r5, #0x4
	add r1, r4, #0x0
	bl FUN_02027C88
	pop {r3-r5, pc}
	.balign 4
_02027634: .word 0x00001234
_02027638: .word 0x00002345

	thumb_func_start FUN_0202763C
FUN_0202763C: ; 0x0202763C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027664 ; =0x00001234
	cmp r1, r0
	beq _0202764E
	ldr r0, _02027668 ; =0x00002345
	cmp r1, r0
	bne _02027652
_0202764E:
	mov r0, #0x1
	b _02027654
_02027652:
	mov r0, #0x0
_02027654:
	cmp r0, #0x0
	bne _0202765C
	bl ErrorHandling
_0202765C:
	add r0, r4, #0x4
	bl FUN_02027C98
	pop {r4, pc}
	.balign 4
_02027664: .word 0x00001234
_02027668: .word 0x00002345

	thumb_func_start FUN_0202766C
FUN_0202766C: ; 0x0202766C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027694 ; =0x00001234
	cmp r1, r0
	beq _0202767E
	ldr r0, _02027698 ; =0x00002345
	cmp r1, r0
	bne _02027682
_0202767E:
	mov r0, #0x1
	b _02027684
_02027682:
	mov r0, #0x0
_02027684:
	cmp r0, #0x0
	bne _0202768C
	bl ErrorHandling
_0202768C:
	add r4, #0x70
	ldrb r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02027694: .word 0x00001234
_02027698: .word 0x00002345

	thumb_func_start FUN_0202769C
FUN_0202769C: ; 0x0202769C
	ldr r3, _020276A4 ; =FUN_02013918
	add r0, #0x40
	mov r1, #0x0
	bx r3
	.balign 4
_020276A4: .word FUN_02013918

	thumb_func_start FUN_020276A8
FUN_020276A8: ; 0x020276A8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _020276D0 ; =0x00001234
	cmp r1, r0
	beq _020276BA
	ldr r0, _020276D4 ; =0x00002345
	cmp r1, r0
	bne _020276BE
_020276BA:
	mov r0, #0x1
	b _020276C0
_020276BE:
	mov r0, #0x0
_020276C0:
	cmp r0, #0x0
	bne _020276C8
	bl ErrorHandling
_020276C8:
	add r4, #0x71
	ldrb r0, [r4, #0x0]
	pop {r4, pc}
	nop
_020276D0: .word 0x00001234
_020276D4: .word 0x00002345

	thumb_func_start FUN_020276D8
FUN_020276D8: ; 0x020276D8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027708 ; =0x00001234
	cmp r1, r0
	beq _020276EA
	ldr r0, _0202770C ; =0x00002345
	cmp r1, r0
	bne _020276EE
_020276EA:
	mov r0, #0x1
	b _020276F0
_020276EE:
	mov r0, #0x0
_020276F0:
	cmp r0, #0x0
	bne _020276F8
	bl ErrorHandling
_020276F8:
	ldr r1, [r4, #0x0]
	ldr r0, _0202770C ; =0x00002345
	cmp r1, r0
	bne _02027704
	mov r0, #0x1
	pop {r4, pc}
_02027704:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_02027708: .word 0x00001234
_0202770C: .word 0x00002345

	thumb_func_start FUN_02027710
FUN_02027710: ; 0x02027710
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027738 ; =0x00001234
	cmp r1, r0
	beq _02027722
	ldr r0, _0202773C ; =0x00002345
	cmp r1, r0
	bne _02027726
_02027722:
	mov r0, #0x1
	b _02027728
_02027726:
	mov r0, #0x0
_02027728:
	cmp r0, #0x0
	bne _02027730
	bl ErrorHandling
_02027730:
	ldr r0, _0202773C ; =0x00002345
	str r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02027738: .word 0x00001234
_0202773C: .word 0x00002345

	thumb_func_start FUN_02027740
FUN_02027740: ; 0x02027740
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027770 ; =0x00001234
	cmp r1, r0
	beq _02027752
	ldr r0, _02027774 ; =0x00002345
	cmp r1, r0
	bne _02027756
_02027752:
	mov r0, #0x1
	b _02027758
_02027756:
	mov r0, #0x0
_02027758:
	cmp r0, #0x0
	bne _02027760
	bl ErrorHandling
_02027760:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x98
	bl Call_FillMemWithValue
	ldr r0, _02027770 ; =0x00001234
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4
_02027770: .word 0x00001234
_02027774: .word 0x00002345

	thumb_func_start FUN_02027778
FUN_02027778: ; 0x02027778
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020277AC ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _0202778E
	ldr r0, _020277B0 ; =0x00002345
	cmp r1, r0
	bne _02027792
_0202778E:
	mov r0, #0x1
	b _02027794
_02027792:
	mov r0, #0x0
_02027794:
	cmp r0, #0x0
	bne _0202779C
	bl ErrorHandling
_0202779C:
	add r5, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D34
	pop {r4-r6, pc}
	nop
_020277AC: .word 0x00001234
_020277B0: .word 0x00002345

	thumb_func_start FUN_020277B4
FUN_020277B4: ; 0x020277B4
	push {r4-r7, lr}
	sub sp, #0x14
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x4]
	add r6, r2, #0x0
	bl FUN_02013ECC
	add r1, sp, #0xc
	strh r0, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x2]
	ldrh r0, [r1, #0x0]
	strh r0, [r1, #0x4]
	ldrh r0, [r1, #0x2]
	strh r0, [r1, #0x6]
	ldr r0, [r4, #0x4]
	bl FUN_02013F00
	str r0, [sp, #0x8]
	cmp r6, #0x14
	blt _020277E4
	bl ErrorHandling
_020277E4:
	add r1, sp, #0xc
	mov r0, #0x4
	ldrsh r1, [r1, r0]
	add r0, #0xfc
	cmp r1, r0
	blt _020277F4
	bl ErrorHandling
_020277F4:
	add r1, sp, #0xc
	mov r0, #0x6
	ldrsh r7, [r1, r0]
	add r0, #0xfa
	cmp r7, r0
	blt _02027804
	bl ErrorHandling
_02027804:
	mov r1, #0x7f
	ldr r0, [sp, #0x8]
	mvn r1, r1
	cmp r0, r1
	bgt _02027812
	bl ErrorHandling
_02027812:
	mov r0, #0x1
	lsl r0, r6
	ldr r1, [r5, #0x40]
	str r0, [sp, #0x4]
	tst r0, r1
	beq _02027822
	bl ErrorHandling
_02027822:
	ldr r1, [r5, #0x0]
	ldr r0, _02027874 ; =0x00001234
	cmp r1, r0
	beq _02027830
	ldr r0, _02027878 ; =0x00002345
	cmp r1, r0
	bne _02027834
_02027830:
	mov r0, #0x1
	b _02027836
_02027834:
	mov r0, #0x0
_02027836:
	cmp r0, #0x0
	bne _0202783E
	bl ErrorHandling
_0202783E:
	ldr r0, [sp, #0x8]
	add r1, r5, #0x0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r3, sp, #0xc
	mov r2, #0x4
	ldrsh r2, [r3, r2]
	lsl r3, r7, #0x18
	add r1, #0x44
	lsl r0, r6, #0x2
	add r0, r1, r0
	ldr r1, [r4, #0x0]
	lsl r2, r2, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02026DB0
	ldr r1, [r5, #0x40]
	ldr r0, [sp, #0x4]
	orr r0, r1
	str r0, [r5, #0x40]
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02027874: .word 0x00001234
_02027878: .word 0x00002345

	thumb_func_start FUN_0202787C
FUN_0202787C: ; 0x0202787C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020278A4 ; =0x00001234
	cmp r1, r0
	beq _02027890
	ldr r0, _020278A8 ; =0x00002345
	cmp r1, r0
	bne _02027894
_02027890:
	mov r0, #0x1
	b _02027896
_02027894:
	mov r0, #0x0
_02027896:
	cmp r0, #0x0
	bne _0202789E
	bl ErrorHandling
_0202789E:
	add r5, #0x94
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4
_020278A4: .word 0x00001234
_020278A8: .word 0x00002345

	thumb_func_start FUN_020278AC
FUN_020278AC: ; 0x020278AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020278D4 ; =0x00001234
	cmp r1, r0
	beq _020278C0
	ldr r0, _020278D8 ; =0x00002345
	cmp r1, r0
	bne _020278C4
_020278C0:
	mov r0, #0x1
	b _020278C6
_020278C4:
	mov r0, #0x0
_020278C6:
	cmp r0, #0x0
	bne _020278CE
	bl ErrorHandling
_020278CE:
	str r4, [r5, #0x4]
	pop {r3-r5, pc}
	nop
_020278D4: .word 0x00001234
_020278D8: .word 0x00002345

	thumb_func_start FUN_020278DC
FUN_020278DC: ; 0x020278DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202790C ; =0x00001234
	cmp r1, r0
	beq _020278F0
	ldr r0, _02027910 ; =0x00002345
	cmp r1, r0
	bne _020278F4
_020278F0:
	mov r0, #0x1
	b _020278F6
_020278F4:
	mov r0, #0x0
_020278F6:
	cmp r0, #0x0
	bne _020278FE
	bl ErrorHandling
_020278FE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x98
	bl memcpy
	pop {r3-r5, pc}
	nop
_0202790C: .word 0x00001234
_02027910: .word 0x00002345

	thumb_func_start FUN_02027914
FUN_02027914: ; 0x02027914
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202795C ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _0202792C
	ldr r0, _02027960 ; =0x00002345
	cmp r1, r0
	bne _02027930
_0202792C:
	mov r0, #0x1
	b _02027932
_02027930:
	mov r0, #0x0
_02027932:
	cmp r0, #0x0
	bne _0202793A
	bl ErrorHandling
_0202793A:
	add r1, sp, #0x4
	add r0, r4, #0x0
	add r1, #0x1
	add r2, sp, #0x4
	bl FUN_02026F3C
	add r5, #0x8
	str r6, [sp, #0x0]
	add r3, sp, #0x4
	ldrb r2, [r3, #0x1]
	ldrb r3, [r3, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02026CD0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_0202795C: .word 0x00001234
_02027960: .word 0x00002345

	thumb_func_start FUN_02027964
FUN_02027964: ; 0x02027964
	push {r4-r7, lr}
	sub sp, #0xc
	str r3, [sp, #0x4]
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	ldr r4, [sp, #0x24]
	cmp r6, #0x14
	blo _0202797A
	bl ErrorHandling
_0202797A:
	cmp r7, #0x64
	blo _02027982
	bl ErrorHandling
_02027982:
	mov r1, #0x1
	ldr r0, [sp, #0x4]
	lsl r1, r1, #0x8
	cmp r0, r1
	blt _02027990
	bl ErrorHandling
_02027990:
	add r0, sp, #0x10
	ldrb r1, [r0, #0x10]
	mov r0, #0x1
	lsl r0, r0, #0x8
	cmp r1, r0
	blt _020279A0
	bl ErrorHandling
_020279A0:
	mov r0, #0x7f
	mvn r0, r0
	cmp r4, r0
	bgt _020279AC
	bl ErrorHandling
_020279AC:
	mov r0, #0x1
	lsl r0, r6
	ldr r1, [r5, #0x40]
	str r0, [sp, #0x8]
	tst r0, r1
	beq _020279BC
	bl ErrorHandling
_020279BC:
	ldr r1, [r5, #0x0]
	ldr r0, _02027A0C ; =0x00001234
	cmp r1, r0
	beq _020279CA
	ldr r0, _02027A10 ; =0x00002345
	cmp r1, r0
	bne _020279CE
_020279CA:
	mov r0, #0x1
	b _020279D0
_020279CE:
	mov r0, #0x0
_020279D0:
	cmp r0, #0x0
	bne _020279D8
	bl ErrorHandling
_020279D8:
	mov r0, #0x38
	ldrsb r0, [r5, r0]
	cmp r0, r4
	blt _020279E6
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
_020279E6:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r3, sp, #0x10
	add r1, r5, #0x0
	ldrb r3, [r3, #0x10]
	add r1, #0x44
	lsl r0, r6, #0x2
	add r0, r1, r0
	ldr r2, [sp, #0x4]
	add r1, r7, #0x0
	bl FUN_02026DB0
	ldr r1, [r5, #0x40]
	ldr r0, [sp, #0x8]
	orr r0, r1
	str r0, [r5, #0x40]
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02027A0C: .word 0x00001234
_02027A10: .word 0x00002345

	thumb_func_start FUN_02027A14
FUN_02027A14: ; 0x02027A14
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x14
	blt _02027A22
	bl ErrorHandling
_02027A22:
	ldr r1, [r5, #0x0]
	ldr r0, _02027A50 ; =0x00001234
	cmp r1, r0
	beq _02027A30
	ldr r0, _02027A54 ; =0x00002345
	cmp r1, r0
	bne _02027A34
_02027A30:
	mov r0, #0x1
	b _02027A36
_02027A34:
	mov r0, #0x0
_02027A36:
	cmp r0, #0x0
	bne _02027A3E
	bl ErrorHandling
_02027A3E:
	mov r0, #0x1
	add r1, r0, #0x0
	ldr r2, [r5, #0x40]
	lsl r1, r4
	tst r1, r2
	bne _02027A4C
	mov r0, #0x0
_02027A4C:
	pop {r3-r5, pc}
	nop
_02027A50: .word 0x00001234
_02027A54: .word 0x00002345

	thumb_func_start FUN_02027A58
FUN_02027A58: ; 0x02027A58
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027A8C ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _02027A6E
	ldr r0, _02027A90 ; =0x00002345
	cmp r1, r0
	bne _02027A72
_02027A6E:
	mov r0, #0x1
	b _02027A74
_02027A72:
	mov r0, #0x0
_02027A74:
	cmp r0, #0x0
	bne _02027A7C
	bl ErrorHandling
_02027A7C:
	add r5, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D98
	pop {r4-r6, pc}
	nop
_02027A8C: .word 0x00001234
_02027A90: .word 0x00002345

	thumb_func_start FUN_02027A94
FUN_02027A94: ; 0x02027A94
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027ABC ; =0x00001234
	cmp r1, r0
	beq _02027AA6
	ldr r0, _02027AC0 ; =0x00002345
	cmp r1, r0
	bne _02027AAA
