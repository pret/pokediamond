    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start ScrCmd_unk_248
ScrCmd_unk_248: ; 0x0203FE90
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r1, r0, #0x0
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	bl FUN_02082140
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_249
ScrCmd_unk_249: ; 0x0203FEC0
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [r4, #0x64]
	ldr r1, _0203FEF0 ; =FUN_0203FEF4
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203FEF0: .word FUN_0203FEF4

	thumb_func_start FUN_0203FEF4
FUN_0203FEF4: ; 0x0203FEF4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r1, [r4, #0x64]
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02082158
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_250
ScrCmd_unk_250: ; 0x0203FF10
	push {r3-r7, lr}
	sub sp, #0x38
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x4]
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
	str r0, [sp, #0xc]
	add r0, r5, #0x0
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
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	mov r1, #0x4
	bl PlayerProfile_GetPlayerName_NewString
	add r7, r0, #0x0
	ldr r1, [sp, #0x8]
	add r0, sp, #0x14
	strb r1, [r0, #0x0]
	ldr r1, [sp, #0x4]
	strb r1, [r0, #0x1]
	ldr r1, [sp, #0xc]
	strb r1, [r0, #0x2]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205ED0C
	add r1, sp, #0x14
	strb r0, [r1, #0x3]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	bl Pokedex_GetNatDexFlag
	add r1, sp, #0x14
	strb r0, [r1, #0x4]
	strb r6, [r1, #0x5]
	ldr r0, [sp, #0x10]
	str r7, [sp, #0x20]
	str r0, [sp, #0x1c]
	add r0, r5, #0x0
	str r4, [sp, #0x24]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [sp, #0x2c]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r5, #0x80
	ldr r0, [r0, #0xc]
	str r0, [sp, #0x30]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029EF8
	str r0, [sp, #0x34]
	add r0, sp, #0x14
	bl FUN_02081214
	ldr r1, [sp, #0x0]
	str r0, [r1, #0x0]
	add r0, r7, #0x0
	bl String_dtor
	mov r0, #0x0
	add sp, #0x38
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_251
ScrCmd_unk_251: ; 0x02040028
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034824
	add r5, #0x80
	ldr r3, [r5, #0x0]
	add r2, r0, #0x0
	ldr r1, [r3, #0xc]
	add r3, #0x98
	ldr r0, [r4, #0x0]
	ldr r3, [r3, #0x0]
	bl FUN_02082630
	ldr r0, [r4, #0x0]
	bl FUN_020814E8
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_252
ScrCmd_unk_252: ; 0x02040074
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
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
	bl VarGet
	add r3, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r2, [r6, #0x0]
	add r1, r7, #0x0
	bl FUN_0208201C
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_253
ScrCmd_unk_253: ; 0x020400C8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
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
	bl VarGet
	add r3, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r2, [r6, #0x0]
	add r1, r7, #0x0
	bl FUN_02082034
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_254
ScrCmd_unk_254: ; 0x0204011C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
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
	bl VarGet
	add r3, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r2, [r6, #0x0]
	add r1, r7, #0x0
	bl FUN_0208206C
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_255
ScrCmd_unk_255: ; 0x02040170
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
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
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r1, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r3, #0x1
	str r3, [sp, #0x4]
	ldr r0, [r4, #0x0]
	add r2, r6, #0x0
	bl BufferIntegerAsString
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_256
ScrCmd_unk_256: ; 0x020401CC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02081DC4
	ldr r1, _020401EC ; =FUN_020401F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_020401EC: .word FUN_020401F0

	thumb_func_start FUN_020401F0
FUN_020401F0: ; 0x020401F0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02081EB8
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_257
ScrCmd_unk_257: ; 0x02040204
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	ldr r1, [r1, #0x0]
	bl FUN_02080E0C
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_258
ScrCmd_unk_258: ; 0x02040220
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_02082090
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_259
ScrCmd_unk_259: ; 0x0204025C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_020820B8
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_260
ScrCmd_unk_260: ; 0x02040298
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_020820DC
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_261
ScrCmd_unk_261: ; 0x020402D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0208213C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_262
ScrCmd_unk_262: ; 0x02040304
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_0208210C
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_263
ScrCmd_unk_263: ; 0x02040340
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0208217C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_264
ScrCmd_unk_264: ; 0x02040370
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02082190
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_265
ScrCmd_unk_265: ; 0x020403A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020821B4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_266
ScrCmd_unk_266: ; 0x020403D0
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	bl FUN_020821C4
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_267
ScrCmd_unk_267: ; 0x02040414
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	bl FUN_020821DC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_268
ScrCmd_unk_268: ; 0x02040458
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020821F0
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_272
ScrCmd_unk_272: ; 0x02040488
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
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
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r3, [sp, #0x4]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02082214
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_269
ScrCmd_unk_269: ; 0x020404FC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02082254
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_270
ScrCmd_unk_270: ; 0x0204052C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r6, #0x0]
	mov r3, #0xb
	bl FUN_02082284
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_271
ScrCmd_unk_271: ; 0x0204056C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020822F0
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_279
ScrCmd_unk_279: ; 0x0204059C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_0208223C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_280
ScrCmd_unk_280: ; 0x020405B4
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_0208224C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_273
ScrCmd_unk_273: ; 0x020405CC
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02082444
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_274
ScrCmd_unk_274: ; 0x020405F8
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r1, _02040614 ; =FUN_02040618
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_02040614: .word FUN_02040618

	thumb_func_start FUN_02040618
FUN_02040618: ; 0x02040618
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02082508
	cmp r0, #0x1
	bne _02040632
	mov r0, #0x1
	pop {r3, pc}
_02040632:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_275
ScrCmd_unk_275: ; 0x02040638
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_276
ScrCmd_unk_276: ; 0x0204064C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_277
ScrCmd_unk_277: ; 0x02040660
	push {r4-r5, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x0]
	add r1, sp, #0x18
	add r2, sp, #0x14
	add r3, sp, #0x10
	bl FUN_020825A0
	ldr r0, [sp, #0x14]
	cmp r0, #0x1
	beq _020406B0
	ldr r0, [sp, #0x10]
	cmp r0, #0x1
	beq _020406B0
	ldr r0, [sp, #0xc]
	cmp r0, #0x1
	beq _020406B0
	ldr r0, [sp, #0x8]
	cmp r0, #0x1
	bne _020406B6
_020406B0:
	mov r0, #0x1
	strh r0, [r5, #0x0]
	b _020406BA
_020406B6:
	mov r0, #0x0
	strh r0, [r5, #0x0]
_020406BA:
	mov r0, #0x0
	add sp, #0x1c
	pop {r4-r5, pc}

	thumb_func_start ScrCmd_unk_278
ScrCmd_unk_278: ; 0x020406C0
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl MOD06_0224D3E8
	mov r0, #0x1
	pop {r3, pc}
