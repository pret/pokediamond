	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start __fill_mem
__fill_mem: ; 0x020DF550
	cmp r2, #0x20
	and r3, r1, #0xff
	blo _020DF5E4
	rsb r1, r0, #0x0
	ands r12, r1, #0x3
	beq _020DF57C
	sub r2, r2, r12
	and r1, r3, #0xff
_020DF570:
	strb r1, [r0], #0x1
	subs r12, r12, #0x1
	bne _020DF570
_020DF57C:
	cmp r3, #0x0
	beq _020DF594
	mov r1, r3, lsl #0x10
	orr r1, r1, r3, lsl #0x18
	orr r1, r1, r3, lsl #0x8
	orr r3, r3, r1
_020DF594:
	movs r1, r2, lsr #0x5
	beq _020DF5C8
_020DF59C:
	str r3, [r0, #0x0]
	str r3, [r0, #0x4]
	str r3, [r0, #0x8]
	str r3, [r0, #0xc]
	str r3, [r0, #0x10]
	str r3, [r0, #0x14]
	str r3, [r0, #0x18]
	str r3, [r0, #0x1c]
	add r0, r0, #0x20
	subs r1, r1, #0x1
	bne _020DF59C
_020DF5C8:
	and r1, r2, #0x1f
	movs r1, r1, lsr #0x2
	beq _020DF5E0
_020DF5D4:
	str r3, [r0], #0x4
	subs r1, r1, #0x1
	bne _020DF5D4
_020DF5E0:
	and r2, r2, #0x3
_020DF5E4:
	cmp r2, #0x0
	bxeq lr
	and r1, r3, #0xff
_020DF5F0:
	strb r1, [r0], #0x1
	subs r2, r2, #0x1
	bne _020DF5F0
	bx lr
	arm_func_end __fill_mem
