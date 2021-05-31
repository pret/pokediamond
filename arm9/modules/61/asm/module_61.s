	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD61_021D74E0
MOD61_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	mov r2, #2
	mov r0, #3
	mov r1, #0x29
	lsl r2, r2, #0x10
	bl CreateHeap
	add r0, r5, #0
	mov r1, #0xbc
	mov r2, #0x29
	bl OverlayManager_CreateAndGetData
	mov r1, #0
	mov r2, #0xbc
	add r4, r0, #0
	bl memset
	mov r0, #0x29
	str r0, [r4]
	add r0, r5, #0
	bl OverlayManager_GetField18
	str r0, [r4, #0x1c]
	ldrh r0, [r0]
	ldr r1, _021D754C ; =0x0000FFFF
	strb r0, [r4, #0xc]
	ldrb r0, [r4, #0xc]
	strb r0, [r4, #0xd]
	ldr r0, [r4, #0x1c]
	ldrb r0, [r0, #2]
	strb r0, [r4, #0x11]
	ldr r0, [r4, #0x1c]
	ldrb r0, [r0, #3]
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x11]
	strb r0, [r4, #0x16]
	strb r0, [r4, #0x17]
	ldr r0, [r4, #0x1c]
	strh r1, [r0]
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #4]
	bl Options_GetTextFrameDelay
	strb r0, [r4, #0x10]
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #4]
	bl Options_GetFrame
	strh r0, [r4, #0xa]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D754C: .word 0x0000FFFF
	thumb_func_end MOD61_021D74E0

	thumb_func_start MOD61_021D7550
MOD61_021D7550: ; 0x021D7550
	push {r3, lr}
	bl OverlayManager_GetData
	bl MOD61_021D78D4
	cmp r0, #0
	beq _021D7562
	mov r0, #1
	pop {r3, pc}
_021D7562:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD61_021D7550

	thumb_func_start MOD61_021D7568
MOD61_021D7568: ; 0x021D7568
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	ldr r4, [r0]
	add r0, r5, #0
	bl OverlayManager_FreeData
	add r0, r4, #0
	bl DestroyHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD61_021D7568

	thumb_func_start MOD61_021D7584
MOD61_021D7584: ; 0x021D7584
	push {r4, r5, r6, lr}
	mov r4, #0
	add r6, r0, #0
	add r5, r4, #0
_021D758C:
	ldr r0, [r6, #0x1c]
	add r0, #0x1a
	add r0, r0, r5
	bl MailMsg_IsInit
	cmp r0, #0
	beq _021D759E
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D759E:
	add r4, r4, #1
	add r5, #8
	cmp r4, #3
	blt _021D758C
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD61_021D7584

	thumb_func_start MOD61_021D75AC
MOD61_021D75AC: ; 0x021D75AC
	push {r3, lr}
	ldr r0, _021D75C8 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D75C2
	ldr r0, _021D75CC ; =0x000005E3
	bl FUN_020054C8
	mov r0, #1
	pop {r3, pc}
_021D75C2:
	mov r0, #0
	pop {r3, pc}
	nop
_021D75C8: .word gMain
_021D75CC: .word 0x000005E3
	thumb_func_end MOD61_021D75AC

	thumb_func_start MOD61_021D75D0
MOD61_021D75D0: ; 0x021D75D0
	push {r3, r4, r5, lr}
	ldr r1, _021D76E0 ; =gMain
	add r4, r0, #0
	ldr r2, [r1, #0x48]
	mov r1, #1
	add r5, r2, #0
	mov r3, #0
	tst r5, r1
	beq _021D7648
	ldrb r1, [r4, #0x11]
	cmp r1, #3
	bne _021D762E
	ldrb r1, [r4, #0x12]
	cmp r1, #0
	bne _021D7612
	bl MOD61_021D7584
	cmp r0, #0
	beq _021D7604
	ldr r0, _021D76E4 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #2
	strb r0, [r4, #0xc]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D7604:
	ldr r0, [r4, #0x1c]
	mov r1, #3
	strh r1, [r0]
	ldr r0, _021D76E8 ; =0x000005E3
	bl FUN_020054C8
	b _021D7620
_021D7612:
	ldr r0, _021D76E4 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #3
	strb r0, [r4, #0xc]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D7620:
	ldr r0, [r4, #0x1c]
	mov r1, #0
	strb r1, [r0, #3]
	ldr r1, [r4, #0x1c]
	ldrb r0, [r1, #3]
	strb r0, [r1, #2]
	b _021D7644
_021D762E:
	ldr r0, [r4, #0x1c]
	strb r1, [r0, #2]
	ldr r1, [r4, #0x1c]
	ldrb r0, [r1, #2]
	strh r0, [r1]
	ldrb r1, [r4, #0x12]
	ldr r0, [r4, #0x1c]
	strb r1, [r0, #3]
	ldr r0, _021D76E4 ; =0x000005DD
	bl FUN_020054C8
_021D7644:
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D7648:
	mov r0, #2
	tst r0, r2
	beq _021D765C
	ldr r0, _021D76E4 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #3
	strb r0, [r4, #0xc]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D765C:
	mov r0, #8
	tst r0, r2
	beq _021D766C
	mov r0, #3
	strb r0, [r4, #0x11]
	strb r3, [r4, #0x12]
	add r3, r1, #0
	b _021D76BE
_021D766C:
	mov r0, #0x80
	tst r0, r2
	beq _021D7688
	ldrb r0, [r4, #0x11]
	add r0, r0, #1
	lsr r3, r0, #0x1f
	lsl r2, r0, #0x1e
	sub r2, r2, r3
	mov r0, #0x1e
	ror r2, r0
	add r0, r3, r2
	strb r0, [r4, #0x11]
	add r3, r1, #0
	b _021D76BE
_021D7688:
	mov r0, #0x40
	tst r0, r2
	beq _021D76A4
	ldrb r0, [r4, #0x11]
	add r0, r0, #3
	lsr r3, r0, #0x1f
	lsl r2, r0, #0x1e
	sub r2, r2, r3
	mov r0, #0x1e
	ror r2, r0
	add r0, r3, r2
	strb r0, [r4, #0x11]
	add r3, r1, #0
	b _021D76BE
_021D76A4:
	mov r0, #0x30
	tst r0, r2
	beq _021D76BA
	ldrb r0, [r4, #0x11]
	cmp r0, #3
	bne _021D76BE
	ldrb r0, [r4, #0x12]
	add r3, r1, #0
	eor r0, r1
	strb r0, [r4, #0x12]
	b _021D76BE
_021D76BA:
	add r0, r3, #0
	pop {r3, r4, r5, pc}
_021D76BE:
	cmp r3, #0
	bne _021D76C6
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D76C6:
	ldr r0, _021D76EC ; =0x000005DC
	bl FUN_020054C8
	ldrb r1, [r4, #0x11]
	cmp r1, #3
	bne _021D76DA
	ldrb r0, [r4, #0x12]
	add r0, r1, r0
	strb r0, [r4, #0x16]
	b _021D76DC
_021D76DA:
	strb r1, [r4, #0x16]
_021D76DC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D76E0: .word gMain
_021D76E4: .word 0x000005DD
_021D76E8: .word 0x000005E3
_021D76EC: .word 0x000005DC
	thumb_func_end MOD61_021D75D0

	thumb_func_start MOD61_021D76F0
MOD61_021D76F0: ; 0x021D76F0
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldrh r0, [r5, #8]
	cmp r0, #0
	beq _021D7702
	cmp r0, #1
	beq _021D774E
	b _021D777C
_021D7702:
	add r0, r5, #0
	add r0, #0x94
	mov r1, #1
	mov r2, #0xa
	mov r3, #6
	bl FUN_0200D0BC
	add r0, r5, #0
	add r0, #0x94
	mov r1, #0xff
	bl FillWindowPixelBuffer
	ldr r1, [r5]
	mov r0, #0x4c
	bl String_ctor
	add r4, r0, #0
	ldr r0, [r5, #0x20]
	mov r1, #2
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r3, #0
	str r3, [sp]
	ldr r0, _021D7788 ; =0x0001020F
	str r3, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0x94
	mov r1, #1
	add r2, r4, #0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	b _021D777C
_021D774E:
	ldr r0, _021D778C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _021D775E
	add sp, #0x10
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D775E:
	add r0, r5, #0
	add r0, #0x94
	mov r1, #1
	bl FUN_0200D0E0
	add r0, r5, #0
	add r0, #0x94
	bl FUN_02019570
	mov r0, #0
	strh r0, [r5, #8]
	ldrb r1, [r5, #0xd]
	add sp, #0x10
	strb r1, [r5, #0xc]
	pop {r3, r4, r5, pc}
_021D777C:
	ldrh r0, [r5, #8]
	add r0, r0, #1
	strh r0, [r5, #8]
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7788: .word 0x0001020F
_021D778C: .word gMain
	thumb_func_end MOD61_021D76F0

	thumb_func_start MOD61_021D7790
MOD61_021D7790: ; 0x021D7790
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4]
	ldr r1, _021D77B0 ; =0x021D842C
	str r0, [sp]
	ldr r0, [r4, #0x18]
	mov r2, #1
	mov r3, #5
	bl Std_CreateYesNoMenu
	add r4, #0xa4
	str r0, [r4]
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D77B0: .word MOD61_021D842C
	thumb_func_end MOD61_021D7790

	thumb_func_start MOD61_021D77B4
MOD61_021D77B4: ; 0x021D77B4
	push {r3, lr}
	add r1, r0, #0
	add r0, #0xa4
	ldr r0, [r0]
	ldr r1, [r1]
	bl FUN_020021AC
	cmp r0, #0
	beq _021D77D0
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _021D77D4
	b _021D77D8
_021D77D0:
	mov r0, #1
	pop {r3, pc}
_021D77D4:
	mov r0, #0
	pop {r3, pc}
_021D77D8:
	add r0, r1, #1
	pop {r3, pc}
	thumb_func_end MOD61_021D77B4

	thumb_func_start MOD61_021D77DC
MOD61_021D77DC: ; 0x021D77DC
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldrh r1, [r5, #8]
	cmp r1, #0
	beq _021D77F2
	cmp r1, #1
	beq _021D7864
	cmp r1, #2
	beq _021D787C
	b _021D78BA
_021D77F2:
	mov r1, #1
	add r0, #0x94
	mov r2, #0xa
	mov r3, #6
	strb r1, [r5, #0x13]
	bl FUN_0200D0BC
	add r0, r5, #0
	add r0, #0x94
	mov r1, #0xff
	bl FillWindowPixelBuffer
	ldr r1, [r5]
	mov r0, #0x4c
	bl String_ctor
	add r4, r0, #0
	ldr r0, [r5, #0x20]
	mov r1, #3
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r3, #0
	str r3, [sp]
	ldrb r0, [r5, #0x10]
	mov r1, #1
	add r2, r4, #0
	str r0, [sp, #4]
	ldr r0, _021D78C8 ; =0x0001020F
	str r0, [sp, #8]
	add r0, r5, #0
	str r3, [sp, #0xc]
	add r0, #0x94
	bl AddTextPrinterParameterized2
	strb r0, [r5, #0xf]
	add r0, r4, #0
	bl String_dtor
	mov r1, #0
	ldr r0, _021D78CC ; =0x00007FFF
	str r1, [sp]
	str r0, [sp, #4]
	ldrb r2, [r5, #0x17]
	ldr r0, [r5, #0x30]
	mov r3, #1
	add r2, #0x22
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	bl FUN_020039E8
	ldrb r0, [r5, #0x16]
	strb r0, [r5, #0x17]
	mov r0, #0
	strb r0, [r5, #0x15]
	strb r0, [r5, #0x14]
	b _021D78BA
_021D7864:
	ldrb r0, [r5, #0xf]
	bl FUN_0201BD70
	cmp r0, #0
	beq _021D7874
	add sp, #0x10
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D7874:
	add r0, r5, #0
	bl MOD61_021D7790
	b _021D78BA
_021D787C:
	bl MOD61_021D77B4
	add r4, r0, #0
	bpl _021D788A
	add sp, #0x10
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D788A:
	add r0, r5, #0
	add r0, #0x94
	mov r1, #1
	bl FUN_0200D0E0
	add r0, r5, #0
	add r0, #0x94
	bl FUN_02019570
	mov r0, #0
	strh r0, [r5, #8]
	cmp r4, #0
	beq _021D78B0
	ldr r1, _021D78D0 ; =0x0000FFFF
	ldr r0, [r5, #0x1c]
	add sp, #0x10
	strh r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D78B0:
	ldrb r1, [r5, #0xd]
	add sp, #0x10
	strb r1, [r5, #0xc]
	strb r0, [r5, #0x13]
	pop {r3, r4, r5, pc}
_021D78BA:
	ldrh r0, [r5, #8]
	add r0, r0, #1
	strh r0, [r5, #8]
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D78C8: .word 0x0001020F
_021D78CC: .word 0x00007FFF
_021D78D0: .word 0x0000FFFF
	thumb_func_end MOD61_021D77DC

	thumb_func_start MOD61_021D78D4
MOD61_021D78D4: ; 0x021D78D4
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #5
	bls _021D78E2
	b _021D7A46
_021D78E2:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D78EE: ; jump table
	.short _021D78FA - _021D78EE - 2 ; case 0
	.short _021D7940 - _021D78EE - 2 ; case 1
	.short _021D798A - _021D78EE - 2 ; case 2
	.short _021D79A6 - _021D78EE - 2 ; case 3
	.short _021D79E0 - _021D78EE - 2 ; case 4
	.short _021D7A32 - _021D78EE - 2 ; case 5
_021D78FA:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7A54 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D7A58 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	bl FUN_0200E388
	mov r0, #1
	bl FUN_0200E388
	b _021D7A46
_021D7940:
	bl MOD61_021D7B38
	cmp r0, #0
	bne _021D794E
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D794E:
	ldr r0, _021D7A5C ; =MOD61_021D7A6C
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0
	bl FUN_0200E394
	mov r1, #4
	ldr r0, _021D7A60 ; =0x04000050
	mov r2, #8
	mov r3, #0x1c
	str r1, [sp]
	bl G2x_SetBlendAlpha_
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r1, #5
	ldr r0, [r4, #0x30]
	ldr r2, _021D7A64 ; =0x0000FFFF
	sub r3, r1, #6
	bl FUN_02003210
	b _021D7A46
_021D798A:
	add r0, #0xac
	ldr r0, [r0]
	cmp r0, #0
	beq _021D7996
	bl FUN_0200BC1C
_021D7996:
	ldr r0, [r4, #0x30]
	bl FUN_020038E4
	cmp r0, #0
	beq _021D7A46
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D79A6:
	add r0, #0xac
	ldr r0, [r0]
	cmp r0, #0
	beq _021D79B2
	bl FUN_0200BC1C
_021D79B2:
	ldrb r1, [r4, #0xc]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _021D7A68 ; =0x021D8444
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	bne _021D79C8
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D79C8:
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r1, #5
	ldr r0, [r4, #0x30]
	ldr r2, _021D7A64 ; =0x0000FFFF
	sub r3, r1, #6
	bl FUN_02003210
	b _021D7A46
_021D79E0:
	ldr r0, [r4, #0x30]
	bl FUN_020038E4
	cmp r0, #0
	beq _021D79FC
	add r4, #0xac
	ldr r0, [r4]
	cmp r0, #0
	beq _021D79F6
	bl FUN_0200BC1C
_021D79F6:
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D79FC:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7A54 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D7A58 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	b _021D7A46
_021D7A32:
	bl MOD61_021D7B84
	cmp r0, #0
	beq _021D7A40
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, pc}
_021D7A40:
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D7A46:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_021D7A54: .word 0xFFFFE0FF
_021D7A58: .word 0x04001000
_021D7A5C: .word MOD61_021D7A6C
_021D7A60: .word 0x04000050
_021D7A64: .word 0x0000FFFF
_021D7A68: .word MOD61_021D8444
	thumb_func_end MOD61_021D78D4

	thumb_func_start MOD61_021D7A6C
MOD61_021D7A6C: ; 0x021D7A6C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	cmp r0, #0
	beq _021D7A7A
	bl FUN_0200372C
_021D7A7A:
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	cmp r0, #0
	beq _021D7A88
	bl FUN_0200BC30
_021D7A88:
	bl NNS_GfdDoVramTransfer
	ldr r0, [r4, #0x18]
	bl FUN_0201AB60
	ldr r3, _021D7AA0 ; =0x027E0000
	ldr r1, _021D7AA4 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.align 2, 0
_021D7AA0: .word 0x027E0000
_021D7AA4: .word 0x00003FF8
	thumb_func_end MOD61_021D7A6C

	thumb_func_start MOD61_021D7AA8
MOD61_021D7AA8: ; 0x021D7AA8
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	ldr r2, [r4, #0x30]
	cmp r2, #0
	bne _021D7ABC
	bl FUN_0200CAB4
	add sp, #8
	pop {r4, pc}
_021D7ABC:
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _021D7B30
	ldrb r3, [r4, #0x17]
	ldrb r0, [r4, #0x16]
	cmp r3, r0
	beq _021D7AEA
	mov r1, #0
	ldr r0, _021D7B34 ; =0x00007FFF
	str r1, [sp]
	str r0, [sp, #4]
	add r3, #0x22
	add r0, r2, #0
	lsl r2, r3, #0x10
	lsr r2, r2, #0x10
	mov r3, #1
	bl FUN_020039E8
	ldrb r0, [r4, #0x16]
	strb r0, [r4, #0x17]
	mov r0, #0
	strb r0, [r4, #0x15]
	strb r0, [r4, #0x14]
_021D7AEA:
	ldrb r0, [r4, #0x14]
	mov r1, #0
	mov r3, #1
	str r0, [sp]
	ldr r0, _021D7B34 ; =0x00007FFF
	str r0, [sp, #4]
	ldrb r2, [r4, #0x16]
	ldr r0, [r4, #0x30]
	add r2, #0x22
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	bl FUN_020039E8
	ldrb r0, [r4, #0x15]
	ldrb r1, [r4, #0x14]
	cmp r0, #0
	beq _021D7B20
	sub r0, r1, #1
	strb r0, [r4, #0x14]
	cmp r1, #1
	bne _021D7B30
	ldrb r1, [r4, #0x15]
	mov r0, #1
	add sp, #8
	eor r0, r1
	strb r0, [r4, #0x15]
	pop {r4, pc}
_021D7B20:
	add r0, r1, #1
	strb r0, [r4, #0x14]
	cmp r1, #0xc
	bne _021D7B30
	ldrb r1, [r4, #0x15]
	mov r0, #1
	eor r0, r1
	strb r0, [r4, #0x15]
_021D7B30:
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_021D7B34: .word 0x00007FFF
	thumb_func_end MOD61_021D7AA8

	thumb_func_start MOD61_021D7B38
MOD61_021D7B38: ; 0x021D7B38
	push {r4, lr}
	add r4, r0, #0
	ldrh r1, [r4, #8]
	cmp r1, #3
	bhi _021D7B7A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7B4E: ; jump table
	.short _021D7B56 - _021D7B4E - 2 ; case 0
	.short _021D7B5C - _021D7B4E - 2 ; case 1
	.short _021D7B62 - _021D7B4E - 2 ; case 2
	.short _021D7B6E - _021D7B4E - 2 ; case 3
_021D7B56:
	bl MOD61_021D7BD0
	b _021D7B7A
_021D7B5C:
	bl MOD61_021D7CE8
	b _021D7B7A
_021D7B62:
	bl MOD61_021D7FF4
	add r0, r4, #0
	bl MOD61_021D8114
	b _021D7B7A
_021D7B6E:
	bl MOD61_021D8228
	mov r0, #0
	strh r0, [r4, #8]
	mov r0, #1
	pop {r4, pc}
_021D7B7A:
	ldrh r0, [r4, #8]
	add r0, r0, #1
	strh r0, [r4, #8]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD61_021D7B38

	thumb_func_start MOD61_021D7B84
MOD61_021D7B84: ; 0x021D7B84
	push {r4, lr}
	add r4, r0, #0
	bl MOD61_021D83E8
	add r0, r4, #0
	add r0, #0x24
	beq _021D7B98
	ldr r0, [r4, #0x20]
	bl DestroyMsgData
_021D7B98:
	add r0, r4, #0
	bl MOD61_021D80F4
	add r0, r4, #0
	bl MOD61_021D7FB4
	add r0, r4, #0
	bl MOD61_021D7CB4
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD61_021D7B84

	thumb_func_start MOD61_021D7BB0
MOD61_021D7BB0: ; 0x021D7BB0
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7BCC ; =0x021D84A0
	add r3, sp, #0
	mov r2, #5
_021D7BBA:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7BBA
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7BCC: .word MOD61_021D84A0
	thumb_func_end MOD61_021D7BB0

	thumb_func_start MOD61_021D7BD0
MOD61_021D7BD0: ; 0x021D7BD0
	push {r4, r5, lr}
	sub sp, #0x9c
	add r4, r0, #0
	bl MOD61_021D7BB0
	ldr r0, [r4]
	bl FUN_02016B94
	add r3, sp, #0
	ldr r5, _021D7CAC ; =0x021D8434
	str r0, [r4, #0x18]
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D7CB0 ; =0x021D84C8
	add r3, sp, #0x10
	mov r2, #0x11
_021D7BFC:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7BFC
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	ldr r0, [r4, #0x18]
	add r2, sp, #0x10
	add r3, r1, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #1
	add r2, sp, #0x2c
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #2
	add r2, sp, #0x48
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #3
	add r2, sp, #0x64
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #4
	add r2, sp, #0x80
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_02018744
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_02018744
	ldr r0, [r4, #0x18]
	mov r1, #2
	bl FUN_02018744
	ldr r0, [r4, #0x18]
	mov r1, #3
	bl FUN_02018744
	ldr r0, [r4, #0x18]
	mov r1, #4
	bl FUN_02018744
	mov r0, #0
	ldr r3, [r4]
	mov r1, #0x20
	add r2, r0, #0
	bl FUN_02017F18
	ldr r3, [r4]
	mov r0, #1
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	ldr r3, [r4]
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	ldr r3, [r4]
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	ldr r3, [r4]
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	add sp, #0x9c
	pop {r4, r5, pc}
	.align 2, 0
_021D7CAC: .word MOD61_021D8434
_021D7CB0: .word MOD61_021D84C8
	thumb_func_end MOD61_021D7BD0

	thumb_func_start MOD61_021D7CB4
MOD61_021D7CB4: ; 0x021D7CB4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	mov r1, #4
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD61_021D7CB4

	thumb_func_start MOD61_021D7CE8
MOD61_021D7CE8: ; 0x021D7CE8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r1, [r5]
	ldrb r4, [r0, #0xf]
	str r4, [sp, #0x1c]
	ldr r0, [sp, #0x1c]
	add r4, #0xc
	str r0, [sp, #0x20]
	add r0, #0x18
	str r0, [sp, #0x20]
	mov r0, #0x4f
	bl NARC_ctor
	mov r1, #0
	str r1, [sp]
	add r6, r0, #0
	ldr r0, [r5]
	mov r2, #1
	str r0, [sp, #4]
	ldr r0, [r5, #0x18]
	mov r3, #5
	bl FUN_0200CB00
	ldrh r0, [r5, #0xa]
	mov r1, #0
	mov r2, #0xa
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [r5]
	mov r3, #6
	str r0, [sp, #4]
	ldr r0, [r5, #0x18]
	bl FUN_0200CD68
	mov r0, #0x4f
	add r1, r4, #0
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0
	ldr r0, [r5]
	bl AllocFromHeapAtEnd
	add r7, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	add r2, r7, #0
	bl NARC_ReadWholeMember
	add r0, r7, #0
	add r1, sp, #0x28
	bl NNS_G2dGetUnpackedCharacterData
	ldr r3, [sp, #0x28]
	mov r0, #0
	str r0, [sp]
	ldr r2, [r3, #0x14]
	ldr r0, [r5, #0x18]
	ldr r3, [r3, #0x10]
	mov r1, #1
	bl FUN_02017E14
	ldr r3, [sp, #0x28]
	mov r0, #0
	str r0, [sp]
	ldr r2, [r3, #0x14]
	ldr r0, [r5, #0x18]
	ldr r3, [r3, #0x10]
	mov r1, #4
	bl FUN_02017E14
	add r0, r7, #0
	bl FreeToHeap
	ldr r1, [sp, #0x1c]
	mov r0, #0x4f
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0
	ldr r0, [r5]
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	ldr r1, [sp, #0x1c]
	add r0, r6, #0
	add r2, r4, #0
	bl NARC_ReadWholeMember
	add r0, r4, #0
	add r1, sp, #0x24
	bl NNS_G2dGetUnpackedPaletteData
	ldr r2, [sp, #0x24]
	mov r0, #4
	ldr r1, [r2, #0xc]
	ldr r2, [r2, #8]
	mov r3, #0
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	bl FUN_02017FB4
	ldr r0, [r5]
	bl FUN_02002FD0
	str r0, [r5, #0x30]
	ldr r3, [r5]
	mov r1, #0
	mov r2, #0xe0
	bl FUN_02003008
	ldr r0, [r5, #0x30]
	ldr r3, [r5]
	mov r1, #2
	mov r2, #0x60
	bl FUN_02003008
	mov r0, #0x60
	str r0, [sp]
	ldr r1, [sp, #0x24]
	mov r2, #0
	ldr r0, [r5, #0x30]
	ldr r1, [r1, #0xc]
	add r3, r2, #0
	bl FUN_02003054
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bne _021D7E00
	mov r0, #0x20
	str r0, [sp]
	ldr r1, [sp, #0x24]
	ldr r0, [r5, #0x30]
	ldr r1, [r1, #0xc]
	mov r2, #0
	add r1, #0x60
	mov r3, #0x10
	bl FUN_02003054
_021D7E00:
	mov r0, #2
	str r0, [sp]
	mov r0, #0x60
	str r0, [sp, #4]
	mov r2, #0
	str r2, [sp, #8]
	ldr r0, [r5, #0x30]
	ldr r3, [r5]
	mov r1, #0x13
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x30
	str r0, [sp, #8]
	ldr r0, [r5, #0x30]
	ldr r3, [r5]
	mov r1, #0xe
	mov r2, #6
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x40
	str r0, [sp, #8]
	ldr r0, [r5, #0x30]
	ldr r3, [r5]
	mov r1, #0xe
	mov r2, #7
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x50
	str r0, [sp, #8]
	ldr r0, [r5, #0x30]
	ldr r3, [r5]
	mov r1, #0x26
	mov r2, #0x18
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x60
	str r0, [sp, #8]
	ldrh r2, [r5, #0xa]
	ldr r0, [r5, #0x30]
	ldr r3, [r5]
	mov r1, #0x26
	add r2, #0x19
	bl FUN_020030E8
	mov r0, #0x10
	mov r1, #0
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r5, #0x30]
	add r2, r1, #0
	mov r3, #0x70
	bl FUN_020039E8
	mov r0, #0x10
	str r0, [sp]
	mov r2, #0
	str r2, [sp, #4]
	ldr r0, [r5, #0x30]
	mov r1, #2
	mov r3, #0x30
	bl FUN_020039E8
	ldr r0, [r5, #0x30]
	mov r1, #1
	bl FUN_020038F0
	ldr r0, [r5, #0x30]
	bl FUN_0200372C
	add r0, r4, #0
	bl FreeToHeap
	ldr r1, [sp, #0x20]
	mov r0, #0x4f
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0
	ldr r0, [r5]
	bl AllocFromHeap
	str r0, [r5, #0x34]
	ldr r1, [sp, #0x20]
	ldr r2, [r5, #0x34]
	add r0, r6, #0
	bl NARC_ReadWholeMember
	add r1, r5, #0
	ldr r0, [r5, #0x34]
	add r1, #0x3c
	bl NNS_G2dGetUnpackedScreenData
	mov r0, #0x4f
	mov r1, #0x24
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0
	ldr r0, [r5]
	bl AllocFromHeap
	str r0, [r5, #0x38]
	ldr r2, [r5, #0x38]
	add r0, r6, #0
	mov r1, #0x24
	bl NARC_ReadWholeMember
	add r1, r5, #0
	ldr r0, [r5, #0x38]
	add r1, #0x40
	bl NNS_G2dGetUnpackedScreenData
	add r0, r6, #0
	bl NARC_dtor
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x18]
	ldr r2, _021D7FAC ; =0x00002001
	mov r1, #4
	bl FUN_02018540
	mov r2, #0
	ldr r0, [r5, #0x3c]
	mov r1, #0x20
	str r1, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldrh r1, [r0]
	add r3, r2, #0
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #3
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [r5, #0x18]
	bl FUN_02018170
	ldr r0, [r5, #0x18]
	mov r1, #3
	bl FUN_0201AC68
	ldr r0, [r5, #0x18]
	mov r1, #4
	bl FUN_0201AC68
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bne _021D7FA6
	ldr r0, [r5, #0x40]
	mov r1, #0x20
	str r1, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	mov r2, #0
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldrh r1, [r0]
	add r3, r2, #0
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #2
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [r5, #0x18]
	bl FUN_02018170
	ldr r0, [r5, #0x18]
	mov r1, #2
	bl FUN_0201AC68
	mov r2, #0
	strb r2, [r5, #0x14]
	ldr r0, _021D7FB0 ; =MOD61_021D7AA8
	add r1, r5, #0
	strb r2, [r5, #0x15]
	bl FUN_0200CA44
_021D7FA6:
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_021D7FAC: .word 0x00002001
_021D7FB0: .word MOD61_021D7AA8
	thumb_func_end MOD61_021D7CE8

	thumb_func_start MOD61_021D7FB4
MOD61_021D7FB4: ; 0x021D7FB4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	bl FreeToHeap
	ldr r0, [r4, #0x34]
	bl FreeToHeap
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl FUN_02003038
	ldr r0, [r4, #0x30]
	mov r1, #0
	bl FUN_02003038
	ldr r0, [r4, #0x30]
	bl FUN_02002FEC
	mov r1, #0
	str r1, [r4, #0x30]
	ldr r0, _021D7FF0 ; =0x04000050
	add r2, r1, #0
	mov r3, #0x1f
	str r1, [sp]
	bl G2x_SetBlendAlpha_
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D7FF0: .word 0x04000050
	thumb_func_end MOD61_021D7FB4

	thumb_func_start MOD61_021D7FF4
MOD61_021D7FF4: ; 0x021D7FF4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	mov r3, #3
	add r5, r0, #0
	str r3, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r2, #1
	add r1, r5, #0
	ldr r0, _021D80DC ; =0x00000397
	str r2, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x18]
	add r1, #0x44
	bl FUN_02019064
	mov r0, #8
	str r0, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r2, #1
	add r1, r5, #0
	ldr r0, _021D80E0 ; =0x0000032F
	str r2, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x18]
	add r1, #0x54
	mov r3, #3
	bl FUN_02019064
	mov r0, #0xd
	str r0, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r2, #1
	add r1, r5, #0
	ldr r0, _021D80E4 ; =0x000002C7
	str r2, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x18]
	add r1, #0x64
	mov r3, #3
	bl FUN_02019064
	mov r0, #0x14
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r2, #1
	add r1, r5, #0
	ldr r0, _021D80E8 ; =0x000002B7
	str r2, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x18]
	add r1, #0x74
	mov r3, #0x15
	bl FUN_02019064
	mov r0, #0x14
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r2, #1
	add r1, r5, #0
	ldr r0, _021D80EC ; =0x000002A7
	str r2, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x18]
	add r1, #0x84
	mov r3, #3
	bl FUN_02019064
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _021D80F0 ; =0x00000297
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x18]
	add r1, #0x94
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	mov r4, #0
	add r5, #0x44
	add r6, r4, #0
_021D80BE:
	add r0, r5, #0
	add r1, r6, #0
	bl FillWindowPixelBuffer
	cmp r4, #5
	bge _021D80D0
	add r0, r5, #0
	bl CopyWindowToVram
_021D80D0:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #6
	blt _021D80BE
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D80DC: .word 0x00000397
_021D80E0: .word 0x0000032F
_021D80E4: .word 0x000002C7
_021D80E8: .word 0x000002B7
_021D80EC: .word 0x000002A7
_021D80F0: .word 0x00000297
	thumb_func_end MOD61_021D7FF4

	thumb_func_start MOD61_021D80F4
MOD61_021D80F4: ; 0x021D80F4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	add r5, #0x44
_021D80FC:
	add r0, r5, #0
	bl FUN_02019570
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #6
	blt _021D80FC
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD61_021D80F4

	thumb_func_start MOD61_021D8114
MOD61_021D8114: ; 0x021D8114
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r0, #0
	mov r7, #0
	add r6, r4, #0
	add r5, r7, #0
	add r6, #0x44
_021D8122:
	ldr r0, [r4, #0x1c]
	add r0, #0x1a
	add r0, r0, r5
	bl MailMsg_IsInit
	cmp r0, #0
	beq _021D8164
	ldr r0, [r4, #0x1c]
	ldr r1, [r4]
	add r0, #0x1a
	add r0, r0, r5
	bl MailMsg_GetExpandedString
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _021D8220 ; =0x00010200
	ldr r2, [sp, #0x10]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r6, #0
	mov r1, #1
	mov r3, #0
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r6, #0
	bl CopyWindowToVram
_021D8164:
	add r7, r7, #1
	add r5, #8
	add r6, #0x10
	cmp r7, #3
	blt _021D8122
	ldrb r0, [r4, #0xc]
	cmp r0, #1
	bne _021D81F8
	ldr r2, _021D8224 ; =0x00000169
	ldr r3, [r4]
	mov r0, #1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	str r0, [r4, #0x20]
	ldr r1, [r4]
	mov r0, #0x10
	bl String_ctor
	add r5, r0, #0
	add r0, r4, #0
	str r0, [sp, #0x18]
	add r0, #0x44
	mov r6, #0
	str r0, [sp, #0x18]
_021D8196:
	add r0, r5, #0
	bl StringSetEmpty
	ldr r0, [r4, #0x20]
	add r1, r6, #0
	add r2, r5, #0
	bl ReadMsgDataIntoString
	mov r0, #1
	add r1, r5, #0
	mov r2, #0
	bl FUN_02002E14
	mov r1, #0x40
	sub r7, r1, r0
	add r0, r6, #3
	lsl r0, r0, #4
	str r0, [sp, #0x14]
	mov r0, #2
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _021D8220 ; =0x00010200
	lsr r3, r7, #0x1f
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r3, r7, r3
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r2, r5, #0
	add r0, r0, r1
	mov r1, #1
	asr r3, r3, #1
	bl AddTextPrinterParameterized2
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r0, r0, r1
	bl CopyWindowToVram
	add r6, r6, #1
	cmp r6, #2
	blt _021D8196
	add r0, r5, #0
	bl String_dtor
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
_021D81F8:
	mov r0, #2
	str r0, [sp]
	mov r3, #0
	ldr r0, _021D8220 ; =0x00010200
	str r3, [sp, #4]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r2, [r4, #0x1c]
	add r0, r4, #0
	ldr r2, [r2, #0x10]
	add r0, #0x74
	mov r1, #1
	bl AddTextPrinterParameterized2
	add r4, #0x74
	add r0, r4, #0
	bl CopyWindowToVram
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D8220: .word 0x00010200
_021D8224: .word 0x00000169
	thumb_func_end MOD61_021D8114

	thumb_func_start MOD61_021D8228
MOD61_021D8228: ; 0x021D8228
	push {r4, r5, r6, r7, lr}
	sub sp, #0x94
	add r5, r0, #0
	bl FUN_02033F20
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bne _021D823A
	b _021D83D4
_021D823A:
	ldr r1, [r5]
	mov r0, #0x20
	bl FUN_0201C24C
	ldr r0, [r5]
	bl FUN_0200BB14
	add r1, r5, #0
	add r1, #0xa8
	str r0, [r1]
	add r0, r5, #0
	add r0, #0xa8
	ldr r0, [r0]
	bl FUN_0200BB34
	add r1, r5, #0
	add r1, #0xac
	add r2, sp, #0x40
	ldr r4, _021D83D8 ; =0x021D8480
	str r0, [r1]
	ldmia r4!, {r0, r1}
	add r3, r2, #0
	stmia r2!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r4!, {r0, r1}
	ldr r6, _021D83DC ; =0x021D8454
	stmia r2!, {r0, r1}
	add r4, sp, #0x2c
	ldmia r6!, {r0, r1}
	add r2, r4, #0
	stmia r4!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r4!, {r0, r1}
	ldr r0, [r6]
	ldr r6, _021D83E0 ; =0x021D8468
	str r0, [r4]
	add r4, sp, #0x14
	ldmia r6!, {r0, r1}
	stmia r4!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r4!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r4!, {r0, r1}
	add r0, r5, #0
	add r0, #0xa8
	add r1, r3, #0
	ldr r0, [r0]
	mov r3, #0x20
	bl FUN_0200BB6C
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xa8
	add r1, #0xac
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #3
	bl FUN_0200BBF0
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xa8
	add r1, #0xac
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, sp, #0x14
	bl FUN_0200BF60
	ldr r0, [r5]
	bl FUN_0200A064
	bl FUN_0206B888
	mov r1, #0
	add r3, r0, #0
	str r1, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xa8
	add r1, #0xac
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x13
	bl FUN_0200C06C
	bl FUN_0206B88C
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xa8
	add r1, #0xac
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x13
	bl FUN_0200C124
	bl FUN_0206B898
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xa8
	add r1, #0xac
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x13
	bl FUN_0200C13C
	mov r6, #0
	add r4, r6, #0
	add r7, r6, #0
	str r5, [sp, #0x10]
_021D8338:
	ldr r0, [r5, #0x1c]
	add r3, r0, r4
	ldrh r1, [r3, #0x14]
	ldr r0, _021D83E4 ; =0x0000FFFF
	cmp r1, r0
	beq _021D83D4
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldrh r3, [r3, #0x14]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xa8
	add r1, #0xac
	lsl r3, r3, #0x14
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x13
	lsr r3, r3, #0x14
	bl FUN_0200C918
	add r0, sp, #0x60
	mov r1, #0
	mov r2, #0x34
	bl MI_CpuFill8
	mov r0, #0x80
	sub r1, r0, r7
	add r0, sp, #0x60
	strh r1, [r0]
	mov r1, #0xa0
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	strh r1, [r0, #6]
	mov r0, #2
	str r0, [sp, #0x8c]
	ldr r0, [r5, #0x1c]
	add r2, sp, #0x60
	add r0, r0, r4
	ldrh r0, [r0, #0x14]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1c
	str r0, [sp, #0x6c]
	add r0, r1, #0
	str r0, [sp, #0x90]
	mov r0, #1
	str r0, [sp, #0x70]
	add r0, r1, #0
	str r0, [sp, #0x78]
	str r0, [sp, #0x7c]
	str r0, [sp, #0x80]
	sub r0, r1, #1
	str r0, [sp, #0x84]
	sub r0, r1, #1
	str r0, [sp, #0x88]
	add r0, r5, #0
	add r1, r5, #0
	str r6, [sp, #0x74]
	add r0, #0xa8
	add r1, #0xac
	ldr r0, [r0]
	ldr r1, [r1]
	bl FUN_0200C154
	ldr r1, [sp, #0x10]
	add r6, r6, #1
	add r1, #0xb0
	str r0, [r1]
	ldr r0, [sp, #0x10]
	add r4, r4, #2
	add r0, r0, #4
	add r7, #0x28
	str r0, [sp, #0x10]
	cmp r6, #3
	blt _021D8338
_021D83D4:
	add sp, #0x94
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D83D8: .word MOD61_021D8480
_021D83DC: .word MOD61_021D8454
_021D83E0: .word MOD61_021D8468
_021D83E4: .word 0x0000FFFF
	thumb_func_end MOD61_021D8228

	thumb_func_start MOD61_021D83E8
MOD61_021D83E8: ; 0x021D83E8
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldrb r0, [r6, #0xc]
	cmp r0, #0
	bne _021D8428
	mov r4, #0
	add r5, r6, #0
_021D83F6:
	add r0, r5, #0
	add r0, #0xb0
	ldr r0, [r0]
	cmp r0, #0
	beq _021D8404
	bl FUN_0200C3DC
_021D8404:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _021D83F6
	add r0, r6, #0
	add r1, r6, #0
	add r0, #0xa8
	add r1, #0xac
	ldr r0, [r0]
	ldr r1, [r1]
	bl FUN_0200C398
	add r6, #0xa8
	ldr r0, [r6]
	bl FUN_0200BD04
	bl FUN_0201C29C
_021D8428:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD61_021D83E8

	.rodata
	.global MOD61_021D842C
MOD61_021D842C: ; 0x021D842C
	.byte 0x00, 0x19, 0x0D, 0x06, 0x04, 0x03, 0x2B, 0x02

	.global MOD61_021D8434
MOD61_021D8434: ; 0x021D8434
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD61_021D8444
MOD61_021D8444: ; 0x021D8444
	.word MOD61_021D75AC, MOD61_021D75D0, MOD61_021D76F0, MOD61_021D77DC

	.global MOD61_021D8454
MOD61_021D8454: ; 0x021D8454
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00

	.global MOD61_021D8468
MOD61_021D8468: ; 0x021D8468
	.byte 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD61_021D8480
MOD61_021D8480: ; 0x021D8480
	.byte 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD61_021D84A0
MOD61_021D84A0: ; 0x021D84A0
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD61_021D84C8
MOD61_021D84C8: ; 0x021D84C8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1E, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1D, 0x00, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1C, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.bss
