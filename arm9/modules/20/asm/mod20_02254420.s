	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 2, 0

	thumb_func_start MOD20_02254420
MOD20_02254420: ; 0x02254420
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r5, #0x1e
	blo _02254432
	bl GF_AssertFail
_02254432:
	cmp r4, #0x21
	blo _0225443A
	bl GF_AssertFail
_0225443A:
	cmp r5, #0x1e
	blo _02254440
	mov r5, #0
_02254440:
	cmp r4, #0x21
	blo _02254446
	mov r4, #0
_02254446:
	ldr r0, _02254458 ; =MOD20_02254744
	lsl r1, r5, #1
	ldrh r0, [r0, r1]
	lsl r1, r4, #1
	str r0, [r6]
	ldr r0, _0225445C ; =MOD20_02254780
	ldrh r0, [r0, r1]
	str r0, [r7]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254458: .word MOD20_02254744
_0225445C: .word MOD20_02254780
	thumb_func_end MOD20_02254420

	thumb_func_start MOD20_02254460
MOD20_02254460: ; 0x02254460
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	cmp r5, #4
	blo _02254470
	bl GF_AssertFail
_02254470:
	ldr r0, _02254480 ; =MOD20_02254724
	lsl r1, r5, #3
	ldr r0, [r0, r1]
	str r0, [r4]
	ldr r0, _02254484 ; =MOD20_02254724 + 4
	ldr r0, [r0, r1]
	str r0, [r6]
	pop {r4, r5, r6, pc}
	.align 2, 0
_02254480: .word MOD20_02254724
_02254484: .word MOD20_02254724 + 4
	thumb_func_end MOD20_02254460

	thumb_func_start MOD20_02254488
MOD20_02254488: ; 0x02254488
	push {r4, r5}
	ldr r5, _022544B8 ; =MOD20_022547C2
	mov r4, #0
_0225448E:
	ldrh r3, [r5]
	cmp r0, r3
	bne _022544A8
	ldr r0, _022544BC ; =MOD20_022547C2 + 2
	lsl r3, r4, #2
	ldrb r0, [r0, r3]
	str r0, [r1]
	ldr r0, _022544C0 ; =MOD20_022547C2 + 3
	ldrb r0, [r0, r3]
	str r0, [r2]
	mov r0, #1
	pop {r4, r5}
	bx lr
_022544A8:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x1d
	blo _0225448E
	mov r0, #0
	pop {r4, r5}
	bx lr
	nop
_022544B8: .word MOD20_022547C2
_022544BC: .word MOD20_022547C2 + 2
_022544C0: .word MOD20_022547C2 + 3
	thumb_func_end MOD20_02254488

	.section .rodata

	.global MOD20_02254724
MOD20_02254724: ; 0x02254724
	.word 0x00000020, 0x0000002A
	.word 0x00000032, 0x0000002A
	.word 0x000000A8, 0x0000007A
	.word 0x000000C2, 0x0000003A

	.global MOD20_02254744
MOD20_02254744: ; 0x02254744
	.short 0x001A, 0x0020, 0x0026, 0x002C, 0x0032, 0x0038, 0x003E, 0x0044
	.short 0x004A, 0x0050, 0x0056, 0x005C, 0x0062, 0x0068, 0x006E, 0x0074
	.short 0x007A, 0x0080, 0x0086, 0x008C, 0x0092, 0x0098, 0x009E, 0x00A4
	.short 0x00AA, 0x00B0, 0x00B6, 0x00BC, 0x00C2, 0x00C8

	.global MOD20_02254780
MOD20_02254780: ; 0x02254780
	.short 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0018, 0x001E, 0x0024
	.short 0x002A, 0x0030, 0x0036, 0x003C, 0x0042, 0x0048, 0x004E, 0x0054
	.short 0x005A, 0x0060, 0x0066, 0x006C, 0x0072, 0x0078, 0x007E, 0x0084
	.short 0x008A, 0x0090, 0x0096, 0x009C, 0x00A2, 0x00A8, 0x00AE, 0x00B4
	.short 0x00BA

	.global MOD20_022547C2
MOD20_022547C2: ; 0x022547C2
	.short 0x0156
	.byte 0x2F, 0x96
	.short 0x0157
	.byte 0x38, 0x90
	.short 0x0158
	.byte 0x41, 0x84
	.short 0x0159
	.byte 0x32, 0x7E
	.short 0x015A
	.byte 0x32, 0x78
	.short 0x015B
	.byte 0x3E, 0x6C
	.short 0x015D
	.byte 0x4A, 0x5A
	.short 0x015E
	.byte 0x50, 0x6F
	.short 0x0161
	.byte 0x53, 0x7E
	.short 0x0162
	.byte 0x65, 0x7E
	.short 0x0164
	.byte 0x7D, 0x7E
	.short 0x016A
	.byte 0x80, 0x66
	.short 0x016B
	.byte 0x7A, 0x5A
	.short 0x016D
	.byte 0x5C, 0x5A
	.short 0x016E
	.byte 0x68, 0x5A
	.short 0x016F
	.byte 0x6E, 0x8A
	.short 0x0173
	.byte 0x77, 0x96
	.short 0x0175
	.byte 0x98, 0x93
	.short 0x017C
	.byte 0x98, 0x78
	.short 0x017E
	.byte 0x8C, 0x66
	.short 0x017F
	.byte 0x56, 0x42
	.short 0x0181
	.byte 0x50, 0x33
	.short 0x0184
	.byte 0x29, 0x84
	.short 0x0187
	.byte 0x38, 0x9C
	.short 0x01D3
	.byte 0x3B, 0xA2
	.short 0x0188
	.byte 0x4A, 0xA2
	.short 0x018B
	.byte 0xAA, 0x8A
	.short 0x00C8
	.byte 0x44, 0x72
	.short 0x00CC
	.byte 0x38, 0x66

	.data
	.bss
