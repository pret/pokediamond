	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020F34FC
	.extern UNK_020F3538
	.extern gSystem
	.extern sub_0203BB90
	.extern sub_0203BC04

	.text

	thumb_func_start ScrCmd_PCFreeSpace
ScrCmd_PCFreeSpace: ; 0x0203ED70
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl GetStoragePCPointer
	bl PCStorage_CountMonsAndEggsInAllBoxes
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	mov r0, #0x87
	lsl r0, r0, #0x2
	sub r0, r0, r1
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Unk0258
ScrCmd_Unk0258: ; 0x0203EDA4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x16
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	mov r0, #0x0
	add r5, #0x80
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	bl ov05_021E7184
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0259
ScrCmd_Unk0259: ; 0x0203EDC8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x16
	bl FieldSysGetAttrAddr
	ldr r0, [r0, #0x0]
	bl ov05_021E71E8
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk025A
ScrCmd_Unk025A: ; 0x0203EDE0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r4, #0x80
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	bl ov06_0224E554
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk025B
ScrCmd_Unk025B: ; 0x0203EE08
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl sub_0206486C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk025C
ScrCmd_Unk025C: ; 0x0203EE18
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl sub_020649D4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk025D
ScrCmd_Unk025D: ; 0x0203EE28
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_020649B0
	cmp r0, #0x0
	beq _0203EE4E
	mov r0, #0x1
	b _0203EE50
_0203EE4E:
	mov r0, #0x0
_0203EE50:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk025E
ScrCmd_Unk025E: ; 0x0203EE58
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl ov06_0224E764
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk025F
ScrCmd_Unk025F: ; 0x0203EE68
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl ov06_0224E7C4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0260
ScrCmd_Unk0260: ; 0x0203EE78
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_GameStats_Get
	add r1, r4, #0x0
	bl GameStats_AddSpecial
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0262
ScrCmd_Unk0262: ; 0x0203EE98
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SaveArray_PlayerParty_Get
	add r1, r6, #0x0
	bl PartyHasMon
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_Unk0263
ScrCmd_Unk0263: ; 0x0203EED8
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, sp, #0x4
	strh r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SaveArray_PlayerParty_Get
	str r0, [sp, #0x0]
	bl GetPartyCount
	add r4, #0x80
	add r6, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_Pokedex_Get
	add r7, r0, #0x0
	mov r5, #0x0
	cmp r6, #0x0
	ble _0203EF4E
_0203EF18:
	ldr r0, [sp, #0x0]
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	ldr r1, _0203EF54 ; =0x00000182
	cmp r0, r1
	bne _0203EF48
	add r0, r4, #0x0
	mov r1, #0x70
	add r2, sp, #0x4
	bl SetMonData
	add r0, r4, #0x0
	bl CalcMonLevelAndStats
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl Pokedex_SetMonCaughtFlag
_0203EF48:
	add r5, r5, #0x1
	cmp r5, r6
	blt _0203EF18
_0203EF4E:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0203EF54: .word 0x00000182

	thumb_func_start ScrCmd_Unk0264
ScrCmd_Unk0264: ; 0x0203EF58
	push {r3-r7, lr}
	sub sp, #0x30
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl SaveArray_PlayerParty_Get
	str r0, [sp, #0xc]
	bl GetPartyCount
	add r2, sp, #0x18
	mov r4, #0x0
	ldr r3, _0203F008 ; =UNK_020F34FC
	str r0, [sp, #0x8]
	add r7, r2, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [sp, #0x8]
	str r4, [sp, #0x4]
	cmp r0, #0x0
	ble _0203EFFC
	mov r5, #0x1
	str r7, [sp, #0x14]
_0203EFA2:
	ldr r0, [sp, #0xc]
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	add r6, r0, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x10]
	add r0, r6, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl GetMonData
	add r3, r0, #0x0
	mov r0, #0x67
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0x2
	cmp r1, r0
	bne _0203EFF2
	mov r2, #0x0
	add r1, r2, #0x0
	str r3, [r7, #0x0]
	cmp r4, #0x0
	ble _0203EFE8
	ldr r6, [sp, #0x14]
_0203EFD8:
	ldr r0, [r6, #0x0]
	cmp r3, r0
	bne _0203EFE0
	add r2, r5, #0x0
_0203EFE0:
	add r1, r1, #0x1
	add r6, r6, #0x4
	cmp r1, r4
	blt _0203EFD8
_0203EFE8:
	cmp r2, #0x0
	bne _0203EFF2
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	str r0, [sp, #0x4]
_0203EFF2:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r7, r7, #0x4
	cmp r4, r0
	blt _0203EFA2
_0203EFFC:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x1
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_0203F008: .word UNK_020F34FC

	thumb_func_start ScrCmd_Unk0265
ScrCmd_Unk0265: ; 0x0203F00C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F1C4
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_Unk0266
ScrCmd_Unk0266: ; 0x0203F020
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F1D4
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_Unk0267
ScrCmd_Unk0267: ; 0x0203F034
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl sub_020389CC
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_Unk0268
ScrCmd_Unk0268: ; 0x0203F058
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl Script_GetHour
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Unk0269
ScrCmd_Unk0269: ; 0x0203F07C
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, #0x34]
	bl GetMapObjectByID
	add r7, r0, #0x0
	bne _0203F0FA
	bl GF_AssertFail
_0203F0FA:
	str r6, [sp, #0x0]
	str r4, [sp, #0x4]
	ldr r0, [r5, #0x74]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	add r1, r7, #0x0
	bl sub_02054F50
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_Unk026A
ScrCmd_Unk026A: ; 0x0203F110
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r5, #0x0
	ldr r0, [r0, #0x34]
	bl GetMapObjectByID
	add r5, r0, #0x0
	bne _0203F164
	bl GF_AssertFail
_0203F164:
	ldr r0, [r4, #0x74]
	add r1, r5, #0x0
	add r2, r7, #0x0
	add r3, r6, #0x0
	bl sub_0205502C
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_Unk026B
ScrCmd_Unk026B: ; 0x0203F174
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl sub_02054E30
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk026C
ScrCmd_Unk026C: ; 0x0203F19C
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_FashionData_Get
	bl Save_FashionData_GetFashionCase
	mov r6, #0x0
	add r7, r0, #0x0
	add r4, r6, #0x0
	add r5, sp, #0x4
_0203F1CA:
	add r1, r4, #0x0
	add r0, r7, #0x0
	add r1, #0x22
	mov r2, #0x1
	bl sub_020270D8
	cmp r0, #0x1
	bne _0203F1E0
	mov r0, #0x1
	strh r0, [r5, #0x0]
	add r6, r6, #0x1
_0203F1E0:
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, #0x10
	blt _0203F1CA
	cmp r6, #0x0
	bne _0203F1F8
	ldr r0, [sp, #0x0]
	ldr r1, _0203F230 ; =0x0000FFFF
	add sp, #0x24
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4-r7, pc}
_0203F1F8:
	bl LCRandom
	add r1, r6, #0x0
	bl _s32_div_f
	mov r4, #0x0
	add r2, sp, #0x4
_0203F206:
	ldrh r0, [r2, #0x0]
	cmp r0, #0x1
	bne _0203F212
	cmp r1, #0x0
	beq _0203F21A
	sub r1, r1, #0x1
_0203F212:
	add r4, r4, #0x1
	add r2, r2, #0x2
	cmp r4, #0x10
	blt _0203F206
_0203F21A:
	cmp r4, #0x10
	blt _0203F222
	bl GF_AssertFail
_0203F222:
	ldr r0, [sp, #0x0]
	add r4, #0x22
	strh r4, [r0, #0x0]
	mov r0, #0x0
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0203F230: .word 0x0000FFFF

	thumb_func_start ScrCmd_Unk026E
ScrCmd_Unk026E: ; 0x0203F234
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	ldr r1, _0203F250 ; =gSystem + 0x60
	ldrb r1, [r1, #0x6]
	strh r1, [r0, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203F250: .word gSystem + 0x60

	thumb_func_start ScrCmd_Unk026F
ScrCmd_Unk026F: ; 0x0203F254
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	mov r1, #0x0
	bl sub_0205F698
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0270
ScrCmd_Unk0270: ; 0x0203F26C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldrb r4, [r1, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	cmp r4, #0x0
	beq _0203F2A0
	add r1, r6, #0x0
	bl sub_0205F4E4
	b _0203F2A6
_0203F2A0:
	add r1, r6, #0x0
	bl sub_0205F50C
_0203F2A6:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0273
ScrCmd_Unk0273: ; 0x0203F2AC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FieldSysGetAttrAddr
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl BufferContestBackgroundName
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0275
ScrCmd_Unk0275: ; 0x0203F2E4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0205F6C8
	cmp r0, #0xa
	blo _0203F314
	mov r0, #0x1
	b _0203F316
_0203F314:
	mov r0, #0x0
_0203F316:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Unk0277
ScrCmd_Unk0277: ; 0x0203F31C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F648
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0279
ScrCmd_Unk0279: ; 0x0203F348
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_FashionData_Get
	bl Save_FashionData_GetFashionCase
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl sub_02027210
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_Unk027A
ScrCmd_Unk027A: ; 0x0203F38C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl sub_02046030
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk027B
ScrCmd_Unk027B: ; 0x0203F39C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl sub_0205F668
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_Unk027D
ScrCmd_Unk027D: ; 0x0203F3AC
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FieldSysGetAttrAddr
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_EasyChat_Get
	bl sub_02013B74
	cmp r0, #0x20
	bne _0203F3FE
	ldr r0, _0203F414 ; =0x0000FFFF
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
_0203F3FE:
	strh r0, [r4, #0x0]
	bl sub_02013BE4
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r7, #0x0
	bl BufferECWord
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0203F414: .word 0x0000FFFF

	thumb_func_start ScrCmd_Unk027F
ScrCmd_Unk027F: ; 0x0203F418
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_EasyChat_Get
	bl sub_02013BC8
	cmp r0, #0x1
	bne _0203F444
	mov r0, #0x1
	b _0203F446
_0203F444:
	mov r0, #0x0
_0203F446:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Unk027E
ScrCmd_Unk027E: ; 0x0203F44C
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0205F710
	cmp r0, #0x5
	blo _0203F47C
	mov r0, #0x1
	b _0203F47E
_0203F47C:
	mov r0, #0x0
_0203F47E:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Unk0282
ScrCmd_Unk0282: ; 0x0203F484
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	ldr r5, [r5, #0x0]
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Save_SysInfo_Get
	add r7, r0, #0x0
	bl Save_SysInfo_GetBirthMonth
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl Script_GetMonth
	cmp r6, r0
	bne _0203F4CE
	add r0, r7, #0x0
	bl Save_SysInfo_GetBirthDay
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl Script_GetDay
	cmp r6, r0
	bne _0203F4CE
	mov r0, #0x1
	strh r0, [r4, #0x0]
	b _0203F4D2
_0203F4CE:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0203F4D2:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0284
ScrCmd_Unk0284: ; 0x0203F4D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_Pokedex_Get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl Pokedex_CountSeenUnown
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0285
ScrCmd_Unk0285: ; 0x0203F508
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r6, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x1c]
	ldr r1, [r2, #0x8]
	lsl r1, r1, #0x10
	lsr r5, r1, #0x10
	ldr r1, [r2, #0xc]
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	cmp r7, #0x3
	blo _0203F54C
	ldr r7, _0203F5C8 ; =0x0000010E
	b _0203F582
_0203F54C:
	cmp r0, #0x1e
	blo _0203F556
	mov r7, #0x43
	lsl r7, r7, #0x2
	b _0203F582
_0203F556:
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, #0x19
	bge _0203F568
	ldr r7, _0203F5CC ; =0x0000010D
	b _0203F582
_0203F568:
	bl LCRandom
	mov r1, #0x6
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r1, r0, #0x10
	mov r0, #0x6
	mul r0, r7
	add r0, r1, r0
	lsl r1, r0, #0x1
	ldr r0, _0203F5D0 ; =UNK_020F3538
	ldrh r7, [r0, r1]
_0203F582:
	cmp r5, #0xb
	bne _0203F59A
	cmp r4, #0x1
	bne _0203F58E
	mov r4, #0x0
	b _0203F5A4
_0203F58E:
	cmp r4, #0x14
	bne _0203F596
	mov r4, #0x2
	b _0203F5A4
_0203F596:
	mov r4, #0x5
	b _0203F5A4
_0203F59A:
	cmp r5, #0x14
	bne _0203F5A2
	mov r4, #0x1
	b _0203F5A4
_0203F5A2:
	mov r4, #0x3
_0203F5A4:
	mov r5, #0x0
_0203F5A6:
	cmp r5, r4
	beq _0203F5B8
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl sub_02034C24
_0203F5B8:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x4
	blo _0203F5A6
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0203F5C8: .word 0x0000010E
_0203F5CC: .word 0x0000010D
_0203F5D0: .word UNK_020F3538

	thumb_func_start ScrCmd_Unk0286
ScrCmd_Unk0286: ; 0x0203F5D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl sub_0205F720
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0287
ScrCmd_Unk0287: ; 0x0203F604
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl sub_0205F740
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0288
ScrCmd_Unk0288: ; 0x0203F634
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl sub_0205F760
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0289
ScrCmd_Unk0289: ; 0x0203F664
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x0
	add r3, sp, #0x0
	add r0, #0x8
_0203F684:
	ldr r6, [r0, #0x0]
	ldr r1, [r5, #0x8]
	add r6, r6, #0x1
	str r6, [r0, #0x0]
	ldrb r1, [r1, #0x0]
	add r2, r2, #0x1
	strb r1, [r3, #0x0]
	add r3, r3, #0x1
	cmp r2, #0x5
	blt _0203F684
	ldr r1, [r0, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	ldrb r6, [r2, #0x0]
	mov r0, #0x4
	bl sub_02027E5C
	add r1, sp, #0x0
	add r2, r6, #0x0
	mov r3, #0x0
	add r7, r0, #0x0
	bl sub_02027F04
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl sub_02028048
	add r1, r7, #0x0
	bl sub_02028094
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FreeToHeap
	ldr r0, _0203F6E0 ; =0x0000FFFF
	cmp r5, r0
	bne _0203F6D8
	strh r0, [r4, #0x0]
	b _0203F6DA
_0203F6D8:
	strh r6, [r4, #0x0]
_0203F6DA:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0203F6E0: .word 0x0000FFFF

	thumb_func_start ScrCmd_Unk028A
ScrCmd_Unk028A: ; 0x0203F6E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl sub_02028048
	bl sub_02028074
	ldr r1, _0203F71C ; =0x0000FFFF
	cmp r0, r1
	bne _0203F712
	mov r0, #0x0
	b _0203F714
_0203F712:
	mov r0, #0x1
_0203F714:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203F71C: .word 0x0000FFFF

	thumb_func_start ScrCmd_Unk028B
ScrCmd_Unk028B: ; 0x0203F720
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	add r5, r0, #0x0
	cmp r4, #0x3
	bls _0203F752
	bl GF_AssertFail
_0203F752:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205F4A0
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_Unk028F
ScrCmd_Unk028F: ; 0x0203F760
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x20
	ldr r0, [r0, #0xc]
	add r2, sp, #0x0
	bl LoadHallOfFame
	ldr r1, [sp, #0x0]
	add r4, r0, #0x0
	cmp r1, #0x0
	bne _0203F798
	mov r1, #0x0
	strh r1, [r5, #0x0]
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F798:
	cmp r1, #0x1
	bne _0203F7AE
	mov r1, #0x0
	bl Save_HOF_TranslateRecordIdx
	strh r0, [r5, #0x0]
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F7AE:
	cmp r1, #0x2
	bne _0203F7BE
	mov r1, #0x0
	strh r1, [r5, #0x0]
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F7BE:
	mov r0, #0x0
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0290
ScrCmd_Unk0290: ; 0x0203F7C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FieldSysGetAttrAddr
	add r1, r5, #0x0
	add r1, #0x80
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	add r2, r6, #0x0
	bl sub_02037A48
	str r0, [r4, #0x0]
	ldr r1, _0203F808 ; =sub_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203F808: .word sub_0203BC04 

	thumb_func_start ScrCmd_Unk0291
ScrCmd_Unk0291: ; 0x0203F80C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203F84C
	bl GF_AssertFail
_0203F84C:
	ldr r0, [r4, #0x0]
	bl sub_02037A40
	strh r0, [r6, #0x0]
	ldrh r0, [r6, #0x0]
	cmp r0, #0x7
	bne _0203F85E
	mov r0, #0xff
	strh r0, [r6, #0x0]
_0203F85E:
	ldr r0, [r4, #0x0]
	bl sub_02037A70
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	bne _0203F870
	mov r0, #0x1
	b _0203F872
_0203F870:
	mov r0, #0x0
_0203F872:
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_Unk0292
ScrCmd_Unk0292: ; 0x0203F880
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	cmp r4, #0x64
	bls _0203F8A2
	mov r4, #0x64
_0203F8A2:
	bl LCRandom
	mov r1, #0x65
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	cmp r0, r4
	bgt _0203F8B8
	mov r0, #0x1
	b _0203F8BA
_0203F8B8:
	mov r0, #0x0
_0203F8BA:
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Unk029E
ScrCmd_Unk029E: ; 0x0203F8C0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r4, #0x0
	beq _0203F8FC
	cmp r4, #0x1
	beq _0203F906
	cmp r4, #0x2
	beq _0203F910
	b _0203F91A
_0203F8FC:
	mov r2, #0x0
	mov r3, #0x20
	bl ov06_0224F12C
	b _0203F91E
_0203F906:
	mov r2, #0x1
	mov r3, #0x20
	bl ov06_0224F12C
	b _0203F91E
_0203F910:
	mov r2, #0x2
	mov r3, #0x20
	bl ov06_0224F12C
	b _0203F91E
_0203F91A:
	bl GF_AssertFail
_0203F91E:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0293
ScrCmd_Unk0293: ; 0x0203F924
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl sub_0205F6A8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk029F
ScrCmd_Unk029F: ; 0x0203F954
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	cmp r0, #0x0
	bne _0203F978
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl ov06_02239944
	b _0203F982
_0203F978:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl ov06_02239AAC
_0203F982:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02A3
ScrCmd_Unk02A3: ; 0x0203F988
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl sub_0203384C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02A4
ScrCmd_Unk02A4: ; 0x0203F9B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl sub_020286EC
	bl sub_02028448
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02A2
ScrCmd_Unk02A2: ; 0x0203F9DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl sub_02026CC4
	ldr r1, _0203FA10 ; =0x0000FF79
	add r1, r4, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	cmp r1, #0x1
	bhi _0203FA0C
	bl sub_02025C30
_0203FA0C:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0203FA10: .word 0x0000FF79

	thumb_func_start ScrCmd_Unk02A7
ScrCmd_Unk02A7: ; 0x0203FA14
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	mov r1, #0x0
	strh r1, [r0, #0x0]
	ldr r1, _0203FA54 ; =0x0000012A
	cmp r4, r1
	blo _0203FA4E
	add r1, #0xf
	cmp r4, r1
	bhi _0203FA4E
	mov r1, #0x1
	strh r1, [r0, #0x0]
_0203FA4E:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203FA54: .word 0x0000012A

	thumb_func_start ScrCmd_Unk02AA
ScrCmd_Unk02AA: ; 0x0203FA58
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r7, r0, #0x0
	mov r0, #0x20
	bl MessageFormat_New
	add r4, r0, #0x0
	ldr r2, _0203FB48 ; =0x00000147
	mov r0, #0x0
	mov r1, #0x1a
	mov r3, #0x20
	bl NewMsgDataFromNarc
	add r5, r0, #0x0
	ldr r2, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x0
	bl BufferECWord
	ldr r2, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x1
	bl BufferECWord
	ldr r2, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x2
	bl BufferECWord
	add r0, r4, #0x0
	mov r1, #0x3
	add r2, r7, #0x0
	bl BufferECWord
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	mov r3, #0x20
	bl ReadMsgData_ExpandPlaceholders
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl NewString_ReadMsgData
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r7, #0x0
	bl StringCompare
	cmp r0, #0x0
	bne _0203FB24
	mov r0, #0x1
	b _0203FB26
_0203FB24:
	mov r0, #0x0
_0203FB26:
	strh r0, [r6, #0x0]
	add r0, r7, #0x0
	bl String_Delete
	ldr r0, [sp, #0x0]
	bl String_Delete
	add r0, r5, #0x0
	bl DestroyMsgData
	add r0, r4, #0x0
	bl MessageFormat_Delete
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_0203FB48: .word 0x00000147

	thumb_func_start ScrCmd_Unk02AC
ScrCmd_Unk02AC: ; 0x0203FB4C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_SysInfo_Get
	mov r1, #0x1
	bl sub_02023828
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02AF
ScrCmd_Unk02AF: ; 0x0203FB64
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xf
	bl FieldSysGetAttrAddr
	ldr r0, [r0, #0x0]
	bl sub_0205296C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02B0
ScrCmd_Unk02B0: ; 0x0203FB94
	push {r3, lr}
	bl sub_02033E74
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02B1
ScrCmd_Unk02B1: ; 0x0203FBA0
	push {r3, lr}
	bl sub_02033ED0
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02B2
ScrCmd_Unk02B2: ; 0x0203FBAC
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl sub_02034E48
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02B5
ScrCmd_Unk02B5: ; 0x0203FBBC
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_LocalFieldData_Get
	bl sub_02034DCC
	str r4, [r0, #0x0]
	str r6, [r0, #0x8]
	mov r1, #0x0
	str r7, [r0, #0xc]
	mvn r1, r1
	str r1, [r0, #0x4]
	mov r1, #0x1
	str r1, [r0, #0x10]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_Unk02B6
ScrCmd_Unk02B6: ; 0x0203FC1C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	ldr r2, [r5, #0x8]
	add r1, r0, #0x0
	add r0, r2, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldrb r4, [r2, #0x0]
	ldr r0, [r0, #0x34]
	bl GetMapObjectByID
	add r5, r0, #0x0
	bne _0203FC4C
	bl GF_AssertFail
_0203FC4C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_020588B8
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Unk02BE
ScrCmd_Unk02BE: ; 0x0203FC58
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl sub_02065078
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02C1
ScrCmd_Unk02C1: ; 0x0203FC80
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x28
	add r0, r5, #0x0
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Save_FileDoesNotBelongToPlayer
	cmp r0, #0x0
	bne _0203FCAA
	add r0, r5, #0x0
	mov r1, #0x4
	mov r2, #0x3
	bl ov05_021E8588
	str r0, [r4, #0x0]
	bl ov05_021E84F4
_0203FCAA:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02C2
ScrCmd_Unk02C2: ; 0x0203FCB0
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x28
	add r0, r5, #0x0
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Save_FileDoesNotBelongToPlayer
	cmp r0, #0x0
	bne _0203FCD6
	ldr r0, [r4, #0x0]
	bl ov05_021E856C
	ldr r0, [r4, #0x0]
	bl ov05_021E85E4
_0203FCD6:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02C3
ScrCmd_Unk02C3: ; 0x0203FCDC
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl sub_0206367C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
