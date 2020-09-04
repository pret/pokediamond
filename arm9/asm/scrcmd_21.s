    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020F4574
UNK_020F4574: ; 0x020F4574
	.byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07

	.text

	thumb_func_start ScrCmd_unk_343
ScrCmd_unk_343: ; 0x020453F4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl Pokedex_GetSinnohDexFlag
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_344
ScrCmd_unk_344: ; 0x02045424
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	bl Pokedex_SetSinnohDexFlag
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_345
ScrCmd_unk_345: ; 0x02045438
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
	bl FUN_02034E30
	bl FUN_02034E20
	bl FUN_02055474
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_346
ScrCmd_unk_346: ; 0x02045468
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034E20
	mov r1, #0x1
	bl FUN_02055488
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_347
ScrCmd_unk_347: ; 0x02045484
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
	bl GetVarPointer
	add r6, r0, #0x0
	cmp r4, #0x8
	blo _020454B6
	bl ErrorHandling
_020454B6:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	add r1, r4, #0x0
	bl PlayerProfile_TestBadgeFlag
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_348
ScrCmd_unk_348: ; 0x020454CC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	cmp r4, #0x8
	blo _020454EA
	bl ErrorHandling
_020454EA:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	add r1, r4, #0x0
	bl PlayerProfile_SetBadgeFlag
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_350
ScrCmd_unk_350: ; 0x02045500
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
	bl SavArray_Flags_get
	bl FUN_0205ECE0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_349
ScrCmd_unk_349: ; 0x0204552C
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	mov r4, #0x0
	ldr r7, _02045578 ; =UNK_020F4574
	str r0, [sp, #0x0]
	add r5, r4, #0x0
_02045548:
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	ldrb r1, [r7, r4]
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0x1
	bne _02045564
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_02045564:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x8
	blo _02045548
	ldr r0, [sp, #0x0]
	strh r5, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02045578: .word UNK_020F4574

	thumb_func_start ScrCmd_unk_351
ScrCmd_unk_351: ; 0x0204557C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205ECD4
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_352
ScrCmd_unk_352: ; 0x02045590
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
	bl SavArray_Flags_get
	bl FUN_0205ED3C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_353
ScrCmd_unk_353: ; 0x020455BC
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205ED1C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_354
ScrCmd_unk_354: ; 0x020455D0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205ED2C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_355
ScrCmd_unk_355: ; 0x020455E4
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
	bl SavArray_Flags_get
	bl FUN_0205ED6C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_356
ScrCmd_unk_356: ; 0x02045610
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205ED4C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_357
ScrCmd_unk_357: ; 0x02045624
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205ED5C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_358
ScrCmd_unk_358: ; 0x02045638
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
	bl SavArray_Flags_get
	bl FUN_0205ED0C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_359
ScrCmd_unk_359: ; 0x02045664
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205ECFC
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_463
ScrCmd_unk_463: ; 0x02045678
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	ldr r2, [r5, #0x8]
	add r4, r0, #0x0
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	beq _020456A6
	cmp r1, #0x1
	beq _0204569E
	cmp r1, #0x2
	beq _020456AE
	b _020456CC
_0204569E:
	mov r1, #0x1
	bl FUN_0205F264
	b _020456D0
_020456A6:
	mov r1, #0x0
	bl FUN_0205F264
	b _020456D0
_020456AE:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0205F264
	strh r0, [r5, #0x0]
	b _020456D0
_020456CC:
	bl ErrorHandling
_020456D0:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_464
ScrCmd_unk_464: ; 0x020456D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	ldr r2, [r5, #0x8]
	add r4, r0, #0x0
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	beq _02045700
	cmp r1, #0x1
	beq _020456FA
	cmp r1, #0x2
	beq _02045706
	b _02045722
_020456FA:
	bl FUN_0205F274
	b _02045726
_02045700:
	bl FUN_0205F284
	b _02045726
_02045706:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F294
	strh r0, [r5, #0x0]
	b _02045726
_02045722:
	bl ErrorHandling
_02045726:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_465
ScrCmd_unk_465: ; 0x0204572C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	ldr r2, [r5, #0x8]
	add r4, r0, #0x0
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	beq _02045758
	cmp r1, #0x1
	beq _02045752
	cmp r1, #0x2
	beq _0204575E
	b _0204577A
_02045752:
	bl FUN_0205F2A4
	b _0204577E
_02045758:
	bl FUN_0205F2B4
	b _0204577E
_0204575E:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F2C4
	strh r0, [r5, #0x0]
	b _0204577E
_0204577A:
	bl ErrorHandling
_0204577E:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
