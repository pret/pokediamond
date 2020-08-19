    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02045D88
FUN_02045D88: ; 0x02045D88
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
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r1, r5, #0x0
	add r1, #0x80
	lsl r2, r4, #0x18
	add r6, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	lsr r2, r2, #0x18
	bl FUN_02037CF0
	str r0, [r6, #0x0]
	ldr r1, _02045DCC ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	nop
_02045DCC: .word FUN_0203BC04

	thumb_func_start FUN_02045DD0
FUN_02045DD0: ; 0x02045DD0
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
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02045DFC
	bl ErrorHandling
_02045DFC:
	ldr r0, [r4, #0x0]
	bl FUN_02037D5C
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x4
	bne _02045E0E
	mov r0, #0xff
	strh r0, [r5, #0x0]
_02045E0E:
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02045E1C
FUN_02045E1C: ; 0x02045E1C
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02045E20
FUN_02045E20: ; 0x02045E20
	push {r4-r6, lr}
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
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x20
	bl FUN_02088DF8
	add r5, r0, #0x0
	bl FUN_02088EF8
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02045E74
FUN_02045E74: ; 0x02045E74
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	add r7, r1, #0x0
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	str r2, [sp, #0x0]
	add r6, r3, #0x0
	bl FUN_02039438
	str r0, [sp, #0x4]
	mov r0, #0x20
	bl FUN_02088DD8
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	str r4, [r0, #0x0]
	ldr r0, [sp, #0x0]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r4, #0x8]
	str r6, [r4, #0xc]
	add r0, r5, #0x0
	strb r7, [r4, #0x15]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_02038864
	ldr r1, _02045EDC ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	add r0, r6, #0x0
	bl FreeToHeap
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02045EDC: .word FUN_0203BC04

	thumb_func_start FUN_02045EE0
FUN_02045EE0: ; 0x02045EE0
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_02045EE4
FUN_02045EE4: ; 0x02045EE4
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
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	add r4, r0, #0x0
	mov r1, #0x20
	bl FUN_02088DF8
	add r3, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x1
	add r2, r4, #0x0
	bl FUN_02045E74
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_02045F24
FUN_02045F24: ; 0x02045F24
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
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	add r6, r0, #0x0
	mov r0, #0x20
	mov r1, #0x4
	bl AllocFromHeap
	add r3, r0, #0x0
	ldr r0, _02045F80 ; =0x0000FFFF
	strh r4, [r3, #0x0]
	strh r0, [r3, #0x2]
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02045E74
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_02045F80: .word 0x0000FFFF

	thumb_func_start FUN_02045F84
FUN_02045F84: ; 0x02045F84
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02045F88
FUN_02045F88: ; 0x02045F88
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
	mov r1, #0x13
	bl FUN_02039438
	ldr r4, [r0, #0x0]
	cmp r4, #0x0
	bne _02045FB2
	bl ErrorHandling
_02045FB2:
	ldrb r0, [r4, #0x16]
	cmp r0, #0x0
	bne _02045FBC
	mov r0, #0x0
	b _02045FBE
_02045FBC:
	mov r0, #0xff
_02045FBE:
	strh r0, [r5, #0x0]
	add r0, r4, #0x0
	bl FUN_02088DF0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02045FCC
FUN_02045FCC: ; 0x02045FCC
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
	mov r1, #0x13
	bl FUN_02039438
	ldr r4, [r0, #0x0]
	cmp r4, #0x0
	bne _02045FF6
	bl ErrorHandling
_02045FF6:
	ldrb r0, [r4, #0x16]
	cmp r0, #0x0
	bne _02046000
	mov r0, #0x0
	b _02046002
_02046000:
	mov r0, #0xff
_02046002:
	strh r0, [r5, #0x0]
	add r0, r4, #0x0
	bl FUN_02088DF0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
