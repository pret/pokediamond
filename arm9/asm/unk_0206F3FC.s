    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_021C48F8
	.extern gUnknown21C48B8

	.section .rodata

	.global UNK_020F944C
UNK_020F944C: ; 0x020F944C
	.byte 0x01

	.global UNK_020F944D
UNK_020F944D: ; 0x020F944D
	.byte 0x03, 0x1A, 0x03, 0x01, 0x0A, 0x1A, 0x0A, 0x01, 0x11, 0x1A, 0x11

	.global UNK_020F9458
UNK_020F9458: ; 0x020F9458
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F9468
UNK_020F9468: ; 0x020F9468
	.byte 0x00, 0x02, 0x04, 0x01, 0x03, 0x05, 0x01, 0x03, 0x05, 0x00, 0x02, 0x04, 0x04, 0x02, 0x00, 0x05
	.byte 0x03, 0x01, 0x05, 0x03, 0x01, 0x04, 0x02, 0x00

	.global UNK_020F9480
UNK_020F9480: ; 0x020F9480
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F949C
UNK_020F949C: ; 0x020F949C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F94B8
UNK_020F94B8: ; 0x020F94B8
	.byte 0x18, 0x3F, 0x08, 0x2F, 0x18, 0x3F, 0xD0, 0xF7, 0x50, 0x77, 0x08, 0x2F, 0x50, 0x77, 0xD0, 0xF7
	.byte 0x88, 0xAF, 0x08, 0x2F, 0x88, 0xAF, 0xD0, 0xF7, 0xFF, 0x00, 0x00, 0x00

	.global UNK_020F94D4
UNK_020F94D4: ; 0x020F94D4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F94F0
UNK_020F94F0: ; 0x020F94F0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F950C
UNK_020F950C: ; 0x020F950C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F9528
UNK_020F9528: ; 0x020F9528
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F9544
UNK_020F9544: ; 0x020F9544
	.byte 0x0F, 0x00, 0x13, 0x00, 0x39, 0x00, 0x46, 0x00, 0xB0, 0x01, 0xF9, 0x00, 0x7F, 0x00, 0xAF, 0x01
	.byte 0x94, 0x00, 0x64, 0x00, 0x5B, 0x00, 0xE6, 0x00, 0xC0, 0x01, 0xD0, 0x00, 0x87, 0x00, 0x00, 0x00

	.global UNK_020F9564
UNK_020F9564: ; 0x020F9564
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F958C
UNK_020F958C: ; 0x020F958C
	.byte 0x40, 0x19, 0x00, 0x00, 0x07, 0x02, 0x07, 0x01, 0xC0, 0x21, 0x00, 0x00, 0x07, 0x03, 0x00, 0x02
	.byte 0x40, 0x49, 0x00, 0x00, 0x00, 0x04, 0x01, 0x03, 0xC0, 0x51, 0x00, 0x00, 0x01, 0x05, 0x02, 0x04
	.byte 0x40, 0x79, 0x00, 0x00, 0x02, 0x07, 0x03, 0x05, 0xC0, 0x81, 0x00, 0x00, 0x03, 0x07, 0x04, 0x07
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xA8, 0x00, 0x00, 0x05, 0x01, 0x05, 0x00

	.global UNK_020F95CC
UNK_020F95CC: ; 0x020F95CC
	.byte 0x40, 0x19, 0x00, 0x00, 0x04, 0x02, 0x01, 0x01, 0xC0, 0x19, 0x00, 0x00, 0x07, 0x03, 0x00, 0x00
	.byte 0x40, 0x49, 0x00, 0x00, 0x00, 0x04, 0x03, 0x03, 0xC0, 0x49, 0x00, 0x00, 0x01, 0x05, 0x02, 0x02
	.byte 0x40, 0x79, 0x00, 0x00, 0x02, 0x00, 0x05, 0x05, 0xC0, 0x79, 0x00, 0x00, 0x03, 0x07, 0x04, 0x04
	.byte 0xE0, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xA8, 0x00, 0x00, 0x05, 0x01, 0xFF, 0xFF

	.global UNK_020F960C
UNK_020F960C: ; 0x020F960C
	.byte 0x40, 0x19, 0x00, 0x00, 0x07, 0x02, 0x07, 0x01, 0xC0, 0x21, 0x00, 0x00, 0x07, 0x03, 0x00, 0x02
	.byte 0x40, 0x49, 0x00, 0x00, 0x00, 0x04, 0x01, 0x03, 0xC0, 0x51, 0x00, 0x00, 0x01, 0x05, 0x02, 0x04
	.byte 0x40, 0x79, 0x00, 0x00, 0x02, 0x06, 0x03, 0x05, 0xC0, 0x81, 0x00, 0x00, 0x03, 0x06, 0x04, 0x06
	.byte 0xE0, 0xA8, 0x00, 0x00, 0x05, 0x07, 0x05, 0x07, 0xE0, 0xB8, 0x00, 0x00, 0x06, 0x01, 0x06, 0x00

	.global UNK_020F964C
UNK_020F964C: ; 0x020F964C
	.byte 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x10, 0x00, 0x10, 0x00, 0x0E, 0x00, 0x10, 0x00, 0x01, 0x00
	.byte 0x9E, 0x00, 0x18, 0x00, 0x90, 0x00, 0x16, 0x00, 0x00, 0x00, 0x06, 0x00, 0x1E, 0x00, 0x40, 0x00
	.byte 0x10, 0x00, 0x3E, 0x00, 0x10, 0x00, 0x07, 0x00, 0x9E, 0x00, 0x48, 0x00, 0x90, 0x00, 0x46, 0x00
	.byte 0x00, 0x00, 0x0C, 0x00, 0x1E, 0x00, 0x70, 0x00, 0x10, 0x00, 0x6E, 0x00, 0x10, 0x00, 0x0D, 0x00
	.byte 0x9E, 0x00, 0x78, 0x00, 0x90, 0x00, 0x76, 0x00

	.global UNK_020F9694
UNK_020F9694: ; 0x020F9694
	.byte 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x10, 0x00, 0x10, 0x00, 0x0E, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x9E, 0x00, 0x10, 0x00, 0x90, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x06, 0x00, 0x1E, 0x00, 0x40, 0x00
	.byte 0x10, 0x00, 0x3E, 0x00, 0x10, 0x00, 0x06, 0x00, 0x9E, 0x00, 0x40, 0x00, 0x90, 0x00, 0x3E, 0x00
	.byte 0x00, 0x00, 0x0C, 0x00, 0x1E, 0x00, 0x70, 0x00, 0x10, 0x00, 0x6E, 0x00, 0x10, 0x00, 0x0C, 0x00
	.byte 0x9E, 0x00, 0x70, 0x00, 0x90, 0x00, 0x6E, 0x00

	.global UNK_020F96DC
UNK_020F96DC: ; 0x020F96DC
	.word FUN_0206F3FC, FUN_0206F5AC, FUN_0206FAA4, 0xFFFFFFFF

	.text

	thumb_func_start FUN_0206F3FC
FUN_0206F3FC: ; 0x0206F3FC
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r2, [r0, #0x0]
	ldr r1, _0206F594 ; =0xFFFFE0FF
	ldr r3, _0206F598 ; =0x04001000
	and r2, r1
	str r2, [r0, #0x0]
	ldr r2, [r3, #0x0]
	add r0, #0x50
	and r1, r2
	str r1, [r3, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x0]
	add r3, #0x50
	strh r1, [r3, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	mov r2, #0x2
	mov r0, #0x3
	mov r1, #0xc
	lsl r2, r2, #0x10
	bl FUN_0201681C
	add r0, r4, #0x0
	bl FUN_0206FE74
	add r4, r0, #0x0
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0xc
	str r1, [sp, #0x8]
	mov r1, #0x3
	add r2, r1, #0x0
	mov r3, #0x0
	bl FUN_0200E1D0
	add r0, r4, #0x0
	bl FUN_0206FF74
	bl FUN_0206FB80
	ldr r0, [r4, #0x0]
	bl FUN_0206FBA0
	add r0, r4, #0x0
	bl FUN_0206FD24
	bl FUN_0201CC08
	mov r0, #0x4
	bl FUN_0201CC24
	mov r1, #0x0
	mov r0, #0x39
	add r2, r1, #0x0
	bl FUN_0200433C
	add r0, r4, #0x0
	bl FUN_02072590
	add r0, r4, #0x0
	bl FUN_02073710
	add r0, r4, #0x0
	bl FUN_0207388C
	add r0, r4, #0x0
	bl FUN_0206FFB4
	add r0, r4, #0x0
	bl FUN_0207047C
	ldr r1, _0206F59C ; =0x00000B25
	add r0, r4, #0x0
	ldrb r1, [r4, r1]
	mov r2, #0x1
	bl FUN_020713EC
	ldr r1, _0206F5A0 ; =0x000005A4
	ldr r3, [r4, r1]
	add r0, r3, #0x0
	add r0, #0x20
	ldrb r2, [r0, #0x0]
	cmp r2, #0x5
	beq _0206F4CC
	cmp r2, #0x10
	bne _0206F4E2
_0206F4CC:
	ldrh r0, [r3, #0x24]
	bl FUN_02076144
	cmp r0, #0x0
	bne _0206F564
	add r0, r4, #0x0
	mov r1, #0x20
	mov r2, #0x1
	bl FUN_020731C0
	b _0206F564
_0206F4E2:
	cmp r2, #0x6
	bne _0206F4F2
	add r0, r4, #0x0
	mov r1, #0x21
	mov r2, #0x1
	bl FUN_020731C0
	b _0206F564
_0206F4F2:
	cmp r2, #0x9
	beq _0206F4FA
	cmp r2, #0xe
	bne _0206F506
_0206F4FA:
	add r0, r4, #0x0
	mov r1, #0x1f
	mov r2, #0x1
	bl FUN_020731C0
	b _0206F564
_0206F506:
	cmp r2, #0x7
	beq _0206F51A
	cmp r2, #0x8
	beq _0206F51A
	add r0, r2, #0x0
	add r0, #0xf5
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	bhi _0206F526
_0206F51A:
	ldr r0, _0206F5A4 ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C664
	b _0206F564
_0206F526:
	cmp r2, #0x2
	beq _0206F52E
	cmp r2, #0x11
	bne _0206F53A
_0206F52E:
	add r0, r4, #0x0
	mov r1, #0x22
	mov r2, #0x1
	bl FUN_020731C0
	b _0206F564
_0206F53A:
	cmp r2, #0xf
	bne _0206F54A
	add r0, r4, #0x0
	mov r1, #0x22
	mov r2, #0x1
	bl FUN_020731C0
	b _0206F564
_0206F54A:
	cmp r2, #0xa
	beq _0206F55A
	add r0, r4, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731C0
	b _0206F564
_0206F55A:
	add r1, #0x24
	ldr r0, [r4, r1]
	mov r1, #0x1
	bl FUN_0200C664
_0206F564:
	add r0, r4, #0x0
	bl FUN_02072720
	add r0, r4, #0x0
	bl FUN_02070AA4
	add r0, r4, #0x0
	bl FUN_0207248C
	cmp r0, #0x0
	bne _0206F582
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201E74C
_0206F582:
	ldr r0, _0206F5A8 ; =FUN_0206FB58
	add r1, r4, #0x0
	bl FUN_02015F10
	bl FUN_02033F20
	mov r0, #0x1
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4
_0206F594: .word 0xFFFFE0FF
_0206F598: .word 0x04001000
_0206F59C: .word 0x00000B25
_0206F5A0: .word 0x000005A4
_0206F5A4: .word 0x000005C8
_0206F5A8: .word FUN_0206FB58

	thumb_func_start FUN_0206F5AC
FUN_0206F5AC: ; 0x0206F5AC
	push {r3-r5, lr}
	add r4, r1, #0x0
	bl FUN_02006278
	ldr r1, [r4, #0x0]
	add r5, r0, #0x0
	cmp r1, #0x1c
	bhi _0206F61C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0206F5C8: ; jump table (using 16-bit offset)
	.short _0206F602 - _0206F5C8 - 2; case 0
	.short _0206F60A - _0206F5C8 - 2; case 1
	.short _0206F612 - _0206F5C8 - 2; case 2
	.short _0206F624 - _0206F5C8 - 2; case 3
	.short _0206F62C - _0206F5C8 - 2; case 4
	.short _0206F634 - _0206F5C8 - 2; case 5
	.short _0206F63E - _0206F5C8 - 2; case 6
	.short _0206F646 - _0206F5C8 - 2; case 7
	.short _0206F64E - _0206F5C8 - 2; case 8
	.short _0206F656 - _0206F5C8 - 2; case 9
	.short _0206F65E - _0206F5C8 - 2; case 10
	.short _0206F666 - _0206F5C8 - 2; case 11
	.short _0206F66E - _0206F5C8 - 2; case 12
	.short _0206F676 - _0206F5C8 - 2; case 13
	.short _0206F67E - _0206F5C8 - 2; case 14
	.short _0206F686 - _0206F5C8 - 2; case 15
	.short _0206F68E - _0206F5C8 - 2; case 16
	.short _0206F696 - _0206F5C8 - 2; case 17
	.short _0206F69E - _0206F5C8 - 2; case 18
	.short _0206F6A6 - _0206F5C8 - 2; case 19
	.short _0206F6AE - _0206F5C8 - 2; case 20
	.short _0206F6B6 - _0206F5C8 - 2; case 21
	.short _0206F6BE - _0206F5C8 - 2; case 22
	.short _0206F6C6 - _0206F5C8 - 2; case 23
	.short _0206F6CE - _0206F5C8 - 2; case 24
	.short _0206F6E6 - _0206F5C8 - 2; case 25
	.short _0206F6F4 - _0206F5C8 - 2; case 26
	.short _0206F6FC - _0206F5C8 - 2; case 27
	.short _0206F70A - _0206F5C8 - 2; case 28
_0206F602:
	bl FUN_0206F750
	str r0, [r4, #0x0]
	b _0206F722
_0206F60A:
	bl FUN_0206F7D8
	str r0, [r4, #0x0]
	b _0206F722
_0206F612:
	add r1, r4, #0x0
	bl FUN_020718CC
	cmp r0, #0x1
	beq _0206F61E
_0206F61C:
	b _0206F722
_0206F61E:
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _0206F722
_0206F624:
	bl FUN_020754D0
	str r0, [r4, #0x0]
	b _0206F722
_0206F62C:
	bl FUN_0206F874
	str r0, [r4, #0x0]
	b _0206F722
_0206F634:
	ldr r1, _0206F740 ; =0x00000B14
	ldr r1, [r5, r1]
	blx r1
	str r0, [r4, #0x0]
	b _0206F722
_0206F63E:
	bl FUN_02077110
	str r0, [r4, #0x0]
	b _0206F722
_0206F646:
	bl FUN_020761A0
	str r0, [r4, #0x0]
	b _0206F722
_0206F64E:
	bl FUN_0206F8B4
	str r0, [r4, #0x0]
	b _0206F722
_0206F656:
	bl FUN_02072170
	str r0, [r4, #0x0]
	b _0206F722
_0206F65E:
	bl FUN_02072194
	str r0, [r4, #0x0]
	b _0206F722
_0206F666:
	bl FUN_02072140
	str r0, [r4, #0x0]
	b _0206F722
_0206F66E:
	bl FUN_0207230C
	str r0, [r4, #0x0]
	b _0206F722
_0206F676:
	bl FUN_0206F8F4
	str r0, [r4, #0x0]
	b _0206F722
_0206F67E:
	bl FUN_02071F58
	str r0, [r4, #0x0]
	b _0206F722
_0206F686:
	bl FUN_0207405C
	str r0, [r4, #0x0]
	b _0206F722
_0206F68E:
	bl FUN_0207436C
	str r0, [r4, #0x0]
	b _0206F722
_0206F696:
	bl FUN_0206FA14
	str r0, [r4, #0x0]
	b _0206F722
_0206F69E:
	bl FUN_02076D3C
	str r0, [r4, #0x0]
	b _0206F722
_0206F6A6:
	bl FUN_02074F6C
	str r0, [r4, #0x0]
	b _0206F722
_0206F6AE:
	bl FUN_0206F980
	str r0, [r4, #0x0]
	b _0206F722
_0206F6B6:
	bl FUN_0206F9A4
	str r0, [r4, #0x0]
	b _0206F722
_0206F6BE:
	bl FUN_0206F9C8
	str r0, [r4, #0x0]
	b _0206F722
_0206F6C6:
	bl FUN_0206F9D4
	str r0, [r4, #0x0]
	b _0206F722
_0206F6CE:
	bl FUN_020714D0
	cmp r0, #0x0
	bne _0206F6DC
	mov r0, #0x19
	str r0, [r4, #0x0]
	b _0206F722
_0206F6DC:
	cmp r0, #0x3
	bne _0206F722
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _0206F722
_0206F6E6:
	bl FUN_020746D4
	cmp r0, #0x1
	bne _0206F722
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _0206F722
_0206F6F4:
	bl FUN_02071970
	str r0, [r4, #0x0]
	b _0206F722
_0206F6FC:
	mov r0, #0x1
	mov r1, #0xc
	bl FUN_02079A70
	mov r0, #0x1c
	str r0, [r4, #0x0]
	b _0206F722
_0206F70A:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0206F722
	ldr r0, _0206F744 ; =0x00000B25
	ldrb r1, [r5, r0]
	ldr r0, _0206F748 ; =0x000005A4
	ldr r0, [r5, r0]
	add r0, #0x22
	strb r1, [r0, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0206F722:
	add r0, r5, #0x0
	bl FUN_02073BEC
	add r0, r5, #0x0
	bl FUN_02073D6C
	add r0, r5, #0x0
	bl FUN_02070F14
	ldr r0, _0206F74C ; =0x000005AC
	ldr r0, [r5, r0]
	bl FUN_0200BC1C
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0206F740: .word 0x00000B14
_0206F744: .word 0x00000B25
_0206F748: .word 0x000005A4
_0206F74C: .word 0x000005AC

	thumb_func_start FUN_0206F750
FUN_0206F750: ; 0x0206F750
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0206F7CA
	ldr r0, _0206F7D0 ; =0x000005A4
	ldr r2, [r4, r0]
	add r0, r2, #0x0
	add r0, #0x20
	ldrb r1, [r0, #0x0]
	cmp r1, #0x5
	beq _0206F76E
	cmp r1, #0x10
	bne _0206F786
_0206F76E:
	ldrh r0, [r2, #0x24]
	bl FUN_02076144
	cmp r0, #0x1
	bne _0206F782
	ldr r0, _0206F7D4 ; =0x00000B22
	mov r1, #0x0
	strb r1, [r4, r0]
	mov r0, #0x7
	pop {r4, pc}
_0206F782:
	mov r0, #0x4
	pop {r4, pc}
_0206F786:
	cmp r1, #0x6
	bne _0206F78E
	mov r0, #0x11
	pop {r4, pc}
_0206F78E:
	cmp r1, #0x7
	bne _0206F79A
	add r0, r4, #0x0
	bl FUN_02076C94
	pop {r4, pc}
_0206F79A:
	cmp r1, #0x8
	bne _0206F7A6
	add r0, r4, #0x0
	bl FUN_02076890
	pop {r4, pc}
_0206F7A6:
	add r0, r1, #0x0
	add r0, #0xf5
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	bhi _0206F7B6
	mov r0, #0xc
	pop {r4, pc}
_0206F7B6:
	cmp r1, #0x9
	bne _0206F7BE
	mov r0, #0x8
	pop {r4, pc}
_0206F7BE:
	cmp r1, #0xa
	bne _0206F7C6
	mov r0, #0xe
	pop {r4, pc}
_0206F7C6:
	mov r0, #0x1
	pop {r4, pc}
_0206F7CA:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0206F7D0: .word 0x000005A4
_0206F7D4: .word 0x00000B22

	thumb_func_start FUN_0206F7D8
FUN_0206F7D8: ; 0x0206F7D8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02070F94
	cmp r0, #0x0
	bne _0206F81E
	ldr r0, _0206F870 ; =0x000005A4
	ldr r1, [r4, r0]
	add r0, r1, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	beq _0206F7F6
	cmp r0, #0x14
	bne _0206F800
_0206F7F6:
	mov r0, #0x0
	add r1, #0x23
	strb r0, [r1, #0x0]
	mov r0, #0x1b
	pop {r4, pc}
_0206F800:
	cmp r0, #0xe
	bne _0206F80E
	add r0, r4, #0x0
	bl FUN_02077248
	mov r0, #0x14
	pop {r4, pc}
_0206F80E:
	cmp r0, #0x13
	bne _0206F81A
	add r0, r4, #0x0
	bl FUN_02072420
	pop {r4, pc}
_0206F81A:
	mov r0, #0x2
	pop {r4, pc}
_0206F81E:
	cmp r0, #0x4
	bne _0206F82A
	add r0, r4, #0x0
	bl FUN_0207155C
	pop {r4, pc}
_0206F82A:
	cmp r0, #0x3
	bne _0206F83C
	ldr r0, _0206F870 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	pop {r4, pc}
_0206F83C:
	cmp r0, #0x2
	bne _0206F86A
	ldr r0, _0206F870 ; =0x000005A4
	ldr r2, [r4, r0]
	add r1, r2, #0x0
	add r1, #0x20
	ldrb r1, [r1, #0x0]
	cmp r1, #0xf
	beq _0206F858
	mov r0, #0x1
	add r2, #0x23
	strb r0, [r2, #0x0]
	mov r0, #0x1b
	pop {r4, pc}
_0206F858:
	add r0, #0x24
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_0200C664
	add r0, r4, #0x0
	bl FUN_02075118
	pop {r4, pc}
_0206F86A:
	mov r0, #0x1
	pop {r4, pc}
	nop
_0206F870: .word 0x000005A4

	thumb_func_start FUN_0206F874
FUN_0206F874: ; 0x0206F874
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02071D48
	cmp r0, #0x0
	beq _0206F884
	cmp r0, #0x2
	bne _0206F896
_0206F884:
	ldr r0, _0206F8AC ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C664
	add r0, r4, #0x0
	bl FUN_02071DF4
	pop {r4, pc}
_0206F896:
	cmp r0, #0x3
	bne _0206F8A8
	ldr r0, _0206F8B0 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	pop {r4, pc}
_0206F8A8:
	mov r0, #0x4
	pop {r4, pc}
	.balign 4
_0206F8AC: .word 0x000005C8
_0206F8B0: .word 0x000005A4

	thumb_func_start FUN_0206F8B4
FUN_0206F8B4: ; 0x0206F8B4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02071D48
	cmp r0, #0x0
	beq _0206F8C4
	cmp r0, #0x2
	bne _0206F8D6
_0206F8C4:
	ldr r0, _0206F8EC ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C664
	add r0, r4, #0x0
	bl FUN_02071F58
	pop {r4, pc}
_0206F8D6:
	cmp r0, #0x3
	bne _0206F8E8
	ldr r0, _0206F8F0 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	pop {r4, pc}
_0206F8E8:
	mov r0, #0x8
	pop {r4, pc}
	.balign 4
_0206F8EC: .word 0x000005C8
_0206F8F0: .word 0x000005A4

	thumb_func_start FUN_0206F8F4
FUN_0206F8F4: ; 0x0206F8F4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldr r0, _0206F974 ; =0x000006FC
	ldr r0, [r4, r0]
	bl FUN_02001C78
	add r2, r0, #0x0
	mov r0, #0x1
	mvn r0, r0
	cmp r2, r0
	beq _0206F914
	add r0, r0, #0x1
	cmp r2, r0
	beq _0206F96E
	b _0206F962
_0206F914:
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200CCF8
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	ldr r0, _0206F974 ; =0x000006FC
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_02001C5C
	ldr r0, _0206F978 ; =0x000006F8
	ldr r0, [r4, r0]
	bl FUN_02012870
	add r0, r4, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _0206F97C ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C664
	add sp, #0x4
	mov r0, #0x1
	pop {r3-r4, pc}
_0206F962:
	add r0, r4, #0x0
	add r1, sp, #0x0
	blx r2
	ldr r0, [sp, #0x0]
	add sp, #0x4
	pop {r3-r4, pc}
_0206F96E:
	mov r0, #0xd
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0206F974: .word 0x000006FC
_0206F978: .word 0x000006F8
_0206F97C: .word 0x000005C8

	thumb_func_start FUN_0206F980
FUN_0206F980: ; 0x0206F980
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0206F99C ; =0x00000B24
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _0206F996
	ldr r0, _0206F9A0 ; =0x00000B22
	ldrb r0, [r4, r0]
	pop {r4, pc}
_0206F996:
	mov r0, #0x14
	pop {r4, pc}
	nop
_0206F99C: .word 0x00000B24
_0206F9A0: .word 0x00000B22

	thumb_func_start FUN_0206F9A4
FUN_0206F9A4: ; 0x0206F9A4
	push {r3, lr}
	ldr r0, _0206F9C0 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0206F9BA
	ldr r0, _0206F9C4 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x1b
	pop {r3, pc}
_0206F9BA:
	mov r0, #0x15
	pop {r3, pc}
	nop
_0206F9C0: .word gUnknown21C48B8
_0206F9C4: .word 0x000005DC

	thumb_func_start FUN_0206F9C8
FUN_0206F9C8: ; 0x0206F9C8
	push {r3, lr}
	bl FUN_020732CC
	mov r0, #0x17
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0206F9D4
FUN_0206F9D4: ; 0x0206F9D4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0206FA08 ; =0x000006FC
	mov r1, #0xc
	ldr r0, [r4, r0]
	bl FUN_020021AC
	cmp r0, #0x0
	beq _0206F9F0
	mov r1, #0x1
	mvn r1, r1
	cmp r0, r1
	beq _0206F9FA
	b _0206FA04
_0206F9F0:
	ldr r1, _0206FA0C ; =0x00000B18
	add r0, r4, #0x0
	ldr r1, [r4, r1]
	blx r1
	pop {r4, pc}
_0206F9FA:
	ldr r1, _0206FA10 ; =0x00000B1C
	add r0, r4, #0x0
	ldr r1, [r4, r1]
	blx r1
	pop {r4, pc}
_0206FA04:
	mov r0, #0x17
	pop {r4, pc}
	.balign 4
_0206FA08: .word 0x000006FC
_0206FA0C: .word 0x00000B18
_0206FA10: .word 0x00000B1C

	thumb_func_start FUN_0206FA14
FUN_0206FA14: ; 0x0206FA14
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02071D48
	cmp r0, #0x0
	beq _0206FA24
	cmp r0, #0x2
	bne _0206FA78
_0206FA24:
	ldr r0, _0206FA90 ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C664
	ldr r0, _0206FA94 ; =0x00000B25
	mov r1, #0x2c
	ldrb r0, [r4, r0]
	add r2, r0, #0x0
	mul r2, r1
	mov r0, #0x71
	add r2, r4, r2
	lsl r0, r0, #0x4
	ldrb r0, [r2, r0]
	cmp r0, #0x1
	beq _0206FA4C
	add r0, r4, #0x0
	bl FUN_02076AF8
	pop {r4, pc}
_0206FA4C:
	add r0, r4, #0x0
	sub r1, #0x2d
	mov r2, #0x1
	bl FUN_020731E8
	ldr r1, _0206FA98 ; =0x000005A4
	mov r2, #0x0
	ldr r0, [r4, r1]
	add r1, #0xf8
	add r0, #0x23
	strb r2, [r0, #0x0]
	ldr r0, _0206FA9C ; =0x00000B22
	mov r2, #0x15
	strb r2, [r4, r0]
	ldr r2, _0206FAA0 ; =0x000006A4
	ldr r0, [r4, r1]
	ldr r2, [r4, r2]
	mov r1, #0x69
	bl ReadMsgDataIntoString
	mov r0, #0x14
	pop {r4, pc}
_0206FA78:
	cmp r0, #0x3
	bne _0206FA8A
	ldr r0, _0206FA98 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	pop {r4, pc}
_0206FA8A:
	mov r0, #0x11
	pop {r4, pc}
	nop
_0206FA90: .word 0x000005C8
_0206FA94: .word 0x00000B25
_0206FA98: .word 0x000005A4
_0206FA9C: .word 0x00000B22
_0206FAA0: .word 0x000006A4

	thumb_func_start FUN_0206FAA4
FUN_0206FAA4: ; 0x0206FAA4
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	bl FUN_02006278
	add r6, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	add r0, r6, #0x0
	bl FUN_02073A2C
	add r0, r6, #0x0
	bl FUN_020726F0
	ldr r0, [r6, #0x0]
	bl FUN_0206FCD4
	bl FUN_0201CD04
	bl FUN_0201C29C
	mov r7, #0x7
	mov r4, #0x0
	add r5, r6, #0x0
	lsl r7, r7, #0x8
_0206FAD8:
	ldr r0, [r5, r7]
	bl String_dtor
	add r4, r4, #0x1
	add r5, #0x2c
	cmp r4, #0x6
	blo _0206FAD8
	ldr r0, _0206FB40 ; =0x000006A4
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r0, _0206FB44 ; =0x000006A8
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r7, _0206FB48 ; =0x000006AC
	mov r5, #0x0
	add r4, r6, #0x0
_0206FAFC:
	ldr r0, [r4, r7]
	bl String_dtor
	add r5, r5, #0x1
	add r4, r4, #0x4
	cmp r5, #0x13
	blo _0206FAFC
	ldr r0, _0206FB4C ; =0x0000069C
	ldr r0, [r6, r0]
	bl DestroyMsgData
	ldr r0, _0206FB50 ; =0x00000698
	ldr r0, [r6, r0]
	bl FUN_0200B990
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r6, r0]
	bl FUN_0200AB18
	ldr r0, _0206FB54 ; =0x00000B34
	ldr r0, [r6, r0]
	cmp r0, #0x0
	beq _0206FB30
	bl FUN_0206BB74
_0206FB30:
	ldr r0, [sp, #0x0]
	bl FUN_0200627C
	mov r0, #0xc
	bl FUN_020168D0
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0206FB40: .word 0x000006A4
_0206FB44: .word 0x000006A8
_0206FB48: .word 0x000006AC
_0206FB4C: .word 0x0000069C
_0206FB50: .word 0x00000698
_0206FB54: .word 0x00000B34

	thumb_func_start FUN_0206FB58
FUN_0206FB58: ; 0x0206FB58
	push {r3, lr}
	ldr r0, [r0, #0x0]
	bl FUN_0201AB60
	bl FUN_0201C30C
	bl FUN_0200BC30
	ldr r3, _0206FB78 ; =0x027E0000
	ldr r1, _0206FB7C ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, pc}
	nop
_0206FB78: .word 0x027E0000
_0206FB7C: .word 0x00003FF8

	thumb_func_start FUN_0206FB80
FUN_0206FB80: ; 0x0206FB80
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _0206FB9C ; =UNK_020F9564
	add r3, sp, #0x0
	mov r2, #0x5
_0206FB8A:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0206FB8A
	add r0, sp, #0x0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.balign 4
_0206FB9C: .word UNK_020F9564

	thumb_func_start FUN_0206FBA0
FUN_0206FBA0: ; 0x0206FBA0
	push {r3-r5, lr}
	sub sp, #0xb8
	ldr r5, _0206FCB8 ; =UNK_020F9458
	add r3, sp, #0xa8
	add r4, r0, #0x0
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	bl FUN_02016BBC
	ldr r5, _0206FCBC ; =UNK_020F94D4
	add r3, sp, #0x8c
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	add r3, r1, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02018744
	ldr r5, _0206FCC0 ; =UNK_020F94F0
	add r3, sp, #0x70
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02018744
	ldr r5, _0206FCC4 ; =UNK_020F949C
	add r3, sp, #0x54
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02018744
	ldr r5, _0206FCC8 ; =UNK_020F9480
	add r3, sp, #0x38
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x3
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02016C18
	ldr r5, _0206FCCC ; =UNK_020F950C
	add r3, sp, #0x1c
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r1, #0x4
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_02018744
	ldr r5, _0206FCD0 ; =UNK_020F9528
	add r3, sp, #0x0
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x5
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02016C18
	mov r0, #0x0
	mov r1, #0x20
	add r2, r0, #0x0
	mov r3, #0xc
	bl FUN_02017F18
	mov r0, #0x4
	mov r1, #0x20
	mov r2, #0x0
	mov r3, #0xc
	bl FUN_02017F18
	add sp, #0xb8
	pop {r3-r5, pc}
	nop
_0206FCB8: .word UNK_020F9458
_0206FCBC: .word UNK_020F94D4
_0206FCC0: .word UNK_020F94F0
_0206FCC4: .word UNK_020F949C
_0206FCC8: .word UNK_020F9480
_0206FCCC: .word UNK_020F950C
_0206FCD0: .word UNK_020F9528

	thumb_func_start FUN_0206FCD4
FUN_0206FCD4: ; 0x0206FCD4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1f
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x13
	mov r1, #0x0
	bl FUN_0201E74C
	add r0, r4, #0x0
	mov r1, #0x5
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020178A0
	mov r0, #0xc
	add r1, r4, #0x0
	bl FUN_02016A8C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0206FD24
FUN_0206FD24: ; 0x0206FD24
	push {r4-r5, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x0]
	mov r0, #0x14
	mov r1, #0xf
	mov r3, #0x3
	bl FUN_0200687C
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x0]
	mov r0, #0x14
	mov r1, #0x11
	mov r3, #0x3
	bl FUN_020068C8
	mov r0, #0x14
	mov r1, #0x10
	mov r2, #0xc
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x10
	add r4, r0, #0x0
	bl FUN_020B0138
	ldr r2, [sp, #0x10]
	mov r0, #0x3
	ldr r1, [r2, #0xc]
	ldr r2, [r2, #0x8]
	mov r3, #0x0
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	bl FUN_02017FB4
	ldr r1, [sp, #0x10]
	ldr r0, _0206FE6C ; =0x000004A4
	ldr r1, [r1, #0xc]
	mov r2, #0x1
	add r0, r5, r0
	add r1, #0x60
	lsl r2, r2, #0x8
	bl memcpy
	mov r0, #0xc
	add r1, r4, #0x0
	bl FUN_02016A8C
	mov r1, #0x1a
	mov r0, #0x0
	lsl r1, r1, #0x4
	mov r2, #0xc
	bl FUN_02002EEC
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r0, #0xc
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	mov r2, #0x1
	mov r3, #0xe
	bl FUN_0200CB00
	ldr r0, _0206FE70 ; =0x000005A4
	ldr r0, [r5, r0]
	ldr r0, [r0, #0xc]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0xc
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	mov r2, #0xa
	mov r3, #0xf
	bl FUN_0200CD68
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x0]
	mov r0, #0x14
	mov r1, #0x3
	mov r3, #0x4
	bl FUN_0200687C
	mov r3, #0x20
	mov r1, #0x4
	str r3, [sp, #0x0]
	mov r0, #0xc
	str r0, [sp, #0x4]
	mov r0, #0x14
	add r2, r1, #0x0
	bl FUN_02006930
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r1, #0xc
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x0]
	mov r0, #0x14
	mov r3, #0x5
	bl FUN_0200687C
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x0]
	mov r0, #0x14
	mov r1, #0xe
	mov r3, #0x5
	bl FUN_020068C8
	mov r0, #0x20
	str r0, [sp, #0x0]
	mov r0, #0xc
	str r0, [sp, #0x4]
	mov r0, #0x14
	mov r1, #0xd
	mov r2, #0x4
	mov r3, #0x0
	bl FUN_02006930
	mov r2, #0x99
	lsl r2, r2, #0x2
	mov r3, #0xf9
	add r1, r5, r2
	add r2, #0xc0
	lsl r3, r3, #0x2
	mov r0, #0xc
	add r2, r5, r2
	add r3, r5, r3
	bl FUN_020724D4
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02017FE4
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_02017FE4
	add sp, #0x14
	pop {r4-r5, pc}
	.balign 4
_0206FE6C: .word 0x000004A4
_0206FE70: .word 0x000005A4

	thumb_func_start FUN_0206FE74
FUN_0206FE74: ; 0x0206FE74
	push {r3-r7, lr}
	ldr r1, _0206FF50 ; =0x00000B38
	mov r2, #0xc
	add r4, r0, #0x0
	bl FUN_02006268
	ldr r2, _0206FF50 ; =0x00000B38
	mov r1, #0x0
	add r6, r0, #0x0
	bl memset
	add r0, r4, #0x0
	bl FUN_0200628C
	ldr r1, _0206FF54 ; =0x000005A4
	str r0, [r6, r1]
	mov r0, #0xc
	bl FUN_02016B94
	str r0, [r6, #0x0]
	ldr r0, _0206FF54 ; =0x000005A4
	ldr r1, [r6, r0]
	add r0, r1, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0206FEBC
	ldr r0, [r1, #0x14]
	cmp r0, #0x0
	beq _0206FEBC
	mov r0, #0xc
	bl FUN_0206BB5C
	ldr r1, _0206FF58 ; =0x00000B34
	str r0, [r6, r1]
	b _0206FEC2
_0206FEBC:
	ldr r0, _0206FF58 ; =0x00000B34
	mov r1, #0x0
	str r1, [r6, r0]
_0206FEC2:
	ldr r2, _0206FF5C ; =0x00000192
	mov r0, #0x0
	mov r1, #0x1a
	mov r3, #0xc
	bl NewMsgDataFromNarc
	ldr r1, _0206FF60 ; =0x0000069C
	mov r2, #0x0
	str r0, [r6, r1]
	mov r0, #0xf
	mov r1, #0xe
	mov r3, #0xc
	bl FUN_0200B870
	ldr r1, _0206FF64 ; =0x00000698
	str r0, [r6, r1]
	mov r0, #0xc
	bl FUN_0200AA80
	mov r1, #0x6a
	lsl r1, r1, #0x4
	add r7, r1, #0x0
	str r0, [r6, r1]
	mov r4, #0x0
	add r5, r6, #0x0
	add r7, #0x60
_0206FEF6:
	mov r0, #0xb
	mov r1, #0xc
	bl String_ctor
	str r0, [r5, r7]
	add r4, r4, #0x1
	add r5, #0x2c
	cmp r4, #0x6
	blo _0206FEF6
	mov r0, #0x1
	lsl r0, r0, #0x8
	mov r1, #0xc
	bl String_ctor
	ldr r1, _0206FF68 ; =0x000006A4
	str r0, [r6, r1]
	mov r0, #0x1
	lsl r0, r0, #0x8
	mov r1, #0xc
	bl String_ctor
	ldr r1, _0206FF6C ; =0x000006A8
	mov r5, #0x0
	str r0, [r6, r1]
	add r4, r6, #0x0
	add r7, r1, #0x4
_0206FF2A:
	mov r0, #0x20
	mov r1, #0xc
	bl String_ctor
	str r0, [r4, r7]
	add r5, r5, #0x1
	add r4, r4, #0x4
	cmp r5, #0x13
	blo _0206FF2A
	ldr r0, _0206FF54 ; =0x000005A4
	ldr r0, [r6, r0]
	add r0, #0x22
	ldrb r1, [r0, #0x0]
	ldr r0, _0206FF70 ; =0x00000B25
	strb r1, [r6, r0]
	add r0, r0, #0x1
	strb r1, [r6, r0]
	add r0, r6, #0x0
	pop {r3-r7, pc}
	.balign 4
_0206FF50: .word 0x00000B38
_0206FF54: .word 0x000005A4
_0206FF58: .word 0x00000B34
_0206FF5C: .word 0x00000192
_0206FF60: .word 0x0000069C
_0206FF64: .word 0x00000698
_0206FF68: .word 0x000006A4
_0206FF6C: .word 0x000006A8
_0206FF70: .word 0x00000B25

	thumb_func_start FUN_0206FF74
FUN_0206FF74: ; 0x0206FF74
	push {r3-r4}
	ldr r2, _0206FFAC ; =0x000005A4
	mov r3, #0x80
	ldr r1, [r0, r2]
	add r1, #0x20
	ldrb r1, [r1, #0x0]
	tst r1, r3
	beq _0206FF9E
	ldr r1, _0206FFB0 ; =0x00000B23
	ldrb r4, [r0, r1]
	orr r4, r3
	strb r4, [r0, r1]
	ldr r1, [r0, r2]
	add r0, r1, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	add r1, #0x20
	eor r0, r3
	strb r0, [r1, #0x0]
	pop {r3-r4}
	bx lr
_0206FF9E:
	ldr r2, _0206FFB0 ; =0x00000B23
	mov r1, #0x80
	ldrb r3, [r0, r2]
	bic r3, r1
	strb r3, [r0, r2]
	pop {r3-r4}
	bx lr
	.balign 4
_0206FFAC: .word 0x000005A4
_0206FFB0: .word 0x00000B23

	thumb_func_start FUN_0206FFB4
FUN_0206FFB4: ; 0x0206FFB4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02070064 ; =0x000005A4
	mov r4, #0x3
	ldr r1, [r5, r0]
	add r0, r1, #0x0
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0206FFD0
	ldr r1, _02070068 ; =UNK_020F95CC
	ldr r0, _0207006C ; =0x00000808
	str r1, [r5, r0]
	b _0206FFEA
_0206FFD0:
	add r1, #0x20
	ldrb r0, [r1, #0x0]
	cmp r0, #0x2
	beq _0206FFDC
	cmp r0, #0x11
	bne _0206FFE4
_0206FFDC:
	ldr r1, _02070070 ; =UNK_020F960C
	ldr r0, _0207006C ; =0x00000808
	str r1, [r5, r0]
	b _0206FFEA
_0206FFE4:
	ldr r1, _02070074 ; =UNK_020F958C
	ldr r0, _0207006C ; =0x00000808
	str r1, [r5, r0]
_0206FFEA:
	ldr r0, _02070064 ; =0x000005A4
	ldr r1, [r5, r0]
	add r1, #0x20
	ldrb r1, [r1, #0x0]
	cmp r1, #0x2
	beq _0207003C
	cmp r1, #0x11
	beq _0207003C
	add r0, #0x2c
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
	ldr r0, _02070078 ; =0x000005D4
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldr r0, _02070078 ; =0x000005D4
	add r1, sp, #0x0
	ldr r0, [r5, r0]
	add r1, #0x2
	add r2, sp, #0x0
	bl FUN_0200C75C
	ldr r0, _02070078 ; =0x000005D4
	add r3, sp, #0x0
	mov r2, #0x0
	ldrsh r2, [r3, r2]
	mov r1, #0x2
	ldrsh r1, [r3, r1]
	sub r2, #0x8
	lsl r2, r2, #0x10
	ldr r0, [r5, r0]
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	mov r0, #0x1
	eor r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_0207003C:
	ldr r0, _02070064 ; =0x000005A4
	ldr r1, [r5, r0]
	add r1, #0x20
	ldrb r1, [r1, #0x0]
	cmp r1, #0x4
	bne _0207005A
	add r0, #0x30
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
	mov r0, #0x2
	eor r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_0207005A:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073094
	pop {r3-r5, pc}
	.balign 4
_02070064: .word 0x000005A4
_02070068: .word UNK_020F95CC
_0207006C: .word 0x00000808
_02070070: .word UNK_020F960C
_02070074: .word UNK_020F958C
_02070078: .word 0x000005D4

	thumb_func_start FUN_0207007C
FUN_0207007C: ; 0x0207007C
	mov r2, #0x2c
	mul r2, r1
	add r1, r0, r2
	ldr r0, _02070088 ; =0x00000729
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02070088: .word 0x00000729

	thumb_func_start FUN_0207008C
FUN_0207008C: ; 0x0207008C
	push {r4-r7, lr}
	sub sp, #0xc
	str r1, [sp, #0x0]
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r1, #0x2c
	add r4, r0, #0x0
	ldr r0, _020701D8 ; =0x00000729
	mul r4, r1
	add r0, r5, r0
	mov r1, #0x0
	str r0, [sp, #0x8]
	strb r1, [r0, r4]
	ldr r0, _020701DC ; =0x000005A4
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x0]
	bl GetPartyCount
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bgt _020700BC
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_020700BC:
	ldr r0, _020701DC ; =0x000005A4
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0x5
	mov r2, #0x0
	add r7, r0, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	bne _020700DE
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_020700DE:
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02072A00
	ldr r0, [sp, #0x0]
	mov r1, #0x2c
	add r6, r0, #0x0
	mul r6, r1
	ldr r1, _020701E0 ; =0x00000704
	ldr r0, [sp, #0x4]
	add r2, r5, r6
	strh r0, [r2, r1]
	add r0, r7, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	ldr r1, _020701E4 ; =0x00000706
	add r2, r5, r6
	strh r0, [r2, r1]
	add r0, r7, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl GetMonData
	ldr r1, _020701E8 ; =0x00000708
	add r2, r5, r6
	strh r0, [r2, r1]
	add r0, r7, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	ldr r1, _020701EC ; =0x0000070A
	add r2, r5, r6
	strh r0, [r2, r1]
	add r0, r7, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl GetMonData
	ldr r1, _020701F0 ; =0x0000070C
	add r2, r5, r6
	strh r0, [r2, r1]
	add r0, r7, #0x0
	mov r1, #0xa1
	mov r2, #0x0
	bl GetMonData
	ldr r1, _020701F4 ; =0x00000712
	add r2, r5, r6
	strh r0, [r2, r1]
	add r0, r7, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonData
	mov r1, #0x71
	add r2, r5, r6
	lsl r1, r1, #0x4
	strb r0, [r2, r1]
	add r0, r7, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl GetMonData
	ldr r1, _020701F8 ; =0x00000711
	add r2, r5, r6
	strb r0, [r2, r1]
	add r0, r7, #0x0
	mov r1, #0xaf
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x1
	ldr r0, _020701FC ; =0x0000070E
	bne _02070184
	add r2, r5, r0
	ldrh r1, [r2, r4]
	ldr r0, _02070200 ; =0xFFFFEFFF
	and r0, r1
	b _0207018E
_02070184:
	add r2, r5, r0
	ldrh r1, [r2, r4]
	mov r0, #0x1
	lsl r0, r0, #0xc
	orr r0, r1
_0207018E:
	strh r0, [r2, r4]
	ldr r0, _020701FC ; =0x0000070E
	add r6, r5, r0
	add r0, r7, #0x0
	bl GetMonGender
	lsl r0, r0, #0x1e
	ldrh r2, [r6, r4]
	ldr r1, _02070204 ; =0xFFFF9FFF
	lsr r0, r0, #0x11
	and r1, r2
	orr r0, r1
	strh r0, [r6, r4]
	ldr r0, [sp, #0x8]
	mov r1, #0x1
	strb r1, [r0, r4]
	add r0, r7, #0x0
	bl FUN_0207C2D4
	lsl r0, r0, #0x18
	ldrh r1, [r6, r4]
	ldr r2, _02070208 ; =0xFFFFF000
	lsr r0, r0, #0x18
	and r1, r2
	lsr r2, r2, #0x14
	and r0, r2
	orr r0, r1
	strh r0, [r6, r4]
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_0207020C
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_020701D8: .word 0x00000729
_020701DC: .word 0x000005A4
_020701E0: .word 0x00000704
_020701E4: .word 0x00000706
_020701E8: .word 0x00000708
_020701EC: .word 0x0000070A
_020701F0: .word 0x0000070C
_020701F4: .word 0x00000712
_020701F8: .word 0x00000711
_020701FC: .word 0x0000070E
_02070200: .word 0xFFFFEFFF
_02070204: .word 0xFFFF9FFF
_02070208: .word 0xFFFFF000

	thumb_func_start FUN_0207020C
FUN_0207020C: ; 0x0207020C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _0207029C ; =0x000005A4
	add r5, r1, #0x0
	ldr r1, [r7, r0]
	add r0, r1, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0xd
	bne _0207029A
	mov r0, #0x2c
	add r6, r2, #0x0
	mul r6, r0
	mov r0, #0x71
	add r3, r7, r6
	lsl r0, r0, #0x4
	ldrb r2, [r3, r0]
	cmp r2, #0x1
	beq _0207023A
	sub r0, #0xa
	ldrh r0, [r3, r0]
	cmp r0, #0x0
	bne _02070248
_0207023A:
	ldr r0, _020702A0 ; =0x0000070E
	add r2, r7, r0
	ldrh r1, [r2, r6]
	ldr r0, _020702A4 ; =0xFFFF7FFF
	and r0, r1
	strh r0, [r2, r6]
	pop {r3-r7, pc}
_02070248:
	add r1, #0x2a
	ldrb r1, [r1, #0x0]
	add r0, r5, #0x0
	bl FUN_020702A8
	str r0, [sp, #0x0]
	mov r4, #0x0
_02070256:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _0207026C
	add r4, r4, #0x1
	cmp r4, #0x4
	blo _02070256
_0207026C:
	ldr r0, _0207029C ; =0x000005A4
	ldr r0, [r7, r0]
	add r0, #0x2b
	ldrb r1, [r0, #0x0]
	ldr r0, [sp, #0x0]
	cmp r1, r0
	bhi _0207028E
	cmp r4, #0x2
	blo _0207028E
	ldr r0, _020702A0 ; =0x0000070E
	add r2, r7, r0
	ldrh r1, [r2, r6]
	mov r0, #0x2
	lsl r0, r0, #0xe
	orr r0, r1
	strh r0, [r2, r6]
	pop {r3-r7, pc}
_0207028E:
	ldr r0, _020702A0 ; =0x0000070E
	add r2, r7, r0
	ldrh r1, [r2, r6]
	ldr r0, _020702A4 ; =0xFFFF7FFF
	and r0, r1
	strh r0, [r2, r6]
_0207029A:
	pop {r3-r7, pc}
	.balign 4
_0207029C: .word 0x000005A4
_020702A0: .word 0x0000070E
_020702A4: .word 0xFFFF7FFF

	thumb_func_start FUN_020702A8
FUN_020702A8: ; 0x020702A8
	push {r3-r5, lr}
	add r5, r0, #0x0
	cmp r1, #0x4
	bls _020702B2
	b _020703B6
_020702B2:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020702BE: ; jump table (using 16-bit offset)
	.short _020702C8 - _020702BE - 2; case 0
	.short _020702F8 - _020702BE - 2; case 1
	.short _02070328 - _020702BE - 2; case 2
	.short _02070358 - _020702BE - 2; case 3
	.short _02070388 - _020702BE - 2; case 4
_020702C8:
	mov r1, #0x7a
	mov r2, #0x0
	bl GetMonData
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x7b
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	add r0, r5, #0x0
	mov r1, #0x7c
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	add r0, r5, #0x0
	mov r1, #0x7d
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	b _020703B6
_020702F8:
	mov r1, #0x7e
	mov r2, #0x0
	bl GetMonData
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x7f
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	add r0, r5, #0x0
	mov r1, #0x80
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	add r0, r5, #0x0
	mov r1, #0x81
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	b _020703B6
_02070328:
	mov r1, #0x82
	mov r2, #0x0
	bl GetMonData
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x83
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	add r0, r5, #0x0
	mov r1, #0x84
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	add r0, r5, #0x0
	mov r1, #0x85
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	b _020703B6
_02070358:
	mov r1, #0x86
	mov r2, #0x0
	bl GetMonData
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x87
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	add r0, r5, #0x0
	mov r1, #0x88
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	add r0, r5, #0x0
	mov r1, #0x89
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	b _020703B6
_02070388:
	mov r1, #0x8a
	mov r2, #0x0
	bl GetMonData
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x8b
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	add r0, r5, #0x0
	mov r1, #0x8c
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
	add r0, r5, #0x0
	mov r1, #0x8d
	mov r2, #0x0
	bl GetMonData
	add r4, r4, r0
_020703B6:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020703BC
FUN_020703BC: ; 0x020703BC
	mov r1, #0x39
	lsl r1, r1, #0x4
	add r0, r0, r1
	bx lr

	thumb_func_start FUN_020703C4
FUN_020703C4: ; 0x020703C4
	push {r4-r7, lr}
	sub sp, #0x1c
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r4, #0x0
	beq _020703E4
	ldr r0, _02070474 ; =0x000005A4
	ldr r0, [r5, r0]
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020703EC
	cmp r4, #0x1
	bne _020703EC
_020703E4:
	mov r0, #0x99
	lsl r0, r0, #0x2
	add r0, r5, r0
	b _020703F2
_020703EC:
	mov r0, #0xc9
	lsl r0, r0, #0x2
	add r0, r5, r0
_020703F2:
	mov r1, #0x2c
	mul r1, r4
	ldr r2, _02070478 ; =0x00000714
	add r1, r5, r1
	strb r6, [r1, r2]
	add r2, r2, #0x1
	strb r7, [r1, r2]
	mov r2, #0x10
	str r2, [sp, #0x0]
	mov r1, #0x6
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r2, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl FUN_02018170
	add r0, sp, #0x20
	ldrb r0, [r0, #0x10]
	cmp r0, #0x0
	bne _0207044C
	add r0, r7, #0x3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x9
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0x10
	add r3, r6, #0x6
	str r0, [sp, #0xc]
	lsl r3, r3, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	mov r2, #0x17
	lsr r3, r3, #0x18
	bl FUN_02018540
_0207044C:
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	add r0, r4, #0x3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl FUN_020186B4
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020709FC
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4
_02070474: .word 0x000005A4
_02070478: .word 0x00000714

	thumb_func_start FUN_0207047C
FUN_0207047C: ; 0x0207047C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020704E4 ; =0x000005A4
	ldr r2, [r4, r0]
	add r0, r2, #0x0
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _02070492
	ldr r1, _020704E8 ; =UNK_020F9694
	b _02070494
_02070492:
	ldr r1, _020704EC ; =UNK_020F964C
_02070494:
	add r2, #0x20
	ldrb r0, [r2, #0x0]
	cmp r0, #0x10
	bne _020704A4
	add r0, r4, #0x0
	bl FUN_02070600
	b _020704D2
_020704A4:
	cmp r0, #0x6
	bne _020704B0
	add r0, r4, #0x0
	bl FUN_020706E0
	b _020704D2
_020704B0:
	cmp r0, #0xd
	bne _020704BC
	add r0, r4, #0x0
	bl FUN_020707C0
	b _020704D2
_020704BC:
	cmp r0, #0x2
	beq _020704C4
	cmp r0, #0x11
	bne _020704CC
_020704C4:
	add r0, r4, #0x0
	bl FUN_020708A0
	b _020704D2
_020704CC:
	add r0, r4, #0x0
	bl FUN_020704F0
_020704D2:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl FUN_0201AC68
	ldr r0, [r4, #0x0]
	mov r1, #0x4
	bl FUN_0201AC68
	pop {r4, pc}
	.balign 4
_020704E4: .word 0x000005A4
_020704E8: .word UNK_020F9694
_020704EC: .word UNK_020F964C

	thumb_func_start FUN_020704F0
FUN_020704F0: ; 0x020704F0
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r4, #0x0
_020704FA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207008C
	cmp r0, #0x1
	bne _020705D4
	mov r0, #0x2c
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x71
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	str r1, [sp, #0x4]
	cmp r0, #0x1
	bne _0207053A
	mov r0, #0xc
	add r2, r4, #0x0
	mul r2, r0
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r3, r6, r2
	ldrh r2, [r6, r2]
	ldrh r3, [r3, #0x2]
	add r0, r5, #0x0
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_020703C4
	b _0207055A
_0207053A:
	mov r0, #0xc
	add r2, r4, #0x0
	mul r2, r0
	mov r0, #0x1
	str r0, [sp, #0x0]
	add r3, r6, r2
	ldrh r2, [r6, r2]
	ldrh r3, [r3, #0x2]
	add r0, r5, #0x0
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_020703C4
_0207055A:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02072D1C
	mov r0, #0xc
	mul r0, r4
	add r7, r6, r0
	ldrh r2, [r7, #0x4]
	ldrh r3, [r7, #0x6]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020737D0
	ldrh r2, [r7, #0x8]
	ldrh r3, [r7, #0xa]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020739E4
	ldr r3, [sp, #0x4]
	ldr r2, _020705F8 ; =0x0000070C
	add r0, r5, #0x0
	ldrh r2, [r3, r2]
	add r1, r4, #0x0
	bl FUN_02073A78
	mov r2, #0x4
	mov r3, #0x6
	ldrsh r2, [r7, r2]
	ldrsh r3, [r7, r3]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073AD8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073B3C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073B0C
	mov r2, #0x2c
	mul r2, r4
	add r3, r5, r2
	ldr r2, _020705FC ; =0x0000070E
	add r0, r5, #0x0
	ldrh r2, [r3, r2]
	add r1, r4, #0x0
	lsl r2, r2, #0x14
	lsr r2, r2, #0x14
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020717E8
	b _020705EA
_020705D4:
	mov r0, #0xc
	add r2, r4, #0x0
	mul r2, r0
	add r7, r6, r2
	mov r3, #0x2
	ldrsh r2, [r6, r2]
	ldrsh r3, [r7, r3]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02070988
_020705EA:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x6
	blo _020704FA
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020705F8: .word 0x0000070C
_020705FC: .word 0x0000070E

	thumb_func_start FUN_02070600
FUN_02070600: ; 0x02070600
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	str r1, [sp, #0x4]
	mov r4, #0x0
_0207060A:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207008C
	cmp r0, #0x1
	bne _020706B0
	mov r0, #0xc
	add r2, r4, #0x0
	mul r2, r0
	ldr r0, [sp, #0x4]
	ldr r3, [sp, #0x4]
	add r6, r0, r2
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldrh r2, [r3, r2]
	ldrh r3, [r6, #0x2]
	add r0, r5, #0x0
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_020703C4
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02072E4C
	ldrh r2, [r6, #0x4]
	ldrh r3, [r6, #0x6]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020737D0
	ldrh r2, [r6, #0x8]
	ldrh r3, [r6, #0xa]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020739E4
	mov r0, #0x2c
	add r7, r4, #0x0
	mul r7, r0
	ldr r2, _020706D8 ; =0x0000070C
	add r3, r5, r7
	ldrh r2, [r3, r2]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073A78
	mov r2, #0x4
	mov r3, #0x6
	ldrsh r2, [r6, r2]
	ldrsh r3, [r6, r3]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073AD8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073B3C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073B0C
	ldr r2, _020706DC ; =0x0000070E
	add r3, r5, r7
	ldrh r2, [r3, r2]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x14
	lsr r2, r2, #0x14
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020717E8
	b _020706CA
_020706B0:
	mov r0, #0xc
	add r2, r4, #0x0
	mul r2, r0
	ldr r0, [sp, #0x4]
	ldr r6, [sp, #0x4]
	add r3, r0, r2
	ldrsh r2, [r6, r2]
	mov r6, #0x2
	ldrsh r3, [r3, r6]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02070988
_020706CA:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x6
	blo _0207060A
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020706D8: .word 0x0000070C
_020706DC: .word 0x0000070E

	thumb_func_start FUN_020706E0
FUN_020706E0: ; 0x020706E0
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	str r1, [sp, #0x4]
	mov r4, #0x0
_020706EA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207008C
	cmp r0, #0x1
	bne _02070790
	mov r0, #0xc
	add r2, r4, #0x0
	mul r2, r0
	ldr r0, [sp, #0x4]
	ldr r3, [sp, #0x4]
	add r6, r0, r2
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldrh r2, [r3, r2]
	ldrh r3, [r6, #0x2]
	add r0, r5, #0x0
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_020703C4
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02072EE4
	ldrh r2, [r6, #0x4]
	ldrh r3, [r6, #0x6]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020737D0
	ldrh r2, [r6, #0x8]
	ldrh r3, [r6, #0xa]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020739E4
	mov r0, #0x2c
	add r7, r4, #0x0
	mul r7, r0
	ldr r2, _020707B8 ; =0x0000070C
	add r3, r5, r7
	ldrh r2, [r3, r2]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073A78
	mov r2, #0x4
	mov r3, #0x6
	ldrsh r2, [r6, r2]
	ldrsh r3, [r6, r3]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073AD8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073B3C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073B0C
	ldr r2, _020707BC ; =0x0000070E
	add r3, r5, r7
	ldrh r2, [r3, r2]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x14
	lsr r2, r2, #0x14
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020717E8
	b _020707AA
_02070790:
	mov r0, #0xc
	add r2, r4, #0x0
	mul r2, r0
	ldr r0, [sp, #0x4]
	ldr r6, [sp, #0x4]
	add r3, r0, r2
	ldrsh r2, [r6, r2]
	mov r6, #0x2
	ldrsh r3, [r3, r6]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02070988
_020707AA:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x6
	blo _020706EA
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020707B8: .word 0x0000070C
_020707BC: .word 0x0000070E

	thumb_func_start FUN_020707C0
FUN_020707C0: ; 0x020707C0
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	str r1, [sp, #0x4]
	mov r4, #0x0
_020707CA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207008C
	cmp r0, #0x1
	bne _02070870
	mov r0, #0xc
	add r2, r4, #0x0
	mul r2, r0
	ldr r0, [sp, #0x4]
	ldr r3, [sp, #0x4]
	add r6, r0, r2
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldrh r2, [r3, r2]
	ldrh r3, [r6, #0x2]
	add r0, r5, #0x0
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_020703C4
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02072F78
	ldrh r2, [r6, #0x4]
	ldrh r3, [r6, #0x6]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020737D0
	ldrh r2, [r6, #0x8]
	ldrh r3, [r6, #0xa]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020739E4
	mov r0, #0x2c
	add r7, r4, #0x0
	mul r7, r0
	ldr r2, _02070898 ; =0x0000070C
	add r3, r5, r7
	ldrh r2, [r3, r2]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073A78
	mov r2, #0x4
	mov r3, #0x6
	ldrsh r2, [r6, r2]
	ldrsh r3, [r6, r3]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073AD8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073B3C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073B0C
	ldr r2, _0207089C ; =0x0000070E
	add r3, r5, r7
	ldrh r2, [r3, r2]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x14
	lsr r2, r2, #0x14
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020717E8
	b _0207088A
_02070870:
	mov r0, #0xc
	add r2, r4, #0x0
	mul r2, r0
	ldr r0, [sp, #0x4]
	ldr r6, [sp, #0x4]
	add r3, r0, r2
	ldrsh r2, [r6, r2]
	mov r6, #0x2
	ldrsh r3, [r3, r6]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02070988
_0207088A:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x6
	blo _020707CA
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02070898: .word 0x0000070C
_0207089C: .word 0x0000070E

	thumb_func_start FUN_020708A0
FUN_020708A0: ; 0x020708A0
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	str r1, [sp, #0x4]
	mov r4, #0x0
_020708AA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207008C
	cmp r0, #0x1
	bne _02070958
	mov r0, #0xc
	add r2, r4, #0x0
	mul r2, r0
	ldr r0, [sp, #0x4]
	ldr r3, [sp, #0x4]
	add r6, r0, r2
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldrh r2, [r3, r2]
	ldrh r3, [r6, #0x2]
	add r0, r5, #0x0
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_020703C4
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02072FDC
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073024
	ldrh r2, [r6, #0x4]
	ldrh r3, [r6, #0x6]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020737D0
	ldrh r2, [r6, #0x8]
	ldrh r3, [r6, #0xa]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020739E4
	mov r0, #0x2c
	add r7, r4, #0x0
	mul r7, r0
	ldr r2, _02070980 ; =0x0000070C
	add r3, r5, r7
	ldrh r2, [r3, r2]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073A78
	mov r2, #0x4
	mov r3, #0x6
	ldrsh r2, [r6, r2]
	ldrsh r3, [r6, r3]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073AD8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073B3C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073B0C
	ldr r2, _02070984 ; =0x0000070E
	add r3, r5, r7
	ldrh r2, [r3, r2]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x14
	lsr r2, r2, #0x14
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020717E8
	b _02070972
_02070958:
	mov r0, #0xc
	add r2, r4, #0x0
	mul r2, r0
	ldr r0, [sp, #0x4]
	ldr r6, [sp, #0x4]
	add r3, r0, r2
	ldrsh r2, [r6, r2]
	mov r6, #0x2
	ldrsh r3, [r3, r6]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02070988
_02070972:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x6
	blo _020708AA
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02070980: .word 0x0000070C
_02070984: .word 0x0000070E

	thumb_func_start FUN_02070988
FUN_02070988: ; 0x02070988
	push {r4-r7, lr}
	sub sp, #0x1c
	add r7, r1, #0x0
	add r4, r2, #0x0
	mov r1, #0x10
	mov r2, #0xf9
	add r5, r0, #0x0
	lsl r2, r2, #0x2
	add r6, r3, #0x0
	lsl r3, r6, #0x18
	str r1, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	add r2, r5, r2
	str r2, [sp, #0x8]
	mov r2, #0x0
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	lsl r2, r4, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02018170
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	lsl r2, r4, #0x18
	lsl r3, r6, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_020186B4
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x7
	bl FUN_02073A4C
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x0
	bl FUN_02073A78
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02073B3C
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_020709FC
FUN_020709FC: ; 0x020709FC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _02070A78 ; =0x000005A4
	add r6, r1, #0x0
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	ldr r1, _02070A7C ; =0x00000B23
	ldrb r2, [r5, r1]
	lsl r3, r2, #0x19
	lsr r3, r3, #0x1f
	cmp r3, #0x1
	bne _02070A2C
	add r1, r1, #0x2
	ldrb r1, [r5, r1]
	cmp r6, r1
	beq _02070A28
	lsl r1, r2, #0x1a
	lsr r1, r1, #0x1a
	cmp r6, r1
	bne _02070A2C
_02070A28:
	mov r4, #0x7
	b _02070A60
_02070A2C:
	ldr r1, _02070A80 ; =0x00000B25
	ldrb r1, [r5, r1]
	cmp r6, r1
	bne _02070A38
	mov r4, #0x4
	b _02070A3A
_02070A38:
	mov r4, #0x0
_02070A3A:
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _02070A4E
	add r0, r4, #0x2
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	b _02070A60
_02070A4E:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02070A88
	cmp r0, #0x1
	bne _02070A60
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02070A60:
	ldr r1, _02070A84 ; =0x000004A4
	add r3, r6, #0x3
	add r2, r5, r1
	lsl r1, r4, #0x5
	lsl r3, r3, #0x15
	add r1, r2, r1
	mov r0, #0x2
	mov r2, #0x10
	lsr r3, r3, #0x10
	bl FUN_02017FB4
	pop {r4-r6, pc}
	.balign 4
_02070A78: .word 0x000005A4
_02070A7C: .word 0x00000B23
_02070A80: .word 0x00000B25
_02070A84: .word 0x000004A4

	thumb_func_start FUN_02070A88
FUN_02070A88: ; 0x02070A88
	ldr r2, _02070AA0 ; =0x000005A4
	ldr r0, [r0, r2]
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _02070A9A
	mov r0, #0x1
	tst r1, r0
	bne _02070A9C
_02070A9A:
	mov r0, #0x0
_02070A9C:
	bx lr
	nop
_02070AA0: .word 0x000005A4

	thumb_func_start FUN_02070AA4
FUN_02070AA4: ; 0x02070AA4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	mov r3, #0x0
	ldr r0, _02070AF4 ; =0x00000B25
	str r3, [sp, #0x0]
	ldrb r0, [r4, r0]
	add r1, sp, #0xc
	add r1, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, _02070AF8 ; =0x00000808
	add r2, sp, #0xc
	ldr r0, [r4, r0]
	bl FUN_0201C638
	ldr r0, _02070AFC ; =0x000005A4
	ldr r1, _02070AF4 ; =0x00000B25
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	bl FUN_020714BC
	add r1, r0, #0x0
	ldr r0, _02070B00 ; =0x000005C8
	ldr r0, [r4, r0]
	bl FUN_02020130
	ldr r0, _02070B00 ; =0x000005C8
	add r2, sp, #0xc
	ldrb r1, [r2, #0x1]
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, r0]
	bl FUN_0200C6E4
	add sp, #0x10
	pop {r4, pc}
	nop
_02070AF4: .word 0x00000B25
_02070AF8: .word 0x00000808
_02070AFC: .word 0x000005A4
_02070B00: .word 0x000005C8

	thumb_func_start FUN_02070B04
FUN_02070B04: ; 0x02070B04
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02070B28
	cmp r0, #0x1
	bne _02070B14
	mov r0, #0x1
	pop {r4, pc}
_02070B14:
	add r0, r4, #0x0
	bl FUN_02070D90
	cmp r0, #0x1
	bne _02070B22
	mov r0, #0x2
	pop {r4, pc}
_02070B22:
	mov r0, #0x5
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02070B28
FUN_02070B28: ; 0x02070B28
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	ldr r0, _02070CC0 ; =gUnknown21C48B8
	mov r1, #0x40
	ldr r0, [r0, #0x4c]
	mov r3, #0x4
	tst r1, r0
	beq _02070B3E
	mov r3, #0x0
	b _02070B5A
_02070B3E:
	mov r1, #0x80
	tst r1, r0
	beq _02070B48
	mov r3, #0x1
	b _02070B5A
_02070B48:
	mov r1, #0x20
	tst r1, r0
	beq _02070B52
	mov r3, #0x2
	b _02070B5A
_02070B52:
	mov r1, #0x10
	tst r0, r1
	beq _02070B5A
	mov r3, #0x3
_02070B5A:
	cmp r3, #0x4
	bne _02070B64
	add sp, #0x4
	mov r0, #0x0
	pop {r3-r6, pc}
_02070B64:
	ldr r4, _02070CC4 ; =0x00000B25
	ldrb r0, [r5, r4]
	cmp r0, #0x6
	bne _02070BA0
	cmp r3, #0x0
	add r1, sp, #0x0
	bne _02070B92
	add r4, r4, #0x1
	ldrb r6, [r5, r4]
	mov r4, #0x1
	ldr r3, _02070CC8 ; =UNK_020F9468
	and r4, r6
	add r6, r4, #0x2
	mov r4, #0x6
	mul r4, r6
	add r0, r5, #0x0
	add r1, #0x1
	add r2, sp, #0x0
	add r3, r3, r4
	bl FUN_02070D2C
	add r6, r0, #0x0
	b _02070C1A
_02070B92:
	add r0, r5, #0x0
	add r1, #0x1
	add r2, sp, #0x0
	bl FUN_02070CDC
	add r6, r0, #0x0
	b _02070C1A
_02070BA0:
	cmp r0, #0x7
	bne _02070C0C
	ldr r0, _02070CCC ; =0x000005A4
	ldr r0, [r5, r0]
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	beq _02070BDA
	cmp r0, #0x11
	beq _02070BDA
	cmp r3, #0x0
	bne _02070BDA
	add r4, r4, #0x1
	ldrb r6, [r5, r4]
	mov r4, #0x1
	add r1, sp, #0x0
	and r4, r6
	add r6, r4, #0x2
	mov r4, #0x6
	ldr r3, _02070CC8 ; =UNK_020F9468
	mul r4, r6
	add r0, r5, #0x0
	add r1, #0x1
	add r2, sp, #0x0
	add r3, r3, r4
	bl FUN_02070D2C
	add r6, r0, #0x0
	b _02070C1A
_02070BDA:
	cmp r3, #0x1
	add r1, sp, #0x0
	bne _02070BFE
	ldr r4, _02070CD0 ; =0x00000B26
	ldr r3, _02070CC8 ; =UNK_020F9468
	ldrb r6, [r5, r4]
	mov r4, #0x1
	add r0, r5, #0x0
	and r6, r4
	mov r4, #0x6
	mul r4, r6
	add r1, #0x1
	add r2, sp, #0x0
	add r3, r3, r4
	bl FUN_02070D2C
	add r6, r0, #0x0
	b _02070C1A
_02070BFE:
	add r0, r5, #0x0
	add r1, #0x1
	add r2, sp, #0x0
	bl FUN_02070CDC
	add r6, r0, #0x0
	b _02070C1A
_02070C0C:
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x1
	add r2, sp, #0x0
	bl FUN_02070CDC
	add r6, r0, #0x0
_02070C1A:
	ldr r0, _02070CC4 ; =0x00000B25
	ldrb r0, [r5, r0]
	cmp r6, r0
	beq _02070CB8
	cmp r6, #0xff
	beq _02070CB8
	add r0, r6, #0x0
	add r0, #0xfa
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	bhi _02070C3E
	ldr r0, _02070CD4 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	b _02070C6E
_02070C3E:
	ldr r0, _02070CCC ; =0x000005A4
	add r1, r6, #0x0
	ldr r0, [r5, r0]
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	bl FUN_020714BC
	add r1, r0, #0x0
	ldr r0, _02070CD4 ; =0x000005C8
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldr r0, _02070CD4 ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _02070CD4 ; =0x000005C8
	add r2, sp, #0x0
	ldrb r1, [r2, #0x1]
	ldrb r2, [r2, #0x0]
	ldr r0, [r5, r0]
	bl FUN_0200C6E4
_02070C6E:
	ldr r0, _02070CC4 ; =0x00000B25
	mov r2, #0x0
	ldrb r4, [r5, r0]
	strb r6, [r5, r0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020713EC
	ldr r1, _02070CC4 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	mov r2, #0x1
	bl FUN_020713EC
	ldr r0, _02070CD8 ; =0x000005DC
	bl FUN_020054C8
	cmp r4, #0x6
	bhs _02070CA6
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020717E8
	ldr r0, [r5, #0x0]
	mov r1, #0x4
	bl FUN_0201AC68
_02070CA6:
	cmp r4, #0x6
	beq _02070CB2
	cmp r4, #0x7
	beq _02070CB2
	ldr r0, _02070CD0 ; =0x00000B26
	strb r4, [r5, r0]
_02070CB2:
	add sp, #0x4
	mov r0, #0x1
	pop {r3-r6, pc}
_02070CB8:
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_02070CC0: .word gUnknown21C48B8
_02070CC4: .word 0x00000B25
_02070CC8: .word UNK_020F9468
_02070CCC: .word 0x000005A4
_02070CD0: .word 0x00000B26
_02070CD4: .word 0x000005C8
_02070CD8: .word 0x000005DC

	thumb_func_start FUN_02070CDC
FUN_02070CDC: ; 0x02070CDC
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, _02070D24 ; =0x00000B25
	add r7, r1, #0x0
	ldrb r4, [r5, r0]
	str r2, [sp, #0xc]
	add r6, r3, #0x0
_02070CEC:
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	ldr r0, _02070D28 ; =0x00000808
	str r6, [sp, #0x8]
	ldr r0, [r5, r0]
	ldr r2, [sp, #0xc]
	add r1, r7, #0x0
	mov r3, #0x0
	bl FUN_0201C638
	add r4, r0, #0x0
	cmp r4, #0x6
	beq _02070D1C
	cmp r4, #0x7
	beq _02070D1C
	cmp r4, #0xff
	beq _02070D1C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207007C
	cmp r0, #0x0
	beq _02070CEC
_02070D1C:
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_02070D24: .word 0x00000B25
_02070D28: .word 0x00000808

	thumb_func_start FUN_02070D2C
FUN_02070D2C: ; 0x02070D2C
	push {r3-r7, lr}
	sub sp, #0x10
	add r6, r0, #0x0
	add r7, r1, #0x0
	str r2, [sp, #0xc]
	add r5, r3, #0x0
	mov r4, #0x0
_02070D3A:
	cmp r4, #0x6
	beq _02070D70
	ldrb r1, [r5, r4]
	add r0, r6, #0x0
	bl FUN_0207007C
	cmp r0, #0x0
	beq _02070D68
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldrb r0, [r5, r4]
	ldr r2, [sp, #0xc]
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, _02070D8C ; =0x00000808
	ldr r0, [r6, r0]
	bl FUN_0201C638
	add sp, #0x10
	ldrb r0, [r5, r4]
	pop {r3-r7, pc}
_02070D68:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	b _02070D3A
_02070D70:
	mov r3, #0x0
	str r3, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, _02070D8C ; =0x00000808
	ldr r2, [sp, #0xc]
	ldr r0, [r6, r0]
	add r1, r7, #0x0
	bl FUN_0201C638
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02070D8C: .word 0x00000808

	thumb_func_start FUN_02070D90
FUN_02070D90: ; 0x02070D90
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	bl FUN_02071870
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02070E42
	ldr r1, _02070E48 ; =0x00000B25
	mov r2, #0x0
	ldrb r4, [r5, r1]
	strb r0, [r5, r1]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020713EC
	ldr r1, _02070E48 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	mov r2, #0x1
	bl FUN_020713EC
	cmp r4, #0x6
	bhs _02070DCC
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020717E8
_02070DCC:
	mov r3, #0x0
	ldr r0, _02070E48 ; =0x00000B25
	str r3, [sp, #0x0]
	ldrb r0, [r5, r0]
	add r1, sp, #0xc
	add r1, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, _02070E4C ; =0x00000808
	add r2, sp, #0xc
	ldr r0, [r5, r0]
	bl FUN_0201C638
	ldr r0, _02070E50 ; =0x000005A4
	ldr r1, _02070E48 ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	bl FUN_020714BC
	add r1, r0, #0x0
	ldr r0, _02070E54 ; =0x000005C8
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldr r0, _02070E54 ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _02070E54 ; =0x000005C8
	add r2, sp, #0xc
	ldrb r1, [r2, #0x1]
	ldrb r2, [r2, #0x0]
	ldr r0, [r5, r0]
	bl FUN_0200C6E4
	mov r0, #0xb2
	mov r1, #0x1
	lsl r0, r0, #0x4
	strb r1, [r5, r0]
	add r1, r0, #0x5
	ldrb r1, [r5, r1]
	add r0, r0, #0x1
	strb r1, [r5, r0]
	ldr r0, _02070E58 ; =0x000005E4
	bl FUN_020054C8
	cmp r4, #0x6
	beq _02070E3C
	cmp r4, #0x7
	beq _02070E3C
	ldr r0, _02070E5C ; =0x00000B26
	strb r4, [r5, r0]
_02070E3C:
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r5, pc}
_02070E42:
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4
_02070E48: .word 0x00000B25
_02070E4C: .word 0x00000808
_02070E50: .word 0x000005A4
_02070E54: .word 0x000005C8
_02070E58: .word 0x000005E4
_02070E5C: .word 0x00000B26

	thumb_func_start FUN_02070E60
FUN_02070E60: ; 0x02070E60
	push {r4-r6, lr}
	sub sp, #0x10
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	add r0, #0xfa
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	bhi _02070E80
	ldr r0, _02070F04 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	b _02070ECC
_02070E80:
	mov r3, #0x0
	ldr r0, _02070F08 ; =0x00000B25
	str r3, [sp, #0x0]
	ldrb r0, [r5, r0]
	add r1, sp, #0xc
	add r1, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, _02070F0C ; =0x00000808
	add r2, sp, #0xc
	ldr r0, [r5, r0]
	bl FUN_0201C638
	ldr r0, _02070F10 ; =0x000005A4
	add r1, r6, #0x0
	ldr r0, [r5, r0]
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	bl FUN_020714BC
	add r1, r0, #0x0
	ldr r0, _02070F04 ; =0x000005C8
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldr r0, _02070F04 ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _02070F04 ; =0x000005C8
	add r2, sp, #0xc
	ldrb r1, [r2, #0x1]
	ldrb r2, [r2, #0x0]
	ldr r0, [r5, r0]
	bl FUN_0200C6E4
_02070ECC:
	ldr r0, _02070F08 ; =0x00000B25
	mov r2, #0x0
	ldrb r4, [r5, r0]
	strb r6, [r5, r0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020713EC
	ldr r1, _02070F08 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	mov r2, #0x1
	bl FUN_020713EC
	cmp r4, #0x6
	bhs _02070EFE
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020717E8
	ldr r0, [r5, #0x0]
	mov r1, #0x4
	bl FUN_0201AC68
_02070EFE:
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02070F04: .word 0x000005C8
_02070F08: .word 0x00000B25
_02070F0C: .word 0x00000808
_02070F10: .word 0x000005A4

	thumb_func_start FUN_02070F14
FUN_02070F14: ; 0x02070F14
	push {r3-r4, lr}
	sub sp, #0x4
	mov r1, #0xb2
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldrb r2, [r4, r1]
	cmp r2, #0x0
	beq _02070F8A
	cmp r2, #0x1
	beq _02070F30
	cmp r2, #0x2
	beq _02070F70
	add sp, #0x4
	pop {r3-r4, pc}
_02070F30:
	add r0, r1, #0x1
	ldrb r0, [r4, r0]
	add r1, sp, #0x0
	add r1, #0x2
	add r2, sp, #0x0
	bl FUN_02071850
	add r3, sp, #0x0
	mov r1, #0x2
	mov r2, #0x0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, r4, #0x0
	bl FUN_02073D1C
	ldr r1, _02070F90 ; =0x00000B21
	add r0, r4, #0x0
	ldrb r1, [r4, r1]
	mov r2, #0x2
	bl FUN_020717E8
	ldr r0, [r4, #0x0]
	mov r1, #0x4
	bl FUN_0201AC68
	mov r0, #0xb2
	lsl r0, r0, #0x4
	ldrb r1, [r4, r0]
	add sp, #0x4
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r4, pc}
_02070F70:
	add r1, r1, #0x1
	ldrb r1, [r4, r1]
	mov r2, #0x1
	bl FUN_020717E8
	ldr r0, [r4, #0x0]
	mov r1, #0x4
	bl FUN_0201AC68
	mov r0, #0xb2
	mov r1, #0x0
	lsl r0, r0, #0x4
	strb r1, [r4, r0]
_02070F8A:
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_02070F90: .word 0x00000B21

	thumb_func_start FUN_02070F94
FUN_02070F94: ; 0x02070F94
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020710AC ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	beq _0207104A
	ldr r0, _020710B0 ; =0x00000B25
	ldrb r1, [r4, r0]
	cmp r1, #0x6
	bne _02070FAE
	mov r0, #0x4
	pop {r4, pc}
_02070FAE:
	cmp r1, #0x7
	bne _02070FC6
	ldr r0, _020710B4 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _020710B8 ; =0x00000B23
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _0207104A
	mov r0, #0x3
	pop {r4, pc}
_02070FC6:
	ldr r0, _020710BC ; =0x000005A4
	ldr r2, [r4, r0]
	add r2, #0x20
	ldrb r2, [r2, #0x0]
	cmp r2, #0x3
	beq _02070FD6
	cmp r2, #0x13
	bne _02070FE0
_02070FD6:
	ldr r0, _020710B4 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x0
	pop {r4, pc}
_02070FE0:
	cmp r2, #0x14
	beq _02070FE8
	cmp r2, #0xe
	bne _0207100C
_02070FE8:
	mov r0, #0x2c
	mul r0, r1
	add r1, r4, r0
	mov r0, #0x71
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02071002
	ldr r0, _020710B4 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x0
	pop {r4, pc}
_02071002:
	ldr r0, _020710C0 ; =0x000005F2
	bl FUN_020054C8
	mov r0, #0x5
	pop {r4, pc}
_0207100C:
	cmp r2, #0xf
	bne _0207103A
	mov r2, #0x2c
	mul r2, r1
	mov r1, #0x71
	add r2, r4, r2
	lsl r1, r1, #0x4
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	bne _02071030
	add r0, #0x38
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_020710C4
	mov r0, #0x0
	pop {r4, pc}
_02071030:
	add r0, #0x4e
	bl FUN_020054C8
	mov r0, #0x5
	pop {r4, pc}
_0207103A:
	add r0, #0x38
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_020710C4
	mov r0, #0x0
	pop {r4, pc}
_0207104A:
	ldr r0, _020710AC ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x2
	tst r0, r1
	beq _0207106E
	ldr r0, _020710B8 ; =0x00000B23
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _0207106E
	ldr r0, _020710B4 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _020710B0 ; =0x00000B25
	mov r1, #0x7
	strb r1, [r4, r0]
	mov r0, #0x3
	pop {r4, pc}
_0207106E:
	add r0, r4, #0x0
	bl FUN_02070B04
	cmp r0, #0x2
	bne _020710AA
	ldr r1, _020710BC ; =0x000005A4
	ldr r1, [r4, r1]
	add r1, #0x20
	ldrb r1, [r1, #0x0]
	cmp r1, #0x14
	beq _0207108E
	add r1, #0xf2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #0x1
	bhi _020710AA
_0207108E:
	ldr r1, _020710B0 ; =0x00000B25
	ldrb r2, [r4, r1]
	mov r1, #0x2c
	mul r1, r2
	add r2, r4, r1
	mov r1, #0x71
	lsl r1, r1, #0x4
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _020710AA
	ldr r0, _020710C0 ; =0x000005F2
	bl FUN_020054C8
	mov r0, #0x5
_020710AA:
	pop {r4, pc}
	.balign 4
_020710AC: .word gUnknown21C48B8
_020710B0: .word 0x00000B25
_020710B4: .word 0x000005DC
_020710B8: .word 0x00000B23
_020710BC: .word 0x000005A4
_020710C0: .word 0x000005F2

	thumb_func_start FUN_020710C4
FUN_020710C4: ; 0x020710C4
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	mov r0, #0xc
	mov r1, #0x8
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r0, _02071174 ; =0x000005A4
	ldr r0, [r5, r0]
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0xf
	bgt _020710FC
	bge _02071124
	cmp r0, #0x2
	bgt _0207113C
	cmp r0, #0x0
	blt _0207113C
	beq _0207110C
	cmp r0, #0x2
	beq _02071118
	b _0207113C
_020710FC:
	cmp r0, #0x12
	bgt _0207113C
	cmp r0, #0x11
	blt _0207113C
	beq _02071118
	cmp r0, #0x12
	beq _02071130
	b _0207113C
_0207110C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207117C
	add r2, r0, #0x0
	b _02071146
_02071118:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020712F0
	add r2, r0, #0x0
	b _02071146
_02071124:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02071274
	add r2, r0, #0x0
	b _02071146
_02071130:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02071280
	add r2, r0, #0x0
	b _02071146
_0207113C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020712B4
	add r2, r0, #0x0
_02071146:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02072844
	mov r0, #0xc
	add r1, r4, #0x0
	bl FUN_02016A8C
	add r0, r5, #0x0
	bl FUN_0207295C
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731D4
	ldr r0, _02071178 ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_0200C664
	pop {r3-r5, pc}
	.balign 4
_02071174: .word 0x000005A4
_02071178: .word 0x000005C8

	thumb_func_start FUN_0207117C
FUN_0207117C: ; 0x0207117C
	push {r4-r7, lr}
	sub sp, #0xc
	str r1, [sp, #0x4]
	ldr r1, _02071268 ; =0x000005A4
	str r0, [sp, #0x0]
	ldr r0, [r0, r1]
	ldr r2, _0207126C ; =0x00000B25
	ldr r1, [sp, #0x0]
	ldr r0, [r0, #0x0]
	ldrb r1, [r1, r2]
	bl GetPartyMonByIndex
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4]
	mov r1, #0x1
	strb r1, [r0, #0x0]
	mov r4, #0x0
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r1, _02071268 ; =0x000005A4
	ldr r0, [sp, #0x0]
	ldr r0, [r0, r1]
	ldr r0, [r0, #0x1c]
	bl FUN_02060144
	cmp r0, #0x0
	bne _02071258
	ldr r1, _0207126C ; =0x00000B25
	ldr r0, [sp, #0x0]
	ldrb r1, [r0, r1]
	mov r0, #0x2c
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [sp, #0x0]
	add r1, r0, r2
	mov r0, #0x71
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0207124C
	add r6, r4, #0x0
_020711D0:
	add r1, r6, #0x0
	ldr r0, [sp, #0x8]
	add r1, #0x36
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	beq _02071210
	add r0, r7, #0x0
	bl FUN_02071948
	cmp r0, #0xff
	beq _02071206
	ldr r1, [sp, #0x4]
	add r2, r4, #0x0
	strb r0, [r1, r5]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	bl FUN_020727FC
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02071206:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x4
	blo _020711D0
_02071210:
	ldr r0, [sp, #0x4]
	mov r1, #0x0
	strb r1, [r0, r5]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r1, _0207126C ; =0x00000B25
	ldr r0, [sp, #0x0]
	ldrb r1, [r0, r1]
	mov r0, #0x2c
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [sp, #0x0]
	add r1, r0, r2
	ldr r0, _02071270 ; =0x0000070C
	ldrh r0, [r1, r0]
	bl ItemIdIsMail
	cmp r0, #0x1
	bne _0207123E
	mov r1, #0x5
	ldr r0, [sp, #0x4]
	b _02071242
_0207123E:
	ldr r0, [sp, #0x4]
	mov r1, #0x2
_02071242:
	strb r1, [r0, r5]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	b _02071258
_0207124C:
	ldr r0, [sp, #0x4]
	add r1, r4, #0x0
	strb r1, [r0, r5]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
_02071258:
	ldr r0, [sp, #0x4]
	mov r1, #0x9
	strb r1, [r0, r5]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02071268: .word 0x000005A4
_0207126C: .word 0x00000B25
_02071270: .word 0x0000070C

	thumb_func_start FUN_02071274
FUN_02071274: ; 0x02071274
	mov r0, #0xe
	strb r0, [r1, #0x0]
	mov r0, #0x9
	strb r0, [r1, #0x1]
	mov r0, #0x2
	bx lr

	thumb_func_start FUN_02071280
FUN_02071280: ; 0x02071280
	ldr r2, _020712B0 ; =0x00000B25
	ldrb r3, [r0, r2]
	mov r2, #0x2c
	mul r2, r3
	add r2, r0, r2
	mov r0, #0x71
	lsl r0, r0, #0x4
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	bne _020712A4
	mov r0, #0x8
	strb r0, [r1, #0x0]
	mov r0, #0x1
	strb r0, [r1, #0x1]
	mov r0, #0x9
	strb r0, [r1, #0x2]
	mov r0, #0x3
	bx lr
_020712A4:
	mov r0, #0x1
	strb r0, [r1, #0x0]
	mov r0, #0x9
	strb r0, [r1, #0x1]
	mov r0, #0x2
	bx lr
	.balign 4
_020712B0: .word 0x00000B25

	thumb_func_start FUN_020712B4
FUN_020712B4: ; 0x020712B4
	ldr r2, _020712E8 ; =0x00000B25
	ldrb r3, [r0, r2]
	mov r2, #0x2c
	mul r2, r3
	add r2, r0, r2
	ldr r0, _020712EC ; =0x0000070E
	ldrh r0, [r2, r0]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	bne _020712DA
	mov r0, #0xd
	strb r0, [r1, #0x0]
	mov r0, #0x1
	strb r0, [r1, #0x1]
	mov r0, #0x9
	strb r0, [r1, #0x2]
	mov r0, #0x3
	bx lr
_020712DA:
	mov r0, #0x1
	strb r0, [r1, #0x0]
	mov r0, #0x9
	strb r0, [r1, #0x1]
	mov r0, #0x2
	bx lr
	nop
_020712E8: .word 0x00000B25
_020712EC: .word 0x0000070E

	thumb_func_start FUN_020712F0
FUN_020712F0: ; 0x020712F0
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, _0207133C ; =0x00000B25
	ldrb r1, [r0, r1]
	bl FUN_02071340
	cmp r0, #0x0
	beq _0207130A
	cmp r0, #0x1
	beq _02071316
	cmp r0, #0x2
	beq _02071326
	b _02071336
_0207130A:
	mov r0, #0x1
	strb r0, [r4, #0x0]
	mov r0, #0x9
	strb r0, [r4, #0x1]
	mov r0, #0x2
	pop {r4, pc}
_02071316:
	mov r0, #0xb
	strb r0, [r4, #0x0]
	mov r0, #0x1
	strb r0, [r4, #0x1]
	mov r0, #0x9
	strb r0, [r4, #0x2]
	mov r0, #0x3
	pop {r4, pc}
_02071326:
	mov r0, #0xc
	strb r0, [r4, #0x0]
	mov r0, #0x1
	strb r0, [r4, #0x1]
	mov r0, #0x9
	strb r0, [r4, #0x2]
	mov r0, #0x3
	pop {r4, pc}
_02071336:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0207133C: .word 0x00000B25

	thumb_func_start FUN_02071340
FUN_02071340: ; 0x02071340
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _020713E0 ; =0x000005A4
	add r4, r1, #0x0
	ldr r2, [r5, r0]
	ldr r0, [r2, #0x14]
	cmp r0, #0x0
	beq _0207136E
	ldr r0, [r2, #0x0]
	bl GetPartyMonByIndex
	add r1, r0, #0x0
	ldr r0, _020713E0 ; =0x000005A4
	ldr r2, _020713E4 ; =0x00000B34
	ldr r0, [r5, r0]
	ldr r2, [r5, r2]
	ldr r0, [r0, #0x14]
	bl FUN_0206BB84
	cmp r0, #0x0
	bne _0207136E
	mov r0, #0x0
	pop {r4-r6, pc}
_0207136E:
	ldr r0, _020713E0 ; =0x000005A4
	ldr r0, [r5, r0]
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x11
	bne _02071390
	mov r0, #0x2c
	mul r0, r4
	add r1, r5, r0
	ldr r0, _020713E8 ; =0x00000704
	ldrh r0, [r1, r0]
	bl IsPokemonLegendaryOrMythical
	cmp r0, #0x1
	bne _02071390
	mov r0, #0x0
	pop {r4-r6, pc}
_02071390:
	ldr r1, _020713E0 ; =0x000005A4
	mov r0, #0x0
	ldr r2, [r5, r1]
	add r1, r2, #0x0
	add r1, #0x32
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x18
	lsr r3, r1, #0x1c
	beq _020713BC
	add r1, r4, #0x1
_020713A4:
	add r6, r2, r0
	add r6, #0x2c
	ldrb r6, [r6, #0x0]
	cmp r1, r6
	bne _020713B2
	mov r0, #0x2
	pop {r4-r6, pc}
_020713B2:
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, r3
	blo _020713A4
_020713BC:
	mov r0, #0x2c
	mul r0, r4
	add r3, r5, r0
	mov r0, #0x71
	lsl r0, r0, #0x4
	ldrb r1, [r3, r0]
	cmp r1, #0x1
	beq _020713D8
	sub r0, r0, #0x6
	add r2, #0x33
	ldrh r1, [r3, r0]
	ldrb r0, [r2, #0x0]
	cmp r1, r0
	ble _020713DC
_020713D8:
	mov r0, #0x0
	pop {r4-r6, pc}
_020713DC:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_020713E0: .word 0x000005A4
_020713E4: .word 0x00000B34
_020713E8: .word 0x00000704

	thumb_func_start FUN_020713EC
FUN_020713EC: ; 0x020713EC
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x6
	bne _02071426
	mov r0, #0x5d
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	bl FUN_020201DC
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r6, #0x0
	bne _02071410
	mov r0, #0x2
	and r0, r1
	b _02071416
_02071410:
	mov r0, #0x2
	and r0, r1
	add r0, r0, #0x1
_02071416:
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x5d
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	bl FUN_02020130
	pop {r4-r6, pc}
_02071426:
	cmp r4, #0x7
	bne _02071454
	ldr r0, _020714B4 ; =0x000005D4
	ldr r0, [r5, r0]
	bl FUN_020201DC
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r6, #0x0
	bne _02071440
	mov r0, #0x2
	and r0, r1
	b _02071446
_02071440:
	mov r0, #0x2
	and r0, r1
	add r0, r0, #0x1
_02071446:
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, _020714B4 ; =0x000005D4
	ldr r0, [r5, r0]
	bl FUN_02020130
	pop {r4-r6, pc}
_02071454:
	cmp r6, #0x0
	ldr r1, _020714B8 ; =0x00000716
	bne _02071482
	mov r0, #0x2c
	add r3, r5, r1
	mul r0, r4
	ldrsh r2, [r3, r0]
	add r1, r1, #0x2
	sub r2, r2, #0x2
	strh r2, [r3, r0]
	add r2, r5, r1
	ldrsh r1, [r2, r0]
	sub r1, r1, #0x2
	strh r1, [r2, r0]
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x5b
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	mov r1, #0x0
	bl FUN_02020130
	b _020714A8
_02071482:
	mov r0, #0x2c
	add r3, r5, r1
	mul r0, r4
	ldrsh r2, [r3, r0]
	add r1, r1, #0x2
	add r2, r2, #0x2
	strh r2, [r3, r0]
	add r2, r5, r1
	ldrsh r1, [r2, r0]
	add r1, r1, #0x2
	strh r1, [r2, r0]
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x5b
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	mov r1, #0x1
	bl FUN_02020130
_020714A8:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020709FC
	pop {r4-r6, pc}
	nop
_020714B4: .word 0x000005D4
_020714B8: .word 0x00000716

	thumb_func_start FUN_020714BC
FUN_020714BC: ; 0x020714BC
	cmp r1, #0x0
	beq _020714C8
	cmp r0, #0x0
	beq _020714CC
	cmp r1, #0x1
	bne _020714CC
_020714C8:
	mov r0, #0x1
	bx lr
_020714CC:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020714D0
FUN_020714D0: ; 0x020714D0
	push {r4, lr}
	ldr r1, _02071550 ; =gUnknown21C48B8
	add r4, r0, #0x0
	ldr r2, [r1, #0x48]
	mov r1, #0x1
	tst r1, r2
	beq _0207150C
	ldr r0, _02071554 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _02071558 ; =0x00000B25
	ldrb r1, [r4, r0]
	cmp r1, #0x6
	bhs _020714F8
	sub r0, r0, #0x2
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1a
	cmp r1, r0
	bne _02071502
_020714F8:
	add r0, r4, #0x0
	bl FUN_02074538
	mov r0, #0x3
	pop {r4, pc}
_02071502:
	add r0, r4, #0x0
	bl FUN_02074584
	mov r0, #0x0
	pop {r4, pc}
_0207150C:
	mov r1, #0x2
	tst r1, r2
	beq _02071522
	ldr r0, _02071554 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_02074538
	mov r0, #0x3
	pop {r4, pc}
_02071522:
	bl FUN_02070B04
	cmp r0, #0x2
	bne _0207154C
	ldr r0, _02071558 ; =0x00000B25
	ldrb r1, [r4, r0]
	sub r0, r0, #0x2
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1a
	cmp r1, r0
	bne _02071544
	add r0, r4, #0x0
	bl FUN_02074538
	mov r0, #0x3
	pop {r4, pc}
_02071544:
	add r0, r4, #0x0
	bl FUN_02074584
	mov r0, #0x0
_0207154C:
	pop {r4, pc}
	nop
_02071550: .word gUnknown21C48B8
_02071554: .word 0x000005DC
_02071558: .word 0x00000B25

	thumb_func_start FUN_0207155C
FUN_0207155C: ; 0x0207155C
	push {r3-r5, lr}
	sub sp, #0x8
	ldr r1, _02071738 ; =0x000005A4
	add r4, r0, #0x0
	ldr r3, [r4, r1]
	mov r0, #0x0
	add r1, r3, #0x0
	add r1, #0x32
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	beq _02071606
_02071574:
	add r2, r3, r0
	add r2, #0x2c
	ldrb r2, [r2, #0x0]
	cmp r2, #0x0
	bne _020715FC
	add r3, #0x32
	ldrb r0, [r3, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	cmp r0, #0x6
	bhi _020715E0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02071596: ; jump table (using 16-bit offset)
	.short _020715E0 - _02071596 - 2; case 0
	.short _020715E0 - _02071596 - 2; case 1
	.short _020715A4 - _02071596 - 2; case 2
	.short _020715B0 - _02071596 - 2; case 3
	.short _020715BC - _02071596 - 2; case 4
	.short _020715C8 - _02071596 - 2; case 5
	.short _020715D4 - _02071596 - 2; case 6
_020715A4:
	add r0, r4, #0x0
	mov r1, #0x6b
	mov r2, #0x1
	bl FUN_020731E8
	b _020715EA
_020715B0:
	add r0, r4, #0x0
	mov r1, #0x77
	mov r2, #0x1
	bl FUN_020731E8
	b _020715EA
_020715BC:
	add r0, r4, #0x0
	mov r1, #0x78
	mov r2, #0x1
	bl FUN_020731E8
	b _020715EA
_020715C8:
	add r0, r4, #0x0
	mov r1, #0x79
	mov r2, #0x1
	bl FUN_020731E8
	b _020715EA
_020715D4:
	add r0, r4, #0x0
	mov r1, #0x7a
	mov r2, #0x1
	bl FUN_020731E8
	b _020715EA
_020715E0:
	add r0, r4, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731E8
_020715EA:
	ldr r0, _0207173C ; =0x00000B22
	mov r1, #0x13
	strb r1, [r4, r0]
	ldr r0, _02071740 ; =0x000005F2
	bl FUN_020054C8
	add sp, #0x8
	mov r0, #0x14
	pop {r3-r5, pc}
_020715FC:
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, r1
	blo _02071574
_02071606:
	ldr r0, [r3, #0x14]
	cmp r0, #0x0
	beq _020716CA
	ldr r2, _02071744 ; =0x00000B34
	ldr r1, [r3, #0x0]
	ldr r2, [r4, r2]
	add r3, #0x2c
	bl FUN_0206BC60
	cmp r0, #0x3
	bhi _020716CA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02071628: ; jump table (using 16-bit offset)
	.short _020716CA - _02071628 - 2; case 0
	.short _02071630 - _02071628 - 2; case 1
	.short _02071692 - _02071628 - 2; case 2
	.short _020716AE - _02071628 - 2; case 3
_02071630:
	ldr r0, _02071748 ; =0x0000069C
	mov r1, #0xb8
	ldr r0, [r4, r0]
	bl NewString_ReadMsgData
	add r5, r0, #0x0
	ldr r0, _02071738 ; =0x000005A4
	mov r1, #0x3
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x14]
	bl FUN_02023B0C
	mov r1, #0x0
	add r2, r0, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r3, #0x3
	bl FUN_0200AD38
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl StringExpandPlaceholders
	add r0, r5, #0x0
	bl String_dtor
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _0207173C ; =0x00000B22
	mov r1, #0x13
	strb r1, [r4, r0]
	ldr r0, _02071740 ; =0x000005F2
	bl FUN_020054C8
	add sp, #0x8
	mov r0, #0x14
	pop {r3-r5, pc}
_02071692:
	add r0, r4, #0x0
	mov r1, #0xb6
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _0207173C ; =0x00000B22
	mov r1, #0x13
	strb r1, [r4, r0]
	ldr r0, _02071740 ; =0x000005F2
	bl FUN_020054C8
	add sp, #0x8
	mov r0, #0x14
	pop {r3-r5, pc}
_020716AE:
	add r0, r4, #0x0
	mov r1, #0xb7
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _0207173C ; =0x00000B22
	mov r1, #0x13
	strb r1, [r4, r0]
	ldr r0, _02071740 ; =0x000005F2
	bl FUN_020054C8
	add sp, #0x8
	mov r0, #0x14
	pop {r3-r5, pc}
_020716CA:
	ldr r0, _02071738 ; =0x000005A4
	ldr r0, [r4, r0]
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x11
	bne _02071722
	add r0, r4, #0x0
	bl FUN_0207174C
	cmp r0, #0x0
	beq _02071722
	cmp r0, #0x1
	beq _020716EA
	cmp r0, #0x2
	beq _02071706
	b _02071722
_020716EA:
	add r0, r4, #0x0
	mov r1, #0xb6
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _0207173C ; =0x00000B22
	mov r1, #0x13
	strb r1, [r4, r0]
	ldr r0, _02071740 ; =0x000005F2
	bl FUN_020054C8
	add sp, #0x8
	mov r0, #0x14
	pop {r3-r5, pc}
_02071706:
	add r0, r4, #0x0
	mov r1, #0xb7
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _0207173C ; =0x00000B22
	mov r1, #0x13
	strb r1, [r4, r0]
	ldr r0, _02071740 ; =0x000005F2
	bl FUN_020054C8
	add sp, #0x8
	mov r0, #0x14
	pop {r3-r5, pc}
_02071722:
	ldr r0, _02071738 ; =0x000005A4
	mov r2, #0x0
	ldr r1, [r4, r0]
	add r0, #0x38
	add r1, #0x23
	strb r2, [r1, #0x0]
	bl FUN_020054C8
	mov r0, #0x1b
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_02071738: .word 0x000005A4
_0207173C: .word 0x00000B22
_02071740: .word 0x000005F2
_02071744: .word 0x00000B34
_02071748: .word 0x0000069C

	thumb_func_start FUN_0207174C
FUN_0207174C: ; 0x0207174C
	push {r4-r7}
	add r5, r0, #0x0
	mov r0, #0x0
	mov r12, r0
	ldr r0, _020717E0 ; =0x000005A4
	ldr r4, [r5, r0]
_02071758:
	mov r0, r12
	add r0, r4, r0
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020717DA
	mov r0, r12
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	cmp r3, #0x6
	bhs _020717CC
	mov r0, r12
	add r7, r4, r0
_02071774:
	add r0, r4, r3
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020717CC
	add r0, r4, r3
	add r0, #0x2c
	ldrb r1, [r0, #0x0]
	mov r0, #0x2c
	ldr r6, _020717E4 ; =0x000006D8
	mul r0, r1
	add r2, r5, r0
	add r0, r7, #0x0
	add r0, #0x2c
	ldrb r1, [r0, #0x0]
	mov r0, #0x2c
	ldrh r6, [r2, r6]
	mul r0, r1
	add r1, r5, r0
	ldr r0, _020717E4 ; =0x000006D8
	ldrh r0, [r1, r0]
	cmp r0, r6
	bne _020717A8
	mov r0, #0x1
	pop {r4-r7}
	bx lr
_020717A8:
	mov r0, #0x6e
	lsl r0, r0, #0x4
	ldrh r0, [r1, r0]
	cmp r0, #0x0
	beq _020717C2
	mov r1, #0x6e
	lsl r1, r1, #0x4
	ldrh r1, [r2, r1]
	cmp r0, r1
	bne _020717C2
	mov r0, #0x2
	pop {r4-r7}
	bx lr
_020717C2:
	add r0, r3, #0x1
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	cmp r3, #0x6
	blo _02071774
_020717CC:
	mov r0, r12
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r12, r0
	cmp r0, #0x5
	blo _02071758
_020717DA:
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	.balign 4
_020717E0: .word 0x000005A4
_020717E4: .word 0x000006D8

	thumb_func_start FUN_020717E8
FUN_020717E8: ; 0x020717E8
	push {r3-r7, lr}
	ldr r0, [r0, #0x0]
	add r5, r1, #0x0
	add r4, r2, #0x0
	mov r1, #0x4
	bl FUN_0201886C
	lsl r1, r5, #0x1
	mov r3, #0x19
	add r5, r4, #0x0
	mul r5, r3
	ldr r3, _02071844 ; =0x00001005
	mov r2, #0x0
	add r3, r5, r3
	lsl r3, r3, #0x10
	lsr r4, r3, #0x10
	ldr r3, _02071848 ; =UNK_020F944C
	ldrb r3, [r3, r1]
	lsl r3, r3, #0x1
	add r0, r0, r3
	mov r12, r0
	ldr r0, _0207184C ; =UNK_020F944D
	ldrb r7, [r0, r1]
_02071816:
	lsl r0, r2, #0x2
	add r5, r2, r0
	add r0, r7, r2
	lsl r1, r0, #0x6
	mov r0, r12
	mov r3, #0x0
	add r6, r0, r1
_02071824:
	add r0, r3, r5
	add r1, r4, r0
	lsl r0, r3, #0x1
	strh r1, [r6, r0]
	add r0, r3, #0x1
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	cmp r3, #0x5
	blo _02071824
	add r0, r2, #0x1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, #0x5
	blo _02071816
	pop {r3-r7, pc}
	nop
_02071844: .word 0x00001005
_02071848: .word UNK_020F944C
_0207184C: .word UNK_020F944D

	thumb_func_start FUN_02071850
FUN_02071850: ; 0x02071850
	lsl r3, r0, #0x1
	ldr r0, _02071868 ; =UNK_020F944C
	ldrb r0, [r0, r3]
	lsl r0, r0, #0x3
	add r0, #0x14
	strh r0, [r1, #0x0]
	ldr r0, _0207186C ; =UNK_020F944D
	ldrb r0, [r0, r3]
	lsl r0, r0, #0x3
	add r0, #0x14
	strh r0, [r2, #0x0]
	bx lr
	.balign 4
_02071868: .word UNK_020F944C
_0207186C: .word UNK_020F944D

	thumb_func_start FUN_02071870
FUN_02071870: ; 0x02071870
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl FUN_0207248C
	cmp r0, #0x0
	bne _02071886
	mov r0, #0x0
	add sp, #0x8
	mvn r0, r0
	pop {r3-r5, pc}
_02071886:
	ldr r0, _020718C0 ; =UNK_020F94B8
	bl FUN_02020988
	add r4, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	beq _020718BA
	ldr r1, _020718C4 ; =0x0000FFFE
	add r0, sp, #0x4
	strh r1, [r0, #0x0]
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	ldr r3, _020718C8 ; =UNK_021C48F8
	ldr r0, [r5, #0x0]
	ldrh r2, [r3, #0x1c]
	ldrh r3, [r3, #0x1e]
	mov r1, #0x4
	bl FUN_0201AFBC
	cmp r0, #0x0
	bne _020718BA
	mov r0, #0x0
	add sp, #0x8
	mvn r0, r0
	pop {r3-r5, pc}
_020718BA:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_020718C0: .word UNK_020F94B8
_020718C4: .word 0x0000FFFE
_020718C8: .word UNK_021C48F8

	thumb_func_start FUN_020718CC
FUN_020718CC: ; 0x020718CC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0207193C ; =0x000006FC
	add r4, r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_02001C78
	add r2, r0, #0x0
	mov r0, #0x1
	mvn r0, r0
	cmp r2, r0
	beq _020718EC
	add r0, r0, #0x1
	cmp r2, r0
	beq _02071938
	b _02071932
_020718EC:
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r5, #0x0
	bl FUN_02073DB4
	ldr r0, _02071940 ; =0x000005A4
	ldr r0, [r5, r0]
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	beq _0207190E
	cmp r0, #0x11
	bne _0207191A
_0207190E:
	add r0, r5, #0x0
	mov r1, #0x22
	mov r2, #0x1
	bl FUN_020731C0
	b _02071924
_0207191A:
	add r0, r5, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731C0
_02071924:
	ldr r0, _02071944 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_0200C664
	mov r0, #0x1
	pop {r3-r5, pc}
_02071932:
	add r0, r5, #0x0
	add r1, r4, #0x0
	blx r2
_02071938:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0207193C: .word 0x000006FC
_02071940: .word 0x000005A4
_02071944: .word 0x000005C8

	thumb_func_start FUN_02071948
FUN_02071948: ; 0x02071948
	ldr r2, _0207196C ; =UNK_020F9544
	mov r3, #0x0
_0207194C:
	lsl r1, r3, #0x1
	ldrh r1, [r2, r1]
	cmp r0, r1
	bne _0207195C
	add r3, #0xf
	lsl r0, r3, #0x18
	lsr r0, r0, #0x18
	bx lr
_0207195C:
	add r1, r3, #0x1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0xf
	blo _0207194C
	mov r0, #0xff
	bx lr
	nop
_0207196C: .word UNK_020F9544

	thumb_func_start FUN_02071970
FUN_02071970: ; 0x02071970
	push {r4-r6, lr}
	sub sp, #0x8
	ldr r1, _02071C18 ; =0x00000B2A
	add r4, r0, #0x0
	ldrh r2, [r4, r1]
	cmp r2, #0x4
	bhi _02071A7A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0207198A: ; jump table (using 16-bit offset)
	.short _02071994 - _0207198A - 2; case 0
	.short _02071AD2 - _0207198A - 2; case 1
	.short _02071B0C - _0207198A - 2; case 2
	.short _02071B34 - _0207198A - 2; case 3
	.short _02071BE0 - _0207198A - 2; case 4
_02071994:
	ldr r2, _02071C1C ; =gUnknown21C48B8
	ldr r3, [r2, #0x48]
	mov r2, #0x1
	tst r2, r3
	beq _02071A26
	sub r1, r1, #0x5
	ldrb r1, [r4, r1]
	cmp r1, #0x6
	blo _020719B8
	ldr r0, _02071C20 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_02074538
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_020719B8:
	bl FUN_02071C48
	cmp r0, #0x0
	beq _020719CA
	cmp r0, #0x1
	beq _02071A08
	cmp r0, #0x2
	beq _02071A1A
	b _02071A26
_020719CA:
	ldr r0, _02071C24 ; =0x000005EC
	bl FUN_020054C8
	ldr r0, _02071C28 ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C664
	ldr r0, _02071C2C ; =0x00000B25
	mov r1, #0x2c
	ldrb r2, [r4, r0]
	mul r1, r2
	add r3, r4, r1
	ldr r1, _02071C30 ; =0x00000708
	ldrh r2, [r3, r1]
	sub r1, r1, #0x2
	ldrh r1, [r3, r1]
	sub r2, r2, r1
	add r1, r0, #0x3
	ldrh r1, [r4, r1]
	cmp r2, r1
	bge _020719FA
	add r0, r0, #0x3
	strh r2, [r4, r0]
_020719FA:
	ldr r0, _02071C18 ; =0x00000B2A
	mov r1, #0x2
	strh r1, [r4, r0]
	mov r1, #0x0
	add r0, r0, #0x2
	strh r1, [r4, r0]
	b _02071A26
_02071A08:
	ldr r0, _02071C20 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _02071C18 ; =0x00000B2A
	mov r1, #0x1
	strh r1, [r4, r0]
	add sp, #0x8
	mov r0, #0x14
	pop {r4-r6, pc}
_02071A1A:
	ldr r0, _02071C34 ; =0x000005F2
	bl FUN_020054C8
	add sp, #0x8
	mov r0, #0x1a
	pop {r4-r6, pc}
_02071A26:
	ldr r0, _02071C1C ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x2
	tst r0, r1
	beq _02071A42
	ldr r0, _02071C20 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_02074538
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02071A42:
	add r0, r4, #0x0
	bl FUN_02070B04
	cmp r0, #0x2
	bne _02071A7A
	ldr r0, _02071C2C ; =0x00000B25
	ldrb r1, [r4, r0]
	sub r0, r0, #0x2
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1a
	cmp r1, r0
	bne _02071A68
	add r0, r4, #0x0
	bl FUN_02074538
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02071A68:
	add r0, r4, #0x0
	bl FUN_02071C48
	cmp r0, #0x0
	beq _02071A7C
	cmp r0, #0x1
	beq _02071ABA
	cmp r0, #0x2
	beq _02071AC6
_02071A7A:
	b _02071C12
_02071A7C:
	ldr r0, _02071C24 ; =0x000005EC
	bl FUN_020054C8
	ldr r0, _02071C28 ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C664
	ldr r0, _02071C2C ; =0x00000B25
	mov r1, #0x2c
	ldrb r2, [r4, r0]
	mul r1, r2
	add r3, r4, r1
	ldr r1, _02071C30 ; =0x00000708
	ldrh r2, [r3, r1]
	sub r1, r1, #0x2
	ldrh r1, [r3, r1]
	sub r2, r2, r1
	add r1, r0, #0x3
	ldrh r1, [r4, r1]
	cmp r2, r1
	bge _02071AAC
	add r0, r0, #0x3
	strh r2, [r4, r0]
_02071AAC:
	ldr r0, _02071C18 ; =0x00000B2A
	mov r1, #0x2
	strh r1, [r4, r0]
	mov r1, #0x0
	add r0, r0, #0x2
	strh r1, [r4, r0]
	b _02071C12
_02071ABA:
	ldr r0, _02071C18 ; =0x00000B2A
	mov r1, #0x1
	strh r1, [r4, r0]
	add sp, #0x8
	mov r0, #0x14
	pop {r4-r6, pc}
_02071AC6:
	ldr r0, _02071C34 ; =0x000005F2
	bl FUN_020054C8
	add sp, #0x8
	mov r0, #0x1a
	pop {r4-r6, pc}
_02071AD2:
	ldr r0, _02071C1C ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	bne _02071ADE
	b _02071C12
_02071ADE:
	ldr r0, _02071C20 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	ldr r0, _02071C28 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C664
	add r0, r4, #0x0
	mov r1, #0x24
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _02071C18 ; =0x00000B2A
	mov r1, #0x0
	strh r1, [r4, r0]
	b _02071C12
_02071B0C:
	sub r1, r1, #0x7
	ldrb r1, [r4, r1]
	mov r2, #0x0
	mvn r2, r2
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1a
	bl FUN_02071CB4
	cmp r0, #0x1
	bne _02071C12
	ldr r0, _02071C24 ; =0x000005EC
	bl FUN_020054C8
	ldr r0, _02071C18 ; =0x00000B2A
	mov r1, #0x3
	strh r1, [r4, r0]
	mov r1, #0x0
	add r0, r0, #0x2
	strh r1, [r4, r0]
	b _02071C12
_02071B34:
	sub r1, r1, #0x5
	ldrb r1, [r4, r1]
	mov r2, #0x1
	bl FUN_02071CB4
	cmp r0, #0x1
	bne _02071C12
	ldr r0, _02071C38 ; =0x000005A4
	ldr r1, _02071C2C ; =0x00000B25
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r6, r0, #0x0
	ldr r0, _02071C3C ; =0x0000069C
	mov r1, #0x40
	ldr r0, [r4, r0]
	bl NewString_ReadMsgData
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r1, #0x1
	mov r0, #0x6a
	ldr r2, _02071C40 ; =0x00000B2C
	str r1, [sp, #0x4]
	lsl r0, r0, #0x4
	ldrh r2, [r4, r2]
	ldr r0, [r4, r0]
	mov r3, #0x3
	bl FUN_0200AD38
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl StringExpandPlaceholders
	add r0, r5, #0x0
	bl String_dtor
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02071C44 ; =0x00000B2E
	mov r1, #0x0
	ldrh r0, [r4, r0]
	mov r2, #0xc
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0202914C
	add r1, r0, #0x0
	ldr r0, _02071C38 ; =0x000005A4
	mov r2, #0x1
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x1c]
	add r0, #0x98
	ldr r0, [r0, #0x0]
	bl FUN_02028AD4
	ldr r0, _02071C18 ; =0x00000B2A
	mov r1, #0x4
	strh r1, [r4, r0]
	mov r1, #0x1a
	sub r0, #0x8
	strb r1, [r4, r0]
	add sp, #0x8
	mov r0, #0x14
	pop {r4-r6, pc}
_02071BE0:
	ldr r0, _02071C1C ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _02071C12
	ldr r0, _02071C20 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	ldr r0, _02071C28 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C664
	add r0, r4, #0x0
	bl FUN_02074538
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02071C12:
	mov r0, #0x1a
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_02071C18: .word 0x00000B2A
_02071C1C: .word gUnknown21C48B8
_02071C20: .word 0x000005DC
_02071C24: .word 0x000005EC
_02071C28: .word 0x000005C8
_02071C2C: .word 0x00000B25
_02071C30: .word 0x00000708
_02071C34: .word 0x000005F2
_02071C38: .word 0x000005A4
_02071C3C: .word 0x0000069C
_02071C40: .word 0x00000B2C
_02071C44: .word 0x00000B2E

	thumb_func_start FUN_02071C48
FUN_02071C48: ; 0x02071C48
	push {r3-r5, lr}
	ldr r2, _02071CA8 ; =0x00000B25
	add r4, r0, #0x0
	ldrb r1, [r4, r2]
	mov r0, #0x2c
	mov r3, #0x71
	mul r0, r1
	add r0, r4, r0
	lsl r3, r3, #0x4
	ldrb r5, [r0, r3]
	cmp r5, #0x0
	beq _02071C64
	mov r0, #0x2
	pop {r3-r5, pc}
_02071C64:
	sub r2, r2, #0x2
	ldrb r2, [r4, r2]
	lsl r2, r2, #0x1a
	lsr r2, r2, #0x1a
	cmp r1, r2
	beq _02071C82
	add r1, r3, #0x0
	sub r1, #0xa
	ldrh r1, [r0, r1]
	cmp r1, #0x0
	beq _02071C82
	sub r3, #0x8
	ldrh r0, [r0, r3]
	cmp r1, r0
	bne _02071CA4
_02071C82:
	ldr r0, _02071CAC ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C664
	add r0, r4, #0x0
	mov r1, #0x83
	mov r2, #0x1
	bl FUN_020731E8
	ldr r1, _02071CB0 ; =0x00000B2A
	mov r0, #0x1
	strh r0, [r4, r1]
	mov r2, #0x1a
	sub r1, #0x8
	strb r2, [r4, r1]
	pop {r3-r5, pc}
_02071CA4:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02071CA8: .word 0x00000B25
_02071CAC: .word 0x000005C8
_02071CB0: .word 0x00000B2A

	thumb_func_start FUN_02071CB4
FUN_02071CB4: ; 0x02071CB4
	push {r3-r7, lr}
	add r6, r1, #0x0
	mov r3, #0x2c
	add r4, r6, #0x0
	mul r4, r3
	ldr r3, _02071D34 ; =0x00000706
	add r5, r0, #0x0
	add r7, r5, r3
	lsl r2, r2, #0x10
	ldrh r3, [r7, r4]
	lsr r2, r2, #0x10
	add r2, r3, r2
	ldr r3, _02071D38 ; =0x00000B2C
	strh r2, [r7, r4]
	ldrh r2, [r5, r3]
	add r2, r2, #0x1
	strh r2, [r5, r3]
	bl FUN_02072BBC
	lsl r1, r6, #0x2
	add r1, r6, r1
	add r1, r1, #0x3
	add r0, r5, #0x4
	lsl r1, r1, #0x4
	add r0, r0, r1
	mov r1, #0x0
	bl FUN_02019620
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02072B7C
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02072C28
	ldr r1, _02071D3C ; =0x00000B28
	ldrh r0, [r5, r1]
	add r1, r1, #0x4
	ldrh r1, [r5, r1]
	cmp r0, r1
	beq _02071D14
	ldr r1, _02071D40 ; =0x00000708
	add r2, r5, r4
	ldrh r0, [r7, r4]
	ldrh r1, [r2, r1]
	cmp r0, r1
	bne _02071D30
_02071D14:
	ldr r0, _02071D44 ; =0x000005A4
	add r1, r6, #0x0
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	ldrh r1, [r7, r4]
	add r2, sp, #0x0
	str r1, [sp, #0x0]
	mov r1, #0xa2
	bl SetMonData
	mov r0, #0x1
	pop {r3-r7, pc}
_02071D30:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02071D34: .word 0x00000706
_02071D38: .word 0x00000B2C
_02071D3C: .word 0x00000B28
_02071D40: .word 0x00000708
_02071D44: .word 0x000005A4

	thumb_func_start FUN_02071D48
FUN_02071D48: ; 0x02071D48
	push {r4, lr}
	ldr r1, _02071DE0 ; =gUnknown21C48B8
	add r4, r0, #0x0
	ldr r2, [r1, #0x48]
	mov r1, #0x1
	tst r1, r2
	beq _02071D96
	ldr r0, _02071DE4 ; =0x00000B25
	ldrb r1, [r4, r0]
	cmp r1, #0x7
	bne _02071D72
	sub r0, r0, #0x2
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _02071D92
	ldr r0, _02071DE8 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x3
	pop {r4, pc}
_02071D72:
	mov r0, #0x2c
	mul r0, r1
	add r1, r4, r0
	mov r0, #0x71
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02071D8C
	ldr r0, _02071DE8 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x0
	pop {r4, pc}
_02071D8C:
	ldr r0, _02071DEC ; =0x000005F2
	bl FUN_020054C8
_02071D92:
	mov r0, #0x5
	pop {r4, pc}
_02071D96:
	mov r1, #0x2
	tst r1, r2
	beq _02071DBA
	ldr r0, _02071DF0 ; =0x00000B23
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _02071DB6
	ldr r0, _02071DE8 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _02071DE4 ; =0x00000B25
	mov r1, #0x7
	strb r1, [r4, r0]
	mov r0, #0x3
	pop {r4, pc}
_02071DB6:
	mov r0, #0x5
	pop {r4, pc}
_02071DBA:
	bl FUN_02070B04
	cmp r0, #0x2
	bne _02071DDE
	ldr r1, _02071DE4 ; =0x00000B25
	ldrb r2, [r4, r1]
	mov r1, #0x2c
	mul r1, r2
	add r2, r4, r1
	mov r1, #0x71
	lsl r1, r1, #0x4
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _02071DDE
	ldr r0, _02071DEC ; =0x000005F2
	bl FUN_020054C8
	mov r0, #0x5
_02071DDE:
	pop {r4, pc}
	.balign 4
_02071DE0: .word gUnknown21C48B8
_02071DE4: .word 0x00000B25
_02071DE8: .word 0x000005DC
_02071DEC: .word 0x000005F2
_02071DF0: .word 0x00000B23

	thumb_func_start FUN_02071DF4
FUN_02071DF4: ; 0x02071DF4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02071F1C ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r5, r0]
	mov r2, #0xc
	ldrh r0, [r0, #0x24]
	bl LoadItemDataOrGfx
	mov r1, #0x22
	add r4, r0, #0x0
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0x0
	bne _02071E1E
	add r0, r4, #0x0
	mov r1, #0x23
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0x0
	beq _02071E30
_02071E1E:
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0207703C
	mov r0, #0x6
	pop {r3-r5, pc}
_02071E30:
	add r0, r4, #0x0
	mov r1, #0x24
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0x0
	beq _02071E5A
	add r0, r4, #0x0
	mov r1, #0x25
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0x0
	bne _02071E5A
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0207703C
	mov r0, #0x6
	pop {r3-r5, pc}
_02071E5A:
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r0, _02071F1C ; =0x000005A4
	ldr r2, _02071F20 ; =0x00000B25
	ldr r1, [r5, r0]
	mov r0, #0xc
	str r0, [sp, #0x0]
	ldr r0, [r1, #0x0]
	ldrh r1, [r1, #0x24]
	ldrb r2, [r5, r2]
	mov r3, #0x0
	bl FUN_020847F8
	cmp r0, #0x1
	bne _02071F02
	ldr r0, _02071F1C ; =0x000005A4
	mov r2, #0x1
	ldr r1, [r5, r0]
	mov r3, #0xc
	ldr r0, [r1, #0x4]
	ldrh r1, [r1, #0x24]
	bl FUN_0206EDD4
	add r0, r4, #0x0
	mov r1, #0x1a
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0x0
	ldr r0, _02071F1C ; =0x000005A4
	beq _02071ECC
	ldr r1, _02071F20 ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r1, r0, #0x0
	ldr r0, _02071F1C ; =0x000005A4
	mov r2, #0x3
	ldr r3, [r5, r0]
	add r0, r3, #0x0
	add r0, #0x3c
	str r0, [sp, #0x0]
	ldrh r3, [r3, #0x24]
	mov r0, #0x0
	bl GetMonEvolution
	ldr r1, _02071F1C ; =0x000005A4
	ldr r2, [r5, r1]
	strh r0, [r2, #0x38]
	ldr r0, [r5, r1]
	mov r2, #0x8
	add r0, #0x23
	strb r2, [r0, #0x0]
	mov r0, #0x1b
	pop {r3-r5, pc}
_02071ECC:
	ldr r0, [r5, r0]
	ldrh r0, [r0, #0x24]
	bl ItemIsBitter
	cmp r0, #0x1
	bne _02071EFA
	ldr r0, _02071F1C ; =0x000005A4
	ldr r1, [r5, r0]
	ldr r0, [r1, #0x10]
	cmp r0, #0x0
	beq _02071EFA
	ldr r0, [r1, #0x0]
	ldr r1, _02071F20 ; =0x00000B25
	ldrb r1, [r5, r1]
	bl GetPartyMonByIndex
	add r1, r0, #0x0
	ldr r0, _02071F1C ; =0x000005A4
	ldr r2, [r5, r0]
	ldr r0, [r2, #0x10]
	ldrh r2, [r2, #0x24]
	bl FUN_02061618
_02071EFA:
	add r0, r5, #0x0
	bl FUN_02075C54
	b _02071F18
_02071F02:
	add r0, r5, #0x0
	mov r1, #0x69
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02071F20 ; =0x00000B25
	mov r1, #0x7
	strb r1, [r5, r0]
	ldr r1, _02071F24 ; =FUN_02075CE4
	sub r0, #0x11
	str r1, [r5, r0]
_02071F18:
	mov r0, #0x5
	pop {r3-r5, pc}
	.balign 4
_02071F1C: .word 0x000005A4
_02071F20: .word 0x00000B25
_02071F24: .word FUN_02075CE4

	thumb_func_start FUN_02071F28
FUN_02071F28: ; 0x02071F28
	push {r3, lr}
	ldr r1, _02071F50 ; =0x00000B25
	ldrb r2, [r0, r1]
	mov r1, #0x2c
	mul r1, r2
	add r1, r0, r1
	ldr r0, _02071F54 ; =0x0000070C
	ldrh r0, [r1, r0]
	cmp r0, #0x0
	bne _02071F40
	mov r0, #0x0
	pop {r3, pc}
_02071F40:
	bl ItemIdIsMail
	cmp r0, #0x1
	bne _02071F4C
	mov r0, #0x2
	pop {r3, pc}
_02071F4C:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_02071F50: .word 0x00000B25
_02071F54: .word 0x0000070C

	thumb_func_start FUN_02071F58
FUN_02071F58: ; 0x02071F58
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _02072074 ; =0x000005A4
	ldr r1, _02072078 ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r6, r0, #0x0
	mov r7, #0x89
	add r0, r5, #0x0
	lsl r7, r7, #0x2
	bl FUN_02071F28
	cmp r0, #0x0
	beq _02071F84
	cmp r0, #0x1
	beq _02071FF2
	cmp r0, #0x2
	beq _02072044
	b _02072054
_02071F84:
	ldr r0, _02072074 ; =0x000005A4
	ldr r0, [r5, r0]
	ldrh r0, [r0, #0x24]
	bl ItemIdIsMail
	cmp r0, #0x1
	bne _02071FA0
	ldr r0, _02072074 ; =0x000005A4
	mov r1, #0x6
	ldr r0, [r5, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	pop {r3-r7, pc}
_02071FA0:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02072080
	ldr r2, _0207207C ; =0x0000069C
	mov r1, #0x76
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	add r0, r6, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	mov r2, #0x6a
	lsl r2, r2, #0x4
	ldr r0, [r5, r2]
	sub r2, #0xfc
	ldr r2, [r5, r2]
	mov r1, #0x1
	ldrh r2, [r2, #0x24]
	bl FUN_0200AE38
	mov r2, #0x6a
	lsl r2, r2, #0x4
	add r1, r2, #0x4
	ldr r0, [r5, r2]
	add r2, #0x8
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	mov r4, #0xb
	b _02072054
_02071FF2:
	ldr r2, _0207207C ; =0x0000069C
	mov r1, #0x4e
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	add r0, r6, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	ldr r2, _02072078 ; =0x00000B25
	mov r3, #0x6a
	ldrb r4, [r5, r2]
	mov r2, #0x2c
	lsl r3, r3, #0x4
	mul r2, r4
	ldr r0, [r5, r3]
	add r2, r5, r2
	add r3, #0x6c
	ldrh r2, [r2, r3]
	mov r1, #0x1
	bl FUN_0200AE70
	mov r2, #0x6a
	lsl r2, r2, #0x4
	add r1, r2, #0x4
	ldr r0, [r5, r2]
	add r2, #0x8
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	mov r4, #0x9
	b _02072054
_02072044:
	ldr r2, _0207207C ; =0x0000069C
	mov r1, #0x4d
	ldr r0, [r5, r2]
	add r2, #0x8
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	mov r4, #0xb
_02072054:
	add r0, r5, r7
	mov r1, #0x1
	mov r2, #0xa
	mov r3, #0xf
	bl FUN_0200D0BC
	add r0, r5, r7
	mov r1, #0xf
	bl FUN_02019620
	add r0, r5, #0x0
	bl FUN_0207322C
	add r0, r4, #0x0
	pop {r3-r7, pc}
	nop
_02072074: .word 0x000005A4
_02072078: .word 0x00000B25
_0207207C: .word 0x0000069C

	thumb_func_start FUN_02072080
FUN_02072080: ; 0x02072080
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, _020720D4 ; =0x000005A4
	add r5, r1, #0x0
	ldr r1, [r4, r0]
	mov r2, #0x1
	ldrh r1, [r1, #0x24]
	mov r3, #0xc
	str r1, [sp, #0x0]
	ldr r1, [r4, r0]
	ldr r0, [r1, #0x4]
	ldrh r1, [r1, #0x24]
	bl FUN_0206EDD4
	add r0, r5, #0x0
	mov r1, #0x6
	add r2, sp, #0x0
	bl SetMonData
	add r0, r5, #0x0
	bl FUN_02069EC4
	ldr r1, _020720D8 ; =0x00000B25
	ldr r0, _020720D4 ; =0x000005A4
	ldrb r3, [r4, r1]
	ldr r0, [r4, r0]
	mov r2, #0x2c
	add r5, r3, #0x0
	mul r5, r2
	ldrh r0, [r0, #0x24]
	ldr r3, _020720DC ; =0x0000070C
	add r5, r4, r5
	strh r0, [r5, r3]
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	mul r2, r1
	add r2, r4, r2
	ldrh r2, [r2, r3]
	bl FUN_02073A78
	pop {r3-r5, pc}
	nop
_020720D4: .word 0x000005A4
_020720D8: .word 0x00000B25
_020720DC: .word 0x0000070C

	thumb_func_start FUN_020720E0
FUN_020720E0: ; 0x020720E0
	push {r0-r3}
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, _02072134 ; =0x000005A4
	add r5, r1, #0x0
	ldr r0, [r4, r0]
	lsl r1, r2, #0x10
	ldr r0, [r0, #0x4]
	lsr r1, r1, #0x10
	mov r2, #0x1
	mov r3, #0xc
	bl FUN_0206ED38
	add r0, r5, #0x0
	mov r1, #0x6
	add r2, sp, #0x1c
	bl SetMonData
	add r0, r5, #0x0
	bl FUN_02069EC4
	ldr r1, _02072138 ; =0x00000B25
	mov r2, #0x2c
	ldrb r3, [r4, r1]
	ldr r0, [sp, #0x1c]
	add r5, r3, #0x0
	mul r5, r2
	ldr r3, _0207213C ; =0x0000070C
	add r5, r4, r5
	strh r0, [r5, r3]
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	mul r2, r1
	add r2, r4, r2
	ldrh r2, [r2, r3]
	bl FUN_02073A78
	pop {r3-r5}
	pop {r3}
	add sp, #0x10
	bx r3
	nop
_02072134: .word 0x000005A4
_02072138: .word 0x00000B25
_0207213C: .word 0x0000070C

	thumb_func_start FUN_02072140
FUN_02072140: ; 0x02072140
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02072168 ; =0x00000B24
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02072162
	ldr r0, _0207216C ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _02072162
	add r0, r4, #0x0
	bl FUN_020722B8
	pop {r4, pc}
_02072162:
	mov r0, #0xb
	pop {r4, pc}
	nop
_02072168: .word 0x00000B24
_0207216C: .word gUnknown21C48B8

	thumb_func_start FUN_02072170
FUN_02072170: ; 0x02072170
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02072190 ; =0x00000B24
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _0207218A
	add r0, r4, #0x0
	bl FUN_020732CC
	mov r0, #0xa
	pop {r4, pc}
_0207218A:
	mov r0, #0x9
	pop {r4, pc}
	nop
_02072190: .word 0x00000B24

	thumb_func_start FUN_02072194
FUN_02072194: ; 0x02072194
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _020722A4 ; =0x000006FC
	mov r1, #0xc
	ldr r0, [r5, r0]
	bl FUN_020021AC
	cmp r0, #0x0
	beq _020721B0
	mov r1, #0x1
	mvn r1, r1
	cmp r0, r1
	beq _02072298
	b _020722A0
_020721B0:
	ldr r0, _020722A8 ; =0x000005A4
	ldr r1, _020722AC ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r7, r0, #0x0
	ldr r0, _020722A8 ; =0x000005A4
	ldr r0, [r5, r0]
	ldrh r6, [r0, #0x24]
	ldr r0, _020722AC ; =0x00000B25
	ldrb r1, [r5, r0]
	mov r0, #0x2c
	mul r0, r1
	add r1, r5, r0
	ldr r0, _020722B0 ; =0x0000070C
	ldrh r4, [r1, r0]
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02072080
	ldr r0, _020722A8 ; =0x000005A4
	add r1, r4, #0x0
	ldr r0, [r5, r0]
	mov r2, #0x1
	ldr r0, [r0, #0x4]
	mov r3, #0xc
	bl FUN_0206ED38
	cmp r0, #0x0
	bne _0207220C
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	add r3, r4, #0x0
	bl FUN_020720E0
	ldr r2, _020722B4 ; =0x0000069C
	mov r1, #0x53
	ldr r0, [r5, r2]
	add r2, #0x8
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	b _02072282
_0207220C:
	ldr r0, _020722A8 ; =0x000005A4
	ldr r0, [r5, r0]
	ldrh r0, [r0, #0x24]
	bl ItemIdIsMail
	cmp r0, #0x1
	bne _02072246
	ldr r0, _020722A8 ; =0x000005A4
	lsl r1, r4, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0x10
	ldr r0, [r0, #0x4]
	mov r2, #0x1
	mov r3, #0xc
	bl FUN_0206EDD4
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	add r3, r4, #0x0
	bl FUN_020720E0
	ldr r0, _020722A8 ; =0x000005A4
	mov r1, #0x6
	ldr r0, [r5, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	pop {r3-r7, pc}
_02072246:
	ldr r2, _020722B4 ; =0x0000069C
	mov r1, #0x54
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x1
	add r2, r4, #0x0
	bl FUN_0200AE38
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x2
	add r2, r6, #0x0
	bl FUN_0200AE38
	mov r2, #0x6a
	lsl r2, r2, #0x4
	add r1, r2, #0x4
	ldr r0, [r5, r2]
	add r2, #0x8
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
_02072282:
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0xf
	bl FUN_02019620
	add r0, r5, #0x0
	bl FUN_0207322C
	mov r0, #0xb
	pop {r3-r7, pc}
_02072298:
	add r0, r5, #0x0
	bl FUN_020722B8
	pop {r3-r7, pc}
_020722A0:
	mov r0, #0xa
	pop {r3-r7, pc}
	.balign 4
_020722A4: .word 0x000006FC
_020722A8: .word 0x000005A4
_020722AC: .word 0x00000B25
_020722B0: .word 0x0000070C
_020722B4: .word 0x0000069C

	thumb_func_start FUN_020722B8
FUN_020722B8: ; 0x020722B8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02072304 ; =0x000005A4
	ldr r1, [r4, r0]
	add r0, r1, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0xa
	bne _020722F8
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r4, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _02072308 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C664
	ldr r0, _02072304 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x20
	strb r1, [r0, #0x0]
	mov r0, #0x1
	pop {r4, pc}
_020722F8:
	mov r0, #0xa
	add r1, #0x23
	strb r0, [r1, #0x0]
	mov r0, #0x1b
	pop {r4, pc}
	nop
_02072304: .word 0x000005A4
_02072308: .word 0x000005C8

	thumb_func_start FUN_0207230C
FUN_0207230C: ; 0x0207230C
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _02072410 ; =0x000005A4
	ldr r1, _02072414 ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r7, r0, #0x0
	ldr r0, _02072410 ; =0x000005A4
	ldr r0, [r5, r0]
	ldrh r6, [r0, #0x24]
	ldr r0, _02072414 ; =0x00000B25
	ldrb r1, [r5, r0]
	mov r0, #0x2c
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02072418 ; =0x0000070C
	ldrh r4, [r1, r0]
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02072080
	cmp r4, #0x0
	bne _02072388
	ldr r2, _0207241C ; =0x0000069C
	mov r1, #0x76
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	add r0, r7, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	mov r2, #0x6a
	lsl r2, r2, #0x4
	ldr r0, [r5, r2]
	sub r2, #0xfc
	ldr r2, [r5, r2]
	mov r1, #0x1
	ldrh r2, [r2, #0x24]
	bl FUN_0200AE38
	mov r2, #0x6a
	lsl r2, r2, #0x4
	add r1, r2, #0x4
	ldr r0, [r5, r2]
	add r2, #0x8
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	b _020723D6
_02072388:
	ldr r0, _02072410 ; =0x000005A4
	lsl r1, r4, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0x10
	ldr r0, [r0, #0x4]
	mov r2, #0x1
	mov r3, #0xc
	bl FUN_0206ED38
	ldr r2, _0207241C ; =0x0000069C
	mov r1, #0x54
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x1
	add r2, r4, #0x0
	bl FUN_0200AE38
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x2
	add r2, r6, #0x0
	bl FUN_0200AE38
	mov r2, #0x6a
	lsl r2, r2, #0x4
	add r1, r2, #0x4
	ldr r0, [r5, r2]
	add r2, #0x8
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
_020723D6:
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	mov r2, #0xa
	mov r3, #0xf
	bl FUN_0200D0BC
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0xf
	bl FUN_02019620
	add r0, r5, #0x0
	bl FUN_0207322C
	ldr r0, _02072410 ; =0x000005A4
	ldr r1, [r5, r0]
	add r0, r1, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0xc
	bne _0207240C
	mov r0, #0xa
	add r1, #0x20
	strb r0, [r1, #0x0]
_0207240C:
	mov r0, #0xb
	pop {r3-r7, pc}
	.balign 4
_02072410: .word 0x000005A4
_02072414: .word 0x00000B25
_02072418: .word 0x0000070C
_0207241C: .word 0x0000069C

	thumb_func_start FUN_02072420
FUN_02072420: ; 0x02072420
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02072470 ; =0x00000B25
	ldrb r1, [r4, r0]
	mov r0, #0x2c
	mul r0, r1
	add r1, r4, r0
	ldr r0, _02072474 ; =0x00000712
	ldrh r0, [r1, r0]
	cmp r0, #0x0
	bne _02072444
	ldr r0, _02072478 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	pop {r4, pc}
_02072444:
	ldr r0, _0207247C ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C664
	add r0, r4, #0x0
	mov r1, #0xc3
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02072480 ; =FUN_02074428
	ldr r1, _02072484 ; =0x00000B18
	ldr r2, _02072488 ; =FUN_02074454
	str r0, [r4, r1]
	add r0, r1, #0x4
	str r2, [r4, r0]
	mov r0, #0x16
	add r1, #0xa
	strb r0, [r4, r1]
	mov r0, #0x14
	pop {r4, pc}
	nop
_02072470: .word 0x00000B25
_02072474: .word 0x00000712
_02072478: .word 0x000005A4
_0207247C: .word 0x000005C8
_02072480: .word FUN_02074428
_02072484: .word 0x00000B18
_02072488: .word FUN_02074454

	thumb_func_start FUN_0207248C
FUN_0207248C: ; 0x0207248C
	ldr r1, _020724C0 ; =0x000005A4
	ldr r0, [r0, r1]
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x5
	beq _020724B8
	cmp r0, #0x6
	beq _020724B8
	cmp r0, #0x7
	beq _020724B8
	cmp r0, #0x8
	beq _020724B8
	cmp r0, #0x9
	beq _020724B8
	cmp r0, #0xb
	beq _020724B8
	cmp r0, #0xe
	beq _020724B8
	cmp r0, #0x10
	beq _020724B8
	cmp r0, #0x14
	bne _020724BC
_020724B8:
	mov r0, #0x0
	bx lr
_020724BC:
	mov r0, #0x1
	bx lr
	.balign 4
_020724C0: .word 0x000005A4

	thumb_func_start FUN_020724C4
FUN_020724C4: ; 0x020724C4
	mov r0, #0x14
	bx lr

	thumb_func_start FUN_020724C8
FUN_020724C8: ; 0x020724C8
	mov r0, #0x15
	bx lr

	thumb_func_start FUN_020724CC
FUN_020724CC: ; 0x020724CC
	mov r0, #0x13
	bx lr

	thumb_func_start FUN_020724D0
FUN_020724D0: ; 0x020724D0
	mov r0, #0x12
	bx lr

	thumb_func_start FUN_020724D4
FUN_020724D4: ; 0x020724D4
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	mov r0, #0x14
	mov r1, #0x16
	add r2, r4, #0x0
	add r7, r3, #0x0
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0xc
	str r0, [sp, #0x8]
	bl FUN_020B0180
	ldr r0, [sp, #0xc]
	mov r4, #0x0
	str r0, [sp, #0x4]
	add r0, #0xc
	str r0, [sp, #0x4]
	str r0, [sp, #0x0]
_020724FE:
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x20
	bl memcpy
	add r1, r4, #0x6
	lsl r2, r1, #0x6
	ldr r1, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r1, r2
	mov r2, #0x20
	bl memcpy
	add r1, r4, #0x0
	add r1, #0xc
	lsl r2, r1, #0x6
	ldr r1, [sp, #0x4]
	add r0, r7, #0x0
	add r1, r1, r2
	mov r2, #0x20
	bl memcpy
	ldr r0, [sp, #0x0]
	add r4, r4, #0x1
	add r0, #0x40
	str r0, [sp, #0x0]
	add r5, #0x20
	add r6, #0x20
	add r7, #0x20
	cmp r4, #0x6
	blo _020724FE
	ldr r0, [sp, #0x8]
	bl FreeToHeap
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
