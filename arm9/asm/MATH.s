	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start MATH_CountPopulation
MATH_CountPopulation: ; 0x020DDC5C
	ldr r1, _020DDC94 ; =0x55555555
	ldr r2, _020DDC98 ; =0x33333333
	and r1, r1, r0, lsr #0x1
	sub r0, r0, r1
	and r1, r0, r2
	and r0, r2, r0, lsr #0x2
	add r1, r1, r0
	ldr r0, _020DDC9C ; =0x0F0F0F0F
	add r1, r1, r1, lsr #0x4
	and r0, r1, r0
	add r0, r0, r0, lsr #0x8
	add r0, r0, r0, lsr #0x10
	and r0, r0, #0xff
	bx lr
	.balign 4
_020DDC94: .word 0x55555555
_020DDC98: .word 0x33333333
_020DDC9C: .word 0x0F0F0F0F
