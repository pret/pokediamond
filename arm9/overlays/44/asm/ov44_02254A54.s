	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov44_02254A54
ov44_02254A54: ; 0x02254A54
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
	bl ov44_02254A90
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254A8A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov44_02254A54

	thumb_func_start ov44_02254A90
ov44_02254A90: ; 0x02254A90
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
	mov r1, #0x45
	bl GfGfxLoader_LoadWholePalette
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x28
	mov r1, #0xc
	mov r2, #0x43
	mov r3, #0x44
	bl ov20_02253FBC
	add r2, r5, #0
	ldr r0, [r5, #0x20]
	ldr r1, _02254AE0 ; =ov44_02254C60
	add r2, #0x28
	bl ov20_02253E74
	str r0, [r5, #0x24]
	ldr r1, [r4]
	mov r2, #0x25
	lsl r1, r1, #4
	add r1, #0x38
	lsl r1, r1, #0xc
	lsl r2, r2, #0xe
	bl ov20_02253F64
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02254AE0: .word ov44_02254C60
	thumb_func_end ov44_02254A90

	thumb_func_start ov44_02254AE4
ov44_02254AE4: ; 0x02254AE4
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x24]
	cmp r1, #0
	beq _02254AF4
	ldr r0, [r4, #0x20]
	bl ov20_02253F14
_02254AF4:
	add r4, #0x28
	add r0, r4, #0
	bl ov20_02254014
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov44_02254AE4

	thumb_func_start ov44_02254B00
ov44_02254B00: ; 0x02254B00
	push {r4, lr}
	add r4, r0, #0
	beq _02254B10
	bl ov44_02254AE4
	add r0, r4, #0
	bl FreeToHeap
_02254B10:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov44_02254B00

	thumb_func_start ov44_02254B14
ov44_02254B14: ; 0x02254B14
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254B34 ; =ov44_02254C8C
	ldr r3, [r2]
	bl ov20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254B34: .word ov44_02254C8C
	thumb_func_end ov44_02254B14

	thumb_func_start ov44_02254B38
ov44_02254B38: ; 0x02254B38
	ldr r3, _02254B40 ; =ov20_02253794
	add r0, #8
	bx r3
	nop
_02254B40: .word ov20_02253794
	thumb_func_end ov44_02254B38

	thumb_func_start ov44_02254B44
ov44_02254B44: ; 0x02254B44
	ldr r3, _02254B4C ; =ov20_022537B8
	add r0, #8
	bx r3
	nop
_02254B4C: .word ov20_022537B8
	thumb_func_end ov44_02254B44

	thumb_func_start ov44_02254B50
ov44_02254B50: ; 0x02254B50
	push {r4, lr}
	add r4, r0, #0
	bl ov20_022538A0
	add r0, #8
	add r1, r4, #0
	bl ov20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov44_02254B50

	thumb_func_start ov44_02254B64
ov44_02254B64: ; 0x02254B64
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	add r5, r0, #0
	add r0, r4, #0
	bl ov20_022538A4
	ldr r0, [r5, #4]
	ldr r2, _02254BEC ; =ov44_02254C70
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
	mov r1, #0x42
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
	mov r1, #0x41
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	add r1, r0, #0
	bl ov20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r1, _02254BF0 ; =0x04001000
	ldr r0, _02254BF4 ; =0xFFFFE0FF
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
	bl ov44_02254B50
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_02254BEC: .word ov44_02254C70
_02254BF0: .word 0x04001000
_02254BF4: .word 0xFFFFE0FF
	thumb_func_end ov44_02254B64

	thumb_func_start ov44_02254BF8
ov44_02254BF8: ; 0x02254BF8
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl ov44_02254B50
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov44_02254BF8

	thumb_func_start ov44_02254C14
ov44_02254C14: ; 0x02254C14
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
	mov r0, #0
	add r1, r0, #0
	bl ov20_02252D7C
	ldr r1, [r4]
	mov r2, #0x25
	lsl r1, r1, #4
	add r1, #0x38
	ldr r0, [r5, #0x24]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xe
	bl ov20_02253F64
	add r0, r6, #0
	bl ov44_02254B50
	pop {r4, r5, r6, pc}
	.align 2, 0
_02254C50: .word 0x00000663
	thumb_func_end ov44_02254C14

	.section .rodata

	.global ov44_02254C60
ov44_02254C60: ; 0x02254C60
	.byte 0x00, 0x80, 0x03, 0x00
	.byte 0x00, 0x40, 0x09, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00

	.global ov44_02254C70
ov44_02254C70: ; 0x02254C70
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov44_02254C8C
ov44_02254C8C: ; 0x02254C8C
	.word 0x00, ov44_02254B64, 0x00
	.word 0x01, ov44_02254BF8, 0x00
	.word 0x02, ov44_02254C14, 0x00
	.word 0x00, 0x00000000, 0x00
