	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start frexp
frexp: ; 0x020E825C
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4,lr}
	ldr r1, [sp, #0xc]
	ldr r0, _020E8308 ; =0x7FF00000
	mov r4, r2
	bic r3, r1, #0x80000000
	mov r2, #0x0
	str r2, [r4, #0x0]
	cmp r3, r0
	ldr r0, [sp, #0x8]
	bge _020E8290
	orrs r0, r3, r0
	bne _020E82A4
_020E8290:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E82A4:
	cmp r3, #0x100000
	bge _020E82D0
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	ldr r3, _020E830C ; =0x43500000
	bl _dmul
	mvn r2, #0x35
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	str r2, [r4, #0x0]
	bic r3, r1, #0x80000000
_020E82D0:
	ldr r2, _020E8310 ; =0x800FFFFF
	ldr r0, _020E8314 ; =0xFFFFFC02
	and r1, r1, r2
	orr r1, r1, #0xfe00000
	orr r1, r1, #0x30000000
	ldr r2, [r4, #0x0]
	add r0, r0, r3, asr #0x14
	add r2, r2, r0
	ldr r0, [sp, #0x8]
	str r2, [r4, #0x0]
	str r1, [sp, #0xc]
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E8308: .word 0x7FF00000
_020E830C: .word 0x43500000
_020E8310: .word 0x800FFFFF
_020E8314: .word 0xFFFFFC02
	arm_func_end frexp

	exception frexp, 189, 0x00300120
