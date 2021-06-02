	.include "asm/macros.inc"
	.include "global.inc"
	.extern __fill_mem

    .text

	arm_func_start memcpy
memcpy: ; 0x020DF438
	mov r12, r0
	cmp r2, #0x0
	bxeq lr
_020DF444:
	ldrsb r3, [r1], #0x1
	subs r2, r2, #0x1
	strb r3, [r12], #0x1
	bne _020DF444
	bx lr
    arm_func_end memcpy

	arm_func_start memmove
memmove: ; 0x020DF458
	cmp r1, r0
	blo _020DF480
	mov r12, r0
	cmp r2, #0x0
	bxeq lr
_020DF46C:
	ldrsb r3, [r1], #0x1
	subs r2, r2, #0x1
	strb r3, [r12], #0x1
	bne _020DF46C
	bx lr
_020DF480:
	cmp r2, #0x0
	add r3, r1, r2
	add r12, r0, r2
	bxeq lr
_020DF490:
	ldrsb r1, [r3, #-0x1]!
	subs r2, r2, #0x1
	strb r1, [r12, #-0x1]!
	bne _020DF490
	bx lr
    arm_func_end memmove

	arm_func_start memset
memset: ; 0x020DF4A4
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl __fill_mem
	mov r0, r4
	ldmia sp!, {r4,pc}
    arm_func_end memset

	arm_func_start memchr
memchr:
	cmp r2, #0x0
	and r3, r1, #0xff
	beq _020DF4DC
_020DF4C4:
	ldrb r1, [r0], #0x1
	cmp r1, r3
	subeq r0, r0, #0x1
	bxeq lr
	subs r2, r2, #0x1
	bne _020DF4C4
_020DF4DC:
	mov r0, #0x0
	bx lr
    arm_func_end memchr

	arm_func_start __memrchr
__memrchr: ; 0x020DF4E4
	cmp r2, #0x0
	and r3, r1, #0xff
	add r0, r0, r2
	beq _020DF508
_020DF4F4:
	ldrb r1, [r0, #-0x1]!
	cmp r1, r3
	bxeq lr
	subs r2, r2, #0x1
	bne _020DF4F4
_020DF508:
	mov r0, #0x0
	bx lr
    arm_func_end __memrchr

	arm_func_start memcmp
memcmp: ; 0x020DF510
	cmp r2, #0x0
	beq _020DF548
_020DF518:
	ldrb r12, [r0], #0x1
	ldrb r3, [r1], #0x1
	cmp r12, r3
	beq _020DF540
	ldrb r2, [r0, #-0x1]
	ldrb r0, [r1, #-0x1]
	cmp r2, r0
	mvncc r0, #0x0
	movcs r0, #0x1
	bx lr
_020DF540:
	subs r2, r2, #0x1
	bne _020DF518
_020DF548:
	mov r0, #0x0
	bx lr
    arm_func_end memcmp

    .section .exceptix,4

	.word memset
	.short 21
	.word 0x00100100
