	.include "asm/macros.inc"
	.include "global.inc"

	.extern gSystem
	.extern Blackout_WindowTemplate

	.text

	thumb_func_start sub_02048164
sub_02048164: ; 0x02048164
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	mov r1, #0x24
	bl AllocFromHeap
	add r4, r0, #0x0
	bne _0204817A
	bl GF_AssertFail
_0204817A:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x24
	bl memset
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r5, [r4, #0x4]
	mov r0, #0xb
	bl BgConfig_Alloc
	str r0, [r4, #0x8]
	bl Blackout_InitDisplays
	mov r2, #0x52
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	mov r3, #0xb
	bl NewMsgDataFromNarc
	str r0, [r4, #0x1c]
	mov r0, #0xb
	bl MessageFormat_New
	str r0, [r4, #0x20]
	add r1, r4, #0x0
	ldr r0, [r4, #0x8]
	ldr r2, _02048208 ; =Blackout_WindowTemplate
	add r1, #0xc
	bl AddWindow
	add r0, r5, #0x0
	bl FieldSystem_GetSaveData
	bl Save_PlayerData_GetProfileAddr
	add r2, r0, #0x0
	ldr r0, [r4, #0x20]
	mov r1, #0x0
	bl BufferPlayersName
	ldr r0, [r5, #0x1c]
	ldr r1, [r0, #0x0]
	ldr r0, _0204820C ; =0x0000019E
	cmp r1, r0
	bne _020481E6
	mov r2, #0x0
	add r0, r4, #0x0
	mov r1, #0x4
	add r3, r2, #0x0
	bl sub_020482F4
	b _020481F2
_020481E6:
	mov r2, #0x0
	add r0, r4, #0x0
	mov r1, #0x3
	add r3, r2, #0x0
	bl sub_020482F4
_020481F2:
	add r0, r4, #0x0
	add r0, #0xc
	bl CopyWindowToVram
	ldr r1, _02048210 ; =sub_02048214
	add r0, r6, #0x0
	add r2, r4, #0x0
	bl TaskManager_Call
	pop {r4-r6, pc}
	nop
_02048208: .word Blackout_WindowTemplate
_0204820C: .word 0x0000019E
_02048210: .word sub_02048214

	thumb_func_start sub_02048214
sub_02048214: ; 0x02048214
	push {r3-r4, lr}
	sub sp, #0xc
	bl TaskManager_GetEnvironment
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x4
	bhi _020482EA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02048230: ; jump table (using 16-bit offset)
	.short _0204823A - _02048230 - 2; case 0
	.short _02048258 - _02048230 - 2; case 1
	.short _02048268 - _02048230 - 2; case 2
	.short _02048298 - _02048230 - 2; case 3
	.short _020482B2 - _02048230 - 2; case 4
_0204823A:
	mov r0, #0x8
	str r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r0, #0x20
	str r0, [sp, #0x8]
	mov r0, #0x3
	mov r2, #0x2a
	mov r3, #0x0
	bl BeginNormalPaletteFade
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020482EA
_02048258:
	bl IsPaletteFadeFinished
	cmp r0, #0x0
	beq _020482EA
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020482EA
_02048268:
	ldr r0, _020482F0 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	bne _02048278
	mov r0, #0x2
	tst r0, r1
	beq _020482EA
_02048278:
	mov r0, #0x8
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x20
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl BeginNormalPaletteFade
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020482EA
_02048298:
	bl IsPaletteFadeFinished
	cmp r0, #0x0
	beq _020482EA
	add r0, r4, #0x0
	add r0, #0xc
	mov r1, #0x0
	bl FillWindowPixelBuffer
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020482EA
_020482B2:
	add r0, r4, #0x0
	add r0, #0xc
	mov r1, #0x0
	bl ClearFrameAndWindow2
	add r0, r4, #0x0
	add r0, #0xc
	bl RemoveWindow
	ldr r0, [r4, #0x20]
	bl MessageFormat_Delete
	ldr r0, [r4, #0x1c]
	bl DestroyMsgData
	ldr r0, [r4, #0x8]
	mov r1, #0x3
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #0x8]
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0xc
	mov r0, #0x1
	pop {r3-r4, pc}
_020482EA:
	mov r0, #0x0
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4
_020482F0: .word gSystem

	thumb_func_start sub_020482F4
sub_020482F4: ; 0x020482F4
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	mov r0, #0x1
	str r1, [sp, #0x10]
	lsl r0, r0, #0xa
	mov r1, #0xb
	add r7, r3, #0x0
	bl String_New
	add r6, r0, #0x0
	mov r0, #0x1
	lsl r0, r0, #0xa
	mov r1, #0xb
	bl String_New
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0xc
	mov r1, #0x0
	bl FillWindowPixelBuffer
	ldr r0, [r5, #0x1c]
	ldr r1, [sp, #0x10]
	add r2, r6, #0x0
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0x20]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl StringExpandPlaceholders
	mov r0, #0x0
	add r1, r4, #0x0
	add r2, r0, #0x0
	bl sub_02002F08
	add r3, r0, #0x0
	str r7, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _02048378 ; =0x000F0200
	mov r1, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	str r1, [sp, #0xc]
	ldrb r5, [r5, #0x13]
	add r0, #0xc
	add r2, r4, #0x0
	lsl r5, r5, #0x3
	sub r3, r5, r3
	lsl r3, r3, #0x18
	lsr r3, r3, #0x19
	sub r3, r3, #0x4
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl AddTextPrinterParameterized2
	add r0, r6, #0x0
	bl String_Delete
	add r0, r4, #0x0
	bl String_Delete
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02048378: .word 0x000F0200

	thumb_func_start FieldTask_BlackOut
FieldTask_BlackOut: ; 0x0204837C
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl TaskManager_GetStatePtr
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x6
	bhi _02048488
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020483A2: ; jump table (using 16-bit offset)
	.short _020483B0 - _020483A2 - 2; case 0
	.short _020483E8 - _020483A2 - 2; case 1
	.short _020483F8 - _020483A2 - 2; case 2
	.short _0204840C - _020483A2 - 2; case 3
	.short _02048434 - _020483A2 - 2; case 4
	.short _02048442 - _020483A2 - 2; case 5
	.short _02048482 - _020483A2 - 2; case 6
_020483B0:
	ldr r0, [r6, #0xc]
	bl Save_LocalFieldData_Get
	add r7, r0, #0x0
	bl sub_02034DFC
	add r1, sp, #0x4
	str r0, [sp, #0x0]
	bl sub_02034EC4
	add r0, r7, #0x0
	bl LocalFieldData_GetSpecialSpawnWarpPtr
	add r1, r0, #0x0
	ldr r0, [sp, #0x0]
	bl sub_02034E90
	add r0, r5, #0x0
	add r1, sp, #0x4
	bl sub_02049160
	add r0, r6, #0x0
	bl sub_020637F0
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02048488
_020483E8:
	mov r0, #0x0
	mov r1, #0x14
	bl sub_020053CC
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02048488
_020483F8:
	bl sub_02005404
	cmp r0, #0x0
	bne _02048488
	bl sub_0204AB0C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02048488
_0204840C:
	mov r0, #0xf
	mvn r0, r0
	mov r1, #0x37
	mov r2, #0x1
	bl SetBlendBrightness
	mov r0, #0xf
	mvn r0, r0
	mov r1, #0x3f
	mov r2, #0x2
	bl SetBlendBrightness
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl sub_02048164
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02048488
_02048434:
	add r0, r5, #0x0
	bl CallTask_RestoreOverworld
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02048488
_02048442:
	mov r0, #0x0
	mov r1, #0x3f
	mov r2, #0x3
	bl SetBlendBrightness
	bl sub_02034E8C
	add r7, r0, #0x0
	ldr r0, [r6, #0xc]
	bl Save_LocalFieldData_Get
	bl sub_02034DFC
	cmp r7, r0
	bne _0204846E
	mov r2, #0x0
	ldr r1, _02048490 ; =0x000007E4
	add r0, r5, #0x0
	add r3, r2, #0x0
	bl QueueScript
	b _0204847A
_0204846E:
	mov r2, #0x0
	ldr r1, _02048494 ; =0x000007E5
	add r0, r5, #0x0
	add r3, r2, #0x0
	bl QueueScript
_0204847A:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02048488
_02048482:
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02048488:
	mov r0, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_02048490: .word 0x000007E4
_02048494: .word 0x000007E5

	thumb_func_start CallFieldTask_BlackOut
CallFieldTask_BlackOut: ; 0x02048498
	ldr r3, _020484A0 ; =TaskManager_Call
	ldr r1, _020484A4 ; =FieldTask_BlackOut
	mov r2, #0x0
	bx r3
	.balign 4
_020484A0: .word TaskManager_Call
_020484A4: .word FieldTask_BlackOut
