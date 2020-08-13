    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020F7440
UNK_020F7440: ; 0x020F7440
	.byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
	.byte 0x11, 0x43, 0x10, 0x44

	.section .data

	.global UNK_02105FA8
UNK_02105FA8: ; 0x02105FA8
	.asciz "data/tmap_flags.dat"

	.text

	thumb_func_start FUN_0205F7A0
FUN_0205F7A0: ; 0x0205F7A0
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x0]
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	str r2, [sp, #0x4]
	bl SavArray_Flags_get
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034DCC
	mov r2, #0x5
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x6
	bl memset
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055320
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	asr r1, r4, #0x4
	asr r2, r6, #0x4
	lsr r1, r1, #0x1b
	lsr r2, r2, #0x1b
	add r1, r4, r1
	add r2, r6, r2
	ldr r0, [r0, #0x28]
	asr r1, r1, #0x5
	asr r2, r2, #0x5
	bl FUN_0203451C
	bl FUN_02034908
	cmp r0, #0x0
	beq _0205F806
	str r4, [r5, #0x0]
	str r6, [r5, #0x4]
	b _0205F812
_0205F806:
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #0x8]
	str r0, [r5, #0x0]
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x4]
_0205F812:
	ldr r0, [sp, #0x0]
	bl FUN_020377AC
	bl Sav2_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerGender
	str r0, [r5, #0xc]
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034E0C
	str r0, [sp, #0x8]
	ldr r0, [r0, #0x0]
	mov r1, #0x6
	add r0, r0, #0x4
	bl _s32_div_f
	mov r6, #0x0
	add r4, r5, #0x0
_0205F83E:
	ldr r0, [sp, #0x8]
	lsl r2, r1, #0x2
	add r0, r0, r2
	ldrb r2, [r0, #0x6]
	str r2, [r4, #0x20]
	ldrb r2, [r0, #0x7]
	str r2, [r4, #0x24]
	ldrb r2, [r0, #0x9]
	strh r2, [r4, #0x2a]
	ldrb r0, [r0, #0x8]
	cmp r0, #0x3
	bls _0205F85A
	mov r0, #0x4
	b _0205F85A
_0205F85A:
	strh r0, [r4, #0x28]
	add r0, r1, #0x5
	mov r1, #0x6
	bl _s32_div_f
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, #0x5
	blt _0205F83E
	mov r6, #0x4f
	mov r4, #0x0
	lsl r6, r6, #0x2
_0205F872:
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_0205F524
	cmp r0, #0x0
	beq _0205F888
	mov r0, #0x1
	ldrh r1, [r5, r6]
	lsl r0, r4
	orr r0, r1
	strh r0, [r5, r6]
_0205F888:
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _0205F872
	ldr r6, _0205F8C0 ; =UNK_020F7440
	mov r4, #0x0
_0205F892:
	ldrb r2, [r6, #0x0]
	add r0, r7, #0x0
	mov r1, #0x2
	bl FUN_0205F2E4
	mov r1, #0x49
	add r2, r5, r4
	lsl r1, r1, #0x2
	add r4, r4, #0x1
	add r6, r6, #0x1
	strb r0, [r2, r1]
	cmp r4, #0x14
	blt _0205F892
	ldr r0, [sp, #0x0]
	ldr r2, _0205F8C4 ; =UNK_02105FA8
	add r1, r5, #0x0
	bl FUN_0205F8CC
	ldr r1, _0205F8C8 ; =0x00000139
	ldr r0, [sp, #0x4]
	strb r0, [r5, r1]
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0205F8C0: .word UNK_020F7440
_0205F8C4: .word UNK_02105FA8
_0205F8C8: .word 0x00000139

	thumb_func_start FUN_0205F8CC
FUN_0205F8CC: ; 0x0205F8CC
	push {r3-r7, lr}
	sub sp, #0x70
	add r7, r0, #0x0
	ldr r0, [r7, #0xc]
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl SavArray_Flags_get
	str r0, [sp, #0x0]
	add r0, sp, #0x28
	bl FS_InitFile
	add r0, sp, #0x28
	add r1, r4, #0x0
	bl FS_OpenFile
	cmp r0, #0x0
	bne _0205F8F8
	bl ErrorHandling
	add sp, #0x70
	pop {r3-r7, pc}
_0205F8F8:
	add r0, sp, #0x28
	add r1, sp, #0x24
	mov r2, #0x4
	bl FS_ReadFile
	cmp r0, #0x0
	bge _0205F90A
	bl ErrorHandling
_0205F90A:
	mov r0, #0xb
	mov r1, #0x4
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0x4
	add r6, r0, #0x0
	bl MI_CpuFill8
	ldr r1, [sp, #0x24]
	ldr r0, _0205FA28 ; =0x0000013A
	mov r4, #0x0
	strb r1, [r5, r0]
	ldr r0, [sp, #0x24]
	cmp r0, #0x0
	ble _0205FA16
	mov r0, #0xc
	str r0, [sp, #0x10]
	mov r0, #0x3
	str r0, [sp, #0xc]
	mov r0, #0xc
	str r0, [sp, #0x8]
	mov r0, #0x3
	str r0, [sp, #0x4]
	mov r0, #0xc0
	str r0, [sp, #0x20]
	mov r0, #0x30
	str r0, [sp, #0x1c]
	mov r0, #0xc0
	str r0, [sp, #0x18]
	mov r0, #0x30
	add r5, #0x5c
	str r0, [sp, #0x14]
_0205F94C:
	add r0, sp, #0x28
	add r1, r6, #0x0
	mov r2, #0x4
	bl FS_ReadFile
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	beq _0205F962
	cmp r0, #0x2
	beq _0205F98C
	b _0205F9B2
_0205F962:
	ldrb r2, [r6, #0x1]
	ldr r0, [sp, #0x0]
	mov r1, #0x2
	bl FUN_0205F2E4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1e
	ldrb r1, [r5, r4]
	ldr r2, [sp, #0x8]
	lsr r0, r0, #0x1c
	bic r1, r2
	orr r0, r1
	strb r0, [r5, r4]
	ldrb r1, [r5, r4]
	ldr r0, [sp, #0x4]
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strb r0, [r5, r4]
	b _0205F9B2
_0205F98C:
	ldrb r1, [r6, #0x1]
	add r0, r7, #0x0
	bl FlagCheck
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1e
	ldrb r1, [r5, r4]
	ldr r2, [sp, #0x10]
	lsr r0, r0, #0x1c
	bic r1, r2
	orr r0, r1
	strb r0, [r5, r4]
	ldrb r1, [r5, r4]
	ldr r0, [sp, #0xc]
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strb r0, [r5, r4]
_0205F9B2:
	ldrb r0, [r6, #0x2]
	cmp r0, #0x1
	beq _0205F9BE
	cmp r0, #0x2
	beq _0205F9E8
	b _0205FA0E
_0205F9BE:
	ldrb r2, [r6, #0x3]
	ldr r0, [sp, #0x0]
	mov r1, #0x2
	bl FUN_0205F2E4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1e
	ldrb r1, [r5, r4]
	ldr r2, [sp, #0x18]
	lsr r0, r0, #0x18
	bic r1, r2
	orr r0, r1
	strb r0, [r5, r4]
	ldrb r1, [r5, r4]
	ldr r0, [sp, #0x14]
	bic r1, r0
	mov r0, #0x10
	orr r0, r1
	strb r0, [r5, r4]
	b _0205FA0E
_0205F9E8:
	ldrb r1, [r6, #0x3]
	add r0, r7, #0x0
	bl FlagCheck
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1e
	ldrb r1, [r5, r4]
	ldr r2, [sp, #0x20]
	lsr r0, r0, #0x18
	bic r1, r2
	orr r0, r1
	strb r0, [r5, r4]
	ldrb r1, [r5, r4]
	ldr r0, [sp, #0x1c]
	bic r1, r0
	mov r0, #0x10
	orr r0, r1
	strb r0, [r5, r4]
_0205FA0E:
	ldr r0, [sp, #0x24]
	add r4, r4, #0x1
	cmp r4, r0
	blt _0205F94C
_0205FA16:
	add r0, sp, #0x28
	bl FS_CloseFile
	add r0, r6, #0x0
	bl FreeToHeap
	add sp, #0x70
	pop {r3-r7, pc}
	nop
_0205FA28: .word 0x0000013A
