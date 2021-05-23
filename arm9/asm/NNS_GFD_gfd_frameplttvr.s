	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global s_managerState_
s_managerState_: ; 0x021CCD4C
	.space 0xc

	.section .text

	arm_func_start NNS_GfdResetFrmPlttVramState
NNS_GfdResetFrmPlttVramState: ; 0x020AEC60
	ldr r0, _020AEC78 ; =s_managerState_
	mov r2, #0x0
	ldr r1, [r0, #0x8]
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
	bx lr
	.balign 4
_020AEC78: .word s_managerState_
	arm_func_end NNS_GfdResetFrmPlttVramState

	arm_func_start NNS_GfdSetFrmPlttVramState
NNS_GfdSetFrmPlttVramState: ; 0x020AEC7C
	ldr r2, [r0, #0x0]
	ldr r1, _020AEC94 ; =s_managerState_
	str r2, [r1, #0x0]
	ldr r0, [r0, #0x4]
	str r0, [r1, #0x4]
	bx lr
	.balign 4
_020AEC94: .word s_managerState_
	arm_func_end NNS_GfdSetFrmPlttVramState

	arm_func_start NNS_GfdGetFrmPlttVramState
NNS_GfdGetFrmPlttVramState: ; 0x020AEC98
	ldr r1, _020AECB0 ; =s_managerState_
	ldr r2, [r1, #0x0]
	str r2, [r0, #0x0]
	ldr r1, [r1, #0x4]
	str r1, [r0, #0x4]
	bx lr
	.balign 4
_020AECB0: .word s_managerState_
	arm_func_end NNS_GfdGetFrmPlttVramState

	arm_func_start NNS_GfdFreeFrmPlttVram
NNS_GfdFreeFrmPlttVram: ; 0x020AECB4
	mov r0, #0x0
	bx lr
	arm_func_end NNS_GfdFreeFrmPlttVram

	arm_func_start NNS_GfdAllocFrmPlttVram
NNS_GfdAllocFrmPlttVram: ; 0x020AECBC
	stmdb sp!, {r4,lr}
	cmp r0, #0x0
	moveq r0, #0x8
	addne r0, r0, #0x7
	ldr ip, _020AEDE8 ; =0x0007FFF8
	bicne r0, r0, #0x7
	cmp r0, r12
	mov r3, #0x0
	movcs r0, #0x0
	ldmcsia sp!, {r4,pc}
	cmp r2, #0x1
	bne _020AED64
	ldr r2, _020AEDEC ; =s_managerState_
	cmp r1, #0x0
	ldr r12, [r2, #0x0]
	andne r2, r12, #0x7
	rsbne r2, r2, #0x8
	andne r4, r2, #0x7
	andeq r2, r12, #0xf
	rsbeq r2, r2, #0x10
	andeq r4, r2, #0xf
	ldr r2, _020AEDEC ; =s_managerState_
	add lr, r0, r4
	ldr r2, [r2, #0x4]
	sub r2, r2, r12
	cmp r2, lr
	blo _020AED5C
	cmp r1, #0x0
	add r1, r12, lr
	beq _020AED40
	cmp r1, #0x10000
	movhi r12, #0x0
	bhi _020AEDCC
_020AED40:
	ldr r1, _020AEDEC ; =s_managerState_
	add r3, r12, r4
	ldr r2, [r1, #0x0]
	mov r12, #0x1
	add r2, r2, lr
	str r2, [r1, #0x0]
	b _020AEDCC
_020AED5C:
	mov r12, #0x0
	b _020AEDCC
_020AED64:
	ldr r2, _020AEDEC ; =s_managerState_
	ldr r12, [r2, #0x4]
	cmp r12, r0
	blo _020AEDC8
	sub r2, r12, r0
	cmp r1, #0x0
	andne r4, r2, #0x7
	andeq r4, r2, #0xf
	ldr r2, _020AEDEC ; =s_managerState_
	add lr, r0, r4
	ldr r2, [r2, #0x0]
	sub r2, r12, r2
	cmp r2, lr
	blo _020AEDC8
	cmp r1, #0x0
	beq _020AEDB0
	cmp r12, #0x10000
	movhi r12, #0x0
	bhi _020AEDCC
_020AEDB0:
	ldr r1, _020AEDEC ; =s_managerState_
	mov r12, #0x1
	ldr r2, [r1, #0x4]
	sub r3, r2, lr
	str r3, [r1, #0x4]
	b _020AEDCC
_020AEDC8:
	mov r12, #0x0
_020AEDCC:
	cmp r12, #0x0
	ldrne r1, _020AEDF0 ; =0x0000FFFF
	movne r2, r0, lsr #0x3
	andne r0, r1, r3, lsr #0x3
	orrne r0, r0, r2, lsl #0x10
	moveq r0, #0x0
	ldmia sp!, {r4,pc}
	.balign 4
_020AEDE8: .word 0x0007FFF8
_020AEDEC: .word s_managerState_
_020AEDF0: .word 0x0000FFFF
	arm_func_end NNS_GfdAllocFrmPlttVram

	arm_func_start NNS_GfdInitFrmPlttVramManager
NNS_GfdInitFrmPlttVramManager: ; 0x020AEDF4
	stmdb sp!, {r4,lr}
	ldr r2, _020AEE2C ; =s_managerState_
	mov r4, r1
	str r0, [r2, #0x8]
	bl NNS_GfdResetFrmPlttVramState
	cmp r4, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r3, _020AEE30 ; =NNS_GfdAllocFrmPlttVram
	ldr r1, _020AEE34 ; =NNS_GfdDefaultFuncAllocPlttVram
	ldr r2, _020AEE38 ; =NNS_GfdFreeFrmPlttVram
	ldr r0, _020AEE3C ; =NNS_GfdDefaultFuncFreePlttVram
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020AEE2C: .word s_managerState_
_020AEE30: .word NNS_GfdAllocFrmPlttVram
_020AEE34: .word NNS_GfdDefaultFuncAllocPlttVram
_020AEE38: .word NNS_GfdFreeFrmPlttVram
_020AEE3C: .word NNS_GfdDefaultFuncFreePlttVram
	arm_func_end NNS_GfdInitFrmPlttVramManager
