	.include "global.inc"
	.include "asm/macros.inc"

	.text

	arm_func_start nan
nan: ; 0x020DE2E4
	ldr r0, _020DE2F4 ; =__float_nan
	ldr ip, _020DE2F8 ; =_f2d
	ldr r0, [r0, #0x0]
	bx r12
	.balign 4
_020DE2F4: .word __float_nan
_020DE2F8: .word _f2d
	arm_func_end nan

	exception nan, 25, 0x00000000
