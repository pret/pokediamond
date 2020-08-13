    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020F4264
UNK_020F4264: ; 0x020F4264
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020F4268
UNK_020F4268: ; 0x020F4268
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020F426C
UNK_020F426C: ; 0x020F426C
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020F4270
UNK_020F4270: ; 0x020F4270
	.byte 0x03, 0x00, 0x00, 0x00, 0xCD, 0x1B, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0xF5, 0x22, 0x04, 0x02
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x5D, 0x1C, 0x06, 0x02, 0x89, 0x22, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x4D, 0x1D, 0x06, 0x02, 0xA9, 0x22, 0x04, 0x02, 0x05, 0x23, 0x04, 0x02
	.byte 0x08, 0x00, 0x00, 0x00, 0xA5, 0x1D, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x15, 0x23, 0x04, 0x02
	.byte 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x7D, 0x1E, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x25, 0x23, 0x04, 0x02
	.byte 0x0B, 0x00, 0x00, 0x00, 0xF9, 0x1E, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x2D, 0x1F, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x35, 0x23, 0x04, 0x02
	.byte 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0E, 0x00, 0x00, 0x00, 0xBD, 0x1F, 0x06, 0x02, 0xC1, 0x22, 0x04, 0x02, 0x45, 0x23, 0x04, 0x02
	.byte 0x0F, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_02041E40
FUN_02041E40: ; 0x02041E40
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	cmp r0, #0x6
	bls _02041E4E
	b _02041FD2
_02041E4E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02041E5A: ; jump table (using 16-bit offset)
	.short _02041E68 - _02041E5A - 2; case 0
	.short _02041E88 - _02041E5A - 2; case 1
	.short _02041F24 - _02041E5A - 2; case 2
	.short _02041ECA - _02041E5A - 2; case 3
	.short _02041F2E - _02041E5A - 2; case 4
	.short _02041F68 - _02041E5A - 2; case 5
	.short _02041FB4 - _02041E5A - 2; case 6
_02041E68:
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
	bl MOD06_02248CD0
	strh r0, [r5, #0x0]
	b _02041FD2
_02041E88:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
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
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	ldr r0, _02041FD8 ; =0x00000233
	add r4, #0x80
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	add r1, r7, #0x0
	bl MOD06_02249038
	strh r0, [r6, #0x0]
	b _02041FD2
_02041ECA:
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
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
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r1, [r5, #0x0]
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl MOD06_022490A0
	b _02041FD2
_02041F24:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl MOD06_02248CC0
	b _02041FD2
_02041F2E:
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
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r4, #0x80
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl MOD06_022491FC
	strh r0, [r6, #0x0]
	b _02041FD2
_02041F68:
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
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl MOD06_02248F70
	strh r0, [r5, #0x0]
	b _02041FD2
_02041FB4:
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
	bl MOD06_02248FE0
	strh r0, [r5, #0x0]
_02041FD2:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02041FD8: .word 0x00000233

	thumb_func_start FUN_02041FDC
FUN_02041FDC: ; 0x02041FDC
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02061374
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02042000
FUN_02042000: ; 0x02042000
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl GetPartyMonByIndex
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02061460
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02042038
FUN_02042038: ; 0x02042038
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	cmp r0, #0x0
	beq _02042058
	cmp r0, #0x1
	beq _020420A8
	b _02042106
_02042058:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
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
	ldr r0, _0204210C ; =0x00000232
	add r5, #0x80
	strh r0, [r6, #0x0]
	ldr r0, [sp, #0x0]
	ldr r1, [r5, #0x0]
	ldr r2, [r4, #0x0]
	bl FUN_020421F0
	strh r0, [r7, #0x0]
	b _02042106
_020420A8:
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
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
	add r5, #0x80
	add r3, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020421D8
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_0202A170
_02042106:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0204210C: .word 0x00000232

	thumb_func_start FUN_02042110
FUN_02042110: ; 0x02042110
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
	add r1, r6, #0x0
	bl FUN_02042214
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204214C
FUN_0204214C: ; 0x0204214C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	cmp r0, #0x0
	beq _02042170
	cmp r0, #0x1
	beq _020421A2
	cmp r0, #0x2
	beq _020421BC
	b _020421D4
_02042170:
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl GetPartyMonByIndex
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x4
	bl FUN_02060F3C
	b _020421D4
_020421A2:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02060F9C
	b _020421D4
_020421BC:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02060F88
_020421D4:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020421D8
FUN_020421D8: ; 0x020421D8
	push {r3, lr}
	sub r1, r1, #0x1
	lsl r3, r1, #0x4
	ldr r1, _020421EC ; =UNK_020F4264
	ldr r3, [r1, r3]
	cmp r3, #0x0
	beq _020421EA
	add r1, r2, #0x0
	blx r3
_020421EA:
	pop {r3, pc}
	.balign 4
_020421EC: .word UNK_020F4264

	thumb_func_start FUN_020421F0
FUN_020421F0: ; 0x020421F0
	push {r4, lr}
	sub r0, r0, #0x1
	lsl r4, r0, #0x4
	ldr r0, _0204220C ; =UNK_020F4268
	ldr r3, [r0, r4]
	cmp r3, #0x0
	beq _02042204
	add r0, r1, #0x0
	add r1, r2, #0x0
	blx r3
_02042204:
	ldr r0, _02042210 ; =UNK_020F4270
	ldr r0, [r0, r4]
	pop {r4, pc}
	nop
_0204220C: .word UNK_020F4268
_02042210: .word UNK_020F4270

	thumb_func_start FUN_02042214
FUN_02042214: ; 0x02042214
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	add r5, r1, #0x0
	bl FUN_02022504
	mov r1, #0x1
	add r2, r5, #0x0
	bl FUN_0202B710
	cmp r0, #0x0
	bne _02042230
	mov r0, #0x0
	pop {r3-r5, pc}
_02042230:
	sub r0, r5, #0x1
	lsl r1, r0, #0x4
	ldr r0, _02042248 ; =UNK_020F426C
	ldr r1, [r0, r1]
	cmp r1, #0x0
	bne _02042240
	mov r0, #0x1
	pop {r3-r5, pc}
_02042240:
	add r0, r4, #0x0
	blx r1
	pop {r3-r5, pc}
	nop
_02042248: .word UNK_020F426C

	thumb_func_start FUN_0204224C
FUN_0204224C: ; 0x0204224C
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	mov r0, #0x40
	mov r1, #0x4
	str r3, [sp, #0x8]
	bl String_ctor
	add r1, r7, #0x0
	add r4, r0, #0x0
	bl CopyU16ArrayToString
	ldr r0, [sp, #0x24]
	ldr r3, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	add r1, r6, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl String_dtor
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02042288
FUN_02042288: ; 0x02042288
	push {r4, lr}
	ldr r0, [r0, #0xc]
	add r4, r1, #0x0
	bl SavArray_PlayerParty_get
	bl FUN_0204A20C
	bl FUN_020690E4
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200AC60
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020422A8
FUN_020422A8: ; 0x020422A8
	push {r4, lr}
	ldr r0, [r0, #0x4]
	add r4, r1, #0x0
	ldr r0, [r0, #0x14]
	bl MOD20_02252538
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200B02C
	pop {r4, pc}

	thumb_func_start FUN_020422C0
FUN_020422C0: ; 0x020422C0
	push {r4, lr}
	sub sp, #0x20
	ldr r0, [r0, #0xc]
	add r4, r1, #0x0
	bl FUN_02022504
	bl FUN_0202B844
	ldrh r0, [r0, #0x2]
	mov r1, #0x4
	add r2, sp, #0x8
	bl GetSpeciesNameIntoArray
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r0, #0x1
	mov r1, #0x0
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r2, sp, #0x8
	add r3, r1, #0x0
	bl FUN_0204224C
	add sp, #0x20
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020422F4
FUN_020422F4: ; 0x020422F4
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	bl FUN_0202B85C
	ldrb r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02042304
FUN_02042304: ; 0x02042304
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_0204C1A8
	bl FUN_0204BEC8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02042314
FUN_02042314: ; 0x02042314
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	bl FUN_0202B838
	ldrb r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02042324
FUN_02042324: ; 0x02042324
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	mov r1, #0x0
	bl FUN_02027098
	pop {r3, pc}

	thumb_func_start FUN_02042334
FUN_02042334: ; 0x02042334
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	bl FUN_0202B850
	ldrb r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02042344
FUN_02042344: ; 0x02042344
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	bl FUN_0202B844
	ldrb r0, [r0, #0x0]
	pop {r3, pc}
