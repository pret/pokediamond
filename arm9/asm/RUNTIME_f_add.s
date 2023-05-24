	.include "asm/macros.inc"
	.include "global.inc"

	.extern __fsub_start

	.text

	arm_func_start _fadd
_fadd: ; 0x020EA980
	eors r2, r0, r1
	eormi r1, r1, #0x80000000
	bmi __fsub_start
	.global __fadd_start
__fadd_start:
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
