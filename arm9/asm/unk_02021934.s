	.include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020EE67C
UNK_020EE67C: ; 0x020EE67C
	.byte 0xA2, 0x00, 0xA3, 0x00, 0xA4, 0x00, 0xA5, 0x00, 0xA6, 0x00, 0xA7, 0x00, 0xA8, 0x00, 0xA9, 0x00
	.byte 0xAA, 0x00, 0xAB, 0x00

	.global UNK_020EE690
UNK_020EE690: ; 0x020EE690
	.byte 0x21, 0x01, 0x22, 0x01, 0x23, 0x01, 0x24, 0x01, 0x25, 0x01, 0x26, 0x01, 0x27, 0x01, 0x28, 0x01

	.global UNK_020EE6A0
UNK_020EE6A0: ; 0x020EE6A0
	.byte 0x29, 0x01, 0x2A, 0x01, 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00
	.byte 0xE8, 0x03, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0xA0, 0x86, 0x01, 0x00, 0x40, 0x42, 0x0F, 0x00
	.byte 0x80, 0x96, 0x98, 0x00, 0x00, 0xE1, 0xF5, 0x05, 0x00, 0xCA, 0x9A, 0x3B

	.text

	thumb_func_start FUN_02021934
FUN_02021934: ; 0x02021934
	push {r3-r7, lr}
	add r5, r1, #0x0
	ldrh r1, [r5, #0x0]
	add r7, r0, #0x0
	mov r4, #0x0
	ldr r0, _02021994 ; =0x0000FFFF
	add r6, r2, #0x0
	str r4, [sp, #0x0]
	cmp r1, r0
	beq _02021986
_02021948:
	ldr r0, _02021998 ; =0x0000FFFE
	cmp r1, r0
	bne _02021958
	add r0, r5, #0x0
	bl FUN_0201B8B8
	add r5, r0, #0x0
	b _0202197E
_02021958:
	mov r0, #0xe
	lsl r0, r0, #0xc
	cmp r1, r0
	bne _02021970
	ldr r0, [sp, #0x0]
	sub r1, r4, r6
	cmp r0, r1
	bhs _0202196A
	str r1, [sp, #0x0]
_0202196A:
	mov r4, #0x0
	add r5, r5, #0x2
	b _0202197E
_02021970:
	ldr r2, [r7, #0x70]
	add r0, r7, #0x0
	sub r1, r1, #0x1
	blx r2
	add r0, r6, r0
	add r4, r4, r0
	add r5, r5, #0x2
_0202197E:
	ldrh r1, [r5, #0x0]
	ldr r0, _02021994 ; =0x0000FFFF
	cmp r1, r0
	bne _02021948
_02021986:
	ldr r0, [sp, #0x0]
	sub r1, r4, r6
	cmp r0, r1
	bhs _02021990
	str r1, [sp, #0x0]
_02021990:
	ldr r0, [sp, #0x0]
	pop {r3-r7, pc}
	.balign 4
_02021994: .word 0x0000FFFF
_02021998: .word 0x0000FFFE

	thumb_func_start FUN_0202199C
FUN_0202199C: ; 0x0202199C
	push {r3-r7, lr}
	add r5, r1, #0x0
	ldrh r1, [r5, #0x0]
	add r6, r0, #0x0
	ldr r0, _020219EC ; =0x0000FFFF
	mov r4, #0x0
	cmp r1, r0
	beq _020219E8
	sub r7, r0, #0x1
_020219AE:
	cmp r1, r7
	bne _020219D4
	add r0, r5, #0x0
	bl FUN_0201B8E0
	ldr r1, _020219F0 ; =0x00000203
	cmp r0, r1
	bne _020219CA
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0201B914
	add r4, r0, #0x0
	sub r4, #0xc
_020219CA:
	add r0, r5, #0x0
	bl FUN_0201B8B8
	add r5, r0, #0x0
	b _020219E0
_020219D4:
	ldr r2, [r6, #0x70]
	add r0, r6, #0x0
	sub r1, r1, #0x1
	blx r2
	add r4, r4, r0
	add r5, r5, #0x2
_020219E0:
	ldrh r1, [r5, #0x0]
	ldr r0, _020219EC ; =0x0000FFFF
	cmp r1, r0
	bne _020219AE
_020219E8:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_020219EC: .word 0x0000FFFF
_020219F0: .word 0x00000203

	thumb_func_start String_ctor
String_ctor: ; 0x020219F4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	lsl r1, r4, #0x1
	add r1, #0xa
	bl AllocFromHeap
	cmp r0, #0x0
	beq _02021A14
	ldr r1, _02021A18 ; =0xB6F8D2EC
	str r1, [r0, #0x4]
	strh r4, [r0, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x2]
	ldr r1, _02021A1C ; =0x0000FFFF
	strh r1, [r0, #0x8]
_02021A14:
	pop {r4, pc}
	nop
_02021A18: .word 0xB6F8D2EC
_02021A1C: .word 0x0000FFFF

	thumb_func_start String_dtor
String_dtor: ; 0x02021A20
	push {r4, lr}
	add r4, r0, #0x0
	bne _02021A2A
	bl ErrorHandling
_02021A2A:
	ldr r1, [r4, #0x4]
	ldr r0, _02021A44 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021A36
	bl ErrorHandling
_02021A36:
	ldr r0, _02021A48 ; =0xB6F8D2ED
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	nop
_02021A44: .word 0xB6F8D2EC
_02021A48: .word 0xB6F8D2ED

	thumb_func_start StringSetEmpty
StringSetEmpty: ; 0x02021A4C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02021A56
	bl ErrorHandling
_02021A56:
	ldr r1, [r4, #0x4]
	ldr r0, _02021A6C ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021A62
	bl ErrorHandling
_02021A62:
	mov r0, #0x0
	strh r0, [r4, #0x2]
	ldr r0, _02021A70 ; =0x0000FFFF
	strh r0, [r4, #0x8]
	pop {r4, pc}
	.balign 4
_02021A6C: .word 0xB6F8D2EC
_02021A70: .word 0x0000FFFF

	thumb_func_start StringCopy
StringCopy: ; 0x02021A74
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021A82
	bl ErrorHandling
_02021A82:
	ldr r1, [r5, #0x4]
	ldr r0, _02021AC8 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021A8E
	bl ErrorHandling
_02021A8E:
	cmp r4, #0x0
	bne _02021A96
	bl ErrorHandling
_02021A96:
	ldr r1, [r4, #0x4]
	ldr r0, _02021AC8 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021AA2
	bl ErrorHandling
_02021AA2:
	ldrh r2, [r4, #0x2]
	ldrh r0, [r5, #0x0]
	cmp r0, r2
	bls _02021AC0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r2, #0x1
	add r0, #0x8
	add r1, #0x8
	lsl r2, r2, #0x1
	bl memcpy
	ldrh r0, [r4, #0x2]
	strh r0, [r5, #0x2]
	pop {r3-r5, pc}
_02021AC0:
	bl ErrorHandling
	pop {r3-r5, pc}
	nop
_02021AC8: .word 0xB6F8D2EC

	thumb_func_start StringDup
StringDup: ; 0x02021ACC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021ADA
	bl ErrorHandling
_02021ADA:
	ldr r1, [r5, #0x4]
	ldr r0, _02021B00 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021AE6
	bl ErrorHandling
_02021AE6:
	ldrh r0, [r5, #0x2]
	add r1, r4, #0x0
	add r0, r0, #0x1
	bl String_ctor
	add r4, r0, #0x0
	beq _02021AFA
	add r1, r5, #0x0
	bl StringCopy
_02021AFA:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_02021B00: .word 0xB6F8D2EC

	thumb_func_start FUN_02021B04
FUN_02021B04: ; 0x02021B04
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [sp, #0x20]
	add r6, r1, #0x0
	add r7, r3, #0x0
	str r2, [sp, #0x0]
	str r0, [sp, #0x20]
	cmp r5, #0x0
	bne _02021B1C
	bl ErrorHandling
_02021B1C:
	ldr r1, [r5, #0x4]
	ldr r0, _02021C1C ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021B28
	bl ErrorHandling
_02021B28:
	cmp r6, #0x0
	bge _02021B30
	mov r4, #0x1
	b _02021B32
_02021B30:
	mov r4, #0x0
_02021B32:
	ldr r0, [sp, #0x0]
	ldrh r1, [r5, #0x0]
	add r0, r0, r4
	cmp r1, r0
	bls _02021C14
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	bne _02021B48
	ldr r0, _02021C20 ; =UNK_020EE67C
	str r0, [sp, #0x4]
	b _02021B4C
_02021B48:
	ldr r0, _02021C24 ; =UNK_020EE690
	str r0, [sp, #0x4]
_02021B4C:
	add r0, r5, #0x0
	bl StringSetEmpty
	cmp r4, #0x0
	beq _02021B74
	mov r0, #0x0
	mvn r0, r0
	mul r6, r0
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	bne _02021B66
	mov r0, #0xf1
	b _02021B68
_02021B66:
	ldr r0, _02021C28 ; =0x000001BE
_02021B68:
	ldrh r2, [r5, #0x2]
	add r1, r2, #0x1
	strh r1, [r5, #0x2]
	lsl r1, r2, #0x1
	add r1, r5, r1
	strh r0, [r1, #0x8]
_02021B74:
	ldr r0, [sp, #0x0]
	lsl r1, r0, #0x2
	ldr r0, _02021C2C ; =UNK_020EE6A0
	ldr r4, [r0, r1]
	cmp r4, #0x0
	beq _02021C06
_02021B80:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl _u32_div_f
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r0, r4, #0x0
	mul r0, r1
	sub r6, r6, r0
	cmp r7, #0x2
	bne _02021BB4
	cmp r1, #0xa
	bhs _02021BA2
	ldr r0, [sp, #0x4]
	lsl r1, r1, #0x1
	ldrh r1, [r0, r1]
	b _02021BA4
_02021BA2:
	mov r1, #0xe2
_02021BA4:
	ldrh r0, [r5, #0x2]
	add r2, r0, #0x0
	add r2, r2, #0x1
	lsl r0, r0, #0x1
	strh r2, [r5, #0x2]
	add r0, r5, r0
	strh r1, [r0, #0x8]
	b _02021BFA
_02021BB4:
	cmp r1, #0x0
	bne _02021BBC
	cmp r4, #0x1
	bne _02021BDC
_02021BBC:
	mov r7, #0x2
	cmp r1, #0xa
	bhs _02021BCA
	ldr r0, [sp, #0x4]
	lsl r1, r1, #0x1
	ldrh r1, [r0, r1]
	b _02021BCC
_02021BCA:
	mov r1, #0xe2
_02021BCC:
	ldrh r0, [r5, #0x2]
	add r2, r0, #0x0
	add r2, r2, #0x1
	lsl r0, r0, #0x1
	strh r2, [r5, #0x2]
	add r0, r5, r0
	strh r1, [r0, #0x8]
	b _02021BFA
_02021BDC:
	cmp r7, #0x1
	bne _02021BFA
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	bne _02021BEA
	mov r1, #0x1
	b _02021BEC
_02021BEA:
	ldr r1, _02021C30 ; =0x000001E2
_02021BEC:
	ldrh r0, [r5, #0x2]
	add r2, r0, #0x0
	add r2, r2, #0x1
	lsl r0, r0, #0x1
	strh r2, [r5, #0x2]
	add r0, r5, r0
	strh r1, [r0, #0x8]
_02021BFA:
	add r0, r4, #0x0
	mov r1, #0xa
	bl _u32_div_f
	add r4, r0, #0x0
	bne _02021B80
_02021C06:
	ldrh r0, [r5, #0x2]
	ldr r1, _02021C34 ; =0x0000FFFF
	add sp, #0x8
	lsl r0, r0, #0x1
	add r0, r5, r0
	strh r1, [r0, #0x8]
	pop {r3-r7, pc}
_02021C14:
	bl ErrorHandling
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02021C1C: .word 0xB6F8D2EC
_02021C20: .word UNK_020EE67C
_02021C24: .word UNK_020EE690
_02021C28: .word 0x000001BE
_02021C2C: .word UNK_020EE6A0
_02021C30: .word 0x000001E2
_02021C34: .word 0x0000FFFF

	thumb_func_start FUN_02021C38
FUN_02021C38: ; 0x02021C38
	push {r3-r7, lr}
	sub sp, #0x10
	str r1, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x8]
	str r1, [sp, #0xc]
	add r5, r1, #0x0
	ldrh r1, [r0, #0x2]
	mov r7, #0x1
	cmp r1, #0x12
	bls _02021C56
	ldr r0, [sp, #0x8]
	add sp, #0x10
	add r1, r0, #0x0
	pop {r3-r7, pc}
_02021C56:
	sub r1, r1, #0x1
	str r1, [sp, #0x4]
	bmi _02021CCC
	lsl r1, r1, #0x1
	add r4, r0, r1
_02021C60:
	ldrh r6, [r4, #0x8]
	mov r3, #0xa
	mov r0, #0x0
	add r1, r6, #0x0
	sub r1, #0xa2
	asr r2, r1, #0x1f
	sub r3, r1, r3
	mov r12, r2
	mov r3, r12
	sbc r3, r0
	blo _02021C98
	ldr r0, _02021CDC ; =0x00000121
	mov r3, #0xa
	sub r1, r6, r0
	asr r2, r1, #0x1f
	mov r0, #0x0
	sub r3, r1, r3
	mov r12, r2
	mov r3, r12
	sbc r3, r0
	blo _02021C98
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	add sp, #0x10
	pop {r3-r7, pc}
_02021C98:
	add r0, r1, #0x0
	add r1, r2, #0x0
	add r2, r7, #0x0
	add r3, r5, #0x0
	bl _ll_mul
	add r2, r1, #0x0
	ldr r1, [sp, #0x8]
	add r0, r1, r0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0xc]
	adc r0, r2
	str r0, [sp, #0xc]
	add r0, r7, #0x0
	add r1, r5, #0x0
	mov r2, #0xa
	mov r3, #0x0
	bl _ll_mul
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	add r5, r1, #0x0
	sub r4, r4, #0x2
	sub r0, r0, #0x1
	str r0, [sp, #0x4]
	bpl _02021C60
_02021CCC:
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_02021CDC: .word 0x00000121

	thumb_func_start FUN_02021CE0
FUN_02021CE0: ; 0x02021CE0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021CEE
	bl ErrorHandling
_02021CEE:
	ldr r1, [r5, #0x4]
	ldr r0, _02021D34 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021CFA
	bl ErrorHandling
_02021CFA:
	cmp r4, #0x0
	bne _02021D02
	bl ErrorHandling
_02021D02:
	ldr r1, [r4, #0x4]
	ldr r0, _02021D34 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021D0E
	bl ErrorHandling
_02021D0E:
	ldrh r1, [r5, #0x8]
	ldrh r0, [r4, #0x8]
	cmp r1, r0
	bne _02021D2E
	ldr r0, _02021D38 ; =0x0000FFFF
_02021D18:
	ldrh r1, [r5, #0x8]
	cmp r1, r0
	bne _02021D22
	mov r0, #0x0
	pop {r3-r5, pc}
_02021D22:
	add r5, r5, #0x2
	add r4, r4, #0x2
	ldrh r2, [r5, #0x8]
	ldrh r1, [r4, #0x8]
	cmp r2, r1
	beq _02021D18
_02021D2E:
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_02021D34: .word 0xB6F8D2EC
_02021D38: .word 0x0000FFFF

	thumb_func_start FUN_02021D3C
FUN_02021D3C: ; 0x02021D3C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02021D46
	bl ErrorHandling
_02021D46:
	ldr r1, [r4, #0x4]
	ldr r0, _02021D58 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021D52
	bl ErrorHandling
_02021D52:
	ldrh r0, [r4, #0x2]
	pop {r4, pc}
	nop
_02021D58: .word 0xB6F8D2EC

	thumb_func_start FUN_02021D5C
FUN_02021D5C: ; 0x02021D5C
	push {r3-r5, lr}
	add r4, r0, #0x0
	bne _02021D66
	bl ErrorHandling
_02021D66:
	ldr r1, [r4, #0x4]
	ldr r0, _02021D98 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021D72
	bl ErrorHandling
_02021D72:
	ldrh r1, [r4, #0x2]
	mov r3, #0x0
	mov r0, #0x1
	cmp r1, #0x0
	ble _02021D94
	mov r1, #0xe
	add r5, r4, #0x0
	lsl r1, r1, #0xc
_02021D82:
	ldrh r2, [r5, #0x8]
	cmp r2, r1
	bne _02021D8A
	add r0, r0, #0x1
_02021D8A:
	ldrh r2, [r4, #0x2]
	add r3, r3, #0x1
	add r5, r5, #0x2
	cmp r3, r2
	blt _02021D82
_02021D94:
	pop {r3-r5, pc}
	nop
_02021D98: .word 0xB6F8D2EC

	thumb_func_start FUN_02021D9C
FUN_02021D9C: ; 0x02021D9C
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r7, r0, #0x0
	add r6, r2, #0x0
	cmp r5, #0x0
	bne _02021DAC
	bl ErrorHandling
_02021DAC:
	ldr r1, [r5, #0x4]
	ldr r0, _02021E24 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021DB8
	bl ErrorHandling
_02021DB8:
	cmp r7, #0x0
	bne _02021DC0
	bl ErrorHandling
_02021DC0:
	ldr r1, [r7, #0x4]
	ldr r0, _02021E24 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021DCC
	bl ErrorHandling
_02021DCC:
	mov r4, #0x0
	cmp r6, #0x0
	beq _02021DF6
	ldrh r0, [r5, #0x2]
	cmp r0, #0x0
	ble _02021DF6
	mov r1, #0xe
	add r0, r5, #0x0
	lsl r1, r1, #0xc
_02021DDE:
	ldrh r2, [r0, #0x8]
	cmp r2, r1
	bne _02021DEC
	sub r6, r6, #0x1
	bne _02021DEC
	add r4, r4, #0x1
	b _02021DF6
_02021DEC:
	ldrh r2, [r5, #0x2]
	add r4, r4, #0x1
	add r0, r0, #0x2
	cmp r4, r2
	blt _02021DDE
_02021DF6:
	add r0, r7, #0x0
	bl StringSetEmpty
	ldrh r0, [r5, #0x2]
	cmp r4, r0
	bge _02021E20
	lsl r0, r4, #0x1
	add r6, r5, r0
_02021E06:
	ldrh r1, [r6, #0x8]
	mov r0, #0xe
	lsl r0, r0, #0xc
	cmp r1, r0
	beq _02021E20
	add r0, r7, #0x0
	bl FUN_02021FB0
	ldrh r0, [r5, #0x2]
	add r4, r4, #0x1
	add r6, r6, #0x2
	cmp r4, r0
	blt _02021E06
_02021E20:
	pop {r3-r7, pc}
	nop
_02021E24: .word 0xB6F8D2EC

	thumb_func_start FUN_02021E28
FUN_02021E28: ; 0x02021E28
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021E36
	bl ErrorHandling
_02021E36:
	ldr r1, [r5, #0x4]
	ldr r0, _02021E84 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021E42
	bl ErrorHandling
_02021E42:
	mov r0, #0x0
	strh r0, [r5, #0x2]
	ldrh r1, [r4, #0x0]
	ldr r0, _02021E88 ; =0x0000FFFF
	cmp r1, r0
	beq _02021E76
	add r1, r0, #0x0
_02021E50:
	ldrh r2, [r5, #0x0]
	ldrh r0, [r5, #0x2]
	sub r2, r2, #0x1
	cmp r0, r2
	blt _02021E60
	bl ErrorHandling
	b _02021E76
_02021E60:
	add r2, r0, #0x0
	add r2, r2, #0x1
	strh r2, [r5, #0x2]
	ldrh r2, [r4, #0x0]
	lsl r0, r0, #0x1
	add r0, r5, r0
	add r4, r4, #0x2
	strh r2, [r0, #0x8]
	ldrh r0, [r4, #0x0]
	cmp r0, r1
	bne _02021E50
_02021E76:
	ldrh r0, [r5, #0x2]
	ldr r1, _02021E88 ; =0x0000FFFF
	lsl r0, r0, #0x1
	add r0, r5, r0
	strh r1, [r0, #0x8]
	pop {r3-r5, pc}
	nop
_02021E84: .word 0xB6F8D2EC
_02021E88: .word 0x0000FFFF

	thumb_func_start FUN_02021E8C
FUN_02021E8C: ; 0x02021E8C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r2, #0x0
	cmp r5, #0x0
	bne _02021E9C
	bl ErrorHandling
_02021E9C:
	ldr r1, [r5, #0x4]
	ldr r0, _02021EE8 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021EA8
	bl ErrorHandling
_02021EA8:
	ldrh r0, [r5, #0x0]
	cmp r4, r0
	bhi _02021EE2
	lsl r6, r4, #0x1
	add r0, r5, #0x0
	add r0, #0x8
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl memcpy
	mov r2, #0x0
	cmp r4, #0x0
	bls _02021ED4
	ldr r0, _02021EEC ; =0x0000FFFF
	add r3, r5, #0x0
_02021EC6:
	ldrh r1, [r3, #0x8]
	cmp r1, r0
	beq _02021ED4
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, r4
	blo _02021EC6
_02021ED4:
	strh r2, [r5, #0x2]
	cmp r2, r4
	bne _02021EE6
	ldr r1, _02021EEC ; =0x0000FFFF
	add r0, r5, r6
	strh r1, [r0, #0x6]
	pop {r3-r7, pc}
_02021EE2:
	bl ErrorHandling
_02021EE6:
	pop {r3-r7, pc}
	.balign 4
_02021EE8: .word 0xB6F8D2EC
_02021EEC: .word 0x0000FFFF

	thumb_func_start FUN_02021EF0
FUN_02021EF0: ; 0x02021EF0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	cmp r5, #0x0
	bne _02021F00
	bl ErrorHandling
_02021F00:
	ldr r1, [r5, #0x4]
	ldr r0, _02021F28 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021F0C
	bl ErrorHandling
_02021F0C:
	ldrh r0, [r5, #0x2]
	add r2, r0, #0x1
	cmp r2, r4
	bhi _02021F22
	add r5, #0x8
	add r0, r6, #0x0
	add r1, r5, #0x0
	lsl r2, r2, #0x1
	bl memcpy
	pop {r4-r6, pc}
_02021F22:
	bl ErrorHandling
	pop {r4-r6, pc}
	.balign 4
_02021F28: .word 0xB6F8D2EC

	thumb_func_start String_c_str
String_c_str: ; 0x02021F2C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02021F36
	bl ErrorHandling
_02021F36:
	ldr r1, [r4, #0x4]
	ldr r0, _02021F48 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021F42
	bl ErrorHandling
_02021F42:
	add r4, #0x8
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02021F48: .word 0xB6F8D2EC

	thumb_func_start FUN_02021F4C
FUN_02021F4C: ; 0x02021F4C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021F5A
	bl ErrorHandling
_02021F5A:
	ldr r1, [r5, #0x4]
	ldr r0, _02021FAC ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021F66
	bl ErrorHandling
_02021F66:
	cmp r4, #0x0
	bne _02021F6E
	bl ErrorHandling
_02021F6E:
	ldr r1, [r4, #0x4]
	ldr r0, _02021FAC ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021F7A
	bl ErrorHandling
_02021F7A:
	ldrh r2, [r4, #0x2]
	ldrh r0, [r5, #0x2]
	add r1, r0, r2
	add r3, r1, #0x1
	ldrh r1, [r5, #0x0]
	cmp r3, r1
	bgt _02021FA6
	add r1, r5, #0x0
	add r1, #0x8
	lsl r0, r0, #0x1
	add r0, r1, r0
	add r1, r4, #0x0
	add r2, r2, #0x1
	add r1, #0x8
	lsl r2, r2, #0x1
	bl memcpy
	ldrh r1, [r5, #0x2]
	ldrh r0, [r4, #0x2]
	add r0, r1, r0
	strh r0, [r5, #0x2]
	pop {r3-r5, pc}
_02021FA6:
	bl ErrorHandling
	pop {r3-r5, pc}
	.balign 4
_02021FAC: .word 0xB6F8D2EC

	thumb_func_start FUN_02021FB0
FUN_02021FB0: ; 0x02021FB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021FBE
	bl ErrorHandling
_02021FBE:
	ldr r1, [r5, #0x4]
	ldr r0, _02021FF0 ; =0xB6F8D2EC
	cmp r1, r0
	beq _02021FCA
	bl ErrorHandling
_02021FCA:
	ldrh r2, [r5, #0x2]
	ldrh r0, [r5, #0x0]
	add r1, r2, #0x1
	cmp r1, r0
	bge _02021FE8
	lsl r0, r2, #0x1
	strh r1, [r5, #0x2]
	add r0, r5, r0
	strh r4, [r0, #0x8]
	ldrh r0, [r5, #0x2]
	ldr r1, _02021FF4 ; =0x0000FFFF
	lsl r0, r0, #0x1
	add r0, r5, r0
	strh r1, [r0, #0x8]
	pop {r3-r5, pc}
_02021FE8:
	bl ErrorHandling
	pop {r3-r5, pc}
	nop
_02021FF0: .word 0xB6F8D2EC
_02021FF4: .word 0x0000FFFF

	thumb_func_start FUN_02021FF8
FUN_02021FF8: ; 0x02021FF8
	push {r4, lr}
	add r4, r0, #0x0
	bne _02022002
	bl ErrorHandling
_02022002:
	ldr r1, [r4, #0x4]
	ldr r0, _02022028 ; =0xB6F8D2EC
	cmp r1, r0
	beq _0202200E
	bl ErrorHandling
_0202200E:
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _02022026
	ldrh r1, [r4, #0x8]
	ldr r0, _0202202C ; =0x00000145
	cmp r1, r0
	blo _02022026
	add r0, #0x19
	cmp r1, r0
	bhi _02022026
	sub r1, #0x1a
	strh r1, [r4, #0x8]
_02022026:
	pop {r4, pc}
	.balign 4
_02022028: .word 0xB6F8D2EC
_0202202C: .word 0x00000145
