	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start MI_SetWramBank
MI_SetWramBank:
	ldr r1, _020CD870 ; =0x04000247
	strb r0, [r1, #0x0]
	bx lr
	.balign 4
_020CD870: .word 0x04000247
