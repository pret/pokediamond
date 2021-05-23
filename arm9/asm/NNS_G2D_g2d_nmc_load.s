	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNS_G2dGetMultiCellDataByIdx
NNS_G2dGetMultiCellDataByIdx: ; 0x020AFF34
	ldrh r2, [r0, #0x0]
	cmp r1, r2
	ldrcc r0, [r0, #0x4]
	addcc r0, r0, r1, lsl #0x3
	movcs r0, #0x0
	bx lr
	arm_func_end NNS_G2dGetMultiCellDataByIdx

	arm_func_start NNS_G2dUnpackNMC
NNS_G2dUnpackNMC: ; 0x020AFF4C
	stmdb sp!, {r4,lr}
	ldr r1, [r0, #0x4]
	mov r4, #0x0
	add r1, r1, r0
	str r1, [r0, #0x4]
	ldr r1, [r0, #0x8]
	add r1, r1, r0
	str r1, [r0, #0x8]
	ldrh r1, [r0, #0x0]
	ldr lr, [r0, #0x4]
	cmp r1, #0x0
	bls _020AFFA8
_020AFF7C:
	add r3, lr, r4, lsl #0x3
	ldr r12, [r0, #0x8]
	ldr r2, [r3, #0x4]
	add r1, r4, #0x1
	add r2, r12, r2
	str r2, [r3, #0x4]
	mov r1, r1, lsl #0x10
	ldrh r2, [r0, #0x0]
	mov r4, r1, lsr #0x10
	cmp r4, r2
	blo _020AFF7C
_020AFFA8:
	ldr r1, [r0, #0x10]
	cmp r1, #0x0
	ldmeqia sp!, {r4,pc}
	add r1, r1, r0
	str r1, [r0, #0x10]
	ldr r0, [r0, #0x10]
	bl UnpackExtendedData_
	ldmia sp!, {r4,pc}
	arm_func_end NNS_G2dUnpackNMC

	arm_func_start UnpackExtendedData_
UnpackExtendedData_: ; 0x020AFFC8
	ldr ip, _020AFFD4 ; =NNSi_G2dUnpackUserExCellAttrBank
	add r0, r0, #0x8
	bx r12
	.balign 4
_020AFFD4: .word NNSi_G2dUnpackUserExCellAttrBank
	arm_func_end UnpackExtendedData_

	arm_func_start NNS_G2dGetUnpackedMultiCellBank
NNS_G2dGetUnpackedMultiCellBank: ; 0x020AFFD8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020B001C ; =0x4D43424B
	bl NNS_G2dFindBinaryBlock
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
	add r0, r4, #0x8
	bl NNS_G2dUnpackNMC
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B001C: .word 0x4D43424B
	arm_func_end NNS_G2dGetUnpackedMultiCellBank
