	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov24_02254F40
ov24_02254F40: ; 0x02254F40
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r0, r1, #0
	str r1, [sp, #8]
	bl ov20_022538A0
	add r7, r0, #0
	ldr r0, [r7]
	ldr r1, [r0]
	cmp r1, #0
	bne _02254FF2
	mov r1, #8
	str r1, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r1, [r0, #4]
	ldr r0, [r0, #8]
	lsl r1, r1, #1
	lsl r0, r0, #1
	sub r6, r1, #4
	sub r5, r0, #4
	cmp r6, #0
	bge _02254F74
	ldr r0, [sp, #0x10]
	add r0, r0, r6
	str r0, [sp, #0x14]
	mov r6, #0
_02254F74:
	cmp r5, #0
	bge _02254F80
	ldr r0, [sp, #0x10]
	add r0, r0, r5
	str r0, [sp, #0x10]
	mov r5, #0
_02254F80:
	ldr r0, [sp, #0x14]
	lsl r2, r6, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [sp, #0x10]
	lsl r3, r5, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r7, #0x70]
	mov r1, #4
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl FillWindowPixelRect
	asr r1, r5, #3
	mov r2, #0x14
	asr r0, r6, #3
	mul r2, r1
	add r4, r0, r2
	ldr r2, [sp, #0x14]
	add r2, r6, r2
	sub r2, r2, #1
	asr r2, r2, #3
	sub r0, r2, r0
	ldr r2, [sp, #0x10]
	add r0, r0, #1
	add r2, r5, r2
	sub r2, r2, #1
	asr r2, r2, #3
	sub r1, r2, r1
	add r1, r1, #1
	sub r6, r1, #1
	cmp r1, #0
	beq _0225502C
	lsl r0, r0, #5
	lsl r5, r4, #5
	str r0, [sp, #0xc]
_02254FCE:
	ldr r0, [r7, #0x70]
	add r1, r4, #0
	ldr r0, [r0, #0xc]
	add r1, #0xc
	ldr r2, [sp, #0xc]
	add r0, r0, r5
	lsl r1, r1, #5
	bl GXS_LoadBG3Char
	mov r0, #0xa
	lsl r0, r0, #6
	add r5, r5, r0
	add r0, r6, #0
	add r4, #0x14
	sub r6, r6, #1
	cmp r0, #0
	bne _02254FCE
	b _0225502C
_02254FF2:
	ldr r1, [r0, #4]
	ldr r0, [r0, #8]
	lsl r2, r1, #1
	lsl r3, r0, #1
	asr r1, r3, #3
	mov r0, #0x14
	asr r4, r2, #3
	mul r0, r1
	add r4, r4, r0
	mov r0, #2
	str r0, [sp]
	str r0, [sp, #4]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	ldr r0, [r7, #0x70]
	mov r1, #1
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl FillWindowPixelRect
	ldr r0, [r7, #0x70]
	mov r2, #0x20
	ldr r1, [r0, #0xc]
	lsl r0, r4, #5
	add r4, #0xc
	add r0, r1, r0
	lsl r1, r4, #5
	bl GXS_LoadBG3Char
_0225502C:
	ldr r0, [sp, #8]
	bl ov24_02254DC8
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end ov24_02254F40

	thumb_func_start ov24_02255038
ov24_02255038: ; 0x02255038
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	ldr r0, [r0, #0x70]
	bl CopyWindowPixelsToVram_TextMode
	add r0, r4, #0
	bl ov24_02254DC8
	pop {r4, pc}
	thumb_func_end ov24_02255038

	thumb_func_start ov24_02255050
ov24_02255050: ; 0x02255050
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	bl ov24_022550D4
	ldr r0, [r4, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #4]
	mov r1, #7
	bl FreeBgTilemapBuffer
	add r0, r5, #0
	bl ov24_02254DC8
	pop {r3, r4, r5, pc}
	thumb_func_end ov24_02255050

	thumb_func_start ov24_02255078
ov24_02255078: ; 0x02255078
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r7, r0, #0
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x20
	bl GfGfxLoader_LoadWholePalette
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x54
	mov r1, #0xc
	mov r2, #0x21
	mov r3, #0x22
	bl ov20_02253FBC
	cmp r0, #0
	beq _022550CC
	add r0, r7, #0
	str r0, [sp, #0xc]
	add r0, #0x54
	ldr r4, _022550D0 ; =ov24_0225514C
	mov r6, #0
	add r5, r7, #0
	str r0, [sp, #0xc]
_022550B6:
	ldr r0, [r7, #0x50]
	ldr r2, [sp, #0xc]
	add r1, r4, #0
	bl ov20_02253E74
	str r0, [r5, #0x68]
	add r6, r6, #1
	add r4, #0x10
	add r5, r5, #4
	cmp r6, #2
	blt _022550B6
_022550CC:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022550D0: .word ov24_0225514C
	thumb_func_end ov24_02255078

	thumb_func_start ov24_022550D4
ov24_022550D4: ; 0x022550D4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_022550DC:
	ldr r0, [r6, #0x50]
	ldr r1, [r5, #0x68]
	bl ov20_02253F14
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blo _022550DC
	add r6, #0x54
	add r0, r6, #0
	bl ov20_02254014
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov24_022550D4

	.section .rodata
	.global ov24_022550F8
ov24_022550F8: ; 0x022550F8
	.byte 0x18, 0x58, 0xB4, 0xCC, 0x68, 0xA8, 0xB4, 0xCC

	.global ov24_02255100
ov24_02255100: ; 0x02255100
	.word ov24_022549AC, ov24_022549F8, ov24_02254C64

	.global ov24_0225510C
ov24_0225510C: ; 0x0225510C
	.byte 0x07, 0x02, 0x02, 0x14, 0x13, 0x00, 0x0C, 0x00

	.global ov24_02255114
ov24_02255114: ; 0x02255114
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov24_02255130
ov24_02255130: ; 0x02255130
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x03, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov24_0225514C
ov24_0225514C: ; 0x0225514C
	.byte 0x00, 0x00, 0x0C, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x80, 0x08, 0x00, 0x03, 0x00, 0x00, 0x02
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov24_0225516C
ov24_0225516C: ; 0x0225516C
	.word 0x00, ov24_02254DDC, 0x00
	.word 0x01, ov24_02254EE0, 0x00
	.word 0x02, ov24_02254F28, 0x00
	.word 0x03, ov24_02254F40, 0x00
	.word 0x04, ov24_02255038, 0x00
	.word 0x05, ov24_02255050, 0x00
	.word 0x00, 0x00000000, 0x00
