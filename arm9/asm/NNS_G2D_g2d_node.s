	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNSi_G2dInitializeNode
NNSi_G2dInitializeNode: ; 0x020B1AD4
	mov r2, #0x0
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
	mov r1, #0x1
	str r1, [r0, #0x8]
	ldr ip, _020B1AF4 ; =NNSi_G2dSrtcInitControl
	add r0, r0, #0xc
	bx r12
	.balign 4
_020B1AF4: .word NNSi_G2dSrtcInitControl
	arm_func_end NNSi_G2dInitializeNode
