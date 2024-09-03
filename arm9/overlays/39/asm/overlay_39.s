	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov39_02254854
ov39_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x68
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl ov39_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =ov39_02254998
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
_02254898: .word ov39_02254998
	thumb_func_end ov39_02254854

	thumb_func_start ov39_0225489C
ov39_0225489C: ; 0x0225489C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp, #4]
	add r0, r1, #0
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	bl ov20_02252C40
	bl SaveArray_Party_Get
	str r0, [sp, #0x10]
	bl Party_GetCount
	ldr r1, [sp, #4]
	mov r6, #0
	add r1, #0x34
	strb r0, [r1]
	ldr r0, [sp, #4]
	add r0, #0x34
	ldrb r0, [r0]
	cmp r0, #0
	ble _02254906
	ldr r4, [sp, #4]
	add r5, r4, #0
_022548CC:
	ldr r0, [sp, #0x10]
	add r1, r6, #0
	bl Party_GetMonByIndex
	add r7, r0, #0
	bl sub_0206B688
	str r0, [r4, #4]
	add r0, r7, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	strh r0, [r5, #0x1c]
	add r0, r7, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	strh r0, [r5, #0x28]
	ldr r0, [sp, #4]
	str r7, [r4, #0x48]
	add r0, #0x34
	ldrb r0, [r0]
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #2
	cmp r6, r0
	blt _022548CC
_02254906:
	ldr r0, [sp, #4]
	mov r1, #0
	add r0, #0x36
	strb r1, [r0]
	ldr r0, [sp, #4]
	add r0, #0x34
	ldrb r0, [r0]
	cmp r0, #1
	bls _0225491A
	mov r1, #1
_0225491A:
	ldr r0, [sp, #4]
	ldr r2, [sp, #0xc]
	add r0, #0x37
	strb r1, [r0]
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	add r0, #0x38
	add r1, r1, #4
	bl ov39_02254C1C
	cmp r0, #0
	beq _02254964
	ldr r0, [sp, #4]
	mov r1, #0
	strb r1, [r0]
	strb r1, [r0, #1]
	strb r1, [r0, #2]
	mov r0, #8
	str r0, [sp]
	ldr r0, _0225496C ; =ov39_02255300
	ldr r2, _02254970 ; =ov39_0225498C
	ldr r3, [sp, #4]
	mov r1, #3
	bl ov20_02254130
	ldr r1, [sp, #4]
	str r0, [r1, #0x40]
	ldr r0, [sp, #4]
	mov r1, #0
	add r0, #0x46
	strh r1, [r0]
	ldr r1, [sp, #8]
	ldr r0, [sp, #4]
	add sp, #0x14
	str r1, [r0, #0x3c]
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02254964:
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0225496C: .word ov39_02255300
_02254970: .word ov39_0225498C
	thumb_func_end ov39_0225489C

	thumb_func_start ov39_02254974
ov39_02254974: ; 0x02254974
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	bl ov20_02254198
	ldr r0, [r4, #0x38]
	bl ov39_02254C58
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end ov39_02254974

	thumb_func_start ov39_0225498C
ov39_0225498C: ; 0x0225498C
	add r2, r3, #0
	add r2, #0x44
	strh r0, [r2]
	add r3, #0x46
	strh r1, [r3]
	bx lr
	thumb_func_end ov39_0225498C

	thumb_func_start ov39_02254998
ov39_02254998: ; 0x02254998
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _022549CE
	ldr r0, [r4, #0x3c]
	ldr r1, [r4, #0x40]
	bl ov20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _022549D0 ; =ov39_0225530C
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _022549CE
	add r0, r4, #0
	bl ov39_02254974
	add r0, r5, #0
	bl sub_0200CAB4
	ldr r0, [r4, #0x3c]
	bl ov20_022529A0
_022549CE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022549D0: .word ov39_0225530C
	thumb_func_end ov39_02254998

	thumb_func_start ov39_022549D4
ov39_022549D4: ; 0x022549D4
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end ov39_022549D4

	thumb_func_start ov39_022549DC
ov39_022549DC: ; 0x022549DC
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _022549E4
	b _022549E6
_022549E4:
	mov r1, #2
_022549E6:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end ov39_022549DC

	thumb_func_start ov39_022549F0
ov39_022549F0: ; 0x022549F0
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A00
	cmp r0, #1
	beq _02254A10
	b _02254A2A
_02254A00:
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl ov39_02254DA4
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A2A
_02254A10:
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl ov39_02254DC8
	cmp r0, #0
	beq _02254A2A
	ldr r0, [r4, #0x3c]
	bl ov20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl ov39_022549DC
_02254A2A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov39_022549F0

	thumb_func_start ov39_02254A30
ov39_02254A30: ; 0x02254A30
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254A44
	mov r1, #2
	bl ov39_022549DC
	mov r0, #0
	pop {r4, pc}
_02254A44:
	ldrb r1, [r4, #1]
	cmp r1, #3
	bhi _02254B48
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02254A56: ; jump table
	.short _02254A5E - _02254A56 - 2 ; case 0
	.short _02254ACC - _02254A56 - 2 ; case 1
	.short _02254ADC - _02254A56 - 2 ; case 2
	.short _02254B38 - _02254A56 - 2 ; case 3
_02254A5E:
	add r1, r4, #0
	add r1, #0x46
	ldrh r1, [r1]
	cmp r1, #1
	bne _02254B48
	add r1, r4, #0
	add r1, #0x44
	ldrh r1, [r1]
	cmp r1, #0
	beq _02254AA8
	cmp r1, #1
	beq _02254A7C
	cmp r1, #2
	beq _02254A92
	b _02254AC4
_02254A7C:
	bl ov39_02254B50
	cmp r0, #0
	beq _02254AC4
	ldr r0, [r4, #0x38]
	mov r1, #4
	bl ov39_02254DA4
	mov r0, #1
	strb r0, [r4, #1]
	b _02254AC4
_02254A92:
	bl ov39_02254B9C
	cmp r0, #0
	beq _02254AC4
	ldr r0, [r4, #0x38]
	mov r1, #5
	bl ov39_02254DA4
	mov r0, #1
	strb r0, [r4, #1]
	b _02254AC4
_02254AA8:
	add r0, #0x34
	ldrb r0, [r0]
	cmp r0, #1
	bls _02254ABE
	ldr r0, [r4, #0x38]
	mov r1, #2
	bl ov39_02254DA4
	mov r0, #2
	strb r0, [r4, #1]
	b _02254AC4
_02254ABE:
	ldr r0, _02254B4C ; =0x0000066E
	bl Poketch_PlaySoundEffect
_02254AC4:
	mov r0, #0
	add r4, #0x46
	strh r0, [r4]
	b _02254B48
_02254ACC:
	ldr r0, [r4, #0x38]
	bl ov39_02254DD4
	cmp r0, #0
	beq _02254B48
	mov r0, #0
	strb r0, [r4, #1]
	b _02254B48
_02254ADC:
	add r0, #0x46
	ldrh r0, [r0]
	cmp r0, #2
	bne _02254AF2
	ldr r0, [r4, #0x38]
	mov r1, #3
	bl ov39_02254DA4
	mov r0, #0
	strb r0, [r4, #1]
	b _02254B48
_02254AF2:
	cmp r0, #3
	bne _02254B48
	add r0, r4, #0
	add r0, #0x36
	ldrb r0, [r0]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x48]
	str r0, [r4, #0x60]
	add r0, r4, #0
	add r0, #0x37
	ldrb r0, [r0]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x48]
	str r0, [r4, #0x64]
	add r0, r4, #0
	add r0, #0x60
	bl ov05_021ED9B4
	add r1, r4, #0
	add r1, #0x35
	strb r0, [r1]
	ldr r0, [r4, #0x38]
	mov r1, #3
	bl ov39_02254DA4
	ldr r0, [r4, #0x38]
	mov r1, #6
	bl ov39_02254DA4
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254B48
_02254B38:
	ldr r0, [r4, #0x38]
	mov r1, #6
	bl ov39_02254DC8
	cmp r0, #0
	beq _02254B48
	mov r0, #0
	strb r0, [r4, #1]
_02254B48:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02254B4C: .word 0x0000066E
	thumb_func_end ov39_02254A30

	thumb_func_start ov39_02254B50
ov39_02254B50: ; 0x02254B50
	push {r3, r4}
	add r1, r0, #0
	add r1, #0x34
	ldrb r1, [r1]
	cmp r1, #2
	bls _02254B94
	add r2, r0, #0
	mov r1, #0
	add r2, #0x36
_02254B62:
	ldrb r3, [r2]
	add r3, r3, #1
	strb r3, [r2]
	add r3, r0, #0
	add r3, #0x36
	ldrb r4, [r3]
	add r3, r0, #0
	add r3, #0x34
	ldrb r3, [r3]
	cmp r4, r3
	blo _02254B7E
	add r3, r0, #0
	add r3, #0x36
	strb r1, [r3]
_02254B7E:
	add r3, r0, #0
	add r3, #0x36
	ldrb r4, [r3]
	add r3, r0, #0
	add r3, #0x37
	ldrb r3, [r3]
	cmp r4, r3
	beq _02254B62
	mov r0, #1
	pop {r3, r4}
	bx lr
_02254B94:
	mov r0, #0
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end ov39_02254B50

	thumb_func_start ov39_02254B9C
ov39_02254B9C: ; 0x02254B9C
	push {r3, r4}
	add r1, r0, #0
	add r1, #0x34
	ldrb r1, [r1]
	cmp r1, #2
	bls _02254BE0
	add r2, r0, #0
	mov r1, #0
	add r2, #0x37
_02254BAE:
	ldrb r3, [r2]
	add r3, r3, #1
	strb r3, [r2]
	add r3, r0, #0
	add r3, #0x37
	ldrb r4, [r3]
	add r3, r0, #0
	add r3, #0x34
	ldrb r3, [r3]
	cmp r4, r3
	blo _02254BCA
	add r3, r0, #0
	add r3, #0x37
	strb r1, [r3]
_02254BCA:
	add r3, r0, #0
	add r3, #0x37
	ldrb r4, [r3]
	add r3, r0, #0
	add r3, #0x36
	ldrb r3, [r3]
	cmp r4, r3
	beq _02254BAE
	mov r0, #1
	pop {r3, r4}
	bx lr
_02254BE0:
	mov r0, #0
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end ov39_02254B9C

	thumb_func_start ov39_02254BE8
ov39_02254BE8: ; 0x02254BE8
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254BF8
	cmp r0, #1
	beq _02254C08
	b _02254C16
_02254BF8:
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl ov39_02254DA4
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254C16
_02254C08:
	ldr r0, [r4, #0x38]
	bl ov39_02254DD4
	cmp r0, #0
	beq _02254C16
	mov r0, #1
	pop {r4, pc}
_02254C16:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov39_02254BE8

	thumb_func_start ov39_02254C1C
ov39_02254C1C: ; 0x02254C1C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0x88
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254C52
	add r0, #8
	mov r1, #4
	bl ov20_022536F4
	str r5, [r4]
	bl ov20_02252D34
	str r0, [r4, #4]
	bl ov20_02252D24
	str r0, [r4, #0x20]
	add r0, r4, #0
	add r1, r5, #0
	bl ov39_02254C6C
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254C52:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov39_02254C1C

	thumb_func_start ov39_02254C58
ov39_02254C58: ; 0x02254C58
	push {r4, lr}
	add r4, r0, #0
	beq _02254C68
	bl ov39_02254D78
	add r0, r4, #0
	bl FreeToHeap
_02254C68:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov39_02254C58

	thumb_func_start ov39_02254C6C
ov39_02254C6C: ; 0x02254C6C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #1
	str r1, [sp, #0xc]
	bl ov20_022539C4
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x4a
	bl GfGfxLoader_LoadWholePalette
	mov r1, #0x14
	bl _u32_div_f
	ldr r1, [sp, #0xc]
	str r0, [r5, #0x64]
	add r2, r1, #0
	add r2, #0x30
	ldrb r2, [r2]
	mov r3, #0
	bl ov20_02253A04
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x3c
	mov r1, #0xc
	mov r2, #0x48
	mov r3, #0x49
	bl ov20_02253FBC
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x50
	mov r1, #0xc
	mov r2, #5
	mov r3, #6
	bl ov20_02253FBC
	add r0, r5, #0
	str r0, [sp, #0x10]
	add r0, #0x3c
	ldr r7, _02254D74 ; =ov39_02255408
	mov r4, #0
	add r6, r5, #0
	str r0, [sp, #0x10]
_02254CD6:
	ldr r0, [r5, #0x20]
	ldr r2, [sp, #0x10]
	add r1, r7, #0
	bl ov20_02253E74
	str r0, [r6, #0x24]
	add r4, r4, #1
	add r7, #0x10
	add r6, r6, #4
	cmp r4, #4
	blt _02254CD6
	cmp r4, #6
	bge _02254D18
	ldr r1, _02254D74 ; =ov39_02255408
	lsl r0, r4, #4
	add r7, r1, r0
	lsl r0, r4, #2
	add r6, r5, r0
	add r0, r5, #0
	str r0, [sp, #0x14]
	add r0, #0x50
	str r0, [sp, #0x14]
_02254D02:
	ldr r0, [r5, #0x20]
	ldr r2, [sp, #0x14]
	add r1, r7, #0
	bl ov20_02253E74
	str r0, [r6, #0x24]
	add r4, r4, #1
	add r7, #0x10
	add r6, r6, #4
	cmp r4, #6
	blt _02254D02
_02254D18:
	ldr r0, [sp, #0xc]
	add r0, #0x32
	ldrb r2, [r0]
	ldr r0, [sp, #0xc]
	lsl r1, r2, #1
	add r3, r0, r1
	ldrh r0, [r3, #0x24]
	mov r1, #4
	str r0, [sp]
	ldrh r3, [r3, #0x18]
	add r0, r5, #0
	bl ov39_02254FA4
	ldr r0, [sp, #0xc]
	add r0, #0x33
	ldrb r2, [r0]
	ldr r0, [sp, #0xc]
	lsl r1, r2, #1
	add r3, r0, r1
	ldrh r0, [r3, #0x24]
	mov r1, #5
	str r0, [sp]
	ldrh r3, [r3, #0x18]
	add r0, r5, #0
	bl ov39_02254FA4
	ldr r0, [sp, #0xc]
	add r0, #0x30
	str r0, [sp, #0xc]
	ldrb r0, [r0]
	cmp r0, #1
	bhi _02254D70
	ldr r0, [r5, #0x38]
	mov r1, #1
	bl ov20_02253F78
	ldr r0, [r5, #0x30]
	mov r1, #1
	bl ov20_02253F78
	ldr r0, [r5, #0x24]
	mov r1, #0xa
	bl ov20_02253F28
_02254D70:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254D74: .word ov39_02255408
	thumb_func_end ov39_02254C6C

	thumb_func_start ov39_02254D78
ov39_02254D78: ; 0x02254D78
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r0, #0x50
	bl ov20_02254014
	add r0, r6, #0
	add r0, #0x3c
	bl ov20_02254014
	mov r4, #0
	add r5, r6, #0
_02254D8E:
	ldr r1, [r5, #0x24]
	cmp r1, #0
	beq _02254D9A
	ldr r0, [r6, #0x20]
	bl ov20_02253F14
_02254D9A:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02254D8E
	pop {r4, r5, r6, pc}
	thumb_func_end ov39_02254D78

	thumb_func_start ov39_02254DA4
ov39_02254DA4: ; 0x02254DA4
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254DC4 ; =ov39_022553A8
	ldr r3, [r2]
	bl ov20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254DC4: .word ov39_022553A8
	thumb_func_end ov39_02254DA4

	thumb_func_start ov39_02254DC8
ov39_02254DC8: ; 0x02254DC8
	ldr r3, _02254DD0 ; =ov20_02253794
	add r0, #8
	bx r3
	nop
_02254DD0: .word ov20_02253794
	thumb_func_end ov39_02254DC8

	thumb_func_start ov39_02254DD4
ov39_02254DD4: ; 0x02254DD4
	ldr r3, _02254DDC ; =ov20_022537B8
	add r0, #8
	bx r3
	nop
_02254DDC: .word ov20_022537B8
	thumb_func_end ov39_02254DD4

	thumb_func_start ov39_02254DE0
ov39_02254DE0: ; 0x02254DE0
	push {r4, lr}
	add r4, r0, #0
	bl ov20_022538A0
	add r0, #8
	add r1, r4, #0
	bl ov20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov39_02254DE0

	thumb_func_start ov39_02254DF4
ov39_02254DF4: ; 0x02254DF4
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	add r5, r0, #0
	add r0, r4, #0
	bl ov20_022538A4
	ldr r0, [r5, #4]
	ldr r2, _02254E7C ; =ov39_02255330
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
	mov r1, #0x47
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x46
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	add r1, r0, #0
	bl ov20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r1, _02254E80 ; =0x04001000
	ldr r0, _02254E84 ; =0xFFFFE0FF
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
	add r0, r4, #0
	bl ov39_02254DE0
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_02254E7C: .word ov39_02255330
_02254E80: .word 0x04001000
_02254E84: .word 0xFFFFE0FF
	thumb_func_end ov39_02254DF4

	thumb_func_start ov39_02254E88
ov39_02254E88: ; 0x02254E88
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538AC
	cmp r0, #0
	beq _02254EA4
	cmp r0, #1
	beq _02254EB0
	pop {r3, r4, r5, pc}
_02254EA4:
	mov r0, #1
	str r0, [r4, #0x68]
	add r0, r5, #0
	bl ov20_022538B0
	pop {r3, r4, r5, pc}
_02254EB0:
	add r0, r4, #0
	mov r1, #6
	bl ov39_02254DC8
	cmp r0, #0
	beq _02254ECA
	ldr r0, [r4, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r5, #0
	bl ov39_02254DE0
_02254ECA:
	pop {r3, r4, r5, pc}
	thumb_func_end ov39_02254E88

	thumb_func_start ov39_02254ECC
ov39_02254ECC: ; 0x02254ECC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	ldr r0, _02254EF4 ; =0x00000669
	bl Poketch_PlaySoundEffect
	ldr r0, [r4, #0x24]
	mov r1, #0xa
	bl ov20_02253F28
	add r0, r5, #0
	bl ov39_02254DE0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254EF4: .word 0x00000669
	thumb_func_end ov39_02254ECC

	thumb_func_start ov39_02254EF8
ov39_02254EF8: ; 0x02254EF8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	ldr r0, [r4, #0x24]
	mov r1, #9
	bl ov20_02253F28
	add r0, r5, #0
	bl ov39_02254DE0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov39_02254EF8

	thumb_func_start ov39_02254F1C
ov39_02254F1C: ; 0x02254F1C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r6, #0
	bl ov20_022538A4
	add r7, r0, #0
	add r0, #0x32
	ldrb r5, [r0]
	ldr r0, _02254F5C ; =0x00000663
	bl Poketch_PlaySoundEffect
	lsl r0, r5, #1
	add r3, r7, r0
	ldrh r0, [r3, #0x24]
	mov r1, #4
	add r2, r5, #0
	str r0, [sp]
	ldrh r3, [r3, #0x18]
	add r0, r4, #0
	bl ov39_02254FA4
	add r0, r4, #0
	bl ov39_02254FF8
	add r0, r6, #0
	bl ov39_02254DE0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254F5C: .word 0x00000663
	thumb_func_end ov39_02254F1C

	thumb_func_start ov39_02254F60
ov39_02254F60: ; 0x02254F60
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r6, #0
	bl ov20_022538A4
	add r7, r0, #0
	add r0, #0x33
	ldrb r5, [r0]
	ldr r0, _02254FA0 ; =0x00000663
	bl Poketch_PlaySoundEffect
	lsl r0, r5, #1
	add r3, r7, r0
	ldrh r0, [r3, #0x24]
	mov r1, #5
	add r2, r5, #0
	str r0, [sp]
	ldrh r3, [r3, #0x18]
	add r0, r4, #0
	bl ov39_02254FA4
	add r0, r4, #0
	bl ov39_02254FF8
	add r0, r6, #0
	bl ov39_02254DE0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254FA0: .word 0x00000663
	thumb_func_end ov39_02254F60

	thumb_func_start ov39_02254FA4
ov39_02254FA4: ; 0x02254FA4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	add r6, r2, #0
	add r7, r3, #0
	ldr r4, [r0, #0x24]
	cmp r1, #5
	bne _02254FBA
	mov r1, #4
	b _02254FCC
_02254FBA:
	add r0, r7, #0
	mov r1, #0x1c ; BASE_FLIP
	bl GetMonBaseStat
	cmp r0, #0
	beq _02254FCA
	mov r1, #4
	b _02254FCC
_02254FCA:
	mov r1, #5
_02254FCC:
	add r0, r4, #0
	bl ov20_02253F28
	ldr r2, [r5, #0x64]
	lsl r1, r6, #4
	add r0, r4, #0
	add r1, r2, r1
	bl ov20_02253FA4
	add r1, sp, #8
	ldrh r1, [r1, #0x10]
	add r0, r7, #0
	mov r2, #0
	bl sub_0206B7BC
	add r1, r0, #0
	add r0, r4, #0
	add r1, r1, #1
	bl ov20_02253F9C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end ov39_02254FA4

	thumb_func_start ov39_02254FF8
ov39_02254FF8: ; 0x02254FF8
	push {r4, lr}
	add r4, r0, #0
	mov r1, #3
	mov r2, #0x16
	ldr r0, [r4, #0x2c]
	lsl r1, r1, #0x10
	lsl r2, r2, #0xe
	bl ov20_02253F64
	mov r1, #0xb
	lsl r1, r1, #0x10
	ldr r0, [r4, #0x30]
	lsr r2, r1, #1
	bl ov20_02253F64
	ldr r0, [r4, #0x2c]
	mov r1, #5
	bl ov20_02253F28
	ldr r0, [r4, #0x30]
	mov r1, #6
	bl ov20_02253F28
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl ov20_02253F28
	pop {r4, pc}
	thumb_func_end ov39_02254FF8

	thumb_func_start ov39_02255030
ov39_02255030: ; 0x02255030
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	add r6, r0, #0
	add r0, r5, #0
	bl ov20_022538AC
	cmp r0, #0
	beq _0225505C
	ldr r0, [r4, #0x68]
	cmp r0, #0
	beq _0225505C
	add r0, r5, #0
	bl ov39_02254DE0
	pop {r4, r5, r6, pc}
_0225505C:
	add r0, r5, #0
	bl ov20_022538AC
	cmp r0, #0
	beq _0225506C
	cmp r0, #1
	beq _02255086
	pop {r4, r5, r6, pc}
_0225506C:
	mov r0, #0
	str r0, [r4, #0x68]
	add r0, r4, #0
	bl ov39_02254FF8
	add r0, r4, #0
	add r1, r6, #0
	bl ov39_0225509C
	add r0, r5, #0
	bl ov20_022538B0
	pop {r4, r5, r6, pc}
_02255086:
	add r0, r4, #0
	add r1, r6, #0
	bl ov39_02255114
	cmp r0, #0
	beq _02255098
	add r0, r5, #0
	bl ov39_02254DE0
_02255098:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov39_02255030

	thumb_func_start ov39_0225509C
ov39_0225509C: ; 0x0225509C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r5, r1, #0
	mov r1, #0
	str r1, [r4, #0x70]
	str r1, [r4, #0x74]
	str r1, [r4, #0x78]
	add r0, #0x84
	str r1, [r0]
	add r0, r5, #0
	add r0, #0x31
	ldrb r0, [r0]
	cmp r0, #3
	bhi _022550FA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022550C4: ; jump table
	.short _022550EE - _022550C4 - 2 ; case 0
	.short _022550E0 - _022550C4 - 2 ; case 1
	.short _022550D2 - _022550C4 - 2 ; case 2
	.short _022550CC - _022550C4 - 2 ; case 3
_022550CC:
	ldr r0, _02255104 ; =ov39_02255378
	str r0, [r4, #0x6c]
	b _022550FA
_022550D2:
	ldr r0, _02255108 ; =ov39_02255318
	mov r1, #1
	str r0, [r4, #0x6c]
	ldr r0, [r4, #0x28]
	bl ov20_02253F28
	b _022550FA
_022550E0:
	ldr r0, _0225510C ; =ov39_0225534C
	mov r1, #2
	str r0, [r4, #0x6c]
	ldr r0, [r4, #0x28]
	bl ov20_02253F28
	b _022550FA
_022550EE:
	ldr r0, _02255110 ; =ov39_02255468
	mov r1, #3
	str r0, [r4, #0x6c]
	ldr r0, [r4, #0x28]
	bl ov20_02253F28
_022550FA:
	add r0, r4, #0
	add r1, r5, #0
	bl ov39_02255114
	pop {r3, r4, r5, pc}
	.align 2, 0
_02255104: .word ov39_02255378
_02255108: .word ov39_02255318
_0225510C: .word ov39_0225534C
_02255110: .word ov39_02255468
	thumb_func_end ov39_0225509C

	thumb_func_start ov39_02255114
ov39_02255114: ; 0x02255114
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r4, #0
	add r6, r4, #0
	mov r7, #0x16
	add r5, #0x84
	add r6, #0x78
	lsl r7, r7, #0xe
_02255124:
	ldr r0, [r4, #0x70]
	cmp r0, #0
	beq _02255138
	cmp r0, #1
	bne _02255130
	b _02255280
_02255130:
	cmp r0, #2
	bne _02255136
	b _022552DC
_02255136:
	b _022552FA
_02255138:
	beq _0225513C
	b _022552FA
_0225513C:
	add r6, r4, #0
	add r5, r4, #0
	add r6, #0x7c
	mov r7, #1
	add r5, #0x74
_02255146:
	ldr r0, [r5]
	ldr r1, [r4, #0x74]
	add r0, r0, #1
	str r0, [r5]
	ldr r0, [r4, #0x6c]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r0, r0, #7
	cmp r0, #6
	bls _0225515C
	b _02255276
_0225515C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02255168: ; jump table
	.short _02255252 - _02255168 - 2 ; case 0
	.short _02255240 - _02255168 - 2 ; case 1
	.short _0225522C - _02255168 - 2 ; case 2
	.short _02255212 - _02255168 - 2 ; case 3
	.short _022551C2 - _02255168 - 2 ; case 4
	.short _0225517A - _02255168 - 2 ; case 5
	.short _02255176 - _02255168 - 2 ; case 6
_02255176:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0225517A:
	ldr r0, [r5]
	ldr r1, [r4, #0x74]
	add r0, r0, #1
	str r0, [r5]
	ldr r0, [r4, #0x6c]
	lsl r1, r1, #2
	ldr r1, [r0, r1]
	add r0, r4, #0
	add r0, #0x84
	str r1, [r0]
	ldr r0, [r5]
	ldr r1, [r4, #0x74]
	add r0, r0, #1
	str r0, [r5]
	ldr r0, [r4, #0x6c]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	str r0, [r4, #0x7c]
	ldr r0, [r6]
	lsl r0, r0, #0xc
	str r0, [r6]
	ldr r1, [r4, #0x78]
	ldr r0, [r4, #0x7c]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r1, r4, #0
	add r1, #0x84
	ldr r0, [r6]
	ldr r1, [r1]
	bl _u32_div_f
	str r0, [r6]
	str r7, [r4, #0x70]
	b _02255276
_022551C2:
	ldr r0, [r5]
	ldr r1, [r4, #0x74]
	add r0, r0, #1
	str r0, [r5]
	ldr r0, [r4, #0x6c]
	lsl r1, r1, #2
	ldr r1, [r0, r1]
	add r0, r4, #0
	add r0, #0x84
	str r1, [r0]
	ldr r0, [r5]
	ldr r1, [r4, #0x74]
	add r0, r0, #1
	str r0, [r5]
	ldr r0, [r4, #0x6c]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #0
	str r0, [r4, #0x7c]
	ldr r0, [r6]
	mvn r1, r1
	lsl r0, r0, #0xc
	mul r1, r0
	str r1, [r6]
	ldr r1, [r4, #0x78]
	ldr r0, [r4, #0x7c]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r1, r4, #0
	add r1, #0x84
	ldr r0, [r6]
	ldr r1, [r1]
	bl _u32_div_f
	str r0, [r6]
	mov r0, #1
	str r0, [r4, #0x70]
	b _02255276
_02255212:
	ldr r0, [r5]
	ldr r1, [r4, #0x74]
	add r0, r0, #1
	str r0, [r5]
	ldr r0, [r4, #0x6c]
	lsl r1, r1, #2
	ldr r1, [r0, r1]
	add r0, r4, #0
	add r0, #0x84
	str r1, [r0]
	mov r0, #2
	str r0, [r4, #0x70]
	b _02255276
_0225522C:
	ldr r0, [r5]
	ldr r1, [r4, #0x74]
	add r0, r0, #1
	str r0, [r5]
	ldr r0, [r4, #0x6c]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bl Poketch_PlaySoundEffect
	b _02255276
_02255240:
	ldr r0, [r4, #0x2c]
	mov r1, #6
	bl ov20_02253F28
	ldr r0, [r4, #0x30]
	mov r1, #5
	bl ov20_02253F28
	b _02255276
_02255252:
	ldr r1, [r5]
	ldr r0, [r4, #0x74]
	add r1, r1, #1
	str r1, [r5]
	ldr r2, [r4, #0x6c]
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	ldr r2, [r4, #0x74]
	add r1, r1, #1
	str r1, [r5]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r1, [r4, #0x6c]
	lsl r2, r2, #2
	ldr r0, [r0, #0x24]
	ldr r1, [r1, r2]
	bl ov20_02253F28
_02255276:
	ldr r0, [r4, #0x70]
	cmp r0, #0
	bne _0225527E
	b _02255146
_0225527E:
	b _022552FA
_02255280:
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	beq _022552CC
	ldr r0, [r5]
	sub r0, r0, #1
	str r0, [r5]
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	beq _022552A4
	ldr r1, [r6]
	ldr r0, [r4, #0x7c]
	add r0, r1, r0
	str r0, [r6]
	b _022552AC
_022552A4:
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	str r0, [r4, #0x78]
_022552AC:
	mov r1, #3
	ldr r2, [r4, #0x78]
	lsl r1, r1, #0x10
	add r1, r2, r1
	ldr r0, [r4, #0x2c]
	add r2, r7, #0
	bl ov20_02253F64
	mov r1, #0xb
	ldr r2, [r4, #0x78]
	lsl r1, r1, #0x10
	sub r1, r1, r2
	ldr r0, [r4, #0x30]
	add r2, r7, #0
	bl ov20_02253F64
_022552CC:
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	bne _022552FA
	mov r0, #0
	str r0, [r4, #0x70]
	b _02255124
_022552DC:
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	beq _022552F4
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	add r4, #0x84
	sub r0, r0, #1
	str r0, [r4]
	b _022552FA
_022552F4:
	mov r0, #0
	str r0, [r4, #0x70]
	b _02255124
_022552FA:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end ov39_02255114

	.section .rodata

	.global ov39_02255300
ov39_02255300: ; 0x02255300
	.byte 0x80, 0xA8, 0x5C, 0x84, 0x82, 0xA4, 0x18, 0x48, 0x82, 0xA4, 0x98, 0xC8

	.global ov39_0225530C
ov39_0225530C: ; 0x0225530C
	.word ov39_022549F0, ov39_02254A30, ov39_02254BE8

	.global ov39_02255318
ov39_02255318: ; 0x02255318
	.word -2, 0x10, 0x10, -5
	.word 0x66B, -1

	.global ov39_02255330
ov39_02255330: ; 0x02255330
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov39_0225534C
ov39_0225534C: ; 0x0225534C
	.word -2, 0x10, 0x10, -5
	.word 0x66B, -2, 0x10, 0x10
	.word -5, 0x66B, -1

	.global ov39_02255378
ov39_02255378: ; 0x02255378
	.word -2, 0x10, 0x10, -4
	.word 0x10, -6, -5, 0x66C
	.word -3, 0x10, 0x10, -1

	.global ov39_022553A8
ov39_022553A8: ; 0x022553A8
	.word 0x00, ov39_02254DF4, 0x00
	.word 0x01, ov39_02254E88, 0x00
	.word 0x02, ov39_02254ECC, 0x00
	.word 0x03, ov39_02254EF8, 0x00
	.word 0x04, ov39_02254F1C, 0x00
	.word 0x05, ov39_02254F60, 0x00
	.word 0x06, ov39_02255030, 0x00
	.word 0x00, 0x00000000, 0x00

	.global ov39_02255408
ov39_02255408: ; 0x02255408
	.byte 0x00, 0x00, 0x07, 0x00, 0x00, 0x40, 0x09, 0x00
	.byte 0x09, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x80, 0x05, 0x00
	.byte 0x05, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x80, 0x05, 0x00
	.byte 0x06, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0xC0, 0x08, 0x00
	.byte 0x05, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0xC0, 0x08, 0x00
	.byte 0x04, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00

	.global ov39_02255468
ov39_02255468: ; 0x02255468
	.word -2, 0x10, 0x10, -5
	.word 0x066B, -2, 0x10, 0x10
	.word -5, 0x66B, -2, 0x10
	.word 0x10, -5, 0x66B, -4
	.word 0x10, -5, 0x66D, -7
	.word 0x02, 0x07, -7, 0x03
	.word 0x08, -7, 0x01, 0x04
	.word -4, 0x10, -1
