	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global cvtTbl$7926
cvtTbl$7926: ; 0x020FF8C4
	.byte 0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00
	; static const in function

	.section .bss

	.global s_pTaskRegisterFunc
s_pTaskRegisterFunc: ; 0x021CECFC
	.space 0x4

	.global s_numCellState
s_numCellState: ; 0x021CED00
	.space 0x4

	.global s_pCellStateArray
s_pCellStateArray: ; 0x021CED04
	.space 0x4

	.section .text

	arm_func_start NNS_G2dFreeCellTransferStateHandle
NNS_G2dFreeCellTransferStateHandle: ; 0x020B4358
	stmdb sp!, {r4,lr}
	ldr r2, _020B43A0 ; =s_pCellStateArray
	mov r1, #0x30
	ldr r2, [r2, #0x0]
	mla r4, r0, r1, r2
	mov r0, r4
	bl NNSi_G2dInitializeVRamLocation
	mov r0, #0x0
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	str r0, [r4, #0x20]
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	ldmia sp!, {r4,pc}
	.balign 4
_020B43A0: .word s_pCellStateArray
	arm_func_end NNS_G2dFreeCellTransferStateHandle

	arm_func_start NNS_G2dGetNewCellTransferStateHandle
NNS_G2dGetNewCellTransferStateHandle: ; 0x020B43A4
	ldr r1, _020B43F8 ; =s_numCellState
	mov r0, #0x0
	ldr r3, [r1, #0x0]
	cmp r3, #0x0
	bls _020B43F0
	ldr r1, _020B43FC ; =s_pCellStateArray
	ldr r2, [r1, #0x0]
	mov r12, r2
_020B43C4:
	ldr r1, [r12, #0x1c]
	cmp r1, #0x1
	movne r1, #0x30
	mlane r1, r0, r1, r2
	movne r2, #0x1
	strne r2, [r1, #0x1c]
	bxne lr
	add r0, r0, #0x1
	cmp r0, r3
	add r12, r12, #0x30
	blo _020B43C4
_020B43F0:
	mvn r0, #0x0
	bx lr
	.balign 4
_020B43F8: .word s_numCellState
_020B43FC: .word s_pCellStateArray
	arm_func_end NNS_G2dGetNewCellTransferStateHandle

	arm_func_start NNS_G2dSetCellTransferStateRequested
NNS_G2dSetCellTransferStateRequested: ; 0x020B4400
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	mov r4, r2
	bl NNSi_G2dGetCellTransferState
	mvn r1, #0x0
	str r1, [r0, #0x24]
	str r5, [r0, #0x28]
	str r4, [r0, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end NNS_G2dSetCellTransferStateRequested

	arm_func_start NNS_G2dUpdateCellTransferStateManager
NNS_G2dUpdateCellTransferStateManager: ; 0x020B442C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, _020B4558 ; =s_numCellState
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addls sp, sp, #0x14
	ldmlsia sp!, {r4-r11,pc}
	ldr r0, [sp, #0x0]
	mov r5, #0x1
	str r0, [sp, #0x4]
	mov r11, r0
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
_020B4468:
	ldr r0, _020B455C ; =s_pCellStateArray
	ldr r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	add r8, r1, r0
	ldr r0, [r8, #0x1c]
	cmp r0, #0x0
	beq _020B4528
	ldr r9, [sp, #0x8]
	mov r0, r9
	cmp r0, #0x3
	bge _020B4520
	add r4, r8, #0x24
_020B4498:
	mov r6, r5, lsl r9
	mov r1, r11
	ldr r0, [r8, #0x24]
	ands r0, r0, r6
	beq _020B44B8
	ldr r0, [r8, #0x20]
	ands r0, r0, r6
	movne r1, r5
_020B44B8:
	cmp r1, #0x0
	beq _020B4514
	ldr r0, _020B4560 ; =cvtTbl$7926
	cmp r9, #0x0
	ldr r7, [r0, r9, lsl #0x2]
	ldreq r10, [r8, #0x14]
	mov r0, r8
	mov r1, r9
	ldrne r10, [r8, #0x10]
	bl NNSi_G2dGetVramLocation
	mov r1, r0
	mov r0, r7
	ldr r7, _020B4564 ; =s_pTaskRegisterFunc
	ldr r2, [r8, #0x28]
	ldr r3, [r8, #0x2c]
	ldr r7, [r7, #0x0]
	add r2, r10, r2
	blx r7
	cmp r0, #0x0
	ldrne r1, [r4, #0x0]
	mvnne r0, r6
	andne r0, r1, r0
	strne r0, [r4, #0x0]
_020B4514:
	add r9, r9, #0x1
	cmp r9, #0x3
	blt _020B4498
_020B4520:
	ldr r0, [sp, #0xc]
	str r0, [r8, #0x20]
_020B4528:
	ldr r0, _020B4558 ; =s_numCellState
	ldr r1, [r0, #0x0]
	ldr r0, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	cmp r0, r1
	ldr r0, [sp, #0x4]
	add r0, r0, #0x30
	str r0, [sp, #0x4]
	blo _020B4468
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B4558: .word s_numCellState
_020B455C: .word s_pCellStateArray
_020B4560: .word cvtTbl$7926
_020B4564: .word s_pTaskRegisterFunc
	arm_func_end NNS_G2dUpdateCellTransferStateManager

	arm_func_start NNS_G2dInitCellTransferStateManager
NNS_G2dInitCellTransferStateManager: ; 0x020B4568
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr ip, _020B45E4 ; =s_pTaskRegisterFunc
	movs r6, r1
	ldr r1, _020B45E8 ; =s_numCellState
	ldr r3, _020B45EC ; =s_pCellStateArray
	mov r7, r0
	str r2, [r12, #0x0]
	mov r5, #0x0
	addeq sp, sp, #0x4
	str r7, [r3, #0x0]
	str r6, [r1, #0x0]
	ldmeqia sp!, {r4-r7,pc}
	mov r4, r5
_020B45A0:
	mov r0, r7
	bl NNSi_G2dInitializeVRamLocation
	str r4, [r7, #0xc]
	str r4, [r7, #0x10]
	str r4, [r7, #0x14]
	str r4, [r7, #0x18]
	str r4, [r7, #0x1c]
	str r4, [r7, #0x20]
	str r4, [r7, #0x24]
	str r4, [r7, #0x28]
	add r5, r5, #0x1
	str r4, [r7, #0x2c]
	cmp r5, r6
	add r7, r7, #0x30
	blo _020B45A0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B45E4: .word s_pTaskRegisterFunc
_020B45E8: .word s_numCellState
_020B45EC: .word s_pCellStateArray
	arm_func_end NNS_G2dInitCellTransferStateManager

	arm_func_start NNSi_G2dInitCellTransferState
NNSi_G2dInitCellTransferState: ; 0x020B45F0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr ip, _020B4698 ; =s_pCellStateArray
	mov r4, #0x30
	ldr r12, [r12, #0x0]
	mov r7, r1
	mla r4, r0, r4, r12
	mov r0, r4
	mov r6, r2
	mov r5, r3
	bl NNSi_G2dInitializeVRamLocation
	mvn r0, #0x0
	cmp r7, r0
	beq _020B4638
	mov r0, r4
	mov r2, r7
	mov r1, #0x0
	bl NNSi_G2dSetVramLocation
_020B4638:
	mvn r0, #0x0
	cmp r6, r0
	beq _020B4654
	mov r0, r4
	mov r2, r6
	mov r1, #0x1
	bl NNSi_G2dSetVramLocation
_020B4654:
	mvn r0, #0x0
	cmp r5, r0
	beq _020B4670
	mov r0, r4
	mov r2, r5
	mov r1, #0x2
	bl NNSi_G2dSetVramLocation
_020B4670:
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	str r1, [r4, #0xc]
	ldr r1, [sp, #0x20]
	str r0, [r4, #0x10]
	ldr r0, [sp, #0x24]
	str r1, [r4, #0x14]
	str r0, [r4, #0x18]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B4698: .word s_pCellStateArray
	arm_func_end NNSi_G2dInitCellTransferState

	arm_func_start NNSi_G2dGetCellTransferState
NNSi_G2dGetCellTransferState: ; 0x020B469C
	ldr r2, _020B46B0 ; =s_pCellStateArray
	mov r1, #0x30
	ldr r2, [r2, #0x0]
	mla r0, r1, r0, r2
	bx lr
	.balign 4
_020B46B0: .word s_pCellStateArray
	arm_func_end NNSi_G2dGetCellTransferState
