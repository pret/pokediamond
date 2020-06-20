    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020ECE64
UNK_020ECE64: ; 0x020ECE64
	.byte 0x7E, 0x01, 0x80, 0x01, 0x7F, 0x01, 0x00, 0x00

	.global UNK_020ECE6C
UNK_020ECE6C: ; 0x020ECE6C
	.byte 0x40, 0x01

	.global UNK_020ECE6E
UNK_020ECE6E: ; 0x020ECE6E
	.byte 0x08, 0x00, 0x60, 0x01, 0x10, 0x00, 0xA0, 0x01, 0x10, 0x00, 0xE0, 0x01, 0x10, 0x00, 0x20, 0x02
	.byte 0x10, 0x00, 0x60, 0x02, 0x10, 0x00, 0xA0, 0x02, 0x10, 0x00

	.text

	thumb_func_start FUN_0200AA80
FUN_0200AA80: ; 0x0200AA80
	ldr r3, _0200AA8C ; =FUN_0200AA90
	add r2, r0, #0x0
	mov r0, #0x8
	mov r1, #0x20
	bx r3
	nop
_0200AA8C: .word FUN_0200AA90

	thumb_func_start FUN_0200AA90
FUN_0200AA90: ; 0x0200AA90
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	bne _0200AAA0
	bl ErrorHandling
_0200AAA0:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _0200AAAA
	bl ErrorHandling
_0200AAAA:
	ldr r0, [sp, #0x4]
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	beq _0200AB10
	ldr r0, [sp, #0x4]
	str r7, [r4, #0x0]
	str r0, [r4, #0x4]
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	bl String_ctor
	str r0, [r4, #0xc]
	cmp r0, #0x0
	beq _0200AB10
	ldr r0, [sp, #0x4]
	lsl r1, r7, #0x3
	bl AllocFromHeapAtEnd
	str r0, [r4, #0x8]
	cmp r0, #0x0
	beq _0200AB10
	mov r6, #0x0
	cmp r7, #0x0
	bls _0200AB06
	add r5, r6, #0x0
_0200AAE0:
	add r0, r0, r5
	bl FUN_0200AB6C
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	bl String_ctor
	ldr r1, [r4, #0x8]
	add r1, r1, r5
	str r0, [r1, #0x4]
	ldr r0, [r4, #0x8]
	add r1, r0, r5
	ldr r1, [r1, #0x4]
	cmp r1, #0x0
	beq _0200AB06
	add r6, r6, #0x1
	add r5, #0x8
	cmp r6, r7
	blo _0200AAE0
_0200AB06:
	cmp r6, r7
	bne _0200AB10
	add sp, #0x8
	add r0, r4, #0x0
	pop {r3-r7, pc}
_0200AB10:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200AB18
FUN_0200AB18: ; 0x0200AB18
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	bne _0200AB26
	bl ErrorHandling
_0200AB26:
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	beq _0200AB54
	ldr r0, [r5, #0x0]
	mov r6, #0x0
	cmp r0, #0x0
	bls _0200AB4E
	add r4, r6, #0x0
_0200AB36:
	ldr r0, [r5, #0x8]
	add r0, r0, r4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0200AB4E
	bl String_dtor
	ldr r0, [r5, #0x0]
	add r6, r6, #0x1
	add r4, #0x8
	cmp r6, r0
	blo _0200AB36
_0200AB4E:
	ldr r0, [r5, #0x8]
	bl FreeToHeap
_0200AB54:
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	beq _0200AB5E
	bl String_dtor
_0200AB5E:
	mov r0, #0x0
	str r0, [r5, #0x0]
	add r0, r5, #0x0
	bl FreeToHeap
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200AB6C
FUN_0200AB6C: ; 0x0200AB6C
	bx lr
	.balign 4

	thumb_func_start FUN_0200AB70
FUN_0200AB70: ; 0x0200AB70
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	cmp r6, r0
	blo _0200AB84
	bl ErrorHandling
_0200AB84:
	ldr r0, [r5, #0x0]
	cmp r6, r0
	bhs _0200ABB2
	cmp r4, #0x0
	beq _0200ABA4
	ldrb r0, [r4, #0x0]
	ldr r3, [r5, #0x8]
	lsl r2, r6, #0x3
	strb r0, [r3, r2]
	ldrb r0, [r4, #0x1]
	add r1, r3, r2
	strb r0, [r1, #0x1]
	ldrb r0, [r4, #0x2]
	strb r0, [r1, #0x2]
	ldrb r0, [r4, #0x3]
	strb r0, [r1, #0x3]
_0200ABA4:
	ldr r1, [r5, #0x8]
	lsl r0, r6, #0x3
	add r0, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r7, #0x0
	bl StringCopy
_0200ABB2:
	pop {r3-r7, pc}

	thumb_func_start FUN_0200ABB4
FUN_0200ABB4: ; 0x0200ABB4
	push {r3, lr}
	mov r3, #0x0
	bl FUN_0200AB70
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0200ABC0
FUN_0200ABC0: ; 0x0200ABC0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r4, r1, #0x0
	bl FUN_0202398C
	add r1, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02021E28
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0200ABE4
FUN_0200ABE4: ; 0x0200ABE4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r4, r1, #0x0
	bl FUN_02024EC0
	bl FUN_02024EE8
	add r1, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02021E28
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0200AC0C
FUN_0200AC0C: ; 0x0200AC0C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r6, r1, #0x0
	bl FUN_020238F4
	add r7, r0, #0x0
	ldr r2, _0200AC5C ; =0x000001F1
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r4, r0, #0x0
	add r0, r7, #0x0
	bl FUN_020239CC
	cmp r0, #0x0
	bne _0200AC3E
	ldr r2, [r5, #0xc]
	add r0, r4, #0x0
	mov r1, #0x1
	bl ReadMsgDataIntoString
	b _0200AC48
_0200AC3E:
	ldr r2, [r5, #0xc]
	add r0, r4, #0x0
	mov r1, #0x0
	bl ReadMsgDataIntoString
_0200AC48:
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r4, #0x0
	bl DestroyMsgData
	pop {r3-r7, pc}
	.balign 4
_0200AC5C: .word 0x000001F1

	thumb_func_start FUN_0200AC60
FUN_0200AC60: ; 0x0200AC60
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r2, #0x0
	add r6, r1, #0x0
	ldr r2, _0200ACA0 ; =0x0000016A
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r4, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetBoxMonData
	add r1, r0, #0x0
	ldr r2, [r5, #0xc]
	add r0, r4, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r4, #0x0
	bl DestroyMsgData
	pop {r3-r7, pc}
	nop
_0200ACA0: .word 0x0000016A

	thumb_func_start FUN_0200ACA4
FUN_0200ACA4: ; 0x0200ACA4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetBoxMonData
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0200ACC0
	pop {r3-r5, pc}

	thumb_func_start FUN_0200ACC0
FUN_0200ACC0: ; 0x0200ACC0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200ACF4 ; =0x0000016B
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	add r7, r0, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
	pop {r3-r7, pc}
	nop
_0200ACF4: .word 0x0000016B

	thumb_func_start FUN_0200ACF8
FUN_0200ACF8: ; 0x0200ACF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r4, r1, #0x0
	ldr r2, [r5, #0xc]
	mov r1, #0x76
	bl GetBoxMonData
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0200AD18
FUN_0200AD18: ; 0x0200AD18
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r4, r1, #0x0
	ldr r2, [r5, #0xc]
	mov r1, #0x90
	bl GetBoxMonData
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0200AD38
FUN_0200AD38: ; 0x0200AD38
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [sp, #0x14]
	add r4, r1, #0x0
	str r0, [sp, #0x0]
	add r1, r2, #0x0
	add r2, r3, #0x0
	ldr r0, [r5, #0xc]
	ldr r3, [sp, #0x10]
	bl FUN_02021B04
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	pop {r3-r5, pc}

	thumb_func_start FUN_0200AD5C
FUN_0200AD5C: ; 0x0200AD5C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	mov r2, #0x93
	add r4, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200AD90
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200AD90:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200AD94
FUN_0200AD94: ; 0x0200AD94
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	mov r2, #0x79
	add r4, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200ADC8
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200ADC8:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200ADCC
FUN_0200ADCC: ; 0x0200ADCC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	mov r2, #0x8a
	add r4, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200AE00
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200AE00:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200AE04
FUN_0200AE04: ; 0x0200AE04
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r3, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xbe
	bl NewMsgDataFromNarc
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	add r7, r0, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200AE38
FUN_0200AE38: ; 0x0200AE38
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	mov r2, #0x56
	add r4, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200AE6C
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200AE6C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200AE70
FUN_0200AE70: ; 0x0200AE70
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200AEA4 ; =0x0000015A
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200AEA2
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200AEA2:
	pop {r3-r7, pc}
	.balign 4
_0200AEA4: .word 0x0000015A

	thumb_func_start FUN_0200AEA8
FUN_0200AEA8: ; 0x0200AEA8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200AEDC ; =0x0000015B
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200AEDA
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200AEDA:
	pop {r3-r7, pc}
	.balign 4
_0200AEDC: .word 0x0000015B

	thumb_func_start FUN_0200AEE0
FUN_0200AEE0: ; 0x0200AEE0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200AF14 ; =0x0000015D
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200AF12
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200AF12:
	pop {r3-r7, pc}
	.balign 4
_0200AF14: .word 0x0000015D

	thumb_func_start FUN_0200AF18
FUN_0200AF18: ; 0x0200AF18
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200AF4C ; =0x00000235
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200AF4A
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200AF4A:
	pop {r3-r7, pc}
	.balign 4
_0200AF4C: .word 0x00000235

	thumb_func_start FUN_0200AF50
FUN_0200AF50: ; 0x0200AF50
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200AF84 ; =0x000001EF
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200AF82
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200AF82:
	pop {r3-r7, pc}
	.balign 4
_0200AF84: .word 0x000001EF

	thumb_func_start FUN_0200AF88
FUN_0200AF88: ; 0x0200AF88
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r3, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xcd
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200AFBA
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200AFBA:
	pop {r3-r7, pc}

	thumb_func_start FUN_0200AFBC
FUN_0200AFBC: ; 0x0200AFBC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	mov r2, #0x89
	add r4, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200AFF0
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200AFF0:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200AFF4
FUN_0200AFF4: ; 0x0200AFF4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B028 ; =0x0000017E
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B026
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B026:
	pop {r3-r7, pc}
	.balign 4
_0200B028: .word 0x0000017E

	thumb_func_start FUN_0200B02C
FUN_0200B02C: ; 0x0200B02C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B060 ; =0x00000196
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B05E
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B05E:
	pop {r3-r7, pc}
	.balign 4
_0200B060: .word 0x00000196

	thumb_func_start FUN_0200B064
FUN_0200B064: ; 0x0200B064
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	mov r2, #0x23
	add r4, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x4
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B098
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B098:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200B09C
FUN_0200B09C: ; 0x0200B09C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B0D0 ; =0x00000231
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B0CE
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B0CE:
	pop {r3-r7, pc}
	.balign 4
_0200B0D0: .word 0x00000231

	thumb_func_start FUN_0200B0D4
FUN_0200B0D4: ; 0x0200B0D4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	mov r2, #0x23
	add r6, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x4
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B108
	ldrb r1, [r4, #0x1]
	ldr r2, [r5, #0xc]
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B108:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200B10C
FUN_0200B10C: ; 0x0200B10C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B140 ; =0x0000022F
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B13E
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B13E:
	pop {r3-r7, pc}
	.balign 4
_0200B140: .word 0x0000022F

	thumb_func_start FUN_0200B144
FUN_0200B144: ; 0x0200B144
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r2, #0x14
	add r4, r1, #0x0
	add r1, r2, #0x0
	bl FUN_02021E28
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0200B164
FUN_0200B164: ; 0x0200B164
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B198 ; =0x00000239
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B196
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B196:
	pop {r3-r7, pc}
	.balign 4
_0200B198: .word 0x00000239

	thumb_func_start FUN_0200B19C
FUN_0200B19C: ; 0x0200B19C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B1D0 ; =0x0000023A
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B1CE
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B1CE:
	pop {r3-r7, pc}
	.balign 4
_0200B1D0: .word 0x0000023A

	thumb_func_start FUN_0200B1D4
FUN_0200B1D4: ; 0x0200B1D4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B208 ; =0x0000023B
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B206
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B206:
	pop {r3-r7, pc}
	.balign 4
_0200B208: .word 0x0000023B

	thumb_func_start FUN_0200B20C
FUN_0200B20C: ; 0x0200B20C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	mov r2, #0x8f
	add r4, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B240
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B240:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200B244
FUN_0200B244: ; 0x0200B244
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r3, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xc2
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B276
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B276:
	pop {r3-r7, pc}

	thumb_func_start FUN_0200B278
FUN_0200B278: ; 0x0200B278
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r3, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xbf
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B2AA
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B2AA:
	pop {r3-r7, pc}

	thumb_func_start FUN_0200B2AC
FUN_0200B2AC: ; 0x0200B2AC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r3, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xbf
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B2DE
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B2DE:
	pop {r3-r7, pc}

	thumb_func_start FUN_0200B2E0
FUN_0200B2E0: ; 0x0200B2E0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B314 ; =0x0000023E
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B312
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B312:
	pop {r3-r7, pc}
	.balign 4
_0200B314: .word 0x0000023E

	thumb_func_start FUN_0200B318
FUN_0200B318: ; 0x0200B318
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B34C ; =0x0000023D
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B34A
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B34A:
	pop {r3-r7, pc}
	.balign 4
_0200B34C: .word 0x0000023D

	thumb_func_start FUN_0200B350
FUN_0200B350: ; 0x0200B350
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B384 ; =0x00000237
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B382
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B382:
	pop {r3-r7, pc}
	.balign 4
_0200B384: .word 0x00000237

	thumb_func_start FUN_0200B388
FUN_0200B388: ; 0x0200B388
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	mov r2, #0x8e
	add r4, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B3BC
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B3BC:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200B3C0
FUN_0200B3C0: ; 0x0200B3C0
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r3, [r5, #0x4]
	add r6, r1, #0x0
	add r4, r2, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xc7
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	cmp r4, #0x0
	beq _0200B3E0
	cmp r4, #0x1
	beq _0200B3EA
	b _0200B3F4
_0200B3E0:
	ldr r2, [r5, #0xc]
	mov r1, #0x44
	bl ReadMsgDataIntoString
	b _0200B3FA
_0200B3EA:
	ldr r2, [r5, #0xc]
	mov r1, #0x45
	bl ReadMsgDataIntoString
	b _0200B3FA
_0200B3F4:
	ldr r0, [r5, #0xc]
	bl StringSetEmpty
_0200B3FA:
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200B410
FUN_0200B410: ; 0x0200B410
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r4, r1, #0x0
	ldr r2, [r5, #0xc]
	add r1, r3, #0x0
	bl FUN_0206B484
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0200B430
FUN_0200B430: ; 0x0200B430
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B464 ; =0x0000014B
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B462
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B462:
	pop {r3-r7, pc}
	.balign 4
_0200B464: .word 0x0000014B

	thumb_func_start FUN_0200B468
FUN_0200B468: ; 0x0200B468
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B49C ; =0x00000226
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B49A
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B49A:
	pop {r3-r7, pc}
	.balign 4
_0200B49C: .word 0x00000226

	thumb_func_start FUN_0200B4A0
FUN_0200B4A0: ; 0x0200B4A0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	mov r2, #0x99
	add r4, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B4D4
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B4D4:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200B4D8
FUN_0200B4D8: ; 0x0200B4D8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r6, r1, #0x0
	add r4, r3, #0x0
	bl FUN_02088D40
	add r2, r0, #0x0
	beq _0200B516
	cmp r4, #0x0
	beq _0200B516
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B516
	ldr r2, [r5, #0xc]
	add r1, r4, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B516:
	pop {r3-r7, pc}

	thumb_func_start FUN_0200B518
FUN_0200B518: ; 0x0200B518
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0xc]
	add r0, r2, #0x0
	bl FUN_02013A58
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	pop {r3-r5, pc}

	thumb_func_start FUN_0200B534
FUN_0200B534: ; 0x0200B534
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r3, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xa
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B566
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B566:
	pop {r3-r7, pc}

	thumb_func_start FUN_0200B568
FUN_0200B568: ; 0x0200B568
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r3, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xb
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B59A
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B59A:
	pop {r3-r7, pc}

	thumb_func_start FUN_0200B59C
FUN_0200B59C: ; 0x0200B59C
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r7, r1, #0x0
	bl FUN_02015CC0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02015CE0
	add r4, r0, #0x0
	ldr r2, _0200B620 ; =UNK_020ECE64
	lsl r3, r6, #0x1
	ldrh r2, [r2, r3]
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r6, r0, #0x0
	beq _0200B61E
	bl MsgDataGetCount
	cmp r4, r0
	bhs _0200B5EE
	ldr r2, [r5, #0xc]
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r6, #0x0
	bl DestroyMsgData
	pop {r3-r7, pc}
_0200B5EE:
	add r0, r6, #0x0
	bl DestroyMsgData
	ldr r2, _0200B624 ; =0x0000017E
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r4, r0, #0x0
	beq _0200B61E
	ldr r2, [r5, #0xc]
	mov r1, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r4, #0x0
	bl DestroyMsgData
_0200B61E:
	pop {r3-r7, pc}
	.balign 4
_0200B620: .word UNK_020ECE64
_0200B624: .word 0x0000017E

	thumb_func_start FUN_0200B628
FUN_0200B628: ; 0x0200B628
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B65C ; =0x0000019E
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B65A
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B65A:
	pop {r3-r7, pc}
	.balign 4
_0200B65C: .word 0x0000019E

	thumb_func_start FUN_0200B660
FUN_0200B660: ; 0x0200B660
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B694 ; =0x00000152
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B692
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B692:
	pop {r3-r7, pc}
	.balign 4
_0200B694: .word 0x00000152

	thumb_func_start FUN_0200B698
FUN_0200B698: ; 0x0200B698
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r1, #0x0
	ldr r2, _0200B6CC ; =0x00000153
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B6CA
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B6CA:
	pop {r3-r7, pc}
	.balign 4
_0200B6CC: .word 0x00000153

	thumb_func_start FUN_0200B6D0
FUN_0200B6D0: ; 0x0200B6D0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	mov r2, #0x55
	add r4, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	beq _0200B704
	ldr r2, [r5, #0xc]
	add r1, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r7, #0x0
	bl DestroyMsgData
_0200B704:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200B708
FUN_0200B708: ; 0x0200B708
	push {r4-r7, lr}
	sub sp, #0x14
	str r0, [sp, #0x8]
	add r5, r2, #0x0
	add r0, r1, #0x0
	str r3, [sp, #0xc]
	bl FUN_0202881C
	add r6, r0, #0x0
	add r1, r5, #0x0
	bl FUN_020287F8
	str r0, [sp, #0x10]
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02028804
	add r7, r0, #0x0
	mov r0, #0x40
	mov r1, #0x4
	bl String_ctor
	add r4, r0, #0x0
	ldr r2, [sp, #0x28]
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_020287A8
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02021E28
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r2, r4, #0x0
	str r7, [sp, #0x4]
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl String_dtor
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_0200B764
FUN_0200B764: ; 0x0200B764
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	mov r2, #0x5b
	add r7, r1, #0x0
	ldr r3, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl NewMsgDataFromNarc
	add r6, r0, #0x0
	beq _0200B7A4
	cmp r4, #0x1
	blo _0200B786
	cmp r4, #0xc
	bls _0200B788
_0200B786:
	mov r4, #0x1
_0200B788:
	ldr r2, [r5, #0xc]
	add r0, r6, #0x0
	sub r1, r4, #0x1
	bl ReadMsgDataIntoString
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r3, #0x0
	bl FUN_0200AB70
	add r0, r6, #0x0
	bl DestroyMsgData
_0200B7A4:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200B7A8
FUN_0200B7A8: ; 0x0200B7A8
	ldr r2, [r0, #0x8]
	lsl r0, r1, #0x3
	add r0, r2, r0
	ldr r3, _0200B7B4 ; =FUN_02021FF8
	ldr r0, [r0, #0x4]
	bx r3
	.balign 4
_0200B7B4: .word FUN_02021FF8

	thumb_func_start StringExpandPlaceholders
StringExpandPlaceholders: ; 0x0200B7B8
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r6, r1, #0x0
	add r0, r2, #0x0
	bl String_c_str
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl StringSetEmpty
	ldrh r1, [r5, #0x0]
	ldr r0, _0200B844 ; =0x0000FFFF
	cmp r1, r0
	beq _0200B840
_0200B7D4:
	ldr r0, _0200B848 ; =0x0000FFFE
	cmp r1, r0
	bne _0200B82E
	add r0, r5, #0x0
	bl FUN_0201B8F8
	cmp r0, #0x0
	beq _0200B810
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0201B914
	add r4, r0, #0x0
	ldr r0, [r7, #0x0]
	cmp r4, r0
	blo _0200B7F8
	bl ErrorHandling
_0200B7F8:
	ldr r2, [r7, #0x8]
	lsl r1, r4, #0x3
	add r1, r2, r1
	ldr r1, [r1, #0x4]
	add r0, r6, #0x0
	bl FUN_02022048
	add r0, r5, #0x0
	bl FUN_0201B8B8
	add r5, r0, #0x0
	b _0200B838
_0200B810:
	add r0, r5, #0x0
	add r4, r5, #0x0
	bl FUN_0201B8B8
	add r5, r0, #0x0
	cmp r4, r5
	bhs _0200B838
_0200B81E:
	ldrh r1, [r4, #0x0]
	add r0, r6, #0x0
	add r4, r4, #0x2
	bl FUN_02021FB0
	cmp r4, r5
	blo _0200B81E
	b _0200B838
_0200B82E:
	ldrh r1, [r5, #0x0]
	add r0, r6, #0x0
	add r5, r5, #0x2
	bl FUN_02021FB0
_0200B838:
	ldrh r1, [r5, #0x0]
	ldr r0, _0200B844 ; =0x0000FFFF
	cmp r1, r0
	bne _0200B7D4
_0200B840:
	pop {r3-r7, pc}
	nop
_0200B844: .word 0x0000FFFF
_0200B848: .word 0x0000FFFE

	thumb_func_start FUN_0200B84C
FUN_0200B84C: ; 0x0200B84C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r6, #0x0
	cmp r0, #0x0
	bls _0200B86E
	add r4, r6, #0x0
_0200B85A:
	ldr r0, [r5, #0x8]
	add r0, r0, r4
	ldr r0, [r0, #0x4]
	bl StringSetEmpty
	ldr r0, [r5, #0x0]
	add r6, r6, #0x1
	add r4, #0x8
	cmp r6, r0
	blo _0200B85A
_0200B86E:
	pop {r4-r6, pc}

	thumb_func_start FUN_0200B870
FUN_0200B870: ; 0x0200B870
	push {r4-r7, lr}
	sub sp, #0x2c
	add r4, r3, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r4, #0x0
	mov r1, #0x2c
	str r2, [sp, #0x4]
	bl AllocFromHeap
	str r0, [sp, #0x8]
	cmp r0, #0x0
	beq _0200B98A
	ldr r3, [sp, #0x8]
	mov r0, #0xe
	mov r1, #0x4
	mov r2, #0x1
	add r3, r3, #0x4
	str r4, [sp, #0x0]
	bl FUN_02006BB0
	ldr r1, [sp, #0x8]
	mov r3, #0x0
	str r0, [r1, #0x0]
	add r0, r1, #0x0
	ldr r0, [r0, #0x4]
	ldr r4, [r0, #0x14]
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	bls _0200B984
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x4
	orr r1, r0
	str r1, [sp, #0xc]
	add r1, r0, #0x0
	orr r1, r5
	str r1, [sp, #0x10]
	orr r0, r6
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x4]
	lsl r0, r5, #0x4
	orr r1, r0
	str r1, [sp, #0x18]
	add r1, r5, #0x0
	orr r1, r0
	str r1, [sp, #0x1c]
	orr r0, r6
	lsl r2, r6, #0x4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x4]
	add r7, r2, #0x0
	orr r7, r1
	add r1, r2, #0x0
	orr r1, r5
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	orr r2, r6
	str r1, [sp, #0x28]
	lsl r1, r7, #0x18
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r0, [sp, #0x18]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	lsr r1, r1, #0x18
	lsl r0, r0, #0x18
	mov r12, r2
	str r1, [sp, #0x24]
	lsr r6, r0, #0x18
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	lsl r0, r0, #0x18
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
_0200B914:
	ldrb r5, [r4, r3]
	cmp r5, #0x12
	bgt _0200B93C
	bge _0200B962
	cmp r5, #0x10
	bgt _0200B936
	bge _0200B95A
	cmp r5, #0x2
	bgt _0200B978
	cmp r5, #0x0
	blt _0200B978
	beq _0200B94E
	cmp r5, #0x1
	beq _0200B952
	cmp r5, #0x2
	beq _0200B956
	b _0200B978
_0200B936:
	cmp r5, #0x11
	beq _0200B95E
	b _0200B978
_0200B93C:
	cmp r5, #0x21
	bgt _0200B948
	bge _0200B96E
	cmp r5, #0x20
	beq _0200B968
	b _0200B978
_0200B948:
	cmp r5, #0x22
	beq _0200B974
	b _0200B978
_0200B94E:
	strb r2, [r4, r3]
	b _0200B978
_0200B952:
	strb r1, [r4, r3]
	b _0200B978
_0200B956:
	strb r0, [r4, r3]
	b _0200B978
_0200B95A:
	strb r6, [r4, r3]
	b _0200B978
_0200B95E:
	strb r7, [r4, r3]
	b _0200B978
_0200B962:
	ldr r5, [sp, #0x20]
	strb r5, [r4, r3]
	b _0200B978
_0200B968:
	ldr r5, [sp, #0x24]
	strb r5, [r4, r3]
	b _0200B978
_0200B96E:
	ldr r5, [sp, #0x28]
	strb r5, [r4, r3]
	b _0200B978
_0200B974:
	mov r5, r12
	strb r5, [r4, r3]
_0200B978:
	ldr r5, [sp, #0x8]
	add r3, r3, #0x1
	ldr r5, [r5, #0x4]
	ldr r5, [r5, #0x10]
	cmp r3, r5
	blo _0200B914
_0200B984:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x8]
	str r1, [r0, #0x28]
_0200B98A:
	ldr r0, [sp, #0x8]
	add sp, #0x2c
	pop {r4-r7, pc}

	thumb_func_start FUN_0200B990
FUN_0200B990: ; 0x0200B990
	push {r4, lr}
	add r4, r0, #0x0
	beq _0200B9A6
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0200B9A0
	bl FreeToHeap
_0200B9A0:
	add r0, r4, #0x0
	bl FreeToHeap
_0200B9A6:
	pop {r4, pc}

	thumb_func_start FUN_0200B9A8
FUN_0200B9A8: ; 0x0200B9A8
	push {r3-r5, lr}
	sub sp, #0x18
	add r4, r0, #0x0
	ldr r0, _0200B9E4 ; =UNK_020ECE6E
	lsl r5, r1, #0x2
	ldrh r1, [r0, r5]
	lsl r3, r3, #0x10
	mov r0, #0x8
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	lsr r3, r3, #0x10
	str r3, [sp, #0x8]
	ldr r3, [sp, #0x28]
	lsl r3, r3, #0x10
	lsr r3, r3, #0x10
	str r3, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [r4, #0x4]
	add r0, r2, #0x0
	ldr r2, [r1, #0x14]
	ldr r1, _0200B9E8 ; =UNK_020ECE6C
	ldrh r1, [r1, r5]
	add r1, r2, r1
	mov r2, #0x0
	add r3, r2, #0x0
	bl FUN_02019658
	add sp, #0x18
	pop {r3-r5, pc}
	.balign 4
_0200B9E4: .word UNK_020ECE6E
_0200B9E8: .word UNK_020ECE6C

	thumb_func_start FUN_0200B9EC
FUN_0200B9EC: ; 0x0200B9EC
	push {r3-r7, lr}
	sub sp, #0x18
	add r6, r0, #0x0
	ldr r0, [sp, #0x30]
	add r4, r2, #0x0
	str r0, [sp, #0x30]
	add r0, r6, #0x0
	add r2, r3, #0x0
	add r0, #0x8
	add r3, r4, #0x0
	ldr r5, [sp, #0x34]
	ldr r7, [sp, #0x38]
	bl ConvertUIntToDecimalString
	ldrh r1, [r6, #0x8]
	ldr r0, _0200BA74 ; =0x0000FFFF
	cmp r1, r0
	beq _0200BA6E
	lsl r0, r7, #0x10
	add r4, r6, #0x0
	lsr r7, r0, #0x10
_0200BA16:
	ldrh r2, [r4, #0x8]
	cmp r2, #0xa2
	blo _0200BA4A
	cmp r2, #0xab
	bhi _0200BA4A
	mov r0, #0x8
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x8]
	str r7, [sp, #0xc]
	mov r0, #0x8
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [r6, #0x4]
	sub r2, #0xa2
	ldr r1, [r1, #0x14]
	lsl r2, r2, #0x5
	add r1, r1, r2
	mov r2, #0x0
	ldr r0, [sp, #0x30]
	add r3, r2, #0x0
	bl FUN_02019658
	b _0200BA62
_0200BA4A:
	mov r0, #0x8
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r1, [r6, #0x28]
	lsl r2, r5, #0x10
	lsl r1, r1, #0x18
	ldr r0, [sp, #0x30]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x10
	add r3, r7, #0x0
	bl FUN_020196F4
_0200BA62:
	add r4, r4, #0x2
	ldrh r1, [r4, #0x8]
	ldr r0, _0200BA74 ; =0x0000FFFF
	add r5, #0x8
	cmp r1, r0
	bne _0200BA16
_0200BA6E:
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_0200BA74: .word 0x0000FFFF
