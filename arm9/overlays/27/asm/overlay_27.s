	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov27_02254854
ov27_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x7c
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl ov27_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =ov27_022548F8
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
_02254898: .word ov27_022548F8
	thumb_func_end ov27_02254854

	thumb_func_start ov27_0225489C
ov27_0225489C: ; 0x0225489C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r0, #0x74
	add r1, r5, #4
	bl ov27_02254AF0
	cmp r0, #0
	beq _022548E0
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	add r0, r4, #0
	bl ov20_02252C40
	bl SaveArray_Party_Get
	add r1, r0, #0
	add r0, r5, #4
	bl ov27_02254A48
	add r0, r5, #0
	mov r1, #0
	add r0, #0x68
	strh r1, [r0]
	add r0, r5, #0
	add r0, #0x6a
	strh r1, [r0]
	str r1, [r5, #0x6c]
	str r1, [r5, #0x70]
	str r4, [r5, #0x78]
	mov r0, #1
	pop {r3, r4, r5, pc}
_022548E0:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end ov27_0225489C

	thumb_func_start ov27_022548E4
ov27_022548E4: ; 0x022548E4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x74]
	bl ov27_02254B88
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov27_022548E4

	thumb_func_start ov27_022548F8
ov27_022548F8: ; 0x022548F8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhs _02254924
	lsl r2, r1, #2
	ldr r1, _02254928 ; =ov27_0225533C
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254924
	add r0, r4, #0
	bl ov27_022548E4
	add r0, r5, #0
	bl sub_0200CAB4
	ldr r0, [r4, #0x78]
	bl ov20_022529A0
_02254924:
	pop {r3, r4, r5, pc}
	nop
_02254928: .word ov27_0225533C
	thumb_func_end ov27_022548F8

	thumb_func_start ov27_0225492C
ov27_0225492C: ; 0x0225492C
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end ov27_0225492C

	thumb_func_start ov27_02254934
ov27_02254934: ; 0x02254934
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _0225493C
	b _0225493E
_0225493C:
	mov r1, #2
_0225493E:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end ov27_02254934

	thumb_func_start ov27_02254948
ov27_02254948: ; 0x02254948
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254958
	cmp r0, #1
	beq _02254968
	b _02254982
_02254958:
	ldr r0, [r4, #0x74]
	mov r1, #0
	bl ov27_02254BB8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254982
_02254968:
	ldr r0, [r4, #0x74]
	mov r1, #0
	bl ov27_02254BDC
	cmp r0, #0
	beq _02254982
	ldr r0, [r4, #0x78]
	bl ov20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl ov27_02254934
_02254982:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov27_02254948

	thumb_func_start ov27_02254988
ov27_02254988: ; 0x02254988
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _0225499C
	mov r1, #2
	bl ov27_02254934
	mov r0, #0
	pop {r4, pc}
_0225499C:
	ldr r0, [r4, #0x74]
	mov r1, #2
	bl ov27_02254BDC
	cmp r0, #0
	beq _02254A06
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x6c
	add r1, #0x70
	bl TouchScreen_GetTapState
	add r1, r4, #0
	add r1, #0x68
	strh r0, [r1]
	add r0, r4, #0
	add r0, #0x68
	ldrh r0, [r0]
	cmp r0, #0
	beq _02254A06
	bl sub_02020AA4
	add r1, r4, #0
	add r1, #0x6a
	strh r0, [r1]
	add r0, r4, #0
	add r0, #0x6a
	ldrh r0, [r0]
	cmp r0, #0
	beq _02254A02
	ldr r0, [r4, #0x6c]
	ldr r1, [r4, #0x70]
	ldr r2, [r4, #4]
	bl ov27_022551F4
	ldr r1, [r4, #4]
	cmp r0, r1
	blo _02254A02
	ldr r0, [r4, #0x78]
	bl ov20_02252C40
	bl SaveArray_Party_Get
	add r1, r0, #0
	add r0, r4, #4
	bl ov27_02254A48
	ldr r0, [r4, #0x74]
	mov r1, #2
	bl ov27_02254BB8
_02254A02:
	mov r0, #0
	pop {r4, pc}
_02254A06:
	mov r0, #0
	str r0, [r4, #0x6c]
	str r0, [r4, #0x70]
	add r4, #0x6a
	strh r0, [r4]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov27_02254988

	thumb_func_start ov27_02254A14
ov27_02254A14: ; 0x02254A14
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A24
	cmp r0, #1
	beq _02254A34
	b _02254A42
_02254A24:
	ldr r0, [r4, #0x74]
	mov r1, #1
	bl ov27_02254BB8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A42
_02254A34:
	ldr r0, [r4, #0x74]
	bl ov27_02254BE8
	cmp r0, #0
	beq _02254A42
	mov r0, #1
	pop {r4, pc}
_02254A42:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov27_02254A14

	thumb_func_start ov27_02254A48
ov27_02254A48: ; 0x02254A48
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	add r0, r1, #0
	str r1, [sp, #4]
	bl Party_GetCount
	ldr r1, [sp]
	mov r6, #0
	str r0, [r1]
	cmp r0, #0
	ble _02254AEC
	add r5, r1, #0
_02254A62:
	ldr r0, [sp, #4]
	add r1, r6, #0
	bl Party_GetMonByIndex
	add r4, r0, #0
	bl AcquireMonLock
	add r7, r0, #0
	add r0, r4, #0
	bl sub_0206B688
	str r0, [r5, #4]
	add r0, r4, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	strh r0, [r5, #8]
	add r0, r4, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	strh r0, [r5, #0xa]
	add r0, r4, #0
	mov r1, #0xa3
	mov r2, #0
	bl GetMonData
	strh r0, [r5, #0xc]
	add r0, r4, #0
	mov r1, #6
	mov r2, #0
	bl GetMonData
	strh r0, [r5, #0xe]
	add r0, r4, #0
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02254ABC
	mov r0, #1
	b _02254ABE
_02254ABC:
	mov r0, #0
_02254ABE:
	strh r0, [r5, #0x10]
	add r0, r4, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	strb r0, [r5, #0x12]
	add r0, r4, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	strb r0, [r5, #0x13]
	add r0, r4, #0
	add r1, r7, #0
	bl ReleaseMonLock
	ldr r0, [sp]
	add r6, r6, #1
	ldr r0, [r0]
	add r5, #0x10
	cmp r6, r0
	blt _02254A62
_02254AEC:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov27_02254A48

	thumb_func_start ov27_02254AF0
ov27_02254AF0: ; 0x02254AF0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	mov r1, #0xe3
	str r0, [sp, #4]
	mov r0, #8
	lsl r1, r1, #2
	bl AllocFromHeap
	str r0, [sp, #8]
	cmp r0, #0
	beq _02254B82
	add r0, #0xc
	mov r1, #8
	bl ov20_022536F4
	ldr r0, [sp, #8]
	str r4, [r0]
	bl ov20_02252D34
	ldr r1, [sp, #8]
	str r0, [r1, #4]
	bl ov20_02252D24
	ldr r1, [sp, #8]
	mov r6, #0
	str r0, [r1, #8]
	add r0, r1, #0
	str r6, [r0, #0x38]
	add r0, #0xf4
	add r4, r1, #0
	str r6, [r0]
	add r4, #0x3c
	add r5, r1, #0
	add r7, r6, #0
_02254B36:
	add r0, r4, #0
	bl InitWindow
	add r0, r5, #0
	add r0, #0x9c
	str r7, [r0]
	add r0, r5, #0
	add r0, #0xb4
	add r6, r6, #1
	str r7, [r0]
	add r4, #0x10
	add r5, r5, #4
	cmp r6, #6
	blt _02254B36
	mov r0, #8
	str r0, [sp]
	ldr r0, [sp, #8]
	mov r1, #0xc
	add r0, #0xcc
	mov r2, #5
	mov r3, #6
	bl ov20_02253FBC
	mov r0, #8
	str r0, [sp]
	ldr r0, [sp, #8]
	mov r1, #0xc
	add r0, #0xe0
	mov r2, #0x6b
	mov r3, #0x6c
	bl ov20_02253FBC
	ldr r1, [sp, #8]
	ldr r0, [sp, #4]
	add sp, #0xc
	str r1, [r0]
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02254B82:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end ov27_02254AF0

	thumb_func_start ov27_02254B88
ov27_02254B88: ; 0x02254B88
	push {r4, lr}
	add r4, r0, #0
	beq _02254BB6
	bl ov27_02255250
	add r0, r4, #0
	add r0, #0xcc
	bl ov20_02254014
	add r0, r4, #0
	add r0, #0xe0
	bl ov20_02254014
	add r0, r4, #0
	add r0, #0xf4
	ldr r0, [r0]
	cmp r0, #0
	beq _02254BB0
	bl sub_0200CAB4
_02254BB0:
	add r0, r4, #0
	bl FreeToHeap
_02254BB6:
	pop {r4, pc}
	thumb_func_end ov27_02254B88

	thumb_func_start ov27_02254BB8
ov27_02254BB8: ; 0x02254BB8
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #0xc
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254BD8 ; =ov27_02255394
	ldr r3, [r2]
	bl ov20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254BD8: .word ov27_02255394
	thumb_func_end ov27_02254BB8

	thumb_func_start ov27_02254BDC
ov27_02254BDC: ; 0x02254BDC
	ldr r3, _02254BE4 ; =ov20_02253794
	add r0, #0xc
	bx r3
	nop
_02254BE4: .word ov20_02253794
	thumb_func_end ov27_02254BDC

	thumb_func_start ov27_02254BE8
ov27_02254BE8: ; 0x02254BE8
	ldr r3, _02254BF0 ; =ov20_022537B8
	add r0, #0xc
	bx r3
	nop
_02254BF0: .word ov20_022537B8
	thumb_func_end ov27_02254BE8

	thumb_func_start ov27_02254BF4
ov27_02254BF4: ; 0x02254BF4
	push {r4, lr}
	add r4, r0, #0
	bl ov20_022538A0
	add r0, #0xc
	add r1, r4, #0
	bl ov20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov27_02254BF4

	thumb_func_start ov27_02254C08
ov27_02254C08: ; 0x02254C08
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r6, r1, #0
	add r0, r6, #0
	bl ov20_022538A0
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r2, _02254CBC ; =ov27_02255378
	mov r1, #6
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0xc
	mov r1, #0x6a
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	mov r3, #0
	lsr r5, r0, #5
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #5
	bl FillBgTilemapRect
	mov r0, #0
	add r1, r0, #0
	bl ov20_02252D7C
	str r5, [r4, #0x34]
	ldr r1, [r4]
	add r0, r4, #0
	add r2, r5, #0
	bl ov27_02254CC8
	ldr r0, [r4, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	mov r0, #0xf
	mov r1, #1
	bl ov20_0225396C
	mov r0, #2
	bl ov20_022539C4
	ldr r1, [r4]
	add r0, r4, #0
	bl ov27_02254F18
	ldr r1, [r4]
	add r0, r4, #0
	bl ov27_02254FAC
	add r0, r4, #0
	bl ov27_022550C8
	ldr r1, _02254CC0 ; =0x04001000
	ldr r0, _02254CC4 ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp, #0x10]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #0x14
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r6, #0
	bl ov27_02254BF4
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_02254CBC: .word ov27_02255378
_02254CC0: .word 0x04001000
_02254CC4: .word 0xFFFFE0FF
	thumb_func_end ov27_02254C08

	thumb_func_start ov27_02254CC8
ov27_02254CC8: ; 0x02254CC8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x20]
	add r0, r1, #0
	str r1, [sp, #0x18]
	ldr r1, [r0]
	str r2, [sp, #0x1c]
	cmp r1, #0
	ble _02254D54
	ldr r4, [sp, #0x14]
	ldr r7, [sp, #0x20]
	ldr r5, _02254D5C ; =ov27_02255360
	ldr r6, [sp, #0x18]
	add r4, #0x3c
_02254CE8:
	add r0, r4, #0
	bl InitWindow
	ldrh r0, [r5, #2]
	add r1, r4, #0
	mov r2, #6
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x1c]
	add r0, r0, r7
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldrh r3, [r5]
	ldr r0, [sp, #0x14]
	lsl r3, r3, #0x18
	ldr r0, [r0, #4]
	lsr r3, r3, #0x18
	bl AddWindowParameterized
	add r0, r4, #0
	bl PutWindowTilemap
	ldr r1, [sp, #0x14]
	add r0, r4, #0
	bl ov27_02254D60
	ldrh r0, [r6, #0xa]
	ldrh r1, [r6, #0xc]
	bl ov27_02254EEC
	add r1, r0, #0
	add r0, r4, #0
	bl ov27_02254EAC
	ldr r0, [sp, #0x20]
	add r4, #0x10
	add r0, r0, #1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	add r7, #8
	ldr r1, [r0]
	ldr r0, [sp, #0x20]
	add r5, r5, #4
	add r6, #0x10
	cmp r0, r1
	blt _02254CE8
_02254D54:
	ldr r0, [sp, #0x14]
	str r1, [r0, #0x38]
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254D5C: .word ov27_02255360
	thumb_func_end ov27_02254CC8

	thumb_func_start ov27_02254D60
ov27_02254D60: ; 0x02254D60
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldrb r0, [r5, #6]
	add r4, r1, #0
	mov r2, #1
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	str r2, [sp, #4]
	str r2, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r3, [r5, #5]
	ldr r0, [r4, #4]
	mov r1, #6
	sub r3, r3, #1
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	ldrb r0, [r5, #6]
	mov r1, #6
	mov r2, #2
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldrb r0, [r5, #7]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r3, [r5, #5]
	ldr r0, [r4, #4]
	bl FillBgTilemapRect
	ldrb r0, [r5, #6]
	ldr r2, _02254E98 ; =0x00000401
	mov r1, #6
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r6, [r5, #5]
	ldrb r3, [r5, #7]
	ldr r0, [r4, #4]
	add r3, r6, r3
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	ldrb r0, [r5, #6]
	mov r1, #6
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldrb r0, [r5, #8]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r3, [r5, #5]
	ldr r0, [r4, #4]
	sub r3, r3, #1
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	ldrb r0, [r5, #6]
	ldr r2, _02254E9C ; =0x00000406
	mov r1, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldrb r0, [r5, #8]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r6, [r5, #5]
	ldrb r3, [r5, #7]
	ldr r0, [r4, #4]
	add r3, r6, r3
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	ldrb r1, [r5, #6]
	ldrb r0, [r5, #8]
	ldr r2, _02254EA0 ; =0x00000801
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r3, [r5, #5]
	ldr r0, [r4, #4]
	mov r1, #6
	sub r3, r3, #1
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	ldrb r1, [r5, #6]
	ldrb r0, [r5, #8]
	ldr r2, _02254EA4 ; =0x00000802
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldrb r0, [r5, #7]
	mov r1, #6
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r3, [r5, #5]
	ldr r0, [r4, #4]
	bl FillBgTilemapRect
	ldrb r1, [r5, #6]
	ldrb r0, [r5, #8]
	ldr r2, _02254EA8 ; =0x00000C01
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [r4, #4]
	ldrb r4, [r5, #5]
	ldrb r3, [r5, #7]
	mov r1, #6
	add r3, r4, r3
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_02254E98: .word 0x00000401
_02254E9C: .word 0x00000406
_02254EA0: .word 0x00000801
_02254EA4: .word 0x00000802
_02254EA8: .word 0x00000C01
	thumb_func_end ov27_02254D60

	thumb_func_start ov27_02254EAC
ov27_02254EAC: ; 0x02254EAC
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	mov r1, #0x40
	str r1, [sp]
	mov r1, #8
	mov r2, #0
	str r1, [sp, #4]
	mov r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl FillWindowPixelRect
	cmp r4, #0
	beq _02254EE0
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	mov r0, #8
	mov r2, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0xf
	add r3, r2, #0
	bl FillWindowPixelRect
_02254EE0:
	add r0, r5, #0
	bl CopyWindowPixelsToVram_TextMode
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov27_02254EAC

	thumb_func_start ov27_02254EEC
ov27_02254EEC: ; 0x02254EEC
	push {r3, lr}
	cmp r0, #0
	bne _02254EF6
	mov r0, #0
	pop {r3, pc}
_02254EF6:
	cmp r0, r1
	bne _02254EFE
	mov r0, #0x40
	pop {r3, pc}
_02254EFE:
	lsl r0, r0, #0xc
	bl _u32_div_f
	lsl r0, r0, #5
	lsr r0, r0, #0xc
	bne _02254F0E
	mov r0, #1
	b _02254F14
_02254F0E:
	cmp r0, #0x20
	bne _02254F14
	mov r0, #0x1f
_02254F14:
	lsl r0, r0, #1
	pop {r3, pc}
	thumb_func_end ov27_02254EEC

	thumb_func_start ov27_02254F18
ov27_02254F18: ; 0x02254F18
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x6d
	bl GfGfxLoader_LoadWholePalette
	mov r4, #0
	add r0, sp, #0x18
	strb r4, [r0, #0xa]
	mov r1, #2
	strb r1, [r0, #0xb]
	strb r4, [r0, #0xc]
	strb r4, [r0, #0xd]
	ldr r0, [sp, #0x10]
	ldr r0, [r0]
	cmp r0, #0
	ble _02254FA2
	ldr r7, [sp, #0xc]
	ldr r6, [sp, #0x10]
	add r0, r7, #0
	str r0, [sp, #0x14]
	add r0, #0xe0
	ldr r5, _02254FA8 ; =ov27_02255348
	str r0, [sp, #0x14]
_02254F58:
	ldrh r0, [r6, #0xe]
	cmp r0, #0
	beq _02254F92
	bl ItemIdIsMail
	cmp r0, #0
	beq _02254F6A
	mov r1, #1
	b _02254F6C
_02254F6A:
	mov r1, #0
_02254F6C:
	add r0, sp, #0x18
	strh r1, [r0, #8]
	ldrh r0, [r5]
	ldr r2, [sp, #0x14]
	add r1, sp, #0x18
	add r0, #0x1c
	lsl r0, r0, #0xc
	str r0, [sp, #0x18]
	ldrh r0, [r5, #2]
	add r0, #0x15
	lsl r0, r0, #0xc
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #8]
	bl ov20_02253E74
	add r1, r7, #0
	add r1, #0xb4
	str r0, [r1]
_02254F92:
	ldr r0, [sp, #0x10]
	add r4, r4, #1
	ldr r0, [r0]
	add r6, #0x10
	add r5, r5, #4
	add r7, r7, #4
	cmp r4, r0
	blt _02254F58
_02254FA2:
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254FA8: .word ov27_02255348
	thumb_func_end ov27_02254F18

	thumb_func_start ov27_02254FAC
ov27_02254FAC: ; 0x02254FAC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x13
	mov r1, #8
	bl NARC_New
	str r0, [sp, #0x14]
	cmp r0, #0
	beq _022550C0
	mov r0, #0
	add r1, sp, #0x20
	strh r0, [r1, #0xc]
	str r0, [sp, #0x10]
	strb r0, [r1, #0xe]
	mov r0, #2
	strb r0, [r1, #0xf]
	mov r7, #1
	strb r7, [r1, #0x10]
	ldr r0, [sp, #8]
	strb r7, [r1, #0x11]
	ldr r0, [r0]
	cmp r0, #0
	ble _022550BA
	ldr r5, [sp, #4]
	mov r0, #8
	mov r1, #0x43
	str r0, [sp, #0xc]
	lsl r1, r1, #2
	add r0, r5, #0
	add r0, r0, r1
	str r0, [sp, #0x18]
	add r0, r5, #0
	str r0, [sp, #0x1c]
	add r0, #0xcc
	ldr r4, [sp, #8]
	ldr r6, _022550C4 ; =ov27_02255348
	add r7, #0xff
	str r0, [sp, #0x1c]
_02254FFC:
	ldr r0, [sp, #0x18]
	mov r3, #0xa
	str r0, [sp]
	ldr r0, [sp, #0x14]
	ldr r1, [r4, #4]
	mov r2, #0
	lsl r3, r3, #6
	bl NARC_ReadFromMember
	ldr r0, [sp, #0x18]
	add r1, sp, #0x20
	bl NNS_G2dGetUnpackedCharacterData
	ldr r0, [sp, #0x20]
	mov r1, #2
	ldr r0, [r0, #0x14]
	lsl r1, r1, #8
	bl DC_FlushRange
	ldr r0, [sp, #0x20]
	mov r2, #2
	ldr r0, [r0, #0x14]
	add r1, r7, #0
	lsl r2, r2, #8
	bl GXS_LoadOBJ
	ldrh r0, [r6]
	ldr r2, [sp, #0x1c]
	add r1, sp, #0x24
	lsl r0, r0, #0xc
	str r0, [sp, #0x24]
	ldrh r0, [r6, #2]
	lsl r0, r0, #0xc
	str r0, [sp, #0x28]
	ldr r0, [sp, #4]
	ldr r0, [r0, #8]
	bl ov20_02253E74
	add r1, r5, #0
	add r1, #0x9c
	str r0, [r1]
	add r0, r5, #0
	add r0, #0x9c
	ldr r0, [r0]
	ldr r1, [sp, #0xc]
	bl ov20_02253FA4
	add r0, r5, #0
	add r0, #0x9c
	ldr r0, [r0]
	mov r1, #4
	bl ov20_02253F28
	ldrh r0, [r4, #0xa]
	cmp r0, #0
	beq _02255072
	ldrh r0, [r4, #0x10]
	cmp r0, #0
	beq _02255080
_02255072:
	add r0, r5, #0
	add r0, #0x9c
	ldr r0, [r0]
	mov r1, #1
	bl ov20_02253F9C
	b _02255098
_02255080:
	ldrh r0, [r4, #8]
	ldrb r1, [r4, #0x13]
	ldrb r2, [r4, #0x12]
	bl sub_0206B7BC
	add r1, r0, #0
	add r0, r5, #0
	add r0, #0x9c
	ldr r0, [r0]
	add r1, r1, #2
	bl ov20_02253F9C
_02255098:
	mov r0, #2
	lsl r0, r0, #8
	add r7, r7, r0
	ldr r0, [sp, #0xc]
	add r4, #0x10
	add r0, #0x10
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	add r6, r6, #4
	add r0, r0, #1
	str r0, [sp, #0x10]
	ldr r0, [sp, #8]
	add r5, r5, #4
	ldr r1, [r0]
	ldr r0, [sp, #0x10]
	cmp r0, r1
	blt _02254FFC
_022550BA:
	ldr r0, [sp, #0x14]
	bl NARC_Delete
_022550C0:
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022550C4: .word ov27_02255348
	thumb_func_end ov27_02254FAC

	thumb_func_start ov27_022550C8
ov27_022550C8: ; 0x022550C8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	mov r1, #0
	lsl r0, r0, #8
	strb r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xf8
	str r4, [r0]
	add r0, r4, #0
	ldr r1, [r4]
	add r0, #0xfc
	str r1, [r0]
	add r1, r4, #0
	ldr r0, _022550F4 ; =ov27_022550F8
	add r1, #0xf8
	mov r2, #1
	bl SysTask_CreateOnMainQueue
	add r4, #0xf4
	str r0, [r4]
	pop {r4, pc}
	.align 2, 0
_022550F4: .word ov27_022550F8
	thumb_func_end ov27_022550C8

	thumb_func_start ov27_022550F8
ov27_022550F8: ; 0x022550F8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldrb r0, [r5, #8]
	ldr r4, [r5, #4]
	ldr r6, [r5]
	cmp r0, #0
	beq _0225510C
	cmp r0, #1
	beq _02255164
	pop {r4, r5, r6, pc}
_0225510C:
	add r0, r4, #0
	add r0, #0x66
	ldrh r0, [r0]
	cmp r0, #0
	beq _022551EA
	ldr r0, [r4, #0x68]
	ldr r1, [r4, #0x6c]
	ldr r2, [r4]
	bl ov27_022551F4
	ldr r1, [r4]
	cmp r0, r1
	bhs _022551EA
	lsl r2, r0, #4
	add r1, r4, r2
	ldrh r3, [r1, #0xa]
	cmp r3, #0
	beq _022551EA
	ldrb r3, [r1, #0x12]
	cmp r3, #0
	bne _022551EA
	mov r3, #0
	strb r3, [r5, #9]
	strb r3, [r5, #0xb]
	strb r0, [r5, #0xa]
	mov r3, #2
	str r3, [r5, #0x10]
	ldrh r0, [r1, #0x10]
	cmp r0, #0
	bne _02255150
	mov r0, #1
	strb r0, [r5, #0xc]
	mov r0, #8
	b _02255154
_02255150:
	strb r3, [r5, #0xc]
	mov r0, #4
_02255154:
	strb r0, [r5, #0xd]
	mov r0, #1
	strb r0, [r5, #8]
	add r0, r4, r2
	ldrh r0, [r0, #8]
	bl ov20_02252B48
	pop {r4, r5, r6, pc}
_02255164:
	ldrb r1, [r5, #0xb]
	ldrb r0, [r5, #0xd]
	cmp r1, r0
	bne _022551A6
	add r0, r4, #0
	add r0, #0x64
	ldrh r0, [r0]
	cmp r0, #0
	beq _02255186
	ldr r0, [r4, #0x68]
	ldr r1, [r4, #0x6c]
	ldr r2, [r4]
	bl ov27_022551F4
	ldrb r1, [r5, #0xa]
	cmp r1, r0
	beq _022551A6
_02255186:
	ldrb r0, [r5, #0xa]
	ldr r1, _022551EC ; =ov27_02255348
	ldr r3, _022551F0 ; =ov27_02255348 + 2
	lsl r2, r0, #2
	add r0, r6, r2
	ldrh r1, [r1, r2]
	ldrh r2, [r3, r2]
	add r0, #0x9c
	ldr r0, [r0]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl ov20_02253F64
	mov r0, #0
	strb r0, [r5, #8]
	pop {r4, r5, r6, pc}
_022551A6:
	ldrb r0, [r5, #9]
	cmp r0, #0
	bne _022551E6
	ldrb r0, [r5, #0xa]
	ldr r1, _022551EC ; =ov27_02255348
	ldr r3, _022551F0 ; =ov27_02255348 + 2
	lsl r2, r0, #2
	add r0, r6, r2
	ldrh r1, [r1, r2]
	add r0, #0x9c
	ldrh r2, [r3, r2]
	ldr r4, [r5, #0x10]
	ldr r0, [r0]
	add r2, r4, r2
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl ov20_02253F64
	ldrb r1, [r5, #0xb]
	ldrb r0, [r5, #0xd]
	cmp r1, r0
	bhs _022551D6
	add r0, r1, #1
	strb r0, [r5, #0xb]
_022551D6:
	mov r0, #0
	ldr r1, [r5, #0x10]
	mvn r0, r0
	mul r0, r1
	str r0, [r5, #0x10]
	ldrb r0, [r5, #0xc]
	strb r0, [r5, #9]
	pop {r4, r5, r6, pc}
_022551E6:
	sub r0, r0, #1
	strb r0, [r5, #9]
_022551EA:
	pop {r4, r5, r6, pc}
	.align 2, 0
_022551EC: .word ov27_02255348
_022551F0: .word ov27_02255348 + 2
	thumb_func_end ov27_022550F8

	thumb_func_start ov27_022551F4
ov27_022551F4: ; 0x022551F4
	push {r3, r4, r5, r6, r7, lr}
	mov lr, r0
	mov ip, r1
	add r7, r2, #0
	ldr r6, _02255248 ; =0x00000000
	beq _02255242
	ldr r3, _0225524C ; =ov27_02255348
_02255202:
	ldrh r1, [r3]
	ldrh r4, [r3, #2]
	mov r5, lr
	add r0, r1, #0
	sub r0, #0x10
	add r2, r4, #0
	add r1, #0x10
	sub r5, r5, r0
	sub r0, r1, r0
	sub r2, #8
	cmp r5, r0
	bhs _0225521E
	mov r0, #1
	b _02255220
_0225521E:
	mov r0, #0
_02255220:
	mov r1, ip
	add r4, #0x18
	sub r1, r1, r2
	sub r2, r4, r2
	cmp r1, r2
	bhs _02255230
	mov r1, #1
	b _02255232
_02255230:
	mov r1, #0
_02255232:
	tst r0, r1
	beq _0225523A
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
_0225523A:
	add r6, r6, #1
	add r3, r3, #4
	cmp r6, r7
	blo _02255202
_02255242:
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255248: .word 0x00000000
_0225524C: .word ov27_02255348
	thumb_func_end ov27_022551F4

	thumb_func_start ov27_02255250
ov27_02255250: ; 0x02255250
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #0
	add r7, r6, #0
_0225525A:
	add r0, r4, #0
	add r0, #0x9c
	ldr r1, [r0]
	cmp r1, #0
	beq _02255270
	ldr r0, [r5, #8]
	bl ov20_02253F14
	add r0, r4, #0
	add r0, #0x9c
	str r7, [r0]
_02255270:
	add r0, r4, #0
	add r0, #0xb4
	ldr r1, [r0]
	cmp r1, #0
	beq _02255288
	ldr r0, [r5, #8]
	bl ov20_02253F14
	add r1, r4, #0
	add r1, #0xb4
	mov r0, #0
	str r0, [r1]
_02255288:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #6
	blt _0225525A
	ldr r0, [r5, #0x38]
	mov r6, #0
	cmp r0, #0
	bls _022552AC
	add r4, r5, #0
	add r4, #0x3c
_0225529C:
	add r0, r4, #0
	bl RemoveWindow
	ldr r0, [r5, #0x38]
	add r6, r6, #1
	add r4, #0x10
	cmp r6, r0
	blo _0225529C
_022552AC:
	mov r0, #0
	str r0, [r5, #0x38]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end ov27_02255250

	thumb_func_start ov27_022552B4
ov27_022552B4: ; 0x022552B4
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl ov27_02254BF4
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov27_022552B4

	thumb_func_start ov27_022552D0
ov27_022552D0: ; 0x022552D0
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r6, r1, #0
	add r0, r6, #0
	bl ov20_022538A0
	add r5, r0, #0
	add r0, r6, #0
	bl ov20_022538A4
	add r4, r0, #0
	add r0, r5, #0
	bl ov27_02255250
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r0, [r5, #4]
	mov r1, #6
	mov r2, #5
	bl FillBgTilemapRect
	add r0, r5, #0
	add r1, r4, #0
	bl ov27_02254F18
	add r0, r5, #0
	add r1, r4, #0
	bl ov27_02254FAC
	ldr r2, [r5, #0x34]
	add r0, r5, #0
	add r1, r4, #0
	bl ov27_02254CC8
	ldr r0, [r5, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r0, _02255338 ; =0x00000669
	bl Poketch_PlaySoundEffect
	add r0, r6, #0
	bl ov27_02254BF4
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_02255338: .word 0x00000669
	thumb_func_end ov27_022552D0

	.section .rodata

	.global ov27_0225533C
ov27_0225533C: ; 0x0225533C
	.word ov27_02254948, ov27_02254988, ov27_02254A14

	.global ov27_02255348
ov27_02255348: ; 0x02255348
	.short 0x40, 0x24, 0xA0, 0x24, 0x40, 0x54, 0xA0, 0x54
	.short 0x40, 0x84, 0xA0, 0x84

	.global ov27_02255360
ov27_02255360: ; 0x02255360
	.short 0x04, 0x08, 0x10, 0x08, 0x04, 0x0E, 0x10, 0x0E
	.short 0x04, 0x14, 0x10, 0x14

	.global ov27_02255378
ov27_02255378: ; 0x02255378
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov27_02255394
ov27_02255394: ; 0x02255394
	.word 0x00, ov27_02254C08, 0x00
	.word 0x01, ov27_022552B4, 0x00
	.word 0x02, ov27_022552D0, 0x00
	.word 0x00, 0x00000000, 0x00
