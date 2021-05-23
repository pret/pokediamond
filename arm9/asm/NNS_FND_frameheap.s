	.include "asm/macros.inc"
	.include "global.inc"

	.extern FUN_020ADCA4
	.extern FUN_020ADC8C

	.text

	arm_func_start FUN_020AE554
FUN_020AE554: ; 0x020AE554
	add r2, r0, #0x24
	cmp r1, #0x0
	ldr r3, [r2, #0x8]
	beq _020AE584
	cmp r3, #0x0
	beq _020AE584
_020AE56C:
	ldr r0, [r3, #0x0]
	cmp r0, r1
	beq _020AE584
	ldr r3, [r3, #0xc]
	cmp r3, #0x0
	bne _020AE56C
_020AE584:
	cmp r3, #0x0
	moveq r0, #0x0
	bxeq lr
	ldr r1, [r3, #0x4]
	mov r0, #0x1
	str r1, [r2, #0x0]
	ldr r1, [r3, #0x8]
	str r1, [r2, #0x4]
	ldr r1, [r3, #0xc]
	str r1, [r2, #0x8]
	bx lr

	arm_func_start FUN_020AE5B0
FUN_020AE5B0: ; 0x020AE5B0
	stmdb sp!, {r4-r6,lr}
	add r4, r0, #0x24
	ldr r5, [r0, #0x24]
	mov r6, r1
	mov r0, r4
	mov r1, #0x10
	mov r2, #0x4
	bl FUN_020AE77C
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	str r6, [r0, #0x0]
	str r5, [r0, #0x4]
	ldr r1, [r4, #0x4]
	str r1, [r0, #0x8]
	ldr r1, [r4, #0x8]
	str r1, [r0, #0xc]
	str r0, [r4, #0x8]
	mov r0, #0x1
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020AE600
FUN_020AE600: ; 0x020AE600
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	ands r1, r4, #0x1
	beq _020AE61C
	bl FUN_020AE6F8
_020AE61C:
	ands r0, r4, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	mov r0, r5
	bl FUN_020AE6C8
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020AE638
FUN_020AE638: ; 0x020AE638
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x0
	moveq r1, #0x1
	add r1, r1, #0x3
	add r0, r0, #0x24
	cmp r2, #0x0
	bic r1, r1, #0x3
	blt _020AE668
	bl FUN_020AE77C
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020AE668:
	rsb r2, r2, #0x0
	bl FUN_020AE710
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start thunk_FUN_020adc8c_2
thunk_FUN_020adc8c_2: ; 0x020AE678
	ldr ip, _020AE680 ; =FUN_020ADC8C
	bx r12
	.balign 4
_020AE680: .word FUN_020ADC8C

	arm_func_start FUN_020AE684
FUN_020AE684: ; 0x020AE684
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	add r1, r1, r0
	add r0, r0, #0x3
	bic r1, r1, #0x3
	bic r0, r0, #0x3
	cmp r0, r1
	bhi _020AE6B0
	sub r3, r1, r0
	cmp r3, #0x30
	bhs _020AE6BC
_020AE6B0:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {pc}
_020AE6BC:
	bl FUN_020AE7E0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AE6C8
FUN_020AE6C8: ; 0x020AE6C8
	add r2, r0, #0x24
	ldr r3, [r2, #0x8]
	cmp r3, #0x0
	beq _020AE6EC
_020AE6D8:
	ldr r1, [r0, #0x1c]
	str r1, [r3, #0x8]
	ldr r3, [r3, #0xc]
	cmp r3, #0x0
	bne _020AE6D8
_020AE6EC:
	ldr r0, [r0, #0x1c]
	str r0, [r2, #0x4]
	bx lr

	arm_func_start FUN_020AE6F8
FUN_020AE6F8: ; 0x020AE6F8
	ldr r1, [r0, #0x18]
	add r2, r0, #0x24
	str r1, [r0, #0x24]
	mov r0, #0x0
	str r0, [r2, #0x8]
	bx lr

	arm_func_start FUN_020AE710
FUN_020AE710: ; 0x020AE710
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r3, [r5, #0x4]
	sub r0, r2, #0x1
	mvn r2, r0
	sub r1, r3, r1
	ldr r0, [r5, #0x0]
	and r4, r2, r1
	cmp r4, r0
	addcc sp, sp, #0x4
	movcc r0, #0x0
	ldmccia sp!, {r4-r5,pc}
	ldr r0, [r5, #-0x4]
	sub r2, r3, r4
	and r0, r0, #0xff
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ands r0, r0, #0x1
	beq _020AE76C
	mov r1, r4
	mov r0, #0x0
	bl MIi_CpuClear32
_020AE76C:
	mov r0, r4
	str r4, [r5, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020AE77C
FUN_020AE77C:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r0, [r6, #0x0]
	sub r2, r2, #0x1
	mvn r3, r2
	add r2, r2, r0
	and r5, r3, r2
	ldr r2, [r6, #0x4]
	add r4, r1, r5
	cmp r4, r2
	movhi r0, #0x0
	ldmhiia sp!, {r4-r6,pc}
	ldr r1, [r6, #-0x4]
	sub r2, r4, r0
	and r1, r1, #0xff
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	ands r1, r1, #0x1
	beq _020AE7D4
	mov r1, r0
	mov r0, #0x0
	bl MIi_CpuClear32
_020AE7D4:
	mov r0, r5
	str r4, [r6, #0x0]
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020AE7E0
FUN_020AE7E0: ; 0x020AE7E0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r3, r1
	add r4, r5, #0x24
	str r2, [sp, #0x0]
	ldr r1, _020AE828 ; =0x46524D48
	add r2, r4, #0xc
	bl FUN_020ADCA4
	ldr r0, [r5, #0x18]
	mov r1, #0x0
	str r0, [r5, #0x24]
	ldr r2, [r5, #0x1c]
	mov r0, r5
	str r2, [r4, #0x4]
	str r1, [r4, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AE828: .word 0x46524D48
