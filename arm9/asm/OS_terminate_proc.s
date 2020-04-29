	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start OS_Halt
OS_Halt: ; 0x020CD844
	mov r0, #0x0
	mcr p15, 0x0, r0, c7, c0, 0x4
	bx lr

	arm_func_start OS_Terminate
OS_Terminate: ; 0x020CD850
	stmdb sp!, {lr}
	sub sp, sp, #0x4
_020CD858:
	bl OS_DisableInterrupts
	bl OS_Halt
	b _020CD858
