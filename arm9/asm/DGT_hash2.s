	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global Unk_02106A00
Unk_02106A00: ; 0x02106A00
	.word DGTi_hash2_arm4_small

	.global Unk_02106A04
Unk_02106A04: ; 0x02106A04
	.byte 0x14, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

    .text

	arm_func_start DGT_Hash2CalcHmac
DGT_Hash2CalcHmac: ; 0x020D2D78
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0xa0
	ldr lr, _020D2E00 ; =Unk_02106A04
	add r12, sp, #0x1c
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, r3
	mov r4, r12
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr, {r0-r2}
	stmia r12, {r0-r2}
	add lr, sp, #0x38
	add r12, sp, #0x8
	str lr, [sp, #0x24]
	ldr lr, _020D2E04 ; =DGT_Hash2Reset
	str r12, [sp, #0x28]
	ldr ip, _020D2E08 ; =DGT_Hash2SetSource
	str lr, [sp, #0x2c]
	ldr lr, _020D2E0C ; =DGT_Hash2GetDigest
	str r12, [sp, #0x30]
	ldr r12, [sp, #0xb8]
	str lr, [sp, #0x34]
	str r12, [sp, #0x0]
	mov r3, r5
	mov r0, r8
	mov r1, r7
	mov r2, r6
	str r4, [sp, #0x4]
	bl DGTi_Hash2CalcHmac
	add sp, sp, #0xa0
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D2E00: .word Unk_02106A04 ; = Unk_02106A04
_020D2E04: .word DGT_Hash2Reset
_020D2E08: .word DGT_Hash2SetSource
_020D2E0C: .word DGT_Hash2GetDigest

	arm_func_start DGT_Hash2GetDigest
DGT_Hash2GetDigest: ; 0x020D2E10
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r6,lr}
	ldr r0, [sp, #0x10]
	mov r6, r1
	ldr r3, [r0, #0x1c]
	add r5, r0, #0x20
	ands r1, r3, #0x3
	mov r0, r3, asr #0x2
	moveq r1, #0x0
	streq r1, [r5, r0, lsl #0x2]
	ldr r2, [sp, #0x10]
	mov r1, #0x80
	add r4, r2, #0x20
	strb r1, [r4, r3]
	add r3, r3, #0x1
	ands r1, r3, #0x3
	beq _020D2E68
	mov r2, #0x0
_020D2E58:
	strb r2, [r4, r3]
	add r3, r3, #0x1
	ands r1, r3, #0x3
	bne _020D2E58
_020D2E68:
	ldr r1, [sp, #0x10]
	add r0, r0, #0x1
	ldr r1, [r1, #0x1c]
	cmp r1, #0x38
	blt _020D2EB4
	cmp r0, #0x10
	bge _020D2E98
	mov r1, #0x0
_020D2E88:
	str r1, [r5, r0, lsl #0x2]
	add r0, r0, #0x1
	cmp r0, #0x10
	blt _020D2E88
_020D2E98:
	ldr r1, _020D3008 ; =Unk_02106A00
	ldr r0, [sp, #0x10]
	ldr r3, [r1, #0x0]
	mov r1, r5
	mov r2, #0x40
	blx r3
	mov r0, #0x0
_020D2EB4:
	cmp r0, #0xe
	bge _020D2ED0
	mov r1, #0x0
_020D2EC0:
	str r1, [r5, r0, lsl #0x2]
	add r0, r0, #0x1
	cmp r0, #0xe
	blt _020D2EC0
_020D2ED0:
	ldr r0, [sp, #0x10]
	mov r1, r5
	ldr r2, [r0, #0x14]
	ldr r3, _020D3008 ; =Unk_02106A00
	strb r2, [r4, #0x3f]
	mov r0, r2, lsr #0x8
	strb r0, [r4, #0x3e]
	mov r0, r2, lsr #0x10
	strb r0, [r4, #0x3d]
	mov r0, r2, lsr #0x18
	strb r0, [r4, #0x3c]
	ldr r0, [sp, #0x10]
	mov r2, #0x40
	ldr r5, [r0, #0x18]
	strb r5, [r4, #0x3b]
	mov r0, r5, lsr #0x8
	strb r0, [r4, #0x3a]
	mov r0, r5, lsr #0x10
	strb r0, [r4, #0x39]
	mov r0, r5, lsr #0x18
	strb r0, [r4, #0x38]
	ldr r0, [sp, #0x10]
	ldr r3, [r3, #0x0]
	blx r3
	ldr r0, [sp, #0x10]
	add r1, sp, #0x10
	ldr r3, [r0, #0x0]
	mov r0, #0x0
	mov r2, r3, lsr #0x18
	strb r2, [r6, #0x0]
	mov r2, r3, lsr #0x10
	strb r2, [r6, #0x1]
	mov r2, r3, lsr #0x8
	strb r2, [r6, #0x2]
	strb r3, [r6, #0x3]
	ldr r3, [sp, #0x10]
	mov r2, #0x4
	ldr r4, [r3, #0x4]
	mov r3, r4, lsr #0x18
	strb r3, [r6, #0x4]
	mov r3, r4, lsr #0x10
	strb r3, [r6, #0x5]
	mov r3, r4, lsr #0x8
	strb r3, [r6, #0x6]
	strb r4, [r6, #0x7]
	ldr r3, [sp, #0x10]
	ldr r4, [r3, #0x8]
	mov r3, r4, lsr #0x18
	strb r3, [r6, #0x8]
	mov r3, r4, lsr #0x10
	strb r3, [r6, #0x9]
	mov r3, r4, lsr #0x8
	strb r3, [r6, #0xa]
	strb r4, [r6, #0xb]
	ldr r3, [sp, #0x10]
	ldr r4, [r3, #0xc]
	mov r3, r4, lsr #0x18
	strb r3, [r6, #0xc]
	mov r3, r4, lsr #0x10
	strb r3, [r6, #0xd]
	mov r3, r4, lsr #0x8
	strb r3, [r6, #0xe]
	strb r4, [r6, #0xf]
	ldr r3, [sp, #0x10]
	ldr r4, [r3, #0x10]
	mov r3, r4, lsr #0x18
	strb r3, [r6, #0x10]
	mov r3, r4, lsr #0x10
	strb r3, [r6, #0x11]
	mov r3, r4, lsr #0x8
	strb r3, [r6, #0x12]
	strb r4, [r6, #0x13]
	ldr r3, [sp, #0x10]
	str r0, [r3, #0x1c]
	bl MIi_CpuClear32
	ldmia sp!, {r4-r6,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020D3008: .word Unk_02106A00 ; = Unk_02106A00

	arm_func_start DGT_Hash2SetSource
DGT_Hash2SetSource: ; 0x020D300C
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	movs r6, r2
	mov r7, r1
	add r5, r8, #0x20
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r0, [r8, #0x14]
	add r1, r0, r6, lsl #0x3
	cmp r1, r0
	ldrcc r0, [r8, #0x18]
	addcc r0, r0, #0x1
	strcc r0, [r8, #0x18]
	ldr r0, [r8, #0x18]
	add r0, r0, r6, lsr #0x1d
	str r0, [r8, #0x18]
	str r1, [r8, #0x14]
	ldr r1, [r8, #0x1c]
	cmp r1, #0x0
	beq _020D30CC
	add r0, r1, r6
	cmp r0, #0x40
	blo _020D30A8
	rsb r4, r1, #0x40
	mov r0, r7
	mov r2, r4
	add r1, r5, r1
	bl MI_CpuCopy8
	ldr r1, _020D3164 ; =Unk_02106A00
	mov r0, r8
	ldr r3, [r1, #0x0]
	mov r1, r5
	mov r2, #0x40
	sub r6, r6, r4
	add r7, r7, r4
	blx r3
	mov r0, #0x0
	str r0, [r8, #0x1c]
	b _020D30CC
_020D30A8:
	mov r0, r7
	mov r2, r6
	add r1, r5, r1
	bl MI_CpuCopy8
	ldr r0, [r8, #0x1c]
	add r0, r0, r6
	str r0, [r8, #0x1c]
	ldmia sp!, {r4-r8,lr}
	bx lr
_020D30CC:
	cmp r6, #0x40
	blo _020D313C
	bic r4, r6, #0x3f
	sub r6, r6, r4
	ands r0, r7, #0x3
	bne _020D3104
	ldr r1, _020D3164 ; =Unk_02106A00
	mov r0, r8
	ldr r3, [r1, #0x0]
	mov r1, r7
	mov r2, r4
	blx r3
	add r7, r7, r4
	b _020D313C
_020D3104:
	mov r0, r7
	mov r1, r5
	mov r2, #0x40
	bl MI_CpuCopy8
	ldr r1, _020D3164 ; =Unk_02106A00
	mov r0, r8
	ldr r3, [r1, #0x0]
	mov r1, r5
	mov r2, #0x40
	add r7, r7, #0x40
	blx r3
	sub r4, r4, #0x40
	cmp r4, #0x0
	bgt _020D3104
_020D313C:
	str r6, [r8, #0x1c]
	cmp r6, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r0, r7
	mov r1, r5
	mov r2, r6
	bl MI_CpuCopy8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D3164: .word Unk_02106A00 ; = Unk_02106A00

	arm_func_start DGT_Hash2Reset
DGT_Hash2Reset: ; 0x020D3168
	ldr r1, _020D31A4 ; =0x67452301
	ldr r2, _020D31A8 ; =0xEFCDAB89
	str r1, [r0, #0x0]
	ldr r1, _020D31AC ; =0x98BADCFE
	str r2, [r0, #0x4]
	ldr r2, _020D31B0 ; =0x10325476
	str r1, [r0, #0x8]
	ldr r1, _020D31B4 ; =0xC3D2E1F0
	str r2, [r0, #0xc]
	str r1, [r0, #0x10]
	mov r1, #0x0
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
	bx lr
	.balign 4
_020D31A4: .word 0x67452301
_020D31A8: .word 0xEFCDAB89
_020D31AC: .word 0x98BADCFE
_020D31B0: .word 0x10325476
_020D31B4: .word 0xC3D2E1F0

	arm_func_start DGTi_Hash2CalcHmac
DGTi_Hash2CalcHmac: ; 0x020D31B8
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc4
	ldr r5, [sp, #0xe0]
	ldr r4, [sp, #0xe4]
	movs r9, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r8, #0x0
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r7, #0x0
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r6, #0x0
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r5, #0x0
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r4, #0x0
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r0, [r4, #0x4]
	cmp r5, r0
	ble _020D3278
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0x10]
	blx r1
	ldr r0, [r4, #0x8]
	ldr r3, [r4, #0x14]
	mov r1, r6
	mov r2, r5
	blx r3
	ldr r0, [r4, #0x8]
	ldr r2, [r4, #0x18]
	add r1, sp, #0x0
	blx r2
	ldr r5, [r4, #0x0]
	add r6, sp, #0x0
_020D3278:
	cmp r5, #0x0
	mov r0, #0x0
	ble _020D32A0
	add r2, sp, #0x40
_020D3288:
	ldrb r1, [r6, r0]
	add r0, r0, #0x1
	cmp r0, r5
	eor r1, r1, #0x36
	strb r1, [r2], #0x1
	blt _020D3288
_020D32A0:
	ldr r1, [r4, #0x4]
	cmp r0, r1
	bge _020D32CC
	add r1, sp, #0x40
	add r3, r1, r0
	mov r2, #0x36
_020D32B8:
	strb r2, [r3], #0x1
	ldr r1, [r4, #0x4]
	add r0, r0, #0x1
	cmp r0, r1
	blt _020D32B8
_020D32CC:
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0x10]
	blx r1
	ldr r0, [r4, #0x8]
	ldr r2, [r4, #0x4]
	ldr r3, [r4, #0x14]
	add r1, sp, #0x40
	blx r3
	ldr r0, [r4, #0x8]
	ldr r3, [r4, #0x14]
	mov r1, r8
	mov r2, r7
	blx r3
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x18]
	blx r2
	cmp r5, #0x0
	mov r2, #0x0
	ble _020D3338
	add r1, sp, #0x80
_020D3320:
	ldrb r0, [r6, r2]
	add r2, r2, #0x1
	cmp r2, r5
	eor r0, r0, #0x5c
	strb r0, [r1], #0x1
	blt _020D3320
_020D3338:
	ldr r0, [r4, #0x4]
	cmp r2, r0
	bge _020D3364
	add r0, sp, #0x80
	add r3, r0, r2
	mov r1, #0x5c
_020D3350:
	strb r1, [r3], #0x1
	ldr r0, [r4, #0x4]
	add r2, r2, #0x1
	cmp r2, r0
	blt _020D3350
_020D3364:
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0x10]
	blx r1
	ldr r0, [r4, #0x8]
	ldr r2, [r4, #0x4]
	ldr r3, [r4, #0x14]
	add r1, sp, #0x80
	blx r3
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x0]
	ldr r3, [r4, #0x14]
	blx r3
	ldr r0, [r4, #0x8]
	ldr r2, [r4, #0x18]
	mov r1, r9
	blx r2
	add sp, sp, #0xc4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
