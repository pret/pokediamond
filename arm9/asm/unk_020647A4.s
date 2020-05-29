    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020F7D4C
UNK_020F7D4C: ; 0x020F7D4C
	.byte 0x02, 0x01, 0x00, 0x00, 0xF6, 0x01, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0xF6, 0x01, 0x00, 0x00
	.byte 0x02, 0x01, 0x00, 0x00, 0xF6, 0x01, 0x00, 0x00

	.global UNK_020F7D64
UNK_020F7D64: ; 0x020F7D64
	.byte 0x00, 0x80, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x2C, 0x00

	.global UNK_020F7D70
UNK_020F7D70: ; 0x020F7D70
	.byte 0x00, 0x00, 0x01, 0x00

	.global UNK_020F7D74
UNK_020F7D74: ; 0x020F7D74
	.byte 0x00, 0x00, 0x09, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00

	.global UNK_020F7D80
UNK_020F7D80: ; 0x020F7D80
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020F7D84
UNK_020F7D84: ; 0x020F7D84
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x12, 0x00, 0x00, 0x00
	.byte 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x13, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x0F, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_020647A4
FUN_020647A4: ; 0x020647A4
	push {r3-r7, lr}
	sub sp, #0x30
	add r4, r0, #0x0
	bl FUN_020377AC
	bl FUN_02024ED8
	mov r1, #0x7
	bl FUN_020254A0
	ldrh r1, [r0, #0x2]
	ldrh r0, [r0, #0x0]
	ldr r3, _0206485C ; =UNK_020F7D70
	mov r7, #0x18
	add r2, r1, #0x0
	mul r2, r7
	add r6, r3, r2
	lsl r0, r0, #0x2
	ldr r5, [r6, r0]
	ldr r0, [r6, #0x14]
	cmp r0, #0x0
	beq _0206480A
	ldr r3, _02064860 ; =UNK_020F7D64
	add r2, sp, #0x24
	ldmia r3!, {r0-r1}
	mov r12, r2
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r7, #0xea
	str r0, [r2, #0x0]
	str r5, [sp, #0x28]
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x4c]
	add r2, r7, #0x0
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r0, #0xa0
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x2c]
	mov r3, r12
	bl MOD05_021E7FBC
	add r0, r4, #0x0
	add r0, #0xa0
	ldr r0, [r0, #0x0]
	ldr r1, _02064864 ; =0x00000102
	bl MOD05_021E7ED8
	str r0, [sp, #0x14]
	b _0206482C
_0206480A:
	ldr r0, _02064868 ; =UNK_020F7D4C
	add r1, sp, #0xc
	ldr r2, [r0, #0x8]
	ldr r0, [r0, #0xc]
	str r2, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r2, #0x2
	add r3, sp, #0x14
	bl FUN_0204AA5C
	cmp r0, #0x0
	bne _0206482C
	bl ErrorHandling
_0206482C:
	ldr r1, [sp, #0x14]
	add r0, sp, #0x18
	bl MOD05_021E7EA0
	ldr r0, [sp, #0x14]
	add r1, sp, #0x18
	str r5, [sp, #0x1c]
	bl MOD05_021E7EB0
	mov r0, #0x2
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	add r4, #0x9c
	ldr r0, [r4, #0x0]
	mov r3, #0x3
	str r0, [sp, #0x8]
	ldr r1, [r6, #0x8]
	ldr r2, [r6, #0xc]
	mov r0, #0x0
	bl MOD05_021F44D8
	add sp, #0x30
	pop {r3-r7, pc}
	nop
_0206485C: .word UNK_020F7D70
_02064860: .word UNK_020F7D64
_02064864: .word 0x00000102
_02064868: .word UNK_020F7D4C

	thumb_func_start FUN_0206486C
FUN_0206486C: ; 0x0206486C
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_020377AC
	bl FUN_02024ED8
	add r5, r0, #0x0
	mov r1, #0x7
	bl FUN_02025490
	add r0, r5, #0x0
	mov r1, #0x7
	bl FUN_020254A0
	mov r3, #0x1
	str r3, [r0, #0x4]
	mov r2, #0x0
	str r2, [r0, #0x8]
	ldr r4, [r4, #0x1c]
	ldr r5, _020649A8 ; =0x00000123
	ldr r1, [r4, #0x0]
	cmp r1, r5
	bgt _020648C4
	bge _020648D6
	add r5, r1, #0x0
	sub r5, #0xb0
	cmp r5, #0x9
	bhi _020649A0
	add r5, r5, r5
	add r5, pc
	ldrh r5, [r5, #0x6]
	lsl r5, r5, #0x10
	asr r5, r5, #0x10
	add pc, r5
_020648B0: ; jump table (using 16-bit offset)
	.short _02064910 - _020648B0 - 2; case 0
	.short _020649A0 - _020648B0 - 2; case 1
	.short _02064928 - _020648B0 - 2; case 2
	.short _020649A0 - _020648B0 - 2; case 3
	.short _02064940 - _020648B0 - 2; case 4
	.short _020649A0 - _020648B0 - 2; case 5
	.short _02064958 - _020648B0 - 2; case 6
	.short _020649A0 - _020648B0 - 2; case 7
	.short _02064970 - _020648B0 - 2; case 8
	.short _02064988 - _020648B0 - 2; case 9
_020648C4:
	ldr r2, _020649AC ; =0x00000125
	cmp r1, r2
	bgt _020648CE
	beq _020648E8
	b _020649A0
_020648CE:
	add r2, r2, #0x1
	cmp r1, r2
	beq _020648FC
	b _020649A0
_020648D6:
	ldr r1, [r4, #0xc]
	cmp r1, #0x1a
	bne _020648E0
	strh r2, [r0, #0x0]
	b _020648E2
_020648E0:
	strh r3, [r0, #0x0]
_020648E2:
	mov r1, #0x0
	strh r1, [r0, #0x2]
	pop {r3-r5, pc}
_020648E8:
	ldr r1, [r4, #0xc]
	cmp r1, #0x30
	bne _020648F2
	mov r1, #0x0
	b _020648F4
_020648F2:
	mov r1, #0x1
_020648F4:
	strh r1, [r0, #0x0]
	mov r1, #0x1
	strh r1, [r0, #0x2]
	pop {r3-r5, pc}
_020648FC:
	ldr r1, [r4, #0xc]
	cmp r1, #0xf
	bne _02064906
	mov r1, #0x0
	b _02064908
_02064906:
	mov r1, #0x1
_02064908:
	strh r1, [r0, #0x0]
	mov r1, #0x2
	strh r1, [r0, #0x2]
	pop {r3-r5, pc}
_02064910:
	ldr r1, [r4, #0xc]
	cmp r1, #0xf
	bne _0206491A
	strh r2, [r0, #0x0]
	b _0206491E
_0206491A:
	strh r3, [r0, #0x0]
	str r2, [r0, #0x4]
_0206491E:
	mov r1, #0x3
	strh r1, [r0, #0x2]
	mov r1, #0x1
	str r1, [r0, #0x8]
	pop {r3-r5, pc}
_02064928:
	ldr r1, [r4, #0xc]
	cmp r1, #0xf
	bne _02064932
	strh r2, [r0, #0x0]
	b _02064936
_02064932:
	strh r3, [r0, #0x0]
	str r2, [r0, #0x4]
_02064936:
	mov r1, #0x4
	strh r1, [r0, #0x2]
	mov r1, #0x1
	str r1, [r0, #0x8]
	pop {r3-r5, pc}
_02064940:
	ldr r1, [r4, #0xc]
	cmp r1, #0xf
	bne _0206494A
	strh r2, [r0, #0x0]
	b _0206494E
_0206494A:
	strh r3, [r0, #0x0]
	str r2, [r0, #0x4]
_0206494E:
	mov r1, #0x5
	strh r1, [r0, #0x2]
	mov r1, #0x1
	str r1, [r0, #0x8]
	pop {r3-r5, pc}
_02064958:
	ldr r1, [r4, #0xc]
	cmp r1, #0xf
	bne _02064962
	strh r2, [r0, #0x0]
	b _02064966
_02064962:
	strh r3, [r0, #0x0]
	str r2, [r0, #0x4]
_02064966:
	mov r1, #0x6
	strh r1, [r0, #0x2]
	mov r1, #0x1
	str r1, [r0, #0x8]
	pop {r3-r5, pc}
_02064970:
	ldr r1, [r4, #0xc]
	cmp r1, #0x17
	bne _0206497A
	strh r2, [r0, #0x0]
	b _0206497E
_0206497A:
	strh r3, [r0, #0x0]
	str r2, [r0, #0x4]
_0206497E:
	mov r1, #0x7
	strh r1, [r0, #0x2]
	mov r1, #0x1
	str r1, [r0, #0x8]
	pop {r3-r5, pc}
_02064988:
	ldr r1, [r4, #0xc]
	cmp r1, #0x12
	bne _02064992
	strh r2, [r0, #0x0]
	b _02064996
_02064992:
	strh r3, [r0, #0x0]
	str r2, [r0, #0x4]
_02064996:
	mov r1, #0x8
	strh r1, [r0, #0x2]
	mov r1, #0x1
	str r1, [r0, #0x8]
	pop {r3-r5, pc}
_020649A0:
	bl ErrorHandling
	pop {r3-r5, pc}
	nop
_020649A8: .word 0x00000123
_020649AC: .word 0x00000125

	thumb_func_start FUN_020649B0
FUN_020649B0: ; 0x020649B0
	push {r3, lr}
	bl FUN_020377AC
	bl FUN_02024ED8
	mov r1, #0x7
	bl FUN_020254A0
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _020649CA
	mov r0, #0x1
	b _020649CC
_020649CA:
	mov r0, #0x0
_020649CC:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020649D4
FUN_020649D4: ; 0x020649D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020377AC
	bl FUN_02024ED8
	mov r1, #0x7
	bl FUN_020254A0
	add r4, r0, #0x0
	ldrh r1, [r4, #0x2]
	mov r0, #0x18
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, _02064A58 ; =UNK_020F7D80
	ldr r0, [r0, r2]
	cmp r0, #0x0
	beq _020649FE
	ldrh r0, [r4, #0x0]
	cmp r0, #0x1
	beq _02064A54
_020649FE:
	mov r0, #0xb
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	ldrh r1, [r4, #0x2]
	mov r0, #0x18
	add r3, r1, #0x0
	ldr r1, _02064A5C ; =UNK_020F7D84
	mul r3, r0
	ldr r1, [r1, r3]
	str r1, [r2, #0x8]
	ldr r1, [r4, #0x8]
	str r1, [r2, #0xc]
	ldrh r1, [r4, #0x0]
	cmp r1, #0x0
	ldrh r1, [r4, #0x2]
	bne _02064A3E
	add r3, r1, #0x0
	mul r3, r0
	ldr r0, _02064A60 ; =UNK_020F7D74
	ldr r1, _02064A64 ; =FUN_02064A70
	ldr r0, [r0, r3]
	str r0, [r2, #0x4]
	ldr r0, [r5, #0x10]
	bl FUN_0204640C
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}
_02064A3E:
	add r3, r1, #0x0
	mul r3, r0
	ldr r0, _02064A68 ; =UNK_020F7D70
	ldr r1, _02064A6C ; =FUN_02064B70
	ldr r0, [r0, r3]
	str r0, [r2, #0x4]
	ldr r0, [r5, #0x10]
	bl FUN_0204640C
	mov r0, #0x0
	strh r0, [r4, #0x0]
_02064A54:
	pop {r3-r5, pc}
	nop
_02064A58: .word UNK_020F7D80
_02064A5C: .word UNK_020F7D84
_02064A60: .word UNK_020F7D74
_02064A64: .word FUN_02064A70
_02064A68: .word UNK_020F7D70
_02064A6C: .word FUN_02064B70

	thumb_func_start FUN_02064A70
FUN_02064A70: ; 0x02064A70
	push {r4-r5, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x3
	bhi _02064B5C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02064A96: ; jump table (using 16-bit offset)
	.short _02064A9E - _02064A96 - 2; case 0
	.short _02064AB4 - _02064A96 - 2; case 1
	.short _02064B2E - _02064A96 - 2; case 2
	.short _02064B52 - _02064A96 - 2; case 3
_02064A9E:
	ldr r0, [r5, #0x38]
	mov r1, #0x0
	bl FUN_02055560
	ldr r0, [r4, #0xc]
	bl FUN_02064C64
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02064B5C
_02064AB4:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _02064ACA
	add r0, r5, #0x0
	add r0, #0xa0
	ldr r0, [r0, #0x0]
	ldr r1, _02064B64 ; =0x00000102
	bl MOD05_021E7ED8
	str r0, [sp, #0xc]
	b _02064AEC
_02064ACA:
	ldr r0, _02064B68 ; =UNK_020F7D4C
	add r1, sp, #0x4
	ldr r2, [r0, #0x0]
	ldr r0, [r0, #0x4]
	str r2, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x2
	add r3, sp, #0xc
	bl FUN_0204AA5C
	cmp r0, #0x0
	bne _02064AEC
	bl ErrorHandling
_02064AEC:
	ldr r1, [sp, #0xc]
	add r0, sp, #0x10
	bl MOD05_021E7EA0
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	bne _02064AFE
	mov r1, #0x1
	b _02064B00
_02064AFE:
	mov r1, #0x2
_02064B00:
	ldr r0, [sp, #0x14]
	lsl r1, r1, #0xc
	add r1, r0, r1
	str r1, [sp, #0x14]
	ldr r0, [r4, #0x4]
	cmp r1, r0
	blt _02064B1C
	str r0, [sp, #0x14]
	ldr r0, [r4, #0xc]
	bl FUN_02064C84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
_02064B1C:
	ldr r0, [r5, #0x38]
	ldr r1, [sp, #0x14]
	bl FUN_02055540
	ldr r0, [sp, #0xc]
	add r1, sp, #0x10
	bl MOD05_021E7EB0
	b _02064B5C
_02064B2E:
	add r2, r5, #0x0
	add r2, #0x9c
	ldr r1, [r4, #0x4]
	ldr r2, [r2, #0x0]
	mov r0, #0x0
	bl MOD05_021F4594
	ldr r0, [r5, #0x38]
	mov r1, #0x1
	bl FUN_0205557C
	ldr r0, _02064B6C ; =0x0000061A
	bl FUN_020054C8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02064B5C
_02064B52:
	bl FreeToHeap
	add sp, #0x1c
	mov r0, #0x1
	pop {r4-r5, pc}
_02064B5C:
	mov r0, #0x0
	add sp, #0x1c
	pop {r4-r5, pc}
	nop
_02064B64: .word 0x00000102
_02064B68: .word UNK_020F7D4C
_02064B6C: .word 0x0000061A

	thumb_func_start FUN_02064B70
FUN_02064B70: ; 0x02064B70
	push {r4-r5, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x3
	bhi _02064C52
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02064B96: ; jump table (using 16-bit offset)
	.short _02064B9E - _02064B96 - 2; case 0
	.short _02064BB4 - _02064B96 - 2; case 1
	.short _02064C24 - _02064B96 - 2; case 2
	.short _02064C48 - _02064B96 - 2; case 3
_02064B9E:
	ldr r0, [r5, #0x38]
	mov r1, #0x0
	bl FUN_02055560
	ldr r0, [r4, #0xc]
	bl FUN_02064C64
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02064C52
_02064BB4:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _02064BCA
	add r0, r5, #0x0
	add r0, #0xa0
	ldr r0, [r0, #0x0]
	ldr r1, _02064C58 ; =0x00000102
	bl MOD05_021E7ED8
	str r0, [sp, #0xc]
	b _02064BEC
_02064BCA:
	ldr r0, _02064C5C ; =UNK_020F7D4C
	add r1, sp, #0x4
	ldr r2, [r0, #0x10]
	ldr r0, [r0, #0x14]
	str r2, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x2
	add r3, sp, #0xc
	bl FUN_0204AA5C
	cmp r0, #0x0
	bne _02064BEC
	bl ErrorHandling
_02064BEC:
	ldr r1, [sp, #0xc]
	add r0, sp, #0x10
	bl MOD05_021E7EA0
	mov r0, #0x1
	ldr r1, [sp, #0x14]
	lsl r0, r0, #0xc
	sub r1, r1, r0
	str r1, [sp, #0x14]
	ldr r0, [r4, #0x4]
	cmp r1, r0
	bgt _02064C12
	str r0, [sp, #0x14]
	ldr r0, [r4, #0xc]
	bl FUN_02064C84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
_02064C12:
	ldr r0, [r5, #0x38]
	ldr r1, [sp, #0x14]
	bl FUN_02055540
	ldr r0, [sp, #0xc]
	add r1, sp, #0x10
	bl MOD05_021E7EB0
	b _02064C52
_02064C24:
	add r2, r5, #0x0
	add r2, #0x9c
	ldr r1, [r4, #0x4]
	ldr r2, [r2, #0x0]
	mov r0, #0x0
	bl MOD05_021F4594
	ldr r0, [r5, #0x38]
	mov r1, #0x1
	bl FUN_0205557C
	ldr r0, _02064C60 ; =0x0000061A
	bl FUN_020054C8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02064C52
_02064C48:
	bl FreeToHeap
	add sp, #0x1c
	mov r0, #0x1
	pop {r4-r5, pc}
_02064C52:
	mov r0, #0x0
	add sp, #0x1c
	pop {r4-r5, pc}
	.balign 4
_02064C58: .word 0x00000102
_02064C5C: .word UNK_020F7D4C
_02064C60: .word 0x0000061A

	thumb_func_start FUN_02064C64
FUN_02064C64: ; 0x02064C64
	push {r3, lr}
	cmp r0, #0x0
	bne _02064C72
	ldr r0, _02064C7C ; =0x00000611
	bl FUN_020054C8
	pop {r3, pc}
_02064C72:
	ldr r0, _02064C80 ; =0x00000614
	bl FUN_020054C8
	pop {r3, pc}
	nop
_02064C7C: .word 0x00000611
_02064C80: .word 0x00000614

	thumb_func_start FUN_02064C84
FUN_02064C84: ; 0x02064C84
	push {r3, lr}
	cmp r0, #0x0
	bne _02064C94
	ldr r0, _02064CA0 ; =0x00000611
	mov r1, #0x0
	bl FUN_020054F0
	pop {r3, pc}
_02064C94:
	ldr r0, _02064CA4 ; =0x00000614
	mov r1, #0x0
	bl FUN_020054F0
	pop {r3, pc}
	nop
_02064CA0: .word 0x00000611
_02064CA4: .word 0x00000614
