	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021F5C44
MOD05_021F5C44: ; 0x021F5C44
	push {r3, r4, r5, lr}
	add r0, r1, #0
	mov r1, #0x18
	add r5, r2, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	add r2, r4, #0
	mov r1, #0x18
	mov r0, #0
_021F5C58:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _021F5C58
	add r0, r5, #0
	str r5, [r4, #0xc]
	bl MOD05_021F61B0
	str r0, [r4, #4]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5C70
MOD05_021F5C70: ; 0x021F5C70
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	bl FUN_02046528
	add r4, r0, #0
	add r0, r6, #0
	bl FUN_0204652C
	add r5, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _021F5C8E
	cmp r0, #1
	beq _021F5CBA
	b _021F5D28
_021F5C8E:
	ldr r0, [r4, #0x34]
	bl FUN_02058780
	mov r0, #0
	str r0, [r5, #0x10]
	add r2, r5, #0
	ldr r1, [r5, #0xc]
	add r0, r4, #0
	add r2, #0x10
	bl MOD06_0223BD14
	str r0, [r5, #8]
	ldr r1, [r5, #0xc]
	ldr r2, [r5, #8]
	add r0, r4, #0
	bl MOD05_021F5D2C
	str r0, [r5, #0x14]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021F5D28
_021F5CBA:
	ldr r0, [r5, #0x14]
	bl MOD05_021F5D50
	cmp r0, #1
	bne _021F5D28
	ldr r0, [r5, #0x14]
	bl MOD05_021F5D5C
	add r7, r0, #0
	ldr r0, [r5, #0x14]
	bl MOD05_021F5D68
	cmp r7, #1
	ldr r0, [r5, #0x10]
	bne _021F5D10
	ldr r0, [r0, #8]
	mov r1, #0
	bl GetPartyMonByIndex
	ldr r2, [r5, #4]
	add r3, r0, #0
	lsl r2, r2, #0x10
	add r0, r4, #0
	mov r1, #1
	lsr r2, r2, #0x10
	bl FUN_02061208
	ldr r0, [r4, #0xc]
	bl Sav2_GameStats_get
	mov r1, #0xa
	bl GameStats_Inc
	ldr r2, [r5, #0x10]
	add r0, r4, #0
	add r1, r6, #0
	bl FUN_02046A20
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F5D10:
	cmp r0, #0
	beq _021F5D18
	bl FUN_02047964
_021F5D18:
	ldr r0, [r4, #0x34]
	bl FUN_020587B0
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F5D28:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F5D2C
MOD05_021F5D2C: ; 0x021F5D2C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x4c
	add r4, r1, #0
	add r6, r2, #0
	bl MOD05_021F6074
	add r1, r0, #0
	str r5, [r1, #0x20]
	str r4, [r1, #0x1c]
	ldr r0, _021F5D4C ; =MOD05_021F5D7C
	mov r2, #0x80
	str r6, [r1]
	bl FUN_0200CA44
	pop {r4, r5, r6, pc}
	.align 2, 0
_021F5D4C: .word MOD05_021F5D7C

	thumb_func_start MOD05_021F5D50
MOD05_021F5D50: ; 0x021F5D50
	push {r3, lr}
	bl FUN_0201B6C8
	ldr r0, [r0, #4]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5D5C
MOD05_021F5D5C: ; 0x021F5D5C
	push {r3, lr}
	bl FUN_0201B6C8
	ldr r0, [r0, #8]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5D68
MOD05_021F5D68: ; 0x021F5D68
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0201B6C8
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start MOD05_021F5D7C
MOD05_021F5D7C: ; 0x021F5D7C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x20]
	ldr r6, [r0, #0x38]
	add r0, r6, #0
	bl FUN_020553A0
	ldr r7, _021F5DA4 ; =UNK05_021FC9B8
	add r4, r0, #0
_021F5D8E:
	ldr r3, [r5, #0xc]
	add r0, r5, #0
	lsl r3, r3, #2
	ldr r3, [r7, r3]
	add r1, r6, #0
	add r2, r4, #0
	blx r3
	cmp r0, #0
	bne _021F5D8E
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F5DA4: .word UNK05_021FC9B8

	thumb_func_start MOD05_021F5DA8
MOD05_021F5DA8: ; 0x021F5DA8
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r0, #0
	bl MOD05_021F60C4
	add r0, r4, #0
	bl FUN_02058914
	mov r0, #1
	str r0, [r5, #0xc]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5DC0
MOD05_021F5DC0: ; 0x021F5DC0
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r0, #0
	add r0, r6, #0
	add r4, r1, #0
	bl FUN_0205AD98
	cmp r0, #1
	bne _021F5DF2
	add r0, r6, #0
	bl FUN_0205AE50
	add r0, r4, #0
	mov r1, #0x20
	bl MOD05_021E5FD8
	add r0, r4, #0
	bl MOD05_021E5FE0
	add r0, r6, #0
	mov r1, #1
	bl FUN_02058544
	mov r0, #2
	str r0, [r5, #0xc]
_021F5DF2:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5DF8
MOD05_021F5DF8: ; 0x021F5DF8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	cmp r0, #0xa
	bne _021F5E0E
	mov r0, #0x65
	lsl r0, r0, #4
	bl PlaySE
_021F5E0E:
	ldr r0, [r4, #0x10]
	cmp r0, #0x22
	bge _021F5E18
	mov r0, #0
	pop {r4, pc}
_021F5E18:
	ldr r0, [r4]
	cmp r0, #1
	bne _021F5E22
	mov r0, #3
	b _021F5E24
_021F5E22:
	mov r0, #0xc
_021F5E24:
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x10]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5E30
MOD05_021F5E30: ; 0x021F5E30
	push {r4, lr}
	add r4, r0, #0
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r0, r0, #0x1e
	sub r0, r0, r1
	mov r2, #0x1e
	ror r0, r2
	add r0, r1, r0
	add r0, r0, #1
	add r1, r0, #0
	mul r1, r2
	str r1, [r4, #0x14]
	ldr r0, [r4, #0x1c]
	lsl r1, r0, #2
	ldr r0, _021F5E60 ; =UNK05_021FC9AC
	ldr r0, [r0, r1]
	str r0, [r4, #0x18]
	mov r0, #4
	str r0, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}
	nop
_021F5E60: .word UNK05_021FC9AC

	thumb_func_start MOD05_021F5E64
MOD05_021F5E64: ; 0x021F5E64
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x14]
	add r4, r2, #0
	sub r0, r0, #1
	str r0, [r5, #0x14]
	bl MOD05_021F6098
	cmp r0, #1
	bne _021F5E80
	mov r0, #0xa
	str r0, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F5E80:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	ble _021F5E8A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F5E8A:
	add r0, r4, #0
	mov r1, #2
	bl FUN_02058544
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl MOD05_021E7AC0
	str r0, [r5, #0x24]
	mov r0, #5
	str r0, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5EA8
MOD05_021F5EA8: ; 0x021F5EA8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	sub r0, r0, #1
	str r0, [r4, #0x18]
	bl MOD05_021F6098
	cmp r0, #1
	bne _021F5EC2
	mov r0, #6
	str r0, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}
_021F5EC2:
	ldr r0, [r4, #0x18]
	cmp r0, #0
	ble _021F5ECC
	mov r0, #0
	pop {r4, pc}
_021F5ECC:
	mov r0, #0xb
	str r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021F5ED4
MOD05_021F5ED4: ; 0x021F5ED4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x24]
	add r4, r2, #0
	bl FUN_02064520
	mov r0, #0
	str r0, [r5, #0x24]
	add r0, r4, #0
	mov r1, #3
	bl FUN_02058544
	mov r0, #0
	str r0, [r5, #0x10]
	mov r1, #7
	str r1, [r5, #0xc]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5EF8
MOD05_021F5EF8: ; 0x021F5EF8
	push {r3, lr}
	ldr r1, [r0, #0x10]
	add r1, r1, #1
	str r1, [r0, #0x10]
	cmp r1, #0xf
	ble _021F5F12
	mov r1, #0
	str r1, [r0, #0x10]
	mov r1, #8
	str r1, [r0, #0xc]
	mov r1, #0x39
	bl MOD05_021F6140
_021F5F12:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5F18
MOD05_021F5F18: ; 0x021F5F18
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021F617C
	cmp r0, #0
	bne _021F5F28
	mov r0, #0
	pop {r4, pc}
_021F5F28:
	mov r0, #9
	str r0, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD05_021F5F30
MOD05_021F5F30: ; 0x021F5F30
	mov r2, #1
	str r2, [r0, #8]
	mov r1, #0xf
	str r1, [r0, #0xc]
	add r0, r2, #0
	bx lr

	thumb_func_start MOD05_021F5F3C
MOD05_021F5F3C: ; 0x021F5F3C
	push {r4, lr}
	add r4, r0, #0
	add r0, r2, #0
	mov r1, #0
	bl FUN_02058544
	add r0, r4, #0
	mov r1, #0x38
	bl MOD05_021F6140
	mov r0, #0x10
	str r0, [r4, #0x10]
	mov r0, #0xe
	str r0, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD05_021F5F5C
MOD05_021F5F5C: ; 0x021F5F5C
	push {r4, lr}
	add r4, r0, #0
	add r0, r2, #0
	mov r1, #0
	bl FUN_02058544
	add r0, r4, #0
	mov r1, #0x37
	bl MOD05_021F6140
	mov r0, #0x10
	str r0, [r4, #0x10]
	mov r0, #0xe
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x20]
	ldr r0, [r0, #0xc]
	bl Sav2_GameStats_get
	mov r1, #0x49
	bl GameStats_Inc
	ldr r0, [r4, #0x1c]
	bl MOD05_021F61B0
	add r2, r0, #0
	mov r1, #0
	ldr r0, [r4, #0x20]
	add r3, r1, #0
	bl FUN_02061208
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD05_021F5F9C
MOD05_021F5F9C: ; 0x021F5F9C
	mov r1, #0x78
	str r1, [r0, #0x10]
	mov r1, #0xd
	str r1, [r0, #0xc]
	mov r0, #1
	bx lr

	thumb_func_start MOD05_021F5FA8
MOD05_021F5FA8: ; 0x021F5FA8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	add r4, r2, #0
	sub r0, r0, #1
	str r0, [r5, #0x10]
	bl MOD05_021F6098
	cmp r0, #1
	bne _021F5FC4
	mov r0, #0xa
	str r0, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F5FC4:
	ldr r0, [r5, #0x10]
	cmp r0, #0
	beq _021F5FCE
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F5FCE:
	add r0, r4, #0
	mov r1, #0
	bl FUN_02058544
	add r0, r5, #0
	mov r1, #0x36
	bl MOD05_021F6140
	mov r0, #0x10
	str r0, [r5, #0x10]
	mov r0, #0xe
	str r0, [r5, #0xc]
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5FEC
MOD05_021F5FEC: ; 0x021F5FEC
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x10]
	add r1, r1, #1
	str r1, [r4, #0x10]
	cmp r1, #0x10
	bge _021F5FFE
	mov r0, #0
	pop {r4, pc}
_021F5FFE:
	mov r1, #0x10
	str r1, [r4, #0x10]
	bl MOD05_021F617C
	cmp r0, #0
	bne _021F600E
	mov r0, #0
	pop {r4, pc}
_021F600E:
	mov r0, #0xf
	str r0, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD05_021F6018
MOD05_021F6018: ; 0x021F6018
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x24]
	add r4, r1, #0
	cmp r0, #0
	beq _021F602C
	bl FUN_02064520
	mov r0, #0
	str r0, [r5, #0x24]
_021F602C:
	add r0, r5, #0
	bl MOD05_021F60FC
	add r0, r4, #0
	bl FUN_020553C4
	bl FUN_02055648
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E5FD8
	add r0, r4, #0
	bl MOD05_021E5FE0
	mov r0, #0
	str r0, [r5, #0x10]
	mov r0, #0x10
	str r0, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F6058
MOD05_021F6058: ; 0x021F6058
	ldr r1, [r0, #0x10]
	add r1, r1, #1
	str r1, [r0, #0x10]
	cmp r1, #2
	ble _021F6066
	mov r1, #0x11
	str r1, [r0, #0xc]
_021F6066:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD05_021F606C
MOD05_021F606C: ; 0x021F606C
	mov r1, #1
	str r1, [r0, #4]
	mov r0, #0
	bx lr

	thumb_func_start MOD05_021F6074
MOD05_021F6074: ; 0x021F6074
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #4
	add r1, r5, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	bne _021F6088
	bl GF_AssertFail
_021F6088:
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl memset
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F6098
MOD05_021F6098: ; 0x021F6098
	ldr r0, _021F60A8 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r1, r0
	bne _021F60A4
	mov r0, #0
_021F60A4:
	bx lr
	nop
_021F60A8: .word gMain

	thumb_func_start MOD05_021F60AC
MOD05_021F60AC: ; 0x021F60AC
	ldr r0, _021F60C0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021F60BA
	mov r0, #1
	bx lr
_021F60BA:
	mov r0, #0
	bx lr
	nop
_021F60C0: .word gMain

	thumb_func_start MOD05_021F60C4
MOD05_021F60C4: ; 0x021F60C4
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	mov r1, #0x1a
	mov r2, #0xc7
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [r4, #0x48]
	mov r0, #1
	lsl r0, r0, #0xa
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x2c]
	mov r0, #1
	lsl r0, r0, #0xa
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x30]
	mov r0, #8
	mov r1, #0x40
	mov r2, #4
	bl ScrStrBufs_new_custom
	str r0, [r4, #0x34]
	pop {r4, pc}

	thumb_func_start MOD05_021F60FC
MOD05_021F60FC: ; 0x021F60FC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0x2c]
	bl String_dtor
	ldr r0, [r4, #0x30]
	bl String_dtor
	ldr r0, [r4, #0x48]
	bl DestroyMsgData
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD05_021F611C
MOD05_021F611C: ; 0x021F611C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5, #0x20]
	add r1, r5, #0
	ldr r0, [r4, #8]
	add r1, #0x38
	mov r2, #3
	bl FUN_020545B8
	ldr r0, [r4, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r5, #0x38
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_02054608
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F6140
MOD05_021F6140: ; 0x021F6140
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	bl MOD05_021F611C
	ldr r0, [r5, #0x48]
	ldr r2, [r5, #0x30]
	add r1, r6, #0
	ldr r4, [r5, #0x20]
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0x34]
	ldr r1, [r5, #0x2c]
	ldr r2, [r5, #0x30]
	bl StringExpandPlaceholders
	ldr r0, [r4, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r2, r0, #0
	add r0, r5, #0
	ldr r1, [r5, #0x2c]
	add r0, #0x38
	mov r3, #1
	bl FUN_02054658
	add r5, #0x28
	strb r0, [r5]
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD05_021F617C
MOD05_021F617C: ; 0x021F617C
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x28
	ldrb r0, [r0]
	bl FUN_020546C8
	cmp r0, #1
	bne _021F61AA
	bl MOD05_021F60AC
	cmp r0, #1
	bne _021F61AA
	add r0, r4, #0
	add r0, #0x38
	mov r1, #0
	bl ClearFrameAndWindow2
	add r4, #0x38
	add r0, r4, #0
	bl RemoveWindow
	mov r0, #1
	pop {r4, pc}
_021F61AA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD05_021F61B0
MOD05_021F61B0: ; 0x021F61B0
	push {r3, lr}
	cmp r0, #0
	beq _021F61C2
	cmp r0, #1
	beq _021F61C6
	cmp r0, #2
	beq _021F61CA
	bl GF_AssertFail
_021F61C2:
	ldr r0, _021F61D0 ; =0x000001BD
	pop {r3, pc}
_021F61C6:
	ldr r0, _021F61D4 ; =0x000001BE
	pop {r3, pc}
_021F61CA:
	ldr r0, _021F61D8 ; =0x000001BF
	pop {r3, pc}
	nop
_021F61D0: .word 0x000001BD
_021F61D4: .word 0x000001BE
_021F61D8: .word 0x000001BF

	.section .rodata

	.global UNK05_021FC718
UNK05_021FC718: ; 0x021FC718
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00
	.byte 0x1F, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x15, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00
	.byte 0x19, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FC79C
UNK05_021FC79C: ; 0x021FC79C
	.byte 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x09, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FC820
UNK05_021FC820: ; 0x021FC820
	.word 0x00, MOD06_022492B0, MOD06_022492D4
	.word 0x01, MOD06_022497A0, MOD06_022497BC
	.word 0x02, MOD05_021E52A8, MOD05_021E52C4
	.word 0x03, MOD05_021E5300, MOD05_021E531C
	.word 0x04, MOD05_021E5564, MOD05_021E5580
	.word 0x05, MOD05_021E55BC, MOD05_021E55D8
	.word 0x06, MOD05_021E577C, MOD05_021E5798
	.word 0x07, MOD05_021E5918, MOD05_021E5934
	.word 0x08, MOD05_021E5AB4, MOD05_021E5AD0
	.word 0x09, MOD05_021E5C8C, MOD05_021E5CA8
	.word 0x0A, MOD05_021E5E10, MOD05_021E5E2C
	.word 0x0B, MOD06_02249C98, MOD06_02249CB8
	.word 0x0C, MOD06_0224A040, MOD06_0224A05C
	.word 0x0D, MOD06_0224A280, MOD06_0224A29C
	.word 0x0E, MOD06_0224A63C, MOD06_0224A658
	.word 0x0F, MOD06_0224A87C, MOD06_0224A898
	.word 0x10, MOD05_021EDB70, MOD05_021EDB8C
	.word 0x11, MOD06_0224AB54, MOD06_0224AB70
	.word 0x12, MOD06_0224AE10, MOD06_0224AE24
	.word 0x13, MOD06_0224B0A8, MOD06_0224B0C4
	.word 0x14, MOD06_0224B248, MOD06_0224B264
	.word 0x15, MOD06_0224B3E4, MOD06_0224B400
	.word 0x16, MOD05_021E779C, MOD05_021E77B0
	.word 0x17, MOD06_0224B948, MOD06_0224B964
	.word 0x18, MOD05_021ED9C0, MOD05_021ED9DC
	.word 0x19, MOD06_0224BB50, MOD06_0224BB6C
	.word 0x1A, MOD06_0224BCF4, MOD06_0224BD10
	.word 0x1B, MOD06_0224BF9C, MOD06_0224BFB8
	.word 0x1C, MOD06_0224CE30, MOD06_0224CE4C
	.word 0x1D, MOD06_0224D244, MOD06_0224D260
	.word 0x1E, MOD06_0224A44C, MOD06_0224A460
	.word 0x1F, MOD06_0224A9E8, MOD06_0224AA04
	.word 0x20, 0x00000000, 0x00000000

	.global UNK05_021FC9AC
UNK05_021FC9AC: ; 0x021FC9AC
	.word 45, 30, 15

	.global UNK05_021FC9B8
UNK05_021FC9B8: ; 0x021FC9B8
	.word MOD05_021F5DA8, MOD05_021F5DC0, MOD05_021F5DF8, MOD05_021F5E30
	.word MOD05_021F5E64, MOD05_021F5EA8, MOD05_021F5ED4, MOD05_021F5EF8
	.word MOD05_021F5F18, MOD05_021F5F30, MOD05_021F5F3C, MOD05_021F5F5C
	.word MOD05_021F5F9C, MOD05_021F5FA8, MOD05_021F5FEC, MOD05_021F6018
	.word MOD05_021F6058, MOD05_021F606C
