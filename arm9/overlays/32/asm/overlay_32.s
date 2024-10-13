	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov32_02254854
ov32_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x1c
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl ov32_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =ov32_02254920
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
_02254898: .word ov32_02254920
	thumb_func_end ov32_02254854

	thumb_func_start ov32_0225489C
ov32_0225489C: ; 0x0225489C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0
	add r1, sp, #4
	add r6, r2, #0
	bl PM_GetBackLight
	ldr r0, [sp, #4]
	cmp r0, #1
	bne _022548B8
	mov r0, #1
	b _022548BA
_022548B8:
	mov r0, #0
_022548BA:
	str r0, [r5, #4]
	add r0, r5, #0
	add r0, #8
	add r1, r5, #4
	add r2, r6, #0
	bl ov32_02254A54
	cmp r0, #0
	beq _022548F2
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	mov r0, #8
	str r0, [sp]
	ldr r0, _022548F8 ; =ov32_02254C54
	ldr r2, _022548FC ; =ov32_02254918
	mov r1, #2
	add r3, r5, #0
	bl ov20_02254130
	str r0, [r5, #0x10]
	mov r0, #0
	str r0, [r5, #0x14]
	add sp, #8
	str r4, [r5, #0xc]
	mov r0, #1
	pop {r4, r5, r6, pc}
_022548F2:
	mov r0, #0
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_022548F8: .word ov32_02254C54
_022548FC: .word ov32_02254918
	thumb_func_end ov32_0225489C

	thumb_func_start ov32_02254900
ov32_02254900: ; 0x02254900
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	bl ov20_02254198
	ldr r0, [r4, #8]
	bl ov32_02254A90
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end ov32_02254900

	thumb_func_start ov32_02254918
ov32_02254918: ; 0x02254918
	str r0, [r3, #0x18]
	str r1, [r3, #0x14]
	bx lr
	.align 2, 0
	thumb_func_end ov32_02254918

	thumb_func_start ov32_02254920
ov32_02254920: ; 0x02254920
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _02254956
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	bl ov20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254958 ; =ov32_02254C5C
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254956
	add r0, r4, #0
	bl ov32_02254900
	add r0, r5, #0
	bl SysTask_Destroy
	ldr r0, [r4, #0xc]
	bl ov20_022529A0
_02254956:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254958: .word ov32_02254C5C
	thumb_func_end ov32_02254920

	thumb_func_start ov32_0225495C
ov32_0225495C: ; 0x0225495C
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end ov32_0225495C

	thumb_func_start ov32_02254964
ov32_02254964: ; 0x02254964
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _0225496C
	b _0225496E
_0225496C:
	mov r1, #2
_0225496E:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end ov32_02254964

	thumb_func_start ov32_02254978
ov32_02254978: ; 0x02254978
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254988
	cmp r0, #1
	beq _02254998
	b _022549B2
_02254988:
	ldr r0, [r4, #8]
	mov r1, #0
	bl ov32_02254B08
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549B2
_02254998:
	ldr r0, [r4, #8]
	mov r1, #0
	bl ov32_02254B2C
	cmp r0, #0
	beq _022549B2
	ldr r0, [r4, #0xc]
	bl ov20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl ov32_02254964
_022549B2:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov32_02254978

	thumb_func_start ov32_022549B8
ov32_022549B8: ; 0x022549B8
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _022549CC
	mov r1, #2
	bl ov32_02254964
	mov r0, #0
	pop {r4, pc}
_022549CC:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549D8
	cmp r0, #1
	beq _02254A0C
	b _02254A1C
_022549D8:
	ldr r0, [r4, #0x14]
	cmp r0, #1
	bne _02254A1C
	ldr r1, [r4, #0x18]
	cmp r1, #0
	bne _022549EA
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _022549F4
_022549EA:
	cmp r1, #1
	bne _02254A04
	ldr r0, [r4, #4]
	cmp r0, #1
	bne _02254A04
_022549F4:
	ldr r1, [r4, #4]
	mov r0, #1
	eor r0, r1
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	mov r1, #2
	bl ov32_02254B08
_02254A04:
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A1C
_02254A0C:
	ldr r0, [r4, #8]
	mov r1, #2
	bl ov32_02254B2C
	cmp r0, #0
	beq _02254A1C
	mov r0, #0
	strb r0, [r4, #1]
_02254A1C:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end ov32_022549B8

	thumb_func_start ov32_02254A20
ov32_02254A20: ; 0x02254A20
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A30
	cmp r0, #1
	beq _02254A40
	b _02254A4E
_02254A30:
	ldr r0, [r4, #8]
	mov r1, #1
	bl ov32_02254B08
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A4E
_02254A40:
	ldr r0, [r4, #8]
	bl ov32_02254B38
	cmp r0, #0
	beq _02254A4E
	mov r0, #1
	pop {r4, pc}
_02254A4E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov32_02254A20

	thumb_func_start ov32_02254A54
ov32_02254A54: ; 0x02254A54
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0x3c
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254A8A
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
	bl ov32_02254A9C
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254A8A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov32_02254A54

	thumb_func_start ov32_02254A90
ov32_02254A90: ; 0x02254A90
	push {r3, lr}
	cmp r0, #0
	beq _02254A9A
	bl FreeToHeap
_02254A9A:
	pop {r3, pc}
	thumb_func_end ov32_02254A90

	thumb_func_start ov32_02254A9C
ov32_02254A9C: ; 0x02254A9C
	push {r4, r5, lr}
	sub sp, #0xc
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r5, r0, #0
	add r4, r1, #0
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x68
	bl GfGfxLoader_LoadWholePalette
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x28
	mov r1, #0xc
	mov r2, #0x66
	mov r3, #0x67
	bl ov20_02253FBC
	add r2, r5, #0
	ldr r0, [r5, #0x20]
	ldr r1, _02254AEC ; =ov32_02254C68
	add r2, #0x28
	bl ov20_02253E74
	str r0, [r5, #0x24]
	ldr r0, [r4]
	cmp r0, #0
	bne _02254AE6
	ldr r0, [r5, #0x24]
	mov r1, #1
	bl ov20_02253F28
_02254AE6:
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_02254AEC: .word ov32_02254C68
	thumb_func_end ov32_02254A9C

	thumb_func_start ov32_02254AF0
ov32_02254AF0: ; 0x02254AF0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x24]
	bl ov20_02253F14
	add r4, #0x28
	add r0, r4, #0
	bl ov20_02254014
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov32_02254AF0

	thumb_func_start ov32_02254B08
ov32_02254B08: ; 0x02254B08
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254B28 ; =ov32_02254C94
	ldr r3, [r2]
	bl ov20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254B28: .word ov32_02254C94
	thumb_func_end ov32_02254B08

	thumb_func_start ov32_02254B2C
ov32_02254B2C: ; 0x02254B2C
	ldr r3, _02254B34 ; =ov20_02253794
	add r0, #8
	bx r3
	nop
_02254B34: .word ov20_02253794
	thumb_func_end ov32_02254B2C

	thumb_func_start ov32_02254B38
ov32_02254B38: ; 0x02254B38
	ldr r3, _02254B40 ; =ov20_022537B8
	add r0, #8
	bx r3
	nop
_02254B40: .word ov20_022537B8
	thumb_func_end ov32_02254B38

	thumb_func_start ov32_02254B44
ov32_02254B44: ; 0x02254B44
	push {r4, lr}
	add r4, r0, #0
	bl ov20_022538A0
	add r0, #8
	add r1, r4, #0
	bl ov20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov32_02254B44

	thumb_func_start ov32_02254B58
ov32_02254B58: ; 0x02254B58
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254BDC ; =ov32_02254C78
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
	mov r1, #0x65
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
	mov r1, #0x64
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	add r1, r0, #0
	bl ov20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r1, _02254BE0 ; =0x04001000
	ldr r0, _02254BE4 ; =0xFFFFE0FF
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
	bl ov32_02254B44
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02254BDC: .word ov32_02254C78
_02254BE0: .word 0x04001000
_02254BE4: .word 0xFFFFE0FF
	thumb_func_end ov32_02254B58

	thumb_func_start ov32_02254BE8
ov32_02254BE8: ; 0x02254BE8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	bl ov32_02254AF0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r5, #0
	bl ov32_02254B44
	pop {r3, r4, r5, pc}
	thumb_func_end ov32_02254BE8

	thumb_func_start ov32_02254C08
ov32_02254C08: ; 0x02254C08
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl ov20_022538A0
	add r5, r0, #0
	add r0, r6, #0
	bl ov20_022538A4
	add r4, r0, #0
	ldr r0, _02254C50 ; =0x00000663
	bl Poketch_PlaySoundEffect
	ldr r0, [r4]
	cmp r0, #0
	ldr r0, [r5, #0x24]
	beq _02254C3A
	mov r1, #0
	bl ov20_02253F28
	mov r0, #1
	add r1, r0, #0
	bl PM_SetBackLight
	b _02254C48
_02254C3A:
	mov r1, #1
	bl ov20_02253F28
	mov r0, #1
	mov r1, #0
	bl PM_SetBackLight
_02254C48:
	add r0, r6, #0
	bl ov32_02254B44
	pop {r4, r5, r6, pc}
	.align 2, 0
_02254C50: .word 0x00000663
	thumb_func_end ov32_02254C08

	.section .rodata

	.global ov32_02254C54
ov32_02254C54: ; 0x02254C54
	.byte 0x48, 0x68, 0x5C, 0x84, 0x68, 0x88, 0x5C, 0x84

	.global ov32_02254C5C
ov32_02254C5C: ; 0x02254C5C
	.word ov32_02254978, ov32_022549B8, ov32_02254A20

	.global ov32_02254C68
ov32_02254C68: ; 0x02254C68
	.byte 0x00, 0x00, 0x07, 0x00, 0x00, 0x80, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov32_02254C78
ov32_02254C78: ; 0x02254C78
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov32_02254C94
ov32_02254C94: ; 0x02254C94
	.word 0x00, ov32_02254B58, 0x00
	.word 0x01, ov32_02254BE8, 0x00
	.word 0x02, ov32_02254C08, 0x00
	.word 0x00, 0x00000000, 0x00
