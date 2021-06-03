	.include "asm/macros.inc"
	.include "global.inc"

    .extern __dadd_start

    .text

	arm_func_start _drsb
_drsb: ; 0x020EA5B4
	eor r1, r1, r3
	eor r3, r1, r3
	eor r1, r1, r3
	eor r0, r0, r2
	eor r2, r0, r2
	eor r0, r0, r2

	arm_func_start _dsub
_dsub:
	stmdb sp!, {r4,lr}
	eors r12, r1, r3
	eormi r3, r3, #0x80000000
	bmi __dadd_start
	.global __dsub_start
__dsub_start:
	subs r12, r0, r2
	sbcs lr, r1, r3
	bhs _020EA5FC
	eor lr, lr, #0x80000000
	adds r2, r2, r12
	adc r3, r3, lr
	subs r0, r0, r12
	sbc r1, r1, lr
_020EA5FC:
	mov lr, #0x80000000
	mov r12, r1, lsr #0x14
	orr r1, lr, r1, lsl #0xb
	orr r1, r1, r0, lsr #0x15
	mov r0, r0, lsl #0xb
	movs r4, r12, lsl #0x15
	cmnne r4, #0x200000
	beq _020EA800
	mov r4, r3, lsr #0x14
	orr r3, lr, r3, lsl #0xb
	orr r3, r3, r2, lsr #0x15
	mov r2, r2, lsl #0xb
	movs lr, r4, lsl #0x15
	beq _020EA848
_020EA634:
	subs r4, r12, r4
	beq _020EA6DC
	cmp r4, #0x20
	ble _020EA670
	cmp r4, #0x38
	movge r4, #0x3f
	sub r4, r4, #0x20
	rsb lr, r4, #0x20
	orrs lr, r2, r3, lsl lr
	mov r2, r3, lsr r4
	orrne r2, r2, #0x1
	subs r0, r0, r2
	sbcs r1, r1, #0x0
	bmi _020EA698
	b _020EA788
_020EA670:
	rsb lr, r4, #0x20
	movs lr, r2, lsl lr
	rsb lr, r4, #0x20
	mov r2, r2, lsr r4
	orr r2, r2, r3, lsl lr
	mov r3, r3, lsr r4
	orrne r2, r2, #0x1
	subs r0, r0, r2
	sbcs r1, r1, r3
	bpl _020EA788
_020EA698:
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
_020EA6DC:
	subs r0, r0, r2
	sbc r1, r1, r3
	orrs lr, r1, r0
	beq _020EA96C
	mov lr, r12, lsl #0x14
	and lr, lr, #0x80000000
	bic r12, r12, #0x800
	cmp r1, #0x0
	bmi _020EA764
	bne _020EA714
	sub r12, r12, #0x20
	movs r1, r0
	mov r0, #0x0
	bmi _020EA730
_020EA714:
	clz r4, r1
	movs r1, r1, lsl r4
	rsb r4, r4, #0x20
	orr r1, r1, r0, lsr r4
	rsb r4, r4, #0x20
	mov r0, r0, lsl r4
	sub r12, r12, r4
_020EA730:
	cmp r12, #0x0
	bgt _020EA76C
	rsb r12, r12, #0xc
	cmp r12, #0x20
	movge r0, r1
	movge r1, #0x0
	subge r12, r12, #0x20
	rsb r4, r12, #0x20
	mov r0, r0, lsr r12
	orr r0, r0, r1, lsl r4
	orr r1, lr, r1, lsr r12
	ldmia sp!, {r4,lr}
	bx lr
_020EA764:
	cmp r1, #0x0
	subges r12, r12, #0x1
_020EA76C:
	mov r0, r0, lsr #0xb
	orr r0, r0, r1, lsl #0x15
	add r1, r1, r1
	orr r1, lr, r1, lsr #0xc
	orr r1, r1, r12, lsl #0x14
	ldmia sp!, {r4,lr}
	bx lr
_020EA788:
	mov lr, r12, lsl #0x14
	and lr, lr, #0x80000000
	bic r12, r12, #0x800
	cmp r1, #0x0
	bne _020EA7AC
	sub r12, r12, #0x20
	movs r1, r0
	mov r0, #0x0
	bmi _020EA7C8
_020EA7AC:
	clz r4, r1
	movs r1, r1, lsl r4
	rsb r4, r4, #0x20
	orr r1, r1, r0, lsr r4
	rsb r4, r4, #0x20
	mov r0, r0, lsl r4
	sub r12, r12, r4
_020EA7C8:
	cmp r12, #0x0
	orrgt r12, r12, lr, lsr #0x14
	bgt _020EA698
	rsb r12, r12, #0xc
	cmp r12, #0x20
	movge r0, r1
	movge r1, #0x0
	subge r12, r12, #0x20
	rsb r4, r12, #0x20
	mov r0, r0, lsr r12
	orr r0, r0, r1, lsl r4
	orr r1, lr, r1, lsr r12
	ldmia sp!, {r4,lr}
	bx lr
_020EA800:
	cmp r12, #0x800
	movge lr, #0x80000000
	movlt lr, #0x0
	bics r12, r12, #0x800
	beq _020EA86C
	orrs r4, r0, r1, lsl #0x1
	bne _020EA948
	mov r4, r3, lsr #0x14
	mov r3, r3, lsl #0xb
	orr r3, r3, r2, lsr #0x15
	mov r2, r2, lsl #0xb
	movs r4, r4, lsl #0x15
	beq _020EA934
	cmn r4, #0x200000
	bne _020EA934
	orrs r4, r2, r3, lsl #0x1
	beq _020EA95C
	b _020EA948
_020EA848:
	cmp r4, #0x800
	movge lr, #0x80000000
	movlt lr, #0x0
	bic r12, r12, #0x800
	bics r4, r4, #0x800
	beq _020EA8E4
	orrs r4, r2, r3, lsl #0x1
	bne _020EA948
	b _020EA934
_020EA86C:
	orrs r4, r0, r1, lsl #0x1
	beq _020EA8AC
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
	beq _020EA848
	orr r3, r3, #0x80000000
	orr r12, r12, lr, lsr #0x14
	b _020EA634
_020EA8AC:
	mov r12, r3, lsr #0x14
	mov r1, r3, lsl #0xb
	orr r1, r1, r2, lsr #0x15
	mov r0, r2, lsl #0xb
	movs r4, r12, lsl #0x15
	beq _020EA8D8
	cmn r4, #0x200000
	bne _020EA900
	orrs r4, r0, r1, lsl #0x1
	bne _020EA94C
	b _020EA934
_020EA8D8:
	orrs r4, r0, r1, lsl #0x1
	beq _020EA96C
	b _020EA900
_020EA8E4:
	orrs r4, r2, r3, lsl #0x1
	beq _020EA910
	mov r4, #0x1
	bic r3, r3, #0x80000000
	orr r12, r12, lr, lsr #0x14
	orr r4, r4, lr, lsr #0x14
	b _020EA634
_020EA900:
	mov r1, r3
	mov r0, r2
	ldmia sp!, {r4,lr}
	bx lr
_020EA910:
	cmp r1, #0x0
	subges r12, r12, #0x1
	mov r0, r0, lsr #0xb
	orr r0, r0, r1, lsl #0x15
	add r1, r1, r1
	orr r1, lr, r1, lsr #0xc
	orr r1, r1, r12, lsl #0x14
	ldmia sp!, {r4,lr}
	bx lr
_020EA934:
	ldr r1, _020EA97C ; =0x7FF00000
	orr r1, lr, r1
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020EA948:
	mov r1, r3
_020EA94C:
	mvn r0, #0x0
	bic r1, r0, #0x80000000
	ldmia sp!, {r4,lr}
	bx lr
_020EA95C:
	mvn r0, #0x0
	bic r1, r0, #0x80000000
	ldmia sp!, {r4,lr}
	bx lr
_020EA96C:
	mov r1, #0x0
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020EA97C: .word 0x7FF00000
