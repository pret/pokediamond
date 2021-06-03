    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start fclose
fclose: ; 0x020DEC88
	stmdb sp!, {r3-r5,lr}
	movs r5, r0
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r5,pc}
	ldr r1, [r5, #0x4]
	mov r1, r1, lsl #0x16
	movs r1, r1, lsr #0x1d
	moveq r0, #0x0
	ldmeqia sp!, {r3-r5,pc}
	bl fflush
	mov r4, r0
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x44]
	blx r1
	ldr r1, [r5, #0x4]
	mov r2, #0x0
	bic r1, r1, #0x380
	str r1, [r5, #0x4]
	str r2, [r5, #0x0]
	ldr r1, [r5, #0x8]
	mov r1, r1, lsl #0x1c
	movs r1, r1, lsr #0x1f
	subne r0, r2, #0x1
	ldmneia sp!, {r3-r5,pc}
	cmp r4, #0x0
	cmpeq r0, #0x0
	movne r2, #0x1
	rsb r0, r2, #0x0
	ldmia sp!, {r3-r5,pc}
	arm_func_end fclose

	arm_func_start fflush
fflush:
	stmdb sp!, {r4,lr}
	movs r4, r0
	bne _020DED10
	bl __flush_all
	ldmia sp!, {r4,pc}
_020DED10:
	ldrb r0, [r4, #0xd]
	cmp r0, #0x0
	bne _020DED2C
	ldr r0, [r4, #0x4]
	mov r1, r0, lsl #0x16
	movs r1, r1, lsr #0x1d
	bne _020DED34
_020DED2C:
	mvn r0, #0x0
	ldmia sp!, {r4,pc}
_020DED34:
	mov r0, r0, lsl #0x1b
	mov r0, r0, lsr #0x1d
	cmp r0, #0x1
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r0, [r4, #0x8]
	mov r1, r0, lsl #0x1d
	mov r1, r1, lsr #0x1d
	cmp r1, #0x3
	biccs r0, r0, #0x7
	orrcs r0, r0, #0x2
	strcs r0, [r4, #0x8]
	ldr r0, [r4, #0x8]
	mov r0, r0, lsl #0x1d
	mov r0, r0, lsr #0x1d
	cmp r0, #0x2
	moveq r0, #0x0
	streq r0, [r4, #0x28]
	ldr r0, [r4, #0x8]
	mov r1, r0, lsl #0x1d
	mov r1, r1, lsr #0x1d
	cmp r1, #0x1
	beq _020DEDA0
	bic r0, r0, #0x7
	str r0, [r4, #0x8]
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020DEDA0:
	mov r0, r4
	mov r1, #0x0
	bl __flush_buffer
	cmp r0, #0x0
	mov r0, #0x0
	beq _020DEDCC
	mov r1, #0x1
	strb r1, [r4, #0xd]
	str r0, [r4, #0x28]
	sub r0, r0, #0x1
	ldmia sp!, {r4,pc}
_020DEDCC:
	ldr r1, [r4, #0x8]
	bic r1, r1, #0x7
	str r1, [r4, #0x8]
	str r0, [r4, #0x18]
	str r0, [r4, #0x28]
	ldmia sp!, {r4,pc}
    arm_func_end fflush

    .section .exceptix,4

	.word fclose
	.short 117
	.word 0x00200300
	.word fflush
	.short 233
	.word 0x00100100
