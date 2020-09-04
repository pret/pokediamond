    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start ScrCmd_unk_365
ScrCmd_unk_365: ; 0x02043E00
	push {r3-r5, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	ldr r5, [r0, #0xc]
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl Sav2_DayCare_get
	ldr r1, [r4, #0x0]
	bl MOD05_021ED4E0
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_366
ScrCmd_unk_366: ; 0x02043E20
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x8
	bl SavArray_get
	bl MOD05_021ED5EC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_424
ScrCmd_unk_424: ; 0x02043E50
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x8
	ldr r0, [r0, #0xc]
	bl SavArray_get
	bl MOD05_021ECD64
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_425
ScrCmd_unk_425: ; 0x02043E68
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x8
	ldr r0, [r5, #0xc]
	bl SavArray_get
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	add r2, r0, #0x0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl MOD05_DayCare_GiveEggToPlayer
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_420
ScrCmd_unk_420: ; 0x02043E9C
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xf
	add r0, r5, #0x0
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	ldr r6, [r5, #0xc]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x8
	bl SavArray_get
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	lsl r3, r4, #0x18
	ldr r1, [r7, #0x0]
	add r2, r6, #0x0
	lsr r3, r3, #0x18
	bl MOD05_021EC71C
	ldr r1, [sp, #0x0]
	strh r0, [r1, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_426
ScrCmd_unk_426: ; 0x02043EFC
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xf
	add r0, r5, #0x0
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	ldr r5, [r5, #0xc]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x8
	bl SavArray_get
	lsl r1, r4, #0x18
	ldr r2, [r7, #0x0]
	lsr r1, r1, #0x18
	bl MOD05_021EC854
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_430
ScrCmd_unk_430: ; 0x02043F50
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	ldr r4, [r0, #0xc]
	bl FUN_02039438
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
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x8
	bl SavArray_get
	ldr r2, [r6, #0x0]
	add r1, r5, #0x0
	bl MOD05_021EC864
	strh r0, [r7, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_431
ScrCmd_unk_431: ; 0x02043FA0
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xf
	add r0, r5, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
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
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	ldr r2, [r6, #0x0]
	add r1, r7, #0x0
	bl MOD05_021ED5C4
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_432
ScrCmd_unk_432: ; 0x02043FF4
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r1, r6, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	ldr r5, [r4, #0xc]
	bl ScriptReadHalfword
	add r6, #0x80
	add r1, r0, #0x0
	ldr r0, [r6, #0x0]
	bl VarGet
	add r6, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_PlayerParty_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x8
	bl SavArray_get
	lsl r1, r6, #0x18
	add r2, r0, #0x0
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	add r3, r5, #0x0
	bl MOD05_021EC57C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_444
ScrCmd_unk_444: ; 0x02044034
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	ldr r5, [r0, #0xc]
	bl FUN_02039438
	add r6, r0, #0x0
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
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl Sav2_DayCare_get
	lsl r1, r4, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x0]
	ldr r1, [r6, #0x0]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	str r1, [sp, #0x4]
	lsl r1, r7, #0x18
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl MOD05_021ED52C
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_446
ScrCmd_unk_446: ; 0x020440C0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x8
	bl SavArray_get
	bl MOD05_021ED644
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_447
ScrCmd_unk_447: ; 0x020440F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x8
	bl SavArray_get
	bl Sav2_DayCare_GetEggPID
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_421
ScrCmd_unk_421: ; 0x02044120
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_422
ScrCmd_unk_422: ; 0x02044138
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_unk_423
ScrCmd_unk_423: ; 0x0204413C
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_unk_429
ScrCmd_unk_429: ; 0x02044140
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
