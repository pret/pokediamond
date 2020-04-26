	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start ProcessBlock
ProcessBlock: ; 0x020D2798
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	add r3, r0, #0x18
	ldr r5, [r0, #0x0]
	ldr r4, [r0, #0x4]
	ldr lr, [r0, #0x8]
	ldr r12, [r0, #0xc]
	ldr r2, _020D2B78 ; =0x02106900
	mov r8, r3
	mov r7, #0x0
_020D27C0:
	mvn r1, r4
	and r6, r4, lr
	and r1, r1, r12
	orr r1, r6, r1
	ldr r6, [r8, #0x0]
	add r1, r5, r1
	ldr r5, [r2, #0x0]
	add r1, r6, r1
	add r5, r5, r1
	mov r1, r5, lsl #0x7
	orr r1, r1, r5, lsr #0x19
	add r5, r4, r1
	mvn r1, r5
	and r6, r5, r4
	and r1, r1, lr
	orr r1, r6, r1
	ldr r6, [r8, #0x4]
	add r1, r12, r1
	ldr r9, [r2, #0x4]
	add r1, r6, r1
	add r6, r9, r1
	mov r1, r6, lsl #0xc
	orr r1, r1, r6, lsr #0x14
	add r12, r5, r1
	mvn r1, r12
	and r6, r12, r5
	and r1, r1, r4
	orr r6, r6, r1
	add r1, r8, #0xc
	ldr r9, [r8, #0x8]
	add r6, lr, r6
	add r6, r9, r6
	ldr r9, [r2, #0x8]
	ldr r1, [r1, #0x0]
	add r10, r9, r6
	add r6, r2, #0xc
	ldr r6, [r6, #0x0]
	mov r9, r10, lsl #0x11
	orr r9, r9, r10, lsr #0xf
	add lr, r12, r9
	add r2, r2, #0x10
	add r8, r8, #0x10
	and r10, lr, r12
	mvn r9, lr
	and r9, r9, r5
	orr r9, r10, r9
	add r4, r4, r9
	add r1, r1, r4
	add r4, r6, r1
	mov r1, r4, lsl #0x16
	orr r1, r1, r4, lsr #0xa
	add r4, lr, r1
	add r7, r7, #0x1
	cmp r7, #0x4
	blt _020D27C0
	ldr r6, _020D2B7C ; =0x02106840
	mov r1, #0x0
_020D28A4:
	mvn r7, r12
	ldr r9, [r6, #0x0]
	and r8, r4, r12
	and r7, lr, r7
	orr r7, r8, r7
	ldr r8, [r3, r9, lsl #0x2]
	add r5, r5, r7
	ldr r7, [r2, #0x0]
	add r5, r8, r5
	add r7, r7, r5
	mov r5, r7, lsl #0x5
	orr r5, r5, r7, lsr #0x1b
	add r5, r4, r5
	mvn r8, lr
	ldr r7, [r6, #0x4]
	and r9, r5, lr
	and r8, r4, r8
	orr r10, r9, r8
	mvn r8, r4
	ldr r9, [r6, #0x8]
	ldr r11, [r3, r7, lsl #0x2]
	add r7, r12, r10
	add r10, r11, r7
	add r7, r6, #0xc
	ldr r9, [r3, r9, lsl #0x2]
	and r8, r5, r8
	ldr r7, [r7, #0x0]
	ldr r11, [r2, #0x4]
	ldr r7, [r3, r7, lsl #0x2]
	add r11, r11, r10
	mov r10, r11, lsl #0x9
	orr r10, r10, r11, lsr #0x17
	add r12, r5, r10
	ldr r10, [r2, #0x8]
	and r11, r12, r4
	orr r8, r11, r8
	add r8, lr, r8
	add r8, r9, r8
	add r10, r10, r8
	add r8, r2, #0xc
	ldr r8, [r8, #0x0]
	mov r9, r10, lsl #0xe
	orr r9, r9, r10, lsr #0x12
	add lr, r12, r9
	add r2, r2, #0x10
	add r6, r6, #0x10
	and r10, lr, r5
	mvn r9, r5
	and r9, r12, r9
	orr r9, r10, r9
	add r4, r4, r9
	add r4, r7, r4
	add r7, r8, r4
	mov r4, r7, lsl #0x14
	orr r4, r4, r7, lsr #0xc
	add r4, lr, r4
	add r1, r1, #0x1
	cmp r1, #0x4
	blt _020D28A4
	mov r7, #0x0
_020D2994:
	ldr r8, [r6, #0x0]
	eor r1, r4, lr
	eor r1, r12, r1
	add r1, r5, r1
	ldr r8, [r3, r8, lsl #0x2]
	ldr r5, [r2, #0x0]
	add r1, r8, r1
	add r5, r5, r1
	mov r1, r5, lsl #0x4
	orr r1, r1, r5, lsr #0x1c
	add r5, r4, r1
	ldr r8, [r6, #0x4]
	eor r1, r5, r4
	eor r1, lr, r1
	ldr r8, [r3, r8, lsl #0x2]
	add r1, r12, r1
	ldr r9, [r6, #0x8]
	ldr r10, [r2, #0x4]
	add r1, r8, r1
	add r8, r10, r1
	mov r1, r8, lsl #0xb
	orr r1, r1, r8, lsr #0x15
	add r12, r5, r1
	eor r8, r12, r5
	eor r8, r4, r8
	ldr r9, [r3, r9, lsl #0x2]
	add r8, lr, r8
	add r9, r9, r8
	ldr r10, [r2, #0x8]
	add r1, r2, #0xc
	ldr r8, [r6, #0xc]
	add r10, r10, r9
	ldr r9, [r3, r8, lsl #0x2]
	mov r8, r10, lsl #0x10
	orr r8, r8, r10, lsr #0x10
	add lr, r12, r8
	eor r8, lr, r12
	eor r8, r5, r8
	add r4, r4, r8
	add r7, r7, #0x1
	ldr r1, [r1, #0x0]
	add r4, r9, r4
	add r4, r1, r4
	mov r1, r4, lsl #0x17
	orr r1, r1, r4, lsr #0x9
	add r2, r2, #0x10
	add r6, r6, #0x10
	add r4, lr, r1
	cmp r7, #0x4
	blt _020D2994
	mov r10, #0x0
_020D2A60:
	mvn r1, r12
	ldr r7, [r6, #0x0]
	orr r1, r4, r1
	eor r1, lr, r1
	ldr r7, [r3, r7, lsl #0x2]
	add r1, r5, r1
	ldr r5, [r2, #0x0]
	add r1, r7, r1
	add r5, r5, r1
	mov r1, r5, lsl #0x6
	orr r1, r1, r5, lsr #0x1a
	add r5, r4, r1
	mvn r1, lr
	ldr r7, [r6, #0x4]
	orr r1, r5, r1
	eor r1, r4, r1
	ldr r8, [r6, #0x8]
	ldr r7, [r3, r7, lsl #0x2]
	add r1, r12, r1
	ldr r9, [r2, #0x4]
	add r1, r7, r1
	add r9, r9, r1
	mov r7, r9, lsl #0xa
	add r1, r6, #0xc
	orr r9, r7, r9, lsr #0x16
	ldr r1, [r1, #0x0]
	add r7, r2, #0xc
	add r12, r5, r9
	ldr r8, [r3, r8, lsl #0x2]
	ldr r7, [r7, #0x0]
	ldr r1, [r3, r1, lsl #0x2]
	ldr r9, [r2, #0x8]
	mvn r11, r4
	orr r11, r12, r11
	eor r11, r5, r11
	add r11, lr, r11
	add r8, r8, r11
	add r9, r9, r8
	mov r8, r9, lsl #0xf
	orr r8, r8, r9, lsr #0x11
	add lr, r12, r8
	add r2, r2, #0x10
	add r6, r6, #0x10
	mvn r8, r5
	orr r8, lr, r8
	eor r8, r12, r8
	add r4, r4, r8
	add r1, r1, r4
	add r4, r7, r1
	mov r1, r4, lsl #0x15
	orr r1, r1, r4, lsr #0xb
	add r4, lr, r1
	add r10, r10, #0x1
	cmp r10, #0x4
	blt _020D2A60
	ldr r1, [r0, #0x0]
	add r1, r1, r5
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, r4
	str r1, [r0, #0x4]
	ldr r1, [r0, #0x8]
	add r1, r1, lr
	str r1, [r0, #0x8]
	ldr r1, [r0, #0xc]
	add r1, r1, r12
	str r1, [r0, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D2B78: .word Unk_02106900 ; = 0x02106900
_020D2B7C: .word Unk_02106840 ; = 0x02106840

	arm_func_start DGT_Hash1GetDigest_R
DGT_Hash1GetDigest_R: ; 0x020D2B80
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldr r1, [r6, #0x14]
	ldr r3, [r6, #0x10]
	mov r7, r0
	mov r4, r1, lsl #0x3
	ldr r1, _020D2C40 ; =0x0210683C
	mov r0, r6
	mov r2, #0x1
	orr r4, r4, r3, lsr #0x1d
	mov r5, r3, lsl #0x3
	bl DGT_Hash1SetSource
	ldr r0, [r6, #0x10]
	mov r1, #0x0
	and r3, r0, #0x3f
	rsb r2, r3, #0x40
	cmp r2, #0x8
	bhs _020D2BE8
	add r0, r6, #0x18
	add r0, r0, r3
	bl MI_CpuFill8
	mov r0, r6
	bl ProcessBlock
	mov r3, #0x0
	mov r2, #0x40
_020D2BE8:
	cmp r2, #0x8
	bls _020D2C04
	add r0, r6, #0x18
	add r0, r0, r3
	sub r2, r2, #0x8
	mov r1, #0x0
	bl MI_CpuFill8
_020D2C04:
	str r5, [r6, #0x50]
	mov r0, r6
	str r4, [r6, #0x54]
	bl ProcessBlock
	mov r0, r6
	mov r1, r7
	mov r2, #0x10
	bl MI_CpuCopy8
	mov r0, r6
	mov r1, #0x0
	mov r2, #0x58
	bl MI_CpuFill8
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D2C40: .word Unk_0210683C ; = 0x0210683C

	arm_func_start DGT_Hash1SetSource
DGT_Hash1SetSource: ; 0x020D2C44
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	add r12, r8, #0x10
	ldr r4, [r8, #0x10]
	mov r6, r2
	and r3, r4, #0x3f
	ldr r0, [r12, #0x4]
	adds r4, r4, r6
	str r4, [r8, #0x10]
	adc r0, r0, #0x0
	rsb r5, r3, #0x40
	mov r7, r1
	str r0, [r12, #0x4]
	cmp r5, r6
	bls _020D2CB0
	cmp r6, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	add r1, r8, #0x18
	mov r0, r7
	add r1, r1, r3
	bl MI_CpuCopy8
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
_020D2CB0:
	add r1, r8, #0x18
	mov r0, r7
	mov r2, r5
	add r1, r1, r3
	bl MI_CpuCopy8
	mov r0, r8
	bl ProcessBlock
	sub r6, r6, r5
	mov r4, r6, lsr #0x6
	cmp r4, #0x0
	add r9, r7, r5
	ble _020D2D10
	add r7, r8, #0x18
	mov r5, #0x40
_020D2CE8:
	mov r0, r9
	mov r1, r7
	mov r2, r5
	bl MI_CpuCopy8
	mov r0, r8
	add r9, r9, #0x40
	bl ProcessBlock
	sub r4, r4, #0x1
	cmp r4, #0x0
	bgt _020D2CE8
_020D2D10:
	ands r2, r6, #0x3f
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r0, r9
	add r1, r8, #0x18
	bl MI_CpuCopy8
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start DGT_Hash1Reset
DGT_Hash1Reset: ; 0x020D2D38
	ldr r2, _020D2D68 ; =0x67452301
	ldr r1, _020D2D6C ; =0xEFCDAB89
	str r2, [r0, #0x0]
	ldr r2, _020D2D70 ; =0x98BADCFE
	str r1, [r0, #0x4]
	ldr r1, _020D2D74 ; =0x10325476
	str r2, [r0, #0x8]
	str r1, [r0, #0xc]
	mov r1, #0x0
	str r1, [r0, #0x10]
	str r1, [r0, #0x14]
	bx lr
	.balign 4
_020D2D68: .word 0x67452301
_020D2D6C: .word 0xEFCDAB89
_020D2D70: .word 0x98BADCFE
_020D2D74: .word 0x10325476

	arm_func_start MATH_CalcHMACSHA1
MATH_CalcHMACSHA1: ; 0x020D2D78
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0xa0
	ldr lr, _020D2E00 ; =0x02106A04
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
	ldr lr, _020D2E04 ; =MATH_SHA1Init
	str r12, [sp, #0x28]
	ldr ip, _020D2E08 ; =MATH_SHA1Update
	str lr, [sp, #0x2c]
	ldr lr, _020D2E0C ; =MATH_SHA1GetHash
	str r12, [sp, #0x30]
	ldr r12, [sp, #0xb8]
	str lr, [sp, #0x34]
	str r12, [sp, #0x0]
	mov r3, r5
	mov r0, r8
	mov r1, r7
	mov r2, r6
	str r4, [sp, #0x4]
	bl MATHi_CalcHMAC
	add sp, sp, #0xa0
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D2E00: .word Unk_02106A04 ; = 0x02106A04
_020D2E04: .word MATH_SHA1Init
_020D2E08: .word MATH_SHA1Update
_020D2E0C: .word MATH_SHA1GetHash

	arm_func_start MATH_SHA1GetHash
MATH_SHA1GetHash: ; 0x020D2E10
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
	ldr r1, _020D3008 ; =0x02106A00
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
	ldr r3, _020D3008 ; =0x02106A00
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
_020D3008: .word Unk_02106A00 ; = 0x02106A00

	arm_func_start MATH_SHA1Update
MATH_SHA1Update: ; 0x020D300C
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
	ldr r1, _020D3164 ; =0x02106A00
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
	ldr r1, _020D3164 ; =0x02106A00
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
	ldr r1, _020D3164 ; =0x02106A00
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
_020D3164: .word Unk_02106A00 ; = 0x02106A00

	arm_func_start MATH_SHA1Init
MATH_SHA1Init: ; 0x020D3168
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

	arm_func_start MATHi_CalcHMAC
MATHi_CalcHMAC: ; 0x020D31B8
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
_020D33B4: .word 0x00FF00FF
_020D33B8: .word 0x5A827999
_020D33BC: .word 0x6ED9EBA1
_020D33C0: .word 0x8F1BBCDC
_020D33C4: .word 0xCA62C1D6

	arm_func_start DGTi_hash2_arm4_small
DGTi_hash2_arm4_small: ; 0x020D33C8
	stmdb sp!, {r4-r12,lr}
	ldmia r0, {r3,r9-r12}
	sub sp, sp, #0x84
	str r2, [sp, #0x80]
_020D33D8:
	ldr r8, _020D33B8 ; =0x5A827999
	ldr r7, _020D33B4 ; =0x00FF00FF
	mov r6, sp
	mov r5, #0x0
_020D33E8:
	ldr r4, [r1], #0x4
	add r2, r8, r12
	add r2, r2, r3, ror #0x1B
	and lr, r4, r7
	and r4, r7, r4, ror #0x18
	orr r4, r4, lr, ror #0x8
	str r4, [r6, #0x40]
	str r4, [r6], #0x4
	add r2, r2, r4
	eor r4, r10, r11
	and r4, r4, r9
	eor r4, r4, r11
	add r2, r2, r4
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r5, r5, #0x4
	cmp r5, #0x40
	blt _020D33E8
	mov r7, #0x0
	mov r6, sp
_020D3448:
	ldr r2, [r6, #0x0]
	ldr r5, [r6, #0x8]
	ldr r4, [r6, #0x20]
	ldr lr, [r6, #0x34]
	eor r2, r2, r5
	eor r4, r4, lr
	eor r2, r2, r4
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	eor r4, r10, r11
	and r4, r4, r9
	eor r4, r4, r11
	add r2, r2, r4
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x4
	cmp r7, #0x10
	blt _020D3448
	ldr r8, _020D33BC ; =0x6ED9EBA1
	mov r7, #0x0
_020D34B8:
	ldr r2, [r6, #0x0]
	ldr r4, [r6, #0x8]
	ldr lr, [r6, #0x20]
	ldr r5, [r6, #0x34]
	eor r2, r2, r4
	eor lr, lr, r5
	eor r2, r2, lr
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	eor lr, r9, r10
	eor lr, lr, r11
	add r2, r2, lr
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x1
	cmp r7, #0xc
	moveq r6, sp
	cmp r7, #0x14
	blt _020D34B8
	ldr r8, _020D33C0 ; =0x8F1BBCDC
	mov r7, #0x0
_020D352C:
	ldr r2, [r6, #0x0]
	ldr lr, [r6, #0x8]
	ldr r5, [r6, #0x20]
	ldr r4, [r6, #0x34]
	eor r2, r2, lr
	eor r5, r5, r4
	eor r2, r2, r5
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	orr r5, r9, r10
	and r5, r5, r11
	and r4, r9, r10
	orr r5, r5, r4
	add r2, r2, r5
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x1
	cmp r7, #0x8
	moveq r6, sp
	cmp r7, #0x14
	blt _020D352C
	ldr r8, _020D33C4 ; =0xCA62C1D6
	mov r7, #0x0
_020D35A8:
	ldr r2, [r6, #0x0]
	ldr r5, [r6, #0x8]
	ldr r4, [r6, #0x20]
	ldr lr, [r6, #0x34]
	eor r2, r2, r5
	eor r4, r4, lr
	eor r2, r2, r4
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	eor r4, r9, r10
	eor r4, r4, r11
	add r2, r2, r4
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x1
	cmp r7, #0x4
	moveq r6, sp
	cmp r7, #0x14
	blt _020D35A8
	ldmia r0, {r2,r4,r6-r7,lr}
	add r3, r3, r2
	add r9, r9, r4
	add r10, r10, r6
	add r11, r11, r7
	add r12, r12, lr
	stmia r0, {r3,r9-r12}
	ldr lr, [sp, #0x80]
	subs lr, lr, #0x40
	str lr, [sp, #0x80]
	bgt _020D33D8
	add sp, sp, #0x84
	ldmia sp!, {r4-r12,pc}
