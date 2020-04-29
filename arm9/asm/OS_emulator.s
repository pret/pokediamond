    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_GetConsoleType
OS_GetConsoleType: ; 0x020CBBC0
	ldr r0, _020CBBD0 ; =0x82000001
	ldr r1, _020CBBD4 ; =0x02106828
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020CBBD0: .word 0x82000001
_020CBBD4: .word 0x02106828

	arm_func_start OS_IsRunOnEmulator
OS_IsRunOnEmulator:
	mov r0, #0x0
	bx lr
