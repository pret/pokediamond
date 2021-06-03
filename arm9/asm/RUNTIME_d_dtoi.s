	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start _dfix
_dfix: ; 0x020E9F60
	bic r3, r1, #0x80000000
	ldr r2, _020E9FA8 ; =0x0000041E
	subs r2, r2, r3, lsr #0x14
	ble _020E9F9C
	cmp r2, #0x20
	bge _020E9F94
	mov r3, r1, lsl #0xb
	orr r3, r3, #0x80000000
	orr r3, r3, r0, lsr #0x15
	cmp r1, #0x0
	mov r0, r3, lsr r2
	rsbmi r0, r0, #0x0
	bx lr
_020E9F94:
	mov r0, #0x0
	bx lr
_020E9F9C:
	mvn r0, r1, asr #0x1f
	add r0, r0, #0x80000000
	bx lr
	.balign 4
_020E9FA8: .word 0x0000041E
    arm_func_end _dfix
