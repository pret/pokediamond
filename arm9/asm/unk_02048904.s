	.include "asm/macros.inc"
	.include "global.inc"

	.extern gMain

	.section .rodata

	.global UNK_020F46D8
UNK_020F46D8: ; 0x020F46D8
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x03

	.global UNK_020F46E0
UNK_020F46E0: ; 0x020F46E0
	.byte 0x01, 0x00, 0x10, 0x00, 0x00, 0x40, 0x0C, 0x00, 0x12, 0x11, 0x01, 0x10, 0x00, 0x40, 0x0C, 0x00
	.byte 0x03, 0x00, 0x10, 0x00, 0x00, 0x40, 0x0C, 0x00, 0x14, 0x01, 0x11, 0x01, 0x00, 0x40, 0x0C, 0x00
	.byte 0x11, 0x01, 0x11, 0x01, 0x00, 0x00, 0x0A, 0x00

	.text

	thumb_func_start FUN_02048904
FUN_02048904: ; 0x02048904
	ldr r1, [r0, #0x1c]
	ldr r2, _02048950 ; =0x0000014B
	ldr r1, [r1, #0x0]
	cmp r1, r2
	bgt _0204892C
	sub r2, r2, #0x5
	sub r2, r1, r2
	bmi _02048936
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02048920: ; jump table (using 16-bit offset)
	.short _02048932 - _02048920 - 2; case 0
	.short _02048932 - _02048920 - 2; case 1
	.short _02048932 - _02048920 - 2; case 2
	.short _02048932 - _02048920 - 2; case 3
	.short _02048932 - _02048920 - 2; case 4
	.short _02048932 - _02048920 - 2; case 5
_0204892C:
	ldr r2, _02048954 ; =0x000001ED
	cmp r1, r2
	bne _02048936
_02048932:
	mov r2, #0x1
	b _02048938
_02048936:
	mov r2, #0x0
_02048938:
	cmp r2, #0x0
	bne _02048946
	ldr r1, [r0, #0x6c]
	cmp r1, #0x4
	bne _02048946
	mov r1, #0x0
	str r1, [r0, #0x6c]
_02048946:
	cmp r2, #0x0
	beq _0204894E
	mov r1, #0x4
	str r1, [r0, #0x6c]
_0204894E:
	bx lr
	.balign 4
_02048950: .word 0x0000014B
_02048954: .word 0x000001ED

	thumb_func_start FUN_02048958
FUN_02048958: ; 0x02048958
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	bl FUN_02034E30
	add r6, r0, #0x0
	bl FUN_02034DC8
	add r2, r0, #0x0
	cmp r4, #0x0
	beq _0204898C
	ldr r3, [r5, #0x1c]
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldr r2, [r5, #0x1c]
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r2, #0x0]
_0204898C:
	ldr r1, [r5, #0x1c]
	add r0, r5, #0x0
	ldr r1, [r1, #0x0]
	bl FUN_02034A60
	ldr r0, [r5, #0x1c]
	ldr r1, [r0, #0x4]
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	beq _020489DA
	add r0, r5, #0x0
	bl FUN_02034B00
	ldrh r2, [r0, #0x0]
	ldr r1, [r5, #0x1c]
	str r2, [r1, #0x8]
	ldrh r2, [r0, #0x2]
	ldr r1, [r5, #0x1c]
	str r2, [r1, #0xc]
	ldrh r1, [r0, #0x6]
	mov r0, #0x1
	lsl r0, r0, #0x8
	cmp r1, r0
	bne _020489DA
	add r0, r6, #0x0
	bl FUN_02034DD0
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02034DC4
	add r2, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r4, #0x0]
_020489DA:
	pop {r4-r6, pc}

	thumb_func_start FUN_020489DC
FUN_020489DC: ; 0x020489DC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x6c]
	cmp r0, #0x5
	blt _020489EA
	bl GF_AssertFail
_020489EA:
	ldr r0, [r4, #0x70]
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0x10
	lsr r1, r0, #0x1c
	ldr r0, _020489F8 ; =gMain + 0x60
	strb r1, [r0, #0x5]
	pop {r4, pc}
	.balign 4
_020489F8: .word gMain + 0x60

	thumb_func_start FUN_020489FC
FUN_020489FC: ; 0x020489FC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [r5, #0x1c]
	add r4, r1, #0x0
	ldr r7, [r0, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_02034E30
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_0204AB44
	add r0, r5, #0x0
	bl ResetTempFlagsAndVars
	cmp r4, #0x0
	bne _02048A28
	add r0, r5, #0x0
	bl FUN_020636DC
	b _02048A2E
_02048A28:
	add r0, r5, #0x0
	bl FUN_02063684
_02048A2E:
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F408
	cmp r4, #0x0
	bne _02048A42
	add r0, r5, #0x0
	bl FUN_0204B0F8
_02048A42:
	cmp r4, #0x0
	bne _02048A50
	ldr r0, [r5, #0xc]
	bl FUN_02024ED8
	bl FUN_02025484
_02048A50:
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02034FE4
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #0xe
	bne _02048A72
	ldr r0, [sp, #0x0]
	bl FUN_0205F2C4
	cmp r0, #0x1
	beq _02048A80
_02048A72:
	cmp r6, #0x10
	bne _02048A82
	ldr r0, [sp, #0x0]
	bl FUN_0205F294
	cmp r0, #0x1
	bne _02048A82
_02048A80:
	mov r6, #0x0
_02048A82:
	ldr r0, [sp, #0x4]
	add r1, r6, #0x0
	bl FUN_02034DF4
	cmp r4, #0x0
	beq _02048AA6
	ldr r0, [sp, #0x4]
	bl FUN_02034E10
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl MapHeader_GetCameraType
	cmp r6, r0
	beq _02048AB4
	bl GF_AssertFail
	b _02048AB4
_02048AA6:
	add r0, r7, #0x0
	bl MapHeader_GetCameraType
	add r1, r0, #0x0
	ldr r0, [sp, #0x4]
	bl FUN_02034E18
_02048AB4:
	cmp r4, #0x0
	bne _02048ACA
	add r0, r7, #0x0
	bl FUN_02034EF8
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	beq _02048ACA
	ldr r0, [sp, #0x4]
	bl FUN_02034E04
_02048ACA:
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0203989C
	add r0, r5, #0x0
	mov r1, #0x0
	add r0, #0x74
	strh r1, [r0, #0x0]
	add r5, #0x76
	strh r1, [r5, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02048AE4
FUN_02048AE4: ; 0x02048AE4
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r1, #0x40
	mov r2, #0x5
	bl FUN_02057380
	str r0, [r5, #0x34]
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerGender
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02034E30
	bl FUN_02034E20
	ldr r3, [r5, #0x1c]
	ldr r1, [r0, #0x4]
	str r1, [sp, #0x0]
	str r4, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x34]
	ldr r1, [r3, #0x8]
	ldr r2, [r3, #0xc]
	ldr r3, [r3, #0x10]
	bl FUN_02055068
	str r0, [r5, #0x38]
	add r0, r5, #0x0
	bl FUN_02034AC8
	ldr r0, [r5, #0x34]
	bl FUN_02058768
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_02048B34
FUN_02048B34: ; 0x02048B34
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0204CC48
	ldr r0, [r4, #0x38]
	bl FUN_02055160
	ldr r0, [r4, #0x34]
	bl FUN_0205771C
	ldr r0, [r4, #0x34]
	bl FUN_020573AC
	pop {r4, pc}

	thumb_func_start FUN_02048B50
FUN_02048B50: ; 0x02048B50
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0x40
	mov r2, #0x5
	bl FUN_02057380
	str r0, [r5, #0x34]
	add r0, r5, #0x0
	bl FUN_02034E60
	ldr r0, [r5, #0xc]
	bl FUN_02034E30
	bl FUN_02034E20
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerGender
	add r2, r0, #0x0
	ldr r0, [r5, #0x34]
	add r1, r4, #0x0
	bl FUN_020550A4
	str r0, [r5, #0x38]
	ldr r0, [r5, #0x34]
	bl FUN_02058768
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02048B90
FUN_02048B90: ; 0x02048B90
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02048904
	ldr r0, [r4, #0x58]
	cmp r0, #0x0
	beq _02048BA2
	bl GF_AssertFail
_02048BA2:
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x28]
	ldr r0, [r0, #0x0]
	bl FUN_020344AC
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	mov r1, #0x3
	bl FUN_0205F524
	cmp r0, #0x0
	beq _02048BC2
	ldr r0, [r4, #0x28]
	bl FUN_020346CC
_02048BC2:
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	mov r1, #0x2
	bl FUN_0205F524
	cmp r0, #0x0
	bne _02048BD8
	ldr r0, [r4, #0x28]
	bl FUN_02034678
_02048BD8:
	ldr r0, [r4, #0x6c]
	cmp r0, #0x5
	blt _02048BE2
	bl GF_AssertFail
_02048BE2:
	ldr r0, [r4, #0x6c]
	ldr r1, _02048C28 ; =UNK_020F46E0
	lsl r0, r0, #0x3
	add r0, r1, r0
	str r0, [r4, #0x70]
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x70]
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	str r0, [r4, #0x18]
	ldr r1, [r4, #0x70]
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	add r0, #0x58
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1c
	bl FUN_0204A690
	ldr r0, [r4, #0x70]
	ldr r1, [r0, #0x0]
	lsl r0, r1, #0xc
	lsr r0, r0, #0x1c
	beq _02048C24
	lsr r1, r1, #0x18
	lsl r1, r1, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl FUN_0204A368
_02048C24:
	pop {r4, pc}
	nop
_02048C28: .word UNK_020F46E0

	thumb_func_start FUN_02048C2C
FUN_02048C2C: ; 0x02048C2C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x58]
	cmp r0, #0x0
	bne _02048C3A
	bl GF_AssertFail
_02048C3A:
	mov r0, #0x0
	str r0, [r4, #0x58]
	mov r0, #0x5
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x70]
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0x1c
	beq _02048C52
	add r0, r4, #0x0
	bl FUN_0204A390
_02048C52:
	mov r0, #0x0
	str r0, [r4, #0x70]
	pop {r4, pc}

	thumb_func_start FUN_02048C58
FUN_02048C58: ; 0x02048C58
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02048C7E
	ldr r0, [r4, #0x1c]
	mov r1, #0xb
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02028FA4
	add r4, #0x98
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r2, #0x0
	bl FUN_02028AD4
_02048C7E:
	pop {r4, pc}

	thumb_func_start FUN_02048C80
FUN_02048C80: ; 0x02048C80
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02048CAE
	ldr r0, [r4, #0xc]
	bl FUN_02034E30
	bl FUN_02034DD0
	ldr r0, [r0, #0x0]
	mov r1, #0xb
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02028FA4
	add r4, #0x98
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r2, #0x0
	bl FUN_02028AD4
_02048CAE:
	pop {r4, pc}

	thumb_func_start FUN_02048CB0
FUN_02048CB0: ; 0x02048CB0
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_0205532C
	add r6, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_02055320
	ldr r1, [r4, #0x1c]
	ldr r1, [r1, #0x0]
	str r1, [r5, #0x0]
	mov r1, #0x0
	mvn r1, r1
	str r1, [r5, #0x4]
	str r0, [r5, #0x8]
	str r6, [r5, #0xc]
	mov r0, #0x1
	str r0, [r5, #0x10]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02048CDC
FUN_02048CDC: ; 0x02048CDC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_020349E4
	cmp r0, #0x0
	beq _02048CFE
	ldr r1, [r4, #0x1c]
	ldr r0, [r1, #0x8]
	cmp r0, #0x7
	bne _02048CFE
	ldr r0, [r1, #0xc]
	cmp r0, #0x6
	bne _02048CFE
	mov r0, #0x1
	pop {r4, pc}
_02048CFE:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02048D04
FUN_02048D04: ; 0x02048D04
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02034E30
	bl FUN_02034DD0
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	ldr r0, [r5, #0x1c]
	ldr r0, [r0, #0x0]
	str r0, [r4, #0x0]
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0x4]
	mov r0, #0x8
	str r0, [r4, #0x8]
	mov r0, #0x2
	str r0, [r4, #0xc]
	mov r0, #0x1
	str r0, [r4, #0x10]
	pop {r3-r5, pc}

	thumb_func_start FUN_02048D34
FUN_02048D34: ; 0x02048D34
	push {r4-r6, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02048D56
	cmp r0, #0x1
	beq _02048D7A
	cmp r0, #0x2
	beq _02048D88
	b _02048D8C
_02048D56:
	ldr r1, [r5, #0x1c]
	add r0, r5, #0x0
	bl FUN_02048958
	add r0, r5, #0x0
	bl FUN_02048B90
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020489FC
	add r0, r5, #0x0
	bl FUN_02048AE4
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02048D8C
_02048D7A:
	add r0, r6, #0x0
	bl FUN_0204B0E8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02048D8C
_02048D88:
	mov r0, #0x1
	pop {r4-r6, pc}
_02048D8C:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02048D90
FUN_02048D90: ; 0x02048D90
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	str r1, [r4, #0x6c]
	bl RunPokemonCenterScriptsInNewContext
	ldr r1, _02048DA8 ; =FUN_02048D34
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_020463CC
	pop {r4, pc}
	.balign 4
_02048DA8: .word FUN_02048D34

	thumb_func_start FUN_02048DAC
FUN_02048DAC: ; 0x02048DAC
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02046530
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x4
	bhi _02048EC2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02048DD8: ; jump table (using 16-bit offset)
	.short _02048DE2 - _02048DD8 - 2; case 0
	.short _02048E10 - _02048DD8 - 2; case 1
	.short _02048EA4 - _02048DD8 - 2; case 2
	.short _02048EB0 - _02048DD8 - 2; case 3
	.short _02048EB4 - _02048DD8 - 2; case 4
_02048DE2:
	ldr r0, [r4, #0xc]
	bl FUN_02025B94
	add r0, r6, #0x0
	mov r1, #0x2
	bl FUN_0205F2D4
	add r7, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_020289A4
	add r1, r7, #0x0
	bl FUN_02028A20
	cmp r0, #0x0
	beq _02048E10
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02037944
	mov r0, #0x4
	str r0, [r5, #0x0]
	b _02048EC2
_02048E10:
	add r0, r6, #0x0
	mov r1, #0x2
	bl FUN_0205F2D4
	add r7, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_020289A4
	add r1, r7, #0x0
	bl FUN_020289B0
	add r1, r4, #0x0
	add r1, #0x98
	str r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_0205F174
	cmp r0, #0x0
	beq _02048E78
	ldr r0, [r4, #0xc]
	bl FUN_02034E30
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02048CDC
	cmp r0, #0x0
	beq _02048E4E
	add r0, r4, #0x0
	bl FUN_02048D04
_02048E4E:
	add r0, r6, #0x0
	bl FUN_0205F164
	add r0, r7, #0x0
	bl FUN_02034DD0
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02048958
	add r0, r4, #0x0
	bl FUN_02048B90
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020489FC
	add r0, r4, #0x0
	bl FUN_02048AE4
	b _02048E92
_02048E78:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02048958
	add r0, r4, #0x0
	bl FUN_02048B90
	add r0, r4, #0x0
	bl FUN_0204B0F8
	add r0, r4, #0x0
	bl FUN_02048B50
_02048E92:
	add r0, r4, #0x0
	bl FUN_02048C58
	add r0, r4, #0x0
	bl FUN_02063808
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _02048EC2
_02048EA4:
	add r0, r7, #0x0
	bl FUN_0204B0E8
	mov r0, #0x3
	str r0, [r5, #0x0]
	b _02048EC2
_02048EB0:
	mov r0, #0x1
	pop {r3-r7, pc}
_02048EB4:
	add r0, r4, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	bne _02048EC2
	mov r0, #0x1
	str r0, [r5, #0x0]
_02048EC2:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02048EC8
FUN_02048EC8: ; 0x02048EC8
	ldr r3, _02048ED4 ; =FUN_020463CC
	mov r2, #0x0
	str r2, [r0, #0x6c]
	ldr r1, _02048ED8 ; =FUN_02048DAC
	bx r3
	nop
_02048ED4: .word FUN_020463CC
_02048ED8: .word FUN_02048DAC

	thumb_func_start FUN_02048EDC
FUN_02048EDC: ; 0x02048EDC
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0204652C
	add r6, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	bl FUN_02046530
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x5
	bhi _02048FC4
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02048F10: ; jump table (using 16-bit offset)
	.short _02048F1C - _02048F10 - 2; case 0
	.short _02048F54 - _02048F10 - 2; case 1
	.short _02048F7E - _02048F10 - 2; case 2
	.short _02048F9A - _02048F10 - 2; case 3
	.short _02048FAE - _02048F10 - 2; case 4
	.short _02048FBA - _02048F10 - 2; case 5
_02048F1C:
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3A0
	ldr r0, [r4, #0xc]
	bl FUN_02025B94
	ldr r0, [sp, #0x0]
	mov r1, #0x2
	bl FUN_0205F2D4
	add r6, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_020289A4
	add r1, r6, #0x0
	bl FUN_020289B0
	add r4, #0x98
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _02048FC4
_02048F54:
	add r0, r4, #0x0
	add r1, r6, #0x4
	bl FUN_02048958
	add r0, r4, #0x0
	bl FUN_02048B90
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020489FC
	add r0, r4, #0x0
	bl FUN_02048AE4
	add r0, r4, #0x0
	bl FUN_02048C80
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _02048FC4
_02048F7E:
	add r0, r4, #0x0
	bl FUN_020520AC
	str r0, [r4, #0x78]
	bl FUN_02052EE8
	str r0, [r4, #0x7c]
	add r0, r7, #0x0
	bl FUN_0204AF84
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _02048FC4
_02048F9A:
	mov r1, #0x0
	str r1, [r6, #0x0]
	add r0, r4, #0x0
	add r2, r6, #0x0
	bl MOD05_021E7750
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _02048FC4
_02048FAE:
	ldr r1, [r6, #0x0]
	cmp r1, #0x0
	beq _02048FC4
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _02048FC4
_02048FBA:
	add r0, r6, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r7, pc}
_02048FC4:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02048FC8
FUN_02048FC8: ; 0x02048FC8
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034998
	cmp r0, #0x0
	bne _02049000
	add r0, r4, #0x0
	bl FUN_02048CDC
	cmp r0, #0x0
	beq _02048FF8
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02048D04
	add r0, r5, #0x0
	bl FUN_0205F154
	b _02049000
_02048FF8:
	add r0, r4, #0x0
	bl FUN_02048EC8
	pop {r3-r5, pc}
_02049000:
	mov r0, #0xb
	mov r1, #0x18
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	mov r1, #0x0
	ldr r0, _02049030 ; =0x000001D2
	str r1, [r2, #0x0]
	str r0, [r2, #0x4]
	sub r0, r1, #0x1
	str r0, [r2, #0x8]
	mov r0, #0x8
	str r0, [r2, #0xc]
	mov r0, #0xe
	str r0, [r2, #0x10]
	str r1, [r2, #0x14]
	mov r0, #0x2
	str r0, [r4, #0x6c]
	ldr r1, _02049034 ; =FUN_02048EDC
	add r0, r4, #0x0
	bl FUN_020463CC
	pop {r3-r5, pc}
	nop
_02049030: .word 0x000001D2
_02049034: .word FUN_02048EDC

	thumb_func_start FUN_02049038
FUN_02049038: ; 0x02049038
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x3
	bhi _020490B6
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0204905C: ; jump table (using 16-bit offset)
	.short _02049064 - _0204905C - 2; case 0
	.short _02049080 - _0204905C - 2; case 1
	.short _02049090 - _0204905C - 2; case 2
	.short _020490AE - _0204905C - 2; case 3
_02049064:
	ldr r0, _020490BC ; =0x00000603
	bl FUN_020054C8
	ldr r1, [r4, #0x4]
	add r0, r6, #0x0
	bl FUN_0204AD60
	add r0, r5, #0x0
	bl FUN_0204B090
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020490B6
_02049080:
	add r0, r5, #0x0
	add r1, r4, #0x4
	bl FUN_02049160
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020490B6
_02049090:
	bl FUN_02005404
	cmp r0, #0x0
	bne _020490B6
	ldr r1, [r4, #0x4]
	add r0, r6, #0x0
	bl FUN_0204AD8C
	add r0, r5, #0x0
	bl FUN_0204B0E8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020490B6
_020490AE:
	bl FreeToHeap
	mov r0, #0x1
	pop {r4-r6, pc}
_020490B6:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_020490BC: .word 0x00000603

	thumb_func_start FUN_020490C0
FUN_020490C0: ; 0x020490C0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0xb
	mov r1, #0x1c
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	ldmia r4!, {r0-r1}
	add r3, r2, #0x4
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r4, #0x0]
	ldr r1, _020490EC ; =FUN_02049038
	str r0, [r3, #0x0]
	add r0, r5, #0x0
	bl FUN_0204640C
	pop {r3-r5, pc}
	.balign 4
_020490EC: .word FUN_02049038

	thumb_func_start FUN_020490F0
FUN_020490F0: ; 0x020490F0
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02049112
	cmp r0, #0x1
	beq _02049126
	cmp r0, #0x2
	beq _0204914C
	b _0204915C
_02049112:
	add r0, r5, #0x0
	bl FUN_02048B34
	add r0, r5, #0x0
	bl FUN_02048C2C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204915C
_02049126:
	add r0, r5, #0x0
	add r1, r4, #0x4
	bl FUN_02048958
	add r0, r5, #0x0
	bl FUN_02048B90
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020489FC
	add r5, #0x90
	ldr r0, [r5, #0x0]
	bl FUN_0205DD40
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204915C
_0204914C:
	add r0, r5, #0x0
	bl FUN_02048AE4
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0204915C:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02049160
FUN_02049160: ; 0x02049160
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	mov r0, #0xb
	mov r1, #0x18
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0203739C
	cmp r0, #0x0
	beq _02049186
	bl GF_AssertFail
	pop {r3-r7, pc}
_02049186:
	mov r0, #0x0
	str r0, [r4, #0x0]
	ldmia r5!, {r0-r1}
	add r2, r4, #0x4
	stmia r2!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r5, #0x0]
	ldr r1, _020491A4 ; =FUN_020490F0
	str r0, [r2, #0x0]
	add r0, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r3-r7, pc}
	.balign 4
_020491A4: .word FUN_020490F0

	thumb_func_start FUN_020491A8
FUN_020491A8: ; 0x020491A8
	push {lr}
	sub sp, #0x14
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x18]
	str r2, [sp, #0x4]
	str r1, [sp, #0xc]
	ldr r1, [sp, #0x1c]
	str r3, [sp, #0x8]
	str r1, [sp, #0x10]
	add r1, sp, #0x0
	bl FUN_02049160
	add sp, #0x14
	pop {pc}

	thumb_func_start FUN_020491C4
FUN_020491C4: ; 0x020491C4
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x3
	bhi _0204923C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020491E8: ; jump table (using 16-bit offset)
	.short _020491F0 - _020491E8 - 2; case 0
	.short _02049206 - _020491E8 - 2; case 1
	.short _02049216 - _020491E8 - 2; case 2
	.short _02049234 - _020491E8 - 2; case 3
_020491F0:
	ldr r1, [r4, #0x4]
	add r0, r6, #0x0
	bl FUN_0204AD60
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204923C
_02049206:
	add r0, r5, #0x0
	add r1, r4, #0x4
	bl FUN_02049160
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204923C
_02049216:
	bl FUN_02005404
	cmp r0, #0x0
	bne _0204923C
	ldr r1, [r4, #0x4]
	add r0, r6, #0x0
	bl FUN_0204AD8C
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204923C
_02049234:
	bl FreeToHeap
	mov r0, #0x1
	pop {r4-r6, pc}
_0204923C:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02049240
FUN_02049240: ; 0x02049240
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0xb
	mov r1, #0x18
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	str r5, [r2, #0x4]
	str r4, [r2, #0x8]
	ldr r0, [sp, #0x18]
	str r6, [r2, #0xc]
	str r0, [r2, #0x10]
	ldr r0, [sp, #0x1c]
	ldr r1, _02049270 ; =FUN_020491C4
	str r0, [r2, #0x14]
	add r0, r7, #0x0
	bl FUN_0204640C
	pop {r3-r7, pc}
	.balign 4
_02049270: .word FUN_020491C4

	thumb_func_start FUN_02049274
FUN_02049274: ; 0x02049274
	push {r4-r5, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	ldr r0, [sp, #0x20]
	str r1, [sp, #0x0]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x24]
	mov r1, #0x20
	str r0, [sp, #0x10]
	mov r0, #0xb
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	add r3, r2, #0x0
	add r5, sp, #0x0
	str r0, [r2, #0x4]
	ldmia r5!, {r0-r1}
	add r3, #0x8
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	ldr r1, _020492B8 ; =FUN_02049304
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	bl FUN_020463CC
	add sp, #0x14
	pop {r4-r5, pc}
	nop
_020492B8: .word FUN_02049304

	thumb_func_start FUN_020492BC
FUN_020492BC: ; 0x020492BC
	push {r4-r5, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	ldr r0, [sp, #0x20]
	str r1, [sp, #0x0]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x24]
	mov r1, #0x20
	str r0, [sp, #0x10]
	mov r0, #0xb
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	add r3, r2, #0x0
	add r5, sp, #0x0
	str r0, [r2, #0x4]
	ldmia r5!, {r0-r1}
	add r3, #0x8
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	ldr r1, _02049300 ; =FUN_02049304
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	bl FUN_020463EC
	add sp, #0x14
	pop {r4-r5, pc}
	nop
_02049300: .word FUN_02049304

	thumb_func_start FUN_02049304
FUN_02049304: ; 0x02049304
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r5, r4, #0x0
	ldr r1, [r4, #0x0]
	add r5, #0x8
	cmp r1, #0x3
	bhi _02049390
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0204932C: ; jump table (using 16-bit offset)
	.short _02049334 - _0204932C - 2; case 0
	.short _0204934A - _0204932C - 2; case 1
	.short _02049364 - _0204932C - 2; case 2
	.short _02049388 - _0204932C - 2; case 3
_02049334:
	ldr r1, [r5, #0x0]
	add r0, r6, #0x0
	bl FUN_0204AD60
	add r0, r7, #0x0
	bl FUN_02049394
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049390
_0204934A:
	ldr r0, [r6, #0x38]
	mov r1, #0x0
	bl FUN_020553A8
	add r1, r4, #0x0
	add r0, r7, #0x0
	add r1, #0x8
	bl FUN_02049160
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049390
_02049364:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02049390
	ldr r1, [r5, #0x0]
	add r0, r6, #0x0
	bl FUN_0204AD8C
	add r0, r6, #0x0
	bl FUN_020637A8
	add r0, r7, #0x0
	bl FUN_020493D0
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049390
_02049388:
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r7, pc}
_02049390:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02049394
FUN_02049394: ; 0x02049394
	ldr r3, _0204939C ; =FUN_0204640C
	ldr r1, _020493A0 ; =FUN_020493A4
	mov r2, #0x0
	bx r3
	.balign 4
_0204939C: .word FUN_0204640C
_020493A0: .word FUN_020493A4

	thumb_func_start FUN_020493A4
FUN_020493A4: ; 0x020493A4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020493BA
	cmp r0, #0x1
	beq _020493C8
	b _020493CC
_020493BA:
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020493CC
_020493C8:
	mov r0, #0x1
	pop {r3-r5, pc}
_020493CC:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_020493D0
FUN_020493D0: ; 0x020493D0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0204652C
	add r2, r0, #0x0
	ldr r1, _020493E4 ; =FUN_020493E8
	add r0, r4, #0x0
	bl FUN_0204640C
	pop {r4, pc}
	.balign 4
_020493E4: .word FUN_020493E8

	thumb_func_start FUN_020493E8
FUN_020493E8: ; 0x020493E8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02046528
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02049408
	cmp r1, #0x1
	beq _02049416
	cmp r1, #0x2
	beq _02049428
	b _0204942C
_02049408:
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204942C
_02049416:
	bl MOD05_021E331C
	add r0, r5, #0x0
	bl FUN_02049430
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204942C
_02049428:
	mov r0, #0x1
	pop {r3-r5, pc}
_0204942C:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02049430
FUN_02049430: ; 0x02049430
	push {r4-r6, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0203739C
	cmp r0, #0x0
	bne _02049452
	bl GF_AssertFail
	pop {r4-r6, pc}
_02049452:
	ldr r0, [r5, #0x38]
	bl FUN_020553E8
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MOD06_022483BC
	str r0, [r4, #0x4]
	ldr r1, _02049470 ; =FUN_02049474
	add r0, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r4-r6, pc}
	nop
_02049470: .word FUN_02049474

	thumb_func_start FUN_02049474
FUN_02049474: ; 0x02049474
	push {r4, lr}
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	bl MOD06_022483E0
	cmp r0, #0x1
	bne _02049490
	ldr r0, [r4, #0x4]
	bl MOD06_022483EC
	mov r0, #0x1
	pop {r4, pc}
_02049490:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02049494
FUN_02049494: ; 0x02049494
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0xb
	mov r1, #0x20
	add r4, r2, #0x0
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	str r4, [r2, #0x4]
	str r0, [r2, #0x8]
	add r3, r2, #0x0
	ldmia r5!, {r0-r1}
	add r3, #0xc
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	ldr r1, _020494C8 ; =FUN_020494CC
	str r0, [r3, #0x0]
	add r0, r6, #0x0
	bl FUN_020463EC
	pop {r4-r6, pc}
	.balign 4
_020494C8: .word FUN_020494CC

	thumb_func_start FUN_020494CC
FUN_020494CC: ; 0x020494CC
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r6, r4, #0x0
	ldr r1, [r4, #0x0]
	add r6, #0xc
	cmp r1, #0x3
	bhi _02049570
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020494F4: ; jump table (using 16-bit offset)
	.short _020494FC - _020494F4 - 2; case 0
	.short _02049512 - _020494F4 - 2; case 1
	.short _0204952C - _020494F4 - 2; case 2
	.short _02049568 - _020494F4 - 2; case 3
_020494FC:
	ldr r1, [r6, #0x0]
	add r0, r5, #0x0
	bl FUN_0204AD60
	add r0, r7, #0x0
	bl FUN_02049574
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049570
_02049512:
	ldr r0, [r5, #0x38]
	mov r1, #0x0
	bl FUN_020553A8
	add r1, r4, #0x0
	add r0, r7, #0x0
	add r1, #0xc
	bl FUN_02049160
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049570
_0204952C:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02049570
	ldr r1, [r6, #0x0]
	add r0, r5, #0x0
	bl FUN_0204AD8C
	ldr r0, [r4, #0x4]
	cmp r0, #0x2
	bne _0204954A
	add r0, r5, #0x0
	bl FUN_020637C4
	b _0204955A
_0204954A:
	cmp r0, #0x1
	bhi _02049556
	add r0, r5, #0x0
	bl FUN_020637E0
	b _0204955A
_02049556:
	bl GF_AssertFail
_0204955A:
	add r0, r7, #0x0
	bl FUN_020495B0
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049570
_02049568:
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r7, pc}
_02049570:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02049574
FUN_02049574: ; 0x02049574
	ldr r3, _0204957C ; =FUN_0204640C
	ldr r1, _02049580 ; =FUN_02049584
	mov r2, #0x0
	bx r3
	.balign 4
_0204957C: .word FUN_0204640C
_02049580: .word FUN_02049584

	thumb_func_start FUN_02049584
FUN_02049584: ; 0x02049584
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0204959A
	cmp r0, #0x1
	beq _020495A8
	b _020495AC
_0204959A:
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020495AC
_020495A8:
	mov r0, #0x1
	pop {r3-r5, pc}
_020495AC:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_020495B0
FUN_020495B0: ; 0x020495B0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0204652C
	add r2, r0, #0x0
	ldr r1, _020495C4 ; =FUN_020495C8
	add r0, r4, #0x0
	bl FUN_0204640C
	pop {r4, pc}
	.balign 4
_020495C4: .word FUN_020495C8

	thumb_func_start FUN_020495C8
FUN_020495C8: ; 0x020495C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020495F0
	cmp r0, #0x1
	beq _020495FE
	cmp r0, #0x2
	beq _02049612
	b _02049616
_020495F0:
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049616
_020495FE:
	add r0, r6, #0x0
	bl MOD05_021E331C
	add r0, r5, #0x0
	bl FUN_0204961C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049616
_02049612:
	mov r0, #0x1
	pop {r4-r6, pc}
_02049616:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204961C
FUN_0204961C: ; 0x0204961C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0203739C
	cmp r0, #0x0
	bne _0204963E
	bl GF_AssertFail
	pop {r4-r6, pc}
_0204963E:
	ldr r2, [r6, #0x4]
	add r0, r4, #0x0
	mov r1, #0x4
	bl MOD06_0224C8C8
	add r2, r0, #0x0
	ldr r1, _02049654 ; =MOD06_0224C8E8
	add r0, r5, #0x0
	bl FUN_0204640C
	pop {r4-r6, pc}
	.balign 4
_02049654: .word MOD06_0224C8E8

	thumb_func_start FUN_02049658
FUN_02049658: ; 0x02049658
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r5, r4, #0x0
	ldr r1, [r4, #0x0]
	add r5, #0x8
	cmp r1, #0x6
	bhi _02049712
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02049680: ; jump table (using 16-bit offset)
	.short _0204968E - _02049680 - 2; case 0
	.short _020496A0 - _02049680 - 2; case 1
	.short _020496BC - _02049680 - 2; case 2
	.short _020496CC - _02049680 - 2; case 3
	.short _020496EA - _02049680 - 2; case 4
	.short _020496FE - _02049680 - 2; case 5
	.short _0204970A - _02049680 - 2; case 6
_0204968E:
	add r0, r7, #0x0
	mov r1, #0x1
	add r2, r4, #0x4
	bl MOD05_021E7750
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049712
_020496A0:
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _02049712
	ldr r1, [r5, #0x0]
	add r0, r7, #0x0
	bl FUN_0204AD60
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049712
_020496BC:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02049160
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049712
_020496CC:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02049712
	ldr r1, [r5, #0x0]
	add r0, r7, #0x0
	bl FUN_0204AD8C
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049712
_020496EA:
	mov r1, #0x0
	str r1, [r4, #0x4]
	add r0, r7, #0x0
	add r2, r4, #0x4
	bl MOD05_021E7750
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049712
_020496FE:
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _02049712
	add r0, r1, #0x1
	str r0, [r4, #0x0]
	b _02049712
_0204970A:
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r7, pc}
_02049712:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02049718
FUN_02049718: ; 0x02049718
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0xb
	mov r1, #0x1c
	add r6, r2, #0x0
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0x1c
	add r7, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	mov r1, #0x0
	add r2, r7, #0x0
	str r4, [sp, #0x0]
	str r6, [sp, #0x4]
	add r3, sp, #0x0
	str r1, [sp, #0x8]
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldmia r3!, {r0-r1}
	add r2, #0x8
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	ldr r1, _02049768 ; =FUN_02049658
	str r0, [r2, #0x0]
	add r0, r5, #0x0
	add r2, r7, #0x0
	bl FUN_020463CC
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02049768: .word FUN_02049658

	thumb_func_start FUN_0204976C
FUN_0204976C: ; 0x0204976C
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_02034E30
	bl FUN_02034DD0
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x40
	bl AllocFromHeapAtEnd
	add r5, r0, #0x0
	mov r1, #0x0
	str r1, [r5, #0x0]
	str r1, [r5, #0x4]
	ldr r0, [r6, #0x6c]
	cmp r0, #0x1
	bne _020497A4
	ldr r0, [r4, #0x0]
	str r0, [r5, #0x8]
	sub r0, r1, #0x1
	str r0, [r5, #0xc]
	ldr r0, [r4, #0x8]
	str r0, [r5, #0x10]
	ldr r0, [r4, #0xc]
	str r0, [r5, #0x14]
	b _02049820
_020497A4:
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_02048CB0
	mov r0, #0x2
	str r0, [r5, #0x8]
	sub r0, r0, #0x3
	str r0, [r5, #0xc]
	ldr r1, [r4, #0x8]
	asr r0, r1, #0x4
	lsr r0, r0, #0x1b
	add r0, r1, r0
	asr r0, r0, #0x5
	ldr r1, [r4, #0xc]
	sub r6, r0, #0x1
	asr r0, r1, #0x4
	lsr r0, r0, #0x1b
	add r0, r1, r0
	asr r0, r0, #0x5
	sub r4, r0, #0x6
	cmp r6, #0x0
	bge _020497D4
	bl GF_AssertFail
_020497D4:
	cmp r4, #0x0
	bge _020497DC
	bl GF_AssertFail
_020497DC:
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	bne _020497EE
	mov r0, #0x8
	b _020497F0
_020497EE:
	mov r0, #0x17
_020497F0:
	lsr r3, r4, #0x1f
	lsl r2, r4, #0x1f
	sub r2, r2, r3
	mov r1, #0x1f
	ror r2, r1
	add r1, r3, r2
	bne _02049802
	mov r1, #0x8
	b _02049804
_02049802:
	mov r1, #0x17
_02049804:
	lsr r2, r6, #0x1f
	add r2, r6, r2
	asr r2, r2, #0x1
	add r6, r2, #0x1
	lsr r2, r4, #0x1f
	add r2, r4, r2
	asr r2, r2, #0x1
	add r3, r2, #0x3
	lsl r2, r6, #0x5
	add r0, r0, r2
	str r0, [r5, #0x10]
	lsl r0, r3, #0x5
	add r0, r1, r0
	str r0, [r5, #0x14]
_02049820:
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02049824
FUN_02049824: ; 0x02049824
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0204976C
	add r4, r0, #0x0
	beq _02049840
	add r0, r5, #0x0
	bl FUN_02049BE8
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020463CC
_02049840:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02049844
FUN_02049844: ; 0x02049844
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0xc
	bhi _0204992C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0204986A: ; jump table (using 16-bit offset)
	.short _02049884 - _0204986A - 2; case 0
	.short _020498DC - _0204986A - 2; case 1
	.short _02049918 - _0204986A - 2; case 2
	.short _0204995E - _0204986A - 2; case 3
	.short _020499A2 - _0204986A - 2; case 4
	.short _020499D0 - _0204986A - 2; case 5
	.short _020499E2 - _0204986A - 2; case 6
	.short _020499F2 - _0204986A - 2; case 7
	.short _02049A06 - _0204986A - 2; case 8
	.short _02049A14 - _0204986A - 2; case 9
	.short _02049A42 - _0204986A - 2; case 10
	.short _02049A64 - _0204986A - 2; case 11
	.short _02049A96 - _0204986A - 2; case 12
_02049884:
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xcf
	mov r3, #0xb
	bl NewMsgDataFromNarc
	add r6, r0, #0x0
	mov r1, #0x7c
	bl NewString_ReadMsgData
	str r0, [r4, #0x34]
	add r0, r6, #0x0
	bl DestroyMsgData
	add r1, r4, #0x0
	ldr r0, [r5, #0x8]
	add r1, #0x24
	mov r2, #0x3
	bl FUN_020545B8
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x24
	bl FUN_02054608
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r2, r0, #0x0
	add r0, r4, #0x0
	ldr r1, [r4, #0x34]
	add r0, #0x24
	mov r3, #0x1
	bl FUN_02054658
	add r1, r4, #0x0
	add r1, #0x38
	strb r0, [r1, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _02049AB2
_020498DC:
	add r0, r4, #0x0
	add r0, #0x38
	ldrb r0, [r0, #0x0]
	bl FUN_020546C8
	cmp r0, #0x1
	bne _0204992C
	ldr r0, [r4, #0x34]
	bl String_dtor
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r3, #0xb
	str r3, [sp, #0x4]
	ldr r0, [r5, #0x8]
	ldr r2, _02049AB8 ; =0x000003D9
	mov r1, #0x3
	bl FUN_0200CB00
	mov r3, #0xb
	str r3, [sp, #0x0]
	ldr r0, [r5, #0x8]
	ldr r1, _02049ABC ; =UNK_020F46D8
	ldr r2, _02049AB8 ; =0x000003D9
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x3c]
	mov r0, #0x2
	str r0, [r4, #0x0]
	b _02049AB2
_02049918:
	ldr r0, [r4, #0x3c]
	mov r1, #0xb
	bl FUN_020021AC
	cmp r0, #0x0
	beq _0204992E
	mov r1, #0x1
	mvn r1, r1
	cmp r0, r1
	beq _02049946
_0204992C:
	b _02049AB2
_0204992E:
	add r0, r4, #0x0
	add r0, #0x24
	mov r1, #0x0
	bl FUN_0200D0E0
	add r0, r4, #0x0
	add r0, #0x24
	bl FUN_02019178
	mov r0, #0x3
	str r0, [r4, #0x0]
	b _02049AB2
_02049946:
	add r0, r4, #0x0
	add r0, #0x24
	mov r1, #0x0
	bl FUN_0200D0E0
	add r0, r4, #0x0
	add r0, #0x24
	bl FUN_02019178
	mov r0, #0x5
	str r0, [r4, #0x0]
	b _02049AB2
_0204995E:
	ldr r0, [r5, #0xc]
	bl FUN_0202280C
	cmp r0, #0x0
	beq _02049976
	mov r2, #0x0
	ldr r1, _02049AC0 ; =0x000007F2
	add r0, r6, #0x0
	add r3, r2, #0x0
	bl FUN_02038CD8
	b _0204999C
_02049976:
	ldr r0, [r5, #0xc]
	bl FUN_02025BE8
	add r0, r5, #0x0
	mov r1, #0xb
	mov r2, #0x3
	bl MOD05_021E8588
	str r0, [r4, #0x20]
	bl MOD05_021E84F4
	add r3, r4, #0x0
	mov r2, #0x0
	ldr r1, _02049AC4 ; =0x000007D5
	add r0, r6, #0x0
	add r3, #0x1c
	strh r2, [r4, #0x1c]
	bl FUN_02038CD8
_0204999C:
	mov r0, #0x4
	str r0, [r4, #0x0]
	b _02049AB2
_020499A2:
	ldr r0, [r5, #0xc]
	bl FUN_0202280C
	cmp r0, #0x0
	beq _020499B2
	mov r0, #0x5
	str r0, [r4, #0x0]
	b _02049AB2
_020499B2:
	ldr r0, [r4, #0x20]
	bl MOD05_021E856C
	ldr r0, [r4, #0x20]
	bl MOD05_021E85E4
	ldrh r0, [r4, #0x1c]
	cmp r0, #0x0
	bne _020499CA
	mov r0, #0x5
	str r0, [r4, #0x0]
	b _02049AB2
_020499CA:
	mov r0, #0x6
	str r0, [r4, #0x0]
	b _02049AB2
_020499D0:
	ldr r0, [r5, #0x34]
	bl FUN_020587B0
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_020499E2:
	mov r0, #0x0
	mov r1, #0x1e
	bl FUN_020053CC
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049AB2
_020499F2:
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_02049C0C
	cmp r0, #0x0
	beq _02049AB2
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049AB2
_02049A06:
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049AB2
_02049A14:
	mov r0, #0x1
	str r0, [r5, #0x6c]
	ldr r0, _02049AC8 ; =SDK_OVERLAY_MODULE_18_ID
	mov r1, #0x2
	bl HandleLoadOverlay
	add r0, r5, #0x0
	bl FUN_0204FC5C
	ldr r0, [r4, #0x14]
	mov r2, #0x1
	str r0, [sp, #0x0]
	str r2, [sp, #0x4]
	ldr r1, [r4, #0x8]
	ldr r3, [r4, #0x10]
	add r0, r6, #0x0
	sub r2, r2, #0x2
	bl FUN_020491A8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049AB2
_02049A42:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02049AB2
	mov r0, #0x0
	bl FUN_0200415C
	add r0, r5, #0x0
	bl FUN_0204AB44
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049AB2
_02049A64:
	add r0, r6, #0x0
	mov r1, #0x1
	bl FUN_02049C0C
	cmp r0, #0x0
	beq _02049AB2
	bl FUN_0204FCA0
	add r0, r5, #0x0
	bl MOD18_02244824
	mov r1, #0x0
	str r0, [r5, #0x68]
	mov r0, #0x2
	add r2, r1, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1e
	sub r2, #0x10
	mov r3, #0x19
	bl FUN_0200A208
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049AB2
_02049A96:
	mov r0, #0x2
	bl FUN_0200A344
	cmp r0, #0x0
	beq _02049AB2
	mov r0, #0x1
	bl MOD18_02247970
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02049AB2:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_02049AB8: .word 0x000003D9
_02049ABC: .word UNK_020F46D8
_02049AC0: .word 0x000007F2
_02049AC4: .word 0x000007D5
_02049AC8: .word SDK_OVERLAY_MODULE_18_ID

	thumb_func_start FUN_02049ACC
FUN_02049ACC: ; 0x02049ACC
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x7
	bhi _02049BDC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02049AF2: ; jump table (using 16-bit offset)
	.short _02049B02 - _02049AF2 - 2; case 0
	.short _02049B2C - _02049AF2 - 2; case 1
	.short _02049B54 - _02049AF2 - 2; case 2
	.short _02049B68 - _02049AF2 - 2; case 3
	.short _02049B76 - _02049AF2 - 2; case 4
	.short _02049B9C - _02049AF2 - 2; case 5
	.short _02049BBE - _02049AF2 - 2; case 6
	.short _02049BD2 - _02049AF2 - 2; case 7
_02049B02:
	mov r0, #0x0
	bl MOD18_02247970
	bl FUN_0204FCD8
	ldr r0, [r5, #0x68]
	bl MOD18_0224484C
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r0, #0x1e
	add r1, r0, #0x0
	sub r1, #0x2e
	mov r2, #0x0
	mov r3, #0x1
	bl FUN_0200A208
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049BDC
_02049B2C:
	mov r0, #0x2
	bl FUN_0200A344
	cmp r0, #0x0
	beq _02049BDC
	ldr r0, [r5, #0x68]
	cmp r0, #0x0
	bne _02049BDC
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02049BDC
	mov r0, #0x0
	mov r1, #0x1e
	bl FUN_020053CC
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049BDC
_02049B54:
	add r0, r6, #0x0
	mov r1, #0x2
	bl FUN_02049C0C
	cmp r0, #0x0
	beq _02049BDC
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049BDC
_02049B68:
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049BDC
_02049B76:
	mov r0, #0x0
	str r0, [r5, #0x6c]
	ldr r0, _02049BE4 ; =SDK_OVERLAY_MODULE_18_ID
	bl UnloadOverlayByID
	ldr r0, [r4, #0x14]
	mov r2, #0x1
	str r0, [sp, #0x0]
	str r2, [sp, #0x4]
	ldr r1, [r4, #0x8]
	ldr r3, [r4, #0x10]
	add r0, r6, #0x0
	sub r2, r2, #0x2
	bl FUN_020491A8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049BDC
_02049B9C:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02049BDC
	mov r0, #0x0
	bl FUN_0200415C
	add r0, r5, #0x0
	bl FUN_0204AB44
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049BDC
_02049BBE:
	add r0, r6, #0x0
	mov r1, #0x3
	bl FUN_02049C0C
	cmp r0, #0x0
	beq _02049BDC
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049BDC
_02049BD2:
	bl FreeToHeap
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02049BDC:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_02049BE4: .word SDK_OVERLAY_MODULE_18_ID

	thumb_func_start FUN_02049BE8
FUN_02049BE8: ; 0x02049BE8
	push {r3, lr}
	ldr r0, [r0, #0x6c]
	cmp r0, #0x0
	bne _02049BF4
	ldr r0, _02049C04 ; =FUN_02049844
	pop {r3, pc}
_02049BF4:
	cmp r0, #0x1
	bne _02049BFC
	ldr r0, _02049C08 ; =FUN_02049ACC
	pop {r3, pc}
_02049BFC:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02049C04: .word FUN_02049844
_02049C08: .word FUN_02049ACC

	thumb_func_start FUN_02049C0C
FUN_02049C0C: ; 0x02049C0C
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r6, r1, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	mov r5, #0x0
	cmp r0, #0x0
	beq _02049C2E
	cmp r0, #0x1
	beq _02049C44
	b _02049C4E
_02049C2E:
	add r2, r4, #0x0
	str r5, [r4, #0x18]
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, #0x18
	bl FUN_02053C98
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02049C4E
_02049C44:
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _02049C4E
	str r5, [r4, #0x4]
	mov r5, #0x1
_02049C4E:
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02049C54
FUN_02049C54: ; 0x02049C54
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02049C76
	cmp r0, #0x1
	beq _02049C84
	cmp r0, #0x2
	beq _02049C9C
	b _02049CAC
_02049C76:
	add r0, r5, #0x0
	bl FUN_02048B34
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049CAC
_02049C84:
	add r0, r5, #0x0
	add r1, r4, #0x4
	bl FUN_02048958
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0203989C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049CAC
_02049C9C:
	add r0, r5, #0x0
	bl FUN_02048AE4
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_02049CAC:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02049CB0
FUN_02049CB0: ; 0x02049CB0
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	mov r0, #0xb
	mov r1, #0x18
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0203739C
	cmp r0, #0x0
	beq _02049CD6
	bl GF_AssertFail
	pop {r3-r7, pc}
_02049CD6:
	mov r0, #0x0
	str r0, [r4, #0x0]
	ldmia r5!, {r0-r1}
	add r2, r4, #0x4
	stmia r2!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r5, #0x0]
	ldr r1, _02049CF4 ; =FUN_02049C54
	str r0, [r2, #0x0]
	add r0, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r3-r7, pc}
	.balign 4
_02049CF4: .word FUN_02049C54

	thumb_func_start FUN_02049CF8
FUN_02049CF8: ; 0x02049CF8
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x5
	bhi _02049D98
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02049D24: ; jump table (using 16-bit offset)
	.short _02049D30 - _02049D24 - 2; case 0
	.short _02049D4C - _02049D24 - 2; case 1
	.short _02049D60 - _02049D24 - 2; case 2
	.short _02049D72 - _02049D24 - 2; case 3
	.short _02049D80 - _02049D24 - 2; case 4
	.short _02049D8E - _02049D24 - 2; case 5
_02049D30:
	ldr r1, [r5, #0x8]
	add r0, r7, #0x0
	mov r2, #0x0
	bl FUN_0204ACA8
	add r0, r7, #0x0
	mov r1, #0x1
	add r2, r5, #0x4
	bl MOD05_021E7750
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049D98
_02049D4C:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _02049D98
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049D98
_02049D60:
	add r5, #0x8
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02049160
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049D98
_02049D72:
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049D98
_02049D80:
	add r0, r6, #0x0
	bl FUN_0204B00C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049D98
_02049D8E:
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r7, pc}
_02049D98:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02049D9C
FUN_02049D9C: ; 0x02049D9C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02034E30
	bl FUN_02034DD0
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x1c
	bl AllocFromHeapAtEnd
	add r6, r0, #0x0
	mov r1, #0x0
	mov r2, #0x1c
	bl MI_CpuFill8
	add r2, r6, #0x0
	ldmia r4!, {r0-r1}
	add r2, #0x8
	stmia r2!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r2, #0x0]
	add r0, r5, #0x0
	bl FUN_020520F8
	ldr r0, [r5, #0x7c]
	bl FUN_02052FA4
	mov r0, #0x0
	str r0, [r5, #0x6c]
	ldr r1, _02049DF0 ; =FUN_02049CF8
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl FUN_020463CC
	mov r0, #0x0
	str r0, [r5, #0x78]
	pop {r4-r6, pc}
	nop
_02049DF0: .word FUN_02049CF8

	thumb_func_start FUN_02049DF4
FUN_02049DF4: ; 0x02049DF4
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x6
	bhi _02049E9E
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02049E20: ; jump table (using 16-bit offset)
	.short _02049E2E - _02049E20 - 2; case 0
	.short _02049E46 - _02049E20 - 2; case 1
	.short _02049E54 - _02049E20 - 2; case 2
	.short _02049E66 - _02049E20 - 2; case 3
	.short _02049E74 - _02049E20 - 2; case 4
	.short _02049E88 - _02049E20 - 2; case 5
	.short _02049E94 - _02049E20 - 2; case 6
_02049E2E:
	ldr r1, [r5, #0x8]
	add r0, r7, #0x0
	mov r2, #0x0
	bl FUN_0204ACA8
	add r0, r6, #0x0
	bl FUN_0204AFC8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049E9E
_02049E46:
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049E9E
_02049E54:
	add r5, #0x8
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02049160
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049E9E
_02049E66:
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049E9E
_02049E74:
	mov r1, #0x0
	str r1, [r5, #0x4]
	add r0, r7, #0x0
	add r2, r5, #0x4
	bl MOD05_021E7750
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049E9E
_02049E88:
	ldr r1, [r5, #0x4]
	cmp r1, #0x0
	beq _02049E9E
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049E9E
_02049E94:
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r7, pc}
_02049E9E:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02049EA4
FUN_02049EA4: ; 0x02049EA4
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02034E30
	bl FUN_02034DD0
	add r7, r0, #0x0
	mov r0, #0xb
	mov r1, #0x1c
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0x1c
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl FUN_02048CB0
	ldr r0, _02049F08 ; =0x000001D2
	str r0, [r4, #0x8]
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0xc]
	mov r0, #0x8
	str r0, [r4, #0x10]
	mov r0, #0xe
	str r0, [r4, #0x14]
	mov r0, #0x0
	str r0, [r4, #0x18]
	add r0, r5, #0x0
	bl FUN_020520AC
	str r0, [r5, #0x78]
	bl FUN_02052EE8
	str r0, [r5, #0x7c]
	mov r0, #0x2
	str r0, [r5, #0x6c]
	ldr r1, _02049F0C ; =FUN_02049DF4
	add r0, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r3-r7, pc}
	.balign 4
_02049F08: .word 0x000001D2
_02049F0C: .word FUN_02049DF4

	thumb_func_start FUN_02049F10
FUN_02049F10: ; 0x02049F10
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x3
	bhi _02049F8E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02049F34: ; jump table (using 16-bit offset)
	.short _02049F3C - _02049F34 - 2; case 0
	.short _02049F58 - _02049F34 - 2; case 1
	.short _02049F68 - _02049F34 - 2; case 2
	.short _02049F86 - _02049F34 - 2; case 3
_02049F3C:
	ldr r0, _02049F94 ; =0x00000603
	bl FUN_020054C8
	ldr r1, [r4, #0x4]
	add r0, r6, #0x0
	bl FUN_0204AD60
	add r0, r5, #0x0
	bl FUN_0204B090
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049F8E
_02049F58:
	add r0, r5, #0x0
	add r1, r4, #0x4
	bl FUN_02049160
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049F8E
_02049F68:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02049F8E
	ldr r1, [r4, #0x4]
	add r0, r6, #0x0
	bl FUN_0204AD8C
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02049F8E
_02049F86:
	bl FreeToHeap
	mov r0, #0x1
	pop {r4-r6, pc}
_02049F8E:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_02049F94: .word 0x00000603

	thumb_func_start FUN_02049F98
FUN_02049F98: ; 0x02049F98
	push {r3-r7, lr}
	sub sp, #0x18
	str r0, [sp, #0x0]
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02034E30
	bl FUN_02034DD0
	add r1, r4, #0x0
	bl FUN_02048CB0
	mov r0, #0x3
	str r0, [r4, #0x6c]
	mov r0, #0xb
	mov r1, #0x1c
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	ldr r0, [sp, #0x30]
	str r5, [sp, #0x4]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x34]
	str r6, [sp, #0x8]
	str r0, [sp, #0x14]
	mov r0, #0x0
	str r7, [sp, #0xc]
	add r4, sp, #0x4
	str r0, [r2, #0x0]
	ldmia r4!, {r0-r1}
	add r3, r2, #0x4
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r4, #0x0]
	ldr r1, _02049FF8 ; =FUN_02049F10
	str r0, [r3, #0x0]
	ldr r0, [sp, #0x0]
	bl FUN_0204640C
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_02049FF8: .word FUN_02049F10

	thumb_func_start FUN_02049FFC
FUN_02049FFC: ; 0x02049FFC
	push {r4, lr}
	bl FUN_02046528
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02034E30
	bl FUN_02034DD0
	add r1, r0, #0x0
	mov r0, #0x0
	str r0, [r4, #0x6c]
	ldr r0, [r4, #0x10]
	bl FUN_020490C0
	pop {r4, pc}
