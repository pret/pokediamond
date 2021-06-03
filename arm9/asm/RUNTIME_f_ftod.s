	.include "asm/macros.inc"
	.include "global.inc"

    .text

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
