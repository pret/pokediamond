	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD50_022549AC
MOD50_022549AC: ; 0x022549AC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x30
	bl AllocFromHeap
	add r4, r0, #0
	beq _022549DA
	add r0, #8
	mov r1, #8
	bl MOD20_022536F4
	mov r0, #8
	str r6, [r4]
	bl BgConfig_Alloc
	str r0, [r4, #4]
	cmp r0, #0
	beq _022549DA
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_022549DA:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD50_022549AC

	thumb_func_start MOD50_022549E0
MOD50_022549E0: ; 0x022549E0
	push {r4, lr}
	add r4, r0, #0
	beq _022549F6
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _022549F0
	bl FreeToHeap
_022549F0:
	add r0, r4, #0
	bl FreeToHeap
_022549F6:
	pop {r4, pc}
	thumb_func_end MOD50_022549E0

	thumb_func_start MOD50_022549F8
MOD50_022549F8: ; 0x022549F8
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254A18 ; =MOD50_02254B2C
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254A18: .word MOD50_02254B2C
	thumb_func_end MOD50_022549F8

	thumb_func_start MOD50_02254A1C
MOD50_02254A1C: ; 0x02254A1C
	ldr r3, _02254A24 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254A24: .word MOD20_02253794
	thumb_func_end MOD50_02254A1C

	thumb_func_start MOD50_02254A28
MOD50_02254A28: ; 0x02254A28
	ldr r3, _02254A30 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254A30: .word MOD20_022537B8
	thumb_func_end MOD50_02254A28

	thumb_func_start MOD50_02254A34
MOD50_02254A34: ; 0x02254A34
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD50_02254A34

	thumb_func_start MOD50_02254A48
MOD50_02254A48: ; 0x02254A48
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254ADC ; =MOD50_02254B10
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
	ldr r1, [r5]
	ldr r0, [r5, #4]
	ldr r1, [r1]
	mov r2, #6
	bl MOD20_02253AA4
	ldr r0, [r5, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r1, _02254AE0 ; =0x04001000
	ldr r0, _02254AE4 ; =0xFFFFE0FF
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
	bl MOD50_02254A34
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_02254ADC: .word MOD50_02254B10
_02254AE0: .word 0x04001000
_02254AE4: .word 0xFFFFE0FF
	thumb_func_end MOD50_02254A48

	thumb_func_start MOD50_02254AE8
MOD50_02254AE8: ; 0x02254AE8
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl MOD50_02254A34
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD50_02254AE8

	.section .rodata

	.global MOD50_02254B10
MOD50_02254B10: ; 0x02254B10
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD50_02254B2C
MOD50_02254B2C: ; 0x02254B2C
	.word 0x00, MOD50_02254A48, 0x00
	.word 0x01, MOD50_02254AE8, 0x00
	.word 0x00, 0x00000000, 0x00
