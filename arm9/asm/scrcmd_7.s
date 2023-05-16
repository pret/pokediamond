	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start ScrCmd_Unk00B6
ScrCmd_Unk00B6: ; 0x020416A8
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r5, r0, #0x0
	bne _02041708
	add r0, r4, #0x0
	mov r1, #0x18
	bl FieldSysGetAttrAddr
	str r0, [sp, #0x14]
	add r0, r4, #0x0
	mov r1, #0x19
	bl FieldSysGetAttrAddr
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x1a
	bl FieldSysGetAttrAddr
	add r0, r4, #0x0
	mov r1, #0x1b
	bl FieldSysGetAttrAddr
	add r0, r4, #0x0
	mov r1, #0x1c
	bl FieldSysGetAttrAddr
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	mov r1, #0x1d
	bl FieldSysGetAttrAddr
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x1e
	bl FieldSysGetAttrAddr
	b _02041748
_02041708:
	add r0, r4, #0x0
	mov r1, #0x1f
	bl FieldSysGetAttrAddr
	str r0, [sp, #0x14]
	add r0, r4, #0x0
	mov r1, #0x20
	bl FieldSysGetAttrAddr
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x21
	bl FieldSysGetAttrAddr
	add r0, r4, #0x0
	mov r1, #0x22
	bl FieldSysGetAttrAddr
	add r0, r4, #0x0
	mov r1, #0x23
	bl FieldSysGetAttrAddr
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	mov r1, #0x24
	bl FieldSysGetAttrAddr
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x25
	bl FieldSysGetAttrAddr
_02041748:
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0xc]
	ldr r0, [r0, #0x0]
	ldr r3, [sp, #0x14]
	str r0, [sp, #0x4]
	str r5, [sp, #0x8]
	ldr r0, [r6, #0x0]
	ldr r1, [r4, #0x38]
	ldr r2, [r2, #0x0]
	ldr r3, [r3, #0x0]
	bl FUN_0205CA4C
	str r0, [r7, #0x0]
	mov r0, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk00B7
ScrCmd_Unk00B7: ; 0x02041770
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
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x0]
	cmp r6, #0x0
	bne _020417AE
	add r5, #0x80
	ldr r0, [r5, #0x0]
	mov r1, #0x1e
	bl FieldSysGetAttrAddr
	b _020417B8
_020417AE:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	mov r1, #0x25
	bl FieldSysGetAttrAddr
_020417B8:
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	bne _020417C6
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_020417C6:
	bl FUN_0205CA64
	cmp r0, #0x1
	bne _020417DC
	ldr r0, [r5, #0x0]
	bl FUN_0205CA78
	mov r0, #0x0
	str r0, [r5, #0x0]
	mov r0, #0x1
	strh r0, [r4, #0x0]
_020417DC:
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_Unk00B8
ScrCmd_Unk00B8: ; 0x020417E0
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1c
	bl FieldSysGetAttrAddr
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	ldrh r1, [r5, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Unk00B9
ScrCmd_Unk00B9: ; 0x02041808
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1b
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x22
	bl FieldSysGetAttrAddr
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	cmp r7, #0x0
	bne _02041852
	ldrh r1, [r4, #0x0]
	b _02041854
_02041852:
	ldrh r1, [r6, #0x0]
_02041854:
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk00E4
ScrCmd_Unk00E4: ; 0x0204185C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x8
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_020395F4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk00E5
ScrCmd_Unk00E5: ; 0x0204188C
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x8
	add r0, r4, #0x0
	bl FieldSysGetAttrAddr
	add r0, r4, #0x0
	mov r1, #0x17
	bl FieldSysGetAttrAddr
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
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r6, #0x0
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205ED3C
	cmp r0, #0x1
	bne _020418F2
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F368
	add r6, r0, #0x0
_020418F2:
	mov r0, #0xb
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	ldr r0, [r5, #0x74]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x8]
	add r3, r6, #0x0
	bl FUN_020470E8
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02A0
ScrCmd_Unk02A0: ; 0x0204190C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FieldSysGetAttrAddr
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
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r2, r0, #0x0
	mov r0, #0xb
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	ldr r0, [r5, #0x74]
	add r1, r7, #0x0
	add r3, r6, #0x0
	bl FUN_020470E8
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_Unk00E7
ScrCmd_Unk00E7: ; 0x02041970
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x8
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_020395F4
	bl Field_TrainerIsDoubleBattle
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bne _020419D2
	mov r0, #0x0
	mov r1, #0x2
	add r2, r0, #0x0
	b _020419EC
_020419D2:
	ldrh r0, [r4, #0x0]
	bl FUN_02039618
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bne _020419E6
	mov r0, #0x3
	mov r1, #0x5
	mov r2, #0x6
	b _020419EC
_020419E6:
	mov r0, #0x7
	mov r1, #0x9
	mov r2, #0xa
_020419EC:
	strh r0, [r7, #0x0]
	strh r1, [r6, #0x0]
	strh r2, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk00E8
ScrCmd_Unk00E8: ; 0x020419F8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x8
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_020395F4
	bl Field_TrainerIsDoubleBattle
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bne _02041A5A
	mov r1, #0x0
	mov r0, #0x11
	add r2, r1, #0x0
	b _02041A74
_02041A5A:
	ldrh r0, [r4, #0x0]
	bl FUN_02039618
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bne _02041A6E
	mov r0, #0x12
	mov r1, #0x0
	mov r2, #0x6
	b _02041A74
_02041A6E:
	mov r0, #0x13
	mov r1, #0x0
	mov r2, #0xa
_02041A74:
	strh r0, [r7, #0x0]
	strh r1, [r6, #0x0]
	strh r2, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk00E9
ScrCmd_Unk00E9: ; 0x02041A80
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x8
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_020395F4
	bl Field_TrainerIsDoubleBattle
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk00EA
ScrCmd_Unk00EA: ; 0x02041AB4
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	bl FUN_0204AD0C
	bl FUN_02004724
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk00EB
ScrCmd_Unk00EB: ; 0x02041AD4
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02048498
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_Unk00EC
ScrCmd_Unk00EC: ; 0x02041AE0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020480B8
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk00ED
ScrCmd_Unk00ED: ; 0x02041B10
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020480C8
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02BC
ScrCmd_Unk02BC: ; 0x02041B40
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FieldSysGetAttrAddr
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020480D8
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk00EE
ScrCmd_Unk00EE: ; 0x02041B70
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
	bl SavArray_PlayerParty_get
	bl HasEnoughAlivePokemonForDoubleBattle
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk00EF
ScrCmd_Unk00EF: ; 0x02041B9C
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FieldSysGetAttrAddr
	mov r1, #0xb
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r2, #0x0
	ldr r0, [r4, #0x74]
	mov r1, #0x1
	add r3, r2, #0x0
	bl FUN_020470E8
	mov r0, #0x1
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start ScrCmd_Unk00F0
ScrCmd_Unk00F0: ; 0x02041BC4
	push {r3-r5, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FieldSysGetAttrAddr
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02058738
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02058448
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r4, #0x0
	lsr r1, r1, #0x10
	bl TrainerFlagSet
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Unk00F1
ScrCmd_Unk00F1: ; 0x02041BF0
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FieldSysGetAttrAddr
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl ScriptReadWord
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02058738
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02058448
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r7, #0x0
	lsr r1, r1, #0x10
	bl TrainerFlagCheck
	cmp r0, #0x1
	bne _02041C34
	ldr r1, [r6, #0x8]
	add r0, r6, #0x0
	add r1, r1, r4
	bl ScriptJump
	mov r0, #0x1
	pop {r3-r7, pc}
_02041C34:
	mov r0, #0x0
	pop {r3-r7, pc}
