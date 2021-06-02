	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNS_G2dGetUnpackedScreenData
NNS_G2dGetUnpackedScreenData: ; 0x020B0180
	stmdb sp!, {r4,lr}
	mov r4, r1
	ldr r1, _020B01AC ; =0x5343524E
	bl NNS_G2dFindBinaryBlock
	cmp r0, #0x0
	addne r0, r0, #0x8
	strne r0, [r4, #0x0]
	movne r0, #0x1
	moveq r0, #0x0
	streq r0, [r4, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020B01AC: .word 0x5343524E
	arm_func_end NNS_G2dGetUnpackedScreenData
