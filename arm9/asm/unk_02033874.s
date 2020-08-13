	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02033874
FUN_02033874: ; 0x02033874
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r5, r1, #0x0
	str r2, [sp, #0x0]
	bl FUN_020286EC
	bl FUN_02028228
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020286EC
	mov r1, #0x0
	bl FUN_0202838C
	add r4, r0, #0x0
	mov r1, #0x0
	ldr r0, [sp, #0x0]
	mvn r1, r1
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	bl DWC_IsValidFriendData
	cmp r0, #0x0
	bne _020338AE
	add sp, #0x8
	mov r0, #0x3
	pop {r3-r7, pc}
_020338AE:
	mov r7, #0x0
_020338B0:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl DWC_IsEqualFriendData
	cmp r0, #0x0
	beq _020338C6
	ldr r0, [sp, #0x0]
	add sp, #0x8
	str r7, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
_020338C6:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl DWC_GetGsProfileId
	cmp r0, #0x0
	ble _020338F4
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl DWC_GetGsProfileId
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl DWC_GetGsProfileId
	ldr r1, [sp, #0x4]
	cmp r1, r0
	bne _020338F4
	ldr r0, [sp, #0x0]
	add sp, #0x8
	str r7, [r0, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_020338F4:
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bge _0203390A
	add r0, r4, #0x0
	bl DWC_IsValidFriendData
	cmp r0, #0x0
	bne _0203390A
	ldr r0, [sp, #0x0]
	str r7, [r0, #0x0]
_0203390A:
	add r7, r7, #0x1
	add r4, #0xc
	cmp r7, #0x20
	blt _020338B0
	mov r0, #0x2
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02033918
FUN_02033918: ; 0x02033918
	push {r3-r7, lr}
	sub sp, #0x18
	add r4, r0, #0x0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r6, r3, #0x0
	bl FUN_020286EC
	bl FUN_02028228
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020286EC
	mov r1, #0x0
	bl FUN_0202838C
	add r5, r0, #0x0
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, r7, #0x0
	bl DWC_CheckFriendKey
	cmp r0, #0x0
	bne _02033950
	add sp, #0x18
	mov r0, #0x3
	pop {r3-r7, pc}
_02033950:
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, sp, #0xc
	bl DWC_CreateFriendKeyToken
	add r0, r7, #0x0
	add r1, sp, #0xc
	bl DWC_GetGsProfileId
	cmp r0, #0x0
	bgt _0203396C
	add sp, #0x18
	mov r0, #0x3
	pop {r3-r7, pc}
_0203396C:
	mov r0, #0x0
	mvn r0, r0
	str r0, [r6, #0x0]
	mov r4, #0x0
_02033974:
	add r0, r7, #0x0
	add r1, sp, #0xc
	bl DWC_GetGsProfileId
	str r0, [sp, #0x8]
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl DWC_GetGsProfileId
	ldr r1, [sp, #0x8]
	cmp r1, r0
	bne _02033994
	add sp, #0x18
	str r4, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
_02033994:
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	bge _020339A6
	add r0, r5, #0x0
	bl DWC_IsValidFriendData
	cmp r0, #0x0
	bne _020339A6
	str r4, [r6, #0x0]
_020339A6:
	add r4, r4, #0x1
	add r5, #0xc
	cmp r4, #0x20
	blt _02033974
	mov r0, #0x2
	add sp, #0x18
	pop {r3-r7, pc}

	thumb_func_start FUN_020339B4
FUN_020339B4: ; 0x020339B4
	push {r4-r7, lr}
	sub sp, #0x14
	add r6, r1, #0x0
	mov r1, #0x0
	add r5, r0, #0x0
	str r2, [sp, #0x4]
	str r1, [sp, #0xc]
	bl FUN_020286EC
	mov r1, #0x0
	bl FUN_0202838C
	str r0, [sp, #0x8]
	mov r4, #0x0
	bl FUN_02030F20
	cmp r0, #0x0
	ble _02033A68
_020339D8:
	bl FUN_02031190
	cmp r4, r0
	beq _02033A5C
	add r0, r4, #0x0
	bl FUN_0202DFD8
	add r7, r0, #0x0
	beq _02033A5C
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, sp, #0x10
	bl FUN_02033874
	str r0, [r6, #0x0]
	cmp r0, #0x3
	bne _020339FE
	bl ErrorHandling
_020339FE:
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	bne _02033A1C
	mov r0, #0x2
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02033A70
	add r0, r5, #0x0
	bl FUN_0202E1BC
	b _02033A5C
_02033A1C:
	cmp r0, #0x1
	bne _02033A54
	bl FUN_02033590
	cmp r0, #0x0
	bne _02033A5C
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02033A70
	ldr r2, [sp, #0x10]
	mov r1, #0xc
	add r3, r2, #0x0
	mul r3, r1
	ldr r1, [sp, #0x8]
	add r0, r7, #0x0
	add r1, r1, r3
	mov r2, #0xc
	bl MI_CpuCopy8
	add r0, r5, #0x0
	bl FUN_0202E1BC
	b _02033A5C
_02033A54:
	cmp r0, #0x2
	bne _02033A5C
	mov r0, #0x1
	str r0, [sp, #0xc]
_02033A5C:
	add r6, r6, #0x4
	add r4, r4, #0x1
	bl FUN_02030F20
	cmp r4, r0
	blt _020339D8
_02033A68:
	ldr r0, [sp, #0xc]
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02033A70
FUN_02033A70: ; 0x02033A70
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r2, #0x0
	str r0, [sp, #0x0]
	add r7, r1, #0x0
	str r3, [sp, #0x4]
	bl FUN_020286EC
	add r1, r5, #0x0
	add r4, r0, #0x0
	bl FUN_0202838C
	str r0, [sp, #0x8]
	add r0, r7, #0x0
	bl FUN_0202DFA4
	add r6, r0, #0x0
	ldr r0, [sp, #0x28]
	cmp r0, #0x2
	beq _02033AA6
	add r0, r7, #0x0
	bl FUN_0202DFD8
	ldr r1, [sp, #0x8]
	mov r2, #0xc
	bl MI_CpuCopy8
_02033AA6:
	ldr r0, [sp, #0x28]
	cmp r0, #0x0
	bne _02033AEC
	ldr r1, [sp, #0x4]
	add r0, r6, #0x0
	bl PlayerProfile_GetPlayerName_NewString
	str r0, [sp, #0xc]
	ldr r2, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020283C0
	ldr r0, [sp, #0xc]
	bl String_dtor
	add r0, r6, #0x0
	bl PlayerProfile_GetTrainerGender
	add r3, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x8
	bl FUN_020282E8
	add r0, r6, #0x0
	bl PlayerProfile_GetTrainerID
	add r3, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_020282E8
	b _02033B22
_02033AEC:
	cmp r0, #0x1
	bne _02033B22
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x8
	bl FUN_0202822C
	cmp r0, #0x2
	bne _02033B22
	add r0, r6, #0x0
	bl PlayerProfile_GetTrainerGender
	add r3, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x8
	bl FUN_020282E8
	add r0, r6, #0x0
	bl PlayerProfile_GetTrainerID
	add r3, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_020282E8
_02033B22:
	ldr r1, [sp, #0x4]
	mov r0, #0x78
	bl String_ctor
	str r0, [sp, #0x10]
	add r0, r7, #0x0
	bl FUN_0202DFFC
	add r1, r0, #0x0
	ldr r0, [sp, #0x10]
	bl CopyU16ArrayToString
	ldr r2, [sp, #0x10]
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02028404
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r6, #0x0
	bl FUN_02023A28
	add r3, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x7
	bl FUN_020282E8
	ldr r0, [sp, #0x0]
	bl FUN_0202E1BC
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
