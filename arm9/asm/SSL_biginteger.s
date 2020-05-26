	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start get48bits_1
get48bits_1: ; 0x020A4ABC
	ldrh r1, [r0, #0x0]
	mov r0, #0x0
	bx lr

	arm_func_start get48bits_2
get48bits_2: ; 0x020A4AC8
	ldrh r1, [r0, #0x0]
	ldrh r0, [r0, #-0x2]
	mov r0, r0, lsl #0x10
	bx lr

	arm_func_start get48bits_3
get48bits_3: ; 0x020A4AD8
	ldrh r1, [r0, #0x0]
	ldrh r2, [r0, #-0x2]
	ldrh r3, [r0, #-0x4]
	orr r0, r3, r2, lsl #0x10
	bx lr

	arm_func_start get64bits
get64bits: ; 0x020A4AEC
	ldrh r2, [r0, #0x0]
	ldrh r3, [r0, #-0x2]
	orr r1, r3, r2, lsl #0x10
	ldrh r2, [r0, #-0x4]
	ldrh r3, [r0, #-0x6]
	orr r0, r3, r2, lsl #0x10
	bx lr

	arm_func_start CPSi_char_from_big
CPSi_char_from_big: ; 0x020A4B08
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

	arm_func_start CPSi_big_from_char
CPSi_big_from_char: ; 0x020A4B50
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

	arm_func_start CPSi_big_montpower
CPSi_big_montpower: ; 0x020A4BB0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	mov r10, r3
	mov r3, #0x16
	mul r4, r10, r3
	ldr r3, _020A4DE0 ; =CPSiAlloc
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
	bl count_digits
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
	bl CPSi_big_modinv
	ldr r1, [sp, #0x1c]
	mov r0, r5
	mov r2, r6
	mov r3, r10
	bl CPSi_big_mult
	mov r0, r6
	mov r1, r5
	mov r2, #0x1
	mov r3, r10
	bl CPSi_big_subsmall
	str r10, [sp, #0x0]
	mov r0, r6
	mov r1, r6
	mov r2, r9
	mov r3, #0x0
	str r7, [sp, #0x4]
	bl CPSi_big_div
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x20]
	ldr r2, [sp, #0x1c]
	mov r3, r10
	bl CPSi_big_mult
	ldr r1, [sp, #0x20]
	str r10, [sp, #0x0]
	mov r0, #0x0
	mov r2, r9
	mov r3, r1
	str r7, [sp, #0x4]
	bl CPSi_big_div
	str r10, [sp, #0x0]
	ldr r1, [sp, #0x1c]
	mov r0, #0x0
	mov r2, r9
	mov r3, r11
	str r7, [sp, #0x4]
	bl CPSi_big_div
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
	bl CPSi_big_montmult
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
	bl CPSi_big_montmult
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
	bl CPSi_big_montmult
	ldr r1, _020A4DE4 ; =CPSiFree
	ldr r0, [sp, #0x1c]
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A4DE0: .word CPSiAlloc
_020A4DE4: .word CPSiFree

	arm_func_start CPSi_big_montmult
CPSi_big_montmult: ; 0x020A4DE8
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
	bl CPSi_big_sqr
	b _020A4E48
_020A4E2C:
	cmp r8, #0x0
	beq _020A4E48
	mov r0, r6
	mov r1, r9
	mov r2, r8
	mov r3, r5
	bl CPSi_big_mult
_020A4E48:
	ldr r0, [sp, #0x2c]
	ldr r2, [sp, #0x28]
	mov r1, r6
	mov r3, r4
	bl CPSi_big_mult
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
	bl CPSi_big_mult
	mov r0, r6
	mov r1, r6
	ldr r2, [sp, #0x30]
	mov r3, r5
	bl CPSi_big_add
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
	bl CPSi_big_compare
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
	bl CPSi_big_sub
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start CPSi_big_modinv
CPSi_big_modinv: ; 0x020A4F2C
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
	bl CPSi_big_sign
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
	bl CPSi_big_div
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
	bl CPSi_big_mult
	mov r0, r5
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl CPSi_big_sub
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
	bl CPSi_big_sign
	cmp r0, #0x0
	bgt _020A4FA0
_020A503C:
	ldr r2, [sp, #0xc]
	mov r0, r6
	mov r1, r6
	mov r3, r10
	bl CPSi_big_add
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	ldr r4, [sp, #0x10]
	str r10, [sp, #0x0]
	mov r1, r6
	mov r0, #0x0
	str r4, [sp, #0x4]
	bl CPSi_big_div
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start CPSi_big_power
CPSi_big_power: ; 0x020A507C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	ldr r4, _020A5238 ; =CPSiAlloc
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
	bl count_digits
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
	bl CPSi_big_sqr
	ldr r2, [sp, #0xc]
	mov r0, r6
	mov r1, r10
	bl MI_CpuCopy8
	cmp r7, #0x0
	beq _020A51A4
	ldr r0, [sp, #0x10]
	str r8, [sp, #0x0]
	mov r1, r10
	mov r2, r7
	mov r3, r10
	str r11, [sp, #0x4]
	bl CPSi_big_div
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
	bl CPSi_big_mult
	ldr r2, [sp, #0xc]
	mov r0, r6
	mov r1, r10
	bl MI_CpuCopy8
	cmp r7, #0x0
	beq _020A5210
	ldr r0, [sp, #0x10]
	str r8, [sp, #0x0]
	mov r1, r10
	mov r2, r7
	mov r3, r10
	str r11, [sp, #0x4]
	bl CPSi_big_div
_020A5210:
	add r5, r5, #0x1
	cmp r5, r4
	blo _020A5160
_020A521C:
	ldr r1, _020A523C ; =CPSiFree
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A5238: .word CPSiAlloc
_020A523C: .word CPSiFree

	arm_func_start CPSi_big_div
CPSi_big_div: ; 0x020A5240
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
	bl count_digits
	mov r11, r0
	mov r0, r10
	mov r1, r9
	bl count_digits
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
	bl get48bits_3
	str r0, [sp, #0x14]
	str r1, [sp, #0x10]
	b _020A5340
_020A5304:
	cmp r7, #0x1
	ble _020A5328
	add r0, r10, r7, lsl #0x1
	sub r0, r0, #0x2
	mov r7, r7, lsl #0x1
	bl get48bits_2
	str r0, [sp, #0x14]
	str r1, [sp, #0x10]
	b _020A5340
_020A5328:
	add r0, r10, r7, lsl #0x1
	sub r0, r0, #0x2
	mov r7, r7, lsl #0x1
	bl get48bits_1
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
	bl get64bits
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
	bl CPSi_big_mult_small
	mov r0, r4
	mov r1, r6
	mov r2, r9
	bl CPSi_big_compare
	cmp r0, #0x0
	sublt r7, r7, #0x1
	blt _020A5390
	mov r0, r4
	mov r1, r4
	mov r2, r6
	mov r3, r9
	bl CPSi_big_sub
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

	arm_func_start CPSi_big_sqr
CPSi_big_sqr: ; 0x020A5438
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	mov r8, r2
	mov r10, r0
	mov r0, r9
	mov r1, r8
	bl count_digits
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
	bl CPSi_big_add_part
	b _020A5550
_020A5528:
	mov r0, r10
	mov r1, r4
	mov r2, r5
	mov r3, r8
	bl CPSi_big_add_part
	mov r0, r10
	mov r1, r4
	mov r2, r5
	mov r3, r8
	bl CPSi_big_add_part
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

	arm_func_start CPSi_big_mult_small
CPSi_big_mult_small: ; 0x020A5584
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	mov r4, r3
	mov r7, r0
	mov r0, r6
	mov r1, r4
	mov r5, r2
	bl count_digits
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

	arm_func_start CPSi_big_mult
CPSi_big_mult: ; 0x020A5608
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
	bl count_digits
	mov r5, r0
	mov r0, r9
	mov r1, r8
	bl count_digits
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
	bl CPSi_big_add_part
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

	arm_func_start CPSi_big_add_part
CPSi_big_add_part: ; 0x020A56C4
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

	arm_func_start CPSi_big_compare
CPSi_big_compare:
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

	arm_func_start CPSi_big_subsmall
CPSi_big_subsmall: ; 0x020A5748
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

	arm_func_start CPSi_big_sub
CPSi_big_sub: ; 0x020A57BC
	stmdb sp!, {r4-r8,lr}
	mov r7, r1
	mov r5, r3
	mov r8, r0
	mov r6, r2
	mov r0, r7
	mov r1, r5
	bl count_digits
	mov r4, r0
	mov r0, r6
	mov r1, r5
	bl count_digits
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

	arm_func_start CPSi_big_negate
CPSi_big_negate: ; 0x020A5874
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
	bl CPSi_big_add_small
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start CPSi_big_add_small
CPSi_big_add_small: ; 0x020A58C0
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

	arm_func_start CPSi_big_add
CPSi_big_add: ; 0x020A5930
	stmdb sp!, {r4-r8,lr}
	mov r7, r1
	mov r5, r3
	mov r8, r0
	mov r6, r2
	mov r0, r7
	mov r1, r5
	bl count_digits
	mov r4, r0
	mov r0, r6
	mov r1, r5
	bl count_digits
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

	arm_func_start CPSi_big_sign
CPSi_big_sign:
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
	bl count_digits
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start count_digits
count_digits:
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
