	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021DB44C
MOD05_021DB44C: ; 0x021DB44C
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	cmp r6, #3
	blo _021DB45A
	bl ErrorHandling
_021DB45A:
	mov r0, #4
	mov r1, #0x14
	bl AllocFromHeap
	add r4, r0, #0
	ldr r0, _021DB4AC ; =UNK05_021F65FC
	lsl r1, r6, #2
	ldr r0, [r0, r1]
	str r5, [r4, #0xc]
	add r1, r4, #4
	bl MOD05_021DB61C
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #8]
	bl GF_RTC_TimeToSec
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r3, r1, #1
	ldr r5, [r4]
	mov r1, #0
	cmp r5, #0
	bls _021DB49E
	ldr r2, [r4, #4]
_021DB48C:
	ldr r0, [r2]
	cmp r0, r3
	bls _021DB496
	str r1, [r4, #8]
	b _021DB49E
_021DB496:
	add r1, r1, #1
	add r2, #0x30
	cmp r1, r5
	blo _021DB48C
_021DB49E:
	mov r0, #1
	str r0, [r4, #0x10]
	add r0, r4, #0
	bl MOD05_021DB5D4
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021DB4AC: .word UNK05_021F65FC

	thumb_func_start MOD05_021DB4B0
MOD05_021DB4B0: ; 0x021DB4B0
	push {r4, lr}
	add r4, r0, #0
	bne _021DB4BA
	bl ErrorHandling
_021DB4BA:
	ldr r0, [r4]
	add r0, r0, #4
	bl MOD05_021DB7A0
	ldr r1, [r4]
	mov r0, #4
	bl FreeToHeapExplicit
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}

	thumb_func_start MOD05_021DB4D0
MOD05_021DB4D0: ; 0x021DB4D0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bne _021DB4DA
	bl ErrorHandling
_021DB4DA:
	bl GF_RTC_TimeToSec
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r0, r1, #1
	ldr r1, [r4]
	cmp r1, #1
	bls _021DB528
	ldr r1, [r4, #8]
	sub r5, r1, #1
	bmi _021DB4FA
	mov r2, #0x30
	ldr r3, [r4, #4]
	mul r2, r5
	ldr r2, [r3, r2]
	b _021DB4FC
_021DB4FA:
	mov r2, #0
_021DB4FC:
	mov r3, #0x30
	ldr r5, [r4, #4]
	mul r3, r1
	ldr r1, [r5, r3]
	cmp r0, r1
	bge _021DB50C
	cmp r0, r2
	bge _021DB528
_021DB50C:
	ldr r0, [r4, #8]
	add r1, r0, #1
	str r1, [r4, #8]
	ldr r0, [r4]
	cmp r1, r0
	blo _021DB51C
	mov r0, #0
	str r0, [r4, #8]
_021DB51C:
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021DB528
	add r0, r4, #0
	bl MOD05_021DB5D4
_021DB528:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DB52C
MOD05_021DB52C: ; 0x021DB52C
	push {r3, lr}
	str r1, [r0, #0x10]
	cmp r1, #0
	beq _021DB538
	bl MOD05_021DB5D4
_021DB538:
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DB53C
MOD05_021DB53C: ; 0x021DB53C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp, #4]
	add r6, r1, #0
	mov r4, #0
	add r5, r0, #0
	add r7, r0, #0
_021DB54A:
	ldr r0, [sp, #4]
	ldrb r1, [r0, #4]
	mov r0, #1
	lsl r0, r4
	tst r0, r1
	beq _021DB578
	mov r0, #0x12
	ldrsh r0, [r5, r0]
	mov r2, #0xe
	mov r3, #0x10
	str r0, [sp]
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	add r0, r6, #0
	add r1, r4, #0
	bl MOD05_021DBC94
	ldrh r2, [r7, #6]
	add r0, r6, #0
	add r1, r4, #0
	bl MOD05_021DBCBC
	b _021DB592
_021DB578:
	mov r0, #0
	mov r2, #0
	str r0, [sp]
	add r0, r6, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD05_021DBC94
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD05_021DBCBC
_021DB592:
	add r4, r4, #1
	add r5, r5, #6
	add r7, r7, #2
	cmp r4, #4
	blt _021DB54A
	ldr r1, [sp, #4]
	mov r2, #0
	ldrh r1, [r1, #0x26]
	add r0, r6, #0
	add r3, r2, #0
	bl MOD05_021DBCD0
	ldr r1, [sp, #4]
	add r0, r6, #0
	ldrh r1, [r1, #0x28]
	mov r2, #1
	bl MOD05_021DBCE4
	ldr r1, [sp, #4]
	mov r2, #0
	ldrh r1, [r1, #0x2a]
	add r0, r6, #0
	add r3, r2, #0
	bl MOD05_021DBCF8
	ldr r1, [sp, #4]
	add r0, r6, #0
	ldrh r1, [r1, #0x2c]
	mov r2, #1
	bl MOD05_021DBD0C
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021DB5D4
MOD05_021DB5D4: ; 0x021DB5D4
	add r3, r0, #0
	ldr r1, [r3, #8]
	mov r0, #0x30
	mul r0, r1
	ldr r2, [r3, #4]
	ldr r1, [r3, #0xc]
	ldr r3, _021DB5E8 ; =MOD05_021DB53C
	add r0, r2, r0
	bx r3
	nop
_021DB5E8: .word MOD05_021DB53C

	thumb_func_start MOD05_021DB5EC
MOD05_021DB5EC: ; 0x021DB5EC
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x40
	bl FUN_020BC094
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x80
	bl FUN_020BC094
	mov r2, #2
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #8
	bl FUN_020BC094
	mov r2, #1
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #0xa
	bl FUN_020BC094
	pop {r4, pc}

	thumb_func_start MOD05_021DB61C
MOD05_021DB61C: ; 0x021DB61C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1fc
	sub sp, #0x20
	add r2, r0, #0
	str r1, [sp]
	mov r0, #4
	add r1, r2, #0
	bl FUN_020161A4
	mov r1, #0
	str r0, [sp, #0x14]
	str r1, [sp, #8]
	add r5, sp, #0x11c
	mov r6, #1
	mov r7, #2
	add r4, r1, #0
_021DB63C:
	add r1, r5, #0
	mov r2, #0xd
	bl FUN_0201C6C8
	ldrsb r1, [r5, r4]
	cmp r1, #0x45
	bne _021DB656
	ldrsb r1, [r5, r6]
	cmp r1, #0x4f
	bne _021DB656
	ldrsb r1, [r5, r7]
	cmp r1, #0x46
	beq _021DB6A4
_021DB656:
	add r1, r5, #0
	mov r2, #0xd
	bl FUN_0201C6C8
	add r1, r5, #0
	mov r2, #0xd
	bl FUN_0201C6C8
	add r1, r5, #0
	mov r2, #0xd
	bl FUN_0201C6C8
	add r1, r5, #0
	mov r2, #0xd
	bl FUN_0201C6C8
	add r1, r5, #0
	mov r2, #0xd
	bl FUN_0201C6C8
	add r1, r5, #0
	mov r2, #0xd
	bl FUN_0201C6C8
	add r1, r5, #0
	mov r2, #0xd
	bl FUN_0201C6C8
	add r1, r5, #0
	mov r2, #0xd
	bl FUN_0201C6C8
	add r1, r5, #0
	mov r2, #0xd
	bl FUN_0201C6C8
	ldr r1, [sp, #8]
	add r1, r1, #1
	str r1, [sp, #8]
_021DB6A4:
	mov r1, #0
	ldrsb r1, [r5, r1]
	cmp r1, #0x45
	bne _021DB63C
	mov r1, #1
	ldrsb r1, [r5, r1]
	cmp r1, #0x4f
	bne _021DB63C
	mov r1, #2
	ldrsb r1, [r5, r1]
	cmp r1, #0x46
	bne _021DB63C
	ldr r0, [sp, #8]
	mov r1, #0x30
	add r4, r0, #0
	mul r4, r1
	mov r0, #4
	add r1, r4, #0
	bl AllocFromHeap
	ldr r1, [sp]
	add r2, r4, #0
	str r0, [r1]
	mov r1, #0
	bl MI_CpuFill8
	mov r1, #0
	str r1, [sp, #0x18]
	ldr r1, [sp, #8]
	ldr r0, [sp, #0x14]
	cmp r1, #0
	ble _021DB78A
	ldr r1, [sp, #0x18]
	str r1, [sp, #0x10]
_021DB6E8:
	ldr r1, [sp]
	mov r2, #0xd
	ldr r5, [r1]
	ldr r1, [sp, #0x10]
	add r4, r5, r1
	add r1, sp, #0x11c
	bl FUN_0201C6C8
	str r0, [sp, #4]
	add r0, sp, #0x11c
	add r1, sp, #0x1c
	mov r2, #0x2c
	bl FUN_0201C6C8
	add r0, sp, #0x1c
	bl FUN_0201C70C
	ldr r1, [sp, #0x10]
	add r6, r4, #0
	str r0, [r5, r1]
	add r0, r4, #6
	mov r7, #0
	add r6, #0xe
	str r0, [sp, #0xc]
	add r5, r4, #0
_021DB71A:
	ldr r0, [sp, #4]
	ldr r1, [sp, #0xc]
	add r2, r6, #0
	bl MOD05_021DB7B4
	str r0, [sp, #4]
	ldrh r1, [r5, #6]
	ldr r0, _021DB79C ; =0x0000FFFF
	cmp r1, r0
	beq _021DB73A
	mov r0, #1
	ldrb r1, [r4, #4]
	lsl r0, r7
	orr r0, r1
	strb r0, [r4, #4]
	b _021DB73E
_021DB73A:
	mov r0, #0
	strh r0, [r5, #6]
_021DB73E:
	ldr r0, [sp, #0xc]
	add r7, r7, #1
	add r0, r0, #2
	add r6, r6, #6
	add r5, r5, #2
	str r0, [sp, #0xc]
	cmp r7, #4
	blt _021DB71A
	add r1, r4, #0
	ldr r0, [sp, #4]
	add r1, #0x26
	bl MOD05_021DB8A4
	add r1, r4, #0
	add r1, #0x28
	bl MOD05_021DB8A4
	add r1, r4, #0
	add r1, #0x2a
	bl MOD05_021DB8A4
	add r4, #0x2c
	add r1, r4, #0
	bl MOD05_021DB8A4
	add r1, sp, #0x11c
	mov r2, #0xd
	bl FUN_0201C6C8
	ldr r1, [sp, #0x10]
	add r1, #0x30
	str r1, [sp, #0x10]
	ldr r1, [sp, #0x18]
	add r2, r1, #1
	ldr r1, [sp, #8]
	str r2, [sp, #0x18]
	cmp r2, r1
	blt _021DB6E8
_021DB78A:
	ldr r1, [sp, #0x14]
	mov r0, #4
	bl FreeToHeapExplicit
	ldr r0, [sp, #8]
	add sp, #0x1fc
	add sp, #0x20
	pop {r4, r5, r6, r7, pc}
	nop
_021DB79C: .word 0x0000FFFF

	thumb_func_start MOD05_021DB7A0
MOD05_021DB7A0: ; 0x021DB7A0
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	mov r0, #4
	bl FreeToHeapExplicit
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DB7B4
MOD05_021DB7B4: ; 0x021DB7B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1fc
	sub sp, #0x20
	str r1, [sp, #4]
	add r7, r2, #0
	add r1, sp, #0x11c
	mov r2, #0xd
	bl FUN_0201C6C8
	str r0, [sp]
	add r0, sp, #0x11c
	add r1, sp, #0x1c
	mov r2, #0x2c
	bl FUN_0201C6C8
	add r4, r0, #0
	add r0, sp, #0x1c
	bl FUN_0201C70C
	cmp r0, #1
	bne _021DB88C
	mov r6, #0
	add r5, sp, #8
_021DB7E2:
	add r0, r4, #0
	add r1, sp, #0x1c
	mov r2, #0x2c
	bl FUN_0201C6C8
	add r4, r0, #0
	add r0, sp, #0x1c
	bl FUN_0201C70C
	strh r0, [r5]
	add r6, r6, #1
	add r5, r5, #2
	cmp r6, #3
	blt _021DB7E2
	add r1, sp, #8
	ldrh r0, [r1, #4]
	ldrh r2, [r1]
	ldrh r1, [r1, #2]
	lsl r0, r0, #0xa
	mov r6, #0
	lsl r1, r1, #5
	orr r1, r2
	orr r1, r0
	ldr r0, [sp, #4]
	add r5, sp, #0x10
	strh r1, [r0]
_021DB816:
	add r0, r4, #0
	add r1, sp, #0x1c
	mov r2, #0x2c
	bl FUN_0201C6C8
	add r4, r0, #0
	add r0, sp, #0x1c
	bl FUN_0201C70C
	add r6, r6, #1
	stmia r5!, {r0}
	cmp r6, #3
	blt _021DB816
	ldr r0, [sp, #0x10]
	strh r0, [r7]
	ldr r0, [sp, #0x14]
	strh r0, [r7, #2]
	ldr r0, [sp, #0x18]
	strh r0, [r7, #4]
	mov r0, #0
	ldrsh r1, [r7, r0]
	mov r0, #1
	lsl r0, r0, #0xc
	cmp r1, r0
	ble _021DB84A
	strh r0, [r7]
_021DB84A:
	mov r0, #0
	ldrsh r1, [r7, r0]
	ldr r0, _021DB89C ; =0xFFFFF000
	cmp r1, r0
	bge _021DB856
	strh r0, [r7]
_021DB856:
	mov r0, #2
	ldrsh r2, [r7, r0]
	lsl r1, r0, #0xb
	cmp r2, r1
	ble _021DB864
	lsl r0, r0, #0xb
	strh r0, [r7, #2]
_021DB864:
	mov r0, #2
	ldrsh r1, [r7, r0]
	ldr r0, _021DB89C ; =0xFFFFF000
	cmp r1, r0
	bge _021DB870
	strh r0, [r7, #2]
_021DB870:
	mov r0, #4
	ldrsh r2, [r7, r0]
	lsl r1, r0, #0xa
	cmp r2, r1
	ble _021DB87E
	lsl r0, r0, #0xa
	strh r0, [r7, #4]
_021DB87E:
	mov r0, #4
	ldrsh r1, [r7, r0]
	ldr r0, _021DB89C ; =0xFFFFF000
	cmp r1, r0
	bge _021DB892
	strh r0, [r7, #4]
	b _021DB892
_021DB88C:
	ldr r1, _021DB8A0 ; =0x0000FFFF
	ldr r0, [sp, #4]
	strh r1, [r0]
_021DB892:
	ldr r0, [sp]
	add sp, #0x1fc
	add sp, #0x20
	pop {r4, r5, r6, r7, pc}
	nop
_021DB89C: .word 0xFFFFF000
_021DB8A0: .word 0x0000FFFF

	thumb_func_start MOD05_021DB8A4
MOD05_021DB8A4: ; 0x021DB8A4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x1fc
	sub sp, #0x14
	str r1, [sp, #4]
	add r1, sp, #0x10c
	add r1, #2
	mov r2, #0xd
	bl FUN_0201C6C8
	add r6, sp, #0x10c
	add r7, sp, #0xc
	str r0, [sp]
	add r6, #2
	mov r4, #0
	add r5, sp, #8
	add r7, #2
_021DB8C4:
	add r0, r6, #0
	add r1, r7, #0
	mov r2, #0x2c
	bl FUN_0201C6C8
	add r6, r0, #0
	add r0, r7, #0
	bl FUN_0201C70C
	strh r0, [r5]
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #3
	blt _021DB8C4
	add r0, sp, #8
	ldrh r1, [r0, #4]
	lsl r2, r1, #0xa
	ldrh r1, [r0]
	ldrh r0, [r0, #2]
	lsl r0, r0, #5
	orr r0, r1
	add r1, r2, #0
	orr r1, r0
	ldr r0, [sp, #4]
	strh r1, [r0]
	ldr r0, [sp]
	add sp, #0x1fc
	add sp, #0x14
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	.section .rodata

	.global UNK05_021F65FC
UNK05_021F65FC: ; 0x021F65FC
	.word UNK05_021FD1F8, UNK05_021FD1E0, UNK05_021FD210

	.section .data

	.global UNK05_021FD1E0
UNK05_021FD1E0: ; 0x021FD1E0
	.asciz "data/area01light.txt"

	.balign 4
	.global UNK05_021FD1F8
UNK05_021FD1F8: ; 0x021FD1F8
	.asciz "data/area00light.txt"

	.balign 4
	.global UNK05_021FD210
UNK05_021FD210: ; 0x021FD210
	.asciz "data/area02light.txt"
