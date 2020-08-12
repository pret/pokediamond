    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F96DC
	.extern UNK_020FA6E8

	.section .rodata

	.global UNK_020F7454
UNK_020F7454: ; 0x020F7454
	.byte 0x00, 0x01, 0x02, 0x04, 0x03, 0x05, 0x06, 0x07, 0x08, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_0205FA2C
FUN_0205FA2C: ; 0x0205FA2C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x40
	bl AllocFromHeapAtEnd
	ldr r6, [r7, #0xc]
	mov r1, #0x0
	mov r2, #0x40
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r6, #0x0
	bl LoadPlayerDataAddress
	str r0, [r4, #0xc]
	add r0, r6, #0x0
	bl SavArray_PlayerParty_get
	str r0, [r4, #0x0]
	add r0, r6, #0x0
	bl FUN_0206F158
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	ldrb r2, [r5, #0x8]
	add r0, #0x20
	strb r2, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x32
	ldrb r0, [r0, #0x0]
	mov r2, #0xf
	ldrb r3, [r5, #0xa]
	bic r0, r2
	mov r2, #0xf
	and r2, r3
	orr r2, r0
	add r0, r4, #0x0
	add r0, #0x32
	strb r2, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x32
	ldrb r0, [r0, #0x0]
	mov r2, #0xf0
	bic r0, r2
	ldrb r2, [r5, #0xb]
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x18
	orr r2, r0
	add r0, r4, #0x0
	add r0, #0x32
	strb r2, [r0, #0x0]
	add r0, r4, #0x0
	ldrb r2, [r5, #0xc]
	add r0, #0x33
	strb r2, [r0, #0x0]
	add r0, r4, #0x0
	ldrb r2, [r5, #0xd]
	add r0, #0x22
	strb r2, [r0, #0x0]
_0205FAAE:
	add r0, r5, r1
	ldrb r2, [r0, #0xe]
	add r0, r4, r1
	add r0, #0x2c
	strb r2, [r0, #0x0]
	add r0, r1, #0x1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, #0x6
	blo _0205FAAE
	ldr r1, _0205FAD4 ; =UNK_020F96DC
	add r0, r7, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	ldr r0, [r5, #0x14]
	str r4, [r0, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0205FAD4: .word UNK_020F96DC

	thumb_func_start FUN_0205FAD8
FUN_0205FAD8: ; 0x0205FAD8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0205FAEA
	mov r0, #0x1
	pop {r3-r5, pc}
_0205FAEA:
	ldr r0, [r5, #0x14]
	ldr r4, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	cmp r0, #0x6
	beq _0205FB04
	cmp r0, #0x7
	bne _0205FB0C
	mov r0, #0x0
	str r0, [r5, #0x0]
	mov r0, #0x4
	pop {r3-r5, pc}
_0205FB04:
	mov r0, #0x1
	str r0, [r5, #0x0]
	mov r0, #0x4
	pop {r3-r5, pc}
_0205FB0C:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r0, #0x2c
	add r1, #0xe
	mov r2, #0x6
	bl MI_CpuCopy8
	add r0, r4, #0x0
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	strb r0, [r5, #0xd]
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r0, [r5, #0x14]
	mov r1, #0x0
	str r1, [r0, #0x0]
	mov r0, #0x2
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205FB34
FUN_0205FB34: ; 0x0205FB34
	push {r3-r7, lr}
	add r7, r1, #0x0
	add r6, r0, #0x0
	ldr r5, [r7, #0xc]
	add r0, r2, #0x0
	mov r1, #0x30
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0x30
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r5, #0x0
	bl LoadPlayerDataAddress
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl SavArray_PlayerParty_get
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_0206BB28
	str r0, [r4, #0x1c]
	add r0, r5, #0x0
	bl FUN_02079C70
	str r0, [r4, #0x2c]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	ldrb r0, [r6, #0xd]
	strb r0, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl GetPartyCount
	strb r0, [r4, #0x13]
	mov r0, #0x0
	strh r0, [r4, #0x18]
	ldrb r0, [r6, #0x9]
	strb r0, [r4, #0x12]
	add r0, r5, #0x0
	bl FUN_0202A918
	str r0, [r4, #0x20]
	ldr r1, _0205FBB8 ; =UNK_020F7454
	add r0, r4, #0x0
	bl FUN_0207B000
	add r0, r5, #0x0
	bl Sav2_GetPlayerDataPtr
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0207C2A4
	ldr r1, _0205FBBC ; =UNK_020FA6E8
	add r0, r7, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	ldr r0, [r6, #0x14]
	str r4, [r0, #0x0]
	mov r0, #0x3
	pop {r3-r7, pc}
	nop
_0205FBB8: .word UNK_020F7454
_0205FBBC: .word UNK_020FA6E8

	thumb_func_start FUN_0205FBC0
FUN_0205FBC0: ; 0x0205FBC0
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0205FBD2
	mov r0, #0x3
	pop {r4, pc}
_0205FBD2:
	ldr r0, [r4, #0x14]
	ldr r0, [r0, #0x0]
	ldrb r1, [r0, #0x14]
	strb r1, [r4, #0xd]
	bl FreeToHeap
	ldr r1, [r4, #0x14]
	mov r0, #0x0
	str r0, [r1, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205FBE8
FUN_0205FBE8: ; 0x0205FBE8
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	cmp r1, #0x4
	bhi _0205FC4A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0205FC0C: ; jump table (using 16-bit offset)
	.short _0205FC16 - _0205FC0C - 2; case 0
	.short _0205FC22 - _0205FC0C - 2; case 1
	.short _0205FC2C - _0205FC0C - 2; case 2
	.short _0205FC38 - _0205FC0C - 2; case 3
	.short _0205FC42 - _0205FC0C - 2; case 4
_0205FC16:
	add r1, r5, #0x0
	mov r2, #0xb
	bl FUN_0205FA2C
	str r0, [r4, #0x4]
	b _0205FC4A
_0205FC22:
	add r1, r5, #0x0
	bl FUN_0205FAD8
	str r0, [r4, #0x4]
	b _0205FC4A
_0205FC2C:
	add r1, r5, #0x0
	mov r2, #0xb
	bl FUN_0205FB34
	str r0, [r4, #0x4]
	b _0205FC4A
_0205FC38:
	add r1, r5, #0x0
	bl FUN_0205FBC0
	str r0, [r4, #0x4]
	b _0205FC4A
_0205FC42:
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0205FC4A:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205FC50
FUN_0205FC50: ; 0x0205FC50
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_02046528
	str r0, [sp, #0x0]
	mov r0, #0xb
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x18
	bl MI_CpuFill8
	strb r6, [r4, #0x8]
	strb r7, [r4, #0x9]
	add r0, sp, #0x8
	ldrb r1, [r0, #0x10]
	add r2, r4, #0x0
	strb r1, [r4, #0xa]
	ldrb r1, [r0, #0x14]
	strb r1, [r4, #0xb]
	ldrb r1, [r0, #0x18]
	strb r1, [r4, #0xc]
	ldrb r0, [r0, #0x1c]
	ldr r1, _0205FC98 ; =FUN_0205FBE8
	strb r0, [r4, #0xd]
	ldr r0, [sp, #0x0]
	str r5, [r4, #0x14]
	ldr r0, [r0, #0x10]
	bl FUN_0204640C
	pop {r3-r7, pc}
	nop
_0205FC98: .word FUN_0205FBE8

	thumb_func_start FUN_0205FC9C
FUN_0205FC9C: ; 0x0205FC9C
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0203384C
	cmp r0, #0x0
	beq _0205FCBC
	ldrh r1, [r4, #0x12]
	ldrh r2, [r4, #0x14]
	add r0, r5, #0x0
	bl FUN_02038790
	str r0, [r4, #0x8]
	mov r0, #0x1
	pop {r3-r5, pc}
_0205FCBC:
	mov r0, #0x1
	str r0, [r4, #0x0]
	mov r0, #0x2
	pop {r3-r5, pc}

	thumb_func_start FUN_0205FCC4
FUN_0205FCC4: ; 0x0205FCC4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0205FCD6
	mov r0, #0x1
	pop {r4, pc}
_0205FCD6:
	ldr r0, [r4, #0x8]
	ldr r0, [r0, #0x20]
	str r0, [r4, #0x0]
	ldr r0, [r4, #0x8]
	bl FreeToHeap
	mov r0, #0x2
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205FCE8
FUN_0205FCE8: ; 0x0205FCE8
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	beq _0205FD0A
	cmp r1, #0x1
	beq _0205FD14
	cmp r1, #0x2
	beq _0205FD1E
	b _0205FD34
_0205FD0A:
	add r1, r5, #0x0
	bl FUN_0205FC9C
	str r0, [r4, #0x4]
	b _0205FD34
_0205FD14:
	add r1, r5, #0x0
	bl FUN_0205FCC4
	str r0, [r4, #0x4]
	b _0205FD34
_0205FD1E:
	ldrh r1, [r4, #0x10]
	add r0, r5, #0x0
	bl GetVarPointer
	ldr r1, [r4, #0x0]
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0205FD34:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0205FD38
FUN_0205FD38: ; 0x0205FD38
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_02046528
	str r0, [sp, #0x0]
	mov r0, #0xb
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x18
	bl MI_CpuFill8
	strh r5, [r4, #0x12]
	strh r7, [r4, #0x14]
	ldr r0, [sp, #0x0]
	strh r6, [r4, #0x10]
	ldr r0, [r0, #0x10]
	ldr r1, _0205FD6C ; =FUN_0205FCE8
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r3-r7, pc}
	.balign 4
_0205FD6C: .word FUN_0205FCE8

	thumb_func_start FUN_0205FD70
FUN_0205FD70: ; 0x0205FD70
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	bl FUN_02031190
	mov r1, #0x1
	sub r0, r1, r0
	bl FUN_020316E0
	add r7, r0, #0x0
	bne _0205FD96
	mov r0, #0x0
	pop {r3-r7, pc}
_0205FD96:
	ldrh r1, [r5, #0x2]
	add r0, r6, #0x0
	bl GetVarPointer
	add r4, r0, #0x0
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0205FDB0
	cmp r0, #0x1
	beq _0205FDBC
	cmp r0, #0x2
	beq _0205FDC8
	b _0205FDD2
_0205FDB0:
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl MOD06_02244660
	strh r0, [r4, #0x0]
	b _0205FDD2
_0205FDBC:
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl MOD06_022446BC
	strh r0, [r4, #0x0]
	b _0205FDD2
_0205FDC8:
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl MOD06_022446E0
	strh r0, [r4, #0x0]
_0205FDD2:
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start FUN_0205FDDC
FUN_0205FDDC: ; 0x0205FDDC
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	mov r0, #0xb
	mov r1, #0x4
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x4
	bl MI_CpuFill8
	strh r5, [r4, #0x0]
	strh r6, [r4, #0x2]
	ldr r0, [r7, #0x10]
	ldr r1, _0205FE0C ; =FUN_0205FD70
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r3-r7, pc}
	nop
_0205FE0C: .word FUN_0205FD70

	thumb_func_start FUN_0205FE10
FUN_0205FE10: ; 0x0205FE10
	push {r4-r7, lr}
	sub sp, #0x14
	str r0, [sp, #0x0]
	bl FUN_02029FC8
	mov r1, #0x35
	bl FUN_0202A150
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	cmp r0, #0x14
	bhs _0205FE30
	add sp, #0x14
	mov r0, #0x0
	pop {r4-r7, pc}
_0205FE30:
	ldr r0, [sp, #0x0]
	bl FUN_0202A8D8
	mov r1, #0xd
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_0202A578
	lsl r0, r0, #0x18
	mov r1, #0x0
	lsr r7, r0, #0x18
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl FUN_0202A578
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	add r0, r4, #0x0
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_0202A578
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	add r0, r4, #0x0
	mov r1, #0xe
	mov r2, #0x0
	bl FUN_0202A578
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x2
	mov r2, #0x0
	bl FUN_0202A578
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x3
	mov r2, #0x0
	bl FUN_0202A578
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4]
	cmp r7, #0x0
	beq _0205FEA2
	cmp r6, #0x0
	beq _0205FEA2
	cmp r5, #0x0
	beq _0205FEA2
	add sp, #0x14
	mov r0, #0x0
	pop {r4-r7, pc}
_0205FEA2:
	ldr r0, [sp, #0x0]
	bl FUN_02026CC4
	cmp r7, #0x0
	bne _0205FEDC
	mov r1, #0x55
	bl FUN_02025D94
	cmp r0, #0x0
	beq _0205FEC6
	add r0, r4, #0x0
	mov r1, #0xd
	mov r2, #0x1
	bl FUN_0202A578
	add sp, #0x14
	mov r0, #0x1
	pop {r4-r7, pc}
_0205FEC6:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _0205FED6
	add r0, r4, #0x0
	mov r1, #0xe
	mov r2, #0x1
	bl FUN_0202A578
_0205FED6:
	add sp, #0x14
	mov r0, #0x4
	pop {r4-r7, pc}
_0205FEDC:
	ldr r1, [sp, #0x10]
	cmp r1, #0x32
	bhs _0205FEE8
	add sp, #0x14
	mov r0, #0x0
	pop {r4-r7, pc}
_0205FEE8:
	cmp r6, #0x0
	bne _0205FF1C
	mov r1, #0x56
	bl FUN_02025D94
	cmp r0, #0x0
	beq _0205FF06
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x1
	bl FUN_0202A578
	add sp, #0x14
	mov r0, #0x2
	pop {r4-r7, pc}
_0205FF06:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bne _0205FF16
	add r0, r4, #0x0
	mov r1, #0x2
	mov r2, #0x1
	bl FUN_0202A578
_0205FF16:
	add sp, #0x14
	mov r0, #0x4
	pop {r4-r7, pc}
_0205FF1C:
	cmp r1, #0x64
	blo _0205FF24
	cmp r5, #0x0
	beq _0205FF2A
_0205FF24:
	add sp, #0x14
	mov r0, #0x0
	pop {r4-r7, pc}
_0205FF2A:
	mov r1, #0x57
	bl FUN_02025D94
	cmp r0, #0x0
	beq _0205FF44
	mov r1, #0x1
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl FUN_0202A578
	add sp, #0x14
	mov r0, #0x3
	pop {r4-r7, pc}
_0205FF44:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _0205FF54
	add r0, r4, #0x0
	mov r1, #0x3
	mov r2, #0x1
	bl FUN_0202A578
_0205FF54:
	mov r0, #0x4
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0205FF5C
FUN_0205FF5C: ; 0x0205FF5C
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl FUN_02029FC8
	mov r1, #0x35
	bl FUN_0202A150
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	cmp r7, #0x14
	bhs _0205FF7A
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0205FF7A:
	add r0, r4, #0x0
	bl FUN_0202A8D8
	mov r1, #0xd
	mov r2, #0x0
	str r0, [sp, #0x8]
	bl FUN_0202A578
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	mov r1, #0x0
	ldr r0, [sp, #0x8]
	add r2, r1, #0x0
	bl FUN_0202A578
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x8]
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_0202A578
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r0, [sp, #0x8]
	mov r1, #0xe
	mov r2, #0x0
	bl FUN_0202A578
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x8]
	mov r1, #0x2
	mov r2, #0x0
	bl FUN_0202A578
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	mov r1, #0x3
	mov r2, #0x0
	bl FUN_0202A578
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r6, #0x0
	beq _0205FFEA
	cmp r4, #0x0
	beq _0205FFEA
	cmp r5, #0x0
	beq _0205FFEA
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0205FFEA:
	cmp r6, #0x0
	bne _02060000
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0205FFFA
	add sp, #0xc
	mov r0, #0x4
	pop {r4-r7, pc}
_0205FFFA:
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_02060000:
	cmp r7, #0x32
	bhs _0206000A
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0206000A:
	cmp r4, #0x0
	bne _02060020
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _0206001A
	add sp, #0xc
	mov r0, #0x5
	pop {r4-r7, pc}
_0206001A:
	add sp, #0xc
	mov r0, #0x2
	pop {r4-r7, pc}
_02060020:
	cmp r7, #0x64
	bhs _0206002A
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0206002A:
	cmp r5, #0x0
	beq _02060034
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02060034:
	cmp r0, #0x0
	beq _0206003E
	add sp, #0xc
	mov r0, #0x6
	pop {r4-r7, pc}
_0206003E:
	mov r0, #0x3
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02060044
FUN_02060044: ; 0x02060044
	add r0, #0xa8
	ldr r0, [r0, #0x0]
	ldr r2, [r1, #0x0]
	ldrh r3, [r0, #0x24]
	add r2, r3, r2
	strh r2, [r0, #0x24]
	ldrh r3, [r0, #0x28]
	ldr r2, [r1, #0x4]
	add r2, r3, r2
	strh r2, [r0, #0x28]
	ldrh r2, [r0, #0x26]
	ldr r1, [r1, #0x8]
	add r1, r2, r1
	strh r1, [r0, #0x26]
	bx lr
	.balign 4

	thumb_func_start FUN_02060064
FUN_02060064: ; 0x02060064
	ldr r1, _0206006C ; =0x02E90EDD
	mul r1, r0
	add r0, r1, #0x1
	bx lr
	.balign 4
_0206006C: .word 0x02E90EDD

	thumb_func_start FUN_02060070
FUN_02060070: ; 0x02060070
	ldr r1, _02060078 ; =0x5D588B65
	mul r1, r0
	add r0, r1, #0x1
	bx lr
	.balign 4
_02060078: .word 0x5D588B65

	thumb_func_start FUN_0206007C
FUN_0206007C: ; 0x0206007C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0202881C
	bl FUN_020287A4
	bl FUN_02060070
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202A8D8
	add r1, r4, #0x0
	bl FUN_0202A5CC
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020600A0
FUN_020600A0: ; 0x020600A0
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl FUN_0202A8D8
	add r6, r0, #0x0
	bl FUN_0202A5D0
	bl FUN_02060070
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0202A5CC
	add r0, r4, #0x0
	bl FUN_02060064
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_0202A8CC
	mov r1, #0xa
	add r2, sp, #0x0
	bl FUN_0202A2C4
	ldr r0, [sp, #0x0]
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_020600DC
FUN_020600DC: ; 0x020600DC
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r0, #0x0
	bl FUN_0202A8D8
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0202A8CC
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202A5D0
	bl FUN_02060064
	mov r1, #0x0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_0202A240
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r4, #0x0
	lsr r1, r1, #0x10
	mov r2, #0x0
	bl FUN_0202A538
	mov r1, #0x18
	add r5, r0, #0x0
	mul r5, r1
	mov r4, #0x0
	cmp r5, #0x0
	ble _0206012E
	ldr r0, [sp, #0x0]
_02060122:
	bl FUN_02060064
	add r4, r4, #0x1
	str r0, [sp, #0x0]
	cmp r4, r5
	blt _02060122
_0206012E:
	add r0, r6, #0x0
	bl FUN_0202A8CC
	mov r1, #0xa
	add r2, sp, #0x0
	bl FUN_0202A2C4
	ldr r0, [sp, #0x0]
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02060144
FUN_02060144: ; 0x02060144
	ldr r0, [r0, #0x1c]
	ldr r1, [r0, #0x0]
	ldr r0, _02060158 ; =0x000001ED
	cmp r1, r0
	bne _02060152
	mov r0, #0x1
	bx lr
_02060152:
	mov r0, #0x0
	bx lr
	nop
_02060158: .word 0x000001ED
