	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020B0408
FUN_020B0408: ; 0x020B0408
	ldr r1, [r0, #0x14]
	cmp r1, #0x0
	ldreq r0, [r0, #0x18]
	ldreq r1, [r0, #0x8]
	cmp r1, #0x2
	beq _020B0428
	cmp r1, #0x4
	bne _020B0430
_020B0428:
	mov r0, #0x1
	bx lr
_020B0430:
	mov r0, #0x0
	bx lr
	arm_func_end FUN_020B0408

	; NNS_G2dBindAnimCtrl
	arm_func_start FUN_020B0438
FUN_020B0438: ; 0x020B0438
	ldr ip, _020B0444 ; =FUN_020B0448
	str r1, [r0, #0x18]
	bx r12
	.balign 4
_020B0444: .word FUN_020B0448
	arm_func_end FUN_020B0438

	; NNS_G2dResetAnimCtrlState
	arm_func_start FUN_020B0448
FUN_020B0448: ; 0x020B0448
	ldr r1, [r0, #0x10]
	cmp r1, #0x0
	movgt r2, #0x1
	ldr r1, [r0, #0x4]
	movle r2, #0x0
	eors r1, r2, r1
	beq _020B047C
	ldr r2, [r0, #0x18]
	ldrh r1, [r2, #0x2]
	ldr r2, [r2, #0xc]
	add r1, r2, r1, lsl #0x3
	str r1, [r0, #0x0]
	b _020B0494
_020B047C:
	ldr r2, [r0, #0x18]
	ldrh r1, [r2, #0x0]
	ldr r2, [r2, #0xc]
	add r1, r2, r1, lsl #0x3
	sub r1, r1, #0x8
	str r1, [r0, #0x0]
_020B0494:
	ldr ip, _020B04A4 ; =FUN_020B0534
	mov r1, #0x0
	str r1, [r0, #0xc]
	bx r12
	.balign 4
_020B04A4: .word FUN_020B0534
	arm_func_end FUN_020B0448

	; _end
	arm_func_start FUN_020B04A8
FUN_020B04A8: ; 0x020B04A8
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	strh r1, [r0, #0xc]
	bx lr
	arm_func_end FUN_020B04A8

	; _end
	arm_func_start FUN_020B04C0
FUN_020B04C0: ; 0x020B04C0
	stmdb sp!, {r4,lr}
	mov r4, r0
	add r0, r4, #0x1c
	bl FUN_020B04A8
	mov r1, #0x0
	str r1, [r4, #0x0]
	str r1, [r4, #0x4]
	mov r0, #0x1
	str r0, [r4, #0x8]
	str r1, [r4, #0xc]
	mov r0, #0x1000
	str r0, [r4, #0x10]
	str r1, [r4, #0x14]
	str r1, [r4, #0x18]
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020B04C0

	; _end
	arm_func_start FUN_020B04FC
FUN_020B04FC: ; 0x020B04FC
	ldr r1, [r0, #0x18]
	ldr r2, [r0, #0x0]
	ldr r0, [r1, #0xc]
	sub r0, r2, r0
	mov r0, r0, lsl #0xd
	mov r0, r0, lsr #0x10
	bx lr
	arm_func_end FUN_020B04FC

	; _end
	arm_func_start FUN_020B0518
FUN_020B0518: ; 0x020B0518
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020B06EC
	cmp r0, #0x0
	movne r1, #0x0
	strne r1, [r4, #0xc]
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020B0518

	; _end
	arm_func_start FUN_020B0534
FUN_020B0534: ; 0x020B0534
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldr r0, [r8, #0x8]
	mov r7, #0x0
	cmp r0, #0x1
	movne r0, r7
	ldmneia sp!, {r4-r8,pc}
	ldr r2, [r8, #0x10]
	mov r0, #0x800
	smull r3, r1, r2, r1
	adds r0, r3, r0
	adc r1, r1, r7
	mov r0, r0, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	bl abs
	ldr r1, [r8, #0xc]
	add r6, r8, #0xc
	add r0, r1, r0
	str r0, [r8, #0xc]
	mov r4, r7
	mov r5, #0x1
	b _020B06A8
_020B058C:
	ldr r0, [r8, #0x0]
	ldr r1, [r6, #0x0]
	ldrh r0, [r0, #0x4]
	mov r7, r5
	sub r0, r1, r0, lsl #0xc
	str r0, [r6, #0x0]
	ldr r0, [r8, #0x10]
	cmp r0, #0x0
	movgt r1, r5
	ldr r0, [r8, #0x4]
	movle r1, r4
	eors r0, r1, r0
	ldrne r0, [r8, #0x0]
	addne r0, r0, #0x8
	strne r0, [r8, #0x0]
	ldreq r0, [r8, #0x0]
	subeq r0, r0, #0x8
	streq r0, [r8, #0x0]
	ldr r1, [r8, #0x10]
	ldr r0, [r8, #0x0]
	cmp r1, #0x0
	movgt r2, r5
	ldr r1, [r8, #0x4]
	movle r2, r4
	eors r1, r2, r1
	beq _020B0614
	ldr r2, [r8, #0x18]
	ldrh r1, [r2, #0x0]
	ldr r2, [r2, #0xc]
	add r1, r2, r1, lsl #0x3
	cmp r0, r1
	movcs r0, r5
	movcc r0, r4
	b _020B0634
_020B0614:
	ldr r2, [r8, #0x18]
	ldrh r1, [r2, #0x2]
	ldr r2, [r2, #0xc]
	add r1, r2, r1, lsl #0x3
	sub r1, r1, #0x8
	cmp r0, r1
	movls r0, r5
	movhi r0, r4
_020B0634:
	cmp r0, #0x0
	beq _020B0644
	mov r0, r8
	bl FUN_020B0710
_020B0644:
	ldr r0, [r8, #0x1c]
	cmp r0, #0x0
	beq _020B06A8
	ldr r0, [r8, #0x18]
	ldr r2, [r8, #0x1c]
	ldr r1, [r8, #0x0]
	ldr r0, [r0, #0xc]
	cmp r2, #0x2
	sub r0, r1, r0
	mov r0, r0, lsl #0xd
	mov r1, r0, lsr #0x10
	beq _020B0680
	cmp r2, #0x3
	beq _020B069C
	b _020B06A8
_020B0680:
	ldrh r0, [r8, #0x28]
	cmp r1, r0
	bne _020B06A8
	ldr r0, [r8, #0x20]
	ldr r2, [r8, #0x24]
	blx r2
	b _020B06A8
_020B069C:
	ldr r0, [r8, #0x20]
	ldr r2, [r8, #0x24]
	blx r2
_020B06A8:
	ldr r0, [r8, #0x8]
	cmp r0, #0x0
	beq _020B06CC
	ldr r0, [r8, #0x0]
	ldr r1, [r8, #0xc]
	ldrh r0, [r0, #0x4]
	cmp r1, r0, lsl #0xc
	movge r0, r5
	bge _020B06D0
_020B06CC:
	mov r0, r4
_020B06D0:
	cmp r0, #0x0
	bne _020B058C
	mov r0, r7
	ldmia sp!, {r4-r8,pc}
	arm_func_end FUN_020B0534

	; _end
	arm_func_start FUN_020B06E0
FUN_020B06E0: ; 0x020B06E0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	bx lr
	arm_func_end FUN_020B06E0

	; _end
	arm_func_start FUN_020B06EC
FUN_020B06EC: ; 0x020B06EC
	ldr r3, [r0, #0x18]
	ldrh r2, [r3, #0x0]
	cmp r1, r2
	ldrcc r2, [r3, #0xc]
	addcc r1, r2, r1, lsl #0x3
	strcc r1, [r0, #0x0]
	movcc r0, #0x1
	movcs r0, #0x0
	bx lr
	arm_func_end FUN_020B06EC

	; _end
	arm_func_start FUN_020B0710
FUN_020B0710: ; 0x020B0710
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	ldreq r0, [r4, #0x18]
	ldreq r0, [r0, #0x8]
	cmp r0, #0x3
	beq _020B0738
	cmp r0, #0x4
	bne _020B07B4
_020B0738:
	ldr r0, [r4, #0x4]
	eor r0, r0, #0x1
	str r0, [r4, #0x4]
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x0]
	ldrh r0, [r1, #0x2]
	ldr r1, [r1, #0xc]
	add r0, r1, r0, lsl #0x3
	sub r0, r0, #0x8
	cmp r2, r0
	bhi _020B0800
	ldr r0, [r4, #0x1c]
	cmp r0, #0x1
	bne _020B0780
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x24]
	blx r2
_020B0780:
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	ldreq r0, [r4, #0x18]
	ldreq r0, [r0, #0x8]
	cmp r0, #0x2
	beq _020B07A8
	cmp r0, #0x4
	movne r0, #0x0
	strne r0, [r4, #0x8]
	bne _020B0800
_020B07A8:
	mov r0, r4
	bl FUN_020B0448
	b _020B0800
_020B07B4:
	ldr r0, [r4, #0x1c]
	cmp r0, #0x1
	bne _020B07D0
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x24]
	blx r2
_020B07D0:
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	ldreq r0, [r4, #0x18]
	ldreq r0, [r0, #0x8]
	cmp r0, #0x2
	beq _020B07F8
	cmp r0, #0x4
	movne r0, #0x0
	strne r0, [r4, #0x8]
	bne _020B0800
_020B07F8:
	mov r0, r4
	bl FUN_020B0448
_020B0800:
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x0]
	ldrh r0, [r1, #0x0]
	ldr r1, [r1, #0xc]
	add r0, r1, r0, lsl #0x3
	sub r0, r0, #0x8
	cmp r2, r0
	strhi r0, [r4, #0x0]
	ldmhiia sp!, {r4,pc}
	cmp r2, r1
	strcc r1, [r4, #0x0]
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020B0710

