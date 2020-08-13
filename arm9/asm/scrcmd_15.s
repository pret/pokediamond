    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02043C6C
FUN_02043C6C: ; 0x02043C6C
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl Sav2_PlayerData_GetProfileAddr
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadWord
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl PlayerProfile_AddMoney
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02043C90
FUN_02043C90: ; 0x02043C90
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl Sav2_PlayerData_GetProfileAddr
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadWord
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl PlayerProfile_SubMoney
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02043CB4
FUN_02043CB4: ; 0x02043CB4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl Sav2_PlayerData_GetProfileAddr
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl PlayerProfile_SubMoney
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02043CE4
FUN_02043CE4: ; 0x02043CE4
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl Sav2_PlayerData_GetProfileAddr
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadWord
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl PlayerProfile_GetMoney
	cmp r0, r4
	bhs _02043D20
	mov r0, #0x0
	b _02043D22
_02043D20:
	mov r0, #0x1
_02043D22:
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02043D28
FUN_02043D28: ; 0x02043D28
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl Sav2_PlayerData_GetProfileAddr
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl PlayerProfile_GetMoney
	cmp r0, r4
	bhs _02043D6E
	mov r0, #0x0
	b _02043D70
_02043D6E:
	mov r0, #0x1
_02043D70:
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02043D78
FUN_02043D78: ; 0x02043D78
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x27
	bl FUN_02039438
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl MOD05_021E27E8
	str r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02043DC8
FUN_02043DC8: ; 0x02043DC8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x27
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD05_021E288C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02043DE0
FUN_02043DE0: ; 0x02043DE0
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x27
	bl FUN_02039438
	add r1, r0, #0x0
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	bl MOD05_021E28A0
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
