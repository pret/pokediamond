	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start Sav2_PlayerData_sizeof
Sav2_PlayerData_sizeof: ; 0x020238C4
	mov r0, #0x2c
	bx lr

	thumb_func_start Sav2_PlayerData_init
Sav2_PlayerData_init: ; 0x020238C8
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x2c
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	bl Options_init
	add r0, r4, #0x4
	bl PlayerData_Clear
	add r0, r4, #0x0
	add r0, #0x24
	bl InitCoins
	add r4, #0x26
	add r0, r4, #0x0
	bl FUN_02029E48
	pop {r4, pc}

	thumb_func_start Sav2_GetPlayerDataPtr
Sav2_GetPlayerDataPtr: ; 0x020238F4
	push {r3, lr}
	mov r1, #0x1
	bl SavArray_get
	add r0, r0, #0x4
	pop {r3, pc}

	thumb_func_start LoadPlayerDataAddress
LoadPlayerDataAddress: ; 0x02023900
	ldr r3, _02023908 ; =SavArray_get
	mov r1, #0x1
	bx r3
	nop
_02023908: .word SavArray_get

	thumb_func_start FUN_0202390C
FUN_0202390C: ; 0x0202390C
	push {r3, lr}
	mov r1, #0x1
	bl SavArray_get
	add r0, #0x24
	pop {r3, pc}

	thumb_func_start FUN_02023918
FUN_02023918: ; 0x02023918
	push {r3, lr}
	mov r1, #0x1
	bl SavArray_get
	add r0, #0x26
	pop {r3, pc}

	thumb_func_start PlayerData_sizeof
PlayerData_sizeof: ; 0x02023924
	mov r0, #0x20
	bx lr

	thumb_func_start PlayerData_init
PlayerData_init: ; 0x02023928
	push {r4, lr}
	mov r1, #0x20
	bl AllocFromHeap
	add r4, r0, #0x0
	bl PlayerData_Clear
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202393C
FUN_0202393C: ; 0x0202393C
	ldr r3, _02023944 ; =MI_CpuCopy8
	mov r2, #0x20
	bx r3
	nop
_02023944: .word MI_CpuCopy8

	thumb_func_start PlayerData_Clear
PlayerData_Clear: ; 0x02023948
	push {r4, lr}
	mov r1, #0x0
	mov r2, #0x20
	add r4, r0, #0x0
	bl memset
	mov r0, #0x2
	strb r0, [r4, #0x19]
	pop {r4, pc}
	.balign 4

	thumb_func_start CopyPlayerName
CopyPlayerName: ; 0x0202395C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl StringLength
	cmp r0, #0x8
	blt _02023970
	bl ErrorHandling
_02023970:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl CopyU16StringArray
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start PlayerName_StringToFlat
PlayerName_StringToFlat: ; 0x0202397C
	ldr r3, _02023988 ; =CopyStringToU16Array
	add r2, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	mov r2, #0x8
	bx r3
	.balign 4
_02023988: .word CopyStringToU16Array

	thumb_func_start FUN_0202398C
FUN_0202398C: ; 0x0202398C
	bx lr
	.balign 4

	thumb_func_start PlayerName_FlatToString
PlayerName_FlatToString: ; 0x02023990
	ldr r3, _0202399C ; =CopyU16ArrayToString
	add r2, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	bx r3
	nop
_0202399C: .word CopyU16ArrayToString

	thumb_func_start PlayerData_GetPlayerName_NewString
PlayerData_GetPlayerName_NewString: ; 0x020239A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x8
	bl String_ctor
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl PlayerName_FlatToString
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_020239B8
FUN_020239B8: ; 0x020239B8
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start PlayerData_GetTrainerID
PlayerData_GetTrainerID: ; 0x020239BC
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start PlayerData_GetTrainerID_VisibleHalf
PlayerData_GetTrainerID_VisibleHalf: ; 0x020239C0
	ldr r0, [r0, #0x10]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr

	thumb_func_start PlayerData_SetTrainerGender
PlayerData_SetTrainerGender: ; 0x020239C8
	strb r1, [r0, #0x18]
	bx lr

	thumb_func_start PlayerData_GetTrainerGender
PlayerData_GetTrainerGender: ; 0x020239CC
	ldrb r0, [r0, #0x18]
	bx lr

	thumb_func_start PlayerData_TestBadgeFlag
PlayerData_TestBadgeFlag: ; 0x020239D0
	ldrb r3, [r0, #0x1a]
	mov r0, #0x1
	add r2, r0, #0x0
	lsl r2, r1
	add r1, r3, #0x0
	tst r1, r2
	bne _020239E0
	mov r0, #0x0
_020239E0:
	bx lr
	.balign 4

	thumb_func_start PlayerData_SetBadgeFlag
PlayerData_SetBadgeFlag: ; 0x020239E4
	ldrb r3, [r0, #0x1a]
	mov r2, #0x1
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strb r1, [r0, #0x1a]
	bx lr
	.balign 4

	thumb_func_start PlayerData_CountBadges
PlayerData_CountBadges: ; 0x020239F4
	ldrb r3, [r0, #0x1a]
	mov r2, #0x0
	cmp r3, #0x0
	beq _02023A0A
	mov r0, #0x1
_020239FE:
	add r1, r3, #0x0
	tst r1, r0
	beq _02023A06
	add r2, r2, #0x1
_02023A06:
	lsr r3, r3, #0x1
	bne _020239FE
_02023A0A:
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start PlayerData_GetMoney
PlayerData_GetMoney: ; 0x02023A10
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start PlayerData_SetMoney
PlayerData_SetMoney: ; 0x02023A14
	ldr r2, _02023A24 ; =0x000F423F
	cmp r1, r2
	bls _02023A1C
	add r1, r2, #0x0
_02023A1C:
	str r1, [r0, #0x14]
	add r0, r1, #0x0
	bx lr
	nop
_02023A24: .word 0x000F423F

	thumb_func_start FUN_02023A28
FUN_02023A28: ; 0x02023A28
	ldrb r0, [r0, #0x1b]
	bx lr

	thumb_func_start FUN_02023A2C
FUN_02023A2C: ; 0x02023A2C
	strb r1, [r0, #0x1b]
	bx lr

	thumb_func_start PlayerData_AddMoney
PlayerData_AddMoney: ; 0x02023A30
	ldr r2, _02023A50 ; =0x000F423F
	cmp r1, r2
	bls _02023A3A
	str r2, [r0, #0x14]
	b _02023A40
_02023A3A:
	ldr r2, [r0, #0x14]
	add r1, r2, r1
	str r1, [r0, #0x14]
_02023A40:
	ldr r2, [r0, #0x14]
	ldr r1, _02023A50 ; =0x000F423F
	cmp r2, r1
	bls _02023A4A
	str r1, [r0, #0x14]
_02023A4A:
	ldr r0, [r0, #0x14]
	bx lr
	nop
_02023A50: .word 0x000F423F

	thumb_func_start PlayerData_SubMoney
PlayerData_SubMoney: ; 0x02023A54
	ldr r2, [r0, #0x14]
	cmp r2, r1
	bhs _02023A5E
	mov r1, #0x0
	b _02023A60
_02023A5E:
	sub r1, r2, r1
_02023A60:
	str r1, [r0, #0x14]
	ldr r0, [r0, #0x14]
	bx lr
	.balign 4

	thumb_func_start FUN_02023A68
FUN_02023A68: ; 0x02023A68
	ldrb r0, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_02023A6C
FUN_02023A6C: ; 0x02023A6C
	strb r1, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_02023A70
FUN_02023A70: ; 0x02023A70
	ldrb r0, [r0, #0x19]
	bx lr

	thumb_func_start FUN_02023A74
FUN_02023A74: ; 0x02023A74
	strb r1, [r0, #0x19]
	bx lr

	thumb_func_start FUN_02023A78
FUN_02023A78: ; 0x02023A78
	ldrb r2, [r0, #0x1d]
	mov r1, #0x1
	bic r2, r1
	mov r1, #0x1
	orr r1, r2
	strb r1, [r0, #0x1d]
	bx lr
	.balign 4

	thumb_func_start FUN_02023A88
FUN_02023A88: ; 0x02023A88
	ldrb r0, [r0, #0x1d]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_02023A90
FUN_02023A90: ; 0x02023A90
	ldrb r2, [r0, #0x1d]
	mov r1, #0x2
	orr r1, r2
	strb r1, [r0, #0x1d]
	bx lr
	.balign 4

	thumb_func_start FUN_02023A9C
FUN_02023A9C: ; 0x02023A9C
	ldrb r0, [r0, #0x1d]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start PlayerData_NameAndOTIDMatchPlayer
PlayerData_NameAndOTIDMatchPlayer: ; 0x02023AA4
	push {r3-r5, lr}
	mov r2, #0x7
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl StringNotEqualN
	cmp r0, #0x0
	bne _02023AC0
	ldr r1, [r5, #0x10]
	ldr r0, [r4, #0x10]
	cmp r1, r0
	bne _02023AC0
	mov r0, #0x1
	pop {r3-r5, pc}
_02023AC0:
	mov r0, #0x0
	pop {r3-r5, pc}
