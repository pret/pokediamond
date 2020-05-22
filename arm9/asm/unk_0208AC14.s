	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020FFA38
	.extern UNK_02106158
	.extern UNK_02106160
	.extern UNK_02106168
	.extern UNK_021064B8
	.extern UNK_021064C0

	.section .bss

	.global UNK_021C8C5C
UNK_021C8C5C: ; 0x021C8C5C
	.space 0x4

	.global UNK_021C8C60
UNK_021C8C60: ; 0x021C8C60
	.space 0x4

	.global UNK_021C8C64
UNK_021C8C64: ; 0x021C8C64
	.space 0x4

	.global UNK_021C8C68
UNK_021C8C68: ; 0x021C8C68
	.space 0x4

	.global UNK_021C8C6C
UNK_021C8C6C: ; 0x021C8C6C
	.space 0x4

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
	ldr r3, _0208B660 ; =UNK_021064C0
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
_0208B660: .word UNK_021064C0
_0208B664: .word 0x0000FFFF

	arm_func_start FUN_0208B668
FUN_0208B668: ; 0x0208B668
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, _0208B698 ; =UNK_021064B8
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
_0208B698: .word UNK_021064B8
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
	ldr r6, _0208C954 ; =UNK_020FFA38
	ldr r0, [r0, #0x14]
	mov r1, r1, asr #0x4
	ldrh r0, [r0, #0x0]
	mov r2, r1, lsl #0x1
	add r1, r2, #0x1
	mov r7, r2, lsl #0x1
	mov r1, r1, lsl #0x1
	mov r0, r0, lsl #0x15
	mov r3, r0, lsr #0x1e
	ldr r2, _0208C958 ; =UNK_02106160
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
	bl MTX_Scale43_
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
	ldr r4, _0208C970 ; =UNK_02106158
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
_0208C954: .word UNK_020FFA38
_0208C958: .word UNK_02106160
_0208C95C: .word 0x00000CCD
_0208C960: .word 0xFFFFF333
_0208C964: .word 0x04000454
_0208C968: .word 0x04000470
_0208C96C: .word 0x04000480
_0208C970: .word UNK_02106158

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
	ldr r6, _0208CDD0 ; =UNK_020FFA38
	ldr r0, [r0, #0x0]
	mov r1, r1, asr #0x4
	mov r2, r1, lsl #0x1
	ldr r0, [r0, #0x0]
	add r1, r2, #0x1
	mov r7, r2, lsl #0x1
	mov r1, r1, lsl #0x1
	mov r0, r0, lsl #0xd
	mov r3, r0, lsr #0x1e
	ldr r2, _0208CDD4 ; =UNK_02106160
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
	bl MTX_Scale43_
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
	ldr r4, _0208CDEC ; =UNK_02106158
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
_0208CDD0: .word UNK_020FFA38
_0208CDD4: .word UNK_02106160
_0208CDD8: .word 0x00000CCD
_0208CDDC: .word 0xFFFFF333
_0208CDE0: .word 0x04000454
_0208CDE4: .word 0x04000470
_0208CDE8: .word 0x04000480
_0208CDEC: .word UNK_02106158

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
	ldr r6, _0208D128 ; =UNK_020FFA38
	ldr r0, [r0, #0x14]
	mov r1, r1, asr #0x4
	ldrh r0, [r0, #0x0]
	mov r2, r1, lsl #0x1
	add r1, r2, #0x1
	mov r7, r2, lsl #0x1
	mov r1, r1, lsl #0x1
	mov r0, r0, lsl #0x15
	mov r3, r0, lsr #0x1e
	ldr r2, _0208D12C ; =UNK_02106160
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
	bl MTX_Scale43_
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
	ldr r4, _0208D13C ; =UNK_02106158
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
_0208D128: .word UNK_020FFA38
_0208D12C: .word UNK_02106160
_0208D130: .word 0x04000454
_0208D134: .word 0x04000470
_0208D138: .word 0x04000480
_0208D13C: .word UNK_02106158

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
	ldr r6, _0208D478 ; =UNK_020FFA38
	ldr r0, [r0, #0x0]
	mov r1, r1, asr #0x4
	mov r2, r1, lsl #0x1
	ldr r0, [r0, #0x0]
	add r1, r2, #0x1
	mov r7, r2, lsl #0x1
	mov r1, r1, lsl #0x1
	mov r0, r0, lsl #0xd
	mov r3, r0, lsr #0x1e
	ldr r2, _0208D47C ; =UNK_02106160
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
	bl MTX_Scale43_
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
	ldr r4, _0208D48C ; =UNK_02106158
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
_0208D478: .word UNK_020FFA38
_0208D47C: .word UNK_02106160
_0208D480: .word 0x04000454
_0208D484: .word 0x04000470
_0208D488: .word 0x04000480
_0208D48C: .word UNK_02106158

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
	ldr r2, _0208E69C ; =UNK_020FFA38
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
	ldr r2, _0208E69C ; =UNK_020FFA38
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
_0208E69C: .word UNK_020FFA38
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
	ldr r2, _0208EAE8 ; =UNK_020FFA38
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
	ldr r2, _0208EAE8 ; =UNK_020FFA38
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
_0208EAE8: .word UNK_020FFA38
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
	ldr sb, _0208F06C ; =UNK_021C8C5C
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
_0208F06C: .word UNK_021C8C5C
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
	ldr r6, _0208FD8C ; =UNK_021C8C5C
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
	ldr r0, _0208FD98 ; =UNK_020FFA38
	mov r1, r2, lsl #0x1
	ldrsh r0, [r0, r1]
	add r1, r2, #0x1
	mov r2, r1, lsl #0x1
	ldr r1, _0208FD98 ; =UNK_020FFA38
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
_0208FD8C: .word UNK_021C8C5C
_0208FD90: .word 0x5EEDF715
_0208FD94: .word 0x1B0CB173
_0208FD98: .word UNK_020FFA38
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
	ldr r1, _0209018C ; =UNK_02106168
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
_0209018C: .word UNK_02106168

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
	ldr r3, _02090368 ; =UNK_021C8C5C
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
_02090368: .word UNK_021C8C5C
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
	ldr r3, _02090854 ; =UNK_020FFA38
	add r0, sp, #0x0
	mov r1, r1, asr #0x4
	mov r2, r1, lsl #0x1
	add r1, r2, #0x1
	mov r12, r2, lsl #0x1
	mov r2, r1, lsl #0x1
	ldrsh r1, [r3, r12]
	ldrsh r2, [r3, r2]
	bl MTX_RotX33_
	b _02090838
_020907DC:
	ldrh r1, [r0, #0x0]
	ldr r3, _02090854 ; =UNK_020FFA38
	add r0, sp, #0x0
	mov r1, r1, asr #0x4
	mov r2, r1, lsl #0x1
	add r1, r2, #0x1
	mov r12, r2, lsl #0x1
	mov r2, r1, lsl #0x1
	ldrsh r1, [r3, r12]
	ldrsh r2, [r3, r2]
	bl MTX_RotY33_
	b _02090838
_0209080C:
	ldrh r1, [r0, #0x0]
	ldr r3, _02090854 ; =UNK_020FFA38
	add r0, sp, #0x0
	mov r1, r1, asr #0x4
	mov r2, r1, lsl #0x1
	add r1, r2, #0x1
	mov r12, r2, lsl #0x1
	mov r2, r1, lsl #0x1
	ldrsh r1, [r3, r12]
	ldrsh r2, [r3, r2]
	bl MTX_RotZ33_
_02090838:
	add r0, r4, #0x8
	add r1, sp, #0x0
	mov r2, r0
	bl MTX_MultVec33
	add sp, sp, #0x28
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02090854: .word UNK_020FFA38

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
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r2, _02090998 ; =UNK_021C8C5C
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
_02090998: .word UNK_021C8C5C
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
	ldr ip, _02090B44 ; =UNK_021C8C5C
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
_02090B44: .word UNK_021C8C5C
_02090B48: .word 0x5EEDF715
_02090B4C: .word 0x1B0CB173

	arm_func_start FUN_02090B50
FUN_02090B50: ; 0x02090B50
	stmdb sp!, {r4,lr}
	ldr ip, _02090BAC ; =UNK_021C8C5C
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
_02090BAC: .word UNK_021C8C5C
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
	ldr r3, _02090CB8 ; =UNK_021C8C6C
	ldr r2, _02090CBC ; =UNK_021C8C68
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
	ldr r0, _02090CC0 ; =UNK_021C8C64
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02090C84
	ldr r1, _02090CC4 ; =UNK_021C8C60
	ldrh r2, [r1, #0x0]
	cmp r2, #0x0
	beq _02090C84
	ldrh r0, [r0, #0x0]
	ldrh r1, [r1, #0x0]
	bl OSi_UnlockVram
	ldr r0, _02090CC0 ; =UNK_021C8C64
	mov r1, #0x0
	strh r1, [r0, #0x0]
	b _02090C84
_02090C38:
	cmp r4, #0x0
	bne _02090C78
	ldr r0, _02090CC0 ; =UNK_021C8C64
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02090C78
	ldr r1, _02090CC4 ; =UNK_021C8C60
	ldrh r2, [r1, #0x0]
	cmp r2, #0x0
	beq _02090C78
	ldrh r0, [r0, #0x0]
	ldrh r1, [r1, #0x0]
	bl OSi_UnlockVram
	ldr r0, _02090CC0 ; =UNK_021C8C64
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
	ldr r3, _02090CB8 ; =UNK_021C8C6C
	mov r12, #0x0
	ldr r2, _02090CBC ; =UNK_021C8C68
	mov r0, r5
	mov r1, r4
	str r12, [r3, #0x0]
	str r12, [r2, #0x0]
	blx r6
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_02090CB8: .word UNK_021C8C6C
_02090CBC: .word UNK_021C8C68
_02090CC0: .word UNK_021C8C64
_02090CC4: .word UNK_021C8C60

	arm_func_start FUN_02090CC8
FUN_02090CC8: ; 0x02090CC8
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	bl PXI_Init
	mov r0, #0xf
	mov r1, #0x1
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	moveq r0, #0x2
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	bl OS_DisableInterrupts
	ldr r1, _02090DA8 ; =UNK_021C8C6C
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
	cmp r0, #0x0
	bne _02090D3C
	ldr r1, _02090DAC ; =FUN_02090BBC
	mov r0, #0xf
	bl PXI_SetFifoRecvCallback
_02090D3C:
	cmp r6, #0x0
	ldreq r1, _02090DB0 ; =FUN_02090BB8
	ldreq r0, _02090DA8 ; =UNK_021C8C6C
	ldr r3, _02090DB4 ; =UNK_021C8C68
	streq r1, [r0, #0x0]
	ldrne r0, _02090DA8 ; =UNK_021C8C6C
	mov r1, #0x20000
	strne r6, [r0, #0x0]
	mov r0, #0xf
	mov r2, #0x0
	str r5, [r3, #0x0]
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	bge _02090D94
	ldr r1, _02090DA8 ; =UNK_021C8C6C
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
_02090DA8: .word UNK_021C8C6C
_02090DAC: .word FUN_02090BBC
_02090DB0: .word FUN_02090BB8
_02090DB4: .word UNK_021C8C68

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
	cmp r0, #0x0
	moveq r0, #0x2
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r8, _02091020 ; =UNK_021C8C60
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
	ldr r1, _02091024 ; =UNK_021C8C6C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _02090E48
	bl OS_RestoreInterrupts
	mov r0, #0x5
	ldmia sp!, {r4-r8,lr}
	bx lr
_02090E48:
	ldr r1, _02091028 ; =UNK_021C8C64
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
	ldr r1, _02091020 ; =UNK_021C8C60
	mov r0, #0x4
	ldrh r1, [r1, #0x0]
	bl OSi_TryLockVram
	cmp r0, #0x0
	bne _02090EB0
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r8,lr}
	bx lr
_02090EB0:
	ldr r0, _02091028 ; =UNK_021C8C64
	mov r2, #0x4
	ldr r1, _0209102C ; =0x04000242
	strh r2, [r0, #0x0]
	mov r0, #0x82
	strb r0, [r1, #0x0]
	b _02090F78
_02090ECC:
	ldr r1, _02091020 ; =UNK_021C8C60
	mov r0, #0x8
	ldrh r1, [r1, #0x0]
	bl OSi_TryLockVram
	cmp r0, #0x0
	bne _02090EF8
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r8,lr}
	bx lr
_02090EF8:
	ldr r0, _02091028 ; =UNK_021C8C64
	mov r2, #0x8
	ldr r1, _02091030 ; =0x04000243
	strh r2, [r0, #0x0]
	mov r0, #0x82
	strb r0, [r1, #0x0]
	b _02090F78
_02090F14:
	ldr r1, _02091020 ; =UNK_021C8C60
	mov r0, #0xc
	ldrh r1, [r1, #0x0]
	bl OSi_TryLockVram
	cmp r0, #0x0
	bne _02090F40
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r8,lr}
	bx lr
_02090F40:
	ldr r0, _02091028 ; =UNK_021C8C64
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
	cmp r0, #0x0
	bne _02090F98
	ldr r1, _02091034 ; =FUN_02090BBC
	mov r0, #0xf
	bl PXI_SetFifoRecvCallback
_02090F98:
	cmp r6, #0x0
	ldreq r1, _02091038 ; =FUN_02090BB8
	ldreq r0, _02091024 ; =UNK_021C8C6C
	ldr r3, _0209103C ; =UNK_021C8C68
	streq r1, [r0, #0x0]
	ldrne r0, _02091024 ; =UNK_021C8C6C
	mov r1, #0x10000
	strne r6, [r0, #0x0]
	mov r0, #0xf
	mov r2, #0x0
	str r5, [r3, #0x0]
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	bge _0209100C
	ldr r0, _02091028 ; =UNK_021C8C64
	ldr r1, _02091020 ; =UNK_021C8C60
	ldrh r0, [r0, #0x0]
	ldrh r1, [r1, #0x0]
	bl OSi_UnlockVram
	ldr r2, _02091028 ; =UNK_021C8C64
	mov r3, #0x0
	ldr r1, _02091024 ; =UNK_021C8C6C
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
_02091020: .word UNK_021C8C60
_02091024: .word UNK_021C8C6C
_02091028: .word UNK_021C8C64
_0209102C: .word 0x04000242
_02091030: .word 0x04000243
_02091034: .word FUN_02090BBC
_02091038: .word FUN_02090BB8
_0209103C: .word UNK_021C8C68
