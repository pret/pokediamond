	.include "asm/macros.inc"
	.include "global.inc"

    .data

    .global random_next
random_next: ; 0x02106DE0
    .word 0x00000001
    .size random_next,.-random_next

    .text

	arm_func_start rand
rand: ; 0x020E19EC
	ldr r2, _020E1A14 ; =random_next
	ldr r0, _020E1A18 ; =0x41C64E6D
	ldr r3, [r2, #0x0]
	ldr r1, _020E1A1C ; =0x00007FFF
	mul r0, r3, r0
	add r0, r0, #0x39
	add r0, r0, #0x3000
	str r0, [r2, #0x0]
	and r0, r1, r0, lsr #0x10
	bx lr
	.balign 4
_020E1A14: .word random_next
_020E1A18: .word 0x41C64E6D
_020E1A1C: .word 0x00007FFF
    arm_func_end rand

	arm_func_start srand
srand: ; 0x020E1A20
	ldr r1, _020E1A2C ; =random_next
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020E1A2C: .word random_next
    arm_func_end srand
