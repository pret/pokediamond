	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020B0020
FUN_020B0020: ; 0x020B0020
	ldr r1, [r0, #0x14]
	add r1, r1, r0
	str r1, [r0, #0x14]
	bx lr
	arm_func_end FUN_020B0020

	; NNS_G2dGetUnpackedBGCharacterData
	arm_func_start FUN_020B0030
FUN_020B0030: ; 0x020B0030
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020B0074 ; =0x43484152
	bl FUN_020B01F8
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
	add r0, r4, #0x8
	bl FUN_020B0020
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B0074: .word 0x43484152
	arm_func_end FUN_020B0030

	; _end
	arm_func_start FUN_020B0078
FUN_020B0078: ; 0x020B0078
	ldr r1, [r0, #0x14]
	add r1, r1, r0
	str r1, [r0, #0x14]
	bx lr
	arm_func_end FUN_020B0078

	; NNS_G2dGetUnpackedCharacterData
	arm_func_start FUN_020B0088
FUN_020B0088: ; 0x020B0088
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020B00CC ; =0x43484152
	bl FUN_020B01F8
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
	add r0, r4, #0x8
	bl FUN_020B0078
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B00CC: .word 0x43484152
	arm_func_end FUN_020B0088

