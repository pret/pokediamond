	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_02064E90
sub_02064E90: ; 0x02064E90
	push {r3-r7, lr}
	sub sp, #0xa0
	str r0, [sp, #0x10]
	ldr r6, [sp, #0xb8]
	str r1, [sp, #0x14]
	str r2, [sp, #0x18]
	add r0, r6, #0x0
	str r3, [sp, #0x1c]
	ldr r5, [sp, #0xbc]
	bl ScriptEnvironment_GetSavePtr
	str r0, [sp, #0x20]
	bl Save_PlayerData_GetProfileAddr
	add r7, r0, #0x0
	ldr r0, [sp, #0x20]
	bl Save_GameStats_Get
	add r4, r0, #0x0
	ldr r0, [sp, #0x1c]
	strb r0, [r5, #0x5]
	add r0, r6, #0x0
	bl sub_02065078
	str r0, [sp, #0x24]
	add r0, r7, #0x0
	bl PlayerProfile_GetLanguage
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x18]
	mov r1, #GAME_VERSION
	bl sub_02065154
	add r0, r7, #0x0
	bl PlayerProfile_GetTrainerID_VisibleHalf
	str r0, [sp, #0x28]
	add r0, r7, #0x0
	bl PlayerProfile_GetTrainerGender
	str r0, [sp, #0x2c]
	add r0, r7, #0x0
	bl PlayerProfile_GetNamePtr
	str r0, [sp, #0x30]
	add r0, r7, #0x0
	bl PlayerProfile_GetMoney
	str r0, [sp, #0x34]
	ldr r0, [r6, #0xc]
	bl Save_Pokedex_Get
	bl Pokedex_CountSeenMons
	str r0, [sp, #0x38]
	ldr r0, [r6, #0xc]
	bl Save_Pokedex_Get
	bl Pokedex_GetSinnohDexFlag
	str r0, [sp, #0x3c]
	add r0, r4, #0x0
	bl GameStats_GetStat0
	ldr r1, [sp, #0x38]
	ldr r2, [sp, #0x30]
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x3c]
	ldr r3, [sp, #0x34]
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x28]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r5, [sp, #0xc]
	bl sub_02065178
	ldr r0, [sp, #0x20]
	bl Save_PlayerData_GetIGTAddr
	str r0, [sp, #0x40]
	add r0, r6, #0x0
	add r1, sp, #0x90
	add r2, sp, #0x74
	bl Script_SavRTC_x24toDateTime
	add r0, r6, #0x0
	add r1, sp, #0x80
	add r2, sp, #0x74
	bl Script_SavRTC_x2CtoDateTime
	ldr r0, [r6, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205ED0C
	add r1, sp, #0x74
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x14]
	lsl r0, r0, #0x18
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x40]
	str r5, [sp, #0x8]
	lsr r0, r0, #0x18
	add r2, sp, #0x90
	add r3, sp, #0x80
	bl sub_020651BC
	ldr r0, [r6, #0xc]
	bl sub_02029ABC
	str r0, [sp, #0x44]
	add r0, r4, #0x0
	mov r1, #0x20
	bl GameStats_GetCapped
	str r0, [sp, #0x48]
	add r0, r4, #0x0
	mov r1, #0x19
	bl GameStats_GetCapped
	str r0, [sp, #0x4c]
	add r0, r4, #0x0
	mov r1, #0x14
	bl GameStats_GetCapped
	str r0, [sp, #0x50]
	add r0, r4, #0x0
	mov r1, #0x18
	bl GameStats_GetCapped
	str r0, [sp, #0x54]
	add r0, r4, #0x0
	mov r1, #0x40
	bl GameStats_GetCapped
	str r0, [sp, #0x58]
	add r0, r4, #0x0
	mov r1, #0x13
	bl GameStats_GetCapped
	ldr r1, [sp, #0x58]
	add r1, r1, r0
	ldr r0, [sp, #0x54]
	add r1, r0, r1
	ldr r0, [sp, #0x50]
	add r1, r0, r1
	ldr r0, [sp, #0x4c]
	add r0, r0, r1
	str r0, [sp, #0x5c]
	add r0, r4, #0x0
	mov r1, #0x15
	bl GameStats_GetCapped
	str r0, [sp, #0x60]
	add r0, r4, #0x0
	mov r1, #0x1a
	bl GameStats_GetCapped
	str r0, [sp, #0x64]
	add r0, r4, #0x0
	mov r1, #0x16
	bl GameStats_GetCapped
	str r0, [sp, #0x68]
	add r0, r4, #0x0
	mov r1, #0x1b
	bl GameStats_GetCapped
	str r0, [sp, #0x6c]
	add r0, r4, #0x0
	mov r1, #0x13
	bl GameStats_GetCapped
	str r0, [sp, #0x70]
	add r0, r4, #0x0
	mov r1, #0x18
	bl GameStats_GetCapped
	add r4, r0, #0x0
	ldr r0, [sp, #0x44]
	bl sub_02029AC8
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x48]
	ldr r0, [sp, #0x5c]
	ldr r2, [sp, #0x60]
	add r0, r1, r0
	ldr r1, [sp, #0x64]
	ldr r3, [sp, #0x68]
	add r1, r2, r1
	ldr r2, [sp, #0x6c]
	str r5, [sp, #0x4]
	add r2, r3, r2
	ldr r3, [sp, #0x70]
	add r3, r3, r4
	bl sub_02065260
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl sub_020652AC
	mov r3, #0x0
	ldr r0, _0206504C ; =0x0000066C
	add r2, r3, #0x0
_02065034:
	ldrb r1, [r5, r2]
	add r2, r2, #0x1
	eor r3, r1
	cmp r2, r0
	blo _02065034
	ldr r0, _02065050 ; =0x00000668
	mov r1, #0x0
	strh r3, [r5, r0]
	add r0, r0, #0x2
	strh r1, [r5, r0]
	add sp, #0xa0
	pop {r3-r7, pc}
	.balign 4
_0206504C: .word 0x0000066C
_02065050: .word 0x00000668

	thumb_func_start sub_02065054
sub_02065054: ; 0x02065054
	push {r4, lr}
	ldr r1, _0206506C ; =0x0000066C
	bl AllocFromHeap
	ldr r2, _0206506C ; =0x0000066C
	mov r1, #0x0
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_0206506C: .word 0x0000066C

	thumb_func_start sub_02065070
sub_02065070: ; 0x02065070
	ldr r3, _02065074 ; =FreeToHeap
	bx r3
	.balign 4
_02065074: .word FreeToHeap

	thumb_func_start sub_02065078
sub_02065078: ; 0x02065078
	push {r3-r7, lr}
	bl ScriptEnvironment_GetSavePtr
	add r7, r0, #0x0
	bl Save_GameStats_Get
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl SaveArray_Flags_Get
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl sub_02026CB4
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r4, #0x0
	bl sub_0205ED0C
	cmp r0, #0x0
	beq _020650A8
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_020650A8:
	add r0, r7, #0x0
	bl Save_Pokedex_Get
	bl Pokedex_HasCompletedNationalDex
	cmp r0, #0x0
	beq _020650BC
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_020650BC:
	add r0, r6, #0x0
	mov r1, #0x35
	bl GameStats_GetCapped
	cmp r0, #0x64
	bhs _020650F8
	add r0, r6, #0x0
	mov r1, #0x37
	bl GameStats_GetCapped
	cmp r0, #0x64
	bhs _020650F8
	add r0, r6, #0x0
	mov r1, #0x39
	bl GameStats_GetCapped
	cmp r0, #0x64
	bhs _020650F8
	add r0, r6, #0x0
	mov r1, #0x3b
	bl GameStats_GetCapped
	cmp r0, #0x64
	bhs _020650F8
	add r0, r6, #0x0
	mov r1, #0x3d
	bl GameStats_GetCapped
	cmp r0, #0x64
	blo _020650FE
_020650F8:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_020650FE:
	add r0, r5, #0x0
	mov r1, #0x0
	bl sub_0205EE60
	cmp r0, #0x0
	bne _0206513A
	add r0, r5, #0x0
	mov r1, #0x1
	bl sub_0205EE60
	cmp r0, #0x0
	bne _0206513A
	add r0, r5, #0x0
	mov r1, #0x3
	bl sub_0205EE60
	cmp r0, #0x0
	bne _0206513A
	add r0, r5, #0x0
	mov r1, #0x4
	bl sub_0205EE60
	cmp r0, #0x0
	bne _0206513A
	add r0, r5, #0x0
	mov r1, #0x2
	bl sub_0205EE60
	cmp r0, #0x0
	beq _02065140
_0206513A:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02065140:
	ldr r0, [sp, #0x0]
	bl sub_020268D4
	cmp r0, #0x1
	bne _02065150
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02065150:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start sub_02065154
sub_02065154: ; 0x02065154
	push {r3-r6}
	ldr r5, [sp, #0x14]
	mov r6, #0x1
	ldrb r4, [r5, #0x4]
	bic r4, r6
	mov r6, #0x1
	and r0, r6
	orr r0, r4
	strb r0, [r5, #0x4]
	strb r1, [r5, #0x0]
	strb r2, [r5, #0x3]
	add r0, sp, #0x0
	ldrb r0, [r0, #0x10]
	strb r0, [r5, #0x1]
	strb r3, [r5, #0x2]
	pop {r3-r6}
	bx lr
	.balign 4

	thumb_func_start sub_02065178
sub_02065178: ; 0x02065178
	push {r4-r6, lr}
	ldr r4, [sp, #0x1c]
	add r6, r1, #0x0
	strh r0, [r4, #0x28]
	ldrb r0, [r4, #0x4]
	add r1, r2, #0x0
	mov r2, #0x4
	bic r0, r2
	lsl r2, r6, #0x1f
	lsr r2, r2, #0x1d
	orr r0, r2
	strb r0, [r4, #0x4]
	add r0, r4, #0x0
	add r0, #0x8
	mov r2, #0x8
	add r5, r3, #0x0
	bl CopyU16StringArrayN
	ldr r0, [sp, #0x10]
	str r5, [r4, #0x1c]
	str r0, [r4, #0x20]
	ldrb r0, [r4, #0x4]
	mov r1, #0x8
	bic r0, r1
	ldr r1, [sp, #0x14]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1c
	orr r0, r1
	strb r0, [r4, #0x4]
	ldr r0, [sp, #0x18]
	str r0, [r4, #0x24]
	pop {r4-r6, pc}

	thumb_func_start sub_020651BC
sub_020651BC: ; 0x020651BC
	push {r3-r7, lr}
	sub sp, #0x8
	ldr r4, [sp, #0x28]
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, r1, #0x0
	add r5, r2, #0x0
	add r6, r3, #0x0
	ldr r7, [sp, #0x20]
	bl GetIGTHours
	strh r0, [r4, #0x2a]
	ldr r0, [sp, #0x4]
	bl GetIGTMinutes
	add r1, r4, #0x0
	add r1, #0x2e
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	ldr r1, [r5, #0x0]
	add r0, #0x2f
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	ldr r1, [r5, #0x4]
	add r0, #0x30
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	ldr r1, [r5, #0x8]
	add r0, #0x31
	strb r1, [r0, #0x0]
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _0206521E
	add r0, r4, #0x0
	ldr r1, [r6, #0x0]
	add r0, #0x32
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	ldr r1, [r6, #0x4]
	add r0, #0x33
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	ldr r1, [r6, #0x8]
	add r0, #0x34
	strb r1, [r0, #0x0]
	ldr r0, [r7, #0x0]
	strh r0, [r4, #0x2c]
	ldr r1, [r7, #0x4]
	b _02065234
_0206521E:
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x32
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x33
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x34
	strb r1, [r0, #0x0]
	strh r1, [r4, #0x2c]
_02065234:
	add r0, r4, #0x0
	add r0, #0x35
	strb r1, [r0, #0x0]
	ldrb r2, [r4, #0x4]
	mov r0, #0x2
	bic r2, r0
	add r0, sp, #0x10
	ldrb r0, [r0, #0x14]
	lsl r1, r0, #0x1f
	lsr r1, r1, #0x1e
	orr r1, r2
	strb r1, [r4, #0x4]
	cmp r0, #0x0
	beq _02065258
	ldr r0, [sp, #0x4]
	add sp, #0x8
	str r0, [r4, #0x18]
	pop {r3-r7, pc}
_02065258:
	mov r0, #0x0
	str r0, [r4, #0x18]
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start sub_02065260
sub_02065260: ; 0x02065260
	push {r3-r5, lr}
	ldr r4, [sp, #0x14]
	ldr r5, _020652A0 ; =0x000F423F
	str r0, [r4, #0x38]
	cmp r0, r5
	bls _0206526E
	str r5, [r4, #0x38]
_0206526E:
	str r1, [r4, #0x3c]
	str r2, [r4, #0x40]
	ldr r1, [r4, #0x3c]
	ldr r0, _020652A4 ; =0x0000270F
	cmp r1, r0
	bls _0206527C
	str r0, [r4, #0x3c]
_0206527C:
	ldr r1, [r4, #0x40]
	ldr r0, _020652A4 ; =0x0000270F
	cmp r1, r0
	bls _02065286
	str r0, [r4, #0x40]
_02065286:
	ldr r0, _020652A8 ; =0x0001869F
	str r3, [r4, #0x44]
	cmp r3, r0
	bls _02065290
	str r0, [r4, #0x44]
_02065290:
	add r4, #0x68
	mov r2, #0x6
	ldr r0, [sp, #0x10]
	add r1, r4, #0x0
	lsl r2, r2, #0x8
	bl MI_CpuCopy8
	pop {r3-r5, pc}
	.balign 4
_020652A0: .word 0x000F423F
_020652A4: .word 0x0000270F
_020652A8: .word 0x0001869F

	thumb_func_start sub_020652AC
sub_020652AC: ; 0x020652AC
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	ldr r0, [r1, #0xc]
	add r5, r2, #0x0
	bl sub_02029ABC
	bl sub_02029ACC
	str r0, [sp, #0x4]
	mov r0, #0x1
	mov r4, #0x0
	add r5, #0x48
	str r0, [sp, #0x8]
	add r7, r0, #0x0
_020652CA:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0x0
	beq _020652E6
	lsl r0, r4, #0x2
	ldr r2, [r5, r0]
	mov r1, #0x1
	bic r2, r7
	orr r1, r2
	add r6, r5, r0
	str r1, [r5, r0]
	b _020652F2
_020652E6:
	lsl r2, r4, #0x2
	ldr r1, [r5, r2]
	ldr r0, [sp, #0x8]
	add r6, r5, r2
	bic r1, r0
	str r1, [r5, r2]
_020652F2:
	ldr r1, [sp, #0x4]
	add r0, r4, #0x0
	bl sub_02029AD0
	ldr r2, [r6, #0x0]
	mov r1, #0x1
	and r1, r2
	lsl r0, r0, #0x1
	orr r0, r1
	str r0, [r6, #0x0]
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x8
	blo _020652CA
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start sub_02065314
sub_02065314: ; 0x02065314
	push {r4-r6, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl sub_02029ABC
	bl sub_02029ACC
	add r6, r0, #0x0
	mov r4, #0x0
_02065326:
	lsl r1, r4, #0x2
	add r1, r5, r1
	ldr r1, [r1, #0x48]
	add r0, r4, #0x0
	asr r1, r1, #0x1
	add r2, r6, #0x0
	bl sub_02029AD8
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x8
	blo _02065326
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_02065344
sub_02065344: ; 0x02065344
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x78]
	bl sub_02052E38
	str r0, [r4, #0x4]
	ldr r0, [r5, #0x10]
	ldr r1, _0206536C ; =sub_02065370
	add r2, r4, #0x0
	bl sub_0204640C
	pop {r3-r5, pc}
	nop
_0206536C: .word sub_02065370

	thumb_func_start sub_02065370
sub_02065370: ; 0x02065370
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl sub_02046528
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204652C
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0xa
	bgt _0206539A
	bge _020653BA
	cmp r0, #0x1
	bgt _020653E2
	cmp r0, #0x0
	blt _020653E2
	beq _020653A0
	cmp r0, #0x1
	beq _020653AA
	b _020653E2
_0206539A:
	cmp r0, #0xb
	beq _020653C8
	b _020653E2
_020653A0:
	ldr r0, [r4, #0x78]
	bl sub_02052ED0
	mov r0, #0x1
	str r0, [r5, #0x0]
_020653AA:
	ldr r1, [r5, #0x4]
	ldr r0, _020653E8 ; =0x0000066A
	ldrh r0, [r1, r0]
	cmp r0, #0x0
	beq _020653E2
	mov r0, #0xa
	str r0, [r5, #0x0]
	b _020653E2
_020653BA:
	ldr r1, [r5, #0x4]
	add r0, r4, #0x0
	bl sub_02038680
	mov r0, #0xb
	str r0, [r5, #0x0]
	b _020653E2
_020653C8:
	add r0, r4, #0x0
	bl sub_0204647C
	cmp r0, #0x0
	bne _020653E2
	ldr r0, [r4, #0x78]
	bl sub_02052EAC
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_020653E2:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_020653E8: .word 0x0000066A
