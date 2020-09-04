    .include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global UNK_021C5A10
UNK_021C5A10: ; 0x021C5A10
	.space 0x4

	.text

	thumb_func_start ScrCmd_unk_590
ScrCmd_unk_590: ; 0x02041194
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F5D8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_591
ScrCmd_unk_591: ; 0x020411C4
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r0, #0x0
	add r0, #0x80
	ldr r7, [r0, #0x0]
	ldr r0, [r7, #0xc]
	bl GetStoragePCPointer
	str r0, [sp, #0x20]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x8]
	add r0, r4, #0x0
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
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, _0204133C ; =0x00000000
	str r0, [sp, #0x1c]
	str r0, [sp, #0x18]
	ldr r5, [sp, #0x1c]
	beq _02041286
_0204123C:
	ldr r0, [r7, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _0204127C
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	lsl r1, r1, #0x10
	ldr r0, [sp, #0x0]
	lsr r1, r1, #0x10
	bl FUN_02041354
	cmp r0, #0x0
	beq _0204127C
	ldr r1, [sp, #0x1c]
	cmp r1, r0
	bge _0204127C
	str r0, [sp, #0x1c]
	str r5, [sp, #0x18]
_0204127C:
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, r6
	blo _0204123C
_02041286:
	mov r6, #0x0
	str r6, [sp, #0x14]
	str r6, [sp, #0x10]
	add r7, r6, #0x0
_0204128E:
	mov r5, #0x0
_02041290:
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x10]
	add r2, r5, #0x0
	bl PCStorage_GetMonByIndexPair
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetBoxMonData
	cmp r0, #0x0
	beq _020412E0
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetBoxMonData
	cmp r0, #0x0
	bne _020412E0
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl GetBoxMonData
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	lsl r1, r1, #0x10
	ldr r0, [sp, #0x0]
	lsr r1, r1, #0x10
	bl FUN_02041354
	cmp r0, #0x0
	beq _020412E0
	cmp r6, r0
	bge _020412E0
	add r6, r0, #0x0
	add r0, r5, r7
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x14]
_020412E0:
	add r5, r5, #0x1
	cmp r5, #0x1e
	blo _02041290
	ldr r0, [sp, #0x10]
	add r7, #0x1e
	add r0, r0, #0x1
	str r0, [sp, #0x10]
	cmp r0, #0x12
	blo _0204128E
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _0204130C
	cmp r6, #0x0
	bne _0204130C
	ldr r0, [sp, #0xc]
	mov r1, #0x0
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	strh r1, [r0, #0x0]
	b _02041336
_0204130C:
	ldr r0, [sp, #0x1c]
	cmp r0, r6
	blo _02041326
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0xc]
	strh r1, [r0, #0x0]
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x8]
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	mov r1, #0x0
	strh r1, [r0, #0x0]
	b _02041336
_02041326:
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0xc]
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	mov r1, #0x1
	strh r6, [r0, #0x0]
	ldr r0, [sp, #0x4]
	strh r1, [r0, #0x0]
_02041336:
	mov r0, #0x0
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_0204133C: .word 0x00000000

	thumb_func_start ScrCmd_unk_592
ScrCmd_unk_592: ; 0x02041340
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F5FC
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02041354
FUN_02041354: ; 0x02041354
	push {r4-r7, lr}
	sub sp, #0xc
	mov r6, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r7, r6, #0x0
_02041360:
	add r0, r5, #0x0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x0]
	cmp r0, r1
	bne _020413AC
	add r0, r5, #0x0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, #0x0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	add r0, r7, #0x1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	cmp r7, #0x5
	blo _02041360
_020413AC:
	ldr r1, _020413BC ; =UNK_021C5A10
	ldr r0, [sp, #0x8]
	strh r0, [r1, #0x2]
	ldr r0, [sp, #0x4]
	strh r0, [r1, #0x0]
	add r0, r6, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_020413BC: .word UNK_021C5A10
