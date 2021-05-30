    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start ScrCmd_GetPartySpecies
ScrCmd_GetPartySpecies: ; 0x0204434C
	; getpartyspecies XXXX, YYYY
	; Sets var YYYY to species of mon in party slot XXXX.
	; If mon is an egg, the value is SPECIES_NONE.
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
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
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	ldrh r1, [r6, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r5, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _020443A0
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	b _020443A2
_020443A0:
	mov r0, #0x0
_020443A2:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_CheckPartyMonOTID
ScrCmd_CheckPartyMonOTID: ; 0x020443A8
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	add r0, r5, #0x0
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	add r7, r0, #0x0
	add r0, r4, #0x0
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
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	ldrh r1, [r6, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0x7
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r7, #0x0
	bl PlayerProfile_GetTrainerID
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r5, r0
	bne _0204440C
	mov r0, #0x0
	b _0204440E
_0204440C:
	mov r0, #0x1
_0204440E:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_GiveEgg
ScrCmd_GiveEgg: ; 0x02044414
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	ldr r0, [r4, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	add r7, r0, #0x0
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
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_PlayerParty_get
	add r6, r0, #0x0
	bl GetPartyCount
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x6
	bhs _02044494
	mov r0, #0xb
	bl AllocMonZeroed
	add r4, r0, #0x0
	bl ZeroMonData
	mov r0, #0x1
	add r1, r5, #0x0
	bl FUN_02015CF8
	mov r1, #0x3
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r1, [sp, #0x8]
	add r0, r4, #0x0
	mov r2, #0x1
	add r3, r7, #0x0
	bl MOD05_SetEggStats
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl AddMonToParty
	add r0, r4, #0x0
	bl FreeToHeap
_02044494:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_SetPartyMonMove
ScrCmd_SetPartyMonMove: ; 0x0204449C
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
	bl SavArray_PlayerParty_get
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl PartyMonSetMoveInSlot
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_PartyMonHasMove
ScrCmd_PartyMonHasMove: ; 0x020444F4
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
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
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r4, r0, #0x0
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	mov r2, #0x0
	mov r1, #0x4c
	add r4, r0, #0x0
	strh r2, [r6, #0x0]
	bl GetMonData
	cmp r0, #0x0
	beq _02044556
	mov r0, #0x0
	pop {r3-r7, pc}
_02044556:
	add r0, r4, #0x0
	mov r1, #0x36
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	beq _0204458E
	add r0, r4, #0x0
	mov r1, #0x37
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	beq _0204458E
	add r0, r4, #0x0
	mov r1, #0x38
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	beq _0204458E
	add r0, r4, #0x0
	mov r1, #0x39
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	bne _02044592
_0204458E:
	mov r0, #0x1
	strh r0, [r6, #0x0]
_02044592:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_FindPartyMonWithMove
ScrCmd_FindPartyMonWithMove: ; 0x02044598
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x4]
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
	add r5, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r1, _02044650 ; =0x00000006
	ldr r0, [sp, #0x0]
	ldr r6, _02044654 ; =0x00000000
	strh r1, [r0, #0x0]
	beq _02044648
_020445E4:
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _0204463E
	add r0, r4, #0x0
	mov r1, #0x36
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	beq _02044638
	add r0, r4, #0x0
	mov r1, #0x37
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	beq _02044638
	add r0, r4, #0x0
	mov r1, #0x38
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	beq _02044638
	add r0, r4, #0x0
	mov r1, #0x39
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	bne _0204463E
_02044638:
	ldr r0, [sp, #0x0]
	strh r6, [r0, #0x0]
	b _02044648
_0204463E:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, r7
	blo _020445E4
_02044648:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02044650: .word 0x00000006
_02044654: .word 0x00000000

	thumb_func_start ScrCmd_SurvivePsn
ScrCmd_SurvivePsn: ; 0x02044658
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
	bl SurvivePoisoning
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_CountPartyMonsAtOrBelowLevel
ScrCmd_CountPartyMonsAtOrBelowLevel: ; 0x0204469C
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	mov r4, #0x0
	ldr r0, [sp, #0x4]
	add r5, r4, #0x0
	strh r4, [r0, #0x0]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bls _02044726
_020446EA:
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r6, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _0204471A
	add r0, r6, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bhi _0204471A
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
_0204471A:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x8]
	cmp r4, r0
	blo _020446EA
_02044726:
	ldr r0, [sp, #0x4]
	strh r5, [r0, #0x0]
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start ScrCmd_GetPartyMonLevel
ScrCmd_GetPartyMonLevel: ; 0x02044730
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r5, r0, #0x0
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r2, #0x0
	mov r1, #0x4c
	add r5, r0, #0x0
	strh r2, [r4, #0x0]
	bl GetMonData
	cmp r0, #0x0
	bne _02044786
	add r0, r5, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	strh r0, [r4, #0x0]
_02044786:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_GetPartyMonNature
ScrCmd_GetPartyMonNature: ; 0x0204478C
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r1, r6, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl ScriptReadHalfword
	add r6, #0x80
	add r1, r0, #0x0
	ldr r0, [r6, #0x0]
	bl VarGet
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r6, r0
	blt _020447D2
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_020447D2:
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r5, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _020447F2
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_020447F2:
	add r0, r5, #0x0
	bl GetMonNature
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_FindPartyMonWithNature
ScrCmd_FindPartyMonWithNature: ; 0x02044800
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r1, _02044884 ; =0x000000FF
	ldr r0, [sp, #0x4]
	ldr r5, _02044888 ; =0x00000000
	strh r1, [r0, #0x0]
	beq _0204487E
_02044848:
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _02044874
	add r0, r4, #0x0
	bl GetMonNature
	ldr r1, [sp, #0x0]
	cmp r1, r0
	bne _02044874
	ldr r0, [sp, #0x4]
	strh r5, [r0, #0x0]
	b _0204487E
_02044874:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r6
	blo _02044848
_0204487E:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02044884: .word 0x000000FF
_02044888: .word 0x00000000

	thumb_func_start ScrCmd_GetPartyMonFriendship
ScrCmd_GetPartyMonFriendship: ; 0x0204488C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
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
	bl VarGet
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x9
	mov r2, #0x0
	bl GetMonData
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_Unk01BA
ScrCmd_Unk01BA: ; 0x020448D4
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
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
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0, #0x0]
	bl MapHeader_GetMapSec
	add r7, r0, #0x0
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	ldr r1, [sp, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0x9
	mov r2, #0x0
	add r5, r0, #0x0
	bl GetMonData
	add r1, sp, #0x4
	strh r0, [r1, #0x0]
	cmp r4, #0x0
	beq _02044982
	add r0, r5, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x1
	mov r2, #0xb
	bl GetItemAttr
	cmp r0, #0x34
	bne _0204495A
	mov r0, #0x96
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0204495A:
	add r0, r5, #0x0
	mov r1, #0x9a
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0xb
	bne _0204496E
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0204496E:
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	cmp r7, r0
	bne _02044982
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02044982:
	add r0, sp, #0x4
	ldrh r1, [r0, #0x0]
	add r1, r1, r4
	strh r1, [r0, #0x0]
	ldrh r1, [r0, #0x0]
	cmp r1, #0xff
	bls _02044994
	mov r1, #0xff
	strh r1, [r0, #0x0]
_02044994:
	add r0, r5, #0x0
	mov r1, #0x9
	add r2, sp, #0x4
	bl SetMonData
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_Unk01BB
ScrCmd_Unk01BB: ; 0x020449A4
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
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
	bl VarGet
	add r5, r0, #0x0
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x9
	mov r2, #0x0
	add r5, r0, #0x0
	bl GetMonData
	add r1, sp, #0x0
	strh r0, [r1, #0x0]
	ldrh r0, [r1, #0x0]
	cmp r4, r0
	bls _020449F8
	mov r0, #0x0
	b _020449FA
_020449F8:
	sub r0, r0, r4
_020449FA:
	strh r0, [r1, #0x0]
	add r0, r5, #0x0
	mov r1, #0x9
	add r2, sp, #0x0
	bl SetMonData
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start ScrCmd_Unk0281
ScrCmd_Unk0281: ; 0x02044A0C
	push {r3-r7, lr}
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
	add r4, r0, #0x0
	add r0, r5, #0x0
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
	bl SavArray_PlayerParty_get
	add r1, r7, #0x0
	bl GetPartyMonByIndex
	add r4, #0x13
	add r1, r4, #0x0
	mov r2, #0x0
	bl GetMonData
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0247
ScrCmd_Unk0247: ; 0x02044A6C
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
	bl FUN_02054DEC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0248
ScrCmd_Unk0248: ; 0x02044A94
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
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
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	add r4, r0, #0x0
	mov r1, #0xb0
	mov r2, #0x0
	bl GetMonData
	strh r0, [r6, #0x0]
	add r0, r4, #0x0
	mov r1, #0xb1
	mov r2, #0x0
	bl GetMonData
	strh r0, [r7, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0177
ScrCmd_Unk0177: ; 0x02044B00
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
	ldr r0, [r4, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk019A
ScrCmd_Unk019A: ; 0x02044B2C
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	mov r5, #0x0
	add r7, r0, #0x0
	add r4, r5, #0x0
	cmp r7, #0x0
	ble _02044B7A
_02044B5A:
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _02044B74
	add r4, r4, #0x1
_02044B74:
	add r5, r5, #0x1
	cmp r5, r7
	blt _02044B5A
_02044B7A:
	ldr r0, [sp, #0x0]
	strh r4, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk019B
ScrCmd_Unk019B: ; 0x02044B84
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	mov r5, #0x0
	add r4, r5, #0x0
	str r0, [sp, #0x8]
	cmp r0, #0x0
	ble _02044C00
_02044BC8:
	ldr r0, [sp, #0x0]
	cmp r5, r0
	beq _02044BF8
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r6, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _02044BF8
	add r0, r6, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02044BF8
	add r4, r4, #0x1
_02044BF8:
	ldr r0, [sp, #0x8]
	add r5, r5, #0x1
	cmp r5, r0
	blt _02044BC8
_02044C00:
	ldr r0, [sp, #0x4]
	strh r4, [r0, #0x0]
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk019C
ScrCmd_Unk019C: ; 0x02044C0C
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	ldr r0, [r7, #0xc]
	bl GetStoragePCPointer
	str r0, [sp, #0x4]
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	mov r5, #0x0
	add r4, r5, #0x0
	str r0, [sp, #0x8]
	cmp r0, #0x0
	ble _02044C76
_02044C44:
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r6, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _02044C6E
	add r0, r6, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02044C6E
	add r4, r4, #0x1
_02044C6E:
	ldr r0, [sp, #0x8]
	add r5, r5, #0x1
	cmp r5, r0
	blt _02044C44
_02044C76:
	ldr r0, [sp, #0x4]
	bl PCStorage_CountMonsInAllBoxes
	add r1, r4, r0
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start ScrCmd_Unk019D
ScrCmd_Unk019D: ; 0x02044C88
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	mov r5, #0x0
	add r7, r0, #0x0
	add r4, r5, #0x0
	cmp r7, #0x0
	ble _02044CD6
_02044CB6:
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02044CD0
	add r4, r4, #0x1
_02044CD0:
	add r5, r5, #0x1
	cmp r5, r7
	blt _02044CB6
_02044CD6:
	ldr r0, [sp, #0x0]
	strh r4, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0119
ScrCmd_Unk0119: ; 0x02044CE0
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r4, _02044D40 ; =0x00000000
	ldr r0, [sp, #0x0]
	strh r4, [r0, #0x0]
	beq _02044D3C
	mov r7, #0x99
_02044D12:
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	add r1, r7, #0x0
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02044D32
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	strh r1, [r0, #0x0]
	b _02044D3C
_02044D32:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r6
	blo _02044D12
_02044D3C:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02044D40: .word 0x00000000

	thumb_func_start ScrCmd_Unk011A
ScrCmd_Unk011A: ; 0x02044D44
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
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x6f
	mov r2, #0x0
	bl GetMonData
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_Unk01C8
ScrCmd_Unk01C8: ; 0x02044D8C
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
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
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r6, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02044DDA
	mov r0, #0x0
	strh r0, [r5, #0x0]
	pop {r4-r6, pc}
_02044DDA:
	mov r4, #0x0
	add r0, r6, #0x0
	mov r1, #0x36
	add r2, r4, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02044DF0
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02044DF0:
	add r0, r6, #0x0
	mov r1, #0x37
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02044E04
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02044E04:
	add r0, r6, #0x0
	mov r1, #0x38
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02044E18
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02044E18:
	add r0, r6, #0x0
	mov r1, #0x39
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02044E2C
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02044E2C:
	strh r4, [r5, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk01C9
ScrCmd_Unk01C9: ; 0x02044E34
	push {r4-r6, lr}
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
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	add r1, r4, #0x0
	bl FUN_020699A4
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_Unk01CA
ScrCmd_Unk01CA: ; 0x02044E78
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
	bl GetVarPointer
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
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r7, #0x0
	bl GetPartyMonByIndex
	add r4, #0x36
	add r1, r4, #0x0
	mov r2, #0x0
	bl GetMonData
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk01EE
ScrCmd_Unk01EE: ; 0x02044ED8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
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
	bl VarGet
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x6
	mov r2, #0x0
	bl GetMonData
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_Unk01F0
ScrCmd_Unk01F0: ; 0x02044F20
	push {r3-r5, lr}
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
	ldr r0, [r4, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r2, #0x0
	add r1, sp, #0x0
	strh r2, [r1, #0x0]
	mov r1, #0x6
	add r2, sp, #0x0
	bl SetMonData
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Unk01C0
ScrCmd_Unk01C0: ; 0x02044F58
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r5, _02044FE4 ; =0x00000000
	ldr r0, [sp, #0x4]
	strh r5, [r0, #0x0]
	beq _02044FDE
_02044F9E:
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _02044FD4
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [sp, #0x0]
	cmp r0, r1
	bne _02044FD4
	ldr r0, [sp, #0x4]
	mov r1, #0x1
	strh r1, [r0, #0x0]
	b _02044FDE
_02044FD4:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r6
	blo _02044F9E
_02044FDE:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02044FE4: .word 0x00000000

	thumb_func_start ScrCmd_Unk022E
ScrCmd_Unk022E: ; 0x02044FE8
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	add r0, r5, #0x0
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
	bl SavArray_PlayerParty_get
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	mov r4, #0x0
	add r6, r0, #0x0
	add r5, r4, #0x0
	add r7, r4, #0x0
_0204502A:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	add r1, r7, #0x0
	bl FUN_0207FC5C
	add r1, r0, #0x0
	add r0, r6, #0x0
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02045048
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_02045048:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x50
	blo _0204502A
	ldr r0, [sp, #0x0]
	strh r5, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk022F
ScrCmd_Unk022F: ; 0x0204505C
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	lsl r0, r0, #0x10
	add r4, #0x80
	lsr r6, r0, #0x10
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x8]
	str r0, [sp, #0x4]
_0204509A:
	mov r5, #0x0
	cmp r6, #0x0
	bls _020450E8
	ldr r0, [sp, #0x8]
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
_020450A6:
	ldr r0, [sp, #0xc]
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _020450E8
	add r0, r7, #0x0
	mov r1, #0x0
	bl FUN_0207FC5C
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _020450DE
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	b _020450E8
_020450DE:
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, r6
	blo _020450A6
_020450E8:
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x8]
	cmp r0, #0x50
	blo _0204509A
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0230
ScrCmd_Unk0230: ; 0x02045104
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
	add r1, r7, #0x0
	bl GetPartyMonByIndex
	add r5, r0, #0x0
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	mov r1, #0x0
	bl FUN_0207FC5C
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x0
	bl GetMonData
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0231
ScrCmd_Unk0231: ; 0x02045170
	push {r3-r6, lr}
	sub sp, #0x4
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
	mov r1, #0x1
	add r0, sp, #0x0
	add r5, #0x80
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	add r5, r0, #0x0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	mov r1, #0x0
	bl FUN_0207FC5C
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r2, sp, #0x0
	bl SetMonData
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk02B7
ScrCmd_Unk02B7: ; 0x020451D0
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	bl GetPartyCount
	lsl r0, r0, #0x10
	add r4, #0x80
	lsr r6, r0, #0x10
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x4]
_0204520C:
	mov r5, #0x0
	cmp r6, #0x0
	bls _0204524C
_02045212:
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02045242
	add r0, r4, #0x0
	mov r1, #0x3
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02045242
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	strh r1, [r0, #0x0]
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_02045242:
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, r6
	blo _02045212
_0204524C:
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	cmp r0, #0x50
	blo _0204520C
	ldr r1, [sp, #0x0]
	mov r0, #0x0
	strh r0, [r1, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_Unk00A0
ScrCmd_Unk00A0: ; 0x02045264
	mov r0, #0x0
	bx lr
