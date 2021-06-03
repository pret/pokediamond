	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start _ffixu
_ffixu: ; 0x020EB4F4
	tst r0, #0x80000000
	bne _020EB518
	mov r1, #0x9e
	subs r1, r1, r0, lsr #0x17
	blt _020EB52C
	mov r2, r0, lsl #0x8
	orr r0, r2, #0x80000000
	mov r0, r0, lsr r1
	bx lr
_020EB518:
	mov r2, #0xff000000
	cmp r2, r0, lsl #0x1
	movcs r0, #0x0
	mvncc r0, #0x0
	bx lr
_020EB52C:
	mvn r0, #0x0
	bx lr
