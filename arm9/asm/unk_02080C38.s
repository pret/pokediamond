	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020FBB90
UNK_020FBB90: ; 0x020FBB90
	.byte 0x14, 0x14, 0xFF, 0x0F, 0x19, 0xFF, 0x00, 0x00

	.global UNK_020FBB98
UNK_020FBB98: ; 0x020FBB98
	.byte 0x0A, 0x0A, 0x1E, 0xFF, 0x0F, 0x0F, 0x0F, 0xFF

	.global UNK_020FBBA0
UNK_020FBBA0: ; 0x020FBBA0
	.byte 0x0A, 0x08, 0x14, 0x1C, 0xFF, 0x0F, 0x0F, 0x08, 0x08, 0xFF, 0x00, 0x00

	.global UNK_020FBBAC
UNK_020FBBAC: ; 0x020FBBAC
	.byte 0x08, 0x08, 0x08, 0x08, 0x1E, 0xFF, 0x0F, 0x0F, 0x08, 0x08, 0x14, 0xFF

	.global UNK_020FBBB8
UNK_020FBBB8: ; 0x020FBBB8
	.word ov12_02241210, ov12_02241490, ov12_022415A8, SDK_OVERLAY_OVERLAY_12_ID

	.global UNK_020FBBC8
UNK_020FBBC8: ; 0x020FBBC8
	.word ov12_0222EF04, ov12_0222F19C, ov12_0222F324, SDK_OVERLAY_OVERLAY_12_ID

	.global UNK_020FBBD8
UNK_020FBBD8: ; 0x020FBBD8
	.word ov17_021D8818, ov17_021D8998, ov17_021D8C9C, SDK_OVERLAY_OVERLAY_17_ID

	.global UNK_020FBBE8
UNK_020FBBE8: ; 0x020FBBE8
	.word ov12_0222D5C0, ov12_0222D89C, ov12_0222D9B0, SDK_OVERLAY_OVERLAY_12_ID

	.global UNK_020FBBF8
UNK_020FBBF8: ; 0x020FBBF8
	.word ov12_0222FE4C, ov12_02230128, ov12_0223023C, SDK_OVERLAY_OVERLAY_12_ID

	.text

	thumb_func_start sub_02080C38
sub_02080C38: ; 0x02080C38
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0x8
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r1, _02080C5C ; =sub_02080C60
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl TaskManager_Call
	pop {r3-r5, pc}
	nop
_02080C5C: .word sub_02080C60

	thumb_func_start sub_02080C60
sub_02080C60: ; 0x02080C60
	push {r3-r7, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0xe
	bls _02080C7C
	b _02080DE2
_02080C7C:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02080C88: ; jump table (using 16-bit offset)
	.short _02080CA6 - _02080C88 - 2; case 0
	.short _02080CB4 - _02080C88 - 2; case 1
	.short _02080D16 - _02080C88 - 2; case 2
	.short _02080D28 - _02080C88 - 2; case 3
	.short _02080D36 - _02080C88 - 2; case 4
	.short _02080D48 - _02080C88 - 2; case 5
	.short _02080D64 - _02080C88 - 2; case 6
	.short _02080D78 - _02080C88 - 2; case 7
	.short _02080D8A - _02080C88 - 2; case 8
	.short _02080D9C - _02080C88 - 2; case 9
	.short _02080DAE - _02080C88 - 2; case 10
	.short _02080DC0 - _02080C88 - 2; case 11
	.short _02080DCE - _02080C88 - 2; case 12
	.short _02080DD4 - _02080C88 - 2; case 13
	.short _02080DE6 - _02080C88 - 2; case 14
_02080CA6:
	add r0, r5, #0x0
	bl sub_0204AF3C
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080CB4:
	ldr r0, [r6, #0xc]
	bl SaveArray_PlayerParty_Get
	mov r1, #0x0
	bl GetPartyMonByIndex
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FieldSystem_GetSaveDataPtr
	bl Save_PlayerData_GetProfileAddr
	mov r1, #0xb
	str r0, [sp, #0x0]
	bl PlayerProfile_GetPlayerName_NewString
	add r5, r0, #0x0
	mov r1, #0x0
	add r0, sp, #0x4
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	mov r1, #0x2
	strb r1, [r0, #0x2]
	ldr r0, [sp, #0x0]
	str r7, [sp, #0xc]
	str r5, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r0, [r6, #0xc]
	bl Save_FashionData_Get
	str r0, [sp, #0x18]
	ldr r0, [r6, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [sp, #0x1c]
	add r0, sp, #0x4
	bl sub_02081214
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	bl String_Delete
	ldr r0, [r4, #0x0]
	bl sub_02081DC4
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D16:
	ldr r0, [r4, #0x0]
	bl sub_02081EB8
	cmp r0, #0x1
	bne _02080DF2
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D28:
	mov r0, #0x1
	bl sub_02031588
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D36:
	mov r0, #0x1
	bl sub_020315D8
	cmp r0, #0x1
	bne _02080DF2
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D48:
	ldr r0, [r4, #0x0]
	bl sub_020815D0
	ldr r3, [r4, #0x0]
	ldr r2, _02080DF8 ; =0x000019B8
	ldr r1, _02080DFC ; =UNK_020FBBD8
	ldr r2, [r3, r2]
	add r0, r5, #0x0
	bl sub_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D64:
	ldr r0, [r4, #0x0]
	bl sub_02081668
	ldr r0, [r4, #0x0]
	bl sub_02081ED4
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D78:
	ldr r0, [r4, #0x0]
	bl sub_02081EC0
	cmp r0, #0x1
	bne _02080DF2
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D8A:
	ldr r1, _02080E00 ; =UNK_020FBBC8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl sub_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D9C:
	ldr r1, _02080E04 ; =UNK_020FBBF8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl sub_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080DAE:
	ldr r1, _02080E08 ; =UNK_020FBBE8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl sub_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080DC0:
	ldr r0, [r4, #0x0]
	bl sub_020814E8
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080DCE:
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080DD4:
	add r0, r5, #0x0
	bl sub_0204AF84
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080DE2:
	bl GF_AssertFail
_02080DE6:
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x28
	mov r0, #0x1
	pop {r3-r7, pc}
_02080DF2:
	mov r0, #0x0
	add sp, #0x28
	pop {r3-r7, pc}
	.balign 4
_02080DF8: .word 0x000019B8
_02080DFC: .word UNK_020FBBD8
_02080E00: .word UNK_020FBBC8
_02080E04: .word UNK_020FBBF8
_02080E08: .word UNK_020FBBE8

	thumb_func_start sub_02080E0C
sub_02080E0C: ; 0x02080E0C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0x8
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, _02080E50 ; =0x00000121
	str r6, [r4, #0x0]
	ldrb r0, [r6, r0]
	cmp r0, #0x0
	beq _02080E36
	cmp r0, #0x1
	beq _02080E36
	cmp r0, #0x2
	bne _02080E42
_02080E36:
	ldr r1, _02080E54 ; =sub_02080E5C
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl TaskManager_Call
	pop {r4-r6, pc}
_02080E42:
	ldr r1, _02080E58 ; =sub_02081000
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl TaskManager_Call
	pop {r4-r6, pc}
	nop
_02080E50: .word 0x00000121
_02080E54: .word sub_02080E5C
_02080E58: .word sub_02081000

	thumb_func_start sub_02080E5C
sub_02080E5C: ; 0x02080E5C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r0, r5, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0xd
	bls _02080E74
	b _02080FCE
_02080E74:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02080E80: ; jump table (using 16-bit offset)
	.short _02080E9C - _02080E80 - 2; case 0
	.short _02080EAA - _02080E80 - 2; case 1
	.short _02080EC6 - _02080E80 - 2; case 2
	.short _02080EDE - _02080E80 - 2; case 3
	.short _02080F00 - _02080E80 - 2; case 4
	.short _02080F1C - _02080E80 - 2; case 5
	.short _02080F3E - _02080E80 - 2; case 6
	.short _02080F58 - _02080E80 - 2; case 7
	.short _02080F6A - _02080E80 - 2; case 8
	.short _02080F8A - _02080E80 - 2; case 9
	.short _02080FA8 - _02080E80 - 2; case 10
	.short _02080FBA - _02080E80 - 2; case 11
	.short _02080FC0 - _02080E80 - 2; case 12
	.short _02080FD2 - _02080E80 - 2; case 13
_02080E9C:
	add r0, r5, #0x0
	bl sub_0204AF3C
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080EAA:
	ldr r0, [r4, #0x0]
	ldr r1, _02080FE0 ; =0x00000171
	ldrb r1, [r0, r1]
	cmp r1, #0x0
	beq _02080EBE
	bl sub_02081EC0
	cmp r0, #0x1
	beq _02080EBE
	b _02080FDC
_02080EBE:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080EC6:
	ldr r1, [r4, #0x0]
	ldr r0, _02080FE0 ; =0x00000171
	ldrb r0, [r1, r0]
	cmp r0, #0x1
	bne _02080ED6
	mov r0, #0x0
	bl sub_02031588
_02080ED6:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080EDE:
	ldr r2, [r4, #0x0]
	ldr r1, _02080FE0 ; =0x00000171
	ldrb r1, [r2, r1]
	cmp r1, #0x1
	bne _02080EFA
	mov r0, #0x0
	bl sub_020315D8
	cmp r0, #0x1
	bne _02080FDC
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080EFA:
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F00:
	ldr r0, [r4, #0x0]
	bl sub_020815D0
	ldr r3, [r4, #0x0]
	ldr r2, _02080FE4 ; =0x000019B8
	ldr r1, _02080FE8 ; =UNK_020FBBD8
	ldr r2, [r3, r2]
	add r0, r5, #0x0
	bl sub_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F1C:
	ldr r0, [r4, #0x0]
	bl sub_02081668
	ldr r0, [r4, #0x0]
	ldr r1, _02080FE0 ; =0x00000171
	ldrb r1, [r0, r1]
	cmp r1, #0x1
	bne _02080F38
	bl sub_02081ED4
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F38:
	mov r0, #0x6
	str r0, [r4, #0x4]
	b _02080FDC
_02080F3E:
	ldr r0, [r4, #0x0]
	ldr r1, _02080FE0 ; =0x00000171
	ldrb r1, [r0, r1]
	cmp r1, #0x0
	beq _02080F50
	bl sub_02081EC0
	cmp r0, #0x1
	bne _02080FDC
_02080F50:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F58:
	ldr r1, _02080FEC ; =UNK_020FBBC8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl sub_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F6A:
	ldr r2, [r4, #0x0]
	ldr r0, _02080FF0 ; =0x00000121
	ldrb r0, [r2, r0]
	add r0, #0xff
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	bhi _02080F82
	ldr r1, _02080FF4 ; =UNK_020FBBF8
	add r0, r5, #0x0
	bl sub_02046500
_02080F82:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F8A:
	ldr r2, [r4, #0x0]
	ldr r0, _02080FF0 ; =0x00000121
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	beq _02080F98
	cmp r0, #0x2
	bne _02080FA0
_02080F98:
	ldr r1, _02080FF8 ; =UNK_020FBBE8
	add r0, r5, #0x0
	bl sub_02046500
_02080FA0:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080FA8:
	ldr r1, _02080FFC ; =UNK_020FBBB8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl sub_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080FBA:
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080FC0:
	add r0, r5, #0x0
	bl sub_0204AF84
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080FCE:
	bl GF_AssertFail
_02080FD2:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_02080FDC:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02080FE0: .word 0x00000171
_02080FE4: .word 0x000019B8
_02080FE8: .word UNK_020FBBD8
_02080FEC: .word UNK_020FBBC8
_02080FF0: .word 0x00000121
_02080FF4: .word UNK_020FBBF8
_02080FF8: .word UNK_020FBBE8
_02080FFC: .word UNK_020FBBB8

	thumb_func_start sub_02081000
sub_02081000: ; 0x02081000
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r0, r5, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x9
	bls _0208101A
	b _020811A4
_0208101A:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02081026: ; jump table (using 16-bit offset)
	.short _0208103A - _02081026 - 2; case 0
	.short _02081048 - _02081026 - 2; case 1
	.short _02081070 - _02081026 - 2; case 2
	.short _0208108A - _02081026 - 2; case 3
	.short _02081090 - _02081026 - 2; case 4
	.short _020810AE - _02081026 - 2; case 5
	.short _020810D2 - _02081026 - 2; case 6
	.short _020810F0 - _02081026 - 2; case 7
	.short _02081196 - _02081026 - 2; case 8
	.short _020811A8 - _02081026 - 2; case 9
_0208103A:
	add r0, r5, #0x0
	bl sub_0204AF3C
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_02081048:
	ldr r0, [r4, #0x0]
	ldr r1, _020811BC ; =0x00000121
	ldrb r1, [r0, r1]
	cmp r1, #0x3
	beq _02081056
	cmp r1, #0x4
	bne _02081068
_02081056:
	bl sub_020815D0
	ldr r3, [r4, #0x0]
	ldr r2, _020811C0 ; =0x000019B8
	ldr r1, _020811C4 ; =UNK_020FBBD8
	ldr r2, [r3, r2]
	add r0, r5, #0x0
	bl sub_02046500
_02081068:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_02081070:
	ldr r0, [r4, #0x0]
	ldr r1, _020811BC ; =0x00000121
	ldrb r1, [r0, r1]
	cmp r1, #0x3
	beq _0208107E
	cmp r1, #0x4
	bne _02081082
_0208107E:
	bl sub_02081668
_02081082:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_0208108A:
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_02081090:
	ldr r2, [r4, #0x0]
	ldr r0, _020811BC ; =0x00000121
	ldrb r0, [r2, r0]
	cmp r0, #0x3
	beq _0208109E
	cmp r0, #0x4
	bne _020810A6
_0208109E:
	ldr r1, _020811C8 ; =UNK_020FBBC8
	add r0, r5, #0x0
	bl sub_02046500
_020810A6:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_020810AE:
	ldr r0, [r4, #0x0]
	ldr r1, _020811BC ; =0x00000121
	ldrb r1, [r0, r1]
	cmp r1, #0x5
	beq _020810BC
	cmp r1, #0x6
	bne _020810CA
_020810BC:
	bl sub_02082D18
	ldr r1, _020811CC ; =UNK_020FBBF8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl sub_02046500
_020810CA:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_020810D2:
	ldr r2, [r4, #0x0]
	ldr r0, _020811BC ; =0x00000121
	ldrb r0, [r2, r0]
	cmp r0, #0x7
	beq _020810E0
	cmp r0, #0x8
	bne _020810E8
_020810E0:
	ldr r1, _020811D0 ; =UNK_020FBBE8
	add r0, r5, #0x0
	bl sub_02046500
_020810E8:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_020810F0:
	ldr r1, [r4, #0x0]
	ldr r0, _020811BC ; =0x00000121
	ldrb r0, [r1, r0]
	cmp r0, #0x8
	bhi _0208116E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02081106: ; jump table (using 16-bit offset)
	.short _0208116E - _02081106 - 2; case 0
	.short _0208116E - _02081106 - 2; case 1
	.short _0208116E - _02081106 - 2; case 2
	.short _02081118 - _02081106 - 2; case 3
	.short _02081118 - _02081106 - 2; case 4
	.short _0208113A - _02081106 - 2; case 5
	.short _0208113A - _02081106 - 2; case 6
	.short _02081156 - _02081106 - 2; case 7
	.short _02081156 - _02081106 - 2; case 8
_02081118:
	mov r5, #0x0
	add r6, sp, #0x0
_0208111C:
	ldr r0, [r4, #0x0]
	add r1, r5, #0x0
	bl sub_02083308
	add r7, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r5, #0x0
	bl sub_0208336C
	add r0, r7, r0
	add r5, r5, #0x1
	stmia r6!, {r0}
	cmp r5, #0x4
	blt _0208111C
	b _0208116E
_0208113A:
	mov r2, #0x0
	mov r3, #0x4b
	add r0, r2, #0x0
	add r1, sp, #0x0
	lsl r3, r3, #0x2
_02081144:
	ldr r5, [r4, #0x0]
	add r2, r2, #0x1
	add r5, r5, r0
	ldrsh r5, [r5, r3]
	add r0, #0xc
	cmp r2, #0x4
	stmia r1!, {r5}
	blt _02081144
	b _0208116E
_02081156:
	mov r2, #0x0
	ldr r3, _020811D4 ; =0x0000012E
	add r0, r2, #0x0
	add r1, sp, #0x0
_0208115E:
	ldr r5, [r4, #0x0]
	add r2, r2, #0x1
	add r5, r5, r0
	ldrsh r5, [r5, r3]
	add r0, #0xc
	cmp r2, #0x4
	stmia r1!, {r5}
	blt _0208115E
_0208116E:
	ldr r1, [sp, #0x0]
	mov r2, #0x0
	mov r5, #0x1
	add r3, sp, #0x4
_02081176:
	ldr r0, [r3, #0x0]
	cmp r1, r0
	bge _0208117E
	add r2, r2, #0x1
_0208117E:
	add r5, r5, #0x1
	add r3, r3, #0x4
	cmp r5, #0x4
	blt _02081176
	mov r0, #0x13
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_02081196:
	add r0, r5, #0x0
	bl sub_0204AF84
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_020811A4:
	bl GF_AssertFail
_020811A8:
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_020811B4:
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_020811BC: .word 0x00000121
_020811C0: .word 0x000019B8
_020811C4: .word UNK_020FBBD8
_020811C8: .word UNK_020FBBC8
_020811CC: .word UNK_020FBBF8
_020811D0: .word UNK_020FBBE8
_020811D4: .word 0x0000012E

	thumb_func_start sub_020811D8
sub_020811D8: ; 0x020811D8
	push {r4, lr}
	ldr r1, _02081204 ; =0x000019C4
	mov r0, #0x14
	bl AllocFromHeap
	ldr r2, _02081204 ; =0x000019C4
	mov r1, #0x0
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, _02081208 ; =0x00000123
	mov r1, #0x0
	strb r1, [r4, r0]
	add r1, r0, #0x4
	mov r2, #0x1
	strb r2, [r4, r1]
	mov r1, #0x3
	add r0, r0, #0x3
	strb r1, [r4, r0]
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_02081204: .word 0x000019C4
_02081208: .word 0x00000123

	thumb_func_start sub_0208120C
sub_0208120C: ; 0x0208120C
	ldr r3, _02081210 ; =FreeToHeap
	bx r3
	.balign 4
_02081210: .word FreeToHeap

	thumb_func_start sub_02081214
sub_02081214: ; 0x02081214
	push {r3-r7, lr}
	mov r2, #0x1
	add r6, r0, #0x0
	mov r0, #0xb
	mov r1, #0x14
	lsl r2, r2, #0xe
	bl CreateHeap
	bl sub_020811D8
	add r4, r0, #0x0
	bl GetLCRNGSeed
	mov r1, #0x67
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	add r0, r4, #0x0
	bl sub_0208285C
	ldrb r1, [r6, #0x0]
	ldr r0, _020813E4 ; =0x0000011F
	strb r1, [r4, r0]
	add r1, r0, #0x1
	ldrb r2, [r6, #0x1]
	add r0, r0, #0x2
	strb r2, [r4, r1]
	ldrb r1, [r6, #0x2]
	strb r1, [r4, r0]
	ldrb r0, [r6, #0x1]
	mov r1, #0x0
	bl sub_02083454
	ldr r1, _020813E8 ; =0x00000122
	mov r7, #0x0
	strb r0, [r4, r1]
	add r0, r1, #0x1
	ldrb r2, [r4, r0]
	sub r0, r1, #0x6
	add r5, r4, #0x0
	strb r2, [r4, r0]
	mov r0, #0x64
	add r1, r0, #0x0
	add r1, #0xc1
	strb r0, [r4, r1]
	add r1, r0, #0x0
	add r1, #0xc1
	ldrb r2, [r4, r1]
	add r1, r0, #0x0
	add r1, #0xb9
	strb r2, [r4, r1]
	mov r1, #0x1
	add r0, #0xba
	strb r1, [r4, r0]
	ldr r1, [r6, #0x14]
	ldr r0, _020813EC ; =0x0000199C
	str r1, [r4, r0]
	add r1, r0, #0x0
	ldr r2, [r6, #0x18]
	sub r1, #0x14
	str r2, [r4, r1]
	add r1, r0, #0x0
	ldr r2, [r6, #0x1c]
	sub r1, #0x10
	str r2, [r4, r1]
	add r1, r0, #0x0
	ldr r2, [r6, #0x8]
	sub r1, #0xc
	str r2, [r4, r1]
	ldrb r2, [r6, #0x5]
	sub r1, r0, #0x4
	strb r2, [r4, r1]
	add r1, r0, #0x0
	ldr r2, [r6, #0x10]
	sub r1, #0x8
	str r2, [r4, r1]
	sub r1, r0, #0x3
	ldrb r2, [r6, #0x3]
	sub r0, r0, #0x2
	strb r2, [r4, r1]
	ldrb r1, [r6, #0x4]
	strb r1, [r4, r0]
_020812B6:
	mov r0, #0x14
	bl sub_02026FE8
	add r1, r5, #0x0
	add r1, #0xf8
	add r7, r7, #0x1
	add r5, r5, #0x4
	str r0, [r1, #0x0]
	cmp r7, #0x4
	blt _020812B6
	mov r3, #0x12
	lsl r3, r3, #0x4
	ldrb r0, [r4, r3]
	sub r2, r3, #0x2
	sub r3, r3, #0x1
	str r0, [sp, #0x0]
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	add r0, r4, #0x0
	mov r1, #0xb
	bl sub_02082ED0
	mov r0, #0x14
	bl SaveArray_Party_Alloc
	mov r1, #0x56
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r7, #0x0
	add r5, r4, #0x0
_020812F2:
	mov r0, #0x14
	bl AllocMonZeroed
	add r7, r7, #0x1
	stmia r5!, {r0}
	cmp r7, #0x4
	blt _020812F2
	mov r7, #0x0
	add r5, r4, #0x0
_02081304:
	mov r0, #0x14
	bl Chatot_New
	mov r1, #0x57
	lsl r1, r1, #0x2
	str r0, [r5, r1]
	add r7, r7, #0x1
	add r5, r5, #0x4
	cmp r7, #0x4
	blt _02081304
	add r0, r1, #0x0
	ldr r0, [r4, r0]
	ldr r1, [r6, #0x20]
	bl Chatot_Copy
	ldr r0, [r6, #0x8]
	ldr r1, [r4, #0x0]
	bl CopyPokemonToPokemon
	mov r0, #0x8
	mov r1, #0x14
	bl String_New
	add r1, r4, #0x0
	add r1, #0xe8
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	ldr r1, [r6, #0xc]
	bl StringCopy
	ldr r0, [r6, #0x10]
	bl PlayerProfile_GetTrainerGender
	mov r1, #0x42
	lsl r1, r1, #0x2
	strb r0, [r4, r1]
	add r0, r1, #0x4
	mov r2, #0x0
	strb r2, [r4, r0]
	add r1, #0x17
	ldrb r1, [r4, r1]
	ldr r0, [r4, #0x0]
	bl sub_02081540
	mov r1, #0x11
	lsl r1, r1, #0x4
	strb r0, [r4, r1]
	add r0, r4, #0x0
	bl sub_020832EC
	cmp r0, #0x0
	ldr r0, [r6, #0x10]
	bne _0208138E
	bl PlayerProfile_GetTrainerGender
	cmp r0, #0x0
	bne _02081384
	mov r1, #0xba
	add r0, r1, #0x0
	add r0, #0x5a
	strh r1, [r4, r0]
	b _020813A8
_02081384:
	mov r1, #0xbb
	add r0, r1, #0x0
	add r0, #0x59
	strh r1, [r4, r0]
	b _020813A8
_0208138E:
	bl PlayerProfile_GetTrainerGender
	cmp r0, #0x0
	bne _020813A0
	mov r0, #0x45
	mov r1, #0x0
	lsl r0, r0, #0x2
	strh r1, [r4, r0]
	b _020813A8
_020813A0:
	mov r1, #0x61
	add r0, r1, #0x0
	add r0, #0xb3
	strh r1, [r4, r0]
_020813A8:
	ldrb r1, [r6, #0x3]
	ldrb r2, [r6, #0x4]
	add r0, r4, #0x0
	bl sub_020813F4
	add r0, r4, #0x0
	bl sub_020832EC
	cmp r0, #0x1
	bne _020813D0
	ldr r1, _020813F0 ; =0x00000172
	mov r5, #0x0
	mov r0, #0x3
_020813C2:
	sub r3, r0, r5
	add r2, r4, r5
	add r5, r5, #0x1
	strb r3, [r2, r1]
	cmp r5, #0x4
	blt _020813C2
	b _020813DE
_020813D0:
	ldr r0, _020813F0 ; =0x00000172
	mov r2, #0x0
_020813D4:
	add r1, r4, r2
	strb r2, [r1, r0]
	add r2, r2, #0x1
	cmp r2, #0x4
	blt _020813D4
_020813DE:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	nop
_020813E4: .word 0x0000011F
_020813E8: .word 0x00000122
_020813EC: .word 0x0000199C
_020813F0: .word 0x00000172

	thumb_func_start sub_020813F4
sub_020813F4: ; 0x020813F4
	push {r3-r7, lr}
	sub sp, #0x10
	mov r3, #0x12
	add r5, r0, #0x0
	lsl r3, r3, #0x4
	ldrb r4, [r5, r3]
	str r4, [sp, #0x0]
	add r4, r3, #0x1
	ldrb r4, [r5, r4]
	sub r3, r3, #0x1
	str r4, [sp, #0x4]
	str r1, [sp, #0x8]
	str r2, [sp, #0xc]
	ldrb r3, [r5, r3]
	mov r1, #0xb
	mov r2, #0x3
	bl sub_020828E4
	add r4, r5, #0x0
	add r4, #0x10
	mov r7, #0x1
	add r6, r5, #0x4
	add r4, #0x30
_02081422:
	ldr r1, [r6, #0x0]
	add r0, r4, #0x0
	mov r2, #0x14
	bl sub_02082D60
	add r7, r7, #0x1
	add r6, r6, #0x4
	add r4, #0x30
	cmp r7, #0x4
	blt _02081422
	mov r6, #0x1
	add r4, r5, #0x4
	mov r7, #0x8
_0208143C:
	add r0, r4, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02081454
	add r0, r7, #0x0
	mov r1, #0x14
	bl String_New
	add r1, r4, #0x0
	add r1, #0xe8
	str r0, [r1, #0x0]
_02081454:
	add r2, r4, #0x0
	add r2, #0xe8
	ldr r0, [r4, #0x0]
	ldr r2, [r2, #0x0]
	mov r1, #0x90
	bl GetMonData
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, #0x4
	blt _0208143C
	add r0, r5, #0x0
	add r0, #0x30
	mov r2, #0x42
	mov r1, #0x1
	add r0, #0x30
	lsl r2, r2, #0x2
_02081476:
	ldrh r3, [r0, #0x0]
	add r0, #0x30
	lsl r3, r3, #0x12
	lsr r4, r3, #0x1e
	add r3, r5, r1
	add r1, r1, #0x1
	strb r4, [r3, r2]
	cmp r1, #0x4
	blt _02081476
	add r0, r5, #0x0
	add r0, #0x30
	mov r2, #0x43
	mov r1, #0x1
	add r0, #0x30
	lsl r2, r2, #0x2
_02081494:
	ldrh r3, [r0, #0x0]
	add r0, #0x30
	lsl r3, r3, #0x10
	lsr r4, r3, #0x1e
	add r3, r5, r1
	add r1, r1, #0x1
	strb r4, [r3, r2]
	cmp r1, #0x4
	blt _02081494
	add r3, r5, #0x0
	mov r1, #0x11
	mov r4, #0x1
	add r3, #0x30
	lsl r1, r1, #0x4
_020814B0:
	add r0, r3, #0x0
	add r0, #0x3e
	ldrb r2, [r0, #0x0]
	add r0, r5, r4
	add r4, r4, #0x1
	add r3, #0x30
	strb r2, [r0, r1]
	cmp r4, #0x4
	blt _020814B0
	add r2, r5, #0x0
	mov r0, #0x45
	mov r4, #0x1
	add r2, #0x30
	add r3, r5, #0x2
	lsl r0, r0, #0x2
_020814CE:
	ldrh r1, [r2, #0x18]
	add r4, r4, #0x1
	add r2, #0x30
	strh r1, [r3, r0]
	add r3, r3, #0x2
	cmp r4, #0x4
	blt _020814CE
	add r0, r5, #0x0
	mov r1, #0xb
	bl sub_02082B90
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start sub_020814E8
sub_020814E8: ; 0x020814E8
	push {r3-r7, lr}
	add r7, r0, #0x0
	mov r0, #0x56
	lsl r0, r0, #0x2
	ldr r0, [r7, r0]
	bl FreeToHeap
	mov r6, #0x57
	mov r4, #0x0
	add r5, r7, #0x0
	lsl r6, r6, #0x2
_020814FE:
	ldr r0, [r5, #0x0]
	bl FreeToHeap
	add r0, r5, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	bl String_Delete
	add r0, r5, #0x0
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	ldr r0, [r5, r6]
	bl FreeToHeap
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blt _020814FE
	mov r0, #0x67
	lsl r0, r0, #0x6
	ldr r0, [r7, r0]
	bl SetLCRNGSeed
	add r0, r7, #0x0
	bl sub_0208120C
	mov r0, #0x14
	bl DestroyHeap
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_02081540
sub_02081540: ; 0x02081540
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x1
	add r7, r1, #0x0
	str r0, [sp, #0x0]
	mov r4, #0x0
_0208154C:
	cmp r7, #0x4
	bhi _020815B6
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0208155C: ; jump table (using 16-bit offset)
	.short _02081566 - _0208155C - 2; case 0
	.short _02081576 - _0208155C - 2; case 1
	.short _02081586 - _0208155C - 2; case 2
	.short _02081596 - _0208155C - 2; case 3
	.short _020815A6 - _0208155C - 2; case 4
_02081566:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x7a
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	b _020815BA
_02081576:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x7e
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	b _020815BA
_02081586:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x82
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	b _020815BA
_02081596:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x86
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	b _020815BA
_020815A6:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x8a
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	b _020815BA
_020815B6:
	bl GF_AssertFail
_020815BA:
	cmp r6, #0x0
	beq _020815CA
	ldr r0, [sp, #0x0]
	add r4, r4, #0x1
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	cmp r4, #0x3
	ble _0208154C
_020815CA:
	ldr r0, [sp, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_020815D0
sub_020815D0: ; 0x020815D0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02081658 ; =0x00000123
	ldrb r0, [r5, r0]
	lsl r0, r0, #0x2
	add r0, r5, r0
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	bl sub_02027740
	mov r0, #0x14
	mov r1, #0x28
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x28
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, _02081658 ; =0x00000123
	ldrb r1, [r5, r0]
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	str r1, [r4, #0x0]
	ldrb r1, [r5, r0]
	lsl r1, r1, #0x2
	add r1, r5, r1
	add r1, #0xf8
	ldr r1, [r1, #0x0]
	str r1, [r4, #0x4]
	sub r1, r0, #0x1
	ldrb r1, [r5, r1]
	str r1, [r4, #0x8]
	add r1, r0, #0x0
	add r1, #0x4e
	ldrb r1, [r5, r1]
	cmp r1, #0x1
	bne _02081620
	mov r0, #0x4
	b _02081624
_02081620:
	sub r0, r0, #0x3
	ldrb r0, [r5, r0]
_02081624:
	str r0, [r4, #0xc]
	ldr r0, _0208165C ; =0x00000121
	ldrb r1, [r5, r0]
	sub r0, r0, #0x2
	str r1, [r4, #0x10]
	ldrb r0, [r5, r0]
	str r0, [r4, #0x14]
	ldr r0, _02081660 ; =0x0000199C
	ldr r0, [r5, r0]
	bl sub_0202708C
	ldr r1, _02081664 ; =0x000019A0
	str r0, [r4, #0x18]
	add r0, r5, r1
	str r0, [r4, #0x1c]
	add r0, r1, #0x0
	sub r0, #0x18
	ldr r0, [r5, r0]
	str r0, [r4, #0x20]
	add r0, r1, #0x0
	sub r0, #0xc
	ldr r0, [r5, r0]
	add r1, #0x18
	str r0, [r4, #0x24]
	str r4, [r5, r1]
	pop {r3-r5, pc}
	.balign 4
_02081658: .word 0x00000123
_0208165C: .word 0x00000121
_02081660: .word 0x0000199C
_02081664: .word 0x000019A0

	thumb_func_start sub_02081668
sub_02081668: ; 0x02081668
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0208167C ; =0x000019B8
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _0208167C ; =0x000019B8
	mov r1, #0x0
	str r1, [r4, r0]
	pop {r4, pc}
	.balign 4
_0208167C: .word 0x000019B8

	thumb_func_start sub_02081680
sub_02081680: ; 0x02081680
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r2, _020819E8 ; =0x00000176
	add r4, r1, #0x0
	str r0, [sp, #0x0]
	ldrb r0, [r4, r2]
	cmp r0, #0x2f
	bls _02081692
	b _02081D24
_02081692:
	add r3, r0, r0
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0208169E: ; jump table (using 16-bit offset)
	.short _020816FE - _0208169E - 2; case 0
	.short _02081716 - _0208169E - 2; case 1
	.short _0208172C - _0208169E - 2; case 2
	.short _02081742 - _0208169E - 2; case 3
	.short _0208175E - _0208169E - 2; case 4
	.short _02081776 - _0208169E - 2; case 5
	.short _0208178C - _0208169E - 2; case 6
	.short _020817A8 - _0208169E - 2; case 7
	.short _020817C4 - _0208169E - 2; case 8
	.short _020817DC - _0208169E - 2; case 9
	.short _020817F2 - _0208169E - 2; case 10
	.short _02081822 - _0208169E - 2; case 11
	.short _02081838 - _0208169E - 2; case 12
	.short _02081850 - _0208169E - 2; case 13
	.short _02081866 - _0208169E - 2; case 14
	.short _02081884 - _0208169E - 2; case 15
	.short _020818A0 - _0208169E - 2; case 16
	.short _020818B8 - _0208169E - 2; case 17
	.short _020818CE - _0208169E - 2; case 18
	.short _0208190A - _0208169E - 2; case 19
	.short _02081940 - _0208169E - 2; case 20
	.short _02081958 - _0208169E - 2; case 21
	.short _0208196E - _0208169E - 2; case 22
	.short _0208198E - _0208169E - 2; case 23
	.short _020819DE - _0208169E - 2; case 24
	.short _02081A04 - _0208169E - 2; case 25
	.short _02081A1A - _0208169E - 2; case 26
	.short _02081A54 - _0208169E - 2; case 27
	.short _02081A8A - _0208169E - 2; case 28
	.short _02081AB6 - _0208169E - 2; case 29
	.short _02081ACC - _0208169E - 2; case 30
	.short _02081AE8 - _0208169E - 2; case 31
	.short _02081B04 - _0208169E - 2; case 32
	.short _02081B1C - _0208169E - 2; case 33
	.short _02081B32 - _0208169E - 2; case 34
	.short _02081B6C - _0208169E - 2; case 35
	.short _02081BA2 - _0208169E - 2; case 36
	.short _02081BBA - _0208169E - 2; case 37
	.short _02081BD0 - _0208169E - 2; case 38
	.short _02081BFA - _0208169E - 2; case 39
	.short _02081C16 - _0208169E - 2; case 40
	.short _02081C2E - _0208169E - 2; case 41
	.short _02081C44 - _0208169E - 2; case 42
	.short _02081C86 - _0208169E - 2; case 43
	.short _02081CBC - _0208169E - 2; case 44
	.short _02081CD4 - _0208169E - 2; case 45
	.short _02081CEA - _0208169E - 2; case 46
	.short _02081D08 - _0208169E - 2; case 47
_020816FE:
	mov r0, #0x5
	bl sub_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081716:
	mov r0, #0x5
	bl sub_020315D8
	cmp r0, #0x1
	bne _0208180C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_0208172C:
	add r0, r4, #0x0
	bl sub_02083630
	cmp r0, #0x1
	bne _0208180C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081742:
	ldr r0, _020819EC ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _0208180C
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_0208175E:
	mov r0, #0x6
	bl sub_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081776:
	mov r0, #0x6
	bl sub_020315D8
	cmp r0, #0x1
	bne _0208180C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_0208178C:
	sub r2, #0x53
	ldrb r1, [r4, r2]
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	bl sub_020836BC
	cmp r0, #0x1
	bne _0208180C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020817A8:
	ldr r0, _020819EC ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _0208180C
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_020817C4:
	mov r0, #0x7
	bl sub_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020817DC:
	mov r0, #0x7
	bl sub_020315D8
	cmp r0, #0x1
	bne _0208180C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020817F2:
	add r3, r2, #0x0
	sub r3, #0x53
	ldrb r5, [r4, r3]
	add r3, r2, #0x0
	sub r3, #0x5a
	ldrb r3, [r4, r3]
	cmp r5, r3
	bne _0208181A
	add r0, r4, #0x0
	bl sub_0208373C
	cmp r0, #0x1
	beq _0208180E
_0208180C:
	b _02081DBC
_0208180E:
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_0208181A:
	add r0, r0, #0x1
	add sp, #0x10
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081822:
	ldr r0, _020819EC ; =0x00000584
	ldrb r1, [r4, r0]
	cmp r1, #0x0
	beq _02081912
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081838:
	mov r0, #0x8
	bl sub_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081850:
	mov r0, #0x8
	bl sub_020315D8
	cmp r0, #0x1
	bne _02081912
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081866:
	sub r2, #0x53
	ldrb r1, [r4, r2]
	add r2, r4, #0x0
	add r0, r4, #0x0
	add r2, #0x10
	bl sub_020837B4
	cmp r0, #0x1
	bne _02081912
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081884:
	ldr r0, _020819EC ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _02081912
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_020818A0:
	mov r0, #0x9
	bl sub_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020818B8:
	mov r0, #0x9
	bl sub_020315D8
	cmp r0, #0x1
	bne _02081912
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020818CE:
	add r1, r2, #0x0
	sub r1, #0x53
	ldrb r3, [r4, r1]
	add r1, r2, #0x0
	sub r1, #0x5a
	ldrb r1, [r4, r1]
	cmp r3, r1
	bne _02081902
	add r0, r2, #0x2
	ldr r1, [r4, r0]
	add r3, r4, #0x0
	mov r2, #0x30
	add r3, #0x10
	mul r2, r1
	add r0, r4, #0x0
	add r2, r3, r2
	bl sub_020837B4
	cmp r0, #0x1
	bne _02081912
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081902:
	add r0, r0, #0x1
	add sp, #0x10
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_0208190A:
	ldr r1, _020819EC ; =0x00000584
	ldrb r0, [r4, r1]
	cmp r0, #0x0
	bne _02081914
_02081912:
	b _02081DBC
_02081914:
	mov r0, #0x0
	strb r0, [r4, r1]
	add r1, r2, #0x2
	ldr r1, [r4, r1]
	add r3, r1, #0x1
	add r1, r2, #0x2
	str r3, [r4, r1]
	ldr r1, [r4, r1]
	cmp r1, #0x4
	bge _02081932
	ldrb r0, [r4, r2]
	add sp, #0x10
	sub r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081932:
	add r1, r2, #0x2
	str r0, [r4, r1]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081940:
	mov r0, #0xa
	bl sub_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081958:
	mov r0, #0xa
	bl sub_020315D8
	cmp r0, #0x1
	bne _02081A5C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_0208196E:
	sub r2, #0x53
	ldrb r1, [r4, r2]
	add r2, r4, #0x0
	add r2, #0xe8
	ldr r2, [r2, #0x0]
	add r0, r4, #0x0
	bl sub_020838B4
	cmp r0, #0x1
	bne _02081A5C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_0208198E:
	ldr r0, _020819EC ; =0x00000584
	sub r2, #0x4f
	ldrb r1, [r4, r2]
	ldrb r0, [r4, r0]
	cmp r0, r1
	blo _02081A5C
	mov r5, #0x0
	cmp r1, #0x0
	ble _020819CC
	add r6, r4, #0x0
_020819A2:
	add r0, r5, #0x0
	bl sub_0202DFA4
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	bl StringSetEmpty
	add r1, r6, #0x0
	add r1, #0xe8
	ldr r1, [r1, #0x0]
	add r0, r7, #0x0
	bl PlayerName_FlatToString
	ldr r0, _020819F0 ; =0x00000127
	add r5, r5, #0x1
	ldrb r0, [r4, r0]
	add r6, r6, #0x4
	cmp r5, r0
	blt _020819A2
_020819CC:
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020819DE:
	mov r0, #0xb
	bl sub_02031588
	ldr r0, _020819EC ; =0x00000584
	b _020819F4
	.balign 4
_020819E8: .word 0x00000176
_020819EC: .word 0x00000584
_020819F0: .word 0x00000127
_020819F4:
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081A04:
	mov r0, #0xb
	bl sub_020315D8
	cmp r0, #0x1
	bne _02081A5C
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081A1A:
	add r1, r2, #0x0
	sub r1, #0x53
	ldrb r3, [r4, r1]
	add r1, r2, #0x0
	sub r1, #0x5a
	ldrb r1, [r4, r1]
	cmp r3, r1
	bne _02081A4C
	add r0, r2, #0x2
	ldr r1, [r4, r0]
	add r0, r4, #0x0
	lsl r2, r1, #0x2
	add r2, r4, r2
	add r2, #0xe8
	ldr r2, [r2, #0x0]
	bl sub_020838B4
	cmp r0, #0x1
	bne _02081A5C
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081A4C:
	add r0, r0, #0x1
	add sp, #0x10
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081A54:
	ldr r1, _02081D2C ; =0x00000584
	ldrb r0, [r4, r1]
	cmp r0, #0x0
	bne _02081A5E
_02081A5C:
	b _02081DBC
_02081A5E:
	mov r0, #0x0
	strb r0, [r4, r1]
	add r1, r2, #0x2
	ldr r1, [r4, r1]
	add r3, r1, #0x1
	add r1, r2, #0x2
	str r3, [r4, r1]
	ldr r1, [r4, r1]
	cmp r1, #0x4
	bge _02081A7C
	ldrb r0, [r4, r2]
	add sp, #0x10
	sub r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081A7C:
	add r1, r2, #0x2
	str r0, [r4, r1]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081A8A:
	bl Save_Chatot_sizeof
	add r2, r0, #0x0
	mov r0, #0x57
	lsl r0, r0, #0x2
	ldr r1, _02081D30 ; =0x00000585
	ldr r0, [r4, r0]
	add r1, r4, r1
	bl MI_CpuCopy8
	mov r0, #0xc
	bl sub_02031588
	ldr r0, _02081D2C ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081AB6:
	mov r0, #0xc
	bl sub_020315D8
	cmp r0, #0x1
	bne _02081B74
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081ACC:
	sub r2, #0x53
	ldrb r1, [r4, r2]
	add r0, r4, #0x0
	mov r2, #0x0
	bl sub_02083AD4
	cmp r0, #0x1
	bne _02081B74
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081AE8:
	ldr r0, _02081D2C ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _02081B74
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081B04:
	mov r0, #0xd
	bl sub_02031588
	ldr r0, _02081D2C ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081B1C:
	mov r0, #0xd
	bl sub_020315D8
	cmp r0, #0x1
	bne _02081B74
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081B32:
	add r1, r2, #0x0
	sub r1, #0x53
	ldrb r3, [r4, r1]
	add r1, r2, #0x0
	sub r1, #0x5a
	ldrb r1, [r4, r1]
	cmp r3, r1
	bne _02081B64
	add r0, r2, #0x2
	ldr r1, [r4, r0]
	sub r2, #0x1a
	lsl r3, r1, #0x2
	add r3, r4, r3
	ldr r2, [r3, r2]
	add r0, r4, #0x0
	bl sub_02083AD4
	cmp r0, #0x1
	bne _02081B74
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081B64:
	add r0, r0, #0x1
	add sp, #0x10
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081B6C:
	ldr r1, _02081D2C ; =0x00000584
	ldrb r0, [r4, r1]
	cmp r0, #0x0
	bne _02081B76
_02081B74:
	b _02081DBC
_02081B76:
	mov r0, #0x0
	strb r0, [r4, r1]
	add r1, r2, #0x2
	ldr r1, [r4, r1]
	add r3, r1, #0x1
	add r1, r2, #0x2
	str r3, [r4, r1]
	ldr r1, [r4, r1]
	cmp r1, #0x4
	bge _02081B94
	ldrb r0, [r4, r2]
	add sp, #0x10
	sub r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081B94:
	add r1, r2, #0x2
	str r0, [r4, r1]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081BA2:
	mov r0, #0xe
	bl sub_02031588
	ldr r0, _02081D2C ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081BBA:
	mov r0, #0xe
	bl sub_020315D8
	cmp r0, #0x1
	bne _02081C8E
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081BD0:
	add r2, sp, #0x8
	add r0, r4, #0x0
	mov r1, #0x0
	add r2, #0x2
	bl sub_02082894
	ldr r1, _02081D34 ; =0x00000123
	add r2, sp, #0x8
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	add r2, #0x2
	bl sub_02083B48
	cmp r0, #0x1
	bne _02081C8E
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081BFA:
	ldr r0, _02081D2C ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _02081C8E
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081C16:
	mov r0, #0xf
	bl sub_02031588
	ldr r0, _02081D2C ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081C2E:
	mov r0, #0xf
	bl sub_020315D8
	cmp r0, #0x1
	bne _02081C8E
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081C44:
	add r1, r2, #0x0
	sub r1, #0x53
	ldrb r3, [r4, r1]
	add r1, r2, #0x0
	sub r1, #0x5a
	ldrb r1, [r4, r1]
	cmp r3, r1
	bne _02081C7E
	add r1, r2, #0x2
	ldr r1, [r4, r1]
	add r0, r4, #0x0
	add r2, sp, #0x4
	bl sub_02082894
	mov r1, #0x5e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	add r0, r4, #0x0
	add r2, sp, #0x4
	bl sub_02083B48
	cmp r0, #0x1
	bne _02081C8E
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081C7E:
	add r0, r0, #0x1
	add sp, #0x10
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081C86:
	ldr r1, _02081D2C ; =0x00000584
	ldrb r0, [r4, r1]
	cmp r0, #0x0
	bne _02081C90
_02081C8E:
	b _02081DBC
_02081C90:
	mov r0, #0x0
	strb r0, [r4, r1]
	add r1, r2, #0x2
	ldr r1, [r4, r1]
	add r3, r1, #0x1
	add r1, r2, #0x2
	str r3, [r4, r1]
	ldr r1, [r4, r1]
	cmp r1, #0x4
	bge _02081CAE
	ldrb r0, [r4, r2]
	add sp, #0x10
	sub r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081CAE:
	add r1, r2, #0x2
	str r0, [r4, r1]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081CBC:
	mov r0, #0x10
	bl sub_02031588
	ldr r0, _02081D2C ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081CD4:
	mov r0, #0x10
	bl sub_020315D8
	cmp r0, #0x1
	bne _02081DBC
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081CEA:
	sub r2, #0x53
	ldrb r1, [r4, r2]
	add r2, r4, #0x0
	add r0, r4, #0x0
	add r2, #0xd0
	bl sub_02083834
	cmp r0, #0x1
	bne _02081DBC
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081D08:
	ldr r0, _02081D2C ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _02081DBC
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081D24:
	ldr r0, _02081D38 ; =0x00000127
	b _02081D3C
	.balign 4
_02081D28: .word 0x00000176
_02081D2C: .word 0x00000584
_02081D30: .word 0x00000585
_02081D34: .word 0x00000123
_02081D38: .word 0x00000127
_02081D3C:
	mov r5, #0x0
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ble _02081D62
	mov r7, #0x42
	lsl r7, r7, #0x2
	add r6, r7, #0x0
	add r6, #0x1f
_02081D4C:
	add r0, r5, #0x0
	bl sub_0202DFA4
	bl PlayerProfile_GetTrainerGender
	add r1, r4, r5
	strb r0, [r1, r7]
	ldrb r0, [r4, r6]
	add r5, r5, #0x1
	cmp r5, r0
	blt _02081D4C
_02081D62:
	cmp r5, #0x4
	bge _02081D86
	add r1, r4, #0x0
	mov r0, #0x30
	add r1, #0x30
	mul r0, r5
	add r0, r1, r0
	mov r1, #0x42
	lsl r1, r1, #0x2
_02081D74:
	ldrh r2, [r0, #0x0]
	add r0, #0x30
	lsl r2, r2, #0x12
	lsr r3, r2, #0x1e
	add r2, r4, r5
	add r5, r5, #0x1
	strb r3, [r2, r1]
	cmp r5, #0x4
	blt _02081D74
_02081D86:
	mov r0, #0x47
	lsl r0, r0, #0x2
	ldrb r2, [r4, r0]
	ldr r1, _02081DC0 ; =0x000019B4
	strb r2, [r4, r1]
	add r2, r0, #0x0
	add r2, #0x8
	ldrb r3, [r4, r2]
	add r2, r1, #0x1
	strb r3, [r4, r2]
	add r2, r1, #0x2
	mov r3, #0x1
	strb r3, [r4, r2]
	add r2, r0, #0x0
	add r2, #0xb
	ldrb r2, [r4, r2]
	add r1, r1, #0x3
	strb r2, [r4, r1]
	add r1, r0, #0x0
	mov r2, #0x0
	add r1, #0x64
	str r2, [r4, r1]
	add r0, #0x5a
	strb r2, [r4, r0]
	ldr r0, [sp, #0x0]
	bl sub_0200CAB4
_02081DBC:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02081DC0: .word 0x000019B4

	thumb_func_start sub_02081DC4
sub_02081DC4: ; 0x02081DC4
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl sub_02030F40
	cmp r0, #0x0
	bne _02081DD4
	mov r0, #0x0
	pop {r3-r7, pc}
_02081DD4:
	ldr r0, _02081EA4 ; =0x00000171
	mov r1, #0x1
	strb r1, [r6, r0]
	bl sub_02030F20
	add r4, r0, #0x0
	bl sub_02031190
	mov r5, #0x0
	str r0, [sp, #0x0]
	cmp r4, #0x0
	ble _02081E0A
_02081DEC:
	add r0, r5, #0x0
	bl sub_0202DFA4
	add r7, r0, #0x0
	bne _02081DFA
	bl GF_AssertFail
_02081DFA:
	add r0, r7, #0x0
	bl PlayerProfile_GetGameClearFlag
	cmp r0, #0x0
	beq _02081E0A
	add r5, r5, #0x1
	cmp r5, r4
	blt _02081DEC
_02081E0A:
	cmp r5, r4
	beq _02081E12
	mov r1, #0x0
	b _02081E14
_02081E12:
	mov r1, #0x1
_02081E14:
	ldr r0, _02081EA8 ; =0x00001999
	mov r5, #0x0
	strb r1, [r6, r0]
	cmp r4, #0x0
	ble _02081E3C
_02081E1E:
	add r0, r5, #0x0
	bl sub_0202DFA4
	add r7, r0, #0x0
	bne _02081E2C
	bl GF_AssertFail
_02081E2C:
	add r0, r7, #0x0
	bl PlayerProfile_GetNatDexFlag
	cmp r0, #0x0
	beq _02081E3C
	add r5, r5, #0x1
	cmp r5, r4
	blt _02081E1E
_02081E3C:
	cmp r5, r4
	beq _02081E44
	mov r1, #0x0
	b _02081E46
_02081E44:
	mov r1, #0x1
_02081E46:
	ldr r0, _02081EAC ; =0x0000199A
	ldr r2, _02081EA8 ; =0x00001999
	strb r1, [r6, r0]
	ldrb r1, [r6, r2]
	add r2, r2, #0x1
	ldrb r2, [r6, r2]
	add r0, r6, #0x0
	bl sub_020813F4
	ldr r0, [sp, #0x0]
	mov r1, #0x49
	lsl r0, r0, #0x18
	mov r2, #0x4
	lsr r0, r0, #0x18
	lsl r1, r1, #0x2
	sub r3, r2, r4
	strb r0, [r6, r1]
	add r2, r1, #0x2
	strb r3, [r6, r2]
	add r2, r1, #0x3
	strb r4, [r6, r2]
	sub r1, r1, #0x1
	strb r0, [r6, r1]
	mov r1, #0x64
	add r0, r1, #0x0
	add r0, #0xc1
	strb r1, [r6, r0]
	add r1, #0xbc
	ldrb r0, [r6, r1]
	mov r1, #0x1
	bl sub_02083454
	ldr r1, _02081EB0 ; =0x00000122
	strb r0, [r6, r1]
	add r0, r6, #0x0
	bl sub_020834D0
	ldr r0, _02081EB4 ; =sub_02081680
	add r1, r6, #0x0
	mov r2, #0xa
	bl sub_0200CA44
	mov r1, #0x6
	lsl r1, r1, #0x6
	str r0, [r6, r1]
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_02081EA4: .word 0x00000171
_02081EA8: .word 0x00001999
_02081EAC: .word 0x0000199A
_02081EB0: .word 0x00000122
_02081EB4: .word sub_02081680

	thumb_func_start sub_02081EB8
sub_02081EB8: ; 0x02081EB8
	ldr r3, _02081EBC ; =sub_02081EC0
	bx r3
	.balign 4
_02081EBC: .word sub_02081EC0

	thumb_func_start sub_02081EC0
sub_02081EC0: ; 0x02081EC0
	mov r1, #0x6
	lsl r1, r1, #0x6
	ldr r0, [r0, r1]
	cmp r0, #0x0
	bne _02081ECE
	mov r0, #0x1
	bx lr
_02081ECE:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_02081ED4
sub_02081ED4: ; 0x02081ED4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	cmp r0, #0x0
	beq _02081EE6
	bl GF_AssertFail
_02081EE6:
	ldr r0, _02081F00 ; =0x00000176
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081F04 ; =sub_02081F08
	add r1, r4, #0x0
	mov r2, #0xa
	bl sub_0200CA44
	mov r1, #0x6
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	pop {r4, pc}
	nop
_02081F00: .word 0x00000176
_02081F04: .word sub_02081F08

	thumb_func_start sub_02081F08
sub_02081F08: ; 0x02081F08
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, _02082014 ; =0x00000176
	ldrb r2, [r4, r1]
	cmp r2, #0x7
	bhi _02082000
	add r3, r2, r2
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_02081F20: ; jump table (using 16-bit offset)
	.short _02081F30 - _02081F20 - 2; case 0
	.short _02081F46 - _02081F20 - 2; case 1
	.short _02081F5A - _02081F20 - 2; case 2
	.short _02081F7A - _02081F20 - 2; case 3
	.short _02081F94 - _02081F20 - 2; case 4
	.short _02081FAA - _02081F20 - 2; case 5
	.short _02081FBE - _02081F20 - 2; case 6
	.short _02081FEC - _02081F20 - 2; case 7
_02081F30:
	mov r0, #0x11
	bl sub_02031588
	ldr r0, _02082018 ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081F46:
	mov r0, #0x11
	bl sub_020315D8
	cmp r0, #0x1
	bne _02082010
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081F5A:
	sub r1, #0x53
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	lsl r2, r1, #0x2
	add r2, r4, r2
	add r2, #0xf8
	ldr r2, [r2, #0x0]
	bl sub_02083930
	cmp r0, #0x1
	bne _02082010
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081F7A:
	ldr r0, _02082018 ; =0x00000584
	add r2, r1, #0x0
	sub r2, #0x4f
	ldrb r3, [r4, r0]
	ldrb r2, [r4, r2]
	cmp r3, r2
	blo _02082010
	mov r2, #0x0
	strb r2, [r4, r0]
	ldrb r0, [r4, r1]
	add r0, r0, #0x1
	strb r0, [r4, r1]
	pop {r4, pc}
_02081F94:
	mov r0, #0x12
	bl sub_02031588
	ldr r0, _02082018 ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081FAA:
	mov r0, #0x12
	bl sub_020315D8
	cmp r0, #0x1
	bne _02082010
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081FBE:
	add r0, r1, #0x0
	sub r0, #0x53
	ldrb r3, [r4, r0]
	add r0, r1, #0x0
	sub r0, #0x5a
	ldrb r0, [r4, r0]
	cmp r3, r0
	bne _02081FE6
	add r1, r4, #0x0
	add r0, r4, #0x0
	add r1, #0xf8
	bl sub_020839C0
	cmp r0, #0x1
	bne _02082010
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081FE6:
	add r0, r2, #0x1
	strb r0, [r4, r1]
	pop {r4, pc}
_02081FEC:
	ldr r0, _02082018 ; =0x00000584
	ldrb r2, [r4, r0]
	cmp r2, #0x0
	beq _02082010
	mov r2, #0x0
	strb r2, [r4, r0]
	ldrb r0, [r4, r1]
	add r0, r0, #0x1
	strb r0, [r4, r1]
	pop {r4, pc}
_02082000:
	mov r1, #0x6
	mov r2, #0x0
	lsl r1, r1, #0x6
	str r2, [r4, r1]
	sub r1, #0xa
	strb r2, [r4, r1]
	bl sub_0200CAB4
_02082010:
	pop {r4, pc}
	nop
_02082014: .word 0x00000176
_02082018: .word 0x00000584

	thumb_func_start sub_0208201C
sub_0208201C: ; 0x0208201C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r2, #0x0
	lsl r2, r4, #0x3
	add r2, r5, r2
	add r2, #0xd0
	ldrh r2, [r2, #0x0]
	add r1, r3, #0x0
	bl BufferContestJudgeName
	pop {r3-r5, pc}

	thumb_func_start sub_02082034
sub_02082034: ; 0x02082034
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl sub_020832E4
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	lsl r2, r3, #0x2
	add r4, r5, r3
	mov r3, #0x42
	add r2, r5, r2
	lsl r3, r3, #0x2
	add r2, #0xe8
	ldrb r3, [r4, r3]
	ldr r2, [r2, #0x0]
	add r1, r6, #0x0
	bl BufferString
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_0208206C
sub_0208206C: ; 0x0208206C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl sub_020832E4
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl sub_020690E4
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl BufferBoxMonNickname
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_02082090
sub_02082090: ; 0x02082090
	push {r3-r5, lr}
	add r4, r2, #0x0
	mov r2, #0x12
	add r3, r0, #0x0
	lsl r2, r2, #0x4
	add r5, r1, #0x0
	add r1, r2, #0x1
	ldrb r0, [r3, r2]
	add r2, #0x51
	ldrb r1, [r3, r1]
	ldrb r2, [r3, r2]
	bl sub_02083228
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl BufferContestMessage
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_020820B8
sub_020820B8: ; 0x020820B8
	push {r3-r5, lr}
	add r5, r1, #0x0
	ldr r1, _020820D8 ; =0x0000011F
	add r3, r0, #0x0
	ldrb r0, [r3, r1]
	add r1, r1, #0x2
	ldrb r1, [r3, r1]
	add r4, r2, #0x0
	bl sub_020832A4
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl BufferContestMessage2
	pop {r3-r5, pc}
	.balign 4
_020820D8: .word 0x0000011F

	thumb_func_start sub_020820DC
sub_020820DC: ; 0x020820DC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r1, #0x13
	add r6, r2, #0x0
	mov r0, #0x0
	add r3, r5, #0x0
	lsl r1, r1, #0x4
_020820EC:
	ldrb r2, [r3, r1]
	cmp r2, #0x0
	beq _020820FA
	add r0, r0, #0x1
	add r3, #0xc
	cmp r0, #0x4
	blt _020820EC
_020820FA:
	bl sub_020832DC
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl sub_02082034
	pop {r4-r6, pc}

	thumb_func_start sub_0208210C
sub_0208210C: ; 0x0208210C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r1, #0x13
	add r6, r2, #0x0
	mov r0, #0x0
	add r3, r5, #0x0
	lsl r1, r1, #0x4
_0208211C:
	ldrb r2, [r3, r1]
	cmp r2, #0x0
	beq _0208212A
	add r0, r0, #0x1
	add r3, #0xc
	cmp r0, #0x4
	blt _0208211C
_0208212A:
	bl sub_020832DC
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl sub_0208206C
	pop {r4-r6, pc}

	thumb_func_start sub_0208213C
sub_0208213C: ; 0x0208213C
	mov r0, #0x1
	bx lr

	thumb_func_start sub_02082140
sub_02082140: ; 0x02082140
	push {r3, lr}
	ldr r2, _02082154 ; =0x00000171
	ldrb r0, [r0, r2]
	cmp r0, #0x0
	beq _02082150
	add r0, r1, #0x0
	bl sub_02031588
_02082150:
	pop {r3, pc}
	nop
_02082154: .word 0x00000171

	thumb_func_start sub_02082158
sub_02082158: ; 0x02082158
	push {r3, lr}
	ldr r2, _02082178 ; =0x00000171
	ldrb r0, [r0, r2]
	cmp r0, #0x0
	bne _02082166
	mov r0, #0x1
	pop {r3, pc}
_02082166:
	add r0, r1, #0x0
	bl sub_020315D8
	cmp r0, #0x1
	bne _02082174
	mov r0, #0x1
	pop {r3, pc}
_02082174:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02082178: .word 0x00000171

	thumb_func_start sub_0208217C
sub_0208217C: ; 0x0208217C
	ldr r2, _0208218C ; =0x00000123
	mov r1, #0xc
	ldrb r3, [r0, r2]
	add r2, #0xd
	mul r1, r3
	add r0, r0, r1
	ldrb r0, [r0, r2]
	bx lr
	.balign 4
_0208218C: .word 0x00000123

	thumb_func_start sub_02082190
sub_02082190: ; 0x02082190
	push {r3, lr}
	mov r1, #0x13
	mov r3, #0x0
	lsl r1, r1, #0x4
_02082198:
	ldrb r2, [r0, r1]
	cmp r2, #0x0
	bne _020821A6
	add r0, r3, #0x0
	bl sub_020832DC
	pop {r3, pc}
_020821A6:
	add r3, r3, #0x1
	add r0, #0xc
	cmp r3, #0x4
	blt _02082198
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_020821B4
sub_020821B4: ; 0x020821B4
	ldr r1, _020821BC ; =0x00000123
	ldr r3, _020821C0 ; =sub_020832DC
	ldrb r0, [r0, r1]
	bx r3
	.balign 4
_020821BC: .word 0x00000123
_020821C0: .word sub_020832DC

	thumb_func_start sub_020821C4
sub_020821C4: ; 0x020821C4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl sub_020832E4
	lsl r0, r0, #0x1
	add r1, r4, r0
	mov r0, #0x45
	lsl r0, r0, #0x2
	ldrh r0, [r1, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_020821DC
sub_020821DC: ; 0x020821DC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl sub_020832E4
	add r1, r4, r0
	mov r0, #0x11
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	pop {r4, pc}

	thumb_func_start sub_020821F0
sub_020821F0: ; 0x020821F0
	push {r3, lr}
	ldr r1, _02082210 ; =0x00000171
	ldrb r1, [r0, r1]
	cmp r1, #0x1
	bne _020821FE
	mov r0, #0x1
	pop {r3, pc}
_020821FE:
	bl sub_020832EC
	cmp r0, #0x1
	bne _0208220A
	mov r0, #0x2
	pop {r3, pc}
_0208220A:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02082210: .word 0x00000171

	thumb_func_start sub_02082214
sub_02082214: ; 0x02082214
	push {r4-r5}
	mov r4, #0x12
	lsl r4, r4, #0x4
	ldrb r5, [r0, r4]
	strh r5, [r1, #0x0]
	sub r1, r4, #0x1
	ldrb r1, [r0, r1]
	strh r1, [r2, #0x0]
	add r1, r4, #0x1
	ldrb r1, [r0, r1]
	strh r1, [r3, #0x0]
	ldr r1, _02082238 ; =0x00001998
	ldrb r1, [r0, r1]
	ldr r0, [sp, #0x8]
	strh r1, [r0, #0x0]
	pop {r4-r5}
	bx lr
	nop
_02082238: .word 0x00001998

	thumb_func_start sub_0208223C
sub_0208223C: ; 0x0208223C
	ldr r1, _02082244 ; =0x00000171
	ldr r3, _02082248 ; =sub_020833D4
	ldrb r0, [r0, r1]
	bx r3
	.balign 4
_02082244: .word 0x00000171
_02082248: .word sub_020833D4

	thumb_func_start sub_0208224C
sub_0208224C: ; 0x0208224C
	ldr r3, _02082250 ; =sub_02083404
	bx r3
	.balign 4
_02082250: .word sub_02083404

	thumb_func_start sub_02082254
sub_02082254: ; 0x02082254
	push {r4, lr}
	mov r1, #0x12
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldrb r0, [r4, r1]
	sub r1, r1, #0x1
	ldrb r1, [r4, r1]
	bl sub_0208341C
	add r1, r0, #0x0
	ldr r0, _02082280 ; =0x00001990
	mov r2, #0x0
	ldr r0, [r4, r0]
	bl GetMonData
	cmp r0, #0x0
	beq _0208227A
	mov r0, #0x1
	pop {r4, pc}
_0208227A:
	mov r0, #0x0
	pop {r4, pc}
	nop
_02082280: .word 0x00001990

	thumb_func_start sub_02082284
sub_02082284: ; 0x02082284
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, _020822EC ; =0x0000011F
	add r5, r2, #0x0
	ldrb r2, [r0, r1]
	cmp r2, #0x4
	bhi _020822D0
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0208229E: ; jump table (using 16-bit offset)
	.short _020822A8 - _0208229E - 2; case 0
	.short _020822B0 - _0208229E - 2; case 1
	.short _020822B8 - _0208229E - 2; case 2
	.short _020822C0 - _0208229E - 2; case 3
	.short _020822C8 - _0208229E - 2; case 4
_020822A8:
	add r1, r1, #0x1
	ldrb r0, [r0, r1]
	add r0, #0x21
	b _020822D6
_020822B0:
	add r1, r1, #0x1
	ldrb r0, [r0, r1]
	add r0, #0x25
	b _020822D6
_020822B8:
	add r1, r1, #0x1
	ldrb r0, [r0, r1]
	add r0, #0x29
	b _020822D6
_020822C0:
	add r1, r1, #0x1
	ldrb r0, [r0, r1]
	add r0, #0x2d
	b _020822D6
_020822C8:
	add r1, r1, #0x1
	ldrb r0, [r0, r1]
	add r0, #0x31
	b _020822D6
_020822D0:
	bl GF_AssertFail
	pop {r3-r5, pc}
_020822D6:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r1, #0x3
	bl sub_0207FC5C
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl BufferRibbonNameOrDesc
	pop {r3-r5, pc}
	.balign 4
_020822EC: .word 0x0000011F

	thumb_func_start sub_020822F0
sub_020822F0: ; 0x020822F0
	push {r3-r5, lr}
	mov r4, #0x64
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r0, #0xbf
	ldrb r1, [r5, r0]
	mov r0, #0xc
	mul r0, r1
	add r1, r5, r0
	add r0, r4, #0x0
	add r0, #0xcc
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _02082310
	ldr r0, _0208243C ; =0x0000FFFF
	pop {r3-r5, pc}
_02082310:
	add r0, r4, #0x0
	add r0, #0xbb
	ldrb r0, [r5, r0]
	cmp r0, #0x4
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02082326: ; jump table (using 16-bit offset)
	.short _02082330 - _02082326 - 2; case 0
	.short _0208235E - _02082326 - 2; case 1
	.short _0208238C - _02082326 - 2; case 2
	.short _020823BA - _02082326 - 2; case 3
	.short _020823E8 - _02082326 - 2; case 4
_02082330:
	add r0, r4, #0x0
	add r0, #0xbc
	ldrb r0, [r5, r0]
	cmp r0, #0x3
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02082346: ; jump table (using 16-bit offset)
	.short _0208234E - _02082346 - 2; case 0
	.short _02082352 - _02082346 - 2; case 1
	.short _02082356 - _02082346 - 2; case 2
	.short _0208235A - _02082346 - 2; case 3
_0208234E:
	mov r4, #0x49
	b _02082414
_02082352:
	mov r4, #0x4e
	b _02082414
_02082356:
	mov r4, #0x53
	b _02082414
_0208235A:
	mov r4, #0x58
	b _02082414
_0208235E:
	add r0, r4, #0x0
	add r0, #0xbc
	ldrb r0, [r5, r0]
	cmp r0, #0x3
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02082374: ; jump table (using 16-bit offset)
	.short _0208237C - _02082374 - 2; case 0
	.short _02082380 - _02082374 - 2; case 1
	.short _02082384 - _02082374 - 2; case 2
	.short _02082388 - _02082374 - 2; case 3
_0208237C:
	mov r4, #0x4a
	b _02082414
_02082380:
	mov r4, #0x4f
	b _02082414
_02082384:
	mov r4, #0x54
	b _02082414
_02082388:
	mov r4, #0x59
	b _02082414
_0208238C:
	add r0, r4, #0x0
	add r0, #0xbc
	ldrb r0, [r5, r0]
	cmp r0, #0x3
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020823A2: ; jump table (using 16-bit offset)
	.short _020823AA - _020823A2 - 2; case 0
	.short _020823AE - _020823A2 - 2; case 1
	.short _020823B2 - _020823A2 - 2; case 2
	.short _020823B6 - _020823A2 - 2; case 3
_020823AA:
	mov r4, #0x48
	b _02082414
_020823AE:
	mov r4, #0x4d
	b _02082414
_020823B2:
	mov r4, #0x52
	b _02082414
_020823B6:
	mov r4, #0x57
	b _02082414
_020823BA:
	add r0, r4, #0x0
	add r0, #0xbc
	ldrb r0, [r5, r0]
	cmp r0, #0x3
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020823D0: ; jump table (using 16-bit offset)
	.short _020823D8 - _020823D0 - 2; case 0
	.short _020823DC - _020823D0 - 2; case 1
	.short _020823E0 - _020823D0 - 2; case 2
	.short _020823E4 - _020823D0 - 2; case 3
_020823D8:
	mov r4, #0x4c
	b _02082414
_020823DC:
	mov r4, #0x51
	b _02082414
_020823E0:
	mov r4, #0x56
	b _02082414
_020823E4:
	mov r4, #0x5b
	b _02082414
_020823E8:
	add r0, r4, #0x0
	add r0, #0xbc
	ldrb r0, [r5, r0]
	cmp r0, #0x3
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020823FE: ; jump table (using 16-bit offset)
	.short _02082406 - _020823FE - 2; case 0
	.short _0208240A - _020823FE - 2; case 1
	.short _0208240E - _020823FE - 2; case 2
	.short _02082412 - _020823FE - 2; case 3
_02082406:
	mov r4, #0x4b
	b _02082414
_0208240A:
	mov r4, #0x50
	b _02082414
_0208240E:
	mov r4, #0x55
	b _02082414
_02082412:
	mov r4, #0x5a
_02082414:
	cmp r4, #0x64
	bne _0208241C
	bl GF_AssertFail
_0208241C:
	ldr r0, _02082440 ; =0x0000198C
	ldr r0, [r5, r0]
	bl Save_FashionData_Get
	bl sub_0202708C
	add r1, r4, #0x0
	mov r2, #0x1
	bl sub_020270D8
	cmp r0, #0x0
	bne _02082438
	ldr r0, _0208243C ; =0x0000FFFF
	pop {r3-r5, pc}
_02082438:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_0208243C: .word 0x0000FFFF
_02082440: .word 0x0000198C

	thumb_func_start sub_02082444
sub_02082444: ; 0x02082444
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _020824F0 ; =0x000019BC
	add r6, r1, #0x0
	ldr r0, [r5, r0]
	cmp r0, #0x0
	beq _02082456
	bl GF_AssertFail
_02082456:
	mov r0, #0x4
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0x10
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r6, #0x0
	bl sub_020832E4
	strb r0, [r4, #0xc]
	ldrb r0, [r4, #0xc]
	mov r1, #0x43
	lsl r1, r1, #0x2
	add r0, r5, r0
	ldrb r2, [r0, r1]
	mov r0, #0x1
	and r0, r2
	add r2, r1, #0x0
	add r2, #0x65
	ldrb r2, [r5, r2]
	cmp r2, #0x1
	bne _02082494
	mov r1, #0x6
	ldr r2, _020824F4 ; =UNK_020FBBAC
	mul r1, r0
	add r0, r2, r1
	str r0, [r4, #0x4]
	b _020824DC
_02082494:
	add r1, #0x14
	ldrb r1, [r5, r1]
	cmp r1, #0x3
	bhi _020824D2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020824A8: ; jump table (using 16-bit offset)
	.short _020824B0 - _020824A8 - 2; case 0
	.short _020824BC - _020824A8 - 2; case 1
	.short _020824C6 - _020824A8 - 2; case 2
	.short _020824D2 - _020824A8 - 2; case 3
_020824B0:
	lsl r1, r0, #0x1
	ldr r2, _020824F8 ; =UNK_020FBB90
	add r0, r0, r1
	add r0, r2, r0
	str r0, [r4, #0x4]
	b _020824DC
_020824BC:
	ldr r1, _020824FC ; =UNK_020FBB98
	lsl r0, r0, #0x2
	add r0, r1, r0
	str r0, [r4, #0x4]
	b _020824DC
_020824C6:
	lsl r1, r0, #0x2
	ldr r2, _02082500 ; =UNK_020FBBA0
	add r0, r0, r1
	add r0, r2, r0
	str r0, [r4, #0x4]
	b _020824DC
_020824D2:
	mov r1, #0x6
	ldr r2, _020824F4 ; =UNK_020FBBAC
	mul r1, r0
	add r0, r2, r1
	str r0, [r4, #0x4]
_020824DC:
	ldr r0, _02082504 ; =sub_0208251C
	add r1, r5, #0x0
	mov r2, #0x64
	bl sub_0200CA44
	str r0, [r4, #0x0]
	ldr r0, _020824F0 ; =0x000019BC
	str r4, [r5, r0]
	pop {r4-r6, pc}
	nop
_020824F0: .word 0x000019BC
_020824F4: .word UNK_020FBBAC
_020824F8: .word UNK_020FBB90
_020824FC: .word UNK_020FBB98
_02082500: .word UNK_020FBBA0
_02082504: .word sub_0208251C

	thumb_func_start sub_02082508
sub_02082508: ; 0x02082508
	ldr r1, _02082518 ; =0x000019BC
	ldr r0, [r0, r1]
	cmp r0, #0x0
	bne _02082514
	mov r0, #0x1
	bx lr
_02082514:
	mov r0, #0x0
	bx lr
	.balign 4
_02082518: .word 0x000019BC

	thumb_func_start sub_0208251C
sub_0208251C: ; 0x0208251C
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r0, #0x0
	ldr r0, _02082598 ; =0x000019BC
	add r5, r1, #0x0
	ldr r4, [r5, r0]
	mov r0, #0x1
	bl IsBrightnessTransitionActive
	cmp r0, #0x0
	beq _02082594
	ldrb r0, [r4, #0xb]
	cmp r0, #0x0
	bne _02082580
	mov r0, #0x8
	ldrsh r1, [r4, r0]
	add r1, r1, #0x1
	strh r1, [r4, #0x8]
	ldrsh r2, [r4, r0]
	ldrb r0, [r4, #0xa]
	ldr r1, [r4, #0x4]
	ldrb r0, [r1, r0]
	cmp r2, r0
	ble _02082594
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x6
	mov r1, #0x0
	mov r2, #0x4
	mov r3, #0x3f
	bl StartBrightnessTransition
	ldr r0, _0208259C ; =0x000005F8
	bl PlaySE
	ldrb r0, [r4, #0xa]
	add r0, r0, #0x1
	strb r0, [r4, #0xa]
	mov r0, #0x0
	strh r0, [r4, #0x8]
	ldrb r0, [r4, #0xa]
	ldr r1, [r4, #0x4]
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	bne _02082594
	ldrb r0, [r4, #0xb]
	add sp, #0x4
	add r0, r0, #0x1
	strb r0, [r4, #0xb]
	pop {r3-r6, pc}
_02082580:
	ldr r0, _02082598 ; =0x000019BC
	ldr r0, [r5, r0]
	bl FreeToHeap
	ldr r0, _02082598 ; =0x000019BC
	mov r1, #0x0
	str r1, [r5, r0]
	add r0, r6, #0x0
	bl sub_0200CAB4
_02082594:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02082598: .word 0x000019BC
_0208259C: .word 0x000005F8

	thumb_func_start sub_020825A0
sub_020825A0: ; 0x020825A0
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r0, #0x13
	str r2, [sp, #0x4]
	ldr r6, [sp, #0x20]
	ldr r7, [sp, #0x24]
	str r1, [sp, #0x0]
	str r3, [sp, #0x8]
	mov r4, #0x0
	add r2, r5, #0x0
	lsl r0, r0, #0x4
_020825B8:
	ldrb r1, [r2, r0]
	cmp r1, #0x0
	beq _020825C6
	add r4, r4, #0x1
	add r2, #0xc
	cmp r4, #0x4
	blt _020825B8
_020825C6:
	add r0, r4, #0x0
	bl sub_020832DC
	ldr r1, [sp, #0x0]
	str r0, [r1, #0x0]
	ldr r1, _02082628 ; =0x00000171
	ldr r0, [sp, #0x4]
	ldrb r2, [r5, r1]
	sub r1, #0x4a
	str r2, [r0, #0x0]
	ldrb r0, [r5, r1]
	cmp r4, r0
	blt _020825E6
	mov r1, #0x1
	ldr r0, [sp, #0x8]
	b _020825EA
_020825E6:
	ldr r0, [sp, #0x8]
	mov r1, #0x0
_020825EA:
	str r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [r6, #0x0]
	str r0, [r7, #0x0]
	ldr r0, _0208262C ; =0x00000121
	ldrb r0, [r5, r0]
	cmp r0, #0x8
	bhi _02082624
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02082606: ; jump table (using 16-bit offset)
	.short _02082624 - _02082606 - 2; case 0
	.short _02082624 - _02082606 - 2; case 1
	.short _02082624 - _02082606 - 2; case 2
	.short _02082618 - _02082606 - 2; case 3
	.short _02082620 - _02082606 - 2; case 4
	.short _02082618 - _02082606 - 2; case 5
	.short _02082620 - _02082606 - 2; case 6
	.short _02082618 - _02082606 - 2; case 7
	.short _02082620 - _02082606 - 2; case 8
_02082618:
	mov r0, #0x1
	add sp, #0xc
	str r0, [r6, #0x0]
	pop {r4-r7, pc}
_02082620:
	mov r0, #0x1
	str r0, [r7, #0x0]
_02082624:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02082628: .word 0x00000171
_0208262C: .word 0x00000121

	thumb_func_start sub_02082630
sub_02082630: ; 0x02082630
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r0, _02082840 ; =0x00000121
	str r2, [sp, #0x4]
	ldrb r0, [r4, r0]
	add r6, r3, #0x0
	mov r5, #0x0
	cmp r0, #0x8
	bhi _02082666
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02082650: ; jump table (using 16-bit offset)
	.short _02082666 - _02082650 - 2; case 0
	.short _02082666 - _02082650 - 2; case 1
	.short _02082666 - _02082650 - 2; case 2
	.short _02082662 - _02082650 - 2; case 3
	.short _02082662 - _02082650 - 2; case 4
	.short _02082662 - _02082650 - 2; case 5
	.short _02082662 - _02082650 - 2; case 6
	.short _02082662 - _02082650 - 2; case 7
	.short _02082662 - _02082650 - 2; case 8
_02082662:
	add sp, #0xc
	pop {r4-r7, pc}
_02082666:
	ldr r2, _02082844 ; =0x00000171
	ldrb r0, [r4, r2]
	cmp r0, #0x0
	ldr r0, _02082848 ; =0x0000198C
	beq _02082672
	b _02082774
_02082672:
	ldr r0, [r4, r0]
	bl SaveArray_Flags_Get
	add r6, r0, #0x0
	ldr r0, _02082840 ; =0x00000121
	ldrb r1, [r4, r0]
	cmp r1, #0x2
	bne _020826AC
	sub r0, r0, #0x1
	ldrb r0, [r4, r0]
	cmp r0, #0x3
	blo _020826AC
	add r0, r4, #0x0
	bl sub_0208217C
	cmp r0, #0x0
	bne _020826AC
	ldr r1, _0208284C ; =0x0000011F
	add r0, r6, #0x0
	ldrb r1, [r4, r1]
	bl sub_0205EE60
	cmp r0, #0x0
	bne _020826AC
	ldr r1, _0208284C ; =0x0000011F
	add r0, r6, #0x0
	ldrb r1, [r4, r1]
	bl sub_0205EE08
_020826AC:
	add r0, r4, #0x0
	bl sub_0208217C
	cmp r0, #0x0
	bne _020826EA
	mov r1, #0x1
	add r0, sp, #0x8
	strb r1, [r0, #0x0]
	mov r1, #0x12
	lsl r1, r1, #0x4
	ldrb r0, [r4, r1]
	sub r1, r1, #0x1
	ldrb r1, [r4, r1]
	bl sub_0208341C
	add r6, r0, #0x0
	ldr r0, _02082850 ; =0x00001990
	add r1, r6, #0x0
	ldr r0, [r4, r0]
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _020826DE
	mov r5, #0x1
_020826DE:
	ldr r0, _02082850 ; =0x00001990
	add r1, r6, #0x0
	ldr r0, [r4, r0]
	add r2, sp, #0x8
	bl SetMonData
_020826EA:
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl sub_02022504
	ldr r3, _02082854 ; =0x00000123
	mov r1, #0xc
	ldrb r2, [r4, r3]
	mul r1, r2
	add r2, r4, r1
	add r1, r3, #0x0
	add r1, #0xd
	ldrb r1, [r2, r1]
	sub r2, r3, #0x4
	sub r3, r3, #0x3
	add r1, r1, #0x1
	str r1, [sp, #0x0]
	ldr r1, _02082850 ; =0x00001990
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	ldr r1, [r4, r1]
	bl sub_02060F10
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl Save_GameStats_Get
	mov r1, #0x3f
	add r6, r0, #0x0
	bl GameStats_Inc
	add r0, r4, #0x0
	bl sub_0208217C
	cmp r0, #0x0
	bne _02082740
	add r0, r6, #0x0
	mov r1, #0x41
	bl GameStats_Inc
	add r0, r6, #0x0
	mov r1, #0xd
	bl GameStats_AddSpecial
_02082740:
	cmp r5, #0x1
	bne _0208274C
	add r0, r6, #0x0
	mov r1, #0x43
	bl GameStats_Inc
_0208274C:
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl Save_Pokedex_Get
	add r7, r0, #0x0
	ldr r0, _02082858 ; =0x00000127
	ldrb r6, [r4, r0]
	cmp r6, #0x4
	bge _020827E8
	lsl r0, r6, #0x2
	add r5, r4, r0
_02082762:
	ldr r1, [r5, #0x0]
	add r0, r7, #0x0
	bl Pokedex_SetMonSeenFlag
	add r6, r6, #0x1
	add r5, r5, #0x4
	cmp r6, #0x4
	blt _02082762
	b _020827E8
_02082774:
	add r3, r2, #0x0
	sub r3, #0x4e
	ldrb r5, [r4, r3]
	add r1, r2, #0x0
	mov r3, #0xc
	mul r3, r5
	sub r1, #0x52
	add r3, r4, r3
	sub r2, #0x41
	ldrb r1, [r4, r1]
	ldrb r2, [r3, r2]
	ldr r0, [r4, r0]
	bl sub_0202C108
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl Save_GameStats_Get
	mov r1, #0x40
	add r5, r0, #0x0
	bl GameStats_Inc
	add r0, r4, #0x0
	bl sub_0208217C
	cmp r0, #0x0
	bne _020827BA
	add r0, r5, #0x0
	mov r1, #0x42
	bl GameStats_Inc
	add r0, r5, #0x0
	mov r1, #0x13
	bl GameStats_AddSpecial
_020827BA:
	ldr r1, _02082854 ; =0x00000123
	mov r0, #0xc
	ldrb r2, [r4, r1]
	add r1, #0xd
	mul r0, r2
	add r0, r4, r0
	ldrb r0, [r0, r1]
	mov r1, #0xb
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_02029500
	add r5, r0, #0x0
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl sub_020289A4
	add r0, r6, #0x0
	add r1, r5, #0x0
	mov r2, #0x4
	bl sub_02028AD4
_020827E8:
	add r0, r4, #0x0
	bl sub_0208217C
	cmp r0, #0x0
	bne _02082820
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl Save_FashionData_Get
	ldr r1, _0208284C ; =0x0000011F
	ldrb r1, [r4, r1]
	bl sub_02027044
	add r5, r0, #0x0
	bl sub_02027740
	ldr r1, _02082854 ; =0x00000123
	add r0, r5, #0x0
	ldrb r1, [r4, r1]
	lsl r1, r1, #0x2
	add r1, r4, r1
	add r1, #0xf8
	ldr r1, [r1, #0x0]
	bl sub_020278DC
	add r0, r5, #0x0
	bl sub_02027710
_02082820:
	add r0, r4, #0x0
	bl sub_0208217C
	cmp r0, #0x0
	bne _0208283A
	ldr r0, _02082850 ; =0x00001990
	ldr r2, [sp, #0x4]
	ldr r0, [r4, r0]
	lsl r2, r2, #0x10
	mov r1, #0x9
	lsr r2, r2, #0x10
	bl MonApplyFriendshipMod
_0208283A:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02082840: .word 0x00000121
_02082844: .word 0x00000171
_02082848: .word 0x0000198C
_0208284C: .word 0x0000011F
_02082850: .word 0x00001990
_02082854: .word 0x00000123
_02082858: .word 0x00000127

	thumb_func_start sub_0208285C
sub_0208285C: ; 0x0208285C
	push {r4, lr}
	bl GF_RTC_TimeToSec
	add r4, r0, #0x0
	bl GetLCRNGSeed
	add r0, #0xa
	mul r0, r4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl SetLCRNGSeed
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02082878
sub_02082878: ; 0x02082878
	ldr r3, _0208287C ; =LCRandom
	bx r3
	.balign 4
_0208287C: .word LCRandom

	thumb_func_start sub_02082880
sub_02082880: ; 0x02082880
	push {r4, lr}
	add r4, r1, #0x0
	bl PRandom
	str r0, [r4, #0x0]
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02082894
sub_02082894: ; 0x02082894
	push {r4-r5}
	mov r5, #0x42
	add r3, r0, r1
	lsl r5, r5, #0x2
	ldrb r4, [r3, r5]
	lsl r1, r1, #0x1
	add r0, r0, r1
	strb r4, [r2, #0x0]
	add r4, r5, #0x4
	ldrb r4, [r3, r4]
	strb r4, [r2, #0x1]
	add r4, r5, #0x0
	add r4, #0x8
	ldrb r3, [r3, r4]
	add r5, #0xc
	strb r3, [r2, #0x2]
	ldrh r0, [r0, r5]
	strh r0, [r2, #0x4]
	pop {r4-r5}
	bx lr
