	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD11_0222F29C
MOD11_0222F29C: ; 0x0222F29C
	push {r4, r5, r6, lr}
	sub sp, #0x68
	add r4, r1, #0
	ldr r1, _0222F4C0 ; =0x00001028
	mov r2, #5
	bl OverlayManager_CreateAndGetData
	add r5, r0, #0
	ldr r0, _0222F4C4 ; =0x00001020
	str r4, [r5]
	mov r2, #0
	strb r2, [r5, r0]
	add r1, r0, #1
	strb r2, [r5, r1]
	add r0, r0, #2
	strh r2, [r5, r0]
	mov r0, #5
	bl FUN_02002FD0
	str r0, [r5, #0xc]
	mov r1, #1
	bl FUN_020038F0
	mov r2, #2
	ldr r0, [r5, #0xc]
	mov r1, #0
	lsl r2, r2, #8
	mov r3, #5
	bl PaletteData_AllocBuffers
	mov r1, #0
	mov r0, #1
	str r1, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	ldr r0, [r5, #0xc]
	mov r2, #2
	add r3, r1, #0
	bl PaletteData_FillPalette
	mov r0, #5
	bl BgConfig_Alloc
	str r0, [r5, #4]
	mov r0, #5
	mov r1, #1
	bl AllocWindows
	str r0, [r5, #8]
	add r0, r5, #0
	bl FUN_0206BFF0
	bl GX_DisableEngineALayers
	ldr r6, _0222F4C8 ; =MOD11_0225DA40
	add r3, sp, #0x40
	mov r2, #5
_0222F30E:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222F30E
	add r0, sp, #0x40
	bl GX_SetBanks
	mov r1, #6
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x18
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x62
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	mov r1, #0x19
	mov r2, #1
	mov r0, #0
	lsl r1, r1, #0x16
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x66
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	mov r1, #5
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x18
	lsl r2, r2, #8
	bl MIi_CpuClear16
	ldr r6, _0222F4CC ; =MOD11_0225D9B8
	add r3, sp, #0x30
	add r2, r3, #0
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl SetBothScreensModesAndDisable
	ldr r6, _0222F4D0 ; =MOD11_0225DA04
	add r3, sp, #0x14
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	mov r1, #1
	str r0, [r3]
	ldr r0, [r5, #4]
	mov r3, #0
	bl InitBgFromTemplate
	ldr r0, [r5, #4]
	mov r1, #1
	bl BgClearTilemapBufferAndCommit
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl Options_GetFrame
	add r4, r0, #0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	mov r1, #1
	ldr r0, [r5, #4]
	add r2, r1, #0
	mov r3, #0xa
	bl FUN_0200D274
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xb0
	str r0, [sp, #8]
	ldr r0, [r5, #0xc]
	mov r1, #0xe
	mov r2, #7
	mov r3, #5
	bl PaletteData_LoadNarc
	add r0, r4, #0
	bl FUN_0200CD64
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xa0
	str r0, [sp, #8]
	ldr r0, [r5, #0xc]
	mov r1, #0x26
	mov r3, #5
	bl PaletteData_LoadNarc
	mov r1, #0
	mov r0, #1
	str r1, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	ldr r0, [r5, #0xc]
	add r2, r1, #0
	add r3, r1, #0
	bl PaletteData_FillPalette
	bl GX_BothDispOn
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	mov r0, #0x1f
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	ldr r1, [r5, #8]
	mov r2, #1
	mov r3, #2
	bl AddWindowParameterized
	ldr r0, [r5, #8]
	mov r1, #0xff
	bl FillWindowPixelBuffer
	ldr r0, [r5, #8]
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl DrawFrameAndWindow2
	mov r2, #0x51
	mov r0, #1
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #5
	bl NewMsgDataFromNarc
	add r4, r0, #0
	mov r0, #1
	lsl r0, r0, #8
	mov r1, #5
	bl String_ctor
	add r6, r0, #0
	ldr r1, _0222F4D4 ; =0x0000039B
	add r0, r4, #0
	add r2, r6, #0
	bl ReadMsgDataIntoString
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r5, #8]
	mov r1, #1
	add r2, r6, #0
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	bl DestroyMsgData
	ldr r0, _0222F4D8 ; =MOD11_0222F0D4
	add r1, r5, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r5, #0xc]
	ldr r2, _0222F4DC ; =0x0000FFFF
	mov r1, #5
	bl FUN_02003210
	ldr r0, [r5, #8]
	mov r1, #1
	bl WaitingIcon_new
	ldr r1, _0222F4E0 ; =0x00001024
	str r0, [r5, r1]
	bl FUN_02033E74
	add sp, #0x68
	pop {r4, r5, r6, pc}
	nop
_0222F4C0: .word 0x00001028
_0222F4C4: .word 0x00001020
_0222F4C8: .word MOD11_0225DA40
_0222F4CC: .word MOD11_0225D9B8
_0222F4D0: .word MOD11_0225DA04
_0222F4D4: .word 0x0000039B
_0222F4D8: .word MOD11_0222F0D4
_0222F4DC: .word 0x0000FFFF
_0222F4E0: .word 0x00001024

	thumb_func_start MOD11_0222F4E4
MOD11_0222F4E4: ; 0x0222F4E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r1, [r4, #4]
	mov r0, #5
	bl FUN_020335F0
	ldr r0, _0222F804 ; =0x00001021
	mov r7, #0
	ldrb r1, [r4, r0]
	cmp r1, #0x21
	bls _0222F502
	b _0222F922
_0222F502:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222F50E: ; jump table
	.short _0222F552 - _0222F50E - 2 ; case 0
	.short _0222F562 - _0222F50E - 2 ; case 1
	.short _0222F576 - _0222F50E - 2 ; case 2
	.short _0222F586 - _0222F50E - 2 ; case 3
	.short _0222F5C0 - _0222F50E - 2 ; case 4
	.short _0222F898 - _0222F50E - 2 ; case 5
	.short _0222F5D8 - _0222F50E - 2 ; case 6
	.short _0222F5F2 - _0222F50E - 2 ; case 7
	.short _0222F898 - _0222F50E - 2 ; case 8
	.short _0222F606 - _0222F50E - 2 ; case 9
	.short _0222F622 - _0222F50E - 2 ; case 10
	.short _0222F898 - _0222F50E - 2 ; case 11
	.short _0222F636 - _0222F50E - 2 ; case 12
	.short _0222F650 - _0222F50E - 2 ; case 13
	.short _0222F898 - _0222F50E - 2 ; case 14
	.short _0222F664 - _0222F50E - 2 ; case 15
	.short _0222F67E - _0222F50E - 2 ; case 16
	.short _0222F898 - _0222F50E - 2 ; case 17
	.short _0222F692 - _0222F50E - 2 ; case 18
	.short _0222F6AC - _0222F50E - 2 ; case 19
	.short _0222F898 - _0222F50E - 2 ; case 20
	.short _0222F6C0 - _0222F50E - 2 ; case 21
	.short _0222F704 - _0222F50E - 2 ; case 22
	.short _0222F898 - _0222F50E - 2 ; case 23
	.short _0222F740 - _0222F50E - 2 ; case 24
	.short _0222F774 - _0222F50E - 2 ; case 25
	.short _0222F898 - _0222F50E - 2 ; case 26
	.short _0222F7AE - _0222F50E - 2 ; case 27
	.short _0222F7E2 - _0222F50E - 2 ; case 28
	.short _0222F898 - _0222F50E - 2 ; case 29
	.short _0222F82A - _0222F50E - 2 ; case 30
	.short _0222F85E - _0222F50E - 2 ; case 31
	.short _0222F898 - _0222F50E - 2 ; case 32
	.short _0222F908 - _0222F50E - 2 ; case 33
_0222F552:
	add r0, r7, #0
	bl SetMasterBrightnessNeutral
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F562:
	ldr r0, [r4, #0xc]
	bl FUN_020038E4
	cmp r0, #0
	bne _0222F610
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F576:
	mov r0, #0x32
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F586:
	mov r0, #0x32
	bl FUN_020315D8
	cmp r0, #0
	beq _0222F5A8
	mov r0, #0x33
	bl FUN_02031588
	ldr r0, _0222F808 ; =0x00001022
	add r1, r7, #0
	strh r1, [r4, r0]
	sub r1, r0, #1
	ldrb r1, [r4, r1]
	sub r0, r0, #1
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F5A8:
	ldr r0, _0222F808 ; =0x00001022
	ldrh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, r0]
	ldrh r1, [r4, r0]
	ldr r0, _0222F80C ; =0x00000708
	cmp r1, r0
	bls _0222F610
	mov r0, #1
	bl FUN_020336A0
	b _0222F922
_0222F5C0:
	mov r1, #0x11
	add r0, r4, #0
	lsl r1, r1, #4
	bl FUN_0206C1A0
	cmp r0, #1
	bne _0222F610
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F5D8:
	add r0, r4, #0
	bl FUN_0206C1FC
	cmp r0, #1
	bne _0222F610
	mov r0, #0x34
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F5F2:
	add r0, r4, #0
	bl FUN_0206C224
	cmp r0, #1
	bne _0222F610
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F606:
	add r0, r4, #0
	bl FUN_0206C268
	cmp r0, #1
	beq _0222F612
_0222F610:
	b _0222F922
_0222F612:
	mov r0, #0x35
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F622:
	add r0, r4, #0
	bl FUN_0206C294
	cmp r0, #1
	bne _0222F71C
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F636:
	add r0, r4, #0
	bl FUN_0206C2D4
	cmp r0, #1
	bne _0222F71C
	mov r0, #0x36
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F650:
	add r0, r4, #0
	bl FUN_0206C2F8
	cmp r0, #1
	bne _0222F71C
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F664:
	add r0, r4, #0
	bl FUN_0206C33C
	cmp r0, #1
	bne _0222F71C
	mov r0, #0x37
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F67E:
	add r0, r4, #0
	bl FUN_0206C364
	cmp r0, #1
	bne _0222F71C
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F692:
	add r0, r4, #0
	bl FUN_0206C398
	cmp r0, #1
	bne _0222F71C
	mov r0, #0x38
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F6AC:
	add r0, r4, #0
	bl FUN_0206C3F4
	cmp r0, #1
	bne _0222F71C
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F6C0:
	ldr r1, [r4]
	ldr r2, [r1]
	mov r1, #0x80
	tst r1, r2
	bne _0222F6D0
	mov r1, #0x21
	strb r1, [r4, r0]
	b _0222F922
_0222F6D0:
	bl FUN_02031190
	cmp r0, #0
	beq _0222F6E8
	mov r0, #0x39
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F6E8:
	add r0, r4, #0
	mov r1, #1
	bl FUN_0206C438
	cmp r0, #1
	bne _0222F71C
	mov r0, #0x39
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F704:
	mov r1, #1
	sub r0, r0, #1
	strb r1, [r4, r0]
	bl FUN_02031190
	cmp r0, #0
	beq _0222F728
	mov r0, #0x39
	bl FUN_020315D8
	cmp r0, #1
	beq _0222F71E
_0222F71C:
	b _0222F922
_0222F71E:
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F728:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x39
	bl FUN_0206C46C
	cmp r0, #1
	bne _0222F81E
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F740:
	bl FUN_02031190
	cmp r0, #0
	beq _0222F758
	mov r0, #0x3a
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F758:
	add r0, r4, #0
	mov r1, #3
	bl FUN_0206C438
	cmp r0, #1
	bne _0222F81E
	mov r0, #0x3a
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F774:
	mov r1, #1
	sub r0, r0, #1
	strb r1, [r4, r0]
	bl FUN_02031190
	cmp r0, #0
	beq _0222F796
	mov r0, #0x3a
	bl FUN_020315D8
	cmp r0, #1
	bne _0222F81E
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F796:
	add r0, r4, #0
	mov r1, #3
	mov r2, #0x3a
	bl FUN_0206C46C
	cmp r0, #1
	bne _0222F81E
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F7AE:
	bl FUN_02031190
	cmp r0, #0
	beq _0222F7C6
	mov r0, #0x3b
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F7C6:
	add r0, r4, #0
	mov r1, #1
	bl FUN_0206C4C4
	cmp r0, #1
	bne _0222F81E
	mov r0, #0x3b
	bl FUN_02031588
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F7E2:
	mov r1, #1
	sub r0, r0, #1
	strb r1, [r4, r0]
	bl FUN_02031190
	cmp r0, #0
	beq _0222F810
	mov r0, #0x3b
	bl FUN_020315D8
	cmp r0, #1
	bne _0222F81E
	ldr r0, _0222F804 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
	.align 2, 0
_0222F804: .word 0x00001021
_0222F808: .word 0x00001022
_0222F80C: .word 0x00000708
_0222F810:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x3b
	bl FUN_0206C4F0
	cmp r0, #1
	beq _0222F820
_0222F81E:
	b _0222F922
_0222F820:
	ldr r0, _0222F928 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F82A:
	bl FUN_02031190
	cmp r0, #0
	beq _0222F842
	mov r0, #0x3c
	bl FUN_02031588
	ldr r0, _0222F928 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F842:
	add r0, r4, #0
	mov r1, #3
	bl FUN_0206C4C4
	cmp r0, #1
	bne _0222F922
	mov r0, #0x3c
	bl FUN_02031588
	ldr r0, _0222F928 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F85E:
	mov r1, #1
	sub r0, r0, #1
	strb r1, [r4, r0]
	bl FUN_02031190
	cmp r0, #0
	beq _0222F880
	mov r0, #0x3c
	bl FUN_020315D8
	cmp r0, #1
	bne _0222F922
	ldr r0, _0222F928 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F880:
	add r0, r4, #0
	mov r1, #3
	mov r2, #0x3c
	bl FUN_0206C4F0
	cmp r0, #1
	bne _0222F922
	ldr r0, _0222F928 ; =0x00001021
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0222F922
_0222F898:
	bl FUN_02030F20
	ldr r1, _0222F92C ; =0x00001020
	ldrb r2, [r4, r1]
	cmp r2, r0
	bne _0222F8EE
	add r0, r1, #1
	ldrb r0, [r4, r0]
	cmp r0, #0x14
	bne _0222F8BE
	add r6, r7, #0
	add r5, r4, #0
_0222F8B0:
	ldr r0, [r5, #0x10]
	bl FreeToHeap
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _0222F8B0
_0222F8BE:
	ldr r0, _0222F92C ; =0x00001020
	mov r3, #0
	strb r3, [r4, r0]
	add r1, r0, #2
	strh r3, [r4, r1]
	add r1, r0, #1
	ldrb r1, [r4, r1]
	add r2, r1, #1
	add r1, r0, #1
	strb r2, [r4, r1]
	add r0, r0, #1
	ldrb r0, [r4, r0]
	cmp r0, #0x21
	bne _0222F922
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r4, #0xc]
	ldr r2, _0222F930 ; =0x0000FFFF
	mov r1, #5
	bl FUN_02003210
	b _0222F922
_0222F8EE:
	add r0, r1, #2
	ldrh r0, [r4, r0]
	add r2, r0, #1
	add r0, r1, #2
	strh r2, [r4, r0]
	ldrh r1, [r4, r0]
	ldr r0, _0222F934 ; =0x00000708
	cmp r1, r0
	bls _0222F922
	mov r0, #1
	bl FUN_020336A0
	b _0222F922
_0222F908:
	ldr r0, [r4, #0xc]
	bl FUN_020038E4
	cmp r0, #0
	bne _0222F922
	ldr r0, _0222F938 ; =0x00001024
	mov r7, #1
	ldr r0, [r4, r0]
	bl FUN_0200DBFC
	mov r0, #0
	bl FUN_02031400
_0222F922:
	add r0, r7, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222F928: .word 0x00001021
_0222F92C: .word 0x00001020
_0222F930: .word 0x0000FFFF
_0222F934: .word 0x00000708
_0222F938: .word 0x00001024

	thumb_func_start MOD11_0222F93C
MOD11_0222F93C: ; 0x0222F93C
	push {r4, lr}
	bl OverlayManager_GetData
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl PaletteData_FreeBuffers
	ldr r0, [r4, #0xc]
	bl FUN_02002FEC
	ldr r0, [r4, #8]
	mov r1, #1
	bl WindowArray_dtor
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4, #4]
	mov r1, #1
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #4]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD11_0222F988
MOD11_0222F988: ; 0x0222F988
	push {r4, r5, r6, lr}
	ldr r1, _0222FAB4 ; =0x00002444
	add r5, r0, #0
	mov r2, #5
	bl OverlayManager_CreateAndGetData
	add r4, r0, #0
	add r0, r5, #0
	bl OverlayManager_GetField18
	add r6, r0, #0
	bl FUN_02031190
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r2, _0222FAB4 ; =0x00002444
	mov r0, #0
	add r1, r4, #0
	bl MIi_CpuClearFast
	add r0, r4, #0
	add r1, r6, #0
	bl MOD11_0222E520
	ldr r1, [r4, #0x2c]
	mov r0, #4
	tst r0, r1
	beq _0222F9C6
	mov r0, #0x80
	tst r0, r1
	beq _0222F9CA
_0222F9C6:
	mov r0, #0
	pop {r4, r5, r6, pc}
_0222F9CA:
	ldr r0, _0222FAB8 ; =SDK_OVERLAY_MODULE_07_ID
	mov r1, #2
	bl HandleLoadOverlay
	ldr r1, [r4, #0x2c]
	mov r0, #8
	tst r0, r1
	bne _0222F9DE
	mov r0, #0
	pop {r4, r5, r6, pc}
_0222F9DE:
	mov r0, #5
	mov r1, #0x2c
	bl AllocFromHeap
	mov r1, #7
	lsl r1, r1, #6
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	mov r0, #0
	mov r2, #0x2c
	bl MIi_CpuClearFast
	add r0, r5, #0
	bl FUN_020313CC
	cmp r0, #3
	bhi _0222FA5A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222FA0C: ; jump table
	.short _0222FA14 - _0222FA0C - 2 ; case 0
	.short _0222FA3A - _0222FA0C - 2 ; case 1
	.short _0222FA3A - _0222FA0C - 2 ; case 2
	.short _0222FA14 - _0222FA0C - 2 ; case 3
_0222FA14:
	lsl r0, r5, #2
	add r0, r4, r0
	ldr r1, [r0, #0x68]
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	str r1, [r0, #4]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD11_022302BC
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r1, [r0, #0x68]
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	str r1, [r0, #0xc]
	b _0222FA5A
_0222FA3A:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD11_022302BC
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r2, [r0, #0x68]
	mov r0, #7
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	str r2, [r1, #4]
	lsl r1, r5, #2
	add r1, r4, r1
	ldr r1, [r1, #0x68]
	ldr r0, [r4, r0]
	str r1, [r0, #0xc]
_0222FA5A:
	mov r0, #7
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r2, #5
	str r2, [r1, #0x24]
	ldr r0, [r4, r0]
	mov r1, #0
	add r0, #0x28
	strb r1, [r0]
	add r0, r5, #0
	bl FUN_020313CC
	cmp r0, #3
	bhi _0222FAA4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222FA82: ; jump table
	.short _0222FA8A - _0222FA82 - 2 ; case 0
	.short _0222FA98 - _0222FA82 - 2 ; case 1
	.short _0222FA98 - _0222FA82 - 2 ; case 2
	.short _0222FA8A - _0222FA82 - 2 ; case 3
_0222FA8A:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #0
	add r0, #0x29
	strb r1, [r0]
	b _0222FAA4
_0222FA98:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #1
	add r0, #0x29
	strb r1, [r0]
_0222FAA4:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl MOD07_02211E60
	mov r0, #1
	pop {r4, r5, r6, pc}
	nop
_0222FAB4: .word 0x00002444
_0222FAB8: .word SDK_OVERLAY_MODULE_07_ID

	thumb_func_start MOD11_0222FABC
MOD11_0222FABC: ; 0x0222FABC
	push {r3, r4, r5, r6, r7, lr}
	bl OverlayManager_GetData
	add r6, r0, #0
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r6, r0]
	add r0, #0x2b
	ldrb r0, [r0]
	cmp r0, #0
	beq _0222FAFE
	mov r4, #0
	mov r7, #7
	add r5, r4, #0
	lsl r7, r7, #6
_0222FADA:
	ldr r0, [r6, r7]
	add r0, r0, r5
	ldr r0, [r0, #0x14]
	cmp r0, #0
	beq _0222FAE8
	bl FreeToHeap
_0222FAE8:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0222FADA
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r6, r0]
	bl FreeToHeap
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0222FAFE:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_0222FB04
MOD11_0222FB04: ; 0x0222FB04
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, r5, #0
	bl OverlayManager_GetField18
	bl FUN_02031190
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r1, [r4, #0x2c]
	mov r0, #4
	tst r0, r1
	beq _0222FB2A
	mov r0, #0x80
	tst r0, r1
	beq _0222FB2E
_0222FB2A:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0222FB2E:
	mov r0, #5
	mov r1, #0x2c
	bl AllocFromHeap
	mov r1, #7
	lsl r1, r1, #6
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	mov r0, #0
	mov r2, #0x2c
	bl MIi_CpuClearFast
	ldr r1, [r4, #0x2c]
	mov r0, #8
	tst r0, r1
	beq _0222FBA4
	mov r6, #0
	add r5, r4, #0
_0222FB52:
	add r0, r6, #0
	bl FUN_020313CC
	mov r2, #7
	lsl r2, r2, #6
	ldr r2, [r4, r2]
	lsl r0, r0, #2
	ldr r1, [r5, #0x68]
	add r0, r2, r0
	str r1, [r0, #4]
	add r0, r6, #0
	bl FUN_020313CC
	add r7, r0, #0
	ldr r0, [r5, #0x48]
	mov r1, #5
	bl PlayerProfile_GetPlayerName_NewString
	mov r1, #7
	lsl r1, r1, #6
	ldr r2, [r4, r1]
	lsl r1, r7, #2
	add r1, r2, r1
	add r6, r6, #1
	add r5, r5, #4
	str r0, [r1, #0x14]
	cmp r6, #4
	blt _0222FB52
	mov r0, #7
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r2, #5
	str r2, [r1, #0x24]
	ldr r1, [r4, r0]
	mov r2, #1
	add r1, #0x28
	strb r2, [r1]
	ldr r0, [r4, r0]
	add r0, #0x29
	strb r2, [r0]
	b _0222FC2A
_0222FBA4:
	add r0, r7, #0
	lsl r6, r7, #2
	bl FUN_020313CC
	mov r2, #7
	lsl r2, r2, #6
	add r1, r4, r6
	ldr r2, [r4, r2]
	lsl r0, r0, #2
	ldr r1, [r1, #0x68]
	add r0, r2, r0
	str r1, [r0, #4]
	mov r0, #1
	eor r0, r7
	lsl r5, r0, #2
	str r0, [sp]
	bl FUN_020313CC
	add r1, r4, r5
	ldr r2, [r1, #0x68]
	mov r1, #7
	lsl r1, r1, #6
	ldr r1, [r4, r1]
	lsl r0, r0, #2
	add r0, r1, r0
	str r2, [r0, #4]
	add r0, r7, #0
	bl FUN_020313CC
	add r7, r0, #0
	add r0, r4, r6
	ldr r0, [r0, #0x48]
	mov r1, #5
	bl PlayerProfile_GetPlayerName_NewString
	mov r1, #7
	lsl r1, r1, #6
	ldr r2, [r4, r1]
	lsl r1, r7, #2
	add r1, r2, r1
	str r0, [r1, #0x14]
	ldr r0, [sp]
	bl FUN_020313CC
	add r6, r0, #0
	add r0, r4, r5
	ldr r0, [r0, #0x48]
	mov r1, #5
	bl PlayerProfile_GetPlayerName_NewString
	mov r1, #7
	lsl r1, r1, #6
	ldr r3, [r4, r1]
	lsl r2, r6, #2
	add r2, r3, r2
	str r0, [r2, #0x14]
	ldr r0, [r4, r1]
	mov r2, #5
	str r2, [r0, #0x24]
	ldr r0, [r4, r1]
	mov r2, #1
	add r0, #0x28
	strb r2, [r0]
	ldr r0, [r4, r1]
	mov r2, #0
	add r0, #0x29
	strb r2, [r0]
_0222FC2A:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl MOD07_02211E60
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_0222FC38
MOD11_0222FC38: ; 0x0222FC38
	push {r3, r4, r5, r6, r7, lr}
	bl OverlayManager_GetData
	add r6, r0, #0
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r6, r0]
	add r0, #0x2b
	ldrb r0, [r0]
	cmp r0, #0
	beq _0222FC7A
	mov r4, #0
	mov r7, #7
	add r5, r4, #0
	lsl r7, r7, #6
_0222FC56:
	ldr r0, [r6, r7]
	add r0, r0, r5
	ldr r0, [r0, #0x14]
	cmp r0, #0
	beq _0222FC64
	bl FreeToHeap
_0222FC64:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0222FC56
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r6, r0]
	bl FreeToHeap
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0222FC7A:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_0222FC80
MOD11_0222FC80: ; 0x0222FC80
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	bl OverlayManager_GetField18
	add r7, r0, #0
	bl FUN_02031190
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r1, [r7]
	mov r0, #4
	tst r0, r1
	beq _0222FCA2
	mov r0, #0x80
	tst r0, r1
	beq _0222FCA8
_0222FCA2:
	add sp, #0x10
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0222FCA8:
	ldr r0, _0222FE54 ; =SDK_OVERLAY_MODULE_07_ID
	mov r1, #2
	bl HandleLoadOverlay
	mov r0, #5
	mov r1, #0x2c
	bl AllocFromHeap
	add r6, r0, #0
	mov r0, #0x66
	lsl r0, r0, #2
	str r6, [r7, r0]
	mov r0, #0
	add r1, r6, #0
	mov r2, #0x2c
	bl MIi_CpuClearFast
	str r7, [r6]
	ldr r0, [r7, #0x14]
	cmp r0, #5
	bhi _0222FD54
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222FCDE: ; jump table
	.short _0222FD54 - _0222FCDE - 2 ; case 0
	.short _0222FCEA - _0222FCDE - 2 ; case 1
	.short _0222FD0E - _0222FCDE - 2 ; case 2
	.short _0222FD32 - _0222FCDE - 2 ; case 3
	.short _0222FD54 - _0222FCDE - 2 ; case 4
	.short _0222FD32 - _0222FCDE - 2 ; case 5
_0222FCEA:
	bl FUN_02033590
	cmp r0, #0
	bne _0222FD00
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r1, #0x15
	bl GameStats_Inc
	b _0222FD54
_0222FD00:
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r1, #0x1a
	bl GameStats_Inc
	b _0222FD54
_0222FD0E:
	bl FUN_02033590
	cmp r0, #0
	bne _0222FD24
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r1, #0x16
	bl GameStats_Inc
	b _0222FD54
_0222FD24:
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r1, #0x1b
	bl GameStats_Inc
	b _0222FD54
_0222FD32:
	bl FUN_02033590
	cmp r0, #0
	bne _0222FD48
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r1, #0x17
	bl GameStats_Inc
	b _0222FD54
_0222FD48:
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r1, #0x1c
	bl GameStats_Inc
_0222FD54:
	ldr r1, [r7]
	mov r0, #8
	tst r0, r1
	beq _0222FDBE
	mov r4, #0
	add r5, r7, #0
_0222FD60:
	add r0, r4, #0
	bl FUN_020313CC
	lsl r0, r0, #2
	ldr r1, [r5, #4]
	add r0, r6, r0
	str r1, [r0, #4]
	add r0, r4, #0
	bl FUN_020313CC
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	mov r1, #5
	bl PlayerProfile_GetPlayerName_NewString
	ldr r1, [sp, #8]
	add r4, r4, #1
	lsl r1, r1, #2
	add r1, r6, r1
	add r5, r5, #4
	str r0, [r1, #0x14]
	cmp r4, #4
	blt _0222FD60
	mov r0, #5
	str r0, [r6, #0x24]
	add r0, r6, #0
	mov r1, #2
	add r0, #0x28
	strb r1, [r0]
	add r0, r6, #0
	mov r1, #1
	add r0, #0x29
	strb r1, [r0]
	ldr r1, [r7, #0x14]
	cmp r1, #5
	beq _0222FDB4
	add r0, r6, #0
	add r0, #0x2a
	strb r1, [r0]
	b _0222FE48
_0222FDB4:
	add r0, r6, #0
	mov r1, #3
	add r0, #0x2a
	strb r1, [r0]
	b _0222FE48
_0222FDBE:
	ldr r0, [sp, #4]
	lsl r5, r0, #2
	bl FUN_020313CC
	add r1, r7, r5
	lsl r0, r0, #2
	ldr r1, [r1, #4]
	add r0, r6, r0
	str r1, [r0, #4]
	ldr r0, [sp, #4]
	mov r1, #1
	eor r0, r1
	lsl r4, r0, #2
	str r0, [sp]
	bl FUN_020313CC
	add r1, r7, r4
	lsl r0, r0, #2
	ldr r1, [r1, #4]
	add r0, r6, r0
	str r1, [r0, #4]
	ldr r0, [sp, #4]
	bl FUN_020313CC
	str r0, [sp, #0xc]
	add r0, r7, r5
	add r0, #0xf8
	ldr r0, [r0]
	mov r1, #5
	bl PlayerProfile_GetPlayerName_NewString
	ldr r1, [sp, #0xc]
	lsl r1, r1, #2
	add r1, r6, r1
	str r0, [r1, #0x14]
	ldr r0, [sp]
	bl FUN_020313CC
	add r5, r0, #0
	add r0, r7, r4
	add r0, #0xf8
	ldr r0, [r0]
	mov r1, #5
	bl PlayerProfile_GetPlayerName_NewString
	lsl r1, r5, #2
	add r1, r6, r1
	str r0, [r1, #0x14]
	mov r0, #5
	str r0, [r6, #0x24]
	add r0, r6, #0
	mov r1, #2
	add r0, #0x28
	strb r1, [r0]
	add r0, r6, #0
	mov r1, #0
	add r0, #0x29
	strb r1, [r0]
	ldr r1, [r7, #0x14]
	cmp r1, #5
	beq _0222FE40
	add r0, r6, #0
	add r0, #0x2a
	strb r1, [r0]
	b _0222FE48
_0222FE40:
	add r0, r6, #0
	mov r1, #3
	add r0, #0x2a
	strb r1, [r0]
_0222FE48:
	add r0, r6, #0
	bl MOD07_02211E60
	mov r0, #1
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222FE54: .word SDK_OVERLAY_MODULE_07_ID

	thumb_func_start MOD11_0222FE58
MOD11_0222FE58: ; 0x0222FE58
	push {r4, r5, r6, lr}
	bl OverlayManager_GetField18
	mov r1, #0x66
	lsl r1, r1, #2
	ldr r6, [r0, r1]
	add r0, r6, #0
	add r0, #0x2b
	ldrb r0, [r0]
	cmp r0, #0
	beq _0222FE8E
	mov r4, #0
	add r5, r6, #0
_0222FE72:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _0222FE7C
	bl FreeToHeap
_0222FE7C:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0222FE72
	add r0, r6, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, r5, r6, pc}
_0222FE8E:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD11_0222FE94
MOD11_0222FE94: ; 0x0222FE94
	push {r3, lr}
	ldr r1, [r0, #0x2c]
	ldr r0, _0222FEBC ; =0x00000404
	tst r0, r1
	beq _0222FEA6
	mov r0, #1
	bl FUN_02002B7C
	pop {r3, pc}
_0222FEA6:
	mov r0, #3
	bl FUN_02002B7C
	mov r0, #1
	bl TextFlags_SetCanABSpeedUpPrint
	mov r0, #1
	bl FUN_02002BB8
	pop {r3, pc}
	nop
_0222FEBC: .word 0x00000404

	thumb_func_start MOD11_0222FEC0
MOD11_0222FEC0: ; 0x0222FEC0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	str r0, [sp]
	mov r0, #0x5f
	mov r3, #0
	add r4, sp, #0x30
	add r5, sp, #0x20
	lsl r0, r0, #2
_0222FED0:
	stmia r4!, {r3}
	ldr r2, [r1, r0]
	add r3, r3, #1
	add r1, r1, #4
	stmia r5!, {r2}
	cmp r3, #4
	blt _0222FED0
	bl FUN_02031190
	str r0, [sp, #0x10]
	bl FUN_02030F20
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	sub r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, #0
	ble _0222FF50
	add r0, sp, #0x30
	add r3, sp, #0x20
	str r0, [sp, #8]
	str r3, [sp, #0x18]
	mov ip, r0
_0222FF02:
	ldr r0, [sp, #4]
	add r2, r0, #1
	ldr r0, [sp, #0xc]
	cmp r2, r0
	bge _0222FF3C
	ldr r0, [sp, #0x18]
	lsl r1, r2, #2
	add r4, r0, r1
	mov r0, ip
	add r5, r0, r1
_0222FF16:
	ldr r0, [r4]
	ldr r6, [r3]
	str r0, [sp, #0x1c]
	cmp r6, r0
	bge _0222FF30
	ldr r0, [sp, #8]
	ldr r1, [r5]
	ldr r7, [r0]
	str r1, [r0]
	ldr r0, [sp, #0x1c]
	str r7, [r5]
	str r0, [r3]
	str r6, [r4]
_0222FF30:
	ldr r0, [sp, #0xc]
	add r2, r2, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r2, r0
	blt _0222FF16
_0222FF3C:
	ldr r0, [sp, #8]
	add r3, r3, #4
	add r0, r0, #4
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [sp, #4]
	cmp r1, r0
	blt _0222FF02
_0222FF50:
	ldr r1, [sp, #0x30]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bne _0222FF60
	ldr r1, _0222FF64 ; =0x000023F8
	ldr r0, [sp]
	mov r2, #1
	strb r2, [r0, r1]
_0222FF60:
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222FF64: .word 0x000023F8
