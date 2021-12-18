	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global UNK_021C5A1C
UNK_021C5A1C: ; 0x021C5A1C
	.space 0x4c

	.text

	thumb_func_start FUN_0204B9EC
FUN_0204B9EC: ; 0x0204B9EC
	push {r4, lr}
	ldr r1, _0204BA14 ; =UNK_021C5A1C
	add r4, r0, #0x0
	mov r0, #0x0
	mov r2, #0x4c
	bl MIi_CpuClearFast
	ldr r1, _0204BA14 ; =UNK_021C5A1C
	add r0, r4, #0x0
	bl FUN_0204BB20
	ldr r0, _0204BA14 ; =UNK_021C5A1C
	bl FUN_0204BBC4
	bl GF_RTC_DateTimeToSec
	ldr r2, _0204BA18 ; =UNK_021C5A1C
	str r0, [r2, #0x40]
	str r1, [r2, #0x44]
	pop {r4, pc}
	.balign 4
_0204BA14: .word UNK_021C5A1C
_0204BA18: .word UNK_021C5A1C

	thumb_func_start FUN_0204BA1C
FUN_0204BA1C: ; 0x0204BA1C
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	ldr r4, _0204BA60 ; =UNK_021C5A1C
	bl Sav2_GameStats_get
	add r5, r0, #0x0
	bl GF_RTC_DateTimeToSec
	add r3, r1, #0x0
	ldr r1, _0204BA64 ; =UNK_021C5A1C
	add r2, r0, #0x0
	ldr r0, [r1, #0x40]
	ldr r1, [r1, #0x44]
	bl GF_RTC_TimeDelta
	mov r2, #0xfa
	mov r3, #0x0
	lsl r2, r2, #0x2
	sub r2, r0, r2
	sbc r1, r3
	bge _0204BA50
	mov r1, #0xfa
	lsl r1, r1, #0x2
	sub r0, r1, r0
	lsl r0, r0, #0x1
	b _0204BA52
_0204BA50:
	mov r0, #0x0
_0204BA52:
	str r0, [r4, #0x48]
	add r0, r5, #0x0
	mov r1, #0x11
	bl GameStats_AddSpecial
	pop {r3-r5, pc}
	nop
_0204BA60: .word UNK_021C5A1C
_0204BA64: .word UNK_021C5A1C

	thumb_func_start FUN_0204BA68
FUN_0204BA68: ; 0x0204BA68
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _0204BA8C ; =UNK_021C5A1C
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0204BBE8
	cmp r0, #0x1
	bne _0204BA88
	ldr r1, _0204BA8C ; =UNK_021C5A1C
	add r0, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_0204BC48
	pop {r4-r6, pc}
_0204BA88:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_0204BA8C: .word UNK_021C5A1C

	thumb_func_start FUN_0204BA90
FUN_0204BA90: ; 0x0204BA90
	ldr r3, _0204BA98 ; =FUN_0204BD40
	ldr r1, _0204BA9C ; =UNK_021C5A1C
	bx r3
	nop
_0204BA98: .word FUN_0204BD40
_0204BA9C: .word UNK_021C5A1C

	thumb_func_start FUN_0204BAA0
FUN_0204BAA0: ; 0x0204BAA0
	ldr r3, _0204BAA8 ; =FUN_0204BD18
	ldr r2, _0204BAAC ; =UNK_021C5A1C
	bx r3
	nop
_0204BAA8: .word FUN_0204BD18
_0204BAAC: .word UNK_021C5A1C

	thumb_func_start FUN_0204BAB0
FUN_0204BAB0: ; 0x0204BAB0
	push {r3, lr}
	ldr r0, _0204BAC0 ; =UNK_021C5A1C
	bl FUN_0204BBA8
	mov r1, #0x6
	sub r0, r1, r0
	pop {r3, pc}
	nop
_0204BAC0: .word UNK_021C5A1C

	thumb_func_start FUN_0204BAC4
FUN_0204BAC4: ; 0x0204BAC4
	ldr r3, _0204BACC ; =FUN_0204BD8C
	ldr r0, _0204BAD0 ; =UNK_021C5A1C
	bx r3
	nop
_0204BACC: .word FUN_0204BD8C
_0204BAD0: .word UNK_021C5A1C

	thumb_func_start FUN_0204BAD4
FUN_0204BAD4: ; 0x0204BAD4
	ldr r3, _0204BADC ; =FUN_0204BE10
	ldr r0, _0204BAE0 ; =UNK_021C5A1C
	bx r3
	nop
_0204BADC: .word FUN_0204BE10
_0204BAE0: .word UNK_021C5A1C

	thumb_func_start FUN_0204BAE4
FUN_0204BAE4: ; 0x0204BAE4
	ldr r3, _0204BAEC ; =FUN_0204BDA0
	ldr r0, _0204BAF0 ; =UNK_021C5A1C
	bx r3
	nop
_0204BAEC: .word FUN_0204BDA0
_0204BAF0: .word UNK_021C5A1C

	thumb_func_start FUN_0204BAF4
FUN_0204BAF4: ; 0x0204BAF4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	beq _0204BB04
	ldr r0, _0204BB1C ; =0x000001ED
	cmp r5, r0
	bls _0204BB08
_0204BB04:
	bl GF_AssertFail
_0204BB08:
	mov r3, #0x6
	add r0, r4, #0x0
	sub r4, r5, #0x1
	str r3, [sp, #0x0]
	mov r1, #0x83
	mov r2, #0x0
	mul r3, r4
	bl ReadFromNarcMemberByIdPair
	pop {r3-r5, pc}
	.balign 4
_0204BB1C: .word 0x000001ED

	thumb_func_start FUN_0204BB20
FUN_0204BB20: ; 0x0204BB20
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r0, [r0, #0xc]
	str r1, [sp, #0x0]
	bl FUN_02022528
	str r0, [sp, #0x4]
	mov r0, #0x4
	bl AllocMonZeroed
	ldr r5, [sp, #0x0]
	add r4, r0, #0x0
	mov r6, #0x0
	add r7, sp, #0x8
_0204BB3C:
	ldr r0, [sp, #0x0]
	add r2, r4, #0x0
	add r1, r0, r6
	add r1, #0x30
	mov r0, #0x0
	strb r0, [r1, #0x0]
	ldr r0, [sp, #0x4]
	add r1, r6, #0x0
	bl FUN_0202BFD8
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	strh r0, [r5, #0x0]
	add r1, sp, #0x8
	bl FUN_0204BAF4
	ldrb r0, [r7, #0x0]
	cmp r0, #0x0
	beq _0204BB6E
	b _0204BB72
_0204BB6E:
	ldrb r0, [r7, #0x1]
	add r0, r0, #0x4
_0204BB72:
	strb r0, [r5, #0x2]
	ldrb r0, [r7, #0x3]
	mov r1, #0xb0
	mov r2, #0x0
	strb r0, [r5, #0x3]
	ldrb r0, [r7, #0x2]
	strh r0, [r5, #0x4]
	add r0, r4, #0x0
	bl GetMonData
	strb r0, [r5, #0x6]
	add r0, r4, #0x0
	mov r1, #0xb1
	mov r2, #0x0
	bl GetMonData
	strb r0, [r5, #0x7]
	add r6, r6, #0x1
	add r5, #0x8
	cmp r6, #0x6
	blt _0204BB3C
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204BBA8
FUN_0204BBA8: ; 0x0204BBA8
	mov r3, #0x0
	add r2, r3, #0x0
_0204BBAC:
	add r1, r0, r2
	add r1, #0x30
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0204BBB8
	add r3, r3, #0x1
_0204BBB8:
	add r2, r2, #0x1
	cmp r2, #0x6
	blt _0204BBAC
	add r0, r3, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0204BBC4
FUN_0204BBC4: ; 0x0204BBC4
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl LCRandom
	ldr r1, _0204BBE4 ; =0x0000199A
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0xa
	blo _0204BBDE
	bl GF_AssertFail
_0204BBDE:
	add r0, r5, #0x5
	str r0, [r4, #0x38]
	pop {r3-r5, pc}
	.balign 4
_0204BBE4: .word 0x0000199A

	thumb_func_start FUN_0204BBE8
FUN_0204BBE8: ; 0x0204BBE8
	push {r3, lr}
	ldr r1, [r0, #0x38]
	sub r1, r1, #0x1
	str r1, [r0, #0x38]
	bne _0204BBFA
	bl FUN_0204BBC4
	mov r0, #0x1
	pop {r3, pc}
_0204BBFA:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0204BC00
FUN_0204BC00: ; 0x0204BC00
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0204A6E0
	add r4, r0, #0x0
	cmp r5, #0x20
	blt _0204BC14
	mov r5, #0x1
	b _0204BC16
_0204BC14:
	mov r5, #0x0
_0204BC16:
	cmp r6, #0x20
	bge _0204BC1E
	mov r0, #0x0
	b _0204BC20
_0204BC1E:
	mov r0, #0x2
_0204BC20:
	add r5, r5, r0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_0205478C
	cmp r0, #0x0
	beq _0204BC32
	add r0, r5, #0x1
	pop {r4-r6, pc}
_0204BC32:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_0205481C
	cmp r0, #0x0
	beq _0204BC42
	add r0, r5, #0x5
	pop {r4-r6, pc}
_0204BC42:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204BC48
FUN_0204BC48: ; 0x0204BC48
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r1, r2, #0x0
	add r2, r3, #0x0
	mov r6, #0x0
	bl FUN_0204BC00
	add r7, r0, #0x0
	bne _0204BC5E
	add r0, r6, #0x0
	pop {r3-r7, pc}
_0204BC5E:
	add r0, r6, #0x0
	add r1, r5, #0x0
_0204BC62:
	add r2, r5, r0
	add r2, #0x30
	ldrb r2, [r2, #0x0]
	cmp r2, #0x0
	bne _0204BC76
	ldrb r2, [r1, #0x2]
	cmp r7, r2
	bne _0204BC76
	ldrb r2, [r1, #0x3]
	add r6, r6, r2
_0204BC76:
	add r0, r0, #0x1
	add r1, #0x8
	cmp r0, #0x6
	blt _0204BC62
	cmp r6, #0x0
	bne _0204BC86
	mov r0, #0x0
	pop {r3-r7, pc}
_0204BC86:
	add r0, r6, #0x0
	add r0, #0x14
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bne _0204BC94
	bl GF_AssertFail
_0204BC94:
	add r0, r6, #0x0
	add r0, #0x14
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0x1
	bhi _0204BCA4
	mov r4, #0x0
	b _0204BCD8
_0204BCA4:
	bl LCRandom
	add r1, r6, #0x0
	add r1, #0x14
	add r4, r0, #0x0
	lsl r1, r1, #0x10
	ldr r0, _0204BD14 ; =0x0000FFFF
	lsr r1, r1, #0x10
	bl _s32_div_f
	add r1, r0, #0x0
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	add r0, r4, #0x0
	lsr r1, r1, #0x10
	bl _s32_div_f
	lsl r0, r0, #0x10
	add r6, #0x14
	lsr r4, r0, #0x10
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	cmp r4, r0
	blo _0204BCD8
	bl GF_AssertFail
_0204BCD8:
	cmp r4, #0x14
	bge _0204BCE0
	mov r0, #0x0
	pop {r3-r7, pc}
_0204BCE0:
	sub r4, #0x14
	mov r1, #0x0
	add r0, r5, #0x0
_0204BCE6:
	add r2, r5, r1
	add r2, #0x30
	ldrb r2, [r2, #0x0]
	cmp r2, #0x0
	bne _0204BD04
	ldrb r2, [r0, #0x2]
	cmp r7, r2
	bne _0204BD04
	ldrb r2, [r0, #0x3]
	cmp r4, r2
	bge _0204BD02
	str r1, [r5, #0x3c]
	mov r0, #0x1
	pop {r3-r7, pc}
_0204BD02:
	sub r4, r4, r2
_0204BD04:
	add r1, r1, #0x1
	add r0, #0x8
	cmp r1, #0x6
	blt _0204BCE6
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0204BD14: .word 0x0000FFFF

	thumb_func_start FUN_0204BD18
FUN_0204BD18: ; 0x0204BD18
	push {r4, lr}
	ldr r0, [r1, #0x14]
	add r4, r2, #0x0
	cmp r0, #0x4
	beq _0204BD28
	cmp r0, #0x5
	beq _0204BD3E
	b _0204BD3A
_0204BD28:
	add r0, r4, #0x0
	bl FUN_0204BBA8
	add r1, r0, #0x1
	ldr r0, [r4, #0x3c]
	add r0, r4, r0
	add r0, #0x30
	strb r1, [r0, #0x0]
	pop {r4, pc}
_0204BD3A:
	bl GF_AssertFail
_0204BD3E:
	pop {r4, pc}

	thumb_func_start FUN_0204BD40
FUN_0204BD40: ; 0x0204BD40
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x20
	add r6, r1, #0x0
	bl AllocMonZeroed
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02022528
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_0204BAB0
	add r1, r0, #0x0
	mov r0, #0xb
	bl FUN_02047800
	add r1, r5, #0x0
	add r7, r0, #0x0
	bl FUN_02047BB0
	ldr r0, [sp, #0x0]
	ldr r1, [r6, #0x3c]
	add r2, r4, #0x0
	bl FUN_0202BFD8
	add r0, r7, #0x0
	add r1, r4, #0x0
	mov r2, #0x1
	bl FUN_020479FC
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r7, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204BD8C
FUN_0204BD8C: ; 0x0204BD8C
	mov r3, #0x0
	add r2, r3, #0x0
_0204BD90:
	ldrh r1, [r0, #0x4]
	add r2, r2, #0x1
	add r0, #0x8
	add r3, r3, r1
	cmp r2, #0x6
	blt _0204BD90
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_0204BDA0
FUN_0204BDA0: ; 0x0204BDA0
	push {r4-r7}
	mov r3, #0x0
	add r5, r0, #0x0
	add r4, r3, #0x0
	mov r0, #0x1
_0204BDAA:
	mov r1, #0x0
_0204BDAC:
	add r2, r5, r1
	add r2, #0x30
	ldrb r2, [r2, #0x0]
	cmp r0, r2
	bne _0204BDEC
	lsl r1, r1, #0x3
	add r2, r5, r1
	ldrb r1, [r2, #0x6]
	ldrb r2, [r2, #0x7]
	cmp r0, #0x1
	beq _0204BDD8
	mov r6, r12
	cmp r6, r1
	beq _0204BDD8
	mov r6, r12
	cmp r6, r2
	beq _0204BDD8
	cmp r7, r1
	beq _0204BDD8
	cmp r7, r2
	beq _0204BDD8
	add r4, #0xc8
_0204BDD8:
	mov r6, #0x1
	mov r12, r1
	lsl r6, r1
	add r1, r3, #0x0
	mov r3, #0x1
	lsl r3, r2
	orr r1, r6
	add r7, r2, #0x0
	orr r3, r1
	b _0204BDF2
_0204BDEC:
	add r1, r1, #0x1
	cmp r1, #0x6
	blt _0204BDAC
_0204BDF2:
	add r0, r0, #0x1
	cmp r0, #0x7
	blt _0204BDAA
	cmp r3, #0x0
	beq _0204BE0A
	mov r0, #0x1
_0204BDFE:
	add r1, r3, #0x0
	tst r1, r0
	beq _0204BE06
	add r4, #0x32
_0204BE06:
	lsr r3, r3, #0x1
	bne _0204BDFE
_0204BE0A:
	add r0, r4, #0x0
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_0204BE10
FUN_0204BE10: ; 0x0204BE10
	ldr r0, [r0, #0x48]
	bx lr
