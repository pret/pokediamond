/* rom2.s TODO: Disassemble */
	.include "asm/macros.inc"

	.section .text

	.incbin "baserom.nds", 0xD9150, 0x16AE0

	arm_func_start _ll_mul
_ll_mul: ; 0x020EBC30
	stmdb sp!, {r4, r5, lr}
	umull r5, r4, r0, r2
	mla r4, r0, r3, r4
	mla r4, r2, r1, r4
	mov r1, r4
	mov r0, r5
	ldmia sp!, {r4, r5, lr}
	bx lr

	arm_func_start _ll_shl
_ll_shl: ; 0x020EBC50
	ands r2, r2, #0x3F
	bxeq lr
	subs r3, r2, #0x20
	bge _020EBC74
	rsb r3, r2, #0x20
	mov r1, r1, lsl r2
	orr r1, r1, r0, lsr r3
	mov r0, r0, lsl r2
	bx lr
_020EBC74:
	mov r1, r0, lsl r3
	mov r0, #0x0
	bx lr

	arm_func_start _s32_div_f
_s32_div_f: ; 0x20EBC80
	; Test whether the args have different signs
	eor ip, r0, r1
	and ip, ip, #0x80000000
	; Test the sign of the numerator, and make it positive
	cmp r0, #0x0
	rsblt r0, r0, #0x0
	addlt ip, ip, #1
	; Make the denominator positive, also test for div0
	cmp r1, #0x0
	rsblt r1, r1, #0x0
	beq _020EBE78
	; If the numerator is less than the denominator, return (0, numerator)
	cmp r0, r1
	movcc r1, r0
	movcc r0, #0x0
	bcc _020EBE78
	; Do the actual division
	mov r2, #0x1c
	mov r3, r0, lsr #0x4
	cmp r1, r3, lsr #0xc
	suble r2, r2, #0x10
	movle r3, r3, lsr #0x10
	cmp r1, r3, lsr #0x4
	suble r2, r2, #0x8
	movle r3, r3, lsr #0x8
	cmp r1, r3
	suble r2, r2, #0x4
	movle r3, r3, lsr #0x4
	mov r0, r0, lsl r2
	rsb r1, r1, #0x0
	adds r0, r0, r0
	add r2, r2, r2, lsl #0x1
	add pc, pc, r2, lsl #0x2
	nop
	.rept 32
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	.endr
	mov r1, r3
_020EBE78:
	; If the signs differed originally, negate quotient
	ands r3, ip, #0x80000000
	rsbne r0, r0, #0x0
	; If the numerator was negative, negate remainder
	ands r3, ip, #0x1
	rsbne r1, r1, #0x0
	bx lr

; required to make the linker happy :

	arm_func_start _u32_div_f
_u32_div_f: ; 0x020EBE8C
	cmp r1, #0x0
	bxeq lr ; About as wrong as we can be
	cmp r0, r1
	movcc r1, r0
	movcc r0, #0x0
	bxcc lr
	mov r2, #0x1c
	mov r3, r0, lsr #0x4
	cmp r1, r3, lsr #0xc
	suble r2, r2, #0x10
	movle r3, r3, lsr #0x10
	cmp r1, r3, lsr #0x4
	suble r2, r2, #0x8
	movle r3, r3, lsr #0x8
	cmp r1, r3
	suble r2, r2, #0x4
	movle r3, r3, lsr #0x4
	mov r0, r0, lsl r2
	rsb r1, r1, #0x0
	adds r0, r0, r0
	add r2, r2, r2, lsl #0x1
	add pc, pc, r2, lsl #0x2
	nop
	.rept 32
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	.endr
	mov r1, r3
	bx lr

	.incbin "baserom.nds", 0xF0070, 0x55C

	.global FUN_020EC5CC
FUN_020EC5CC:
	.incbin "baserom.nds", 0xF05CC, 0xC8

	.global FUN_020EC694
FUN_020EC694:
.incbin "baserom.nds", 0xF0694, 0x7C

	.section .data
.incbin "baserom.nds", 0xF0710, 0x3F8
