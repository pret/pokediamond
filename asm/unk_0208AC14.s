	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start FUN_0208AC14
FUN_0208AC14: ; 0x0208AC14
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r1, [r5, #0x4]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
_0208AC34:
	ldr r4, [r1, #0x0]
	mov r0, r5
	bl FUN_0208AC58
	mov r1, r4
	cmp r4, #0x0
	bne _0208AC34
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0208AC58
FUN_0208AC58: ; 0x0208AC58
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	mov r7, r0
	add r0, r6, #0x8
	bl FUN_02090A58
	movs r1, r0
	beq _0208AC98
	add r5, r7, #0x1c
	add r4, r6, #0x8
_0208AC80:
	mov r0, r5
	bl FUN_02090AA4
	mov r0, r4
	bl FUN_02090A58
	movs r1, r0
	bne _0208AC80
_0208AC98:
	add r0, r6, #0x14
	bl FUN_02090A58
	movs r1, r0
	beq _0208ACC8
	add r5, r7, #0x1c
	add r4, r6, #0x14
_0208ACB0:
	mov r0, r5
	bl FUN_02090AA4
	mov r0, r4
	bl FUN_02090A58
	movs r1, r0
	bne _0208ACB0
_0208ACC8:
	mov r1, r6
	add r0, r7, #0x4
	bl FUN_020909D8
	mov r1, r6
	add r0, r7, #0x10
	bl FUN_02090AA4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0208ACEC
FUN_0208ACEC: ; 0x0208ACEC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r7, r0
	ldr r0, [r7, #0x10]
	mov r6, r1
	mov r5, r2
	cmp r0, #0x0
	mov r4, #0x0
	beq _0208AD70
	add r1, sp, #0x0
	str r4, [r1, #0x0]
	str r4, [r1, #0x4]
	add r0, r7, #0x10
	str r4, [r1, #0x8]
	bl FUN_02090A58
	ldr r1, [r7, #0x28]
	add r2, sp, #0x0
	add r1, r1, r6, lsl #0x5
	mov r4, r0
	bl FUN_0208C138
_0208AD3C: ; 0x0208AD3C
	cmp r5, #0x0
	beq _0208AD4C
	mov r0, r4
	blx r5
_0208AD4C:
	mov r1, r4
	add r0, r7, #0x4
	bl FUN_02090AA4
	ldr r0, [r4, #0x20]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x11
	movs r0, r0, lsr #0x1f
	movne r4, #0x0
_0208AD70:
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0208AD80
FUN_0208AD80: ; 0x0208AD80
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r2, _0208AE44 ; =0x04000060
	mov r4, r0
	ldrh r0, [r2, #0x0]
	bic r0, r0, #0x3000
	orr r0, r0, #0x8
	strh r0, [r2, #0x0]
	str r1, [r4, #0x44]
	ldr r0, [r4, #0x38]
	mov r0, r0, lsl #0x7
	movs r0, r0, lsr #0x1f
	bne _0208ADFC
	ldr r5, [r4, #0x4]
	cmp r5, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
_0208ADC8:
	str r5, [r4, #0x40]
	ldr r0, [r5, #0x24]
	mov r0, r0, lsl #0x1c
	movs r0, r0, lsr #0x1f
	bne _0208ADE4
	mov r0, r4
	bl FUN_0208B6A0
_0208ADE4:
	ldr r5, [r5, #0x0]
	cmp r5, #0x0
	bne _0208ADC8
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_0208ADFC:
	ldr r5, [r4, #0xc]
	cmp r5, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
_0208AE10:
	str r5, [r4, #0x40]
	ldr r0, [r5, #0x24]
	mov r0, r0, lsl #0x1c
	movs r0, r0, lsr #0x1f
	bne _0208AE2C
	mov r0, r4
	bl FUN_0208B6A0
_0208AE2C:
	ldr r5, [r5, #0x4]
	cmp r5, #0x0
	bne _0208AE10
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0208AE44: .word 0x04000060

	arm_func_start FUN_0208AE48
FUN_0208AE48: ; 0x0208AE48
	stmdb sp!, {r4-r10,lr}
	mov r8, r0
	ldr r7, [r8, #0x4]
	cmp r7, #0x0
	beq _0208AF5C
	add r10, r8, #0x4
	add r9, r8, #0x10
	mov r4, #0x0
_0208AE68:
	ldr r2, [r7, #0x24]
	ldr r1, [r7, #0x20]
	mov r0, r2, lsl #0x1b
	movs r0, r0, lsr #0x1f
	ldr r5, [r1, #0x0]
	ldr r6, [r7, #0x0]
	bne _0208AE9C
	ldrh r1, [r7, #0x4c]
	ldrh r0, [r5, #0x32]
	cmp r1, r0
	orrcs r0, r2, #0x10
	strcs r0, [r7, #0x24]
	strcsh r4, [r7, #0x4c]
_0208AE9C:
	ldr r0, [r7, #0x24]
	mov r0, r0, lsl #0x1d
	movs r0, r0, lsr #0x1f
	bne _0208AED8
	ldr r0, [r7, #0x80]
	mov r0, r0, lsl #0xd
	movs r0, r0, lsr #0x1d
	beq _0208AECC
	ldrh r1, [r8, #0x48]
	sub r0, r0, #0x1
	cmp r1, r0
	bne _0208AED8
_0208AECC:
	mov r0, r8
	mov r1, r7
	bl FUN_0208B8F0
_0208AED8:
	ldr r0, [r5, #0x0]
	mov r0, r0, lsl #0x11
	movs r0, r0, lsr #0x1f
	beq _0208AF10
	ldrh r1, [r5, #0x3c]
	cmp r1, #0x0
	beq _0208AF10
	ldr r0, [r7, #0x24]
	mov r0, r0, lsl #0x1b
	movs r0, r0, lsr #0x1f
	beq _0208AF10
	ldrh r0, [r7, #0x4c]
	cmp r0, r1
	bhi _0208AF20
_0208AF10:
	ldr r0, [r7, #0x24]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	beq _0208AF50
_0208AF20:
	ldr r0, [r7, #0xc]
	cmp r0, #0x0
	bne _0208AF50
	ldr r0, [r7, #0x18]
	cmp r0, #0x0
	bne _0208AF50
	mov r0, r10
	mov r1, r7
	bl FUN_020909D8
	mov r1, r0
	mov r0, r9
	bl FUN_02090AA4
_0208AF50:
	mov r7, r6
	cmp r6, #0x0
	bne _0208AE68
_0208AF5C:
	ldrh r0, [r8, #0x48]
	add r0, r0, #0x1
	strh r0, [r8, #0x48]
	ldrh r0, [r8, #0x48]
	cmp r0, #0x1
	movhi r0, #0x0
	strhih r0, [r8, #0x48]
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start FUN_0208AF80
FUN_0208AF80: ; 0x0208AF80
	ldr ip, _0208AF8C ; =FUN_0208AFA8
	ldr r1, _0208AF90 ; =FUN_0208B630
	bx r12
	.balign 4
_0208AF8C: .word FUN_0208AFA8
_0208AF90: .word FUN_0208B630

	arm_func_start FUN_0208AF94
FUN_0208AF94: ; 0x0208AF94
	ldr ip, _0208AFA0 ; =FUN_0208B05C
	ldr r1, _0208AFA4 ; =FUN_0208B668
	bx r12
	.balign 4
_0208AFA0: .word FUN_0208B05C
_0208AFA4: .word FUN_0208B668

	arm_func_start FUN_0208AFA8
FUN_0208AFA8: ; 0x0208AFA8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r10, r0
	mov r11, r1
	bl GX_BeginLoadTexPltt
	ldrh r0, [r10, #0x32]
	mov r9, #0x0
	cmp r0, #0x0
	ble _0208B048
	mov r0, #0x1
	mov r5, r9
	mov r4, r9
	str r0, [sp, #0x0]
_0208AFDC:
	ldr r0, [r10, #0x2c]
	mov r6, r4
	ldr r7, [r0, r5]
	add r8, r0, r5
	ldr r0, [r7, #0x10]
	cmp r0, #0x0
	beq _0208B030
	ldr r1, [r7, #0x4]
	mov r1, r1, lsl #0x1c
	mov r1, r1, lsr #0x1c
	cmp r1, #0x2
	ldreq r1, [sp, #0x0]
	movne r1, r4
	blx r11
	mov r6, r0
	ldr r1, [r8, #0x0]
	ldr r0, [r7, #0xc]
	ldr r2, [r7, #0x10]
	add r0, r1, r0
	mov r1, r6
	bl GX_LoadTexPltt
_0208B030:
	str r6, [r8, #0x8]
	ldrh r0, [r10, #0x32]
	add r9, r9, #0x1
	add r5, r5, #0x14
	cmp r9, r0
	blt _0208AFDC
_0208B048:
	bl GX_EndLoadTexPltt
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_0208B05C
FUN_0208B05C: ; 0x0208B05C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r10, r0
	mov r11, r1
	bl GX_BeginLoadTex
	ldrh r0, [r10, #0x32]
	mov r9, #0x0
	cmp r0, #0x0
	ble _0208B114
	mov r0, #0x1
	mov r6, r9
	str r9, [sp, #0x4]
	str r0, [sp, #0x0]
	mov r4, #0x14
_0208B094:
	ldr r2, [r10, #0x2c]
	ldr r7, [r2, r6]
	add r8, r2, r6
	ldr r0, [r7, #0x4]
	mov r1, r0, lsl #0xe
	movs r1, r1, lsr #0x1f
	beq _0208B0C8
	mov r0, r0, lsl #0x6
	mov r1, r0, lsr #0x18
	mla r0, r1, r4, r2
	ldr r0, [r0, #0x4]
	str r0, [r8, #0x4]
	b _0208B100
_0208B0C8:
	mov r0, r0, lsl #0x1c
	mov r0, r0, lsr #0x1c
	cmp r0, #0x5
	ldreq r1, [sp, #0x0]
	ldr r0, [r7, #0x8]
	ldrne r1, [sp, #0x4]
	blx r11
	mov r5, r0
	ldr r0, [r8, #0x0]
	ldr r2, [r7, #0x8]
	add r0, r0, #0x20
	mov r1, r5
	bl GX_LoadTex
	str r5, [r8, #0x4]
_0208B100:
	ldrh r0, [r10, #0x32]
	add r9, r9, #0x1
	add r6, r6, #0x14
	cmp r9, r0
	blt _0208B094
_0208B114:
	bl GX_EndLoadTex
	mov r0, #0x1
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_0208B128
FUN_0208B128: ; 0x0208B128
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x2c
	mov r9, r1
	ldrh r1, [r9, #0x8]
	mov r10, r0
	mov r8, #0x20
	strh r1, [r10, #0x30]
	ldrh r0, [r9, #0xa]
	strh r0, [r10, #0x32]
	ldrh r0, [r10, #0x30]
	ldr r1, [r10, #0x0]
	mov r0, r0, lsl #0x5
	blx r1
	str r0, [r10, #0x28]
	ldrh r2, [r10, #0x30]
	ldr r0, [r10, #0x28]
	mov r1, #0x0
	mov r2, r2, lsl #0x5
	bl MI_CpuFill8
	ldrh r1, [r10, #0x30]
	mov r0, #0x0
	str r0, [sp, #0x0]
	cmp r1, #0x0
	ble _0208B3C8
	mov r6, r0
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
_0208B1A4:
	ldr r1, [r10, #0x28]
	add r0, r9, r8
	str r0, [r1, r6]
	ldr r0, [r1, r6]
	add r8, r8, #0x58
	ldr r0, [r0, #0x0]
	add r7, r1, r6
	str r0, [sp, #0x28]
	mov r0, r0, lsl #0x17
	movs r0, r0, lsr #0x1f
	addne r0, r9, r8
	strne r0, [r7, #0x4]
	ldreq r0, [sp, #0x10]
	addne r8, r8, #0xc
	streq r0, [r7, #0x4]
	ldr r0, [sp, #0x28]
	mov r0, r0, lsl #0x16
	movs r0, r0, lsr #0x1f
	addne r0, r9, r8
	strne r0, [r7, #0x8]
	ldreq r0, [sp, #0x14]
	addne r8, r8, #0xc
	streq r0, [r7, #0x8]
	ldr r0, [sp, #0x28]
	mov r0, r0, lsl #0x15
	movs r0, r0, lsr #0x1f
	addne r0, r9, r8
	strne r0, [r7, #0xc]
	ldreq r0, [sp, #0x18]
	addne r8, r8, #0x8
	streq r0, [r7, #0xc]
	ldr r0, [sp, #0x28]
	mov r0, r0, lsl #0x14
	movs r0, r0, lsr #0x1f
	addne r0, r9, r8
	strne r0, [r7, #0x10]
	ldreq r0, [sp, #0x1c]
	addne r8, r8, #0xc
	streq r0, [r7, #0x10]
	ldr r0, [sp, #0x28]
	mov r0, r0, lsl #0xf
	movs r0, r0, lsr #0x1f
	addne r0, r9, r8
	strne r0, [r7, #0x14]
	ldreq r0, [sp, #0x20]
	addne r8, r8, #0x14
	streq r0, [r7, #0x14]
	ldr r0, [sp, #0x28]
	mov r1, r0, lsl #0x7
	mov r2, r0, lsl #0x6
	mov r5, r1, lsr #0x1f
	mov r4, r2, lsr #0x1f
	add r1, r5, r2, lsr #0x1f
	mov r2, r0, lsl #0x5
	add r1, r1, r2, lsr #0x1f
	mov r3, r0, lsl #0x4
	mov r11, r2, lsr #0x1f
	add r2, r1, r3, lsr #0x1f
	mov r1, r3, lsr #0x1f
	mov r12, r0, lsl #0x3
	str r1, [sp, #0x4]
	mov r3, r0, lsl #0x2
	mov r0, r12, lsr #0x1f
	add r1, r2, r12, lsr #0x1f
	str r0, [sp, #0x8]
	add r0, r1, r3, lsr #0x1f
	strh r0, [r7, #0x1c]
	mov r0, r3, lsr #0x1f
	str r0, [sp, #0xc]
	ldrh r0, [r7, #0x1c]
	cmp r0, #0x0
	beq _0208B3A4
	mov r0, r0, lsl #0x3
	ldr r1, [r10, #0x0]
	blx r1
	str r0, [r7, #0x18]
	cmp r5, #0x0
	ldr r0, [r7, #0x18]
	beq _0208B2F8
	add r1, r9, r8
	str r1, [r0, #0x4]
	ldr r1, _0208B488 ; =FUN_020909A4
	add r8, r8, #0x8
	str r1, [r0, #0x0]
	add r0, r0, #0x8
_0208B2F8:
	cmp r4, #0x0
	beq _0208B318
	add r1, r9, r8
	str r1, [r0, #0x4]
	ldr r1, _0208B48C ; =FUN_020908DC
	add r8, r8, #0x8
	str r1, [r0, #0x0]
	add r0, r0, #0x8
_0208B318:
	cmp r11, #0x0
	beq _0208B338
	add r1, r9, r8
	str r1, [r0, #0x4]
	ldr r1, _0208B490 ; =FUN_02090858
	add r8, r8, #0x10
	str r1, [r0, #0x0]
	add r0, r0, #0x8
_0208B338:
	ldr r1, [sp, #0x4]
	cmp r1, #0x0
	beq _0208B35C
	add r1, r9, r8
	str r1, [r0, #0x4]
	ldr r1, _0208B494 ; =FUN_02090780
	add r8, r8, #0x4
	str r1, [r0, #0x0]
	add r0, r0, #0x8
_0208B35C:
	ldr r1, [sp, #0x8]
	cmp r1, #0x0
	beq _0208B380
	add r1, r9, r8
	str r1, [r0, #0x4]
	ldr r1, _0208B498 ; =FUN_02090664
	add r8, r8, #0x8
	str r1, [r0, #0x0]
	add r0, r0, #0x8
_0208B380:
	ldr r1, [sp, #0xc]
	cmp r1, #0x0
	beq _0208B3AC
	add r1, r9, r8
	str r1, [r0, #0x4]
	ldr r1, _0208B49C ; =FUN_020905D0
	add r8, r8, #0x10
	str r1, [r0, #0x0]
	b _0208B3AC
_0208B3A4:
	ldr r0, [sp, #0x24]
	str r0, [r7, #0x18]
_0208B3AC:
	ldr r0, [sp, #0x0]
	ldrh r1, [r10, #0x30]
	add r0, r0, #0x1
	add r6, r6, #0x20
	str r0, [sp, #0x0]
	cmp r0, r1
	blt _0208B1A4
_0208B3C8:
	ldrh r2, [r10, #0x32]
	mov r0, #0x14
	ldr r1, [r10, #0x0]
	mul r0, r2, r0
	blx r1
	str r0, [r10, #0x2c]
	ldrh r3, [r10, #0x32]
	mov r1, #0x14
	ldr r0, [r10, #0x2c]
	mul r2, r3, r1
	mov r1, #0x0
	bl MI_CpuFill8
	ldrh r0, [r10, #0x32]
	mov r3, #0x0
	cmp r0, #0x0
	addle sp, sp, #0x2c
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	mov r4, r3
	mov r0, #0x1
_0208B418:
	ldr r2, [r10, #0x2c]
	add r1, r9, r8
	str r1, [r2, r4]
	ldr r5, [r1, #0x4]
	add r2, r2, r4
	mov r5, r5, lsl #0x18
	mov r5, r5, lsr #0x1c
	add r5, r5, #0x3
	mov r5, r0, lsl r5
	strh r5, [r2, #0x10]
	ldr r5, [r1, #0x4]
	add r3, r3, #0x1
	mov r5, r5, lsl #0x14
	mov r5, r5, lsr #0x1c
	add r5, r5, #0x3
	mov r5, r0, lsl r5
	strh r5, [r2, #0x12]
	ldr r5, [r1, #0x4]
	add r4, r4, #0x14
	str r5, [r2, #0xc]
	ldrh r2, [r10, #0x32]
	ldr r1, [r1, #0x1c]
	cmp r3, r2
	add r8, r8, r1
	blt _0208B418
	add sp, sp, #0x2c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0208B488: .word FUN_020909A4
_0208B48C: .word FUN_020908DC
_0208B490: .word FUN_02090858
_0208B494: .word FUN_02090780
_0208B498: .word FUN_02090664
_0208B49C: .word FUN_020905D0

	arm_func_start FUN_0208B4A0
FUN_0208B4A0: ; 0x0208B4A0
	stmdb sp!, {r4-r10,lr}
	mov r8, r0
	mov r0, #0x4c
	mov r7, r1
	mov r6, r2
	mov r4, r3
	blx r8
	mov r5, r0
	mov r1, #0x0
	mov r2, #0x4c
	bl MI_CpuFill8
	strh r7, [r5, #0x34]
	strh r6, [r5, #0x36]
	ldrh r0, [sp, #0x20]
	and r2, r4, #0x3f
	ldr r1, [r5, #0x38]
	and r0, r0, #0x3f
	bic r1, r1, #0x3f
	orr r0, r1, r0
	str r0, [r5, #0x38]
	ldrh r0, [sp, #0x24]
	ldr r3, [r5, #0x38]
	mov r1, #0x0
	bic r3, r3, #0xfc0
	and r0, r0, #0x3f
	orr r0, r3, r0, lsl #0x6
	str r0, [r5, #0x38]
	ldr r3, [r5, #0x38]
	mov r0, #0x9c
	mul r4, r7, r0
	bic r12, r3, #0x3f000
	mov r0, r3, lsl #0x1a
	mov r0, r0, lsr #0x1a
	and r0, r0, #0x3f
	orr r0, r12, r0, lsl #0xc
	str r0, [r5, #0x38]
	ldr r3, [r5, #0x38]
	mov r0, r4
	bic r3, r3, #0xfc0000
	orr r2, r3, r2, lsl #0x12
	str r2, [r5, #0x38]
	ldr r2, [r5, #0x38]
	bic r2, r2, #0x1000000
	str r2, [r5, #0x38]
	ldr r2, [r5, #0x38]
	bic r2, r2, #0xfe000000
	str r2, [r5, #0x38]
	str r8, [r5, #0x0]
	str r1, [r5, #0x8]
	str r1, [r5, #0x14]
	str r1, [r5, #0x20]
	str r1, [r5, #0x4]
	str r1, [r5, #0x10]
	str r1, [r5, #0x1c]
	str r1, [r5, #0x3c]
	strh r1, [r5, #0x48]
	blx r8
	mov r2, r4
	mov r9, r0
	mov r1, #0x0
	bl MI_CpuFill8
_0208B594: ; 0x0208B594
	cmp r7, #0x0
	mov r10, #0x0
	ble _0208B5C0
	add r4, r5, #0x10
_0208B5A4:
	mov r0, r4
	mov r1, r9
	bl FUN_02090AA4
	add r10, r10, #0x1
	cmp r10, r7
	add r9, r9, #0x9c
	blt _0208B5A4
_0208B5C0:
	mov r0, #0x44
	mul r4, r6, r0
	mov r0, r4
	blx r8
	mov r2, r4
	mov r1, #0x0
	mov r8, r0
	bl MI_CpuFill8
_0208B5E0: ; 0x0208B5E0
	cmp r6, #0x0
	mov r7, #0x0
	ble _0208B60C
	add r4, r5, #0x1c
_0208B5F0:
	mov r0, r4
	mov r1, r8
	bl FUN_02090AA4
	add r7, r7, #0x1
	cmp r7, r6
	add r8, r8, #0x44
	blt _0208B5F0
_0208B60C:
	mov r0, #0x0
	str r0, [r5, #0x28]
	str r0, [r5, #0x2c]
	strh r0, [r5, #0x32]
	ldrh r1, [r5, #0x32]
	mov r0, r5
	strh r1, [r5, #0x30]
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start FUN_0208B630
FUN_0208B630: ; 0x0208B630
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, _0208B660 ; =0x021064C0
	mov r2, #0x0
	ldr r3, [r3, #0x0]
	blx r3
	ldr r1, _0208B664 ; =0x0000FFFF
	and r0, r0, r1
	mov r0, r0, lsl #0x3
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0208B660: .word 0x021064C0
_0208B664: .word 0x0000FFFF

	arm_func_start FUN_0208B668
FUN_0208B668: ; 0x0208B668
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, _0208B698 ; =0x021064B8
	mov r2, #0x0
	ldr r3, [r3, #0x0]
	blx r3
	ldr r1, _0208B69C ; =0x0000FFFF
	and r0, r0, r1
	mov r0, r0, lsl #0x3
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0208B698: .word 0x021064B8
_0208B69C: .word 0x0000FFFF

	arm_func_start FUN_0208B6A0
FUN_0208B6A0: ; 0x0208B6A0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r1, [r4, #0x40]
	ldr r1, [r1, #0x20]
	ldr r5, [r1, #0x0]
	ldr r1, [r5, #0x0]
	mov r2, r1, lsl #0xa
	movs r2, r2, lsr #0x1f
	beq _0208B6F8
	bl FUN_0208B71C
_0208B6CC: ; 0x0208B6CC
	ldr r0, [r5, #0x0]
	mov r0, r0, lsl #0x9
	movs r0, r0, lsr #0x1f
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r0, r4
	bl FUN_0208B804
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_0208B6F8:
	mov r1, r1, lsl #0x9
	movs r1, r1, lsr #0x1f
	bne _0208B708
	bl FUN_0208B804
_0208B708:
	mov r0, r4
	bl FUN_0208B71C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0208B71C
FUN_0208B71C:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r6, [r7, #0x40]
	mov r4, #0x0
	ldr r5, [r6, #0x20]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0xf
	movs r0, r0, lsr #0x1f
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, [r5, #0x14]
	ldr r2, [r7, #0x2c]
	ldrb r1, [r0, #0xf]
	mov r0, #0x14
	mla r0, r1, r0, r2
	bl FUN_0208C408
	ldr r0, [r5, #0x14]
	ldrh r0, [r0, #0x0]
	mov r0, r0, lsl #0x17
	mov r0, r0, lsr #0x1e
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _0208B7BC
_0208B784:
	b _0208B798
_0208B788:
	b _0208B7A0
_0208B78C:
	b _0208B7A8
_0208B790:
	b _0208B7B0
_0208B794:
	b _0208B7B8
_0208B798:
	ldr r4, _0208B7F4 ; =FUN_0208E258
	b _0208B7BC
_0208B7A0:
	ldr r4, _0208B7F8 ; =FUN_0208D490
	b _0208B7BC
_0208B7A8:
	ldr r4, _0208B7FC ; =FUN_0208CDF0
	b _0208B7BC
_0208B7B0:
	ldr r4, _0208B800 ; =FUN_0208C4F4
	b _0208B7BC
_0208B7B8:
	ldr r4, _0208B800 ; =FUN_0208C4F4
_0208B7BC:
	ldr r5, [r6, #0x14]
	cmp r5, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
_0208B7D0:
	mov r0, r7
	mov r1, r5
	blx r4
	ldr r5, [r5, #0x0]
	cmp r5, #0x0
	bne _0208B7D0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0208B7F4: .word FUN_0208E258
_0208B7F8: .word FUN_0208D490
_0208B7FC: .word FUN_0208CDF0
_0208B800: .word FUN_0208C4F4

	arm_func_start FUN_0208B804
FUN_0208B804: ; 0x0208B804
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	ldr r6, [r7, #0x40]
	ldr r2, [r7, #0x2c]
	ldr r1, [r6, #0x20]
	mov r0, #0x14
	ldr r5, [r1, #0x0]
	mov r4, #0x0
	ldrb r1, [r5, #0x47]
	mla r0, r1, r0, r2
	bl FUN_0208C408
_0208B830: ; 0x0208B830
	ldr r0, [r5, #0x0]
	mov r0, r0, lsl #0x1a
	mov r0, r0, lsr #0x1e
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _0208B880
_0208B848:
	b _0208B85C
_0208B84C:
	b _0208B864
_0208B850:
	b _0208B86C
_0208B854:
	b _0208B874
_0208B858:
	b _0208B87C
_0208B85C:
	ldr r4, _0208B8D8 ; =FUN_0208E6AC
	b _0208B880
_0208B864:
	ldr r4, _0208B8DC ; =FUN_0208DB70
	b _0208B880
_0208B86C:
	ldr r4, _0208B8E0 ; =FUN_0208D140
	b _0208B880
_0208B874:
	ldr r4, _0208B8E4 ; =FUN_0208C974
	b _0208B880
_0208B87C:
	ldr r4, _0208B8E4 ; =FUN_0208C974
_0208B880:
	ldr r0, [r5, #0x0]
	ldr r8, [r6, #0x8]
	mov r0, r0, lsl #0x14
	movs r0, r0, lsr #0x1f
	ldrne r5, _0208B8E8 ; =FUN_0208C408
	ldreq r5, _0208B8EC ; =FUN_0208C404
	cmp r8, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r6, #0x14
_0208B8A8:
	ldrb r1, [r8, #0x2c]
	ldr r0, [r7, #0x2c]
	mla r0, r1, r6, r0
	blx r5
	mov r0, r7
	mov r1, r8
	blx r4
	ldr r8, [r8, #0x0]
	cmp r8, #0x0
	bne _0208B8A8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0208B8D8: .word FUN_0208E6AC
_0208B8DC: .word FUN_0208DB70
_0208B8E0: .word FUN_0208D140
_0208B8E4: .word FUN_0208C974
_0208B8E8: .word FUN_0208C408
_0208B8EC: .word FUN_0208C404

	arm_func_start FUN_0208B8F0
FUN_0208B8F0:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x74
	mov r9, r1
	ldr r8, [r9, #0x20]
	mov r10, r0
	ldr r0, [r8, #0x14]
	ldr r4, [r8, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x0]
	mov r6, #0x0
	str r0, [sp, #0x24]
	ldrb r0, [r4, #0x46]
	ldr r2, [r9, #0x90]
	ldrh r7, [r8, #0x1c]
	add r0, r0, #0x180
	cmp r2, #0x0
	str r0, [sp, #0x8]
	beq _0208B944
	mov r0, r9
	mov r1, r6
	blx r2
_0208B944:
	ldrh r1, [r4, #0x3c]
	cmp r1, #0x0
	beq _0208B95C
	ldrh r0, [r9, #0x4c]
	cmp r0, r1
	bhs _0208B9A4
_0208B95C:
	ldrh r0, [r9, #0x4c]
	ldrb r1, [r9, #0x80]
	bl _s32_div_f
_0208B968: ; 0x0208B968
	cmp r1, #0x0
	bne _0208B9A4
	ldr r1, [r9, #0x24]
	mov r0, r1, lsl #0x1f
	movs r0, r0, lsr #0x1f
	bne _0208B9A4
	mov r0, r1, lsl #0x1e
	movs r0, r0, lsr #0x1f
	bne _0208B9A4
	mov r0, r1, lsl #0x1b
	movs r0, r0, lsr #0x1f
	beq _0208B9A4
	mov r0, r9
	add r1, r10, #0x1c
	bl FUN_0208F07C
_0208B9A4:
	ldr r0, [sp, #0x24]
	mov r0, r0, lsl #0x17
	movs r0, r0, lsr #0x1f
	beq _0208B9D4
	ldr r0, _0208C120 ; =FUN_02090540
	add r6, r6, #0x1
	str r0, [sp, #0x28]
	ldr r0, [r8, #0x4]
	ldrh r0, [r0, #0x8]
	mov r0, r0, lsl #0x1f
	mov r0, r0, lsr #0x1f
	str r0, [sp, #0x2c]
_0208B9D4:
	ldr r0, [sp, #0x24]
	mov r0, r0, lsl #0x16
	movs r0, r0, lsr #0x1f
	beq _0208BA20
	ldr r3, [r8, #0x8]
	ldrh r0, [r3, #0x8]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	bne _0208BA20
	ldr r2, _0208C124 ; =FUN_02090374
	add r1, sp, #0x28
	str r2, [r1, r6, lsl #0x3]
	ldrh r1, [r3, #0x8]
	mov r2, r6, lsl #0x3
	add r0, sp, #0x2c
	mov r1, r1, lsl #0x1e
	mov r1, r1, lsr #0x1f
	add r6, r6, #0x1
	str r1, [r0, r2]
_0208BA20:
	ldr r0, [sp, #0x24]
	mov r0, r0, lsl #0x15
	movs r0, r0, lsr #0x1f
	beq _0208BA5C
	ldr r2, _0208C128 ; =FUN_02090298
	add r1, sp, #0x28
	str r2, [r1, r6, lsl #0x3]
	ldr r1, [r8, #0xc]
	mov r2, r6, lsl #0x3
	ldrh r1, [r1, #0x2]
	add r0, sp, #0x2c
	add r6, r6, #0x1
	mov r1, r1, lsl #0x17
	mov r1, r1, lsr #0x1f
	str r1, [r0, r2]
_0208BA5C:
	ldr r0, [sp, #0x24]
	mov r0, r0, lsl #0x14
	movs r0, r0, lsr #0x1f
	beq _0208BAA4
	ldr r3, [r8, #0x10]
	ldr r0, [r3, #0x8]
	mov r0, r0, lsl #0xf
	movs r0, r0, lsr #0x1f
	bne _0208BAA4
	ldr r2, _0208C12C ; =FUN_02090234
	add r1, sp, #0x28
	str r2, [r1, r6, lsl #0x3]
	ldr r1, [r3, #0x8]
	add r0, sp, #0x2c
	mov r1, r1, lsl #0xe
	mov r1, r1, lsr #0x1f
	str r1, [r0, r6, lsl #0x3]
	add r6, r6, #0x1
_0208BAA4:
	ldr r4, [r9, #0x8]
	cmp r4, #0x0
	beq _0208BDE0
	ldr r0, [sp, #0x24]
	add r11, sp, #0x28
	mov r2, r0, lsl #0x10
	mov r1, r0, lsl #0xf
	mov r0, r2, lsr #0x1f
	str r0, [sp, #0xc]
	mov r0, r1, lsr #0x1f
	str r0, [sp, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x18]
_0208BAD8:
	ldr r0, [r4, #0x0]
	ldrh r1, [r4, #0x2a]
	str r0, [sp, #0x0]
	ldrh r0, [r4, #0x26]
	cmp r6, #0x0
	ldr r5, [sp, #0x18]
	mul r2, r1, r0
	mov r1, r2, asr #0x8
	strb r1, [sp, #0x20]
	ldrh r1, [r4, #0x28]
	ldrb r2, [r4, #0x2d]
	mul r0, r1, r0
	add r0, r2, r0, asr #0x8
	strb r0, [sp, #0x21]
	ble _0208BB40
_0208BB14:
	add r2, r11, r5, lsl #0x3
	ldr r12, [r2, #0x4]
	add r2, sp, #0x20
	ldrb r2, [r2, r12]
	ldr r3, [r11, r5, lsl #0x3]
	mov r0, r4
	mov r1, r8
	blx r3
	add r5, r5, #0x1
	cmp r5, r6
	blt _0208BB14
_0208BB40:
	ldr r0, [sp, #0x18]
	ldr r5, [sp, #0x18]
	str r0, [sp, #0x70]
	str r0, [sp, #0x6c]
	str r0, [sp, #0x68]
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	addne r0, r9, #0x28
	addne r3, r4, #0x38
	ldmneia r0, {r0-r2}
	stmneia r3, {r0-r2}
	cmp r7, #0x0
	ble _0208BBA0
_0208BB74:
	ldr r2, [r8, #0x18]
	mov r1, r4
	add r0, r2, r5, lsl #0x3
	ldr r12, [r2, r5, lsl #0x3]
	ldr r0, [r0, #0x4]
	add r2, sp, #0x68
	mov r3, r9
	blx r12
	add r5, r5, #0x1
	cmp r5, r7
	blt _0208BB74
_0208BBA0:
	ldr r0, [sp, #0x10]
	ldrh r1, [r4, #0x20]
	cmp r0, #0x0
	ldrsh r0, [r4, #0x22]
	add r0, r1, r0
	strh r0, [r4, #0x20]
	ldr r1, [r4, #0x14]
	ldr r0, [sp, #0x8]
	mul r0, r1, r0
	mov r0, r0, asr #0x9
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	ldr r0, [sp, #0x8]
	mul r0, r1, r0
	mov r0, r0, asr #0x9
	str r0, [r4, #0x18]
	ldr r1, [r4, #0x1c]
	ldr r0, [sp, #0x8]
	mul r0, r1, r0
	mov r0, r0, asr #0x9
	str r0, [r4, #0x1c]
	ldr r1, [r4, #0x14]
	ldr r0, [sp, #0x68]
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	ldr r0, [sp, #0x6c]
	add r0, r1, r0
	str r0, [r4, #0x18]
	ldr r1, [r4, #0x1c]
	ldr r0, [sp, #0x70]
	add r0, r1, r0
	str r0, [r4, #0x1c]
	ldr r1, [r4, #0x14]
	ldr r0, [r9, #0x34]
	ldr r2, [r4, #0x8]
	add r0, r1, r0
	add r0, r2, r0
	str r0, [r4, #0x8]
	ldr r1, [r4, #0x18]
	ldr r0, [r9, #0x38]
	ldr r2, [r4, #0xc]
	add r0, r1, r0
	add r0, r2, r0
	str r0, [r4, #0xc]
	ldr r1, [r4, #0x1c]
	ldr r0, [r9, #0x3c]
	ldr r2, [r4, #0x10]
	add r0, r1, r0
	add r0, r2, r0
	str r0, [r4, #0x10]
	beq _0208BCD8
	ldr r0, [sp, #0x4]
	ldrh r2, [r4, #0x24]
	ldrb r1, [r0, #0xd]
	ldrh r3, [r4, #0x26]
	mov r2, r2, lsl #0xc
	mov r1, r1, lsl #0xc
	mov r0, r3, lsl #0xc
	smull r5, r3, r2, r1
	mov r1, #0x800
	adds r2, r5, r1
	adc r1, r3, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	mov r1, r2, asr #0x8
	subs r0, r0, r1
	bmi _0208BCD8
	ldr r1, [sp, #0x4]
	mov r0, r0, asr #0xc
	ldrb r1, [r1, #0xe]
	bl _s32_div_f
_0208BCC0: ; 0x0208BCC0
	cmp r1, #0x0
	bne _0208BCD8
	mov r0, r4
	mov r1, r9
	add r2, r10, #0x1c
	bl FUN_0208ED5C
_0208BCD8:
	ldr r0, [r9, #0x20]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x1
	movs r0, r0, lsr #0x1f
	beq _0208BD1C
	ldrh r0, [r4, #0x2e]
	ldr r1, [r10, #0x38]
	bic r0, r0, #0xfc00
	mov r1, r1, lsl #0x8
	mov r1, r1, lsr #0x1a
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	and r1, r1, #0x3f
	orr r0, r0, r1, lsl #0xa
	strh r0, [r4, #0x2e]
	b _0208BD9C
_0208BD1C:
	ldrh r0, [r4, #0x2e]
	ldr r2, [r10, #0x38]
	add r1, r10, #0x38
	bic r0, r0, #0xfc00
	mov r2, r2, lsl #0xe
	mov r2, r2, lsr #0x1a
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	and r2, r2, #0x3f
	orr r0, r0, r2, lsl #0xa
	strh r0, [r4, #0x2e]
	ldr r2, [r10, #0x38]
	bic r0, r2, #0x3f000
	mov r2, r2, lsl #0xe
	mov r2, r2, lsr #0x1a
	add r2, r2, #0x1
	and r2, r2, #0x3f
	orr r0, r0, r2, lsl #0xc
	str r0, [r10, #0x38]
	ldr r2, [r10, #0x38]
	mov r0, r2, lsl #0xe
	mov r3, r0, lsr #0x1a
	mov r0, r2, lsl #0x14
	cmp r3, r0, lsr #0x1a
	bls _0208BD9C
	mov r0, r2, lsl #0x1a
	mov r0, r0, lsr #0x1a
	and r0, r0, #0x3f
	ldr r2, [r1, #0x0]
	bic r2, r2, #0x3f000
	orr r0, r2, r0, lsl #0xc
	str r0, [r1, #0x0]
_0208BD9C:
	ldrh r0, [r4, #0x26]
	add r0, r0, #0x1
	strh r0, [r4, #0x26]
	ldrh r1, [r4, #0x26]
	ldrh r0, [r4, #0x24]
	cmp r1, r0
	bls _0208BDD0
	mov r1, r4
	add r0, r9, #0x8
	bl FUN_020909D8
	mov r1, r0
	add r0, r10, #0x1c
	bl FUN_02090AA4
_0208BDD0:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	mov r4, r0
	bne _0208BAD8
_0208BDE0:
	ldr r0, [sp, #0x24]
	mov r0, r0, lsl #0xf
	movs r0, r0, lsr #0x1f
	beq _0208C0E8
	ldr r0, [sp, #0x4]
	mov r6, #0x0
	ldrh r0, [r0, #0x0]
	mov r0, r0, lsl #0x1e
	movs r0, r0, lsr #0x1f
	ldrne r0, _0208C130 ; =FUN_020901E8
	strne r6, [sp, #0x4c]
	strne r0, [sp, #0x48]
	ldr r0, [sp, #0x4]
	addne r6, r6, #0x1
	ldrh r0, [r0, #0x0]
	mov r0, r0, lsl #0x1d
	movs r0, r0, lsr #0x1f
	beq _0208BE44
	ldr r2, _0208C134 ; =FUN_02090190
	add r1, sp, #0x48
	str r2, [r1, r6, lsl #0x3]
	add r0, sp, #0x4c
	mov r1, #0x0
	str r1, [r0, r6, lsl #0x3]
	add r6, r6, #0x1
_0208BE44:
	ldr r0, [sp, #0x4]
	ldr r5, [r9, #0x14]
	ldrh r0, [r0, #0x0]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	moveq r7, #0x0
	cmp r5, #0x0
	beq _0208C0E8
	mov r0, #0x0
	str r0, [sp, #0x1c]
_0208BE6C:
	ldrh r2, [r5, #0x26]
	ldr r0, [r5, #0x0]
	ldrh r1, [r5, #0x24]
	str r0, [sp, #0x14]
	mov r0, r2, lsl #0x8
	bl _s32_div_f
	ldr r4, [sp, #0x1c]
	strb r0, [sp, #0x20]
	cmp r6, #0x0
	ble _0208BEBC
	ldrb r11, [sp, #0x20]
_0208BE98:
	add r3, sp, #0x48
	ldr r3, [r3, r4, lsl #0x3]
	mov r0, r5
	mov r1, r8
	mov r2, r11
	blx r3
	add r4, r4, #0x1
	cmp r4, r6
	blt _0208BE98
_0208BEBC:
	ldr r0, [sp, #0x1c]
	ldr r4, [sp, #0x1c]
	str r0, [sp, #0x70]
	str r0, [sp, #0x6c]
	str r0, [sp, #0x68]
	ldr r0, [sp, #0x4]
	ldrh r0, [r0, #0x0]
	mov r0, r0, lsl #0x1a
	movs r0, r0, lsr #0x1f
	addne r0, r9, #0x28
	addne r3, r5, #0x38
	ldmneia r0, {r0-r2}
	stmneia r3, {r0-r2}
	cmp r7, #0x0
	ble _0208BF24
_0208BEF8:
	ldr r2, [r8, #0x18]
	mov r1, r5
	add r0, r2, r4, lsl #0x3
	ldr r11, [r2, r4, lsl #0x3]
	ldr r0, [r0, #0x4]
	add r2, sp, #0x68
	mov r3, r9
	blx r11
	add r4, r4, #0x1
	cmp r4, r7
	blt _0208BEF8
_0208BF24:
	ldrh r1, [r5, #0x20]
	ldrsh r0, [r5, #0x22]
	add r0, r1, r0
	strh r0, [r5, #0x20]
	ldr r1, [r5, #0x14]
	ldr r0, [sp, #0x8]
	mul r0, r1, r0
	mov r0, r0, asr #0x9
	str r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	ldr r0, [sp, #0x8]
	mul r0, r1, r0
	mov r0, r0, asr #0x9
	str r0, [r5, #0x18]
	ldr r1, [r5, #0x1c]
	ldr r0, [sp, #0x8]
	mul r0, r1, r0
	mov r0, r0, asr #0x9
	str r0, [r5, #0x1c]
	ldr r1, [r5, #0x14]
	ldr r0, [sp, #0x68]
	add r0, r1, r0
	str r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	ldr r0, [sp, #0x6c]
	add r0, r1, r0
	str r0, [r5, #0x18]
	ldr r1, [r5, #0x1c]
	ldr r0, [sp, #0x70]
	add r0, r1, r0
	str r0, [r5, #0x1c]
	ldr r1, [r5, #0x14]
	ldr r0, [r9, #0x34]
	ldr r2, [r5, #0x8]
	add r0, r1, r0
	add r0, r2, r0
	str r0, [r5, #0x8]
	ldr r1, [r5, #0x18]
	ldr r0, [r9, #0x38]
	ldr r2, [r5, #0xc]
	add r0, r1, r0
	add r0, r2, r0
	str r0, [r5, #0xc]
	ldr r1, [r5, #0x1c]
	ldr r0, [r9, #0x3c]
	ldr r2, [r5, #0x10]
	add r0, r1, r0
	add r0, r2, r0
	str r0, [r5, #0x10]
	ldr r0, [r9, #0x20]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	movs r0, r0, lsr #0x1f
	beq _0208C028
	ldr r0, [r10, #0x38]
	ldrh r1, [r5, #0x2e]
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x1a
	bic r1, r1, #0xfc00
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	and r0, r0, #0x3f
	orr r0, r1, r0, lsl #0xa
	strh r0, [r5, #0x2e]
	b _0208C0A8
_0208C028:
	ldr r0, [r10, #0x38]
	ldrh r1, [r5, #0x2e]
	mov r0, r0, lsl #0xe
	mov r0, r0, lsr #0x1a
	bic r1, r1, #0xfc00
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	and r0, r0, #0x3f
	orr r0, r1, r0, lsl #0xa
	strh r0, [r5, #0x2e]
	ldr r1, [r10, #0x38]
	add r0, r10, #0x38
	bic r2, r1, #0x3f000
	mov r1, r1, lsl #0xe
	mov r1, r1, lsr #0x1a
	add r1, r1, #0x1
	and r1, r1, #0x3f
	orr r1, r2, r1, lsl #0xc
	str r1, [r10, #0x38]
	ldr r2, [r10, #0x38]
	mov r1, r2, lsl #0xe
	mov r3, r1, lsr #0x1a
	mov r1, r2, lsl #0x14
	cmp r3, r1, lsr #0x1a
	bls _0208C0A8
	mov r1, r2, lsl #0x1a
	mov r1, r1, lsr #0x1a
	and r1, r1, #0x3f
	ldr r2, [r0, #0x0]
	bic r2, r2, #0x3f000
	orr r1, r2, r1, lsl #0xc
	str r1, [r0, #0x0]
_0208C0A8:
	ldrh r0, [r5, #0x26]
	add r0, r0, #0x1
	strh r0, [r5, #0x26]
	ldrh r1, [r5, #0x26]
	ldrh r0, [r5, #0x24]
	cmp r1, r0
	bls _0208C0DC
	mov r1, r5
	add r0, r9, #0x14
	bl FUN_020909D8
	mov r1, r0
	add r0, r10, #0x1c
	bl FUN_02090AA4
_0208C0DC:
	ldr r5, [sp, #0x14]
	movs r0, r5
	bne _0208BE6C
_0208C0E8:
	ldrh r0, [r9, #0x4c]
	add r0, r0, #0x1
	strh r0, [r9, #0x4c]
	ldr r2, [r9, #0x90]
	cmp r2, #0x0
	addeq sp, sp, #0x74
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	mov r0, r9
	mov r1, #0x1
	blx r2
	add sp, sp, #0x74
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0208C120: .word FUN_02090540
_0208C124: .word FUN_02090374
_0208C128: .word FUN_02090298
_0208C12C: .word FUN_02090234
_0208C130: .word FUN_020901E8
_0208C134: .word FUN_02090190

	arm_func_start FUN_0208C138
FUN_0208C138:
	stmdb sp!, {r4-r6,lr}
	str r1, [r0, #0x20]
	mov r3, #0x0
	str r3, [r0, #0x24]
	ldr r1, [r0, #0x20]
	ldr r5, [r2, #0x0]
	ldr r1, [r1, #0x0]
	ldr r4, _0208C3FC ; =0x00007FFF
	ldr r1, [r1, #0x4]
	ldr ip, _0208C400 ; =0x0007FFFF
	add r1, r5, r1
	str r1, [r0, #0x28]
	ldr r1, [r0, #0x20]
	ldr r6, [r2, #0x4]
	ldr r1, [r1, #0x0]
	mov lr, #0x80000000
	ldr r5, [r1, #0x8]
	mov r1, #0x1000
	add r5, r6, r5
	str r5, [r0, #0x2c]
	ldr r5, [r0, #0x20]
	ldr r6, [r2, #0x8]
	ldr r2, [r5, #0x0]
	ldr r2, [r2, #0xc]
	add r2, r6, r2
	str r2, [r0, #0x30]
	str r3, [r0, #0x40]
	str r3, [r0, #0x44]
	str r3, [r0, #0x48]
	str r3, [r0, #0x3c]
	ldr r2, [r0, #0x3c]
	str r2, [r0, #0x38]
	ldr r2, [r0, #0x38]
	str r2, [r0, #0x34]
	strh r3, [r0, #0x4c]
	strh r3, [r0, #0x4e]
	ldr r2, [r0, #0x20]
	ldr r5, [r2, #0x0]
	ldrh r3, [r5, #0x1c]
	ldrh r2, [r5, #0x1e]
	strh r3, [r0, #0x50]
	strh r2, [r0, #0x52]
	ldrh r2, [r5, #0x20]
	strh r2, [r0, #0x54]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldrh r2, [r2, #0x38]
	strh r2, [r0, #0x56]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x10]
	str r2, [r0, #0x58]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x14]
	str r2, [r0, #0x5c]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x18]
	str r2, [r0, #0x60]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x24]
	str r2, [r0, #0x64]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x28]
	str r2, [r0, #0x68]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x2c]
	str r2, [r0, #0x6c]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldrh r2, [r2, #0x3e]
	strh r2, [r0, #0x70]
	strh r4, [r0, #0x72]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldrb r2, [r2, #0x44]
	strb r2, [r0, #0x80]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldrb r2, [r2, #0x45]
	strb r2, [r0, #0x81]
	ldr r2, [r0, #0x80]
	bic r2, r2, #0x70000
	str r2, [r0, #0x80]
	ldr r2, [r0, #0x80]
	and r2, r2, r12
	str r2, [r0, #0x80]
	str lr, [r0, #0x74]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x48]
	mov r2, r2, lsl #0x6
	mov r2, r2, lsr #0x1e
	mov r2, r1, lsl r2
	strh r2, [r0, #0x78]
	ldr r2, [r0, #0x20]
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x48]
	mov r2, r2, lsl #0x4
	mov r2, r2, lsr #0x1e
	mov r1, r1, lsl r2
	strh r1, [r0, #0x7a]
	ldr r1, [r0, #0x20]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x4c]
	mov r1, r1, lsl #0x1f
	movs r1, r1, lsr #0x1f
	ldrnesh r2, [r0, #0x78]
	mvnne r1, #0x0
	smulbbne r1, r2, r1
	strneh r1, [r0, #0x78]
	ldr r1, [r0, #0x20]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x4c]
	mov r1, r1, lsl #0x1e
	movs r1, r1, lsr #0x1f
	ldrnesh r2, [r0, #0x7a]
	mvnne r1, #0x0
	smulbbne r1, r2, r1
	strneh r1, [r0, #0x7a]
	ldr r2, [r0, #0x20]
	ldr r1, [r2, #0x0]
	ldr r1, [r1, #0x0]
	mov r1, r1, lsl #0xf
	movs r1, r1, lsr #0x1f
	beq _0208C3C0
	ldr r1, [r2, #0x14]
	mov r2, #0x1000
	ldr r1, [r1, #0x10]
	mov r1, r1, lsl #0x1e
	mov r1, r1, lsr #0x1e
	mov r1, r2, lsl r1
	strh r1, [r0, #0x7c]
	ldr r1, [r0, #0x20]
	ldr r1, [r1, #0x14]
	ldr r1, [r1, #0x10]
	mov r1, r1, lsl #0x1c
	mov r1, r1, lsr #0x1e
	mov r1, r2, lsl r1
	strh r1, [r0, #0x7e]
	ldr r1, [r0, #0x20]
	ldr r1, [r1, #0x14]
	ldr r1, [r1, #0x10]
	mov r1, r1, lsl #0x1b
	movs r1, r1, lsr #0x1f
	ldrnesh r2, [r0, #0x7c]
	mvnne r1, #0x0
	smulbbne r1, r2, r1
	strneh r1, [r0, #0x7c]
	ldr r1, [r0, #0x20]
	ldr r1, [r1, #0x14]
	ldr r1, [r1, #0x10]
	mov r1, r1, lsl #0x1a
	movs r1, r1, lsr #0x1f
	ldrnesh r2, [r0, #0x7e]
	mvnne r1, #0x0
	smulbbne r1, r2, r1
	strneh r1, [r0, #0x7e]
_0208C3C0:
	mov r2, #0x0
	str r2, [r0, #0x4]
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	str r2, [r0, #0x14]
	ldr r1, [r0, #0x14]
	str r1, [r0, #0x8]
	str r2, [r0, #0x18]
	ldr r1, [r0, #0x18]
	str r1, [r0, #0xc]
	str r2, [r0, #0x90]
	str r2, [r0, #0x94]
	str r2, [r0, #0x98]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0208C3FC: .word 0x00007FFF
_0208C400: .word 0x0007FFFF

	arm_func_start FUN_0208C404
FUN_0208C404: ; 0x0208C404
	bx lr

	arm_func_start FUN_0208C408
FUN_0208C408:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r7, [r0, #0xc]
	ldr r3, _0208C4E0 ; =0x040004A8
	str r7, [sp, #0x0]
	ldr r1, [r0, #0x4]
	mov r2, r7, lsl #0x1c
	mov lr, r2, lsr #0x1c
	mov r1, r1, lsr #0x3
	orr r12, r1, lr, lsl #0x1a
	mov r4, r7, lsl #0x18
	mov r5, r7, lsl #0x14
	mov r2, r7, lsl #0xf
	mov r4, r4, lsr #0x1c
	orr r12, r12, #0x40000000
	mov r6, r7, lsl #0x12
	orr r12, r12, r4, lsl #0x14
	mov r5, r5, lsr #0x1c
	mov r1, r7, lsl #0x10
	orr r12, r12, r5, lsl #0x17
	mov r4, r6, lsr #0x1e
	mov r5, r1, lsr #0x1e
	orr r1, r12, r4, lsl #0x10
	mov r2, r2, lsr #0x1f
	orr r1, r1, r5, lsl #0x12
	orr r1, r1, r2, lsl #0x1d
	str r1, [r3, #0x0]
	cmp lr, #0x2
	moveq r1, #0x1
	movne r1, #0x0
	ldr r2, [r0, #0x8]
	rsb r1, r1, #0x4
	mov r2, r2, lsr r1
	ldr r1, _0208C4E4 ; =0x040004AC
	ldr ip, _0208C4E8 ; =0x04000440
	str r2, [r1, #0x0]
	mov r2, #0x3
	ldr r1, _0208C4EC ; =0x04000454
	str r2, [r12, #0x0]
	mov r3, #0x0
	str r3, [r1, #0x0]
	ldrh r1, [r0, #0x10]
	ldrh r2, [r0, #0x12]
	ldr r0, _0208C4F0 ; =0x0400046C
	mov r1, r1, lsl #0xc
	str r1, [r0, #0x0]
	mov r1, r2, lsl #0xc
	str r1, [r0, #0x0]
	str r3, [r0, #0x0]
	mov r0, #0x1
	str r0, [r12, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0208C4E0: .word 0x040004A8
_0208C4E4: .word 0x040004AC
_0208C4E8: .word 0x04000440
_0208C4EC: .word 0x04000454
_0208C4F0: .word 0x0400046C

	arm_func_start FUN_0208C4F4
FUN_0208C4F4: ; 0x0208C4F4
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0xf0
	mov r4, r1
	ldrh r2, [r4, #0x2e]
	mov r5, r0
	ldr r0, [r5, #0x3c]
	mov r1, r2, lsl #0x16
	mov r3, r2, lsl #0x1b
	mov r1, r1, lsr #0x1b
	mov r3, r3, lsr #0x1b
	add r1, r1, #0x1
	mul r6, r3, r1
	mov r1, r2, lsl #0x10
	movs r2, r6, asr #0x5
	mov r1, r1, lsr #0x1a
	orr r0, r0, #0xc0
	orr r1, r0, r1, lsl #0x18
	ldr r0, _0208C950 ; =0x040004A4
	orr r1, r1, r2, lsl #0x10
	str r1, [r0, #0x0]
	addeq sp, sp, #0xf0
	ldr r0, [r0, #0x0]
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r0, [r5, #0x40]
	ldrh r1, [r4, #0x20]
	ldr r0, [r0, #0x20]
	ldr r6, _0208C954 ; =0x020FFA38
	ldr r0, [r0, #0x14]
	mov r1, r1, asr #0x4
	ldrh r0, [r0, #0x0]
	mov r2, r1, lsl #0x1
	add r1, r2, #0x1
	mov r7, r2, lsl #0x1
	mov r1, r1, lsl #0x1
	mov r0, r0, lsl #0x15
	mov r3, r0, lsr #0x1e
	ldr r2, _0208C958 ; =0x02106160
	ldrsh r0, [r6, r7]
	ldr r3, [r2, r3, lsl #0x2]
	ldrsh r1, [r6, r1]
	add r2, sp, #0x30
	blx r3
	add r0, sp, #0xc0
	bl MTX_Identity43_
	ldr r0, [r5, #0x40]
	ldr r0, [r0, #0x20]
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0x10]
	mov r0, r0, lsl #0x19
	movs r0, r0, lsr #0x1f
	bne _0208C5D4
	add r1, sp, #0x90
	add r0, r4, #0x14
	bl VEC_Normalize
	b _0208C604
_0208C5D4:
	add r1, sp, #0x90
	add r0, r4, #0x8
	bl VEC_Normalize
	ldr r2, [sp, #0x90]
	ldr r1, [sp, #0x94]
	ldr r0, [sp, #0x98]
	rsb r2, r2, #0x0
	rsb r1, r1, #0x0
	rsb r0, r0, #0x0
	str r2, [sp, #0x90]
	str r1, [sp, #0x94]
	str r0, [sp, #0x98]
_0208C604:
	mov r3, #0x0
	mov r2, #0x1000
	add r0, sp, #0x90
	add r1, sp, #0xb4
	str r3, [sp, #0xb4]
	str r2, [sp, #0xb8]
	str r3, [sp, #0xbc]
	bl VEC_DotProduct
	ldr r1, _0208C95C ; =0x00000CCD
	cmp r0, r1
	bgt _0208C63C
	ldr r1, _0208C960 ; =0xFFFFF333
	cmp r0, r1
	bge _0208C650
_0208C63C:
	mov r0, #0x0
	mov r1, #0x1000
	str r1, [sp, #0xb4]
	str r0, [sp, #0xb8]
	str r0, [sp, #0xbc]
_0208C650:
	add r0, sp, #0x90
	add r1, sp, #0xb4
	add r2, sp, #0x9c
	bl VEC_CrossProduct
	add r0, sp, #0x90
	add r1, sp, #0x9c
	add r2, sp, #0xa8
	bl VEC_CrossProduct
	ldr r7, [sp, #0x9c]
	ldr r6, [sp, #0xa0]
	ldr r3, [sp, #0xa4]
	ldr r0, [sp, #0x90]
	ldr r1, [sp, #0x94]
	ldr r2, [sp, #0x98]
	str r7, [sp, #0xc0]
	ldr r7, [sp, #0xa8]
	str r6, [sp, #0xc4]
	ldr r6, [sp, #0xac]
	str r3, [sp, #0xc8]
	ldr r3, [sp, #0xb0]
	str r0, [sp, #0xcc]
	str r1, [sp, #0xd0]
	add r0, sp, #0x30
	str r2, [sp, #0xd4]
	add r1, sp, #0xc0
	mov r2, r0
	str r7, [sp, #0xd8]
	str r6, [sp, #0xdc]
	str r3, [sp, #0xe0]
	bl MTX_Concat43
	ldr r0, [r5, #0x40]
	ldr r2, [r4, #0x30]
	ldr r0, [r0, #0x20]
	mov r12, #0x800
	ldr r0, [r0, #0x0]
	mov r3, r2, asr #0x1f
	ldrsh r1, [r0, #0x30]
	ldr r0, [r0, #0x48]
	mov lr, #0x0
	smull r6, r1, r2, r1
	adds r7, r6, r12
	adc r6, r1, #0x0
	mov r0, r0, lsl #0x1
	mov r1, r7, lsr #0xc
	orr r1, r1, r6, lsl #0x14
	movs r0, r0, lsr #0x1d
	beq _0208C720
	cmp r0, #0x1
	beq _0208C75C
	cmp r0, #0x2
	beq _0208C778
	b _0208C79C
_0208C720:
	ldrsh r0, [r4, #0x34]
	mov r8, r0, asr #0x1f
	umull r7, r6, r2, r0
	mla r6, r2, r8, r6
	smull r8, r2, r1, r0
	adds r1, r8, r12
	adc r8, r2, lr
	adds r2, r7, r12
	mla r6, r3, r0, r6
	mov r1, r1, lsr #0xc
	adc r0, r6, lr
	mov r2, r2, lsr #0xc
	orr r1, r1, r8, lsl #0x14
	orr r2, r2, r0, lsl #0x14
	b _0208C79C
_0208C75C:
	ldrsh r0, [r4, #0x34]
	smull r3, r0, r1, r0
	adds r1, r3, r12
	adc r0, r0, lr
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	b _0208C79C
_0208C778:
	ldrsh r6, [r4, #0x34]
	mov r0, r6, asr #0x1f
	umull r8, r7, r2, r6
	mla r7, r2, r0, r7
	adds r2, r8, r12
	mla r7, r3, r6, r7
	adc r0, r7, lr
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
_0208C79C:
	add r0, sp, #0x60
	mov r3, r2
	blx MTX_Scale43_
	add r0, sp, #0x30
	add r1, sp, #0x60
	add r2, sp, #0x0
	bl MTX_Concat43
	ldr r0, [r5, #0x40]
	ldr r0, [r0, #0x20]
	ldr r3, [r0, #0x0]
	ldr r0, [r3, #0x0]
	mov r0, r0, lsl #0x8
	movs r0, r0, lsr #0x1f
	bne _0208C818
	ldr r1, [r4, #0x8]
	ldr r0, [r4, #0x38]
	add r0, r1, r0
	str r0, [sp, #0x24]
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x3c]
	add r0, r1, r0
	str r0, [sp, #0x28]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x40]
	add r0, r1, r0
	str r0, [sp, #0x2c]
	ldr r0, [r5, #0x44]
	bl G3_LoadMtx43
_0208C80C: ; 0x0208C80C
	add r0, sp, #0x0
	bl G3_MultMtx43
	b _0208C8BC
_0208C818:
	ldr r2, [r4, #0x8]
	ldr r1, [r4, #0x38]
	ldr r0, [r3, #0x4]
	add r1, r2, r1
	sub r0, r1, r0
	str r0, [sp, #0x24]
	ldr r0, [r5, #0x40]
	ldr r2, [r4, #0xc]
	ldr r0, [r0, #0x20]
	ldr r1, [r4, #0x3c]
	ldr r0, [r0, #0x0]
	add r2, r2, r1
	ldr r1, [r0, #0x8]
	ldr r0, _0208C964 ; =0x04000454
	sub r1, r2, r1
	str r1, [sp, #0x28]
	ldr r1, [r5, #0x40]
	ldr r3, [r4, #0x10]
	ldr r1, [r1, #0x20]
	ldr r2, [r4, #0x40]
	ldr r1, [r1, #0x0]
	add r3, r3, r2
	ldr r2, [r1, #0xc]
	mov r1, #0x0
	sub r2, r3, r2
	str r2, [sp, #0x2c]
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x40]
	ldr r0, _0208C968 ; =0x04000470
	ldr r1, [r1, #0x20]
	ldr r1, [r1, #0x0]
	ldr r3, [r1, #0xc]
	ldr r2, [r1, #0x8]
	ldr r1, [r1, #0x4]
	str r1, [r0, #0x0]
	str r2, [r0, #0x0]
	str r3, [r0, #0x0]
	ldr r0, [r5, #0x44]
	bl G3_MultMtx43
_0208C8B4: ; 0x0208C8B4
	add r0, sp, #0x0
	bl G3_MultMtx43
_0208C8BC:
	ldr r0, [r5, #0x40]
	ldrh r4, [r4, #0x36]
	ldrh r12, [r0, #0x72]
	mov r2, #0x0
	and r1, r4, #0x1f
	and r0, r12, #0x1f
	mul r3, r1, r0
	and r1, r4, #0x3e0
	and r0, r12, #0x3e0
	mul r0, r1, r0
	and r4, r4, #0x7c00
	and r1, r12, #0x7c00
	mul r12, r4, r1
	mov r1, r3, asr #0x5
	mov r0, r0, asr #0xf
	mov r3, r12, asr #0x19
	orr r0, r1, r0, lsl #0x5
	orr r0, r0, r3, lsl #0xa
	mov r0, r0, lsl #0x10
	ldr r1, _0208C96C ; =0x04000480
	mov r0, r0, lsr #0x10
	str r0, [r1, #0x0]
	ldr r5, [r5, #0x40]
	ldr r4, _0208C970 ; =0x02106158
	ldr r1, [r5, #0x20]
	ldrsh r0, [r5, #0x7c]
	ldr r3, [r1, #0x14]
	ldrsh r1, [r5, #0x7e]
	ldrh r5, [r3, #0x0]
	mov r3, r2
	mov r5, r5, lsl #0x14
	mov r5, r5, lsr #0x1f
	ldr r4, [r4, r5, lsl #0x2]
	blx r4
	add sp, sp, #0xf0
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0208C950: .word 0x040004A4
_0208C954: .word 0x020FFA38
_0208C958: .word 0x02106160
_0208C95C: .word 0x00000CCD
_0208C960: .word 0xFFFFF333
_0208C964: .word 0x04000454
_0208C968: .word 0x04000470
_0208C96C: .word 0x04000480
_0208C970: .word 0x02106158

	arm_func_start FUN_0208C974
FUN_0208C974: ; 0x0208C974
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0xf0
	mov r4, r1
	ldrh r2, [r4, #0x2e]
	mov r5, r0
	ldr r0, [r5, #0x3c]
	mov r1, r2, lsl #0x16
	mov r3, r2, lsl #0x1b
	mov r1, r1, lsr #0x1b
	mov r3, r3, lsr #0x1b
	add r1, r1, #0x1
	mul r6, r3, r1
	mov r1, r2, lsl #0x10
	movs r2, r6, asr #0x5
	mov r1, r1, lsr #0x1a
	orr r0, r0, #0xc0
	orr r1, r0, r1, lsl #0x18
	ldr r0, _0208CDCC ; =0x040004A4
	orr r1, r1, r2, lsl #0x10
	str r1, [r0, #0x0]
	addeq sp, sp, #0xf0
	ldr r0, [r0, #0x0]
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r0, [r5, #0x40]
	ldrh r1, [r4, #0x20]
	ldr r0, [r0, #0x20]
	ldr r6, _0208CDD0 ; =0x020FFA38
	ldr r0, [r0, #0x0]
	mov r1, r1, asr #0x4
	mov r2, r1, lsl #0x1
	ldr r0, [r0, #0x0]
	add r1, r2, #0x1
	mov r7, r2, lsl #0x1
	mov r1, r1, lsl #0x1
	mov r0, r0, lsl #0xd
	mov r3, r0, lsr #0x1e
	ldr r2, _0208CDD4 ; =0x02106160
	ldrsh r0, [r6, r7]
	ldr r3, [r2, r3, lsl #0x2]
	ldrsh r1, [r6, r1]
	add r2, sp, #0x30
	blx r3
	add r0, sp, #0xc0
	bl MTX_Identity43_
	ldr r0, [r5, #0x40]
	ldr r0, [r0, #0x20]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x48]
	movs r0, r0, lsr #0x1f
	bne _0208CA50
	add r1, sp, #0x90
	add r0, r4, #0x14
	bl VEC_Normalize
	b _0208CA80
_0208CA50:
	add r1, sp, #0x90
	add r0, r4, #0x8
	bl VEC_Normalize
	ldr r2, [sp, #0x90]
	ldr r1, [sp, #0x94]
	ldr r0, [sp, #0x98]
	rsb r2, r2, #0x0
	rsb r1, r1, #0x0
	rsb r0, r0, #0x0
	str r2, [sp, #0x90]
	str r1, [sp, #0x94]
	str r0, [sp, #0x98]
_0208CA80:
	mov r3, #0x0
	mov r2, #0x1000
	add r0, sp, #0x90
	add r1, sp, #0xb4
	str r3, [sp, #0xb4]
	str r2, [sp, #0xb8]
	str r3, [sp, #0xbc]
	bl VEC_DotProduct
	ldr r1, _0208CDD8 ; =0x00000CCD
	cmp r0, r1
	bgt _0208CAB8
	ldr r1, _0208CDDC ; =0xFFFFF333
	cmp r0, r1
	bge _0208CACC
_0208CAB8:
	mov r0, #0x0
	mov r1, #0x1000
	str r1, [sp, #0xb4]
	str r0, [sp, #0xb8]
	str r0, [sp, #0xbc]
_0208CACC:
	add r0, sp, #0x90
	add r1, sp, #0xb4
	add r2, sp, #0x9c
	bl VEC_CrossProduct
	add r0, sp, #0x90
	add r1, sp, #0x9c
	add r2, sp, #0xa8
	bl VEC_CrossProduct
	ldr r7, [sp, #0x9c]
	ldr r6, [sp, #0xa0]
	ldr r3, [sp, #0xa4]
	ldr r0, [sp, #0x90]
	ldr r1, [sp, #0x94]
	ldr r2, [sp, #0x98]
	str r7, [sp, #0xc0]
	ldr r7, [sp, #0xa8]
	str r6, [sp, #0xc4]
	ldr r6, [sp, #0xac]
	str r3, [sp, #0xc8]
	ldr r3, [sp, #0xb0]
	str r0, [sp, #0xcc]
	str r1, [sp, #0xd0]
	add r0, sp, #0x30
	str r2, [sp, #0xd4]
	add r1, sp, #0xc0
	mov r2, r0
	str r7, [sp, #0xd8]
	str r6, [sp, #0xdc]
	str r3, [sp, #0xe0]
	bl MTX_Concat43
	ldr r0, [r5, #0x40]
	ldr r2, [r4, #0x30]
	ldr r0, [r0, #0x20]
	mov r12, #0x800
	ldr r0, [r0, #0x0]
	mov r3, r2, asr #0x1f
	ldrsh r1, [r0, #0x30]
	ldr r0, [r0, #0x48]
	mov lr, #0x0
	smull r6, r1, r2, r1
	adds r7, r6, r12
	adc r6, r1, #0x0
	mov r0, r0, lsl #0x1
	mov r1, r7, lsr #0xc
	orr r1, r1, r6, lsl #0x14
	movs r0, r0, lsr #0x1d
	beq _0208CB9C
	cmp r0, #0x1
	beq _0208CBD8
	cmp r0, #0x2
	beq _0208CBF4
	b _0208CC18
_0208CB9C:
	ldrsh r0, [r4, #0x34]
	mov r8, r0, asr #0x1f
	umull r7, r6, r2, r0
	mla r6, r2, r8, r6
	smull r8, r2, r1, r0
	adds r1, r8, r12
	adc r8, r2, lr
	adds r2, r7, r12
	mla r6, r3, r0, r6
	mov r1, r1, lsr #0xc
	adc r0, r6, lr
	mov r2, r2, lsr #0xc
	orr r1, r1, r8, lsl #0x14
	orr r2, r2, r0, lsl #0x14
	b _0208CC18
_0208CBD8:
	ldrsh r0, [r4, #0x34]
	smull r3, r0, r1, r0
	adds r1, r3, r12
	adc r0, r0, lr
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	b _0208CC18
_0208CBF4:
	ldrsh r6, [r4, #0x34]
	mov r0, r6, asr #0x1f
	umull r8, r7, r2, r6
	mla r7, r2, r0, r7
	adds r2, r8, r12
	mla r7, r3, r6, r7
	adc r0, r7, lr
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
_0208CC18:
	add r0, sp, #0x60
	mov r3, r2
	blx MTX_Scale43_
	add r0, sp, #0x60
	add r1, sp, #0x30
	add r2, sp, #0x0
	bl MTX_Concat43
	ldr r0, [r5, #0x40]
	ldr r0, [r0, #0x20]
	ldr r3, [r0, #0x0]
	ldr r0, [r3, #0x0]
	mov r0, r0, lsl #0x8
	movs r0, r0, lsr #0x1f
	bne _0208CC94
	ldr r1, [r4, #0x8]
	ldr r0, [r4, #0x38]
	add r0, r1, r0
	str r0, [sp, #0x24]
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x3c]
	add r0, r1, r0
	str r0, [sp, #0x28]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x40]
	add r0, r1, r0
	str r0, [sp, #0x2c]
	ldr r0, [r5, #0x44]
	bl G3_LoadMtx43
_0208CC88: ; 0x0208CC88
	add r0, sp, #0x0
	bl G3_MultMtx43
	b _0208CD38
_0208CC94:
	ldr r2, [r4, #0x8]
	ldr r1, [r4, #0x38]
	ldr r0, [r3, #0x4]
	add r1, r2, r1
	sub r0, r1, r0
	str r0, [sp, #0x24]
	ldr r0, [r5, #0x40]
	ldr r2, [r4, #0xc]
	ldr r0, [r0, #0x20]
	ldr r1, [r4, #0x3c]
	ldr r0, [r0, #0x0]
	add r2, r2, r1
	ldr r1, [r0, #0x8]
	ldr r0, _0208CDE0 ; =0x04000454
	sub r1, r2, r1
	str r1, [sp, #0x28]
	ldr r1, [r5, #0x40]
	ldr r3, [r4, #0x10]
	ldr r1, [r1, #0x20]
	ldr r2, [r4, #0x40]
	ldr r1, [r1, #0x0]
	add r3, r3, r2
	ldr r2, [r1, #0xc]
	mov r1, #0x0
	sub r2, r3, r2
	str r2, [sp, #0x2c]
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x40]
	ldr r0, _0208CDE4 ; =0x04000470
	ldr r1, [r1, #0x20]
	ldr r1, [r1, #0x0]
	ldr r3, [r1, #0xc]
	ldr r2, [r1, #0x8]
	ldr r1, [r1, #0x4]
	str r1, [r0, #0x0]
	str r2, [r0, #0x0]
	str r3, [r0, #0x0]
	ldr r0, [r5, #0x44]
	bl G3_MultMtx43
_0208CD30: ; 0x0208CD30
	add r0, sp, #0x0
	bl G3_MultMtx43
_0208CD38:
	ldr r0, [r5, #0x40]
	ldrh r4, [r4, #0x36]
	ldrh r12, [r0, #0x72]
	ldr r1, _0208CDE8 ; =0x04000480
	and r2, r4, #0x1f
	and r0, r12, #0x1f
	mul r3, r2, r0
	and r2, r4, #0x3e0
	and r0, r12, #0x3e0
	mul r0, r2, r0
	and r4, r4, #0x7c00
	and r2, r12, #0x7c00
	mul r12, r4, r2
	mov r2, r3, asr #0x5
	mov r0, r0, asr #0xf
	mov r3, r12, asr #0x19
	orr r0, r2, r0, lsl #0x5
	orr r0, r0, r3, lsl #0xa
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r0, [r1, #0x0]
	ldr r2, [r5, #0x40]
	ldr r4, _0208CDEC ; =0x02106158
	ldr r1, [r2, #0x20]
	ldrsh r0, [r2, #0x78]
	ldr r12, [r1, #0x0]
	ldrsh r1, [r2, #0x7a]
	ldr r3, [r12, #0x0]
	ldrsh r2, [r12, #0x50]
	mov r3, r3, lsl #0xc
	mov r5, r3, lsr #0x1f
	ldrsh r3, [r12, #0x52]
	ldr r4, [r4, r5, lsl #0x2]
	blx r4
	add sp, sp, #0xf0
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0208CDCC: .word 0x040004A4
_0208CDD0: .word 0x020FFA38
_0208CDD4: .word 0x02106160
_0208CDD8: .word 0x00000CCD
_0208CDDC: .word 0xFFFFF333
_0208CDE0: .word 0x04000454
_0208CDE4: .word 0x04000470
_0208CDE8: .word 0x04000480
_0208CDEC: .word 0x02106158

	arm_func_start FUN_0208CDF0
FUN_0208CDF0: ; 0x0208CDF0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x90
	mov r4, r1
	ldrh r2, [r4, #0x2e]
	mov r5, r0
	ldr r0, [r5, #0x3c]
	mov r1, r2, lsl #0x16
	mov r3, r2, lsl #0x1b
	mov r1, r1, lsr #0x1b
	mov r3, r3, lsr #0x1b
	add r1, r1, #0x1
	mul r6, r3, r1
	mov r1, r2, lsl #0x10
	movs r2, r6, asr #0x5
	mov r1, r1, lsr #0x1a
	orr r0, r0, #0xc0
	orr r1, r0, r1, lsl #0x18
	ldr r0, _0208D124 ; =0x040004A4
	orr r1, r1, r2, lsl #0x10
	str r1, [r0, #0x0]
	addeq sp, sp, #0x90
	ldr r0, [r0, #0x0]
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r0, [r5, #0x40]
	ldrh r1, [r4, #0x20]
	ldr r0, [r0, #0x20]
	ldr r6, _0208D128 ; =0x020FFA38
	ldr r0, [r0, #0x14]
	mov r1, r1, asr #0x4
	ldrh r0, [r0, #0x0]
	mov r2, r1, lsl #0x1
	add r1, r2, #0x1
	mov r7, r2, lsl #0x1
	mov r1, r1, lsl #0x1
	mov r0, r0, lsl #0x15
	mov r3, r0, lsr #0x1e
	ldr r2, _0208D12C ; =0x02106160
	ldrsh r0, [r6, r7]
	ldr r3, [r2, r3, lsl #0x2]
	ldrsh r1, [r6, r1]
	add r2, sp, #0x30
	blx r3
	ldr r0, [r5, #0x40]
	ldr r2, [r4, #0x30]
	ldr r0, [r0, #0x20]
	mov r12, #0x800
	ldr r0, [r0, #0x0]
	mov r3, r2, asr #0x1f
	ldrsh r1, [r0, #0x30]
	ldr r0, [r0, #0x48]
	mov lr, #0x0
	smull r6, r1, r2, r1
	adds r7, r6, r12
	adc r6, r1, #0x0
	mov r1, r7, lsr #0xc
	mov r0, r0, lsl #0x1
	orr r1, r1, r6, lsl #0x14
	movs r0, r0, lsr #0x1d
	beq _0208CEF4
	cmp r0, #0x1
	beq _0208CF30
	cmp r0, #0x2
	beq _0208CF4C
	b _0208CF70
_0208CEF4:
	ldrsh r0, [r4, #0x34]
	mov r8, r0, asr #0x1f
	umull r7, r6, r2, r0
	mla r6, r2, r8, r6
	smull r8, r2, r1, r0
	adds r1, r8, r12
	adc r8, r2, lr
	adds r2, r7, r12
	mla r6, r3, r0, r6
	mov r1, r1, lsr #0xc
	adc r0, r6, lr
	mov r2, r2, lsr #0xc
	orr r1, r1, r8, lsl #0x14
	orr r2, r2, r0, lsl #0x14
	b _0208CF70
_0208CF30:
	ldrsh r0, [r4, #0x34]
	smull r3, r0, r1, r0
	adds r1, r3, r12
	adc r0, r0, lr
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	b _0208CF70
_0208CF4C:
	ldrsh r6, [r4, #0x34]
	mov r0, r6, asr #0x1f
	umull r8, r7, r2, r6
	mla r7, r2, r0, r7
	adds r2, r8, r12
	mla r7, r3, r6, r7
	adc r0, r7, lr
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
_0208CF70:
	add r0, sp, #0x60
	mov r3, r2
	blx MTX_Scale43_
	add r0, sp, #0x30
	add r1, sp, #0x60
	add r2, sp, #0x0
	bl MTX_Concat43
	ldr r0, [r5, #0x40]
	ldr r0, [r0, #0x20]
	ldr r3, [r0, #0x0]
	ldr r0, [r3, #0x0]
	mov r0, r0, lsl #0x8
	movs r0, r0, lsr #0x1f
	bne _0208CFEC
	ldr r1, [r4, #0x8]
	ldr r0, [r4, #0x38]
	add r0, r1, r0
	str r0, [sp, #0x24]
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x3c]
	add r0, r1, r0
	str r0, [sp, #0x28]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x40]
	add r0, r1, r0
	str r0, [sp, #0x2c]
	ldr r0, [r5, #0x44]
	bl G3_LoadMtx43
_0208CFE0: ; 0x0208CFE0
	add r0, sp, #0x0
	bl G3_MultMtx43
	b _0208D090
_0208CFEC:
	ldr r2, [r4, #0x8]
	ldr r1, [r4, #0x38]
	ldr r0, [r3, #0x4]
	add r1, r2, r1
	sub r0, r1, r0
	str r0, [sp, #0x24]
	ldr r0, [r5, #0x40]
	ldr r2, [r4, #0xc]
	ldr r0, [r0, #0x20]
	ldr r1, [r4, #0x3c]
	ldr r0, [r0, #0x0]
	add r2, r2, r1
	ldr r1, [r0, #0x8]
	ldr r0, _0208D130 ; =0x04000454
	sub r1, r2, r1
	str r1, [sp, #0x28]
	ldr r1, [r5, #0x40]
	ldr r3, [r4, #0x10]
	ldr r1, [r1, #0x20]
	ldr r2, [r4, #0x40]
	ldr r1, [r1, #0x0]
	add r3, r3, r2
	ldr r2, [r1, #0xc]
	mov r1, #0x0
	sub r2, r3, r2
	str r2, [sp, #0x2c]
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x40]
	ldr r0, _0208D134 ; =0x04000470
	ldr r1, [r1, #0x20]
	ldr r1, [r1, #0x0]
	ldr r3, [r1, #0xc]
	ldr r2, [r1, #0x8]
	ldr r1, [r1, #0x4]
	str r1, [r0, #0x0]
	str r2, [r0, #0x0]
	str r3, [r0, #0x0]
	ldr r0, [r5, #0x44]
	bl G3_MultMtx43
_0208D088: ; 0x0208D088
	add r0, sp, #0x0
	bl G3_MultMtx43
_0208D090:
	ldr r0, [r5, #0x40]
	ldrh r4, [r4, #0x36]
	ldrh r12, [r0, #0x72]
	mov r2, #0x0
	and r1, r4, #0x1f
	and r0, r12, #0x1f
	mul r3, r1, r0
	and r1, r4, #0x3e0
	and r0, r12, #0x3e0
	mul r0, r1, r0
	and r4, r4, #0x7c00
	and r1, r12, #0x7c00
	mul r12, r4, r1
	mov r1, r3, asr #0x5
	mov r0, r0, asr #0xf
	mov r3, r12, asr #0x19
	orr r0, r1, r0, lsl #0x5
	orr r0, r0, r3, lsl #0xa
	mov r0, r0, lsl #0x10
	ldr r1, _0208D138 ; =0x04000480
	mov r0, r0, lsr #0x10
	str r0, [r1, #0x0]
	ldr r5, [r5, #0x40]
	ldr r4, _0208D13C ; =0x02106158
	ldr r1, [r5, #0x20]
	ldrsh r0, [r5, #0x7c]
	ldr r3, [r1, #0x14]
	ldrsh r1, [r5, #0x7e]
	ldrh r5, [r3, #0x0]
	mov r3, r2
	mov r5, r5, lsl #0x14
	mov r5, r5, lsr #0x1f
	ldr r4, [r4, r5, lsl #0x2]
	blx r4
	add sp, sp, #0x90
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0208D124: .word 0x040004A4
_0208D128: .word 0x020FFA38
_0208D12C: .word 0x02106160
_0208D130: .word 0x04000454
_0208D134: .word 0x04000470
_0208D138: .word 0x04000480
_0208D13C: .word 0x02106158

	arm_func_start FUN_0208D140
FUN_0208D140: ; 0x0208D140
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x90
	mov r4, r1
	ldrh r2, [r4, #0x2e]
	mov r5, r0
	ldr r0, [r5, #0x3c]
	mov r1, r2, lsl #0x16
	mov r3, r2, lsl #0x1b
	mov r1, r1, lsr #0x1b
	mov r3, r3, lsr #0x1b
	add r1, r1, #0x1
	mul r6, r3, r1
	mov r1, r2, lsl #0x10
	movs r2, r6, asr #0x5
	mov r1, r1, lsr #0x1a
	orr r0, r0, #0xc0
	orr r1, r0, r1, lsl #0x18
	ldr r0, _0208D474 ; =0x040004A4
	orr r1, r1, r2, lsl #0x10
	str r1, [r0, #0x0]
	addeq sp, sp, #0x90
	ldr r0, [r0, #0x0]
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r0, [r5, #0x40]
	ldrh r1, [r4, #0x20]
	ldr r0, [r0, #0x20]
	ldr r6, _0208D478 ; =0x020FFA38
	ldr r0, [r0, #0x0]
	mov r1, r1, asr #0x4
	mov r2, r1, lsl #0x1
	ldr r0, [r0, #0x0]
	add r1, r2, #0x1
	mov r7, r2, lsl #0x1
	mov r1, r1, lsl #0x1
	mov r0, r0, lsl #0xd
	mov r3, r0, lsr #0x1e
	ldr r2, _0208D47C ; =0x02106160
	ldrsh r0, [r6, r7]
	ldr r3, [r2, r3, lsl #0x2]
	ldrsh r1, [r6, r1]
	add r2, sp, #0x30
	blx r3
	ldr r0, [r5, #0x40]
	ldr r2, [r4, #0x30]
	ldr r0, [r0, #0x20]
	mov r12, #0x800
	ldr r0, [r0, #0x0]
	mov r3, r2, asr #0x1f
	ldrsh r1, [r0, #0x30]
	ldr r0, [r0, #0x48]
	mov lr, #0x0
	smull r6, r1, r2, r1
	adds r7, r6, r12
	adc r6, r1, #0x0
	mov r1, r7, lsr #0xc
	mov r0, r0, lsl #0x1
	orr r1, r1, r6, lsl #0x14
	movs r0, r0, lsr #0x1d
	beq _0208D244
	cmp r0, #0x1
	beq _0208D280
	cmp r0, #0x2
	beq _0208D29C
	b _0208D2C0
_0208D244:
	ldrsh r0, [r4, #0x34]
	mov r8, r0, asr #0x1f
	umull r7, r6, r2, r0
	mla r6, r2, r8, r6
	smull r8, r2, r1, r0
	adds r1, r8, r12
	adc r8, r2, lr
	adds r2, r7, r12
	mla r6, r3, r0, r6
	mov r1, r1, lsr #0xc
	adc r0, r6, lr
	mov r2, r2, lsr #0xc
	orr r1, r1, r8, lsl #0x14
	orr r2, r2, r0, lsl #0x14
	b _0208D2C0
_0208D280:
	ldrsh r0, [r4, #0x34]
	smull r3, r0, r1, r0
	adds r1, r3, r12
	adc r0, r0, lr
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	b _0208D2C0
_0208D29C:
	ldrsh r6, [r4, #0x34]
	mov r0, r6, asr #0x1f
	umull r8, r7, r2, r6
	mla r7, r2, r0, r7
	adds r2, r8, r12
	mla r7, r3, r6, r7
	adc r0, r7, lr
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
_0208D2C0:
	add r0, sp, #0x60
	mov r3, r2
	blx MTX_Scale43_
	add r0, sp, #0x60
	add r1, sp, #0x30
	add r2, sp, #0x0
	bl MTX_Concat43
	ldr r0, [r5, #0x40]
	ldr r0, [r0, #0x20]
	ldr r3, [r0, #0x0]
	ldr r0, [r3, #0x0]
	mov r0, r0, lsl #0x8
	movs r0, r0, lsr #0x1f
	bne _0208D33C
	ldr r1, [r4, #0x8]
	ldr r0, [r4, #0x38]
	add r0, r1, r0
	str r0, [sp, #0x24]
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x3c]
	add r0, r1, r0
	str r0, [sp, #0x28]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x40]
	add r0, r1, r0
	str r0, [sp, #0x2c]
	ldr r0, [r5, #0x44]
	bl G3_LoadMtx43
_0208D330: ; 0x0208D330
	add r0, sp, #0x0
	bl G3_MultMtx43
	b _0208D3E0
_0208D33C:
	ldr r2, [r4, #0x8]
	ldr r1, [r4, #0x38]
	ldr r0, [r3, #0x4]
	add r1, r2, r1
	sub r0, r1, r0
	str r0, [sp, #0x24]
	ldr r0, [r5, #0x40]
	ldr r2, [r4, #0xc]
	ldr r0, [r0, #0x20]
	ldr r1, [r4, #0x3c]
	ldr r0, [r0, #0x0]
	add r2, r2, r1
	ldr r1, [r0, #0x8]
	ldr r0, _0208D480 ; =0x04000454
	sub r1, r2, r1
	str r1, [sp, #0x28]
	ldr r1, [r5, #0x40]
	ldr r3, [r4, #0x10]
	ldr r1, [r1, #0x20]
	ldr r2, [r4, #0x40]
	ldr r1, [r1, #0x0]
	add r3, r3, r2
	ldr r2, [r1, #0xc]
	mov r1, #0x0
	sub r2, r3, r2
	str r2, [sp, #0x2c]
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x40]
	ldr r0, _0208D484 ; =0x04000470
	ldr r1, [r1, #0x20]
	ldr r1, [r1, #0x0]
	ldr r3, [r1, #0xc]
	ldr r2, [r1, #0x8]
	ldr r1, [r1, #0x4]
	str r1, [r0, #0x0]
	str r2, [r0, #0x0]
	str r3, [r0, #0x0]
	ldr r0, [r5, #0x44]
	bl G3_MultMtx43
_0208D3D8: ; 0x0208D3D8
	add r0, sp, #0x0
	bl G3_MultMtx43
_0208D3E0:
	ldr r0, [r5, #0x40]
	ldrh r4, [r4, #0x36]
	ldrh r12, [r0, #0x72]
	ldr r1, _0208D488 ; =0x04000480
	and r2, r4, #0x1f
	and r0, r12, #0x1f
	mul r3, r2, r0
	and r2, r4, #0x3e0
	and r0, r12, #0x3e0
	mul r0, r2, r0
	and r4, r4, #0x7c00
	and r2, r12, #0x7c00
	mul r12, r4, r2
	mov r2, r3, asr #0x5
	mov r0, r0, asr #0xf
	mov r3, r12, asr #0x19
	orr r0, r2, r0, lsl #0x5
	orr r0, r0, r3, lsl #0xa
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r0, [r1, #0x0]
	ldr r2, [r5, #0x40]
	ldr r4, _0208D48C ; =0x02106158
	ldr r1, [r2, #0x20]
	ldrsh r0, [r2, #0x78]
	ldr r12, [r1, #0x0]
	ldrsh r1, [r2, #0x7a]
	ldr r3, [r12, #0x0]
	ldrsh r2, [r12, #0x50]
	mov r3, r3, lsl #0xc
	mov r5, r3, lsr #0x1f
	ldrsh r3, [r12, #0x52]
	ldr r4, [r4, r5, lsl #0x2]
	blx r4
	add sp, sp, #0x90
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0208D474: .word 0x040004A4
_0208D478: .word 0x020FFA38
_0208D47C: .word 0x02106160
_0208D480: .word 0x04000454
_0208D484: .word 0x04000470
_0208D488: .word 0x04000480
_0208D48C: .word 0x02106158

	arm_func_start FUN_0208D490
FUN_0208D490: ; 0x0208D490
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x88
	mov r6, r1
	ldrh r1, [r6, #0x2e]
	mov r7, r0
	ldr r4, [r7, #0x40]
	mov r0, r1, lsl #0x16
	mov r2, r1, lsl #0x1b
	mov r0, r0, lsr #0x1b
	mov r2, r2, lsr #0x1b
	add r0, r0, #0x1
	mul r3, r2, r0
	ldr r2, [r4, #0x20]
	movs r3, r3, asr #0x5
	ldr r0, [r7, #0x3c]
	ldr r4, [r2, #0x0]
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x1a
	orr r1, r0, #0xc0
	orr r2, r1, r2, lsl #0x18
	ldrsh r0, [r4, #0x30]
	ldr r8, [r7, #0x44]
	ldr r1, _0208DB60 ; =0x040004A4
	orr r2, r2, r3, lsl #0x10
	str r2, [r1, #0x0]
	addeq sp, sp, #0x88
	ldr r1, [r1, #0x0]
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
	ldr r4, [r6, #0x30]
	ldr r1, [r7, #0x40]
	smull r2, r5, r4, r0
	ldr r0, [r1, #0x20]
	mov r3, #0x800
	adds r1, r2, r3
	ldr r2, [r0, #0x0]
	adc r9, r5, #0x0
	ldr r0, [r2, #0x48]
	mov r5, r1, lsr #0xc
	mov r0, r0, lsl #0x1
	mov r1, r4, asr #0x1f
	orr r5, r5, r9, lsl #0x14
	movs r0, r0, lsr #0x1d
	mov r9, #0x0
	beq _0208D558
	cmp r0, #0x1
	beq _0208D594
	cmp r0, #0x2
	beq _0208D5B0
	b _0208D5D4
_0208D558:
	ldrsh r0, [r6, #0x34]
	mov lr, r0, asr #0x1f
	umull r12, r10, r4, r0
	mla r10, r4, lr, r10
	smull lr, r4, r5, r0
	mla r10, r1, r0, r10
	adds r0, lr, r3
	adc lr, r4, r9
	adds r1, r12, r3
	mov r5, r0, lsr #0xc
	adc r0, r10, r9
	mov r4, r1, lsr #0xc
	orr r5, r5, lr, lsl #0x14
	orr r4, r4, r0, lsl #0x14
	b _0208D5D4
_0208D594:
	ldrsh r0, [r6, #0x34]
	smull r1, r0, r5, r0
	adds r1, r1, r3
	adc r0, r0, r9
	mov r5, r1, lsr #0xc
	orr r5, r5, r0, lsl #0x14
	b _0208D5D4
_0208D5B0:
	ldrsh r10, [r6, #0x34]
	mov r0, r10, asr #0x1f
	umull lr, r12, r4, r10
	mla r12, r4, r0, r12
	adds r3, lr, r3
	mla r12, r1, r10, r12
	adc r0, r12, r9
	mov r4, r3, lsr #0xc
	orr r4, r4, r0, lsl #0x14
_0208D5D4:
	ldr r0, [r2, #0x0]
	mov r0, r0, lsl #0x8
	movs r0, r0, lsr #0x1f
	bne _0208D83C
	ldr r1, [r6, #0x8]
	ldr r0, [r6, #0x38]
	add r9, sp, #0x18
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r2, [r6, #0xc]
	ldr r1, [r6, #0x3c]
	add r0, r6, #0x14
	add r1, r2, r1
	str r1, [sp, #0x10]
	ldr r2, [r6, #0x10]
	ldr r1, [r6, #0x40]
	add r1, r2, r1
	str r1, [sp, #0x14]
	ldmia r0, {r0-r2}
	stmia r9, {r0-r2}
	ldr r0, [r8, #0x8]
	add r1, sp, #0x24
	str r0, [sp, #0x24]
	ldr r2, [r8, #0x14]
	mov r0, r9
	str r2, [sp, #0x28]
	ldr r3, [r8, #0x20]
	mov r2, r9
	str r3, [sp, #0x2c]
	bl VEC_CrossProduct
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	bne _0208D678
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _0208D678
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	addeq sp, sp, #0x88
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
_0208D678:
	add r0, sp, #0x18
	mov r1, r0
	bl VEC_Normalize
	add r1, sp, #0x30
	mov r0, r8
	bl MI_Copy36B
	add r0, sp, #0x18
	add r1, sp, #0x30
	mov r2, r0
	bl MTX_MultVec33
	add r0, sp, #0xc
	mov r1, r8
	mov r2, r0
	bl MTX_MultVec43
	add r0, r6, #0x14
	add r3, sp, #0x0
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	mov r0, r3
	mov r1, r3
	bl VEC_Normalize
	ldr r0, [r8, #0x20]
	ldr r1, [sp, #0x8]
	rsb r0, r0, #0x0
	smull r3, r0, r1, r0
	mov r2, #0x800
	adds r1, r3, r2
	ldr r3, [r8, #0x14]
	adc r0, r0, #0x0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	ldr r0, [r8, #0x8]
	ldr r9, [sp, #0x0]
	rsb r0, r0, #0x0
	smull r8, r0, r9, r0
	adds r9, r8, r2
	adc r8, r0, #0x0
	mov r0, r9, lsr #0xc
	orr r0, r0, r8, lsl #0x14
	ldr r8, [sp, #0x4]
	rsb r3, r3, #0x0
	smull r9, r3, r8, r3
	adds r8, r9, r2
	adc r2, r3, #0x0
	mov r3, r8, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	add r0, r0, r3
	adds r1, r1, r0
	ldr r0, [r7, #0x40]
	rsbmi r1, r1, #0x0
	ldr r0, [r0, #0x20]
	rsb r2, r1, #0x1000
	ldr r0, [r0, #0x0]
	mov r9, #0x800
	ldr r0, [r0, #0x48]
	ldr r12, [sp, #0x18]
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x10
	smull r8, r0, r2, r0
	adds r2, r8, r9
	adc r0, r0, #0x0
	mov r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	add r0, r2, #0x1000
	smull r2, r0, r4, r0
	adds r2, r2, r9
	adc r0, r0, #0x0
	mov lr, r2, lsr #0xc
	orr lr, lr, r0, lsl #0x14
	smull r0, r4, r12, r5
	adds r8, r0, r9
	ldr r3, [sp, #0x1c]
	ldr r0, [sp, #0xc]
	rsb r2, r3, #0x0
	str r0, [sp, #0x78]
	ldr r0, [sp, #0x10]
	smull r10, r5, r3, r5
	str r0, [sp, #0x7c]
	smull r3, r0, r2, lr
	adc r4, r4, #0x0
	mov r8, r8, lsr #0xc
	orr r8, r8, r4, lsl #0x14
	adds r3, r3, r9
	smull lr, r2, r12, lr
	str r8, [sp, #0x54]
	adc r0, r0, #0x0
	adds r8, r10, r9
	adc r4, r5, #0x0
	adds r5, lr, r9
	mov r9, r3, lsr #0xc
	orr r9, r9, r0, lsl #0x14
	mov r8, r8, lsr #0xc
	orr r8, r8, r4, lsl #0x14
	ldr r3, [sp, #0x14]
	adc r0, r2, #0x0
	mov r5, r5, lsr #0xc
	orr r5, r5, r0, lsl #0x14
	mov r4, #0x1000
	ldr r2, _0208DB64 ; =0x04000454
	str r9, [sp, #0x60]
	str r8, [sp, #0x58]
	add r0, sp, #0x54
	str r5, [sp, #0x64]
	str r1, [sp, #0x6c]
	str r1, [sp, #0x70]
	str r1, [sp, #0x5c]
	str r1, [sp, #0x68]
	str r4, [sp, #0x74]
	str r3, [sp, #0x80]
	str r1, [r2, #0x0]
	bl G3_MultMtx43
	b _0208DAE8
_0208D83C:
	ldr r3, [r6, #0x8]
	ldr r1, [r6, #0x38]
	ldr r0, [r2, #0x4]
	add r1, r3, r1
	sub r0, r1, r0
	str r0, [sp, #0xc]
	ldr r0, [r7, #0x40]
	ldr r2, [r6, #0xc]
	ldr r0, [r0, #0x20]
	ldr r1, [r6, #0x3c]
	ldr r0, [r0, #0x0]
	add r1, r2, r1
	ldr r0, [r0, #0x8]
	add r9, sp, #0x18
	sub r0, r1, r0
	str r0, [sp, #0x10]
	ldr r0, [r7, #0x40]
	ldr r2, [r6, #0x10]
	ldr r0, [r0, #0x20]
	ldr r1, [r6, #0x40]
	ldr r0, [r0, #0x0]
	add r2, r2, r1
	ldr r1, [r0, #0xc]
	add r0, r6, #0x14
	sub r1, r2, r1
	str r1, [sp, #0x14]
	ldmia r0, {r0-r2}
	stmia r9, {r0-r2}
	ldr r0, [r8, #0x8]
	add r1, sp, #0x24
	str r0, [sp, #0x24]
	ldr r2, [r8, #0x14]
	mov r0, r9
	str r2, [sp, #0x28]
	ldr r3, [r8, #0x20]
	mov r2, r9
	str r3, [sp, #0x2c]
	bl VEC_CrossProduct
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	bne _0208D900
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _0208D900
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	addeq sp, sp, #0x88
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
_0208D900:
	add r0, sp, #0x18
	mov r1, r0
	bl VEC_Normalize
	add r1, sp, #0x30
	mov r0, r8
	bl MI_Copy36B
	add r0, sp, #0x18
	add r1, sp, #0x30
	mov r2, r0
	bl MTX_MultVec33
	add r0, sp, #0xc
	mov r1, r8
	mov r2, r0
	bl MTX_MultVec43
	add r0, r6, #0x14
	add r3, sp, #0x0
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	mov r0, r3
	mov r1, r3
	bl VEC_Normalize
	ldr r0, [r8, #0x20]
	ldr r1, [sp, #0x8]
	rsb r0, r0, #0x0
	smull r3, r0, r1, r0
	mov r2, #0x800
	adds r1, r3, r2
	ldr r3, [r8, #0x14]
	adc r0, r0, #0x0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	ldr r0, [r8, #0x8]
	ldr r9, [sp, #0x0]
	rsb r0, r0, #0x0
	smull r8, r0, r9, r0
	adds r9, r8, r2
	adc r8, r0, #0x0
	mov r0, r9, lsr #0xc
	orr r0, r0, r8, lsl #0x14
	ldr r8, [sp, #0x4]
	rsb r3, r3, #0x0
	smull r9, r3, r8, r3
	adds r8, r9, r2
	adc r2, r3, #0x0
	mov r3, r8, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	add r0, r0, r3
	adds r1, r1, r0
	ldr r0, [r7, #0x40]
	rsbmi r1, r1, #0x0
	ldr r0, [r0, #0x20]
	rsb r2, r1, #0x1000
	ldr r0, [r0, #0x0]
	mov r9, #0x800
	ldr r0, [r0, #0x48]
	ldr lr, [sp, #0x18]
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x10
	smull r8, r0, r2, r0
	adds r2, r8, r9
	adc r0, r0, #0x0
	mov r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	add r0, r2, #0x1000
	smull r2, r0, r4, r0
	adds r2, r2, r9
	adc r0, r0, #0x0
	mov r8, r2, lsr #0xc
	orr r8, r8, r0, lsl #0x14
	smull r0, r4, lr, r5
	adds r12, r0, r9
	ldr r3, [sp, #0x1c]
	ldr r0, [sp, #0xc]
	rsb r2, r3, #0x0
	str r0, [sp, #0x78]
	ldr r0, [sp, #0x10]
	smull r10, r5, r3, r5
	str r0, [sp, #0x7c]
	smull r3, r0, r2, r8
	adc r4, r4, #0x0
	mov r12, r12, lsr #0xc
	adds r3, r3, r9
	orr r12, r12, r4, lsl #0x14
	adc r0, r0, #0x0
	adds r10, r10, r9
	smull r8, r2, lr, r8
	adc r4, r5, #0x0
	adds r5, r8, r9
	mov r9, r3, lsr #0xc
	orr r9, r9, r0, lsl #0x14
	mov r8, r10, lsr #0xc
	orr r8, r8, r4, lsl #0x14
	ldr r3, [sp, #0x14]
	adc r0, r2, #0x0
	mov r2, r5, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	mov r4, #0x1000
	ldr r0, _0208DB64 ; =0x04000454
	str r12, [sp, #0x54]
	str r9, [sp, #0x60]
	str r8, [sp, #0x58]
	str r1, [sp, #0x6c]
	str r2, [sp, #0x64]
	str r1, [sp, #0x70]
	str r1, [sp, #0x5c]
	str r1, [sp, #0x68]
	str r4, [sp, #0x74]
	str r3, [sp, #0x80]
	str r1, [r0, #0x0]
	ldr r0, [r7, #0x40]
	ldr r1, _0208DB68 ; =0x04000470
	ldr r2, [r0, #0x20]
	add r0, sp, #0x54
	ldr r2, [r2, #0x0]
	ldr r4, [r2, #0xc]
	ldr r3, [r2, #0x8]
	ldr r2, [r2, #0x4]
	str r2, [r1, #0x0]
	str r3, [r1, #0x0]
	str r4, [r1, #0x0]
	bl G3_MultMtx43
_0208DAE8:
	ldr r0, [r7, #0x40]
	ldrh r4, [r6, #0x36]
	ldrh r5, [r0, #0x72]
	mov r2, #0x0
	and r1, r4, #0x1f
	and r0, r5, #0x1f
	mul r3, r1, r0
	and r1, r4, #0x3e0
	and r0, r5, #0x3e0
	mul r0, r1, r0
	and r4, r4, #0x7c00
	and r1, r5, #0x7c00
	mul r5, r4, r1
	mov r1, r3, asr #0x5
	mov r0, r0, asr #0xf
	mov r3, r5, asr #0x19
	orr r0, r1, r0, lsl #0x5
	orr r0, r0, r3, lsl #0xa
	mov r0, r0, lsl #0x10
	ldr r1, _0208DB6C ; =0x04000480
	mov r0, r0, lsr #0x10
	str r0, [r1, #0x0]
	ldr r1, [r7, #0x40]
	mov r3, r2
	ldrsh r0, [r1, #0x7c]
	ldrsh r1, [r1, #0x7e]
	bl FUN_0208ECA0
	add sp, sp, #0x88
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_0208DB60: .word 0x040004A4
_0208DB64: .word 0x04000454
_0208DB68: .word 0x04000470
_0208DB6C: .word 0x04000480

	arm_func_start FUN_0208DB70
FUN_0208DB70: ; 0x0208DB70
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x88
	mov r6, r1
	ldrh r1, [r6, #0x2e]
	mov r7, r0
	ldr r4, [r7, #0x40]
	mov r0, r1, lsl #0x16
	mov r2, r1, lsl #0x1b
	mov r0, r0, lsr #0x1b
	mov r2, r2, lsr #0x1b
	add r0, r0, #0x1
	mul r3, r2, r0
	ldr r2, [r4, #0x20]
	movs r3, r3, asr #0x5
	ldr r0, [r7, #0x3c]
	ldr r4, [r2, #0x0]
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x1a
	orr r1, r0, #0xc0
	orr r2, r1, r2, lsl #0x18
	ldrsh r0, [r4, #0x30]
	ldr r8, [r7, #0x44]
	ldr r1, _0208E248 ; =0x040004A4
	orr r2, r2, r3, lsl #0x10
	str r2, [r1, #0x0]
	addeq sp, sp, #0x88
	ldr r1, [r1, #0x0]
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
	ldr r4, [r6, #0x30]
	ldr r1, [r7, #0x40]
	smull r2, r5, r4, r0
	ldr r0, [r1, #0x20]
	mov r3, #0x800
	adds r1, r2, r3
	ldr r2, [r0, #0x0]
	adc r9, r5, #0x0
	ldr r0, [r2, #0x48]
	mov r5, r1, lsr #0xc
	mov r0, r0, lsl #0x1
	mov r1, r4, asr #0x1f
	orr r5, r5, r9, lsl #0x14
	movs r0, r0, lsr #0x1d
	mov r9, #0x0
	beq _0208DC38
	cmp r0, #0x1
	beq _0208DC74
	cmp r0, #0x2
	beq _0208DC90
	b _0208DCB4
_0208DC38:
	ldrsh r0, [r6, #0x34]
	mov lr, r0, asr #0x1f
	umull r12, r10, r4, r0
	mla r10, r4, lr, r10
	smull lr, r4, r5, r0
	mla r10, r1, r0, r10
	adds r0, lr, r3
	adc lr, r4, r9
	adds r1, r12, r3
	mov r5, r0, lsr #0xc
	adc r0, r10, r9
	mov r4, r1, lsr #0xc
	orr r5, r5, lr, lsl #0x14
	orr r4, r4, r0, lsl #0x14
	b _0208DCB4
_0208DC74:
	ldrsh r0, [r6, #0x34]
	smull r1, r0, r5, r0
	adds r1, r1, r3
	adc r0, r0, r9
	mov r5, r1, lsr #0xc
	orr r5, r5, r0, lsl #0x14
	b _0208DCB4
_0208DC90:
	ldrsh r10, [r6, #0x34]
	mov r0, r10, asr #0x1f
	umull lr, r12, r4, r10
	mla r12, r4, r0, r12
	adds r3, lr, r3
	mla r12, r1, r10, r12
	adc r0, r12, r9
	mov r4, r3, lsr #0xc
	orr r4, r4, r0, lsl #0x14
_0208DCB4:
	ldr r0, [r2, #0x0]
	mov r0, r0, lsl #0x8
	movs r0, r0, lsr #0x1f
	bne _0208DF1C
	ldr r1, [r6, #0x8]
	ldr r0, [r6, #0x38]
	add r9, sp, #0x18
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r2, [r6, #0xc]
	ldr r1, [r6, #0x3c]
	add r0, r6, #0x14
	add r1, r2, r1
	str r1, [sp, #0x10]
	ldr r2, [r6, #0x10]
	ldr r1, [r6, #0x40]
	add r1, r2, r1
	str r1, [sp, #0x14]
	ldmia r0, {r0-r2}
	stmia r9, {r0-r2}
	ldr r0, [r8, #0x8]
	add r1, sp, #0x24
	str r0, [sp, #0x24]
	ldr r2, [r8, #0x14]
	mov r0, r9
	str r2, [sp, #0x28]
	ldr r3, [r8, #0x20]
	mov r2, r9
	str r3, [sp, #0x2c]
	bl VEC_CrossProduct
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	bne _0208DD58
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _0208DD58
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	addeq sp, sp, #0x88
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
_0208DD58:
	add r0, sp, #0x18
	mov r1, r0
	bl VEC_Normalize
	add r1, sp, #0x30
	mov r0, r8
	bl MI_Copy36B
	add r0, sp, #0x18
	add r1, sp, #0x30
	mov r2, r0
	bl MTX_MultVec33
	add r0, sp, #0xc
	mov r1, r8
	mov r2, r0
	bl MTX_MultVec43
	add r0, r6, #0x14
	add r3, sp, #0x0
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	mov r0, r3
	mov r1, r3
	bl VEC_Normalize
	ldr r0, [r8, #0x20]
	ldr r1, [sp, #0x8]
	rsb r0, r0, #0x0
	smull r3, r0, r1, r0
	mov r2, #0x800
	adds r1, r3, r2
	ldr r3, [r8, #0x14]
	adc r0, r0, #0x0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	ldr r0, [r8, #0x8]
	ldr r9, [sp, #0x0]
	rsb r0, r0, #0x0
	smull r8, r0, r9, r0
	adds r9, r8, r2
	adc r8, r0, #0x0
	mov r0, r9, lsr #0xc
	orr r0, r0, r8, lsl #0x14
	ldr r8, [sp, #0x4]
	rsb r3, r3, #0x0
	smull r9, r3, r8, r3
	adds r8, r9, r2
	adc r2, r3, #0x0
	mov r3, r8, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	add r0, r0, r3
	adds r1, r1, r0
	ldr r0, [r7, #0x40]
	rsbmi r1, r1, #0x0
	ldr r0, [r0, #0x20]
	rsb r2, r1, #0x1000
	ldr r0, [r0, #0x0]
	mov r9, #0x800
	ldr r0, [r0, #0x48]
	ldr r12, [sp, #0x18]
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x10
	smull r8, r0, r2, r0
	adds r2, r8, r9
	adc r0, r0, #0x0
	mov r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	add r0, r2, #0x1000
	smull r2, r0, r4, r0
	adds r2, r2, r9
	adc r0, r0, #0x0
	mov lr, r2, lsr #0xc
	orr lr, lr, r0, lsl #0x14
	smull r0, r4, r12, r5
	adds r8, r0, r9
	ldr r3, [sp, #0x1c]
	ldr r0, [sp, #0xc]
	rsb r2, r3, #0x0
	str r0, [sp, #0x78]
	ldr r0, [sp, #0x10]
	smull r10, r5, r3, r5
	str r0, [sp, #0x7c]
	smull r3, r0, r2, lr
	adc r4, r4, #0x0
	mov r8, r8, lsr #0xc
	orr r8, r8, r4, lsl #0x14
	adds r3, r3, r9
	smull lr, r2, r12, lr
	str r8, [sp, #0x54]
	adc r0, r0, #0x0
	adds r8, r10, r9
	adc r4, r5, #0x0
	adds r5, lr, r9
	mov r9, r3, lsr #0xc
	orr r9, r9, r0, lsl #0x14
	mov r8, r8, lsr #0xc
	orr r8, r8, r4, lsl #0x14
	ldr r3, [sp, #0x14]
	adc r0, r2, #0x0
	mov r5, r5, lsr #0xc
	orr r5, r5, r0, lsl #0x14
	mov r4, #0x1000
	ldr r2, _0208E24C ; =0x04000454
	str r9, [sp, #0x60]
	str r8, [sp, #0x58]
	add r0, sp, #0x54
	str r5, [sp, #0x64]
	str r1, [sp, #0x6c]
	str r1, [sp, #0x70]
	str r1, [sp, #0x5c]
	str r1, [sp, #0x68]
	str r4, [sp, #0x74]
	str r3, [sp, #0x80]
	str r1, [r2, #0x0]
	bl G3_MultMtx43
	b _0208E1C8
_0208DF1C:
	ldr r3, [r6, #0x8]
	ldr r1, [r6, #0x38]
	ldr r0, [r2, #0x4]
	add r1, r3, r1
	sub r0, r1, r0
	str r0, [sp, #0xc]
	ldr r0, [r7, #0x40]
	ldr r2, [r6, #0xc]
	ldr r0, [r0, #0x20]
	ldr r1, [r6, #0x3c]
	ldr r0, [r0, #0x0]
	add r1, r2, r1
	ldr r0, [r0, #0x8]
	add r9, sp, #0x18
	sub r0, r1, r0
	str r0, [sp, #0x10]
	ldr r0, [r7, #0x40]
	ldr r2, [r6, #0x10]
	ldr r0, [r0, #0x20]
	ldr r1, [r6, #0x40]
	ldr r0, [r0, #0x0]
	add r2, r2, r1
	ldr r1, [r0, #0xc]
	add r0, r6, #0x14
	sub r1, r2, r1
	str r1, [sp, #0x14]
	ldmia r0, {r0-r2}
	stmia r9, {r0-r2}
	ldr r0, [r8, #0x8]
	add r1, sp, #0x24
	str r0, [sp, #0x24]
	ldr r2, [r8, #0x14]
	mov r0, r9
	str r2, [sp, #0x28]
	ldr r3, [r8, #0x20]
	mov r2, r9
	str r3, [sp, #0x2c]
	bl VEC_CrossProduct
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	bne _0208DFE0
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _0208DFE0
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	addeq sp, sp, #0x88
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
_0208DFE0:
	add r0, sp, #0x18
	mov r1, r0
	bl VEC_Normalize
	add r1, sp, #0x30
	mov r0, r8
	bl MI_Copy36B
	add r0, sp, #0x18
	add r1, sp, #0x30
	mov r2, r0
	bl MTX_MultVec33
	add r0, sp, #0xc
	mov r1, r8
	mov r2, r0
	bl MTX_MultVec43
	add r0, r6, #0x14
	add r3, sp, #0x0
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	mov r0, r3
	mov r1, r3
	bl VEC_Normalize
	ldr r0, [r8, #0x20]
	ldr r1, [sp, #0x8]
	rsb r0, r0, #0x0
	smull r3, r0, r1, r0
	mov r2, #0x800
	adds r1, r3, r2
	ldr r3, [r8, #0x14]
	adc r0, r0, #0x0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	ldr r0, [r8, #0x8]
	ldr r9, [sp, #0x0]
	rsb r0, r0, #0x0
	smull r8, r0, r9, r0
	adds r9, r8, r2
	adc r8, r0, #0x0
	mov r0, r9, lsr #0xc
	orr r0, r0, r8, lsl #0x14
	ldr r8, [sp, #0x4]
	rsb r3, r3, #0x0
	smull r9, r3, r8, r3
	adds r8, r9, r2
	adc r2, r3, #0x0
	mov r3, r8, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	add r0, r0, r3
	adds r1, r1, r0
	ldr r0, [r7, #0x40]
	rsbmi r1, r1, #0x0
	ldr r0, [r0, #0x20]
	rsb r2, r1, #0x1000
	ldr r0, [r0, #0x0]
	mov r9, #0x800
	ldr r0, [r0, #0x48]
	ldr lr, [sp, #0x18]
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x10
	smull r8, r0, r2, r0
	adds r2, r8, r9
	adc r0, r0, #0x0
	mov r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	add r0, r2, #0x1000
	smull r2, r0, r4, r0
	adds r2, r2, r9
	adc r0, r0, #0x0
	mov r8, r2, lsr #0xc
	orr r8, r8, r0, lsl #0x14
	smull r0, r4, lr, r5
	adds r12, r0, r9
	ldr r3, [sp, #0x1c]
	ldr r0, [sp, #0xc]
	rsb r2, r3, #0x0
	str r0, [sp, #0x78]
	ldr r0, [sp, #0x10]
	smull r10, r5, r3, r5
	str r0, [sp, #0x7c]
	smull r3, r0, r2, r8
	adc r4, r4, #0x0
	mov r12, r12, lsr #0xc
	adds r3, r3, r9
	orr r12, r12, r4, lsl #0x14
	adc r0, r0, #0x0
	adds r10, r10, r9
	smull r8, r2, lr, r8
	adc r4, r5, #0x0
	adds r5, r8, r9
	mov r9, r3, lsr #0xc
	orr r9, r9, r0, lsl #0x14
	mov r8, r10, lsr #0xc
	orr r8, r8, r4, lsl #0x14
	ldr r3, [sp, #0x14]
	adc r0, r2, #0x0
	mov r2, r5, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	mov r4, #0x1000
	ldr r0, _0208E24C ; =0x04000454
	str r12, [sp, #0x54]
	str r9, [sp, #0x60]
	str r8, [sp, #0x58]
	str r1, [sp, #0x6c]
	str r2, [sp, #0x64]
	str r1, [sp, #0x70]
	str r1, [sp, #0x5c]
	str r1, [sp, #0x68]
	str r4, [sp, #0x74]
	str r3, [sp, #0x80]
	str r1, [r0, #0x0]
	ldr r0, [r7, #0x40]
	ldr r1, _0208E250 ; =0x04000470
	ldr r2, [r0, #0x20]
	add r0, sp, #0x54
	ldr r2, [r2, #0x0]
	ldr r4, [r2, #0xc]
	ldr r3, [r2, #0x8]
	ldr r2, [r2, #0x4]
	str r2, [r1, #0x0]
	str r3, [r1, #0x0]
	str r4, [r1, #0x0]
	bl G3_MultMtx43
_0208E1C8:
	ldr r0, [r7, #0x40]
	ldrh r4, [r6, #0x36]
	ldrh r5, [r0, #0x72]
	ldr r1, _0208E254 ; =0x04000480
	and r2, r4, #0x1f
	and r0, r5, #0x1f
	mul r3, r2, r0
	and r2, r4, #0x3e0
	and r0, r5, #0x3e0
	mul r0, r2, r0
	and r4, r4, #0x7c00
	and r2, r5, #0x7c00
	mul r5, r4, r2
	mov r2, r3, asr #0x5
	mov r0, r0, asr #0xf
	mov r3, r5, asr #0x19
	orr r0, r2, r0, lsl #0x5
	orr r0, r0, r3, lsl #0xa
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r0, [r1, #0x0]
	ldr r2, [r7, #0x40]
	ldr r1, [r2, #0x20]
	ldrsh r0, [r2, #0x78]
	ldr r3, [r1, #0x0]
	ldrsh r1, [r2, #0x7a]
	ldrsh r2, [r3, #0x50]
	ldrsh r3, [r3, #0x52]
	bl FUN_0208ECA0
	add sp, sp, #0x88
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_0208E248: .word 0x040004A4
_0208E24C: .word 0x04000454
_0208E250: .word 0x04000470
_0208E254: .word 0x04000480

	arm_func_start FUN_0208E258
FUN_0208E258: ; 0x0208E258
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x40
	mov r6, r1
	ldrh r1, [r6, #0x2e]
	mov r7, r0
	ldr r4, [r7, #0x40]
	mov r0, r1, lsl #0x16
	mov r2, r1, lsl #0x1b
	mov r0, r0, lsr #0x1b
	mov r2, r2, lsr #0x1b
	add r0, r0, #0x1
	mul r3, r2, r0
	ldr r2, [r4, #0x20]
	ldr r0, [r7, #0x3c]
	ldr r4, [r2, #0x0]
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x1a
	orr r1, r0, #0xc0
	ldrsh r0, [r4, #0x30]
	movs r4, r3, asr #0x5
	orr r3, r1, r2, lsl #0x18
	ldr r1, [r7, #0x44]
	ldr r2, _0208E698 ; =0x040004A4
	orr r3, r3, r4, lsl #0x10
	str r3, [r2, #0x0]
	addeq sp, sp, #0x40
	ldr r2, [r2, #0x0]
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
	ldr r4, [r6, #0x30]
	ldr r2, [r7, #0x40]
	smull r3, r5, r4, r0
	ldr r0, [r2, #0x20]
	mov r8, #0x800
	adds r2, r3, r8
	ldr r3, [r0, #0x0]
	adc r9, r5, #0x0
	ldr r0, [r3, #0x48]
	mov r5, r2, lsr #0xc
	mov r0, r0, lsl #0x1
	mov r2, r4, asr #0x1f
	orr r5, r5, r9, lsl #0x14
	movs r0, r0, lsr #0x1d
	mov r9, #0x0
	beq _0208E320
	cmp r0, #0x1
	beq _0208E35C
	cmp r0, #0x2
	beq _0208E378
	b _0208E39C
_0208E320:
	ldrsh r0, [r6, #0x34]
	mov lr, r0, asr #0x1f
	umull r12, r10, r4, r0
	mla r10, r4, lr, r10
	smull lr, r4, r5, r0
	mla r10, r2, r0, r10
	adds r0, lr, r8
	adc lr, r4, r9
	adds r2, r12, r8
	mov r5, r0, lsr #0xc
	adc r0, r10, r9
	mov r4, r2, lsr #0xc
	orr r5, r5, lr, lsl #0x14
	orr r4, r4, r0, lsl #0x14
	b _0208E39C
_0208E35C:
	ldrsh r0, [r6, #0x34]
	smull r2, r0, r5, r0
	adds r2, r2, r8
	adc r0, r0, r9
	mov r5, r2, lsr #0xc
	orr r5, r5, r0, lsl #0x14
	b _0208E39C
_0208E378:
	ldrsh r10, [r6, #0x34]
	mov r0, r10, asr #0x1f
	umull lr, r12, r4, r10
	mla r12, r4, r0, r12
	adds r4, lr, r8
	mla r12, r2, r10, r12
	adc r0, r12, r9
	mov r4, r4, lsr #0xc
	orr r4, r4, r0, lsl #0x14
_0208E39C:
	ldr r0, [r3, #0x0]
	mov r0, r0, lsl #0x8
	movs r0, r0, lsr #0x1f
	bne _0208E4BC
	ldr r3, [r6, #0x8]
	ldr r2, [r6, #0x38]
	add r0, sp, #0x0
	add r2, r3, r2
	str r2, [sp, #0x0]
	ldr r8, [r6, #0xc]
	ldr r3, [r6, #0x3c]
	mov r2, r0
	add r3, r8, r3
	str r3, [sp, #0x4]
	ldr r8, [r6, #0x10]
	ldr r3, [r6, #0x40]
	add r3, r8, r3
	str r3, [sp, #0x8]
	bl MTX_MultVec43
	ldrh r0, [r6, #0x20]
	ldr r2, _0208E69C ; =0x020FFA38
	mov r9, #0x0
	mov r0, r0, asr #0x4
	mov r3, r0, lsl #0x1
	mov r0, r3, lsl #0x1
	ldrsh r1, [r2, r0]
	add r0, r3, #0x1
	mov r0, r0, lsl #0x1
	ldrsh r0, [r2, r0]
	mov lr, #0x1000
	ldr r3, [sp, #0x0]
	ldr r2, [sp, #0x4]
	str r3, [sp, #0x30]
	smull r12, r10, r1, r5
	str lr, [sp, #0x2c]
	rsb r8, r1, #0x0
	ldr r1, [sp, #0x8]
	smull lr, r5, r0, r5
	mov r3, #0x800
	str r2, [sp, #0x34]
	adds r2, lr, r3
	adc r5, r5, #0x0
	adds r12, r12, r3
	mov lr, r2, lsr #0xc
	orr lr, lr, r5, lsl #0x14
	smull r5, r2, r8, r4
	adc r10, r10, #0x0
	mov r8, r12, lsr #0xc
	orr r8, r8, r10, lsl #0x14
	adds r5, r5, r3
	smull r10, r4, r0, r4
	adc r0, r2, #0x0
	adds r2, r10, r3
	mov r5, r5, lsr #0xc
	orr r5, r5, r0, lsl #0x14
	mov r3, r2, lsr #0xc
	adc r0, r4, #0x0
	orr r3, r3, r0, lsl #0x14
	ldr r2, _0208E6A0 ; =0x04000454
	str lr, [sp, #0xc]
	add r0, sp, #0xc
	str r8, [sp, #0x10]
	str r9, [sp, #0x14]
	str r5, [sp, #0x18]
	str r3, [sp, #0x1c]
	str r9, [sp, #0x20]
	str r9, [sp, #0x24]
	str r9, [sp, #0x28]
	str r1, [sp, #0x38]
	str r9, [r2, #0x0]
	bl G3_MultMtx43
	b _0208E620
_0208E4BC:
	ldr r8, [r6, #0x8]
	ldr r2, [r6, #0x38]
	ldr r0, [r3, #0x4]
	add r2, r8, r2
	sub r0, r2, r0
	str r0, [sp, #0x0]
	ldr r2, [r7, #0x40]
	ldr r8, [r6, #0xc]
	ldr r2, [r2, #0x20]
	ldr r3, [r6, #0x3c]
	ldr r2, [r2, #0x0]
	add r3, r8, r3
	ldr r2, [r2, #0x8]
	add r0, sp, #0x0
	sub r2, r3, r2
	str r2, [sp, #0x4]
	ldr r2, [r7, #0x40]
	ldr r8, [r6, #0x10]
	ldr r2, [r2, #0x20]
	ldr r3, [r6, #0x40]
	ldr r2, [r2, #0x0]
	add r8, r8, r3
	ldr r3, [r2, #0xc]
	mov r2, r0
	sub r3, r8, r3
	str r3, [sp, #0x8]
	bl MTX_MultVec43
	ldrh r0, [r6, #0x20]
	ldr r2, _0208E69C ; =0x020FFA38
	mov lr, #0x0
	mov r0, r0, asr #0x4
	mov r3, r0, lsl #0x1
	mov r0, r3, lsl #0x1
	ldrsh r1, [r2, r0]
	add r0, r3, #0x1
	mov r0, r0, lsl #0x1
	ldrsh r0, [r2, r0]
	mov r10, #0x1000
	ldr r3, [sp, #0x0]
	ldr r2, [sp, #0x4]
	str r3, [sp, #0x30]
	smull r9, r8, r1, r5
	str r10, [sp, #0x2c]
	rsb r12, r1, #0x0
	smull r10, r5, r0, r5
	ldr r1, [sp, #0x8]
	mov r3, #0x800
	str r2, [sp, #0x34]
	adds r2, r10, r3
	adc r5, r5, #0x0
	mov r10, r2, lsr #0xc
	orr r10, r10, r5, lsl #0x14
	str r1, [sp, #0x38]
	adds r9, r9, r3
	str r10, [sp, #0xc]
	adc r10, r8, #0x0
	smull r5, r2, r12, r4
	mov r8, r9, lsr #0xc
	orr r8, r8, r10, lsl #0x14
	smull r9, r4, r0, r4
	adds r5, r5, r3
	adc r0, r2, #0x0
	adds r2, r9, r3
	mov r3, r5, lsr #0xc
	orr r3, r3, r0, lsl #0x14
	adc r0, r4, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	ldr r0, _0208E6A0 ; =0x04000454
	str r8, [sp, #0x10]
	str lr, [sp, #0x14]
	str r3, [sp, #0x18]
	str r2, [sp, #0x1c]
	str lr, [sp, #0x20]
	str lr, [sp, #0x24]
	str lr, [sp, #0x28]
	str lr, [r0, #0x0]
	ldr r0, [r7, #0x40]
	ldr r1, _0208E6A4 ; =0x04000470
	ldr r2, [r0, #0x20]
	add r0, sp, #0xc
	ldr r2, [r2, #0x0]
	ldr r4, [r2, #0xc]
	ldr r3, [r2, #0x8]
	ldr r2, [r2, #0x4]
	str r2, [r1, #0x0]
	str r3, [r1, #0x0]
	str r4, [r1, #0x0]
	bl G3_MultMtx43
_0208E620:
	ldr r0, [r7, #0x40]
	ldrh r4, [r6, #0x36]
	ldrh r5, [r0, #0x72]
	mov r2, #0x0
	and r1, r4, #0x1f
	and r0, r5, #0x1f
	mul r3, r1, r0
	and r1, r4, #0x3e0
	and r0, r5, #0x3e0
	mul r0, r1, r0
	and r4, r4, #0x7c00
	and r1, r5, #0x7c00
	mul r5, r4, r1
	mov r1, r3, asr #0x5
	mov r0, r0, asr #0xf
	mov r3, r5, asr #0x19
	orr r0, r1, r0, lsl #0x5
	orr r0, r0, r3, lsl #0xa
	mov r0, r0, lsl #0x10
	ldr r1, _0208E6A8 ; =0x04000480
	mov r0, r0, lsr #0x10
	str r0, [r1, #0x0]
	ldr r1, [r7, #0x40]
	mov r3, r2
	ldrsh r0, [r1, #0x7c]
	ldrsh r1, [r1, #0x7e]
	bl FUN_0208ECA0
	add sp, sp, #0x40
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_0208E698: .word 0x040004A4
_0208E69C: .word 0x020FFA38
_0208E6A0: .word 0x04000454
_0208E6A4: .word 0x04000470
_0208E6A8: .word 0x04000480

	arm_func_start FUN_0208E6AC
FUN_0208E6AC: ; 0x0208E6AC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x3c
	mov r8, r1
	ldrh r3, [r8, #0x2e]
	mov r9, r0
	ldr r1, [r9, #0x40]
	mov r0, r3, lsl #0x16
	mov r2, r3, lsl #0x1b
	mov r0, r0, lsr #0x1b
	ldr r4, [r1, #0x20]
	mov r2, r2, lsr #0x1b
	ldr r5, [r4, #0x0]
	add r0, r0, #0x1
	mul r0, r2, r0
	movs r11, r0, asr #0x5
	mov r3, r3, lsl #0x10
	ldr r2, [r9, #0x3c]
	mov r6, r3, lsr #0x1a
	orr r3, r2, #0xc0
	ldr r4, [r5, #0x48]
	ldrsh r7, [r5, #0x30]
	mov r2, r4, lsl #0x1
	ldrh r4, [r1, #0x72]
	orr r3, r3, r6, lsl #0x18
	ldrsh r10, [r8, #0x34]
	ldrh r5, [r8, #0x36]
	ldr r1, [r9, #0x44]
	ldr r0, _0208EAE4 ; =0x040004A4
	orr r3, r3, r11, lsl #0x10
	str r3, [r0, #0x0]
	mov r2, r2, lsr #0x1d
	addeq sp, sp, #0x3c
	and r3, r2, #0xff
	ldr r0, [r0, #0x0]
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r6, [r8, #0x30]
	mov r0, #0x800
	smull r7, r2, r6, r7
	adds r7, r7, r0
	adc r2, r2, #0x0
	mov r7, r7, lsr #0xc
	cmp r3, #0x0
	mov lr, r6, asr #0x1f
	orr r7, r7, r2, lsl #0x14
	mov r2, #0x0
	bne _0208E7A0
	mov r12, r10, asr #0x1f
	umull r11, r3, r6, r10
	mla r3, r6, r12, r3
	mla r3, lr, r10, r3
	smull r6, r10, r7, r10
	adds r6, r6, r0
	adc r10, r10, r2
	adds r11, r11, r0
	adc r0, r3, r2
	mov r7, r6, lsr #0xc
	mov r6, r11, lsr #0xc
	orr r7, r7, r10, lsl #0x14
	orr r6, r6, r0, lsl #0x14
	b _0208E7E0
_0208E7A0:
	cmp r3, #0x1
	bne _0208E7C0
	smull r10, r3, r7, r10
	adds r7, r10, r0
	adc r0, r3, r2
	mov r7, r7, lsr #0xc
	orr r7, r7, r0, lsl #0x14
	b _0208E7E0
_0208E7C0:
	mov r12, r10, asr #0x1f
	umull r11, r3, r6, r10
	adds r0, r11, r0
	mla r3, r6, r12, r3
	mla r3, lr, r10, r3
	adc r2, r3, r2
	mov r6, r0, lsr #0xc
	orr r6, r6, r2, lsl #0x14
_0208E7E0:
	ldr r0, [r9, #0x40]
	ldr r0, [r0, #0x20]
	ldr r10, [r0, #0x0]
	ldr r0, [r10, #0x0]
	mov r0, r0, lsl #0x8
	movs r0, r0, lsr #0x1f
	bne _0208E90C
	ldr r3, [r8, #0x8]
	ldr r2, [r8, #0x38]
	add r0, sp, #0x0
	add r2, r3, r2
	str r2, [sp, #0x0]
	ldr r10, [r8, #0xc]
	ldr r3, [r8, #0x3c]
	mov r2, r0
	add r3, r10, r3
	str r3, [sp, #0x4]
	ldr r10, [r8, #0x10]
	ldr r3, [r8, #0x40]
	add r3, r10, r3
	str r3, [sp, #0x8]
	bl MTX_MultVec43
	ldrh r0, [r8, #0x20]
	ldr r2, _0208EAE8 ; =0x020FFA38
	ldr r12, [sp, #0x0]
	mov r0, r0, asr #0x4
	mov r3, r0, lsl #0x1
	mov r0, r3, lsl #0x1
	ldrsh r1, [r2, r0]
	add r0, r3, #0x1
	mov r0, r0, lsl #0x1
	ldrsh r0, [r2, r0]
	str r12, [sp, #0x30]
	mov r12, #0x1000
	ldr r2, [sp, #0x4]
	smull r11, r10, r1, r7
	str r12, [sp, #0x2c]
	rsb r3, r1, #0x0
	ldr r1, [sp, #0x8]
	str r2, [sp, #0x34]
	mov r8, #0x0
	smull r12, r7, r0, r7
	mov r2, #0x800
	str r1, [sp, #0x38]
	adds r1, r12, r2
	adc r12, r7, #0x0
	adds r7, r11, r2
	mov r11, r1, lsr #0xc
	orr r11, r11, r12, lsl #0x14
	smull r12, r1, r3, r6
	adc r10, r10, #0x0
	mov r7, r7, lsr #0xc
	orr r7, r7, r10, lsl #0x14
	adds r3, r12, r2
	smull r10, r6, r0, r6
	adc r0, r1, #0x0
	adds r1, r10, r2
	mov r3, r3, lsr #0xc
	orr r3, r3, r0, lsl #0x14
	mov r2, r1, lsr #0xc
	adc r0, r6, #0x0
	orr r2, r2, r0, lsl #0x14
	ldr r1, _0208EAEC ; =0x04000454
	str r11, [sp, #0xc]
	add r0, sp, #0xc
	str r7, [sp, #0x10]
	str r8, [sp, #0x14]
	str r3, [sp, #0x18]
	str r2, [sp, #0x1c]
	str r8, [sp, #0x20]
	str r8, [sp, #0x24]
	str r8, [sp, #0x28]
	str r8, [r1, #0x0]
	bl G3_MultMtx43
	b _0208EA70
_0208E90C:
	ldr r3, [r8, #0x8]
	ldr r2, [r8, #0x38]
	ldr r0, [r10, #0x4]
	add r2, r3, r2
	sub r0, r2, r0
	str r0, [sp, #0x0]
	ldr r2, [r9, #0x40]
	ldr r10, [r8, #0xc]
	ldr r2, [r2, #0x20]
	ldr r3, [r8, #0x3c]
	ldr r2, [r2, #0x0]
	add r3, r10, r3
	ldr r2, [r2, #0x8]
	add r0, sp, #0x0
	sub r2, r3, r2
	str r2, [sp, #0x4]
	ldr r2, [r9, #0x40]
	ldr r10, [r8, #0x10]
	ldr r2, [r2, #0x20]
	ldr r3, [r8, #0x40]
	ldr r2, [r2, #0x0]
	add r10, r10, r3
	ldr r3, [r2, #0xc]
	mov r2, r0
	sub r3, r10, r3
	str r3, [sp, #0x8]
	bl MTX_MultVec43
	ldrh r0, [r8, #0x20]
	ldr r2, _0208EAE8 ; =0x020FFA38
	mov r8, #0x0
	mov r0, r0, asr #0x4
	mov r3, r0, lsl #0x1
	mov r0, r3, lsl #0x1
	ldrsh r1, [r2, r0]
	add r0, r3, #0x1
	mov r0, r0, lsl #0x1
	ldrsh r0, [r2, r0]
	ldr r12, [sp, #0x0]
	ldr r2, [sp, #0x4]
	str r12, [sp, #0x30]
	mov r12, #0x1000
	str r2, [sp, #0x34]
	smull r11, r10, r1, r7
	str r12, [sp, #0x2c]
	rsb r3, r1, #0x0
	ldr r1, [sp, #0x8]
	smull r12, r7, r0, r7
	mov r2, #0x800
	str r1, [sp, #0x38]
	adds r1, r12, r2
	adc r12, r7, #0x0
	adds r7, r11, r2
	mov r11, r1, lsr #0xc
	orr r11, r11, r12, lsl #0x14
	smull r12, r1, r3, r6
	adc r10, r10, #0x0
	mov r7, r7, lsr #0xc
	orr r7, r7, r10, lsl #0x14
	smull r10, r6, r0, r6
	adds r3, r12, r2
	adc r0, r1, #0x0
	adds r1, r10, r2
	mov r2, r3, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	adc r0, r6, #0x0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x1c]
	ldr r0, _0208EAEC ; =0x04000454
	str r11, [sp, #0xc]
	str r7, [sp, #0x10]
	str r8, [sp, #0x14]
	str r2, [sp, #0x18]
	str r8, [sp, #0x20]
	str r8, [sp, #0x24]
	str r8, [sp, #0x28]
	str r8, [r0, #0x0]
	ldr r0, [r9, #0x40]
	ldr r1, _0208EAF0 ; =0x04000470
	ldr r2, [r0, #0x20]
	add r0, sp, #0xc
	ldr r2, [r2, #0x0]
	ldr r6, [r2, #0xc]
	ldr r3, [r2, #0x8]
	ldr r2, [r2, #0x4]
	str r2, [r1, #0x0]
	str r3, [r1, #0x0]
	str r6, [r1, #0x0]
	bl G3_MultMtx43
_0208EA70:
	and r1, r5, #0x1f
	and r0, r4, #0x1f
	mul r2, r1, r0
	and r1, r5, #0x3e0
	and r0, r4, #0x3e0
	mul r0, r1, r0
	and r3, r5, #0x7c00
	and r1, r4, #0x7c00
	mul r4, r3, r1
	mov r1, r2, asr #0x5
	mov r0, r0, asr #0xf
	mov r2, r4, asr #0x19
	orr r0, r1, r0, lsl #0x5
	orr r0, r0, r2, lsl #0xa
	mov r0, r0, lsl #0x10
	ldr r1, _0208EAF4 ; =0x04000480
	mov r0, r0, lsr #0x10
	str r0, [r1, #0x0]
	ldr r2, [r9, #0x40]
	ldr r1, [r2, #0x20]
	ldrsh r0, [r2, #0x78]
	ldr r3, [r1, #0x0]
	ldrsh r1, [r2, #0x7a]
	ldrsh r2, [r3, #0x50]
	ldrsh r3, [r3, #0x52]
	bl FUN_0208ECA0
	add sp, sp, #0x3c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0208EAE4: .word 0x040004A4
_0208EAE8: .word 0x020FFA38
_0208EAEC: .word 0x04000454
_0208EAF0: .word 0x04000470
_0208EAF4: .word 0x04000480

	arm_func_start FUN_0208EAF8
FUN_0208EAF8: ; 0x0208EAF8
	str r1, [r2, #0x0]
	mov r12, #0x0
	str r12, [r2, #0xc]
	str r0, [r2, #0x18]
	str r12, [r2, #0x24]
	str r12, [r2, #0x4]
	mov r3, #0x1000
	str r3, [r2, #0x10]
	str r12, [r2, #0x1c]
	str r12, [r2, #0x28]
	rsb r0, r0, #0x0
	str r0, [r2, #0x8]
	str r12, [r2, #0x14]
	str r1, [r2, #0x20]
	str r12, [r2, #0x2c]
	bx lr

	arm_func_start FUN_0208EB38
FUN_0208EB38: ; 0x0208EB38
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r3, _0208EBDC ; =0x00000555
	rsb r7, r1, #0x1000
	ldr ip, _0208EBE0 ; =0x0000093D
	mov r4, #0x0
	umull r9, r8, r7, r3
	umull r6, r5, r0, r12
	mov lr, #0x800
	adds r9, r9, lr
	mla r8, r7, r4, r8
	mov r7, r7, asr #0x1f
	mla r8, r7, r3, r8
	adc r7, r8, #0x0
	mov r3, r9, lsr #0xc
	adds r6, r6, lr
	orr r3, r3, r7, lsl #0x14
	add r1, r3, r1
	mla r5, r0, r4, r5
	mov r0, r0, asr #0x1f
	mla r5, r0, r12, r5
	adc r0, r5, #0x0
	mov r5, r6, lsr #0xc
	orr r5, r5, r0, lsl #0x14
	str r1, [r2, #0x0]
	add r12, r3, r5
	str r12, [r2, #0xc]
	sub r0, r3, r5
	str r0, [r2, #0x18]
	str r4, [r2, #0x24]
	str r0, [r2, #0x4]
	str r1, [r2, #0x10]
	str r12, [r2, #0x1c]
	str r4, [r2, #0x28]
	str r12, [r2, #0x8]
	str r0, [r2, #0x14]
	str r1, [r2, #0x20]
	str r4, [r2, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_0208EBDC: .word 0x00000555
_0208EBE0: .word 0x0000093D

	arm_func_start FUN_0208EBE4
FUN_0208EBE4: ; 0x0208EBE4
	stmdb sp!, {r4-r8,lr}
	sub r7, r2, #0x1000
	add r5, r3, #0x1000
	add r4, r2, #0x1000
	mov r2, r0, lsl #0x8
	mov r0, r1, lsl #0x8
	sub r3, r3, #0x1000
	mov r0, r0, lsr #0x10
	mov r1, r2, lsr #0x10
	ldr ip, _0208EC8C ; =0x04000500
	mov r8, #0x1
	ldr r6, _0208EC90 ; =0x000003FF
	mov r2, r7, lsl #0x10
	mov lr, r5, lsl #0x10
	mov r4, r4, lsl #0x10
	mov r5, r3, lsl #0x10
	ldr r3, _0208EC94 ; =0x04000488
	str r8, [r12, #0x0]
	mov r12, #0x0
	and r2, r6, r2, asr #0x16
	and r7, r6, lr, asr #0x16
	and lr, r6, r4, asr #0x16
	and r4, r6, r5, asr #0x16
	ldr r6, _0208EC98 ; =0x04000490
	str r12, [r3, #0x0]
	orr r5, r2, r7, lsl #0x14
	str r5, [r6, #0x0]
	str r1, [r3, #0x0]
	orr r5, lr, r7, lsl #0x14
	str r5, [r6, #0x0]
	orr r1, r1, r0, lsl #0x10
	str r1, [r3, #0x0]
	orr r1, lr, r4, lsl #0x14
	str r1, [r6, #0x0]
	mov r0, r0, lsl #0x10
	str r0, [r3, #0x0]
	orr r1, r2, r4, lsl #0x14
	ldr r0, _0208EC9C ; =0x04000504
	str r1, [r6, #0x0]
	str r12, [r0, #0x0]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0208EC8C: .word 0x04000500
_0208EC90: .word 0x000003FF
_0208EC94: .word 0x04000488
_0208EC98: .word 0x04000490
_0208EC9C: .word 0x04000504

	arm_func_start FUN_0208ECA0
FUN_0208ECA0: ; 0x0208ECA0
	stmdb sp!, {r4-r8,lr}
	add r12, r3, #0x1000
	sub r5, r2, #0x1000
	add r4, r2, #0x1000
	mov r2, r0, lsl #0x8
	mov r0, r1, lsl #0x8
	sub r3, r3, #0x1000
	mov r0, r0, lsr #0x10
	mov r1, r2, lsr #0x10
	ldr r7, _0208ED48 ; =0x04000500
	mov r8, #0x1
	ldr r6, _0208ED4C ; =0x000003FF
	mov r2, r12, lsl #0x10
	mov lr, r5, lsl #0x10
	mov r4, r4, lsl #0x10
	mov r5, r3, lsl #0x10
	ldr r3, _0208ED50 ; =0x04000488
	str r8, [r7, #0x0]
	mov r12, #0x0
	and r7, r6, r2, asr #0x16
	and r2, r6, lr, asr #0x16
	and lr, r6, r4, asr #0x16
	and r4, r6, r5, asr #0x16
	ldr r6, _0208ED54 ; =0x04000490
	str r12, [r3, #0x0]
	orr r5, r2, r7, lsl #0xa
	str r5, [r6, #0x0]
	str r1, [r3, #0x0]
	orr r5, lr, r7, lsl #0xa
	str r5, [r6, #0x0]
	orr r1, r1, r0, lsl #0x10
	str r1, [r3, #0x0]
	orr r1, lr, r4, lsl #0xa
	str r1, [r6, #0x0]
	mov r0, r0, lsl #0x10
	str r0, [r3, #0x0]
	orr r1, r2, r4, lsl #0xa
	ldr r0, _0208ED58 ; =0x04000504
	str r1, [r6, #0x0]
	str r12, [r0, #0x0]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0208ED48: .word 0x04000500
_0208ED4C: .word 0x000003FF
_0208ED50: .word 0x04000488
_0208ED54: .word 0x04000490
_0208ED58: .word 0x04000504

	arm_func_start FUN_0208ED5C
FUN_0208ED5C: ; 0x0208ED5C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x24
	ldr r3, [r1, #0x20]
	str r1, [sp, #0x0]
	ldr r6, [r3, #0x14]
	mov r8, r0
	ldrb r3, [r6, #0x8]
	ldrb r0, [r6, #0xc]
	str r2, [sp, #0x4]
	mov r3, r3, lsl #0xc
	mov r2, r3, asr #0x1f
	mov r2, r2, lsl #0x4
	mov r1, #0x800
	mov r4, r3, lsl #0x4
	adds r4, r4, r1
	orr r2, r2, r3, lsr #0x1c
	adc r1, r2, #0x0
	mov r5, r4, lsr #0xc
	cmp r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x8]
	orr r5, r5, r1, lsl #0x14
	addle sp, sp, #0x24
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	ldr sb, _0208F06C ; =0x021C8C5C
	str r0, [sp, #0x18]
	str r0, [sp, #0x14]
	str r0, [sp, #0x1c]
	str r0, [sp, #0x20]
	mov r0, #0x1000
	mov r4, r5, asr #0x1f
	str r0, [sp, #0x10]
_0208EDE0:
	ldr r0, [sp, #0x4]
	bl FUN_02090A58
	movs r7, r0
	addeq sp, sp, #0x24
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r0, [sp, #0x0]
	mov r1, r7
	add r0, r0, #0x14
	bl FUN_02090AA4
	add r0, r7, #0x38
	add r1, r8, #0x8
	str r0, [sp, #0xc]
	add r10, r7, #0x8
	ldmia r1, {r0-r2}
	stmia r10, {r0-r2}
	ldr r10, [r8, #0x14]
	ldr r12, [r9, #0x0]
	ldr r1, _0208F070 ; =0x5EEDF715
	ldr r0, _0208F074 ; =0x1B0CB173
	mov r2, r10, asr #0x1f
	mla r0, r12, r1, r0
	str r0, [r9, #0x0]
	umull lr, r12, r10, r5
	mla r12, r10, r4, r12
	ldrsh r1, [r6, #0x2]
	mov r0, r0, lsr #0x17
	mla r12, r2, r5, r12
	mul r0, r1, r0
	mov r3, #0x800
	adds r2, lr, r3
	sub r0, r0, r1, lsl #0x8
	adc r10, r12, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r10, lsl #0x14
	add r0, r2, r0, asr #0x8
	str r0, [r7, #0x14]
	ldr r10, [r8, #0x18]
	ldr r12, [r9, #0x0]
	ldr r1, _0208F070 ; =0x5EEDF715
	ldr r0, _0208F074 ; =0x1B0CB173
	mov r2, r10, asr #0x1f
	mla r0, r12, r1, r0
	str r0, [r9, #0x0]
	umull lr, r12, r10, r5
	mla r12, r10, r4, r12
	mla r12, r2, r5, r12
	adds r2, lr, r3
	ldrsh r1, [r6, #0x2]
	mov r0, r0, lsr #0x17
	adc r10, r12, #0x0
	mul r0, r1, r0
	mov r2, r2, lsr #0xc
	sub r0, r0, r1, lsl #0x8
	orr r2, r2, r10, lsl #0x14
	add r0, r2, r0, asr #0x8
	str r0, [r7, #0x18]
	ldr r12, [r8, #0x1c]
	ldr r10, [r9, #0x0]
	ldr r1, _0208F070 ; =0x5EEDF715
	ldr r0, _0208F074 ; =0x1B0CB173
	mov r2, r12, asr #0x1f
	mla r0, r10, r1, r0
	umull r10, lr, r12, r5
	str r0, [r9, #0x0]
	mla lr, r12, r4, lr
	adds r3, r10, r3
	mla lr, r2, r5, lr
	ldrsh r1, [r6, #0x2]
	mov r0, r0, lsr #0x17
	adc r2, lr, #0x0
	mul r0, r1, r0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	sub r0, r0, r1, lsl #0x8
	add r0, r3, r0, asr #0x8
	ldr r3, [sp, #0xc]
	add r11, r8, #0x38
	str r0, [r7, #0x1c]
	ldmia r11, {r0-r2}
	stmia r3, {r0-r2}
	ldrb r0, [r6, #0x9]
	ldrsh r1, [r8, #0x34]
	ldr r2, [r8, #0x30]
	add r0, r0, #0x1
	mul r1, r2, r1
	mov r1, r1, asr #0xc
	mul r0, r1, r0
	mov r0, r0, asr #0x6
	str r0, [r7, #0x30]
	ldr r0, [sp, #0x10]
	strh r0, [r7, #0x34]
	ldrh r0, [r6, #0x0]
	mov r0, r0, lsl #0x19
	movs r0, r0, lsr #0x1f
	ldrneh r0, [r6, #0xa]
	strneh r0, [r7, #0x36]
	ldreqh r0, [r8, #0x36]
	streqh r0, [r7, #0x36]
	ldrh r1, [r8, #0x2e]
	ldrh r0, [r7, #0x2e]
	mov r2, r1, lsl #0x1b
	mov r1, r1, lsl #0x16
	mov r1, r1, lsr #0x1b
	mov r2, r2, lsr #0x1b
	add r1, r1, #0x1
	mul r1, r2, r1
	mov r1, r1, lsl #0xb
	mov r1, r1, lsr #0x10
	bic r0, r0, #0x1f
	and r1, r1, #0x1f
	orr r0, r0, r1
	strh r0, [r7, #0x2e]
	ldrh r0, [r7, #0x2e]
	bic r0, r0, #0x3e0
	orr r0, r0, #0x3e0
	strh r0, [r7, #0x2e]
	ldrh r0, [r6, #0x0]
	mov r0, r0, lsl #0x1b
	movs r0, r0, lsr #0x1e
	beq _0208EFE4
	cmp r0, #0x1
	beq _0208EFF4
	cmp r0, #0x2
	ldreqh r0, [r8, #0x20]
	streqh r0, [r7, #0x20]
	ldreqsh r0, [r8, #0x22]
	streqh r0, [r7, #0x22]
	b _0208F004
_0208EFE4:
	ldr r0, [sp, #0x14]
	strh r0, [r7, #0x20]
	strh r0, [r7, #0x22]
	b _0208F004
_0208EFF4:
	ldrh r0, [r8, #0x20]
	strh r0, [r7, #0x20]
	ldr r0, [sp, #0x18]
	strh r0, [r7, #0x22]
_0208F004:
	ldrh r1, [r6, #0x6]
	ldr r0, _0208F078 ; =0x0000FFFF
	strh r1, [r7, #0x24]
	ldr r1, [sp, #0x1c]
	strh r1, [r7, #0x26]
	ldrb r1, [r6, #0xf]
	strb r1, [r7, #0x2c]
	ldrh r1, [r8, #0x24]
	mov r1, r1, lsr #0x1
	bl _s32_div_f
	strh r0, [r7, #0x28]
	ldrh r1, [r8, #0x24]
	ldr r0, _0208F078 ; =0x0000FFFF
	bl _s32_div_f
	strh r0, [r7, #0x2a]
	ldr r0, [sp, #0x20]
	strb r0, [r7, #0x2d]
	ldr r0, [sp, #0x8]
	ldrb r1, [r6, #0xc]
	add r0, r0, #0x1
	str r0, [sp, #0x8]
	cmp r0, r1
	blt _0208EDE0
	add sp, sp, #0x24
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0208F06C: .word 0x021C8C5C
_0208F070: .word 0x5EEDF715
_0208F074: .word 0x1B0CB173
_0208F078: .word 0x0000FFFF

	arm_func_start FUN_0208F07C
FUN_0208F07C: ; 0x0208F07C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc4
	mov r9, r0
	ldr r0, [r9, #0x20]
	ldrsh r3, [r9, #0x4e]
	str r0, [sp, #0x4]
	ldr r0, [r9, #0x58]
	ldr r2, _0208FD88 ; =0x00000FFF
	add r3, r0, r3
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x0]
	ldr r8, [r0, #0x0]
	and r0, r3, r2
	strh r0, [r9, #0x4e]
	ldr r0, [r8, #0x0]
	mov r0, r0, lsl #0x1c
	mov r1, r0, lsr #0x1c
	mov r0, r3, asr #0xc
	cmp r1, #0x2
	str r0, [sp, #0xc]
	beq _0208F0E4
	cmp r1, #0x3
	beq _0208F0E4
	sub r0, r1, #0x5
	cmp r0, #0x4
	bhi _0208F0EC
_0208F0E4:
	mov r0, r9
	bl FUN_0208FF08
_0208F0EC:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x8]
	addle sp, sp, #0xc4
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	str r0, [sp, #0x18]
	str r0, [sp, #0x24]
	str r0, [sp, #0x20]
	str r0, [sp, #0x1c]
	mov r0, #0x1000
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x8]
	ldr r6, _0208FD8C ; =0x021C8C5C
	ldr r4, _0208FD90 ; =0x5EEDF715
	ldr r5, _0208FD94 ; =0x1B0CB173
	str r0, [sp, #0x38]
	str r0, [sp, #0x3c]
	str r0, [sp, #0x40]
_0208F13C:
	ldr r0, [sp, #0x0]
	bl FUN_02090A58
	movs r7, r0
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	add r0, r9, #0x8
	mov r1, r7
	bl FUN_02090AA4
_0208F160: ; 0x0208F160
	ldr r0, [r8, #0x0]
	mov r0, r0, lsl #0x1c
	mov r0, r0, lsr #0x1c
	cmp r0, #0x9
	addls pc, pc, r0, lsl #0x2
	b _0208F87C
_0208F178:
	b _0208F1A0
_0208F17C:
	b _0208F1BC
_0208F180:
	b _0208F22C
_0208F184:
	b _0208F294
_0208F188:
	b _0208F328
_0208F18C:
	b _0208F428
_0208F190:
	b _0208F720
_0208F194:
	b _0208F7A4
_0208F198:
	b _0208F4E4
_0208F19C:
	b _0208F5B4
_0208F1A0:
	ldr r0, [sp, #0x1c]
	str r0, [r7, #0x10]
	ldr r0, [r7, #0x10]
	str r0, [r7, #0xc]
	ldr r0, [r7, #0xc]
	str r0, [r7, #0x8]
	b _0208F87C
_0208F1BC:
	add r0, r7, #0x8
	bl FUN_02090B50
	ldr r2, [r7, #0x8]
	ldr r1, [r9, #0x5c]
	mov r0, #0x800
	smull r3, r1, r2, r1
	adds r2, r3, r0
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [r7, #0x8]
	ldr r2, [r7, #0xc]
	ldr r1, [r9, #0x5c]
	smull r3, r1, r2, r1
	adds r2, r3, r0
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [r7, #0xc]
	ldr r2, [r7, #0x10]
	ldr r1, [r9, #0x5c]
	smull r3, r1, r2, r1
	adds r2, r3, r0
	adc r0, r1, #0x0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [r7, #0x10]
	b _0208F87C
_0208F22C:
	add r0, sp, #0x58
	bl FUN_02090AF4
	ldr r2, [sp, #0x58]
	ldr r0, [r9, #0x5c]
	mov r1, #0x800
	smull r3, r0, r2, r0
	adds r2, r3, r1
	adc r0, r0, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x58]
	ldr r3, [sp, #0x5c]
	ldr r2, [r9, #0x5c]
	add r0, r7, #0x8
	smull r10, r2, r3, r2
	adds r3, r10, r1
	adc r1, r2, #0x0
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	ldr r1, [sp, #0x20]
	str r2, [sp, #0x5c]
	str r1, [sp, #0x60]
	add r1, sp, #0x58
	mov r2, r9
	bl FUN_0208FDA8
	b _0208F87C
_0208F294:
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0xc]
	bl _s32_div_f
	ldr r1, [sp, #0x18]
	mov r0, r0, asr #0x4
	add r1, r1, #0x10000
	mov r2, r0, lsl #0x1
	str r1, [sp, #0x18]
	ldr r0, _0208FD98 ; =0x020FFA38
	mov r1, r2, lsl #0x1
	ldrsh r0, [r0, r1]
	add r1, r2, #0x1
	mov r2, r1, lsl #0x1
	ldr r1, _0208FD98 ; =0x020FFA38
	ldrsh r3, [r1, r2]
	ldr r2, [r9, #0x5c]
	mov r1, #0x800
	smull r10, r2, r0, r2
	adds r10, r10, r1
	adc r0, r2, #0x0
	mov r2, r10, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x64]
	ldr r2, [r9, #0x5c]
	add r0, r7, #0x8
	smull r10, r2, r3, r2
	adds r3, r10, r1
	adc r1, r2, #0x0
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	ldr r1, [sp, #0x24]
	str r2, [sp, #0x68]
	str r1, [sp, #0x6c]
	add r1, sp, #0x64
	mov r2, r9
	bl FUN_0208FDA8
	b _0208F87C
_0208F328:
	add r0, r7, #0x8
	bl FUN_02090B50
	ldr r1, [r6, #0x0]
	mov r0, #0x800
	mla r2, r1, r4, r5
	str r2, [r6, #0x0]
	mov r1, r2, lsr #0x17
	mov r1, r1, lsl #0xc
	sub r1, r1, #0x100000
	mov r1, r1, asr #0x8
	ldr r3, [r7, #0x8]
	ldr r2, [r9, #0x5c]
	smull r10, r2, r3, r2
	adds r3, r10, r0
	adc r2, r2, #0x0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	smull r2, r1, r3, r1
	adds r2, r2, r0
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [r7, #0x8]
	ldr r1, [r6, #0x0]
	mla r2, r1, r4, r5
	str r2, [r6, #0x0]
	mov r1, r2, lsr #0x17
	mov r1, r1, lsl #0xc
	sub r1, r1, #0x100000
	mov r1, r1, asr #0x8
	ldr r3, [r7, #0xc]
	ldr r2, [r9, #0x5c]
	smull r10, r2, r3, r2
	adds r3, r10, r0
	adc r2, r2, #0x0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	smull r2, r1, r3, r1
	adds r2, r2, r0
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [r7, #0xc]
	ldr r1, [r6, #0x0]
	mla r2, r1, r4, r5
	str r2, [r6, #0x0]
	mov r1, r2, lsr #0x17
	mov r1, r1, lsl #0xc
	sub r1, r1, #0x100000
	mov r1, r1, asr #0x8
	ldr r3, [r7, #0x10]
	ldr r2, [r9, #0x5c]
	smull r10, r2, r3, r2
	adds r3, r10, r0
	adc r2, r2, #0x0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	smull r2, r1, r3, r1
	adds r2, r2, r0
	adc r0, r1, #0x0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [r7, #0x10]
	b _0208F87C
_0208F428:
	add r0, sp, #0x70
	bl FUN_02090AF4
_0208F430: ; 0x0208F430
	ldr r0, [r6, #0x0]
	ldr r3, [sp, #0x70]
	mla r1, r0, r4, r5
	str r1, [r6, #0x0]
	ldr r0, [r9, #0x5c]
	mov r2, #0x800
	smull r10, r0, r3, r0
	adds r10, r10, r2
	adc r3, r0, #0x0
	mov r0, r10, lsr #0xc
	orr r0, r0, r3, lsl #0x14
	mov r3, r1, lsr #0x17
	mov r3, r3, lsl #0xc
	sub r3, r3, #0x100000
	mov r3, r3, asr #0x8
	smull r10, r3, r0, r3
	adds r10, r10, r2
	adc r0, r3, #0x0
	mov r3, r10, lsr #0xc
	orr r3, r3, r0, lsl #0x14
	mla r0, r1, r4, r5
	str r0, [r6, #0x0]
	str r3, [sp, #0x70]
	mov r0, r0, lsr #0x17
	mov r0, r0, lsl #0xc
	sub r0, r0, #0x100000
	mov r1, r0, asr #0x8
	ldr r10, [sp, #0x74]
	ldr r3, [r9, #0x5c]
	add r0, r7, #0x8
	smull r11, r3, r10, r3
	adds r10, r11, r2
	adc r3, r3, #0x0
	mov r10, r10, lsr #0xc
	orr r10, r10, r3, lsl #0x14
	smull r3, r1, r10, r1
	adds r2, r3, r2
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0x74]
	add r1, sp, #0x70
	mov r2, r9
	bl FUN_0208FDA8
	b _0208F87C
_0208F4E4:
	add r0, r7, #0x8
	bl FUN_02090B50
	add r0, r9, #0x84
	add r1, r9, #0x8a
	add r2, sp, #0x44
	bl VEC_Fx16CrossProduct
	ldrsh r1, [sp, #0x46]
	ldrsh r0, [sp, #0x48]
	ldrsh r2, [sp, #0x44]
	str r1, [sp, #0x80]
	str r0, [sp, #0x84]
	add r0, sp, #0x7c
	add r1, r7, #0x8
	str r2, [sp, #0x7c]
	bl VEC_DotProduct
_0208F520: ; 0x0208F520
	cmp r0, #0x0
	bgt _0208F54C
	ldr r0, [r7, #0x8]
	rsb r0, r0, #0x0
	str r0, [r7, #0x8]
	ldr r0, [r7, #0xc]
	rsb r0, r0, #0x0
	str r0, [r7, #0xc]
	ldr r0, [r7, #0x10]
	rsb r0, r0, #0x0
	str r0, [r7, #0x10]
_0208F54C:
	ldr r2, [r7, #0x8]
	ldr r1, [r9, #0x5c]
	mov r0, #0x800
	smull r3, r1, r2, r1
	adds r2, r3, r0
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [r7, #0x8]
	ldr r2, [r7, #0xc]
	ldr r1, [r9, #0x5c]
	smull r3, r1, r2, r1
	adds r2, r3, r0
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [r7, #0xc]
	ldr r2, [r7, #0x10]
	ldr r1, [r9, #0x5c]
	smull r3, r1, r2, r1
	adds r2, r3, r0
	adc r0, r1, #0x0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [r7, #0x10]
	b _0208F87C
_0208F5B4:
	add r0, r7, #0x8
	bl FUN_02090B50
	add r0, r9, #0x84
	add r1, r9, #0x8a
	add r2, sp, #0x4a
	bl VEC_Fx16CrossProduct
	ldrsh r1, [sp, #0x4c]
	ldrsh r0, [sp, #0x4e]
	ldrsh r2, [sp, #0x4a]
	str r1, [sp, #0x8c]
	str r0, [sp, #0x90]
	add r0, sp, #0x88
	add r1, r7, #0x8
	str r2, [sp, #0x88]
	bl VEC_DotProduct
_0208F5F0: ; 0x0208F5F0
	cmp r0, #0x0
	bge _0208F61C
	ldr r0, [r7, #0x8]
	rsb r0, r0, #0x0
	str r0, [r7, #0x8]
	ldr r0, [r7, #0xc]
	rsb r0, r0, #0x0
	str r0, [r7, #0xc]
	ldr r0, [r7, #0x10]
	rsb r0, r0, #0x0
	str r0, [r7, #0x10]
_0208F61C:
	ldr r1, [r6, #0x0]
	mov r0, #0x800
	mla r2, r1, r4, r5
	str r2, [r6, #0x0]
	mov r1, r2, lsr #0x17
	mov r1, r1, lsl #0xc
	sub r1, r1, #0x100000
	mov r1, r1, asr #0x9
	add r1, r1, #0x800
	ldr r3, [r7, #0x8]
	ldr r2, [r9, #0x5c]
	smull r10, r2, r3, r2
	adds r3, r10, r0
	adc r2, r2, #0x0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	smull r2, r1, r3, r1
	adds r2, r2, r0
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [r7, #0x8]
	ldr r1, [r6, #0x0]
	mla r2, r1, r4, r5
	str r2, [r6, #0x0]
	mov r1, r2, lsr #0x17
	mov r1, r1, lsl #0xc
	sub r1, r1, #0x100000
	mov r1, r1, asr #0x9
	add r1, r1, #0x800
	ldr r3, [r7, #0xc]
	ldr r2, [r9, #0x5c]
	smull r10, r2, r3, r2
	adds r3, r10, r0
	adc r2, r2, #0x0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	smull r2, r1, r3, r1
	adds r2, r2, r0
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [r7, #0xc]
	ldr r1, [r6, #0x0]
	mla r2, r1, r4, r5
	str r2, [r6, #0x0]
	mov r1, r2, lsr #0x17
	mov r1, r1, lsl #0xc
	sub r1, r1, #0x100000
	mov r1, r1, asr #0x9
	add r1, r1, #0x800
	ldr r3, [r7, #0x10]
	ldr r2, [r9, #0x5c]
	smull r10, r2, r3, r2
	adds r3, r10, r0
	adc r2, r2, #0x0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	smull r2, r1, r3, r1
	adds r2, r2, r0
	adc r0, r1, #0x0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [r7, #0x10]
	b _0208F87C
_0208F720:
	add r0, r7, #0x14
	bl FUN_02090AF4
	ldr r2, [r7, #0x14]
	ldr r1, [r9, #0x5c]
	mov r0, #0x800
	smull r3, r1, r2, r1
	adds r2, r3, r0
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0x94]
	ldr r3, [r7, #0x18]
	ldr r2, [r9, #0x5c]
	ldr r1, [r6, #0x0]
	smull r10, r2, r3, r2
	adds r3, r10, r0
	adc r0, r2, #0x0
	mov r2, r3, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	mla r0, r1, r4, r5
	str r0, [r6, #0x0]
	str r2, [sp, #0x98]
	mov r1, r0, lsr #0x17
	ldr r2, [r9, #0x60]
	add r0, r7, #0x8
	mul r1, r2, r1
	sub r1, r1, r2, lsl #0x8
	mov r1, r1, asr #0x8
	str r1, [sp, #0x9c]
	add r1, sp, #0x94
	mov r2, r9
	bl FUN_0208FDA8
	b _0208F87C
_0208F7A4:
	add r0, r7, #0x14
	bl FUN_02090AF4
_0208F7AC: ; 0x0208F7AC
	ldr r0, [r6, #0x0]
	mov r3, #0x800
	mla r2, r0, r4, r5
	str r2, [r6, #0x0]
	ldr r10, [r7, #0x14]
	ldr r0, [r9, #0x5c]
	mov r1, r2, lsr #0x17
	smull r11, r0, r10, r0
	adds r11, r11, r3
	mov r1, r1, lsl #0xc
	adc r10, r0, #0x0
	mov r0, r11, lsr #0xc
	sub r1, r1, #0x100000
	orr r0, r0, r10, lsl #0x14
	mov r1, r1, asr #0x8
	smull r10, r1, r0, r1
	adds r10, r10, r3
	adc r0, r1, #0x0
	mov r1, r10, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0xa0]
	mla r1, r2, r4, r5
	str r1, [r6, #0x0]
	mov r2, r1, lsr #0x17
	mov r2, r2, lsl #0xc
	sub r2, r2, #0x100000
	ldr r10, [r7, #0x18]
	ldr r0, [r9, #0x5c]
	mov r2, r2, asr #0x8
	smull r11, r0, r10, r0
	adds r11, r11, r3
	adc r10, r0, #0x0
	mov r0, r11, lsr #0xc
	orr r0, r0, r10, lsl #0x14
	smull r10, r2, r0, r2
	adds r3, r10, r3
	adc r0, r2, #0x0
	mov r2, r3, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	mla r0, r1, r4, r5
	str r0, [r6, #0x0]
	str r2, [sp, #0xa4]
	mov r1, r0, lsr #0x17
	ldr r2, [r9, #0x60]
	add r0, r7, #0x8
	mul r1, r2, r1
	sub r1, r1, r2, lsl #0x8
	mov r1, r1, asr #0x8
	str r1, [sp, #0xa8]
	add r1, sp, #0xa0
	mov r2, r9
	bl FUN_0208FDA8
_0208F87C:
	ldr r1, [r6, #0x0]
	mla r0, r1, r4, r5
	str r0, [r6, #0x0]
	ldrb r2, [r8, #0x42]
	mov r1, r0, lsr #0x18
	ldr r3, [r9, #0x64]
	mul r1, r2, r1
	add r2, r2, #0xff
	sub r1, r2, r1, asr #0x7
	mul r1, r3, r1
	mov r1, r1, asr #0x8
	str r1, [sp, #0x10]
	mla r1, r0, r4, r5
	str r1, [r6, #0x0]
	mov r0, r1, lsr #0x18
	ldrb r2, [r8, #0x42]
	ldr r3, [r9, #0x68]
	ldr r1, [r8, #0x0]
	mul r0, r2, r0
	add r2, r2, #0xff
	sub r0, r2, r0, asr #0x7
	mul r0, r3, r0
	mov r0, r0, asr #0x8
	str r0, [sp, #0x14]
	mov r0, r1, lsl #0x1c
	mov r0, r0, lsr #0x1c
	cmp r0, #0x6
	bne _0208F9C8
	ldrsh r0, [r9, #0x84]
	ldr r1, [r7, #0x14]
	mov r2, #0x800
	smull r3, r0, r1, r0
	adds r1, r3, r2
	ldrsh r3, [r9, #0x8a]
	ldr lr, [r7, #0x18]
	mov r12, r1, lsr #0xc
	smull r10, r3, lr, r3
	adc r0, r0, #0x0
	adds r10, r10, r2
	orr r12, r12, r0, lsl #0x14
	adc r3, r3, #0x0
	mov r10, r10, lsr #0xc
	orr r10, r10, r3, lsl #0x14
	add r3, r12, r10
	str r3, [sp, #0xb8]
	ldrsh r10, [r9, #0x86]
	ldr r3, [r7, #0x14]
	ldrsh lr, [r9, #0x8c]
	smull r12, r10, r3, r10
	adds r12, r12, r2
	ldr r11, [r7, #0x18]
	adc r10, r10, #0x0
	smull r3, lr, r11, lr
	mov r12, r12, lsr #0xc
	adds r3, r3, r2
	orr r12, r12, r10, lsl #0x14
	adc r10, lr, #0x0
	mov r3, r3, lsr #0xc
	orr r3, r3, r10, lsl #0x14
	add r3, r12, r3
	str r3, [sp, #0xbc]
	ldr r10, [r7, #0x18]
	ldrsh r11, [r9, #0x88]
	ldr r3, [r7, #0x14]
	str r10, [sp, #0x28]
	smull r12, r11, r3, r11
	ldrsh r10, [r9, #0x8e]
	ldr r3, [sp, #0x28]
	adds r12, r12, r2
	smull r10, lr, r3, r10
	adc r3, r11, #0x0
	adds r2, r10, r2
	mov r10, r12, lsr #0xc
	orr r10, r10, r3, lsl #0x14
	adc r3, lr, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r3, lsl #0x14
	add r2, r10, r2
	add r0, sp, #0xb8
	add r1, sp, #0xac
	str r2, [sp, #0xc0]
	bl VEC_Normalize
	b _0208FA04
_0208F9C8:
	ldr r0, [r7, #0x8]
	cmp r0, #0x0
	bne _0208F9F8
	ldr r0, [r7, #0xc]
	cmp r0, #0x0
	bne _0208F9F8
	ldr r0, [r7, #0x10]
	cmp r0, #0x0
	bne _0208F9F8
	add r0, sp, #0xac
	bl FUN_02090B50
	b _0208FA04
_0208F9F8:
	add r0, r7, #0x8
	add r1, sp, #0xac
	bl VEC_Normalize
_0208FA04:
	ldr r2, [sp, #0xac]
	ldr r1, [sp, #0x10]
	mov r0, #0x800
	smull r10, r1, r2, r1
	adds r2, r10, r0
	add r10, r9, #0x28
	str r10, [sp, #0x2c]
	add r10, r7, #0x38
	str r10, [sp, #0x30]
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	ldrsh r1, [r9, #0x50]
	ldr r10, [sp, #0x14]
	ldr r3, [r9, #0x40]
	smull r11, r10, r1, r10
	adds r11, r11, r0
	adc r1, r10, #0x0
	mov r10, r11, lsr #0xc
	orr r10, r10, r1, lsl #0x14
	add r1, r2, r10
	add r1, r3, r1
	str r1, [r7, #0x14]
	ldr r3, [sp, #0xb0]
	ldr r1, [sp, #0x10]
	ldrsh r10, [r9, #0x52]
	smull r11, r1, r3, r1
	adds r11, r11, r0
	adc r3, r1, #0x0
	mov r1, r11, lsr #0xc
	orr r1, r1, r3, lsl #0x14
	ldr r3, [sp, #0x14]
	ldr r2, [r9, #0x44]
	smull r11, r3, r10, r3
	adds r10, r11, r0
	adc r3, r3, #0x0
	mov r10, r10, lsr #0xc
	orr r10, r10, r3, lsl #0x14
	add r1, r1, r10
	add r1, r2, r1
	str r1, [r7, #0x18]
	ldr r1, [sp, #0xb4]
	ldr r2, [sp, #0x10]
	ldrsh lr, [r9, #0x54]
	smull r10, r3, r1, r2
	ldr r1, [sp, #0x14]
	adds r10, r10, r0
	smull r2, r1, lr, r1
	adc r3, r3, #0x0
	adds r0, r2, r0
	mov r2, r10, lsr #0xc
	orr r2, r2, r3, lsl #0x14
	adc r1, r1, #0x0
	mov r0, r0, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	ldr r12, [r9, #0x48]
	add r0, r2, r0
	add r0, r12, r0
	str r0, [r7, #0x1c]
	ldr r0, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	ldr r0, [r6, #0x0]
	mla r1, r0, r4, r5
	str r1, [r6, #0x0]
	mov r0, r1, lsr #0x18
	ldrb r1, [r8, #0x40]
	ldr r2, [r9, #0x6c]
	mul r0, r1, r0
	add r1, r1, #0xff
	sub r0, r1, r0, asr #0x7
	mul r0, r2, r0
	mov r0, r0, asr #0x8
	str r0, [r7, #0x30]
	ldr r0, [sp, #0x34]
	strh r0, [r7, #0x34]
	ldr r0, [r8, #0x0]
	mov r0, r0, lsl #0x16
	movs r0, r0, lsr #0x1f
	beq _0208FBBC
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0x8]
	ldrh r0, [r0, #0x8]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	beq _0208FBBC
	ldr r0, [r6, #0x0]
	ldr r3, _0208FD9C ; =0x00000003
	mla r1, r0, r4, r5
	str r1, [r6, #0x0]
	mov r0, r1, lsr #0x14
	ldr r1, [sp, #0x4]
	ldr r2, [r1, #0x8]
	ldr r1, _0208FDA0 ; =0xAAAAAAAB
	umull r1, r10, r0, r1
	mov r10, r10, lsr #0x1
	umull r10, r11, r3, r10
	ldrh r1, [r2, #0x0]
	sub r10, r0, r10
	strh r1, [sp, #0x50]
	ldrh r0, [r8, #0x22]
	mov r1, r10, lsl #0x1
	strh r0, [sp, #0x52]
	ldrh r0, [r2, #0x2]
	strh r0, [sp, #0x54]
	add r0, sp, #0x50
	ldrh r0, [r0, r1]
	strh r0, [r7, #0x36]
	b _0208FBC4
_0208FBBC:
	ldrh r0, [r8, #0x22]
	strh r0, [r7, #0x36]
_0208FBC4:
	ldrh r1, [r7, #0x2e]
	ldrb r0, [r9, #0x81]
	bic r1, r1, #0x1f
	and r0, r0, #0x1f
	orr r0, r1, r0
	strh r0, [r7, #0x2e]
	ldrh r0, [r7, #0x2e]
	bic r0, r0, #0x3e0
	orr r0, r0, #0x3e0
	strh r0, [r7, #0x2e]
	ldr r0, [r8, #0x0]
	mov r0, r0, lsl #0x12
	movs r0, r0, lsr #0x1f
	ldrne r0, [r6, #0x0]
	mlane r1, r0, r4, r5
	strne r1, [r6, #0x0]
	strneh r1, [r7, #0x20]
	ldreqh r0, [r9, #0x56]
	streqh r0, [r7, #0x20]
	ldr r0, [r8, #0x0]
	mov r0, r0, lsl #0x13
	movs r0, r0, lsr #0x1f
	ldreq r0, [sp, #0x38]
	streqh r0, [r7, #0x22]
	beq _0208FC54
	ldr r0, [r6, #0x0]
	mla r1, r0, r4, r5
	str r1, [r6, #0x0]
	mov r0, r1, lsr #0x14
	ldrsh r2, [r8, #0x34]
	ldrsh r1, [r8, #0x36]
	sub r1, r1, r2
	mul r0, r1, r0
	add r0, r0, r2, lsl #0xc
	mov r0, r0, lsr #0xc
	strh r0, [r7, #0x22]
_0208FC54:
	ldr r0, [r6, #0x0]
	mla r1, r0, r4, r5
	str r1, [r6, #0x0]
	mov r0, r1, lsr #0x18
	ldrb r1, [r8, #0x41]
	ldrh r2, [r9, #0x70]
	mul r0, r1, r0
	mov r0, r0, asr #0x8
	rsb r0, r0, #0xff
	mul r0, r2, r0
	mov r0, r0, asr #0x8
	add r0, r0, #0x1
	strh r0, [r7, #0x24]
	ldr r0, [sp, #0x3c]
	strh r0, [r7, #0x26]
	ldr r0, [r8, #0x0]
	mov r0, r0, lsl #0x14
	movs r1, r0, lsr #0x1f
	beq _0208FCE4
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0x10]
	ldr r0, [r0, #0x8]
	mov r0, r0, lsl #0xf
	movs r0, r0, lsr #0x1f
	beq _0208FCE4
	ldr r0, [r6, #0x0]
	mla r1, r0, r4, r5
	str r1, [r6, #0x0]
	mov r0, r1, lsr #0x14
	ldr r1, [sp, #0x4]
	ldr r10, [r1, #0x10]
	ldrb r1, [r10, #0x8]
	bl _u32_div_f
	ldrb r0, [r10, r1]
	strb r0, [r7, #0x2c]
	b _0208FD14
_0208FCE4:
	cmp r1, #0x0
	beq _0208FD0C
	ldr r0, [sp, #0x4]
	ldr r1, [r0, #0x10]
	ldr r0, [r1, #0x8]
	mov r0, r0, lsl #0xf
	movs r0, r0, lsr #0x1f
	ldreqb r0, [r1, #0x0]
	streqb r0, [r7, #0x2c]
	beq _0208FD14
_0208FD0C:
	ldrb r0, [r8, #0x47]
	strb r0, [r7, #0x2c]
_0208FD14:
	ldr r1, [sp, #0x4]
	ldr r0, _0208FDA4 ; =0x0000FFFF
	ldr r1, [r1, #0x0]
	ldrb r1, [r1, #0x48]
	bl _s32_div_f
	strh r0, [r7, #0x28]
	ldrh r1, [r7, #0x24]
	ldr r0, _0208FDA4 ; =0x0000FFFF
	bl _s32_div_f
	strh r0, [r7, #0x2a]
	ldr r0, [sp, #0x40]
	strb r0, [r7, #0x2d]
	ldr r0, [r8, #0x0]
	mov r0, r0, lsl #0xb
	movs r0, r0, lsr #0x1f
	ldrne r0, [r6, #0x0]
	mlane r1, r0, r4, r5
	strne r1, [r6, #0x0]
	movne r0, r1, lsr #0x18
	strneb r0, [r7, #0x2d]
	ldr r0, [sp, #0x8]
	add r1, r0, #0x1
	ldr r0, [sp, #0xc]
	str r1, [sp, #0x8]
	cmp r1, r0
	blt _0208F13C
	add sp, sp, #0xc4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0208FD88: .word 0x00000FFF
_0208FD8C: .word 0x021C8C5C
_0208FD90: .word 0x5EEDF715
_0208FD94: .word 0x1B0CB173
_0208FD98: .word 0x020FFA38
_0208FD9C: .word 0x00000003
_0208FDA0: .word 0xAAAAAAAB
_0208FDA4: .word 0x0000FFFF

	arm_func_start FUN_0208FDA8
FUN_0208FDA8: ; 0x0208FDA8
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r4, r2
	mov r6, r0
	mov r5, r1
	add r2, sp, #0x0
	add r0, r4, #0x84
	add r1, r4, #0x8a
	bl VEC_Fx16CrossProduct
_0208FDCC: ; 0x0208FDCC
	add r0, sp, #0x0
	mov r1, r0
	bl VEC_Fx16Normalize
	ldrsh r1, [sp, #0x0]
	ldr lr, [r5, #0x8]
	ldrsh r0, [r4, #0x84]
	ldr r12, [r5, #0x0]
	smull r3, r2, lr, r1
	smull r1, r0, r12, r0
	ldrsh r7, [r4, #0x8a]
	ldr r8, [r5, #0x4]
	mov r12, #0x800
	smull lr, r7, r8, r7
	adds r8, r3, r12
	adc r3, r2, #0x0
	mov r2, r8, lsr #0xc
	adds r1, r1, r12
	orr r2, r2, r3, lsl #0x14
	adc r0, r0, #0x0
	mov r3, r1, lsr #0xc
	adds r1, lr, r12
	orr r3, r3, r0, lsl #0x14
	adc r0, r7, #0x0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	add r0, r3, r1
	add r0, r2, r0
	str r0, [r6, #0x0]
	ldrsh r0, [sp, #0x2]
	ldr r1, [r5, #0x8]
	ldrsh r3, [r4, #0x86]
	smull r2, r0, r1, r0
	adds r2, r2, r12
	ldr lr, [r5, #0x0]
	adc r1, r0, #0x0
	mov r0, r2, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	smull r8, r7, lr, r3
	ldrsh r1, [r4, #0x8c]
	ldr r2, [r5, #0x4]
	adds r8, r8, r12
	smull r3, r1, r2, r1
	adc r2, r7, #0x0
	mov r7, r8, lsr #0xc
	orr r7, r7, r2, lsl #0x14
	adds r2, r3, r12
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	add r1, r7, r2
	add r0, r0, r1
	str r0, [r6, #0x4]
	ldrsh r0, [sp, #0x4]
	ldr r1, [r5, #0x8]
	ldr lr, [r5, #0x0]
	smull r3, r0, r1, r0
	adds r3, r3, r12
	adc r1, r0, #0x0
	mov r0, r3, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	ldrsh r3, [r4, #0x88]
	ldrsh r1, [r4, #0x8e]
	ldr r2, [r5, #0x4]
	smull r5, r4, lr, r3
	adds r5, r5, r12
	smull r3, r1, r2, r1
	adc r4, r4, #0x0
	adds r2, r3, r12
	mov r3, r5, lsr #0xc
	adc r1, r1, #0x0
	mov r2, r2, lsr #0xc
	orr r3, r3, r4, lsl #0x14
	orr r2, r2, r1, lsl #0x14
	add r1, r3, r2
	add r0, r0, r1
	str r0, [r6, #0x8]
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_0208FF08
FUN_0208FF08: ; 0x0208FF08
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x10
	ldr r1, _0209018C ; =0x02106168
	mov r4, r0
	ldrh r3, [r1, #0x0]
	ldrh r2, [r1, #0x2]
	ldrh r0, [r1, #0x4]
	strh r3, [sp, #0x0]
	strh r2, [sp, #0x2]
	strh r0, [sp, #0x4]
	ldr r0, [r4, #0x20]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x18
	movs r0, r0, lsr #0x1e
	beq _0208FF88
	cmp r0, #0x1
	beq _0208FF70
	cmp r0, #0x2
	bne _0208FFA0
	mov r0, #0x0
	mov r1, #0x1000
	strh r1, [sp, #0x6]
	strh r0, [sp, #0x8]
	strh r0, [sp, #0xa]
	b _0208FFAC
_0208FF70:
	mov r1, #0x0
	mov r0, #0x1000
	strh r1, [sp, #0x6]
	strh r0, [sp, #0x8]
	strh r1, [sp, #0xa]
	b _0208FFAC
_0208FF88:
	mov r1, #0x0
	mov r0, #0x1000
	strh r1, [sp, #0x6]
	strh r1, [sp, #0x8]
	strh r0, [sp, #0xa]
	b _0208FFAC
_0208FFA0:
	add r1, sp, #0x6
	add r0, r4, #0x50
	bl VEC_Fx16Normalize
_0208FFAC:
	add r0, sp, #0x0
	add r1, sp, #0x6
	bl VEC_Fx16DotProduct
	cmp r0, #0x1000
	beq _0208FFD0
	mov r1, #0x1000
	rsb r1, r1, #0x0
	cmp r0, r1
	bne _0208FFE4
_0208FFD0:
	mov r0, #0x0
	mov r1, #0x1000
	strh r1, [sp, #0x0]
	strh r0, [sp, #0x2]
	strh r0, [sp, #0x4]
_0208FFE4:
	ldrsh r3, [sp, #0x8]
	ldrsh r1, [sp, #0x4]
	ldrsh r2, [sp, #0xa]
	ldrsh r0, [sp, #0x2]
	smull r6, r5, r3, r1
	mov r1, #0x800
	adds r6, r6, r1
	smull r3, r0, r2, r0
	adc r5, r5, #0x0
	adds r2, r3, r1
	mov r3, r6, lsr #0xc
	adc r0, r0, #0x0
	mov r2, r2, lsr #0xc
	orr r3, r3, r5, lsl #0x14
	orr r2, r2, r0, lsl #0x14
	sub r0, r3, r2
	strh r0, [r4, #0x84]
	ldrsh r5, [sp, #0xa]
	ldrsh r3, [sp, #0x0]
	ldrsh r2, [sp, #0x6]
	ldrsh r0, [sp, #0x4]
	smull r3, r6, r5, r3
	adds r12, r3, r1
	smull r3, r0, r2, r0
	adc r5, r6, #0x0
	adds r2, r3, r1
	mov r3, r12, lsr #0xc
	adc r0, r0, #0x0
	mov r2, r2, lsr #0xc
	orr r3, r3, r5, lsl #0x14
	orr r2, r2, r0, lsl #0x14
	sub r0, r3, r2
	strh r0, [r4, #0x86]
	ldrsh r5, [sp, #0x6]
	ldrsh r3, [sp, #0x2]
	ldrsh r2, [sp, #0x8]
	ldrsh r0, [sp, #0x0]
	smull r3, r6, r5, r3
	adds r12, r3, r1
	smull r3, r0, r2, r0
	adc r5, r6, #0x0
	adds r2, r3, r1
	mov r3, r12, lsr #0xc
	adc r0, r0, #0x0
	mov r2, r2, lsr #0xc
	orr r3, r3, r5, lsl #0x14
	orr r2, r2, r0, lsl #0x14
	sub r0, r3, r2
	strh r0, [r4, #0x88]
	ldrsh r6, [sp, #0x8]
	ldrsh r5, [r4, #0x88]
	add r0, r4, #0x84
	ldrsh r3, [sp, #0xa]
	ldrsh r2, [r4, #0x86]
	smull r5, r12, r6, r5
	adds lr, r5, r1
	smull r5, r2, r3, r2
	adc r6, r12, #0x0
	adds r3, r5, r1
	mov r5, lr, lsr #0xc
	adc r2, r2, #0x0
	mov r3, r3, lsr #0xc
	orr r5, r5, r6, lsl #0x14
	orr r3, r3, r2, lsl #0x14
	sub r2, r5, r3
	strh r2, [r4, #0x8a]
	ldrsh r6, [sp, #0xa]
	ldrsh r5, [r4, #0x84]
	ldrsh r3, [sp, #0x6]
	ldrsh r2, [r4, #0x88]
	smull lr, r12, r6, r5
	smull r5, r2, r3, r2
	adds r6, lr, r1
	adc r3, r12, #0x0
	mov r6, r6, lsr #0xc
	orr r6, r6, r3, lsl #0x14
	adds r3, r5, r1
	adc r2, r2, #0x0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	sub r2, r6, r3
	strh r2, [r4, #0x8c]
	ldrsh lr, [sp, #0x6]
	ldrsh r12, [r4, #0x86]
	ldrsh r3, [sp, #0x8]
	ldrsh r2, [r4, #0x84]
	smull r6, r5, lr, r12
	smull r12, r2, r3, r2
	adds r6, r6, r1
	adc r5, r5, #0x0
	adds r3, r12, r1
	mov r6, r6, lsr #0xc
	orr r6, r6, r5, lsl #0x14
	adc r1, r2, #0x0
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	sub r1, r6, r2
	strh r1, [r4, #0x8e]
	mov r1, r0
	bl VEC_Fx16Normalize
	add r0, r4, #0x8a
	mov r1, r0
	bl VEC_Fx16Normalize
	add sp, sp, #0x10
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209018C: .word 0x02106168

	arm_func_start FUN_02090190
FUN_02090190: ; 0x02090190
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	rsb r2, r2, #0xff
	mov r1, #0x1f
	mul r3, r2, r1
	ldr r2, _020901E4 ; =0x80808081
	ldrh lr, [r0, #0x2e]
	smull r1, r12, r2, r3
	add r12, r3, r12
	mov r12, r12, asr #0x7
	mov r1, r3, lsr #0x1f
	add r12, r1, r12
	mov r1, r12, lsl #0x10
	mov r1, r1, lsr #0x10
	bic r2, lr, #0x3e0
	and r1, r1, #0x1f
	orr r1, r2, r1, lsl #0x5
	strh r1, [r0, #0x2e]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020901E4: .word 0x80808081

	arm_func_start FUN_020901E8
FUN_020901E8: ; 0x020901E8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r1, #0x14]
	sub r1, r2, #0xff
	ldrsh lr, [r3, #0x4]
	ldr r2, _02090230 ; =0x80808081
	sub r3, lr, #0x1000
	mul r12, r3, r1
	smull r1, r3, r2, r12
	add r3, r12, r3
	mov r3, r3, asr #0x7
	mov r1, r12, lsr #0x1f
	add r3, r1, r3
	add r1, lr, r3
	strh r1, [r0, #0x34]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02090230: .word 0x80808081

	arm_func_start FUN_02090234
FUN_02090234: ; 0x02090234
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, [r1, #0x10]
	mov r4, #0x0
	ldrb r3, [r5, #0x8]
	cmp r3, #0x0
	addle sp, sp, #0x4
	ldmleia sp!, {r4-r5,lr}
	bxle lr
	ldrb r12, [r5, #0x9]
	mov lr, r4
_02090260:
	add r1, lr, r12
	cmp r2, r1
	ldrltb r1, [r5, r4]
	addlt sp, sp, #0x4
	strltb r1, [r0, #0x2c]
	ldmltia sp!, {r4-r5,lr}
	bxlt lr
	add r4, r4, #0x1
	cmp r4, r3
	add lr, lr, r12
	blt _02090260
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02090298
FUN_02090298: ; 0x02090298
	stmdb sp!, {r4-r6,lr}
	ldr r4, [r1, #0xc]
	mov r5, r0
	ldrb r1, [r4, #0x4]
	ldrb r3, [r4, #0x5]
	cmp r2, r1
	bge _020902D8
	ldrh r3, [r4, #0x0]
	mov r0, r3, lsl #0x16
	mov r6, r3, lsl #0x1b
	mov r0, r0, lsr #0x1b
	sub r0, r0, r6, lsr #0x1b
	mul r0, r2, r0
	bl _s32_div_f
	add r0, r0, r6, lsr #0x1b
	b _02090314
_020902D8:
	cmp r2, r3
	ldrlth r0, [r4, #0x0]
	movlt r0, r0, lsl #0x16
	movlt r0, r0, lsr #0x1b
	blt _02090314
	ldrh r0, [r4, #0x0]
	sub r2, r2, #0xff
	rsb r1, r3, #0xff
	mov r6, r0, lsl #0x11
	mov r3, r6, lsr #0x1b
	mov r0, r0, lsl #0x16
	sub r0, r3, r0, lsr #0x1b
	mul r0, r2, r0
	bl _s32_div_f
	add r0, r0, r6, lsr #0x1b
_02090314:
	ldr r3, _02090368 ; =0x021C8C5C
	ldr r1, _0209036C ; =0x5EEDF715
	ldr r12, [r3, #0x0]
	ldr r2, _02090370 ; =0x1B0CB173
	mla r1, r12, r1, r2
	str r1, [r3, #0x0]
	ldrb r2, [r4, #0x2]
	mov r1, r1, lsr #0x18
	ldrh r3, [r5, #0x2e]
	mul r1, r2, r1
	mov r1, r1, asr #0x8
	rsb r1, r1, #0xff
	mul r1, r0, r1
	mov r0, r1, lsl #0x8
	mov r0, r0, lsr #0x10
	bic r1, r3, #0x3e0
	and r0, r0, #0x1f
	orr r0, r1, r0, lsl #0x5
	strh r0, [r5, #0x2e]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_02090368: .word 0x021C8C5C
_0209036C: .word 0x5EEDF715
_02090370: .word 0x1B0CB173

	arm_func_start FUN_02090374
FUN_02090374: ; 0x02090374
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4

	arm_func_start FUN_0209037C
FUN_0209037C: ; 0x0209037C
	ldr r4, [r1, #0x8]
	mov r10, r0
	ldrb r3, [r4, #0x4]
	ldr r0, [r1, #0x0]
	ldrb r1, [r4, #0x5]
	cmp r2, r3
	ldrb r11, [r4, #0x6]
	ldrlth r0, [r4, #0x0]
	addlt sp, sp, #0x4
	strlth r0, [r10, #0x36]
	ldmltia sp!, {r4-r11,lr}
	bxlt lr
	cmp r2, r1
	bge _0209046C
	ldrh r9, [r0, #0x22]
	ldrh r0, [r4, #0x8]
	ldrh r8, [r4, #0x0]
	mov r7, r9, asr #0x5
	mov r11, r9, asr #0xa
	mov r4, r0, lsl #0x1d
	mov r6, r8, asr #0x5
	mov r5, r8, asr #0xa
	movs r4, r4, lsr #0x1f
	and r9, r9, #0x1f
	and r7, r7, #0x1f
	and r0, r11, #0x1f
	orreq r1, r9, r7, lsl #0x5
	orreq r0, r1, r0, lsl #0xa
	and r8, r8, #0x1f
	and r6, r6, #0x1f
	and r5, r5, #0x1f
	addeq sp, sp, #0x4
	streqh r0, [r10, #0x36]
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	sub r4, r2, r3
	sub r0, r0, r5
	mul r0, r4, r0
	sub r11, r1, r3
	mov r1, r11
	bl _s32_div_f
	sub r1, r9, r8
	mov r9, r0
	mul r0, r4, r1
	mov r1, r11
	bl _s32_div_f
	sub r1, r7, r6
	mov r7, r0
	mul r0, r4, r1
	mov r1, r11
	bl _s32_div_f
	add r1, r8, r7
	add r0, r6, r0
	add r2, r5, r9
	orr r0, r1, r0, lsl #0x5
	orr r0, r0, r2, lsl #0xa
	add sp, sp, #0x4
	strh r0, [r10, #0x36]
	ldmia sp!, {r4-r11,lr}
	bx lr
_0209046C:
	cmp r2, r11
	bge _0209052C
	ldrh r7, [r4, #0x2]
	ldrh r8, [r0, #0x22]
	ldrh r0, [r4, #0x8]
	mov r5, r7, asr #0x5
	mov r4, r7, asr #0xa
	mov r3, r0, lsl #0x1d
	mov r6, r8, asr #0x5
	mov r9, r8, asr #0xa
	movs r3, r3, lsr #0x1f
	and r7, r7, #0x1f
	and r5, r5, #0x1f
	and r0, r4, #0x1f
	orreq r1, r7, r5, lsl #0x5
	orreq r0, r1, r0, lsl #0xa
	and r8, r8, #0x1f
	and r6, r6, #0x1f
	and r9, r9, #0x1f
	addeq sp, sp, #0x4
	streqh r0, [r10, #0x36]
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	sub r4, r2, r1
	sub r0, r0, r9
	mul r0, r4, r0
	sub r11, r11, r1
	mov r1, r11
	bl _s32_div_f
	sub r1, r7, r8
	mov r7, r0
	mul r0, r4, r1
	mov r1, r11
	bl _s32_div_f
	sub r1, r5, r6
	mov r5, r0
	mul r0, r4, r1
	mov r1, r11
	bl _s32_div_f
	add r1, r8, r5
	add r0, r6, r0
	add r2, r9, r7
	orr r0, r1, r0, lsl #0x5
	orr r0, r0, r2, lsl #0xa
	add sp, sp, #0x4
	strh r0, [r10, #0x36]
	ldmia sp!, {r4-r11,lr}
	bx lr
_0209052C:
	ldrh r0, [r4, #0x2]
	strh r0, [r10, #0x36]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02090540
FUN_02090540: ; 0x02090540
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r12, [r1, #0x4]
	mov r4, r0
	ldrb r1, [r12, #0x6]
	ldrb r3, [r12, #0x7]
	cmp r2, r1
	bge _02090588
	ldrsh r5, [r12, #0x0]
	ldrsh r0, [r12, #0x2]
	sub r0, r0, r5
	mul r0, r2, r0
	bl _s32_div_f
_02090574: ; 0x02090574
	add r0, r5, r0
	add sp, sp, #0x4
	strh r0, [r4, #0x34]
	ldmia sp!, {r4-r5,lr}
	bx lr
_02090588:
	cmp r2, r3
	ldrltsh r0, [r12, #0x2]
	addlt sp, sp, #0x4
	strlth r0, [r4, #0x34]
	ldmltia sp!, {r4-r5,lr}
	bxlt lr
	ldrsh r5, [r12, #0x4]
	ldrsh r0, [r12, #0x2]
	sub r2, r2, #0xff
	rsb r1, r3, #0xff
	sub r0, r5, r0
	mul r0, r2, r0
	bl _s32_div_f
_020905BC: ; 0x020905BC
	add r0, r5, r0
	strh r0, [r4, #0x34]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020905D0
FUN_020905D0: ; 0x020905D0
	stmdb sp!, {r4,lr}
	ldr lr, [r1, #0x8]
	ldr r2, [r0, #0x0]
	ldrsh r4, [r0, #0xc]
	sub r3, r2, lr
	mov r2, #0x800
	smull r12, r3, r4, r3
	adds r4, r12, r2
	adc r3, r3, #0x0
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	add r3, lr, r4
	str r3, [r1, #0x8]
	ldr r4, [r1, #0xc]
	ldr r3, [r0, #0x4]
	ldrsh r12, [r0, #0xc]
	sub r3, r3, r4
	smull lr, r3, r12, r3
	adds r12, lr, r2
	adc r3, r3, #0x0
	mov r12, r12, lsr #0xc
	orr r12, r12, r3, lsl #0x14
	add r3, r4, r12
	str r3, [r1, #0xc]
	ldr lr, [r1, #0x10]
	ldr r3, [r0, #0x8]
	ldrsh r12, [r0, #0xc]
	sub r0, r3, lr
	smull r3, r0, r12, r0
	adds r2, r3, r2
	adc r0, r0, #0x0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	add r0, lr, r2
	str r0, [r1, #0x10]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02090664
FUN_02090664: ; 0x02090664
	ldr r3, [r3, #0x74]
	ldr r2, [r0, #0x0]
	cmp r3, #0x80000000
	movne r2, r3
	ldrh r3, [r0, #0x6]
	mov r3, r3, lsl #0x1e
	movs r3, r3, lsr #0x1e
	beq _02090690
	cmp r3, #0x1
	beq _020906E4
	bx lr
_02090690:
	ldr r3, [r1, #0x3c]
	cmp r3, r2
	bge _020906BC
	ldr r0, [r1, #0xc]
	add r0, r3, r0
	cmp r0, r2
	subgt r0, r2, r3
	strgt r0, [r1, #0xc]
	ldrgth r0, [r1, #0x24]
	strgth r0, [r1, #0x26]
	bxgt lr
_020906BC:
	cmp r3, r2
	bxlt lr
	ldr r0, [r1, #0xc]
	add r0, r3, r0
	cmp r0, r2
	sublt r0, r2, r3
	strlt r0, [r1, #0xc]
	ldrlth r0, [r1, #0x24]
	strlth r0, [r1, #0x26]
	bx lr
_020906E4:
	ldr r12, [r1, #0x3c]
	cmp r12, r2
	bge _02090734
	ldr r3, [r1, #0xc]
	add r3, r12, r3
	cmp r3, r2
	ble _02090734
	sub r2, r2, r12
	str r2, [r1, #0xc]
	ldrsh r2, [r0, #0x4]
	ldr r3, [r1, #0x18]
	mov r0, #0x800
	smull r12, r2, r3, r2
	adds r3, r12, r0
	adc r0, r2, #0x0
	mov r2, r3, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	rsb r0, r2, #0x0
	str r0, [r1, #0x18]
	bx lr
_02090734:
	cmp r12, r2
	bxlt lr
	ldr r3, [r1, #0xc]
	add r3, r12, r3
	cmp r3, r2
	bxge lr
	sub r2, r2, r12
	str r2, [r1, #0xc]
	ldrsh r2, [r0, #0x4]
	ldr r3, [r1, #0x18]
	mov r0, #0x800
	smull r12, r2, r3, r2
	adds r3, r12, r0
	adc r0, r2, #0x0
	mov r2, r3, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	rsb r0, r2, #0x0
	str r0, [r1, #0x18]
	bx lr

	arm_func_start FUN_02090780
FUN_02090780: ; 0x02090780
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x28
	ldrh r2, [r0, #0x2]
	mov r4, r1
	cmp r2, #0x0
	beq _020907AC
	cmp r2, #0x1
	beq _020907DC
	cmp r2, #0x2
	beq _0209080C
	b _02090838
_020907AC:
	ldrh r1, [r0, #0x0]
	ldr r3, _02090854 ; =0x020FFA38
	add r0, sp, #0x0
	mov r1, r1, asr #0x4
	mov r2, r1, lsl #0x1
	add r1, r2, #0x1
	mov r12, r2, lsl #0x1
	mov r2, r1, lsl #0x1
	ldrsh r1, [r3, r12]
	ldrsh r2, [r3, r2]
	blx MTX_RotX33_
	b _02090838
_020907DC:
	ldrh r1, [r0, #0x0]
	ldr r3, _02090854 ; =0x020FFA38
	add r0, sp, #0x0
	mov r1, r1, asr #0x4
	mov r2, r1, lsl #0x1
	add r1, r2, #0x1
	mov r12, r2, lsl #0x1
	mov r2, r1, lsl #0x1
	ldrsh r1, [r3, r12]
	ldrsh r2, [r3, r2]
	blx MTX_RotY33_
	b _02090838
_0209080C:
	ldrh r1, [r0, #0x0]
	ldr r3, _02090854 ; =0x020FFA38
	add r0, sp, #0x0
	mov r1, r1, asr #0x4
	mov r2, r1, lsl #0x1
	add r1, r2, #0x1
	mov r12, r2, lsl #0x1
	mov r2, r1, lsl #0x1
	ldrsh r1, [r3, r12]
	ldrsh r2, [r3, r2]
	blx MTX_RotZ33_
_02090838:
	add r0, r4, #0x8
	add r1, sp, #0x0
	mov r2, r0
	bl MTX_MultVec33
	add sp, sp, #0x28
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02090854: .word 0x020FFA38

	arm_func_start FUN_02090858
FUN_02090858: ; 0x02090858
	stmdb sp!, {r4,lr}
	ldr r12, [r0, #0x0]
	ldr r4, [r1, #0x8]
	ldrsh lr, [r0, #0xc]
	ldr r3, [r1, #0x14]
	sub r4, r12, r4
	sub r3, r4, r3
	mul r3, lr, r3
	ldr r4, [r2, #0x0]
	add r3, r4, r3, asr #0xc
	str r3, [r2, #0x0]
	ldr lr, [r0, #0x4]
	ldr r12, [r1, #0xc]
	ldrsh r4, [r0, #0xc]
	ldr r3, [r1, #0x18]
	sub r12, lr, r12
	sub r3, r12, r3
	mul r3, r4, r3
	ldr r4, [r2, #0x4]
	add r3, r4, r3, asr #0xc
	str r3, [r2, #0x4]
	ldr r12, [r0, #0x8]
	ldr r3, [r1, #0x10]
	ldrsh lr, [r0, #0xc]
	ldr r0, [r1, #0x1c]
	sub r1, r12, r3
	sub r0, r1, r0
	mul r0, lr, r0
	ldr r1, [r2, #0x8]
	add r0, r1, r0, asr #0xc
	str r0, [r2, #0x8]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020908DC
FUN_020908DC: ; 0x020908DC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrh r0, [r1, #0x26]
	ldrh r1, [r5, #0x6]
	mov r4, r2
	bl _s32_div_f
_020908F8: ; 0x020908F8
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r2, _02090998 ; =0x021C8C5C
	ldr r0, _0209099C ; =0x5EEDF715
	ldr r3, [r2, #0x0]
	ldr r1, _020909A0 ; =0x1B0CB173
	mla r12, r3, r0, r1
	str r12, [r2, #0x0]
	ldrsh lr, [r5, #0x0]
	mov r3, r12, lsr #0x17
	ldr r12, [r4, #0x0]
	mul r3, lr, r3
	sub r3, r3, lr, lsl #0x8
	add r3, r12, r3, asr #0x8
	str r3, [r4, #0x0]
	ldr r3, [r2, #0x0]
	mla r12, r3, r0, r1
	str r12, [r2, #0x0]
	ldrsh lr, [r5, #0x2]
	mov r3, r12, lsr #0x17
	ldr r12, [r4, #0x4]
	mul r3, lr, r3
	sub r3, r3, lr, lsl #0x8
	add r3, r12, r3, asr #0x8
	str r3, [r4, #0x4]
	ldr r3, [r2, #0x0]
	mla r0, r3, r0, r1
	str r0, [r2, #0x0]
	ldrsh r2, [r5, #0x4]
	mov r0, r0, lsr #0x17
	ldr r1, [r4, #0x8]
	mul r0, r2, r0
	sub r0, r0, r2, lsl #0x8
	add r0, r1, r0, asr #0x8
	str r0, [r4, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02090998: .word 0x021C8C5C
_0209099C: .word 0x5EEDF715
_020909A0: .word 0x1B0CB173

	arm_func_start FUN_020909A4
FUN_020909A4: ; 0x020909A4
	ldrsh r1, [r0, #0x0]
	ldr r3, [r2, #0x0]
	add r1, r3, r1
	str r1, [r2, #0x0]
	ldrsh r1, [r0, #0x2]
	ldr r3, [r2, #0x4]
	add r1, r3, r1
	str r1, [r2, #0x4]
	ldrsh r0, [r0, #0x4]
	ldr r1, [r2, #0x8]
	add r0, r1, r0
	str r0, [r2, #0x8]
	bx lr

	arm_func_start FUN_020909D8
FUN_020909D8: ; 0x020909D8
	ldr r3, [r1, #0x0]
	cmp r3, #0x0
	bne _02090A18
	ldr r2, [r0, #0x0]
	cmp r2, r1
	moveq r2, #0x0
	streq r2, [r0, #0x0]
	streq r2, [r0, #0x8]
	beq _02090A44
	ldr r2, [r1, #0x4]
	mov r3, #0x0
	str r3, [r2, #0x0]
	ldr r2, [r0, #0x8]
	ldr r2, [r2, #0x4]
	str r2, [r0, #0x8]
	b _02090A44
_02090A18:
	ldr r2, [r0, #0x0]
	cmp r2, r1
	streq r3, [r0, #0x0]
	ldreq r2, [r0, #0x0]
	moveq r3, #0x0
	streq r3, [r2, #0x4]
	ldrne r2, [r1, #0x4]
	strne r2, [r3, #0x4]
	ldrne r3, [r1, #0x0]
	ldrne r2, [r1, #0x4]
	strne r3, [r2, #0x0]
_02090A44:
	ldr r2, [r0, #0x4]
	sub r2, r2, #0x1
	str r2, [r0, #0x4]
	mov r0, r1
	bx lr

	arm_func_start FUN_02090A58
FUN_02090A58: ; 0x02090A58
	ldr r2, [r0, #0x0]
	mov r3, #0x0
	mov r12, r3
	cmp r2, #0x0
	beq _02090A9C
	ldr r1, [r2, #0x0]
	mov r12, r2
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	ldrne r1, [r2, #0x0]
	strne r3, [r1, #0x4]
	streq r3, [r0, #0x0]
	streq r3, [r0, #0x8]
	ldr r1, [r0, #0x4]
	sub r1, r1, #0x1
	str r1, [r0, #0x4]
_02090A9C:
	mov r0, r12
	bx lr

	arm_func_start FUN_02090AA4
FUN_02090AA4:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	bne _02090ACC
	str r1, [r0, #0x0]
	str r1, [r0, #0x8]
	mov r2, #0x0
	str r2, [r1, #0x0]
	ldr r2, [r1, #0x0]
	str r2, [r1, #0x4]
	b _02090AE4
_02090ACC:
	str r2, [r1, #0x0]
	mov r2, #0x0
	str r2, [r1, #0x4]
	ldr r2, [r0, #0x0]
	str r1, [r2, #0x4]
	str r1, [r0, #0x0]
_02090AE4:
	ldr r1, [r0, #0x4]
	add r1, r1, #0x1
	str r1, [r0, #0x4]
	bx lr

	arm_func_start FUN_02090AF4
FUN_02090AF4:
	stmdb sp!, {r4,lr}
	ldr ip, _02090B44 ; =0x021C8C5C
	ldr r2, _02090B48 ; =0x5EEDF715
	ldr r4, [r12, #0x0]
	ldr r3, _02090B4C ; =0x1B0CB173
	mov r1, r0
	mla lr, r4, r2, r3
	str lr, [r12, #0x0]
	mov r4, lr, asr #0x8
	str r4, [r0, #0x0]
	ldr r4, [r12, #0x0]
	mov lr, #0x0
	mla r2, r4, r2, r3
	str r2, [r12, #0x0]
	mov r2, r2, asr #0x8
	str r2, [r0, #0x4]
	str lr, [r0, #0x8]
	bl VEC_Normalize
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02090B44: .word 0x021C8C5C
_02090B48: .word 0x5EEDF715
_02090B4C: .word 0x1B0CB173

	arm_func_start FUN_02090B50
FUN_02090B50: ; 0x02090B50
	stmdb sp!, {r4,lr}
	ldr ip, _02090BAC ; =0x021C8C5C
	ldr r2, _02090BB0 ; =0x5EEDF715
	ldr r4, [r12, #0x0]
	ldr r3, _02090BB4 ; =0x1B0CB173
	mov r1, r0
	mla lr, r4, r2, r3
	str lr, [r12, #0x0]
	mov r4, lr, asr #0x8
	str r4, [r0, #0x0]
	ldr lr, [r12, #0x0]
	mla r4, lr, r2, r3
	str r4, [r12, #0x0]
	mov lr, r4, asr #0x8
	str lr, [r0, #0x4]
	ldr lr, [r12, #0x0]
	mla r2, lr, r2, r3
	str r2, [r12, #0x0]
	mov r2, r2, asr #0x8
	str r2, [r0, #0x8]
	bl VEC_Normalize
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02090BAC: .word 0x021C8C5C
_02090BB0: .word 0x5EEDF715
_02090BB4: .word 0x1B0CB173

	arm_func_start FUN_02090BB8
FUN_02090BB8: ; 0x02090BB8
	bx lr

	arm_func_start FUN_02090BBC
FUN_02090BBC: ; 0x02090BBC
	stmdb sp!, {r4-r6,lr}
	mov r0, #0x10000
	rsb r0, r0, #0x0
	ldr r3, _02090CB8 ; =0x021C8C6C
	ldr r2, _02090CBC ; =0x021C8C68
	and r0, r1, r0
	cmp r0, #0x10000
	and r4, r1, #0xff
	ldr r6, [r3, #0x0]
	ldr r5, [r2, #0x0]
	beq _02090BF4
	cmp r0, #0x20000
	beq _02090C38
	b _02090C84
_02090BF4:
	cmp r4, #0x7
	bne _02090C84
	ldr r0, _02090CC0 ; =0x021C8C64
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02090C84
	ldr r1, _02090CC4 ; =0x021C8C60
	ldrh r2, [r1, #0x0]
	cmp r2, #0x0
	beq _02090C84
	ldrh r0, [r0, #0x0]
	ldrh r1, [r1, #0x0]
	bl OSi_UnlockVram
	ldr r0, _02090CC0 ; =0x021C8C64
	mov r1, #0x0
	strh r1, [r0, #0x0]
	b _02090C84
_02090C38:
	cmp r4, #0x0
	bne _02090C78
	ldr r0, _02090CC0 ; =0x021C8C64
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02090C78
	ldr r1, _02090CC4 ; =0x021C8C60
	ldrh r2, [r1, #0x0]
	cmp r2, #0x0
	beq _02090C78
	ldrh r0, [r0, #0x0]
	ldrh r1, [r1, #0x0]
	bl OSi_UnlockVram
	ldr r0, _02090CC0 ; =0x021C8C64
	mov r1, #0x0
	strh r1, [r0, #0x0]
_02090C78:
	mov r0, #0xf
	mov r1, #0x0
	bl PXI_SetFifoRecvCallback
_02090C84:
	cmp r6, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r3, _02090CB8 ; =0x021C8C6C
	mov r12, #0x0
	ldr r2, _02090CBC ; =0x021C8C68
	mov r0, r5
	mov r1, r4
	str r12, [r3, #0x0]
	str r12, [r2, #0x0]
	blx r6
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_02090CB8: .word 0x021C8C6C
_02090CBC: .word 0x021C8C68
_02090CC0: .word 0x021C8C64
_02090CC4: .word 0x021C8C60

	arm_func_start FUN_02090CC8
FUN_02090CC8: ; 0x02090CC8
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	bl PXI_Init
	mov r0, #0xf
	mov r1, #0x1
	bl PXI_IsCallbackReady
_02090CE4: ; 0x02090CE4
	cmp r0, #0x0
	moveq r0, #0x2
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	bl OS_DisableInterrupts
	ldr r1, _02090DA8 ; =0x021C8C6C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _02090D1C
	bl OS_RestoreInterrupts
	mov r0, #0x5
	ldmia sp!, {r4-r6,lr}
	bx lr
_02090D1C:
	mov r0, #0xf
	mov r1, #0x0
	bl PXI_IsCallbackReady
_02090D28: ; 0x02090D28
	cmp r0, #0x0
	bne _02090D3C
	ldr r1, _02090DAC ; =FUN_02090BBC
	mov r0, #0xf
	bl PXI_SetFifoRecvCallback
_02090D3C:
	cmp r6, #0x0
	ldreq r1, _02090DB0 ; =FUN_02090BB8
	ldreq r0, _02090DA8 ; =0x021C8C6C
	ldr r3, _02090DB4 ; =0x021C8C68
	streq r1, [r0, #0x0]
	ldrne r0, _02090DA8 ; =0x021C8C6C
	mov r1, #0x20000
	strne r6, [r0, #0x0]
	mov r0, #0xf
	mov r2, #0x0
	str r5, [r3, #0x0]
	bl PXI_SendWordByFifo
_02090D6C: ; 0x02090D6C
	cmp r0, #0x0
	bge _02090D94
	ldr r1, _02090DA8 ; =0x021C8C6C
	mov r2, #0x0
	mov r0, r4
	str r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	mov r0, #0x4
	ldmia sp!, {r4-r6,lr}
	bx lr
_02090D94:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_02090DA8: .word 0x021C8C6C
_02090DAC: .word FUN_02090BBC
_02090DB0: .word FUN_02090BB8
_02090DB4: .word 0x021C8C68

	arm_func_start FUN_02090DB8
FUN_02090DB8: ; 0x02090DB8
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl PXI_Init
	mov r0, #0xf
	mov r1, #0x1
	bl PXI_IsCallbackReady
_02090DD8: ; 0x02090DD8
	cmp r0, #0x0
	moveq r0, #0x2
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r8, _02091020 ; =0x021C8C60
	ldrh r0, [r8, #0x0]
	cmp r0, #0x0
	bne _02090E20
	mvn r4, #0x2
_02090DFC:
	bl OS_GetLockID
	cmp r0, r4
	moveq r0, #0x7
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	strh r0, [r8, #0x0]
	ldrh r0, [r8, #0x0]
	cmp r0, #0x0
	beq _02090DFC
_02090E20:
	bl OS_DisableInterrupts
	ldr r1, _02091024 ; =0x021C8C6C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _02090E48
	bl OS_RestoreInterrupts
	mov r0, #0x5
	ldmia sp!, {r4-r8,lr}
	bx lr
_02090E48:
	ldr r1, _02091028 ; =0x021C8C64
	ldrh r1, [r1, #0x0]
	cmp r1, #0x0
	beq _02090E68
	bl OS_RestoreInterrupts
	mov r0, #0x5
	ldmia sp!, {r4-r8,lr}
	bx lr
_02090E68:
	cmp r7, #0x4
	beq _02090E84
	cmp r7, #0x8
	beq _02090ECC
	cmp r7, #0xc
	beq _02090F14
	b _02090F68
_02090E84:
	ldr r1, _02091020 ; =0x021C8C60
	mov r0, #0x4
	ldrh r1, [r1, #0x0]
	bl OSi_TryLockVram
_02090E94: ; 0x02090E94
	cmp r0, #0x0
	bne _02090EB0
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r8,lr}
	bx lr
_02090EB0:
	ldr r0, _02091028 ; =0x021C8C64
	mov r2, #0x4
	ldr r1, _0209102C ; =0x04000242
	strh r2, [r0, #0x0]
	mov r0, #0x82
	strb r0, [r1, #0x0]
	b _02090F78
_02090ECC:
	ldr r1, _02091020 ; =0x021C8C60
	mov r0, #0x8
	ldrh r1, [r1, #0x0]
	bl OSi_TryLockVram
_02090EDC: ; 0x02090EDC
	cmp r0, #0x0
	bne _02090EF8
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r8,lr}
	bx lr
_02090EF8:
	ldr r0, _02091028 ; =0x021C8C64
	mov r2, #0x8
	ldr r1, _02091030 ; =0x04000243
	strh r2, [r0, #0x0]
	mov r0, #0x82
	strb r0, [r1, #0x0]
	b _02090F78
_02090F14:
	ldr r1, _02091020 ; =0x021C8C60
	mov r0, #0xc
	ldrh r1, [r1, #0x0]
	bl OSi_TryLockVram
_02090F24: ; 0x02090F24
	cmp r0, #0x0
	bne _02090F40
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r8,lr}
	bx lr
_02090F40:
	ldr r0, _02091028 ; =0x021C8C64
	mov r2, #0xc
	ldr r1, _0209102C ; =0x04000242
	strh r2, [r0, #0x0]
	mov r2, #0x82
	ldr r0, _02091030 ; =0x04000243
	strb r2, [r1, #0x0]
	mov r1, #0x8a
	strb r1, [r0, #0x0]
	b _02090F78
_02090F68:
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4-r8,lr}
	bx lr
_02090F78:
	mov r0, #0xf
	mov r1, #0x0
	bl PXI_IsCallbackReady
_02090F84: ; 0x02090F84
	cmp r0, #0x0
	bne _02090F98
	ldr r1, _02091034 ; =FUN_02090BBC
	mov r0, #0xf
	bl PXI_SetFifoRecvCallback
_02090F98:
	cmp r6, #0x0
	ldreq r1, _02091038 ; =FUN_02090BB8
	ldreq r0, _02091024 ; =0x021C8C6C
	ldr r3, _0209103C ; =0x021C8C68
	streq r1, [r0, #0x0]
	ldrne r0, _02091024 ; =0x021C8C6C
	mov r1, #0x10000
	strne r6, [r0, #0x0]
	mov r0, #0xf
	mov r2, #0x0
	str r5, [r3, #0x0]
	bl PXI_SendWordByFifo
_02090FC8: ; 0x02090FC8
	cmp r0, #0x0
	bge _0209100C
	ldr r0, _02091028 ; =0x021C8C64
	ldr r1, _02091020 ; =0x021C8C60
	ldrh r0, [r0, #0x0]
	ldrh r1, [r1, #0x0]
	bl OSi_UnlockVram
	ldr r2, _02091028 ; =0x021C8C64
	mov r3, #0x0
	ldr r1, _02091024 ; =0x021C8C6C
	mov r0, r4
	strh r3, [r2, #0x0]
	str r3, [r1, #0x0]
	bl OS_RestoreInterrupts
	mov r0, #0x4
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209100C:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_02091020: .word 0x021C8C60
_02091024: .word 0x021C8C6C
_02091028: .word 0x021C8C64
_0209102C: .word 0x04000242
_02091030: .word 0x04000243
_02091034: .word FUN_02090BBC
_02091038: .word FUN_02090BB8
_0209103C: .word 0x021C8C68

	arm_func_start FUN_02091040
FUN_02091040: ; 0x02091040
	ldr r3, _02091054 ; =0x021C8C70
	ldr r2, _02091058 ; =0x021C8C74
	str r0, [r3, #0x0]
	str r1, [r2, #0x0]
	bx lr
	.balign 4
_02091054: .word 0x021C8C70
_02091058: .word 0x021C8C74

	arm_func_start FUN_0209105C
FUN_0209105C: ; 0x0209105C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020910A0 ; =0x021C8C74
	mov r2, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _02091088
	blx r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_02091088:
	mov r0, #0x0
	mvn r1, #0x0
	bl OS_FreeToHeap
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020910A0: .word 0x021C8C74

	arm_func_start FUN_020910A4
FUN_020910A4:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020910E8 ; =0x021C8C70
	mov r2, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020910D0
	blx r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020910D0:
	mov r0, #0x0
	mvn r1, #0x0
	bl OS_AllocFromHeap
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020910E8: .word 0x021C8C70

	arm_func_start FUN_020910EC
FUN_020910EC: ; 0x020910EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	mov r12, r0
	mov r4, r1
	mov r5, r2
	mov r2, r4
	add r0, sp, #0x0
	mov r1, r12
	mov r4, r3
	bl MATH_CalcSHA1
_02091114: ; 0x02091114
	add r0, sp, #0x0
	mov r1, r5
	mov r2, r4
	bl FUN_02091130
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02091130
FUN_02091130: ; 0x02091130
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x120
	mov r3, #0x0
	str r3, [sp, #0x10]
	str r3, [sp, #0x18]
	str r2, [sp, #0x0]
	mov r3, #0x80
	mov r4, r0
	mov r2, r1
	ldr ip, _0209122C ; =0x00010001
	str r3, [sp, #0x4]
	add r0, sp, #0x1c
	mov r1, #0x100
	str r12, [sp, #0x8]
	bl FUN_0209156C
	mov r1, r0
	add r0, sp, #0x1c
	add r2, sp, #0xc
	add r3, sp, #0x10
	bl FUN_020913D4
_02091180: ; 0x02091180
	cmp r0, #0x0
	addeq sp, sp, #0x120
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r1, sp, #0x14
	add r0, sp, #0x18
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r2, #0x0
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	mov r3, r2
	bl FUN_02091230
_020911B8: ; 0x020911B8
	cmp r0, #0x0
	addeq sp, sp, #0x120
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, [sp, #0x18]
	cmp r0, #0x14
	addne sp, sp, #0x120
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	ldr r2, [sp, #0x14]
	mov r3, #0x0
_020911EC:
	ldrb r1, [r2, #0x0]
	ldrb r0, [r4, #0x0]
	cmp r1, r0
	addne sp, sp, #0x120
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	add r3, r3, #0x1
	cmp r3, #0x14
	add r4, r4, #0x1
	add r2, r2, #0x1
	blt _020911EC
	mov r0, #0x1
	add sp, sp, #0x120
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209122C: .word 0x00010001

	arm_func_start FUN_02091230
FUN_02091230:
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r2
	mov r4, r3
	add r0, sp, #0x10
	add r1, sp, #0x14
	mov r2, #0x30
	mov r3, #0x0
	bl FUN_02091498
_02091258: ; 0x02091258
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	addeq sp, sp, #0x10
	bxeq lr
	add r0, sp, #0x10
	add r1, sp, #0x14
	mov r2, #0x30
	mov r3, #0x0
	bl FUN_02091498
_02091284: ; 0x02091284
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	addeq sp, sp, #0x10
	bxeq lr
	add r0, sp, #0x10
	add r1, sp, #0x14
	add r3, sp, #0x0
	mov r2, #0x6
	bl FUN_02091498
_020912B0: ; 0x020912B0
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	addeq sp, sp, #0x10
	bxeq lr
	cmp r5, #0x0
	ldrne r0, [sp, #0x10]
	strne r0, [r5, #0x0]
	cmp r4, #0x0
	ldrne r0, [sp, #0x0]
	strne r0, [r4, #0x0]
	ldr r2, [sp, #0x0]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r0, r0, r2
	str r0, [sp, #0x10]
	cmp r1, r2
	addcc sp, sp, #0x4
	movcc r0, #0x0
	ldmccia sp!, {r4-r5,lr}
	addcc sp, sp, #0x10
	bxcc lr
	sub r12, r1, r2
	add r0, sp, #0x10
	add r1, sp, #0x14
	add r3, sp, #0x0
	mov r2, #0x5
	str r12, [sp, #0x14]
	bl FUN_02091498
_02091328: ; 0x02091328
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r2, [sp, #0x0]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r0, r0, r2
	str r0, [sp, #0x10]
	cmp r1, r2
	addcc sp, sp, #0x4
	movcc r0, #0x0
	ldmccia sp!, {r4-r5,lr}
	addcc sp, sp, #0x10
	bxcc lr
	sub r12, r1, r2
	add r0, sp, #0x10
	add r1, sp, #0x14
	add r3, sp, #0x0
	mov r2, #0x4
	str r12, [sp, #0x14]
	bl FUN_02091498
_02091388: ; 0x02091388
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r1, [sp, #0x20]
	cmp r1, #0x0
	ldrne r0, [sp, #0x10]
	strne r0, [r1, #0x0]
	ldr r1, [sp, #0x24]
	cmp r1, #0x0
	ldrne r0, [sp, #0x0]
	strne r0, [r1, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start FUN_020913D4
FUN_020913D4:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0xa
	addcc sp, sp, #0x4
	movcc r0, #0x0
	ldmccia sp!, {lr}
	bxcc lr
	ldrb r12, [r0, #0x0]
	add lr, r0, r1
	cmp r12, #0x1
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {lr}
	bxne lr
	add r12, r0, #0x1
	mov r1, #0x0
_02091414:
	ldrb r0, [r12], #0x1
	cmp r0, #0xff
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {lr}
	bxne lr
	add r1, r1, #0x1
	cmp r1, #0x8
	blt _02091414
	cmp r12, lr
	beq _02091458
_02091440:
	ldrb r0, [r12, #0x0]
	cmp r0, #0xff
	bne _02091458
	add r12, r12, #0x1
	cmp r12, lr
	bne _02091440
_02091458:
	cmp r12, lr
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {lr}
	bxeq lr
	ldrb r0, [r12, #0x0]
	cmp r0, #0x0
	movne r0, #0x0
	addeq r0, r12, #0x1
	subeq r1, lr, r0
	streq r1, [r3, #0x0]
	streq r0, [r2, #0x0]
	moveq r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_02091498
FUN_02091498:
	stmdb sp!, {r4-r6,lr}
	ldr r5, [r0, #0x0]
	mov r6, #0x0
	ldrb r4, [r5, #0x0]
	add r5, r5, #0x1
	mov r12, r6
	cmp r4, r2
	ldr r2, [r1, #0x0]
	movne r0, r6
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	cmp r2, #0x1
	movcc r0, r6
	ldmccia sp!, {r4-r6,lr}
	bxcc lr
	ldrb lr, [r5, #0x0]
	sub r4, r2, #0x1
	ands r2, lr, #0x80
	beq _02091534
	and r2, lr, #0x7f
	and lr, r2, #0xff
	add r2, lr, #0x1
	cmp r4, r2
	movcc r0, r6
	ldmccia sp!, {r4-r6,lr}
	bxcc lr
	cmp r3, #0x0
	sub r6, r4, lr
	beq _0209152C
	ldrb r2, [r5, #0x1]
	add r5, r5, #0x1
	and r4, r2, #0x7f
_02091518:
	sub r2, lr, #0x1
	add r12, r4, r12, lsl #0x7
	ands lr, r2, #0xff
	bne _02091518
	b _02091550
_0209152C:
	add r5, r5, lr
	b _02091550
_02091534:
	add r5, r5, #0x1
	cmp r4, #0x1
	mov r12, lr
	movcc r0, r6
	ldmccia sp!, {r4-r6,lr}
	bxcc lr
	sub r6, r4, #0x1
_02091550:
	str r5, [r0, #0x0]
	str r6, [r1, #0x0]
	cmp r3, #0x0
	strne r12, [r3, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209156C
FUN_0209156C: ; 0x0209156C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x58
	movs r6, r0
	mov r5, r1
	mov r8, r2
	mov r7, r3
	beq _0209159C
	cmp r8, #0x0
	beq _0209159C
	ldr r0, [sp, #0x70]
	cmp r0, #0x0
	bne _020915AC
_0209159C:
	add sp, sp, #0x58
	mvn r0, #0x2
	ldmia sp!, {r4-r8,lr}
	bx lr
_020915AC:
	bl FUN_02094FAC
	mov r4, r0
	add r0, sp, #0x4
	bl FUN_0209502C
	add r0, sp, #0x18
	bl FUN_0209502C
	add r0, sp, #0x2c
	bl FUN_0209502C
	add r0, sp, #0x40
	bl FUN_0209502C
_020915D4: ; 0x020915D4
	cmp r4, #0x0
	mvneq r5, #0x1
	beq _02091688
	add r2, sp, #0x4
	mov r0, r8
	mov r1, r7
	bl FUN_02094C68
_020915F0: ; 0x020915F0
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	ldr r1, [sp, #0x78]
	add r0, sp, #0x2c
	bl FUN_02094D7C
_02091608: ; 0x02091608
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	ldr r0, [sp, #0x70]
	ldr r1, [sp, #0x74]
	add r2, sp, #0x40
	bl FUN_02094C68
_02091624: ; 0x02091624
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	add r0, sp, #0x18
	add r1, sp, #0x4
	add r2, sp, #0x2c
	add r3, sp, #0x40
	str r4, [sp, #0x0]
	bl FUN_020931B8
_02091648: ; 0x02091648
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	add r0, sp, #0x18
	bl FUN_02095188
	add r1, r0, #0x7
	mov r0, r1, asr #0x2
	add r0, r1, r0, lsr #0x1d
	mov r0, r0, asr #0x3
	cmp r0, r5
	mvngt r5, #0x0
	bgt _02091688
	add r0, sp, #0x18
	mov r1, r6
	bl FUN_02094BEC
	mov r5, r0
_02091688:
	add r0, sp, #0x4
	bl FUN_0209510C
	add r0, sp, #0x18
	bl FUN_0209510C
	add r0, sp, #0x2c
	bl FUN_0209510C
	add r0, sp, #0x40
	bl FUN_0209510C
_020916A8: ; 0x020916A8
	cmp r4, #0x0
	beq _020916B8
	mov r0, r4
	bl FUN_02094F3C
_020916B8:
	mov r0, r5
	add sp, sp, #0x58
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_020916C8
FUN_020916C8: ; 0x020916C8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x7c
	mov r4, #0x0
	mov r5, r3
	mov r3, r4
	str r3, [sp, #0x34]
	ldr r3, [r5, #0x0]
	str r0, [sp, #0x4]
	mov r0, r4
	ldr r3, [r3, #0x0]
	str r0, [sp, #0x1c]
	str r0, [sp, #0x20]
	ands r0, r3, #0x1
	ldr r0, [sp, #0xa0]
	str r4, [sp, #0x8]
	str r0, [sp, #0xa0]
	mov r7, r1
	mov r6, r2
	addeq sp, sp, #0x7c
	moveq r0, r4
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r1, [r7, #0x4]
	ldr r0, [r0, #0x0]
	cmp r1, #0x0
	str r0, [sp, #0xc]
	beq _0209174C
	cmp r1, #0x1
	bne _02091768
	ldr r0, [r7, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02091768
_0209174C:
	ldr r0, [sp, #0x4]
	mov r1, #0x0
	bl FUN_02094D7C
	add sp, sp, #0x7c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_02091768:
	ldr r1, [r6, #0x4]
	cmp r1, #0x0
	beq _0209178C
	cmp r1, #0x1
	bne _020917A8
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020917A8
_0209178C:
	ldr r0, [sp, #0x4]
	mov r1, #0x1
	bl FUN_02094D7C
	add sp, sp, #0x7c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020917A8:
	cmp r1, #0x1
	bne _020917DC
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	bne _020917DC
	ldr r0, [sp, #0x4]
	mov r1, r7
	bl FUN_02094E24
	add sp, sp, #0x7c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020917DC:
	ldr r0, [sp, #0xa4]
	str r0, [sp, #0x18]
	cmp r0, #0x0
	bne _02091810
	bl FUN_02092860
	str r0, [sp, #0x18]
	cmp r0, #0x0
	beq _02091E6C
	ldr r2, [sp, #0xa0]
	mov r1, r5
	bl FUN_02092894
_02091808: ; 0x02091808
	cmp r0, #0x0
	beq _02091E6C
_02091810:
	ldr r3, [sp, #0xa0]
	add r1, sp, #0x34
	mov r4, r3
	ldr r4, [r4, #0x10c]
	mov r0, r6
	mov r2, #0x0
	str r4, [sp, #0x1c]
	bl FUN_02092C28
_02091830: ; 0x02091830
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [sp, #0xa0]
	ldr r0, [r0, #0x0]
	add r1, r0, #0x1
	ldr r0, [sp, #0xa0]
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x34]
	ldrb r1, [r0, #0x2]
	ldrb r0, [r0, #0x3]
	str r0, [sp, #0x10]
	add r0, r1, #0x3f
	bl _s32_div_f
	ldr r1, [sp, #0x34]
	mov r4, r0
	add r0, r1, #0x4
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x18]
	ldr r3, [r7, #0x4]
	ldr r10, [r0, #0x24]
	cmp r3, r10
	bne _020918A8
	ldr r1, [r7, #0x0]
	sub r2, r10, #0x1
	ldr r0, [r5, #0x0]
	ldr r1, [r1, r2, lsl #0x2]
	ldr r0, [r0, r2, lsl #0x2]
	cmp r1, r0
	strcc r7, [sp, #0x14]
	blo _02091960
_020918A8:
	cmp r3, r10
	bge _0209191C
	ldr r0, [sp, #0xa0]
	ldr r3, [r0, #0x0]
	add r1, r0, #0x4
	add r2, r3, #0x1
	str r2, [r0, #0x0]
	mov r0, #0x14
	mla r0, r3, r0, r1
	ldr r2, [r7, #0x4]
	mov r1, r0
	str r2, [r1, #0x4]
	mov r1, r10
	str r0, [sp, #0x14]
	bl FUN_0209508C
	ldr r0, [r7, #0x4]
	mov r2, #0x0
	cmp r0, #0x0
	ble _02091960
_020918F4:
	ldr r1, [r7, #0x0]
	ldr r0, [sp, #0x14]
	ldr r1, [r1, r2, lsl #0x2]
	ldr r0, [r0, #0x0]
	str r1, [r0, r2, lsl #0x2]
	ldr r0, [r7, #0x4]
	add r2, r2, #0x1
	cmp r2, r0
	blt _020918F4
	b _02091960
_0209191C:
	ldr r0, [sp, #0xa0]
	mov r2, r5
	ldr r3, [r0, #0x0]
	mov r1, r7
	add r5, r3, #0x1
	str r5, [r0, #0x0]
	add r5, r0, #0x4
	mov r0, #0x14
	mla r0, r3, r0, r5
	ldr r3, [sp, #0xa0]
	str r0, [sp, #0x14]
	bl FUN_02093214
_0209194C: ; 0x0209194C
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [sp, #0x14]
	mov r1, r10
	bl FUN_0209508C
_02091960:
	ldr r0, [sp, #0xa0]
	ldr r3, [r0, #0x0]
	ldr r0, [r6, #0x4]
	add r1, r3, #0x1
	mul r2, r0, r4
	ldr r0, [sp, #0xa0]
	mov r4, r2, lsl #0x1
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r4, r4, #0x7
	add r2, r1, #0x1
	str r2, [r0, #0x0]
	ldr r2, [sp, #0x10]
	ldr r0, [r0, #0x0]
	mul r5, r2, r10
	mov r2, r4, asr #0x1
	add r2, r4, r2, lsr #0x1e
	add r5, r5, r2, asr #0x2
	ldr r2, [sp, #0xa0]
	mov r6, #0x14
	add r2, r2, #0x4
	mla r8, r1, r6, r2
	mla r4, r3, r6, r2
	ldr r1, [sp, #0xa0]
	add r3, r0, #0x1
	mla r7, r0, r6, r2
	str r3, [r1, #0x0]
	mov r0, r1
	ldr r0, [r0, #0x0]
	mla r6, r0, r6, r2
	add r1, r0, #0x1
	ldr r0, [sp, #0xa0]
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0x8]
	cmp r10, r0
	ldrle r0, [sp, #0x4]
	ble _02091A04
	ldr r0, [sp, #0x4]
	mov r1, r10
	bl FUN_02094EBC
_02091A04:
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [r8, #0x8]
	mov r1, r10, lsl #0x2
	cmp r1, r0
	movle r0, r8
	ble _02091A28
	mov r0, r8
	bl FUN_02094EBC
_02091A28:
	cmp r0, #0x0
	beq _02091E6C
	ldr r1, [r7, #0x8]
	mov r0, r10, lsl #0x1
	str r0, [sp, #0x24]
	cmp r0, r1
	movle r0, r7
	ble _02091A54
	ldr r1, [sp, #0x24]
	mov r0, r7
	bl FUN_02094EBC
_02091A54:
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [r4, #0x8]
	cmp r5, r0
	movle r0, r4
	ble _02091A78
	mov r1, r5
	mov r0, r4
	bl FUN_02094EBC
_02091A78:
	cmp r0, #0x0
	beq _02091E6C
	ldr r1, [r6, #0x8]
	ldr r0, [sp, #0x24]
	cmp r0, r1
	movle r0, r6
	ble _02091AA0
	ldr r1, [sp, #0x24]
	mov r0, r6
	bl FUN_02094EBC
_02091AA0:
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [sp, #0x18]
	ldr r11, [r8, #0x0]
	ldr r8, [r7, #0x0]
	ldr r6, [r6, #0x0]
	ldr r1, [r4, #0x0]
	ldr r7, [r0, #0x48]
	ldr r5, [r0, #0x20]
	ldr r3, [sp, #0x18]
	str r1, [sp, #0x38]
	str r10, [sp, #0x0]
	ldr r1, [sp, #0x14]
	ldr r3, [r3, #0xc]
	ldr r1, [r1, #0x0]
	mov r0, r6
	mov r2, r10
	bl FUN_020937E8
	str r7, [sp, #0x0]
	ldr r0, [sp, #0x38]
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl FUN_02092E30
	ldr r0, [sp, #0x10]
	cmp r0, #0x1
	ble _02091BA8
	ldr r1, [sp, #0x38]
	mov r0, r6
	mov r2, r10
	mov r3, r11
	bl FUN_02092F70
	mov r0, r11
	mov r1, r6
	mov r2, r5
	mov r3, r10
	str r7, [sp, #0x0]
	bl FUN_02092E30
	ldr r0, [sp, #0x10]
	mov r4, #0x1
	cmp r0, #0x1
	ble _02091BA8
	mov r0, r10, lsl #0x2
	str r0, [sp, #0x28]
	add r9, sp, #0x38
_02091B54:
	sub r3, r4, #0x1
	ldr r2, [r9, r3, lsl #0x2]
	ldr r1, [sp, #0x28]
	mov r0, r6
	add r1, r2, r1
	str r1, [r9, r4, lsl #0x2]
	str r10, [sp, #0x0]
	ldr r1, [r9, r3, lsl #0x2]
	mov r2, r10
	mov r3, r11
	bl FUN_020937E8
	str r7, [sp, #0x0]
	ldr r0, [r9, r4, lsl #0x2]
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl FUN_02092E30
	ldr r0, [sp, #0x10]
	add r4, r4, #0x1
	cmp r4, r0
	blt _02091B54
_02091BA8:
	ldr r3, [sp, #0x34]
	add r0, r3, #0x1
	str r0, [sp, #0x34]
	add r2, r0, #0x1
	ldrb r1, [r3, #0x0]
	str r2, [sp, #0x34]
	ldrb r9, [r3, #0x1]
	cmp r9, #0xff
	bne _02091C28
	cmp r1, #0x0
	bne _02091C28
	add r0, r2, #0x1
	str r0, [sp, #0x34]
	ldrb r1, [r2, #0x0]
	b _02091BF8
_02091BE4:
	add r9, r9, #0x100
	ldr r1, [sp, #0x34]
	add r1, r1, #0x2
	str r1, [sp, #0x34]
	ldrb r1, [r0, #0x1]
_02091BF8:
	ldr r0, [sp, #0x34]
	ldrb r2, [r0, #0x0]
	cmp r2, #0xff
	bne _02091C10
	cmp r1, #0x0
	beq _02091BE4
_02091C10:
	ldr r2, [sp, #0x34]
	add r2, r2, #0x1
	str r2, [sp, #0x34]
	ldrb r0, [r0, #0x0]
	add r0, r0, #0x1
	add r9, r9, r0
_02091C28:
	mov r2, r1, asr #0x1
	add r0, sp, #0x38
	ldr r0, [r0, r2, lsl #0x2]
	mov r1, r8
	mov r2, r10, lsl #0x2
	bl MI_CpuCopy8
_02091C40: ; 0x02091C40
	cmp r9, #0x0
	beq _02091E00
	mov r0, #0xff
	str r0, [sp, #0x2c]
	mov r0, #0x0
	str r0, [sp, #0x30]
_02091C58:
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	beq _02091C8C
	mov r3, r0
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x20]
	ldr r3, [r3, #0x0]
	blx r3
	cmp r0, #0x0
	ldr r0, [sp, #0x20]
	add r0, r0, #0x1
	str r0, [sp, #0x20]
	bne _02091E6C
_02091C8C:
	ldr r0, [sp, #0xa0]
	ldr r0, [r0, #0x108]
	ands r0, r0, #0x4000
	bne _02091E6C
	cmp r9, #0x0
	ldr r4, [sp, #0x30]
	ble _02091CE0
_02091CA8:
	mov r0, r6
	mov r1, r8
	mov r2, r10
	mov r3, r11
	bl FUN_02092F70
	str r7, [sp, #0x0]
	mov r0, r8
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl FUN_02092E30
	add r4, r4, #0x1
	cmp r4, r9
	blt _02091CA8
_02091CE0:
	ldr r2, [sp, #0x34]
	add r0, r2, #0x1
	str r0, [sp, #0x34]
	add r1, r0, #0x1
	ldrb r0, [r2, #0x0]
	str r1, [sp, #0x34]
	ldrb r9, [r2, #0x1]
	cmp r9, #0xff
	bne _02091D60
	cmp r0, #0x0
	bne _02091D60
	add r0, r1, #0x1
	str r0, [sp, #0x34]
	ldrb r0, [r1, #0x0]
	b _02091D30
_02091D1C:
	add r9, r9, #0x100
	ldr r0, [sp, #0x34]
	add r0, r0, #0x2
	str r0, [sp, #0x34]
	ldrb r0, [r1, #0x1]
_02091D30:
	ldr r1, [sp, #0x34]
	ldrb r2, [r1, #0x0]
	cmp r2, #0xff
	bne _02091D48
	cmp r0, #0x0
	beq _02091D1C
_02091D48:
	ldr r2, [sp, #0x34]
	add r2, r2, #0x1
	str r2, [sp, #0x34]
	ldrb r1, [r1, #0x0]
	add r1, r1, #0x1
	add r9, r9, r1
_02091D60:
	cmp r0, #0x0
	bne _02091D70
	cmp r9, #0x0
	beq _02091E00
_02091D70:
	cmp r9, #0x0
	bne _02091D80
	cmp r0, #0x1
	beq _02091DBC
_02091D80:
	mov r1, r0, asr #0x1
	str r10, [sp, #0x0]
	add r0, sp, #0x38
	ldr r3, [r0, r1, lsl #0x2]
	mov r0, r6
	mov r1, r8
	mov r2, r10
	bl FUN_020937E8
	mov r0, r8
	mov r1, r6
	mov r2, r5
	mov r3, r10
	str r7, [sp, #0x0]
	bl FUN_02092E30
	b _02091DF8
_02091DBC:
	ldr r0, [sp, #0x14]
	str r10, [sp, #0x0]
	ldr r3, [r0, #0x0]
	mov r0, r6
	mov r1, r8
	mov r2, r10
	bl FUN_020937E8
	ldr r0, [sp, #0x4]
	str r7, [sp, #0x0]
	ldr r0, [r0, #0x0]
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl FUN_02092E30
	b _02091E44
_02091DF8:
	cmp r9, #0x0
	bne _02091C58
_02091E00:
	ldr r0, [sp, #0x24]
	mov r2, r10
	cmp r10, r0
	bge _02091E28
	mov r1, #0x0
_02091E14:
	ldr r0, [sp, #0x24]
	str r1, [r8, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, r0
	blt _02091E14
_02091E28:
	ldr r0, [sp, #0x4]
	str r7, [sp, #0x0]
	ldr r0, [r0, #0x0]
	mov r1, r8
	mov r2, r5
	mov r3, r10
	bl FUN_02092E30
_02091E44:
	ldr r0, [sp, #0xa0]
	ldr r0, [r0, #0x108]
	ands r0, r0, #0x4000
	bne _02091E6C
	ldr r0, [sp, #0x4]
	mov r1, r0
	str r10, [r1, #0x4]
	bl FUN_02095040
	mov r0, #0x1
	str r0, [sp, #0x8]
_02091E6C:
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	beq _02091E94
	ldr r3, [r0, #0x0]
	mov r1, #0xff
	mvn r2, #0x0
	blx r3
	cmp r0, #0x0
	movne r0, #0x0
	strne r0, [sp, #0x8]
_02091E94:
	ldr r0, [sp, #0xa4]
	cmp r0, #0x0
	bne _02091EB0
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	beq _02091EB0
	bl FUN_020927E4
_02091EB0:
	ldr r2, [sp, #0xc]
	ldr r1, [sp, #0xa0]
	ldr r0, [sp, #0x8]
	str r2, [r1, #0x0]
	add sp, sp, #0x7c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02091ECC
FUN_02091ECC: ; 0x02091ECC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x18c
	mov r10, r0
	mov r0, #0x0
	str r0, [sp, #0x8]
	mov r5, r1
	ldr r1, [sp, #0x8]
	mov r0, r2
	str r2, [sp, #0x4]
	mov r4, r3
	str r1, [sp, #0xc]
	ldr r9, [sp, #0x1b0]
	bl FUN_02095188
	ldr r1, [r5, #0x4]
	mov r8, r0
	cmp r1, #0x0
	beq _02091F28
	cmp r1, #0x1
	bne _02091F44
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02091F44
_02091F28:
	mov r0, r10
	mov r1, #0x0
	bl FUN_02094D7C
	add sp, sp, #0x18c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_02091F44:
	ldr r0, [sp, #0x4]
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _02091F6C
	cmp r1, #0x1
	bne _02091F88
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02091F88
_02091F6C:
	mov r0, r10
	mov r1, #0x1
	bl FUN_02094D7C
	add sp, sp, #0x18c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_02091F88:
	cmp r1, #0x1
	bne _02091FC0
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02091FC0
	mov r0, r10
	mov r1, r5
	bl FUN_02094E24
	add sp, sp, #0x18c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_02091FC0:
	add r0, sp, #0x18
	bl FUN_020927BC
	add r0, sp, #0x18
	mov r1, r4
	mov r2, r9
	bl FUN_02092744
_02091FD8: ; 0x02091FD8
	cmp r0, #0x0
	ble _0209220C
	add r0, sp, #0x4c
	bl FUN_0209502C
	ldr r2, [r9, #0x0]
	add r1, r9, #0x4
	mov r0, #0x14
	mla r6, r2, r0, r1
	add r1, r2, #0x1
	str r1, [r9, #0x0]
	mov r2, r4
	mov r4, #0x1
	add r0, sp, #0x4c
	mov r1, r5
	mov r3, r9
	str r4, [sp, #0xc]
	bl FUN_02093214
_0209201C: ; 0x0209201C
	cmp r0, #0x0
	beq _0209220C
	add r1, sp, #0x4c
	add r3, sp, #0x18
	mov r0, r6
	mov r2, r1
	str r9, [sp, #0x0]
	bl FUN_02092698
_0209203C: ; 0x0209203C
	cmp r0, #0x0
	beq _0209220C
	cmp r8, #0x11
	movle r11, r4
	ble _02092068
	cmp r8, #0x100
	movge r11, #0x5
	bge _02092068
	cmp r8, #0x80
	movge r11, #0x4
	movlt r11, #0x3
_02092068:
	sub r0, r11, #0x1
	mov r4, #0x1
	mov r7, r4, lsl r0
	cmp r7, #0x1
	ble _020920C4
	add r5, sp, #0x60
_02092080:
	mov r0, r5
	bl FUN_0209502C
	sub r3, r4, #0x1
	mov r2, #0x14
	add r1, sp, #0x4c
	mla r1, r3, r2, r1
	mov r0, r5
	mov r2, r6
	add r3, sp, #0x18
	str r9, [sp, #0x0]
	bl FUN_02092698
_020920AC: ; 0x020920AC
	cmp r0, #0x0
	beq _0209220C
	add r4, r4, #0x1
	cmp r4, r7
	add r5, r5, #0x14
	blt _02092080
_020920C4:
	mov r5, #0x1
	mov r0, r10
	mov r1, r5
	str r4, [sp, #0xc]
	sub r8, r8, #0x1
	bl FUN_02094D7C
_020920DC: ; 0x020920DC
	cmp r0, #0x0
	beq _0209220C
	mov r0, r5
	str r0, [sp, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x14]
_020920F4:
	ldr r0, [sp, #0x4]
	mov r1, r8
	bl FUN_02094A8C
_02092100: ; 0x02092100
	cmp r0, #0x0
	bne _02092140
	cmp r5, #0x0
	bne _02092130
	mov r0, r10
	mov r1, r10
	mov r2, r10
	add r3, sp, #0x18
	str r9, [sp, #0x0]
	bl FUN_02092698
_02092128: ; 0x02092128
	cmp r0, #0x0
	beq _0209220C
_02092130:
	cmp r8, #0x0
	beq _02092204
	sub r8, r8, #0x1
	b _020920F4
_02092140:
	ldr r6, [sp, #0x10]
	ldr r7, [sp, #0x14]
	cmp r11, #0x1
	mov r4, r6
	ble _02092184
_02092154:
	subs r1, r8, r4
	bmi _02092184
	ldr r0, [sp, #0x4]
	bl FUN_02094A8C
_02092164: ; 0x02092164
	cmp r0, #0x0
	subne r0, r4, r7
	movne r0, r6, lsl r0
	movne r7, r4
	add r4, r4, #0x1
	orrne r6, r0, #0x1
	cmp r4, r11
	blt _02092154
_02092184:
	cmp r5, #0x0
	add r5, r7, #0x1
	bne _020921C8
	cmp r5, #0x0
	ldr r4, [sp, #0x14]
	ble _020921C8
_0209219C:
	mov r0, r10
	mov r1, r10
	mov r2, r10
	add r3, sp, #0x18
	str r9, [sp, #0x0]
	bl FUN_02092698
_020921B4: ; 0x020921B4
	cmp r0, #0x0
	beq _0209220C
	add r4, r4, #0x1
	cmp r4, r5
	blt _0209219C
_020921C8:
	mov r3, r6, asr #0x1
	mov r1, #0x14
	add r0, sp, #0x4c
	mla r2, r3, r1, r0
	mov r0, r10
	mov r1, r10
	add r3, sp, #0x18
	str r9, [sp, #0x0]
	bl FUN_02092698
_020921EC: ; 0x020921EC
	cmp r0, #0x0
	beq _0209220C
	add r0, r7, #0x1
	ldr r5, [sp, #0x14]
	subs r8, r8, r0
	bpl _020920F4
_02092204:
	mov r0, #0x1
	str r0, [sp, #0x8]
_0209220C:
	ldr r0, [sp, #0xc]
	ldr r1, [r9, #0x0]
	cmp r0, #0x0
	sub r0, r1, #0x1
	str r0, [r9, #0x0]
	mov r4, #0x0
	ble _02092248
	add r5, sp, #0x4c
_0209222C:
	mov r0, r5
	bl FUN_02095164
	ldr r0, [sp, #0xc]
	add r4, r4, #0x1
	cmp r4, r0
	add r5, r5, #0x14
	blt _0209222C
_02092248:
	add r0, sp, #0x18
	bl FUN_02092788
	ldr r0, [sp, #0x8]
	add sp, sp, #0x18c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02092260
FUN_02092260: ; 0x02092260
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	movs r8, r2
	mov r10, r0
	mov r9, r1
	mov r11, #0x0
	mov r5, #0x2
	addeq sp, sp, #0x4
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	mov r0, r8
	bl FUN_020951BC
	cmp r0, #0x20
	beq _020922B4
	mov r1, #0x1
	cmp r10, r1, lsl r0
	addhi sp, sp, #0x4
	movhi r0, r11
	ldmhiia sp!, {r4-r11,lr}
	bxhi lr
_020922B4:
	cmp r10, r8
	rsb r2, r0, #0x20
	subcs r10, r10, r8
	cmp r2, #0x0
	movne r1, r10, lsl r2
	rsbne r0, r2, #0x20
	orrne r10, r1, r9, lsr r0
	movne r8, r8, lsl r2
	ldr r4, _0209239C ; =0x0000FFFF
	movne r9, r9, lsl r2
	and r7, r4, r8, lsr #0x10
	and r6, r8, r4
_020922E4:
	mov r0, r10, lsr #0x10
	cmp r0, r7
	moveq r0, r4
	beq _02092300
	mov r0, r10
	mov r1, r7
	bl _u32_div_f
_02092300:
	mul r12, r0, r7
	mul r3, r0, r6
	and r2, r4, r9, lsr #0x10
_0209230C:
	mov lr, #0x10000
	sub r1, r10, r12
	rsb lr, lr, #0x0
	ands lr, r1, lr
	bne _02092338
	add r1, r2, r1, lsl #0x10
	cmp r3, r1
	subhi r12, r12, r7
	subhi r3, r3, r6
	subhi r0, r0, #0x1
	bhi _0209230C
_02092338:
	mul r2, r0, r6
	and r1, r2, r4
	mul r3, r0, r7
	mov r1, r1, lsl #0x10
	cmp r9, r1
	add r2, r3, r2, lsr #0x10
	addcc r2, r2, #0x1
	cmp r10, r2
	addcc r10, r10, r8
	sub r9, r9, r1
	subcc r0, r0, #0x1
	sub r1, r10, r2
	subs r5, r5, #0x1
	beq _0209238C
	and r2, r0, r4
	mov r1, r1, lsl #0x10
	and r0, r9, r4
	orr r10, r1, r9, lsr #0x10
	mov r11, r2, lsl #0x10
	mov r9, r0, lsl #0x10
	b _020922E4
_0209238C:
	orr r0, r11, r0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209239C: .word 0x0000FFFF

	arm_func_start FUN_020923A0
FUN_020923A0: ; 0x020923A0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x18
	mov r8, r0
	add r0, sp, #0x4
	mov r7, r1
	mov r6, r2
	mov r5, r3
	mvn r4, #0x0
	bl FUN_0209502C
	add r0, sp, #0x4
	mov r1, #0x0
	bl FUN_02094D7C
	add r0, sp, #0x4
	mov r1, r6
	bl FUN_02094AFC
_020923DC: ; 0x020923DC
	cmp r0, #0x0
	beq _02092404
	add r2, sp, #0x4
	mov r0, r8
	mov r3, r7
	mov r1, #0x0
	str r5, [sp, #0x0]
	bl FUN_02093248
_020923FC: ; 0x020923FC
	cmp r0, #0x0
	movne r4, r6
_02092404:
	add r0, sp, #0x4
	bl FUN_0209510C
	mov r0, r4
	add sp, sp, #0x18
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_0209241C
FUN_0209241C: ; 0x0209241C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	ldr r6, [sp, #0x30]
	mov r9, r1
	ldr r11, [r6, #0x0]
	movs r10, r0
	add r0, r11, #0x1
	str r0, [r6, #0x0]
	ldr r7, [r6, #0x0]
	add r4, r6, #0x4
	mov r0, #0x14
	mla r5, r11, r0, r4
	add r12, r7, #0x1
	mov r1, #0x0
	str r5, [sp, #0x4]
	mla r5, r7, r0, r4
	str r12, [r6, #0x0]
	str r1, [sp, #0x0]
	ldreq r1, [r6, #0x0]
	mov r8, r2
	mlaeq r10, r1, r0, r4
	addeq r0, r1, #0x1
	streq r0, [r6, #0x0]
	mov r7, r3
	cmp r9, #0x0
	bne _0209249C
	ldr r2, [r6, #0x0]
	add r1, r6, #0x4
	mov r0, #0x14
	mla r9, r2, r0, r1
	add r0, r2, #0x1
	str r0, [r6, #0x0]
_0209249C:
	mov r0, r8
	mov r1, r7
	bl FUN_02094B98
_020924A8: ; 0x020924A8
	cmp r0, #0x0
	bge _020924DC
	mov r0, r10
	mov r1, #0x0
	bl FUN_02094D7C
	mov r0, r9
	mov r1, r8
	bl FUN_02094E24
	add sp, sp, #0xc
	str r11, [r6, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020924DC:
	mov r0, r8
	bl FUN_02095188
	ldr r1, [r7, #0x28]
	mov r2, r0
	mov r0, r1, lsl #0x1
	cmp r0, r2
	movgt r2, r0
	suble r0, r2, r0
	movgt r4, #0x0
	addle r0, r0, r0, lsr #0x1f
	movle r4, r0, asr #0x1
	ldr r1, [r7, #0x2c]
	add r0, r2, r2, lsr #0x1f
	mov r0, r0, asr #0x1
	cmp r2, r1
	str r0, [sp, #0x8]
	beq _02092534
	mov r1, r7
	mov r3, r6
	add r0, r7, #0x14
	bl FUN_020923A0
	str r0, [r7, #0x2c]
_02092534:
	ldr r2, [sp, #0x8]
	ldr r0, [sp, #0x4]
	mov r1, r8
	sub r2, r2, r4
	bl FUN_02094134
_02092548: ; 0x02092548
	cmp r0, #0x0
	beq _02092684
	ldr r1, [sp, #0x4]
	mov r0, r5
	mov r3, r6
	add r2, r7, #0x14
	bl FUN_0209390C
_02092564: ; 0x02092564
	cmp r0, #0x0
	beq _02092684
	ldr r2, [sp, #0x8]
	mov r0, r10
	mov r1, r5
	add r2, r2, r4
	bl FUN_02094134
_02092580: ; 0x02092580
	cmp r0, #0x0
	beq _02092684
	mov r4, #0x0
	mov r0, r5
	mov r1, r7
	mov r2, r10
	mov r3, r6
	str r4, [r10, #0xc]
	bl FUN_0209390C
_020925A4: ; 0x020925A4
	cmp r0, #0x0
	beq _02092684
	mov r0, r9
	mov r1, r8
	mov r2, r5
	bl FUN_02093B50
_020925BC: ; 0x020925BC
	cmp r0, #0x0
	beq _02092684
	mov r5, r4
	mov r0, r9
	mov r1, r7
	str r5, [r9, #0xc]
	bl FUN_02094B98
_020925D8: ; 0x020925D8
	cmp r0, #0x0
	blt _02092630
	mov r4, #0x1
_020925E4:
	cmp r5, #0x2
	add r5, r5, #0x1
	bgt _02092684
	mov r0, r9
	mov r1, r9
	mov r2, r7
	bl FUN_02093B50
_02092600: ; 0x02092600
	cmp r0, #0x0
	beq _02092684
	mov r0, r10
	mov r1, r4
	bl FUN_0209400C
_02092614: ; 0x02092614
	cmp r0, #0x0
	beq _02092684
	mov r0, r9
	mov r1, r7
	bl FUN_02094B98
_02092628: ; 0x02092628
	cmp r0, #0x0
	bge _020925E4
_02092630:
	ldr r0, [r9, #0x4]
	mov r1, #0x1
	cmp r0, #0x0
	beq _0209265C
	cmp r0, #0x1
	bne _02092658
	ldr r0, [r9, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209265C
_02092658:
	mov r1, #0x0
_0209265C:
	cmp r1, #0x0
	movne r0, #0x0
	ldreq r0, [r8, #0xc]
	str r0, [r9, #0xc]
	mov r0, #0x1
	ldr r2, [r8, #0xc]
	ldr r1, [r7, #0xc]
	str r0, [sp, #0x0]
	eor r0, r2, r1
	str r0, [r10, #0xc]
_02092684:
	ldr r0, [sp, #0x0]
	str r11, [r6, #0x0]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02092698
FUN_02092698:
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	ldr r4, [sp, #0x20]
	mov r12, #0x14
	ldr r5, [r4, #0x0]
	add lr, r4, #0x4
	mla r6, r5, r12, lr
	add r12, r5, #0x1
	mov r8, r0
	mov r7, r3
	str r12, [r4, #0x0]
	cmp r2, #0x0
	mov r5, #0x0
	beq _02092708
	cmp r1, r2
	bne _020926F0
	mov r0, r6
	mov r2, r4
	bl FUN_0209305C
_020926E4: ; 0x020926E4
	cmp r0, #0x0
	bne _0209270C
	b _02092728
_020926F0:
	mov r0, r6
	mov r3, r4
	bl FUN_0209390C
_020926FC: ; 0x020926FC
	cmp r0, #0x0
	bne _0209270C
	b _02092728
_02092708:
	mov r6, r1
_0209270C:
	mov r1, r8
	mov r2, r6
	mov r3, r7
	mov r0, #0x0
	str r4, [sp, #0x0]
	bl FUN_0209241C
	mov r5, #0x1
_02092728:
	ldr r1, [r4, #0x0]
	mov r0, r5
	sub r1, r1, #0x1
	str r1, [r4, #0x0]
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_02092744
FUN_02092744:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_02094E24
	add r0, r5, #0x14
	mov r1, #0x0
	bl FUN_02094D7C
	mov r0, r4
	bl FUN_02095188
	str r0, [r5, #0x28]
	mov r0, #0x0
	str r0, [r5, #0x2c]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02092788
FUN_02092788: ; 0x02092788
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_0209510C
	add r0, r4, #0x14
	bl FUN_0209510C
	ldr r0, [r4, #0x30]
	ands r0, r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	bl FUN_0209105C
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020927BC
FUN_020927BC: ; 0x020927BC
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_0209502C
	add r0, r4, #0x14
	bl FUN_0209502C
_020927D0: ; 0x020927D0
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x30]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020927E4
FUN_020927E4: ; 0x020927E4
	stmdb sp!, {r4,lr}
	mov r4, r0
	add r0, r4, #0xc
	bl FUN_0209510C
	add r0, r4, #0x20
	bl FUN_0209510C
	add r0, r4, #0x34
	bl FUN_0209510C
	ldr r0, [r4, #0x4c]
	ands r0, r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	bl FUN_0209105C
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02092824
FUN_02092824: ; 0x02092824
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r1, #0x0
	str r1, [r4, #0x0]
	add r0, r4, #0xc
	str r1, [r4, #0x8]
	bl FUN_0209502C
	add r0, r4, #0x20
	bl FUN_0209502C
	add r0, r4, #0x34
	bl FUN_0209502C
_02092850: ; 0x02092850
	mov r0, #0x0
	str r0, [r4, #0x4c]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02092860
FUN_02092860: ; 0x02092860
	stmdb sp!, {r4,lr}
	mov r0, #0x50
	bl FUN_020910A4
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl FUN_02092824
	mov r1, #0x1
	mov r0, r4
	str r1, [r4, #0x4c]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02092894
FUN_02092894:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r6, r1
	ldr r3, [r6, #0x4]
	mov r7, r0
	cmp r3, #0x0
	mov r5, r2
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r0, r7, #0x20
	add r4, r7, #0xc
	bl FUN_02094E24
_020928CC: ; 0x020928CC
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r0, sp, #0x0
	bl FUN_0209502C
	mov r1, #0x1
	mov r0, r6
	str r1, [r7, #0x0]
	bl FUN_02095188
	add r1, r0, #0x1f
	mov r0, r1, asr #0x4
	add r0, r1, r0, lsr #0x1b
	mov r2, r0, asr #0x5
	mov r0, r4
	mov r1, #0x0
	str r2, [r7, #0x8]
	bl FUN_02094D7C
_02092918: ; 0x02092918
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r4
	mov r1, #0x20
	bl FUN_02094AFC
_02092938: ; 0x02092938
	cmp r0, #0x0
	beq _02092A38
	ldr r0, [r6, #0x0]
	ldr r4, [r0, #0x0]
	mov r0, r4
	bl FUN_02092D9C
	mov r1, r0
	add r0, sp, #0x0
	bl FUN_02094D7C
_0209295C: ; 0x0209295C
	cmp r0, #0x0
	beq _02092A38
	add r0, sp, #0x0
	mov r2, #0x20
	mov r1, r0
	bl FUN_02094250
_02092974: ; 0x02092974
	cmp r0, #0x0
	beq _02092A38
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020929B0
	cmp r0, #0x1
	bne _020929A0
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020929B0
_020929A0:
	add r0, sp, #0x0
	mov r1, #0x1
	bl FUN_02093EAC
	b _020929C4
_020929B0:
	add r0, sp, #0x0
	mvn r1, #0x0
	bl FUN_02094D7C
_020929BC: ; 0x020929BC
	cmp r0, #0x0
	beq _02092A38
_020929C4:
	ldr r2, [sp, #0x4]
	cmp r2, #0x1
	ldrge r0, [sp, #0x0]
	ldrge r1, [r0, #0x0]
	movlt r1, #0x0
	cmp r2, #0x2
	ldrge r0, [sp, #0x0]
	mov r2, r4
	ldrge r0, [r0, #0x4]
	movlt r0, #0x0
	bl FUN_02092260
	str r0, [r7, #0x48]
	add r0, r7, #0xc
	mov r1, #0x0
	bl FUN_02094D7C
	ldr r1, [r7, #0x8]
	add r0, r7, #0xc
	mov r1, r1, lsl #0x6
	bl FUN_02094AFC
_02092A10: ; 0x02092A10
	cmp r0, #0x0
	beq _02092A38
	add r0, r7, #0xc
	mov r1, r0
	mov r3, r5
	add r2, r7, #0x20
	bl FUN_02093214
	ldr r1, [r7, #0x8]
	add r0, r7, #0xc
	bl FUN_0209508C
_02092A38:
	add r0, sp, #0x0
	bl FUN_0209510C
	mov r0, #0x1
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02092A50
FUN_02092A50: ; 0x02092A50
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r4, r2
	mov r7, r1
	cmp r4, #0x6
	mov r5, r0
	movgt r4, #0x6
	mov r1, #0x1
	mov r2, r1, lsl r4
	ldr r0, [r7, #0x4]
	sub r2, r2, #0x1
	add r0, r4, r0, lsl #0x5
	ldr r3, _02092C24 ; =0x02106170
	str r2, [sp, #0x0]
	ldr r2, [r3, r4, lsl #0x2]
	mov r1, r4
	sub r0, r0, #0x1
	str r2, [sp, #0x4]
	mov r6, #0x0
	bl _s32_div_f
	mov r12, #0x0
	mov r0, r0, lsl #0x1
	add r0, r0, #0x2
	mov r8, r6
	add r1, r5, r0
	strb r8, [r5, r0]
	strb r8, [r1, #-0x1]
	ldr r0, [r7, #0x0]
	ldr r2, [r7, #0x4]
	ldr r7, [r0, #0x0]
	add lr, r0, #0x4
	cmp r2, #0x1
	sub r9, r1, #0x2
	ldrgt r8, [lr], #0x4
	mov r10, r7
	mov r0, r12
	str r12, [sp, #0x8]
	mov r1, #0xff
	mov r11, r12
_02092AEC:
	ldr r3, [sp, #0x0]
	and r3, r10, r3
	ldr r10, [sp, #0x4]
	ldrb r10, [r10, r3]
	cmp r10, #0x0
	beq _02092B4C
	add r12, r12, r10
	add r6, r6, r10
	cmp r6, #0x20
	blo _02092B34
	cmp r2, #0x1
	ble _02092B4C
	sub r2, r2, #0x1
	mov r7, r8
	cmp r2, #0x1
	movle r8, r11
	ldrgt r8, [lr], #0x4
	sub r6, r6, #0x20
_02092B34:
	cmp r6, #0x0
	moveq r10, r7
	movne r10, r7, lsr r6
	rsbne r3, r6, #0x20
	orrne r10, r10, r8, lsl r3
	b _02092AEC
_02092B4C:
	cmp r3, #0x0
	beq _02092BD0
	strb r12, [r9, #0x0]
	strb r3, [r9, #-0x1]
	cmp r12, #0x100
	sub r9, r9, #0x2
	blo _02092B88
	cmp r12, #0x100
	blo _02092B88
_02092B70:
	strb r1, [r9, #0x0]
	sub r12, r12, #0x100
	strb r0, [r9, #-0x1]
	sub r9, r9, #0x2
	cmp r12, #0x100
	bhs _02092B70
_02092B88:
	mov r12, r4
	add r6, r6, r4
	cmp r6, #0x20
	blo _02092BB8
	cmp r2, #0x1
	ble _02092BD0
	sub r2, r2, #0x1
	mov r7, r8
	cmp r2, #0x1
	ldrle r8, [sp, #0x8]
	sub r6, r6, #0x20
	ldrgt r8, [lr], #0x4
_02092BB8:
	cmp r6, #0x0
	moveq r10, r7
	movne r10, r7, lsr r6
	rsbne r3, r6, #0x20
	orrne r10, r10, r8, lsl r3
	b _02092AEC
_02092BD0:
	add r9, r9, #0x1
	mov r0, #0x2
	b _02092BF4
_02092BDC:
	strb r2, [r5, #0x0]
	ldrb r1, [r9, #0x1]
	add r9, r9, #0x2
	add r0, r0, #0x2
	strb r1, [r5, #0x1]
	add r5, r5, #0x2
_02092BF4:
	ldrb r2, [r9, #0x0]
	cmp r2, #0x0
	bne _02092BDC
	ldrb r1, [r9, #0x1]
	cmp r1, #0x0
	bne _02092BDC
	mov r1, #0x0
	strb r1, [r5, #0x0]
	strb r1, [r5, #0x1]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_02092C24: .word 0x02106170

	arm_func_start FUN_02092C28
FUN_02092C28:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r5, [r3], #0x4
	mov r2, #0x14
	mla r4, r5, r2, r3
	mov r9, r0
	ldr r0, [r9, #0x4]
	mov r8, r1
	cmp r0, #0x0
	mov r5, #0x0
	mov r1, r0, lsl #0x5
	addeq sp, sp, #0x4
	moveq r0, r5
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r0, #0x1
	bne _02092CC8
	cmp r0, #0x1
	bne _02092C8C
	ldr r2, [r9, #0x0]
	ldr r1, _02092D8C ; =0x00010001
	ldr r2, [r2, #0x0]
	cmp r2, r1
	ldreq r5, _02092D90 ; =0x020FF500
	beq _02092CB8
_02092C8C:
	ldr r1, [r9, #0x0]
	ldr r1, [r1, #0x0]
	cmp r1, #0x11
	bne _02092CA8
	cmp r0, #0x1
	ldreq r5, _02092D94 ; =0x020FF518
	beq _02092CB8
_02092CA8:
	cmp r1, #0x3
	bne _02092CB8
	cmp r0, #0x1
	ldreq r5, _02092D98 ; =0x020FF50C
_02092CB8:
	mov r7, #0x1
	mov r6, r7
	mov r1, #0x20
	b _02092CF8
_02092CC8:
	cmp r1, #0x100
	movge r7, #0x5
	movge r6, #0x10
	movge r1, #0x7
	bge _02092CF8
	cmp r1, #0x80
	movge r6, #0x8
	movge r1, r6
	movge r7, #0x4
	movlt r7, #0x3
	movlt r6, #0x4
	movlt r1, #0xb
_02092CF8:
	mul r1, r0, r1
	mov r0, r1, lsl #0x1
	add r1, r0, #0x7
	mov r0, r1, asr #0x1
	add r0, r1, r0, lsr #0x1e
	cmp r5, #0x0
	mov r1, r0, asr #0x2
	bne _02092D74
	ldr r0, [r4, #0x8]
	cmp r1, r0
	movle r0, r4
	ble _02092D30
	mov r0, r4
	bl FUN_02094EBC
_02092D30:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r5, [r4, #0x0]
	mov r1, r9
	mov r2, r7
	add r0, r5, #0x4
	bl FUN_02092A50
	add r1, r0, #0x2
	mov r0, r1, asr #0x8
	strb r0, [r5, #0x0]
	strb r1, [r5, #0x1]
	strb r7, [r5, #0x2]
	strb r6, [r5, #0x3]
	b _02092D78
_02092D74:
	mov r1, #0x8
_02092D78:
	str r5, [r8, #0x0]
	add r0, r1, #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_02092D8C: .word 0x00010001
_02092D90: .word 0x020FF500
_02092D94: .word 0x020FF518
_02092D98: .word 0x020FF50C

	arm_func_start FUN_02092D9C
FUN_02092D9C: ; 0x02092D9C
	stmdb sp!, {r4-r10,lr}
	mov r10, r0
	mov r1, r10
	rsb r0, r10, #0x0
	bl _u32_div_f
	movs r8, r1
	mov r7, r10
	mov r5, #0x0
	mov r6, #0x1
	mvn r4, #0x0
	beq _02092E04
_02092DC8:
	mov r0, r7
	mov r1, r8
	bl _u32_div_f
	mov r9, r1
	mov r0, r7
	mov r1, r8
	bl _u32_div_f
	mla r1, r0, r6, r5
	mov r5, r6
	mov r7, r8
	mov r6, r1
	mov r8, r9
	cmp r9, #0x0
	rsb r4, r4, #0x0
	bne _02092DC8
_02092E04:
	cmp r4, #0x0
	sublt r5, r10, r5
	cmp r7, #0x1
	movne r1, #0x0
	bne _02092E24
	mov r0, r5
	mov r1, r10
	bl _u32_div_f
_02092E24:
	mov r0, r1
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start FUN_02092E30
FUN_02092E30: ; 0x02092E30
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r7, r3
	mov r9, r1
	mov r6, #0x0
	mov r10, r0
	mov r8, r2
	mov r4, r6
	cmp r7, #0x0
	add r5, r9, r7, lsl #0x2
	ldr r11, [sp, #0x30]
	ble _02092EC0
	mov r0, #0x1
	str r6, [sp, #0x4]
	str r0, [sp, #0x0]
_02092E6C:
	ldr r1, [r9, #0x0]
	mov r0, r9
	mul r3, r1, r11
	mov r1, r8
	mov r2, r7
	bl FUN_020948AC
	add r1, r0, r6
	ldr r0, [r5, #0x0]
	cmp r1, r6
	ldrcc r6, [sp, #0x0]
	add r0, r0, r1
	str r0, [r5, #0x0]
	ldr r0, [r5, #0x0]
	ldrcs r6, [sp, #0x4]
	cmp r0, r1
	add r4, r4, #0x1
	addcc r6, r6, #0x1
	cmp r4, r7
	add r9, r9, #0x4
	add r5, r5, #0x4
	blt _02092E6C
_02092EC0:
	cmp r6, #0x0
	sub r2, r7, #0x1
	bne _02092F14
	ldr r1, [r9, r2, lsl #0x2]
	ldr r0, [r8, r2, lsl #0x2]
	cmp r1, r0
	bne _02092F00
	cmp r2, #0x0
	ble _02092F00
_02092EE4:
	ldr r1, [r9, r2, lsl #0x2]
	ldr r0, [r8, r2, lsl #0x2]
	cmp r1, r0
	bne _02092F00
	sub r2, r2, #0x1
	cmp r2, #0x0
	bgt _02092EE4
_02092F00:
	ldr r1, [r9, r2, lsl #0x2]
	ldr r0, [r8, r2, lsl #0x2]
	cmp r1, r0
	movcs r6, #0x1
	movcc r6, #0x0
_02092F14:
	cmp r6, #0x0
	beq _02092F3C
	mov r0, r10
	mov r1, r9
	mov r2, r8
	mov r3, r7
	bl FUN_02094354
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
_02092F3C:
	cmp r7, #0x0
	addle sp, sp, #0xc
	mov r1, #0x0
	ldmleia sp!, {r4-r11,lr}
	bxle lr
_02092F50:
	ldr r0, [r9, r1, lsl #0x2]
	str r0, [r10, r1, lsl #0x2]
	add r1, r1, #0x1
	cmp r1, r7
	blt _02092F50
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02092F70
FUN_02092F70:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r11, r2
	mov r6, r11, lsl #0x1
	mov r10, r0
	mov r7, r11
	mov r9, r1
	sub r7, r7, #0x1
	sub r2, r6, #0x1
	mov r0, #0x0
	str r0, [r10, r2, lsl #0x2]
	ldr r0, [r10, r2, lsl #0x2]
	str r3, [sp, #0x0]
	mov r5, r9
	str r0, [r10, #0x0]
	cmp r7, #0x0
	add r4, r10, #0x4
	ble _02092FD8
	add r5, r5, #0x4
	ldr r3, [r9, #0x0]
	mov r0, r4
	mov r1, r5
	mov r2, r7
	bl FUN_0209470C
	str r0, [r4, r7, lsl #0x2]
	add r4, r4, #0x8
_02092FD8:
	sub r8, r11, #0x2
	cmp r8, #0x0
	ble _02093018
_02092FE4:
	mov r0, r5
	sub r7, r7, #0x1
	add r5, r5, #0x4
	ldr r3, [r0, #0x0]
	mov r0, r4
	mov r1, r5
	mov r2, r7
	bl FUN_020948AC
	sub r8, r8, #0x1
	str r0, [r4, r7, lsl #0x2]
	cmp r8, #0x0
	add r4, r4, #0x8
	bgt _02092FE4
_02093018:
	mov r0, r10
	mov r1, r10
	mov r2, r10
	mov r3, r6
	bl FUN_02094468
_0209302C: ; 0x0209302C
	ldr r0, [sp, #0x0]
	mov r1, r9
	mov r2, r11
	bl FUN_020945B8
	ldr r2, [sp, #0x0]
	mov r0, r10
	mov r1, r10
	mov r3, r6
	bl FUN_02094468
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_0209305C
FUN_0209305C:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x64
	ldr r5, [r2, #0x0]
	mov r9, r0
	mov r8, r1
	cmp r8, r9
	add r3, r2, #0x4
	mov r2, #0x14
	movne r7, r9
	addeq r0, r5, #0x1
	mla r4, r5, r2, r3
	mlaeq r7, r0, r2, r3
	ldr r5, [r8, #0x4]
	cmp r5, #0x0
	movle r0, #0x0
	strle r0, [r9, #0x4]
	addle sp, sp, #0x64
	movle r0, #0x1
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r0, [r7, #0x8]
	mov r6, r5, lsl #0x1
	cmp r6, r0
	movle r0, r7
	ble _020930CC
	mov r0, r7
	mov r1, r6
	bl FUN_02094EBC
_020930CC:
	cmp r0, #0x0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	str r6, [r7, #0x4]
	mov r0, #0x0
	str r0, [r7, #0xc]
	cmp r5, #0x4
	bne _0209310C
	ldr r0, [r7, #0x0]
	ldr r1, [r8, #0x0]
	add r3, sp, #0x0
	mov r2, #0x4
	bl FUN_02092F70
	b _02093170
_0209310C:
	cmp r5, #0x8
	bne _0209312C
	ldr r0, [r7, #0x0]
	ldr r1, [r8, #0x0]
	add r3, sp, #0x20
	mov r2, #0x8
	bl FUN_02092F70
	b _02093170
_0209312C:
	ldr r0, [r4, #0x8]
	cmp r6, r0
	movle r0, r4
	ble _02093148
	mov r0, r4
	mov r1, r6
	bl FUN_02094EBC
_02093148:
	cmp r0, #0x0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r0, [r7, #0x0]
	ldr r1, [r8, #0x0]
	ldr r3, [r4, #0x0]
	mov r2, r5
	bl FUN_02092F70
_02093170:
	cmp r6, #0x0
	ble _02093194
	ldr r1, [r7, #0x0]
	sub r0, r6, #0x1
	ldr r0, [r1, r0, lsl #0x2]
	cmp r0, #0x0
	ldreq r0, [r7, #0x4]
	subeq r0, r0, #0x1
	streq r0, [r7, #0x4]
_02093194:
	cmp r7, r9
	beq _020931A8
	mov r0, r9
	mov r1, r7
	bl FUN_02094E24
_020931A8:
	mov r0, #0x1
	add sp, sp, #0x64
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_020931B8
FUN_020931B8:
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r12, [r3, #0x4]
	cmp r12, #0x0
	ble _020931FC
	ldr r12, [r3, #0x0]
	ldr r12, [r12, #0x0]
	ands r12, r12, #0x1
	beq _020931FC
	ldr lr, [sp, #0x10]
	mov r12, #0x0
	str lr, [sp, #0x0]
	str r12, [sp, #0x4]
	bl FUN_020916C8
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
_020931FC:
	ldr r12, [sp, #0x10]
	str r12, [sp, #0x0]
	bl FUN_02091ECC
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_02093214
FUN_02093214:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	mov r1, r0
	mov r2, lr
	mov r3, r12
	mov r0, #0x0
	bl FUN_02093248
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_02093248
FUN_02093248:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4c
	mov r6, r3
	ldr r3, [r6, #0x4]
	mov r8, r0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	cmp r3, #0x0
	ldr r4, [sp, #0x70]
	beq _02093288
	cmp r3, #0x1
	bne _02093298
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02093298
_02093288:
	add sp, sp, #0x4c
	mov r0, #0x0
	ldmia sp!, {r4-r11,lr}
	bx lr
_02093298:
	ldr r0, [sp, #0x4]
	mov r1, r6
	bl FUN_02094B98
_020932A4: ; 0x020932A4
	cmp r0, #0x0
	bge _020932F8
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _020932D4
	ldr r1, [sp, #0x4]
	bl FUN_02094E24
_020932C0: ; 0x020932C0
	cmp r0, #0x0
	addeq sp, sp, #0x4c
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
_020932D4:
	cmp r8, #0x0
	beq _020932E8
	mov r0, r8
	mov r1, #0x0
	bl FUN_02094D7C
_020932E8:
	add sp, sp, #0x4c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020932F8:
	ldr r3, [r4, #0x0]
	add r0, r4, #0x4
	mov r2, #0x14
	mla r1, r3, r2, r0
	mov r3, #0x0
	str r3, [r1, #0xc]
	ldr r5, [r4, #0x0]
	str r1, [sp, #0x14]
	add r4, r5, #0x1
	mla r1, r4, r2, r0
	add r3, r5, #0x2
	str r1, [sp, #0x18]
	mla r1, r3, r2, r0
	cmp r8, #0x0
	str r1, [sp, #0x1c]
	addeq r1, r5, #0x3
	mlaeq r8, r1, r2, r0
	mov r0, r6
	bl FUN_02095188
	mov r1, r0, lsr #0x1f
	rsb r0, r1, r0, lsl #0x1b
	add r0, r1, r0, ror #0x1b
	rsb r0, r0, #0x20
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x1c]
	ldr r2, [sp, #0x8]
	mov r1, r6
	bl FUN_02094250
_02093368: ; 0x02093368
	cmp r0, #0x0
	addeq sp, sp, #0x4c
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r2, [sp, #0x8]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x4]
	ldr r3, [sp, #0x1c]
	mov r4, #0x0
	add r2, r2, #0x20
	str r4, [r3, #0xc]
	bl FUN_02094250
_0209339C: ; 0x0209339C
	cmp r0, #0x0
	addeq sp, sp, #0x4c
	moveq r0, r4
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r0, [sp, #0x18]
	mov r1, r4
	str r1, [r0, #0xc]
	ldr r0, [sp, #0x1c]
	ldr r0, [r0, #0x4]
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x28]
	ldr r4, [r0, #0x4]
	add r0, sp, #0x38
	sub r1, r4, r1
	str r1, [sp, #0x10]
	bl FUN_0209502C
	ldr r0, [sp, #0x18]
	ldr r2, [r0, #0x0]
	ldr r0, [sp, #0x28]
	sub r1, r0, #0x1
	ldr r0, [sp, #0x10]
	add r0, r2, r0, lsl #0x2
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x28]
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x18]
	ldr r2, [r0, #0x8]
	ldr r0, [sp, #0x28]
	cmp r0, #0x1
	add r0, r2, #0x1
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x1c]
	moveq r5, #0x0
	ldr r2, [r0, #0x0]
	ldr r0, [r2, r1, lsl #0x2]
	str r0, [sp, #0x24]
	ldrne r0, [sp, #0x28]
	subne r0, r0, #0x2
	ldrne r5, [r2, r0, lsl #0x2]
	ldr r0, [sp, #0x18]
	ldr r2, [r8, #0x8]
	ldr r1, [r0, #0x0]
	sub r0, r4, #0x1
	add r7, r1, r0, lsl #0x2
	ldr r0, [sp, #0x10]
	add r1, r0, #0x1
	cmp r1, r2
	movle r0, r8
	ble _02093470
	mov r0, r8
	bl FUN_02094EBC
_02093470:
	cmp r0, #0x0
	beq _020937D4
	ldr r0, [sp, #0x4]
	ldr r1, [r6, #0xc]
	ldr r3, [r0, #0xc]
	ldr r0, [sp, #0x10]
	sub r2, r0, #0x1
	eor r0, r3, r1
	str r0, [r8, #0xc]
	ldr r0, [sp, #0x10]
	str r0, [r8, #0x4]
	ldr r0, [sp, #0x28]
	ldr r3, [r8, #0x0]
	add r1, r0, #0x1
	add r0, r3, r2, lsl #0x2
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x14]
	ldr r0, [r0, #0x8]
	cmp r1, r0
	ldrle r0, [sp, #0x14]
	ble _020934CC
	ldr r0, [sp, #0x14]
	bl FUN_02094EBC
_020934CC:
	cmp r0, #0x0
	beq _020937D4
	ldr r1, [sp, #0x1c]
	add r0, sp, #0x38
	bl FUN_02094B98
_020934E0: ; 0x020934E0
	cmp r0, #0x0
	blt _02093520
	add r0, sp, #0x38
	ldr r2, [sp, #0x1c]
	mov r1, r0
	bl FUN_02093B50
_020934F8: ; 0x020934F8
	cmp r0, #0x0
	beq _020937D4
	ldr r0, [sp, #0x20]
	mov r2, #0x1
	str r2, [r0, #0x0]
	ldr r0, [r8, #0x4]
	ldr r1, [r8, #0x0]
	sub r0, r0, #0x1
	str r2, [r1, r0, lsl #0x2]
	b _0209352C
_02093520:
	ldr r0, [r8, #0x4]
	sub r0, r0, #0x1
	str r0, [r8, #0x4]
_0209352C:
	ldr r0, [sp, #0x10]
	sub r1, r0, #0x1
	ldr r0, [sp, #0x20]
	cmp r1, #0x0
	sub r0, r0, #0x4
	str r0, [sp, #0x20]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ble _0209377C
	ldr r8, _020937E4 ; =0x0000FFFF
	cmp r1, #0x0
	and r0, r5, r8
	str r0, [sp, #0x2c]
	and r0, r8, r5, lsr #0x10
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x24]
	and r4, r0, r8
	ble _0209377C
	and r9, r8, r0, lsr #0x10
	mvn r0, #0x0
	str r0, [sp, #0x34]
_02093580:
	ldr r1, [sp, #0x38]
	ldr r0, [sp, #0x3c]
	sub r1, r1, #0x4
	add r0, r0, #0x1
	str r0, [sp, #0x3c]
	str r1, [sp, #0x38]
	ldr r11, [r7, #0x0]
	ldr r0, [sp, #0x24]
	ldr r5, [r7, #-0x4]
	cmp r11, r0
	ldreq r6, [sp, #0x34]
	beq _020935C4
	ldr r2, [sp, #0x24]
	mov r0, r11
	mov r1, r5
	bl FUN_02092260
	mov r6, r0
_020935C4:
	ldr r0, [sp, #0x2c]
	and r2, r6, r8
	mul r12, r0, r2
	ldr r0, [sp, #0x30]
	and lr, r8, r6, lsr #0x10
	ldr r1, [sp, #0x30]
	mul r0, r2, r0
	mul r3, r1, lr
	ldr r1, [sp, #0x2c]
	mul r10, r9, lr
	mla r1, lr, r1, r0
	cmp r1, r0
	addcc r3, r3, #0x10000
	and r0, r8, r1, lsr #0x10
	add r3, r3, r0
	and r0, r1, r8
	add r12, r12, r0, lsl #0x10
	cmp r12, r0, lsl #0x10
	mul r0, r2, r9
	mul r1, r4, r2
	mla r2, lr, r4, r0
	addcc r3, r3, #0x1
	cmp r2, r0
	addcc r10, r10, #0x10000
	and r0, r8, r2, lsr #0x10
	add r10, r10, r0
	and r0, r2, r8
	add r1, r1, r0, lsl #0x10
	cmp r1, r0, lsl #0x10
	addcc r10, r10, #0x1
	sub r1, r5, r1
	cmp r1, r5
	addhi r10, r10, #0x1
	subs r0, r11, r10
	bne _02093674
	cmp r3, r1
	blo _02093674
	cmp r3, r1
	bne _0209366C
	ldr r0, [r7, #-0x8]
	cmp r12, r0
	bls _02093674
_0209366C:
	sub r6, r6, #0x1
	b _020935C4
_02093674:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x1c]
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0x0]
	ldr r2, [sp, #0x28]
	mov r3, r6
	bl FUN_0209470C
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x28]
	ldr r3, [r1, #0x0]
	ldr r1, [sp, #0x28]
	str r0, [r3, r2, lsl #0x2]
	add r1, r1, #0x1
	cmp r1, #0x0
	ble _020936D4
	ldr r0, [sp, #0x14]
	ldr r2, [r0, #0x0]
_020936B8:
	sub r0, r1, #0x1
	ldr r0, [r2, r0, lsl #0x2]
	cmp r0, #0x0
	bne _020936D4
	sub r1, r1, #0x1
	cmp r1, #0x0
	bgt _020936B8
_020936D4:
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x14]
	str r1, [r0, #0x4]
	add r0, sp, #0x38
	mov r1, r0
	ldr r5, [sp, #0x3c]
	bl FUN_02093A0C
	ldr r0, [sp, #0x18]
	ldr r1, [r0, #0x4]
	ldr r0, [sp, #0x3c]
	add r0, r1, r0
	sub r1, r0, r5
	ldr r0, [sp, #0x18]
	str r1, [r0, #0x4]
	ldr r0, [sp, #0x44]
	cmp r0, #0x0
	beq _0209374C
	add r0, sp, #0x38
	ldr r2, [sp, #0x1c]
	mov r1, r0
	sub r6, r6, #0x1
	ldr r5, [sp, #0x3c]
	bl FUN_02093DD0
	ldr r0, [sp, #0x18]
	ldr r1, [r0, #0x4]
	ldr r0, [sp, #0x3c]
	sub r0, r0, r5
	add r1, r1, r0
	ldr r0, [sp, #0x18]
	str r1, [r0, #0x4]
_0209374C:
	ldr r0, [sp, #0x20]
	sub r7, r7, #0x4
	str r6, [r0], #-0x4
	str r0, [sp, #0x20]
	ldr r0, [sp, #0xc]
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	sub r1, r0, #0x1
	ldr r0, [sp, #0xc]
	cmp r0, r1
	blt _02093580
_0209377C:
	ldr r0, [sp, #0x18]
	bl FUN_02095040
_02093784: ; 0x02093784
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _020937C4
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0x4]
	ldr r1, [sp, #0x18]
	add r2, r2, #0x20
	ldr r4, [r3, #0xc]
	bl FUN_02094134
_020937A8: ; 0x020937A8
	cmp r0, #0x0
	addeq sp, sp, #0x4c
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r0, [sp, #0x0]
	str r4, [r0, #0xc]
_020937C4:
	add sp, sp, #0x4c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020937D4:
	mov r0, #0x0
	add sp, sp, #0x4c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020937E4: .word 0x0000FFFF

	arm_func_start FUN_020937E8
FUN_020937E8: ; 0x020937E8
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r5, [sp, #0x20]
	mov r7, r2
	mov r9, r0
	mov r8, r1
	mov r6, r3
	cmp r7, r5
	bge _02093824
	mov r1, r7
	mov r0, r8
	mov r7, r5
	mov r8, r6
	mov r5, r1
	mov r6, r0
_02093824:
	ldr r3, [r6, #0x0]
	mov r0, r9
	mov r1, r8
	mov r2, r7
	add r4, r9, r7, lsl #0x2
	bl FUN_0209470C
	str r0, [r9, r7, lsl #0x2]
_02093840:
	sub r0, r5, #0x1
	cmp r0, #0x0
	addle sp, sp, #0x4
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r3, [r6, #0x4]
	mov r1, r8
	mov r2, r7
	add r0, r9, #0x4
	bl FUN_020948AC
	sub r1, r5, #0x2
	cmp r1, #0x0
	addle sp, sp, #0x4
	str r0, [r4, #0x4]
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r3, [r6, #0x8]
	mov r1, r8
	mov r2, r7
	add r0, r9, #0x8
	bl FUN_020948AC
	sub r1, r5, #0x3
	cmp r1, #0x0
	addle sp, sp, #0x4
	str r0, [r4, #0x8]
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r3, [r6, #0xc]
	mov r1, r8
	mov r2, r7
	add r0, r9, #0xc
	bl FUN_020948AC
	sub r5, r5, #0x4
	cmp r5, #0x0
	addle sp, sp, #0x4
	str r0, [r4, #0xc]
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r3, [r6, #0x10]
	mov r1, r8
	mov r2, r7
	add r0, r9, #0x10
	bl FUN_020948AC
	str r0, [r4, #0x10]
	add r4, r4, #0x10
	add r9, r9, #0x10
	add r6, r6, #0x10
	b _02093840
_02093900: ; 0x02093900
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_0209390C
FUN_0209390C:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldr r6, [r9, #0x4]
	mov r8, r2
	mov r10, r0
	cmp r6, #0x0
	ldr r5, [r8, #0x4]
	beq _02093938
	cmp r5, #0x0
	bne _02093954
_02093938:
	mov r0, r10
	mov r1, #0x0
	bl FUN_02094D7C
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_02093954:
	ldr r1, [r9, #0xc]
	ldr r0, [r8, #0xc]
	cmp r10, r9
	add r7, r6, r5
	eor r11, r1, r0
	beq _02093974
	cmp r10, r8
	bne _0209398C
_02093974:
	ldr r0, [r3, #0x0]
	add r2, r3, #0x4
	add r1, r0, #0x1
	mov r0, #0x14
	mla r4, r1, r0, r2
	b _02093990
_0209398C:
	mov r4, r10
_02093990:
	ldr r0, [r4, #0x8]
	cmp r7, r0
	movle r0, r4
	ble _020939AC
	mov r0, r4
	mov r1, r7
	bl FUN_02094EBC
_020939AC:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	str r7, [r4, #0x4]
	str r5, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, [r9, #0x0]
	ldr r3, [r8, #0x0]
	mov r2, r6
	bl FUN_020937E8
	mov r0, r4
	str r11, [r10, #0xc]
	bl FUN_02095040
	cmp r10, r4
	beq _020939FC
	mov r0, r10
	mov r1, r4
	bl FUN_02094E24
_020939FC:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02093A0C
FUN_02093A0C: ; 0x02093A0C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldr r1, [r6, #0xc]
	mov r3, #0x0
	mov r7, r0
	mov r5, r2
	mov r4, r3
	cmp r1, #0x0
	beq _02093A54
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	movne r0, r6
	moveq r3, #0x1
	movne r6, r5
	movne r5, r0
	moveq r4, r3
	b _02093A60
_02093A54:
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	movne r3, #0x1
_02093A60:
	cmp r3, #0x0
	beq _02093A94
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_02093CB4
_02093A78: ; 0x02093A78
	cmp r0, #0x0
	moveq r0, #0x0
	add sp, sp, #0x4
	strne r4, [r7, #0xc]
	movne r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_02093A94:
	ldr r0, [r5, #0x4]
	ldr r1, [r6, #0x4]
	cmp r1, r0
	movle r1, r0
	ldr r0, [r7, #0x8]
	cmp r1, r0
	movle r0, r7
	ble _02093ABC
	mov r0, r7
	bl FUN_02094EBC
_02093ABC:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r6
	mov r1, r5
	bl FUN_02094B98
_02093ADC: ; 0x02093ADC
	cmp r0, #0x0
	bge _02093B14
	mov r0, r7
	mov r1, r5
	mov r2, r6
	bl FUN_02093B50
_02093AF4: ; 0x02093AF4
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, #0x1
	str r0, [r7, #0xc]
	b _02093B40
_02093B14:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_02093B50
_02093B24: ; 0x02093B24
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, #0x0
	str r0, [r7, #0xc]
_02093B40:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02093B50
FUN_02093B50:
	stmdb sp!, {r4-r10,lr}
	mov r8, r1
	mov r7, r2
	ldr r5, [r7, #0x4]
	ldr r6, [r8, #0x4]
	mov r4, r0
	cmp r6, r5
	movlt r0, #0x0
	ldmltia sp!, {r4-r10,lr}
	bxlt lr
	ldr r1, [r4, #0x8]
	cmp r6, r1
	ble _02093B8C
	mov r1, r6
	bl FUN_02094EBC
_02093B8C:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
	mov r3, #0x0
	mov r0, r3
	cmp r5, #0x0
	ldr r2, [r8, #0x0]
	ldr r9, [r7, #0x0]
	ldr r1, [r4, #0x0]
	ble _02093C0C
	mov r12, r3
	mov r7, r3
	mov lr, #0x1
_02093BC4:
	cmp r3, #0x0
	ldr r10, [r2], #0x4
	ldr r8, [r9], #0x4
	beq _02093BEC
	cmp r10, r8
	movls r3, lr
	sub r8, r10, r8
	movhi r3, r12
	sub r10, r8, #0x1
	b _02093BFC
_02093BEC:
	cmp r10, r8
	movcc r3, lr
	movcs r3, r7
	sub r10, r10, r8
_02093BFC:
	add r0, r0, #0x1
	cmp r0, r5
	str r10, [r1], #0x4
	blt _02093BC4
_02093C0C:
	cmp r3, #0x0
	beq _02093C3C
	cmp r0, r6
	bge _02093C3C
_02093C1C:
	ldr r5, [r2], #0x4
	add r0, r0, #0x1
	sub r3, r5, #0x1
	cmp r5, r3
	str r3, [r1], #0x4
	bhi _02093C3C
	cmp r0, r6
	blt _02093C1C
_02093C3C:
	cmp r1, r2
	beq _02093C9C
_02093C44:
	cmp r0, r6
	bge _02093C9C
	ldr r5, [r2, #0x0]
	add r3, r0, #0x1
	str r5, [r1, #0x0]
	cmp r3, r6
	bge _02093C9C
	ldr r5, [r2, #0x4]
	add r3, r0, #0x2
	str r5, [r1, #0x4]
	cmp r3, r6
	bge _02093C9C
	ldr r5, [r2, #0x8]
	add r3, r0, #0x3
	str r5, [r1, #0x8]
	cmp r3, r6
	ldrlt r3, [r2, #0xc]
	add r0, r0, #0x4
	strlt r3, [r1, #0xc]
	addlt r2, r2, #0x10
	addlt r1, r1, #0x10
	blt _02093C44
_02093C9C:
	mov r0, r4
	str r6, [r4, #0x4]
	bl FUN_02095040
	mov r0, #0x1
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start FUN_02093CB4
FUN_02093CB4:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r8, r2
	ldr r2, [r4, #0x4]
	ldr r1, [r8, #0x4]
	mov r9, r0
	cmp r2, r1
	movlt r0, r4
	movlt r4, r8
	movlt r8, r0
	ldr r6, [r4, #0x4]
	ldr r0, [r9, #0x8]
	add r1, r6, #0x1
	cmp r1, r0
	ldr r7, [r8, #0x4]
	movle r0, r9
	ble _02093D04
	mov r0, r9
	bl FUN_02094EBC
_02093D04:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	str r6, [r9, #0x4]
	ldr r5, [r4, #0x0]
	ldr r4, [r9, #0x0]
	ldr r2, [r8, #0x0]
	mov r0, r4
	mov r1, r5
	mov r3, r7
	bl FUN_02094468
_02093D38: ; 0x02093D38
	cmp r0, #0x0
	add r4, r4, r7, lsl #0x2
	add r5, r5, r7, lsl #0x2
	beq _02093D9C
	cmp r7, r6
	bge _02093D7C
_02093D50:
	ldr r2, [r5], #0x4
	mov r3, r4
	add r1, r2, #0x1
	str r1, [r4], #0x4
	ldr r1, [r3, #0x0]
	add r7, r7, #0x1
	cmp r1, r2
	movcs r0, #0x0
	bhs _02093D7C
	cmp r7, r6
	blt _02093D50
_02093D7C:
	cmp r7, r6
	blt _02093D9C
	cmp r0, #0x0
	movne r0, #0x1
	strne r0, [r4], #0x4
	ldrne r0, [r9, #0x4]
	addne r0, r0, #0x1
	strne r0, [r9, #0x4]
_02093D9C:
	cmp r4, r5
	beq _02093DC0
	cmp r7, r6
	bge _02093DC0
_02093DAC:
	ldr r0, [r5], #0x4
	add r7, r7, #0x1
	cmp r7, r6
	str r0, [r4], #0x4
	blt _02093DAC
_02093DC0:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_02093DD0
FUN_02093DD0: ; 0x02093DD0
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r4, r2
	ldr r2, [r5, #0xc]
	ldr r1, [r4, #0xc]
	mov r6, r0
	eors r0, r2, r1
	beq _02093E74
	cmp r2, #0x0
	movne r0, r5
	movne r5, r4
	movne r4, r0
	mov r0, r5
	mov r1, r4
	bl FUN_02094B98
_02093E0C: ; 0x02093E0C
	cmp r0, #0x0
	bge _02093E40
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_02093B50
_02093E24: ; 0x02093E24
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, #0x1
	str r0, [r6, #0xc]
	b _02093E68
_02093E40:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_02093B50
_02093E50: ; 0x02093E50
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, #0x0
	str r0, [r6, #0xc]
_02093E68:
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_02093E74:
	cmp r2, #0x0
	movne r0, #0x1
	strne r0, [r6, #0xc]
	moveq r0, #0x0
	streq r0, [r6, #0xc]
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_02093CB4
_02093E98: ; 0x02093E98
	cmp r0, #0x0
	moveq r0, #0x0
	movne r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02093EAC
FUN_02093EAC: ; 0x02093EAC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r4, r1
	mov r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [r5, #0xc]
	cmp r2, #0x0
	beq _02093EF8
	mov r2, #0x0
	str r2, [r5, #0xc]
	bl FUN_0209400C
	mov r1, #0x1
	add sp, sp, #0x4
	str r1, [r5, #0xc]
	ldmia sp!, {r4-r5,lr}
	bx lr
_02093EF8:
	ldr r1, [r5, #0x4]
	cmp r1, #0x1
	bgt _02093F9C
	cmp r1, #0x0
	bne _02093F54
	ldr r1, [r5, #0x8]
	cmp r1, #0x1
	bge _02093F20
	mov r1, #0x1
	bl FUN_02094EBC
_02093F20:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [r5, #0x0]
	mov r0, #0x1
	str r4, [r1, #0x0]
	str r0, [r5, #0xc]
	add sp, sp, #0x4
	str r0, [r5, #0x4]
	ldmia sp!, {r4-r5,lr}
	bx lr
_02093F54:
	ldr r2, [r5, #0x0]
	ldr r1, [r2, #0x0]
	cmp r1, r4
	moveq r0, #0x0
	streq r0, [r5, #0x4]
	beq _02093F8C
	cmp r1, r4
	subhi r0, r1, r4
	strhi r0, [r2, #0x0]
	movls r0, #0x1
	strls r0, [r5, #0xc]
	ldrls r0, [r5, #0x0]
	subls r1, r4, r1
	strls r1, [r0, #0x0]
_02093F8C:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_02093F9C:
	mov r0, #0x0
	mov r1, #0x1
_02093FA4:
	ldr r12, [r5, #0x0]
	mov r3, r0, lsl #0x2
	ldr r2, [r12, r0, lsl #0x2]
	cmp r2, r4
	ldrcs r1, [r12, r3]
	subcs r1, r1, r4
	strcs r1, [r12, r3]
	bhs _02093FDC
	ldr r2, [r12, r3]
	add r0, r0, #0x1
	sub r2, r2, r4
	mov r4, r1
	str r2, [r12, r3]
	b _02093FA4
_02093FDC:
	ldr r1, [r5, #0x0]
	ldr r1, [r1, r3]
	cmp r1, #0x0
	bne _02093FFC
	ldr r1, [r5, #0x4]
	sub r1, r1, #0x1
	cmp r0, r1
	streq r1, [r5, #0x4]
_02093FFC:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209400C
FUN_0209400C:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r4, r1
	mov r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [r5, #0xc]
	cmp r2, #0x0
	beq _020940B4
	ldr r2, [r5, #0x4]
	cmp r2, #0x1
	ble _02094064
	mov r2, #0x0
	str r2, [r5, #0xc]
	bl FUN_02093EAC
	mov r1, #0x1
	add sp, sp, #0x4
	str r1, [r5, #0xc]
	ldmia sp!, {r4-r5,lr}
	bx lr
_02094064:
	ldr r2, [r5, #0x0]
	ldr r1, [r2, #0x0]
	cmp r1, r4
	subhi r0, r1, r4
	strhi r0, [r2, #0x0]
	bhi _020940A4
	cmp r1, r4
	movcs r0, #0x0
	strcs r0, [r5, #0xc]
	strcs r0, [r5, #0x4]
	bhs _020940A4
	mov r0, #0x0
	str r0, [r5, #0xc]
	ldr r0, [r5, #0x0]
	sub r1, r4, r1
	str r1, [r0, #0x0]
_020940A4:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020940B4:
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	add r1, r1, #0x1
	cmp r1, r2
	ble _020940CC
	bl FUN_02094EBC
_020940CC:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [r5, #0x0]
	ldr r0, [r5, #0x4]
	mov r3, #0x0
	str r3, [r1, r0, lsl #0x2]
	mov r0, #0x1
_020940F4:
	ldr r2, [r5, #0x0]
	ldr r1, [r2, r3, lsl #0x2]
	add r1, r4, r1
	cmp r4, r1
	str r1, [r2, r3, lsl #0x2]
	movhi r4, r0
	addhi r3, r3, #0x1
	bhi _020940F4
	ldr r0, [r5, #0x4]
	cmp r3, r0
	addge r0, r0, #0x1
	strge r0, [r5, #0x4]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02094134
FUN_02094134:
	stmdb sp!, {r4-r8,lr}
	mov r7, r1
	mov r1, r2, asr #0x4
	mov r3, r2, lsr #0x1f
	add r1, r2, r1, lsr #0x1b
	rsb r2, r3, r2, lsl #0x1b
	add r4, r3, r2, ror #0x1b
	ldr r2, [r7, #0x4]
	mov r6, r1, asr #0x5
	mov r8, r0
	cmp r6, r2
	rsb r5, r4, #0x20
	ble _0209417C
	mov r1, #0x0
	bl FUN_02094D7C
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209417C:
	cmp r8, r7
	beq _020941B4
	sub r1, r2, r6
	ldr r2, [r8, #0x8]
	add r1, r1, #0x2
	cmp r1, r2
	ble _0209419C
	bl FUN_02094EBC
_0209419C:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r0, [r7, #0xc]
	str r0, [r8, #0xc]
_020941B4:
	ldr r0, [r7, #0x0]
	ldr r1, [r7, #0x4]
	add r2, r0, r6, lsl #0x2
	ldr r0, [r8, #0x0]
	sub r7, r1, r6
	mov r6, r2
	str r7, [r8, #0x4]
	cmp r4, #0x0
	bne _020941FC
	add r2, r7, #0x1
	cmp r2, #0x0
	ble _0209423C
_020941E4:
	ldr r1, [r6], #0x4
	sub r2, r2, #0x1
	cmp r2, #0x0
	str r1, [r0], #0x4
	bgt _020941E4
	b _0209423C
_020941FC:
	cmp r7, #0x1
	add r6, r2, #0x4
	ldr r3, [r2, #0x0]
	mov r2, #0x1
	ble _0209422C
_02094210:
	mov r1, r3, lsr r4
	ldr r3, [r6], #0x4
	add r2, r2, #0x1
	orr r1, r1, r3, lsl r5
	cmp r2, r7
	str r1, [r0], #0x4
	blt _02094210
_0209422C:
	mov r1, r3, lsr r4
	str r1, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
_0209423C:
	mov r0, r8
	bl FUN_02095040
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_02094250
FUN_02094250:
	stmdb sp!, {r4-r10,lr}
	mov r4, r1
	mov r7, r2
	mov r1, r7, asr #0x4
	mov r5, r0
	add r2, r7, r1, lsr #0x1b
	ldr r1, [r4, #0x4]
	ldr r3, [r5, #0x8]
	add r1, r1, r2, asr #0x5
	add r1, r1, #0x1
	cmp r1, r3
	mov r6, r2, asr #0x5
	ble _02094288
	bl FUN_02094EBC
_02094288:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
	ldr r0, [r4, #0xc]
	mov r1, r7, lsr #0x1f
	str r0, [r5, #0xc]
	ldr r3, [r4, #0x4]
	rsb r0, r1, r7, lsl #0x1b
	adds r12, r1, r0, ror #0x1b
	ldr r2, [r4, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r3, r6
	mov r3, #0x0
	str r3, [r0, r1, lsl #0x2]
	rsb r3, r12, #0x20
	bne _020942F0
	ldr r1, [r4, #0x4]
	subs r7, r1, #0x1
	bmi _02094324
_020942D8:
	ldr r3, [r2, r7, lsl #0x2]
	add r1, r6, r7
	str r3, [r0, r1, lsl #0x2]
	subs r7, r7, #0x1
	bpl _020942D8
	b _02094324
_020942F0:
	ldr r1, [r4, #0x4]
	subs r1, r1, #0x1
	bmi _02094324
_020942FC:
	add r9, r6, r1
	add r8, r9, #0x1
	ldr r10, [r2, r1, lsl #0x2]
	ldr lr, [r0, r8, lsl #0x2]
	mov r7, r10, lsl r12
	orr lr, lr, r10, lsr r3
	str lr, [r0, r8, lsl #0x2]
	str r7, [r0, r9, lsl #0x2]
	subs r1, r1, #0x1
	bpl _020942FC
_02094324:
	mov r2, r6, lsl #0x2
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r1, [r4, #0x4]
	mov r0, r5
	add r1, r1, r6
	add r1, r1, #0x1
	str r1, [r5, #0x4]
	bl FUN_02095040
	mov r0, #0x1
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start FUN_02094354
FUN_02094354: ; 0x02094354
	stmdb sp!, {r4-r10,lr}
	cmp r3, #0x0
	movle r0, #0x0
	ldmleia sp!, {r4-r10,lr}
	bxle lr
	mov r6, #0x0
	mov r4, r6
	mov lr, r6
	mov r12, r6
	mov r7, r6
	mov r5, #0x1
_02094380:
	ldr r10, [r1, #0x0]
	ldr r9, [r2, #0x0]
	sub r8, r10, r9
	sub r8, r8, r6
	str r8, [r0, #0x0]
	cmp r10, r9
	beq _020943A8
	cmp r10, r9
	movcc r6, r5
	movcs r6, r4
_020943A8:
	sub r8, r3, #0x1
	cmp r8, #0x0
	ble _0209445C
	ldr r10, [r1, #0x4]
	ldr r9, [r2, #0x4]
	sub r8, r10, r9
	sub r8, r8, r6
	str r8, [r0, #0x4]
	cmp r10, r9
	beq _020943DC
	cmp r10, r9
	movcc r6, r5
	movcs r6, lr
_020943DC:
	sub r8, r3, #0x2
	cmp r8, #0x0
	ble _0209445C
	ldr r10, [r1, #0x8]
	ldr r9, [r2, #0x8]
	sub r8, r10, r9
	sub r8, r8, r6
	str r8, [r0, #0x8]
	cmp r10, r9
	beq _02094410
	cmp r10, r9
	movcc r6, r5
	movcs r6, r12
_02094410:
	sub r8, r3, #0x3
	cmp r8, #0x0
	ble _0209445C
	ldr r10, [r1, #0xc]
	ldr r9, [r2, #0xc]
	sub r8, r10, r9
	sub r8, r8, r6
	str r8, [r0, #0xc]
	cmp r10, r9
	beq _02094444
	cmp r10, r9
	movcc r6, r5
	movcs r6, r7
_02094444:
	sub r3, r3, #0x4
	cmp r3, #0x0
	addgt r1, r1, #0x10
	addgt r2, r2, #0x10
	addgt r0, r0, #0x10
	bgt _02094380
_0209445C:
	mov r0, r6
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start FUN_02094468
FUN_02094468:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	cmp r3, #0x0
	addle sp, sp, #0xc
	movle r0, #0x0
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	mov r12, #0x0
	mov r7, r12
	mov r6, r12
	mov r5, r12
	mov r4, r12
	mov lr, r12
	mov r11, r12
	str r12, [sp, #0x0]
	str r12, [sp, #0x4]
	mov r8, #0x1
_020944AC:
	ldr r9, [r1, #0x0]
	add r10, r9, r12
	ldr r9, [r2, #0x0]
	cmp r10, r12
	movcc r12, r8
	add r9, r10, r9
	movcs r12, r7
	cmp r9, r10
	movcc r10, r8
	movcs r10, r6
	str r9, [r0, #0x0]
	sub r9, r3, #0x1
	add r12, r12, r10
	cmp r9, #0x0
	ble _020945A8
	ldr r9, [r1, #0x4]
	ldr r10, [r2, #0x4]
	add r9, r9, r12
	cmp r9, r12
	movcc r12, r8
	add r10, r9, r10
	movcs r12, r5
	cmp r10, r9
	movcc r9, r8
	movcs r9, r4
	add r12, r12, r9
	sub r9, r3, #0x2
	str r10, [r0, #0x4]
	cmp r9, #0x0
	ble _020945A8
	ldr r9, [r1, #0x8]
	ldr r10, [r2, #0x8]
	add r9, r9, r12
	cmp r9, r12
	movcc r12, r8
	add r10, r9, r10
	movcs r12, lr
	cmp r10, r9
	movcc r9, r8
	movcs r9, r11
	add r12, r12, r9
	sub r9, r3, #0x3
	str r10, [r0, #0x8]
	cmp r9, #0x0
	ble _020945A8
	ldr r9, [r1, #0xc]
	ldr r10, [r2, #0xc]
	add r9, r9, r12
	cmp r9, r12
	movcc r12, r8
	add r10, r9, r10
	ldrcs r12, [sp, #0x0]
	cmp r10, r9
	movcc r9, r8
	ldrcs r9, [sp, #0x4]
	sub r3, r3, #0x4
	cmp r3, #0x0
	str r10, [r0, #0xc]
	add r12, r12, r9
	addgt r1, r1, #0x10
	addgt r2, r2, #0x10
	addgt r0, r0, #0x10
	bgt _020944AC
_020945A8:
	mov r0, r12
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_020945B8
FUN_020945B8: ; 0x020945B8
	stmdb sp!, {r4-r8,lr}
	cmp r2, #0x0
	ldmleia sp!, {r4-r8,lr}
	bxle lr
	mov r3, #0x8000
	ldr lr, _02094708 ; =0x0000FFFF
	rsb r12, r3, #0x0
_020945D4:
	ldr r5, [r1, #0x0]
	mov r3, #0x8000
	and r4, r5, lr
	and r7, lr, r5, lsr #0x10
	mul r6, r4, r7
	mul r5, r4, r4
	and r4, r6, lr
	add r8, r5, r4, lsl #0x11
	rsb r3, r3, #0x0
	mul r5, r7, r7
	and r3, r6, r3
	add r3, r5, r3, lsr #0xf
	cmp r8, r4, lsl #0x11
	addcc r3, r3, #0x1
	str r8, [r0, #0x0]
	str r3, [r0, #0x4]
	subs r3, r2, #0x1
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r4, [r1, #0x4]
	and r7, lr, r4, lsr #0x10
	and r3, r4, lr
	mul r6, r3, r7
	mul r4, r3, r3
	and r3, r6, lr
	add r8, r4, r3, lsl #0x11
	mul r5, r7, r7
	and r4, r6, r12
	cmp r8, r3, lsl #0x11
	add r3, r5, r4, lsr #0xf
	addcc r3, r3, #0x1
	str r8, [r0, #0x8]
	str r3, [r0, #0xc]
	subs r3, r2, #0x2
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r5, [r1, #0x8]
	mov r3, #0x8000
	and r4, r5, lr
	and r7, lr, r5, lsr #0x10
	mul r6, r4, r7
	mul r5, r4, r4
	and r4, r6, lr
	add r8, r5, r4, lsl #0x11
	rsb r3, r3, #0x0
	mul r5, r7, r7
	and r3, r6, r3
	add r3, r5, r3, lsr #0xf
	cmp r8, r4, lsl #0x11
	addcc r3, r3, #0x1
	str r8, [r0, #0x10]
	str r3, [r0, #0x14]
	subs r3, r2, #0x3
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r5, [r1, #0xc]
	mov r3, #0x8000
	and r4, r5, lr
	and r7, lr, r5, lsr #0x10
	mul r6, r4, r7
	mul r5, r4, r4
	and r4, r6, lr
	add r8, r5, r4, lsl #0x11
	rsb r3, r3, #0x0
	mul r5, r7, r7
	and r3, r6, r3
	add r3, r5, r3, lsr #0xf
	cmp r8, r4, lsl #0x11
	addcc r3, r3, #0x1
	str r8, [r0, #0x18]
	subs r2, r2, #0x4
	str r3, [r0, #0x1c]
	addne r1, r1, #0x10
	addne r0, r0, #0x20
	bne _020945D4
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_02094708: .word 0x0000FFFF

	arm_func_start FUN_0209470C
FUN_0209470C: ; 0x0209470C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	mov r4, #0x0
	addle sp, sp, #0x4
	movle r0, r4
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r5, _020948A8 ; =0x0000FFFF
	and lr, r3, r5
	and r12, r5, r3, lsr #0x10
_02094738:
	ldr r3, [r1, #0x0]
	and r7, r5, r3, lsr #0x10
	mul r6, lr, r7
	and r3, r3, r5
	mla r9, r12, r3, r6
	mul r8, r3, lr
	mul r3, r7, r12
	cmp r9, r6
	and r6, r9, r5
	addcc r3, r3, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r3, r3, r7
	add r6, r8, r4
	addcc r3, r3, #0x1
	cmp r6, r4
	addcc r3, r3, #0x1
	str r6, [r0, #0x0]
	mov r4, r3
	subs r6, r2, #0x1
	beq _02094898
	ldr r4, [r1, #0x4]
	and r7, r5, r4, lsr #0x10
	mul r6, lr, r7
	and r4, r4, r5
	mla r9, r12, r4, r6
	mul r8, r4, lr
	mul r4, r7, r12
	cmp r9, r6
	and r6, r9, r5
	addcc r4, r4, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r4, r4, r7
	add r6, r8, r3
	addcc r4, r4, #0x1
	cmp r6, r3
	addcc r4, r4, #0x1
	str r6, [r0, #0x4]
	subs r3, r2, #0x2
	beq _02094898
	ldr r3, [r1, #0x8]
	and r7, r5, r3, lsr #0x10
	mul r6, lr, r7
	and r3, r3, r5
	mla r9, r12, r3, r6
	mul r8, r3, lr
	mul r3, r7, r12
	cmp r9, r6
	and r6, r9, r5
	addcc r3, r3, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r3, r3, r7
	add r6, r8, r4
	addcc r3, r3, #0x1
	cmp r6, r4
	addcc r3, r3, #0x1
	str r6, [r0, #0x8]
	mov r4, r3
	subs r6, r2, #0x3
	beq _02094898
	ldr r4, [r1, #0xc]
	and r7, r5, r4, lsr #0x10
	mul r6, lr, r7
	and r4, r4, r5
	mla r9, r12, r4, r6
	mul r8, r4, lr
	mul r4, r7, r12
	cmp r9, r6
	and r6, r9, r5
	addcc r4, r4, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r4, r4, r7
	add r6, r8, r3
	addcc r4, r4, #0x1
	cmp r6, r3
	addcc r4, r4, #0x1
	subs r2, r2, #0x4
	str r6, [r0, #0xc]
	addne r1, r1, #0x10
	addne r0, r0, #0x10
	bne _02094738
_02094898:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020948A8: .word 0x0000FFFF

	arm_func_start FUN_020948AC
FUN_020948AC: ; 0x020948AC
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	mov r12, #0x0
	addle sp, sp, #0x4
	movle r0, r12
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r5, _02094A88 ; =0x0000FFFF
	and r4, r3, r5
	and lr, r5, r3, lsr #0x10
_020948D8:
	ldr r3, [r1, #0x0]
	and r7, r5, r3, lsr #0x10
	mul r6, r4, r7
	and r3, r3, r5
	mla r9, lr, r3, r6
	mul r8, r3, r4
	mul r3, r7, lr
	cmp r9, r6
	and r6, r9, r5
	addcc r3, r3, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r3, r3, r7
	ldr r6, [r0, #0x0]
	addcc r3, r3, #0x1
	add r7, r8, r12
	cmp r7, r12
	add r7, r7, r6
	addcc r3, r3, #0x1
	cmp r7, r6
	addcc r3, r3, #0x1
	mov r12, r3
	str r7, [r0, #0x0]
	subs r6, r2, #0x1
	beq _02094A78
	ldr r12, [r1, #0x4]
	and r7, r5, r12, lsr #0x10
	mul r6, r4, r7
	and r12, r12, r5
	mla r9, lr, r12, r6
	mul r8, r12, r4
	mul r12, r7, lr
	cmp r9, r6
	and r6, r9, r5
	addcc r12, r12, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r12, r12, r7
	add r6, r8, r3
	addcc r12, r12, #0x1
	cmp r6, r3
	ldr r3, [r0, #0x4]
	addcc r12, r12, #0x1
	add r6, r6, r3
	cmp r6, r3
	addcc r12, r12, #0x1
	str r6, [r0, #0x4]
	subs r3, r2, #0x2
	beq _02094A78
	ldr r3, [r1, #0x8]
	and r7, r5, r3, lsr #0x10
	mul r6, r4, r7
	and r3, r3, r5
	mla r9, lr, r3, r6
	mul r8, r3, r4
	mul r3, r7, lr
	cmp r9, r6
	and r6, r9, r5
	addcc r3, r3, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r3, r3, r7
	ldr r6, [r0, #0x8]
	addcc r3, r3, #0x1
	add r7, r8, r12
	cmp r7, r12
	add r7, r7, r6
	addcc r3, r3, #0x1
	cmp r7, r6
	addcc r3, r3, #0x1
	mov r12, r3
	str r7, [r0, #0x8]
	subs r6, r2, #0x3
	beq _02094A78
	ldr r12, [r1, #0xc]
	and r7, r5, r12, lsr #0x10
	mul r6, r4, r7
	and r12, r12, r5
	mla r9, lr, r12, r6
	mul r8, r12, r4
	mul r12, r7, lr
	cmp r9, r6
	and r6, r9, r5
	addcc r12, r12, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r12, r12, r7
	add r6, r8, r3
	addcc r12, r12, #0x1
	cmp r6, r3
	ldr r3, [r0, #0xc]
	addcc r12, r12, #0x1
	add r6, r6, r3
	cmp r6, r3
	addcc r12, r12, #0x1
	subs r2, r2, #0x4
	str r6, [r0, #0xc]
	addne r1, r1, #0x10
	addne r0, r0, #0x10
	bne _020948D8
_02094A78:
	mov r0, r12
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_02094A88: .word 0x0000FFFF

	arm_func_start FUN_02094A8C
FUN_02094A8C:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x0
	addlt sp, sp, #0x4
	movlt r0, #0x0
	ldmltia sp!, {lr}
	bxlt lr
	mov r2, r1, asr #0x4
	add r2, r1, r2, lsr #0x1b
	mov r3, r1, lsr #0x1f
	ldr r12, [r0, #0x4]
	mov lr, r2, asr #0x5
	cmp r12, lr
	rsb r1, r3, r1, lsl #0x1b
	addle sp, sp, #0x4
	add r2, r3, r1, ror #0x1b
	movle r0, #0x0
	ldmleia sp!, {lr}
	bxle lr
	ldr r1, [r0, #0x0]
	mov r0, #0x1
	mov r2, r0, lsl r2
	ldr r1, [r1, lr, lsl #0x2]
	ands r1, r2, r1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_02094AFC
FUN_02094AFC:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r2, r1, asr #0x4
	add r2, r1, r2, lsr #0x1b
	mov r3, r1, lsr #0x1f
	rsb r1, r3, r1, lsl #0x1b
	ldr r4, [r6, #0x4]
	mov r5, r2, asr #0x5
	cmp r4, r5
	add r4, r3, r1, ror #0x1b
	bgt _02094B7C
	ldr r2, [r6, #0x8]
	add r1, r5, #0x1
	cmp r1, r2
	ble _02094B3C
	bl FUN_02094EBC
_02094B3C:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r3, [r6, #0x4]
	add r2, r5, #0x1
	cmp r3, r2
	bge _02094B74
	mov r1, #0x0
_02094B60:
	ldr r0, [r6, #0x0]
	str r1, [r0, r3, lsl #0x2]
	add r3, r3, #0x1
	cmp r3, r2
	blt _02094B60
_02094B74:
	add r0, r5, #0x1
	str r0, [r6, #0x4]
_02094B7C:
	ldr r2, [r6, #0x0]
	mov r0, #0x1
	ldr r1, [r2, r5, lsl #0x2]
	orr r1, r1, r0, lsl r4
	str r1, [r2, r5, lsl #0x2]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02094B98
FUN_02094B98:
	ldr r3, [r0, #0x4]
	ldr r2, [r1, #0x4]
	subs r2, r3, r2
	movne r0, r2
	bxne lr
	subs r2, r3, #0x1
	ldr r12, [r0, #0x0]
	ldr r3, [r1, #0x0]
	bmi _02094BE4
_02094BBC:
	ldr r1, [r12, r2, lsl #0x2]
	ldr r0, [r3, r2, lsl #0x2]
	cmp r1, r0
	beq _02094BDC
	cmp r1, r0
	movhi r0, #0x1
	mvnls r0, #0x0
	bx lr
_02094BDC:
	subs r2, r2, #0x1
	bpl _02094BBC
_02094BE4:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_02094BEC
FUN_02094BEC: ; 0x02094BEC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_02095188
	add r1, r0, #0x7
	mov r0, r1, asr #0x2
	add r0, r1, r0, lsr #0x1d
	mov r0, r0, asr #0x3
	cmp r0, #0x0
	addle sp, sp, #0x4
	sub r12, r0, #0x1
	ldmleia sp!, {r4-r5,lr}
	bxle lr
_02094C24:
	mov r3, r12, lsr #0x1f
	mov r1, r12, asr #0x1
	rsb r2, r3, r12, lsl #0x1e
	add r1, r12, r1, lsr #0x1e
	add r2, r3, r2, ror #0x1e
	ldr r3, [r5, #0x0]
	mov r1, r1, asr #0x2
	ldr r3, [r3, r1, lsl #0x2]
	mov r1, r2, lsl #0x3
	mov r1, r3, lsr r1
	cmp r12, #0x0
	strb r1, [r4], #0x1
	sub r12, r12, #0x1
	bgt _02094C24
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02094C68
FUN_02094C68:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs r5, r2
	mov r7, r0
	mov r6, r1
	bne _02094C88
	bl FUN_02094FE0
	mov r5, r0
_02094C88:
	cmp r5, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r6, #0x0
	mov r4, #0x0
	addeq sp, sp, #0x4
	moveq r0, r5
	streq r4, [r5, #0x4]
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r0, r6, #0x2
	mov r2, r0, lsl #0x3
	add r1, r2, #0x1f
	mov r0, r1, asr #0x4
	add r0, r1, r0, lsr #0x1b
	ldr r1, [r5, #0x8]
	mov r0, r0, asr #0x5
	cmp r0, r1
	movle r0, r5
	ble _02094CF8
	mov r0, r2, asr #0x4
	add r0, r2, r0, lsr #0x1b
	mov r1, r0, asr #0x5
	mov r0, r5
	add r1, r1, #0x1
	bl FUN_02094EBC
_02094CF8:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	sub r0, r6, #0x1
	mov r1, r0, lsr #0x2
	add r12, r1, #0x1
	cmp r6, #0x0
	str r12, [r5, #0x4]
	and r3, r0, #0x3
	sub r6, r6, #0x1
	beq _02094D64
	mov r1, #0x0
	mov r0, #0x3
_02094D34:
	ldrb r2, [r7], #0x1
	cmp r3, #0x0
	sub r3, r3, #0x1
	orr r4, r2, r4, lsl #0x8
	ldreq r2, [r5, #0x0]
	subeq r12, r12, #0x1
	streq r4, [r2, r12, lsl #0x2]
	moveq r4, r1
	moveq r3, r0
	cmp r6, #0x0
	sub r6, r6, #0x1
	bne _02094D34
_02094D64:
	mov r0, r5
	bl FUN_02095040
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02094D7C
FUN_02094D7C:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r2, [r4, #0x8]
	mov r5, r1
	cmp r2, #0x1
	bge _02094DA0
	mov r1, #0x2
	bl FUN_02094EBC
_02094DA0:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	mov r0, #0x0
	str r0, [r4, #0xc]
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	str r5, [r0, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	movne r0, #0x1
	strne r0, [r4, #0x4]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02094DEC
FUN_02094DEC: ; 0x02094DEC
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02094E10
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	mov r2, r2, lsl #0x2
	bl MI_CpuFill8
_02094E10:
	mov r0, #0x0
	str r0, [r4, #0x4]
	str r0, [r4, #0xc]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02094E24
FUN_02094E24:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	cmp r5, r4
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [r4, #0x4]
	ldr r2, [r5, #0x8]
	cmp r1, r2
	ble _02094E58
	bl FUN_02094EBC
_02094E58:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [r4, #0x4]
	ldr r0, [r4, #0x0]
	ldr r1, [r5, #0x0]
	mov r2, r2, lsl #0x2
	bl MI_CpuCopy8
	ldr r0, [r4, #0x4]
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _02094EA4
	ldr r1, [r5, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x0]
_02094EA4:
	ldr r1, [r4, #0xc]
	mov r0, r5
	str r1, [r5, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02094EBC
FUN_02094EBC:
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldr r0, [r5, #0x8]
	mov r4, r1
	cmp r4, r0
	ble _02094F30
	ldr r0, [r5, #0x10]
	ands r0, r0, #0x2
	movne r0, #0x0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	add r0, r4, #0x1
	mov r0, r0, lsl #0x2
	bl FUN_020910A4
	movs r6, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02094F28
	ldr r2, [r5, #0x4]
	mov r1, r6
	mov r2, r2, lsl #0x2
	bl MI_CpuCopy8
_02094F20: ; 0x02094F20
	ldr r0, [r5, #0x0]
	bl FUN_0209105C
_02094F28:
	str r6, [r5, #0x0]
	str r4, [r5, #0x8]
_02094F30:
	mov r0, r5
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02094F3C
FUN_02094F3C: ; 0x02094F3C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	add r4, r6, #0x4
	mov r5, #0x0
_02094F4C:
	mov r0, r4
	bl FUN_02095164
	add r5, r5, #0x1
	cmp r5, #0xc
	add r4, r4, #0x14
	blt _02094F4C
	ldr r0, [r6, #0x108]
	ands r0, r0, #0x1
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, r6
	bl FUN_0209105C
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02094F84
FUN_02094F84: ; 0x02094F84
	stmdb sp!, {r4,lr}
	mov r1, #0x0
	mov r2, #0x110
	mov r4, r0
	bl MI_CpuFill8
_02094F98: ; 0x02094F98
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r0, [r4, #0x108]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02094FAC
FUN_02094FAC: ; 0x02094FAC
	stmdb sp!, {r4,lr}
	mov r0, #0x110
	bl FUN_020910A4
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl FUN_02094F84
	mov r1, #0x1
	mov r0, r4
	str r1, [r4, #0x108]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02094FE0
FUN_02094FE0: ; 0x02094FE0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x14
	bl FUN_020910A4
_02094FF0: ; 0x02094FF0
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {lr}
	bxeq lr
	mov r1, #0x1
	str r1, [r0, #0x10]
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0xc]
	str r1, [r0, #0x8]
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209502C
FUN_0209502C:
	ldr ip, _0209503C ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x14
	bx r12
	.balign 4
_0209503C: .word MI_CpuFill8

	arm_func_start FUN_02095040
FUN_02095040:
	ldr r3, [r0, #0x4]
	cmp r3, #0x0
	bxle lr
	ldr r2, [r0, #0x0]
	sub r1, r3, #0x1
	cmp r3, #0x0
	add r3, r2, r1, lsl #0x2
	bxle lr
	add r2, r0, #0x4
_02095064:
	ldr r1, [r3], #-0x4
	cmp r1, #0x0
	bxne lr
	ldr r1, [r2, #0x0]
	sub r1, r1, #0x1
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	bgt _02095064
	bx lr

	arm_func_start FUN_0209508C
FUN_0209508C:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r2, [r5, #0x4]
	mov r4, r1
	cmp r2, r4
	addge sp, sp, #0x4
	ldmgeia sp!, {r4-r5,lr}
	bxge lr
	ldr r2, [r5, #0x8]
	cmp r4, r2
	ble _020950C0
	bl FUN_02094EBC
_020950C0:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [r5, #0x4]
	cmp r2, r4
	addge sp, sp, #0x4
	ldmgeia sp!, {r4-r5,lr}
	bxge lr
	mov r1, #0x0
_020950EC:
	ldr r0, [r5, #0x0]
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, r4
	blt _020950EC
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209510C
FUN_0209510C:
	stmdb sp!, {r4,lr}
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02095138
	ldr r1, [r4, #0x10]
	ands r1, r1, #0x2
	bne _02095138
	bl FUN_0209105C
_02095138:
	ldr r0, [r4, #0x10]
	orr r0, r0, #0x8000
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x10]
	ands r0, r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	bl FUN_0209105C
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02095164
FUN_02095164: ; 0x02095164
	stmdb sp!, {r4,lr}
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl FUN_02094DEC
	mov r0, r4
	bl FUN_0209510C
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02095188
FUN_02095188: ; 0x02095188
	stmdb sp!, {r4,lr}
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, [r0, #0x0]
	sub r4, r1, #0x1
	ldr r0, [r0, r4, lsl #0x2]
	bl FUN_020951BC
	add r0, r0, r4, lsl #0x5
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020951BC
FUN_020951BC: ; 0x020951BC
	mov r1, #0x10000
	rsb r1, r1, #0x0
	ands r1, r0, r1
	beq _020951DC
	ands r1, r0, #0xff000000
	movne r2, #0x18
	moveq r2, #0x10
	b _020951E8
_020951DC:
	ands r1, r0, #0xff00
	movne r2, #0x8
	moveq r2, #0x0
_020951E8:
	mov r1, r0, lsr r2
	ands r0, r1, #0xf0
	ldreq r0, _02095218 ; =0x020FF524
	ldreqsb r0, [r0, r1]
	addeq r0, r0, r2
	bxeq lr
	ldr r0, _02095218 ; =0x020FF524
	mov r1, r1, lsr #0x4
	ldrsb r0, [r0, r1]
	add r0, r0, r2
	add r0, r0, #0x4
	bx lr
	.balign 4
_02095218: .word 0x020FF524

	arm_func_start FUN_0209521C
FUN_0209521C: ; 0x0209521C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r3, #0x0
	strb r3, [r0, #0x0]
	cmp r2, #0x10
	strb r3, [r0, #0x1]
	movhi r2, #0x10
	add r0, r0, #0x4
_0209523C:
	strb r3, [r0, r3]
	add r3, r3, #0x1
	cmp r3, #0x100
	blt _0209523C
	mov r6, #0x0
	mov r7, r6
	mov r4, r6
	mov r3, r6
	and r12, r2, #0xff
_02095260:
	ldrb r5, [r0, r4]
	ldrb lr, [r1, r7]
	add r2, r7, #0x1
	and r7, r2, #0xff
	add r2, r5, lr
	add r2, r6, r2
	and r6, r2, #0xff
	ldrb r2, [r0, r6]
	add lr, r0, r4
	add r4, r4, #0x1
	strb r2, [lr, #0x0]
	cmp r7, r12
	moveq r7, r3
	cmp r4, #0x100
	strb r5, [r0, r6]
	blt _02095260
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_020952AC
FUN_020952AC: ; 0x020952AC
	stmdb sp!, {r4-r9,lr}
	ldrb r7, [r0, #0x0]
	ldrb r6, [r0, #0x1]
	add r0, r0, #0x4
	mov lr, #0x1000000
	add r7, lr, r7, lsl #0x18
	mov r6, r6, lsl #0x18
	ldrb r9, [r0, r7, lsr #0x18]
	subs r2, r2, #0x1
	bmi _0209530C
_020952D4:
	add r6, r6, r9, lsl #0x18
	subs r2, r2, #0x1
	ldrb r8, [r0, r6, lsr #0x18]
	ldrb r5, [r1], #0x1
	strb r8, [r0, r7, lsr #0x18]
	strb r9, [r0, r6, lsr #0x18]
	add r4, r9, r8
	and r4, r4, #0xff
	add r7, r7, lr
	ldrb r4, [r0, r4]
	ldrb r9, [r0, r7, lsr #0x18]
	eor r5, r5, r4
	strb r5, [r3], #0x1
	bge _020952D4
_0209530C:
	sub r7, r7, lr
	mov r7, r7, lsr #0x18
	mov r6, r6, lsr #0x18
	strb r7, [r0, #-0x4]
	strb r6, [r0, #-0x3]
	ldmia sp!, {r4-r9,pc}
_02095324: ; 0x02095324
	ldr r0, _0209532C ; =0x021C8C84
	bx lr
	.balign 4
_0209532C: .word 0x021C8C84

	arm_func_start FUN_02095330
FUN_02095330: ; 0x02095330
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldr r3, [r4, #0x8]
	ldr r2, [r4, #0xc]
	ldr r1, _020953E4 ; =0x021C8C84
	str r2, [sp, #0x4]
	str r3, [sp, #0x0]
	mov r2, #0x5
	bl MI_CpuCopy8
	ldr r1, [sp, #0x0]
	ldr r2, [r4, #0x4]
	ldr r0, [sp, #0x4]
	mov r2, r2, lsr #0x8
	mov r12, r1, lsr #0x5
	mov r3, r0, lsr #0x5
	orr r12, r12, r0, lsl #0x1b
	and lr, r2, #0x7
	and r0, r1, #0x1f
	orr lr, lr, r0, lsl #0x3
	ldr r2, _020953E4 ; =0x021C8C84
	ldr r1, _020953E8 ; =0x021C8C8A
	strb lr, [r2, #0x5]
	add r0, sp, #0x0
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r2, #0x4
	bl MI_CpuCopy8
	ldrh r0, [r4, #0x10]
	ldr r1, [sp, #0x4]
	ldr r3, _020953E4 ; =0x021C8C84
	and r1, r1, #0x3f
	and r0, r0, #0x3
	orr r0, r1, r0, lsl #0x6
	strb r0, [r3, #0xa]
	ldrh r2, [r4, #0x10]
	add r0, r4, #0x12
	ldr r1, _020953EC ; =0x021C8C90
	mov r4, r2, asr #0x2
	mov r2, #0x2
	strb r4, [r3, #0xb]
	bl MI_CpuCopy8
	ldr r0, _020953E4 ; =0x021C8C84
	add sp, sp, #0x8
	ldmia sp!, {r4,pc}
	.balign 4
_020953E4: .word 0x021C8C84
_020953E8: .word 0x021C8C8A
_020953EC: .word 0x021C8C90

	arm_func_start FUN_020953F0
FUN_020953F0: ; 0x020953F0
	ldr r3, _02095420 ; =0x021C8C78
	and r12, r1, #0xff
	ldr r0, _02095424 ; =0x021C8C7C
	mov r1, #0x1
	strh r12, [r3, #0x0]
	str r1, [r0, #0x0]
	cmp r2, #0x0
	movne r0, #0xff
	strneh r0, [r3, #0x0]
	ldr r0, _02095420 ; =0x021C8C78
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
_02095420: .word 0x021C8C78
_02095424: .word 0x021C8C7C

	arm_func_start FUN_02095428
FUN_02095428:
	stmdb sp!, {r4-r6,lr}
	mov r5, #0x4
	mov r4, #0x1
_02095434:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_02095440: ; 0x02095440
	cmp r0, #0x0
	beq _02095434
	ldr r1, _02095490 ; =FUN_020953F0
	mov r0, #0x4
	bl PXI_SetFifoRecvCallback
	mov r4, #0x40000
	mov r6, #0x7
	mov r5, #0x0
_02095460:
	mov r0, r6
	mov r1, r5
	mov r2, r5
	mov r3, r5
	bl FUN_020955F4
	cmp r0, #0x1
	beq _02095488
	mov r0, r4
	blx FUN_020005F2
	b _02095460
_02095488:
	mov r0, #0x1
	ldmia sp!, {r4-r6,pc}
	.balign 4
_02095490: .word FUN_020953F0

	arm_func_start FUN_02095494
FUN_02095494:
	stmdb sp!, {r4-r6,lr}
	mov r5, r2
	mov r4, r3
	mov r6, r0
	mov r0, r1
	mov r1, r5
	mov r2, r4
	bl FUN_0209555C
_020954B4: ; 0x020954B4
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020954C0: ; 0x020954C0
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl memcmp
_020954D0: ; 0x020954D0
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020954E0
FUN_020954E0: ; 0x020954E0
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, #0x4
	mov r4, #0x1
_020954F8:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_02095504: ; 0x02095504
	cmp r0, #0x0
	beq _020954F8
	ldr r1, _02095558 ; =FUN_020953F0
	mov r0, #0x4
	bl PXI_SetFifoRecvCallback
	mov r0, r6
	mov r1, r7
	bl DC_StoreRange
	mov r4, #0x40000
	mov r5, #0x2
_0209552C:
	mov r0, r5
	mov r1, r8
	mov r2, r7
	mov r3, r6
	bl FUN_020955F4
	cmp r0, #0x1
	ldmeqia sp!, {r4-r8,pc}
_02095548: ; 0x02095548
	mov r0, r4
	blx FUN_020005F2
	b _0209552C
_02095554: ; 0x02095554
	ldmia sp!, {r4-r8,pc}
	.balign 4
_02095558: .word FUN_020953F0

	arm_func_start FUN_0209555C
FUN_0209555C:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r4, r2
	mov r6, r0
	mov r0, r4
	mov r5, r1
	bl DC_InvalidateRange
	mov r8, #0x4
	mov r7, #0x1
_02095580:
	mov r0, r8
	mov r1, r7
	bl PXI_IsCallbackReady
_0209558C: ; 0x0209558C
	cmp r0, #0x0
	beq _02095580
	ldr r1, _020955F0 ; =FUN_020953F0
	mov r0, #0x4
	bl PXI_SetFifoRecvCallback
	mov r0, r5, lsl #0x10
	mov r8, r0, lsr #0x10
	mov r7, #0x40000
	mov r9, #0x1
_020955B0:
	mov r0, r9
	mov r1, r6
	mov r2, r8
	mov r3, r4
	bl FUN_020955F4
	cmp r0, #0x1
	beq _020955D8
	mov r0, r7
	blx FUN_020005F2
	b _020955B0
_020955D8:
	mov r0, r4
	mov r1, r5
	bl DC_InvalidateRange
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020955F0: .word FUN_020953F0

	arm_func_start FUN_020955F4
FUN_020955F4: ; 0x020955F4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc4
	ldr ip, _02095AAC ; =0x0000FFFF
	ldr sl, _02095AB0 ; =0x021C8CA0
	and r8, r2, r12
	and r7, r1, r12
	mov r5, r1, lsr #0x10
	mov r4, r3, lsr #0x10
	and r1, r3, r12
	orr r3, r8, #0x30000
	str r3, [sp, #0xc]
	ldr r3, _02095AB4 ; =0x01050000
	orr r2, r2, #0x20000
	orr r3, r1, r3
	str r3, [sp, #0x14]
	orr r1, r1, #0x1040000
	mov r9, r0
	and r0, r5, #0xff
	str r2, [sp, #0x1c]
	str r1, [sp, #0x24]
	ldr r1, _02095AB8 ; =0x02002200
	mov r8, #0x0
	orr r2, r4, #0x40000
	orr r1, r1, r10, lsr #0x18
	str r1, [sp, #0x28]
	and r1, r12, r10, lsr #0x8
	orr r1, r1, #0x10000
	ldr r3, _02095ABC ; =0x02002300
	str r2, [sp, #0x10]
	orr r2, r0, r3
	str r2, [sp, #0x8]
	orr r2, r4, #0x30000
	str r2, [sp, #0x20]
	ldr r2, _02095AC0 ; =0x02002500
	mov r6, r10, lsl #0x8
	str r1, [sp, #0x2c]
	and r1, r6, #0xff00
	orr r0, r0, r2
	ldr r3, _02095AC4 ; =0x01020000
	str r0, [sp, #0x18]
	orr r0, r1, r3
	str r0, [sp, #0x30]
	mov r0, #0x20000
	str r0, [sp, #0x40]
	mov r0, #0x5
	str r0, [sp, #0xac]
	mov r0, #0x3
	str r0, [sp, #0xb0]
	mov r0, #0x6
	str r0, [sp, #0xb8]
	mov r0, #0x4000
	orr r7, r7, #0x10000
	str r8, [sp, #0xb4]
	mov r4, #0x1
	str r8, [sp, #0xa8]
	mov r5, #0x4
	str r8, [sp, #0xa4]
	str r8, [sp, #0xa0]
	str r8, [sp, #0x90]
	str r8, [sp, #0x98]
	str r8, [sp, #0x9c]
	str r8, [sp, #0x94]
	str r8, [sp, #0x8c]
	str r8, [sp, #0x6c]
	str r8, [sp, #0x74]
	str r8, [sp, #0x7c]
	str r8, [sp, #0x84]
	str r8, [sp, #0x88]
	str r8, [sp, #0x80]
	str r8, [sp, #0x78]
	str r8, [sp, #0x70]
	str r8, [sp, #0x68]
	str r8, [sp, #0x64]
	str r8, [sp, #0x38]
	str r8, [sp, #0x44]
	str r8, [sp, #0x4c]
	str r8, [sp, #0x54]
	str r8, [sp, #0x5c]
	str r8, [sp, #0x60]
	str r8, [sp, #0x58]
	str r8, [sp, #0x50]
	str r8, [sp, #0x48]
	str r8, [sp, #0x3c]
	str r8, [sp, #0x34]
	mov r6, r8
	str r0, [sp, #0xbc]
_0209574C:
	cmp r8, #0x0
	bne _02095988
	ldr r0, _02095AC8 ; =0x021C8C7C
	cmp r9, #0x7
	str r6, [r0, #0x0]
	addls pc, pc, r9, lsl #0x2
	b _0209574C
_02095768:
	b _0209574C
_0209576C:
	b _02095788
_02095770:
	b _02095834
_02095774:
	b _02095854
_02095778:
	b _020958F0
_0209577C:
	b _020958F0
_02095780:
	b _02095948
_02095784:
	b _02095968
_02095788:
	ldr r1, [sp, #0x8]
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
_02095798: ; 0x02095798
	cmp r0, #0x0
	ldrlt r8, [sp, #0x34]
	blt _0209574C
	ldr r2, [sp, #0x38]
	mov r0, r5
	mov r1, r7
	bl PXI_SendWordByFifo
_020957B4: ; 0x020957B4
	cmp r0, #0x0
	ldrlt r8, [sp, #0x3c]
	blt _0209574C
	ldr r1, [sp, #0x40]
	ldr r2, [sp, #0x44]
	mov r0, r5
	bl PXI_SendWordByFifo
_020957D0: ; 0x020957D0
	cmp r0, #0x0
	ldrlt r8, [sp, #0x48]
	blt _0209574C
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x4c]
	mov r0, r5
	bl PXI_SendWordByFifo
_020957EC: ; 0x020957EC
	cmp r0, #0x0
	ldrlt r8, [sp, #0x50]
	blt _0209574C
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x54]
	mov r0, r5
	bl PXI_SendWordByFifo
_02095808: ; 0x02095808
	cmp r0, #0x0
	ldrlt r8, [sp, #0x58]
	blt _0209574C
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x5c]
	mov r0, r5
	bl PXI_SendWordByFifo
_02095824: ; 0x02095824
	cmp r0, #0x0
	ldrlt r8, [sp, #0x60]
	movge r8, r4
	b _0209574C
_02095834:
	ldr r1, _02095ACC ; =0x03002000
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
_02095844: ; 0x02095844
	cmp r0, #0x0
	movge r8, r4
	ldrlt r8, [sp, #0x64]
	b _0209574C
_02095854:
	ldr r1, [sp, #0x18]
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
_02095864: ; 0x02095864
	cmp r0, #0x0
	ldrlt r8, [sp, #0x68]
	blt _020958E0
	ldr r2, [sp, #0x6c]
	mov r0, r5
	mov r1, r7
	bl PXI_SendWordByFifo
_02095880: ; 0x02095880
	cmp r0, #0x0
	ldrlt r8, [sp, #0x70]
	blt _020958E0
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x74]
	mov r0, r5
	bl PXI_SendWordByFifo
_0209589C: ; 0x0209589C
	cmp r0, #0x0
	ldrlt r8, [sp, #0x78]
	blt _020958E0
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x7c]
	mov r0, r5
	bl PXI_SendWordByFifo
_020958B8: ; 0x020958B8
	cmp r0, #0x0
	ldrlt r8, [sp, #0x80]
	blt _020958E0
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x84]
	mov r0, r5
	bl PXI_SendWordByFifo
_020958D4: ; 0x020958D4
	cmp r0, #0x0
	ldrlt r8, [sp, #0x88]
	movge r8, r4
_020958E0:
	bl OS_GetTick
_020958E4: ; 0x020958E4
	str r0, [sp, #0x0]
	mov r11, r1
	b _0209574C
_020958F0:
	ldr r1, [sp, #0x28]
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
_02095900: ; 0x02095900
	cmp r0, #0x0
	ldrlt r8, [sp, #0x8c]
	blt _0209574C
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x90]
	mov r0, r5
	bl PXI_SendWordByFifo
_0209591C: ; 0x0209591C
	cmp r0, #0x0
	ldrlt r8, [sp, #0x94]
	blt _0209574C
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x98]
	mov r0, r5
	bl PXI_SendWordByFifo
_02095938: ; 0x02095938
	cmp r0, #0x0
	ldrlt r8, [sp, #0x9c]
	movge r8, r4
	b _0209574C
_02095948:
	ldr r1, _02095AD0 ; =0x03002D00
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
_02095958: ; 0x02095958
	cmp r0, #0x0
	movge r8, r4
	ldrlt r8, [sp, #0xa0]
	b _0209574C
_02095968:
	ldr r1, _02095AD4 ; =0x03002100
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
_02095978: ; 0x02095978
	cmp r0, #0x0
	movge r8, r4
	ldrlt r8, [sp, #0xa4]
	b _0209574C
_02095988:
	ldr r0, _02095AC8 ; =0x021C8C7C
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0209574C
	ldr r0, _02095AD8 ; =0x021C8C78
	ldr r8, [sp, #0xa8]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02095AA0
	cmp r9, #0x7
	addls pc, pc, r9, lsl #0x2
	b _0209574C
_020959B8: ; 0x020959B8
	b _0209574C
_020959BC: ; 0x020959BC
	b _020959D8
_020959C0: ; 0x020959C0
	b _020959E4
_020959C4: ; 0x020959C4
	b _020959EC
_020959C8: ; 0x020959C8
	b _020959F4
_020959CC: ; 0x020959CC
	b _020959F4
_020959D0: ; 0x020959D0
	b _02095A88
_020959D4: ; 0x020959D4
	b _02095A94
_020959D8:
	add sp, sp, #0xc4
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020959E4:
	mov r9, r5
	b _0209574C
_020959EC:
	ldr r9, [sp, #0xac]
	b _0209574C
_020959F4:
	mov r0, r10
	mov r1, r4
	bl DC_InvalidateRange
	cmp r9, #0x4
	bne _02095A24
	ldrb r0, [r10, #0x0]
	ands r0, r0, #0x2
	ldrne r9, [sp, #0xb0]
	bne _0209574C
	add sp, sp, #0xc4
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_02095A24:
	ldrb r1, [r10, #0x0]
	ands r0, r1, #0x1
	addeq sp, sp, #0xc4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r11,pc}
_02095A38: ; 0x02095A38
	ands r0, r1, #0x20
	bne _02095A74
	bl OS_GetTick
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0xb4]
	subs r2, r0, r2
	sbc r0, r1, r11
	mov r1, r0, lsl #0x6
	orr r1, r1, r2, lsr #0x1a
	mov r0, r2, lsl #0x6
	ldr r2, _02095ADC ; =0x000082EA
	bl _ll_udiv
_02095A68: ; 0x02095A68
	cmp r1, #0x0
	cmpeq r0, #0xfa0
	bls _02095A7C
_02095A74:
	ldr r9, [sp, #0xb8]
	b _0209574C
_02095A7C:
	ldr r0, [sp, #0xbc]
	blx FUN_020005F2
	b _0209574C
_02095A88:
	add sp, sp, #0xc4
	mov r0, r8
	ldmia sp!, {r4-r11,pc}
_02095A94:
	add sp, sp, #0xc4
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_02095AA0:
	mov r0, r8
	add sp, sp, #0xc4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_02095AAC: .word 0x0000FFFF
_02095AB0: .word 0x021C8CA0
_02095AB4: .word 0x01050000
_02095AB8: .word 0x02002200
_02095ABC: .word 0x02002300
_02095AC0: .word 0x02002500
_02095AC4: .word 0x01020000
_02095AC8: .word 0x021C8C7C
_02095ACC: .word 0x03002000
_02095AD0: .word 0x03002D00
_02095AD4: .word 0x03002100
_02095AD8: .word 0x021C8C78
_02095ADC: .word 0x000082EA

	arm_func_start FUN_02095AE0
FUN_02095AE0:
	ldrb r0, [r0, #0x0]
	cmp r0, #0x7f
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x1
	movcc r0, #0x0
	bxcc lr
	cmp r0, #0xdf
	movls r0, #0x1
	movhi r0, #0x0
	bx lr

	arm_func_start FUN_02095B0C
FUN_02095B0C:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	mov r4, r1
	bl FUN_02095AE0
_02095B20: ; 0x02095B20
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
_02095B30: ; 0x02095B30
	add r1, sp, #0x0
	mov r0, r5
	mov r2, #0x4
	bl MI_CpuCopy8
	add r1, sp, #0x4
	mov r0, r4
	mov r2, #0x4
	bl MI_CpuCopy8
	ldr r3, [sp, #0x4]
	ldr r2, [sp, #0x0]
	mvn r0, #0x1
	orr r1, r2, r3
	cmp r1, r0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
_02095B70: ; 0x02095B70
	mvn r0, r3
	ands r0, r2, r0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_02095B88
FUN_02095B88:
	mov r2, #0x0
_02095B8C:
	ldrb r1, [r0, r2]
	cmp r1, #0x0
	movne r0, #0x1
	bxne lr
	add r2, r2, #0x1
	cmp r2, #0x20
	blt _02095B8C
	mov r0, #0x0
	bx lr

	arm_func_start FUN_02095BB0
FUN_02095BB0: ; 0x02095BB0
	mvn r2, #0x0
	mov r12, #0x0
	eor r3, r2, r2, lsr r0
	mov r2, r12
_02095BC0:
	rsb r0, r2, #0x18
	mov r0, r3, lsr r0
	strb r0, [r1, r12]
	add r12, r12, #0x1
	cmp r12, #0x4
	add r2, r2, #0x8
	blt _02095BC0
	bx lr

	arm_func_start FUN_02095BE0
FUN_02095BE0: ; 0x02095BE0
	stmdb sp!, {r4,lr}
	mov lr, #0x0
	mov r4, lr
	mov r2, lr
_02095BF0:
	ldrb r3, [r0, lr]
	mov r12, r2
_02095BF8:
	mov r1, r3, asr r12
	ands r1, r1, #0x1
	add r12, r12, #0x1
	addne r4, r4, #0x1
	cmp r12, #0x8
	blt _02095BF8
	add lr, lr, #0x1
	cmp lr, #0x4
	blt _02095BF0
	and r0, r4, #0xff
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02095C24
FUN_02095C24: ; 0x02095C24
	ldr ip, _02095C34 ; =MI_CpuCopy8
	ldr r1, _02095C38 ; =0x021C8C84
	mov r2, #0xe
	bx r12
	.balign 4
_02095C34: .word MI_CpuCopy8
_02095C38: .word 0x021C8C84

	arm_func_start FUN_02095C3C
FUN_02095C3C:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r1, _02095CD8 ; =0x021C8C80
	mov r10, r0
	ldr r8, [r1, #0x0]
	mov r7, r10
	mov r9, #0x0
	add r4, r10, #0x400
	add r6, r10, #0x500
	mov r5, #0x100
	mov r11, #0xfe
_02095C68:
	mov r0, r6
	mov r1, r7
	mov r2, r11
	bl MATH_CalcCRC16
	add r1, r10, r9, lsl #0x8
	strh r0, [r1, #0xfe]
_02095C80:
	mov r0, r8
	mov r1, r5
	mov r2, r7
	bl FUN_020954E0
	mov r0, r7
	mov r1, r8
	mov r2, r5
	mov r3, r4
	bl FUN_02095494
_02095CA4: ; 0x02095CA4
	cmp r0, #0x0
	beq _02095C80
	add r9, r9, #0x1
	cmp r9, #0x4
	add r7, r7, #0x100
	add r8, r8, #0x100
	blt _02095C68
	bl FUN_02095428
_02095CC4: ; 0x02095CC4
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_02095CD8: .word 0x021C8C80

	arm_func_start FUN_02095CDC
FUN_02095CDC: ; 0x02095CDC
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r3, _02095D64 ; =0x021C8C80
	mov r4, r0
	ldr r6, [r3, #0x0]
	mov r9, r1
	mov r8, r2
	mov r7, #0x0
	mov r5, #0x100
_02095D00:
	ldr r0, [r9, r7, lsl #0x2]
	cmp r0, #0x0
	beq _02095D38
_02095D0C:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_020954E0
	mov r0, r4
	mov r1, r6
	mov r2, r5
	mov r3, r8
	bl FUN_02095494
_02095D30: ; 0x02095D30
	cmp r0, #0x0
	beq _02095D0C
_02095D38:
	add r7, r7, #0x1
	cmp r7, #0x4
	add r4, r4, #0x100
	add r6, r6, #0x100
	blt _02095D00
	bl FUN_02095428
_02095D50: ; 0x02095D50
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_02095D64: .word 0x021C8C80

	arm_func_start FUN_02095D68
FUN_02095D68:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _02095D98 ; =0x021C8C80
	mov r2, r0
	ldr r0, [r1, #0x0]
	mov r1, #0x400
	bl FUN_0209555C
_02095D84: ; 0x02095D84
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_02095D98: .word 0x021C8C80

	arm_func_start FUN_02095D9C
FUN_02095D9C:
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x20
	mov r1, r0
	mov r2, r4
	bl FUN_0209555C
_02095DB4: ; 0x02095DB4
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_02095DC0: ; 0x02095DC0
	ldrh r2, [r4, #0x0]
	ldr r1, _02095DDC ; =0x021C8C80
	mov r0, #0x1
	mov r2, r2, lsl #0x3
	sub r2, r2, #0x400
	str r2, [r1, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_02095DDC: .word 0x021C8C80

	arm_func_start FUN_02095DE0
FUN_02095DE0:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r2, _02095EBC ; =0x021C8C80
	mov r10, r1
	ldr r8, [r2, #0x0]
	bl FUN_02095330
	ldr r1, _02095EC0 ; =0x0000A001
	add r0, r10, #0x200
	bl MATHi_CRC16InitTableRev
	mov r9, #0x0
	add r4, r10, #0x100
	add r6, r10, #0xf0
	mov r7, #0x100
	mov r5, #0xe
	mov r11, #0xfe
_02095E1C:
	mov r0, r8
	mov r1, r7
	mov r2, r10
	bl FUN_0209555C
_02095E2C: ; 0x02095E2C
	cmp r0, #0x0
	bne _02095E44
	bl OS_Terminate
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_02095E44:
	ldr r0, _02095EC4 ; =0x021C8C84
	mov r1, r6
	mov r2, r5
	bl MI_CpuCopy8
	mov r1, r10
	mov r2, r11
	add r0, r10, #0x200
	bl MATH_CalcCRC16
	strh r0, [r10, #0xfe]
_02095E68:
	mov r0, r8
	mov r1, r7
	mov r2, r10
	bl FUN_020954E0
	mov r0, r10
	mov r1, r8
	mov r2, r7
	mov r3, r4
	bl FUN_02095494
_02095E8C: ; 0x02095E8C
	cmp r0, #0x0
	beq _02095E68
	add r9, r9, #0x1
	cmp r9, #0x2
	add r8, r8, #0x100
	blt _02095E1C
	bl FUN_02095428
_02095EA8: ; 0x02095EA8
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_02095EBC: .word 0x021C8C80
_02095EC0: .word 0x0000A001
_02095EC4: .word 0x021C8C84

	arm_func_start FUN_02095EC8
FUN_02095EC8:
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _02095F90 ; =0x021C8C84
	mov r1, r4
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r3, [r4, #0x0]
	mvn r0, #0x0
	ldr r2, [r4, #0x4]
	ldr r1, _02095F94 ; =0x000007FF
	and r0, r3, r0
	str r0, [r4, #0x0]
	and r1, r2, r1
	ldr r0, _02095F98 ; =0x021C8C89
	str r1, [r4, #0x4]
	add r1, r4, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	add r12, r4, #0x8
	ldr r1, [r4, #0x8]
	ldr r0, [r12, #0x4]
	mov r1, r1, lsr #0x3
	orr r1, r1, r0, lsl #0x1d
	str r1, [r4, #0x8]
	mov r0, r0, lsr #0x3
	str r0, [r12, #0x4]
	ldr r3, [r4, #0x8]
	mvn r0, #0x0
	ldr r2, [r12, #0x4]
	ldr r1, _02095F94 ; =0x000007FF
	and r0, r3, r0
	str r0, [r4, #0x8]
	and r1, r2, r1
	ldr r0, _02095F9C ; =0x021C8C8E
	str r1, [r12, #0x4]
	add r1, r4, #0x10
	mov r2, #0x2
	bl MI_CpuCopy8
	ldrh r1, [r4, #0x10]
	ldr r3, _02095FA0 ; =0x000003FF
	ldr r0, _02095FA4 ; =0x021C8C90
	mov r1, r1, asr #0x6
	strh r1, [r4, #0x10]
	ldrh r12, [r4, #0x10]
	add r1, r4, #0x12
	mov r2, #0x2
	and r3, r12, r3
	strh r3, [r4, #0x10]
	bl MI_CpuCopy8
	ldmia sp!, {r4,pc}
	.balign 4
_02095F90: .word 0x021C8C84
_02095F94: .word 0x000007FF
_02095F98: .word 0x021C8C89
_02095F9C: .word 0x021C8C8E
_02095FA0: .word 0x000003FF
_02095FA4: .word 0x021C8C90

	arm_func_start FUN_02095FA8
FUN_02095FA8: ; 0x02095FA8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _02095FD8 ; =0x021C8C80
	mov r2, r0
	ldr r0, [r1, #0x0]
	mov r1, #0x300
	bl FUN_0209555C
_02095FC4: ; 0x02095FC4
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_02095FD8: .word 0x021C8C80

	arm_func_start FUN_02095FDC
FUN_02095FDC: ; 0x02095FDC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	add r1, r5, r4, lsl #0x8
	mov r0, #0x0
	mov r2, #0x100
	bl MIi_CpuClear16
	add r0, r5, r4, lsl #0x8
	mov r1, #0xff
	strb r1, [r0, #0xe7]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_02096010
FUN_02096010: ; 0x02096010
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r7, r0
	mov r1, r7
	mov r0, #0x0
	mov r2, #0x400
	bl MIi_CpuClear16
	mov r2, #0x0
	mov r1, #0xff
_02096034:
	add r0, r7, r2, lsl #0x8
	add r2, r2, #0x1
	strb r1, [r0, #0xe7]
	cmp r2, #0x3
	blt _02096034
	add r0, sp, #0x0
	bl FUN_020967A4
_02096050: ; 0x02096050
	add r0, sp, #0x0
	bl FUN_02095330
	mov r6, r0
	mov r5, #0x0
	mov r4, #0xe
_02096064:
	mov r0, r6
	mov r2, r4
	add r1, r7, #0xf0
	bl MI_CpuCopy8
	add r5, r5, #0x1
	cmp r5, #0x2
	add r7, r7, #0x100
	blt _02096064
	mov r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_02096090
FUN_02096090:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldrb r0, [r4, #0xe7]
	cmp r0, #0xff
	addeq sp, sp, #0x8
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
_020960B0: ; 0x020960B0
	cmp r0, #0x2
	addhi sp, sp, #0x8
	movhi r0, #0x0
	ldmhiia sp!, {r4,pc}
_020960C0: ; 0x020960C0
	add r0, r4, #0x40
	bl FUN_02095B88
_020960C8: ; 0x020960C8
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_020960D8: ; 0x020960D8
	ldr r1, _0209618C ; =0x020FF574
	add r0, r4, #0xc0
	mov r2, #0x4
	bl memcmp
_020960E8: ; 0x020960E8
	cmp r0, #0x0
	beq _02096140
	add r0, r4, #0xc4
	bl FUN_02095AE0
_020960F8: ; 0x020960F8
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_02096108: ; 0x02096108
	ldrb r0, [r4, #0xd0]
	cmp r0, #0x20
	addhi sp, sp, #0x8
	movhi r0, #0x0
	ldmhiia sp!, {r4,pc}
_0209611C: ; 0x0209611C
	add r1, sp, #0x0
	bl FUN_02095BB0
	add r1, sp, #0x0
	add r0, r4, #0xc0
	bl FUN_02095B0C
_02096130: ; 0x02096130
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_02096140:
	ldr r1, _0209618C ; =0x020FF574
	add r0, r4, #0xc8
	mov r2, #0x4
	bl memcmp
_02096150: ; 0x02096150
	cmp r0, #0x0
	beq _02096180
	add r0, r4, #0xc8
	bl FUN_02095AE0
_02096160: ; 0x02096160
	cmp r0, #0x0
	bne _02096180
	add r0, r4, #0xcc
	bl FUN_02095AE0
_02096170: ; 0x02096170
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_02096180:
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4,pc}
	.balign 4
_0209618C: .word 0x020FF574

	arm_func_start FUN_02096190
FUN_02096190: ; 0x02096190
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r0
	mov r1, #0x0
	mov r2, #0x700
	bl MI_CpuFill8
	mov r0, r10
	bl FUN_02095D9C
_020961B0: ; 0x020961B0
	cmp r0, #0x0
	addeq sp, sp, #0x14
	ldreq r0, _020964B4 ; =0xFFFFD8EF
	ldmeqia sp!, {r4-r11,pc}
_020961C0: ; 0x020961C0
	ldr r1, _020964B8 ; =0x0000A001
	add r0, r10, #0x500
	bl MATHi_CRC16InitTableRev
	mov r0, r10
	bl FUN_02095D68
_020961D4: ; 0x020961D4
	cmp r0, #0x0
	addeq sp, sp, #0x14
	ldreq r0, _020964B4 ; =0xFFFFD8EF
	ldmeqia sp!, {r4-r11,pc}
_020961E4: ; 0x020961E4
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x10
	bl MI_CpuFill8
	mov r8, r10
	mov r7, r10
	mov r9, #0x0
	add r11, sp, #0x0
	add r6, r10, #0x500
	mov r4, #0x1
	mov r5, #0xfe
_02096210:
	mov r0, r6
	mov r1, r8
	mov r2, r5
	bl MATH_CalcCRC16
	add r1, r10, r9, lsl #0x8
	ldrh r1, [r1, #0xfe]
	cmp r0, r1
	bne _02096240
	mov r0, r7
	bl FUN_02096090
_02096238: ; 0x02096238
	cmp r0, #0x0
	strne r4, [r11, r9, lsl #0x2]
_02096240:
	add r9, r9, #0x1
	cmp r9, #0x3
	add r8, r8, #0x100
	add r7, r7, #0x100
	blt _02096210
	add r0, r10, #0x500
	add r1, r10, #0x300
	mov r2, #0xfe
	bl MATH_CalcCRC16
	add r1, r10, #0x300
	ldrh r1, [r1, #0xfe]
	cmp r0, r1
	moveq r0, #0x1
	ldr r1, [sp, #0x0]
	streq r0, [sp, #0xc]
	cmp r1, #0x0
	beq _020962BC
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020962BC
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _020962BC
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	beq _020962BC
	add r0, r10, #0xf0
	bl FUN_02095C24
	add sp, sp, #0x14
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020962BC:
	cmp r1, #0x0
	bne _0209630C
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _0209630C
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bne _0209630C
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _0209630C
	mov r0, r10
	bl FUN_02096010
	mov r0, r10
	bl FUN_02095C3C
_020962F8: ; 0x020962F8
	cmp r0, #0x0
	movne r0, #0x0
	add sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmia sp!, {r4-r11,pc}
_0209630C:
	cmp r1, #0x0
	beq _02096320
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _0209635C
_02096320:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _02096338
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _0209635C
_02096338:
	mov r0, r10
	bl FUN_02096010
	mov r0, r10
	bl FUN_02095C3C
_02096348: ; 0x02096348
	cmp r0, #0x0
	movne r0, #0x0
	add sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmia sp!, {r4-r11,pc}
_0209635C:
	cmp r1, #0x0
	bne _02096394
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _02096394
	mov r0, r10
	bl FUN_02096010
	mov r0, r10
	bl FUN_02095C3C
_02096380: ; 0x02096380
	cmp r0, #0x0
	ldrne r0, _020964C0 ; =0xFFFFD8ED
	add sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmia sp!, {r4-r11,pc}
_02096394:
	cmp r1, #0x0
	bne _020963C4
	mov r0, r10
	mov r1, #0x0
	bl FUN_02095FDC
	add r0, r10, #0x1f0
	add r1, r10, #0xf0
	mov r2, #0xe
	bl MI_CpuCopy8
	ldrb r0, [r10, #0x1ef]
	strb r0, [r10, #0xef]
	b _020963F4
_020963C4:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _020963F4
	mov r0, r10
	mov r1, #0x1
	bl FUN_02095FDC
	add r0, r10, #0xf0
	add r1, r10, #0x1f0
	mov r2, #0xe
	bl MI_CpuCopy8
	ldrb r0, [r10, #0xef]
	strb r0, [r10, #0x1ef]
_020963F4:
	add r0, r10, #0xf0
	bl FUN_02095C24
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bne _02096414
	mov r0, r10
	mov r1, #0x2
	bl FUN_02095FDC
_02096414:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _02096430
	add r1, r10, #0x300
	mov r0, #0x0
	mov r2, #0x100
	bl MIi_CpuClear16
_02096430:
	mov r4, #0x0
	mov r1, r4
	add r0, sp, #0x0
	add r5, r10, #0xef
	mov r6, #0x1
_02096444:
	ldr r2, [r0, r1, lsl #0x2]
	cmp r2, #0x0
	bne _0209647C
	ldrb r2, [r10, #0xef]
	mov r7, r6, lsl r1
	ands r2, r2, r7
	beq _0209647C
	ldrb r3, [r5, #0x0]
	mvn r2, r7
	mov r4, r6
	and r2, r3, r2
	strb r2, [r5, #0x0]
	ldrb r2, [r10, #0xef]
	strb r2, [r10, #0x1ef]
_0209647C:
	add r1, r1, #0x1
	cmp r1, #0x3
	blt _02096444
	mov r0, r10
	bl FUN_02095C3C
_02096490: ; 0x02096490
	cmp r0, #0x0
	addeq sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmeqia sp!, {r4-r11,pc}
_020964A0: ; 0x020964A0
	cmp r4, #0x0
	ldrne r0, _020964C4 ; =0xFFFFD8EE
	moveq r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020964B4: .word 0xFFFFD8EF
_020964B8: .word 0x0000A001
_020964BC: .word 0xFFFFD8F0
_020964C0: .word 0xFFFFD8ED
_020964C4: .word 0xFFFFD8EE

	arm_func_start FUN_020964C8
FUN_020964C8:
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	add r0, sp, #0x0
	bl FUN_02095EC8
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0xc]
	mov r0, #0x0
	cmp r1, r0
	cmpeq r2, r0
	bne _0209650C
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	cmp r1, r0
	cmpeq r2, r0
	addeq sp, sp, #0x14
	moveq r0, #0x1
	ldmeqia sp!, {pc}
_0209650C:
	mov r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {pc}

	arm_func_start FUN_02096518
FUN_02096518: ; 0x02096518
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, sp, #0x0
	bl FUN_02095EC8
_0209652C: ; 0x0209652C
	add r0, sp, #0x0
	ldmia r0, {r2-r3}
	stmia r4, {r2-r3}
	add r1, sp, #0x8
	add r0, r4, #0x8
	ldmia r1, {r2-r3}
	stmia r0, {r2-r3}
	ldr r2, [sp, #0x0]
	ldr r1, [sp, #0x4]
	mov r0, #0x0
	cmp r1, r0
	cmpeq r2, r0
	streq r0, [r4, #0x10]
	movne r0, #0x1
	strne r0, [r4, #0x10]
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02096570
FUN_02096570: ; 0x02096570
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x28
	add r2, sp, #0x0
	mov r1, #0x0
	strb r1, [r2, #0x0]
	strb r1, [r2, #0x1]
	strb r1, [r2, #0x2]
	strb r1, [r2, #0x3]
	strb r1, [r2, #0x4]
	mov r5, r0
	strb r1, [r2, #0x5]
	bl FUN_02095EC8
	bl RTC_Init
	add r0, sp, #0x8
	bl RTC_GetDate
_020965AC: ; 0x020965AC
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
_020965BC: ; 0x020965BC
	add r0, sp, #0x18
	bl RTC_GetTime
_020965C4: ; 0x020965C4
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
_020965D4: ; 0x020965D4
	add r0, sp, #0x8
	add r1, sp, #0x18
	bl RTC_ConvertDateTimeToSecond
	mov r4, r0
	mov r0, #0x0
	subs r2, r4, r0
	sbcs r2, r1, r0
	addlt sp, sp, #0x28
	ldmltia sp!, {r4-r10,pc}
_020965F8: ; 0x020965F8
	bl OS_IsTickAvailable
_020965FC: ; 0x020965FC
	cmp r0, #0x0
	beq _0209660C
	ldr r0, _02096700 ; =OS_GetTick
	adds r4, r4, r0
_0209660C:
	add r0, sp, #0x0
	bl OS_GetMacAddress
	ldrb r1, [sp, #0x0]
	ldr r6, _02096704 ; =0x5D588B65
	ldr r7, _02096708 ; =0x00269EC3
	ldrb r0, [sp, #0x1]
	mla r9, r4, r6, r7
	mov r1, r1, lsl #0x10
	orr r1, r1, r0, lsl #0x8
	ldrb r2, [sp, #0x2]
	ldr r0, _0209670C ; =0x000009BF
	ldrb r8, [sp, #0x3]
	orr r1, r2, r1
	cmp r1, r0
	movne r1, #0x1
	mov r2, r9, lsr #0x10
	mov r0, #0x3e8
	mul r3, r2, r0
	mov r2, r3, lsr #0x10
	mov r3, r8, lsl #0x10
	ldrb r4, [sp, #0x4]
	ldrb r0, [sp, #0x5]
	mov r8, #0x0
	orr r10, r3, r4, lsl #0x8
	strh r2, [r5, #0x10]
	str r8, [r5, #0x8]
	str r8, [r5, #0xc]
	moveq r1, #0x0
	ldr r2, [r5, #0xc]
	ldr r3, [r5, #0x8]
	cmp r2, r8
	cmpeq r3, r8
	and r4, r1, #0xff
	orr r10, r0, r10
	bne _020966F4
_02096698:
	mla r9, r6, r9, r7
	b _020966A4
_020966A0:
	mla r9, r6, r9, r7
_020966A4:
	cmp r9, #0x0
	beq _020966A0
	ldrh r1, [r5, #0x12]
	mov r0, r9, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r1, r0
	beq _020966A0
	strh r0, [r5, #0x12]
	ldrh r0, [r5, #0x12]
	mov r1, r10
	mov r2, r4
	mov r3, r8
	bl FUN_02096988
	str r0, [r5, #0x8]
	str r1, [r5, #0xc]
	ldr r0, [r5, #0xc]
	ldr r1, [r5, #0x8]
	cmp r0, r8
	cmpeq r1, r8
	beq _02096698
_020966F4:
	mov r0, #0x1
	add sp, sp, #0x28
	ldmia sp!, {r4-r10,pc}
	.balign 4
_02096700: .word OS_GetTick
_02096704: .word 0x5D588B65
_02096708: .word 0x00269EC3
_0209670C: .word 0x000009BF

	arm_func_start FUN_02096710
FUN_02096710: ; 0x02096710
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	mov r5, r0
	add r0, sp, #0x0
	mov r4, r1
	bl FUN_02095EC8
	add r12, r5, #0x8
	ldmia r12, {r2-r3}
	stmia r5, {r2-r3}
	add r1, sp, #0x8
	ldmia r1, {r2-r3}
	mov r0, r5
	mov r1, r4
	stmia r12, {r2-r3}
	bl FUN_02095DE0
_0209674C: ; 0x0209674C
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_02096760
FUN_02096760: ; 0x02096760
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, sp, #0x0
	bl FUN_020967A4
_02096774: ; 0x02096774
	cmp r0, #0x0
	addeq sp, sp, #0x18
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_02096784: ; 0x02096784
	add r0, sp, #0x0
	mov r1, r4
	bl FUN_02095DE0
_02096790: ; 0x02096790
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020967A4
FUN_020967A4:
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x28
	mov r8, r0
	bl FUN_02095EC8
	bl RTC_Init
	add r0, sp, #0x8
	bl RTC_GetDate
_020967C0: ; 0x020967C0
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
_020967D0: ; 0x020967D0
	add r0, sp, #0x18
	bl RTC_GetTime
_020967D8: ; 0x020967D8
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
_020967E8: ; 0x020967E8
	add r0, sp, #0x8
	add r1, sp, #0x18
	bl RTC_ConvertDateTimeToSecond
	mov r4, r0
	mov r0, #0x0
	subs r2, r4, r0
	sbcs r2, r1, r0
	addlt sp, sp, #0x28
	ldmltia sp!, {r4-r10,pc}
_0209680C: ; 0x0209680C
	bl OS_IsTickAvailable
_02096810: ; 0x02096810
	cmp r0, #0x0
	beq _02096820
	ldr r0, _02096978 ; =OS_GetTick
	adds r4, r4, r0
_02096820:
	add r0, sp, #0x0
	bl OS_GetMacAddress
	ldrb r1, [sp, #0x0]
	ldr sb, _0209697C ; =0x5D588B65
	ldr sl, _02096980 ; =0x00269EC3
	ldrb r0, [sp, #0x1]
	mla r5, r4, r9, r10
	mov r1, r1, lsl #0x10
	orr r1, r1, r0, lsl #0x8
	ldrb r2, [sp, #0x2]
	ldr r0, _02096984 ; =0x000009BF
	ldrb r6, [sp, #0x3]
	orr r1, r2, r1
	cmp r1, r0
	movne r1, #0x1
	moveq r1, #0x0
	mov r2, r5, lsr #0x10
	mov r0, #0x3e8
	mul r3, r2, r0
	mov r2, r3, lsr #0x10
	ldrb r0, [sp, #0x5]
	ldrb r4, [sp, #0x4]
	mov r3, r6, lsl #0x10
	and r7, r1, #0xff
	orr r3, r3, r4, lsl #0x8
	strh r2, [r8, #0x10]
	mov r4, #0x0
	str r4, [r8, #0x0]
	str r4, [r8, #0x4]
	ldrh r2, [r8, #0x12]
	orr r6, r0, r3
	cmp r2, #0x0
	bne _02096910
	str r4, [r8, #0x8]
	str r4, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, r4
	bne _0209696C
_020968C0:
	mul r0, r5, r9
	adds r5, r0, r10
	bne _020968D8
_020968CC:
	mul r0, r5, r9
	adds r5, r0, r10
	beq _020968CC
_020968D8:
	strh r5, [r8, #0x12]
	ldrh r0, [r8, #0x12]
	mov r1, r6
	mov r2, r7
	mov r3, r4
	bl FUN_02096988
	str r0, [r8, #0x8]
	str r1, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, #0x0
	beq _020968C0
	b _0209696C
_02096910:
	str r4, [r8, #0x8]
	str r4, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, r4
	bne _0209696C
	add r5, r8, #0x12
_02096930:
	ldrh r0, [r5, #0x0]
	mov r1, r6
	mov r2, r7
	add r0, r0, #0x1
	strh r0, [r5, #0x0]
	ldrh r0, [r8, #0x12]
	mov r3, r4
	bl FUN_02096988
	str r0, [r8, #0x8]
	str r1, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, r4
	beq _02096930
_0209696C:
	mov r0, #0x1
	add sp, sp, #0x28
	ldmia sp!, {r4-r10,pc}
	.balign 4
_02096978: .word OS_GetTick
_0209697C: .word 0x5D588B65
_02096980: .word 0x00269EC3
_02096984: .word 0x000009BF

	arm_func_start FUN_02096988
FUN_02096988: ; 0x02096988
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov lr, #0x0
	and r12, lr, #0x0
	mvn r5, #0xff000000
	ldr r4, _02096B08 ; =0x0000FFFF
	and r2, r2, #0x1
	mov r6, r12, lsl #0x2
	and r3, r3, #0x3
	and r5, r1, r5
	orr r1, r3, r2, lsl #0x2
	orr r6, r6, r2, lsr #0x1e
	mov r7, r12, lsl #0x3
	and r2, r0, r4
	orr r0, r1, r5, lsl #0x3
	orr r1, r0, r2, lsl #0x1b
	mov r3, r12, lsl #0x1b
	orr r3, r3, r2, lsr #0x5
	orr r7, r7, r5, lsr #0x1d
	orr r0, r12, r6
	orr r0, r7, r0
	orr r0, r3, r0
	add r2, sp, #0x0
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
_020969EC:
	ldrb r0, [r2, #0x0]
	add lr, lr, #0x1
	cmp lr, #0x6
	eor r0, r0, #0xd6
	strb r0, [r2], #0x1
	blt _020969EC
	ldr r2, _02096B0C ; =0x020FF580
	add r5, sp, #0x0
	mov r4, #0x0
_02096A10:
	ldrb r3, [r5, #0x0]
	add r4, r4, #0x1
	cmp r4, #0x5
	mov r0, r3, asr #0x4
	and r1, r0, #0xf
	and r0, r3, #0xf
	ldrb r1, [r2, r1]
	ldrb r0, [r2, r0]
	orr r0, r0, r1, lsl #0x4
	strb r0, [r5], #0x1
	blt _02096A10
	add r0, sp, #0x0
	add r1, sp, #0x8
	mov r2, #0x8
	bl MI_CpuCopy8
	ldr r4, _02096B10 ; =0x020FF578
	add r5, sp, #0x8
	mov r3, #0x0
	add r1, sp, #0x0
_02096A5C:
	ldrb r2, [r5, #0x0]
	ldrb r0, [r4, #0x0]
	add r3, r3, #0x1
	cmp r3, #0x5
	strb r2, [r1, r0]
	add r5, r5, #0x1
	add r4, r4, #0x1
	blt _02096A5C
	ldrb r2, [sp, #0x5]
	mov r0, #0x0
	ldr r3, [sp, #0x0]
	and r2, r2, #0x7
	strb r0, [sp, #0x7]
	strb r0, [sp, #0x6]
	strb r2, [sp, #0x5]
	ldr r2, [sp, #0x4]
	mov r4, r3, lsl #0x1
	mov r2, r2, lsl #0x1
	orr r2, r2, r3, lsr #0x1f
	str r2, [sp, #0x4]
	ldrb r2, [sp, #0x5]
	str r4, [sp, #0x0]
	ldrb r3, [sp, #0x0]
	mov r2, r2, asr #0x3
	and r2, r2, #0x1
	orr r2, r3, r2
	strb r2, [sp, #0x0]
_02096AC8:
	ldrb r2, [r1, #0x0]
	add r0, r0, #0x1
	cmp r0, #0x6
	eor r2, r2, #0x67
	strb r2, [r1], #0x1
	blt _02096AC8
	ldrb r0, [sp, #0x5]
	mov r1, #0x0
	strb r1, [sp, #0x7]
	and r0, r0, #0x7
	strb r1, [sp, #0x6]
	strb r0, [sp, #0x5]
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}
	.balign 4
_02096B08: .word 0x0000FFFF
_02096B0C: .word 0x020FF580
_02096B10: .word 0x020FF578

	arm_func_start FUN_02096B14
FUN_02096B14: ; 0x02096B14
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r0, _02096B74 ; =0x02000B8C
	mov r4, #0x0
	bl OSi_ReferSymbol
	mov r0, r6
	bl FUN_02096190
	mov r5, r0
	bl FUN_020964C8
_02096B38: ; 0x02096B38
	cmp r0, #0x0
	beq _02096B4C
	mov r0, r6
	bl FUN_02096760
	mov r4, #0x1
_02096B4C:
	cmp r5, #0x0
	bge _02096B64
	cmp r4, #0x0
	movne r0, #0x2
	moveq r0, #0x3
	ldmia sp!, {r4-r6,pc}
_02096B64:
	cmp r4, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r4-r6,pc}
	.balign 4
_02096B74: .word 0x02000B8C

	arm_func_start FUN_02096B78
FUN_02096B78: ; 0x02096B78
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r7, r0
	bl FUN_020974C8
	mov r5, r0
	mov r0, r4
	bl FUN_020974C8
_02096B98: ; 0x02096B98
	cmp r5, r0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r7,pc}
_02096BA8: ; 0x02096BA8
	cmp r5, #0x3
	bne _02096BD8
	mov r0, r7
	bl FUN_02097544
	mov r5, r0
	mov r0, r4
	bl FUN_02097544
_02096BC4: ; 0x02096BC4
	cmp r5, r0
	moveq r0, #0x1
	add sp, sp, #0x4
	movne r0, #0x0
	ldmia sp!, {r4-r7,pc}
_02096BD8:
	cmp r5, #0x1
	bne _02096C34
	mov r0, r7
	bl FUN_02097568
	mov r5, r0
	mov r6, r1
	mov r0, r4
	bl FUN_02097568
	cmp r6, r1
	cmpeq r5, r0
	bne _02096C28
	mov r0, r7
	bl FUN_02097560
	mov r5, r0
	mov r0, r4
	bl FUN_02097560
_02096C18: ; 0x02096C18
	cmp r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r7,pc}
_02096C28:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_02096C34:
	cmp r5, #0x2
	bne _02096C6C
	mov r0, r7
	bl FUN_0209754C
	mov r5, r0
	mov r6, r1
	mov r0, r4
	bl FUN_0209754C
	cmp r6, r1
	cmpeq r5, r0
	moveq r0, #0x1
	add sp, sp, #0x4
	movne r0, #0x0
	ldmia sp!, {r4-r7,pc}
_02096C6C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
_02096C78: ; 0x02096C78
	ldr ip, _02096C8C ; =FUN_02097218
	mov r3, r0
	mov r0, r1
	ldr r1, [r3, #0x24]
	bx r12
	.balign 4
_02096C8C: .word FUN_02097218

	arm_func_start FUN_02096C90
FUN_02096C90: ; 0x02096C90
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	mov r1, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	mov r0, r5
	mov r1, r4
	bl FUN_020974F4
	mov r0, r5
	mov r1, #0x3
	bl FUN_02097440
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_02096CCC
FUN_02096CCC: ; 0x02096CCC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	mov r0, r4
	mov r1, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	mov r0, r5
	bl FUN_0209702C
_02096CF4: ; 0x02096CF4
	cmp r0, #0x0
	addeq r0, r5, #0x4
	ldmeqia r0, {r0-r2}
	addeq sp, sp, #0x4
	stmeqia r4, {r0-r2}
	ldmeqia sp!, {r4-r5,pc}
_02096D0C: ; 0x02096D0C
	ldr r1, [r5, #0x1c]
	mov r0, r4
	bl FUN_020974F4
	mov r0, r4
	mov r1, #0x3
	bl FUN_02097440
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_02096D2C
FUN_02096D2C: ; 0x02096D2C
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r4, r2
	mov r6, r0
	mov r1, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_020974FC
	mov r0, r6
	mov r1, #0x2
	bl FUN_02097440
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_02096D68
FUN_02096D68: ; 0x02096D68
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r0
	ldr r0, [r3, #0x1c]
	mov r2, #0x0
	mov r1, r2
	cmp r0, #0x0
	beq _02096D94
	ldr r1, [r3, #0x24]
	bl FUN_020973D0
	mov r2, r0
_02096D94:
	mov r0, r2
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_02096DA0
FUN_02096DA0: ; 0x02096DA0
	stmdb sp!, {r4-r6,lr}
	mov r4, r1
	mov r6, r0
	mov r0, r4
	bl FUN_020974C8
	cmp r0, #0x1
	beq _02096E14
	cmp r0, #0x2
	beq _02096DD0
	cmp r0, #0x3
	beq _02096E08
	b _02096E1C
_02096DD0:
	mov r0, r4
	bl FUN_0209754C
	ldr r2, [r6, #0x24]
	mov r4, r0
	mov r5, r1
	bl FUN_02097344
_02096DE8: ; 0x02096DE8
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_02096DF4: ; 0x02096DF4
	ldr r2, [r6, #0x24]
	mov r0, r4
	mov r1, r5
	bl FUN_02097324
	ldmia sp!, {r4-r6,pc}
_02096E08:
	mov r0, r4
	bl FUN_02097544
	ldmia sp!, {r4-r6,pc}
_02096E14:
	mvn r0, #0x0
	ldmia sp!, {r4-r6,pc}
_02096E1C:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_02096E24
FUN_02096E24: ; 0x02096E24
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020974C8
	cmp r0, #0x2
	movne r0, #0x0
	movne r1, r0
	ldmneia sp!, {r4,pc}
_02096E40: ; 0x02096E40
	mov r0, r4
	bl FUN_0209754C
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02096E4C
FUN_02096E4C: ; 0x02096E4C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x400
	mov r4, r0
	ldr r1, [r4, #0x20]
	add r0, sp, #0x0
	bic r2, r1, #0x1
	ldr r1, _02096E8C ; =0xEDB88320
	str r2, [r4, #0x20]
	bl MATHi_CRC32InitTableRev
_02096E70: ; 0x02096E70
	add r0, sp, #0x0
	mov r1, r4
	mov r2, #0x3c
	bl MATH_CalcCRC32
	str r0, [r4, #0x3c]
	add sp, sp, #0x400
	ldmia sp!, {r4,pc}
	.balign 4
_02096E8C: .word 0xEDB88320

	arm_func_start thunk_FUN_02096e4c
thunk_FUN_02096e4c: ; 0x02096E90
	ldr ip, _02096E98 ; =FUN_02096E4C
	bx r12
	.balign 4
_02096E98: .word FUN_02096E4C

	arm_func_start FUN_02096E9C
FUN_02096E9C: ; 0x02096E9C
	ldr r0, [r0, #0x20]
	and r0, r0, #0x1
	cmp r0, #0x1
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

	arm_func_start FUN_02096EB4
FUN_02096EB4: ; 0x02096EB4
	ldr ip, _02096EBC ; =FUN_02096E9C
	bx r12
	.balign 4
_02096EBC: .word FUN_02096E9C

	arm_func_start FUN_02096EC0
FUN_02096EC0: ; 0x02096EC0
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x400
	mov r4, r0
	add r3, r4, #0x10
	mov r12, r2
	ldmia r1, {r0-r2}
	stmia r3, {r0-r2}
	ldr r1, _02096F14 ; =0xEDB88320
	add r0, sp, #0x0
	str r12, [r4, #0x1c]
	bl MATHi_CRC32InitTableRev
_02096EEC: ; 0x02096EEC
	add r0, sp, #0x0
	mov r1, r4
	mov r2, #0x3c
	bl MATH_CalcCRC32
	str r0, [r4, #0x3c]
	ldr r0, [r4, #0x20]
	orr r0, r0, #0x1
	str r0, [r4, #0x20]
	add sp, sp, #0x400
	ldmia sp!, {r4,pc}
	.balign 4
_02096F14: .word 0xEDB88320

	arm_func_start FUN_02096F18
FUN_02096F18: ; 0x02096F18
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, r4, #0x10
	bl FUN_020974C8
_02096F2C: ; 0x02096F2C
	cmp r0, #0x0
	addeq sp, sp, #0x18
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
_02096F3C: ; 0x02096F3C
	add r0, sp, #0x0
	bl FUN_02096518
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	addeq sp, sp, #0x18
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_02096F58: ; 0x02096F58
	add r0, r4, #0x10
	bl FUN_02097568
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x0]
	cmp r2, r1
	cmpeq r3, r0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02096F80
FUN_02096F80: ; 0x02096F80
	stmdb sp!, {r4,lr}
	mov r4, r0
	add r0, r4, #0x10
	bl FUN_0209703C
_02096F90: ; 0x02096F90
	cmp r0, #0x0
	beq _02096FA8
	ldr r0, [r4, #0x1c]
	cmp r0, #0x0
	movgt r0, #0x1
	ldmgtia sp!, {r4,pc}
_02096FA8:
	mov r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02096FB0
FUN_02096FB0: ; 0x02096FB0
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x400
	ldr r1, _02096FF0 ; =0xEDB88320
	mov r4, r0
	add r0, sp, #0x0
	bl MATHi_CRC32InitTableRev
_02096FC8: ; 0x02096FC8
	add r0, sp, #0x0
	mov r1, r4
	mov r2, #0x3c
	bl MATH_CalcCRC32
	ldr r1, [r4, #0x3c]
	cmp r0, r1
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x400
	ldmia sp!, {r4,pc}
	.balign 4
_02096FF0: .word 0xEDB88320

	arm_func_start thunk_FUN_02097190
thunk_FUN_02097190: ; 0x02096FF4
	ldr ip, _02096FFC ; =FUN_02097190
	bx r12
	.balign 4
_02096FFC: .word FUN_02097190

	arm_func_start FUN_02097000
FUN_02097000: ; 0x02097000
	ldr ip, _02097008 ; =FUN_0209700C
	bx r12
	.balign 4
_02097008: .word FUN_0209700C

	arm_func_start FUN_0209700C
FUN_0209700C: ; 0x0209700C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020974C8
_02097018: ; 0x02097018
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_0209702C
FUN_0209702C:
	ldr ip, _02097038 ; =FUN_0209703C
	add r0, r0, #0x10
	bx r12
	.balign 4
_02097038: .word FUN_0209703C

	arm_func_start FUN_0209703C
FUN_0209703C:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020974C8
	cmp r0, #0x1
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_0209705C
FUN_0209705C: ; 0x0209705C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, sp, #0x0
	bl FUN_02096518
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	beq _020970A4
	mov r0, r4
	bl FUN_02097568
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x0]
	cmp r2, r1
	cmpeq r3, r0
	moveq r0, #0x1
	add sp, sp, #0x18
	movne r0, #0x0
	ldmia sp!, {r4,pc}
_020970A4:
	mov r0, r4
	bl FUN_02097568
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	cmp r2, r1
	cmpeq r3, r0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020970CC
FUN_020970CC: ; 0x020970CC
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x38
	mov r6, r0
	add r0, sp, #0x14
	bl OS_GetLowEntropyData
	mov r3, #0x1
	add r2, sp, #0x14
_020970E8:
	add r0, r2, r3, lsl #0x2
	ldr r1, [r2, r3, lsl #0x2]
	ldr r0, [r0, #-0x4]
	eor r0, r1, r0
	str r0, [r2, r3, lsl #0x2]
	add r3, r3, #0x1
	cmp r3, #0x8
	blo _020970E8
	add r0, sp, #0x0
	ldr r5, [sp, #0x30]
	mov r4, #0x0
	bl FUN_02096518
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	beq _02097138
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	mov r0, r6
	bl FUN_02097510
	b _02097148
_02097138:
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0xc]
	mov r0, r6
	bl FUN_02097510
_02097148:
	ldr r0, _02097184 ; =0x6C078965
	ldr r1, _02097188 ; =0x5D588B65
	umull r3, r2, r5, r0
	mla r2, r5, r1, r2
	ldr r1, _0209718C ; =0x00269EC3
	mla r2, r4, r0, r2
	adds r0, r3, r1
	mov r0, r6
	adc r1, r2, #0x0
	bl FUN_02097508
	mov r0, r6
	mov r1, #0x1
	bl FUN_02097440
	add sp, sp, #0x38
	ldmia sp!, {r4-r6,pc}
	.balign 4
_02097184: .word 0x6C078965
_02097188: .word 0x5D588B65
_0209718C: .word 0x00269EC3

	arm_func_start FUN_02097190
FUN_02097190: ; 0x02097190
	stmdb sp!, {r4-r5,lr}
	ldr ip, _02097210 ; =0x00000404
	sub sp, sp, r12
	mov r4, r1
	mov r1, #0x0
	mov r2, #0x40
	mov r5, r0
	bl MI_CpuFill8
	mov r0, #0x40
	str r0, [r5, #0x0]
	mov r0, #0x0
	str r0, [r5, #0x1c]
	add r0, r5, #0x4
	str r4, [r5, #0x24]
	bl FUN_020970CC
	add r0, r5, #0x10
	mov r1, #0x0
	bl FUN_02097440
	ldr r1, _02097214 ; =0xEDB88320
	add r0, sp, #0x0
	bl MATHi_CRC32InitTableRev
_020971E4: ; 0x020971E4
	add r0, sp, #0x0
	mov r1, r5
	mov r2, #0x3c
	bl MATH_CalcCRC32
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x20]
	orr r0, r0, #0x1
	str r0, [r5, #0x20]
	ldr ip, _02097210 ; =0x00000404
	add sp, sp, r12
	ldmia sp!, {r4-r5,pc}
	.balign 4
_02097210: .word 0x00000404
_02097214: .word 0xEDB88320

	arm_func_start FUN_02097218
FUN_02097218: ; 0x02097218
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x40
	mov r6, r0
	mov r4, r1
	mov r5, r2
	bl FUN_02097568
	add r3, sp, #0x14
	mov r2, #0x2b
	bl FUN_020972A8
	mov r0, r6
	bl FUN_02097560
	mov r1, #0x0
	mov r2, #0x20
	add r3, sp, #0x29
	bl FUN_020972A8
	mov r1, r4, lsr #0x18
	and r1, r1, #0xff
	str r1, [sp, #0x0]
	mov r1, r4, lsr #0x10
	and r1, r1, #0xff
	str r1, [sp, #0x4]
	mov r1, r4, lsr #0x8
	and r1, r1, #0xff
	str r1, [sp, #0x8]
	and r1, r4, #0xff
	str r1, [sp, #0xc]
	add r2, sp, #0x29
	str r2, [sp, #0x10]
	ldr r2, _020972A4 ; =0x0210618C
	mov r0, r5
	mov r1, #0x15
	add r3, sp, #0x14
	bl OS_SNPrintf
	add sp, sp, #0x40
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020972A4: .word 0x0210618C

	arm_func_start FUN_020972A8
FUN_020972A8: ; 0x020972A8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr lr, _0209731C ; =0x66666667
	add r4, r2, #0x4
	smull r12, r2, lr, r4
	mov r2, r2, asr #0x1
	mov r12, r4, lsr #0x1f
	add r2, r12, r2
	cmp r2, #0x0
	ldr r6, _02097320 ; =0x0210619C
	mov r7, #0x0
	ble _0209730C
	add r4, r3, r2
	sub r4, r4, #0x1
	mov r12, #0x1f
_020972E4:
	and r5, r0, r12
	ldrsb r5, [r6, r5]
	mov r0, r0, lsr #0x5
	mov lr, r1, lsr #0x5
	strb r5, [r4, -r7]
	add r7, r7, #0x1
	orr r0, r0, r1, lsl #0x1b
	mov r1, lr
	cmp r7, r2
	blt _020972E4
_0209730C:
	mov r0, #0x0
	strb r0, [r3, r2]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_0209731C: .word 0x66666667
_02097320: .word 0x0210619C

	arm_func_start FUN_02097324
FUN_02097324: ; 0x02097324
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_02097344
_02097330: ; 0x02097330
	cmp r0, #0x0
	mvnne r0, #0x0
	andne r0, r4, r0
	moveq r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02097344
FUN_02097344:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x108
	mov r4, r1
	and r3, r4, #0x0
	mov r1, #0x0
	and r12, r0, #0x80000000
	cmp r3, r1
	cmpeq r12, r1
	addne sp, sp, #0x108
	movne r0, r1
	ldmneia sp!, {r4,pc}
_02097370: ; 0x02097370
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	mov r1, #0x7
	str r2, [sp, #0x4]
	bl MATHi_CRC8InitTable
	add r0, sp, #0x8
	add r1, sp, #0x0
	mov r2, #0x8
	bl MATH_CalcCRC8
	and r2, r0, #0x7f
	mov r1, r2, asr #0x1f
	mov r0, #0x0
	cmp r1, r0
	cmpeq r2, r4
	moveq r0, #0x1
	add sp, sp, #0x108
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020973B4
FUN_020973B4: ; 0x020973B4
	ldr ip, _020973CC ; =FUN_02097344
	mov r3, r0
	mov r0, r1
	mov r1, r2
	ldr r2, [r3, #0x24]
	bx r12
	.balign 4
_020973CC: .word FUN_02097344

	arm_func_start FUN_020973D0
FUN_020973D0: ; 0x020973D0
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x108
	mov r4, r0
	str r1, [sp, #0x4]
	add r0, sp, #0x8
	mov r1, #0x7
	str r4, [sp, #0x0]
	bl MATHi_CRC8InitTable
	add r0, sp, #0x8
	add r1, sp, #0x0
	mov r2, #0x8
	bl MATH_CalcCRC8
	and r0, r0, #0x7f
	orr r1, r0, #0x0
	orr r0, r4, #0x0
	add sp, sp, #0x108
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02097414
FUN_02097414: ; 0x02097414
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020974C8
	cmp r0, #0x3
	ldmneia sp!, {r4,pc}
_02097428: ; 0x02097428
	mov r0, r4
	bl FUN_020974E0
	orr r1, r0, #0x4
	mov r0, r4
	bl FUN_0209746C
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02097440
FUN_02097440: ; 0x02097440
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_020974E0
	bic r1, r0, #0x3
	mov r0, r5
	orr r1, r1, r4
	bl FUN_0209746C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_0209746C
FUN_0209746C: ; 0x0209746C
	ldr ip, _0209747C ; =FUN_02097588
	ldr r3, _02097480 ; =0x001FFFFF
	mov r2, #0xb
	bx r12
	.balign 4
_0209747C: .word FUN_02097588
_02097480: .word 0x001FFFFF

	arm_func_start FUN_02097484
FUN_02097484: ; 0x02097484
	ldr ip, _0209748C ; =FUN_020974C8
	bx r12
	.balign 4
_0209748C: .word FUN_020974C8

	arm_func_start FUN_02097490
FUN_02097490: ; 0x02097490
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020974C8
	cmp r0, #0x3
	bne _020974C0
	mov r0, r4
	bl FUN_020974E0
	and r0, r0, #0x4
	cmp r0, #0x4
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4,pc}
_020974C0:
	mov r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020974C8
FUN_020974C8: ; 0x020974C8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020974E0
	and r0, r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020974E0
FUN_020974E0: ; 0x020974E0
	ldr r1, [r0, #0x0]
	ldr r0, _020974F0 ; =0x001FFFFF
	and r0, r0, r1, lsr #0xb
	bx lr
	.balign 4
_020974F0: .word 0x001FFFFF

	arm_func_start FUN_020974F4
FUN_020974F4: ; 0x020974F4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start FUN_020974FC
FUN_020974FC: ; 0x020974FC
	str r1, [r0, #0x4]
	str r2, [r0, #0x8]
	bx lr

	arm_func_start FUN_02097508
FUN_02097508: ; 0x02097508
	str r1, [r0, #0x8]
	bx lr

	arm_func_start FUN_02097510
FUN_02097510: ; 0x02097510
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r12, #0x0
	mov r4, r1
	mov r1, r2
	ldr r3, _02097540 ; =0x000007FF
	mov r2, r12
	mov r5, r0
	bl FUN_02097588
	str r4, [r5, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_02097540: .word 0x000007FF

	arm_func_start FUN_02097544
FUN_02097544:
	ldr r0, [r0, #0x4]
	bx lr

	arm_func_start FUN_0209754C
FUN_0209754C: ; 0x0209754C
	ldr r1, [r0, #0x8]
	ldr r0, [r0, #0x4]
	orr r1, r1, #0x0
	orr r0, r0, #0x0
	bx lr

	arm_func_start FUN_02097560
FUN_02097560:
	ldr r0, [r0, #0x8]
	bx lr

	arm_func_start FUN_02097568
FUN_02097568: ; 0x02097568
	ldr r2, [r0, #0x0]
	ldr r1, _02097584 ; =0x000007FF
	ldr r0, [r0, #0x4]
	and r1, r2, r1
	orr r1, r1, #0x0
	orr r0, r0, #0x0
	bx lr
	.balign 4
_02097584: .word 0x000007FF

	arm_func_start FUN_02097588
FUN_02097588: ; 0x02097588
	mvn r12, r3
	ands r12, r1, r12
	movne r0, #0x0
	bxne lr
	mvn r3, r3, lsl r2
	ldr r12, [r0, #0x0]
	and r3, r12, r3
	orr r1, r3, r1, lsl r2
	str r1, [r0, #0x0]
	mov r0, #0x1
	bx lr

	arm_func_start FUN_020975B4
FUN_020975B4: ; 0x020975B4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020A8850
_020975C0: ; 0x020975C0
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020975D8
FUN_020975D8: ; 0x020975D8
	ldr r0, _020975EC ; =0x021C8CCC
	ldr r1, [r0, #0x0]
	orr r1, r1, #0x2
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020975EC: .word 0x021C8CCC

	arm_func_start FUN_020975F0
FUN_020975F0: ; 0x020975F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _02097654 ; =0x021C8CC0
	ldr r0, _02097658 ; =0x021C8CCC
	ldr lr, [r1, #0x0]
	ldr r3, [r0, #0x0]
	ldr r12, [lr, #0x4]
	ldr r2, _0209765C ; =0x021C8F04
	ldr r1, _02097660 ; =0x021C8ED0
	str r12, [r2, #0x0]
	ldr r12, [lr, #0x8]
	ldr r2, _02097664 ; =0x021C8EE0
	str r12, [r1, #0x0]
	ldr r12, [lr, #0xc]
	ldr r1, _02097668 ; =0x021C8F1C
	str r12, [r2, #0x0]
	ldr r12, [lr, #0x10]
	orr r2, r3, #0x2
	str r12, [r1, #0x0]
	ldr r3, [lr, #0x14]
	str r3, [r1, #0x4]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097654: .word 0x021C8CC0
_02097658: .word 0x021C8CCC
_0209765C: .word 0x021C8F04
_02097660: .word 0x021C8ED0
_02097664: .word 0x021C8EE0
_02097668: .word 0x021C8F1C

	arm_func_start FUN_0209766C
FUN_0209766C: ; 0x0209766C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020977C0 ; =0x021C8CC0
	ldr r5, _020977C4 ; =0x021C8CD4
	ldr r4, [r0, #0x0]
	mov r0, r5
	mov r1, #0x0
	mov r2, #0x30
	bl MI_CpuFill8
	ldr r0, _020977C8 ; =0x021C8CC4
	ldr r2, [r4, #0x18]
	mov r1, r5
	str r2, [r1, #0x4]
	ldr r12, [r4, #0x1c]
	mov r2, #0x0
	ldr r3, _020977CC ; =FUN_020975B4
	ldr r0, [r0, #0x0]
	str r12, [r1, #0x8]
	str r3, [r1, #0x10]
	str r2, [r1, #0x14]
	str r2, [r1, #0x18]
	str r0, [r1, #0x2c]
	ldr r0, [r4, #0x24]
	cmp r0, #0x0
	strne r0, [r5, #0x20]
	moveq r0, #0x4000
	streq r0, [r5, #0x20]
	ldr r0, [r4, #0x28]
	cmp r0, #0x0
	strne r0, [r5, #0x1c]
	bne _02097700
	ldr r1, _020977C0 ; =0x021C8CC0
	ldr r0, [r5, #0x20]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	blx r1
	str r0, [r5, #0x1c]
_02097700:
	ldr r0, [r4, #0x30]
	ldr r12, [r4, #0x34]
	cmp r0, #0x0
	moveq r0, #0x240
	cmp r12, #0x0
	sub r2, r0, #0x28
	moveq r12, #0x10c0
	add r0, r12, r12, lsr #0x1f
	str r2, [r5, #0x24]
	ldr r1, _020977D0 ; =0x021061DC
	mov r3, r0, asr #0x1
	ldr r0, _020977D4 ; =0x021C8F04
	mov r2, #0x0
	strh r12, [r1, #0x2]
	strh r3, [r1, #0x4]
	str r2, [r0, #0x0]
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02097774
	ldr r0, _020977D8 ; =0x021C8CCC
	mov r1, #0x1
	str r1, [r0, #0x0]
	ldr r1, _020977DC ; =FUN_020975D8
	str r2, [r5, #0x0]
	ldr r0, _020977E0 ; =0x021C8CC8
	str r1, [r5, #0xc]
	ldr r0, [r0, #0x0]
	str r0, [r5, #0x28]
	b _0209778C
_02097774:
	ldr r0, _020977D8 ; =0x021C8CCC
	mov r1, #0x1
	str r2, [r0, #0x0]
	ldr r0, _020977E4 ; =FUN_020975F0
	str r1, [r5, #0x0]
	str r0, [r5, #0xc]
_0209778C:
	ldr r0, [r4, #0x2c]
	cmp r0, #0x0
	moveq r0, #0xb
	bl FUN_0209FC88
	ldr r0, _020977E8 ; =FUN_0209F65C
	bl FUN_020A87BC
	ldr r0, _020977EC ; =FUN_020996C0
	bl FUN_0209FD24
	mov r0, r5
	bl FUN_0209FD94
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020977C0: .word 0x021C8CC0
_020977C4: .word 0x021C8CD4
_020977C8: .word 0x021C8CC4
_020977CC: .word FUN_020975B4
_020977D0: .word 0x021061DC
_020977D4: .word 0x021C8F04
_020977D8: .word 0x021C8CCC
_020977DC: .word FUN_020975D8
_020977E0: .word 0x021C8CC8
_020977E4: .word FUN_020975F0
_020977E8: .word FUN_0209F65C
_020977EC: .word FUN_020996C0

	arm_func_start FUN_020977F0
FUN_020977F0: ; 0x020977F0
	stmdb sp!, {r4,lr}
	ldr r0, _02097828 ; =0x021C8CC0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x20]
	bl FUN_02097B78
	movs r4, r0
	bmi _0209781C
	ldr r0, _0209782C ; =0x021061F4
	bl FUN_02097F70
	ldr r1, _02097830 ; =0x021C8CD0
	str r0, [r1, #0x0]
_0209781C:
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097828: .word 0x021C8CC0
_0209782C: .word 0x021061F4
_02097830: .word 0x021C8CD0

	arm_func_start FUN_02097834
FUN_02097834: ; 0x02097834
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _02097870 ; =0x02000BC4
	bl OSi_ReferSymbol
	ldr r0, _02097874 ; =0x021C8CC0
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	str r4, [r0, #0x0]
	bl FUN_0209766C
	bl FUN_020977F0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097870: .word 0x02000BC4
_02097874: .word 0x021C8CC0

	arm_func_start FUN_02097878
FUN_02097878: ; 0x02097878
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	add r6, sp, #0x0
	mov r4, #0x0
	mov r5, #0x1
_02097890:
	mov r0, r9
	mov r1, r6
	mov r2, r5
	bl OS_ReadMessage
_020978A0: ; 0x020978A0
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r1, [r0, #0x0]
	blx r1
	mov r7, r0
	bl OS_DisableInterrupts
	mov r8, r0
	bl OS_DisableScheduler
	mov r0, r9
	mov r1, r4
	mov r2, r4
	bl OS_ReceiveMessage
_020978DC: ; 0x020978DC
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	strne r7, [r0, #0x6c]
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _02097908
	mov r1, r7
	mov r2, r4
	bl OS_SendMessage
_02097908:
	ldr r0, [sp, #0x0]
	bl FUN_02097A64
	bl OS_EnableScheduler
	mov r0, r8
	bl OS_RestoreInterrupts
	b _02097890
_02097920: ; 0x02097920
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_0209792C
FUN_0209792C: ; 0x0209792C
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl FUN_02097A50
	mov r1, r4
	bl FUN_02097968
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02097948
FUN_02097948:
	ldr ip, _02097954 ; =FUN_02097968
	ldr r0, [r0, #0x68]
	bx r12
	.balign 4
_02097954: .word FUN_02097968

	arm_func_start FUN_02097958
FUN_02097958: ; 0x02097958
	ldr ip, _02097964 ; =FUN_02097968
	ldr r0, [r0, #0x64]
	bx r12
	.balign 4
_02097964: .word FUN_02097968

	arm_func_start FUN_02097968
FUN_02097968: ; 0x02097968
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x2c
	mov r4, r1
	ldrsb r2, [r4, #0xd]
	mov r5, r0
	cmp r2, #0x1
	bne _020979BC
	add r0, sp, #0x8
	add r1, sp, #0x4
	mov r2, #0x1
	bl OS_InitMessageQueue
	add r2, sp, #0x8
	mov r0, r5
	mov r1, r4
	str r2, [r4, #0x8]
	bl FUN_020979F8
	add r0, sp, #0x8
	add r1, sp, #0x0
	mov r2, #0x1
	bl OS_ReceiveMessage
	b _020979CC
_020979BC:
	mov r2, #0x0
	str r2, [r4, #0x8]
	bl FUN_020979F8
_020979C8: ; 0x020979C8
	str r0, [sp, #0x0]
_020979CC:
	ldr r0, [sp, #0x0]
	add sp, sp, #0x2c
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020979DC
FUN_020979DC:
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl FUN_02097A50
	mov r1, r4
	bl FUN_020979F8
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020979F8
FUN_020979F8:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r1
	beq _02097A14
	ldrsb r1, [r5, #0xd]
	ands r1, r1, #0x1
	beq _02097A1C
_02097A14:
	mov r2, #0x1
	b _02097A20
_02097A1C:
	mov r2, #0x0
_02097A20:
	mov r1, r5
	bl OS_SendMessage
	movs r4, r0
	bne _02097A38
	mov r0, r5
	bl FUN_02097A64
_02097A38:
	cmp r4, #0x0
	movne r0, #0x0
	mvneq r0, #0x29
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02097A50
FUN_02097A50: ; 0x02097A50
	ldr r1, [r0, #0x64]
	cmp r1, #0x0
	ldreq r1, [r0, #0x68]
	mov r0, r1
	bx lr

	arm_func_start FUN_02097A64
FUN_02097A64:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	movs r1, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r0, _02097A94 ; =0x021C8D08
	mov r2, #0x0
	bl OS_SendMessage
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097A94: .word 0x021C8D08

	arm_func_start FUN_02097A98
FUN_02097A98: ; 0x02097A98
	stmdb sp!, {r4-r6,lr}
	mov r4, r2
	mov r6, r0
	mov r0, r4
	mov r5, r1
	bl FUN_02097AE0
_02097AB0: ; 0x02097AB0
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	str r6, [r0, #0x0]
	str r5, [r0, #0x4]
	mov r1, #0x0
	str r1, [r0, #0x8]
	ldrsb r1, [r5, #0x73]
	strb r1, [r0, #0xc]
	strb r4, [r0, #0xd]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02097AE0
FUN_02097AE0:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r0
	ldr r0, _02097B10 ; =0x021C8D08
	add r1, sp, #0x0
	bl OS_ReceiveMessage
_02097AF8: ; 0x02097AF8
	cmp r0, #0x0
	ldrne r0, [sp, #0x0]
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097B10: .word 0x021C8D08

	arm_func_start FUN_02097B14
FUN_02097B14: ; 0x02097B14
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _02097B6C ; =0x021C8D08
	ldr r1, [r0, #0x1c]
	ldr r0, [r0, #0x14]
	cmp r1, r0
	addlt sp, sp, #0x4
	mvnlt r0, #0x0
	ldmltia sp!, {lr}
	bxlt lr
	ldr r0, _02097B70 ; =0x021C8CC0
	ldr r1, _02097B74 ; =0x021C8D04
	ldr r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	ldr r1, [r2, #0x1c]
	blx r1
	ldr r1, _02097B74 ; =0x021C8D04
	mov r0, #0x0
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097B6C: .word 0x021C8D08
_02097B70: .word 0x021C8CC0
_02097B74: .word 0x021C8D04

	arm_func_start FUN_02097B78
FUN_02097B78: ; 0x02097B78
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	mov r0, #0x2c
	mul r1, r4, r0
	ldr r0, _02097C08 ; =0x021C8CC0
	mov r2, r4, lsl #0x2
	add r2, r2, #0x3
	ldr r0, [r0, #0x0]
	add r1, r1, #0x3
	bic r5, r2, #0x3
	bic r2, r1, #0x3
	ldr r1, [r0, #0x18]
	add r0, r2, r5
	blx r1
	movs r6, r0
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, _02097C0C ; =0x021C8D08
	mov r1, r6
	mov r2, r4
	bl OS_InitMessageQueue
_02097BD0: ; 0x02097BD0
	cmp r4, #0x0
	add r5, r6, r5
	ble _02097BF4
_02097BDC:
	mov r0, r5
	bl FUN_02097A64
	sub r4, r4, #0x1
	cmp r4, #0x0
	add r5, r5, #0x2c
	bgt _02097BDC
_02097BF4:
	ldr r1, _02097C10 ; =0x021C8D04
	mov r0, #0x0
	str r6, [r1, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_02097C08: .word 0x021C8CC0
_02097C0C: .word 0x021C8D08
_02097C10: .word 0x021C8D04

	arm_func_start FUN_02097C14
FUN_02097C14: ; 0x02097C14
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r5, r2
	mov r7, r0
	mov r0, r5
	mov r6, r1
	bl FUN_02097DC4
	add r4, r7, r0
	ldrb r2, [r5, #0x3]
	mov r0, r6
	mov r1, r7
	bl OS_InitMessageQueue
	add r0, r6, #0xe0
	bl OS_InitMutex
	ldrh r2, [r5, #0x0]
	add r0, r6, #0x20
	ldr r1, _02097C88 ; =FUN_02097878
	str r2, [sp, #0x0]
	ldrb r12, [r5, #0x2]
	mov r2, r6
	mov r3, r4
	str r12, [sp, #0x4]
	bl OS_CreateThread
	add r0, r6, #0x20
	bl OS_WakeupThreadDirect
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02097C88: .word FUN_02097878

	arm_func_start FUN_02097C8C
FUN_02097C8C: ; 0x02097C8C
	stmdb sp!, {r4,lr}
	mov r4, r0
	cmp r2, #0x0
	moveq r0, #0x0
	str r0, [r1, #0x4]
	mov r0, r2
	str r2, [r1, #0x0]
	bl FUN_02099F6C
_02097CAC: ; 0x02097CAC
	add r0, r4, r0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02097CB8
FUN_02097CB8: ; 0x02097CB8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldrsb r1, [r6, #0x0]
	mov r7, r0
	add r4, r7, #0x80
	strb r1, [r7, #0x73]
	ldrsb r0, [r6, #0x1]
	strb r0, [r7, #0x72]
	ldrh r0, [r6, #0x2]
	cmp r0, #0x0
	beq _02097D40
	str r4, [r7, #0x64]
	ldrh r2, [r6, #0x4]
	mov r1, r4
	add r0, r4, #0x114
	strh r2, [r4, #0xfc]
	add r2, r6, #0x10
	mov r5, r4
	bl FUN_02097C14
	ldrh r2, [r6, #0x2]
	add r1, r7, #0x3c
	bl FUN_02097C8C
	ldrh r2, [r6, #0x8]
	add r1, r7, #0x50
	bl FUN_02097C8C
	ldrh r3, [r6, #0xe]
	add r1, r5, #0x100
	mov r2, #0x0
	strh r3, [r1, #0xa]
	str r2, [r5, #0x110]
	ldr r1, [r5, #0x110]
	mov r4, r0
	str r1, [r5, #0x10c]
_02097D40:
	ldrh r0, [r6, #0x6]
	cmp r0, #0x0
	ldreq r0, _02097DC0 ; =0x021C8CD0
	ldreq r0, [r0, #0x0]
	ldreq r0, [r0, #0x68]
	streq r0, [r7, #0x68]
	beq _02097DB0
	str r4, [r7, #0x68]
	mov r1, r4
	str r7, [r4, #0x10c]
	add r0, r4, #0x110
	add r2, r6, #0x14
	mov r5, r4
	bl FUN_02097C14
	ldrh r2, [r6, #0x6]
	add r1, r7, #0x48
	bl FUN_02097C8C
	ldrh r2, [r6, #0xa]
	add r1, r7, #0x58
	bl FUN_02097C8C
	ldrh r2, [r6, #0xc]
	add r1, r4, #0xf8
	bl FUN_02097C8C
	mov r1, #0x0
	str r1, [r5, #0x108]
	ldr r1, [r5, #0x108]
	mov r4, r0
	str r1, [r5, #0x104]
_02097DB0:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02097DC0: .word 0x021C8CD0

	arm_func_start FUN_02097DC4
FUN_02097DC4: ; 0x02097DC4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrb r0, [r5, #0x3]
	mov r0, r0, lsl #0x2
	bl FUN_02099F6C
	mov r4, r0
	ldrh r0, [r5, #0x0]
	bl FUN_02099F6C
_02097DE8: ; 0x02097DE8
	add r0, r4, r0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02097DF8
FUN_02097DF8: ; 0x02097DF8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrh r0, [r5, #0x2]
	mov r4, #0x80
	cmp r0, #0x0
	beq _02097E38
	add r4, r4, #0x114
	bl FUN_02099F6C
	add r4, r4, r0
	ldrh r0, [r5, #0x8]
	bl FUN_02099F6C
	add r4, r4, r0
	add r0, r5, #0x10
	bl FUN_02097DC4
	add r4, r4, r0
_02097E38:
	ldrh r0, [r5, #0x6]
	cmp r0, #0x0
	beq _02097E74
	add r4, r4, #0x110
	bl FUN_02099F6C
	add r4, r4, r0
	ldrh r0, [r5, #0xa]
	bl FUN_02099F6C
	add r4, r4, r0
	ldrh r0, [r5, #0xc]
	bl FUN_02099F6C
	add r4, r4, r0
	add r0, r5, #0x14
	bl FUN_02097DC4
	add r4, r4, r0
_02097E74:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02097E84
FUN_02097E84: ; 0x02097E84
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl FUN_02097DF8
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _02097EF4 ; =0x021C8CC0
	mov r5, r0
	ldr r1, [r1, #0x0]
	mov r0, r4
	ldr r1, [r1, #0x18]
	blx r1
	movs r6, r0
	beq _02097EDC
	mov r2, r4
	mov r1, #0x0
	bl MI_CpuFill8
	mov r0, r6
	mov r1, r7
	bl FUN_02097CB8
	mov r0, r6
	bl FUN_0209A094
_02097EDC:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02097EF4: .word 0x021C8CC0

	arm_func_start FUN_02097EF8
FUN_02097EF8: ; 0x02097EF8
	stmdb sp!, {r4,lr}
	ldr r4, [r0, #0x4]
	mov r0, r4
	bl FUN_0209CC28
	ldrsb r0, [r4, #0x73]
	ldr r1, [r4, #0x68]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _02097F58
_02097F1C:
	b _02097F30
_02097F20:
	b _02097F40
_02097F24:
	b _02097F54
_02097F28:
	b _02097F58
_02097F2C:
	b _02097F30
_02097F30:
	add r0, r1, #0x20
	bl FUN_0209CB0C
	bl FUN_0209CB44
	b _02097F58
_02097F40:
	bl FUN_0209CB44
	bl FUN_0209CBE8
	ldr r0, _02097F6C ; =FUN_02098550
	bl FUN_0209CAA8
_02097F50: ; 0x02097F50
	b _02097F58
_02097F54:
	bl FUN_0209CBE8
_02097F58:
	mov r0, #0x1
	strh r0, [r4, #0x70]
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097F6C: .word FUN_02098550

	arm_func_start FUN_02097F70
FUN_02097F70: ; 0x02097F70
	stmdb sp!, {r4,lr}
	bl FUN_02097E84
	movs r4, r0
	mvneq r0, #0x30
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, _02097FB0 ; =FUN_02097EF8
	mov r1, r4
	mov r2, #0x1
	bl FUN_02097A98
	mov r1, r0
	mov r0, r4
	bl FUN_0209792C
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097FB0: .word FUN_02097EF8

	arm_func_start FUN_02097FB4
FUN_02097FB4: ; 0x02097FB4
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r6, r0
	ldr r4, [r6, #0x4]
	ldr r5, [r4, #0x64]
	add r0, r5, #0xe0
	bl OS_LockMutex
	mov r1, #0x0
	ldrh r0, [r6, #0x10]
	mov r2, r1
	bl FUN_0209CB78
	bl FUN_0209CA54
	mov r2, #0x0
	add r0, sp, #0x0
	add r1, sp, #0x4
	str r2, [r5, #0xf8]
	bl FUN_0209C8E0
	ldrh r2, [sp, #0x0]
	ldr r1, [r6, #0x14]
	strh r2, [r1, #0x0]
	ldr r1, [r6, #0x18]
	str r0, [r1, #0x0]
	ldrsh r1, [r4, #0x70]
	add r0, r5, #0xe0
	orr r1, r1, #0x4
	strh r1, [r4, #0x70]
	bl OS_UnlockMutex
_02098020: ; 0x02098020
	mov r0, #0x0
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02098030
FUN_02098030:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl FUN_02099FA8
_02098044: ; 0x02098044
	cmp r0, #0x0
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	cmp r6, #0x0
	mov r1, #0x0
	beq _0209806C
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_0209806C:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x2
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrsb r0, [r6, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020980A8
	cmp r0, #0x4
	movne r1, #0x0
_020980A8:
	cmp r1, #0x0
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrsb r2, [r6, #0x72]
	cmp r2, #0x1
	mvnne r0, #0x5
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrh r0, [r6, #0x74]
	cmp r0, #0x0
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, _0209811C ; =FUN_02097FB4
	mov r1, r6
	bl FUN_02097A98
	mov r1, r0
	ldrh r2, [r6, #0x74]
	mov r0, r6
	strh r2, [r1, #0x10]
	str r5, [r1, #0x14]
	str r4, [r1, #0x18]
	ldrsh r2, [r6, #0x70]
	orr r2, r2, #0x2
	strh r2, [r6, #0x70]
	bl FUN_02097958
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209811C: .word FUN_02097FB4

	arm_func_start FUN_02098120
FUN_02098120:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl FUN_02099FA8
_02098138: ; 0x02098138
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r6, #0x0
	mov r1, #0x0
	beq _02098164
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02098164:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x2
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrsb r0, [r6, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020981A8
	cmp r0, #0x4
	movne r1, #0x0
_020981A8:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrsb r0, [r6, #0x72]
	cmp r0, #0x1
	addne sp, sp, #0x4
	mvnne r0, #0x5
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldr r0, _02098228 ; =0x021061DC
	bl FUN_02097F70
	movs r7, r0
	addmi sp, sp, #0x4
	ldmmiia sp!, {r4-r7,lr}
	bxmi lr
	ldrh r1, [r6, #0x74]
	bl FUN_020984B4
_020981F4: ; 0x020981F4
	cmp r0, #0x0
	addlt sp, sp, #0x4
	ldmltia sp!, {r4-r7,lr}
	bxlt lr
	mov r0, r7
	mov r1, r5
	mov r2, r4
	bl FUN_02098030
_02098214: ; 0x02098214
	cmp r0, #0x0
	movge r0, r7
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02098228: .word 0x021061DC

	arm_func_start FUN_0209822C
FUN_0209822C: ; 0x0209822C
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_02099FA8
_02098238: ; 0x02098238
	cmp r0, #0x0
	mvnne r0, #0x1b
	ldmneia sp!, {r4,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _02098260
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02098260:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x2
	mvnne r0, #0x1b
	ldmneia sp!, {r4,lr}
	bxne lr
	ldrsb r0, [r4, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _0209829C
	cmp r0, #0x4
	movne r1, #0x0
_0209829C:
	cmp r1, #0x0
	mvneq r0, #0x1b
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrsb r0, [r4, #0x72]
	cmp r0, #0x1
	moveq r0, #0x0
	mvnne r0, #0x5
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020982C4
FUN_020982C4: ; 0x020982C4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r4, [r7, #0x4]
	mov r5, #0x0
	ldr r6, [r4, #0x64]
	add r0, r6, #0xe0
	bl OS_LockMutex
	ldrh r0, [r7, #0x10]
	ldrh r1, [r7, #0x12]
	ldr r2, [r7, #0x14]
	bl FUN_0209CB78
	mov r0, r5
	str r0, [r6, #0xf8]
	ldrsb r0, [r7, #0xc]
	cmp r0, #0x0
	beq _02098310
	cmp r0, #0x4
	bne _02098318
_02098310:
	bl FUN_0209C934
	mov r5, r0
_02098318:
	add r0, r6, #0xe0
	bl OS_UnlockMutex
_02098320: ; 0x02098320
	cmp r5, #0x0
	ldrnesh r1, [r4, #0x70]
	mvnne r0, #0x4b
	moveq r0, #0x0
	orrne r1, r1, #0x40
	strneh r1, [r4, #0x70]
	ldreqsh r1, [r4, #0x70]
	orreq r1, r1, #0x4
	streqh r1, [r4, #0x70]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02098350
FUN_02098350: ; 0x02098350
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrsb r2, [r4, #0x72]
	ldr r0, _020983AC ; =FUN_020982C4
	mov r1, r4
	bl FUN_02097A98
	movs r1, r0
	mvneq r0, #0x20
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrh r2, [r4, #0x74]
	mov r0, r4
	strh r2, [r1, #0x10]
	ldrh r2, [r4, #0x76]
	strh r2, [r1, #0x12]
	ldr r2, [r4, #0x78]
	str r2, [r1, #0x14]
	ldrsh r2, [r4, #0x70]
	orr r2, r2, #0x2
	strh r2, [r4, #0x70]
	bl FUN_02097958
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020983AC: .word FUN_020982C4

	arm_func_start FUN_020983B0
FUN_020983B0: ; 0x020983B0
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl FUN_02099FA8
_020983C4: ; 0x020983C4
	cmp r0, #0x0
	bne _020983D8
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x8
	beq _020983E4
_020983D8:
	mvn r0, #0x1b
	ldmia sp!, {r4-r6,lr}
	bx lr
_020983E4:
	cmp r6, #0x0
	mov r1, #0x0
	beq _020983FC
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020983FC:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrsb r0, [r6, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02098424
	cmp r0, #0x4
	movne r1, #0x0
_02098424:
	cmp r1, #0x0
	beq _0209849C
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x4
	beq _02098450
	ldrsb r0, [r6, #0x72]
	cmp r0, #0x1
	mvneq r0, #0x1d
	movne r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_02098450:
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x2
	beq _02098478
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x40
	ldrne r0, [r6, #0x6c]
	ldreq r0, _020984B0 ; =0x021061C0
	ldreq r0, [r0, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
_02098478:
	strh r5, [r6, #0x76]
	mov r0, r6
	str r4, [r6, #0x78]
	bl FUN_02098350
	ldrsb r1, [r6, #0x72]
	cmp r1, #0x1
	mvnne r0, #0x19
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209849C:
	strh r5, [r6, #0x76]
	str r4, [r6, #0x78]
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020984B0: .word 0x021061C0

	arm_func_start FUN_020984B4
FUN_020984B4:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	mov r5, r1
	bl FUN_02099FA8
_020984C8: ; 0x020984C8
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _020984F4
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020984F4:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x2
	addne sp, sp, #0x4
	mvnne r0, #0x6
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	strh r5, [r4, #0x74]
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x1
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r0, r4
	bl FUN_02098350
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02098550
FUN_02098550: ; 0x02098550
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r7, r2
	ldr r6, [r7, #0x64]
	mov r9, r0
	mov r8, r1
	bl OS_DisableInterrupts
	add r1, r6, #0x100
	ldrh r2, [r1, #0x8]
	ldrh r1, [r1, #0xa]
	mov r4, r0
	add r0, r2, r8
	cmp r1, r0
	blo _02098618
	ldr r1, _02098668 ; =0x021C8CC0
	add r0, r8, #0xc
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	blx r1
	movs r5, r0
	beq _02098604
	add r1, r6, #0x100
	ldrh r3, [r1, #0x8]
	mov r2, #0x0
	mov r0, r9
	add r3, r3, r8
	strh r3, [r1, #0x8]
	str r2, [r5, #0x0]
	strh r8, [r5, #0x4]
	ldrh r3, [r7, #0x18]
	mov r2, r8
	add r1, r5, #0xc
	strh r3, [r5, #0x6]
	ldr r3, [r7, #0x1c]
	str r3, [r5, #0x8]
	bl MI_CpuCopy8
	ldr r0, [r6, #0x100]
	cmp r0, #0x0
	ldrne r0, [r6, #0x100]
	strne r5, [r0, #0x0]
	str r5, [r6, #0x100]
	ldr r0, [r6, #0x104]
	cmp r0, #0x0
	streq r5, [r6, #0x104]
	b _02098628
_02098604:
	ldr r0, _0209866C ; =0x021C8D28
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	b _02098628
_02098618:
	ldr r0, _0209866C ; =0x021C8D28
	ldr r1, [r0, #0x4]
	add r1, r1, #0x1
	str r1, [r0, #0x4]
_02098628:
	ldrh r0, [r7, #0x74]
	cmp r0, #0x0
	ldreqh r0, [r7, #0xa]
	streqh r0, [r7, #0x74]
	ldrh r1, [r7, #0x1a]
	add r0, r6, #0x10c
	strh r1, [r7, #0x18]
	ldr r1, [r7, #0x20]
	str r1, [r7, #0x1c]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_02098668: .word 0x021C8CC0
_0209866C: .word 0x021C8D28

	arm_func_start FUN_02098670
FUN_02098670: ; 0x02098670
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r0
	ldr r9, [r10, #0x64]
	str r1, [sp, #0x0]
	ldr r0, [r9, #0x104]
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	bl OS_DisableInterrupts
	ldr r8, [r9, #0x104]
	str r0, [sp, #0xc]
	cmp r8, #0x0
	bne _02098710
	ldr r0, [sp, #0x3c]
	and r7, r0, #0x1
	add r6, r9, #0x10c
	mov r4, #0x1
	mov r5, #0x0
_020986B8:
	cmp r7, #0x0
	mvneq r11, #0x5
	beq _02098710
	mov r0, r6
	bl OS_SleepThread
	mov r0, r10
	bl FUN_02099FA8
_020986D4: ; 0x020986D4
	cmp r0, #0x0
	bne _020986FC
	mov r1, r5
	cmp r10, #0x0
	beq _020986F4
	ldrsh r0, [r10, #0x70]
	ands r0, r0, #0x1
	movne r1, r4
_020986F4:
	cmp r1, #0x0
	bne _02098704
_020986FC:
	mvn r11, #0x37
	b _02098710
_02098704:
	ldr r8, [r9, #0x104]
	cmp r8, #0x0
	beq _020986B8
_02098710:
	cmp r8, #0x0
	beq _020987A4
	ldrh r1, [r8, #0x4]
	ldr r0, [sp, #0x4]
	cmp r0, r1
	strgt r1, [sp, #0x4]
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, r8, #0xc
	bl MI_CpuCopy8
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	ldrneh r1, [r8, #0x6]
	strneh r1, [r0, #0x0]
	ldr r1, [sp, #0x38]
	cmp r1, #0x0
	ldrne r0, [r8, #0x8]
	strne r0, [r1, #0x0]
	ldrsb r0, [r9, #0xfe]
	ldrh r11, [r8, #0x4]
	cmp r0, #0x0
	bne _020987A4
	ldr r0, [r8, #0x0]
	ldr r1, _020987BC ; =0x021C8CC0
	str r0, [r9, #0x104]
	ldr r0, [r8, #0x0]
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r9, #0x100]
	ldr r1, [r1, #0x0]
	mov r0, r8
	ldr r1, [r1, #0x1c]
	blx r1
	add r0, r9, #0x100
	ldrh r1, [r0, #0x8]
	sub r1, r1, r11
	strh r1, [r0, #0x8]
_020987A4:
	ldr r0, [sp, #0xc]
	bl OS_RestoreInterrupts
	mov r0, r11
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020987BC: .word 0x021C8CC0

	arm_func_start FUN_020987C0
FUN_020987C0: ; 0x020987C0
	stmdb sp!, {r4-r6,lr}
	ldr r6, [r0, #0x64]
	bl OS_DisableInterrupts
	ldr r4, [r6, #0xf8]
	mov r5, r0
	cmp r4, #0x0
	beq _020987EC
	mov r1, #0x0
	mov r0, r4
	str r1, [r6, #0xf8]
	bl FUN_0209C52C
_020987EC:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02098800
FUN_02098800: ; 0x02098800
	ldr ip, _0209880C ; =FUN_020987C0
	ldr r0, [r0, #0x4]
	bx r12
	.balign 4
_0209880C: .word FUN_020987C0

	arm_func_start FUN_02098810
FUN_02098810:
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x64]
	ldrh r0, [r1, #0xfc]
	ldr r1, [r1, #0xf8]
	cmp r1, r0
	movlt r0, #0x0
	ldmltia sp!, {r4,lr}
	bxlt lr
	ldr r0, _02098864 ; =FUN_02098800
	mov r1, r4
	mov r2, #0x0
	bl FUN_02097A98
	movs r1, r0
	mvneq r0, #0x20
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	bl FUN_02097958
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02098864: .word FUN_02098800

	arm_func_start FUN_02098868
FUN_02098868: ; 0x02098868
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	ldr r9, [r0, #0x4]
	ldr r1, [r0, #0x10]
	ldr r8, [r9, #0x64]
	str r1, [sp, #0x4]
	ldr r1, [r0, #0x18]
	ldr r10, [r0, #0x14]
	ldr r0, [r0, #0x1c]
	ldr r7, [r8, #0xf8]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	add r11, sp, #0x10
	mov r5, #0x0
	mov r6, #0x1
	mov r4, #0xa
_020988A8:
	mov r0, r11
	bl FUN_0209C638
_020988B0: ; 0x020988B0
	cmp r0, #0x0
	beq _02098904
	ldr r1, [sp, #0x10]
	sub r1, r1, r7
	cmp r1, #0x0
	bgt _02098904
	ldrsb r0, [r9, #0x73]
	mov r1, r6
	cmp r0, #0x0
	beq _020988E0
	cmp r0, #0x4
	movne r1, r5
_020988E0:
	cmp r1, #0x0
	beq _020988F8
	ldrb r0, [r9, #0x8]
	cmp r0, #0x4
	movne r0, #0x0
	bne _02098904
_020988F8:
	mov r0, r4
	bl OS_Sleep
	b _020988A8
_02098904:
	ldrsb r1, [r9, #0x73]
	cmp r1, #0x4
	bne _02098954
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r1, [sp, #0x10]
	cmp r10, r1
	movhi r10, r1
	ldr r1, [sp, #0x4]
	mov r2, r10
	bl MI_CpuCopy8
	mov r0, r10
	bl FUN_0209C52C
	add sp, sp, #0x14
	mov r0, r10
	ldmia sp!, {r4-r11,lr}
	bx lr
_02098954:
	cmp r0, #0x0
	moveq r4, #0x0
	beq _02098980
	ldr r4, [sp, #0xc]
	ldr r1, [sp, #0x4]
	ldr r3, [sp, #0x8]
	mov r0, r9
	mov r2, r10
	str r4, [sp, #0x0]
	bl FUN_02098AA4
	mov r4, r0
_02098980:
	cmp r4, #0x0
	addle sp, sp, #0x14
	movle r0, r4
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	ldrh r0, [r8, #0xfc]
	ldr r1, [r8, #0xf8]
	cmp r1, r0
	blt _020989AC
	mov r0, r9
	bl FUN_020987C0
_020989AC:
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_020989BC
FUN_020989BC: ; 0x020989BC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	ldr r0, _02098A10 ; =FUN_02098868
	mov r1, r7
	mov r2, #0x1
	mov r4, r3
	bl FUN_02097A98
	mov r1, r0
	str r6, [r1, #0x10]
	str r5, [r1, #0x14]
	ldr r2, [sp, #0x18]
	str r4, [r1, #0x18]
	mov r0, r7
	str r2, [r1, #0x1c]
	bl FUN_02097958
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02098A10: .word FUN_02098868

	arm_func_start FUN_02098A14
FUN_02098A14:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x64]
	ldr r5, [r0, #0xc4]
	ldr r4, [r0, #0xf8]
	ldr r0, [r5, #0x44]
	subs lr, r0, r4
	bmi _02098A78
	ldrh r12, [r5, #0xa]
	ldr r0, [sp, #0x10]
	cmp lr, #0x0
	strh r12, [r2, #0x0]
	ldrh r2, [r5, #0x18]
	strh r2, [r3, #0x0]
	ldr r2, [r5, #0x1c]
	str r2, [r0, #0x0]
	str lr, [r1, #0x0]
	bne _02098A90
	ldrb r0, [r5, #0x8]
	cmp r0, #0x4
	beq _02098A90
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_02098A78:
	mvn r0, #0x0
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_02098A90:
	ldr r0, [r5, #0x40]
	add r0, r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02098AA4
FUN_02098AA4: ; 0x02098AA4
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x14
	mov r9, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	bl OS_DisableInterrupts
	add r1, sp, #0xc
	mov r5, r0
	str r1, [sp, #0x0]
	add r1, sp, #0x8
	mov r0, r9
	add r2, sp, #0x4
	add r3, sp, #0x6
	bl FUN_02098A14
_02098AE0: ; 0x02098AE0
	cmp r0, #0x0
	beq _02098B48
	ldr r4, [sp, #0x8]
	cmp r4, #0x0
	mvneq r4, #0x5
	beq _02098B64
	ldrsb r1, [r9, #0x73]
	cmp r7, r4
	movgt r7, r4
	mov r2, #0x1
	cmp r1, #0x0
	beq _02098B18
	cmp r1, #0x4
	movne r2, #0x0
_02098B18:
	cmp r2, #0x0
	mov r1, r8
	mov r2, r7
	movne r4, r7
	bl MI_CpuCopy8
	ldr r1, [r9, #0x64]
	ldrsb r0, [r1, #0xfe]
	cmp r0, #0x0
	ldreq r0, [r1, #0xf8]
	addeq r0, r0, r4
	streq r0, [r1, #0xf8]
	b _02098B64
_02098B48:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	ldrsh r0, [r9, #0x70]
	moveq r4, #0x0
	mvnne r4, #0x1b
	bic r0, r0, #0x6
	strh r0, [r9, #0x70]
_02098B64:
	cmp r4, #0x0
	blt _02098B9C
	cmp r6, #0x0
	beq _02098B8C
	ldr r1, [sp, #0x30]
	cmp r1, #0x0
	ldrneh r0, [sp, #0x6]
	strneh r0, [r6, #0x0]
	ldrne r0, [sp, #0xc]
	strne r0, [r1, #0x0]
_02098B8C:
	ldrh r0, [r9, #0x74]
	cmp r0, #0x0
	ldreqh r0, [sp, #0x4]
	streqh r0, [r9, #0x74]
_02098B9C:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_02098BB4
FUN_02098BB4: ; 0x02098BB4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldrsb r12, [r7, #0x73]
	mov r6, r1
	mov r5, r2
	mov r4, r3
	cmp r12, #0x4
	bne _02098BF0
	ldr r4, [sp, #0x18]
	str r4, [sp, #0x0]
	bl FUN_020989BC
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_02098BF0:
	ldr r12, [sp, #0x18]
	str r12, [sp, #0x0]
	bl FUN_02098AA4
	mvn r1, #0x5
	cmp r0, r1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldr r1, [sp, #0x1c]
	ands r1, r1, #0x1
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r12, [sp, #0x18]
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, r4
	str r12, [sp, #0x0]
	bl FUN_020989BC
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02098C4C
FUN_02098C4C: ; 0x02098C4C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	ldr r5, [sp, #0x28]
	mov r7, r0
	ands r0, r5, #0x2
	ldr r5, [r7, #0x64]
	beq _02098C74
	cmp r5, #0x0
	movne r6, #0x1
	bne _02098C78
_02098C74:
	mov r6, #0x0
_02098C78:
	cmp r6, #0x0
	ldrnesb r4, [r5, #0xfe]
	movne r0, #0x1
	strneb r0, [r5, #0xfe]
	ldrsb r0, [r7, #0x73]
	cmp r0, #0x1
	bne _02098CB4
	ldr r0, [sp, #0x20]
	ldr r12, [sp, #0x24]
	str r0, [sp, #0x0]
	mov r0, r7
	str r12, [sp, #0x4]
	bl FUN_02098670
	mov r8, r0
	b _02098CDC
_02098CB4:
	ldr r0, [sp, #0x20]
	ldr r12, [sp, #0x24]
	str r0, [sp, #0x0]
	mov r0, r7
	str r12, [sp, #0x4]
	bl FUN_02098BB4
	movs r8, r0
	bmi _02098CDC
	mov r0, r7
	bl FUN_02098810
_02098CDC:
	cmp r6, #0x0
	strneb r4, [r5, #0xfe]
	mov r0, r8
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_02098CF4
FUN_02098CF4:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc
	mov r9, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	bl FUN_02099FA8
_02098D10: ; 0x02098D10
	cmp r0, #0x0
	addne sp, sp, #0xc
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	ldr r0, [sp, #0x2c]
	ands r0, r0, #0x4
	bne _02098D3C
	ldrsb r0, [r9, #0x72]
	cmp r0, #0x0
	bne _02098D5C
_02098D3C:
	ldrsb r0, [r9, #0x73]
	cmp r0, #0x4
	addeq sp, sp, #0xc
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r4, #0x0
	b _02098D78
_02098D5C:
	bl OS_GetProcMode
	cmp r0, #0x12
	addeq sp, sp, #0xc
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r4, #0x1
_02098D78:
	cmp r9, #0x0
	mov r1, #0x0
	beq _02098D90
	ldrsh r0, [r9, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02098D90:
	cmp r1, #0x0
	addeq sp, sp, #0xc
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldrsb r0, [r9, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02098DBC
	cmp r0, #0x4
	movne r1, #0x0
_02098DBC:
	cmp r1, #0x0
	beq _02098DEC
	ldrsh r0, [r9, #0x70]
	ands r0, r0, #0x4
	beq _02098DDC
	ldrsh r0, [r9, #0x70]
	ands r0, r0, #0x8
	beq _02098DEC
_02098DDC:
	add sp, sp, #0xc
	mvn r0, #0x37
	ldmia sp!, {r4-r9,lr}
	bx lr
_02098DEC:
	ands r0, r4, #0x1
	ldr r5, [r9, #0x64]
	bne _02098E18
	add r0, r5, #0xe0
	bl OS_TryLockMutex
_02098E00: ; 0x02098E00
	cmp r0, #0x0
	bne _02098E20
	add sp, sp, #0xc
	mvn r0, #0x5
	ldmia sp!, {r4-r9,lr}
	bx lr
_02098E18:
	add r0, r5, #0xe0
	bl OS_LockMutex
_02098E20:
	ldr r0, [sp, #0x28]
	ldr r12, [sp, #0x2c]
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	mov r0, r9
	mov r1, r8
	mov r2, r7
	mov r3, r6
	str r12, [sp, #0x8]
	bl FUN_02098C4C
	mov r4, r0
	add r0, r5, #0xe0
	bl OS_UnlockMutex
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_02098E64
FUN_02098E64: ; 0x02098E64
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r2
	ldr r5, [r6, #0x14]
	ldr r4, [r6, #0x1c]
	cmp r5, r1
	mov r7, r0
	movgt r5, r1
	movgt r4, #0x0
	bgt _02098E98
	sub r0, r1, r5
	cmp r4, r0
	movgt r4, r0
_02098E98:
	cmp r5, #0x0
	ble _02098EC8
	ldr r0, [r6, #0x10]
	mov r1, r7
	mov r2, r5
	bl MI_CpuCopy8
	ldr r0, [r6, #0x10]
	add r0, r0, r5
	str r0, [r6, #0x10]
	ldr r0, [r6, #0x14]
	sub r0, r0, r5
	str r0, [r6, #0x14]
_02098EC8:
	cmp r4, #0x0
	ble _02098EF8
	ldr r0, [r6, #0x18]
	mov r2, r4
	add r1, r7, r5
	bl MI_CpuCopy8
	ldr r0, [r6, #0x18]
	add r0, r0, r4
	str r0, [r6, #0x18]
	ldr r0, [r6, #0x1c]
	sub r0, r0, r4
	str r0, [r6, #0x1c]
_02098EF8:
	add r0, r5, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02098F08
FUN_02098F08: ; 0x02098F08
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _02098FBC ; =0x021D3498
	mov r4, r0
	ldr r0, [r1, #0x4]
	ldr r5, [r0, #0xa4]
	bl OS_DisableInterrupts
_02098F24: ; 0x02098F24
	cmp r5, #0x0
	beq _02098F74
	ldrh r3, [r5, #0x2e]
	cmp r3, #0x0
	beq _02098F64
	ldrh r2, [r5, #0x2c]
	cmp r2, #0x0
	beq _02098F64
	ldr r1, _02098FC0 ; =0x021C8CD4
	cmp r3, r2
	ldr r1, [r1, #0x24]
	movgt r3, r2
	cmp r3, r1
	movgt r3, r1
	mov r5, r3, lsl #0x1
	b _02098F80
_02098F64:
	ldr r1, _02098FC0 ; =0x021C8CD4
	ldr r1, [r1, #0x24]
	mov r5, r1, lsl #0x1
	b _02098F80
_02098F74:
	ldr r1, _02098FC0 ; =0x021C8CD4
	ldr r1, [r1, #0x24]
	mov r5, r1, lsl #0x1
_02098F80:
	bl OS_RestoreInterrupts
_02098F84: ; 0x02098F84
	cmp r5, #0x0
	ble _02098FAC
	mov r0, r4
	mov r1, r5
	bl _s32_div_f
_02098F98: ; 0x02098F98
	cmp r0, #0x0
	mulgt r0, r5, r0
	addgt sp, sp, #0x4
	ldmgtia sp!, {r4-r5,lr}
	bxgt lr
_02098FAC:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02098FBC: .word 0x021D3498
_02098FC0: .word 0x021C8CD4

	arm_func_start FUN_02098FC4
FUN_02098FC4: ; 0x02098FC4
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	ldr r7, [r8, #0x4]
	mov r4, #0x0
	ldrsb r0, [r7, #0x73]
	ldr r6, [r7, #0x68]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02098FF4
	cmp r0, #0x4
	movne r1, r4
_02098FF4:
	cmp r1, #0x0
	beq _02099008
	ldrsh r0, [r7, #0x70]
	ands r0, r0, #0x4
	beq _020990DC
_02099008:
	ldr r2, [r8, #0x28]
	cmp r2, #0x0
	beq _02099020
	ldrh r0, [r8, #0x24]
	ldrh r1, [r8, #0x26]
	bl FUN_0209CB78
_02099020:
	ldrsb r1, [r7, #0x73]
	mov r0, #0x1
	cmp r1, #0x0
	beq _02099038
	cmp r1, #0x4
	movne r0, #0x0
_02099038:
	cmp r0, #0x0
	movne r2, #0x36
	moveq r2, #0x2a
	ldr r0, [r7, #0x4c]
	cmp r1, #0x0
	add r5, r0, r2
	beq _0209905C
	cmp r1, #0x4
	bne _02099070
_0209905C:
	ldr r0, [r7, #0x48]
	sub r0, r0, r2
	bl FUN_02098F08
	mov r9, r0
	b _02099078
_02099070:
	ldr r0, [r7, #0x48]
	sub r9, r0, r2
_02099078:
	mov r0, r5
	mov r1, r9
	mov r2, r8
	bl FUN_02098E64
	mov r1, r0
	cmp r1, #0x0
	ble _020990E0
	mov r0, r5
	bl FUN_0209C030
_0209909C: ; 0x0209909C
	cmp r0, #0x0
	bgt _020990D4
	ldrsb r0, [r7, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020990BC
	cmp r0, #0x4
	movne r1, #0x0
_020990BC:
	cmp r1, #0x0
	ldrnesh r0, [r7, #0x70]
	mvn r4, #0x4b
	bicne r0, r0, #0xe
	strneh r0, [r7, #0x70]
	b _020990E0
_020990D4:
	add r4, r4, r0
	b _02099078
_020990DC:
	mvn r4, #0x4b
_020990E0:
	ldrh r2, [r8, #0x20]
	add r1, r6, #0x100
	add r0, r6, #0x104
	strh r2, [r1, #0x2]
	bl OS_WakeupThread
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_02099104
FUN_02099104:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	ldr r6, [r9, #0x68]
	mov r4, r1
	mov r8, r2
	ldr r1, [r6, #0x10c]
	ldr r2, [sp, #0x28]
	ldr r0, _0209929C ; =FUN_02098FC4
	mov r7, r3
	bl FUN_02097A98
	movs r5, r0
	addeq sp, sp, #0x4
	mvneq r0, #0x20
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r0, [sp, #0x28]
	ands r0, r0, #0x1
	beq _02099164
	ldrsb r0, [r9, #0x73]
	cmp r0, #0x1
	movne r0, #0x3
	strneb r0, [r5, #0xd]
	bne _0209916C
_02099164:
	mov r0, #0x0
	strb r0, [r5, #0xd]
_0209916C:
	ldr r2, [r6, #0xf8]
	add r1, r7, r8
	cmp r1, r2
	ldr r3, [r6, #0xfc]
	bge _020991A0
	add r0, r3, r7
	str r0, [r5, #0x10]
	str r8, [r5, #0x14]
	mov r0, #0x0
	str r0, [r5, #0x18]
	mov r7, r1
	str r0, [r5, #0x1c]
	b _020991D8
_020991A0:
	add r0, r3, r7
	str r0, [r5, #0x10]
	sub r0, r2, r7
	str r0, [r5, #0x14]
	str r3, [r5, #0x18]
	ldr r0, [r5, #0x14]
	sub r0, r8, r0
	str r0, [r5, #0x1c]
	ldr r7, [r5, #0x1c]
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	mov r2, r7
	add r0, r4, r0
	bl MI_CpuCopy8
_020991D8:
	ldr r1, [r5, #0x10]
	ldr r2, [r5, #0x14]
	mov r0, r4
	bl MI_CpuCopy8
	add r0, r6, #0x100
	ldrh r4, [r0, #0x0]
	strh r7, [r5, #0x20]
	ldrh r1, [r5, #0x20]
	strh r1, [r0, #0x0]
	ldrsb r0, [r9, #0x73]
	cmp r0, #0x1
	bne _02099268
	ldrh r0, [r9, #0x74]
	cmp r0, #0x0
	bne _02099224
	bl FUN_0209CC8C
	strh r0, [r9, #0x74]
	ldrh r0, [r9, #0x74]
	strh r0, [r9, #0xa]
_02099224:
	ldrh r0, [r9, #0x74]
	strh r0, [r5, #0x24]
	ldr r1, [r9, #0x78]
	cmp r1, #0x0
	beq _02099244
	ldr r0, [sp, #0x24]
	cmp r0, #0x0
	beq _02099258
_02099244:
	ldr r1, [sp, #0x24]
	ldrh r0, [sp, #0x20]
	str r1, [r5, #0x28]
	strh r0, [r5, #0x26]
	b _02099270
_02099258:
	str r1, [r5, #0x28]
	ldrh r0, [r9, #0x76]
	strh r0, [r5, #0x26]
	b _02099270
_02099268:
	mov r0, #0x0
	str r0, [r5, #0x28]
_02099270:
	ldr r0, [r6, #0x10c]
	mov r1, r5
	bl FUN_02097948
_0209927C: ; 0x0209927C
	cmp r0, #0x0
	addne r0, r6, #0x100
	movne r8, #0x0
	strneh r4, [r0, #0x0]
	mov r0, r8
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_0209929C: .word FUN_02098FC4

	arm_func_start FUN_020992A0
FUN_020992A0:
	ldr r2, [r0, #0x68]
	add r0, r2, #0x100
	ldrh r1, [r0, #0x0]
	ldrh r0, [r0, #0x2]
	ldr r2, [r2, #0xf8]
	sub r0, r0, r1
	subs r0, r0, #0x1
	addmi r0, r0, r2
	bx lr

	arm_func_start FUN_020992C4
FUN_020992C4: ; 0x020992C4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r10, r0
	mov r9, r1
	mov r8, r2
	cmp r8, r9
	mov r11, r3
	ldr r7, [r10, #0x68]
	movgt r8, r9
	bl OS_DisableInterrupts
	ldr r1, [sp, #0x28]
	str r0, [sp, #0x0]
	and r5, r1, #0x1
	add r4, r7, #0x104
_020992FC:
	mov r0, r10
	bl FUN_020992A0
	mov r6, r0
	cmp r6, r8
	blt _02099328
	add r0, r7, #0x100
	ldrh r0, [r0, #0x0]
	cmp r6, r9
	movge r6, r9
	str r0, [r11, #0x0]
	b _02099340
_02099328:
	cmp r5, #0x0
	moveq r6, #0x0
	beq _02099340
	mov r0, r4
	bl OS_SleepThread
	b _020992FC
_02099340:
	ldr r0, [sp, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02099358
FUN_02099358: ; 0x02099358
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	mov r10, r0
	ldr r4, [r10, #0x68]
	ldrsb r0, [r10, #0x73]
	ldr r4, [r4, #0x10c]
	mov r9, r1
	cmp r0, #0x1
	ldr r0, [r4, #0x48]
	mov r8, r2
	str r3, [sp, #0xc]
	ldr r7, [sp, #0x40]
	ldr r6, [sp, #0x44]
	mov r4, #0x0
	bne _020993B4
	sub r0, r0, #0x2a
	cmp r8, r0
	addgt sp, sp, #0x1c
	mvngt r0, #0x22
	ldmgtia sp!, {r4-r11,lr}
	bxgt lr
	str r8, [sp, #0x10]
	b _020993C4
_020993B4:
	sub r0, r0, #0x36
	str r0, [sp, #0x10]
	cmp r8, r0
	strle r8, [sp, #0x10]
_020993C4:
	cmp r8, #0x0
	ble _02099460
	and r11, r6, #0x1
_020993D0:
	ldr r2, [sp, #0x10]
	mov r0, r10
	mov r1, r8
	add r3, sp, #0x14
	str r6, [sp, #0x0]
	bl FUN_020992C4
	mov r5, r0
	cmp r5, #0x0
	ble _02099438
	ldr r0, [sp, #0xc]
	mov r1, r9
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	str r6, [sp, #0x8]
	ldr r3, [sp, #0x14]
	mov r0, r10
	mov r2, r5
	bl FUN_02099104
_02099418: ; 0x02099418
	cmp r0, #0x0
	addle sp, sp, #0x1c
	mvnle r0, #0x5
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	add r9, r9, r5
	sub r8, r8, r5
	add r4, r4, r5
_02099438:
	cmp r11, #0x0
	bne _02099458
	cmp r5, #0x0
	bgt _02099460
	add sp, sp, #0x1c
	mvn r0, #0x5
	ldmia sp!, {r4-r11,lr}
	bx lr
_02099458:
	cmp r8, #0x0
	bgt _020993D0
_02099460:
	mov r0, r4
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02099470
FUN_02099470: ; 0x02099470
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, r3
	bl FUN_02099FA8
_0209948C: ; 0x0209948C
	cmp r0, #0x0
	addne sp, sp, #0x8
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	cmp r8, #0x0
	mov r1, #0x0
	beq _020994B8
	ldrsh r0, [r8, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020994B8:
	cmp r1, #0x0
	addeq sp, sp, #0x8
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldrsb r0, [r8, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020994E4
	cmp r0, #0x4
	movne r1, #0x0
_020994E4:
	cmp r1, #0x0
	beq _02099514
	ldrsh r0, [r8, #0x70]
	ands r0, r0, #0x4
	beq _02099504
	ldrsh r0, [r8, #0x70]
	ands r0, r0, #0x8
	beq _02099514
_02099504:
	add sp, sp, #0x8
	mvn r0, #0x37
	ldmia sp!, {r4-r8,lr}
	bx lr
_02099514:
	ldr r0, [sp, #0x24]
	ldr r4, [r8, #0x68]
	ands r0, r0, #0x4
	bne _02099530
	ldrsb r0, [r8, #0x72]
	cmp r0, #0x0
	bne _02099554
_02099530:
	add r0, r4, #0xe0
	bl OS_TryLockMutex
_02099538: ; 0x02099538
	cmp r0, #0x0
	addeq sp, sp, #0x8
	mvneq r0, #0x5
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r12, #0x0
	b _02099560
_02099554:
	add r0, r4, #0xe0
	bl OS_LockMutex
	mov r12, #0x1
_02099560:
	ldr r1, [sp, #0x20]
	mov r0, r8
	str r1, [sp, #0x0]
	mov r1, r7
	mov r2, r6
	mov r3, r5
	str r12, [sp, #0x4]
	bl FUN_02099358
	mov r5, r0
	add r0, r4, #0xe0
	bl OS_UnlockMutex
	mov r0, r5
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_0209959C
FUN_0209959C: ; 0x0209959C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x4]
	mov r1, #0x1
	ldrsb r0, [r0, #0x73]
	cmp r0, #0x0
	beq _020995C0
	cmp r0, #0x4
	movne r1, #0x0
_020995C0:
	cmp r1, #0x0
	beq _020995CC
	bl FUN_0209C840
_020995CC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020995DC
FUN_020995DC: ; 0x020995DC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl FUN_02099FA8
_020995EC: ; 0x020995EC
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _02099618
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02099618:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x4
	beq _02099644
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x8
	beq _02099654
_02099644:
	add sp, sp, #0x4
	mvn r0, #0x37
	ldmia sp!, {r4-r5,lr}
	bx lr
_02099654:
	ldrsh r0, [r4, #0x70]
	orr r0, r0, #0x8
	strh r0, [r4, #0x70]
	ldr r5, [r4, #0x68]
	cmp r5, #0x0
	beq _020996AC
	ldr r1, [r5, #0x10c]
	cmp r1, #0x0
	beq _020996AC
	ldrsb r2, [r4, #0x72]
	ldr r0, _020996BC ; =FUN_0209959C
	bl FUN_02097A98
	movs r1, r0
	addeq sp, sp, #0x4
	mvneq r0, #0x20
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, [r5, #0x10c]
	bl FUN_02097948
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020996AC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020996BC: .word FUN_0209959C

	arm_func_start FUN_020996C0
FUN_020996C0: ; 0x020996C0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r4, _02099704 ; =0x021C8D34
	mov r5, r0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020996F0
_020996E0:
	bl FUN_020997B8
_020996E4: ; 0x020996E4
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020996E0
_020996F0:
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099704: .word 0x021C8D34

	arm_func_start FUN_02099708
FUN_02099708: ; 0x02099708
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	movs r8, r0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	add r0, r8, #0x20
	bl OS_JoinThread
	bl OS_DisableInterrupts
	mov r7, r0
	bl OS_DisableScheduler
	add r1, sp, #0x0
	mov r0, r8
	mov r2, #0x0
	bl OS_ReceiveMessage
_02099744: ; 0x02099744
	cmp r0, #0x0
	beq _0209979C
	add r4, sp, #0x0
	mvn r6, #0xa
	mov r5, #0x0
_02099758:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02099784
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0209977C
	mov r1, r6
	mov r2, r5
	bl OS_SendMessage
_0209977C:
	ldr r0, [sp, #0x0]
	bl FUN_02097A64
_02099784:
	mov r0, r8
	mov r1, r4
	mov r2, r5
	bl OS_ReceiveMessage
_02099794: ; 0x02099794
	cmp r0, #0x0
	bne _02099758
_0209979C:
	bl OS_EnableScheduler
	bl OS_RescheduleThread
	mov r0, r7
	bl OS_RestoreInterrupts
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_020997B8
FUN_020997B8:
	stmdb sp!, {r4-r6,lr}
	movs r4, r0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, #0x0
	strh r0, [r4, #0x70]
	ldrsb r1, [r4, #0x73]
	mov r2, #0x1
	cmp r1, #0x0
	beq _020997E8
	cmp r1, #0x4
	movne r2, r0
_020997E8:
	cmp r2, #0x0
	beq _02099804
	ldr r0, [r4, #0x68]
	bl FUN_02099708
	ldr r0, [r4, #0x64]
	bl FUN_02099708
	b _02099884
_02099804:
	cmp r1, #0x1
	bne _02099874
	ldr r0, [r4, #0x64]
	ldr r0, [r0, #0x104]
	cmp r0, #0x0
	beq _0209983C
	ldr r5, _020998C0 ; =0x021C8CC0
_02099820:
	ldr r1, [r5, #0x0]
	ldr r6, [r0, #0x0]
	ldr r1, [r1, #0x1c]
	blx r1
	mov r0, r6
	cmp r6, #0x0
	bne _02099820
_0209983C:
	ldr r0, [r4, #0x64]
	mov r1, #0x0
	add r0, r0, #0x100
	strh r1, [r0, #0x8]
	ldr r0, [r4, #0x64]
	str r1, [r0, #0x100]
	ldr r0, [r4, #0x64]
	str r1, [r0, #0x104]
	ldr r0, [r4, #0x64]
	add r0, r0, #0x10c
	bl OS_WakeupThread
	ldr r0, [r4, #0x64]
	bl FUN_02099708
	b _02099884
_02099874:
	cmp r1, #0x2
	bne _02099884
	ldr r0, [r4, #0x68]
	bl FUN_02099708
_02099884:
	bl OS_DisableInterrupts
	mov r5, r0
	mov r0, r4
	bl FUN_0209A054
	mov r0, r4
	bl FUN_02099FF0
	ldr r1, _020998C0 ; =0x021C8CC0
	mov r0, r4
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x1c]
	blx r1
	mov r0, r5
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020998C0: .word 0x021C8CC0

	arm_func_start FUN_020998C4
FUN_020998C4: ; 0x020998C4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, [r0, #0x4]
	mov r1, #0x1
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x0
	beq _020998E8
	cmp r0, #0x4
	movne r1, #0x0
_020998E8:
	cmp r1, #0x0
	beq _02099908
	ldr r0, [r4, #0x68]
	add r0, r0, #0x20
	bl OS_JoinThread
	bl FUN_0209C840
	bl FUN_0209C7AC
	bl FUN_0209CB24
_02099908:
	bl FUN_0209CC10
	ldrsh r0, [r4, #0x70]
	mov r1, #0x0
	bic r0, r0, #0x6
	strh r0, [r4, #0x70]
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x2
	ldreq r0, [r4, #0x68]
	ldrne r0, [r4, #0x64]
	bl FUN_020979F8
	bl OS_DisableInterrupts
	mov r5, r0
	mov r0, r4
	bl FUN_0209A054
	mov r0, r4
	bl FUN_0209A06C
	mov r0, r5
	bl OS_RestoreInterrupts
	ldrsh r1, [r4, #0x70]
	mov r0, #0x0
	orr r1, r1, #0x20
	strh r1, [r4, #0x70]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209996C
FUN_0209996C: ; 0x0209996C
	stmdb sp!, {r4,lr}
	mov r4, r0
	cmp r4, #0x0
	mvnle r0, #0x1b
	ldmleia sp!, {r4,lr}
	bxle lr
	bl FUN_02099F78
_02099988: ; 0x02099988
	cmp r0, #0x0
	mvnne r0, #0x19
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r0, r4
	bl FUN_02099FA8
_020999A0: ; 0x020999A0
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _020999C8
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020999C8:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x10
	mvnne r0, #0x19
	ldmneia sp!, {r4,lr}
	bxne lr
	ldrsh r0, [r4, #0x70]
	mov r1, #0x1
	orr r0, r0, #0x18
	strh r0, [r4, #0x70]
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x0
	beq _02099A10
	cmp r0, #0x4
	movne r1, #0x0
_02099A10:
	cmp r1, #0x0
	beq _02099A24
	ldr r0, [r4, #0x68]
	mov r1, #0x0
	bl FUN_020979F8
_02099A24:
	ldr r0, _02099A54 ; =FUN_020998C4
	mov r1, r4
	mov r2, #0x1
	bl FUN_02097A98
	mov r1, r0
	mov r2, #0x0
	mov r0, r4
	str r2, [r1, #0x8]
	bl FUN_020979DC
_02099A48: ; 0x02099A48
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02099A54: .word FUN_020998C4

	arm_func_start FUN_02099A58
FUN_02099A58:
	stmdb sp!, {r4,lr}
	movs r4, r0
	bmi _02099A88
	bl FUN_02099FA8
_02099A68: ; 0x02099A68
	cmp r0, #0x0
	beq _02099A88
	mov r0, r4
	bl FUN_02099F78
_02099A78: ; 0x02099A78
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
_02099A88:
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02099A94
FUN_02099A94: ; 0x02099A94
	stmdb sp!, {r4,lr}
	ldr r0, _02099B10 ; =0x021C8CD0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02099AE8
	bl FUN_02099B14
	movs r4, r0
	bne _02099AE0
	ldr r0, _02099B10 ; =0x021C8CD0
	ldr r0, [r0, #0x0]
	bl FUN_0209996C
	ldr r0, _02099B10 ; =0x021C8CD0
	ldr r0, [r0, #0x0]
	bl FUN_02099A58
_02099ACC: ; 0x02099ACC
	cmp r0, #0x0
	ldrne r0, _02099B10 ; =0x021C8CD0
	movne r1, #0x0
	strne r1, [r0, #0x0]
	mvn r4, #0x19
_02099AE0:
	bl FUN_020996C0
	b _02099B04
_02099AE8:
	bl FUN_0209FD34
_02099AEC: ; 0x02099AEC
	cmp r0, #0x0
	mvneq r4, #0x19
	beq _02099B04
	mov r0, #0x0
	bl FUN_020A87BC
	mov r4, #0x0
_02099B04:
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02099B10: .word 0x021C8CD0

	arm_func_start FUN_02099B14
FUN_02099B14: ; 0x02099B14
	stmdb sp!, {r4-r6,lr}
	ldr r4, _02099BBC ; =0x021C8CD0
	ldr r5, _02099BC0 ; =0x021C8D30
_02099B20:
	bl OS_DisableInterrupts
	ldr r6, [r5, #0x0]
	cmp r6, #0x0
	beq _02099B54
	ldr r2, [r4, #0x0]
_02099B34:
	cmp r6, r2
	beq _02099B48
	ldrsh r1, [r6, #0x70]
	ands r1, r1, #0x10
	beq _02099B54
_02099B48:
	ldr r6, [r6, #0x7c]
	cmp r6, #0x0
	bne _02099B34
_02099B54:
	bl OS_RestoreInterrupts
_02099B58: ; 0x02099B58
	cmp r6, #0x0
	beq _02099B6C
	mov r0, r6
	bl FUN_0209996C
	b _02099B20
_02099B6C:
	ldr r0, _02099BC0 ; =0x021C8D30
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02099B98
	ldr r0, _02099BBC ; =0x021C8CD0
	ldr r0, [r0, #0x0]
	cmp r1, r0
	bne _02099BB0
	ldr r0, [r1, #0x7c]
	cmp r0, #0x0
	bne _02099BB0
_02099B98:
	ldr r0, _02099BC4 ; =0x021C8D34
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
_02099BB0:
	mvn r0, #0x19
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_02099BBC: .word 0x021C8CD0
_02099BC0: .word 0x021C8D30
_02099BC4: .word 0x021C8D34

	arm_func_start FUN_02099BC8
FUN_02099BC8: ; 0x02099BC8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _02099C68 ; =0x021C8CC8
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	ldreq r0, _02099C6C ; =0x021C8F04
	ldreq r0, [r0, #0x0]
	streq r0, [r1, #0x0]
	bl FUN_02099A94
	mvn r4, #0x19
	cmp r0, r4
	bne _02099C10
	mov r5, #0x64
_02099BFC:
	mov r0, r5
	bl OS_Sleep
	bl FUN_02099A94
	cmp r0, r4
	beq _02099BFC
_02099C10:
	bl FUN_02097B14
	movs r4, r0
	bmi _02099C58
	bl FUN_0209FCC4
_02099C20: ; 0x02099C20
	mov r0, #0x0
	bl FUN_0209FD24
	ldr r0, _02099C70 ; =0x021C8CC0
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x28]
	cmp r0, #0x0
	bne _02099C4C
	ldr r0, _02099C74 ; =0x021C8CD4
	ldr r1, [r1, #0x1c]
	ldr r0, [r0, #0x1c]
	blx r1
_02099C4C:
	ldr r0, _02099C70 ; =0x021C8CC0
	mov r1, #0x0
	str r1, [r0, #0x0]
_02099C58:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099C68: .word 0x021C8CC8
_02099C6C: .word 0x021C8F04
_02099C70: .word 0x021C8CC0
_02099C74: .word 0x021C8CD4

	arm_func_start FUN_02099C78
FUN_02099C78:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _02099CE0 ; =0x021C8F04
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	bne _02099CBC
	ldr r0, _02099CE4 ; =0x021C8CCC
	ldr r0, [r0, #0x0]
	and r0, r0, #0x3
	cmp r0, #0x1
	bne _02099CCC
	bl OS_GetProcMode
	cmp r0, #0x12
	beq _02099CCC
	mov r0, #0xa
	bl OS_Sleep
	b _02099CCC
_02099CBC:
	ldr r0, _02099CE8 ; =0x021C8CC8
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	streq r2, [r0, #0x0]
_02099CCC:
	ldr r0, _02099CE0 ; =0x021C8F04
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02099CE0: .word 0x021C8F04
_02099CE4: .word 0x021C8CCC
_02099CE8: .word 0x021C8CC8

	arm_func_start FUN_02099CEC
FUN_02099CEC: ; 0x02099CEC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_02099C78
_02099D00: ; 0x02099D00
	cmp r0, #0x0
	ldrne r1, _02099D24 ; =0x021C8F1C
	mvneq r0, #0x26
	movne r0, #0x0
	strne r5, [r1, #0x0]
	strne r4, [r1, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099D24: .word 0x021C8F1C

	arm_func_start FUN_02099D28
FUN_02099D28:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _02099D84 ; =0x021C8F1C
	mov r5, r0
	ldr r7, [r1, #0x0]
	mov r2, #0x0
	ldr r6, [r1, #0x4]
	mov r0, r4
	str r2, [r1, #0x0]
	str r2, [r1, #0x4]
	bl FUN_0209AB80
	ldr r1, _02099D84 ; =0x021C8F1C
	mov r4, r0
	mov r0, r5
	str r7, [r1, #0x0]
	str r6, [r1, #0x4]
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02099D84: .word 0x021C8F1C

	arm_func_start FUN_02099D88
FUN_02099D88: ; 0x02099D88
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x64
	movs r4, r0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, _02099E34 ; =0x021C8CC0
	mov r0, #0xfd0
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	blx r1
	movs r5, r0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x64
	bl MI_CpuFill8
	ldr r3, _02099E38 ; =0x00000B68
	ldr r1, _02099E3C ; =0x00000466
	add r2, r5, r3
	add r0, sp, #0x0
	str r5, [sp, #0x40]
	str r3, [sp, #0x3c]
	str r2, [sp, #0x4c]
	str r1, [sp, #0x48]
	bl FUN_0209CC28
	mov r0, r4
	bl FUN_0209AB80
	mov r4, r0
	bl FUN_0209CC10
	ldr r1, _02099E34 ; =0x021C8CC0
	mov r0, r5
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x1c]
	blx r1
	mov r0, r4
	add sp, sp, #0x64
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099E34: .word 0x021C8CC0
_02099E38: .word 0x00000B68
_02099E3C: .word 0x00000466

	arm_func_start FUN_02099E40
FUN_02099E40:
	ldr r2, [r0, #0x64]
	mov r3, #0x0
	cmp r2, #0x0
	beq _02099E88
	ldrsb r1, [r0, #0x73]
	cmp r1, #0x1
	bne _02099E6C
	ldr r0, [r2, #0x104]
	cmp r0, #0x0
	ldrneh r3, [r0, #0x4]
	b _02099E88
_02099E6C:
	cmp r1, #0x0
	beq _02099E7C
	cmp r1, #0x4
	bne _02099E88
_02099E7C:
	ldr r1, [r0, #0x44]
	ldr r0, [r2, #0xf8]
	sub r3, r1, r0
_02099E88:
	mov r0, r3
	bx lr

	arm_func_start FUN_02099E90
FUN_02099E90:
	stmdb sp!, {r4-r6,lr}
	mov r4, #0x0
	mov r5, r0
	bl FUN_02099FA8
_02099EA0: ; 0x02099EA0
	cmp r0, #0x0
	orrne r4, r4, #0x80
	bne _02099F60
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x40
	ldrsb r0, [r5, #0x73]
	orrne r4, r4, #0x20
	cmp r0, #0x1
	beq _02099ED0
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x4
	beq _02099F00
_02099ED0:
	bl OS_DisableInterrupts
	mov r6, r0
	mov r0, r5
	bl FUN_02099E40
_02099EE0: ; 0x02099EE0
	cmp r0, #0x0
	mov r0, r5
	orrgt r4, r4, #0x1
	bl FUN_020992A0
_02099EF0: ; 0x02099EF0
	cmp r0, #0x0
	mov r0, r6
	orrgt r4, r4, #0x8
	bl OS_RestoreInterrupts
_02099F00:
	ldrsb r0, [r5, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02099F18
	cmp r0, #0x4
	movne r1, #0x0
_02099F18:
	cmp r1, #0x0
	beq _02099F60
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x4
	beq _02099F48
	ldrb r0, [r5, #0x8]
	cmp r0, #0x4
	beq _02099F48
	ands r0, r4, #0x1
	ldreqsh r0, [r5, #0x70]
	biceq r0, r0, #0x6
	streqh r0, [r5, #0x70]
_02099F48:
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x2
	bne _02099F60
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x4
	orreq r4, r4, #0x40
_02099F60:
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02099F6C
FUN_02099F6C:
	add r0, r0, #0x3
	bic r0, r0, #0x3
	bx lr

	arm_func_start FUN_02099F78
FUN_02099F78:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r1, r0
	ldr r0, _02099FA4 ; =0x021C8D34
	bl FUN_0209A008
_02099F8C: ; 0x02099F8C
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02099FA4: .word 0x021C8D34

	arm_func_start FUN_02099FA8
FUN_02099FA8:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r1, r0
	cmp r1, #0x0
	ble _02099FCC
	ldr r0, _02099FEC ; =0x021C8D30
	bl FUN_0209A008
_02099FC4: ; 0x02099FC4
	cmp r0, #0x0
	bne _02099FDC
_02099FCC:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {lr}
	bx lr
_02099FDC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02099FEC: .word 0x021C8D30

	arm_func_start FUN_02099FF0
FUN_02099FF0: ; 0x02099FF0
	ldr ip, _0209A000 ; =FUN_0209A034
	mov r1, r0
	ldr r0, _0209A004 ; =0x021C8D34
	bx r12
	.balign 4
_0209A000: .word FUN_0209A034
_0209A004: .word 0x021C8D34

	arm_func_start FUN_0209A008
FUN_0209A008:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _0209A02C
_0209A014:
	cmp r2, r1
	bxeq lr
	add r0, r2, #0x7c
	ldr r2, [r2, #0x7c]
	cmp r2, #0x0
	bne _0209A014
_0209A02C:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_0209A034
FUN_0209A034: ; 0x0209A034
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl FUN_0209A008
_0209A040: ; 0x0209A040
	cmp r0, #0x0
	ldrne r1, [r4, #0x7c]
	strne r1, [r0, #0x0]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209A054
FUN_0209A054: ; 0x0209A054
	ldr ip, _0209A064 ; =FUN_0209A034
	mov r1, r0
	ldr r0, _0209A068 ; =0x021C8D30
	bx r12
	.balign 4
_0209A064: .word FUN_0209A034
_0209A068: .word 0x021C8D30

	arm_func_start FUN_0209A06C
FUN_0209A06C: ; 0x0209A06C
	ldr ip, _0209A07C ; =FUN_0209A084
	mov r1, r0
	ldr r0, _0209A080 ; =0x021C8D34
	bx r12
	.balign 4
_0209A07C: .word FUN_0209A084
_0209A080: .word 0x021C8D34

	arm_func_start FUN_0209A084
FUN_0209A084: ; 0x0209A084
	ldr r2, [r0, #0x0]
	str r2, [r1, #0x7c]
	str r1, [r0, #0x0]
	bx lr

	arm_func_start FUN_0209A094
FUN_0209A094: ; 0x0209A094
	ldr ip, _0209A0A4 ; =FUN_0209A084
	mov r1, r0
	ldr r0, _0209A0A8 ; =0x021C8D30
	bx r12
	.balign 4
_0209A0A4: .word FUN_0209A084
_0209A0A8: .word 0x021C8D30

	arm_func_start FUN_0209A0AC
FUN_0209A0AC: ; 0x0209A0AC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r9, r2
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0x0
	mov r8, r3
	mvn r2, #0x0
	cmp r8, r2
	cmpeq r9, r2
	movne r11, #0x1
	mov r10, r1
	moveq r11, #0x0
	str r0, [sp, #0x4]
_0209A0E8:
	ldr r5, [sp, #0x4]
	ldr r7, [sp, #0x0]
	mov r6, r5
	cmp r10, #0x0
	bls _0209A128
_0209A0FC:
	ldrsh r1, [r7, #0x4]
	ldr r0, [r7, #0x0]
	orr r4, r1, #0xe0
	bl FUN_02099E90
_0209A10C: ; 0x0209A10C
	ands r0, r4, r0
	strh r0, [r7, #0x6]
	add r6, r6, #0x1
	addne r5, r5, #0x1
	cmp r6, r10
	add r7, r7, #0x8
	blo _0209A0FC
_0209A128:
	cmp r5, #0x0
	bgt _0209A160
	cmp r11, #0x0
	beq _0209A148
	mov r1, #0x0
	subs r0, r1, r9
	sbcs r0, r1, r8
	bge _0209A160
_0209A148:
	ldr r0, [sp, #0x8]
	bl OS_Sleep
	ldr r0, _0209A170 ; =0x0000020B
	subs r9, r9, r0
	sbc r8, r8, #0x0
	b _0209A0E8
_0209A160:
	mov r0, r5
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209A170: .word 0x0000020B

	arm_func_start FUN_0209A174
FUN_0209A174: ; 0x0209A174
	mov r2, r0, lsr #0x18
	strb r2, [r1, #0x0]
	mov r2, r0, lsr #0x10
	strb r2, [r1, #0x1]
	mov r2, r0, lsr #0x8
	strb r2, [r1, #0x2]
	strb r0, [r1, #0x3]
	bx lr

	arm_func_start FUN_0209A194
FUN_0209A194: ; 0x0209A194
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	cmp r0, #0x2
	mov r4, r2
	addne sp, sp, #0x18
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	cmp r3, #0x10
	addcc sp, sp, #0x18
	movcc r0, #0x0
	ldmccia sp!, {r4,lr}
	bxcc lr
	mov r0, r1
	add r1, sp, #0xc
	mov r2, #0x4
	bl MI_CpuCopy8
	ldr r0, [sp, #0xc]
	add r1, sp, #0x10
	bl FUN_0209A174
	ldrb r1, [sp, #0x12]
	ldr r2, _0209A220 ; =0x0210620C
	mov r0, r4
	str r1, [sp, #0x0]
	ldrb r3, [sp, #0x11]
	mov r1, #0x10
	str r3, [sp, #0x4]
	ldrb r3, [sp, #0x10]
	str r3, [sp, #0x8]
	ldrb r3, [sp, #0x13]
	bl OS_SNPrintf
	mov r0, r4
	add sp, sp, #0x18
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209A220: .word 0x0210620C

	arm_func_start FUN_0209A224
FUN_0209A224: ; 0x0209A224
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl FUN_02099D28
_0209A230: ; 0x0209A230
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r2, r0, lsr #0x18
	mov r1, r0, lsr #0x8
	mov r3, r0, lsl #0x8
	mov r12, r0, lsl #0x18
	and r2, r2, #0xff
	and r0, r1, #0xff00
	and r1, r3, #0xff0000
	orr r0, r2, r0
	and r2, r12, #0xff000000
	orr r0, r1, r0
	orr r0, r2, r0
	str r0, [r4, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209A27C
FUN_0209A27C: ; 0x0209A27C
	stmdb sp!, {r0-r3}

	arm_func_start FUN_0209A280
FUN_0209A280: ; 0x0209A280
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _0209A2B0 ; =0x021C8D5C
	add r1, sp, #0x8
	mov r0, #0x2
	mov r3, #0x10
	bl FUN_0209A194
	ldr r0, _0209A2B0 ; =0x021C8D5C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_0209A2B0: .word 0x021C8D5C

	arm_func_start THUNK_FUN_02099BC8
THUNK_FUN_02099BC8: ; 0x0209A2B4
	ldr ip, _0209A2BC ; =FUN_02099BC8
	bx r12
	.balign 4
_0209A2BC: .word FUN_02099BC8

	arm_func_start FUN_0209A2C0
FUN_0209A2C0: ; 0x0209A2C0
	stmdb sp!, {r4-r8,lr}
	ldr r1, [r0, #0xc]
	ldr ip, _0209A430 ; =0x021C8D6C
	cmp r1, #0x1
	moveq r1, #0x1
	movne r1, #0x0
	str r1, [r12, #0x0]
	ldr r6, [r0, #0x10]
	ldr r5, _0209A434 ; =FUN_0209A484
	mov r2, r6, lsr #0x18
	mov r1, r6, lsr #0x8
	mov r3, r6, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	mov r6, r6, lsl #0x18
	orr r1, r2, r1
	and r3, r3, #0xff0000
	orr r1, r3, r1
	and r2, r6, #0xff000000
	orr r1, r2, r1
	str r1, [r12, #0x4]
	ldr r7, [r0, #0x14]
	ldr r4, _0209A438 ; =FUN_0209A444
	mov r2, r7, lsr #0x18
	mov r1, r7, lsr #0x8
	mov r6, r7, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	mov r7, r7, lsl #0x18
	orr r1, r2, r1
	and r6, r6, #0xff0000
	and r2, r7, #0xff000000
	orr r1, r6, r1
	orr r1, r2, r1
	str r1, [r12, #0x8]
	ldr r1, [r0, #0x18]
	ldr r3, _0209A43C ; =0x021C8D40
	mov r7, r1, lsr #0x18
	mov r6, r1, lsr #0x8
	mov r8, r1, lsl #0x8
	and r7, r7, #0xff
	and r6, r6, #0xff00
	mov r1, r1, lsl #0x18
	orr r6, r7, r6
	and r8, r8, #0xff0000
	and r7, r1, #0xff000000
	orr r1, r8, r6
	orr r1, r7, r1
	str r1, [r12, #0xc]
	ldr r1, [r0, #0x1c]
	ldr r2, _0209A440 ; =0x021C8D3C
	mov r7, r1, lsr #0x18
	mov r6, r1, lsr #0x8
	mov r8, r1, lsl #0x8
	and r7, r7, #0xff
	and r6, r6, #0xff00
	mov r1, r1, lsl #0x18
	orr r6, r7, r6
	and r8, r8, #0xff0000
	and r7, r1, #0xff000000
	orr r1, r8, r6
	orr r1, r7, r1
	str r1, [r12, #0x10]
	ldr r1, [r0, #0x20]
	mov lr, #0x40
	mov r7, r1, lsr #0x18
	mov r6, r1, lsr #0x8
	mov r8, r1, lsl #0x8
	and r7, r7, #0xff
	and r6, r6, #0xff00
	mov r1, r1, lsl #0x18
	orr r6, r7, r6
	and r8, r8, #0xff0000
	and r7, r1, #0xff000000
	orr r1, r8, r6
	orr r1, r7, r1
	str r5, [r12, #0x18]
	str r4, [r12, #0x1c]
	str r1, [r12, #0x14]
	ldr r1, [r0, #0x4]
	str r1, [r3, #0x0]
	ldr r1, [r0, #0x8]
	str lr, [r12, #0x20]
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x2c]
	str r1, [r12, #0x30]
	ldr r1, [r0, #0x30]
	mov r0, r12
	str r1, [r12, #0x34]
	bl FUN_02097834
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209A430: .word 0x021C8D6C
_0209A434: .word FUN_0209A484
_0209A438: .word FUN_0209A444
_0209A43C: .word 0x021C8D40
_0209A440: .word 0x021C8D3C

	arm_func_start FUN_0209A444
FUN_0209A444: ; 0x0209A444
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r1, _0209A480 ; =0x021C8D3C
	ldr r2, [r0, #-0x4]
	ldr r3, [r1, #0x0]
	sub r1, r0, #0x4
	mov r0, #0x0
	blx r3
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209A480: .word 0x021C8D3C

	arm_func_start FUN_0209A484
FUN_0209A484: ; 0x0209A484
	stmdb sp!, {r4,lr}
	ldr r1, _0209A4B0 ; =0x021C8D40
	add r4, r0, #0x4
	ldr r2, [r1, #0x0]
	mov r1, r4
	mov r0, #0x0
	blx r2
	cmp r0, #0x0
	strne r4, [r0], #0x4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209A4B0: .word 0x021C8D40

	arm_func_start FUN_0209A4B4
FUN_0209A4B4: ; 0x0209A4B4
	cmp r0, #0x0
	mvneq r0, #0x0
	bxeq lr
	cmp r1, #0x3
	beq _0209A4D4
	cmp r1, #0x4
	beq _0209A4E8
	b _0209A4FC
_0209A4D4:
	ldrsb r0, [r0, #0x72]
	cmp r0, #0x1
	moveq r0, #0x0
	movne r0, #0x4
	bx lr
_0209A4E8:
	ands r1, r2, #0x4
	movne r1, #0x0
	strneb r1, [r0, #0x72]
	moveq r1, #0x1
	streqb r1, [r0, #0x72]
_0209A4FC:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_0209A504
FUN_0209A504: ; 0x0209A504
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r1
	add r1, sp, #0x0
	add r2, sp, #0x4
	bl FUN_02098120
_0209A51C: ; 0x0209A51C
	cmp r0, #0x0
	addlt sp, sp, #0x8
	ldmltia sp!, {r4,lr}
	bxlt lr
	ldrh r1, [sp, #0x0]
	mov r2, r1, asr #0x8
	mov r1, r1, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	orr r1, r2, r1
	strh r1, [r4, #0x2]
	ldr r12, [sp, #0x4]
	mov r2, r12, lsr #0x18
	mov r1, r12, lsr #0x8
	mov r3, r12, lsl #0x8
	mov r12, r12, lsl #0x18
	and r2, r2, #0xff
	and r1, r1, #0xff00
	and r3, r3, #0xff0000
	orr r1, r2, r1
	and r2, r12, #0xff000000
	orr r1, r3, r1
	orr r1, r2, r1
	str r1, [r4, #0x4]
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209A588
FUN_0209A588: ; 0x0209A588
	ldr ip, _0209A590 ; =FUN_0209822C
	bx r12
	.balign 4
_0209A590: .word FUN_0209822C

	arm_func_start FUN_0209A594
FUN_0209A594: ; 0x0209A594
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r12, [r1, #0x0]
	ldr r0, [r0, #0x0]
	mov r2, r12, lsr #0x18
	mov r4, r0, lsr #0x18
	mov lr, r0, lsr #0x8
	mov r1, r12, lsr #0x8
	mov r5, r0, lsl #0x8
	mov r3, r12, lsl #0x8
	mov r0, r0, lsl #0x18
	mov r12, r12, lsl #0x18
	and r4, r4, #0xff
	and lr, lr, #0xff00
	and r2, r2, #0xff
	and r1, r1, #0xff00
	and r5, r5, #0xff0000
	orr r4, r4, lr
	and r3, r3, #0xff0000
	orr r1, r2, r1
	and lr, r0, #0xff000000
	orr r0, r5, r4
	and r2, r12, #0xff000000
	orr r1, r3, r1
	orr r0, lr, r0
	orr r1, r2, r1
	bl FUN_02099CEC
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209A60C
FUN_0209A60C: ; 0x0209A60C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_02099C78
	mov r2, r0, lsr #0x18
	mov r1, r0, lsr #0x8
	mov r3, r0, lsl #0x8
	mov r12, r0, lsl #0x18
	and r2, r2, #0xff
	and r0, r1, #0xff00
	and r1, r3, #0xff0000
	orr r0, r2, r0
	and r2, r12, #0xff000000
	orr r0, r1, r0
	orr r0, r2, r0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209A650
FUN_0209A650: ; 0x0209A650
	stmdb sp!, {r4-r6,lr}
	movs r5, r0
	mov r4, r1
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	bl FUN_02099C78
_0209A66C: ; 0x0209A66C
	cmp r5, #0x0
	ldrneh r1, [r5, #0x74]
	mov r2, r0, lsr #0x18
	mov r6, #0x8
	moveq r1, #0x0
	cmp r0, #0x0
	moveq r1, #0x0
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	mov r5, r3, asr #0x8
	mov lr, r3, lsl #0x8
	strb r6, [r4, #0x0]
	mov r6, #0x2
	mov r1, r0, lsr #0x8
	mov r3, r0, lsl #0x8
	mov r12, r0, lsl #0x18
	and r0, r1, #0xff00
	and r2, r2, #0xff
	orr r0, r2, r0
	and r1, r3, #0xff0000
	and r5, r5, #0xff
	and lr, lr, #0xff00
	strb r6, [r4, #0x1]
	orr r3, r5, lr
	and r2, r12, #0xff000000
	orr r0, r1, r0
	strh r3, [r4, #0x2]
	orr r0, r2, r0
	str r0, [r4, #0x4]
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209A6EC
FUN_0209A6EC: ; 0x0209A6EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl FUN_02099D88
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, _0209A7A4 ; =0x021C8DA4
	ldr r2, _0209A7A8 ; =0x00000101
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, _0209A7A4 ; =0x021C8DA4
	ldr r2, _0209A7A8 ; =0x00000101
	mov r1, r5
	bl STD_CopyLString
	mov r1, r4, lsr #0x18
	mov r0, r4, lsr #0x8
	mov r2, r4, lsl #0x8
	mov r3, r4, lsl #0x18
	and r1, r1, #0xff
	and r0, r0, #0xff00
	and r2, r2, #0xff0000
	orr r0, r1, r0
	and r3, r3, #0xff000000
	orr r1, r2, r0
	ldr r5, _0209A7A4 ; =0x021C8DA4
	ldr r0, _0209A7AC ; =0x021C8D4C
	ldr ip, _0209A7B0 ; =0x021C8D44
	mov r4, #0x0
	ldr r2, _0209A7B4 ; =0x021C8D38
	orr r1, r3, r1
	mov lr, #0x2
	mov r3, #0x4
	str r5, [r0, #0x0]
	str r4, [r0, #0x4]
	strh lr, [r0, #0x8]
	strh r3, [r0, #0xa]
	str r12, [r0, #0xc]
	str r2, [r12, #0x0]
	str r4, [r12, #0x4]
	str r1, [r2, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209A7A4: .word 0x021C8DA4
_0209A7A8: .word 0x00000101
_0209A7AC: .word 0x021C8D4C
_0209A7B0: .word 0x021C8D44
_0209A7B4: .word 0x021C8D38

	arm_func_start thunk_FUN_0209996c
thunk_FUN_0209996c: ; 0x0209A7B8
	ldr ip, _0209A7C0 ; =FUN_0209996C
	bx r12
	.balign 4
_0209A7C0: .word FUN_0209996C

	arm_func_start thunk_FUN_020995dc
thunk_FUN_020995dc: ; 0x0209A7C4
	ldr ip, _0209A7CC ; =FUN_020995DC
	bx r12
	.balign 4
_0209A7CC: .word FUN_020995DC

	arm_func_start FUN_0209A7D0
FUN_0209A7D0: ; 0x0209A7D0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	ldr r5, [sp, #0x20]
	cmp r5, #0x0
	moveq r5, #0x0
	moveq r4, r5
	beq _0209A83C
	ldrh r4, [r5, #0x2]
	ldr r6, [r5, #0x4]
	mov r7, r4, asr #0x8
	mov r12, r4, lsl #0x8
	mov r4, r6, lsr #0x18
	mov lr, r6, lsr #0x8
	mov r5, r6, lsl #0x8
	mov r6, r6, lsl #0x18
	and r7, r7, #0xff
	and r12, r12, #0xff00
	orr r7, r7, r12
	and r4, r4, #0xff
	and lr, lr, #0xff00
	and r5, r5, #0xff0000
	orr r4, r4, lr
	mov r12, r7, lsl #0x10
	orr r4, r5, r4
	and r6, r6, #0xff000000
	mov r5, r12, lsr #0x10
	orr r4, r6, r4
_0209A83C:
	str r4, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r3, r5
	bl FUN_02099470
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209A858
FUN_0209A858: ; 0x0209A858
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	mov r12, #0x0
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r3, r12
	bl FUN_02099470
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209A880
FUN_0209A880: ; 0x0209A880
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	add r12, sp, #0xc
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	add r3, sp, #0x8
	bl FUN_02098CF4
_0209A89C: ; 0x0209A89C
	cmp r0, #0x0
	addlt sp, sp, #0x14
	ldmltia sp!, {lr}
	bxlt lr
	ldr r1, [sp, #0x18]
	cmp r1, #0x0
	addeq sp, sp, #0x14
	ldmeqia sp!, {lr}
	bxeq lr
	ldrh r2, [sp, #0x8]
	mov r3, r2, asr #0x8
	mov r2, r2, lsl #0x8
	and r3, r3, #0xff
	and r2, r2, #0xff00
	orr r2, r3, r2
	strh r2, [r1, #0x2]
	ldr lr, [sp, #0xc]
	mov r3, lr, lsr #0x18
	mov r2, lr, lsr #0x8
	mov r12, lr, lsl #0x8
	mov lr, lr, lsl #0x18
	and r3, r3, #0xff
	and r2, r2, #0xff00
	and r12, r12, #0xff0000
	orr r2, r3, r2
	and r3, lr, #0xff000000
	orr r2, r12, r2
	orr r2, r3, r2
	str r2, [r1, #0x4]
	add sp, sp, #0x14
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209A91C
FUN_0209A91C: ; 0x0209A91C
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	mov r12, #0x0
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r3, r12
	bl FUN_02098CF4
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209A944
FUN_0209A944: ; 0x0209A944
	stmdb sp!, {r4,lr}
	ldrh r2, [r1, #0x2]
	ldr lr, [r1, #0x4]
	mov r4, r2, asr #0x8
	mov r1, r2, lsl #0x8
	mov r3, lr, lsr #0x18
	mov r2, lr, lsr #0x8
	mov r12, lr, lsl #0x8
	mov lr, lr, lsl #0x18
	and r4, r4, #0xff
	and r1, r1, #0xff00
	orr r1, r4, r1
	mov r1, r1, lsl #0x10
	and r3, r3, #0xff
	and r2, r2, #0xff00
	and r12, r12, #0xff0000
	orr r2, r3, r2
	and r3, lr, #0xff000000
	orr r2, r12, r2
	mov r1, r1, lsr #0x10
	orr r2, r3, r2
	bl FUN_020983B0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209A9A4
FUN_0209A9A4: ; 0x0209A9A4
	ldrh r1, [r1, #0x2]
	ldr ip, _0209A9CC ; =FUN_020984B4
	mov r2, r1, asr #0x8
	mov r1, r1, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	orr r1, r2, r1
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	bx r12
	.balign 4
_0209A9CC: .word FUN_020984B4

	arm_func_start FUN_0209A9D0
FUN_0209A9D0: ; 0x0209A9D0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x1
	bne _0209A9F4
	ldr r0, _0209AA08 ; =0x021061DC
	bl FUN_02097F70
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209A9F4:
	ldr r0, _0209AA0C ; =0x021061C4
	bl FUN_02097F70
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209AA08: .word 0x021061DC
_0209AA0C: .word 0x021061C4

	arm_func_start FUN_0209AA10
FUN_0209AA10: ; 0x0209AA10
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r6, [r7, #0x4]
	ldr r5, [r6, #0x64]
	add r0, r5, #0xe0
	ldr r4, [r5, #0xc4]
	bl OS_LockMutex
	ldr r1, [r7, #0x10]
	cmp r1, #0x0
	beq _0209AA54
	mov r0, #0x1
	str r1, [r4, #0xc]
	bl FUN_020A02EC
	mov r0, #0x4
	strb r0, [r6, #0x73]
	b _0209AA68
_0209AA54:
	mov r0, #0x0
	strb r0, [r6, #0x73]
	bl FUN_020A02EC
_0209AA60: ; 0x0209AA60
	mov r0, #0x0
	str r0, [r4, #0xc]
_0209AA68:
	add r0, r5, #0xe0
	bl OS_UnlockMutex
_0209AA70: ; 0x0209AA70
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209AA80
FUN_0209AA80: ; 0x0209AA80
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	ldr r0, _0209AACC ; =FUN_0209AA10
	mov r1, r5
	mov r2, #0x1
	bl FUN_02097A98
	movs r1, r0
	addeq sp, sp, #0x4
	mvneq r0, #0x20
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	mov r0, r5
	str r4, [r1, #0x10]
	bl FUN_02097958
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209AACC: .word FUN_0209AA10

	arm_func_start FUN_0209AAD0
FUN_0209AAD0: ; 0x0209AAD0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_02099FA8
_0209AAE4: ; 0x0209AAE4
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldrsb r0, [r5, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _0209AB10
	cmp r0, #0x4
	movne r1, #0x0
_0209AB10:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r5, #0x0
	mov r1, #0x0
	beq _0209AB3C
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_0209AB3C:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x2
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r0, r5
	mov r1, r4
	bl FUN_0209AA80
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209AB80
FUN_0209AB80: ; 0x0209AB80
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	ldr r6, _0209ACC0 ; =0x021C8F24
	mov r9, #0x0
	ldr r11, [r6, #0x8]
	ldr r2, [r6, #0x0]
	ldr r1, [r6, #0x4]
	umull r5, r4, r11, r2
	mla r4, r11, r1, r4
	ldr r10, [r6, #0xc]
	ldr r3, [r6, #0x10]
	mla r4, r10, r2, r4
	adds r5, r3, r5
	ldr r1, [r6, #0x14]
	umull r8, r7, r11, r5
	adc r4, r1, r4
	mla r7, r11, r4, r7
	mla r7, r10, r5, r7
	mov r2, r9, lsl #0x10
	adds r8, r3, r8
	str r5, [r6, #0x0]
	adc r5, r1, r7
	mov r3, r9, lsl #0x10
	orr r2, r2, r4, lsr #0x10
	str r4, [r6, #0x4]
	orr r3, r3, r5, lsr #0x10
	add r1, sp, #0x4
	mov r10, r0
	strh r2, [sp, #0x8]
	str r8, [r6, #0x0]
	str r5, [r6, #0x4]
	strh r3, [sp, #0xa]
	bl FUN_0209AD34
_0209AC04: ; 0x0209AC04
	cmp r0, #0x0
	ldrne r0, [sp, #0x4]
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	mov r0, #0x1
	ldr r6, _0209ACC4 ; =0x021C8F1C
	strb r0, [sp, #0x0]
	strb r0, [sp, #0x1]
	add r5, sp, #0x8
	mov r4, r9
	mov r11, r9
_0209AC34:
	mov r8, r11
	add r7, sp, #0x0
_0209AC3C:
	ldrb r0, [r7, #0x0]
	cmp r0, #0x0
	beq _0209AC80
	mov r0, r8, lsl #0x1
	ldrh r2, [r5, r0]
	ldr r1, [r6, r8, lsl #0x2]
	mov r0, r10
	bl FUN_0209ACC8
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0209AC74
	mvn r1, #0x0
	cmp r0, r1
	bne _0209AC9C
_0209AC74:
	mvn r1, #0x0
	cmp r0, r1
	streqb r4, [r7, #0x0]
_0209AC80:
	add r8, r8, #0x1
	cmp r8, #0x2
	add r7, r7, #0x1
	blt _0209AC3C
	add r9, r9, #0x1
	cmp r9, #0x3
	blt _0209AC34
_0209AC9C:
	ldr r1, [sp, #0x4]
	mvn r0, #0x0
	cmp r1, r0
	moveq r0, #0x0
	streq r0, [sp, #0x4]
	ldr r0, [sp, #0x4]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209ACC0: .word 0x021C8F24
_0209ACC4: .word 0x021C8F1C

	arm_func_start FUN_0209ACC8
FUN_0209ACC8: ; 0x0209ACC8
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	movs r5, r1
	mov r6, r0
	mov r4, r2
	addeq sp, sp, #0x8
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	bl FUN_0209CB44
	bl FUN_0209CBE8
	mov r2, r5
	mov r0, #0x0
	mov r1, #0x35
	bl FUN_0209CB78
	mov r0, r6
	mov r2, r4
	mov r3, #0x0
	str r3, [sp, #0x0]
	mov r1, #0x1
	bl FUN_0209AE18
	mov r4, r0
	bl FUN_0209CB24
	mov r0, r4
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209AD34
FUN_0209AD34:
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r6, #0x0
	mov r8, r0
	mov r7, r1
	mov r5, r6
	add r4, sp, #0x0
_0209AD50:
	mov r0, r8
	mov r1, r4
	mov r6, r6, lsl #0x8
	bl FUN_0209ADE4
	ldr r2, [sp, #0x0]
	cmp r8, r2
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r8, r2
	cmp r0, #0xff
	bhi _0209ADB0
	cmp r5, #0x3
	beq _0209AD9C
	ldrb r1, [r2, #0x0]
	add r8, r2, #0x1
	cmp r1, #0x2e
	bne _0209ADB0
_0209AD9C:
	cmp r5, #0x3
	bne _0209ADC0
	ldrb r1, [r8, #0x0]
	cmp r1, #0x0
	beq _0209ADC0
_0209ADB0:
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209ADC0:
	add r5, r5, #0x1
	cmp r5, #0x4
	orr r6, r6, r0
	blt _0209AD50
	str r6, [r7, #0x0]
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_0209ADE4
FUN_0209ADE4: ; 0x0209ADE4
	str r0, [r1, #0x0]
	mov r12, #0x0
	mov r2, #0xa
_0209ADF0:
	ldrb r3, [r0, #0x0]
	sub r3, r3, #0x30
	and r3, r3, #0xff
	cmp r3, #0x9
	mlals r12, r2, r12, r3
	addls r0, r0, #0x1
	strls r0, [r1, #0x0]
	bls _0209ADF0
	mov r0, r12
	bx lr

	arm_func_start FUN_0209AE18
FUN_0209AE18: ; 0x0209AE18
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4c
	mov r9, r2
	mov r2, r9, asr #0x8
	mov r10, r1
	orr r1, r2, r9, lsl #0x8
	strh r1, [sp, #0x10]
	cmp r10, #0x20
	mov r5, #0x0
	movne r1, #0x1
	strneh r1, [sp, #0x12]
	ldreq r1, _0209B0C8 ; =0x00001001
	strh r5, [sp, #0x16]
	streqh r1, [sp, #0x12]
	mov r1, #0x100
	strh r1, [sp, #0x14]
	add r1, sp, #0x1c
	strh r5, [sp, #0x18]
	strh r5, [sp, #0x1a]
	str r5, [sp, #0xc]
	ldrb r6, [r0], #0x1
	str r3, [sp, #0x0]
	ldr r8, [sp, #0x70]
	add r2, r1, #0x1
	cmp r6, #0x0
	beq _0209AED8
	add r4, sp, #0x10
_0209AE84:
	cmp r6, #0x2e
	beq _0209AEB8
	sub r3, r2, r4
	cmp r3, #0x3c
	addge sp, sp, #0x4c
	mvnge r0, #0x0
	ldmgeia sp!, {r4-r11,lr}
	bxge lr
	strb r6, [r2], #0x1
	ldr r3, [sp, #0xc]
	add r3, r3, #0x1
	str r3, [sp, #0xc]
	b _0209AECC
_0209AEB8:
	ldr r3, [sp, #0xc]
	strb r3, [r1, #0x0]
	mov r1, r2
	str r5, [sp, #0xc]
	add r2, r2, #0x1
_0209AECC:
	ldrb r6, [r0], #0x1
	cmp r6, #0x0
	bne _0209AE84
_0209AED8:
	ldr r0, [sp, #0xc]
	mov r3, #0x0
	strb r0, [r1, #0x0]
	strb r3, [r2, #0x0]
	mov r0, r10, lsr #0x8
	strb r0, [r2, #0x1]
	strb r10, [r2, #0x2]
	strb r3, [r2, #0x3]
	mov r3, #0x1
	add r0, sp, #0x10
	add r1, r2, #0x5
	sub r1, r1, r0
	strb r3, [r2, #0x4]
	bl FUN_0209C030
	mov r6, #0x0
	bl OS_GetTick
	mov r5, r0, lsr #0x10
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x1
	orr r5, r5, r1, lsl #0x10
	str r0, [sp, #0x4]
	mvn r11, #0x0
	b _0209B084
_0209AF38:
	bl FUN_0209BF9C
_0209AF3C: ; 0x0209AF3C
	cmp r0, #0x0
	bne _0209AF4C
	bl FUN_020A005C
	b _0209B084
_0209AF4C:
	add r0, sp, #0xc
	bl FUN_0209C638
	ldr r1, [sp, #0xc]
	cmp r1, #0xc
	bls _0209B07C
	ldrh r3, [r0, #0x0]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r9, r2, lsr #0x10
	bne _0209B07C
	ldrb r2, [r0, #0x3]
	and r2, r2, #0xf
	cmp r2, #0x3
	moveq r6, r11
	beq _0209B07C
	cmp r2, #0x0
	bne _0209B07C
	ldrb r2, [r0, #0x4]
	add r4, r0, r1
	ldrb r1, [r0, #0x5]
	add r0, r0, #0xc
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	movs r1, r1, lsr #0x10
	sub r7, r1, #0x1
	beq _0209AFCC
_0209AFB8:
	bl FUN_0209B0D0
_0209AFBC: ; 0x0209AFBC
	cmp r7, #0x0
	add r0, r0, #0x4
	sub r7, r7, #0x1
	bne _0209AFB8
_0209AFCC:
	cmp r0, r4
	bhs _0209B07C
_0209AFD4:
	bl FUN_0209B0D0
	ldrb r7, [r0, #0x8]
	ldrb r1, [r0, #0x9]
	ldrb r3, [r0, #0x0]
	ldrb r2, [r0, #0x1]
	orr r1, r1, r7, lsl #0x8
	mov r1, r1, lsl #0x10
	orr r3, r2, r3, lsl #0x8
	mov r2, r1, lsr #0x10
	mov r1, r3, lsl #0x10
	cmp r10, r1, lsr #0x10
	bne _0209B06C
	cmp r10, #0xc
	beq _0209B04C
	add r1, r0, #0x6
	add r3, r1, r2
	add r4, r0, #0x8
	ldrb r1, [r1, r2]
	ldrb r0, [r3, #0x1]
	add r3, r4, r2
	ldrb r2, [r4, r2]
	orr r0, r0, r1, lsl #0x8
	ldrb r1, [r3, #0x1]
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	orr r0, r1, r2, lsl #0x8
	mov r1, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r6, r1, r0, lsr #0x10
	b _0209B07C
_0209B04C:
	cmp r2, r8
	ldrhi r6, [sp, #0x8]
	bhi _0209B07C
	ldr r1, [sp, #0x0]
	add r0, r0, #0xa
	bl MI_CpuCopy8
	ldr r6, [sp, #0x4]
	b _0209B07C
_0209B06C:
	add r1, r2, #0xa
	add r0, r0, r1
	cmp r0, r4
	blo _0209AFD4
_0209B07C:
	ldr r0, [sp, #0xc]
	bl FUN_0209C52C
_0209B084:
	ldr r0, _0209B0CC ; =0x021C8EFC
	ldr r0, [r0, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209B0B8
	cmp r6, #0x0
	bne _0209B0B8
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r5
	cmp r0, #0xf
	blt _0209AF38
_0209B0B8:
	mov r0, r6
	add sp, sp, #0x4c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209B0C8: .word 0x00001001
_0209B0CC: .word 0x021C8EFC

	arm_func_start FUN_0209B0D0
FUN_0209B0D0:
	ldrb r2, [r0], #0x1
	cmp r2, #0x0
	bxeq lr
_0209B0DC:
	and r1, r2, #0xc0
	cmp r1, #0xc0
	addeq r0, r0, #0x1
	bxeq lr
	add r0, r0, r2
	ldrb r2, [r0], #0x1
	cmp r2, #0x0
	bne _0209B0DC
	bx lr

	arm_func_start FUN_0209B100
FUN_0209B100: ; 0x0209B100
	stmdb sp!, {r4,lr}
	bl FUN_0209CB44
	bl FUN_0209CBE8
	ldr r1, _0209B168 ; =0x021C8ED4
	mov r0, #0x44
	ldr r2, [r1, #0x0]
	mov r1, #0x43
	bl FUN_0209CB78
	ldr r4, _0209B16C ; =0x021C924A
	mov r1, #0x7
	mov r0, r4
	mov r2, #0x0
	bl FUN_0209B8E0
	mov r1, #0xff
	add r2, r0, #0x1
	strb r1, [r0, #0x0]
	mov r0, #0x0
	mov r1, #0x12c
	sub r3, r2, r4
	bl FUN_0209B8A0
	sub r1, r0, r4
	mov r0, r4
	bl FUN_0209C030
	bl FUN_0209CB24
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209B168: .word 0x021C8ED4
_0209B16C: .word 0x021C924A

	arm_func_start FUN_0209B170
FUN_0209B170:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	bl FUN_0209CB44
	bl FUN_0209CBE8
	cmp r4, #0x1
	bne _0209B1A8
	ldr r1, _0209B28C ; =0x021C8ED4
	mov r0, #0x44
	ldr r2, [r1, #0x0]
	mov r1, #0x43
	bl FUN_0209CB78
	b _0209B1B8
_0209B1A8:
	mov r0, #0x44
	mov r1, #0x43
	mvn r2, #0x0
	bl FUN_0209CB78
_0209B1B8:
	mov r6, #0x0
_0209B1BC:
	mov r0, r4
	bl FUN_0209B6BC
	mov r1, r6
	bl FUN_0209B2FC
	movs r7, r0
	bne _0209B1E0
	add r6, r6, #0x1
	cmp r6, #0x4
	blt _0209B1BC
_0209B1E0:
	bl FUN_0209CB24
	cmp r7, #0x2
	bne _0209B224
	ldr r0, _0209B290 ; =0x021C8F00
	mov r1, #0x3
	ldr r3, [r0, #0x0]
	ldr r2, _0209B294 ; =0x021C8EEC
	mov r3, r3, lsr #0x1
	str r3, [r5, #0x0]
	ldr r3, [r0, #0x0]
	add sp, sp, #0x4
	mul r1, r3, r1
	mov r1, r1, lsr #0x3
	str r1, [r2, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209B224:
	ldr r1, _0209B294 ; =0x021C8EEC
	cmp r4, #0x1
	ldr r0, [r1, #0x0]
	mov r0, r0, lsr #0x1
	str r0, [r1, #0x0]
	str r0, [r5, #0x0]
	beq _0209B24C
	cmp r4, #0x2
	beq _0209B270
	b _0209B27C
_0209B24C:
	cmp r0, #0x3c
	bhs _0209B27C
	mov r2, #0x1
	ldr r0, _0209B290 ; =0x021C8F00
	str r2, [r5, #0x0]
	ldr r0, [r0, #0x0]
	mov r0, r0, lsr #0x3
	str r0, [r1, #0x0]
	b _0209B27C
_0209B270:
	cmp r0, #0x3c
	movcc r0, #0x1
	strcc r0, [r5, #0x0]
_0209B27C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209B28C: .word 0x021C8ED4
_0209B290: .word 0x021C8F00
_0209B294: .word 0x021C8EEC

	arm_func_start FUN_0209B298
FUN_0209B298:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl FUN_0209CB44
	bl FUN_0209CBE8
	mov r0, #0x44
	mov r1, #0x43
	mvn r2, #0x0
	bl FUN_0209CB78
	mov r4, #0x0
_0209B2BC:
	bl FUN_0209B7D8
	mov r1, r4
	bl FUN_0209B2FC
	mov r5, r0
	cmp r5, #0x1
	beq _0209B2E0
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _0209B2BC
_0209B2E0:
	bl FUN_0209CB24
	cmp r5, #0x1
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209B2FC
FUN_0209B2FC: ; 0x0209B2FC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	add r2, r1, #0x1
	mov r1, #0xf
	mul r1, r2, r1
	str r1, [sp, #0x8]
	str r0, [sp, #0x0]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	str r0, [sp, #0x4]
	orr r0, r0, r1, lsl #0x10
	mov r4, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x3
	mov r9, r4
	ldr r5, _0209B698 ; =0x021C8F1C
	mov r7, #0x2
	mov r8, #0x1
	ldr fp, _0209B69C ; =0x021C8EE0
	ldr r6, _0209B6A0 ; =0x021C8ED0
	str r0, [sp, #0xc]
	b _0209B64C
_0209B354:
	bl FUN_0209BF9C
_0209B358: ; 0x0209B358
	cmp r0, #0x0
	bne _0209B368
	bl FUN_020A005C
	b _0209B64C
_0209B368:
	add r0, sp, #0x10
	bl FUN_0209C638
	mov r10, r0
	ldr r0, [sp, #0x10]
	cmp r0, #0xf0
	bls _0209B644
	ldrb r0, [r10, #0x0]
	cmp r0, #0x2
	bne _0209B644
	ldrh r1, [r10, #0x6]
	ldrh r2, [r10, #0x4]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r1, r0, lsl #0x10
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	orr r1, r0, r1, lsr #0x10
	ldr r0, [sp, #0x0]
	cmp r0, r1
	bne _0209B644
	ldr r1, _0209B6A4 ; =0x021C8F14
	add r0, r10, #0x1c
	bl FUN_0209F9A0
_0209B3D0: ; 0x0209B3D0
	cmp r0, #0x0
	bne _0209B644
	ldrb r3, [r10, #0x10]
	ldrb r0, [r10, #0x11]
	ldrb r2, [r10, #0x12]
	ldrb r1, [r10, #0x13]
	orr r0, r0, r3, lsl #0x8
	mov r0, r0, lsl #0x10
	orr r1, r1, r2, lsl #0x8
	mov r0, r0, lsr #0x10
	mov r2, r0, lsl #0x10
	mov r0, r1, lsl #0x10
	orr r0, r2, r0, lsr #0x10
	ldrb r2, [r10, #0xec]
	ldr r1, [sp, #0x10]
	ldr r4, [sp, #0xc]
	add r1, r10, r1
	cmp r2, #0x63
	bne _0209B644
	ldrb r2, [r10, #0xed]
	cmp r2, #0x82
	bne _0209B644
	ldrb r2, [r10, #0xee]
	cmp r2, #0x53
	bne _0209B644
	add r2, r10, #0xf0
	ldrb r3, [r10, #0xef]
	cmp r3, #0x63
	bne _0209B644
	b _0209B630
_0209B448:
	cmp r3, #0x0
	beq _0209B630
	cmp r3, #0x33
	bgt _0209B48C
	cmp r3, #0x33
	bge _0209B588
	cmp r3, #0x6
	bgt _0209B624
	cmp r3, #0x1
	blt _0209B624
	cmp r3, #0x1
	beq _0209B4AC
	cmp r3, #0x3
	beq _0209B4E0
	cmp r3, #0x6
	beq _0209B514
	b _0209B624
_0209B48C:
	cmp r3, #0x35
	bgt _0209B4A0
	cmp r3, #0x35
	beq _0209B5C0
	b _0209B624
_0209B4A0:
	cmp r3, #0x36
	beq _0209B5F0
	b _0209B624
_0209B4AC:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r6, #0x0]
	b _0209B624
_0209B4E0:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r11, #0x0]
	b _0209B624
_0209B514:
	ldrb r3, [r2, #0x0]
	cmp r3, #0x8
	strcc r9, [r5, #0x4]
	blo _0209B554
	ldrb lr, [r2, #0x5]
	ldrb r12, [r2, #0x6]
	ldrb r10, [r2, #0x7]
	ldrb r3, [r2, #0x8]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r5, #0x4]
_0209B554:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r5, #0x0]
	b _0209B624
_0209B588:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r10, r10, r3, lsr #0x10
	ldr r3, _0209B6A8 ; =0x021C8F00
	str r10, [r3, #0x0]
	b _0209B624
_0209B5C0:
	ldrb r3, [r2, #0x1]
	cmp r3, #0x2
	beq _0209B5E0
	cmp r3, #0x5
	ldreq r3, _0209B6AC ; =0x021C8F04
	moveq r4, r7
	streq r0, [r3, #0x0]
	b _0209B624
_0209B5E0:
	ldr r3, _0209B6B0 ; =0x021C8EE8
	mov r4, r8
	str r0, [r3, #0x0]
	b _0209B624
_0209B5F0:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r10, r10, r3, lsr #0x10
	ldr r3, _0209B6B4 ; =0x021C8ED4
	str r10, [r3, #0x0]
_0209B624:
	ldrb r3, [r2, #0x0]
	add r3, r3, #0x1
	add r2, r2, r3
_0209B630:
	cmp r2, r1
	bhs _0209B644
	ldrb r3, [r2], #0x1
	cmp r3, #0xff
	bne _0209B448
_0209B644:
	ldr r0, [sp, #0x10]
	bl FUN_0209C52C
_0209B64C:
	ldr r0, _0209B6B8 ; =0x021C8EFC
	ldr r0, [r0, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209B688
	cmp r4, #0x0
	bne _0209B688
	bl OS_GetTick
	mov r2, r0, lsr #0x10
	ldr r0, [sp, #0x4]
	orr r2, r2, r1, lsl #0x10
	sub r1, r2, r0
	ldr r0, [sp, #0x8]
	cmp r1, r0
	blt _0209B354
_0209B688:
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209B698: .word 0x021C8F1C
_0209B69C: .word 0x021C8EE0
_0209B6A0: .word 0x021C8ED0
_0209B6A4: .word 0x021C8F14
_0209B6A8: .word 0x021C8F00
_0209B6AC: .word 0x021C8F04
_0209B6B0: .word 0x021C8EE8
_0209B6B4: .word 0x021C8ED4
_0209B6B8: .word 0x021C8EFC

	arm_func_start FUN_0209B6BC
FUN_0209B6BC: ; 0x0209B6BC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, _0209B7CC ; =0x021C924A
	mov r5, r0
	add r2, sp, #0x0
	mov r0, r4
	mov r1, #0x3
	bl FUN_0209B8E0
	mov r12, r0
	cmp r5, #0x0
	bne _0209B790
	mov r0, #0x32
	strb r0, [r12, #0x0]
	mov r0, #0x4
	ldr r3, _0209B7D0 ; =0x021C8EE8
	strb r0, [r12, #0x1]
	ldr r1, [r3, #0x0]
	mov lr, #0x36
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #0x8
	strb r1, [r12, #0x2]
	ldr r1, [r3, #0x0]
	ldr r2, _0209B7D4 ; =0x021C8ED4
	mov r1, r1, lsr #0x10
	strb r1, [r12, #0x3]
	ldr r1, [r3, #0x0]
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #0x8
	strb r1, [r12, #0x4]
	ldr r1, [r3, #0x0]
	strb r1, [r12, #0x5]
	strb lr, [r12, #0x6]
	strb r0, [r12, #0x7]
	ldr r0, [r2, #0x0]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0x8]
	ldr r0, [r2, #0x0]
	mov r0, r0, lsr #0x10
	strb r0, [r12, #0x9]
	ldr r0, [r2, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0xa]
	ldr r0, [r2, #0x0]
	strb r0, [r12, #0xb]
	add r12, r12, #0xc
_0209B790:
	add r2, r12, #0x1
	mov lr, #0xff
	sub r3, r2, r4
	mov r0, #0x0
	mov r1, #0x12c
	strb lr, [r12, #0x0]
	bl FUN_0209B8A0
	mov r1, r0
	mov r0, r4
	sub r1, r1, r4
	bl FUN_0209C030
_0209B7BC: ; 0x0209B7BC
	ldr r0, [sp, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209B7CC: .word 0x021C924A
_0209B7D0: .word 0x021C8EE8
_0209B7D4: .word 0x021C8ED4

	arm_func_start FUN_0209B7D8
FUN_0209B7D8: ; 0x0209B7D8
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r4, _0209B898 ; =0x021C924A
	add r2, sp, #0x0
	mov r0, r4
	mov r1, #0x1
	bl FUN_0209B8E0
	ldr r1, _0209B89C ; =0x021C8EE8
	mov r12, r0
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0209B85C
	mov r0, #0x32
	strb r0, [r12, #0x0]
	mov r0, #0x4
	strb r0, [r12, #0x1]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0x2]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsr #0x10
	strb r0, [r12, #0x3]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0x4]
	ldr r0, [r1, #0x0]
	strb r0, [r12, #0x5]
	add r12, r12, #0x6
_0209B85C:
	add r2, r12, #0x1
	mov lr, #0xff
	sub r3, r2, r4
	mov r0, #0x0
	mov r1, #0x12c
	strb lr, [r12, #0x0]
	bl FUN_0209B8A0
	mov r1, r0
	mov r0, r4
	sub r1, r1, r4
	bl FUN_0209C030
_0209B888: ; 0x0209B888
	ldr r0, [sp, #0x0]
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209B898: .word 0x021C924A
_0209B89C: .word 0x021C8EE8

	arm_func_start FUN_0209B8A0
FUN_0209B8A0: ; 0x0209B8A0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r12, r0
	mov r5, r2
	cmp r3, r1
	bhs _0209B8D0
	sub r4, r1, r3
	mov r0, r5
	mov r1, r12
	mov r2, r4
	bl MI_CpuFill8
	add r5, r5, r4
_0209B8D0:
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209B8E0
FUN_0209B8E0: ; 0x0209B8E0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	mov r4, r2
	mov r1, #0x0
	mov r2, #0xec
	mov r6, r0
	bl MI_CpuFill8
	ldr r0, _0209BA5C ; =0x00000101
	mov r1, #0x6
	strh r0, [r6, #0x0]
	ldr r0, _0209BA60 ; =0x021C8F24
	strb r1, [r6, #0x2]
	ldr r3, [r0, #0x8]
	ldr r2, [r0, #0x0]
	ldr r1, [r0, #0x4]
	umull lr, r12, r3, r2
	mla r12, r3, r1, r12
	ldr r1, [r0, #0xc]
	ldr r7, [r0, #0x10]
	mla r12, r1, r2, r12
	adds r3, r7, lr
	ldr r1, [r0, #0x14]
	str r3, [r0, #0x0]
	adc r1, r1, r12
	str r1, [r0, #0x4]
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	cmp r4, #0x0
	mov r2, r3, asr #0x8
	mov r0, r1, lsl #0x10
	strne r1, [r4, #0x0]
	mov r1, r0, lsr #0x10
	orr r2, r2, r3, lsl #0x8
	mov r0, r1, asr #0x8
	strh r2, [r6, #0x4]
	orr r0, r0, r1, lsl #0x8
	strh r0, [r6, #0x6]
	ldr r2, _0209BA64 ; =0x021C8F04
	ldr r0, _0209BA68 ; =0x021C8F14
	ldr r1, [r2, #0x0]
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	mov r1, r3, asr #0x8
	orr r1, r1, r3, lsl #0x8
	strh r1, [r6, #0xc]
	ldr r2, [r2, #0x0]
	add r1, r6, #0x1c
	mov r2, r2, lsl #0x10
	mov r3, r2, lsr #0x10
	mov r2, r3, asr #0x8
	orr r3, r2, r3, lsl #0x8
	mov r2, #0x6
	strh r3, [r6, #0xe]
	bl MI_CpuCopy8
	ldr r0, _0209BA6C ; =0x00008263
	ldr r1, _0209BA70 ; =0x00006353
	strh r0, [r6, #0xec]
	strh r1, [r6, #0xee]
	ldr r0, _0209BA74 ; =0x00000135
	mov r1, #0x7
	strh r0, [r6, #0xf0]
	strb r5, [r6, #0xf2]
	mov r0, #0x3d
	strb r0, [r6, #0xf3]
	strb r1, [r6, #0xf4]
	mov r3, #0x1
	ldr r0, _0209BA68 ; =0x021C8F14
	add r1, r6, #0xf6
	mov r2, #0x6
	strb r3, [r6, #0xf5]
	bl MI_CpuCopy8
	mov r1, #0xc
	strb r1, [r6, #0xfc]
	mov r2, #0xa
	ldr r0, _0209BA78 ; =0x02106224
	add r1, r6, #0xfe
	strb r2, [r6, #0xfd]
	bl MI_CpuCopy8
	mov r1, #0x37
	strb r1, [r6, #0x108]
	mov r2, #0x3
	ldr r0, _0209BA7C ; =0x0000010D
	strb r2, [r6, #0x109]
	mov r1, #0x1
	strb r1, [r6, #0x10a]
	strb r2, [r6, #0x10b]
	mov r1, #0x6
	strb r1, [r6, #0x10c]
	add r0, r6, r0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209BA5C: .word 0x00000101
_0209BA60: .word 0x021C8F24
_0209BA64: .word 0x021C8F04
_0209BA68: .word 0x021C8F14
_0209BA6C: .word 0x00008263
_0209BA70: .word 0x00006353
_0209BA74: .word 0x00000135
_0209BA78: .word 0x02106224
_0209BA7C: .word 0x0000010D

	arm_func_start FUN_0209BA80
FUN_0209BA80: ; 0x0209BA80
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x54
	ldr r3, _0209BE40 ; =0x021C8EF8
	mov r1, #0x0
	ldr r0, _0209BE44 ; =0x021C8FD8
	mov r2, #0x64
	str r1, [r3, #0x0]
	bl MI_CpuFill8
	ldr r0, _0209BE44 ; =0x021C8FD8
	mov r3, #0x180
	ldr r2, _0209BE48 ; =0x021C93A0
	ldr r1, _0209BE4C ; =0x021C9220
	str r3, [r0, #0x3c]
	str r2, [r0, #0x40]
	str r3, [r0, #0x48]
	str r1, [r0, #0x4c]
	bl FUN_0209CC28
	mov r11, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x4c]
	mov r1, r0
	ldr r0, _0209BE50 ; =0x021C8EC0
	ldr r5, [sp, #0x0]
	str r1, [r0, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x10]
	mov r0, r5
	str r0, [sp, #0x34]
	str r0, [sp, #0x3c]
	mov r0, #0x3
	str r0, [sp, #0x1c]
	mov r0, r5
	str r0, [sp, #0x30]
	str r0, [sp, #0x28]
	str r0, [sp, #0x24]
	str r0, [sp, #0x20]
	str r0, [sp, #0xc]
	mov r0, #0x69
	str r0, [sp, #0x44]
	mov r0, #0x3e8
	mov r6, r11
	mov r4, r11
	mov r10, r11
	str r11, [sp, #0x14]
	str r11, [sp, #0x18]
	str r11, [sp, #0x38]
	str r11, [sp, #0x2c]
	str r11, [sp, #0x40]
	str r11, [sp, #0x48]
	str r0, [sp, #0x8]
_0209BB50:
	ldr r0, [sp, #0x8]
	bl OS_Sleep
	ldr r0, _0209BE40 ; =0x021C8EF8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0209BE14
	bl OS_GetTick
	mov r9, r0, lsr #0x10
	ldr r0, _0209BE54 ; =0x021C8EFC
	orr r9, r9, r1, lsl #0x10
	ldr r0, [r0, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209BC8C
	ldr r0, [sp, #0x4c]
	subs r0, r0, #0x1
	str r0, [sp, #0x4c]
	bne _0209BCA4
	ldr r0, _0209BE58 ; =0x021C8EC4
	ldr r0, [r0, #0x0]
	ands r0, r0, #0x1
	beq _0209BBBC
	cmp r11, #0x0
	bne _0209BCA4
	bl FUN_0209BE78
	ldr r11, [sp, #0xc]
	b _0209BCA4
_0209BBBC:
	cmp r11, #0x3
	addls pc, pc, r11, lsl #0x2
	b _0209BCA4
_0209BBC8:
	b _0209BBD8
_0209BBCC:
	b _0209BC28
_0209BBD0:
	b _0209BC4C
_0209BBD4:
	b _0209BCA4
_0209BBD8:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrne r1, [sp, #0x10]
	ldrne r0, _0209BE50 ; =0x021C8EC0
	strne r1, [r0, #0x0]
	ldrne r0, [sp, #0x14]
	strne r0, [sp, #0x4]
	bl FUN_0209B298
_0209BBF8: ; 0x0209BBF8
	cmp r0, #0x0
	beq _0209BC14
	ldr r1, [sp, #0x18]
	add r0, sp, #0x4c
	bl FUN_0209B170
_0209BC0C: ; 0x0209BC0C
	cmp r0, #0x0
	bne _0209BC20
_0209BC14:
	bl FUN_0209BE78
	ldr r11, [sp, #0x1c]
	b _0209BCA4
_0209BC20:
	ldr r11, [sp, #0x20]
	b _0209BCA4
_0209BC28:
	ldr r1, [sp, #0x24]
	add r0, sp, #0x4c
	bl FUN_0209B170
_0209BC34: ; 0x0209BC34
	cmp r0, #0x0
	bne _0209BCA4
	ldr r0, [sp, #0x4c]
	cmp r0, #0x3c
	ldrcc r11, [sp, #0x10]
	b _0209BCA4
_0209BC4C:
	ldr r1, [sp, #0x10]
	add r0, sp, #0x4c
	bl FUN_0209B170
_0209BC58: ; 0x0209BC58
	cmp r0, #0x0
	ldrne r11, [sp, #0x28]
	bne _0209BCA4
	ldr r0, [sp, #0x4c]
	cmp r0, #0x3c
	bhs _0209BCA4
	ldr r0, [sp, #0x1c]
	bl FUN_020A0098
	ldr r0, [sp, #0x30]
	ldr r11, [sp, #0x2c]
	str r0, [sp, #0x4c]
	str r0, [sp, #0x0]
	b _0209BCA4
_0209BC8C:
	ldr r0, [sp, #0x34]
	bl FUN_020A0098
	ldr r0, [sp, #0x3c]
	ldr r11, [sp, #0x38]
	str r0, [sp, #0x4c]
	str r0, [sp, #0x0]
_0209BCA4:
	ldr r1, [sp, #0x40]
	ldr r0, _0209BE5C ; =0x021C8F78
_0209BCAC:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _0209BCD4
	ldrh r2, [r0, #0xa]
	sub r2, r9, r2
	mov r2, r2, lsl #0x10
	mov r3, r2, asr #0x10
	ldr r2, _0209BE60 ; =0x000003BD
	cmp r3, r2
	strgt r6, [r0, #0x0]
_0209BCD4:
	add r0, r0, #0xc
	add r1, r1, #0x1
	cmp r1, #0x8
	blt _0209BCAC
	ldr r0, _0209BE64 ; =0x021C8EE0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209BD10
	ldr r1, [sp, #0x0]
	subs r1, r1, #0x1
	str r1, [sp, #0x0]
	bne _0209BD10
	bl FUN_0209F338
	ldr r0, [sp, #0x44]
	str r0, [sp, #0x0]
_0209BD10:
	ldr r0, _0209BE68 ; =0x021D3498
	ldr r7, [r0, #0x8]
	cmp r7, #0x0
	beq _0209BDAC
_0209BD20:
	ldr r0, [r7, #0xa4]
	cmp r0, #0x0
	beq _0209BDA0
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0209BDA0
	ldrb r2, [r0, #0x8]
	cmp r2, #0x3
	bne _0209BD6C
	ldr r1, [r0, #0x10]
	sub r1, r9, r1
	cmp r1, #0x27
	ble _0209BD6C
	strb r5, [r0, #0x8]
	ldrh r1, [r0, #0x1a]
	strh r1, [r0, #0x18]
	ldr r1, [r0, #0x20]
	str r1, [r0, #0x1c]
	b _0209BDA0
_0209BD6C:
	cmp r2, #0x2
	bne _0209BDA0
	ldr r1, [r0, #0x10]
	sub r1, r9, r1
	cmp r1, #0x27
	ble _0209BDA0
	ldr r1, [r0, #0x4]
	cmp r1, #0x1
	bne _0209BDA0
	strb r4, [r0, #0x8]
	str r4, [r0, #0x4]
	ldr r0, [r0, #0x0]
	bl OS_WakeupThreadDirect
_0209BDA0:
	ldr r7, [r7, #0x68]
	cmp r7, #0x0
	bne _0209BD20
_0209BDAC:
	ldr r7, [sp, #0x48]
	ldr r8, _0209BE6C ; =0x021C9520
_0209BDB4:
	ldrh r0, [r8, #0x4]
	cmp r0, #0x0
	beq _0209BDE4
	ldr r0, [r8, #0x2c]
	sub r0, r9, r0
	cmp r0, #0xef
	ble _0209BDE4
	ldr r1, _0209BE70 ; =0x021C8EF4
	ldr r0, [r8, #0x34]
	ldr r1, [r1, #0x0]
	blx r1
	strh r10, [r8, #0x4]
_0209BDE4:
	add r8, r8, #0x38
	add r7, r7, #0x1
	cmp r7, #0x8
	blt _0209BDB4
	mov r0, r9
	bl FUN_020A01FC
	ldr r0, _0209BE74 ; =0x021C8EF0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209BB50
	blx r0
	b _0209BB50
_0209BE14:
	ldr r0, _0209BE58 ; =0x021C8EC4
	ldr r0, [r0, #0x0]
	ands r0, r0, #0x1
	bne _0209BE30
	cmp r11, #0x3
	beq _0209BE30
	bl FUN_0209B100
_0209BE30:
	bl FUN_0209CC10
	add sp, sp, #0x54
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209BE40: .word 0x021C8EF8
_0209BE44: .word 0x021C8FD8
_0209BE48: .word 0x021C93A0
_0209BE4C: .word 0x021C9220
_0209BE50: .word 0x021C8EC0
_0209BE54: .word 0x021C8EFC
_0209BE58: .word 0x021C8EC4
_0209BE5C: .word 0x021C8F78
_0209BE60: .word 0x000003BD
_0209BE64: .word 0x021C8EE0
_0209BE68: .word 0x021D3498
_0209BE6C: .word 0x021C9520
_0209BE70: .word 0x021C8EF4
_0209BE74: .word 0x021C8EF0

	arm_func_start FUN_0209BE78
FUN_0209BE78: ; 0x0209BE78
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r0, _0209BF3C ; =0x021C8ECC
	ldr r0, [r0, #0x0]
	blx r0
	ldr r0, _0209BF40 ; =0x021C8F04
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	bl FUN_0209F338
	mov r0, #0x64
	bl OS_Sleep
	ldr r0, _0209BF40 ; =0x021C8F04
	ldr r0, [r0, #0x0]
	bl FUN_0209F338
	bl OS_GetTick
	mov r4, r0, lsr #0x10
	orr r4, r4, r1, lsl #0x10
	ldr r6, _0209BF44 ; =0x021C8EAC
	mov r7, #0x64
	ldr r5, _0209BF48 ; =0x021C8EFC
	b _0209BF00
_0209BED8:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x0
	beq _0209BEF8
	mov r0, #0x4
	bl FUN_020A0098
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209BEF8:
	mov r0, r7
	bl OS_Sleep
_0209BF00:
	ldr r0, [r5, #0x0]
	blx r0
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r4
	cmp r0, #0x17
	blt _0209BED8
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209BF3C: .word 0x021C8ECC
_0209BF40: .word 0x021C8F04
_0209BF44: .word 0x021C8EAC
_0209BF48: .word 0x021C8EFC

	arm_func_start FUN_0209BF4C
FUN_0209BF4C: ; 0x0209BF4C
	stmdb sp!, {r4,lr}
	ldr r0, _0209BF98 ; =0x021D3498
	ldr r0, [r0, #0x4]
	ldr r4, [r0, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r4, #0x60]
	cmp r1, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r2, #0x0
	ldr r0, [r4, #0x5c]
	mov r3, r2
	bl FUN_0209C0E8
_0209BF88: ; 0x0209BF88
	mov r0, #0x0
	str r0, [r4, #0x60]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209BF98: .word 0x021D3498

	arm_func_start FUN_0209BF9C
FUN_0209BF9C:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _0209C02C ; =0x021D3498
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xa4]
	cmp r0, #0x0
	beq _0209C01C
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _0209BFD4
	bl FUN_020A0538
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209BFD4:
	ldr r1, [r0, #0x44]
	cmp r1, #0x0
	bne _0209BFFC
	ldrb r0, [r0, #0x8]
	cmp r0, #0x4
	beq _0209BFFC
	add r0, r0, #0xf6
	and r0, r0, #0xff
	cmp r0, #0x1
	bhi _0209C00C
_0209BFFC:
	add sp, sp, #0x4
	mov r0, r1
	ldmia sp!, {lr}
	bx lr
_0209C00C:
	add sp, sp, #0x4
	mvn r0, #0x0
	ldmia sp!, {lr}
	bx lr
_0209C01C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C02C: .word 0x021D3498

	arm_func_start FUN_0209C030
FUN_0209C030:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r3, _0209C0E4 ; =0x021D3498
	mov r2, r0
	ldr r4, [r3, #0x4]
	mov r3, r1
	ldr r5, [r4, #0xa4]
	cmp r5, #0x0
	beq _0209C0D4
	ldr r4, [r5, #0x60]
	cmp r4, #0x0
	beq _0209C0BC
	ldr r0, [r5, #0x5c]
	mov r1, r4
	bl FUN_0209C0E8
	ldr r1, [r5, #0x60]
	mov r4, r0
	cmp r4, r1
	movcs r0, #0x0
	strcs r0, [r5, #0x60]
	addcs sp, sp, #0x4
	subcs r0, r4, r1
	ldmcsia sp!, {r4-r5,lr}
	bxcs lr
	ldr r0, [r5, #0x5c]
	sub r2, r1, r4
	add r1, r0, r4
	bl memmove
	ldr r1, [r5, #0x60]
	add sp, sp, #0x4
	sub r1, r1, r4
	mov r0, #0x0
	str r1, [r5, #0x60]
	ldmia sp!, {r4-r5,lr}
	bx lr
_0209C0BC:
	mov r2, #0x0
	mov r3, r2
	bl FUN_0209C0E8
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_0209C0D4:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209C0E4: .word 0x021D3498

	arm_func_start FUN_0209C0E8
FUN_0209C0E8:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr ip, _0209C1CC ; =0x021D3498
	mov r7, r1
	ldr r12, [r12, #0x4]
	mov r6, r2
	ldr r4, [r12, #0xa4]
	mov r5, r3
	cmp r4, #0x0
	beq _0209C1BC
	ldrb r12, [r4, #0x8]
	cmp r12, #0xa
	bne _0209C14C
	cmp r7, #0x0
	beq _0209C12C
	mov r2, r4
	bl FUN_0209EB00
_0209C12C:
	cmp r5, #0x0
	beq _0209C144
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209EB00
_0209C144:
	add r0, r7, r5
	b _0209C1A4
_0209C14C:
	cmp r12, #0xb
	bne _0209C184
	cmp r7, #0x0
	beq _0209C164
	mov r2, r4
	bl FUN_0209EC40
_0209C164:
	cmp r5, #0x0
	beq _0209C17C
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209EC40
_0209C17C:
	add r0, r7, r5
	b _0209C1A4
_0209C184:
	ldrb r12, [r4, #0x9]
	cmp r12, #0x0
	beq _0209C19C
	str r4, [sp, #0x0]
	bl FUN_020A03E0
	b _0209C1A4
_0209C19C:
	str r4, [sp, #0x0]
	bl FUN_0209C1D4
_0209C1A4:
	ldr r1, _0209C1D0 ; =0x021C8EA8
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
_0209C1BC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209C1CC: .word 0x021D3498
_0209C1D0: .word 0x021C8EA8

	arm_func_start FUN_0209C1D4
FUN_0209C1D4:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	mov r4, #0x0
	mov r10, r0
	ldr r8, [sp, #0x40]
	mov r0, r4
	str r4, [sp, #0xc]
	mov r9, r1
	mov r11, r2
	str r3, [sp, #0x8]
	mov r6, r4
	str r0, [r8, #0x34]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	str r0, [sp, #0x10]
	orr r0, r0, r1, lsl #0x10
	str r0, [sp, #0x10]
	mov r0, r6
	str r0, [sp, #0x18]
	mov r0, #0x1
	ldr r4, _0209C3EC ; =0x021C8EFC
	str r0, [sp, #0x14]
	b _0209C39C
_0209C230:
	ldr r7, [r8, #0x28]
	ldr r3, [sp, #0x8]
	str r8, [sp, #0x0]
	mov r0, r10
	mov r1, r9
	mov r2, r11
	str r6, [sp, #0x4]
	bl FUN_0209C3F0
	bl OS_GetTick
	mov r5, r0, lsr #0x10
	orr r5, r5, r1, lsl #0x10
_0209C25C:
	bl FUN_020A005C
_0209C260: ; 0x0209C260
	ldr r0, [r4, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C2B8
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	bne _0209C2B8
	ldr r1, [r8, #0x28]
	ldr r0, [r8, #0x30]
	cmp r1, r0
	beq _0209C2B8
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r5
	cmp r0, #0xf
	bge _0209C2B8
	cmp r6, #0x0
	beq _0209C25C
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	beq _0209C25C
_0209C2B8:
	ldr r0, [r8, #0x30]
	subs r7, r0, r7
	ldr r0, [sp, #0xc]
	add r0, r0, r7
	str r0, [sp, #0xc]
	beq _0209C2E4
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	str r0, [sp, #0x10]
	orr r0, r0, r1, lsl #0x10
	str r0, [sp, #0x10]
_0209C2E4:
	ldr r0, [r8, #0x30]
	str r0, [r8, #0x28]
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	bne _0209C36C
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	bne _0209C36C
	cmp r7, #0x0
	bne _0209C36C
	cmp r6, #0x0
	bne _0209C370
	bl OS_GetTick
	mov r5, r0, lsr #0x10
	orr r5, r5, r1, lsl #0x10
	b _0209C334
_0209C324:
	bl FUN_020A005C
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	bne _0209C35C
_0209C334:
	ldr r0, [r4, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C35C
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r5
	cmp r0, #0xf
	blt _0209C324
_0209C35C:
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	ldreq r6, [sp, #0x14]
	b _0209C370
_0209C36C:
	ldr r6, [sp, #0x18]
_0209C370:
	cmp r7, r9
	addcc r10, r10, r7
	subcc r9, r9, r7
	blo _0209C39C
	sub r1, r7, r9
	add r10, r11, r1
	ldr r0, [sp, #0x8]
	ldr r11, [sp, #0x18]
	sub r9, r0, r1
	mov r0, r11
	str r0, [sp, #0x8]
_0209C39C:
	ldr r0, [r4, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C3DC
	cmp r9, #0x0
	beq _0209C3DC
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	bne _0209C3DC
	bl OS_GetTick
	mov r2, r0, lsr #0x10
	ldr r0, [sp, #0x10]
	orr r2, r2, r1, lsl #0x10
	sub r0, r2, r0
	cmp r0, #0x9f
	blt _0209C230
_0209C3DC:
	ldr r0, [sp, #0xc]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209C3EC: .word 0x021C8EFC

	arm_func_start FUN_0209C3F0
FUN_0209C3F0: ; 0x0209C3F0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r2
	mov r4, r3
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	bl FUN_0209C44C
_0209C40C: ; 0x0209C40C
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [sp, #0x10]
	mov r0, r5
	mov r1, r4
	mov r3, #0x0
	bl FUN_0209C44C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209C44C
FUN_0209C44C:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r8, r2
	ldr r11, [r8, #0x34]
	mov r10, r0
	movs r0, r3
	mov r0, r11, lsl #0x1
	movne r6, #0x1
	add r5, r0, #0x4
	mov r0, #0x18
	str r3, [sp, #0x4]
	mov r9, r1
	ldreqh r6, [r8, #0x2c]
	mov r4, #0x0
	str r0, [sp, #0x8]
	b _0209C504
_0209C48C:
	ldr r0, _0209C528 ; =0x021C8EB0
	ldrh r7, [r8, #0x2e]
	ldrh r0, [r0, #0x0]
	ldr r1, [r8, #0x34]
	cmp r7, r6
	movcs r7, r6
	cmp r0, r7
	movcc r7, r0
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	biceq r7, r7, #0x1
	cmp r9, r7
	sub r0, r1, r11
	movcc r7, r9
	adds r0, r5, r0
	moveq r7, r4
	mov r11, r1
	sub r5, r0, #0x1
	cmp r7, #0x0
	beq _0209C518
	ldr r3, [sp, #0x8]
	mov r0, r10
	mov r1, r7
	mov r2, r8
	str r4, [sp, #0x0]
	sub r6, r6, r7
	bl FUN_0209E878
	bl OS_YieldThread
	add r10, r10, r7
	sub r9, r9, r7
_0209C504:
	cmp r9, #0x0
	beq _0209C518
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	beq _0209C48C
_0209C518:
	mov r0, r7
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209C528: .word 0x021C8EB0

	arm_func_start FUN_0209C52C
FUN_0209C52C: ; 0x0209C52C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _0209C57C ; =0x021D3498
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldrb r2, [r1, #0x9]
	cmp r2, #0x0
	beq _0209C56C
	bl FUN_020A0738
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C56C:
	bl FUN_0209C580
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C57C: .word 0x021D3498

	arm_func_start FUN_0209C580
FUN_0209C580:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r7, r0
	bl OS_DisableInterrupts
	ldr r2, [r4, #0x44]
	ldr r1, [r4, #0x3c]
	mov r6, r0
	cmp r2, r1
	mov r5, #0x0
	bne _0209C5B4
	cmp r7, #0x0
	movne r5, #0x1
_0209C5B4:
	cmp r7, r2
	movcs r0, #0x0
	strcs r0, [r4, #0x44]
	bhs _0209C5D8
	ldr r0, [r4, #0x40]
	sub r2, r2, r7
	add r1, r0, r7
	str r2, [r4, #0x44]
	bl memmove
_0209C5D8:
	mov r0, r6
	bl OS_RestoreInterrupts
	ldrb r0, [r4, #0x8]
	cmp r0, #0xa
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r0, #0xb
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	beq _0209C620
	cmp r5, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
_0209C620:
	mov r0, r4
	mov r1, #0x1b
	bl FUN_0209DF84
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209C638
FUN_0209C638:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _0209C6BC ; =0x021D3498
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	cmp r1, #0x0
	beq _0209C6A4
	ldrb r2, [r1, #0x8]
	add r2, r2, #0xf6
	and r2, r2, #0xff
	cmp r2, #0x1
	bhi _0209C678
	bl FUN_0209C74C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C678:
	ldrb r2, [r1, #0x9]
	cmp r2, #0x0
	beq _0209C694
	bl FUN_020A0790
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C694:
	bl FUN_0209C6C0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C6A4:
	mov r1, #0x0
	str r1, [r0, #0x0]
	mov r0, r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C6BC: .word 0x021D3498

	arm_func_start FUN_0209C6C0
FUN_0209C6C0: ; 0x0209C6C0
	stmdb sp!, {r4-r8,lr}
	mov r4, r1
	ldr r1, [r4, #0x44]
	mov r5, r0
	cmp r1, #0x0
	bne _0209C728
	ldrb r0, [r4, #0x8]
	cmp r0, #0x4
	bne _0209C728
	bl OS_DisableInterrupts
	mov r8, r0
	mov r7, #0x2
	mov r6, #0x0
	b _0209C704
_0209C6F8:
	mov r0, r6
	str r7, [r4, #0x4]
	bl OS_SleepThread
_0209C704:
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	bne _0209C71C
	ldrb r0, [r4, #0x8]
	cmp r0, #0x4
	beq _0209C6F8
_0209C71C:
	mov r0, r8
	bl OS_RestoreInterrupts
_0209C724: ; 0x0209C724
	b _0209C72C
_0209C728:
	bl OS_YieldThread
_0209C72C:
	ldr r0, [r4, #0x44]
	str r0, [r5, #0x0]
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	ldrne r0, [r4, #0x40]
	moveq r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_0209C74C
FUN_0209C74C: ; 0x0209C74C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r1
	mov r9, r0
	bl OS_DisableInterrupts
	ldr r7, [r8, #0x44]
	mov r6, r0
	cmp r7, #0x0
	bne _0209C790
	mov r5, #0x3
	mov r4, #0x0
_0209C778:
	mov r0, r4
	str r5, [r8, #0x4]
	bl OS_SleepThread
	ldr r7, [r8, #0x44]
	cmp r7, #0x0
	beq _0209C778
_0209C790:
	mov r0, r6
	bl OS_RestoreInterrupts
	str r7, [r9, #0x0]
	ldr r0, [r8, #0x40]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_0209C7AC
FUN_0209C7AC: ; 0x0209C7AC
	stmdb sp!, {r4-r6,lr}
	ldr r0, _0209C838 ; =0x021D3498
	ldr r0, [r0, #0x4]
	ldr r4, [r0, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrb r0, [r4, #0x9]
	cmp r0, #0x0
	beq _0209C7DC
	mov r0, r4
	bl FUN_020A0320
_0209C7DC:
	bl OS_GetTick
	mov r6, r0, lsr #0x10
	orr r6, r6, r1, lsl #0x10
	ldr r5, _0209C83C ; =0x021C8EFC
	b _0209C7F4
_0209C7F0:
	bl FUN_020A005C
_0209C7F4:
	ldr r0, [r5, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C828
	ldrb r0, [r4, #0x8]
	cmp r0, #0x0
	beq _0209C828
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r6
	cmp r0, #0x27
	blt _0209C7F0
_0209C828:
	mov r0, #0x0
	strb r0, [r4, #0x8]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209C838: .word 0x021D3498
_0209C83C: .word 0x021C8EFC

	arm_func_start FUN_0209C840
FUN_0209C840:
	stmdb sp!, {r4,lr}
	ldr r0, _0209C880 ; =0x021D3498
	ldr r0, [r0, #0x4]
	ldr r4, [r0, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrb r0, [r4, #0x9]
	cmp r0, #0x0
	beq _0209C870
	mov r0, r4
	bl FUN_020A035C
_0209C870:
	mov r0, r4
	bl FUN_0209C884
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209C880: .word 0x021D3498

	arm_func_start FUN_0209C884
FUN_0209C884: ; 0x0209C884
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_YieldThread
	ldrb r1, [r4, #0x8]
	add r0, r1, #0xfd
	and r0, r0, #0xff
	cmp r0, #0x1
	bhi _0209C8C0
	mov r0, r4
	mov r1, #0x19
	bl FUN_0209DF70
	mov r0, #0x7
	strb r0, [r4, #0x8]
	ldmia sp!, {r4,lr}
	bx lr
_0209C8C0:
	cmp r1, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	mov r1, #0x1a
	bl FUN_0209DF84
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209C8E0
FUN_0209C8E0: ; 0x0209C8E0
	ldr r2, _0209C930 ; =0x021D3498
	ldr r2, [r2, #0x4]
	ldr r3, [r2, #0xa4]
	cmp r3, #0x0
	beq _0209C928
	ldrb r2, [r3, #0x8]
	cmp r2, #0x4
	beq _0209C908
	cmp r2, #0xa
	bne _0209C928
_0209C908:
	cmp r0, #0x0
	ldrneh r2, [r3, #0x18]
	strneh r2, [r0, #0x0]
	cmp r1, #0x0
	ldrne r0, [r3, #0x14]
	strne r0, [r1, #0x0]
	ldr r0, [r3, #0x1c]
	bx lr
_0209C928:
	mov r0, #0x0
	bx lr
	.balign 4
_0209C930: .word 0x021D3498

	arm_func_start FUN_0209C934
FUN_0209C934: ; 0x0209C934
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _0209C98C ; =0x021D3498
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xa4]
	cmp r0, #0x0
	beq _0209C97C
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _0209C96C
	bl FUN_020A0874
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C96C:
	bl FUN_0209C990
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C97C:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C98C: .word 0x021D3498

	arm_func_start FUN_0209C990
FUN_0209C990:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r10, r0
	bl FUN_0209CC3C
	mov r8, r0
	mov r9, #0x0
	mov r11, r9
	mov r4, #0x1
	mov r6, #0x2
	mov r5, #0x18
_0209C9B8:
	str r8, [r10, #0x28]
	strb r6, [r10, #0x8]
	bl OS_GetTick
	mov r2, r0, lsr #0x10
	orr r2, r2, r1, lsl #0x10
	str r2, [r10, #0x10]
	mov r0, r10
	mov r1, r6
	mov r2, r5
	bl FUN_0209DF98
	bl OS_DisableInterrupts
	mov r7, r0
	ldr r0, _0209CA50 ; =0x021C8F04
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209CA04
	mov r0, r11
	str r4, [r10, #0x4]
	bl OS_SleepThread
_0209CA04:
	mov r0, r7
	bl OS_RestoreInterrupts
	ldrb r0, [r10, #0x8]
	cmp r0, #0x4
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r0, _0209CA50 ; =0x021C8F04
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209CA40
	add r9, r9, #0x1
	cmp r9, #0x3
	blo _0209C9B8
_0209CA40:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209CA50: .word 0x021C8F04

	arm_func_start FUN_0209CA54
FUN_0209CA54: ; 0x0209CA54
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _0209CAA4 ; =0x021D3498
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xa4]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _0209CA94
	bl FUN_020A09CC
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209CA94:
	bl FUN_0209CAC4
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209CAA4: .word 0x021D3498

	arm_func_start FUN_0209CAA8
FUN_0209CAA8:
	ldr r1, _0209CAC0 ; =0x021D3498
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	cmp r1, #0x0
	strne r0, [r1, #0x38]
	bx lr
	.balign 4
_0209CAC0: .word 0x021D3498

	arm_func_start FUN_0209CAC4
FUN_0209CAC4: ; 0x0209CAC4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl FUN_0209CC3C
	str r0, [r5, #0x28]
	mov r0, #0x1
	strb r0, [r5, #0x8]
	bl OS_DisableInterrupts
	mov r4, r0
	mov r1, #0x1
	mov r0, #0x0
	str r1, [r5, #0x4]
	bl OS_SleepThread
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209CB0C
FUN_0209CB0C: ; 0x0209CB0C
	ldr r1, _0209CB20 ; =0x021D3498
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	str r1, [r0, #0xa4]
	bx lr
	.balign 4
_0209CB20: .word 0x021D3498

	arm_func_start FUN_0209CB24
FUN_0209CB24: ; 0x0209CB24
	ldr r0, _0209CB40 ; =0x021D3498
	ldr r0, [r0, #0x4]
	ldr r1, [r0, #0xa4]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x0]
	bx lr
	.balign 4
_0209CB40: .word 0x021D3498

	arm_func_start FUN_0209CB44
FUN_0209CB44: ; 0x0209CB44
	ldr r0, _0209CB74 ; =0x021D3498
	ldr r0, [r0, #0x4]
	ldr r1, [r0, #0xa4]
	cmp r1, #0x0
	bxeq lr
	str r0, [r1, #0x0]
	mov r0, #0x0
	strb r0, [r1, #0x8]
	str r0, [r1, #0x44]
	str r0, [r1, #0x60]
	str r0, [r1, #0x38]
	bx lr
	.balign 4
_0209CB74: .word 0x021D3498

	arm_func_start FUN_0209CB78
FUN_0209CB78: ; 0x0209CB78
	stmdb sp!, {r4,lr}
	ldr r3, _0209CBDC ; =0x021D3498
	ldr r3, [r3, #0x4]
	ldr r4, [r3, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r3, _0209CBE0 ; =0x7F000001
	cmp r2, r3
	ldreq r2, _0209CBE4 ; =0x021C8F04
	ldreq r2, [r2, #0x0]
	cmp r0, #0x0
	strh r1, [r4, #0x1a]
	ldrh r1, [r4, #0x1a]
	strh r1, [r4, #0x18]
	str r2, [r4, #0x20]
	ldr r1, [r4, #0x20]
	str r1, [r4, #0x1c]
	strneh r0, [r4, #0xa]
	ldmneia sp!, {r4,lr}
	bxne lr
	bl FUN_0209CC8C
	strh r0, [r4, #0xa]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209CBDC: .word 0x021D3498
_0209CBE0: .word 0x7F000001
_0209CBE4: .word 0x021C8F04

	arm_func_start FUN_0209CBE8
FUN_0209CBE8: ; 0x0209CBE8
	ldr r0, _0209CC0C ; =0x021D3498
	ldr r0, [r0, #0x4]
	ldr r1, [r0, #0xa4]
	cmp r1, #0x0
	movne r0, #0xa
	strneb r0, [r1, #0x8]
	movne r0, #0x0
	strne r0, [r1, #0x44]
	bx lr
	.balign 4
_0209CC0C: .word 0x021D3498

	arm_func_start FUN_0209CC10
FUN_0209CC10: ; 0x0209CC10
	ldr r0, _0209CC24 ; =0x021D3498
	mov r1, #0x0
	ldr r0, [r0, #0x4]
	str r1, [r0, #0xa4]
	bx lr
	.balign 4
_0209CC24: .word 0x021D3498

	arm_func_start FUN_0209CC28
FUN_0209CC28: ; 0x0209CC28
	ldr r1, _0209CC38 ; =0x021D3498
	ldr r1, [r1, #0x4]
	str r0, [r1, #0xa4]
	bx lr
	.balign 4
_0209CC38: .word 0x021D3498

	arm_func_start FUN_0209CC3C
FUN_0209CC3C: ; 0x0209CC3C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _0209CC88 ; =0x021C8F24
	ldr r3, [r1, #0x8]
	ldr r2, [r1, #0x0]
	ldr r0, [r1, #0x4]
	umull lr, r12, r3, r2
	mla r12, r3, r0, r12
	ldr r0, [r1, #0xc]
	ldr r3, [r1, #0x10]
	mla r12, r0, r2, r12
	adds r2, r3, lr
	ldr r0, [r1, #0x14]
	str r2, [r1, #0x0]
	adc r0, r0, r12
	str r0, [r1, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209CC88: .word 0x021C8F24

	arm_func_start FUN_0209CC8C
FUN_0209CC8C: ; 0x0209CC8C
	stmdb sp!, {r4-r8,lr}
	ldr r0, _0209CD30 ; =0x021D3498
	ldr r6, [r0, #0x8]
	ldr r2, _0209CD34 ; =0x021C8EBC
	mov r4, #0x400
	mov r3, #0x1
	mov r5, #0x0
	ldr r1, _0209CD38 ; =0x00001388
_0209CCAC:
	ldrh r12, [r2, #0x0]
	mov r0, r5
	add r12, r12, #0x1
	strh r12, [r2, #0x0]
	ldrh r12, [r2, #0x0]
	cmp r12, #0x400
	blo _0209CCD0
	cmp r12, r1
	blo _0209CCD4
_0209CCD0:
	strh r4, [r2, #0x0]
_0209CCD4:
	mov r8, r6
	cmp r6, #0x0
	beq _0209CD18
	ldrh r7, [r2, #0x0]
_0209CCE4:
	ldr lr, [r8, #0xa4]
	cmp lr, #0x0
	beq _0209CD0C
	ldr r12, [lr, #0x0]
	cmp r12, #0x0
	beq _0209CD0C
	ldrh r12, [lr, #0xa]
	cmp r12, r7
	moveq r0, r3
	beq _0209CD18
_0209CD0C:
	ldr r8, [r8, #0x68]
	cmp r8, #0x0
	bne _0209CCE4
_0209CD18:
	cmp r0, #0x0
	bne _0209CCAC
	ldr r0, _0209CD34 ; =0x021C8EBC
	ldrh r0, [r0, #0x0]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209CD30: .word 0x021D3498
_0209CD34: .word 0x021C8EBC
_0209CD38: .word 0x00001388

	arm_func_start FUN_0209CD3C
FUN_0209CD3C: ; 0x0209CD3C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, _0209CDAC ; =0x00000806
	add r4, sp, #0x0
_0209CD4C:
	mov r0, r4
	bl FUN_0209F57C
	ldr r3, [sp, #0x0]
	cmp r3, #0x22
	bls _0209CDA4
	ldrh r2, [r0, #0xc]
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	cmp r1, #0x800
	beq _0209CD88
	cmp r1, r5
	beq _0209CD98
	b _0209CDA4
_0209CD88:
	add r0, r0, #0xe
	sub r1, r3, #0xe
	bl FUN_0209CDB0
	b _0209CDA4
_0209CD98:
	add r0, r0, #0xe
	sub r1, r3, #0xe
	bl FUN_0209E614
_0209CDA4:
	bl FUN_0209F51C
	b _0209CD4C
	.balign 4
_0209CDAC: .word 0x00000806

	arm_func_start FUN_0209CDB0
FUN_0209CDB0: ; 0x0209CDB0
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldrh r12, [r4, #0xc]
	ldrh r6, [r4, #0x10]
	ldrh r2, [r4, #0xe]
	ldrh r0, [r4, #0x12]
	mov r5, r6, asr #0x8
	mov r3, r12, asr #0x8
	orr r5, r5, r6, lsl #0x8
	orr r12, r3, r12, lsl #0x8
	mov r3, r5, lsl #0x10
	mov r5, r0, asr #0x8
	mov r12, r12, lsl #0x10
	mov lr, r2, asr #0x8
	mov r6, r3, lsr #0x10
	orr r0, r5, r0, lsl #0x8
	mov r3, r12, lsr #0x10
	orr r2, lr, r2, lsl #0x8
	mov r5, r6, lsl #0x10
	mov r0, r0, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r0, r5, r0, lsr #0x10
	orr r2, r3, r2, lsr #0x10
	mov r5, r1
	cmp r0, r2
	beq _0209CEF0
	bl FUN_0209F9CC
_0209CE24: ; 0x0209CE24
	cmp r0, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrh r1, [r4, #0x2]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	cmp r5, r0, lsr #0x10
	addcc sp, sp, #0x8
	ldmccia sp!, {r4-r6,lr}
	bxcc lr
	ldrb r1, [r4, #0x0]
	mov r0, r4
	and r1, r1, #0xf
	mov r1, r1, lsl #0x2
	bl FUN_0209FB84
	ldr r1, _0209CFA0 ; =0x0000FFFF
	cmp r0, r1
	addne sp, sp, #0x8
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrh r2, [r4, #0x10]
	ldrh r12, [r4, #0x12]
	ldr r1, _0209CFA4 ; =0x021C8F04
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r2, r12, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r2, r12, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	ldr r1, [r1, #0x0]
	orr r0, r2, r0, lsr #0x10
	cmp r1, r0
	bne _0209CEF0
	ldrh r2, [r4, #0xc]
	ldrh r12, [r4, #0xe]
	sub r0, r4, #0x8
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r12, asr #0x8
	mov r3, r1, lsr #0x10
	orr r1, r2, r12, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r2, r1, lsr #0x10
	mov r2, #0x1
	bl FUN_0209F12C
_0209CEF0:
	add r1, sp, #0x0
	mov r0, r4
	bl FUN_0209CFAC
	movs r4, r0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrh r2, [r4, #0x2]
	ldrb r3, [r4, #0x0]
	ldrb r12, [r4, #0x9]
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	and r3, r3, #0xf
	mov r2, r1, lsr #0x10
	cmp r12, #0x11
	add r1, r4, r3, lsl #0x2
	sub r2, r2, r3, lsl #0x2
	bne _0209CF44
	bl FUN_0209D2BC
	b _0209CF70
_0209CF44:
	ldr r3, _0209CFA4 ; =0x021C8F04
	ldr r3, [r3, #0x0]
	cmp r3, #0x0
	beq _0209CF70
	cmp r12, #0x1
	bne _0209CF64
	bl FUN_0209E2E0
	b _0209CF70
_0209CF64:
	cmp r12, #0x6
	bne _0209CF70
	bl FUN_0209D4D8
_0209CF70:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r1, _0209CFA8 ; =0x021C8EF4
	sub r0, r4, #0xe
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209CFA0: .word 0x0000FFFF
_0209CFA4: .word 0x021C8F04
_0209CFA8: .word 0x021C8EF4

	arm_func_start FUN_0209CFAC
FUN_0209CFAC: ; 0x0209CFAC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r6, #0x0
	mov r10, r0
	str r6, [r1, #0x0]
	ldrh r3, [r10, #0x6]
	str r1, [sp, #0x0]
	ldr r2, _0209D2A4 ; =0x00003FFF
	mov r1, r3, asr #0x8
	orr r1, r1, r3, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	str r1, [sp, #0x4]
	ands r1, r1, r2
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldrh r1, [r10, #0xc]
	ldrh r3, [r10, #0xe]
	ldrb r4, [r10, #0x0]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	and r3, r4, #0xf
	ldrh r9, [r10, #0x4]
	mov r2, r2, lsl #0x10
	mov r1, r0, lsl #0x10
	ldr r5, _0209D2A8 ; =0x021C9520
	mov r0, r6
	mov r7, r3, lsl #0x2
	orr r4, r2, r1, lsr #0x10
_0209D034:
	ldrh r2, [r5, #0x4]
	cmp r2, #0x0
	beq _0209D058
	ldr r1, [r5, #0x0]
	cmp r1, r4
	bne _0209D058
	ldrh r1, [r5, #0x6]
	cmp r1, r9
	beq _0209D078
_0209D058:
	cmp r2, #0x0
	bne _0209D068
	cmp r6, #0x0
	moveq r6, r5
_0209D068:
	add r0, r0, #0x1
	cmp r0, #0x8
	add r5, r5, #0x38
	blo _0209D034
_0209D078:
	ldrh r2, [r10, #0x2]
	cmp r0, #0x8
	ldr r1, _0209D2AC ; =0x00001FFF
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	ldr r0, [sp, #0x4]
	and r8, r0, r1
	sub r0, r2, r7
	str r0, [sp, #0x8]
	mov r0, r8, lsl #0x3
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x8]
	add r11, r0, r8, lsl #0x3
	bne _0209D150
	cmp r6, #0x0
	beq _0209D0C8
	cmp r11, #0x1000
	bls _0209D0D8
_0209D0C8:
	add sp, sp, #0x14
	mov r0, #0x0
	ldmia sp!, {r4-r11,lr}
	bx lr
_0209D0D8:
	ldr r1, _0209D2B0 ; =0x021C8EC8
	ldr r0, _0209D2B4 ; =0x0000100E
	ldr r1, [r1, #0x0]
	add r0, r7, r0
	mov r5, r6
	blx r1
	str r0, [r6, #0x34]
	ldr r0, [r6, #0x34]
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	str r4, [r6, #0x0]
	strh r9, [r6, #0x6]
	mov r0, #0x0
	strh r0, [r6, #0x8]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	str r0, [r6, #0x2c]
	ldr r1, [r6, #0x34]
	mov r0, r10
	add r1, r1, #0xe
	add r1, r1, r7
	str r1, [r6, #0x30]
	ldr r1, [r6, #0x34]
	mov r2, r7
	add r1, r1, #0xe
	bl MI_CpuCopy8
_0209D150:
	ldrh r0, [r5, #0x4]
	cmp r0, #0x8
	beq _0209D164
	cmp r11, #0x1000
	bls _0209D18C
_0209D164:
	mov r0, #0x0
	strh r0, [r5, #0x4]
	ldr r1, _0209D2B8 ; =0x021C8EF4
	ldr r0, [r5, #0x34]
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x14
	mov r0, #0x0
	ldmia sp!, {r4-r11,lr}
	bx lr
_0209D18C:
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x8]
	add r0, r0, #0x7
	add r1, r8, r0, lsr #0x3
	ldr r0, [sp, #0x4]
	ands r0, r0, #0x2000
	streqh r11, [r5, #0xa]
	streqh r1, [r5, #0x8]
	ldrh r3, [r5, #0x4]
	add r0, r10, r7
	add r3, r5, r3, lsl #0x1
	strh r8, [r3, #0xc]
	ldrh r3, [r5, #0x4]
	add r3, r5, r3, lsl #0x1
	strh r1, [r3, #0x1c]
	ldrh r1, [r5, #0x4]
	add r1, r1, #0x1
	strh r1, [r5, #0x4]
	ldr r3, [r5, #0x30]
	ldr r1, [sp, #0xc]
	add r1, r3, r1
	bl MI_CpuCopy8
	ldrh r6, [r5, #0x8]
	cmp r6, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldrh r7, [r5, #0x4]
	mov r3, #0x0
	mov r4, r3
	cmp r7, #0x0
	bls _0209D244
	mov r0, r3
_0209D214:
	add r2, r5, r4, lsl #0x1
	ldrh r1, [r2, #0xc]
	cmp r1, r3
	bhi _0209D238
	ldrh r1, [r2, #0x1c]
	cmp r3, r1
	movcc r3, r1
	movcc r4, r0
	blo _0209D23C
_0209D238:
	add r4, r4, #0x1
_0209D23C:
	cmp r4, r7
	blo _0209D214
_0209D244:
	cmp r3, r6
	addcc sp, sp, #0x14
	movcc r0, #0x0
	ldmccia sp!, {r4-r11,lr}
	bxcc lr
	ldr r0, [r5, #0x34]
	ldrh r3, [r5, #0xa]
	ldrb r1, [r0, #0xe]
	add r0, r0, #0xe
	mov r2, #0x0
	and r1, r1, #0xf
	add r1, r3, r1, lsl #0x2
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	mov r1, r3, asr #0x8
	orr r1, r1, r3, lsl #0x8
	strh r1, [r0, #0x2]
	strh r2, [r5, #0x4]
	ldr r1, [sp, #0x0]
	mov r2, #0x1
	str r2, [r1, #0x0]
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209D2A4: .word 0x00003FFF
_0209D2A8: .word 0x021C9520
_0209D2AC: .word 0x00001FFF
_0209D2B0: .word 0x021C8EC8
_0209D2B4: .word 0x0000100E
_0209D2B8: .word 0x021C8EF4

	arm_func_start FUN_0209D2BC
FUN_0209D2BC: ; 0x0209D2BC
	stmdb sp!, {r4-r8,lr}
	mov r6, r1
	ldrh r1, [r6, #0x6]
	mov r7, r0
	mov r5, r2
	cmp r1, #0x0
	beq _0209D2F8
	mov r0, r6
	mov r1, r5
	mov r2, r7
	mov r3, #0x11
	bl FUN_0209FB28
_0209D2EC: ; 0x0209D2EC
	cmp r0, #0x0
	ldmneia sp!, {r4-r8,lr}
	bxne lr
_0209D2F8:
	bl OS_DisableInterrupts
	ldr r1, _0209D4D4 ; =0x021D3498
	mov r8, r0
	ldr r2, [r1, #0x8]
	cmp r2, #0x0
	beq _0209D4C4
	mvn r12, #0x0
_0209D314:
	ldr r4, [r2, #0xa4]
	cmp r4, #0x0
	beq _0209D4B8
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0209D4B8
	ldrb r0, [r4, #0x8]
	cmp r0, #0xa
	bne _0209D4B8
	ldrh r3, [r6, #0x2]
	ldrh r1, [r4, #0xa]
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	mov r0, r0, lsl #0x10
	cmp r1, r0, lsr #0x10
	bne _0209D4B8
	ldrh r3, [r4, #0x18]
	cmp r3, #0x0
	beq _0209D378
	ldrh r1, [r6, #0x0]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	cmp r3, r0, lsr #0x10
	bne _0209D4B8
_0209D378:
	ldr r1, [r4, #0x1c]
	cmp r1, #0x0
	beq _0209D3C0
	cmp r1, r12
	beq _0209D3C0
	ldrh lr, [r7, #0xc]
	ldrh r0, [r7, #0xe]
	mov r3, lr, asr #0x8
	orr r3, r3, lr, lsl #0x8
	mov r3, r3, lsl #0x10
	mov lr, r0, asr #0x8
	mov r3, r3, lsr #0x10
	orr r0, lr, r0, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r3, r0, lsr #0x10
	cmp r1, r0
	bne _0209D4B8
_0209D3C0:
	ldrh r1, [r7, #0x10]
	ldrh r3, [r7, #0x12]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x1c]
	cmp r0, #0x0
	bne _0209D43C
	ldrh r1, [r7, #0xc]
	ldrh r3, [r7, #0xe]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	str r0, [r4, #0x1c]
	ldrh r1, [r6, #0x0]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	strh r0, [r4, #0x18]
_0209D43C:
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	bne _0209D4C4
	ldr r1, [r4, #0x3c]
	sub r0, r5, #0x8
	cmp r0, r1
	strhi r1, [r4, #0x44]
	strls r0, [r4, #0x44]
	ldr r1, [r4, #0x40]
	ldr r2, [r4, #0x44]
	add r0, r6, #0x8
	bl MI_CpuCopy8
	ldr r0, [r4, #0x4]
	cmp r0, #0x3
	bne _0209D48C
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	b _0209D4C4
_0209D48C:
	ldr r3, [r4, #0x38]
	cmp r3, #0x0
	beq _0209D4C4
	ldr r0, [r4, #0x40]
	ldr r1, [r4, #0x44]
	mov r2, r4
	blx r3
	cmp r0, #0x0
	movne r0, #0x0
	strne r0, [r4, #0x44]
	b _0209D4C4
_0209D4B8:
	ldr r2, [r2, #0x68]
	cmp r2, #0x0
	bne _0209D314
_0209D4C4:
	mov r0, r8
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209D4D4: .word 0x021D3498

	arm_func_start FUN_0209D4D8
FUN_0209D4D8:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	mov r0, r5
	mov r1, r4
	mov r2, r6
	mov r3, #0x6
	bl FUN_0209FB28
_0209D4FC: ; 0x0209D4FC
	cmp r0, #0x0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrb r0, [r5, #0xc]
	ldrb r2, [r5, #0xd]
	and r1, r0, #0xf0
	mov r0, r1, asr #0x1
	add r0, r1, r0, lsr #0x1e
	and r1, r2, #0x17
	cmp r1, #0x10
	sub r4, r4, r0, asr #0x2
	bgt _0209D558
	cmp r1, #0x10
	bge _0209D5C4
	cmp r1, #0x2
	bgt _0209D5F4
	cmp r1, #0x1
	blt _0209D5F4
	cmp r1, #0x1
	beq _0209D5DC
	cmp r1, #0x2
	beq _0209D57C
	b _0209D5F4
_0209D558:
	cmp r1, #0x12
	bgt _0209D5F4
	cmp r1, #0x11
	blt _0209D5F4
	cmp r1, #0x11
	beq _0209D5C4
	cmp r1, #0x12
	beq _0209D5A0
	b _0209D5F4
_0209D57C:
	ands r0, r2, #0x28
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209DBB0
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5A0:
	ands r0, r2, #0x28
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209DA9C
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5C4:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209D774
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5DC:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209D674
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5F4:
	ands r0, r2, #0x4
	beq _0209D610
	mov r0, r6
	mov r1, r5
	bl FUN_0209D62C
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D610:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	mov r3, #0x0
	bl FUN_0209DE34
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209D62C
FUN_0209D62C: ; 0x0209D62C
	stmdb sp!, {r4,lr}
	bl FUN_0209E0C8
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl OS_YieldThread
	mov r1, #0x0
	strb r1, [r4, #0x8]
	ldr r0, [r4, #0x4]
	sub r0, r0, #0x1
	cmp r0, #0x1
	ldmhiia sp!, {r4,lr}
	bxhi lr
	str r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209D674
FUN_0209D674: ; 0x0209D674
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl FUN_0209E0C8
	movs r4, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrb r1, [r4, #0x8]
	cmp r1, #0x4
	beq _0209D72C
	cmp r1, #0x7
	beq _0209D6BC
	cmp r1, #0x8
	beq _0209D6E4
	b _0209D754
_0209D6BC:
	ldr r2, [r4, #0x24]
	mov r1, #0x0
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl FUN_0209DF84
	mov r0, #0x9
	add sp, sp, #0x4
	strb r0, [r4, #0x8]
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209D6E4:
	ldr r2, [r4, #0x24]
	mov r1, #0x0
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl FUN_0209DF84
	mov r1, #0x0
	strb r1, [r4, #0x8]
	ldr r0, [r4, #0x4]
	cmp r0, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	str r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209D72C:
	ldr r2, [r4, #0x24]
	mov r1, #0x0
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl FUN_0209DF70
	mov r0, #0x6
	add sp, sp, #0x4
	strb r0, [r4, #0x8]
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209D754:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, #0x0
	bl FUN_0209DE34
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209D774
FUN_0209D774: ; 0x0209D774
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	mov r7, r1
	mov r6, r2
	bl FUN_0209E0C8
	movs r5, r0
	bne _0209D7B4
	mov r0, r8
	mov r1, r7
	mov r2, r6
	mov r3, #0x0
	bl FUN_0209DE34
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
_0209D7B4:
	ldrh r3, [r7, #0x8]
	ldrh r1, [r7, #0xa]
	ldrb r4, [r7, #0xd]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, r1, asr #0x8
	mov r2, r2, lsr #0x10
	orr r1, r3, r1, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r2, r1, lsr #0x10
	str r1, [r5, #0x30]
	ldrh r9, [r7, #0x4]
	ldrh r1, [r7, #0x6]
	ldrb r3, [r5, #0x8]
	mov r2, r9, asr #0x8
	orr r2, r2, r9, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r9, r1, asr #0x8
	mov r2, r2, lsr #0x10
	orr r1, r9, r1, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r1, r1, lsl #0x10
	cmp r3, #0x4
	orr r2, r2, r1, lsr #0x10
	bne _0209D840
	ldr r1, [r5, #0x24]
	cmp r1, r2
	beq _0209D840
	mov r1, #0x0
	bl FUN_0209DF84
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
_0209D840:
	ldrh r1, [r7, #0xe]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	strh r0, [r5, #0x2c]
	ldrb r0, [r5, #0x8]
	cmp r0, #0x9
	addls pc, pc, r0, lsl #0x2
	b _0209DA70
_0209D860:
	b _0209D888
_0209D864:
	b _0209DA70
_0209D868:
	b _0209D888
_0209D86C:
	b _0209D8A0
_0209D870:
	b _0209D8CC
_0209D874:
	b _0209DA70
_0209D878:
	b _0209DA4C
_0209D87C:
	b _0209D9D8
_0209D880:
	b _0209D9D8
_0209D884:
	b _0209DA4C
_0209D888:
	mov r0, r8
	mov r1, r7
	mov r2, r6
	mov r3, #0x0
	bl FUN_0209DE34
	b _0209DA8C
_0209D8A0:
	mov r0, #0x4
	strb r0, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r0, #0x1
	bne _0209D8C4
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
_0209D8C4:
	cmp r6, #0x0
	beq _0209DA8C
_0209D8CC:
	ldr r0, [r5, #0x34]
	add r0, r0, #0x1
	str r0, [r5, #0x34]
	ldr r1, [r5, #0x3c]
	ldr r0, [r5, #0x44]
	sub r0, r1, r0
	cmp r6, r0
	movhi r9, #0x0
	movhi r6, r0
	movls r9, #0x1
	cmp r6, #0x0
	beq _0209D968
	bl OS_DisableInterrupts
	ldrb r1, [r7, #0xc]
	ldr r12, [r5, #0x40]
	ldr r3, [r5, #0x44]
	and r2, r1, #0xf0
	mov r1, r2, asr #0x1
	add r1, r2, r1, lsr #0x1e
	mov r8, r0
	mov r2, r6
	add r0, r7, r1, asr #0x2
	add r1, r12, r3
	bl MI_CpuCopy8
	ldr r1, [r5, #0x44]
	mov r0, r8
	add r1, r1, r6
	str r1, [r5, #0x44]
	ldr r1, [r5, #0x24]
	add r1, r1, r6
	str r1, [r5, #0x24]
	bl OS_RestoreInterrupts
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209D968
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
_0209D968:
	cmp r9, #0x0
	beq _0209D9C0
	ands r0, r4, #0x1
	beq _0209D9C0
	mov r0, #0x6
	strb r0, [r5, #0x8]
	ldr r1, [r5, #0x24]
	mov r0, r5
	add r2, r1, #0x1
	mov r1, #0x0
	str r2, [r5, #0x24]
	bl FUN_0209DF70
_0209D998: ; 0x0209D998
	cmp r6, #0x0
	bne _0209DA8C
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209DA8C
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
	b _0209DA8C
_0209D9C0:
	cmp r6, #0x0
	beq _0209DA8C
	mov r0, r5
	mov r1, #0x0
	bl FUN_0209DF84
	b _0209DA8C
_0209D9D8:
	ands r0, r4, #0x1
	beq _0209DA20
	ldr r1, [r5, #0x24]
	add r0, r6, #0x1
	add r2, r1, r0
	mov r0, r5
	mov r1, #0x0
	str r2, [r5, #0x24]
	bl FUN_0209DF84
	mov r1, #0x0
	strb r1, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209DA8C
	str r1, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
	b _0209DA8C
_0209DA20:
	cmp r6, #0x0
	beq _0209DA40
	ldr r1, [r5, #0x24]
	mov r0, r5
	add r2, r1, r6
	mov r1, #0x0
	str r2, [r5, #0x24]
	bl FUN_0209DF84
_0209DA40:
	mov r0, #0x8
	strb r0, [r5, #0x8]
	b _0209DA8C
_0209DA4C:
	mov r1, #0x0
	strb r1, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209DA8C
	str r1, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
	b _0209DA8C
_0209DA70:
	ands r0, r4, #0x1
	ldrne r0, [r5, #0x24]
	mov r1, #0x0
	addne r0, r0, #0x1
	strne r0, [r5, #0x24]
	mov r0, r5
	bl FUN_0209DF84
_0209DA8C:
	bl OS_YieldThread
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_0209DA9C
FUN_0209DA9C: ; 0x0209DA9C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r5, r1
	mov r6, r2
	bl FUN_0209E0C8
	movs r4, r0
	beq _0209DAC8
	ldrb r0, [r4, #0x8]
	cmp r0, #0x2
	beq _0209DAE8
_0209DAC8:
	mov r0, r7
	mov r1, r5
	mov r2, r6
	mov r3, #0x0
	bl FUN_0209DE34
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209DAE8:
	bl OS_YieldThread
	ldrh r2, [r5, #0x4]
	ldrh r12, [r5, #0x6]
	mov r0, r5
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r12, asr #0x8
	mov r3, r1, lsr #0x10
	orr r1, r2, r12, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r2, r1, lsr #0x10
	add r1, r1, #0x1
	str r1, [r4, #0x24]
	ldrh r3, [r5, #0x8]
	ldrh lr, [r5, #0xa]
	mov r1, r4
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, lr, asr #0x8
	mov r12, r2, lsr #0x10
	orr r2, r3, lr, lsl #0x8
	mov r3, r12, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r2, r3, r2, lsr #0x10
	str r2, [r4, #0x30]
	ldrh r3, [r5, #0xe]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	strh r2, [r4, #0x2c]
	bl FUN_0209E044
	mov r0, r4
	mov r1, #0x0
	bl FUN_0209DF84
	mov r0, #0x4
	strb r0, [r4, #0x8]
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209DBB0
FUN_0209DBB0: ; 0x0209DBB0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldrh r12, [r4, #0x10]
	ldrh r7, [r4, #0xc]
	ldrh r3, [r4, #0x12]
	mov r5, r12, asr #0x8
	mov r6, r7, asr #0x8
	orr r5, r5, r12, lsl #0x8
	orr r6, r6, r7, lsl #0x8
	mov r12, r6, lsl #0x10
	ldrh r0, [r4, #0xe]
	mov lr, r5, lsl #0x10
	mov r5, r3, asr #0x8
	mov r6, r0, asr #0x8
	mov r7, r12, lsr #0x10
	orr r0, r6, r0, lsl #0x8
	orr r3, r5, r3, lsl #0x8
	mov r12, lr, lsr #0x10
	mov r6, r7, lsl #0x10
	mov r0, r0, lsl #0x10
	mov r5, r12, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r7, r1
	orr r1, r5, r3, lsr #0x10
	orr r0, r6, r0, lsr #0x10
	mov r5, r2
	bl FUN_0209E3DC
_0209DC20: ; 0x0209DC20
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r4
	mov r1, r7
	mov r2, r5
	bl FUN_0209DCB4
_0209DC40: ; 0x0209DC40
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	mov r0, r4
	mov r1, r7
	bl FUN_0209E200
	movs r2, r0
	beq _0209DC7C
	mov r0, r4
	mov r1, r7
	bl FUN_0209DD44
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209DC7C:
	bl OS_YieldThread
	mov r0, r4
	mov r1, r7
	bl FUN_0209E200
	movs r2, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r4
	mov r1, r7
	bl FUN_0209DD44
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209DCB4
FUN_0209DCB4:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl FUN_0209E0C8
	movs r2, r0
	beq _0209DD38
	ldrb r0, [r2, #0x8]
	cmp r0, #0x1
	bne _0209DCEC
	mov r0, r6
	mov r1, r5
	bl FUN_0209DD44
	b _0209DD2C
_0209DCEC:
	add r0, r0, #0xfd
	and r0, r0, #0xff
	cmp r0, #0x1
	bhi _0209DD18
	ldr r1, [r2, #0x28]
	mov r0, r6
	sub r3, r1, #0x1
	mov r1, r5
	str r3, [r2, #0x28]
	bl FUN_0209DD44
	b _0209DD2C
_0209DD18:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	mov r3, #0x0
	bl FUN_0209DE34
_0209DD2C:
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209DD38:
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209DD44
FUN_0209DD44: ; 0x0209DD44
	stmdb sp!, {r4-r6,lr}
	mov r4, r2
	mov r2, #0x3
	mov r6, r0
	mov r5, r1
	strb r2, [r4, #0x8]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	str r0, [r4, #0x10]
	ldrh r2, [r6, #0x10]
	ldrh r3, [r6, #0x12]
	mov r0, r5
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r1, r1, lsr #0x10
	mov r3, r1, lsl #0x10
	mov r1, r2, lsl #0x10
	orr r1, r3, r1, lsr #0x10
	str r1, [r4, #0x14]
	ldrh r3, [r5, #0x0]
	mov r1, r4
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	strh r2, [r4, #0x18]
	ldrh r3, [r6, #0xc]
	ldrh r6, [r6, #0xe]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, r6, asr #0x8
	orr r3, r3, r6, lsl #0x8
	mov r2, r2, lsr #0x10
	mov r6, r2, lsl #0x10
	mov r2, r3, lsl #0x10
	orr r2, r6, r2, lsr #0x10
	str r2, [r4, #0x1c]
	ldrh r3, [r5, #0x4]
	ldrh r6, [r5, #0x6]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, r6, asr #0x8
	mov r5, r2, lsr #0x10
	orr r2, r3, r6, lsl #0x8
	mov r3, r5, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r2, r3, r2, lsr #0x10
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl FUN_0209E044
	mov r0, r4
	mov r1, #0x12
	mov r2, #0x0
	bl FUN_0209DF98
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209DE34
FUN_0209DE34: ; 0x0209DE34
	stmdb sp!, {r4-r8,lr}
	ldr r4, _0209DF6C ; =0x021C903C
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r0, r4
	mov r1, #0x0
	mov r2, #0x64
	mov r5, r3
	bl MI_CpuFill8
	ldrh r2, [r7, #0x2]
	mov r1, r4
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r1, #0xa]
	ldrh r2, [r7, #0x0]
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r1, #0x18]
	ldrh r2, [r8, #0xc]
	ldrh r8, [r8, #0xe]
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r2, r8, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r2, r8, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r2, r0, lsr #0x10
	str r0, [r1, #0x1c]
	ldrb r0, [r7, #0xd]
	ands r0, r0, #0x10
	beq _0209DF04
	ldrh r2, [r7, #0x8]
	ldrh r6, [r7, #0xa]
	mov r0, r4
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r6, asr #0x8
	mov r3, r1, lsr #0x10
	orr r1, r2, r6, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r3, r2, r1, lsr #0x10
	mov r2, r5
	mov r1, #0x4
	str r3, [r4, #0x28]
	bl FUN_0209DF98
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209DF04:
	mov r0, #0x0
	str r0, [r4, #0x28]
	ldrh r1, [r7, #0x4]
	ldrh r3, [r7, #0x6]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	add r0, r6, r0
	str r0, [r4, #0x24]
	ldrb r0, [r7, #0xd]
	mov r2, r5
	mov r1, #0x14
	ands r0, r0, #0x3
	ldrne r0, [r4, #0x24]
	addne r0, r0, #0x1
	strne r0, [r4, #0x24]
	mov r0, r4
	bl FUN_0209DF98
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209DF6C: .word 0x021C903C

	arm_func_start FUN_0209DF70
FUN_0209DF70:
	ldr ip, _0209DF80 ; =FUN_0209DF98
	mov r2, r1
	mov r1, #0x11
	bx r12
	.balign 4
_0209DF80: .word FUN_0209DF98

	arm_func_start FUN_0209DF84
FUN_0209DF84: ; 0x0209DF84
	ldr ip, _0209DF94 ; =FUN_0209DF98
	mov r2, r1
	mov r1, #0x10
	bx r12
	.balign 4
_0209DF94: .word FUN_0209DF98

	arm_func_start FUN_0209DF98
FUN_0209DF98: ; 0x0209DF98
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r6, r0
	ldr r0, [r6, #0x1c]
	mov r5, r1
	mov r4, r2
	bl FUN_0209E014
_0209DFB4: ; 0x0209DFB4
	cmp r0, #0x0
	bne _0209DFD0
	ldr r0, _0209E00C ; =0x021D3498
	ldr r1, _0209E010 ; =0x021C9160
	ldr r0, [r0, #0x4]
	cmp r0, r1
	beq _0209DFF4
_0209DFD0:
	mov r0, #0x0
	mov r1, r0
	mov r2, r6
	mov r3, r5
	str r4, [sp, #0x0]
	bl FUN_0209E878
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209DFF4:
	ldr r0, [r6, #0x1c]
	bl FUN_0209FAB0
	bl FUN_0209F338
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209E00C: .word 0x021D3498
_0209E010: .word 0x021C9160

	arm_func_start FUN_0209E014
FUN_0209E014:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_0209FAB0
_0209E020: ; 0x0209E020
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {lr}
	bxeq lr
	bl FUN_0209F438
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209E044
FUN_0209E044: ; 0x0209E044
	mov r2, #0x218
	strh r2, [r1, #0x2e]
	ldrb r2, [r0, #0xc]
	add r3, r0, #0x14
	and r2, r2, #0xf0
	mov r0, r2, asr #0x1
	add r0, r2, r0, lsr #0x1e
	mov r0, r0, asr #0x2
	subs r0, r0, #0x14
	sub r12, r0, #0x1
	bxeq lr
_0209E070:
	ldrb r0, [r3], #0x1
	cmp r0, #0x0
	bxeq lr
	cmp r0, #0x1
	beq _0209E0B8
	cmp r0, #0x2
	bne _0209E0A8
	ldrb r2, [r3, #0x1]
	ldrb r0, [r3, #0x2]
	add r3, r3, #0x3
	sub r12, r12, #0x3
	orr r0, r0, r2, lsl #0x8
	strh r0, [r1, #0x2e]
	b _0209E0B8
_0209E0A8:
	ldrb r0, [r3, #0x0]
	sub r0, r0, #0x1
	sub r12, r12, r0
	add r3, r3, r0
_0209E0B8:
	cmp r12, #0x0
	sub r12, r12, #0x1
	bne _0209E070
	bx lr

	arm_func_start FUN_0209E0C8
FUN_0209E0C8: ; 0x0209E0C8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r2, _0209E140 ; =0x021D3498
	mov r7, r0
	ldr r4, [r2, #0x8]
	mov r6, r1
	cmp r4, #0x0
	beq _0209E130
_0209E0E8:
	ldr r5, [r4, #0xa4]
	cmp r5, #0x0
	beq _0209E124
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0209E124
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_0209E144
_0209E110: ; 0x0209E110
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, r5
	ldmneia sp!, {r4-r7,lr}
	bxne lr
_0209E124:
	ldr r4, [r4, #0x68]
	cmp r4, #0x0
	bne _0209E0E8
_0209E130:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209E140: .word 0x021D3498

	arm_func_start FUN_0209E144
FUN_0209E144:
	stmdb sp!, {r4-r6,lr}
	ldrb r4, [r2, #0x8]
	mov r12, #0x0
	mov r3, r12
	mov r6, r12
	mov r5, r12
	cmp r4, #0xa
	beq _0209E16C
	cmp r4, #0xb
	movne r5, #0x1
_0209E16C:
	cmp r5, #0x0
	beq _0209E190
	ldrh lr, [r1, #0x2]
	ldrh r5, [r2, #0xa]
	mov r4, lr, asr #0x8
	orr r4, r4, lr, lsl #0x8
	mov lr, r4, lsl #0x10
	cmp r5, lr, lsr #0x10
	moveq r6, #0x1
_0209E190:
	cmp r6, #0x0
	beq _0209E1B4
	ldrh r4, [r1, #0x0]
	ldrh lr, [r2, #0x18]
	mov r1, r4, asr #0x8
	orr r1, r1, r4, lsl #0x8
	mov r1, r1, lsl #0x10
	cmp lr, r1, lsr #0x10
	moveq r3, #0x1
_0209E1B4:
	cmp r3, #0x0
	beq _0209E1F4
	ldrh r1, [r0, #0xc]
	ldrh lr, [r0, #0xe]
	ldr r3, [r2, #0x1c]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, lr, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, lr, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	cmp r3, r0
	moveq r12, #0x1
_0209E1F4:
	mov r0, r12
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209E200
FUN_0209E200: ; 0x0209E200
	stmdb sp!, {r4-r6,lr}
	ldr r2, _0209E2DC ; =0x021D3498
	ldr r3, [r2, #0x8]
	cmp r3, #0x0
	beq _0209E2D0
_0209E214:
	ldr r12, [r3, #0xa4]
	cmp r12, #0x0
	beq _0209E2C4
	ldr r2, [r12, #0x0]
	cmp r2, #0x0
	beq _0209E2C4
	ldrb r2, [r12, #0x8]
	cmp r2, #0x1
	bne _0209E2C4
	ldrh r5, [r1, #0x2]
	ldrh r4, [r12, #0xa]
	mov r2, r5, asr #0x8
	orr r2, r2, r5, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r4, r2, lsr #0x10
	bne _0209E2C4
	ldrh r5, [r12, #0x18]
	cmp r5, #0x0
	beq _0209E278
	ldrh r4, [r1, #0x0]
	mov r2, r4, asr #0x8
	orr r2, r2, r4, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r5, r2, lsr #0x10
	bne _0209E2C4
_0209E278:
	ldr r2, [r12, #0x1c]
	cmp r2, #0x0
	beq _0209E2B8
	ldrh r5, [r0, #0xc]
	ldrh r6, [r0, #0xe]
	mov r4, r5, asr #0x8
	orr r4, r4, r5, lsl #0x8
	mov lr, r4, lsl #0x10
	mov r4, r6, asr #0x8
	mov lr, lr, lsr #0x10
	orr r4, r4, r6, lsl #0x8
	mov r5, lr, lsl #0x10
	mov lr, r4, lsl #0x10
	orr r4, r5, lr, lsr #0x10
	cmp r2, r4
	bne _0209E2C4
_0209E2B8:
	mov r0, r12
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209E2C4:
	ldr r3, [r3, #0x68]
	cmp r3, #0x0
	bne _0209E214
_0209E2D0:
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209E2DC: .word 0x021D3498

	arm_func_start FUN_0209E2E0
FUN_0209E2E0: ; 0x0209E2E0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	mov r4, r2
	mov r6, r0
	mov r0, r5
	mov r1, r4
	bl FUN_0209FB84
	ldr r1, _0209E3D8 ; =0x0000FFFF
	cmp r0, r1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r12, [r6, #0x10]
	ldrh r7, [r6, #0xc]
	ldrh r0, [r6, #0xe]
	ldrh r1, [r6, #0x12]
	mov r3, r7, asr #0x8
	mov lr, r0, asr #0x8
	orr r0, lr, r0, lsl #0x8
	mov r2, r12, asr #0x8
	orr r7, r3, r7, lsl #0x8
	orr r3, r2, r12, lsl #0x8
	mov r2, r7, lsl #0x10
	mov r12, r1, asr #0x8
	orr r1, r12, r1, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r7, r2, lsr #0x10
	mov r2, r3, lsr #0x10
	mov r3, r7, lsl #0x10
	mov r0, r0, lsl #0x10
	mov r2, r2, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r0, r3, r0, lsr #0x10
	orr r1, r2, r1, lsr #0x10
	bl FUN_0209E3DC
_0209E370: ; 0x0209E370
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrb r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0209E3A0
	cmp r0, #0x8
	beq _0209E3BC
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E3A0:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209E40C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E3BC:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209E524
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209E3D8: .word 0x0000FFFF

	arm_func_start FUN_0209E3DC
FUN_0209E3DC:
	cmp r0, #0x0
	beq _0209E404
	mvn r2, #0x0
	cmp r0, r2
	beq _0209E404
	cmp r1, #0x0
	beq _0209E404
	cmp r1, r2
	movne r0, #0x1
	bxne lr
_0209E404:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_0209E40C
FUN_0209E40C: ; 0x0209E40C
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl OS_DisableInterrupts
	ldr r1, _0209E520 ; =0x021D3498
	mov r8, r0
	ldr r2, [r1, #0x8]
	cmp r2, #0x0
	beq _0209E510
_0209E434:
	ldr r4, [r2, #0xa4]
	cmp r4, #0x0
	beq _0209E504
	ldr r3, [r4, #0x0]
	cmp r3, #0x0
	beq _0209E504
	ldrb r0, [r4, #0x8]
	cmp r0, #0xb
	bne _0209E504
	ldrh r1, [r6, #0x4]
	mov r0, r3, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r0, r1
	bne _0209E504
	ldrh r1, [r4, #0xa]
	ldrh r0, [r6, #0x6]
	cmp r1, r0
	bne _0209E504
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	bne _0209E504
	ldrh r12, [r7, #0xc]
	ldrh r1, [r7, #0xe]
	ldr r0, [r4, #0x1c]
	mov r3, r12, asr #0x8
	orr r3, r3, r12, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r12, r1, asr #0x8
	mov r3, r3, lsr #0x10
	orr r1, r12, r1, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r3, r1, lsr #0x10
	cmp r0, r1
	bne _0209E504
	ldr r1, [r4, #0x3c]
	sub r0, r5, #0x8
	cmp r0, r1
	strhi r1, [r4, #0x44]
	strls r0, [r4, #0x44]
	ldr r1, [r4, #0x40]
	ldr r2, [r4, #0x44]
	add r0, r6, #0x8
	bl MI_CpuCopy8
	ldr r0, [r4, #0x4]
	cmp r0, #0x3
	bne _0209E510
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	b _0209E510
_0209E504:
	ldr r2, [r2, #0x68]
	cmp r2, #0x0
	bne _0209E434
_0209E510:
	mov r0, r8
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209E520: .word 0x021D3498

	arm_func_start FUN_0209E524
FUN_0209E524: ; 0x0209E524
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r6, r0
	ldrh r3, [r6, #0xc]
	ldrh r4, [r6, #0xe]
	mov r5, r1
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r4, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r1, r4, lsl #0x8
	mov r1, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	mov r4, r2
	bl FUN_0209FAB0
	movs r7, r0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	bl FUN_0209F438
_0209E57C: ; 0x0209E57C
	cmp r0, #0x0
	bne _0209E598
	mov r0, r7
	bl FUN_0209F338
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E598:
	mov r2, #0x0
	strb r2, [r5, #0x0]
	mov r0, r5
	mov r1, r4
	strh r2, [r5, #0x2]
	bl FUN_0209FB84
	mov r1, r0, asr #0x8
	orr r0, r1, r0, lsl #0x8
	strh r0, [r5, #0x2]
	ldrh r1, [r6, #0xc]
	ldrh r6, [r6, #0xe]
	mov r2, #0x0
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r6, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r1, r6, lsl #0x8
	mov r1, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r6, r1, r0, lsr #0x10
	mov r0, r5
	mov r1, r4
	mov r3, r2
	str r6, [sp, #0x0]
	mov r4, #0x1
	str r4, [sp, #0x4]
	bl FUN_0209ECFC
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209E614
FUN_0209E614: ; 0x0209E614
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	cmp r1, #0x1c
	mov r6, r0
	addcc sp, sp, #0x4
	ldmccia sp!, {r4-r7,lr}
	bxcc lr
	ldr r1, _0209E7BC ; =0x021C8F14
	add r0, r6, #0x8
	bl FUN_0209F9A0
_0209E63C: ; 0x0209E63C
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, _0209E7C0 ; =0x021C8F04
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrh r0, [r6, #0x0]
	cmp r0, #0x100
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r0, [r6, #0x2]
	cmp r0, #0x8
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r1, [r6, #0x4]
	ldr r0, _0209E7C4 ; =0x00000406
	cmp r1, r0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r1, [r6, #0x6]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	cmp r4, #0x1
	beq _0209E6D0
	cmp r4, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
_0209E6D0:
	ldrh r1, [r6, #0xe]
	ldrh r5, [r6, #0x10]
	ldr r2, _0209E7C0 ; =0x021C8F04
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r1, r5, asr #0x8
	orr r0, r1, r5, lsl #0x8
	mov r1, r0, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r1, r3, r1, lsr #0x10
	ldr r0, [r2, #0x0]
	ldrh r3, [r6, #0x18]
	ldrh lr, [r6, #0x1a]
	cmp r1, r0
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	moveq r5, #0x1
	mov r3, lr, asr #0x8
	mov r12, r2, lsr #0x10
	orr r2, r3, lr, lsl #0x8
	mov r3, r12, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r2, r3, r2, lsr #0x10
	movne r5, #0x0
	cmp r0, r2
	moveq r7, #0x1
	movne r7, #0x0
	cmp r5, #0x0
	bne _0209E75C
	mov r2, r7
	add r0, r6, #0x8
	bl FUN_0209F12C
_0209E75C:
	cmp r4, #0x1
	bne _0209E780
	cmp r7, #0x0
	beq _0209E780
	mov r0, r6
	bl FUN_0209E7CC
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E780:
	cmp r4, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r7, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r5, #0x0
	ldrne r0, _0209E7C8 ; =0x021C8EAC
	movne r1, #0x1
	strneb r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209E7BC: .word 0x021C8F14
_0209E7C0: .word 0x021C8F04
_0209E7C4: .word 0x00000406
_0209E7C8: .word 0x021C8EAC

	arm_func_start FUN_0209E7CC
FUN_0209E7CC: ; 0x0209E7CC
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r3, #0x200
	add r0, r4, #0x8
	add r1, r4, #0x12
	mov r2, #0xa
	strh r3, [r4, #0x6]
	bl MI_CpuCopy8
	ldr r0, _0209E870 ; =0x021C8F14
	add r1, r4, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r3, _0209E874 ; =0x021C8F04
	add r0, r4, #0x12
	ldr r2, [r3, #0x0]
	sub r1, r4, #0xe
	mov r2, r2, lsr #0x10
	mov r2, r2, lsl #0x10
	mov r12, r2, lsr #0x10
	mov r2, r12, asr #0x8
	orr r2, r2, r12, lsl #0x8
	strh r2, [r4, #0xe]
	ldr r3, [r3, #0x0]
	mov r2, #0x6
	mov r3, r3, lsl #0x10
	mov r12, r3, lsr #0x10
	mov r3, r12, asr #0x8
	orr r3, r3, r12, lsl #0x8
	strh r3, [r4, #0x10]
	bl MI_CpuCopy8
	ldr r0, _0209E870 ; =0x021C8F14
	sub r1, r4, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	sub r0, r4, #0xe
	mov r1, #0x2a
	mov r2, #0x0
	mov r3, r2
	bl FUN_0209F930
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209E870: .word 0x021C8F14
_0209E874: .word 0x021C8F04

	arm_func_start FUN_0209E878
FUN_0209E878: ; 0x0209E878
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc
	mov r7, r2
	ldrb r2, [r7, #0x8]
	mov r9, r0
	mov r8, r1
	cmp r2, #0x0
	mov r6, r3
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r0, _0209EAEC ; =0x021D3498
	ldr r3, _0209EAF0 ; =0x021C8F04
	ldr r1, _0209EAF4 ; =0x021C9160
	ldr r0, [r0, #0x4]
	ldr r12, [r3, #0x0]
	cmp r0, r1
	ldreq r4, _0209EAF8 ; =0x021C8F5E
	ldrne r0, [r7, #0x4c]
	addne r4, r0, #0x22
	ands r0, r6, #0x2
	movne r5, #0x18
	moveq r5, #0x14
	add r1, r5, r8
	mov r2, r1, lsl #0x10
	mov r1, r12, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r12, r1, lsr #0x10
	mov r1, r12, asr #0x8
	orr r1, r1, r12, lsl #0x8
	strh r1, [r4, #-0xc]
	ldr r1, [r3, #0x0]
	mov r12, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x10
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #-0xa]
	ldr r1, [r7, #0x1c]
	mov r3, r12, asr #0x8
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x10
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #-0x8]
	ldr r1, [r7, #0x1c]
	mov r2, r5, lsr #0x2
	mov r1, r1, lsl #0x10
	mov lr, r1, lsr #0x10
	mov r1, lr, asr #0x8
	orr r1, r1, lr, lsl #0x8
	strh r1, [r4, #-0x6]
	mov r1, #0x600
	strh r1, [r4, #-0x4]
	orr r1, r3, r12, lsl #0x8
	strh r1, [r4, #-0x2]
	ldrh r12, [r7, #0xa]
	cmp r0, #0x0
	mov r2, r2, lsl #0x4
	mov r3, r12, asr #0x8
	orr r3, r3, r12, lsl #0x8
	strh r3, [r4, #0x0]
	ldrh r3, [r7, #0x18]
	mov r1, #0x0
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x2]
	ldr r0, [r7, #0x28]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x4]
	ldr r0, [r7, #0x28]
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x6]
	ldr r0, [r7, #0x24]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x8]
	ldr r0, [r7, #0x24]
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0xa]
	strb r2, [r4, #0xc]
	strb r6, [r4, #0xd]
	ldr r2, [r7, #0x3c]
	ldr r0, [r7, #0x44]
	sub r0, r2, r0
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r4, #0xe]
	strh r1, [r4, #0x10]
	strh r1, [r4, #0x12]
	beq _0209EA64
	ldr r1, _0209EAFC ; =0x021C8EB0
	ldrh r0, [r1, #0x0]
	add r0, r0, #0x2040000
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r4, #0x14]
	ldrh r0, [r1, #0x0]
	add r0, r0, #0x2040000
	mov r0, r0, lsl #0x10
	mov r1, r0, lsr #0x10
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	strh r0, [r4, #0x16]
_0209EA64:
	sub r0, r4, #0xc
	add r1, r5, #0xc
	mov r2, #0x0
	bl FUN_0209FBC8
	mov r2, r0
	mov r0, r9
	mov r1, r8
	bl FUN_0209FBC8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl FUN_0209FBAC
	mov r3, r0, asr #0x8
	orr r0, r3, r0, lsl #0x8
	strh r0, [r4, #0x10]
	mov r0, r4
	ldr r4, [r7, #0x1c]
	mov r3, #0x6
	str r4, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r1, r5
	mov r2, r9
	mov r3, r8
	bl FUN_0209ECFC
	ands r0, r6, #0x3
	ldr r0, [r7, #0x28]
	add r1, r7, #0x28
	add r0, r0, r8
	str r0, [r7, #0x28]
	ldrne r0, [r1, #0x0]
	addne r0, r0, #0x1
	strne r0, [r1, #0x0]
	add sp, sp, #0xc
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_0209EAEC: .word 0x021D3498
_0209EAF0: .word 0x021C8F04
_0209EAF4: .word 0x021C9160
_0209EAF8: .word 0x021C8F5E
_0209EAFC: .word 0x021C8EB0

	arm_func_start FUN_0209EB00
FUN_0209EB00:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	ldr r7, _0209EC3C ; =0x021C8F04
	mov r5, r2
	ldr r2, [r7, #0x0]
	mov r6, r1
	mov r1, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x10
	ldr r3, [r5, #0x4c]
	mov r1, r2, asr #0x8
	add r4, r3, #0x22
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #-0xc]
	ldr r1, [r7, #0x0]
	add r2, r6, #0x8
	mov r1, r1, lsl #0x10
	mov r7, r1, lsr #0x10
	mov r1, r7, asr #0x8
	orr r1, r1, r7, lsl #0x8
	strh r1, [r4, #-0xa]
	ldr r1, [r5, #0x1c]
	mov r2, r2, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r7, r1, lsr #0x10
	mov r1, r7, asr #0x8
	orr r1, r1, r7, lsl #0x8
	strh r1, [r4, #-0x8]
	ldr r1, [r5, #0x1c]
	mov r2, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r7, r1, lsr #0x10
	mov r1, r7, asr #0x8
	orr r7, r1, r7, lsl #0x8
	mov r1, r2, asr #0x8
	strh r7, [r4, #-0x6]
	mov r7, #0x1100
	strh r7, [r4, #-0x4]
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #0x4]
	ldrh r1, [r4, #0x4]
	mov r7, r0
	sub r0, r4, #0xc
	strh r1, [r4, #-0x2]
	ldrh lr, [r5, #0x18]
	mov r2, #0x0
	mov r1, #0x14
	mov r12, lr, asr #0x8
	orr r12, r12, lr, lsl #0x8
	strh r12, [r4, #0x2]
	ldrh lr, [r5, #0xa]
	mov r12, lr, asr #0x8
	orr r12, r12, lr, lsl #0x8
	strh r12, [r3, #0x22]
	strh r2, [r4, #0x6]
	bl FUN_0209FBC8
	mov r2, r0
	mov r0, r7
	mov r1, r6
	bl FUN_0209FBC8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl FUN_0209FBAC
	mov r2, r7
	mov r3, r6
	mov r1, r0, asr #0x8
	orr r0, r1, r0, lsl #0x8
	strh r0, [r4, #0x6]
	ldr r1, [r5, #0x1c]
	mov r0, r4
	str r1, [sp, #0x0]
	mov r1, #0x11
	str r1, [sp, #0x4]
	mov r1, #0x8
	bl FUN_0209ECFC
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209EC3C: .word 0x021C8F04

	arm_func_start FUN_0209EC40
FUN_0209EC40:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r5, r2
	ldr r3, [r5, #0x4c]
	mov r6, r1
	mov r1, #0x8
	ldr r2, _0209ECF4 ; =0x021D3498
	strh r1, [r3, #0x22]
	ldr r2, [r2, #0x4]
	add r4, r3, #0x22
	strh r2, [r4, #0x4]
	mov r2, #0x0
	ldr r3, _0209ECF8 ; =0x021C8EB4
	strh r2, [r4, #0x2]
	ldrh lr, [r3, #0x0]
	mov r7, r0
	mov r0, r4
	strh lr, [r5, #0xa]
	ldrh r12, [r3, #0x0]
	add r12, r12, #0x1
	strh r12, [r3, #0x0]
	strh lr, [r4, #0x6]
	bl FUN_0209FBC8
	mov r2, r0
	mov r0, r7
	mov r1, r6
	bl FUN_0209FBC8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl FUN_0209FBAC
	mov r2, r7
	mov r3, r6
	mov r1, r0, asr #0x8
	orr r0, r1, r0, lsl #0x8
	strh r0, [r4, #0x2]
	ldr r1, [r5, #0x1c]
	mov r0, r4
	str r1, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r1, #0x8
	bl FUN_0209ECFC
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209ECF4: .word 0x021D3498
_0209ECF8: .word 0x021C8EB4

	arm_func_start FUN_0209ECFC
FUN_0209ECFC: ; 0x0209ECFC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r10, r0
	mov r0, #0x45
	strb r0, [r10, #-0x14]
	mov r5, #0x0
	ldr r0, _0209EF0C ; =0x021C8EB8
	strb r5, [r10, #-0x13]
	ldrh r7, [r0, #0x0]
	ldr r6, [sp, #0x30]
	ldrb r4, [sp, #0x34]
	add r7, r7, #0x1
	strh r7, [r0, #0x0]
	ldrh r9, [r0, #0x0]
	mov r0, r6, lsr #0x10
	mov r7, #0x80
	mov r8, r9, asr #0x8
	orr r8, r8, r9, lsl #0x8
	strh r8, [r10, #-0x10]
	strb r7, [r10, #-0xc]
	ldr r7, _0209EF10 ; =0x021C8F04
	strb r4, [r10, #-0xb]
	ldr r8, [r7, #0x0]
	mov r4, r0, lsl #0x10
	mov r0, r8, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r8, r0, lsr #0x10
	mov r0, r8, asr #0x8
	orr r0, r0, r8, lsl #0x8
	strh r0, [r10, #-0x8]
	ldr r0, [r7, #0x0]
	mov r8, r4, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r7, r0, lsr #0x10
	mov r4, r7, asr #0x8
	mov r0, r6, lsl #0x10
	orr r9, r4, r7, lsl #0x8
	mov r7, r8, asr #0x8
	mov r4, r0, lsr #0x10
	mov r0, r4, asr #0x8
	strh r9, [r10, #-0x6]
	orr r7, r7, r8, lsl #0x8
	ldr fp, _0209EF14 ; =0x000005C8
	mov r9, r1
	strh r7, [r10, #-0x4]
	orr r0, r0, r4, lsl #0x8
	mov r8, r2
	mov r7, r3
	strh r0, [r10, #-0x2]
	cmp r9, r11
	bls _0209EE74
	mov r4, r10
	cmp r9, r11
	bls _0209EE14
	str r5, [sp, #0x8]
_0209EDD8:
	ldr r1, [sp, #0x8]
	mov r0, r10
	mov r2, r4
	mov r3, r11
	str r6, [sp, #0x0]
	orr r12, r5, #0x2000
	str r12, [sp, #0x4]
	bl FUN_0209EF18
	add r0, r5, #0xb9
	sub r9, r9, r11
	mov r0, r0, lsl #0x10
	cmp r9, r11
	add r4, r4, r11
	mov r5, r0, lsr #0x10
	bhi _0209EDD8
_0209EE14:
	cmp r9, #0x0
	beq _0209EE74
	cmp r7, #0x0
	beq _0209EE48
	mov r0, r10
	mov r2, r4
	mov r3, r9
	str r6, [sp, #0x0]
	orr r4, r5, #0x2000
	mov r1, #0x0
	str r4, [sp, #0x4]
	bl FUN_0209EF18
	b _0209EE64
_0209EE48:
	str r6, [sp, #0x0]
	mov r0, r10
	mov r2, r4
	mov r3, r9
	mov r1, #0x0
	str r5, [sp, #0x4]
	bl FUN_0209EF18
_0209EE64:
	add r0, r5, r9, lsr #0x3
	mov r0, r0, lsl #0x10
	mov r5, r0, lsr #0x10
	mov r9, #0x0
_0209EE74:
	ldr r0, _0209EF14 ; =0x000005C8
	add r1, r9, r7
	cmp r1, r0
	bls _0209EED4
	mov r11, #0x0
_0209EE88:
	ldr r0, _0209EF14 ; =0x000005C8
	mov r1, r9
	sub r4, r0, r9
	mov r0, r10
	mov r2, r8
	mov r3, r4
	str r6, [sp, #0x0]
	orr r9, r5, #0x2000
	str r9, [sp, #0x4]
	bl FUN_0209EF18
	add r0, r5, #0xb9
	mov r1, r0, lsl #0x10
	ldr r0, _0209EF14 ; =0x000005C8
	sub r7, r7, r4
	mov r9, r11
	cmp r7, r0
	add r8, r8, r4
	mov r5, r1, lsr #0x10
	bhi _0209EE88
_0209EED4:
	adds r0, r9, r7
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	str r6, [sp, #0x0]
	mov r0, r10
	mov r1, r9
	mov r2, r8
	mov r3, r7
	str r5, [sp, #0x4]
	bl FUN_0209EF18
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209EF0C: .word 0x021C8EB8
_0209EF10: .word 0x021C8F04
_0209EF14: .word 0x000005C8

	arm_func_start FUN_0209EF18
FUN_0209EF18: ; 0x0209EF18
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r7, r1
	mov r5, r3
	add r1, r7, #0x14
	add r1, r1, r5
	ldr r3, [sp, #0x24]
	mov r1, r1, lsl #0x10
	mov r4, r1, lsr #0x10
	mov r1, r3, lsl #0x10
	mov r3, r4, asr #0x8
	mov r1, r1, lsr #0x10
	mov r8, r0
	orr r3, r3, r4, lsl #0x8
	mov r0, r1, asr #0x8
	strh r3, [r8, #-0x12]
	orr r0, r0, r1, lsl #0x8
	strh r0, [r8, #-0xe]
	mov r3, #0x0
	sub r0, r8, #0x14
	mov r1, #0x14
	mov r6, r2
	strh r3, [r8, #-0xa]
	ldr r4, [sp, #0x20]
	bl FUN_0209FB84
	mov r2, r0, asr #0x8
	ldr r1, _0209F040 ; =0x7F000001
	orr r0, r2, r0, lsl #0x8
	strh r0, [r8, #-0xa]
	cmp r4, r1
	beq _0209EFC4
	ldr r0, _0209F044 ; =0x021C8F04
	ldr r0, [r0, #0x0]
	cmp r4, r0
	beq _0209EFC4
	mov r2, r6
	mov r3, r5
	str r4, [sp, #0x0]
	mov r12, #0x800
	sub r0, r8, #0x14
	add r1, r7, #0x14
	str r12, [sp, #0x4]
	bl FUN_0209F050
_0209EFC4:
	ldr r0, _0209F040 ; =0x7F000001
	cmp r4, r0
	beq _0209EFF8
	ldr r0, _0209F044 ; =0x021C8F04
	ldr r0, [r0, #0x0]
	cmp r4, r0
	beq _0209EFF8
	mov r0, r4
	bl FUN_0209FA54
_0209EFE8: ; 0x0209EFE8
	cmp r0, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
_0209EFF8:
	ldr r0, _0209F048 ; =0x02106230
	sub r1, r8, #0x1c
	mov r2, #0x8
	bl MI_CpuCopy8
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r0, _0209F04C ; =0x021C8F14
	str r6, [sp, #0x0]
	mov r1, r0
	str r5, [sp, #0x4]
	sub r2, r8, #0x1c
	add r3, r7, #0x1c
	bl FUN_0209F6C0
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209F040: .word 0x7F000001
_0209F044: .word 0x021C8F04
_0209F048: .word 0x02106230
_0209F04C: .word 0x021C8F14

	arm_func_start FUN_0209F050
FUN_0209F050: ; 0x0209F050
	stmdb sp!, {r4-r8,lr}
	ldrh r5, [sp, #0x1c]
	ldr r4, [sp, #0x18]
	mov r8, r0
	mov r0, r5, asr #0x8
	orr r12, r0, r5, lsl #0x8
	mov r0, r4
	mov r7, r1
	mov r6, r2
	mov r5, r3
	strh r12, [r8, #-0x2]
	bl FUN_0209FA54
_0209F080: ; 0x0209F080
	cmp r0, #0x0
	bne _0209F0CC
	mov r0, r4
	bl FUN_0209FAB0
	movs r4, r0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	bl FUN_0209F438
_0209F0A0: ; 0x0209F0A0
	cmp r0, #0x0
	bne _0209F0B0
	mov r0, r4
	bl FUN_0209F2AC
_0209F0B0:
	cmp r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	sub r1, r8, #0xe
	mov r2, #0x6
	bl MI_CpuCopy8
	b _0209F0FC
_0209F0CC:
	mov r0, #0x1
	strb r0, [r8, #-0xe]
	mov r1, #0x0
	mov r0, r4, lsr #0x10
	strb r1, [r8, #-0xd]
	mov r1, #0x5e
	strb r1, [r8, #-0xc]
	and r0, r0, #0x7f
	strb r0, [r8, #-0xb]
	mov r0, r4, lsr #0x8
	strb r0, [r8, #-0xa]
	strb r4, [r8, #-0x9]
_0209F0FC:
	ldr r0, _0209F128 ; =0x021C8F14
	sub r1, r8, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	mov r2, r6
	mov r3, r5
	sub r0, r8, #0xe
	add r1, r7, #0xe
	bl FUN_0209F930
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209F128: .word 0x021C8F14

	arm_func_start FUN_0209F12C
FUN_0209F12C: ; 0x0209F12C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r3, _0209F29C ; =0x7F000001
	mov r6, r1
	cmp r6, r3
	mov r7, r0
	mov r4, r2
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, _0209F2A0 ; =0x021C8F04
	ldr r0, [r0, #0x0]
	cmp r6, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r6
	bl FUN_0209FAD8
_0209F174: ; 0x0209F174
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r6
	bl FUN_0209FA54
_0209F18C: ; 0x0209F18C
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	mov r0, r0, lsl #0x10
	ldr r1, _0209F2A4 ; =0x021C8F78
	mov r5, r0, lsr #0x10
	mov r2, #0x0
_0209F1B8:
	ldr r0, [r1, #0x0]
	cmp r6, r0
	bne _0209F1F8
	mov r0, #0xc
	mul r4, r2, r0
	ldr r0, _0209F2A4 ; =0x021C8F78
	ldr r3, _0209F2A8 ; =0x021C8F82
	add r1, r0, r4
	mov r0, r7
	add r1, r1, #0x4
	mov r2, #0x6
	strh r5, [r3, r4]
	bl MI_CpuCopy8
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209F1F8:
	add r2, r2, #0x1
	cmp r2, #0x8
	add r1, r1, #0xc
	blo _0209F1B8
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r12, #0x0
	ldr r4, _0209F2A4 ; =0x021C8F78
	mov r0, r12
	mov r3, r12
_0209F228:
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	moveq r0, r3
	beq _0209F264
	ldrh r1, [r4, #0xa]
	add r4, r4, #0xc
	sub r1, r5, r1
	mov r1, r1, lsl #0x10
	mov r2, r1, asr #0x10
	cmp r2, r12
	movgt r0, r3
	add r3, r3, #0x1
	movgt r12, r1, lsr #0x10
	cmp r3, #0x8
	blo _0209F228
_0209F264:
	mov r1, #0xc
	mul r4, r0, r1
	ldr r3, _0209F2A4 ; =0x021C8F78
	mov r0, r7
	add r1, r3, r4
	add r1, r1, #0x4
	mov r2, #0x6
	str r6, [r3, r4]
	bl MI_CpuCopy8
	ldr r0, _0209F2A8 ; =0x021C8F82
	strh r5, [r0, r4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209F29C: .word 0x7F000001
_0209F2A0: .word 0x021C8F04
_0209F2A4: .word 0x021C8F78
_0209F2A8: .word 0x021C8F82

	arm_func_start FUN_0209F2AC
FUN_0209F2AC:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	mov r8, #0x0
	ldr r4, _0209F334 ; =0x021C8F04
	mov r6, r8
	mov r5, #0x64
_0209F2C8:
	mov r0, r9
	bl FUN_0209F338
	mov r7, r6
_0209F2D4:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r0, r5
	bl OS_Sleep
	mov r0, r9
	bl FUN_0209F438
_0209F2FC: ; 0x0209F2FC
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	add r7, r7, #0x1
	cmp r7, #0x14
	blo _0209F2D4
	add r8, r8, #0x1
	cmp r8, #0x8
	blo _0209F2C8
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_0209F334: .word 0x021C8F04

	arm_func_start FUN_0209F338
FUN_0209F338: ; 0x0209F338
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x30
	mov r4, r0
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x2a
	bl MI_CpuFill8
_0209F354: ; 0x0209F354
	add r0, sp, #0x0
	mov r1, #0xff
	mov r2, #0x6
	bl MI_CpuFill8
	ldr r0, _0209F428 ; =0x021C8F14
	add r1, sp, #0x6
	mov r2, #0x6
	bl MI_CpuCopy8
	mov r0, #0x1
	ldr r1, _0209F42C ; =0x00000608
	strb r0, [sp, #0xf]
	strh r1, [sp, #0xc]
	strb r0, [sp, #0x15]
	mov r0, #0x8
	ldr r1, _0209F430 ; =0x00000406
	strb r0, [sp, #0x10]
	strh r1, [sp, #0x12]
	ldr r0, _0209F428 ; =0x021C8F14
	add r1, sp, #0x16
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r0, _0209F434 ; =0x021C8F04
	mov r1, r4, lsr #0x10
	ldr r3, [r0, #0x0]
	mov r0, r1, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r4, lsl #0x10
	mov r1, r0, lsr #0x10
	mov r0, r3, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	mov r0, r3, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r4, asr #0x8
	orr r0, r0, r4, lsl #0x8
	strh r0, [sp, #0x1c]
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [sp, #0x1e]
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [sp, #0x26]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r2, #0x0
	strh r0, [sp, #0x28]
	add r0, sp, #0x0
	mov r1, #0x2a
	mov r3, r2
	bl FUN_0209F930
	add sp, sp, #0x30
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209F428: .word 0x021C8F14
_0209F42C: .word 0x00000608
_0209F430: .word 0x00000406
_0209F434: .word 0x021C8F04

	arm_func_start FUN_0209F438
FUN_0209F438:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl OS_DisableInterrupts
	ldr r1, _0209F504 ; =0x7F000001
	mov r4, r0
	cmp r7, r1
	mov r5, #0x0
	beq _0209F46C
	ldr r0, _0209F508 ; =0x021C8F04
	ldr r0, [r0, #0x0]
	cmp r7, r0
	bne _0209F474
_0209F46C:
	ldr r5, _0209F50C ; =0x021C8F14
	b _0209F4EC
_0209F474:
	mov r0, r7
	bl FUN_0209FA68
_0209F47C: ; 0x0209F47C
	cmp r0, #0x0
	bne _0209F494
	mov r0, r7
	bl FUN_0209FA54
_0209F48C: ; 0x0209F48C
	cmp r0, #0x0
	beq _0209F49C
_0209F494:
	ldr r5, _0209F510 ; =0x0210621C
	b _0209F4EC
_0209F49C:
	ldr r1, _0209F514 ; =0x021C8F78
	mov r6, r5
_0209F4A4:
	ldr r0, [r1, #0x0]
	cmp r7, r0
	bne _0209F4DC
	bl OS_GetTick
	mov r2, #0xc
	mul r3, r6, r2
	ldr r2, _0209F514 ; =0x021C8F78
	mov r5, r0, lsr #0x10
	add r0, r2, r3
	ldr r2, _0209F518 ; =0x021C8F82
	orr r5, r5, r1, lsl #0x10
	strh r5, [r2, r3]
	add r5, r0, #0x4
	b _0209F4EC
_0209F4DC:
	add r6, r6, #0x1
	cmp r6, #0x8
	add r1, r1, #0xc
	blo _0209F4A4
_0209F4EC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209F504: .word 0x7F000001
_0209F508: .word 0x021C8F04
_0209F50C: .word 0x021C8F14
_0209F510: .word 0x0210621C
_0209F514: .word 0x021C8F78
_0209F518: .word 0x021C8F82

	arm_func_start FUN_0209F51C
FUN_0209F51C: ; 0x0209F51C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r2, _0209F570 ; =0x021C8EE4
	ldr r1, _0209F574 ; =0x021C8F0C
	ldr lr, [r2, #0x0]
	ldr r12, [r1, #0x0]
	ldr r3, [r2, #0x0]
	ldr r1, _0209F578 ; =0x021C8F10
	ldrh r3, [r12, r3]
	add r3, lr, r3
	str r3, [r2, #0x0]
	ldr r3, [r2, #0x0]
	ldr r1, [r1, #0x0]
	cmp r3, r1
	movcs r1, #0x0
	strcs r1, [r2, #0x0]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209F570: .word 0x021C8EE4
_0209F574: .word 0x021C8F0C
_0209F578: .word 0x021C8F10

	arm_func_start FUN_0209F57C
FUN_0209F57C: ; 0x0209F57C
	stmdb sp!, {r4-r10,lr}
	mov r6, r0
	bl OS_DisableInterrupts
	ldr sl, _0209F644 ; =0x021C8EE4
	ldr sb, _0209F648 ; =0x021C8EDC
	ldr r2, [r10, #0x0]
	ldr r1, [r9, #0x0]
	mov r5, r0
	cmp r2, r1
	bne _0209F5D4
	ldr r8, _0209F64C ; =0x021D3498
	ldr r7, _0209F650 ; =0x021C8F08
	mov r4, #0x0
_0209F5B0:
	ldr r1, [r8, #0x4]
	mov r0, r4
	str r1, [r7, #0x0]
	bl OS_SleepThread
	str r4, [r7, #0x0]
	ldr r1, [r10, #0x0]
	ldr r0, [r9, #0x0]
	cmp r1, r0
	beq _0209F5B0
_0209F5D4:
	mov r0, r5
	bl OS_RestoreInterrupts
	ldr r0, _0209F654 ; =0x021C8F0C
	ldr r5, [r0, #0x0]
	ldr r0, _0209F644 ; =0x021C8EE4
	ldr r1, _0209F658 ; =0x021C8F10
	mov r3, #0x0
_0209F5F0:
	ldr r4, [r1, #0x0]
	ldr r2, [r0, #0x0]
	sub r2, r4, r2
	cmp r2, #0x2
	strcc r3, [r0, #0x0]
	ldr r2, [r0, #0x0]
	ldrh r2, [r5, r2]
	cmp r2, #0x0
	streq r3, [r0, #0x0]
	cmp r2, #0x0
	beq _0209F5F0
	sub r0, r2, #0x2
	ldr r1, _0209F654 ; =0x021C8F0C
	str r0, [r6, #0x0]
	ldr r0, _0209F644 ; =0x021C8EE4
	ldr r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r1, r0
	add r0, r0, #0x2
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_0209F644: .word 0x021C8EE4
_0209F648: .word 0x021C8EDC
_0209F64C: .word 0x021D3498
_0209F650: .word 0x021C8F08
_0209F654: .word 0x021C8F0C
_0209F658: .word 0x021C8F10

	arm_func_start FUN_0209F65C
FUN_0209F65C: ; 0x0209F65C
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	mov r12, #0x0
	str r12, [sp, #0x0]
	str r12, [sp, #0x4]
	bl FUN_0209F6C0
	ldr r0, _0209F6BC ; =0x021C8F08
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0xc
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r0, [r0, #0x0]
	bl OS_IsThreadTerminated
_0209F694: ; 0x0209F694
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _0209F6BC ; =0x021C8F08
	ldr r0, [r0, #0x0]
	bl OS_WakeupThreadDirect
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209F6BC: .word 0x021C8F08

	arm_func_start FUN_0209F6C0
FUN_0209F6C0: ; 0x0209F6C0
	stmdb sp!, {r4-r8,lr}
	ldr r4, _0209F918 ; =0x021C8F0C
	mov r7, r0
	ldr r0, [r4, #0x0]
	mov r6, r2
	mov r5, r3
	cmp r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r2, _0209F91C ; =0x021C8F10
	ldr r2, [r2, #0x0]
	cmp r2, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r2, [sp, #0x1c]
	add r2, r5, r2
	cmp r2, #0x8
	ldmccia sp!, {r4-r8,lr}
	bxcc lr
	ldr r3, _0209F920 ; =0x000005E4
	cmp r2, r3
	ldmhiia sp!, {r4-r8,lr}
	bxhi lr
	ldr r3, _0209F924 ; =0x02106230
	ldrb r8, [r6, #0x0]
	ldrb r4, [r3, #0x0]
	cmp r8, r4
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r8, [r6, #0x1]
	ldrb r4, [r3, #0x1]
	cmp r8, r4
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r4, [r6, #0x2]
	ldrb r3, [r3, #0x2]
	cmp r4, r3
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r3, [r6, #0x6]
	cmp r3, #0x8
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r3, [r6, #0x7]
	cmp r3, #0x0
	beq _0209F784
	cmp r3, #0x6
	ldmneia sp!, {r4-r8,lr}
	bxne lr
_0209F784:
	ldr r4, _0209F928 ; =0x021C8EDC
	add r2, r2, #0x9
	bic r2, r2, #0x1
	ldr lr, [r4, #0x0]
	mov r3, r2, lsl #0x10
	ldr ip, _0209F92C ; =0x021C8EE4
	ldr r8, [r4, #0x0]
	ldr r4, [r12, #0x0]
	mov r2, r3, lsr #0x10
	cmp r8, r4
	add r4, lr, r3, lsr #0x10
	bhs _0209F7C4
	ldr r3, [r12, #0x0]
	cmp r3, r4
	ldmlsia sp!, {r4-r8,lr}
	bxls lr
_0209F7C4:
	ldr r3, _0209F91C ; =0x021C8F10
	ldr r8, [r3, #0x0]
	cmp r4, r8
	bne _0209F7F0
	ldr r3, _0209F92C ; =0x021C8EE4
	mov r4, #0x0
	ldr r3, [r3, #0x0]
	cmp r3, #0x0
	bne _0209F814
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209F7F0:
	ldr r3, [r3, #0x0]
	cmp r4, r3
	bls _0209F814
	ldr r3, _0209F92C ; =0x021C8EE4
	mov r4, r2
	ldr r3, [r3, #0x0]
	cmp r3, r2
	ldmlsia sp!, {r4-r8,lr}
	bxls lr
_0209F814:
	ldr ip, _0209F928 ; =0x021C8EDC
	ldr r3, _0209F91C ; =0x021C8F10
	ldr lr, [r12, #0x0]
	ldr r8, [r3, #0x0]
	add lr, lr, r2
	cmp lr, r8
	bls _0209F858
	ldr r8, [r3, #0x0]
	ldr r3, [r12, #0x0]
	sub r3, r8, r3
	cmp r3, #0x2
	ldrcs r3, [r12, #0x0]
	movcs r8, #0x0
	strcsh r8, [r0, r3]
	ldr r0, _0209F928 ; =0x021C8EDC
	mov r3, #0x0
	str r3, [r0, #0x0]
_0209F858:
	ldr ip, _0209F918 ; =0x021C8F0C
	ldr r3, _0209F928 ; =0x021C8EDC
	ldr r8, [r12, #0x0]
	ldr lr, [r3, #0x0]
	mov r0, r1
	strh r2, [r8, lr]
	ldr r12, [r12, #0x0]
	ldr r1, [r3, #0x0]
	mov r2, #0x6
	add r1, r12, r1
	add r1, r1, #0x2
	bl MI_CpuCopy8
	ldr r1, _0209F918 ; =0x021C8F0C
	ldr r0, _0209F928 ; =0x021C8EDC
	ldr r2, [r1, #0x0]
	ldr r1, [r0, #0x0]
	mov r0, r7
	add r1, r2, r1
	add r1, r1, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r1, _0209F918 ; =0x021C8F0C
	ldr r0, _0209F928 ; =0x021C8EDC
	ldr r2, [r1, #0x0]
	ldr r1, [r0, #0x0]
	add r0, r6, #0x6
	add r1, r2, r1
	add r1, r1, #0xe
	sub r2, r5, #0x6
	bl MI_CpuCopy8
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	beq _0209F908
	ldr r2, [sp, #0x1c]
	cmp r2, #0x0
	beq _0209F908
	ldr r3, _0209F918 ; =0x021C8F0C
	ldr r1, _0209F928 ; =0x021C8EDC
	ldr r3, [r3, #0x0]
	ldr r1, [r1, #0x0]
	add r1, r3, r1
	add r1, r1, #0x8
	add r1, r1, r5
	bl MI_CpuCopy8
_0209F908:
	ldr r0, _0209F928 ; =0x021C8EDC
	str r4, [r0, #0x0]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209F918: .word 0x021C8F0C
_0209F91C: .word 0x021C8F10
_0209F920: .word 0x000005E4
_0209F924: .word 0x02106230
_0209F928: .word 0x021C8EDC
_0209F92C: .word 0x021C8EE4

	arm_func_start FUN_0209F930
FUN_0209F930: ; 0x0209F930
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	add r1, r6, r5
	mov r4, r3
	cmp r1, r2
	beq _0209F958
	mov r0, r2
	mov r2, r4
	bl MI_CpuCopy8
_0209F958:
	ldr r0, _0209F998 ; =0x02106230
	add r1, r6, #0x6
	mov r2, #0x6
	bl MI_CpuCopy8
	add r2, r5, r4
	mov r0, r6
	add r1, r6, #0x6
	sub r2, r2, #0x6
	bl FUN_020A8644
_0209F97C: ; 0x0209F97C
	cmp r0, #0x0
	movlt r1, #0x1
	ldr r0, _0209F99C ; =0x021C8EA8
	movge r1, #0x0
	strb r1, [r0, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209F998: .word 0x02106230
_0209F99C: .word 0x021C8EA8

	arm_func_start FUN_0209F9A0
FUN_0209F9A0:
	mov r12, #0x0
_0209F9A4:
	ldrh r3, [r0], #0x2
	ldrh r2, [r1], #0x2
	cmp r3, r2
	movne r0, #0x1
	bxne lr
	add r12, r12, #0x1
	cmp r12, #0x3
	blt _0209F9A4
	mov r0, #0x0
	bx lr

	arm_func_start FUN_0209F9CC
FUN_0209F9CC:
	stmdb sp!, {r4-r6,lr}
	ldr r1, _0209FA4C ; =0x021C8F04
	mov r5, #0x1
	ldr r1, [r1, #0x0]
	mov r6, r0
	mov r4, r5
	mov r2, r5
	mov r0, r5
	cmp r1, #0x0
	beq _0209F9FC
	cmp r6, r1
	movne r0, #0x0
_0209F9FC:
	cmp r0, #0x0
	bne _0209FA10
	ldr r0, _0209FA50 ; =0x7F000001
	cmp r6, r0
	movne r2, #0x0
_0209FA10:
	cmp r2, #0x0
	bne _0209FA28
	mov r0, r6
	bl FUN_0209FA68
_0209FA20: ; 0x0209FA20
	cmp r0, #0x0
	moveq r4, #0x0
_0209FA28:
	cmp r4, #0x0
	bne _0209FA40
	mov r0, r6
	bl FUN_0209FA54
_0209FA38: ; 0x0209FA38
	cmp r0, #0x0
	moveq r5, #0x0
_0209FA40:
	mov r0, r5
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209FA4C: .word 0x021C8F04
_0209FA50: .word 0x7F000001

	arm_func_start FUN_0209FA54
FUN_0209FA54:
	and r0, r0, #0xf0000000
	cmp r0, #0xe0000000
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

	arm_func_start FUN_0209FA68
FUN_0209FA68:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, #0x0
	bl FUN_0209FAD8
_0209FA7C: ; 0x0209FA7C
	cmp r0, #0x0
	beq _0209FA9C
	ldr r0, _0209FAAC ; =0x021C8ED0
	ldr r0, [r0, #0x0]
	mvn r1, r0
	and r0, r1, r5
	cmp r1, r0
	moveq r4, #0x1
_0209FA9C:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209FAAC: .word 0x021C8ED0

	arm_func_start FUN_0209FAB0
FUN_0209FAB0:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_0209FAD8
_0209FABC: ; 0x0209FABC
	cmp r0, #0x0
	ldreq r0, _0209FAD4 ; =0x021C8EE0
	ldreq r4, [r0, #0x0]
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209FAD4: .word 0x021C8EE0

	arm_func_start FUN_0209FAD8
FUN_0209FAD8:
	mvn r1, #0x0
	cmp r0, r1
	mov r12, #0x1
	beq _0209FB14
	ldr r1, _0209FB1C ; =0x7F000001
	cmp r0, r1
	beq _0209FB14
	ldr r2, _0209FB20 ; =0x021C8ED0
	ldr r1, _0209FB24 ; =0x021C8F04
	ldr r3, [r2, #0x0]
	ldr r1, [r1, #0x0]
	and r2, r0, r3
	and r0, r1, r3
	cmp r2, r0
	movne r12, #0x0
_0209FB14:
	mov r0, r12
	bx lr
	.balign 4
_0209FB1C: .word 0x7F000001
_0209FB20: .word 0x021C8ED0
_0209FB24: .word 0x021C8F04

	arm_func_start FUN_0209FB28
FUN_0209FB28:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r2
	mov r2, r3
	mov r5, r1
	bl FUN_0209FBC8
	mov r2, r0
	add r0, r4, #0xc
	mov r1, #0x8
	bl FUN_0209FBC8
	add r1, r0, r5
	ands r0, r1, #0x10000
	ldrne r0, _0209FB80 ; =0x0000FFFF
	addne r1, r1, #0x1
	andne r1, r1, r0
	ldr r0, _0209FB80 ; =0x0000FFFF
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209FB80: .word 0x0000FFFF

	arm_func_start FUN_0209FB84
FUN_0209FB84: ; 0x0209FB84
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x0
	bl FUN_0209FBC8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl FUN_0209FBAC
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209FBAC
FUN_0209FBAC: ; 0x0209FBAC
	ldr r1, _0209FBC4 ; =0x0000FFFF
	eor r0, r0, r1
	mov r0, r0, lsl #0x10
	movs r0, r0, lsr #0x10
	moveq r0, r1
	bx lr
	.balign 4
_0209FBC4: .word 0x0000FFFF

	arm_func_start FUN_0209FBC8
FUN_0209FBC8: ; 0x0209FBC8
	ands r3, r0, #0x1
	beq _0209FC00
	cmp r1, #0x1
	bls _0209FC54
_0209FBD8:
	ldrb r12, [r0, #0x0]
	ldrb r3, [r0, #0x1]
	sub r1, r1, #0x2
	cmp r1, #0x1
	orr r3, r3, r12, lsl #0x8
	mov r3, r3, lsl #0x10
	add r2, r2, r3, lsr #0x10
	add r0, r0, #0x2
	bhi _0209FBD8
	b _0209FC54
_0209FC00:
	mov r2, r2, lsl #0x10
	mov r3, r2, lsr #0x10
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r1, #0x1
	mov r2, r2, lsr #0x10
	bls _0209FC38
_0209FC20:
	ldrh r3, [r0, #0x0]
	sub r1, r1, #0x2
	cmp r1, #0x1
	add r2, r2, r3
	add r0, r0, #0x2
	bhi _0209FC20
_0209FC38:
	ldr r3, _0209FC7C ; =0x00FF00FF
	ldr ip, _0209FC80 ; =0xFF00FF00
	and r3, r3, r2, lsr #0x8
	and r2, r12, r2, lsl #0x8
	orr r3, r3, r2
	mov r2, r3, lsr #0x10
	orr r2, r2, r3, lsl #0x10
_0209FC54:
	cmp r1, #0x0
	ldrneb r0, [r0, #0x0]
	addne r2, r2, r0, lsl #0x8
	ldr r0, _0209FC84 ; =0x0000FFFF
	and r0, r2, r0
	add r0, r0, r2, lsr #0x10
	add r0, r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bx lr
	.balign 4
_0209FC7C: .word 0x00FF00FF
_0209FC80: .word 0xFF00FF00
_0209FC84: .word 0x0000FFFF

	arm_func_start FUN_0209FC88
FUN_0209FC88: ; 0x0209FC88
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r2, _0209FCB8 ; =0x02106218
	ldr r0, _0209FCBC ; =0x021C9160
	mov r1, r4
	str r4, [r2, #0x0]
	bl OS_SetThreadPriority
	ldr r0, _0209FCC0 ; =0x021C90A0
	mov r1, r4
	bl OS_SetThreadPriority
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209FCB8: .word 0x02106218
_0209FCBC: .word 0x021C9160
_0209FCC0: .word 0x021C90A0

	arm_func_start FUN_0209FCC4
FUN_0209FCC4:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_0209FD34
	ldr r0, _0209FD10 ; =0x021C90A0
	bl OS_JoinThread
	ldr r0, _0209FD14 ; =0x021C9160
	bl OS_DestroyThread
	ldr r1, _0209FD18 ; =0x021C8F08
	mov r0, #0x0
	str r0, [r1, #0x0]
	bl FUN_020A0098
	ldr r1, _0209FD1C ; =0x021C8F0C
	mov r2, #0x0
	ldr r0, _0209FD20 ; =0x021C8F10
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209FD10: .word 0x021C90A0
_0209FD14: .word 0x021C9160
_0209FD18: .word 0x021C8F08
_0209FD1C: .word 0x021C8F0C
_0209FD20: .word 0x021C8F10

	arm_func_start FUN_0209FD24
FUN_0209FD24: ; 0x0209FD24
	ldr r1, _0209FD30 ; =0x021C8EF0
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_0209FD30: .word 0x021C8EF0

	arm_func_start FUN_0209FD34
FUN_0209FD34:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	mov r5, r0
	ldr r0, _0209FD8C ; =0x021C90A0
	bl OS_IsThreadTerminated
	movs r4, r0
	bne _0209FD74
	ldr r1, _0209FD90 ; =0x021C8EF8
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _0209FD74
	ldr r0, _0209FD8C ; =0x021C90A0
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_WakeupThreadDirect
_0209FD74:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209FD8C: .word 0x021C90A0
_0209FD90: .word 0x021C8EF8

	arm_func_start FUN_0209FD94
FUN_0209FD94: ; 0x0209FD94
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldr r0, _0209FFD4 ; =0x02000BEC
	bl OSi_ReferSymbol
	ldr r12, [r4, #0x14]
	ldr r6, [r4, #0x18]
	mov r1, #0x0
	cmp r6, r1
	cmpeq r12, r1
	beq _0209FDEC
	ldr r0, _0209FFD8 ; =0x021C8F24
	ldr r5, _0209FFDC ; =0x6C078965
	ldr r3, _0209FFE0 ; =0x5D588B65
	ldr r2, _0209FFE4 ; =0x00269EC3
	str r12, [r0, #0x0]
	str r6, [r0, #0x4]
	str r5, [r0, #0x8]
	str r3, [r0, #0xc]
	str r2, [r0, #0x10]
	str r1, [r0, #0x14]
	b _0209FE1C
_0209FDEC:
	bl OS_GetTick
	ldr r2, _0209FFD8 ; =0x021C8F24
	ldr ip, _0209FFDC ; =0x6C078965
	ldr r6, _0209FFE0 ; =0x5D588B65
	ldr r5, _0209FFE4 ; =0x00269EC3
	mov r3, #0x0
	str r0, [r2, #0x0]
	str r1, [r2, #0x4]
	str r12, [r2, #0x8]
	str r6, [r2, #0xc]
	str r5, [r2, #0x10]
	str r3, [r2, #0x14]
_0209FE1C:
	ldr r2, [r4, #0x4]
	cmp r2, #0x0
	beq _0209FE4C
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _0209FE4C
	ldr r1, _0209FFE8 ; =0x021C8EC8
	ldr r0, _0209FFEC ; =0x021C8EF4
	str r2, [r1, #0x0]
	ldr r1, [r4, #0x8]
	str r1, [r0, #0x0]
	b _0209FE60
_0209FE4C:
	ldr r2, _0209FFF0 ; =FUN_020A0058
	ldr r1, _0209FFE8 ; =0x021C8EC8
	ldr r0, _0209FFEC ; =0x021C8EF4
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
_0209FE60:
	ldr r1, [r4, #0x0]
	ldr r0, _0209FFF4 ; =0x021C8EC4
	ldr ip, _0209FFD8 ; =0x021C8F24
	str r1, [r0, #0x0]
	ldr r1, [r4, #0x24]
	ldr r3, [r12, #0x8]
	cmp r1, #0x0
	ldrne r0, _0209FFF8 ; =0x021C8EB0
	strneh r1, [r0, #0x0]
	ldreq r1, _0209FFFC ; =0x000005B4
	ldreq r0, _0209FFF8 ; =0x021C8EB0
	streqh r1, [r0, #0x0]
	ldr r2, [r4, #0x28]
	ldr r1, _020A0000 ; =0x021C8EE8
	ldr r0, _020A0004 ; =0x021C8ED8
	str r2, [r1, #0x0]
	ldr r1, [r4, #0x2c]
	ldr r2, [r12, #0x0]
	str r1, [r0, #0x0]
	ldr r1, [r4, #0xc]
	umull lr, r5, r3, r2
	cmp r1, #0x0
	ldrne r0, _020A0008 ; =0x021C8ECC
	strne r1, [r0, #0x0]
	ldreq r1, _0209FFF0 ; =FUN_020A0058
	ldreq r0, _020A0008 ; =0x021C8ECC
	streq r1, [r0, #0x0]
	ldr r1, [r4, #0x10]
	cmp r1, #0x0
	ldrne r0, _020A000C ; =0x021C8EFC
	strne r1, [r0, #0x0]
	ldreq r1, _020A0010 ; =FUN_020A0050
	ldreq r0, _020A000C ; =0x021C8EFC
	streq r1, [r0, #0x0]
	ldr r1, [r12, #0x4]
	ldr r0, _020A0014 ; =0x00000F88
	mla r5, r3, r1, r5
	ldr r1, [r12, #0xc]
	ldr r3, [r12, #0x10]
	mla r5, r1, r2, r5
	adds r2, r3, lr
	ldr r1, [r12, #0x14]
	mov r3, #0x0
	adc r1, r1, r5
	umull lr, r5, r1, r0
	mla r5, r1, r3, r5
	mla r5, r3, r0, r5
	ldr r6, [r4, #0x1c]
	ldr r0, _020A0018 ; =0x021C8F0C
	ldr lr, _020A001C ; =0x021C8F10
	str r6, [r0, #0x0]
	ldr r4, [r4, #0x20]
	ldr r0, _020A0020 ; =0x021C8EE4
	str r4, [lr, #0x0]
	str r3, [r0, #0x0]
	ldr lr, _020A0024 ; =0x021C8EDC
	ldr r4, _020A0028 ; =0x021C8EBC
	add r5, r5, #0x400
	ldr r0, _020A002C ; =0x021C8F14
	str r3, [lr, #0x0]
	str r2, [r12, #0x0]
	str r1, [r12, #0x4]
	strh r5, [r4, #0x0]
	bl OS_GetMacAddress
	ldr r0, _020A0030 ; =0x021C8EAC
	mov r2, #0x0
	strb r2, [r0, #0x0]
	mov r1, #0x800
	str r1, [sp, #0x0]
	ldr r0, _020A0034 ; =0x02106218
	ldr r1, _020A0038 ; =FUN_0209CD3C
	ldr r4, [r0, #0x0]
	ldr r0, _020A003C ; =0x021C9160
	ldr r3, _020A0040 ; =0x021CA6E0
	str r4, [sp, #0x4]
	bl OS_CreateThread
	mov r1, #0x800
	ldr r0, _020A0034 ; =0x02106218
	str r1, [sp, #0x0]
	ldr r1, [r0, #0x0]
	ldr r0, _020A0044 ; =0x021C90A0
	str r1, [sp, #0x4]
	ldr r1, _020A0048 ; =FUN_0209BA80
	ldr r3, _020A004C ; =0x021C9EE0
	mov r2, #0x0
	bl OS_CreateThread
	ldr r0, _020A003C ; =0x021C9160
	bl OS_WakeupThreadDirect
	ldr r0, _020A0044 ; =0x021C90A0
	bl OS_WakeupThreadDirect
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209FFD4: .word 0x02000BEC
_0209FFD8: .word 0x021C8F24
_0209FFDC: .word 0x6C078965
_0209FFE0: .word 0x5D588B65
_0209FFE4: .word 0x00269EC3
_0209FFE8: .word 0x021C8EC8
_0209FFEC: .word 0x021C8EF4
_0209FFF0: .word FUN_020A0058
_0209FFF4: .word 0x021C8EC4
_0209FFF8: .word 0x021C8EB0
_0209FFFC: .word 0x000005B4
_020A0000: .word 0x021C8EE8
_020A0004: .word 0x021C8ED8
_020A0008: .word 0x021C8ECC
_020A000C: .word 0x021C8EFC
_020A0010: .word FUN_020A0050
_020A0014: .word 0x00000F88
_020A0018: .word 0x021C8F0C
_020A001C: .word 0x021C8F10
_020A0020: .word 0x021C8EE4
_020A0024: .word 0x021C8EDC
_020A0028: .word 0x021C8EBC
_020A002C: .word 0x021C8F14
_020A0030: .word 0x021C8EAC
_020A0034: .word 0x02106218
_020A0038: .word FUN_0209CD3C
_020A003C: .word 0x021C9160
_020A0040: .word 0x021CA6E0
_020A0044: .word 0x021C90A0
_020A0048: .word FUN_0209BA80
_020A004C: .word 0x021C9EE0

	arm_func_start FUN_020A0050
FUN_020A0050: ; 0x020A0050
	mov r0, #0x1
	bx lr

	arm_func_start FUN_020A0058
FUN_020A0058: ; 0x020A0058
	bx lr

	arm_func_start FUN_020A005C
FUN_020A005C:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020A0094 ; =0x021C8ED8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020A0084
	bl OS_YieldThread
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A0084:
	bl OS_Sleep
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A0094: .word 0x021C8ED8

	arm_func_start FUN_020A0098
FUN_020A0098: ; 0x020A0098
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r1, _020A01B8 ; =0x021C8F04
	ldr r5, _020A01BC ; =0x021C8EC0
	ldr r1, [r1, #0x0]
	ldr r3, _020A01C0 ; =0x021C8F1C
	cmp r1, #0x0
	mov r1, #0x0
	movne r6, #0x1
	ldr ip, _020A01C4 ; =0x021C8ED0
	ldr r2, _020A01C8 ; =0x021C8ED4
	moveq r6, #0x0
	ldr lr, _020A01B8 ; =0x021C8F04
	ldr r4, _020A01CC ; =0x021C8EE0
	cmp r6, #0x0
	str r1, [r12, #0x0]
	str r1, [r3, #0x0]
	str r1, [r3, #0x4]
	str r1, [r2, #0x0]
	addeq sp, sp, #0x4
	str r0, [r5, #0x0]
	str r1, [lr, #0x0]
	str r1, [r4, #0x0]
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, _020A01D0 ; =0x021C8F78
	mov r2, #0x60
	bl MI_CpuFill8
	ldr r0, _020A01D4 ; =0x021D3498
	ldr r5, [r0, #0x8]
	cmp r5, #0x0
	beq _020A016C
	mov r4, #0x0
_020A011C:
	ldr r1, [r5, #0xa4]
	cmp r1, #0x0
	beq _020A0160
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _020A0160
	ldrb r0, [r1, #0x8]
	cmp r0, #0xa
	beq _020A0148
	cmp r0, #0xb
	strneb r4, [r1, #0x8]
_020A0148:
	ldr r0, [r1, #0x4]
	cmp r0, #0x0
	beq _020A0160
	str r4, [r1, #0x4]
	ldr r0, [r1, #0x0]
	bl OS_WakeupThreadDirect
_020A0160:
	ldr r5, [r5, #0x68]
	cmp r5, #0x0
	bne _020A011C
_020A016C:
	ldr r6, _020A01D8 ; =0x021C9520
	mov r7, #0x0
	ldr r4, _020A01DC ; =0x021C8EF4
	mov r5, r7
_020A017C:
	ldrh r0, [r6, #0x4]
	cmp r0, #0x0
	beq _020A0198
	ldr r0, [r6, #0x34]
	ldr r1, [r4, #0x0]
	blx r1
	strh r5, [r6, #0x4]
_020A0198:
	add r7, r7, #0x1
	cmp r7, #0x8
	add r6, r6, #0x38
	blt _020A017C
	bl FUN_020A01E0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A01B8: .word 0x021C8F04
_020A01BC: .word 0x021C8EC0
_020A01C0: .word 0x021C8F1C
_020A01C4: .word 0x021C8ED0
_020A01C8: .word 0x021C8ED4
_020A01CC: .word 0x021C8EE0
_020A01D0: .word 0x021C8F78
_020A01D4: .word 0x021D3498
_020A01D8: .word 0x021C9520
_020A01DC: .word 0x021C8EF4

	arm_func_start FUN_020A01E0
FUN_020A01E0: ; 0x020A01E0
	ldr ip, _020A01F4 ; =MI_CpuFill8
	ldr r0, _020A01F8 ; =0x021CA6FC
	mov r1, #0x0
	mov r2, #0x170
	bx r12
	.balign 4
_020A01F4: .word MI_CpuFill8
_020A01F8: .word 0x021CA6FC

	arm_func_start FUN_020A01FC
FUN_020A01FC: ; 0x020A01FC
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r4, _020A02E0 ; =0x021CA6FC
	mov r6, #0x0
	mov r2, r6
	ldr r1, _020A02E4 ; =0x000003BD
_020A0218:
	ldrb r3, [r4, #0x5a]
	cmp r3, #0x0
	beq _020A0234
	ldr r3, [r4, #0x50]
	sub r3, r5, r3
	cmp r3, r1
	strgtb r2, [r4, #0x5a]
_020A0234:
	add r6, r6, #0x1
	cmp r6, #0x4
	add r4, r4, #0x5c
	blt _020A0218
	bl OS_RestoreInterrupts
	ldr r0, _020A02E8 ; =0x021D3498
	ldr r4, [r0, #0x8]
	cmp r4, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r6, #0x0
_020A0260:
	ldr r1, [r4, #0xa4]
	cmp r1, #0x0
	beq _020A02CC
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _020A02CC
	ldrb r0, [r1, #0x9]
	cmp r0, #0x0
	beq _020A02CC
	ldrb r0, [r1, #0x8]
	cmp r0, #0x4
	bne _020A02CC
	ldr r0, [r1, #0xc]
	ldrb r0, [r0, #0x455]
	cmp r0, #0x8
	bhs _020A02CC
	ldr r0, [r1, #0x10]
	sub r0, r5, r0
	cmp r0, #0xef
	ble _020A02CC
	ldr r0, [r1, #0x4]
	cmp r0, #0x2
	bne _020A02CC
	strb r6, [r1, #0x8]
	str r6, [r1, #0x4]
	ldr r0, [r1, #0x0]
	bl OS_WakeupThreadDirect
_020A02CC:
	ldr r4, [r4, #0x68]
	cmp r4, #0x0
	bne _020A0260
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A02E0: .word 0x021CA6FC
_020A02E4: .word 0x000003BD
_020A02E8: .word 0x021D3498

	arm_func_start FUN_020A02EC
FUN_020A02EC:
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _020A0318 ; =0x02000C04
	bl OSi_ReferSymbol
	ldr r0, _020A031C ; =0x021D3498
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xa4]
	cmp r0, #0x0
	strneb r4, [r0, #0x9]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A0318: .word 0x02000C04
_020A031C: .word 0x021D3498

	arm_func_start FUN_020A0320
FUN_020A0320: ; 0x020A0320
	stmdb sp!, {r4,lr}
	ldr r4, [r0, #0xc]
	mov r0, #0x0
	strb r0, [r4, #0x455]
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	beq _020A0348
	ldr r1, _020A0358 ; =0x021C8EF4
	ldr r1, [r1, #0x0]
	blx r1
_020A0348:
	mov r0, #0x0
	str r0, [r4, #0x824]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A0358: .word 0x021C8EF4

	arm_func_start FUN_020A035C
FUN_020A035C: ; 0x020A035C
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x20
	mov r5, r0
	ldr r4, [r5, #0xc]
	ldrb r0, [r4, #0x455]
	cmp r0, #0x8
	bne _020A03CC
	mov r12, #0x0
	mov r6, #0x15
	mov lr, #0x3
	mov r3, #0x2
	mov r2, #0x1
	add r1, sp, #0x4
	mov r0, r4
	strb r6, [sp, #0x4]
	strb lr, [sp, #0x5]
	strb r12, [sp, #0x6]
	strb r12, [sp, #0x7]
	strb r3, [sp, #0x8]
	strb r2, [sp, #0x9]
	strb r12, [sp, #0xa]
	bl FUN_020A19F4
	mov r2, #0x0
	mov r1, r0
	add r0, sp, #0x4
	mov r3, r2
	str r5, [sp, #0x0]
	bl FUN_0209C1D4
_020A03CC:
	mov r0, #0x0
	strb r0, [r4, #0x455]
	add sp, sp, #0x20
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_020A03E0
FUN_020A03E0: ; 0x020A03E0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x24
	ldr r4, [sp, #0x48]
	mov r9, r1
	mov r1, r4
	mov r10, r0
	mov r0, #0x0
	ldr r1, [r1, #0xc]
	str r0, [sp, #0x8]
	str r0, [sp, #0x1c]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	mov r0, #0x17
	str r0, [sp, #0xc]
	mov r0, #0x3
	str r4, [sp, #0x48]
	str r1, [sp, #0x4]
	mov r8, r2
	add r6, r9, r3
	str r0, [sp, #0x10]
_020A0430:
	ldr r0, _020A052C ; =0x00000B4F
	ldr r1, _020A0530 ; =0x021C8EC8
	cmp r6, r0
	movgt r5, r0
	movle r5, r6
	ldr r1, [r1, #0x0]
	add r0, r5, #0x19
	blx r1
	movs r7, r0
	beq _020A051C
	cmp r9, r5
	movcs r4, r5
	movcc r4, r9
	mov r0, r10
	add r1, r7, #0x5
	mov r2, r4
	sub r11, r5, r4
	bl MI_CpuCopy8
	add r1, r7, #0x5
	mov r0, r8
	add r1, r1, r4
	mov r2, r11
	add r10, r10, r4
	sub r9, r9, r4
	bl MI_CpuCopy8
	ldr r0, [sp, #0xc]
	mov r1, r7
	strb r0, [r7, #0x0]
	ldr r0, [sp, #0x10]
	add r8, r8, r11
	strb r0, [r7, #0x1]
	ldr r0, [sp, #0x14]
	strb r0, [r7, #0x2]
	mov r0, r5, asr #0x8
	strb r0, [r7, #0x3]
	ldr r0, [sp, #0x4]
	strb r5, [r7, #0x4]
	bl FUN_020A19F4
	ldr r1, [sp, #0x48]
	ldr r2, [sp, #0x18]
	mov r4, r0
	str r1, [sp, #0x0]
	mov r0, r7
	mov r1, r4
	mov r3, r2
	bl FUN_0209C1D4
	cmp r0, r4
	ldr r1, _020A0534 ; =0x021C8EF4
	mov r0, r7
	ldr r1, [r1, #0x0]
	ldrcc r5, [sp, #0x1c]
	blx r1
	ldr r0, [sp, #0x8]
	subs r6, r6, r5
	add r0, r0, r5
	str r0, [sp, #0x8]
	beq _020A051C
	cmp r5, #0x0
	bne _020A0430
_020A051C:
	ldr r0, [sp, #0x8]
	add sp, sp, #0x24
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A052C: .word 0x00000B4F
_020A0530: .word 0x021C8EC8
_020A0534: .word 0x021C8EF4

	arm_func_start FUN_020A0538
FUN_020A0538: ; 0x020A0538
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r4, [r5, #0xc]
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	beq _020A0560
	ldrb r0, [r4, #0x456]
	cmp r0, #0x0
	bne _020A0568
_020A0560:
	mov r0, r5
	bl FUN_020A05D4
_020A0568:
	ldr r1, [r4, #0x824]
	cmp r1, #0x0
	beq _020A0594
	ldrb r0, [r4, #0x456]
	cmp r0, #0x0
	ldrne r1, [r4, #0x828]
	ldrne r0, [r4, #0x82c]
	addne sp, sp, #0x4
	subne r0, r1, r0
	ldmneia sp!, {r4-r5,lr}
	bxne lr
_020A0594:
	cmp r1, #0x0
	bne _020A05C4
	ldrb r0, [r5, #0x8]
	cmp r0, #0x4
	bne _020A05B4
	ldrb r0, [r4, #0x455]
	cmp r0, #0x9
	bne _020A05C4
_020A05B4:
	add sp, sp, #0x4
	mvn r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A05C4:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A05D4
FUN_020A05D4: ; 0x020A05D4
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r0
	ldr r4, [r5, #0xc]
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	bne _020A0684
	ldr r0, [r5, #0x44]
	cmp r0, #0x5
	addcc sp, sp, #0x8
	ldmccia sp!, {r4-r6,lr}
	bxcc lr
	add r0, sp, #0x0
	mov r1, r5
	bl FUN_0209C6C0
	ldrb r2, [r0, #0x3]
	ldrb r0, [r0, #0x4]
	ldr r1, _020A0730 ; =0x00004805
	add r0, r0, r2, lsl #0x8
	add r0, r0, #0x5
	str r0, [sp, #0x0]
	cmp r0, r1
	movhi r0, #0x9
	addhi sp, sp, #0x8
	strhib r0, [r4, #0x455]
	ldmhiia sp!, {r4-r6,lr}
	bxhi lr
	ldr r1, _020A0734 ; =0x021C8EC8
	ldr r1, [r1, #0x0]
	blx r1
	str r0, [r4, #0x824]
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r4, #0x455]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r1, [sp, #0x0]
	mov r0, #0x0
	str r1, [r4, #0x828]
	str r0, [r4, #0x82c]
	strb r0, [r4, #0x456]
	b _020A0698
_020A0684:
	ldr r0, [r5, #0x44]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
_020A0698:
	add r0, sp, #0x0
	mov r1, r5
	bl FUN_0209C6C0
	ldr r3, [r4, #0x828]
	ldr r2, [r4, #0x82c]
	ldr r1, [sp, #0x0]
	sub r2, r3, r2
	cmp r1, r2
	strcs r2, [sp, #0x0]
	movcs r6, #0x1
	ldr r3, [r4, #0x824]
	ldr r1, [r4, #0x82c]
	ldr r2, [sp, #0x0]
	add r1, r3, r1
	movcc r6, #0x0
	bl MI_CpuCopy8
_020A06D8: ; 0x020A06D8
	ldr r0, [sp, #0x0]
	mov r1, r5
	bl FUN_0209C580
_020A06E4: ; 0x020A06E4
	cmp r6, #0x0
	beq _020A0714
	ldr r1, [r4, #0x824]
	mov r0, r4
	bl FUN_020A16E8
	ldrb r0, [r4, #0x456]
	add sp, sp, #0x8
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r4, #0x824]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A0714:
	ldr r1, [r4, #0x82c]
	ldr r0, [sp, #0x0]
	add r0, r1, r0
	str r0, [r4, #0x82c]
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A0730: .word 0x00004805
_020A0734: .word 0x021C8EC8

	arm_func_start FUN_020A0738
FUN_020A0738: ; 0x020A0738
	stmdb sp!, {r4,lr}
	ldr r4, [r1, #0xc]
	ldr r2, [r4, #0x828]
	ldr r1, [r4, #0x82c]
	sub r2, r2, r1
	cmp r0, r2
	blo _020A077C
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	beq _020A076C
	ldr r1, _020A078C ; =0x021C8EF4
	ldr r1, [r1, #0x0]
	blx r1
_020A076C:
	mov r0, #0x0
	str r0, [r4, #0x824]
	ldmia sp!, {r4,lr}
	bx lr
_020A077C:
	add r0, r1, r0
	str r0, [r4, #0x82c]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A078C: .word 0x021C8EF4

	arm_func_start FUN_020A0790
FUN_020A0790: ; 0x020A0790
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	ldr r4, [r5, #0xc]
	mov r6, r0
	ldr r12, [r4, #0x824]
	cmp r12, #0x0
	beq _020A0818
	ldrb r0, [r4, #0x456]
	cmp r0, #0x0
	bne _020A0818
	ldr r3, [r4, #0x82c]
	ldr r1, [r4, #0x828]
	mov r2, r5
	add r0, r12, r3
	sub r1, r1, r3
	bl FUN_020A1974
_020A07D0: ; 0x020A07D0
	cmp r0, #0x0
	beq _020A07FC
	ldr r1, _020A0870 ; =0x021C8EF4
	ldr r0, [r4, #0x824]
	ldr r1, [r1, #0x0]
	blx r1
	mov r0, #0x0
	str r0, [r4, #0x824]
	str r0, [r6, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A07FC:
	ldr r1, [r4, #0x824]
	mov r0, r4
	bl FUN_020A16E8
	ldrb r0, [r4, #0x456]
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r4, #0x824]
_020A0818:
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	bne _020A084C
_020A0824:
	mov r0, r5
	bl FUN_020A1528
	cmp r0, #0x9
	moveq r0, #0x0
	streq r0, [r6, #0x0]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	beq _020A0824
_020A084C:
	ldr r1, [r4, #0x828]
	ldr r0, [r4, #0x82c]
	sub r0, r1, r0
	str r0, [r6, #0x0]
	ldr r1, [r4, #0x824]
	ldr r0, [r4, #0x82c]
	add r0, r1, r0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A0870: .word 0x021C8EF4

	arm_func_start FUN_020A0874
FUN_020A0874: ; 0x020A0874
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrb r1, [r5, #0x8]
	ldr r4, [r5, #0xc]
	cmp r1, #0x4
	beq _020A08A8
	bl FUN_0209C990
_020A0894: ; 0x020A0894
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {r4-r5,lr}
	bxne lr
_020A08A8:
	mov r1, #0x0
	strb r1, [r4, #0x455]
	str r1, [r4, #0x1d4]
	add r0, r4, #0x2ec
	strb r1, [r4, #0x454]
	bl FUN_020A41CC
	add r0, r4, #0x3a4
	bl FUN_020A3B8C
	mov r0, r5
	bl FUN_020A08DC
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A08DC
FUN_020A08DC: ; 0x020A08DC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r4, [r5, #0xc]
	bl FUN_020A0DE4
_020A08F0:
	mov r0, r5
	bl FUN_020A1528
	cmp r0, #0x9
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r0, #0x4
	beq _020A0920
	ldrb r0, [r4, #0x31]
	cmp r0, #0x0
	beq _020A08F0
_020A0920:
	ldrb r0, [r4, #0x31]
	cmp r0, #0x0
	beq _020A095C
	mov r0, r4
	bl FUN_020A215C
	mov r0, r5
	bl FUN_020A0AF4
_020A093C: ; 0x020A093C
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r0, r5
	bl FUN_020A0F94
	b _020A09B4
_020A095C:
	mov r0, r5
	bl FUN_020A0B2C
	mov r0, r4
	bl FUN_020A2364
	ldrb r0, [r4, #0x30]
	cmp r0, #0x0
	beq _020A0988
	ldrh r2, [r5, #0x18]
	ldr r1, [r5, #0x1c]
	mov r0, r4
	bl FUN_020A3808
_020A0988:
	mov r0, r4
	bl FUN_020A215C
	mov r0, r5
	bl FUN_020A0F94
	mov r0, r5
	bl FUN_020A0AF4
_020A09A0: ; 0x020A09A0
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {r4-r5,lr}
	bxne lr
_020A09B4:
	mov r0, #0x8
	strb r0, [r4, #0x455]
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A09CC
FUN_020A09CC: ; 0x020A09CC
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	ldr r8, [r9, #0xc]
	add r5, r8, #0x2ec
	add r4, r8, #0x3a4
	mov r7, #0x0
	mov r6, #0x1
_020A09EC:
	mov r0, r9
	bl FUN_0209CAC4
	strb r7, [r8, #0x455]
	str r7, [r8, #0x1d4]
	mov r0, r5
	strb r6, [r8, #0x454]
	bl FUN_020A41CC
	mov r0, r4
	bl FUN_020A3B8C
	mov r0, r9
	bl FUN_020A0A58
_020A0A18: ; 0x020A0A18
	cmp r0, #0x0
	moveq r0, #0x8
	addeq sp, sp, #0x4
	streqb r0, [r8, #0x455]
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r0, r9
	bl FUN_0209C884
	ldrh r0, [r9, #0x1a]
	strh r0, [r9, #0x18]
	ldr r0, [r9, #0x20]
	str r0, [r9, #0x1c]
	b _020A09EC
_020A0A4C: ; 0x020A0A4C
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_020A0A58
FUN_020A0A58:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020A1528
	cmp r0, #0x1
	movne r0, #0x1
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r0, r4
	bl FUN_020A10F4
_020A0A7C: ; 0x020A0A7C
	cmp r0, #0x0
	beq _020A0AB0
	ldr r0, [r4, #0xc]
	bl FUN_020A215C
	mov r0, r4
	bl FUN_020A0F94
	mov r0, r4
	bl FUN_020A0AF4
_020A0A9C: ; 0x020A0A9C
	cmp r0, #0x0
	beq _020A0AE8
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A0AB0:
	mov r0, r4
	bl FUN_020A1528
	cmp r0, #0x5
	movne r0, #0x1
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r0, r4
	bl FUN_020A0AF4
_020A0AD0: ; 0x020A0AD0
	cmp r0, #0x0
	movne r0, #0x1
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r0, r4
	bl FUN_020A0F94
_020A0AE8:
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A0AF4
FUN_020A0AF4:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020A1528
	cmp r0, #0x7
	movne r0, #0x1
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r0, r4
	bl FUN_020A1528
	cmp r0, #0x6
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A0B2C
FUN_020A0B2C: ; 0x020A0B2C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r11, r0
	ldr r10, [r11, #0xc]
	mov r0, #0x3
	strb r0, [r10, #0x0]
	mov r0, #0x0
	strb r0, [r10, #0x1]
	add r0, r10, #0x2
	mov r1, #0x2e
	bl FUN_020A13E0
	ldr r4, [r10, #0x594]
	ldr r0, _020A0DD4 ; =0x021C8EC8
	mov r1, r4, lsl #0x1
	ldr r2, [r0, #0x0]
	add r1, r1, r1, lsr #0x1f
	mov r0, r4
	mov r6, r1, asr #0x1
	blx r2
	movs r5, r0
	moveq r0, #0x9
	addeq sp, sp, #0xc
	streqb r0, [r10, #0x455]
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	mov r0, #0x0
	strb r0, [r5, #0x0]
	mov r2, #0x2
	add r0, r5, #0x2
	sub r1, r4, #0x33
	strb r2, [r5, #0x1]
	bl FUN_020A13E0
	add r1, r5, r4
	mov r0, r10
	sub r3, r4, #0x31
	mov r7, #0x0
	sub r1, r1, #0x30
	mov r2, #0x30
	strb r7, [r5, r3]
	bl MI_CpuCopy8
	ldr r1, _020A0DD4 ; =0x021C8EC8
	mov r0, r6, lsl #0x3
	ldr r1, [r1, #0x0]
	blx r1
	movs r9, r0
	bne _020A0C08
	ldr r1, _020A0DD8 ; =0x021C8EF4
	mov r0, r5
	ldr r1, [r1, #0x0]
	blx r1
	mov r0, #0x9
	add sp, sp, #0xc
	strb r0, [r10, #0x455]
	ldmia sp!, {r4-r11,lr}
	bx lr
_020A0C08:
	add r0, r9, r6, lsl #0x1
	add r8, r0, r6, lsl #0x1
	mov r1, r5
	mov r2, r4
	mov r3, r6
	str r0, [sp, #0x4]
	add r7, r8, r6, lsl #0x1
	bl FUN_020A4B50
	ldr r1, _020A0DDC ; =0x00000598
	ldr r2, [r10, #0x5a0]
	mov r0, r8
	add r1, r10, r1
	mov r3, r6
	bl FUN_020A4B50
	ldr r1, _020A0DE0 ; =0x00000494
	mov r0, r7
	mov r2, r4
	add r1, r10, r1
	mov r3, r6
	bl FUN_020A4B50
	bl FUN_020A36EC
	mov r3, r6
	mov r6, r0
	ldr r1, [sp, #0x4]
	mov r2, r8
	mov r0, r9
	str r7, [sp, #0x0]
	bl FUN_020A507C
	mov r0, r6
	bl FUN_020A36B4
	ldr r1, _020A0DD4 ; =0x021C8EC8
	add r0, r4, #0x49
	ldr r1, [r1, #0x0]
	blx r1
	movs r6, r0
	bne _020A0CCC
	ldr r1, _020A0DD8 ; =0x021C8EF4
	mov r0, r5
	ldr r1, [r1, #0x0]
	blx r1
	ldr r1, _020A0DD8 ; =0x021C8EF4
	mov r0, r9
	ldr r1, [r1, #0x0]
	blx r1
	mov r0, #0x9
	add sp, sp, #0xc
	strb r0, [r10, #0x455]
	ldmia sp!, {r4-r11,lr}
	bx lr
_020A0CCC:
	mov r0, #0x16
	strb r0, [r6, #0x0]
	mov r1, #0x3
	add r0, r4, #0x4
	strb r1, [r6, #0x1]
	mov r1, #0x0
	strb r1, [r6, #0x2]
	mov r1, r0, asr #0x8
	strb r1, [r6, #0x3]
	add r2, r6, #0x9
	strb r0, [r6, #0x4]
	mov r0, #0x10
	strb r0, [r6, #0x5]
	mov r0, r4, asr #0x10
	strb r0, [r6, #0x6]
	mov r0, r4, asr #0x8
	strb r0, [r6, #0x7]
	mov r0, r2
	strb r4, [r6, #0x8]
	ands r1, r4, #0x1
	beq _020A0D38
	add r0, r4, r4, lsr #0x1f
	mov r0, r0, asr #0x1
	mov r0, r0, lsl #0x1
	ldrh r1, [r9, r0]
	add r0, r2, #0x1
	strb r1, [r2, #0x0]
_020A0D38:
	add r1, r4, r4, lsr #0x1f
	mov r1, r1, asr #0x1
	subs r7, r1, #0x1
	bmi _020A0D70
_020A0D48:
	mov r3, r7, lsl #0x1
	ldrh r1, [r9, r3]
	add r2, r0, #0x1
	subs r7, r7, #0x1
	mov r1, r1, asr #0x8
	strb r1, [r0, #0x0]
	ldrh r1, [r9, r3]
	add r0, r0, #0x2
	strb r1, [r2, #0x0]
	bpl _020A0D48
_020A0D70:
	mov r2, #0x0
	mov r0, r6
	mov r3, r2
	add r1, r4, #0x9
	str r11, [sp, #0x0]
	bl FUN_0209C1D4
	mov r0, r10
	add r1, r6, #0x5
	add r2, r4, #0x4
	bl FUN_020A1944
	ldr r1, _020A0DD8 ; =0x021C8EF4
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	ldr r1, _020A0DD8 ; =0x021C8EF4
	mov r0, r9
	ldr r1, [r1, #0x0]
	blx r1
	ldr r1, _020A0DD8 ; =0x021C8EF4
	mov r0, r5
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A0DD4: .word 0x021C8EC8
_020A0DD8: .word 0x021C8EF4
_020A0DDC: .word 0x00000598
_020A0DE0: .word 0x00000494

	arm_func_start FUN_020A0DE4
FUN_020A0DE4: ; 0x020A0DE4
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	ldr r1, _020A0F88 ; =0x021C8EC8
	mov r8, r0
	ldr r1, [r1, #0x0]
	mov r0, #0x98
	ldr r7, [r8, #0xc]
	blx r1
	movs r6, r0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r7, #0x455]
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r0, #0x3
	strb r0, [r6, #0x9]
	add r5, r6, #0x9
	mov r0, #0x0
	strb r0, [r5, #0x1]
	bl FUN_020A375C
	mov r1, r0, lsr #0x18
	strb r1, [r7, #0x34]
	mov r1, r0, lsr #0x10
	strb r1, [r7, #0x35]
	mov r1, r0, lsr #0x8
	strb r1, [r7, #0x36]
	strb r0, [r7, #0x37]
	add r0, r7, #0x38
	mov r1, #0x1c
	bl FUN_020A13E0
	add r0, r7, #0x34
	add r1, r5, #0x2
	mov r2, #0x20
	bl MI_CpuCopy8
	ldrh r2, [r8, #0x18]
	ldr r1, [r8, #0x1c]
	mov r0, r7
	bl FUN_020A3908
	ldrb r0, [r7, #0x30]
	cmp r0, #0x0
	moveq r0, #0x0
	streqb r0, [r5, #0x22]
	addeq r5, r5, #0x23
	beq _020A0EAC
	mov r2, #0x20
	add r0, r7, #0x74
	add r1, r5, #0x23
	strb r2, [r5, #0x22]
	bl MI_CpuCopy8
	add r5, r5, #0x43
_020A0EAC:
	mov r4, #0x0
	strb r4, [r5, #0x0]
	mov r0, #0x4
	strb r0, [r5, #0x1]
	ldr r2, _020A0F8C ; =0x0210623C
	add r5, r5, #0x2
_020A0EC4:
	mov r3, r4, lsl #0x1
	ldrh r0, [r2, r3]
	add r4, r4, #0x1
	add r1, r5, #0x1
	mov r0, r0, asr #0x8
	strb r0, [r5, #0x0]
	ldrh r0, [r2, r3]
	cmp r4, #0x2
	add r5, r5, #0x2
	strb r0, [r1, #0x0]
	blo _020A0EC4
	mov r3, #0x1
	mov r2, #0x0
	strb r3, [r5, #0x0]
	add r0, r5, #0x2
	sub r0, r0, r6
	sub r4, r0, #0x5
	strb r2, [r5, #0x1]
	sub r1, r4, #0x4
	mov r0, #0x16
	strb r0, [r6, #0x0]
	mov r0, #0x3
	strb r0, [r6, #0x1]
	strb r2, [r6, #0x2]
	mov r0, r4, asr #0x8
	strb r0, [r6, #0x3]
	strb r4, [r6, #0x4]
	strb r3, [r6, #0x5]
	mov r0, r1, asr #0x10
	strb r0, [r6, #0x6]
	mov r0, r1, asr #0x8
	strb r0, [r6, #0x7]
	strb r1, [r6, #0x8]
	mov r0, r6
	mov r3, r2
	add r1, r4, #0x5
	str r8, [sp, #0x0]
	bl FUN_0209C1D4
	mov r0, r7
	mov r2, r4
	add r1, r6, #0x5
	bl FUN_020A1944
	ldr r1, _020A0F90 ; =0x021C8EF4
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A0F88: .word 0x021C8EC8
_020A0F8C: .word 0x0210623C
_020A0F90: .word 0x021C8EF4

	arm_func_start FUN_020A0F94
FUN_020A0F94:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	ldr r1, _020A10EC ; =0x021C8EC8
	mov r6, r0
	ldr r1, [r1, #0x0]
	mov r0, #0x83
	ldr r5, [r6, #0xc]
	blx r1
	movs r4, r0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r5, #0x455]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, #0x14
	strb r0, [r4, #0x0]
	mov r0, #0x3
	strb r0, [r4, #0x1]
	mov r1, #0x0
	strb r1, [r4, #0x2]
	strb r1, [r4, #0x3]
	mov r3, #0x1
	strb r3, [r4, #0x4]
	add r0, r5, #0x1cc
	mov r2, #0x8
	strb r3, [r4, #0x5]
	bl MI_CpuFill8
	mov r0, #0x16
	strb r0, [r4, #0x6]
	mov r0, #0x3
	strb r0, [r4, #0x7]
	mov r1, #0x0
	strb r1, [r4, #0x8]
	strb r1, [r4, #0x9]
	mov r0, #0x28
	strb r0, [r4, #0xa]
	mov r0, #0x14
	strb r0, [r4, #0xb]
	strb r1, [r4, #0xc]
	strb r1, [r4, #0xd]
	mov r3, #0x24
	add r0, r5, #0x3a4
	add r1, r5, #0x3fc
	mov r2, #0x58
	strb r3, [r4, #0xe]
	bl MI_CpuCopy8
	mov r0, r5
	add r1, r4, #0xf
	mov r2, #0x0
	bl FUN_020A2034
	add r0, r5, #0x3fc
	add r1, r5, #0x3a4
	mov r2, #0x58
	bl MI_CpuCopy8
	add r0, r5, #0x2ec
	add r1, r5, #0x348
	mov r2, #0x5c
	bl MI_CpuCopy8
	mov r0, r5
	add r1, r4, #0x1f
	mov r2, #0x0
	bl FUN_020A1F4C
	add r0, r5, #0x348
	add r1, r5, #0x2ec
	mov r2, #0x5c
	bl MI_CpuCopy8
	mov r0, r5
	add r1, r4, #0xb
	mov r2, #0x28
	bl FUN_020A1944
	mov r0, r5
	add r1, r4, #0x6
	bl FUN_020A19F4
	mov r2, #0x0
	add r1, r0, #0x6
	mov r0, r4
	mov r3, r2
	str r6, [sp, #0x0]
	bl FUN_0209C1D4
	ldr r1, _020A10F0 ; =0x021C8EF4
	mov r0, r4
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A10EC: .word 0x021C8EC8
_020A10F0: .word 0x021C8EF4

	arm_func_start FUN_020A10F4
FUN_020A10F4:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	ldr r7, [r9, #0xc]
	ldr r4, [r7, #0x820]
	cmp r4, #0x0
	ldrne r8, [r4, #0x0]
	moveq r8, #0x0
	bl FUN_020A375C
	mov r1, r0, lsr #0x18
	strb r1, [r7, #0x54]
	mov r1, r0, lsr #0x10
	strb r1, [r7, #0x55]
	mov r1, r0, lsr #0x8
	strb r1, [r7, #0x56]
	strb r0, [r7, #0x57]
	add r0, r7, #0x58
	mov r1, #0x1c
	bl FUN_020A13E0
	ldr r1, _020A1360 ; =0x021C8EC8
	add r0, r8, #0x9d
	ldr r1, [r1, #0x0]
	blx r1
	movs r6, r0
	moveq r0, #0x9
	streqb r0, [r7, #0x455]
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r0, #0x2
	add r5, r6, #0x5
	strb r0, [r6, #0x5]
	mov r3, #0x0
	strb r3, [r5, #0x1]
	strb r3, [r5, #0x2]
	mov r0, #0x46
	strb r0, [r5, #0x3]
	mov r0, #0x3
	strb r0, [r5, #0x4]
	add r0, r7, #0x54
	add r1, r5, #0x6
	mov r2, #0x20
	strb r3, [r5, #0x5]
	bl MI_CpuCopy8
	mov r2, #0x20
	strb r2, [r5, #0x26]
	ldrb r0, [r7, #0x30]
	cmp r0, #0x0
	beq _020A11D8
	add r0, r7, #0x74
	add r1, r5, #0x27
	bl MI_CpuCopy8
	mov r0, #0x1
	strb r0, [r7, #0x31]
	add r5, r5, #0x47
	b _020A1238
_020A11D8:
	add r0, r5, #0x27
	mov r1, #0x1c
	bl FUN_020A13E0
	ldr r0, _020A1364 ; =0x021CA6E4
	add r2, r5, #0x46
	ldr r3, [r0, #0x0]
	add r1, r7, #0x74
	mov r0, r3, lsr #0x18
	strb r0, [r5, #0x43]
	mov r0, r3, lsr #0x10
	strb r0, [r5, #0x44]
	mov r0, r3, lsr #0x8
	strb r0, [r5, #0x45]
	add r5, r5, #0x47
	sub r0, r5, #0x20
	strb r3, [r2, #0x0]
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, _020A1364 ; =0x021CA6E4
	mov r1, #0x0
	ldr r2, [r0, #0x0]
	add r2, r2, #0x1
	str r2, [r0, #0x0]
	strb r1, [r7, #0x31]
_020A1238:
	ldrh r2, [r7, #0x32]
	mov r0, #0x0
	mov r2, r2, asr #0x8
	strb r2, [r5, #0x0]
	ldrh r2, [r7, #0x32]
	strb r2, [r5, #0x1]
	strb r0, [r5, #0x2]
	ldrb r0, [r7, #0x31]
	add r5, r5, #0x3
	cmp r0, #0x0
	bne _020A12EC
	cmp r8, #0x0
	beq _020A12D0
	mov r0, #0xb
	add r2, r8, #0x6
	strb r0, [r5, #0x0]
	mov r0, r2, asr #0x10
	strb r0, [r5, #0x1]
	mov r0, r2, asr #0x8
	strb r0, [r5, #0x2]
	add r1, r8, #0x3
	strb r2, [r5, #0x3]
	mov r0, r1, asr #0x10
	strb r0, [r5, #0x4]
	mov r0, r1, asr #0x8
	strb r0, [r5, #0x5]
	strb r1, [r5, #0x6]
	mov r0, r8, asr #0x10
	strb r0, [r5, #0x7]
	mov r0, r8, asr #0x8
	strb r0, [r5, #0x8]
	strb r8, [r5, #0x9]
	add r5, r5, #0xa
	ldr r0, [r4, #0x4]
	mov r1, r5
	mov r2, r8
	bl MI_CpuCopy8
	add r5, r5, r8
_020A12D0:
	mov r0, #0xe
	strb r0, [r5, #0x0]
	mov r1, #0x0
	strb r1, [r5, #0x1]
	strb r1, [r5, #0x2]
	strb r1, [r5, #0x3]
	add r5, r5, #0x4
_020A12EC:
	mov r0, #0x16
	sub r1, r5, r6
	sub r4, r1, #0x5
	strb r0, [r6, #0x0]
	mov r0, #0x3
	strb r0, [r6, #0x1]
	mov r0, #0x0
	strb r0, [r6, #0x2]
	mov r0, r4, asr #0x8
	strb r0, [r6, #0x3]
	mov r0, r7
	mov r2, r4
	add r1, r6, #0x5
	strb r4, [r6, #0x4]
	bl FUN_020A1944
	mov r2, #0x0
	mov r0, r6
	mov r3, r2
	add r1, r4, #0x5
	str r9, [sp, #0x0]
	bl FUN_0209C1D4
	ldr r1, _020A1368 ; =0x021C8EF4
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	ldrb r0, [r7, #0x31]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020A1360: .word 0x021C8EC8
_020A1364: .word 0x021CA6E4
_020A1368: .word 0x021C8EF4

	arm_func_start FUN_020A136C
FUN_020A136C:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x60
	mov r6, r0
	add r0, sp, #0x0
	mov r5, r1
	bl FUN_020A41CC
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r1, _020A13D8 ; =0x021CA6E8
	add r0, sp, #0x0
	mov r2, #0x14
	bl FUN_020A410C
	mov r1, r6
	mov r2, r5
	add r0, sp, #0x0
	bl FUN_020A410C
	ldr r1, _020A13D8 ; =0x021CA6E8
	add r0, sp, #0x0
	bl FUN_020A4098
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r0, _020A13DC ; =0x021CA6E0
	mov r1, #0x1
	strb r1, [r0, #0x0]
	add sp, sp, #0x60
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A13D8: .word 0x021CA6E8
_020A13DC: .word 0x021CA6E0

	arm_func_start FUN_020A13E0
FUN_020A13E0: ; 0x020A13E0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x7c
	ldr r2, _020A1518 ; =0x021CA6E0
	mov r10, r0
	ldrb r0, [r2, #0x0]
	mov r9, r1
	cmp r0, #0x0
	bne _020A1448
	ldr r2, _020A151C ; =0x021C8F24
	add r0, sp, #0x4
	ldr r4, [r2, #0x8]
	ldr r3, [r2, #0x0]
	ldr r1, [r2, #0x4]
	umull r6, r5, r4, r3
	mla r5, r4, r1, r5
	ldr r1, [r2, #0xc]
	ldr r4, [r2, #0x10]
	mla r5, r1, r3, r5
	adds r4, r4, r6
	ldr r3, [r2, #0x14]
	mov r1, #0x4
	adc r3, r3, r5
	str r4, [r2, #0x0]
	str r3, [r2, #0x4]
	str r3, [sp, #0x4]
	bl FUN_020A136C
_020A1448:
	cmp r9, #0x0
	mov r7, #0x0
	addle sp, sp, #0x7c
	mov r1, #0x14
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	add r6, sp, #0x1c
	mov r11, r1
	str r7, [sp, #0x0]
	mov r5, #0x1
	mov r4, #0x13
_020A1474:
	cmp r1, #0x14
	bne _020A14EC
	mov r0, r6
	bl FUN_020A41CC
	bl OS_DisableInterrupts
	mov r8, r0
	ldr r1, _020A1520 ; =0x021CA6E8
	mov r0, r6
	mov r2, r11
	bl FUN_020A410C
	mov r0, r6
	add r1, sp, #0x8
	bl FUN_020A405C
	ldr r2, _020A1524 ; =0x021CA6FB
	mov r12, r5
	mov lr, r4
	add r3, sp, #0x1b
_020A14B8:
	ldrb r1, [r2, #0x0]
	ldrb r0, [r3], #-0x1
	subs lr, lr, #0x1
	add r0, r1, r0
	add r0, r12, r0
	strb r0, [r2, #0x0]
	mov r12, r0, lsr #0x8
	sub r2, r2, #0x1
	bpl _020A14B8
	str r0, [sp, #0x4]
	mov r0, r8
	bl OS_RestoreInterrupts
	ldr r1, [sp, #0x0]
_020A14EC:
	add r0, sp, #0x8
	ldrb r0, [r0, r1]
	add r1, r1, #0x1
	cmp r0, #0x0
	strneb r0, [r10, r7]
	addne r7, r7, #0x1
	cmp r7, r9
	blt _020A1474
	add sp, sp, #0x7c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A1518: .word 0x021CA6E0
_020A151C: .word 0x021C8F24
_020A1520: .word 0x021CA6E8
_020A1524: .word 0x021CA6FB

	arm_func_start FUN_020A1528
FUN_020A1528: ; 0x020A1528
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r0
	ldr r4, [r5, #0xc]
	add r6, sp, #0x0
_020A153C:
	mov r0, r6
	mov r1, r5
	bl FUN_0209C6C0
	ldr r1, [sp, #0x0]
	cmp r1, #0x0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r4, #0x455]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	cmp r1, #0x5
	blo _020A153C
	ldrb r1, [r0, #0x0]
	cmp r1, #0x80
	bne _020A1634
	ldrb r1, [r4, #0x454]
	cmp r1, #0x0
	beq _020A1628
	ldrb r1, [r4, #0x455]
	cmp r1, #0x0
	bne _020A1628
	ldrb r2, [r0, #0x1]
	mov r1, r5
	mov r0, #0x2
	str r2, [sp, #0x0]
	bl FUN_0209C580
	ldr r1, _020A16DC ; =0x021C8EC8
	ldr r0, [sp, #0x0]
	ldr r1, [r1, #0x0]
	blx r1
	movs r6, r0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r4, #0x455]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r1, [sp, #0x0]
	mov r2, r5
	bl FUN_020A1974
_020A15D8: ; 0x020A15D8
	cmp r0, #0x0
	bne _020A15FC
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _020A15FC
	mov r0, r4
	add r1, r6, #0x1
	bl FUN_020A2774
	b _020A1604
_020A15FC:
	mov r0, #0x9
	strb r0, [r4, #0x455]
_020A1604:
	ldr r2, [sp, #0x0]
	mov r0, r4
	mov r1, r6
	bl FUN_020A1944
	ldr r1, _020A16E0 ; =0x021C8EF4
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	b _020A16CC
_020A1628:
	mov r0, #0x9
	strb r0, [r4, #0x455]
	b _020A16CC
_020A1634:
	ldrb r2, [r0, #0x3]
	ldrb r0, [r0, #0x4]
	ldr r1, _020A16E4 ; =0x00004805
	add r0, r0, r2, lsl #0x8
	add r0, r0, #0x5
	str r0, [sp, #0x0]
	cmp r0, r1
	movhi r0, #0x9
	addhi sp, sp, #0x8
	strhib r0, [r4, #0x455]
	ldmhiia sp!, {r4-r6,lr}
	bxhi lr
	ldr r1, _020A16DC ; =0x021C8EC8
	ldr r1, [r1, #0x0]
	blx r1
	movs r6, r0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r4, #0x455]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r1, [sp, #0x0]
	mov r2, r5
	bl FUN_020A1974
_020A1694: ; 0x020A1694
	cmp r0, #0x0
	beq _020A16C0
	ldr r1, _020A16E0 ; =0x021C8EF4
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	mov r0, #0x9
	add sp, sp, #0x8
	strb r0, [r4, #0x455]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A16C0:
	mov r0, r4
	mov r1, r6
	bl FUN_020A16E8
_020A16CC:
	ldrb r0, [r4, #0x455]
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A16DC: .word 0x021C8EC8
_020A16E0: .word 0x021C8EF4
_020A16E4: .word 0x00004805

	arm_func_start FUN_020A16E8
FUN_020A16E8: ; 0x020A16E8
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldrb r0, [r8, #0x455]
	mov r7, r1
	cmp r0, #0x9
	bne _020A1718
	ldr r1, _020A1940 ; =0x021C8EF4
	mov r0, r7
	ldr r1, [r1, #0x0]
	blx r1
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A1718:
	ldrb r2, [r7, #0x3]
	ldrb r1, [r7, #0x4]
	add r0, r0, #0xf9
	and r0, r0, #0xff
	add r1, r1, r2, lsl #0x8
	cmp r0, #0x1
	add r5, r1, #0x5
	ldrb r4, [r7, #0x0]
	bhi _020A1744
	cmp r4, #0x15
	bne _020A1754
_020A1744:
	cmp r4, #0x15
	bne _020A1764
	cmp r5, #0x7
	bls _020A1764
_020A1754:
	mov r0, r8
	mov r1, r7
	bl FUN_020A1C08
	mov r5, r0
_020A1764:
	sub r0, r4, #0x14
	cmp r0, #0x3
	add r6, r7, #0x5
	sub r5, r5, #0x5
	addls pc, pc, r0, lsl #0x2
	b _020A1920
_020A177C: ; 0x020A177C
	b _020A178C
_020A1780: ; 0x020A1780
	b _020A17BC
_020A1784: ; 0x020A1784
	b _020A17D0
_020A1788: ; 0x020A1788
	b _020A18FC
_020A178C:
	ldr r0, [r8, #0x1d4]
	cmp r0, #0x0
	moveq r0, #0x9
	streqb r0, [r8, #0x455]
	beq _020A1928
	add r0, r8, #0x2e4
	mov r1, #0x0
	mov r2, #0x8
	bl MI_CpuFill8
	mov r0, #0x7
	strb r0, [r8, #0x455]
	b _020A1928
_020A17BC:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x2
	moveq r0, #0x9
	streqb r0, [r8, #0x455]
	b _020A1928
_020A17D0:
	ldrb r1, [r6, #0x1]
	ldrb r0, [r6, #0x2]
	ldrb r3, [r6, #0x0]
	ldrb r2, [r6, #0x3]
	mov r1, r1, lsl #0x10
	add r0, r1, r0, lsl #0x8
	cmp r3, #0xb
	add r4, r2, r0
	add r6, r6, #0x4
	bgt _020A1824
	cmp r3, #0xb
	bge _020A1898
	cmp r3, #0x2
	bgt _020A18C4
	cmp r3, #0x1
	blt _020A18C4
	cmp r3, #0x1
	beq _020A1850
	cmp r3, #0x2
	beq _020A1888
	b _020A18C4
_020A1824:
	cmp r3, #0x14
	bgt _020A18C4
	cmp r3, #0xe
	blt _020A18C4
	cmp r3, #0xe
	beq _020A18A8
	cmp r3, #0x10
	beq _020A1878
	cmp r3, #0x14
	beq _020A18B4
	b _020A18C4
_020A1850:
	ldrb r0, [r8, #0x454]
	cmp r0, #0x0
	beq _020A18CC
	ldrb r0, [r8, #0x455]
	cmp r0, #0x0
	bne _020A18CC
	mov r0, r8
	mov r1, r6
	bl FUN_020A26D0
	b _020A18CC
_020A1878:
	mov r0, r8
	mov r1, r6
	bl FUN_020A211C
	b _020A18CC
_020A1888:
	mov r0, r8
	mov r1, r6
	bl FUN_020A2914
	b _020A18CC
_020A1898:
	mov r0, r8
	mov r1, r6
	bl FUN_020A29DC
	b _020A18CC
_020A18A8:
	mov r0, #0x4
	strb r0, [r8, #0x455]
	b _020A18CC
_020A18B4:
	mov r0, r8
	mov r1, r6
	bl FUN_020A1E84
	b _020A18CC
_020A18C4:
	mov r0, #0x9
	strb r0, [r8, #0x455]
_020A18CC:
	mov r0, r8
	sub r1, r6, #0x4
	add r2, r4, #0x4
	bl FUN_020A1944
	add r0, r4, #0x4
	add r6, r6, r4
	subs r5, r5, r0
	beq _020A1928
	ldrb r0, [r8, #0x455]
	cmp r0, #0x9
	bne _020A17D0
	b _020A1928
_020A18FC:
	str r7, [r8, #0x824]
	mov r0, #0x5
	str r0, [r8, #0x82c]
	add r0, r5, #0x5
	str r0, [r8, #0x828]
	mov r0, #0x1
	strb r0, [r8, #0x456]
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A1920:
	mov r0, #0x9
	strb r0, [r8, #0x455]
_020A1928:
	ldr r1, _020A1940 ; =0x021C8EF4
	mov r0, r7
	ldr r1, [r1, #0x0]
	blx r1
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A1940: .word 0x021C8EF4

	arm_func_start FUN_020A1944
FUN_020A1944: ; 0x020A1944
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	add r0, r6, #0x2ec
	bl FUN_020A410C
	mov r1, r5
	mov r2, r4
	add r0, r6, #0x3a4
	bl FUN_020A3ACC
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_020A1974
FUN_020A1974:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	add r4, sp, #0x0
_020A198C:
	mov r0, r4
	mov r1, r5
	bl FUN_0209C6C0
	ldr r1, [sp, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r1, r6
	strhi r6, [sp, #0x0]
	ldr r2, [sp, #0x0]
	mov r1, r7
	bl MI_CpuCopy8
_020A19C4: ; 0x020A19C4
	ldr r0, [sp, #0x0]
	mov r1, r5
	bl FUN_0209C580
_020A19D0: ; 0x020A19D0
	ldr r0, [sp, #0x0]
	sub r6, r6, r0
	cmp r6, #0x0
	add r7, r7, r0
	bgt _020A198C
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_020A19F4
FUN_020A19F4: ; 0x020A19F4
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x30
	mov r5, r1
	mov r6, r0
	ldrh r0, [r6, #0x32]
	ldrb r3, [r5, #0x3]
	ldrb r2, [r5, #0x4]
	add r1, r5, #0x5
	cmp r0, #0x4
	add r4, r2, r3, lsl #0x8
	add r8, r1, r4
	beq _020A1A30
	cmp r0, #0x5
	beq _020A1B04
	b _020A1BD4
_020A1A30:
	add r7, r6, #0x3fc
	mov r0, r7
	bl FUN_020A3B8C
	ldr r1, [r6, #0xbc]
	mov r0, r7
	mov r2, #0x10
	bl FUN_020A3ACC
_020A1A4C: ; 0x020A1A4C
	add r0, sp, #0x0
	mov r1, #0x36
	mov r2, #0x30
	bl MI_CpuFill8
	mov r0, r7
	add r1, sp, #0x0
	mov r2, #0x30
	bl FUN_020A3ACC
	mov r0, r7
	add r1, r6, #0x1cc
	mov r2, #0x8
	bl FUN_020A3ACC
	mov r0, r7
	mov r1, r5
	mov r2, #0x1
	bl FUN_020A3ACC
	mov r0, r7
	add r1, r5, #0x3
	add r2, r4, #0x2
	bl FUN_020A3ACC
	mov r0, r7
	mov r1, r8
	bl FUN_020A3A58
	mov r0, r7
	bl FUN_020A3B8C
	ldr r1, [r6, #0xbc]
	mov r0, r7
	mov r2, #0x10
	bl FUN_020A3ACC
_020A1AC0: ; 0x020A1AC0
	add r0, sp, #0x0
	mov r1, #0x5c
	mov r2, #0x30
	bl MI_CpuFill8
	mov r0, r7
	add r1, sp, #0x0
	mov r2, #0x30
	bl FUN_020A3ACC
	mov r0, r7
	mov r1, r8
	mov r2, #0x10
	bl FUN_020A3ACC
	mov r0, r7
	mov r1, r8
	bl FUN_020A3A58
	add r4, r4, #0x10
	b _020A1BD4
_020A1B04:
	add r7, r6, #0x348
	mov r0, r7
	bl FUN_020A41CC
	ldr r1, [r6, #0xbc]
	mov r0, r7
	mov r2, #0x14
	bl FUN_020A410C
_020A1B20: ; 0x020A1B20
	add r0, sp, #0x0
	mov r1, #0x36
	mov r2, #0x28
	bl MI_CpuFill8
	mov r0, r7
	add r1, sp, #0x0
	mov r2, #0x28
	bl FUN_020A410C
	mov r0, r7
	add r1, r6, #0x1cc
	mov r2, #0x8
	bl FUN_020A410C
	mov r0, r7
	mov r1, r5
	mov r2, #0x1
	bl FUN_020A410C
	mov r0, r7
	add r1, r5, #0x3
	add r2, r4, #0x2
	bl FUN_020A410C
	mov r0, r7
	mov r1, r8
	bl FUN_020A4098
	mov r0, r7
	bl FUN_020A41CC
	ldr r1, [r6, #0xbc]
	mov r0, r7
	mov r2, #0x14
	bl FUN_020A410C
_020A1B94: ; 0x020A1B94
	add r0, sp, #0x0
	mov r1, #0x5c
	mov r2, #0x28
	bl MI_CpuFill8
	mov r0, r7
	add r1, sp, #0x0
	mov r2, #0x28
	bl FUN_020A410C
	mov r0, r7
	mov r1, r8
	mov r2, #0x14
	bl FUN_020A410C
	mov r0, r7
	mov r1, r8
	bl FUN_020A4098
	add r4, r4, #0x14
_020A1BD4:
	mov r0, r4, asr #0x8
	strb r0, [r5, #0x3]
	mov r2, r4
	add r0, r6, #0xc8
	add r1, r5, #0x5
	strb r4, [r5, #0x4]
	bl FUN_020A49CC
	add r0, r6, #0x1d4
	bl FUN_020A1E60
	add r0, r4, #0x5
	add sp, sp, #0x30
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_020A1C08
FUN_020A1C08: ; 0x020A1C08
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x44
	mov r6, r1
	ldrb r3, [r6, #0x3]
	ldrb r2, [r6, #0x4]
	mov r7, r0
	add r1, r6, #0x5
	add r2, r2, r3, lsl #0x8
	bl FUN_020A1E44
	ldrh r1, [r7, #0x32]
	mov r5, r0
	cmp r1, #0x4
	beq _020A1C48
	cmp r1, #0x5
	beq _020A1D2C
	b _020A1E0C
_020A1C48:
	sub r5, r5, #0x10
	mov r0, r5, asr #0x8
	strb r0, [r6, #0x3]
	add r4, r7, #0x3fc
	mov r0, r4
	strb r5, [r6, #0x4]
	bl FUN_020A3B8C
	ldr r1, [r7, #0x1d4]
	mov r0, r4
	mov r2, #0x10
	bl FUN_020A3ACC
	add r0, sp, #0x14
	mov r1, #0x36
	mov r2, #0x30
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x14
	mov r2, #0x30
	bl FUN_020A3ACC
	mov r0, r4
	add r1, r7, #0x2e4
	mov r2, #0x8
	bl FUN_020A3ACC
	mov r0, r4
	mov r1, r6
	mov r2, #0x1
	bl FUN_020A3ACC
	mov r0, r4
	add r1, r6, #0x3
	add r2, r5, #0x2
	bl FUN_020A3ACC
	mov r0, r4
	add r1, sp, #0x0
	bl FUN_020A3A58
	mov r0, r4
	bl FUN_020A3B8C
	ldr r1, [r7, #0x1d4]
	mov r0, r4
	mov r2, #0x10
	bl FUN_020A3ACC
	add r0, sp, #0x14
	mov r1, #0x5c
	mov r2, #0x30
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x14
	mov r2, #0x30
	bl FUN_020A3ACC
	mov r0, r4
	add r1, sp, #0x0
	mov r2, #0x10
	bl FUN_020A3ACC
	mov r0, r4
	add r1, sp, #0x0
	bl FUN_020A3A58
	mov r4, #0x10
	b _020A1E0C
_020A1D2C:
	sub r5, r5, #0x14
	mov r0, r5, asr #0x8
	strb r0, [r6, #0x3]
	add r4, r7, #0x348
	mov r0, r4
	strb r5, [r6, #0x4]
	bl FUN_020A41CC
	ldr r1, [r7, #0x1d4]
	mov r0, r4
	mov r2, #0x14
	bl FUN_020A410C
	add r0, sp, #0x14
	mov r1, #0x36
	mov r2, #0x28
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x14
	mov r2, #0x28
	bl FUN_020A410C
	mov r0, r4
	add r1, r7, #0x2e4
	mov r2, #0x8
	bl FUN_020A410C
	mov r0, r4
	mov r1, r6
	mov r2, #0x1
	bl FUN_020A410C
	mov r0, r4
	add r1, r6, #0x3
	add r2, r5, #0x2
	bl FUN_020A410C
	mov r0, r4
	add r1, sp, #0x0
	bl FUN_020A4098
	mov r0, r4
	bl FUN_020A41CC
	ldr r1, [r7, #0x1d4]
	mov r0, r4
	mov r2, #0x14
	bl FUN_020A410C
	add r0, sp, #0x14
	mov r1, #0x5c
	mov r2, #0x28
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x14
	mov r2, #0x28
	bl FUN_020A410C
	mov r0, r4
	add r1, sp, #0x0
	mov r2, #0x14
	bl FUN_020A410C
	mov r0, r4
	add r1, sp, #0x0
	bl FUN_020A4098
	mov r4, #0x14
_020A1E0C:
	add r0, r6, #0x5
	add r1, sp, #0x0
	mov r2, r4
	add r0, r0, r5
	bl memcmp
_020A1E20: ; 0x020A1E20
	cmp r0, #0x0
	movne r0, #0x9
	strneb r0, [r7, #0x455]
	add r0, r7, #0x2ec
	bl FUN_020A1E60
	add r0, r5, #0x5
	add sp, sp, #0x44
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_020A1E44
FUN_020A1E44: ; 0x020A1E44
	stmdb sp!, {r4,lr}
	add r0, r0, #0x1e0
	mov r4, r2
	bl FUN_020A49CC
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A1E60
FUN_020A1E60: ; 0x020A1E60
	mov r2, #0x8
_020A1E64:
	ldrb r1, [r0, #-0x1]!
	add r1, r1, #0x1
	ands r1, r1, #0xff
	strb r1, [r0, #0x0]
	bxne lr
	subs r2, r2, #0x1
	bne _020A1E64
	bx lr

	arm_func_start FUN_020A1E84
FUN_020A1E84: ; 0x020A1E84
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	mov r5, r0
	mov r4, r1
	add r0, r5, #0x3a4
	add r1, r5, #0x3fc
	mov r2, #0x58
	bl MI_CpuCopy8
	add r1, sp, #0x0
	mov r0, r5
	mov r2, #0x1
	bl FUN_020A2034
	add r0, r5, #0x3fc
	add r1, r5, #0x3a4
	mov r2, #0x58
	bl MI_CpuCopy8
	add r1, sp, #0x0
	mov r0, r4
	mov r2, #0x10
	bl memcmp
_020A1ED4: ; 0x020A1ED4
	cmp r0, #0x0
	movne r0, #0x9
	addne sp, sp, #0x14
	strneb r0, [r5, #0x455]
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	add r0, r5, #0x2ec
	add r1, r5, #0x348
	mov r2, #0x5c
	bl MI_CpuCopy8
	add r1, sp, #0x0
	mov r0, r5
	mov r2, #0x1
	bl FUN_020A1F4C
	add r0, r5, #0x348
	add r1, r5, #0x2ec
	mov r2, #0x5c
	bl MI_CpuCopy8
	add r1, sp, #0x0
	add r0, r4, #0x10
	mov r2, #0x14
	bl memcmp
_020A1F2C: ; 0x020A1F2C
	cmp r0, #0x0
	movne r0, #0x9
	strneb r0, [r5, #0x455]
	moveq r0, #0x6
	streqb r0, [r5, #0x455]
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A1F4C
FUN_020A1F4C: ; 0x020A1F4C
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x28
	mov r6, r0
	ldrb r0, [r6, #0x454]
	mov r5, r1
	add r4, r6, #0x2ec
	eors r0, r0, r2
	beq _020A1F80
	ldr r1, _020A202C ; =0x02106290
	mov r0, r4
	mov r2, #0x4
	bl FUN_020A410C
	b _020A1F90
_020A1F80:
	ldr r1, _020A2030 ; =0x02106298
	mov r0, r4
	mov r2, #0x4
	bl FUN_020A410C
_020A1F90:
	mov r0, r4
	mov r1, r6
	mov r2, #0x30
	bl FUN_020A410C
_020A1FA0: ; 0x020A1FA0
	add r0, sp, #0x0
	mov r1, #0x36
	mov r2, #0x28
	bl MI_CpuFill8
	add r1, sp, #0x0
	mov r0, r4
	mov r2, #0x28
	bl FUN_020A410C
	mov r0, r4
	mov r1, r5
	bl FUN_020A4098
	mov r0, r4
	bl FUN_020A41CC
	mov r1, r6
	mov r0, r4
	mov r2, #0x30
	bl FUN_020A410C
_020A1FE4: ; 0x020A1FE4
	add r0, sp, #0x0
	mov r1, #0x5c
	mov r2, #0x28
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x0
	mov r2, #0x28
	bl FUN_020A410C
	mov r0, r4
	mov r1, r5
	mov r2, #0x14
	bl FUN_020A410C
	mov r0, r4
	mov r1, r5
	bl FUN_020A4098
	add sp, sp, #0x28
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A202C: .word 0x02106290
_020A2030: .word 0x02106298

	arm_func_start FUN_020A2034
FUN_020A2034: ; 0x020A2034
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x30
	mov r6, r0
	ldrb r0, [r6, #0x454]
	mov r5, r1
	add r4, r6, #0x3a4
	eors r0, r0, r2
	beq _020A2068
	ldr r1, _020A2114 ; =0x02106290
	mov r0, r4
	mov r2, #0x4
	bl FUN_020A3ACC
	b _020A2078
_020A2068:
	ldr r1, _020A2118 ; =0x02106298
	mov r0, r4
	mov r2, #0x4
	bl FUN_020A3ACC
_020A2078:
	mov r0, r4
	mov r1, r6
	mov r2, #0x30
	bl FUN_020A3ACC
_020A2088: ; 0x020A2088
	add r0, sp, #0x0
	mov r1, #0x36
	mov r2, #0x30
	bl MI_CpuFill8
	add r1, sp, #0x0
	mov r0, r4
	mov r2, #0x30
	bl FUN_020A3ACC
	mov r0, r4
	mov r1, r5
	bl FUN_020A3A58
	mov r0, r4
	bl FUN_020A3B8C
	mov r1, r6
	mov r0, r4
	mov r2, #0x30
	bl FUN_020A3ACC
_020A20CC: ; 0x020A20CC
	add r0, sp, #0x0
	mov r1, #0x5c
	mov r2, #0x30
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x0
	mov r2, #0x30
	bl FUN_020A3ACC
	mov r0, r4
	mov r1, r5
	mov r2, #0x10
	bl FUN_020A3ACC
	mov r0, r4
	mov r1, r5
	bl FUN_020A3A58
	add sp, sp, #0x30
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A2114: .word 0x02106290
_020A2118: .word 0x02106298

	arm_func_start FUN_020A211C
FUN_020A211C: ; 0x020A211C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r2, [r4, #0x81c]
	bl FUN_020A2470
	mov r0, r4
	bl FUN_020A2364
	mov r1, #0x0
	mov r0, r4
	mov r2, r1
	bl FUN_020A3808
	mov r0, r4
	bl FUN_020A215C
	mov r0, #0x5
	strb r0, [r4, #0x455]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A215C
FUN_020A215C: ; 0x020A215C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	mov r10, r0
	ldrh r0, [r10, #0x32]
	cmp r0, #0x4
	beq _020A2190
	cmp r0, #0x5
	moveq r0, #0x14
	streq r0, [sp, #0x0]
	moveq r0, #0x10
	streq r0, [sp, #0x4]
	moveq r2, #0x0
	b _020A21A0
_020A2190:
	mov r0, #0x10
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r2, #0x0
_020A21A0:
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	mov r9, #0x0
	add r0, r1, r0
	add r0, r2, r0
	mov r0, r0, lsl #0x1
	str r0, [sp, #0x8]
	cmp r0, #0x0
	ble _020A22B8
	mov r0, #0x20
	str r0, [sp, #0x10]
	mov r0, #0x14
	mov r6, r9
	add r5, sp, #0x18
	str r9, [sp, #0xc]
	mov r4, #0x1
	mov r11, #0x30
	str r0, [sp, #0x14]
_020A21E8:
	add r7, r10, #0x348
	mov r0, r7
	bl FUN_020A41CC
	add r0, r9, #0x41
	strb r0, [sp, #0x18]
	add r0, r9, #0x1
	ldr r8, [sp, #0xc]
	cmp r0, #0x0
	ble _020A222C
_020A220C:
	mov r0, r7
	mov r1, r5
	mov r2, r4
	bl FUN_020A410C
	add r8, r8, #0x1
	add r0, r9, #0x1
	cmp r8, r0
	blt _020A220C
_020A222C:
	mov r0, r7
	mov r1, r10
	mov r2, r11
	bl FUN_020A410C
	ldr r2, [sp, #0x10]
	mov r0, r7
	add r1, r10, #0x54
	bl FUN_020A410C
	ldr r2, [sp, #0x10]
	mov r0, r7
	add r1, r10, #0x34
	bl FUN_020A410C
	mov r0, r7
	add r1, sp, #0x19
	bl FUN_020A4098
	add r7, r10, #0x3fc
	mov r0, r7
	bl FUN_020A3B8C
	mov r0, r7
	mov r1, r10
	mov r2, r11
	bl FUN_020A3ACC
	ldr r2, [sp, #0x14]
	mov r0, r7
	add r1, sp, #0x19
	bl FUN_020A3ACC
	add r1, r10, #0x74
	mov r0, r7
	add r1, r1, r6
	bl FUN_020A3A58
	ldr r0, [sp, #0x8]
	add r6, r6, #0x10
	cmp r6, r0
	add r9, r9, #0x1
	blt _020A21E8
_020A22B8:
	ldrb r0, [r10, #0x454]
	cmp r0, #0x0
	beq _020A2300
	add r1, r10, #0x74
	str r1, [r10, #0x1d4]
	ldr r0, [sp, #0x0]
	ldr r2, [r10, #0x1d4]
	add r1, r1, r0
	add r0, r2, r0, lsl #0x1
	str r0, [r10, #0x1d8]
	str r1, [r10, #0xbc]
	ldr r1, [r10, #0xbc]
	ldr r0, [sp, #0x0]
	add r1, r1, r0
	ldr r0, [sp, #0x4]
	add r0, r1, r0
	str r0, [r10, #0xc0]
	b _020A2338
_020A2300:
	add r1, r10, #0x74
	str r1, [r10, #0xbc]
	ldr r0, [sp, #0x0]
	ldr r2, [r10, #0xbc]
	add r1, r1, r0
	add r0, r2, r0, lsl #0x1
	str r0, [r10, #0xc0]
	str r1, [r10, #0x1d4]
	ldr r1, [r10, #0x1d4]
	ldr r0, [sp, #0x0]
	add r1, r1, r0
	ldr r0, [sp, #0x4]
	add r0, r1, r0
	str r0, [r10, #0x1d8]
_020A2338:
	ldr r1, [r10, #0x1d8]
	add r0, r10, #0x1e0
	mov r2, #0x10
	bl FUN_020A4A3C
	ldr r1, [r10, #0xc0]
	add r0, r10, #0xc8
	mov r2, #0x10
	bl FUN_020A4A3C
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_020A2364
FUN_020A2364: ; 0x020A2364
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x30
	mov r4, r0
	ldr r1, _020A23BC ; =0x021062A0
	add r0, sp, #0x0
	mov r2, r4
	bl FUN_020A23C8
	ldr r1, _020A23C0 ; =0x021062A4
	add r0, sp, #0x10
	mov r2, r4
	bl FUN_020A23C8
	ldr r1, _020A23C4 ; =0x021062A8
	add r0, sp, #0x20
	mov r2, r4
	bl FUN_020A23C8
_020A23A0: ; 0x020A23A0
	add r0, sp, #0x0
	mov r1, r4
	mov r2, #0x30
	bl MI_CpuCopy8
	add sp, sp, #0x30
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A23BC: .word 0x021062A0
_020A23C0: .word 0x021062A4
_020A23C4: .word 0x021062A8

	arm_func_start FUN_020A23C8
FUN_020A23C8:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r5, r2
	add r4, r5, #0x348
	mov r7, r0
	mov r6, r1
	mov r0, r4
	bl FUN_020A41CC
	mov r0, r6
	bl strlen
	mov r2, r0
	mov r1, r6
	mov r0, r4
	bl FUN_020A410C
	mov r0, r4
	mov r1, r5
	mov r2, #0x30
	bl FUN_020A410C
	mov r0, r4
	add r1, r5, #0x34
	mov r2, #0x40
	bl FUN_020A410C
	mov r0, r4
	add r1, sp, #0x0
	bl FUN_020A4098
	add r4, r5, #0x3fc
	mov r0, r4
	bl FUN_020A3B8C
	mov r1, r5
	mov r0, r4
	mov r2, #0x30
	bl FUN_020A3ACC
	mov r0, r4
	add r1, sp, #0x0
	mov r2, #0x14
	bl FUN_020A3ACC
	mov r0, r4
	mov r1, r7
	bl FUN_020A3A58
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_020A2470
FUN_020A2470: ; 0x020A2470
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	movs r10, r2
	str r0, [sp, #0x8]
	mov r11, r1
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r0, [r10, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	mov r0, r0, lsl #0x1
	add r0, r0, r0, lsr #0x1f
	mov r0, r0, asr #0x1
	add r9, r0, #0x1
	mov r0, #0x14
	mul r0, r9, r0
	ldr r1, _020A26C8 ; =0x021C8EC8
	ldr r1, [r1, #0x0]
	blx r1
	movs r8, r0
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	add r7, r8, r9, lsl #0x1
	add r6, r7, r9, lsl #0x1
	add r1, r6, r9, lsl #0x1
	str r1, [sp, #0xc]
	add r1, r1, r9, lsl #0x1
	add r5, r1, r9, lsl #0x1
	str r1, [sp, #0x10]
	ldr r2, [r10, #0x0]
	add r4, r5, r9, lsl #0x1
	mov r1, r11
	mov r3, r9
	add r11, r4, r9, lsl #0x1
	bl FUN_020A4B50
	ldr r1, [r10, #0x1c]
	ldr r2, [r10, #0x18]
	mov r0, r7
	mov r3, r9
	bl FUN_020A4B50
	ldr r1, [r10, #0xc]
	ldr r2, [r10, #0x8]
	mov r0, r5
	mov r3, r9
	bl FUN_020A4B50
	bl FUN_020A36EC
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xc]
	str r5, [sp, #0x0]
	mov r1, r8
	mov r2, r7
	mov r3, r9
	bl FUN_020A4BB0
	ldr r1, [r10, #0x24]
	ldr r2, [r10, #0x20]
	mov r0, r7
	mov r3, r9
	bl FUN_020A4B50
	ldr r1, [r10, #0x14]
	ldr r2, [r10, #0x10]
	mov r0, r5
	mov r3, r9
	bl FUN_020A4B50
	ldr r0, [sp, #0x10]
	mov r1, r8
	mov r2, r7
	mov r3, r9
	str r5, [sp, #0x0]
	bl FUN_020A4BB0
	ldr r0, [sp, #0x14]
	bl FUN_020A36B4
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	mov r0, r8
	mov r3, r9
	bl FUN_020A57BC
	ldr r1, [r10, #0x2c]
	ldr r2, [r10, #0x28]
	mov r0, r7
	mov r3, r9
	bl FUN_020A4B50
	mov r0, r6
	mov r1, r8
	mov r2, r7
	mov r3, r9
	bl FUN_020A5608
	ldr r1, [r10, #0x14]
	ldr r2, [r10, #0x10]
	mov r0, r7
	mov r3, r9
	bl FUN_020A4B50
	mov r0, r8
	mov r1, r6
	mov r2, r7
	mov r3, r9
	bl FUN_020A5608
	ldr r2, [sp, #0x10]
	mov r0, r6
	mov r1, r8
	mov r3, r9
	bl FUN_020A5930
	ldr r1, [r10, #0x4]
	ldr r2, [r10, #0x0]
	mov r0, r7
	mov r3, r9
	bl FUN_020A4B50
	mov r0, r6
	mov r1, r9
	bl FUN_020A59DC
_020A2634: ; 0x020A2634
	cmp r0, #0x0
	bge _020A267C
	mov r0, r6
	mov r1, r9
	bl FUN_020A5874
	str r9, [sp, #0x0]
	mov r1, r6
	mov r2, r7
	mov r3, r4
	mov r0, #0x0
	str r11, [sp, #0x4]
	bl FUN_020A5240
	mov r0, r4
	mov r1, r7
	mov r2, r4
	mov r3, r9
	bl FUN_020A57BC
	b _020A2698
_020A267C:
	str r9, [sp, #0x0]
	mov r1, r6
	mov r2, r7
	mov r3, r4
	mov r0, #0x0
	str r11, [sp, #0x4]
	bl FUN_020A5240
_020A2698:
	ldr r0, [sp, #0x8]
	mov r1, r4
	mov r3, r9
	mov r2, #0x30
	bl FUN_020A4B08
	ldr r1, _020A26CC ; =0x021C8EF4
	mov r0, r8
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A26C8: .word 0x021C8EC8
_020A26CC: .word 0x021C8EF4

	arm_func_start FUN_020A26D0
FUN_020A26D0: ; 0x020A26D0
	stmdb sp!, {r4-r6,lr}
	mov r6, r1
	mov r4, r0
	ldrb r0, [r6, #0x0]
	ldrb r1, [r6, #0x1]
	bl FUN_020A284C
_020A26E8: ; 0x020A26E8
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	add r0, r6, #0x2
	add r1, r4, #0x34
	mov r2, #0x20
	bl MI_CpuCopy8
	ldrb r5, [r6, #0x22]
	add r6, r6, #0x23
	cmp r5, #0x20
	movne r0, #0x0
	strneb r0, [r4, #0x30]
	bne _020A2734
	mov r0, r6
	add r1, r4, #0x74
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r0, r4
	bl FUN_020A39B0
_020A2734:
	add r0, r6, r5
	ldrb r1, [r0, #0x1]
	ldrb r3, [r6, r5]
	add r0, r0, #0x2
	mov r2, #0x2
	add r1, r1, r3, lsl #0x8
	add r1, r1, r1, lsr #0x1f
	mov r1, r1, asr #0x1
	bl FUN_020A285C
	mov r0, r0, lsl #0x10
	movs r0, r0, lsr #0x10
	strh r0, [r4, #0x32]
	movne r0, #0x1
	strneb r0, [r4, #0x455]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_020A2774
FUN_020A2774: ; 0x020A2774
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r6, r0
	ldrb r0, [r5, #0x0]
	ldrb r1, [r5, #0x1]
	bl FUN_020A284C
_020A278C: ; 0x020A278C
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrb r2, [r5, #0x2]
	ldrb r1, [r5, #0x3]
	ldr r3, _020A2848 ; =0x55555556
	add r0, r5, #0x8
	add r4, r1, r2, lsl #0x8
	smull r2, r1, r3, r4
	add r1, r1, r4, lsr #0x1f
	mov r2, #0x3
	bl FUN_020A285C
	mov r0, r0, lsl #0x10
	movs r0, r0, lsr #0x10
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	strh r0, [r6, #0x32]
	ldrb r12, [r5, #0x4]
	ldrb r0, [r5, #0x5]
	ldrb r3, [r5, #0x6]
	ldrb r2, [r5, #0x7]
	mov r1, #0x0
	add r12, r0, r12, lsl #0x8
	add r0, r4, #0x8
	add r4, r2, r3, lsl #0x8
	add r0, r0, r12
	strb r1, [r6, #0x30]
	cmp r4, #0x20
	add r5, r5, r0
	blt _020A2818
	mov r0, r5
	add r1, r6, #0x34
	mov r2, #0x20
	bl MI_CpuCopy8
	b _020A2838
_020A2818:
	add r0, r6, #0x34
	rsb r2, r4, #0x20
	bl MI_CpuFill8
	add r1, r6, #0x54
	mov r0, r5
	mov r2, r4
	sub r1, r1, r4
	bl MI_CpuCopy8
_020A2838:
	mov r0, #0x1
	strb r0, [r6, #0x455]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A2848: .word 0x55555556

	arm_func_start FUN_020A284C
FUN_020A284C:
	cmp r0, #0x3
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

	arm_func_start FUN_020A285C
FUN_020A285C: ; 0x020A285C
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, #0x0
	ldr r4, _020A28BC ; =0x0210623C
_020A2874:
	mov r0, r5, lsl #0x1
	ldrh r3, [r4, r0]
	mov r0, r8
	mov r1, r7
	mov r2, r6
	bl FUN_020A28C0
_020A288C: ; 0x020A288C
	cmp r0, #0x0
	ldrne r0, _020A28BC ; =0x0210623C
	movne r1, r5, lsl #0x1
	ldrneh r0, [r0, r1]
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	add r5, r5, #0x1
	cmp r5, #0x2
	blo _020A2874
	mov r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A28BC: .word 0x0210623C

	arm_func_start FUN_020A28C0
FUN_020A28C0:
	stmdb sp!, {r4,lr}
	cmp r1, #0x0
	mov r4, #0x0
	ble _020A2908
_020A28D0:
	ldrb lr, [r0, #0x0]
	ldrb r12, [r0, #0x1]
	cmp r2, #0x3
	add lr, r12, lr, lsl #0x8
	ldreqb r12, [r0, #0x2]
	addeq lr, r12, lr, lsl #0x8
	cmp lr, r3
	moveq r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r4, r4, #0x1
	cmp r4, r1
	add r0, r0, r2
	blt _020A28D0
_020A2908:
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A2914
FUN_020A2914: ; 0x020A2914
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	add r0, r5, #0x2
	add r1, r6, #0x54
	mov r2, #0x20
	bl MI_CpuCopy8
	add r0, r5, #0x22
	ldrb r7, [r6, #0x30]
	add r5, r5, #0x23
	ldrb r4, [r0, #0x0]
	cmp r7, #0x0
	beq _020A2974
	cmp r4, #0x20
	bne _020A2974
	mov r1, r5
	add r0, r6, #0x74
	mov r2, #0x20
	bl memcmp
_020A2964: ; 0x020A2964
	cmp r0, #0x0
	moveq r0, #0x1
	streqb r0, [r6, #0x31]
	beq _020A29B4
_020A2974:
	cmp r7, #0x0
	beq _020A2984
	mov r0, r6
	bl FUN_020A3798
_020A2984:
	cmp r4, #0x0
	moveq r0, #0x0
	streqb r0, [r6, #0x30]
	beq _020A29AC
	mov r0, r5
	add r1, r6, #0x74
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r0, #0x1
	strb r0, [r6, #0x30]
_020A29AC:
	mov r0, #0x0
	strb r0, [r6, #0x31]
_020A29B4:
	add r0, r5, r4
	ldrb r2, [r5, r4]
	ldrb r1, [r0, #0x1]
	mov r0, #0x2
	add r1, r1, r2, lsl #0x8
	strh r1, [r6, #0x32]
	strb r0, [r6, #0x455]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_020A29DC
FUN_020A29DC: ; 0x020A29DC
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x24
	ldr r1, [sp, #0x4c]
	mov r10, r0
	ldrb r4, [r1, #0x2]
	ldrb r3, [r1, #0x0]
	ldrb r2, [r1, #0x1]
	add r0, r1, #0x3
	mvn r1, #0x0
	str r0, [sp, #0x4c]
	add r2, r2, r3, lsl #0x8
	add r0, sp, #0x14
	str r1, [r10, #0x45c]
	add r7, r4, r2, lsl #0x8
	bl RTC_GetDate
	mov r8, #0x0
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x1c]
	add r1, r0, #0x7d0
	ldr r0, [sp, #0x18]
	mov r1, r1, lsl #0x10
	add r0, r1, r0, lsl #0x8
	add r0, r2, r0
	str r0, [r10, #0x80c]
	strb r8, [r10, #0x6b0]
	str r8, [r10, #0x5a0]
	ldr r0, [r10, #0x5a0]
	mov r6, r8
	str r0, [r10, #0x594]
	add r0, r10, #0x7b0
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r8, [sp, #0x8]
	mov r4, r8
	mov r11, #0x2
	str r0, [sp, #0xc]
	mvn r5, #0x0
_020A2A74:
	ldr r1, [sp, #0x4c]
	mov r0, r10
	ldrb r2, [r1, #0x2]
	ldrb r12, [r1, #0x0]
	ldrb r3, [r1, #0x1]
	add r9, r1, #0x3
	add r1, sp, #0x4c
	str r9, [sp, #0x4c]
	str r5, [r10, #0x458]
	strb r4, [r10, #0x5ad]
	strb r4, [r10, #0x5ac]
	strb r4, [r10, #0x5af]
	strb r4, [r10, #0x6b0]
	strb r4, [r10, #0x5b0]
	strb r4, [r10, #0x7b0]
	add r3, r3, r12, lsl #0x8
	ldr r9, [sp, #0x4c]
	add r3, r2, r3, lsl #0x8
	add r2, r3, #0x3
	str r9, [r10, #0x804]
	str r3, [r10, #0x808]
	sub r7, r7, r2
	mov r2, r4
	mov r3, r4
	str r8, [sp, #0x0]
	bl FUN_020A2F98
_020A2ADC: ; 0x020A2ADC
	cmp r0, #0x0
	bne _020A2AFC
	ldr r0, [r10, #0x594]
	cmp r0, #0x33
	blo _020A2AFC
	ldr r0, [r10, #0x5a0]
	cmp r0, #0x0
	bne _020A2B14
_020A2AFC:
	mov r0, #0x9
	add sp, sp, #0x24
	strb r0, [r10, #0x455]
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020A2B14:
	mov r0, r10
	bl FUN_020A2CBC
	mov r8, r0
	cmp r6, #0x0
	bne _020A2B44
	ldr r0, [r10, #0x800]
	cmp r0, #0x0
	beq _020A2B44
	ldr r1, [sp, #0x4]
	bl FUN_020A2C18
_020A2B3C: ; 0x020A2B3C
	cmp r0, #0x0
	orrne r8, r8, #0x4000
_020A2B44:
	and r9, r8, #0xff
	cmp r9, #0x1
	bne _020A2BB4
	cmp r7, #0x0
	beq _020A2BB4
	ldr r1, [sp, #0x4c]
	ldr r2, [sp, #0x8]
	add r1, r1, #0x3
	str r1, [sp, #0x10]
	ldr r1, [sp, #0x8]
	mov r0, r10
	strb r1, [r10, #0x5ad]
	add r1, sp, #0x10
	mov r3, r2
	str r11, [sp, #0x0]
	bl FUN_020A2F98
_020A2B84: ; 0x020A2B84
	cmp r0, #0x0
	movne r0, #0x9
	addne sp, sp, #0x24
	strneb r0, [r10, #0x455]
	ldmneia sp!, {r4-r11,lr}
	addne sp, sp, #0x10
	bxne lr
	mov r0, r10
	add r1, r10, #0x480
	bl FUN_020A2DBC
	bic r1, r8, #0xff
	orr r8, r1, r0
_020A2BB4:
	ldr r3, [r10, #0x810]
	cmp r3, #0x0
	beq _020A2BD4
	mov r0, r8
	mov r1, r10
	mov r2, r6
	blx r3
	mov r8, r0
_020A2BD4:
	cmp r9, #0x0
	add r6, r6, #0x1
	beq _020A2BF4
	cmp r8, #0x0
	bne _020A2BF4
	cmp r7, #0x0
	ldrne r8, [sp, #0xc]
	bne _020A2A74
_020A2BF4:
	cmp r8, #0x0
	moveq r0, #0x3
	streqb r0, [r10, #0x455]
	movne r0, #0x9
	strneb r0, [r10, #0x455]
	add sp, sp, #0x24
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start FUN_020A2C18
FUN_020A2C18:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	b _020A2C38
_020A2C28:
	cmp r1, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
_020A2C38:
	ldrsb r0, [r5], #0x1
	ldrsb r1, [r6], #0x1
	cmp r1, r0
	beq _020A2C28
	cmp r0, #0x2a
	movne r0, #0x1
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	sub r6, r6, #0x1
	mov r0, r6
	bl FUN_020A2C94
	mov r4, r0
	mov r0, r5
	bl FUN_020A2C94
	cmp r0, r4
	movgt r0, #0x1
	ldmgtia sp!, {r4-r6,lr}
	bxgt lr
	sub r0, r4, r0
	add r6, r6, r0
	b _020A2C38
_020A2C8C: ; 0x020A2C8C
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_020A2C94
FUN_020A2C94: ; 0x020A2C94
	mov r2, r0
	b _020A2CA0
_020A2C9C:
	add r0, r0, #0x1
_020A2CA0:
	ldrsb r1, [r0, #0x0]
	cmp r1, #0x2e
	beq _020A2CB4
	cmp r1, #0x0
	bne _020A2C9C
_020A2CB4:
	sub r0, r0, r2
	bx lr

	arm_func_start FUN_020A2CBC
FUN_020A2CBC: ; 0x020A2CBC
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldrb r0, [r5, #0x5af]
	ldr r1, [r5, #0x45c]
	cmp r0, #0x0
	movne r4, #0x0
	moveq r4, #0x8000
	mvn r0, #0x0
	cmp r1, r0
	orreq r0, r4, #0x4
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, [r5, #0x458]
	cmp r0, #0x3
	beq _020A2D04
	cmp r0, #0x4
	beq _020A2D40
	b _020A2D7C
_020A2D04:
	add r6, r5, #0x3fc
	mov r0, r6
	bl FUN_020A3B8C
	ldr r1, [r5, #0x460]
	ldr r2, [r5, #0x464]
	mov r0, r6
	sub r2, r2, r1
	bl FUN_020A3ACC
	ldr r1, _020A2DB8 ; =0x00000468
	mov r0, r6
	add r1, r5, r1
	bl FUN_020A3A58
	mov r0, #0x10
	str r0, [r5, #0x47c]
	b _020A2D88
_020A2D40:
	add r6, r5, #0x348
	mov r0, r6
	bl FUN_020A41CC
	ldr r1, [r5, #0x460]
	ldr r2, [r5, #0x464]
	mov r0, r6
	sub r2, r2, r1
	bl FUN_020A410C
	ldr r1, _020A2DB8 ; =0x00000468
	mov r0, r6
	add r1, r5, r1
	bl FUN_020A4098
	mov r0, #0x14
	str r0, [r5, #0x47c]
	b _020A2D88
_020A2D7C:
	orr r0, r4, #0x3
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A2D88:
	mov r0, r5
	add r1, r5, #0x5b0
	bl FUN_020A3628
	movs r1, r0
	orreq r0, r4, #0x1
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, r5
	bl FUN_020A2DBC
_020A2DAC: ; 0x020A2DAC
	orr r0, r4, r0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A2DB8: .word 0x00000468

	arm_func_start FUN_020A2DBC
FUN_020A2DBC:
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x8
	mov r8, r0
	ldr r0, [r8, #0x5a4]
	mov r7, r1
	cmp r0, #0x0
	beq _020A2E14
	ldr r0, [r8, #0x5a8]
	cmp r0, #0x0
	beq _020A2E14
	ldr r0, [r7, #0x10]
	cmp r0, #0x0
	beq _020A2E14
	ldr r0, [r7, #0xc]
	cmp r0, #0x0
	beq _020A2E14
	ldr r0, [r7, #0x8]
	cmp r0, #0x0
	beq _020A2E14
	ldr r0, [r7, #0x4]
	cmp r0, #0x0
	bne _020A2E24
_020A2E14:
	add sp, sp, #0x8
	mov r0, #0x2
	ldmia sp!, {r4-r10,lr}
	bx lr
_020A2E24:
	mov r0, r0, lsl #0x1
	ldr r1, _020A2F8C ; =0x021C8EC8
	add r0, r0, r0, lsr #0x1f
	mov r4, r0, asr #0x1
	ldr r1, [r1, #0x0]
	mov r0, r4, lsl #0x3
	blx r1
	movs r6, r0
	addeq sp, sp, #0x8
	moveq r0, #0x2
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
	add r5, r6, r4, lsl #0x1
	add r10, r5, r4, lsl #0x1
	ldr r1, [r8, #0x5a4]
	ldr r2, [r8, #0x5a8]
	mov r0, r5
	mov r3, r4
	add r9, r10, r4, lsl #0x1
	bl FUN_020A4B50
	ldr r1, [r7, #0x10]
	ldr r2, [r7, #0xc]
	mov r0, r10
	mov r3, r4
	bl FUN_020A4B50
	mov r0, r9
	ldr r1, [r7, #0x8]
	ldr r2, [r7, #0x4]
	mov r3, r4
	bl FUN_020A4B50
	bl FUN_020A36EC
	str r9, [sp, #0x0]
	mov r2, r10
	mov r9, r0
	mov r0, r6
	mov r1, r5
	mov r3, r4
	bl FUN_020A507C
	mov r0, r9
	bl FUN_020A36B4
	mov r0, r5
	mov r1, r6
	ldr r2, [r7, #0x4]
	mov r3, r4
	bl FUN_020A4B08
	ldrb r0, [r6, r4, lsl #0x1]
	mov r4, #0x0
	cmp r0, #0x0
	bne _020A2EF4
	ldrb r0, [r5, #0x1]
	cmp r0, #0x1
	beq _020A2EFC
_020A2EF4:
	mov r4, #0x2
	b _020A2F6C
_020A2EFC:
	ldr r3, [r7, #0x4]
	mov r2, #0x2
	cmp r3, #0x2
	ble _020A2F24
_020A2F0C:
	ldrb r0, [r5, r2]
	cmp r0, #0xff
	bne _020A2F24
	add r2, r2, #0x1
	cmp r2, r3
	blt _020A2F0C
_020A2F24:
	add r1, r2, #0x1
	cmp r1, r3
	bge _020A2F68
	ldrb r0, [r5, r2]
	cmp r0, #0x0
	bne _020A2F68
	ldrb r0, [r5, r1]
	cmp r0, #0x30
	bne _020A2F68
	ldr r0, _020A2F90 ; =0x00000468
	ldr r2, [r8, #0x47c]
	add r1, r5, r3
	add r0, r8, r0
	sub r1, r1, r2
	bl memcmp
_020A2F60: ; 0x020A2F60
	cmp r0, #0x0
	beq _020A2F6C
_020A2F68:
	mov r4, #0x2
_020A2F6C:
	ldr r1, _020A2F94 ; =0x021C8EF4
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	mov r0, r4
	add sp, sp, #0x8
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020A2F8C: .word 0x021C8EC8
_020A2F90: .word 0x00000468
_020A2F94: .word 0x021C8EF4

	arm_func_start FUN_020A2F98
FUN_020A2F98:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	str r1, [sp, #0x4]
	ldr r1, [r1, #0x0]
	mov r9, r0
	str r1, [sp, #0x8]
	add r0, r1, #0x1
	str r0, [sp, #0x8]
	add r0, sp, #0x8
	mov r5, r2
	mov r4, r3
	ldr r8, [sp, #0x30]
	ldrb r6, [r1, #0x0]
	bl FUN_020A35D8
	movs r7, r0
	bmi _020A2FE0
	cmp r7, #0x7d0
	ble _020A2FF0
_020A2FE0:
	add sp, sp, #0xc
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020A2FF0:
	and r1, r6, #0x1f
	cmp r1, #0x18
	addls pc, pc, r1, lsl #0x2
	b _020A3430
_020A3000:
	b _020A3430
_020A3004:
	b _020A3430
_020A3008:
	b _020A3064
_020A300C:
	b _020A315C
_020A3010:
	b _020A3430
_020A3014:
	b _020A3430
_020A3018:
	b _020A31DC
_020A301C:
	b _020A3430
_020A3020:
	b _020A3430
_020A3024:
	b _020A3430
_020A3028:
	b _020A3430
_020A302C:
	b _020A3430
_020A3030:
	b _020A3274
_020A3034:
	b _020A3430
_020A3038:
	b _020A3430
_020A303C:
	b _020A3430
_020A3040:
	b _020A3348
_020A3044:
	b _020A33D8
_020A3048:
	b _020A3430
_020A304C:
	b _020A3274
_020A3050:
	b _020A3274
_020A3054:
	b _020A3430
_020A3058:
	b _020A3274
_020A305C:
	b _020A32F4
_020A3060:
	b _020A32F4
_020A3064:
	ldrb r0, [r9, #0x5ad]
	cmp r0, #0x0
	beq _020A314C
	cmp r4, #0x0
	bne _020A30E0
	ldr r0, [sp, #0x8]
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	bne _020A30A4
_020A3088:
	ldr r1, [sp, #0x8]
	sub r7, r7, #0x1
	add r0, r1, #0x1
	str r0, [sp, #0x8]
	ldrb r1, [r1, #0x1]
	cmp r1, #0x0
	beq _020A3088
_020A30A4:
	cmp r8, #0x0
	beq _020A30C0
	cmp r8, #0x2
	streq r7, [r9, #0x484]
	ldreq r0, [sp, #0x8]
	streq r0, [r9, #0x488]
	b _020A314C
_020A30C0:
	cmp r7, #0x100
	bgt _020A314C
	ldr r1, _020A34B8 ; =0x00000494
	mov r2, r7
	add r1, r9, r1
	bl MI_CpuCopy8
	str r7, [r9, #0x594]
	b _020A314C
_020A30E0:
	cmp r4, #0x1
	bne _020A314C
	ldr r0, [sp, #0x8]
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	bne _020A3114
_020A30F8:
	ldr r1, [sp, #0x8]
	sub r7, r7, #0x1
	add r0, r1, #0x1
	str r0, [sp, #0x8]
	ldrb r1, [r1, #0x1]
	cmp r1, #0x0
	beq _020A30F8
_020A3114:
	cmp r8, #0x0
	beq _020A3130
	cmp r8, #0x2
	streq r7, [r9, #0x48c]
	ldreq r0, [sp, #0x8]
	streq r0, [r9, #0x490]
	b _020A314C
_020A3130:
	cmp r7, #0x8
	bgt _020A314C
	ldr r1, _020A34BC ; =0x00000598
	mov r2, r7
	add r1, r9, r1
	bl MI_CpuCopy8
	str r7, [r9, #0x5a0]
_020A314C:
	ldr r0, [sp, #0x8]
	add r0, r0, r7
	str r0, [sp, #0x8]
	b _020A349C
_020A315C:
	cmp r5, #0x1
	bne _020A317C
	cmp r8, #0x2
	ldrne r1, [sp, #0x8]
	subne r0, r7, #0x1
	addne r1, r1, #0x1
	strne r1, [r9, #0x5a4]
	strne r0, [r9, #0x5a8]
_020A317C:
	ldrb r0, [r9, #0x5ad]
	cmp r0, #0x0
	beq _020A31CC
	ldr r0, [sp, #0x8]
	add r1, sp, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x8]
	mov r0, r9
	mov r2, r5
	mov r3, #0x0
	str r8, [sp, #0x0]
	bl FUN_020A2F98
_020A31AC: ; 0x020A31AC
	cmp r0, #0x0
	addne sp, sp, #0xc
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	mov r0, #0x0
	strb r0, [r9, #0x5ad]
	b _020A349C
_020A31CC:
	ldr r0, [sp, #0x8]
	add r0, r0, r7
	str r0, [sp, #0x8]
	b _020A349C
_020A31DC:
	ldr r5, [sp, #0x8]
	mov r6, #0x0
	ldr sl, _020A34C0 ; =0x02106278
_020A31E8:
	ldr r4, [r10, r6, lsl #0x2]
	mov r0, r4
	bl strlen
	mov r2, r0
	mov r0, r5
	mov r1, r4
	bl memcmp
_020A3204: ; 0x020A3204
	cmp r0, #0x0
	bne _020A3258
	cmp r6, #0x5
	addls pc, pc, r6, lsl #0x2
	b _020A3264
_020A3218: ; 0x020A3218
	b _020A3264
_020A321C: ; 0x020A321C
	b _020A3230
_020A3220: ; 0x020A3220
	b _020A3230
_020A3224: ; 0x020A3224
	b _020A3240
_020A3228: ; 0x020A3228
	b _020A3240
_020A322C: ; 0x020A322C
	b _020A324C
_020A3230:
	cmp r8, #0x0
	streq r6, [r9, #0x45c]
	strb r6, [r9, #0x5ad]
	b _020A3264
_020A3240:
	cmp r8, #0x2
	strne r6, [r9, #0x458]
	b _020A3264
_020A324C:
	cmp r8, #0x2
	strneb r6, [r9, #0x5ae]
	b _020A3264
_020A3258:
	add r6, r6, #0x1
	cmp r6, #0x6
	blt _020A31E8
_020A3264:
	ldr r0, [sp, #0x8]
	add r0, r0, r7
	str r0, [sp, #0x8]
	b _020A349C
_020A3274:
	cmp r8, #0x2
	beq _020A32DC
	ldrb r0, [r9, #0x5ac]
	cmp r0, #0x0
	beq _020A32CC
	ldr r1, [sp, #0x8]
	mov r2, r7
	add r0, r9, #0x6b0
	bl FUN_020A3554
	ldrb r0, [r9, #0x5ae]
	cmp r0, #0x5
	bne _020A32DC
	cmp r7, #0x4f
	bgt _020A32DC
	ldr r0, [sp, #0x8]
	mov r2, r7
	add r1, r9, #0x7b0
	bl MI_CpuCopy8
	add r0, r9, r7
	mov r1, #0x0
	strb r1, [r0, #0x7b0]
	b _020A32DC
_020A32CC:
	ldr r1, [sp, #0x8]
	mov r2, r7
	add r0, r9, #0x5b0
	bl FUN_020A3554
_020A32DC:
	mov r0, #0x0
	strb r0, [r9, #0x5ae]
	ldr r0, [sp, #0x8]
	add r0, r0, r7
	str r0, [sp, #0x8]
	b _020A349C
_020A32F4:
	cmp r8, #0x2
	beq _020A3330
	ldr r0, [sp, #0x8]
	bl FUN_020A34C4
_020A3304: ; 0x020A3304
	cmp r4, #0x0
	bne _020A3320
	ldr r1, [r9, #0x80c]
	cmp r1, r0
	movcs r0, #0x1
	strcsb r0, [r9, #0x5af]
	b _020A3330
_020A3320:
	ldr r1, [r9, #0x80c]
	cmp r1, r0
	movhi r0, #0x0
	strhib r0, [r9, #0x5af]
_020A3330:
	ldr r1, [sp, #0x8]
	mov r0, #0x1
	add r1, r1, r7
	str r1, [sp, #0x8]
	strb r0, [r9, #0x5ac]
	b _020A349C
_020A3348:
	cmp r5, #0x0
	bne _020A3364
	cmp r4, #0x0
	bne _020A3364
	cmp r8, #0x2
	ldrne r0, [sp, #0x8]
	strne r0, [r9, #0x460]
_020A3364:
	ldr r0, [sp, #0x8]
	mov r10, #0x0
	add r7, r0, r7
	cmp r0, r7
	bhs _020A33BC
	add r11, sp, #0x8
	add r6, r5, #0x1
_020A3380:
	mov r0, r9
	mov r1, r11
	mov r2, r6
	mov r3, r10
	str r8, [sp, #0x0]
	bl FUN_020A2F98
_020A3398: ; 0x020A3398
	cmp r0, #0x0
	add r10, r10, #0x1
	addne sp, sp, #0xc
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldr r0, [sp, #0x8]
	cmp r0, r7
	blo _020A3380
_020A33BC:
	cmp r5, #0x1
	bne _020A349C
	cmp r4, #0x0
	bne _020A349C
	cmp r8, #0x2
	strne r0, [r9, #0x464]
	b _020A349C
_020A33D8:
	ldr r0, [sp, #0x8]
	add r6, r0, r7
	cmp r0, r6
	bhs _020A349C
	add r7, r5, #0x1
	add r4, sp, #0x8
	mov r5, #0x0
_020A33F4:
	mov r0, r9
	mov r1, r4
	mov r2, r7
	mov r3, r5
	str r8, [sp, #0x0]
	bl FUN_020A2F98
_020A340C: ; 0x020A340C
	cmp r0, #0x0
	addne sp, sp, #0xc
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldr r0, [sp, #0x8]
	cmp r0, r6
	blo _020A33F4
	b _020A349C
_020A3430:
	cmp r6, #0xa0
	bne _020A3490
	ldr r0, [sp, #0x8]
	add r6, r0, r7
	cmp r0, r6
	bhs _020A349C
	add r7, r5, #0x1
	add r4, sp, #0x8
	mov r5, #0x0
_020A3454:
	mov r0, r9
	mov r1, r4
	mov r2, r7
	mov r3, r5
	str r8, [sp, #0x0]
	bl FUN_020A2F98
_020A346C: ; 0x020A346C
	cmp r0, #0x0
	addne sp, sp, #0xc
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldr r0, [sp, #0x8]
	cmp r0, r6
	blo _020A3454
	b _020A349C
_020A3490:
	ldr r0, [sp, #0x8]
	add r0, r0, r7
	str r0, [sp, #0x8]
_020A349C:
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0x4]
	mov r0, #0x0
	str r2, [r1, #0x0]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A34B8: .word 0x00000494
_020A34BC: .word 0x00000598
_020A34C0: .word 0x02106278

	arm_func_start FUN_020A34C4
FUN_020A34C4:
	stmdb sp!, {r4,lr}
	ldrb r12, [r0, #0x1]
	ldrb r3, [r0, #0x0]
	mov r2, #0xa
	cmp r1, #0x17
	mla r1, r3, r2, r12
	sub lr, r1, #0x210
	add r0, r0, #0x2
	bne _020A34FC
	cmp lr, #0x32
	ldrhs r1, _020A3550 ; =0x0000076C
	addcc r4, lr, #0x7d0
	addcs r4, lr, r1
	b _020A3518
_020A34FC:
	ldrb r12, [r0, #0x1]
	ldrb r3, [r0, #0x0]
	mov r1, #0x64
	add r0, r0, #0x2
	mla r2, r3, r2, r12
	sub r2, r2, #0x210
	mla r4, lr, r1, r2
_020A3518:
	ldrb r12, [r0, #0x1]
	ldrb r3, [r0, #0x0]
	mov r1, #0xa
	ldrb r2, [r0, #0x3]
	ldrb r0, [r0, #0x2]
	mla r12, r3, r1, r12
	mla r1, r0, r1, r2
	mov r2, r4, lsl #0x10
	sub r0, r12, #0x210
	add r2, r2, r0, lsl #0x8
	sub r0, r1, #0x210
	add r0, r2, r0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A3550: .word 0x0000076C

	arm_func_start FUN_020A3554
FUN_020A3554:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrsb r3, [r0, #0x0]
	mov lr, r0
	cmp r3, #0x0
	beq _020A35AC
_020A356C:
	ldrsb r3, [r0, #0x1]!
	cmp r3, #0x0
	bne _020A356C
	sub r3, r0, lr
	cmp r3, #0xff
	addge sp, sp, #0x4
	ldmgeia sp!, {lr}
	bxge lr
	mov r3, #0x2c
	strb r3, [r0, #0x0]
	mov r3, #0x20
	strb r3, [r0, #0x1]
	add r0, r0, #0x2
	b _020A35AC
_020A35A4:
	ldrsb r3, [r1], #0x1
	strb r3, [r0], #0x1
_020A35AC:
	cmp r2, #0x0
	sub r2, r2, #0x1
	beq _020A35C4
	sub r3, r0, lr
	cmp r3, #0xff
	blt _020A35A4
_020A35C4:
	mov r1, #0x0
	strb r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A35D8
FUN_020A35D8: ; 0x020A35D8
	ldr r1, [r0, #0x0]
	ldrb r3, [r1, #0x0]
	add r12, r1, #0x1
	ands r1, r3, #0x80
	beq _020A361C
	ands r1, r3, #0x7f
	sub r2, r1, #0x1
	mov r3, #0x0
	beq _020A361C
_020A35FC:
	ands r1, r3, #0xff000000
	mvnne r0, #0x0
	bxne lr
	ldrb r1, [r12], #0x1
	cmp r2, #0x0
	sub r2, r2, #0x1
	add r3, r1, r3, lsl #0x8
	bne _020A35FC
_020A361C:
	str r12, [r0, #0x0]
	mov r0, r3
	bx lr

	arm_func_start FUN_020A3628
FUN_020A3628: ; 0x020A3628
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, [r0, #0x818]
	mov r7, r1
	cmp r4, #0x0
	mov r6, #0x0
	ble _020A3678
	ldr r5, [r0, #0x814]
_020A3648:
	ldr r0, [r5, r6, lsl #0x2]
	mov r1, r7
	ldr r0, [r0, #0x0]
	bl strcmp
_020A3658: ; 0x020A3658
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldreq r0, [r5, r6, lsl #0x2]
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r6, r6, #0x1
	cmp r6, r4
	blt _020A3648
_020A3678:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_020A3688
FUN_020A3688: ; 0x020A3688
	ldr r2, _020A36B0 ; =0x021D3498
	ldr r2, [r2, #0x4]
	ldr r2, [r2, #0xa4]
	cmp r2, #0x0
	bxeq lr
	ldr r2, [r2, #0xc]
	cmp r2, #0x0
	strne r0, [r2, #0x814]
	strne r1, [r2, #0x818]
	bx lr
	.balign 4
_020A36B0: .word 0x021D3498

	arm_func_start FUN_020A36B4
FUN_020A36B4: ; 0x020A36B4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r1, r0
	cmp r1, #0x20
	addcs sp, sp, #0x4
	ldmcsia sp!, {lr}
	bxcs lr
	ldr r0, _020A36E8 ; =0x021D3498
	ldr r0, [r0, #0x4]
	bl OS_SetThreadPriority
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A36E8: .word 0x021D3498

	arm_func_start FUN_020A36EC
FUN_020A36EC: ; 0x020A36EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020A3744 ; =0x02106244
	ldr r0, [r0, #0x0]
	cmp r0, #0x20
	addcs sp, sp, #0x4
	mvncs r0, #0x0
	ldmcsia sp!, {r4-r5,lr}
	bxcs lr
	ldr r0, _020A3748 ; =0x021D3498
	ldr r5, [r0, #0x4]
	mov r0, r5
	bl OS_GetThreadPriority
	ldr r1, _020A3744 ; =0x02106244
	mov r4, r0
	ldr r1, [r1, #0x0]
	mov r0, r5
	bl OS_SetThreadPriority
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A3744: .word 0x02106244
_020A3748: .word 0x021D3498

	arm_func_start FUN_020A374C
FUN_020A374C: ; 0x020A374C
	ldr r1, _020A3758 ; =0x02106244
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020A3758: .word 0x02106244

	arm_func_start FUN_020A375C
FUN_020A375C: ; 0x020A375C
	stmdb sp!, {lr}
	sub sp, sp, #0x1c
	add r0, sp, #0x0
	bl RTC_GetDate
	add r0, sp, #0x10
	bl RTC_GetTime
_020A3774: ; 0x020A3774
	add r0, sp, #0x0
	add r1, sp, #0x10
	bl RTC_ConvertDateTimeToSecond
	ldr r1, _020A3794 ; =0x386D4380
	add r0, r0, r1
	add sp, sp, #0x1c
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A3794: .word 0x386D4380

	arm_func_start FUN_020A3798
FUN_020A3798:
	stmdb sp!, {r4-r8,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r6, _020A3804 ; =0x021CA6FC
	mov r7, r0
	mov r8, #0x0
	add r5, r4, #0x74
	mov r4, #0x20
_020A37B8:
	ldrb r0, [r6, #0x5a]
	cmp r0, #0x0
	beq _020A37E4
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl memcmp
_020A37D4: ; 0x020A37D4
	cmp r0, #0x0
	moveq r0, #0x0
	streqb r0, [r6, #0x5a]
	beq _020A37F4
_020A37E4:
	add r8, r8, #0x1
	cmp r8, #0x4
	add r6, r6, #0x5c
	blt _020A37B8
_020A37F4:
	mov r0, r7
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A3804: .word 0x021CA6FC

	arm_func_start FUN_020A3808
FUN_020A3808: ; 0x020A3808
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	mov r8, r1
	mov r7, r2
	bl OS_DisableInterrupts
	mov r5, r0
	bl OS_GetTick
	ldr r6, _020A3904 ; =0x021CA6FC
	mov r4, r0, lsr #0x10
	mov r3, #0x0
	mov r12, r3
	mov r2, r6
	orr r4, r4, r1, lsl #0x10
	mvn r0, #0x0
_020A3844:
	ldrb r1, [r2, #0x5a]
	cmp r1, #0x0
	beq _020A387C
	cmp r8, #0x0
	beq _020A387C
	ldr lr, [r2, #0x54]
	cmp r8, lr
	bne _020A387C
	cmp r7, #0x0
	beq _020A387C
	ldrh lr, [r2, #0x58]
	cmp r7, lr
	moveq r6, r2
	beq _020A38BC
_020A387C:
	mvn lr, #0x0
	cmp r3, lr
	beq _020A38AC
	cmp r1, #0x0
	moveq r3, r0
	moveq r6, r2
	beq _020A38AC
	ldr r1, [r2, #0x50]
	sub r1, r4, r1
	cmp r1, r3
	movhi r3, r1
	movhi r6, r2
_020A38AC:
	add r12, r12, #0x1
	cmp r12, #0x4
	add r2, r2, #0x5c
	blt _020A3844
_020A38BC:
	mov r1, r6
	add r0, r9, #0x74
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r0, r9
	add r1, r6, #0x20
	mov r2, #0x30
	bl MI_CpuCopy8
	str r4, [r6, #0x50]
	mov r0, #0x1
	strb r0, [r6, #0x5a]
	str r8, [r6, #0x54]
	mov r0, r5
	strh r7, [r6, #0x58]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020A3904: .word 0x021CA6FC

	arm_func_start FUN_020A3908
FUN_020A3908: ; 0x020A3908
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	bl OS_DisableInterrupts
	mov r1, #0x0
	ldr r4, _020A39AC ; =0x021CA6FC
	mov r5, r0
	strb r1, [r8, #0x30]
_020A392C:
	ldrb r0, [r4, #0x5a]
	cmp r0, #0x0
	beq _020A398C
	ldr r0, [r4, #0x54]
	cmp r0, r7
	bne _020A398C
	ldrh r0, [r4, #0x58]
	cmp r0, r6
	bne _020A398C
	mov r0, r4
	add r1, r8, #0x74
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r1, r8
	add r0, r4, #0x20
	mov r2, #0x30
	bl MI_CpuCopy8
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	str r0, [r4, #0x50]
	mov r0, #0x1
	strb r0, [r8, #0x30]
	b _020A399C
_020A398C:
	add r1, r1, #0x1
	cmp r1, #0x4
	add r4, r4, #0x5c
	blt _020A392C
_020A399C:
	mov r0, r5
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A39AC: .word 0x021CA6FC

	arm_func_start FUN_020A39B0
FUN_020A39B0: ; 0x020A39B0
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl OS_DisableInterrupts
	mov r6, #0x0
	ldr r4, _020A3A54 ; =0x021CA6FC
	mov r5, r0
	strb r6, [r7, #0x30]
	add r9, r7, #0x74
	mov r8, #0x20
_020A39D8:
	ldrb r0, [r4, #0x5a]
	cmp r0, #0x0
	beq _020A3A30
	ldr r0, [r4, #0x54]
	cmp r0, #0x0
	bne _020A3A30
	ldrh r0, [r4, #0x58]
	cmp r0, #0x0
	bne _020A3A30
	mov r0, r4
	mov r1, r9
	mov r2, r8
	bl memcmp
_020A3A0C: ; 0x020A3A0C
	cmp r0, #0x0
	bne _020A3A30
	mov r1, r7
	add r0, r4, #0x20
	mov r2, #0x30
	bl MI_CpuCopy8
	mov r0, #0x1
	strb r0, [r7, #0x30]
	b _020A3A40
_020A3A30:
	add r6, r6, #0x1
	cmp r6, #0x4
	add r4, r4, #0x5c
	blt _020A39D8
_020A3A40:
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020A3A54: .word 0x021CA6FC

	arm_func_start FUN_020A3A58
FUN_020A3A58: ; 0x020A3A58
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r0, r4
	add r1, r5, #0x10
	mov r2, #0x8
	bl FUN_020A4044
	ldr r0, [r5, #0x10]
	ldr r1, _020A3AC8 ; =0x021062EC
	mov r0, r0, lsr #0x3
	and r0, r0, #0x3f
	cmp r0, #0x38
	rsblt r2, r0, #0x38
	rsbge r2, r0, #0x78
	mov r0, r5
	bl FUN_020A3ACC
	mov r0, r5
	mov r1, r4
	mov r2, #0x8
	bl FUN_020A3ACC
	mov r0, r4
	mov r1, r5
	mov r2, #0x10
	bl FUN_020A4044
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A3AC8: .word 0x021062EC

	arm_func_start FUN_020A3ACC
FUN_020A3ACC:
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldr r3, [r8, #0x10]
	mov r6, r2
	add r0, r3, r6, lsl #0x3
	str r0, [r8, #0x10]
	ldr r0, [r8, #0x10]
	mov r2, r3, lsr #0x3
	cmp r0, r6, lsl #0x3
	ldrcc r0, [r8, #0x14]
	and r4, r2, #0x3f
	addcc r0, r0, #0x1
	strcc r0, [r8, #0x14]
	ldr r0, [r8, #0x14]
	rsb r5, r4, #0x40
	add r0, r0, r6, lsr #0x1d
	mov r7, r1
	str r0, [r8, #0x14]
	cmp r6, r5
	blo _020A3B6C
	add r1, r8, #0x18
	mov r0, r7
	mov r2, r5
	add r1, r1, r4
	bl MI_CpuCopy8
	mov r0, r8
	add r1, r8, #0x18
	mov r4, #0x0
	bl FUN_020A3BD8
	add r0, r5, #0x3f
	cmp r0, r6
	bhs _020A3B70
_020A3B4C:
	mov r0, r8
	add r1, r7, r5
	bl FUN_020A3BD8
	add r5, r5, #0x40
	add r0, r5, #0x3f
	cmp r0, r6
	blo _020A3B4C
	b _020A3B70
_020A3B6C:
	mov r5, #0x0
_020A3B70:
	add r1, r8, #0x18
	add r0, r7, r5
	add r1, r1, r4
	sub r2, r6, r5
	bl MI_CpuCopy8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_020A3B8C
FUN_020A3B8C: ; 0x020A3B8C
	stmdb sp!, {r4,lr}
	mov r1, #0x0
	mov r2, #0x58
	mov r4, r0
	bl MI_CpuFill8
	ldr r1, _020A3BC8 ; =0x67452301
	ldr r0, _020A3BCC ; =0xEFCDAB89
	str r1, [r4, #0x0]
	ldr r1, _020A3BD0 ; =0x98BADCFE
	str r0, [r4, #0x4]
	ldr r0, _020A3BD4 ; =0x10325476
	str r1, [r4, #0x8]
	str r0, [r4, #0xc]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A3BC8: .word 0x67452301
_020A3BCC: .word 0xEFCDAB89
_020A3BD0: .word 0x98BADCFE
_020A3BD4: .word 0x10325476

	arm_func_start FUN_020A3BD8
FUN_020A3BD8: ; 0x020A3BD8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x44
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x0]
	add r0, sp, #0x4
	mov r2, #0x40
	ldr r7, [r3, #0x0]
	ldr r6, [r3, #0x4]
	ldr r5, [r3, #0x8]
	ldr r4, [r3, #0xc]
	bl FUN_020A402C
	ldr r2, _020A4024 ; =0x021062AC
	mov r3, #0x0
	ldr r1, _020A4028 ; =0x0210632C
	mov r11, r3
	add r0, sp, #0x4
	mov r10, r2
_020A3C1C:
	ldrb r9, [r2, #0x0]
	add r8, r3, #0x1
	eor r12, r5, r4
	and r12, r6, r12
	eor r12, r4, r12
	ldr r9, [r0, r9, lsl #0x2]
	ldr lr, [r1, r3, lsl #0x2]
	add r9, r12, r9
	add r9, lr, r9
	add r9, r7, r9
	mov r7, r9, lsl #0x7
	orr r7, r7, r9, lsr #0x19
	ldrb r9, [r10, r8]
	add r7, r6, r7
	ldr r8, [r1, r8, lsl #0x2]
	ldr r9, [r0, r9, lsl #0x2]
	eor r12, r6, r5
	and r12, r7, r12
	eor r12, r5, r12
	add r9, r12, r9
	add r9, r8, r9
	add r8, r3, #0x2
	add r9, r4, r9
	mov r4, r9, lsl #0xc
	orr r4, r4, r9, lsr #0x14
	add r4, r7, r4
	ldr r9, [r1, r8, lsl #0x2]
	ldrb r12, [r10, r8]
	eor r8, r7, r6
	and r8, r4, r8
	eor r8, r6, r8
	ldr lr, [r0, r12, lsl #0x2]
	add r12, r3, #0x3
	add r8, r8, lr
	add r8, r9, r8
	add r8, r5, r8
	mov r5, r8, lsl #0x11
	orr r5, r5, r8, lsr #0xf
	add r5, r4, r5
	ldr r9, [r1, r12, lsl #0x2]
	ldrb r12, [r10, r12]
	eor r8, r4, r7
	and r8, r5, r8
	eor r8, r7, r8
	ldr r12, [r0, r12, lsl #0x2]
	add r2, r2, #0x4
	add r8, r8, r12
	add r8, r9, r8
	add r8, r6, r8
	mov r6, r8, lsl #0x16
	orr r6, r6, r8, lsr #0xa
	add r6, r5, r6
	add r3, r3, #0x4
	add r11, r11, #0x1
	cmp r11, #0x4
	blt _020A3C1C
	add r8, r10, r3
	mov r2, #0x0
	ldr r1, _020A4028 ; =0x0210632C
	add r0, sp, #0x4
	ldr lr, _020A4024 ; =0x021062AC
_020A3D10:
	ldrb r10, [r8, #0x0]
	add r9, r3, #0x1
	eor r11, r6, r5
	and r11, r4, r11
	eor r11, r5, r11
	ldr r10, [r0, r10, lsl #0x2]
	ldr r12, [r1, r3, lsl #0x2]
	add r10, r11, r10
	add r10, r12, r10
	add r10, r7, r10
	mov r7, r10, lsl #0x5
	orr r7, r7, r10, lsr #0x1b
	ldrb r10, [lr, r9]
	add r7, r6, r7
	ldr r9, [r1, r9, lsl #0x2]
	ldr r10, [r0, r10, lsl #0x2]
	eor r11, r7, r6
	and r11, r5, r11
	eor r11, r6, r11
	add r10, r11, r10
	add r10, r9, r10
	add r9, r3, #0x2
	add r10, r4, r10
	mov r4, r10, lsl #0x9
	orr r4, r4, r10, lsr #0x17
	add r4, r7, r4
	ldr r12, [r1, r9, lsl #0x2]
	ldrb r9, [lr, r9]
	eor r10, r4, r7
	and r10, r6, r10
	eor r11, r7, r10
	ldr r10, [r0, r9, lsl #0x2]
	add r9, r3, #0x3
	add r10, r11, r10
	add r10, r12, r10
	add r10, r5, r10
	mov r5, r10, lsl #0xe
	orr r5, r5, r10, lsr #0x12
	add r5, r4, r5
	ldr r10, [r1, r9, lsl #0x2]
	ldrb r11, [lr, r9]
	eor r9, r5, r4
	and r9, r7, r9
	eor r9, r4, r9
	ldr r11, [r0, r11, lsl #0x2]
	add r8, r8, #0x4
	add r9, r9, r11
	add r9, r10, r9
	add r9, r6, r9
	mov r6, r9, lsl #0x14
	orr r6, r6, r9, lsr #0xc
	add r6, r5, r6
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r2, #0x4
	blt _020A3D10
	add r8, lr, r3
	mov lr, #0x0
	ldr r2, _020A4028 ; =0x0210632C
	add r0, sp, #0x4
_020A3E00:
	ldrb r1, [r8, #0x0]
	eor r12, r6, r5
	add lr, lr, #0x1
	ldr r11, [r0, r1, lsl #0x2]
	eor r12, r4, r12
	ldr r1, [r2, r3, lsl #0x2]
	add r11, r12, r11
	add r1, r1, r11
	add r7, r7, r1
	mov r1, r7, lsl #0x4
	orr r1, r1, r7, lsr #0x1c
	add r7, r6, r1
	add r10, r3, #0x1
	ldr r1, _020A4024 ; =0x021062AC
	ldr r12, [r2, r10, lsl #0x2]
	ldrb r1, [r1, r10]
	eor r10, r7, r6
	eor r11, r5, r10
	ldr r10, [r0, r1, lsl #0x2]
	add r9, r3, #0x2
	add r10, r11, r10
	add r10, r12, r10
	add r4, r4, r10
	ldr sl, _020A4024 ; =0x021062AC
	ldr r1, [r2, r9, lsl #0x2]
	ldrb r9, [r10, r9]
	mov r10, r4, lsl #0xb
	orr r4, r10, r4, lsr #0x15
	add r4, r7, r4
	eor r10, r4, r7
	ldr r9, [r0, r9, lsl #0x2]
	eor r10, r6, r10
	add r9, r10, r9
	add r1, r1, r9
	add r5, r5, r1
	add r10, r3, #0x3
	ldr sb, _020A4024 ; =0x021062AC
	mov r1, r5, lsl #0x10
	ldrb r9, [r9, r10]
	orr r1, r1, r5, lsr #0x10
	add r5, r4, r1
	ldr r1, [r2, r10, lsl #0x2]
	eor r10, r5, r4
	ldr r9, [r0, r9, lsl #0x2]
	eor r10, r7, r10
	add r9, r10, r9
	add r1, r1, r9
	add r6, r6, r1
	mov r1, r6, lsl #0x17
	orr r1, r1, r6, lsr #0x9
	add r8, r8, #0x4
	add r6, r5, r1
	add r3, r3, #0x4
	cmp lr, #0x4
	blt _020A3E00
	ldr r0, _020A4024 ; =0x021062AC
	ldr r1, _020A4028 ; =0x0210632C
	add r8, r0, r3
	ldr lr, _020A4024 ; =0x021062AC
	mov r2, #0x0
	add r0, sp, #0x4
_020A3EF4:
	ldrb r10, [r8, #0x0]
	add r9, r3, #0x1
	mvn r11, r4
	orr r11, r6, r11
	eor r11, r5, r11
	ldr r10, [r0, r10, lsl #0x2]
	ldr r12, [r1, r3, lsl #0x2]
	add r10, r11, r10
	add r10, r12, r10
	add r10, r7, r10
	mov r7, r10, lsl #0x6
	orr r7, r7, r10, lsr #0x1a
	ldrb r10, [lr, r9]
	add r7, r6, r7
	ldr r9, [r1, r9, lsl #0x2]
	ldr r10, [r0, r10, lsl #0x2]
	mvn r11, r5
	orr r11, r7, r11
	eor r11, r6, r11
	add r10, r11, r10
	add r10, r9, r10
	add r9, r3, #0x2
	add r10, r4, r10
	mov r4, r10, lsl #0xa
	orr r4, r4, r10, lsr #0x16
	add r4, r7, r4
	ldr r12, [r1, r9, lsl #0x2]
	ldrb r9, [lr, r9]
	mvn r10, r6
	orr r10, r4, r10
	eor r11, r7, r10
	ldr r10, [r0, r9, lsl #0x2]
	add r9, r3, #0x3
	add r10, r11, r10
	add r10, r12, r10
	add r10, r5, r10
	mov r5, r10, lsl #0xf
	orr r5, r5, r10, lsr #0x11
	add r5, r4, r5
	ldr r10, [r1, r9, lsl #0x2]
	ldrb r11, [lr, r9]
	mvn r9, r7
	orr r9, r5, r9
	eor r9, r4, r9
	ldr r11, [r0, r11, lsl #0x2]
	add r8, r8, #0x4
	add r9, r9, r11
	add r9, r10, r9
	add r9, r6, r9
	mov r6, r9, lsl #0x15
	orr r6, r6, r9, lsr #0xb
	add r6, r5, r6
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r2, #0x4
	blt _020A3EF4
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r1, r0, r7
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x0]
	ldr r0, [r0, #0x4]
	add r1, r0, r6
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x4]
	ldr r0, [r0, #0x8]
	add r1, r0, r5
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x8]
	ldr r0, [r0, #0xc]
	add r1, r0, r4
	ldr r0, [sp, #0x0]
	str r1, [r0, #0xc]
	add sp, sp, #0x44
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A4024: .word 0x021062AC
_020A4028: .word 0x0210632C

	arm_func_start FUN_020A402C
FUN_020A402C: ; 0x020A402C
	ldr ip, _020A4040 ; =MI_CpuCopy8
	mov r3, r0
	mov r0, r1
	mov r1, r3
	bx r12
	.balign 4
_020A4040: .word MI_CpuCopy8

	arm_func_start FUN_020A4044
FUN_020A4044: ; 0x020A4044
	ldr ip, _020A4058 ; =MI_CpuCopy8
	mov r3, r0
	mov r0, r1
	mov r1, r3
	bx r12
	.balign 4
_020A4058: .word MI_CpuCopy8

	arm_func_start FUN_020A405C
FUN_020A405C: ; 0x020A405C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	ldr r1, _020A4094 ; =0x0210642D
	mov r5, r0
	mov r2, #0x2c
	bl FUN_020A410C
	mov r0, r4
	mov r1, r5
	mov r2, #0x14
	bl FUN_020A4930
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A4094: .word 0x0210642D

	arm_func_start FUN_020A4098
FUN_020A4098: ; 0x020A4098
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r0, r4
	add r1, r5, #0x14
	mov r2, #0x8
	bl FUN_020A4930
	ldr r0, [r5, #0x18]
	ldr r1, _020A4108 ; =0x0210642C
	mov r0, r0, lsr #0x3
	and r0, r0, #0x3f
	cmp r0, #0x38
	rsblt r2, r0, #0x38
	rsbge r2, r0, #0x78
	mov r0, r5
	bl FUN_020A410C
	mov r0, r5
	mov r1, r4
	mov r2, #0x8
	bl FUN_020A410C
	mov r0, r4
	mov r1, r5
	mov r2, #0x14
	bl FUN_020A4930
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A4108: .word 0x0210642C

	arm_func_start FUN_020A410C
FUN_020A410C:
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldr r3, [r8, #0x18]
	mov r6, r2
	add r0, r3, r6, lsl #0x3
	str r0, [r8, #0x18]
	ldr r0, [r8, #0x18]
	mov r2, r3, lsr #0x3
	cmp r0, r6, lsl #0x3
	ldrcc r0, [r8, #0x14]
	and r4, r2, #0x3f
	addcc r0, r0, #0x1
	strcc r0, [r8, #0x14]
	ldr r0, [r8, #0x14]
	rsb r5, r4, #0x40
	add r0, r0, r6, lsr #0x1d
	mov r7, r1
	str r0, [r8, #0x14]
	cmp r6, r5
	blo _020A41AC
	add r1, r8, #0x1c
	mov r0, r7
	mov r2, r5
	add r1, r1, r4
	bl MI_CpuCopy8
	mov r0, r8
	add r1, r8, #0x1c
	mov r4, #0x0
	bl FUN_020A4224
	add r0, r5, #0x3f
	cmp r0, r6
	bhs _020A41B0
_020A418C:
	mov r0, r8
	add r1, r7, r5
	bl FUN_020A4224
	add r5, r5, #0x40
	add r0, r5, #0x3f
	cmp r0, r6
	blo _020A418C
	b _020A41B0
_020A41AC:
	mov r5, #0x0
_020A41B0:
	add r1, r8, #0x1c
	add r0, r7, r5
	add r1, r1, r4
	sub r2, r6, r5
	bl MI_CpuCopy8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_020A41CC
FUN_020A41CC: ; 0x020A41CC
	stmdb sp!, {r4,lr}
	mov r1, #0x0
	mov r2, #0x5c
	mov r4, r0
	bl MI_CpuFill8
	ldr r0, _020A4210 ; =0x67452301
	ldr r1, _020A4214 ; =0xEFCDAB89
	str r0, [r4, #0x0]
	ldr r0, _020A4218 ; =0x98BADCFE
	str r1, [r4, #0x4]
	ldr r1, _020A421C ; =0x10325476
	str r0, [r4, #0x8]
	ldr r0, _020A4220 ; =0xC3D2E1F0
	str r1, [r4, #0xc]
	str r0, [r4, #0x10]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A4210: .word 0x67452301
_020A4214: .word 0xEFCDAB89
_020A4218: .word 0x98BADCFE
_020A421C: .word 0x10325476
_020A4220: .word 0xC3D2E1F0

	arm_func_start FUN_020A4224
FUN_020A4224: ; 0x020A4224
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x54
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x0]
	add r0, sp, #0x10
	mov r2, #0x40
	ldr r6, [r3, #0x0]
	ldr r7, [r3, #0x4]
	ldr r8, [r3, #0x8]
	ldr r5, [r3, #0xc]
	ldr r4, [r3, #0x10]
	bl FUN_020A48CC
	mov r2, #0x0
	ldr r3, _020A48BC ; =0x5A827999
	mov r0, r2
	add r1, sp, #0x10
_020A4264:
	eor r9, r8, r5
	mov r10, r6, lsl #0x5
	and r9, r7, r9
	orr r10, r10, r6, lsr #0x1b
	eor r9, r5, r9
	mov r11, r7, lsl #0x1e
	orr r7, r11, r7, lsr #0x2
	eor r11, r7, r8
	add r9, r10, r9
	ldr r12, [r1, r2, lsl #0x2]
	and r10, r6, r11
	add r9, r12, r9
	add r9, r9, r3
	add r4, r4, r9
	add r9, r2, #0x1
	ldr r9, [r1, r9, lsl #0x2]
	eor r10, r8, r10
	mov r11, r4, lsl #0x5
	orr r11, r11, r4, lsr #0x1b
	add r10, r11, r10
	add r10, r9, r10
	mov r9, r6, lsl #0x1e
	add r10, r10, r3
	add r5, r5, r10
	orr r6, r9, r6, lsr #0x2
	add r9, r2, #0x2
	ldr r10, [r1, r9, lsl #0x2]
	mov r9, r5, lsl #0x5
	orr r9, r9, r5, lsr #0x1b
	eor r11, r6, r7
	and r11, r4, r11
	eor r11, r7, r11
	add r9, r9, r11
	add r9, r10, r9
	add r9, r9, r3
	add r8, r8, r9
	mov r9, r4, lsl #0x1e
	orr r4, r9, r4, lsr #0x2
	add r9, r2, #0x3
	ldr r10, [r1, r9, lsl #0x2]
	mov r9, r8, lsl #0x5
	orr r9, r9, r8, lsr #0x1b
	eor r11, r4, r6
	and r11, r5, r11
	eor r11, r6, r11
	add r9, r9, r11
	add r9, r10, r9
	add r9, r9, r3
	add r7, r7, r9
	mov r9, r5, lsl #0x1e
	orr r5, r9, r5, lsr #0x2
	add r9, r2, #0x4
	ldr r10, [r1, r9, lsl #0x2]
	mov r9, r7, lsl #0x5
	orr r9, r9, r7, lsr #0x1b
	eor r11, r5, r4
	and r11, r8, r11
	eor r11, r4, r11
	add r9, r9, r11
	add r9, r10, r9
	add r9, r9, r3
	add r6, r6, r9
	mov r9, r8, lsl #0x1e
	orr r8, r9, r8, lsr #0x2
	add r2, r2, #0x5
	add r0, r0, #0x1
	cmp r0, #0x3
	blt _020A4264
	eor r0, r8, r5
	mov r2, r6, lsl #0x5
	and r0, r7, r0
	orr r3, r2, r6, lsr #0x1b
	eor r0, r5, r0
	add r3, r3, r0
	ldr r9, [sp, #0x4c]
	ldr r0, _020A48BC ; =0x5A827999
	add r3, r9, r3
	add r3, r3, r0
	mov r2, r7, lsl #0x1e
	orr r9, r2, r7, lsr #0x2
	mov r0, #0x0
	add r4, r4, r3
	bl FUN_020A4988
	eor r1, r9, r8
	mov r3, r4, lsl #0x5
	and r1, r6, r1
	mov r2, r6, lsl #0x1e
	orr r3, r3, r4, lsr #0x1b
	eor r1, r8, r1
	add r1, r3, r1
	add r3, r1, r0
	ldr r0, _020A48BC ; =0x5A827999
	add r1, sp, #0x10
	add r3, r3, r0
	orr r10, r2, r6, lsr #0x2
	mov r0, #0x1
	add r5, r5, r3
	bl FUN_020A4988
	eor r1, r10, r9
	mov r2, r5, lsl #0x5
	and r1, r4, r1
	orr r2, r2, r5, lsr #0x1b
	eor r1, r9, r1
	add r1, r2, r1
	add r2, r1, r0
	ldr r0, _020A48BC ; =0x5A827999
	mov r1, r4, lsl #0x1e
	add r0, r2, r0
	orr r6, r1, r4, lsr #0x2
	add r8, r8, r0
	add r1, sp, #0x10
	mov r0, #0x2
	bl FUN_020A4988
	mov r1, r8, lsl #0x5
	orr r2, r1, r8, lsr #0x1b
	eor r1, r6, r10
	and r1, r5, r1
	eor r1, r10, r1
	add r1, r2, r1
	add r2, r1, r0
	ldr r0, _020A48BC ; =0x5A827999
	mov r1, r5, lsl #0x1e
	add r0, r2, r0
	orr r7, r1, r5, lsr #0x2
	add r9, r9, r0
	mov r0, #0x3
	add r1, sp, #0x10
	bl FUN_020A4988
	mov r1, r9, lsl #0x5
	orr r2, r1, r9, lsr #0x1b
	eor r1, r7, r6
	and r1, r8, r1
	eor r1, r6, r1
	add r1, r2, r1
	add r2, r1, r0
	ldr r0, _020A48BC ; =0x5A827999
	mov r1, r8, lsl #0x1e
	add r0, r2, r0
	add r10, r10, r0
	mov r0, #0x0
	ldr r4, _020A48C0 ; =0x6ED9EBA1
	orr r8, r1, r8, lsr #0x2
	mov r5, #0x4
	str r0, [sp, #0xc]
	add r11, sp, #0x10
_020A44A8:
	mov r0, r5
	mov r1, r11
	bl FUN_020A4988
	mov r2, r10, lsl #0x5
	eor r1, r9, r8
	orr r2, r2, r10, lsr #0x1b
	eor r1, r7, r1
	add r1, r2, r1
	add r0, r1, r0
	add r1, r0, r4
	mov r0, r9, lsl #0x1e
	add r6, r6, r1
	orr r9, r0, r9, lsr #0x2
	add r0, r5, #0x1
	mov r1, r11
	bl FUN_020A4988
	mov r1, r6, lsl #0x5
	orr r2, r1, r6, lsr #0x1b
	eor r1, r10, r9
	eor r1, r8, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r7, r7, r0
	mov r0, r10, lsl #0x1e
	orr r10, r0, r10, lsr #0x2
	add r0, r5, #0x2
	and r5, r0, #0xf
	mov r0, r5
	mov r1, r11
	bl FUN_020A4988
	mov r1, r7, lsl #0x5
	orr r2, r1, r7, lsr #0x1b
	eor r1, r6, r10
	eor r1, r9, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r8, r8, r0
	mov r0, r6, lsl #0x1e
	orr r6, r0, r6, lsr #0x2
	add r0, r5, #0x1
	mov r1, r11
	bl FUN_020A4988
	mov r1, r8, lsl #0x5
	orr r2, r1, r8, lsr #0x1b
	eor r1, r7, r6
	eor r1, r10, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r9, r9, r0
	mov r0, r7, lsl #0x1e
	orr r7, r0, r7, lsr #0x2
	add r0, r5, #0x2
	mov r1, r11
	bl FUN_020A4988
	mov r1, r9, lsl #0x5
	orr r2, r1, r9, lsr #0x1b
	eor r1, r8, r7
	eor r1, r6, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r10, r10, r0
	mov r0, r8, lsl #0x1e
	orr r8, r0, r8, lsr #0x2
	ldr r0, [sp, #0xc]
	add r5, r5, #0x3
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	cmp r0, #0x4
	blt _020A44A8
	mov r0, #0x0
	ldr r4, _020A48C4 ; =0x8F1BBCDC
	str r0, [sp, #0x8]
	add r11, sp, #0x10
_020A45DC:
	mov r0, r5
	mov r1, r11
	bl FUN_020A4988
	orr r2, r8, r7
	mov r1, r10, lsl #0x5
	and r3, r9, r2
	and r2, r8, r7
	orr r1, r1, r10, lsr #0x1b
	orr r2, r3, r2
	add r1, r1, r2
	add r1, r1, r0
	mov r0, r9, lsl #0x1e
	add r1, r1, r4
	add r6, r6, r1
	orr r9, r0, r9, lsr #0x2
	add r0, r5, #0x1
	mov r1, r11
	bl FUN_020A4988
	orr r2, r9, r8
	mov r1, r6, lsl #0x5
	and r3, r10, r2
	and r2, r9, r8
	orr r1, r1, r6, lsr #0x1b
	orr r2, r3, r2
	add r1, r1, r2
	add r0, r1, r0
	add r0, r0, r4
	add r7, r7, r0
	mov r0, r10, lsl #0x1e
	orr r10, r0, r10, lsr #0x2
	add r0, r5, #0x2
	mov r1, r11
	bl FUN_020A4988
	orr r2, r10, r9
	mov r1, r7, lsl #0x5
	and r3, r6, r2
	and r2, r10, r9
	orr r1, r1, r7, lsr #0x1b
	orr r2, r3, r2
	add r1, r1, r2
	add r0, r1, r0
	add r0, r0, r4
	add r8, r8, r0
	mov r0, r6, lsl #0x1e
	orr r6, r0, r6, lsr #0x2
	add r0, r5, #0x3
	and r5, r0, #0xf
	mov r0, r5
	mov r1, r11
	bl FUN_020A4988
	orr r2, r6, r10
	mov r1, r8, lsl #0x5
	and r3, r7, r2
	and r2, r6, r10
	orr r1, r1, r8, lsr #0x1b
	orr r2, r3, r2
	add r1, r1, r2
	add r0, r1, r0
	add r0, r0, r4
	add r9, r9, r0
	mov r0, r7, lsl #0x1e
	orr r7, r0, r7, lsr #0x2
	add r0, r5, #0x1
	mov r1, r11
	bl FUN_020A4988
	orr r2, r7, r6
	mov r1, r9, lsl #0x5
	and r3, r8, r2
	and r2, r7, r6
	orr r1, r1, r9, lsr #0x1b
	orr r2, r3, r2
	add r1, r1, r2
	add r0, r1, r0
	add r0, r0, r4
	add r10, r10, r0
	mov r0, r8, lsl #0x1e
	orr r8, r0, r8, lsr #0x2
	ldr r0, [sp, #0x8]
	add r5, r5, #0x2
	add r0, r0, #0x1
	str r0, [sp, #0x8]
	cmp r0, #0x4
	blt _020A45DC
	mov r0, #0x0
	ldr r4, _020A48C8 ; =0xCA62C1D6
	str r0, [sp, #0x4]
	add r11, sp, #0x10
_020A4738:
	mov r0, r5
	mov r1, r11
	bl FUN_020A4988
	mov r2, r10, lsl #0x5
	eor r1, r9, r8
	orr r2, r2, r10, lsr #0x1b
	eor r1, r7, r1
	add r1, r2, r1
	add r0, r1, r0
	add r1, r0, r4
	mov r0, r9, lsl #0x1e
	add r6, r6, r1
	orr r9, r0, r9, lsr #0x2
	add r0, r5, #0x1
	mov r1, r11
	bl FUN_020A4988
	mov r1, r6, lsl #0x5
	orr r2, r1, r6, lsr #0x1b
	eor r1, r10, r9
	eor r1, r8, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r7, r7, r0
	mov r0, r10, lsl #0x1e
	orr r10, r0, r10, lsr #0x2
	add r0, r5, #0x2
	mov r1, r11
	bl FUN_020A4988
	mov r1, r7, lsl #0x5
	orr r2, r1, r7, lsr #0x1b
	eor r1, r6, r10
	eor r1, r9, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r8, r8, r0
	mov r0, r6, lsl #0x1e
	orr r6, r0, r6, lsr #0x2
	add r0, r5, #0x3
	mov r1, r11
	bl FUN_020A4988
	mov r1, r8, lsl #0x5
	orr r2, r1, r8, lsr #0x1b
	eor r1, r7, r6
	eor r1, r10, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r9, r9, r0
	mov r0, r7, lsl #0x1e
	orr r7, r0, r7, lsr #0x2
	add r0, r5, #0x4
	and r5, r0, #0xf
	mov r0, r5
	mov r1, r11
	bl FUN_020A4988
	mov r1, r9, lsl #0x5
	orr r2, r1, r9, lsr #0x1b
	eor r1, r8, r7
	eor r1, r6, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r10, r10, r0
	mov r0, r8, lsl #0x1e
	orr r8, r0, r8, lsr #0x2
	ldr r0, [sp, #0x4]
	add r5, r5, #0x1
	add r0, r0, #0x1
	str r0, [sp, #0x4]
	cmp r0, #0x4
	blt _020A4738
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r1, r0, r10
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x0]
	ldr r0, [r0, #0x4]
	add r1, r0, r9
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x4]
	ldr r0, [r0, #0x8]
	add r1, r0, r8
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x8]
	ldr r0, [r0, #0xc]
	add r1, r0, r7
	ldr r0, [sp, #0x0]
	str r1, [r0, #0xc]
	ldr r0, [r0, #0x10]
	add r1, r0, r6
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x10]
	add sp, sp, #0x54
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A48BC: .word 0x5A827999
_020A48C0: .word 0x6ED9EBA1
_020A48C4: .word 0x8F1BBCDC
_020A48C8: .word 0xCA62C1D6

	arm_func_start FUN_020A48CC
FUN_020A48CC: ; 0x020A48CC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	addls sp, sp, #0x4
	mov r3, #0x0
	ldmlsia sp!, {r4-r5,lr}
	bxls lr
_020A48E8:
	add r12, r3, #0x1
	ldrb lr, [r1, r3]
	add r4, r3, #0x2
	add r5, r3, #0x3
	ldrb r12, [r1, r12]
	mov lr, lr, lsl #0x18
	add r3, r3, #0x4
	ldrb r4, [r1, r4]
	orr r12, lr, r12, lsl #0x10
	ldrb lr, [r1, r5]
	orr r4, r12, r4, lsl #0x8
	cmp r3, r2
	orr r4, lr, r4
	str r4, [r0], #0x4
	blo _020A48E8
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A4930
FUN_020A4930: ; 0x020A4930
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	movs r12, r2, lsr #0x2
	mov lr, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
_020A494C:
	ldr r3, [r1], #0x4
	add lr, lr, #0x1
	mov r2, r3, lsr #0x18
	strb r2, [r0, #0x0]
	mov r2, r3, lsr #0x10
	strb r2, [r0, #0x1]
	mov r2, r3, lsr #0x8
	strb r2, [r0, #0x2]
	strb r3, [r0, #0x3]
	cmp lr, r12
	add r0, r0, #0x4
	blo _020A494C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A4988
FUN_020A4988: ; 0x020A4988
	add r2, r0, #0xd
	add r12, r0, #0x2
	and r3, r2, #0xf
	eor r2, r0, #0x8
	and r12, r12, #0xf
	ldr r3, [r1, r3, lsl #0x2]
	ldr r2, [r1, r2, lsl #0x2]
	ldr r12, [r1, r12, lsl #0x2]
	eor r2, r3, r2
	ldr r3, [r1, r0, lsl #0x2]
	eor r2, r12, r2
	eor r3, r3, r2
	mov r2, r3, lsl #0x1
	orr r2, r2, r3, lsr #0x1f
	str r2, [r1, r0, lsl #0x2]
	ldr r0, [r1, r0, lsl #0x2]
	bx lr

	arm_func_start FUN_020A49CC
FUN_020A49CC: ; 0x020A49CC
	stmdb sp!, {r4-r6,lr}
	cmp r2, #0x0
	add r3, r0, #0x2
	ldrb lr, [r0, #0x0]
	ldrb r12, [r0, #0x1]
	mov r4, #0x0
	ble _020A4A2C
_020A49E8:
	add r5, lr, #0x1
	and lr, r5, #0xff
	ldrb r6, [r3, lr]
	add r5, r12, r6
	and r12, r5, #0xff
	ldrb r5, [r3, r12]
	strb r5, [r3, lr]
	add r5, r6, r5
	strb r6, [r3, r12]
	and r5, r5, #0xff
	ldrb r6, [r1, r4]
	ldrb r5, [r3, r5]
	eor r5, r6, r5
	strb r5, [r1, r4]
	add r4, r4, #0x1
	cmp r4, r2
	blt _020A49E8
_020A4A2C:
	strb lr, [r0, #0x0]
	strb r12, [r0, #0x1]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_020A4A3C
FUN_020A4A3C: ; 0x020A4A3C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r3, #0x0
	strb r3, [r0, #0x0]
	strb r3, [r0, #0x1]
	add r7, r0, #0x2
_020A4A54:
	strb r3, [r7, r3]
	add r3, r3, #0x1
	cmp r3, #0x100
	blt _020A4A54
	mov r5, #0x0
	mov r6, r5
	mov r4, r5
	mov r0, r5
_020A4A74:
	ldrb lr, [r7, r4]
	ldrb r12, [r1, r5]
	add r3, r5, #0x1
	and r5, r3, #0xff
	add r3, lr, r12
	add r3, r6, r3
	and r6, r3, #0xff
	ldrb r3, [r7, r6]
	cmp r5, r2
	movge r5, r0
	strb r3, [r7, r4]
	add r4, r4, #0x1
	strb lr, [r7, r6]
	cmp r4, #0x100
	blt _020A4A74
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_020A4ABC
FUN_020A4ABC: ; 0x020A4ABC
	ldrh r1, [r0, #0x0]
	mov r0, #0x0
	bx lr

	arm_func_start FUN_020A4AC8
FUN_020A4AC8: ; 0x020A4AC8
	ldrh r1, [r0, #0x0]
	ldrh r0, [r0, #-0x2]
	mov r0, r0, lsl #0x10
	bx lr

	arm_func_start FUN_020A4AD8
FUN_020A4AD8: ; 0x020A4AD8
	ldrh r1, [r0, #0x0]
	ldrh r2, [r0, #-0x2]
	ldrh r3, [r0, #-0x4]
	orr r0, r3, r2, lsl #0x10
	bx lr

	arm_func_start FUN_020A4AEC
FUN_020A4AEC: ; 0x020A4AEC
	ldrh r2, [r0, #0x0]
	ldrh r3, [r0, #-0x2]
	orr r1, r3, r2, lsl #0x10
	ldrh r2, [r0, #-0x4]
	ldrh r3, [r0, #-0x6]
	orr r0, r3, r2, lsl #0x10
	bx lr

	arm_func_start FUN_020A4B08
FUN_020A4B08: ; 0x020A4B08
	sub r3, r2, #0x1
	cmp r2, #0x1
	add r0, r0, r3
	ble _020A4B40
_020A4B18:
	ldrh r3, [r1, #0x0]
	sub r2, r2, #0x2
	sub r12, r0, #0x1
	strb r3, [r0, #0x0]
	ldrh r3, [r1], #0x2
	cmp r2, #0x1
	sub r0, r0, #0x2
	mov r3, r3, asr #0x8
	strb r3, [r12, #0x0]
	bgt _020A4B18
_020A4B40:
	cmp r2, #0x0
	ldrgth r1, [r1, #0x0]
	strgtb r1, [r0, #0x0]
	bx lr

	arm_func_start FUN_020A4B50
FUN_020A4B50: ; 0x020A4B50
	stmdb sp!, {r4-r6,lr}
	mov r6, r1
	mov r5, r2
	mov r2, r3, lsl #0x1
	mov r1, #0x0
	mov r4, r0
	bl MI_CpuFill8
	sub r0, r5, #0x1
	cmp r5, #0x1
	add r6, r6, r0
	ble _020A4B9C
_020A4B7C:
	ldrb r1, [r6, #0x0]
	ldrb r0, [r6, #-0x1]
	sub r5, r5, #0x2
	cmp r5, #0x1
	add r0, r1, r0, lsl #0x8
	strh r0, [r4], #0x2
	sub r6, r6, #0x2
	bgt _020A4B7C
_020A4B9C:
	cmp r5, #0x0
	ldrgtb r0, [r6, #0x0]
	strgth r0, [r4, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_020A4BB0
FUN_020A4BB0: ; 0x020A4BB0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	mov r10, r3
	mov r3, #0x16
	mul r4, r10, r3
	ldr r3, _020A4DE0 ; =0x021C8EC8
	mov r11, r0
	ldr r3, [r3, #0x0]
	mov r0, r4
	ldr r9, [sp, #0x58]
	str r1, [sp, #0x14]
	str r2, [sp, #0x18]
	blx r3
	str r0, [sp, #0x1c]
	cmp r0, #0x0
	addeq sp, sp, #0x34
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	mov r2, r4
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, [sp, #0x1c]
	mov r1, r10
	add r6, r0, r10, lsl #0x1
	add r0, r6, r10, lsl #0x1
	add r5, r0, r10, lsl #0x1
	add r4, r5, r10, lsl #0x1
	str r0, [sp, #0x20]
	add r0, r4, r10, lsl #0x1
	str r0, [sp, #0x24]
	add r7, r0, r10, lsl #0x1
	mov r0, r9
	bl thunk_FUN_020a5a28
	mov r8, r0
	ldr r0, [sp, #0x1c]
	mov r2, #0x1
	mov r1, r8, lsl #0x1
	strh r2, [r0, r1]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x1c]
	str r0, [sp, #0x0]
	mov r0, r6
	mov r2, r9
	mov r3, r10
	bl FUN_020A4F2C
	ldr r1, [sp, #0x1c]
	mov r0, r5
	mov r2, r6
	mov r3, r10
	bl FUN_020A5608
	mov r0, r6
	mov r1, r5
	mov r2, #0x1
	mov r3, r10
	bl FUN_020A5748
	str r10, [sp, #0x0]
	mov r0, r6
	mov r1, r6
	mov r2, r9
	mov r3, #0x0
	str r7, [sp, #0x4]
	bl FUN_020A5240
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x20]
	ldr r2, [sp, #0x1c]
	mov r3, r10
	bl FUN_020A5608
	ldr r1, [sp, #0x20]
	str r10, [sp, #0x0]
	mov r0, #0x0
	mov r2, r9
	mov r3, r1
	str r7, [sp, #0x4]
	bl FUN_020A5240
	str r10, [sp, #0x0]
	ldr r1, [sp, #0x1c]
	mov r0, #0x0
	mov r2, r9
	mov r3, r11
	str r7, [sp, #0x4]
	bl FUN_020A5240
	movs r0, r8, lsl #0x4
	mov r7, #0x0
	str r0, [sp, #0x28]
	beq _020A4D9C
	mov r0, #0x1
	str r0, [sp, #0x2c]
	mov r0, #0x8000
	str r0, [sp, #0x30]
_020A4D14:
	str r8, [sp, #0x0]
	str r9, [sp, #0x4]
	str r6, [sp, #0x8]
	str r5, [sp, #0xc]
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x2c]
	mov r0, r11
	mov r3, r10
	str r4, [sp, #0x10]
	bl FUN_020A4DE8
	ldr r0, [sp, #0x30]
	and r1, r7, #0xf
	mov r0, r0, lsr r1
	sub r1, r8, r7, asr #0x4
	sub r1, r1, #0x1
	mov r2, r1, lsl #0x1
	ldr r1, [sp, #0x18]
	ldrh r1, [r1, r2]
	ands r0, r0, r1
	beq _020A4D8C
	str r8, [sp, #0x0]
	str r9, [sp, #0x4]
	str r6, [sp, #0x8]
	str r5, [sp, #0xc]
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x20]
	mov r0, r11
	mov r3, r10
	str r4, [sp, #0x10]
	bl FUN_020A4DE8
_020A4D8C:
	ldr r0, [sp, #0x28]
	add r7, r7, #0x1
	cmp r7, r0
	blo _020A4D14
_020A4D9C:
	str r8, [sp, #0x0]
	str r9, [sp, #0x4]
	str r6, [sp, #0x8]
	str r5, [sp, #0xc]
	ldr r1, [sp, #0x24]
	mov r0, r11
	mov r3, r10
	mov r2, #0x0
	str r4, [sp, #0x10]
	bl FUN_020A4DE8
	ldr r1, _020A4DE4 ; =0x021C8EF4
	ldr r0, [sp, #0x1c]
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A4DE0: .word 0x021C8EC8
_020A4DE4: .word 0x021C8EF4

	arm_func_start FUN_020A4DE8
FUN_020A4DE8: ; 0x020A4DE8
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r5, r3
	mov r7, r5, lsl #0x1
	mov r8, r2
	mov r2, r7
	mov r6, r0
	mov r9, r1
	ldr r4, [sp, #0x20]
	bl MI_CpuCopy8
	cmp r8, #0x1
	bne _020A4E2C
	mov r0, r6
	mov r1, r9
	mov r2, r5
	bl FUN_020A5438
	b _020A4E48
_020A4E2C:
	cmp r8, #0x0
	beq _020A4E48
	mov r0, r6
	mov r1, r9
	mov r2, r8
	mov r3, r5
	bl FUN_020A5608
_020A4E48:
	ldr r0, [sp, #0x2c]
	ldr r2, [sp, #0x28]
	mov r1, r6
	mov r3, r4
	bl FUN_020A5608
	sub r1, r5, r4
	ldr r0, [sp, #0x2c]
	mov r8, r1, lsl #0x1
	mov r2, r8
	add r0, r0, r4, lsl #0x1
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, [sp, #0x30]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x24]
	mov r3, r5
	bl FUN_020A5608
	mov r0, r6
	mov r1, r6
	ldr r2, [sp, #0x30]
	mov r3, r5
	bl FUN_020A5930
	mov r2, r8
	mov r0, r6
	add r1, r6, r4, lsl #0x1
	bl memmove
	add r0, r6, r5, lsl #0x1
	sub r0, r0, r4, lsl #0x1
	mov r2, r4, lsl #0x1
	mov r1, #0x0
	bl MI_CpuFill8
	mov r0, r6
	ldr r1, [sp, #0x24]
	mov r2, r5
	bl FUN_020A570C
_020A4ED4: ; 0x020A4ED4
	cmp r0, #0x0
	beq _020A4EF0
	cmp r0, #0x1
	beq _020A4F0C
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
_020A4EF0:
	mov r0, r6
	mov r2, r7
	mov r1, #0x0
	bl MI_CpuFill8
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
_020A4F0C:
	ldr r2, [sp, #0x24]
	mov r0, r6
	mov r1, r6
	mov r3, r5
	bl FUN_020A57BC
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_020A4F2C
FUN_020A4F2C: ; 0x020A4F2C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	ldr r9, [sp, #0x38]
	mov r10, r3
	add r11, r9, r10, lsl #0x1
	add r8, r11, r10, lsl #0x1
	add r7, r8, r10, lsl #0x1
	add r6, r7, r10, lsl #0x1
	add r5, r6, r10, lsl #0x1
	str r0, [sp, #0x8]
	mov r0, r1
	add r1, r5, r10, lsl #0x1
	str r1, [sp, #0x10]
	mov r4, r10, lsl #0x1
	str r2, [sp, #0xc]
	mov r1, r9
	mov r2, r4
	bl MI_CpuCopy8
	ldr r0, [sp, #0xc]
	mov r1, r8
	mov r2, r4
	bl MI_CpuCopy8
	mov r0, #0x1
	strh r0, [r8, r4]
	mov r0, r9
	mov r1, r10
	bl FUN_020A59DC
_020A4F98: ; 0x020A4F98
	cmp r0, #0x0
	ble _020A503C
_020A4FA0:
	ldr r3, [sp, #0x10]
	str r10, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r0, r11
	mov r1, r8
	mov r2, r9
	mov r3, r5
	bl FUN_020A5240
	mov r0, r9
	mov r1, r8
	mov r2, r4
	bl MI_CpuCopy8
	mov r0, r5
	mov r1, r9
	mov r2, r4
	bl MI_CpuCopy8
	mov r0, r5
	mov r1, r11
	mov r2, r7
	mov r3, r10
	bl FUN_020A5608
	mov r0, r5
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl FUN_020A57BC
	mov r0, r7
	mov r1, r6
	mov r2, r4
	bl MI_CpuCopy8
	mov r0, r5
	mov r1, r7
	mov r2, r4
	bl MI_CpuCopy8
	mov r0, r9
	mov r1, r10
	bl FUN_020A59DC
_020A5034: ; 0x020A5034
	cmp r0, #0x0
	bgt _020A4FA0
_020A503C:
	ldr r2, [sp, #0xc]
	mov r0, r6
	mov r1, r6
	mov r3, r10
	bl FUN_020A5930
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	ldr r4, [sp, #0x10]
	str r10, [sp, #0x0]
	mov r1, r6
	mov r0, #0x0
	str r4, [sp, #0x4]
	bl FUN_020A5240
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_020A507C
FUN_020A507C: ; 0x020A507C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	ldr r4, _020A5238 ; =0x021C8EC8
	mov r8, r3
	ldr r3, [r4, #0x0]
	mov r10, r0
	mov r0, r8, lsl #0x3
	ldr r7, [sp, #0x40]
	str r1, [sp, #0x8]
	mov r9, r2
	blx r3
	movs r6, r0
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	sub r1, r8, #0x1
	add r0, r10, #0x2
	mov r2, r1, lsl #0x1
	mov r1, #0x0
	add r11, r6, r8, lsl #0x1
	bl MI_CpuFill8
	mov r2, #0x1
	mov r0, r9
	mov r1, r8
	strh r2, [r10, #0x0]
	bl thunk_FUN_020a5a28
_020A50E4: ; 0x020A50E4
	sub r0, r8, r0
	mov r5, r0, lsl #0x4
	mov r4, r8, lsl #0x4
	cmp r5, r4
	bhs _020A5140
	mov r0, #0x8000
_020A50FC:
	sub r1, r8, r5, asr #0x4
	sub r1, r1, #0x1
	mov r1, r1, lsl #0x1
	and r2, r5, #0xf
	ldrh r1, [r9, r1]
	mov r2, r0, lsr r2
	ands r1, r2, r1
	beq _020A5134
	ldr r0, [sp, #0x8]
	mov r1, r10
	mov r2, r8, lsl #0x1
	bl MI_CpuCopy8
	add r5, r5, #0x1
	b _020A5140
_020A5134:
	add r5, r5, #0x1
	cmp r5, r4
	blo _020A50FC
_020A5140:
	cmp r5, r4
	bhs _020A521C
	mov r0, r8, lsl #0x1
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	mov r0, #0x8000
	str r0, [sp, #0x14]
_020A5160:
	mov r0, r6
	mov r1, r10
	mov r2, r8
	bl FUN_020A5438
	ldr r2, [sp, #0xc]
	mov r0, r6
	mov r1, r10
	bl MI_CpuCopy8
_020A5180: ; 0x020A5180
	cmp r7, #0x0
	beq _020A51A4
	ldr r0, [sp, #0x10]
	str r8, [sp, #0x0]
	mov r1, r10
	mov r2, r7
	mov r3, r10
	str r11, [sp, #0x4]
	bl FUN_020A5240
_020A51A4:
	sub r0, r8, r5, asr #0x4
	sub r0, r0, #0x1
	mov r1, r0, lsl #0x1
	ldr r0, [sp, #0x14]
	and r2, r5, #0xf
	mov r2, r0, lsr r2
	ldrh r0, [r9, r1]
	ands r0, r2, r0
	beq _020A5210
	ldr r2, [sp, #0x8]
	mov r0, r6
	mov r1, r10
	mov r3, r8
	bl FUN_020A5608
	ldr r2, [sp, #0xc]
	mov r0, r6
	mov r1, r10
	bl MI_CpuCopy8
_020A51EC: ; 0x020A51EC
	cmp r7, #0x0
	beq _020A5210
	ldr r0, [sp, #0x10]
	str r8, [sp, #0x0]
	mov r1, r10
	mov r2, r7
	mov r3, r10
	str r11, [sp, #0x4]
	bl FUN_020A5240
_020A5210:
	add r5, r5, #0x1
	cmp r5, r4
	blo _020A5160
_020A521C:
	ldr r1, _020A523C ; =0x021C8EF4
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A5238: .word 0x021C8EC8
_020A523C: .word 0x021C8EF4

	arm_func_start FUN_020A5240
FUN_020A5240: ; 0x020A5240
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x24
	ldr r9, [sp, #0x48]
	ldr r6, [sp, #0x4c]
	str r1, [sp, #0x4]
	add r5, r6, r9, lsl #0x1
	str r0, [sp, #0x0]
	mov r10, r2
	mov r0, r5
	mov r2, r9, lsl #0x2
	mov r1, #0x0
	str r3, [sp, #0x8]
	add r4, r5, r9, lsl #0x1
	bl MI_CpuFill8
	ldr r0, [sp, #0x4]
	mov r1, r9
	bl thunk_FUN_020a5a28
	mov r11, r0
	mov r0, r10
	mov r1, r9
	bl thunk_FUN_020a5a28
	mov r7, r0
	cmp r11, #0x0
	ble _020A53E8
	cmp r7, #0x0
	ble _020A53E8
	sub r0, r9, r11
	add r0, r7, r0
	sub r8, r0, #0x1
	cmp r8, r9
	blt _020A52D0
	ldr r0, [sp, #0x4]
	mov r1, r4
	mov r2, r9, lsl #0x1
	bl MI_CpuCopy8
	b _020A53E8
_020A52D0:
	ldr r0, [sp, #0x4]
	add r1, r5, r8, lsl #0x1
	mov r2, r11, lsl #0x1
	bl MI_CpuCopy8
	cmp r7, #0x2
	ble _020A5304
	add r0, r10, r7, lsl #0x1
	sub r0, r0, #0x2
	mov r7, r7, lsl #0x1
	bl FUN_020A4AD8
	str r0, [sp, #0x14]
	str r1, [sp, #0x10]
	b _020A5340
_020A5304:
	cmp r7, #0x1
	ble _020A5328
	add r0, r10, r7, lsl #0x1
	sub r0, r0, #0x2
	mov r7, r7, lsl #0x1
	bl FUN_020A4AC8
	str r0, [sp, #0x14]
	str r1, [sp, #0x10]
	b _020A5340
_020A5328:
	add r0, r10, r7, lsl #0x1
	sub r0, r0, #0x2
	mov r7, r7, lsl #0x1
	bl FUN_020A4ABC
	str r0, [sp, #0x14]
	str r1, [sp, #0x10]
_020A5340:
	cmp r8, r9
	bge _020A53E8
	mov r0, r9, lsl #0x1
	sub r0, r0, #0x1
	mov r11, r0, lsl #0x1
	add r0, r4, r7
	str r0, [sp, #0x1c]
_020A535C:
	mov r1, r5
	add r0, r5, #0x2
	mov r2, r11
	bl memmove
	ldr r0, [sp, #0x1c]
	bl FUN_020A4AEC
	ldr r2, [sp, #0x14]
	ldr r3, [sp, #0x10]
	bl _ll_udiv
	mov r7, r0
	ldr r0, _020A5434 ; =0x0000FFFF
	cmp r7, r0
	movhi r7, r0
_020A5390:
	mov r2, r7, lsl #0x10
	mov r0, r6
	mov r1, r10
	mov r2, r2, lsr #0x10
	mov r3, r9
	bl FUN_020A5584
	mov r0, r4
	mov r1, r6
	mov r2, r9
	bl FUN_020A570C
_020A53B8: ; 0x020A53B8
	cmp r0, #0x0
	sublt r7, r7, #0x1
	blt _020A5390
	mov r0, r4
	mov r1, r4
	mov r2, r6
	mov r3, r9
	bl FUN_020A57BC
	strh r7, [r5, #0x0]
	add r8, r8, #0x1
	cmp r8, r9
	blt _020A535C
_020A53E8:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _020A5404
	ldr r1, [sp, #0x0]
	mov r0, r5
	mov r2, r9, lsl #0x1
	bl MI_CpuCopy8
_020A5404:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	addeq sp, sp, #0x24
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r1, [sp, #0x8]
	mov r0, r4
	mov r2, r9, lsl #0x1
	bl MI_CpuCopy8
	add sp, sp, #0x24
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A5434: .word 0x0000FFFF

	arm_func_start FUN_020A5438
FUN_020A5438: ; 0x020A5438
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	mov r8, r2
	mov r10, r0
	mov r0, r9
	mov r1, r8
	bl thunk_FUN_020a5a28
	mov r11, r0
	mov r0, r11, lsl #0x1
	cmp r0, r8
	bge _020A547C
	sub r1, r8, r0
	add r0, r10, r0, lsl #0x1
	mov r2, r1, lsl #0x1
	mov r1, #0x0
	bl MI_CpuFill8
_020A547C:
	cmp r11, #0x0
	mov r1, #0x0
	ble _020A54D4
	mov r0, r1
	sub r4, r8, #0x1
_020A5490:
	cmp r0, r8
	bge _020A54D4
	mov r2, r1, lsl #0x1
	ldrh r5, [r9, r2]
	mov r2, r0, lsl #0x1
	cmp r0, r4
	mul r3, r5, r5
	strh r3, [r10, r2]
	beq _020A54D4
	add r2, r0, #0x1
	add r1, r1, #0x1
	mov r3, r3, lsr #0x10
	mov r2, r2, lsl #0x1
	strh r3, [r10, r2]
	cmp r1, r11
	add r0, r0, #0x2
	blt _020A5490
_020A54D4:
	cmp r11, #0x0
	mov r6, #0x0
	addle sp, sp, #0x4
	ldmleia sp!, {r4-r11,lr}
	bxle lr
_020A54E8:
	add r7, r6, #0x1
	b _020A5554
_020A54F0:
	mov r1, r7, lsl #0x1
	mov r0, r6, lsl #0x1
	ldrh r1, [r9, r1]
	ldrh r0, [r9, r0]
	mul r4, r1, r0
	ldr r0, _020A5580 ; =0x7FFF8000
	cmp r4, r0
	bhi _020A5528
	mov r0, r10
	mov r2, r5
	mov r3, r8
	mov r1, r4, lsl #0x1
	bl FUN_020A56C4
	b _020A5550
_020A5528:
	mov r0, r10
	mov r1, r4
	mov r2, r5
	mov r3, r8
	bl FUN_020A56C4
	mov r0, r10
	mov r1, r4
	mov r2, r5
	mov r3, r8
	bl FUN_020A56C4
_020A5550:
	add r7, r7, #0x1
_020A5554:
	cmp r7, r11
	bge _020A5568
	add r5, r6, r7
	cmp r5, r8
	blt _020A54F0
_020A5568:
	add r6, r6, #0x1
	cmp r6, r11
	blt _020A54E8
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A5580: .word 0x7FFF8000

	arm_func_start FUN_020A5584
FUN_020A5584: ; 0x020A5584
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	mov r4, r3
	mov r7, r0
	mov r0, r6
	mov r1, r4
	mov r5, r2
	bl thunk_FUN_020a5a28
	mov r3, #0x0
	mov r12, r3
	cmp r0, #0x0
	ble _020A55D8
_020A55B8:
	mov r2, r12, lsl #0x1
	ldrh r1, [r6, r2]
	add r12, r12, #0x1
	cmp r12, r0
	mla r1, r5, r1, r3
	strh r1, [r7, r2]
	mov r3, r1, lsr #0x10
	blt _020A55B8
_020A55D8:
	cmp r12, r4
	movlt r0, r12, lsl #0x1
	addlt r12, r12, #0x1
	sub r1, r4, r12
	strlth r3, [r7, r0]
	mov r2, r1, lsl #0x1
	add r0, r7, r12, lsl #0x1
	mov r1, #0x0
	bl MI_CpuFill8
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_020A5608
FUN_020A5608: ; 0x020A5608
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r8, r3
	mov r10, r1
	mov r9, r2
	mov r2, r8, lsl #0x1
	mov r1, #0x0
	mov r11, r0
	bl MI_CpuFill8
	mov r0, r10
	mov r1, r8
	bl thunk_FUN_020a5a28
	mov r5, r0
	mov r0, r9
	mov r1, r8
	bl thunk_FUN_020a5a28
_020A5648: ; 0x020A5648
	str r0, [sp, #0x0]
	cmp r0, #0x0
	mov r7, #0x0
	addle sp, sp, #0xc
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	str r7, [sp, #0x4]
_020A5664:
	ldr r6, [sp, #0x4]
	sub r4, r8, r7
	b _020A5698
_020A5670:
	mov r1, r6, lsl #0x1
	mov r0, r7, lsl #0x1
	ldrh r2, [r10, r1]
	ldrh r1, [r9, r0]
	mov r0, r11
	mov r3, r8
	mul r1, r2, r1
	add r2, r7, r6
	bl FUN_020A56C4
	add r6, r6, #0x1
_020A5698:
	cmp r6, r5
	bge _020A56A8
	cmp r6, r4
	blt _020A5670
_020A56A8:
	ldr r0, [sp, #0x0]
	add r7, r7, #0x1
	cmp r7, r0
	blt _020A5664
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_020A56C4
FUN_020A56C4: ; 0x020A56C4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	b _020A56E8
_020A56D0:
	mov lr, r2, lsl #0x1
	ldrh r12, [r0, lr]
	add r2, r2, #0x1
	add r1, r1, r12
	strh r1, [r0, lr]
	mov r1, r1, lsr #0x10
_020A56E8:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	cmp r2, r3
	blt _020A56D0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A570C
FUN_020A570C:
	subs r12, r2, #0x1
	bmi _020A5740
_020A5714:
	mov r2, r12, lsl #0x1
	ldrh r3, [r1, r2]
	ldrh r2, [r0, r2]
	cmp r2, r3
	movhi r0, #0x1
	bxhi lr
	cmp r2, r3
	mvncc r0, #0x0
	bxcc lr
	subs r12, r12, #0x1
	bpl _020A5714
_020A5740:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_020A5748
FUN_020A5748: ; 0x020A5748
	stmdb sp!, {r4,lr}
	cmp r3, #0x0
	mov r4, #0x0
	ble _020A5780
_020A5758:
	mov lr, r4, lsl #0x1
	ldrh r12, [r1, lr]
	sub r12, r12, r2
	mov r2, r12, lsr #0x10
	strh r12, [r0, lr]
	ands r2, r2, #0x1
	beq _020A5780
	add r4, r4, #0x1
	cmp r4, r3
	blt _020A5758
_020A5780:
	cmp r0, r1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r4, r4, #0x1
	cmp r4, r3
	ldmgeia sp!, {r4,lr}
	bxge lr
_020A579C:
	mov r12, r4, lsl #0x1
	ldrh r2, [r1, r12]
	add r4, r4, #0x1
	cmp r4, r3
	strh r2, [r0, r12]
	blt _020A579C
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A57BC
FUN_020A57BC: ; 0x020A57BC
	stmdb sp!, {r4-r8,lr}
	mov r7, r1
	mov r5, r3
	mov r8, r0
	mov r6, r2
	mov r0, r7
	mov r1, r5
	bl thunk_FUN_020a5a28
	mov r4, r0
	mov r0, r6
	mov r1, r5
	bl thunk_FUN_020a5a28
_020A57EC: ; 0x020A57EC
	cmp r4, r0
	movlt r4, r0
	mov r3, #0x0
	cmp r4, r5
	addne r4, r4, #0x1
	mov r12, r3
	b _020A5828
_020A5808:
	mov r2, r12, lsl #0x1
	ldrh r1, [r7, r2]
	ldrh r0, [r6, r2]
	add r12, r12, #0x1
	sub r0, r1, r0
	add r0, r3, r0
	strh r0, [r8, r2]
	mov r3, r0, asr #0x10
_020A5828:
	cmp r12, r4
	blt _020A5808
	cmp r12, r5
	bge _020A5840
	cmp r3, #0x0
	bne _020A5808
_020A5840:
	cmp r8, r7
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	cmp r8, r6
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	sub r1, r5, r12
	add r0, r8, r12, lsl #0x1
	mov r2, r1, lsl #0x1
	mov r1, #0x0
	bl MI_CpuFill8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_020A5874
FUN_020A5874: ; 0x020A5874
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r1
	cmp r3, #0x0
	mov r12, #0x0
	ble _020A58A8
_020A588C:
	mov r2, r12, lsl #0x1
	ldrh r1, [r0, r2]
	add r12, r12, #0x1
	cmp r12, r3
	mvn r1, r1
	strh r1, [r0, r2]
	blt _020A588C
_020A58A8:
	mov r1, r0
	mov r2, #0x1
	bl FUN_020A58C0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A58C0
FUN_020A58C0: ; 0x020A58C0
	stmdb sp!, {r4,lr}
	cmp r3, #0x0
	mov r4, #0x0
	ble _020A58F4
_020A58D0:
	mov lr, r4, lsl #0x1
	ldrh r12, [r1, lr]
	add r2, r2, r12
	strh r2, [r0, lr]
	movs r2, r2, lsr #0x10
	beq _020A58F4
	add r4, r4, #0x1
	cmp r4, r3
	blt _020A58D0
_020A58F4:
	cmp r0, r1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r4, r4, #0x1
	cmp r4, r3
	ldmgeia sp!, {r4,lr}
	bxge lr
_020A5910:
	mov r12, r4, lsl #0x1
	ldrh r2, [r1, r12]
	add r4, r4, #0x1
	cmp r4, r3
	strh r2, [r0, r12]
	blt _020A5910
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A5930
FUN_020A5930: ; 0x020A5930
	stmdb sp!, {r4-r8,lr}
	mov r7, r1
	mov r5, r3
	mov r8, r0
	mov r6, r2
	mov r0, r7
	mov r1, r5
	bl thunk_FUN_020a5a28
	mov r4, r0
	mov r0, r6
	mov r1, r5
	bl thunk_FUN_020a5a28
_020A5960: ; 0x020A5960
	cmp r4, r0
	movlt r4, r0
	cmp r4, r5
	addne r4, r4, #0x1
	mov r3, #0x0
	mov r12, r3
	cmp r4, #0x0
	ble _020A59A8
_020A5980:
	mov r2, r12, lsl #0x1
	ldrh r1, [r7, r2]
	ldrh r0, [r6, r2]
	add r12, r12, #0x1
	cmp r12, r4
	add r0, r1, r0
	add r0, r3, r0
	strh r0, [r8, r2]
	mov r3, r0, lsr #0x10
	blt _020A5980
_020A59A8:
	cmp r8, r7
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	cmp r8, r6
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	sub r1, r5, r12
	add r0, r8, r12, lsl #0x1
	mov r2, r1, lsl #0x1
	mov r1, #0x0
	bl MI_CpuFill8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_020A59DC
FUN_020A59DC:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	sub r2, r1, #0x1
	mov r2, r2, lsl #0x1
	ldrh r2, [r0, r2]
	ands r2, r2, #0x8000
	addne sp, sp, #0x4
	mvnne r0, #0x0
	ldmneia sp!, {lr}
	bxne lr
	bl thunk_FUN_020a5a28
_020A5A08: ; 0x020A5A08
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start thunk_FUN_020a5a28
thunk_FUN_020a5a28:
	b _020A5A28
_020A5A24:
	sub r1, r1, #0x1
_020A5A28:
	cmp r1, #0x0
	beq _020A5A44
	sub r2, r1, #0x1
	mov r2, r2, lsl #0x1
	ldrh r2, [r0, r2]
	cmp r2, #0x0
	beq _020A5A24
_020A5A44:
	mov r0, r1
	bx lr

	arm_func_start FUN_020A5A4C
FUN_020A5A4C: ; 0x020A5A4C
	mov r1, r0
	mov r0, #0x0
	mov r3, #0x1
_020A5A58:
	clz r2, r1
	rsbs r2, r2, #0x1f
	bxcc lr
	bic r1, r1, r3, lsl r2
	add r0, r0, #0x1
	b _020A5A58

	arm_func_start FUN_020A5A70
FUN_020A5A70: ; 0x020A5A70
	clz r0, r0
	bx lr

	arm_func_start FUN_020A5A78
FUN_020A5A78: ; 0x020A5A78
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	bne _020A5D80
	ldr r2, _020A5DA8 ; =0x021CA86C
	mov r0, #0x0
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2000
	strb r0, [r1, #0x26b]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x82]
	ldr r3, [r2, #0x0]
	add r1, r3, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0xd
	addls pc, pc, r1, lsl #0x2
	b _020A5D4C
_020A5AC4:
	b _020A5D4C
_020A5AC8:
	b _020A5D4C
_020A5ACC:
	b _020A5D4C
_020A5AD0:
	b _020A5D4C
_020A5AD4:
	b _020A5D4C
_020A5AD8:
	b _020A5AFC
_020A5ADC:
	b _020A5AFC
_020A5AE0:
	b _020A5B24
_020A5AE4:
	b _020A5B4C
_020A5AE8:
	b _020A5C74
_020A5AEC:
	b _020A5CA4
_020A5AF0:
	b _020A5D4C
_020A5AF4:
	b _020A5C74
_020A5AF8:
	b _020A5CD4
_020A5AFC:
	mov r0, #0x3
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A5DAC ; =0x000008F5
	mov r2, r1
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5B24:
	mov r0, #0x3
	bl FUN_020A6C38
_020A5B2C: ; 0x020A5B2C
	mov r0, #0x0
	ldr r3, _020A5DB0 ; =0x000008FB
	mov r1, r0
	mov r2, r0
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5B4C:
	add r1, r3, #0x2200
	ldrh r4, [r1, #0xf8]
	strh r0, [r1, #0xf8]
	cmp r4, #0x12
	bne _020A5C44
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2100
	ldrh r3, [r1, #0x70]
	and r12, r3, #0x24
	cmp r12, #0x24
	beq _020A5C44
	orr r3, r3, #0x24
	strh r3, [r1, #0x70]
	ldr r2, [r2, #0x0]
	add r1, r2, #0x2000
	ldr r3, [r1, #0x264]
	and r1, r3, #0xc0000
	cmp r1, #0xc0000
	moveq r0, #0x1
	mov r0, r0, lsl #0x10
	mov r12, r0, lsr #0x10
	and r1, r3, #0x30000
	cmp r1, #0x30000
	movne r3, #0x1
	add r1, r2, #0x2140
	ldr r0, _020A5DB4 ; =FUN_020A6144
	moveq r3, #0x0
	mov r2, #0x0
	str r12, [sp, #0x0]
	bl WM_StartConnectEx
	cmp r0, #0x2
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A5C14
	cmp r0, #0x8
	bne _020A5C14
	mov r0, #0xc
	bl FUN_020A6C38
	ldr r0, _020A5DA8 ; =0x021CA86C
	ldr r3, _020A5DB8 ; =0x0000091C
	ldr r0, [r0, #0x0]
	mov r2, r4
	add r1, r0, #0x2140
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5C14:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A5DA8 ; =0x021CA86C
	ldr r3, _020A5DBC ; =0x00000925
	ldr r0, [r0, #0x0]
	mov r2, r4
	add r1, r0, #0x2140
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5C44:
	mov r0, #0x3
	bl FUN_020A6C38
	ldr r0, _020A5DA8 ; =0x021CA86C
	ldr r3, _020A5DC0 ; =0x0000092D
	ldr r0, [r0, #0x0]
	mov r2, r4
	add r1, r0, #0x2140
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5C74:
	mov r0, #0x3
	bl FUN_020A6C38
	ldr r0, _020A5DA8 ; =0x021CA86C
	ldr r3, _020A5DC4 ; =0x00000935
	ldr r1, [r0, #0x0]
	mov r0, #0x0
	add r1, r1, #0x2140
	mov r2, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5CA4:
	mov r0, #0x3
	bl FUN_020A6C38
	ldr r1, _020A5DA8 ; =0x021CA86C
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r3, _020A5DC8 ; =0x0000093C
	mov r2, r0
	add r1, r1, #0x2140
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5CD4:
	ldr r0, _020A5DCC ; =FUN_020A6768
	bl WM_PowerOff
	cmp r0, #0x2
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A5D24
	cmp r0, #0x8
	bne _020A5D24
	mov r0, #0xc
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A5DD0 ; =0x0000094A
	mov r2, r1
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5D24:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A5DD4 ; =0x00000953
	mov r2, r1
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5D4C:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A5DA8 ; =0x021CA86C
	ldr r3, _020A5DD8 ; =0x00000959
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2000
	ldr r2, [r1, #0x260]
	mov r1, #0x0
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5D80:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	mov r2, r1
	mov r0, #0x7
	mov r3, #0x960
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A5DA8: .word 0x021CA86C
_020A5DAC: .word 0x000008F5
_020A5DB0: .word 0x000008FB
_020A5DB4: .word FUN_020A6144
_020A5DB8: .word 0x0000091C
_020A5DBC: .word 0x00000925
_020A5DC0: .word 0x0000092D
_020A5DC4: .word 0x00000935
_020A5DC8: .word 0x0000093C
_020A5DCC: .word FUN_020A6768
_020A5DD0: .word 0x0000094A
_020A5DD4: .word 0x00000953
_020A5DD8: .word 0x00000959

	arm_func_start FUN_020A5DDC
FUN_020A5DDC: ; 0x020A5DDC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r0, [r0, #0x2]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A5EF4
_020A5DF4:
	b _020A5E08
_020A5DF8:
	b _020A5EDC
_020A5DFC:
	b _020A5EF4
_020A5E00:
	b _020A5EDC
_020A5E04:
	b _020A5EF4
_020A5E08:
	ldr r0, _020A5F24 ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A5E38
	mov r0, #0xa
	bl FUN_020A6C38
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5E38:
	ldr r0, _020A5F28 ; =FUN_020A6058
	mov r1, #0x0
	bl WM_Disconnect
	cmp r0, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A5E94
	cmp r0, #0x8
	bne _020A5EAC
	mov r0, #0xc
	bl FUN_020A6C38
	ldr r0, _020A5F24 ; =0x021CA86C
	ldr r3, _020A5F2C ; =0x000008B4
	ldr r1, [r0, #0x0]
	mov r0, #0x1
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5E94:
	mov r0, #0xa
	bl FUN_020A6C38
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5EAC:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r1, _020A5F24 ; =0x021CA86C
	mov r0, #0x7
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	add r1, r1, #0x2140
	mov r3, #0x8c0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5EDC:
	mov r0, #0xa
	bl FUN_020A6C38
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5EF4:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A5F24 ; =0x021CA86C
	ldr r3, _020A5F30 ; =0x000008D3
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A5F24: .word 0x021CA86C
_020A5F28: .word FUN_020A6058
_020A5F2C: .word 0x000008B4
_020A5F30: .word 0x000008D3

	arm_func_start FUN_020A5F34
FUN_020A5F34: ; 0x020A5F34
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _020A5F50
	cmp r0, #0x4
	b _020A601C
_020A5F50:
	ldrh r0, [r4, #0x4]
	cmp r0, #0xe
	beq _020A5F68
	cmp r0, #0xf
	beq _020A5FC0
	b _020A5FF0
_020A5F68:
	ldr r0, _020A6048 ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A5F94
	mov r0, #0x8
	bl FUN_020A6C38
	bl FUN_020A6B28
	ldmia sp!, {r4,lr}
	bx lr
_020A5F94:
	mov r0, #0x9
	bl FUN_020A6C38
	ldr r1, _020A6048 ; =0x021CA86C
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r3, _020A604C ; =0x00000872
	mov r2, r0
	add r1, r1, #0x2140
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
_020A5FC0:
	ldr r0, [r4, #0x8]
	ldrh r0, [r0, #0xe]
	mov r0, r0, asr #0x8
	and r0, r0, #0xff
	bl FUN_020A89D0
	ldr r0, [r4, #0x8]
	mov r1, #0x620
	bl DC_InvalidateRange
	ldr r0, [r4, #0x8]
	bl FUN_020A8934
	ldmia sp!, {r4,lr}
	bx lr
_020A5FF0:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A6048 ; =0x021CA86C
	ldrh r2, [r4, #0x4]
	ldr r0, [r0, #0x0]
	ldr r3, _020A6050 ; =0x00000881
	add r1, r0, #0x2140
	mov r0, #0x7
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
_020A601C:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A6048 ; =0x021CA86C
	ldr r3, _020A6054 ; =0x0000088C
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A6048: .word 0x021CA86C
_020A604C: .word 0x00000872
_020A6050: .word 0x00000881
_020A6054: .word 0x0000088C

	arm_func_start FUN_020A6058
FUN_020A6058: ; 0x020A6058
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r0, [r0, #0x2]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6108
_020A6070:
	b _020A6084
_020A6074:
	b _020A60F0
_020A6078:
	b _020A6108
_020A607C:
	b _020A60F0
_020A6080:
	b _020A6108
_020A6084:
	ldr r0, _020A6138 ; =0x021CA86C
	ldr r1, [r0, #0x0]
	add r0, r1, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A60B4
	mov r0, #0xa
	bl FUN_020A6C38
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A60B4:
	add r1, r1, #0x2200
	mov r2, #0x0
	mov r0, #0x3
	strh r2, [r1, #0x82]
	bl FUN_020A6C38
	ldr r1, _020A6138 ; =0x021CA86C
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r3, _020A613C ; =0x0000083D
	mov r2, r0
	add r1, r1, #0x2140
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A60F0:
	mov r0, #0xa
	bl FUN_020A6C38
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6108:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A6138 ; =0x021CA86C
	ldr r3, _020A6140 ; =0x0000084F
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6138: .word 0x021CA86C
_020A613C: .word 0x0000083D
_020A6140: .word 0x0000084F

	arm_func_start FUN_020A6144
FUN_020A6144: ; 0x020A6144
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrh r0, [r4, #0x2]
	cmp r0, #0xc
	addls pc, pc, r0, lsl #0x2
	b _020A638C
_020A615C:
	b _020A6190
_020A6160:
	b _020A6364
_020A6164:
	b _020A638C
_020A6168:
	b _020A638C
_020A616C:
	b _020A638C
_020A6170:
	b _020A638C
_020A6174:
	b _020A6378
_020A6178:
	b _020A638C
_020A617C:
	b _020A638C
_020A6180:
	b _020A638C
_020A6184:
	b _020A638C
_020A6188:
	b _020A6378
_020A618C:
	b _020A6378
_020A6190:
	ldrh r0, [r4, #0x8]
	cmp r0, #0x9
	bgt _020A61D0
	cmp r0, #0x0
	addge pc, pc, r0, lsl #0x2
	b _020A6338
_020A61A8: ; 0x020A61A8
	b _020A6338
_020A61AC: ; 0x020A61AC
	b _020A6338
_020A61B0: ; 0x020A61B0
	b _020A6338
_020A61B4: ; 0x020A61B4
	b _020A6338
_020A61B8: ; 0x020A61B8
	b _020A6338
_020A61BC: ; 0x020A61BC
	b _020A6338
_020A61C0: ; 0x020A61C0
	b _020A63B0
_020A61C4: ; 0x020A61C4
	b _020A6258
_020A61C8: ; 0x020A61C8
	b _020A61E0
_020A61CC: ; 0x020A61CC
	b _020A61E0
_020A61D0:
	cmp r0, #0x1a
	ldmeqia sp!, {r4,lr}
	bxeq lr
	b _020A6338
_020A61E0:
	ldr r1, _020A63B8 ; =0x021CA86C
	ldr r2, [r1, #0x0]
	add r0, r2, #0x2000
	ldr r0, [r0, #0x260]
	sub r0, r0, #0x8
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A63B0
_020A6200:
	b _020A6220
_020A6204:
	b _020A6230
_020A6208:
	b _020A6214
_020A620C:
	b _020A63B0
_020A6210:
	b _020A624C
_020A6214:
	add r0, r2, #0x2200
	mov r1, #0x0
	strh r1, [r0, #0x82]
_020A6220:
	mov r0, #0xc
	bl FUN_020A6C38
	ldmia sp!, {r4,lr}
	bx lr
_020A6230:
	add r0, r2, #0x2200
	mov r2, #0x0
	strh r2, [r0, #0x82]
	ldr r0, [r1, #0x0]
	mov r1, #0x6
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
_020A624C:
	bl FUN_020A6B28
	ldmia sp!, {r4,lr}
	bx lr
_020A6258:
	ldr r1, _020A63B8 ; =0x021CA86C
	ldr r3, [r1, #0x0]
	add r0, r3, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A6284
	mov r0, #0x8
	bl FUN_020A6C38
	bl FUN_020A6B28
	ldmia sp!, {r4,lr}
	bx lr
_020A6284:
	ldrh r2, [r4, #0xa]
	cmp r2, #0x1
	blo _020A632C
	ldr r0, _020A63BC ; =0x000007D7
	cmp r2, r0
	bhi _020A632C
	add r0, r3, #0x2200
	strh r2, [r0, #0x82]
	ldr r1, [r1, #0x0]
	ldr r0, _020A63C0 ; =FUN_020A5F34
	add r1, r1, #0x1500
	mov r2, #0x620
	bl WM_StartDCF
	cmp r0, #0x2
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A6300
	cmp r0, #0x8
	bne _020A6300
	mov r0, #0xc
	bl FUN_020A6C38
	ldr r0, _020A63B8 ; =0x021CA86C
	ldr r3, _020A63C4 ; =0x000007ED
	ldr r1, [r0, #0x0]
	mov r0, #0x1
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
_020A6300:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A63B8 ; =0x021CA86C
	ldr r3, _020A63C8 ; =0x000007F6
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
_020A632C:
	bl FUN_020A6B28
	ldmia sp!, {r4,lr}
	bx lr
_020A6338:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A63B8 ; =0x021CA86C
	ldrh r2, [r4, #0x8]
	ldr r0, [r0, #0x0]
	ldr r3, _020A63CC ; =0x00000804
	add r1, r0, #0x2140
	mov r0, #0x7
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
_020A6364:
	ldr r0, _020A63B8 ; =0x021CA86C
	ldrh r1, [r4, #0xe]
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0xf8]
_020A6378:
	mov r0, #0x8
	bl FUN_020A6C38
	bl FUN_020A6B28
	ldmia sp!, {r4,lr}
	bx lr
_020A638C:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A63B8 ; =0x021CA86C
	ldr r3, _020A63D0 ; =0x0000081B
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
_020A63B0:
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A63B8: .word 0x021CA86C
_020A63BC: .word 0x000007D7
_020A63C0: .word FUN_020A5F34
_020A63C4: .word 0x000007ED
_020A63C8: .word 0x000007F6
_020A63CC: .word 0x00000804
_020A63D0: .word 0x0000081B

	arm_func_start FUN_020A63D4
FUN_020A63D4: ; 0x020A63D4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r0, [r0, #0x2]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6438
_020A63EC:
	b _020A6400
_020A63F0:
	b _020A6428
_020A63F4:
	b _020A6438
_020A63F8:
	b _020A6438
_020A63FC:
	b _020A6438
_020A6400:
	mov r0, #0x3
	bl FUN_020A6C38
_020A6408: ; 0x020A6408
	mov r0, #0x0
	ldr r3, _020A6460 ; =0x00000783
	mov r1, r0
	mov r2, r0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6428:
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6438:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A6464 ; =0x00000793
	mov r2, r1
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6460: .word 0x00000783
_020A6464: .word 0x00000793

	arm_func_start FUN_020A6468
FUN_020A6468: ; 0x020A6468
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r5, r0
	ldrh r0, [r5, #0x2]
	mov r4, #0x14
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6714
_020A6488:
	b _020A649C
_020A648C:
	b _020A6704
_020A6490:
	b _020A6714
_020A6494:
	b _020A6714
_020A6498:
	b _020A6714
_020A649C:
	ldr r0, _020A673C ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x5
	bne _020A64D0
	mov r0, #0x6
	bl FUN_020A6C38
_020A64BC: ; 0x020A64BC
	mov r0, #0x0
	ldr r3, _020A6740 ; =0x00000704
	mov r1, r0
	mov r2, r0
	bl FUN_020A6D3C
_020A64D0:
	ldr r1, _020A673C ; =0x021CA86C
	ldr r2, [r1, #0x0]
	add r0, r2, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x6
	beq _020A64FC
	cmp r0, #0x7
	beq _020A6674
	cmp r0, #0xd
	beq _020A6684
	b _020A6694
_020A64FC:
	add r0, r2, #0x2200
	mov r2, #0x7
	strh r2, [r0, #0x80]
	ldrh r0, [r5, #0x8]
	cmp r0, #0x5
	bne _020A6588
	ldr r0, [r1, #0x0]
	add r1, r0, #0x2200
	add r0, r0, #0x2000
	ldrh r1, [r1, #0x8c]
	ldr r0, [r0, #0x288]
	bl DC_InvalidateRange
	ldrh r0, [r5, #0xe]
	mov r4, #0x0
	cmp r0, #0x0
	ble _020A6588
	ldr r8, _020A6744 ; =0x0000071A
	mov r6, r4
	mov r7, #0x7
_020A6548:
	add r0, r5, r4, lsl #0x1
	add r2, r5, r4, lsl #0x2
	ldrh r1, [r0, #0x50]
	ldr r0, [r2, #0x10]
	bl FUN_020A8298
	str r8, [sp, #0x0]
	add r0, r5, r4, lsl #0x2
	ldr r2, [r0, #0x10]
	mov r0, r7
	mov r1, r6
	mov r3, r5
	bl FUN_020A6CE0
	ldrh r0, [r5, #0xe]
	add r4, r4, #0x1
	cmp r4, r0
	blt _020A6548
_020A6588:
	ldr r0, _020A673C ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r1, [r0, #0x264]
	and r0, r1, #0xc00000
	cmp r0, #0xc00000
	bne _020A65F4
	ldr r0, _020A6748 ; =0x00003FFE
	and r0, r1, r0
	bl FUN_020A5A4C
	movs r1, r0
	beq _020A65F4
	ldr r0, _020A673C ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r6, [r0, #0x284]
	mov r0, r6
	bl _u32_div_f
_020A65D0: ; 0x020A65D0
	cmp r1, #0x0
	bne _020A65F4
	ldr r4, _020A674C ; =0x00000728
	mov r1, #0x0
	mov r2, r6
	mov r3, r1
	mov r0, #0x8
	str r4, [sp, #0x0]
	bl FUN_020A6CE0
_020A65F4:
	ldrh r0, [r5, #0xa]
	bl FUN_020A5A70
	rsb r0, r0, #0x20
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl FUN_020A6D8C
	ldr r1, _020A673C ; =0x021CA86C
	mov r2, #0x1
	mov r2, r2, lsl r0
	ldr r0, [r1, #0x0]
	mov r2, r2, asr #0x1
	add r0, r0, #0x2200
	strh r2, [r0, #0x8e]
	ldr r0, [r1, #0x0]
	add r1, r0, #0x2200
	add r0, r0, #0x2000
	ldrh r1, [r1, #0x8c]
	ldr r0, [r0, #0x288]
	bl DC_InvalidateRange
	ldr r3, _020A673C ; =0x021CA86C
	ldr r2, _020A6750 ; =0x00002288
	ldr r1, [r3, #0x0]
	ldr r0, _020A6754 ; =FUN_020A6468
	add r1, r1, #0x2000
	ldr r4, [r1, #0x284]
	add r4, r4, #0x1
	str r4, [r1, #0x284]
	ldr r1, [r3, #0x0]
	add r1, r1, r2
	bl WM_StartScanEx
	mov r4, r0
	b _020A6694
_020A6674:
	ldr r0, _020A6758 ; =FUN_020A63D4
	bl WM_EndScan
	mov r4, r0
	b _020A6694
_020A6684:
	bl FUN_020A6B28
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A6694:
	cmp r4, #0x2
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	cmp r4, #0x3
	beq _020A66DC
	cmp r4, #0x8
	bne _020A66DC
	mov r0, #0xc
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A675C ; =0x00000753
	mov r2, r1
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A66DC:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A6760 ; =0x0000075C
	mov r2, r1
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A6704:
	bl FUN_020A6B28
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A6714:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A6764 ; =0x0000076D
	mov r2, r1
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A673C: .word 0x021CA86C
_020A6740: .word 0x00000704
_020A6744: .word 0x0000071A
_020A6748: .word 0x00003FFE
_020A674C: .word 0x00000728
_020A6750: .word 0x00002288
_020A6754: .word FUN_020A6468
_020A6758: .word FUN_020A63D4
_020A675C: .word 0x00000753
_020A6760: .word 0x0000075C
_020A6764: .word 0x0000076D

	arm_func_start FUN_020A6768
FUN_020A6768: ; 0x020A6768
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r1, [r0, #0x2]
	mov r2, #0x14
	cmp r1, #0x4
	addls pc, pc, r1, lsl #0x2
	b _020A6A0C
_020A6784:
	b _020A6798
_020A6788:
	b _020A69CC
_020A678C:
	b _020A6A0C
_020A6790:
	b _020A6A0C
_020A6794:
	b _020A6A0C
_020A6798:
	ldrh r0, [r0, #0x0]
	cmp r0, #0x19
	bgt _020A67D4
	cmp r0, #0x19
	bge _020A68B4
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020A692C
_020A67B8:
	b _020A692C
_020A67BC:
	b _020A692C
_020A67C0:
	b _020A692C
_020A67C4:
	b _020A67F4
_020A67C8:
	b _020A6804
_020A67CC:
	b _020A6868
_020A67D0:
	b _020A6890
_020A67D4:
	cmp r0, #0x1d
	bgt _020A67E8
	cmp r0, #0x1d
	beq _020A68A0
	b _020A692C
_020A67E8:
	cmp r0, #0x27
	beq _020A68DC
	b _020A692C
_020A67F4:
	ldr r0, _020A6A4C ; =FUN_020A6768
	bl WM_PowerOn
	mov r2, r0
	b _020A692C
_020A6804:
	bl WM_Finish
_020A6808: ; 0x020A6808
	cmp r0, #0x0
	beq _020A6818
	cmp r0, #0x4
	b _020A6840
_020A6818:
	mov r0, #0x1
	bl FUN_020A6C38
_020A6820: ; 0x020A6820
	mov r0, #0x0
	ldr r3, _020A6A50 ; =0x00000663
	mov r1, r0
	mov r2, r0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6840:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A6A54 ; =0x0000066C
	mov r2, r1
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6868:
	mov r0, #0x3
	bl FUN_020A6C38
_020A6870: ; 0x020A6870
	mov r0, #0x0
	ldr r3, _020A6A58 ; =0x00000673
	mov r1, r0
	mov r2, r0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6890:
	ldr r0, _020A6A4C ; =FUN_020A6768
	bl WM_Disable
	mov r2, r0
	b _020A692C
_020A68A0:
	ldr r0, _020A6A4C ; =FUN_020A6768
	mov r1, #0x0
	bl WM_SetBeaconIndication
	mov r2, r0
	b _020A692C
_020A68B4:
	ldr r1, _020A6A5C ; =0x021CA86C
	ldr r0, _020A6A4C ; =FUN_020A6768
	ldr r3, [r1, #0x0]
	add r2, r3, #0x2000
	ldrb r1, [r2, #0x250]
	ldrb r2, [r2, #0x251]
	add r3, r3, #0x2200
	bl WM_SetWEPKeyEx
	mov r2, r0
	b _020A692C
_020A68DC:
	ldr r0, _020A6A5C ; =0x021CA86C
	ldr r2, [r0, #0x0]
	add r0, r2, #0x2000
	ldr r1, [r0, #0x264]
	and r0, r1, #0xc0000
	cmp r0, #0xc0000
	moveq r0, #0x1
	movne r0, #0x0
	mov r0, r0, lsl #0x10
	mov r12, r0, lsr #0x10
	and r1, r1, #0x30000
	cmp r1, #0x30000
	movne r3, #0x1
	add r1, r2, #0x2140
	ldr r0, _020A6A60 ; =FUN_020A6144
	moveq r3, #0x0
	mov r2, #0x0
	str r12, [sp, #0x0]
	bl WM_StartConnectEx
	mov r2, r0
_020A692C:
	cmp r2, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	cmp r2, #0x3
	beq _020A698C
	cmp r2, #0x8
	bne _020A698C
	mov r0, #0xc
	bl FUN_020A6C38
	ldr r0, _020A6A5C ; =0x021CA86C
	ldr r3, _020A6A64 ; =0x000006AF
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A698C:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A6A5C ; =0x021CA86C
	ldr r3, _020A6A68 ; =0x000006B8
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A69CC:
	mov r0, #0xc
	bl FUN_020A6C38
	ldr r0, _020A6A5C ; =0x021CA86C
	ldr r3, _020A6A6C ; =0x000006DE
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6A0C:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A6A5C ; =0x021CA86C
	ldr r3, _020A6A70 ; =0x000006E8
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6A4C: .word FUN_020A6768
_020A6A50: .word 0x00000663
_020A6A54: .word 0x0000066C
_020A6A58: .word 0x00000673
_020A6A5C: .word 0x021CA86C
_020A6A60: .word FUN_020A6144
_020A6A64: .word 0x000006AF
_020A6A68: .word 0x000006B8
_020A6A6C: .word 0x000006DE
_020A6A70: .word 0x000006E8

	arm_func_start FUN_020A6A74
FUN_020A6A74: ; 0x020A6A74
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r1, [r0, #0x2]
	cmp r1, #0x8
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldrh r1, [r0, #0x4]
	cmp r1, #0x16
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldrh r0, [r0, #0x6]
	cmp r0, #0x25
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020A6B24 ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	sub r0, r0, #0x8
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6B18
_020A6AD8:
	b _020A6AEC
_020A6ADC:
	b _020A6B00
_020A6AE0:
	b _020A6B10
_020A6AE4:
	b _020A6B18
_020A6AE8:
	b _020A6B00
_020A6AEC:
	mov r0, #0xc
	bl FUN_020A6C38
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6B00:
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6B10:
	mov r0, #0xc
	bl FUN_020A6C38
_020A6B18:
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6B24: .word 0x021CA86C

	arm_func_start FUN_020A6B28
FUN_020A6B28: ; 0x020A6B28
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020A6B98 ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r1, r0, #0x2000
	ldrb r0, [r1, #0x26b]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020A6B9C ; =FUN_020A5A78
	mov r2, #0x1
	strb r2, [r1, #0x26b]
	bl WM_Reset
	cmp r0, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	mov r2, r1
	mov r0, #0x7
	mov r3, #0x610
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6B98: .word 0x021CA86C
_020A6B9C: .word FUN_020A5A78

	arm_func_start FUN_020A6BA0
FUN_020A6BA0: ; 0x020A6BA0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020A88A8
	bl FUN_020A6BBC
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A6BBC
FUN_020A6BBC: ; 0x020A6BBC
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	bl OS_DisableInterrupts
	ldr r2, _020A6C28 ; =0x021CA86C
	ldr r1, _020A6C2C ; =0x000022CC
	ldr r2, [r2, #0x0]
	mov r4, r0
	add r0, r2, r1
	bl OS_CancelAlarm
	ldr r0, _020A6C28 ; =0x021CA86C
	ldr r12, [r0, #0x0]
	add r0, r12, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x9
	bne _020A6C14
	ldr r0, _020A6C2C ; =0x000022CC
	ldr r1, _020A6C30 ; =0x022F5341
	mov r2, #0x0
	ldr r3, _020A6C34 ; =FUN_020A6BA0
	add r0, r12, r0
	str r2, [sp, #0x0]
	bl OS_SetAlarm
_020A6C14:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A6C28: .word 0x021CA86C
_020A6C2C: .word 0x000022CC
_020A6C30: .word 0x022F5341
_020A6C34: .word FUN_020A6BA0

	arm_func_start FUN_020A6C38
FUN_020A6C38:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020A6CD0 ; =0x021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	add r0, r1, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x9
	bne _020A6C78
	cmp r5, #0x9
	beq _020A6C78
	ldr r0, _020A6CD4 ; =0x000022CC
	add r0, r1, r0
	bl OS_CancelAlarm
_020A6C78:
	ldr r0, _020A6CD0 ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r1, [r0, #0x260]
	cmp r1, #0xb
	strne r5, [r0, #0x260]
	cmp r5, #0x9
	bne _020A6CBC
	mov r2, #0x0
	ldr r0, _020A6CD0 ; =0x021CA86C
	str r2, [sp, #0x0]
	ldr r5, [r0, #0x0]
	ldr r0, _020A6CD4 ; =0x000022CC
	ldr r1, _020A6CD8 ; =0x022F5341
	ldr r3, _020A6CDC ; =FUN_020A6BA0
	add r0, r5, r0
	bl OS_SetAlarm
_020A6CBC:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A6CD0: .word 0x021CA86C
_020A6CD4: .word 0x000022CC
_020A6CD8: .word 0x022F5341
_020A6CDC: .word FUN_020A6BA0

	arm_func_start FUN_020A6CE0
FUN_020A6CE0: ; 0x020A6CE0
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	ldr ip, _020A6D38 ; =0x021CA86C
	ldr r12, [r12, #0x0]
	add r12, r12, #0x2000
	ldr lr, [r12, #0x27c]
	cmp lr, #0x0
	addeq sp, sp, #0x14
	ldmeqia sp!, {lr}
	bxeq lr
	ldr lr, [sp, #0x18]
	strh r0, [sp, #0x0]
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	str lr, [sp, #0xc]
	strh r1, [sp, #0x2]
	ldr r1, [r12, #0x27c]
	add r0, sp, #0x0
	blx r1
	add sp, sp, #0x14
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6D38: .word 0x021CA86C

	arm_func_start FUN_020A6D3C
FUN_020A6D3C: ; 0x020A6D3C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr ip, _020A6D88 ; =0x021CA86C
	mov r5, r0
	ldr r0, [r12, #0x0]
	mov r4, r1
	add r1, r0, #0x2200
	ldrsh r0, [r1, #0x80]
	mov r12, #0x0
	mov lr, r2
	strh r12, [r1, #0x80]
	str r3, [sp, #0x0]
	mov r1, r5
	mov r2, r4
	mov r3, lr
	bl FUN_020A6CE0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A6D88: .word 0x021CA86C

	arm_func_start FUN_020A6D8C
FUN_020A6D8C: ; 0x020A6D8C
	stmdb sp!, {r4-r6,lr}
	ldr r1, _020A6E24 ; =0x021CA86C
	mov r2, r0
	ldr r1, [r1, #0x0]
	mov r3, #0x0
	add r1, r1, #0x2000
	ldr r1, [r1, #0x264]
	mov r6, #0x1
	ldr r5, _020A6E28 ; =0x4EC4EC4F
	ldr r4, _020A6E2C ; =0x0000000D
_020A6DB4:
	smull r12, lr, r5, r2
	mov lr, lr, asr #0x2
	mov r12, r2, lsr #0x1f
	add lr, r12, lr
	smull r12, lr, r4, lr
	sub lr, r2, r12
	add r12, lr, #0x1
	mov r12, r6, lsl r12
	ands r12, r1, r12
	bne _020A6DEC
	add r3, r3, #0x1
	cmp r3, #0xd
	add r2, r2, #0x1
	blt _020A6DB4
_020A6DEC:
	ldr r1, _020A6E28 ; =0x4EC4EC4F
	add r3, r0, r3
	smull r0, r4, r1, r3
	mov r4, r4, asr #0x2
	mov r0, r3, lsr #0x1f
	ldr r2, _020A6E2C ; =0x0000000D
	add r4, r0, r4
	smull r0, r1, r2, r4
	sub r4, r3, r0
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A6E24: .word 0x021CA86C
_020A6E28: .word 0x4EC4EC4F
_020A6E2C: .word 0x0000000D

	arm_func_start FUN_020A6E30
FUN_020A6E30: ; 0x020A6E30
	ldr r0, _020A6E48 ; =0x021CA86C
	ldr r1, _020A6E4C ; =0x00AAA082
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r1, [r0, #0x264]
	bx lr
	.balign 4
_020A6E48: .word 0x021CA86C
_020A6E4C: .word 0x00AAA082

	arm_func_start FUN_020A6E50
FUN_020A6E50: ; 0x020A6E50
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r0, r2
	mov r4, r1
	bl FUN_020A7148
	ldr r2, _020A6FF4 ; =0x021CA86C
	mov r3, #0x400
	ldr r1, [r2, #0x0]
	mov r0, #0x0
	add r12, r1, #0x1500
	add r1, r1, #0x2000
	str r12, [r1, #0x288]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r3, [r1, #0x8c]
	bl FUN_020A6D8C
	ldr r1, _020A6FF4 ; =0x021CA86C
	mov r2, #0x1
	mov r2, r2, lsl r0
	ldr r0, [r1, #0x0]
	mov r2, r2, asr #0x1
	add r0, r0, #0x2200
	strh r2, [r0, #0x8e]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2200
	ldrh r0, [r0, #0x68]
	cmp r0, #0x0
	bne _020A6EC8
	bl WM_GetDispersionScanPeriod
_020A6EC8:
	ldr r2, _020A6FF4 ; =0x021CA86C
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x90]
	ldr r1, [r2, #0x0]
	add r0, r1, #0x2000
	ldr r0, [r0, #0x264]
	and r0, r0, #0x300000
	cmp r0, #0x300000
	movne r2, #0x1
	moveq r2, #0x0
	add r0, r1, #0x2200
	strh r2, [r0, #0x98]
	cmp r5, #0x0
	bne _020A6F24
	ldr r0, _020A6FF4 ; =0x021CA86C
	ldr r1, _020A6FF8 ; =0x00002292
	ldr r2, [r0, #0x0]
	ldr r0, _020A6FFC ; =0x020FF590
	add r1, r2, r1
	mov r2, #0x6
	bl MI_CpuCopy8
	b _020A6F40
_020A6F24:
	ldr r0, _020A6FF4 ; =0x021CA86C
	ldr r1, _020A6FF8 ; =0x00002292
	ldr r2, [r0, #0x0]
	mov r0, r5
	add r1, r2, r1
	mov r2, #0x6
	bl MI_CpuCopy8
_020A6F40:
	cmp r4, #0x0
	beq _020A6F54
	ldr r0, _020A7000 ; =0x020FF598
	cmp r4, r0
	bne _020A6F88
_020A6F54:
	ldr r0, _020A6FF4 ; =0x021CA86C
	ldr r1, _020A7004 ; =0x0000229C
	ldr r2, [r0, #0x0]
	ldr r0, _020A7000 ; =0x020FF598
	add r1, r2, r1
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, _020A6FF4 ; =0x021CA86C
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x9a]
	b _020A6FD4
_020A6F88:
	ldr r0, _020A6FF4 ; =0x021CA86C
	ldr r1, _020A7004 ; =0x0000229C
	ldr r2, [r0, #0x0]
	mov r0, r4
	add r1, r2, r1
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r1, #0x0
_020A6FA8:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020A6FC4
	add r1, r1, #0x1
	cmp r1, #0x20
	add r4, r4, #0x1
	blt _020A6FA8
_020A6FC4:
	ldr r0, _020A6FF4 ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x9a]
_020A6FD4:
	ldr r0, _020A6FF4 ; =0x021CA86C
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r1, [r0, #0x284]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A6FF4: .word 0x021CA86C
_020A6FF8: .word 0x00002292
_020A6FFC: .word 0x020FF590
_020A7000: .word 0x020FF598
_020A7004: .word 0x0000229C

	arm_func_start FUN_020A7008
FUN_020A7008: ; 0x020A7008
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r0
	mov r4, r1
	bne _020A705C
	ldr r1, _020A7134 ; =0x021CA86C
	mov r3, #0x3
	ldr r0, [r1, #0x0]
	mov r2, #0x0
	add r0, r0, #0x2000
	str r3, [r0, #0x26c]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x270]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x274]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x278]
	b _020A7118
_020A705C:
	ldr r1, _020A7134 ; =0x021CA86C
	ldr r2, [r5, #0x0]
	ldr r0, [r1, #0x0]
	and r2, r2, #0x3
	add r0, r0, #0x2000
	str r2, [r0, #0x26c]
	ldr r3, [r5, #0x4]
	ldr r0, [r5, #0x8]
	and r2, r3, #0x3
	rsb r2, r2, #0x4
	and r2, r2, #0x3
	add r2, r2, #0xc
	cmp r2, r0
	bls _020A70B4
	ldr r0, [r1, #0x0]
	mov r2, #0x0
	add r0, r0, #0x2000
	str r2, [r0, #0x270]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x274]
	b _020A7104
_020A70B4:
	ldr r0, [r1, #0x0]
	add r2, r3, #0x3
	bic r2, r2, #0x3
	add r0, r0, #0x2000
	str r2, [r0, #0x270]
	ldr r2, [r5, #0x4]
	ldr r0, [r1, #0x0]
	and r2, r2, #0x3
	rsb r2, r2, #0x4
	ldr r3, [r5, #0x8]
	and r2, r2, #0x3
	sub r2, r3, r2
	add r0, r0, #0x2000
	str r2, [r0, #0x274]
	ldr r0, [r1, #0x0]
	mov r1, #0x0
	add r2, r0, #0x2000
	ldr r0, [r2, #0x270]
	ldr r2, [r2, #0x274]
	bl MI_CpuFill8
_020A7104:
	ldr r0, _020A7134 ; =0x021CA86C
	ldr r1, [r5, #0xc]
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r1, [r0, #0x278]
_020A7118:
	ldr r0, _020A7134 ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r4, [r0, #0x27c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A7134: .word 0x021CA86C

	arm_func_start FUN_020A7138
FUN_020A7138:
	ldr r0, _020A7144 ; =0x021CA86C
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020A7144: .word 0x021CA86C

	arm_func_start FUN_020A7148
FUN_020A7148: ; 0x020A7148
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020A71EC ; =0x021CA86C
	mov r2, #0x0
	ldr r1, [r1, #0x0]
	add r3, r1, #0x2000
	cmp r1, #0x0
	ldr r4, [r3, #0x264]
	bne _020A7188
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7188:
	ands r3, r5, #0x8000
	beq _020A71A4
	ldr r3, _020A71F0 ; =0x00003FFE
	orr r2, r2, r3
	ands r3, r5, r3
	ldreq r3, _020A71F4 ; =0x0000A082
	orreq r5, r5, r3
_020A71A4:
	ands r3, r5, #0x20000
	orrne r2, r2, #0x10000
	ands r3, r5, #0x80000
	orrne r2, r2, #0x40000
	ands r3, r5, #0x200000
	orrne r2, r2, #0x100000
	ands r3, r5, #0x800000
	orrne r2, r2, #0x400000
	mvn r2, r2
	and r2, r4, r2
	orr r2, r5, r2
	add r1, r1, #0x2000
	str r2, [r1, #0x264]
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A71EC: .word 0x021CA86C
_020A71F0: .word 0x00003FFE
_020A71F4: .word 0x0000A082

	arm_func_start FUN_020A71F8
FUN_020A71F8: ; 0x020A71F8
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A7228 ; =0x021CA86C
	mov r4, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	addne r1, r1, #0x2000
	ldrne r4, [r1, #0x260]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A7228: .word 0x021CA86C

	arm_func_start FUN_020A722C
FUN_020A722C: ; 0x020A722C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r1, _020A747C ; =0x021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7260
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7260:
	add r1, r1, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0xd
	addls pc, pc, r2, lsl #0x2
	b _020A7308
_020A7274:
	b _020A7308
_020A7278:
	b _020A72C0
_020A727C:
	b _020A7308
_020A7280:
	b _020A7320
_020A7284:
	b _020A7308
_020A7288:
	b _020A7308
_020A728C:
	b _020A72D4
_020A7290:
	b _020A7308
_020A7294:
	b _020A7308
_020A7298:
	b _020A7320
_020A729C:
	b _020A7308
_020A72A0:
	b _020A7308
_020A72A4:
	b _020A7320
_020A72A8:
	b _020A72AC
_020A72AC:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A72C0:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A72D4:
	mov r0, #0xd
	bl FUN_020A6C38
	ldr r1, _020A747C ; =0x021CA86C
	mov r0, r4
	ldr r1, [r1, #0x0]
	mov r2, #0x9
	add r1, r1, #0x2200
	strh r2, [r1, #0x80]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x3
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7308:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7320:
	ldrb r0, [r1, #0x26b]
	cmp r0, #0x1
	bne _020A734C
	mov r0, #0xd
	bl FUN_020A6C38
	ldr r0, _020A747C ; =0x021CA86C
	mov r1, #0x9
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7464
_020A734C:
	bl WMi_GetStatusAddress
	mov r5, r0
	mov r1, #0x2
	bl DC_InvalidateRange
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _020A737C
	cmp r0, #0x1
	beq _020A73BC
	cmp r0, #0x2
	beq _020A73C8
	b _020A73D4
_020A737C:
	bl WM_Finish
_020A7380: ; 0x020A7380
	cmp r0, #0x0
	bne _020A73F0
	mov r0, #0x1
	bl FUN_020A6C38
	ldr r1, _020A747C ; =0x021CA86C
	mov r0, r4
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	add r1, r1, #0x2200
	strh r2, [r1, #0x80]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A73BC:
	ldr r0, _020A7480 ; =FUN_020A6768
	bl WM_Disable
	b _020A73F0
_020A73C8:
	ldr r0, _020A7480 ; =FUN_020A6768
	bl WM_PowerOff
	b _020A73F0
_020A73D4:
	ldr r1, _020A747C ; =0x021CA86C
	ldr r0, _020A7484 ; =FUN_020A5A78
	ldr r1, [r1, #0x0]
	mov r2, #0x1
	add r1, r1, #0x2000
	strb r2, [r1, #0x26b]
	bl WM_Reset
_020A73F0:
	cmp r0, #0x2
	beq _020A740C
	cmp r0, #0x3
	beq _020A7444
	cmp r0, #0x8
	beq _020A742C
	b _020A7444
_020A740C:
	mov r0, #0xd
	bl FUN_020A6C38
	ldr r0, _020A747C ; =0x021CA86C
	mov r1, #0x9
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7464
_020A742C:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7444:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x7
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7464:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A747C: .word 0x021CA86C
_020A7480: .word FUN_020A6768
_020A7484: .word FUN_020A5A78

	arm_func_start FUN_020A7488
FUN_020A7488: ; 0x020A7488
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A75B8 ; =0x021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A74B4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A74B4:
	add r1, r1, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0x3
	beq _020A74E4
	cmp r2, #0x9
	beq _020A7504
	cmp r2, #0xa
	bne _020A74F4
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr
_020A74E4:
	bl OS_RestoreInterrupts
_020A74E8: ; 0x020A74E8
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020A74F4:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A7504:
	ldrb r0, [r1, #0x26b]
	cmp r0, #0x1
	bne _020A7530
	mov r0, #0xa
	bl FUN_020A6C38
	ldr r0, _020A75B8 ; =0x021CA86C
	mov r1, #0x6
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A75A4
_020A7530:
	ldr r0, _020A75BC ; =FUN_020A5DDC
	bl WM_EndDCF
	cmp r0, #0x2
	beq _020A7554
	cmp r0, #0x3
	beq _020A7588
	cmp r0, #0x8
	beq _020A7574
	b _020A7588
_020A7554:
	mov r0, #0xa
	bl FUN_020A6C38
	ldr r0, _020A75B8 ; =0x021CA86C
	mov r1, #0x6
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A75A4
_020A7574:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x4
	ldmia sp!, {r4,lr}
	bx lr
_020A7588:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4,lr}
	bx lr
_020A75A4:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A75B8: .word 0x021CA86C
_020A75BC: .word FUN_020A5DDC

	arm_func_start FUN_020A75C0
FUN_020A75C0: ; 0x020A75C0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl OS_DisableInterrupts
	ldr r2, _020A7814 ; =0x021CA86C
	mov r4, r0
	ldr r12, [r2, #0x0]
	cmp r12, #0x0
	bne _020A7600
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7600:
	add r1, r12, #0x2000
	ldr r3, [r1, #0x260]
	cmp r3, #0x3
	beq _020A7624
	cmp r3, #0x8
	beq _020A7734
	cmp r3, #0x9
	beq _020A7748
	b _020A775C
_020A7624:
	cmp r7, #0x0
	bne _020A7640
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7640:
	ldrh r3, [r7, #0x3c]
	cmp r3, #0x0
	beq _020A7660
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7660:
	cmp r6, #0x0
	beq _020A76E8
	ldrb r3, [r6, #0x0]
	cmp r3, #0x4
	bhs _020A7680
	ldrb r0, [r6, #0x1]
	cmp r0, #0x4
	blo _020A7698
_020A7680:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7698:
	strb r3, [r1, #0x250]
	ldr r0, [r2, #0x0]
	ldrb r1, [r6, #0x1]
	add r0, r0, #0x2000
	strb r1, [r0, #0x251]
	ldr r1, [r2, #0x0]
	add r0, r1, #0x2000
	ldrb r0, [r0, #0x250]
	cmp r0, #0x0
	bne _020A76D4
	add r0, r1, #0x2200
	mov r1, #0x0
	mov r2, #0x50
	bl MI_CpuFill8
	b _020A76F8
_020A76D4:
	add r0, r6, #0x2
	add r1, r1, #0x2200
	mov r2, #0x50
	bl MI_CpuCopy8
	b _020A76F8
_020A76E8:
	add r0, r12, #0x2200
	mov r1, #0x0
	mov r2, #0x52
	bl MI_CpuFill8
_020A76F8:
	ldr r1, _020A7814 ; =0x021CA86C
	mov r0, r7
	ldr r1, [r1, #0x0]
	mov r2, #0xc0
	add r1, r1, #0x2140
	bl MI_CpuCopy8
	ldr r1, _020A7814 ; =0x021CA86C
	mov r0, r5
	ldr r1, [r1, #0x0]
	add r1, r1, #0x2100
	ldrh r2, [r1, #0x6e]
	orr r2, r2, #0x3
	strh r2, [r1, #0x70]
	bl FUN_020A7148
	b _020A7770
_020A7734:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7748:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A775C:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7770:
	ldr r1, _020A7818 ; =0x0000FFFF
	ldr r0, _020A781C ; =FUN_020A6768
	mov r3, r1
	mov r2, #0x50
	str r1, [sp, #0x0]
	bl WM_SetLifeTime
	cmp r0, #0x2
	beq _020A77A4
	cmp r0, #0x3
	beq _020A77DC
	cmp r0, #0x8
	beq _020A77C4
	b _020A77DC
_020A77A4:
	mov r0, #0x8
	bl FUN_020A6C38
	ldr r0, _020A7814 ; =0x021CA86C
	mov r1, #0x5
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A77FC
_020A77C4:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A77DC:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x7
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A77FC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A7814: .word 0x021CA86C
_020A7818: .word 0x0000FFFF
_020A781C: .word FUN_020A6768

	arm_func_start FUN_020A7820
FUN_020A7820: ; 0x020A7820
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A78D4 ; =0x021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A784C
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A784C:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x3
	beq _020A78A0
	cmp r1, #0x6
	beq _020A7870
	cmp r1, #0x7
	beq _020A7890
	b _020A78B0
_020A7870:
	mov r0, #0x7
	bl FUN_020A6C38
	ldr r0, _020A78D4 ; =0x021CA86C
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A78C0
_020A7890:
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr
_020A78A0:
	bl OS_RestoreInterrupts
_020A78A4: ; 0x020A78A4
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020A78B0:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A78C0:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A78D4: .word 0x021CA86C

	arm_func_start FUN_020A78D8
FUN_020A78D8: ; 0x020A78D8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl OS_DisableInterrupts
	ldr r1, _020A7A84 ; =0x021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7918
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7918:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x3
	beq _020A79A0
	cmp r1, #0x5
	beq _020A793C
	cmp r1, #0x6
	beq _020A7964
	b _020A798C
_020A793C:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_020A6E50
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7964:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_020A6E50
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A798C:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A79A0:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_020A6E50
	ldr r0, _020A7A84 ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r1, r0, #0x2200
	add r0, r0, #0x2000
	ldrh r1, [r1, #0x8c]
	ldr r0, [r0, #0x288]
	bl DC_InvalidateRange
	ldr r3, _020A7A84 ; =0x021CA86C
	ldr r2, _020A7A88 ; =0x00002288
	ldr r1, [r3, #0x0]
	ldr r0, _020A7A8C ; =FUN_020A6468
	add r1, r1, #0x2000
	ldr r5, [r1, #0x284]
	add r5, r5, #0x1
	str r5, [r1, #0x284]
	ldr r1, [r3, #0x0]
	add r1, r1, r2
	bl WM_StartScanEx
	cmp r0, #0x2
	beq _020A7A14
	cmp r0, #0x3
	beq _020A7A4C
	cmp r0, #0x8
	beq _020A7A34
	b _020A7A4C
_020A7A14:
	mov r0, #0x5
	bl FUN_020A6C38
	ldr r0, _020A7A84 ; =0x021CA86C
	mov r1, #0x3
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7A6C
_020A7A34:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7A4C:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x7
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7A6C:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A7A84: .word 0x021CA86C
_020A7A88: .word 0x00002288
_020A7A8C: .word FUN_020A6468

	arm_func_start FUN_020A7A90
FUN_020A7A90: ; 0x020A7A90
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	beq _020A7AA8
	cmp r1, #0x0
	bne _020A7AB8
_020A7AA8:
	bl FUN_020A7820
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A7AB8:
	bl FUN_020A78D8
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A7AC8
FUN_020A7AC8: ; 0x020A7AC8
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A7BCC ; =0x021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7AF4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A7AF4:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x1
	beq _020A7B24
	cmp r1, #0x3
	beq _020A7B44
	cmp r1, #0x4
	bne _020A7B34
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr
_020A7B24:
	bl OS_RestoreInterrupts
_020A7B28: ; 0x020A7B28
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020A7B34:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A7B44:
	ldr r0, _020A7BD0 ; =FUN_020A6768
	bl WM_PowerOff
	cmp r0, #0x2
	beq _020A7B68
	cmp r0, #0x3
	beq _020A7B9C
	cmp r0, #0x8
	beq _020A7B88
	b _020A7B9C
_020A7B68:
	mov r0, #0x4
	bl FUN_020A6C38
	ldr r0, _020A7BCC ; =0x021CA86C
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7BB8
_020A7B88:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x4
	ldmia sp!, {r4,lr}
	bx lr
_020A7B9C:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4,lr}
	bx lr
_020A7BB8:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A7BCC: .word 0x021CA86C
_020A7BD0: .word FUN_020A6768

	arm_func_start FUN_020A7BD4
FUN_020A7BD4: ; 0x020A7BD4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	bl OS_DisableInterrupts
	ldr r1, _020A7E00 ; =0x021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7C08
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C08:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x1
	beq _020A7C2C
	cmp r1, #0x2
	beq _020A7C3C
	cmp r1, #0x3
	beq _020A7C4C
	b _020A7C5C
_020A7C2C:
	mov r0, r6
	mov r1, r5
	bl FUN_020A7008
	b _020A7C6C
_020A7C3C:
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C4C:
	bl OS_RestoreInterrupts
_020A7C50: ; 0x020A7C50
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C5C:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C6C:
	ldr r0, _020A7E00 ; =0x021CA86C
	ldr r0, [r0, #0x0]
	add r1, r0, #0x2000
	ldr r1, [r1, #0x26c]
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	bl WM_Init
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020A7CE0
_020A7C94:
	b _020A7CFC
_020A7C98:
	b _020A7CE0
_020A7C9C:
	b _020A7CE0
_020A7CA0:
	b _020A7CB0
_020A7CA4:
	b _020A7CCC
_020A7CA8:
	b _020A7CE0
_020A7CAC:
	b _020A7CE0
_020A7CB0:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7CCC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x5
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7CE0:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7CFC:
	bl WM_GetAllowedChannel
_020A7D00: ; 0x020A7D00
	cmp r0, #0x0
	bne _020A7D44
	bl WM_Finish
_020A7D0C: ; 0x020A7D0C
	cmp r0, #0x0
	beq _020A7D30
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7D30:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x5
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7D44:
	ldr r0, _020A7E04 ; =FUN_020A6A74
	bl WM_SetIndCallback
_020A7D4C: ; 0x020A7D4C
	cmp r0, #0x0
	beq _020A7D70
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7D70:
	ldr r0, _020A7E08 ; =FUN_020A6768
	bl WM_Enable
	cmp r0, #0x2
	beq _020A7D94
	cmp r0, #0x3
	beq _020A7DD0
	cmp r0, #0x8
	beq _020A7DB4
	b _020A7DD0
_020A7D94:
	mov r0, #0x2
	bl FUN_020A6C38
	ldr r0, _020A7E00 ; =0x021CA86C
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7DEC
_020A7DB4:
	mov r0, #0xc
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7DD0:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7DEC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A7E00: .word 0x021CA86C
_020A7E04: .word FUN_020A6A74
_020A7E08: .word FUN_020A6768

	arm_func_start FUN_020A7E0C
FUN_020A7E0C: ; 0x020A7E0C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r2, _020A7E7C ; =0x021CA86C
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	bne _020A7E3C
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {lr}
	bx lr
_020A7E3C:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x1
	beq _020A7E60
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {lr}
	bx lr
_020A7E60:
	mov r1, #0x0
	str r1, [r2, #0x0]
	bl OS_RestoreInterrupts
_020A7E6C: ; 0x020A7E6C
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A7E7C: .word 0x021CA86C

	arm_func_start FUN_020A7E80
FUN_020A7E80: ; 0x020A7E80
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	bl OS_DisableInterrupts
	ldr r2, _020A7FA8 ; =0x021CA86C
	mov r4, r0
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	beq _020A7EB4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7EB4:
	cmp r6, #0x0
	bne _020A7ECC
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7ECC:
	ands r1, r6, #0x1f
	beq _020A7EE4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7EE4:
	cmp r5, #0x2300
	bhs _020A7EFC
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7EFC:
	str r6, [r2, #0x0]
	add r0, r6, #0x2000
	mov r1, #0x1
	str r1, [r0, #0x260]
	ldr r1, [r2, #0x0]
	mov r0, #0x0
	add r1, r1, #0x2200
	strh r0, [r1, #0x80]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x68]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2000
	strb r0, [r1, #0x26a]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2000
	strb r0, [r1, #0x26b]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x82]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0xf8]
	bl FUN_020A6E30
	bl FUN_020A897C
	bl OS_IsTickAvailable
_020A7F64: ; 0x020A7F64
	cmp r0, #0x0
	bne _020A7F70
	bl OS_InitTick
_020A7F70:
	bl OS_IsAlarmAvailable
_020A7F74: ; 0x020A7F74
	cmp r0, #0x0
	bne _020A7F80
	bl OS_InitAlarm
_020A7F80:
	ldr r1, _020A7FA8 ; =0x021CA86C
	ldr r0, _020A7FAC ; =0x000022CC
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	bl OS_CreateAlarm
	mov r0, r4
	bl OS_RestoreInterrupts
_020A7F9C: ; 0x020A7F9C
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A7FA8: .word 0x021CA86C
_020A7FAC: .word 0x000022CC

	arm_func_start FUN_020A7FB0
FUN_020A7FB0: ; 0x020A7FB0
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020A7138
	add r1, r0, #0x2000
	cmp r4, #0x0
	ldr r0, [r1, #0x270]
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r1, #0x274]
	cmp r1, #0xc
	ldmlsia sp!, {r4,lr}
	bxls lr
	ldr r3, [r0, #0x4]
	cmp r3, #0x0
	beq _020A8040
_020A7FF8:
	cmp r3, r4
	bne _020A8034
	ldr r2, [r3, #0x8]
	cmp r2, #0x0
	ldrne r1, [r3, #0xc]
	strne r1, [r2, #0xc]
	ldreq r1, [r3, #0xc]
	streq r1, [r0, #0x4]
	ldr r2, [r3, #0xc]
	cmp r2, #0x0
	ldrne r1, [r3, #0x8]
	strne r1, [r2, #0x8]
	ldreq r1, [r3, #0x8]
	streq r1, [r0, #0x8]
	b _020A8040
_020A8034:
	ldr r3, [r3, #0xc]
	cmp r3, #0x0
	bne _020A7FF8
_020A8040:
	mov r1, #0x0
	str r1, [r4, #0xc]
	ldr r1, [r0, #0x8]
	str r1, [r4, #0x8]
	str r4, [r0, #0x8]
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	strne r4, [r1, #0xc]
	streq r4, [r0, #0x4]
	cmp r3, #0x0
	ldreq r1, [r0, #0x0]
	streq r1, [r4, #0x4]
	ldreq r1, [r0, #0x0]
	addeq r1, r1, #0x1
	streq r1, [r0, #0x0]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A8084
FUN_020A8084: ; 0x020A8084
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020A7138
	add r1, r0, #0x2000
	ldr r2, [r1, #0x270]
	mov r0, #0x0
	cmp r2, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r1, #0x274]
	cmp r1, #0xc
	ldmlsia sp!, {r4,lr}
	bxls lr
	ldr r0, [r2, #0x4]
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
_020A80C8:
	ldr r1, [r0, #0x4]
	cmp r1, r4
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, [r0, #0xc]
	cmp r0, #0x0
	bne _020A80C8
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A80EC
FUN_020A80EC: ; 0x020A80EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl FUN_020A7138
	add r0, r0, #0x2000
	cmp r5, #0x0
	mov r4, #0x0
	ldr r1, [r0, #0x270]
	addeq sp, sp, #0x4
	moveq r0, r4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r1, #0x0
	beq _020A8160
	ldr r0, [r0, #0x274]
	cmp r0, #0xc
	bls _020A8160
	ldr r4, [r1, #0x4]
	cmp r4, #0x0
	beq _020A8160
_020A813C:
	add r0, r4, #0x10
	mov r1, r5
	add r0, r0, #0x4
	bl FUN_020A8B78
_020A814C: ; 0x020A814C
	cmp r0, #0x0
	bne _020A8160
	ldr r4, [r4, #0xc]
	cmp r4, #0x0
	bne _020A813C
_020A8160:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A8170
FUN_020A8170: ; 0x020A8170
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020A7138
	add r0, r0, #0x2000
	ldr r1, [r0, #0x270]
	cmp r1, #0x0
	beq _020A81A4
	ldr r0, [r0, #0x274]
	cmp r0, #0xc
	addhi sp, sp, #0x4
	ldrhi r0, [r1, #0x4]
	ldmhiia sp!, {lr}
	bxhi lr
_020A81A4:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A81B4
FUN_020A81B4: ; 0x020A81B4
	stmdb sp!, {r4,lr}
	bl FUN_020A7138
	add r2, r0, #0x2000
	ldr r1, [r2, #0x270]
	mov r0, #0x0
	cmp r1, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r3, [r2, #0x274]
	cmp r3, #0xc
	ldmlsia sp!, {r4,lr}
	bxls lr
	ldr r2, _020A8294 ; =0x4EC4EC4F
	sub r3, r3, #0xc
	umull r2, r4, r3, r2
	movs r4, r4, lsr #0x6
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r2, [r1, #0x0]
	cmp r4, r2
	ldmlsia sp!, {r4,lr}
	bxls lr
	mov lr, r0
	cmp r4, #0x0
	bls _020A8240
	add r12, r1, #0xc
	mov r2, #0xd0
_020A8220:
	mul r0, lr, r2
	ldrb r3, [r12, r0]
	add r0, r12, r0
	cmp r3, #0x0
	beq _020A8240
	add lr, lr, #0x1
	cmp lr, r4
	blo _020A8220
_020A8240:
	cmp lr, r4
	ldmcsia sp!, {r4,lr}
	bxcs lr
	mov r2, #0x1
	strb r2, [r0, #0x0]
	ldr r3, [r1, #0x0]
	mov r2, #0x0
	str r3, [r0, #0x4]
	str r2, [r0, #0xc]
	ldr r2, [r1, #0x8]
	str r2, [r0, #0x8]
	str r0, [r1, #0x8]
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	strne r0, [r2, #0xc]
	streq r0, [r1, #0x4]
	ldr r2, [r1, #0x0]
	add r2, r2, #0x1
	str r2, [r1, #0x0]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A8294: .word 0x4EC4EC4F

	arm_func_start FUN_020A8298
FUN_020A8298: ; 0x020A8298
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_020A7138
	movs r7, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r0, r7, #0x2000
	ldrb r0, [r0, #0x26a]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r0, [r5, #0x3c]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	add r0, r5, #0x4
	bl FUN_020A80EC
	movs r6, r0
	bne _020A8300
	bl FUN_020A81B4
	mov r6, r0
_020A8300:
	cmp r6, #0x0
	bne _020A8320
	add r0, r7, #0x2000
	ldr r0, [r0, #0x278]
	cmp r0, #0x1
	bne _020A8320
	bl FUN_020A8170
	mov r6, r0
_020A8320:
	cmp r6, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r5
	add r1, r6, #0x10
	mov r2, #0xc0
	strh r4, [r6, #0x2]
	bl MIi_CpuCopyFast
	mov r0, r6
	bl FUN_020A7FB0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_020A8358
FUN_020A8358: ; 0x020A8358
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl OS_DisableInterrupts
	mov r5, r0
	bl FUN_020A7138
_020A8370: ; 0x020A8370
	cmp r0, #0x0
	bne _020A8390
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A8390:
	mov r0, r4
	bl FUN_020A8084
	movs r4, r0
	bne _020A83B8
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A83B8:
	mov r0, r5
	bl OS_RestoreInterrupts
	add r0, r4, #0x10
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A83D0
FUN_020A83D0: ; 0x020A83D0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	mov r4, r0
	bl FUN_020A7138
_020A83E8: ; 0x020A83E8
	cmp r0, #0x0
	bne _020A8408
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A8408:
	cmp r5, #0x0
	beq _020A8434
	add r1, r0, #0x2000
	ldrb r1, [r1, #0x26a]
	add r0, r0, #0x2000
	cmp r1, #0x0
	movne r5, #0x1
	mov r1, #0x1
	moveq r5, #0x0
	strb r1, [r0, #0x26a]
	b _020A8454
_020A8434:
	add r1, r0, #0x2000
	ldrb r1, [r1, #0x26a]
	add r0, r0, #0x2000
	cmp r1, #0x0
	movne r5, #0x1
	mov r1, #0x0
	moveq r5, #0x0
	strb r1, [r0, #0x26a]
_020A8454:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A846C
FUN_020A846C: ; 0x020A846C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	mov r5, r0
	bl FUN_020A7138
_020A8480: ; 0x020A8480
	cmp r0, #0x0
	mov r4, #0x0
	bne _020A84A4
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, r4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A84A4:
	add r0, r0, #0x2000
	ldr r1, [r0, #0x270]
	cmp r1, #0x0
	beq _020A84C0
	ldr r0, [r0, #0x274]
	cmp r0, #0xc
	ldrhi r4, [r1, #0x0]
_020A84C0:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A84D8
FUN_020A84D8: ; 0x020A84D8
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	mov r4, r0
	bl FUN_020A7138
_020A84E8: ; 0x020A84E8
	cmp r0, #0x0
	bne _020A8500
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
_020A8500:
	add r1, r0, #0x2000
	ldr r0, [r1, #0x270]
	cmp r0, #0x0
	beq _020A8524
	ldr r2, [r1, #0x274]
	cmp r2, #0x0
	ble _020A8524
	mov r1, #0x0
	bl MI_CpuFill8
_020A8524:
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A8534
FUN_020A8534: ; 0x020A8534
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x8]
	ldr r1, _020A858C ; =0x01FF8000
	cmp r2, r1
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, [r0, #0xc]
	sub r1, r1, #0x1
	str r1, [r0, #0xc]
	ldr r1, [r0, #0xc]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r1, #0x0
	str r1, [r0, #0x8]
	bl OS_WakeupThread
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A858C: .word 0x01FF8000

	arm_func_start FUN_020A8590
FUN_020A8590:
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	bne _020A85B8
	ldr r1, _020A85D8 ; =0x01FF8000
	str r1, [r0, #0x8]
	ldr r1, [r0, #0xc]
	add r1, r1, #0x1
	str r1, [r0, #0xc]
	mov r0, #0x1
	bx lr
_020A85B8:
	ldr r1, _020A85D8 ; =0x01FF8000
	cmp r2, r1
	ldreq r1, [r0, #0xc]
	addeq r1, r1, #0x1
	streq r1, [r0, #0xc]
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
	.balign 4
_020A85D8: .word 0x01FF8000

	arm_func_start FUN_020A85DC
FUN_020A85DC: ; 0x020A85DC
	ldr ip, _020A85E8 ; =FUN_020A8534
	ldr r0, _020A85EC ; =0x021CA87C
	bx r12
	.balign 4
_020A85E8: .word FUN_020A8534
_020A85EC: .word 0x021CA87C

	arm_func_start FUN_020A85F0
FUN_020A85F0: ; 0x020A85F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r1, [r0, #0x0]
	cmp r1, #0x12
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldrh r2, [r0, #0x2]
	ldr r1, _020A863C ; =0x021CA870
	str r2, [r1, #0x24]
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	bne _020A8628
	bl FUN_020A6BBC
_020A8628:
	ldr r0, _020A8640 ; =0x021CA874
	bl OS_WakeupThread
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A863C: .word 0x021CA870
_020A8640: .word 0x021CA874

	arm_func_start FUN_020A8644
FUN_020A8644:
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	bl OS_DisableInterrupts
	mov r5, r0
	bl FUN_020A7138
_020A8660: ; 0x020A8660
	cmp r0, #0x0
	bne _020A867C
	mov r0, r5
	bl OS_RestoreInterrupts
_020A8670: ; 0x020A8670
	mvn r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A867C:
	ldr r0, _020A87AC ; =0x021CA87C
	bl OS_LockMutex
	bl FUN_020A7138
	movs r4, r0
	bne _020A86AC
	ldr r0, _020A87AC ; =0x021CA87C
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
_020A86A0: ; 0x020A86A0
	mvn r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A86AC:
	add r0, r4, #0x2000
	ldr r1, [r0, #0x260]
	cmp r1, #0x9
	bne _020A86C8
	ldrb r0, [r0, #0x26b]
	cmp r0, #0x1
	bne _020A86E4
_020A86C8:
	ldr r0, _020A87AC ; =0x021CA87C
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x3
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A86E4:
	mov r0, r7
	mov r2, r6
	add r1, r4, #0xf00
	bl MI_CpuCopy8
	mov r3, r6, lsl #0x10
	ldr r0, _020A87B0 ; =FUN_020A85F0
	mov r1, r8
	add r2, r4, #0xf00
	mov r3, r3, lsr #0x10
	bl WM_SetDCFData
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020A873C
_020A8718:
	b _020A873C
_020A871C:
	b _020A873C
_020A8720:
	b _020A8758
_020A8724:
	b _020A873C
_020A8728:
	b _020A873C
_020A872C:
	b _020A873C
_020A8730:
	b _020A873C
_020A8734:
	b _020A873C
_020A8738:
	b _020A873C
_020A873C:
	ldr r0, _020A87AC ; =0x021CA87C
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x4
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A8758:
	ldr r0, _020A87B4 ; =0x021CA874
	bl OS_SleepThread
	ldr r0, _020A87B8 ; =0x021CA870
	ldr r0, [r0, #0x24]
	cmp r0, #0x0
	beq _020A8790
	cmp r0, #0x1
	ldr r0, _020A87AC ; =0x021CA87C
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x4
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A8790:
	ldr r0, _020A87AC ; =0x021CA87C
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r6
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A87AC: .word 0x021CA87C
_020A87B0: .word FUN_020A85F0
_020A87B4: .word 0x021CA874
_020A87B8: .word 0x021CA870

	arm_func_start FUN_020A87BC
FUN_020A87BC: ; 0x020A87BC
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _020A87DC ; =0x021CA870
	str r4, [r1, #0x28]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A87DC: .word 0x021CA870

	arm_func_start FUN_020A87E0
FUN_020A87E0: ; 0x020A87E0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, #0x0
	mov r4, r0
	mov r6, r7
	bl FUN_020A7138
	mov r5, r0
	bl OS_DisableInterrupts
_020A8800: ; 0x020A8800
	cmp r5, #0x0
	beq _020A8830
	add r1, r5, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0x9
	bne _020A8830
	ldrb r1, [r1, #0x26b]
	cmp r1, #0x0
	addeq r2, r5, #0x2100
	ldreq r1, _020A884C ; =0x0000214C
	ldreqh r6, [r2, #0x4a]
	addeq r7, r5, r1
_020A8830:
	bl OS_RestoreInterrupts
_020A8834: ; 0x020A8834
	cmp r4, #0x0
	strneh r6, [r4, #0x0]
	mov r0, r7
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A884C: .word 0x0000214C

	arm_func_start FUN_020A8850
FUN_020A8850:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, #0x0
	bl FUN_020A7138
	mov r4, r0
	bl OS_DisableInterrupts
_020A8868: ; 0x020A8868
	cmp r4, #0x0
	beq _020A8890
	add r1, r4, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0x9
	bne _020A8890
	ldrb r1, [r1, #0x26b]
	cmp r1, #0x0
	ldreq r1, _020A88A4 ; =0x00002144
	addeq r5, r4, r1
_020A8890:
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A88A4: .word 0x00002144

	arm_func_start FUN_020A88A8
FUN_020A88A8: ; 0x020A88A8
	stmdb sp!, {r4,lr}
	bl FUN_020A7138
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r0, r4, #0x2000
	ldr r1, [r0, #0x260]
	cmp r1, #0x9
	ldmneia sp!, {r4,lr}
	bxne lr
	ldrb r0, [r0, #0x26b]
	cmp r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, _020A8928 ; =0x021CA87C
	bl FUN_020A8590
_020A88E8: ; 0x020A88E8
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, _020A892C ; =0x00002144
	ldr r0, _020A8930 ; =FUN_020A85DC
	add r1, r4, r1
	add r2, r4, #0xf00
	mov r3, #0x0
	bl WM_SetDCFData
	cmp r0, #0x2
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, _020A8928 ; =0x021CA87C
	bl FUN_020A8534
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A8928: .word 0x021CA87C
_020A892C: .word 0x00002144
_020A8930: .word FUN_020A85DC

	arm_func_start FUN_020A8934
FUN_020A8934: ; 0x020A8934
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020A8978 ; =0x021CA870
	mov r2, r0
	ldr r12, [r1, #0x28]
	cmp r12, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldrh r3, [r2, #0x6]
	add r0, r2, #0x1e
	add r1, r2, #0x18
	add r2, r2, #0x2c
	blx r12
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A8978: .word 0x021CA870

	arm_func_start FUN_020A897C
FUN_020A897C: ; 0x020A897C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020A89C8 ; =0x021CA870
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020A89CC ; =0x021CA87C
	mov r2, #0x0
	mov r3, #0x1
	strb r3, [r1, #0x0]
	str r2, [r1, #0x24]
	str r2, [r1, #0x8]
	str r2, [r1, #0x4]
	bl OS_InitMutex
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A89C8: .word 0x021CA870
_020A89CC: .word 0x021CA87C

	arm_func_start FUN_020A89D0
FUN_020A89D0: ; 0x020A89D0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020A8A48 ; =0x021CA89C
	ands r1, r0, #0x2
	ldrb r12, [r2, #0x0]
	movne r0, r0, asr #0x2
	andne lr, r0, #0xff
	moveq r0, r0, asr #0x2
	addeq r0, r0, #0x19
	andeq lr, r0, #0xff
	mov r1, r12, lsr #0x1f
	rsb r0, r1, r12, lsl #0x1c
	cmp r12, #0x10
	ldr r3, _020A8A4C ; =0x021CA8A0
	add r0, r1, r0, ror #0x1c
	strb lr, [r3, r0]
	addcc r0, r12, #0x1
	strccb r0, [r2, #0x0]
	addcc sp, sp, #0x4
	ldmccia sp!, {lr}
	bxcc lr
	add r0, r12, #0x1
	mov r1, r0, lsr #0x1f
	rsb r0, r1, r0, lsl #0x1c
	add r0, r1, r0, ror #0x1c
	add r0, r0, #0x10
	strb r0, [r2, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A8A48: .word 0x021CA89C
_020A8A4C: .word 0x021CA8A0

	arm_func_start FUN_020A8A50
FUN_020A8A50: ; 0x020A8A50
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020A8A90
	mov r1, #0x0
	cmp r0, #0x1c
	movcs r1, #0x3
	bhs _020A8A80
	cmp r0, #0x16
	movcs r1, #0x2
	bhs _020A8A80
	cmp r0, #0x10
	movcs r1, #0x1
_020A8A80:
	mov r0, r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A8A90
FUN_020A8A90: ; 0x020A8A90
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020A8B20 ; =0x021CA89C
	mov r0, #0x0
	ldrb r1, [r1, #0x0]
	cmp r1, #0x10
	bls _020A8ADC
	ldr r2, _020A8B24 ; =0x021CA8A0
	mov r3, r0
_020A8AB4:
	ldrb r1, [r2, #0x0]
	add r3, r3, #0x1
	cmp r3, #0x10
	add r0, r0, r1
	add r2, r2, #0x1
	blt _020A8AB4
	mov r1, r0, asr #0x3
	add r0, r0, r1, lsr #0x1c
	mov r0, r0, asr #0x4
	b _020A8B10
_020A8ADC:
	cmp r1, #0x0
	beq _020A8B10
	mov r3, r0
	cmp r1, #0x0
	ble _020A8B0C
	ldr ip, _020A8B24 ; =0x021CA8A0
_020A8AF4:
	ldrb r2, [r12, #0x0]
	add r3, r3, #0x1
	cmp r3, r1
	add r0, r0, r2
	add r12, r12, #0x1
	blt _020A8AF4
_020A8B0C:
	bl _s32_div_f
_020A8B10:
	and r0, r0, #0xff
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A8B20: .word 0x021CA89C
_020A8B24: .word 0x021CA8A0

	arm_func_start FUN_020A8B28
FUN_020A8B28: ; 0x020A8B28
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	mov r5, r0
	bl FUN_020A7138
_020A8B3C: ; 0x020A8B3C
	cmp r0, #0x0
	mov r4, #0x0
	beq _020A8B60
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x9
	bne _020A8B60
	bl FUN_020A8A50
	mov r4, r0
_020A8B60:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A8B78
FUN_020A8B78:
	mov r12, #0x0
_020A8B7C:
	ldrb r3, [r0, r12]
	ldrb r2, [r1, r12]
	cmp r3, r2
	movne r0, #0x0
	bxne lr
	add r12, r12, #0x1
	cmp r12, #0x6
	blt _020A8B7C
	mov r0, #0x1
	bx lr

	arm_func_start FUN_020A8BA4
FUN_020A8BA4: ; 0x020A8BA4
	ldr ip, _020A8BAC ; =DGT_Hash1GetDigest_R
	bx r12
	.balign 4
_020A8BAC: .word DGT_Hash1GetDigest_R

	arm_func_start FUN_020A8BB0
FUN_020A8BB0: ; 0x020A8BB0
	ldr ip, _020A8BB8 ; =DGT_Hash1SetSource
	bx r12
	.balign 4
_020A8BB8: .word DGT_Hash1SetSource

	arm_func_start FUN_020A8BBC
FUN_020A8BBC: ; 0x020A8BBC
	ldr ip, _020A8BC4 ; =DGT_Hash1Reset
	bx r12
	.balign 4
_020A8BC4: .word DGT_Hash1Reset

	arm_func_start FUN_020A8BC8
FUN_020A8BC8: ; 0x020A8BC8
	stmdb sp!, {r4,lr}
	ldrsh r4, [r3, #0x0]
	ldr r12, [sp, #0x8]
	mov lr, #0x0
	strh r4, [r0, #0x0]
	ldrb r4, [r3, #0x2]
	cmp r12, #0x2
	strb r4, [r0, #0x2]
	strb lr, [r0, #0x3]
	beq _020A8C04
	cmp r12, #0x3
	beq _020A8C10
	cmp r12, #0x4
	beq _020A8C1C
	ldmia sp!, {r4,pc}
_020A8C04:
	add r0, r0, #0x4
	bl FUN_020A8CA8
	ldmia sp!, {r4,pc}
_020A8C10:
	add r0, r0, #0x4
	bl FUN_020A91D8
	ldmia sp!, {r4,pc}
_020A8C1C:
	add r0, r0, #0x4
	bl FUN_020A9D18
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020A8C28
FUN_020A8C28: ; 0x020A8C28
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrsh r12, [r0, #0x0]
	cmp r3, #0x2
	strh r12, [sp, #0x0]
	ldrb r12, [r0, #0x2]
	strb r12, [sp, #0x2]
	beq _020A8C60
	cmp r3, #0x3
	beq _020A8C78
	cmp r3, #0x4
	beq _020A8C90
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020A8C60:
	add r3, sp, #0x0
	add r0, r0, #0x4
	sub r2, r2, #0x4
	bl FUN_020A8F58
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020A8C78:
	add r3, sp, #0x0
	add r0, r0, #0x4
	sub r2, r2, #0x4
	bl FUN_020A97DC
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020A8C90:
	add r3, sp, #0x0
	add r0, r0, #0x4
	sub r2, r2, #0x4
	bl FUN_020A9F10
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020A8CA8
FUN_020A8CA8: ; 0x020A8CA8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x3c
	movs r2, r2, lsr #0x2
	str r2, [sp, #0x4]
	mov r2, #0x0
	str r2, [sp, #0x0]
	addeq sp, sp, #0x3c
	ldmeqia sp!, {r4-r11,pc}
_020A8CC8: ; 0x020A8CC8
	mov r5, #0x8000
	ldr fp, _020A8F4C ; =0x020FF5D4
	ldr r4, _020A8F50 ; =0x00007FFF
	str r2, [sp, #0x8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	str r2, [sp, #0x14]
	str r2, [sp, #0x18]
	rsb r5, r5, #0x0
	mov r6, #0x2
	mov lr, #0x58
	str r2, [sp, #0x1c]
	str r2, [sp, #0x20]
	str r2, [sp, #0x24]
	str r2, [sp, #0x28]
	str r2, [sp, #0x2c]
	str r2, [sp, #0x30]
	str r2, [sp, #0x34]
_020A8D10:
	ldrb r9, [r3, #0x2]
	ldrsh r2, [r3, #0x0]
	ldrsh r7, [r1, #0x0]
	mov r10, r9, lsl #0x1
	ldrsh r10, [r11, r10]
	subs r8, r7, r2
	movmi r7, r6
	ldrpl r7, [sp, #0x8]
	rsbmi r8, r8, #0x0
	cmp r8, r10
	orrge r7, r7, #0x1
	ands r8, r7, #0x1
	ldreq r10, [sp, #0xc]
	ands r8, r7, #0x2
	rsbne r10, r10, #0x0
	mov r8, #0x8000
	add r2, r2, r10
	rsb r8, r8, #0x0
	cmp r2, r8
	ldr r8, _020A8F54 ; =0x020FF5B8
	movlt r2, r5
	cmp r2, r4
	ldrsb r8, [r8, r7]
	movgt r2, r4
	adds r9, r9, r8
	ldrmi r9, [sp, #0x10]
	bmi _020A8D84
	cmp r9, #0x58
	movgt r9, lr
_020A8D84:
	strh r2, [r3, #0x0]
	strb r9, [r3, #0x2]
	ldrb r10, [r3, #0x2]
	and r2, r7, #0xff
	ldrsh r7, [r3, #0x0]
	ldrsh r8, [r1, #0x2]
	mov r12, r10, lsl #0x1
	ldrsh r12, [r11, r12]
	subs r9, r8, r7
	movmi r8, r6
	ldrpl r8, [sp, #0x14]
	rsbmi r9, r9, #0x0
	cmp r9, r12
	orrge r8, r8, #0x1
	ands r9, r8, #0x1
	ldreq r12, [sp, #0x18]
	ands r9, r8, #0x2
	rsbne r12, r12, #0x0
	mov r9, #0x8000
	add r7, r7, r12
	rsb r9, r9, #0x0
	cmp r7, r9
	ldr sb, _020A8F54 ; =0x020FF5B8
	movlt r7, r5
	cmp r7, r4
	ldrsb r9, [r9, r8]
	movgt r7, r4
	adds r10, r10, r9
	ldrmi r10, [sp, #0x1c]
	bmi _020A8E04
	cmp r10, #0x58
	movgt r10, lr
_020A8E04:
	strh r7, [r3, #0x0]
	strb r10, [r3, #0x2]
	and r7, r8, #0xff
	orr r2, r2, r7, lsl #0x2
	ldrb r10, [r3, #0x2]
	ldrsh r7, [r3, #0x0]
	ldrsh r8, [r1, #0x4]
	mov r12, r10, lsl #0x1
	ldrsh r12, [r11, r12]
	subs r9, r8, r7
	movmi r8, r6
	ldrpl r8, [sp, #0x20]
	rsbmi r9, r9, #0x0
	cmp r9, r12
	orrge r8, r8, #0x1
	ands r9, r8, #0x1
	ldreq r12, [sp, #0x24]
	ands r9, r8, #0x2
	rsbne r12, r12, #0x0
	mov r9, #0x8000
	add r7, r7, r12
	rsb r9, r9, #0x0
	cmp r7, r9
	ldr sb, _020A8F54 ; =0x020FF5B8
	movlt r7, r5
	cmp r7, r4
	ldrsb r9, [r9, r8]
	movgt r7, r4
	and r2, r2, #0xff
	adds r10, r10, r9
	ldrmi r10, [sp, #0x28]
	bmi _020A8E8C
	cmp r10, #0x58
	movgt r10, lr
_020A8E8C:
	strh r7, [r3, #0x0]
	strb r10, [r3, #0x2]
	and r7, r8, #0xff
	orr r2, r2, r7, lsl #0x4
	ldrb r10, [r3, #0x2]
	ldrsh r8, [r1, #0x6]
	ldrsh r7, [r3, #0x0]
	mov r12, r10, lsl #0x1
	ldrsh r12, [r11, r12]
	subs r9, r8, r7
	movmi r8, r6
	ldrpl r8, [sp, #0x2c]
	rsbmi r9, r9, #0x0
	cmp r9, r12
	orrge r8, r8, #0x1
	ands r9, r8, #0x1
	ldreq r12, [sp, #0x30]
	ands r9, r8, #0x2
	rsbne r12, r12, #0x0
	mov r9, #0x8000
	add r7, r7, r12
	rsb r9, r9, #0x0
	cmp r7, r9
	ldr sb, _020A8F54 ; =0x020FF5B8
	movlt r7, r5
	cmp r7, r4
	ldrsb r9, [r9, r8]
	movgt r7, r4
	and r2, r2, #0xff
	adds r10, r10, r9
	add r1, r1, #0x8
	ldrmi r10, [sp, #0x34]
	bmi _020A8F18
	cmp r10, #0x58
	movgt r10, lr
_020A8F18:
	strh r7, [r3, #0x0]
	and r7, r8, #0xff
	strb r10, [r3, #0x2]
	orr r2, r2, r7, lsl #0x6
	strb r2, [r0], #0x1
	ldr r2, [sp, #0x0]
	add r7, r2, #0x1
	ldr r2, [sp, #0x4]
	str r7, [sp, #0x0]
	cmp r7, r2
	blo _020A8D10
	add sp, sp, #0x3c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020A8F4C: .word 0x020FF5D4
_020A8F50: .word 0x00007FFF
_020A8F54: .word 0x020FF5B8

	arm_func_start FUN_020A8F58
FUN_020A8F58: ; 0x020A8F58
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	cmp r2, #0x0
	addls sp, sp, #0x34
	mov r12, #0x0
	ldmlsia sp!, {r4-r11,pc}
_020A8F70: ; 0x020A8F70
	mov r4, #0x8000
	rsb r6, r4, #0x0
	ldr r5, _020A91CC ; =0x00007FFF
	ldr fp, _020A91D0 ; =0x020FF5D4
	str r12, [sp, #0x0]
	str r12, [sp, #0x8]
	str r12, [sp, #0xc]
	str r12, [sp, #0x14]
	str r12, [sp, #0x18]
	mov r4, #0x58
	str r12, [sp, #0x20]
	str r12, [sp, #0x24]
	str r12, [sp, #0x2c]
_020A8FA4:
	ldrb r7, [r0, #0x0]
	ldrb r8, [r3, #0x2]
	ldrsh r9, [r3, #0x0]
	and r10, r7, #0x3
	ands r7, r10, #0x1
	mov r7, r8, lsl #0x1
	ldrsh r7, [r11, r7]
	ldreq r7, [sp, #0x0]
	ands lr, r10, #0x2
	str lr, [sp, #0x4]
	beq _020A8FE8
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r6
	b _020A8FF4
_020A8FE8:
	add r9, r9, r7
	cmp r9, r5
	movgt r9, r5
_020A8FF4:
	ldr r7, _020A91D4 ; =0x020FF5B8
	ldrsb r7, [r7, r10]
	adds r8, r8, r7
	ldrmi r8, [sp, #0x8]
	bmi _020A9010
	cmp r8, #0x58
	movgt r8, r4
_020A9010:
	mov r7, r9, lsl #0x10
	mov r7, r7, asr #0x10
	strh r7, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r7, [r1, #0x0]
	ldrb r7, [r0, #0x0]
	ldrb r8, [r3, #0x2]
	ldrsh r9, [r3, #0x0]
	mov r7, r7, asr #0x2
	and r10, r7, #0x3
	ands r7, r10, #0x1
	mov r7, r8, lsl #0x1
	ldrsh r7, [r11, r7]
	ldreq r7, [sp, #0xc]
	ands lr, r10, #0x2
	str lr, [sp, #0x10]
	beq _020A906C
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r6
	b _020A9078
_020A906C:
	add r9, r9, r7
	cmp r9, r5
	movgt r9, r5
_020A9078:
	ldr r7, _020A91D4 ; =0x020FF5B8
	ldrsb r7, [r7, r10]
	adds r8, r8, r7
	ldrmi r8, [sp, #0x14]
	bmi _020A9094
	cmp r8, #0x58
	movgt r8, r4
_020A9094:
	mov r7, r9, lsl #0x10
	mov r7, r7, asr #0x10
	strh r7, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r7, [r1, #0x2]
	ldrb r7, [r0, #0x0]
	ldrb r8, [r3, #0x2]
	ldrsh r9, [r3, #0x0]
	mov r7, r7, asr #0x4
	and r10, r7, #0x3
	ands r7, r10, #0x1
	mov r7, r8, lsl #0x1
	ldrsh r7, [r11, r7]
	ldreq r7, [sp, #0x18]
	ands lr, r10, #0x2
	str lr, [sp, #0x1c]
	beq _020A90F0
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r6
	b _020A90FC
_020A90F0:
	add r9, r9, r7
	cmp r9, r5
	movgt r9, r5
_020A90FC:
	ldr r7, _020A91D4 ; =0x020FF5B8
	ldrsb r7, [r7, r10]
	adds r8, r8, r7
	ldrmi r8, [sp, #0x20]
	bmi _020A9118
	cmp r8, #0x58
	movgt r8, r4
_020A9118:
	mov r7, r9, lsl #0x10
	mov r7, r7, asr #0x10
	strh r7, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r7, [r1, #0x4]
	ldrb r7, [r0, #0x0]
	ldrb r8, [r3, #0x2]
	ldrsh r9, [r3, #0x0]
	mov r7, r7, asr #0x6
	and r10, r7, #0x3
	ands r7, r10, #0x1
	mov r7, r8, lsl #0x1
	ldrsh r7, [r11, r7]
	ldreq r7, [sp, #0x24]
	ands lr, r10, #0x2
	str lr, [sp, #0x28]
	beq _020A9174
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r6
	b _020A9180
_020A9174:
	add r9, r9, r7
	cmp r9, r5
	movgt r9, r5
_020A9180:
	ldr r7, _020A91D4 ; =0x020FF5B8
	ldrsb r7, [r7, r10]
	adds r8, r8, r7
	ldrmi r8, [sp, #0x2c]
	bmi _020A919C
	cmp r8, #0x58
	movgt r8, r4
_020A919C:
	mov r7, r9, lsl #0x10
	mov r9, r7, asr #0x10
	strh r9, [r3, #0x0]
	strb r8, [r3, #0x2]
	add r12, r12, #0x1
	strh r9, [r1, #0x6]
	add r1, r1, #0x8
	add r0, r0, #0x1
	cmp r12, r2
	blo _020A8FA4
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020A91CC: .word 0x00007FFF
_020A91D0: .word 0x020FF5D4
_020A91D4: .word 0x020FF5B8

	arm_func_start FUN_020A91D8
FUN_020A91D8: ; 0x020A91D8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x54
	movs r2, r2, lsr #0x3
	str r2, [sp, #0x4]
	mov r2, #0x0
	str r2, [sp, #0x0]
	addeq sp, sp, #0x54
	ldmeqia sp!, {r4-r11,pc}
_020A91F8: ; 0x020A91F8
	ldr r5, [sp, #0x0]
	mov r4, #0x8000
	rsb lr, r4, #0x0
	ldr ip, _020A97D0 ; =0x00007FFF
	str r2, [sp, #0x10]
	str r2, [sp, #0x14]
	str r2, [sp, #0x18]
	str r2, [sp, #0x1c]
	str r2, [sp, #0x20]
	mov r4, #0x4
	mov r2, #0x58
	str r5, [sp, #0x24]
	str r5, [sp, #0x28]
	str r5, [sp, #0x2c]
	str r5, [sp, #0x30]
	str r5, [sp, #0x34]
	str r5, [sp, #0x38]
	str r5, [sp, #0x3c]
	str r5, [sp, #0x40]
	str r5, [sp, #0x44]
	str r5, [sp, #0x48]
	str r5, [sp, #0x4c]
_020A9250:
	ldrsh r8, [r3, #0x0]
	ldrsh r6, [r1, #0x0]
	ldrb r5, [r3, #0x2]
	subs r7, r6, r8
	movmi r10, r4
	ldr r6, _020A97D4 ; =0x020FF5D4
	mov r9, r5, lsl #0x1
	ldrsh r6, [r6, r9]
	ldrpl r10, [sp, #0x10]
	rsbmi r7, r7, #0x0
	cmp r7, r6
	orrge r10, r10, #0x2
	subge r7, r7, r6
	mov r9, r6, asr #0x1
	cmp r7, r9
	orrge r10, r10, #0x1
	ands r7, r10, #0x2
	mov r7, r6, asr #0x2
	addne r7, r7, r6
	ands r6, r10, #0x1
	addne r7, r7, r9
	ands r6, r10, #0x4
	rsbne r7, r7, #0x0
	add r6, r8, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r6, r7
	ldr r7, _020A97D8 ; =0x020FF5BC
	movlt r6, lr
	cmp r6, r12
	ldrsb r7, [r7, r10]
	movgt r6, r12
	adds r5, r5, r7
	ldrmi r5, [sp, #0x14]
	bmi _020A92E4
	cmp r5, #0x58
	movgt r5, r2
_020A92E4:
	strh r6, [r3, #0x0]
	strb r5, [r3, #0x2]
	and r5, r10, #0xff
	mov r5, r5, lsl #0x5
	and r10, r5, #0xff
	ldrb r8, [r3, #0x2]
	ldrsh r11, [r3, #0x0]
	ldrsh r5, [r1, #0x2]
	mov r9, r8, lsl #0x1
	subs r7, r5, r11
	ldr r5, _020A97D4 ; =0x020FF5D4
	movmi r6, r4
	ldrsh r9, [r5, r9]
	ldrpl r6, [sp, #0x18]
	rsbmi r7, r7, #0x0
	cmp r7, r9
	orrge r6, r6, #0x2
	subge r7, r7, r9
	mov r5, r9, asr #0x1
	cmp r7, r5
	orrge r6, r6, #0x1
	ands r7, r6, #0x2
	mov r7, r9, asr #0x2
	addne r7, r7, r9
	ands r9, r6, #0x1
	addne r7, r7, r5
	ands r5, r6, #0x4
	rsbne r7, r7, #0x0
	add r5, r11, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r5, r7
	ldr r7, _020A97D8 ; =0x020FF5BC
	movlt r5, lr
	cmp r5, r12
	ldrsb r7, [r7, r6]
	movgt r5, r12
	adds r8, r8, r7
	ldrmi r8, [sp, #0x1c]
	bmi _020A938C
	cmp r8, #0x58
	movgt r8, r2
_020A938C:
	strh r5, [r3, #0x0]
	strb r8, [r3, #0x2]
	and r5, r6, #0xff
	orr r5, r10, r5, lsl #0x2
	and r10, r5, #0xff
	ldrb r8, [r3, #0x2]
	ldrsh r11, [r3, #0x0]
	ldrsh r5, [r1, #0x4]
	mov r9, r8, lsl #0x1
	subs r7, r5, r11
	ldr r5, _020A97D4 ; =0x020FF5D4
	movmi r6, r4
	ldrsh r9, [r5, r9]
	ldrpl r6, [sp, #0x20]
	rsbmi r7, r7, #0x0
	cmp r7, r9
	orrge r6, r6, #0x2
	subge r7, r7, r9
	mov r5, r9, asr #0x1
	cmp r7, r5
	orrge r6, r6, #0x1
	ands r7, r6, #0x2
	mov r7, r9, asr #0x2
	addne r7, r7, r9
	ands r9, r6, #0x1
	addne r7, r7, r5
	ands r5, r6, #0x4
	rsbne r7, r7, #0x0
	add r5, r11, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r5, r7
	ldr r7, _020A97D8 ; =0x020FF5BC
	movlt r5, lr
	cmp r5, r12
	ldrsb r7, [r7, r6]
	movgt r5, r12
	adds r8, r8, r7
	ldrmi r8, [sp, #0x24]
	bmi _020A9434
	cmp r8, #0x58
	movgt r8, r2
_020A9434:
	strh r5, [r3, #0x0]
	and r5, r6, #0xff
	str r5, [sp, #0x8]
	strb r8, [r3, #0x2]
	orr r5, r10, r5, asr #0x1
	strb r5, [r0, #0x0]
	ldrb r5, [r3, #0x2]
	ldrsh r8, [r3, #0x0]
	ldrsh r6, [r1, #0x6]
	mov r9, r5, lsl #0x1
	subs r7, r6, r8
	ldr r6, _020A97D4 ; =0x020FF5D4
	movmi r10, r4
	ldrsh r6, [r6, r9]
	ldrpl r10, [sp, #0x28]
	rsbmi r7, r7, #0x0
	cmp r7, r6
	orrge r10, r10, #0x2
	subge r7, r7, r6
	mov r9, r6, asr #0x1
	cmp r7, r9
	orrge r10, r10, #0x1
	ands r7, r10, #0x2
	mov r7, r6, asr #0x2
	addne r7, r7, r6
	ands r6, r10, #0x1
	addne r7, r7, r9
	ands r6, r10, #0x4
	rsbne r7, r7, #0x0
	add r6, r8, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r6, r7
	ldr r7, _020A97D8 ; =0x020FF5BC
	movlt r6, lr
	cmp r6, r12
	ldrsb r7, [r7, r10]
	movgt r6, r12
	adds r5, r5, r7
	ldrmi r5, [sp, #0x2c]
	bmi _020A94E0
	cmp r5, #0x58
	movgt r5, r2
_020A94E0:
	strh r6, [r3, #0x0]
	strb r5, [r3, #0x2]
	ldrsh r11, [r3, #0x0]
	ldrsh r6, [r1, #0x8]
	ldrb r9, [r3, #0x2]
	and r5, r10, #0xff
	subs r8, r6, r11
	movmi r7, r4
	ldr r6, _020A97D4 ; =0x020FF5D4
	mov r10, r9, lsl #0x1
	ldrsh r10, [r6, r10]
	ldrpl r7, [sp, #0x30]
	rsbmi r8, r8, #0x0
	cmp r8, r10
	orrge r7, r7, #0x2
	subge r8, r8, r10
	mov r6, r10, asr #0x1
	cmp r8, r6
	orrge r7, r7, #0x1
	ands r8, r7, #0x2
	mov r8, r10, asr #0x2
	addne r8, r8, r10
	ands r10, r7, #0x1
	addne r8, r8, r6
	ands r6, r7, #0x4
	rsbne r8, r8, #0x0
	add r6, r11, r8
	mov r8, #0x8000
	rsb r8, r8, #0x0
	cmp r6, r8
	ldr r8, _020A97D8 ; =0x020FF5BC
	movlt r6, lr
	mov r5, r5, lsl #0x4
	cmp r6, r12
	ldrsb r8, [r8, r7]
	movgt r6, r12
	and r5, r5, #0xff
	adds r9, r9, r8
	ldrmi r9, [sp, #0x34]
	bmi _020A9588
	cmp r9, #0x58
	movgt r9, r2
_020A9588:
	strh r6, [r3, #0x0]
	strb r9, [r3, #0x2]
	and r6, r7, #0xff
	orr r5, r5, r6, lsl #0x1
	ldrb r9, [r3, #0x2]
	ldrsh r11, [r3, #0x0]
	ldrsh r6, [r1, #0xa]
	mov r10, r9, lsl #0x1
	and r5, r5, #0xff
	subs r8, r6, r11
	ldr r6, _020A97D4 ; =0x020FF5D4
	movmi r7, r4
	ldrsh r10, [r6, r10]
	ldrpl r7, [sp, #0x38]
	rsbmi r8, r8, #0x0
	cmp r8, r10
	orrge r7, r7, #0x2
	subge r8, r8, r10
	mov r6, r10, asr #0x1
	cmp r8, r6
	orrge r7, r7, #0x1
	ands r8, r7, #0x2
	mov r8, r10, asr #0x2
	addne r8, r8, r10
	ands r10, r7, #0x1
	addne r8, r8, r6
	ands r6, r7, #0x4
	rsbne r8, r8, #0x0
	add r6, r11, r8
	mov r8, #0x8000
	rsb r8, r8, #0x0
	cmp r6, r8
	ldr r8, _020A97D8 ; =0x020FF5BC
	movlt r6, lr
	cmp r6, r12
	ldrsb r8, [r8, r7]
	movgt r6, r12
	adds r9, r9, r8
	ldrmi r9, [sp, #0x3c]
	bmi _020A9630
	cmp r9, #0x58
	movgt r9, r2
_020A9630:
	ldr r8, [sp, #0x8]
	strh r6, [r3, #0x0]
	orr r8, r5, r8, lsl #0x7
	and r5, r7, #0xff
	str r5, [sp, #0xc]
	strb r9, [r3, #0x2]
	orr r5, r8, r5, asr #0x2
	strb r5, [r0, #0x1]
	ldrb r5, [r3, #0x2]
	ldrsh r8, [r3, #0x0]
	ldrsh r6, [r1, #0xc]
	mov r9, r5, lsl #0x1
	subs r7, r6, r8
	ldr r6, _020A97D4 ; =0x020FF5D4
	movmi r10, r4
	ldrsh r6, [r6, r9]
	ldrpl r10, [sp, #0x40]
	rsbmi r7, r7, #0x0
	cmp r7, r6
	orrge r10, r10, #0x2
	subge r7, r7, r6
	mov r9, r6, asr #0x1
	cmp r7, r9
	orrge r10, r10, #0x1
	ands r7, r10, #0x2
	mov r7, r6, asr #0x2
	addne r7, r7, r6
	ands r6, r10, #0x1
	addne r7, r7, r9
	ands r6, r10, #0x4
	rsbne r7, r7, #0x0
	add r6, r8, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r6, r7
	ldr r7, _020A97D8 ; =0x020FF5BC
	movlt r6, lr
	cmp r6, r12
	ldrsb r7, [r7, r10]
	movgt r6, r12
	adds r5, r5, r7
	ldrmi r5, [sp, #0x44]
	bmi _020A96E4
	cmp r5, #0x58
	movgt r5, r2
_020A96E4:
	strh r6, [r3, #0x0]
	strb r5, [r3, #0x2]
	and r5, r10, #0xff
	mov r5, r5, lsl #0x3
	and r11, r5, #0xff
	ldrsh r6, [r1, #0xe]
	ldrsh r5, [r3, #0x0]
	ldrb r9, [r3, #0x2]
	add r1, r1, #0x10
	subs r8, r6, r5
	movmi r7, r4
	ldr r6, _020A97D4 ; =0x020FF5D4
	mov r10, r9, lsl #0x1
	ldrsh r10, [r6, r10]
	ldrpl r7, [sp, #0x48]
	rsbmi r8, r8, #0x0
	cmp r8, r10
	orrge r7, r7, #0x2
	subge r8, r8, r10
	mov r6, r10, asr #0x1
	cmp r8, r6
	orrge r7, r7, #0x1
	ands r8, r7, #0x2
	mov r8, r10, asr #0x2
	addne r8, r8, r10
	ands r10, r7, #0x1
	addne r8, r8, r6
	ands r6, r7, #0x4
	rsbne r8, r8, #0x0
	mov r6, #0x8000
	add r5, r5, r8
	rsb r6, r6, #0x0
	cmp r5, r6
	ldr r6, _020A97D8 ; =0x020FF5BC
	movlt r5, lr
	cmp r5, r12
	ldrsb r6, [r6, r7]
	movgt r5, r12
	adds r9, r9, r6
	ldrmi r9, [sp, #0x4c]
	bmi _020A9790
	cmp r9, #0x58
	movgt r9, r2
_020A9790:
	strh r5, [r3, #0x0]
	and r5, r7, #0xff
	orr r6, r11, r5
	ldr r5, [sp, #0xc]
	strb r9, [r3, #0x2]
	orr r5, r6, r5, lsl #0x6
	strb r5, [r0, #0x2]
	ldr r5, [sp, #0x0]
	add r0, r0, #0x3
	add r6, r5, #0x1
	ldr r5, [sp, #0x4]
	str r6, [sp, #0x0]
	cmp r6, r5
	blo _020A9250
	add sp, sp, #0x54
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020A97D0: .word 0x00007FFF
_020A97D4: .word 0x020FF5D4
_020A97D8: .word 0x020FF5BC

	arm_func_start FUN_020A97DC
FUN_020A97DC: ; 0x020A97DC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4c
	ldr r5, _020A9D08 ; =0xAAAAAAAB
	mov r4, #0x0
	str r4, [sp, #0x0]
	umull r5, r4, r2, r5
	str r4, [sp, #0xc]
	movs r2, r4, lsr #0x1
	str r2, [sp, #0xc]
	addeq sp, sp, #0x4c
	ldmeqia sp!, {r4-r11,pc}
_020A9808: ; 0x020A9808
	ldr r2, [sp, #0x0]
	mov r4, #0x8000
	ldr lr, _020A9D0C ; =0x00007FFF
	str r2, [sp, #0x18]
	str r2, [sp, #0x24]
	str r2, [sp, #0x2c]
	str r2, [sp, #0x34]
	str r2, [sp, #0x3c]
	rsb r4, r4, #0x0
	mov r12, #0x58
	str r2, [sp, #0x40]
	str r2, [sp, #0x44]
	str r2, [sp, #0x48]
_020A983C:
	ldrb r8, [r3, #0x2]
	ldr r5, _020A9D10 ; =0x020FF5D4
	ldrb r6, [r0, #0x0]
	mov r7, r8, lsl #0x1
	ldrsh r5, [r5, r7]
	ldrb r11, [r0, #0x1]
	ldrb r2, [r0, #0x2]
	str r5, [sp, #0x4]
	mov r5, r6, asr #0x5
	ands r7, r5, #0x2
	ldr r7, [sp, #0x4]
	ldrne r10, [sp, #0x4]
	mov r7, r7, asr #0x2
	addne r7, r7, r10
	ands r10, r5, #0x1
	str r10, [sp, #0x10]
	ldrne r10, [sp, #0x4]
	ldrsh r9, [r3, #0x0]
	addne r7, r7, r10, asr #0x1
	ands r10, r5, #0x4
	str r10, [sp, #0x14]
	beq _020A98AC
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r4
	b _020A98B8
_020A98AC:
	add r9, r9, r7
	cmp r9, lr
	movgt r9, lr
_020A98B8:
	ldr r7, _020A9D14 ; =0x020FF5BC
	ldrsb r5, [r7, r5]
	adds r8, r8, r5
	ldrmi r8, [sp, #0x18]
	bmi _020A98D4
	cmp r8, #0x58
	movgt r8, r12
_020A98D4:
	mov r5, r9, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r5, [r1, #0x0]
	ldrb r8, [r3, #0x2]
	mov r5, r6, asr #0x2
	ands r7, r5, #0x2
	ldr r7, _020A9D10 ; =0x020FF5D4
	mov r10, r8, lsl #0x1
	ldrsh r7, [r7, r10]
	ldrsh r9, [r3, #0x0]
	str r7, [sp, #0x8]
	ldrne r10, [sp, #0x8]
	mov r7, r7, asr #0x2
	addne r7, r7, r10
	ands r10, r5, #0x1
	str r10, [sp, #0x1c]
	ldrne r10, [sp, #0x8]
	addne r7, r7, r10, asr #0x1
	ands r10, r5, #0x4
	str r10, [sp, #0x20]
	beq _020A9948
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r4
	b _020A9954
_020A9948:
	add r9, r9, r7
	cmp r9, lr
	movgt r9, lr
_020A9954:
	and r7, r5, #0x7
	ldr r5, _020A9D14 ; =0x020FF5BC
	ldrsb r5, [r5, r7]
	adds r8, r8, r5
	ldrmi r8, [sp, #0x24]
	bmi _020A9974
	cmp r8, #0x58
	movgt r8, r12
_020A9974:
	mov r5, r9, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	mov r6, r6, lsl #0x1
	strb r8, [r3, #0x2]
	strh r5, [r1, #0x2]
	and r6, r6, #0x7
	orr r6, r6, r11, asr #0x7
	ldrb r8, [r3, #0x2]
	ands r5, r6, #0x2
	ldr r5, _020A9D10 ; =0x020FF5D4
	mov r7, r8, lsl #0x1
	ldrsh r10, [r5, r7]
	ldrsh r9, [r3, #0x0]
	mov r7, r10, asr #0x2
	addne r7, r7, r10
	ands r5, r6, #0x1
	str r5, [sp, #0x28]
	addne r7, r7, r10, asr #0x1
	ands r5, r6, #0x4
	beq _020A99E0
	mov r5, #0x8000
	sub r9, r9, r7
	rsb r5, r5, #0x0
	cmp r9, r5
	movlt r9, r4
	b _020A99EC
_020A99E0:
	add r9, r9, r7
	cmp r9, lr
	movgt r9, lr
_020A99EC:
	ldr r5, _020A9D14 ; =0x020FF5BC
	ldrsb r5, [r5, r6]
	adds r8, r8, r5
	ldrmi r8, [sp, #0x2c]
	bmi _020A9A08
	cmp r8, #0x58
	movgt r8, r12
_020A9A08:
	mov r5, r9, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r5, [r1, #0x4]
	ldrb r8, [r3, #0x2]
	mov r6, r11, asr #0x4
	ands r5, r6, #0x2
	ldr r5, _020A9D10 ; =0x020FF5D4
	mov r7, r8, lsl #0x1
	ldrsh r10, [r5, r7]
	ldrsh r9, [r3, #0x0]
	mov r7, r10, asr #0x2
	addne r7, r7, r10
	ands r5, r6, #0x1
	str r5, [sp, #0x30]
	addne r7, r7, r10, asr #0x1
	ands r5, r6, #0x4
	beq _020A9A6C
	mov r5, #0x8000
	sub r9, r9, r7
	rsb r5, r5, #0x0
	cmp r9, r5
	movlt r9, r4
	b _020A9A78
_020A9A6C:
	add r9, r9, r7
	cmp r9, lr
	movgt r9, lr
_020A9A78:
	ldr r5, _020A9D14 ; =0x020FF5BC
	and r6, r6, #0x7
	ldrsb r5, [r5, r6]
	adds r8, r8, r5
	ldrmi r8, [sp, #0x34]
	bmi _020A9A98
	cmp r8, #0x58
	movgt r8, r12
_020A9A98:
	mov r5, r9, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r5, [r1, #0x6]
	ldrb r8, [r3, #0x2]
	mov r6, r11, asr #0x1
	ands r5, r6, #0x2
	ldr r5, _020A9D10 ; =0x020FF5D4
	mov r7, r8, lsl #0x1
	ldrsh r10, [r5, r7]
	ldrsh r9, [r3, #0x0]
	mov r7, r10, asr #0x2
	addne r7, r7, r10
	ands r5, r6, #0x1
	str r5, [sp, #0x38]
	addne r7, r7, r10, asr #0x1
	ands r5, r6, #0x4
	beq _020A9AFC
	mov r5, #0x8000
	sub r9, r9, r7
	rsb r5, r5, #0x0
	cmp r9, r5
	movlt r9, r4
	b _020A9B08
_020A9AFC:
	add r9, r9, r7
	cmp r9, lr
	movgt r9, lr
_020A9B08:
	ldr r5, _020A9D14 ; =0x020FF5BC
	and r6, r6, #0x7
	ldrsb r5, [r5, r6]
	adds r8, r8, r5
	ldrmi r8, [sp, #0x3c]
	bmi _020A9B28
	cmp r8, #0x58
	movgt r8, r12
_020A9B28:
	mov r5, r9, lsl #0x10
	mov r6, r5, asr #0x10
	mov r5, r11, lsl #0x2
	and r5, r5, #0x7
	strh r6, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r6, [r1, #0x8]
	orr r5, r5, r2, asr #0x6
	ands r6, r5, #0x2
	ldrb r6, [r3, #0x2]
	ldr r8, _020A9D10 ; =0x020FF5D4
	ldrsh r7, [r3, #0x0]
	mov r9, r6, lsl #0x1
	ldrsh r10, [r8, r9]
	mov r9, r10, asr #0x2
	addne r9, r9, r10
	ands r8, r5, #0x1
	addne r9, r9, r10, asr #0x1
	ands r8, r5, #0x4
	beq _020A9B90
	mov r8, #0x8000
	sub r7, r7, r9
	rsb r8, r8, #0x0
	cmp r7, r8
	movlt r7, r4
	b _020A9B9C
_020A9B90:
	add r7, r7, r9
	cmp r7, lr
	movgt r7, lr
_020A9B9C:
	ldr r8, _020A9D14 ; =0x020FF5BC
	ldrsb r5, [r8, r5]
	adds r6, r6, r5
	ldrmi r6, [sp, #0x40]
	bmi _020A9BB8
	cmp r6, #0x58
	movgt r6, r12
_020A9BB8:
	mov r5, r7, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r6, [r3, #0x2]
	strh r5, [r1, #0xa]
	ldrb r6, [r3, #0x2]
	mov r5, r2, asr #0x3
	ands r8, r5, #0x2
	ldr r8, _020A9D10 ; =0x020FF5D4
	mov r9, r6, lsl #0x1
	ldrsh r10, [r8, r9]
	ldrsh r7, [r3, #0x0]
	mov r9, r10, asr #0x2
	addne r9, r9, r10
	ands r8, r5, #0x1
	addne r9, r9, r10, asr #0x1
	ands r8, r5, #0x4
	beq _020A9C18
	mov r8, #0x8000
	sub r7, r7, r9
	rsb r8, r8, #0x0
	cmp r7, r8
	movlt r7, r4
	b _020A9C24
_020A9C18:
	add r7, r7, r9
	cmp r7, lr
	movgt r7, lr
_020A9C24:
	and r8, r5, #0x7
	ldr r5, _020A9D14 ; =0x020FF5BC
	ldrsb r5, [r5, r8]
	adds r6, r6, r5
	ldrmi r6, [sp, #0x44]
	bmi _020A9C44
	cmp r6, #0x58
	movgt r6, r12
_020A9C44:
	mov r5, r7, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r6, [r3, #0x2]
	strh r5, [r1, #0xc]
	ands r5, r2, #0x2
	ldrb r5, [r3, #0x2]
	ldr r7, _020A9D10 ; =0x020FF5D4
	ldrsh r6, [r3, #0x0]
	mov r8, r5, lsl #0x1
	ldrsh r9, [r7, r8]
	mov r8, r9, asr #0x2
	addne r8, r8, r9
	ands r7, r2, #0x1
	addne r8, r8, r9, asr #0x1
	ands r7, r2, #0x4
	beq _020A9CA0
	mov r7, #0x8000
	sub r6, r6, r8
	rsb r7, r7, #0x0
	cmp r6, r7
	movlt r6, r4
	b _020A9CAC
_020A9CA0:
	add r6, r6, r8
	cmp r6, lr
	movgt r6, lr
_020A9CAC:
	and r7, r2, #0x7
	ldr r2, _020A9D14 ; =0x020FF5BC
	ldrsb r2, [r2, r7]
	adds r5, r5, r2
	ldrmi r5, [sp, #0x48]
	bmi _020A9CCC
	cmp r5, #0x58
	movgt r5, r12
_020A9CCC:
	mov r2, r6, lsl #0x10
	mov r2, r2, asr #0x10
	strh r2, [r3, #0x0]
	strb r5, [r3, #0x2]
	strh r2, [r1, #0xe]
	ldr r2, [sp, #0x0]
	add r0, r0, #0x3
	add r5, r2, #0x1
	ldr r2, [sp, #0xc]
	add r1, r1, #0x10
	str r5, [sp, #0x0]
	cmp r5, r2
	blo _020A983C
	add sp, sp, #0x4c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020A9D08: .word 0xAAAAAAAB
_020A9D0C: .word 0x00007FFF
_020A9D10: .word 0x020FF5D4
_020A9D14: .word 0x020FF5BC

	arm_func_start FUN_020A9D18
FUN_020A9D18: ; 0x020A9D18
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	movs r2, r2, lsr #0x1
	str r2, [sp, #0x4]
	mov r2, #0x0
	str r2, [sp, #0x0]
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4-r11,pc}
_020A9D38: ; 0x020A9D38
	mov r4, #0x8000
	rsb r5, r4, #0x0
	ldr fp, _020A9F04 ; =0x00007FFF
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	str r2, [sp, #0x14]
	str r2, [sp, #0x18]
	mov r6, #0x8
	mov r4, #0x58
_020A9D5C:
	ldrb r2, [r3, #0x2]
	ldrsh r8, [r3, #0x0]
	ldrsh r7, [r1, #0x0]
	ldr sb, _020A9F08 ; =0x020FF5D4
	mov r12, r2, lsl #0x1
	subs r7, r7, r8
	ldrsh r12, [r9, r12]
	movmi r10, r6
	ldrpl r10, [sp, #0xc]
	rsbmi r7, r7, #0x0
	cmp r7, r12
	orrge r10, r10, #0x4
	subge r7, r7, r12
	mov lr, r12, asr #0x1
	cmp r7, lr
	orrge r10, r10, #0x2
	subge r7, r7, lr
	mov r9, r12, asr #0x2
	cmp r7, r9
	orrge r10, r10, #0x1
	ands r7, r10, #0x4
	mov r7, r12, asr #0x3
	addne r7, r7, r12
	ands r12, r10, #0x2
	addne r7, r7, lr
	ands r12, r10, #0x1
	addne r7, r7, r9
	ands r9, r10, #0x8
	rsbne r7, r7, #0x0
	add r7, r8, r7
	mov r8, #0x8000
	rsb r8, r8, #0x0
	cmp r7, r8
	ldr r8, _020A9F0C ; =0x020FF5C4
	movlt r7, r5
	cmp r7, r11
	ldrsb r8, [r8, r10]
	movgt r7, r11
	adds r2, r2, r8
	ldrmi r2, [sp, #0x10]
	bmi _020A9E08
	cmp r2, #0x58
	movgt r2, r4
_020A9E08:
	strh r7, [r3, #0x0]
	strb r2, [r3, #0x2]
	ldrsh r2, [r3, #0x0]
	ldrsh r8, [r1, #0x2]
	and lr, r10, #0xff
	str r2, [sp, #0x8]
	ldrb r2, [r3, #0x2]
	ldr r7, [sp, #0x8]
	add r1, r1, #0x4
	subs r7, r8, r7
	movmi r10, r6
	ldr r8, _020A9F08 ; =0x020FF5D4
	mov r9, r2, lsl #0x1
	ldrsh r12, [r8, r9]
	ldrpl r10, [sp, #0x14]
	rsbmi r7, r7, #0x0
	cmp r7, r12
	orrge r10, r10, #0x4
	subge r7, r7, r12
	mov r9, r12, asr #0x1
	cmp r7, r9
	orrge r10, r10, #0x2
	subge r7, r7, r9
	mov r8, r12, asr #0x2
	cmp r7, r8
	orrge r10, r10, #0x1
	ands r7, r10, #0x4
	mov r7, r12, asr #0x3
	addne r7, r7, r12
	ands r12, r10, #0x2
	addne r7, r7, r9
	ands r9, r10, #0x1
	addne r7, r7, r8
	ands r8, r10, #0x8
	ldr r8, [sp, #0x8]
	rsbne r7, r7, #0x0
	add r7, r8, r7
	mov r8, #0x8000
	rsb r8, r8, #0x0
	cmp r7, r8
	ldr r8, _020A9F0C ; =0x020FF5C4
	movlt r7, r5
	cmp r7, r11
	ldrsb r8, [r8, r10]
	movgt r7, r11
	adds r2, r2, r8
	ldrmi r2, [sp, #0x18]
	bmi _020A9ED0
	cmp r2, #0x58
	movgt r2, r4
_020A9ED0:
	strh r7, [r3, #0x0]
	strb r2, [r3, #0x2]
	and r2, r10, #0xff
	orr r2, lr, r2, lsl #0x4
	strb r2, [r0], #0x1
	ldr r2, [sp, #0x0]
	add r7, r2, #0x1
	ldr r2, [sp, #0x4]
	str r7, [sp, #0x0]
	cmp r7, r2
	blo _020A9D5C
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020A9F04: .word 0x00007FFF
_020A9F08: .word 0x020FF5D4
_020A9F0C: .word 0x020FF5C4

	arm_func_start FUN_020A9F10
FUN_020A9F10: ; 0x020A9F10
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	cmp r2, #0x0
	addls sp, sp, #0x1c
	mov r12, #0x0
	ldmlsia sp!, {r4-r11,pc}
_020A9F28: ; 0x020A9F28
	mov r4, #0x8000
	ldr fp, _020AA098 ; =0x00007FFF
	str r12, [sp, #0x8]
	str r12, [sp, #0x14]
	rsb r4, r4, #0x0
	mov lr, #0x58
_020A9F40:
	ldrb r5, [r0, #0x0]
	ldrb r6, [r3, #0x2]
	ldrsh r7, [r3, #0x0]
	and r9, r5, #0xf
	ldr r5, _020AA09C ; =0x020FF5D4
	mov r8, r6, lsl #0x1
	ldrsh r8, [r5, r8]
	ands r5, r9, #0x4
	mov r5, r8, asr #0x3
	addne r5, r5, r8
	ands r10, r9, #0x2
	str r10, [sp, #0x0]
	addne r5, r5, r8, asr #0x1
	ands r10, r9, #0x1
	addne r5, r5, r8, asr #0x2
	str r10, [sp, #0x4]
	ands r8, r9, #0x8
	beq _020A9FA0
	sub r7, r7, r5
	mov r5, #0x8000
	rsb r5, r5, #0x0
	cmp r7, r5
	movlt r7, r4
	b _020A9FAC
_020A9FA0:
	add r7, r7, r5
	cmp r7, r11
	movgt r7, r11
_020A9FAC:
	ldr r5, _020AA0A0 ; =0x020FF5C4
	ldrsb r5, [r5, r9]
	adds r6, r6, r5
	ldrmi r6, [sp, #0x8]
	bmi _020A9FC8
	cmp r6, #0x58
	movgt r6, lr
_020A9FC8:
	mov r5, r7, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r6, [r3, #0x2]
	strh r5, [r1, #0x0]
	ldrb r5, [r0, #0x0]
	ldrb r6, [r3, #0x2]
	ldrsh r7, [r3, #0x0]
	mov r5, r5, asr #0x4
	and r9, r5, #0xf
	ldr r5, _020AA09C ; =0x020FF5D4
	mov r8, r6, lsl #0x1
	ldrsh r8, [r5, r8]
	ands r5, r9, #0x4
	mov r5, r8, asr #0x3
	addne r5, r5, r8
	ands r10, r9, #0x2
	str r10, [sp, #0xc]
	addne r5, r5, r8, asr #0x1
	ands r10, r9, #0x1
	addne r5, r5, r8, asr #0x2
	str r10, [sp, #0x10]
	ands r8, r9, #0x8
	beq _020AA040
	sub r7, r7, r5
	mov r5, #0x8000
	rsb r5, r5, #0x0
	cmp r7, r5
	movlt r7, r4
	b _020AA04C
_020AA040:
	add r7, r7, r5
	cmp r7, r11
	movgt r7, r11
_020AA04C:
	ldr r5, _020AA0A0 ; =0x020FF5C4
	ldrsb r5, [r5, r9]
	adds r6, r6, r5
	ldrmi r6, [sp, #0x14]
	bmi _020AA068
	cmp r6, #0x58
	movgt r6, lr
_020AA068:
	mov r5, r7, lsl #0x10
	mov r7, r5, asr #0x10
	strh r7, [r3, #0x0]
	strb r6, [r3, #0x2]
	add r12, r12, #0x1
	strh r7, [r1, #0x2]
	cmp r12, r2
	add r1, r1, #0x4
	add r0, r0, #0x1
	blo _020A9F40
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AA098: .word 0x00007FFF
_020AA09C: .word 0x020FF5D4
_020AA0A0: .word 0x020FF5C4

	arm_func_start FUN_020AA0A4
FUN_020AA0A4:
	stmdb sp!, {r4-r8,lr}
	ldr r0, _020AA1B4 ; =0x021CA8D0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4-r8,pc}
_020AA0BC: ; 0x020AA0BC
	ldr r1, _020AA1B8 ; =0x021CAF00
	ldr r0, [r1, #0x8c8]
	cmp r0, #0x0
	bne _020AA0FC
	bl FUN_020AA4C0
	ldr r1, _020AA1B8 ; =0x021CAF00
	cmp r0, #0x0
	str r0, [r1, #0x8c8]
	beq _020AA0F4
	ldr r0, _020AA1BC ; =0x021CA8C8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4-r8,pc}
_020AA0F4:
	mov r0, #0x1
	ldmia sp!, {r4-r8,pc}
_020AA0FC:
	ldr r0, _020AA1C0 ; =0x021CCD20
	mov r5, #0x1
	ldr r0, [r0, #0x10]
	cmp r0, #0x2
	bne _020AA130
	ldr r3, [r1, #0x8d4]
	ldr r2, _020AA1C4 ; =0x020FF694
	mov r0, #0x3
	mla r0, r3, r0, r2
	ldr r3, [r1, #0x8d0]
	add r2, r3, #0x1
	ldrb r5, [r3, r0]
	str r2, [r1, #0x8d0]
_020AA130:
	mov r4, #0x0
	ldr r7, _020AA1B8 ; =0x021CAF00
	mov r8, #0x80000000
	ldr r6, _020AA1C8 ; =0x021CA8BC
	b _020AA1A4
_020AA144:
	ldr r1, [r7, #0x8cc]
	mov r2, r1
	clz r2, r2
	cmp r2, #0x20
	beq _020AA1AC
	mvn r0, r8, lsr r2
	and r3, r1, r0
	rsb r0, r2, #0x1f
	ldr r1, [r7, #0x8c8]
	ldr r2, [r6, #0x0]
	str r3, [r7, #0x8cc]
	and r0, r0, #0xff
	bl FUN_021EAE90
	ldr r0, [r7, #0x8cc]
	cmp r0, #0x0
	bne _020AA1A0
	ldr r1, [r7, #0x8c0]
	mov r0, #0x0
	add r1, r1, #0x1
	str r1, [r7, #0x8c0]
	str r0, [r7, #0x8c8]
	str r0, [r7, #0x8cc]
	b _020AA1AC
_020AA1A0:
	add r4, r4, #0x1
_020AA1A4:
	cmp r4, r5
	blt _020AA144
_020AA1AC:
	mov r0, #0x1
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020AA1B4: .word 0x021CA8D0
_020AA1B8: .word 0x021CAF00
_020AA1BC: .word 0x021CA8C8
_020AA1C0: .word 0x021CCD20
_020AA1C4: .word 0x020FF694
_020AA1C8: .word 0x021CA8BC

	arm_func_start FUN_020AA1CC
FUN_020AA1CC: ; 0x020AA1CC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	bl FUN_020AB154
_020AA1D8: ; 0x020AA1D8
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
_020AA1E8: ; 0x020AA1E8
	ldrb r5, [r0, #0x11]
	mov r0, r5
	bl FUN_020AB144
	mov r6, r0
	cmp r6, #0x0
	mov r7, #0x0
	ble _020AA294
_020AA204:
	mov r0, r5
	bl FUN_020AB10C
	mov r4, r0
	ldr r3, [r4, #0xc]
	cmp r3, #0x2
	blt _020AA230
	ldr r0, [r4, #0x474]
	ldr r2, [r4, #0x14]
	add r1, r4, #0x1c
	bl FUN_020A8C28
	b _020AA25C
_020AA230:
	cmp r3, #0x1
	bne _020AA24C
	ldr r0, [r4, #0x474]
	ldr r2, [r4, #0x14]
	add r1, r4, #0x1c
	bl FUN_020AB328
	b _020AA25C
_020AA24C:
	ldr r0, [r4, #0x474]
	ldr r2, [r4, #0x14]
	add r1, r4, #0x1c
	bl FUN_020AB2C0
_020AA25C:
	add r1, r4, #0x1c
	mov r0, r4
	str r1, [r4, #0x474]
	bl FUN_020AB088
	ldrb r1, [r4, #0x11]
	mov r0, r4
	bl FUN_020AB500
_020AA278: ; 0x020AA278
	cmp r0, #0x0
	bge _020AA288
	mov r0, r4
	bl FUN_020ACD90
_020AA288:
	add r7, r7, #0x1
	cmp r7, r6
	blt _020AA204
_020AA294:
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020AA2A0
FUN_020AA2A0: ; 0x020AA2A0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r4, _020AA4A8 ; =0x021CA8D0
	mov r10, r0
	ldr r0, [r4, #0x0]
	ldr r7, [sp, #0x28]
	cmp r0, #0x0
	mov r5, #0x0
	mov r9, r1
	mov r8, r2
	mov r11, r3
	addeq sp, sp, #0x4
	moveq r0, r5
	ldmeqia sp!, {r4-r11,pc}
_020AA2D8: ; 0x020AA2D8
	ldr r1, _020AA4AC ; =0x021CA8E8
	mov r2, r5
_020AA2E0:
	ldr r0, [r1, #0x38]
	cmp r10, r0
	ldreq r1, _020AA4AC ; =0x021CA8E8
	moveq r0, #0x94
	mlaeq r5, r2, r0, r1
	beq _020AA308
	add r2, r2, #0x1
	cmp r2, #0x3
	add r1, r1, #0x94
	blo _020AA2E0
_020AA308:
	cmp r5, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,pc}
_020AA318: ; 0x020AA318
	ldrb r0, [r9, #0x4]
	cmp r0, #0x41
	bne _020AA344
	ldrh r2, [r9, #0x6]
	mov r0, #0x0
	mov r1, #0x1
	str r2, [r5, #0x30]
	str r0, [r5, #0x4c]
	add sp, sp, #0x4
	str r1, [r5, #0x6c]
	ldmia sp!, {r4-r11,pc}
_020AA344:
	cmp r0, #0x40
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r11,pc}
_020AA354: ; 0x020AA354
	ldrb r0, [r9, #0x5]
	and r4, r0, #0x7f
	cmp r4, #0x5
	addge sp, sp, #0x4
	str r4, [r5, #0x24]
	movge r0, #0x0
	ldmgeia sp!, {r4-r11,pc}
_020AA370: ; 0x020AA370
	ldr r1, _020AA4B0 ; =0x020FF689
	ldr r0, _020AA4B4 ; =0x020FF688
	ldrb r2, [r1, r4, lsl #0x1]
	ldrb r1, [r0, r4, lsl #0x1]
	mov r0, #0x44
	mla r0, r1, r0, r2
	add r0, r0, #0xc
	cmp r8, r0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r11,pc}
_020AA39C: ; 0x020AA39C
	cmp r10, #0x0
	movne r0, #0x1
	movne r1, r0, lsl r10
	ldr r0, _020AA4B8 ; =0x021CA8B4
	moveq r1, #0x1
	ldr r0, [r0, #0x0]
	ands r0, r0, r1
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,pc}
_020AA3C4: ; 0x020AA3C4
	bl FUN_020ACDC8
	movs r6, r0
	bne _020AA40C
	ldr r0, [r5, #0x34]
	bl FUN_020AB6C4
	ldr r0, [r5, #0x34]
	bl FUN_020AB234
	bl FUN_020ACDC8
	movs r6, r0
	bne _020AA3FC
	bl FUN_020AB630
	bl FUN_020AB1E4
	bl FUN_020ACDC8
	mov r6, r0
_020AA3FC:
	cmp r6, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,pc}
_020AA40C:
	ldr r0, _020AA4BC ; =0x0000045C
	sub r2, r8, #0xc
	add r0, r6, r0
	sub r1, r0, r2
	add r0, r9, #0xc
	str r1, [sp, #0x0]
	bl MI_CpuCopy8
	ldr r0, [r5, #0x34]
	sub r1, r8, #0xc
	strb r0, [r6, #0x11]
	ldr r0, [sp, #0x0]
	str r4, [r6, #0xc]
	str r0, [r6, #0x474]
	str r1, [r6, #0x14]
	str r11, [r6, #0x464]
	str r7, [r6, #0x468]
	strb r10, [r6, #0x10]
	ldrb r2, [r9, #0x5]
	mov r0, r5
	mov r1, r6
	and r2, r2, #0x80
	str r2, [r6, #0x45c]
	ldr r2, [r9, #0x8]
	str r2, [r6, #0x460]
	ldrh r2, [r9, #0x6]
	str r2, [r6, #0x18]
	bl FUN_020AB760
_020AA478: ; 0x020AA478
	cmp r0, #0x0
	bne _020AA494
	mov r0, r6
	bl FUN_020ACD90
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020AA494:
	mov r0, r6
	bl FUN_020AB164
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AA4A8: .word 0x021CA8D0
_020AA4AC: .word 0x021CA8E8
_020AA4B0: .word 0x020FF689
_020AA4B4: .word 0x020FF688
_020AA4B8: .word 0x021CA8B4
_020AA4BC: .word 0x0000045C

	arm_func_start FUN_020AA4C0
FUN_020AA4C0: ; 0x020AA4C0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	ldr r0, _020AA728 ; =0x021CAF00
	ldr r1, _020AA72C ; =0x021CA8CC
	ldr r3, [r0, #0x8c4]
	ldr r2, [r0, #0x8c0]
	ldr r5, [r1, #0x0]
	sub r1, r3, r2
	cmp r1, #0x1
	subhi r1, r3, #0x1
	strhi r1, [r0, #0x8c0]
	movhi r1, #0x1
	cmp r1, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
_020AA500: ; 0x020AA500
	ldr r0, _020AA728 ; =0x021CAF00
	ldr r0, [r0, #0x8c0]
	ands r0, r0, #0x1
	movne r1, #0x0
	moveq r1, #0x460
	ldr r0, _020AA728 ; =0x021CAF00
	cmp r5, #0x2
	add r8, r0, r1
	ldr r1, _020AA730 ; =0x021CA8D4
	add r7, r8, #0xc
	addge r7, r7, #0x4
	ldr r1, [r1, #0x0]
	mov r0, r7
	bl FUN_020AD500
	ldr r2, _020AA734 ; =0x040002B0
	mov r3, #0x0
	ldr r1, _020AA738 ; =0x040002B8
	mov r6, r0
	strh r3, [r2, #0x0]
	str r6, [r1, #0x0]
_020AA550:
	ldrh r0, [r2, #0x0]
	ands r0, r0, #0x8000
	bne _020AA550
	ldr r0, _020AA73C ; =0x021CA8C8
	ldr r1, _020AA740 ; =0x040002B4
	ldr r0, [r0, #0x0]
	ldr r4, [r1, #0x0]
	cmp r0, #0x0
	beq _020AA588
	ldr r1, _020AA730 ; =0x021CA8D4
	mov r0, r7
	ldr r1, [r1, #0x0]
	mov r2, r4
	bl FUN_020AD1CC
_020AA588:
	ldr r0, _020AA744 ; =0x0210646C
	strb r5, [r8, #0x5]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020AA5FC
	mov r0, r6
	mov r1, r4
	mov r2, #0x0
	bl FUN_020ACF38
	ldr r1, _020AA748 ; =0x021CA8D8
	cmp r0, #0x0
	str r0, [r1, #0x0]
	beq _020AA5D4
	cmp r0, #0x1
	beq _020AA5F0
	cmp r0, #0x3
	moveq r0, #0x41
	streqb r0, [r8, #0x4]
	b _020AA5FC
_020AA5D4:
	ldr r1, _020AA728 ; =0x021CAF00
	add sp, sp, #0x8
	ldr r2, [r1, #0x8c0]
	mov r0, #0x0
	add r2, r2, #0x1
	str r2, [r1, #0x8c0]
	ldmia sp!, {r4-r8,pc}
_020AA5F0:
	ldrb r0, [r8, #0x5]
	orr r0, r0, #0x80
	strb r0, [r8, #0x5]
_020AA5FC:
	ldr r0, _020AA744 ; =0x0210646C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020AA62C
	ldr r0, _020AA74C ; =0x021CA8B8
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	ldrneb r2, [r8, #0x5]
	movne r1, #0x0
	orrne r2, r2, #0x80
	strneb r2, [r8, #0x5]
	strne r1, [r0, #0x0]
_020AA62C:
	ldr r0, _020AA750 ; =0x021CA8C4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	ldrneb r2, [r8, #0x5]
	movne r1, #0x0
	orrne r2, r2, #0x80
	strneb r2, [r8, #0x5]
	strne r1, [r0, #0x0]
	cmp r5, #0x2
	blt _020AA690
	ldrb r0, [r8, #0x5]
	ldr r3, _020AA754 ; =0x021CA8C0
	ands r0, r0, #0x80
	ldrne r0, _020AA754 ; =0x021CA8C0
	movne r1, #0x0
	strneh r1, [r0, #0x0]
	strneb r1, [r0, #0x2]
	ldr r0, _020AA730 ; =0x021CA8D4
	str r5, [sp, #0x0]
	ldr r2, [r0, #0x0]
	mov r1, r7
	sub r0, r7, #0x4
	mov r2, r2, lsr #0x1
	bl FUN_020A8BC8
	b _020AA6D4
_020AA690:
	cmp r5, #0x1
	bne _020AA6B4
	ldr r1, _020AA730 ; =0x021CA8D4
	mov r0, r7
	ldr r2, [r1, #0x0]
	mov r1, r7
	mov r2, r2, lsr #0x1
	bl FUN_020AB37C
	b _020AA6D4
_020AA6B4:
	cmp r5, #0x0
	bne _020AA6D4
	ldr r1, _020AA730 ; =0x021CA8D4
	mov r0, r7
	ldr r2, [r1, #0x0]
	mov r1, r7
	mov r2, r2, lsr #0x1
	bl FUN_020AB2FC
_020AA6D4:
	ldr r0, _020AA758 ; =0x021CCD20
	ldr r1, _020AA75C ; =0x021CA8B4
	ldrb r0, [r0, #0x0]
	mov r2, #0x1
	ldr r3, [r1, #0x0]
	mvn r0, r2, lsl r0
	ldr r1, _020AA728 ; =0x021CAF00
	and r0, r3, r0
	str r3, [r1, #0x8cc]
	str r0, [r1, #0x8cc]
	bl MATH_CountPopulation
	sub r0, r0, #0x1
	ldr r1, _020AA728 ; =0x021CAF00
	cmp r0, #0x7
	str r0, [r1, #0x8d4]
	movgt r0, #0x0
	movle r2, #0x0
	movle r0, r8
	strle r2, [r1, #0x8d0]
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020AA728: .word 0x021CAF00
_020AA72C: .word 0x021CA8CC
_020AA730: .word 0x021CA8D4
_020AA734: .word 0x040002B0
_020AA738: .word 0x040002B8
_020AA73C: .word 0x021CA8C8
_020AA740: .word 0x040002B4
_020AA744: .word 0x0210646C
_020AA748: .word 0x021CA8D8
_020AA74C: .word 0x021CA8B8
_020AA750: .word 0x021CA8C4
_020AA754: .word 0x021CA8C0
_020AA758: .word 0x021CCD20
_020AA75C: .word 0x021CA8B4

	arm_func_start FUN_020AA760
FUN_020AA760: ; 0x020AA760
	ldr r1, _020AA76C ; =0x021CA8C8
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020AA76C: .word 0x021CA8C8

	arm_func_start FUN_020AA770
FUN_020AA770: ; 0x020AA770
	stmdb sp!, {r4,lr}
	ldr r1, _020AA798 ; =0x0210646C
	mov r4, r0
	str r4, [r1, #0x0]
	bl FUN_020AD170
_020AA784: ; 0x020AA784
	cmp r4, #0x0
	ldreq r0, _020AA79C ; =0x021CA8B8
	moveq r1, #0x1
	streq r1, [r0, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020AA798: .word 0x0210646C
_020AA79C: .word 0x021CA8B8

	arm_func_start FUN_020AA7A0
FUN_020AA7A0: ; 0x020AA7A0
	cmp r0, #0x5
	movge r0, #0x0
	bxge lr
	ldr r1, _020AA80C ; =0x021CCD20
	ldr r1, [r1, #0x10]
	cmp r1, #0x1
	beq _020AA7C8
	cmp r0, #0x1
	movls r0, #0x0
	bxls lr
_020AA7C8:
	ldr r2, _020AA810 ; =0x020FF689
	ldr r1, _020AA814 ; =0x020FF688
	ldrb r12, [r2, r0, lsl #0x1]
	ldrb r3, [r1, r0, lsl #0x1]
	mov r1, #0x44
	ldr r2, _020AA818 ; =0x021CA8CC
	mla r12, r3, r1, r12
	str r0, [r2, #0x0]
	ldr r1, _020AA81C ; =0x021CA8BC
	add r3, r12, #0xc
	ldr r0, _020AA820 ; =0x021CA8C0
	mov r2, #0x0
	str r3, [r1, #0x0]
	strh r2, [r0, #0x0]
	strb r2, [r0, #0x2]
	mov r0, #0x1
	bx lr
	.balign 4
_020AA80C: .word 0x021CCD20
_020AA810: .word 0x020FF689
_020AA814: .word 0x020FF688
_020AA818: .word 0x021CA8CC
_020AA81C: .word 0x021CA8BC
_020AA820: .word 0x021CA8C0

	arm_func_start FUN_020AA824
FUN_020AA824: ; 0x020AA824
	stmdb sp!, {r4-r10,lr}
	movs r5, r2
	mov r7, r0
	movne r0, #0x0
	strne r0, [r5, #0x0]
	ldr r0, _020AA958 ; =0x021CA8D4
	mov r6, r1
	ldr r0, [r0, #0x0]
	mov r4, #0x0
	cmp r6, r0
	bne _020AA920
	ldr r8, _020AA95C ; =0x021CA8D0
	ldr r0, [r8, #0x0]
	cmp r0, #0x0
	beq _020AA920
	mov r9, r4
	cmp r0, #0x0
	bls _020AA89C
_020AA86C:
	mov r0, r7
	mov r1, r6
	mov r2, r9
	mov r3, r5
	bl FUN_020AA968
	cmp r0, #0x1
	moveq r4, #0x1
	beq _020AA89C
	ldr r0, [r8, #0x0]
	add r9, r9, #0x1
	cmp r9, r0
	blo _020AA86C
_020AA89C:
	cmp r4, #0x0
	beq _020AA90C
	ldr r8, _020AA95C ; =0x021CA8D0
	add r10, r9, #0x1
	ldr r0, [r8, #0x0]
	cmp r10, r0
	moveq r4, #0x1
	beq _020AA934
	cmp r10, r0
	bhs _020AA934
	ldr sb, _020AA960 ; =0x021CAAA4
_020AA8C8:
	mov r0, r9
	mov r1, r6
	mov r2, r10
	mov r3, r5
	bl FUN_020AA968
	cmp r0, #0x1
	bne _020AA8F8
	mov r0, r7
	mov r1, r9
	mov r2, r7
	mov r3, r6
	bl FUN_020AD61C
_020AA8F8:
	ldr r0, [r8, #0x0]
	add r10, r10, #0x1
	cmp r10, r0
	blo _020AA8C8
	b _020AA934
_020AA90C:
	mov r1, r7
	mov r2, r6
	mov r0, #0x0
	bl MIi_CpuClearFast
	b _020AA934
_020AA920:
	mov r1, r7
	mov r2, r6
	mov r0, #0x0
	bl MIi_CpuClearFast
	mov r4, #0x0
_020AA934:
	ldr r0, _020AA964 ; =0x021CA8C8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020AA950
	mov r0, r7
	mov r1, r6
	bl FUN_020AD45C
_020AA950:
	mov r0, r4
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020AA958: .word 0x021CA8D4
_020AA95C: .word 0x021CA8D0
_020AA960: .word 0x021CAAA4
_020AA964: .word 0x021CA8C8

	arm_func_start FUN_020AA968
FUN_020AA968: ; 0x020AA968
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	ldr r4, _020AABD4 ; =0x021CA8E8
	mov r10, r2
	mov r2, #0x94
	mla r6, r10, r2, r4
	str r0, [sp, #0x0]
	mov r0, r10
	str r1, [sp, #0x4]
	str r3, [sp, #0x8]
	mov r5, #0x1
	bl FUN_020AB434
	movs r8, r0
	beq _020AABB0
	mov r11, #0x0
_020AA9A4:
	bl OS_GetTick
	mov r4, r0
	mov r0, r10
	mov r9, r1
	bl FUN_020AB4B8
	movs r7, r0
	beq _020AAB98
	mov r0, #0x34
	adds r2, r4, r0
	ldr r8, [r7, #0x46c]
	ldr r3, [r7, #0x470]
	mov r1, #0x0
	adc r0, r9, #0x0
	cmp r3, r0
	cmpeq r8, r2
	bls _020AAA68
	ldr r0, [r7, #0x45c]
	cmp r0, #0x0
	bne _020AAA5C
	ldr r0, [r6, #0x3c]
	cmp r0, #0x0
	beq _020AAA5C
	ldr r0, [r6, #0x20]
	ldr r1, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [r6, #0x20]
	ldr r0, [r6, #0x3c]
	ldr r2, [sp, #0x4]
	ldr r0, [r0, #0x474]
	bl MIi_CpuCopyFast
	ldr r0, [r6, #0x3c]
	bl FUN_020ACD90
_020AAA24: ; 0x020AAA24
	mov r0, #0x0
	str r0, [r6, #0x3c]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _020AAA50
	ldrb r1, [r7, #0x10]
	ldr r2, [r0, #0x0]
	mov r0, #0x1
	orr r1, r2, r0, lsl r1
	ldr r0, [sp, #0x8]
	str r1, [r0, #0x0]
_020AAA50:
	add sp, sp, #0xc
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020AAA5C:
	add sp, sp, #0xc
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020AAA68:
	ldr r0, _020AABD8 ; =0x00008B4C
	adds r2, r8, r0
	adc r0, r3, r1
	cmp r9, r0
	cmpeq r4, r2
	bls _020AAAA8
	ldr r2, [r7, #0x18]
	mov r0, r6
	mov r1, r7
	str r2, [r6, #0x58]
	bl FUN_020ABC0C
	mov r8, r0
	mov r0, r10
	bl FUN_020AB4B8
	mov r5, r11
	b _020AABA8
_020AAAA8:
	ldr r1, [r6, #0x58]
	ldr r2, [r7, #0x18]
	add r0, r1, #0x1
	cmp r0, r2
	beq _020AAAE0
	cmp r1, #0x0
	beq _020AAAE0
	cmp r1, r2
	bhi _020AAAE0
	ldr r0, [r7, #0x45c]
	cmp r0, #0x0
	ldreq r0, [r6, #0x14]
	addeq r0, r0, #0x1
	streq r0, [r6, #0x14]
_020AAAE0:
	ldr r0, [r7, #0x18]
	cmp r5, #0x0
	str r0, [r6, #0x58]
	beq _020AAB24
	ldr r0, [r6, #0x70]
	cmp r0, #0x0
	beq _020AAB24
	mov r0, r6
	mov r1, r7
	bl FUN_020ABC0C
	mov r8, r0
	mov r0, r10
	bl FUN_020AB4B8
	ldr r0, [r6, #0x70]
	sub r0, r0, #0x1
	str r0, [r6, #0x70]
	b _020AABA8
_020AAB24:
	ldr r1, [r7, #0x464]
	ldr r0, [r6, #0x28]
	subs r2, r4, r1
	str r2, [r6, #0x28]
	ldr r1, [r6, #0x28]
	sub r0, r2, r0
	sub r0, r0, r1
	add r0, r1, r0, lsr #0x4
	str r0, [r6, #0x2c]
	str r0, [r6, #0x0]
	ldr r0, [r7, #0x474]
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	bl MIi_CpuCopyFast
	mov r0, r6
	mov r1, r7
	bl FUN_020ABC0C
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _020AAB8C
	ldrb r1, [r7, #0x10]
	ldr r2, [r0, #0x0]
	mov r0, #0x1
	orr r1, r2, r0, lsl r1
	ldr r0, [sp, #0x8]
	str r1, [r0, #0x0]
_020AAB8C:
	add sp, sp, #0xc
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020AAB98:
	add sp, sp, #0xc
	str r8, [r6, #0x8]
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020AABA8:
	cmp r8, #0x0
	bne _020AA9A4
_020AABB0:
	ldr r0, [r6, #0x3c]
	cmp r0, #0x0
	beq _020AABC8
	bl FUN_020ACD90
_020AABC0: ; 0x020AABC0
	mov r0, #0x0
	str r0, [r6, #0x3c]
_020AABC8:
	mov r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AABD4: .word 0x021CA8E8
_020AABD8: .word 0x00008B4C

	arm_func_start FUN_020AABDC
FUN_020AABDC: ; 0x020AABDC
	stmdb sp!, {r4,lr}
	ldr r3, _020AACE0 ; =0x021CA8D4
	mov r2, r1
	ldr r1, [r3, #0x0]
	mov r12, #0x0
	cmp r2, r1
	movne r0, r12
	ldmneia sp!, {r4,pc}
_020AABFC: ; 0x020AABFC
	ldr r1, _020AACE4 ; =0x021CA8D0
	ldr r4, [r1, #0x0]
	cmp r4, #0x0
	moveq r0, r12
	ldmeqia sp!, {r4,pc}
_020AAC10: ; 0x020AAC10
	mov lr, r12
	cmp r4, #0x0
	bls _020AAC48
	ldr r3, _020AACE8 ; =0x021CA8DC
_020AAC20:
	ldr r1, [r3, lr, lsl #0x2]
	cmp r1, #0x0
	beq _020AAC3C
	ldr r1, [r1, #0xc]
	cmp r1, #0x2
	moveq r12, #0x1
	beq _020AAC48
_020AAC3C:
	add lr, lr, #0x1
	cmp lr, r4
	blo _020AAC20
_020AAC48:
	cmp r12, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_020AAC54: ; 0x020AAC54
	ldr r1, _020AACEC ; =0x021CAF00
	ldr r4, _020AACEC ; =0x021CAF00
	ldr r1, [r1, #0x8c4]
	ldr r3, _020AACF0 ; =0x5F564354
	ands r1, r1, #0x1
	movne r12, #0x0
	moveq r12, #0x460
	str r3, [r4, r12]
	ldr r1, _020AACF4 ; =0x021CA8CC
	add r4, r4, r12
	ldr r1, [r1, #0x0]
	cmp r1, #0x2
	blt _020AAC94
	add r1, r4, #0x10
	bl MIi_CpuCopyFast
	b _020AAC9C
_020AAC94:
	add r1, r4, #0xc
	bl MIi_CpuCopyFast
_020AAC9C:
	mov r1, #0x40
	ldr r0, _020AACF8 ; =0x021CA8B0
	strb r1, [r4, #0x4]
	ldrh r2, [r0, #0x0]
	add r1, r2, #0x1
	strh r1, [r0, #0x0]
	strh r2, [r4, #0x6]
	bl OS_GetTick
	mov r0, r0, lsr #0x6
	orr r0, r0, r1, lsl #0x1a
	ldr r1, _020AACEC ; =0x021CAF00
	str r0, [r4, #0x8]
	ldr r2, [r1, #0x8c4]
	mov r0, #0x1
	add r2, r2, #0x1
	str r2, [r1, #0x8c4]
	ldmia sp!, {r4,pc}
	.balign 4
_020AACE0: .word 0x021CA8D4
_020AACE4: .word 0x021CA8D0
_020AACE8: .word 0x021CA8DC
_020AACEC: .word 0x021CAF00
_020AACF0: .word 0x5F564354
_020AACF4: .word 0x021CA8CC
_020AACF8: .word 0x021CA8B0

	arm_func_start FUN_020AACFC
FUN_020AACFC: ; 0x020AACFC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, #0x0
	ldr ip, _020AADB8 ; =0x021CA8DC
_020AAD10:
	ldr r0, [r12, r4, lsl #0x2]
	mov lr, r4, lsl #0x2
	cmp r0, r5
	bne _020AAD74
	ldr r1, _020AADBC ; =0x021CA8E8
	mov r0, #0x94
	mla r0, r4, r0, r1
	ldr r1, _020AADC0 ; =0x021CA8D0
	mov r3, #0x0
	ldr r2, [r1, #0x0]
	str r3, [r12, lr]
	sub r2, r2, #0x1
	str r2, [r1, #0x0]
	bl FUN_020ABC40
	mov r0, r4
	bl FUN_020AB6C4
	mov r0, r4
	bl FUN_020AB234
	ldr r0, _020AADC4 ; =0x021CA8B4
	ldr r1, [r5, #0x8]
	ldr r2, [r0, #0x0]
	mvn r1, r1
	and r1, r2, r1
	str r1, [r0, #0x0]
	b _020AAD80
_020AAD74:
	add r4, r4, #0x1
	cmp r4, #0x3
	blo _020AAD10
_020AAD80:
	ldr r0, _020AADC0 ; =0x021CA8D0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
_020AAD94: ; 0x020AAD94
	ldr r0, _020AADC8 ; =0x021CA8C4
	mov r1, #0x1
	str r1, [r0, #0x0]
	bl FUN_020AD170
	ldr r0, _020AADC4 ; =0x021CA8B4
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AADB8: .word 0x021CA8DC
_020AADBC: .word 0x021CA8E8
_020AADC0: .word 0x021CA8D0
_020AADC4: .word 0x021CA8B4
_020AADC8: .word 0x021CA8C4

	arm_func_start FUN_020AADCC
FUN_020AADCC: ; 0x020AADCC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
_020AADE4: ; 0x020AADE4
	ldr r0, _020AAF24 ; =0x021CA8D0
	ldr r0, [r0, #0x0]
	cmp r0, #0x3
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
_020AADFC: ; 0x020AADFC
	ldr r0, [r5, #0xc]
	cmp r0, #0x2
	beq _020AAE18
	cmp r0, #0x3
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r5,pc}
_020AAE18:
	ldr r1, _020AAF28 ; =0x021CA8DC
	mov r2, #0x0
_020AAE20:
	ldr r0, [r1, r2, lsl #0x2]
	cmp r0, r5
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r5,pc}
_020AAE34: ; 0x020AAE34
	add r2, r2, #0x1
	cmp r2, #0x3
	blo _020AAE20
	ldr r1, _020AAF28 ; =0x021CA8DC
	mov r4, #0x0
_020AAE48:
	ldr r0, [r1, r4, lsl #0x2]
	mov r2, r4, lsl #0x2
	cmp r0, #0x0
	streq r5, [r1, r2]
	beq _020AAE68
	add r4, r4, #0x1
	cmp r4, #0x3
	blo _020AAE48
_020AAE68:
	ldr r0, _020AAF24 ; =0x021CA8D0
	ldr r1, _020AAF2C ; =0x021CA8B4
	ldr r3, [r0, #0x0]
	ldr r2, _020AAF30 ; =0x021CA8E8
	add r3, r3, #0x1
	str r3, [r0, #0x0]
	mov r0, #0x94
	ldr r12, [r1, #0x0]
	ldr r3, [r5, #0x8]
	mla r0, r4, r0, r2
	orr r2, r12, r3
	str r2, [r1, #0x0]
	ldrb r2, [r5, #0x5]
	mov r1, r4
	bl FUN_020ABC6C
	mov r0, r4
	bl FUN_020AB714
	ldr r0, [r5, #0xc]
	cmp r0, #0x2
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {r4-r5,pc}
_020AAEC0: ; 0x020AAEC0
	ldr r0, _020AAF24 ; =0x021CA8D0
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	bne _020AAF18
	bl FUN_020AD170
	bl OS_GetTickLo
	ldr r4, _020AAF34 ; =0x021CA8B0
	ldr r3, _020AAF38 ; =0x021CA8C0
	mov r12, #0x0
	ldr r1, _020AAF3C ; =0x021CAF00
	ldr r2, _020AAF40 ; =0x021CA8C4
	mov r5, #0x1
	strh r0, [r4, #0x0]
	strh r12, [r3, #0x0]
	strb r12, [r3, #0x2]
	str r5, [r2, #0x0]
	str r12, [r1, #0x8c0]
	str r12, [r1, #0x8c4]
	str r12, [r1, #0x8cc]
	str r12, [r1, #0x8c8]
	str r12, [r1, #0x8d0]
	str r12, [r1, #0x8d4]
_020AAF18:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AAF24: .word 0x021CA8D0
_020AAF28: .word 0x021CA8DC
_020AAF2C: .word 0x021CA8B4
_020AAF30: .word 0x021CA8E8
_020AAF34: .word 0x021CA8B0
_020AAF38: .word 0x021CA8C0
_020AAF3C: .word 0x021CAF00
_020AAF40: .word 0x021CA8C4

	arm_func_start FUN_020AAF44
FUN_020AAF44: ; 0x020AAF44
	ldr r0, _020AAF54 ; =0x021CA8D0
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020AAF54: .word 0x021CA8D0

	arm_func_start FUN_020AAF58
FUN_020AAF58:
	stmdb sp!, {r4-r8,lr}
	bl OS_GetTickLo
	ldr r1, _020AB054 ; =0x021CCD20
	ldr ip, _020AB058 ; =0x021CA8B0
	ldr r4, [r1, #0x10]
	strh r0, [r12, #0x0]
	cmp r4, #0x1
	ldreq r0, _020AB05C ; =0x021CA8CC
	mov r5, #0x0
	ldr r1, _020AB060 ; =0x021CA8B4
	streq r5, [r0, #0x0]
	str r5, [r1, #0x0]
	ldr r2, _020AB064 ; =0x021CA8D0
	ldrne r0, _020AB05C ; =0x021CA8CC
	movne r1, #0x4
	strne r1, [r0, #0x0]
	str r5, [r2, #0x0]
	ldr r0, _020AB05C ; =0x021CA8CC
	ldr r3, _020AB068 ; =0x0210646C
	ldr r2, [r0, #0x0]
	mov r6, #0x1
	ldr r1, _020AB06C ; =0x020FF689
	str r6, [r3, #0x0]
	ldr r0, _020AB070 ; =0x020FF688
	ldrb r3, [r1, r2, lsl #0x1]
	ldrb r1, [r0, r2, lsl #0x1]
	mov r0, #0x44
	ldr r2, _020AB074 ; =0x021CA8D4
	mla r0, r1, r0, r3
	add r4, r0, #0xc
	ldr r1, _020AB078 ; =0x021CA8BC
	mov r5, #0x440
	ldr r0, _020AB07C ; =0x021CAF00
	mov r3, #0x0
	str r5, [r2, #0x0]
	str r4, [r1, #0x0]
	str r3, [r0, #0x8c0]
	str r3, [r0, #0x8c4]
	str r3, [r0, #0x8cc]
	str r3, [r0, #0x8c8]
	str r3, [r0, #0x8d0]
	str r3, [r0, #0x8d4]
	bl FUN_020ACF10
	mov r8, #0x0
	ldr r7, _020AB080 ; =0x021CA8E8
	ldr r5, _020AB084 ; =0x021CA8DC
	mov r6, r8
	mvn r4, #0x0
_020AB018:
	mov r0, r8
	str r6, [r5, r8, lsl #0x2]
	bl FUN_020AB714
	mov r0, r7
	mov r1, r8
	mov r2, r4
	bl FUN_020ABC6C
	add r8, r8, #0x1
	cmp r8, #0x3
	add r7, r7, #0x94
	blo _020AB018
	bl FUN_020AB284
	bl FUN_020AD474
	mov r0, #0x1
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020AB054: .word 0x021CCD20
_020AB058: .word 0x021CA8B0
_020AB05C: .word 0x021CA8CC
_020AB060: .word 0x021CA8B4
_020AB064: .word 0x021CA8D0
_020AB068: .word 0x0210646C
_020AB06C: .word 0x020FF689
_020AB070: .word 0x020FF688
_020AB074: .word 0x021CA8D4
_020AB078: .word 0x021CA8BC
_020AB07C: .word 0x021CAF00
_020AB080: .word 0x021CA8E8
_020AB084: .word 0x021CA8DC

	arm_func_start FUN_020AB088
FUN_020AB088: ; 0x020AB088
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	ldrne r1, [r0, #0x8]
	strne r1, [r2, #0x8]
	bne _020AB0B4
	ldr r2, [r0, #0x8]
	ldr r1, _020AB100 ; =0x021CB7D8
	cmp r2, #0x0
	str r2, [r1, #0x0]
	movne r1, #0x0
	strne r1, [r2, #0x4]
_020AB0B4:
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	ldrne r1, [r0, #0x4]
	strne r1, [r2, #0x4]
	bne _020AB0E0
	ldr r2, [r0, #0x4]
	ldr r1, _020AB104 ; =0x021CB7DC
	cmp r2, #0x0
	str r2, [r1, #0x0]
	movne r1, #0x0
	strne r1, [r2, #0x8]
_020AB0E0:
	ldrb r2, [r0, #0x11]
	ldr r3, _020AB108 ; =0x021CB7E0
	ldr r1, [r3, r2, lsl #0x2]
	sub r1, r1, #0x1
	str r1, [r3, r2, lsl #0x2]
	ldrb r0, [r0, #0x11]
	ldr r0, [r3, r0, lsl #0x2]
	bx lr
	.balign 4
_020AB100: .word 0x021CB7D8
_020AB104: .word 0x021CB7DC
_020AB108: .word 0x021CB7E0

	arm_func_start FUN_020AB10C
FUN_020AB10C: ; 0x020AB10C
	ldr r1, _020AB140 ; =0x021CB7D8
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	beq _020AB138
_020AB11C:
	ldrb r1, [r2, #0x11]
	cmp r1, r0
	moveq r0, r2
	bxeq lr
	ldr r2, [r2, #0x8]
	cmp r2, #0x0
	bne _020AB11C
_020AB138:
	mov r0, #0x0
	bx lr
	.balign 4
_020AB140: .word 0x021CB7D8

	arm_func_start FUN_020AB144
FUN_020AB144: ; 0x020AB144
	ldr r1, _020AB150 ; =0x021CB7E0
	ldr r0, [r1, r0, lsl #0x2]
	bx lr
	.balign 4
_020AB150: .word 0x021CB7E0

	arm_func_start FUN_020AB154
FUN_020AB154:
	ldr r0, _020AB160 ; =0x021CB7D8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020AB160: .word 0x021CB7D8

	arm_func_start FUN_020AB164
FUN_020AB164: ; 0x020AB164
	ldr r2, _020AB1D8 ; =0x021CB7D8
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	bne _020AB198
	str r0, [r2, #0x0]
	mov r12, #0x0
	str r12, [r0, #0x4]
	ldr r3, [r2, #0x0]
	ldr r1, _020AB1DC ; =0x021CB7DC
	str r12, [r3, #0x8]
	ldr r2, [r2, #0x0]
	str r2, [r1, #0x0]
	b _020AB1B8
_020AB198:
	ldr r1, _020AB1DC ; =0x021CB7DC
	mov r2, #0x0
	ldr r3, [r1, #0x0]
	str r3, [r0, #0x4]
	str r2, [r0, #0x8]
	ldr r2, [r1, #0x0]
	str r0, [r2, #0x8]
	str r0, [r1, #0x0]
_020AB1B8:
	ldrb r2, [r0, #0x11]
	ldr r3, _020AB1E0 ; =0x021CB7E0
	ldr r1, [r3, r2, lsl #0x2]
	add r1, r1, #0x1
	str r1, [r3, r2, lsl #0x2]
	ldrb r0, [r0, #0x11]
	ldr r0, [r3, r0, lsl #0x2]
	bx lr
	.balign 4
_020AB1D8: .word 0x021CB7D8
_020AB1DC: .word 0x021CB7DC
_020AB1E0: .word 0x021CB7E0

	arm_func_start FUN_020AB1E4
FUN_020AB1E4: ; 0x020AB1E4
	stmdb sp!, {r4,lr}
	ldr r0, _020AB22C ; =0x021CB7D8
	ldr r4, [r0, #0x0]
	cmp r4, #0x0
	beq _020AB20C
_020AB1F8:
	mov r0, r4
	ldr r4, [r4, #0x8]
	bl FUN_020ACD90
_020AB204: ; 0x020AB204
	cmp r4, #0x0
	bne _020AB1F8
_020AB20C:
	mov r2, #0x0
	ldr r0, _020AB230 ; =0x021CB7E0
	mov r1, r2
_020AB218:
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, #0x3
	blt _020AB218
	ldmia sp!, {r4,pc}
	.balign 4
_020AB22C: .word 0x021CB7D8
_020AB230: .word 0x021CB7E0

	arm_func_start FUN_020AB234
FUN_020AB234: ; 0x020AB234
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl FUN_020AB10C
	movs r4, r0
	beq _020AB26C
_020AB24C:
	mov r0, r4
	bl FUN_020AB088
	mov r0, r4
	bl FUN_020ACD90
	mov r0, r5
	bl FUN_020AB10C
	movs r4, r0
	bne _020AB24C
_020AB26C:
	ldr r0, _020AB280 ; =0x021CB7E0
	mov r1, #0x0
	str r1, [r0, r5, lsl #0x2]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AB280: .word 0x021CB7E0

	arm_func_start FUN_020AB284
FUN_020AB284: ; 0x020AB284
	ldr r1, _020AB2B4 ; =0x021CB7DC
	mov r2, #0x0
	ldr r0, _020AB2B8 ; =0x021CB7D8
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	ldr r0, _020AB2BC ; =0x021CB7E0
	mov r1, r2
_020AB2A0:
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, #0x3
	blt _020AB2A0
	bx lr
	.balign 4
_020AB2B4: .word 0x021CB7DC
_020AB2B8: .word 0x021CB7D8
_020AB2BC: .word 0x021CB7E0

	arm_func_start FUN_020AB2C0
FUN_020AB2C0: ; 0x020AB2C0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	addls sp, sp, #0x4
	mov lr, #0x0
	ldmlsia sp!, {pc}
_020AB2D8:
	ldrsb r12, [r0, lr]
	mov r3, lr, lsl #0x1
	add lr, lr, #0x1
	mov r12, r12, lsl #0x8
	strh r12, [r1, r3]
	cmp lr, r2
	blo _020AB2D8
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AB2FC
FUN_020AB2FC: ; 0x020AB2FC
	cmp r2, #0x0
	mov r12, #0x0
	bxls lr
_020AB308:
	mov r3, r12, lsl #0x1
	ldrsh r3, [r1, r3]
	mov r3, r3, asr #0x8
	strb r3, [r0, r12]
	add r12, r12, #0x1
	cmp r12, r2
	blo _020AB308
	bx lr

	arm_func_start FUN_020AB328
FUN_020AB328: ; 0x020AB328
	stmdb sp!, {r4,lr}
	mov r4, #0x0
	cmp r2, #0x0
	ldmlsia sp!, {r4,pc}
_020AB338:
	ldrb r3, [r0, r4]
	mvn lr, r3
	and r3, lr, #0xf
	mov r12, r3, lsl #0x3
	and r3, lr, #0x70
	add r12, r12, #0x84
	mov r3, r3, asr #0x4
	mov r12, r12, lsl r3
	ands r3, lr, #0x80
	rsbne r12, r12, #0x84
	mov r3, r4, lsl #0x1
	subeq r12, r12, #0x84
	add r4, r4, #0x1
	strh r12, [r1, r3]
	cmp r4, r2
	blo _020AB338
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020AB37C
FUN_020AB37C: ; 0x020AB37C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	mov r8, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r11,pc}
_020AB394: ; 0x020AB394
	mov r12, r8
	mov lr, #0xff
	mov r4, #0x7f
	mov r3, #0x8
_020AB3A4:
	mov r5, r8, lsl #0x1
	ldrsh r5, [r1, r5]
	ldr fp, _020AB42C ; =0x02106470
	movs r7, r5, asr #0x2
	movmi r6, r4
	ldr r5, _020AB430 ; =0x00001FDF
	rsbmi r7, r7, #0x0
	movpl r6, lr
	cmp r7, r5
	movgt r7, r5
	mov r5, r12
	add r10, r7, #0x21
_020AB3D4:
	ldr r9, [r11], #0x4
	cmp r10, r9
	ble _020AB3F0
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _020AB3D4
	mov r5, r3
_020AB3F0:
	cmp r5, #0x8
	eorge r5, r6, #0x7f
	bge _020AB414
	add r9, r7, #0x21
	add r7, r5, #0x1
	mov r7, r9, asr r7
	and r7, r7, #0xf
	orr r5, r7, r5, lsl #0x4
	eor r5, r5, r6
_020AB414:
	strb r5, [r0, r8]
	add r8, r8, #0x1
	cmp r8, r2
	blo _020AB3A4
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AB42C: .word 0x02106470
_020AB430: .word 0x00001FDF

	arm_func_start FUN_020AB434
FUN_020AB434: ; 0x020AB434
	ldr r1, _020AB440 ; =0x021CB7FC
	ldr r0, [r1, r0, lsl #0x2]
	bx lr
	.balign 4
_020AB440: .word 0x021CB7FC

	arm_func_start FUN_020AB444
FUN_020AB444: ; 0x020AB444
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r3, _020AB4AC ; =0x021CB7F0
	ldr r1, _020AB4B0 ; =0x021CB7EC
	ldr r2, [r3, r4, lsl #0x2]
	str r0, [r1, #0x0]
	cmp r2, #0x0
	mov r12, r4, lsl #0x2
	beq _020AB494
	ldr r1, _020AB4B4 ; =0x021CB7FC
	ldr r2, [r2, #0x8]
	ldr r0, [r1, r12]
	sub r0, r0, #0x1
	str r0, [r1, r12]
	str r2, [r3, r12]
	ldr r1, [r3, r12]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x4]
_020AB494:
	ldr r0, _020AB4B0 ; =0x021CB7EC
	ldr r0, [r0, #0x0]
	bl OS_RestoreInterrupts
	ldr r0, _020AB4B4 ; =0x021CB7FC
	ldr r0, [r0, r4, lsl #0x2]
	ldmia sp!, {r4,pc}
	.balign 4
_020AB4AC: .word 0x021CB7F0
_020AB4B0: .word 0x021CB7EC
_020AB4B4: .word 0x021CB7FC

	arm_func_start FUN_020AB4B8
FUN_020AB4B8: ; 0x020AB4B8
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r2, _020AB4F8 ; =0x021CB7F0
	ldr r1, _020AB4FC ; =0x021CB7EC
	ldr r2, [r2, r4, lsl #0x2]
	str r0, [r1, #0x0]
	cmp r2, #0x0
	beq _020AB4EC
	bl OS_RestoreInterrupts
	ldr r0, _020AB4F8 ; =0x021CB7F0
	ldr r0, [r0, r4, lsl #0x2]
	ldmia sp!, {r4,pc}
_020AB4EC:
	bl OS_RestoreInterrupts
_020AB4F0: ; 0x020AB4F0
	mov r0, #0x0
	ldmia sp!, {r4,pc}
	.balign 4
_020AB4F8: .word 0x021CB7F0
_020AB4FC: .word 0x021CB7EC

	arm_func_start FUN_020AB500
FUN_020AB500:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r0
	mov r4, r1
	addeq sp, sp, #0x4
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
_020AB51C: ; 0x020AB51C
	cmp r4, #0x3
	addcs sp, sp, #0x4
	mvncs r0, #0x0
	ldmcsia sp!, {r4-r5,pc}
_020AB52C: ; 0x020AB52C
	bl OS_DisableInterrupts
	ldr r3, _020AB620 ; =0x021CB7F0
	ldr r1, _020AB624 ; =0x021CB7EC
	ldr r2, [r3, r4, lsl #0x2]
	str r0, [r1, #0x0]
	cmp r2, #0x0
	mov r12, r4, lsl #0x2
	bne _020AB574
	str r5, [r3, r12]
	ldr r0, [r3, r12]
	mov r2, #0x0
	str r2, [r0, #0x4]
	ldr r1, [r3, r12]
	ldr r0, _020AB628 ; =0x021CB808
	str r2, [r1, #0x8]
	ldr r1, [r3, r12]
	str r1, [r0, r12]
	b _020AB5F4
_020AB574:
	ldr r0, _020AB628 ; =0x021CB808
	ldr r3, [r0, r12]
	cmp r3, #0x0
	beq _020AB5D4
	ldr r1, [r5, #0x18]
_020AB588:
	ldr r0, [r3, #0x18]
	cmp r0, r1
	bhs _020AB5C8
	str r3, [r5, #0x4]
	ldr r0, [r3, #0x8]
	ldr r1, _020AB628 ; =0x021CB808
	str r0, [r5, #0x8]
	str r5, [r3, #0x8]
	ldr r0, [r5, #0x8]
	mov r2, r4, lsl #0x2
	cmp r0, #0x0
	strne r5, [r0, #0x4]
	ldr r0, [r1, r4, lsl #0x2]
	cmp r3, r0
	streq r5, [r1, r2]
	b _020AB5F4
_020AB5C8:
	ldr r3, [r3, #0x4]
	cmp r3, #0x0
	bne _020AB588
_020AB5D4:
	mov r0, #0x0
	ldr r1, _020AB620 ; =0x021CB7F0
	str r0, [r5, #0x4]
	ldr r0, [r1, r4, lsl #0x2]
	str r0, [r5, #0x8]
	ldr r0, [r1, r4, lsl #0x2]
	str r5, [r0, #0x4]
	str r5, [r1, r4, lsl #0x2]
_020AB5F4:
	ldr r2, _020AB62C ; =0x021CB7FC
	ldr r0, _020AB624 ; =0x021CB7EC
	ldr r1, [r2, r4, lsl #0x2]
	add r1, r1, #0x1
	str r1, [r2, r4, lsl #0x2]
	ldr r0, [r0, #0x0]
	bl OS_RestoreInterrupts
	ldr r0, _020AB62C ; =0x021CB7FC
	ldr r0, [r0, r4, lsl #0x2]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AB620: .word 0x021CB7F0
_020AB624: .word 0x021CB7EC
_020AB628: .word 0x021CB808
_020AB62C: .word 0x021CB7FC

	arm_func_start FUN_020AB630
FUN_020AB630: ; 0x020AB630
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	mov r7, #0x0
	ldr r1, _020AB6B8 ; =0x021CB7EC
	mov r4, r7
	mov r9, r7
	str r0, [r1, #0x0]
	ldr r5, _020AB6BC ; =0x021CB7F0
	ldr r8, _020AB6C0 ; =0x021CB7FC
	b _020AB69C
_020AB65C:
	ldr r0, [r5, r7, lsl #0x2]
	mov r6, r7, lsl #0x2
	cmp r0, #0x0
	beq _020AB694
_020AB66C:
	ldr r0, [r5, r6]
	ldr r1, [r0, #0x8]
	str r1, [r5, r6]
	ldr r1, [r5, r6]
	cmp r1, #0x0
	strne r4, [r1, #0x4]
	bl FUN_020ACD90
	ldr r0, [r5, r6]
	cmp r0, #0x0
	bne _020AB66C
_020AB694:
	str r9, [r8, r7, lsl #0x2]
	add r7, r7, #0x1
_020AB69C:
	cmp r7, #0x3
	blt _020AB65C
	ldr r0, _020AB6B8 ; =0x021CB7EC
	ldr r0, [r0, #0x0]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020AB6B8: .word 0x021CB7EC
_020AB6BC: .word 0x021CB7F0
_020AB6C0: .word 0x021CB7FC

	arm_func_start FUN_020AB6C4
FUN_020AB6C4: ; 0x020AB6C4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl FUN_020AB4B8
	movs r4, r0
	beq _020AB6FC
_020AB6DC:
	mov r0, r5
	bl FUN_020AB444
	mov r0, r4
	bl FUN_020ACD90
	mov r0, r5
	bl FUN_020AB4B8
	movs r4, r0
	bne _020AB6DC
_020AB6FC:
	ldr r0, _020AB710 ; =0x021CB7FC
	mov r1, #0x0
	str r1, [r0, r5, lsl #0x2]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AB710: .word 0x021CB7FC

	arm_func_start FUN_020AB714
FUN_020AB714: ; 0x020AB714
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _020AB750 ; =0x021CB7EC
	ldr r3, _020AB754 ; =0x021CB808
	mov lr, #0x0
	str lr, [r3, r4, lsl #0x2]
	ldr r2, _020AB758 ; =0x021CB7FC
	ldr r12, [r3, r4, lsl #0x2]
	ldr r3, _020AB75C ; =0x021CB7F0
	str r0, [r1, #0x0]
	str r12, [r3, r4, lsl #0x2]
	str lr, [r2, r4, lsl #0x2]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,pc}
	.balign 4
_020AB750: .word 0x021CB7EC
_020AB754: .word 0x021CB808
_020AB758: .word 0x021CB7FC
_020AB75C: .word 0x021CB7F0

	arm_func_start FUN_020AB760
FUN_020AB760:
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	ldr r2, [r7, #0x5c]
	mov r6, r1
	cmp r2, #0x0
	mov r4, #0x0
	beq _020AB790
	ldr r1, [r6, #0x18]
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	bl FUN_020ABBEC
	b _020AB820
_020AB790:
	ldr r2, [r6, #0x18]
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	bl FUN_020ABB1C
_020AB7A0: ; 0x020AB7A0
	cmp r0, #0x0
	ldreq r1, [r7, #0x14]
	moveq r0, r4
	addeq r1, r1, #0x1
	streq r1, [r7, #0x14]
	ldmeqia sp!, {r4-r8,pc}
_020AB7B8: ; 0x020AB7B8
	ldr r0, [r6, #0x18]
	str r0, [r7, #0x10]
	ldr r2, [r6, #0x18]
	ldr r1, [r7, #0x54]
	cmp r1, r2
	ldreq r1, [r7, #0x14]
	moveq r0, r4
	addeq r1, r1, #0x1
	streq r1, [r7, #0x14]
	ldmeqia sp!, {r4-r8,pc}
_020AB7E0: ; 0x020AB7E0
	add r0, r1, #0x1
	cmp r0, r2
	beq _020AB820
	ldr r0, [r6, #0x45c]
	cmp r0, #0x0
	bne _020AB820
	subs r0, r2, r1
	rsbmi r0, r0, #0x0
	cmp r0, #0x64
	strgt r2, [r7, #0x54]
	movgt r0, #0x0
	ldmgtia sp!, {r4-r8,pc}
_020AB810: ; 0x020AB810
	cmp r1, r2
	ldrhi r0, [r7, #0x1c]
	addhi r0, r0, #0x1
	strhi r0, [r7, #0x1c]
_020AB820:
	ldr r0, [r6, #0x18]
	str r0, [r7, #0x54]
	ldr r0, [r7, #0x4c]
	cmp r0, #0x0
	bne _020AB858
	ldr r1, [r6, #0x460]
	ldr r0, _020ABAF4 ; =0x00000464
	str r1, [r7, #0x4c]
	add r1, r6, r0
	add r0, r7, #0x44
	ldmia r1, {r2-r3}
	stmia r0, {r2-r3}
	mov r0, #0x0
	str r0, [r7, #0x6c]
_020AB858:
	ldr r3, [r6, #0x460]
	ldr r1, [r7, #0x4c]
	ldr r2, [r6, #0x464]
	ldr r0, [r7, #0x44]
	sub r1, r3, r1
	ldr r3, [r7, #0x80]
	mov r1, r1, lsl #0x6
	subs r0, r2, r0
	subs r5, r1, r0
	cmp r3, #0x0
	mov r0, #0x0
	beq _020AB894
	ldr r2, [r6, #0x45c]
	cmp r2, #0x0
	beq _020AB89C
_020AB894:
	str r5, [r7, #0x80]
	b _020AB918
_020AB89C:
	str r5, [r7, #0x80]
	subs r2, r5, r3
	ldr r8, [r7, #0x7c]
	ldr r3, _020ABAF8 ; =0x00008B18
	ldr ip, _020ABAFC ; =0x0000CC8D
	add r3, r8, r3
	mov r8, r3, lsl #0x1
	rsbmi r2, r2, #0x0
	mov r3, r8, asr #0x1f
	adds r8, r8, r12
	mov r12, r2, asr #0x1f
	adc r3, r3, #0x0
	cmp r12, r3
	cmpeq r2, r8
	bls _020AB8F4
	ldr lr, _020ABB00 ; =0x75CA82CB
	mov r3, r2, lsr #0x1f
	smull r12, r8, lr, r2
	mov r8, r8, asr #0xe
	add r8, r3, r8
	add r3, r8, #0x2
	str r3, [r7, #0x84]
_020AB8F4:
	ldr r3, [r7, #0x84]
	cmp r3, #0x0
	bgt _020AB918
	ldr r3, [r7, #0x7c]
	sub r2, r2, r3
	add r2, r3, r2, asr #0x4
	str r2, [r7, #0x7c]
	ldr r2, [r7, #0x7c]
	str r2, [r7, #0x18]
_020AB918:
	ldr r3, [r7, #0x44]
	ldr r12, [r7, #0x4]
	ldr r2, [r7, #0x48]
	adds r1, r1, r3
	adc r0, r0, r2
	adds r1, r12, r1
	str r1, [r6, #0x46c]
	adc r0, r0, #0x0
	str r0, [r6, #0x470]
	bl OS_GetTick
	ldr r12, [r6, #0x46c]
	ldr r2, _020ABAF8 ; =0x00008B18
	ldr lr, [r6, #0x470]
	adds r6, r12, r2
	adc r3, lr, #0x0
	cmp r3, r1
	mov r3, #0x0
	cmpeq r6, r0
	movcc r0, r3
	ldmccia sp!, {r4-r8,pc}
_020AB968: ; 0x020AB968
	ldr r6, _020ABB04 ; =0x0007FD88
	adds r6, r0, r6
	adc r0, r1, r3
	cmp lr, r0
	cmpeq r12, r6
	movhi r0, r3
	ldmhiia sp!, {r4-r8,pc}
_020AB984: ; 0x020AB984
	ldr r0, [r7, #0x84]
	cmp r0, #0x0
	bgt _020ABAE0
	ldr r1, [r7, #0x7c]
	mov r0, #0x3
	mul lr, r1, r0
	ldr r6, _020ABB00 ; =0x75CA82CB
	ldr r12, [r7, #0x8c]
	smull r1, r0, r6, lr
	mov r0, r0, asr #0xe
	mov r1, lr, lsr #0x1f
	cmp lr, r12
	add r0, r1, r0
	bls _020AB9EC
	ldr r1, _020ABB08 ; =0x000134DF
	add r6, r0, #0x1
	mla r12, r6, r2, r1
	str r12, [r7, #0x8c]
	mla r1, r0, r2, r1
	ldr r2, [r7, #0x8c]
	ldr r0, _020ABB0C ; =0xFFFF2F5C
	add r0, r2, r0
	str r0, [r7, #0x88]
	str r1, [r7, #0x4]
	str r3, [r7, #0x90]
	b _020ABA50
_020AB9EC:
	ldr r1, [r7, #0x88]
	cmp lr, r1
	bge _020ABA50
	ldr r1, [r7, #0x90]
	add r1, r1, #0x1
	str r1, [r7, #0x90]
	ldr r1, [r7, #0x90]
	cmp r1, #0x46
	bls _020ABA50
	ldr r1, _020ABB08 ; =0x000134DF
	add r12, r0, #0x1
	mla lr, r12, r2, r1
	ldr r6, _020ABB10 ; =0xFFFFBA74
	str lr, [r7, #0x8c]
	mla r1, r0, r2, r6
	str r1, [r7, #0x88]
	ldr r1, [r7, #0x88]
	ldr r2, _020ABB08 ; =0x000134DF
	cmp r1, #0x0
	ldr r1, _020ABAF8 ; =0x00008B18
	strlt r3, [r7, #0x88]
	mla r1, r0, r1, r2
	mov r3, #0x0
	str r1, [r7, #0x4]
	str r3, [r7, #0x90]
_020ABA50:
	ldr r1, [r7, #0x4]
	ldr r0, _020ABB14 ; =0x00068520
	cmp r1, r0
	strhi r0, [r7, #0x4]
	ldr r0, [r7, #0x6c]
	cmp r0, #0x10
	addcc r0, r0, #0x1
	strcc r0, [r7, #0x6c]
	strcc r5, [r7, #0x74]
	strcc r5, [r7, #0x78]
	blo _020ABA98
	ldr r1, [r7, #0x74]
	mov r0, #0x1f
	mla r2, r1, r0, r5
	mov r0, r2, asr #0x4
	add r0, r2, r0, lsr #0x1b
	mov r0, r0, asr #0x5
	str r0, [r7, #0x74]
_020ABA98:
	ldr r2, [r7, #0x78]
	ldr r1, [r7, #0x74]
	ldr r0, _020ABB18 ; =0x00008701
	sub r1, r2, r1
	str r1, [r7, #0xc]
	ldr r1, [r7, #0xc]
	cmp r1, r0
	mvn r0, #0x8700
	movgt r4, #0x1
	cmp r1, r0
	ldrlt r0, [r7, #0x70]
	mvnlt r4, #0x0
	addlt r0, r0, #0x1
	strlt r0, [r7, #0x70]
	cmp r4, #0x0
	movne r0, #0x0
	strne r0, [r7, #0x6c]
	strne r0, [r7, #0x4c]
_020ABAE0:
	ldr r1, [r7, #0x84]
	mov r0, #0x1
	sub r1, r1, #0x1
	str r1, [r7, #0x84]
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020ABAF4: .word 0x00000464
_020ABAF8: .word 0x00008B18
_020ABAFC: .word 0x0000CC8D
_020ABB00: .word 0x75CA82CB
_020ABB04: .word 0x0007FD88
_020ABB08: .word 0x000134DF
_020ABB0C: .word 0xFFFF2F5C
_020ABB10: .word 0xFFFFBA74
_020ABB14: .word 0x00068520
_020ABB18: .word 0x00008701

	arm_func_start FUN_020ABB1C
FUN_020ABB1C:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrh r12, [r6, #0x68]
	mov r4, r2
	ldr r3, _020ABBE4 ; =0x00000BB8
	sub r2, r4, r12
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r5, r1
	cmp r2, r3
	bhs _020ABB60
	cmp r4, r12
	ldrcc r0, [r6, #0x60]
	addcc r0, r0, #0x10000
	strcc r0, [r6, #0x60]
	strh r4, [r6, #0x68]
	b _020ABBD0
_020ABB60:
	ldr r1, _020ABBE8 ; =0x0000FF9C
	cmp r2, r1
	bhi _020ABBAC
	ldr r1, [r6, #0x64]
	cmp r4, r1
	bne _020ABB94
	mov r1, r4
	bl FUN_020ABBEC
	sub r0, r4, #0x1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r0, [r6, #0x54]
	b _020ABBD0
_020ABB94:
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r0, [r6, #0x64]
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}
_020ABBAC:
	ldr r2, [r6, #0x60]
	ldr r0, [r6, #0x54]
	add r2, r4, r2
	add r0, r0, r1
	cmp r2, r0
	subhi r0, r2, #0x10000
	strhi r0, [r5, #0x18]
	movhi r0, #0x1
	ldmhiia sp!, {r4-r6,pc}
_020ABBD0:
	ldr r1, [r6, #0x60]
	mov r0, #0x1
	add r1, r4, r1
	str r1, [r5, #0x18]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020ABBE4: .word 0x00000BB8
_020ABBE8: .word 0x0000FF9C

	arm_func_start FUN_020ABBEC
FUN_020ABBEC: ; 0x020ABBEC
	ldr r2, _020ABC08 ; =0x00010001
	strh r1, [r0, #0x68]
	str r2, [r0, #0x64]
	mov r1, #0x0
	str r1, [r0, #0x60]
	str r1, [r0, #0x5c]
	bx lr
	.balign 4
_020ABC08: .word 0x00010001

	arm_func_start FUN_020ABC0C
FUN_020ABC0C: ; 0x020ABC0C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, [r5, #0x3c]
	mov r4, r1
	cmp r0, #0x0
	beq _020ABC2C
	bl FUN_020ACD90
_020ABC2C:
	str r4, [r5, #0x3c]
	ldr r0, [r5, #0x34]
	bl FUN_020AB444
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020ABC40
FUN_020ABC40: ; 0x020ABC40
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x3c]
	cmp r0, #0x0
	beq _020ABC60
	bl FUN_020ACD90
_020ABC58: ; 0x020ABC58
	mov r0, #0x0
	str r0, [r4, #0x3c]
_020ABC60:
	mvn r0, #0x0
	str r0, [r4, #0x38]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020ABC6C
FUN_020ABC6C: ; 0x020ABC6C
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r4, r2
	mov r1, #0x0
	mov r2, #0x28
	mov r6, r0
	bl MI_CpuFill8
	ldr r0, _020ABCF4 ; =0x000134DF
	mov r1, #0x0
	str r0, [r6, #0x4]
	str r1, [r6, #0x28]
	str r1, [r6, #0x2c]
	str r5, [r6, #0x34]
	str r4, [r6, #0x38]
	str r1, [r6, #0x7c]
	str r1, [r6, #0x80]
	str r1, [r6, #0x84]
	str r1, [r6, #0x88]
	str r0, [r6, #0x8c]
	str r1, [r6, #0x90]
	str r1, [r6, #0x4c]
	str r1, [r6, #0x44]
	str r1, [r6, #0x48]
	str r1, [r6, #0x6c]
	str r1, [r6, #0x70]
	str r1, [r6, #0x50]
	str r1, [r6, #0x54]
	str r1, [r6, #0x58]
	mov r0, #0x1
	str r0, [r6, #0x5c]
	str r1, [r6, #0x3c]
	str r1, [r6, #0x40]
	str r1, [r6, #0x30]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020ABCF4: .word 0x000134DF

	arm_func_start FUN_020ABCF8
FUN_020ABCF8: ; 0x020ABCF8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, _020ABE34 ; =0x021CCD20
	ldr r2, [r3, #0x10]
	cmp r2, #0x2
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {pc}
	ldrb r12, [r3, #0x1]
	ldrb r2, [r0, #0x8]
	cmp r12, r2
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {pc}
	ldrb r2, [r0, #0xa]
	cmp r2, #0x0
	beq _020ABD48
	cmp r2, #0x1
	beq _020ABDA4
	b _020ABE1C
_020ABD48:
	ldr r0, _020ABE38 ; =0x021CB824
	ldr r2, [r0, #0x2c]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x38]
	cmp r0, #0x5
	beq _020ABD74
	cmp r0, #0x2
	bne _020ABD80
_020ABD74:
	mov r0, #0x9
	str r0, [r1, #0x0]
	b _020ABD88
_020ABD80:
	mov r0, #0x5
	str r0, [r1, #0x0]
_020ABD88:
	ldr r0, _020ABE38 ; =0x021CB824
	mov r3, #0x0
	ldr r2, _020ABE3C ; =0x021CB850
	str r3, [r0, #0x2c]
	str r3, [r0, #0x38]
	str r2, [r1, #0x4]
	b _020ABE28
_020ABDA4:
	ldr r2, _020ABE38 ; =0x021CB824
	mov lr, #0x2
	str lr, [r2, #0x2c]
	ldrb r12, [r0, #0xb]
	ldrb r3, [r3, #0x0]
	cmp r12, r3
	bne _020ABDD8
	str lr, [r2, #0x38]
	mov r3, #0x7
	str r3, [r1, #0x0]
	ldr r3, [r0, #0xc]
	str r3, [r2, #0x34]
	b _020ABE04
_020ABDD8:
	mov r3, #0x3
	str r3, [r2, #0x38]
	mov r2, #0x6
	str r2, [r1, #0x0]
	ldrb r3, [r0, #0xb]
	cmp r3, #0x0
	movne r2, #0x1
	movne r3, r2, lsl r3
	ldr r2, _020ABE38 ; =0x021CB824
	moveq r3, #0x1
	str r3, [r2, #0x34]
_020ABE04:
	ldrb r3, [r0, #0xb]
	ldr r0, _020ABE38 ; =0x021CB824
	ldr r2, _020ABE3C ; =0x021CB850
	strb r3, [r0, #0x31]
	str r2, [r1, #0x4]
	b _020ABE28
_020ABE1C:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {pc}
_020ABE28:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020ABE34: .word 0x021CCD20
_020ABE38: .word 0x021CB824
_020ABE3C: .word 0x021CB850

	arm_func_start FUN_020ABE40
FUN_020ABE40: ; 0x020ABE40
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrb r0, [r5, #0x4]
	mov r4, r1
	cmp r0, #0xff
	bne _020ABE70
	ldrb r0, [r5, #0x6]
	cmp r0, #0x4
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
_020ABE70:
	ldrb r0, [r5, #0x8]
	bl FUN_020AC1E8
_020ABE78: ; 0x020ABE78
	cmp r0, #0x0
	beq _020ABEA4
	mov r1, #0x2
	str r1, [r4, #0x0]
	str r0, [r4, #0x4]
	mov r2, #0x0
	str r2, [r0, #0x0]
	bl FUN_020AC708
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,pc}
_020ABEA4:
	ldrb r1, [r5, #0x8]
	ldr r0, _020ABEC8 ; =0x021CB838
	bl FUN_020AC5A4
	ldr r0, _020ABEC8 ; =0x021CB838
	mov r1, #0x2
	bl FUN_020AC708
_020ABEBC: ; 0x020ABEBC
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020ABEC8: .word 0x021CB838

	arm_func_start FUN_020ABECC
FUN_020ABECC: ; 0x020ABECC
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020AC070 ; =0x021CB824
	mov r6, r0
	ldr r0, [r2, #0x2c]
	mov r5, r1
	cmp r0, #0x2
	bne _020ABF84
	ldrb r1, [r2, #0x30]
	ldrb r0, [r6, #0x8]
	cmp r1, r0
	bne _020ABF74
	ldr r0, _020AC074 ; =0x021CB850
	mov r1, r6
	bl FUN_020AC350
	mov r4, r0
	mvn r0, #0x2
	cmp r4, r0
	beq _020ABF48
	mvn r0, #0x1
	cmp r4, r0
	beq _020ABF30
	mvn r0, #0x0
	cmp r4, r0
	beq _020ABF48
	b _020ABF50
_020ABF30:
	mov r0, #0xc
	str r0, [r5, #0x0]
	mov r0, #0x0
	str r0, [r5, #0x4]
	mov r0, #0x1
	ldmia sp!, {r4-r6,pc}
_020ABF48:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}
_020ABF50:
	ldr r1, _020AC074 ; =0x021CB850
	mov r0, r6
	bl FUN_020AC4A0
	ldr r1, _020AC074 ; =0x021CB850
	str r0, [r5, #0x0]
	str r1, [r5, #0x4]
	ldr r0, [r5, #0x4]
	str r4, [r0, #0xc]
	b _020AC028
_020ABF74:
	mov r0, #0x1
	bl FUN_020AC5E8
_020ABF7C: ; 0x020ABF7C
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}
_020ABF84:
	ldrb r12, [r6, #0x8]
	cmp r12, #0x0
	movne r0, #0x1
	movne r1, r0, lsl r12
	ldr r0, _020AC078 ; =0x021CB818
	moveq r1, #0x1
	ldr r0, [r0, #0x0]
	ands r0, r0, r1
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020ABFAC: ; 0x020ABFAC
	ldr r2, _020AC070 ; =0x021CB824
	mov r4, #0x2
	mov r3, #0x0
	ldr r0, _020AC074 ; =0x021CB850
	mov r1, r6
	strb r12, [r2, #0x30]
	str r4, [r2, #0x2c]
	str r3, [r2, #0x38]
	bl FUN_020AC350
	mov r4, r0
	mvn r0, #0x2
	cmp r4, r0
	beq _020ABFF8
	mvn r0, #0x1
	cmp r4, r0
	beq _020ABFF8
	mvn r0, #0x0
	cmp r4, r0
	bne _020AC008
_020ABFF8:
	ldr r1, _020AC070 ; =0x021CB824
	mov r0, #0x0
	str r0, [r1, #0x2c]
	ldmia sp!, {r4-r6,pc}
_020AC008:
	ldr r1, _020AC074 ; =0x021CB850
	mov r0, r6
	bl FUN_020AC4A0
	ldr r1, _020AC074 ; =0x021CB850
	str r0, [r5, #0x0]
	str r1, [r5, #0x4]
	ldr r0, [r5, #0x4]
	str r4, [r0, #0xc]
_020AC028:
	ldr r0, [r5, #0x0]
	cmp r0, #0xa
	bne _020AC050
	mov r0, #0x1
	bl FUN_020AC5E8
	bl OS_GetTick
	ldr r2, _020AC07C ; =0x021CB81C
	str r0, [r2, #0x0]
	str r1, [r2, #0x4]
	b _020AC068
_020AC050:
	mov r0, #0x0
	bl FUN_020AC5E8
	ldr r0, _020AC07C ; =0x021CB81C
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
_020AC068:
	mov r0, #0x1
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020AC070: .word 0x021CB824
_020AC074: .word 0x021CB850
_020AC078: .word 0x021CB818
_020AC07C: .word 0x021CB81C

	arm_func_start FUN_020AC080
FUN_020AC080: ; 0x020AC080
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	ldrb r2, [r6, #0x4]
	mov r5, r1
	cmp r2, #0xff
	bne _020AC0C4
	ldrb r2, [r6, #0x6]
	cmp r2, #0x4
	bne _020AC0B4
	bl FUN_020ABCF8
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
_020AC0B4:
	cmp r2, #0x3
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
_020AC0C4:
	ldrb r0, [r6, #0x8]
	bl FUN_020AC1E8
	movs r4, r0
	beq _020AC154
	mov r1, r6
	bl FUN_020AC350
	mov r7, r0
	mvn r0, #0x1
	cmp r7, r0
	beq _020AC104
	mvn r0, #0x0
	cmp r7, r0
	bne _020AC124
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AC104:
	mov r0, #0xc
	str r0, [r5, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	add sp, sp, #0x4
	str r4, [r5, #0x4]
	mov r0, #0x1
	ldmia sp!, {r4-r7,pc}
_020AC124:
	mov r0, r6
	mov r1, r4
	bl FUN_020AC4A0
_020AC130: ; 0x020AC130
	str r0, [r5, #0x0]
	str r4, [r5, #0x4]
	str r7, [r4, #0xc]
	ldr r0, [r5, #0x0]
	add sp, sp, #0x4
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AC154:
	ldrb r0, [r6, #0x8]
	bl FUN_020AC790
	movs r7, r0
	bne _020AC188
	ldrb r1, [r6, #0x8]
	ldr r0, _020AC1E4 ; =0x021CB838
	bl FUN_020AC5A4
	ldr r0, _020AC1E4 ; =0x021CB838
	mov r1, #0x3
	bl FUN_020AC708
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AC188:
	mov r1, r6
	bl FUN_020AC350
	mov r4, r0
	add r0, r4, #0x2
	cmp r0, #0x1
	bhi _020AC1B4
	mov r0, r7
	bl FUN_020ACC84
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AC1B4:
	mov r0, r6
	mov r1, r7
	bl FUN_020AC4A0
_020AC1C0: ; 0x020AC1C0
	str r0, [r5, #0x0]
	str r7, [r5, #0x4]
	str r4, [r7, #0xc]
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020AC1E4: .word 0x021CB838

	arm_func_start FUN_020AC1E8
FUN_020AC1E8:
	ldr r1, _020AC25C ; =0x021CCD20
	ldr r2, _020AC260 ; =0x021CB824
	ldr r1, [r1, #0x10]
	ldr r3, [r2, #0x4]
	cmp r1, #0x2
	bne _020AC224
	ldr r1, [r2, #0x2c]
	cmp r1, #0x0
	beq _020AC21C
	ldrb r1, [r2, #0x30]
	cmp r1, r0
	ldreq r0, _020AC264 ; =0x021CB850
	bxeq lr
_020AC21C:
	mov r0, #0x0
	bx lr
_020AC224:
	cmp r3, #0x0
	beq _020AC254
_020AC22C:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _020AC248
	ldrb r1, [r3, #0x4]
	cmp r1, r0
	moveq r0, r3
	bxeq lr
_020AC248:
	ldr r3, [r3, #0x14]
	cmp r3, #0x0
	bne _020AC22C
_020AC254:
	mov r0, #0x0
	bx lr
	.balign 4
_020AC25C: .word 0x021CCD20
_020AC260: .word 0x021CB824
_020AC264: .word 0x021CB850

	arm_func_start FUN_020AC268
FUN_020AC268:
	ldrb r2, [r1, #0x4]
	ldrb r12, [r1, #0x6]
	cmp r2, #0x0
	addeq r12, r12, #0x5
	cmp r12, #0x0
	blt _020AC288
	cmp r12, #0xb
	blt _020AC28C
_020AC288:
	mvn r12, #0x0
_020AC28C:
	cmp r12, #0x0
	mvnlt r0, #0x0
	bxlt lr
	ldr r1, _020AC2F8 ; =0x021CCD20
	ldr r1, [r1, #0x10]
	cmp r1, #0x1
	ldrne r3, [r0, #0xc]
	ldrne r2, _020AC2FC ; =0x020FF788
	movne r1, #0xb
	mlane r1, r3, r1, r2
	ldrnesb r2, [r12, r1]
	bne _020AC2D0
	ldr r3, [r0, #0xc]
	ldr r2, _020AC300 ; =0x020FF744
	mov r1, #0xb
	mla r1, r3, r1, r2
	ldrsb r2, [r12, r1]
_020AC2D0:
	mvn r1, #0x0
	cmp r2, r1
	moveq r0, #0x1
	bxeq lr
	mvn r1, #0x1
	cmp r2, r1
	moveq r0, #0x0
	strne r2, [r0, #0xc]
	movne r0, #0x1
	bx lr
	.balign 4
_020AC2F8: .word 0x021CCD20
_020AC2FC: .word 0x020FF788
_020AC300: .word 0x020FF744

	arm_func_start FUN_020AC304
FUN_020AC304:
	ldr r1, _020AC34C ; =0x021CB824
	ldr r2, [r1, #0x4]
	cmp r2, #0x0
	beq _020AC344
_020AC314:
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	beq _020AC338
	ldr r1, [r2, #0xc]
	cmp r1, #0x2
	bne _020AC338
	cmp r0, r2
	movne r0, #0x0
	bxne lr
_020AC338:
	ldr r2, [r2, #0x14]
	cmp r2, #0x0
	bne _020AC314
_020AC344:
	mov r0, #0x1
	bx lr
	.balign 4
_020AC34C: .word 0x021CB824

	arm_func_start FUN_020AC350
FUN_020AC350: ; 0x020AC350
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldrb r2, [r1, #0x4]
	ldrb r3, [r1, #0x6]
	mov r4, r0
	cmp r2, #0x0
	addeq r3, r3, #0x5
	cmp r3, #0x0
	blt _020AC37C
	cmp r3, #0xb
	blt _020AC380
_020AC37C:
	mvn r3, #0x0
_020AC380:
	cmp r3, #0x0
	addlt sp, sp, #0x4
	mvnlt r0, #0x0
	ldmltia sp!, {r4-r5,pc}
_020AC390: ; 0x020AC390
	ldr r0, _020AC44C ; =0x021CCD20
	ldr r0, [r0, #0x10]
	cmp r0, #0x1
	ldrne r2, [r4, #0xc]
	ldrne r1, _020AC450 ; =0x020FF700
	movne r0, #0xb
	mlane r0, r2, r0, r1
	ldrnesb r5, [r3, r0]
	bne _020AC3C8
	ldr r2, [r4, #0xc]
	ldr r1, _020AC454 ; =0x020FF6BC
	mov r0, #0xb
	mla r0, r2, r0, r1
	ldrsb r5, [r3, r0]
_020AC3C8:
	mvn r0, #0x2
	cmp r5, r0
	beq _020AC41C
	mvn r0, #0x1
	cmp r5, r0
	beq _020AC3F8
	mvn r0, #0x0
	cmp r5, r0
	bne _020AC440
	add sp, sp, #0x4
	mov r0, r5
	ldmia sp!, {r4-r5,pc}
_020AC3F8:
	mov r0, r4
	mov r1, #0x1
	bl FUN_020AC708
	mov r1, #0x0
	str r1, [r4, #0xc]
	add sp, sp, #0x4
	mov r0, r5
	str r1, [r4, #0x0]
	ldmia sp!, {r4-r5,pc}
_020AC41C:
	mov r0, r4
	mov r1, #0x3
	bl FUN_020AC708
	mov r1, #0x0
	str r1, [r4, #0xc]
	add sp, sp, #0x4
	mov r0, r5
	str r1, [r4, #0x0]
	ldmia sp!, {r4-r5,pc}
_020AC440:
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AC44C: .word 0x021CCD20
_020AC450: .word 0x020FF700
_020AC454: .word 0x020FF6BC

	arm_func_start FUN_020AC458
FUN_020AC458:
	ldr ip, _020AC498 ; =0x5F564354
	mov r3, #0x10
	str r12, [r1, #0x0]
	strb r3, [r1, #0x5]
	ldr r3, _020AC49C ; =0x021CCD20
	strb r2, [r1, #0x6]
	ldrb r2, [r3, #0x0]
	strb r2, [r1, #0x8]
	ldrb r2, [r0, #0x4]
	mov r0, #0x0
	strb r2, [r1, #0x9]
	strb r0, [r1, #0xa]
	ldrb r2, [r3, #0x0]
	strb r2, [r1, #0xb]
	str r0, [r1, #0xc]
	bx lr
	.balign 4
_020AC498: .word 0x5F564354
_020AC49C: .word 0x021CCD20

	arm_func_start FUN_020AC4A0
FUN_020AC4A0:
	ldrb r2, [r0, #0xb]
	strb r2, [r1, #0x5]
	ldrb r2, [r0, #0x4]
	cmp r2, #0xff
	bne _020AC4E8
	ldrb r2, [r0, #0x6]
	cmp r2, #0x0
	bne _020AC4D8
	ldrb r3, [r1, #0x4]
	cmp r3, #0x0
	movne r2, #0x1
	movne r2, r2, lsl r3
	moveq r2, #0x1
	str r2, [r1, #0x8]
_020AC4D8:
	ldrb r1, [r0, #0x6]
	ldr r0, _020AC54C ; =0x020FF6AC
	ldrb r0, [r0, r1]
	bx lr
_020AC4E8:
	cmp r2, #0x0
	bne _020AC544
	ldrb r2, [r0, #0x6]
	cmp r2, #0x0
	bne _020AC538
	ldr r0, [r1, #0xc]
	cmp r0, #0x1
	bne _020AC528
	ldrb r2, [r1, #0x4]
	cmp r2, #0x0
	movne r0, #0x1
	movne r0, r0, lsl r2
	moveq r0, #0x1
	str r0, [r1, #0x8]
	mov r0, #0x7
	bx lr
_020AC528:
	cmp r0, #0x5
	moveq r0, #0x9
	movne r0, #0xc
	bx lr
_020AC538:
	ldr r0, _020AC550 ; =0x020FF6B4
	ldrb r0, [r0, r2]
	bx lr
_020AC544:
	mov r0, #0xc
	bx lr
	.balign 4
_020AC54C: .word 0x020FF6AC
_020AC550: .word 0x020FF6B4

	arm_func_start FUN_020AC554
FUN_020AC554:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrb r2, [r1, #0x4]
	cmp r2, #0xff
	bne _020AC57C
	ldrb r2, [r1, #0x6]
	cmp r2, #0x4
	bne _020AC57C
	bl FUN_020AC628
	b _020AC598
_020AC57C:
	ldrb r0, [r0, #0x4]
	mov r2, #0x10
	bl FUN_021EB044
_020AC588: ; 0x020AC588
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {pc}
_020AC598:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AC5A4
FUN_020AC5A4: ; 0x020AC5A4
	mov r12, r0
	mov r3, #0x6
	mov r2, #0x0
_020AC5B0:
	strb r2, [r12], #0x1
	strb r2, [r12], #0x1
	strb r2, [r12], #0x1
	strb r2, [r12], #0x1
	subs r3, r3, #0x1
	bne _020AC5B0
	ldr r2, _020AC5E4 ; =0x021CCD20
	mov r3, #0x0
	ldr r2, [r2, #0x10]
	str r2, [r0, #0x0]
	str r3, [r0, #0xc]
	strb r1, [r0, #0x4]
	bx lr
	.balign 4
_020AC5E4: .word 0x021CCD20

	arm_func_start FUN_020AC5E8
FUN_020AC5E8:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x10
	mov r4, r0
	mov r3, #0xff
	ldr r0, _020AC624 ; =0x021CB850
	add r1, sp, #0x0
	mov r2, #0x4
	strb r3, [sp, #0x4]
	bl FUN_020AC458
	ldr r0, _020AC624 ; =0x021CB850
	add r1, sp, #0x0
	strb r4, [sp, #0xa]
	bl FUN_020AC628
	add sp, sp, #0x10
	ldmia sp!, {r4,pc}
	.balign 4
_020AC624: .word 0x021CB850

	arm_func_start FUN_020AC628
FUN_020AC628: ; 0x020AC628
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r11, r0
	mov r10, r1
	mov r9, #0x0
	bl FUN_020AC6E4
	ldr r4, _020AC6DC ; =0x021CCD20
	ldr r5, _020AC6E0 ; =0x021CB818
	mov r8, r9
	mov r7, #0x1
	mov r6, #0x10
_020AC654:
	cmp r8, #0x0
	movne r1, r7, lsl r8
	ldr r0, [r5, #0x0]
	moveq r1, r7
	ands r0, r0, r1
	beq _020AC694
	ldrb r0, [r4, #0x0]
	cmp r8, r0
	beq _020AC694
	mov r0, r8
	mov r1, r10
	mov r2, r6
	strb r8, [r10, #0x9]
	bl FUN_021EB044
_020AC68C: ; 0x020AC68C
	cmp r0, #0x0
	addne r9, r9, #0x1
_020AC694:
	add r0, r8, #0x1
	and r8, r0, #0xff
	cmp r8, #0x20
	blo _020AC654
	ldrb r0, [r10, #0xa]
	cmp r0, #0x1
	ldreq r0, _020AC6E0 ; =0x021CB818
	ldreq r0, [r0, #0x0]
	streq r0, [r11, #0x8]
	beq _020AC6C8
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r11, #0x8]
_020AC6C8:
	cmp r9, #0x0
	mvneq r0, #0x3
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AC6DC: .word 0x021CCD20
_020AC6E0: .word 0x021CB818

	arm_func_start FUN_020AC6E4
FUN_020AC6E4: ; 0x020AC6E4
	ldrb r2, [r1, #0xa]
	cmp r2, #0x1
	ldreqb r2, [r0, #0x4]
	ldreq r0, _020AC704 ; =0x021CB818
	streqb r2, [r1, #0xb]
	ldreq r0, [r0, #0x0]
	streq r0, [r1, #0xc]
	bx lr
	.balign 4
_020AC704: .word 0x021CB818

	arm_func_start FUN_020AC708
FUN_020AC708:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x10
	add r2, sp, #0x0
	mov r3, #0x10
	mov r4, r0
	bl FUN_020ACAE0
_020AC720: ; 0x020AC720
	cmp r0, #0x0
	addne sp, sp, #0x10
	ldmneia sp!, {r4,pc}
_020AC72C: ; 0x020AC72C
	add r1, sp, #0x0
	mov r0, r4
	bl FUN_020AC554
_020AC738: ; 0x020AC738
	cmp r0, #0x0
	movne r0, #0x0
	mvneq r0, #0x3
	add sp, sp, #0x10
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020AC74C
FUN_020AC74C: ; 0x020AC74C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x10
	add r2, sp, #0x0
	mov r3, #0x10
	mov r4, r0
	bl FUN_020ACBD0
_020AC764: ; 0x020AC764
	cmp r0, #0x0
	addne sp, sp, #0x10
	ldmneia sp!, {r4,pc}
_020AC770: ; 0x020AC770
	add r1, sp, #0x0
	mov r0, r4
	bl FUN_020AC554
_020AC77C: ; 0x020AC77C
	cmp r0, #0x0
	movne r0, #0x0
	mvneq r0, #0x3
	add sp, sp, #0x10
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020AC790
FUN_020AC790: ; 0x020AC790
	stmdb sp!, {r4,lr}
	mov r1, r0
	cmp r1, #0x20
	movcs r0, #0x0
	ldmcsia sp!, {r4,pc}
_020AC7A4: ; 0x020AC7A4
	ldr r0, _020AC7F4 ; =0x021CCD20
	ldrb r0, [r0, #0x0]
	cmp r1, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_020AC7B8: ; 0x020AC7B8
	ldr r2, _020AC7F8 ; =0x021CB824
	ldr r4, [r2, #0x0]
	cmp r4, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_020AC7CC: ; 0x020AC7CC
	ldr r3, [r4, #0x14]
	mov r0, r4
	str r3, [r2, #0x0]
	bl FUN_020AC5A4
	ldr r1, _020AC7F8 ; =0x021CB824
	mov r0, r4
	ldr r2, [r1, #0x4]
	str r2, [r4, #0x14]
	str r4, [r1, #0x4]
	ldmia sp!, {r4,pc}
	.balign 4
_020AC7F4: .word 0x021CCD20
_020AC7F8: .word 0x021CB824

	arm_func_start FUN_020AC7FC
FUN_020AC7FC:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r2, #0x10
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {pc}
	ldrb r2, [r1, #0x8]
	cmp r2, r0
	bne _020AC834
	ldr r0, _020AC894 ; =0x021CCD20
	ldrb r12, [r1, #0x9]
	ldrb r2, [r0, #0x0]
	cmp r12, r2
	beq _020AC840
_020AC834:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {pc}
_020AC840:
	ldrb r2, [r1, #0x5]
	cmp r2, #0x10
	beq _020AC860
	mov r0, r1
	mov r1, r3
	bl FUN_020ABE40
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020AC860:
	ldr r0, [r0, #0xc]
	cmp r0, #0x0
	bne _020AC880
	mov r0, r1
	mov r1, r3
	bl FUN_020AC080
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020AC880:
	mov r0, r1
	mov r1, r3
	bl FUN_020ABECC
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AC894: .word 0x021CCD20

	arm_func_start FUN_020AC898
FUN_020AC898: ; 0x020AC898
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_GetTick
	ldr r2, _020AC950 ; =0x021CCD20
	ldr r3, [r2, #0x10]
	cmp r3, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
_020AC8B8: ; 0x020AC8B8
	ldr r2, [r2, #0xc]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020AC8C8: ; 0x020AC8C8
	ldr r3, _020AC954 ; =0x021CB81C
	mov r12, #0x0
	ldr r5, [r3, #0x4]
	ldr r4, [r3, #0x0]
	cmp r5, r12
	cmpeq r4, r12
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020AC8E8: ; 0x020AC8E8
	ldr r2, _020AC958 ; =0x02106490
	subs r4, r0, r4
	ldr lr, [r2, #0x0]
	ldr r0, [r2, #0x4]
	sbc r1, r1, r5
	cmp r1, r0
	cmpeq r4, lr
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r5,pc}
_020AC90C: ; 0x020AC90C
	ldr r1, _020AC95C ; =0x021CB824
	mov r0, r12
	str r12, [r3, #0x0]
	str r12, [r3, #0x4]
	str r12, [r1, #0x2c]
	str r12, [r1, #0x38]
	bl FUN_020AC5E8
	ldr r1, _020AC950 ; =0x021CCD20
	ldr r0, _020AC95C ; =0x021CB824
	ldr r3, [r1, #0x8]
	ldrb r0, [r0, #0x30]
	ldr r12, [r1, #0x4]
	ldr r2, _020AC960 ; =0x021CB850
	mov r1, #0x9
	blx r12
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AC950: .word 0x021CCD20
_020AC954: .word 0x021CB81C
_020AC958: .word 0x02106490
_020AC95C: .word 0x021CB824
_020AC960: .word 0x021CB850

	arm_func_start FUN_020AC964
FUN_020AC964: ; 0x020AC964
	ldr r0, _020AC978 ; =0x021CB824
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020AC978: .word 0x021CB824

	arm_func_start FUN_020AC97C
FUN_020AC97C:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020AC9A8
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	beq _020AC9A8
	cmp r1, #0x8
	bls _020AC9B4
_020AC9A8:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,pc}
_020AC9B4:
	ldr r1, _020ACA8C ; =0x021CB824
	mov r2, #0x18
	str r0, [r1, #0x0]
	ldr r3, [r4, #0x4]
	mov r1, #0x0
	mul r2, r3, r2
	bl MI_CpuFill8
	ldr r0, _020ACA90 ; =0x021CB850
	mov r1, #0x0
	mov r2, #0x18
	bl MI_CpuFill8
	ldr r0, _020ACA94 ; =0x021CB838
	mov r1, #0x0
	mov r2, #0x18
	bl MI_CpuFill8
	ldr r12, [r4, #0x4]
	mov lr, #0x0
	subs r0, r12, #0x1
	beq _020ACA34
	ldr r1, _020ACA8C ; =0x021CB824
	mov r5, lr
	mov r0, #0x18
_020ACA0C:
	ldr r2, [r1, #0x0]
	add lr, lr, #0x1
	mla r3, lr, r0, r2
	add r2, r2, r5
	str r3, [r2, #0x14]
	ldr r12, [r4, #0x4]
	add r5, r5, #0x18
	sub r2, r12, #0x1
	cmp lr, r2
	blo _020ACA0C
_020ACA34:
	ldr r3, _020ACA8C ; =0x021CB824
	mov r0, #0x18
	ldr r1, [r3, #0x0]
	mov r5, #0x0
	mla r0, r12, r0, r1
	str r5, [r0, #-0x4]
	ldr r2, _020ACA98 ; =0x021CB818
	ldr r1, _020ACA9C ; =0x021CB814
	ldr r0, _020ACAA0 ; =0x021CCD20
	ldr lr, _020ACAA4 ; =OS_GetTick
	ldr ip, _020ACAA8 ; =0x5D588B65
	ldr r4, _020ACAAC ; =0x00269EC3
	str r5, [r3, #0x4]
	str r5, [r2, #0x0]
	str r5, [r1, #0x0]
	str r5, [r0, #0x14]
	str lr, [r3, #0x8]
	str r12, [r3, #0xc]
	str r4, [r3, #0x10]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020ACA8C: .word 0x021CB824
_020ACA90: .word 0x021CB850
_020ACA94: .word 0x021CB838
_020ACA98: .word 0x021CB818
_020ACA9C: .word 0x021CB814
_020ACAA0: .word 0x021CCD20
_020ACAA4: .word OS_GetTick
_020ACAA8: .word 0x5D588B65
_020ACAAC: .word 0x00269EC3

	arm_func_start FUN_020ACAB0
FUN_020ACAB0: ; 0x020ACAB0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020ACADC ; =0x021CCD20
	ldr r2, [r2, #0x10]
	cmp r2, #0x2
	addeq sp, sp, #0x4
	mvneq r0, #0x2
	ldmeqia sp!, {pc}
	bl FUN_020AC708
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020ACADC: .word 0x021CCD20

	arm_func_start FUN_020ACAE0
FUN_020ACAE0:
	stmdb sp!, {r4-r6,lr}
	movs r5, r0
	mov r6, r1
	mov r4, r2
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020ACAF8: ; 0x020ACAF8
	cmp r3, #0x10
	mvncc r0, #0x0
	ldmccia sp!, {r4-r6,pc}
_020ACB04: ; 0x020ACB04
	cmp r6, #0x0
	blt _020ACB14
	cmp r6, #0x6
	blt _020ACB1C
_020ACB14:
	mvn r0, #0x2
	ldmia sp!, {r4-r6,pc}
_020ACB1C:
	mov r3, #0x0
	mov r1, r4
	and r2, r6, #0xff
	strb r3, [r4, #0x4]
	bl FUN_020AC458
_020ACB30: ; 0x020ACB30
	cmp r6, #0x0
	bne _020ACB80
	ldr r0, _020ACB9C ; =0x021CCD20
	ldr r0, [r0, #0x10]
	cmp r0, #0x1
	bne _020ACB68
	ldr r0, [r5, #0xc]
	cmp r0, #0x4
	bne _020ACB68
	mov r0, r5
	bl FUN_020AC304
_020ACB5C: ; 0x020ACB5C
	cmp r0, #0x0
	mvneq r0, #0x2
	ldmeqia sp!, {r4-r6,pc}
_020ACB68:
	ldrb r1, [r5, #0x4]
	cmp r1, #0x0
	movne r0, #0x1
	movne r0, r0, lsl r1
	moveq r0, #0x1
	str r0, [r5, #0x8]
_020ACB80:
	mov r0, r5
	mov r1, r4
	bl FUN_020AC268
_020ACB8C: ; 0x020ACB8C
	cmp r0, #0x0
	mvneq r0, #0x2
	movne r0, #0x0
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020ACB9C: .word 0x021CCD20

	arm_func_start FUN_020ACBA0
FUN_020ACBA0: ; 0x020ACBA0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020ACBCC ; =0x021CCD20
	ldr r2, [r2, #0x10]
	cmp r2, #0x2
	addeq sp, sp, #0x4
	mvneq r0, #0x2
	ldmeqia sp!, {pc}
	bl FUN_020AC74C
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020ACBCC: .word 0x021CCD20

	arm_func_start FUN_020ACBD0
FUN_020ACBD0:
	stmdb sp!, {r4-r6,lr}
	movs r5, r0
	mov r4, r1
	mov r6, r2
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020ACBE8: ; 0x020ACBE8
	cmp r3, #0x10
	mvncc r0, #0x0
	ldmccia sp!, {r4-r6,pc}
_020ACBF4: ; 0x020ACBF4
	ldr r1, _020ACC80 ; =0x021CCD20
	ldr r1, [r1, #0xc]
	cmp r1, #0x1
	mvneq r0, #0x2
	ldmeqia sp!, {r4-r6,pc}
_020ACC08: ; 0x020ACC08
	cmp r4, #0x0
	blt _020ACC18
	cmp r4, #0x5
	blt _020ACC20
_020ACC18:
	mvn r0, #0x2
	ldmia sp!, {r4-r6,pc}
_020ACC20:
	mov r3, #0xff
	mov r1, r6
	and r2, r4, #0xff
	strb r3, [r6, #0x4]
	bl FUN_020AC458
	mov r0, r5
	mov r1, r6
	bl FUN_020AC268
_020ACC40: ; 0x020ACC40
	cmp r0, #0x0
	mvneq r0, #0x2
	ldmeqia sp!, {r4-r6,pc}
_020ACC4C: ; 0x020ACC4C
	ldr r0, _020ACC80 ; =0x021CCD20
	ldr r0, [r0, #0x10]
	cmp r0, #0x1
	bne _020ACC78
	cmp r4, #0x0
	bne _020ACC78
	mov r0, r5
	bl FUN_020AC304
_020ACC6C: ; 0x020ACC6C
	cmp r0, #0x0
	mvneq r0, #0x2
	ldmeqia sp!, {r4-r6,pc}
_020ACC78:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020ACC80: .word 0x021CCD20

	arm_func_start FUN_020ACC84
FUN_020ACC84: ; 0x020ACC84
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020ACD48 ; =0x021CB824
	cmp r0, #0x0
	mov lr, #0x0
	addeq sp, sp, #0x4
	ldr r12, [r2, #0x4]
	moveq r0, lr
	ldmeqia sp!, {pc}
	ldr r1, _020ACD4C ; =0x021CCD20
	ldr r1, [r1, #0x10]
	cmp r1, #0x2
	bne _020ACCD0
	ldr r1, _020ACD50 ; =0x021CB850
	add sp, sp, #0x4
	cmp r0, r1
	streq lr, [r2, #0x2c]
	mov r0, #0x1
	ldmia sp!, {pc}
_020ACCD0:
	cmp r12, #0x0
	beq _020ACD3C
_020ACCD8:
	cmp r12, r0
	bne _020ACD2C
	mov r3, #0x0
	str r3, [r0, #0x0]
	cmp lr, #0x0
	ldrne r1, [r0, #0x14]
	strne r1, [lr, #0x14]
	bne _020ACD10
	ldr r2, [r12, #0x14]
	cmp r2, #0x0
	ldrne r1, _020ACD48 ; =0x021CB824
	strne r2, [r1, #0x4]
	ldreq r1, _020ACD48 ; =0x021CB824
	streq r3, [r1, #0x4]
_020ACD10:
	ldr r1, _020ACD48 ; =0x021CB824
	add sp, sp, #0x4
	ldr r2, [r1, #0x0]
	str r2, [r0, #0x14]
	str r0, [r1, #0x0]
	mov r0, #0x1
	ldmia sp!, {pc}
_020ACD2C:
	mov lr, r12
	ldr r12, [r12, #0x14]
	cmp r12, #0x0
	bne _020ACCD8
_020ACD3C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020ACD48: .word 0x021CB824
_020ACD4C: .word 0x021CCD20
_020ACD50: .word 0x021CB850

	arm_func_start FUN_020ACD54
FUN_020ACD54: ; 0x020ACD54
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020ACD8C ; =0x021CCD20
	ldr r1, [r1, #0x10]
	cmp r1, #0x0
	beq _020ACD74
	cmp r1, #0x2
	bne _020ACD80
_020ACD74:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {pc}
_020ACD80:
	bl FUN_020AC790
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020ACD8C: .word 0x021CCD20

	arm_func_start FUN_020ACD90
FUN_020ACD90:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _020ACDC0 ; =0x021CB86C
	ldr r2, _020ACDC4 ; =0x021CB868
	ldr r3, [r1, #0x0]
	str r0, [r2, #0x0]
	str r3, [r4, #0x0]
	ldr r0, [r2, #0x0]
	str r4, [r1, #0x0]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,pc}
	.balign 4
_020ACDC0: .word 0x021CB86C
_020ACDC4: .word 0x021CB868

	arm_func_start FUN_020ACDC8
FUN_020ACDC8: ; 0x020ACDC8
	stmdb sp!, {r4,lr}
	mov r4, #0x0
	bl OS_DisableInterrupts
	ldr r1, _020ACE08 ; =0x021CB86C
	ldr r2, _020ACE0C ; =0x021CB868
	ldr r3, [r1, #0x0]
	str r0, [r2, #0x0]
	cmp r3, #0x0
	ldrne r0, [r3, #0x0]
	movne r4, r3
	strne r0, [r1, #0x0]
	ldr r0, _020ACE0C ; =0x021CB868
	ldr r0, [r0, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,pc}
	.balign 4
_020ACE08: .word 0x021CB86C
_020ACE0C: .word 0x021CB868

	arm_func_start FUN_020ACE10
FUN_020ACE10:
	ldr r1, _020ACE28 ; =0x021CB86C
	mov r2, #0x0
	ldr r0, _020ACE2C ; =0x021CB870
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	bx lr
	.balign 4
_020ACE28: .word 0x021CB86C
_020ACE2C: .word 0x021CB870

	arm_func_start FUN_020ACE30
FUN_020ACE30:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r3, _020ACF00 ; =0xE525982B
	mov r2, r1
	umull r1, r4, r2, r3
	ldr r1, _020ACF04 ; =0x021CB870
	mov r4, r4, lsr #0xa
	str r0, [r1, #0x0]
	cmp r4, #0x4
	blo _020ACE60
	cmp r4, #0x48
	bls _020ACE6C
_020ACE60:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,pc}
_020ACE6C:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
_020ACE7C: ; 0x020ACE7C
	ands r3, r0, #0x1f
	movne r0, #0x0
	strne r0, [r1, #0x0]
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
_020ACE90: ; 0x020ACE90
	mov r1, r0
	mov r0, #0x0
	bl MIi_CpuClearFast
	subs r12, r4, #0x1
	mov r5, #0x0
	beq _020ACED0
	ldr r1, _020ACF04 ; =0x021CB870
	ldr r0, _020ACF08 ; =0x00000478
	mov lr, r5
_020ACEB4:
	ldr r3, [r1, #0x0]
	add r5, r5, #0x1
	mla r2, r5, r0, r3
	str r2, [r3, lr]
	cmp r5, r12
	add lr, lr, r0
	blo _020ACEB4
_020ACED0:
	ldr r1, _020ACF04 ; =0x021CB870
	ldr r0, _020ACF08 ; =0x00000478
	ldr r2, [r1, #0x0]
	mov r3, #0x0
	mla r0, r4, r0, r2
	str r3, [r0, #-0x478]
	ldr r2, [r1, #0x0]
	ldr r1, _020ACF0C ; =0x021CB86C
	mov r0, #0x1
	str r2, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020ACF00: .word 0xE525982B
_020ACF04: .word 0x021CB870
_020ACF08: .word 0x00000478
_020ACF0C: .word 0x021CB86C

	arm_func_start FUN_020ACF10
FUN_020ACF10: ; 0x020ACF10
	mov r2, #0xf
	mov r0, #0x44
	mul r1, r2, r0
	ldr r0, _020ACF30 ; =0x02106498
	ldr ip, _020ACF34 ; =FUN_020AD170
	str r2, [r0, #0x8]
	str r1, [r0, #0xc]
	bx r12
	.balign 4
_020ACF30: .word 0x02106498
_020ACF34: .word FUN_020AD170

	arm_func_start FUN_020ACF38
FUN_020ACF38: ; 0x020ACF38
	stmdb sp!, {r4,lr}
	ldr r3, _020AD124 ; =0x02106498
	mov r12, r1, lsr #0x8
	str r12, [r3, #0x4]
	cmp r2, #0x0
	strneb r12, [r2, #0x0]
	ldr r2, _020AD124 ; =0x02106498
	ldr r2, [r2, #0x0]
	cmp r2, #0x0
	bne _020AD05C
	mov r4, #0x0
	mov r12, r4
	ldr r3, _020AD128 ; =0x021CB880
_020ACF6C:
	ldr r2, [r3, r12, lsl #0x2]
	add r12, r12, #0x1
	cmp r12, #0x4
	add r4, r4, r2
	blt _020ACF6C
	ldr ip, _020AD12C ; =0x040002B0
	mov r3, #0x0
	ldr r2, _020AD130 ; =0x040002B8
	strh r3, [r12, #0x0]
	mov r3, r4, lsr #0x2
	str r3, [r2, #0x0]
_020ACF98:
	ldrh r2, [r12, #0x0]
	ands r2, r2, #0x8000
	bne _020ACF98
	ldr r2, _020AD134 ; =0x040002B4
	cmp r1, #0x0
	ldr r2, [r2, #0x0]
	beq _020AD038
	cmp r1, r2, lsl #0x1
	blo _020AD038
	mov r4, #0x0
	mov r3, r4
	ldr r2, _020AD128 ; =0x021CB880
_020ACFC8:
	ldr r1, [r2, r3, lsl #0x2]
	add r3, r3, #0x1
	cmp r3, #0x4
	add r4, r4, r1
	blo _020ACFC8
	ldr r3, _020AD12C ; =0x040002B0
	mov r2, #0x0
	ldr r1, _020AD130 ; =0x040002B8
	strh r2, [r3, #0x0]
	mov r2, r4, lsr #0x2
	str r2, [r1, #0x0]
_020ACFF4:
	ldrh r1, [r3, #0x0]
	ands r1, r1, #0x8000
	bne _020ACFF4
	ldr r2, _020AD134 ; =0x040002B4
	mov r1, #0x3
	ldr r2, [r2, #0x0]
	ldr r3, _020AD138 ; =0x021CB874
	mul r1, r2, r1
	mov lr, r1, lsr #0x1
	ldr r2, _020AD13C ; =0x021CB878
	mov r12, #0x0
	ldr r1, _020AD124 ; =0x02106498
	mov r4, #0x1
	str lr, [r3, #0x0]
	str r12, [r2, #0x0]
	str r4, [r1, #0x0]
	b _020AD03C
_020AD038:
	mov r4, #0x0
_020AD03C:
	ldr r1, _020AD13C ; =0x021CB878
	ldr r3, _020AD128 ; =0x021CB880
	ldr r12, [r1, #0x0]
	add r2, r12, #0x1
	and r2, r2, #0x3
	str r0, [r3, r12, lsl #0x2]
	str r2, [r1, #0x0]
	b _020AD11C
_020AD05C:
	ldr r1, _020AD13C ; =0x021CB878
	mov lr, #0x0
	ldr r12, [r1, #0x0]
	ldr r3, _020AD128 ; =0x021CB880
	add r2, r12, #0x1
	and r2, r2, #0x3
	mov r4, lr
	str r0, [r3, r12, lsl #0x2]
	str r2, [r1, #0x0]
_020AD080:
	ldr r0, [r3, r4, lsl #0x2]
	add r4, r4, #0x1
	cmp r4, #0x4
	add lr, lr, r0
	blt _020AD080
	ldr r2, _020AD12C ; =0x040002B0
	mov r1, #0x0
	ldr r0, _020AD130 ; =0x040002B8
	strh r1, [r2, #0x0]
	mov r1, lr, lsr #0x2
	str r1, [r0, #0x0]
_020AD0AC:
	ldrh r0, [r2, #0x0]
	ands r0, r0, #0x8000
	bne _020AD0AC
	ldr r1, _020AD134 ; =0x040002B4
	ldr r0, _020AD138 ; =0x021CB874
	ldr r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	cmp r1, r0
	bhi _020AD10C
	ldr r2, _020AD140 ; =0x021CB87C
	ldr r1, _020AD124 ; =0x02106498
	ldr r3, [r2, #0x0]
	ldr r0, [r1, #0x8]
	add r3, r3, #0x1
	str r3, [r2, #0x0]
	cmp r3, r0
	ble _020AD118
	ldr r0, _020AD13C ; =0x021CB878
	mov r3, #0x0
	str r3, [r0, #0x0]
	str r3, [r1, #0x0]
	str r3, [r2, #0x0]
	mov r0, #0x3
	ldmia sp!, {r4,pc}
_020AD10C:
	ldr r0, _020AD140 ; =0x021CB87C
	mov r1, #0x0
	str r1, [r0, #0x0]
_020AD118:
	mov r4, #0x2
_020AD11C:
	mov r0, r4
	ldmia sp!, {r4,pc}
	.balign 4
_020AD124: .word 0x02106498
_020AD128: .word 0x021CB880
_020AD12C: .word 0x040002B0
_020AD130: .word 0x040002B8
_020AD134: .word 0x040002B4
_020AD138: .word 0x021CB874
_020AD13C: .word 0x021CB878
_020AD140: .word 0x021CB87C

	arm_func_start FUN_020AD144
FUN_020AD144: ; 0x020AD144
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	movs r1, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, _020AD16C ; =0x02106498
	mov r2, #0x10
	bl MI_CpuCopy8
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AD16C: .word 0x02106498

	arm_func_start FUN_020AD170
FUN_020AD170:
	ldr r0, _020AD1B8 ; =0x021CB880
	mov r2, #0x0
	mov r1, #0x1000000
_020AD17C:
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, #0x4
	blt _020AD17C
	ldr r3, _020AD1BC ; =0x021CB878
	mov r12, #0x0
	ldr r1, _020AD1C0 ; =0x02106498
	ldr r2, _020AD1C4 ; =0x021CB874
	ldr r0, _020AD1C8 ; =0x021CB87C
	str r12, [r3, #0x0]
	str r12, [r2, #0x0]
	str r12, [r1, #0x0]
	str r12, [r1, #0x4]
	str r12, [r0, #0x0]
	bx lr
	.balign 4
_020AD1B8: .word 0x021CB880
_020AD1BC: .word 0x021CB878
_020AD1C0: .word 0x02106498
_020AD1C4: .word 0x021CB874
_020AD1C8: .word 0x021CB87C

	arm_func_start FUN_020AD1CC
FUN_020AD1CC: ; 0x020AD1CC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r12, r1
	mov r3, r2
	ldr r1, _020AD1F0 ; =0x021CB8D4
	mov r2, r12
	bl FUN_020AD1F4
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AD1F0: .word 0x021CB8D4

	arm_func_start FUN_020AD1F4
FUN_020AD1F4: ; 0x020AD1F4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r4, #0x0
	str r4, [sp, #0x0]
	str r4, [sp, #0x4]
	mov r9, r4
	movs r8, r2, lsr #0x1
	beq _020AD330
	mov r4, #0xc0000000
	ldr ip, _020AD420 ; =0x021CB8BC
	ldr r2, _020AD424 ; =0x021CB8A4
	str r4, [sp, #0xc]
_020AD224:
	ldr r4, _020AD428 ; =0x021CB894
	ldr lr, [r2, #0x10]
	ldr r7, [r4, #0x0]
	mov r4, r9, lsl #0x1
	ldrsh r10, [r1, r4]
	ldr r4, _020AD42C ; =0x021CB898
	mov r5, r7, lsl #0x1
	ldr r6, [r4, #0x0]
	ldr r4, _020AD430 ; =0x021CBD14
	ldr r11, [r2, #0x14]
	strh r10, [r4, r5]
	ldr r10, [r12, #0x10]
	mov r5, r6, lsl #0x1
	ldrsh r5, [r4, r5]
	ldr r4, [r12, #0x14]
	mul lr, r10, lr
	str r10, [sp, #0x8]
	str r10, [r12, #0x14]
	mla r10, r4, r11, lr
	ldr r4, [r12, #0xc]
	ldr r11, [r2, #0xc]
	str r4, [r12, #0x10]
	mla r10, r4, r11, r10
	ldr r4, [r12, #0x8]
	ldr r11, [r2, #0x8]
	str r4, [r12, #0xc]
	mla r10, r4, r11, r10
	ldr r4, [r12, #0x4]
	ldr r11, [r2, #0x4]
	str r4, [r12, #0x8]
	mla r10, r4, r11, r10
	ldr r4, [r2, #0x0]
	str r5, [r12, #0x0]
	mla r4, r5, r4, r10
	str r5, [r12, #0x4]
	ldr r5, _020AD434 ; =0x3FFF8000
	cmp r4, r5
	movgt r4, r5
	bgt _020AD2C8
	cmp r4, #0xc0000000
	ldrlt r4, [sp, #0xc]
_020AD2C8:
	ldr r5, _020AD438 ; =0x000007FF
	add r7, r7, #0x1
	and r7, r7, r5
	ldr r5, _020AD428 ; =0x021CB894
	add r6, r6, #0x1
	str r7, [r5, #0x0]
	ldr r5, _020AD438 ; =0x000007FF
	mov r7, r9, lsl #0x1
	and r6, r6, r5
	ldr r5, _020AD42C ; =0x021CB898
	mov r4, r4, asr #0xf
	str r6, [r5, #0x0]
	strh r4, [r1, r7]
	ldrsh r6, [r1, r7]
	ldrsh r4, [r0, r7]
	add r9, r9, #0x1
	mul r5, r6, r6
	strh r4, [r1, r7]
	ldr r4, [sp, #0x0]
	adds r4, r4, r5
	str r4, [sp, #0x0]
	ldr r4, [sp, #0x4]
	adc r4, r4, r5, asr #0x1f
	str r4, [sp, #0x4]
	cmp r9, r8
	blo _020AD224
_020AD330:
	ldr r5, _020AD43C ; =0x04000280
	mov r1, #0x1
	strh r1, [r5, #0x0]
	ldr r4, _020AD440 ; =0x04000290
	ldr r1, [sp, #0x0]
	ldr r2, _020AD444 ; =0x04000298
	str r1, [r4, #0x0]
	ldr r1, [sp, #0x4]
	str r1, [r4, #0x4]
	str r8, [r2, #0x0]
	mov r1, #0x0
	str r1, [r2, #0x4]
_020AD360:
	ldrh r1, [r5, #0x0]
	ands r1, r1, #0x8000
	bne _020AD360
	ldr r1, _020AD448 ; =0x040002A0
	ldr r2, _020AD44C ; =0x040002B0
	ldr r5, [r1, #0x0]
	mov r4, #0x0
	ldr r1, _020AD450 ; =0x040002B8
	strh r4, [r2, #0x0]
	str r5, [r1, #0x0]
_020AD388:
	ldrh r1, [r2, #0x0]
	ands r1, r1, #0x8000
	bne _020AD388
	ldr r2, _020AD454 ; =0x040002B4
	mov r1, #0x3
	ldr r4, [r2, #0x0]
	mov r2, r3, lsl #0x1
	mul r1, r4, r1
	cmp r2, r1
	ldrhi r0, _020AD458 ; =0x021CB890
	movhi r1, #0x0
	strhih r1, [r0, #0x0]
	addhi sp, sp, #0x14
	ldmhiia sp!, {r4-r11,pc}
_020AD3C0: ; 0x020AD3C0
	cmp r3, r4
	ldrlo r1, _020AD458 ; =0x021CB890
	movcc r2, #0x4
	strcch r2, [r1, #0x0]
	ldr r1, _020AD458 ; =0x021CB890
	mov r3, #0x0
	ldrsh r2, [r1, #0x0]
	cmp r2, #0x4
	addlt r2, r2, #0x1
	strlth r2, [r1, #0x0]
	cmp r8, #0x0
	addls sp, sp, #0x14
	ldmlsia sp!, {r4-r11,pc}
_020AD3F4: ; 0x020AD3F4
	ldr r1, _020AD458 ; =0x021CB890
	ldrsh r4, [r1, #0x0]
_020AD3FC:
	mov r2, r3, lsl #0x1
	ldrsh r1, [r0, r2]
	add r3, r3, #0x1
	cmp r3, r8
	mov r1, r1, asr r4
	strh r1, [r0, r2]
	blo _020AD3FC
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AD420: .word 0x021CB8BC
_020AD424: .word 0x021CB8A4
_020AD428: .word 0x021CB894
_020AD42C: .word 0x021CB898
_020AD430: .word 0x021CBD14
_020AD434: .word 0x3FFF8000
_020AD438: .word 0x000007FF
_020AD43C: .word 0x04000280
_020AD440: .word 0x04000290
_020AD444: .word 0x04000298
_020AD448: .word 0x040002A0
_020AD44C: .word 0x040002B0
_020AD450: .word 0x040002B8
_020AD454: .word 0x040002B4
_020AD458: .word 0x021CB890

	arm_func_start FUN_020AD45C
FUN_020AD45C: ; 0x020AD45C
	ldr ip, _020AD46C ; =MIi_CpuCopyFast
	mov r2, r1
	ldr r1, _020AD470 ; =0x021CB8D4
	bx r12
	.balign 4
_020AD46C: .word MIi_CpuCopyFast
_020AD470: .word 0x021CB8D4

	arm_func_start FUN_020AD474
FUN_020AD474: ; 0x020AD474
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020AD4E4 ; =0x021CB894
	mov r3, #0x0
	ldr r2, _020AD4E8 ; =0x0000019D
	ldr r0, _020AD4EC ; =0x021CB898
	ldr lr, _020AD4F0 ; =0x021064A8
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	ldr r0, _020AD4F4 ; =0x021CBD14
	mov r12, r3
_020AD4A0:
	mov r1, r3, lsl #0x1
	add r3, r3, #0x1
	strh r12, [r0, r1]
	cmp r3, #0x800
	blt _020AD4A0
	ldr r2, _020AD4F8 ; =0x021CB8BC
	ldr r0, _020AD4FC ; =0x021CB8A4
	mov r3, #0x0
_020AD4C0:
	str r3, [r2, r12, lsl #0x2]
	mov r1, r12, lsl #0x1
	ldrsh r1, [lr, r1]
	str r1, [r0, r12, lsl #0x2]
	add r12, r12, #0x1
	cmp r12, #0x6
	blt _020AD4C0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AD4E4: .word 0x021CB894
_020AD4E8: .word 0x0000019D
_020AD4EC: .word 0x021CB898
_020AD4F0: .word 0x021064A8
_020AD4F4: .word 0x021CBD14
_020AD4F8: .word 0x021CB8BC
_020AD4FC: .word 0x021CB8A4

	arm_func_start FUN_020AD500
FUN_020AD500: ; 0x020AD500
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldrsh r2, [r0, #0x0]
	ldr r6, _020AD5FC ; =0x00000E9F
	ldr sb, _020AD600 ; =0x021CB89C
	ldr r8, _020AD604 ; =0x021CB8A0
	smulbb r10, r2, r6
	ldr r3, [r9, #0x0]
	ldr r2, [r8, #0x0]
	ldr r7, _020AD608 ; =0x00000D3E
	add r3, r10, r3
	mla r5, r2, r7, r3
	mov r3, r5, asr #0xc
	mul r4, r3, r3
	str r5, [r8, #0x0]
	rsb r2, r10, #0x0
	mov r12, r1, lsr #0x1
	str r3, [r8, #0x0]
	str r2, [r9, #0x0]
	cmp r12, #0x1
	mov lr, r4, asr #0x1f
	mov r5, #0x1
	bls _020AD5AC
_020AD55C:
	mov r2, r5, lsl #0x1
	ldrsh r10, [r0, r2]
	ldr r3, [r8, #0x0]
	add r2, r0, r5, lsl #0x1
	strh r3, [r2, #-0x2]
	smulbb r11, r10, r6
	ldr r2, [r9, #0x0]
	rsb r10, r11, #0x0
	add r2, r11, r2
	mla r2, r3, r7, r2
	mov r3, r2, asr #0xc
	mul r11, r3, r3
	str r2, [r8, #0x0]
	adds r4, r4, r11
	str r10, [r9, #0x0]
	add r5, r5, #0x1
	adc lr, lr, r11, asr #0x1f
	str r3, [r8, #0x0]
	cmp r5, r12
	blo _020AD55C
_020AD5AC:
	bic r1, r1, #0x1
	add r0, r0, r1
	ldr r2, _020AD60C ; =0x04000280
	strh r3, [r0, #-0x2]
	mov r0, #0x1
	ldr r1, _020AD610 ; =0x04000290
	strh r0, [r2, #0x0]
	str r4, [r1, #0x0]
	ldr r0, _020AD614 ; =0x04000298
	str lr, [r1, #0x4]
	str r12, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
_020AD5E0:
	ldrh r0, [r2, #0x0]
	ands r0, r0, #0x8000
	bne _020AD5E0
	ldr r0, _020AD618 ; =0x040002A0
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AD5FC: .word 0x00000E9F
_020AD600: .word 0x021CB89C
_020AD604: .word 0x021CB8A0
_020AD608: .word 0x00000D3E
_020AD60C: .word 0x04000280
_020AD610: .word 0x04000290
_020AD614: .word 0x04000298
_020AD618: .word 0x040002A0

	arm_func_start FUN_020AD61C
FUN_020AD61C:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs lr, r3, lsr #0x1
	mov r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
_020AD634: ; 0x020AD634
	mov r3, #0x8000
	ldr ip, _020AD720 ; =0x00007FFF
	rsb r3, r3, #0x0
_020AD640:
	mov r5, r4, lsl #0x1
	ldrsh r6, [r0, r5]
	ldrsh r5, [r1, r5]
	add r6, r6, r5
	cmp r6, r12
	movgt r6, r12
	bgt _020AD664
	cmp r6, r3
	movlt r6, r3
_020AD664:
	mov r5, r4, lsl #0x1
	add r7, r4, #0x1
	strh r6, [r2, r5]
	mov r5, r7, lsl #0x1
	ldrsh r6, [r0, r5]
	ldrsh r5, [r1, r5]
	add r6, r6, r5
	cmp r6, r12
	movgt r6, r12
	bgt _020AD694
	cmp r6, r3
	movlt r6, r3
_020AD694:
	mov r5, r7, lsl #0x1
	add r7, r4, #0x2
	strh r6, [r2, r5]
	mov r5, r7, lsl #0x1
	ldrsh r6, [r0, r5]
	ldrsh r5, [r1, r5]
	add r6, r6, r5
	cmp r6, r12
	movgt r6, r12
	bgt _020AD6CC
	mov r5, #0x8000
	rsb r5, r5, #0x0
	cmp r6, r5
	movlt r6, r3
_020AD6CC:
	mov r5, r7, lsl #0x1
	add r7, r4, #0x3
	strh r6, [r2, r5]
	mov r5, r7, lsl #0x1
	ldrsh r6, [r0, r5]
	ldrsh r5, [r1, r5]
	add r6, r6, r5
	cmp r6, r12
	movgt r6, r12
	bgt _020AD704
	mov r5, #0x8000
	rsb r5, r5, #0x0
	cmp r6, r5
	movlt r6, r3
_020AD704:
	mov r5, r7, lsl #0x1
	add r4, r4, #0x4
	strh r6, [r2, r5]
	cmp r4, lr
	blo _020AD640
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020AD720: .word 0x00007FFF

	arm_func_start FUN_020AD724
FUN_020AD724:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs r6, r1
	mov r7, r0
	mov r5, r2
	mov r4, r3
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
_020AD748: ; 0x020AD748
	ldr r1, [r6, #0x0]
	ldr r0, _020AD824 ; =0x5F564354
	cmp r1, r0
	addne sp, sp, #0x4
	movne r0, #0x2
	ldmneia sp!, {r4-r7,pc}
_020AD760: ; 0x020AD760
	ldr r0, _020AD828 ; =0x021CCD20
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	beq _020AD780
	ldr r0, _020AD82C ; =0x021CCD1C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020AD78C
_020AD780:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AD78C:
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r0, [r4, #0x4]
	bl OS_GetTick
	ldrb r3, [r6, #0x4]
	and r2, r3, #0xf0
	cmp r2, #0x40
	bne _020AD7E0
	ldr r2, _020AD830 ; =0x021CCD18
	mov r3, r0
	ldr r4, [r2, #0x0]
	mov r0, r7
	add r4, r4, #0x1
	str r4, [r2, #0x0]
	str r1, [sp, #0x0]
	mov r1, r6
	mov r2, r5
	bl FUN_020AA2A0
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AD7E0:
	cmp r3, #0x0
	beq _020AD7F0
	cmp r3, #0xff
	bne _020AD818
_020AD7F0:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, r4
	bl FUN_020AC7FC
_020AD804: ; 0x020AD804
	cmp r0, #0x0
	movne r0, #0x1
	add sp, sp, #0x4
	moveq r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AD818:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020AD824: .word 0x5F564354
_020AD828: .word 0x021CCD20
_020AD82C: .word 0x021CCD1C
_020AD830: .word 0x021CCD18

	arm_func_start FUN_020AD834
FUN_020AD834: ; 0x020AD834
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	add r3, sp, #0x0
	mov r4, r0
	bl FUN_020AD724
_020AD848: ; 0x020AD848
	cmp r0, #0x0
	beq _020AD898
	cmp r0, #0x1
	beq _020AD864
	cmp r0, #0x2
	beq _020AD88C
	b _020AD898
_020AD864:
	ldr r0, _020AD8A4 ; =0x021CCD20
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	ldr r3, [r0, #0x8]
	ldr r12, [r0, #0x4]
	mov r0, r4
	blx r12
	add sp, sp, #0x8
	mov r0, #0x1
	ldmia sp!, {r4,pc}
_020AD88C:
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020AD898:
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4,pc}
	.balign 4
_020AD8A4: .word 0x021CCD20

	arm_func_start FUN_020AD8A8
FUN_020AD8A8: ; 0x020AD8A8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020AD8FC ; =0x021CCD1C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, _020AD900 ; =0x021CCD14
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	ands r0, r1, #0xf
	bne _020AD8E0
	bl FUN_020AC898
_020AD8E0:
	bl FUN_020AA0A4
_020AD8E4: ; 0x020AD8E4
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	bl FUN_020AA1CC
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AD8FC: .word 0x021CCD1C
_020AD900: .word 0x021CCD14

	arm_func_start FUN_020AD904
FUN_020AD904: ; 0x020AD904
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020AAF44
	bl FUN_020AC964
	bl FUN_020ACE10
	ldr r1, _020AD934 ; =0x021CCD20
	mov r2, #0x0
	ldr r0, _020AD938 ; =0x021CCD1C
	str r2, [r1, #0x10]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AD934: .word 0x021CCD20
_020AD938: .word 0x021CCD1C

	arm_func_start FUN_020AD93C
FUN_020AD93C: ; 0x020AD93C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _020ADA78 ; =0x02000C1C
	bl OSi_ReferSymbol
_020AD94C: ; 0x020AD94C
	cmp r4, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_020AD958: ; 0x020AD958
	ldr r0, _020ADA7C ; =0x021CCD1C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	movne r0, #0x1
	ldmneia sp!, {r4,pc}
_020AD96C: ; 0x020AD96C
	ldr r0, [r4, #0x8]
	cmp r0, #0x1
	beq _020AD98C
	cmp r0, #0x2
	beq _020AD98C
	cmp r0, #0x3
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
_020AD98C:
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_020AD99C: ; 0x020AD99C
	ldr r2, [r4, #0x10]
	cmp r2, #0x0
	beq _020AD9B4
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	bne _020AD9BC
_020AD9B4:
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020AD9BC:
	mov r1, r2, lsr #0x1f
	rsb r0, r1, r2, lsl #0x1b
	adds r0, r1, r0, ror #0x1b
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
_020AD9D0: ; 0x020AD9D0
	ldr r0, _020ADA80 ; =0x021CCD20
	mov r1, #0x0
	mov r2, #0x18
	bl MI_CpuFill8
	ldr r2, [r4, #0x18]
	ldr r1, _020ADA80 ; =0x021CCD20
	mov r0, #0x0
	str r2, [r1, #0x4]
	ldr r2, [r4, #0x1c]
	str r2, [r1, #0x8]
	ldr r2, [r4, #0x8]
	str r0, [r1, #0xc]
	str r2, [r1, #0x10]
	ldrb r2, [r4, #0xc]
	cmp r2, #0x20
	ldmcsia sp!, {r4,pc}
_020ADA10: ; 0x020ADA10
	strb r2, [r1, #0x0]
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	bl FUN_020ACE30
_020ADA20: ; 0x020ADA20
	cmp r0, #0x0
	bne _020ADA34
	bl FUN_020ACE10
_020ADA2C: ; 0x020ADA2C
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020ADA34:
	mov r0, r4
	bl FUN_020AC97C
_020ADA3C: ; 0x020ADA3C
	cmp r0, #0x0
	bne _020ADA50
	bl FUN_020ACE10
_020ADA48: ; 0x020ADA48
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020ADA50:
	bl FUN_020AAF58
_020ADA54: ; 0x020ADA54
	cmp r0, #0x0
	ldrne r1, _020ADA7C ; =0x021CCD1C
	movne r0, #0x1
	strne r0, [r1, #0x0]
	ldmneia sp!, {r4,pc}
_020ADA68: ; 0x020ADA68
	bl FUN_020AC964
	bl FUN_020ACE10
_020ADA70: ; 0x020ADA70
	mov r0, #0x0
	ldmia sp!, {r4,pc}
	.balign 4
_020ADA78: .word 0x02000C1C
_020ADA7C: .word 0x021CCD1C
_020ADA80: .word 0x021CCD20

	arm_func_start FUN_020ADA84
FUN_020ADA84: ; 0x020ADA84
	cmp r1, #0x0
	ldreq r0, [r0, #0x4]
	ldrneh r0, [r0, #0xa]
	ldrne r0, [r1, r0]
	bx lr

	arm_func_start FUN_020ADA98
FUN_020ADA98: ; 0x020ADA98
	cmp r1, #0x0
	ldreq r0, [r0, #0x0]
	ldrneh r0, [r0, #0xa]
	addne r0, r1, r0
	ldrne r0, [r0, #0x4]
	bx lr

	arm_func_start FUN_020ADAB0
FUN_020ADAB0: ; 0x020ADAB0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r12, [r0, #0xa]
	ldr r3, [r1, r12]
	add lr, r1, r12
	cmp r3, #0x0
	ldreq r1, [lr, #0x4]
	streq r1, [r0, #0x0]
	ldrne r2, [lr, #0x4]
	addne r1, r3, r12
	strne r2, [r1, #0x4]
	ldr r3, [lr, #0x4]
	cmp r3, #0x0
	ldreq r1, [lr, #0x0]
	streq r1, [r0, #0x4]
	ldrneh r1, [r0, #0xa]
	ldrne r2, [lr, #0x0]
	strne r2, [r3, r1]
	mov r1, #0x0
	str r1, [lr, #0x0]
	str r1, [lr, #0x4]
	ldrh r1, [r0, #0x8]
	sub r1, r1, #0x1
	strh r1, [r0, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020ADB18
FUN_020ADB18: ; 0x020ADB18
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x0
	bne _020ADB38
	mov r1, r2
	bl FUN_020ADBE8
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020ADB38:
	ldr r3, [r0, #0x0]
	cmp r1, r3
	bne _020ADB54
	mov r1, r2
	bl FUN_020ADB8C
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020ADB54:
	ldrh lr, [r0, #0xa]
	ldr r3, [r1, lr]
	add r12, r2, lr
	str r3, [r2, lr]
	str r1, [r12, #0x4]
	add r3, r3, lr
	str r2, [r3, #0x4]
	ldrh r3, [r0, #0xa]
	str r2, [r1, r3]
	ldrh r1, [r0, #0x8]
	add r1, r1, #0x1
	strh r1, [r0, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020ADB8C
FUN_020ADB8C: ; 0x020ADB8C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	bne _020ADBAC
	bl FUN_020ADC48
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020ADBAC:
	ldrh r3, [r0, #0xa]
	mov r2, #0x0
	str r2, [r1, r3]
	ldr r2, [r0, #0x0]
	add r3, r1, r3
	str r2, [r3, #0x4]
	ldrh r2, [r0, #0xa]
	ldr r3, [r0, #0x0]
	str r1, [r3, r2]
	str r1, [r0, #0x0]
	ldrh r1, [r0, #0x8]
	add r1, r1, #0x1
	strh r1, [r0, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020ADBE8
FUN_020ADBE8: ; 0x020ADBE8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	bne _020ADC08
	bl FUN_020ADC48
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020ADC08:
	ldrh r12, [r0, #0xa]
	ldr r3, [r0, #0x4]
	mov r2, #0x0
	str r3, [r1, r12]
	add r3, r1, r12
	str r2, [r3, #0x4]
	ldrh r2, [r0, #0xa]
	ldr r3, [r0, #0x4]
	add r2, r3, r2
	str r1, [r2, #0x4]
	str r1, [r0, #0x4]
	ldrh r1, [r0, #0x8]
	add r1, r1, #0x1
	strh r1, [r0, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020ADC48
FUN_020ADC48: ; 0x020ADC48
	ldrh r3, [r0, #0xa]
	mov r2, #0x0
	add r12, r1, r3
	str r2, [r12, #0x4]
	str r2, [r1, r3]
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	ldrh r1, [r0, #0x8]
	add r1, r1, #0x1
	strh r1, [r0, #0x8]
	bx lr

	arm_func_start FUN_020ADC74
FUN_020ADC74: ; 0x020ADC74
	mov r2, #0x0
	str r2, [r0, #0x0]
	str r2, [r0, #0x4]
	strh r2, [r0, #0x8]
	strh r1, [r0, #0xa]
	bx lr

	arm_func_start FUN_020ADC8C
FUN_020ADC8C: ; 0x020ADC8C
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020ADD30
	mov r1, r4
	bl FUN_020ADAB0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020ADCA4
FUN_020ADCA4:
	stmdb sp!, {r4,lr}
	mov r4, r0
	str r1, [r4, #0x0]
	str r2, [r4, #0x18]
	str r3, [r4, #0x1c]
	mov r0, #0x0
	str r0, [r4, #0x20]
	ldr r1, [r4, #0x20]
	ldrh r0, [sp, #0x8]
	bic r1, r1, #0xff
	str r1, [r4, #0x20]
	ldr r1, [r4, #0x20]
	and r0, r0, #0xff
	orr r2, r1, r0
	add r0, r4, #0xc
	mov r1, #0x4
	str r2, [r4, #0x20]
	bl FUN_020ADC74
	ldr r0, _020ADD28 ; =0x021CCD38
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020ADD14
	ldr r0, _020ADD2C ; =0x021CCD3C
	mov r1, #0x4
	bl FUN_020ADC74
	ldr r0, _020ADD28 ; =0x021CCD38
	mov r1, #0x1
	str r1, [r0, #0x0]
_020ADD14:
	mov r0, r4
	bl FUN_020ADD30
	mov r1, r4
	bl FUN_020ADBE8
	ldmia sp!, {r4,pc}
	.balign 4
_020ADD28: .word 0x021CCD38
_020ADD2C: .word 0x021CCD3C

	arm_func_start FUN_020ADD30
FUN_020ADD30: ; 0x020ADD30
	stmdb sp!, {r4,lr}
	ldr r4, _020ADD54 ; =0x021CCD3C
	mov r1, r0
	mov r0, r4
	bl FUN_020ADD58
_020ADD44: ; 0x020ADD44
	cmp r0, #0x0
	addne r4, r0, #0xc
	mov r0, r4
	ldmia sp!, {r4,pc}
	.balign 4
_020ADD54: .word 0x021CCD3C

	arm_func_start FUN_020ADD58
FUN_020ADD58:
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r1, #0x0
	mov r6, r0
	bl FUN_020ADA98
	movs r4, r0
	beq _020ADDB8
_020ADD74:
	ldr r0, [r4, #0x18]
	cmp r0, r5
	bhi _020ADDA4
	ldr r0, [r4, #0x1c]
	cmp r5, r0
	bhs _020ADDA4
	mov r1, r5
	add r0, r4, #0xc
	bl FUN_020ADD58
_020ADD98: ; 0x020ADD98
	cmp r0, #0x0
	moveq r0, r4
	ldmia sp!, {r4-r6,pc}
_020ADDA4:
	mov r0, r6
	mov r1, r4
	bl FUN_020ADA98
	movs r4, r0
	bne _020ADD74
_020ADDB8:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020ADDC0
FUN_020ADDC0: ; 0x020ADDC0
	ldr r0, [r0, #-0xc]
	bx lr

	arm_func_start FUN_020ADDC8
FUN_020ADDC8: ; 0x020ADDC8
	ldr r2, [r0, #0x24]
	mov r0, #0x0
	cmp r2, #0x0
	bxeq lr
_020ADDD8:
	ldr r1, [r2, #0x4]
	ldr r2, [r2, #0xc]
	add r0, r0, r1
	cmp r2, #0x0
	bne _020ADDD8
	bx lr

	arm_func_start FUN_020ADDF0
FUN_020ADDF0: ; 0x020ADDF0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	sub r4, r1, #0x10
	add r5, r0, #0x24
	add r0, sp, #0x0
	mov r1, r4
	bl FUN_020AE528
	mov r1, r4
	add r0, r5, #0x8
	bl FUN_020AE500
	add r1, sp, #0x0
	mov r0, r5
	bl FUN_020AE02C
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020ADE2C
FUN_020ADE2C: ; 0x020ADE2C
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x10
	mov r4, r1
	mov r10, r2
	sub r6, r4, #0x10
	add r1, r10, #0x3
	mov r5, r0
	ldr r8, [r6, #0x4]
	bic r10, r1, #0x3
	cmp r10, r8
	add r7, r5, #0x24
	addeq sp, sp, #0x10
	moveq r0, r10
	ldmeqia sp!, {r4-r10,pc}
_020ADE64: ; 0x020ADE64
	cmp r10, r8
	bls _020ADF60
	ldr r9, [r7, #0x0]
	add r0, r6, #0x10
	cmp r9, #0x0
	add r0, r8, r0
	beq _020ADE94
_020ADE80:
	cmp r9, r0
	beq _020ADE94
	ldr r9, [r9, #0xc]
	cmp r9, #0x0
	bne _020ADE80
_020ADE94:
	cmp r9, #0x0
	beq _020ADEB0
	ldr r0, [r9, #0x4]
	add r1, r8, #0x10
	add r0, r1, r0
	cmp r10, r0
	bls _020ADEBC
_020ADEB0:
	add sp, sp, #0x10
	mov r0, #0x0
	ldmia sp!, {r4-r10,pc}
_020ADEBC:
	add r0, sp, #0x0
	mov r1, r9
	bl FUN_020AE528
	mov r0, r7
	mov r1, r9
	bl FUN_020AE500
	ldr r2, [sp, #0x4]
	add r3, r10, r4
	ldr r9, [sp, #0x0]
	sub r1, r2, r3
	str r3, [sp, #0x0]
	cmp r1, #0x10
	strcc r2, [sp, #0x0]
	mov r8, r0
	ldr r0, [sp, #0x0]
	sub r0, r0, r4
	str r0, [r6, #0x4]
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	sub r0, r1, r0
	cmp r0, #0x10
	blo _020ADF30
	ldr r1, _020ADF9C ; =0x00004652
	add r0, sp, #0x0
	bl FUN_020AE4A0
	mov r1, r0
	mov r0, r7
	mov r2, r8
	bl FUN_020AE4D0
_020ADF30:
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #0x0]
	and r0, r0, #0xff
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	sub r2, r1, r9
	ands r0, r0, #0x1
	beq _020ADF90
	mov r1, r9
	mov r0, #0x0
	bl MIi_CpuClear32
	b _020ADF90
_020ADF60:
	add r0, r10, r4
	str r0, [sp, #0x8]
	ldr r1, [r6, #0x4]
	add r0, r6, #0x10
	add r0, r1, r0
	str r0, [sp, #0xc]
	add r1, sp, #0x8
	mov r0, r7
	str r10, [r6, #0x4]
	bl FUN_020AE02C
_020ADF88: ; 0x020ADF88
	cmp r0, #0x0
	streq r8, [r6, #0x4]
_020ADF90:
	ldr r0, [r6, #0x4]
	add sp, sp, #0x10
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020ADF9C: .word 0x00004652

	arm_func_start tempName_NNS_FndAllocFromExpHeapEx
tempName_NNS_FndAllocFromExpHeapEx: ; 0x020ADFA0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x0
	moveq r1, #0x1
	add r1, r1, #0x3
	cmp r2, #0x0
	bic r1, r1, #0x3
	blt _020ADFCC
	bl FUN_020AE1D8
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020ADFCC:
	rsb r2, r2, #0x0
	bl FUN_020AE11C
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start thunk_FUN_020adc8c
thunk_FUN_020adc8c: ; 0x020ADFDC
	ldr ip, _020ADFE4 ; =FUN_020ADC8C
	bx r12
	.balign 4
_020ADFE4: .word FUN_020ADC8C

	arm_func_start tempName_NNS_FndCreateExpHeapEx
tempName_NNS_FndCreateExpHeapEx: ; 0x020ADFE8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	add r1, r1, r0
	add r0, r0, #0x3
	bic r1, r1, #0x3
	bic r0, r0, #0x3
	cmp r0, r1
	bhi _020AE014
	sub r3, r1, r0
	cmp r3, #0x4c
	bhs _020AE020
_020AE014:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {pc}
_020AE020:
	bl FUN_020AE420
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AE02C
FUN_020AE02C:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r1
	ldr r2, [r5, #0x0]
	ldr r1, [r5, #0x4]
	mov r6, r0
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [r6, #0x0]
	mov r4, #0x0
	cmp r1, #0x0
	beq _020AE0A0
	ldr r0, [r5, #0x0]
_020AE060:
	cmp r1, r0
	movcc r4, r1
	blo _020AE094
	ldr r0, [r5, #0x4]
	cmp r1, r0
	bne _020AE0A0
	ldr r2, [r1, #0x4]
	add r0, r1, #0x10
	add r2, r2, r0
	mov r0, r6
	str r2, [sp, #0x4]
	bl FUN_020AE500
	b _020AE0A0
_020AE094:
	ldr r1, [r1, #0xc]
	cmp r1, #0x0
	bne _020AE060
_020AE0A0:
	cmp r4, #0x0
	beq _020AE0D4
	ldr r2, [r4, #0x4]
	add r1, r4, #0x10
	ldr r0, [r5, #0x0]
	add r1, r2, r1
	cmp r1, r0
	bne _020AE0D4
	mov r0, r6
	mov r1, r4
	str r4, [sp, #0x0]
	bl FUN_020AE500
	mov r4, r0
_020AE0D4:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	sub r0, r1, r0
	cmp r0, #0x10
	addcc sp, sp, #0x8
	movcc r0, #0x0
	ldmccia sp!, {r4-r6,pc}
_020AE0F0: ; 0x020AE0F0
	ldr r1, _020AE118 ; =0x00004652
	add r0, sp, #0x0
	bl FUN_020AE4A0
	mov r1, r0
	mov r0, r6
	mov r2, r4
	bl FUN_020AE4D0
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020AE118: .word 0x00004652

	arm_func_start FUN_020AE11C
FUN_020AE11C: ; 0x020AE11C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	add r0, r0, #0x24
	ldrh r4, [r0, #0x12]
	mov r3, r1
	mvn lr, #0x0
	and r1, r4, #0x1
	mov r1, r1, lsl #0x10
	movs r1, r1, lsr #0x10
	moveq r5, #0x1
	mov r1, #0x0
	ldr r4, [r0, #0x4]
	movne r5, #0x0
	mov r12, r1
	cmp r4, #0x0
	beq _020AE1B0
	sub r2, r2, #0x1
	mvn r2, r2
_020AE164:
	ldr r8, [r4, #0x4]
	add r9, r4, #0x10
	add r6, r8, r9
	sub r6, r6, r3
	and r7, r2, r6
	subs r6, r7, r9
	bmi _020AE1A4
	cmp lr, r8
	bls _020AE1A4
	mov r1, r4
	mov lr, r8
	mov r12, r7
	cmp r5, #0x0
	bne _020AE1B0
	cmp r8, r3
	beq _020AE1B0
_020AE1A4:
	ldr r4, [r4, #0x8]
	cmp r4, #0x0
	bne _020AE164
_020AE1B0:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
_020AE1C0: ; 0x020AE1C0
	mov r4, #0x1
	mov r2, r12
	str r4, [sp, #0x0]
	bl FUN_020AE298
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}

	arm_func_start FUN_020AE1D8
FUN_020AE1D8: ; 0x020AE1D8
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	add r0, r0, #0x24
	ldrh r4, [r0, #0x12]
	mov r3, r1
	ldr r5, [r0, #0x0]
	and r1, r4, #0x1
	mov r1, r1, lsl #0x10
	movs r1, r1, lsr #0x10
	moveq r6, #0x1
	mov r1, #0x0
	movne r6, #0x0
	mov lr, r1
	cmp r5, #0x0
	mvn r4, #0x0
	beq _020AE270
	sub r12, r2, #0x1
	mvn r2, r12
_020AE220:
	add r8, r5, #0x10
	add r7, r12, r8
	and r9, r2, r7
	sub r7, r9, r8
	ldr r8, [r5, #0x4]
	add r7, r3, r7
	cmp r8, r7
	blo _020AE264
	cmp r4, r8
	bls _020AE264
	mov r1, r5
	mov r4, r8
	mov lr, r9
	cmp r6, #0x0
	bne _020AE270
	cmp r8, r3
	beq _020AE270
_020AE264:
	ldr r5, [r5, #0xc]
	cmp r5, #0x0
	bne _020AE220
_020AE270:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
_020AE280: ; 0x020AE280
	mov r4, #0x0
	mov r2, lr
	str r4, [sp, #0x0]
	bl FUN_020AE298
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}

	arm_func_start FUN_020AE298
FUN_020AE298: ; 0x020AE298
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x18
	mov r7, r0
	add r0, sp, #0x0
	mov r8, r1
	mov r6, r2
	mov r5, r3
	bl FUN_020AE528
	ldr r3, [sp, #0x4]
	sub r4, r6, #0x10
	add r2, r5, r6
	mov r0, r7
	mov r1, r8
	str r4, [sp, #0x4]
	str r3, [sp, #0xc]
	str r2, [sp, #0x8]
	bl FUN_020AE500
	ldr r2, [sp, #0x0]
	ldr r1, [sp, #0x4]
	mov r5, r0
	sub r0, r1, r2
	cmp r0, #0x10
	strcc r2, [sp, #0x4]
	blo _020AE318
	ldr r1, _020AE418 ; =0x00004652
	add r0, sp, #0x0
	bl FUN_020AE4A0
	mov r1, r0
	mov r0, r7
	mov r2, r5
	bl FUN_020AE4D0
	mov r5, r0
_020AE318:
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x8]
	sub r0, r1, r0
	cmp r0, #0x10
	strcc r1, [sp, #0x8]
	blo _020AE34C
	ldr r1, _020AE418 ; =0x00004652
	add r0, sp, #0x8
	bl FUN_020AE4A0
	mov r1, r0
	mov r0, r7
	mov r2, r5
	bl FUN_020AE4D0
_020AE34C:
	ldr r0, [r7, #-0x4]
	ldr r1, [sp, #0x4]
	and r0, r0, #0xff
	mov r0, r0, lsl #0x10
	ldr r2, [sp, #0x8]
	mov r0, r0, lsr #0x10
	sub r2, r2, r1
	ands r0, r0, #0x1
	beq _020AE378
	mov r0, #0x0
	bl MIi_CpuClear32
_020AE378:
	ldr r2, [sp, #0x8]
	ldr r1, _020AE41C ; =0x00005544
	add r0, sp, #0x10
	str r4, [sp, #0x10]
	str r2, [sp, #0x14]
	bl FUN_020AE4A0
	mov r1, r0
	ldrh r3, [r1, #0x2]
	ldrh r2, [sp, #0x30]
	add r0, r7, #0x8
	bic r3, r3, #0x8000
	strh r3, [r1, #0x2]
	ldrh r3, [r1, #0x2]
	and r2, r2, #0x1
	orr r2, r3, r2, lsl #0xf
	strh r2, [r1, #0x2]
	ldrh r2, [r1, #0x2]
	ldr r3, [sp, #0x4]
	bic r2, r2, #0x7f00
	strh r2, [r1, #0x2]
	sub r2, r1, r3
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	ldrh r3, [r1, #0x2]
	and r2, r2, #0x7f
	orr r2, r3, r2, lsl #0x8
	strh r2, [r1, #0x2]
	ldrh r2, [r1, #0x2]
	ldrh r3, [r7, #0x10]
	bic r2, r2, #0xff
	strh r2, [r1, #0x2]
	ldrh r2, [r1, #0x2]
	and r3, r3, #0xff
	orr r2, r2, r3
	strh r2, [r1, #0x2]
	ldr r2, [r7, #0xc]
	bl FUN_020AE4D0
	mov r0, r6
	add sp, sp, #0x18
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020AE418: .word 0x00004652
_020AE41C: .word 0x00005544

	arm_func_start FUN_020AE420
FUN_020AE420: ; 0x020AE420
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	mov r3, r1
	add r4, r5, #0x24
	str r2, [sp, #0x0]
	ldr r1, _020AE498 ; =0x45585048
	add r2, r4, #0x14
	bl FUN_020ADCA4
_020AE444: ; 0x020AE444
	mov r0, #0x0
	strh r0, [r4, #0x10]
	strh r0, [r4, #0x12]
	ldrh r2, [r4, #0x12]
	ldr r1, _020AE49C ; =0x00004652
	add r0, sp, #0x4
	bic r2, r2, #0x1
	strh r2, [r4, #0x12]
	ldr r2, [r5, #0x18]
	str r2, [sp, #0x4]
	ldr r2, [r5, #0x1c]
	str r2, [sp, #0x8]
	bl FUN_020AE4A0
	str r0, [r5, #0x24]
	str r0, [r4, #0x4]
	mov r1, #0x0
	str r1, [r4, #0x8]
	mov r0, r5
	str r1, [r4, #0xc]
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AE498: .word 0x45585048
_020AE49C: .word 0x00004652

	arm_func_start FUN_020AE4A0
FUN_020AE4A0: ; 0x020AE4A0
	ldr r3, [r0, #0x0]
	mov r2, #0x0
	strh r1, [r3, #0x0]
	strh r2, [r3, #0x2]
	ldr r1, [r0, #0x4]
	add r0, r3, #0x10
	sub r0, r1, r0
	str r0, [r3, #0x4]
	str r2, [r3, #0x8]
	mov r0, r3
	str r2, [r3, #0xc]
	bx lr

	arm_func_start FUN_020AE4D0
FUN_020AE4D0: ; 0x020AE4D0
	str r2, [r1, #0x8]
	cmp r2, #0x0
	ldrne r3, [r2, #0xc]
	strne r1, [r2, #0xc]
	ldreq r3, [r0, #0x0]
	streq r1, [r0, #0x0]
	str r3, [r1, #0xc]
	cmp r3, #0x0
	strne r1, [r3, #0x8]
	streq r1, [r0, #0x4]
	mov r0, r1
	bx lr

	arm_func_start FUN_020AE500
FUN_020AE500: ; 0x020AE500
	ldr r2, [r1, #0x8]
	ldr r1, [r1, #0xc]
	cmp r2, #0x0
	strne r1, [r2, #0xc]
	streq r1, [r0, #0x0]
	cmp r1, #0x0
	strne r2, [r1, #0x8]
	streq r2, [r0, #0x4]
	mov r0, r2
	bx lr

	arm_func_start FUN_020AE528
FUN_020AE528: ; 0x020AE528
	ldrh r2, [r1, #0x2]
	add r3, r1, #0x10
	mov r2, r2, asr #0x8
	and r2, r2, #0x7f
	mov r2, r2, lsl #0x10
	sub r2, r1, r2, lsr #0x10
	str r2, [r0, #0x0]
	ldr r1, [r1, #0x4]
	add r1, r1, r3
	str r1, [r0, #0x4]
	bx lr

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
_020AE5D0: ; 0x020AE5D0
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020AE5DC: ; 0x020AE5DC
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
_020AE628: ; 0x020AE628
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
_020AE744: ; 0x020AE744
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
_020AE7AC: ; 0x020AE7AC
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

	arm_func_start FUN_020AE82C
FUN_020AE82C: ; 0x020AE82C
	ldr ip, _020AE848 ; =0x020FF7CC
	mov r3, #0x0
	str r12, [r0, #0x0]
	str r1, [r0, #0x4]
	str r2, [r0, #0x8]
	str r3, [r0, #0xc]
	bx lr
	.balign 4
_020AE848: .word 0x020FF7CC

	arm_func_start FUN_020AE84C
FUN_020AE84C: ; 0x020AE84C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x0]
	ldr r2, [r2, #0x4]
	blx r2
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AE868
FUN_020AE868: ; 0x020AE868
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x0]
	ldr r2, [r2, #0x0]
	blx r2
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AE884
FUN_020AE884: ; 0x020AE884
	ldr ip, _020AE890 ; =FUN_020ADDF0
	ldr r0, [r0, #0x4]
	bx r12
	.balign 4
_020AE890: .word FUN_020ADDF0

	arm_func_start FUN_020AE894
FUN_020AE894: ; 0x020AE894
	ldr ip, _020AE8A8 ; =tempName_NNS_FndAllocFromExpHeapEx
	mov r2, r0
	ldr r0, [r2, #0x4]
	ldr r2, [r2, #0x8]
	bx r12
	.balign 4
_020AE8A8: .word tempName_NNS_FndAllocFromExpHeapEx

	arm_func_start FUN_020AE8AC
FUN_020AE8AC: ; 0x020AE8AC
	mvn r0, #0x0
	bx lr

	arm_func_start FUN_020AE8B4
FUN_020AE8B4: ; 0x020AE8B4
	mov r0, #0x0
	bx lr

	arm_func_start FUN_020AE8BC
FUN_020AE8BC: ; 0x020AE8BC
	mvn r0, #0x0
	bx lr

	arm_func_start FUN_020AE8C4
FUN_020AE8C4: ; 0x020AE8C4
	mov r0, #0x0
	bx lr

	arm_func_start FUN_020AE8CC
FUN_020AE8CC: ; 0x020AE8CC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, #0x0
	ldr r3, _020AE914 ; =0x021064E4
	mov r12, lr
	mov r2, #0x1
_020AE8E4:
	ldr r1, [r0, r12, lsl #0x2]
	add lr, lr, #0x1
	str r1, [r3, #0x0]
	ldr r1, [r0, r2, lsl #0x2]
	cmp lr, #0x5
	str r1, [r3, #0x4]
	add r12, r12, #0x2
	add r3, r3, #0x18
	add r2, r2, #0x2
	blt _020AE8E4
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AE914: .word 0x021064E4

	arm_func_start FUN_020AE918
FUN_020AE918: ; 0x020AE918
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, #0x0
	ldr ip, _020AE960 ; =0x021064E4
	mov r3, lr
	mov r2, #0x1
_020AE930:
	ldr r1, [r12, #0x0]
	add lr, lr, #0x1
	str r1, [r0, r3, lsl #0x2]
	ldr r1, [r12, #0x4]
	cmp lr, #0x5
	str r1, [r0, r2, lsl #0x2]
	add r12, r12, #0x18
	add r3, r3, #0x2
	add r2, r2, #0x2
	blt _020AE930
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AE960: .word 0x021064E4

	arm_func_start FUN_020AE964
FUN_020AE964: ; 0x020AE964
	mov r0, #0x0
	bx lr

	arm_func_start FUN_020AE96C
FUN_020AE96C: ; 0x020AE96C
	stmdb sp!, {r4-r10,lr}
	cmp r0, #0x0
	moveq r7, #0x10
	addne r0, r0, #0xf
	bicne r7, r0, #0xf
	ldr r0, _020AEADC ; =0x0007FFF0
	cmp r7, r0
	movcs r0, #0x0
	ldmcsia sp!, {r4-r10,pc}
_020AE990: ; 0x020AE990
	cmp r1, #0x0
	beq _020AEA5C
	mov lr, r7, lsr #0x1
	mov r6, #0x0
	ldr r2, _020AEAE0 ; =0x02106514
	ldr r3, _020AEAE4 ; =0x021064FC
	ldr ip, _020AEAE8 ; =0x021064C8
	mov r0, r6
_020AE9B0:
	ldr r5, [r12, r6, lsl #0x2]
	ldr r4, [r5, #0x8]
	cmp r4, #0x0
	beq _020AEA48
	ldr r9, [r5, #0x4]
	ldr r4, [r5, #0x0]
	sub r4, r9, r4
	cmp r4, r7
	blo _020AEA48
	ldrh r4, [r5, #0x10]
	cmp r4, #0x0
	beq _020AE9EC
	cmp r4, #0x3
	beq _020AE9F4
	b _020AE9FC
_020AE9EC:
	mov r4, r3
	b _020AEA00
_020AE9F4:
	mov r4, r2
	b _020AEA00
_020AE9FC:
	mov r4, r0
_020AEA00:
	ldr r9, [r4, #0x8]
	cmp r9, #0x0
	beq _020AEA48
	ldr r10, [r4, #0x4]
	ldr r9, [r4, #0x0]
	sub r9, r10, r9
	cmp r9, lr
	blo _020AEA48
	ldr r3, [r5, #0x0]
	mov r0, #0x1
	add r2, r3, r7
	str r2, [r5, #0x0]
	ldr r2, [r4, #0x0]
	add r2, r2, lr
	str r2, [r4, #0x0]
	ldr r2, [r5, #0x14]
	add r8, r3, r2
	b _020AEAB8
_020AEA48:
	add r6, r6, #0x1
	cmp r6, #0x2
	blt _020AE9B0
	mov r0, #0x0
	b _020AEAB8
_020AEA5C:
	ldr r3, _020AEAEC ; =0x021064D0
	mov r5, #0x0
_020AEA64:
	ldr r4, [r3, r5, lsl #0x2]
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _020AEAA8
	ldr r2, [r4, #0x4]
	ldr r0, [r4, #0x0]
	sub r0, r2, r0
	cmp r0, r7
	blo _020AEAA8
	ldr r2, [r4, #0x4]
	mov r0, #0x1
	sub r2, r2, r7
	str r2, [r4, #0x4]
	ldr r3, [r4, #0x4]
	ldr r2, [r4, #0x14]
	add r8, r3, r2
	b _020AEAB8
_020AEAA8:
	add r5, r5, #0x1
	cmp r5, #0x5
	blt _020AEA64
	mov r0, #0x0
_020AEAB8:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r10,pc}
_020AEAC4: ; 0x020AEAC4
	ldr r0, _020AEAF0 ; =0x0000FFFF
	mov r2, r7, lsr #0x4
	and r0, r0, r8, lsr #0x3
	orr r0, r0, r2, lsl #0x10
	orr r0, r0, r1, lsl #0x1f
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020AEADC: .word 0x0007FFF0
_020AEAE0: .word 0x02106514
_020AEAE4: .word 0x021064FC
_020AEAE8: .word 0x021064C8
_020AEAEC: .word 0x021064D0
_020AEAF0: .word 0x0000FFFF

	arm_func_start FUN_020AEAF4
FUN_020AEAF4:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r0, _020AEB68 ; =0x021CCD48
	mov r6, #0x0
	ldrh r7, [r0, #0x0]
	ldr r5, _020AEB6C ; =0x021064E4
	mov lr, r6
	cmp r7, #0x1
	addhi r7, r7, #0x1
	mov r1, r6
	mov r3, r6
	mov r4, #0x1
	mov r0, #0x20000
	mov r2, #0x10000
_020AEB2C:
	cmp r6, r7
	strlt r4, [r5, #0x8]
	strge lr, [r5, #0x8]
	ldr r12, [r5, #0xc]
	add r6, r6, #0x1
	cmp r12, #0x0
	strne r3, [r5, #0x0]
	strne r2, [r5, #0x4]
	streq r1, [r5, #0x0]
	streq r0, [r5, #0x4]
	cmp r6, #0x5
	add r5, r5, #0x18
	blt _020AEB2C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020AEB68: .word 0x021CCD48
_020AEB6C: .word 0x021064E4

	arm_func_start FUN_020AEB70
FUN_020AEB70: ; 0x020AEB70
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	cmp r5, #0x2
	bhi _020AEBA8
	mov r12, #0x1
	mov r0, #0x4
	mov r1, #0x3
	mov r2, #0x2
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl FUN_020AEC10
	b _020AEBC4
_020AEBA8:
	mov r12, #0x1
	mov r0, #0x4
	mov r1, #0x3
	mov r2, #0x0
	mov r3, #0x2
	str r12, [sp, #0x0]
	bl FUN_020AEC10
_020AEBC4:
	ldr r0, _020AEBFC ; =0x021CCD48
	strh r5, [r0, #0x0]
	bl FUN_020AEAF4
_020AEBD0: ; 0x020AEBD0
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020AEBDC: ; 0x020AEBDC
	ldr r3, _020AEC00 ; =FUN_020AE96C
	ldr r1, _020AEC04 ; =0x021064B8
	ldr r2, _020AEC08 ; =FUN_020AE964
	ldr r0, _020AEC0C ; =0x021064BC
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AEBFC: .word 0x021CCD48
_020AEC00: .word FUN_020AE96C
_020AEC04: .word 0x021064B8
_020AEC08: .word FUN_020AE964
_020AEC0C: .word 0x021064BC

	arm_func_start FUN_020AEC10
FUN_020AEC10: ; 0x020AEC10
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr lr, [sp, #0x18]
	ldr r6, _020AEC58 ; =0x021064E4
	mov r12, #0x18
	mla r7, r0, r12, r6
	ldr r0, _020AEC5C ; =0x021064D0
	mla r5, r1, r12, r6
	mla r4, r2, r12, r6
	mla r2, r3, r12, r6
	mla r1, lr, r12, r6
	str r7, [r0, #0x0]
	str r5, [r0, #0x4]
	str r4, [r0, #0x8]
	str r2, [r0, #0xc]
	str r1, [r0, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020AEC58: .word 0x021064E4
_020AEC5C: .word 0x021064D0

	arm_func_start FUN_020AEC60
FUN_020AEC60:
	ldr r0, _020AEC78 ; =0x021CCD4C
	mov r2, #0x0
	ldr r1, [r0, #0x8]
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
	bx lr
	.balign 4
_020AEC78: .word 0x021CCD4C

	arm_func_start FUN_020AEC7C
FUN_020AEC7C: ; 0x020AEC7C
	ldr r2, [r0, #0x0]
	ldr r1, _020AEC94 ; =0x021CCD4C
	str r2, [r1, #0x0]
	ldr r0, [r0, #0x4]
	str r0, [r1, #0x4]
	bx lr
	.balign 4
_020AEC94: .word 0x021CCD4C

	arm_func_start FUN_020AEC98
FUN_020AEC98: ; 0x020AEC98
	ldr r1, _020AECB0 ; =0x021CCD4C
	ldr r2, [r1, #0x0]
	str r2, [r0, #0x0]
	ldr r1, [r1, #0x4]
	str r1, [r0, #0x4]
	bx lr
	.balign 4
_020AECB0: .word 0x021CCD4C

	arm_func_start FUN_020AECB4
FUN_020AECB4: ; 0x020AECB4
	mov r0, #0x0
	bx lr

	arm_func_start FUN_020AECBC
FUN_020AECBC: ; 0x020AECBC
	stmdb sp!, {r4,lr}
	cmp r0, #0x0
	moveq r0, #0x8
	addne r0, r0, #0x7
	ldr ip, _020AEDE8 ; =0x0007FFF8
	bicne r0, r0, #0x7
	cmp r0, r12
	mov r3, #0x0
	movcs r0, #0x0
	ldmcsia sp!, {r4,pc}
_020AECE4: ; 0x020AECE4
	cmp r2, #0x1
	bne _020AED64
	ldr r2, _020AEDEC ; =0x021CCD4C
	cmp r1, #0x0
	ldr r12, [r2, #0x0]
	andne r2, r12, #0x7
	rsbne r2, r2, #0x8
	andne r4, r2, #0x7
	andeq r2, r12, #0xf
	rsbeq r2, r2, #0x10
	andeq r4, r2, #0xf
	ldr r2, _020AEDEC ; =0x021CCD4C
	add lr, r0, r4
	ldr r2, [r2, #0x4]
	sub r2, r2, r12
	cmp r2, lr
	blo _020AED5C
	cmp r1, #0x0
	add r1, r12, lr
	beq _020AED40
	cmp r1, #0x10000
	movhi r12, #0x0
	bhi _020AEDCC
_020AED40:
	ldr r1, _020AEDEC ; =0x021CCD4C
	add r3, r12, r4
	ldr r2, [r1, #0x0]
	mov r12, #0x1
	add r2, r2, lr
	str r2, [r1, #0x0]
	b _020AEDCC
_020AED5C:
	mov r12, #0x0
	b _020AEDCC
_020AED64:
	ldr r2, _020AEDEC ; =0x021CCD4C
	ldr r12, [r2, #0x4]
	cmp r12, r0
	blo _020AEDC8
	sub r2, r12, r0
	cmp r1, #0x0
	andne r4, r2, #0x7
	andeq r4, r2, #0xf
	ldr r2, _020AEDEC ; =0x021CCD4C
	add lr, r0, r4
	ldr r2, [r2, #0x0]
	sub r2, r12, r2
	cmp r2, lr
	blo _020AEDC8
	cmp r1, #0x0
	beq _020AEDB0
	cmp r12, #0x10000
	movhi r12, #0x0
	bhi _020AEDCC
_020AEDB0:
	ldr r1, _020AEDEC ; =0x021CCD4C
	mov r12, #0x1
	ldr r2, [r1, #0x4]
	sub r3, r2, lr
	str r3, [r1, #0x4]
	b _020AEDCC
_020AEDC8:
	mov r12, #0x0
_020AEDCC:
	cmp r12, #0x0
	ldrne r1, _020AEDF0 ; =0x0000FFFF
	movne r2, r0, lsr #0x3
	andne r0, r1, r3, lsr #0x3
	orrne r0, r0, r2, lsl #0x10
	moveq r0, #0x0
	ldmia sp!, {r4,pc}
	.balign 4
_020AEDE8: .word 0x0007FFF8
_020AEDEC: .word 0x021CCD4C
_020AEDF0: .word 0x0000FFFF

	arm_func_start FUN_020AEDF4
FUN_020AEDF4: ; 0x020AEDF4
	stmdb sp!, {r4,lr}
	ldr r2, _020AEE2C ; =0x021CCD4C
	mov r4, r1
	str r0, [r2, #0x8]
	bl FUN_020AEC60
_020AEE08: ; 0x020AEE08
	cmp r4, #0x0
	ldmeqia sp!, {r4,pc}
_020AEE10: ; 0x020AEE10
	ldr r3, _020AEE30 ; =FUN_020AECBC
	ldr r1, _020AEE34 ; =0x021064C0
	ldr r2, _020AEE38 ; =FUN_020AECB4
	ldr r0, _020AEE3C ; =0x021064C4
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020AEE2C: .word 0x021CCD4C
_020AEE30: .word FUN_020AECBC
_020AEE34: .word 0x021064C0
_020AEE38: .word FUN_020AECB4
_020AEE3C: .word 0x021064C4

	arm_func_start FUN_020AEE40
FUN_020AEE40: ; 0x020AEE40
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r5, _020AEEB4 ; =0x021CCD58
	mov r9, r0
	mov r0, r5
	mov r8, r1
	mov r7, r2
	mov r6, r3
	bl FUN_020AF2F4
_020AEE64: ; 0x020AEE64
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
_020AEE74: ; 0x020AEE74
	mov r0, r5
	bl FUN_020AEF78
	mov r4, r0
	str r9, [r4, #0x0]
	str r7, [r4, #0x4]
	str r8, [r4, #0x8]
	mov r0, r5
	str r6, [r4, #0xc]
	bl FUN_020AEF98
	ldr r2, [r5, #0x10]
	ldr r1, [r4, #0xc]
	mov r0, #0x1
	add r1, r2, r1
	str r1, [r5, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020AEEB4: .word 0x021CCD58

	arm_func_start FUN_020AEEB8
FUN_020AEEB8: ; 0x020AEEB8
	stmdb sp!, {r4-r6,lr}
	ldr r6, _020AEF18 ; =0x021CCD58
	mov r0, r6
	bl FUN_020AEF88
	mov r5, r0
	mov r0, r6
	bl FUN_020AEF3C
_020AEED4: ; 0x020AEED4
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020AEEDC: ; 0x020AEEDC
	add r4, r6, #0x10
_020AEEE0:
	mov r0, r5
	bl FUN_020AEFF0
	ldr r2, [r4, #0x0]
	ldr r1, [r5, #0xc]
	mov r0, r6
	sub r1, r2, r1
	str r1, [r4, #0x0]
	bl FUN_020AEF88
	mov r5, r0
	mov r0, r6
	bl FUN_020AEF3C
_020AEF0C: ; 0x020AEF0C
	cmp r0, #0x0
	bne _020AEEE0
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020AEF18: .word 0x021CCD58

	arm_func_start FUN_020AEF1C
FUN_020AEF1C: ; 0x020AEF1C
	ldr r2, _020AEF34 ; =0x021CCD58
	ldr ip, _020AEF38 ; =FUN_020AEFD4
	str r0, [r2, #0x0]
	mov r0, r2
	str r1, [r2, #0x4]
	bx r12
	.balign 4
_020AEF34: .word 0x021CCD58
_020AEF38: .word FUN_020AEFD4

	arm_func_start FUN_020AEF3C
FUN_020AEF3C:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020AF2E0
_020AEF48: ; 0x020AEF48
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
_020AEF54: ; 0x020AEF54
	ldrh r1, [r4, #0x8]
	mov r0, r4
	bl FUN_020AF30C
	strh r0, [r4, #0x8]
	ldrh r1, [r4, #0xc]
	mov r0, #0x1
	sub r1, r1, #0x1
	strh r1, [r4, #0xc]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020AEF78
FUN_020AEF78: ; 0x020AEF78
	ldrh r1, [r0, #0xa]
	ldr r0, [r0, #0x0]
	add r0, r0, r1, lsl #0x4
	bx lr

	arm_func_start FUN_020AEF88
FUN_020AEF88: ; 0x020AEF88
	ldrh r1, [r0, #0x8]
	ldr r0, [r0, #0x0]
	add r0, r0, r1, lsl #0x4
	bx lr

	arm_func_start FUN_020AEF98
FUN_020AEF98: ; 0x020AEF98
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020AF2F4
_020AEFA4: ; 0x020AEFA4
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
_020AEFB0: ; 0x020AEFB0
	ldrh r1, [r4, #0xa]
	mov r0, r4
	bl FUN_020AF30C
	strh r0, [r4, #0xa]
	ldrh r1, [r4, #0xc]
	mov r0, #0x1
	add r1, r1, #0x1
	strh r1, [r4, #0xc]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020AEFD4
FUN_020AEFD4: ; 0x020AEFD4
	mov r2, #0x0
	strh r2, [r0, #0xa]
	ldrh r1, [r0, #0xa]
	strh r1, [r0, #0x8]
	strh r2, [r0, #0xc]
	str r2, [r0, #0x10]
	bx lr

	arm_func_start FUN_020AEFF0
FUN_020AEFF0: ; 0x020AEFF0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r3, [r5, #0x0]
	ldr r2, _020AF02C ; =0x020FF7D4
	ldr r0, [r5, #0x4]
	ldr r1, [r5, #0xc]
	ldr r4, [r2, r3, lsl #0x2]
	bl DC_FlushRange
	ldr r0, [r5, #0x4]
	ldr r1, [r5, #0x8]
	ldr r2, [r5, #0xc]
	blx r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AF02C: .word 0x020FF7D4
