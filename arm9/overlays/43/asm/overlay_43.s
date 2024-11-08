	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov43_02254854
ov43_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0xb0
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl ov43_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =ov43_0225493C
	add r1, r4, #0
	mov r2, #1
	bl SysTask_CreateOnMainQueue
	cmp r0, #0
	beq _0225488C
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0225488C:
	add r0, r4, #0
	bl FreeToHeap
_02254892:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254898: .word ov43_0225493C
	thumb_func_end ov43_02254854

	thumb_func_start ov43_0225489C
ov43_0225489C: ; 0x0225489C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	add r1, r5, #0
	add r1, #0xac
	str r7, [r1]
	str r2, [sp]
	bl ov43_02254A88
	str r0, [r5, #0xc]
	add r0, r5, #0
	add r0, #0xac
	ldr r0, [r0]
	bl ov20_02252C38
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetSpecialSpawnWarpPtr
	add r6, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl MapHeader_MapIsOnMainMatrix
	cmp r0, #0
	beq _022548E0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #8]
	str r0, [r5, #4]
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #0xc]
	b _022548E6
_022548E0:
	ldr r0, [r6, #8]
	str r0, [r5, #4]
	ldr r0, [r6, #0xc]
_022548E6:
	str r0, [r5, #8]
	ldr r1, [r5, #4]
	asr r0, r1, #4
	lsr r0, r0, #0x1b
	add r0, r1, r0
	asr r0, r0, #5
	str r0, [r5, #4]
	ldr r1, [r5, #8]
	asr r0, r1, #4
	lsr r0, r0, #0x1b
	add r0, r1, r0
	asr r0, r0, #5
	str r0, [r5, #8]
	add r0, r5, #0
	add r1, r7, #0
	bl ov43_02254B60
	add r0, r5, #0
	ldr r2, [sp]
	add r0, #0xa8
	add r1, r5, #4
	bl ov43_02254B8C
	cmp r0, #0
	beq _02254924
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02254924:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov43_0225489C

	thumb_func_start ov43_02254928
ov43_02254928: ; 0x02254928
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xa8
	ldr r0, [r0]
	bl ov43_02254BCC
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end ov43_02254928

	thumb_func_start ov43_0225493C
ov43_0225493C: ; 0x0225493C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhs _0225496A
	lsl r2, r1, #2
	ldr r1, _0225496C ; =ov43_022550A8
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _0225496A
	add r0, r4, #0
	bl ov43_02254928
	add r0, r5, #0
	bl SysTask_Destroy
	add r4, #0xac
	ldr r0, [r4]
	bl ov20_022529A0
_0225496A:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0225496C: .word ov43_022550A8
	thumb_func_end ov43_0225493C

	thumb_func_start ov43_02254970
ov43_02254970: ; 0x02254970
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end ov43_02254970

	thumb_func_start ov43_02254978
ov43_02254978: ; 0x02254978
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254980
	b _02254982
_02254980:
	mov r1, #2
_02254982:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end ov43_02254978

	thumb_func_start ov43_0225498C
ov43_0225498C: ; 0x0225498C
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _0225499C
	cmp r0, #1
	beq _022549B0
	b _022549D2
_0225499C:
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	mov r1, #0
	bl ov43_02254BD8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549D2
_022549B0:
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	mov r1, #0
	bl ov43_02254BFC
	cmp r0, #0
	beq _022549D2
	add r0, r4, #0
	add r0, #0xac
	ldr r0, [r0]
	bl ov20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl ov43_02254978
_022549D2:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov43_0225498C

	thumb_func_start ov43_022549D8
ov43_022549D8: ; 0x022549D8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _022549F0
	mov r1, #2
	bl ov43_02254978
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_022549F0:
	bl ov43_02254AF8
	add r1, r4, #0
	add r1, #0x94
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	mov r1, #2
	bl ov43_02254BFC
	cmp r0, #0
	beq _02254A48
	add r0, sp, #4
	add r1, sp, #0
	bl ov20_02252BB8
	cmp r0, #0
	beq _02254A48
	ldr r0, [sp, #4]
	sub r0, #0x10
	cmp r0, #0xc0
	bhs _02254A22
	mov r1, #1
	b _02254A24
_02254A22:
	mov r1, #0
_02254A24:
	ldr r0, [sp]
	sub r0, #0x10
	cmp r0, #0xc0
	bhs _02254A30
	mov r0, #1
	b _02254A32
_02254A30:
	mov r0, #0
_02254A32:
	tst r0, r1
	beq _02254A48
	add r0, r4, #0
	bl ov43_02254A88
	str r0, [r4, #0xc]
	add r4, #0xa8
	ldr r0, [r4]
	mov r1, #2
	bl ov43_02254BD8
_02254A48:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov43_022549D8

	thumb_func_start ov43_02254A50
ov43_02254A50: ; 0x02254A50
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A60
	cmp r0, #1
	beq _02254A74
	b _02254A84
_02254A60:
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	mov r1, #1
	bl ov43_02254BD8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A84
_02254A74:
	add r4, #0xa8
	ldr r0, [r4]
	bl ov43_02254C08
	cmp r0, #0
	beq _02254A84
	mov r0, #1
	pop {r4, pc}
_02254A84:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end ov43_02254A50

	thumb_func_start ov43_02254A88
ov43_02254A88: ; 0x02254A88
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, #0xac
	ldr r0, [r0]
	bl ov20_02252C40
	bl sub_02024ECC
	mov r4, #0
	add r6, r0, #0
	add r7, r4, #0
_02254A9E:
	add r0, r6, #0
	add r1, r4, #0
	bl sub_020252B8
	cmp r0, #1
	bne _02254AEA
	add r0, r6, #0
	add r1, r4, #0
	bl sub_02025238
	cmp r0, #5
	bne _02254AEA
	ldr r1, _02254AF4 ; =ov43_022550B4
	lsl r0, r4, #1
	ldr r2, _02254AF4 ; =ov43_022550B4
	add r1, r1, r0
	ldrb r0, [r2, r0]
	strb r0, [r5, #0x10]
	ldrb r0, [r1, #1]
	strb r0, [r5, #0x11]
	b _02254ACC
_02254AC8:
	add r1, r1, #2
	add r4, r4, #1
_02254ACC:
	add r0, r4, #1
	cmp r0, #0x76
	bhs _02254AE2
	ldrb r2, [r5, #0x10]
	ldrb r0, [r1, #2]
	cmp r2, r0
	bne _02254AE2
	ldrb r2, [r5, #0x11]
	ldrb r0, [r1, #3]
	cmp r2, r0
	beq _02254AC8
_02254AE2:
	add r7, r7, #1
	add r5, r5, #2
	cmp r7, #0x40
	bge _02254AF0
_02254AEA:
	add r4, r4, #1
	cmp r4, #0x76
	blo _02254A9E
_02254AF0:
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254AF4: .word ov43_022550B4
	thumb_func_end ov43_02254A88

	thumb_func_start ov43_02254AF8
ov43_02254AF8: ; 0x02254AF8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, #0xac
	ldr r0, [r0]
	mov r6, #0
	bl ov20_02252C30
	cmp r0, #0
	beq _02254B5C
	add r0, r5, #0
	add r0, #0xac
	ldr r0, [r0]
	bl ov20_02252C38
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetSpecialSpawnWarpPtr
	add r7, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl MapHeader_MapIsOnMainMatrix
	cmp r0, #0
	beq _02254B36
	ldr r1, [r4, #0x1c]
	ldr r0, [r1, #8]
	ldr r1, [r1, #0xc]
	b _02254B3A
_02254B36:
	ldr r0, [r7, #8]
	ldr r1, [r7, #0xc]
_02254B3A:
	asr r2, r0, #4
	lsr r2, r2, #0x1b
	add r2, r0, r2
	asr r0, r2, #5
	asr r2, r1, #4
	lsr r2, r2, #0x1b
	add r2, r1, r2
	asr r1, r2, #5
	ldr r2, [r5, #4]
	cmp r0, r2
	bne _02254B56
	ldr r2, [r5, #8]
	cmp r1, r2
	beq _02254B5C
_02254B56:
	str r0, [r5, #4]
	str r1, [r5, #8]
	mov r6, #1
_02254B5C:
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov43_02254AF8

	thumb_func_start ov43_02254B60
ov43_02254B60: ; 0x02254B60
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, r1, #0
	bl ov20_02252C40
	bl Save_VarsFlags_Get
	add r6, r0, #0
	mov r4, #0
_02254B72:
	add r0, r6, #0
	add r1, r4, #0
	bl sub_0205F524
	add r1, r5, #0
	add r1, #0x98
	add r4, r4, #1
	add r5, r5, #4
	str r0, [r1]
	cmp r4, #4
	blt _02254B72
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov43_02254B60

	thumb_func_start ov43_02254B8C
ov43_02254B8C: ; 0x02254B8C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r1, #0x16
	add r6, r0, #0
	mov r0, #8
	lsl r1, r1, #4
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254BC6
	add r0, #8
	mov r1, #4
	bl ov20_022536F4
	str r5, [r4]
	bl ov20_02252D34
	str r0, [r4, #4]
	bl ov20_02252D24
	str r0, [r4, #0x20]
	add r5, #0x8c
	mov r0, #0x15
	ldr r1, [r5]
	lsl r0, r0, #4
	str r1, [r4, r0]
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254BC6:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov43_02254B8C

	thumb_func_start ov43_02254BCC
ov43_02254BCC: ; 0x02254BCC
	push {r3, lr}
	cmp r0, #0
	beq _02254BD6
	bl FreeToHeap
_02254BD6:
	pop {r3, pc}
	thumb_func_end ov43_02254BCC

	thumb_func_start ov43_02254BD8
ov43_02254BD8: ; 0x02254BD8
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254BF8 ; =ov43_022551BC
	ldr r3, [r2]
	bl ov20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254BF8: .word ov43_022551BC
	thumb_func_end ov43_02254BD8

	thumb_func_start ov43_02254BFC
ov43_02254BFC: ; 0x02254BFC
	ldr r3, _02254C04 ; =ov20_02253794
	add r0, #8
	bx r3
	nop
_02254C04: .word ov20_02253794
	thumb_func_end ov43_02254BFC

	thumb_func_start ov43_02254C08
ov43_02254C08: ; 0x02254C08
	ldr r3, _02254C10 ; =ov20_022537B8
	add r0, #8
	bx r3
	nop
_02254C10: .word ov20_022537B8
	thumb_func_end ov43_02254C08

	thumb_func_start ov43_02254C14
ov43_02254C14: ; 0x02254C14
	push {r4, lr}
	add r4, r0, #0
	bl ov20_022538A0
	add r0, #8
	add r1, r4, #0
	bl ov20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov43_02254C14

	thumb_func_start ov43_02254C28
ov43_02254C28: ; 0x02254C28
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r6, r1, #0
	add r0, r6, #0
	bl ov20_022538A0
	add r5, r0, #0
	ldr r0, _02254CC0 ; =0x0400104C
	mov r3, #0
	strb r3, [r0]
	strb r3, [r0, #1]
	ldr r0, [r5, #4]
	ldr r2, _02254CC4 ; =ov43_022551A0
	mov r1, #6
	bl InitBgFromTemplate
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x75
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x74
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	add r1, r0, #0
	bl ov20_02252D7C
	add r0, r5, #0
	lsr r1, r4, #5
	bl ov43_02254CD0
	ldr r0, [r5, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r1, _02254CC8 ; =0x04001000
	ldr r0, _02254CCC ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp, #0x10]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #4
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r5, #0
	bl ov43_02254E78
	add r0, r6, #0
	bl ov43_02254C14
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02254CC0: .word 0x0400104C
_02254CC4: .word ov43_022551A0
_02254CC8: .word 0x04001000
_02254CCC: .word 0xFFFFE0FF
	thumb_func_end ov43_02254C28

	thumb_func_start ov43_02254CD0
ov43_02254CD0: ; 0x02254CD0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x24
	add r4, r1, #0
	mov r1, #0x66
	add r5, r0, #0
	mov r0, #0x1a
	lsl r1, r1, #2
	mov r2, #0
	mov r3, #8
	bl ReadMsgData_NewNarc_NewString
	add r6, r0, #0
	beq _02254D44
	mov r0, #0x14
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	add r1, sp, #0x14
	mov r2, #6
	mov r3, #0x12
	bl AddWindowParameterized
	add r0, sp, #0x14
	mov r1, #4
	bl FillWindowPixelBuffer
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02254D48 ; =0x00010104
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, sp, #0x14
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, sp, #0x14
	bl PutWindowTilemap
	add r0, sp, #0x14
	bl CopyWindowPixelsToVram_TextMode
	add r0, sp, #0x14
	bl RemoveWindow
	add r0, r6, #0
	bl String_Delete
_02254D44:
	add sp, #0x24
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02254D48: .word 0x00010104
	thumb_func_end ov43_02254CD0

	thumb_func_start ov43_02254D4C
ov43_02254D4C: ; 0x02254D4C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538AC
	cmp r0, #0
	beq _02254D68
	cmp r0, #1
	beq _02254D78
	pop {r3, r4, r5, pc}
_02254D68:
	mov r0, #0x57
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r5, #0
	bl ov20_022538B0
	pop {r3, r4, r5, pc}
_02254D78:
	add r0, r4, #0
	mov r1, #2
	bl ov43_02254BFC
	cmp r0, #0
	beq _02254DA0
	add r0, r4, #0
	bl ov43_02255000
	ldr r0, _02254DA4 ; =0x0400104C
	mov r1, #0
	strb r1, [r0]
	strb r1, [r0, #1]
	ldr r0, [r4, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r5, #0
	bl ov43_02254C14
_02254DA0:
	pop {r3, r4, r5, pc}
	nop
_02254DA4: .word 0x0400104C
	thumb_func_end ov43_02254D4C

	thumb_func_start ov43_02254DA8
ov43_02254DA8: ; 0x02254DA8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	add r0, r5, #0
	bl ov20_022538AC
	cmp r0, #0
	beq _02254DCE
	cmp r0, #1
	beq _02254E02
	cmp r0, #2
	beq _02254E10
	pop {r3, r4, r5, pc}
_02254DCE:
	mov r1, #0x55
	mov r0, #6
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r2, #0
	add r0, r1, #4
	str r2, [r4, r0]
	add r0, r1, #0
	add r0, #8
	str r2, [r4, r0]
	ldr r2, [r4, r1]
	lsl r0, r2, #4
	orr r0, r2
	ldr r2, _02254E70 ; =0x0400104C
	strb r0, [r2]
	ldr r1, [r4, r1]
	lsl r0, r1, #4
	orr r0, r1
	strb r0, [r2, #1]
	ldr r0, _02254E74 ; =0x00000678
	bl Poketch_PlaySoundEffect
	add r0, r5, #0
	bl ov20_022538B0
	pop {r3, r4, r5, pc}
_02254E02:
	add r0, r4, #0
	bl ov43_02254F9C
	add r0, r5, #0
	bl ov20_022538B0
	pop {r3, r4, r5, pc}
_02254E10:
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _02254E22
	add r0, r5, #0
	bl ov43_02254C14
	pop {r3, r4, r5, pc}
_02254E22:
	sub r1, r0, #4
	ldr r1, [r4, r1]
	add r2, r1, #1
	sub r1, r0, #4
	str r2, [r4, r1]
	ldr r1, [r4, r1]
	cmp r1, #3
	blt _02254E6E
	mov r2, #0
	sub r1, r0, #4
	str r2, [r4, r1]
	add r1, r0, #0
	sub r1, #8
	ldr r1, [r4, r1]
	sub r2, r1, #1
	add r1, r0, #0
	sub r1, #8
	str r2, [r4, r1]
	add r1, r0, #0
	sub r1, #8
	ldr r2, [r4, r1]
	lsl r1, r2, #4
	orr r2, r1
	ldr r1, _02254E70 ; =0x0400104C
	strb r2, [r1]
	add r2, r0, #0
	sub r2, #8
	ldr r3, [r4, r2]
	sub r0, #8
	lsl r2, r3, #4
	orr r2, r3
	strb r2, [r1, #1]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02254E6E
	add r0, r5, #0
	bl ov43_02254C14
_02254E6E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254E70: .word 0x0400104C
_02254E74: .word 0x00000678
	thumb_func_end ov43_02254DA8

	thumb_func_start ov43_02254E78
ov43_02254E78: ; 0x02254E78
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r6, r0, #0
	ldr r7, [r6]
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x78
	bl GfGfxLoader_LoadWholePalette
	mov r0, #8
	str r0, [sp]
	mov r0, #0x4e
	lsl r0, r0, #2
	add r0, r6, r0
	mov r1, #0xc
	mov r2, #0x76
	mov r3, #0x77
	bl ov20_02253FBC
	mov r2, #0
	add r0, sp, #0xc
	strb r2, [r0, #0x12]
	mov r1, #2
	strb r1, [r0, #0x13]
	strb r2, [r0, #0x15]
	ldr r0, [r7]
	ldr r1, [r7, #4]
	add r2, sp, #0x10
	add r3, sp, #0xc
	bl ov20_02254420
	ldr r0, [sp, #0x10]
	mov r2, #0x4e
	lsl r0, r0, #0xc
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xc]
	lsl r2, r2, #2
	lsl r0, r0, #0xc
	str r0, [sp, #0x18]
	mov r1, #0
	add r0, sp, #0xc
	strb r1, [r0, #0x14]
	strh r1, [r0, #0x10]
	ldr r0, [r6, #0x20]
	add r1, sp, #0x14
	add r2, r6, r2
	bl ov20_02253E74
	mov r1, #1
	str r0, [r6, #0x24]
	bl ov20_02253FAC
	mov r1, #1
	add r0, sp, #0xc
	strb r1, [r0, #0x14]
	mov r1, #7
	strh r1, [r0, #0x10]
	mov r5, #0
	str r5, [sp, #0x14]
	str r5, [sp, #0x18]
	add r4, r6, #0
_02254EFC:
	mov r2, #0x4e
	lsl r2, r2, #2
	ldr r0, [r6, #0x20]
	add r1, sp, #0x14
	add r2, r6, r2
	bl ov20_02253E74
	mov r1, #1
	str r0, [r4, #0x28]
	bl ov20_02253FAC
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #0x40
	blt _02254EFC
	add r0, r6, #0
	bl ov43_02254F9C
	mov r5, #0
	add r4, r6, #0
_02254F24:
	add r0, r5, #0
	add r1, sp, #0x10
	add r2, sp, #0xc
	bl ov20_02254460
	ldr r0, [sp, #0x10]
	mov r1, #2
	lsl r0, r0, #0xc
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xc]
	mov r2, #0x4e
	lsl r0, r0, #0xc
	str r0, [sp, #0x18]
	add r0, sp, #0xc
	strb r1, [r0, #0x14]
	add r1, r5, #0
	add r1, #0xe
	strh r1, [r0, #0x10]
	lsl r2, r2, #2
	ldr r0, [r6, #0x20]
	add r1, sp, #0x14
	add r2, r6, r2
	bl ov20_02253E74
	mov r1, #0x4a
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #1
	bl ov20_02253FAC
	add r0, r7, #0
	add r0, #0x94
	ldr r0, [r0]
	cmp r0, #0
	bne _02254F7A
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl ov20_02253F78
_02254F7A:
	add r5, r5, #1
	add r4, r4, #4
	add r7, r7, #4
	cmp r5, #4
	blt _02254F24
	ldr r0, _02254F98 ; =ov43_02255078
	add r1, r6, #0
	mov r2, #3
	bl SysTask_CreateOnMainQueue
	mov r1, #0x53
	lsl r1, r1, #2
	str r0, [r6, r1]
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254F98: .word ov43_02255078
	thumb_func_end ov43_02254E78

	thumb_func_start ov43_02254F9C
ov43_02254F9C: ; 0x02254F9C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	ldr r1, [r7]
	mov r4, #0
	ldr r0, [r1, #8]
	cmp r0, #0
	ble _02254FE2
	add r6, r4, #0
	add r5, r7, #0
_02254FB0:
	add r1, r1, r6
	ldrb r0, [r1, #0xc]
	ldrb r1, [r1, #0xd]
	add r2, sp, #4
	add r3, sp, #0
	bl ov20_02254420
	ldr r1, [sp, #4]
	ldr r2, [sp]
	ldr r0, [r5, #0x28]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl ov20_02253F64
	ldr r0, [r5, #0x28]
	mov r1, #0
	bl ov20_02253F78
	ldr r1, [r7]
	add r4, r4, #1
	ldr r0, [r1, #8]
	add r6, r6, #2
	add r5, r5, #4
	cmp r4, r0
	blt _02254FB0
_02254FE2:
	cmp r4, #0x40
	bge _02254FFC
	lsl r0, r4, #2
	add r5, r7, r0
	mov r6, #1
_02254FEC:
	ldr r0, [r5, #0x28]
	add r1, r6, #0
	bl ov20_02253F78
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x40
	blt _02254FEC
_02254FFC:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov43_02254F9C

	thumb_func_start ov43_02255000
ov43_02255000: ; 0x02255000
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0225501A
	bl SysTask_Destroy
	mov r0, #0x53
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
_0225501A:
	mov r6, #0
	add r4, r5, #0
	add r7, r6, #0
_02255020:
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _02255036
	ldr r0, [r5, #0x20]
	bl ov20_02253F14
	mov r0, #0x4a
	lsl r0, r0, #2
	str r7, [r4, r0]
_02255036:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _02255020
	mov r6, #0
	add r4, r5, #0
	add r7, r6, #0
_02255044:
	ldr r1, [r4, #0x28]
	cmp r1, #0
	beq _02255052
	ldr r0, [r5, #0x20]
	bl ov20_02253F14
	str r7, [r4, #0x28]
_02255052:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #0x40
	blt _02255044
	ldr r1, [r5, #0x24]
	cmp r1, #0
	beq _0225506A
	ldr r0, [r5, #0x20]
	bl ov20_02253F14
	mov r0, #0
	str r0, [r5, #0x24]
_0225506A:
	mov r0, #0x4e
	lsl r0, r0, #2
	add r0, r5, r0
	bl ov20_02254014
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end ov43_02255000

	thumb_func_start ov43_02255078
ov43_02255078: ; 0x02255078
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	ldr r1, [r4]
	add r0, r1, #0
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #0
	beq _022550A2
	ldmia r1!, {r0, r1}
	add r2, sp, #4
	add r3, sp, #0
	bl ov20_02254420
	ldr r1, [sp, #4]
	ldr r2, [sp]
	ldr r0, [r4, #0x24]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl ov20_02253F64
_022550A2:
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov43_02255078

	.section .rodata

	.global ov43_022550A8
ov43_022550A8: ; 0x022550A8
	.word ov43_0225498C, ov43_022549D8, ov43_02254A50

	.global ov43_022550B4
ov43_022550B4: ; 0x022550B4
	.byte 0x05, 0x14
	.byte 0x05, 0x14
	.byte 0x06, 0x14
	.byte 0x06, 0x14
	.byte 0x06, 0x13
	.byte 0x06, 0x13
	.byte 0x07, 0x11
	.byte 0x07, 0x11
	.byte 0x07, 0x11
	.byte 0x07, 0x11
	.byte 0x05, 0x12
	.byte 0x05, 0x12
	.byte 0x05, 0x12
	.byte 0x05, 0x12
	.byte 0x08, 0x10
	.byte 0x08, 0x10
	.byte 0x08, 0x10
	.byte 0x08, 0x10
	.byte 0x09, 0x13
	.byte 0x09, 0x13
	.byte 0x09, 0x15
	.byte 0x09, 0x15
	.byte 0x09, 0x16
	.byte 0x09, 0x16
	.byte 0x09, 0x16
	.byte 0x09, 0x16
	.byte 0x0D, 0x16
	.byte 0x0D, 0x16
	.byte 0x0D, 0x16
	.byte 0x0D, 0x16
	.byte 0x10, 0x16
	.byte 0x10, 0x16
	.byte 0x11, 0x15
	.byte 0x11, 0x15
	.byte 0x11, 0x14
	.byte 0x11, 0x14
	.byte 0x11, 0x14
	.byte 0x11, 0x14
	.byte 0x11, 0x13
	.byte 0x11, 0x13
	.byte 0x11, 0x13
	.byte 0x11, 0x13
	.byte 0x0F, 0x10
	.byte 0x0F, 0x10
	.byte 0x0F, 0x10
	.byte 0x0F, 0x10
	.byte 0x0D, 0x10
	.byte 0x0D, 0x10
	.byte 0x0D, 0x10
	.byte 0x0D, 0x10
	.byte 0x0E, 0x18
	.byte 0x0E, 0x18
	.byte 0x0E, 0x19
	.byte 0x0E, 0x19
	.byte 0x11, 0x1A
	.byte 0x11, 0x1A
	.byte 0x11, 0x1A
	.byte 0x11, 0x1A
	.byte 0x13, 0x19
	.byte 0x13, 0x19
	.byte 0x13, 0x19
	.byte 0x13, 0x19
	.byte 0x14, 0x19
	.byte 0x14, 0x19
	.byte 0x14, 0x19
	.byte 0x14, 0x19
	.byte 0x16, 0x14
	.byte 0x16, 0x14
	.byte 0x16, 0x14
	.byte 0x16, 0x14
	.byte 0x13, 0x12
	.byte 0x13, 0x12
	.byte 0x14, 0x12
	.byte 0x14, 0x12
	.byte 0x02, 0x17
	.byte 0x02, 0x17
	.byte 0x02, 0x17
	.byte 0x02, 0x17
	.byte 0x08, 0x1C
	.byte 0x08, 0x1C
	.byte 0x08, 0x1C
	.byte 0x08, 0x1C
	.byte 0x17, 0x18
	.byte 0x17, 0x18
	.byte 0x17, 0x18
	.byte 0x17, 0x18
	.byte 0x1C, 0x10
	.byte 0x1C, 0x10
	.byte 0x1C, 0x10
	.byte 0x1C, 0x10
	.byte 0x13, 0x0D
	.byte 0x14, 0x0D
	.byte 0x14, 0x0D
	.byte 0x14, 0x0D
	.byte 0x13, 0x0A
	.byte 0x13, 0x0A
	.byte 0x13, 0x0A
	.byte 0x13, 0x0A
	.byte 0x15, 0x0A
	.byte 0x15, 0x0A
	.byte 0x15, 0x0A
	.byte 0x15, 0x0A
	.byte 0x18, 0x0C
	.byte 0x18, 0x0C
	.byte 0x18, 0x0C
	.byte 0x18, 0x0C
	.byte 0x19, 0x0D
	.byte 0x19, 0x0D
	.byte 0x19, 0x0D
	.byte 0x19, 0x0D
	.byte 0x19, 0x0E
	.byte 0x19, 0x0E
	.byte 0x19, 0x0E
	.byte 0x19, 0x0E
	.byte 0x15, 0x0D
	.byte 0x15, 0x0D
	.byte 0x15, 0x0D
	.byte 0x15, 0x0D

	.global ov43_022551A0
ov43_022551A0: ; 0x022551A0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00

	.global ov43_022551BC
ov43_022551BC: ; 0x022551BC
	.word 0x00, ov43_02254C28, 0x00
	.word 0x01, ov43_02254D4C, 0x00
	.word 0x02, ov43_02254DA8, 0x00
	.word 0x00, 0x00000000, 0x00
