	.include "asm/macros.inc"
	.include "global.inc"

    .extern __fadd_start

    .text

	arm_func_start _frsb
_frsb: ; 0x020EB7A4
	eor r0, r0, r1
	eor r1, r0, r1
	eor r0, r0, r1

	arm_func_start _fsub
_fsub: ; 0x020EB7B0
	eors r2, r0, r1
	eormi r1, r1, #0x80000000
	bmi __fadd_start
	.global __fsub_start
__fsub_start:
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
