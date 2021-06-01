	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start qsort
qsort: ; 0x020E1888
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x10
	mov r9, r1
	cmp r9, #0x2
	mov r10, r0
	mov r8, r2
	mov r7, r3
	addcc sp, sp, #0x10
	ldmccia sp!, {r3-r11,pc}
	mov r0, r9, lsr #0x1
	add r11, r0, #0x1
	sub r0, r11, #0x1
	mla r0, r8, r0, r10
	sub r2, r9, #0x1
	str r0, [sp, #0xc]
	mla r0, r8, r2, r10
	str r0, [sp, #0x8]
	mul r0, r11, r8
	mvn r1, #0x0
	str r0, [sp, #0x4]
	mul r0, r8, r1
	str r0, [sp, #0x0]
_020E18E0:
	cmp r11, #0x1
	bls _020E1908
	ldr r0, [sp, #0x4]
	sub r11, r11, #0x1
	sub r0, r0, r8
	str r0, [sp, #0x4]
	ldr r0, [sp, #0xc]
	sub r0, r0, r8
	str r0, [sp, #0xc]
	b _020E1950
_020E1908:
	mov r2, r8
	ldr r4, [sp, #0x8]
	ldr r3, [sp, #0xc]
	cmp r8, #0x0
	beq _020E1934
_020E191C:
	ldrsb r0, [r4, #0x0]
	ldrsb r1, [r3, #0x0]
	subs r2, r2, #0x1
	strb r0, [r3], #0x1
	strb r1, [r4], #0x1
	bne _020E191C
_020E1934:
	sub r9, r9, #0x1
	cmp r9, #0x1
	addeq sp, sp, #0x10
	ldmeqia sp!, {r3-r11,pc}
	ldr r0, [sp, #0x8]
	sub r0, r0, r8
	str r0, [sp, #0x8]
_020E1950:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	mov r4, r11
	add r0, r1, r0
	cmp r9, r11, lsl #0x1
	add r5, r10, r0
	blo _020E18E0
_020E196C:
	mov r4, r4, lsl #0x1
	sub r0, r4, #0x1
	mov r6, r5
	mla r5, r8, r0, r10
	cmp r9, r4
	bls _020E199C
	mov r0, r5
	add r1, r5, r8
	blx r7
	cmp r0, #0x0
	addlt r4, r4, #0x1
	addlt r5, r5, r8
_020E199C:
	mov r0, r6
	mov r1, r5
	blx r7
	cmp r0, #0x0
	bge _020E18E0
	mov r2, r8
	mov r3, r5
	cmp r8, #0x0
	beq _020E19D8
_020E19C0:
	ldrsb r1, [r6, #0x0]
	ldrsb r0, [r3, #0x0]
	subs r2, r2, #0x1
	strb r0, [r6], #0x1
	strb r1, [r3], #0x1
	bne _020E19C0
_020E19D8:
	cmp r9, r4, lsl #0x1
	bhs _020E196C
	b _020E18E0
	add sp, sp, #0x10
	ldmia sp!, {r3-r11,pc}
    arm_func_end qsort
