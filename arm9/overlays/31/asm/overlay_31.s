	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov31_02254854
ov31_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x20
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl ov31_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =ov31_02254918
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
_02254898: .word ov31_02254918
	thumb_func_end ov31_02254854

	thumb_func_start ov31_0225489C
ov31_0225489C: ; 0x0225489C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	str r1, [r5, #0x10]
	add r0, r1, #0
	add r4, r2, #0
	bl ov20_02252C3C
	str r0, [r5, #0x1c]
	mov r0, #1
	str r0, [r5, #8]
	ldr r0, [r5, #0x1c]
	bl Save_Poketch_GetStepCounter
	str r0, [r5, #4]
	add r0, r5, #0
	add r0, #0xc
	add r1, r5, #4
	add r2, r4, #0
	bl ov31_02254A84
	cmp r0, #0
	beq _022548EA
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	mov r0, #8
	str r0, [sp]
	ldr r0, _022548F0 ; =ov31_02254D98
	ldr r2, _022548F4 ; =ov31_022548F8
	mov r1, #1
	add r3, r5, #0
	bl ov20_02254130
	str r0, [r5, #0x14]
	mov r0, #0
	str r0, [r5, #0x18]
	mov r0, #1
	pop {r3, r4, r5, pc}
_022548EA:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_022548F0: .word ov31_02254D98
_022548F4: .word ov31_022548F8
	thumb_func_end ov31_0225489C

	thumb_func_start ov31_022548F8
ov31_022548F8: ; 0x022548F8
	cmp r0, #0
	bne _022548FE
	str r1, [r3, #0x18]
_022548FE:
	bx lr
	thumb_func_end ov31_022548F8

	thumb_func_start ov31_02254900
ov31_02254900: ; 0x02254900
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	bl ov20_02254198
	ldr r0, [r4, #0xc]
	bl ov31_02254AC0
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end ov31_02254900

	thumb_func_start ov31_02254918
ov31_02254918: ; 0x02254918
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _0225494E
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	bl ov20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254950 ; =ov31_02254D9C
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _0225494E
	add r0, r4, #0
	bl ov31_02254900
	add r0, r5, #0
	bl sub_0200CAB4
	ldr r0, [r4, #0x10]
	bl ov20_022529A0
_0225494E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254950: .word ov31_02254D9C
	thumb_func_end ov31_02254918

	thumb_func_start ov31_02254954
ov31_02254954: ; 0x02254954
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end ov31_02254954

	thumb_func_start ov31_0225495C
ov31_0225495C: ; 0x0225495C
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254964
	b _02254966
_02254964:
	mov r1, #2
_02254966:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end ov31_0225495C

	thumb_func_start ov31_02254970
ov31_02254970: ; 0x02254970
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254980
	cmp r0, #1
	beq _02254990
	b _022549AA
_02254980:
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl ov31_02254BBC
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549AA
_02254990:
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl ov31_02254BE0
	cmp r0, #0
	beq _022549AA
	ldr r0, [r4, #0x10]
	bl ov20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl ov31_0225495C
_022549AA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov31_02254970

	thumb_func_start ov31_022549B0
ov31_022549B0: ; 0x022549B0
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _022549C4
	mov r1, #2
	bl ov31_0225495C
	mov r0, #0
	pop {r4, pc}
_022549C4:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549D0
	cmp r0, #1
	beq _02254A0A
	b _02254A4C
_022549D0:
	ldr r0, [r4, #0x18]
	cmp r0, #1
	bne _022549EE
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl ov31_02254BBC
	mov r0, #0
	str r0, [r4, #0x18]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A4C
_022549EE:
	ldr r0, [r4, #0x10]
	bl ov20_02252C34
	cmp r0, #0
	beq _02254A4C
	ldr r0, [r4, #0x1c]
	bl Save_Poketch_GetStepCounter
	str r0, [r4, #4]
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl ov31_02254BBC
	b _02254A4C
_02254A0A:
	ldr r0, [r4, #0x18]
	cmp r0, #2
	bne _02254A24
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl ov31_02254BBC
	mov r0, #0
	str r0, [r4, #0x18]
	strb r0, [r4, #1]
	b _02254A4C
_02254A24:
	cmp r0, #3
	bne _02254A4C
	mov r0, #1
	str r0, [r4, #8]
	mov r1, #0
	str r1, [r4, #4]
	ldr r0, [r4, #0x1c]
	bl Save_Poketch_SetStepCounter
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl ov31_02254BBC
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl ov31_02254BBC
	mov r0, #0
	str r0, [r4, #0x18]
	strb r0, [r4, #1]
_02254A4C:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end ov31_022549B0

	thumb_func_start ov31_02254A50
ov31_02254A50: ; 0x02254A50
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A60
	cmp r0, #1
	beq _02254A70
	b _02254A7E
_02254A60:
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl ov31_02254BBC
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A7E
_02254A70:
	ldr r0, [r4, #0xc]
	bl ov31_02254BEC
	cmp r0, #0
	beq _02254A7E
	mov r0, #1
	pop {r4, pc}
_02254A7E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov31_02254A50

	thumb_func_start ov31_02254A84
ov31_02254A84: ; 0x02254A84
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0x64
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254ABA
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
	bl ov31_02254AD4
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254ABA:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov31_02254A84

	thumb_func_start ov31_02254AC0
ov31_02254AC0: ; 0x02254AC0
	push {r4, lr}
	add r4, r0, #0
	beq _02254AD0
	bl ov31_02254B88
	add r0, r4, #0
	bl FreeToHeap
_02254AD0:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov31_02254AC0

	thumb_func_start ov31_02254AD4
ov31_02254AD4: ; 0x02254AD4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r7, r0, #0
	str r1, [sp, #0xc]
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #2
	bl GfGfxLoader_LoadWholePalette
	mov r0, #0
	str r0, [sp]
	mov r2, #1
	mov r3, #0xa
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x34
	lsl r3, r3, #8
	bl GfGfxLoader_LoadWholePalette
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x3c
	mov r1, #0xc
	mov r2, #0x32
	mov r3, #0x33
	bl ov20_02253FBC
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x50
	mov r1, #0xc
	mov r2, #3
	mov r3, #4
	bl ov20_02253FBC
	add r2, r7, #0
	ldr r0, [r7, #0x20]
	ldr r1, _02254B80 ; =ov31_02254DA8
	add r2, #0x3c
	bl ov20_02253E74
	mov r1, #0x50
	str r0, [r7, #0x24]
	bl ov20_02253FA4
	add r0, r7, #0
	mov r5, #5
	str r0, [sp, #0x10]
	add r0, #0x50
	mov r6, #0
	add r4, r7, #0
	lsl r5, r5, #0x10
	str r0, [sp, #0x10]
_02254B50:
	ldr r0, [r7, #0x20]
	ldr r1, _02254B84 ; =ov31_02254DB8
	ldr r2, [sp, #0x10]
	bl ov20_02253E74
	mov r2, #1
	add r1, r5, #0
	lsl r2, r2, #0x12
	str r0, [r4, #0x28]
	bl ov20_02253F64
	mov r0, #1
	lsl r0, r0, #0x10
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, r0
	cmp r6, #5
	blt _02254B50
	ldr r1, [sp, #0xc]
	add r0, r7, #0
	bl ov31_02254D1C
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254B80: .word ov31_02254DA8
_02254B84: .word ov31_02254DB8
	thumb_func_end ov31_02254AD4

	thumb_func_start ov31_02254B88
ov31_02254B88: ; 0x02254B88
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x20]
	ldr r1, [r6, #0x24]
	bl ov20_02253F14
	mov r4, #0
	add r5, r6, #0
_02254B98:
	ldr r0, [r6, #0x20]
	ldr r1, [r5, #0x28]
	bl ov20_02253F14
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _02254B98
	add r0, r6, #0
	add r0, #0x3c
	bl ov20_02254014
	add r6, #0x50
	add r0, r6, #0
	bl ov20_02254014
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov31_02254B88

	thumb_func_start ov31_02254BBC
ov31_02254BBC: ; 0x02254BBC
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254BDC ; =ov31_02254DE4
	ldr r3, [r2]
	bl ov20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254BDC: .word ov31_02254DE4
	thumb_func_end ov31_02254BBC

	thumb_func_start ov31_02254BE0
ov31_02254BE0: ; 0x02254BE0
	ldr r3, _02254BE8 ; =ov20_02253794
	add r0, #8
	bx r3
	nop
_02254BE8: .word ov20_02253794
	thumb_func_end ov31_02254BE0

	thumb_func_start ov31_02254BEC
ov31_02254BEC: ; 0x02254BEC
	ldr r3, _02254BF4 ; =ov20_022537B8
	add r0, #8
	bx r3
	nop
_02254BF4: .word ov20_022537B8
	thumb_func_end ov31_02254BEC

	thumb_func_start ov31_02254BF8
ov31_02254BF8: ; 0x02254BF8
	push {r4, lr}
	add r4, r0, #0
	bl ov20_022538A0
	add r0, #8
	add r1, r4, #0
	bl ov20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov31_02254BF8

	thumb_func_start ov31_02254C0C
ov31_02254C0C: ; 0x02254C0C
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254C90 ; =ov31_02254DC8
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
	mov r1, #0x31
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
	mov r1, #0x30
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	add r1, r0, #0
	bl ov20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r1, _02254C94 ; =0x04001000
	ldr r0, _02254C98 ; =0xFFFFE0FF
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
	bl ov31_02254BF8
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02254C90: .word ov31_02254DC8
_02254C94: .word 0x04001000
_02254C98: .word 0xFFFFE0FF
	thumb_func_end ov31_02254C0C

	thumb_func_start ov31_02254C9C
ov31_02254C9C: ; 0x02254C9C
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl ov31_02254BF8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov31_02254C9C

	thumb_func_start ov31_02254CB8
ov31_02254CB8: ; 0x02254CB8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	ldr r0, [r4]
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _02254CD2
	cmp r0, #1
	beq _02254CE2
	b _02254CEA
_02254CD2:
	ldr r0, _02254CF4 ; =0x00000669
	bl ov20_02252B28
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl ov20_02253F28
	b _02254CEA
_02254CE2:
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl ov20_02253F28
_02254CEA:
	add r0, r5, #0
	bl ov31_02254BF8
	pop {r3, r4, r5, pc}
	nop
_02254CF4: .word 0x00000669
	thumb_func_end ov31_02254CB8

	thumb_func_start ov31_02254CF8
ov31_02254CF8: ; 0x02254CF8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	add r1, r0, #0
	add r0, r4, #0
	bl ov31_02254D1C
	add r0, r5, #0
	bl ov31_02254BF8
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov31_02254CF8

	thumb_func_start ov31_02254D1C
ov31_02254D1C: ; 0x02254D1C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	ldr r0, [r1]
	ldr r5, _02254D80 ; =0x04000280
	str r0, [sp, #4]
	ldr r0, _02254D84 ; =0x00002710
	lsr r4, r5, #0xb
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #8]
	lsr r6, r5, #0xb
_02254D34:
	mov r0, #0
	strh r0, [r5]
	ldr r1, [sp, #4]
	ldr r0, _02254D88 ; =0x04000290
	str r1, [r0]
	ldr r1, [sp]
	str r1, [r0, #8]
	ldr r0, _02254D8C ; =0x04000298
	mov r1, #0
	str r1, [r0, #4]
_02254D48:
	ldrh r0, [r5]
	tst r0, r4
	bne _02254D48
	ldr r1, _02254D90 ; =0x040002A0
	ldr r0, [r7, #0x28]
	ldr r1, [r1]
	bl ov20_02253F28
_02254D58:
	ldrh r0, [r5]
	tst r0, r6
	bne _02254D58
	ldr r0, _02254D94 ; =0x040002A8
	mov r1, #0xa
	ldr r0, [r0]
	str r0, [sp, #4]
	ldr r0, [sp]
	bl _u32_div_f
	str r0, [sp]
	ldr r0, [sp, #8]
	add r7, r7, #4
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, #5
	blt _02254D34
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02254D80: .word 0x04000280
_02254D84: .word 0x00002710
_02254D88: .word 0x04000290
_02254D8C: .word 0x04000298
_02254D90: .word 0x040002A0
_02254D94: .word 0x040002A8
	thumb_func_end ov31_02254D1C

	.section .rodata

	.global ov31_02254D98
ov31_02254D98: ; 0x02254D98
	.byte 0x64, 0x9C, 0x52, 0x92

	.global ov31_02254D9C
ov31_02254D9C: ; 0x02254D9C
	.word ov31_02254970, ov31_022549B0, ov31_02254A50

	.global ov31_02254DA8
ov31_02254DA8: ; 0x02254DA8
	.byte 0x00, 0x20, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00

	.global ov31_02254DB8
ov31_02254DB8: ; 0x02254DB8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00

	.global ov31_02254DC8
ov31_02254DC8: ; 0x02254DC8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov31_02254DE4
ov31_02254DE4: ; 0x02254DE4
	.word 0x00, ov31_02254C0C, 0x00
	.word 0x01, ov31_02254C9C, 0x00
	.word 0x02, ov31_02254CB8, 0x00
	.word 0x03, ov31_02254CF8, 0x00
	.word 0x00, 0x00000000, 0x00
