    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020F7430
UNK_020F7430: ; 0x020F7430
	.byte 0x09, 0x12, 0x12, 0x11, 0x23, 0x11

	.global UNK_020F7436
UNK_020F7436: ; 0x020F7436
	.byte 0x08, 0x02, 0x29, 0x02, 0x12, 0x03, 0x28, 0x10, 0x00, 0x00

	.text

	thumb_func_start FUN_0205F314
FUN_0205F314: ; 0x0205F314
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02046380
	mov r1, #0x1
	lsl r1, r1, #0xe
	cmp r5, r1
	blo _0205F32C
	lsl r1, r1, #0x1
	cmp r5, r1
	bls _0205F334
_0205F32C:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0205F334:
	cmp r0, #0x0
	bne _0205F33C
	mov r0, #0x0
	pop {r3-r5, pc}
_0205F33C:
	strh r4, [r0, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205F344
FUN_0205F344: ; 0x0205F344
	push {r3, lr}
	bl FUN_02046380
	cmp r0, #0x0
	bne _0205F352
	mov r0, #0x0
	pop {r3, pc}
_0205F352:
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205F358
FUN_0205F358: ; 0x0205F358
	ldr r3, _0205F360 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F364 ; =0x0000403F
	bx r3
	.balign 4
_0205F360: .word FUN_0205F314
_0205F364: .word 0x0000403F

	thumb_func_start FUN_0205F368
FUN_0205F368: ; 0x0205F368
	ldr r3, _0205F370 ; =FUN_0205F344
	ldr r1, _0205F374 ; =0x0000403F
	bx r3
	nop
_0205F370: .word FUN_0205F344
_0205F374: .word 0x0000403F

	thumb_func_start FUN_0205F378
FUN_0205F378: ; 0x0205F378
	ldr r3, _0205F380 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F384 ; =0x00004030
	bx r3
	.balign 4
_0205F380: .word FUN_0205F314
_0205F384: .word 0x00004030

	thumb_func_start FUN_0205F388
FUN_0205F388: ; 0x0205F388
	ldr r3, _0205F390 ; =FUN_0205F344
	ldr r1, _0205F394 ; =0x00004030
	bx r3
	nop
_0205F390: .word FUN_0205F344
_0205F394: .word 0x00004030

	thumb_func_start FUN_0205F398
FUN_0205F398: ; 0x0205F398
	push {r3, lr}
	ldr r1, _0205F3B8 ; =0x00004030
	bl FUN_0205F344
	ldr r2, _0205F3BC ; =0x00000183
	cmp r0, r2
	bne _0205F3AA
	add r2, r2, #0x3
	b _0205F3B2
_0205F3AA:
	add r1, r2, #0x3
	cmp r0, r1
	bne _0205F3B2
	add r2, r2, #0x6
_0205F3B2:
	add r0, r2, #0x0
	pop {r3, pc}
	nop
_0205F3B8: .word 0x00004030
_0205F3BC: .word 0x00000183

	thumb_func_start FUN_0205F3C0
FUN_0205F3C0: ; 0x0205F3C0
	push {r3, lr}
	ldr r1, _0205F3E0 ; =0x00004030
	bl FUN_0205F344
	ldr r2, _0205F3E4 ; =0x00000183
	cmp r0, r2
	bne _0205F3D2
	add r2, r2, #0x6
	b _0205F3DA
_0205F3D2:
	add r1, r2, #0x3
	cmp r0, r1
	beq _0205F3DA
	add r2, r2, #0x3
_0205F3DA:
	add r0, r2, #0x0
	pop {r3, pc}
	nop
_0205F3E0: .word 0x00004030
_0205F3E4: .word 0x00000183

	thumb_func_start FUN_0205F3E8
FUN_0205F3E8: ; 0x0205F3E8
	ldr r3, _0205F3F0 ; =FUN_0205F344
	ldr r1, _0205F3F4 ; =0x00004035
	bx r3
	nop
_0205F3F0: .word FUN_0205F344
_0205F3F4: .word 0x00004035

	thumb_func_start FUN_0205F3F8
FUN_0205F3F8: ; 0x0205F3F8
	ldr r3, _0205F400 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F404 ; =0x00004035
	bx r3
	.balign 4
_0205F400: .word FUN_0205F314
_0205F404: .word 0x00004035

	thumb_func_start FUN_0205F408
FUN_0205F408: ; 0x0205F408
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0205ED8C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0205F44C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205F41C
FUN_0205F41C: ; 0x0205F41C
	ldr r3, _0205F424 ; =FUN_0205F344
	ldr r1, _0205F428 ; =0x00004033
	bx r3
	nop
_0205F424: .word FUN_0205F344
_0205F428: .word 0x00004033

	thumb_func_start FUN_0205F42C
FUN_0205F42C: ; 0x0205F42C
	ldr r3, _0205F434 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F438 ; =0x00004033
	bx r3
	.balign 4
_0205F434: .word FUN_0205F314
_0205F438: .word 0x00004033

	thumb_func_start FUN_0205F43C
FUN_0205F43C: ; 0x0205F43C
	ldr r3, _0205F444 ; =FUN_0205F344
	ldr r1, _0205F448 ; =0x00004034
	bx r3
	nop
_0205F444: .word FUN_0205F344
_0205F448: .word 0x00004034

	thumb_func_start FUN_0205F44C
FUN_0205F44C: ; 0x0205F44C
	ldr r3, _0205F454 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F458 ; =0x00004034
	bx r3
	.balign 4
_0205F454: .word FUN_0205F314
_0205F458: .word 0x00004034

	thumb_func_start FUN_0205F45C
FUN_0205F45C: ; 0x0205F45C
	push {r4, lr}
	add r4, r0, #0x0
	bmi _0205F466
	cmp r4, #0x3
	blo _0205F46A
_0205F466:
	bl ErrorHandling
_0205F46A:
	ldr r0, _0205F474 ; =UNK_020F7430
	lsl r1, r4, #0x1
	ldrh r0, [r0, r1]
	pop {r4, pc}
	nop
_0205F474: .word UNK_020F7430

	thumb_func_start FUN_0205F478
FUN_0205F478: ; 0x0205F478
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F45C
	add r2, r0, #0x0
	ldr r1, _0205F49C ; =0x00004043
	lsl r2, r2, #0x10
	add r1, r4, r1
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl FUN_0205F314
	pop {r3-r5, pc}
	nop
_0205F49C: .word 0x00004043

	thumb_func_start FUN_0205F4A0
FUN_0205F4A0: ; 0x0205F4A0
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, _0205F4C4 ; =0x00004043
	add r1, r4, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0205F344
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F45C
	cmp r5, r0
	bne _0205F4C0
	mov r0, #0x1
	pop {r3-r5, pc}
_0205F4C0:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0205F4C4: .word 0x00004043

	thumb_func_start FUN_0205F4C8
FUN_0205F4C8: ; 0x0205F4C8
	push {r4, lr}
	add r4, r0, #0x0
	bmi _0205F4D2
	cmp r4, #0x4
	blt _0205F4D6
_0205F4D2:
	bl ErrorHandling
_0205F4D6:
	ldr r0, _0205F4E0 ; =UNK_020F7436
	lsl r1, r4, #0x1
	ldrh r0, [r0, r1]
	pop {r4, pc}
	nop
_0205F4E0: .word UNK_020F7436

	thumb_func_start FUN_0205F4E4
FUN_0205F4E4: ; 0x0205F4E4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F4C8
	add r2, r0, #0x0
	ldr r1, _0205F508 ; =0x00004036
	lsl r2, r2, #0x10
	add r1, r4, r1
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl FUN_0205F314
	pop {r3-r5, pc}
	nop
_0205F508: .word 0x00004036

	thumb_func_start FUN_0205F50C
FUN_0205F50C: ; 0x0205F50C
	ldr r2, _0205F51C ; =0x00004036
	ldr r3, _0205F520 ; =FUN_0205F314
	add r1, r1, r2
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	mov r2, #0x0
	bx r3
	nop
_0205F51C: .word 0x00004036
_0205F520: .word FUN_0205F314

	thumb_func_start FUN_0205F524
FUN_0205F524: ; 0x0205F524
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, _0205F548 ; =0x00004036
	add r1, r4, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0205F344
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F4C8
	cmp r5, r0
	bne _0205F544
	mov r0, #0x1
	pop {r3-r5, pc}
_0205F544:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0205F548: .word 0x00004036

	thumb_func_start FUN_0205F54C
FUN_0205F54C: ; 0x0205F54C
	ldr r3, _0205F554 ; =FUN_0205F314
	ldr r1, _0205F558 ; =0x0000403A
	mov r2, #0x0
	bx r3
	.balign 4
_0205F554: .word FUN_0205F314
_0205F558: .word 0x0000403A

	thumb_func_start FUN_0205F55C
FUN_0205F55C: ; 0x0205F55C
	ldr r3, _0205F564 ; =FUN_0205F344
	ldr r1, _0205F568 ; =0x0000403A
	bx r3
	nop
_0205F564: .word FUN_0205F344
_0205F568: .word 0x0000403A

	thumb_func_start FUN_0205F56C
FUN_0205F56C: ; 0x0205F56C
	push {r4, lr}
	ldr r1, _0205F58C ; =0x0000403A
	add r4, r0, #0x0
	bl FUN_0205F344
	ldr r2, _0205F590 ; =0x00002710
	cmp r0, r2
	bhs _0205F582
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
_0205F582:
	ldr r1, _0205F58C ; =0x0000403A
	add r0, r4, #0x0
	bl FUN_0205F314
	pop {r4, pc}
	.balign 4
_0205F58C: .word 0x0000403A
_0205F590: .word 0x00002710

	thumb_func_start FUN_0205F594
FUN_0205F594: ; 0x0205F594
	ldr r3, _0205F59C ; =FUN_0205F344
	ldr r1, _0205F5A0 ; =0x0000403B
	bx r3
	nop
_0205F59C: .word FUN_0205F344
_0205F5A0: .word 0x0000403B

	thumb_func_start FUN_0205F5A4
FUN_0205F5A4: ; 0x0205F5A4
	ldr r3, _0205F5AC ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F5B0 ; =0x0000403B
	bx r3
	.balign 4
_0205F5AC: .word FUN_0205F314
_0205F5B0: .word 0x0000403B

	thumb_func_start FUN_0205F5B4
FUN_0205F5B4: ; 0x0205F5B4
	push {r3-r5, lr}
	add r4, r1, #0x0
	lsl r2, r4, #0x10
	ldr r1, _0205F5D4 ; =0x0000403C
	lsr r2, r2, #0x10
	add r5, r0, #0x0
	bl FUN_0205F314
	lsr r2, r4, #0x10
	lsl r2, r2, #0x10
	ldr r1, _0205F5D4 ; =0x0000403C
	add r0, r5, #0x0
	lsr r2, r2, #0x10
	bl FUN_0205F314
	pop {r3-r5, pc}
	.balign 4
_0205F5D4: .word 0x0000403C

	thumb_func_start FUN_0205F5D8
FUN_0205F5D8: ; 0x0205F5D8
	push {r3-r5, lr}
	ldr r1, _0205F5F4 ; =0x0000403C
	add r5, r0, #0x0
	bl FUN_0205F344
	add r4, r0, #0x0
	ldr r1, _0205F5F8 ; =0x0000403D
	add r0, r5, #0x0
	bl FUN_0205F344
	lsl r0, r0, #0x10
	orr r0, r4
	pop {r3-r5, pc}
	nop
_0205F5F4: .word 0x0000403C
_0205F5F8: .word 0x0000403D

	thumb_func_start FUN_0205F5FC
FUN_0205F5FC: ; 0x0205F5FC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl LCRandom
	add r4, r0, #0x0
	bl LCRandom
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	orr r1, r4
	bl FUN_0205F5B4
	pop {r3-r5, pc}

	thumb_func_start FUN_0205F618
FUN_0205F618: ; 0x0205F618
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202881C
	bl FUN_020287A4
	add r2, r0, #0x0
	ldr r1, _0205F640 ; =0x41C64E6D
	add r0, r4, #0x0
	mul r2, r1
	ldr r1, _0205F644 ; =0x00003039
	add r1, r2, r1
	bl FUN_0205F5B4
	pop {r3-r5, pc}
	nop
_0205F640: .word 0x41C64E6D
_0205F644: .word 0x00003039

	thumb_func_start FUN_0205F648
FUN_0205F648: ; 0x0205F648
	ldr r3, _0205F650 ; =FUN_0205F344
	ldr r1, _0205F654 ; =0x00004041
	bx r3
	nop
_0205F650: .word FUN_0205F344
_0205F654: .word 0x00004041

	thumb_func_start FUN_0205F658
FUN_0205F658: ; 0x0205F658
	ldr r3, _0205F660 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F664 ; =0x00004041
	bx r3
	.balign 4
_0205F660: .word FUN_0205F314
_0205F664: .word 0x00004041

	thumb_func_start FUN_0205F668
FUN_0205F668: ; 0x0205F668
	push {r4, lr}
	bl FUN_020462AC
	add r4, r0, #0x0
	bl LCRandom
	mov r1, #0x62
	bl _s32_div_f
	add r1, r1, #0x2
	lsl r1, r1, #0x10
	add r0, r4, #0x0
	lsr r1, r1, #0x10
	bl FUN_0205F658
	pop {r4, pc}

	thumb_func_start FUN_0205F688
FUN_0205F688: ; 0x0205F688
	ldr r3, _0205F690 ; =FUN_0205F344
	ldr r1, _0205F694 ; =0x0000403E
	bx r3
	nop
_0205F690: .word FUN_0205F344
_0205F694: .word 0x0000403E

	thumb_func_start FUN_0205F698
FUN_0205F698: ; 0x0205F698
	ldr r3, _0205F6A0 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F6A4 ; =0x0000403E
	bx r3
	.balign 4
_0205F6A0: .word FUN_0205F314
_0205F6A4: .word 0x0000403E

	thumb_func_start FUN_0205F6A8
FUN_0205F6A8: ; 0x0205F6A8
	ldr r3, _0205F6B0 ; =FUN_0205F344
	ldr r1, _0205F6B4 ; =0x00004049
	bx r3
	nop
_0205F6B0: .word FUN_0205F344
_0205F6B4: .word 0x00004049

	thumb_func_start FUN_0205F6B8
FUN_0205F6B8: ; 0x0205F6B8
	ldr r3, _0205F6C0 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F6C4 ; =0x00004049
	bx r3
	.balign 4
_0205F6C0: .word FUN_0205F314
_0205F6C4: .word 0x00004049

	thumb_func_start FUN_0205F6C8
FUN_0205F6C8: ; 0x0205F6C8
	ldr r3, _0205F6D0 ; =FUN_0205F344
	ldr r1, _0205F6D4 ; =0x00004040
	bx r3
	nop
_0205F6D0: .word FUN_0205F344
_0205F6D4: .word 0x00004040

	thumb_func_start FUN_0205F6D8
FUN_0205F6D8: ; 0x0205F6D8
	ldr r3, _0205F6E0 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F6E4 ; =0x00004040
	bx r3
	.balign 4
_0205F6E0: .word FUN_0205F314
_0205F6E4: .word 0x00004040

	thumb_func_start FUN_0205F6E8
FUN_0205F6E8: ; 0x0205F6E8
	push {r4, lr}
	ldr r1, _0205F708 ; =0x00004042
	add r4, r0, #0x0
	bl FUN_0205F344
	ldr r2, _0205F70C ; =0x00002710
	cmp r0, r2
	bhs _0205F6FE
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
_0205F6FE:
	ldr r1, _0205F708 ; =0x00004042
	add r0, r4, #0x0
	bl FUN_0205F314
	pop {r4, pc}
	.balign 4
_0205F708: .word 0x00004042
_0205F70C: .word 0x00002710

	thumb_func_start FUN_0205F710
FUN_0205F710: ; 0x0205F710
	ldr r3, _0205F718 ; =FUN_0205F344
	ldr r1, _0205F71C ; =0x00004042
	bx r3
	nop
_0205F718: .word FUN_0205F344
_0205F71C: .word 0x00004042

	thumb_func_start FUN_0205F720
FUN_0205F720: ; 0x0205F720
	ldr r3, _0205F728 ; =FUN_0205F344
	ldr r1, _0205F72C ; =0x00004046
	bx r3
	nop
_0205F728: .word FUN_0205F344
_0205F72C: .word 0x00004046

	thumb_func_start FUN_0205F730
FUN_0205F730: ; 0x0205F730
	ldr r3, _0205F738 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F73C ; =0x00004046
	bx r3
	.balign 4
_0205F738: .word FUN_0205F314
_0205F73C: .word 0x00004046

	thumb_func_start FUN_0205F740
FUN_0205F740: ; 0x0205F740
	ldr r3, _0205F748 ; =FUN_0205F344
	ldr r1, _0205F74C ; =0x00004047
	bx r3
	nop
_0205F748: .word FUN_0205F344
_0205F74C: .word 0x00004047

	thumb_func_start FUN_0205F750
FUN_0205F750: ; 0x0205F750
	ldr r3, _0205F758 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F75C ; =0x00004047
	bx r3
	.balign 4
_0205F758: .word FUN_0205F314
_0205F75C: .word 0x00004047

	thumb_func_start FUN_0205F760
FUN_0205F760: ; 0x0205F760
	ldr r3, _0205F768 ; =FUN_0205F344
	ldr r1, _0205F76C ; =0x00004048
	bx r3
	nop
_0205F768: .word FUN_0205F344
_0205F76C: .word 0x00004048

	thumb_func_start FUN_0205F770
FUN_0205F770: ; 0x0205F770
	ldr r3, _0205F778 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F77C ; =0x00004048
	bx r3
	.balign 4
_0205F778: .word FUN_0205F314
_0205F77C: .word 0x00004048

	thumb_func_start FUN_0205F780
FUN_0205F780: ; 0x0205F780
	ldr r3, _0205F788 ; =FUN_0205F344
	ldr r1, _0205F78C ; =0x0000404A
	bx r3
	nop
_0205F788: .word FUN_0205F344
_0205F78C: .word 0x0000404A

	thumb_func_start FUN_0205F790
FUN_0205F790: ; 0x0205F790
	ldr r3, _0205F798 ; =FUN_0205F314
	add r2, r1, #0x0
	ldr r1, _0205F79C ; =0x0000404A
	bx r3
	.balign 4
_0205F798: .word FUN_0205F314
_0205F79C: .word 0x0000404A
