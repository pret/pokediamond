    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OSi_SetTimerReserved
OSi_SetTimerReserved: ; 0x037FA348
	ldr	r1, _037FA360	; =_0380791C
	ldrh	r3, [r1]
	mov	r2, #1
	orr	r0, r3, r2, lsl r0
	strh	r0, [r1]
	bx	lr
_037FA360:	.word	_0380791C
