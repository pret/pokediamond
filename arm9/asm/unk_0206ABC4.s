    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020F8010
UNK_020F8010: ; 0x020F8010
	.byte 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x02
	.byte 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02
	.byte 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00
	.byte 0x01, 0x00, 0x02, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00
	.byte 0x01, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_0206ABC4
FUN_0206ABC4: ; 0x0206ABC4
	push {r3-r7, lr}
	sub sp, #0x48
	str r2, [sp, #0x4]
	ldr r2, _0206AC70 ; =0x0000022F
	str r0, [sp, #0x0]
	add r4, r1, #0x0
	ldr r3, [sp, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl FUN_0200A86C
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	bl FUN_02024EC0
	bl FUN_02024EE8
	ldr r4, [sp, #0x0]
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r5, r4, #0x0
	mov r7, #0x0
	str r0, [sp, #0x8]
	add r5, #0x3c
_0206ABF4:
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _0206AC48
	add r1, sp, #0x14
	bl FUN_0206ADE0
	ldr r3, [sp, #0x8]
	add r6, sp, #0x14
	add r3, #0x28
	mov r2, #0x6
_0206AC08:
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0206AC08
	ldr r0, [r6, #0x0]
	str r0, [r3, #0x0]
	add r0, sp, #0x14
	ldrb r0, [r0, #0x1]
	cmp r0, #0x3f
	bne _0206AC26
	ldr r1, [sp, #0xc]
	add r0, r5, #0x0
	bl StringCopy
	b _0206AC3E
_0206AC26:
	ldr r0, [sp, #0x10]
	ldr r1, [r4, #0x18]
	bl FUN_0200A914
	add r6, r0, #0x0
	add r1, r5, #0x0
	mov r2, #0x8
	bl FUN_02021EF0
	add r0, r6, #0x0
	bl FUN_02021A20
_0206AC3E:
	ldr r0, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r1, r7, #0x0
	bl FUN_0206AE0C
_0206AC48:
	ldr r0, [sp, #0x8]
	add r7, r7, #0x1
	add r0, #0x34
	add r4, r4, #0x4
	add r5, #0x34
	str r0, [sp, #0x8]
	cmp r7, #0x4
	blt _0206ABF4
	ldr r0, [sp, #0x0]
	ldr r1, [r0, #0x0]
	ldr r0, [sp, #0x24]
	orr r1, r0
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x10]
	bl FUN_0200A8B8
	add sp, #0x48
	pop {r3-r7, pc}
	nop
_0206AC70: .word 0x0000022F

	thumb_func_start FUN_0206AC74
FUN_0206AC74: ; 0x0206AC74
	push {r4-r5, lr}
	sub sp, #0x34
	add r5, r1, #0x0
	add r1, sp, #0x0
	bl FUN_0206ADE0
	cmp r5, #0x9
	bhi _0206ACCC
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0206AC90: ; jump table (using 16-bit offset)
	.short _0206ACA4 - _0206AC90 - 2; case 0
	.short _0206ACAA - _0206AC90 - 2; case 1
	.short _0206ACB0 - _0206AC90 - 2; case 2
	.short _0206ACB6 - _0206AC90 - 2; case 3
	.short _0206ACBC - _0206AC90 - 2; case 4
	.short _0206ACBC - _0206AC90 - 2; case 5
	.short _0206ACBC - _0206AC90 - 2; case 6
	.short _0206ACBC - _0206AC90 - 2; case 7
	.short _0206ACC6 - _0206AC90 - 2; case 8
	.short _0206ACCA - _0206AC90 - 2; case 9
_0206ACA4:
	add r0, sp, #0x0
	ldrb r4, [r0, #0x0]
	b _0206ACCC
_0206ACAA:
	add r0, sp, #0x0
	ldrb r4, [r0, #0x1]
	b _0206ACCC
_0206ACB0:
	add r0, sp, #0x0
	ldrb r4, [r0, #0x2]
	b _0206ACCC
_0206ACB6:
	add r0, sp, #0x0
	ldrb r4, [r0, #0x3]
	b _0206ACCC
_0206ACBC:
	sub r0, r5, #0x4
	lsl r1, r0, #0x1
	add r0, sp, #0x4
	ldrh r4, [r0, r1]
	b _0206ACCC
_0206ACC6:
	ldr r4, [sp, #0xc]
	b _0206ACCC
_0206ACCA:
	ldr r4, [sp, #0x10]
_0206ACCC:
	add r0, r4, #0x0
	add sp, #0x34
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_0206ACD4
FUN_0206ACD4: ; 0x0206ACD4
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x4]
	add r7, r1, #0x0
	ldr r1, [sp, #0x4]
	mov r0, #0x3b
	add r4, r2, #0x0
	bl GetNarcMemberSizeByIdPair
	add r6, r0, #0x0
	mov r0, #0x2
	str r0, [sp, #0x0]
	add r0, sp, #0xc
	mov r1, #0x89
	mov r2, #0x0
	lsl r3, r5, #0x1
	bl ReadFromNarcMemberByIdPair
	mov r0, #0x3b
	add r1, r4, #0x0
	bl NARC_ctor
	add r4, sp, #0xc
	ldrh r2, [r4, #0x0]
	str r0, [sp, #0x8]
	cmp r2, r6
	beq _0206AD40
_0206AD0E:
	add r0, sp, #0xc
	add r0, #0x2
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	mov r3, #0x4
	bl NARC_ReadFromMember
	ldrh r1, [r4, #0x2]
	cmp r1, r5
	bne _0206AD30
	ldrh r0, [r4, #0x4]
	cmp r0, r7
	bne _0206AD30
	mov r0, #0x1
	str r0, [sp, #0x4]
	b _0206AD40
_0206AD30:
	cmp r1, r5
	bne _0206AD40
	ldrh r0, [r4, #0x0]
	add r0, r0, #0x4
	strh r0, [r4, #0x0]
	ldrh r2, [r4, #0x0]
	cmp r2, r6
	bne _0206AD0E
_0206AD40:
	ldr r0, [sp, #0x8]
	bl NARC_dtor
	ldr r0, [sp, #0x4]
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_0206AD4C
FUN_0206AD4C: ; 0x0206AD4C
	push {r3-r7, lr}
	sub sp, #0x18
	add r6, r0, #0x0
	add r7, r1, #0x0
	mov r0, #0x3b
	mov r1, #0x0
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	bl GetNarcMemberSizeByIdPair
	add r5, r0, #0x0
	mov r0, #0x2
	str r0, [sp, #0x0]
	add r0, sp, #0x10
	mov r1, #0x89
	mov r2, #0x0
	lsl r3, r6, #0x1
	bl ReadFromNarcMemberByIdPair
	ldr r1, [sp, #0x8]
	mov r0, #0x3b
	bl NARC_ctor
	add r4, sp, #0x10
	ldrh r2, [r4, #0x0]
	str r0, [sp, #0xc]
	cmp r2, r5
	beq _0206ADC2
_0206AD84:
	add r0, sp, #0x10
	add r0, #0x2
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xc]
	mov r1, #0x0
	mov r3, #0x4
	bl NARC_ReadFromMember
	ldrh r0, [r4, #0x2]
	cmp r0, r6
	bne _0206ADB6
	ldrh r0, [r4, #0x4]
	cmp r0, r7
	bne _0206ADB6
	ldr r0, [sp, #0x4]
	add r2, sp, #0x10
	str r0, [sp, #0x0]
	ldrh r2, [r2, #0x0]
	ldr r1, _0206ADDC ; =0x0000022E
	ldr r3, [sp, #0x8]
	mov r0, #0x1a
	lsr r2, r2, #0x2
	bl FUN_0200A648
	b _0206ADC2
_0206ADB6:
	ldrh r0, [r4, #0x0]
	add r0, r0, #0x4
	strh r0, [r4, #0x0]
	ldrh r2, [r4, #0x0]
	cmp r2, r5
	bne _0206AD84
_0206ADC2:
	ldr r0, [sp, #0xc]
	bl NARC_dtor
	add r0, sp, #0x10
	ldrh r0, [r0, #0x0]
	cmp r0, r5
	bne _0206ADD6
	ldr r0, [sp, #0x4]
	bl FUN_02021A4C
_0206ADD6:
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_0206ADDC: .word 0x0000022E

	thumb_func_start FUN_0206ADE0
FUN_0206ADE0: ; 0x0206ADE0
	ldr r3, _0206ADEC ; =ReadWholeNarcMemberByIdPair
	add r2, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x39
	bx r3
	nop
_0206ADEC: .word ReadWholeNarcMemberByIdPair

	thumb_func_start FUN_0206ADF0
FUN_0206ADF0: ; 0x0206ADF0
	ldr r3, _0206ADFC ; =ReadWholeNarcMemberByIdPair
	add r2, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x3a
	bx r3
	nop
_0206ADFC: .word ReadWholeNarcMemberByIdPair

	thumb_func_start FUN_0206AE00
FUN_0206AE00: ; 0x0206AE00
	ldr r1, _0206AE08 ; =UNK_020F8010
	ldrb r0, [r1, r0]
	bx lr
	nop
_0206AE08: .word UNK_020F8010

	thumb_func_start FUN_0206AE0C
FUN_0206AE0C: ; 0x0206AE0C
	push {r3-r7, lr}
	sub sp, #0x50
	add r7, r1, #0x0
	add r4, r0, #0x0
	add r5, r2, #0x0
	bl getseed_LC
	lsl r6, r7, #0x2
	str r0, [sp, #0x44]
	add r0, r4, r6
	ldr r0, [r0, #0x4]
	mov r1, #0x6
	bl FUN_0206B8CC
	add r0, r5, #0x0
	mov r1, #0x60
	bl AllocFromHeap
	str r0, [sp, #0x4c]
	add r0, r5, #0x0
	bl FUN_020669C0
	str r0, [sp, #0x40]
	add r0, r4, r6
	ldr r0, [r0, #0x18]
	ldr r1, [sp, #0x4c]
	bl FUN_0206ADF0
	mov r0, #0x34
	add r5, r7, #0x0
	mul r5, r0
	add r0, r4, r5
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	bl FUN_0206AE00
	cmp r0, #0x1
	bne _0206AE5E
	mov r0, #0x78
	str r0, [sp, #0x10]
	b _0206AE62
_0206AE5E:
	mov r0, #0x88
	str r0, [sp, #0x10]
_0206AE62:
	add r0, r4, r5
	add r0, #0x28
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	bhi _0206AF26
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0206AE78: ; jump table (using 16-bit offset)
	.short _0206AE80 - _0206AE78 - 2; case 0
	.short _0206AF28 - _0206AE78 - 2; case 1
	.short _0206AFE8 - _0206AE78 - 2; case 2
	.short _0206B08C - _0206AE78 - 2; case 3
_0206AE80:
	mov r0, #0x0
	str r0, [sp, #0x48]
	add r0, r4, r5
	add r0, #0x2b
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	ble _0206AF26
	ldr r0, [sp, #0x4c]
	str r0, [sp, #0x28]
	add r0, r4, r6
	str r0, [sp, #0x24]
_0206AE96:
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x28]
	ldr r1, [r0, #0x18]
	ldr r0, [sp, #0x28]
	ldrh r3, [r2, #0x0]
	ldrh r2, [r2, #0x2]
	ldrh r0, [r0, #0x4]
	add r2, r3, r2
	add r0, r0, r2
	add r7, r1, r0
	add r0, r7, #0x0
	bl seedr_LC
	add r0, r4, r5
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0206AECE
_0206AEBC:
	bl rand_LC
	add r7, r0, #0x0
	add r0, r4, r5
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	add r6, r6, #0x1
	cmp r6, r0
	blt _0206AEBC
_0206AECE:
	ldr r0, [sp, #0x10]
	lsl r1, r7, #0x8
	add r6, r1, r0
	ldr r0, [sp, #0x28]
	ldrh r1, [r0, #0x0]
	mov r0, #0x1f
	mul r0, r1
	mov r1, #0xff
	bl _s32_div_f
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	lsl r3, r3, #0x18
	str r6, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x28]
	ldrh r1, [r1, #0x4]
	ldrh r2, [r2, #0x2]
	ldr r0, [sp, #0x40]
	lsr r3, r3, #0x18
	bl CreateMon
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x40]
	ldr r0, [r0, #0x4]
	bl FUN_0206B900
	ldr r0, [sp, #0x28]
	add r0, r0, #0x6
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
	add r0, r4, r5
	add r0, #0x2b
	ldrb r1, [r0, #0x0]
	ldr r0, [sp, #0x48]
	cmp r0, r1
	blt _0206AE96
_0206AF26:
	b _0206B156
_0206AF28:
	mov r0, #0x0
	str r0, [sp, #0x18]
	add r0, r4, r5
	add r0, #0x2b
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	ble _0206AFE6
	ldr r0, [sp, #0x4c]
	str r0, [sp, #0x30]
	add r0, r4, r6
	str r0, [sp, #0x2c]
_0206AF3E:
	ldr r0, [sp, #0x2c]
	ldr r2, [sp, #0x30]
	ldr r1, [r0, #0x18]
	ldr r0, [sp, #0x30]
	ldrh r3, [r2, #0x0]
	ldrh r2, [r2, #0x2]
	ldrh r0, [r0, #0x4]
	add r2, r3, r2
	add r0, r0, r2
	add r7, r1, r0
	add r0, r7, #0x0
	bl seedr_LC
	add r0, r4, r5
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0206AF76
_0206AF64:
	bl rand_LC
	add r7, r0, #0x0
	add r0, r4, r5
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	add r6, r6, #0x1
	cmp r6, r0
	blt _0206AF64
_0206AF76:
	ldr r0, [sp, #0x10]
	lsl r1, r7, #0x8
	add r6, r1, r0
	ldr r0, [sp, #0x30]
	ldrh r1, [r0, #0x0]
	mov r0, #0x1f
	mul r0, r1
	mov r1, #0xff
	bl _s32_div_f
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	lsl r3, r3, #0x18
	str r6, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x30]
	ldrh r1, [r1, #0x4]
	ldrh r2, [r2, #0x2]
	ldr r0, [sp, #0x40]
	lsr r3, r3, #0x18
	bl CreateMon
	ldr r7, [sp, #0x30]
	mov r6, #0x0
_0206AFB0:
	ldrh r1, [r7, #0x6]
	lsl r2, r6, #0x18
	ldr r0, [sp, #0x40]
	lsr r2, r2, #0x18
	bl FUN_020697CC
	add r6, r6, #0x1
	add r7, r7, #0x2
	cmp r6, #0x4
	blt _0206AFB0
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x40]
	ldr r0, [r0, #0x4]
	bl FUN_0206B900
	ldr r0, [sp, #0x30]
	add r0, #0xe
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x18]
	add r0, r0, #0x1
	str r0, [sp, #0x18]
	add r0, r4, r5
	add r0, #0x2b
	ldrb r1, [r0, #0x0]
	ldr r0, [sp, #0x18]
	cmp r0, r1
	blt _0206AF3E
_0206AFE6:
	b _0206B156
_0206AFE8:
	mov r0, #0x0
	str r0, [sp, #0x1c]
	add r0, r4, r5
	add r0, #0x2b
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	ble _0206B08A
	add r0, r4, r6
	ldr r7, [sp, #0x4c]
	str r0, [sp, #0x34]
_0206AFFC:
	ldr r0, [sp, #0x34]
	ldrh r3, [r7, #0x0]
	ldrh r2, [r7, #0x2]
	ldr r1, [r0, #0x18]
	ldrh r0, [r7, #0x4]
	add r2, r3, r2
	add r0, r0, r2
	add r0, r1, r0
	str r0, [sp, #0x14]
	bl seedr_LC
	add r0, r4, r5
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0206B030
_0206B01E:
	bl rand_LC
	str r0, [sp, #0x14]
	add r0, r4, r5
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	add r6, r6, #0x1
	cmp r6, r0
	blt _0206B01E
_0206B030:
	ldr r0, [sp, #0x14]
	lsl r1, r0, #0x8
	ldr r0, [sp, #0x10]
	add r6, r1, r0
	ldrh r1, [r7, #0x0]
	mov r0, #0x1f
	mul r0, r1
	mov r1, #0xff
	bl _s32_div_f
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	lsl r3, r3, #0x18
	str r6, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ldrh r1, [r7, #0x4]
	ldrh r2, [r7, #0x2]
	ldr r0, [sp, #0x40]
	lsr r3, r3, #0x18
	bl CreateMon
	ldr r0, [sp, #0x40]
	mov r1, #0x6
	add r2, r7, #0x6
	bl FUN_02067830
	ldr r0, [sp, #0x34]
	ldr r1, [sp, #0x40]
	ldr r0, [r0, #0x4]
	bl FUN_0206B900
	ldr r0, [sp, #0x1c]
	add r7, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x1c]
	add r0, r4, r5
	add r0, #0x2b
	ldrb r1, [r0, #0x0]
	ldr r0, [sp, #0x1c]
	cmp r0, r1
	blt _0206AFFC
_0206B08A:
	b _0206B156
_0206B08C:
	mov r0, #0x0
	str r0, [sp, #0x20]
	add r0, r4, r5
	add r0, #0x2b
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	ble _0206B156
	ldr r0, [sp, #0x4c]
	str r0, [sp, #0x3c]
	add r0, r4, r6
	str r0, [sp, #0x38]
_0206B0A2:
	ldr r0, [sp, #0x38]
	ldr r2, [sp, #0x3c]
	ldr r1, [r0, #0x18]
	ldr r0, [sp, #0x3c]
	ldrh r3, [r2, #0x0]
	ldrh r2, [r2, #0x2]
	ldrh r0, [r0, #0x4]
	add r2, r3, r2
	add r0, r0, r2
	add r7, r1, r0
	add r0, r7, #0x0
	bl seedr_LC
	add r0, r4, r5
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0206B0DA
_0206B0C8:
	bl rand_LC
	add r7, r0, #0x0
	add r0, r4, r5
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	add r6, r6, #0x1
	cmp r6, r0
	blt _0206B0C8
_0206B0DA:
	ldr r0, [sp, #0x10]
	lsl r1, r7, #0x8
	add r6, r1, r0
	ldr r0, [sp, #0x3c]
	ldrh r1, [r0, #0x0]
	mov r0, #0x1f
	mul r0, r1
	mov r1, #0xff
	bl _s32_div_f
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	lsl r3, r3, #0x18
	str r6, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x3c]
	ldr r2, [sp, #0x3c]
	ldrh r1, [r1, #0x4]
	ldrh r2, [r2, #0x2]
	ldr r0, [sp, #0x40]
	lsr r3, r3, #0x18
	bl CreateMon
	ldr r2, [sp, #0x3c]
	ldr r0, [sp, #0x40]
	mov r1, #0x6
	add r2, r2, #0x6
	bl FUN_02067830
	ldr r7, [sp, #0x3c]
	mov r6, #0x0
_0206B120:
	ldrh r1, [r7, #0x8]
	lsl r2, r6, #0x18
	ldr r0, [sp, #0x40]
	lsr r2, r2, #0x18
	bl FUN_020697CC
	add r6, r6, #0x1
	add r7, r7, #0x2
	cmp r6, #0x4
	blt _0206B120
	ldr r0, [sp, #0x38]
	ldr r1, [sp, #0x40]
	ldr r0, [r0, #0x4]
	bl FUN_0206B900
	ldr r0, [sp, #0x3c]
	add r0, #0x10
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x20]
	add r0, r0, #0x1
	str r0, [sp, #0x20]
	add r0, r4, r5
	add r0, #0x2b
	ldrb r1, [r0, #0x0]
	ldr r0, [sp, #0x20]
	cmp r0, r1
	blt _0206B0A2
_0206B156:
	ldr r0, [sp, #0x4c]
	bl FreeToHeap
	ldr r0, [sp, #0x40]
	bl FreeToHeap
	ldr r0, [sp, #0x44]
	bl seedr_LC
	add sp, #0x50
	pop {r3-r7, pc}
