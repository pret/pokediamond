	.include "global.inc"
	.include "asm/macros.inc"

	.text

	arm_func_start __msl_generic_count_bits64
__msl_generic_count_bits64: ; 0x020E998C
	mov r3, r0, lsr #0x1
	ldr r2, _020E9A14 ; =0x55555555
	orr r3, r3, r1, lsl #0x1f
	and r3, r3, r2
	subs r12, r0, r3
	and r2, r2, r1, lsr #0x1
	ldr r0, _020E9A18 ; =0x33333333
	sbc r3, r1, r2
	mov r1, r12, lsr #0x2
	orr r1, r1, r3, lsl #0x1e
	and r2, r12, r0
	and r1, r1, r0
	adds r2, r2, r1
	and r1, r3, r0
	and r0, r0, r3, lsr #0x2
	adc r1, r1, r0
	mov r0, r2, lsr #0x4
	orr r0, r0, r1, lsl #0x1c
	adds r2, r2, r0
	ldr r0, _020E9A1C ; =0x0F0F0F0F
	adc r1, r1, r1, lsr #0x4
	and r3, r2, r0
	and r2, r1, r0
	mov r0, r3, lsr #0x8
	orr r0, r0, r2, lsl #0x18
	adds r1, r3, r0
	adc r2, r2, r2, lsr #0x8
	mov r0, r1, lsr #0x10
	orr r0, r0, r2, lsl #0x10
	adds r1, r1, r0
	adc r0, r2, r2, lsr #0x10
	adds r0, r1, r0
	and r0, r0, #0xff
	bx lr
	.balign 4
_020E9A14: .word 0x55555555
_020E9A18: .word 0x33333333
_020E9A1C: .word 0x0F0F0F0F
	arm_func_end __msl_generic_count_bits64

	arm_func_start __signbitd
__signbitd:
	stmdb sp!, {r0-r3}
	ldr r0, [sp, #0x4]
	and r0, r0, #0x80000000
	add sp, sp, #0x10
	bx lr
	arm_func_end __signbitd

	arm_func_start __fpclassifyd
__fpclassifyd: ; 0x020E9A34
	stmdb sp!, {r0-r3}
	ldr r2, [sp, #0x4]
	ldr r0, _020E9A9C ; =0x7FF00000
	ands r1, r2, r0
	beq _020E9A70
	cmp r1, r0
	bne _020E9A90
	ldr r0, _020E9AA0 ; =0x000FFFFF
	tst r2, r0
	ldreq r0, [sp, #0x0]
	add sp, sp, #0x10
	cmpeq r0, #0x0
	movne r0, #0x1
	moveq r0, #0x2
	bx lr
_020E9A70:
	ldr r0, _020E9AA0 ; =0x000FFFFF
	tst r2, r0
	ldreq r0, [sp, #0x0]
	add sp, sp, #0x10
	cmpeq r0, #0x0
	movne r0, #0x5
	moveq r0, #0x3
	bx lr
_020E9A90:
	mov r0, #0x4
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E9A9C: .word 0x7FF00000
_020E9AA0: .word 0x000FFFFF
	arm_func_end __fpclassifyd

	arm_func_start scalbn
scalbn: ; 0x020E9AA4
	stmdb sp!, {r3-r4,lr}
	sub sp, sp, #0x4
	mov r4, r2
	add r2, sp, #0x0
	bl frexp
	ldr r2, [sp, #0x0]
	add r2, r2, r4
	str r2, [sp, #0x0]
	bl ldexp
	add sp, sp, #0x4
	ldmia sp!, {r3-r4,pc}
	arm_func_end scalbn

	exception scalbn, 45, 0x00200100
