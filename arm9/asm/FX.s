	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start FX_Modf
FX_Modf: ; 0x020C5928
	cmp r0, #0x0
	blt _020C5948
	ldr r2, _020C596C ; =0x7FFFF000
	ldr r3, _020C5970 ; =0x00000FFF
	and r2, r0, r2
	str r2, [r1, #0x0]
	and r0, r0, r3
	bx lr
_020C5948:
	ldr r2, _020C596C ; =0x7FFFF000
	rsb r3, r0, #0x0
	ldr r0, _020C5970 ; =0x00000FFF
	and r2, r3, r2
	rsb r2, r2, #0x0
	and r0, r3, r0
	str r2, [r1, #0x0]
	rsb r0, r0, #0x0
	bx lr
	.balign 4
_020C596C: .word 0x7FFFF000
_020C5970: .word 0x00000FFF

	arm_func_start FX_Init
FX_Init: ; 0x020C5974
	bx lr
