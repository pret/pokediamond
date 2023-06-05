	.include "asm/macros.inc"
	.include "global.inc"

	.extern gGameLanguage
	.extern gGameVersion

	.text

	thumb_func_start FUN_02066840
FUN_02066840: ; 0x02066840
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	str r1, [sp, #0x0]
	add r7, r2, #0x0
	bl Save_PlayerData_GetProfileAddr
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02029AFC
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl SaveStruct23_GetSubstruct2
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r1, #0x0
	mov r2, #0xe4
	bl MI_CpuFill8
	add r0, r4, #0x0
	bl PlayerProfile_GetNamePtr
	add r1, r7, #0x0
	add r1, #0xa8
	mov r2, #0x10
	bl MI_CpuCopy8
	add r0, r4, #0x0
	bl PlayerProfile_GetTrainerID
	add r1, r7, #0x0
	add r1, #0xbc
	str r0, [r1, #0x0]
	ldr r0, _02066970 ; =gGameVersion
	ldrb r1, [r0, #0x0]
	add r0, r7, #0x0
	add r0, #0xb8
	strb r1, [r0, #0x0]
	ldr r0, _02066974 ; =gGameLanguage
	ldrb r1, [r0, #0x0]
	add r0, r7, #0x0
	add r0, #0xb9
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_02029B38
	add r1, r7, #0x0
	add r1, #0xba
	strb r0, [r1, #0x0]
	add r0, r5, #0x0
	bl FUN_02029B3C
	add r1, r7, #0x0
	add r1, #0xbb
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	bl PlayerProfile_GetTrainerGender
	add r1, r7, #0x0
	add r1, #0xc8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1f
	ldrb r1, [r1, #0x0]
	mov r2, #0x2
	lsr r0, r0, #0x1e
	bic r1, r2
	orr r1, r0
	add r0, r7, #0x0
	add r0, #0xc8
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	bl PlayerProfile_GetAvatar
	add r1, r0, #0x0
	add r0, r7, #0x0
	add r0, #0xc8
	ldrb r0, [r0, #0x0]
	mov r2, #0x1
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bl FUN_020536D0
	add r1, r7, #0x0
	add r1, #0xc9
	strb r0, [r1, #0x0]
	add r0, r7, #0x0
	mov r4, #0x0
	str r0, [sp, #0x8]
	add r0, #0xca
	add r5, r4, #0x0
	str r0, [sp, #0x8]
_020668FC:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl SaveStruct23_GetMessage
	ldr r1, [sp, #0x8]
	mov r2, #0x8
	add r1, r1, r5
	bl MI_CpuCopy8
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, #0x3
	blt _020668FC
	add r0, r6, #0x0
	mov r1, #0x3
	bl SaveStruct23_GetMessage
	add r1, r7, #0x0
	add r1, #0xc0
	mov r2, #0x8
	bl MI_CpuCopy8
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02066956
	ldr r0, [sp, #0x4]
	mov r1, #0x7
	mov r2, #0x0
	bl SaveStruct23_Substruct2_SetFlag
	add r1, r7, #0x0
	add r1, #0xe2
	strh r0, [r1, #0x0]
	add r0, r7, #0x0
	add r0, #0xe2
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0206696C
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x0]
	add r2, r7, #0x0
	bl SaveStruct23_Substruct2_GetArray
	add sp, #0xc
	pop {r4-r7, pc}
_02066956:
	ldr r0, [sp, #0x4]
	bl SaveStruct23_Substruct2_GetField_0x16
	add r1, r7, #0x0
	add r1, #0xe2
	strh r0, [r1, #0x0]
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x0]
	add r2, r7, #0x0
	bl SaveStruct23_Substruct2_GetArray
_0206696C:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02066970: .word gGameVersion
_02066974: .word gGameLanguage
