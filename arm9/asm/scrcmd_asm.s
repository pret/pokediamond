	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020F34FC
	.extern UNK_020F3538
	.extern gSystem
	.extern sub_0203BB90
	.extern sub_0203BC04

	.text

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
	bl Save_PoffinData_Get
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
