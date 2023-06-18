	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021F4CF8
MOD05_021F4CF8: ; 0x021F4CF8
	push {r4, lr}
	mov r0, #4
	mov r1, #0xfc
	bl AllocFromHeap
	mov r4, #0
	add r2, r4, #0
_021F4D06:
	lsl r1, r4, #3
	add r3, r0, r1
	strb r2, [r0, r1]
	add r1, r4, #1
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
	str r2, [r3, #4]
	cmp r4, #0x15
	blo _021F4D06
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4D1C
MOD05_021F4D1C: ; 0x021F4D1C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}

	thumb_func_start MOD05_021F4D2C
MOD05_021F4D2C: ; 0x021F4D2C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, _021F4D7C ; =0x000007D8
	str r0, [r1]
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	add r4, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	cmp r0, #0
	bne _021F4D76
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, sp, #0xc
	mov r2, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, r6, #0
	sub r3, r2, #1
	bl FUN_0204A840
	add r0, r5, #0
	mov r1, #0x1a
	add r2, sp, #0xc
	mov r3, #0
	bl FUN_0204A8C4
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
_021F4D76:
	mov r0, #0
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0
_021F4D7C: .word 0x000007D8

	thumb_func_start MOD05_021F4D80
MOD05_021F4D80: ; 0x021F4D80
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl MOD05_021F50FC
	add r5, r0, #0
	cmp r5, #0x15
	bne _021F4D96
	bl GF_AssertFail
_021F4D96:
	ldr r0, [r4, #0xc]
	bl Save_Roamers_Get
	bl FUN_0202A9BC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0202A9C8
	add r4, r0, #0
	ldr r0, [r4]
	bl MOD05_021F5120
	cmp r0, #0
	beq _021F4DB8
	mov r0, #3
	pop {r3, r4, r5, pc}
_021F4DB8:
	ldr r0, [r4]
	cmp r0, #0
	beq _021F4DC2
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F4DC2:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4DC8
MOD05_021F4DC8: ; 0x021F4DC8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x1c]
	ldr r0, [r0]
	bl MOD05_021F50FC
	add r5, r0, #0
	cmp r5, #0x15
	bne _021F4DDE
	bl GF_AssertFail
_021F4DDE:
	ldr r0, [r6, #0xc]
	bl Save_Roamers_Get
	bl FUN_0202A9BC
	str r0, [sp]
	ldr r1, [sp]
	add r0, r5, #0
	bl FUN_0202A9C8
	add r4, r0, #0
	mov r0, #0x5a
	lsl r0, r0, #4
	str r0, [r4]
	ldr r0, [r6, #0xc]
	bl Save_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerID
	add r1, r5, #0
	bl MOD05_021F5138
	add r7, r0, #0
	ldr r0, [sp]
	bl FUN_0202A9C0
	cmp r5, r0
	bne _021F4E42
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #0x64
	blo _021F4E2E
	bl GF_AssertFail
_021F4E2E:
	cmp r6, #0x5a
	bhs _021F4E42
	add r0, r4, #4
	bl MOD05_021F4F44
	ldrb r0, [r4, #6]
	bl MOD05_021F4FAC
	strb r0, [r4, #7]
	pop {r3, r4, r5, r6, r7, pc}
_021F4E42:
	add r0, r7, #0
	add r1, r4, #6
	bl MOD05_021F4EE4
	ldrb r0, [r4, #6]
	cmp r0, #0
	beq _021F4E60
	add r0, r4, #4
	bl MOD05_021F4F44
	ldrb r0, [r4, #6]
	bl MOD05_021F4F98
	strb r0, [r4, #5]
	b _021F4E68
_021F4E60:
	mov r0, #0
	strb r0, [r4, #5]
	strb r0, [r4, #4]
	str r0, [r4]
_021F4E68:
	ldrb r0, [r4, #6]
	bl MOD05_021F4FAC
	strb r0, [r4, #7]
	ldr r1, [sp]
	add r0, r5, #0
	bl FUN_0202A9C4
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4E7C
MOD05_021F4E7C: ; 0x021F4E7C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl MOD05_021F50FC
	add r4, r0, #0
	cmp r4, #0x15
	bne _021F4E94
	bl GF_AssertFail
_021F4E94:
	add r0, r5, #0
	add r0, #0xa4
	ldr r0, [r0]
	lsl r4, r4, #3
	add r0, r0, r4
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021F4EE0
	ldr r0, [r5, #0x24]
	bl MOD05_021EF618
	ldr r1, [r5, #0x24]
	add r2, sp, #0
	bl MOD05_021EF604
	ldr r0, [sp]
	mov r1, #0x1a
	bl MOD05_021E7ED8
	add r6, r0, #0
	bl MOD05_021E7EC8
	add r1, r0, #0
	cmp r6, #0
	beq _021F4ED6
	add r3, r5, #0
	add r3, #0xa4
	ldr r3, [r3]
	ldr r0, [r5, #0x4c]
	ldrb r3, [r3, r4]
	mov r2, #0x1a
	bl MOD05_021D9FB4
_021F4ED6:
	add r5, #0xa4
	ldr r0, [r5]
	mov r1, #0
	add r0, r0, r4
	str r1, [r0, #4]
_021F4EE0:
	add sp, #4
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD05_021F4EE4
MOD05_021F4EE4: ; 0x021F4EE4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x64
	blo _021F4F02
	bl GF_AssertFail
_021F4F02:
	cmp r6, #0
	beq _021F4F2A
	cmp r4, #1
	bge _021F4F10
	mov r0, #3
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F10:
	cmp r4, #0xa
	bge _021F4F1A
	mov r0, #0
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F1A:
	cmp r4, #0x1e
	bge _021F4F24
	mov r0, #1
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F24:
	mov r0, #2
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F2A:
	cmp r4, #0xa
	bge _021F4F34
	mov r0, #0
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F34:
	cmp r4, #0x1e
	bge _021F4F3E
	mov r0, #2
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F3E:
	mov r0, #1
	strb r0, [r5]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F4F44
MOD05_021F4F44: ; 0x021F4F44
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x64
	blo _021F4F60
	bl GF_AssertFail
_021F4F60:
	cmp r5, #5
	bge _021F4F6A
	mov r0, #5
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_021F4F6A:
	cmp r5, #0xa
	bge _021F4F74
	mov r0, #4
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_021F4F74:
	cmp r5, #0x14
	bge _021F4F7E
	mov r0, #3
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_021F4F7E:
	cmp r5, #0x28
	bge _021F4F88
	mov r0, #2
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_021F4F88:
	cmp r5, #0x3c
	bge _021F4F92
	mov r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_021F4F92:
	mov r0, #0
	strb r0, [r4]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F4F98
MOD05_021F4F98: ; 0x021F4F98
	cmp r0, #3
	bne _021F4FA0
	mov r0, #2
	bx lr
_021F4FA0:
	cmp r0, #2
	bne _021F4FA8
	mov r0, #1
	bx lr
_021F4FA8:
	mov r0, #0
	bx lr

	thumb_func_start MOD05_021F4FAC
MOD05_021F4FAC: ; 0x021F4FAC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x64
	blo _021F4FC8
	bl GF_AssertFail
_021F4FC8:
	cmp r4, #3
	bne _021F4FE8
	cmp r5, #5
	bge _021F4FD4
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F4FD4:
	cmp r5, #6
	bge _021F4FDC
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F4FDC:
	cmp r5, #7
	bge _021F4FE4
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F4FE4:
	mov r0, #3
	pop {r3, r4, r5, pc}
_021F4FE8:
	cmp r4, #2
	bne _021F5008
	cmp r5, #0x4b
	bge _021F4FF4
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F4FF4:
	cmp r5, #0x5f
	bge _021F4FFC
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F4FFC:
	cmp r5, #0x60
	bge _021F5004
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F5004:
	mov r0, #3
	pop {r3, r4, r5, pc}
_021F5008:
	cmp r4, #1
	bne _021F5028
	cmp r5, #0x13
	bge _021F5014
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F5014:
	cmp r5, #0x4f
	bge _021F501C
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F501C:
	cmp r5, #0x63
	bge _021F5024
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F5024:
	mov r0, #3
	pop {r3, r4, r5, pc}
_021F5028:
	cmp r5, #1
	bge _021F5030
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F5030:
	cmp r5, #0x13
	bge _021F5038
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F5038:
	cmp r5, #0x63
	bge _021F5040
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F5040:
	mov r0, #3
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F5044
MOD05_021F5044: ; 0x021F5044
	mov r2, #1
	cmp r0, #3
	bne _021F5050
	mov r0, #2
	strb r0, [r1]
	b _021F5064
_021F5050:
	cmp r0, #2
	bne _021F5058
	strb r2, [r1]
	b _021F5064
_021F5058:
	cmp r0, #1
	bne _021F5062
	mov r0, #0
	strb r0, [r1]
	b _021F5064
_021F5062:
	mov r2, #0
_021F5064:
	add r0, r2, #0
	bx lr

	thumb_func_start MOD05_021F5068
MOD05_021F5068: ; 0x021F5068
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0x28]
	add r7, r1, #0
	add r1, r2, #0
	bl MapMatrix_GetMapHeaderFromID
	bl MOD05_021F50FC
	add r4, r0, #0
	cmp r4, #0x15
	beq _021F50F8
	ldr r0, [r5, #0xc]
	bl Save_Roamers_Get
	bl FUN_0202A9BC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0202A9C8
	add r6, r0, #0
	ldr r0, [r6]
	bl MOD05_021F5120
	cmp r0, #0
	beq _021F50F8
	ldrb r0, [r6, #7]
	add r1, sp, #4
	bl MOD05_021F5044
	add r6, r0, #0
	beq _021F50F8
	add r0, r7, #0
	mov r1, #0x1a
	bl MOD05_021E7ED8
	cmp r0, #0
	beq _021F50F8
	bl MOD05_021E7EC8
	add r3, r5, #0
	add r7, r0, #0
	add r3, #0xa4
	ldr r3, [r3]
	lsl r4, r4, #3
	ldrb r3, [r3, r4]
	ldr r0, [r5, #0x4c]
	add r1, r7, #0
	mov r2, #0x1a
	bl MOD05_021D9FB4
	add r1, sp, #4
	add r2, r5, #0
	add r2, #0xa4
	ldrb r0, [r1]
	ldr r2, [r2]
	add r3, r7, #0
	strb r0, [r2, r4]
	add r0, r5, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r2, #1
	add r0, r0, r4
	str r6, [r0, #4]
	ldr r0, [r5, #0x4c]
	str r0, [sp]
	ldrb r1, [r1]
	mov r0, #0x1a
	bl MOD05_021D9DC0
_021F50F8:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F50FC
MOD05_021F50FC: ; 0x021F50FC
	ldr r2, _021F511C ; =UNK05_021FC650
	mov r3, #0
_021F5100:
	lsl r1, r3, #2
	ldr r1, [r2, r1]
	cmp r0, r1
	bne _021F510C
	add r0, r3, #0
	bx lr
_021F510C:
	add r1, r3, #1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0x15
	blo _021F5100
	add r0, r3, #0
	bx lr
	nop
_021F511C: .word UNK05_021FC650

	thumb_func_start MOD05_021F5120
MOD05_021F5120: ; 0x021F5120
	cmp r0, #0
	ble _021F512E
	ldr r1, _021F5134 ; =0x00000438
	cmp r0, r1
	bgt _021F512E
	mov r0, #1
	bx lr
_021F512E:
	mov r0, #0
	bx lr
	nop
_021F5134: .word 0x00000438

	thumb_func_start MOD05_021F5138
MOD05_021F5138: ; 0x021F5138
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	lsr r2, r0, #0x18
	add r1, sp, #0
	strb r2, [r1]
	lsr r2, r0, #0x10
	strb r2, [r1, #1]
	lsr r2, r0, #8
	strb r2, [r1, #2]
	strb r0, [r1, #3]
	ldrb r0, [r1]
	mov r1, #0x15
	bl _s32_div_f
	add r0, sp, #0
	strb r1, [r0]
	ldrb r0, [r0, #1]
	mov r1, #0x15
	bl _s32_div_f
	add r0, sp, #0
	strb r1, [r0, #1]
	ldrb r0, [r0, #2]
	mov r1, #0x15
	bl _s32_div_f
	add r0, sp, #0
	strb r1, [r0, #2]
	ldrb r0, [r0, #3]
	mov r1, #0x15
	bl _s32_div_f
	add r0, sp, #0
	strb r1, [r0, #3]
	mov r0, #0
	mov r3, #1
	add r1, sp, #0
	add r2, r0, #0
_021F5184:
	add r5, r2, #0
	cmp r3, #0
	bls _021F51A8
_021F518A:
	ldrb r7, [r1, r5]
	ldrb r6, [r1, r3]
	cmp r7, r6
	bne _021F519E
	add r6, r6, #1
	strb r6, [r1, r3]
	ldrb r6, [r1, r3]
	cmp r6, #0x15
	blo _021F519E
	strb r0, [r1, r3]
_021F519E:
	add r5, r5, #1
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	cmp r5, r3
	blo _021F518A
_021F51A8:
	add r3, r3, #1
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	cmp r3, #4
	blo _021F5184
	mov r2, #0
	add r1, sp, #0
_021F51B6:
	ldrb r0, [r1, r2]
	cmp r4, r0
	bne _021F51C0
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F51C0:
	add r0, r2, #1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, #4
	blo _021F51B6
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F51D0
MOD05_021F51D0: ; 0x021F51D0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl MOD05_021F50FC
	add r5, r0, #0
	cmp r5, #0x15
	bne _021F51E6
	bl GF_AssertFail
_021F51E6:
	ldr r0, [r4, #0xc]
	bl Save_Roamers_Get
	bl FUN_0202A9BC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0202A9C8
	add r4, r0, #0
	ldrb r1, [r4, #5]
	mov r0, #0x6a
	lsl r2, r1, #2
	ldr r1, _021F5218 ; =UNK05_021FC644
	ldr r1, [r1, r2]
	mov r2, #4
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	ldrb r1, [r4, #4]
	lsl r1, r1, #2
	ldr r4, [r0, r1]
	bl FreeToHeap
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021F5218: .word UNK05_021FC644

	thumb_func_start MOD05_021F521C
MOD05_021F521C: ; 0x021F521C
	push {r3, lr}
	add r3, r1, #0
	bmi _021F522A
	add r1, r2, #0
	add r2, r3, #0
	bl MOD05_021F5068
_021F522A:
	pop {r3, pc}

	thumb_func_start MOD05_021F522C
MOD05_021F522C: ; 0x021F522C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl MOD05_021F50FC
	add r4, r0, #0
	cmp r4, #0x15
	bne _021F5242
	bl GF_AssertFail
_021F5242:
	add r0, r5, #0
	add r0, #0xa4
	ldr r1, [r0]
	lsl r0, r4, #3
	mov r2, #0
	add r0, r1, r0
	str r2, [r0, #4]
	ldr r0, [r5, #0xc]
	bl Save_Roamers_Get
	bl FUN_0202A9BC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0202A9C8
	mov r1, #0
	str r1, [r0]
	pop {r3, r4, r5, pc}

	.section .rodata

	.global UNK05_021FC644
UNK05_021FC644: ; 0x021FC644
.ifdef DIAMOND
	.word 2, 3, 4
.else
	.word 5, 6, 7
.endif

	.global UNK05_021FC650
UNK05_021FC650: ; 0x021FC650
	.byte 0x5B, 0x01, 0x00, 0x00, 0x5D, 0x01, 0x00, 0x00, 0x5E, 0x01, 0x00, 0x00
	.byte 0x61, 0x01, 0x00, 0x00, 0x62, 0x01, 0x00, 0x00, 0x64, 0x01, 0x00, 0x00, 0x6A, 0x01, 0x00, 0x00
	.byte 0x6B, 0x01, 0x00, 0x00, 0x6E, 0x01, 0x00, 0x00, 0x6F, 0x01, 0x00, 0x00, 0x73, 0x01, 0x00, 0x00
	.byte 0x75, 0x01, 0x00, 0x00, 0x7C, 0x01, 0x00, 0x00, 0x7E, 0x01, 0x00, 0x00, 0x84, 0x01, 0x00, 0x00
	.byte 0x88, 0x01, 0x00, 0x00, 0x8B, 0x01, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0xCA, 0x00, 0x00, 0x00
	.byte 0xCC, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
