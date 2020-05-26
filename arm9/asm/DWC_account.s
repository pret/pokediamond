	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global UNK_0210618C
UNK_0210618C: ; 0x0210618C
	.asciz "%s%c%c%c%c%s"

	.balign 4, 0
	.global UNK_0210619C
UNK_0210619C: ; 0x0210619C
	; .asciz "0123456789abcdefghijklmnopqrstuvwxyz"
	.byte 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66
	.byte 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76
	.byte 0x00, 0x00, 0x00, 0x00

	.text

	arm_func_start DWC_IsEqualFriendData
DWC_IsEqualFriendData: ; 0x02096B78
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r7, r0
	bl DWCi_Acc_GetFlag_DataType
	mov r5, r0
	mov r0, r4
	bl DWCi_Acc_GetFlag_DataType
	cmp r5, r0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r7,pc}
	cmp r5, #0x3
	bne _02096BD8
	mov r0, r7
	bl DWCi_Acc_GetGsProfileId
	mov r5, r0
	mov r0, r4
	bl DWCi_Acc_GetGsProfileId
	cmp r5, r0
	moveq r0, #0x1
	add sp, sp, #0x4
	movne r0, #0x0
	ldmia sp!, {r4-r7,pc}
_02096BD8:
	cmp r5, #0x1
	bne _02096C34
	mov r0, r7
	bl DWCi_Acc_GetUserId
	mov r5, r0
	mov r6, r1
	mov r0, r4
	bl DWCi_Acc_GetUserId
	cmp r6, r1
	cmpeq r5, r0
	bne _02096C28
	mov r0, r7
	bl DWCi_Acc_GetPlayerId
	mov r5, r0
	mov r0, r4
	bl DWCi_Acc_GetPlayerId
	cmp r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r7,pc}
_02096C28:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_02096C34:
	cmp r5, #0x2
	bne _02096C6C
	mov r0, r7
	bl DWCi_Acc_GetFriendKey
	mov r5, r0
	mov r6, r1
	mov r0, r4
	bl DWCi_Acc_GetFriendKey
	cmp r6, r1
	cmpeq r5, r0
	moveq r0, #0x1
	add sp, sp, #0x4
	movne r0, #0x0
	ldmia sp!, {r4-r7,pc}
_02096C6C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start DWC_LoginIdToUserName
DWC_LoginIdToUserName: ; 0x02096C78
	ldr ip, _02096C8C ; =DWCi_Acc_LoginIdToUserName
	mov r3, r0
	mov r0, r1
	ldr r1, [r3, #0x24]
	bx r12
	.balign 4
_02096C8C: .word DWCi_Acc_LoginIdToUserName

	arm_func_start DWC_SetGsProfileId
DWC_SetGsProfileId: ; 0x02096C90
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	mov r1, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	mov r0, r5
	mov r1, r4
	bl DWCi_Acc_SetGsProfileId
	mov r0, r5
	mov r1, #0x3
	bl DWCi_Acc_SetFlag_DataType
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start DWC_CreateExchangeToken
DWC_CreateExchangeToken: ; 0x02096CCC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	mov r0, r4
	mov r1, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	mov r0, r5
	bl DWCi_Acc_IsAuthentic
	cmp r0, #0x0
	addeq r0, r5, #0x4
	ldmeqia r0, {r0-r2}
	addeq sp, sp, #0x4
	stmeqia r4, {r0-r2}
	ldmeqia sp!, {r4-r5,pc}
	ldr r1, [r5, #0x1c]
	mov r0, r4
	bl DWCi_Acc_SetGsProfileId
	mov r0, r4
	mov r1, #0x3
	bl DWCi_Acc_SetFlag_DataType
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start DWC_CreateFriendKeyToken
DWC_CreateFriendKeyToken: ; 0x02096D2C
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r4, r2
	mov r6, r0
	mov r1, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl DWCi_Acc_SetFriendKey
	mov r0, r6
	mov r1, #0x2
	bl DWCi_Acc_SetFlag_DataType
	ldmia sp!, {r4-r6,pc}

	arm_func_start DWC_CreateFriendKey
DWC_CreateFriendKey: ; 0x02096D68
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r0
	ldr r0, [r3, #0x1c]
	mov r2, #0x0
	mov r1, r2
	cmp r0, #0x0
	beq _02096D94
	ldr r1, [r3, #0x24]
	bl DWC_Acc_CreateFriendKey
	mov r2, r0
_02096D94:
	mov r0, r2
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start DWC_GetGsProfileId
DWC_GetGsProfileId: ; 0x02096DA0
	stmdb sp!, {r4-r6,lr}
	mov r4, r1
	mov r6, r0
	mov r0, r4
	bl DWCi_Acc_GetFlag_DataType
	cmp r0, #0x1
	beq _02096E14
	cmp r0, #0x2
	beq _02096DD0
	cmp r0, #0x3
	beq _02096E08
	b _02096E1C
_02096DD0:
	mov r0, r4
	bl DWCi_Acc_GetFriendKey
	ldr r2, [r6, #0x24]
	mov r4, r0
	mov r5, r1
	bl DWC_Acc_CheckFriendKey
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r2, [r6, #0x24]
	mov r0, r4
	mov r1, r5
	bl DWC_Acc_FriendKeyToGsProfileId
	ldmia sp!, {r4-r6,pc}
_02096E08:
	mov r0, r4
	bl DWCi_Acc_GetGsProfileId
	ldmia sp!, {r4-r6,pc}
_02096E14:
	mvn r0, #0x0
	ldmia sp!, {r4-r6,pc}
_02096E1C:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start DWC_GetFriendKey
DWC_GetFriendKey: ; 0x02096E24
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl DWCi_Acc_GetFlag_DataType
	cmp r0, #0x2
	movne r0, #0x0
	movne r1, r0
	ldmneia sp!, {r4,pc}
	mov r0, r4
	bl DWCi_Acc_GetFriendKey
	ldmia sp!, {r4,pc}

	arm_func_start DWCi_Acc_ClearDirty
DWCi_Acc_ClearDirty: ; 0x02096E4C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x400
	mov r4, r0
	ldr r1, [r4, #0x20]
	add r0, sp, #0x0
	bic r2, r1, #0x1
	ldr r1, _02096E8C ; =0xEDB88320
	str r2, [r4, #0x20]
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x0
	mov r1, r4
	mov r2, #0x3c
	bl MATH_CalcCRC32
	str r0, [r4, #0x3c]
	add sp, sp, #0x400
	ldmia sp!, {r4,pc}
	.balign 4
_02096E8C: .word 0xEDB88320

	arm_func_start DWC_ClearDirtyFlag
DWC_ClearDirtyFlag: ; 0x02096E90
	ldr ip, _02096E98 ; =DWCi_Acc_ClearDirty
	bx r12
	.balign 4
_02096E98: .word DWCi_Acc_ClearDirty

	arm_func_start DWCi_Acc_IsDirty
DWCi_Acc_IsDirty: ; 0x02096E9C
	ldr r0, [r0, #0x20]
	and r0, r0, #0x1
	cmp r0, #0x1
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

	arm_func_start DWC_CheckDirtyFlag
DWC_CheckDirtyFlag: ; 0x02096EB4
	ldr ip, _02096EBC ; =DWCi_Acc_IsDirty
	bx r12
	.balign 4
_02096EBC: .word DWCi_Acc_IsDirty

	arm_func_start DWCi_Acc_SetLoginIdToUserData
DWCi_Acc_SetLoginIdToUserData: ; 0x02096EC0
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x400
	mov r4, r0
	add r3, r4, #0x10
	mov r12, r2
	ldmia r1, {r0-r2}
	stmia r3, {r0-r2}
	ldr r1, _02096F14 ; =0xEDB88320
	add r0, sp, #0x0
	str r12, [r4, #0x1c]
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x0
	mov r1, r4
	mov r2, #0x3c
	bl MATH_CalcCRC32
	str r0, [r4, #0x3c]
	ldr r0, [r4, #0x20]
	orr r0, r0, #0x1
	str r0, [r4, #0x20]
	add sp, sp, #0x400
	ldmia sp!, {r4,pc}
	.balign 4
_02096F14: .word 0xEDB88320

	arm_func_start DWC_CheckValidConsole
DWC_CheckValidConsole: ; 0x02096F18
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, r4, #0x10
	bl DWCi_Acc_GetFlag_DataType
	cmp r0, #0x0
	addeq sp, sp, #0x18
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
	add r0, sp, #0x0
	bl DWC_Auth_GetId
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	addeq sp, sp, #0x18
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	add r0, r4, #0x10
	bl DWCi_Acc_GetUserId
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x0]
	cmp r2, r1
	cmpeq r3, r0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start DWC_CheckHasProfile
DWC_CheckHasProfile: ; 0x02096F80
	stmdb sp!, {r4,lr}
	mov r4, r0
	add r0, r4, #0x10
	bl DWCi_Acc_IsValidLoginId
	cmp r0, #0x0
	beq _02096FA8
	ldr r0, [r4, #0x1c]
	cmp r0, #0x0
	movgt r0, #0x1
	ldmgtia sp!, {r4,pc}
_02096FA8:
	mov r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start DWC_CheckUserData
DWC_CheckUserData: ; 0x02096FB0
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x400
	ldr r1, _02096FF0 ; =0xEDB88320
	mov r4, r0
	add r0, sp, #0x0
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x0
	mov r1, r4
	mov r2, #0x3c
	bl MATH_CalcCRC32
	ldr r1, [r4, #0x3c]
	cmp r0, r1
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x400
	ldmia sp!, {r4,pc}
	.balign 4
_02096FF0: .word 0xEDB88320

	arm_func_start DWC_CreateUserData
DWC_CreateUserData: ; 0x02096FF4
	ldr ip, _02096FFC ; =DWCi_Acc_CreateUserData
	bx r12
	.balign 4
_02096FFC: .word DWCi_Acc_CreateUserData

	arm_func_start DWCi_Acc_IsValidFriendData
DWCi_Acc_IsValidFriendData: ; 0x02097000
	ldr ip, _02097008 ; =DWC_IsValidFriendData
	bx r12
	.balign 4
_02097008: .word DWC_IsValidFriendData

	arm_func_start DWC_IsValidFriendData
DWC_IsValidFriendData: ; 0x0209700C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl DWCi_Acc_GetFlag_DataType
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start DWCi_Acc_IsAuthentic
DWCi_Acc_IsAuthentic:
	ldr ip, _02097038 ; =DWCi_Acc_IsValidLoginId
	add r0, r0, #0x10
	bx r12
	.balign 4
_02097038: .word DWCi_Acc_IsValidLoginId

	arm_func_start DWCi_Acc_IsValidLoginId
DWCi_Acc_IsValidLoginId:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl DWCi_Acc_GetFlag_DataType
	cmp r0, #0x1
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start DWCi_Acc_CheckConsoleUserId
DWCi_Acc_CheckConsoleUserId: ; 0x0209705C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, sp, #0x0
	bl DWC_Auth_GetId
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	beq _020970A4
	mov r0, r4
	bl DWCi_Acc_GetUserId
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x0]
	cmp r2, r1
	cmpeq r3, r0
	moveq r0, #0x1
	add sp, sp, #0x18
	movne r0, #0x0
	ldmia sp!, {r4,pc}
_020970A4:
	mov r0, r4
	bl DWCi_Acc_GetUserId
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	cmp r2, r1
	cmpeq r3, r0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start DWCi_Acc_CreateTempLoginId
DWCi_Acc_CreateTempLoginId: ; 0x020970CC
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x38
	mov r6, r0
	add r0, sp, #0x14
	bl OS_GetLowEntropyData
	mov r3, #0x1
	add r2, sp, #0x14
_020970E8:
	add r0, r2, r3, lsl #0x2
	ldr r1, [r2, r3, lsl #0x2]
	ldr r0, [r0, #-0x4]
	eor r0, r1, r0
	str r0, [r2, r3, lsl #0x2]
	add r3, r3, #0x1
	cmp r3, #0x8
	blo _020970E8
	add r0, sp, #0x0
	ldr r5, [sp, #0x30]
	mov r4, #0x0
	bl DWC_Auth_GetId
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	beq _02097138
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	mov r0, r6
	bl DWCi_Acc_SetUserId
	b _02097148
_02097138:
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0xc]
	mov r0, r6
	bl DWCi_Acc_SetUserId
_02097148:
	ldr r0, _02097184 ; =0x6C078965
	ldr r1, _02097188 ; =0x5D588B65
	umull r3, r2, r5, r0
	mla r2, r5, r1, r2
	ldr r1, _0209718C ; =0x00269EC3
	mla r2, r4, r0, r2
	adds r0, r3, r1
	mov r0, r6
	adc r1, r2, #0x0
	bl DWCi_Acc_SetPlayerId
	mov r0, r6
	mov r1, #0x1
	bl DWCi_Acc_SetFlag_DataType
	add sp, sp, #0x38
	ldmia sp!, {r4-r6,pc}
	.balign 4
_02097184: .word 0x6C078965
_02097188: .word 0x5D588B65
_0209718C: .word 0x00269EC3

	arm_func_start DWCi_Acc_CreateUserData
DWCi_Acc_CreateUserData: ; 0x02097190
	stmdb sp!, {r4-r5,lr}
	ldr ip, _02097210 ; =0x00000404
	sub sp, sp, r12
	mov r4, r1
	mov r1, #0x0
	mov r2, #0x40
	mov r5, r0
	bl MI_CpuFill8
	mov r0, #0x40
	str r0, [r5, #0x0]
	mov r0, #0x0
	str r0, [r5, #0x1c]
	add r0, r5, #0x4
	str r4, [r5, #0x24]
	bl DWCi_Acc_CreateTempLoginId
	add r0, r5, #0x10
	mov r1, #0x0
	bl DWCi_Acc_SetFlag_DataType
	ldr r1, _02097214 ; =0xEDB88320
	add r0, sp, #0x0
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x0
	mov r1, r5
	mov r2, #0x3c
	bl MATH_CalcCRC32
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x20]
	orr r0, r0, #0x1
	str r0, [r5, #0x20]
	ldr ip, _02097210 ; =0x00000404
	add sp, sp, r12
	ldmia sp!, {r4-r5,pc}
	.balign 4
_02097210: .word 0x00000404
_02097214: .word 0xEDB88320

	arm_func_start DWCi_Acc_LoginIdToUserName
DWCi_Acc_LoginIdToUserName: ; 0x02097218
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x40
	mov r6, r0
	mov r4, r1
	mov r5, r2
	bl DWCi_Acc_GetUserId
	add r3, sp, #0x14
	mov r2, #0x2b
	bl DWCi_Acc_U64ToString32
	mov r0, r6
	bl DWCi_Acc_GetPlayerId
	mov r1, #0x0
	mov r2, #0x20
	add r3, sp, #0x29
	bl DWCi_Acc_U64ToString32
	mov r1, r4, lsr #0x18
	and r1, r1, #0xff
	str r1, [sp, #0x0]
	mov r1, r4, lsr #0x10
	and r1, r1, #0xff
	str r1, [sp, #0x4]
	mov r1, r4, lsr #0x8
	and r1, r1, #0xff
	str r1, [sp, #0x8]
	and r1, r4, #0xff
	str r1, [sp, #0xc]
	add r2, sp, #0x29
	str r2, [sp, #0x10]
	ldr r2, _020972A4 ; =UNK_0210618C
	mov r0, r5
	mov r1, #0x15
	add r3, sp, #0x14
	bl OS_SNPrintf
	add sp, sp, #0x40
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020972A4: .word UNK_0210618C

	arm_func_start DWCi_Acc_U64ToString32
DWCi_Acc_U64ToString32: ; 0x020972A8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr lr, _0209731C ; =0x66666667
	add r4, r2, #0x4
	smull r12, r2, lr, r4
	mov r2, r2, asr #0x1
	mov r12, r4, lsr #0x1f
	add r2, r12, r2
	cmp r2, #0x0
	ldr r6, _02097320 ; =UNK_0210619C
	mov r7, #0x0
	ble _0209730C
	add r4, r3, r2
	sub r4, r4, #0x1
	mov r12, #0x1f
_020972E4:
	and r5, r0, r12
	ldrsb r5, [r6, r5]
	mov r0, r0, lsr #0x5
	mov lr, r1, lsr #0x5
	strb r5, [r4, -r7]
	add r7, r7, #0x1
	orr r0, r0, r1, lsl #0x1b
	mov r1, lr
	cmp r7, r2
	blt _020972E4
_0209730C:
	mov r0, #0x0
	strb r0, [r3, r2]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_0209731C: .word 0x66666667
_02097320: .word UNK_0210619C

	arm_func_start DWC_Acc_FriendKeyToGsProfileId
DWC_Acc_FriendKeyToGsProfileId: ; 0x02097324
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl DWC_Acc_CheckFriendKey
	cmp r0, #0x0
	mvnne r0, #0x0
	andne r0, r4, r0
	moveq r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start DWC_Acc_CheckFriendKey
DWC_Acc_CheckFriendKey: ; 0x02097334
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x108
	mov r4, r1
	and r3, r4, #0x0
	mov r1, #0x0
	and r12, r0, #0x80000000
	cmp r3, r1
	cmpeq r12, r1
	addne sp, sp, #0x108
	movne r0, r1
	ldmneia sp!, {r4,pc}
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	mov r1, #0x7
	str r2, [sp, #0x4]
	bl MATHi_CRC8InitTable
	add r0, sp, #0x8
	add r1, sp, #0x0
	mov r2, #0x8
	bl MATH_CalcCRC8
	and r2, r0, #0x7f
	mov r1, r2, asr #0x1f
	mov r0, #0x0
	cmp r1, r0
	cmpeq r2, r4
	moveq r0, #0x1
	add sp, sp, #0x108
	ldmia sp!, {r4,pc}

	arm_func_start DWC_CheckFriendKey
DWC_CheckFriendKey: ; 0x020973B4
	ldr ip, _020973CC ; =DWC_Acc_CheckFriendKey
	mov r3, r0
	mov r0, r1
	mov r1, r2
	ldr r2, [r3, #0x24]
	bx r12
	.balign 4
_020973CC: .word DWC_Acc_CheckFriendKey

	arm_func_start DWC_Acc_CreateFriendKey
DWC_Acc_CreateFriendKey: ; 0x020973D0
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x108
	mov r4, r0
	str r1, [sp, #0x4]
	add r0, sp, #0x8
	mov r1, #0x7
	str r4, [sp, #0x0]
	bl MATHi_CRC8InitTable
	add r0, sp, #0x8
	add r1, sp, #0x0
	mov r2, #0x8
	bl MATH_CalcCRC8
	and r0, r0, #0x7f
	orr r1, r0, #0x0
	orr r0, r4, #0x0
	add sp, sp, #0x108
	ldmia sp!, {r4,pc}

	arm_func_start DWCi_SetBuddyFriendData
DWCi_SetBuddyFriendData: ; 0x02097414
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl DWCi_Acc_GetFlag_DataType
	cmp r0, #0x3
	ldmneia sp!, {r4,pc}
	mov r0, r4
	bl DWCi_Acc_GetFlags
	orr r1, r0, #0x4
	mov r0, r4
	bl DWCi_Acc_SetFlags
	ldmia sp!, {r4,pc}

	arm_func_start DWCi_Acc_SetFlag_DataType
DWCi_Acc_SetFlag_DataType: ; 0x02097440
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl DWCi_Acc_GetFlags
	bic r1, r0, #0x3
	mov r0, r5
	orr r1, r1, r4
	bl DWCi_Acc_SetFlags
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start DWCi_Acc_SetFlags
DWCi_Acc_SetFlags: ; 0x0209746C
	ldr ip, _0209747C ; =DWCi_Acc_SetMaskBits
	ldr r3, _02097480 ; =0x001FFFFF
	mov r2, #0xb
	bx r12
	.balign 4
_0209747C: .word DWCi_Acc_SetMaskBits
_02097480: .word 0x001FFFFF

	arm_func_start DWC_GetFriendDataType
DWC_GetFriendDataType: ; 0x02097484
	ldr ip, _0209748C ; =DWCi_Acc_GetFlag_DataType
	bx r12
	.balign 4
_0209748C: .word DWCi_Acc_GetFlag_DataType

	arm_func_start DWC_IsBuddyFriendData
DWC_IsBuddyFriendData: ; 0x02097490
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl DWCi_Acc_GetFlag_DataType
	cmp r0, #0x3
	bne _020974C0
	mov r0, r4
	bl DWCi_Acc_GetFlags
	and r0, r0, #0x4
	cmp r0, #0x4
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4,pc}
_020974C0:
	mov r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start DWCi_Acc_GetFlag_DataType
DWCi_Acc_GetFlag_DataType: ; 0x020974C8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl DWCi_Acc_GetFlags
	and r0, r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start DWCi_Acc_GetFlags
DWCi_Acc_GetFlags: ; 0x020974E0
	ldr r1, [r0, #0x0]
	ldr r0, _020974F0 ; =0x001FFFFF
	and r0, r0, r1, lsr #0xb
	bx lr
	.balign 4
_020974F0: .word 0x001FFFFF

	arm_func_start DWCi_Acc_SetGsProfileId
DWCi_Acc_SetGsProfileId: ; 0x020974F4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start DWCi_Acc_SetFriendKey
DWCi_Acc_SetFriendKey: ; 0x020974FC
	str r1, [r0, #0x4]
	str r2, [r0, #0x8]
	bx lr

	arm_func_start DWCi_Acc_SetPlayerId
DWCi_Acc_SetPlayerId: ; 0x02097508
	str r1, [r0, #0x8]
	bx lr

	arm_func_start DWCi_Acc_SetUserId
DWCi_Acc_SetUserId: ; 0x02097510
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r12, #0x0
	mov r4, r1
	mov r1, r2
	ldr r3, _02097540 ; =0x000007FF
	mov r2, r12
	mov r5, r0
	bl DWCi_Acc_SetMaskBits
	str r4, [r5, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_02097540: .word 0x000007FF

	arm_func_start DWCi_Acc_GetGsProfileId
DWCi_Acc_GetGsProfileId:
	ldr r0, [r0, #0x4]
	bx lr

	arm_func_start DWCi_Acc_GetFriendKey
DWCi_Acc_GetFriendKey: ; 0x0209754C
	ldr r1, [r0, #0x8]
	ldr r0, [r0, #0x4]
	orr r1, r1, #0x0
	orr r0, r0, #0x0
	bx lr

	arm_func_start DWCi_Acc_GetPlayerId
DWCi_Acc_GetPlayerId:
	ldr r0, [r0, #0x8]
	bx lr

	arm_func_start DWCi_Acc_GetUserId
DWCi_Acc_GetUserId: ; 0x02097568
	ldr r2, [r0, #0x0]
	ldr r1, _02097584 ; =0x000007FF
	ldr r0, [r0, #0x4]
	and r1, r2, r1
	orr r1, r1, #0x0
	orr r0, r0, #0x0
	bx lr
	.balign 4
_02097584: .word 0x000007FF

	arm_func_start DWCi_Acc_SetMaskBits
DWCi_Acc_SetMaskBits: ; 0x02097588
	mvn r12, r3
	ands r12, r1, r12
	movne r0, #0x0
	bxne lr
	mvn r3, r3, lsl r2
	ldr r12, [r0, #0x0]
	and r3, r12, r3
	orr r1, r3, r1, lsl r2
	str r1, [r0, #0x0]
	mov r0, #0x1
	bx lr
