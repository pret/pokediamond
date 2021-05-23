	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNSi_G2dUnpackUserExCellAttrBank
NNSi_G2dUnpackUserExCellAttrBank: ; 0x020B01B0
	ldr r1, [r0, #0x4]
	mov r12, #0x0
	add r1, r1, r0
	str r1, [r0, #0x4]
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	bxls lr
_020B01CC:
	ldr r3, [r0, #0x4]
	add r1, r12, #0x1
	ldr r2, [r3, r12, lsl #0x2]
	mov r1, r1, lsl #0x10
	add r2, r0, r2
	str r2, [r3, r12, lsl #0x2]
	ldrh r2, [r0, #0x0]
	mov r12, r1, lsr #0x10
	cmp r12, r2
	blo _020B01CC
	bx lr
	arm_func_end NNSi_G2dUnpackUserExCellAttrBank

	arm_func_start NNS_G2dFindBinaryBlock
NNS_G2dFindBinaryBlock: ; 0x020B01F8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r2, [r0, #0xc]
	ldrh r12, [r0, #0xe]
	mov lr, #0x0
	add r0, r0, r2
	cmp r12, #0x0
	bls _020B0244
_020B0218:
	ldr r2, [r0, #0x0]
	cmp r2, r1
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	add r2, lr, #0x1
	mov r2, r2, lsl #0x10
	ldr r3, [r0, #0x4]
	mov lr, r2, lsr #0x10
	cmp lr, r12
	add r0, r0, r3
	blo _020B0218
_020B0244:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_G2dFindBinaryBlock
