	.include "asm/macros.inc"
	.include "global.inc"

    .text

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
	bne __f_result_x_NaN
	mov r12, r1, lsr #0x17
	mov r1, r1, lsl #0x9
	ands r12, r12, #0xff
	beq _020EB674
	cmp r12, #0xff
	blt __f_result_INF
	cmp r1, #0x0
	beq __f_result_INF
	b __f_result_x_NaN
_020EB674:
	cmp r1, #0x0
	beq __f_result_invalid
	b __f_result_INF
_020EB680:
	cmp r12, #0x0
	beq _020EB6F0
_020EB688:
	movs r1, r1, lsl #0x1
	bne __f_result_x_NaN
	b __f_result_INF
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
	beq __f_result_invalid
	b __f_result_x_NaN
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
    .global __f_result_INF
__f_result_INF:
	mov r0, #0xff000000
	orr r0, r2, r0, lsr #0x1
	bx lr
    .global __f_result_x_NaN
__f_result_x_NaN:
	mvn r0, #0x80000000
	bx lr
    .global __f_result_invalid
__f_result_invalid:
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
