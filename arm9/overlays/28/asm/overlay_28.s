	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov28_02254854
ov28_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x64
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl ov28_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =ov28_022549C0
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
_02254898: .word ov28_022549C0
	thumb_func_end ov28_02254854

	thumb_func_start ov28_0225489C
ov28_0225489C: ; 0x0225489C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	add r4, r1, #0
	add r0, #0x5c
	add r1, r7, #4
	bl ov28_02254AF4
	cmp r0, #0
	beq _02254986
	mov r0, #0
	strb r0, [r7]
	strb r0, [r7, #1]
	strb r0, [r7, #2]
	str r4, [r7, #0x60]
	bl sub_020225F8
	bl SaveArray_Party_Get
	mov r1, #0
	str r0, [sp, #4]
	str r1, [sp]
	bl Party_GetCount
	mov r6, #0
	str r0, [r7, #4]
	cmp r0, #0
	ble _0225496A
	add r4, r7, #0
_022548D6:
	ldr r0, [sp, #4]
	add r1, r6, #0
	bl Party_GetMonByIndex
	mov r1, #0x4c
	mov r2, #0
	add r5, r0, #0
	bl GetMonData
	cmp r0, #0
	bne _02254962
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0x10]
	add r0, r5, #0
	bl sub_0206B688
	str r0, [r4, #8]
	add r0, r5, #0
	mov r1, #9
	mov r2, #0
	bl GetMonData
	bl ov28_0225498C
	cmp r0, #6
	bhi _02254944
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0225492A: ; jump table
	.short _02254938 - _0225492A - 2 ; case 0
	.short _02254938 - _0225492A - 2 ; case 1
	.short _02254938 - _0225492A - 2 ; case 2
	.short _02254944 - _0225492A - 2 ; case 3
	.short _0225494E - _0225492A - 2 ; case 4
	.short _0225494E - _0225492A - 2 ; case 5
	.short _0225494E - _0225492A - 2 ; case 6
_02254938:
	mov r1, #1
	strb r1, [r4, #0x12]
	mov r1, #3
	sub r0, r1, r0
	strb r0, [r4, #0x13]
	b _0225495A
_02254944:
	mov r0, #2
	strb r0, [r4, #0x12]
	mov r0, #0
	strb r0, [r4, #0x13]
	b _0225495A
_0225494E:
	mov r1, #0
	strb r1, [r4, #0x12]
	mov r1, #3
	sub r0, r1, r0
	neg r0, r0
	strb r0, [r4, #0x13]
_0225495A:
	ldr r0, [sp]
	add r4, #0xc
	add r0, r0, #1
	str r0, [sp]
_02254962:
	ldr r0, [r7, #4]
	add r6, r6, #1
	cmp r6, r0
	blt _022548D6
_0225496A:
	ldr r0, [sp]
	mov r1, #0
	str r0, [r7, #4]
	add r0, r7, #0
	add r0, #0x50
	strh r1, [r0]
	add r0, r7, #0
	add r0, #0x52
	strh r1, [r0]
	str r1, [r7, #0x54]
	add sp, #8
	str r1, [r7, #0x58]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02254986:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov28_0225489C

	thumb_func_start ov28_0225498C
ov28_0225498C: ; 0x0225498C
	ldr r3, _022549A8 ; =ov28_02255E78
	mov r2, #0
_02254990:
	ldrb r1, [r3]
	cmp r0, r1
	bhs _0225499A
	add r0, r2, #0
	bx lr
_0225499A:
	add r2, r2, #1
	add r3, r3, #1
	cmp r2, #6
	blo _02254990
	mov r0, #6
	bx lr
	nop
_022549A8: .word ov28_02255E78
	thumb_func_end ov28_0225498C

	thumb_func_start ov28_022549AC
ov28_022549AC: ; 0x022549AC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x5c]
	bl ov28_02254B70
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov28_022549AC

	thumb_func_start ov28_022549C0
ov28_022549C0: ; 0x022549C0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhs _022549EC
	lsl r2, r1, #2
	ldr r1, _022549F0 ; =ov28_02255E80
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _022549EC
	add r0, r4, #0
	bl ov28_022549AC
	add r0, r5, #0
	bl sub_0200CAB4
	ldr r0, [r4, #0x60]
	bl ov20_022529A0
_022549EC:
	pop {r3, r4, r5, pc}
	nop
_022549F0: .word ov28_02255E80
	thumb_func_end ov28_022549C0

	thumb_func_start ov28_022549F4
ov28_022549F4: ; 0x022549F4
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end ov28_022549F4

	thumb_func_start ov28_022549FC
ov28_022549FC: ; 0x022549FC
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254A04
	b _02254A06
_02254A04:
	mov r1, #2
_02254A06:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end ov28_022549FC

	thumb_func_start ov28_02254A10
ov28_02254A10: ; 0x02254A10
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A20
	cmp r0, #1
	beq _02254A30
	b _02254A4A
_02254A20:
	ldr r0, [r4, #0x5c]
	mov r1, #0
	bl ov28_02254BC8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A4A
_02254A30:
	ldr r0, [r4, #0x5c]
	mov r1, #0
	bl ov28_02254BEC
	cmp r0, #0
	beq _02254A4A
	ldr r0, [r4, #0x60]
	bl ov20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl ov28_022549FC
_02254A4A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov28_02254A10

	thumb_func_start ov28_02254A50
ov28_02254A50: ; 0x02254A50
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254A64
	mov r1, #2
	bl ov28_022549FC
	mov r0, #0
	pop {r4, pc}
_02254A64:
	add r1, r4, #0
	add r0, #0x54
	add r1, #0x58
	bl TouchScreen_GetTapState
	add r1, r4, #0
	add r1, #0x50
	strh r0, [r1]
	add r0, r4, #0
	add r0, #0x50
	ldrh r0, [r0]
	cmp r0, #0
	beq _02254AB2
	ldr r0, [r4, #0x54]
	sub r0, #0x10
	cmp r0, #0xbf
	bhs _02254A8A
	mov r1, #1
	b _02254A8C
_02254A8A:
	mov r1, #0
_02254A8C:
	ldr r0, [r4, #0x58]
	sub r0, #0x10
	cmp r0, #0x9f
	bhs _02254A98
	mov r0, #1
	b _02254A9A
_02254A98:
	mov r0, #0
_02254A9A:
	tst r0, r1
	beq _02254AAA
	bl sub_02020AA4
	add r4, #0x52
	strh r0, [r4]
	mov r0, #0
	pop {r4, pc}
_02254AAA:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x50
	strh r1, [r0]
_02254AB2:
	mov r0, #0
	str r0, [r4, #0x54]
	str r0, [r4, #0x58]
	add r4, #0x52
	strh r0, [r4]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov28_02254A50

	thumb_func_start ov28_02254AC0
ov28_02254AC0: ; 0x02254AC0
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254AD0
	cmp r0, #1
	beq _02254AE0
	b _02254AEE
_02254AD0:
	ldr r0, [r4, #0x5c]
	mov r1, #1
	bl ov28_02254BC8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254AEE
_02254AE0:
	ldr r0, [r4, #0x5c]
	bl ov28_02254BF8
	cmp r0, #0
	beq _02254AEE
	mov r0, #1
	pop {r4, pc}
_02254AEE:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov28_02254AC0

	thumb_func_start ov28_02254AF4
ov28_02254AF4: ; 0x02254AF4
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r6, r1, #0
	mov r1, #0xa3
	add r5, r0, #0
	mov r0, #8
	lsl r1, r1, #2
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254B6A
	add r0, #8
	mov r1, #8
	bl ov20_022536F4
	str r6, [r4]
	bl ov20_02252D34
	str r0, [r4, #4]
	bl ov20_02252D24
	str r0, [r4, #0x30]
	add r0, r4, #0
	mov r3, #0
	add r0, #0xb0
	str r3, [r0]
	mov r0, #0x4d
	lsl r0, r0, #2
	add r6, r4, #0
	add r2, r3, #0
	add r1, r0, #4
_02254B32:
	str r2, [r6, r0]
	str r2, [r6, r1]
	add r3, r3, #1
	add r6, #0x38
	cmp r3, #6
	blt _02254B32
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x34
	mov r1, #0xc
	mov r2, #5
	mov r3, #6
	bl ov20_02253FBC
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0xc
	mov r2, #0x24
	mov r3, #0x25
	bl ov20_02253FBC
	add sp, #4
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_02254B6A:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	thumb_func_end ov28_02254AF4

	thumb_func_start ov28_02254B70
ov28_02254B70: ; 0x02254B70
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	beq _02254BC6
	mov r7, #0x4d
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #2
_02254B7E:
	ldr r1, [r4, r7]
	cmp r1, #0
	beq _02254B8A
	ldr r0, [r5, #0x30]
	bl ov20_02253F14
_02254B8A:
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _02254B9A
	ldr r0, [r5, #0x30]
	bl ov20_02253F14
_02254B9A:
	add r6, r6, #1
	add r4, #0x38
	cmp r6, #6
	blt _02254B7E
	add r0, r5, #0
	add r0, #0x34
	bl ov20_02254014
	add r0, r5, #0
	add r0, #0x48
	bl ov20_02254014
	add r0, r5, #0
	add r0, #0xb0
	ldr r0, [r0]
	cmp r0, #0
	beq _02254BC0
	bl sub_0200CAB4
_02254BC0:
	add r0, r5, #0
	bl FreeToHeap
_02254BC6:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov28_02254B70

	thumb_func_start ov28_02254BC8
ov28_02254BC8: ; 0x02254BC8
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254BE8 ; =ov28_02255EF4
	ldr r3, [r2]
	bl ov20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254BE8: .word ov28_02255EF4
	thumb_func_end ov28_02254BC8

	thumb_func_start ov28_02254BEC
ov28_02254BEC: ; 0x02254BEC
	ldr r3, _02254BF4 ; =ov20_02253794
	add r0, #8
	bx r3
	nop
_02254BF4: .word ov20_02253794
	thumb_func_end ov28_02254BEC

	thumb_func_start ov28_02254BF8
ov28_02254BF8: ; 0x02254BF8
	ldr r3, _02254C00 ; =ov20_022537B8
	add r0, #8
	bx r3
	nop
_02254C00: .word ov20_022537B8
	thumb_func_end ov28_02254BF8

	thumb_func_start ov28_02254C04
ov28_02254C04: ; 0x02254C04
	push {r4, lr}
	add r4, r0, #0
	bl ov20_022538A0
	add r0, #8
	add r1, r4, #0
	bl ov20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov28_02254C04

	thumb_func_start ov28_02254C18
ov28_02254C18: ; 0x02254C18
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254CA8 ; =ov28_02255ED8
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
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #7
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	ldr r0, [r5, #4]
	mov r1, #6
	add r3, r2, #0
	bl FillBgTilemapRect
	mov r0, #0
	add r1, r0, #0
	bl ov20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r1, [r5]
	add r0, r5, #0
	bl ov28_02254CB4
	ldr r1, [r5]
	add r0, r5, #0
	bl ov28_02254E9C
	ldr r1, _02254CAC ; =0x04001000
	ldr r0, _02254CB0 ; =0xFFFFE0FF
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
	add r0, r4, #0
	bl ov28_02254C04
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_02254CA8: .word ov28_02255ED8
_02254CAC: .word 0x04001000
_02254CB0: .word 0xFFFFE0FF
	thumb_func_end ov28_02254C18

	thumb_func_start ov28_02254CB4
ov28_02254CB4: ; 0x02254CB4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	str r0, [sp, #0xc]
	mov r0, #1
	str r1, [sp, #0x10]
	bl ov20_022539C4
	mov r0, #0
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x23
	lsl r3, r0, #9
	bl GfGfxLoader_LoadWholePalette
	mov r0, #0x13
	mov r1, #8
	bl NARC_New
	str r0, [sp, #0x1c]
	cmp r0, #0
	bne _02254CE8
	b _02254E46
_02254CE8:
	mov r0, #0
	str r0, [sp, #0x18]
	add r1, r0, #0
	add r0, sp, #0x2c
	strh r1, [r0, #0xc]
	ldr r1, [sp, #0x18]
	strb r1, [r0, #0xe]
	mov r1, #2
	strb r1, [r0, #0xf]
	mov r1, #1
	strb r1, [r0, #0x11]
	ldr r0, [sp, #0x10]
	ldr r0, [r0]
	cmp r0, #0
	bgt _02254D08
	b _02254E40
_02254D08:
	ldr r0, [sp, #0x18]
	ldr r5, [sp, #0xc]
	str r0, [sp, #0x14]
	add r7, r0, #0
	add r0, r5, #0
	str r0, [sp, #0x24]
	add r0, #0x34
	str r0, [sp, #0x24]
	add r0, r5, #0
	str r0, [sp, #0x28]
	add r0, #0x48
	ldr r4, [sp, #0x10]
	ldr r6, _02254E4C ; =ov28_02255EC0
	str r0, [sp, #0x28]
_02254D24:
	ldr r0, [sp, #0x1c]
	ldr r1, [r4, #4]
	mov r2, #8
	bl NARC_AllocAndReadWholeMember
	add r1, sp, #0x2c
	str r0, [sp, #0x20]
	bl NNS_G2dGetUnpackedCharacterData
	ldr r0, [sp, #0x2c]
	mov r1, #1
	ldr r0, [r0, #0x14]
	lsl r1, r1, #0xa
	bl DC_FlushRange
	ldr r0, [sp, #0x2c]
	mov r2, #1
	ldr r0, [r0, #0x14]
	ldr r1, [sp, #0x14]
	lsl r2, r2, #0xa
	bl GXS_LoadOBJ
	ldr r0, [sp, #0x20]
	bl FreeToHeap
	ldrh r0, [r6]
	mov r1, #1
	ldr r2, [sp, #0x24]
	lsl r0, r0, #0xc
	str r0, [sp, #0x30]
	ldrh r0, [r6, #2]
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	add r0, sp, #0x2c
	strb r1, [r0, #0x10]
	ldr r0, [sp, #0xc]
	add r1, sp, #0x30
	ldr r0, [r0, #0x30]
	bl ov20_02253E74
	mov r1, #0x4d
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	add r1, r7, #0
	bl ov20_02253FA4
	ldrh r0, [r4, #8]
	ldrh r1, [r4, #0xc]
	mov r2, #0
	bl sub_0206B7BC
	add r1, r0, #0
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r1, #1
	bl ov20_02253F9C
	mov r1, #0
	add r0, sp, #0x2c
	strb r1, [r0, #0x10]
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x28]
	ldr r0, [r0, #0x30]
	add r1, sp, #0x30
	bl ov20_02253E74
	mov r1, #0x4e
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02254DDC
	mov r1, #1
	bl ov20_02253F78
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0xc0
	bl ov20_02253FA4
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl ov20_02253F9C
	b _02254DE0
_02254DDC:
	bl GF_AssertFail
_02254DE0:
	ldrh r0, [r4, #8]
	mov r1, #0x1c ; BASE_FLIP
	bl GetMonBaseStat
	mov r1, #0x59
	lsl r1, r1, #2
	strb r0, [r5, r1]
	ldr r0, _02254E50 ; =0x00000165
	mov r1, #0
	strb r1, [r5, r0]
	add r0, r0, #1
	strb r1, [r5, r0]
	mov r1, #0x52
	ldr r0, [sp, #0x34]
	ldr r2, [sp, #0x30]
	lsl r1, r1, #2
	str r2, [r5, r1]
	add r1, r1, #4
	str r0, [r5, r1]
	mov r0, #0x15
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r0, #4
	str r1, [r5, r0]
	mov r0, #0x56
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r0, #4
	str r1, [r5, r0]
	mov r0, #1
	ldr r1, [sp, #0x14]
	lsl r0, r0, #0xa
	add r0, r1, r0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r4, #0xc
	add r0, r0, #1
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x10]
	add r6, r6, #4
	ldr r1, [r0]
	ldr r0, [sp, #0x18]
	add r5, #0x38
	add r7, #0x20
	cmp r0, r1
	bge _02254E40
	b _02254D24
_02254E40:
	ldr r0, [sp, #0x1c]
	bl NARC_Delete
_02254E46:
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254E4C: .word ov28_02255EC0
_02254E50: .word 0x00000165
	thumb_func_end ov28_02254CB4

	thumb_func_start ov28_02254E54
ov28_02254E54: ; 0x02254E54
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MTRandom
	mov r1, #0x3f
	and r0, r1
	sub r0, #0x20
	lsl r4, r0, #0xc
	bl MTRandom
	mov r1, #0x3f
	and r0, r1
	sub r0, #0x20
	lsl r0, r0, #0xc
	str r4, [r5]
	str r0, [r5, #4]
	mov r0, #0
	str r0, [r5, #8]
	add r0, r5, #0
	add r1, r5, #0
	bl VEC_Normalize
	ldr r1, [r5]
	asr r0, r1, #3
	lsr r0, r0, #0x1c
	add r0, r1, r0
	asr r0, r0, #4
	str r0, [r5]
	ldr r1, [r5, #4]
	asr r0, r1, #3
	lsr r0, r0, #0x1c
	add r0, r1, r0
	asr r0, r0, #4
	str r0, [r5, #4]
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov28_02254E54

	thumb_func_start ov28_02254E9C
ov28_02254E9C: ; 0x02254E9C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	str r0, [sp]
	ldr r0, [r7]
	mov r6, #0
	cmp r0, #0
	ble _02254EF8
	mov r1, #0x4f
	ldr r0, [sp]
	lsl r1, r1, #2
	add r4, r0, r1
	add r5, r0, #0
_02254EB4:
	add r0, r4, #0
	bl ov28_02254E54
	mov r0, #0x59
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _02254ED2
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl ov20_02253F28
	b _02254EEC
_02254ED2:
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	ble _02254EE0
	mov r1, #7
	b _02254EE2
_02254EE0:
	mov r1, #6
_02254EE2:
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl ov20_02253F28
_02254EEC:
	ldr r0, [r7]
	add r6, r6, #1
	add r4, #0x38
	add r5, #0x38
	cmp r6, r0
	blt _02254EB4
_02254EF8:
	ldr r0, [sp]
	bl ov28_02254F34
	ldr r0, _02254F14 ; =ov28_02254F84
	ldr r1, [sp]
	mov r2, #1
	bl SysTask_CreateOnMainQueue
	ldr r1, [sp]
	add r1, #0xb0
	str r1, [sp]
	str r0, [r1]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254F14: .word ov28_02254F84
	thumb_func_end ov28_02254E9C

	thumb_func_start ov28_02254F18
ov28_02254F18: ; 0x02254F18
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl ov28_02254C04
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov28_02254F18

	thumb_func_start ov28_02254F34
ov28_02254F34: ; 0x02254F34
	push {r3, r4, r5, r6}
	add r1, r0, #0
	mov r5, #0
	add r1, #0xe4
	str r5, [r1]
	ldr r1, [r0]
	ldr r3, [r1]
	cmp r3, #0
	ble _02254F60
	mov r1, #0x16
	lsl r1, r1, #4
	add r6, r0, #0
	add r4, r5, #0
	add r2, r1, #3
_02254F50:
	strb r4, [r6, r1]
	strb r4, [r6, r2]
	ldr r3, [r0]
	add r5, r5, #1
	ldr r3, [r3]
	add r6, #0x38
	cmp r5, r3
	blt _02254F50
_02254F60:
	add r1, r0, #0
	add r1, #0xec
	str r3, [r1]
	add r1, r0, #0
	add r1, #0xec
	ldr r1, [r1]
	add r0, #0xf0
	str r1, [r0]
	pop {r3, r4, r5, r6}
	bx lr
	thumb_func_end ov28_02254F34

	thumb_func_start ov28_02254F74
ov28_02254F74: ; 0x02254F74
	add r2, r0, #0
	add r2, #0xe4
	str r1, [r2]
	mov r1, #0
	add r0, #0xe8
	str r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end ov28_02254F74

	thumb_func_start ov28_02254F84
ov28_02254F84: ; 0x02254F84
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r4, [r5]
	add r0, r4, #0
	add r0, #0x4c
	ldrh r0, [r0]
	cmp r0, #0
	beq _02254FFC
	mov r0, #0xa1
	ldr r1, [r4, #0x50]
	lsl r0, r0, #2
	str r1, [r5, r0]
	ldr r1, [r4, #0x54]
	add r0, r0, #4
	sub r1, #8
	str r1, [r5, r0]
	add r0, r5, #0
	bl ov28_02255040
	add r1, r5, #0
	add r1, #0xec
	str r0, [r1]
	add r0, r5, #0
	add r0, #0xec
	ldr r1, [r0]
	ldr r0, [r4]
	cmp r1, r0
	bhs _02254FC0
	mov r1, #1
	b _02254FC2
_02254FC0:
	mov r1, #0
_02254FC2:
	add r0, r5, #0
	add r0, #0xf8
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	cmp r0, #0
	beq _02254FEE
	add r0, r5, #0
	add r0, #0xec
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xf0
	ldr r0, [r0]
	cmp r1, r0
	beq _02254FEE
	mov r0, #0xc
	mul r0, r1
	add r0, r4, r0
	ldrh r0, [r0, #8]
	bl ov20_02252B48
_02254FEE:
	add r0, r5, #0
	add r0, #0xec
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xf0
	str r1, [r0]
	b _0225500C
_02254FFC:
	add r0, r5, #0
	mov r1, #0
	add r0, #0xf8
	str r1, [r0]
	add r0, r5, #0
	ldr r1, [r4]
	add r0, #0xf0
	str r1, [r0]
_0225500C:
	add r2, r5, #0
	add r2, #0xe4
	ldr r2, [r2]
	add r0, r5, #0
	lsl r3, r2, #2
	ldr r2, _0225503C ; =ov28_02255E94
	add r1, r4, #0
	ldr r2, [r2, r3]
	blx r2
	add r0, r5, #0
	add r1, r4, #0
	bl ov28_022551C4
	add r0, r5, #0
	add r0, #0xe4
	ldr r0, [r0]
	cmp r0, #4
	beq _02255038
	add r0, r5, #0
	add r1, r4, #0
	bl ov28_02255920
_02255038:
	pop {r3, r4, r5, pc}
	nop
_0225503C: .word ov28_02255E94
	thumb_func_end ov28_02254F84

	thumb_func_start ov28_02255040
ov28_02255040: ; 0x02255040
	push {r4, r5, r6, r7}
	add r5, r0, #0
	ldr r0, [r5]
	mov r1, #0
	ldr r4, [r0]
	cmp r4, #0
	ble _0225508C
	mov r0, #0xa1
	lsl r0, r0, #2
	ldr r2, [r5, r0]
	add r0, r0, #4
	ldr r3, [r5, r0]
_02255058:
	mov r0, #0x52
	lsl r0, r0, #2
	mov r6, #0x53
	ldr r0, [r5, r0]
	lsl r6, r6, #2
	ldr r6, [r5, r6]
	asr r0, r0, #0xc
	asr r6, r6, #0xc
	sub r0, r2, r0
	sub r7, r3, r6
	add r6, r0, #0
	mul r6, r0
	add r0, r7, #0
	mul r0, r7
	add r6, r6, r0
	mov r0, #1
	lsl r0, r0, #8
	cmp r6, r0
	bge _02255084
	add r0, r1, #0
	pop {r4, r5, r6, r7}
	bx lr
_02255084:
	add r1, r1, #1
	add r5, #0x38
	cmp r1, r4
	blt _02255058
_0225508C:
	add r0, r4, #0
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
	thumb_func_end ov28_02255040

	thumb_func_start ov28_02255094
ov28_02255094: ; 0x02255094
	push {r4, r5}
	lsl r4, r0, #0xc
	ldr r0, [r3]
	sub r0, r4, r0
	lsl r4, r1, #0xc
	ldr r1, [r3, #4]
	sub r5, r4, r1
	asr r1, r0, #0xc
	add r4, r0, #0
	mul r4, r1
	add r1, r2, #0
	mul r1, r2
	asr r0, r5, #0xc
	add r3, r5, #0
	mul r3, r0
	lsl r2, r1, #0xc
	add r1, r4, r3
	mov r0, #0
	cmp r2, r1
	ble _022550BE
	mov r0, #1
_022550BE:
	pop {r4, r5}
	bx lr
	.align 2, 0
	thumb_func_end ov28_02255094

	thumb_func_start ov28_022550C4
ov28_022550C4: ; 0x022550C4
	push {r3, lr}
	add r1, #0x4e
	ldrh r1, [r1]
	cmp r1, #0
	beq _022550E0
	add r1, r0, #0
	add r1, #0xf8
	ldr r2, [r1]
	add r1, r0, #0
	add r1, #0xfc
	str r2, [r1]
	mov r1, #1
	bl ov28_02254F74
_022550E0:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end ov28_022550C4

	thumb_func_start ov28_022550E4
ov28_022550E4: ; 0x022550E4
	push {r3, lr}
	add r1, #0x4c
	ldrh r1, [r1]
	cmp r1, #0
	beq _0225510E
	add r1, r0, #0
	add r1, #0xe8
	ldr r1, [r1]
	add r2, r1, #1
	add r1, r0, #0
	add r1, #0xe8
	str r2, [r1]
	add r1, r0, #0
	add r1, #0xe8
	ldr r1, [r1]
	cmp r1, #6
	bls _02255126
	mov r1, #2
	bl ov28_02254F74
	pop {r3, pc}
_0225510E:
	add r1, r0, #0
	add r1, #0xfc
	ldr r1, [r1]
	cmp r1, #0
	beq _02255120
	mov r1, #0
	bl ov28_02254F74
	pop {r3, pc}
_02255120:
	mov r1, #3
	bl ov28_02254F74
_02255126:
	pop {r3, pc}
	thumb_func_end ov28_022550E4

	thumb_func_start ov28_02255128
ov28_02255128: ; 0x02255128
	push {r3, lr}
	add r1, #0x4c
	ldrh r1, [r1]
	cmp r1, #0
	bne _02255138
	mov r1, #0
	bl ov28_02254F74
_02255138:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end ov28_02255128

	thumb_func_start ov28_0225513C
ov28_0225513C: ; 0x0225513C
	push {r3, lr}
	add r1, #0x4e
	ldrh r1, [r1]
	cmp r1, #0
	bne _02255166
	add r1, r0, #0
	add r1, #0xe8
	ldr r1, [r1]
	add r2, r1, #1
	add r1, r0, #0
	add r1, #0xe8
	str r2, [r1]
	add r1, r0, #0
	add r1, #0xe8
	ldr r1, [r1]
	cmp r1, #6
	bls _02255184
	mov r1, #0
	bl ov28_02254F74
	pop {r3, pc}
_02255166:
	add r1, r0, #0
	add r1, #0xf8
	ldr r1, [r1]
	cmp r1, #0
	beq _0225517E
	add r2, r0, #0
	mov r1, #1
	add r2, #0xfc
	str r1, [r2]
	bl ov28_02254F74
	pop {r3, pc}
_0225517E:
	mov r1, #4
	bl ov28_02254F74
_02255184:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end ov28_0225513C

	thumb_func_start ov28_02255188
ov28_02255188: ; 0x02255188
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0xe8
	ldr r1, [r1]
	cmp r1, #0
	bne _022551A8
	bl ov28_02255288
	add r0, r4, #0
	add r0, #0xe8
	ldr r0, [r0]
	add r4, #0xe8
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_022551A8:
	bl ov28_022552C0
	cmp r0, #0
	beq _022551B8
	add r0, r4, #0
	mov r1, #0
	bl ov28_02254F74
_022551B8:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov28_02255188

	thumb_func_start ov28_022551BC
ov28_022551BC: ; 0x022551BC
	push {r0, r1, r2, r3}
	add sp, #0x10
	bx lr
	.align 2, 0
	thumb_func_end ov28_022551BC

	thumb_func_start ov28_022551C4
ov28_022551C4: ; 0x022551C4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	str r0, [sp]
	ldr r0, [r7]
	mov r4, #0
	cmp r0, #0
	ble _02255212
	ldr r5, [sp]
_022551D4:
	ldr r0, _0225521C ; =0x00000163
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _022551F4
	ldr r0, _0225521C ; =0x00000163
	ldr r2, _0225521C ; =0x00000163
	ldrb r0, [r5, r0]
	sub r1, r0, #1
	ldr r0, _0225521C ; =0x00000163
	strb r1, [r5, r0]
	ldrb r2, [r5, r2]
	ldr r0, _02255220 ; =ov28_02255F20
	add r1, r4, #0
	bl ov28_022551BC
	b _02255208
_022551F4:
	mov r3, #0x16
	lsl r3, r3, #4
	ldrb r3, [r5, r3]
	ldr r0, [sp]
	add r1, r7, #0
	lsl r6, r3, #2
	ldr r3, _02255224 ; =ov28_02255EA8
	add r2, r4, #0
	ldr r3, [r3, r6]
	blx r3
_02255208:
	ldr r0, [r7]
	add r4, r4, #1
	add r5, #0x38
	cmp r4, r0
	blt _022551D4
_02255212:
	ldr r0, _02255228 ; =ov28_02255F34
	bl ov28_022551BC
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225521C: .word 0x00000163
_02255220: .word ov28_02255F20
_02255224: .word ov28_02255EA8
_02255228: .word ov28_02255F34
	thumb_func_end ov28_022551C4

	thumb_func_start ov28_0225522C
ov28_0225522C: ; 0x0225522C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r2, #0
	mov r2, #0x38
	add r4, r6, #0
	mul r4, r2
	add r5, r0, #0
	mov r2, #0x16
	add r3, r5, r4
	lsl r2, r2, #4
	ldrb r2, [r3, r2]
	cmp r2, #3
	bne _0225524A
	bl ov28_02255344
_0225524A:
	mov r0, #0x16
	lsl r0, r0, #4
	add r2, r5, r0
	mov r3, #0x16
	lsl r3, r3, #4
	strb r7, [r2, r4]
	mov r1, #0
	add r0, r5, r4
	add r3, #8
	str r1, [r0, r3]
	mov r3, #0x16
	lsl r3, r3, #4
	sub r3, #0xc
	str r1, [r0, r3]
	mov r3, #0x16
	lsl r3, r3, #4
	sub r3, #8
	str r1, [r0, r3]
	mov r3, #0x16
	lsl r3, r3, #4
	sub r3, r3, #4
	str r1, [r0, r3]
	ldrb r0, [r2, r4]
	cmp r0, #3
	bne _02255284
	add r0, r5, #0
	add r1, r6, #0
	bl ov28_022552D4
_02255284:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end ov28_0225522C

	thumb_func_start ov28_02255288
ov28_02255288: ; 0x02255288
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6]
	mov r4, #0
	ldr r1, [r0]
	cmp r1, #0
	ble _022552B4
	add r5, r6, #0
	add r7, r4, #0
_0225529A:
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #5
	bl ov28_0225522C
	ldr r0, _022552BC ; =0x00000163
	add r4, r4, #1
	strb r7, [r5, r0]
	ldr r0, [r6]
	add r5, #0x38
	ldr r1, [r0]
	cmp r4, r1
	blt _0225529A
_022552B4:
	mov r0, #1
	lsl r0, r0, #8
	str r1, [r6, r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022552BC: .word 0x00000163
	thumb_func_end ov28_02255288

	thumb_func_start ov28_022552C0
ov28_022552C0: ; 0x022552C0
	mov r1, #1
	lsl r1, r1, #8
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _022552CE
	mov r0, #1
	bx lr
_022552CE:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end ov28_022552C0

	thumb_func_start ov28_022552D4
ov28_022552D4: ; 0x022552D4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0xc
	add r7, r1, #0
	mul r7, r0
	ldr r0, [r5]
	add r0, r0, r7
	ldrb r0, [r0, #0xe]
	cmp r0, #0
	bne _02255314
	mov r0, #0x4e
	lsl r0, r0, #2
	add r4, r5, r0
	mov r0, #0x38
	add r6, r1, #0
	mul r6, r0
	ldr r0, [r5, #0x30]
	ldr r1, [r4, r6]
	mov r2, #0
	bl ov20_02253F80
	ldr r1, [r5]
	ldr r0, [r4, r6]
	add r1, r1, r7
	ldrb r1, [r1, #0xf]
	sub r1, r1, #1
	bl ov20_02253F28
	ldr r0, [r4, r6]
	mov r1, #0
	bl ov20_02253F78
_02255314:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end ov28_022552D4

	thumb_func_start ov28_02255318
ov28_02255318: ; 0x02255318
	push {r3, r4, r5, lr}
	mov r2, #0x4e
	lsl r2, r2, #2
	add r4, r0, r2
	mov r2, #0x38
	add r5, r1, #0
	mul r5, r2
	ldr r0, [r0, #0x30]
	ldr r1, [r4, r5]
	mov r2, #2
	bl ov20_02253F80
	ldr r0, [r4, r5]
	mov r1, #3
	bl ov20_02253F28
	ldr r0, [r4, r5]
	mov r1, #0
	bl ov20_02253F78
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov28_02255318

	thumb_func_start ov28_02255344
ov28_02255344: ; 0x02255344
	mov r2, #0x38
	mul r2, r1
	add r1, r0, r2
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r3, _02255358 ; =ov20_02253F78
	mov r1, #1
	bx r3
	nop
_02255358: .word ov20_02253F78
	thumb_func_end ov28_02255344

	thumb_func_start ov28_0225535C
ov28_0225535C: ; 0x0225535C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r2, #0
	add r5, r0, #0
	add r0, r6, #0
	add r4, r1, #0
	bl VEC_Mag
	cmp r0, r5
	ble _0225539A
	add r1, r0, #0
	mul r1, r4
	add r0, r1, #0
	mov r1, #0x64
	bl _u32_div_f
	add r4, r0, #0
	add r0, r6, #0
	add r1, sp, #0
	bl VEC_Normalize
	mov r0, #0
	str r0, [r6]
	str r0, [r6, #4]
	str r0, [r6, #8]
	add r0, r4, #0
	add r1, sp, #0
	add r2, r6, #0
	add r3, r6, #0
	bl VEC_MultAdd
_0225539A:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov28_0225535C

	thumb_func_start ov28_022553A0
ov28_022553A0: ; 0x022553A0
	ldr r1, [r0]
	cmp r1, #0
	bne _022553B0
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _022553B0
	mov r0, #1
	bx lr
_022553B0:
	mov r0, #0
	bx lr
	thumb_func_end ov28_022553A0

	thumb_func_start ov28_022553B4
ov28_022553B4: ; 0x022553B4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r2, #0
	add r6, r1, #0
	ldr r0, _02255498 ; =ov28_02255F44
	add r1, r4, #0
	bl ov28_022551BC
	add r0, r6, #0
	add r0, #0x4c
	ldrh r0, [r0]
	cmp r0, #0
	bne _022553E6
	mov r1, #0x60
	add r2, r1, #0
	add r2, #0xdc
	add r3, r5, r2
	mov r2, #0x38
	mov r0, #3
	mul r2, r4
	lsl r0, r0, #8
	add r2, r3, r2
	bl ov28_0225535C
	pop {r3, r4, r5, r6, r7, pc}
_022553E6:
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	cmp r0, #0
	bne _02255448
	mov r1, #0xa1
	mov r3, #0x52
	lsl r1, r1, #2
	lsl r3, r3, #2
	ldr r0, [r5, r1]
	add r1, r1, #4
	add r7, r5, r3
	mov r3, #0x38
	mul r3, r4
	ldr r1, [r5, r1]
	mov r2, #0x30
	add r3, r7, r3
	bl ov28_02255094
	cmp r0, #0
	beq _02255494
	mov r0, #0xc
	mul r0, r4
	add r0, r6, r0
	ldrb r0, [r0, #0xe]
	cmp r0, #1
	beq _02255432
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #1
	bl ov28_0225522C
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl ov28_0225549C
	pop {r3, r4, r5, r6, r7, pc}
_02255432:
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #2
	bl ov28_0225522C
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl ov28_022555B4
	pop {r3, r4, r5, r6, r7, pc}
_02255448:
	add r0, r5, #0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, r4
	bne _02255494
	mov r1, #0xa1
	mov r3, #0x52
	lsl r1, r1, #2
	lsl r3, r3, #2
	ldr r0, [r5, r1]
	add r1, r1, #4
	add r7, r5, r3
	mov r3, #0x38
	mul r3, r4
	ldr r1, [r5, r1]
	mov r2, #8
	add r3, r7, r3
	bl ov28_02255094
	cmp r0, #0
	beq _02255494
	mov r0, #0xc
	mul r0, r4
	add r0, r6, r0
	ldrb r0, [r0, #0xe]
	cmp r0, #1
	beq _0225548A
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #3
	bl ov28_0225522C
	pop {r3, r4, r5, r6, r7, pc}
_0225548A:
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #4
	bl ov28_0225522C
_02255494:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255498: .word ov28_02255F44
	thumb_func_end ov28_022553B4

	thumb_func_start ov28_0225549C
ov28_0225549C: ; 0x0225549C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r2, #0
	add r6, r1, #0
	ldr r0, _022555AC ; =ov28_02255F58
	add r1, r4, #0
	bl ov28_022551BC
	add r0, r6, #0
	add r0, #0x4c
	ldrh r0, [r0]
	cmp r0, #0
	beq _0225559C
	mov r0, #0x52
	lsl r0, r0, #2
	add r7, r5, r0
	mov r0, #0x38
	mul r0, r4
	mov r1, #0xa1
	str r0, [sp]
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r3, [sp]
	ldr r1, [r5, r1]
	mov r2, #0x40
	add r3, r7, r3
	bl ov28_02255094
	cmp r0, #0
	beq _0225559C
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	cmp r0, #0
	beq _022554F0
	add r0, r5, #0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, r4
	bne _022555A6
_022554F0:
	mov r1, #0xa1
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r3, [sp]
	ldr r1, [r5, r1]
	mov r2, #8
	add r3, r7, r3
	bl ov28_02255094
	cmp r0, #0
	beq _02255516
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #3
	bl ov28_0225522C
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_02255516:
	mov r1, #0xa2
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	sub r1, r1, #4
	ldr r1, [r5, r1]
	lsl r0, r0, #0xc
	lsl r1, r1, #0xc
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	ldr r1, [sp]
	str r0, [sp, #0xc]
	add r0, sp, #4
	add r1, r7, r1
	add r2, r0, #0
	bl VEC_Subtract
	add r0, sp, #4
	add r1, r0, #0
	bl VEC_Normalize
	mov r0, #0xc
	add r7, r4, #0
	mul r7, r0
	add r6, #0xf
	ldrb r2, [r6, r7]
	ldr r0, _022555B0 ; =ov28_02255E90
	ldr r1, [sp, #4]
	ldrb r0, [r0, r2]
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	str r0, [sp, #4]
	ldrb r2, [r6, r7]
	ldr r0, _022555B0 ; =ov28_02255E90
	ldr r1, [sp, #8]
	ldrb r0, [r0, r2]
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	ldr r2, [sp, #4]
	str r0, [sp, #8]
	asr r1, r2, #3
	lsr r1, r1, #0x1c
	add r1, r2, r1
	asr r1, r1, #4
	str r1, [sp, #4]
	asr r1, r0, #3
	lsr r1, r1, #0x1c
	add r1, r0, r1
	asr r0, r1, #4
	str r0, [sp, #8]
	mov r0, #0x38
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x4f
	add r3, sp, #4
	lsl r0, r0, #2
	add r2, r1, r0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add sp, #0x10
	str r0, [r2]
	pop {r3, r4, r5, r6, r7, pc}
_0225559C:
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl ov28_0225522C
_022555A6:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022555AC: .word ov28_02255F58
_022555B0: .word ov28_02255E90
	thumb_func_end ov28_0225549C

	thumb_func_start ov28_022555B4
ov28_022555B4: ; 0x022555B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r2, #0
	add r4, r1, #0
	ldr r0, _02255688 ; =ov28_02255F6C
	add r1, r6, #0
	bl ov28_022551BC
	add r0, r4, #0
	add r0, #0x4c
	ldrh r0, [r0]
	cmp r0, #0
	beq _0225567A
	mov r0, #0x52
	lsl r0, r0, #2
	add r7, r5, r0
	mov r0, #0x38
	mul r0, r6
	mov r1, #0xa1
	str r0, [sp]
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r3, [sp]
	ldr r1, [r5, r1]
	mov r2, #0x40
	add r3, r7, r3
	bl ov28_02255094
	cmp r0, #0
	beq _0225567A
	mov r1, #0xa2
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	sub r1, r1, #4
	ldr r1, [r5, r1]
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	mov r0, #0
	lsl r1, r1, #0xc
	str r0, [sp, #0xc]
	ldr r0, [sp]
	str r1, [sp, #4]
	add r1, sp, #4
	add r0, r7, r0
	add r2, r1, #0
	bl VEC_Subtract
	add r0, sp, #4
	add r1, r0, #0
	bl VEC_Normalize
	mov r0, #0xc
	add r7, r6, #0
	mul r7, r0
	add r4, #0xf
	ldrb r2, [r4, r7]
	ldr r0, _0225568C ; =ov28_02255E8C
	ldr r1, [sp, #4]
	ldrb r0, [r0, r2]
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	str r0, [sp, #4]
	ldrb r2, [r4, r7]
	ldr r0, _0225568C ; =ov28_02255E8C
	ldr r1, [sp, #8]
	ldrb r0, [r0, r2]
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	ldr r2, [sp, #4]
	str r0, [sp, #8]
	asr r1, r2, #3
	lsr r1, r1, #0x1c
	add r1, r2, r1
	asr r1, r1, #4
	str r1, [sp, #4]
	asr r1, r0, #3
	lsr r1, r1, #0x1c
	add r1, r0, r1
	asr r0, r1, #4
	str r0, [sp, #8]
	mov r0, #0x38
	mul r0, r6
	add r1, r5, r0
	mov r0, #0x4f
	add r3, sp, #4
	lsl r0, r0, #2
	add r2, r1, r0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add sp, #0x10
	str r0, [r2]
	pop {r3, r4, r5, r6, r7, pc}
_0225567A:
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0
	bl ov28_0225522C
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02255688: .word ov28_02255F6C
_0225568C: .word ov28_02255E8C
	thumb_func_end ov28_022555B4

	thumb_func_start ov28_02255690
ov28_02255690: ; 0x02255690
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r7, r2, #0
	add r4, r1, #0
	ldr r0, _02255764 ; =ov28_02255F80
	add r1, r7, #0
	bl ov28_022551BC
	add r4, #0x4c
	ldrh r0, [r4]
	cmp r0, #0
	beq _02255756
	mov r1, #0xa2
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r4, r7, #0
	lsl r2, r0, #0xc
	sub r0, r1, #4
	ldr r0, [r5, r0]
	lsl r0, r0, #0xc
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #0x38
	mul r4, r0
	mov r0, #0x52
	lsl r0, r0, #2
	add r6, r5, r0
	str r2, [sp, #4]
	sub r0, r1, #4
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	mov r2, #8
	add r3, r6, r4
	bl ov28_02255094
	cmp r0, #0
	beq _02255732
	add r0, sp, #0
	add r1, r6, r4
	add r2, r0, #0
	bl VEC_Subtract
	add r0, sp, #0
	bl VEC_Mag
	mov r1, #6
	lsl r1, r1, #8
	cmp r0, r1
	ble _02255704
	add r0, sp, #0
	add r1, r0, #0
	bl VEC_Normalize
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
_02255704:
	ldr r1, [sp]
	add r3, sp, #0
	asr r0, r1, #3
	lsr r0, r0, #0x1c
	add r0, r1, r0
	asr r0, r0, #4
	ldr r1, [sp, #4]
	str r0, [sp]
	asr r0, r1, #3
	lsr r0, r0, #0x1c
	add r0, r1, r0
	asr r0, r0, #4
	str r0, [sp, #4]
	mov r0, #0x4f
	add r1, r5, r4
	lsl r0, r0, #2
	add r2, r1, r0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add sp, #0xc
	str r0, [r2]
	pop {r4, r5, r6, r7, pc}
_02255732:
	mov r1, #0xa1
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x40
	add r3, r6, r4
	bl ov28_02255094
	cmp r0, #0
	beq _02255756
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #1
	bl ov28_0225522C
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_02255756:
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0
	bl ov28_0225522C
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02255764: .word ov28_02255F80
	thumb_func_end ov28_02255690

	thumb_func_start ov28_02255768
ov28_02255768: ; 0x02255768
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r2, #0
	add r4, r1, #0
	ldr r0, _02255808 ; =ov28_02255F94
	add r1, r7, #0
	bl ov28_022551BC
	add r4, #0x4c
	ldrh r0, [r4]
	cmp r0, #0
	beq _022557D8
	mov r0, #0x38
	add r4, r7, #0
	mul r4, r0
	mov r0, #0x52
	mov r1, #0xa1
	lsl r0, r0, #2
	add r6, r5, r0
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #8
	add r3, r6, r4
	bl ov28_02255094
	cmp r0, #0
	beq _022557B6
	mov r1, #0x4f
	lsl r1, r1, #2
	mov r3, #0
	add r2, r5, r4
	str r3, [r2, r1]
	add r0, r1, #4
	str r3, [r2, r0]
	add r1, #8
	str r3, [r2, r1]
	pop {r3, r4, r5, r6, r7, pc}
_022557B6:
	mov r1, #0xa1
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x40
	add r3, r6, r4
	bl ov28_02255094
	cmp r0, #0
	beq _022557FA
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #2
	bl ov28_0225522C
	pop {r3, r4, r5, r6, r7, pc}
_022557D8:
	mov r0, #0x38
	add r4, r7, #0
	mul r4, r0
	mov r0, #0x4f
	lsl r0, r0, #2
	add r0, r5, r0
	add r0, r0, r4
	bl ov28_022553A0
	cmp r0, #0
	beq _022557FA
	mov r0, #0x4f
	lsl r0, r0, #2
	add r0, r5, r0
	add r0, r0, r4
	bl ov28_02254E54
_022557FA:
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0
	bl ov28_0225522C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255808: .word ov28_02255F94
	thumb_func_end ov28_02255768

	thumb_func_start ov28_0225580C
ov28_0225580C: ; 0x0225580C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x4d
	lsl r0, r0, #2
	add r1, r5, r0
	add r6, r2, #0
	mov r0, #0x38
	mul r0, r6
	add r4, r1, r0
	ldr r0, _02255918 ; =ov28_02255FA8
	add r1, r6, #0
	bl ov28_022551BC
	add r0, r4, #0
	add r0, #0x34
	ldrb r0, [r0]
	cmp r0, #0
	beq _02255836
	cmp r0, #1
	beq _0225585A
	pop {r4, r5, r6, pc}
_02255836:
	mov r0, #0
	str r0, [r4, #8]
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	add r0, r5, #0
	add r1, r6, #0
	bl ov28_02255318
	ldr r0, _0225591C ; =0x00000669
	bl Poketch_PlaySoundEffect
	add r0, r4, #0
	add r0, #0x34
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x34
	strb r1, [r0]
_0225585A:
	add r0, r4, #0
	add r0, #0x35
	ldrb r1, [r0]
	add r0, r4, #0
	add r0, #0x35
	add r1, #8
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x36
	ldrb r0, [r0]
	cmp r0, #0
	bne _0225588C
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #0x8c
	bls _0225588C
	add r0, r5, #0
	add r1, r6, #0
	bl ov28_02255344
	add r0, r4, #0
	mov r1, #1
	add r0, #0x36
	strb r1, [r0]
_0225588C:
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #0xb4
	bls _022558A6
	add r0, r4, #0
	mov r1, #0xb4
	add r0, #0x35
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #2
	add r0, #0x36
	strb r1, [r0]
_022558A6:
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	bl Sin
	mov r1, #0x13
	mvn r1, r1
	mul r1, r0
	mov r0, #0
	str r0, [r4, #0x20]
	str r1, [r4, #0x24]
	str r0, [r4, #0x28]
	add r0, r4, #0
	add r1, r4, #0
	add r2, r5, #0
	add r0, #0x14
	add r1, #0x20
	add r2, #0xa4
	bl VEC_Add
	add r1, r5, #0
	add r2, r5, #0
	add r1, #0xa4
	add r2, #0xa8
	ldr r0, [r4]
	ldr r1, [r1]
	ldr r2, [r2]
	bl ov20_02253F64
	mov r2, #2
	ldr r3, [r4, #0x18]
	lsl r2, r2, #0xe
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x14]
	add r2, r3, r2
	bl ov20_02253F64
	add r0, r4, #0
	add r0, #0x36
	ldrb r0, [r0]
	cmp r0, #2
	bne _02255916
	add r4, #8
	add r0, r4, #0
	bl ov28_02254E54
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0
	bl ov28_0225522C
	mov r0, #1
	lsl r0, r0, #8
	ldr r1, [r5, r0]
	sub r1, r1, #1
	str r1, [r5, r0]
_02255916:
	pop {r4, r5, r6, pc}
	.align 2, 0
_02255918: .word ov28_02255FA8
_0225591C: .word 0x00000669
	thumb_func_end ov28_0225580C

	thumb_func_start ov28_02255920
ov28_02255920: ; 0x02255920
	push {r4, r5, r6, r7, lr}
	sub sp, #0x74
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0x10
	str r1, [sp, #4]
	str r0, [sp, #0x34]
_0225592E:
	mov r0, #0
	str r0, [sp, #0x28]
	str r0, [sp, #0x24]
	ldr r0, [sp, #4]
	ldr r4, [sp, #0x34]
	ldr r0, [r0]
	str r0, [sp, #0x10]
	cmp r0, #0
	ble _02255974
	mov r1, #0x52
	ldr r5, [sp]
	ldr r0, [sp]
	lsl r1, r1, #2
	add r7, r0, r1
	sub r1, #0xc
	add r5, #0x5c
	add r6, r0, r1
_02255950:
	ldr r0, [sp, #0x34]
	add r1, r6, #0
	add r2, r7, #0
	add r3, r5, #0
	bl VEC_MultAdd
	ldr r0, [sp, #0x24]
	add r5, #0xc
	add r0, r0, #1
	str r0, [sp, #0x24]
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x24]
	ldr r0, [r0]
	add r7, #0x38
	add r6, #0x38
	str r0, [sp, #0x10]
	cmp r1, r0
	blt _02255950
_02255974:
	ldr r0, [sp, #0x10]
	mov r5, #0
	cmp r0, #0
	ble _02255A3E
	ldr r0, [sp]
	str r0, [sp, #0x14]
	add r6, r0, #0
_02255982:
	ldr r0, [sp, #0x14]
	ldr r7, [r0, #0x5c]
	ldr r0, _02255CB8 ; =0xFFFF6000
	cmp r7, r0
	bge _022559AE
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	cmp r1, #0
	beq _022559AE
	mov r0, #0xa
	lsl r0, r0, #0xc
	add r0, r7, r0
	bl _s32_div_f
	sub r1, r4, r0
	cmp r1, r4
	bge _022559AE
	mov r0, #2
	str r0, [sp, #0x28]
	str r5, [sp, #0x30]
	add r4, r1, #0
_022559AE:
	mov r0, #0xd9
	lsl r0, r0, #0xc
	cmp r7, r0
	ble _022559D8
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	cmp r1, #0
	beq _022559D8
	mov r0, #0xd9
	lsl r0, r0, #0xc
	sub r0, r7, r0
	bl _s32_div_f
	sub r1, r4, r0
	cmp r1, r4
	bge _022559D8
	mov r0, #3
	str r0, [sp, #0x28]
	str r5, [sp, #0x30]
	add r4, r1, #0
_022559D8:
	ldr r0, [sp, #0x14]
	ldr r7, [r0, #0x60]
	ldr r0, _02255CBC ; =0xFFFEA000
	cmp r7, r0
	bge _02255A04
	mov r0, #5
	lsl r0, r0, #6
	ldr r1, [r6, r0]
	cmp r1, #0
	beq _02255A04
	mov r0, #0x16
	lsl r0, r0, #0xc
	add r0, r7, r0
	bl _s32_div_f
	sub r1, r4, r0
	cmp r1, r4
	bge _02255A04
	mov r0, #4
	str r0, [sp, #0x28]
	str r5, [sp, #0x30]
	add r4, r1, #0
_02255A04:
	mov r0, #0xb7
	lsl r0, r0, #0xc
	cmp r7, r0
	ble _02255A2E
	mov r0, #5
	lsl r0, r0, #6
	ldr r1, [r6, r0]
	cmp r1, #0
	beq _02255A2E
	mov r0, #0xb7
	lsl r0, r0, #0xc
	sub r0, r7, r0
	bl _s32_div_f
	sub r1, r4, r0
	cmp r1, r4
	bge _02255A2E
	mov r0, #5
	str r0, [sp, #0x28]
	str r5, [sp, #0x30]
	add r4, r1, #0
_02255A2E:
	ldr r0, [sp, #0x14]
	add r5, r5, #1
	add r0, #0xc
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r6, #0x38
	cmp r5, r0
	blt _02255982
_02255A3E:
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x10]
	cmp r0, #0
	ble _02255AEE
	ldr r0, [sp]
	mov r1, #0x4f
	str r0, [sp, #0x1c]
	add r0, #0x5c
	str r0, [sp, #0x1c]
	ldr r0, [sp]
	lsl r1, r1, #2
	add r0, r0, r1
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x3c]
_02255A62:
	ldr r0, [sp, #0x20]
	mov r5, #0
	cmp r0, #0
	ble _02255AD0
	ldr r7, [sp, #0x38]
	ldr r6, [sp, #0x3c]
_02255A6E:
	ldr r1, [sp, #0x1c]
	add r0, r7, #0
	add r2, sp, #0x68
	bl VEC_Subtract
	add r0, sp, #0x68
	bl VEC_Mag
	mov r1, #2
	lsl r1, r1, #0x10
	str r0, [sp, #0x40]
	cmp r0, r1
	bge _02255AC4
	add r0, sp, #0x68
	add r1, sp, #0x5c
	bl VEC_Normalize
	ldr r1, [sp, #0x18]
	add r0, r6, #0
	add r2, sp, #0x50
	bl VEC_Subtract
	add r0, sp, #0x50
	add r1, sp, #0x5c
	bl VEC_DotProduct
	add r2, r0, #0
	mov r1, #2
	ldr r0, [sp, #0x40]
	lsl r1, r1, #0x10
	sub r0, r1, r0
	neg r1, r2
	bl _s32_div_f
	sub r0, r4, r0
	cmp r0, r4
	bge _02255AC4
	mov r1, #1
	str r1, [sp, #0x28]
	ldr r1, [sp, #0x20]
	str r5, [sp, #0x30]
	str r1, [sp, #0x2c]
	add r4, r0, #0
_02255AC4:
	ldr r0, [sp, #0x20]
	add r5, r5, #1
	add r7, #0xc
	add r6, #0x38
	cmp r5, r0
	blt _02255A6E
_02255AD0:
	ldr r0, [sp, #0x1c]
	add r0, #0xc
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r0, #0x38
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x20]
	ldr r0, [r0]
	str r0, [sp, #0x10]
	cmp r1, r0
	blt _02255A62
_02255AEE:
	cmp r4, #0
	bgt _02255AF4
	b _02255DC8
_02255AF4:
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x10]
	cmp r0, #0
	ble _02255B2E
	mov r1, #0x52
	ldr r0, [sp]
	lsl r1, r1, #2
	add r7, r0, r1
	sub r1, #0xc
	add r6, r7, #0
	add r5, r0, r1
_02255B0C:
	add r0, r4, #0
	add r1, r5, #0
	add r2, r6, #0
	add r3, r7, #0
	bl VEC_MultAdd
	ldr r0, [sp, #8]
	add r7, #0x38
	add r0, r0, #1
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	add r6, #0x38
	ldr r1, [r0]
	ldr r0, [sp, #8]
	add r5, #0x38
	cmp r0, r1
	blt _02255B0C
_02255B2E:
	ldr r0, [sp, #0x28]
	cmp r0, #5
	bls _02255B36
	b _02255DBA
_02255B36:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02255B42: ; jump table
	.short _02255DBA - _02255B42 - 2 ; case 0
	.short _02255B4E - _02255B42 - 2 ; case 1
	.short _02255D7C - _02255B42 - 2 ; case 2
	.short _02255D7C - _02255B42 - 2 ; case 3
	.short _02255D9C - _02255B42 - 2 ; case 4
	.short _02255D9C - _02255B42 - 2 ; case 5
_02255B4E:
	ldr r1, [sp, #0x30]
	mov r0, #0x38
	add r6, r1, #0
	ldr r1, [sp]
	mul r6, r0
	add r1, r1, r6
	str r1, [sp, #0xc]
	mov r1, #0x16
	ldr r2, [sp, #0xc]
	lsl r1, r1, #4
	ldrb r2, [r2, r1]
	cmp r2, #3
	bne _02255C1C
	ldr r2, [sp, #0x2c]
	sub r1, #0x24
	add r7, r2, #0
	mul r7, r0
	ldr r0, [sp]
	add r0, r0, r1
	add r5, r0, r7
	ldr r0, [r0, r7]
	cmp r0, #0
	bne _02255B82
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _02255B8E
_02255B82:
	ldr r0, [sp]
	ldr r1, _02255CC0 ; =0x00000166
	add r0, r0, r7
	ldrb r1, [r0, r1]
	cmp r1, #0
	beq _02255C02
_02255B8E:
	mov r1, #0x52
	ldr r0, [sp]
	lsl r1, r1, #2
	add r1, r0, r1
	add r0, r1, r7
	add r1, r1, r6
	add r2, sp, #0x68
	bl VEC_Subtract
	add r0, sp, #0x68
	add r1, sp, #0x5c
	bl VEC_Normalize
	ldr r0, [sp, #0x5c]
	ldr r2, _02255CC4 ; =0x0000019A
	asr r1, r0, #0x1f
	mov r3, #0
	bl _ll_mul
	add r2, r0, #0
	mov r0, #2
	mov r3, #0
	lsl r0, r0, #0xa
	add r0, r2, r0
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	str r0, [r5]
	ldr r0, [sp, #0x60]
	ldr r2, _02255CC4 ; =0x0000019A
	asr r1, r0, #0x1f
	bl _ll_mul
	add r2, r0, #0
	mov r0, #2
	mov r3, #0
	lsl r0, r0, #0xa
	add r0, r2, r0
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	str r0, [r5, #4]
	ldr r0, [sp]
	ldr r1, _02255CC0 ; =0x00000166
	add r0, r0, r7
	mov r2, #1
	strb r2, [r0, r1]
	ldr r1, [sp, #0x30]
	cmp r1, #1
	bne _02255BFC
	ldr r1, [sp, #0x2c]
	cmp r1, #2
	beq _02255C14
_02255BFC:
	ldr r1, [sp, #0x2c]
	cmp r1, #1
	b _02255C14
_02255C02:
	ldr r2, [r5]
	mov r1, #0
	mvn r1, r1
	add r3, r2, #0
	mul r3, r1
	str r3, [r5]
	ldr r2, [r5, #4]
	mul r1, r2
	str r1, [r5, #4]
_02255C14:
	ldr r1, _02255CC8 ; =0x00000163
	mov r2, #0x14
	strb r2, [r0, r1]
	b _02255DBA
_02255C1C:
	ldr r2, [sp, #0x2c]
	add r7, r2, #0
	mul r7, r0
	ldr r0, [sp]
	add r0, r0, r7
	ldrb r0, [r0, r1]
	cmp r0, #3
	bne _02255CE8
	ldr r0, [sp]
	sub r1, #0x24
	add r0, r0, r1
	add r5, r0, r6
	ldr r0, [r0, r6]
	cmp r0, #0
	bne _02255C40
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _02255C4A
_02255C40:
	ldr r1, _02255CC0 ; =0x00000166
	ldr r0, [sp, #0xc]
	ldrb r0, [r0, r1]
	cmp r0, #0
	beq _02255CCC
_02255C4A:
	mov r1, #0x52
	ldr r0, [sp]
	lsl r1, r1, #2
	add r1, r0, r1
	add r0, r1, r6
	add r1, r1, r7
	add r2, sp, #0x68
	bl VEC_Subtract
	add r0, sp, #0x68
	add r1, sp, #0x5c
	bl VEC_Normalize
	ldr r0, [sp, #0x5c]
	ldr r2, _02255CC4 ; =0x0000019A
	asr r1, r0, #0x1f
	mov r3, #0
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	str r1, [r5]
	ldr r0, [sp, #0x60]
	ldr r2, _02255CC4 ; =0x0000019A
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	str r1, [r5, #4]
	ldr r1, _02255CC0 ; =0x00000166
	ldr r0, [sp, #0xc]
	mov r2, #1
	strb r2, [r0, r1]
	ldr r0, [sp, #0x30]
	cmp r0, #1
	bne _02255CB2
	ldr r0, [sp, #0x2c]
	cmp r0, #2
	beq _02255CDE
_02255CB2:
	ldr r0, [sp, #0x2c]
	cmp r0, #1
	b _02255CDE
	.align 2, 0
_02255CB8: .word 0xFFFF6000
_02255CBC: .word 0xFFFEA000
_02255CC0: .word 0x00000166
_02255CC4: .word 0x0000019A
_02255CC8: .word 0x00000163
_02255CCC:
	ldr r1, [r5]
	mov r0, #0
	mvn r0, r0
	add r2, r1, #0
	mul r2, r0
	str r2, [r5]
	ldr r1, [r5, #4]
	mul r0, r1
	str r0, [r5, #4]
_02255CDE:
	ldr r1, _02255E74 ; =0x00000163
	ldr r0, [sp, #0xc]
	mov r2, #0x14
	strb r2, [r0, r1]
	b _02255DBA
_02255CE8:
	ldr r0, [sp]
	sub r1, #0x18
	add r1, r0, r1
	add r0, r1, r6
	add r1, r1, r7
	add r2, sp, #0x68
	bl VEC_Subtract
	add r0, sp, #0x68
	bl VEC_Mag
	add r0, sp, #0x68
	add r1, sp, #0x5c
	bl VEC_Normalize
	mov r1, #0x4f
	ldr r0, [sp]
	lsl r1, r1, #2
	add r0, r0, r1
	str r0, [sp, #0x4c]
	ldr r1, [sp, #0x4c]
	add r0, r0, r6
	add r1, r1, r7
	add r2, sp, #0x50
	bl VEC_Subtract
	add r0, sp, #0x50
	add r1, sp, #0x5c
	bl VEC_DotProduct
	mov r5, #0x4f
	ldr r2, [sp, #0x4c]
	str r0, [sp, #0x44]
	ldr r3, [sp]
	lsl r5, r5, #2
	add r3, r3, r5
	neg r0, r0
	add r1, sp, #0x5c
	add r2, r2, r6
	add r3, r3, r6
	bl VEC_MultAdd
	ldr r3, [sp]
	ldr r2, [sp, #0x4c]
	add r3, r3, r5
	ldr r0, [sp, #0x44]
	add r1, sp, #0x5c
	add r2, r2, r7
	add r3, r3, r7
	bl VEC_MultAdd
	ldr r0, [sp]
	add r1, r5, #0
	ldr r3, [sp]
	add r1, #0x27
	add r0, r0, r6
	mov r2, #0x14
	strb r2, [r0, r1]
	add r3, r3, r7
	strb r2, [r3, r1]
	mov r2, #0
	add r5, r1, #3
	strb r2, [r0, r5]
	add r0, r5, #0
	strb r2, [r3, r0]
	ldr r0, [sp, #0x30]
	cmp r0, #1
	bne _02255D76
	ldr r0, [sp, #0x2c]
	cmp r0, #2
	beq _02255DBA
_02255D76:
	ldr r0, [sp, #0x2c]
	cmp r0, #1
	b _02255DBA
_02255D7C:
	ldr r0, [sp, #0x30]
	mov r1, #0x38
	add r2, r0, #0
	mul r2, r1
	ldr r0, [sp]
	sub r1, #0x39
	add r0, r0, r2
	mov r2, #0x4f
	lsl r2, r2, #2
	ldr r3, [r0, r2]
	mul r1, r3
	str r1, [r0, r2]
	mov r1, #0
	add r2, #0x2a
	strb r1, [r0, r2]
	b _02255DBA
_02255D9C:
	ldr r0, [sp, #0x30]
	mov r1, #0x38
	add r2, r0, #0
	mul r2, r1
	ldr r0, [sp]
	sub r1, #0x39
	add r0, r0, r2
	mov r2, #5
	lsl r2, r2, #6
	ldr r3, [r0, r2]
	mul r1, r3
	str r1, [r0, r2]
	mov r1, #0
	add r2, #0x26
	strb r1, [r0, r2]
_02255DBA:
	ldr r0, [sp, #0x34]
	sub r0, r0, r4
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x28]
	cmp r0, #0
	beq _02255DC8
	b _0225592E
_02255DC8:
	ldr r0, [sp, #4]
	mov r5, #0
	ldr r0, [r0]
	cmp r0, #0
	ble _02255E6E
	ldr r4, [sp]
	mov r1, #0x55
	add r0, r4, #0
	lsl r1, r1, #2
	add r7, r0, r1
	sub r1, #0xc
	add r6, r0, r1
	str r0, [sp, #0x48]
	add r0, #0xa4
	str r0, [sp, #0x48]
_02255DE6:
	mov r0, #0x16
	lsl r0, r0, #4
	ldrb r0, [r4, r0]
	cmp r0, #3
	bhs _02255E22
	mov r0, #0x59
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _02255E08
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl ov20_02253F28
	b _02255E22
_02255E08:
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	ble _02255E16
	mov r1, #7
	b _02255E18
_02255E16:
	mov r1, #6
_02255E18:
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov20_02253F28
_02255E22:
	ldr r2, [sp, #0x48]
	add r0, r6, #0
	add r1, r7, #0
	bl VEC_Add
	ldr r1, [sp]
	ldr r2, [sp]
	mov r0, #0x4d
	lsl r0, r0, #2
	add r1, #0xa4
	add r2, #0xa8
	ldr r0, [r4, r0]
	ldr r1, [r1]
	ldr r2, [r2]
	bl ov20_02253F64
	mov r2, #0x53
	mov r0, #0x4e
	mov r1, #0x52
	lsl r2, r2, #2
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r3, [r4, r2]
	mov r2, #2
	lsl r2, r2, #0xe
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	add r2, r3, r2
	bl ov20_02253F64
	ldr r0, [sp, #4]
	add r5, r5, #1
	ldr r0, [r0]
	add r4, #0x38
	add r7, #0x38
	add r6, #0x38
	cmp r5, r0
	blt _02255DE6
_02255E6E:
	add sp, #0x74
	pop {r4, r5, r6, r7, pc}
	nop
_02255E74: .word 0x00000163
	thumb_func_end ov28_02255920

	.section .rodata

	.global ov28_02255E78
ov28_02255E78: ; 0x02255E78
	.byte 0x01, 0x23, 0x46, 0x96, 0xC8, 0xFF, 0x00, 0x00

	.global ov28_02255E80
ov28_02255E80: ; 0x02255E80
	.word ov28_02254A10, ov28_02254A50, ov28_02254AC0

	.global ov28_02255E8C
ov28_02255E8C: ; 0x02255E8C
	.byte 0x64, 0x96, 0xAF, 0xC8

	.global ov28_02255E90
ov28_02255E90: ; 0x02255E90
	.byte 0x64, 0x96, 0xAF, 0xC8

	.global ov28_02255E94
ov28_02255E94: ; 0x02255E94
	.word ov28_022550C4, ov28_022550E4, ov28_02255128, ov28_0225513C
	.word ov28_02255188

	.global ov28_02255EA8
ov28_02255EA8: ; 0x02255EA8
	.word ov28_022553B4, ov28_0225549C, ov28_022555B4, ov28_02255690
	.word ov28_02255768, ov28_0225580C

	.global ov28_02255EC0
ov28_02255EC0: ; 0x02255EC0
	.short 0x30, 0x2C, 0xB0, 0x2C, 0x30, 0x5C, 0xB0, 0x5C
	.short 0x30, 0x8C, 0xB0, 0x8C

	.global ov28_02255ED8
ov28_02255ED8: ; 0x02255ED8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov28_02255EF4
ov28_02255EF4: ; 0x02255EF4
	.word 0x00, ov28_02254C18, 0x00
	.word 0x01, ov28_02254F18, 0x00
	.word 0x00, 0x00000000, 0x00

	.section .data

	.global ov28_02255F20
ov28_02255F20: ; 0x02255F20
	.asciz "icon[%d] REF[%d]\n"

	.balign 4
	.global ov28_02255F34
ov28_02255F34: ; 0x02255F34
	.asciz "------------\n"

	.balign 4
	.global ov28_02255F44
ov28_02255F44: ; 0x02255F44
	.asciz " icon[%d] Default\n"

	.balign 4
	.global ov28_02255F58
ov28_02255F58: ; 0x02255F58
	.asciz " icon[%d] ReaLike\n"

	.balign 4
	.global ov28_02255F6C
ov28_02255F6C: ; 0x02255F6C
	.asciz " icon[%d] ReaHate\n"

	.balign 4
	.global ov28_02255F80
ov28_02255F80: ; 0x02255F80
	.asciz " icon[%d] TcgLike\n"

	.balign 4
	.global ov28_02255F94
ov28_02255F94: ; 0x02255F94
	.asciz " icon[%d] TchHate\n"

	.balign 4
	.global ov28_02255FA8
ov28_02255FA8: ; 0x02255FA8
	.asciz " icon[%d] Reset!!\n"
