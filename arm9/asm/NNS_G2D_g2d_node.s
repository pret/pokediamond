	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; NNSi_G2dInitializeNode
	arm_func_start FUN_020B1AD4
FUN_020B1AD4: ; 0x020B1AD4
	mov r2, #0x0
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
	mov r1, #0x1
	str r1, [r0, #0x8]
	ldr ip, _020B1AF4 ; =FUN_020B1A68
	add r0, r0, #0xc
	bx r12
	.balign 4
_020B1AF4: .word FUN_020B1A68
	arm_func_end FUN_020B1AD4

