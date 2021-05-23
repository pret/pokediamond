	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020AFDE8
FUN_020AFDE8: ; 0x020AFDE8
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldr r1, [r5, #0x4]
	add r1, r1, r5
	str r1, [r5, #0x4]
	bl FUN_020AFF10
	ldrh r1, [r5, #0x0]
	mov r4, r0
	mov r6, #0x0
	cmp r1, #0x0
	bls _020AFE44
_020AFE14:
	mov r0, r5
	mov r1, r6
	bl FUN_020AFE8C
	ldr r2, [r0, #0x4]
	add r1, r6, #0x1
	add r2, r2, r4
	str r2, [r0, #0x4]
	mov r0, r1, lsl #0x10
	ldrh r1, [r5, #0x0]
	mov r6, r0, lsr #0x10
	cmp r6, r1
	blo _020AFE14
_020AFE44:
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	beq _020AFE6C
	add r0, r0, r5
	str r0, [r5, #0xc]
	ldr r1, [r5, #0xc]
	ldr r0, [r1, #0x4]
	add r0, r0, r1
	str r0, [r1, #0x4]
	str r1, [r5, #0xc]
_020AFE6C:
	ldr r0, [r5, #0x14]
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	add r0, r0, r5
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x14]
	bl FUN_020AFF00
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020AFDE8

	; _end
	arm_func_start FUN_020AFE8C
FUN_020AFE8C: ; 0x020AFE8C
	ldrh r2, [r0, #0x0]
	cmp r1, r2
	movcs r0, #0x0
	bxcs lr
	ldrh r2, [r0, #0x2]
	ands r2, r2, #0x1
	ldrne r0, [r0, #0x4]
	addne r0, r0, r1, lsl #0x4
	ldreq r0, [r0, #0x4]
	addeq r0, r0, r1, lsl #0x3
	bx lr
	arm_func_end FUN_020AFE8C

	; NNS_G2dGetUnpackedCellBank
	arm_func_start FUN_020AFEB8
FUN_020AFEB8: ; 0x020AFEB8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020AFEFC ; =0x4345424B
	bl FUN_020B01F8
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
	add r0, r4, #0x8
	bl FUN_020AFDE8
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AFEFC: .word 0x4345424B
	arm_func_end FUN_020AFEB8

	; UnPackExtendedData_
	arm_func_start FUN_020AFF00
FUN_020AFF00: ; 0x020AFF00
	ldr ip, _020AFF0C ; =FUN_020B01B0
	add r0, r0, #0x8
	bx r12
	.balign 4
_020AFF0C: .word FUN_020B01B0
	arm_func_end FUN_020AFF00

	; _end
	arm_func_start FUN_020AFF10
FUN_020AFF10: ; 0x020AFF10
	ldrh r1, [r0, #0x2]
	ands r1, r1, #0x1
	ldrneh r1, [r0, #0x0]
	ldrne r0, [r0, #0x4]
	addne r0, r0, r1, lsl #0x4
	ldreqh r1, [r0, #0x0]
	ldreq r0, [r0, #0x4]
	addeq r0, r0, r1, lsl #0x3
	bx lr
	arm_func_end FUN_020AFF10

