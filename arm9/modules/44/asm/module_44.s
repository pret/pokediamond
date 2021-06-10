	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD44_02254854
MOD44_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x14
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD44_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD44_022548EC
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA44
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
_02254898: .word MOD44_022548EC
	thumb_func_end MOD44_02254854

	thumb_func_start MOD44_0225489C
MOD44_0225489C: ; 0x0225489C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r6, r2, #0
	bl MOD20_02252C3C
	str r0, [r5, #0x10]
	bl Sav2_Poketch_GetScreenTint
	str r0, [r5, #4]
	strb r0, [r5, #3]
	add r0, r5, #0
	add r0, #8
	add r1, r5, #4
	add r2, r6, #0
	bl MOD44_02254A54
	cmp r0, #0
	beq _022548D2
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	str r4, [r5, #0xc]
	mov r0, #1
	pop {r4, r5, r6, pc}
_022548D2:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD44_0225489C

	thumb_func_start MOD44_022548D8
MOD44_022548D8: ; 0x022548D8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl MOD44_02254B00
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD44_022548D8

	thumb_func_start MOD44_022548EC
MOD44_022548EC: ; 0x022548EC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhs _02254918
	lsl r2, r1, #2
	ldr r1, _0225491C ; =MOD44_02254C54
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254918
	add r0, r4, #0
	bl MOD44_022548D8
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0xc]
	bl MOD20_022529A0
_02254918:
	pop {r3, r4, r5, pc}
	nop
_0225491C: .word MOD44_02254C54
	thumb_func_end MOD44_022548EC

	thumb_func_start MOD44_02254920
MOD44_02254920: ; 0x02254920
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD44_02254920

	thumb_func_start MOD44_02254928
MOD44_02254928: ; 0x02254928
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254930
	b _02254932
_02254930:
	mov r1, #2
_02254932:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD44_02254928

	thumb_func_start MOD44_0225493C
MOD44_0225493C: ; 0x0225493C
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _0225494C
	cmp r0, #1
	beq _0225495C
	b _02254976
_0225494C:
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD44_02254B14
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254976
_0225495C:
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD44_02254B38
	cmp r0, #0
	beq _02254976
	ldr r0, [r4, #0xc]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD44_02254928
_02254976:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD44_0225493C

	thumb_func_start MOD44_0225497C
MOD44_0225497C: ; 0x0225497C
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254990
	mov r1, #2
	bl MOD44_02254928
	mov r0, #0
	pop {r4, pc}
_02254990:
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _0225499C
	cmp r1, #1
	beq _022549B4
	b _022549C4
_0225499C:
	bl MOD44_022549C8
	cmp r0, #0
	beq _022549C4
	ldr r0, [r4, #8]
	mov r1, #2
	bl MOD44_02254B14
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549C4
_022549B4:
	ldr r0, [r4, #8]
	mov r1, #2
	bl MOD44_02254B38
	cmp r0, #0
	beq _022549C4
	mov r0, #0
	strb r0, [r4, #1]
_022549C4:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD44_0225497C

	thumb_func_start MOD44_022549C8
MOD44_022549C8: ; 0x022549C8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD20_02252C08
	cmp r0, #0
	bne _02254A18
	add r0, sp, #4
	add r1, sp, #0
	bl FUN_02020AB0
	cmp r0, #0
	beq _02254A18
	ldr r0, [sp]
	cmp r0, #0x88
	blo _02254A18
	cmp r0, #0xa0
	bhs _02254A18
	ldr r0, [sp, #4]
	cmp r0, #0x30
	blo _02254A18
	cmp r0, #0xb8
	bhs _02254A18
	sub r0, #0x30
	lsr r1, r0, #4
	cmp r1, #8
	blo _02254A02
	mov r1, #7
_02254A02:
	ldrb r0, [r4, #3]
	cmp r1, r0
	beq _02254A18
	str r1, [r4, #4]
	strb r1, [r4, #3]
	ldr r0, [r4, #0x10]
	bl Sav2_Poketch_SetScreenTint
	add sp, #8
	mov r0, #1
	pop {r4, pc}
_02254A18:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD44_022549C8

	thumb_func_start MOD44_02254A20
MOD44_02254A20: ; 0x02254A20
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
	bl MOD44_02254B14
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A4E
_02254A40:
	ldr r0, [r4, #8]
	bl MOD44_02254B44
	cmp r0, #0
	beq _02254A4E
	mov r0, #1
	pop {r4, pc}
_02254A4E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD44_02254A20

	thumb_func_start MOD44_02254A54
MOD44_02254A54: ; 0x02254A54
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
	bl MOD20_022536F4
	str r5, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x20]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD44_02254A90
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254A8A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD44_02254A54

	thumb_func_start MOD44_02254A90
MOD44_02254A90: ; 0x02254A90
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
	bl MOD20_02253FBC
	add r2, r5, #0
	ldr r0, [r5, #0x20]
	ldr r1, _02254AE0 ; =MOD44_02254C60
	add r2, #0x28
	bl MOD20_02253E74
	str r0, [r5, #0x24]
	ldr r1, [r4]
	mov r2, #0x25
	lsl r1, r1, #4
	add r1, #0x38
	lsl r1, r1, #0xc
	lsl r2, r2, #0xe
	bl MOD20_02253F64
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02254AE0: .word MOD44_02254C60
	thumb_func_end MOD44_02254A90

	thumb_func_start MOD44_02254AE4
MOD44_02254AE4: ; 0x02254AE4
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x24]
	cmp r1, #0
	beq _02254AF4
	ldr r0, [r4, #0x20]
	bl MOD20_02253F14
_02254AF4:
	add r4, #0x28
	add r0, r4, #0
	bl MOD20_02254014
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD44_02254AE4

	thumb_func_start MOD44_02254B00
MOD44_02254B00: ; 0x02254B00
	push {r4, lr}
	add r4, r0, #0
	beq _02254B10
	bl MOD44_02254AE4
	add r0, r4, #0
	bl FreeToHeap
_02254B10:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD44_02254B00

	thumb_func_start MOD44_02254B14
MOD44_02254B14: ; 0x02254B14
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254B34 ; =MOD44_02254C8C
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254B34: .word MOD44_02254C8C
	thumb_func_end MOD44_02254B14

	thumb_func_start MOD44_02254B38
MOD44_02254B38: ; 0x02254B38
	ldr r3, _02254B40 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254B40: .word MOD20_02253794
	thumb_func_end MOD44_02254B38

	thumb_func_start MOD44_02254B44
MOD44_02254B44: ; 0x02254B44
	ldr r3, _02254B4C ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254B4C: .word MOD20_022537B8
	thumb_func_end MOD44_02254B44

	thumb_func_start MOD44_02254B50
MOD44_02254B50: ; 0x02254B50
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD44_02254B50

	thumb_func_start MOD44_02254B64
MOD44_02254B64: ; 0x02254B64
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	add r0, r4, #0
	bl MOD20_022538A4
	ldr r0, [r5, #4]
	ldr r2, _02254BEC ; =MOD44_02254C70
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
	bl MOD20_02252D7C
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
	bl MOD44_02254B50
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_02254BEC: .word MOD44_02254C70
_02254BF0: .word 0x04001000
_02254BF4: .word 0xFFFFE0FF
	thumb_func_end MOD44_02254B64

	thumb_func_start MOD44_02254BF8
MOD44_02254BF8: ; 0x02254BF8
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl MOD44_02254B50
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD44_02254BF8

	thumb_func_start MOD44_02254C14
MOD44_02254C14: ; 0x02254C14
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r4, r0, #0
	ldr r0, _02254C50 ; =0x00000663
	bl MOD20_02252B28
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	ldr r1, [r4]
	mov r2, #0x25
	lsl r1, r1, #4
	add r1, #0x38
	ldr r0, [r5, #0x24]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xe
	bl MOD20_02253F64
	add r0, r6, #0
	bl MOD44_02254B50
	pop {r4, r5, r6, pc}
	.align 2, 0
_02254C50: .word 0x00000663
	thumb_func_end MOD44_02254C14

	.section .rodata

	.global MOD44_02254C54
MOD44_02254C54: ; 0x02254C54
	.word MOD44_0225493C, MOD44_0225497C, MOD44_02254A20

	.global MOD44_02254C60
MOD44_02254C60: ; 0x02254C60
	.byte 0x00, 0x80, 0x03, 0x00
	.byte 0x00, 0x40, 0x09, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00

	.global MOD44_02254C70
MOD44_02254C70: ; 0x02254C70
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD44_02254C8C
MOD44_02254C8C: ; 0x02254C8C
	.word 0x00, MOD44_02254B64, 0x00
	.word 0x01, MOD44_02254BF8, 0x00
	.word 0x02, MOD44_02254C14, 0x00
	.word 0x00, 0x00000000, 0x00
