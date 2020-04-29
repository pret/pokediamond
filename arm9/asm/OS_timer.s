    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OSi_SetTimerReserved
OSi_SetTimerReserved: ; 0x020CCBF0
	ldr r1, _020CCC08 ; =OSi_TimerReserved
	mov r2, #0x1
	ldrh r3, [r1, #0x0]
	orr r0, r3, r2, lsl r0
	strh r0, [r1, #0x0]
	bx lr
	.balign 4
_020CCC08: .word OSi_TimerReserved
