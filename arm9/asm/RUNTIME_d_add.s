	.include "asm/macros.inc"
	.include "global.inc"

	.extern __dsub_start

	.text

	arm_func_start _dadd
_dadd:
	stmdb sp!, {r4,lr}
	eors r12, r1, r3
	eormi r3, r3, #0x80000000
	bmi __dsub_start
	.global __dadd_start
__dadd_start:
	subs r12, r0, r2
	sbcs lr, r1, r3
	bhs _020E9B70
	adds r2, r2, r12
	adc r3, r3, lr
	subs r0, r0, r12
	sbc r1, r1, lr
_020E9B70:
	mov lr, #0x80000000
	mov r12, r1, lsr #0x14
	orr r1, lr, r1, lsl #0xb
	orr r1, r1, r0, lsr #0x15
	mov r0, r0, lsl #0xb
	movs r4, r12, lsl #0x15
	cmnne r4, #0x200000
	beq _020E9C6C
	mov r4, r3, lsr #0x14
	orr r3, lr, r3, lsl #0xb
	orr r3, r3, r2, lsr #0x15
	mov r2, r2, lsl #0xb
	movs lr, r4, lsl #0x15
	beq _020E9CB4
_020E9BA8:
	subs r4, r12, r4
	beq _020E9C00
	cmp r4, #0x20
	ble _020E9BE4
	cmp r4, #0x38
	movge r4, #0x3f
	sub r4, r4, #0x20
	rsb lr, r4, #0x20
	orrs lr, r2, r3, lsl lr
	mov r2, r3, lsr r4
	orrne r2, r2, #0x1
	adds r0, r0, r2
	adcs r1, r1, #0x0
	blo _020E9C28
	b _020E9C0C
_020E9BE4:
	rsb lr, r4, #0x20
	movs lr, r2, lsl lr
	rsb lr, r4, #0x20
	mov r2, r2, lsr r4
	orr r2, r2, r3, lsl lr
	mov r3, r3, lsr r4
	orrne r2, r2, #0x1
_020E9C00:
	adds r0, r0, r2
	adcs r1, r1, r3
	blo _020E9C28
_020E9C0C:
	add r12, r12, #0x1
	and r4, r0, #0x1
	movs r1, r1, rrx
	orr r0, r4, r0, rrx
	mov lr, r12, lsl #0x15
	cmn lr, #0x200000
	beq _020E9E38
_020E9C28:
	movs r2, r0, lsl #0x15
	mov r0, r0, lsr #0xb
	orr r0, r0, r1, lsl #0x15
	add r1, r1, r1
	mov r1, r1, lsr #0xc
	orr r1, r1, r12, lsl #0x14
	tst r2, #0x80000000
	ldmeqia sp!, {r4,lr}
	bxeq lr
	movs r2, r2, lsl #0x1
	andeqs r2, r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	adds r0, r0, #0x1
	adc r1, r1, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020E9C6C:
	cmp r12, #0x800
	movge lr, #0x80000000
	movlt lr, #0x0
	bics r12, r12, #0x800
	beq _020E9CD8
	orrs r4, r0, r1, lsl #0x1
	bne _020E9E14
	mov r4, r3, lsr #0x14
	mov r3, r3, lsl #0xb
	orr r3, r3, r2, lsr #0x15
	mov r2, r2, lsl #0xb
	movs r4, r4, lsl #0x15
	beq _020E9E00
	cmn r4, #0x200000
	bne _020E9E00
	orrs r4, r2, r3, lsl #0x1
	beq _020E9E00
	b _020E9E14
_020E9CB4:
	cmp r4, #0x800
	movge lr, #0x80000000
	movlt lr, #0x0
	bic r12, r12, #0x800
	bics r4, r4, #0x800
	beq _020E9D44
	orrs r4, r2, r3, lsl #0x1
	bne _020E9E14
	b _020E9E00
_020E9CD8:
	orrs r4, r0, r1, lsl #0x1
	beq _020E9D18
	mov r12, #0x1
	bic r1, r1, #0x80000000
	mov r4, r3, lsr #0x14
	mov r3, r3, lsl #0xb
	orr r3, r3, r2, lsr #0x15
	mov r2, r2, lsl #0xb
	movs r4, r4, lsl #0x15
	cmnne r4, #0x200000
	mov r4, r4, lsr #0x15
	orr r4, r4, lr, lsr #0x14
	beq _020E9CB4
	orr r3, r3, #0x80000000
	orr r12, r12, lr, lsr #0x14
	b _020E9BA8
_020E9D18:
	mov r12, r3, lsr #0x14
	mov r1, r3, lsl #0xb
	orr r1, r1, r2, lsr #0x15
	mov r0, r2, lsl #0xb
	movs r4, r12, lsl #0x15
	beq _020E9DCC
	cmn r4, #0x200000
	bne _020E9DCC
	orrs r4, r0, r1, lsl #0x1
	beq _020E9E00
	b _020E9E18
_020E9D44:
	orrs r4, r2, r3, lsl #0x1
	beq _020E9DDC
	mov r4, #0x1
	bic r3, r3, #0x80000000
	cmp r1, #0x0
	bpl _020E9D68
	orr r12, r12, lr, lsr #0x14
	orr r4, r4, lr, lsr #0x14
	b _020E9BA8
_020E9D68:
	adds r0, r0, r2
	adcs r1, r1, r3
	blo _020E9D88
	add r12, r12, #0x1
	and r4, r0, #0x1
	movs r1, r1, rrx
	mov r0, r0, rrx
	orr r0, r0, r4
_020E9D88:
	cmp r1, #0x0
	subges r12, r12, #0x1
	movs r2, r0, lsl #0x15
	mov r0, r0, lsr #0xb
	orr r0, r0, r1, lsl #0x15
	add r1, r1, r1
	orr r1, lr, r1, lsr #0xc
	orr r1, r1, r12, lsl #0x14
	ldmeqia sp!, {r4,lr}
	bxeq lr
	tst r2, #0x80000000
	ldmeqia sp!, {r4,lr}
	bxeq lr
	movs r2, r2, lsl #0x1
	andeqs r2, r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
_020E9DCC:
	mov r1, r3
	mov r0, r2
	ldmia sp!, {r4,lr}
	bx lr
_020E9DDC:
	cmp r1, #0x0
	subges r12, r12, #0x1
	mov r0, r0, lsr #0xb
	orr r0, r0, r1, lsl #0x15
	add r1, r1, r1
	orr r1, lr, r1, lsr #0xc
	orr r1, r1, r12, lsl #0x14
	ldmia sp!, {r4,lr}
	bx lr
_020E9E00:
	ldr r1, _020E9E58 ; =0x7FF00000
	orr r1, lr, r1
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020E9E14:
	mov r1, r3
_020E9E18:
	mvn r0, #0x0
	bic r1, r0, #0x80000000
	ldmia sp!, {r4,lr}
	bx lr
_020E9E28: ; 0x020E9E28
	mvn r0, #0x0
	bic r1, r0, #0x80000000
	ldmia sp!, {r4,lr}
	bx lr
_020E9E38:
	cmp r12, #0x800
	movge lr, #0x80000000
	movlt lr, #0x0
	ldr r1, _020E9E58 ; =0x7FF00000
	orr r1, lr, r1
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020E9E58: .word 0x7FF00000
	arm_func_end _dadd
