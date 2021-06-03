	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global Unk_0210683C
Unk_0210683C: ; 0x0210683C
	.word 0x80

	.global Unk_02106840
Unk_02106840: ; 0x02106840
	.word  1,  6, 11,  0
	.word  5, 10, 15,  4
	.word  9, 14,  3,  8
	.word 13,  2,  7, 12
	.word  5,  8, 11, 14
	.word  1,  4,  7, 10
	.word 13,  0,  3,  6
	.word  9, 12, 15,  2
	.word  0,  7, 14,  5
	.word 12,  3, 10,  1
	.word  8, 15,  6, 13
	.word  4, 11,  2,  9

	.global Unk_02106900
Unk_02106900: ; 0x02106900
	.word 0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE
	.word 0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501
	.word 0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE
	.word 0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821
	.word 0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA
	.word 0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8
	.word 0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED
	.word 0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A
	.word 0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C
	.word 0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70
	.word 0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05
	.word 0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665
	.word 0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039
	.word 0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1
	.word 0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1
	.word 0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391

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
	ldr r2, _020D2B78 ; =Unk_02106900
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
	ldr r6, _020D2B7C ; =Unk_02106840
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
_020D2B78: .word Unk_02106900 ; = Unk_02106900
_020D2B7C: .word Unk_02106840 ; = Unk_02106840

	arm_func_start DGT_Hash1GetDigest_R
DGT_Hash1GetDigest_R: ; 0x020D2B80
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldr r1, [r6, #0x14]
	ldr r3, [r6, #0x10]
	mov r7, r0
	mov r4, r1, lsl #0x3
	ldr r1, _020D2C40 ; =Unk_0210683C
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
_020D2C40: .word Unk_0210683C ; = Unk_0210683C

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
