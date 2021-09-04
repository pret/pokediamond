	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _ExitProcess
_ExitProcess: ; 0x020EC704
	ldr ip, _020EC70C ; =sys_exit
	bx r12
	.balign 4
_020EC70C: .word sys_exit

	exception _ExitProcess, 13, 0x00000000
