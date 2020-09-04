    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start ScrCmd_unk_381
ScrCmd_unk_381: ; 0x02042B0C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r1, r0, #0x0
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r1, [r1, #0x0]
	bl FUN_0204B5FC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_382
ScrCmd_unk_382: ; 0x02042B40
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
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
	ldr r1, [r4, #0x0]
	bl FUN_0204B63C
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_383
ScrCmd_unk_383: ; 0x02042B74
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
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
	ldr r1, [r4, #0x0]
	bl FUN_0204B660
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_384
ScrCmd_unk_384: ; 0x02042BA8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
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
	ldr r1, [r4, #0x0]
	bl FUN_0204B684
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_385
ScrCmd_unk_385: ; 0x02042BDC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
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
	ldr r1, [r4, #0x0]
	bl FUN_0204B6A4
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_386
ScrCmd_unk_386: ; 0x02042C10
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_0204B57C
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_387
ScrCmd_unk_387: ; 0x02042C44
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_0204B5A8
	add r0, r6, #0x0
	mov r1, #0x3
	bl FUN_0202A0E8
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_388
ScrCmd_unk_388: ; 0x02042C8C
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	cmp r0, #0x0
	beq _02042C9E
	cmp r0, #0x1
	beq _02042CA8
	b _02042CB2
_02042C9E:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_0204B9A0
	b _02042CB6
_02042CA8:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_0204B9CC
	b _02042CB6
_02042CB2:
	bl ErrorHandling
_02042CB6:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_389
ScrCmd_unk_389: ; 0x02042CBC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r1, r0, #0x0
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r1, [r1, #0x0]
	bl FUN_0204B4FC
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0202A170
	mov r0, #0x0
	pop {r3-r5, pc}
