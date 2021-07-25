	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD33_022549AC
MOD33_022549AC: ; 0x022549AC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x30
	bl AllocFromHeap
	add r4, r0, #0
	beq _022549D8
	add r0, #8
	mov r1, #8
	bl MOD20_022536F4
	str r6, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	cmp r0, #0
	beq _022549D8
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_022549D8:
	mov r0, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD33_022549AC

	thumb_func_start MOD33_022549DC
MOD33_022549DC: ; 0x022549DC
	push {r3, lr}
	cmp r0, #0
	beq _022549E6
	bl FreeToHeap
_022549E6:
	pop {r3, pc}
	thumb_func_end MOD33_022549DC

	thumb_func_start MOD33_022549E8
MOD33_022549E8: ; 0x022549E8
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254A08 ; =MOD33_02254B1C
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254A08: .word MOD33_02254B1C
	thumb_func_end MOD33_022549E8

	thumb_func_start MOD33_02254A0C
MOD33_02254A0C: ; 0x02254A0C
	ldr r3, _02254A14 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254A14: .word MOD20_02253794
	thumb_func_end MOD33_02254A0C

	thumb_func_start MOD33_02254A18
MOD33_02254A18: ; 0x02254A18
	ldr r3, _02254A20 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254A20: .word MOD20_022537B8
	thumb_func_end MOD33_02254A18

	thumb_func_start MOD33_02254A24
MOD33_02254A24: ; 0x02254A24
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD33_02254A24

	thumb_func_start MOD33_02254A38
MOD33_02254A38: ; 0x02254A38
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254ACC ; =MOD33_02254B00
	mov r1, #6
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r1, #8
	str r1, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
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
	mov r0, #0x20
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #0xc
	mov r1, #9
	mov r2, #4
	mov r3, #0
	bl GfGfxLoader_GXLoadPal
	ldr r0, [r5, #4]
	mov r1, #0xc
	mov r2, #6
	bl MOD20_02253AA4
	ldr r0, [r5, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r1, _02254AD0 ; =0x04001000
	ldr r0, _02254AD4 ; =0xFFFFE0FF
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
	bl MOD33_02254A24
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02254ACC: .word MOD33_02254B00
_02254AD0: .word 0x04001000
_02254AD4: .word 0xFFFFE0FF
	thumb_func_end MOD33_02254A38

	thumb_func_start MOD33_02254AD8
MOD33_02254AD8: ; 0x02254AD8
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl MOD33_02254A24
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD33_02254AD8

	.section .rodata

	.global MOD33_02254B00	
MOD33_02254B00: ; 0x02254B00
	.byte 0x00, 0x00, 0x00, 0x00	
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	

	.global MOD33_02254B1C
MOD33_02254B1C: ; 0x02254B1C
	.word 0x00, MOD33_02254A38, 0x00
	.word 0x01, MOD33_02254AD8, 0x00
	.word 0x00, 0x00000000, 0x00
