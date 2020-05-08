	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start _dadd
_dadd:
	stmdb sp!, {r4,lr}
	eors r12, r1, r3
	eormi r3, r3, #0x80000000
	bmi _020EA5DC
_020E9B54:
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

	arm_func_start _d2f
_d2f:
	and r2, r1, #0x80000000
	mov r12, r1, lsr #0x14
	bics r12, r12, #0x800
	beq _020E9ED4
	mov r3, r12, lsl #0x15
	cmn r3, #0x200000
	bhs _020E9EB8
	subs r12, r12, #0x380
	bls _020E9EE4
	cmp r12, #0xff
	bge _020E9F54
	mov r1, r1, lsl #0xc
	orr r3, r2, r1, lsr #0x9
	orr r3, r3, r0, lsr #0x1d
	movs r1, r0, lsl #0x3
	orr r0, r3, r12, lsl #0x17
	bxeq lr
	tst r1, #0x80000000
	bxeq lr
	movs r1, r1, lsl #0x1
	andeqs r1, r0, #0x1
	addne r0, r0, #0x1
	bx lr
_020E9EB8:
	orrs r3, r0, r1, lsl #0xc
	bne _020E9ECC
	mov r0, #0xff000000
	orr r0, r2, r0, lsr #0x1
	bx lr
_020E9ECC:
	mvn r0, #0x80000000
	bx lr
_020E9ED4:
	orrs r3, r0, r1, lsl #0xc
	bne _020E9F4C
	mov r0, r2
	bx lr
_020E9EE4:
	cmn r12, #0x17
	beq _020E9F38
	bmi _020E9F4C
	mov r1, r1, lsl #0xb
	orr r1, r1, #0x80000000
	mov r3, r1, lsr #0x8
	orr r3, r3, r0, lsr #0x1d
	rsb r12, r12, #0x1
	movs r1, r0, lsl #0x3
	orr r0, r2, r3, lsr r12
	rsb r12, r12, #0x20
	mov r3, r3, lsl r12
	orrne r3, r3, #0x1
	movs r1, r3
	bxeq lr
	tst r1, #0x80000000
	bxeq lr
	movs r1, r1, lsl #0x1
	andeqs r1, r0, #0x1
	addne r0, r0, #0x1
	bx lr
_020E9F38:
	orr r0, r0, r1, lsl #0xc
	movs r1, r0
	mov r0, r2
	addne r0, r0, #0x1
	bx lr
_020E9F4C:
	mov r0, r2
	bx lr
_020E9F54:
	mov r0, #0xff000000
	orr r0, r2, r0, lsr #0x1
	bx lr

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

	arm_func_start _ll_ufrom_d
_ll_ufrom_d: ; 0x020E9FAC
	tst r1, #0x80000000
	bne _020EA010
	ldr r2, _020EA034 ; =0x0000043E
	subs r2, r2, r1, lsr #0x14
	blt _020EA028
	cmp r2, #0x40
	bge _020EA004
	mov r12, r1, lsl #0xb
	orr r12, r12, #0x80000000
	orr r12, r12, r0, lsr #0x15
	cmp r2, #0x20
	ble _020E9FEC
	sub r2, r2, #0x20
	mov r1, #0x0
	mov r0, r12, lsr r2
	bx lr
_020E9FEC:
	mov r3, r0, lsl #0xb
	mov r1, r12, lsr r2
	mov r0, r3, lsr r2
	rsb r2, r2, #0x20
	orr r0, r0, r12, lsl r2
	bx lr
_020EA004:
	mov r1, #0x0
	mov r0, #0x0
	bx lr
_020EA010:
	cmn r1, #0x100000
	cmpeq r0, #0x0
	bhi _020EA028
	mov r1, #0x0
	mov r0, #0x0
	bx lr
_020EA028:
	mvn r1, #0x0
	mvn r0, #0x0
	bx lr
	.balign 4
_020EA034: .word 0x0000043E

	arm_func_start _dflt
_dflt: ; 0x020EA038
	ands r2, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r0, #0x0
	mov r1, #0x0
	bxeq lr
	mov r3, #0x400
	add r3, r3, #0x1e
	clz r12, r0
	movs r0, r0, lsl r12
	sub r3, r3, r12
	movs r1, r0
	mov r0, r1, lsl #0x15
	add r1, r1, r1
	orr r1, r2, r1, lsr #0xc
	orr r1, r1, r3, lsl #0x14
	bx lr

	arm_func_start _dfltu
_dfltu: ; 0x020EA078
	cmp r0, #0x0
	mov r1, #0x0
	bxeq lr
	mov r3, #0x400
	add r3, r3, #0x1e
	bmi _020EA09C
	clz r12, r0
	movs r0, r0, lsl r12
	sub r3, r3, r12
_020EA09C:
	mov r1, r0
	mov r0, r1, lsl #0x15
	add r1, r1, r1
	mov r1, r1, lsr #0xc
	orr r1, r1, r3, lsl #0x14
	bx lr

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

	arm_func_start _dsqrt
_dsqrt: ; 0x020EA418
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020EA5A8 ; =0x7FF00000
	cmp r1, r2
	bhs _020EA564
	movs r12, r1, lsr #0x14
	beq _020EA510
	bic r1, r1, r2
	orr r1, r1, #0x100000
_020EA438:
	movs r12, r12, asr #0x1
	bhs _020EA44C
	sub r12, r12, #0x1
	movs r0, r0, lsl #0x1
	adc r1, r1, r1
_020EA44C:
	movs r3, r0, lsl #0x1
	adc r1, r1, r1
	mov r2, #0x0
	mov r4, #0x0
	mov lr, #0x200000
_020EA460:
	add r6, r4, lr
	cmp r6, r1
	addle r4, r6, lr
	suble r1, r1, r6
	addle r2, r2, lr
	movs r3, r3, lsl #0x1
	adc r1, r1, r1
	movs lr, lr, lsr #0x1
	bne _020EA460
	mov r0, #0x0
	mov r5, #0x0
	cmp r1, r4
	cmpeq r3, #0x80000000
	blo _020EA4A8
	subs r3, r3, #0x80000000
	sbc r1, r1, r4
	add r4, r4, #0x1
	mov r0, #0x80000000
_020EA4A8:
	movs r3, r3, lsl #0x1
	adc r1, r1, r1
	mov lr, #0x40000000
_020EA4B4:
	add r6, r5, lr
	cmp r4, r1
	cmpeq r6, r3
	bhi _020EA4D4
	add r5, r6, lr
	subs r3, r3, r6
	sbc r1, r1, r4
	add r0, r0, lr
_020EA4D4:
	movs r3, r3, lsl #0x1
	adc r1, r1, r1
	movs lr, lr, lsr #0x1
	bne _020EA4B4
	orrs r1, r1, r3
	biceq r0, r0, #0x1
	movs r1, r2, lsr #0x1
	movs r0, r0, rrx
	adcs r0, r0, #0x0
	adc r1, r1, #0x0
	add r1, r1, #0x20000000
	sub r1, r1, #0x100000
	add r1, r1, r12, lsl #0x14
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EA510:
	cmp r1, #0x0
	bne _020EA540
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mvn r12, #0x13
	clz r5, r0
	movs r0, r0, lsl r5
	sub r12, r12, r5
	mov r1, r0, lsr #0xb
	mov r0, r0, lsl #0x15
	b _020EA438
_020EA540:
	clz r2, r1
	movs r1, r1, lsl r2
	rsb r2, r2, #0x2b
	mov r1, r1, lsr #0xb
	orr r1, r1, r0, lsr r2
	rsb r2, r2, #0x20
	mov r0, r0, lsl r2
	rsb r12, r2, #0x1
	b _020EA438
_020EA564:
	tst r1, #0x80000000
	beq _020EA580
	bics r3, r1, #0x80000000
	cmpeq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	b _020EA58C
_020EA580:
	orrs r2, r0, r1, lsl #0xc
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
_020EA58C:
	ldr r2, _020EA5AC ; =0x7FF80000
	orr r1, r1, r2
	ldr r3, _020EA5B0 ; =0x021D74A8
	mov r4, #0x21
	str r4, [r3, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020EA5A8: .word 0x7FF00000
_020EA5AC: .word 0x7FF80000
_020EA5B0: .word 0x021D74A8

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
	bmi _020E9B54
_020EA5DC:
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

	arm_func_start _fadd
_fadd: ; 0x020EA980
	eors r2, r0, r1
	eormi r1, r1, #0x80000000
	bmi _020EB7BC
_020EA98C:
	subs r12, r0, r1
	subcc r0, r0, r12
	addcc r1, r1, r12
	mov r2, #0x80000000
	mov r3, r0, lsr #0x17
	orr r0, r2, r0, lsl #0x8
	ands r12, r3, #0xff
	cmpne r12, #0xff
	beq _020EAA20
	mov r12, r1, lsr #0x17
	orr r1, r2, r1, lsl #0x8
	ands r2, r12, #0xff
	beq _020EAA60
_020EA9C0:
	subs r12, r3, r12
	beq _020EA9D8
	rsb r2, r12, #0x20
	movs r2, r1, lsl r2
	mov r1, r1, lsr r12
	orrne r1, r1, #0x1
_020EA9D8:
	adds r0, r0, r1
	blo _020EA9F8
	and r1, r0, #0x1
	orr r0, r1, r0, rrx
	add r3, r3, #0x1
	and r2, r3, #0xff
	cmp r2, #0xff
	beq _020EAB68
_020EA9F8:
	ands r1, r0, #0xff
	add r0, r0, r0
	mov r0, r0, lsr #0x9
	orr r0, r0, r3, lsl #0x17
	tst r1, #0x80
	bxeq lr
	ands r1, r1, #0x7f
	andeqs r1, r0, #0x1
	addne r0, r0, #0x1
	bx lr
_020EAA20:
	cmp r3, #0x100
	movge r2, #0x80000000
	movlt r2, #0x0
	ands r3, r3, #0xff
	beq _020EAA84
	movs r0, r0, lsl #0x1
	bne _020EAB94
	mov r12, r1, lsr #0x17
	mov r1, r1, lsl #0x9
	ands r12, r12, #0xff
	beq _020EAB88
	cmp r12, #0xff
	blt _020EAB88
	cmp r1, #0x0
	beq _020EAB88
	b _020EAB94
_020EAA60:
	cmp r3, #0x100
	movge r2, #0x80000000
	movlt r2, #0x0
	and r3, r3, #0xff
	ands r12, r12, #0xff
	beq _020EAAE0
_020EAA78:
	movs r1, r1, lsl #0x1
	bne _020EAB94
	b _020EAB88
_020EAA84:
	movs r0, r0, lsl #0x1
	beq _020EAABC
	mov r3, #0x1
	mov r0, r0, lsr #0x1
	mov r12, r1, lsr #0x17
	mov r1, r1, lsl #0x8
	ands r12, r12, #0xff
	beq _020EAAE0
	cmp r12, #0xff
	beq _020EAA78
	orr r1, r1, #0x80000000
	orr r3, r3, r2, lsr #0x17
	orr r12, r12, r2, lsr #0x17
	b _020EA9C0
_020EAABC:
	mov r3, r1, lsr #0x17
	mov r0, r1, lsl #0x9
	ands r3, r3, #0xff
	beq _020EAB48
	cmp r3, #0xff
	blt _020EAB48
	cmp r0, #0x0
	beq _020EAB88
	b _020EAB80
_020EAAE0:
	movs r1, r1, lsl #0x1
	beq _020EAB50
	mov r1, r1, lsr #0x1
	mov r12, #0x1
	orr r3, r3, r2, lsr #0x17
	orr r12, r12, r2, lsr #0x17
	cmp r0, #0x0
	bmi _020EA9C0
	adds r0, r0, r1
	blo _020EAB14
	and r1, r0, #0x1
	orr r0, r1, r0, rrx
	add r12, r12, #0x1
_020EAB14:
	cmp r0, #0x0
	subge r12, r12, #0x1
	ands r1, r0, #0xff
	add r0, r0, r0
	mov r0, r0, lsr #0x9
	orr r0, r0, r12, lsl #0x17
	bxeq lr
	tst r1, #0x80
	bxeq lr
	ands r1, r1, #0x7f
	andeqs r1, r0, #0x1
	addne r0, r0, #0x1
	bx lr
_020EAB48:
	mov r0, r1
	bx lr
_020EAB50:
	cmp r0, #0x0
	subges r3, r3, #0x1
	add r0, r0, r0
	orr r0, r2, r0, lsr #0x9
	orr r0, r0, r3, lsl #0x17
	bx lr
_020EAB68:
	cmp r3, #0x100
	movge r2, #0x80000000
	movlt r2, #0x0
	mov r0, #0xff000000
	orr r0, r2, r0, lsr #0x1
	bx lr
_020EAB80:
	mvn r0, #0x80000000
	bx lr
_020EAB88:
	mov r0, #0xff000000
	orr r0, r2, r0, lsr #0x1
	bx lr
_020EAB94:
	mvn r0, #0x80000000
	bx lr
_020EAB9C: ; 0x020EAB9C
	mvn r0, #0x80000000
	bx lr

	arm_func_start _dgr
_dgr: ; 0x020EABA4
	mov r12, #0x200000
	cmn r12, r1, lsl #0x1
	bhs _020EAC18
	cmn r12, r3, lsl #0x1
	bhs _020EAC2C
_020EABB8:
	orrs r12, r3, r1
	bmi _020EABE8
	cmp r1, r3
	cmpeq r0, r2
	movhi r0, #0x1
	movls r0, #0x0
	bx lr
_020EABD4:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EABE8:
	orr r12, r0, r12, lsl #0x1
	orrs r12, r12, r2
	moveq r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x20000000
	msr cpsr_f, r12
	bxeq lr
	cmp r3, r1
	cmpeq r2, r0
	movhi r0, #0x1
	movls r0, #0x0
	bx lr
_020EAC18:
	bne _020EABD4
	cmp r0, #0x0
	bhi _020EABD4
	cmn r12, r3, lsl #0x1
	blo _020EABB8
_020EAC2C:
	bne _020EABD4
	cmp r2, #0x0
	bhi _020EABD4
	b _020EABB8

	arm_func_start _dleq
_dleq: ; 0x020EAC3C
	mov r12, #0x200000
	cmn r12, r1, lsl #0x1
	bhs _020EACBC
	cmn r12, r3, lsl #0x1
	bhs _020EACD0
_020EAC50:
	orrs r12, r3, r1
	bmi _020EAC84
	cmp r1, r3
	cmpeq r0, r2
	movls r0, #0x1
	movhi r0, #0x0
	bx lr
_020EAC6C:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x40000000
	orr r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EAC84:
	orr r12, r0, r12, lsl #0x1
	orrs r12, r12, r2
	moveq r0, #0x1
	bne _020EACA8
	mrs r12, cpsr
	bic r12, r12, #0x20000000
	orr r12, r12, #0x40000000
	msr cpsr_f, r12
	bxeq lr
_020EACA8:
	cmp r3, r1
	cmpeq r2, r0
	movls r0, #0x1
	movhi r0, #0x0
	bx lr
_020EACBC:
	bne _020EAC6C
	cmp r0, #0x0
	bhi _020EAC6C
	cmn r12, r3, lsl #0x1
	blo _020EAC50
_020EACD0:
	bne _020EAC6C
	cmp r2, #0x0
	bhi _020EAC6C
	b _020EAC50

	arm_func_start _dls
_dls: ; 0x020EACE0
	mov r12, #0x200000
	cmn r12, r1, lsl #0x1
	bhs _020EAD58
	cmn r12, r3, lsl #0x1
	bhs _020EAD6C
_020EACF4:
	orrs r12, r3, r1
	bmi _020EAD24
	cmp r1, r3
	cmpeq r0, r2
	movcc r0, #0x1
	movcs r0, #0x0
	bx lr
_020EAD10:
	mov r0, #0x0
	mrs r12, cpsr
	orr r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EAD24:
	orr r12, r0, r12, lsl #0x1
	orrs r12, r12, r2
	moveq r0, #0x0
	bne _020EAD44
	mrs r12, cpsr
	orr r12, r12, #0x20000000
	msr cpsr_f, r12
	bxeq lr
_020EAD44:
	cmp r3, r1
	cmpeq r2, r0
	movcc r0, #0x1
	movcs r0, #0x0
	bx lr
_020EAD58:
	bne _020EAD10
	cmp r0, #0x0
	bhi _020EAD10
	cmn r12, r3, lsl #0x1
	blo _020EACF4
_020EAD6C:
	bne _020EAD10
	cmp r2, #0x0
	bhi _020EAD10
	b _020EACF4

	arm_func_start _deq
_deq: ; 0x020EAD7C
	mov r12, #0x200000
	cmn r12, r1, lsl #0x1
	bhs _020EADE4
	cmn r12, r3, lsl #0x1
	bhs _020EADF8
_020EAD90:
	orrs r12, r3, r1
	bmi _020EADC0
	cmp r1, r3
	cmpeq r0, r2
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
_020EADAC:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr
_020EADC0:
	orr r12, r0, r12, lsl #0x1
	orrs r12, r12, r2
	moveq r0, #0x1
	bxeq lr
	cmp r3, r1
	cmpeq r2, r0
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
_020EADE4:
	bne _020EADAC
	cmp r0, #0x0
	bhi _020EADAC
	cmn r12, r3, lsl #0x1
	blo _020EAD90
_020EADF8:
	bne _020EADAC
	cmp r2, #0x0
	bhi _020EADAC
	b _020EAD90

	arm_func_start _dneq
_dneq: ; 0x020EAE08
	mov r12, #0x200000
	cmn r12, r1, lsl #0x1
	bhs _020EAE70
	cmn r12, r3, lsl #0x1
	bhs _020EAE84
_020EAE1C:
	orrs r12, r3, r1
	bmi _020EAE4C
	cmp r1, r3
	cmpeq r0, r2
	movne r0, #0x1
	moveq r0, #0x0
	bx lr
_020EAE38:
	mov r0, #0x1
	mrs r12, cpsr
	bic r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr
_020EAE4C:
	orr r12, r0, r12, lsl #0x1
	orrs r12, r12, r2
	moveq r0, #0x0
	bxeq lr
	cmp r3, r1
	cmpeq r2, r0
	movne r0, #0x1
	moveq r0, #0x0
	bx lr
_020EAE70:
	bne _020EAE38
	cmp r0, #0x0
	bhi _020EAE38
	cmn r12, r3, lsl #0x1
	blo _020EAE1C
_020EAE84:
	bne _020EAE38
	cmp r2, #0x0
	bhi _020EAE38
	b _020EAE1C

	arm_func_start _fgeq
_fgeq: ; 0x020EAE94
	mov r3, #0xff000000
	cmp r3, r0, lsl #0x1
	cmpcs r3, r1, lsl #0x1
	blo _020EAEDC
	cmp r0, #0x0
	bicmi r0, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r1, #0x0
	bicmi r1, r1, #0x80000000
	rsbmi r1, r1, #0x0
	cmp r0, r1
	movge r0, #0x1
	movlt r0, #0x0
	mrs r12, cpsr
	biclt r12, r12, #0x20000000
	orrge r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EAEDC:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr

	arm_func_start _fgr
_fgr: ; 0x020EAEF0
	mov r3, #0xff000000
	cmp r3, r0, lsl #0x1
	cmpcs r3, r1, lsl #0x1
	blo _020EAF38
	cmp r0, #0x0
	bicmi r0, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r1, #0x0
	bicmi r1, r1, #0x80000000
	rsbmi r1, r1, #0x0
	cmp r0, r1
	movgt r0, #0x1
	movle r0, #0x0
	mrs r12, cpsr
	bicle r12, r12, #0x20000000
	orrgt r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EAF38:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr

	arm_func_start _fleq
_fleq: ; 0x020EAF4C
	mov r3, #0xff000000
	cmp r3, r0, lsl #0x1
	cmpcs r3, r1, lsl #0x1
	blo _020EAF9C
	cmp r0, #0x0
	bicmi r0, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r1, #0x0
	bicmi r1, r1, #0x80000000
	rsbmi r1, r1, #0x0
	cmp r0, r1
	movle r0, #0x1
	movgt r0, #0x0
	mrs r12, cpsr
	orrgt r12, r12, #0x20000000
	bicgt r12, r12, #0x40000000
	bicle r12, r12, #0x20000000
	orrle r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr
_020EAF9C:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x40000000
	orr r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr

	arm_func_start _fls
_fls: ; 0x020EAFB4
	mov r3, #0xff000000
	cmp r3, r0, lsl #0x1
	cmpcs r3, r1, lsl #0x1
	blo _020EAFFC
	cmp r0, #0x0
	bicmi r0, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r1, #0x0
	bicmi r1, r1, #0x80000000
	rsbmi r1, r1, #0x0
	cmp r0, r1
	movlt r0, #0x1
	movge r0, #0x0
	mrs r12, cpsr
	orrge r12, r12, #0x20000000
	biclt r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EAFFC:
	mov r0, #0x0
	mrs r12, cpsr
	orr r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr

	arm_func_start _feq
_feq: ; 0x020EB010
	mov r3, #0xff000000
	cmp r3, r0, lsl #0x1
	blo _020EB064
	cmp r3, r1, lsl #0x1
	blo _020EB064
	orr r3, r0, r1
	movs r3, r3, lsl #0x1
	moveq r0, #0x0
	bne _020EB044
	mrs r12, cpsr
	orr r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr
_020EB044:
	cmp r0, r1
	movne r0, #0x1
	moveq r0, #0x0
	mrs r12, cpsr
	bicne r12, r12, #0x40000000
	orreq r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr
_020EB064:
	mov r0, #0x1
	mrs r12, cpsr
	bic r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr

	arm_func_start _frdiv
_frdiv: ; 0x020EB078
	eor r0, r0, r1
	eor r1, r0, r1
	eor r0, r0, r1

	arm_func_start _fdiv
_fdiv: ; 0x020EB084
	stmdb sp!, {lr}
	mov r12, #0xff
	ands r3, r12, r0, lsr #0x17
	cmpne r3, #0xff
	beq _020EB258
	ands r12, r12, r1, lsr #0x17
	cmpne r12, #0xff
	beq _020EB294
	orr r1, r1, #0x800000
	orr r0, r0, #0x800000
	bic r2, r0, #0xff000000
	bic lr, r1, #0xff000000
_020EB0B4:
	cmp r2, lr
	movcc r2, r2, lsl #0x1
	subcc r3, r3, #0x1
	teq r0, r1
	sub r0, pc, #0x94
	ldrb r1, [r0, lr, lsr #0xf]
	rsb lr, lr, #0x0
	mov r0, lr, asr #0x1
	mul r0, r1, r0
	add r0, r0, #0x80000000
	mov r0, r0, lsr #0x6
	mul r0, r1, r0
	mov r0, r0, lsr #0xe
	mul r1, lr, r0
	sub r12, r3, r12
	mov r1, r1, lsr #0xc
	mul r1, r0, r1
	mov r0, r0, lsl #0xe
	add r0, r0, r1, lsr #0xf
	umull r1, r0, r2, r0
	mov r3, r0
	orrmi r0, r0, #0x80000000
	adds r12, r12, #0x7e
	bmi _020EB35C
	cmp r12, #0xfe
	bge _020EB410
	add r0, r0, r12, lsl #0x17
	mov r12, r1, lsr #0x1c
	cmp r12, #0x7
	beq _020EB238
	add r0, r0, r1, lsr #0x1f
	ldmia sp!, {lr}
	bx lr
_020EB138: ; not code
	.byte 0xFF, 0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9
	.byte 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0, 0xF0, 0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA
	.byte 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE2, 0xE1, 0xE0, 0xDF, 0xDF, 0xDE
	.byte 0xDD, 0xDC, 0xDC, 0xDB, 0xDA, 0xD9, 0xD9, 0xD8, 0xD7, 0xD7, 0xD6, 0xD5, 0xD4, 0xD4, 0xD3, 0xD2
	.byte 0xD2, 0xD1, 0xD0, 0xD0, 0xCF, 0xCE, 0xCE, 0xCD, 0xCC, 0xCC, 0xCB, 0xCB, 0xCA, 0xC9, 0xC9, 0xC8
	.byte 0xC8, 0xC7, 0xC6, 0xC6, 0xC5, 0xC5, 0xC4, 0xC3, 0xC3, 0xC2, 0xC2, 0xC1, 0xC0, 0xC0, 0xBF, 0xBF
	.byte 0xBE, 0xBE, 0xBD, 0xBD, 0xBC, 0xBC, 0xBB, 0xBA, 0xBA, 0xB9, 0xB9, 0xB8, 0xB8, 0xB7, 0xB7, 0xB6
	.byte 0xB6, 0xB5, 0xB5, 0xB4, 0xB4, 0xB3, 0xB3, 0xB2, 0xB2, 0xB1, 0xB1, 0xB0, 0xB0, 0xAF, 0xAF, 0xAF
	.byte 0xAE, 0xAE, 0xAD, 0xAD, 0xAC, 0xAC, 0xAB, 0xAB, 0xAA, 0xAA, 0xAA, 0xA9, 0xA9, 0xA8, 0xA8, 0xA7
	.byte 0xA7, 0xA7, 0xA6, 0xA6, 0xA5, 0xA5, 0xA4, 0xA4, 0xA4, 0xA3, 0xA3, 0xA2, 0xA2, 0xA2, 0xA1, 0xA1
	.byte 0xA0, 0xA0, 0xA0, 0x9F, 0x9F, 0x9E, 0x9E, 0x9E, 0x9D, 0x9D, 0x9D, 0x9C, 0x9C, 0x9B, 0x9B, 0x9B
	.byte 0x9A, 0x9A, 0x9A, 0x99, 0x99, 0x99, 0x98, 0x98, 0x98, 0x97, 0x97, 0x96, 0x96, 0x96, 0x95, 0x95
	.byte 0x95, 0x94, 0x94, 0x94, 0x93, 0x93, 0x93, 0x92, 0x92, 0x92, 0x91, 0x91, 0x91, 0x91, 0x90, 0x90
	.byte 0x90, 0x8F, 0x8F, 0x8F, 0x8E, 0x8E, 0x8E, 0x8D, 0x8D, 0x8D, 0x8C, 0x8C, 0x8C, 0x8C, 0x8B, 0x8B
	.byte 0x8B, 0x8A, 0x8A, 0x8A, 0x8A, 0x89, 0x89, 0x89, 0x88, 0x88, 0x88, 0x88, 0x87, 0x87, 0x87, 0x86
	.byte 0x86, 0x86, 0x86, 0x85, 0x85, 0x85, 0x85, 0x84, 0x84, 0x84, 0x83, 0x83, 0x83, 0x83, 0x82, 0x82
	.byte 0x82, 0x82, 0x81, 0x81, 0x81, 0x81, 0x80, 0x80
_020EB238:
	mov r1, r3, lsl #0x1
	add r1, r1, #0x1
	rsb lr, lr, #0x0
	mul r1, lr, r1
	cmp r1, r2, lsl #0x18
	addmi r0, r0, #0x1
	ldmia sp!, {lr}
	bx lr
_020EB258:
	eor lr, r0, r1
	and lr, lr, #0x80000000
	cmp r3, #0x0
	beq _020EB2B0
	movs r0, r0, lsl #0x9
	bne _020EB3F8
	mov r12, r1, lsr #0x17
	mov r1, r1, lsl #0x9
	ands r12, r12, #0xff
	beq _020EB3E8
	cmp r12, #0xff
	blt _020EB3E8
	cmp r1, #0x0
	beq _020EB404
	b _020EB3E0
_020EB294:
	eor lr, r0, r1
	and lr, lr, #0x80000000
	cmp r12, #0x0
	beq _020EB314
_020EB2A4:
	movs r1, r1, lsl #0x9
	bne _020EB3E0
	b _020EB430
_020EB2B0:
	movs r2, r0, lsl #0x9
	beq _020EB2E4
	clz r3, r2
	movs r2, r2, lsl r3
	rsb r3, r3, #0x0
	mov r2, r2, lsr #0x8
	ands r12, r12, r1, lsr #0x17
	beq _020EB33C
	cmp r12, #0xff
	beq _020EB2A4
	orr r1, r1, #0x800000
	bic lr, r1, #0xff000000
	b _020EB0B4
_020EB2E4:
	mov r12, r1, lsr #0x17
	mov r1, r1, lsl #0x9
	ands r12, r12, #0xff
	beq _020EB308
	cmp r12, #0xff
	blt _020EB430
	cmp r1, #0x0
	beq _020EB430
	b _020EB3E0
_020EB308:
	cmp r1, #0x0
	beq _020EB404
	b _020EB430
_020EB314:
	movs r12, r1, lsl #0x9
	beq _020EB3E8
	mov lr, r12
	clz r12, lr
	movs lr, lr, lsl r12
	rsb r12, r12, #0x0
	mov lr, lr, lsr #0x8
	orr r0, r0, #0x800000
	bic r2, r0, #0xff000000
	b _020EB0B4
_020EB33C:
	movs r12, r1, lsl #0x9
	beq _020EB3E8
	mov lr, r12
	clz r12, lr
	movs lr, lr, lsl r12
	rsb r12, r12, #0x0
	mov lr, lr, lsr #0x8
	b _020EB0B4
_020EB35C:
	and r0, r0, #0x80000000
	cmn r12, #0x18
	beq _020EB3D0
	bmi _020EB428
	add r1, r12, #0x17
	mov r2, r2, lsl r1
	rsb r12, r12, #0x0
	mov r3, r3, lsr r12
	orr r0, r0, r3
	rsb lr, lr, #0x0
	mul r1, lr, r3
	cmp r1, r2
	ldmeqia sp!, {lr}
	bxeq lr
	add r1, r1, lr
	cmp r1, r2
	beq _020EB3C4
	addmi r0, r0, #0x1
	subpl r1, r1, lr
	add r1, lr, r1, lsl #0x1
	cmp r1, r2, lsl #0x1
	and r3, r0, #0x1
	addmi r0, r0, #0x1
	addeq r0, r0, r3
	ldmia sp!, {lr}
	bx lr
_020EB3C4:
	add r0, r0, #0x1
	ldmia sp!, {lr}
	bx lr
_020EB3D0:
	cmn r2, lr
	addne r0, r0, #0x1
	ldmia sp!, {lr}
	bx lr
_020EB3E0:
	mov r0, r1
	b _020EB3F8
_020EB3E8:
	mov r0, #0xff000000
	orr r0, lr, r0, lsr #0x1
	ldmia sp!, {lr}
	bx lr
_020EB3F8:
	mvn r0, #0x80000000
	ldmia sp!, {lr}
	bx lr
_020EB404:
	mvn r0, #0x80000000
	ldmia sp!, {lr}
	bx lr
_020EB410:
	tst r0, #0x80000000
	mov r0, #0xff000000
	movne r0, r0, asr #0x1
	moveq r0, r0, lsr #0x1
	ldmia sp!, {lr}
	bx lr
_020EB428:
	ldmia sp!, {lr}
	bx lr
_020EB430:
	mov r0, lr
	ldmia sp!, {lr}
	bx lr

	arm_func_start _f2d
_f2d:
	and r2, r0, #0x80000000
	mov r12, r0, lsr #0x17
	mov r3, r0, lsl #0x9
	ands r12, r12, #0xff
	beq _020EB46C
	cmp r12, #0xff
	beq _020EB498
_020EB458:
	add r12, r12, #0x380
	mov r0, r3, lsl #0x14
	orr r1, r2, r3, lsr #0xc
	orr r1, r1, r12, lsl #0x14
	bx lr
_020EB46C:
	cmp r3, #0x0
	bne _020EB480
	mov r1, r2
	mov r0, #0x0
	bx lr
_020EB480:
	mov r3, r3, lsr #0x1
	clz r12, r3
	movs r3, r3, lsl r12
	rsb r12, r12, #0x1
	add r3, r3, r3
	b _020EB458
_020EB498:
	cmp r3, #0x0
	bhi _020EB4B0
	ldr r1, _020EB4BC ; =0x7FF00000
	orr r1, r1, r2
	mov r0, #0x0
	bx lr
_020EB4B0:
	mvn r0, #0x0
	bic r1, r0, #0x80000000
	bx lr
	.balign 4
_020EB4BC: .word 0x7FF00000

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

	arm_func_start _fflt
_fflt: ; 0x020EB534
	ands r2, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r0, #0x0
	bxeq lr
	clz r3, r0
	movs r0, r0, lsl r3
	rsb r3, r3, #0x9e
	ands r1, r0, #0xff
	add r0, r0, r0
	orr r0, r2, r0, lsr #0x9
	orr r0, r0, r3, lsl #0x17
	bxeq lr
	tst r1, #0x80
	bxeq lr
	ands r3, r1, #0x7f
	andeqs r3, r0, #0x1
	addne r0, r0, #0x1
	bx lr

	arm_func_start _ffltu
_ffltu: ; 0x020EB57C
	cmp r0, #0x0
	bxeq lr
	mov r3, #0x9e
	bmi _020EB598
	clz r12, r0
	movs r0, r0, lsl r12
	sub r3, r3, r12
_020EB598:
	ands r2, r0, #0xff
	add r0, r0, r0
	mov r0, r0, lsr #0x9
	orr r0, r0, r3, lsl #0x17
	bxeq lr
	tst r2, #0x80
	bxeq lr
	ands r1, r2, #0x7f
	andeqs r1, r0, #0x1
	addne r0, r0, #0x1
	bx lr

	arm_func_start _fmul
_fmul: ; 0x020EB5C4
	eor r2, r0, r1
	and r2, r2, #0x80000000
	mov r12, #0xff
	ands r3, r12, r0, lsr #0x17
	mov r0, r0, lsl #0x8
	cmpne r3, #0xff
	beq _020EB640
	orr r0, r0, #0x80000000
	ands r12, r12, r1, lsr #0x17
	mov r1, r1, lsl #0x8
	cmpne r12, #0xff
	beq _020EB680
	orr r1, r1, #0x80000000
_020EB5F8:
	add r12, r3, r12
	umull r1, r3, r0, r1
	movs r0, r3
	addpl r0, r0, r0
	subpl r12, r12, #0x1
	subs r12, r12, #0x7f
	bmi _020EB70C
	cmp r12, #0xfe
	bge _020EB778
	ands r3, r0, #0xff
	orr r0, r2, r0, lsr #0x8
	add r0, r0, r12, lsl #0x17
	tst r3, #0x80
	bxeq lr
	orrs r1, r1, r3, lsl #0x19
	andeqs r3, r0, #0x1
	addne r0, r0, #0x1
	bx lr
_020EB640:
	cmp r3, #0x0
	beq _020EB694
	movs r0, r0, lsl #0x1
	bne _020EB768
	mov r12, r1, lsr #0x17
	mov r1, r1, lsl #0x9
	ands r12, r12, #0xff
	beq _020EB674
	cmp r12, #0xff
	blt _020EB75C
	cmp r1, #0x0
	beq _020EB75C
	b _020EB768
_020EB674:
	cmp r1, #0x0
	beq _020EB770
	b _020EB75C
_020EB680:
	cmp r12, #0x0
	beq _020EB6F0
_020EB688:
	movs r1, r1, lsl #0x1
	bne _020EB768
	b _020EB75C
_020EB694:
	movs r0, r0, lsl #0x1
	beq _020EB6CC
	mov r0, r0, lsr #0x1
	clz r3, r0
	movs r0, r0, lsl r3
	rsb r3, r3, #0x1
	mov r12, r1, lsr #0x17
	mov r1, r1, lsl #0x8
	ands r12, r12, #0xff
	beq _020EB6F0
	cmp r12, #0xff
	beq _020EB688
	orr r1, r1, #0x80000000
	b _020EB5F8
_020EB6CC:
	mov r12, r1, lsr #0x17
	mov r1, r1, lsl #0x9
	ands r12, r12, #0xff
	beq _020EB79C
	cmp r12, #0xff
	blt _020EB79C
	cmp r1, #0x0
	beq _020EB770
	b _020EB768
_020EB6F0:
	movs r1, r1, lsl #0x1
	beq _020EB79C
	mov r1, r1, lsr #0x1
	clz r12, r1
	movs r1, r1, lsl r12
	rsb r12, r12, #0x1
	b _020EB5F8
_020EB70C:
	cmn r12, #0x18
	beq _020EB754
	bmi _020EB794
	cmp r1, #0x0
	orrne r0, r0, #0x1
	mov r3, r0
	mov r0, r0, lsr #0x8
	rsb r12, r12, #0x0
	orr r0, r2, r0, lsr r12
	rsb r12, r12, #0x18
	movs r1, r3, lsl r12
	bxeq lr
	tst r1, #0x80000000
	bxeq lr
	movs r1, r1, lsl #0x1
	andeqs r1, r0, #0x1
	addne r0, r0, #0x1
	bx lr
_020EB754:
	mov r0, r0, lsl #0x1
	b _020EB784
_020EB75C:
	mov r0, #0xff000000
	orr r0, r2, r0, lsr #0x1
	bx lr
_020EB768:
	mvn r0, #0x80000000
	bx lr
_020EB770:
	mvn r0, #0x80000000
	bx lr
_020EB778:
	mov r0, #0xff000000
	orr r0, r2, r0, lsr #0x1
	bx lr
_020EB784:
	movs r1, r0
	mov r0, r2
	addne r0, r0, #0x1
	bx lr
_020EB794:
	mov r0, r2
	bx lr
_020EB79C:
	mov r0, r2
	bx lr

	arm_func_start _frsb
_frsb: ; 0x020EB7A4
	eor r0, r0, r1
	eor r1, r0, r1
	eor r0, r0, r1

	arm_func_start _fsub
_fsub: ; 0x020EB7B0
	eors r2, r0, r1
	eormi r1, r1, #0x80000000
	bmi _020EA98C
_020EB7BC:
	subs r12, r0, r1
	eorcc r12, r12, #0x80000000
	subcc r0, r0, r12
	addcc r1, r1, r12
	mov r2, #0x80000000
	mov r3, r0, lsr #0x17
	orr r0, r2, r0, lsl #0x8
	ands r12, r3, #0xff
	cmpne r12, #0xff
	beq _020EB8D8
	mov r12, r1, lsr #0x17
	orr r1, r2, r1, lsl #0x8
	ands r2, r12, #0xff
	beq _020EB918
_020EB7F4:
	subs r12, r3, r12
	beq _020EB83C
	rsb r2, r12, #0x20
	movs r2, r1, lsl r2
	mov r1, r1, lsr r12
	orrne r1, r1, #0x1
	subs r0, r0, r1
	bpl _020EB880
	ands r1, r0, #0xff
	add r0, r0, r0
	mov r0, r0, lsr #0x9
	orr r0, r0, r3, lsl #0x17
	tst r1, #0x80
	bxeq lr
	ands r1, r1, #0x7f
	andeqs r1, r0, #0x1
	addne r0, r0, #0x1
	bx lr
_020EB83C:
	subs r0, r0, r1
	beq _020EB9E4
	mov r2, r3, lsl #0x17
	and r2, r2, #0x80000000
	bic r3, r3, #0x100
	clz r12, r0
	movs r0, r0, lsl r12
	sub r3, r3, r12
	cmp r3, #0x0
	bgt _020EB870
	rsb r3, r3, #0x9
	orr r0, r2, r0, lsr r3
	bx lr
_020EB870:
	add r0, r0, r0
	orr r0, r2, r0, lsr #0x9
	orr r0, r0, r3, lsl #0x17
	bx lr
_020EB880:
	mov r2, r3, lsl #0x17
	and r2, r2, #0x80000000
	bic r3, r3, #0x100
	clz r12, r0
	movs r0, r0, lsl r12
	sub r3, r3, r12
	cmp r3, #0x0
	bgt _020EB8AC
	rsb r3, r3, #0x9
	orr r0, r2, r0, lsr r3
	bx lr
_020EB8AC:
	ands r1, r0, #0xff
	add r0, r0, r0
	orr r0, r2, r0, lsr #0x9
	orr r0, r0, r3, lsl #0x17
	bxeq lr
	tst r1, #0x80
	bxeq lr
	ands r1, r1, #0x7f
	andeqs r1, r0, #0x1
	addne r0, r0, #0x1
	bx lr
_020EB8D8:
	cmp r3, #0x100
	movge r2, #0x80000000
	movlt r2, #0x0
	ands r3, r3, #0xff
	beq _020EB940
	movs r0, r0, lsl #0x1
	bne _020EBA18
	mov r12, r1, lsr #0x17
	mov r1, r1, lsl #0x9
	ands r12, r12, #0xff
	beq _020EBA0C
	cmp r12, #0xff
	blt _020EBA0C
	cmp r1, #0x0
	beq _020EBA20
	b _020EBA18
_020EB918:
	cmp r12, #0x100
	movge r2, #0x80000000
	movlt r2, #0x0
	and r3, r3, #0xff
	ands r12, r12, #0xff
	beq _020EB9A8
_020EB930:
	eor r2, r2, #0x80000000
	movs r1, r1, lsl #0x1
	bne _020EBA18
	b _020EBA0C
_020EB940:
	movs r0, r0, lsl #0x1
	beq _020EB978
	mov r0, r0, lsr #0x1
	mov r3, #0x1
	mov r12, r1, lsr #0x17
	mov r1, r1, lsl #0x8
	ands r12, r12, #0xff
	beq _020EB9A8
	cmp r12, #0xff
	beq _020EB930
	orr r1, r1, #0x80000000
	orr r3, r3, r2, lsr #0x17
	orr r12, r12, r2, lsr #0x17
	b _020EB7F4
_020EB978:
	mov r3, r1, lsr #0x17
	mov r0, r1, lsl #0x9
	ands r2, r3, #0xff
	beq _020EB99C
	cmp r2, #0xff
	blt _020EB9C4
	cmp r0, #0x0
	bne _020EBA04
	b _020EBA0C
_020EB99C:
	cmp r0, #0x0
	beq _020EB9E4
	b _020EB9C4
_020EB9A8:
	movs r1, r1, lsl #0x1
	beq _020EB9CC
	mov r1, r1, lsr #0x1
	mov r12, #0x1
	orr r12, r12, r2, lsr #0x17
	orr r3, r3, r2, lsr #0x17
	b _020EB7F4
_020EB9C4:
	mov r0, r1
	bx lr
_020EB9CC:
	cmp r0, #0x0
	subges r3, r3, #0x1
	add r0, r0, r0
	orr r0, r2, r0, lsr #0x9
	orr r0, r0, r3, lsl #0x17
	bx lr
_020EB9E4:
	mov r0, #0x0
	bx lr
_020EB9EC: ; 0x020EB9EC
	cmp r0, #0x0
	subges r3, r3, #0x1
	add r0, r0, r0
	mov r0, r0, lsr #0x9
	orr r0, r0, r3, lsl #0x17
	bx lr
_020EBA04:
	mvn r0, #0x80000000
	bx lr
_020EBA0C:
	mov r0, #0xff000000
	orr r0, r2, r0, lsr #0x1
	bx lr
_020EBA18:
	mvn r0, #0x80000000
	bx lr
_020EBA20:
	mvn r0, #0x80000000
	bx lr

	arm_func_start _ll_mod
_ll_mod: ; 0x020EBA28
	stmdb sp!, {r4-r7,r11-r12,lr}
	mov r4, r1
	orr r4, r4, #0x1
	b _020EBA48

	arm_func_start _ll_sdiv
_ll_sdiv: ; 0x020EBA38
	stmdb sp!, {r4-r7,r11-r12,lr}
	eor r4, r1, r3
	mov r4, r4, asr #0x1
	mov r4, r4, lsl #0x1
_020EBA48:
	orrs r5, r3, r2
	bne _020EBA58
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr
_020EBA58:
	mov r5, r0, lsr #0x1f
	add r5, r5, r1
	mov r6, r2, lsr #0x1f
	add r6, r6, r3
	orrs r6, r5, r6
	bne _020EBA8C
	mov r1, r2
	bl _s32_div_f
	ands r4, r4, #0x1
	movne r0, r1
	mov r1, r0, asr #0x1f
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr
_020EBA8C:
	cmp r1, #0x0
	bge _020EBA9C
	rsbs r0, r0, #0x0
	rsc r1, r1, #0x0
_020EBA9C:
	cmp r3, #0x0
	bge _020EBAAC
	rsbs r2, r2, #0x0
	rsc r3, r3, #0x0
_020EBAAC:
	orrs r5, r1, r0
	beq _020EBBD0
	mov r5, #0x0
	mov r6, #0x1
	cmp r3, #0x0
	bmi _020EBAD8
_020EBAC4:
	add r5, r5, #0x1
	adds r2, r2, r2
	adcs r3, r3, r3
	bpl _020EBAC4
	add r6, r6, r5
_020EBAD8:
	cmp r1, #0x0
	blt _020EBAF8
_020EBAE0:
	cmp r6, #0x1
	beq _020EBAF8
	sub r6, r6, #0x1
	adds r0, r0, r0
	adcs r1, r1, r1
	bpl _020EBAE0
_020EBAF8:
	mov r7, #0x0
	mov r12, #0x0
	mov r11, #0x0
	b _020EBB20
_020EBB08:
	orr r12, r12, #0x1
	subs r6, r6, #0x1
	beq _020EBB78
	adds r0, r0, r0
	adcs r1, r1, r1
	adcs r7, r7, r7
_020EBB20:
	subs r0, r0, r2
	sbcs r1, r1, r3
	sbcs r7, r7, #0x0
	adds r12, r12, r12
	adc r11, r11, r11
	cmp r7, #0x0
	bge _020EBB08
_020EBB3C:
	subs r6, r6, #0x1
	beq _020EBB70
	adds r0, r0, r0
	adcs r1, r1, r1
	adc r7, r7, r7
	adds r0, r0, r2
	adcs r1, r1, r3
	adc r7, r7, #0x0
	adds r12, r12, r12
	adc r11, r11, r11
	cmp r7, #0x0
	bge _020EBB08
	b _020EBB3C
_020EBB70:
	adds r0, r0, r2
	adc r1, r1, r3
_020EBB78:
	ands r7, r4, #0x1
	moveq r0, r12
	moveq r1, r11
	beq _020EBBB0
	subs r7, r5, #0x20
	movge r0, r1, lsr r7
	bge _020EBBD4
	rsb r7, r5, #0x20
	mov r0, r0, lsr r5
	orr r0, r0, r1, lsl r7
	mov r1, r1, lsr r5
	b _020EBBB0
_020EBBA8: ; 0x020EBBA8
	mov r0, r1, lsr r7
	mov r1, #0x0
_020EBBB0:
	cmp r4, #0x0
	blt _020EBBC0
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr
_020EBBC0:
	rsbs r0, r0, #0x0
	rsc r1, r1, #0x0
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr
_020EBBD0:
	mov r0, #0x0
_020EBBD4:
	mov r1, #0x0
	cmp r4, #0x0
	blt _020EBBC0
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr

	arm_func_start _ll_udiv
_ll_udiv: ; 0x020EBBE8
	stmdb sp!, {r4-r7,r11-r12,lr}
	mov r4, #0x0
	b _020EBBFC

	arm_func_start _ull_mod
_ull_mod: ; 0x020EBBF4
	stmdb sp!, {r4-r7,r11-r12,lr}
	mov r4, #0x1
_020EBBFC:
	orrs r5, r3, r2
	bne _020EBC0C
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr
_020EBC0C:
	orrs r5, r1, r3
	bne _020EBAAC
	mov r1, r2
	bl _u32_div_not_0_f
	cmp r4, #0x0
	movne r0, r1
	mov r1, #0x0
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr

	arm_func_start _ll_mul
_ll_mul: ; 0x020EBC30
	stmdb sp!, {r4-r5,lr}
	umull r5, r4, r0, r2
	mla r4, r0, r3, r4
	mla r4, r2, r1, r4
	mov r1, r4
	mov r0, r5
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start _ll_shl
_ll_shl: ; 0x020EBC50
	ands r2, r2, #0x3f
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
_s32_div_f: ; 0x020EBC80
	eor r12, r0, r1
	and r12, r12, #0x80000000
	cmp r0, #0x0
	rsblt r0, r0, #0x0
	addlt r12, r12, #0x1
	cmp r1, #0x0
	rsblt r1, r1, #0x0
	beq _020EBE78
	cmp r0, r1
	movcc r1, r0
	movcc r0, #0x0
	blo _020EBE78
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
	mov r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	mov r1, r3
_020EBE78:
	ands r3, r12, #0x80000000
	rsbne r0, r0, #0x0
	ands r3, r12, #0x1
	rsbne r1, r1, #0x0
	bx lr

	arm_func_start _u32_div_f
_u32_div_f: ; 0x020EBE8C
	cmp r1, #0x0
	bxeq lr

	arm_func_start _u32_div_not_0_f
_u32_div_not_0_f:
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
	mov r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	mov r1, r3
	bx lr

	arm_func_start _drdiv
_drdiv: ; 0x020EC070
	eor r1, r1, r3
	eor r3, r1, r3
	eor r1, r1, r3
	eor r0, r0, r2
	eor r2, r0, r2
	eor r0, r0, r2

	arm_func_start _ddiv
_ddiv: ; 0x020EC088
	stmdb sp!, {r4-r6,lr}
	ldr lr, _020EC5C8 ; =0x00000FFE
	eor r4, r1, r3
	ands r12, lr, r1, lsr #0x13
	cmpne r12, lr
	beq _020EC434
	bic r1, r1, lr, lsl #0x14
	orr r1, r1, #0x100000
	add r12, r12, r4, lsr #0x1f
_020EC0AC:
	ands r4, lr, r3, lsr #0x13
	cmpne r4, lr
	beq _020EC4CC
	bic r3, r3, lr, lsl #0x14
	orr r3, r3, #0x100000
_020EC0C0:
	sub r12, r12, r4
	cmp r1, r3
	cmpeq r0, r2
	bhs _020EC0DC
	adds r0, r0, r0
	adc r1, r1, r1
	sub r12, r12, #0x2
_020EC0DC:
	sub r4, pc, #0x24
	ldrb lr, [r4, r3, lsr #0xc]
	rsbs r2, r2, #0x0
	rsc r3, r3, #0x0
	mov r4, #0x20000000
	mla r5, lr, r3, r4
	mov r6, r3, lsl #0xa
	mov r5, r5, lsr #0x7
	mul lr, r5, lr
	orr r6, r6, r2, lsr #0x16
	mov lr, lr, lsr #0xd
	mul r5, lr, r6
	mov r6, r1, lsl #0xa
	orr r6, r6, r0, lsr #0x16
	mov r5, r5, lsr #0x10
	mul r5, lr, r5
	mov lr, lr, lsl #0xe
	add lr, lr, r5, lsr #0x10
	umull r5, r6, lr, r6
	umull r4, r5, r6, r2
	mla r5, r3, r6, r5
	mov r4, r4, lsr #0x1a
	orr r4, r4, r5, lsl #0x6
	add r4, r4, r0, lsl #0x2
	umull lr, r5, r4, lr
	mov r4, #0x0
	adds r5, r5, r6, lsl #0x18
	adc r4, r4, r6, lsr #0x8
	cmp r12, #0x800
	bge _020EC2C0
	add r12, r12, #0x7f0
	adds r12, r12, #0xc
	bmi _020EC2D8
	orr r1, r4, r12, lsl #0x1f
	bic r12, r12, #0x1
	add r1, r1, r12, lsl #0x13
	tst lr, #0x80000000
	bne _020EC1B0
	rsbs r2, r2, #0x0
	mov r4, r4, lsl #0x1
	add r4, r4, r5, lsr #0x1f
	mul lr, r2, r4
	mov r6, #0x0
	mov r4, r5, lsl #0x1
	orr r4, r4, #0x1
	umlal r6, lr, r4, r2
	rsc r3, r3, #0x0
	mla lr, r4, r3, lr
	cmp lr, r0, lsl #0x15
	bmi _020EC1B0
	mov r0, r5
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC1B0:
	adds r0, r5, #0x1
	adc r1, r1, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC1C0: ; not code
	.byte 0xFF, 0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1
	.byte 0xF0, 0xF0, 0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE6, 0xE5, 0xE4
	.byte 0xE3, 0xE2, 0xE2, 0xE1, 0xE0, 0xDF, 0xDF, 0xDE, 0xDD, 0xDC, 0xDC, 0xDB, 0xDA, 0xD9, 0xD9, 0xD8
	.byte 0xD7, 0xD7, 0xD6, 0xD5, 0xD4, 0xD4, 0xD3, 0xD2, 0xD2, 0xD1, 0xD0, 0xD0, 0xCF, 0xCE, 0xCE, 0xCD
	.byte 0xCC, 0xCC, 0xCB, 0xCB, 0xCA, 0xC9, 0xC9, 0xC8, 0xC8, 0xC7, 0xC6, 0xC6, 0xC5, 0xC5, 0xC4, 0xC3
	.byte 0xC3, 0xC2, 0xC2, 0xC1, 0xC0, 0xC0, 0xBF, 0xBF, 0xBE, 0xBE, 0xBD, 0xBD, 0xBC, 0xBC, 0xBB, 0xBA
	.byte 0xBA, 0xB9, 0xB9, 0xB8, 0xB8, 0xB7, 0xB7, 0xB6, 0xB6, 0xB5, 0xB5, 0xB4, 0xB4, 0xB3, 0xB3, 0xB2
	.byte 0xB2, 0xB1, 0xB1, 0xB0, 0xB0, 0xAF, 0xAF, 0xAF, 0xAE, 0xAE, 0xAD, 0xAD, 0xAC, 0xAC, 0xAB, 0xAB
	.byte 0xAA, 0xAA, 0xAA, 0xA9, 0xA9, 0xA8, 0xA8, 0xA7, 0xA7, 0xA7, 0xA6, 0xA6, 0xA5, 0xA5, 0xA4, 0xA4
	.byte 0xA4, 0xA3, 0xA3, 0xA2, 0xA2, 0xA2, 0xA1, 0xA1, 0xA0, 0xA0, 0xA0, 0x9F, 0x9F, 0x9E, 0x9E, 0x9E
	.byte 0x9D, 0x9D, 0x9D, 0x9C, 0x9C, 0x9B, 0x9B, 0x9B, 0x9A, 0x9A, 0x9A, 0x99, 0x99, 0x99, 0x98, 0x98
	.byte 0x98, 0x97, 0x97, 0x96, 0x96, 0x96, 0x95, 0x95, 0x95, 0x94, 0x94, 0x94, 0x93, 0x93, 0x93, 0x92
	.byte 0x92, 0x92, 0x91, 0x91, 0x91, 0x91, 0x90, 0x90, 0x90, 0x8F, 0x8F, 0x8F, 0x8E, 0x8E, 0x8E, 0x8D
	.byte 0x8D, 0x8D, 0x8C, 0x8C, 0x8C, 0x8C, 0x8B, 0x8B, 0x8B, 0x8A, 0x8A, 0x8A, 0x8A, 0x89, 0x89, 0x89
	.byte 0x88, 0x88, 0x88, 0x88, 0x87, 0x87, 0x87, 0x86, 0x86, 0x86, 0x86, 0x85, 0x85, 0x85, 0x85, 0x84
	.byte 0x84, 0x84, 0x83, 0x83, 0x83, 0x83, 0x82, 0x82, 0x82, 0x82, 0x81, 0x81, 0x81, 0x81, 0x80, 0x80
_020EC2C0:
	movs r1, r12, lsl #0x1f
	orr r1, r1, #0x7f000000
	orr r1, r1, #0xf00000
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC2D8:
	mvn r6, r12, asr #0x1
	cmp r6, #0x34
	bgt _020EC424
	beq _020EC400
	cmp r6, #0x14
	bge _020EC320
	rsb r6, r6, #0x13
	mov lr, r0, lsl r6
	rsb r6, r6, #0x14
	mov r0, r5, lsr r6
	rsb r6, r6, #0x20
	orr r0, r0, r4, lsl r6
	rsb r6, r6, #0x20
	mov r4, r4, lsr r6
	orr r1, r4, r12, lsl #0x1f
	mov r12, lr
	mov lr, #0x0
	b _020EC350
_020EC320:
	rsb r6, r6, #0x33
	mov lr, r1, lsl r6
	mov r1, r12, lsl #0x1f
	rsb r6, r6, #0x20
	orr r12, lr, r0, lsr r6
	rsb r6, r6, #0x20
	mov lr, r0, lsl r6
	mov r5, r5, lsr #0x15
	orr r5, r5, r4, lsl #0xb
	rsb r6, r6, #0x1f
	mov r0, r5, lsr r6
	mov r4, #0x0
_020EC350:
	rsbs r2, r2, #0x0
	mul r4, r2, r4
	mov r5, #0x0
	umlal r5, r4, r2, r0
	rsc r3, r3, #0x0
	mla r4, r0, r3, r4
	cmp r4, r12
	cmpeq r5, lr
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	adds r5, r5, r2
	adc r4, r4, r3
	cmp r4, r12
	bmi _020EC3F4
	bne _020EC398
	cmp r5, lr
	beq _020EC3E4
	blo _020EC3F4
_020EC398:
	subs r5, r5, r2
	sbc r4, r4, r3
_020EC3A0:
	adds r5, r5, r5
	adc r4, r4, r4
	adds r5, r5, r2
	adc r4, r4, r3
	adds lr, lr, lr
	adc r12, r12, r12
	cmp r4, r12
	bmi _020EC3E4
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	cmp r5, lr
	blo _020EC3E4
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	tst r0, #0x1
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
_020EC3E4:
	adds r0, r0, #0x1
	adc r1, r1, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC3F4:
	adds r0, r0, #0x1
	adc r1, r1, #0x0
	b _020EC3A0
_020EC400:
	rsbs r2, r2, #0x0
	rsc r3, r3, #0x0
	cmp r1, r3
	cmpeq r0, r2
	mov r1, r12, lsl #0x1f
	mov r0, #0x0
	movne r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC424:
	mov r1, r12, lsl #0x1f
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC434:
	orrs r5, r0, r1, lsl #0x1
	beq _020EC558
	cmp r12, lr
	beq _020EC49C
	movs r1, r1, lsl #0xc
	beq _020EC478
	clz r5, r1
	movs r1, r1, lsl r5
	sub r12, r12, r5
	add r5, r12, #0x1f
	mov r1, r1, lsr #0xb
	orr r1, r1, r0, lsr r5
	rsb r5, r5, #0x20
	mov r0, r0, lsl r5
	mov r12, r12, lsl #0x1
	orr r12, r12, r4, lsr #0x1f
	b _020EC0AC
_020EC478:
	mvn r12, #0x13
	clz r5, r0
	movs r0, r0, lsl r5
	sub r12, r12, r5
	mov r1, r0, lsr #0xb
	mov r0, r0, lsl #0x15
	mov r12, r12, lsl #0x1
	orr r12, r12, r4, lsr #0x1f
	b _020EC0AC
_020EC49C:
	orrs r5, r0, r1, lsl #0xc
	bne _020EC580
	bic r5, r3, #0x80000000
	cmp r5, lr, lsl #0x13
	bhs _020EC4C0
	and r5, r3, #0x80000000
	eor r1, r5, r1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC4C0:
	orrs r5, r2, r3, lsl #0xc
	bne _020EC5A0
	b _020EC5B8
_020EC4CC:
	orrs r5, r2, r3, lsl #0x1
	beq _020EC544
	cmp r4, lr
	beq _020EC52C
	movs r3, r3, lsl #0xc
	beq _020EC50C
	clz r5, r3
	movs r3, r3, lsl r5
	sub r4, r4, r5
	add r5, r4, #0x1f
	mov r3, r3, lsr #0xb
	orr r3, r3, r2, lsr r5
	rsb r5, r5, #0x20
	mov r2, r2, lsl r5
	mov r4, r4, lsl #0x1
	b _020EC0C0
_020EC50C:
	mvn r4, #0x13
	clz r5, r2
	movs r2, r2, lsl r5
	sub r4, r4, r5
	mov r3, r2, lsr #0xb
	mov r2, r2, lsl #0x15
	mov r4, r4, lsl #0x1
	b _020EC0C0
_020EC52C:
	orrs r5, r2, r3, lsl #0xc
	bne _020EC5A0
	mov r1, r12, lsl #0x1f
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC544:
	mov r1, r12, lsl #0x1f
	orr r1, r1, lr, lsl #0x13
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC558:
	orrs r5, r2, r3, lsl #0x1
	beq _020EC5B8
	bic r5, r3, #0x80000000
	cmp r5, lr, lsl #0x13
	cmpeq r2, #0x0
	bhi _020EC5A0
	eor r1, r1, r3
	and r1, r1, #0x80000000
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC580:
	tst r1, #0x80000
	beq _020EC5B8
	bic r5, r3, #0x80000000
	cmp r5, lr, lsl #0x13
	cmpeq r2, #0x0
	bhi _020EC5A0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC5A0:
	tst r3, #0x80000
	beq _020EC5B8
	mov r1, r3
	mov r0, r2
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EC5B8:
	orr r1, r1, #0x7f000000
	orr r1, r1, #0xf80000
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020EC5C8: .word 0x00000FFE

	arm_func_start _fp_init
_fp_init: ; 0x020EC5CC
	bx lr

	arm_func_start sys_writec
sys_writec: ; 0x020EC5D0
	str lr, [sp, #-0x4]!
	mov r1, r0
	mov r0, #0x3
	swi 0x123456
	ldr pc, [sp], #0x4

	arm_func_start sys_readc
sys_readc: ; 0x020EC5E4
	str lr, [sp, #-0x4]!
	mov r1, #0x0
	mov r0, #0x7
	swi 0x123456
	ldr pc, [sp], #0x4

	arm_func_start sys_exit
sys_exit: ; 0x020EC5F8
	mov r1, #0x0
	mov r0, #0x18
	swi 0x123456
	mov pc, lr

	arm_func_start __read_console
__read_console: ; 0x020EC608
	stmdb sp!, {r3-r7,lr}
	mov r6, r2
	ldr r5, [r6, #0x0]
	mov r7, r1
	cmp r5, #0x0
	mov r4, #0x0
	bls _020EC650
_020EC624:
	bl sys_readc
	and r1, r0, #0xff
	cmp r1, #0xd
	strb r0, [r7, r4]
	cmpne r1, #0xa
	addeq r0, r4, #0x1
	streq r0, [r6, #0x0]
	beq _020EC650
	add r4, r4, #0x1
	cmp r4, r5
	blo _020EC624
_020EC650:
	mov r0, #0x0
	ldmia sp!, {r3-r7,pc}

	arm_func_start __write_console
__write_console: ; 0x020EC658
	stmdb sp!, {r4-r6,lr}
	ldr r5, [r2, #0x0]
	mov r6, r1
	cmp r5, #0x0
	mov r4, #0x0
	bls _020EC684
_020EC670:
	add r0, r6, r4
	bl sys_writec
	add r4, r4, #0x1
	cmp r4, r5
	blo _020EC670
_020EC684:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start __close_console
__close_console: ; 0x020EC68C
	mov r0, #0x0
	bx lr

	.section .rodata
__static_initializers:
	.word 0

	.section .text
	arm_func_start __call_static_initializers
__call_static_initializers: ; 0x020EC694
	stmdb sp!, {r4,lr}
	ldr r4, _020EC6BC ; =__static_initializers
	b _020EC6A8
_020EC6A0:
	blx r0
	add r4, r4, #0x4
_020EC6A8:
	cmp r4, #0x0
	ldrne r0, [r4, #0x0]
	cmpne r0, #0x0
	bne _020EC6A0
	ldmia sp!, {r4,pc}
	.balign 4
_020EC6BC: .word __static_initializers

	arm_func_start __destroy_global_chain
__destroy_global_chain: ; 0x020EC6C0
	stmdb sp!, {r3-r5,lr}
	ldr r4, _020EC700 ; =0x021D74C8
	ldr r2, [r4, #0x0]
	cmp r2, #0x0
	ldmeqia sp!, {r3-r5,pc}
_020EC6D4: ; 0x020EC6D4
	mvn r5, #0x0
_020EC6D8:
	ldr r0, [r2, #0x0]
	mov r1, r5
	str r0, [r4, #0x0]
	ldr r0, [r2, #0x8]
	ldr r2, [r2, #0x4]
	blx r2
	ldr r2, [r4, #0x0]
	cmp r2, #0x0
	bne _020EC6D8
	ldmia sp!, {r3-r5,pc}
	.balign 4
_020EC700: .word 0x021D74C8

	arm_func_start _ExitProcess
_ExitProcess: ; 0x020EC704
	ldr ip, _020EC70C ; =sys_exit
	bx r12
	.balign 4
_020EC70C: .word sys_exit
