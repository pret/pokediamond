	.include "asm/macros.inc"
	.include "global.inc"
    .extern __msl_digit
    .extern __float_nan

    .rodata

parse_format$f: ; 0x0210440C
	.byte 0x00, 0x00, 0x00, 0x00
	.word 0x7FFFFFFF
	.word 0x00000000
	.word 0x00000000
	.word 0x00000000
	.word 0x00000000
	.word 0x00000000
	.word 0x00000000
	.word 0x00000000
	.word 0x00000000
	.size parse_format$f,.-parse_format$f

    .text

	local_arm_func_start parse_format
parse_format: ; 0x020E1A30
	stmdb sp!, {r3-r7,lr}
	sub sp, sp, #0x28
	ldr r6, _020E1F20 ; =parse_format$f
	add r5, sp, #0x0
	mov r7, r0
	mov lr, r1
	mov r4, r5
	ldmia r6!, {r0-r3}
	stmia r5!, {r0-r3}
	ldmia r6!, {r0-r3}
	stmia r5!, {r0-r3}
	ldmia r6, {r0-r1}
	stmia r5, {r0-r1}
	ldrsb r0, [r7, #0x1]
	add r12, r7, #0x1
	cmp r0, #0x25
	bne _020E1A9C
	strb r0, [sp, #0x3]
	ldmia r4!, {r0-r3}
	stmia lr!, {r0-r3}
	ldmia r4!, {r0-r3}
	stmia lr!, {r0-r3}
	ldmia r4, {r0-r1}
	stmia lr, {r0-r1}
	add sp, sp, #0x28
	add r0, r12, #0x1
	ldmia sp!, {r3-r7,pc}
_020E1A9C:
	cmp r0, #0x2a
	moveq r0, #0x1
	streqb r0, [sp, #0x0]
	ldreqsb r0, [r12, #0x1]!
	cmp r0, #0x0
	blt _020E1ABC
	cmp r0, #0x80
	blt _020E1AC4
_020E1ABC:
	mov r1, #0x0
	b _020E1AD4
_020E1AC4:
	ldr r1, _020E1F24 ; =__msl_digit
	mov r2, r0, lsl #0x1
	ldrh r1, [r1, r2]
	and r1, r1, #0x8
_020E1AD4:
	cmp r1, #0x0
	beq _020E1B74
	mov r1, #0x0
	ldr r3, _020E1F24 ; =__msl_digit
	str r1, [sp, #0x4]
	mov r4, r1
	mov r1, #0xa
_020E1AF0:
	ldr r2, [sp, #0x4]
	sub r0, r0, #0x30
	mla r0, r2, r1, r0
	str r0, [sp, #0x4]
	ldrsb r0, [r12, #0x1]!
	cmp r0, #0x0
	blt _020E1B14
	cmp r0, #0x80
	blt _020E1B1C
_020E1B14:
	mov r2, r4
	b _020E1B28
_020E1B1C:
	mov r2, r0, lsl #0x1
	ldrh r2, [r3, r2]
	and r2, r2, #0x8
_020E1B28:
	cmp r2, #0x0
	bne _020E1AF0
	ldr r1, [sp, #0x4]
	cmp r1, #0x0
	bne _020E1B6C
	mov r0, #0xff
	add r4, sp, #0x0
	strb r0, [sp, #0x3]
	ldmia r4!, {r0-r3}
	stmia lr!, {r0-r3}
	ldmia r4!, {r0-r3}
	stmia lr!, {r0-r3}
	ldmia r4, {r0-r1}
	stmia lr, {r0-r1}
	add sp, sp, #0x28
	add r0, r12, #0x1
	ldmia sp!, {r3-r7,pc}
_020E1B6C:
	mov r1, #0x1
	strb r1, [sp, #0x1]
_020E1B74:
	cmp r0, #0x6c
	mov r1, #0x1
	bgt _020E1BAC
	cmp r0, #0x68
	blt _020E1BA0
	beq _020E1BC8
	cmp r0, #0x6a
	beq _020E1C14
	cmp r0, #0x6c
	beq _020E1BE4
	b _020E1C38
_020E1BA0:
	cmp r0, #0x4c
	beq _020E1C08
	b _020E1C38
_020E1BAC:
	cmp r0, #0x74
	bgt _020E1BBC
	beq _020E1C2C
	b _020E1C38
_020E1BBC:
	cmp r0, #0x7a
	beq _020E1C20
	b _020E1C38
_020E1BC8:
	mov r2, #0x2
	strb r2, [sp, #0x2]
	ldrsb r2, [r12, #0x1]
	cmp r2, #0x68
	streqb r1, [sp, #0x2]
	ldreqsb r0, [r12, #0x1]!
	b _020E1C3C
_020E1BE4:
	mov r2, #0x3
	strb r2, [sp, #0x2]
	ldrsb r2, [r12, #0x1]
	cmp r2, #0x6c
	bne _020E1C3C
	mov r0, #0x7
	strb r0, [sp, #0x2]
	ldrsb r0, [r12, #0x1]!
	b _020E1C3C
_020E1C08:
	mov r2, #0x9
	strb r2, [sp, #0x2]
	b _020E1C3C
_020E1C14:
	mov r2, #0x4
	strb r2, [sp, #0x2]
	b _020E1C3C
_020E1C20:
	mov r2, #0x5
	strb r2, [sp, #0x2]
	b _020E1C3C
_020E1C2C:
	mov r2, #0x6
	strb r2, [sp, #0x2]
	b _020E1C3C
_020E1C38:
	mov r1, #0x0
_020E1C3C:
	cmp r1, #0x0
	ldrnesb r0, [r12, #0x1]!
	strb r0, [sp, #0x3]
	cmp r0, #0x5b
	bgt _020E1C90
	bge _020E1DE0
	cmp r0, #0x47
	bgt _020E1C84
	subs r1, r0, #0x41
	addpl pc, pc, r1, lsl #0x2
	b _020E1EF0
	b _020E1D1C ; case 65
	b _020E1EF0 ; case 66
	b _020E1EF0 ; case 67
	b _020E1EF0 ; case 68
	b _020E1D1C ; case 69
	b _020E1D1C ; case 70
	b _020E1D1C ; case 71
_020E1C84:
	cmp r0, #0x58
	beq _020E1D08
	b _020E1EF0
_020E1C90:
	cmp r0, #0x61
	bgt _020E1CA0
	beq _020E1D1C
	b _020E1EF0
_020E1CA0:
	sub r0, r0, #0x63
	cmp r0, #0x15
	addls pc, pc, r0, lsl #0x2
	b _020E1EF0
	b _020E1D6C ; case 99
	b _020E1D08 ; case 100
	b _020E1D1C ; case 101
	b _020E1D1C ; case 102
	b _020E1D1C ; case 103
	b _020E1EF0 ; case 104
	b _020E1D08 ; case 105
	b _020E1EF0 ; case 106
	b _020E1EF0 ; case 107
	b _020E1EF0 ; case 108
	b _020E1EF0 ; case 109
	b _020E1EF8 ; case 110
	b _020E1D08 ; case 111
	b _020E1D58 ; case 112
	b _020E1EF0 ; case 113
	b _020E1EF0 ; case 114
	b _020E1D90 ; case 115
	b _020E1EF0 ; case 116
	b _020E1D08 ; case 117
	b _020E1EF0 ; case 118
	b _020E1EF0 ; case 119
	b _020E1D08 ; case 120
_020E1D08:
	ldrb r0, [sp, #0x2]
	cmp r0, #0x9
	moveq r0, #0xff
	streqb r0, [sp, #0x3]
	b _020E1EF8
_020E1D1C:
	ldrb r1, [sp, #0x2]
	cmp r1, #0x1
	cmpne r1, #0x2
	beq _020E1D3C
	add r0, r1, #0xfc
	and r0, r0, #0xff
	cmp r0, #0x3
	bhi _020E1D48
_020E1D3C:
	mov r0, #0xff
	strb r0, [sp, #0x3]
	b _020E1EF8
_020E1D48:
	cmp r1, #0x3
	moveq r0, #0x8
	streqb r0, [sp, #0x2]
	b _020E1EF8
_020E1D58:
	mov r1, #0x3
	mov r0, #0x78
	strb r1, [sp, #0x2]
	strb r0, [sp, #0x3]
	b _020E1EF8
_020E1D6C:
	ldrb r0, [sp, #0x2]
	cmp r0, #0x3
	moveq r0, #0xa
	streqb r0, [sp, #0x2]
	beq _020E1EF8
	cmp r0, #0x0
	movne r0, #0xff
	strneb r0, [sp, #0x3]
	b _020E1EF8
_020E1D90:
	ldrb r0, [sp, #0x2]
	cmp r0, #0x3
	moveq r0, #0xa
	streqb r0, [sp, #0x2]
	beq _020E1DB0
	cmp r0, #0x0
	movne r0, #0xff
	strneb r0, [sp, #0x3]
_020E1DB0:
	add r2, sp, #0x8
	mov r1, #0x20
	mov r0, #0xff
_020E1DBC:
	sub r1, r1, #0x1
	cmp r1, #0x0
	strb r0, [r2], #0x1
	bgt _020E1DBC
	mov r1, #0xc1
	mov r0, #0xfe
	strb r1, [sp, #0x9]
	strb r0, [sp, #0xc]
	b _020E1EF8
_020E1DE0:
	ldrb r0, [sp, #0x2]
	cmp r0, #0x3
	moveq r0, #0xa
	streqb r0, [sp, #0x2]
	beq _020E1E00
	cmp r0, #0x0
	movne r0, #0xff
	strneb r0, [sp, #0x3]
_020E1E00:
	ldrsb r2, [r12, #0x1]!
	mov r1, #0x0
	cmp r2, #0x5e
	ldreqsb r2, [r12, #0x1]!
	moveq r1, #0x1
	cmp r2, #0x5d
	bne _020E1EA8
	ldrb r0, [sp, #0x13]
	orr r0, r0, #0x20
	strb r0, [sp, #0x13]
	ldrsb r2, [r12, #0x1]!
	b _020E1EA8
_020E1E30:
	add r0, sp, #0x0
	and r3, r2, #0xff
	add r6, r0, r3, asr #0x3
	ldrb r5, [r6, #0x8]
	and r3, r2, #0x7
	mov r4, #0x1
	orr r3, r5, r4, lsl r3
	strb r3, [r6, #0x8]
	ldrsb r3, [r12, #0x1]
	cmp r3, #0x2d
	bne _020E1EA4
	ldrsb r7, [r12, #0x2]
	cmp r7, #0x0
	cmpne r7, #0x5d
	beq _020E1EA4
	add r2, r2, #0x1
	cmp r2, r7
	bgt _020E1E9C
_020E1E78:
	and r3, r2, #0xff
	add r6, r0, r3, asr #0x3
	ldrb r5, [r6, #0x8]
	and r3, r2, #0x7
	add r2, r2, #0x1
	orr r3, r5, r4, lsl r3
	strb r3, [r6, #0x8]
	cmp r2, r7
	ble _020E1E78
_020E1E9C:
	ldrsb r2, [r12, #0x3]!
	b _020E1EA8
_020E1EA4:
	ldrsb r2, [r12, #0x1]!
_020E1EA8:
	cmp r2, #0x0
	cmpne r2, #0x5d
	bne _020E1E30
	cmp r2, #0x0
	moveq r0, #0xff
	streqb r0, [sp, #0x3]
	beq _020E1EF8
	cmp r1, #0x0
	beq _020E1EF8
	add r2, sp, #0x8
	mov r1, #0x20
_020E1ED4:
	ldrb r0, [r2, #0x0]
	sub r1, r1, #0x1
	cmp r1, #0x0
	mvn r0, r0
	strb r0, [r2], #0x1
	bgt _020E1ED4
	b _020E1EF8
_020E1EF0:
	mov r0, #0xff
	strb r0, [sp, #0x3]
_020E1EF8:
	add r4, sp, #0x0
	ldmia r4!, {r0-r3}
	stmia lr!, {r0-r3}
	ldmia r4!, {r0-r3}
	stmia lr!, {r0-r3}
	ldmia r4, {r0-r1}
	stmia lr, {r0-r1}
	add r0, r12, #0x1
	add sp, sp, #0x28
	ldmia sp!, {r3-r7,pc}
	.balign 4
_020E1F20: .word parse_format$f
_020E1F24: .word __msl_digit
    arm_func_end parse_format

	arm_func_start __sformatter
__sformatter: ; 0x020E1F28
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x88
	ldrsb r5, [r2, #0x0]
	str r2, [sp, #0xc]
	mov r2, #0x0
	mov r9, r0
	mov r0, r2
	str r2, [sp, #0x20]
	mov r8, r1
	str r3, [sp, #0x10]
	str r0, [sp, #0x24]
	cmp r5, #0x0
	ldr r10, [sp, #0xb0]
	str r0, [sp, #0x30]
	mov r4, r2
	str r0, [sp, #0x44]
	str r0, [sp, #0x40]
	beq _020E2C3C
_020E1F70:
	cmp r5, #0x0
	mov r0, #0x1
	blt _020E1F84
	cmp r5, #0x80
	movlt r0, #0x0
_020E1F84:
	cmp r0, #0x0
	movne r0, #0x0
	bne _020E1FA0
	mov r1, r5, lsl #0x1
	ldr r0, _020E2C74 ; =__msl_digit
	ldrh r0, [r0, r1]
	and r0, r0, #0x100
_020E1FA0:
	cmp r0, #0x0
	beq _020E2060
	mov r2, #0x0
	ldr r1, _020E2C74 ; =__msl_digit
	mov r12, r2
	mov r3, #0x1
_020E1FB8:
	ldr r0, [sp, #0xc]
	ldrsb r5, [r0, #0x1]!
	str r0, [sp, #0xc]
	mov r0, r3
	cmp r5, #0x0
	blt _020E1FD8
	cmp r5, #0x80
	movlt r0, r2
_020E1FD8:
	cmp r0, #0x0
	movne r0, r12
	moveq r0, r5, lsl #0x1
	ldreqh r0, [r1, r0]
	andeq r0, r0, #0x100
	cmp r0, #0x0
	bne _020E1FB8
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	bne _020E2C2C
	ldr r5, _020E2C74 ; =__msl_digit
	b _020E200C
_020E2008:
	add r4, r4, #0x1
_020E200C:
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	blx r9
	strb r0, [sp, #0x50]
	ldrsb r1, [sp, #0x50]
	cmp r1, #0x0
	blt _020E2034
	cmp r1, #0x80
	blt _020E203C
_020E2034:
	mov r0, #0x0
	b _020E2048
_020E203C:
	mov r0, r1, lsl #0x1
	ldrh r0, [r5, r0]
	and r0, r0, #0x100
_020E2048:
	cmp r0, #0x0
	bne _020E2008
	mov r0, r8
	mov r2, #0x1
	blx r9
	b _020E2C2C
_020E2060:
	cmp r5, #0x25
	beq _020E20D8
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	bne _020E20D8
	mov r0, r8
	mov r1, #0x0
	mov r2, r1
	blx r9
	strb r0, [sp, #0x50]
	and r0, r5, #0xff
	ldrsb r1, [sp, #0x50]
	cmp r0, r1
	beq _020E20C4
	mov r0, r8
	mov r2, #0x1
	blx r9
	cmp r10, #0x0
	beq _020E2C3C
	mov r0, #0x1
	str r0, [sp, #0x30]
	ldr r0, [sp, #0xc]
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	b _020E2C2C
_020E20C4:
	ldr r0, [sp, #0xc]
	add r4, r4, #0x1
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	b _020E2C2C
_020E20D8:
	ldr r0, [sp, #0xc]
	add r1, sp, #0x60
	bl parse_format
	str r0, [sp, #0xc]
	ldrb r0, [sp, #0x60]
	cmp r0, #0x0
	bne _020E2114
	ldrb r0, [sp, #0x63]
	cmp r0, #0x25
	beq _020E2114
	ldr r0, [sp, #0x10]
	add r0, r0, #0x4
	str r0, [sp, #0x10]
	ldr r5, [r0, #-0x4]
	b _020E2118
_020E2114:
	mov r5, #0x0
_020E2118:
	ldrb r0, [sp, #0x63]
	cmp r0, #0x6e
	beq _020E2158
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	bne _020E2158
	mov r0, r8
	mov r1, #0x0
	mov r2, #0x2
	blx r9
	cmp r0, #0x0
	beq _020E2158
	cmp r10, #0x0
	beq _020E2C3C
	mov r0, #0x1
	str r0, [sp, #0x30]
_020E2158:
	ldrb r1, [sp, #0x63]
	cmp r1, #0x5b
	bgt _020E21B0
	bge _020E2984
	cmp r1, #0x47
	bgt _020E21A4
	subs r0, r1, #0x41
	addpl pc, pc, r0, lsl #0x2
	b _020E2198
	b _020E2600 ; case 65
	b _020E2C3C ; case 66
	b _020E2C3C ; case 67
	b _020E2C3C ; case 68
	b _020E2600 ; case 69
	b _020E2600 ; case 70
	b _020E2600 ; case 71
_020E2198:
	cmp r1, #0x25
	beq _020E287C
	b _020E2C3C
_020E21A4:
	cmp r1, #0x58
	beq _020E243C
	b _020E2C3C
_020E21B0:
	cmp r1, #0x78
	bgt _020E2228
	subs r0, r1, #0x63
	addpl pc, pc, r0, lsl #0x2
	b _020E221C
	b _020E26C4 ; case 99
	b _020E2230 ; case 100
	b _020E2600 ; case 101
	b _020E2600 ; case 102
	b _020E2600 ; case 103
	b _020E2C3C ; case 104
	b _020E2238 ; case 105
	b _020E2C3C ; case 106
	b _020E2C3C ; case 107
	b _020E2C3C ; case 108
	b _020E2C3C ; case 109
	b _020E2BC8 ; case 110
	b _020E242C ; case 111
	b _020E2C3C ; case 112
	b _020E2C3C ; case 113
	b _020E2C3C ; case 114
	b _020E2908 ; case 115
	b _020E2C3C ; case 116
	b _020E2434 ; case 117
	b _020E2C3C ; case 118
	b _020E2C3C ; case 119
	b _020E243C ; case 120
_020E221C:
	cmp r1, #0x61
	beq _020E2600
	b _020E2C3C
_020E2228:
	cmp r1, #0xff
	b _020E2C3C
_020E2230:
	mov r0, #0xa
	b _020E223C
_020E2238:
	mov r0, #0x0
_020E223C:
	ldr r1, [sp, #0x30]
	cmp r1, #0x0
	beq _020E225C
	mov r0, #0x0
	str r0, [sp, #0x1c]
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
	b _020E2364
_020E225C:
	ldrb r1, [sp, #0x62]
	add r2, sp, #0x5c
	cmp r1, #0x7
	cmpne r1, #0x4
	add r1, sp, #0x58
	bne _020E22A0
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	add r1, sp, #0x54
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x64]
	mov r2, r9
	mov r3, r8
	bl __strtoull
	str r0, [sp, #0x34]
	str r1, [sp, #0x18]
	b _020E22C4
_020E22A0:
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	add r1, sp, #0x54
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x64]
	mov r2, r9
	mov r3, r8
	bl __strtoul
	str r0, [sp, #0x3c]
_020E22C4:
	ldr r0, [sp, #0x5c]
	cmp r0, #0x0
	bne _020E22F4
	cmp r10, #0x0
	beq _020E2C3C
	mov r0, #0x1
	str r0, [sp, #0x30]
	mov r0, #0x0
	str r0, [sp, #0x1c]
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
	b _020E2364
_020E22F4:
	add r4, r4, r0
	ldrb r0, [sp, #0x62]
	cmp r0, #0x7
	cmpne r0, #0x4
	bne _020E2344
	ldr r0, [sp, #0x58]
	cmp r0, #0x0
	beq _020E2330
	ldr r0, [sp, #0x34]
	rsbs r0, r0, #0x0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	rsc r0, r0, #0x0
	str r0, [sp, #0x24]
	b _020E2364
_020E2330:
	ldr r0, [sp, #0x34]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x24]
	b _020E2364
_020E2344:
	ldr r0, [sp, #0x58]
	cmp r0, #0x0
	ldreq r0, [sp, #0x3c]
	streq r0, [sp, #0x1c]
	beq _020E2364
	ldr r0, [sp, #0x3c]
	rsb r0, r0, #0x0
	str r0, [sp, #0x1c]
_020E2364:
	cmp r5, #0x0
	beq _020E241C
	ldrb r0, [sp, #0x62]
	cmp r0, #0x7
	addls pc, pc, r0, lsl #0x2
	b _020E2408
	b _020E239C ; case 0
	b _020E23A8 ; case 1
	b _020E23B4 ; case 2
	b _020E23C0 ; case 3
	b _020E23CC ; case 4
	b _020E23E0 ; case 5
	b _020E23EC ; case 6
	b _020E23F8 ; case 7
_020E239C:
	ldr r0, [sp, #0x1c]
	str r0, [r5, #0x0]
	b _020E2408
_020E23A8:
	ldr r0, [sp, #0x1c]
	strb r0, [r5, #0x0]
	b _020E2408
_020E23B4:
	ldr r0, [sp, #0x1c]
	strh r0, [r5, #0x0]
	b _020E2408
_020E23C0:
	ldr r0, [sp, #0x1c]
	str r0, [r5, #0x0]
	b _020E2408
_020E23CC:
	ldr r0, [sp, #0x20]
	str r0, [r5, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x4]
	b _020E2408
_020E23E0:
	ldr r0, [sp, #0x1c]
	str r0, [r5, #0x0]
	b _020E2408
_020E23EC:
	ldr r0, [sp, #0x1c]
	str r0, [r5, #0x0]
	b _020E2408
_020E23F8:
	ldr r0, [sp, #0x20]
	str r0, [r5, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x4]
_020E2408:
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	ldreq r0, [sp, #0x44]
	addeq r0, r0, #0x1
	streq r0, [sp, #0x44]
_020E241C:
	ldr r0, [sp, #0x40]
	add r0, r0, #0x1
	str r0, [sp, #0x40]
	b _020E2C2C
_020E242C:
	mov r0, #0x8
	b _020E2440
_020E2434:
	mov r0, #0xa
	b _020E2440
_020E243C:
	mov r0, #0x10
_020E2440:
	ldr r1, [sp, #0x30]
	cmp r1, #0x0
	beq _020E2460
	mov r0, #0x0
	str r0, [sp, #0x3c]
	str r0, [sp, #0x34]
	str r0, [sp, #0x18]
	b _020E2538
_020E2460:
	ldrb r1, [sp, #0x62]
	add r2, sp, #0x5c
	cmp r1, #0x7
	cmpne r1, #0x4
	add r1, sp, #0x58
	bne _020E24A4
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	add r1, sp, #0x54
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x64]
	mov r2, r9
	mov r3, r8
	bl __strtoull
	str r0, [sp, #0x34]
	str r1, [sp, #0x18]
	b _020E24C8
_020E24A4:
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	add r1, sp, #0x54
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x64]
	mov r2, r9
	mov r3, r8
	bl __strtoul
	str r0, [sp, #0x3c]
_020E24C8:
	ldr r0, [sp, #0x5c]
	cmp r0, #0x0
	bne _020E24F8
	cmp r10, #0x0
	beq _020E2C3C
	mov r0, #0x1
	str r0, [sp, #0x30]
	mov r0, #0x0
	str r0, [sp, #0x3c]
	str r0, [sp, #0x34]
	str r0, [sp, #0x18]
	b _020E2538
_020E24F8:
	add r4, r4, r0
	ldr r0, [sp, #0x58]
	cmp r0, #0x0
	beq _020E2538
	ldrb r0, [sp, #0x62]
	cmp r0, #0x7
	ldrne r0, [sp, #0x3c]
	rsbne r0, r0, #0x0
	strne r0, [sp, #0x3c]
	bne _020E2538
	ldr r0, [sp, #0x34]
	rsbs r0, r0, #0x0
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x18]
	rsc r0, r0, #0x0
	str r0, [sp, #0x18]
_020E2538:
	cmp r5, #0x0
	beq _020E25F0
	ldrb r0, [sp, #0x62]
	cmp r0, #0x7
	addls pc, pc, r0, lsl #0x2
	b _020E25DC
	b _020E2570 ; case 0
	b _020E257C ; case 1
	b _020E2588 ; case 2
	b _020E2594 ; case 3
	b _020E25A0 ; case 4
	b _020E25B4 ; case 5
	b _020E25C0 ; case 6
	b _020E25CC ; case 7
_020E2570:
	ldr r0, [sp, #0x3c]
	str r0, [r5, #0x0]
	b _020E25DC
_020E257C:
	ldr r0, [sp, #0x3c]
	strb r0, [r5, #0x0]
	b _020E25DC
_020E2588:
	ldr r0, [sp, #0x3c]
	strh r0, [r5, #0x0]
	b _020E25DC
_020E2594:
	ldr r0, [sp, #0x3c]
	str r0, [r5, #0x0]
	b _020E25DC
_020E25A0:
	ldr r0, [sp, #0x34]
	str r0, [r5, #0x0]
	ldr r0, [sp, #0x18]
	str r0, [r5, #0x4]
	b _020E25DC
_020E25B4:
	ldr r0, [sp, #0x3c]
	str r0, [r5, #0x0]
	b _020E25DC
_020E25C0:
	ldr r0, [sp, #0x3c]
	str r0, [r5, #0x0]
	b _020E25DC
_020E25CC:
	ldr r0, [sp, #0x34]
	str r0, [r5, #0x0]
	ldr r0, [sp, #0x18]
	str r0, [r5, #0x4]
_020E25DC:
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	ldreq r0, [sp, #0x44]
	addeq r0, r0, #0x1
	streq r0, [sp, #0x44]
_020E25F0:
	ldr r0, [sp, #0x40]
	add r0, r0, #0x1
	str r0, [sp, #0x40]
	b _020E2C2C
_020E2600:
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	beq _020E261C
	ldr r0, _020E2C78 ; =__float_nan
	ldr r0, [r0, #0x0]
	bl _f2d
	b _020E2668
_020E261C:
	add r0, sp, #0x54
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x64]
	mov r1, r9
	mov r2, r8
	add r3, sp, #0x5c
	bl __strtold
	ldr r2, [sp, #0x5c]
	cmp r2, #0x0
	bne _020E2664
	cmp r10, #0x0
	beq _020E2C3C
	mov r0, #0x1
	str r0, [sp, #0x30]
	ldr r0, _020E2C78 ; =__float_nan
	ldr r0, [r0, #0x0]
	bl _f2d
	b _020E2668
_020E2664:
	add r4, r4, r2
_020E2668:
	cmp r5, #0x0
	beq _020E26B4
	ldrb r2, [sp, #0x62]
	cmp r2, #0x0
	beq _020E2690
	cmp r2, #0x8
	beq _020E269C
	cmp r2, #0x9
	stmeqia r5, {r0-r1}
	b _020E26A0
_020E2690:
	bl _d2f
	str r0, [r5, #0x0]
	b _020E26A0
_020E269C:
	stmia r5, {r0-r1}
_020E26A0:
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	ldreq r0, [sp, #0x44]
	addeq r0, r0, #0x1
	streq r0, [sp, #0x44]
_020E26B4:
	ldr r0, [sp, #0x40]
	add r0, r0, #0x1
	str r0, [sp, #0x40]
	b _020E2C2C
_020E26C4:
	ldrb r0, [sp, #0x61]
	cmp r0, #0x0
	moveq r0, #0x1
	streq r0, [sp, #0x64]
	cmp r5, #0x0
	beq _020E280C
	cmp r10, #0x0
	beq _020E26F8
	ldr r0, [sp, #0x10]
	mov r7, #0x1
	add r0, r0, #0x4
	ldr r11, [r0, #-0x4]
	str r0, [sp, #0x10]
_020E26F8:
	ldr r0, [sp, #0x30]
	mov r1, #0x0
	cmp r0, #0x0
	str r1, [sp, #0x5c]
	beq _020E2718
	cmp r11, #0x0
	strneb r1, [r5, #0x0]
	b _020E2C2C
_020E2718:
	mvn r0, #0x0
	str r5, [sp, #0x2c]
	str r0, [sp, #0x48]
	b _020E2760
_020E2728:
	ldrb r0, [sp, #0x62]
	strb r6, [sp, #0x50]
	cmp r0, #0xa
	ldrnesb r0, [sp, #0x50]
	strneb r0, [r5], #0x1
	bne _020E2754
	mov r0, r5
	add r1, sp, #0x50
	mov r2, #0x1
	bl mbtowc
	add r5, r5, #0x1
_020E2754:
	ldr r0, [sp, #0x5c]
	add r1, r0, #0x1
	str r1, [sp, #0x5c]
_020E2760:
	ldr r0, [sp, #0x64]
	cmp r0, #0x0
	sub r0, r0, #0x1
	str r0, [sp, #0x64]
	beq _020E27B0
	cmp r10, #0x0
	beq _020E2790
	cmp r11, r1
	movhi r7, #0x1
	movls r7, #0x0
	cmp r7, #0x0
	beq _020E27B0
_020E2790:
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	blx r9
	mov r6, r0
	ldr r0, [sp, #0x48]
	cmp r6, r0
	bne _020E2728
_020E27B0:
	strb r6, [sp, #0x50]
	ldr r0, [sp, #0x5c]
	cmp r0, #0x0
	beq _020E27D0
	cmp r10, #0x0
	beq _020E27F8
	cmp r7, #0x0
	bne _020E27F8
_020E27D0:
	cmp r10, #0x0
	beq _020E2C3C
	mov r0, #0x1
	cmp r11, #0x0
	str r0, [sp, #0x30]
	beq _020E2C2C
	ldr r0, [sp, #0x2c]
	mov r1, #0x0
	strb r1, [r0, #0x0]
	b _020E2C2C
_020E27F8:
	add r4, r4, r0
	ldr r0, [sp, #0x44]
	add r0, r0, #0x1
	str r0, [sp, #0x44]
	b _020E286C
_020E280C:
	mov r0, #0x0
	str r0, [sp, #0x5c]
	mvn r5, #0x0
	b _020E282C
_020E281C:
	strb r6, [sp, #0x50]
	ldr r0, [sp, #0x5c]
	add r0, r0, #0x1
	str r0, [sp, #0x5c]
_020E282C:
	ldr r0, [sp, #0x64]
	cmp r0, #0x0
	sub r0, r0, #0x1
	str r0, [sp, #0x64]
	beq _020E285C
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	blx r9
	mov r6, r0
	cmp r6, r5
	bne _020E281C
_020E285C:
	strb r6, [sp, #0x50]
	ldr r0, [sp, #0x5c]
	cmp r0, #0x0
	beq _020E2C3C
_020E286C:
	ldr r0, [sp, #0x40]
	add r0, r0, #0x1
	str r0, [sp, #0x40]
	b _020E2C2C
_020E287C:
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	bne _020E2C2C
	ldr r5, _020E2C74 ; =__msl_digit
	b _020E2894
_020E2890:
	add r4, r4, #0x1
_020E2894:
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	blx r9
	strb r0, [sp, #0x50]
	ldrsb r1, [sp, #0x50]
	cmp r1, #0x0
	blt _020E28BC
	cmp r1, #0x80
	blt _020E28C4
_020E28BC:
	mov r0, #0x0
	b _020E28D0
_020E28C4:
	mov r0, r1, lsl #0x1
	ldrh r0, [r5, r0]
	and r0, r0, #0x100
_020E28D0:
	cmp r0, #0x0
	bne _020E2890
	cmp r1, #0x25
	beq _020E2900
	mov r0, r8
	mov r2, #0x1
	blx r9
	cmp r10, #0x0
	beq _020E2C3C
	mov r0, #0x1
	str r0, [sp, #0x30]
	b _020E2C2C
_020E2900:
	add r4, r4, #0x1
	b _020E2C2C
_020E2908:
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	bne _020E2984
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	blx r9
	strb r0, [sp, #0x50]
	b _020E2944
_020E292C:
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r4, r4, #0x1
	blx r9
	strb r0, [sp, #0x50]
_020E2944:
	ldrsb r1, [sp, #0x50]
	cmp r1, #0x0
	blt _020E2958
	cmp r1, #0x80
	blt _020E2960
_020E2958:
	mov r0, #0x0
	b _020E2970
_020E2960:
	ldr r0, _020E2C74 ; =__msl_digit
	mov r2, r1, lsl #0x1
	ldrh r0, [r0, r2]
	and r0, r0, #0x100
_020E2970:
	cmp r0, #0x0
	bne _020E292C
	mov r0, r8
	mov r2, #0x1
	blx r9
_020E2984:
	cmp r5, #0x0
	beq _020E2B00
	cmp r10, #0x0
	beq _020E29AC
	ldr r0, [sp, #0x10]
	mov r7, #0x1
	add r0, r0, #0x4
	str r0, [sp, #0x10]
	ldr r0, [r0, #-0x4]
	sub r11, r0, #0x1
_020E29AC:
	ldr r0, [sp, #0x30]
	mov r1, #0x0
	cmp r0, #0x0
	str r1, [sp, #0x5c]
	beq _020E29CC
	cmp r11, #0x0
	strneb r1, [r5, #0x0]
	b _020E2C2C
_020E29CC:
	mvn r0, #0x0
	str r5, [sp, #0x28]
	str r0, [sp, #0x4c]
	b _020E2A30
_020E29DC:
	strb r6, [sp, #0x50]
	ldrsb r1, [sp, #0x50]
	add r2, sp, #0x60
	and r3, r1, #0xff
	add r2, r2, r3, asr #0x3
	ldrb r3, [r2, #0x8]
	and r0, r1, #0x7
	mov r2, #0x1
	tst r3, r2, lsl r0
	beq _020E2A80
	ldrb r0, [sp, #0x62]
	cmp r0, #0xa
	strneb r1, [r5], #0x1
	bne _020E2A24
	mov r0, r5
	add r1, sp, #0x50
	bl mbtowc
	add r5, r5, #0x2
_020E2A24:
	ldr r0, [sp, #0x5c]
	add r1, r0, #0x1
	str r1, [sp, #0x5c]
_020E2A30:
	ldr r0, [sp, #0x64]
	cmp r0, #0x0
	sub r0, r0, #0x1
	str r0, [sp, #0x64]
	beq _020E2A80
	cmp r10, #0x0
	beq _020E2A60
	cmp r11, r1
	movcs r7, #0x1
	movcc r7, #0x0
	cmp r7, #0x0
	beq _020E2A80
_020E2A60:
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	blx r9
	mov r6, r0
	ldr r0, [sp, #0x4c]
	cmp r6, r0
	bne _020E29DC
_020E2A80:
	strb r6, [sp, #0x50]
	ldr r0, [sp, #0x5c]
	cmp r0, #0x0
	beq _020E2AA0
	cmp r10, #0x0
	beq _020E2AD8
	cmp r7, #0x0
	bne _020E2AD8
_020E2AA0:
	mov r0, r8
	ldrsb r1, [sp, #0x50]
	mov r2, #0x1
	blx r9
	cmp r10, #0x0
	beq _020E2C3C
	mov r0, #0x1
	cmp r11, #0x0
	str r0, [sp, #0x30]
	beq _020E2C2C
	ldr r0, [sp, #0x28]
	mov r1, #0x0
	strb r1, [r0, #0x0]
	b _020E2C2C
_020E2AD8:
	add r4, r4, r0
	ldrb r0, [sp, #0x62]
	cmp r0, #0xa
	mov r0, #0x0
	streqh r0, [r5, #0x0]
	strneb r0, [r5, #0x0]
	ldr r0, [sp, #0x44]
	add r0, r0, #0x1
	str r0, [sp, #0x44]
	b _020E2B9C
_020E2B00:
	mov r0, #0x0
	str r0, [sp, #0x5c]
	mvn r5, #0x0
	b _020E2B44
_020E2B10:
	strb r6, [sp, #0x50]
	ldrsb r1, [sp, #0x50]
	and r0, r1, #0x7
	and r2, r1, #0xff
	add r1, sp, #0x60
	add r1, r1, r2, asr #0x3
	ldrb r2, [r1, #0x8]
	mov r1, #0x1
	tst r2, r1, lsl r0
	beq _020E2B74
	ldr r0, [sp, #0x5c]
	add r0, r0, #0x1
	str r0, [sp, #0x5c]
_020E2B44:
	ldr r0, [sp, #0x64]
	cmp r0, #0x0
	sub r0, r0, #0x1
	str r0, [sp, #0x64]
	beq _020E2B74
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	blx r9
	mov r6, r0
	cmp r6, r5
	bne _020E2B10
_020E2B74:
	strb r6, [sp, #0x50]
	ldr r0, [sp, #0x5c]
	cmp r0, #0x0
	bne _020E2B98
	mov r0, r8
	ldrsb r1, [sp, #0x50]
	mov r2, #0x1
	blx r9
	b _020E2C2C
_020E2B98:
	add r4, r4, r0
_020E2B9C:
	ldr r0, [sp, #0x64]
	cmp r0, #0x0
	blt _020E2BB8
	mov r0, r8
	ldrsb r1, [sp, #0x50]
	mov r2, #0x1
	blx r9
_020E2BB8:
	ldr r0, [sp, #0x40]
	add r0, r0, #0x1
	str r0, [sp, #0x40]
	b _020E2C2C
_020E2BC8:
	cmp r5, #0x0
	beq _020E2C2C
	ldrb r0, [sp, #0x62]
	cmp r0, #0x7
	addls pc, pc, r0, lsl #0x2
	b _020E2C2C
	b _020E2C00 ; case 0
	b _020E2C18 ; case 1
	b _020E2C08 ; case 2
	b _020E2C10 ; case 3
	b _020E2C2C ; case 4
	b _020E2C2C ; case 5
	b _020E2C2C ; case 6
	b _020E2C20 ; case 7
_020E2C00:
	str r4, [r5, #0x0]
	b _020E2C2C
_020E2C08:
	strh r4, [r5, #0x0]
	b _020E2C2C
_020E2C10:
	str r4, [r5, #0x0]
	b _020E2C2C
_020E2C18:
	strb r4, [r5, #0x0]
	b _020E2C2C
_020E2C20:
	str r4, [r5, #0x0]
	mov r0, r4, asr #0x1f
	str r0, [r5, #0x4]
_020E2C2C:
	ldr r0, [sp, #0xc]
	ldrsb r5, [r0, #0x0]
	cmp r5, #0x0
	bne _020E1F70
_020E2C3C:
	mov r0, r8
	mov r1, #0x0
	mov r2, #0x2
	blx r9
	cmp r0, #0x0
	beq _020E2C68
	ldr r0, [sp, #0x40]
	cmp r0, #0x0
	addeq sp, sp, #0x88
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,pc}
_020E2C68:
	ldr r0, [sp, #0x44]
	add sp, sp, #0x88
	ldmia sp!, {r3-r11,pc}
	.balign 4
_020E2C74: .word __msl_digit
_020E2C78: .word __float_nan
    arm_func_end __sformatter

	arm_func_start __StringRead
__StringRead: ; 0x020E2C7C
	cmp r2, #0x0
	beq _020E2C98
	cmp r2, #0x1
	beq _020E2CC8
	cmp r2, #0x2
	beq _020E2CF0
	b _020E2CF8
_020E2C98:
	ldr r1, [r0, #0x0]
	ldrsb r2, [r1, #0x0]
	cmp r2, #0x0
	bne _020E2CB8
	mov r1, #0x1
	str r1, [r0, #0x4]
	sub r0, r1, #0x2
	bx lr
_020E2CB8:
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	and r0, r2, #0xff
	bx lr
_020E2CC8:
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	movne r2, #0x0
	strne r2, [r0, #0x4]
	bne _020E2CE8
	ldr r2, [r0, #0x0]
	sub r2, r2, #0x1
	str r2, [r0, #0x0]
_020E2CE8:
	mov r0, r1
	bx lr
_020E2CF0:
	ldr r0, [r0, #0x4]
	bx lr
_020E2CF8:
	mov r0, #0x0
	bx lr
    arm_func_end __StringRead

	arm_func_start vsscanf
vsscanf: ; 0x020E2D00
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	str r0, [sp, #0x4]
	cmp r0, #0x0
	ldrnesb r0, [r0, #0x0]
	mov lr, r1
	mov r3, r2
	cmpne r0, #0x0
	addeq sp, sp, #0xc
	mvneq r0, #0x0
	ldmeqia sp!, {pc}
	mov r12, #0x0
	str r12, [sp, #0x8]
	ldr r0, _020E2D50 ; =__StringRead
	add r1, sp, #0x4
	mov r2, lr
	str r12, [sp, #0x0]
	bl __sformatter
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.balign 4
_020E2D50: .word __StringRead
    arm_func_end vsscanf

	arm_func_start sscanf
sscanf: ; 0x020E2D54
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3,lr}
	add r2, sp, #0xc
	bic r2, r2, #0x3
	ldr r1, [sp, #0xc]
	add r2, r2, #0x4
	bl vsscanf
	ldmia sp!, {r3,lr}
	add sp, sp, #0x10
	bx lr
    arm_func_end sscanf
