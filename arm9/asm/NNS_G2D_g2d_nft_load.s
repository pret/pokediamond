	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; NNSi_G2dUnpackNFT
	arm_func_start FUN_020B7468
FUN_020B7468: ; 0x020B7468
	stmdb sp!, {r4-r6,lr}
	ldrh r2, [r0, #0xc]
	ldrh r3, [r0, #0xe]
	mov r1, #0x0
	add r2, r0, r2
	cmp r3, #0x0
	ldmleia sp!, {r4-r6,pc}
	ldr r3, _020B7548 ; =0x46494E46
	ldr ip, _020B754C ; =0x43574448
	ldr r4, _020B7550 ; =0x434D4150
	ldr lr, _020B7554 ; =0x43474C50
_020B7494:
	ldr r5, [r2, #0x0]
	cmp r5, r4
	bhi _020B74B0
	cmp r5, r4
	bhs _020B7518
	cmp r5, lr
	b _020B752C
_020B74B0:
	cmp r5, r12
	bhi _020B74C4
	cmp r5, r12
	beq _020B7500
	b _020B752C
_020B74C4:
	cmp r5, r3
	bne _020B752C
	add r6, r2, #0x8
	ldr r5, [r6, #0x8]
	add r5, r5, r0
	str r5, [r6, #0x8]
	ldr r5, [r6, #0xc]
	cmp r5, #0x0
	addne r5, r5, r0
	strne r5, [r6, #0xc]
	ldr r5, [r6, #0x10]
	cmp r5, #0x0
	addne r5, r5, r0
	strne r5, [r6, #0x10]
	b _020B752C
_020B7500:
	add r6, r2, #0x8
	ldr r5, [r6, #0x4]
	cmp r5, #0x0
	addne r5, r5, r0
	strne r5, [r6, #0x4]
	b _020B752C
_020B7518:
	add r6, r2, #0x8
	ldr r5, [r6, #0x8]
	cmp r5, #0x0
	addne r5, r5, r0
	strne r5, [r6, #0x8]
_020B752C:
	ldrh r5, [r0, #0xe]
	ldr r6, [r2, #0x4]
	add r1, r1, #0x1
	cmp r1, r5
	add r2, r2, r6
	blt _020B7494
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B7548: .word 0x46494E46
_020B754C: .word 0x43574448
_020B7550: .word 0x434D4150
_020B7554: .word 0x43474C50
	arm_func_end FUN_020B7468

	; NNSi_G2dGetUnpackedFont
	arm_func_start FUN_020B7558
FUN_020B7558: ; 0x020B7558
	stmdb sp!, {r4-r6,lr}
	movs r6, r0
	mov r5, r1
	beq _020B75C8
	cmp r6, #0x0
	beq _020B7584
	ldr r1, [r6, #0x0]
	ldr r0, _020B76A8 ; =0x4E465452
	cmp r1, r0
	moveq r0, #0x1
	beq _020B7588
_020B7584:
	mov r0, #0x0
_020B7588:
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B75CC
	cmp r6, #0x0
	beq _020B75B4
	ldrh r0, [r6, #0x6]
	cmp r0, #0x100
	movcs r0, #0x1
	bhs _020B75B8
_020B75B4:
	mov r0, #0x0
_020B75B8:
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	b _020B75CC
_020B75C8:
	mov r0, #0x0
_020B75CC:
	cmp r0, #0x0
	movne r4, #0x0
	bne _020B7654
	cmp r6, #0x0
	beq _020B7640
	cmp r6, #0x0
	beq _020B75FC
	ldr r1, [r6, #0x0]
	ldr r0, _020B76A8 ; =0x4E465452
	cmp r1, r0
	moveq r0, #0x1
	beq _020B7600
_020B75FC:
	mov r0, #0x0
_020B7600:
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B7644
	cmp r6, #0x0
	beq _020B762C
	ldrh r0, [r6, #0x6]
	cmp r0, #0x1
	movcs r0, #0x1
	bhs _020B7630
_020B762C:
	mov r0, #0x0
_020B7630:
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	b _020B7644
_020B7640:
	mov r0, #0x0
_020B7644:
	cmp r0, #0x0
	movne r4, #0x1
	bne _020B7654
	bl OS_Terminate
_020B7654:
	mov r0, r6
	bl FUN_020B7468
	ldr r1, _020B76AC ; =0x46494E46
	mov r0, r6
	bl FUN_020B01F8
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r6,pc}
	add r0, r0, #0x8
	str r0, [r5, #0x0]
	cmp r4, #0x0
	beq _020B76A0
	ldr r2, [r5, #0x0]
	mov r1, #0x0
	ldrsb r0, [r2, #0x6]
	strb r0, [r2, #0x7]
	ldr r0, [r5, #0x0]
	strb r1, [r0, #0x6]
_020B76A0:
	add r0, r4, #0x1
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B76A8: .word 0x4E465452
_020B76AC: .word 0x46494E46
	arm_func_end FUN_020B7558

