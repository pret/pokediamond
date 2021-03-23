	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD68_021D74E0
MOD68_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D75CC ; =0xFFFFE0FF
	ldr r3, _021D75D0 ; =0x04001000
	and r1, r0
	str r1, [r2]
	ldr r1, [r3]
	and r0, r1
	str r0, [r3]
	add r0, r2, #0
	mov r1, #0
	add r0, #0x50
	strh r1, [r0]
	add r3, #0x50
	strh r1, [r3]
	mov r0, #3
	mov r1, #0x24
	lsr r2, r2, #9
	bl FUN_0201681C
	mov r1, #0x81
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #0x24
	bl OverlayManager_CreateAndGetData
	mov r2, #0x81
	mov r1, #0
	lsl r2, r2, #2
	add r5, r0, #0
	bl memset
	add r0, r4, #0
	bl OverlayManager_GetField18
	mov r1, #0x7e
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x24
	bl FUN_02016B94
	str r0, [r5]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x24
	ldrb r0, [r0, #8]
	bl LoadNutDataSingle
	mov r1, #0x7f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0
	mov r1, #0x24
	bl FUN_02079A70
	bl MOD68_021D76A0
	ldr r0, [r5]
	bl MOD68_021D76C0
	add r0, r5, #0
	bl MOD68_021D77A4
	bl MOD68_021D7858
	add r0, r5, #0
	bl MOD68_021D7870
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	add r0, r5, #0
	bl MOD68_021D7EEC
	add r0, r5, #0
	bl MOD68_021D78C8
	add r0, r5, #0
	bl MOD68_021D7D5C
	add r0, r5, #0
	bl MOD68_021D80B4
	add r0, r5, #0
	bl MOD68_021D8294
	ldr r0, _021D75D4 ; =MOD68_021D7680
	add r1, r5, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02033F20
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D75CC: .word 0xFFFFE0FF
_021D75D0: .word 0x04001000
_021D75D4: .word MOD68_021D7680
	thumb_func_end MOD68_021D74E0

	thumb_func_start MOD68_021D75D8
MOD68_021D75D8: ; 0x021D75D8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	bl OverlayManager_GetData
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhi _021D7620
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D75F4: ; jump table
	.short _021D75FC - _021D75F4 - 2 ; case 0
	.short _021D7604 - _021D75F4 - 2 ; case 1
	.short _021D760C - _021D75F4 - 2 ; case 2
	.short _021D7614 - _021D75F4 - 2 ; case 3
_021D75FC:
	bl MOD68_021D7D74
	str r0, [r4]
	b _021D7620
_021D7604:
	bl MOD68_021D7D9C
	str r0, [r4]
	b _021D7620
_021D760C:
	bl MOD68_021D7E84
	str r0, [r4]
	b _021D7620
_021D7614:
	bl MOD68_021D7E78
	cmp r0, #1
	bne _021D7620
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D7620:
	add r0, r5, #0
	bl MOD68_021D806C
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD68_021D75D8

	thumb_func_start MOD68_021D762C
MOD68_021D762C: ; 0x021D762C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, r4, #4
	bl MOD68_021D78EC
	ldr r0, [r4]
	bl MOD68_021D7774
	bl FUN_0201CD04
	add r0, r4, #0
	bl MOD68_021D78A8
	add r0, r4, #0
	bl MOD68_021D80A8
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x24
	bl FUN_020168D0
	ldr r0, _021D767C ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_021D767C: .word 0x04000050
	thumb_func_end MOD68_021D762C

	thumb_func_start MOD68_021D7680
MOD68_021D7680: ; 0x021D7680
	push {r3, lr}
	ldr r0, [r0]
	bl FUN_0201AB60
	ldr r3, _021D7698 ; =0x027E0000
	ldr r1, _021D769C ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, pc}
	nop
_021D7698: .word 0x027E0000
_021D769C: .word 0x00003FF8
	thumb_func_end MOD68_021D7680

	thumb_func_start MOD68_021D76A0
MOD68_021D76A0: ; 0x021D76A0
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D76BC ; =0x021D892C
	add r3, sp, #0
	mov r2, #5
_021D76AA:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D76AA
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D76BC: .word MOD68_021D892C
	thumb_func_end MOD68_021D76A0

	thumb_func_start MOD68_021D76C0
MOD68_021D76C0: ; 0x021D76C0
	push {r4, r5, lr}
	sub sp, #0x64
	ldr r5, _021D7764 ; =0x021D88C8
	add r3, sp, #0x54
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	bl MOD68_021D7FD8
	ldr r5, _021D7768 ; =0x021D8910
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	ldr r5, _021D776C ; =0x021D88D8
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #2
	mov r2, #3
	mov r3, #8
	bl FUN_0201AEE4
	ldr r5, _021D7770 ; =0x021D88F4
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #1
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x24
	bl FUN_02017F18
	add sp, #0x64
	pop {r4, r5, pc}
	nop
_021D7764: .word MOD68_021D88C8
_021D7768: .word MOD68_021D8910
_021D776C: .word MOD68_021D88D8
_021D7770: .word MOD68_021D88F4
	thumb_func_end MOD68_021D76C0

	thumb_func_start MOD68_021D7774
MOD68_021D7774: ; 0x021D7774
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xf
	mov r1, #0
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	mov r1, #3
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	mov r0, #0x24
	add r1, r4, #0
	bl FUN_02016A8C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD68_021D7774

	thumb_func_start MOD68_021D77A4
MOD68_021D77A4: ; 0x021D77A4
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x24
	str r0, [sp, #0xc]
	mov r1, #2
	ldr r2, [r5]
	mov r0, #0x35
	add r3, r1, #0
	bl FUN_0200687C
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x24
	str r0, [sp, #0xc]
	ldr r2, [r5]
	mov r0, #0x35
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x24
	str r0, [sp, #0xc]
	ldr r2, [r5]
	mov r0, #0x35
	mov r1, #1
	mov r3, #3
	bl FUN_020068C8
	mov r2, #0
	str r2, [sp]
	mov r0, #0x24
	str r0, [sp, #4]
	mov r0, #0x35
	mov r1, #3
	add r3, r2, #0
	bl FUN_02006930
	mov r0, #0x24
	mov r1, #0x80
	bl AllocFromHeap
	add r4, r0, #0
	ldr r0, _021D7854 ; =0x00003001
	mov r2, #0
	add r3, r4, #0
_021D7812:
	add r1, r2, r0
	strh r1, [r3]
	add r2, r2, #1
	add r3, r3, #2
	cmp r2, #0x40
	blo _021D7812
	mov r0, #5
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	mov r1, #1
	add r2, r4, #0
	mov r3, #2
	bl FUN_02018148
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r5]
	mov r1, #1
	bl FUN_02017CD0
	mov r1, #0x1e
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x24
	bl FUN_02002ED0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D7854: .word 0x00003001
	thumb_func_end MOD68_021D77A4

	thumb_func_start MOD68_021D7858
MOD68_021D7858: ; 0x021D7858
	push {r3, lr}
	mov r0, #8
	str r0, [sp]
	ldr r0, _021D786C ; =0x04000050
	mov r1, #1
	mov r2, #0xe
	mov r3, #0x17
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	.align 2, 0
_021D786C: .word 0x04000050
	thumb_func_end MOD68_021D7858

	thumb_func_start MOD68_021D7870
MOD68_021D7870: ; 0x021D7870
	push {r4, lr}
	ldr r2, _021D78A4 ; =0x0000015F
	add r4, r0, #0
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x24
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r1, #0xc4
	str r0, [r1]
	mov r0, #0xf
	mov r1, #2
	mov r2, #0
	mov r3, #0x24
	bl MessagePrinter_new
	add r1, r4, #0
	add r1, #0xcc
	str r0, [r1]
	mov r0, #0x24
	bl ScrStrBufs_new
	add r4, #0xc8
	str r0, [r4]
	pop {r4, pc}
	.align 2, 0
_021D78A4: .word 0x0000015F
	thumb_func_end MOD68_021D7870

	thumb_func_start MOD68_021D78A8
MOD68_021D78A8: ; 0x021D78A8
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	bl DestroyMsgData
	add r0, r4, #0
	add r0, #0xcc
	ldr r0, [r0]
	bl MessagePrinter_delete
	add r4, #0xc8
	ldr r0, [r4]
	bl ScrStrBufs_delete
	pop {r4, pc}
	thumb_func_end MOD68_021D78A8

	thumb_func_start MOD68_021D78C8
MOD68_021D78C8: ; 0x021D78C8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r4, _021D78E8 ; =0x021D8954
	mov r6, #0
	add r5, r7, #4
_021D78D2:
	ldr r0, [r7]
	add r1, r5, #0
	add r2, r4, #0
	bl FUN_02019150
	add r6, r6, #1
	add r4, #8
	add r5, #0x10
	cmp r6, #0xc
	blo _021D78D2
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D78E8: .word MOD68_021D8954
	thumb_func_end MOD68_021D78C8

	thumb_func_start MOD68_021D78EC
MOD68_021D78EC: ; 0x021D78EC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021D78F2:
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #0xc
	blo _021D78F2
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD68_021D78EC

	thumb_func_start MOD68_021D7904
MOD68_021D7904: ; 0x021D7904
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #4
	add r0, #0xc4
	lsl r4, r1, #4
	ldr r0, [r0]
	add r1, r2, #0
	add r6, r3, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x10]
	mov r0, #0
	ldr r1, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02002E14
	add r7, r0, #0
	add r0, r5, r4
	bl FUN_0201AB0C
	add r3, r0, #0
	mov r1, #0
	lsl r3, r3, #3
	sub r3, r3, r7
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldr r2, [sp, #0x10]
	add r0, r5, r4
	lsr r3, r3, #1
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r5, r4
	bl FUN_02019220
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD68_021D7904

	thumb_func_start MOD68_021D7958
MOD68_021D7958: ; 0x021D7958
	push {r4, lr}
	add r4, r0, #0
	add r0, r4, #4
	mov r1, #4
	bl FUN_02019620
	mov r1, #0
	ldr r3, _021D7974 ; =0x00010204
	add r0, r4, #0
	add r2, r1, #0
	bl MOD68_021D7904
	pop {r4, pc}
	nop
_021D7974: .word 0x00010204
	thumb_func_end MOD68_021D7958

	thumb_func_start MOD68_021D7978
MOD68_021D7978: ; 0x021D7978
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x24
	mov r1, #0
	bl FUN_02019620
	ldr r3, _021D7994 ; =0x000F0200
	add r0, r4, #0
	mov r1, #2
	mov r2, #1
	bl MOD68_021D7904
	pop {r4, pc}
	nop
_021D7994: .word 0x000F0200
	thumb_func_end MOD68_021D7978

	thumb_func_start MOD68_021D7998
MOD68_021D7998: ; 0x021D7998
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x34
	mov r1, #0
	bl FUN_02019620
	ldr r3, _021D79B4 ; =0x000F0200
	add r0, r4, #0
	mov r1, #3
	mov r2, #2
	bl MOD68_021D7904
	pop {r4, pc}
	nop
_021D79B4: .word 0x000F0200
	thumb_func_end MOD68_021D7998

	thumb_func_start MOD68_021D79B8
MOD68_021D79B8: ; 0x021D79B8
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x44
	mov r1, #0
	bl FUN_02019620
	ldr r3, _021D79D4 ; =0x000F0200
	add r0, r4, #0
	mov r1, #4
	mov r2, #3
	bl MOD68_021D7904
	pop {r4, pc}
	nop
_021D79D4: .word 0x000F0200
	thumb_func_end MOD68_021D79B8

	thumb_func_start MOD68_021D79D8
MOD68_021D79D8: ; 0x021D79D8
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x54
	mov r1, #0
	bl FUN_02019620
	ldr r3, _021D79F4 ; =0x000F0200
	add r0, r4, #0
	mov r1, #5
	mov r2, #4
	bl MOD68_021D7904
	pop {r4, pc}
	nop
_021D79F4: .word 0x000F0200
	thumb_func_end MOD68_021D79D8

	thumb_func_start MOD68_021D79F8
MOD68_021D79F8: ; 0x021D79F8
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x64
	mov r1, #0
	bl FUN_02019620
	ldr r3, _021D7A14 ; =0x000F0200
	add r0, r4, #0
	mov r1, #6
	mov r2, #5
	bl MOD68_021D7904
	pop {r4, pc}
	nop
_021D7A14: .word 0x000F0200
	thumb_func_end MOD68_021D79F8

	thumb_func_start MOD68_021D7A18
MOD68_021D7A18: ; 0x021D7A18
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r5, #0
	add r4, #0x14
	add r0, r4, #0
	mov r1, #0
	bl FUN_02019620
	mov r0, #5
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xcc
	ldr r0, [r0]
	mov r1, #2
	add r2, r4, #0
	mov r3, #0
	bl FUN_0200B9A8
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #6
	bl NewString_ReadMsgData
	add r7, r0, #0
	mov r0, #6
	mov r1, #0x24
	bl String_ctor
	mov r3, #2
	add r6, r0, #0
	mov r2, #0x7e
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	add r0, r5, #0
	ldrb r2, [r2, #8]
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #0
	add r2, r2, #1
	bl BufferIntegerAsString
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	add r1, r6, #0
	add r2, r7, #0
	bl StringExpandPlaceholders
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7AE0 ; =0x000F0200
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r3, #0x10
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x24
	ldrb r0, [r0, #8]
	bl GetNutName
	add r5, r0, #0
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7AE0 ; =0x000F0200
	add r2, r5, #0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r3, #0x28
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	bl String_dtor
	add r0, r4, #0
	bl FUN_02019220
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7AE0: .word 0x000F0200
	thumb_func_end MOD68_021D7A18

	thumb_func_start MOD68_021D7AE4
MOD68_021D7AE4: ; 0x021D7AE4
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r5, r4, #0
	add r5, #0xb4
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x24
	ldrb r0, [r0, #8]
	bl GetNutDesc
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7B30 ; =0x00010200
	add r2, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl FUN_02019220
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D7B30: .word 0x00010200
	thumb_func_end MOD68_021D7AE4

	thumb_func_start MOD68_021D7B34
MOD68_021D7B34: ; 0x021D7B34
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r5, r4, #0
	add r5, #0x94
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	add r4, #0xc4
	ldr r0, [r4]
	mov r1, #0xa
	bl NewString_ReadMsgData
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7B7C ; =0x000F0200
	add r2, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl FUN_02019220
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D7B7C: .word 0x000F0200
	thumb_func_end MOD68_021D7B34

	thumb_func_start MOD68_021D7B80
MOD68_021D7B80: ; 0x021D7B80
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r5, r4, #0
	add r5, #0xa4
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl GetNutAttr
	add r1, r0, #0
	beq _021D7BA4
	sub r1, r1, #1
_021D7BA4:
	add r4, #0xc4
	ldr r0, [r4]
	add r1, #0xb
	bl NewString_ReadMsgData
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7BD8 ; =0x000F0200
	add r2, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl FUN_02019220
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7BD8: .word 0x000F0200
	thumb_func_end MOD68_021D7B80

	thumb_func_start MOD68_021D7BDC
MOD68_021D7BDC: ; 0x021D7BDC
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r5, r4, #0
	add r5, #0x74
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	add r4, #0xc4
	ldr r0, [r4]
	mov r1, #8
	bl NewString_ReadMsgData
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7C24 ; =0x000F0200
	add r2, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl FUN_02019220
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D7C24: .word 0x000F0200
	thumb_func_end MOD68_021D7BDC

	thumb_func_start MOD68_021D7C28
MOD68_021D7C28: ; 0x021D7C28
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r6, r5, #0
	add r6, #0x84
	add r0, r6, #0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl GetNutAttr
	mov r1, #0xfa
	lsl r1, r1, #2
	mul r1, r0
	add r0, r1, #0
	mov r1, #0xfe
	bl _u32_div_f
	add r0, r0, #5
	mov r1, #0xa
	bl _u32_div_f
	add r7, r0, #0
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #9
	bl NewString_ReadMsgData
	str r0, [sp, #0x10]
	mov r0, #0x20
	mov r1, #0x24
	bl String_ctor
	add r4, r0, #0
	add r0, r7, #0
	mov r1, #0xa
	bl _u32_div_f
	mov r1, #0
	add r2, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r3, #2
	bl BufferIntegerAsString
	add r0, r7, #0
	mov r1, #0xa
	bl _u32_div_f
	mov r0, #0
	add r2, r1, #0
	str r0, [sp]
	mov r1, #1
	add r0, r5, #0
	str r1, [sp, #4]
	add r0, #0xc8
	ldr r0, [r0]
	add r3, r1, #0
	bl BufferIntegerAsString
	add r5, #0xc8
	ldr r0, [r5]
	ldr r2, [sp, #0x10]
	add r1, r4, #0
	bl StringExpandPlaceholders
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7CEC ; =0x000F0200
	add r2, r4, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl FUN_02019220
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D7CEC: .word 0x000F0200
	thumb_func_end MOD68_021D7C28

	thumb_func_start MOD68_021D7CF0
MOD68_021D7CF0: ; 0x021D7CF0
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #7
	bhi _021D7D5A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7D04: ; jump table
	.short _021D7D14 - _021D7D04 - 2 ; case 0
	.short _021D7D1A - _021D7D04 - 2 ; case 1
	.short _021D7D20 - _021D7D04 - 2 ; case 2
	.short _021D7D26 - _021D7D04 - 2 ; case 3
	.short _021D7D32 - _021D7D04 - 2 ; case 4
	.short _021D7D3E - _021D7D04 - 2 ; case 5
	.short _021D7D4A - _021D7D04 - 2 ; case 6
	.short _021D7D56 - _021D7D04 - 2 ; case 7
_021D7D14:
	bl MOD68_021D7958
	pop {r4, pc}
_021D7D1A:
	bl MOD68_021D7978
	pop {r4, pc}
_021D7D20:
	bl MOD68_021D7A18
	pop {r4, pc}
_021D7D26:
	bl MOD68_021D79F8
	add r0, r4, #0
	bl MOD68_021D7998
	pop {r4, pc}
_021D7D32:
	bl MOD68_021D79B8
	add r0, r4, #0
	bl MOD68_021D79D8
	pop {r4, pc}
_021D7D3E:
	bl MOD68_021D7BDC
	add r0, r4, #0
	bl MOD68_021D7C28
	pop {r4, pc}
_021D7D4A:
	bl MOD68_021D7B34
	add r0, r4, #0
	bl MOD68_021D7B80
	pop {r4, pc}
_021D7D56:
	bl MOD68_021D7AE4
_021D7D5A:
	pop {r4, pc}
	thumb_func_end MOD68_021D7CF0

	thumb_func_start MOD68_021D7D5C
MOD68_021D7D5C: ; 0x021D7D5C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021D7D62:
	lsl r1, r4, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl MOD68_021D7CF0
	add r4, r4, #1
	cmp r4, #8
	blo _021D7D62
	pop {r3, r4, r5, pc}
	thumb_func_end MOD68_021D7D5C

	thumb_func_start MOD68_021D7D74
MOD68_021D7D74: ; 0x021D7D74
	push {r3, lr}
	bl FUN_0200E308
	cmp r0, #1
	bne _021D7D92
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D7D98 ; =0x04000050
	mov r1, #2
	mov r2, #4
	mov r3, #0x10
	bl G2x_SetBlendAlpha_
	mov r0, #1
	pop {r3, pc}
_021D7D92:
	mov r0, #0
	pop {r3, pc}
	nop
_021D7D98: .word 0x04000050
	thumb_func_end MOD68_021D7D74

	thumb_func_start MOD68_021D7D9C
MOD68_021D7D9C: ; 0x021D7D9C
	push {r4, lr}
	ldr r1, _021D7E70 ; =gMain
	add r4, r0, #0
	ldr r3, [r1, #0x44]
	mov r2, #0x40
	add r0, r3, #0
	tst r0, r2
	beq _021D7DF8
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r2, #0x41
	ldrb r1, [r0, #8]
	bl MOD68_021D7F44
	mov r1, #0x7e
	lsl r1, r1, #2
	ldr r3, [r4, r1]
	ldrb r2, [r3, #8]
	cmp r2, r0
	beq _021D7DF4
	strb r0, [r3, #8]
	add r0, r1, #0
	mov r2, #0
	add r0, #9
	strb r2, [r4, r0]
	add r0, r1, #0
	add r0, #8
	strb r2, [r4, r0]
	ldr r1, [r4, r1]
	ldrb r0, [r1, #0xa]
	cmp r0, #3
	bne _021D7DEA
	ldrb r0, [r1, #9]
	cmp r0, #0
	beq _021D7DEA
	sub r0, r0, #1
	strb r0, [r1, #9]
	b _021D7DF0
_021D7DEA:
	ldrb r0, [r1, #0xa]
	sub r0, r0, #1
	strb r0, [r1, #0xa]
_021D7DF0:
	mov r0, #2
	pop {r4, pc}
_021D7DF4:
	mov r0, #1
	pop {r4, pc}
_021D7DF8:
	mov r0, #0x80
	tst r0, r3
	beq _021D7E50
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r2, #1
	ldrb r1, [r0, #8]
	bl MOD68_021D7F44
	mov r1, #0x7e
	lsl r1, r1, #2
	ldr r3, [r4, r1]
	ldrb r2, [r3, #8]
	cmp r2, r0
	beq _021D7E4C
	strb r0, [r3, #8]
	add r0, r1, #0
	mov r2, #0
	add r0, #9
	strb r2, [r4, r0]
	add r0, r1, #0
	add r0, #8
	strb r2, [r4, r0]
	ldr r3, [r4, r1]
	ldrb r0, [r3, #0xa]
	cmp r0, #5
	bne _021D7E42
	ldrb r1, [r3, #9]
	ldrb r0, [r3, #0xb]
	add r2, r1, #0
	add r2, #9
	cmp r2, r0
	bge _021D7E42
	add r0, r1, #1
	strb r0, [r3, #9]
	b _021D7E48
_021D7E42:
	ldrb r0, [r3, #0xa]
	add r0, r0, #1
	strb r0, [r3, #0xa]
_021D7E48:
	mov r0, #2
	pop {r4, pc}
_021D7E4C:
	mov r0, #1
	pop {r4, pc}
_021D7E50:
	ldr r1, [r1, #0x48]
	mov r0, #2
	tst r0, r1
	bne _021D7E60
	ldr r0, _021D7E74 ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	beq _021D7E6C
_021D7E60:
	mov r0, #1
	mov r1, #0x24
	bl FUN_02079A70
	mov r0, #3
	pop {r4, pc}
_021D7E6C:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D7E70: .word gMain
_021D7E74: .word gMain + 0x40
	thumb_func_end MOD68_021D7D9C

	thumb_func_start MOD68_021D7E78
MOD68_021D7E78: ; 0x021D7E78
	push {r3, lr}
	bl FUN_0200E308
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
	thumb_func_end MOD68_021D7E78

	thumb_func_start MOD68_021D7E84
MOD68_021D7E84: ; 0x021D7E84
	push {r3, r4, r5, lr}
	mov r4, #2
	add r5, r0, #0
	lsl r1, r4, #8
	ldrb r1, [r5, r1]
	cmp r1, #0
	bne _021D7EA8
	ldr r0, _021D7EE4 ; =0x00000201
	ldrb r1, [r5, r0]
	add r1, r1, #4
	strb r1, [r5, r0]
	ldrb r0, [r5, r0]
	cmp r0, #0x10
	bne _021D7ECE
	mov r1, #1
	lsl r0, r1, #9
	strb r1, [r5, r0]
	b _021D7ECE
_021D7EA8:
	cmp r1, #1
	bne _021D7EB8
	bl MOD68_021D7F98
	add r1, r4, #0
	lsl r0, r1, #8
	strb r1, [r5, r0]
	b _021D7ECE
_021D7EB8:
	ldr r0, _021D7EE4 ; =0x00000201
	ldrb r1, [r5, r0]
	sub r1, r1, #4
	strb r1, [r5, r0]
	ldrb r1, [r5, r0]
	cmp r1, #0
	bne _021D7ECE
	mov r1, #0
	sub r0, r0, #1
	strb r1, [r5, r0]
	mov r4, #1
_021D7ECE:
	ldr r0, _021D7EE4 ; =0x00000201
	ldrb r2, [r5, r0]
	mov r0, #0x10
	sub r1, r0, r2
	lsl r0, r2, #8
	orr r1, r0
	ldr r0, _021D7EE8 ; =0x04000052
	strh r1, [r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D7EE4: .word 0x00000201
_021D7EE8: .word 0x04000052
	thumb_func_end MOD68_021D7E84

	thumb_func_start MOD68_021D7EEC
MOD68_021D7EEC: ; 0x021D7EEC
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #8]
	bl MOD68_021D7F3C
	mov r3, #1
	add r1, r0, #0
	str r3, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x24
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x35
	bl FUN_0200687C
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #8]
	bl MOD68_021D7F40
	add r1, r0, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x24
	str r0, [sp, #4]
	mov r0, #0x35
	mov r2, #0
	mov r3, #0x60
	bl FUN_02006930
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD68_021D7EEC

	thumb_func_start MOD68_021D7F3C
MOD68_021D7F3C: ; 0x021D7F3C
	add r0, r0, #6
	bx lr
	thumb_func_end MOD68_021D7F3C

	thumb_func_start MOD68_021D7F40
MOD68_021D7F40: ; 0x021D7F40
	add r0, #0x46
	bx lr
	thumb_func_end MOD68_021D7F40

	thumb_func_start MOD68_021D7F44
MOD68_021D7F44: ; 0x021D7F44
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r5, r2, #0
	add r6, r0, #0
	add r4, r7, #0
	cmp r5, #0
	bge _021D7F72
	cmp r7, #0
	beq _021D7F92
_021D7F56:
	sub r4, r4, #1
	lsl r1, r4, #0x10
	add r0, r6, #0
	lsr r1, r1, #0x10
	bl FUN_02085224
	cmp r0, #1
	bne _021D7F6C
	add r7, r4, #0
	add r5, r5, #1
	beq _021D7F92
_021D7F6C:
	cmp r4, #0
	beq _021D7F92
	b _021D7F56
_021D7F72:
	cmp r7, #0x3f
	beq _021D7F92
_021D7F76:
	add r4, r4, #1
	lsl r1, r4, #0x10
	add r0, r6, #0
	lsr r1, r1, #0x10
	bl FUN_02085224
	cmp r0, #1
	bne _021D7F8E
	lsl r0, r4, #0x10
	lsr r7, r0, #0x10
	sub r5, r5, #1
	beq _021D7F92
_021D7F8E:
	cmp r4, #0x3f
	bne _021D7F76
_021D7F92:
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD68_021D7F44

	thumb_func_start MOD68_021D7F98
MOD68_021D7F98: ; 0x021D7F98
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x24
	ldrb r0, [r0, #8]
	bl LoadNutDataSingle
	mov r1, #0x7f
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD68_021D7D5C
	add r0, r4, #0
	bl MOD68_021D7EEC
	add r0, r4, #0
	bl MOD68_021D85F4
	ldr r0, [r4]
	mov r1, #1
	bl FUN_02017CD0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD68_021D7F98

	thumb_func_start MOD68_021D7FD8
MOD68_021D7FD8: ; 0x021D7FD8
	push {r3, r4, lr}
	sub sp, #4
	bl G3X_Init
	bl G3X_InitMtxStack
	ldr r0, _021D8050 ; =0x04000060
	ldr r1, _021D8054 ; =0xFFFFCFFD
	ldrh r2, [r0]
	ldr r3, _021D8058 ; =0x0000CFFB
	and r2, r1
	strh r2, [r0]
	ldrh r2, [r0]
	and r2, r3
	strh r2, [r0]
	add r2, r1, #2
	ldrh r4, [r0]
	add r1, r1, #2
	sub r3, #0x1c
	and r4, r2
	mov r2, #8
	orr r2, r4
	strh r2, [r0]
	ldrh r2, [r0]
	and r2, r1
	mov r1, #0x10
	orr r1, r2
	strh r1, [r0]
	ldrh r1, [r0]
	and r1, r3
	strh r1, [r0]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl G3X_SetFog
	mov r0, #0
	ldr r2, _021D805C ; =0x00007FFF
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _021D8060 ; =0x04000540
	mov r0, #0
	str r0, [r1]
	ldr r0, _021D8064 ; =0xBFFF0000
	str r0, [r1, #0x40]
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r1, _021D8068 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	strh r2, [r1]
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D8050: .word 0x04000060
_021D8054: .word 0xFFFFCFFD
_021D8058: .word 0x0000CFFB
_021D805C: .word 0x00007FFF
_021D8060: .word 0x04000540
_021D8064: .word 0xBFFF0000
_021D8068: .word 0x04000008
	thumb_func_end MOD68_021D7FD8

	thumb_func_start MOD68_021D806C
MOD68_021D806C: ; 0x021D806C
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020222AC
	bl FUN_0201EBA4
	ldr r2, _021D80A0 ; =0x04000440
	mov r3, #0
	add r1, r2, #0
	str r3, [r2]
	add r1, #0x14
	str r3, [r1]
	mov r0, #2
	str r0, [r2]
	add r0, r4, #0
	add r0, #0xd4
	str r3, [r1]
	bl MOD68_021D8124
	add r0, r4, #0
	bl MOD68_021D81C0
	ldr r0, _021D80A4 ; =0x04000540
	mov r1, #1
	str r1, [r0]
	pop {r4, pc}
	.align 2, 0
_021D80A0: .word 0x04000440
_021D80A4: .word 0x04000540
	thumb_func_end MOD68_021D806C

	thumb_func_start MOD68_021D80A8
MOD68_021D80A8: ; 0x021D80A8
	ldr r3, _021D80B0 ; =FUN_0201EB70
	add r0, #0xd0
	ldr r0, [r0]
	bx r3
	.align 2, 0
_021D80B0: .word FUN_0201EB70
	thumb_func_end MOD68_021D80A8

	thumb_func_start MOD68_021D80B4
MOD68_021D80B4: ; 0x021D80B4
	push {r3, r4, lr}
	sub sp, #0x1c
	ldr r3, _021D811C ; =0x021D88BC
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x10
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, sp, #8
	str r0, [r2]
	mov r0, #0
	strh r0, [r1]
	strh r0, [r1, #2]
	strh r0, [r1, #4]
	strh r0, [r1, #6]
	mov r0, #0x24
	bl FUN_0201EB64
	add r1, r4, #0
	add r1, #0xd0
	str r0, [r1]
	mov r1, #1
	add r0, r4, #0
	str r1, [sp]
	add r0, #0xd0
	ldr r0, [r0]
	ldr r3, _021D8120 ; =0x000005C1
	str r0, [sp, #4]
	add r0, sp, #0x10
	lsl r1, r1, #0x10
	add r2, sp, #8
	bl FUN_0201ED10
	add r2, r4, #0
	add r2, #0xd0
	mov r1, #0x19
	ldr r2, [r2]
	mov r0, #0
	lsl r1, r1, #0xe
	bl FUN_0201EC94
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl FUN_0201EC88
	add r4, #0xd0
	ldr r0, [r4]
	bl FUN_0201EB8C
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0
_021D811C: .word MOD68_021D88BC
_021D8120: .word 0x000005C1
	thumb_func_end MOD68_021D80B4

	thumb_func_start MOD68_021D8124
MOD68_021D8124: ; 0x021D8124
	push {r4, r5, r6, r7}
	add r4, r0, #0
	ldr r0, _021D818C ; =0x121800C0
	ldr r1, _021D8190 ; =0x040004A4
	ldr r2, _021D8194 ; =0x00003FE8
	str r0, [r1]
	mov r0, #1
	str r0, [r1, #0x5c]
	ldr r0, _021D8198 ; =0x0400048C
	mov r3, #0
	sub r1, #0x24
_021D813A:
	str r2, [r1]
	ldrh r7, [r4, #2]
	ldrh r5, [r4]
	ldrh r6, [r4, #4]
	lsl r7, r7, #0x10
	orr r5, r7
	str r5, [r0]
	str r6, [r0]
	str r2, [r1]
	ldrh r7, [r4, #8]
	ldrh r5, [r4, #6]
	ldrh r6, [r4, #0xa]
	lsl r7, r7, #0x10
	orr r5, r7
	str r5, [r0]
	str r6, [r0]
	str r2, [r1]
	ldrh r7, [r4, #0x14]
	ldrh r5, [r4, #0x12]
	ldrh r6, [r4, #0x16]
	lsl r7, r7, #0x10
	orr r5, r7
	str r5, [r0]
	str r6, [r0]
	str r2, [r1]
	ldrh r7, [r4, #0xe]
	ldrh r5, [r4, #0xc]
	ldrh r6, [r4, #0x10]
	lsl r7, r7, #0x10
	orr r5, r7
	str r5, [r0]
	add r3, r3, #1
	add r4, #0x18
	str r6, [r0]
	cmp r3, #4
	blo _021D813A
	ldr r0, _021D819C ; =0x04000504
	mov r1, #0
	str r1, [r0]
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_021D818C: .word 0x121800C0
_021D8190: .word 0x040004A4
_021D8194: .word 0x00003FE8
_021D8198: .word 0x0400048C
_021D819C: .word 0x04000504
	thumb_func_end MOD68_021D8124

	thumb_func_start MOD68_021D81A0
MOD68_021D81A0: ; 0x021D81A0
	mov r2, #0
	ldrsh r3, [r0, r2]
	ldrsh r2, [r1, r2]
	add r2, r3, r2
	strh r2, [r0]
	mov r2, #2
	ldrsh r3, [r0, r2]
	ldrsh r2, [r1, r2]
	add r2, r3, r2
	strh r2, [r0, #2]
	mov r2, #4
	ldrsh r3, [r0, r2]
	ldrsh r1, [r1, r2]
	add r1, r3, r1
	strh r1, [r0, #4]
	bx lr
	thumb_func_end MOD68_021D81A0

	thumb_func_start MOD68_021D81C0
MOD68_021D81C0: ; 0x021D81C0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp]
	mov r0, #0x7d
	ldr r1, [sp]
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	cmp r1, #4
	beq _021D828E
	cmp r1, #3
	bne _021D81FA
	ldr r6, [sp]
	mov r5, #0
	sub r0, #0x60
_021D81DC:
	add r3, r6, #0
	add r4, r6, r0
	add r3, #0xd4
	mov r2, #0xc
_021D81E4:
	ldrh r1, [r4]
	add r4, r4, #2
	strh r1, [r3]
	add r3, r3, #2
	sub r2, r2, #1
	bne _021D81E4
	add r5, r5, #1
	add r6, #0x18
	cmp r5, #4
	blo _021D81DC
	b _021D8280
_021D81FA:
	mov r1, #0
	str r1, [sp, #4]
	add r2, r0, #0
	ldr r1, [sp]
	sub r2, #0xc0
	add r1, r1, r2
	str r1, [sp, #0x14]
	ldr r1, [sp]
	add r2, r0, #0
	str r1, [sp, #0x10]
	add r1, #0xd4
	str r1, [sp, #0x10]
	ldr r1, [sp]
	sub r2, #0xba
	add r1, r1, r2
	add r2, r0, #0
	str r1, [sp, #0xc]
	ldr r1, [sp]
	sub r2, #0xb4
	str r1, [sp, #8]
	add r1, #0xda
	str r1, [sp, #8]
	ldr r1, [sp]
	sub r0, #0xae
	add r4, r1, #0
	add r5, r1, #0
	add r7, r1, r2
	add r4, #0xe0
	add r6, r1, r0
	add r5, #0xe6
_021D8236:
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	bl MOD68_021D81A0
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	bl MOD68_021D81A0
	add r0, r4, #0
	add r1, r7, #0
	bl MOD68_021D81A0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD68_021D81A0
	ldr r0, [sp, #0x14]
	add r7, #0x18
	add r0, #0x18
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r4, #0x18
	add r0, #0x18
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	add r6, #0x18
	add r0, #0x18
	str r0, [sp, #0xc]
	ldr r0, [sp, #8]
	add r5, #0x18
	add r0, #0x18
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #4
	blo _021D8236
_021D8280:
	mov r1, #0x7d
	ldr r0, [sp]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r2, r0, #1
	ldr r0, [sp]
	str r2, [r0, r1]
_021D828E:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD68_021D81C0

	thumb_func_start MOD68_021D8294
MOD68_021D8294: ; 0x021D8294
	push {r4, r5, r6, lr}
	sub sp, #0x18
	ldr r1, _021D840C ; =0x021D89BC
	add r5, r0, #0
	ldrh r2, [r1, #0x34]
	add r3, sp, #0
	add r5, #0xd8
	strh r2, [r3, #0x12]
	ldrh r2, [r1, #0x36]
	strh r2, [r3, #0x14]
	ldrh r1, [r1, #0x38]
	strh r1, [r3, #0x16]
	add r1, r0, #0
	ldrh r4, [r3, #0x12]
	add r1, #0xd4
	strh r4, [r1]
	add r1, r0, #0
	ldrh r2, [r3, #0x14]
	add r1, #0xd6
	strh r2, [r1]
	ldrh r1, [r3, #0x16]
	strh r1, [r5]
	add r5, r0, #0
	add r5, #0xda
	strh r4, [r5]
	add r5, r0, #0
	add r5, #0xdc
	strh r2, [r5]
	add r5, r0, #0
	add r5, #0xde
	strh r1, [r5]
	add r5, r0, #0
	add r5, #0xe0
	strh r4, [r5]
	add r5, r0, #0
	add r5, #0xe2
	strh r2, [r5]
	add r5, r0, #0
	add r5, #0xe4
	strh r1, [r5]
	add r5, r0, #0
	add r5, #0xe6
	strh r4, [r5]
	add r4, r0, #0
	add r4, #0xe8
	strh r2, [r4]
	add r2, r0, #0
	add r2, #0xea
	strh r1, [r2]
	ldr r1, _021D8410 ; =0x021D89FC
	add r5, r0, #0
	ldrh r2, [r1, #0x2a]
	add r5, #0xf0
	strh r2, [r3, #0xc]
	ldrh r2, [r1, #0x2c]
	strh r2, [r3, #0xe]
	ldrh r1, [r1, #0x2e]
	add r2, r0, #0
	add r2, #0xec
	strh r1, [r3, #0x10]
	ldrh r1, [r3, #0xc]
	strh r1, [r2]
	add r2, r0, #0
	ldrh r4, [r3, #0xe]
	add r2, #0xee
	strh r4, [r2]
	ldrh r2, [r3, #0x10]
	strh r2, [r5]
	add r5, r0, #0
	add r5, #0xf2
	strh r1, [r5]
	add r5, r0, #0
	add r5, #0xf4
	strh r4, [r5]
	add r5, r0, #0
	add r5, #0xf6
	strh r2, [r5]
	add r5, r0, #0
	add r5, #0xf8
	strh r1, [r5]
	add r5, r0, #0
	add r5, #0xfa
	strh r4, [r5]
	add r5, r0, #0
	add r5, #0xfc
	strh r2, [r5]
	add r5, r0, #0
	add r5, #0xfe
	strh r1, [r5]
	mov r1, #1
	lsl r1, r1, #8
	strh r4, [r0, r1]
	add r4, r1, #2
	strh r2, [r0, r4]
	ldr r2, _021D8414 ; =0x021D8A3C
	ldrh r4, [r2, #0x20]
	strh r4, [r3, #6]
	ldrh r4, [r2, #0x22]
	strh r4, [r3, #8]
	ldrh r2, [r2, #0x24]
	strh r2, [r3, #0xa]
	ldrh r6, [r3, #6]
	add r2, r1, #4
	strh r6, [r0, r2]
	ldrh r5, [r3, #8]
	add r2, r1, #6
	strh r5, [r0, r2]
	add r2, r1, #0
	ldrh r4, [r3, #0xa]
	add r2, #8
	strh r4, [r0, r2]
	add r2, r1, #0
	add r2, #0xa
	strh r6, [r0, r2]
	add r2, r1, #0
	add r2, #0xc
	strh r5, [r0, r2]
	add r2, r1, #0
	add r2, #0xe
	strh r4, [r0, r2]
	add r2, r1, #0
	add r2, #0x10
	strh r6, [r0, r2]
	add r2, r1, #0
	add r2, #0x12
	strh r5, [r0, r2]
	add r2, r1, #0
	add r2, #0x14
	strh r4, [r0, r2]
	add r2, r1, #0
	add r2, #0x16
	strh r6, [r0, r2]
	add r2, r1, #0
	add r2, #0x18
	strh r5, [r0, r2]
	add r2, r1, #0
	add r2, #0x1a
	strh r4, [r0, r2]
	ldr r2, _021D8418 ; =0x021D8A7C
	ldrh r4, [r2, #0x16]
	strh r4, [r3]
	ldrh r4, [r2, #0x18]
	strh r4, [r3, #2]
	ldrh r2, [r2, #0x1a]
	strh r2, [r3, #4]
	add r2, r1, #0
	ldrh r5, [r3]
	add r2, #0x1c
	strh r5, [r0, r2]
	add r2, r1, #0
	ldrh r4, [r3, #2]
	add r2, #0x1e
	strh r4, [r0, r2]
	ldrh r2, [r3, #4]
	add r3, r1, #0
	add r3, #0x20
	strh r2, [r0, r3]
	add r3, r1, #0
	add r3, #0x22
	strh r5, [r0, r3]
	add r3, r1, #0
	add r3, #0x24
	strh r4, [r0, r3]
	add r3, r1, #0
	add r3, #0x26
	strh r2, [r0, r3]
	add r3, r1, #0
	add r3, #0x28
	strh r5, [r0, r3]
	add r3, r1, #0
	add r3, #0x2a
	strh r4, [r0, r3]
	add r3, r1, #0
	add r3, #0x2c
	strh r2, [r0, r3]
	add r3, r1, #0
	add r3, #0x2e
	strh r5, [r0, r3]
	add r3, r1, #0
	add r3, #0x30
	strh r4, [r0, r3]
	add r1, #0x32
	strh r2, [r0, r1]
	bl MOD68_021D85F4
	add sp, #0x18
	pop {r4, r5, r6, pc}
	nop
_021D840C: .word MOD68_021D89BC
_021D8410: .word MOD68_021D89FC
_021D8414: .word MOD68_021D8A3C
_021D8418: .word MOD68_021D8A7C
	thumb_func_end MOD68_021D8294

	thumb_func_start MOD68_021D841C
MOD68_021D841C: ; 0x021D841C
	push {r4, r5}
	cmp r2, #0xff
	bne _021D8432
	ldrh r2, [r0]
	strh r2, [r1]
	ldrh r2, [r0, #2]
	strh r2, [r1, #2]
	ldrh r0, [r0, #4]
	strh r0, [r1, #4]
	pop {r4, r5}
	bx lr
_021D8432:
	cmp r2, #0
	bne _021D8446
	ldrh r2, [r0, #6]
	strh r2, [r1]
	ldrh r2, [r0, #8]
	strh r2, [r1, #2]
	ldrh r0, [r0, #0xa]
	strh r0, [r1, #4]
	pop {r4, r5}
	bx lr
_021D8446:
	mov r3, #6
	ldrsh r5, [r0, r3]
	mov r3, #0xc
	ldrsh r3, [r0, r3]
	add r4, r3, #0
	mul r4, r2
	add r3, r5, r4
	strh r3, [r1]
	mov r3, #8
	ldrsh r5, [r0, r3]
	mov r3, #0xe
	ldrsh r3, [r0, r3]
	add r4, r3, #0
	mul r4, r2
	add r3, r5, r4
	strh r3, [r1, #2]
	mov r3, #0xa
	ldrsh r4, [r0, r3]
	mov r3, #0x10
	ldrsh r0, [r0, r3]
	mul r2, r0
	add r0, r4, r2
	strh r0, [r1, #4]
	pop {r4, r5}
	bx lr
	thumb_func_end MOD68_021D841C

	thumb_func_start MOD68_021D8478
MOD68_021D8478: ; 0x021D8478
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0
	ldrsh r1, [r4, r0]
	ldrsh r0, [r5, r0]
	add r6, r2, #0
	sub r7, r1, r0
	add r0, r7, #0
	bl _fflt
	ldr r1, _021D85EC ; =0x45800000
	bl _fdiv
	ldr r1, _021D85F0 ; =0x40800000
	bl _fdiv
	mov r1, #0
	bl _fgr
	bls _021D84CC
	add r0, r7, #0
	bl _fflt
	ldr r1, _021D85EC ; =0x45800000
	bl _fdiv
	ldr r1, _021D85F0 ; =0x40800000
	bl _fdiv
	add r1, r0, #0
	ldr r0, _021D85EC ; =0x45800000
	bl _fmul
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	bl _ffix
	b _021D84F2
_021D84CC:
	add r0, r7, #0
	bl _fflt
	ldr r1, _021D85EC ; =0x45800000
	bl _fdiv
	ldr r1, _021D85F0 ; =0x40800000
	bl _fdiv
	add r1, r0, #0
	ldr r0, _021D85EC ; =0x45800000
	bl _fmul
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
	bl _ffix
_021D84F2:
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	strh r0, [r6]
	mov r0, #2
	ldrsh r1, [r4, r0]
	ldrsh r0, [r5, r0]
	sub r7, r1, r0
	add r0, r7, #0
	bl _fflt
	ldr r1, _021D85EC ; =0x45800000
	bl _fdiv
	ldr r1, _021D85F0 ; =0x40800000
	bl _fdiv
	mov r1, #0
	bl _fgr
	bls _021D8544
	add r0, r7, #0
	bl _fflt
	ldr r1, _021D85EC ; =0x45800000
	bl _fdiv
	ldr r1, _021D85F0 ; =0x40800000
	bl _fdiv
	add r1, r0, #0
	ldr r0, _021D85EC ; =0x45800000
	bl _fmul
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	bl _ffix
	b _021D856A
_021D8544:
	add r0, r7, #0
	bl _fflt
	ldr r1, _021D85EC ; =0x45800000
	bl _fdiv
	ldr r1, _021D85F0 ; =0x40800000
	bl _fdiv
	add r1, r0, #0
	ldr r0, _021D85EC ; =0x45800000
	bl _fmul
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
	bl _ffix
_021D856A:
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	strh r0, [r6, #2]
	mov r0, #4
	ldrsh r1, [r4, r0]
	ldrsh r0, [r5, r0]
	sub r4, r1, r0
	add r0, r4, #0
	bl _fflt
	ldr r1, _021D85EC ; =0x45800000
	bl _fdiv
	ldr r1, _021D85F0 ; =0x40800000
	bl _fdiv
	mov r1, #0
	bl _fgr
	bls _021D85BC
	add r0, r4, #0
	bl _fflt
	ldr r1, _021D85EC ; =0x45800000
	bl _fdiv
	ldr r1, _021D85F0 ; =0x40800000
	bl _fdiv
	add r1, r0, #0
	ldr r0, _021D85EC ; =0x45800000
	bl _fmul
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	bl _ffix
	b _021D85E2
_021D85BC:
	add r0, r4, #0
	bl _fflt
	ldr r1, _021D85EC ; =0x45800000
	bl _fdiv
	ldr r1, _021D85F0 ; =0x40800000
	bl _fdiv
	add r1, r0, #0
	ldr r0, _021D85EC ; =0x45800000
	bl _fmul
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
	bl _ffix
_021D85E2:
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	strh r0, [r6, #4]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D85EC: .word 0x45800000
_021D85F0: .word 0x40800000
	thumb_func_end MOD68_021D8478

	thumb_func_start MOD68_021D85F4
MOD68_021D85F4: ; 0x021D85F4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #5
	bl GetNutAttr
	add r2, r0, #0
	mov r1, #0x65
	lsl r1, r1, #2
	lsl r2, r2, #0x18
	ldr r0, _021D885C ; =0x021D89B4
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl GetNutAttr
	add r2, r0, #0
	ldr r1, _021D8860 ; =0x0000019A
	lsl r2, r2, #0x18
	ldr r0, _021D8864 ; =0x021D89C6
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #7
	bl GetNutAttr
	add r2, r0, #0
	ldr r1, _021D8868 ; =0x000001A6
	lsl r2, r2, #0x18
	ldr r0, _021D886C ; =0x021D89D8
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	mov r1, #0x1a
	lsl r1, r1, #4
	ldr r0, _021D8870 ; =0x021D89EA
	add r1, r5, r1
	mov r2, #0
	bl MOD68_021D841C
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #9
	bl GetNutAttr
	add r2, r0, #0
	mov r1, #0x6b
	lsl r1, r1, #2
	lsl r2, r2, #0x18
	ldr r0, _021D8874 ; =0x021D89FC
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #5
	bl GetNutAttr
	add r2, r0, #0
	ldr r1, _021D8878 ; =0x000001B2
	lsl r2, r2, #0x18
	ldr r0, _021D887C ; =0x021D8A0E
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	ldr r1, _021D8880 ; =0x000001BE
	ldr r0, _021D8884 ; =0x021D8A20
	add r1, r5, r1
	mov r2, #0
	bl MOD68_021D841C
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #8
	bl GetNutAttr
	add r2, r0, #0
	mov r1, #0x6e
	lsl r1, r1, #2
	lsl r2, r2, #0x18
	ldr r0, _021D8888 ; =0x021D8A32
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #9
	bl GetNutAttr
	add r2, r0, #0
	mov r1, #0x71
	lsl r1, r1, #2
	lsl r2, r2, #0x18
	ldr r0, _021D888C ; =0x021D8A44
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	ldr r1, _021D8890 ; =0x000001CA
	ldr r0, _021D8894 ; =0x021D8A56
	add r1, r5, r1
	mov r2, #0
	bl MOD68_021D841C
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #7
	bl GetNutAttr
	add r2, r0, #0
	ldr r1, _021D8898 ; =0x000001D6
	lsl r2, r2, #0x18
	ldr r0, _021D889C ; =0x021D8A68
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #8
	bl GetNutAttr
	add r2, r0, #0
	mov r1, #0x1d
	lsl r1, r1, #4
	lsl r2, r2, #0x18
	ldr r0, _021D88A0 ; =0x021D8A7A
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	mov r1, #0x77
	lsl r1, r1, #2
	ldr r0, _021D88A4 ; =0x021D8A8C
	add r1, r5, r1
	mov r2, #0
	bl MOD68_021D841C
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl GetNutAttr
	add r2, r0, #0
	ldr r1, _021D88A8 ; =0x000001E2
	lsl r2, r2, #0x18
	ldr r0, _021D88AC ; =0x021D8A9E
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #7
	bl GetNutAttr
	add r2, r0, #0
	ldr r1, _021D88B0 ; =0x000001EE
	lsl r2, r2, #0x18
	ldr r0, _021D88B4 ; =0x021D8AB0
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #8
	bl GetNutAttr
	add r2, r0, #0
	mov r1, #0x7a
	lsl r1, r1, #2
	lsl r2, r2, #0x18
	ldr r0, _021D88B8 ; =0x021D8AC2
	add r1, r5, r1
	lsr r2, r2, #0x18
	bl MOD68_021D841C
	mov r0, #0
	str r0, [sp, #0x24]
	mov r0, #0x4d
	lsl r0, r0, #2
	add r1, r5, r0
	str r1, [sp, #0x20]
	add r1, r0, #0
	add r1, #0x60
	add r1, r5, r1
	str r1, [sp, #0x1c]
	add r1, r5, #0
	str r1, [sp, #0x18]
	add r1, #0xd4
	str r1, [sp, #0x18]
	add r1, r0, #6
	add r1, r5, r1
	str r1, [sp, #0x14]
	add r1, r0, #0
	add r1, #0x66
	add r1, r5, r1
	str r1, [sp, #0x10]
	add r1, r5, #0
	str r1, [sp, #0xc]
	add r1, #0xda
	str r1, [sp, #0xc]
	add r1, r0, #0
	add r1, #0xc
	add r1, r5, r1
	str r1, [sp, #8]
	add r1, r0, #0
	add r1, #0x6c
	add r1, r5, r1
	str r1, [sp, #4]
	add r1, r5, #0
	str r1, [sp]
	add r1, #0xe0
	str r1, [sp]
	add r1, r0, #0
	add r1, #0x12
	add r0, #0x72
	add r4, r5, #0
	add r7, r5, r1
	add r6, r5, r0
	add r4, #0xe6
_021D87E2:
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	bl MOD68_021D8478
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x14]
	bl MOD68_021D8478
	ldr r0, [sp]
	ldr r1, [sp, #4]
	ldr r2, [sp, #8]
	bl MOD68_021D8478
	add r0, r4, #0
	add r1, r6, #0
	add r2, r7, #0
	bl MOD68_021D8478
	ldr r0, [sp, #0x20]
	add r7, #0x18
	add r0, #0x18
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r6, #0x18
	add r0, #0x18
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r4, #0x18
	add r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r0, #0x18
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r0, #0x18
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	add r0, #0x18
	str r0, [sp, #0xc]
	ldr r0, [sp, #8]
	add r0, #0x18
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	add r0, #0x18
	str r0, [sp, #4]
	ldr r0, [sp]
	add r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #0x24]
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, #4
	blo _021D87E2
	mov r0, #0x7d
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D885C: .word MOD68_021D89B4
_021D8860: .word 0x0000019A
_021D8864: .word MOD68_021D89C6
_021D8868: .word 0x000001A6
_021D886C: .word MOD68_021D89D8
_021D8870: .word MOD68_021D89EA
_021D8874: .word MOD68_021D89FC
_021D8878: .word 0x000001B2
_021D887C: .word MOD68_021D8A0E
_021D8880: .word 0x000001BE
_021D8884: .word MOD68_021D8A20
_021D8888: .word MOD68_021D8A32
_021D888C: .word MOD68_021D8A44
_021D8890: .word 0x000001CA
_021D8894: .word MOD68_021D8A56
_021D8898: .word 0x000001D6
_021D889C: .word MOD68_021D8A68
_021D88A0: .word MOD68_021D8A7A
_021D88A4: .word MOD68_021D8A8C
_021D88A8: .word 0x000001E2
_021D88AC: .word MOD68_021D8A9E
_021D88B0: .word 0x000001EE
_021D88B4: .word MOD68_021D8AB0
_021D88B8: .word MOD68_021D8AC2
	thumb_func_end MOD68_021D85F4

	.rodata
	.global MOD68_021D88BC
MOD68_021D88BC: ; 0x021D88BC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00

	.global MOD68_021D88C8
MOD68_021D88C8: ; 0x021D88C8
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD68_021D88D8
MOD68_021D88D8: ; 0x021D88D8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD68_021D88F4
MOD68_021D88F4: ; 0x021D88F4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD68_021D8910
MOD68_021D8910: ; 0x021D8910
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD68_021D892C
MOD68_021D892C: ; 0x021D892C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD68_021D8954
MOD68_021D8954: ; 0x021D8954
	.byte 0x03, 0x01, 0x00, 0x0C, 0x02, 0x02, 0xE8, 0x03, 0x01, 0x01, 0x03, 0x0A, 0x02, 0x0F, 0x41, 0x00
	.byte 0x03, 0x12, 0x01, 0x07, 0x02, 0x0F, 0x00, 0x02, 0x03, 0x1A, 0x06, 0x06, 0x02, 0x0F, 0x0E, 0x02
	.byte 0x03, 0x17, 0x0C, 0x06, 0x02, 0x0F, 0x1A, 0x02, 0x03, 0x0E, 0x0C, 0x06, 0x02, 0x0F, 0x26, 0x02
	.byte 0x03, 0x0B, 0x06, 0x06, 0x02, 0x0F, 0x32, 0x02, 0x03, 0x02, 0x0D, 0x06, 0x02, 0x0F, 0x3E, 0x02
	.byte 0x01, 0x08, 0x0D, 0x06, 0x02, 0x0F, 0x55, 0x00, 0x03, 0x02, 0x0F, 0x06, 0x02, 0x0F, 0x4A, 0x02
	.byte 0x01, 0x08, 0x0F, 0x0F, 0x02, 0x0F, 0x61, 0x00, 0x01, 0x02, 0x11, 0x1C, 0x06, 0x0F, 0x7F, 0x00

	.global MOD68_021D89B4
MOD68_021D89B4: ; 0x021D89B4
	.byte 0x80, 0x05, 0xAA, 0x0B, 0x00, 0x00, 0x80, 0x05

	.global MOD68_021D89BC
MOD68_021D89BC: ; 0x021D89BC
	.byte 0x47, 0x06, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00

	.global MOD68_021D89C6
MOD68_021D89C6: ; 0x021D89C6
	.byte 0xEC, 0x09, 0x40, 0x07, 0x00, 0x00, 0x0D, 0x06, 0xB9, 0x05, 0x00, 0x00, 0x14, 0x00, 0x08, 0x00
	.byte 0x00, 0x00

	.global MOD68_021D89D8
MOD68_021D89D8: ; 0x021D89D8
	.byte 0x60, 0x08, 0xA7, 0x00, 0x00, 0x00, 0xDC, 0x05, 0xE7, 0x04, 0x00, 0x00, 0x0D, 0x00, 0xEA, 0xFF
	.byte 0x00, 0x00

	.global MOD68_021D89EA
MOD68_021D89EA: ; 0x021D89EA
	.byte 0x80, 0x05, 0x82, 0x05, 0x00, 0x00, 0x80, 0x05, 0x82, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00

	.global MOD68_021D89FC
MOD68_021D89FC: ; 0x021D89FC
	.byte 0x3F, 0x01, 0x40, 0x07, 0x00, 0x00, 0x1B, 0x05, 0xB9, 0x05, 0x00, 0x00, 0xEC, 0xFF, 0x08, 0x00
	.byte 0x00, 0x00

	.global MOD68_021D8A0E
MOD68_021D8A0E: ; 0x021D8A0E
	.byte 0xA8, 0x05, 0xAA, 0x0B, 0x00, 0x00, 0xA8, 0x05, 0x47, 0x06, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00
	.byte 0x00, 0x00

	.global MOD68_021D8A20
MOD68_021D8A20: ; 0x021D8A20
	.byte 0xA8, 0x05, 0x82, 0x05, 0x00, 0x00, 0xA8, 0x05, 0x82, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00

	.global MOD68_021D8A32
MOD68_021D8A32: ; 0x021D8A32
	.byte 0xC0, 0x02, 0xA7, 0x00, 0x00, 0x00, 0x4B, 0x05, 0xE7, 0x04

	.global MOD68_021D8A3C
MOD68_021D8A3C: ; 0x021D8A3C
	.byte 0x00, 0x00, 0xF3, 0xFF, 0xEA, 0xFF, 0x00, 0x00

	.global MOD68_021D8A44
MOD68_021D8A44: ; 0x021D8A44
	.byte 0x3F, 0x01, 0x40, 0x07, 0x00, 0x00, 0x1B, 0x05, 0xB9, 0x05, 0x00, 0x00, 0xEC, 0xFF, 0x08, 0x00
	.byte 0x00, 0x00

	.global MOD68_021D8A56
MOD68_021D8A56: ; 0x021D8A56
	.byte 0xA8, 0x05, 0x82, 0x05, 0x00, 0x00, 0xA8, 0x05, 0x82, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00

	.global MOD68_021D8A68
MOD68_021D8A68: ; 0x021D8A68
	.byte 0x60, 0x08, 0xA7, 0x00, 0x00, 0x00, 0xFF, 0x05, 0xE7, 0x04, 0x00, 0x00, 0x0C, 0x00, 0xEA, 0xFF
	.byte 0x00, 0x00

	.global MOD68_021D8A7A
MOD68_021D8A7A: ; 0x021D8A7A
	.byte 0xC0, 0x02

	.global MOD68_021D8A7C
MOD68_021D8A7C: ; 0x021D8A7C
	.byte 0xA7, 0x00, 0x00, 0x00, 0x4B, 0x05, 0xE7, 0x04, 0x00, 0x00, 0xF3, 0xFF, 0xEA, 0xFF, 0x00, 0x00

	.global MOD68_021D8A8C
MOD68_021D8A8C: ; 0x021D8A8C
	.byte 0x80, 0x05, 0x82, 0x05, 0x00, 0x00, 0x80, 0x05, 0x82, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00

	.global MOD68_021D8A9E
MOD68_021D8A9E: ; 0x021D8A9E
	.byte 0xEC, 0x09, 0x40, 0x07, 0x00, 0x00, 0x0D, 0x06, 0xB9, 0x05, 0x00, 0x00, 0x14, 0x00, 0x08, 0x00
	.byte 0x00, 0x00

	.global MOD68_021D8AB0
MOD68_021D8AB0: ; 0x021D8AB0
	.byte 0x60, 0x08, 0xA7, 0x00, 0x00, 0x00, 0xDC, 0x05, 0xE7, 0x04, 0x00, 0x00, 0x0D, 0x00, 0xEA, 0xFF
	.byte 0x00, 0x00

	.global MOD68_021D8AC2
MOD68_021D8AC2: ; 0x021D8AC2
	.byte 0xC0, 0x02, 0xA7, 0x00, 0x00, 0x00, 0x28, 0x05, 0xE7, 0x04, 0x00, 0x00, 0xF4, 0xFF, 0xEA, 0xFF
	.byte 0x00, 0x00

	.data
	.bss
