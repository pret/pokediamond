	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD48_02254854
MOD48_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x40
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD48_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD48_02254950
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
_02254898: .word MOD48_02254950
	thumb_func_end MOD48_02254854

	thumb_func_start MOD48_0225489C
MOD48_0225489C: ; 0x0225489C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	add r0, r1, #0
	str r1, [sp, #4]
	str r2, [sp, #8]
	bl MOD20_02252C38
	add r6, r0, #0
	bl MOD06_02245824
	str r0, [r7, #8]
	cmp r0, #0
	beq _022548C0
	add r0, r6, #0
	bl MOD06_0224582C
	b _022548C2
_022548C0:
	mov r0, #0
_022548C2:
	str r0, [r7, #4]
	mov r4, #0
	add r5, r7, #0
_022548C8:
	lsl r1, r4, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x18
	bl MOD06_022457F8
	lsl r1, r4, #0x18
	str r0, [r5, #0x18]
	add r0, r6, #0
	lsr r1, r1, #0x18
	bl MOD06_022457CC
	str r0, [r5, #0xc]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _022548C8
	add r0, r6, #0
	bl MOD06_022457A8
	str r0, [r7, #0x24]
	add r0, r7, #0
	ldr r2, [sp, #8]
	add r0, #0x2c
	add r1, r7, #4
	bl MOD48_02254AA0
	cmp r0, #0
	beq _0225492A
	mov r0, #0
	strb r0, [r7]
	strb r0, [r7, #1]
	strb r0, [r7, #2]
	mov r0, #8
	str r0, [sp]
	ldr r0, _02254930 ; =MOD48_02254F60
	ldr r2, _02254934 ; =MOD48_02254994
	mov r1, #3
	add r3, r7, #0
	bl MOD20_02254130
	str r0, [r7, #0x34]
	mov r0, #0
	str r0, [r7, #0x38]
	str r0, [r7, #0x3c]
	ldr r0, [sp, #4]
	add sp, #0xc
	str r0, [r7, #0x30]
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0225492A:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254930: .word MOD48_02254F60
_02254934: .word MOD48_02254994
	thumb_func_end MOD48_0225489C

	thumb_func_start MOD48_02254938
MOD48_02254938: ; 0x02254938
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	bl MOD20_02254198
	ldr r0, [r4, #0x2c]
	bl MOD48_02254AD4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD48_02254938

	thumb_func_start MOD48_02254950
MOD48_02254950: ; 0x02254950
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _02254986
	ldr r0, [r4, #0x30]
	ldr r1, [r4, #0x34]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254988 ; =MOD48_02254F6C
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254986
	add r0, r4, #0
	bl MOD48_02254938
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x30]
	bl MOD20_022529A0
_02254986:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254988: .word MOD48_02254F6C
	thumb_func_end MOD48_02254950

	thumb_func_start MOD48_0225498C
MOD48_0225498C: ; 0x0225498C
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD48_0225498C

	thumb_func_start MOD48_02254994
MOD48_02254994: ; 0x02254994
	str r0, [r3, #0x3c]
	str r1, [r3, #0x38]
	bx lr
	.align 2, 0
	thumb_func_end MOD48_02254994

	thumb_func_start MOD48_0225499C
MOD48_0225499C: ; 0x0225499C
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _022549A4
	b _022549A6
_022549A4:
	mov r1, #2
_022549A6:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD48_0225499C

	thumb_func_start MOD48_022549B0
MOD48_022549B0: ; 0x022549B0
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549C0
	cmp r0, #1
	beq _022549D0
	b _022549EA
_022549C0:
	ldr r0, [r4, #0x2c]
	mov r1, #0
	bl MOD48_02254AE0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549EA
_022549D0:
	ldr r0, [r4, #0x2c]
	mov r1, #0
	bl MOD48_02254B04
	cmp r0, #0
	beq _022549EA
	ldr r0, [r4, #0x30]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD48_0225499C
_022549EA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD48_022549B0

	thumb_func_start MOD48_022549F0
MOD48_022549F0: ; 0x022549F0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254A04
	mov r1, #2
	bl MOD48_0225499C
	mov r0, #0
	pop {r3, r4, r5, pc}
_02254A04:
	ldr r0, [r4, #0x30]
	bl MOD20_02252C38
	add r5, r0, #0
	bl MOD06_02245824
	str r0, [r4, #8]
	cmp r0, #0
	bne _02254A1A
	mov r0, #0
	b _02254A20
_02254A1A:
	add r0, r5, #0
	bl MOD06_0224582C
_02254A20:
	ldr r1, [r4, #4]
	cmp r0, r1
	beq _02254A34
	str r0, [r4, #4]
	ldr r0, [r4, #0x2c]
	mov r1, #2
	bl MOD48_02254AE0
	mov r0, #0
	pop {r3, r4, r5, pc}
_02254A34:
	ldr r0, [r4, #0x2c]
	mov r1, #3
	bl MOD48_02254B04
	cmp r0, #0
	beq _02254A66
	ldr r0, [r4, #0x38]
	cmp r0, #1
	bne _02254A66
	ldr r1, [r4, #0x3c]
	ldr r0, [r4, #0x24]
	cmp r1, r0
	bhs _02254A62
	lsl r0, r1, #2
	add r0, r4, r0
	ldr r0, [r0, #0x18]
	cmp r0, #0
	beq _02254A62
	str r1, [r4, #0x28]
	ldr r0, [r4, #0x2c]
	mov r1, #3
	bl MOD48_02254AE0
_02254A62:
	mov r0, #0
	str r0, [r4, #0x38]
_02254A66:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD48_022549F0

	thumb_func_start MOD48_02254A6C
MOD48_02254A6C: ; 0x02254A6C
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A7C
	cmp r0, #1
	beq _02254A8C
	b _02254A9A
_02254A7C:
	ldr r0, [r4, #0x2c]
	mov r1, #1
	bl MOD48_02254AE0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A9A
_02254A8C:
	ldr r0, [r4, #0x2c]
	bl MOD48_02254B10
	cmp r0, #0
	beq _02254A9A
	mov r0, #1
	pop {r4, pc}
_02254A9A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD48_02254A6C

	thumb_func_start MOD48_02254AA0
MOD48_02254AA0: ; 0x02254AA0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0xb0
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254ACE
	add r0, #8
	mov r1, #4
	bl MOD20_022536F4
	str r6, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x20]
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254ACE:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD48_02254AA0

	thumb_func_start MOD48_02254AD4
MOD48_02254AD4: ; 0x02254AD4
	push {r3, lr}
	cmp r0, #0
	beq _02254ADE
	bl FreeToHeap
_02254ADE:
	pop {r3, pc}
	thumb_func_end MOD48_02254AD4

	thumb_func_start MOD48_02254AE0
MOD48_02254AE0: ; 0x02254AE0
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254B00 ; =MOD48_02254F94
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254B00: .word MOD48_02254F94
	thumb_func_end MOD48_02254AE0

	thumb_func_start MOD48_02254B04
MOD48_02254B04: ; 0x02254B04
	ldr r3, _02254B0C ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254B0C: .word MOD20_02253794
	thumb_func_end MOD48_02254B04

	thumb_func_start MOD48_02254B10
MOD48_02254B10: ; 0x02254B10
	ldr r3, _02254B18 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254B18: .word MOD20_022537B8
	thumb_func_end MOD48_02254B10

	thumb_func_start MOD48_02254B1C
MOD48_02254B1C: ; 0x02254B1C
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD48_02254B1C

	thumb_func_start MOD48_02254B30
MOD48_02254B30: ; 0x02254B30
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r6, r0, #0
	ldr r0, [r4, #4]
	ldr r2, _02254BBC ; =MOD48_02254F78
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0xc
	mov r1, #0x7a
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0xc
	mov r1, #0x79
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	add r0, r4, #0
	add r1, r6, #0
	bl MOD48_02254D2C
	ldr r1, _02254BC0 ; =0x04001000
	ldr r0, _02254BC4 ; =0xFFFFE0FF
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
	add r0, r5, #0
	bl MOD48_02254B1C
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_02254BBC: .word MOD48_02254F78
_02254BC0: .word 0x04001000
_02254BC4: .word 0xFFFFE0FF
	thumb_func_end MOD48_02254B30

	thumb_func_start MOD48_02254BC8
MOD48_02254BC8: ; 0x02254BC8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	bl MOD48_02254EC0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r5, #0
	bl MOD48_02254B1C
	pop {r3, r4, r5, pc}
	thumb_func_end MOD48_02254BC8

	thumb_func_start MOD48_02254BE8
MOD48_02254BE8: ; 0x02254BE8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r0, r7, #0
	bl MOD20_022538A0
	add r5, r0, #0
	add r0, r7, #0
	bl MOD20_022538A4
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _02254C3C
	mov r1, #0
	add r2, r1, #0
	bl FUN_0206B6D4
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xac
	mov r2, #1
	ldr r0, [r0]
	add r1, sp, #0
	add r3, r2, #0
	bl MOD20_02253A04
	mov r1, #0
	ldr r0, [r4]
	add r2, r1, #0
	bl FUN_0206B7BC
	add r1, r0, #0
	ldr r0, [r5, #0x24]
	add r1, r1, #1
	bl MOD20_02253F9C
	add r5, #0x34
	ldr r1, [r4, #4]
	add r0, r5, #0
	bl MOD48_02254EF4
	b _02254C58
_02254C3C:
	ldr r0, [r5, #0x24]
	mov r1, #1
	bl MOD20_02253F78
	mov r4, #0
	mov r6, #1
_02254C48:
	ldr r0, [r5, #0x34]
	add r1, r6, #0
	bl MOD20_02253F78
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _02254C48
_02254C58:
	add r0, r7, #0
	bl MOD48_02254B1C
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD48_02254BE8

	thumb_func_start MOD48_02254C60
MOD48_02254C60: ; 0x02254C60
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r0, r7, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r7, #0
	bl MOD20_022538A4
	add r6, r0, #0
	add r0, r7, #0
	bl MOD20_022538AC
	add r5, r0, #0
	beq _02254C84
	cmp r5, #0x10
	beq _02254CFE
	b _02254CC6
_02254C84:
	ldr r0, [r6, #0x24]
	add r2, r4, #0
	add r0, r0, #1
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r1, [r0, #0x24]
	add r0, r4, #0
	add r0, #0x9c
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x9c
	add r1, r4, #0
	ldr r0, [r0]
	add r1, #0xa4
	add r2, #0xa0
	bl MOD20_02253F6C
	ldr r0, [r6, #0x24]
	lsl r0, r0, #2
	add r0, r6, r0
	ldr r0, [r0, #8]
	bl MOD20_02252B48
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	mov r1, #6
	bl MOD20_02253F28
	add r0, r7, #0
	bl MOD20_022538B0
	add r5, r5, #1
_02254CC6:
	add r0, r4, #0
	add r1, r4, #0
	add r4, #0xa0
	mov r3, #0x2d
	ldr r2, [r4]
	lsl r3, r3, #0xa
	add r4, r5, #0
	mul r4, r3
	mov r3, #2
	lsl r3, r3, #0xa
	add r3, r4, r3
	asr r3, r3, #0xc
	lsl r4, r3, #2
	ldr r3, _02254D28 ; =gSineTable
	add r0, #0x9c
	ldr r4, [r3, r4]
	add r1, #0xa4
	mov r3, #0x18
	mul r3, r4
	ldr r0, [r0]
	ldr r1, [r1]
	sub r2, r2, r3
	bl MOD20_02253F64
	add r0, r7, #0
	bl MOD20_022538B0
	pop {r3, r4, r5, r6, r7, pc}
_02254CFE:
	add r0, r4, #0
	add r1, r4, #0
	add r2, r4, #0
	add r0, #0x9c
	add r1, #0xa4
	add r2, #0xa0
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r2]
	bl MOD20_02253F64
	add r4, #0x9c
	ldr r0, [r4]
	mov r1, #4
	bl MOD20_02253F28
	add r0, r7, #0
	bl MOD48_02254B1C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254D28: .word gSineTable
	thumb_func_end MOD48_02254C60

	thumb_func_start MOD48_02254D2C
MOD48_02254D2C: ; 0x02254D2C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r4, r0, #0
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	str r1, [sp, #0xc]
	add r0, #0x78
	mov r1, #0xc
	mov r2, #5
	mov r3, #6
	bl MOD20_02253FBC
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0xc
	mov r2, #0x7b
	mov r3, #0x7c
	bl MOD20_02253FBC
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x7d
	bl GfGfxLoader_LoadWholePalette
	add r1, r4, #0
	lsr r0, r0, #5
	add r1, #0xac
	str r0, [r1]
	str r0, [sp, #0x28]
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0xc]
	ldr r0, [r0]
	mov r1, #0
	str r0, [sp, #0x30]
	add r3, sp, #0x30
_02254D82:
	ldr r0, [r2, #8]
	add r1, r1, #1
	str r0, [r3, #4]
	add r2, r2, #4
	add r3, r3, #4
	cmp r1, #3
	blt _02254D82
	mov r7, #0
	add r5, sp, #0x30
	add r6, r4, #0
_02254D96:
	ldr r0, [r5]
	cmp r0, #0
	bne _02254D9E
	mov r0, #1
_02254D9E:
	mov r1, #0
	add r2, r1, #0
	bl FUN_0206B6D4
	add r1, r6, #0
	add r1, #0x8c
	add r7, r7, #1
	str r0, [r1]
	add r5, r5, #4
	add r6, r6, #4
	cmp r7, #4
	blt _02254D96
	add r1, r4, #0
	ldr r0, [sp, #0x28]
	add r1, #0x8c
	mov r2, #4
	mov r3, #1
	bl MOD20_02253A04
	mov r0, #1
	bl MOD20_022539C4
	mov r2, #0
	add r0, r2, #0
	add r1, r4, #0
	str r0, [sp, #0x10]
_02254DD2:
	ldr r0, [sp, #0x10]
	add r2, r2, #1
	str r0, [r1, #0x24]
	add r1, r1, #4
	cmp r2, #0x10
	blt _02254DD2
	ldr r0, _02254EBC ; =MOD48_02254FD0
	str r4, [sp, #0x20]
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x10]
	mov r6, #4
	str r0, [sp, #0x1c]
	add r0, sp, #0x30
	str r0, [sp, #0x18]
	ldr r0, [sp, #0xc]
	str r0, [sp, #0x14]
_02254DF2:
	add r2, r4, #0
	ldr r0, [r4, #0x20]
	ldr r1, [sp, #0x24]
	add r2, #0x78
	bl MOD20_02253E74
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x28]
	str r0, [r1, #0x24]
	ldr r1, [sp, #0x1c]
	add r1, r2, r1
	bl MOD20_02253FA4
	add r0, r4, #0
	str r0, [sp, #0x2c]
	add r0, #0x64
	mov r5, #0
	str r0, [sp, #0x2c]
_02254E16:
	add r7, r5, r6
	ldr r1, _02254EBC ; =MOD48_02254FD0
	lsl r2, r7, #4
	add r1, r1, r2
	ldr r0, [r4, #0x20]
	ldr r2, [sp, #0x2c]
	bl MOD20_02253E74
	lsl r1, r7, #2
	add r1, r4, r1
	add r5, r5, #1
	str r0, [r1, #0x24]
	cmp r5, #3
	blt _02254E16
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	cmp r0, #0
	bne _02254E5E
	ldr r0, [sp, #0x20]
	mov r1, #1
	ldr r0, [r0, #0x24]
	bl MOD20_02253F78
	mov r5, #0
	mov r7, #1
_02254E48:
	add r0, r5, r6
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	add r1, r7, #0
	bl MOD20_02253F78
	add r5, r5, #1
	cmp r5, #3
	blt _02254E48
	b _02254E8E
_02254E5E:
	mov r1, #0
	add r2, r1, #0
	bl FUN_0206B7BC
	add r1, r0, #0
	ldr r0, [sp, #0x20]
	add r1, r1, #1
	ldr r0, [r0, #0x24]
	bl MOD20_02253F9C
	ldr r0, [sp, #0x10]
	cmp r0, #0
	bne _02254E7E
	ldr r0, [sp, #0xc]
	ldr r1, [r0, #4]
	b _02254E82
_02254E7E:
	ldr r0, [sp, #0x14]
	ldr r1, [r0, #0x10]
_02254E82:
	add r2, r4, #0
	add r2, #0x24
	lsl r0, r6, #2
	add r0, r2, r0
	bl MOD48_02254EF4
_02254E8E:
	ldr r0, [sp, #0x24]
	add r6, r6, #3
	add r0, #0x10
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x20]
	add r0, r0, #4
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r0, #0x20
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r0, r0, #4
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r0, r0, #4
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, #4
	blt _02254DF2
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254EBC: .word MOD48_02254FD0
	thumb_func_end MOD48_02254D2C

	thumb_func_start MOD48_02254EC0
MOD48_02254EC0: ; 0x02254EC0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
	add r7, r4, #0
_02254ECA:
	ldr r1, [r5, #0x24]
	cmp r1, #0
	beq _02254ED8
	ldr r0, [r6, #0x20]
	bl MOD20_02253F14
	str r7, [r5, #0x24]
_02254ED8:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x10
	blt _02254ECA
	add r0, r6, #0
	add r0, #0x78
	bl MOD20_02254014
	add r6, #0x64
	add r0, r6, #0
	bl MOD20_02254014
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD48_02254EC0

	thumb_func_start MOD48_02254EF4
MOD48_02254EF4: ; 0x02254EF4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	str r1, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r1, _02254F5C ; =0x000003E7
	ldr r0, [sp]
	cmp r0, r1
	bls _02254F0A
	str r1, [sp]
_02254F0A:
	mov r4, #0
	mov r6, #0x64
_02254F0E:
	ldr r0, [sp]
	add r1, r6, #0
	bl _u32_div_f
	add r7, r0, #0
	ldr r0, [sp, #4]
	cmp r0, #1
	beq _02254F26
	cmp r7, #0
	bne _02254F26
	cmp r4, #2
	bne _02254F34
_02254F26:
	ldr r0, [r5]
	add r1, r7, #0
	bl MOD20_02253F28
	mov r0, #1
	str r0, [sp, #4]
	b _02254F3C
_02254F34:
	ldr r0, [r5]
	mov r1, #1
	bl MOD20_02253F78
_02254F3C:
	add r1, r7, #0
	ldr r0, [sp]
	mul r1, r6
	sub r0, r0, r1
	str r0, [sp]
	add r0, r6, #0
	mov r1, #0xa
	add r5, r5, #4
	add r4, r4, #1
	bl _s32_div_f
	add r6, r0, #0
	cmp r4, #3
	blt _02254F0E
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254F5C: .word 0x000003E7
	thumb_func_end MOD48_02254EF4

	.section .rodata

	.global MOD48_02254F60
MOD48_02254F60: ; 0x02254F60
	.byte 0x3E, 0x62, 0x58, 0x88
	.byte 0x4E, 0x72, 0x98, 0xC8
	.byte 0x56, 0x7A, 0x18, 0x48

	.global MOD48_02254F6C
MOD48_02254F6C: ; 0x02254F6C
	.word MOD48_022549B0, MOD48_022549F0, MOD48_02254A6C

	.global MOD48_02254F78
MOD48_02254F78: ; 0x02254F78
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x03, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD48_02254F94
MOD48_02254F94: ; 0x02254F94
	.word 0x00, MOD48_02254B30, 0x00
	.word 0x01, MOD48_02254BC8, 0x00
	.word 0x02, MOD48_02254BE8, 0x00
	.word 0x03, MOD48_02254C60, 0x00
	.word 0x00, 0x00000000, 0x00

	.global MOD48_02254FD0
MOD48_02254FD0: ; 0x02254FD0
	.byte 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x02, 0x0A, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x02, 0x01, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x00, 0x80, 0x06, 0x00, 0x04, 0x00, 0x00, 0x02, 0x02, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x80, 0x09, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x0A, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x40, 0x06, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0xC0, 0x06, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x40, 0x07, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x40, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0xC0, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x40, 0x0B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x40, 0x02, 0x00, 0x00, 0x80, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0xC0, 0x02, 0x00, 0x00, 0x80, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x40, 0x03, 0x00, 0x00, 0x80, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
