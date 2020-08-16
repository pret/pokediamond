    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start MonNotFaintedOrEgg
MonNotFaintedOrEgg: ; 0x0204A01C
	push {r4, lr}
	mov r1, #0xa2
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _0204A030
	mov r0, #0x0
	pop {r4, pc}
_0204A030:
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _0204A042
	mov r0, #0x1
	pop {r4, pc}
_0204A042:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start GiveMon
GiveMon: ; 0x0204A048
	push {r3-r7, lr}
	sub sp, #0x20
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x10]
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [sp, #0x14]
	add r0, r6, #0x0
	bl SavArray_PlayerParty_get
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	bl AllocMonZeroed
	add r4, r0, #0x0
	bl ZeroMonData
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r2, [sp, #0x10]
	add r0, r4, #0x0
	add r1, r7, #0x0
	mov r3, #0x20
	bl CreateMon
	ldr r0, [sp, #0x40]
	ldr r1, [sp, #0x14]
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x3c]
	add r0, r4, #0x0
	mov r2, #0x4
	str r5, [sp, #0x4]
	bl FUN_0206A014
	add r0, sp, #0x28
	ldrh r0, [r0, #0x10]
	mov r1, #0x6
	add r2, sp, #0x1c
	str r0, [sp, #0x1c]
	add r0, r4, #0x0
	bl SetMonData
	ldr r0, [sp, #0x18]
	add r1, r4, #0x0
	bl AddMonToParty
	add r5, r0, #0x0
	beq _0204A0BC
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0202C144
_0204A0BC:
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start GiveEgg
GiveEgg: ; 0x0204A0C8
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r0, r4, #0x0
	add r5, r2, #0x0
	add r7, r3, #0x0
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl SavArray_PlayerParty_get
	add r6, r0, #0x0
	mov r0, #0x20
	bl AllocMonZeroed
	add r4, r0, #0x0
	bl ZeroMonData
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x24]
	bl FUN_02015CF8
	mov r1, #0x4
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r3, [sp, #0x8]
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl MOD05_SetEggStats
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl AddMonToParty
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start PartyMonSetMoveInSlot
PartyMonSetMoveInSlot: ; 0x0204A120
	push {r3-r5, lr}
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl GetPartyMonByIndex
	lsl r2, r5, #0x18
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	bl MonSetMoveInSlot
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start GetIdxOfFirstPartyMonWithMove
GetIdxOfFirstPartyMonWithMove: ; 0x0204A138
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	add r5, r1, #0x0
	bl GetPartyCount
	add r7, r0, #0x0
	mov r6, #0x0
	cmp r7, #0x0
	ble _0204A1A2
_0204A14A:
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _0204A19C
	add r0, r4, #0x0
	mov r1, #0x36
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	beq _0204A198
	add r0, r4, #0x0
	mov r1, #0x37
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	beq _0204A198
	add r0, r4, #0x0
	mov r1, #0x38
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	beq _0204A198
	add r0, r4, #0x0
	mov r1, #0x39
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	bne _0204A19C
_0204A198:
	add r0, r6, #0x0
	pop {r3-r7, pc}
_0204A19C:
	add r6, r6, #0x1
	cmp r6, r7
	blt _0204A14A
_0204A1A2:
	mov r0, #0xff
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start CountAlivePokemon
CountAlivePokemon: ; 0x0204A1A8
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl GetPartyCount
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
	cmp r6, #0x0
	ble _0204A1D2
_0204A1BA:
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	bl MonNotFaintedOrEgg
	cmp r0, #0x0
	beq _0204A1CC
	add r5, r5, #0x1
_0204A1CC:
	add r4, r4, #0x1
	cmp r4, r6
	blt _0204A1BA
_0204A1D2:
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start GetFirstAliveMonInParty_CrashIfNone
GetFirstAliveMonInParty_CrashIfNone: ; 0x0204A1D8
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl GetPartyCount
	add r5, r0, #0x0
	mov r4, #0x0
	cmp r5, #0x0
	ble _0204A204
_0204A1E8:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	add r7, r0, #0x0
	bl MonNotFaintedOrEgg
	cmp r0, #0x0
	beq _0204A1FE
	add r0, r7, #0x0
	pop {r3-r7, pc}
_0204A1FE:
	add r4, r4, #0x1
	cmp r4, r5
	blt _0204A1E8
_0204A204:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start GetFirstNonEggInParty
GetFirstNonEggInParty: ; 0x0204A20C
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl GetPartyCount
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r4, _0204A244 ; =0x00000000
	beq _0204A240
_0204A21C:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r7, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _0204A236
	add r0, r7, #0x0
	pop {r3-r7, pc}
_0204A236:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r5
	blo _0204A21C
_0204A240:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0204A244: .word 0x00000000

	thumb_func_start HasEnoughAlivePokemonForDoubleBattle
HasEnoughAlivePokemonForDoubleBattle: ; 0x0204A248
	push {r3, lr}
	bl CountAlivePokemon
	cmp r0, #0x2
	blt _0204A256
	mov r0, #0x1
	pop {r3, pc}
_0204A256:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start GiveAllMonsTheSinnohChampRibbon
GiveAllMonsTheSinnohChampRibbon: ; 0x0204A25C
	push {r3-r7, lr}
	mov r2, #0x1
	add r1, sp, #0x0
	add r7, r0, #0x0
	strb r2, [r1, #0x0]
	bl GetPartyCount
	add r6, r0, #0x0
	mov r5, #0x0
	cmp r6, #0x0
	ble _0204A298
_0204A272:
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _0204A292
	add r0, r4, #0x0
	mov r1, #0x19
	add r2, sp, #0x0
	bl SetMonData
_0204A292:
	add r5, r5, #0x1
	cmp r5, r6
	blt _0204A272
_0204A298:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ApplyPoisonStep
ApplyPoisonStep: ; 0x0204A29C
	push {r3-r7, lr}
	sub sp, #0x10
	mov r7, #0x0
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r6, r7, #0x0
	bl GetPartyCount
	add r4, r7, #0x0
	str r0, [sp, #0x8]
	cmp r0, #0x0
	ble _0204A310
_0204A2B4:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	add r5, r0, #0x0
	bl MonNotFaintedOrEgg
	cmp r0, #0x0
	beq _0204A308
	add r0, r5, #0x0
	mov r1, #0x9f
	mov r2, #0x0
	bl GetMonData
	mov r1, #0x88
	tst r0, r1
	beq _0204A308
	add r0, r5, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0xc]
	cmp r0, #0x1
	bls _0204A2EA
	sub r0, r0, #0x1
	str r0, [sp, #0xc]
_0204A2EA:
	add r0, r5, #0x0
	mov r1, #0xa2
	add r2, sp, #0xc
	bl SetMonData
	ldr r0, [sp, #0xc]
	cmp r0, #0x1
	bne _0204A306
	ldr r2, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x7
	add r6, r6, #0x1
	bl MonApplyFriendshipMod
_0204A306:
	add r7, r7, #0x1
_0204A308:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	cmp r4, r0
	blt _0204A2B4
_0204A310:
	cmp r6, #0x0
	beq _0204A31A
	add sp, #0x10
	mov r0, #0x2
	pop {r3-r7, pc}
_0204A31A:
	cmp r7, #0x0
	beq _0204A324
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_0204A324:
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start SurvivePoisoning
SurvivePoisoning: ; 0x0204A32C
	push {r3-r4, lr}
	sub sp, #0x4
	mov r1, #0x9f
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	mov r1, #0x88
	tst r0, r1
	beq _0204A362
	add r0, r4, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x1
	bne _0204A362
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x9f
	add r2, sp, #0x0
	bl SetMonData
	add sp, #0x4
	mov r0, #0x1
	pop {r3-r4, pc}
_0204A362:
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r4, pc}
