	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F4334
UNK_020F4334: ; 0x020F4334
	.byte 0x8D, 0x00, 0x91, 0x00, 0x8E, 0x00, 0x8F, 0x00, 0x90, 0x00

	.global UNK_020F433E
UNK_020F433E: ; 0x020F433E
	.byte 0x2E, 0x00

	.global UNK_020F4340
UNK_020F4340: ; 0x020F4340
	.byte 0x01, 0x00, 0x31, 0x00, 0x01, 0x00, 0x2F, 0x00, 0x01, 0x00, 0x34, 0x00, 0x01, 0x00, 0x30, 0x00
	.byte 0x01, 0x00, 0x2D, 0x00, 0x01, 0x00, 0x21, 0x01, 0x10, 0x00, 0x22, 0x01, 0x10, 0x00, 0x23, 0x01
	.byte 0x10, 0x00, 0x24, 0x01, 0x10, 0x00, 0x25, 0x01, 0x10, 0x00, 0x26, 0x01, 0x10, 0x00, 0x10, 0x01
	.byte 0x10, 0x00, 0x11, 0x01, 0x10, 0x00, 0xD6, 0x00, 0x20, 0x00, 0x0F, 0x01, 0x20, 0x00, 0xD5, 0x00
	.byte 0x30, 0x00, 0xDC, 0x00, 0x30, 0x00, 0xE6, 0x00, 0x30, 0x00, 0xE8, 0x00, 0x30, 0x00, 0x0A, 0x01
	.byte 0x30, 0x00, 0x13, 0x01, 0x30, 0x00, 0x1F, 0x01, 0x30, 0x00, 0x46, 0x01, 0x30, 0x00, 0x47, 0x01
	.byte 0x30, 0x00, 0x32, 0x00, 0x30, 0x00, 0x4D, 0x01, 0x20, 0x00, 0x90, 0x01, 0x20, 0x00, 0x84, 0x01
	.byte 0x20, 0x00, 0x74, 0x01, 0x20, 0x00, 0x6F, 0x01, 0x28, 0x00, 0x66, 0x01, 0x28, 0x00, 0x4F, 0x01
	.byte 0x30, 0x00, 0x4B, 0x01, 0x30, 0x00, 0x98, 0x01, 0x40, 0x00, 0x65, 0x01, 0x40, 0x00, 0x7C, 0x01
	.byte 0x40, 0x00, 0x6B, 0x01, 0x50, 0x00, 0x82, 0x01, 0x50, 0x00, 0x8E, 0x01, 0x50, 0x00, 0x61, 0x01
	.byte 0x50, 0x00, 0x00, 0x00

	.text

	thumb_func_start ScrCmd_Unk01DA
ScrCmd_Unk01DA: ; 0x02042354
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r0, #0xa8
	bl ov06_022434BC
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_Unk01DB
ScrCmd_Unk01DB: ; 0x02042364
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FieldSystem_GetSaveDataPtr
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl ov06_022434D0
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r1, #0xa8
	str r0, [r1, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_Unk01DC
ScrCmd_Unk01DC: ; 0x02042394
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r0, #0xa8
	ldr r0, [r0, #0x0]
	bl ov06_02243694
	add r4, #0x80
	ldr r1, [r4, #0x0]
	mov r0, #0x0
	add r1, #0xa8
	str r0, [r1, #0x0]
	pop {r4, pc}

	thumb_func_start ScrCmd_Unk01DD
ScrCmd_Unk01DD: ; 0x020423B0
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	bl ScriptReadHalfword
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r7, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl ScriptReadHalfword
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [sp, #0x4]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r0, #0x80
	ldr r1, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0xa8
	ldr r5, [r0, #0x0]
	ldr r0, [sp, #0x0]
	cmp r0, #0x64
	bls _020423FA
	b _020426F6
_020423FA:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02042406: ; jump table (using 16-bit offset)
	.short _020424D0 - _02042406 - 2; case 0
	.short _020424DA - _02042406 - 2; case 1
	.short _020424F6 - _02042406 - 2; case 2
	.short _020424FC - _02042406 - 2; case 3
	.short _02042508 - _02042406 - 2; case 4
	.short _02042516 - _02042406 - 2; case 5
	.short _0204251E - _02042406 - 2; case 6
	.short _020426F6 - _02042406 - 2; case 7
	.short _02042526 - _02042406 - 2; case 8
	.short _02042532 - _02042406 - 2; case 9
	.short _02042540 - _02042406 - 2; case 10
	.short _0204254E - _02042406 - 2; case 11
	.short _0204255A - _02042406 - 2; case 12
	.short _020426F6 - _02042406 - 2; case 13
	.short _02042564 - _02042406 - 2; case 14
	.short _0204256E - _02042406 - 2; case 15
	.short _02042578 - _02042406 - 2; case 16
	.short _020426F6 - _02042406 - 2; case 17
	.short _020426F6 - _02042406 - 2; case 18
	.short _020426F6 - _02042406 - 2; case 19
	.short _020426F6 - _02042406 - 2; case 20
	.short _020426F6 - _02042406 - 2; case 21
	.short _020426F6 - _02042406 - 2; case 22
	.short _020426F6 - _02042406 - 2; case 23
	.short _020426F6 - _02042406 - 2; case 24
	.short _020426F6 - _02042406 - 2; case 25
	.short _020426F6 - _02042406 - 2; case 26
	.short _020426F6 - _02042406 - 2; case 27
	.short _020426F6 - _02042406 - 2; case 28
	.short _020426F6 - _02042406 - 2; case 29
	.short _0204258A - _02042406 - 2; case 30
	.short _020425A2 - _02042406 - 2; case 31
	.short _020425BC - _02042406 - 2; case 32
	.short _020425C8 - _02042406 - 2; case 33
	.short _020425D2 - _02042406 - 2; case 34
	.short _020425DC - _02042406 - 2; case 35
	.short _020425E6 - _02042406 - 2; case 36
	.short _020425F0 - _02042406 - 2; case 37
	.short _020425F8 - _02042406 - 2; case 38
	.short _02042600 - _02042406 - 2; case 39
	.short _02042608 - _02042406 - 2; case 40
	.short _0204261A - _02042406 - 2; case 41
	.short _02042626 - _02042406 - 2; case 42
	.short _02042642 - _02042406 - 2; case 43
	.short _0204264C - _02042406 - 2; case 44
	.short _02042656 - _02042406 - 2; case 45
	.short _02042660 - _02042406 - 2; case 46
	.short _0204266A - _02042406 - 2; case 47
	.short _02042674 - _02042406 - 2; case 48
	.short _02042680 - _02042406 - 2; case 49
	.short _0204268C - _02042406 - 2; case 50
	.short _020426A0 - _02042406 - 2; case 51
	.short _020426AA - _02042406 - 2; case 52
	.short _020426B4 - _02042406 - 2; case 53
	.short _020426BE - _02042406 - 2; case 54
	.short _020426CC - _02042406 - 2; case 55
	.short _02042612 - _02042406 - 2; case 56
	.short _020426DA - _02042406 - 2; case 57
	.short _020426F6 - _02042406 - 2; case 58
	.short _020426F6 - _02042406 - 2; case 59
	.short _020426F6 - _02042406 - 2; case 60
	.short _020426F6 - _02042406 - 2; case 61
	.short _020426F6 - _02042406 - 2; case 62
	.short _020426F6 - _02042406 - 2; case 63
	.short _020426F6 - _02042406 - 2; case 64
	.short _020426F6 - _02042406 - 2; case 65
	.short _020426F6 - _02042406 - 2; case 66
	.short _020426F6 - _02042406 - 2; case 67
	.short _020426F6 - _02042406 - 2; case 68
	.short _020426F6 - _02042406 - 2; case 69
	.short _020426F6 - _02042406 - 2; case 70
	.short _020426F6 - _02042406 - 2; case 71
	.short _020426F6 - _02042406 - 2; case 72
	.short _020426F6 - _02042406 - 2; case 73
	.short _020426F6 - _02042406 - 2; case 74
	.short _020426F6 - _02042406 - 2; case 75
	.short _020426F6 - _02042406 - 2; case 76
	.short _020426F6 - _02042406 - 2; case 77
	.short _020426F6 - _02042406 - 2; case 78
	.short _020426F6 - _02042406 - 2; case 79
	.short _020426F6 - _02042406 - 2; case 80
	.short _020426F6 - _02042406 - 2; case 81
	.short _020426F6 - _02042406 - 2; case 82
	.short _020426F6 - _02042406 - 2; case 83
	.short _020426F6 - _02042406 - 2; case 84
	.short _020426F6 - _02042406 - 2; case 85
	.short _020426F6 - _02042406 - 2; case 86
	.short _020426F6 - _02042406 - 2; case 87
	.short _020426F6 - _02042406 - 2; case 88
	.short _020426F6 - _02042406 - 2; case 89
	.short _020426F6 - _02042406 - 2; case 90
	.short _020426F6 - _02042406 - 2; case 91
	.short _020426F6 - _02042406 - 2; case 92
	.short _020426F6 - _02042406 - 2; case 93
	.short _020426F6 - _02042406 - 2; case 94
	.short _020426F6 - _02042406 - 2; case 95
	.short _020426F6 - _02042406 - 2; case 96
	.short _020426F6 - _02042406 - 2; case 97
	.short _020426F6 - _02042406 - 2; case 98
	.short _020426F6 - _02042406 - 2; case 99
	.short _020426E6 - _02042406 - 2; case 100
_020424D0:
	add r0, r6, #0x0
	bl ov06_0224312C
	strh r0, [r4, #0x0]
	b _020426FA
_020424DA:
	cmp r6, #0x0
	bne _020424EA
	ldrb r0, [r5, #0xe]
	ldr r1, [r1, #0xc]
	bl ov06_022432E4
	strh r0, [r4, #0x0]
	b _020426FA
_020424EA:
	ldr r1, [r1, #0xc]
	add r0, r6, #0x0
	bl ov06_022432E4
	strh r0, [r4, #0x0]
	b _020426FA
_020424F6:
	bl ov06_0224339C
	b _020426FA
_020424FC:
	ldr r0, [r1, #0xc]
	bl SaveStruct23_GetSubstruct1
	bl ov06_022433A8
	b _020426FA
_02042508:
	ldr r0, [r1, #0xc]
	bl SaveStruct23_GetSubstruct1
	bl ov06_022433B0
	strh r0, [r4, #0x0]
	b _020426FA
_02042516:
	add r0, r1, #0x0
	bl ov06_022433B8
	b _020426FA
_0204251E:
	add r0, r1, #0x0
	bl ov06_022433F8
	b _020426FA
_02042526:
	ldr r0, [r1, #0xc]
	add r1, r6, #0x0
	bl ov06_02243408
	strh r0, [r4, #0x0]
	b _020426FA
_02042532:
	ldr r1, [r1, #0xc]
	mov r0, #0x0
	mov r2, #0x2
	bl ov06_02243E74
	strh r0, [r4, #0x0]
	b _020426FA
_02042540:
	mov r0, #0x0
	ldr r1, [r1, #0xc]
	add r2, r0, #0x0
	bl ov06_02243E74
	strh r0, [r4, #0x0]
	b _020426FA
_0204254E:
	ldr r0, [r1, #0xc]
	lsl r1, r6, #0x18
	lsr r1, r1, #0x18
	bl ov06_02243428
	b _020426FA
_0204255A:
	ldr r0, [r1, #0xc]
	bl ov06_02243448
	strh r0, [r4, #0x0]
	b _020426FA
_02042564:
	ldr r0, [r1, #0xc]
	bl ov06_0224345C
	strh r0, [r4, #0x0]
	b _020426FA
_0204256E:
	ldr r0, [r1, #0xc]
	bl ov06_022434AC
	strh r0, [r4, #0x0]
	b _020426FA
_02042578:
	ldrh r3, [r4, #0x0]
	ldr r0, [r7, #0x74]
	ldr r2, [sp, #0x4]
	add r1, r6, #0x0
	bl sub_0205FD38
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0204258A:
	add r0, r1, #0x0
	mov r1, #0x13
	bl FieldSysGetAttrAddr
	add r2, r0, #0x0
	ldr r1, [r7, #0x74]
	add r0, r5, #0x0
	bl ov06_022436C8
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_020425A2:
	add r0, r1, #0x0
	mov r1, #0x13
	bl FieldSysGetAttrAddr
	add r7, #0x80
	ldr r2, [r7, #0x0]
	add r1, r0, #0x0
	ldr r2, [r2, #0xc]
	add r0, r5, #0x0
	bl ov06_022436E8
	strh r0, [r4, #0x0]
	b _020426FA
_020425BC:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl ov06_02243780
	strh r0, [r4, #0x0]
	b _020426FA
_020425C8:
	add r0, r5, #0x0
	bl ov06_022438DC
	strh r0, [r4, #0x0]
	b _020426FA
_020425D2:
	add r0, r5, #0x0
	bl ov06_022438E0
	strh r0, [r4, #0x0]
	b _020426FA
_020425DC:
	add r0, r5, #0x0
	bl ov06_022438FC
	strh r0, [r4, #0x0]
	b _020426FA
_020425E6:
	add r0, r5, #0x0
	bl ov06_02243920
	strh r0, [r4, #0x0]
	b _020426FA
_020425F0:
	add r0, r5, #0x0
	bl ov06_022439F8
	b _020426FA
_020425F8:
	add r0, r5, #0x0
	bl ov06_02243AD8
	b _020426FA
_02042600:
	add r0, r5, #0x0
	bl ov06_02243BA8
	b _020426FA
_02042608:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl ov06_02243C5C
	b _020426FA
_02042612:
	add r0, r5, #0x0
	bl ov06_02243D3C
	b _020426FA
_0204261A:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl ov06_02243DA0
	strh r0, [r4, #0x0]
	b _020426FA
_02042626:
	add r0, r1, #0x0
	mov r1, #0x17
	bl FieldSysGetAttrAddr
	add r7, #0x80
	add r2, r0, #0x0
	ldr r0, [r7, #0x0]
	add r1, r5, #0x0
	ldr r0, [r0, #0x10]
	bl ov06_02243DB8
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02042642:
	add r0, r5, #0x0
	bl ov06_02243DC0
	strh r0, [r4, #0x0]
	b _020426FA
_0204264C:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl ov06_02243DC4
	b _020426FA
_02042656:
	add r0, r5, #0x0
	bl ov06_02243DD8
	strh r0, [r4, #0x0]
	b _020426FA
_02042660:
	add r0, r5, #0x0
	bl ov06_02243DE0
	strh r0, [r4, #0x0]
	b _020426FA
_0204266A:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl ov06_02243E34
	b _020426FA
_02042674:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl ov06_02243F18
	strh r0, [r4, #0x0]
	b _020426FA
_02042680:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl ov06_02243F50
	strh r0, [r4, #0x0]
	b _020426FA
_0204268C:
	ldrb r1, [r5, #0x10]
	mov r0, #0xe0
	bic r1, r0
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r5, #0x10]
	b _020426FA
_020426A0:
	ldrb r0, [r5, #0x10]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1d
	strh r0, [r4, #0x0]
	b _020426FA
_020426AA:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl ov06_02243838
	b _020426FA
_020426B4:
	add r0, r5, r6
	add r0, #0x2a
	ldrb r0, [r0, #0x0]
	strh r0, [r4, #0x0]
	b _020426FA
_020426BE:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	mov r2, #0x1
	bl ov06_02243E74
	strh r0, [r4, #0x0]
	b _020426FA
_020426CC:
	lsl r1, r6, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl sub_0204290C
	strh r0, [r4, #0x0]
	b _020426FA
_020426DA:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl ov06_02243F9C
	strh r0, [r4, #0x0]
	b _020426FA
_020426E6:
	cmp r5, #0x0
	bne _020426F0
	mov r0, #0x1
	strh r0, [r4, #0x0]
	b _020426FA
_020426F0:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	b _020426FA
_020426F6:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_020426FA:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_Unk01DE
ScrCmd_Unk01DE: ; 0x02042700
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	add r1, #0xa8
	ldr r4, [r1, #0x0]
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
	bl GetVarPointer
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	lsl r2, r6, #0x4
	add r2, r6, r2
	mov r1, #0x38
	lsl r2, r2, #0x4
	mul r1, r7
	add r2, r4, r2
	add r3, r2, r1
	mov r2, #0xb2
	lsl r2, r2, #0x2
	ldrh r1, [r3, r2]
	lsl r1, r1, #0x15
	lsr r4, r1, #0x15
	ldr r1, [sp, #0x0]
	strh r4, [r1, #0x0]
	add r1, r2, #0x4
	ldrh r1, [r3, r1]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk01DF
ScrCmd_Unk01DF: ; 0x02042780
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
	bl sub_0205FE10
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk01E0
ScrCmd_Unk01E0: ; 0x020427A8
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
	bl sub_0205FF5C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk01E1
ScrCmd_Unk01E1: ; 0x020427D0
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
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	add r0, #0xa8
	ldr r6, [r0, #0x0]
	ldr r0, _0204285C ; =0x00000884
	mov r2, #0x46
	add r0, r6, r0
	bl MI_CpuFill8
	cmp r4, #0x0
	beq _0204281E
	cmp r4, #0x1
	beq _02042830
	cmp r4, #0x2
	beq _0204283E
	b _0204284C
_0204281E:
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r0, r1, #0x0
	add r0, #0xa8
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0xc]
	bl ov06_022446FC
	b _0204284C
_02042830:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	add r0, #0xa8
	ldr r0, [r0, #0x0]
	bl ov06_02244758
	b _0204284C
_0204283E:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	add r0, #0xa8
	ldr r0, [r0, #0x0]
	bl ov06_02244770
_0204284C:
	bl sub_02031190
	ldr r1, _02042860 ; =0x0000083E
	add r1, r6, r1
	bl sub_020316AC
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0204285C: .word 0x00000884
_02042860: .word 0x0000083E

	thumb_func_start ScrCmd_Unk01E2
ScrCmd_Unk01E2: ; 0x02042864
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
	bl ScriptReadHalfword
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x10]
	bl sub_0205FDDC
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk01E3
ScrCmd_Unk01E3: ; 0x02042894
	push {r3-r6, lr}
	sub sp, #0x4
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
	bl GetVarPointer
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SaveStruct23_GetSubstruct4
	add r1, sp, #0x0
	bl sub_0202A864
	add r0, sp, #0x0
	ldrb r1, [r0, #0x0]
	strh r1, [r4, #0x0]
	ldrb r0, [r0, #0x1]
	strh r0, [r6, #0x0]
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start ScrCmd_Unk01E4
ScrCmd_Unk01E4: ; 0x020428E0
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
	bl SaveStruct23_GetSubstruct4
	bl SaveStruct23_Substruct4_GetField_0xFF
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0204290C
sub_0204290C: ; 0x0204290C
	cmp r1, #0x2
	bne _02042918
	ldrb r0, [r0, #0x10]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1d
	bx lr
_02042918:
	cmp r1, #0x1
	bne _0204293E
	ldrb r1, [r0, #0xf]
	cmp r1, #0x2
	bne _02042930
	ldrb r0, [r0, #0x10]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1d
	lsl r1, r0, #0x1
	ldr r0, _0204294C ; =UNK_020F4334
	ldrh r0, [r0, r1]
	bx lr
_02042930:
	ldrb r0, [r0, #0x12]
	cmp r0, #0x0
	beq _0204293A
	mov r0, #0x61
	bx lr
_0204293A:
	mov r0, #0x0
	bx lr
_0204293E:
	ldrb r0, [r0, #0x11]
	cmp r0, #0x0
	beq _02042948
	mov r0, #0x61
	bx lr
_02042948:
	mov r0, #0x0
	bx lr
	.balign 4
_0204294C: .word UNK_020F4334

	thumb_func_start ScrCmd_Unk0294
ScrCmd_Unk0294: ; 0x02042950
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r1, [r5, #0x8]
	ldr r0, [r0, #0x0]
	add r2, r1, #0x1
	str r2, [r5, #0x8]
	ldrb r6, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	mov r1, #0x26
	bl FieldSysGetAttrAddr
	add r5, #0x80
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl ov05_021E2A70
	str r0, [r7, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_Unk0295
ScrCmd_Unk0295: ; 0x02042980
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x26
	bl FieldSysGetAttrAddr
	ldr r0, [r0, #0x0]
	bl ov05_021E29B4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0296
ScrCmd_Unk0296: ; 0x02042998
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x26
	bl FieldSysGetAttrAddr
	add r1, r0, #0x0
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	bl ov05_021E2AD4
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0297
ScrCmd_Unk0297: ; 0x020429B8
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
	bl Save_FrontierData_Get
	mov r1, #0x0
	add r2, r1, #0x0
	bl FrontierData_SetField_0x0
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Unk0298
ScrCmd_Unk0298: ; 0x020429E8
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
	bl VarGet
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl Save_FrontierData_Get
	add r1, r5, #0x0
	mov r2, #0x5
	bl FrontierData_SetField_0x0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk0299
ScrCmd_Unk0299: ; 0x02042A18
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
	bl VarGet
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl Save_FrontierData_Get
	add r1, r5, #0x0
	mov r2, #0x6
	bl FrontierData_SetField_0x0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk029A
ScrCmd_Unk029A: ; 0x02042A48
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r5, [r1, #0xc]
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
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl Save_FrontierData_Get
	mov r1, #0x0
	add r2, r1, #0x0
	bl FrontierData_SetField_0x0
	cmp r0, r6
	bhs _02042A8E
	mov r0, #0x0
	b _02042A90
_02042A8E:
	mov r0, #0x1
_02042A90:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_Unk029B
ScrCmd_Unk029B: ; 0x02042A98
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
	add r6, r0, #0x0
	add r0, r5, #0x0
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
	bl GetVarPointer
	cmp r7, #0x1
	bne _02042AEE
	mov r1, #0x1a
	b _02042AF0
_02042AEE:
	mov r1, #0x0
_02042AF0:
	add r1, r1, r6
	lsl r2, r1, #0x2
	ldr r1, _02042B04 ; =UNK_020F433E
	ldrh r1, [r1, r2]
	strh r1, [r4, #0x0]
	ldr r1, _02042B08 ; =UNK_020F4340
	ldrh r1, [r1, r2]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02042B04: .word UNK_020F433E
_02042B08: .word UNK_020F4340
