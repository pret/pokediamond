	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _ffix
_ffix: ; 0x020EB4C0
	bic r1, r0, #0x80000000
	mov r2, #0x9e
	subs r2, r2, r1, lsr #0x17
	ble _020EB4E8
	mov r1, r1, lsl #0x8
	orr r1, r1, #0x80000000
	cmp r0, #0x0
	mov r0, r1, lsr r2
	rsbmi r0, r0, #0x0
	bx lr
_020EB4E8:
	mvn r0, r0, asr #0x1f
	add r0, r0, #0x80000000
	bx lr
