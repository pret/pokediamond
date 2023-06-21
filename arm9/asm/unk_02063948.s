	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F7CE4
UNK_020F7CE4: ; 0x020F7CE4
	.word sub_02063AD0, sub_02063A9C
	.word sub_02063BBC, sub_02063B40
	.word sub_02063C70, sub_02063C14
	.word sub_02063D18, sub_02063CE0
	.word sub_02063DC0, sub_02063D88
	.word sub_02063E68, sub_02063E30
	.word sub_02063F10, sub_02063ED8
	.word sub_02063FCC, sub_02063F80
	.word sub_0206405C, sub_0206403C
	.word sub_02064134, sub_020640CC
	.word sub_020641F0, sub_020641AC
	.word sub_020642B4, sub_02064284
	.word sub_02064324, sub_02064310

	.text

	thumb_func_start sub_02063948
sub_02063948: ; 0x02063948
	cmp r0, #0x0
	bne _02063954
	ldr r0, _0206395C ; =UNK_020F7CE4
	lsl r1, r1, #0x3
	ldr r0, [r0, r1]
	bx lr
_02063954:
	ldr r0, _02063960 ; =UNK_020F7CE4 + 4
	lsl r1, r1, #0x3
	ldr r0, [r0, r1]
	bx lr
	.balign 4
_0206395C: .word UNK_020F7CE4
_02063960: .word UNK_020F7CE4 + 4

	thumb_func_start sub_02063964
sub_02063964: ; 0x02063964
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r5, [r4, #0x4]
	ldr r1, [r5, #0x1c]
	ldr r1, [r1, #0x0]
	str r1, [r4, #0x0]
	mov r1, #0x0
	strh r1, [r4, #0xc]
	add r1, sp, #0x8
	bl sub_02037024
	ldr r0, [sp, #0x8]
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _020639B6
	bl sub_02058458
	cmp r0, #0x54
	beq _0206399A
	cmp r0, #0x55
	beq _020639A4
	cmp r0, #0x56
	beq _020639AE
	b _020639B6
_0206399A:
	ldrh r1, [r4, #0xc]
	mov r0, #0x8
	orr r0, r1
	strh r0, [r4, #0xc]
	b _020639B6
_020639A4:
	ldrh r1, [r4, #0xc]
	mov r0, #0x20
	orr r0, r1
	strh r0, [r4, #0xc]
	b _020639B6
_020639AE:
	ldrh r1, [r4, #0xc]
	mov r0, #0x1
	orr r0, r1
	strh r0, [r4, #0xc]
_020639B6:
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r2, r0, #0x0
	ldr r1, [sp, #0x4]
	str r2, [sp, #0x0]
	add r0, r5, #0x0
	bl sub_0204A6E0
	add r7, r0, #0x0
	ldr r0, [r5, #0x38]
	add r1, sp, #0x4
	add r2, sp, #0x0
	bl sub_020572B8
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	bl sub_0204A6E0
	add r6, r0, #0x0
	ldr r0, [r5, #0x38]
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl MOD05_021E643C
	cmp r0, #0x0
	beq _020639FE
	ldrh r1, [r4, #0xc]
	mov r0, #0x4
	orr r0, r1
	strh r0, [r4, #0xc]
_020639FE:
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl MOD05_021E69BC
	cmp r0, #0x0
	beq _02063A18
	ldrh r1, [r4, #0xc]
	mov r0, #0x80
	orr r0, r1
	strh r0, [r4, #0xc]
_02063A18:
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	bl sub_02054A48
	cmp r0, #0x0
	beq _02063A2C
	ldrh r1, [r4, #0xc]
	mov r0, #0x40
	orr r0, r1
	strh r0, [r4, #0xc]
_02063A2C:
	ldr r0, [r5, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetWeatherType
	cmp r0, #0xe
	beq _02063A42
	cmp r0, #0x10
	beq _02063A4E
	add sp, #0xc
	pop {r4-r7, pc}
_02063A42:
	ldrh r1, [r4, #0xc]
	mov r0, #0x10
	add sp, #0xc
	orr r0, r1
	strh r0, [r4, #0xc]
	pop {r4-r7, pc}
_02063A4E:
	ldrh r1, [r4, #0xc]
	mov r0, #0x1
	lsl r0, r0, #0x8
	orr r0, r1
	strh r0, [r4, #0xc]
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start sub_02063A5C
sub_02063A5C: ; 0x02063A5C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x20
	mov r1, #0x10
	bl AllocFromHeap
	ldr r1, _02063A7C ; =0x19740205
	str r1, [r0, #0x0]
	ldr r1, [r4, #0x8]
	str r1, [r0, #0x4]
	ldr r2, [r5, #0x0]
	ldr r1, [r5, #0x4]
	str r2, [r0, #0x8]
	str r1, [r0, #0xc]
	pop {r3-r5, pc}
	.balign 4
_02063A7C: .word 0x19740205

	thumb_func_start sub_02063A80
sub_02063A80: ; 0x02063A80
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02063A98 ; =0x19740205
	cmp r1, r0
	beq _02063A90
	bl GF_AssertFail
_02063A90:
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4
_02063A98: .word 0x19740205

	thumb_func_start sub_02063A9C
sub_02063A9C: ; 0x02063A9C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	ldr r0, [r1, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _02063AAE
	mov r0, #0x1
	pop {r4, pc}
_02063AAE:
	ldr r0, [r1, #0xc]
	bl Save_PlayerData_GetProfileAddr
	mov r1, #0x1
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0x0
	bne _02063AC2
	mov r0, #0x2
	pop {r4, pc}
_02063AC2:
	ldrh r1, [r4, #0xc]
	mov r0, #0x1
	tst r1, r0
	beq _02063ACC
	mov r0, #0x0
_02063ACC:
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02063AD0
sub_02063AD0: ; 0x02063AD0
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02063A5C
	add r5, r0, #0x0
	ldr r0, [r6, #0x4]
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _02063B00 ; =sub_02063B04
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r5, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r4-r6, pc}
	.balign 4
_02063B00: .word sub_02063B04

	thumb_func_start sub_02063B04
sub_02063B04: ; 0x02063B04
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	ldr r1, _02063B3C ; =0x00002718
	ldr r2, [r4, #0x4]
	add r0, r5, #0x0
	bl sub_02038D10
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldrh r1, [r4, #0xc]
	add r0, r6, #0x0
	add r3, r2, #0x0
	bl sub_020395BC
	add r0, r4, #0x0
	bl sub_02063A80
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02063B3C: .word 0x00002718

	thumb_func_start sub_02063B40
sub_02063B40: ; 0x02063B40
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	ldr r0, [r1, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _02063B52
	mov r0, #0x1
	pop {r4, pc}
_02063B52:
	ldr r0, [r1, #0xc]
	bl Save_PlayerData_GetProfileAddr
	mov r1, #0x2
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0x0
	bne _02063B66
	mov r0, #0x2
	pop {r4, pc}
_02063B66:
	ldr r0, [r4, #0x0]
	bl MapHeader_IsFlyAllowed
	cmp r0, #0x0
	bne _02063B74
	mov r0, #0x1
	pop {r4, pc}
_02063B74:
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205ED3C
	cmp r0, #0x1
	bne _02063B88
	mov r0, #0x3
	pop {r4, pc}
_02063B88:
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205F214
	cmp r0, #0x1
	beq _02063BA8
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205F244
	cmp r0, #0x1
	bne _02063BAC
_02063BA8:
	mov r0, #0x1
	b _02063BAE
_02063BAC:
	mov r0, #0x0
_02063BAE:
	cmp r0, #0x1
	bne _02063BB6
	mov r0, #0x1
	pop {r4, pc}
_02063BB6:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02063BBC
sub_02063BBC: ; 0x02063BBC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_02046528
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x4
	bl AllocFromHeap
	ldrh r1, [r5, #0x4]
	str r1, [r0, #0x0]
	mov r1, #0x7f
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0xb
	sub r1, #0xbc
	bl AllocFromHeap
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	add r0, r6, #0x0
	mov r2, #0x1
	bl sub_0205F7A0
	mov r1, #0x7e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	add r0, r6, #0x0
	bl sub_02037E90
	ldr r1, _02063C10 ; =sub_02036AB8
	add r0, r4, #0x0
	bl sub_02035D04
	pop {r4-r6, pc}
	.balign 4
_02063C10: .word sub_02036AB8

	thumb_func_start sub_02063C14
sub_02063C14: ; 0x02063C14
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	ldr r0, [r1, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _02063C26
	mov r0, #0x1
	pop {r4, pc}
_02063C26:
	ldr r0, [r1, #0xc]
	bl Save_PlayerData_GetProfileAddr
	mov r1, #0x4
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0x0
	bne _02063C3A
	mov r0, #0x2
	pop {r4, pc}
_02063C3A:
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x38]
	bl PlayerAvatar_GetState
	cmp r0, #0x2
	bne _02063C4A
	mov r0, #0x4
	pop {r4, pc}
_02063C4A:
	ldrh r1, [r4, #0xc]
	mov r0, #0x4
	tst r0, r1
	bne _02063C56
	mov r0, #0x1
	pop {r4, pc}
_02063C56:
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205ED3C
	cmp r0, #0x1
	bne _02063C6A
	mov r0, #0x3
	pop {r4, pc}
_02063C6A:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02063C70
sub_02063C70: ; 0x02063C70
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02063A5C
	add r5, r0, #0x0
	ldr r0, [r6, #0x4]
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _02063CA0 ; =sub_02063CA4
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r5, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r4-r6, pc}
	.balign 4
_02063CA0: .word sub_02063CA4

	thumb_func_start sub_02063CA4
sub_02063CA4: ; 0x02063CA4
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	ldr r1, _02063CDC ; =0x0000271C
	add r0, r5, #0x0
	mov r2, #0x0
	bl sub_02038D10
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldrh r1, [r4, #0xc]
	add r0, r6, #0x0
	add r3, r2, #0x0
	bl sub_020395BC
	add r0, r4, #0x0
	bl sub_02063A80
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02063CDC: .word 0x0000271C

	thumb_func_start sub_02063CE0
sub_02063CE0: ; 0x02063CE0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	ldr r0, [r1, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _02063CF2
	mov r0, #0x1
	pop {r4, pc}
_02063CF2:
	ldr r0, [r1, #0xc]
	bl Save_PlayerData_GetProfileAddr
	mov r1, #0x5
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0x0
	bne _02063D06
	mov r0, #0x2
	pop {r4, pc}
_02063D06:
	ldrh r1, [r4, #0xc]
	mov r0, #0x8
	tst r0, r1
	beq _02063D12
	mov r0, #0x0
	pop {r4, pc}
_02063D12:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02063D18
sub_02063D18: ; 0x02063D18
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02063A5C
	add r5, r0, #0x0
	ldr r0, [r6, #0x4]
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _02063D48 ; =sub_02063D4C
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r5, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r4-r6, pc}
	.balign 4
_02063D48: .word sub_02063D4C

	thumb_func_start sub_02063D4C
sub_02063D4C: ; 0x02063D4C
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	ldr r1, _02063D84 ; =0x0000271A
	ldr r2, [r4, #0x4]
	add r0, r5, #0x0
	bl sub_02038D10
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldrh r1, [r4, #0xc]
	add r0, r6, #0x0
	add r3, r2, #0x0
	bl sub_020395BC
	add r0, r4, #0x0
	bl sub_02063A80
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02063D84: .word 0x0000271A

	thumb_func_start sub_02063D88
sub_02063D88: ; 0x02063D88
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	ldr r0, [r1, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _02063D9A
	mov r0, #0x1
	pop {r4, pc}
_02063D9A:
	ldr r0, [r1, #0xc]
	bl Save_PlayerData_GetProfileAddr
	mov r1, #0x3
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0x0
	bne _02063DAE
	mov r0, #0x2
	pop {r4, pc}
_02063DAE:
	ldrh r1, [r4, #0xc]
	mov r0, #0x10
	tst r0, r1
	beq _02063DBA
	mov r0, #0x0
	pop {r4, pc}
_02063DBA:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02063DC0
sub_02063DC0: ; 0x02063DC0
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02063A5C
	add r5, r0, #0x0
	ldr r0, [r6, #0x4]
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _02063DF0 ; =sub_02063DF4
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r5, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r4-r6, pc}
	.balign 4
_02063DF0: .word sub_02063DF4

	thumb_func_start sub_02063DF4
sub_02063DF4: ; 0x02063DF4
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	ldr r1, _02063E2C ; =0x0000271E
	add r0, r5, #0x0
	mov r2, #0x0
	bl sub_02038D10
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldrh r1, [r4, #0xc]
	add r0, r6, #0x0
	add r3, r2, #0x0
	bl sub_020395BC
	add r0, r4, #0x0
	bl sub_02063A80
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02063E2C: .word 0x0000271E

	thumb_func_start sub_02063E30
sub_02063E30: ; 0x02063E30
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	ldr r0, [r1, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _02063E42
	mov r0, #0x1
	pop {r4, pc}
_02063E42:
	ldr r0, [r1, #0xc]
	bl Save_PlayerData_GetProfileAddr
	mov r1, #0x0
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0x0
	bne _02063E56
	mov r0, #0x2
	pop {r4, pc}
_02063E56:
	ldrh r1, [r4, #0xc]
	mov r0, #0x20
	tst r0, r1
	beq _02063E62
	mov r0, #0x0
	pop {r4, pc}
_02063E62:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02063E68
sub_02063E68: ; 0x02063E68
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02063A5C
	add r5, r0, #0x0
	ldr r0, [r6, #0x4]
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _02063E98 ; =sub_02063E9C
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r5, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r4-r6, pc}
	.balign 4
_02063E98: .word sub_02063E9C

	thumb_func_start sub_02063E9C
sub_02063E9C: ; 0x02063E9C
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	ldr r1, _02063ED4 ; =0x00002719
	ldr r2, [r4, #0x4]
	add r0, r5, #0x0
	bl sub_02038D10
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldrh r1, [r4, #0xc]
	add r0, r6, #0x0
	add r3, r2, #0x0
	bl sub_020395BC
	add r0, r4, #0x0
	bl sub_02063A80
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02063ED4: .word 0x00002719

	thumb_func_start sub_02063ED8
sub_02063ED8: ; 0x02063ED8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	ldr r0, [r1, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _02063EEA
	mov r0, #0x1
	pop {r4, pc}
_02063EEA:
	ldr r0, [r1, #0xc]
	bl Save_PlayerData_GetProfileAddr
	mov r1, #0x7
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0x0
	bne _02063EFE
	mov r0, #0x2
	pop {r4, pc}
_02063EFE:
	ldrh r1, [r4, #0xc]
	mov r0, #0x40
	tst r0, r1
	beq _02063F0A
	mov r0, #0x0
	pop {r4, pc}
_02063F0A:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02063F10
sub_02063F10: ; 0x02063F10
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02063A5C
	add r5, r0, #0x0
	ldr r0, [r6, #0x4]
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _02063F40 ; =sub_02063F44
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r5, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r4-r6, pc}
	.balign 4
_02063F40: .word sub_02063F44

	thumb_func_start sub_02063F44
sub_02063F44: ; 0x02063F44
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	ldr r1, _02063F7C ; =0x0000271D
	add r0, r5, #0x0
	mov r2, #0x0
	bl sub_02038D10
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldrh r1, [r4, #0xc]
	add r0, r6, #0x0
	add r3, r2, #0x0
	bl sub_020395BC
	add r0, r4, #0x0
	bl sub_02063A80
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02063F7C: .word 0x0000271D

	thumb_func_start sub_02063F80
sub_02063F80: ; 0x02063F80
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	ldr r0, [r1, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _02063F92
	mov r0, #0x1
	pop {r4, pc}
_02063F92:
	ldr r0, [r1, #0xc]
	bl Save_PlayerData_GetProfileAddr
	mov r1, #0x6
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0x0
	bne _02063FA6
	mov r0, #0x2
	pop {r4, pc}
_02063FA6:
	ldrh r1, [r4, #0xc]
	mov r0, #0x80
	tst r0, r1
	bne _02063FB2
	mov r0, #0x1
	pop {r4, pc}
_02063FB2:
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205ED3C
	cmp r0, #0x1
	bne _02063FC6
	mov r0, #0x3
	pop {r4, pc}
_02063FC6:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02063FCC
sub_02063FCC: ; 0x02063FCC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02063A5C
	add r5, r0, #0x0
	ldr r0, [r6, #0x4]
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _02063FFC ; =sub_02064000
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r5, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r4-r6, pc}
	.balign 4
_02063FFC: .word sub_02064000

	thumb_func_start sub_02064000
sub_02064000: ; 0x02064000
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	ldr r1, _02064038 ; =0x0000271B
	add r0, r5, #0x0
	mov r2, #0x0
	bl sub_02038D10
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldrh r1, [r4, #0xc]
	add r0, r6, #0x0
	add r3, r2, #0x0
	bl sub_020395BC
	add r0, r4, #0x0
	bl sub_02063A80
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02064038: .word 0x0000271B

	thumb_func_start sub_0206403C
sub_0206403C: ; 0x0206403C
	ldr r1, [r0, #0x4]
	ldr r1, [r1, #0x6c]
	sub r1, r1, #0x2
	cmp r1, #0x1
	bhi _0206404A
	mov r0, #0x1
	bx lr
_0206404A:
	ldrh r1, [r0, #0xc]
	mov r0, #0x1
	lsl r0, r0, #0x8
	tst r0, r1
	beq _02064058
	mov r0, #0x0
	bx lr
_02064058:
	mov r0, #0x1
	bx lr

	thumb_func_start sub_0206405C
sub_0206405C: ; 0x0206405C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02063A5C
	add r5, r0, #0x0
	ldr r0, [r6, #0x4]
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _0206408C ; =sub_02064090
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r5, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r4-r6, pc}
	.balign 4
_0206408C: .word sub_02064090

	thumb_func_start sub_02064090
sub_02064090: ; 0x02064090
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	ldr r1, _020640C8 ; =0x0000271F
	add r0, r5, #0x0
	mov r2, #0x0
	bl sub_02038D10
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldrh r1, [r4, #0xc]
	add r0, r6, #0x0
	add r3, r2, #0x0
	bl sub_020395BC
	add r0, r4, #0x0
	bl sub_02063A80
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_020640C8: .word 0x0000271F

	thumb_func_start sub_020640CC
sub_020640CC: ; 0x020640CC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _020640DE
	mov r0, #0x1
	pop {r4, pc}
_020640DE:
	ldr r0, [r4, #0x0]
	bl MapHeader_IsOutdoorNotTown
	cmp r0, #0x0
	bne _020640EC
	mov r0, #0x1
	pop {r4, pc}
_020640EC:
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205ED3C
	cmp r0, #0x1
	bne _02064100
	mov r0, #0x3
	pop {r4, pc}
_02064100:
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205F214
	cmp r0, #0x1
	beq _02064120
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205F244
	cmp r0, #0x1
	bne _02064124
_02064120:
	mov r0, #0x1
	b _02064126
_02064124:
	mov r0, #0x0
_02064126:
	cmp r0, #0x1
	bne _0206412E
	mov r0, #0x1
	pop {r4, pc}
_0206412E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02064134
sub_02064134: ; 0x02064134
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_02046528
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl sub_0204649C
	ldrh r1, [r5, #0x4]
	ldr r2, [r6, #0xc]
	mov r0, #0xb
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl sub_0206439C
	mov r1, #0x72
	ldr r2, _02064170 ; =sub_02064174
	lsl r1, r1, #0x2
	str r2, [r4, r1]
	add r1, #0x30
	str r0, [r4, r1]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r4-r6, pc}
	nop
_02064170: .word sub_02064174

	thumb_func_start sub_02064174
sub_02064174: ; 0x02064174
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	add r0, r6, #0x0
	mov r2, #0x4
	bl MOD06_0224CB30
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r1, _020641A8 ; =MOD06_0224CB54
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl sub_020463EC
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_020641A8: .word MOD06_0224CB54

	thumb_func_start sub_020641AC
sub_020641AC: ; 0x020641AC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _020641BE
	mov r0, #0x1
	pop {r4, pc}
_020641BE:
	ldr r0, [r4, #0x0]
	bl MapHeader_IsCave
	cmp r0, #0x1
	bne _020641D2
	ldr r0, [r4, #0x0]
	bl MapHeader_IsEscapeRopeAllowed
	cmp r0, #0x1
	beq _020641D6
_020641D2:
	mov r0, #0x1
	pop {r4, pc}
_020641D6:
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205ED3C
	cmp r0, #0x1
	bne _020641EA
	mov r0, #0x3
	pop {r4, pc}
_020641EA:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_020641F0
sub_020641F0: ; 0x020641F0
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_02046528
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl sub_0204649C
	ldrh r1, [r5, #0x4]
	ldr r2, [r6, #0xc]
	mov r0, #0xb
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl sub_0206439C
	mov r1, #0x72
	ldr r2, _0206422C ; =sub_02064230
	lsl r1, r1, #0x2
	str r2, [r4, r1]
	add r1, #0x30
	str r0, [r4, r1]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r4-r6, pc}
	nop
_0206422C: .word sub_02064230

	thumb_func_start sub_02064230
sub_02064230: ; 0x02064230
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl sub_02046528
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204652C
	add r6, r0, #0x0
	ldr r1, [r6, #0x0]
	add r0, r4, #0x0
	mov r2, #0xb
	bl MOD06_0224CA88
	ldr r1, [r4, #0x1c]
	add r7, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0xa
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	mov r2, #0x4
	bl sub_0202914C
	add r4, #0x98
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r2, #0x1
	bl sub_02028AD4
	add r0, r6, #0x0
	bl FreeToHeap
	ldr r1, _02064280 ; =MOD06_0224CAAC
	add r0, r5, #0x0
	add r2, r7, #0x0
	bl sub_020463EC
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02064280: .word MOD06_0224CAAC

	thumb_func_start sub_02064284
sub_02064284: ; 0x02064284
	push {r3, lr}
	ldr r1, [r0, #0x4]
	ldr r0, [r1, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _02064294
	mov r0, #0x1
	pop {r3, pc}
_02064294:
	ldr r0, [r1, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205F244
	cmp r0, #0x1
	bne _020642A6
	mov r0, #0x1
	b _020642A8
_020642A6:
	mov r0, #0x0
_020642A8:
	cmp r0, #0x1
	bne _020642B0
	mov r0, #0x1
	pop {r3, pc}
_020642B0:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_020642B4
sub_020642B4: ; 0x020642B4
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	bl sub_02046528
	add r5, r0, #0x0
	ldr r0, [r6, #0x0]
	bl sub_0204652C
	ldrh r1, [r6, #0x4]
	add r4, r0, #0x0
	ldr r2, [r5, #0xc]
	lsl r1, r1, #0x18
	mov r0, #0xb
	lsr r1, r1, #0x18
	bl sub_0206439C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _0206430C ; =MOD05_021F6360
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r6, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	ldr r1, [r5, #0x1c]
	mov r0, #0xb
	ldr r1, [r1, #0x0]
	add r2, r0, #0x0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl sub_0202914C
	add r5, #0x98
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r2, #0x1
	bl sub_02028AD4
	pop {r4-r6, pc}
	.balign 4
_0206430C: .word MOD05_021F6360

	thumb_func_start sub_02064310
sub_02064310: ; 0x02064310
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0x6c]
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _0206431E
	mov r0, #0x1
	bx lr
_0206431E:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_02064324
sub_02064324: ; 0x02064324
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	bl sub_02046528
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02063A5C
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _0206435C ; =sub_02064360
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r5, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r3-r7, pc}
	.balign 4
_0206435C: .word sub_02064360

	thumb_func_start sub_02064360
sub_02064360: ; 0x02064360
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	ldr r1, _02064398 ; =0x000022C4
	add r0, r5, #0x0
	mov r2, #0x0
	bl sub_02038D10
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldrh r1, [r4, #0xc]
	add r0, r6, #0x0
	add r3, r2, #0x0
	bl sub_020395BC
	add r0, r4, #0x0
	bl sub_02063A80
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02064398: .word 0x000022C4
