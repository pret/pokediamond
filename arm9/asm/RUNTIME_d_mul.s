	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start _dmul
_dmul: ; 0x020EA0B4
	stmdb sp!, {r4-r7,lr}
	eor lr, r1, r3
	and lr, lr, #0x80000000
	mov r12, r1, lsr #0x14
	mov r1, r1, lsl #0xb
	orr r1, r1, r0, lsr #0x15
	mov r0, r0, lsl #0xb
	movs r6, r12, lsl #0x15
	cmnne r6, #0x200000
	beq _020EA1BC
	orr r1, r1, #0x80000000
	bic r12, r12, #0x800
	mov r4, r3, lsr #0x14
	mov r3, r3, lsl #0xb
	orr r3, r3, r2, lsr #0x15
	mov r2, r2, lsl #0xb
	movs r5, r4, lsl #0x15
	cmnne r5, #0x200000
	beq _020EA204
	orr r3, r3, #0x80000000
	bic r4, r4, #0x800
_020EA108:
	add r12, r4, r12
	umull r5, r4, r0, r2
	umull r7, r6, r0, r3
	adds r4, r7, r4
	adc r6, r6, #0x0
	umull r7, r0, r1, r2
	adds r4, r7, r4
	adcs r0, r0, r6
	umull r7, r2, r1, r3
	adc r1, r2, #0x0
	adds r0, r0, r7
	adc r1, r1, #0x0
	orrs r4, r4, r5
	orrne r0, r0, #0x1
	cmp r1, #0x0
	blt _020EA154
	sub r12, r12, #0x1
	adds r0, r0, r0
	adc r1, r1, r1
_020EA154:
	add r12, r12, #0x2
	subs r12, r12, #0x400
	bmi _020EA2F0
	beq _020EA2F0
	mov r6, r12, lsl #0x14
	cmn r6, #0x100000
	bmi _020EA3F0
	movs r2, r0, lsl #0x15
	mov r0, r0, lsr #0xb
	orr r0, r0, r1, lsl #0x15
	add r1, r1, r1
	orr r1, lr, r1, lsr #0xc
	orr r1, r1, r12, lsl #0x14
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	tst r2, #0x80000000
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	movs r2, r2, lsl #0x1
	andeqs r2, r0, #0x1
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	adds r0, r0, #0x1
	adc r1, r1, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020EA1BC:
	bics r12, r12, #0x800
	beq _020EA218
	orrs r6, r0, r1, lsl #0x1
	bne _020EA3A4
	mov r4, r3, lsr #0x14
	mov r3, r3, lsl #0xb
	orr r3, r3, r2, lsr #0x15
	mov r2, r2, lsl #0xb
	movs r5, r4, lsl #0x15
	beq _020EA1F8
	cmn r5, #0x200000
	bne _020EA390
	orrs r5, r2, r3, lsl #0x1
	beq _020EA390
	b _020EA3A4
_020EA1F8:
	orrs r5, r3, r2
	beq _020EA3B8
	b _020EA390
_020EA204:
	bics r4, r4, #0x800
	beq _020EA2AC
	orrs r6, r2, r3, lsl #0x1
	bne _020EA3A4
	b _020EA390
_020EA218:
	orrs r6, r0, r1, lsl #0x1
	beq _020EA280
	mov r12, #0x1
	cmp r1, #0x0
	bne _020EA23C
	sub r12, r12, #0x20
	movs r1, r0
	mov r0, #0x0
	bmi _020EA258
_020EA23C:
	clz r6, r1
	movs r1, r1, lsl r6
	rsb r6, r6, #0x20
	orr r1, r1, r0, lsr r6
	rsb r6, r6, #0x20
	mov r0, r0, lsl r6
	sub r12, r12, r6
_020EA258:
	mov r4, r3, lsr #0x14
	mov r3, r3, lsl #0xb
	orr r3, r3, r2, lsr #0x15
	mov r2, r2, lsl #0xb
	movs r5, r4, lsl #0x15
	cmnne r5, #0x200000
	beq _020EA204
	orr r3, r3, #0x80000000
	bic r4, r4, #0x800
	b _020EA108
_020EA280:
	mov r4, r3, lsr #0x14
	mov r3, r3, lsl #0xb
	orr r3, r3, r2, lsr #0x15
	mov r2, r2, lsl #0xb
	movs r5, r4, lsl #0x15
	beq _020EA404
	cmn r5, #0x200000
	bne _020EA404
	orrs r6, r2, r3, lsl #0x1
	beq _020EA3B8
	b _020EA3A4
_020EA2AC:
	orrs r5, r2, r3, lsl #0x1
	beq _020EA404
	mov r4, #0x1
	cmp r3, #0x0
	bne _020EA2D0
	sub r4, r4, #0x20
	movs r3, r2
	mov r2, #0x0
	bmi _020EA108
_020EA2D0:
	clz r6, r3
	movs r3, r3, lsl r6
	rsb r6, r6, #0x20
	orr r3, r3, r2, lsr r6
	rsb r6, r6, #0x20
	mov r2, r2, lsl r6
	sub r4, r4, r6
	b _020EA108
_020EA2F0:
	cmn r12, #0x34
	beq _020EA388
	bmi _020EA3E0
	mov r2, r1
	mov r3, r0
	add r4, r12, #0x34
	cmp r4, #0x20
	movge r2, r3
	movge r3, #0x0
	subge r4, r4, #0x20
	rsb r5, r4, #0x20
	mov r2, r2, lsl r4
	orr r2, r2, r3, lsr r5
	movs r3, r3, lsl r4
	orrne r2, r2, #0x1
	rsb r12, r12, #0xc
	cmp r12, #0x20
	movge r0, r1
	movge r1, #0x0
	subge r12, r12, #0x20
	rsb r4, r12, #0x20
	mov r0, r0, lsr r12
	orr r0, r0, r1, lsl r4
	orr r1, lr, r1, lsr r12
	cmp r2, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	tst r2, #0x80000000
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	movs r2, r2, lsl #0x1
	andeqs r2, r0, #0x1
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	adds r0, r0, #0x1
	adc r1, r1, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020EA388:
	orr r0, r0, r1, lsl #0x1
	b _020EA3C8
_020EA390:
	ldr r1, _020EA414 ; =0x7FF00000
	orr r1, lr, r1
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020EA3A4:
	mov r1, r3
	mvn r0, #0x0
	bic r1, r0, #0x80000000
	ldmia sp!, {r4-r7,lr}
	bx lr
_020EA3B8:
	mvn r0, #0x0
	bic r1, r0, #0x80000000
	ldmia sp!, {r4-r7,lr}
	bx lr
_020EA3C8:
	movs r2, r0
	mov r1, lr
	mov r0, #0x0
	addne r0, r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020EA3E0:
	mov r1, lr
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020EA3F0:
	ldr r1, _020EA414 ; =0x7FF00000
	orr r1, lr, r1
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020EA404:
	mov r1, lr
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020EA414: .word 0x7FF00000
    arm_func_end _dmul
