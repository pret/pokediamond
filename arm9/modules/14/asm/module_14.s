	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD14_021D74E0
MOD14_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	mov r2, #1
	add r5, r0, #0
	mov r0, #3
	mov r1, #9
	lsl r2, r2, #0xe
	bl FUN_0201681C
	mov r2, #0xf
	mov r0, #3
	mov r1, #0xa
	lsl r2, r2, #0xe
	bl FUN_0201681C
	mov r1, #0x87
	add r0, r5, #0
	lsl r1, r1, #2
	mov r2, #9
	bl FUN_02006268
	add r4, r0, #0
	beq _021D7544
	add r0, r5, #0
	bl FUN_0200628C
	add r1, r0, #0
	add r0, r4, #0
	bl MOD14_021DB220
	mov r0, #0x45
	lsl r0, r0, #2
	add r0, r4, r0
	add r1, r4, #0
	add r2, r4, #0
	bl MOD14_021DC76C
	mov r0, #0x1b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	add r0, r4, #0
	bl MOD14_021D762C
	mov r1, #0x6a
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r1, _021D7548 ; =MOD14_021D7680
	add r0, r4, #0
	bl MOD14_021D7610
_021D7544:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7548: .word MOD14_021D7680

	thumb_func_start MOD14_021D754C
MOD14_021D754C: ; 0x021D754C
	push {r4, lr}
	bl FUN_02006278
	mov r1, #0x6b
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	cmp r2, #0
	beq _021D7568
	add r1, #8
	add r1, r4, r1
	blx r2
	mov r0, #0
	pop {r4, pc}
_021D7568:
	sub r0, r1, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D75AA
	ldr r0, _021D75B4 ; =0x021C48B8
	ldr r2, [r0, #0x48]
	mov r0, #2
	lsl r0, r0, #0xa
	tst r0, r2
	beq _021D759E
	sub r1, #0x98
	ldr r0, [r4, r1]
	bl MOD14_021DCBC0
	cmp r0, #1
	bne _021D759E
	add r0, r4, #0
	bl MOD14_021DC394
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x2b
	bl MOD14_021DCB2C
	mov r0, #0
	pop {r4, pc}
_021D759E:
	mov r1, #0x6a
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add r0, r4, #0
	blx r1
	pop {r4, pc}
_021D75AA:
	bl ErrorHandling
	mov r0, #1
	pop {r4, pc}
	nop
_021D75B4: .word 0x021C48B8

	thumb_func_start MOD14_021D75B8
MOD14_021D75B8: ; 0x021D75B8
	push {r4, lr}
	bl FUN_02006278
	mov r1, #0x49
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, #0x95
	bl FUN_0206BAE4
	cmp r0, #0
	bne _021D75DE
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02029EF8
	bl FUN_02029F08
_021D75DE:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCA38
	add r0, r4, #0
	bl MOD14_021DB398
	mov r0, #9
	bl FUN_020168D0
	mov r0, #0xa
	bl FUN_020168D0
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021D7600
MOD14_021D7600: ; 0x021D7600
	mov r2, #0x6a
	lsl r2, r2, #2
	str r1, [r0, r2]
	mov r1, #0
	add r2, #8
	str r1, [r0, r2]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021D7610
MOD14_021D7610: ; 0x021D7610
	mov r2, #0x6b
	lsl r2, r2, #2
	str r1, [r0, r2]
	mov r1, #0
	add r2, #8
	str r1, [r0, r2]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021D7620
MOD14_021D7620: ; 0x021D7620
	mov r1, #0x6b
	mov r2, #0
	lsl r1, r1, #2
	str r2, [r0, r1]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021D762C
MOD14_021D762C: ; 0x021D762C
	push {r3, lr}
	bl MOD14_021DC3CC
	cmp r0, #4
	bhi _021D764C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7642: ; jump table
	.short _021D764C - _021D7642 - 2 ; case 0
	.short _021D7650 - _021D7642 - 2 ; case 1
	.short _021D7654 - _021D7642 - 2 ; case 2
	.short _021D765C - _021D7642 - 2 ; case 3
	.short _021D7658 - _021D7642 - 2 ; case 4
_021D764C:
	ldr r0, _021D7660 ; =MOD14_021D7750
	pop {r3, pc}
_021D7650:
	ldr r0, _021D7664 ; =MOD14_021D79D0
	pop {r3, pc}
_021D7654:
	ldr r0, _021D7668 ; =MOD14_021D7D20
	pop {r3, pc}
_021D7658:
	ldr r0, _021D766C ; =MOD14_021D7F0C
	pop {r3, pc}
_021D765C:
	ldr r0, _021D7670 ; =MOD14_021D8118
	pop {r3, pc}
	.align 2, 0
_021D7660: .word MOD14_021D7750
_021D7664: .word MOD14_021D79D0
_021D7668: .word MOD14_021D7D20
_021D766C: .word MOD14_021D7F0C
_021D7670: .word MOD14_021D8118

	thumb_func_start MOD14_021D7674
MOD14_021D7674: ; 0x021D7674
	mov r1, #0x46
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r2, #1
	str r2, [r0, #8]
	bx lr

	thumb_func_start MOD14_021D7680
MOD14_021D7680: ; 0x021D7680
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021D7696
	cmp r0, #1
	beq _021D76AA
	cmp r0, #2
	beq _021D76CE
	pop {r3, r4, r5, pc}
_021D7696:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl MOD14_021DCB2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D76AA:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D76E4
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl MOD14_021DCB2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D76CE:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D76E4
	add r0, r5, #0
	bl MOD14_021D7620
_021D76E4:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021D76E8
MOD14_021D76E8: ; 0x021D76E8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021D76FE
	cmp r0, #1
	beq _021D7712
	cmp r0, #2
	beq _021D7736
	pop {r3, r4, r5, pc}
_021D76FE:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl MOD14_021DCB2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D7712:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D774C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #2
	bl MOD14_021DCB2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D7736:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #2
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D774C
	add r0, r5, #0
	bl MOD14_021D7620
_021D774C:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021D7750
MOD14_021D7750: ; 0x021D7750
	push {r4, lr}
	mov r1, #0x1b
	add r4, r0, #0
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	cmp r2, #0
	beq _021D776C
	cmp r2, #1
	bne _021D7764
	b _021D793E
_021D7764:
	cmp r2, #2
	bne _021D776A
	b _021D795C
_021D776A:
	b _021D7970
_021D776C:
	ldr r1, _021D7974 ; =0x021C48B8
	ldr r2, [r1, #0x48]
	mov r1, #1
	tst r1, r2
	beq _021D779C
	bl MOD14_021DC408
	cmp r0, #0
	beq _021D779C
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #3
	beq _021D7792
	ldr r1, _021D7978 ; =MOD14_021D8804
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7970
_021D7792:
	ldr r1, _021D797C ; =MOD14_021D8A68
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7970
_021D779C:
	ldr r0, _021D7974 ; =0x021C48B8
	mov r2, #2
	ldr r1, [r0, #0x48]
	tst r1, r2
	beq _021D77B0
	ldr r1, _021D7980 ; =MOD14_021D86BC
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7970
_021D77B0:
	ldr r0, [r0, #0x44]
	lsl r1, r2, #8
	tst r1, r0
	beq _021D77C8
	add r0, r4, #0
	bl MOD14_021DC2A4
	ldr r1, _021D7984 ; =MOD14_021DABE8
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7970
_021D77C8:
	add r2, #0xfe
	add r1, r0, #0
	tst r1, r2
	beq _021D77E0
	add r0, r4, #0
	bl MOD14_021DC278
	ldr r1, _021D7984 ; =MOD14_021DABE8
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7970
_021D77E0:
	add r1, r4, #0
	bl MOD14_021DB5B4
	cmp r0, #0
	beq _021D7818
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB2C
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021D780C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
_021D780C:
	mov r0, #0x1b
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _021D7970
_021D7818:
	add r0, r4, #0
	bl MOD14_021DB9C8
	cmp r0, #0
	beq _021D783A
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021D7862
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D783C
	cmp r0, #1
	beq _021D7846
_021D783A:
	b _021D792E
_021D783C:
	ldr r1, _021D7988 ; =MOD14_021DAC80
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D792E
_021D7846:
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #3
	beq _021D785A
	ldr r1, _021D798C ; =MOD14_021DAF78
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D792E
_021D785A:
	ldr r0, _021D7990 ; =0x000005F3
	bl FUN_020054C8
	b _021D792E
_021D7862:
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D7876
	cmp r0, #1
	beq _021D78C4
	cmp r0, #2
	beq _021D7912
	b _021D792E
_021D7876:
	add r0, r4, #0
	bl MOD14_021DC558
	cmp r0, #0
	bne _021D78BC
	add r0, r4, #0
	bl MOD14_021DC3F0
	cmp r0, #1
	bne _021D78BC
	ldr r0, _021D7994 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC170
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r4, #0
	bl MOD14_021DBE88
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x31
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #1
	b _021D7930
_021D78BC:
	ldr r0, _021D7990 ; =0x000005F3
	bl FUN_020054C8
	b _021D792E
_021D78C4:
	add r0, r4, #0
	bl MOD14_021DC558
	cmp r0, #1
	bne _021D790A
	add r0, r4, #0
	bl MOD14_021DC3F0
	cmp r0, #1
	bne _021D790A
	ldr r0, _021D7994 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC170
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r4, #0
	bl MOD14_021DBE88
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x31
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #1
	b _021D7930
_021D790A:
	ldr r0, _021D7990 ; =0x000005F3
	bl FUN_020054C8
	b _021D792E
_021D7912:
	ldr r0, _021D7994 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC180
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x32
	bl MOD14_021DCB2C
	mov r0, #1
	b _021D7930
_021D792E:
	mov r0, #0
_021D7930:
	cmp r0, #0
	beq _021D7970
	mov r0, #0x1b
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7970
_021D793E:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #5
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D7970
	add r0, r4, #0
	bl MOD14_021D762C
	add r1, r0, #0
	add r0, r4, #0
	bl MOD14_021D7600
	b _021D7970
_021D795C:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D7970
	mov r0, #0x1b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
_021D7970:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D7974: .word 0x021C48B8
_021D7978: .word MOD14_021D8804
_021D797C: .word MOD14_021D8A68
_021D7980: .word MOD14_021D86BC
_021D7984: .word MOD14_021DABE8
_021D7988: .word MOD14_021DAC80
_021D798C: .word MOD14_021DAF78
_021D7990: .word 0x000005F3
_021D7994: .word 0x000005DD

	thumb_func_start MOD14_021D7998
MOD14_021D7998: ; 0x021D7998
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD14_021DC430
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0206EA98
	cmp r0, #0
	beq _021D79B6
	mov r0, #0x1e
	str r0, [r4]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D79B6:
	add r0, r5, #0
	mov r1, #0xa1
	mov r2, #0
	bl MOD14_021DC58C
	cmp r0, #0
	beq _021D79CC
	mov r0, #0x1d
	str r0, [r4]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D79CC:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021D79D0
MOD14_021D79D0: ; 0x021D79D0
	push {r3, r4, lr}
	sub sp, #4
	mov r1, #0x1b
	add r4, r0, #0
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	cmp r2, #6
	bhi _021D7A20
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021D79EC: ; jump table
	.short _021D79FA - _021D79EC - 2 ; case 0
	.short _021D7BD4 - _021D79EC - 2 ; case 1
	.short _021D7BEE - _021D79EC - 2 ; case 2
	.short _021D7C58 - _021D79EC - 2 ; case 3
	.short _021D7C98 - _021D79EC - 2 ; case 4
	.short _021D7CB6 - _021D79EC - 2 ; case 5
	.short _021D7CE4 - _021D79EC - 2 ; case 6
_021D79FA:
	ldr r1, _021D7D00 ; =0x021C48B8
	mov r2, #1
	ldr r1, [r1, #0x48]
	tst r2, r1
	beq _021D7A40
	bl MOD14_021DC3E8
	cmp r0, #6
	bne _021D7A16
	mov r0, #0x1b
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7CF8
_021D7A16:
	add r0, r4, #0
	bl MOD14_021DC408
	cmp r0, #0
	bne _021D7A22
_021D7A20:
	b _021D7CF8
_021D7A22:
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #3
	beq _021D7A36
	ldr r1, _021D7D04 ; =MOD14_021D8804
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7CF8
_021D7A36:
	ldr r1, _021D7D08 ; =MOD14_021D8A68
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7CF8
_021D7A40:
	mov r2, #2
	tst r2, r1
	bne _021D7A6A
	mov r2, #0x10
	tst r1, r2
	beq _021D7A56
	bl MOD14_021DC3E8
	mov r1, #1
	tst r0, r1
	bne _021D7A6A
_021D7A56:
	ldr r0, _021D7D00 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x10
	tst r0, r1
	beq _021D7A74
	add r0, r4, #0
	bl MOD14_021DC3E8
	cmp r0, #6
	bne _021D7A74
_021D7A6A:
	mov r0, #0x1b
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7CF8
_021D7A74:
	ldr r0, _021D7D00 ; =0x021C48B8
	add r1, r4, #0
	ldr r0, [r0, #0x44]
	bl MOD14_021DB5B4
	cmp r0, #0
	beq _021D7AAE
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB2C
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021D7AA4
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
_021D7AA4:
	mov r0, #0x1b
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7CF8
_021D7AAE:
	add r0, r4, #0
	bl MOD14_021DB9C8
	cmp r0, #0
	beq _021D7AD0
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021D7AF8
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D7AD2
	cmp r0, #1
	beq _021D7ADC
_021D7AD0:
	b _021D7BC4
_021D7AD2:
	ldr r1, _021D7D0C ; =MOD14_021DAC80
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7BC4
_021D7ADC:
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #3
	beq _021D7AF0
	ldr r1, _021D7D10 ; =MOD14_021DAF78
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7BC4
_021D7AF0:
	ldr r0, _021D7D14 ; =0x000005F3
	bl FUN_020054C8
	b _021D7BC4
_021D7AF8:
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D7B0C
	cmp r0, #1
	beq _021D7B5A
	cmp r0, #2
	beq _021D7BA8
	b _021D7BC4
_021D7B0C:
	add r0, r4, #0
	bl MOD14_021DC558
	cmp r0, #0
	bne _021D7B52
	add r0, r4, #0
	bl MOD14_021DC3F0
	cmp r0, #1
	bne _021D7B52
	ldr r0, _021D7D18 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC170
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r4, #0
	bl MOD14_021DBE88
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x31
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #1
	b _021D7BC6
_021D7B52:
	ldr r0, _021D7D14 ; =0x000005F3
	bl FUN_020054C8
	b _021D7BC4
_021D7B5A:
	add r0, r4, #0
	bl MOD14_021DC558
	cmp r0, #1
	bne _021D7BA0
	add r0, r4, #0
	bl MOD14_021DC3F0
	cmp r0, #1
	bne _021D7BA0
	ldr r0, _021D7D18 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC170
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r4, #0
	bl MOD14_021DBE88
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x31
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #1
	b _021D7BC6
_021D7BA0:
	ldr r0, _021D7D14 ; =0x000005F3
	bl FUN_020054C8
	b _021D7BC4
_021D7BA8:
	ldr r0, _021D7D18 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC180
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x32
	bl MOD14_021DCB2C
	mov r0, #1
	b _021D7BC6
_021D7BC4:
	mov r0, #0
_021D7BC6:
	cmp r0, #0
	beq _021D7BE2
	mov r0, #0x1b
	mov r1, #6
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7CF8
_021D7BD4:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #5
	bl MOD14_021DCB98
	cmp r0, #0
	bne _021D7BE4
_021D7BE2:
	b _021D7CF8
_021D7BE4:
	mov r0, #0x1b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7CF8
_021D7BEE:
	bl MOD14_021DC3C4
	cmp r0, #0
	bne _021D7C08
	ldr r1, _021D7D1C ; =MOD14_021D86BC
	add r0, r4, #0
	bl MOD14_021D7610
	mov r0, #0x1b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7CF8
_021D7C08:
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	beq _021D7C42
	add r0, r4, #0
	add r1, sp, #0
	bl MOD14_021D7998
	cmp r0, #0
	beq _021D7C42
	ldr r0, _021D7D14 ; =0x000005F3
	bl FUN_020054C8
	ldr r1, [sp]
	add r0, r4, #0
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #0x1b
	mov r1, #5
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7CF8
_021D7C42:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x24
	bl MOD14_021DCB2C
	mov r0, #0x1b
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7CF8
_021D7C58:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #0x24
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D7CF8
	add r0, r4, #0
	bl MOD14_021DB910
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB2C
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021D7C8E
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
_021D7C8E:
	mov r0, #0x1b
	mov r1, #4
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7CF8
_021D7C98:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #5
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D7CF8
	add r0, r4, #0
	bl MOD14_021D762C
	add r1, r0, #0
	add r0, r4, #0
	bl MOD14_021D7600
	b _021D7CF8
_021D7CB6:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #0x18
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D7CF8
	ldr r0, _021D7D00 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D7CF8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #0x1b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7CF8
_021D7CE4:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D7CF8
	mov r0, #0x1b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
_021D7CF8:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D7D00: .word 0x021C48B8
_021D7D04: .word MOD14_021D8804
_021D7D08: .word MOD14_021D8A68
_021D7D0C: .word MOD14_021DAC80
_021D7D10: .word MOD14_021DAF78
_021D7D14: .word 0x000005F3
_021D7D18: .word 0x000005DD
_021D7D1C: .word MOD14_021D86BC

	thumb_func_start MOD14_021D7D20
MOD14_021D7D20: ; 0x021D7D20
	push {r3, r4, r5, lr}
	mov r3, #0x1b
	add r4, r0, #0
	lsl r3, r3, #4
	ldr r1, [r4, r3]
	cmp r1, #0
	beq _021D7D36
	cmp r1, #1
	bne _021D7D34
	b _021D7ECC
_021D7D34:
	b _021D7EE8
_021D7D36:
	ldr r5, _021D7EEC ; =0x021C48B8
	add r2, r3, #0
	ldr r1, [r5, #0x44]
	add r2, #0x70
	tst r2, r1
	beq _021D7D50
	bl MOD14_021DC2A4
	ldr r1, _021D7EF0 ; =MOD14_021DABE8
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7EE8
_021D7D50:
	sub r3, #0xa0
	add r2, r1, #0
	tst r2, r3
	beq _021D7D66
	bl MOD14_021DC278
	ldr r1, _021D7EF0 ; =MOD14_021DABE8
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7EE8
_021D7D66:
	ldr r3, [r5, #0x48]
	mov r2, #1
	tst r2, r3
	beq _021D7D76
	ldr r1, _021D7EF4 ; =MOD14_021D8D70
	bl MOD14_021D7610
	b _021D7EE8
_021D7D76:
	mov r2, #2
	tst r2, r3
	beq _021D7D84
	ldr r1, _021D7EF8 ; =MOD14_021D86BC
	bl MOD14_021D7610
	b _021D7EE8
_021D7D84:
	add r0, r1, #0
	add r1, r4, #0
	bl MOD14_021DB5B4
	cmp r0, #0
	beq _021D7DBC
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB2C
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021D7DB2
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
_021D7DB2:
	mov r0, #0x1b
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D7EE8
_021D7DBC:
	add r0, r4, #0
	bl MOD14_021DB9C8
	cmp r0, #0
	beq _021D7DDE
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021D7E06
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D7DE0
	cmp r0, #1
	beq _021D7DEA
_021D7DDE:
	b _021D7EE8
_021D7DE0:
	ldr r1, _021D7EFC ; =MOD14_021DAC80
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7EE8
_021D7DEA:
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #3
	beq _021D7DFE
	ldr r1, _021D7F00 ; =MOD14_021DAF78
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D7EE8
_021D7DFE:
	ldr r0, _021D7F04 ; =0x000005F3
	bl FUN_020054C8
	b _021D7EE8
_021D7E06:
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D7E1A
	cmp r0, #1
	beq _021D7E66
	cmp r0, #2
	beq _021D7EB2
	b _021D7EE8
_021D7E1A:
	add r0, r4, #0
	bl MOD14_021DC558
	cmp r0, #0
	bne _021D7E5E
	add r0, r4, #0
	bl MOD14_021DC3F0
	cmp r0, #1
	bne _021D7E5E
	ldr r0, _021D7F08 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC170
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r4, #0
	bl MOD14_021DBE88
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x31
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	b _021D7EE8
_021D7E5E:
	ldr r0, _021D7F04 ; =0x000005F3
	bl FUN_020054C8
	b _021D7EE8
_021D7E66:
	add r0, r4, #0
	bl MOD14_021DC558
	cmp r0, #1
	bne _021D7EAA
	add r0, r4, #0
	bl MOD14_021DC3F0
	cmp r0, #1
	bne _021D7EAA
	ldr r0, _021D7F08 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC170
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r4, #0
	bl MOD14_021DBE88
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x31
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	b _021D7EE8
_021D7EAA:
	ldr r0, _021D7F04 ; =0x000005F3
	bl FUN_020054C8
	b _021D7EE8
_021D7EB2:
	ldr r0, _021D7F08 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC180
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x32
	bl MOD14_021DCB2C
	b _021D7EE8
_021D7ECC:
	sub r3, #0x9c
	ldr r0, [r4, r3]
	mov r1, #5
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D7EE8
	add r0, r4, #0
	bl MOD14_021D762C
	add r1, r0, #0
	add r0, r4, #0
	bl MOD14_021D7600
_021D7EE8:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7EEC: .word 0x021C48B8
_021D7EF0: .word MOD14_021DABE8
_021D7EF4: .word MOD14_021D8D70
_021D7EF8: .word MOD14_021D86BC
_021D7EFC: .word MOD14_021DAC80
_021D7F00: .word MOD14_021DAF78
_021D7F04: .word 0x000005F3
_021D7F08: .word 0x000005DD

	thumb_func_start MOD14_021D7F0C
MOD14_021D7F0C: ; 0x021D7F0C
	push {r3, r4, r5, lr}
	mov r1, #0x1b
	add r4, r0, #0
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	cmp r2, #0
	beq _021D7F28
	cmp r2, #1
	bne _021D7F20
	b _021D80BE
_021D7F20:
	cmp r2, #2
	bne _021D7F26
	b _021D80D6
_021D7F26:
	b _021D80F2
_021D7F28:
	ldr r3, _021D80F8 ; =0x021C48B8
	mov r1, #1
	ldr r5, [r3, #0x48]
	tst r1, r5
	beq _021D7F3A
	ldr r1, _021D80FC ; =MOD14_021D854C
	bl MOD14_021D7610
	b _021D80F2
_021D7F3A:
	mov r2, #2
	add r1, r5, #0
	tst r1, r2
	beq _021D7F4A
	ldr r1, _021D8100 ; =MOD14_021D86BC
	bl MOD14_021D7610
	b _021D80F2
_021D7F4A:
	ldr r3, [r3, #0x44]
	lsl r1, r2, #8
	tst r1, r3
	beq _021D7F60
	bl MOD14_021DC2A4
	ldr r1, _021D8104 ; =MOD14_021DABE8
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D80F2
_021D7F60:
	add r2, #0xfe
	add r1, r3, #0
	tst r1, r2
	beq _021D7F76
	bl MOD14_021DC278
	ldr r1, _021D8104 ; =MOD14_021DABE8
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D80F2
_021D7F76:
	add r0, r3, #0
	add r1, r4, #0
	bl MOD14_021DB5B4
	cmp r0, #0
	beq _021D7FAE
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB2C
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021D7FA4
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
_021D7FA4:
	mov r0, #0x1b
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D80F2
_021D7FAE:
	add r0, r4, #0
	bl MOD14_021DB9C8
	cmp r0, #0
	beq _021D7FD0
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021D7FF8
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D7FD2
	cmp r0, #1
	beq _021D7FDC
_021D7FD0:
	b _021D80F2
_021D7FD2:
	ldr r1, _021D8108 ; =MOD14_021DAC80
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D80F2
_021D7FDC:
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #3
	beq _021D7FF0
	ldr r1, _021D810C ; =MOD14_021DAF78
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D80F2
_021D7FF0:
	ldr r0, _021D8110 ; =0x000005F3
	bl FUN_020054C8
	b _021D80F2
_021D7FF8:
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D800C
	cmp r0, #1
	beq _021D8058
	cmp r0, #2
	beq _021D80A4
	b _021D80F2
_021D800C:
	add r0, r4, #0
	bl MOD14_021DC558
	cmp r0, #0
	bne _021D8050
	add r0, r4, #0
	bl MOD14_021DC3F0
	cmp r0, #1
	bne _021D8050
	ldr r0, _021D8114 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC170
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r4, #0
	bl MOD14_021DBE88
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x31
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	b _021D80F2
_021D8050:
	ldr r0, _021D8110 ; =0x000005F3
	bl FUN_020054C8
	b _021D80F2
_021D8058:
	add r0, r4, #0
	bl MOD14_021DC558
	cmp r0, #1
	bne _021D809C
	add r0, r4, #0
	bl MOD14_021DC3F0
	cmp r0, #1
	bne _021D809C
	ldr r0, _021D8114 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC170
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r4, #0
	bl MOD14_021DBE88
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x31
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	b _021D80F2
_021D809C:
	ldr r0, _021D8110 ; =0x000005F3
	bl FUN_020054C8
	b _021D80F2
_021D80A4:
	ldr r0, _021D8114 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC180
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x32
	bl MOD14_021DCB2C
	b _021D80F2
_021D80BE:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #4
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D80F2
	mov r0, #0x1b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D80F2
_021D80D6:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #5
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D80F2
	add r0, r4, #0
	bl MOD14_021D762C
	add r1, r0, #0
	add r0, r4, #0
	bl MOD14_021D7600
_021D80F2:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D80F8: .word 0x021C48B8
_021D80FC: .word MOD14_021D854C
_021D8100: .word MOD14_021D86BC
_021D8104: .word MOD14_021DABE8
_021D8108: .word MOD14_021DAC80
_021D810C: .word MOD14_021DAF78
_021D8110: .word 0x000005F3
_021D8114: .word 0x000005DD

	thumb_func_start MOD14_021D8118
MOD14_021D8118: ; 0x021D8118
	push {r3, r4, r5, lr}
	mov r1, #0x1b
	add r4, r0, #0
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	cmp r2, #5
	bhi _021D8220
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021D8132: ; jump table
	.short _021D813E - _021D8132 - 2 ; case 0
	.short _021D830E - _021D8132 - 2 ; case 1
	.short _021D8332 - _021D8132 - 2 ; case 2
	.short _021D8372 - _021D8132 - 2 ; case 3
	.short _021D838A - _021D8132 - 2 ; case 4
	.short _021D83A8 - _021D8132 - 2 ; case 5
_021D813E:
	ldr r3, _021D83C8 ; =0x021C48B8
	mov r1, #1
	ldr r5, [r3, #0x48]
	tst r1, r5
	beq _021D818A
	bl MOD14_021DC3C4
	cmp r0, #1
	beq _021D8166
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x22
	bl MOD14_021DCB2C
	mov r0, #0x1b
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D83C4
_021D8166:
	ldr r0, _021D83CC ; =0x000005F3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0x12
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #0x1b
	mov r1, #5
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D83C4
_021D818A:
	mov r2, #2
	add r1, r5, #0
	tst r1, r2
	beq _021D819A
	ldr r1, _021D83D0 ; =MOD14_021D86BC
	bl MOD14_021D7610
	b _021D83C4
_021D819A:
	ldr r3, [r3, #0x44]
	lsl r1, r2, #8
	tst r1, r3
	beq _021D81B0
	bl MOD14_021DC2A4
	ldr r1, _021D83D4 ; =MOD14_021DABE8
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D83C4
_021D81B0:
	add r2, #0xfe
	add r1, r3, #0
	tst r1, r2
	beq _021D81C6
	bl MOD14_021DC278
	ldr r1, _021D83D4 ; =MOD14_021DABE8
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D83C4
_021D81C6:
	add r0, r3, #0
	add r1, r4, #0
	bl MOD14_021DB5B4
	cmp r0, #0
	beq _021D81FE
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB2C
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021D81F4
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
_021D81F4:
	mov r0, #0x1b
	mov r1, #4
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D83C4
_021D81FE:
	add r0, r4, #0
	bl MOD14_021DB9C8
	cmp r0, #0
	beq _021D8220
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021D8248
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D8222
	cmp r0, #1
	beq _021D822C
_021D8220:
	b _021D83C4
_021D8222:
	ldr r1, _021D83D8 ; =MOD14_021DAC80
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D83C4
_021D822C:
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #3
	beq _021D8240
	ldr r1, _021D83DC ; =MOD14_021DAF78
	add r0, r4, #0
	bl MOD14_021D7610
	b _021D83C4
_021D8240:
	ldr r0, _021D83CC ; =0x000005F3
	bl FUN_020054C8
	b _021D83C4
_021D8248:
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D825C
	cmp r0, #1
	beq _021D82A8
	cmp r0, #2
	beq _021D82F4
	b _021D83C4
_021D825C:
	add r0, r4, #0
	bl MOD14_021DC558
	cmp r0, #0
	bne _021D82A0
	add r0, r4, #0
	bl MOD14_021DC3F0
	cmp r0, #1
	bne _021D82A0
	ldr r0, _021D83E0 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC170
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r4, #0
	bl MOD14_021DBE88
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x31
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	b _021D83C4
_021D82A0:
	ldr r0, _021D83CC ; =0x000005F3
	bl FUN_020054C8
	b _021D83C4
_021D82A8:
	add r0, r4, #0
	bl MOD14_021DC558
	cmp r0, #1
	bne _021D82EC
	add r0, r4, #0
	bl MOD14_021DC3F0
	cmp r0, #1
	bne _021D82EC
	ldr r0, _021D83E0 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC170
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r4, #0
	bl MOD14_021DBE88
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x31
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	b _021D83C4
_021D82EC:
	ldr r0, _021D83CC ; =0x000005F3
	bl FUN_020054C8
	b _021D83C4
_021D82F4:
	ldr r0, _021D83E0 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021DC180
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x32
	bl MOD14_021DCB2C
	b _021D83C4
_021D830E:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #0x22
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D83C4
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x23
	bl MOD14_021DCB2C
	mov r0, #0x1b
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D83C4
_021D8332:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #0x23
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D83C4
	add r0, r4, #0
	bl MOD14_021DB8D0
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB2C
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021D8368
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
_021D8368:
	mov r0, #0x1b
	mov r1, #4
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D83C4
_021D8372:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #4
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D83C4
	mov r0, #0x1b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D83C4
_021D838A:
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #5
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D83C4
	add r0, r4, #0
	bl MOD14_021D762C
	add r1, r0, #0
	add r0, r4, #0
	bl MOD14_021D7600
	b _021D83C4
_021D83A8:
	ldr r0, _021D83C8 ; =0x021C48B8
	ldr r2, [r0, #0x48]
	mov r0, #3
	tst r0, r2
	beq _021D83C4
	sub r1, #0x9c
	ldr r0, [r4, r1]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #0x1b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
_021D83C4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D83C8: .word 0x021C48B8
_021D83CC: .word 0x000005F3
_021D83D0: .word MOD14_021D86BC
_021D83D4: .word MOD14_021DABE8
_021D83D8: .word MOD14_021DAC80
_021D83DC: .word MOD14_021DAF78
_021D83E0: .word 0x000005DD

	thumb_func_start MOD14_021D83E4
MOD14_021D83E4: ; 0x021D83E4
	push {r4, lr}
	add r4, r0, #0
	bl MOD14_021DC3F4
	cmp r0, #2
	bne _021D8428
	mov r0, #0x4b
	ldr r1, [r4, #0x14]
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldrb r0, [r4, #0x1f]
	cmp r0, #0
	beq _021D8402
	mov r0, #0
	b _021D8404
_021D8402:
	mov r0, #2
_021D8404:
	ldr r1, _021D8500 ; =0x0000013D
	mov r2, #1
	strb r0, [r4, r1]
	add r0, r1, #2
	strb r2, [r4, r0]
	mov r2, #0
	add r0, r1, #3
	strb r2, [r4, r0]
	add r0, r1, #1
	strb r2, [r4, r0]
	add r0, r1, #7
	strh r2, [r4, r0]
	add r0, r1, #0
	add r0, #0x67
	ldr r0, [r4, r0]
	sub r1, #0xd
	str r0, [r4, r1]
	b _021D84AA
_021D8428:
	add r0, r4, #0
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021D8476
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_0206B330
	add r1, r0, #0
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r2, #0
	bl FUN_0206B5E4
	mov r1, #0x4b
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	mov r2, #2
	add r0, #0x11
	strb r2, [r4, r0]
	mov r0, #0x1e
	add r1, #0x13
	strb r0, [r4, r1]
	add r0, r4, #0
	bl MOD14_021DC3E0
	mov r1, #5
	lsl r1, r1, #6
	strb r0, [r4, r1]
	mov r2, #0
	sub r0, r1, #2
	strb r2, [r4, r0]
	add r0, r1, #4
	strh r2, [r4, r0]
	b _021D84AA
_021D8476:
	mov r1, #0x49
	lsl r1, r1, #2
	add r0, r1, #0
	ldr r2, [r4, r1]
	add r0, #8
	str r2, [r4, r0]
	add r0, r1, #0
	mov r2, #1
	add r0, #0x19
	strb r2, [r4, r0]
	ldr r0, [r4, r1]
	bl FUN_0206B9AC
	ldr r1, _021D8504 ; =0x0000013F
	strb r0, [r4, r1]
	add r0, r4, #0
	bl MOD14_021DC3E8
	mov r1, #5
	lsl r1, r1, #6
	strb r0, [r4, r1]
	mov r2, #0
	sub r0, r1, #2
	strb r2, [r4, r0]
	add r0, r1, #4
	strh r2, [r4, r0]
_021D84AA:
	mov r0, #0x55
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r0, #0x38
	ldr r0, [r4, r0]
	bl FUN_0206BB28
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x2c
	ldr r0, [r4, r1]
	bl FUN_02079C70
	mov r1, #0x56
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x3c
	ldr r0, [r4, r1]
	bl FUN_0202A918
	mov r1, #0x53
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x20
	add r0, r4, r1
	ldr r1, _021D8508 ; =0x021E626C
	bl FUN_0207B000
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_020238F4
	add r1, r0, #0
	mov r0, #0x4b
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_0207C2A4
	pop {r4, pc}
	nop
_021D8500: .word 0x0000013D
_021D8504: .word 0x0000013F
_021D8508: .word 0x021E626C

	thumb_func_start MOD14_021D850C
MOD14_021D850C: ; 0x021D850C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x1b
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _021D8520
	cmp r1, #1
	beq _021D8536
	b _021D8546
_021D8520:
	sub r0, #0x9c
	ldr r0, [r4, r0]
	mov r1, #0x33
	bl MOD14_021DCB2C
	mov r0, #0x1b
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _021D8546
_021D8536:
	sub r0, #0x9c
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D8546
	mov r0, #1
	pop {r4, pc}
_021D8546:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021D854C
MOD14_021D854C: ; 0x021D854C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #6
	bls _021D855A
	b _021D86A6
_021D855A:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8566: ; jump table
	.short _021D8574 - _021D8566 - 2 ; case 0
	.short _021D85CC - _021D8566 - 2 ; case 1
	.short _021D8604 - _021D8566 - 2 ; case 2
	.short _021D86A6 - _021D8566 - 2 ; case 3
	.short _021D8660 - _021D8566 - 2 ; case 4
	.short _021D8674 - _021D8566 - 2 ; case 5
	.short _021D8690 - _021D8566 - 2 ; case 6
_021D8574:
	bl MOD14_021DC3C4
	cmp r0, #3
	bne _021D8590
	add r0, r4, #0
	bl MOD14_021DC538
	cmp r0, #0
	beq _021D8590
	ldr r1, _021D86A8 ; =MOD14_021DA7C4
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D8590:
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	beq _021D85BA
	ldr r0, _021D86AC ; =0x000005F3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0x11
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D85BA:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x22
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D85CC:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x22
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D86A6
	ldr r0, _021D86B0 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0xb
	bl MOD14_021DBA44
	add r0, r4, #0
	mov r1, #1
	bl MOD14_021E5D98
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8604:
	bl MOD14_021E6160
	cmp r0, #0x36
	bgt _021D8624
	bge _021D8650
	mov r2, #0
	mvn r2, r2
	cmp r0, r2
	bgt _021D86A6
	sub r1, r2, #1
	cmp r0, r1
	blt _021D86A6
	beq _021D862A
	cmp r0, r2
	beq _021D8638
	pop {r3, r4, r5, pc}
_021D8624:
	cmp r0, #0x37
	beq _021D8638
	pop {r3, r4, r5, pc}
_021D862A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1c
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D8638:
	ldr r0, _021D86B0 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8650:
	ldr r1, _021D86B4 ; =MOD14_021D850C
	add r0, r4, #0
	bl MOD14_021D7600
	add r0, r4, #0
	bl MOD14_021D7620
	pop {r3, r4, r5, pc}
_021D8660:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D86A6
	mov r0, #5
	str r0, [r5]
_021D8674:
	ldr r0, _021D86B8 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D86A6
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8690:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D86A6
	add r0, r4, #0
	bl MOD14_021D7620
_021D86A6:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D86A8: .word MOD14_021DA7C4
_021D86AC: .word 0x000005F3
_021D86B0: .word 0x000005DD
_021D86B4: .word MOD14_021D850C
_021D86B8: .word 0x021C48B8

	thumb_func_start MOD14_021D86BC
MOD14_021D86BC: ; 0x021D86BC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #5
	bls _021D86CA
	b _021D87EC
_021D86CA:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D86D6: ; jump table
	.short _021D86E2 - _021D86D6 - 2 ; case 0
	.short _021D87EC - _021D86D6 - 2 ; case 1
	.short _021D87A6 - _021D86D6 - 2 ; case 2
	.short _021D87BA - _021D86D6 - 2 ; case 3
	.short _021D87D6 - _021D86D6 - 2 ; case 4
	.short _021D8750 - _021D86D6 - 2 ; case 5
_021D86E2:
	bl MOD14_021DC3F4
	cmp r0, #1
	beq _021D870A
	ldr r0, _021D87F0 ; =0x000005F3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0x11
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D870A:
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #3
	bne _021D8728
	add r0, r4, #0
	bl MOD14_021DC538
	cmp r0, #0
	beq _021D8728
	ldr r1, _021D87F4 ; =MOD14_021DA7C4
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D8728:
	ldr r0, _021D87F8 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0xc
	bl MOD14_021DBA44
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021E5D98
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB2C
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8750:
	bl MOD14_021E6160
	cmp r0, #0x36
	bgt _021D8770
	bge _021D8794
	mov r2, #0
	mvn r2, r2
	cmp r0, r2
	bgt _021D87EC
	sub r1, r2, #1
	cmp r0, r1
	blt _021D87EC
	beq _021D8776
	cmp r0, r2
	beq _021D8784
	pop {r3, r4, r5, pc}
_021D8770:
	cmp r0, #0x37
	beq _021D8784
	pop {r3, r4, r5, pc}
_021D8776:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1c
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D8784:
	ldr r1, _021D87FC ; =MOD14_021D850C
	add r0, r4, #0
	bl MOD14_021D7600
	add r0, r4, #0
	bl MOD14_021D7620
	pop {r3, r4, r5, pc}
_021D8794:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D87A6:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D87EC
	mov r0, #3
	str r0, [r5]
_021D87BA:
	ldr r0, _021D8800 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D87EC
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D87D6:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D87EC
	add r0, r4, #0
	bl MOD14_021D7620
_021D87EC:
	pop {r3, r4, r5, pc}
	nop
_021D87F0: .word 0x000005F3
_021D87F4: .word MOD14_021DA7C4
_021D87F8: .word 0x000005DD
_021D87FC: .word MOD14_021D850C
_021D8800: .word 0x021C48B8

	thumb_func_start MOD14_021D8804
MOD14_021D8804: ; 0x021D8804
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #5
	bhi _021D88F6
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D881C: ; jump table
	.short _021D8828 - _021D881C - 2 ; case 0
	.short _021D887C - _021D881C - 2 ; case 1
	.short _021D8890 - _021D881C - 2 ; case 2
	.short _021D88EA - _021D881C - 2 ; case 3
	.short _021D8A08 - _021D881C - 2 ; case 4
	.short _021D8A20 - _021D881C - 2 ; case 5
_021D8828:
	bl MOD14_021DC458
	add r2, r0, #0
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200ACF8
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021DBA44
	add r0, r4, #0
	bl MOD14_021E5DC4
	add r0, r4, #0
	bl MOD14_021DC49C
	cmp r0, #0
	beq _021D8864
	add r0, r4, #0
	bl MOD14_021E6220
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8864:
	ldr r0, _021D8A38 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D887C:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D88F6
	mov r0, #2
	str r0, [r5]
_021D8890:
	add r0, r4, #0
	bl MOD14_021E6160
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0
	ldr r2, [r4, r1]
	mvn r0, r0
	cmp r2, r0
	bgt _021D88BA
	sub r3, r0, #2
	cmp r2, r3
	blt _021D88E4
	beq _021D88F6
	sub r3, r0, #1
	cmp r2, r3
	beq _021D88C0
	cmp r2, r0
	beq _021D88CC
	b _021D88E4
_021D88BA:
	cmp r2, #0x2b
	beq _021D88CC
	b _021D88E4
_021D88C0:
	sub r1, #0xa4
	ldr r0, [r4, r1]
	mov r1, #0x1c
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D88CC:
	ldr r0, _021D8A38 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D88E4:
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D88EA:
	mov r1, #0x6e
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	sub r2, #0x22
	cmp r2, #0x13
	bls _021D88F8
_021D88F6:
	b _021D8A34
_021D88F8:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021D8904: ; jump table
	.short _021D892C - _021D8904 - 2 ; case 0
	.short _021D895E - _021D8904 - 2 ; case 1
	.short _021D8972 - _021D8904 - 2 ; case 2
	.short _021D89A6 - _021D8904 - 2 ; case 3
	.short _021D8986 - _021D8904 - 2 ; case 4
	.short _021D898E - _021D8904 - 2 ; case 5
	.short _021D89AE - _021D8904 - 2 ; case 6
	.short _021D8996 - _021D8904 - 2 ; case 7
	.short _021D899E - _021D8904 - 2 ; case 8
	.short _021D8A34 - _021D8904 - 2 ; case 9
	.short _021D8A34 - _021D8904 - 2 ; case 10
	.short _021D8A34 - _021D8904 - 2 ; case 11
	.short _021D8A34 - _021D8904 - 2 ; case 12
	.short _021D8A34 - _021D8904 - 2 ; case 13
	.short _021D8A34 - _021D8904 - 2 ; case 14
	.short _021D8A34 - _021D8904 - 2 ; case 15
	.short _021D8A34 - _021D8904 - 2 ; case 16
	.short _021D8A34 - _021D8904 - 2 ; case 17
	.short _021D89CA - _021D8904 - 2 ; case 18
	.short _021D89CA - _021D8904 - 2 ; case 19
_021D892C:
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021D8948
	add r0, r4, #0
	bl MOD14_021DC49C
	cmp r0, #1
	bne _021D8948
	ldr r1, _021D8A3C ; =MOD14_021D9230
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D8948:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	ldr r1, _021D8A40 ; =MOD14_021D94BC
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D895E:
	sub r1, #0xa4
	ldr r0, [r4, r1]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	ldr r1, _021D8A44 ; =MOD14_021D95B4
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D8972:
	sub r1, #0xa4
	ldr r0, [r4, r1]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	ldr r1, _021D8A48 ; =MOD14_021D96B0
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D8986:
	ldr r1, _021D8A4C ; =MOD14_021D9770
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D898E:
	ldr r1, _021D8A50 ; =MOD14_021D9934
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D8996:
	ldr r1, _021D8A54 ; =MOD14_021D9138
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D899E:
	ldr r1, _021D8A58 ; =MOD14_021D9C98
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D89A6:
	ldr r1, _021D8A5C ; =MOD14_021DA2C8
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D89AE:
	bl MOD14_021DC430
	cmp r0, #0
	bne _021D89C0
	ldr r1, _021D8A60 ; =MOD14_021DA3E4
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D89C0:
	ldr r1, _021D8A64 ; =MOD14_021DA5F0
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D89CA:
	bl MOD14_021DC170
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r4, #0
	bl MOD14_021DBE88
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x30
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	ldr r0, _021D8A38 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8A08:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D8A34
	add r0, r4, #0
	bl MOD14_021D7620
	pop {r3, r4, r5, pc}
_021D8A20:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D8A34
	add r0, r4, #0
	bl MOD14_021D7620
_021D8A34:
	pop {r3, r4, r5, pc}
	nop
_021D8A38: .word 0x000005DD
_021D8A3C: .word MOD14_021D9230
_021D8A40: .word MOD14_021D94BC
_021D8A44: .word MOD14_021D95B4
_021D8A48: .word MOD14_021D96B0
_021D8A4C: .word MOD14_021D9770
_021D8A50: .word MOD14_021D9934
_021D8A54: .word MOD14_021D9138
_021D8A58: .word MOD14_021D9C98
_021D8A5C: .word MOD14_021DA2C8
_021D8A60: .word MOD14_021DA3E4
_021D8A64: .word MOD14_021DA5F0

	thumb_func_start MOD14_021D8A68
MOD14_021D8A68: ; 0x021D8A68
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #7
	bls _021D8A76
	b _021D8D54
_021D8A76:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8A82: ; jump table
	.short _021D8A92 - _021D8A82 - 2 ; case 0
	.short _021D8B3C - _021D8A82 - 2 ; case 1
	.short _021D8B50 - _021D8A82 - 2 ; case 2
	.short _021D8BB0 - _021D8A82 - 2 ; case 3
	.short _021D8CE0 - _021D8A82 - 2 ; case 4
	.short _021D8CF8 - _021D8A82 - 2 ; case 5
	.short _021D8D24 - _021D8A82 - 2 ; case 6
	.short _021D8D3A - _021D8A82 - 2 ; case 7
_021D8A92:
	bl MOD14_021DC538
	add r2, r0, #0
	beq _021D8AB0
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200AE38
	add r0, r4, #0
	mov r1, #0x19
	bl MOD14_021DBA44
	b _021D8AD8
_021D8AB0:
	add r0, r4, #0
	bl MOD14_021DC430
	add r2, r0, #0
	beq _021D8AD0
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200AE38
	add r0, r4, #0
	mov r1, #0x19
	bl MOD14_021DBA44
	b _021D8AD8
_021D8AD0:
	add r0, r4, #0
	mov r1, #0x1c
	bl MOD14_021DBA44
_021D8AD8:
	add r0, r4, #0
	bl MOD14_021E5F04
	add r0, r4, #0
	bl MOD14_021DC584
	cmp r0, #0
	beq _021D8B08
	ldr r0, _021D8D58 ; =0x000005F3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0x22
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #7
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8B08:
	add r0, r4, #0
	bl MOD14_021DC49C
	cmp r0, #0
	beq _021D8B24
	add r0, r4, #0
	bl MOD14_021E6220
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8B24:
	ldr r0, _021D8D5C ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8B3C:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D8BBC
	mov r0, #2
	str r0, [r5]
_021D8B50:
	add r0, r4, #0
	bl MOD14_021E6160
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0
	ldr r2, [r4, r1]
	mvn r0, r0
	cmp r2, r0
	bgt _021D8B7A
	sub r3, r0, #2
	cmp r2, r3
	blt _021D8BA4
	beq _021D8BBC
	sub r3, r0, #1
	cmp r2, r3
	beq _021D8B80
	cmp r2, r0
	beq _021D8B8C
	b _021D8BA4
_021D8B7A:
	cmp r2, #0x33
	beq _021D8B8C
	b _021D8BA4
_021D8B80:
	sub r1, #0xa4
	ldr r0, [r4, r1]
	mov r1, #0x1c
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D8B8C:
	ldr r0, _021D8D5C ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8BA4:
	ldr r0, _021D8D5C ; =0x000005DD
	bl FUN_020054C8
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8BB0:
	mov r1, #0x6e
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	sub r1, #0x2e
	cmp r1, #4
	bls _021D8BBE
_021D8BBC:
	b _021D8D54
_021D8BBE:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8BCA: ; jump table
	.short _021D8BD4 - _021D8BCA - 2 ; case 0
	.short _021D8C12 - _021D8BCA - 2 ; case 1
	.short _021D8C74 - _021D8BCA - 2 ; case 2
	.short _021D8C7C - _021D8BCA - 2 ; case 3
	.short _021D8CD8 - _021D8BCA - 2 ; case 4
_021D8BD4:
	bl MOD14_021DC538
	cmp r0, #0
	beq _021D8C08
	add r0, r4, #0
	add r1, r4, #0
	bl MOD14_021DC31C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x14
	bl MOD14_021DCB2C
	ldr r0, _021D8D5C ; =0x000005DD
	bl FUN_020054C8
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8C08:
	ldr r1, _021D8D60 ; =MOD14_021DA3E4
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D8C12:
	bl MOD14_021DC430
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0206EA98
	cmp r0, #0
	beq _021D8C42
	ldr r0, _021D8D58 ; =0x000005F3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0x18
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #7
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8C42:
	add r0, r4, #0
	add r1, r4, #0
	bl MOD14_021DC2E4
	add r0, r4, #0
	bl MOD14_021D7674
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x13
	bl MOD14_021DCB2C
	ldr r0, _021D8D5C ; =0x000005DD
	bl FUN_020054C8
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8C74:
	ldr r1, _021D8D64 ; =MOD14_021DA9D0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D8C7C:
	bl MOD14_021DC430
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0206EA98
	cmp r0, #0
	beq _021D8CAC
	ldr r0, _021D8D58 ; =0x000005F3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0x18
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #7
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8CAC:
	add r0, r4, #0
	add r1, r4, #0
	bl MOD14_021DC334
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x15
	bl MOD14_021DCB2C
	ldr r0, _021D8D5C ; =0x000005DD
	bl FUN_020054C8
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8CD8:
	ldr r1, _021D8D68 ; =MOD14_021DA7C4
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D8CE0:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D8D54
	add r0, r4, #0
	bl MOD14_021D7620
	pop {r3, r4, r5, pc}
_021D8CF8:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D8D54
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x16
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8D24:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D8D54
	add r0, r4, #0
	bl MOD14_021D7620
	pop {r3, r4, r5, pc}
_021D8D3A:
	ldr r0, _021D8D6C ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D8D54
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
_021D8D54:
	pop {r3, r4, r5, pc}
	nop
_021D8D58: .word 0x000005F3
_021D8D5C: .word 0x000005DD
_021D8D60: .word MOD14_021DA3E4
_021D8D64: .word MOD14_021DA9D0
_021D8D68: .word MOD14_021DA7C4
_021D8D6C: .word 0x021C48B8

	thumb_func_start MOD14_021D8D70
MOD14_021D8D70: ; 0x021D8D70
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #7
	bls _021D8D7E
	b _021D8EB0
_021D8D7E:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8D8A: ; jump table
	.short _021D8D9A - _021D8D8A - 2 ; case 0
	.short _021D8DDE - _021D8D8A - 2 ; case 1
	.short _021D8DF2 - _021D8D8A - 2 ; case 2
	.short _021D8E42 - _021D8D8A - 2 ; case 3
	.short _021D8E82 - _021D8D8A - 2 ; case 4
	.short _021D8EB0 - _021D8D8A - 2 ; case 5
	.short _021D8EB0 - _021D8D8A - 2 ; case 6
	.short _021D8E9A - _021D8D8A - 2 ; case 7
_021D8D9A:
	mov r1, #7
	bl MOD14_021DBA44
	add r0, r4, #0
	bl MOD14_021E5F84
	add r0, r4, #0
	bl MOD14_021DC49C
	cmp r0, #0
	ldr r0, _021D8EB4 ; =0x000005DD
	beq _021D8DC8
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD14_021E6220
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8DC8:
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8DDE:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D8EB0
	mov r0, #2
	str r0, [r5]
_021D8DF2:
	add r0, r4, #0
	bl MOD14_021E6160
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	add r0, r0, #3
	cmp r0, #6
	bhi _021D8E3C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8E12: ; jump table
	.short _021D8EB0 - _021D8E12 - 2 ; case 0
	.short _021D8E20 - _021D8E12 - 2 ; case 1
	.short _021D8E2C - _021D8E12 - 2 ; case 2
	.short _021D8E3C - _021D8E12 - 2 ; case 3
	.short _021D8E3C - _021D8E12 - 2 ; case 4
	.short _021D8E3C - _021D8E12 - 2 ; case 5
	.short _021D8E2C - _021D8E12 - 2 ; case 6
_021D8E20:
	sub r1, #0xa4
	ldr r0, [r4, r1]
	mov r1, #0x1c
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D8E2C:
	sub r1, #0xa4
	ldr r0, [r4, r1]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8E3C:
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8E42:
	mov r1, #0x6e
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	cmp r2, #0
	beq _021D8E56
	cmp r2, #1
	beq _021D8E6A
	cmp r2, #2
	beq _021D8E7A
	pop {r3, r4, r5, pc}
_021D8E56:
	sub r1, #0xa4
	ldr r0, [r4, r1]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	ldr r1, _021D8EB8 ; =MOD14_021D8EC4
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D8E6A:
	sub r1, #0xa4
	ldr r0, [r4, r1]
	mov r1, #0x1b
	bl MOD14_021DCB2C
	mov r0, #7
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8E7A:
	ldr r1, _021D8EBC ; =MOD14_021DA1D4
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D8E82:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D8EB0
	add r0, r4, #0
	bl MOD14_021D7620
	pop {r3, r4, r5, pc}
_021D8E9A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D8EB0
	ldr r1, _021D8EC0 ; =MOD14_021D8F6C
	add r0, r4, #0
	bl MOD14_021D7610
_021D8EB0:
	pop {r3, r4, r5, pc}
	nop
_021D8EB4: .word 0x000005DD
_021D8EB8: .word MOD14_021D8EC4
_021D8EBC: .word MOD14_021DA1D4
_021D8EC0: .word MOD14_021D8F6C

	thumb_func_start MOD14_021D8EC4
MOD14_021D8EC4: ; 0x021D8EC4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #0
	beq _021D8EDA
	cmp r1, #1
	beq _021D8EEE
	cmp r1, #2
	beq _021D8F52
	pop {r4, r5, r6, pc}
_021D8EDA:
	bl MOD14_021DC424
	add r1, r0, #0
	add r0, r5, #0
	mov r2, #8
	bl MOD14_021DAA7C
	mov r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021D8EEE:
	bl MOD14_021DAAA8
	cmp r0, #0
	beq _021D8F66
	ldr r0, _021D8F68 ; =0x000001C1
	ldrsb r6, [r5, r0]
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	beq _021D8F0C
	add r0, r5, #0
	bl MOD14_021DC424
	cmp r6, r0
	bne _021D8F12
_021D8F0C:
	mov r0, #2
	str r0, [r4]
	b _021D8F38
_021D8F12:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD14_021DC2C4
	mov r1, #0x12
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, #0xa1
	ldrsb r1, [r5, r1]
	bl FUN_0206B428
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #4
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r4]
_021D8F38:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x20
	bl MOD14_021DCB2C
	pop {r4, r5, r6, pc}
_021D8F52:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D8F66
	add r0, r5, #0
	bl MOD14_021D7620
_021D8F66:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8F68: .word 0x000001C1

	thumb_func_start MOD14_021D8F6C
MOD14_021D8F6C: ; 0x021D8F6C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #8
	bhi _021D8FD8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8F84: ; jump table
	.short _021D8F96 - _021D8F84 - 2 ; case 0
	.short _021D8FA2 - _021D8F84 - 2 ; case 1
	.short _021D8FC8 - _021D8F84 - 2 ; case 2
	.short _021D8FDE - _021D8F84 - 2 ; case 3
	.short _021D9062 - _021D8F84 - 2 ; case 4
	.short _021D9076 - _021D8F84 - 2 ; case 5
	.short _021D90FC - _021D8F84 - 2 ; case 6
	.short _021D910E - _021D8F84 - 2 ; case 7
	.short _021D9122 - _021D8F84 - 2 ; case 8
_021D8F96:
	mov r0, #0x6e
	mov r1, #4
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #1
	str r0, [r5]
_021D8FA2:
	add r0, r4, #0
	mov r1, #9
	bl MOD14_021DBA44
	mov r1, #0x6e
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add r0, r4, #0
	bl MOD14_021E5FC8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8FC8:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB98
	cmp r0, #0
	bne _021D8FDA
_021D8FD8:
	b _021D9136
_021D8FDA:
	mov r0, #3
	str r0, [r5]
_021D8FDE:
	add r0, r4, #0
	bl MOD14_021E6160
	add r0, r0, #3
	cmp r0, #0xc
	bhi _021D901E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8FF6: ; jump table
	.short _021D9136 - _021D8FF6 - 2 ; case 0
	.short _021D9010 - _021D8FF6 - 2 ; case 1
	.short _021D901E - _021D8FF6 - 2 ; case 2
	.short _021D901E - _021D8FF6 - 2 ; case 3
	.short _021D901E - _021D8FF6 - 2 ; case 4
	.short _021D901E - _021D8FF6 - 2 ; case 5
	.short _021D901E - _021D8FF6 - 2 ; case 6
	.short _021D9030 - _021D8FF6 - 2 ; case 7
	.short _021D9030 - _021D8FF6 - 2 ; case 8
	.short _021D9030 - _021D8FF6 - 2 ; case 9
	.short _021D9030 - _021D8FF6 - 2 ; case 10
	.short _021D9030 - _021D8FF6 - 2 ; case 11
	.short _021D9030 - _021D8FF6 - 2 ; case 12
_021D9010:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1c
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D901E:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #8
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9030:
	add r0, r4, #0
	bl MOD14_021E6210
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	mov r1, #0xa
	bl MOD14_021DBA44
	mov r1, #0x6e
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add r0, r4, #0
	bl MOD14_021E6038
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9062:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9136
	mov r0, #5
	str r0, [r5]
_021D9076:
	add r0, r4, #0
	bl MOD14_021E6160
	add r0, r0, #3
	cmp r0, #6
	bhi _021D90B0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D908E: ; jump table
	.short _021D9136 - _021D908E - 2 ; case 0
	.short _021D909C - _021D908E - 2 ; case 1
	.short _021D90AA - _021D908E - 2 ; case 2
	.short _021D90B0 - _021D908E - 2 ; case 3
	.short _021D90B0 - _021D908E - 2 ; case 4
	.short _021D90B0 - _021D908E - 2 ; case 5
	.short _021D90AA - _021D908E - 2 ; case 6
_021D909C:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1c
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D90AA:
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D90B0:
	add r0, r4, #0
	bl MOD14_021E6210
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r2, [r4, r1]
	cmp r2, #0xa
	blt _021D90F2
	cmp r2, #0x21
	bgt _021D90F2
	sub r1, #0x98
	ldr r0, [r4, r1]
	mov r1, #0
	mvn r1, r1
	sub r2, #0xa
	bl FUN_0206B458
	mov r1, #0x12
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	add r0, r4, #0
	bl MOD14_021DB59C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D90F2:
	bl ErrorHandling
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D90FC:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x21
	bl MOD14_021DCB2C
	mov r0, #8
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D910E:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9136
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9122:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9136
	add r0, r4, #0
	bl MOD14_021D7620
_021D9136:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021D9138
MOD14_021D9138: ; 0x021D9138
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #0
	beq _021D914E
	cmp r1, #1
	beq _021D916C
	cmp r1, #2
	beq _021D921A
	pop {r3, r4, r5, pc}
_021D914E:
	bl MOD14_021E60B4
	add r0, r5, #0
	mov r1, #1
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x19
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D916C:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D922E
	add r0, r5, #0
	bl MOD14_021E6160
	mov r2, #2
	add r1, r0, #0
	mvn r2, r2
	cmp r1, r2
	bhi _021D919C
	bhs _021D922E
	cmp r1, #0x2d
	bhi _021D91FC
	cmp r1, #0x2c
	blo _021D91FC
	beq _021D91CC
	cmp r1, #0x2d
	beq _021D91BA
	b _021D91FC
_021D919C:
	add r0, r2, #1
	cmp r1, r0
	blo _021D91FC
	beq _021D91AC
	add r0, r2, #2
	cmp r1, r0
	beq _021D91BA
	b _021D91FC
_021D91AC:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1c
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D91BA:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D91CC:
	add r0, r5, #0
	bl MOD14_021DC1AC
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #7
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x27
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D91FC:
	cmp r1, #0x38
	blo _021D922E
	cmp r1, #0x3d
	bhi _021D922E
	add r0, r5, #0
	sub r1, #0x38
	bl MOD14_021E6118
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1d
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D921A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D922E
	add r0, r5, #0
	bl MOD14_021D7620
_021D922E:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021D9230
MOD14_021D9230: ; 0x021D9230
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #4
	bls _021D923E
	b _021D9454
_021D923E:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D924A: ; jump table
	.short _021D9254 - _021D924A - 2 ; case 0
	.short _021D9284 - _021D924A - 2 ; case 1
	.short _021D9326 - _021D924A - 2 ; case 2
	.short _021D942C - _021D924A - 2 ; case 3
	.short _021D9440 - _021D924A - 2 ; case 4
_021D9254:
	ldr r1, _021D9458 ; =0x021C48B8
	ldr r2, [r1, #0x44]
	mov r1, #1
	tst r1, r2
	beq _021D927C
	add r1, r4, #0
	bl MOD14_021DBBD0
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x2c
	bl MOD14_021DCB2C
	ldr r0, _021D945C ; =0x000005DC
	bl FUN_020054C8
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D927C:
	ldr r1, _021D9460 ; =MOD14_021D94BC
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D9284:
	ldr r1, _021D9458 ; =0x021C48B8
	ldr r2, [r1, #0x44]
	mov r1, #1
	tst r1, r2
	beq _021D92E8
	add r0, r2, #0
	add r1, r4, #0
	bl MOD14_021DB790
	cmp r0, #1
	beq _021D92B6
	cmp r0, #2
	bne _021D9342
	ldr r1, _021D9458 ; =0x021C48B8
	mov r0, #0xf0
	ldr r2, [r1, #0x44]
	ldr r1, [r1, #0x48]
	and r2, r0
	and r0, r1
	cmp r2, r0
	bne _021D9342
	ldr r0, _021D9464 ; =0x000005F3
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
_021D92B6:
	add r0, r4, #0
	add r1, r4, #0
	bl MOD14_021DBBEC
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x2e
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D92E8:
	bl MOD14_021DC4DC
	cmp r0, #0
	beq _021D9306
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x2d
	bl MOD14_021DCB2C
	ldr r1, _021D9460 ; =MOD14_021D94BC
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, pc}
_021D9306:
	add r0, r4, #0
	add r1, r4, #0
	bl MOD14_021DBAE0
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x2f
	bl MOD14_021DCB2C
	ldr r0, _021D9468 ; =0x000005EB
	bl FUN_020054C8
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9326:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9342
	ldr r0, _021D9458 ; =0x021C48B8
	add r1, r4, #0
	ldr r0, [r0, #0x44]
	bl MOD14_021DB790
	cmp r0, #4
	bls _021D9344
_021D9342:
	b _021D9454
_021D9344:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9350: ; jump table
	.short _021D93E2 - _021D9350 - 2 ; case 0
	.short _021D9372 - _021D9350 - 2 ; case 1
	.short _021D935A - _021D9350 - 2 ; case 2
	.short _021D9396 - _021D9350 - 2 ; case 3
	.short _021D93BC - _021D9350 - 2 ; case 4
_021D935A:
	ldr r1, _021D9458 ; =0x021C48B8
	mov r0, #0xf0
	ldr r2, [r1, #0x44]
	ldr r1, [r1, #0x48]
	and r2, r0
	and r0, r1
	cmp r2, r0
	bne _021D9454
	ldr r0, _021D9464 ; =0x000005F3
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
_021D9372:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB2C
	add r0, r4, #0
	bl MOD14_021DC3F4
	mov r1, #6
	tst r0, r1
	bne _021D9454
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D9396:
	add r0, r4, #0
	bl MOD14_021DC2A4
	add r0, r4, #0
	bl MOD14_021DC424
	add r1, r0, #0
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_0206B428
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #4
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D93BC:
	add r0, r4, #0
	bl MOD14_021DC278
	add r0, r4, #0
	bl MOD14_021DC424
	add r1, r0, #0
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_0206B428
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #4
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D93E2:
	ldr r0, _021D9458 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _021D941E
	add r0, r4, #0
	bl MOD14_021D9470
	cmp r0, #0
	beq _021D9416
	add r0, r4, #0
	add r1, r4, #0
	bl MOD14_021DBCA0
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xa
	bl MOD14_021DCB2C
	ldr r0, _021D946C ; =0x000005EA
	bl FUN_020054C8
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9416:
	ldr r0, _021D9464 ; =0x000005F3
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
_021D941E:
	mov r0, #2
	tst r0, r1
	beq _021D9454
	ldr r0, _021D9464 ; =0x000005F3
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
_021D942C:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9454
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9440:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9454
	add r0, r4, #0
	bl MOD14_021D7620
_021D9454:
	pop {r3, r4, r5, pc}
	nop
_021D9458: .word 0x021C48B8
_021D945C: .word 0x000005DC
_021D9460: .word MOD14_021D94BC
_021D9464: .word 0x000005F3
_021D9468: .word 0x000005EB
_021D946C: .word 0x000005EA

	thumb_func_start MOD14_021D9470
MOD14_021D9470: ; 0x021D9470
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r5, #0x14
	str r0, [sp]
	bl MOD14_021DC4F8
	add r7, r0, #0
	ldrb r0, [r5, #8]
	mov r4, #0
	ldrb r6, [r5, #9]
	cmp r0, #0
	ble _021D94B6
_021D9488:
	add r3, r5, r4
	mov r2, #0xc
	ldrsb r2, [r3, r2]
	ldr r0, [sp]
	mov r1, #0
	sub r2, r2, r6
	ldr r0, [r0]
	mvn r1, r1
	add r2, r7, r2
	bl FUN_0206B5E4
	mov r1, #0xab
	mov r2, #0
	bl FUN_020672BC
	cmp r0, #0
	beq _021D94AE
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D94AE:
	ldrb r0, [r5, #8]
	add r4, r4, #1
	cmp r4, r0
	blt _021D9488
_021D94B6:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021D94BC
MOD14_021D94BC: ; 0x021D94BC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #3
	bhi _021D95A4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D94D4: ; jump table
	.short _021D94DC - _021D94D4 - 2 ; case 0
	.short _021D954E - _021D94D4 - 2 ; case 1
	.short _021D9574 - _021D94D4 - 2 ; case 2
	.short _021D9590 - _021D94D4 - 2 ; case 3
_021D94DC:
	bl MOD14_021DC3CC
	cmp r0, #1
	bne _021D952E
	add r0, r4, #0
	bl MOD14_021D9B84
	cmp r0, #0
	bne _021D950E
	ldr r0, _021D95A8 ; =0x000005EB
	bl FUN_020054C8
	add r0, r4, #0
	add r1, r4, #0
	bl MOD14_021DBA5C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #9
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D950E:
	ldr r0, _021D95AC ; =0x000005F3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #6
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D952E:
	ldr r0, _021D95A8 ; =0x000005EB
	bl FUN_020054C8
	add r0, r4, #0
	add r1, r4, #0
	bl MOD14_021DBA5C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #9
	bl MOD14_021DCB2C
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D954E:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D95A4
	add r0, r4, #0
	bl MOD14_021DB934
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x25
	bl MOD14_021DCB2C
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9574:
	ldr r0, _021D95B0 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D95A4
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9590:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D95A4
	add r0, r4, #0
	bl MOD14_021D7620
_021D95A4:
	pop {r3, r4, r5, pc}
	nop
_021D95A8: .word 0x000005EB
_021D95AC: .word 0x000005F3
_021D95B0: .word 0x021C48B8

	thumb_func_start MOD14_021D95B4
MOD14_021D95B4: ; 0x021D95B4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #0
	beq _021D95CA
	cmp r1, #1
	beq _021D9616
	cmp r1, #2
	beq _021D9648
	pop {r4, r5, r6, pc}
_021D95CA:
	add r1, r5, #0
	bl MOD14_021DBC00
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0xa
	bl MOD14_021DCB2C
	ldr r0, _021D9664 ; =0x000005EA
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD14_021DC3CC
	cmp r0, #1
	bne _021D9610
	add r0, r5, #0
	bl MOD14_021DC3E8
	add r6, r0, #0
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0206B9AC
	sub r0, r0, #1
	cmp r6, r0
	beq _021D9610
	mov r0, #1
	str r0, [r4]
	add r0, r5, #0
	bl MOD14_021DB934
	pop {r4, r5, r6, pc}
_021D9610:
	mov r0, #2
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021D9616:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9662
	add r0, r5, #0
	bl MOD14_021DB934
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x26
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021D9648:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9662
	add r0, r5, #0
	bl MOD14_021D7674
	add r0, r5, #0
	bl MOD14_021D7620
_021D9662:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D9664: .word 0x000005EA

	thumb_func_start MOD14_021D9668
MOD14_021D9668: ; 0x021D9668
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD14_021D9B84
	cmp r0, #0
	beq _021D96AC
	add r0, r5, #0
	mov r1, #0xac
	mov r2, #0
	bl MOD14_021DC58C
	cmp r0, #0
	beq _021D968C
	mov r0, #6
	str r0, [r4]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D968C:
	add r0, r5, #0
	bl MOD14_021DC3F8
	cmp r0, #0
	beq _021D96AC
	add r0, r5, #0
	mov r1, #0xa2
	mov r2, #0
	bl MOD14_021DC58C
	cmp r0, #0
	bne _021D96AC
	mov r0, #6
	str r0, [r4]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D96AC:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021D96B0
MOD14_021D96B0: ; 0x021D96B0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #0
	beq _021D96C6
	cmp r1, #1
	beq _021D971C
	cmp r1, #2
	beq _021D9748
	pop {r3, r4, r5, pc}
_021D96C6:
	add r1, sp, #0
	bl MOD14_021D9668
	cmp r0, #0
	beq _021D96F0
	ldr r0, _021D9764 ; =0x000005F3
	bl FUN_020054C8
	ldr r1, [sp]
	add r0, r5, #0
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D96F0:
	add r0, r5, #0
	add r1, r5, #0
	bl MOD14_021DBD34
	ldr r0, _021D9768 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0xb
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D971C:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x18
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9762
	ldr r0, _021D976C ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D9762
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D9748:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9762
	add r0, r5, #0
	bl MOD14_021D7674
	add r0, r5, #0
	bl MOD14_021D7620
_021D9762:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D9764: .word 0x000005F3
_021D9768: .word 0x000005DC
_021D976C: .word 0x021C48B8

	thumb_func_start MOD14_021D9770
MOD14_021D9770: ; 0x021D9770
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #8
	bls _021D977E
	b _021D9928
_021D977E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D978A: ; jump table
	.short _021D979C - _021D978A - 2 ; case 0
	.short _021D9818 - _021D978A - 2 ; case 1
	.short _021D983A - _021D978A - 2 ; case 2
	.short _021D9862 - _021D978A - 2 ; case 3
	.short _021D9892 - _021D978A - 2 ; case 4
	.short _021D98B4 - _021D978A - 2 ; case 5
	.short _021D9928 - _021D978A - 2 ; case 6
	.short _021D98E8 - _021D978A - 2 ; case 7
	.short _021D9914 - _021D978A - 2 ; case 8
_021D979C:
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0206B9AC
	cmp r0, #6
	beq _021D97F2
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #2
	bne _021D97D2
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x23
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D97D2:
	ldr r0, _021D992C ; =0x000005EB
	bl FUN_020054C8
	add r0, r4, #0
	add r1, r4, #0
	bl MOD14_021DBA5C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #9
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D97F2:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1b
	bl MOD14_021DCB2C
	add r0, r4, #0
	mov r1, #5
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #7
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9818:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #9
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9928
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x23
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D983A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x23
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9928
	add r0, r4, #0
	bl MOD14_021DB8D0
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB2C
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9862:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9928
	add r0, r4, #0
	add r1, r4, #0
	bl MOD14_021DBC00
	add r0, r4, #0
	bl MOD14_021D7674
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xa
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9892:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xa
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9928
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x24
	bl MOD14_021DCB2C
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D98B4:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x24
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9928
	add r0, r4, #0
	bl MOD14_021DB910
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #8
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D98E8:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9928
	ldr r0, _021D9930 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D9928
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #8
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9914:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9928
	add r0, r4, #0
	bl MOD14_021D7620
_021D9928:
	pop {r3, r4, r5, pc}
	nop
_021D992C: .word 0x000005EB
_021D9930: .word 0x021C48B8

	thumb_func_start MOD14_021D9934
MOD14_021D9934: ; 0x021D9934
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #6
	bhi _021D99F8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D994C: ; jump table
	.short _021D995A - _021D994C - 2 ; case 0
	.short _021D99F0 - _021D994C - 2 ; case 1
	.short _021D9AB2 - _021D994C - 2 ; case 2
	.short _021D9AD8 - _021D994C - 2 ; case 3
	.short _021D9B04 - _021D994C - 2 ; case 4
	.short _021D9B32 - _021D994C - 2 ; case 5
	.short _021D9B60 - _021D994C - 2 ; case 6
_021D995A:
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021D9998
	add r0, r4, #0
	bl MOD14_021D9B84
	cmp r0, #1
	bne _021D9998
	ldr r0, _021D9B78 ; =0x000005F3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #6
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1b
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9998:
	add r0, r4, #0
	add r1, sp, #0
	bl MOD14_021D7998
	cmp r0, #0
	beq _021D99D0
	ldr r0, _021D9B78 ; =0x000005F3
	bl FUN_020054C8
	ldr r1, [sp]
	add r0, r4, #0
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1b
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D99D0:
	mov r1, #0x11
	lsl r1, r1, #4
	ldrh r1, [r4, r1]
	add r0, r4, #0
	mov r2, #0x13
	bl MOD14_021DAA7C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D99F0:
	bl MOD14_021DAAA8
	cmp r0, #0
	bne _021D99FA
_021D99F8:
	b _021D9B74
_021D99FA:
	ldr r0, _021D9B7C ; =0x000001C1
	mov r1, #0
	ldrsb r2, [r4, r0]
	mvn r1, r1
	cmp r2, r1
	bne _021D9A22
	sub r0, #0xad
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x20
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9A22:
	sub r0, #0xb1
	strh r2, [r4, r0]
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #2
	ldr r1, _021D9B7C ; =0x000001C1
	bne _021D9A62
	ldrsb r1, [r4, r1]
	add r0, r4, #0
	bl MOD14_021DBDD8
	cmp r0, #0
	beq _021D9A92
	add r0, r4, #0
	bl MOD14_021D7674
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x20
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9A62:
	ldrsb r1, [r4, r1]
	add r0, r4, #0
	bl MOD14_021DBE00
	cmp r0, #0
	beq _021D9A92
	add r0, r4, #0
	bl MOD14_021D7674
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x20
	bl MOD14_021DCB2C
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9A92:
	ldr r0, _021D9B78 ; =0x000005F3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0xd
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9AB2:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9B74
	ldr r0, _021D9B80 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D9B74
	add r0, r4, #0
	bl MOD14_021DAA98
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9AD8:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9B74
	ldr r0, _021D9B80 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D9B74
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9B04:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x20
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9B74
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xc
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9B32:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x20
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9B74
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xd
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9B60:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9B74
	add r0, r4, #0
	bl MOD14_021D7620
_021D9B74:
	pop {r3, r4, r5, pc}
	nop
_021D9B78: .word 0x000005F3
_021D9B7C: .word 0x000001C1
_021D9B80: .word 0x021C48B8

	thumb_func_start MOD14_021D9B84
MOD14_021D9B84: ; 0x021D9B84
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r1, #0x49
	lsl r1, r1, #2
	str r0, [sp]
	ldr r0, [r0, r1]
	bl FUN_0206B9AC
	mov r6, #0
	add r5, r6, #0
	str r0, [sp, #4]
	cmp r0, #0
	ble _021D9BEC
_021D9B9E:
	mov r0, #0x49
	ldr r1, [sp]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl FUN_0206B9B0
	add r4, r0, #0
	bl FUN_020669D4
	add r7, r0, #0
	add r0, r4, #0
	mov r1, #0xac
	mov r2, #0
	bl FUN_020671BC
	cmp r0, #0
	bne _021D9BD2
	add r0, r4, #0
	mov r1, #0xa2
	mov r2, #0
	bl FUN_020671BC
	cmp r0, #0
	beq _021D9BD2
	add r5, r5, #1
_021D9BD2:
	add r0, r4, #0
	add r1, r7, #0
	bl FUN_02066A20
	cmp r5, #2
	blt _021D9BE4
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D9BE4:
	ldr r0, [sp, #4]
	add r6, r6, #1
	cmp r6, r0
	blt _021D9B9E
_021D9BEC:
	ldr r0, [sp]
	mov r1, #0xac
	mov r2, #0
	bl MOD14_021DC5D0
	cmp r0, #0
	beq _021D9C00
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D9C00:
	ldr r0, [sp]
	mov r1, #0xa2
	mov r2, #0
	bl MOD14_021DC5D0
	cmp r0, #0
	beq _021D9C14
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9C14:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021D9C1C
MOD14_021D9C1C: ; 0x021D9C1C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0xac
	mov r2, #0
	add r5, r0, #0
	bl MOD14_021DC58C
	cmp r0, #0
	beq _021D9C36
	mov r0, #0x1f
	str r0, [r4]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D9C36:
	add r0, r5, #0
	bl MOD14_021DC430
	add r0, r5, #0
	bl MOD14_021DC430
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0206EA98
	cmp r0, #0
	beq _021D9C56
	mov r0, #0x1e
	str r0, [r4]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D9C56:
	add r0, r5, #0
	mov r1, #0xa1
	mov r2, #0
	bl MOD14_021DC58C
	cmp r0, #0
	beq _021D9C6C
	mov r0, #0x1d
	str r0, [r4]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D9C6C:
	add r0, r5, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021D9C92
	add r0, r5, #0
	bl MOD14_021DC3CC
	cmp r0, #1
	bne _021D9C92
	add r0, r5, #0
	bl MOD14_021D9B84
	cmp r0, #0
	beq _021D9C92
	mov r0, #6
	str r0, [r4]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D9C92:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021D9C98
MOD14_021D9C98: ; 0x021D9C98
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #9
	bhi _021D9D44
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D9CB0: ; jump table
	.short _021D9CC4 - _021D9CB0 - 2 ; case 0
	.short _021D9D1C - _021D9CB0 - 2 ; case 1
	.short _021D9D86 - _021D9CB0 - 2 ; case 2
	.short _021D9E0A - _021D9CB0 - 2 ; case 3
	.short _021D9E96 - _021D9CB0 - 2 ; case 4
	.short _021D9E62 - _021D9CB0 - 2 ; case 5
	.short _021D9EC8 - _021D9CB0 - 2 ; case 6
	.short _021D9EF2 - _021D9CB0 - 2 ; case 7
	.short _021D9F36 - _021D9CB0 - 2 ; case 8
	.short _021D9F62 - _021D9CB0 - 2 ; case 9
_021D9CC4:
	add r1, sp, #0
	bl MOD14_021D9C1C
	cmp r0, #0
	beq _021D9CF0
	add r0, r4, #0
	mov r1, #2
	bl MOD14_021DBA44
	add r0, r4, #0
	mov r1, #1
	bl MOD14_021E5D98
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9CF0:
	ldr r0, _021D9F78 ; =0x000005F3
	bl FUN_020054C8
	ldr r1, [sp]
	add r0, r4, #0
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1b
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #8
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9D1C:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9D44
	add r0, r4, #0
	bl MOD14_021E6160
	cmp r0, #0x36
	bgt _021D9D4E
	bge _021D9D74
	mov r2, #0
	mvn r2, r2
	cmp r0, r2
	bgt _021D9D44
	sub r1, r2, #1
	cmp r0, r1
	bge _021D9D46
_021D9D44:
	b _021D9F76
_021D9D46:
	beq _021D9D54
	cmp r0, r2
	beq _021D9D62
	pop {r3, r4, r5, pc}
_021D9D4E:
	cmp r0, #0x37
	beq _021D9D62
	pop {r3, r4, r5, pc}
_021D9D54:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1c
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D9D62:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #9
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9D74:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9D86:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9E70
	add r0, r4, #0
	bl MOD14_021DC458
	add r2, r0, #0
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200ACF8
	add r0, r4, #0
	bl MOD14_021D9F80
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #2
	bne _021D9DD0
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xe
	bl MOD14_021DCB2C
	mov r0, #0x6e
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021D9E04
_021D9DD0:
	add r0, r4, #0
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021D9DF0
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xf
	bl MOD14_021DCB2C
	mov r0, #0x6e
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021D9E04
_021D9DF0:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x10
	bl MOD14_021DCB2C
	mov r0, #0x6e
	mov r1, #2
	lsl r0, r0, #2
	str r1, [r4, r0]
_021D9E04:
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9E0A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9E70
	add r0, r4, #0
	bl MOD14_021DA1C0
	cmp r0, #0
	beq _021D9E48
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #2
	bne _021D9E34
	add r0, r4, #0
	bl MOD14_021DBE34
	b _021D9E3A
_021D9E34:
	add r0, r4, #0
	bl MOD14_021DBE4C
_021D9E3A:
	add r0, r4, #0
	mov r1, #3
	bl MOD14_021DBA44
	mov r0, #5
	str r0, [r5]
	b _021D9E54
_021D9E48:
	add r0, r4, #0
	mov r1, #0x20
	bl MOD14_021DBA44
	mov r0, #4
	str r0, [r5]
_021D9E54:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021D9E62:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	bne _021D9E72
_021D9E70:
	b _021D9F76
_021D9E72:
	ldr r0, _021D9F7C ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D9F76
	add r0, r4, #0
	mov r1, #4
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9E96:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9F76
	ldr r0, _021D9F7C ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D9F76
	add r0, r4, #0
	mov r1, #0x21
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9EC8:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9F76
	ldr r0, _021D9F7C ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D9F76
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #7
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9EF2:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9F76
	add r0, r4, #0
	bl MOD14_021DA1C0
	cmp r0, #0
	beq _021D9F24
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #2
	bne _021D9F1E
	sub r0, #0xa4
	ldr r0, [r4, r0]
	mov r1, #0x25
	bl MOD14_021DCB2C
_021D9F1E:
	add r0, r4, #0
	bl MOD14_021D7674
_021D9F24:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #9
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9F36:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021D9F76
	ldr r0, _021D9F7C ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D9F76
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #9
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D9F62:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021D9F76
	add r0, r4, #0
	bl MOD14_021D7620
_021D9F76:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D9F78: .word 0x000005F3
_021D9F7C: .word 0x021C48B8

	thumb_func_start MOD14_021D9F80
MOD14_021D9F80: ; 0x021D9F80
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r1, #0x57
	lsl r1, r1, #2
	str r0, [sp]
	add r7, r0, r1
	ldr r0, [r0, #0x4c]
	mov r4, #0
	ldr r5, _021DA010 ; =0x021E6224
	str r0, [r7, #0x10]
	str r4, [sp, #4]
_021D9F96:
	ldrh r1, [r5]
	ldr r0, [r7, #0x10]
	add r6, r7, r4
	bl MOD14_021DA168
	strb r0, [r6, #4]
	ldrb r0, [r6, #4]
	cmp r0, #0
	beq _021D9FAE
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
_021D9FAE:
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #3
	blo _021D9F96
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _021D9FC6
	mov r0, #1
	strb r0, [r7]
	add sp, #8
	strb r0, [r7, #1]
	pop {r3, r4, r5, r6, r7, pc}
_021D9FC6:
	mov r0, #0
	strb r0, [r7]
	strb r0, [r7, #1]
	strb r0, [r7, #2]
	strb r0, [r7, #3]
	mov r1, #0x12
	ldr r0, [sp]
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	add r1, r1, #4
	str r0, [r7, #0x14]
	ldr r0, [sp]
	ldr r0, [r0, r1]
	str r0, [r7, #0x18]
	ldr r0, [sp]
	bl MOD14_021DC3F4
	cmp r0, #1
	beq _021D9FF0
	mov r0, #1
	b _021D9FF2
_021D9FF0:
	mov r0, #0
_021D9FF2:
	mov r1, #0
	str r0, [r7, #0x1c]
	add r0, r7, #0
	add r2, r1, #0
_021D9FFA:
	add r1, r1, #1
	strh r2, [r0, #8]
	add r0, r0, #2
	cmp r1, #3
	blo _021D9FFA
	ldr r0, _021DA014 ; =MOD14_021DA018
	add r1, r7, #0
	bl FUN_0200CA44
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DA010: .word 0x021E6224
_021DA014: .word MOD14_021DA018

	thumb_func_start MOD14_021DA018
MOD14_021DA018: ; 0x021DA018
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp]
	ldrb r0, [r1, #2]
	str r1, [sp, #4]
	cmp r0, #0x12
	bhs _021DA0AE
	add r0, r1, #0
	ldrb r0, [r0, #3]
	str r0, [sp, #0xc]
	str r0, [sp, #0x14]
	add r0, #0xf
	str r0, [sp, #0x14]
	cmp r0, #0x1e
	ble _021DA03A
	mov r0, #0x1e
	str r0, [sp, #0x14]
_021DA03A:
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bge _021DA08C
_021DA042:
	ldr r1, [sp, #4]
	ldr r0, [sp, #4]
	ldrb r1, [r1, #2]
	ldr r0, [r0, #0x14]
	ldr r2, [sp, #0xc]
	bl FUN_0206B5E4
	mov r1, #0xab
	mov r2, #0
	add r7, r0, #0
	bl FUN_020672BC
	cmp r0, #0
	beq _021DA080
	ldr r4, _021DA164 ; =0x021E6224
	ldr r5, [sp, #4]
	mov r6, #0
_021DA064:
	ldrh r1, [r4]
	add r0, r7, #0
	bl MOD14_021DA168
	cmp r0, #0
	beq _021DA076
	ldrh r0, [r5, #8]
	add r0, r0, #1
	strh r0, [r5, #8]
_021DA076:
	add r6, r6, #1
	add r4, r4, #2
	add r5, r5, #2
	cmp r6, #3
	blo _021DA064
_021DA080:
	ldr r0, [sp, #0xc]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [sp, #0xc]
	cmp r1, r0
	blt _021DA042
_021DA08C:
	ldr r0, [sp, #0x14]
	cmp r0, #0x1e
	bne _021DA0A4
	ldr r0, [sp, #4]
	mov r1, #0
	strb r1, [r0, #3]
	ldrb r0, [r0, #2]
	add r1, r0, #1
	ldr r0, [sp, #4]
	add sp, #0x18
	strb r1, [r0, #2]
	pop {r3, r4, r5, r6, r7, pc}
_021DA0A4:
	add r1, r0, #0
	ldr r0, [sp, #4]
	add sp, #0x18
	strb r1, [r0, #3]
	pop {r3, r4, r5, r6, r7, pc}
_021DA0AE:
	add r0, r1, #0
	ldr r0, [r0, #0x18]
	bl FUN_0206B9AC
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x10]
	cmp r0, #0
	ble _021DA0FC
_021DA0C2:
	ldr r0, [sp, #4]
	ldr r1, [sp, #8]
	ldr r0, [r0, #0x18]
	bl FUN_0206B9B0
	ldr r4, _021DA164 ; =0x021E6224
	ldr r5, [sp, #4]
	add r7, r0, #0
	mov r6, #0
_021DA0D4:
	ldrh r1, [r4]
	add r0, r7, #0
	bl MOD14_021DA168
	cmp r0, #0
	beq _021DA0E6
	ldrh r0, [r5, #8]
	add r0, r0, #1
	strh r0, [r5, #8]
_021DA0E6:
	add r6, r6, #1
	add r4, r4, #2
	add r5, r5, #2
	cmp r6, #3
	blo _021DA0D4
	ldr r0, [sp, #8]
	add r1, r0, #1
	ldr r0, [sp, #0x10]
	str r1, [sp, #8]
	cmp r1, r0
	blt _021DA0C2
_021DA0FC:
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x1c]
	cmp r0, #0
	beq _021DA128
	ldr r4, _021DA164 ; =0x021E6224
	ldr r5, [sp, #4]
	mov r6, #0
_021DA10A:
	ldr r0, [sp, #4]
	ldrh r1, [r4]
	ldr r0, [r0, #0x10]
	bl MOD14_021DA168
	cmp r0, #0
	beq _021DA11E
	ldrh r0, [r5, #8]
	add r0, r0, #1
	strh r0, [r5, #8]
_021DA11E:
	add r6, r6, #1
	add r4, r4, #2
	add r5, r5, #2
	cmp r6, #3
	blo _021DA10A
_021DA128:
	ldr r0, [sp, #4]
	mov r1, #1
	strb r1, [r0, #1]
	mov r2, #0
	add r1, r0, #0
_021DA132:
	ldrh r0, [r1, #8]
	cmp r0, #1
	bne _021DA14A
	ldr r0, [sp, #4]
	add r0, r0, r2
	ldrb r0, [r0, #4]
	cmp r0, #1
	bne _021DA14A
	ldr r0, [sp, #4]
	mov r1, #0
	strb r1, [r0, #1]
	b _021DA152
_021DA14A:
	add r2, r2, #1
	add r1, r1, #2
	cmp r2, #3
	blo _021DA132
_021DA152:
	ldr r0, [sp, #4]
	mov r1, #1
	strb r1, [r0]
	ldr r0, [sp]
	bl FUN_0200CAB4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DA164: .word 0x021E6224

	thumb_func_start MOD14_021DA168
MOD14_021DA168: ; 0x021DA168
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	mov r1, #0
	add r5, r0, #0
	str r1, [sp, #4]
	bl FUN_02066A6C
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0xac
	mov r2, #0
	bl FUN_020672BC
	cmp r0, #0
	bne _021DA1A8
	mov r4, #0
	add r7, r4, #0
_021DA18C:
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x36
	add r2, r7, #0
	bl FUN_020672BC
	cmp r6, r0
	bne _021DA1A2
	mov r0, #1
	str r0, [sp, #4]
	b _021DA1A8
_021DA1A2:
	add r4, r4, #1
	cmp r4, #4
	blt _021DA18C
_021DA1A8:
	ldr r1, [sp]
	add r0, r5, #0
	bl FUN_02066A94
	ldr r0, [sp, #4]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021DA1B8
MOD14_021DA1B8: ; 0x021DA1B8
	mov r1, #0x57
	lsl r1, r1, #2
	ldrb r0, [r0, r1]
	bx lr

	thumb_func_start MOD14_021DA1C0
MOD14_021DA1C0: ; 0x021DA1C0
	mov r1, #0x57
	lsl r1, r1, #2
	add r1, r0, r1
	ldrb r0, [r1]
	cmp r0, #0
	beq _021DA1D0
	ldrb r0, [r1, #1]
	bx lr
_021DA1D0:
	mov r0, #0
	bx lr

	thumb_func_start MOD14_021DA1D4
MOD14_021DA1D4: ; 0x021DA1D4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _021DA1EA
	cmp r0, #1
	beq _021DA1FE
	cmp r0, #2
	beq _021DA256
	pop {r3, r4, r5, pc}
_021DA1EA:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #3
	bl MOD14_021DCB2C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA1FE:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #3
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DA2BC
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCA38
	mov r0, #0xa
	bl FUN_020168D0
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_0206B330
	mov r2, #0x12
	lsl r2, r2, #4
	add r1, r0, #0
	ldr r0, [r4, r2]
	add r2, #8
	ldr r2, [r4, r2]
	ldr r2, [r2, #0x18]
	bl FUN_0206B484
	mov r1, #0x4a
	lsl r1, r1, #2
	ldr r0, _021DA2C0 ; =0x020FA5FC
	ldr r1, [r4, r1]
	mov r2, #9
	bl FUN_02006234
	mov r1, #0x21
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA256:
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02006290
	cmp r0, #0
	beq _021DA2BC
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_0206B330
	add r5, r0, #0
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02006260
	mov r2, #0xf
	mov r0, #3
	mov r1, #0xa
	lsl r2, r2, #0xe
	bl FUN_0201681C
	mov r2, #0x12
	lsl r2, r2, #4
	ldr r0, [r4, r2]
	add r2, #8
	ldr r2, [r4, r2]
	add r1, r5, #0
	ldr r2, [r2, #0x18]
	bl FUN_0206B4B4
	mov r0, #0x12
	lsl r0, r0, #4
	add r1, r4, #0
	ldr r0, [r4, r0]
	add r1, #0x40
	bl MOD14_021DB580
	mov r0, #0x45
	lsl r0, r0, #2
	add r0, r4, r0
	add r1, r4, #0
	add r2, r4, #0
	bl MOD14_021DC76C
	ldr r1, _021DA2C4 ; =MOD14_021D76E8
	add r0, r4, #0
	bl MOD14_021D7610
_021DA2BC:
	pop {r3, r4, r5, pc}
	nop
_021DA2C0: .word 0x020FA5FC
_021DA2C4: .word MOD14_021D76E8

	thumb_func_start MOD14_021DA2C8
MOD14_021DA2C8: ; 0x021DA2C8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021DA2DE
	cmp r0, #1
	beq _021DA2F2
	cmp r0, #2
	beq _021DA334
	pop {r3, r4, r5, pc}
_021DA2DE:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #3
	bl MOD14_021DCB2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021DA2F2:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #3
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DA390
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl MOD14_021DCA38
	mov r0, #0xa
	bl FUN_020168D0
	add r0, r5, #0
	bl MOD14_021D83E4
	mov r1, #0x4b
	lsl r1, r1, #2
	ldr r0, _021DA394 ; =0x020FA6E8
	add r1, r5, r1
	mov r2, #9
	bl FUN_02006234
	mov r1, #0x21
	lsl r1, r1, #4
	str r0, [r5, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021DA334:
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02006290
	cmp r0, #0
	beq _021DA390
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0206B330
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02006260
	mov r2, #0xf
	mov r0, #3
	mov r1, #0xa
	lsl r2, r2, #0xe
	bl FUN_0201681C
	add r0, r5, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021DA374
	add r0, r5, #0
	add r1, r5, #0
	bl MOD14_021DA39C
_021DA374:
	mov r0, #0x45
	lsl r0, r0, #2
	add r0, r5, r0
	add r1, r5, #0
	add r2, r5, #0
	bl MOD14_021DC76C
	ldr r1, _021DA398 ; =MOD14_021D76E8
	add r0, r5, #0
	bl MOD14_021D7610
	add r0, r5, #0
	bl MOD14_021D7674
_021DA390:
	pop {r3, r4, r5, pc}
	nop
_021DA394: .word 0x020FA6E8
_021DA398: .word MOD14_021D76E8

	thumb_func_start MOD14_021DA39C
MOD14_021DA39C: ; 0x021DA39C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r4, #8
	ldrb r0, [r4, #4]
	add r5, r1, #0
	cmp r0, #0
	beq _021DA3B0
	cmp r0, #1
	beq _021DA3D2
	pop {r3, r4, r5, pc}
_021DA3B0:
	mov r0, #5
	lsl r0, r0, #6
	ldrb r0, [r5, r0]
	mov r1, #6
	strb r0, [r4, #7]
	mov r0, #7
	ldrsb r0, [r4, r0]
	bl _s32_div_f
	strb r1, [r4, #5]
	mov r0, #7
	ldrsb r0, [r4, r0]
	mov r1, #6
	bl _s32_div_f
	strb r0, [r4, #6]
	b _021DA3DA
_021DA3D2:
	mov r0, #5
	lsl r0, r0, #6
	ldrb r0, [r5, r0]
	strb r0, [r4, #8]
_021DA3DA:
	add r0, r5, #0
	bl MOD14_021DB934
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021DA3E4
MOD14_021DA3E4: ; 0x021DA3E4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #6
	bhi _021DA496
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DA3FC: ; jump table
	.short _021DA40A - _021DA3FC - 2 ; case 0
	.short _021DA41E - _021DA3FC - 2 ; case 1
	.short _021DA488 - _021DA3FC - 2 ; case 2
	.short _021DA522 - _021DA3FC - 2 ; case 3
	.short _021DA546 - _021DA3FC - 2 ; case 4
	.short _021DA58E - _021DA3FC - 2 ; case 5
	.short _021DA5C2 - _021DA3FC - 2 ; case 6
_021DA40A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #3
	bl MOD14_021DCB2C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	pop {r4, r5, r6, pc}
_021DA41E:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #3
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DA496
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCA38
	mov r0, #0xa
	bl FUN_020168D0
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0206F158
	ldr r1, _021DA5D8 ; =0x021E6264
	mov r2, #9
	bl FUN_0206EFEC
	mov r1, #0x85
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	sub r1, #0xf8
	ldr r1, [r4, r1]
	mov r2, #1
	mov r3, #0
	bl FUN_0206E314
	ldr r0, _021DA5DC ; =0x0000004B
	mov r1, #2
	bl HandleLoadOverlay
	mov r1, #0x85
	lsl r1, r1, #2
	ldr r0, _021DA5E0 ; =0x021EC68C
	ldr r1, [r4, r1]
	mov r2, #9
	bl FUN_02006234
	mov r1, #0x21
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	pop {r4, r5, r6, pc}
_021DA488:
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02006290
	cmp r0, #0
	bne _021DA498
_021DA496:
	b _021DA5D6
_021DA498:
	mov r0, #0x85
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0206E37C
	ldr r1, _021DA5E4 ; =0x021E6A00
	str r0, [r1, #8]
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02006260
	mov r0, #0x85
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02016A18
	ldr r0, _021DA5DC ; =0x0000004B
	bl UnloadOverlayByID
	ldr r0, _021DA5E4 ; =0x021E6A00
	ldr r6, [r0, #8]
	cmp r6, #0
	beq _021DA4F4
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0206F158
	lsl r1, r6, #0x10
	lsr r1, r1, #0x10
	mov r2, #1
	mov r3, #9
	bl FUN_0206EDD4
	ldr r1, _021DA5E4 ; =0x021E6A00
	add r0, r4, #0
	ldr r1, [r1, #8]
	add r2, r4, #0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl MOD14_021DC1E8
	add r0, r4, #0
	bl MOD14_021D7674
_021DA4F4:
	mov r2, #0xf
	mov r0, #3
	mov r1, #0xa
	lsl r2, r2, #0xe
	bl FUN_0201681C
	mov r0, #0x45
	lsl r0, r0, #2
	add r0, r4, r0
	add r1, r4, #0
	add r2, r4, #0
	bl MOD14_021DC76C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD14_021DCB2C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	pop {r4, r5, r6, pc}
_021DA522:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DA5D6
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl MOD14_021DCB2C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	pop {r4, r5, r6, pc}
_021DA546:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DA5D6
	ldr r0, _021DA5E4 ; =0x021E6A00
	ldr r2, [r0, #8]
	cmp r2, #0
	bne _021DA566
	add r0, r4, #0
	bl MOD14_021D7620
	pop {r4, r5, r6, pc}
_021DA566:
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200AE38
	add r0, r4, #0
	mov r1, #0x10
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	pop {r4, r5, r6, pc}
_021DA58E:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DA5D6
	ldr r0, _021DA5E8 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021DA5D6
	ldr r0, _021DA5EC ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	pop {r4, r5, r6, pc}
_021DA5C2:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021DA5D6
	add r0, r4, #0
	bl MOD14_021D7620
_021DA5D6:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DA5D8: .word 0x021E6264
_021DA5DC: .word 0x0000004B
_021DA5E0: .word 0x021EC68C
_021DA5E4: .word 0x021E6A00
_021DA5E8: .word 0x021C48B8
_021DA5EC: .word 0x000005DD

	thumb_func_start MOD14_021DA5F0
MOD14_021DA5F0: ; 0x021DA5F0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #5
	bhi _021DA6A2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DA608: ; jump table
	.short _021DA614 - _021DA608 - 2 ; case 0
	.short _021DA67A - _021DA608 - 2 ; case 1
	.short _021DA6E4 - _021DA608 - 2 ; case 2
	.short _021DA744 - _021DA608 - 2 ; case 3
	.short _021DA76C - _021DA608 - 2 ; case 4
	.short _021DA79E - _021DA608 - 2 ; case 5
_021DA614:
	bl MOD14_021DC430
	ldr r1, _021DA7B4 ; =0x021E6A00
	str r0, [r1, #4]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0206EA98
	cmp r0, #0
	beq _021DA648
	ldr r0, _021DA7B8 ; =0x000005F3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0x18
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA648:
	mov r0, #0x67
	ldr r2, _021DA7B4 ; =0x021E6A00
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r2, [r2, #4]
	mov r1, #0
	bl FUN_0200AE38
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021E5D98
	add r0, r4, #0
	mov r1, #0x17
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA67A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021DA6A2
	add r0, r4, #0
	bl MOD14_021E6160
	cmp r0, #0x36
	bgt _021DA6AC
	bge _021DA6D2
	mov r2, #0
	mvn r2, r2
	cmp r0, r2
	bgt _021DA6A2
	sub r1, r2, #1
	cmp r0, r1
	bge _021DA6A4
_021DA6A2:
	b _021DA7B2
_021DA6A4:
	beq _021DA6B2
	cmp r0, r2
	beq _021DA6C0
	pop {r3, r4, r5, pc}
_021DA6AC:
	cmp r0, #0x37
	beq _021DA6C0
	pop {r3, r4, r5, pc}
_021DA6B2:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1c
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021DA6C0:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA6D2:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1b
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA6E4:
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0206F158
	ldr r1, _021DA7B4 ; =0x021E6A00
	mov r2, #1
	ldr r1, [r1, #4]
	mov r3, #9
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0206ED38
	cmp r0, #0
	beq _021DA72A
	add r0, r4, #0
	mov r1, #0
	add r2, r4, #0
	bl MOD14_021DC1E8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x16
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA72A:
	add r0, r4, #0
	mov r1, #0xe
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA744:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021DA7B2
	add r0, r4, #0
	mov r1, #0xf
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA76C:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DA7B2
	ldr r0, _021DA7BC ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021DA7B2
	ldr r0, _021DA7C0 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA79E:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021DA7B2
	add r0, r4, #0
	bl MOD14_021D7620
_021DA7B2:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DA7B4: .word 0x021E6A00
_021DA7B8: .word 0x000005F3
_021DA7BC: .word 0x021C48B8
_021DA7C0: .word 0x000005DD

	thumb_func_start MOD14_021DA7C4
MOD14_021DA7C4: ; 0x021DA7C4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #6
	bhi _021DA878
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DA7DC: ; jump table
	.short _021DA7EA - _021DA7DC - 2 ; case 0
	.short _021DA850 - _021DA7DC - 2 ; case 1
	.short _021DA8BA - _021DA7DC - 2 ; case 2
	.short _021DA922 - _021DA7DC - 2 ; case 3
	.short _021DA950 - _021DA7DC - 2 ; case 4
	.short _021DA978 - _021DA7DC - 2 ; case 5
	.short _021DA9AA - _021DA7DC - 2 ; case 6
_021DA7EA:
	bl MOD14_021DC544
	ldr r1, _021DA9C0 ; =0x021E6A00
	str r0, [r1]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0206EA98
	cmp r0, #0
	beq _021DA81E
	ldr r0, _021DA9C4 ; =0x000005F3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0x18
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA81E:
	mov r0, #0x67
	ldr r2, _021DA9C0 ; =0x021E6A00
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r2, [r2]
	mov r1, #0
	bl FUN_0200AE38
	add r0, r4, #0
	mov r1, #0x1a
	bl MOD14_021DBA44
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021E5D98
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA850:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021DA878
	add r0, r4, #0
	bl MOD14_021E6160
	cmp r0, #0x36
	bgt _021DA882
	bge _021DA8A8
	mov r2, #0
	mvn r2, r2
	cmp r0, r2
	bgt _021DA878
	sub r1, r2, #1
	cmp r0, r1
	bge _021DA87A
_021DA878:
	b _021DA9BE
_021DA87A:
	beq _021DA888
	cmp r0, r2
	beq _021DA896
	pop {r3, r4, r5, pc}
_021DA882:
	cmp r0, #0x37
	beq _021DA896
	pop {r3, r4, r5, pc}
_021DA888:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1c
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021DA896:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA8A8:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA8BA:
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0206F158
	ldr r1, _021DA9C0 ; =0x021E6A00
	mov r2, #1
	ldr r1, [r1]
	mov r3, #9
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0206ED38
	cmp r0, #0
	beq _021DA908
	add r0, r4, #0
	bl MOD14_021DC538
	cmp r0, #0
	beq _021DA8EC
	add r0, r4, #0
	bl MOD14_021DC310
	mov r0, #4
	b _021DA8F8
_021DA8EC:
	add r0, r4, #0
	mov r1, #0
	add r2, r4, #0
	bl MOD14_021DC1E8
	mov r0, #3
_021DA8F8:
	str r0, [r5]
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x17
	bl MOD14_021DCB2C
	pop {r3, r4, r5, pc}
_021DA908:
	add r0, r4, #0
	mov r1, #0xe
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA922:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x17
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DA9BE
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x16
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA950:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021DA9BE
	add r0, r4, #0
	mov r1, #0x1b
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA978:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x18
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DA9BE
	ldr r0, _021DA9C8 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021DA9BE
	ldr r0, _021DA9CC ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	mov r0, #6
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DA9AA:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021DA9BE
	add r0, r4, #0
	bl MOD14_021D7620
_021DA9BE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DA9C0: .word 0x021E6A00
_021DA9C4: .word 0x000005F3
_021DA9C8: .word 0x021C48B8
_021DA9CC: .word 0x000005DD

	thumb_func_start MOD14_021DA9D0
MOD14_021DA9D0: ; 0x021DA9D0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #4
	bhi _021DAA74
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DA9E8: ; jump table
	.short _021DA9F2 - _021DA9E8 - 2 ; case 0
	.short _021DAA06 - _021DA9E8 - 2 ; case 1
	.short _021DAA2A - _021DA9E8 - 2 ; case 2
	.short _021DAA42 - _021DA9E8 - 2 ; case 3
	.short _021DAA5E - _021DA9E8 - 2 ; case 4
_021DA9F2:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1a
	bl MOD14_021DCB2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021DAA06:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1a
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DAA74
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x11
	bl MOD14_021DCB2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021DAA2A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x11
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DAA74
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021DAA42:
	ldr r0, _021DAA78 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0xf3
	tst r1, r0
	beq _021DAA74
	add r0, #0x21
	ldr r0, [r5, r0]
	mov r1, #0x12
	bl MOD14_021DCB2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021DAA5E:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x12
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DAA74
	add r0, r5, #0
	bl MOD14_021D7620
_021DAA74:
	pop {r3, r4, r5, pc}
	nop
_021DAA78: .word 0x021C48B8

	thumb_func_start MOD14_021DAA7C
MOD14_021DAA7C: ; 0x021DAA7C
	push {r4, r5}
	mov r3, #0x6f
	lsl r3, r3, #2
	mov r5, #0
	str r5, [r0, r3]
	add r4, r3, #5
	strb r1, [r0, r4]
	add r1, r3, #6
	strh r2, [r0, r1]
	add r1, r3, #4
	strb r5, [r0, r1]
	pop {r4, r5}
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DAA98
MOD14_021DAA98: ; 0x021DAA98
	mov r1, #0x6f
	mov r2, #0
	lsl r1, r1, #2
	str r2, [r0, r1]
	mov r2, #1
	add r1, r1, #4
	strb r2, [r0, r1]
	bx lr

	thumb_func_start MOD14_021DAAA8
MOD14_021DAAA8: ; 0x021DAAA8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x6f
	lsl r0, r0, #2
	add r4, r5, r0
	ldr r1, [r4]
	cmp r1, #3
	bls _021DAABA
	b _021DABDC
_021DAABA:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DAAC6: ; jump table
	.short _021DAACE - _021DAAC6 - 2 ; case 0
	.short _021DAB04 - _021DAAC6 - 2 ; case 1
	.short _021DAB2C - _021DAAC6 - 2 ; case 2
	.short _021DAB3E - _021DAAC6 - 2 ; case 3
_021DAACE:
	ldrb r0, [r4, #4]
	cmp r0, #1
	bne _021DAADA
	mov r0, #1
	str r0, [r4]
	b _021DABDC
_021DAADA:
	mov r0, #5
	ldrsb r1, [r4, r0]
	sub r0, r0, #6
	cmp r1, r0
	bne _021DAAE8
	mov r0, #0
	strb r0, [r4, #5]
_021DAAE8:
	mov r1, #5
	ldrsb r1, [r4, r1]
	add r0, r5, #0
	bl MOD14_021DC2DC
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1e
	bl MOD14_021DCB2C
	mov r0, #1
	str r0, [r4]
	b _021DABDC
_021DAB04:
	sub r0, #0xa8
	ldr r0, [r5, r0]
	mov r1, #0x1e
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DABDC
	ldrh r1, [r4, #6]
	add r0, r5, #0
	bl MOD14_021DBA44
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x18
	bl MOD14_021DCB2C
	mov r0, #2
	str r0, [r4]
	b _021DABDC
_021DAB2C:
	sub r0, #0xa8
	ldr r0, [r5, r0]
	mov r1, #0x18
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DABDC
	mov r0, #3
	str r0, [r4]
_021DAB3E:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1f
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DABDC
	ldr r0, _021DABE0 ; =0x021C48B8
	mov r1, #0x22
	ldr r0, [r0, #0x48]
	lsl r1, r1, #4
	add r2, r0, #0
	tst r2, r1
	beq _021DAB86
	mov r0, #5
	ldrsb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, #5]
	ldrsb r0, [r4, r0]
	cmp r0, #0
	bge _021DAB6E
	mov r0, #0x11
	strb r0, [r4, #5]
_021DAB6E:
	mov r1, #5
	ldrsb r1, [r4, r1]
	add r0, r5, #0
	bl MOD14_021DC2DC
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1f
	bl MOD14_021DCB2C
	b _021DABDC
_021DAB86:
	lsr r1, r1, #1
	tst r1, r0
	beq _021DABB6
	mov r0, #5
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #5]
	ldrsb r0, [r4, r0]
	cmp r0, #0x12
	blt _021DAB9E
	mov r0, #0
	strb r0, [r4, #5]
_021DAB9E:
	mov r1, #5
	ldrsb r1, [r4, r1]
	add r0, r5, #0
	bl MOD14_021DC2DC
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x1f
	bl MOD14_021DCB2C
	b _021DABDC
_021DABB6:
	mov r1, #1
	tst r1, r0
	beq _021DABC6
	ldr r0, _021DABE4 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DABC6:
	mov r1, #2
	tst r0, r1
	beq _021DABDC
	ldr r0, _021DABE4 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0
	mvn r0, r0
	strb r0, [r4, #5]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DABDC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DABE0: .word 0x021C48B8
_021DABE4: .word 0x000005DD

	thumb_func_start MOD14_021DABE8
MOD14_021DABE8: ; 0x021DABE8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #0
	beq _021DABFE
	cmp r1, #1
	beq _021DAC28
	cmp r1, #2
	beq _021DAC68
	pop {r3, r4, r5, pc}
_021DABFE:
	bl MOD14_021DC424
	add r1, r0, #0
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0206B428
	add r0, r5, #0
	bl MOD14_021DB934
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #4
	bl MOD14_021DCB2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021DAC28:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #4
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DAC7E
	add r0, r5, #0
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021DAC60
	add r0, r5, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021DAC60
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021DAC60:
	add r0, r5, #0
	bl MOD14_021D7620
	pop {r3, r4, r5, pc}
_021DAC68:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DAC7E
	add r0, r5, #0
	bl MOD14_021D7620
_021DAC7E:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021DAC80
MOD14_021DAC80: ; 0x021DAC80
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #5
	bhi _021DAD02
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DAC98: ; jump table
	.short _021DACA4 - _021DAC98 - 2 ; case 0
	.short _021DACF2 - _021DAC98 - 2 ; case 1
	.short _021DAEA2 - _021DAC98 - 2 ; case 2
	.short _021DAEF8 - _021DAC98 - 2 ; case 3
	.short _021DAF34 - _021DAC98 - 2 ; case 4
	.short _021DAF4A - _021DAC98 - 2 ; case 5
_021DACA4:
	ldr r0, _021DAF60 ; =0x000005E4
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #1
	bl MOD14_021DC350
	add r0, r4, #0
	bl MOD14_021DC424
	add r1, r0, #0
	add r0, r4, #0
	bl MOD14_021DC358
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x28
	bl MOD14_021DCB2C
	mov r0, #0x58
	str r0, [sp]
	mov r0, #0x72
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	mov r2, #0xc0
	mov r3, #0x38
	bl MOD14_021DC5F8
	mov r0, #0x81
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r1, #1
	add r0, r0, #4
	str r1, [r4, r0]
	str r1, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DACF2:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x28
	bl MOD14_021DCB98
	cmp r0, #0
	bne _021DAD04
_021DAD02:
	b _021DAF5E
_021DAD04:
	add r0, r4, #0
	bl MOD14_021DB9C8
	cmp r0, #0
	beq _021DAD34
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021DAD34
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #3
	beq _021DAD2C
	ldr r1, _021DAF64 ; =MOD14_021DAF78
	add r0, r4, #0
	bl MOD14_021D7610
	pop {r3, r4, r5, r6, r7, pc}
_021DAD2C:
	ldr r0, _021DAF68 ; =0x000005F3
	bl FUN_020054C8
	pop {r3, r4, r5, r6, r7, pc}
_021DAD34:
	ldr r0, _021DAF6C ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0xf3
	tst r0, r1
	beq _021DAD6C
	ldr r0, _021DAF70 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021DC350
	add r0, r4, #0
	bl MOD14_021DC424
	add r1, r0, #0
	add r0, r4, #0
	bl MOD14_021DC358
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x28
	bl MOD14_021DCB2C
	mov r0, #5
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DAD6C:
	mov r1, #0x81
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	cmp r0, #0
	beq _021DADE4
	add r0, r1, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021DADE4
	sub r0, r1, #4
	ldr r0, [r4, r0]
	add r2, r0, #1
	sub r0, r1, #4
	str r2, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0x14
	bls _021DADE4
	add r0, r4, #0
	bl MOD14_021DC474
	add r6, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl MOD14_021DC2C4
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, r6, #0
	bl FUN_0206B428
	add r0, r4, #0
	bl MOD14_021DB934
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021DADC6
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #8
	bl MOD14_021DCB2C
_021DADC6:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #4
	bl MOD14_021DCB2C
	mov r0, #0x81
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r0, r0, #4
	str r1, [r4, r0]
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DADE4:
	mov r0, #0x72
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD14_021DC664
	cmp r0, #1
	beq _021DADFC
	cmp r0, #2
	beq _021DAE1C
	cmp r0, #3
	beq _021DAE76
	pop {r3, r4, r5, r6, r7, pc}
_021DADFC:
	add r0, r4, #0
	bl MOD14_021DC474
	mov r1, #0x7f
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	mov r2, #0
	add r0, #8
	str r2, [r4, r0]
	add r0, r1, #0
	add r0, #0x10
	str r2, [r4, r0]
	add r1, #0xc
	str r2, [r4, r1]
	pop {r3, r4, r5, r6, r7, pc}
_021DAE1C:
	mov r0, #0x72
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD14_021DC708
	add r6, r0, #0
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r6, r0
	bne _021DAE34
	b _021DAF5E
_021DAE34:
	sub r7, r6, r0
	add r0, r4, #0
	bl MOD14_021DC474
	add r1, r7, r0
	bpl _021DAE44
	add r1, #0x12
	b _021DAE4A
_021DAE44:
	cmp r1, #0x12
	blt _021DAE4A
	sub r1, #0x12
_021DAE4A:
	mov r0, #0x83
	lsl r0, r0, #2
	str r6, [r4, r0]
	add r0, r4, #0
	bl MOD14_021DC358
	add r0, r4, #0
	add r1, r7, #0
	bl MOD14_021DC368
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x29
	bl MOD14_021DCB2C
	ldr r0, _021DAF74 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DAE76:
	add r0, r4, #0
	bl MOD14_021DC424
	add r5, r0, #0
	add r0, r4, #0
	bl MOD14_021DC474
	cmp r5, r0
	beq _021DAE8C
	mov r1, #1
	b _021DAE8E
_021DAE8C:
	mov r1, #0
_021DAE8E:
	mov r0, #0x81
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r1, r0, #4
	mov r2, #0
	str r2, [r4, r1]
	mov r1, #1
	add r0, r0, #4
	str r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DAEA2:
	mov r0, #0x82
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	bne _021DAEE2
	sub r0, #0x40
	add r0, r4, r0
	bl MOD14_021DC664
	cmp r0, #3
	bne _021DAEE2
	add r0, r4, #0
	bl MOD14_021DC424
	add r6, r0, #0
	add r0, r4, #0
	bl MOD14_021DC474
	cmp r6, r0
	beq _021DAECE
	mov r1, #1
	b _021DAED0
_021DAECE:
	mov r1, #0
_021DAED0:
	mov r0, #0x81
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r1, r0, #4
	mov r2, #0
	str r2, [r4, r1]
	mov r1, #1
	add r0, r0, #4
	str r1, [r4, r0]
_021DAEE2:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x29
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DAF5E
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DAEF8:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #4
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DAF5E
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021DAF2E
	add r0, r4, #0
	bl MOD14_021DC3F0
	cmp r0, #0
	beq _021DAF2E
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB2C
	mov r0, #4
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DAF2E:
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DAF34:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DAF5E
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DAF4A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021DAF5E
	add r0, r4, #0
	bl MOD14_021D7620
_021DAF5E:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DAF60: .word 0x000005E4
_021DAF64: .word MOD14_021DAF78
_021DAF68: .word 0x000005F3
_021DAF6C: .word 0x021C48B8
_021DAF70: .word 0x000005DD
_021DAF74: .word 0x000005DC

	thumb_func_start MOD14_021DAF78
MOD14_021DAF78: ; 0x021DAF78
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	add r4, r0, #0
	ldr r0, [r6]
	cmp r0, #3
	bhi _021DAFFC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DAF92: ; jump table
	.short _021DAF9A - _021DAF92 - 2 ; case 0
	.short _021DAFEC - _021DAF92 - 2 ; case 1
	.short _021DB144 - _021DAF92 - 2 ; case 2
	.short _021DB19C - _021DAF92 - 2 ; case 3
_021DAF9A:
	ldr r0, _021DB1B4 ; =0x000005E4
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #2
	bl MOD14_021DC350
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021DC360
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021DC358
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x28
	bl MOD14_021DCB2C
	mov r0, #0x58
	str r0, [sp]
	mov r0, #0x72
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0xff
	mov r2, #0xc0
	mov r3, #0x38
	bl MOD14_021DC5F8
	mov r0, #0x81
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r1, #1
	add r0, r0, #4
	str r1, [r4, r0]
	add sp, #8
	str r1, [r6]
	pop {r3, r4, r5, r6, r7, pc}
_021DAFEC:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x28
	bl MOD14_021DCB98
	cmp r0, #0
	bne _021DAFFE
_021DAFFC:
	b _021DB1B0
_021DAFFE:
	add r0, r4, #0
	bl MOD14_021DB9C8
	cmp r0, #0
	beq _021DB01E
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021DB01E
	ldr r1, _021DB1B8 ; =MOD14_021DAC80
	add r0, r4, #0
	bl MOD14_021D7610
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DB01E:
	ldr r0, _021DB1BC ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0xf3
	tst r0, r1
	beq _021DB046
	ldr r0, _021DB1C0 ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021DC350
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x28
	bl MOD14_021DCB2C
	mov r0, #3
	str r0, [r6]
_021DB046:
	add r0, r4, #0
	bl MOD14_021DB1C8
	cmp r0, #0
	beq _021DB072
	ldr r0, _021DB1C0 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x2a
	bl MOD14_021DCB2C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x27
	bl MOD14_021DCB2C
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DB072:
	mov r0, #0x72
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD14_021DC664
	cmp r0, #1
	beq _021DB08C
	cmp r0, #2
	beq _021DB0AE
	cmp r0, #3
	beq _021DB116
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DB08C:
	add r0, r4, #0
	bl MOD14_021DC474
	mov r1, #0x7f
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	mov r2, #0
	add r0, #8
	str r2, [r4, r0]
	add r0, r1, #0
	add r0, #0x10
	str r2, [r4, r0]
	add r1, #0xc
	add sp, #8
	str r2, [r4, r1]
	pop {r3, r4, r5, r6, r7, pc}
_021DB0AE:
	mov r0, #0x72
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD14_021DC708
	add r7, r0, #0
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r7, r0
	beq _021DB1B0
	sub r0, r7, r0
	str r0, [sp, #4]
	add r0, r4, #0
	bl MOD14_021DC474
	ldr r1, [sp, #4]
	add r5, r1, r0
	bpl _021DB0D8
	add r5, #8
	b _021DB0DE
_021DB0D8:
	cmp r5, #8
	blt _021DB0DE
	sub r5, #8
_021DB0DE:
	mov r0, #0x83
	lsl r0, r0, #2
	str r7, [r4, r0]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD14_021DC358
	add r0, r4, #0
	add r1, r5, #0
	bl MOD14_021DC360
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD14_021DC368
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x29
	bl MOD14_021DCB2C
	ldr r0, _021DB1C4 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #2
	add sp, #8
	str r0, [r6]
	pop {r3, r4, r5, r6, r7, pc}
_021DB116:
	add r0, r4, #0
	bl MOD14_021DC424
	add r5, r0, #0
	add r0, r4, #0
	bl MOD14_021DC474
	cmp r5, r0
	beq _021DB12C
	mov r1, #1
	b _021DB12E
_021DB12C:
	mov r1, #0
_021DB12E:
	mov r0, #0x81
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r1, r0, #4
	mov r2, #0
	str r2, [r4, r1]
	mov r1, #1
	add r0, r0, #4
	add sp, #8
	str r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DB144:
	mov r0, #0x82
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	bne _021DB184
	sub r0, #0x40
	add r0, r4, r0
	bl MOD14_021DC664
	cmp r0, #3
	bne _021DB184
	add r0, r4, #0
	bl MOD14_021DC424
	add r5, r0, #0
	add r0, r4, #0
	bl MOD14_021DC474
	cmp r5, r0
	beq _021DB170
	mov r1, #1
	b _021DB172
_021DB170:
	mov r1, #0
_021DB172:
	mov r0, #0x81
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r1, r0, #4
	mov r2, #0
	str r2, [r4, r1]
	mov r1, #1
	add r0, r0, #4
	str r1, [r4, r0]
_021DB184:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x29
	bl MOD14_021DCB98
	cmp r0, #0
	beq _021DB1B0
	mov r0, #1
	add sp, #8
	str r0, [r6]
	pop {r3, r4, r5, r6, r7, pc}
_021DB19C:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD14_021DCBC0
	cmp r0, #0
	beq _021DB1B0
	add r0, r4, #0
	bl MOD14_021D7620
_021DB1B0:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DB1B4: .word 0x000005E4
_021DB1B8: .word MOD14_021DAC80
_021DB1BC: .word 0x021C48B8
_021DB1C0: .word 0x000005DD
_021DB1C4: .word 0x000005DC

	thumb_func_start MOD14_021DB1C8
MOD14_021DB1C8: ; 0x021DB1C8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x62
	mov r1, #8
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r0, #8
	ldr r0, [r4, r0]
	bl FUN_02022144
	mov r0, #0x62
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #8
	beq _021DB1EA
	mov r0, #1
	pop {r4, pc}
_021DB1EA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB1F0
MOD14_021DB1F0: ; 0x021DB1F0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x62
	add r4, r2, #0
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #8
	bne _021DB21E
	cmp r1, #0
	bne _021DB21E
	add r0, r4, #0
	bl MOD14_021DC47C
	add r1, r0, r5
	cmp r1, #8
	blo _021DB212
	sub r1, #8
_021DB212:
	add r0, r4, #0
	bl MOD14_021DC370
	mov r0, #0x62
	lsl r0, r0, #2
	str r5, [r4, r0]
_021DB21E:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021DB220
MOD14_021DB220: ; 0x021DB220
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	bl FUN_02022510
	mov r1, #0x12
	lsl r1, r1, #4
	str r0, [r5, r1]
	ldr r2, [r4]
	sub r0, r1, #4
	str r2, [r5, r0]
	ldr r0, [r4]
	bl FUN_0206BB1C
	mov r1, #0x49
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r4]
	bl LoadPlayerDataAddress
	mov r1, #0x69
	lsl r1, r1, #2
	str r0, [r5, r1]
	sub r1, #0x8c
	str r4, [r5, r1]
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xf
	mov r3, #9
	str r0, [r4, #8]
	bl FUN_0200A86C
	mov r2, #0x63
	lsl r2, r2, #2
	str r0, [r5, r2]
	mov r0, #1
	mov r1, #0x1a
	sub r2, #0x22
	mov r3, #9
	bl FUN_0200A86C
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xbe
	mov r3, #9
	bl FUN_0200A86C
	mov r2, #0x65
	lsl r2, r2, #2
	str r0, [r5, r2]
	mov r0, #0
	mov r1, #0x1a
	add r2, #0x94
	mov r3, #9
	bl FUN_0200A86C
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #9
	bl FUN_0200AA80
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r5, r1]
	bl FUN_020669BC
	add r1, r0, #0
	mov r0, #9
	bl FUN_02016998
	mov r1, #0x1a
	lsl r1, r1, #4
	str r0, [r5, r1]
	sub r0, r1, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _021DB2C8
	bl ErrorHandling
_021DB2C8:
	mov r0, #0x69
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #2
	str r0, [sp]
	mov r0, #9
	mov r2, #0
	mov r3, #8
	bl FUN_02077A84
	mov r1, #0x4a
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r4, #4]
	cmp r0, #4
	beq _021DB2FA
	mov r0, #9
	str r0, [sp]
	ldr r0, _021DB384 ; =0x021E622A
	ldr r2, _021DB388 ; =MOD14_021DB9F4
	mov r1, #3
	add r3, r5, #0
	bl FUN_020220C4
	b _021DB30A
_021DB2FA:
	mov r0, #9
	str r0, [sp]
	ldr r0, _021DB38C ; =0x021E6236
	ldr r2, _021DB388 ; =MOD14_021DB9F4
	mov r1, #4
	add r3, r5, #0
	bl FUN_020220C4
_021DB30A:
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #9
	str r0, [sp]
	ldr r0, _021DB390 ; =0x021E6246
	ldr r2, _021DB394 ; =MOD14_021DB1F0
	mov r1, #7
	add r3, r5, #0
	bl FUN_020220C4
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r5, r1]
	add r0, r1, #0
	sub r0, #0x60
	ldr r0, [r5, r0]
	mov r2, #0
	str r0, [r5]
	add r0, r1, #0
	sub r0, #0x5c
	ldr r0, [r5, r0]
	str r0, [r5, #4]
	add r0, r1, #0
	sub r0, #0x70
	strh r2, [r5, r0]
	sub r1, #0x6e
	strh r2, [r5, r1]
	add r0, r5, #0
	ldr r1, [r4, #4]
	add r0, #0x48
	bl MOD14_021DB424
	add r0, r5, #0
	add r0, #0x4c
	bl MOD14_021DB4C8
	mov r0, #0x12
	lsl r0, r0, #4
	add r1, r5, #0
	ldr r0, [r5, r0]
	add r1, #0x40
	bl MOD14_021DB49C
	add r0, r5, #0
	add r0, #0xa4
	bl MOD14_021DB524
	add r0, r5, #0
	bl MOD14_021DB430
	add r0, r5, #0
	add r0, #0x14
	bl MOD14_021DB470
	add r5, #0x9c
	add r0, r5, #0
	bl MOD14_021DB574
	pop {r3, r4, r5, pc}
	nop
_021DB384: .word 0x021E622A
_021DB388: .word MOD14_021DB9F4
_021DB38C: .word 0x021E6236
_021DB390: .word 0x021E6246
_021DB394: .word MOD14_021DB1F0

	thumb_func_start MOD14_021DB398
MOD14_021DB398: ; 0x021DB398
	push {r4, lr}
	add r4, r0, #0
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl FUN_0202212C
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0202212C
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021DB3BE
	bl FUN_02016A18
_021DB3BE:
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200AB18
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200A8B8
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_0200A8B8
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200A8B8
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200A8B8
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02077AC4
	add r0, r4, #0
	add r0, #0x4c
	bl MOD14_021DB500
	add r0, r4, #0
	add r0, #0x14
	bl MOD14_021DB490
	add r0, r4, #0
	add r0, #0x40
	bl MOD14_021DB4BC
	add r0, r4, #0
	add r0, #0xa4
	bl MOD14_021DB558
	add r0, r4, #0
	bl FUN_02016A18
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB424
MOD14_021DB424: ; 0x021DB424
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	strh r1, [r0, #2]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DB430
MOD14_021DB430: ; 0x021DB430
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #0
	add r4, r5, #0
	add r2, r1, #0
	add r4, #8
	bl MOD14_021DBA4C
	mov r2, #0
	add r0, r5, #0
	strb r2, [r4, #8]
	mov r1, #1
	strb r1, [r4, #9]
	add r0, #0x48
	ldrb r0, [r0]
	cmp r0, #0
	beq _021DB458
	cmp r0, #4
	beq _021DB45C
	b _021DB462
_021DB458:
	strb r1, [r4, #4]
	b _021DB464
_021DB45C:
	mov r0, #2
	strb r0, [r4, #4]
	b _021DB464
_021DB462:
	strb r2, [r4, #4]
_021DB464:
	mov r0, #1
	strb r0, [r4, #0xb]
	add r0, r5, #0
	bl MOD14_021DB934
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021DB470
MOD14_021DB470: ; 0x021DB470
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020690C8
	add r2, r0, #0
	mov r1, #0x1e
	mov r0, #9
	mul r1, r2
	bl FUN_02016998
	str r0, [r4]
	mov r0, #0
	strb r0, [r4, #8]
	strb r0, [r4, #0xb]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB490
MOD14_021DB490: ; 0x021DB490
	ldr r3, _021DB498 ; =0x02016A19
	ldr r0, [r0]
	bx r3
	nop
_021DB498: .word 0x02016A19

	thumb_func_start MOD14_021DB49C
MOD14_021DB49C: ; 0x021DB49C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	bl FUN_0206B330
	strb r0, [r4]
	mov r0, #0x14
	mov r1, #9
	bl FUN_020219F4
	str r0, [r4, #4]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021DB580
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021DB4BC
MOD14_021DB4BC: ; 0x021DB4BC
	ldr r3, _021DB4C4 ; =0x02021A21
	ldr r0, [r0, #4]
	bx r3
	nop
_021DB4C4: .word 0x02021A21

	thumb_func_start MOD14_021DB4C8
MOD14_021DB4C8: ; 0x021DB4C8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xc
	mov r1, #9
	bl FUN_020219F4
	str r0, [r4, #0x14]
	mov r0, #0xc
	mov r1, #9
	bl FUN_020219F4
	str r0, [r4, #0x18]
	mov r0, #0x12
	mov r1, #9
	bl FUN_020219F4
	str r0, [r4, #0x1c]
	mov r0, #0xc
	mov r1, #9
	bl FUN_020219F4
	str r0, [r4, #0x20]
	mov r0, #0x10
	mov r1, #9
	bl FUN_020219F4
	str r0, [r4, #0x24]
	pop {r4, pc}

	thumb_func_start MOD14_021DB500
MOD14_021DB500: ; 0x021DB500
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	bl FUN_02021A20
	ldr r0, [r4, #0x18]
	bl FUN_02021A20
	ldr r0, [r4, #0x1c]
	bl FUN_02021A20
	ldr r0, [r4, #0x20]
	bl FUN_02021A20
	ldr r0, [r4, #0x24]
	bl FUN_02021A20
	pop {r4, pc}

	thumb_func_start MOD14_021DB524
MOD14_021DB524: ; 0x021DB524
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r4, #0
	strb r4, [r6]
	strb r4, [r6, #1]
	str r4, [r6, #4]
	add r5, r6, #0
	add r7, r4, #0
_021DB534:
	add r0, r6, r4
	strb r7, [r0, #2]
	mov r0, #0xc
	mov r1, #9
	bl FUN_020219F4
	str r0, [r5, #0x30]
	mov r0, #0xc
	mov r1, #9
	bl FUN_020219F4
	str r0, [r5, #0x34]
	add r4, r4, #1
	add r5, #0x30
	cmp r4, #2
	blt _021DB534
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB558
MOD14_021DB558: ; 0x021DB558
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021DB55E:
	ldr r0, [r5, #0x30]
	bl FUN_02021A20
	ldr r0, [r5, #0x34]
	bl FUN_02021A20
	add r4, r4, #1
	add r5, #0x30
	cmp r4, #2
	blt _021DB55E
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021DB574
MOD14_021DB574: ; 0x021DB574
	mov r1, #0
	strb r1, [r0]
	strb r1, [r0, #2]
	strb r1, [r0, #1]
	strh r1, [r0, #4]
	bx lr

	thumb_func_start MOD14_021DB580
MOD14_021DB580: ; 0x021DB580
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	bl FUN_0206B43C
	strb r0, [r4, #1]
	ldrb r1, [r4]
	ldr r2, [r4, #4]
	add r0, r5, #0
	bl FUN_0206B484
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB59C
MOD14_021DB59C: ; 0x021DB59C
	push {r4, lr}
	add r2, r0, #0
	add r4, r2, #0
	add r2, #0x40
	add r0, r1, #0
	ldrb r1, [r2]
	add r4, #0x40
	bl FUN_0206B43C
	strb r0, [r4, #1]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB5B4
MOD14_021DB5B4: ; 0x021DB5B4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r4, #0
	tst r2, r1
	beq _021DB5D0
	add r0, r5, #0
	sub r1, #0x21
	add r2, r4, #0
	bl MOD14_021DB61C
	add r4, r0, #0
	b _021DB60C
_021DB5D0:
	mov r1, #0x10
	tst r1, r0
	beq _021DB5E4
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	bl MOD14_021DB61C
	add r4, r0, #0
	b _021DB60C
_021DB5E4:
	mov r2, #0x40
	add r1, r0, #0
	tst r1, r2
	beq _021DB5FA
	add r0, r5, #0
	add r1, r4, #0
	sub r2, #0x41
	bl MOD14_021DB61C
	add r4, r0, #0
	b _021DB60C
_021DB5FA:
	mov r1, #0x80
	tst r0, r1
	beq _021DB60C
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #1
	bl MOD14_021DB61C
	add r4, r0, #0
_021DB60C:
	cmp r4, #1
	bne _021DB616
	add r0, r5, #0
	bl MOD14_021DB934
_021DB616:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB61C
MOD14_021DB61C: ; 0x021DB61C
	push {r4, lr}
	add r3, r0, #0
	add r3, #8
	ldrb r4, [r3, #4]
	cmp r4, #4
	bhi _021DB66A
	add r4, r4, r4
	add r4, pc
	ldrh r4, [r4, #6]
	lsl r4, r4, #0x10
	asr r4, r4, #0x10
	add pc, r4
_021DB634: ; jump table
	.short _021DB63E - _021DB634 - 2 ; case 0
	.short _021DB720 - _021DB634 - 2 ; case 1
	.short _021DB69E - _021DB634 - 2 ; case 2
	.short _021DB6F4 - _021DB634 - 2 ; case 3
	.short _021DB6C8 - _021DB634 - 2 ; case 4
_021DB63E:
	cmp r1, #0
	beq _021DB666
	mov r2, #5
	ldrsb r4, [r3, r2]
	add r1, r4, r1
	strb r1, [r3, #5]
	ldrsb r1, [r3, r2]
	cmp r1, #0
	bge _021DB654
	add r1, r2, #0
	b _021DB65A
_021DB654:
	cmp r1, #6
	blt _021DB65A
	mov r1, #0
_021DB65A:
	mov r2, #6
	ldrsb r2, [r3, r2]
	bl MOD14_021DBA4C
	mov r0, #1
	pop {r4, pc}
_021DB666:
	cmp r2, #0
	bne _021DB66C
_021DB66A:
	b _021DB78A
_021DB66C:
	mov r1, #6
	ldrsb r1, [r3, r1]
	add r2, r1, r2
	bpl _021DB67C
	mov r1, #2
	mov r2, #0
	strb r1, [r3, #4]
	b _021DB692
_021DB67C:
	cmp r2, #4
	ble _021DB692
	mov r1, #5
	ldrsb r1, [r3, r1]
	mov r2, #4
	cmp r1, #5
	bne _021DB68E
	add r1, r2, #0
	b _021DB690
_021DB68E:
	mov r1, #3
_021DB690:
	strb r1, [r3, #4]
_021DB692:
	mov r1, #5
	ldrsb r1, [r3, r1]
	bl MOD14_021DBA4C
	mov r0, #1
	pop {r4, pc}
_021DB69E:
	cmp r2, #0
	ble _021DB6B2
	mov r2, #0
	strb r2, [r3, #4]
	mov r1, #5
	ldrsb r1, [r3, r1]
	bl MOD14_021DBA4C
	mov r0, #1
	pop {r4, pc}
_021DB6B2:
	bge _021DB78A
	mov r0, #5
	ldrsb r0, [r3, r0]
	cmp r0, #5
	bne _021DB6C0
	mov r0, #4
	b _021DB6C2
_021DB6C0:
	mov r0, #3
_021DB6C2:
	strb r0, [r3, #4]
	mov r0, #1
	pop {r4, pc}
_021DB6C8:
	cmp r2, #0
	bge _021DB6DE
	mov r1, #0
	strb r1, [r3, #4]
	mov r1, #5
	ldrsb r1, [r3, r1]
	mov r2, #4
	bl MOD14_021DBA4C
	mov r0, #1
	pop {r4, pc}
_021DB6DE:
	ble _021DB6E8
	mov r0, #2
	strb r0, [r3, #4]
	mov r0, #1
	pop {r4, pc}
_021DB6E8:
	cmp r1, #0
	beq _021DB78A
	mov r0, #3
	strb r0, [r3, #4]
	mov r0, #1
	pop {r4, pc}
_021DB6F4:
	cmp r2, #0
	bge _021DB70A
	mov r1, #0
	strb r1, [r3, #4]
	mov r1, #5
	ldrsb r1, [r3, r1]
	mov r2, #4
	bl MOD14_021DBA4C
	mov r0, #1
	pop {r4, pc}
_021DB70A:
	ble _021DB714
	mov r0, #2
	strb r0, [r3, #4]
	mov r0, #1
	pop {r4, pc}
_021DB714:
	cmp r1, #0
	beq _021DB78A
	mov r0, #4
	strb r0, [r3, #4]
	mov r0, #1
	pop {r4, pc}
_021DB720:
	mov r4, #8
	ldrsb r0, [r3, r4]
	cmp r2, #0
	bge _021DB742
	cmp r0, #6
	bne _021DB732
	mov r1, #5
	strb r1, [r3, #8]
	b _021DB77E
_021DB732:
	sub r1, r0, #2
	strb r1, [r3, #8]
	ldrsb r1, [r3, r4]
	cmp r1, #0
	bge _021DB77E
	mov r1, #6
	strb r1, [r3, #8]
	b _021DB77E
_021DB742:
	ble _021DB75E
	cmp r0, #6
	bne _021DB74E
	mov r1, #0
	strb r1, [r3, #8]
	b _021DB77E
_021DB74E:
	add r1, r0, #2
	strb r1, [r3, #8]
	ldrsb r1, [r3, r4]
	cmp r1, #6
	blt _021DB77E
	mov r1, #6
	strb r1, [r3, #8]
	b _021DB77E
_021DB75E:
	cmp r1, #0
	bge _021DB76E
	mov r1, #1
	tst r1, r0
	beq _021DB77E
	sub r1, r0, #1
	strb r1, [r3, #8]
	b _021DB77E
_021DB76E:
	ble _021DB77E
	cmp r0, #6
	beq _021DB77E
	mov r1, #1
	tst r1, r0
	bne _021DB77E
	add r1, r0, #1
	strb r1, [r3, #8]
_021DB77E:
	mov r1, #8
	ldrsb r1, [r3, r1]
	cmp r0, r1
	beq _021DB78A
	mov r0, #1
	pop {r4, pc}
_021DB78A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB790
MOD14_021DB790: ; 0x021DB790
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r4, #0
	tst r2, r1
	beq _021DB7AC
	add r0, r5, #0
	sub r1, #0x21
	add r2, r4, #0
	bl MOD14_021DB80C
	add r4, r0, #0
	b _021DB7FE
_021DB7AC:
	mov r1, #0x10
	tst r1, r0
	beq _021DB7C0
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	bl MOD14_021DB80C
	add r4, r0, #0
	b _021DB7FE
_021DB7C0:
	mov r2, #0x40
	add r1, r0, #0
	tst r1, r2
	beq _021DB7D6
	add r0, r5, #0
	add r1, r4, #0
	sub r2, #0x41
	bl MOD14_021DB80C
	add r4, r0, #0
	b _021DB7FE
_021DB7D6:
	mov r2, #0x80
	add r1, r0, #0
	tst r1, r2
	beq _021DB7EC
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #1
	bl MOD14_021DB80C
	add r4, r0, #0
	b _021DB7FE
_021DB7EC:
	lsl r1, r2, #2
	tst r1, r0
	beq _021DB7F6
	mov r4, #3
	b _021DB7FE
_021DB7F6:
	add r2, #0x80
	tst r0, r2
	beq _021DB7FE
	mov r4, #4
_021DB7FE:
	cmp r4, #1
	bne _021DB808
	add r0, r5, #0
	bl MOD14_021DB934
_021DB808:
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021DB80C
MOD14_021DB80C: ; 0x021DB80C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r4, r7, #0
	add r4, #8
	ldrb r3, [r4, #4]
	add r6, r7, #0
	add r6, #0x14
	cmp r3, #0
	bne _021DB8C6
	cmp r1, #0
	beq _021DB874
	mov r2, #5
	ldrsb r2, [r4, r2]
	add r5, r2, r1
	bl MOD14_021DC3F4
	mov r1, #0xc
	tst r0, r1
	beq _021DB858
	ldrb r0, [r6, #4]
	ldrb r3, [r6, #6]
	add r2, r5, #0
	add r1, r5, #0
	cmp r3, r0
	bls _021DB844
	sub r0, r3, r0
	sub r1, r5, r0
	b _021DB848
_021DB844:
	sub r0, r0, r3
	add r2, r5, r0
_021DB848:
	cmp r1, #0
	bge _021DB850
	mov r0, #3
	pop {r3, r4, r5, r6, r7, pc}
_021DB850:
	cmp r2, #6
	blt _021DB864
	mov r0, #4
	pop {r3, r4, r5, r6, r7, pc}
_021DB858:
	cmp r5, #0
	blt _021DB860
	cmp r5, #6
	blt _021DB864
_021DB860:
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_021DB864:
	mov r2, #6
	ldrsb r2, [r4, r2]
	add r0, r7, #0
	add r1, r5, #0
	bl MOD14_021DBA4C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DB874:
	cmp r2, #0
	beq _021DB8C6
	mov r1, #6
	ldrsb r1, [r4, r1]
	add r5, r1, r2
	bl MOD14_021DC3F4
	mov r1, #0xc
	tst r0, r1
	beq _021DB8AA
	ldrb r0, [r6, #5]
	ldrb r3, [r6, #7]
	add r2, r5, #0
	add r1, r5, #0
	cmp r3, r0
	bls _021DB89A
	sub r0, r3, r0
	sub r1, r5, r0
	b _021DB89E
_021DB89A:
	sub r0, r0, r3
	add r2, r5, r0
_021DB89E:
	cmp r1, #0
	blt _021DB8A6
	cmp r2, #5
	blt _021DB8B6
_021DB8A6:
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_021DB8AA:
	cmp r5, #0
	blt _021DB8B2
	cmp r5, #5
	blt _021DB8B6
_021DB8B2:
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_021DB8B6:
	mov r1, #5
	ldrsb r1, [r4, r1]
	add r0, r7, #0
	add r2, r5, #0
	bl MOD14_021DBA4C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DB8C6:
	bl ErrorHandling
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB8D0
MOD14_021DB8D0: ; 0x021DB8D0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r5, #0
	add r4, #8
	bl MOD14_021DC3F4
	cmp r0, #2
	bne _021DB8FA
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0206B9AC
	strb r0, [r4, #8]
	mov r0, #8
	ldrsb r0, [r4, r0]
	cmp r0, #6
	blt _021DB8FE
	mov r0, #5
	strb r0, [r4, #8]
	b _021DB8FE
_021DB8FA:
	mov r0, #0
	strb r0, [r4, #8]
_021DB8FE:
	ldrb r0, [r4, #4]
	strb r0, [r4, #9]
	mov r0, #1
	strb r0, [r4, #4]
	add r0, r5, #0
	bl MOD14_021DB934
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB910
MOD14_021DB910: ; 0x021DB910
	push {r4, lr}
	add r4, r0, #0
	add r3, r4, #0
	add r3, #8
	mov r1, #0
	strb r1, [r3, #4]
	mov r2, #9
	ldrsb r2, [r3, r2]
	cmp r2, #0
	beq _021DB92A
	add r2, r1, #0
	bl MOD14_021DBA4C
_021DB92A:
	add r0, r4, #0
	bl MOD14_021DB934
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB934
MOD14_021DB934: ; 0x021DB934
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r5, #0
	add r4, #8
	mov r1, #0
	strb r1, [r4, #0xa]
	ldrb r0, [r4, #4]
	cmp r0, #4
	bhi _021DB994
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DB952: ; jump table
	.short _021DB95C - _021DB952 - 2 ; case 0
	.short _021DB96C - _021DB952 - 2 ; case 1
	.short _021DB994 - _021DB952 - 2 ; case 2
	.short _021DB994 - _021DB952 - 2 ; case 3
	.short _021DB994 - _021DB952 - 2 ; case 4
_021DB95C:
	mov r2, #7
	ldrsb r2, [r4, r2]
	ldr r0, [r5]
	sub r1, r1, #1
	bl FUN_0206B5E4
	str r0, [r4]
	b _021DB998
_021DB96C:
	mov r0, #8
	ldrsb r6, [r4, r0]
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0206B9AC
	cmp r6, r0
	bge _021DB98E
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl FUN_0206B9B0
	str r0, [r4]
	b _021DB998
_021DB98E:
	mov r0, #0
	str r0, [r4]
	b _021DB998
_021DB994:
	mov r0, #0
	str r0, [r4]
_021DB998:
	ldr r0, [r4]
	cmp r0, #0
	beq _021DB9C4
	mov r1, #0xab
	mov r2, #0
	bl FUN_020672BC
	cmp r0, #0
	beq _021DB9C4
	mov r0, #1
	strb r0, [r4, #0xa]
	add r0, r5, #0
	bl MOD14_021DC3F4
	mov r1, #6
	tst r0, r1
	bne _021DB9C4
	ldr r1, [r4]
	add r0, r5, #0
	add r2, r5, #0
	bl MOD14_021DBE88
_021DB9C4:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021DB9C8
MOD14_021DB9C8: ; 0x021DB9C8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x61
	ldr r1, _021DB9F0 ; =0x0000FFFF
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r0, #8
	ldr r0, [r4, r0]
	bl FUN_02022144
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	ldr r0, _021DB9F0 ; =0x0000FFFF
	cmp r1, r0
	beq _021DB9EC
	mov r0, #1
	pop {r4, pc}
_021DB9EC:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021DB9F0: .word 0x0000FFFF

	thumb_func_start MOD14_021DB9F4
MOD14_021DB9F4: ; 0x021DB9F4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r4, r2, #0
	cmp r5, #0
	bne _021DBA0E
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r2, [r4, r0]
	ldr r1, _021DBA40 ; =0x0000FFFF
	cmp r2, r1
	bne _021DBA0E
	str r6, [r4, r0]
_021DBA0E:
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	bne _021DBA3C
	cmp r6, #2
	bne _021DBA3C
	cmp r5, #0
	beq _021DBA2A
	cmp r5, #1
	beq _021DBA34
	cmp r5, #3
	beq _021DBA34
	pop {r4, r5, r6, pc}
_021DBA2A:
	add r0, r4, #0
	mov r1, #1
	bl MOD14_021DC1A0
	pop {r4, r5, r6, pc}
_021DBA34:
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021DC1A0
_021DBA3C:
	pop {r4, r5, r6, pc}
	nop
_021DBA40: .word 0x0000FFFF

	thumb_func_start MOD14_021DBA44
MOD14_021DBA44: ; 0x021DBA44
	mov r2, #0x43
	lsl r2, r2, #2
	str r1, [r0, r2]
	bx lr

	thumb_func_start MOD14_021DBA4C
MOD14_021DBA4C: ; 0x021DBA4C
	add r0, #8
	mov r3, #6
	strb r1, [r0, #5]
	mul r3, r2
	strb r2, [r0, #6]
	add r1, r1, r3
	strb r1, [r0, #7]
	bx lr

	thumb_func_start MOD14_021DBA5C
MOD14_021DBA5C: ; 0x021DBA5C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r0, #0
	add r4, r6, #0
	add r5, r6, #0
	add r0, r6, #0
	add r4, #0x14
	add r5, #8
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021DBA98
	bl FUN_020690C8
	add r2, r0, #0
	ldr r0, [r5]
	ldr r1, [r4]
	bl MIi_CpuCopy32
	mov r0, #0x12
	mov r2, #7
	lsl r0, r0, #4
	mov r1, #0
	ldrsb r2, [r5, r2]
	ldr r0, [r7, r0]
	mvn r1, r1
	bl FUN_0206B2FC
	mov r0, #0
	b _021DBAB6
_021DBA98:
	bl FUN_020690C4
	add r2, r0, #0
	ldr r0, [r5]
	ldr r1, [r4]
	bl MIi_CpuCopy32
	mov r0, #0x49
	mov r1, #8
	lsl r0, r0, #2
	ldrsb r1, [r5, r1]
	ldr r0, [r7, r0]
	bl FUN_0206B938
	mov r0, #1
_021DBAB6:
	strb r0, [r4, #0xb]
	ldr r1, [r4]
	add r0, r6, #0
	bl MOD14_021DC1A8
	mov r0, #5
	ldrsb r0, [r5, r0]
	strb r0, [r4, #6]
	ldrb r0, [r4, #6]
	strb r0, [r4, #4]
	mov r0, #6
	ldrsb r0, [r5, r0]
	strb r0, [r4, #7]
	ldrb r0, [r4, #7]
	strb r0, [r4, #5]
	mov r0, #2
	strb r0, [r6, #0x13]
	mov r0, #0
	strb r0, [r6, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021DBAE0
MOD14_021DBAE0: ; 0x021DBAE0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r6, r1, #0
	add r7, r0, #0
	add r6, #0x14
	mov r0, #1
	strb r0, [r6, #0xa]
	add r0, r1, #0
	str r1, [sp, #4]
	bl MOD14_021DC3E0
	str r0, [sp, #0x14]
	bl FUN_020690C8
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #4]
	add r1, sp, #0x30
	ldr r5, [r0, #0x14]
	add r0, sp, #0x24
	str r0, [sp]
	ldr r0, [sp, #4]
	add r2, sp, #0x2c
	add r3, sp, #0x28
	bl MOD14_021DC4A4
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0x24]
	str r0, [sp, #0x18]
	cmp r0, r1
	bhi _021DBBA6
	mov r1, #6
	mul r1, r0
	str r1, [sp, #8]
_021DBB26:
	ldr r1, [sp, #0x30]
	ldr r0, [sp, #8]
	str r1, [sp, #0x1c]
	add r4, r1, r0
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x1c]
	cmp r0, r1
	bhi _021DBB94
_021DBB36:
	mov r0, #0x12
	lsl r0, r0, #4
	mov r1, #0
	ldr r0, [r7, r0]
	mvn r1, r1
	add r2, r4, #0
	bl FUN_0206B5E4
	mov r1, #0xab
	mov r2, #0
	str r0, [sp, #0x20]
	bl FUN_020672BC
	cmp r0, #0
	beq _021DBB86
	ldr r0, [sp, #0x20]
	ldr r2, [sp, #0x10]
	add r1, r5, #0
	bl MIi_CpuCopy32
	mov r0, #0x12
	lsl r0, r0, #4
	mov r1, #0
	ldr r0, [r7, r0]
	mvn r1, r1
	add r2, r4, #0
	bl FUN_0206B2FC
	ldr r0, [sp, #0x10]
	add r5, r5, r0
	ldr r0, [sp, #0xc]
	add r1, r6, r0
	add r0, r0, #1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	strb r4, [r1, #0xc]
	cmp r4, r0
	bne _021DBB86
	mov r0, #0
	strb r0, [r6, #0xa]
_021DBB86:
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x2c]
	add r0, r0, #1
	add r4, r4, #1
	str r0, [sp, #0x1c]
	cmp r0, r1
	bls _021DBB36
_021DBB94:
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x24]
	add r0, r0, #6
	str r0, [sp, #8]
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, r1
	bls _021DBB26
_021DBBA6:
	ldr r0, [sp, #0xc]
	strb r0, [r6, #8]
	ldr r1, [sp, #0x28]
	mov r0, #6
	ldr r2, [sp, #0x30]
	mul r0, r1
	add r0, r2, r0
	strb r0, [r6, #9]
	ldr r0, [sp, #4]
	ldrb r0, [r0, #0x12]
	cmp r0, #0
	beq _021DBBC2
	mov r1, #4
	b _021DBBC4
_021DBBC2:
	mov r1, #8
_021DBBC4:
	ldr r0, [sp, #4]
	strb r1, [r0, #0x13]
	mov r1, #0
	strb r1, [r0, #0x12]
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021DBBD0
MOD14_021DBBD0: ; 0x021DBBD0
	add r2, r1, #0
	add r1, #8
	mov r0, #5
	ldrsb r0, [r1, r0]
	add r2, #0x14
	strb r0, [r2, #6]
	ldrb r0, [r2, #6]
	strb r0, [r2, #4]
	mov r0, #6
	ldrsb r0, [r1, r0]
	strb r0, [r2, #7]
	ldrb r0, [r2, #7]
	strb r0, [r2, #5]
	bx lr

	thumb_func_start MOD14_021DBBEC
MOD14_021DBBEC: ; 0x021DBBEC
	add r2, r1, #0
	add r1, #8
	mov r0, #5
	ldrsb r0, [r1, r0]
	add r2, #0x14
	strb r0, [r2, #6]
	mov r0, #6
	ldrsb r0, [r1, r0]
	strb r0, [r2, #7]
	bx lr

	thumb_func_start MOD14_021DBC00
MOD14_021DBC00: ; 0x021DBC00
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r5, r0, #0
	add r4, r7, #0
	add r6, r7, #0
	add r0, r7, #0
	add r4, #0x14
	add r6, #8
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021DBC42
	mov r0, #0x12
	mov r2, #7
	lsl r0, r0, #4
	mov r1, #0
	ldrsb r2, [r6, r2]
	ldr r0, [r5, r0]
	ldr r3, [r4]
	mvn r1, r1
	bl FUN_0206B2B0
	mov r0, #0x12
	mov r2, #7
	lsl r0, r0, #4
	mov r1, #0
	ldrsb r2, [r6, r2]
	ldr r0, [r5, r0]
	mvn r1, r1
	bl FUN_0206B5E4
	add r1, r0, #0
	b _021DBC8A
_021DBC42:
	ldrb r0, [r4, #0xb]
	cmp r0, #0
	beq _021DBC56
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [r4]
	bl FUN_0206B900
	b _021DBC70
_021DBC56:
	mov r1, #0x1a
	lsl r1, r1, #4
	ldr r0, [r4]
	ldr r1, [r5, r1]
	bl FUN_02069A64
	mov r1, #0x49
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, #0x7c
	ldr r1, [r5, r1]
	bl FUN_0206B900
_021DBC70:
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0206B9AC
	add r1, r0, #0
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	sub r1, r1, #1
	bl FUN_0206B9B0
	add r1, r0, #0
_021DBC8A:
	add r0, r7, #0
	bl MOD14_021DC1A8
	add r0, r5, #0
	bl MOD14_021DB934
	mov r0, #1
	strb r0, [r7, #0x13]
	strb r0, [r7, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021DBCA0
MOD14_021DBCA0: ; 0x021DBCA0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r1, #0
	add r7, r0, #0
	add r6, #0x14
	add r0, r1, #0
	str r1, [sp]
	bl MOD14_021DC4F8
	str r0, [sp, #8]
	ldrb r0, [r6, #9]
	str r0, [sp, #0xc]
	bl FUN_020690C8
	str r0, [sp, #4]
	ldr r0, [sp]
	mov r5, #0
	ldr r4, [r0, #0x14]
	ldrb r0, [r6, #8]
	cmp r0, #0
	ble _021DBCF4
_021DBCCA:
	add r3, r6, r5
	mov r2, #0xc
	ldrsb r3, [r3, r2]
	ldr r2, [sp, #0xc]
	mov r0, #0x12
	lsl r0, r0, #4
	sub r3, r3, r2
	ldr r2, [sp, #8]
	mov r1, #0
	add r2, r2, r3
	ldr r0, [r7, r0]
	mvn r1, r1
	add r3, r4, #0
	bl FUN_0206B2B0
	ldr r0, [sp, #4]
	add r5, r5, #1
	add r4, r4, r0
	ldrb r0, [r6, #8]
	cmp r5, r0
	blt _021DBCCA
_021DBCF4:
	ldr r0, [sp]
	bl MOD14_021DC3E0
	add r2, r0, #0
	mov r0, #0x12
	lsl r0, r0, #4
	mov r1, #0
	ldr r0, [r7, r0]
	mvn r1, r1
	bl FUN_0206B5E4
	add r1, r0, #0
	ldr r0, [sp]
	bl MOD14_021DC1A8
	add r0, r7, #0
	bl MOD14_021DB934
	mov r1, #0
	ldr r0, [sp]
	strb r1, [r6, #8]
	ldrb r0, [r0, #0x13]
	cmp r0, #4
	bne _021DBD26
	mov r1, #1
_021DBD26:
	ldr r0, [sp]
	strb r1, [r0, #0x12]
	mov r1, #1
	strb r1, [r0, #0x13]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021DBD34
MOD14_021DBD34: ; 0x021DBD34
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	str r1, [sp]
	add r5, r0, #0
	add r4, #0x14
	bl FUN_020690C4
	add r6, r0, #0
	ldr r0, [sp]
	add r2, r6, #0
	ldr r7, [r0, #0x14]
	str r0, [sp, #4]
	add r0, #8
	str r0, [sp, #4]
	add r0, r7, #0
	add r1, r7, r6
	bl MIi_CpuCopy32
	ldr r0, [sp]
	ldr r1, [sp]
	ldr r0, [r0, #8]
	ldr r1, [r1, #0x14]
	add r2, r6, #0
	bl MIi_CpuCopy32
	ldr r0, [sp]
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021DBD8E
	ldr r2, [sp, #4]
	mov r0, #0x12
	mov r3, #7
	lsl r0, r0, #4
	ldrsb r2, [r2, r3]
	mov r1, #0
	ldr r0, [r5, r0]
	mvn r1, r1
	add r3, r7, r6
	bl FUN_0206B2B0
	mov r0, #0
	strb r0, [r4, #0xb]
	b _021DBDC8
_021DBD8E:
	ldrb r0, [r4, #0xb]
	cmp r0, #0
	bne _021DBDA2
	mov r1, #0x1a
	lsl r1, r1, #4
	ldr r1, [r5, r1]
	add r0, r7, r6
	bl FUN_02069A64
	b _021DBDB0
_021DBDA2:
	mov r1, #0x1a
	lsl r1, r1, #4
	ldr r1, [r5, r1]
	add r0, r7, r6
	add r2, r6, #0
	bl MIi_CpuCopy32
_021DBDB0:
	mov r3, #0x49
	lsl r3, r3, #2
	ldr r0, [r5, r3]
	ldr r1, [sp, #4]
	mov r2, #8
	ldrsb r1, [r1, r2]
	add r3, #0x7c
	ldr r2, [r5, r3]
	bl FUN_0206B9DC
	mov r0, #1
	strb r0, [r4, #0xb]
_021DBDC8:
	ldr r0, [sp]
	ldr r1, [r4]
	add r2, r5, #0
	bl MOD14_021DBE88
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021DBDD8
MOD14_021DBDD8: ; 0x021DBDD8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r2, [r4, #0x14]
	bl FUN_0206B244
	cmp r0, #0
	beq _021DBDFA
	mov r0, #1
	strb r0, [r4, #0x13]
	add r0, r4, #0
	bl MOD14_021DB934
	mov r0, #1
	pop {r4, pc}
_021DBDFA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DBE00
MOD14_021DBE00: ; 0x021DBE00
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x12
	lsl r0, r0, #4
	add r4, r5, #0
	ldr r0, [r5, r0]
	ldr r2, [r5, #8]
	add r4, #8
	bl FUN_0206B244
	cmp r0, #0
	beq _021DBE30
	mov r0, #0x49
	mov r1, #8
	lsl r0, r0, #2
	ldrsb r1, [r4, r1]
	ldr r0, [r5, r0]
	bl FUN_0206B938
	add r0, r5, #0
	bl MOD14_021DB934
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DBE30:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021DBE34
MOD14_021DBE34: ; 0x021DBE34
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	bl FUN_020669A0
	mov r0, #1
	strb r0, [r4, #0x13]
	add r0, r4, #0
	bl MOD14_021DB934
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DBE4C
MOD14_021DBE4C: ; 0x021DBE4C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r5, #0
	add r4, #8
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021DBE70
	mov r0, #0x12
	mov r2, #7
	lsl r0, r0, #4
	mov r1, #0
	ldrsb r2, [r4, r2]
	ldr r0, [r5, r0]
	mvn r1, r1
	bl FUN_0206B2FC
	b _021DBE7E
_021DBE70:
	mov r0, #0x49
	mov r1, #8
	lsl r0, r0, #2
	ldrsb r1, [r4, r1]
	ldr r0, [r5, r0]
	bl FUN_0206B938
_021DBE7E:
	add r0, r5, #0
	bl MOD14_021DB934
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021DBE88
MOD14_021DBE88: ; 0x021DBE88
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bl MOD14_021DBEAC
	add r0, r5, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	bne _021DBEA8
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD14_021DBFF4
_021DBEA8:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021DBEAC
MOD14_021DBEAC: ; 0x021DBEAC
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	add r4, r7, #0
	add r0, r5, #0
	add r6, r2, #0
	add r4, #0x4c
	bl FUN_02066A6C
	str r0, [sp]
	str r5, [r7, #0x4c]
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl FUN_020672BC
	strh r0, [r4, #4]
	add r0, r5, #0
	mov r1, #6
	mov r2, #0
	bl FUN_020672BC
	strh r0, [r4, #6]
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_0206BB28
	ldrh r1, [r4, #4]
	bl FUN_0206BB48
	strh r0, [r4, #8]
	add r0, r5, #0
	mov r1, #0xac
	mov r2, #0
	bl FUN_020672BC
	strb r0, [r4, #0xf]
	ldrh r0, [r4, #4]
	mov r1, #9
	bl FUN_0206851C
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #8
	mov r2, #0
	bl FUN_020672BC
	add r2, r0, #0
	ldrh r1, [r4, #4]
	add r0, r7, #0
	bl FUN_02068824
	strb r0, [r4, #0xa]
	add r0, r5, #0
	mov r1, #0xb
	mov r2, #0
	bl FUN_020672BC
	strb r0, [r4, #0xb]
	add r0, r5, #0
	mov r1, #0xb0
	mov r2, #0
	bl FUN_020672BC
	strb r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #0xb1
	mov r2, #0
	bl FUN_020672BC
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	bne _021DBF68
	add r0, r5, #0
	mov r1, #0xaf
	mov r2, #0
	bl FUN_020672BC
	cmp r0, #0
	beq _021DBF68
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl FUN_020672BC
	add r2, r0, #0
	ldrh r1, [r4, #4]
	add r0, r7, #0
	bl FUN_02068A44
	strb r0, [r4, #0xe]
	b _021DBF6C
_021DBF68:
	mov r0, #0xff
	strb r0, [r4, #0xe]
_021DBF6C:
	ldr r2, [r4, #0x14]
	add r0, r5, #0
	mov r1, #0x76
	bl FUN_020672BC
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	bne _021DBF8C
	mov r0, #0x19
	lsl r0, r0, #4
	ldrh r1, [r4, #4]
	ldr r0, [r6, r0]
	ldr r2, [r4, #0x18]
	bl FUN_0200A8E0
	b _021DBF9A
_021DBF8C:
	ldr r0, [r4, #0x18]
	ldr r1, [r4, #0x14]
	bl FUN_02021A74
	ldr r0, [r4, #0x14]
	bl FUN_02021A4C
_021DBF9A:
	ldrh r1, [r4, #6]
	cmp r1, #0
	beq _021DBFAA
	ldr r0, [r4, #0x1c]
	mov r2, #9
	bl FUN_0206E768
	b _021DBFB8
_021DBFAA:
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	ldr r2, [r4, #0x1c]
	mov r1, #0x14
	bl FUN_0200A8E0
_021DBFB8:
	add r0, r5, #0
	bl FUN_0206885C
	add r1, r0, #0
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	ldr r2, [r4, #0x20]
	bl FUN_0200A8E0
	add r0, r5, #0
	mov r1, #0xa
	mov r2, #0
	bl FUN_020672BC
	add r1, r0, #0
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	ldr r2, [r4, #0x24]
	bl FUN_0200A8E0
	add r0, r7, #0
	bl FUN_02068640
	ldr r1, [sp]
	add r0, r5, #0
	bl FUN_02066A94
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021DBFF4
MOD14_021DBFF4: ; 0x021DBFF4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r0, #0xa4
	add r5, r2, #0
	ldrb r2, [r0]
	str r1, [sp]
	mov r0, #0x30
	add r6, r7, #0
	add r1, r7, #0
	mul r0, r2
	add r1, #0xac
	ldr r2, [sp]
	add r6, #0x4c
	add r4, r1, r0
	str r2, [r1, r0]
	ldrh r0, [r6, #4]
	strh r0, [r4, #4]
	ldrb r0, [r6, #0xf]
	strb r0, [r4, #6]
	ldrb r0, [r6, #0xa]
	strh r0, [r4, #8]
	ldrb r0, [r4, #6]
	cmp r0, #0
	ldr r0, [r4, #0x28]
	beq _021DC02E
	ldr r1, [r6, #0x18]
	bl FUN_02021A74
	b _021DC034
_021DC02E:
	ldr r1, [r6, #0x14]
	bl FUN_02021A74
_021DC034:
	ldr r0, [r4, #0x2c]
	ldr r1, [r6, #0x20]
	bl FUN_02021A74
	mov r1, #0x1a
	lsl r1, r1, #4
	ldr r0, [sp]
	ldr r1, [r5, r1]
	bl FUN_02069A64
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_020669D4
	add r6, r0, #0
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0xa3
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0xa]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0xa4
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0xc]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0xa5
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0xe]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0xa7
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x10]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0xa8
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x12]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0xa6
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x14]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x13
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x16]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x14
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x18]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x15
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x1a]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x16
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x1c]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x17
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x1e]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x36
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x20]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x37
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x22]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x38
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x24]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x39
	mov r2, #0
	bl FUN_020671BC
	strh r0, [r4, #0x26]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x70
	mov r2, #0
	bl FUN_020671BC
	strb r0, [r4, #7]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl FUN_02066A20
	add r0, r7, #0
	add r0, #0xa4
	ldrb r0, [r0]
	mov r1, #1
	add r0, r7, r0
	add r0, #0xa6
	strb r1, [r0]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021DC170
MOD14_021DC170: ; 0x021DC170
	add r1, r0, #0
	add r1, #0xa4
	ldrb r2, [r1]
	mov r1, #1
	add r0, #0xa4
	eor r1, r2
	strb r1, [r0]
	bx lr

	thumb_func_start MOD14_021DC180
MOD14_021DC180: ; 0x021DC180
	add r1, r0, #0
	add r1, #0xa5
	ldrb r1, [r1]
	add r2, r1, #1
	add r1, r0, #0
	add r1, #0xa5
	strb r2, [r1]
	add r1, r0, #0
	add r1, #0xa5
	ldrb r1, [r1]
	cmp r1, #3
	blo _021DC19E
	mov r1, #0
	add r0, #0xa5
	strb r1, [r0]
_021DC19E:
	bx lr

	thumb_func_start MOD14_021DC1A0
MOD14_021DC1A0: ; 0x021DC1A0
	add r0, #0xa8
	str r1, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC1A8
MOD14_021DC1A8: ; 0x021DC1A8
	str r1, [r0, #0x4c]
	bx lr

	thumb_func_start MOD14_021DC1AC
MOD14_021DC1AC: ; 0x021DC1AC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	add r0, #0x96
	ldrb r1, [r0]
	add r2, r4, #0
	add r0, sp, #0
	add r2, #0x4c
	strb r1, [r0]
	strb r1, [r2, #0xb]
	ldr r0, [r4, #0x4c]
	mov r1, #0xb
	add r2, sp, #0
	bl FUN_02067960
	add r0, r4, #0
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021DC1E2
	add r0, r4, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021DC1E2
	bl FUN_02022830
_021DC1E2:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DC1E8
MOD14_021DC1E8: ; 0x021DC1E8
	push {r0, r1, r2, r3}
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r0, sp, #0x18
	add r4, r5, #0
	ldrh r1, [r0, #4]
	add r4, #0x4c
	add r6, r2, #0
	strh r1, [r4, #6]
	cmp r1, #0
	beq _021DC20A
	ldr r0, [r4, #0x1c]
	mov r2, #9
	bl FUN_0206E768
	b _021DC218
_021DC20A:
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	ldr r2, [r4, #0x1c]
	mov r1, #0x14
	bl FUN_0200A8E0
_021DC218:
	add r0, r5, #0
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021DC24A
	add r0, r5, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021DC24A
	add r0, r5, #0
	bl MOD14_021DC3E0
	add r2, r0, #0
	add r0, sp, #0x1c
	str r0, [sp]
	mov r0, #0x12
	lsl r0, r0, #4
	mov r1, #0
	ldr r0, [r6, r0]
	mvn r1, r1
	mov r3, #6
	bl FUN_0206B598
	b _021DC254
_021DC24A:
	ldr r0, [r4]
	mov r1, #6
	add r2, sp, #0x1c
	bl FUN_02067960
_021DC254:
	ldr r0, [r4]
	mov r1, #5
	mov r2, #0
	bl FUN_020672BC
	ldr r1, _021DC274 ; =0x000001ED
	cmp r0, r1
	bne _021DC26A
	ldr r0, [r4]
	bl FUN_02069ECC
_021DC26A:
	add sp, #4
	pop {r3, r4, r5, r6}
	pop {r3}
	add sp, #0x10
	bx r3
	.align 2, 0
_021DC274: .word 0x000001ED

	thumb_func_start MOD14_021DC278
MOD14_021DC278: ; 0x021DC278
	add r2, r0, #0
	add r2, #0x40
	ldrb r2, [r2]
	add r1, r0, #0
	add r1, #0x40
	add r3, r2, #1
	add r2, r0, #0
	add r2, #0x40
	strb r3, [r2]
	add r2, r0, #0
	add r2, #0x40
	ldrb r2, [r2]
	cmp r2, #0x12
	blo _021DC298
	mov r2, #0
	strb r2, [r1]
_021DC298:
	ldr r3, _021DC2A0 ; =MOD14_021DB580
	ldr r0, [r0]
	bx r3
	nop
_021DC2A0: .word MOD14_021DB580

	thumb_func_start MOD14_021DC2A4
MOD14_021DC2A4: ; 0x021DC2A4
	add r2, r0, #0
	add r2, #0x40
	ldrb r2, [r2]
	add r1, r0, #0
	add r1, #0x40
	cmp r2, #0
	beq _021DC2B6
	sub r2, r2, #1
	b _021DC2B8
_021DC2B6:
	mov r2, #0x11
_021DC2B8:
	ldr r3, _021DC2C0 ; =MOD14_021DB580
	strb r2, [r1]
	ldr r0, [r0]
	bx r3
	.align 2, 0
_021DC2C0: .word MOD14_021DB580

	thumb_func_start MOD14_021DC2C4
MOD14_021DC2C4: ; 0x021DC2C4
	add r3, r0, #0
	add r2, r0, #0
	add r2, #0x40
	strb r1, [r2]
	add r3, #0x40
	add r1, r3, #0
	ldr r3, _021DC2D8 ; =MOD14_021DB580
	ldr r0, [r0]
	bx r3
	nop
_021DC2D8: .word MOD14_021DB580

	thumb_func_start MOD14_021DC2DC
MOD14_021DC2DC: ; 0x021DC2DC
	add r0, #0x98
	str r1, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC2E4
MOD14_021DC2E4: ; 0x021DC2E4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r2, r5, #0
	add r2, #0x4c
	add r4, r1, #0
	ldrh r1, [r2, #6]
	ldr r0, _021DC30C ; =0x00000112
	strh r1, [r5, r0]
	add r0, #0x7a
	ldr r0, [r4, r0]
	ldr r2, [r2, #0x1c]
	mov r1, #0x14
	bl FUN_0200A8E0
	add r0, r5, #0
	mov r1, #0
	add r2, r4, #0
	bl MOD14_021DC1E8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DC30C: .word 0x00000112

	thumb_func_start MOD14_021DC310
MOD14_021DC310: ; 0x021DC310
	ldr r1, _021DC318 ; =0x00000112
	mov r2, #0
	strh r2, [r0, r1]
	bx lr
	.align 2, 0
_021DC318: .word 0x00000112

	thumb_func_start MOD14_021DC31C
MOD14_021DC31C: ; 0x021DC31C
	push {r4, lr}
	ldr r3, _021DC330 ; =0x00000112
	add r2, r1, #0
	ldrh r1, [r0, r3]
	mov r4, #0
	strh r4, [r0, r3]
	bl MOD14_021DC1E8
	pop {r4, pc}
	nop
_021DC330: .word 0x00000112

	thumb_func_start MOD14_021DC334
MOD14_021DC334: ; 0x021DC334
	push {r4, lr}
	add r3, r0, #0
	add r3, #0x52
	ldr r4, _021DC34C ; =0x00000112
	add r2, r1, #0
	ldrh r1, [r0, r4]
	ldrh r3, [r3]
	strh r3, [r0, r4]
	bl MOD14_021DC1E8
	pop {r4, pc}
	nop
_021DC34C: .word 0x00000112

	thumb_func_start MOD14_021DC350
MOD14_021DC350: ; 0x021DC350
	add r0, #0x9c
	strb r1, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC358
MOD14_021DC358: ; 0x021DC358
	add r0, #0x9e
	strb r1, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC360
MOD14_021DC360: ; 0x021DC360
	add r0, #0x9d
	strb r1, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC368
MOD14_021DC368: ; 0x021DC368
	add r0, #0xa0
	strh r1, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC370
MOD14_021DC370: ; 0x021DC370
	cmp r1, #0
	bne _021DC37C
	mov r1, #0
	add r0, #0x4a
	strh r1, [r0]
	bx lr
_021DC37C:
	add r2, r0, #0
	add r2, #0x4a
	ldrh r3, [r2]
	mov r2, #1
	sub r1, r1, #1
	lsl r2, r1
	add r1, r3, #0
	eor r1, r2
	add r0, #0x4a
	strh r1, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC394
MOD14_021DC394: ; 0x021DC394
	add r1, r0, #0
	add r1, #0x49
	ldrb r2, [r1]
	mov r1, #1
	add r0, #0x49
	eor r1, r2
	strb r1, [r0]
	bx lr

	thumb_func_start MOD14_021DC3A4
MOD14_021DC3A4: ; 0x021DC3A4
	mov r1, #0x63
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD14_021DC3AC
MOD14_021DC3AC: ; 0x021DC3AC
	mov r1, #0x67
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD14_021DC3B4
MOD14_021DC3B4: ; 0x021DC3B4
	mov r1, #0x69
	lsl r1, r1, #2
	ldr r3, _021DC3C0 ; =0x02025085
	ldr r0, [r0, r1]
	bx r3
	nop
_021DC3C0: .word 0x02025085

	thumb_func_start MOD14_021DC3C4
MOD14_021DC3C4: ; 0x021DC3C4
	add r0, #0x48
	ldrb r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC3CC
MOD14_021DC3CC: ; 0x021DC3CC
	ldrb r0, [r0, #0xc]
	bx lr

	thumb_func_start MOD14_021DC3D0
MOD14_021DC3D0: ; 0x021DC3D0
	mov r1, #0xd
	ldrsb r0, [r0, r1]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC3D8
MOD14_021DC3D8: ; 0x021DC3D8
	mov r1, #0xe
	ldrsb r0, [r0, r1]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC3E0
MOD14_021DC3E0: ; 0x021DC3E0
	mov r1, #0xf
	ldrsb r0, [r0, r1]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC3E8
MOD14_021DC3E8: ; 0x021DC3E8
	mov r1, #0x10
	ldrsb r0, [r0, r1]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC3F0
MOD14_021DC3F0: ; 0x021DC3F0
	ldrb r0, [r0, #0x12]
	bx lr

	thumb_func_start MOD14_021DC3F4
MOD14_021DC3F4: ; 0x021DC3F4
	ldrb r0, [r0, #0x13]
	bx lr

	thumb_func_start MOD14_021DC3F8
MOD14_021DC3F8: ; 0x021DC3F8
	ldrb r1, [r0, #0x13]
	cmp r1, #0
	beq _021DC402
	ldrb r0, [r0, #0x1f]
	bx lr
_021DC402:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC408
MOD14_021DC408: ; 0x021DC408
	ldrb r1, [r0, #0x13]
	cmp r1, #2
	beq _021DC412
	cmp r1, #4
	bne _021DC416
_021DC412:
	mov r0, #1
	bx lr
_021DC416:
	ldrb r0, [r0, #0x12]
	cmp r0, #0
	beq _021DC420
	mov r0, #1
	bx lr
_021DC420:
	mov r0, #0
	bx lr

	thumb_func_start MOD14_021DC424
MOD14_021DC424: ; 0x021DC424
	add r0, #0x40
	ldrb r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC42C
MOD14_021DC42C: ; 0x021DC42C
	add r0, #0x4c
	bx lr

	thumb_func_start MOD14_021DC430
MOD14_021DC430: ; 0x021DC430
	push {r4, lr}
	add r4, r0, #0
	bl MOD14_021DC408
	cmp r0, #0
	beq _021DC442
	add r4, #0x52
	ldrh r0, [r4]
	pop {r4, pc}
_021DC442:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DC448
MOD14_021DC448: ; 0x021DC448
	add r0, #0x40
	bx lr

	thumb_func_start MOD14_021DC44C
MOD14_021DC44C: ; 0x021DC44C
	ldr r0, [r0]
	bx lr

	thumb_func_start MOD14_021DC450
MOD14_021DC450: ; 0x021DC450
	mov r1, #0x43
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD14_021DC458
MOD14_021DC458: ; 0x021DC458
	ldr r0, [r0, #0x4c]
	bx lr

	thumb_func_start MOD14_021DC45C
MOD14_021DC45C: ; 0x021DC45C
	add r0, #0x57
	ldrb r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC464
MOD14_021DC464: ; 0x021DC464
	add r0, #0x98
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC46C
MOD14_021DC46C: ; 0x021DC46C
	mov r1, #0xa0
	ldrsh r0, [r0, r1]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC474
MOD14_021DC474: ; 0x021DC474
	add r0, #0x9e
	ldrb r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC47C
MOD14_021DC47C: ; 0x021DC47C
	add r0, #0x9d
	ldrb r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC484
MOD14_021DC484: ; 0x021DC484
	push {r4, lr}
	add r4, r0, #0
	bl MOD14_021DC3C4
	cmp r0, #3
	beq _021DC496
	add r4, #0x4a
	ldrh r0, [r4]
	pop {r4, pc}
_021DC496:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DC49C
MOD14_021DC49C: ; 0x021DC49C
	add r0, #0x49
	ldrb r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC4A4
MOD14_021DC4A4: ; 0x021DC4A4
	push {r3, r4, r5, r6}
	add r0, #0x14
	ldrb r6, [r0, #6]
	ldrb r5, [r0, #4]
	ldr r4, [sp, #0x10]
	cmp r5, r6
	bhi _021DC4B8
	str r5, [r1]
	ldrb r1, [r0, #6]
	b _021DC4BC
_021DC4B8:
	str r6, [r1]
	ldrb r1, [r0, #4]
_021DC4BC:
	str r1, [r2]
	ldrb r2, [r0, #7]
	ldrb r1, [r0, #5]
	cmp r1, r2
	bhi _021DC4D0
	str r1, [r3]
	ldrb r0, [r0, #7]
	str r0, [r4]
	pop {r3, r4, r5, r6}
	bx lr
_021DC4D0:
	str r2, [r3]
	ldrb r0, [r0, #5]
	str r0, [r4]
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC4DC
MOD14_021DC4DC: ; 0x021DC4DC
	add r0, #0x14
	ldrb r2, [r0, #4]
	ldrb r1, [r0, #6]
	cmp r2, r1
	bne _021DC4F2
	ldrb r1, [r0, #5]
	ldrb r0, [r0, #7]
	cmp r1, r0
	bne _021DC4F2
	mov r0, #1
	bx lr
_021DC4F2:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC4F8
MOD14_021DC4F8: ; 0x021DC4F8
	push {r3, r4}
	add r1, r0, #0
	add r1, #0x14
	mov r2, #0xd
	mov r3, #0xe
	ldrsb r2, [r0, r2]
	ldrsb r0, [r0, r3]
	ldrb r4, [r1, #4]
	ldrb r3, [r1, #6]
	cmp r3, r4
	bls _021DC512
	sub r3, r3, r4
	sub r2, r2, r3
_021DC512:
	ldrb r3, [r1, #5]
	ldrb r1, [r1, #7]
	cmp r1, r3
	bls _021DC51E
	sub r1, r1, r3
	sub r0, r0, r1
_021DC51E:
	mov r1, #6
	mul r1, r0
	add r0, r2, r1
	pop {r3, r4}
	bx lr

	thumb_func_start MOD14_021DC528
MOD14_021DC528: ; 0x021DC528
	add r0, #0x14
	add r2, r0, r1
	mov r1, #0xc
	ldrsb r1, [r2, r1]
	ldrb r0, [r0, #9]
	sub r0, r1, r0
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC538
MOD14_021DC538: ; 0x021DC538
	ldr r1, _021DC540 ; =0x00000112
	ldrh r0, [r0, r1]
	bx lr
	nop
_021DC540: .word 0x00000112

	thumb_func_start MOD14_021DC544
MOD14_021DC544: ; 0x021DC544
	push {r4, lr}
	add r4, r0, #0
	bl MOD14_021DC538
	cmp r0, #0
	bne _021DC556
	add r0, r4, #0
	bl MOD14_021DC430
_021DC556:
	pop {r4, pc}

	thumb_func_start MOD14_021DC558
MOD14_021DC558: ; 0x021DC558
	add r0, #0xa4
	ldrb r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC560
MOD14_021DC560: ; 0x021DC560
	add r0, #0xa5
	ldrb r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC568
MOD14_021DC568: ; 0x021DC568
	mov r2, #0x30
	add r0, #0xac
	mul r2, r1
	add r0, r0, r2
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC574
MOD14_021DC574: ; 0x021DC574
	add r0, r0, r1
	add r0, #0xa6
	ldrb r0, [r0]
	bx lr

	thumb_func_start MOD14_021DC57C
MOD14_021DC57C: ; 0x021DC57C
	add r0, #0xa8
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC584
MOD14_021DC584: ; 0x021DC584
	add r0, #0x5b
	ldrb r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DC58C
MOD14_021DC58C: ; 0x021DC58C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bl MOD14_021DC3F4
	cmp r0, #1
	bne _021DC5B2
	add r0, r5, #0
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021DC5C4
	ldr r0, [r5, #0x4c]
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_020672BC
	pop {r4, r5, r6, pc}
_021DC5B2:
	ldrb r0, [r5, #0x1f]
	cmp r0, #0
	bne _021DC5C4
	ldr r0, [r5, #0x4c]
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_020672BC
	pop {r4, r5, r6, pc}
_021DC5C4:
	ldr r0, [r5, #0x4c]
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_020671BC
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021DC5D0
MOD14_021DC5D0: ; 0x021DC5D0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021DC5EC
	ldr r0, [r5, #0x4c]
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_020672BC
	pop {r4, r5, r6, pc}
_021DC5EC:
	ldr r0, [r5, #8]
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_020671BC
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021DC5F8
MOD14_021DC5F8: ; 0x021DC5F8
	push {r3, r4, r5, r6}
	ldr r4, _021DC660 ; =MOD14_021DC6C0
	add r6, r0, #0
	str r4, [r0, #0x30]
	mov r4, #0
	str r4, [r0, #0x1c]
	str r1, [r0, #0xc]
	str r2, [r0, #0x10]
	str r1, [r0, #0x14]
	str r2, [r0, #0x18]
	str r1, [r0, #4]
	add r4, r0, #0
	str r2, [r0, #8]
	lsl r2, r2, #0x18
	mov r5, #0xfe
	add r4, #0x28
	strb r5, [r4]
	lsl r4, r1, #0x18
	lsr r4, r4, #0x18
	add r6, #0x29
	strb r4, [r6]
	add r6, r0, #0
	lsr r2, r2, #0x18
	add r6, #0x2a
	strb r2, [r6]
	add r6, r0, #0
	add r6, #0x2b
	strb r3, [r6]
	add r3, r0, #0
	add r3, #0x2c
	strb r5, [r3]
	add r3, r0, #0
	add r3, #0x2d
	strb r4, [r3]
	add r3, r0, #0
	add r3, #0x2e
	strb r2, [r3]
	add r2, r0, #0
	add r2, #0x2f
	ldr r3, [sp, #0x10]
	cmp r1, #0x80
	strb r3, [r2]
	bge _021DC656
	mov r1, #1
	str r1, [r0, #0x24]
	pop {r3, r4, r5, r6}
	bx lr
_021DC656:
	sub r5, #0xff
	str r5, [r0, #0x24]
	pop {r3, r4, r5, r6}
	bx lr
	nop
_021DC660: .word MOD14_021DC6C0

	thumb_func_start MOD14_021DC664
MOD14_021DC664: ; 0x021DC664
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r0, #0x2c
	bl FUN_02020A40
	cmp r0, #1
	bne _021DC6A4
	add r0, r5, #0
	add r0, #0x28
	bl FUN_02020A40
	cmp r0, #0
	bne _021DC6A4
	ldr r0, [r5, #0x1c]
	mov r4, #1
	cmp r0, #0
	bne _021DC68C
	add r6, r4, #0
	b _021DC68E
_021DC68C:
	mov r6, #0
_021DC68E:
	add r0, sp, #4
	add r1, sp, #0
	bl FUN_02020AB0
	cmp r0, #0
	beq _021DC6A8
	ldr r0, [sp, #4]
	str r0, [r5, #0x14]
	ldr r0, [sp]
	str r0, [r5, #0x18]
	b _021DC6A8
_021DC6A4:
	mov r4, #0
	add r6, r4, #0
_021DC6A8:
	str r4, [r5, #0x1c]
	ldr r3, [r5, #0x30]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	blx r3
	add sp, #8
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021DC6B8
MOD14_021DC6B8: ; 0x021DC6B8
	mov r2, #0
	str r2, [r0]
	str r1, [r0, #0x30]
	bx lr

	thumb_func_start MOD14_021DC6C0
MOD14_021DC6C0: ; 0x021DC6C0
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #0
	beq _021DC6E8
	cmp r2, #0
	beq _021DC6E8
	ldr r1, [r4, #0x14]
	str r1, [r4, #4]
	ldr r2, [r4, #0x18]
	str r2, [r4, #8]
	ldr r1, [r4, #4]
	bl MOD14_021DC720
	strh r0, [r4, #0x20]
	ldr r1, _021DC6EC ; =MOD14_021DC6F0
	add r0, r4, #0
	bl MOD14_021DC6B8
	mov r0, #1
	pop {r4, pc}
_021DC6E8:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021DC6EC: .word MOD14_021DC6F0

	thumb_func_start MOD14_021DC6F0
MOD14_021DC6F0: ; 0x021DC6F0
	push {r3, lr}
	cmp r1, #0
	bne _021DC700
	ldr r1, _021DC704 ; =MOD14_021DC6C0
	bl MOD14_021DC6B8
	mov r0, #3
	pop {r3, pc}
_021DC700:
	mov r0, #2
	pop {r3, pc}
	.align 2, 0
_021DC704: .word MOD14_021DC6C0

	thumb_func_start MOD14_021DC708
MOD14_021DC708: ; 0x021DC708
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x14]
	ldr r2, [r4, #0x18]
	bl MOD14_021DC720
	add r2, r0, #0
	ldrh r1, [r4, #0x20]
	add r0, r4, #0
	bl MOD14_021DC738
	pop {r4, pc}

	thumb_func_start MOD14_021DC720
MOD14_021DC720: ; 0x021DC720
	add r3, r0, #0
	ldr r0, [r3, #0x10]
	sub r0, r2, r0
	ldr r2, [r3, #0xc]
	ldr r3, _021DC734 ; =0x020C5668
	sub r1, r1, r2
	lsl r0, r0, #0xc
	lsl r1, r1, #0xc
	bx r3
	nop
_021DC734: .word 0x020C5668

	thumb_func_start MOD14_021DC738
MOD14_021DC738: ; 0x021DC738
	push {r4, r5}
	sub r2, r2, r1
	bpl _021DC746
	mov r4, #0
	mvn r4, r4
	mul r2, r4
	b _021DC748
_021DC746:
	mov r4, #1
_021DC748:
	ldr r5, _021DC768 ; =0x021E6278
	mov r3, #0
_021DC74C:
	ldrh r1, [r5]
	cmp r2, r1
	blt _021DC75A
	add r3, r3, #1
	add r5, r5, #2
	cmp r3, #2
	blo _021DC74C
_021DC75A:
	ldr r1, [r0, #0x24]
	add r0, r3, #0
	mul r0, r4
	mul r0, r1
	pop {r4, r5}
	bx lr
	nop
_021DC768: .word 0x021E6278

	thumb_func_start MOD14_021DC76C
MOD14_021DC76C: ; 0x021DC76C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	add r7, r0, #0
	ldr r1, _021DC9C8 ; =0x0000B3B4
	mov r0, #0xa
	add r6, r2, #0
	bl FUN_02016998
	add r4, r0, #0
	beq _021DC79A
	mov r0, #0x16
	lsl r0, r0, #4
	str r5, [r4, r0]
	mov r0, #0xa
	bl FUN_02016B94
	mov r1, #0x57
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _021DC79C
_021DC79A:
	b _021DC9C2
_021DC79C:
	mov r0, #0
	add r1, r0, #0
	mov r5, #1
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r1, #1
	lsl r1, r1, #0x1a
	ldr r0, [r1]
	ldr r3, _021DC9CC ; =0xFFFFE0FF
	and r0, r3
	str r0, [r1]
	ldr r0, _021DC9D0 ; =0x04001000
	ldr r2, [r0]
	and r2, r3
	str r2, [r0]
	ldr r3, [r1]
	ldr r2, _021DC9D4 ; =0xFFCFFFEF
	and r3, r2
	ldr r2, _021DC9D8 ; =0x00100010
	orr r2, r3
	str r2, [r1]
	ldr r2, [r0]
	ldr r1, _021DC9D4 ; =0xFFCFFFEF
	and r2, r1
	mov r1, #0x10
	orr r1, r2
	str r1, [r0]
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r2, #0x80
	str r2, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r1, #0xa
	str r1, [sp, #0x10]
	add r1, r2, #0
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r4, #0
	mov r0, #0x80
	add r1, #0x1c
	mov r2, #0xa
	bl FUN_02008C9C
	str r0, [r4, #0x18]
	add r0, r4, #0
	mov r2, #6
	add r0, #0x1c
	mov r1, #0
	lsl r2, r2, #0x12
	bl FUN_02008D24
	mov r0, #0x51
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_020B19DC
	mov r0, #0xa
	str r0, [sp]
	mov r0, #0x51
	lsl r0, r0, #2
	add r0, r4, r0
	str r0, [sp, #4]
	mov r0, #0x12
	mov r1, #0x1a
	add r2, r5, #0
	mov r3, #0
	bl FUN_02006A8C
	mov r0, #0
	mov r1, #0xa
	bl FUN_02002C84
	mov r0, #0xa
	bl FUN_02006D98
	mov r1, #0x56
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r1, #0
	add r2, r4, #0
	add r0, r1, #0
_021DC854:
	add r1, r1, #1
	str r0, [r2, #8]
	add r2, r2, #4
	cmp r1, #4
	blo _021DC854
	bl MOD14_021DDEE8
	mov r2, #0x59
	lsl r2, r2, #2
	str r4, [r7]
	add r0, r4, r2
	sub r2, r2, #4
	ldr r2, [r4, r2]
	ldr r3, [r4, #0x18]
	add r1, r4, #0
	bl MOD14_021E078C
	and r5, r0
	ldr r0, [r4, #0x18]
	mov r3, #0x16
	str r0, [sp]
	lsl r3, r3, #4
	mov r0, #0x43
	ldr r2, [r4, r3]
	sub r3, r3, #4
	lsl r0, r0, #4
	ldr r3, [r4, r3]
	add r0, r4, r0
	add r1, r4, #0
	bl MOD14_021DDF70
	mov r2, #0x16
	and r5, r0
	ldr r0, _021DC9DC ; =0x00005DC0
	lsl r2, r2, #4
	ldr r2, [r4, r2]
	ldr r3, [r4, #0x18]
	add r0, r4, r0
	add r1, r4, #0
	bl MOD14_021DF07C
	mov r2, #0x16
	and r5, r0
	ldr r0, _021DC9E0 ; =0x00006558
	lsl r2, r2, #4
	ldr r2, [r4, r2]
	ldr r3, [r4, #0x18]
	add r0, r4, r0
	add r1, r4, #0
	bl MOD14_021E0C7C
	and r5, r0
	add r0, r6, #0
	bl MOD14_021DC3A4
	ldr r1, [r4, #0x18]
	mov r3, #0x16
	str r1, [sp]
	str r0, [sp, #4]
	lsl r3, r3, #4
	ldr r0, _021DC9E4 ; =0x000065A0
	ldr r2, [r4, r3]
	sub r3, r3, #4
	ldr r3, [r4, r3]
	add r0, r4, r0
	add r1, r4, #0
	bl MOD14_021E0D90
	and r5, r0
	add r0, r6, #0
	bl MOD14_021DC3A4
	add r7, r0, #0
	add r0, r6, #0
	bl MOD14_021DC3AC
	str r0, [sp, #0x14]
	add r0, r6, #0
	bl MOD14_021DC3B4
	ldr r1, [r4, #0x18]
	mov r3, #0x16
	str r1, [sp]
	ldr r1, [sp, #0x14]
	str r7, [sp, #4]
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	lsl r3, r3, #4
	ldr r0, _021DC9E8 ; =0x000065F4
	ldr r2, [r4, r3]
	sub r3, r3, #4
	ldr r3, [r4, r3]
	add r0, r4, r0
	add r1, r4, #0
	bl MOD14_021E1750
	and r5, r0
	ldr r0, [r4, #0x18]
	mov r3, #0x16
	str r0, [sp]
	lsl r3, r3, #4
	ldr r0, _021DC9EC ; =0x0000662C
	ldr r2, [r4, r3]
	sub r3, r3, #4
	ldr r3, [r4, r3]
	add r0, r4, r0
	add r1, r4, #0
	bl MOD14_021E1D38
	and r5, r0
	ldr r0, [r4, #0x18]
	mov r3, #0x16
	str r0, [sp]
	lsl r3, r3, #4
	ldr r0, _021DC9F0 ; =0x0000B22C
	ldr r2, [r4, r3]
	sub r3, r3, #4
	ldr r3, [r4, r3]
	add r0, r4, r0
	add r1, r4, #0
	bl MOD14_021E2A38
	and r5, r0
	ldr r0, [r4, #0x18]
	mov r3, #0x16
	str r0, [sp]
	lsl r3, r3, #4
	ldr r0, _021DC9F4 ; =0x0000B3A4
	ldr r2, [r4, r3]
	sub r3, r3, #4
	ldr r3, [r4, r3]
	add r0, r4, r0
	add r1, r4, #0
	bl MOD14_021E33C8
	and r5, r0
	ldr r0, [r4, #0x18]
	mov r3, #0x16
	str r0, [sp]
	lsl r3, r3, #4
	ldr r0, _021DC9F8 ; =0x0000B3A8
	ldr r2, [r4, r3]
	sub r3, r3, #4
	ldr r3, [r4, r3]
	add r0, r4, r0
	add r1, r4, #0
	bl MOD14_021E4828
	and r5, r0
	add r0, r6, #0
	bl MOD14_021DC3A4
	ldr r1, [r4, #0x18]
	mov r3, #0x16
	str r1, [sp]
	str r0, [sp, #4]
	lsl r3, r3, #4
	ldr r0, _021DC9FC ; =0x0000B3AC
	ldr r2, [r4, r3]
	sub r3, r3, #4
	ldr r3, [r4, r3]
	add r0, r4, r0
	add r1, r4, #0
	bl MOD14_021E5044
	and r5, r0
	ldr r0, _021DCA00 ; =0x0000B3B0
	add r1, r4, #0
	str r6, [r4, r0]
	ldr r0, _021DCA04 ; =MOD14_021DCA0C
	mov r2, #2
	bl FUN_0200CA44
	str r0, [r4]
	ldr r0, _021DCA08 ; =MOD14_021DCBFC
	add r1, r4, #0
	mov r2, #1
	bl MOD14_021DDD40
	str r0, [r4, #4]
	add sp, #0x18
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
_021DC9C2:
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DC9C8: .word 0x0000B3B4
_021DC9CC: .word 0xFFFFE0FF
_021DC9D0: .word 0x04001000
_021DC9D4: .word 0xFFCFFFEF
_021DC9D8: .word 0x00100010
_021DC9DC: .word 0x00005DC0
_021DC9E0: .word 0x00006558
_021DC9E4: .word 0x000065A0
_021DC9E8: .word 0x000065F4
_021DC9EC: .word 0x0000662C
_021DC9F0: .word 0x0000B22C
_021DC9F4: .word 0x0000B3A4
_021DC9F8: .word 0x0000B3A8
_021DC9FC: .word 0x0000B3AC
_021DCA00: .word 0x0000B3B0
_021DCA04: .word MOD14_021DCA0C
_021DCA08: .word MOD14_021DCBFC

	thumb_func_start MOD14_021DCA0C
MOD14_021DCA0C: ; 0x021DCA0C
	push {r4, lr}
	add r4, r1, #0
	bl MOD14_021DDEF4
	bl G3X_ResetMtxStack
	bl G3X_ResetMtxStack_2
	bl FUN_020B02C8
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02006ED4
	ldr r0, _021DCA34 ; =0x04000540
	mov r1, #0
	str r1, [r0]
	pop {r4, pc}
	nop
_021DCA34: .word 0x04000540

	thumb_func_start MOD14_021DCA38
MOD14_021DCA38: ; 0x021DCA38
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	ldr r0, [r4]
	bl FUN_0200CAB4
	ldr r0, [r4, #4]
	bl FUN_0200CAB4
	ldr r0, _021DCB08 ; =0x0000B3AC
	ldr r0, [r4, r0]
	bl MOD14_021E50EC
	ldr r0, _021DCB0C ; =0x0000B3A8
	ldr r0, [r4, r0]
	bl MOD14_021E4880
	ldr r0, _021DCB10 ; =0x0000B3A4
	ldr r0, [r4, r0]
	bl MOD14_021E34C0
	ldr r0, _021DCB14 ; =0x0000B22C
	add r0, r4, r0
	bl MOD14_021E2AC8
	ldr r0, _021DCB18 ; =0x0000662C
	add r0, r4, r0
	bl MOD14_021E1F20
	ldr r0, _021DCB1C ; =0x000065F4
	add r0, r4, r0
	bl MOD14_021E17C4
	ldr r0, _021DCB20 ; =0x000065A0
	add r0, r4, r0
	bl MOD14_021E0E44
	ldr r0, _021DCB24 ; =0x00006558
	add r0, r4, r0
	bl MOD14_021E0D3C
	ldr r0, _021DCB28 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021DF3A8
	mov r0, #0x43
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD14_021DDFEC
	mov r0, #0x59
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD14_021E089C
	ldr r0, [r4, #0x18]
	bl FUN_0201FD58
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #3
	bl FUN_020178A0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020178A0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020178A0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #4
	bl FUN_020178A0
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_020072E8
	mov r0, #0
	bl FUN_02002CC0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02016A18
	add r0, r4, #0
	bl FUN_02016A18
	bl FUN_02009FA0
	pop {r4, pc}
	.align 2, 0
_021DCB08: .word 0x0000B3AC
_021DCB0C: .word 0x0000B3A8
_021DCB10: .word 0x0000B3A4
_021DCB14: .word 0x0000B22C
_021DCB18: .word 0x0000662C
_021DCB1C: .word 0x000065F4
_021DCB20: .word 0x000065A0
_021DCB24: .word 0x00006558
_021DCB28: .word 0x00005DC0

	thumb_func_start MOD14_021DCB2C
MOD14_021DCB2C: ; 0x021DCB2C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r5, r0, #0
	cmp r6, #0x34
	bhs _021DCB88
	mov r4, #0
	add r1, r5, #0
_021DCB3A:
	ldr r0, [r1, #8]
	cmp r0, #0
	bne _021DCB7E
	ldr r0, _021DCB90 ; =0x021E63D0
	lsl r7, r6, #3
	ldr r0, [r0, r7]
	str r0, [sp]
	ldr r1, [sp]
	mov r0, #0xa
	add r1, #0x14
	bl FUN_02016998
	add r1, r0, #0
	beq _021DCB78
	str r6, [r1]
	strh r4, [r1, #4]
	mov r0, #0
	strh r0, [r1, #6]
	ldr r0, [sp]
	str r5, [r1, #0xc]
	add r0, r1, r0
	str r0, [r1, #0x10]
	ldr r0, _021DCB94 ; =0x021E63CC
	mov r2, #1
	ldr r0, [r0, r7]
	bl FUN_0200CA44
	lsl r1, r4, #2
	add r1, r5, r1
	str r0, [r1, #8]
	pop {r3, r4, r5, r6, r7, pc}
_021DCB78:
	bl ErrorHandling
	pop {r3, r4, r5, r6, r7, pc}
_021DCB7E:
	add r4, r4, #1
	add r1, r1, #4
	cmp r4, #4
	blo _021DCB3A
	pop {r3, r4, r5, r6, r7, pc}
_021DCB88:
	bl ErrorHandling
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DCB90: .word 0x021E63D0
_021DCB94: .word 0x021E63CC

	thumb_func_start MOD14_021DCB98
MOD14_021DCB98: ; 0x021DCB98
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
_021DCBA0:
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021DCBB4
	bl FUN_0201B6C8
	ldr r0, [r0]
	cmp r0, r6
	bne _021DCBB4
	mov r0, #0
	pop {r4, r5, r6, pc}
_021DCBB4:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021DCBA0
	mov r0, #1
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021DCBC0
MOD14_021DCBC0: ; 0x021DCBC0
	mov r2, #0
_021DCBC2:
	ldr r1, [r0, #8]
	cmp r1, #0
	beq _021DCBCC
	mov r0, #0
	bx lr
_021DCBCC:
	add r2, r2, #1
	add r0, r0, #4
	cmp r2, #4
	blt _021DCBC2
	mov r0, #1
	bx lr

	thumb_func_start MOD14_021DCBD8
MOD14_021DCBD8: ; 0x021DCBD8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrh r0, [r5, #4]
	ldr r4, [r5, #0xc]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #8]
	bl FUN_0200CAB4
	ldrh r0, [r5, #4]
	mov r1, #0
	lsl r0, r0, #2
	add r0, r4, r0
	str r1, [r0, #8]
	add r0, r5, #0
	bl FUN_02016A18
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021DCBFC
MOD14_021DCBFC: ; 0x021DCBFC
	push {r4, lr}
	ldr r0, _021DCC20 ; =0x000065A0
	add r4, r1, #0
	add r0, r4, r0
	bl MOD14_021E0EE4
	ldr r0, [r4, #0x18]
	bl FUN_0201FDEC
	bl FUN_02009F80
	ldr r3, _021DCC24 ; =0x027E0000
	ldr r1, _021DCC28 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.align 2, 0
_021DCC20: .word 0x000065A0
_021DCC24: .word 0x027E0000
_021DCC28: .word 0x00003FF8

	thumb_func_start MOD14_021DCC2C
MOD14_021DCC2C: ; 0x021DCC2C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r0, #0x16
	ldr r4, [r5, #0xc]
	lsl r0, r0, #4
	ldr r6, [r4, r0]
	ldrh r0, [r5, #6]
	cmp r0, #0
	beq _021DCC44
	cmp r0, #1
	beq _021DCC7E
	pop {r4, r5, r6, pc}
_021DCC44:
	add r0, r4, #0
	add r1, r6, #0
	bl MOD14_021DDA38
	add r0, r4, #0
	add r1, r6, #0
	bl MOD14_021DDB50
	add r0, r4, #0
	add r1, r6, #0
	bl MOD14_021DDCF0
	add r0, r6, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021DCC76
	ldr r0, _021DCC9C ; =0x000065A0
	add r0, r4, r0
	bl MOD14_021E0EF4
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r4, r5, r6, pc}
_021DCC76:
	add r0, r5, #0
	bl MOD14_021DCBD8
	pop {r4, r5, r6, pc}
_021DCC7E:
	ldr r0, _021DCC9C ; =0x000065A0
	add r0, r4, r0
	bl MOD14_021E0F28
	cmp r0, #0
	beq _021DCC98
	ldr r0, _021DCC9C ; =0x000065A0
	add r0, r4, r0
	bl MOD14_021E13F0
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DCC98:
	pop {r4, r5, r6, pc}
	nop
_021DCC9C: .word 0x000065A0

	thumb_func_start MOD14_021DCCA0
MOD14_021DCCA0: ; 0x021DCCA0
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldrh r0, [r4, #6]
	cmp r0, #0
	beq _021DCCB4
	cmp r0, #1
	beq _021DCCEA
	add sp, #0xc
	pop {r3, r4, pc}
_021DCCB4:
	ldr r0, _021DCCFC ; =0x0000060D
	bl FUN_020054C8
	mov r0, #0xa
	str r0, [sp]
	ldr r0, _021DCD00 ; =0x04000050
	mov r1, #0
	mov r2, #0x3f
	mov r3, #6
	bl G2x_SetBlendAlpha_
	mov r0, #8
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldrh r0, [r4, #6]
	add sp, #0xc
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r3, r4, pc}
_021DCCEA:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DCCF8
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DCCF8:
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_021DCCFC: .word 0x0000060D
_021DCD00: .word 0x04000050

	thumb_func_start MOD14_021DCD04
MOD14_021DCD04: ; 0x021DCD04
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldrh r0, [r4, #6]
	cmp r0, #0
	beq _021DCD18
	cmp r0, #1
	beq _021DCD48
	add sp, #0xc
	pop {r3, r4, pc}
_021DCD18:
	mov r0, #0xa
	str r0, [sp]
	ldr r0, _021DCD5C ; =0x04000050
	mov r1, #0
	mov r2, #0x3f
	mov r3, #6
	bl G2x_SetBlendAlpha_
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldrh r0, [r4, #6]
	add sp, #0xc
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r3, r4, pc}
_021DCD48:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DCD56
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DCD56:
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_021DCD5C: .word 0x04000050

	thumb_func_start MOD14_021DCD60
MOD14_021DCD60: ; 0x021DCD60
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldrh r0, [r4, #6]
	cmp r0, #0
	beq _021DCD74
	cmp r0, #1
	beq _021DCD96
	add sp, #0xc
	pop {r3, r4, pc}
_021DCD74:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldrh r0, [r4, #6]
	add sp, #0xc
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r3, r4, pc}
_021DCD96:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DCDA4
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DCDA4:
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD14_021DCDA8
MOD14_021DCDA8: ; 0x021DCDA8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	mov r0, #0x16
	ldr r5, [r4, #0xc]
	lsl r0, r0, #4
	ldr r6, [r5, r0]
	ldrh r0, [r4, #6]
	cmp r0, #4
	bhi _021DCE5E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DCDC6: ; jump table
	.short _021DCDD0 - _021DCDC6 - 2 ; case 0
	.short _021DCDDE - _021DCDC6 - 2 ; case 1
	.short _021DCDF0 - _021DCDC6 - 2 ; case 2
	.short _021DCE30 - _021DCDC6 - 2 ; case 3
	.short _021DCE4C - _021DCDC6 - 2 ; case 4
_021DCDD0:
	ldr r0, _021DCE60 ; =0x0000B3A8
	ldr r0, [r5, r0]
	bl MOD14_021E4DF8
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
_021DCDDE:
	ldr r0, _021DCE60 ; =0x0000B3A8
	ldr r0, [r5, r0]
	bl MOD14_021E4E24
	cmp r0, #0
	beq _021DCE5E
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
_021DCDF0:
	mov r0, #0x43
	add r1, r6, #0
	lsl r0, r0, #4
	add r1, #0x40
	ldrb r0, [r5, r0]
	ldrb r1, [r1]
	bl MOD14_021DDD1C
	add r7, r0, #0
	mov r0, #0x43
	lsl r0, r0, #4
	add r1, r6, #0
	add r0, r5, r0
	add r1, #0x40
	add r2, r7, #0
	mov r3, #1
	bl MOD14_021DE0C4
	mov r0, #0x43
	lsl r0, r0, #4
	add r6, #0x40
	add r0, r5, r0
	add r1, r6, #0
	add r2, r7, #0
	bl MOD14_021DE2E8
	ldr r0, _021DCE64 ; =0x000005DC
	bl FUN_020054C8
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
_021DCE30:
	mov r0, #0x43
	lsl r0, r0, #4
	add r0, r5, r0
	bl MOD14_021DE394
	cmp r0, #0
	beq _021DCE5E
	ldr r0, _021DCE60 ; =0x0000B3A8
	ldr r0, [r5, r0]
	bl MOD14_021E4BE0
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
_021DCE4C:
	ldr r0, _021DCE60 ; =0x0000B3A8
	ldr r0, [r5, r0]
	bl MOD14_021E4C40
	cmp r0, #0
	beq _021DCE5E
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DCE5E:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DCE60: .word 0x0000B3A8
_021DCE64: .word 0x000005DC

	thumb_func_start MOD14_021DCE68
MOD14_021DCE68: ; 0x021DCE68
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrh r0, [r5, #6]
	ldr r4, [r5, #0xc]
	cmp r0, #0
	beq _021DCE7A
	cmp r0, #1
	beq _021DCE98
	pop {r3, r4, r5, pc}
_021DCE7A:
	ldr r0, _021DCEB8 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _021DCEBC ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021DF484
	ldr r0, _021DCEC0 ; =0x0000B3A8
	ldr r0, [r4, r0]
	bl MOD14_021E4BE0
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DCE98:
	ldr r0, _021DCEBC ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021DF59C
	cmp r0, #0
	beq _021DCEB6
	ldr r0, _021DCEC0 ; =0x0000B3A8
	ldr r0, [r4, r0]
	bl MOD14_021E4C40
	cmp r0, #0
	beq _021DCEB6
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DCEB6:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DCEB8: .word 0x000005DC
_021DCEBC: .word 0x00005DC0
_021DCEC0: .word 0x0000B3A8

	thumb_func_start MOD14_021DCEC4
MOD14_021DCEC4: ; 0x021DCEC4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r0, #0x16
	ldr r4, [r5, #0xc]
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC3C4
	cmp r0, #4
	ldrh r0, [r5, #6]
	beq _021DCF08
	cmp r0, #0
	beq _021DCEE4
	cmp r0, #1
	beq _021DCEF4
	pop {r3, r4, r5, pc}
_021DCEE4:
	ldr r0, _021DCF38 ; =0x000065A0
	add r0, r4, r0
	bl MOD14_021E1450
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DCEF4:
	ldr r0, _021DCF38 ; =0x000065A0
	add r0, r4, r0
	bl MOD14_021E1674
	cmp r0, #0
	beq _021DCF34
	add r0, r5, #0
	bl MOD14_021DCBD8
	pop {r3, r4, r5, pc}
_021DCF08:
	cmp r0, #0
	beq _021DCF12
	cmp r0, #1
	beq _021DCF22
	pop {r3, r4, r5, pc}
_021DCF12:
	ldr r0, _021DCF3C ; =0x0000B3AC
	ldr r0, [r4, r0]
	bl MOD14_021E526C
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DCF22:
	ldr r0, _021DCF3C ; =0x0000B3AC
	ldr r0, [r4, r0]
	bl MOD14_021E52BC
	cmp r0, #0
	beq _021DCF34
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DCF34:
	pop {r3, r4, r5, pc}
	nop
_021DCF38: .word 0x000065A0
_021DCF3C: .word 0x0000B3AC

	thumb_func_start MOD14_021DCF40
MOD14_021DCF40: ; 0x021DCF40
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r0, #0x16
	ldr r4, [r5, #0xc]
	lsl r0, r0, #4
	ldr r6, [r4, r0]
	add r0, r6, #0
	bl MOD14_021DC3F4
	cmp r0, #2
	bne _021DCF60
	ldr r0, _021DCF94 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021DFF8C
	b _021DCF84
_021DCF60:
	add r0, r6, #0
	bl MOD14_021DC3CC
	cmp r0, #0
	beq _021DCF70
	cmp r0, #1
	beq _021DCF7C
	b _021DCF84
_021DCF70:
	mov r0, #0x43
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD14_021DEF4C
	b _021DCF84
_021DCF7C:
	ldr r0, _021DCF98 ; =0x0000B22C
	add r0, r4, r0
	bl MOD14_021E3054
_021DCF84:
	ldr r0, _021DCF9C ; =0x000065A0
	add r0, r4, r0
	bl MOD14_021E1678
	add r0, r5, #0
	bl MOD14_021DCBD8
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DCF94: .word 0x00005DC0
_021DCF98: .word 0x0000B22C
_021DCF9C: .word 0x000065A0

	thumb_func_start MOD14_021DCFA0
MOD14_021DCFA0: ; 0x021DCFA0
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	ldr r0, _021DCFB8 ; =0x000065A0
	add r0, r1, r0
	bl MOD14_021E14D0
	add r0, r4, #0
	bl MOD14_021DCBD8
	pop {r4, pc}
	nop
_021DCFB8: .word 0x000065A0

	thumb_func_start MOD14_021DCFBC
MOD14_021DCFBC: ; 0x021DCFBC
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DCFCE
	cmp r0, #1
	beq _021DCFDE
	pop {r4, pc}
_021DCFCE:
	ldr r0, _021DCFF4 ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021DF758
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DCFDE:
	ldr r0, _021DCFF4 ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021DF7A0
	cmp r0, #0
	beq _021DCFF0
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DCFF0:
	pop {r4, pc}
	nop
_021DCFF4: .word 0x00005DC0

	thumb_func_start MOD14_021DCFF8
MOD14_021DCFF8: ; 0x021DCFF8
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD00A
	cmp r0, #1
	beq _021DD01A
	pop {r4, pc}
_021DD00A:
	ldr r0, _021DD030 ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021DF890
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD01A:
	ldr r0, _021DD030 ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021DF8C4
	cmp r0, #0
	beq _021DD02C
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD02C:
	pop {r4, pc}
	nop
_021DD030: .word 0x00005DC0

	thumb_func_start MOD14_021DD034
MOD14_021DD034: ; 0x021DD034
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD046
	cmp r0, #1
	beq _021DD056
	pop {r4, pc}
_021DD046:
	ldr r0, _021DD06C ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021DF9DC
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD056:
	ldr r0, _021DD06C ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021DFA58
	cmp r0, #0
	beq _021DD068
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD068:
	pop {r4, pc}
	nop
_021DD06C: .word 0x00005DC0

	thumb_func_start MOD14_021DD070
MOD14_021DD070: ; 0x021DD070
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD082
	cmp r0, #1
	beq _021DD092
	pop {r4, pc}
_021DD082:
	ldr r0, _021DD09C ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021DFE28
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD092:
	add r0, r4, #0
	bl MOD14_021DCBD8
	pop {r4, pc}
	nop
_021DD09C: .word 0x00005DC0

	thumb_func_start MOD14_021DD0A0
MOD14_021DD0A0: ; 0x021DD0A0
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD0B6
	cmp r0, #1
	beq _021DD0C6
	cmp r0, #2
	beq _021DD0D6
	pop {r4, pc}
_021DD0B6:
	ldr r0, _021DD0EC ; =0x0000B22C
	add r0, r1, r0
	bl MOD14_021E2F08
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD0C6:
	ldr r0, _021DD0EC ; =0x0000B22C
	add r0, r1, r0
	bl MOD14_021E2C7C
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD0D6:
	ldr r0, _021DD0EC ; =0x0000B22C
	add r0, r1, r0
	bl MOD14_021E2DA4
	cmp r0, #0
	beq _021DD0E8
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD0E8:
	pop {r4, pc}
	nop
_021DD0EC: .word 0x0000B22C

	thumb_func_start MOD14_021DD0F0
MOD14_021DD0F0: ; 0x021DD0F0
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD102
	cmp r0, #1
	beq _021DD112
	pop {r4, pc}
_021DD102:
	ldr r0, _021DD128 ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021DFE60
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD112:
	ldr r0, _021DD128 ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021DFE84
	cmp r0, #0
	beq _021DD124
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD124:
	pop {r4, pc}
	nop
_021DD128: .word 0x00005DC0

	thumb_func_start MOD14_021DD12C
MOD14_021DD12C: ; 0x021DD12C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrh r1, [r5, #6]
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r4, [r5, #0xc]
	cmp r1, #0
	ldr r0, [r4, r0]
	beq _021DD144
	cmp r1, #1
	beq _021DD15C
	pop {r3, r4, r5, pc}
_021DD144:
	bl MOD14_021DC3E0
	add r1, r0, #0
	mov r0, #0x43
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD14_021DEDD0
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DD15C:
	mov r0, #0x43
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD14_021DEE08
	cmp r0, #0
	beq _021DD170
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DD170:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021DD174
MOD14_021DD174: ; 0x021DD174
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrh r1, [r5, #6]
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r4, [r5, #0xc]
	cmp r1, #0
	ldr r0, [r4, r0]
	beq _021DD18C
	cmp r1, #1
	beq _021DD1A2
	pop {r3, r4, r5, pc}
_021DD18C:
	bl MOD14_021DC3E8
	add r1, r0, #0
	ldr r0, _021DD1B8 ; =0x0000B22C
	add r0, r4, r0
	bl MOD14_021E2F44
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DD1A2:
	ldr r0, _021DD1B8 ; =0x0000B22C
	add r0, r4, r0
	bl MOD14_021E2F68
	cmp r0, #0
	beq _021DD1B4
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DD1B4:
	pop {r3, r4, r5, pc}
	nop
_021DD1B8: .word 0x0000B22C

	thumb_func_start MOD14_021DD1BC
MOD14_021DD1BC: ; 0x021DD1BC
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD1CE
	cmp r0, #1
	beq _021DD1DE
	pop {r4, pc}
_021DD1CE:
	ldr r0, _021DD1F4 ; =0x0000662C
	add r0, r1, r0
	bl MOD14_021E26E4
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD1DE:
	ldr r0, _021DD1F4 ; =0x0000662C
	add r0, r1, r0
	bl MOD14_021E27AC
	cmp r0, #0
	beq _021DD1F0
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD1F0:
	pop {r4, pc}
	nop
_021DD1F4: .word 0x0000662C

	thumb_func_start MOD14_021DD1F8
MOD14_021DD1F8: ; 0x021DD1F8
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD20A
	cmp r0, #1
	beq _021DD21A
	pop {r4, pc}
_021DD20A:
	ldr r0, _021DD230 ; =0x0000662C
	add r0, r1, r0
	bl MOD14_021E283C
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD21A:
	ldr r0, _021DD230 ; =0x0000662C
	add r0, r1, r0
	bl MOD14_021E2884
	cmp r0, #0
	beq _021DD22C
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD22C:
	pop {r4, pc}
	nop
_021DD230: .word 0x0000662C

	thumb_func_start MOD14_021DD234
MOD14_021DD234: ; 0x021DD234
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrh r0, [r5, #6]
	ldr r4, [r5, #0xc]
	cmp r0, #0
	beq _021DD246
	cmp r0, #1
	beq _021DD256
	pop {r3, r4, r5, pc}
_021DD246:
	ldr r0, _021DD274 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021E0050
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DD256:
	ldr r0, _021DD274 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021E0080
	cmp r0, #0
	beq _021DD270
	ldr r0, _021DD278 ; =0x000065A0
	add r0, r4, r0
	bl MOD14_021E1704
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DD270:
	pop {r3, r4, r5, pc}
	nop
_021DD274: .word 0x00005DC0
_021DD278: .word 0x000065A0

	thumb_func_start MOD14_021DD27C
MOD14_021DD27C: ; 0x021DD27C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrh r0, [r5, #6]
	ldr r4, [r5, #0xc]
	cmp r0, #0
	beq _021DD28E
	cmp r0, #1
	beq _021DD29E
	pop {r3, r4, r5, pc}
_021DD28E:
	ldr r0, _021DD2BC ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021E00F0
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DD29E:
	ldr r0, _021DD2BC ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021E0120
	cmp r0, #0
	beq _021DD2B8
	ldr r0, _021DD2C0 ; =0x000065A0
	add r0, r4, r0
	bl MOD14_021E1704
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DD2B8:
	pop {r3, r4, r5, pc}
	nop
_021DD2BC: .word 0x00005DC0
_021DD2C0: .word 0x000065A0

	thumb_func_start MOD14_021DD2C4
MOD14_021DD2C4: ; 0x021DD2C4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrh r0, [r5, #6]
	ldr r4, [r5, #0xc]
	cmp r0, #0
	beq _021DD2D6
	cmp r0, #1
	beq _021DD2E6
	pop {r3, r4, r5, pc}
_021DD2D6:
	ldr r0, _021DD304 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021E0190
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DD2E6:
	ldr r0, _021DD304 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021E01BC
	cmp r0, #0
	beq _021DD300
	ldr r0, _021DD308 ; =0x000065A0
	add r0, r4, r0
	bl MOD14_021E1704
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DD300:
	pop {r3, r4, r5, pc}
	nop
_021DD304: .word 0x00005DC0
_021DD308: .word 0x000065A0

	thumb_func_start MOD14_021DD30C
MOD14_021DD30C: ; 0x021DD30C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	mov r0, #0x16
	ldr r4, [r7, #0xc]
	lsl r0, r0, #4
	ldr r5, [r4, r0]
	add r0, r5, #0
	bl MOD14_021DC430
	add r6, r0, #0
	add r0, r5, #0
	bl MOD14_021DC3F4
	cmp r0, #2
	bne _021DD336
	ldr r0, _021DD374 ; =0x00005DC0
	add r1, r6, #0
	add r0, r4, r0
	bl MOD14_021DFFD8
	b _021DD36C
_021DD336:
	add r0, r5, #0
	bl MOD14_021DC3CC
	cmp r0, #0
	beq _021DD358
	cmp r0, #1
	bne _021DD36C
	add r0, r5, #0
	bl MOD14_021DC3E8
	add r1, r0, #0
	ldr r0, _021DD378 ; =0x0000B22C
	add r2, r6, #0
	add r0, r4, r0
	bl MOD14_021E3024
	b _021DD36C
_021DD358:
	add r0, r5, #0
	bl MOD14_021DC3E0
	add r1, r0, #0
	mov r0, #0x43
	lsl r0, r0, #4
	add r0, r4, r0
	add r2, r6, #0
	bl MOD14_021DEEF8
_021DD36C:
	add r0, r7, #0
	bl MOD14_021DCBD8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DD374: .word 0x00005DC0
_021DD378: .word 0x0000B22C

	thumb_func_start MOD14_021DD37C
MOD14_021DD37C: ; 0x021DD37C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrh r0, [r5, #6]
	ldr r4, [r5, #0xc]
	cmp r0, #0
	beq _021DD38E
	cmp r0, #1
	beq _021DD3A6
	pop {r3, r4, r5, pc}
_021DD38E:
	ldr r0, _021DD3C4 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021E022C
	ldr r0, _021DD3C8 ; =0x0000B3A8
	ldr r0, [r4, r0]
	bl MOD14_021E4F58
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DD3A6:
	ldr r0, _021DD3C8 ; =0x0000B3A8
	ldr r0, [r4, r0]
	bl MOD14_021E4FA0
	cmp r0, #0
	beq _021DD3C0
	ldr r0, _021DD3C4 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021E0244
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DD3C0:
	pop {r3, r4, r5, pc}
	nop
_021DD3C4: .word 0x00005DC0
_021DD3C8: .word 0x0000B3A8

	thumb_func_start MOD14_021DD3CC
MOD14_021DD3CC: ; 0x021DD3CC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r0, #0x16
	ldr r4, [r5, #0xc]
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC450
	add r1, r0, #0
	ldr r0, _021DD3F0 ; =0x000065F4
	add r0, r4, r0
	bl MOD14_021E189C
	add r0, r5, #0
	bl MOD14_021DCBD8
	pop {r3, r4, r5, pc}
	nop
_021DD3F0: .word 0x000065F4

	thumb_func_start MOD14_021DD3F4
MOD14_021DD3F4: ; 0x021DD3F4
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r0, #0x16
	ldr r4, [r6, #0xc]
	lsl r0, r0, #4
	ldr r5, [r4, r0]
	add r0, r5, #0
	bl MOD14_021DC450
	add r1, r0, #0
	ldr r0, _021DD424 ; =0x000065F4
	add r0, r4, r0
	bl MOD14_021E189C
	ldr r0, _021DD424 ; =0x000065F4
	add r5, #0x74
	add r0, r4, r0
	add r1, r5, #0
	bl MOD14_021E19D0
	add r0, r6, #0
	bl MOD14_021DCBD8
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DD424: .word 0x000065F4

	thumb_func_start MOD14_021DD428
MOD14_021DD428: ; 0x021DD428
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	ldr r0, _021DD440 ; =0x000065F4
	add r0, r1, r0
	bl MOD14_021E1B44
	add r0, r4, #0
	bl MOD14_021DCBD8
	pop {r4, pc}
	nop
_021DD440: .word 0x000065F4

	thumb_func_start MOD14_021DD444
MOD14_021DD444: ; 0x021DD444
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	ldr r0, _021DD45C ; =0x000065F4
	add r0, r1, r0
	bl MOD14_021E1B78
	add r0, r4, #0
	bl MOD14_021DCBD8
	pop {r4, pc}
	nop
_021DD45C: .word 0x000065F4

	thumb_func_start MOD14_021DD460
MOD14_021DD460: ; 0x021DD460
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r0, #0x16
	ldr r4, [r6, #0xc]
	lsl r0, r0, #4
	ldr r5, [r4, r0]
	ldr r0, _021DD488 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _021DD48C ; =0x000065F4
	add r5, #0x74
	add r0, r4, r0
	add r1, r5, #0
	bl MOD14_021E1B9C
	add r0, r6, #0
	bl MOD14_021DCBD8
	pop {r4, r5, r6, pc}
	nop
_021DD488: .word 0x000005DC
_021DD48C: .word 0x000065F4

	thumb_func_start MOD14_021DD490
MOD14_021DD490: ; 0x021DD490
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r0, #0x16
	ldr r4, [r6, #0xc]
	lsl r0, r0, #4
	ldr r5, [r4, r0]
	ldr r0, _021DD4B8 ; =0x000005DD
	bl FUN_020054C8
	ldr r0, _021DD4BC ; =0x000065F4
	add r5, #0x74
	add r0, r4, r0
	add r1, r5, #0
	bl MOD14_021E1BE4
	add r0, r6, #0
	bl MOD14_021DCBD8
	pop {r4, r5, r6, pc}
	nop
_021DD4B8: .word 0x000005DD
_021DD4BC: .word 0x000065F4

	thumb_func_start MOD14_021DD4C0
MOD14_021DD4C0: ; 0x021DD4C0
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD4D2
	cmp r0, #1
	beq _021DD4E2
	pop {r4, pc}
_021DD4D2:
	ldr r0, _021DD4F8 ; =0x0000662C
	add r0, r1, r0
	bl MOD14_021E1F98
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD4E2:
	ldr r0, _021DD4F8 ; =0x0000662C
	add r0, r1, r0
	bl MOD14_021E1FB8
	cmp r0, #0
	beq _021DD4F4
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD4F4:
	pop {r4, pc}
	nop
_021DD4F8: .word 0x0000662C

	thumb_func_start MOD14_021DD4FC
MOD14_021DD4FC: ; 0x021DD4FC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrh r0, [r5, #6]
	ldr r4, [r5, #0xc]
	cmp r0, #0
	beq _021DD50E
	cmp r0, #1
	beq _021DD524
	pop {r3, r4, r5, pc}
_021DD50E:
	ldr r0, _021DD52C ; =0x000005DD
	bl FUN_020054C8
	ldr r0, _021DD530 ; =0x0000662C
	add r0, r4, r0
	bl MOD14_021E1FC0
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DD524:
	add r0, r5, #0
	bl MOD14_021DCBD8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DD52C: .word 0x000005DD
_021DD530: .word 0x0000662C

	thumb_func_start MOD14_021DD534
MOD14_021DD534: ; 0x021DD534
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD546
	cmp r0, #1
	beq _021DD556
	pop {r4, pc}
_021DD546:
	ldr r0, _021DD56C ; =0x0000662C
	add r0, r1, r0
	bl MOD14_021E1FE4
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD556:
	ldr r0, _021DD56C ; =0x0000662C
	add r0, r1, r0
	bl MOD14_021E1FF0
	cmp r0, #0
	beq _021DD568
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD568:
	pop {r4, pc}
	nop
_021DD56C: .word 0x0000662C

	thumb_func_start MOD14_021DD570
MOD14_021DD570: ; 0x021DD570
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD582
	cmp r0, #1
	beq _021DD594
	pop {r4, pc}
_021DD582:
	mov r0, #0x43
	lsl r0, r0, #4
	add r0, r1, r0
	bl MOD14_021DE8C8
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD594:
	mov r0, #0x43
	lsl r0, r0, #4
	add r0, r1, r0
	bl MOD14_021DE8E8
	cmp r0, #0
	beq _021DD5A8
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD5A8:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DD5AC
MOD14_021DD5AC: ; 0x021DD5AC
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r0, #0x16
	ldr r5, [r4, #0xc]
	lsl r0, r0, #4
	ldr r6, [r5, r0]
	ldrh r0, [r4, #6]
	cmp r0, #3
	bhi _021DD65E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DD5CA: ; jump table
	.short _021DD5D2 - _021DD5CA - 2 ; case 0
	.short _021DD5E8 - _021DD5CA - 2 ; case 1
	.short _021DD626 - _021DD5CA - 2 ; case 2
	.short _021DD64C - _021DD5CA - 2 ; case 3
_021DD5D2:
	ldr r0, _021DD660 ; =0x000005DD
	bl FUN_020054C8
	ldr r0, _021DD664 ; =0x00005DC0
	add r0, r5, r0
	bl MOD14_021DFBB8
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, r5, r6, pc}
_021DD5E8:
	ldr r0, _021DD664 ; =0x00005DC0
	add r0, r5, r0
	bl MOD14_021DFC2C
	cmp r0, #0
	beq _021DD65E
	add r0, r6, #0
	bl MOD14_021DC3CC
	cmp r0, #3
	beq _021DD604
	cmp r0, #4
	beq _021DD610
	b _021DD61A
_021DD604:
	ldr r0, _021DD668 ; =0x00006558
	mov r1, #1
	add r0, r5, r0
	bl MOD14_021E0D60
	b _021DD61A
_021DD610:
	ldr r0, _021DD668 ; =0x00006558
	mov r1, #2
	add r0, r5, r0
	bl MOD14_021E0D60
_021DD61A:
	mov r0, #0
	strh r0, [r4, #8]
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, r5, r6, pc}
_021DD626:
	ldrh r0, [r4, #8]
	add r0, r0, #1
	strh r0, [r4, #8]
	ldrh r0, [r4, #8]
	cmp r0, #6
	blo _021DD65E
	ldr r0, _021DD664 ; =0x00005DC0
	add r0, r5, r0
	bl MOD14_021DFD24
	ldr r0, _021DD668 ; =0x00006558
	mov r1, #0
	add r0, r5, r0
	bl MOD14_021E0D60
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, r5, r6, pc}
_021DD64C:
	ldr r0, _021DD664 ; =0x00005DC0
	add r0, r5, r0
	bl MOD14_021DFD80
	cmp r0, #0
	beq _021DD65E
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD65E:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DD660: .word 0x000005DD
_021DD664: .word 0x00005DC0
_021DD668: .word 0x00006558

	thumb_func_start MOD14_021DD66C
MOD14_021DD66C: ; 0x021DD66C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrh r0, [r5, #6]
	ldr r4, [r5, #0xc]
	cmp r0, #0
	beq _021DD67E
	cmp r0, #1
	beq _021DD69C
	pop {r3, r4, r5, pc}
_021DD67E:
	ldr r0, _021DD6B0 ; =0x00000633
	bl FUN_020054C8
	ldr r0, _021DD6B4 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021DFF1C
	ldr r0, _021DD6B8 ; =0x0000B22C
	add r0, r4, r0
	bl MOD14_021E2B10
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DD69C:
	ldr r0, _021DD6B8 ; =0x0000B22C
	add r0, r4, r0
	bl MOD14_021E2B40
	cmp r0, #0
	beq _021DD6AE
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DD6AE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DD6B0: .word 0x00000633
_021DD6B4: .word 0x00005DC0
_021DD6B8: .word 0x0000B22C

	thumb_func_start MOD14_021DD6BC
MOD14_021DD6BC: ; 0x021DD6BC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r5, [r4, #0xc]
	cmp r0, #3
	bhi _021DD72C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DD6D4: ; jump table
	.short _021DD6DC - _021DD6D4 - 2 ; case 0
	.short _021DD6EA - _021DD6D4 - 2 ; case 1
	.short _021DD6FC - _021DD6D4 - 2 ; case 2
	.short _021DD712 - _021DD6D4 - 2 ; case 3
_021DD6DC:
	ldr r0, _021DD730 ; =0x0000B3A8
	ldr r0, [r5, r0]
	bl MOD14_021E4DF8
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
_021DD6EA:
	ldr r0, _021DD730 ; =0x0000B3A8
	ldr r0, [r5, r0]
	bl MOD14_021E4E24
	cmp r0, #0
	beq _021DD72C
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
_021DD6FC:
	ldr r0, _021DD734 ; =0x00000634
	bl FUN_020054C8
	ldr r0, _021DD738 ; =0x0000B22C
	add r0, r5, r0
	bl MOD14_021E2BB0
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r3, r4, r5, pc}
_021DD712:
	ldr r0, _021DD738 ; =0x0000B22C
	add r0, r5, r0
	bl MOD14_021E2BD0
	cmp r0, #0
	beq _021DD72C
	ldr r0, _021DD73C ; =0x00005DC0
	add r0, r5, r0
	bl MOD14_021DFF54
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD72C:
	pop {r3, r4, r5, pc}
	nop
_021DD730: .word 0x0000B3A8
_021DD734: .word 0x00000634
_021DD738: .word 0x0000B22C
_021DD73C: .word 0x00005DC0

	thumb_func_start MOD14_021DD740
MOD14_021DD740: ; 0x021DD740
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD752
	cmp r0, #1
	beq _021DD762
	pop {r4, pc}
_021DD752:
	ldr r0, _021DD778 ; =0x0000B22C
	add r0, r1, r0
	bl MOD14_021E2C7C
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD762:
	ldr r0, _021DD778 ; =0x0000B22C
	add r0, r1, r0
	bl MOD14_021E2DA4
	cmp r0, #0
	beq _021DD774
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD774:
	pop {r4, pc}
	nop
_021DD778: .word 0x0000B22C

	thumb_func_start MOD14_021DD77C
MOD14_021DD77C: ; 0x021DD77C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrh r1, [r5, #6]
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r4, [r5, #0xc]
	cmp r1, #0
	ldr r0, [r4, r0]
	beq _021DD794
	cmp r1, #1
	beq _021DD7B4
	pop {r3, r4, r5, pc}
_021DD794:
	bl MOD14_021DC3CC
	cmp r0, #1
	bne _021DD7AC
	ldr r0, _021DD7C8 ; =0x0000B22C
	add r0, r4, r0
	bl MOD14_021E2DB4
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r3, r4, r5, pc}
_021DD7AC:
	add r0, r5, #0
	bl MOD14_021DCBD8
	pop {r3, r4, r5, pc}
_021DD7B4:
	ldr r0, _021DD7C8 ; =0x0000B22C
	add r0, r4, r0
	bl MOD14_021E2E50
	cmp r0, #0
	beq _021DD7C6
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DD7C6:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DD7C8: .word 0x0000B22C

	thumb_func_start MOD14_021DD7CC
MOD14_021DD7CC: ; 0x021DD7CC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r0, #0x43
	ldr r4, [r5, #0xc]
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD14_021DEEA8
	ldr r0, _021DD7F4 ; =0x0000B22C
	add r0, r4, r0
	bl MOD14_021E2FE8
	ldr r0, _021DD7F8 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021DFFB4
	add r0, r5, #0
	bl MOD14_021DCBD8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DD7F4: .word 0x0000B22C
_021DD7F8: .word 0x00005DC0

	thumb_func_start MOD14_021DD7FC
MOD14_021DD7FC: ; 0x021DD7FC
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r0, #0x16
	ldr r4, [r5, #0xc]
	lsl r0, r0, #4
	ldr r6, [r4, r0]
	ldrh r0, [r5, #6]
	cmp r0, #0
	beq _021DD818
	cmp r0, #1
	beq _021DD828
	cmp r0, #2
	beq _021DD854
	pop {r4, r5, r6, pc}
_021DD818:
	ldr r0, _021DD868 ; =0x0000B3A4
	ldr r0, [r4, r0]
	bl MOD14_021E37B8
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r4, r5, r6, pc}
_021DD828:
	ldr r0, _021DD868 ; =0x0000B3A4
	ldr r0, [r4, r0]
	bl MOD14_021E389C
	cmp r0, #0
	beq _021DD866
	add r6, #0x9c
	ldrb r0, [r6]
	cmp r0, #0
	bne _021DD844
	add r0, r5, #0
	bl MOD14_021DCBD8
	pop {r4, r5, r6, pc}
_021DD844:
	ldr r0, _021DD868 ; =0x0000B3A4
	ldr r0, [r4, r0]
	bl MOD14_021E3B54
	ldrh r0, [r5, #6]
	add r0, r0, #1
	strh r0, [r5, #6]
	pop {r4, r5, r6, pc}
_021DD854:
	ldr r0, _021DD868 ; =0x0000B3A4
	ldr r0, [r4, r0]
	bl MOD14_021E3B80
	cmp r0, #0
	beq _021DD866
	add r0, r5, #0
	bl MOD14_021DCBD8
_021DD866:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DD868: .word 0x0000B3A4

	thumb_func_start MOD14_021DD86C
MOD14_021DD86C: ; 0x021DD86C
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD87E
	cmp r0, #1
	beq _021DD88E
	pop {r4, pc}
_021DD87E:
	ldr r0, _021DD8A4 ; =0x0000B3A4
	ldr r0, [r1, r0]
	bl MOD14_021E3BA8
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD88E:
	ldr r0, _021DD8A4 ; =0x0000B3A4
	ldr r0, [r1, r0]
	bl MOD14_021E3C60
	cmp r0, #0
	beq _021DD8A0
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD8A0:
	pop {r4, pc}
	nop
_021DD8A4: .word 0x0000B3A4

	thumb_func_start MOD14_021DD8A8
MOD14_021DD8A8: ; 0x021DD8A8
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	ldr r0, _021DD8C0 ; =0x0000B3A4
	ldr r0, [r1, r0]
	bl MOD14_021E4734
	add r0, r4, #0
	bl MOD14_021DCBD8
	pop {r4, pc}
	nop
_021DD8C0: .word 0x0000B3A4

	thumb_func_start MOD14_021DD8C4
MOD14_021DD8C4: ; 0x021DD8C4
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	ldr r0, _021DD8DC ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021E0008
	add r0, r4, #0
	bl MOD14_021DCBD8
	pop {r4, pc}
	nop
_021DD8DC: .word 0x00005DC0

	thumb_func_start MOD14_021DD8E0
MOD14_021DD8E0: ; 0x021DD8E0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r4, [r5, #0xc]
	ldr r0, _021DD900 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021E002C
	mov r0, #0x43
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD14_021DEF94
	add r0, r5, #0
	bl MOD14_021DCBD8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DD900: .word 0x00005DC0

	thumb_func_start MOD14_021DD904
MOD14_021DD904: ; 0x021DD904
	push {r4, lr}
	add r4, r1, #0
	mov r0, #0x43
	ldr r1, [r4, #0xc]
	lsl r0, r0, #4
	add r0, r1, r0
	bl MOD14_021DF03C
	add r0, r4, #0
	bl MOD14_021DCBD8
	pop {r4, pc}

	thumb_func_start MOD14_021DD91C
MOD14_021DD91C: ; 0x021DD91C
	push {r4, lr}
	add r4, r1, #0
	mov r0, #0x43
	ldr r1, [r4, #0xc]
	lsl r0, r0, #4
	add r0, r1, r0
	bl MOD14_021DEF94
	add r0, r4, #0
	bl MOD14_021DCBD8
	pop {r4, pc}

	thumb_func_start MOD14_021DD934
MOD14_021DD934: ; 0x021DD934
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD946
	cmp r0, #1
	beq _021DD956
	pop {r4, pc}
_021DD946:
	ldr r0, _021DD96C ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021DF758
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD956:
	ldr r0, _021DD96C ; =0x00005DC0
	add r0, r1, r0
	bl MOD14_021DF7A0
	cmp r0, #0
	beq _021DD968
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD968:
	pop {r4, pc}
	nop
_021DD96C: .word 0x00005DC0

	thumb_func_start MOD14_021DD970
MOD14_021DD970: ; 0x021DD970
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	ldr r0, _021DD988 ; =0x0000B3AC
	ldr r0, [r1, r0]
	mov r1, #0
	bl MOD14_021E5214
	add r0, r4, #0
	bl MOD14_021DCBD8
	pop {r4, pc}
	.align 2, 0
_021DD988: .word 0x0000B3AC

	thumb_func_start MOD14_021DD98C
MOD14_021DD98C: ; 0x021DD98C
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	ldr r0, _021DD9A4 ; =0x0000B3AC
	ldr r0, [r1, r0]
	mov r1, #1
	bl MOD14_021E5214
	add r0, r4, #0
	bl MOD14_021DCBD8
	pop {r4, pc}
	.align 2, 0
_021DD9A4: .word 0x0000B3AC

	thumb_func_start MOD14_021DD9A8
MOD14_021DD9A8: ; 0x021DD9A8
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #6]
	ldr r1, [r4, #0xc]
	cmp r0, #0
	beq _021DD9BA
	cmp r0, #1
	beq _021DD9CA
	pop {r4, pc}
_021DD9BA:
	ldr r0, _021DD9E0 ; =0x0000B3AC
	ldr r0, [r1, r0]
	bl MOD14_021E52C0
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r4, pc}
_021DD9CA:
	ldr r0, _021DD9E0 ; =0x0000B3AC
	ldr r0, [r1, r0]
	bl MOD14_021E52E0
	cmp r0, #0
	beq _021DD9DC
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DD9DC:
	pop {r4, pc}
	nop
_021DD9E0: .word 0x0000B3AC

	thumb_func_start MOD14_021DD9E4
MOD14_021DD9E4: ; 0x021DD9E4
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldrh r0, [r4, #6]
	cmp r0, #0
	beq _021DD9F8
	cmp r0, #1
	beq _021DDA20
	add sp, #0xc
	pop {r3, r4, pc}
_021DD9F8:
	ldr r0, _021DDA34 ; =0x0000060E
	bl FUN_020054C8
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldrh r0, [r4, #6]
	add sp, #0xc
	add r0, r0, #1
	strh r0, [r4, #6]
	pop {r3, r4, pc}
_021DDA20:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DDA2E
	add r0, r4, #0
	bl MOD14_021DCBD8
_021DDA2E:
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_021DDA34: .word 0x0000060E

	thumb_func_start MOD14_021DDA38
MOD14_021DDA38: ; 0x021DDA38
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021DDB20 ; =0x021E63A4
	add r4, r1, #0
	bl FUN_0201E66C
	ldr r2, _021DDB24 ; =0x04000304
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	mov r0, #1
	mov r1, #0
	add r2, r0, #0
	bl GX_SetGraphicsMode
	ldr r0, _021DDB28 ; =0x021E627C
	bl FUN_02016BBC
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, _021DDB2C ; =0x021E6350
	mov r1, #1
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, _021DDB30 ; =0x021E6334
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, _021DDB34 ; =0x021E62FC
	mov r1, #3
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021DDADA
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, _021DDB38 ; =0x021E6318
	mov r1, #4
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, _021DDB3C ; =0x021E62E0
	mov r1, #5
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, _021DDB40 ; =0x021E62C4
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, _021DDB44 ; =0x021E62A8
	mov r1, #7
	mov r3, #0
	bl FUN_02016C18
	b _021DDB1A
_021DDADA:
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, _021DDB38 ; =0x021E6318
	mov r1, #4
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, _021DDB48 ; =0x021E6388
	mov r1, #5
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, _021DDB4C ; =0x021E628C
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, _021DDB44 ; =0x021E62A8
	mov r1, #7
	mov r3, #0
	bl FUN_02016C18
_021DDB1A:
	bl MOD14_021DDC78
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DDB20: .word 0x021E63A4
_021DDB24: .word 0x04000304
_021DDB28: .word 0x021E627C
_021DDB2C: .word 0x021E6350
_021DDB30: .word 0x021E6334
_021DDB34: .word 0x021E62FC
_021DDB38: .word 0x021E6318
_021DDB3C: .word 0x021E62E0
_021DDB40: .word 0x021E62C4
_021DDB44: .word 0x021E62A8
_021DDB48: .word 0x021E6388
_021DDB4C: .word 0x021E628C

	thumb_func_start MOD14_021DDB50
MOD14_021DDB50: ; 0x021DDB50
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r3, #1
	mov r2, #0x57
	add r4, r1, #0
	str r3, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	mov r0, #0x12
	mov r1, #4
	bl FUN_0200687C
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	add r3, r2, #0
	bl FUN_02018540
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02017CD0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r1, #1
	mov r2, #0x57
	str r1, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	mov r0, #0x12
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0xe0
	str r0, [sp]
	mov r0, #0xa
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x12
	mov r1, #5
	add r3, r2, #0
	bl FUN_02006930
	add r0, r4, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021DDBF2
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xa
	mov r2, #0x57
	str r0, [sp, #0xc]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	mov r0, #0x12
	mov r3, #2
	bl FUN_020068C8
_021DDBF2:
	mov r0, #0x43
	lsl r0, r0, #4
	add r0, r5, r0
	bl MOD14_021DE014
	mov r0, #0x43
	lsl r0, r0, #4
	add r1, r4, #0
	add r0, r5, r0
	add r1, #0x40
	mov r2, #0
	mov r3, #1
	bl MOD14_021DE0C4
	ldr r0, _021DDC60 ; =0x000065A0
	add r0, r5, r0
	bl MOD14_021E0F40
	ldr r0, _021DDC64 ; =0x000065F4
	add r0, r5, r0
	bl MOD14_021E1818
	ldr r0, _021DDC68 ; =0x0000662C
	add r0, r5, r0
	bl MOD14_021E1EEC
	ldr r0, _021DDC6C ; =0x0000B3A4
	ldr r0, [r5, r0]
	bl MOD14_021E355C
	ldr r0, _021DDC70 ; =0x0000B3AC
	ldr r0, [r5, r0]
	bl MOD14_021E5128
	add r0, r4, #0
	bl MOD14_021DC3CC
	cmp r0, #1
	bne _021DDC48
	ldr r0, _021DDC74 ; =0x0000B22C
	add r0, r5, r0
	bl MOD14_021E2AE8
_021DDC48:
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	bl GX_DispOn
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DDC60: .word 0x000065A0
_021DDC64: .word 0x000065F4
_021DDC68: .word 0x0000662C
_021DDC6C: .word 0x0000B3A4
_021DDC70: .word 0x0000B3AC
_021DDC74: .word 0x0000B22C

	thumb_func_start MOD14_021DDC78
MOD14_021DDC78: ; 0x021DDC78
	push {r3, lr}
	bl FUN_020BB7F4
	bl G3X_InitMtxStack
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	ldr r0, _021DDCDC ; =0x04000008
	mov r1, #3
	ldrh r2, [r0]
	bic r2, r1
	mov r1, #1
	orr r1, r2
	strh r1, [r0]
	add r0, #0x58
	ldrh r1, [r0]
	ldr r2, _021DDCE0 ; =0xFFFFCFFD
	and r1, r2
	strh r1, [r0]
	ldrh r3, [r0]
	add r1, r2, #2
	and r3, r1
	mov r1, #0x10
	orr r1, r3
	strh r1, [r0]
	ldrh r3, [r0]
	ldr r1, _021DDCE4 ; =0x0000CFFB
	and r1, r3
	strh r1, [r0]
	add r1, r2, #2
	ldrh r3, [r0]
	lsr r2, r2, #0x11
	and r3, r1
	mov r1, #8
	orr r1, r3
	strh r1, [r0]
	mov r0, #0
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _021DDCE8 ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _021DDCEC ; =0xBFFF0000
	str r0, [r1, #0x40]
	pop {r3, pc}
	.align 2, 0
_021DDCDC: .word 0x04000008
_021DDCE0: .word 0xFFFFCFFD
_021DDCE4: .word 0x0000CFFB
_021DDCE8: .word 0x04000540
_021DDCEC: .word 0xBFFF0000

	thumb_func_start MOD14_021DDCF0
MOD14_021DDCF0: ; 0x021DDCF0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021DDD10 ; =0x00005DC0
	add r0, r4, r0
	bl MOD14_021DF144
	ldr r0, _021DDD14 ; =0x00006558
	add r0, r4, r0
	bl MOD14_021E0CCC
	ldr r0, _021DDD18 ; =0x0000B3A8
	ldr r0, [r4, r0]
	bl MOD14_021E49C4
	pop {r4, pc}
	nop
_021DDD10: .word 0x00005DC0
_021DDD14: .word 0x00006558
_021DDD18: .word 0x0000B3A8

	thumb_func_start MOD14_021DDD1C
MOD14_021DDD1C: ; 0x021DDD1C
	cmp r1, r0
	bls _021DDD2A
	mov r2, #0x12
	sub r3, r1, r0
	sub r1, r2, r1
	add r0, r0, r1
	b _021DDD32
_021DDD2A:
	mov r2, #0x12
	sub r2, r2, r0
	add r3, r1, r2
	sub r0, r0, r1
_021DDD32:
	cmp r3, r0
	blt _021DDD3C
	mov r0, #0
	mvn r0, r0
	bx lr
_021DDD3C:
	mov r0, #1
	bx lr

	thumb_func_start MOD14_021DDD40
MOD14_021DDD40: ; 0x021DDD40
	ldr r3, _021DDD44 ; =0x0200CA61
	bx r3
	.align 2, 0
_021DDD44: .word 0x0200CA61

	thumb_func_start MOD14_021DDD48
MOD14_021DDD48: ; 0x021DDD48
	mov r1, #0x51
	lsl r1, r1, #2
	add r0, r0, r1
	bx lr

	thumb_func_start MOD14_021DDD50
MOD14_021DDD50: ; 0x021DDD50
	mov r1, #0x59
	lsl r1, r1, #2
	add r0, r0, r1
	bx lr

	thumb_func_start MOD14_021DDD58
MOD14_021DDD58: ; 0x021DDD58
	mov r1, #0x43
	lsl r1, r1, #4
	add r0, r0, r1
	bx lr

	thumb_func_start MOD14_021DDD60
MOD14_021DDD60: ; 0x021DDD60
	ldr r1, _021DDD68 ; =0x0000B22C
	add r0, r0, r1
	bx lr
	nop
_021DDD68: .word 0x0000B22C

	thumb_func_start MOD14_021DDD6C
MOD14_021DDD6C: ; 0x021DDD6C
	ldr r1, _021DDD74 ; =0x00005DC0
	add r0, r0, r1
	bx lr
	nop
_021DDD74: .word 0x00005DC0

	thumb_func_start MOD14_021DDD78
MOD14_021DDD78: ; 0x021DDD78
	ldr r1, _021DDD80 ; =0x0000B3A8
	ldr r0, [r0, r1]
	bx lr
	nop
_021DDD80: .word 0x0000B3A8

	thumb_func_start MOD14_021DDD84
MOD14_021DDD84: ; 0x021DDD84
	ldr r1, _021DDD8C ; =0x0000662C
	add r0, r0, r1
	bx lr
	nop
_021DDD8C: .word 0x0000662C

	thumb_func_start MOD14_021DDD90
MOD14_021DDD90: ; 0x021DDD90
	mov r1, #0x56
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD14_021DDD98
MOD14_021DDD98: ; 0x021DDD98
	push {r3, lr}
	mov r1, #0x16
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021DDDAC
	mov r0, #0
	pop {r3, pc}
_021DDDAC:
	mov r0, #0x2b
	mvn r0, r0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD14_021DDDB4
MOD14_021DDDB4: ; 0x021DDDB4
	str r1, [r0]
	str r2, [r0, #8]
	ldr r1, [sp]
	str r3, [r0, #0xc]
	str r1, [r0, #0x10]
	add r1, r0, #0
	ldr r2, [sp, #4]
	add r1, #0x20
	strb r2, [r1]
	mov r1, #0
	str r1, [r0, #4]
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DDDD4
MOD14_021DDDD4: ; 0x021DDDD4
	push {r3, r4, r5, lr}
	sub sp, #0x20
	str r0, [sp]
	lsl r0, r2, #0xc
	str r0, [sp, #8]
	lsl r0, r3, #0xc
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x30]
	str r1, [sp, #4]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x34]
	str r0, [sp, #0x18]
	mov r0, #0xa
	str r0, [sp, #0x1c]
	bl OS_DisableInterrupts
	add r4, r0, #0
	add r0, sp, #0
	bl FUN_0201FF84
	add r5, r0, #0
	add r0, r4, #0
	bl OS_RestoreInterrupts
	cmp r5, #0
	beq _021DDE1E
	add r0, r5, #0
	mov r1, #1
	bl FUN_020200BC
	mov r1, #1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_020200D8
_021DDE1E:
	add r0, r5, #0
	add sp, #0x20
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021DDE24
MOD14_021DDE24: ; 0x021DDE24
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl OS_DisableInterrupts
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02020310
	add r0, r6, #0
	bl OS_RestoreInterrupts
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021DDE40
MOD14_021DDE40: ; 0x021DDE40
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	lsl r1, r3, #0x1b
	lsr r1, r1, #0x13
	mov ip, r1
	asr r1, r3, #5
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x13
	mov lr, r1
	asr r1, r3, #0xa
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x13
	str r1, [sp, #4]
	add r7, r0, #0
	str r2, [sp]
	add r1, r2, #0
	sub r2, r2, #1
	ldr r0, [sp, #0x20]
	str r2, [sp]
	cmp r1, #0
	beq _021DDED6
_021DDE6C:
	ldrh r1, [r7]
	add r7, r7, #2
	lsl r2, r1, #0x1b
	lsr r4, r2, #0x13
	asr r2, r1, #5
	asr r1, r1, #0xa
	lsl r2, r2, #0x1b
	lsl r1, r1, #0x1b
	lsr r3, r2, #0x13
	lsr r2, r1, #0x13
	mov r1, ip
	sub r5, r1, r4
	asr r1, r5, #3
	lsr r1, r1, #0x1c
	add r1, r5, r1
	asr r1, r1, #4
	mul r1, r0
	add r5, r4, r1
	mov r1, lr
	sub r1, r1, r3
	asr r4, r1, #3
	lsr r4, r4, #0x1c
	add r4, r1, r4
	asr r1, r4, #4
	mul r1, r0
	add r3, r3, r1
	ldr r1, [sp, #4]
	sub r1, r1, r2
	asr r4, r1, #3
	lsr r4, r4, #0x1c
	add r4, r1, r4
	asr r1, r4, #4
	mul r1, r0
	add r4, r2, r1
	asr r2, r5, #8
	mov r1, #0x1f
	and r1, r2
	asr r2, r3, #8
	asr r3, r4, #8
	lsl r3, r3, #0x1b
	lsl r2, r2, #0x1b
	lsr r3, r3, #0x11
	lsr r2, r2, #0x16
	orr r2, r3
	orr r1, r2
	strh r1, [r6]
	ldr r1, [sp]
	add r6, r6, #2
	add r2, r1, #0
	sub r2, r2, #1
	str r2, [sp]
	cmp r1, #0
	bne _021DDE6C
_021DDED6:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021DDEDC
MOD14_021DDEDC: ; 0x021DDEDC
	ldr r1, _021DDEE4 ; =0x0000B3B0
	ldr r0, [r0, r1]
	bx lr
	nop
_021DDEE4: .word 0x0000B3B0

	thumb_func_start MOD14_021DDEE8
MOD14_021DDEE8: ; 0x021DDEE8
	ldr r0, _021DDEF0 ; =0x021E6A0C
	mov r1, #0
	str r1, [r0]
	bx lr
	.align 2, 0
_021DDEF0: .word 0x021E6A0C

	thumb_func_start MOD14_021DDEF4
MOD14_021DDEF4: ; 0x021DDEF4
	push {r4, r5, r6, lr}
	ldr r6, _021DDF28 ; =0x021E6A0C
	ldr r0, [r6]
	cmp r0, #0
	beq _021DDF26
	mov r4, #0
	cmp r0, #0
	bls _021DDF20
	ldr r5, _021DDF2C ; =0x021E6A10
_021DDF06:
	ldr r0, [r5, #8]
	bl FUN_02016A18
	ldr r1, [r5]
	cmp r1, #0
	beq _021DDF16
	ldr r0, [r5, #4]
	blx r1
_021DDF16:
	ldr r0, [r6]
	add r4, r4, #1
	add r5, #0xc
	cmp r4, r0
	blo _021DDF06
_021DDF20:
	ldr r0, _021DDF28 ; =0x021E6A0C
	mov r1, #0
	str r1, [r0]
_021DDF26:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DDF28: .word 0x021E6A0C
_021DDF2C: .word 0x021E6A10

	thumb_func_start MOD14_021DDF30
MOD14_021DDF30: ; 0x021DDF30
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _021DDF60 ; =0x021E6A0C
	add r4, r1, #0
	ldr r0, [r0]
	add r6, r2, #0
	cmp r0, #0x20
	blo _021DDF44
	bl ErrorHandling
_021DDF44:
	ldr r2, _021DDF60 ; =0x021E6A0C
	mov r1, #0xc
	ldr r0, [r2]
	ldr r3, _021DDF64 ; =0x021E6A18
	mul r1, r0
	str r5, [r3, r1]
	ldr r3, _021DDF68 ; =0x021E6A10
	add r0, r0, #1
	str r4, [r3, r1]
	ldr r3, _021DDF6C ; =0x021E6A14
	str r0, [r2]
	str r6, [r3, r1]
	pop {r4, r5, r6, pc}
	nop
_021DDF60: .word 0x021E6A0C
_021DDF64: .word 0x021E6A18
_021DDF68: .word 0x021E6A10
_021DDF6C: .word 0x021E6A14

	thumb_func_start MOD14_021DDF70
MOD14_021DDF70: ; 0x021DDF70
	push {r3, r4, r5, r6, r7, lr}
	add r6, r2, #0
	add r5, r0, #0
	add r0, r6, #0
	add r0, #0x40
	ldrb r0, [r0]
	add r4, r1, #0
	add r7, r3, #0
	strb r0, [r5]
	mov r0, #0xb
	strb r0, [r5, #1]
	mov r0, #0
	strb r0, [r5, #2]
	add r0, r4, #0
	bl MOD14_021DDD98
	ldr r1, _021DDFE0 ; =0x0000585C
	str r0, [r5, r1]
	ldr r2, [r5, r1]
	add r0, r1, #0
	add r2, #0x48
	sub r0, #8
	str r2, [r5, r0]
	mov r0, #0x11
	ldr r2, [r5, r1]
	lsl r0, r0, #4
	add r2, r2, r0
	sub r0, r1, #4
	str r2, [r5, r0]
	add r0, r4, #0
	bl MOD14_021DDD50
	ldr r1, _021DDFE4 ; =0x00005980
	mov r2, #0x1e
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	add r1, r5, #0
	add r1, #0xa8
	bl MOD14_021E08E4
	ldr r0, _021DDFE4 ; =0x00005980
	mov r1, #0x1b
	lsl r1, r1, #6
	ldr r0, [r5, r0]
	add r1, r5, r1
	mov r2, #0x1e
	bl MOD14_021E08E4
	ldr r1, _021DDFE8 ; =0x00005984
	str r7, [r5, r1]
	add r0, r1, #4
	str r6, [r5, r0]
	add r1, #8
	str r4, [r5, r1]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DDFE0: .word 0x0000585C
_021DDFE4: .word 0x00005980
_021DDFE8: .word 0x00005984

	thumb_func_start MOD14_021DDFEC
MOD14_021DDFEC: ; 0x021DDFEC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021DE010 ; =0x00005980
	add r1, r4, #0
	ldr r0, [r4, r0]
	add r1, #0xa8
	mov r2, #0x1e
	bl MOD14_021E0908
	ldr r0, _021DE010 ; =0x00005980
	mov r1, #0x1b
	lsl r1, r1, #6
	ldr r0, [r4, r0]
	add r1, r4, r1
	mov r2, #0x1e
	bl MOD14_021E0908
	pop {r4, pc}
	.align 2, 0
_021DE010: .word 0x00005980

	thumb_func_start MOD14_021DE014
MOD14_021DE014: ; 0x021DE014
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, _021DE060 ; =0x00005984
	mov r1, #3
	ldr r0, [r4, r0]
	bl FUN_02017B48
	ldr r1, _021DE064 ; =0x0000585C
	str r0, [r4, #0xc]
	ldr r1, [r4, r1]
	mov r2, #0
	sub r1, r0, r1
	add r3, r1, #0
	ldr r0, _021DE068 ; =0x000001FF
	mov r1, #3
	and r3, r0
	ldr r0, _021DE060 ; =0x00005984
	str r3, [r4, #0xc]
	ldr r0, [r4, r0]
	bl FUN_020179E0
	mov r3, #0
	str r3, [sp]
	mov r0, #0x40
	str r0, [sp, #4]
	mov r0, #0x20
	str r0, [sp, #8]
	mov r0, #9
	str r0, [sp, #0xc]
	ldr r0, _021DE060 ; =0x00005984
	mov r1, #3
	ldr r0, [r4, r0]
	mov r2, #0x18
	bl FUN_02018540
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021DE060: .word 0x00005984
_021DE064: .word 0x0000585C
_021DE068: .word 0x000001FF

	thumb_func_start MOD14_021DE06C
MOD14_021DE06C: ; 0x021DE06C
	push {r4, r5, r6, r7}
	ldr r5, [sp, #0x10]
	cmp r1, #0
	beq _021DE0A2
	ldrb r6, [r0, #2]
	mov r4, #1
	add r7, r6, #0
	mov r6, #0x69
	eor r7, r4
	lsl r6, r6, #2
	mul r6, r7
	str r6, [r2]
	mov r2, #0x17
	mul r2, r1
	ldrb r6, [r0, #1]
	mov r1, #0x3f
	add r2, r6, r2
	and r1, r2
	str r1, [r3]
	ldrb r0, [r0, #2]
	eor r0, r4
	lsl r1, r0, #1
	ldr r0, _021DE0C0 ; =0x021E656C
	ldrh r0, [r0, r1]
	str r0, [r5]
	pop {r4, r5, r6, r7}
	bx lr
_021DE0A2:
	ldrb r4, [r0, #2]
	mov r1, #0x69
	lsl r1, r1, #2
	mul r1, r4
	str r1, [r2]
	ldrb r1, [r0, #1]
	str r1, [r3]
	ldrb r0, [r0, #2]
	lsl r1, r0, #1
	ldr r0, _021DE0C0 ; =0x021E656C
	ldrh r0, [r0, r1]
	str r0, [r5]
	pop {r4, r5, r6, r7}
	bx lr
	nop
_021DE0C0: .word 0x021E656C

	thumb_func_start MOD14_021DE0C4
MOD14_021DE0C4: ; 0x021DE0C4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r6, r2, #0
	add r1, sp, #8
	add r7, r3, #0
	str r1, [sp]
	add r1, r6, #0
	add r2, sp, #0x10
	add r3, sp, #0xc
	add r5, r0, #0
	bl MOD14_021DE06C
	ldr r2, [sp, #8]
	add r0, r5, #0
	add r1, r4, #0
	add r3, r7, #0
	bl MOD14_021DE138
	ldr r2, [sp, #0x10]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021DE1D0
	ldr r0, [sp, #8]
	add r1, r4, #0
	str r0, [sp]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r0, r5, #0
	bl MOD14_021DE278
	cmp r7, #0
	beq _021DE12C
	cmp r6, #0
	bne _021DE12C
	ldrb r3, [r5, #2]
	mov r0, #0xb8
	mul r0, r6
	str r0, [sp]
	ldr r0, _021DE130 ; =0x00000618
	add r1, r5, #0
	add r1, #0xa8
	mul r0, r3
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r1, _021DE134 ; =0x00005980
	ldrb r2, [r4]
	ldr r1, [r5, r1]
	add r0, r5, #0
	bl MOD14_021DEB34
_021DE12C:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DE130: .word 0x00000618
_021DE134: .word 0x00005980

	thumb_func_start MOD14_021DE138
MOD14_021DE138: ; 0x021DE138
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r2, #0
	ldrb r2, [r1, #1]
	add r7, r0, #0
	add r5, r3, #0
	lsl r1, r2, #1
	add r2, r2, r1
	ldr r1, _021DE1C4 ; =0x021E65AE
	mov r0, #0x12
	ldrb r1, [r1, r2]
	add r2, sp, #8
	mov r3, #0xa
	bl FUN_02006C08
	str r0, [sp, #4]
	cmp r0, #0
	beq _021DE1C0
	cmp r5, #0
	beq _021DE176
	ldr r0, [sp, #8]
	mov r1, #0x20
	ldr r0, [r0, #0xc]
	bl DC_FlushRange
	ldr r0, [sp, #8]
	lsl r1, r4, #5
	ldr r0, [r0, #0xc]
	mov r2, #0x20
	bl GX_LoadBGPltt
_021DE176:
	ldr r0, _021DE1C8 ; =0x00005860
	mov r6, #0
	add r4, r6, #0
	add r5, r7, r0
_021DE17E:
	str r4, [sp]
	ldr r0, [sp, #8]
	ldr r3, _021DE1CC ; =0x00007FFF
	ldr r0, [r0, #0xc]
	add r1, r5, #0
	mov r2, #0x10
	bl MOD14_021DDE40
	add r6, r6, #1
	add r4, r4, #2
	add r5, #0x20
	cmp r6, #8
	blt _021DE17E
	mov r2, #0x10
	str r2, [sp]
	ldr r1, _021DE1C8 ; =0x00005860
	ldr r0, [sp, #8]
	add r3, r7, r1
	lsl r1, r6, #5
	add r1, r3, r1
	ldr r0, [r0, #0xc]
	ldr r3, _021DE1CC ; =0x00007FFF
	bl MOD14_021DDE40
	ldr r0, _021DE1C8 ; =0x00005860
	mov r1, #0x12
	add r0, r7, r0
	lsl r1, r1, #4
	bl DC_FlushRange
	ldr r0, [sp, #4]
	bl FUN_02016A18
_021DE1C0:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DE1C4: .word 0x021E65AE
_021DE1C8: .word 0x00005860
_021DE1CC: .word 0x00007FFF

	thumb_func_start MOD14_021DE1D0
MOD14_021DE1D0: ; 0x021DE1D0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r2, #0
	mov r2, #1
	add r5, r1, #0
	str r2, [sp]
	ldrb r3, [r5, #1]
	add r6, r0, #0
	mov r0, #0x12
	lsl r1, r3, #1
	add r3, r3, r1
	ldr r1, _021DE26C ; =0x021E65AD
	ldrb r1, [r1, r3]
	mov r3, #0xa
	bl FUN_02006C98
	str r0, [sp, #0x10]
	cmp r0, #0
	beq _021DE268
	add r1, sp, #0x14
	bl FUN_020B0030
	cmp r0, #0
	beq _021DE262
	mov r0, #0xa
	mov r1, #1
	bl FUN_02018FF4
	add r4, r0, #0
	beq _021DE250
	ldr r0, _021DE270 ; =0x00005984
	ldr r0, [r6, r0]
	str r0, [r4]
	mov r0, #0x15
	strb r0, [r4, #7]
	mov r0, #4
	strb r0, [r4, #8]
	ldr r0, [sp, #0x14]
	ldr r0, [r0, #0x14]
	str r0, [r4, #0xc]
	mov r0, #0
	ldr r1, [r5, #4]
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r0, #0xd
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021DE274 ; =0x00020100
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5, #4]
	lsr r5, r3, #1
	mov r3, #0x54
	add r0, r4, #0
	sub r3, r3, r5
	bl FUN_0201BDE0
	add r0, r4, #0
	bl FUN_02016A18
_021DE250:
	ldr r3, [sp, #0x14]
	ldr r0, _021DE270 ; =0x00005984
	str r7, [sp]
	ldr r2, [r3, #0x14]
	ldr r0, [r6, r0]
	ldr r3, [r3, #0x10]
	mov r1, #3
	bl FUN_02017E14
_021DE262:
	ldr r0, [sp, #0x10]
	bl FUN_02016A18
_021DE268:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DE26C: .word 0x021E65AD
_021DE270: .word 0x00005984
_021DE274: .word 0x00020100

	thumb_func_start MOD14_021DE278
MOD14_021DE278: ; 0x021DE278
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r2, #0
	mov r2, #1
	str r2, [sp]
	add r6, r3, #0
	ldrb r3, [r1, #1]
	add r5, r0, #0
	mov r0, #0x12
	lsl r1, r3, #1
	add r3, r3, r1
	ldr r1, _021DE2E0 ; =0x021E65AC
	ldrb r1, [r1, r3]
	mov r3, #0xa
	bl FUN_02006C98
	str r0, [sp, #4]
	cmp r0, #0
	beq _021DE2DC
	add r1, sp, #8
	bl FUN_020B0180
	ldr r0, _021DE2E4 ; =0x00005984
	mov r1, #3
	ldr r0, [r5, r0]
	bl FUN_0201886C
	add r7, r0, #0
	beq _021DE2C2
	ldr r1, [sp, #0x20]
	add r2, r4, #0
	str r1, [sp]
	ldr r1, [sp, #8]
	add r3, r6, #0
	add r1, #0xc
	bl MOD14_021DECD4
_021DE2C2:
	ldr r0, [sp, #4]
	bl FUN_02016A18
	mov r0, #0
	str r0, [sp]
	ldr r0, _021DE2E4 ; =0x00005984
	mov r3, #1
	ldr r0, [r5, r0]
	mov r1, #3
	add r2, r7, #0
	lsl r3, r3, #0xc
	bl FUN_02017CE8
_021DE2DC:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DE2E0: .word 0x021E65AC
_021DE2E4: .word 0x00005984

	thumb_func_start MOD14_021DE2E8
MOD14_021DE2E8: ; 0x021DE2E8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _021DE384 ; =0x00005984
	add r4, r1, #0
	ldr r0, [r5, r0]
	mov r1, #3
	add r6, r2, #0
	bl FUN_02017B48
	lsl r0, r0, #0x17
	lsr r1, r0, #0xb
	mov r0, #0xb8
	add r7, r6, #0
	mul r7, r0
	lsl r0, r7, #0xc
	str r1, [r5, #8]
	add r1, r1, r0
	str r1, [r5, #0x14]
	ldr r0, [r5, #8]
	sub r0, r1, r0
	mov r1, #0x1e
	bl _s32_div_f
	str r0, [r5, #0x10]
	ldr r0, [r5, #0x14]
	asr r1, r0, #0xc
	ldr r0, _021DE388 ; =0x000001FF
	and r0, r1
	str r0, [r5, #0x14]
	mov r0, #0x1e
	str r0, [r5, #4]
	ldrb r0, [r5, #2]
	strb r0, [r5, #3]
	mov r0, #0x17
	ldrb r1, [r5, #1]
	mul r0, r6
	add r0, r1, r0
	strb r0, [r5, #1]
	ldrb r1, [r5, #1]
	mov r0, #0x3f
	and r0, r1
	strb r0, [r5, #1]
	ldrb r1, [r5, #2]
	mov r0, #1
	eor r0, r1
	strb r0, [r5, #2]
	ldrb r1, [r4]
	add r0, r5, #0
	bl MOD14_021DE6B4
	ldr r1, [r5, #0x10]
	add r0, r5, #0
	add r2, r7, #0
	bl MOD14_021DE48C
	ldrb r0, [r4]
	mov r1, #1
	mov r2, #0
	str r0, [r5, #0x30]
	ldrb r0, [r5, #2]
	str r0, [r5, #0x34]
	add r0, r5, #0
	add r0, #0x98
	str r1, [r0]
	add r0, r5, #0
	add r0, #0x9c
	str r2, [r0]
	ldr r0, _021DE38C ; =MOD14_021DE39C
	add r1, r5, #0
	bl FUN_0200CA44
	ldr r0, _021DE390 ; =MOD14_021DE3E4
	add r1, r5, #0
	mov r2, #1
	bl MOD14_021DDD40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DE384: .word 0x00005984
_021DE388: .word 0x000001FF
_021DE38C: .word MOD14_021DE39C
_021DE390: .word MOD14_021DE3E4

	thumb_func_start MOD14_021DE394
MOD14_021DE394: ; 0x021DE394
	add r0, #0x9c
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021DE39C
MOD14_021DE39C: ; 0x021DE39C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021DE3C2
	add r0, r4, #0
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #2
	bne _021DE3DC
	ldr r1, [r4, #0x10]
	add r0, r4, #0
	bl MOD14_021DE514
	mov r0, #0
	add r4, #0x98
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021DE3C2:
	ldr r0, [r4, #0x14]
	str r0, [r4, #0xc]
	ldr r0, _021DE3E0 ; =0x00005988
	ldr r0, [r4, r0]
	bl MOD14_021DC424
	strb r0, [r4]
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r0, #1
	add r4, #0x9c
	str r0, [r4]
_021DE3DC:
	pop {r3, r4, r5, pc}
	nop
_021DE3E0: .word 0x00005988

	thumb_func_start MOD14_021DE3E4
MOD14_021DE3E4: ; 0x021DE3E4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldrb r3, [r5, #3]
	add r6, r0, #0
	mov r0, #1
	add r4, r3, #0
	eor r4, r0
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _021DE45C
	add r0, r5, #0
	add r0, #0x98
	ldr r2, [r0]
	cmp r2, #2
	bhs _021DE47E
	ldr r6, _021DE480 ; =0x00000618
	add r1, #0xa8
	mul r6, r3
	add r0, r5, #0
	add r1, r1, r6
	bl MOD14_021DEBCC
	ldr r1, _021DE480 ; =0x00000618
	add r2, r5, #0
	add r2, #0xa8
	mul r1, r4
	add r1, r2, r1
	add r2, r5, #0
	add r2, #0x98
	ldr r2, [r2]
	add r0, r5, #0
	bl MOD14_021DEC24
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	mov r2, #0
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0x98
	str r1, [r0]
	ldr r0, [r5, #8]
	asr r1, r0, #0xc
	ldr r0, _021DE484 ; =0x000001FF
	and r0, r1
	str r0, [r5, #0xc]
	ldr r1, [r5, #8]
	ldr r0, [r5, #0x10]
	add r0, r1, r0
	str r0, [r5, #8]
	ldr r0, _021DE488 ; =0x00005984
	ldr r3, [r5, #0xc]
	ldr r0, [r5, r0]
	mov r1, #3
	bl FUN_020179E0
	ldr r0, [r5, #4]
	sub r0, r0, #1
	str r0, [r5, #4]
	pop {r4, r5, r6, pc}
_021DE45C:
	ldr r0, _021DE488 ; =0x00005984
	ldr r3, [r5, #0x14]
	ldr r0, [r5, r0]
	mov r1, #3
	mov r2, #0
	bl FUN_020179E0
	ldr r1, _021DE480 ; =0x00000618
	add r0, r5, #0
	add r5, #0xa8
	mul r1, r4
	add r1, r5, r1
	bl MOD14_021DEC7C
	add r0, r6, #0
	bl FUN_0200CAB4
_021DE47E:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DE480: .word 0x00000618
_021DE484: .word 0x000001FF
_021DE488: .word 0x00005984

	thumb_func_start MOD14_021DE48C
MOD14_021DE48C: ; 0x021DE48C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r7, #0
	str r0, [sp, #8]
	add r0, #0xa8
	str r1, [sp]
	str r2, [sp, #4]
	add r6, r7, #0
	add r4, r5, #0
	str r0, [sp, #8]
_021DE4A2:
	ldr r0, _021DE504 ; =0x0000585C
	ldr r0, [r5, r0]
	add r0, #0x70
	add r0, r0, r6
	lsl r1, r0, #0xc
	ldr r0, [sp]
	str r1, [r4, #0x68]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	ldr r0, _021DE504 ; =0x0000585C
	ldr r0, [r5, r0]
	add r0, #0x70
	add r1, r0, r6
	ldr r0, [sp, #4]
	add r0, r0, r1
	lsl r1, r0, #0xc
	ldr r0, [sp]
	str r1, [r4, #0x38]
	sub r0, r1, r0
	str r0, [r4, #0x50]
	asr r2, r0, #0xc
	ldr r0, _021DE508 ; =0x00005854
	ldr r0, [r5, r0]
	cmp r2, r0
	ble _021DE4F6
	ldr r0, _021DE50C ; =0x00005858
	ldr r0, [r5, r0]
	cmp r2, r0
	bge _021DE4F6
	ldrb r3, [r5, #3]
	mov r1, #1
	add r0, r5, #0
	eor r1, r3
	ldr r3, _021DE510 ; =0x00000618
	mul r3, r1
	ldr r1, [sp, #8]
	add r1, r1, r3
	add r3, r7, #0
	bl MOD14_021DE5B4
_021DE4F6:
	add r7, r7, #1
	add r6, #0x18
	add r4, r4, #4
	cmp r7, #6
	blt _021DE4A2
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DE504: .word 0x0000585C
_021DE508: .word 0x00005854
_021DE50C: .word 0x00005858
_021DE510: .word 0x00000618

	thumb_func_start MOD14_021DE514
MOD14_021DE514: ; 0x021DE514
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r6, r1, #0
	ldrb r1, [r5, #3]
	str r0, [sp]
	add r0, #0xa8
	str r0, [sp]
	ldr r0, _021DE5A8 ; =0x00000618
	add r2, r1, #0
	mul r2, r0
	str r2, [sp, #4]
	mov r2, #1
	eor r1, r2
	mul r0, r1
	mov r7, #0
	add r4, r5, #0
	str r0, [sp, #8]
_021DE538:
	add r0, r4, #0
	add r0, #0x80
	ldr r1, _021DE5AC ; =0x00005854
	ldr r0, [r0]
	ldr r1, [r5, r1]
	asr r0, r0, #0xc
	cmp r0, r1
	ble _021DE550
	ldr r1, _021DE5B0 ; =0x00005858
	ldr r1, [r5, r1]
	cmp r0, r1
	blt _021DE55E
_021DE550:
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r0, r5, #0
	add r1, r2, r1
	add r2, r7, #0
	bl MOD14_021DE68C
_021DE55E:
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	sub r0, r0, r6
	str r0, [r4, #0x68]
	sub r1, r0, r6
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	ldr r0, [r4, #0x50]
	sub r0, r0, r6
	str r0, [r4, #0x38]
	sub r0, r0, r6
	str r0, [r4, #0x50]
	asr r2, r0, #0xc
	ldr r0, _021DE5AC ; =0x00005854
	ldr r0, [r5, r0]
	cmp r2, r0
	ble _021DE59A
	ldr r0, _021DE5B0 ; =0x00005858
	ldr r0, [r5, r0]
	cmp r2, r0
	bge _021DE59A
	ldr r3, [sp]
	ldr r1, [sp, #8]
	add r0, r5, #0
	add r1, r3, r1
	add r3, r7, #0
	bl MOD14_021DE5B4
_021DE59A:
	add r7, r7, #1
	add r4, r4, #4
	cmp r7, #6
	blt _021DE538
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_021DE5A8: .word 0x00000618
_021DE5AC: .word 0x00005854
_021DE5B0: .word 0x00005858

	thumb_func_start MOD14_021DE5B4
MOD14_021DE5B4: ; 0x021DE5B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r1, #0
	ldr r1, _021DE678 ; =0x00005988
	str r0, [sp, #0x1c]
	ldr r0, [r0, r1]
	str r2, [sp, #0x20]
	add r4, r3, #0
	bl MOD14_021DC44C
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x1c]
	mov r7, #0x28
	ldr r1, [r0, #0x34]
	mov r0, #0x1e
	add r2, r1, #0
	lsl r0, r0, #4
	mul r2, r0
	add r2, #0x58
	lsl r0, r4, #4
	add r0, r2, r0
	str r0, [sp, #0x28]
	mov r0, #0x34
	mul r0, r4
	add r5, r5, r0
	mov r0, #0
	str r0, [sp, #0x2c]
	ldr r1, _021DE67C ; =0x00000CD8
	ldr r0, [sp, #0x1c]
	add r1, r0, r1
	lsl r0, r7, #4
	mul r0, r4
	add r0, r1, r0
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x1c]
	lsl r1, r4, #1
	add r6, r0, r1
_021DE5FE:
	ldr r0, [r5]
	cmp r0, #0
	bne _021DE64E
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x30]
	ldr r1, [r1, #0x30]
	add r2, r4, #0
	bl FUN_0206B5E4
	mov r1, #0xab
	mov r2, #0
	str r0, [sp, #0x34]
	bl FUN_020672BC
	cmp r0, #0
	beq _021DE64E
	add r0, r4, #0
	bl MOD14_021DEB24
	ldr r1, [sp, #0x24]
	ldr r2, _021DE680 ; =0x00005814
	str r1, [sp]
	ldr r1, [sp, #0x20]
	ldr r3, _021DE684 ; =0x000057D8
	str r1, [sp, #4]
	str r7, [sp, #8]
	mov r1, #2
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0x1c]
	str r0, [sp, #0x14]
	str r5, [sp, #0x18]
	ldr r0, _021DE688 ; =0x00005980
	ldrh r2, [r6, r2]
	ldr r0, [r1, r0]
	ldrh r3, [r6, r3]
	ldr r1, [sp, #0x34]
	bl MOD14_021E0A60
_021DE64E:
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0x24]
	add r0, #0x60
	str r0, [sp, #0x28]
	mov r0, #0x4e
	lsl r0, r0, #2
	add r5, r5, r0
	mov r0, #0xf
	lsl r0, r0, #8
	add r0, r1, r0
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x2c]
	add r6, #0xc
	add r0, r0, #1
	add r4, r4, #6
	add r7, #0x18
	str r0, [sp, #0x2c]
	cmp r0, #5
	blt _021DE5FE
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DE678: .word 0x00005988
_021DE67C: .word 0x00000CD8
_021DE680: .word 0x00005814
_021DE684: .word 0x000057D8
_021DE688: .word 0x00005980

	thumb_func_start MOD14_021DE68C
MOD14_021DE68C: ; 0x021DE68C
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #0x34
	mov r4, #0
	mov r7, #0x4e
	add r5, r1, #0
	mul r0, r2
	add r5, r5, r0
	add r6, r4, #0
	lsl r7, r7, #2
_021DE69E:
	ldr r0, [r5]
	cmp r0, #0
	beq _021DE6AA
	bl FUN_0201FFC8
	str r6, [r5]
_021DE6AA:
	add r4, r4, #1
	add r5, r5, r7
	cmp r4, #5
	blt _021DE69E
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021DE6B4
MOD14_021DE6B4: ; 0x021DE6B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r1, [sp, #4]
	ldr r1, _021DE71C ; =0x00005988
	str r0, [sp]
	ldr r0, [r0, r1]
	bl MOD14_021DC44C
	ldr r4, [sp]
	str r0, [sp, #8]
	ldr r1, _021DE720 ; =0x00000CD8
	add r0, r4, #0
	mov r6, #0
	add r5, r0, r1
_021DE6D0:
	ldr r0, [sp, #8]
	ldr r1, [sp, #4]
	add r2, r6, #0
	bl FUN_0206B5E4
	mov r1, #5
	mov r2, #0
	add r7, r0, #0
	bl FUN_020672BC
	cmp r0, #0
	beq _021DE70A
	ldr r1, _021DE724 ; =0x00005814
	strh r0, [r4, r1]
	add r0, r7, #0
	bl FUN_0206B688
	ldr r1, _021DE728 ; =0x000057D8
	mov r3, #0xa
	strh r0, [r4, r1]
	ldr r2, _021DE728 ; =0x000057D8
	ldr r1, [sp]
	ldr r0, _021DE72C ; =0x00005980
	ldrh r2, [r4, r2]
	ldr r0, [r1, r0]
	add r1, r5, #0
	lsl r3, r3, #6
	bl MOD14_021E0BAC
_021DE70A:
	mov r0, #0xa
	lsl r0, r0, #6
	add r6, r6, #1
	add r4, r4, #2
	add r5, r5, r0
	cmp r6, #0x1e
	blo _021DE6D0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DE71C: .word 0x00005988
_021DE720: .word 0x00000CD8
_021DE724: .word 0x00005814
_021DE728: .word 0x000057D8
_021DE72C: .word 0x00005980

	thumb_func_start MOD14_021DE730
MOD14_021DE730: ; 0x021DE730
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r1, #0
	add r0, #0xa3
	strb r1, [r0]
	mov r0, #0xa
	mov r1, #0x10
	add r7, r2, #0
	str r3, [sp]
	bl FUN_02016998
	add r4, r0, #0
	beq _021DE782
	str r5, [r4]
	strh r6, [r4, #4]
	ldr r0, [sp]
	strh r7, [r4, #6]
	str r0, [r4, #0xc]
	mov r0, #2
	strh r0, [r4, #0xa]
	cmp r7, r6
	ble _021DE762
	mov r0, #1
	b _021DE764
_021DE762:
	sub r0, r0, #3
_021DE764:
	strh r0, [r4, #8]
	ldr r0, _021DE784 ; =MOD14_021DE788
	add r1, r4, #0
	mov r2, #0
	bl MOD14_021DDD40
	cmp r0, #0
	beq _021DE77C
	mov r0, #1
	add r5, #0xa3
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DE77C:
	add r0, r4, #0
	bl FUN_02016A18
_021DE782:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DE784: .word MOD14_021DE788

	thumb_func_start MOD14_021DE788
MOD14_021DE788: ; 0x021DE788
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	cmp r0, #0
	beq _021DE79C
	sub r0, r0, #1
	strh r0, [r4, #0xa]
	pop {r3, r4, r5, pc}
_021DE79C:
	mov r2, #4
	mov r1, #6
	ldrsh r0, [r4, r2]
	ldrsh r1, [r4, r1]
	cmp r0, r1
	beq _021DE7CA
	mov r1, #8
	ldrsh r1, [r4, r1]
	add r0, r0, r1
	strh r0, [r4, #4]
	ldr r1, [r4]
	ldr r0, _021DE7DC ; =0x00005860
	add r1, r1, r0
	ldrsh r0, [r4, r2]
	mov r2, #0x20
	lsl r0, r0, #5
	add r0, r1, r0
	ldr r1, [r4, #0xc]
	bl GX_LoadBGPltt
	mov r0, #2
	strh r0, [r4, #0xa]
	pop {r3, r4, r5, pc}
_021DE7CA:
	ldr r1, _021DE7E0 ; =MOD14_021DE7E4
	ldr r2, [r4]
	add r0, r4, #0
	bl MOD14_021DDF30
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DE7DC: .word 0x00005860
_021DE7E0: .word MOD14_021DE7E4

	thumb_func_start MOD14_021DE7E4
MOD14_021DE7E4: ; 0x021DE7E4
	mov r1, #0
	add r0, #0xa3
	strb r1, [r0]
	bx lr

	thumb_func_start MOD14_021DE7EC
MOD14_021DE7EC: ; 0x021DE7EC
	push {r3, r4, lr}
	sub sp, #4
	ldr r3, _021DE878 ; =0x021E6B90
	add r4, r1, #0
	ldr r1, [r3, #0xc]
	cmp r1, #0
	beq _021DE806
	cmp r1, #1
	beq _021DE83C
	cmp r1, #2
	beq _021DE868
	add sp, #4
	pop {r3, r4, pc}
_021DE806:
	ldr r0, _021DE87C ; =0x021E6B94
	ldr r2, _021DE880 ; =0x021E6B98
	str r0, [sp]
	ldr r3, _021DE884 ; =0x021E6B90
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021DE06C
	ldr r0, _021DE888 ; =0x00005988
	ldr r0, [r4, r0]
	bl MOD14_021DC448
	ldr r2, _021DE878 ; =0x021E6B90
	add r1, r0, #0
	ldr r0, _021DE88C ; =0x021E69E0
	ldr r2, [r2, #4]
	str r1, [r0]
	add r0, r4, #0
	mov r3, #0
	bl MOD14_021DE138
	ldr r0, _021DE878 ; =0x021E6B90
	add sp, #4
	ldr r1, [r0, #0xc]
	add r1, r1, #1
	str r1, [r0, #0xc]
	pop {r3, r4, pc}
_021DE83C:
	ldr r0, [r3, #4]
	ldr r1, _021DE88C ; =0x021E69E0
	str r0, [sp]
	ldr r2, [r3]
	ldr r1, [r1]
	ldr r3, [r3, #8]
	add r0, r4, #0
	bl MOD14_021DE278
	ldr r1, _021DE88C ; =0x021E69E0
	ldr r2, _021DE878 ; =0x021E6B90
	ldr r1, [r1]
	ldr r2, [r2, #8]
	add r0, r4, #0
	bl MOD14_021DE1D0
	ldr r0, _021DE878 ; =0x021E6B90
	add sp, #4
	ldr r1, [r0, #0xc]
	add r1, r1, #1
	str r1, [r0, #0xc]
	pop {r3, r4, pc}
_021DE868:
	mov r1, #0
	add r4, #0xa3
	strb r1, [r4]
	str r1, [r3, #0xc]
	bl FUN_0200CAB4
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021DE878: .word 0x021E6B90
_021DE87C: .word 0x021E6B94
_021DE880: .word 0x021E6B98
_021DE884: .word 0x021E6B90
_021DE888: .word 0x00005988
_021DE88C: .word 0x021E69E0

	thumb_func_start MOD14_021DE890
MOD14_021DE890: ; 0x021DE890
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021DE8C0 ; =MOD14_021DE7EC
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA98
	cmp r0, #0
	beq _021DE8A6
	mov r1, #1
	b _021DE8A8
_021DE8A6:
	mov r1, #0
_021DE8A8:
	add r0, r4, #0
	add r0, #0xa3
	add r4, #0xa3
	strb r1, [r0]
	ldrb r0, [r4]
	cmp r0, #0
	beq _021DE8BC
	ldr r0, _021DE8C4 ; =0x021E6B90
	mov r1, #0
	str r1, [r0, #0xc]
_021DE8BC:
	pop {r4, pc}
	nop
_021DE8C0: .word MOD14_021DE7EC
_021DE8C4: .word 0x021E6B90

	thumb_func_start MOD14_021DE8C8
MOD14_021DE8C8: ; 0x021DE8C8
	push {r4, lr}
	add r2, r0, #0
	mov r1, #0
	add r2, #0xa2
	strb r1, [r2]
	ldrb r3, [r0, #2]
	mov r2, #8
	lsl r4, r3, #1
	ldr r3, _021DE8E4 ; =0x021E656C
	ldrh r3, [r3, r4]
	lsl r3, r3, #5
	bl MOD14_021DE730
	pop {r4, pc}
	.align 2, 0
_021DE8E4: .word 0x021E656C

	thumb_func_start MOD14_021DE8E8
MOD14_021DE8E8: ; 0x021DE8E8
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0xa2
	ldrb r1, [r1]
	cmp r1, #4
	bhi _021DE976
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DE902: ; jump table
	.short _021DE90C - _021DE902 - 2 ; case 0
	.short _021DE922 - _021DE902 - 2 ; case 1
	.short _021DE934 - _021DE902 - 2 ; case 2
	.short _021DE94A - _021DE902 - 2 ; case 3
	.short _021DE96A - _021DE902 - 2 ; case 4
_021DE90C:
	add r0, #0xa3
	ldrb r0, [r0]
	cmp r0, #0
	bne _021DE976
	add r0, r4, #0
	add r0, #0xa2
	ldrb r0, [r0]
	add r4, #0xa2
	add r0, r0, #1
	strb r0, [r4]
	b _021DE976
_021DE922:
	bl MOD14_021DE890
	add r0, r4, #0
	add r0, #0xa2
	ldrb r0, [r0]
	add r4, #0xa2
	add r0, r0, #1
	strb r0, [r4]
	b _021DE976
_021DE934:
	add r0, #0xa3
	ldrb r0, [r0]
	cmp r0, #0
	bne _021DE976
	add r0, r4, #0
	add r0, #0xa2
	ldrb r0, [r0]
	add r4, #0xa2
	add r0, r0, #1
	strb r0, [r4]
	b _021DE976
_021DE94A:
	ldrb r3, [r4, #2]
	mov r1, #8
	mov r2, #0
	lsl r5, r3, #1
	ldr r3, _021DE97C ; =0x021E656C
	ldrh r3, [r3, r5]
	lsl r3, r3, #5
	bl MOD14_021DE730
	add r0, r4, #0
	add r0, #0xa2
	ldrb r0, [r0]
	add r4, #0xa2
	add r0, r0, #1
	strb r0, [r4]
	b _021DE976
_021DE96A:
	add r4, #0xa3
	ldrb r0, [r4]
	cmp r0, #0
	bne _021DE976
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DE976:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021DE97C: .word 0x021E656C

	thumb_func_start MOD14_021DE980
MOD14_021DE980: ; 0x021DE980
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r2, #0
	add r4, r1, #0
	mov r0, #0x34
	mul r4, r0
	add r0, r5, #0
	ldrb r2, [r5, #2]
	ldr r1, _021DE9CC ; =0x00000618
	add r0, #0xa8
	mul r1, r2
	add r0, r0, r1
	add r6, r3, #0
	add r0, r0, r4
	add r1, r6, #0
	mov r2, #1
	bl MOD14_021E0930
	ldr r0, _021DE9D0 ; =0x00005980
	add r1, r6, #0
	ldr r0, [r5, r0]
	add r2, r7, #0
	bl MOD14_021E0BBC
	ldr r0, _021DE9D0 ; =0x00005980
	add r3, r5, #0
	ldrb r2, [r5, #2]
	ldr r1, _021DE9CC ; =0x00000618
	add r3, #0xa8
	mul r1, r2
	add r1, r3, r1
	ldr r0, [r5, r0]
	add r1, r1, r4
	mov r2, #1
	bl MOD14_021E08E4
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DE9CC: .word 0x00000618
_021DE9D0: .word 0x00005980

	thumb_func_start MOD14_021DE9D4
MOD14_021DE9D4: ; 0x021DE9D4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldrb r0, [r6, #2]
	add r7, r1, #0
	add r3, r6, #0
	str r0, [sp]
	ldr r1, _021DEA30 ; =0x00000618
	ldr r0, [sp]
	add r3, #0xa8
	mul r1, r0
	mov r0, #0x34
	add r4, r7, #0
	mul r4, r0
	add r5, r3, r1
	add r0, r2, #0
	add r1, r5, r4
	mov r2, #1
	bl MOD14_021E0930
	ldr r0, _021DEA34 ; =0x00005980
	add r1, r5, r4
	ldr r0, [r6, r0]
	mov r2, #0
	bl MOD14_021E0C5C
	mov r2, #0x1e
	ldr r0, _021DEA34 ; =0x00005980
	ldr r3, [sp]
	lsl r2, r2, #4
	mul r2, r3
	ldr r0, [r6, r0]
	add r2, #0x58
	lsl r3, r7, #4
	add r1, r5, r4
	add r2, r2, r3
	bl MOD14_021E0BBC
	add r0, r7, #0
	bl MOD14_021DEB24
	add r1, r0, #0
	ldr r0, [r5, r4]
	bl MOD14_021DDE24
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DEA30: .word 0x00000618
_021DEA34: .word 0x00005980

	thumb_func_start MOD14_021DEA38
MOD14_021DEA38: ; 0x021DEA38
	ldrb r2, [r0, #2]
	add r3, r0, #0
	ldr r0, _021DEA4C ; =0x00000618
	add r3, #0xa8
	mul r0, r2
	add r2, r3, r0
	mov r0, #0x34
	mul r0, r1
	add r0, r2, r0
	bx lr
	.align 2, 0
_021DEA4C: .word 0x00000618

	thumb_func_start MOD14_021DEA50
MOD14_021DEA50: ; 0x021DEA50
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r5, r0, #0
	ldr r0, _021DEB14 ; =0x00005988
	ldr r0, [r5, r0]
	ldr r0, [r0]
	bl FUN_0206B330
	mov r4, #0
	str r0, [sp, #0x1c]
	add r0, r5, #0
	str r0, [sp, #0x28]
	add r0, #0xa8
	add r7, r4, #0
	str r4, [sp, #0x2c]
	str r0, [sp, #0x28]
_021DEA70:
	ldr r0, _021DEB14 ; =0x00005988
	ldr r1, [sp, #0x1c]
	ldr r0, [r5, r0]
	add r2, r4, #0
	ldr r0, [r0]
	bl FUN_0206B5E4
	mov r1, #0xab
	mov r2, #0
	str r0, [sp, #0x20]
	bl FUN_020672BC
	cmp r0, #0
	beq _021DEB02
	ldrb r1, [r5, #2]
	ldr r0, _021DEB18 ; =0x00000618
	mul r0, r1
	str r0, [sp, #0x18]
	add r0, r5, r0
	add r0, r7, r0
	str r1, [sp, #0x14]
	add r0, #0xa8
	ldr r0, [r0]
	cmp r0, #0
	bne _021DEB02
	add r0, r4, #0
	bl MOD14_021DEB24
	str r0, [sp, #0x24]
	add r0, r4, #0
	mov r1, #6
	bl _s32_div_f
	str r1, [sp, #0x10]
	add r0, r4, #0
	mov r1, #6
	bl _s32_div_f
	mov ip, r0
	mov r0, #2
	str r0, [sp]
	ldr r0, [sp, #0x24]
	ldr r3, [sp, #0x10]
	str r0, [sp, #4]
	ldr r1, [sp, #0x14]
	mov r0, #0x1e
	add r2, r1, #0
	lsl r0, r0, #4
	mul r2, r0
	ldr r0, [sp, #0x2c]
	add r2, #0x58
	add r0, r2, r0
	str r0, [sp, #8]
	ldr r1, [sp, #0x28]
	ldr r0, [sp, #0x18]
	ldr r2, _021DEB1C ; =0x0000585C
	add r0, r1, r0
	add r0, r0, r7
	str r0, [sp, #0xc]
	ldr r6, [r5, r2]
	mov r2, #0x18
	ldr r0, _021DEB20 ; =0x00005980
	mul r2, r3
	add r6, #0x70
	add r2, r6, r2
	mov r6, ip
	mov r3, #0x18
	mul r3, r6
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x20]
	add r3, #0x28
	bl MOD14_021E0940
_021DEB02:
	ldr r0, [sp, #0x2c]
	add r4, r4, #1
	add r0, #0x10
	add r7, #0x34
	str r0, [sp, #0x2c]
	cmp r4, #0x1e
	blt _021DEA70
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DEB14: .word 0x00005988
_021DEB18: .word 0x00000618
_021DEB1C: .word 0x0000585C
_021DEB20: .word 0x00005980

	thumb_func_start MOD14_021DEB24
MOD14_021DEB24: ; 0x021DEB24
	lsl r1, r0, #1
	ldr r0, _021DEB30 ; =0x021E6570
	ldrh r0, [r0, r1]
	add r0, #0xb
	bx lr
	nop
_021DEB30: .word 0x021E6570

	thumb_func_start MOD14_021DEB34
MOD14_021DEB34: ; 0x021DEB34
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	str r0, [sp, #0x10]
	mov r0, #0x1e
	lsl r0, r0, #4
	add r6, r3, #0
	mul r6, r0
	mov r0, #0x28
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x48]
	mov r4, #0
	ldr r7, [sp, #0x4c]
	str r1, [sp, #0x14]
	str r2, [sp, #0x18]
	add r6, #0x58
	str r4, [sp, #0x24]
	str r0, [sp, #0x20]
_021DEB56:
	mov r0, #0
	str r0, [sp, #0x28]
	add r5, r0, #0
_021DEB5C:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	ldr r0, [r0, #0x40]
	add r2, r4, #0
	ldr r0, [r0]
	bl FUN_0206B5E4
	mov r1, #5
	mov r2, #0
	str r0, [sp, #0x2c]
	bl FUN_020672BC
	cmp r0, #0
	beq _021DEBA0
	add r0, r4, #0
	bl MOD14_021DEB24
	mov r1, #2
	str r1, [sp]
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldr r3, [sp, #0x10]
	ldr r2, _021DEBC8 ; =0x0000585C
	str r7, [sp, #0xc]
	ldr r2, [r3, r2]
	ldr r0, [sp, #0x14]
	add r2, #0x70
	add r3, r2, r5
	ldr r2, [sp, #0x20]
	ldr r1, [sp, #0x2c]
	add r2, r2, r3
	ldr r3, [sp, #0x1c]
	bl MOD14_021E0940
_021DEBA0:
	ldr r0, [sp, #0x28]
	add r7, #0x34
	add r0, r0, #1
	add r4, r4, #1
	add r6, #0x10
	add r5, #0x18
	str r0, [sp, #0x28]
	cmp r0, #6
	blo _021DEB5C
	ldr r0, [sp, #0x1c]
	add r0, #0x18
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x24]
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, #5
	blo _021DEB56
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DEBC8: .word 0x0000585C

	thumb_func_start MOD14_021DEBCC
MOD14_021DEBCC: ; 0x021DEBCC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0x18
	mul r0, r2
	add r5, r1, #0
	str r0, [sp, #8]
_021DEBDE:
	ldr r1, [sp]
	ldr r0, [sp, #8]
	mov r7, #0
	add r4, r1, r0
_021DEBE6:
	ldr r0, [r5]
	cmp r0, #0
	beq _021DEC0A
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0xc
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x68]
	str r0, [sp, #0xc]
	ldr r0, [r5]
	bl FUN_02020044
_021DEC0A:
	add r7, r7, #1
	add r5, #0x34
	add r4, r4, #4
	cmp r7, #6
	blt _021DEBE6
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #5
	blt _021DEBDE
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021DEC24
MOD14_021DEC24: ; 0x021DEC24
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0x18
	mul r0, r2
	add r5, r1, #0
	str r0, [sp, #8]
_021DEC36:
	ldr r1, [sp]
	ldr r0, [sp, #8]
	mov r7, #0
	add r4, r1, r0
_021DEC3E:
	ldr r0, [r5]
	cmp r0, #0
	beq _021DEC62
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0xc
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x38]
	str r0, [sp, #0xc]
	ldr r0, [r5]
	bl FUN_02020044
_021DEC62:
	add r7, r7, #1
	add r5, #0x34
	add r4, r4, #4
	cmp r7, #6
	blt _021DEC3E
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #5
	blt _021DEC36
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021DEC7C
MOD14_021DEC7C: ; 0x021DEC7C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #0x10]
	mov r0, #0x28
	add r5, r1, #0
	str r0, [sp]
_021DEC8E:
	ldr r0, [sp]
	mov r6, #0
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	add r4, r6, #0
_021DEC98:
	ldr r0, _021DECD0 ; =0x0000585C
	ldr r0, [r7, r0]
	add r0, #0x70
	add r0, r0, r4
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r0, [r5]
	cmp r0, #0
	beq _021DECB0
	add r1, sp, #8
	bl FUN_02020044
_021DECB0:
	add r6, r6, #1
	add r5, #0x34
	add r4, #0x18
	cmp r6, #6
	blt _021DEC98
	ldr r0, [sp]
	add r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #5
	blt _021DEC8E
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021DECD0: .word 0x0000585C

	thumb_func_start MOD14_021DECD4
MOD14_021DECD4: ; 0x021DECD4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp]
	add r0, r2, #0
	add r7, r3, #0
	str r1, [sp, #4]
	str r2, [sp, #8]
	cmp r0, #0x20
	blo _021DECF0
	mov r1, #2
	ldr r0, [sp]
	lsl r1, r1, #0xa
	add r0, r0, r1
	str r0, [sp]
_021DECF0:
	mov r0, #0
	mov ip, r0
	ldr r0, [sp, #0x28]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	orr r0, r7
	mov lr, r0
_021DECFE:
	ldr r0, [sp, #8]
	mov r2, #0
	lsl r0, r0, #0x1b
	lsr r1, r0, #0x1a
	ldr r0, [sp]
	add r4, r2, #0
	add r3, r0, r1
	mov r0, ip
	lsl r1, r0, #1
	ldr r0, [sp, #4]
	add r6, r0, r1
_021DED14:
	lsl r0, r4, #1
	ldrh r1, [r6, r0]
	mov r0, #3
	lsl r0, r0, #0xa
	add r5, r1, #0
	and r5, r0
	ldr r0, _021DEDCC ; =0x000003FF
	add r2, r2, #1
	and r0, r1
	add r0, r0, r7
	add r1, r5, #0
	orr r1, r0
	ldr r0, [sp, #0xc]
	add r4, #0x15
	orr r0, r1
	strh r0, [r3]
	add r3, #0x40
	cmp r2, #0x14
	blo _021DED14
	mov r1, lr
	lsl r1, r1, #0x10
	mov r0, #0
	lsr r1, r1, #0x10
_021DED42:
	add r0, r0, #1
	strh r1, [r3]
	add r3, #0x40
	cmp r0, #4
	blo _021DED42
	ldr r0, [sp, #8]
	add r1, r0, #1
	mov r0, #0x3f
	and r0, r1
	str r0, [sp, #8]
	bne _021DED62
	mov r1, #2
	ldr r0, [sp]
	lsl r1, r1, #0xa
	sub r0, r0, r1
	str r0, [sp]
_021DED62:
	ldr r0, [sp, #8]
	cmp r0, #0x20
	bne _021DED72
	mov r1, #2
	ldr r0, [sp]
	lsl r1, r1, #0xa
	add r0, r0, r1
	str r0, [sp]
_021DED72:
	mov r0, ip
	add r0, r0, #1
	mov ip, r0
	cmp r0, #0x15
	blo _021DECFE
	mov r1, lr
	mov r3, #2
	mov r0, #0
	lsl r1, r1, #0x10
	lsl r3, r3, #0xa
	lsr r5, r1, #0x10
	add r7, r0, #0
	mov r4, #0x3f
	add r2, r3, #0
_021DED8E:
	ldr r1, [sp, #8]
	lsl r1, r1, #0x1b
	lsr r6, r1, #0x1a
	ldr r1, [sp]
	add r1, r1, r6
	add r6, r7, #0
_021DED9A:
	add r6, r6, #1
	strh r5, [r1]
	add r1, #0x40
	cmp r6, #0x18
	blo _021DED9A
	ldr r1, [sp, #8]
	add r1, r1, #1
	and r1, r4
	str r1, [sp, #8]
	bne _021DEDB4
	ldr r1, [sp]
	sub r1, r1, r3
	str r1, [sp]
_021DEDB4:
	ldr r1, [sp, #8]
	cmp r1, #0x20
	bne _021DEDC0
	ldr r1, [sp]
	add r1, r1, r2
	str r1, [sp]
_021DEDC0:
	add r0, r0, #1
	cmp r0, #2
	blo _021DED8E
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DEDCC: .word 0x000003FF

	thumb_func_start MOD14_021DEDD0
MOD14_021DEDD0: ; 0x021DEDD0
	push {r4, lr}
	add r2, r0, #0
	add r0, #0xa0
	strh r1, [r0]
	add r0, r2, #0
	mov r3, #0
	add r0, #0xa4
	strb r3, [r0]
	ldr r0, _021DEE00 ; =0x00005980
	add r4, r2, #0
	ldrb r3, [r2, #2]
	ldr r0, [r2, r0]
	ldr r2, _021DEE04 ; =0x00000618
	add r4, #0xa8
	mul r2, r3
	add r3, r4, r2
	mov r2, #0x34
	mul r2, r1
	add r1, r3, r2
	mov r2, #1
	bl MOD14_021E0C20
	pop {r4, pc}
	nop
_021DEE00: .word 0x00005980
_021DEE04: .word 0x00000618

	thumb_func_start MOD14_021DEE08
MOD14_021DEE08: ; 0x021DEE08
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldrb r1, [r5, #2]
	ldr r0, _021DEE9C ; =0x00000618
	add r2, r5, #0
	add r2, #0xa8
	mul r0, r1
	add r4, r2, r0
	add r0, r5, #0
	add r0, #0xa0
	ldrh r1, [r0]
	mov r0, #0x34
	add r6, r1, #0
	mul r6, r0
	add r0, r5, #0
	add r0, #0xa4
	ldrb r0, [r0]
	cmp r0, #0
	beq _021DEE34
	cmp r0, #1
	beq _021DEE86
	b _021DEE98
_021DEE34:
	ldr r0, _021DEEA0 ; =0x00005980
	add r1, r4, r6
	ldr r0, [r5, r0]
	bl MOD14_021E0C48
	cmp r0, #0
	beq _021DEE98
	ldr r0, _021DEEA4 ; =0x0000598C
	ldr r0, [r5, r0]
	bl MOD14_021DDEDC
	add r7, r0, #0
	bl MOD14_021DA1B8
	cmp r0, #0
	beq _021DEE98
	add r0, r7, #0
	bl MOD14_021DA1C0
	cmp r0, #0
	ldr r0, _021DEEA0 ; =0x00005980
	beq _021DEE6E
	ldr r0, [r5, r0]
	add r1, r4, r6
	mov r2, #1
	bl MOD14_021E0908
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DEE6E:
	ldr r0, [r5, r0]
	add r1, r4, r6
	mov r2, #2
	bl MOD14_021E0C20
	add r0, r5, #0
	add r0, #0xa4
	ldrb r0, [r0]
	add r5, #0xa4
	add r0, r0, #1
	strb r0, [r5]
	b _021DEE98
_021DEE86:
	ldr r0, _021DEEA0 ; =0x00005980
	add r1, r4, r6
	ldr r0, [r5, r0]
	bl MOD14_021E0C48
	cmp r0, #0
	beq _021DEE98
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DEE98:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DEE9C: .word 0x00000618
_021DEEA0: .word 0x00005980
_021DEEA4: .word 0x0000598C

	thumb_func_start MOD14_021DEEA8
MOD14_021DEEA8: ; 0x021DEEA8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _021DEEEC ; =0x00005988
	ldr r0, [r5, r0]
	bl MOD14_021DC484
	mov r6, #0
	add r7, r5, #0
	str r0, [sp]
	add r4, r6, #0
	add r7, #0xa8
_021DEEBE:
	ldrb r2, [r5, #2]
	ldr r0, _021DEEF0 ; =0x00000618
	add r1, r2, #0
	mul r1, r0
	add r0, r5, r1
	add r0, r4, r0
	add r0, #0xa8
	ldr r0, [r0]
	cmp r0, #0
	beq _021DEEE0
	ldr r0, _021DEEF4 ; =0x00005980
	add r1, r7, r1
	ldr r0, [r5, r0]
	ldr r2, [sp]
	add r1, r1, r4
	bl MOD14_021E0B54
_021DEEE0:
	add r6, r6, #1
	add r4, #0x34
	cmp r6, #0x1e
	blt _021DEEBE
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DEEEC: .word 0x00005988
_021DEEF0: .word 0x00000618
_021DEEF4: .word 0x00005980

	thumb_func_start MOD14_021DEEF8
MOD14_021DEEF8: ; 0x021DEEF8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0x34
	mul r4, r0
	add r3, r5, #0
	ldrb r1, [r5, #2]
	ldr r0, _021DEF40 ; =0x00000618
	add r3, #0xa8
	mul r0, r1
	add r1, r3, r0
	ldr r0, [r1, r4]
	cmp r0, #0
	beq _021DEF3E
	ldr r0, _021DEF44 ; =0x00005980
	add r1, r1, r4
	ldr r0, [r5, r0]
	bl MOD14_021E0BA8
	ldr r0, _021DEF48 ; =0x00005988
	ldr r0, [r5, r0]
	bl MOD14_021DC484
	add r2, r0, #0
	ldr r0, _021DEF44 ; =0x00005980
	add r1, r5, #0
	ldr r0, [r5, r0]
	ldrb r5, [r5, #2]
	ldr r3, _021DEF40 ; =0x00000618
	add r1, #0xa8
	mul r3, r5
	add r1, r1, r3
	add r1, r1, r4
	bl MOD14_021E0B54
_021DEF3E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DEF40: .word 0x00000618
_021DEF44: .word 0x00005980
_021DEF48: .word 0x00005988

	thumb_func_start MOD14_021DEF4C
MOD14_021DEF4C: ; 0x021DEF4C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021DEF88 ; =0x00005988
	ldr r0, [r5, r0]
	bl MOD14_021DC3E0
	add r4, r0, #0
	ldr r0, _021DEF88 ; =0x00005988
	ldr r0, [r5, r0]
	bl MOD14_021DC45C
	add r2, r0, #0
	add r3, r5, #0
	ldrb r1, [r5, #2]
	ldr r0, _021DEF8C ; =0x00000618
	add r3, #0xa8
	mul r0, r1
	add r3, r3, r0
	mov r0, #0x34
	add r1, r4, #0
	mul r1, r0
	ldr r0, [r3, r1]
	cmp r0, #0
	beq _021DEF86
	ldr r0, _021DEF90 ; =0x00005980
	add r1, r3, r1
	ldr r0, [r5, r0]
	bl MOD14_021E0BA4
_021DEF86:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DEF88: .word 0x00005988
_021DEF8C: .word 0x00000618
_021DEF90: .word 0x00005980

	thumb_func_start MOD14_021DEF94
MOD14_021DEF94: ; 0x021DEF94
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r0, #0
	add r0, sp, #0xc
	str r0, [sp]
	ldr r0, _021DF030 ; =0x00005988
	add r1, sp, #0x18
	ldr r0, [r4, r0]
	add r2, sp, #0x14
	add r3, sp, #0x10
	bl MOD14_021DC4A4
	mov r5, #0
	str r5, [sp, #4]
_021DEFB0:
	add r0, r4, #0
	str r0, [sp, #8]
	add r0, #0xa8
	mov r7, #0
	str r0, [sp, #8]
_021DEFBA:
	ldrb r2, [r4, #2]
	ldr r0, _021DF034 ; =0x00000618
	add r1, r2, #0
	mul r1, r0
	add r0, r4, r1
	add r0, r5, r0
	add r0, #0xa8
	ldr r0, [r0]
	cmp r0, #0
	beq _021DF018
	ldr r6, [sp, #0x18]
	ldr r2, [sp, #0x14]
	sub r3, r7, r6
	sub r2, r2, r6
	ldr r0, [sp, #0x10]
	cmp r3, r2
	bhi _021DEFE0
	mov r6, #1
	b _021DEFE2
_021DEFE0:
	mov r6, #0
_021DEFE2:
	ldr r2, [sp, #4]
	sub r3, r2, r0
	ldr r2, [sp, #0xc]
	sub r0, r2, r0
	cmp r3, r0
	bhi _021DEFF2
	mov r0, #1
	b _021DEFF4
_021DEFF2:
	mov r0, #0
_021DEFF4:
	tst r0, r6
	ldr r0, _021DF038 ; =0x00005980
	beq _021DF00A
	ldr r2, [sp, #8]
	ldr r0, [r4, r0]
	add r1, r2, r1
	add r1, r1, r5
	mov r2, #1
	bl MOD14_021E0C5C
	b _021DF018
_021DF00A:
	ldr r2, [sp, #8]
	ldr r0, [r4, r0]
	add r1, r2, r1
	add r1, r1, r5
	mov r2, #0
	bl MOD14_021E0C5C
_021DF018:
	add r7, r7, #1
	add r5, #0x34
	cmp r7, #6
	blo _021DEFBA
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #5
	blo _021DEFB0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021DF030: .word 0x00005988
_021DF034: .word 0x00000618
_021DF038: .word 0x00005980

	thumb_func_start MOD14_021DF03C
MOD14_021DF03C: ; 0x021DF03C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r6, #0
	add r7, r5, #0
	add r4, r6, #0
	add r7, #0xa8
_021DF048:
	ldrb r2, [r5, #2]
	ldr r0, _021DF074 ; =0x00000618
	add r1, r2, #0
	mul r1, r0
	add r0, r5, r1
	add r0, r4, r0
	add r0, #0xa8
	ldr r0, [r0]
	cmp r0, #0
	beq _021DF06A
	ldr r0, _021DF078 ; =0x00005980
	add r1, r7, r1
	ldr r0, [r5, r0]
	add r1, r1, r4
	mov r2, #0
	bl MOD14_021E0C5C
_021DF06A:
	add r6, r6, #1
	add r4, #0x34
	cmp r6, #0x1e
	blt _021DF048
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DF074: .word 0x00000618
_021DF078: .word 0x00005980

	thumb_func_start MOD14_021DF07C
MOD14_021DF07C: ; 0x021DF07C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r0, _021DF128 ; =0x00000794
	add r6, r1, #0
	str r6, [r5, r0]
	add r4, r2, #0
	sub r0, r0, #4
	str r4, [r5, r0]
	add r0, r6, #0
	str r3, [r5]
	bl MOD14_021DDD58
	ldr r1, _021DF12C ; =0x00000758
	str r0, [r5, r1]
	add r0, r6, #0
	bl MOD14_021DDD60
	ldr r1, _021DF130 ; =0x0000075C
	str r0, [r5, r1]
	add r0, r6, #0
	bl MOD14_021DDD50
	str r0, [r5, #0x48]
	add r0, r4, #0
	bl MOD14_021DC3CC
	ldr r1, _021DF134 ; =0x00000785
	strb r0, [r5, r1]
	add r0, r4, #0
	bl MOD14_021DC3D0
	ldr r1, _021DF138 ; =0x00000789
	strb r0, [r5, r1]
	add r0, r4, #0
	bl MOD14_021DC3D8
	ldr r1, _021DF13C ; =0x0000078A
	strb r0, [r5, r1]
	add r0, r4, #0
	bl MOD14_021DC3E8
	ldr r1, _021DF140 ; =0x0000078B
	add r3, r5, #0
	strb r0, [r5, r1]
	mov r2, #0
	str r2, [r5, #4]
	str r2, [r5, #8]
	str r2, [r5, #0xc]
	add r0, r1, #0
	str r2, [r5, #0x10]
	sub r0, #0x37
	str r2, [r5, r0]
	add r0, r1, #3
	mov r2, #1
	strb r2, [r5, r0]
	mov r0, #0xa
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0xd
	add r3, #0x1c
	bl FUN_02006C30
	str r0, [r5, #0x14]
	mov r0, #0xa
	add r3, r5, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0xe
	mov r2, #1
	add r3, #0x20
	bl FUN_02006C5C
	str r0, [r5, #0x18]
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _021DF11C
	ldr r0, [r5, #0x18]
	cmp r0, #0
	bne _021DF122
_021DF11C:
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021DF122:
	mov r0, #1
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DF128: .word 0x00000794
_021DF12C: .word 0x00000758
_021DF130: .word 0x0000075C
_021DF134: .word 0x00000785
_021DF138: .word 0x00000789
_021DF13C: .word 0x0000078A
_021DF140: .word 0x0000078B

	thumb_func_start MOD14_021DF144
MOD14_021DF144: ; 0x021DF144
	push {r4, r5, r6, lr}
	sub sp, #0x38
	add r4, r0, #0
	add r0, #0x24
	bl FUN_020B1A24
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x24
	str r0, [sp, #0x10]
	mov r0, #0x12
	mov r1, #0xc
	bl FUN_02006AE4
	ldr r0, _021DF310 ; =0x00000785
	ldrb r0, [r4, r0]
	cmp r0, #1
	bne _021DF178
	mov r5, #1
	b _021DF17A
_021DF178:
	mov r5, #2
_021DF17A:
	ldr r0, _021DF314 ; =0x00000794
	ldr r0, [r4, r0]
	bl MOD14_021DDD48
	add r2, r0, #0
	ldr r0, [r4, #0x20]
	add r1, r4, #0
	str r0, [sp]
	str r5, [sp, #4]
	ldr r3, [r4, #0x1c]
	add r0, sp, #0x14
	add r1, #0x24
	bl MOD14_021DDDB4
	ldr r2, _021DF318 ; =0x00000764
	add r3, r4, #0
	add r1, r2, #4
	add r0, r4, r2
	add r2, #0x21
	add r1, r4, r1
	add r2, r4, r2
	bl MOD14_021E0264
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r3, _021DF318 ; =0x00000764
	ldr r0, [r4]
	ldr r2, [r4, r3]
	add r3, r3, #4
	ldr r3, [r4, r3]
	add r1, sp, #0x14
	bl MOD14_021DDDD4
	str r0, [r4, #4]
	mov r0, #0x2a
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r3, _021DF318 ; =0x00000764
	ldr r0, [r4]
	ldr r2, [r4, r3]
	add r3, r3, #4
	ldr r3, [r4, r3]
	add r1, sp, #0x14
	add r3, #0x18
	bl MOD14_021DDDD4
	str r0, [r4, #8]
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC3CC
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC3C4
	add r6, r0, #0
	cmp r6, #4
	beq _021DF1FC
	mov r2, #0x6c
	mov r5, #0xec
	b _021DF200
_021DF1FC:
	mov r2, #0x40
	mov r5, #0xc0
_021DF200:
	mov r1, #2
	add r0, sp, #0x34
	strb r1, [r0]
	mov r0, #0x2b
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0x14
	mov r3, #0x14
	bl MOD14_021DDDD4
	str r0, [r4, #0xc]
	mov r0, #0x2b
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0x14
	add r2, r5, #0
	mov r3, #0x14
	bl MOD14_021DDDD4
	str r0, [r4, #0x10]
	ldr r0, [r4, #8]
	mov r1, #5
	bl FUN_02020130
	ldr r0, [r4, #8]
	mov r1, #2
	bl FUN_02020238
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC3CC
	add r5, r0, #0
	cmp r5, #2
	ldr r0, [r4, #0xc]
	beq _021DF262
	mov r1, #6
	bl FUN_02020130
	ldr r0, [r4, #0x10]
	mov r1, #7
	bl FUN_02020130
	b _021DF270
_021DF262:
	mov r1, #8
	bl FUN_02020130
	ldr r0, [r4, #0x10]
	mov r1, #9
	bl FUN_02020130
_021DF270:
	cmp r5, #0
	beq _021DF27C
	ldr r0, [r4, #8]
	mov r1, #0
	bl FUN_020200A0
_021DF27C:
	cmp r6, #3
	beq _021DF2C0
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC3F4
	cmp r0, #1
	ldr r0, [r4, #4]
	bne _021DF2A6
	mov r1, #0
	bl FUN_02020130
	add r1, r4, #0
	ldr r0, [r4, #0x48]
	add r1, #0x4c
	mov r2, #0x1e
	bl MOD14_021E08E4
	mov r1, #0
	b _021DF2B4
_021DF2A6:
	mov r1, #2
	bl FUN_02020130
	add r0, r4, #0
	bl MOD14_021DF324
	mov r1, #1
_021DF2B4:
	ldr r0, _021DF31C ; =0x0000078C
	strb r1, [r4, r0]
	ldr r0, _021DF320 ; =0x0000078D
	mov r1, #0
	strb r1, [r4, r0]
	b _021DF2F8
_021DF2C0:
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC538
	cmp r0, #0
	ldr r0, [r4, #4]
	bne _021DF2DA
	mov r1, #0
	bl FUN_02020130
	mov r1, #0
	b _021DF2E2
_021DF2DA:
	mov r1, #2
	bl FUN_02020130
	mov r1, #1
_021DF2E2:
	ldr r0, _021DF320 ; =0x0000078D
	mov r2, #0x1e
	strb r1, [r4, r0]
	add r1, r4, #0
	ldr r0, [r4, #0x48]
	add r1, #0x4c
	bl MOD14_021E08E4
	ldr r0, _021DF31C ; =0x0000078C
	mov r1, #0
	strb r1, [r4, r0]
_021DF2F8:
	ldr r0, _021DF314 ; =0x00000794
	ldr r0, [r4, r0]
	bl MOD14_021DDD78
	mov r1, #0x76
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD14_021E0008
	add sp, #0x38
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DF310: .word 0x00000785
_021DF314: .word 0x00000794
_021DF318: .word 0x00000764
_021DF31C: .word 0x0000078C
_021DF320: .word 0x0000078D

	thumb_func_start MOD14_021DF324
MOD14_021DF324: ; 0x021DF324
	push {r4, r5, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, [r5, #4]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x10
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r5, #0
	str r0, [r2]
	ldr r0, [r5, #0x48]
	add r1, #0x4c
	mov r2, #1
	bl MOD14_021E08E4
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD14_021DC458
	add r4, r0, #0
	ldr r0, [r5, #4]
	bl FUN_02020240
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _021DF398 ; =0x000004D8
	add r1, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0x4c
	str r0, [sp, #0xc]
	ldr r3, [sp, #0x14]
	ldr r2, [sp, #0x10]
	asr r3, r3, #0xc
	ldr r0, [r5, #0x48]
	asr r2, r2, #0xc
	add r3, r3, #4
	bl MOD14_021E0940
	ldr r1, _021DF39C ; =0x00000664
	mov r0, #0
	str r0, [r5, r1]
	add r0, r1, #4
	ldr r2, _021DF3A0 ; =0xFFFFC000
	add r1, #0xf0
	str r2, [r5, r0]
	mov r2, #1
	ldr r0, _021DF3A4 ; =0x0000078C
	str r2, [r5, r1]
	strb r2, [r5, r0]
	add sp, #0x1c
	pop {r4, r5, pc}
	nop
_021DF398: .word 0x000004D8
_021DF39C: .word 0x00000664
_021DF3A0: .word 0xFFFFC000
_021DF3A4: .word 0x0000078C

	thumb_func_start MOD14_021DF3A8
MOD14_021DF3A8: ; 0x021DF3A8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021DF3BA
	bl FUN_02016A18
	mov r0, #0
	str r0, [r4, #0x14]
_021DF3BA:
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _021DF3C8
	bl FUN_02016A18
	mov r0, #0
	str r0, [r4, #0x18]
_021DF3C8:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021DF3D6
	bl FUN_0201FFC8
	mov r0, #0
	str r0, [r4, #4]
_021DF3D6:
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021DF3E4
	bl FUN_0201FFC8
	mov r0, #0
	str r0, [r4, #8]
_021DF3E4:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DF3F2
	bl FUN_0201FFC8
	mov r0, #0
	str r0, [r4, #0xc]
_021DF3F2:
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021DF400
	bl FUN_0201FFC8
	mov r0, #0
	str r0, [r4, #0x10]
_021DF400:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DF404
MOD14_021DF404: ; 0x021DF404
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r0, #0
	add r5, r1, #0
	str r0, [r2]
	str r0, [r5]
	ldr r0, _021DF47C ; =0x00000785
	ldrb r1, [r4, r0]
	cmp r1, #4
	bhi _021DF478
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DF424: ; jump table
	.short _021DF42E - _021DF424 - 2 ; case 0
	.short _021DF478 - _021DF424 - 2 ; case 1
	.short _021DF458 - _021DF424 - 2 ; case 2
	.short _021DF46C - _021DF424 - 2 ; case 3
	.short _021DF46C - _021DF424 - 2 ; case 4
_021DF42E:
	add r1, r0, #1
	ldrb r1, [r4, r1]
	cmp r1, #0
	bne _021DF478
	add r0, #0xb
	ldr r0, [r4, r0]
	bl MOD14_021DC3D0
	ldr r1, _021DF480 ; =0x00000789
	ldrsb r1, [r4, r1]
	cmp r1, #0
	bne _021DF44A
	cmp r0, #5
	beq _021DF452
_021DF44A:
	cmp r1, #5
	bne _021DF478
	cmp r0, #0
	bne _021DF478
_021DF452:
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DF458:
	add r0, r0, #1
	ldrb r0, [r4, r0]
	add r0, #0xfd
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bhi _021DF478
	mov r0, #1
	str r0, [r2]
	pop {r3, r4, r5, pc}
_021DF46C:
	add r0, r0, #1
	ldrb r0, [r4, r0]
	cmp r0, #2
	bne _021DF478
	mov r0, #1
	str r0, [r2]
_021DF478:
	pop {r3, r4, r5, pc}
	nop
_021DF47C: .word 0x00000785
_021DF480: .word 0x00000789

	thumb_func_start MOD14_021DF484
MOD14_021DF484: ; 0x021DF484
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r2, _021DF584 ; =0x0000076C
	add r5, r0, #0
	add r1, r2, #4
	add r0, r5, r2
	add r2, #0x1a
	add r1, r5, r1
	add r2, r5, r2
	add r3, r5, #0
	bl MOD14_021E0264
	add r0, r5, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD14_021DF404
	ldr r0, _021DF588 ; =0x00000786
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _021DF4B6
	ldr r0, [r5, #8]
	mov r1, #0
	bl FUN_020200A0
_021DF4B6:
	ldr r1, _021DF58C ; =0x00000764
	ldr r0, [r5, r1]
	lsl r2, r0, #0xc
	add r0, r1, #0
	add r0, #0x10
	str r2, [r5, r0]
	add r0, r1, #4
	ldr r0, [r5, r0]
	lsl r2, r0, #0xc
	add r0, r1, #0
	add r0, #0x14
	str r2, [r5, r0]
	add r0, r1, #0
	add r0, #8
	ldr r6, [r5, r0]
	add r0, r1, #0
	add r0, #0xc
	ldr r2, [r5, r0]
	ldr r7, [sp, #4]
	lsl r4, r6, #0xc
	lsl r0, r2, #0xc
	cmp r7, #0
	bne _021DF4EC
	add r1, #0x10
	ldr r1, [r5, r1]
	sub r1, r4, r1
	b _021DF514
_021DF4EC:
	add r3, r1, #0
	add r3, #0x10
	ldr r3, [r5, r3]
	cmp r4, r3
	ble _021DF506
	mov r3, #0x11
	ldr r1, [r5, r1]
	lsl r3, r3, #4
	sub r3, r3, r6
	sub r1, #0x46
	add r1, r3, r1
	neg r1, r1
	b _021DF512
_021DF506:
	ldr r3, [r5, r1]
	mov r1, #0x11
	lsl r1, r1, #4
	sub r1, r1, r3
	sub r6, #0x46
	add r1, r1, r6
_021DF512:
	lsl r1, r1, #0xc
_021DF514:
	ldr r3, [sp]
	cmp r3, #0
	bne _021DF522
	ldr r2, _021DF590 ; =0x00000778
	ldr r2, [r5, r2]
	sub r4, r0, r2
	b _021DF548
_021DF522:
	ldr r4, _021DF590 ; =0x00000778
	ldr r6, [r5, r4]
	cmp r0, r6
	ble _021DF53A
	mov r0, #0xd0
	sub r4, #0x10
	sub r2, r0, r2
	ldr r0, [r5, r4]
	add r0, #0x18
	add r0, r2, r0
	neg r4, r0
	b _021DF546
_021DF53A:
	sub r4, #0x10
	ldr r4, [r5, r4]
	mov r0, #0xd0
	sub r0, r0, r4
	add r2, #0x18
	add r4, r0, r2
_021DF546:
	lsl r4, r4, #0xc
_021DF548:
	cmp r7, #0
	bne _021DF550
	cmp r3, #0
	beq _021DF554
_021DF550:
	mov r6, #0xc
	b _021DF556
_021DF554:
	mov r6, #6
_021DF556:
	add r0, r1, #0
	add r1, r6, #0
	bl _s32_div_f
	ldr r1, _021DF594 ; =0x0000077C
	str r0, [r5, r1]
	add r0, r4, #0
	add r1, r6, #0
	bl _s32_div_f
	mov r1, #0x1e
	lsl r1, r1, #6
	str r0, [r5, r1]
	add r0, r1, #7
	strb r6, [r5, r0]
	ldr r0, _021DF598 ; =MOD14_021DF5B0
	add r1, r5, #0
	mov r2, #0
	bl MOD14_021DDD40
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DF584: .word 0x0000076C
_021DF588: .word 0x00000786
_021DF58C: .word 0x00000764
_021DF590: .word 0x00000778
_021DF594: .word 0x0000077C
_021DF598: .word MOD14_021DF5B0

	thumb_func_start MOD14_021DF59C
MOD14_021DF59C: ; 0x021DF59C
	ldr r1, _021DF5AC ; =0x00000787
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _021DF5A8
	mov r0, #1
	bx lr
_021DF5A8:
	mov r0, #0
	bx lr
	.align 2, 0
_021DF5AC: .word 0x00000787

	thumb_func_start MOD14_021DF5B0
MOD14_021DF5B0: ; 0x021DF5B0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	mov r1, #0
	ldr r0, _021DF72C ; =0x00000787
	str r1, [sp, #8]
	ldrb r2, [r4, r0]
	cmp r2, #0
	beq _021DF68A
	add r1, r0, #0
	sub r1, #0x13
	ldr r2, [r4, r1]
	add r1, r0, #0
	sub r1, #0xb
	ldr r1, [r4, r1]
	add r2, r2, r1
	add r1, r0, #0
	sub r1, #0x13
	str r2, [r4, r1]
	add r1, r0, #0
	sub r1, #0xb
	ldr r1, [r4, r1]
	cmp r1, #0
	ble _021DF5F8
	add r1, r0, #0
	sub r1, #0x13
	ldr r2, [r4, r1]
	mov r1, #0x11
	lsl r1, r1, #0x10
	cmp r2, r1
	ble _021DF5F8
	ldr r1, _021DF730 ; =0x00156000
	sub r0, #0x13
	sub r1, r1, r2
	str r1, [r4, r0]
_021DF5F8:
	ldr r1, _021DF734 ; =0x0000077C
	ldr r0, [r4, r1]
	cmp r0, #0
	bge _021DF61A
	add r0, r1, #0
	sub r0, #8
	ldr r2, [r4, r0]
	mov r0, #0x46
	lsl r0, r0, #0xc
	cmp r2, r0
	bge _021DF61A
	sub r2, r0, r2
	mov r0, #0x11
	lsl r0, r0, #0x10
	sub r0, r0, r2
	sub r1, #8
	str r0, [r4, r1]
_021DF61A:
	ldr r1, _021DF738 ; =0x00000778
	add r0, r1, #0
	add r0, #8
	ldr r2, [r4, r1]
	ldr r0, [r4, r0]
	add r0, r2, r0
	str r0, [r4, r1]
	add r0, r1, #0
	add r0, #8
	ldr r0, [r4, r0]
	cmp r0, #0
	ble _021DF644
	mov r0, #0xd
	ldr r2, [r4, r1]
	lsl r0, r0, #0x10
	cmp r2, r0
	ble _021DF644
	mov r0, #0x2e
	lsl r0, r0, #0xe
	sub r0, r0, r2
	str r0, [r4, r1]
_021DF644:
	mov r1, #0x1e
	lsl r1, r1, #6
	ldr r0, [r4, r1]
	cmp r0, #0
	bge _021DF666
	add r0, r1, #0
	sub r0, #8
	ldr r2, [r4, r0]
	ldr r0, _021DF73C ; =0xFFFE8000
	cmp r2, r0
	bge _021DF666
	sub r2, r0, r2
	mov r0, #0xd
	lsl r0, r0, #0x10
	sub r0, r0, r2
	sub r1, #8
	str r0, [r4, r1]
_021DF666:
	ldr r0, _021DF740 ; =0x00000774
	ldr r1, [r4, r0]
	add r0, r0, #4
	str r1, [sp]
	ldr r0, [r4, r0]
	add r1, sp, #0
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r4, #0
	bl MOD14_021E0320
	ldr r0, _021DF72C ; =0x00000787
	add sp, #0xc
	ldrb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, r0]
	pop {r4, r5, pc}
_021DF68A:
	add r2, r0, #0
	sub r2, #0x1b
	ldr r2, [r4, r2]
	sub r0, #0x17
	lsl r2, r2, #0xc
	str r2, [sp]
	ldr r0, [r4, r0]
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	str r1, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl MOD14_021E0320
	ldr r0, _021DF744 ; =0x0000076C
	add r1, r0, #0
	ldr r2, [r4, r0]
	sub r1, #8
	str r2, [r4, r1]
	add r1, r0, #4
	ldr r2, [r4, r1]
	sub r1, r0, #4
	str r2, [r4, r1]
	add r1, r0, #0
	add r1, #0x1a
	ldrb r2, [r4, r1]
	add r1, r0, #0
	add r1, #0x19
	strb r2, [r4, r1]
	add r0, #0x24
	ldr r0, [r4, r0]
	bl MOD14_021DC3D0
	ldr r1, _021DF748 ; =0x00000789
	strb r0, [r4, r1]
	add r0, r1, #7
	ldr r0, [r4, r0]
	bl MOD14_021DC3D8
	ldr r1, _021DF74C ; =0x0000078A
	strb r0, [r4, r1]
	add r0, r1, #6
	ldr r0, [r4, r0]
	bl MOD14_021DC3E8
	ldr r1, _021DF750 ; =0x0000078B
	strb r0, [r4, r1]
	sub r0, r1, #5
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _021DF6F8
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_020200A0
_021DF6F8:
	ldr r0, _021DF754 ; =0x00000786
	ldrb r0, [r4, r0]
	cmp r0, #2
	ldr r0, [r4, #0xc]
	beq _021DF712
	mov r1, #6
	bl FUN_02020130
	ldr r0, [r4, #0x10]
	mov r1, #7
	bl FUN_02020130
	b _021DF720
_021DF712:
	mov r1, #8
	bl FUN_02020130
	ldr r0, [r4, #0x10]
	mov r1, #9
	bl FUN_02020130
_021DF720:
	add r0, r5, #0
	bl FUN_0200CAB4
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021DF72C: .word 0x00000787
_021DF730: .word 0x00156000
_021DF734: .word 0x0000077C
_021DF738: .word 0x00000778
_021DF73C: .word 0xFFFE8000
_021DF740: .word 0x00000774
_021DF744: .word 0x0000076C
_021DF748: .word 0x00000789
_021DF74C: .word 0x0000078A
_021DF750: .word 0x0000078B
_021DF754: .word 0x00000786

	thumb_func_start MOD14_021DF758
MOD14_021DF758: ; 0x021DF758
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02020130
	mov r1, #2
	mov r0, #0x1e
	lsl r1, r1, #0xc
	lsl r0, r0, #6
	str r1, [r4, r0]
	add r1, r0, #0
	sub r1, #0x18
	ldr r2, [r4, r1]
	add r1, r0, #0
	add r2, #0xc
	sub r1, #0x10
	str r2, [r4, r1]
	add r1, r0, #7
	mov r2, #6
	strb r2, [r4, r1]
	mov r1, #0
	add r0, r0, #4
	strb r1, [r4, r0]
	add r0, r4, #0
	bl MOD14_021E03CC
	ldr r0, _021DF79C ; =MOD14_021DF7B4
	add r1, r4, #0
	mov r2, #0
	bl MOD14_021DDD40
	pop {r4, pc}
	nop
_021DF79C: .word MOD14_021DF7B4

	thumb_func_start MOD14_021DF7A0
MOD14_021DF7A0: ; 0x021DF7A0
	ldr r1, _021DF7B0 ; =0x00000784
	ldrb r0, [r0, r1]
	cmp r0, #0xff
	bne _021DF7AC
	mov r0, #1
	bx lr
_021DF7AC:
	mov r0, #0
	bx lr
	.align 2, 0
_021DF7B0: .word 0x00000784

	thumb_func_start MOD14_021DF7B4
MOD14_021DF7B4: ; 0x021DF7B4
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	ldr r1, _021DF888 ; =0x00000784
	str r0, [r3]
	ldrb r0, [r4, r1]
	cmp r0, #0
	beq _021DF7E0
	cmp r0, #1
	beq _021DF83C
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021DF7E0:
	add r0, r1, #0
	mov r3, #0
	add r0, #0xa
	strb r3, [r4, r0]
	add r0, r1, #3
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _021DF80E
	sub r0, r1, #4
	ldr r3, [sp, #4]
	ldr r0, [r4, r0]
	add r1, r2, #0
	add r0, r3, r0
	str r0, [sp, #4]
	add r0, r4, #0
	bl MOD14_021E0320
	ldr r0, _021DF88C ; =0x00000787
	add sp, #0xc
	ldrb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_021DF80E:
	sub r1, #0x14
	ldr r0, [r4, r1]
	add r1, r2, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	add r0, r4, #0
	bl MOD14_021E0320
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_02020130
	add r0, r4, #0
	bl MOD14_021E0554
	ldr r0, _021DF88C ; =0x00000787
	mov r1, #6
	strb r1, [r4, r0]
	sub r1, r0, #3
	ldrb r1, [r4, r1]
	sub r0, r0, #3
	add r1, r1, #1
	strb r1, [r4, r0]
_021DF83C:
	ldr r0, _021DF88C ; =0x00000787
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021DF862
	sub r0, r0, #7
	ldr r1, [sp, #4]
	ldr r0, [r4, r0]
	sub r0, r1, r0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, sp, #0
	bl MOD14_021E0320
	ldr r0, _021DF88C ; =0x00000787
	add sp, #0xc
	ldrb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_021DF862:
	sub r0, #0x1f
	ldr r0, [r4, r0]
	add r1, sp, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	add r0, r4, #0
	bl MOD14_021E0320
	ldr r0, _021DF888 ; =0x00000784
	mov r1, #0xff
	strb r1, [r4, r0]
	mov r1, #1
	add r0, #0xa
	strb r1, [r4, r0]
	add r0, r5, #0
	bl FUN_0200CAB4
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DF888: .word 0x00000784
_021DF88C: .word 0x00000787

	thumb_func_start MOD14_021DF890
MOD14_021DF890: ; 0x021DF890
	add r1, r0, #0
	mov r2, #2
	mov r0, #0x1e
	lsl r2, r2, #0xc
	lsl r0, r0, #6
	str r2, [r1, r0]
	add r2, r0, #0
	sub r2, #0x18
	ldr r3, [r1, r2]
	add r2, r0, #0
	add r3, #0xc
	sub r2, #0x10
	str r3, [r1, r2]
	add r2, r0, #7
	mov r3, #6
	strb r3, [r1, r2]
	ldr r3, _021DF8BC ; =MOD14_021DDD40
	mov r2, #0
	add r0, r0, #4
	strb r2, [r1, r0]
	ldr r0, _021DF8C0 ; =MOD14_021DF8F8
	bx r3
	.align 2, 0
_021DF8BC: .word MOD14_021DDD40
_021DF8C0: .word MOD14_021DF8F8

	thumb_func_start MOD14_021DF8C4
MOD14_021DF8C4: ; 0x021DF8C4
	push {r4, lr}
	ldr r1, _021DF8F0 ; =0x00000784
	add r4, r0, #0
	ldrb r1, [r4, r1]
	cmp r1, #0xff
	bne _021DF8EC
	bl MOD14_021E0588
	ldr r2, _021DF8F4 ; =0x00000754
	add r1, r4, #0
	ldr r0, [r4, #0x48]
	ldr r2, [r4, r2]
	add r1, #0x4c
	bl MOD14_021E08E4
	ldr r0, _021DF8F4 ; =0x00000754
	mov r1, #0
	str r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
_021DF8EC:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021DF8F0: .word 0x00000784
_021DF8F4: .word 0x00000754

	thumb_func_start MOD14_021DF8F8
MOD14_021DF8F8: ; 0x021DF8F8
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	ldr r1, _021DF9D4 ; =0x00000784
	str r0, [r3]
	ldrb r0, [r4, r1]
	cmp r0, #0
	beq _021DF924
	cmp r0, #1
	beq _021DF980
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021DF924:
	add r0, r1, #0
	mov r3, #0
	add r0, #0xa
	strb r3, [r4, r0]
	add r0, r1, #3
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _021DF952
	sub r0, r1, #4
	ldr r3, [sp, #4]
	ldr r0, [r4, r0]
	add r1, r2, #0
	add r0, r3, r0
	str r0, [sp, #4]
	add r0, r4, #0
	bl MOD14_021E0320
	ldr r0, _021DF9D8 ; =0x00000787
	add sp, #0xc
	ldrb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_021DF952:
	sub r1, #0x14
	ldr r0, [r4, r1]
	add r1, r2, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	add r0, r4, #0
	bl MOD14_021E0320
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02020130
	add r0, r4, #0
	bl MOD14_021E0714
	ldr r0, _021DF9D8 ; =0x00000787
	mov r1, #6
	strb r1, [r4, r0]
	sub r1, r0, #3
	ldrb r1, [r4, r1]
	sub r0, r0, #3
	add r1, r1, #1
	strb r1, [r4, r0]
_021DF980:
	ldr r0, _021DF9D8 ; =0x00000787
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021DF9A6
	sub r0, r0, #7
	ldr r1, [sp, #4]
	ldr r0, [r4, r0]
	sub r0, r1, r0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, sp, #0
	bl MOD14_021E0320
	ldr r0, _021DF9D8 ; =0x00000787
	add sp, #0xc
	ldrb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_021DF9A6:
	sub r0, #0x1f
	ldr r0, [r4, r0]
	add r1, sp, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	add r0, r4, #0
	bl MOD14_021E0320
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_02020130
	ldr r0, _021DF9D4 ; =0x00000784
	mov r1, #0xff
	strb r1, [r4, r0]
	mov r1, #1
	add r0, #0xa
	strb r1, [r4, r0]
	add r0, r5, #0
	bl FUN_0200CAB4
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DF9D4: .word 0x00000784
_021DF9D8: .word 0x00000787

	thumb_func_start MOD14_021DF9DC
MOD14_021DF9DC: ; 0x021DF9DC
	push {r4, r5, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, [r5, #4]
	mov r1, #1
	bl FUN_02020130
	ldr r0, _021DFA50 ; =0x00000788
	mov r1, #0
	strb r1, [r5, r0]
	add r0, r5, #0
	bl MOD14_021E0740
	add r4, r0, #0
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x10
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r4, #0
	bl FUN_0202032C
	str r0, [sp]
	ldr r1, [r5, #0x4c]
	ldr r2, [sp, #0x14]
	add r0, r5, #0
	mov r3, #1
	bl MOD14_021DFA7C
	ldr r0, [r5, #0x4c]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #4
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r5, #0x4c]
	bl FUN_0202032C
	str r0, [sp]
	mov r3, #0
	ldr r2, [sp, #8]
	add r0, r5, #0
	add r1, r4, #0
	mvn r3, r3
	bl MOD14_021DFA7C
	ldr r0, _021DFA54 ; =0x00000784
	mov r1, #0
	strb r1, [r5, r0]
	add sp, #0x1c
	pop {r4, r5, pc}
	nop
_021DFA50: .word 0x00000788
_021DFA54: .word 0x00000784

	thumb_func_start MOD14_021DFA58
MOD14_021DFA58: ; 0x021DFA58
	push {r4, lr}
	add r4, r0, #0
	bl MOD14_021DFB08
	cmp r0, #0
	beq _021DFA76
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_02020130
	add r0, r4, #0
	bl MOD14_021E062C
	mov r0, #1
	pop {r4, pc}
_021DFA76:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DFA7C
MOD14_021DFA7C: ; 0x021DFA7C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0xa
	mov r1, #0x2c
	add r7, r2, #0
	str r3, [sp]
	bl FUN_02016998
	add r4, r0, #0
	beq _021DFAFC
	add r0, r6, #0
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #4
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #0xc
	str r0, [r2]
	str r6, [r4]
	strh r1, [r4, #4]
	mov r0, #6
	strh r0, [r4, #6]
	ldr r0, [sp, #0x28]
	str r0, [r4, #8]
	ldr r0, [sp, #8]
	str r0, [r4, #0xc]
	ldr r0, [sp, #4]
	str r0, [r4, #0x14]
	str r7, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0x18]
	ldr r0, [sp]
	add r2, r0, #0
	mul r2, r1
	str r2, [r4, #0x24]
	ldr r2, [r4, #0x10]
	ldr r0, [r4, #0xc]
	sub r0, r2, r0
	bl _s32_div_f
	str r0, [r4, #0x1c]
	mov r0, #0xf
	lsl r0, r0, #0xc
	str r0, [r4, #0x20]
	ldr r0, _021DFB00 ; =MOD14_021DFB28
	add r1, r4, #0
	mov r2, #0
	str r5, [r4, #0x28]
	bl MOD14_021DDD40
	cmp r0, #0
	beq _021DFAF6
	ldr r0, _021DFB04 ; =0x00000788
	mov r1, #1
	add sp, #0x10
	strb r1, [r5, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DFAF6:
	add r0, r4, #0
	bl FUN_02016A18
_021DFAFC:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DFB00: .word MOD14_021DFB28
_021DFB04: .word 0x00000788

	thumb_func_start MOD14_021DFB08
MOD14_021DFB08: ; 0x021DFB08
	ldr r1, _021DFB18 ; =0x00000788
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _021DFB14
	mov r0, #1
	bx lr
_021DFB14:
	mov r0, #0
	bx lr
	.align 2, 0
_021DFB18: .word 0x00000788

	thumb_func_start MOD14_021DFB1C
MOD14_021DFB1C: ; 0x021DFB1C
	ldr r1, _021DFB24 ; =0x00000788
	mov r2, #0
	strb r2, [r0, r1]
	bx lr
	.align 2, 0
_021DFB24: .word 0x00000788

	thumb_func_start MOD14_021DFB28
MOD14_021DFB28: ; 0x021DFB28
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	ldrh r0, [r4, #4]
	cmp r0, #0
	beq _021DFB90
	sub r0, r0, #1
	strh r0, [r4, #4]
	ldrh r1, [r4, #4]
	ldrh r0, [r4, #6]
	cmp r1, r0
	bne _021DFB5E
	ldr r0, [r4]
	ldr r1, [r4, #8]
	bl MOD14_021DDE24
_021DFB5E:
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x1c]
	add r0, r1, r0
	str r0, [r4, #0xc]
	str r0, [sp, #4]
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x20]
	add r0, r1, r0
	str r0, [r4, #0x18]
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl FUN_0201B93C
	ldr r1, [r4, #0x24]
	add r2, r1, #0
	mul r2, r0
	ldr r0, [r4, #0x14]
	add r1, sp, #0
	add r0, r0, r2
	str r0, [sp]
	ldr r0, [r4]
	bl FUN_02020044
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021DFB90:
	ldr r0, [r4, #0x14]
	add r1, r2, #0
	str r0, [sp]
	ldr r0, [r4, #0x10]
	str r0, [sp, #4]
	ldr r0, [r4]
	bl FUN_02020044
	ldr r1, _021DFBB4 ; =MOD14_021DFB1C
	ldr r2, [r4, #0x28]
	add r0, r4, #0
	bl MOD14_021DDF30
	add r0, r5, #0
	bl FUN_0200CAB4
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DFBB4: .word MOD14_021DFB1C

	thumb_func_start MOD14_021DFBB8
MOD14_021DFBB8: ; 0x021DFBB8
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, _021DFC1C ; =0x0000078C
	ldrb r1, [r4, r0]
	cmp r1, #0
	bne _021DFBD6
	add r0, r0, #1
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _021DFBD6
	ldr r0, [r4, #4]
	mov r1, #3
	bl FUN_02020130
_021DFBD6:
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r5, r0, #0
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	mov r0, #2
	ldr r1, [sp, #4]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r2, #0
	bl MOD14_021E0320
	ldr r0, _021DFC20 ; =0x00000784
	mov r2, #0
	strb r2, [r4, r0]
	add r0, r0, #3
	strb r2, [r4, r0]
	ldr r0, _021DFC24 ; =MOD14_021DFC40
	add r1, r4, #0
	bl MOD14_021DDD40
	cmp r0, #0
	beq _021DFC18
	ldr r0, _021DFC28 ; =0x00000788
	mov r1, #1
	strb r1, [r4, r0]
_021DFC18:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_021DFC1C: .word 0x0000078C
_021DFC20: .word 0x00000784
_021DFC24: .word MOD14_021DFC40
_021DFC28: .word 0x00000788

	thumb_func_start MOD14_021DFC2C
MOD14_021DFC2C: ; 0x021DFC2C
	ldr r1, _021DFC3C ; =0x00000788
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _021DFC38
	mov r0, #1
	bx lr
_021DFC38:
	mov r0, #0
	bx lr
	.align 2, 0
_021DFC3C: .word 0x00000788

	thumb_func_start MOD14_021DFC40
MOD14_021DFC40: ; 0x021DFC40
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r4, r1, #0
	ldr r1, _021DFD18 ; =0x00000784
	add r5, r0, #0
	ldrb r0, [r4, r1]
	cmp r0, #0
	beq _021DFC58
	cmp r0, #1
	beq _021DFCBE
	add sp, #0x18
	pop {r4, r5, r6, pc}
_021DFC58:
	add r0, r1, #3
	ldrb r0, [r4, r0]
	add r2, r0, #1
	add r0, r1, #3
	strb r2, [r4, r0]
	ldrb r0, [r4, r0]
	cmp r0, #4
	blo _021DFD14
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [sp, #0x10]
	mov r2, #3
	asr r0, r0, #0xc
	add r1, r0, #6
	mov r0, #0x77
	lsl r0, r0, #4
	str r1, [r4, r0]
	add r1, r0, #0
	lsl r2, r2, #0xc
	add r1, #0x10
	str r2, [r4, r1]
	add r1, r0, #0
	mov r2, #2
	add r1, #0x17
	strb r2, [r4, r1]
	add r1, r0, #0
	add r1, #0x1c
	ldrb r1, [r4, r1]
	cmp r1, #0
	bne _021DFCB2
	add r0, #0x1d
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _021DFCB2
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_02020130
_021DFCB2:
	ldr r0, _021DFD18 ; =0x00000784
	add sp, #0x18
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021DFCBE:
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	ldr r0, _021DFD1C ; =0x00000787
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021DFCF8
	sub r0, r0, #7
	ldr r1, [sp, #4]
	ldr r0, [r4, r0]
	add r0, r1, r0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r2, #0
	bl MOD14_021E0320
	ldr r0, _021DFD1C ; =0x00000787
	add sp, #0x18
	ldrb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021DFCF8:
	sub r0, #0x17
	ldr r0, [r4, r0]
	add r1, r2, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	add r0, r4, #0
	bl MOD14_021E0320
	ldr r0, _021DFD20 ; =0x00000788
	mov r1, #0
	strb r1, [r4, r0]
	add r0, r5, #0
	bl FUN_0200CAB4
_021DFD14:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DFD18: .word 0x00000784
_021DFD1C: .word 0x00000787
_021DFD20: .word 0x00000788

	thumb_func_start MOD14_021DFD24
MOD14_021DFD24: ; 0x021DFD24
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #0x77
	str r0, [r2]
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	asr r0, r0, #0xc
	sub r0, r0, #4
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r2, _021DFD74 ; =0xFFFFF000
	add r0, #0x10
	str r2, [r4, r0]
	add r0, r1, #0
	mov r2, #4
	add r0, #0x17
	strb r2, [r4, r0]
	mov r2, #0
	add r1, #0x14
	strb r2, [r4, r1]
	ldr r0, _021DFD78 ; =MOD14_021DFDBC
	add r1, r4, #0
	bl MOD14_021DDD40
	cmp r0, #0
	beq _021DFD70
	ldr r0, _021DFD7C ; =0x00000788
	mov r1, #1
	strb r1, [r4, r0]
_021DFD70:
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_021DFD74: .word 0xFFFFF000
_021DFD78: .word MOD14_021DFDBC
_021DFD7C: .word 0x00000788

	thumb_func_start MOD14_021DFD80
MOD14_021DFD80: ; 0x021DFD80
	push {r4, lr}
	ldr r1, _021DFDB8 ; =0x00000788
	add r4, r0, #0
	ldrb r0, [r4, r1]
	cmp r0, #0
	bne _021DFDB2
	add r0, r1, #4
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _021DFDAE
	add r0, r1, #5
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _021DFDAE
	ldr r0, [r4, #4]
	bl FUN_020201DC
	cmp r0, #0
	beq _021DFDAE
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_02020130
_021DFDAE:
	mov r0, #1
	pop {r4, pc}
_021DFDB2:
	mov r0, #0
	pop {r4, pc}
	nop
_021DFDB8: .word 0x00000788

	thumb_func_start MOD14_021DFDBC
MOD14_021DFDBC: ; 0x021DFDBC
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	ldr r0, _021DFE20 ; =0x00000787
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021DFDFE
	sub r0, r0, #7
	ldr r1, [sp, #4]
	ldr r0, [r4, r0]
	add r0, r1, r0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r2, #0
	bl MOD14_021E0320
	ldr r0, _021DFE20 ; =0x00000787
	add sp, #0xc
	ldrb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_021DFDFE:
	sub r0, #0x17
	ldr r0, [r4, r0]
	add r1, r2, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	add r0, r4, #0
	bl MOD14_021E0320
	ldr r0, _021DFE24 ; =0x00000788
	mov r1, #0
	strb r1, [r4, r0]
	add r0, r5, #0
	bl FUN_0200CAB4
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021DFE20: .word 0x00000787
_021DFE24: .word 0x00000788

	thumb_func_start MOD14_021DFE28
MOD14_021DFE28: ; 0x021DFE28
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC424
	mov r1, #0x79
	lsl r1, r1, #4
	mov r2, #0x11
	ldr r3, [r4, r1]
	lsl r2, r2, #4
	ldrh r2, [r3, r2]
	cmp r2, r0
	bne _021DFE4E
	sub r1, #0x38
	ldr r0, [r4, r1]
	bl MOD14_021DEA50
_021DFE4E:
	add r0, r4, #0
	bl MOD14_021E0720
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_02020130
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DFE60
MOD14_021DFE60: ; 0x021DFE60
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02020130
	add r1, r4, #0
	ldr r0, [r4, #0x48]
	add r1, #0x4c
	mov r2, #1
	bl MOD14_021E0C20
	ldr r0, _021DFE80 ; =0x00000784
	mov r1, #0
	strb r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_021DFE80: .word 0x00000784

	thumb_func_start MOD14_021DFE84
MOD14_021DFE84: ; 0x021DFE84
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021DFF14 ; =0x00000794
	ldr r0, [r5, r0]
	bl MOD14_021DDEDC
	ldr r1, _021DFF18 ; =0x00000784
	add r4, r0, #0
	ldrb r1, [r5, r1]
	cmp r1, #0
	beq _021DFEA4
	cmp r1, #1
	beq _021DFEBC
	cmp r1, #2
	beq _021DFEF6
	b _021DFF10
_021DFEA4:
	add r1, r5, #0
	ldr r0, [r5, #0x48]
	add r1, #0x4c
	bl MOD14_021E0C48
	cmp r0, #0
	beq _021DFF10
	ldr r0, _021DFF18 ; =0x00000784
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
	b _021DFF10
_021DFEBC:
	bl MOD14_021DA1B8
	cmp r0, #0
	beq _021DFF10
	add r0, r4, #0
	bl MOD14_021DA1C0
	cmp r0, #0
	beq _021DFEE0
	ldr r0, [r5, #4]
	mov r1, #0
	bl FUN_02020130
	add r0, r5, #0
	bl MOD14_021E0720
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DFEE0:
	add r1, r5, #0
	ldr r0, [r5, #0x48]
	add r1, #0x4c
	mov r2, #2
	bl MOD14_021E0C20
	ldr r0, _021DFF18 ; =0x00000784
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
	b _021DFF10
_021DFEF6:
	add r1, r5, #0
	ldr r0, [r5, #0x48]
	add r1, #0x4c
	bl MOD14_021E0C48
	cmp r0, #0
	beq _021DFF10
	ldr r0, [r5, #4]
	mov r1, #2
	bl FUN_02020130
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DFF10:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DFF14: .word 0x00000794
_021DFF18: .word 0x00000784

	thumb_func_start MOD14_021DFF1C
MOD14_021DFF1C: ; 0x021DFF1C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02020238
	ldr r0, _021DFF4C ; =0x0000078C
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _021DFF38
	ldr r0, [r4, #0x4c]
	mov r1, #1
	bl FUN_02020238
_021DFF38:
	ldr r0, _021DFF50 ; =0x0000078D
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021DFF4A
	sub r0, #0x2d
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD14_021E501C
_021DFF4A:
	pop {r4, pc}
	.align 2, 0
_021DFF4C: .word 0x0000078C
_021DFF50: .word 0x0000078D

	thumb_func_start MOD14_021DFF54
MOD14_021DFF54: ; 0x021DFF54
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_02020238
	ldr r0, _021DFF84 ; =0x0000078C
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _021DFF70
	ldr r0, [r4, #0x4c]
	mov r1, #2
	bl FUN_02020238
_021DFF70:
	ldr r0, _021DFF88 ; =0x0000078D
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021DFF82
	sub r0, #0x2d
	ldr r0, [r4, r0]
	mov r1, #2
	bl MOD14_021E501C
_021DFF82:
	pop {r4, pc}
	.align 2, 0
_021DFF84: .word 0x0000078C
_021DFF88: .word 0x0000078D

	thumb_func_start MOD14_021DFF8C
MOD14_021DFF8C: ; 0x021DFF8C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021DFFB0 ; =0x0000078C
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021DFFAC
	add r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC45C
	add r2, r0, #0
	ldr r0, [r4, #0x48]
	add r4, #0x4c
	add r1, r4, #0
	bl MOD14_021E0BA4
_021DFFAC:
	pop {r4, pc}
	nop
_021DFFB0: .word 0x0000078C

	thumb_func_start MOD14_021DFFB4
MOD14_021DFFB4: ; 0x021DFFB4
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC484
	add r2, r0, #0
	ldr r0, [r4, #0x4c]
	cmp r0, #0
	beq _021DFFD4
	ldr r0, [r4, #0x48]
	add r4, #0x4c
	add r1, r4, #0
	bl MOD14_021E0B54
_021DFFD4:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021DFFD8
MOD14_021DFFD8: ; 0x021DFFD8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x4c]
	add r2, r1, #0
	cmp r0, #0
	beq _021E0004
	add r1, r4, #0
	ldr r0, [r4, #0x48]
	add r1, #0x4c
	bl MOD14_021E0BA8
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC484
	add r2, r0, #0
	ldr r0, [r4, #0x48]
	add r4, #0x4c
	add r1, r4, #0
	bl MOD14_021E0B54
_021E0004:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E0008
MOD14_021E0008: ; 0x021E0008
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC49C
	cmp r0, #0
	ldr r0, [r4, #4]
	beq _021E0024
	mov r1, #1
	bl FUN_02020248
	pop {r4, pc}
_021E0024:
	mov r1, #0
	bl FUN_02020248
	pop {r4, pc}

	thumb_func_start MOD14_021E002C
MOD14_021E002C: ; 0x021E002C
	ldr r3, _021E0034 ; =0x02020131
	ldr r0, [r0, #4]
	mov r1, #1
	bx r3
	.align 2, 0
_021E0034: .word 0x02020131

	thumb_func_start MOD14_021E0038
MOD14_021E0038: ; 0x021E0038
	push {r4, lr}
	ldr r0, [r0, #4]
	add r4, r1, #0
	bl FUN_0202011C
	add r2, r0, #0
	ldmia r2!, {r0, r1}
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	str r0, [r4]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E0050
MOD14_021E0050: ; 0x021E0050
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E0074 ; =0x00000784
	mov r2, #0
	strb r2, [r4, r0]
	ldr r0, _021E0078 ; =MOD14_021E0094
	add r1, r4, #0
	bl FUN_0200CA44
	cmp r0, #0
	beq _021E0070
	ldr r0, _021E007C ; =0x0000078D
	mov r1, #1
	strb r1, [r4, r0]
	sub r0, r0, #5
	strb r1, [r4, r0]
_021E0070:
	pop {r4, pc}
	nop
_021E0074: .word 0x00000784
_021E0078: .word MOD14_021E0094
_021E007C: .word 0x0000078D

	thumb_func_start MOD14_021E0080
MOD14_021E0080: ; 0x021E0080
	ldr r1, _021E0090 ; =0x00000788
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _021E008C
	mov r0, #1
	bx lr
_021E008C:
	mov r0, #0
	bx lr
	.align 2, 0
_021E0090: .word 0x00000788

	thumb_func_start MOD14_021E0094
MOD14_021E0094: ; 0x021E0094
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021E00E8 ; =0x00000784
	add r4, r1, #0
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021E00A8
	cmp r1, #1
	beq _021E00C4
	pop {r3, r4, r5, pc}
_021E00A8:
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02020130
	mov r0, #0x76
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021E4D94
	ldr r0, _021E00E8 ; =0x00000784
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021E00C4:
	sub r0, #0x24
	ldr r0, [r4, r0]
	bl MOD14_021E4DE8
	cmp r0, #0
	beq _021E00E4
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_02020130
	ldr r0, _021E00EC ; =0x00000788
	mov r1, #0
	strb r1, [r4, r0]
	add r0, r5, #0
	bl FUN_0200CAB4
_021E00E4:
	pop {r3, r4, r5, pc}
	nop
_021E00E8: .word 0x00000784
_021E00EC: .word 0x00000788

	thumb_func_start MOD14_021E00F0
MOD14_021E00F0: ; 0x021E00F0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E0114 ; =0x00000784
	mov r2, #0
	strb r2, [r4, r0]
	ldr r0, _021E0118 ; =MOD14_021E0134
	add r1, r4, #0
	bl FUN_0200CA44
	cmp r0, #0
	beq _021E0112
	ldr r0, _021E011C ; =0x0000078D
	mov r1, #0
	strb r1, [r4, r0]
	mov r1, #1
	sub r0, r0, #5
	strb r1, [r4, r0]
_021E0112:
	pop {r4, pc}
	.align 2, 0
_021E0114: .word 0x00000784
_021E0118: .word MOD14_021E0134
_021E011C: .word 0x0000078D

	thumb_func_start MOD14_021E0120
MOD14_021E0120: ; 0x021E0120
	ldr r1, _021E0130 ; =0x00000788
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _021E012C
	mov r0, #1
	bx lr
_021E012C:
	mov r0, #0
	bx lr
	.align 2, 0
_021E0130: .word 0x00000788

	thumb_func_start MOD14_021E0134
MOD14_021E0134: ; 0x021E0134
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021E0188 ; =0x00000784
	add r4, r1, #0
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021E0148
	cmp r1, #1
	beq _021E0164
	pop {r3, r4, r5, pc}
_021E0148:
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02020130
	mov r0, #0x76
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021E4E58
	ldr r0, _021E0188 ; =0x00000784
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021E0164:
	sub r0, #0x24
	ldr r0, [r4, r0]
	bl MOD14_021E4EA4
	cmp r0, #0
	beq _021E0184
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_02020130
	ldr r0, _021E018C ; =0x00000788
	mov r1, #0
	strb r1, [r4, r0]
	add r0, r5, #0
	bl FUN_0200CAB4
_021E0184:
	pop {r3, r4, r5, pc}
	nop
_021E0188: .word 0x00000784
_021E018C: .word 0x00000788

	thumb_func_start MOD14_021E0190
MOD14_021E0190: ; 0x021E0190
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E01B0 ; =0x00000784
	mov r2, #0
	strb r2, [r4, r0]
	ldr r0, _021E01B4 ; =MOD14_021E01D0
	add r1, r4, #0
	bl FUN_0200CA44
	cmp r0, #0
	beq _021E01AC
	ldr r0, _021E01B8 ; =0x00000788
	mov r1, #1
	strb r1, [r4, r0]
_021E01AC:
	pop {r4, pc}
	nop
_021E01B0: .word 0x00000784
_021E01B4: .word MOD14_021E01D0
_021E01B8: .word 0x00000788

	thumb_func_start MOD14_021E01BC
MOD14_021E01BC: ; 0x021E01BC
	ldr r1, _021E01CC ; =0x00000788
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _021E01C8
	mov r0, #1
	bx lr
_021E01C8:
	mov r0, #0
	bx lr
	.align 2, 0
_021E01CC: .word 0x00000788

	thumb_func_start MOD14_021E01D0
MOD14_021E01D0: ; 0x021E01D0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021E0224 ; =0x00000784
	add r4, r1, #0
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021E01E4
	cmp r1, #1
	beq _021E0200
	pop {r3, r4, r5, pc}
_021E01E4:
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02020130
	mov r0, #0x76
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021E4EB4
	ldr r0, _021E0224 ; =0x00000784
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021E0200:
	sub r0, #0x24
	ldr r0, [r4, r0]
	bl MOD14_021E4F48
	cmp r0, #0
	beq _021E0220
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_02020130
	ldr r0, _021E0228 ; =0x00000788
	mov r1, #0
	strb r1, [r4, r0]
	add r0, r5, #0
	bl FUN_0200CAB4
_021E0220:
	pop {r3, r4, r5, pc}
	nop
_021E0224: .word 0x00000784
_021E0228: .word 0x00000788

	thumb_func_start MOD14_021E022C
MOD14_021E022C: ; 0x021E022C
	push {r3, lr}
	ldr r1, _021E0240 ; =0x0000078D
	ldrb r1, [r0, r1]
	cmp r1, #0
	beq _021E023E
	ldr r0, [r0, #4]
	mov r1, #1
	bl FUN_02020130
_021E023E:
	pop {r3, pc}
	.align 2, 0
_021E0240: .word 0x0000078D

	thumb_func_start MOD14_021E0244
MOD14_021E0244: ; 0x021E0244
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E0260 ; =0x0000078D
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _021E025E
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_02020130
	ldr r0, _021E0260 ; =0x0000078D
	mov r1, #0
	strb r1, [r4, r0]
_021E025E:
	pop {r4, pc}
	.align 2, 0
_021E0260: .word 0x0000078D

	thumb_func_start MOD14_021E0264
MOD14_021E0264: ; 0x021E0264
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x79
	add r5, r3, #0
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r7, r2, #0
	add r4, r1, #0
	str r0, [sp]
	bl MOD14_021DC3CC
	strb r0, [r7]
	ldrb r0, [r7]
	cmp r0, #4
	bhi _021E0318
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E028E: ; jump table
	.short _021E0298 - _021E028E - 2 ; case 0
	.short _021E02C2 - _021E028E - 2 ; case 1
	.short _021E02E4 - _021E028E - 2 ; case 2
	.short _021E02F6 - _021E028E - 2 ; case 3
	.short _021E0308 - _021E028E - 2 ; case 4
_021E0298:
	ldr r0, _021E031C ; =0x00000794
	ldr r0, [r5, r0]
	bl MOD14_021DDD98
	add r5, r0, #0
	ldr r0, [sp]
	bl MOD14_021DC3D0
	mov r1, #0x18
	add r5, #0x70
	mul r1, r0
	add r0, r5, r1
	str r0, [r6]
	ldr r0, [sp]
	bl MOD14_021DC3D8
	mov r1, #0x18
	mul r1, r0
	add r1, #0x18
	str r1, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_021E02C2:
	ldr r0, [sp]
	bl MOD14_021DC3E8
	add r7, r0, #0
	ldr r0, _021E031C ; =0x00000794
	ldr r0, [r5, r0]
	bl MOD14_021DDD60
	add r1, r7, #0
	add r2, r6, #0
	add r3, r4, #0
	bl MOD14_021E3170
	ldr r0, [r4]
	sub r0, #0x10
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_021E02E4:
	ldr r0, _021E031C ; =0x00000794
	ldr r0, [r5, r0]
	bl MOD14_021DDD98
	add r0, #0xa8
	str r0, [r6]
	mov r0, #8
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_021E02F6:
	ldr r0, _021E031C ; =0x00000794
	ldr r0, [r5, r0]
	bl MOD14_021DDD98
	add r0, #0x9f
	str r0, [r6]
	mov r0, #0xa0
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_021E0308:
	ldr r0, _021E031C ; =0x00000794
	ldr r0, [r5, r0]
	bl MOD14_021DDD98
	add r0, #0xeb
	str r0, [r6]
	mov r0, #0xa0
	str r0, [r4]
_021E0318:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E031C: .word 0x00000794

	thumb_func_start MOD14_021E0320
MOD14_021E0320: ; 0x021E0320
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r7, r0, #0
	ldr r0, [r7, #4]
	add r6, r1, #0
	bl FUN_02020044
	ldr r1, _021E03B4 ; =0x0000078C
	ldrb r0, [r7, r1]
	cmp r0, #0
	beq _021E0378
	mov r0, #0
	sub r1, #0x38
	str r0, [sp]
	str r0, [sp, #0x18]
	ldr r0, [r7, r1]
	cmp r0, #0
	bls _021E0378
	add r4, r7, #0
	add r5, r7, #0
_021E0348:
	ldr r0, _021E03B8 ; =0x00000664
	ldr r1, [r6]
	ldr r0, [r4, r0]
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r0, _021E03BC ; =0x00000668
	ldr r1, [r6, #4]
	ldr r0, [r4, r0]
	sub r0, r1, r0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	add r1, sp, #0x10
	bl FUN_02020044
	ldr r0, [sp]
	add r4, #8
	add r0, r0, #1
	str r0, [sp]
	ldr r0, _021E03C0 ; =0x00000754
	add r5, #0x34
	ldr r1, [r7, r0]
	ldr r0, [sp]
	cmp r0, r1
	blo _021E0348
_021E0378:
	ldr r0, _021E03C4 ; =0x0000078D
	ldrb r1, [r7, r0]
	cmp r1, #0
	beq _021E038A
	sub r0, #0x2d
	ldr r0, [r7, r0]
	add r1, r6, #0
	bl MOD14_021E4FDC
_021E038A:
	ldr r0, _021E03C8 ; =0x0000078E
	ldrb r0, [r7, r0]
	cmp r0, #0
	beq _021E03B0
	ldmia r6!, {r0, r1}
	add r3, sp, #4
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	mov r0, #6
	ldr r1, [sp, #8]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #8]
	ldr r0, [r7, #8]
	add r1, r2, #0
	bl FUN_02020044
_021E03B0:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021E03B4: .word 0x0000078C
_021E03B8: .word 0x00000664
_021E03BC: .word 0x00000668
_021E03C0: .word 0x00000754
_021E03C4: .word 0x0000078D
_021E03C8: .word 0x0000078E

	thumb_func_start MOD14_021E03CC
MOD14_021E03CC: ; 0x021E03CC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	mov r1, #0x79
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r0, r1]
	bl MOD14_021DC3CC
	cmp r0, #0
	beq _021E03E2
	b _021E0504
_021E03E2:
	mov r1, #0x79
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	bl MOD14_021DC4DC
	cmp r0, #0
	beq _021E042A
	mov r1, #0x79
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	bl MOD14_021DC3E0
	add r1, r0, #0
	ldr r3, [sp, #4]
	ldr r2, _021E053C ; =0x00000758
	ldr r0, [sp, #4]
	add r3, #0x4c
	ldr r0, [r0, r2]
	ldr r2, _021E0540 ; =0x000004D8
	bl MOD14_021DE980
	ldr r0, [sp, #4]
	ldr r2, _021E0544 ; =0x00000754
	mov r1, #1
	str r1, [r0, r2]
	add r1, r2, #0
	mov r3, #0
	sub r1, #0xf0
	str r3, [r0, r1]
	ldr r1, _021E0548 ; =0xFFFFC000
	sub r2, #0xec
	str r1, [r0, r2]
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
_021E042A:
	add r0, sp, #0x24
	str r0, [sp]
	mov r1, #0x79
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	add r1, sp, #0x30
	add r2, sp, #0x2c
	add r3, sp, #0x28
	bl MOD14_021DC4A4
	mov r1, #0x79
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	bl MOD14_021DC3D0
	str r0, [sp, #0x18]
	mov r1, #0x79
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	bl MOD14_021DC3D8
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0x24]
	str r0, [sp, #0x1c]
	cmp r0, r1
	bhi _021E04F8
	ldr r0, [sp, #4]
	ldr r6, [sp, #4]
	str r0, [sp, #0x10]
	add r0, #0x4c
	str r0, [sp, #0x10]
	mov r7, #0x5f
	ldr r0, [sp, #0x1c]
	mov r1, #6
	mul r1, r0
	lsl r7, r7, #4
	str r1, [sp, #0xc]
	add r5, r6, #0
_021E0482:
	ldr r4, [sp, #0x30]
	ldr r0, [sp, #0x2c]
	cmp r4, r0
	bhi _021E04E6
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x14]
	sub r1, r1, r0
	mov r0, #0x18
	add r2, r1, #0
	mul r2, r0
	sub r0, #0x1c
	sub r0, r0, r2
	lsl r0, r0, #0xc
	str r0, [sp, #8]
_021E049E:
	ldr r1, [sp, #4]
	ldr r0, _021E053C ; =0x00000758
	ldr r3, [sp, #0x10]
	ldr r0, [r1, r0]
	ldr r1, [sp, #0xc]
	add r2, r7, #0
	add r1, r4, r1
	bl MOD14_021DE980
	ldr r0, [r6, #0x4c]
	cmp r0, #0
	beq _021E04DE
	ldr r0, [sp, #0x18]
	add r7, #0x10
	sub r1, r4, r0
	mov r0, #6
	add r2, r1, #0
	lsl r0, r0, #0xe
	mul r2, r0
	ldr r0, _021E054C ; =0x00000664
	ldr r1, [sp, #8]
	str r2, [r5, r0]
	add r0, r0, #4
	str r1, [r5, r0]
	ldr r0, [sp, #0x10]
	add r6, #0x34
	add r0, #0x34
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x20]
	add r5, #8
	add r0, r0, #1
	str r0, [sp, #0x20]
_021E04DE:
	ldr r0, [sp, #0x2c]
	add r4, r4, #1
	cmp r4, r0
	bls _021E049E
_021E04E6:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x24]
	add r0, r0, #6
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, r1
	bls _021E0482
_021E04F8:
	ldr r2, _021E0544 ; =0x00000754
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #4]
	add sp, #0x34
	str r1, [r0, r2]
	pop {r4, r5, r6, r7, pc}
_021E0504:
	mov r1, #0x79
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	bl MOD14_021DC3E8
	add r1, r0, #0
	ldr r3, [sp, #4]
	ldr r2, _021E0550 ; =0x0000075C
	ldr r0, [sp, #4]
	add r3, #0x4c
	ldr r0, [r0, r2]
	ldr r2, _021E0540 ; =0x000004D8
	bl MOD14_021E3084
	ldr r2, _021E0544 ; =0x00000754
	ldr r0, [sp, #4]
	mov r1, #1
	str r1, [r0, r2]
	add r1, r2, #0
	mov r3, #0
	sub r1, #0xf0
	str r3, [r0, r1]
	ldr r1, _021E0548 ; =0xFFFFC000
	sub r2, #0xec
	str r1, [r0, r2]
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021E053C: .word 0x00000758
_021E0540: .word 0x000004D8
_021E0544: .word 0x00000754
_021E0548: .word 0xFFFFC000
_021E054C: .word 0x00000664
_021E0550: .word 0x0000075C

	thumb_func_start MOD14_021E0554
MOD14_021E0554: ; 0x021E0554
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, _021E0580 ; =0x00000754
	mov r4, #0
	ldr r0, [r6, r0]
	cmp r0, #0
	bls _021E0578
	ldr r7, _021E0580 ; =0x00000754
	add r5, r6, #0
_021E0566:
	ldr r0, [r5, #0x4c]
	mov r1, #2
	bl MOD14_021DDE24
	ldr r0, [r6, r7]
	add r4, r4, #1
	add r5, #0x34
	cmp r4, r0
	blo _021E0566
_021E0578:
	ldr r0, _021E0584 ; =0x0000078C
	mov r1, #1
	strb r1, [r6, r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E0580: .word 0x00000754
_021E0584: .word 0x0000078C

	thumb_func_start MOD14_021E0588
MOD14_021E0588: ; 0x021E0588
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021E0604
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD14_021DC4DC
	cmp r0, #0
	beq _021E05C2
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD14_021DC3E0
	add r1, r0, #0
	ldr r0, _021E0620 ; =0x00000758
	ldr r0, [r5, r0]
	add r5, #0x4c
	add r2, r5, #0
	bl MOD14_021DE9D4
	pop {r3, r4, r5, r6, r7, pc}
_021E05C2:
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD14_021DC4F8
	add r7, r0, #0
	ldr r0, _021E0624 ; =0x00000754
	mov r4, #0
	ldr r0, [r5, r0]
	cmp r0, #0
	bls _021E061C
	add r6, r5, #0
	add r6, #0x4c
_021E05DC:
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl MOD14_021DC528
	add r1, r0, #0
	ldr r0, _021E0620 ; =0x00000758
	add r1, r7, r1
	ldr r0, [r5, r0]
	add r2, r6, #0
	bl MOD14_021DE9D4
	ldr r0, _021E0624 ; =0x00000754
	add r4, r4, #1
	ldr r0, [r5, r0]
	add r6, #0x34
	cmp r4, r0
	blo _021E05DC
	pop {r3, r4, r5, r6, r7, pc}
_021E0604:
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD14_021DC3E8
	add r1, r0, #0
	ldr r0, _021E0628 ; =0x0000075C
	ldr r0, [r5, r0]
	add r5, #0x4c
	add r2, r5, #0
	bl MOD14_021E30C0
_021E061C:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E0620: .word 0x00000758
_021E0624: .word 0x00000754
_021E0628: .word 0x0000075C

	thumb_func_start MOD14_021E062C
MOD14_021E062C: ; 0x021E062C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021E06A2
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD14_021DC3E0
	add r4, r0, #0
	ldr r0, _021E0708 ; =0x00000758
	add r1, r4, #0
	ldr r0, [r5, r0]
	bl MOD14_021DEA38
	add r6, r0, #0
	add r1, r5, #0
	mov r2, #0x5f
	ldr r0, [r5, #0x48]
	add r1, #0x4c
	lsl r2, r2, #4
	bl MOD14_021E0BBC
	mov r2, #6
	ldr r0, [r5, #0x48]
	add r1, r6, #0
	lsl r2, r2, #8
	bl MOD14_021E0BBC
	bl OS_WaitVBlankIntr
	ldr r0, _021E0708 ; =0x00000758
	add r3, r5, #0
	ldr r0, [r5, r0]
	ldr r2, _021E070C ; =0x000004D8
	add r1, r4, #0
	add r3, #0x80
	bl MOD14_021DE980
	ldr r0, _021E0708 ; =0x00000758
	add r2, r5, #0
	ldr r0, [r5, r0]
	add r1, r4, #0
	add r2, #0x4c
	bl MOD14_021DE9D4
	add r0, r5, #0
	add r5, #0x4c
	add r0, #0x80
	add r1, r5, #0
	mov r2, #1
	bl MOD14_021E0930
	pop {r4, r5, r6, pc}
_021E06A2:
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD14_021DC3E8
	add r4, r0, #0
	ldr r0, _021E0710 ; =0x0000075C
	add r1, r4, #0
	ldr r0, [r5, r0]
	bl MOD14_021E3158
	add r6, r0, #0
	add r1, r5, #0
	mov r2, #0x5f
	ldr r0, [r5, #0x48]
	add r1, #0x4c
	lsl r2, r2, #4
	bl MOD14_021E0BBC
	mov r2, #6
	ldr r0, [r5, #0x48]
	add r1, r6, #0
	lsl r2, r2, #8
	bl MOD14_021E0BBC
	bl OS_WaitVBlankIntr
	ldr r0, _021E0710 ; =0x0000075C
	add r3, r5, #0
	ldr r0, [r5, r0]
	ldr r2, _021E070C ; =0x000004D8
	add r1, r4, #0
	add r3, #0x80
	bl MOD14_021E3084
	ldr r0, _021E0710 ; =0x0000075C
	add r2, r5, #0
	ldr r0, [r5, r0]
	add r1, r4, #0
	add r2, #0x4c
	bl MOD14_021E3114
	add r0, r5, #0
	add r5, #0x4c
	add r0, #0x80
	add r1, r5, #0
	mov r2, #1
	bl MOD14_021E0930
	pop {r4, r5, r6, pc}
	nop
_021E0708: .word 0x00000758
_021E070C: .word 0x000004D8
_021E0710: .word 0x0000075C

	thumb_func_start MOD14_021E0714
MOD14_021E0714: ; 0x021E0714
	ldr r1, _021E071C ; =0x0000078C
	mov r2, #0
	strb r2, [r0, r1]
	bx lr
	.align 2, 0
_021E071C: .word 0x0000078C

	thumb_func_start MOD14_021E0720
MOD14_021E0720: ; 0x021E0720
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4, #0x48]
	add r1, #0x4c
	mov r2, #1
	bl MOD14_021E0908
	ldr r0, _021E073C ; =0x0000078C
	mov r1, #0
	strb r1, [r4, r0]
	sub r0, #0x38
	str r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_021E073C: .word 0x0000078C

	thumb_func_start MOD14_021E0740
MOD14_021E0740: ; 0x021E0740
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021E076A
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC3E0
	add r1, r0, #0
	ldr r0, _021E0784 ; =0x00000758
	ldr r0, [r4, r0]
	bl MOD14_021DEA38
	ldr r0, [r0]
	pop {r4, pc}
_021E076A:
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD14_021DC3E8
	add r1, r0, #0
	ldr r0, _021E0788 ; =0x0000075C
	ldr r0, [r4, r0]
	bl MOD14_021E3158
	ldr r0, [r0]
	pop {r4, pc}
	nop
_021E0784: .word 0x00000758
_021E0788: .word 0x0000075C

	thumb_func_start MOD14_021E078C
MOD14_021E078C: ; 0x021E078C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	add r0, sp, #0x18
	add r4, r1, #0
	add r6, r2, #0
	str r3, [sp, #8]
	bl FUN_020B19DC
	bl FUN_0206B888
	add r1, r0, #0
	mov r0, #0xa
	str r0, [sp]
	add r0, sp, #0x18
	str r0, [sp, #4]
	mov r0, #0x13
	mov r2, #1
	mov r3, #0x40
	bl FUN_02006A8C
	bl FUN_0206B888
	add r1, r0, #0
	mov r0, #0x13
	add r2, sp, #0x14
	mov r3, #0xa
	bl FUN_02006C08
	str r0, [sp, #0xc]
	cmp r0, #0
	beq _021E0818
	add r0, sp, #0x18
	bl FUN_020B19DC
	ldr r0, [sp, #0xc]
	add r1, sp, #0x10
	bl FUN_020B00F0
	ldr r2, [sp, #0x14]
	add r7, r0, #0
	ldr r0, [r2, #0xc]
	mov r1, #8
	str r1, [sp]
	ldr r2, [r2, #8]
	ldr r3, _021E0898 ; =0x0000057F
	add r1, r0, #0
	lsr r2, r2, #1
	bl MOD14_021DDE40
	cmp r7, #0
	beq _021E0806
	add r0, sp, #0x18
	str r0, [sp]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x10]
	mov r2, #0xc0
	mov r3, #1
	bl FUN_020B10E8
	b _021E0812
_021E0806:
	ldr r0, [sp, #0x14]
	mov r1, #0xc0
	mov r2, #1
	add r3, sp, #0x18
	bl FUN_020B1240
_021E0812:
	ldr r0, [sp, #0xc]
	bl FUN_02016A18
_021E0818:
	mov r0, #0xa
	add r3, r5, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x15
	mov r2, #1
	add r3, #0x10
	bl FUN_02006C30
	str r0, [r5, #8]
	mov r0, #0xa
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x16
	mov r2, #1
	add r3, r5, #4
	bl FUN_02006C5C
	str r0, [r5]
	mov r0, #0xa
	add r3, r5, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x17
	mov r2, #1
	add r3, #0x1c
	bl FUN_02006C30
	str r0, [r5, #0x14]
	mov r0, #0xa
	add r3, r5, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x18
	mov r2, #1
	add r3, #0x20
	bl FUN_02006C5C
	str r0, [r5, #0x18]
	mov r0, #0x13
	mov r1, #0xa
	bl FUN_02006670
	str r0, [r5, #0x48]
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021E0882
	ldr r0, [r5]
	cmp r0, #0
	beq _021E0882
	ldr r0, [r5, #0x48]
	cmp r0, #0
	bne _021E0888
_021E0882:
	add sp, #0x2c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021E0888:
	ldr r0, [sp, #8]
	str r0, [r5, #0x24]
	str r6, [r5, #0x40]
	str r4, [r5, #0x44]
	mov r0, #1
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_021E0898: .word 0x0000057F

	thumb_func_start MOD14_021E089C
MOD14_021E089C: ; 0x021E089C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021E08AE
	bl FUN_02016A18
	mov r0, #0
	str r0, [r4, #8]
_021E08AE:
	ldr r0, [r4]
	cmp r0, #0
	beq _021E08BC
	bl FUN_02016A18
	mov r0, #0
	str r0, [r4]
_021E08BC:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021E08CA
	bl FUN_02016A18
	mov r0, #0
	str r0, [r4, #0x14]
_021E08CA:
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _021E08D8
	bl FUN_02016A18
	mov r0, #0
	str r0, [r4, #0x18]
_021E08D8:
	ldr r0, [r4, #0x48]
	cmp r0, #0
	beq _021E08E2
	bl FUN_020066F4
_021E08E2:
	pop {r4, pc}

	thumb_func_start MOD14_021E08E4
MOD14_021E08E4: ; 0x021E08E4
	push {r4, r5, r6, lr}
	add r4, r2, #0
	add r0, r4, #0
	add r5, r1, #0
	sub r4, r4, #1
	cmp r0, #0
	beq _021E0906
	mov r6, #0
_021E08F4:
	add r0, r5, #4
	str r6, [r5]
	bl FUN_020B1A24
	add r0, r4, #0
	add r5, #0x34
	sub r4, r4, #1
	cmp r0, #0
	bne _021E08F4
_021E0906:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021E0908
MOD14_021E0908: ; 0x021E0908
	push {r4, r5, r6, lr}
	add r4, r2, #0
	add r0, r4, #0
	add r5, r1, #0
	sub r4, r4, #1
	cmp r0, #0
	beq _021E092E
	mov r6, #0
_021E0918:
	ldr r0, [r5]
	cmp r0, #0
	beq _021E0924
	bl FUN_0201FFC8
	str r6, [r5]
_021E0924:
	add r0, r4, #0
	add r5, #0x34
	sub r4, r4, #1
	cmp r0, #0
	bne _021E0918
_021E092E:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021E0930
MOD14_021E0930: ; 0x021E0930
	mov r3, #0x34
	mul r3, r2
	add r2, r3, #0
	ldr r3, _021E093C ; =0x020CE210
	bx r3
	nop
_021E093C: .word 0x020CE210

	thumb_func_start MOD14_021E0940
MOD14_021E0940: ; 0x021E0940
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	ldr r4, [sp, #0x64]
	bl FUN_02066A6C
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x44]
	bl MOD14_021DDD48
	add r2, r0, #0
	ldr r0, [r5, #4]
	mov r1, #0
	str r0, [sp]
	ldr r0, [sp, #0x58]
	str r0, [sp, #4]
	ldr r3, [r5, #0x10]
	add r0, sp, #0x20
	bl MOD14_021DDDB4
	add r0, r6, #0
	mov r1, #5
	mov r2, #0
	bl FUN_020672BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x18]
	add r0, r6, #0
	mov r1, #0x4c
	mov r2, #0
	bl FUN_020672BC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x14]
	add r0, r6, #0
	mov r1, #0x70
	mov r2, #0
	bl FUN_020672BC
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	add r0, r6, #0
	bl FUN_0206B688
	str r0, [r4, #0x28]
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r1, r7, #0
	bl FUN_0206B7BC
	strh r0, [r4, #0x2c]
	add r0, r6, #0
	mov r1, #6
	mov r2, #0
	bl FUN_020672BC
	strh r0, [r4, #0x30]
	add r0, r6, #0
	mov r1, #0xb
	mov r2, #0
	bl FUN_020672BC
	strh r0, [r4, #0x2e]
	add r0, r4, #4
	bl FUN_020B1A24
	add r0, r5, #0
	add r0, #0x4c
	str r0, [sp]
	mov r3, #0xa
	ldr r0, [r5, #0x48]
	ldr r1, [r4, #0x28]
	mov r2, #0
	lsl r3, r3, #6
	bl FUN_02006814
	add r0, r5, #0
	add r0, #0x4c
	add r1, sp, #0x1c
	bl FUN_020B0088
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021E0A5C ; =0x00300010
	add r3, r4, #4
	and r1, r0
	ldr r0, [sp, #0x1c]
	str r1, [r0, #8]
	lsr r1, r2, #0x11
	ldr r0, [sp, #0x1c]
	mov r2, #1
	str r1, [r0, #0x10]
	ldr r1, [sp, #0x60]
	ldr r0, [sp, #0x1c]
	lsl r1, r1, #5
	bl FUN_020B1768
	add r0, r4, #4
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x5c]
	ldr r2, [sp, #8]
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #0x24]
	ldr r3, [sp, #0xc]
	add r1, sp, #0x20
	bl MOD14_021DDDD4
	str r0, [r4]
	cmp r0, #0
	bne _021E0A36
	bl ErrorHandling
_021E0A36:
	ldrh r1, [r4, #0x2c]
	ldr r0, [r4]
	add r1, r1, #2
	bl FUN_02020248
	ldr r0, [r5, #0x40]
	bl MOD14_021DC484
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021E0B54
	ldr r1, [sp, #0x10]
	add r0, r6, #0
	bl FUN_02066A94
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021E0A5C: .word 0x00300010

	thumb_func_start MOD14_021E0A60
MOD14_021E0A60: ; 0x021E0A60
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	str r2, [sp, #8]
	add r7, r3, #0
	ldr r4, [sp, #0x70]
	bl FUN_02066A6C
	str r0, [sp, #0x14]
	add r0, r6, #0
	mov r1, #0x4c
	mov r2, #0
	bl FUN_020672BC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10]
	add r0, r6, #0
	mov r1, #0x70
	mov r2, #0
	bl FUN_020672BC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x44]
	bl MOD14_021DDD48
	add r2, r0, #0
	ldr r0, [r5, #4]
	mov r1, #0
	str r0, [sp]
	ldr r0, [sp, #0x64]
	str r0, [sp, #4]
	ldr r3, [r5, #0x10]
	add r0, sp, #0x1c
	bl MOD14_021DDDB4
	str r7, [r4, #0x28]
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	bl FUN_0206B7BC
	strh r0, [r4, #0x2c]
	add r0, r6, #0
	mov r1, #6
	mov r2, #0
	bl FUN_020672BC
	strh r0, [r4, #0x30]
	add r0, r6, #0
	mov r1, #0xb
	mov r2, #0
	bl FUN_020672BC
	strh r0, [r4, #0x2e]
	add r0, r4, #4
	bl FUN_020B1A24
	ldr r0, [sp, #0x58]
	add r1, sp, #0x18
	bl FUN_020B0088
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021E0B50 ; =0x00300010
	add r3, r4, #4
	and r1, r0
	ldr r0, [sp, #0x18]
	str r1, [r0, #8]
	lsr r1, r2, #0x11
	ldr r0, [sp, #0x18]
	mov r2, #1
	str r1, [r0, #0x10]
	ldr r1, [sp, #0x6c]
	ldr r0, [sp, #0x18]
	lsl r1, r1, #5
	bl FUN_020B1768
	add r0, r4, #4
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x68]
	ldr r2, [sp, #0x5c]
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #0x24]
	ldr r3, [sp, #0x60]
	add r1, sp, #0x1c
	bl MOD14_021DDDD4
	str r0, [r4]
	cmp r0, #0
	bne _021E0B28
	bl ErrorHandling
_021E0B28:
	ldrh r1, [r4, #0x2c]
	ldr r0, [r4]
	add r1, r1, #2
	bl FUN_02020248
	ldr r0, [r5, #0x40]
	bl MOD14_021DC484
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021E0B54
	ldr r1, [sp, #0x14]
	add r0, r6, #0
	bl FUN_02066A94
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E0B50: .word 0x00300010

	thumb_func_start MOD14_021E0B54
MOD14_021E0B54: ; 0x021E0B54
	push {r4, r5, r6, lr}
	cmp r2, #0
	beq _021E0B9A
	mov r3, #1
	add r0, r2, #0
	tst r0, r3
	beq _021E0B72
	ldrh r0, [r1, #0x30]
	cmp r0, #0
	bne _021E0B72
	ldr r0, [r1]
	add r1, r3, #0
	bl FUN_02020398
	pop {r4, r5, r6, pc}
_021E0B72:
	mov r3, #0
	mov r4, #1
	mov r0, #2
_021E0B78:
	add r5, r0, #0
	lsl r5, r3
	tst r5, r2
	beq _021E0B94
	add r5, r4, #0
	ldrh r6, [r1, #0x2e]
	lsl r5, r3
	tst r5, r6
	bne _021E0B94
	ldr r0, [r1]
	add r1, r4, #0
	bl FUN_02020398
	pop {r4, r5, r6, pc}
_021E0B94:
	add r3, r3, #1
	cmp r3, #6
	blt _021E0B78
_021E0B9A:
	ldr r0, [r1]
	mov r1, #0
	bl FUN_02020398
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021E0BA4
MOD14_021E0BA4: ; 0x021E0BA4
	strh r2, [r1, #0x2e]
	bx lr

	thumb_func_start MOD14_021E0BA8
MOD14_021E0BA8: ; 0x021E0BA8
	strh r2, [r1, #0x30]
	bx lr

	thumb_func_start MOD14_021E0BAC
MOD14_021E0BAC: ; 0x021E0BAC
	push {r3, lr}
	str r1, [sp]
	ldr r0, [r0, #0x48]
	add r1, r2, #0
	mov r2, #0
	bl FUN_02006814
	pop {r3, pc}

	thumb_func_start MOD14_021E0BBC
MOD14_021E0BBC: ; 0x021E0BBC
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	add r6, r2, #0
	cmp r0, #0
	beq _021E0C18
	add r0, r4, #4
	bl FUN_020B1A24
	add r0, r5, #0
	add r0, #0x4c
	str r0, [sp]
	mov r3, #0xa
	ldr r0, [r5, #0x48]
	ldr r1, [r4, #0x28]
	mov r2, #0
	lsl r3, r3, #6
	bl FUN_02006814
	add r5, #0x4c
	add r0, r5, #0
	add r1, sp, #4
	bl FUN_020B0088
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021E0C1C ; =0x00300010
	add r3, r4, #4
	and r1, r0
	ldr r0, [sp, #4]
	str r1, [r0, #8]
	lsr r1, r2, #0x11
	ldr r0, [sp, #4]
	mov r2, #1
	str r1, [r0, #0x10]
	ldr r0, [sp, #4]
	lsl r1, r6, #5
	bl FUN_020B1768
	ldr r0, [r4]
	add r1, r4, #4
	bl FUN_02020334
_021E0C18:
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_021E0C1C: .word 0x00300010

	thumb_func_start MOD14_021E0C20
MOD14_021E0C20: ; 0x021E0C20
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r1, #0
	sub r0, r4, #1
	cmp r0, #1
	ldr r0, [r5]
	bhi _021E0C36
	mov r1, #1
	bl FUN_020200EC
	b _021E0C3C
_021E0C36:
	mov r1, #0
	bl FUN_020200EC
_021E0C3C:
	ldr r0, [r5]
	add r1, r4, #0
	bl FUN_02020130
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E0C48
MOD14_021E0C48: ; 0x021E0C48
	push {r3, lr}
	ldr r0, [r1]
	bl FUN_02020388
	cmp r0, #0
	bne _021E0C58
	mov r0, #1
	pop {r3, pc}
_021E0C58:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD14_021E0C5C
MOD14_021E0C5C: ; 0x021E0C5C
	cmp r2, #0
	beq _021E0C64
	mov r2, #6
	b _021E0C66
_021E0C64:
	mov r2, #2
_021E0C66:
	ldr r0, [r1]
	ldrh r1, [r1, #0x2c]
	ldr r3, _021E0C70 ; =0x02020249
	add r1, r1, r2
	bx r3
	.align 2, 0
_021E0C70: .word 0x02020249

	thumb_func_start MOD14_021E0C74
MOD14_021E0C74: ; 0x021E0C74
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start MOD14_021E0C78
MOD14_021E0C78: ; 0x021E0C78
	ldr r0, [r0, #4]
	bx lr

	thumb_func_start MOD14_021E0C7C
MOD14_021E0C7C: ; 0x021E0C7C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	str r1, [r4, #0x44]
	str r3, [r4, #0x3c]
	str r2, [r4, #0x40]
	str r3, [r4]
	mov r0, #0
	str r0, [r4, #4]
	mov r1, #0xa
	add r3, r4, #0
	str r1, [sp]
	mov r0, #0x12
	mov r2, #1
	add r3, #0x10
	bl FUN_02006C30
	str r0, [r4, #8]
	mov r0, #0xa
	add r3, r4, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0xb
	mov r2, #1
	add r3, #0x14
	bl FUN_02006C5C
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021E0CC0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	bne _021E0CC6
_021E0CC0:
	add sp, #4
	mov r0, #0
	pop {r3, r4, pc}
_021E0CC6:
	mov r0, #1
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD14_021E0CCC
MOD14_021E0CCC: ; 0x021E0CCC
	push {r4, lr}
	sub sp, #0x38
	add r4, r0, #0
	add r0, #0x18
	bl FUN_020B1A24
	mov r3, #0
	mov r0, #0x9d
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	lsl r0, r0, #8
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x18
	str r0, [sp, #0x10]
	mov r0, #0x12
	mov r1, #9
	bl FUN_02006AE4
	ldr r0, [r4, #0x44]
	bl MOD14_021DDD48
	add r2, r0, #0
	ldr r0, [r4, #0x14]
	add r1, r4, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r3, [r4, #0x10]
	add r0, sp, #0x14
	add r1, #0x18
	bl MOD14_021DDDB4
	ldr r0, [r4, #0x44]
	bl MOD14_021DDD98
	add r2, r0, #0
	mov r0, #0x2c
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0x14
	add r2, #0xb7
	mov r3, #0xb0
	bl MOD14_021DDDD4
	mov r1, #1
	str r0, [r4, #4]
	bl FUN_02020248
	add sp, #0x38
	pop {r4, pc}

	thumb_func_start MOD14_021E0D3C
MOD14_021E0D3C: ; 0x021E0D3C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021E0D4E
	bl FUN_02016A18
	mov r0, #0
	str r0, [r4, #8]
_021E0D4E:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021E0D5C
	bl FUN_02016A18
	mov r0, #0
	str r0, [r4, #0xc]
_021E0D5C:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E0D60
MOD14_021E0D60: ; 0x021E0D60
	push {r3, lr}
	cmp r1, #0
	beq _021E0D70
	cmp r1, #1
	beq _021E0D7A
	cmp r1, #2
	beq _021E0D84
	pop {r3, pc}
_021E0D70:
	ldr r0, [r0, #4]
	mov r1, #0
	bl FUN_02020130
	pop {r3, pc}
_021E0D7A:
	ldr r0, [r0, #4]
	mov r1, #1
	bl FUN_02020130
	pop {r3, pc}
_021E0D84:
	ldr r0, [r0, #4]
	mov r1, #2
	bl FUN_02020130
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD14_021E0D90
MOD14_021E0D90: ; 0x021E0D90
	push {r3, r4, r5, r6, r7, lr}
	add r6, r2, #0
	add r5, r0, #0
	add r0, r6, #0
	add r4, r1, #0
	add r7, r3, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	bne _021E0DAC
	mov r0, #0
	str r0, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E0DAC:
	str r4, [r5, #0x14]
	str r7, [r5, #8]
	ldr r0, [sp, #0x18]
	str r6, [r5, #0x10]
	str r0, [r5, #0xc]
	mov r0, #0
	str r0, [r5, #4]
	str r0, [r5, #0x4c]
	str r0, [r5, #0x24]
	add r0, r4, #0
	bl MOD14_021DDD90
	str r0, [r5, #0x20]
	mov r0, #9
	mov r1, #6
	mov r2, #0xf
	mov r3, #0xa
	bl FUN_0200B870
	str r0, [r5, #0x18]
	mov r0, #1
	mov r1, #2
	mov r2, #0xf
	mov r3, #0xa
	bl FUN_0200B870
	str r0, [r5, #0x1c]
	mov r0, #0xa
	add r3, r5, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x10
	mov r2, #1
	add r3, #0x2c
	bl FUN_02006C30
	str r0, [r5, #0x28]
	mov r0, #0
	str r0, [r5, #0x30]
	ldr r0, [sp, #0x1c]
	mov r1, #0x15
	bl FUN_0200A914
	str r0, [r5, #0x44]
	ldr r0, [sp, #0x1c]
	mov r1, #0x16
	bl FUN_0200A914
	str r0, [r5, #0x48]
	bl FUN_0206E12C
	add r4, r0, #0
	bl FUN_0206E10C
	add r1, r0, #0
	mov r0, #0xa
	add r3, r5, #0
	str r0, [sp]
	add r0, r4, #0
	mov r2, #1
	add r3, #0x38
	bl FUN_02006C30
	mov r1, #0
	str r0, [r5, #0x34]
	add r2, r5, #0
	add r0, r1, #0
_021E0E32:
	add r1, r1, #1
	str r0, [r2, #0x3c]
	add r2, r2, #4
	cmp r1, #2
	blt _021E0E32
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021E0E44
MOD14_021E0E44: ; 0x021E0E44
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _021E0EE2
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _021E0E72
	mov r6, #0
	add r4, r6, #0
_021E0E58:
	ldr r0, [r5, #4]
	add r0, r0, r4
	bl FUN_02019178
	add r6, r6, #1
	add r4, #0x10
	cmp r6, #4
	blt _021E0E58
	ldr r0, [r5, #4]
	bl FUN_02016A18
	mov r0, #0
	str r0, [r5, #4]
_021E0E72:
	ldr r0, [r5, #0x18]
	cmp r0, #0
	beq _021E0E7C
	bl FUN_0200B990
_021E0E7C:
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _021E0E86
	bl FUN_0200B990
_021E0E86:
	ldr r0, [r5, #0x44]
	cmp r0, #0
	beq _021E0E90
	bl FUN_02021A20
_021E0E90:
	ldr r0, [r5, #0x48]
	cmp r0, #0
	beq _021E0E9A
	bl FUN_02021A20
_021E0E9A:
	ldr r0, [r5, #0x24]
	cmp r0, #0
	beq _021E0EA8
	bl FUN_02007534
	mov r0, #0
	str r0, [r5, #0x24]
_021E0EA8:
	ldr r0, [r5, #0x28]
	cmp r0, #0
	beq _021E0EB2
	bl FUN_02016A18
_021E0EB2:
	ldr r0, [r5, #0x30]
	cmp r0, #0
	beq _021E0EBC
	bl FUN_0201FFC8
_021E0EBC:
	ldr r0, [r5, #0x34]
	cmp r0, #0
	beq _021E0EC6
	bl FUN_02016A18
_021E0EC6:
	mov r6, #0
	add r4, r5, #0
_021E0ECA:
	ldr r0, [r4, #0x3c]
	cmp r0, #0
	beq _021E0ED4
	bl FUN_0201FFC8
_021E0ED4:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #2
	blt _021E0ECA
	add r0, r5, #0
	bl MOD14_021E10F4
_021E0EE2:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021E0EE4
MOD14_021E0EE4: ; 0x021E0EE4
	push {r3, lr}
	ldr r1, [r0]
	cmp r1, #0
	beq _021E0EF2
	ldr r0, [r0, #0x20]
	bl FUN_020081C4
_021E0EF2:
	pop {r3, pc}

	thumb_func_start MOD14_021E0EF4
MOD14_021E0EF4: ; 0x021E0EF4
	push {r4, lr}
	sub sp, #0x20
	mov r2, #0
	str r2, [sp]
	add r4, r0, #0
	str r2, [sp, #4]
	add r0, sp, #0x10
	mov r1, #1
	add r3, r2, #0
	str r2, [sp, #8]
	bl FUN_02068C00
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x20]
	add r1, sp, #0x10
	mov r2, #0x2c
	mov r3, #0x54
	bl FUN_020073A0
	str r0, [r4, #0x24]
	add sp, #0x20
	pop {r4, pc}

	thumb_func_start MOD14_021E0F28
MOD14_021E0F28: ; 0x021E0F28
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _021E0F3C
	bl FUN_02007534
	mov r0, #0
	str r0, [r4, #0x24]
	pop {r4, pc}
_021E0F3C:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD14_021E0F40
MOD14_021E0F40: ; 0x021E0F40
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _021E0FA0
	mov r0, #0xa
	mov r1, #4
	bl FUN_02018FF4
	str r0, [r5, #4]
	cmp r0, #0
	beq _021E0F94
	mov r7, #0
	ldr r6, _021E0FA4 ; =0x021E65F4
	add r4, r7, #0
_021E0F5E:
	ldr r1, [r5, #4]
	ldr r0, [r5, #8]
	add r1, r1, r4
	add r2, r6, #0
	bl FUN_02019150
	cmp r7, #3
	ldr r0, [r5, #4]
	beq _021E0F78
	add r0, r0, r4
	bl FUN_02019270
	b _021E0F82
_021E0F78:
	add r0, r0, r4
	mov r1, #0xc
	mov r2, #2
	bl FUN_0201928C
_021E0F82:
	add r7, r7, #1
	add r6, #8
	add r4, #0x10
	cmp r7, #4
	blt _021E0F5E
	ldr r0, [r5, #8]
	mov r1, #2
	bl FUN_02017CD0
_021E0F94:
	add r0, r5, #0
	bl MOD14_021E0FA8
	add r0, r5, #0
	bl MOD14_021E10B0
_021E0FA0:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E0FA4: .word 0x021E65F4

	thumb_func_start MOD14_021E0FA8
MOD14_021E0FA8: ; 0x021E0FA8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x68
	add r5, r0, #0
	bl FUN_0206E12C
	str r0, [sp, #0x1c]
	mov r0, #2
	bl FUN_0206E0F0
	str r0, [sp, #0x18]
	bl FUN_0206E108
	add r1, r0, #0
	mov r0, #0x60
	str r0, [sp]
	mov r3, #0xa
	str r3, [sp, #4]
	ldr r0, [sp, #0x1c]
	mov r2, #1
	lsl r3, r3, #5
	bl FUN_02006930
	mov r0, #0
	mov r6, #0x5e
	str r0, [sp, #0x14]
	lsl r6, r6, #4
	mov r7, #0x18
	add r4, r5, #0
_021E0FE0:
	add r0, sp, #0x44
	bl FUN_020B1A24
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	lsl r0, r6, #5
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	add r0, sp, #0x44
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	mov r2, #1
	mov r3, #0
	bl FUN_02006B38
	ldr r0, [r5, #0x14]
	bl MOD14_021DDD48
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	ldr r3, [r5, #0x38]
	add r0, sp, #0x20
	add r1, sp, #0x44
	bl MOD14_021DDDB4
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #0xc]
	add r1, sp, #0x20
	add r2, r7, #0
	mov r3, #0xb0
	bl MOD14_021DDDD4
	str r0, [r4, #0x3c]
	cmp r0, #0
	bne _021E103E
	bl ErrorHandling
_021E103E:
	ldr r0, [r4, #0x3c]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [sp, #0x14]
	add r6, #8
	add r0, r0, #1
	add r7, #0x24
	add r4, r4, #4
	str r0, [sp, #0x14]
	cmp r0, #2
	blo _021E0FE0
	add r0, sp, #0x44
	bl FUN_020B1A24
	mov r3, #0
	mov r0, #0xb9
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	lsl r0, r0, #8
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	add r0, sp, #0x44
	str r0, [sp, #0x10]
	mov r0, #0x12
	mov r1, #0xf
	bl FUN_02006AE4
	ldr r0, [r5, #0x14]
	bl MOD14_021DDD48
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	ldr r3, [r5, #0x2c]
	add r0, sp, #0x20
	add r1, sp, #0x44
	bl MOD14_021DDDB4
	mov r0, #0x2f
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #0xc]
	add r1, sp, #0x20
	mov r2, #0x38
	mov r3, #0xb0
	bl MOD14_021DDDD4
	str r0, [r5, #0x30]
	add sp, #0x68
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021E10B0
MOD14_021E10B0: ; 0x021E10B0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x4c]
	cmp r0, #0
	bne _021E10EE
	mov r0, #0xa
	mov r1, #0xc
	bl FUN_02016998
	add r4, r0, #0
	beq _021E10EA
	ldr r0, [r5, #0x10]
	bl MOD14_021DC42C
	ldrb r0, [r0, #0xf]
	cmp r0, #0
	beq _021E10D6
	mov r0, #4
	b _021E10D8
_021E10D6:
	mov r0, #0
_021E10D8:
	strh r0, [r4]
	ldr r0, _021E10F0 ; =MOD14_021E115C
	str r5, [r4, #8]
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA44
	str r0, [r5, #0x4c]
	pop {r3, r4, r5, pc}
_021E10EA:
	bl ErrorHandling
_021E10EE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E10F0: .word MOD14_021E115C

	thumb_func_start MOD14_021E10F4
MOD14_021E10F4: ; 0x021E10F4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x4c]
	cmp r0, #0
	beq _021E1110
	bl FUN_0201B6C8
	bl FUN_02016A18
	ldr r0, [r4, #0x4c]
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x4c]
_021E1110:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E1114
MOD14_021E1114: ; 0x021E1114
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x4c]
	bl FUN_0201B6C8
	add r4, r0, #0
	beq _021E113C
	ldr r0, [r5, #0x10]
	bl MOD14_021DC42C
	ldrb r0, [r0, #0xf]
	cmp r0, #0
	beq _021E1132
	mov r0, #4
	b _021E1134
_021E1132:
	mov r0, #0
_021E1134:
	strh r0, [r4]
	add r0, r5, #0
	bl MOD14_021E1268
_021E113C:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E1140
MOD14_021E1140: ; 0x021E1140
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x4c]
	bl FUN_0201B6C8
	cmp r0, #0
	beq _021E1158
	mov r1, #4
	strh r1, [r0]
	add r0, r4, #0
	bl MOD14_021E1268
_021E1158:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E115C
MOD14_021E115C: ; 0x021E115C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrh r0, [r4]
	ldr r5, [r4, #8]
	cmp r0, #4
	bhi _021E1220
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E1174: ; jump table
	.short _021E117E - _021E1174 - 2 ; case 0
	.short _021E1190 - _021E1174 - 2 ; case 1
	.short _021E11B0 - _021E1174 - 2 ; case 2
	.short _021E11CE - _021E1174 - 2 ; case 3
	.short _021E1220 - _021E1174 - 2 ; case 4
_021E117E:
	ldr r0, [r5, #0x10]
	bl MOD14_021DC408
	cmp r0, #0
	beq _021E1220
	mov r0, #0
	strh r0, [r4, #2]
	mov r0, #1
	strh r0, [r4]
_021E1190:
	ldr r0, [r5, #4]
	ldrh r2, [r4, #2]
	add r0, #0x30
	add r1, r5, #0
	mov r3, #0
	bl MOD14_021E12B8
	ldr r0, [r5, #4]
	add r0, #0x30
	bl FUN_02019548
	mov r0, #0
	strh r0, [r4, #4]
	mov r0, #2
	strh r0, [r4]
	pop {r3, r4, r5, pc}
_021E11B0:
	ldrh r0, [r4, #4]
	add r0, r0, #1
	strh r0, [r4, #4]
	ldrh r0, [r4, #4]
	cmp r0, #0x50
	bls _021E1220
	add r0, r4, #0
	bl MOD14_021E1284
	mov r0, #0
	strh r0, [r4, #4]
	strh r0, [r4, #6]
	mov r0, #3
	strh r0, [r4]
	pop {r3, r4, r5, pc}
_021E11CE:
	ldrh r0, [r4, #6]
	mov r1, #1
	lsl r1, r1, #0xe
	add r0, r0, #4
	strh r0, [r4, #6]
	add r0, r5, #0
	bl MOD14_021E1224
	ldr r0, [r5, #4]
	mov r1, #0
	add r0, #0x30
	mov r2, #4
	add r3, r1, #0
	bl FUN_0201A8C8
	ldr r0, [r5, #4]
	add r0, #0x30
	bl FUN_02019548
	ldrh r0, [r4, #6]
	cmp r0, #0x10
	blo _021E1220
	ldrh r0, [r4, #2]
	cmp r0, #1
	bne _021E1206
	add r0, r5, #0
	bl MOD14_021E1268
_021E1206:
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	ldrh r0, [r4, #2]
	cmp r0, #4
	blo _021E1216
	mov r0, #0
	strh r0, [r4, #2]
_021E1216:
	mov r0, #0
	strh r0, [r4, #6]
	strh r0, [r4, #4]
	mov r0, #2
	strh r0, [r4]
_021E1220:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E1224
MOD14_021E1224: ; 0x021E1224
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r7, r1, #0
	mov r4, #0
_021E122E:
	ldr r0, [r5, #0x3c]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [sp, #4]
	sub r0, r0, r7
	str r0, [sp, #4]
	ldr r0, [r5, #0x3c]
	bl FUN_02020044
	cmp r4, #0
	bne _021E125A
	ldr r0, [r5, #0x3c]
	bl FUN_02020128
_021E125A:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _021E122E
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021E1268
MOD14_021E1268: ; 0x021E1268
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_021E1270:
	ldr r0, [r5, #0x3c]
	add r1, r6, #0
	bl FUN_020200A0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _021E1270
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E1284
MOD14_021E1284: ; 0x021E1284
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	mov r1, #0
	ldr r4, [r0, #4]
	add r4, #0x30
	add r0, r4, #0
	bl FUN_02019620
	ldrh r2, [r5, #2]
	ldr r1, [r5, #8]
	add r0, r4, #0
	mov r3, #0
	bl MOD14_021E12B8
	ldrh r0, [r5, #2]
	add r2, r0, #1
	cmp r2, #4
	blo _021E12AC
	mov r2, #0
_021E12AC:
	ldr r1, [r5, #8]
	add r0, r4, #0
	mov r3, #1
	bl MOD14_021E12B8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021E12B8
MOD14_021E12B8: ; 0x021E12B8
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r4, r1, #0
	lsl r5, r3, #4
	cmp r2, #3
	bls _021E12C6
	b _021E13E6
_021E12C6:
	add r1, r2, r2
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E12D2: ; jump table
	.short _021E12DA - _021E12D2 - 2 ; case 0
	.short _021E12EC - _021E12D2 - 2 ; case 1
	.short _021E12E0 - _021E12D2 - 2 ; case 2
	.short _021E12E6 - _021E12D2 - 2 ; case 3
_021E12DA:
	ldr r1, [r4, #0x10]
	ldr r2, [r1, #0x68]
	b _021E13D2
_021E12E0:
	ldr r1, [r4, #0x10]
	ldr r2, [r1, #0x6c]
	b _021E13D2
_021E12E6:
	ldr r1, [r4, #0x10]
	ldr r2, [r1, #0x70]
	b _021E13D2
_021E12EC:
	bl FUN_0206E12C
	ldr r0, [r4, #0x10]
	add r0, #0x58
	ldrb r0, [r0]
	bl FUN_0206E0F0
	bl FUN_0206E12C
	add r6, r0, #0
	ldr r0, [r4, #0x10]
	add r0, #0x58
	ldrb r0, [r0]
	bl FUN_0206E0F0
	mov r2, #0
	add r1, r0, #0
	mov r3, #0x2f
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	add r0, r6, #0
	lsl r3, r3, #0xa
	bl FUN_02006A34
	ldr r0, [r4, #0x3c]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0x10
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r5, #0xb0
	str r0, [r3]
	lsl r0, r5, #0xc
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x3c]
	add r1, r2, #0
	bl FUN_02020044
	ldr r0, [r4, #0x10]
	add r0, #0x58
	ldrb r0, [r0]
	bl FUN_0206E114
	add r1, r0, #0
	ldr r0, [r4, #0x3c]
	add r1, #0xa
	bl FUN_02020248
	ldr r0, [r4, #0x3c]
	mov r1, #1
	bl FUN_020200A0
	ldr r1, [r4, #0x10]
	add r0, r1, #0
	add r0, #0x59
	add r1, #0x58
	ldrb r5, [r0]
	ldrb r0, [r1]
	cmp r0, r5
	beq _021E13C6
	bl FUN_0206E12C
	add r6, r0, #0
	add r0, r5, #0
	bl FUN_0206E0F0
	mov r2, #0
	add r1, r0, #0
	mov r3, #0xbd
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	add r0, r6, #0
	lsl r3, r3, #8
	bl FUN_02006A34
	mov r0, #9
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x40]
	add r1, sp, #0x10
	bl FUN_02020044
	ldr r0, [r4, #0x10]
	add r0, #0x59
	ldrb r0, [r0]
	bl FUN_0206E114
	add r1, r0, #0
	ldr r0, [r4, #0x40]
	add r1, #0xa
	bl FUN_02020248
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl FUN_020200A0
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
_021E13C6:
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
_021E13D2:
	str r5, [sp]
	mov r1, #0xff
	str r1, [sp, #4]
	ldr r1, _021E13EC ; =0x00090600
	str r1, [sp, #8]
	mov r1, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
_021E13E6:
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	nop
_021E13EC: .word 0x00090600

	thumb_func_start MOD14_021E13F0
MOD14_021E13F0: ; 0x021E13F0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021E144E
	ldr r0, [r4, #4]
	mov r1, #0xf
	bl FUN_02019620
	ldr r0, [r4, #4]
	mov r1, #0xf
	add r0, #0x10
	bl FUN_02019620
	ldr r0, [r4, #4]
	mov r1, #0xf
	add r0, #0x20
	bl FUN_02019620
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, #0x30
	bl FUN_02019620
	ldr r0, [r4, #0x10]
	bl MOD14_021DC408
	cmp r0, #0
	beq _021E1430
	add r0, r4, #0
	bl MOD14_021E153C
_021E1430:
	ldr r0, [r4, #4]
	bl FUN_02019548
	ldr r0, [r4, #4]
	add r0, #0x10
	bl FUN_02019548
	ldr r0, [r4, #4]
	add r0, #0x20
	bl FUN_02019548
	ldr r0, [r4, #4]
	add r0, #0x30
	bl FUN_02019548
_021E144E:
	pop {r4, pc}

	thumb_func_start MOD14_021E1450
MOD14_021E1450: ; 0x021E1450
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021E14CC
	ldr r0, [r4, #4]
	mov r1, #0xf
	bl FUN_02019620
	ldr r0, [r4, #4]
	mov r1, #0xf
	add r0, #0x10
	bl FUN_02019620
	ldr r0, [r4, #4]
	mov r1, #0xf
	add r0, #0x20
	bl FUN_02019620
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, #0x30
	bl FUN_02019620
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _021E148E
	bl FUN_02007534
	mov r0, #0
	str r0, [r4, #0x24]
_021E148E:
	ldr r0, [r4, #0x10]
	bl MOD14_021DC408
	cmp r0, #0
	beq _021E14A0
	add r0, r4, #0
	bl MOD14_021E153C
	b _021E14A8
_021E14A0:
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021E16A0
_021E14A8:
	ldr r0, [r4, #4]
	bl FUN_02019548
	ldr r0, [r4, #4]
	add r0, #0x10
	bl FUN_02019548
	ldr r0, [r4, #4]
	add r0, #0x20
	bl FUN_02019548
	ldr r0, [r4, #4]
	add r0, #0x30
	bl FUN_02019548
	add r0, r4, #0
	bl MOD14_021E1114
_021E14CC:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E14D0
MOD14_021E14D0: ; 0x021E14D0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021E153A
	ldr r0, [r4, #4]
	mov r1, #0xf
	bl FUN_02019620
	ldr r0, [r4, #4]
	mov r1, #0xf
	add r0, #0x10
	bl FUN_02019620
	ldr r0, [r4, #4]
	mov r1, #0xf
	add r0, #0x20
	bl FUN_02019620
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, #0x30
	bl FUN_02019620
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _021E150E
	bl FUN_02007534
	mov r0, #0
	str r0, [r4, #0x24]
_021E150E:
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021E16A0
	ldr r0, [r4, #4]
	bl FUN_02019548
	ldr r0, [r4, #4]
	add r0, #0x10
	bl FUN_02019548
	ldr r0, [r4, #4]
	add r0, #0x20
	bl FUN_02019548
	ldr r0, [r4, #4]
	add r0, #0x30
	bl FUN_02019548
	add r0, r4, #0
	bl MOD14_021E1140
_021E153A:
	pop {r4, pc}

	thumb_func_start MOD14_021E153C
MOD14_021E153C: ; 0x021E153C
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	bl MOD14_021DC42C
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E1660 ; =0x0009060F
	mov r3, #2
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #4]
	ldr r2, [r4, #0x18]
	bl FUN_0201BDE0
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E1664 ; =0x0001020F
	mov r3, #2
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #4]
	ldr r2, [r4, #0x14]
	add r0, #0x20
	bl FUN_0201BDE0
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E1664 ; =0x0001020F
	mov r3, #2
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #4]
	ldr r2, [r4, #0x14]
	add r0, #0x20
	bl FUN_0201BDE0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _021E15A2
	cmp r0, #1
	beq _021E15BE
	b _021E15D8
_021E15A2:
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E1668 ; =0x0007080F
	mov r3, #0x46
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #4]
	ldr r2, [r5, #0x44]
	add r0, #0x20
	bl FUN_0201BDE0
	b _021E15D8
_021E15BE:
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E166C ; =0x0003040F
	mov r3, #0x46
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #4]
	ldr r2, [r5, #0x48]
	add r0, #0x20
	bl FUN_0201BDE0
_021E15D8:
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	bne _021E1632
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E1670 ; =0x00090600
	add r3, r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #4]
	ldr r2, [r4, #0x1c]
	add r0, #0x30
	bl FUN_0201BDE0
	ldrh r2, [r4, #8]
	cmp r2, #0
	beq _021E1616
	mov r1, #2
	str r1, [sp]
	ldr r0, [r5, #4]
	mov r3, #3
	add r0, #0x10
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x18]
	bl FUN_0200BA78
_021E1616:
	mov r1, #1
	str r1, [sp]
	ldr r0, [r5, #4]
	mov r3, #3
	add r0, #0x20
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldrb r2, [r4, #0xa]
	ldr r0, [r5, #0x1c]
	bl FUN_0200BA78
_021E1632:
	ldr r1, [r4]
	add r0, sp, #0x10
	mov r2, #2
	bl FUN_02068B70
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x20]
	add r1, sp, #0x10
	mov r2, #0x2c
	mov r3, #0x54
	bl FUN_020073A0
	str r0, [r5, #0x24]
	ldrb r1, [r4, #0xb]
	add r0, r5, #0
	bl MOD14_021E16A0
	add sp, #0x20
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E1660: .word 0x0009060F
_021E1664: .word 0x0001020F
_021E1668: .word 0x0007080F
_021E166C: .word 0x0003040F
_021E1670: .word 0x00090600

	thumb_func_start MOD14_021E1674
MOD14_021E1674: ; 0x021E1674
	mov r0, #1
	bx lr

	thumb_func_start MOD14_021E1678
MOD14_021E1678: ; 0x021E1678
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021E169C
	ldr r0, [r4, #0x10]
	bl MOD14_021DC408
	cmp r0, #0
	beq _021E169C
	ldr r0, [r4, #0x10]
	bl MOD14_021DC42C
	add r1, r0, #0
	ldrb r1, [r1, #0xb]
	add r0, r4, #0
	bl MOD14_021E16A0
_021E169C:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E16A0
MOD14_021E16A0: ; 0x021E16A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp, #4]
	add r4, r1, #0
	ldr r0, [r0, #8]
	mov r1, #2
	bl FUN_0201886C
	mov ip, r0
	add r2, r0, #0
	mov r0, #1
	ldr r6, _021E1700 ; =0x000004C8
	mov r1, #0
	lsl r7, r0, #0xd
_021E16BC:
	add r3, r0, #0
	lsl r3, r1
	tst r3, r4
	beq _021E16CE
	add r3, r1, #0
	add r3, #0x98
	orr r3, r7
	strh r3, [r2, r6]
	b _021E16DC
_021E16CE:
	add r5, r1, #0
	mov r3, #2
	add r5, #0x84
	lsl r3, r3, #0xc
	orr r5, r3
	ldr r3, _021E1700 ; =0x000004C8
	strh r5, [r2, r3]
_021E16DC:
	add r1, r1, #1
	add r2, r2, #2
	cmp r1, #6
	blt _021E16BC
	mov r2, #0x99
	lsl r2, r2, #2
	ldr r0, [sp, #4]
	str r2, [sp]
	lsl r3, r2, #1
	mov r2, ip
	add r2, r2, r3
	ldr r0, [r0, #8]
	mov r1, #2
	mov r3, #0xc
	bl FUN_02017CE8
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E1700: .word 0x000004C8

	thumb_func_start MOD14_021E1704
MOD14_021E1704: ; 0x021E1704
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _021E1748
	ldr r0, [r5, #0x10]
	bl MOD14_021DC42C
	add r4, r0, #0
	ldr r0, [r5, #4]
	mov r1, #0
	add r0, #0x30
	bl FUN_02019620
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	bne _021E1742
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E174C ; =0x00090600
	add r3, r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #4]
	ldr r2, [r4, #0x1c]
	add r0, #0x30
	bl FUN_0201BDE0
_021E1742:
	add r0, r5, #0
	bl MOD14_021E1114
_021E1748:
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E174C: .word 0x00090600

	thumb_func_start MOD14_021E1750
MOD14_021E1750: ; 0x021E1750
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	str r1, [r4, #0xc]
	str r3, [r4]
	str r2, [r4, #8]
	ldr r0, [sp, #0x18]
	mov r1, #0x1a
	str r0, [r4, #0x2c]
	ldr r0, [sp, #0x1c]
	mov r2, #0xe
	str r0, [r4, #0x20]
	ldr r0, [sp, #0x14]
	mov r3, #0xa
	str r0, [r4, #0x10]
	mov r0, #0
	bl FUN_0200A86C
	str r0, [r4, #0x14]
	mov r0, #0x40
	mov r1, #0xa
	bl FUN_020219F4
	str r0, [r4, #0x30]
	mov r0, #0x40
	mov r1, #0xa
	bl FUN_020219F4
	str r0, [r4, #0x34]
	mov r0, #0
	strh r0, [r4, #0x1c]
	strh r0, [r4, #0x1e]
	str r0, [r4, #0x18]
	mov r0, #0xa
	add r3, r4, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x19
	mov r2, #1
	add r3, #0x28
	bl FUN_02006BB0
	str r0, [r4, #0x24]
	cmp r0, #0
	beq _021E17B6
	ldr r0, [r4, #0x30]
	cmp r0, #0
	beq _021E17B6
	ldr r0, [r4, #0x34]
	cmp r0, #0
	bne _021E17BC
_021E17B6:
	add sp, #4
	mov r0, #0
	pop {r3, r4, pc}
_021E17BC:
	mov r0, #1
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E17C4
MOD14_021E17C4: ; 0x021E17C4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	cmp r0, #0
	beq _021E1814
	mov r6, #0
	add r4, r6, #0
_021E17D2:
	ldr r0, [r5, #0x18]
	add r0, r0, r4
	bl FUN_02019178
	add r6, r6, #1
	add r4, #0x10
	cmp r6, #2
	blt _021E17D2
	ldr r0, [r5, #0x24]
	cmp r0, #0
	beq _021E17EC
	bl FUN_02016A18
_021E17EC:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _021E17F6
	bl FUN_0200A8B8
_021E17F6:
	ldr r0, [r5, #0x30]
	cmp r0, #0
	beq _021E1800
	bl FUN_02021A20
_021E1800:
	ldr r0, [r5, #0x34]
	cmp r0, #0
	beq _021E180A
	bl FUN_02021A20
_021E180A:
	ldr r0, [r5, #0x18]
	bl FUN_02016A18
	mov r0, #0
	str r0, [r5, #0x18]
_021E1814:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E1818
MOD14_021E1818: ; 0x021E1818
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r0, #0
	mov r0, #0xa
	mov r1, #2
	bl FUN_02018FF4
	str r0, [r6, #0x18]
	cmp r0, #0
	beq _021E1848
	mov r7, #0
	ldr r4, _021E1894 ; =0x021E6614
	add r5, r7, #0
_021E1832:
	ldr r1, [r6, #0x18]
	ldr r0, [r6]
	add r1, r1, r5
	add r2, r4, #0
	bl FUN_02019150
	add r7, r7, #1
	add r4, #8
	add r5, #0x10
	cmp r7, #2
	blt _021E1832
_021E1848:
	mov r0, #2
	lsl r0, r0, #8
	str r0, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	ldr r2, [r6]
	mov r0, #0x26
	mov r3, #1
	bl FUN_0200687C
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0x26
	mov r1, #0x18
	mov r2, #0
	mov r3, #0xe0
	bl FUN_02006930
	ldr r0, [r6, #0x20]
	ldr r2, _021E1898 ; =0x00000209
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	ldr r0, [r6]
	mov r1, #1
	mov r3, #8
	bl FUN_0200CD68
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E1894: .word 0x021E6614
_021E1898: .word 0x00000209

	thumb_func_start MOD14_021E189C
MOD14_021E189C: ; 0x021E189C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	add r4, r1, #0
	bl FUN_02019270
	ldr r3, [r5, #0x18]
	ldrb r0, [r3, #7]
	str r0, [sp]
	ldrb r0, [r3, #8]
	str r0, [sp, #4]
	ldrb r1, [r3, #4]
	ldrb r2, [r3, #5]
	ldrb r3, [r3, #6]
	ldr r0, [r5]
	bl MOD14_021E1908
	ldr r0, [r5, #0x18]
	mov r1, #0xf
	bl FUN_02019620
	ldr r0, [r5, #0x10]
	ldr r2, [r5, #0x30]
	add r1, r4, #0
	bl FUN_0200A8E0
	ldr r0, [r5, #0x2c]
	ldr r1, [r5, #0x34]
	ldr r2, [r5, #0x30]
	bl FUN_0200B7B8
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r5, #0x18]
	ldr r2, [r5, #0x34]
	mov r1, #1
	bl FUN_0201BD84
	ldr r0, [r5, #0x18]
	bl FUN_02019548
	ldr r0, [r5]
	mov r1, #1
	bl FUN_02017CD0
	mov r0, #1
	strh r0, [r5, #0x1c]
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E1908
MOD14_021E1908: ; 0x021E1908
	push {r3, r4, r5, r6, r7, lr}
	lsl r1, r1, #0x18
	add r7, r3, #0
	lsr r1, r1, #0x18
	add r6, r2, #0
	ldr r4, [sp, #0x18]
	ldr r5, [sp, #0x1c]
	bl FUN_0201886C
	sub r1, r7, #1
	sub r2, r6, #2
	lsl r1, r1, #5
	add r1, r2, r1
	lsl r3, r1, #1
	ldr r2, _021E19AC ; =0x00008209
	add r1, r0, r3
	strh r2, [r0, r3]
	add r0, r2, #1
	mov r2, #0
	strh r0, [r1, #2]
	cmp r4, #0
	bls _021E1942
	ldr r0, _021E19B0 ; =0x0000820B
	add r3, r1, #0
_021E1938:
	add r2, r2, #1
	strh r0, [r3, #4]
	add r3, r3, #2
	cmp r2, r4
	blo _021E1938
_021E1942:
	lsl r0, r4, #1
	add r2, r1, r0
	ldr r3, _021E19B4 ; =0x0000820C
	mov ip, r0
	strh r3, [r2, #4]
	add r0, r3, #1
	strh r0, [r2, #6]
	add r0, r3, #2
	strh r0, [r2, #8]
	add r1, #0x40
	mov r3, #0
	cmp r5, #0
	bls _021E197E
	mov r0, ip
	add r2, r0, r1
	ldr r0, _021E19B8 ; =0x0000820F
	add r7, r0, #1
_021E1964:
	strh r0, [r1]
	strh r7, [r1, #2]
	ldr r6, _021E19BC ; =0x00008212
	add r3, r3, #1
	strh r6, [r2, #4]
	add r6, r6, #1
	strh r6, [r2, #6]
	ldr r6, _021E19C0 ; =0x00008214
	add r1, #0x40
	strh r6, [r2, #8]
	add r2, #0x40
	cmp r3, r5
	blo _021E1964
_021E197E:
	ldr r0, _021E19C4 ; =0x00008215
	mov r3, #0
	strh r0, [r1]
	add r0, r0, #1
	strh r0, [r1, #2]
	cmp r4, #0
	bls _021E199A
	ldr r0, _021E19C8 ; =0x00008217
	add r2, r1, #0
_021E1990:
	add r3, r3, #1
	strh r0, [r2, #4]
	add r2, r2, #2
	cmp r3, r4
	blo _021E1990
_021E199A:
	mov r0, ip
	ldr r2, _021E19CC ; =0x00008218
	add r1, r1, r0
	strh r2, [r1, #4]
	add r0, r2, #1
	strh r0, [r1, #6]
	add r0, r2, #2
	strh r0, [r1, #8]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E19AC: .word 0x00008209
_021E19B0: .word 0x0000820B
_021E19B4: .word 0x0000820C
_021E19B8: .word 0x0000820F
_021E19BC: .word 0x00008212
_021E19C0: .word 0x00008214
_021E19C4: .word 0x00008215
_021E19C8: .word 0x00008217
_021E19CC: .word 0x00008218

	thumb_func_start MOD14_021E19D0
MOD14_021E19D0: ; 0x021E19D0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldrh r0, [r5, #0x1e]
	str r1, [sp, #0x10]
	cmp r0, #0
	beq _021E19E8
	ldr r1, [r5, #0x18]
	ldr r0, [r5]
	add r1, #0x10
	bl MOD14_021E1CA0
_021E19E8:
	ldr r0, [r5, #0x18]
	mov r1, #0xf
	str r0, [sp, #0x14]
	add r0, #0x10
	str r0, [sp, #0x14]
	bl FUN_02019620
	ldr r0, [sp, #0x10]
	mov r6, #0
	add r0, #0x21
	ldrb r1, [r0]
	mov r0, #8
	sub r0, r0, r1
	lsl r7, r0, #4
	cmp r1, #0
	bls _021E1A5C
	ldr r4, [sp, #0x10]
_021E1A0A:
	ldr r3, [r4]
	cmp r3, #0x38
	blt _021E1A26
	cmp r3, #0x3d
	bgt _021E1A26
	ldr r2, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r2, #0x22
	ldrb r2, [r2]
	add r0, r5, #0
	sub r3, #0x38
	bl MOD14_021E1A8C
	b _021E1A4C
_021E1A26:
	add r3, #0x18
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x30]
	add r1, r3, #0
	bl FUN_0200A8E0
	str r7, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E1A88 ; =0x000B0C0F
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	ldr r2, [r5, #0x30]
	mov r3, #0xa
	bl FUN_0201BDE0
_021E1A4C:
	ldr r0, [sp, #0x10]
	add r6, r6, #1
	add r0, #0x21
	ldrb r0, [r0]
	add r7, #0x10
	add r4, r4, #4
	cmp r6, r0
	blo _021E1A0A
_021E1A5C:
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	bl MOD14_021E1B9C
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	add r1, #0x21
	str r1, [sp, #0x10]
	ldrb r1, [r1]
	bl MOD14_021E1AD8
	ldr r0, [sp, #0x14]
	bl FUN_02019548
	ldr r0, [r5]
	mov r1, #1
	bl FUN_02017CD0
	mov r0, #1
	strh r0, [r5, #0x1e]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E1A88: .word 0x000B0C0F

	thumb_func_start MOD14_021E1A8C
MOD14_021E1A8C: ; 0x021E1A8C
	push {r4, r5, lr}
	sub sp, #0x1c
	add r5, r0, #0
	mov r0, #1
	lsl r0, r3
	tst r0, r2
	beq _021E1A9E
	mov r4, #0
	b _021E1AA0
_021E1A9E:
	mov r4, #8
_021E1AA0:
	mov r0, #0x30
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #0x2c
	str r0, [sp, #8]
	lsl r0, r3, #4
	add r0, r0, #4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0xc]
	mov r0, #8
	str r0, [sp, #0x10]
	lsl r2, r3, #0x13
	str r0, [sp, #0x14]
	mov r0, #0xff
	str r0, [sp, #0x18]
	add r0, r1, #0
	ldr r1, [r5, #0x28]
	lsl r3, r4, #0x10
	ldr r1, [r1, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl FUN_02019684
	add sp, #0x1c
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E1AD8
MOD14_021E1AD8: ; 0x021E1AD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp, #8]
	add r5, r1, #0
	ldr r0, [r0]
	mov r1, #1
	bl FUN_0201886C
	mov r2, #8
	sub r2, r2, r5
	mov ip, r2
	add r0, #0xe6
	lsl r2, r2, #7
	add r2, r0, r2
	ldr r1, _021E1B40 ; =0x00000251
	mov r3, #0x18
	mov r0, ip
	mul r3, r0
	add r4, r1, r3
	mov r6, #0
	lsl r7, r5, #1
	beq _021E1B24
	mov r0, #1
	lsl r0, r0, #0xe
_021E1B08:
	mov r3, #0
	add r5, r2, #0
_021E1B0C:
	add r1, r4, #0
	orr r1, r0
	strh r1, [r5]
	add r3, r3, #1
	add r4, r4, #1
	add r5, r5, #2
	cmp r3, #0xc
	blo _021E1B0C
	add r6, r6, #1
	add r2, #0x40
	cmp r6, r7
	blo _021E1B08
_021E1B24:
	mov r0, #0xc
	str r0, [sp]
	mov r3, ip
	lsl r3, r3, #1
	ldr r0, [sp, #8]
	str r7, [sp, #4]
	ldr r0, [r0]
	mov r1, #1
	mov r2, #0x13
	add r3, r3, #3
	bl MOD14_021E1C10
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021E1B40: .word 0x00000251

	thumb_func_start MOD14_021E1B44
MOD14_021E1B44: ; 0x021E1B44
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #0x1c]
	cmp r0, #0
	beq _021E1B5A
	ldr r0, [r4]
	ldr r1, [r4, #0x18]
	bl MOD14_021E1CEC
	mov r0, #0
	strh r0, [r4, #0x1c]
_021E1B5A:
	ldrh r0, [r4, #0x1e]
	cmp r0, #0
	beq _021E1B6E
	ldr r1, [r4, #0x18]
	ldr r0, [r4]
	add r1, #0x10
	bl MOD14_021E1CA0
	mov r0, #0
	strh r0, [r4, #0x1e]
_021E1B6E:
	ldr r0, [r4]
	mov r1, #1
	bl FUN_02017CD0
	pop {r4, pc}

	thumb_func_start MOD14_021E1B78
MOD14_021E1B78: ; 0x021E1B78
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #0x1e]
	cmp r0, #0
	beq _021E1B90
	ldr r1, [r4, #0x18]
	ldr r0, [r4]
	add r1, #0x10
	bl MOD14_021E1CA0
	mov r0, #0
	strh r0, [r4, #0x1e]
_021E1B90:
	ldr r0, [r4]
	mov r1, #1
	bl FUN_02017CD0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E1B9C
MOD14_021E1B9C: ; 0x021E1B9C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r1, #0
	ldr r4, [r0, #0x18]
	add r0, r6, #0
	add r0, #0x21
	ldrb r1, [r0]
	mov r0, #8
	add r4, #0x10
	sub r0, r0, r1
	lsl r5, r0, #4
	mov r0, #0xa
	str r0, [sp]
	lsl r0, r1, #0x14
	lsr r0, r0, #0x10
	lsl r3, r5, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0xf
	mov r2, #0
	lsr r3, r3, #0x10
	bl FUN_020196F4
	add r6, #0x20
	ldrb r2, [r6]
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #4
	add r2, r5, r2
	bl FUN_02002218
	add r0, r4, #0
	bl FUN_02019548
	add sp, #8
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021E1BE4
MOD14_021E1BE4: ; 0x021E1BE4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r4, [r6, #0x18]
	add r7, r1, #0
	add r4, #0x10
	mov r5, #0
_021E1BF0:
	add r2, r7, #0
	add r2, #0x22
	ldrb r2, [r2]
	add r0, r6, #0
	add r1, r4, #0
	add r3, r5, #0
	bl MOD14_021E1A8C
	add r5, r5, #1
	cmp r5, #6
	blt _021E1BF0
	add r0, r4, #0
	bl FUN_02019548
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021E1C10
MOD14_021E1C10: ; 0x021E1C10
	push {r3, r4, r5, r6, r7, lr}
	lsl r1, r1, #0x18
	add r7, r3, #0
	lsr r1, r1, #0x18
	add r6, r2, #0
	ldr r5, [sp, #0x18]
	ldr r4, [sp, #0x1c]
	bl FUN_0201886C
	sub r1, r7, #1
	sub r2, r6, #1
	lsl r1, r1, #5
	add r1, r2, r1
	mov r2, #0x72
	lsl r3, r1, #1
	lsl r2, r2, #8
	strh r2, [r0, r3]
	add r1, r0, r3
	mov r2, #0
	cmp r5, #0
	bls _021E1C48
	ldr r0, _021E1C8C ; =0x00007201
	add r3, r1, #0
_021E1C3E:
	add r2, r2, #1
	strh r0, [r3, #2]
	add r3, r3, #2
	cmp r2, r5
	blo _021E1C3E
_021E1C48:
	lsl r0, r5, #1
	add r2, r1, r0
	ldr r3, _021E1C90 ; =0x00007202
	add r1, #0x40
	mov r7, #0
	strh r3, [r2, #2]
	cmp r4, #0
	bls _021E1C6C
	ldr r2, _021E1C94 ; =0x00007205
	add r6, r0, r1
	add r3, r3, #1
_021E1C5E:
	strh r3, [r1]
	strh r2, [r6, #2]
	add r7, r7, #1
	add r6, #0x40
	add r1, #0x40
	cmp r7, r4
	blo _021E1C5E
_021E1C6C:
	ldr r2, _021E1C98 ; =0x00007206
	mov r4, #0
	strh r2, [r1]
	cmp r5, #0
	bls _021E1C84
	add r3, r1, #0
	add r2, r2, #1
_021E1C7A:
	add r4, r4, #1
	strh r2, [r3, #2]
	add r3, r3, #2
	cmp r4, r5
	blo _021E1C7A
_021E1C84:
	ldr r2, _021E1C9C ; =0x00007208
	add r0, r1, r0
	strh r2, [r0, #2]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E1C8C: .word 0x00007201
_021E1C90: .word 0x00007202
_021E1C94: .word 0x00007205
_021E1C98: .word 0x00007206
_021E1C9C: .word 0x00007208

	thumb_func_start MOD14_021E1CA0
MOD14_021E1CA0: ; 0x021E1CA0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldrb r1, [r4, #4]
	bl FUN_0201886C
	ldrb r1, [r4, #5]
	mov r5, #0
	sub r2, r1, #1
	ldrb r1, [r4, #6]
	sub r1, r1, #1
	lsl r1, r1, #5
	add r1, r2, r1
	lsl r1, r1, #1
	add r2, r0, r1
	ldrb r0, [r4, #8]
	add r0, r0, #2
	beq _021E1CEA
	add r0, r5, #0
	add r1, r5, #0
_021E1CC6:
	ldrb r6, [r4, #7]
	add r3, r1, #0
	add r6, r6, #2
	beq _021E1CDE
	add r6, r2, #0
_021E1CD0:
	strh r0, [r6]
	ldrb r7, [r4, #7]
	add r3, r3, #1
	add r6, r6, #2
	add r7, r7, #2
	cmp r3, r7
	blo _021E1CD0
_021E1CDE:
	ldrb r3, [r4, #8]
	add r5, r5, #1
	add r2, #0x40
	add r3, r3, #2
	cmp r5, r3
	blo _021E1CC6
_021E1CEA:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E1CEC
MOD14_021E1CEC: ; 0x021E1CEC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldrb r1, [r4, #4]
	bl FUN_0201886C
	ldrb r1, [r4, #5]
	mov r5, #0
	sub r2, r1, #2
	ldrb r1, [r4, #6]
	sub r1, r1, #1
	lsl r1, r1, #5
	add r1, r2, r1
	lsl r1, r1, #1
	add r2, r0, r1
	ldrb r0, [r4, #8]
	add r0, r0, #2
	beq _021E1D36
	add r0, r5, #0
	add r1, r5, #0
_021E1D12:
	ldrb r6, [r4, #7]
	add r3, r1, #0
	add r6, r6, #5
	beq _021E1D2A
	add r6, r2, #0
_021E1D1C:
	strh r0, [r6]
	ldrb r7, [r4, #7]
	add r3, r3, #1
	add r6, r6, #2
	add r7, r7, #5
	cmp r3, r7
	blo _021E1D1C
_021E1D2A:
	ldrb r3, [r4, #8]
	add r5, r5, #1
	add r2, #0x40
	add r3, r3, #2
	cmp r5, r3
	blo _021E1D12
_021E1D36:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E1D38
MOD14_021E1D38: ; 0x021E1D38
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	str r1, [r5]
	str r3, [r5, #4]
	str r2, [r5, #0xc]
	ldr r0, [sp, #0x30]
	mov r4, #1
	str r0, [r5, #8]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	add r2, r3, #0
	str r4, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	mov r0, #0x12
	mov r1, #4
	add r3, r4, #0
	bl FUN_0200687C
	mov r0, #0x12
	mov r1, #0x1b
	add r2, sp, #0x14
	mov r3, #0xa
	bl FUN_02006C08
	add r4, r0, #0
	ldr r0, [sp, #0x14]
	add r1, r5, #0
	ldr r0, [r0, #0xc]
	add r1, #0xe4
	mov r2, #0x40
	bl MIi_CpuCopy16
	add r0, r4, #0
	bl FUN_02016A18
	mov r0, #0x12
	mov r1, #0x14
	add r2, sp, #0x14
	mov r3, #0xa
	bl FUN_02006C08
	add r4, r0, #0
	ldr r0, [sp, #0x14]
	mov r1, #0x49
	lsl r1, r1, #2
	ldr r0, [r0, #0xc]
	add r1, r5, r1
	mov r2, #0x20
	bl MIi_CpuCopy16
	add r0, r4, #0
	bl FUN_02016A18
	add r0, r5, #0
	mov r1, #0x2a
	mov r4, #1
	str r0, [sp, #0x10]
	add r0, #0xe4
	lsl r1, r1, #4
	lsl r4, r4, #0x10
	mov r7, #7
	str r0, [sp, #0x10]
	add r6, r0, r1
_021E1DBC:
	asr r0, r4, #0xc
	str r0, [sp]
	ldr r0, [sp, #0x10]
	ldr r3, _021E1ED8 ; =0x00007FFF
	add r1, r6, #0
	mov r2, #0x30
	bl MOD14_021DDE40
	ldr r0, _021E1EDC ; =0x00002492
	sub r7, r7, #1
	sub r4, r4, r0
	sub r6, #0x60
	cmp r7, #1
	bge _021E1DBC
	add r0, r5, #0
	mov r1, #3
	add r0, #0xe4
	lsl r1, r1, #8
	bl DC_FlushRange
	mov r0, #0xe1
	lsl r0, r0, #2
	mov r1, #0x1a
	add r0, r5, r0
	lsl r1, r1, #4
	mov r2, #0x60
	bl GX_LoadOBJPltt
	add r0, r5, #0
	mov r1, #0x1a
	add r0, #0xe4
	lsl r1, r1, #4
	mov r2, #0x60
	bl GXS_LoadOBJPltt
	mov r0, #0xa
	add r3, r5, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x11
	mov r2, #1
	add r3, #0x18
	bl FUN_02006BB0
	str r0, [r5, #0x14]
	mov r0, #0xa
	str r0, [sp]
	mov r0, #0x12
	add r3, r5, #0
	add r1, r0, #0
	mov r2, #1
	add r3, #0x20
	bl FUN_02006C30
	str r0, [r5, #0x1c]
	mov r0, #0xa
	add r3, r5, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #2
	mov r2, #1
	add r3, #0x38
	bl FUN_02006BDC
	str r0, [r5, #0x34]
	mov r0, #0xa
	add r3, r5, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #3
	mov r2, #1
	add r3, #0x30
	bl FUN_02006BDC
	str r0, [r5, #0x2c]
	mov r0, #2
	mov r1, #0xd
	mov r2, #4
	mov r3, #0xa
	bl FUN_0200B870
	str r0, [r5, #0x44]
	mov r0, #0x7d
	lsl r0, r0, #2
	mov r1, #0xa
	bl FUN_020219F4
	ldr r1, _021E1EE0 ; =0x00004BFC
	ldr r2, _021E1EE4 ; =0x00000157
	str r0, [r5, r1]
	mov r0, #0
	str r0, [r5, #0x10]
	ldr r0, [r5, #0x18]
	mov r1, #0x20
	ldr r0, [r0, #0x14]
	mov r3, #0xa
	str r0, [r5, #0x3c]
	add r0, r5, #0
	add r0, #0x40
	strh r1, [r0]
	add r0, r5, #0
	add r0, #0x42
	strh r1, [r0]
	mov r0, #1
	mov r1, #0x1a
	bl FUN_0200A86C
	ldr r1, _021E1EE8 ; =0x00004BF8
	add r2, r5, #0
	str r0, [r5, r1]
	mov r1, #0
	add r0, r1, #0
_021E1E9C:
	add r1, r1, #1
	str r0, [r2, #0x48]
	add r2, r2, #4
	cmp r1, #0x12
	blt _021E1E9C
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _021E1ECC
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _021E1ECC
	ldr r0, [r5, #0x2c]
	cmp r0, #0
	beq _021E1ECC
	ldr r0, [r5, #0x34]
	cmp r0, #0
	beq _021E1ECC
	ldr r0, [r5, #0x44]
	cmp r0, #0
	beq _021E1ECC
	ldr r0, _021E1EE0 ; =0x00004BFC
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _021E1ED2
_021E1ECC:
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021E1ED2:
	mov r0, #1
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E1ED8: .word 0x00007FFF
_021E1EDC: .word 0x00002492
_021E1EE0: .word 0x00004BFC
_021E1EE4: .word 0x00000157
_021E1EE8: .word 0x00004BF8

	thumb_func_start MOD14_021E1EEC
MOD14_021E1EEC: ; 0x021E1EEC
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r0, #0xa
	mov r1, #3
	bl FUN_02018FF4
	str r0, [r7, #0x10]
	cmp r0, #0
	beq _021E1F1A
	mov r6, #0
	ldr r4, _021E1F1C ; =0x021E662C
	add r5, r6, #0
_021E1F04:
	ldr r1, [r7, #0x10]
	ldr r0, [r7, #4]
	add r1, r1, r5
	add r2, r4, #0
	bl FUN_02019150
	add r6, r6, #1
	add r4, #8
	add r5, #0x10
	cmp r6, #3
	blo _021E1F04
_021E1F1A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E1F1C: .word 0x021E662C

	thumb_func_start MOD14_021E1F20
MOD14_021E1F20: ; 0x021E1F20
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _021E1F90 ; =0x00004BF8
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021E1F30
	bl FUN_0200A8B8
_021E1F30:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _021E1F3A
	bl FUN_02016A18
_021E1F3A:
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _021E1F44
	bl FUN_02016A18
_021E1F44:
	ldr r0, [r5, #0x2c]
	cmp r0, #0
	beq _021E1F4E
	bl FUN_02016A18
_021E1F4E:
	ldr r0, [r5, #0x34]
	cmp r0, #0
	beq _021E1F58
	bl FUN_02016A18
_021E1F58:
	ldr r0, [r5, #0x44]
	cmp r0, #0
	beq _021E1F62
	bl FUN_0200B990
_021E1F62:
	ldr r0, _021E1F94 ; =0x00004BFC
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021E1F6E
	bl FUN_02021A20
_021E1F6E:
	ldr r0, [r5, #0x10]
	cmp r0, #0
	beq _021E1F8E
	mov r6, #0
	add r4, r6, #0
_021E1F78:
	ldr r0, [r5, #0x10]
	add r0, r0, r4
	bl FUN_02019178
	add r6, r6, #1
	add r4, #0x10
	cmp r6, #3
	blt _021E1F78
	ldr r0, [r5, #0x10]
	bl FUN_02016A18
_021E1F8E:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021E1F90: .word 0x00004BF8
_021E1F94: .word 0x00004BFC

	thumb_func_start MOD14_021E1F98
MOD14_021E1F98: ; 0x021E1F98
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD14_021DC464
	add r1, r4, #0
	add r1, #0xe0
	str r0, [r1]
	add r0, r4, #0
	bl MOD14_021E223C
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021E247C
	pop {r4, pc}

	thumb_func_start MOD14_021E1FB8
MOD14_021E1FB8: ; 0x021E1FB8
	ldr r3, _021E1FBC ; =MOD14_021E24D8
	bx r3
	.align 2, 0
_021E1FBC: .word MOD14_021E24D8

	thumb_func_start MOD14_021E1FC0
MOD14_021E1FC0: ; 0x021E1FC0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD14_021DC464
	add r1, r4, #0
	add r1, #0xe0
	str r0, [r1]
	add r0, r4, #0
	bl MOD14_021E2360
	add r0, r4, #0
	bl MOD14_021E2394
	add r0, r4, #0
	bl MOD14_021E240C
	pop {r4, pc}

	thumb_func_start MOD14_021E1FE4
MOD14_021E1FE4: ; 0x021E1FE4
	ldr r3, _021E1FEC ; =MOD14_021E247C
	mov r1, #1
	bx r3
	nop
_021E1FEC: .word MOD14_021E247C

	thumb_func_start MOD14_021E1FF0
MOD14_021E1FF0: ; 0x021E1FF0
	ldr r3, _021E1FF4 ; =MOD14_021E24D8
	bx r3
	.align 2, 0
_021E1FF4: .word MOD14_021E24D8

	thumb_func_start MOD14_021E1FF8
MOD14_021E1FF8: ; 0x021E1FF8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	str r0, [sp, #8]
	ldr r0, [r0, #0xc]
	str r1, [sp, #0xc]
	str r2, [sp, #0x10]
	str r3, [sp, #0x14]
	bl MOD14_021DC44C
	ldr r1, [sp, #0xc]
	str r0, [sp, #0x28]
	bl FUN_0206B43C
	add r0, #0xd0
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0xc
	str r0, [sp]
	ldr r0, [sp, #8]
	str r1, [sp, #4]
	add r0, #0x3c
	mov r1, #9
	mov r2, #0xa
	mov r3, #0xe
	bl FUN_02018F4C
	mov r4, #0
	mov r0, #0xc
	str r4, [sp, #0x20]
	str r0, [sp, #0x18]
_021E2034:
	mov r0, #0
	str r0, [sp, #0x24]
	ldr r0, [sp, #8]
	mov r6, #0xa
	str r0, [sp, #0x2c]
	add r0, #0x3c
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x18]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x30]
_021E204A:
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0xc]
	add r2, r4, #0
	bl FUN_0206B5E4
	add r4, r4, #1
	add r5, r0, #0
	bl FUN_02066A6C
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1c]
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl FUN_020672BC
	add r7, r0, #0
	beq _021E20C8
	add r0, r5, #0
	mov r1, #0x4c
	mov r2, #0
	bl FUN_020672BC
	cmp r0, #0
	bne _021E209A
	add r0, r5, #0
	mov r1, #0x70
	mov r2, #0
	bl FUN_020672BC
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r0, r7, #0
	mov r2, #0x1b
	bl FUN_02068654
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	b _021E20AA
_021E209A:
	ldr r0, _021E2174 ; =0x000001EA
	cmp r7, r0
	beq _021E20A4
	mov r0, #8
	b _021E20A6
_021E20A4:
	mov r0, #1
_021E20A6:
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
_021E20AA:
	ldr r0, _021E2178 ; =0x021E6644
	ldr r2, [sp, #0x30]
	ldrb r0, [r0, r1]
	mov r3, #2
	add r0, #0xe0
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #2
	str r0, [sp]
	str r1, [sp, #4]
	lsl r1, r6, #0x10
	ldr r0, [sp, #0x2c]
	lsr r1, r1, #0x10
	bl FUN_02018F4C
_021E20C8:
	ldr r1, [sp, #0x1c]
	add r0, r5, #0
	bl FUN_02066A94
	ldr r0, [sp, #0x24]
	add r6, r6, #2
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, #6
	blo _021E204A
	ldr r0, [sp, #0x18]
	add r0, r0, #2
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	cmp r0, #5
	blo _021E2034
	ldr r0, [sp, #0x48]
	cmp r0, #0
	beq _021E2132
	ldr r0, [sp, #0x14]
	cmp r0, #1
	beq _021E20FE
	cmp r0, #2
	beq _021E2110
	b _021E211E
_021E20FE:
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r1, [r0]
	ldr r0, _021E217C ; =0x00300010
	and r1, r0
	ldr r0, [sp, #8]
	ldr r0, [r0, #0x18]
	str r1, [r0, #8]
	b _021E211E
_021E2110:
	ldr r0, _021E2180 ; =0x04001000
	ldr r1, [r0]
	ldr r0, _021E217C ; =0x00300010
	and r1, r0
	ldr r0, [sp, #8]
	ldr r0, [r0, #0x18]
	str r1, [r0, #8]
_021E211E:
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x10]
	ldr r0, [r0, #0x18]
	ldr r2, [sp, #0x14]
	ldr r3, [sp, #0x48]
	lsl r1, r1, #5
	bl FUN_020B1768
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
_021E2132:
	ldr r0, [sp, #8]
	ldr r1, [r0, #0x18]
	ldr r0, [r1, #0x14]
	ldr r1, [r1, #0x10]
	bl DC_FlushRange
	ldr r0, [sp, #0x14]
	cmp r0, #1
	beq _021E214C
	cmp r0, #2
	beq _021E2160
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
_021E214C:
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x10]
	ldr r2, [r0, #0x18]
	lsl r1, r1, #5
	ldr r0, [r2, #0x14]
	ldr r2, [r2, #0x10]
	bl GX_LoadOBJ
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
_021E2160:
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x10]
	ldr r2, [r0, #0x18]
	lsl r1, r1, #5
	ldr r0, [r2, #0x14]
	ldr r2, [r2, #0x10]
	bl GXS_LoadOBJ
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021E2174: .word 0x000001EA
_021E2178: .word 0x021E6644
_021E217C: .word 0x00300010
_021E2180: .word 0x04001000

	thumb_func_start MOD14_021E2184
MOD14_021E2184: ; 0x021E2184
	ldr r0, [r0, #0x20]
	bx lr

	thumb_func_start MOD14_021E2188
MOD14_021E2188: ; 0x021E2188
	add r0, #0xe0
	ldr r0, [r0]
	sub r0, r0, #3
	bpl _021E2192
	add r0, #0x12
_021E2192:
	bx lr

	thumb_func_start MOD14_021E2194
MOD14_021E2194: ; 0x021E2194
	push {r3, r4}
	mov r4, #0
	ldr r1, _021E21AC ; =0x00004BE4
	add r3, r4, #0
_021E219C:
	add r2, r0, r4
	add r4, r4, #1
	strb r3, [r2, r1]
	cmp r4, #0x12
	blt _021E219C
	pop {r3, r4}
	bx lr
	nop
_021E21AC: .word 0x00004BE4

	thumb_func_start MOD14_021E21B0
MOD14_021E21B0: ; 0x021E21B0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	mov r2, #0xf9
	add r4, r1, #0
	lsl r2, r2, #2
	add r3, r5, r2
	lsl r1, r4, #0xa
	ldr r0, [r0, #0x14]
	add r1, r3, r1
	add r2, #0x1c
	bl MIi_CpuCopy32
	mov r1, #0xf9
	lsl r1, r1, #2
	add r0, r5, r1
	add r1, #0x1c
	bl DC_FlushRange
	ldr r0, _021E21E0 ; =0x00004BE4
	mov r2, #1
	add r1, r5, r4
	strb r2, [r1, r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E21E0: .word 0x00004BE4

	thumb_func_start MOD14_021E21E4
MOD14_021E21E4: ; 0x021E21E4
	push {r4, r5, r6, lr}
	sub sp, #0x28
	add r5, r0, #0
	mov r0, #0x63
	lsl r1, r1, #5
	lsl r0, r0, #4
	add r6, r1, r0
	add r4, r2, #0
	ldr r0, _021E2238 ; =0x00004BE4
	add r1, r5, r4
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _021E2214
	mov r2, #0xf9
	lsl r2, r2, #2
	add r1, r5, r2
	lsl r0, r4, #0xa
	add r0, r1, r0
	lsl r1, r6, #5
	add r2, #0x1c
	bl GX_LoadOBJ
	add sp, #0x28
	pop {r4, r5, r6, pc}
_021E2214:
	add r0, sp, #4
	bl FUN_020B1A24
	add r0, sp, #4
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	mov r3, #1
	bl MOD14_021E1FF8
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021E21B0
	add sp, #0x28
	pop {r4, r5, r6, pc}
	nop
_021E2238: .word 0x00004BE4

	thumb_func_start MOD14_021E223C
MOD14_021E223C: ; 0x021E223C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x64
	add r6, r0, #0
	bl MOD14_021E2194
	ldr r0, [r6]
	bl MOD14_021DDD50
	add r4, r0, #0
	ldr r0, [r6]
	bl MOD14_021DDD48
	add r2, r0, #0
	ldr r0, [r4, #4]
	mov r1, #0
	str r0, [sp]
	str r1, [sp, #4]
	ldr r3, [r6, #0x20]
	add r0, sp, #0x40
	bl MOD14_021DDDB4
	add r0, r6, #0
	bl MOD14_021E2188
	add r7, r0, #0
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #0x63
	lsl r0, r0, #4
	str r0, [sp, #8]
	add r4, r6, #0
	mov r5, #0x20
_021E227C:
	add r0, sp, #0x1c
	bl FUN_020B1A24
	add r0, sp, #0x1c
	str r0, [sp]
	ldr r2, [sp, #8]
	add r0, r6, #0
	add r1, r7, #0
	mov r3, #1
	bl MOD14_021E1FF8
	add r0, sp, #0x1c
	str r0, [sp, #0x40]
	mov r0, #0xb
	str r0, [sp]
	mov r0, #1
	mov r2, #2
	str r0, [sp, #4]
	lsl r2, r2, #8
	ldr r0, [r6, #8]
	add r1, sp, #0x40
	lsr r3, r2, #1
	bl MOD14_021DDDD4
	str r0, [r4, #0x48]
	cmp r0, #0
	bne _021E22B6
	bl ErrorHandling
_021E22B6:
	ldr r0, [r4, #0x48]
	mov r1, #0
	bl FUN_020200A0
	cmp r5, #0
	ble _021E22D4
	lsl r0, r5, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021E22E2
_021E22D4:
	lsl r0, r5, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021E22E2:
	bl _ffix
	str r0, [sp, #0x10]
	mov r0, #0x16
	lsl r0, r0, #0xe
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x48]
	add r1, sp, #0x10
	bl FUN_02020044
	add r0, r6, #0
	add r1, r7, #0
	bl MOD14_021E21B0
	add r7, r7, #1
	cmp r7, #0x12
	blt _021E230A
	mov r7, #0
_021E230A:
	ldr r0, [sp, #8]
	add r4, r4, #4
	add r0, #0x20
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	add r5, #0x20
	add r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, #7
	blt _021E227C
	mov r4, #0
	add r5, r6, #0
_021E2322:
	ldr r0, [r6, #0xc]
	bl MOD14_021DC44C
	add r1, r4, #0
	bl FUN_0206B4E4
	add r1, r5, #0
	add r1, #0x94
	add r4, r4, #1
	add r5, r5, #4
	str r0, [r1]
	cmp r4, #0x12
	blt _021E2322
	add sp, #0x64
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E2340
MOD14_021E2340: ; 0x021E2340
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_021E2348:
	ldr r0, [r5, #0x48]
	cmp r0, #0
	beq _021E2354
	bl FUN_0201FFC8
	str r6, [r5, #0x48]
_021E2354:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #7
	blt _021E2348
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E2360
MOD14_021E2360: ; 0x021E2360
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	bl MOD14_021E2188
	add r4, r0, #0
	mov r6, #0
	add r5, r7, #0
_021E236E:
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD14_021E21E4
	ldr r0, [r5, #0x48]
	mov r1, #1
	bl FUN_020200A0
	add r4, r4, #1
	cmp r4, #0x12
	blt _021E2388
	mov r4, #0
_021E2388:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #7
	blt _021E236E
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021E2394
MOD14_021E2394: ; 0x021E2394
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl MOD14_021DC44C
	add r1, r5, #0
	ldr r2, _021E23F0 ; =0x00004BFC
	add r1, #0xe0
	ldr r1, [r1]
	ldr r2, [r5, r2]
	ldr r4, [r5, #0x10]
	bl FUN_0206B484
	ldr r1, _021E23F0 ; =0x00004BFC
	mov r0, #0
	ldr r1, [r5, r1]
	add r2, r0, #0
	bl FUN_02002E14
	add r6, r0, #0
	add r0, r4, #0
	mov r1, #7
	bl FUN_02019620
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E23F4 ; =0x00020807
	ldr r2, _021E23F0 ; =0x00004BFC
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5, r2]
	lsr r5, r6, #1
	mov r3, #0x30
	add r0, r4, #0
	sub r3, r3, r5
	bl FUN_0201BDE0
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_021E23F0: .word 0x00004BFC
_021E23F4: .word 0x00020807

	thumb_func_start MOD14_021E23F8
MOD14_021E23F8: ; 0x021E23F8
	push {r4, lr}
	ldr r4, [r0, #0x10]
	mov r1, #7
	add r0, r4, #0
	bl FUN_02019620
	add r0, r4, #0
	bl FUN_02019548
	pop {r4, pc}

	thumb_func_start MOD14_021E240C
MOD14_021E240C: ; 0x021E240C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	ldr r0, [r7, #0x10]
	mov r1, #4
	str r0, [sp, #0xc]
	add r0, #0x10
	str r0, [sp, #0xc]
	bl FUN_02019620
	add r0, r7, #0
	bl MOD14_021E2188
	mov r6, #0
	add r4, r0, #0
	add r5, r6, #0
_021E242C:
	ldr r0, [sp, #0xc]
	lsl r1, r4, #2
	str r0, [sp]
	add r1, r7, r1
	str r5, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r1, #0x94
	mov r2, #2
	ldr r0, [r7, #0x44]
	ldr r1, [r1]
	add r3, r2, #0
	bl FUN_0200B9EC
	add r4, r4, #1
	cmp r4, #0x12
	blt _021E2450
	mov r4, #0
_021E2450:
	add r6, r6, #1
	add r5, #0x20
	cmp r6, #7
	blt _021E242C
	ldr r0, [sp, #0xc]
	bl FUN_02019548
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021E2464
MOD14_021E2464: ; 0x021E2464
	push {r4, lr}
	ldr r4, [r0, #0x10]
	mov r1, #4
	add r4, #0x10
	add r0, r4, #0
	bl FUN_02019620
	add r0, r4, #0
	bl FUN_02019548
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E247C
MOD14_021E247C: ; 0x021E247C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0xa
	mov r1, #0xc
	bl FUN_02016998
	add r4, r0, #0
	beq _021E24B6
	ldr r0, _021E24B8 ; =0x021E6624
	lsl r1, r6, #2
	ldr r0, [r0, r1]
	str r5, [r4]
	mov r2, #0
	strb r2, [r4, #4]
	add r1, r4, #0
	strb r2, [r4, #5]
	bl FUN_0200CA44
	add r1, r5, #0
	add r1, #0xdc
	add r5, #0xdc
	str r0, [r1]
	ldr r0, [r5]
	cmp r0, #0
	bne _021E24B6
	add r0, r4, #0
	bl FUN_02016A18
_021E24B6:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021E24B8: .word 0x021E6624

	thumb_func_start MOD14_021E24BC
MOD14_021E24BC: ; 0x021E24BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1]
	mov r2, #0
	add r0, #0xdc
	str r2, [r0]
	add r0, r1, #0
	bl FUN_02016A18
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E24D8
MOD14_021E24D8: ; 0x021E24D8
	add r0, #0xdc
	ldr r0, [r0]
	cmp r0, #0
	bne _021E24E4
	mov r0, #1
	bx lr
_021E24E4:
	mov r0, #0
	bx lr

	thumb_func_start MOD14_021E24E8
MOD14_021E24E8: ; 0x021E24E8
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r4, r1, #0
	ldrb r2, [r4, #4]
	ldr r5, [r4]
	cmp r2, #3
	bls _021E24F8
	b _021E260E
_021E24F8:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021E2504: ; jump table
	.short _021E250C - _021E2504 - 2 ; case 0
	.short _021E2592 - _021E2504 - 2 ; case 1
	.short _021E25B8 - _021E2504 - 2 ; case 2
	.short _021E260A - _021E2504 - 2 ; case 3
_021E250C:
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
	ldrb r0, [r4, #5]
	lsl r1, r0, #1
	cmp r1, #0xa
	bge _021E2562
	mov r1, #0xa
	sub r1, r1, r0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp]
	mov r1, #0x20
	str r1, [sp, #4]
	str r0, [sp, #8]
	ldr r2, [r5, #0x30]
	ldr r0, [r5, #4]
	mov r1, #1
	add r2, #0xc
	mov r3, #0
	bl FUN_02018148
	ldrb r6, [r4, #5]
	mov r0, #0x20
	mov r3, #0xa
	str r0, [sp]
	str r6, [sp, #4]
	ldr r1, [r5, #0x30]
	mov r2, #0
	add r1, #0xc
	str r1, [sp, #8]
	sub r1, r3, r6
	lsl r1, r1, #0x18
	str r2, [sp, #0xc]
	lsr r1, r1, #0x18
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	str r3, [sp, #0x18]
	ldr r0, [r5, #4]
	mov r1, #1
	bl FUN_02018170
	b _021E2582
_021E2562:
	mov r0, #5
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	ldr r2, [r5, #0x30]
	ldr r0, [r5, #4]
	mov r1, #1
	add r2, #0xc
	mov r3, #0
	bl FUN_02018148
	ldrb r0, [r4, #4]
	add r0, r0, #1
	strb r0, [r4, #4]
_021E2582:
	ldr r0, [r5, #4]
	mov r1, #1
	bl FUN_02017CD0
	mov r0, #7
	add sp, #0x1c
	strb r0, [r4, #5]
	pop {r3, r4, r5, r6, pc}
_021E2592:
	ldrb r0, [r4, #5]
	add r3, r5, #0
	mov r2, #0x60
	add r1, r0, #0
	add r3, #0xe4
	mul r1, r2
	add r0, r3, r1
	mov r1, #0x1a
	lsl r1, r1, #4
	bl GX_LoadOBJPltt
	add r0, r5, #0
	bl MOD14_021E2360
	ldrb r0, [r4, #4]
	add sp, #0x1c
	add r0, r0, #1
	strb r0, [r4, #4]
	pop {r3, r4, r5, r6, pc}
_021E25B8:
	ldrb r0, [r4, #5]
	cmp r0, #0
	beq _021E25C2
	sub r0, r0, #1
	strb r0, [r4, #5]
_021E25C2:
	ldrb r0, [r4, #5]
	add r3, r5, #0
	mov r2, #0x60
	add r1, r0, #0
	add r3, #0xe4
	mul r1, r2
	add r0, r3, r1
	mov r1, #0x1a
	lsl r1, r1, #4
	bl GX_LoadOBJPltt
	ldrb r0, [r4, #5]
	cmp r0, #0
	bne _021E260E
	ldr r0, [r5, #0x10]
	bl FUN_02019270
	ldr r0, [r5, #0x10]
	add r0, #0x10
	bl FUN_02019270
	add r0, r5, #0
	bl MOD14_021E2394
	add r0, r5, #0
	bl MOD14_021E240C
	ldr r0, [r5, #4]
	mov r1, #1
	bl FUN_02017CD0
	ldrb r0, [r4, #4]
	add sp, #0x1c
	add r0, r0, #1
	strb r0, [r4, #4]
	pop {r3, r4, r5, r6, pc}
_021E260A:
	bl MOD14_021E24BC
_021E260E:
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E2614
MOD14_021E2614: ; 0x021E2614
	push {r4, r5, lr}
	sub sp, #0x1c
	add r5, r1, #0
	ldrb r2, [r5, #4]
	ldr r4, [r5]
	cmp r2, #0
	beq _021E262E
	cmp r2, #1
	beq _021E264A
	cmp r2, #2
	beq _021E26DC
	add sp, #0x1c
	pop {r4, r5, pc}
_021E262E:
	add r0, r4, #0
	bl MOD14_021E2340
	add r0, r4, #0
	bl MOD14_021E23F8
	add r0, r4, #0
	bl MOD14_021E2464
	ldrb r0, [r5, #4]
	add sp, #0x1c
	add r0, r0, #1
	strb r0, [r5, #4]
	pop {r4, r5, pc}
_021E264A:
	mov r0, #5
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	mov r2, #0
	ldr r0, [r4, #4]
	mov r1, #1
	add r3, r2, #0
	bl FUN_02018540
	ldrb r0, [r5, #5]
	add r0, r0, #1
	strb r0, [r5, #5]
	ldrb r0, [r5, #5]
	lsl r1, r0, #1
	cmp r1, #0xa
	bge _021E26CA
	add r1, r0, #5
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp]
	mov r1, #0x20
	str r1, [sp, #4]
	mov r1, #5
	sub r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r2, [r4, #0x30]
	ldr r0, [r4, #4]
	mov r1, #1
	add r2, #0xc
	mov r3, #0
	bl FUN_02018148
	ldrb r1, [r5, #5]
	mov r2, #5
	mov r0, #0x20
	sub r2, r2, r1
	lsl r2, r2, #0x18
	mov r3, #0xa
	sub r1, r3, r1
	lsl r1, r1, #0x18
	str r0, [sp]
	lsr r2, r2, #0x18
	str r2, [sp, #4]
	ldr r2, [r4, #0x30]
	lsr r1, r1, #0x18
	add r2, #0xc
	str r2, [sp, #8]
	mov r2, #0
	str r2, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	str r3, [sp, #0x18]
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02018170
	b _021E26D0
_021E26CA:
	ldrb r0, [r5, #4]
	add r0, r0, #1
	strb r0, [r5, #4]
_021E26D0:
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02017CD0
	add sp, #0x1c
	pop {r4, r5, pc}
_021E26DC:
	bl MOD14_021E24BC
	add sp, #0x1c
	pop {r4, r5, pc}

	thumb_func_start MOD14_021E26E4
MOD14_021E26E4: ; 0x021E26E4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0xa
	mov r1, #0x18
	bl FUN_02016998
	add r4, r0, #0
	beq _021E2798
	ldr r0, [r5, #0xc]
	bl MOD14_021DC544
	add r6, r0, #0
	ldr r0, [r5, #4]
	mov r1, #1
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	mov r0, #0x18
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	ldr r2, [r5, #0x38]
	ldr r0, [r5, #4]
	mov r1, #1
	add r2, #0xc
	mov r3, #0
	bl FUN_02018148
	ldr r0, [r5, #0x10]
	mov r1, #4
	add r0, #0x20
	bl FUN_02019620
	ldr r2, _021E279C ; =0x00004BF8
	add r1, r6, #0
	ldr r0, [r5, r2]
	add r2, r2, #4
	ldr r2, [r5, r2]
	bl FUN_0200A8E0
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E27A0 ; =0x00020104
	ldr r2, _021E27A4 ; =0x00004BFC
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #0x10]
	ldr r2, [r5, r2]
	add r0, #0x20
	add r3, r1, #0
	bl FUN_0201BDE0
	ldr r0, [r5, #0x10]
	add r0, #0x20
	bl FUN_020191D0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD14_021E2940
	mov r1, #0
	strh r1, [r4, #0x16]
	str r5, [r4]
	ldr r0, [r5, #4]
	str r0, [r4, #4]
	str r1, [r4, #8]
	mov r1, #0xe
	lsl r1, r1, #0xe
	str r1, [r4, #0xc]
	ldr r0, [r4, #8]
	sub r0, r1, r0
	mov r1, #6
	bl _s32_div_f
	str r0, [r4, #0x10]
	mov r0, #6
	strh r0, [r4, #0x14]
	ldr r0, _021E27A8 ; =MOD14_021E27C4
	add r1, r4, #0
	mov r2, #0
	bl MOD14_021DDD40
	add r5, #0xdc
	str r0, [r5]
_021E2798:
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021E279C: .word 0x00004BF8
_021E27A0: .word 0x00020104
_021E27A4: .word 0x00004BFC
_021E27A8: .word MOD14_021E27C4

	thumb_func_start MOD14_021E27AC
MOD14_021E27AC: ; 0x021E27AC
	add r0, #0xdc
	ldr r0, [r0]
	cmp r0, #0
	bne _021E27B8
	mov r0, #1
	bx lr
_021E27B8:
	mov r0, #0
	bx lr

	thumb_func_start MOD14_021E27BC
MOD14_021E27BC: ; 0x021E27BC
	mov r1, #0
	add r0, #0xdc
	str r1, [r0]
	bx lr

	thumb_func_start MOD14_021E27C4
MOD14_021E27C4: ; 0x021E27C4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4, #0x16]
	cmp r0, #0
	beq _021E27D6
	cmp r0, #1
	beq _021E27DC
	pop {r3, r4, r5, pc}
_021E27D6:
	add r0, r0, #1
	strh r0, [r4, #0x16]
	pop {r3, r4, r5, pc}
_021E27DC:
	ldrh r0, [r4, #0x14]
	cmp r0, #0
	beq _021E280A
	sub r0, r0, #1
	strh r0, [r4, #0x14]
	ldr r1, [r4, #8]
	ldr r0, [r4, #0x10]
	mov r2, #3
	add r3, r1, r0
	str r3, [r4, #8]
	ldr r0, [r4, #4]
	mov r1, #1
	asr r3, r3, #0xc
	bl FUN_020179E0
	mov r1, #0xe
	ldr r2, [r4, #8]
	lsl r1, r1, #0x10
	ldr r0, [r4]
	sub r1, r1, r2
	bl MOD14_021E2A00
	pop {r3, r4, r5, pc}
_021E280A:
	ldr r3, [r4, #0xc]
	ldr r0, [r4, #4]
	mov r1, #1
	mov r2, #3
	asr r3, r3, #0xc
	bl FUN_020179E0
	mov r1, #0xe
	ldr r2, [r4, #0xc]
	lsl r1, r1, #0x10
	ldr r0, [r4]
	sub r1, r1, r2
	bl MOD14_021E2A00
	ldr r1, _021E2838 ; =MOD14_021E27BC
	ldr r2, [r4]
	add r0, r4, #0
	bl MOD14_021DDF30
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E2838: .word MOD14_021E27BC

	thumb_func_start MOD14_021E283C
MOD14_021E283C: ; 0x021E283C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0xa
	mov r1, #0x18
	bl FUN_02016998
	add r4, r0, #0
	beq _021E287C
	mov r1, #0
	strh r1, [r4, #0x16]
	str r5, [r4]
	ldr r0, [r5, #4]
	str r0, [r4, #4]
	mov r0, #0xe
	lsl r0, r0, #0xe
	str r0, [r4, #8]
	str r1, [r4, #0xc]
	ldr r0, [r4, #8]
	sub r0, r1, r0
	mov r1, #6
	bl _s32_div_f
	str r0, [r4, #0x10]
	mov r0, #6
	strh r0, [r4, #0x14]
	ldr r0, _021E2880 ; =MOD14_021E28B4
	add r1, r4, #0
	mov r2, #0
	bl MOD14_021DDD40
	add r5, #0xdc
	str r0, [r5]
_021E287C:
	pop {r3, r4, r5, pc}
	nop
_021E2880: .word MOD14_021E28B4

	thumb_func_start MOD14_021E2884
MOD14_021E2884: ; 0x021E2884
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xdc
	ldr r0, [r0]
	cmp r0, #0
	bne _021E28A6
	ldr r0, [r4, #4]
	mov r1, #1
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r0, r4, #0
	bl MOD14_021E2A28
	mov r0, #1
	pop {r4, pc}
_021E28A6:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E28AC
MOD14_021E28AC: ; 0x021E28AC
	mov r1, #0
	add r0, #0xdc
	str r1, [r0]
	bx lr

	thumb_func_start MOD14_021E28B4
MOD14_021E28B4: ; 0x021E28B4
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4, #0x14]
	cmp r0, #0
	beq _021E28EC
	sub r0, r0, #1
	strh r0, [r4, #0x14]
	ldr r1, [r4, #8]
	ldr r0, [r4, #0x10]
	mov r2, #3
	add r3, r1, r0
	str r3, [r4, #8]
	ldr r0, [r4, #4]
	mov r1, #1
	asr r3, r3, #0xc
	bl FUN_020179E0
	mov r1, #0xe
	ldr r2, [r4, #8]
	lsl r1, r1, #0x10
	ldr r0, [r4]
	sub r1, r1, r2
	bl MOD14_021E2A00
	add sp, #0x10
	pop {r3, r4, r5, pc}
_021E28EC:
	ldr r3, [r4, #0xc]
	ldr r0, [r4, #4]
	mov r1, #1
	mov r2, #3
	asr r3, r3, #0xc
	bl FUN_020179E0
	mov r1, #0xe
	ldr r2, [r4, #0xc]
	lsl r1, r1, #0x10
	ldr r0, [r4]
	sub r1, r1, r2
	bl MOD14_021E2A00
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #4]
	mov r1, #1
	add r3, r2, #0
	bl FUN_02018540
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02017CD0
	ldr r1, _021E293C ; =MOD14_021E28AC
	ldr r2, [r4]
	add r0, r4, #0
	bl MOD14_021DDF30
	add r0, r5, #0
	bl FUN_0200CAB4
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E293C: .word MOD14_021E28AC

	thumb_func_start MOD14_021E2940
MOD14_021E2940: ; 0x021E2940
	push {r3, r4, r5, r6, lr}
	sub sp, #0x54
	add r5, r0, #0
	add r4, r1, #0
	beq _021E29F6
	ldr r0, [r5]
	bl MOD14_021DDD50
	add r6, r0, #0
	ldr r0, [r5]
	bl MOD14_021DDD48
	add r2, r0, #0
	ldr r0, [r6, #0x20]
	add r1, sp, #0xc
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r3, [r6, #0x1c]
	add r0, sp, #0x30
	bl MOD14_021DDDB4
	add r0, sp, #0xc
	bl FUN_020B1A24
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	mov r1, #1
	bl FUN_0206E640
	add r1, r0, #0
	mov r0, #0xa
	str r0, [sp]
	mov r0, #0x10
	mov r2, #0
	add r3, sp, #8
	bl FUN_02006BB0
	add r6, r0, #0
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r1, [r0]
	ldr r0, _021E29FC ; =0x00300010
	mov r2, #1
	and r1, r0
	ldr r0, [sp, #8]
	add r3, sp, #0xc
	str r1, [r0, #8]
	mov r1, #0xbe
	ldr r0, [sp, #8]
	lsl r1, r1, #8
	bl FUN_020B1768
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	mov r1, #2
	bl FUN_0206E640
	add r1, r0, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0x10
	mov r2, #1
	mov r3, #0xc0
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #8]
	add r1, sp, #0x30
	mov r2, #0x12
	mov r3, #0xe0
	bl MOD14_021DDDD4
	add r1, r5, #0
	add r1, #0x90
	add r5, #0x90
	str r0, [r1]
	ldr r0, [r5]
	cmp r0, #0
	beq _021E29F0
	mov r1, #6
	bl FUN_02020248
_021E29F0:
	add r0, r6, #0
	bl FUN_02016A18
_021E29F6:
	add sp, #0x54
	pop {r3, r4, r5, r6, pc}
	nop
_021E29FC: .word 0x00300010

	thumb_func_start MOD14_021E2A00
MOD14_021E2A00: ; 0x021E2A00
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r2, #0x90
	ldr r2, [r2]
	cmp r2, #0
	beq _021E2A24
	mov r2, #0x12
	lsl r2, r2, #0xc
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	str r2, [sp]
	add r0, #0x90
	ldr r0, [r0]
	add r1, sp, #0
	bl FUN_02020044
_021E2A24:
	add sp, #0xc
	pop {pc}

	thumb_func_start MOD14_021E2A28
MOD14_021E2A28: ; 0x021E2A28
	push {r3, lr}
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #0
	beq _021E2A36
	bl FUN_0201FFC8
_021E2A36:
	pop {r3, pc}

	thumb_func_start MOD14_021E2A38
MOD14_021E2A38: ; 0x021E2A38
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	str r4, [r5]
	ldr r0, [sp, #0x18]
	str r6, [r5, #0xc]
	str r0, [r5, #8]
	str r3, [r5, #4]
	add r0, r4, #0
	bl MOD14_021DDD50
	str r0, [r5, #0x38]
	add r0, r4, #0
	bl MOD14_021DDD58
	str r0, [r5, #0x10]
	add r0, r6, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021E2A6E
	mov r0, #0xe
	str r0, [r5, #0x30]
	mov r0, #0
	b _021E2A74
_021E2A6E:
	mov r0, #9
	str r0, [r5, #0x30]
	sub r0, #0x31
_021E2A74:
	str r0, [r5, #0x34]
	add r0, r5, #0
	mov r1, #0
	add r0, #0x2b
	strb r1, [r0]
	str r1, [r5, #0x2c]
	add r1, r5, #0
	ldr r0, [r5, #0x38]
	add r1, #0x3c
	mov r2, #6
	bl MOD14_021E08E4
	mov r1, #9
	mov r0, #0xa
	lsl r1, r1, #6
	bl FUN_02016998
	str r0, [r5, #0x1c]
	mov r0, #0xa
	add r3, r5, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #6
	mov r2, #1
	add r3, #0x18
	bl FUN_02006BDC
	str r0, [r5, #0x14]
	cmp r0, #0
	beq _021E2AB6
	ldr r1, [r5, #0x1c]
	cmp r1, #0
	bne _021E2ABC
_021E2AB6:
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021E2ABC:
	add r0, r5, #0
	bl MOD14_021E31F4
	mov r0, #1
	add sp, #4
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD14_021E2AC8
MOD14_021E2AC8: ; 0x021E2AC8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021E2AD6
	bl FUN_02016A18
_021E2AD6:
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _021E2AE0
	bl FUN_02016A18
_021E2AE0:
	add r0, r4, #0
	bl MOD14_021E3390
	pop {r4, pc}

	thumb_func_start MOD14_021E2AE8
MOD14_021E2AE8: ; 0x021E2AE8
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	mov r2, #0
	add r1, #0x2b
	strb r2, [r1]
	add r1, r4, #0
	add r1, #0x2b
	ldrb r1, [r1]
	bl MOD14_021E31A4
	add r0, r4, #0
	mov r1, #1
	bl MOD14_021E32F8
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_02017CD0
	pop {r4, pc}

	thumb_func_start MOD14_021E2B10
MOD14_021E2B10: ; 0x021E2B10
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	bl MOD14_021E32F8
	add r0, r4, #0
	mov r1, #0x1a
	add r0, #0x2b
	strb r1, [r0]
	ldr r0, _021E2B3C ; =MOD14_021E2B50
	add r1, r4, #0
	mov r2, #0
	bl MOD14_021DDD40
	cmp r0, #0
	beq _021E2B34
	mov r0, #1
	b _021E2B36
_021E2B34:
	mov r0, #0
_021E2B36:
	str r0, [r4, #0x2c]
	pop {r4, pc}
	nop
_021E2B3C: .word MOD14_021E2B50

	thumb_func_start MOD14_021E2B40
MOD14_021E2B40: ; 0x021E2B40
	ldr r0, [r0, #0x2c]
	cmp r0, #0
	bne _021E2B4A
	mov r0, #1
	bx lr
_021E2B4A:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021E2B50
MOD14_021E2B50: ; 0x021E2B50
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0x2b
	ldrb r0, [r0]
	cmp r0, #2
	bls _021E2B6C
	add r0, r5, #0
	add r0, #0x2b
	ldrb r0, [r0]
	ldr r4, _021E2BAC ; =0xFFFF0000
	sub r1, r0, #2
	b _021E2B72
_021E2B6C:
	lsl r0, r0, #0xf
	neg r4, r0
	mov r1, #0
_021E2B72:
	add r0, r5, #0
	add r0, #0x2b
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x2b
	ldrb r1, [r1]
	add r0, r5, #0
	bl MOD14_021E31A4
	ldr r0, [r5, #4]
	mov r1, #2
	bl FUN_02017CD0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021E3290
	add r0, r5, #0
	add r0, #0x2b
	ldrb r0, [r0]
	cmp r0, #0
	bne _021E2BA8
	mov r0, #0
	str r0, [r5, #0x2c]
	add r0, r6, #0
	bl FUN_0200CAB4
_021E2BA8:
	pop {r4, r5, r6, pc}
	nop
_021E2BAC: .word 0xFFFF0000

	thumb_func_start MOD14_021E2BB0
MOD14_021E2BB0: ; 0x021E2BB0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E2BCC ; =MOD14_021E2BE4
	add r1, r4, #0
	mov r2, #0
	bl MOD14_021DDD40
	cmp r0, #0
	beq _021E2BC6
	mov r0, #1
	b _021E2BC8
_021E2BC6:
	mov r0, #0
_021E2BC8:
	str r0, [r4, #0x2c]
	pop {r4, pc}
	.align 2, 0
_021E2BCC: .word MOD14_021E2BE4

	thumb_func_start MOD14_021E2BD0
MOD14_021E2BD0: ; 0x021E2BD0
	push {r3, lr}
	ldr r1, [r0, #0x2c]
	cmp r1, #0
	bne _021E2BE0
	bl MOD14_021E3390
	mov r0, #1
	pop {r3, pc}
_021E2BE0:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD14_021E2BE4
MOD14_021E2BE4: ; 0x021E2BE4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0x2b
	ldrb r0, [r0]
	cmp r0, #0x18
	bhs _021E2C04
	add r0, r5, #0
	add r0, #0x2b
	ldrb r0, [r0]
	mov r4, #1
	lsl r4, r4, #0x10
	add r1, r0, #2
	b _021E2C0A
_021E2C04:
	mov r1, #0x1a
	sub r0, r1, r0
	lsl r4, r0, #0xf
_021E2C0A:
	add r0, r5, #0
	add r0, #0x2b
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0x2b
	ldrb r1, [r0]
	cmp r1, #2
	bls _021E2C46
	asr r0, r4, #0xc
	lsr r0, r0, #3
	sub r1, r1, #2
	sub r1, r1, r0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp]
	mov r1, #0xf
	lsl r0, r0, #0x18
	str r1, [sp, #4]
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r3, [r5, #0x30]
	ldr r0, [r5, #4]
	lsl r3, r3, #0x18
	mov r1, #2
	mov r2, #0
	lsr r3, r3, #0x18
	bl FUN_02018540
_021E2C46:
	add r1, r5, #0
	add r1, #0x2b
	ldrb r1, [r1]
	add r0, r5, #0
	bl MOD14_021E31A4
	ldr r0, [r5, #4]
	mov r1, #2
	bl FUN_02017CD0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021E3290
	add r0, r5, #0
	add r0, #0x2b
	ldrb r0, [r0]
	cmp r0, #0x1a
	bne _021E2C76
	mov r0, #0
	str r0, [r5, #0x2c]
	add r0, r6, #0
	bl FUN_0200CAB4
_021E2C76:
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E2C7C
MOD14_021E2C7C: ; 0x021E2C7C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r0, #0
	ldr r0, [r6, #0xc]
	ldr r0, [r0, #4]
	bl FUN_0206B9AC
	add r1, r6, #0
	add r1, #0x28
	ldrb r4, [r1]
	cmp r4, r0
	bge _021E2D20
	sub r0, r0, r4
	str r0, [sp, #8]
	cmp r4, #5
	bge _021E2CF8
	mov r0, #0x34
	add r1, r4, #0
	mul r1, r0
	add r0, r6, #0
	str r0, [sp, #0xc]
	add r0, #0x3c
	str r0, [sp, #0xc]
	add r5, r0, r1
	add r7, r6, r1
	ldr r0, _021E2D28 ; =0x00000418
	lsl r1, r4, #5
	add r0, r1, r0
	str r0, [sp, #4]
_021E2CB6:
	add r1, r4, #1
	mov r0, #0x34
	mul r0, r1
	ldr r1, [sp, #0xc]
	str r0, [sp]
	add r0, r1, r0
	add r1, r5, #0
	mov r2, #1
	bl MOD14_021E0930
	ldr r2, [sp, #0xc]
	ldr r1, [sp]
	ldr r0, [r6, #0x38]
	add r1, r2, r1
	mov r2, #1
	bl MOD14_021E08E4
	ldr r0, [r7, #0x3c]
	cmp r0, #0
	beq _021E2CE8
	ldr r0, [r6, #0x38]
	ldr r2, [sp, #4]
	add r1, r5, #0
	bl MOD14_021E0BBC
_021E2CE8:
	ldr r0, [sp, #4]
	add r4, r4, #1
	add r0, #0x20
	add r5, #0x34
	add r7, #0x34
	str r0, [sp, #4]
	cmp r4, #5
	blt _021E2CB6
_021E2CF8:
	add r1, r6, #0
	ldr r0, [sp, #8]
	add r1, #0x29
	strb r0, [r1]
	add r0, r6, #0
	mov r2, #0
	add r0, #0x2a
	strb r2, [r0]
	ldr r0, _021E2D2C ; =MOD14_021E2D30
	add r1, r6, #0
	bl MOD14_021DDD40
	cmp r0, #0
	beq _021E2D18
	mov r0, #1
	b _021E2D1A
_021E2D18:
	mov r0, #0
_021E2D1A:
	add sp, #0x10
	str r0, [r6, #0x2c]
	pop {r3, r4, r5, r6, r7, pc}
_021E2D20:
	mov r0, #0
	str r0, [r6, #0x2c]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E2D28: .word 0x00000418
_021E2D2C: .word MOD14_021E2D30

	thumb_func_start MOD14_021E2D30
MOD14_021E2D30: ; 0x021E2D30
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r1, [sp, #4]
	ldr r2, [sp, #4]
	str r0, [sp]
	add r1, #0x28
	ldr r0, [sp, #4]
	add r2, #0x2a
	add r0, #0x29
	ldrb r7, [r0]
	ldr r0, [sp, #4]
	ldrb r1, [r1]
	ldrb r3, [r2]
	ldr r0, [r0, #0x1c]
	lsl r2, r1, #3
	add r3, r3, r2
	mov r2, #0xc
	mul r2, r3
	add r4, r0, r2
	mov r6, #0
	cmp r7, #0
	ble _021E2D7C
	mov r0, #0x34
	add r2, r1, #0
	mul r2, r0
	ldr r0, [sp, #4]
	add r5, r0, r2
_021E2D66:
	ldr r0, [r5, #0x3c]
	cmp r0, #0
	beq _021E2D72
	add r1, r4, #0
	bl FUN_02020044
_021E2D72:
	add r6, r6, #1
	add r5, #0x34
	add r4, #0x60
	cmp r6, r7
	blt _021E2D66
_021E2D7C:
	ldr r0, [sp, #4]
	add r0, #0x2a
	ldrb r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #4]
	add r0, #0x2a
	strb r1, [r0]
	ldr r0, [sp, #4]
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #8
	blo _021E2DA0
	ldr r0, [sp, #4]
	mov r1, #0
	str r1, [r0, #0x2c]
	ldr r0, [sp]
	bl FUN_0200CAB4
_021E2DA0:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E2DA4
MOD14_021E2DA4: ; 0x021E2DA4
	ldr r0, [r0, #0x2c]
	cmp r0, #0
	bne _021E2DAE
	mov r0, #1
	bx lr
_021E2DAE:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021E2DB4
MOD14_021E2DB4: ; 0x021E2DB4
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #4]
	bl FUN_0206B9AC
	sub r4, r0, #1
	add r0, r5, #0
	add r0, #0x28
	ldrb r0, [r0]
	cmp r0, r4
	bls _021E2E3A
	mov r0, #0x34
	mul r0, r4
	add r0, r5, r0
	ldr r0, [r0, #0x3c]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r1, _021E2E44 ; =0x021E6650
	str r0, [r2]
	lsl r0, r4, #2
	ldrh r1, [r1, r0]
	ldr r2, [r5, #0x34]
	add r1, r2, r1
	lsl r2, r1, #0xc
	ldr r1, [sp]
	sub r2, r2, r1
	asr r1, r2, #2
	lsr r1, r1, #0x1d
	add r1, r2, r1
	asr r1, r1, #3
	str r1, [r5, #0x20]
	ldr r1, _021E2E48 ; =0x021E6652
	mov r2, #0
	ldrh r0, [r1, r0]
	lsl r1, r0, #0xc
	ldr r0, [sp, #4]
	sub r1, r1, r0
	asr r0, r1, #2
	lsr r0, r0, #0x1d
	add r0, r1, r0
	asr r0, r0, #3
	str r0, [r5, #0x24]
	add r0, r5, #0
	add r0, #0x2a
	strb r2, [r0]
	add r0, r5, #0
	add r0, #0x28
	strb r4, [r0]
	ldr r0, _021E2E4C ; =MOD14_021E2E60
	add r1, r5, #0
	bl MOD14_021DDD40
	cmp r0, #0
	beq _021E2E32
	mov r0, #1
	b _021E2E34
_021E2E32:
	mov r0, #0
_021E2E34:
	add sp, #0xc
	str r0, [r5, #0x2c]
	pop {r4, r5, pc}
_021E2E3A:
	mov r0, #0
	str r0, [r5, #0x2c]
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021E2E44: .word 0x021E6650
_021E2E48: .word 0x021E6652
_021E2E4C: .word MOD14_021E2E60

	thumb_func_start MOD14_021E2E50
MOD14_021E2E50: ; 0x021E2E50
	ldr r0, [r0, #0x2c]
	cmp r0, #0
	bne _021E2E5A
	mov r0, #1
	bx lr
_021E2E5A:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021E2E60
MOD14_021E2E60: ; 0x021E2E60
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0x28
	ldrb r1, [r0]
	mov r0, #0x34
	mul r0, r1
	add r0, r5, r0
	ldr r0, [r0, #0x3c]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r5, #0
	add r0, #0x2a
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0x2a
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #8
	blo _021E2EC6
	add r1, r5, #0
	add r1, #0x28
	ldrb r1, [r1]
	ldr r0, [r5, #0x34]
	mov r4, #1
	lsl r2, r1, #2
	ldr r1, _021E2F00 ; =0x021E6650
	ldrh r1, [r1, r2]
	add r0, r0, r1
	lsl r0, r0, #0xc
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x28
	ldrb r0, [r0]
	lsl r1, r0, #2
	ldr r0, _021E2F04 ; =0x021E6652
	ldrh r0, [r0, r1]
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	b _021E2ED8
_021E2EC6:
	ldr r1, [sp]
	ldr r0, [r5, #0x20]
	mov r4, #0
	add r0, r1, r0
	str r0, [sp]
	ldr r1, [sp, #4]
	ldr r0, [r5, #0x24]
	add r0, r1, r0
	str r0, [sp, #4]
_021E2ED8:
	add r0, r5, #0
	add r0, #0x28
	ldrb r1, [r0]
	mov r0, #0x34
	mul r0, r1
	add r0, r5, r0
	ldr r0, [r0, #0x3c]
	add r1, sp, #0
	bl FUN_02020044
	cmp r4, #0
	beq _021E2EFA
	mov r0, #0
	str r0, [r5, #0x2c]
	add r0, r6, #0
	bl FUN_0200CAB4
_021E2EFA:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021E2F00: .word 0x021E6650
_021E2F04: .word 0x021E6652

	thumb_func_start MOD14_021E2F08
MOD14_021E2F08: ; 0x021E2F08
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl MOD14_021DC424
	mov r1, #0x11
	ldr r2, [r5, #0xc]
	lsl r1, r1, #4
	ldrh r1, [r2, r1]
	cmp r1, r0
	bne _021E2F24
	ldr r0, [r5, #0x10]
	bl MOD14_021DEA50
_021E2F24:
	ldr r0, [r5, #0xc]
	bl MOD14_021DC3E8
	add r4, r0, #0
	add r2, r5, #0
	mov r1, #0x34
	ldr r0, [r5, #0x38]
	add r2, #0x3c
	mul r1, r4
	add r1, r2, r1
	mov r2, #1
	bl MOD14_021E0908
	add r5, #0x28
	strb r4, [r5]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021E2F44
MOD14_021E2F44: ; 0x021E2F44
	add r2, r0, #0
	mov r0, #0x5d
	mov r3, #0
	lsl r0, r0, #2
	strb r3, [r2, r0]
	add r0, r2, #0
	add r0, #0x28
	mov r3, #0x34
	strb r1, [r0]
	ldr r0, [r2, #0x38]
	add r2, #0x3c
	mul r3, r1
	add r1, r2, r3
	ldr r3, _021E2F64 ; =MOD14_021E0C20
	mov r2, #1
	bx r3
	.align 2, 0
_021E2F64: .word MOD14_021E0C20

	thumb_func_start MOD14_021E2F68
MOD14_021E2F68: ; 0x021E2F68
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, #0x28
	ldrb r1, [r0]
	add r4, r5, #0
	mov r0, #0x34
	add r6, r1, #0
	mul r6, r0
	mov r0, #0x5d
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	add r4, #0x3c
	cmp r0, #0
	beq _021E2F8A
	cmp r0, #1
	beq _021E2FD2
	b _021E2FE2
_021E2F8A:
	ldr r0, [r5, #0x38]
	add r1, r4, r6
	bl MOD14_021E0C48
	cmp r0, #0
	beq _021E2FE2
	ldr r0, [r5]
	bl MOD14_021DDEDC
	add r7, r0, #0
	bl MOD14_021DA1B8
	cmp r0, #0
	beq _021E2FE2
	add r0, r7, #0
	bl MOD14_021DA1C0
	cmp r0, #0
	ldr r0, [r5, #0x38]
	beq _021E2FBE
	add r1, r4, r6
	mov r2, #1
	bl MOD14_021E0908
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E2FBE:
	add r1, r4, r6
	mov r2, #2
	bl MOD14_021E0C20
	mov r0, #0x5d
	lsl r0, r0, #2
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
	b _021E2FE2
_021E2FD2:
	ldr r0, [r5, #0x38]
	add r1, r4, r6
	bl MOD14_021E0C48
	cmp r0, #0
	beq _021E2FE2
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E2FE2:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021E2FE8
MOD14_021E2FE8: ; 0x021E2FE8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, [r7, #0xc]
	bl MOD14_021DC3CC
	cmp r0, #1
	bne _021E3020
	ldr r0, [r7, #0xc]
	bl MOD14_021DC484
	add r5, r7, #0
	str r0, [sp]
	mov r6, #0
	add r4, r7, #0
	add r5, #0x3c
_021E3006:
	ldr r0, [r4, #0x3c]
	cmp r0, #0
	beq _021E3016
	ldr r0, [r7, #0x38]
	ldr r2, [sp]
	add r1, r5, #0
	bl MOD14_021E0B54
_021E3016:
	add r6, r6, #1
	add r4, #0x34
	add r5, #0x34
	cmp r6, #6
	blt _021E3006
_021E3020:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3024
MOD14_021E3024: ; 0x021E3024
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r5, #0
	mov r0, #0x34
	add r4, r1, #0
	mul r4, r0
	add r6, #0x3c
	ldr r0, [r6, r4]
	cmp r0, #0
	beq _021E3050
	ldr r0, [r5, #0x38]
	add r1, r6, r4
	bl MOD14_021E0BA8
	ldr r0, [r5, #0xc]
	bl MOD14_021DC484
	add r2, r0, #0
	ldr r0, [r5, #0x38]
	add r1, r6, r4
	bl MOD14_021E0B54
_021E3050:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3054
MOD14_021E3054: ; 0x021E3054
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl MOD14_021DC3E8
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	bl MOD14_021DC45C
	add r2, r0, #0
	add r1, r5, #0
	mov r0, #0x34
	add r3, r4, #0
	add r1, #0x3c
	mul r3, r0
	ldr r0, [r1, r3]
	cmp r0, #0
	beq _021E3080
	ldr r0, [r5, #0x38]
	add r1, r1, r3
	bl MOD14_021E0BA4
_021E3080:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3084
MOD14_021E3084: ; 0x021E3084
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r5, r0, #0
	mov r0, #0x34
	add r4, r6, #0
	mul r4, r0
	add r0, r5, #0
	add r7, r3, #0
	add r0, #0x3c
	str r2, [sp]
	add r0, r0, r4
	add r1, r7, #0
	mov r2, #1
	bl MOD14_021E0930
	ldr r0, [r5, #0x38]
	ldr r2, [sp]
	add r1, r7, #0
	bl MOD14_021E0BBC
	add r1, r5, #0
	add r1, #0x3c
	ldr r0, [r5, #0x38]
	add r1, r1, r4
	mov r2, #1
	bl MOD14_021E08E4
	add r5, #0x28
	strb r6, [r5]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E30C0
MOD14_021E30C0: ; 0x021E30C0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	str r1, [sp]
	ldr r0, [r0, #4]
	str r2, [sp, #4]
	bl FUN_0206B9AC
	sub r6, r0, #1
	add r4, r5, #0
	mov r0, #0x34
	add r7, r6, #0
	mul r7, r0
	add r4, #0x3c
	ldr r0, [sp, #4]
	add r1, r4, r7
	mov r2, #1
	bl MOD14_021E0930
	ldr r2, _021E3110 ; =0x00000418
	lsl r3, r6, #5
	ldr r0, [r5, #0x38]
	add r1, r4, r7
	add r2, r3, r2
	bl MOD14_021E0BBC
	ldr r0, [r4, r7]
	mov r1, #1
	bl FUN_02020238
	ldr r0, [r4, r7]
	add r1, r6, #4
	bl MOD14_021DDE24
	ldr r0, [sp]
	add r5, #0x28
	strb r0, [r5]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E3110: .word 0x00000418

	thumb_func_start MOD14_021E3114
MOD14_021E3114: ; 0x021E3114
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r1, #0
	add r5, r7, #0
	mov r0, #0x34
	add r4, r6, #0
	mul r4, r0
	add r5, #0x3c
	add r0, r2, #0
	add r1, r5, r4
	mov r2, #1
	bl MOD14_021E0930
	ldr r2, _021E3154 ; =0x00000418
	lsl r3, r6, #5
	ldr r0, [r7, #0x38]
	add r1, r5, r4
	add r2, r3, r2
	bl MOD14_021E0BBC
	ldr r0, [r5, r4]
	mov r1, #1
	bl FUN_02020238
	ldr r0, [r5, r4]
	add r1, r6, #4
	bl MOD14_021DDE24
	add r7, #0x28
	strb r6, [r7]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E3154: .word 0x00000418

	thumb_func_start MOD14_021E3158
MOD14_021E3158: ; 0x021E3158
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	cmp r4, #6
	blo _021E3166
	bl ErrorHandling
_021E3166:
	mov r0, #0x34
	add r5, #0x3c
	mul r0, r4
	add r0, r5, r0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021E3170
MOD14_021E3170: ; 0x021E3170
	push {r3, r4}
	cmp r1, #6
	bne _021E3184
	ldr r0, [r0, #0x34]
	add r0, #0xc0
	str r0, [r2]
	mov r0, #0xb8
	str r0, [r3]
	pop {r3, r4}
	bx lr
_021E3184:
	ldr r4, [r0, #0x34]
	ldr r0, _021E319C ; =0x021E6650
	lsl r1, r1, #2
	ldrh r0, [r0, r1]
	add r0, r4, r0
	str r0, [r2]
	ldr r0, _021E31A0 ; =0x021E6652
	ldrh r0, [r0, r1]
	str r0, [r3]
	pop {r3, r4}
	bx lr
	nop
_021E319C: .word 0x021E6650
_021E31A0: .word 0x021E6652

	thumb_func_start MOD14_021E31A4
MOD14_021E31A4: ; 0x021E31A4
	push {r3, r4, lr}
	sub sp, #0xc
	add r3, r0, #0
	cmp r1, #2
	bhi _021E31BE
	mov r0, #2
	sub r1, r0, r1
	add r2, r1, #0
	mov r0, #0x1e
	mul r2, r0
	mov r1, #0x18
	mov r0, #0
	b _021E31CC
_021E31BE:
	cmp r1, #0x1a
	bhs _021E31F0
	mov r0, #0x1a
	sub r1, r0, r1
	mov r0, #0x18
	mov r2, #0
	sub r0, r0, r1
_021E31CC:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xf
	str r0, [sp, #4]
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r4, [r3, #0x18]
	ldr r0, [r3, #4]
	ldr r3, [r3, #0x30]
	add r4, #0xc
	lsl r3, r3, #0x18
	mov r1, #2
	add r2, r4, r2
	lsr r3, r3, #0x18
	bl FUN_02018148
_021E31F0:
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD14_021E31F4
MOD14_021E31F4: ; 0x021E31F4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	str r1, [sp, #4]
	mov r0, #0
	ldr r1, _021E328C ; =0x021E6650
	mov ip, r0
_021E3202:
	ldrh r3, [r1]
	ldrh r2, [r1, #4]
	mov r0, #0
	ldrh r4, [r1, #2]
	sub r2, r3, r2
	lsl r3, r2, #0xc
	asr r2, r3, #2
	lsr r2, r2, #0x1d
	add r2, r3, r2
	ldrh r3, [r1, #6]
	asr r2, r2, #3
	mov lr, r2
	sub r3, r4, r3
	lsl r4, r3, #0xc
	asr r3, r4, #2
	lsr r3, r3, #0x1d
	add r3, r4, r3
	ldr r2, [sp, #4]
	add r6, r0, #0
	asr r7, r3, #3
	add r5, r0, #0
_021E322C:
	ldr r3, [sp]
	add r5, r5, r7
	ldr r4, [r3, #0x34]
	ldrh r3, [r1, #4]
	add r0, r0, #1
	add r3, r4, r3
	lsl r4, r3, #0xc
	mov r3, lr
	add r6, r6, r3
	add r3, r4, r6
	str r3, [r2]
	ldrh r3, [r1, #6]
	lsl r3, r3, #0xc
	add r3, r3, r5
	str r3, [r2, #4]
	mov r3, #0
	str r3, [r2, #8]
	add r2, #0xc
	cmp r0, #7
	blo _021E322C
	ldr r3, [sp]
	mov r2, #0xc
	ldr r4, [r3, #0x34]
	ldrh r3, [r1]
	mul r2, r0
	ldr r0, [sp, #4]
	add r3, r4, r3
	lsl r4, r3, #0xc
	ldr r3, [sp, #4]
	add r0, r0, r2
	str r4, [r3, r2]
	ldrh r2, [r1, #2]
	add r1, r1, #4
	lsl r2, r2, #0xc
	str r2, [r0, #4]
	mov r2, #0
	str r2, [r0, #8]
	add r0, r3, #0
	add r0, #0x60
	str r0, [sp, #4]
	mov r0, ip
	add r0, r0, #1
	mov ip, r0
	cmp r0, #5
	blo _021E3202
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E328C: .word 0x021E6650

	thumb_func_start MOD14_021E3290
MOD14_021E3290: ; 0x021E3290
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	mov r7, #0
_021E329A:
	ldr r0, [r5, #0x3c]
	cmp r0, #0
	beq _021E32F2
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [sp, #4]
	add r0, r0, r4
	str r0, [sp, #4]
	ldr r0, [r5, #0x3c]
	bl FUN_02020044
	cmp r4, #0
	bge _021E32D8
	mov r0, #0xd
	ldr r1, [sp, #4]
	lsl r0, r0, #0x10
	cmp r1, r0
	bge _021E32EA
	ldr r0, [r5, #0x3c]
	mov r1, #1
	bl FUN_020200A0
	b _021E32EA
_021E32D8:
	mov r0, #0xd
	ldr r1, [sp, #4]
	lsl r0, r0, #0x10
	cmp r1, r0
	blt _021E32EA
	ldr r0, [r5, #0x3c]
	mov r1, #0
	bl FUN_020200A0
_021E32EA:
	add r7, r7, #1
	add r5, #0x34
	cmp r7, #6
	blt _021E329A
_021E32F2:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021E32F8
MOD14_021E32F8: ; 0x021E32F8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp, #0x24]
	str r1, [sp, #0x10]
	cmp r1, #0
	beq _021E330A
	mov r0, #0
	str r0, [sp, #0x14]
	b _021E330E
_021E330A:
	mov r0, #0xd0
	str r0, [sp, #0x14]
_021E330E:
	ldr r0, [sp, #0x24]
	ldr r0, [r0, #0xc]
	ldr r0, [r0, #4]
	bl FUN_0206B9AC
	mov r4, #0
	str r0, [sp, #0x20]
	cmp r0, #0
	ble _021E3384
	ldr r0, [sp, #0x24]
	ldr r7, _021E3388 ; =0x00000418
	str r0, [sp, #0x1c]
	add r0, #0x3c
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x24]
	ldr r5, _021E338C ; =0x021E6650
	str r0, [sp, #0x18]
_021E3330:
	ldr r0, [sp, #0x24]
	add r1, r4, #0
	ldr r0, [r0, #0xc]
	ldr r0, [r0, #4]
	bl FUN_0206B9B0
	add r1, r0, #0
	mov r0, #1
	str r0, [sp]
	add r0, r4, #4
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	str r7, [sp, #8]
	str r0, [sp, #0xc]
	ldr r2, [sp, #0x24]
	ldr r0, [sp, #0x24]
	ldr r3, [r2, #0x34]
	ldrh r2, [r5]
	ldrh r6, [r5, #2]
	ldr r0, [r0, #0x38]
	add r2, r3, r2
	ldr r3, [sp, #0x14]
	add r3, r3, r6
	bl MOD14_021E0940
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x10]
	ldr r0, [r0, #0x3c]
	bl FUN_020200A0
	ldr r0, [sp, #0x1c]
	add r4, r4, #1
	add r0, #0x34
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r7, #0x20
	add r0, #0x34
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	add r5, r5, #4
	cmp r4, r0
	blt _021E3330
_021E3384:
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E3388: .word 0x00000418
_021E338C: .word 0x021E6650

	thumb_func_start MOD14_021E3390
MOD14_021E3390: ; 0x021E3390
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, [r7, #0xc]
	ldr r0, [r0, #4]
	bl FUN_0206B9AC
	mov r6, #0
	str r0, [sp]
	cmp r0, #0
	ble _021E33C6
	add r5, r7, #0
	add r4, r7, #0
	add r5, #0x3c
_021E33AA:
	ldr r0, [r4, #0x3c]
	cmp r0, #0
	beq _021E33BA
	ldr r0, [r7, #0x38]
	add r1, r5, #0
	mov r2, #1
	bl MOD14_021E0908
_021E33BA:
	ldr r0, [sp]
	add r6, r6, #1
	add r4, #0x34
	add r5, #0x34
	cmp r6, r0
	blt _021E33AA
_021E33C6:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E33C8
MOD14_021E33C8: ; 0x021E33C8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r2, #0
	add r6, r0, #0
	add r0, r5, #0
	add r7, r1, #0
	str r3, [sp]
	bl MOD14_021DC3C4
	cmp r0, #4
	bne _021E33E4
	mov r0, #0
	str r0, [r6]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E33E4:
	mov r0, #0xa
	mov r1, #0xf4
	bl FUN_02016998
	add r4, r0, #0
	beq _021E3460
	ldr r0, [sp]
	mov r1, #0xa
	str r0, [r4, #8]
	str r7, [r4]
	ldr r0, [sp, #0x18]
	str r5, [r4, #4]
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x14]
	mov r0, #0x20
	bl FUN_020219F4
	add r1, r4, #0
	add r1, #0x84
	str r0, [r1]
	add r5, #0x9c
	ldrb r0, [r5]
	mov r1, #0
	add r2, r1, #0
	str r0, [r4, #0x10]
	add r0, r4, #0
	add r0, #0x98
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xa0
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xa8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xb0
	str r1, [r0]
	str r1, [r4, #0x2c]
	str r1, [r4, #0x30]
	add r0, r4, #0
_021E3436:
	add r1, r1, #1
	str r2, [r0, #0x34]
	add r0, r0, #4
	cmp r1, #8
	blt _021E3436
	add r0, r4, #0
	mov r1, #0
_021E3444:
	add r2, r2, #1
	str r1, [r0, #0x54]
	add r0, r0, #4
	cmp r2, #0xa
	blt _021E3444
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	bl MOD14_021E3464
	str r4, [r6]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E3460:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E3464
MOD14_021E3464: ; 0x021E3464
	push {r4, r5, r6, r7}
	add r1, r0, #0
	mov r2, #0
	add r1, #0xd4
	strb r2, [r1]
	add r1, r0, #0
	mov r4, #0x5a
	mov r3, #0x10
	add r1, #0xe4
	strb r3, [r1]
	ldr r1, _021E34BC ; =0x020EDF50
	mov r3, #1
	lsl r4, r4, #8
	mov r6, #0x10
_021E3480:
	add r2, r2, r4
	asr r5, r2, #0xc
	lsl r5, r5, #2
	ldr r5, [r1, r5]
	lsl r5, r5, #4
	asr r7, r5, #0xc
	add r5, r0, r3
	add r5, #0xd4
	strb r7, [r5]
	add r5, r0, r3
	add r5, #0xd4
	ldrb r5, [r5]
	sub r7, r6, r5
	add r5, r0, r3
	add r5, #0xe4
	add r3, r3, #1
	strb r7, [r5]
	cmp r3, #0xf
	blt _021E3480
	add r1, r0, r3
	add r0, r0, r3
	mov r2, #0x10
	add r1, #0xd4
	strb r2, [r1]
	mov r1, #0
	add r0, #0xe4
	strb r1, [r0]
	pop {r4, r5, r6, r7}
	bx lr
	nop
_021E34BC: .word 0x020EDF50

	thumb_func_start MOD14_021E34C0
MOD14_021E34C0: ; 0x021E34C0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	beq _021E3558
	add r0, #0x88
	bl FUN_02019178
	add r0, r6, #0
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #0
	beq _021E34DA
	bl FUN_02016A18
_021E34DA:
	add r0, r6, #0
	add r0, #0xa0
	ldr r0, [r0]
	cmp r0, #0
	beq _021E34E8
	bl FUN_02016A18
_021E34E8:
	add r0, r6, #0
	add r0, #0xa8
	ldr r0, [r0]
	cmp r0, #0
	beq _021E34F6
	bl FUN_02016A18
_021E34F6:
	add r0, r6, #0
	add r0, #0xb0
	ldr r0, [r0]
	cmp r0, #0
	beq _021E3504
	bl FUN_02016A18
_021E3504:
	ldr r0, [r6, #0x2c]
	cmp r0, #0
	beq _021E350E
	bl FUN_0201FFC8
_021E350E:
	ldr r0, [r6, #0x30]
	cmp r0, #0
	beq _021E3518
	bl FUN_0201FFC8
_021E3518:
	add r0, r6, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	beq _021E3526
	bl FUN_02021A20
_021E3526:
	mov r4, #0
	add r5, r6, #0
_021E352A:
	ldr r0, [r5, #0x34]
	cmp r0, #0
	beq _021E3534
	bl FUN_0201FFC8
_021E3534:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _021E352A
	mov r5, #0
	add r4, r6, #0
_021E3540:
	ldr r0, [r4, #0x54]
	cmp r0, #0
	beq _021E354A
	bl FUN_0201FFC8
_021E354A:
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #0xa
	blt _021E3540
	add r0, r6, #0
	bl FUN_02016A18
_021E3558:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E355C
MOD14_021E355C: ; 0x021E355C
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r0, #0
	beq _021E365C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	ldr r2, [r4, #8]
	mov r0, #0x12
	mov r1, #0x67
	mov r3, #7
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	ldr r2, [r4, #8]
	mov r0, #0x12
	mov r1, #0x64
	mov r3, #7
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	ldr r2, [r4, #8]
	mov r0, #0x12
	mov r1, #0x65
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	ldr r2, [r4, #8]
	mov r0, #0x12
	mov r1, #0x66
	mov r3, #5
	bl FUN_020068C8
	mov r2, #0
	str r2, [sp]
	ldr r0, [r4, #8]
	mov r1, #4
	mov r3, #1
	bl FUN_02017F48
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #8]
	mov r1, #4
	add r3, r2, #0
	bl FUN_02018540
	ldr r0, [r4, #8]
	mov r1, #4
	bl FUN_02017CD0
	ldr r3, [r4, #0x10]
	ldr r0, [r4, #8]
	lsl r5, r3, #2
	ldr r3, _021E3660 ; =0x021E6674
	mov r1, #5
	ldr r3, [r3, r5]
	mov r2, #0
	bl FUN_020179E0
	mov r3, #0
	add r1, r4, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r0, [r4, #8]
	add r1, #0x88
	mov r2, #4
	bl FUN_02019064
	add r0, r4, #0
	add r0, #0x88
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	add r0, #0x88
	bl FUN_020191D0
	add r0, r4, #0
	bl MOD14_021E4764
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0x12
	mov r1, #0x68
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	add r0, r4, #0
	bl MOD14_021E3664
_021E365C:
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_021E3660: .word 0x021E6674

	thumb_func_start MOD14_021E3664
MOD14_021E3664: ; 0x021E3664
	push {r3, r4, lr}
	sub sp, #0x5c
	add r4, r0, #0
	bl MOD14_021E36FC
	add r0, sp, #0x14
	bl FUN_020B1A24
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	add r0, sp, #0x14
	str r0, [sp, #0x10]
	mov r0, #0x12
	mov r1, #0x72
	mov r2, #1
	bl FUN_02006AE4
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	add r3, r4, #0
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	add r3, #0x9c
	add r2, r4, #0
	ldr r3, [r3]
	add r0, sp, #0x38
	add r1, sp, #0x14
	add r2, #0x18
	bl MOD14_021DDDB4
	mov r0, #0x31
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r3, #0x8e
	ldr r0, [r4, #0xc]
	add r1, sp, #0x38
	mov r2, #0
	lsl r3, r3, #2
	bl MOD14_021DDDD4
	str r0, [r4, #0x2c]
	mov r0, #0x31
	mov r3, #0x8e
	str r0, [sp]
	mov r2, #2
	str r2, [sp, #4]
	ldr r0, [r4, #0xc]
	add r1, sp, #0x38
	add r2, #0xfe
	lsl r3, r3, #2
	bl MOD14_021DDDD4
	str r0, [r4, #0x30]
	mov r1, #1
	bl FUN_02020100
	ldr r0, [r4, #4]
	bl MOD14_021DC3C4
	cmp r0, #3
	bne _021E36F6
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_02020130
_021E36F6:
	add sp, #0x5c
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E36FC
MOD14_021E36FC: ; 0x021E36FC
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #0xa
	add r3, r4, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x73
	mov r2, #1
	add r3, #0x9c
	bl FUN_02006C30
	add r1, r4, #0
	add r1, #0x98
	str r0, [r1]
	mov r0, #0xa
	add r3, r4, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x74
	mov r2, #1
	add r3, #0xa4
	bl FUN_02006C5C
	add r1, r4, #0
	add r1, #0xa0
	str r0, [r1]
	mov r0, #0xa
	add r3, r4, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x76
	mov r2, #1
	add r3, #0xac
	bl FUN_02006C30
	add r1, r4, #0
	add r1, #0xa8
	str r0, [r1]
	mov r0, #0xa
	add r3, r4, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x77
	mov r2, #1
	add r3, #0xb4
	bl FUN_02006C5C
	add r1, r4, #0
	add r1, #0xb0
	str r0, [r1]
	add r0, r4, #0
	add r0, #0x18
	bl FUN_020B19DC
	mov r0, #0xa
	str r0, [sp]
	add r4, #0x18
	mov r0, #0x12
	mov r1, #0x78
	mov r2, #2
	mov r3, #0
	str r4, [sp, #4]
	bl FUN_02006A8C
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3784
MOD14_021E3784: ; 0x021E3784
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	mov r2, #0
	bl MOD14_021DDD40
	str r0, [r4, #0x14]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3798
MOD14_021E3798: ; 0x021E3798
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x14]
	pop {r4, pc}

	thumb_func_start MOD14_021E37A8
MOD14_021E37A8: ; 0x021E37A8
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _021E37B2
	mov r0, #1
	bx lr
_021E37B2:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021E37B8
MOD14_021E37B8: ; 0x021E37B8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	beq _021E388A
	ldr r1, [r5, #4]
	add r1, #0x9c
	ldrb r6, [r1]
	ldr r1, [r5, #0x10]
	cmp r1, r6
	beq _021E388A
	add r1, r5, #0
	add r4, r5, #0
	add r1, #0xb8
	str r5, [r1]
	add r4, #0xb8
	mov r1, #0
	str r1, [r4, #8]
	str r1, [r4, #4]
	cmp r6, #0
	beq _021E37E8
	cmp r6, #1
	beq _021E3800
	cmp r6, #2
	beq _021E3822
	b _021E384A
_021E37E8:
	mov r1, #8
	strh r1, [r4, #0xc]
	ldr r7, _021E388C ; =MOD14_021E3AB0
	bl MOD14_021E3DD8
	add r0, r5, #0
	bl MOD14_021E3EBC
	add r0, r5, #0
	bl MOD14_021E4764
	b _021E3852
_021E3800:
	mov r0, #8
	strh r0, [r4, #0xc]
	ldr r0, [r5, #0x10]
	cmp r0, #0
	bne _021E380E
	ldr r7, _021E3890 ; =MOD14_021E38AC
	b _021E3816
_021E380E:
	ldrh r0, [r4, #0xc]
	ldr r7, _021E3894 ; =MOD14_021E3984
	add r0, #8
	strh r0, [r4, #0xc]
_021E3816:
	add r0, r5, #0
	bl MOD14_021E3EBC
	ldr r0, [r5, #0x2c]
	str r0, [r4, #8]
	b _021E3852
_021E3822:
	mov r0, #8
	strh r0, [r4, #0xc]
	ldr r0, [r5, #0x10]
	cmp r0, #0
	bne _021E3830
	ldr r7, _021E3890 ; =MOD14_021E38AC
	b _021E3838
_021E3830:
	ldrh r0, [r4, #0xc]
	ldr r7, _021E3894 ; =MOD14_021E3984
	add r0, #8
	strh r0, [r4, #0xc]
_021E3838:
	ldr r0, [r5, #0x30]
	str r0, [r4, #8]
	add r0, r5, #0
	bl MOD14_021E3DD8
	add r0, r5, #0
	bl MOD14_021E4764
	b _021E3852
_021E384A:
	add r0, r4, #0
	bl FUN_02016A18
	pop {r3, r4, r5, r6, r7, pc}
_021E3852:
	str r6, [r5, #0x10]
	ldr r0, [r5, #8]
	mov r1, #5
	bl FUN_02017B48
	lsl r0, r0, #0xc
	ldr r1, _021E3898 ; =0x021E6674
	lsl r2, r6, #2
	str r0, [r4, #0x10]
	ldr r6, [r1, r2]
	ldrh r1, [r4, #0xc]
	sub r0, r6, r0
	bl _s32_div_f
	str r0, [r4, #0x14]
	asr r0, r6, #0xc
	str r0, [r4, #0x18]
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021E3880
	mov r1, #1
	bl FUN_02020130
_021E3880:
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	bl MOD14_021E3784
_021E388A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E388C: .word MOD14_021E3AB0
_021E3890: .word MOD14_021E38AC
_021E3894: .word MOD14_021E3984
_021E3898: .word 0x021E6674

	thumb_func_start MOD14_021E389C
MOD14_021E389C: ; 0x021E389C
	push {r3, lr}
	cmp r0, #0
	beq _021E38A8
	bl MOD14_021E37A8
	pop {r3, pc}
_021E38A8:
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD14_021E38AC
MOD14_021E38AC: ; 0x021E38AC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r0, [r4, #4]
	ldr r5, [r4]
	cmp r0, #3
	bhi _021E3974
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E38C4: ; jump table
	.short _021E38CC - _021E38C4 - 2 ; case 0
	.short _021E38DE - _021E38C4 - 2 ; case 1
	.short _021E3924 - _021E38C4 - 2 ; case 2
	.short _021E3942 - _021E38C4 - 2 ; case 3
_021E38CC:
	ldr r0, [r4, #8]
	bl FUN_02020388
	cmp r0, #0
	bne _021E3974
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_021E38DE:
	ldrh r0, [r4, #0xc]
	cmp r0, #0
	beq _021E3900
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x14]
	mov r2, #0
	add r3, r1, r0
	str r3, [r4, #0x10]
	ldr r0, [r5, #8]
	mov r1, #5
	asr r3, r3, #0xc
	bl FUN_020179E0
	ldrh r0, [r4, #0xc]
	sub r0, r0, #1
	strh r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_021E3900:
	ldr r0, [r5, #8]
	ldr r3, [r4, #0x18]
	mov r1, #5
	mov r2, #0
	bl FUN_020179E0
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021E3978 ; =0x04001050
	mov r1, #4
	mov r2, #8
	mov r3, #0
	bl G2x_SetBlendAlpha_
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_021E3924:
	ldr r3, [r5, #0x10]
	ldr r0, [r5, #8]
	lsl r5, r3, #2
	ldr r3, _021E397C ; =0x021E6668
	mov r1, #6
	ldr r3, [r3, r5]
	mov r2, #0
	bl FUN_020179E0
	mov r0, #0
	strh r0, [r4, #0xe]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_021E3942:
	mov r1, #0xe
	ldrsh r3, [r4, r1]
	add r0, r5, r3
	add r0, #0xd4
	ldrb r2, [r0]
	add r0, r5, r3
	add r0, #0xe4
	ldrb r0, [r0]
	lsl r0, r0, #8
	orr r2, r0
	ldr r0, _021E3980 ; =0x04001052
	strh r2, [r0]
	ldrsh r0, [r4, r1]
	add r0, r0, #1
	strh r0, [r4, #0xe]
	ldrsh r0, [r4, r1]
	cmp r0, #0x10
	blt _021E3974
	ldr r0, [r4, #8]
	mov r1, #0
	bl FUN_02020130
	add r0, r5, #0
	bl MOD14_021E3798
_021E3974:
	pop {r3, r4, r5, pc}
	nop
_021E3978: .word 0x04001050
_021E397C: .word 0x021E6668
_021E3980: .word 0x04001052

	thumb_func_start MOD14_021E3984
MOD14_021E3984: ; 0x021E3984
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r0, [r4, #4]
	ldr r5, [r4]
	cmp r0, #4
	bls _021E3992
	b _021E3AA2
_021E3992:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E399E: ; jump table
	.short _021E39A8 - _021E399E - 2 ; case 0
	.short _021E39CE - _021E399E - 2 ; case 1
	.short _021E3A0C - _021E399E - 2 ; case 2
	.short _021E3A52 - _021E399E - 2 ; case 3
	.short _021E3A70 - _021E399E - 2 ; case 4
_021E39A8:
	ldr r0, [r4, #8]
	bl FUN_02020388
	cmp r0, #0
	bne _021E3AA2
	mov r0, #0
	str r0, [sp]
	ldr r0, _021E3AA4 ; =0x04001050
	mov r1, #4
	mov r2, #8
	mov r3, #0x10
	bl G2x_SetBlendAlpha_
	mov r0, #0xf
	strh r0, [r4, #0xe]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_021E39CE:
	mov r1, #0xe
	ldrsh r0, [r4, r1]
	sub r0, r0, #1
	strh r0, [r4, #0xe]
	ldrsh r3, [r4, r1]
	add r0, r5, r3
	add r0, #0xd4
	ldrb r2, [r0]
	add r0, r5, r3
	add r0, #0xe4
	ldrb r0, [r0]
	lsl r0, r0, #8
	orr r2, r0
	ldr r0, _021E3AA8 ; =0x04001052
	strh r2, [r0]
	ldrsh r0, [r4, r1]
	cmp r0, #0
	bne _021E3AA2
	ldr r3, [r5, #0x10]
	ldr r0, [r5, #8]
	lsl r5, r3, #2
	ldr r3, _021E3AAC ; =0x021E6668
	mov r1, #6
	ldr r3, [r3, r5]
	mov r2, #0
	bl FUN_020179E0
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_021E3A0C:
	ldrh r0, [r4, #0xc]
	cmp r0, #0
	beq _021E3A2E
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x14]
	mov r2, #0
	add r3, r1, r0
	str r3, [r4, #0x10]
	ldr r0, [r5, #8]
	mov r1, #5
	asr r3, r3, #0xc
	bl FUN_020179E0
	ldrh r0, [r4, #0xc]
	sub r0, r0, #1
	strh r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_021E3A2E:
	ldr r0, [r5, #8]
	ldr r3, [r4, #0x18]
	mov r1, #5
	mov r2, #0
	bl FUN_020179E0
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021E3AA4 ; =0x04001050
	mov r1, #4
	mov r2, #8
	mov r3, #0
	bl G2x_SetBlendAlpha_
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_021E3A52:
	ldr r3, [r5, #0x10]
	ldr r0, [r5, #8]
	lsl r5, r3, #2
	ldr r3, _021E3AAC ; =0x021E6668
	mov r1, #6
	ldr r3, [r3, r5]
	mov r2, #0
	bl FUN_020179E0
	mov r0, #0
	strh r0, [r4, #0xe]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_021E3A70:
	mov r1, #0xe
	ldrsh r3, [r4, r1]
	add r0, r5, r3
	add r0, #0xd4
	ldrb r2, [r0]
	add r0, r5, r3
	add r0, #0xe4
	ldrb r0, [r0]
	lsl r0, r0, #8
	orr r2, r0
	ldr r0, _021E3AA8 ; =0x04001052
	strh r2, [r0]
	ldrsh r0, [r4, r1]
	add r0, r0, #1
	strh r0, [r4, #0xe]
	ldrsh r0, [r4, r1]
	cmp r0, #0x10
	blt _021E3AA2
	ldr r0, [r4, #8]
	mov r1, #0
	bl FUN_02020130
	add r0, r5, #0
	bl MOD14_021E3798
_021E3AA2:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E3AA4: .word 0x04001050
_021E3AA8: .word 0x04001052
_021E3AAC: .word 0x021E6668

	thumb_func_start MOD14_021E3AB0
MOD14_021E3AB0: ; 0x021E3AB0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4, #4]
	ldr r0, [r4]
	cmp r1, #3
	bhi _021E3B4C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E3AC8: ; jump table
	.short _021E3AD0 - _021E3AC8 - 2 ; case 0
	.short _021E3ADA - _021E3AC8 - 2 ; case 1
	.short _021E3B12 - _021E3AC8 - 2 ; case 2
	.short _021E3B48 - _021E3AC8 - 2 ; case 3
_021E3AD0:
	mov r1, #0xf
	strh r1, [r4, #0xe]
	ldr r1, [r4, #4]
	add r1, r1, #1
	str r1, [r4, #4]
_021E3ADA:
	mov r2, #0xe
	ldrsh r1, [r4, r2]
	sub r1, r1, #1
	strh r1, [r4, #0xe]
	ldrsh r5, [r4, r2]
	add r1, r0, r5
	add r1, #0xd4
	ldrb r3, [r1]
	add r1, r0, r5
	add r1, #0xe4
	ldrb r1, [r1]
	lsl r1, r1, #8
	orr r3, r1
	ldr r1, _021E3B50 ; =0x04001052
	strh r3, [r1]
	ldrsh r1, [r4, r2]
	cmp r1, #0
	bne _021E3B4C
	mov r2, #0
	ldr r0, [r0, #8]
	mov r1, #6
	add r3, r2, #0
	bl FUN_020179E0
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_021E3B12:
	ldrh r1, [r4, #0xc]
	cmp r1, #0
	beq _021E3B34
	ldr r2, [r4, #0x10]
	ldr r1, [r4, #0x14]
	add r3, r2, r1
	str r3, [r4, #0x10]
	ldr r0, [r0, #8]
	mov r1, #5
	mov r2, #0
	asr r3, r3, #0xc
	bl FUN_020179E0
	ldrh r0, [r4, #0xc]
	sub r0, r0, #1
	strh r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_021E3B34:
	ldr r0, [r0, #8]
	ldr r3, [r4, #0x18]
	mov r1, #5
	mov r2, #0
	bl FUN_020179E0
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_021E3B48:
	bl MOD14_021E3798
_021E3B4C:
	pop {r3, r4, r5, pc}
	nop
_021E3B50: .word 0x04001052

	thumb_func_start MOD14_021E3B54
MOD14_021E3B54: ; 0x021E3B54
	push {r4, lr}
	add r4, r0, #0
	beq _021E3B7C
	ldr r1, [r4, #0x10]
	cmp r1, #1
	beq _021E3B66
	cmp r1, #2
	beq _021E3B72
	pop {r4, pc}
_021E3B66:
	bl MOD14_021E3C94
	add r0, r4, #0
	bl MOD14_021E41C0
	pop {r4, pc}
_021E3B72:
	bl MOD14_021E3E1C
	add r0, r4, #0
	bl MOD14_021E44E0
_021E3B7C:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3B80
MOD14_021E3B80: ; 0x021E3B80
	push {r4, lr}
	add r4, r0, #0
	beq _021E3BA2
	bl MOD14_021E37A8
	cmp r0, #0
	beq _021E3B9E
	ldr r0, [r4, #0x10]
	cmp r0, #1
	bne _021E3B9A
	add r0, r4, #0
	bl MOD14_021E4790
_021E3B9A:
	mov r0, #1
	pop {r4, pc}
_021E3B9E:
	mov r0, #0
	pop {r4, pc}
_021E3BA2:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3BA8
MOD14_021E3BA8: ; 0x021E3BA8
	push {r4, lr}
	add r4, r0, #0
	beq _021E3BD0
	ldr r1, [r4, #0x10]
	cmp r1, #1
	beq _021E3BBA
	cmp r1, #2
	beq _021E3BCC
	pop {r4, pc}
_021E3BBA:
	bl MOD14_021E4764
	add r0, r4, #0
	bl MOD14_021E3D38
	add r0, r4, #0
	bl MOD14_021E43E8
	pop {r4, pc}
_021E3BCC:
	bl MOD14_021E46E4
_021E3BD0:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3BD4
MOD14_021E3BD4: ; 0x021E3BD4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl MOD14_021DC46C
	cmp r0, #0
	ble _021E3C04
	add r2, r4, #0
	add r2, #0x80
	ldr r2, [r2]
	add r1, r4, #0
	sub r2, r2, r0
	add r0, r4, #0
	add r0, #0x80
	add r4, #0x80
	str r2, [r0]
	ldr r0, [r4]
	add r1, #0x80
	cmp r0, #0
	bge _021E3C24
	ldr r0, [r1]
	add r0, #0xa
	str r0, [r1]
	pop {r4, pc}
_021E3C04:
	add r2, r4, #0
	add r2, #0x80
	ldr r2, [r2]
	add r1, r4, #0
	sub r2, r2, r0
	add r0, r4, #0
	add r0, #0x80
	add r4, #0x80
	str r2, [r0]
	ldr r0, [r4]
	add r1, #0x80
	cmp r0, #0xa
	blt _021E3C24
	ldr r0, [r1]
	sub r0, #0xa
	str r0, [r1]
_021E3C24:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3C28
MOD14_021E3C28: ; 0x021E3C28
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl MOD14_021DC46C
	add r2, r4, #0
	add r2, #0x80
	ldr r2, [r2]
	add r1, r4, #0
	add r2, r2, r0
	add r0, r4, #0
	add r0, #0x80
	add r4, #0x80
	str r2, [r0]
	ldr r0, [r4]
	add r1, #0x80
	cmp r0, #0
	bge _021E3C54
	ldr r0, [r1]
	add r0, #8
	str r0, [r1]
	pop {r4, pc}
_021E3C54:
	cmp r0, #8
	blt _021E3C5E
	ldr r0, [r1]
	sub r0, #8
	str r0, [r1]
_021E3C5E:
	pop {r4, pc}

	thumb_func_start MOD14_021E3C60
MOD14_021E3C60: ; 0x021E3C60
	push {r4, lr}
	add r4, r0, #0
	beq _021E3C90
	bl MOD14_021E37A8
	cmp r0, #0
	beq _021E3C8C
	ldr r0, [r4, #0x10]
	cmp r0, #1
	bne _021E3C82
	add r0, r4, #0
	bl MOD14_021E4790
	add r0, r4, #0
	bl MOD14_021E3BD4
	b _021E3C88
_021E3C82:
	add r0, r4, #0
	bl MOD14_021E3C28
_021E3C88:
	mov r0, #1
	pop {r4, pc}
_021E3C8C:
	mov r0, #0
	pop {r4, pc}
_021E3C90:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD14_021E3C94
MOD14_021E3C94: ; 0x021E3C94
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	str r0, [sp, #8]
	ldr r0, [r0]
	bl MOD14_021DDD84
	add r7, r0, #0
	ldr r0, [sp, #8]
	ldr r0, [r0, #4]
	bl MOD14_021DC474
	add r4, r0, #3
	cmp r4, #0x12
	blt _021E3CB2
	sub r4, #0x12
_021E3CB2:
	ldr r5, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r5, #0
	str r0, [sp, #0x10]
	add r0, #0x18
	mov r6, #0xc0
	str r0, [sp, #0x10]
_021E3CC2:
	add r0, sp, #0x14
	bl FUN_020B1A24
	add r0, sp, #0x14
	str r0, [sp]
	add r0, r7, #0
	add r1, r4, #0
	add r2, r6, #0
	mov r3, #2
	bl MOD14_021E1FF8
	add r0, r7, #0
	bl MOD14_021E2184
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r2, [sp, #0x10]
	add r0, sp, #0x38
	add r1, sp, #0x14
	bl MOD14_021DDDB4
	mov r0, #0x30
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	mov r3, #0x17
	ldr r0, [r0, #0xc]
	add r1, sp, #0x38
	mov r2, #0x10
	lsl r3, r3, #4
	bl MOD14_021DDDD4
	str r0, [r5, #0x54]
	cmp r0, #0
	bne _021E3D14
	bl ErrorHandling
_021E3D14:
	sub r4, r4, #1
	bpl _021E3D1A
	mov r4, #0x11
_021E3D1A:
	ldr r0, [sp, #0xc]
	add r6, #0x20
	add r0, r0, #1
	add r5, r5, #4
	str r0, [sp, #0xc]
	cmp r0, #0xa
	blt _021E3CC2
	ldr r0, [sp, #8]
	mov r1, #0
	add r0, #0x80
	str r0, [sp, #8]
	str r1, [r0]
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3D38
MOD14_021E3D38: ; 0x021E3D38
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp, #4]
	ldr r0, [r0]
	bl MOD14_021DDD84
	str r0, [sp, #0xc]
	ldr r0, [sp, #4]
	ldr r0, [r0, #4]
	bl MOD14_021DC474
	ldr r1, [sp, #4]
	ldr r2, [r1, #4]
	mov r1, #0xa0
	ldrsh r7, [r2, r1]
	cmp r7, #0
	ble _021E3D74
	sub r0, r0, r7
	add r5, r0, #4
	cmp r5, #0x12
	blt _021E3D64
	sub r5, #0x12
_021E3D64:
	ldr r0, [sp, #4]
	mov r6, #1
	add r0, #0x80
	ldr r0, [r0]
	sub r4, r0, #1
	bpl _021E3D90
	add r4, #0xa
	b _021E3D90
_021E3D74:
	sub r0, r0, r7
	sub r5, r0, #3
	bpl _021E3D7C
	add r5, #0x12
_021E3D7C:
	ldr r0, [sp, #4]
	mov r6, #0
	add r0, #0x80
	ldr r0, [r0]
	mvn r6, r6
	add r4, r0, #6
	cmp r4, #0xa
	blt _021E3D8E
	sub r4, #0xa
_021E3D8E:
	neg r7, r7
_021E3D90:
	ldr r0, [sp, #4]
	str r7, [r0, #0x7c]
	mov r0, #0
	str r0, [sp, #8]
	cmp r7, #0
	ble _021E3DD4
_021E3D9C:
	mov r0, #0
	str r0, [sp]
	lsl r2, r4, #5
	ldr r0, [sp, #0xc]
	add r1, r5, #0
	add r2, #0xc0
	mov r3, #2
	bl MOD14_021E1FF8
	add r5, r5, r6
	bpl _021E3DB6
	mov r5, #0x11
	b _021E3DBC
_021E3DB6:
	cmp r5, #0x12
	blt _021E3DBC
	mov r5, #0
_021E3DBC:
	sub r4, r4, r6
	bpl _021E3DC4
	mov r4, #9
	b _021E3DCA
_021E3DC4:
	cmp r4, #0xa
	blt _021E3DCA
	mov r4, #0
_021E3DCA:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, r7
	blt _021E3D9C
_021E3DD4:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E3DD8
MOD14_021E3DD8: ; 0x021E3DD8
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_021E3DE0:
	ldr r0, [r5, #0x54]
	cmp r0, #0
	beq _021E3DEC
	bl FUN_0201FFC8
	str r6, [r5, #0x54]
_021E3DEC:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xa
	blt _021E3DE0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3DF8
MOD14_021E3DF8: ; 0x021E3DF8
	cmp r0, #0
	bne _021E3E08
	cmp r1, #0
	bne _021E3E04
	mov r0, #1
	bx lr
_021E3E04:
	mov r0, #0
	bx lr
_021E3E08:
	mov r3, #1
	sub r2, r0, #1
	lsl r3, r2
	tst r1, r3
	beq _021E3E18
	lsl r0, r0, #1
	add r0, r0, #1
	bx lr
_021E3E18:
	lsl r0, r0, #1
	bx lr

	thumb_func_start MOD14_021E3E1C
MOD14_021E3E1C: ; 0x021E3E1C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x60
	add r5, r0, #0
	ldr r0, [r5, #4]
	bl MOD14_021DC484
	str r0, [sp, #0x14]
	add r0, sp, #0x18
	bl FUN_020B1A24
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #6
	lsl r0, r0, #0xa
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	add r0, sp, #0x18
	str r0, [sp, #0x10]
	mov r0, #0x12
	mov r1, #0x75
	mov r2, #1
	bl FUN_02006AE4
	add r7, r5, #0
	mov r6, #0
	add r4, r5, #0
	add r7, #0x18
_021E3E58:
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r3, r5, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r3, #0xac
	ldr r3, [r3]
	add r0, sp, #0x3c
	add r1, sp, #0x18
	add r2, r7, #0
	bl MOD14_021DDDB4
	mov r0, #0x30
	str r0, [sp]
	mov r0, #2
	mov r2, #0xf0
	str r0, [sp, #4]
	add r3, r2, #0
	ldr r0, [r5, #0xc]
	add r1, sp, #0x3c
	add r3, #0x80
	bl MOD14_021DDDD4
	str r0, [r4, #0x34]
	cmp r0, #0
	bne _021E3E94
	bl ErrorHandling
_021E3E94:
	ldr r1, [sp, #0x14]
	add r0, r6, #0
	bl MOD14_021E3DF8
	add r1, r0, #0
	ldr r0, [r4, #0x34]
	bl FUN_02020130
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #8
	blt _021E3E58
	ldr r0, [r5, #4]
	bl MOD14_021DC47C
	add r5, #0x80
	str r0, [r5]
	add sp, #0x60
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3EBC
MOD14_021E3EBC: ; 0x021E3EBC
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_021E3EC4:
	ldr r0, [r5, #0x34]
	cmp r0, #0
	beq _021E3ED0
	bl FUN_0201FFC8
	str r6, [r5, #0x34]
_021E3ED0:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _021E3EC4
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E3EDC
MOD14_021E3EDC: ; 0x021E3EDC
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4, #0x16]
	cmp r0, #0
	beq _021E3EF2
	sub r0, r0, #1
	add sp, #0xc
	strh r0, [r4, #0x16]
	pop {r4, r5, pc}
_021E3EF2:
	ldrh r0, [r4, #0x14]
	cmp r0, #0
	beq _021E3F28
	sub r0, r0, #1
	strh r0, [r4, #0x14]
	ldr r1, [r4, #8]
	ldr r0, [r4, #0x10]
	add r0, r1, r0
	str r0, [r4, #8]
	asr r0, r0, #0xc
	lsl r1, r0, #2
	ldr r0, _021E3F58 ; =0x021E66A8
	ldrsh r0, [r0, r1]
	lsl r0, r0, #0xc
	str r0, [sp]
	ldr r0, _021E3F5C ; =0x021E66AA
	ldrsh r0, [r0, r1]
	add r1, sp, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	bl FUN_02020044
	add sp, #0xc
	pop {r4, r5, pc}
_021E3F28:
	ldr r0, [r4, #0xc]
	asr r0, r0, #0xc
	lsl r1, r0, #2
	ldr r0, _021E3F58 ; =0x021E66A8
	ldrsh r0, [r0, r1]
	lsl r0, r0, #0xc
	str r0, [sp]
	ldr r0, _021E3F5C ; =0x021E66AA
	ldrsh r0, [r0, r1]
	add r1, sp, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	bl FUN_02020044
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021E4010
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021E3F58: .word 0x021E66A8
_021E3F5C: .word 0x021E66AA

	thumb_func_start MOD14_021E3F60
MOD14_021E3F60: ; 0x021E3F60
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4, #0x16]
	cmp r0, #0
	beq _021E3F76
	sub r0, r0, #1
	add sp, #0xc
	strh r0, [r4, #0x16]
	pop {r4, r5, pc}
_021E3F76:
	ldrh r0, [r4, #0x14]
	cmp r0, #0
	beq _021E3FB2
	sub r0, r0, #1
	strh r0, [r4, #0x14]
	ldr r1, [r4, #8]
	ldr r0, [r4, #0x10]
	add r0, r1, r0
	str r0, [r4, #8]
	asr r0, r0, #0xc
	ldr r1, _021E4008 ; =0x021E66A8
	lsl r0, r0, #2
	ldrsh r2, [r1, r0]
	mov r1, #1
	lsl r1, r1, #8
	sub r1, r1, r2
	lsl r1, r1, #0xc
	str r1, [sp]
	ldr r1, _021E400C ; =0x021E66AA
	ldrsh r0, [r1, r0]
	add r1, sp, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	bl FUN_02020044
	add sp, #0xc
	pop {r4, r5, pc}
_021E3FB2:
	ldr r0, [r4, #0xc]
	ldr r1, _021E4008 ; =0x021E66A8
	asr r0, r0, #0xc
	lsl r0, r0, #2
	ldrsh r2, [r1, r0]
	mov r1, #1
	lsl r1, r1, #8
	sub r1, r1, r2
	lsl r1, r1, #0xc
	str r1, [sp]
	ldr r1, _021E400C ; =0x021E66AA
	ldrsh r0, [r1, r0]
	add r1, sp, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	bl FUN_02020044
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _021E3FFC
	ldrh r0, [r4, #0x28]
	add sp, #0xc
	strh r0, [r4, #0x14]
	ldr r0, [r4, #0x1c]
	str r0, [r4, #8]
	ldr r0, [r4, #0x24]
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x20]
	str r0, [r4, #0xc]
	ldrh r0, [r4, #0x2a]
	strh r0, [r4, #0x16]
	mov r0, #0
	str r0, [r4, #0x18]
	pop {r4, r5, pc}
_021E3FFC:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021E4010
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_021E4008: .word 0x021E66A8
_021E400C: .word 0x021E66AA

	thumb_func_start MOD14_021E4010
MOD14_021E4010: ; 0x021E4010
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r1]
	ldr r0, _021E4034 ; =0x000001CB
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _021E4022
	bl ErrorHandling
_021E4022:
	ldr r0, _021E4034 ; =0x000001CB
	ldrb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, r0]
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	nop
_021E4034: .word 0x000001CB

	thumb_func_start MOD14_021E4038
MOD14_021E4038: ; 0x021E4038
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r6, r0, #0
	add r5, r2, #0
	str r3, [sp]
	ldr r4, [sp, #0x20]
	cmp r7, #0
	bne _021E404C
	bl ErrorHandling
_021E404C:
	cmp r4, #0
	beq _021E4052
	sub r4, r4, #1
_021E4052:
	str r6, [r5]
	ldr r0, [sp, #0x1c]
	str r7, [r5, #4]
	strh r0, [r5, #0x14]
	ldr r0, [sp, #0x24]
	strh r4, [r5, #0x16]
	cmp r0, #0
	beq _021E4066
	ldr r4, _021E40A4 ; =MOD14_021E3F60
	b _021E4068
_021E4066:
	ldr r4, _021E40A8 ; =MOD14_021E3EDC
_021E4068:
	ldr r0, [sp]
	ldr r1, _021E40AC ; =0x021E6680
	lsl r0, r0, #1
	ldrh r0, [r1, r0]
	lsl r0, r0, #0xc
	str r0, [r5, #8]
	ldr r0, [sp, #0x18]
	lsl r0, r0, #1
	ldrh r0, [r1, r0]
	lsl r1, r0, #0xc
	str r1, [r5, #0xc]
	ldr r0, [r5, #8]
	sub r0, r1, r0
	ldr r1, [sp, #0x1c]
	bl _s32_div_f
	str r0, [r5, #0x10]
	mov r2, #0
	add r0, r4, #0
	add r1, r5, #0
	str r2, [r5, #0x18]
	bl MOD14_021DDD40
	cmp r0, #0
	beq _021E40A2
	ldr r0, _021E40B0 ; =0x000001CB
	ldrb r1, [r6, r0]
	add r1, r1, #1
	strb r1, [r6, r0]
_021E40A2:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E40A4: .word MOD14_021E3F60
_021E40A8: .word MOD14_021E3EDC
_021E40AC: .word 0x021E6680
_021E40B0: .word 0x000001CB

	thumb_func_start MOD14_021E40B4
MOD14_021E40B4: ; 0x021E40B4
	push {r4, lr}
	add r4, r1, #0
	mov r0, #1
	str r0, [r4, #0x18]
	strh r2, [r4, #0x2a]
	cmp r2, #0
	beq _021E40C8
	ldrh r0, [r4, #0x2a]
	sub r0, r0, #1
	strh r0, [r4, #0x2a]
_021E40C8:
	ldr r0, [sp, #8]
	sub r2, r0, r3
	bpl _021E40D4
	mov r0, #0
	mvn r0, r0
	mul r2, r0
_021E40D4:
	add r1, r2, #0
	mov r0, #6
	mul r1, r0
	ldr r2, _021E40FC ; =0x021E6680
	lsl r0, r3, #1
	ldrh r0, [r2, r0]
	strh r1, [r4, #0x28]
	lsl r0, r0, #0xc
	str r0, [r4, #0x1c]
	ldr r0, [sp, #8]
	lsl r0, r0, #1
	ldrh r0, [r2, r0]
	lsl r2, r0, #0xc
	str r2, [r4, #0x20]
	ldr r0, [r4, #0x1c]
	sub r0, r2, r0
	bl _s32_div_f
	str r0, [r4, #0x24]
	pop {r4, pc}
	.align 2, 0
_021E40FC: .word 0x021E6680

	thumb_func_start MOD14_021E4100
MOD14_021E4100: ; 0x021E4100
	push {r4, r5, r6, lr}
	sub sp, #0x10
	mov r0, #0x73
	add r4, r1, #0
	lsl r0, r0, #2
	ldrb r3, [r4, r0]
	ldr r2, [r4]
	cmp r3, #0
	beq _021E411E
	cmp r3, #1
	beq _021E4180
	cmp r3, #2
	beq _021E4198
	add sp, #0x10
	pop {r4, r5, r6, pc}
_021E411E:
	sub r1, r0, #2
	ldrb r1, [r4, r1]
	mov r6, #0x2c
	add r3, r1, #1
	sub r1, r0, #2
	strb r3, [r4, r1]
	sub r0, r0, #2
	ldrb r3, [r4, r0]
	mov r1, #6
	mov r0, #7
	sub r5, r1, r3
	sub r0, r0, r3
	str r0, [sp]
	add r0, r5, #1
	mul r1, r0
	str r1, [sp, #4]
	mov r3, #0
	str r3, [sp, #8]
	lsl r1, r5, #2
	add r1, r2, r1
	str r3, [sp, #0xc]
	add r2, r4, #0
	ldr r1, [r1, #0x54]
	add r2, #8
	mul r6, r5
	add r0, r4, #0
	add r2, r2, r6
	bl MOD14_021E4038
	ldr r0, _021E41B0 ; =0x000001CD
	mov r1, #4
	strb r1, [r4, r0]
	sub r1, r0, #3
	ldrb r1, [r4, r1]
	cmp r1, #6
	blo _021E4170
	mov r1, #2
	sub r0, r0, #1
	add sp, #0x10
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E4170:
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021E41AC
	mov r1, #1
	sub r0, r0, #1
	add sp, #0x10
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E4180:
	add r1, r0, #1
	ldrb r1, [r4, r1]
	sub r2, r1, #2
	add r1, r0, #1
	strb r2, [r4, r1]
	ldrb r1, [r4, r1]
	cmp r1, #0
	bne _021E41AC
	mov r1, #0
	add sp, #0x10
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E4198:
	sub r1, r0, #1
	ldrb r1, [r4, r1]
	cmp r1, #0
	bne _021E41AC
	add r1, r3, #1
	strb r1, [r4, r0]
	ldr r1, _021E41B4 ; =MOD14_021E41B8
	add r0, r4, #0
	bl MOD14_021DDF30
_021E41AC:
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021E41B0: .word 0x000001CD
_021E41B4: .word MOD14_021E41B8

	thumb_func_start MOD14_021E41B8
MOD14_021E41B8: ; 0x021E41B8
	ldr r3, _021E41BC ; =MOD14_021E3798
	bx r3
	.align 2, 0
_021E41BC: .word MOD14_021E3798

	thumb_func_start MOD14_021E41C0
MOD14_021E41C0: ; 0x021E41C0
	push {r3, r4, r5, lr}
	mov r1, #0x1d
	add r4, r0, #0
	mov r0, #0xa
	lsl r1, r1, #4
	bl FUN_02016998
	add r5, r0, #0
	beq _021E4208
	mov r1, #0x73
	mov r0, #0
	lsl r1, r1, #2
	str r4, [r5]
	strb r0, [r5, r1]
	sub r2, r1, #2
	strb r0, [r5, r2]
	sub r1, r1, #1
	strb r0, [r5, r1]
	mov r1, #7
	add r3, r0, #0
	lsl r1, r1, #6
_021E41EA:
	add r2, r5, r0
	add r0, r0, #1
	strb r3, [r2, r1]
	cmp r0, #8
	blt _021E41EA
	ldr r1, _021E420C ; =MOD14_021E4100
	add r0, r4, #0
	add r2, r5, #0
	bl MOD14_021E3784
	cmp r0, #0
	bne _021E4208
	add r0, r5, #0
	bl FUN_02016A18
_021E4208:
	pop {r3, r4, r5, pc}
	nop
_021E420C: .word MOD14_021E4100

	thumb_func_start MOD14_021E4210
MOD14_021E4210: ; 0x021E4210
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	mov r2, #0x73
	lsl r2, r2, #2
	add r0, r1, #0
	ldrb r3, [r0, r2]
	str r1, [sp, #0x10]
	ldr r7, [r1]
	cmp r3, #0
	beq _021E422E
	cmp r3, #1
	bne _021E422A
	b _021E43C6
_021E422A:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
_021E422E:
	ldr r1, [r7, #4]
	mov r0, #0xa0
	ldrsh r0, [r1, r0]
	cmp r0, #0
	ble _021E4252
	add r0, r7, #0
	add r0, #0x80
	ldr r0, [r0]
	add r4, r0, #5
	cmp r4, #0xa
	blt _021E4246
	sub r4, #0xa
_021E4246:
	mov r5, #0
	mov r0, #7
	mvn r5, r5
	mov r6, #6
	str r0, [sp, #0x24]
	b _021E4260
_021E4252:
	add r0, r7, #0
	add r0, #0x80
	ldr r4, [r0]
	mov r5, #1
	mov r0, #0
	add r6, r5, #0
	str r0, [sp, #0x24]
_021E4260:
	ldr r1, [r7, #0x7c]
	mov r0, #0
	str r0, [sp, #0x34]
	cmp r1, #0
	ble _021E42C2
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x10]
	str r0, [sp, #0x38]
	add r0, #8
	str r0, [sp, #0x38]
_021E4274:
	ldr r0, [sp, #0x24]
	add r3, r4, #0
	str r0, [sp]
	ldr r0, [sp, #0x28]
	add r0, r0, #6
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	add r1, r0, #0
	ldr r2, [r1, #4]
	lsl r1, r4, #2
	ldr r1, [r2, r1]
	mov r2, #0x2c
	mul r3, r2
	ldr r2, [sp, #0x38]
	add r2, r2, r3
	add r3, r6, #0
	bl MOD14_021E4038
	add r4, r4, r5
	add r6, r6, r5
	cmp r4, #0xa
	blt _021E42AA
	mov r4, #0
	b _021E42B0
_021E42AA:
	cmp r4, #0
	bge _021E42B0
	mov r4, #9
_021E42B0:
	ldr r0, [sp, #0x28]
	ldr r1, [r7, #0x7c]
	add r0, r0, #6
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x34]
	add r0, r0, #1
	str r0, [sp, #0x34]
	cmp r0, r1
	blt _021E4274
_021E42C2:
	mov r0, #6
	sub r0, r0, r1
	str r0, [sp, #0x30]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x30]
	cmp r0, #0
	ble _021E4328
	ldr r0, [sp, #0x10]
	str r0, [sp, #0x3c]
	add r0, #8
	str r0, [sp, #0x3c]
_021E42DA:
	ldr r0, [r7, #0x7c]
	add r1, r5, #0
	mul r1, r0
	sub r1, r6, r1
	str r1, [sp]
	mov r1, #6
	mul r1, r0
	str r1, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	add r3, r4, #0
	add r1, r0, #0
	ldr r2, [r1, #4]
	lsl r1, r4, #2
	ldr r1, [r2, r1]
	mov r2, #0x2c
	mul r3, r2
	ldr r2, [sp, #0x3c]
	add r2, r2, r3
	add r3, r6, #0
	bl MOD14_021E4038
	add r4, r4, r5
	add r6, r6, r5
	cmp r4, #0xa
	blt _021E4316
	mov r4, #0
	b _021E431C
_021E4316:
	cmp r4, #0
	bge _021E431C
	mov r4, #9
_021E431C:
	ldr r0, [sp, #0x14]
	add r1, r0, #1
	ldr r0, [sp, #0x30]
	str r1, [sp, #0x14]
	cmp r1, r0
	blt _021E42DA
_021E4328:
	ldr r1, [r7, #4]
	mov r0, #0xa0
	ldrsh r0, [r1, r0]
	cmp r0, #0
	ble _021E433E
	mov r0, #0
	str r0, [sp, #0x1c]
	ldr r0, [r7, #0x7c]
	str r0, [sp, #0x20]
	str r0, [sp, #0x18]
	b _021E434C
_021E433E:
	mov r0, #7
	str r0, [sp, #0x1c]
	ldr r0, [r7, #0x7c]
	ldr r1, [sp, #0x1c]
	str r0, [sp, #0x20]
	sub r0, r1, r0
	str r0, [sp, #0x18]
_021E434C:
	ldr r0, [sp, #0x20]
	mov r6, #0
	cmp r0, #0
	ble _021E43B4
	ldr r0, [sp, #0x10]
	str r6, [sp, #0x2c]
	str r0, [sp, #0x40]
	add r0, #8
	str r0, [sp, #0x40]
_021E435E:
	ldr r0, [sp, #0x18]
	add r3, r4, #0
	str r0, [sp]
	ldr r0, [r7, #0x7c]
	sub r1, r0, r6
	mov r0, #6
	mul r0, r1
	str r0, [sp, #4]
	ldr r0, [sp, #0x2c]
	add r0, r0, #6
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	add r1, r0, #0
	ldr r2, [r1, #4]
	lsl r1, r4, #2
	ldr r1, [r2, r1]
	mov r2, #0x2c
	mul r3, r2
	ldr r2, [sp, #0x40]
	add r2, r2, r3
	ldr r3, [sp, #0x1c]
	bl MOD14_021E4038
	ldr r0, [sp, #0x18]
	add r4, r4, r5
	add r0, r0, r5
	str r0, [sp, #0x18]
	cmp r4, #0xa
	blt _021E43A0
	sub r4, #0xa
	b _021E43A6
_021E43A0:
	cmp r4, #0
	bge _021E43A6
	add r4, #0xa
_021E43A6:
	ldr r0, [sp, #0x2c]
	add r6, r6, #1
	add r0, r0, #6
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x20]
	cmp r6, r0
	blt _021E435E
_021E43B4:
	mov r1, #0x73
	ldr r0, [sp, #0x10]
	lsl r1, r1, #2
	ldrb r0, [r0, r1]
	add r2, r0, #1
	ldr r0, [sp, #0x10]
	add sp, #0x44
	strb r2, [r0, r1]
	pop {r4, r5, r6, r7, pc}
_021E43C6:
	ldr r0, [sp, #0x10]
	sub r1, r2, #1
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _021E43DE
	ldr r0, [sp, #0x10]
	add r1, r3, #1
	strb r1, [r0, r2]
	ldr r1, _021E43E4 ; =MOD14_021E41B8
	add r2, r7, #0
	bl MOD14_021DDF30
_021E43DE:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	nop
_021E43E4: .word MOD14_021E41B8

	thumb_func_start MOD14_021E43E8
MOD14_021E43E8: ; 0x021E43E8
	push {r3, r4, r5, lr}
	mov r1, #0x1d
	add r4, r0, #0
	mov r0, #0xa
	lsl r1, r1, #4
	bl FUN_02016998
	add r5, r0, #0
	beq _021E4436
	add r0, r4, #0
	mov r1, #0x73
	lsl r1, r1, #2
	str r4, [r5]
	add r0, #0x54
	str r0, [r5, #4]
	mov r0, #0
	strb r0, [r5, r1]
	sub r2, r1, #2
	strb r0, [r5, r2]
	sub r1, r1, #1
	strb r0, [r5, r1]
	mov r1, #7
	add r3, r0, #0
	lsl r1, r1, #6
_021E4418:
	add r2, r5, r0
	add r0, r0, #1
	strb r3, [r2, r1]
	cmp r0, #0xa
	blt _021E4418
	ldr r1, _021E4438 ; =MOD14_021E4210
	add r0, r4, #0
	add r2, r5, #0
	bl MOD14_021E3784
	cmp r0, #0
	bne _021E4436
	add r0, r5, #0
	bl FUN_02016A18
_021E4436:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E4438: .word MOD14_021E4210

	thumb_func_start MOD14_021E443C
MOD14_021E443C: ; 0x021E443C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	ldr r0, [r1]
	mov r2, #0x73
	str r0, [sp, #0x18]
	lsl r2, r2, #2
	add r0, r1, #0
	ldrb r3, [r0, r2]
	str r1, [sp, #0x10]
	cmp r3, #0
	beq _021E445A
	cmp r3, #1
	beq _021E44BE
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
_021E445A:
	ldr r0, [sp, #0x18]
	mov r5, #0
	add r0, #0x80
	ldr r4, [r0]
	add r0, r1, #0
	str r0, [sp, #0x1c]
	add r0, #8
	mov r7, #6
	str r5, [sp, #0x14]
	mov r6, #0x24
	str r0, [sp, #0x1c]
_021E4470:
	str r7, [sp]
	str r6, [sp, #4]
	ldr r1, [sp, #0x18]
	lsl r2, r4, #2
	add r1, r1, r2
	str r5, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r2, #0x2c
	add r3, r4, #0
	mul r3, r2
	ldr r2, [sp, #0x1c]
	ldr r0, [sp, #0x10]
	add r2, r2, r3
	ldr r1, [r1, #0x34]
	mov r3, #0
	bl MOD14_021E4038
	add r4, r4, #1
	sub r6, r6, #6
	sub r7, r7, #1
	cmp r4, #8
	blt _021E44A0
	mov r4, #0
_021E44A0:
	ldr r0, [sp, #0x14]
	add r5, r5, #6
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, #6
	blt _021E4470
	mov r1, #0x73
	ldr r0, [sp, #0x10]
	lsl r1, r1, #2
	ldrb r0, [r0, r1]
	add r2, r0, #1
	ldr r0, [sp, #0x10]
	add sp, #0x20
	strb r2, [r0, r1]
	pop {r3, r4, r5, r6, r7, pc}
_021E44BE:
	ldr r0, [sp, #0x10]
	sub r1, r2, #1
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _021E44D6
	ldr r0, [sp, #0x10]
	add r1, r3, #1
	strb r1, [r0, r2]
	ldr r1, _021E44DC ; =MOD14_021E41B8
	ldr r2, [sp, #0x18]
	bl MOD14_021DDF30
_021E44D6:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E44DC: .word MOD14_021E41B8

	thumb_func_start MOD14_021E44E0
MOD14_021E44E0: ; 0x021E44E0
	push {r3, r4, r5, lr}
	mov r1, #0x1d
	add r4, r0, #0
	mov r0, #0xa
	lsl r1, r1, #4
	bl FUN_02016998
	add r5, r0, #0
	beq _021E4528
	mov r1, #0x73
	mov r0, #0
	lsl r1, r1, #2
	str r4, [r5]
	strb r0, [r5, r1]
	sub r2, r1, #2
	strb r0, [r5, r2]
	sub r1, r1, #1
	strb r0, [r5, r1]
	mov r1, #7
	add r3, r0, #0
	lsl r1, r1, #6
_021E450A:
	add r2, r5, r0
	add r0, r0, #1
	strb r3, [r2, r1]
	cmp r0, #8
	blt _021E450A
	ldr r1, _021E452C ; =MOD14_021E443C
	add r0, r4, #0
	add r2, r5, #0
	bl MOD14_021E3784
	cmp r0, #0
	bne _021E4528
	add r0, r5, #0
	bl FUN_02016A18
_021E4528:
	pop {r3, r4, r5, pc}
	nop
_021E452C: .word MOD14_021E443C

	thumb_func_start MOD14_021E4530
MOD14_021E4530: ; 0x021E4530
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	ldr r0, [r1]
	mov r2, #0x73
	str r0, [sp, #0x34]
	lsl r2, r2, #2
	add r0, r1, #0
	ldrb r3, [r0, r2]
	str r1, [sp, #0x10]
	cmp r3, #0
	beq _021E4550
	cmp r3, #1
	bne _021E454C
	b _021E46C2
_021E454C:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
_021E4550:
	ldr r0, [sp, #0x34]
	ldr r0, [r0, #4]
	bl MOD14_021DC46C
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x34]
	add r0, #0x80
	ldr r4, [r0]
	ldr r0, [sp, #0x30]
	cmp r0, #0
	bge _021E4580
	add r4, r4, #5
	cmp r4, #8
	blt _021E456E
	sub r4, #8
_021E456E:
	ldr r0, [sp, #0x30]
	mov r5, #0
	neg r0, r0
	str r0, [sp, #0x28]
	mov r0, #0
	mvn r5, r5
	mov r6, #1
	str r0, [sp, #0x18]
	b _021E458A
_021E4580:
	str r0, [sp, #0x28]
	mov r0, #7
	mov r5, #1
	mov r6, #6
	str r0, [sp, #0x18]
_021E458A:
	ldr r0, [sp, #0x28]
	mov r7, #0
	add r0, r0, #6
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x28]
	cmp r0, #0
	ble _021E45EC
	ldr r0, [sp, #0x10]
	str r7, [sp, #0x1c]
	str r0, [sp, #0x38]
	add r0, #8
	str r0, [sp, #0x38]
_021E45A2:
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x34]
	str r0, [sp]
	ldr r0, [sp, #0x1c]
	lsl r2, r4, #2
	add r0, r0, #6
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	add r1, r1, r2
	str r0, [sp, #0xc]
	mov r2, #0x2c
	add r3, r4, #0
	mul r3, r2
	ldr r2, [sp, #0x38]
	ldr r0, [sp, #0x10]
	add r2, r2, r3
	ldr r1, [r1, #0x34]
	add r3, r6, #0
	bl MOD14_021E4038
	sub r6, r6, r5
	add r4, r4, r5
	bpl _021E45D8
	add r4, #8
	b _021E45DE
_021E45D8:
	cmp r4, #8
	blt _021E45DE
	sub r4, #8
_021E45DE:
	ldr r0, [sp, #0x1c]
	add r7, r7, #1
	add r0, r0, #6
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x28]
	cmp r7, r0
	blt _021E45A2
_021E45EC:
	mov r0, #0
	str r0, [sp, #0x24]
	cmp r7, #8
	bge _021E4658
	ldr r0, [sp, #0x28]
	mov r1, #6
	mul r1, r0
	ldr r0, [sp, #0x10]
	str r1, [sp, #0x20]
	str r0, [sp, #0x3c]
	add r0, #8
	str r0, [sp, #0x3c]
_021E4604:
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x34]
	sub r0, r0, r5
	str r0, [sp, #0x18]
	str r0, [sp]
	ldr r0, [sp, #0x20]
	lsl r2, r4, #2
	str r0, [sp, #4]
	ldr r0, [sp, #0x24]
	add r1, r1, r2
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r2, #0x2c
	add r3, r4, #0
	mul r3, r2
	ldr r2, [sp, #0x3c]
	ldr r0, [sp, #0x10]
	add r2, r2, r3
	ldr r1, [r1, #0x34]
	add r3, r6, #0
	bl MOD14_021E4038
	cmp r6, #0
	beq _021E463E
	cmp r6, #7
	beq _021E463E
	sub r6, r6, r5
	b _021E4644
_021E463E:
	ldr r0, [sp, #0x24]
	add r0, r0, #6
	str r0, [sp, #0x24]
_021E4644:
	add r4, r4, r5
	bpl _021E464C
	add r4, #8
	b _021E4652
_021E464C:
	cmp r4, #8
	blt _021E4652
	sub r4, #8
_021E4652:
	add r7, r7, #1
	cmp r7, #8
	blt _021E4604
_021E4658:
	ldr r0, [sp, #0x30]
	cmp r0, #0
	bge _021E466C
	mov r0, #7
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x28]
	sub r1, r0, #2
	ldr r0, [sp, #0x14]
	sub r6, r0, r1
	b _021E4674
_021E466C:
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x28]
	sub r6, r0, #2
_021E4674:
	ldr r0, [sp, #0x2c]
	cmp r7, r0
	bge _021E46B0
	ldr r0, [sp, #0x10]
	str r0, [sp, #0x40]
	add r0, #8
	str r0, [sp, #0x40]
_021E4682:
	mov r1, #0x2c
	add r2, r4, #0
	mul r2, r1
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #0x10]
	add r1, r1, r2
	ldr r3, [sp, #0x14]
	mov r2, #6
	str r6, [sp]
	bl MOD14_021E40B4
	sub r6, r6, r5
	add r4, r4, r5
	bpl _021E46A2
	add r4, #8
	b _021E46A8
_021E46A2:
	cmp r4, #8
	blt _021E46A8
	sub r4, #8
_021E46A8:
	ldr r0, [sp, #0x2c]
	add r7, r7, #1
	cmp r7, r0
	blt _021E4682
_021E46B0:
	mov r1, #0x73
	ldr r0, [sp, #0x10]
	lsl r1, r1, #2
	ldrb r0, [r0, r1]
	add r2, r0, #1
	ldr r0, [sp, #0x10]
	add sp, #0x44
	strb r2, [r0, r1]
	pop {r4, r5, r6, r7, pc}
_021E46C2:
	ldr r0, [sp, #0x10]
	sub r1, r2, #1
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _021E46DA
	ldr r0, [sp, #0x10]
	add r1, r3, #1
	strb r1, [r0, r2]
	ldr r1, _021E46E0 ; =MOD14_021E41B8
	ldr r2, [sp, #0x34]
	bl MOD14_021DDF30
_021E46DA:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	nop
_021E46E0: .word MOD14_021E41B8

	thumb_func_start MOD14_021E46E4
MOD14_021E46E4: ; 0x021E46E4
	push {r3, r4, r5, lr}
	mov r1, #0x1d
	add r4, r0, #0
	mov r0, #0xa
	lsl r1, r1, #4
	bl FUN_02016998
	add r5, r0, #0
	beq _021E472C
	mov r1, #0x73
	mov r0, #0
	lsl r1, r1, #2
	str r4, [r5]
	strb r0, [r5, r1]
	sub r2, r1, #2
	strb r0, [r5, r2]
	sub r1, r1, #1
	strb r0, [r5, r1]
	mov r1, #7
	add r3, r0, #0
	lsl r1, r1, #6
_021E470E:
	add r2, r5, r0
	add r0, r0, #1
	strb r3, [r2, r1]
	cmp r0, #8
	blt _021E470E
	ldr r1, _021E4730 ; =MOD14_021E4530
	add r0, r4, #0
	add r2, r5, #0
	bl MOD14_021E3784
	cmp r0, #0
	bne _021E472C
	add r0, r5, #0
	bl FUN_02016A18
_021E472C:
	pop {r3, r4, r5, pc}
	nop
_021E4730: .word MOD14_021E4530

	thumb_func_start MOD14_021E4734
MOD14_021E4734: ; 0x021E4734
	push {r4, r5, r6, lr}
	add r5, r0, #0
	beq _021E4762
	ldr r0, [r5, #0x34]
	cmp r0, #0
	beq _021E4762
	ldr r0, [r5, #4]
	bl MOD14_021DC484
	add r6, r0, #0
	mov r4, #0
_021E474A:
	add r0, r4, #0
	add r1, r6, #0
	bl MOD14_021E3DF8
	add r1, r0, #0
	ldr r0, [r5, #0x34]
	bl FUN_02020130
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _021E474A
_021E4762:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021E4764
MOD14_021E4764: ; 0x021E4764
	ldr r3, _021E476C ; =0x0201797D
	mov r0, #4
	mov r1, #0
	bx r3
	.align 2, 0
_021E476C: .word 0x0201797D

	thumb_func_start MOD14_021E4770
MOD14_021E4770: ; 0x021E4770
	push {r3, lr}
	mov r0, #2
	str r0, [sp]
	ldr r0, _021E478C ; =0x04001050
	mov r1, #1
	mov r2, #0x3f
	mov r3, #0xe
	bl G2x_SetBlendAlpha_
	mov r0, #4
	mov r1, #1
	bl FUN_0201797C
	pop {r3, pc}
	.align 2, 0
_021E478C: .word 0x04001050

	thumb_func_start MOD14_021E4790
MOD14_021E4790: ; 0x021E4790
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	ldr r0, [r6, #4]
	bl MOD14_021DC474
	add r4, r0, #3
	cmp r4, #0x12
	blt _021E47A4
	sub r4, #0x12
_021E47A4:
	mov r0, #0
	add r7, r6, #0
	ldr r5, _021E4820 ; =0x021E6690
	str r0, [sp, #0x10]
	add r7, #0x88
_021E47AE:
	ldr r0, [r6, #4]
	add r2, r6, #0
	add r2, #0x84
	ldr r0, [r0]
	ldr r2, [r2]
	add r1, r4, #0
	bl FUN_0206B484
	mov r0, #0x68
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	ldrh r2, [r5]
	ldrh r3, [r5, #2]
	add r0, r7, #0
	mov r1, #0
	bl FUN_020196F4
	mov r0, #2
	ldrsh r0, [r5, r0]
	mov r1, #0
	add r2, r6, #0
	add r0, r0, #2
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E4824 ; =0x00010200
	add r3, r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrsh r3, [r5, r3]
	add r2, #0x84
	ldr r2, [r2]
	add r0, r7, #0
	add r3, r3, #4
	bl FUN_0201BDE0
	sub r4, r4, #1
	bpl _021E4800
	mov r4, #0x11
_021E4800:
	ldr r0, [sp, #0x10]
	add r5, r5, #4
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, #6
	blo _021E47AE
	add r0, r6, #0
	add r0, #0x88
	bl FUN_02019548
	add r0, r6, #0
	bl MOD14_021E4770
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021E4820: .word 0x021E6690
_021E4824: .word 0x00010200

	thumb_func_start MOD14_021E4828
MOD14_021E4828: ; 0x021E4828
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	mov r0, #0xa
	mov r1, #0x3c
	add r6, r2, #0
	str r3, [sp]
	bl FUN_02016998
	add r4, r0, #0
	beq _021E487C
	str r5, [r4, #4]
	ldr r0, [sp]
	str r6, [r4, #8]
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x18]
	str r0, [r4, #0x10]
	add r0, r5, #0
	bl MOD14_021DDD50
	str r0, [r4, #0x14]
	add r0, r5, #0
	bl MOD14_021DDD6C
	str r0, [r4, #0x18]
	mov r0, #0
	str r0, [r4, #0x34]
	add r0, r6, #0
	bl MOD14_021DC3C4
	cmp r0, #3
	bne _021E486C
	mov r0, #1
	b _021E486E
_021E486C:
	mov r0, #0
_021E486E:
	str r0, [r4]
	add r0, r4, #0
	bl MOD14_021E4890
	str r4, [r7]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E487C:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E4880
MOD14_021E4880: ; 0x021E4880
	push {r4, lr}
	add r4, r0, #0
	bl MOD14_021E495C
	add r0, r4, #0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start MOD14_021E4890
MOD14_021E4890: ; 0x021E4890
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	add r6, r0, #0
	ldr r0, [r6]
	cmp r0, #0
	beq _021E4940
	ldr r4, [r6, #0x14]
	ldr r0, [r6, #4]
	bl MOD14_021DDD48
	add r2, r0, #0
	ldr r0, [r4, #0x20]
	add r1, sp, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r3, [r4, #0x1c]
	add r0, sp, #0x34
	bl MOD14_021DDDB4
	mov r0, #1
	add r1, r0, #0
	bl FUN_0206E640
	add r1, r0, #0
	mov r0, #0xa
	str r0, [sp]
	mov r0, #0x10
	mov r2, #0
	add r3, sp, #0xc
	bl FUN_02006BB0
	str r0, [sp, #8]
	cmp r0, #0
	beq _021E4950
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r1, [r0]
	ldr r0, _021E4954 ; =0x00300010
	ldr r4, _021E4958 ; =0x021E68E8
	and r1, r0
	ldr r0, [sp, #0xc]
	mov r7, #0
	str r1, [r0, #8]
	add r5, r6, #0
_021E48EA:
	add r0, sp, #0x10
	bl FUN_020B1A24
	ldr r0, [sp, #0xc]
	ldr r1, [r4]
	mov r2, #1
	add r3, sp, #0x10
	bl FUN_020B1768
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r2, #0
	ldr r0, [r6, #0x10]
	add r1, sp, #0x34
	add r3, r2, #0
	bl MOD14_021DDDD4
	str r0, [r5, #0x1c]
	ldr r1, [r4, #4]
	bl FUN_02020248
	ldr r0, [r5, #0x1c]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r5, #0x1c]
	mov r1, #1
	bl FUN_020200EC
	mov r0, #0
	str r0, [r5, #0x28]
	add r7, r7, #1
	add r4, #8
	add r5, r5, #4
	cmp r7, #3
	blt _021E48EA
	ldr r0, [sp, #8]
	bl FUN_02016A18
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
_021E4940:
	mov r1, #0
	add r0, r1, #0
_021E4944:
	str r0, [r6, #0x1c]
	str r0, [r6, #0x28]
	add r1, r1, #1
	add r6, r6, #4
	cmp r1, #3
	blt _021E4944
_021E4950:
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E4954: .word 0x00300010
_021E4958: .word 0x021E68E8

	thumb_func_start MOD14_021E495C
MOD14_021E495C: ; 0x021E495C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021E4962:
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _021E496C
	bl FUN_0201FFC8
_021E496C:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _021E4962
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E4978
MOD14_021E4978: ; 0x021E4978
	push {r3, r4}
	mov r3, #0
	add r4, r0, #0
_021E497E:
	ldr r2, [r4, #0x28]
	cmp r2, #0
	bne _021E4990
	lsl r2, r3, #2
	add r0, r0, r2
	str r1, [r0, #0x28]
	add r0, r3, #0
	pop {r3, r4}
	bx lr
_021E4990:
	add r3, r3, #1
	add r4, r4, #4
	cmp r3, #3
	blt _021E497E
	mov r0, #0
	mvn r0, r0
	pop {r3, r4}
	bx lr

	thumb_func_start MOD14_021E49A0
MOD14_021E49A0: ; 0x021E49A0
	mov r3, #0
_021E49A2:
	ldr r2, [r0, #0x28]
	cmp r1, r2
	bne _021E49AC
	add r0, r3, #0
	bx lr
_021E49AC:
	add r3, r3, #1
	add r0, r0, #4
	cmp r3, #3
	blt _021E49A2
	mov r0, #0
	mvn r0, r0
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021E49BC
MOD14_021E49BC: ; 0x021E49BC
	lsl r1, r1, #2
	add r0, r0, r1
	str r2, [r0, #0x28]
	bx lr

	thumb_func_start MOD14_021E49C4
MOD14_021E49C4: ; 0x021E49C4
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #0
	beq _021E49D8
	bl MOD14_021E49DC
	add r0, r4, #0
	bl MOD14_021E4A14
_021E49D8:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E49DC
MOD14_021E49DC: ; 0x021E49DC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC430
	add r4, r0, #0
	beq _021E4A12
	add r0, r5, #0
	mov r1, #1
	bl MOD14_021E4978
	add r6, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD14_021E4B58
	add r5, #0x1c
	lsl r4, r6, #2
	ldr r0, [r5, r4]
	mov r1, #6
	bl FUN_02020130
	ldr r0, [r5, r4]
	mov r1, #1
	bl FUN_020200A0
_021E4A12:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021E4A14
MOD14_021E4A14: ; 0x021E4A14
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC538
	add r7, r0, #0
	beq _021E4AC8
	add r0, r5, #0
	mov r1, #3
	bl MOD14_021E4978
	add r6, r0, #0
	ldr r0, [r5, #0x18]
	add r1, sp, #0x10
	bl MOD14_021E0038
	mov r0, #2
	ldr r1, [sp, #0x14]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x14]
	ldr r0, [r5, #8]
	bl MOD14_021DC3CC
	cmp r0, #1
	bne _021E4A50
	mov r0, #1
	str r0, [sp, #0xc]
	b _021E4A54
_021E4A50:
	mov r0, #2
	str r0, [sp, #0xc]
_021E4A54:
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	mov r1, #1
	lsl r4, r6, #3
	bl FUN_0206E640
	mov r2, #0
	ldr r3, _021E4ACC ; =0x021E68E8
	str r2, [sp]
	add r1, r0, #0
	str r2, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	ldr r3, [r3, r4]
	mov r0, #0x10
	bl FUN_02006A34
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	mov r1, #2
	bl FUN_0206E640
	ldr r3, _021E4AD0 ; =0x021E68EC
	add r1, r0, #0
	mov r0, #0x20
	ldr r3, [r3, r4]
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0x10
	mov r2, #1
	lsl r3, r3, #5
	bl FUN_02006930
	ldr r1, [sp, #0xc]
	add r5, #0x1c
	lsl r4, r6, #2
	lsl r1, r1, #0x18
	ldr r0, [r5, r4]
	lsr r1, r1, #0x18
	bl FUN_02020238
	ldr r0, [r5, r4]
	mov r1, #2
	bl MOD14_021DDE24
	ldr r0, [r5, r4]
	add r1, sp, #0x10
	bl FUN_02020044
	ldr r0, [r5, r4]
	mov r1, #0
	bl FUN_02020130
	ldr r0, [r5, r4]
	mov r1, #1
	bl FUN_020200A0
_021E4AC8:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021E4ACC: .word 0x021E68E8
_021E4AD0: .word 0x021E68EC

	thumb_func_start MOD14_021E4AD4
MOD14_021E4AD4: ; 0x021E4AD4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5, #8]
	add r7, r2, #0
	bl MOD14_021DC3CC
	cmp r0, #1
	ldr r0, [r5, #4]
	bne _021E4B1E
	bl MOD14_021DDD60
	add r6, r0, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC3E8
	add r1, r0, #0
	add r0, r6, #0
	add r2, sp, #4
	add r3, sp, #0
	bl MOD14_021E3170
	ldr r0, [sp, #4]
	add r0, #0xa
	lsl r0, r0, #0xc
	str r0, [r4]
	ldr r0, [sp]
	add sp, #8
	add r0, #8
	lsl r0, r0, #0xc
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r7]
	pop {r3, r4, r5, r6, r7, pc}
_021E4B1E:
	bl MOD14_021DDD98
	add r6, r0, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC3D0
	mov r1, #0x18
	add r6, #0x70
	mul r1, r0
	add r0, r6, r1
	add r0, #0xa
	str r0, [r4]
	ldr r0, [r5, #8]
	bl MOD14_021DC3D8
	mov r1, #0x18
	mul r1, r0
	add r1, #0x30
	str r1, [r4, #4]
	ldr r0, [r4]
	lsl r0, r0, #0xc
	str r0, [r4]
	ldr r0, [r4, #4]
	lsl r0, r0, #0xc
	str r0, [r4, #4]
	mov r0, #2
	str r0, [r7]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E4B58
MOD14_021E4B58: ; 0x021E4B58
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r1, #0
	add r5, r0, #0
	add r7, r2, #0
	cmp r4, #0
	blt _021E4BD2
	add r1, sp, #0x10
	add r2, sp, #0xc
	bl MOD14_021E4AD4
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	mov r1, #1
	lsl r6, r4, #3
	bl FUN_0206E640
	mov r2, #0
	ldr r3, _021E4BD8 ; =0x021E68E8
	str r2, [sp]
	add r1, r0, #0
	str r2, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	ldr r3, [r3, r6]
	mov r0, #0x10
	bl FUN_02006A34
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	mov r1, #2
	bl FUN_0206E640
	ldr r3, _021E4BDC ; =0x021E68EC
	add r1, r0, #0
	mov r0, #0x20
	ldr r3, [r3, r6]
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0x10
	mov r2, #1
	lsl r3, r3, #5
	bl FUN_02006930
	ldr r1, [sp, #0xc]
	add r5, #0x1c
	lsl r4, r4, #2
	lsl r1, r1, #0x18
	ldr r0, [r5, r4]
	lsr r1, r1, #0x18
	bl FUN_02020238
	ldr r0, [r5, r4]
	mov r1, #3
	bl MOD14_021DDE24
	ldr r0, [r5, r4]
	add r1, sp, #0x10
	bl FUN_02020044
_021E4BD2:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021E4BD8: .word 0x021E68E8
_021E4BDC: .word 0x021E68EC

	thumb_func_start MOD14_021E4BE0
MOD14_021E4BE0: ; 0x021E4BE0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r1, [r5]
	cmp r1, #0
	beq _021E4C3E
	mov r1, #1
	bl MOD14_021E49A0
	add r4, r0, #0
	bmi _021E4C0A
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #2
	bl MOD14_021E49BC
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x1c]
	mov r1, #2
	bl FUN_02020130
_021E4C0A:
	ldr r0, [r5, #8]
	bl MOD14_021DC430
	add r6, r0, #0
	beq _021E4C3E
	add r0, r5, #0
	mov r1, #1
	bl MOD14_021E4978
	add r4, r0, #0
	bmi _021E4C3E
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD14_021E4B58
	add r5, #0x1c
	lsl r4, r4, #2
	ldr r0, [r5, r4]
	mov r1, #1
	bl FUN_02020130
	ldr r0, [r5, r4]
	mov r1, #1
	bl FUN_020200A0
_021E4C3E:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021E4C40
MOD14_021E4C40: ; 0x021E4C40
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r1, [r5]
	cmp r1, #0
	bne _021E4C4E
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E4C4E:
	mov r1, #1
	bl MOD14_021E49A0
	cmp r0, #0
	blt _021E4C6A
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x1c]
	bl FUN_02020388
	cmp r0, #0
	beq _021E4C6A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021E4C6A:
	add r0, r5, #0
	mov r1, #2
	bl MOD14_021E49A0
	add r4, r0, #0
	bmi _021E4C92
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x1c]
	bl FUN_02020388
	cmp r0, #0
	beq _021E4C88
	mov r0, #0
	pop {r3, r4, r5, pc}
_021E4C88:
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD14_021E49BC
_021E4C92:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E4C98
MOD14_021E4C98: ; 0x021E4C98
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	mov r0, #0xa
	mov r1, #0x34
	add r6, r2, #0
	str r3, [sp]
	bl FUN_02016998
	add r4, r0, #0
	beq _021E4D1A
	lsl r0, r7, #2
	str r5, [r4]
	add r0, r5, r0
	ldr r0, [r0, #0x1c]
	str r0, [r4, #4]
	bl FUN_0202011C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #8
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r2, r4, #0
	ldmia r6!, {r0, r1}
	add r2, #0x14
	stmia r2!, {r0, r1}
	ldr r0, [r6]
	ldr r6, [sp, #0x18]
	str r0, [r2]
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #8]
	sub r0, r1, r0
	add r1, r6, #0
	bl _s32_div_f
	str r0, [r4, #0x20]
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0xc]
	sub r0, r1, r0
	add r1, r6, #0
	bl _s32_div_f
	str r0, [r4, #0x24]
	ldr r0, [sp, #0x18]
	mov r2, #0
	str r0, [r4, #0x2c]
	ldr r0, [sp]
	add r1, r4, #0
	str r0, [r4, #0x28]
	ldr r0, _021E4D1C ; =MOD14_021E4D20
	str r2, [r4, #0x30]
	bl MOD14_021DDD40
	cmp r0, #0
	beq _021E4D14
	ldr r0, [r5, #0x34]
	add r0, r0, #1
	str r0, [r5, #0x34]
	pop {r3, r4, r5, r6, r7, pc}
_021E4D14:
	add r0, r4, #0
	bl FUN_02016A18
_021E4D1A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E4D1C: .word MOD14_021E4D20

	thumb_func_start MOD14_021E4D20
MOD14_021E4D20: ; 0x021E4D20
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x30]
	cmp r0, #0
	beq _021E4D32
	cmp r0, #1
	beq _021E4D68
	pop {r3, r4, r5, pc}
_021E4D32:
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	beq _021E4D58
	ldr r2, [r4, #8]
	ldr r0, [r4, #0x20]
	add r1, #8
	add r0, r2, r0
	str r0, [r4, #8]
	ldr r2, [r4, #0xc]
	ldr r0, [r4, #0x24]
	add r0, r2, r0
	str r0, [r4, #0xc]
	ldr r0, [r4, #4]
	bl FUN_02020044
	ldr r0, [r4, #0x2c]
	sub r0, r0, #1
	str r0, [r4, #0x2c]
	pop {r3, r4, r5, pc}
_021E4D58:
	ldr r0, [r4, #4]
	add r1, #0x14
	bl FUN_02020044
	ldr r0, [r4, #0x30]
	add r0, r0, #1
	str r0, [r4, #0x30]
	pop {r3, r4, r5, pc}
_021E4D68:
	ldr r0, [r4, #4]
	bl FUN_02020388
	cmp r0, #0
	bne _021E4D92
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x28]
	bl MOD14_021DDE24
	ldr r1, [r4]
	ldr r0, [r1, #0x34]
	sub r0, r0, #1
	str r0, [r1, #0x34]
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD14_021DDF30
_021E4D92:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021E4D94
MOD14_021E4D94: ; 0x021E4D94
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r1, [r5]
	cmp r1, #0
	beq _021E4DE2
	mov r1, #1
	bl MOD14_021E49A0
	add r4, r0, #0
	bmi _021E4DE2
	ldr r0, [r5, #0x18]
	add r1, sp, #4
	bl MOD14_021E0038
	mov r0, #2
	ldr r1, [sp, #8]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #3
	bl MOD14_021E49BC
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x1c]
	mov r1, #3
	bl FUN_02020130
	mov r0, #0xc
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #4
	mov r3, #2
	bl MOD14_021E4C98
_021E4DE2:
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E4DE8
MOD14_021E4DE8: ; 0x021E4DE8
	ldr r0, [r0, #0x34]
	cmp r0, #0
	bne _021E4DF2
	mov r0, #1
	bx lr
_021E4DF2:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021E4DF8
MOD14_021E4DF8: ; 0x021E4DF8
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #0
	beq _021E4E22
	mov r1, #1
	bl MOD14_021E49A0
	add r5, r0, #0
	bmi _021E4E22
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #2
	bl MOD14_021E49BC
	lsl r0, r5, #2
	add r0, r4, r0
	ldr r0, [r0, #0x1c]
	mov r1, #2
	bl FUN_02020130
_021E4E22:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021E4E24
MOD14_021E4E24: ; 0x021E4E24
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r1, [r5]
	cmp r1, #0
	beq _021E4E54
	mov r1, #2
	bl MOD14_021E49A0
	add r4, r0, #0
	bmi _021E4E54
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x1c]
	bl FUN_02020388
	cmp r0, #0
	beq _021E4E4A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021E4E4A:
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD14_021E49BC
_021E4E54:
	mov r0, #1
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021E4E58
MOD14_021E4E58: ; 0x021E4E58
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r1, [r5]
	cmp r1, #0
	beq _021E4E9E
	mov r1, #3
	bl MOD14_021E49A0
	add r4, r0, #0
	bmi _021E4E9E
	add r0, r5, #0
	add r1, sp, #8
	add r2, sp, #4
	bl MOD14_021E4AD4
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #1
	bl MOD14_021E49BC
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x1c]
	mov r1, #4
	bl FUN_02020130
	mov r0, #0xc
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #8
	mov r3, #3
	bl MOD14_021E4C98
_021E4E9E:
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E4EA4
MOD14_021E4EA4: ; 0x021E4EA4
	ldr r0, [r0, #0x34]
	cmp r0, #0
	bne _021E4EAE
	mov r0, #1
	bx lr
_021E4EAE:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021E4EB4
MOD14_021E4EB4: ; 0x021E4EB4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r1, [r5]
	cmp r1, #0
	beq _021E4F42
	mov r1, #3
	bl MOD14_021E49A0
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl MOD14_021E49A0
	add r6, r0, #0
	cmp r4, #0
	blt _021E4F42
	cmp r6, #0
	blt _021E4F42
	add r0, r5, #0
	add r1, sp, #8
	add r2, sp, #4
	bl MOD14_021E4AD4
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #1
	bl MOD14_021E49BC
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x1c]
	mov r1, #4
	bl FUN_02020130
	mov r0, #0xc
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #8
	mov r3, #3
	bl MOD14_021E4C98
	ldr r0, [r5, #0x18]
	add r1, sp, #8
	bl MOD14_021E0038
	mov r0, #2
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #3
	bl MOD14_021E49BC
	lsl r0, r6, #2
	add r0, r5, r0
	ldr r0, [r0, #0x1c]
	mov r1, #3
	bl FUN_02020130
	mov r0, #0xc
	str r0, [sp]
	add r0, r5, #0
	add r1, r6, #0
	add r2, sp, #8
	mov r3, #2
	bl MOD14_021E4C98
_021E4F42:
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E4F48
MOD14_021E4F48: ; 0x021E4F48
	ldr r0, [r0, #0x34]
	cmp r0, #0
	bne _021E4F52
	mov r0, #1
	bx lr
_021E4F52:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021E4F58
MOD14_021E4F58: ; 0x021E4F58
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #0
	beq _021E4F9E
	mov r1, #3
	bl MOD14_021E49A0
	add r5, r0, #0
	bmi _021E4F7C
	lsl r0, r5, #2
	add r0, r4, r0
	ldr r0, [r0, #0x1c]
	mov r1, #5
	bl FUN_02020130
	str r5, [r4, #0x38]
	pop {r3, r4, r5, pc}
_021E4F7C:
	add r0, r4, #0
	mov r1, #1
	bl MOD14_021E49A0
	add r5, r0, #0
	bmi _021E4F98
	lsl r0, r5, #2
	add r0, r4, r0
	ldr r0, [r0, #0x1c]
	mov r1, #2
	bl FUN_02020130
	str r5, [r4, #0x38]
	pop {r3, r4, r5, pc}
_021E4F98:
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0x38]
_021E4F9E:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021E4FA0
MOD14_021E4FA0: ; 0x021E4FA0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021E4FD6
	mov r0, #0
	ldr r1, [r4, #0x38]
	mvn r0, r0
	cmp r1, r0
	beq _021E4FD6
	lsl r0, r1, #2
	add r0, r4, r0
	ldr r0, [r0, #0x1c]
	bl FUN_02020388
	cmp r0, #0
	beq _021E4FC6
	mov r0, #0
	pop {r4, pc}
_021E4FC6:
	ldr r1, [r4, #0x38]
	add r0, r4, #0
	mov r2, #0
	bl MOD14_021E49BC
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0x38]
_021E4FD6:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E4FDC
MOD14_021E4FDC: ; 0x021E4FDC
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5]
	cmp r1, #0
	beq _021E5016
	mov r1, #3
	bl MOD14_021E49A0
	add r6, r0, #0
	bmi _021E5016
	ldmia r4!, {r0, r1}
	add r3, sp, #0
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	str r0, [r3]
	mov r0, #2
	ldr r1, [sp, #4]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #4]
	lsl r0, r6, #2
	add r0, r5, r0
	ldr r0, [r0, #0x1c]
	add r1, r2, #0
	bl FUN_02020044
_021E5016:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E501C
MOD14_021E501C: ; 0x021E501C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5]
	cmp r1, #0
	beq _021E5040
	mov r1, #3
	bl MOD14_021E49A0
	cmp r0, #0
	blt _021E5040
	lsl r0, r0, #2
	add r0, r5, r0
	lsl r1, r4, #0x18
	ldr r0, [r0, #0x1c]
	lsr r1, r1, #0x18
	bl FUN_02020238
_021E5040:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E5044
MOD14_021E5044: ; 0x021E5044
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r2, #0
	add r5, r0, #0
	add r0, r7, #0
	add r6, r1, #0
	str r3, [sp, #4]
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021E5064
	mov r0, #0
	str r0, [r5]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E5064:
	mov r1, #0xe1
	mov r0, #0xa
	lsl r1, r1, #2
	bl FUN_02016998
	add r4, r0, #0
	beq _021E50E6
	str r6, [r4, #4]
	ldr r0, [sp, #4]
	str r7, [r4, #8]
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x20]
	str r0, [r4, #0x10]
	add r0, r6, #0
	bl MOD14_021DDD50
	mov r3, #0xda
	str r0, [r4, #0x14]
	mov r0, #0xa
	lsl r3, r3, #2
	str r0, [sp]
	mov r0, #0x12
	mov r1, #7
	mov r2, #1
	add r3, r4, r3
	bl FUN_02006BDC
	mov r3, #0x37
	lsl r3, r3, #4
	str r0, [r4, r3]
	mov r0, #0xa
	sub r3, r3, #4
	str r0, [sp]
	mov r0, #0x12
	mov r1, #8
	mov r2, #1
	add r3, r4, r3
	bl FUN_02006BDC
	mov r1, #0xdd
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp, #0x24]
	mov r2, #0x93
	str r0, [r4, #0x6c]
	mov r0, #1
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #0xa
	bl FUN_0200A86C
	str r0, [r4, #0x70]
	mov r0, #0x20
	mov r1, #0xa
	bl FUN_020219F4
	str r0, [r4, #0x74]
	mov r0, #0xe
	mov r1, #0
	lsl r0, r0, #6
	str r1, [r4, r0]
	add sp, #8
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E50E6:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E50EC
MOD14_021E50EC: ; 0x021E50EC
	push {r4, lr}
	add r4, r0, #0
	beq _021E5124
	mov r0, #0x37
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02016A18
	mov r0, #0xdd
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02016A18
	ldr r0, [r4, #0x70]
	bl FUN_0200A8B8
	add r0, r4, #0
	bl MOD14_021E5C04
	add r0, r4, #0
	bl MOD14_021E5474
	ldr r0, [r4, #0x74]
	bl FUN_02021A20
	add r0, r4, #0
	bl FUN_02016A18
_021E5124:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E5128
MOD14_021E5128: ; 0x021E5128
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	beq _021E5210
	bl MOD14_021E5334
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x12
	mov r1, #0x6c
	mov r3, #5
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x12
	mov r1, #0x69
	mov r3, #5
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x12
	mov r1, #0x6a
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x12
	mov r1, #0x6b
	mov r3, #7
	bl FUN_020068C8
	mov r0, #0x80
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0x12
	mov r1, #0x6d
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	bl FUN_0206B888
	mov r3, #0x80
	add r1, r0, #0
	str r3, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0x13
	mov r2, #5
	bl FUN_02006930
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0xa
	bl FUN_02017F18
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #0xc]
	mov r1, #4
	add r3, r2, #0
	bl FUN_02018540
	add r0, r4, #0
	bl MOD14_021E539C
	add r0, r4, #0
	bl MOD14_021E5400
	ldr r0, [r4, #8]
	bl MOD14_021DC560
	mov r1, #0xde
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, #0xc]
	mov r1, #4
	bl FUN_02017CD0
	add r0, r4, #0
	bl MOD14_021E5A08
_021E5210:
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start MOD14_021E5214
MOD14_021E5214: ; 0x021E5214
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	cmp r5, #0
	beq _021E5268
	ldr r0, [r5, #8]
	bl MOD14_021DC558
	add r4, r0, #0
	cmp r6, #0
	beq _021E5248
	mov r0, #1
	eor r0, r4
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x28]
	mov r1, #2
	bl FUN_02020130
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x28]
	mov r1, #0
	bl FUN_02020130
	b _021E5262
_021E5248:
	mov r1, #1
	eor r0, r1
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x28]
	bl FUN_02020130
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x28]
	mov r1, #0
	bl FUN_02020130
_021E5262:
	add r0, r5, #0
	bl MOD14_021E5334
_021E5268:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E526C
MOD14_021E526C: ; 0x021E526C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD14_021E5C68
	cmp r5, #0
	beq _021E52B8
	ldr r0, [r5, #8]
	bl MOD14_021DC558
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021E5CFC
	ldr r0, [r5, #8]
	bl MOD14_021DC560
	cmp r0, #0
	beq _021E529C
	cmp r0, #1
	beq _021E52A6
	cmp r0, #2
	beq _021E52B0
	pop {r3, r4, r5, pc}
_021E529C:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021E57E4
	pop {r3, r4, r5, pc}
_021E52A6:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021E55B0
	pop {r3, r4, r5, pc}
_021E52B0:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD14_021E5908
_021E52B8:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E52BC
MOD14_021E52BC: ; 0x021E52BC
	mov r0, #1
	bx lr

	thumb_func_start MOD14_021E52C0
MOD14_021E52C0: ; 0x021E52C0
	push {r4, lr}
	add r4, r0, #0
	beq _021E52DE
	mov r1, #0xdf
	mov r2, #0
	lsl r1, r1, #2
	str r2, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl MOD14_021E5504
	ldr r0, [r4, #0xc]
	mov r1, #4
	bl FUN_02017CD0
_021E52DE:
	pop {r4, pc}

	thumb_func_start MOD14_021E52E0
MOD14_021E52E0: ; 0x021E52E0
	push {r4, lr}
	add r4, r0, #0
	beq _021E5330
	mov r1, #0xdf
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	cmp r1, #0
	beq _021E52FA
	cmp r1, #1
	beq _021E530A
	cmp r1, #2
	beq _021E5328
	b _021E532C
_021E52FA:
	bl MOD14_021E539C
	mov r0, #0xdf
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _021E532C
_021E530A:
	bl MOD14_021E5718
	add r0, r4, #0
	bl MOD14_021E549C
	ldr r0, [r4, #0xc]
	mov r1, #4
	bl FUN_02017CD0
	mov r0, #0xdf
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _021E532C
_021E5328:
	mov r0, #1
	pop {r4, pc}
_021E532C:
	mov r0, #0
	pop {r4, pc}
_021E5330:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD14_021E5334
MOD14_021E5334: ; 0x021E5334
	push {r4, r5, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC558
	cmp r0, #0
	bne _021E5348
	mov r0, #0xda
	b _021E534A
_021E5348:
	mov r0, #0xdb
_021E534A:
	lsl r0, r0, #2
	ldr r4, [r5, r0]
	mov r0, #6
	str r0, [sp]
	mov r1, #0x20
	add r0, r4, #0
	mov r2, #0
	str r1, [sp, #4]
	add r0, #0xc
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	str r1, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r5, #0xc]
	mov r1, #2
	add r3, r2, #0
	bl FUN_02018170
	mov r0, #6
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	add r4, #0xc
	str r4, [sp, #8]
	mov r2, #0x1a
	str r2, [sp, #0xc]
	mov r3, #0
	str r3, [sp, #0x10]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r5, #0xc]
	mov r1, #2
	bl FUN_02018170
	ldr r0, [r5, #0xc]
	mov r1, #2
	bl FUN_02017CD0
	add sp, #0x1c
	pop {r4, r5, pc}

	thumb_func_start MOD14_021E539C
MOD14_021E539C: ; 0x021E539C
	push {r3, lr}
	ldr r0, [r0, #8]
	bl MOD14_021DC560
	cmp r0, #0
	beq _021E53B2
	cmp r0, #1
	beq _021E53CC
	cmp r0, #2
	beq _021E53E6
	pop {r3, pc}
_021E53B2:
	mov r0, #5
	mov r1, #1
	bl FUN_0201797C
	mov r0, #6
	mov r1, #0
	bl FUN_0201797C
	mov r0, #7
	mov r1, #0
	bl FUN_0201797C
	pop {r3, pc}
_021E53CC:
	mov r0, #6
	mov r1, #1
	bl FUN_0201797C
	mov r0, #5
	mov r1, #0
	bl FUN_0201797C
	mov r0, #7
	mov r1, #0
	bl FUN_0201797C
	pop {r3, pc}
_021E53E6:
	mov r0, #7
	mov r1, #1
	bl FUN_0201797C
	mov r0, #5
	mov r1, #0
	bl FUN_0201797C
	mov r0, #6
	mov r1, #0
	bl FUN_0201797C
	pop {r3, pc}

	thumb_func_start MOD14_021E5400
MOD14_021E5400: ; 0x021E5400
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r1, #0
	add r2, r7, #0
	add r5, r1, #0
_021E540A:
	add r0, r2, #0
	add r0, #0x84
	add r1, r1, #1
	add r2, #0x10
	str r5, [r0]
	cmp r1, #7
	blt _021E540A
	add r4, r7, #0
	ldr r6, _021E5470 ; =0x021E6940
	add r4, #0x78
_021E541E:
	ldr r0, [r7, #0xc]
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_02019150
	add r0, r4, #0
	bl FUN_02019270
	add r5, r5, #1
	add r6, #8
	add r4, #0x10
	cmp r5, #3
	blo _021E541E
	add r0, r7, #0
	bl MOD14_021E5718
	add r0, r7, #0
	add r0, #0x78
	mov r1, #0
	bl FUN_02019620
	add r0, r7, #0
	add r0, #0x88
	mov r1, #0
	bl FUN_02019620
	add r4, r7, #0
	mov r5, #0
	add r4, #0x78
_021E5458:
	add r0, r4, #0
	bl FUN_02019548
	add r5, r5, #1
	add r4, #0x10
	cmp r5, #3
	blo _021E5458
	add r0, r7, #0
	bl MOD14_021E549C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E5470: .word 0x021E6940

	thumb_func_start MOD14_021E5474
MOD14_021E5474: ; 0x021E5474
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r5, #0
	mov r6, #0
	add r4, #0x78
_021E547E:
	add r0, r5, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	beq _021E548E
	add r0, r4, #0
	bl FUN_02019178
_021E548E:
	add r6, r6, #1
	add r5, #0x10
	add r4, #0x10
	cmp r6, #7
	blt _021E547E
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E549C
MOD14_021E549C: ; 0x021E549C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC560
	add r4, r0, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC560
	cmp r0, #0
	beq _021E54BC
	cmp r0, #1
	beq _021E54D4
	cmp r0, #2
	beq _021E54E6
	b _021E54FC
_021E54BC:
	add r0, r5, #0
	bl MOD14_021E5540
	add r0, r5, #0
	mov r1, #0
	bl MOD14_021E57E4
	add r0, r5, #0
	mov r1, #1
	bl MOD14_021E57E4
	b _021E54FC
_021E54D4:
	add r0, r5, #0
	mov r1, #0
	bl MOD14_021E55B0
	add r0, r5, #0
	mov r1, #1
	bl MOD14_021E55B0
	b _021E54FC
_021E54E6:
	add r0, r5, #0
	bl MOD14_021E56A8
	add r0, r5, #0
	mov r1, #0
	bl MOD14_021E5908
	add r0, r5, #0
	mov r1, #1
	bl MOD14_021E5908
_021E54FC:
	mov r0, #0xde
	lsl r0, r0, #2
	str r4, [r5, r0]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021E5504
MOD14_021E5504: ; 0x021E5504
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #0
	beq _021E5516
	cmp r1, #1
	beq _021E5522
	cmp r1, #2
	beq _021E5532
	pop {r4, pc}
_021E5516:
	bl MOD14_021E5578
	add r0, r4, #0
	bl MOD14_021E57CC
	pop {r4, pc}
_021E5522:
	mov r1, #0
	bl MOD14_021E5688
	add r0, r4, #0
	mov r1, #1
	bl MOD14_021E5688
	pop {r4, pc}
_021E5532:
	bl MOD14_021E56E0
	add r0, r4, #0
	bl MOD14_021E57CC
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E5540
MOD14_021E5540: ; 0x021E5540
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r7, _021E5574 ; =0x021E6930
	str r0, [sp]
	mov r6, #0
	add r5, #0x78
_021E554C:
	add r0, r6, #3
	lsl r4, r0, #4
	ldr r0, [sp]
	add r1, r5, r4
	ldr r0, [r0, #0xc]
	add r2, r7, #0
	bl FUN_02019150
	add r0, r5, r4
	bl FUN_02019270
	add r0, r5, r4
	mov r1, #0
	bl FUN_02019620
	add r6, r6, #1
	add r7, #8
	cmp r6, #2
	blo _021E554C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E5574: .word 0x021E6930

	thumb_func_start MOD14_021E5578
MOD14_021E5578: ; 0x021E5578
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r0, #0x78
	add r5, r0, #0
	mov r6, #3
	add r4, #0x30
	add r5, #0x30
	mov r7, #0
_021E5588:
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	beq _021E55A4
	add r0, r5, #0
	bl FUN_020192B8
	add r0, r5, #0
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0x84
	str r7, [r0]
_021E55A4:
	add r6, r6, #1
	add r4, #0x10
	add r5, #0x10
	cmp r6, #4
	ble _021E5588
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E55B0
MOD14_021E55B0: ; 0x021E55B0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	ldr r0, [r7, #8]
	str r1, [sp]
	bl MOD14_021DC568
	add r4, r0, #0
	ldr r0, [r7, #8]
	bl MOD14_021DC3F0
	add r6, r0, #0
	ldr r0, [r7, #8]
	bl MOD14_021DC558
	ldr r1, [sp]
	cmp r1, r0
	bne _021E55D8
	mov r5, #1
	b _021E55DA
_021E55D8:
	mov r5, #0
_021E55DA:
	ldr r0, [r7, #8]
	ldr r1, [sp]
	bl MOD14_021DC574
	cmp r6, #1
	bne _021E55EA
	cmp r5, #1
	beq _021E55F2
_021E55EA:
	cmp r5, #0
	bne _021E5676
	cmp r0, #1
	bne _021E5676
_021E55F2:
	ldrb r0, [r4, #6]
	cmp r0, #0
	bne _021E5676
	ldr r1, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #0x10]
	mov r0, #0x14
	add r2, r1, #0
	mul r2, r0
	add r5, r7, r2
	mov r2, #1
	eor r1, r2
	mul r0, r1
	ldr r6, _021E5684 ; =0x021E6958
	add r4, #0x16
	add r7, r7, r0
_021E5614:
	ldr r3, [r6]
	ldr r0, [r6, #8]
	ldrh r2, [r4]
	sub r1, r0, r3
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r0, r0, #8
	mul r0, r2
	add r0, r3, r0
	str r0, [sp, #8]
	ldr r3, [r6, #4]
	ldr r0, [r6, #0xc]
	ldrh r2, [r4]
	sub r1, r0, r3
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r0, r0, #8
	mul r0, r2
	add r0, r3, r0
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x34]
	add r1, sp, #8
	bl FUN_02020044
	ldr r0, [r5, #0x34]
	mov r1, #0
	bl MOD14_021DDE24
	ldr r0, [r7, #0x34]
	mov r1, #1
	bl MOD14_021DDE24
	ldr r0, [r5, #0x34]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [sp, #4]
	add r4, r4, #2
	add r0, r0, #1
	add r6, #0x10
	add r5, r5, #4
	add r7, r7, #4
	str r0, [sp, #4]
	cmp r0, #5
	blt _021E5614
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021E5676:
	ldr r1, [sp]
	add r0, r7, #0
	bl MOD14_021E5688
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021E5684: .word 0x021E6958

	thumb_func_start MOD14_021E5688
MOD14_021E5688: ; 0x021E5688
	push {r4, r5, r6, lr}
	mov r2, #0x14
	mov r4, #0
	mul r2, r1
	add r5, r0, r2
	add r6, r4, #0
_021E5694:
	ldr r0, [r5, #0x34]
	add r1, r6, #0
	bl FUN_020200A0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _021E5694
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD14_021E56A8
MOD14_021E56A8: ; 0x021E56A8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r7, _021E56DC ; =0x021E6920
	str r0, [sp]
	mov r6, #0
	add r5, #0x78
_021E56B4:
	add r0, r6, #5
	lsl r4, r0, #4
	ldr r0, [sp]
	add r1, r5, r4
	ldr r0, [r0, #0xc]
	add r2, r7, #0
	bl FUN_02019150
	add r0, r5, r4
	bl FUN_02019270
	add r0, r5, r4
	mov r1, #0
	bl FUN_02019620
	add r6, r6, #1
	add r7, #8
	cmp r6, #2
	blo _021E56B4
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E56DC: .word 0x021E6920

	thumb_func_start MOD14_021E56E0
MOD14_021E56E0: ; 0x021E56E0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r0, #0x78
	add r5, r0, #0
	mov r6, #5
	add r4, #0x50
	add r5, #0x50
	mov r7, #0
_021E56F0:
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	beq _021E570C
	add r0, r5, #0
	bl FUN_020192B8
	add r0, r5, #0
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0x84
	str r7, [r0]
_021E570C:
	add r6, r6, #1
	add r4, #0x10
	add r5, #0x10
	cmp r6, #6
	ble _021E56F0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E5718
MOD14_021E5718: ; 0x021E5718
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r7, r5, #0
	add r7, #0x98
	add r0, r7, #0
	mov r1, #0
	bl FUN_02019620
	ldr r0, [r5, #8]
	bl MOD14_021DC560
	cmp r0, #0
	beq _021E573A
	cmp r0, #2
	beq _021E5786
	b _021E57B8
_021E573A:
	mov r0, #0
	ldr r6, _021E57C4 ; =0x021E6910
	str r0, [sp, #0x10]
	add r4, r0, #0
_021E5742:
	ldrh r1, [r6]
	ldr r0, [r5, #0x6c]
	ldr r2, [r5, #0x74]
	bl FUN_0200A8E0
	mov r0, #0
	ldr r1, [r5, #0x74]
	add r2, r0, #0
	bl FUN_02002E14
	ldrb r1, [r7, #7]
	lsl r1, r1, #3
	sub r0, r1, r0
	lsr r3, r0, #1
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E57C8 ; =0x000F0E00
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x74]
	add r0, r7, #0
	bl FUN_0201BDE0
	ldr r0, [sp, #0x10]
	add r6, r6, #2
	add r0, r0, #1
	add r4, #0x10
	str r0, [sp, #0x10]
	cmp r0, #8
	blo _021E5742
	b _021E57B8
_021E5786:
	ldr r0, [r5, #0x6c]
	ldr r2, [r5, #0x74]
	mov r1, #0x2b
	bl FUN_0200A8E0
	mov r0, #0
	ldr r1, [r5, #0x74]
	add r2, r0, #0
	bl FUN_02002E14
	ldrb r1, [r7, #7]
	lsl r1, r1, #3
	sub r0, r1, r0
	mov r1, #0
	lsr r3, r0, #1
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E57C8 ; =0x000F0E00
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x74]
	add r0, r7, #0
	bl FUN_0201BDE0
_021E57B8:
	add r0, r7, #0
	bl FUN_02019548
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021E57C4: .word 0x021E6910
_021E57C8: .word 0x000F0E00

	thumb_func_start MOD14_021E57CC
MOD14_021E57CC: ; 0x021E57CC
	push {r4, lr}
	add r4, r0, #0
	add r4, #0x98
	add r0, r4, #0
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	bl FUN_02019548
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD14_021E57E4
MOD14_021E57E4: ; 0x021E57E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	add r0, r1, #0
	add r2, r5, #0
	add r0, r0, #3
	add r2, #0x78
	lsl r0, r0, #4
	add r4, r2, r0
	ldr r0, [r5, #8]
	str r1, [sp, #0x10]
	bl MOD14_021DC568
	add r6, r0, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC3F0
	str r0, [sp, #0x18]
	ldr r0, [r5, #8]
	bl MOD14_021DC558
	ldr r1, [sp, #0x10]
	cmp r1, r0
	bne _021E5818
	mov r7, #1
	b _021E581A
_021E5818:
	mov r7, #0
_021E581A:
	ldr r0, [r5, #8]
	ldr r1, [sp, #0x10]
	bl MOD14_021DC574
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r1, #0
	bl FUN_02019620
	ldr r0, [sp, #0x18]
	cmp r0, #1
	bne _021E5836
	cmp r7, #1
	beq _021E5840
_021E5836:
	cmp r7, #0
	bne _021E58FA
	ldr r0, [sp, #0x14]
	cmp r0, #1
	bne _021E58FA
_021E5840:
	ldrb r0, [r6, #6]
	cmp r0, #0
	bne _021E58BA
	mov r0, #0
	ldr r1, [r6, #0x2c]
	add r2, r0, #0
	bl FUN_02002E14
	ldrb r1, [r4, #7]
	lsl r1, r1, #3
	sub r0, r1, r0
	mov r1, #0
	lsr r3, r0, #1
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E5904 ; =0x000F0E00
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r6, #0x2c]
	add r0, r4, #0
	bl FUN_0201BDE0
	mov r7, #0
	add r6, #8
_021E5872:
	mov r0, #1
	str r0, [sp]
	ldrh r1, [r6]
	ldr r0, [r5, #0x74]
	mov r2, #3
	mov r3, #0
	bl FUN_02021B04
	mov r0, #0
	ldr r1, [r5, #0x74]
	add r2, r0, #0
	bl FUN_02002E14
	ldrb r1, [r4, #7]
	lsl r1, r1, #3
	sub r0, r1, r0
	lsr r3, r0, #1
	add r0, r7, #1
	lsl r0, r0, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E5904 ; =0x000F0E00
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x74]
	add r0, r4, #0
	bl FUN_0201BDE0
	add r7, r7, #1
	add r6, r6, #2
	cmp r7, #7
	blt _021E5872
	b _021E58FA
_021E58BA:
	ldr r0, [r5, #0x6c]
	ldr r2, [r5, #0x74]
	mov r1, #0x2c
	bl FUN_0200A8E0
	mov r7, #0
	add r6, r7, #0
_021E58C8:
	mov r0, #0
	ldr r1, [r5, #0x74]
	add r2, r0, #0
	bl FUN_02002E14
	ldrb r1, [r4, #7]
	lsl r1, r1, #3
	sub r0, r1, r0
	lsr r3, r0, #1
	str r6, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E5904 ; =0x000F0E00
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x74]
	add r0, r4, #0
	bl FUN_0201BDE0
	add r7, r7, #1
	add r6, #0x10
	cmp r7, #8
	blt _021E58C8
_021E58FA:
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021E5904: .word 0x000F0E00

	thumb_func_start MOD14_021E5908
MOD14_021E5908: ; 0x021E5908
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	add r0, r1, #0
	add r2, r5, #0
	add r0, r0, #5
	add r2, #0x78
	lsl r0, r0, #4
	add r4, r2, r0
	ldr r0, [r5, #8]
	str r1, [sp, #0x10]
	bl MOD14_021DC568
	add r6, r0, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC3F0
	str r0, [sp, #0x1c]
	ldr r0, [r5, #8]
	bl MOD14_021DC558
	ldr r1, [sp, #0x10]
	cmp r1, r0
	bne _021E593C
	mov r7, #1
	b _021E593E
_021E593C:
	mov r7, #0
_021E593E:
	ldr r0, [r5, #8]
	ldr r1, [sp, #0x10]
	bl MOD14_021DC574
	str r0, [sp, #0x18]
	add r0, r4, #0
	mov r1, #0
	bl FUN_02019620
	ldr r0, [sp, #0x1c]
	cmp r0, #1
	bne _021E595A
	cmp r7, #1
	beq _021E5964
_021E595A:
	cmp r7, #0
	bne _021E59F8
	ldr r0, [sp, #0x18]
	cmp r0, #1
	bne _021E59F8
_021E5964:
	ldrb r0, [r6, #6]
	cmp r0, #0
	bne _021E59B8
	mov r0, #0
	str r0, [sp, #0x14]
	mov r7, #4
_021E5970:
	ldrh r1, [r6, #0x20]
	cmp r1, #0
	beq _021E59A8
	ldr r0, [r5, #0x70]
	ldr r2, [r5, #0x74]
	bl FUN_0200A8E0
	mov r0, #0
	ldr r1, [r5, #0x74]
	add r2, r0, #0
	bl FUN_02002E14
	ldrb r1, [r4, #7]
	lsl r1, r1, #3
	sub r0, r1, r0
	lsr r3, r0, #1
	str r7, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E5A04 ; =0x000F0E00
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x74]
	add r0, r4, #0
	bl FUN_0201BDE0
_021E59A8:
	ldr r0, [sp, #0x14]
	add r6, r6, #2
	add r0, r0, #1
	add r7, #0x18
	str r0, [sp, #0x14]
	cmp r0, #4
	blt _021E5970
	b _021E59F8
_021E59B8:
	ldr r0, [r5, #0x6c]
	ldr r2, [r5, #0x74]
	mov r1, #0x2c
	bl FUN_0200A8E0
	mov r7, #0
	mov r6, #4
_021E59C6:
	mov r0, #0
	ldr r1, [r5, #0x74]
	add r2, r0, #0
	bl FUN_02002E14
	ldrb r1, [r4, #7]
	lsl r1, r1, #3
	sub r0, r1, r0
	lsr r3, r0, #1
	str r6, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E5A04 ; =0x000F0E00
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x74]
	add r0, r4, #0
	bl FUN_0201BDE0
	add r7, r7, #1
	add r6, #0x18
	cmp r7, #4
	blt _021E59C6
_021E59F8:
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E5A04: .word 0x000F0E00

	thumb_func_start MOD14_021E5A08
MOD14_021E5A08: ; 0x021E5A08
	push {r4, r5, r6, r7, lr}
	sub sp, #0x6c
	add r7, r0, #0
	mov r0, #0xa
	add r3, r7, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x6f
	mov r2, #1
	add r3, #0x60
	bl FUN_02006C30
	str r0, [r7, #0x5c]
	mov r0, #0xa
	add r3, r7, #0
	str r0, [sp]
	mov r0, #0x12
	mov r1, #0x70
	mov r2, #1
	add r3, #0x68
	bl FUN_02006C5C
	str r0, [r7, #0x64]
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0x12
	mov r1, #0x71
	mov r2, #5
	mov r3, #0
	bl FUN_02006930
	add r0, sp, #0x48
	bl FUN_020B1A24
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	add r0, sp, #0x48
	str r0, [sp, #0x10]
	mov r0, #0x12
	mov r1, #0x6e
	mov r2, #1
	bl FUN_02006AE4
	str r0, [sp, #0x20]
	ldr r0, [r7, #4]
	bl MOD14_021DDD48
	add r2, r0, #0
	ldr r0, [r7, #0x68]
	add r1, sp, #0x48
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r3, [r7, #0x60]
	add r0, sp, #0x24
	bl MOD14_021DDDB4
	ldr r0, _021E5B5C ; =0x021E6900
	mov r4, #0
	str r0, [sp, #0x1c]
	str r7, [sp, #0x18]
	str r7, [sp, #0x14]
_021E5A92:
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r2, [sp, #0x1c]
	mov r3, #0
	ldrsh r2, [r2, r3]
	ldr r3, [sp, #0x1c]
	mov r5, #2
	ldrsh r3, [r3, r5]
	ldr r0, [r7, #0x10]
	add r1, sp, #0x24
	bl MOD14_021DDDD4
	ldr r1, [sp, #0x18]
	str r0, [r1, #0x28]
	add r1, r4, #0
	bl FUN_02020248
	ldr r0, [sp, #0x18]
	mov r1, #0
	ldr r0, [r0, #0x28]
	bl FUN_02020130
	ldr r5, [sp, #0x14]
	mov r6, #0
_021E5AC6:
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r2, #0
	ldr r0, [r7, #0x10]
	add r1, sp, #0x24
	add r3, r2, #0
	bl MOD14_021DDDD4
	str r0, [r5, #0x34]
	add r1, r4, #5
	bl FUN_02020130
	ldr r0, [r5, #0x34]
	add r1, r4, #0
	bl FUN_02020248
	ldr r0, [r5, #0x34]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #5
	blo _021E5AC6
	ldr r0, [sp, #0x1c]
	add r4, r4, #1
	add r0, r0, #4
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r0, r0, #4
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r0, #0x14
	str r0, [sp, #0x14]
	cmp r4, #2
	blo _021E5A92
	ldr r0, [r7, #0x2c]
	mov r1, #1
	bl FUN_02020100
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r3, #0x23
	ldr r0, [r7, #0x10]
	add r1, sp, #0x24
	mov r2, #0x80
	lsl r3, r3, #4
	bl MOD14_021DDDD4
	str r0, [r7, #0x30]
	mov r1, #3
	bl FUN_02020130
	ldr r0, [r7, #0x30]
	mov r1, #2
	bl FUN_02020248
	ldr r0, _021E5B60 ; =MOD14_021E5D64
	add r1, r7, #0
	mov r2, #1
	bl FUN_0200CA44
	mov r1, #0xe
	lsl r1, r1, #6
	str r0, [r7, r1]
	ldr r1, [sp, #0x20]
	add r0, r7, #0
	bl MOD14_021E5B64
	add sp, #0x6c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021E5B5C: .word 0x021E6900
_021E5B60: .word MOD14_021E5D64

	thumb_func_start MOD14_021E5B64
MOD14_021E5B64: ; 0x021E5B64
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	str r0, [sp, #8]
	ldr r0, [r0, #4]
	str r1, [sp, #0xc]
	bl MOD14_021DDD48
	add r5, r0, #0
	ldr r0, [sp, #8]
	ldr r0, [r0, #0x14]
	bl MOD14_021E0C74
	add r4, r0, #0
	ldr r0, [sp, #8]
	ldr r0, [r0, #0x14]
	bl MOD14_021E0C78
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, sp, #0x10
	add r1, sp, #0x34
	add r2, r5, #0
	add r3, r4, #0
	bl MOD14_021DDDB4
	mov r7, #0
	ldr r4, [sp, #8]
	ldr r5, _021E5BF8 ; =0x021E6908
	add r6, r7, #0
_021E5BA0:
	ldr r0, [sp, #0xc]
	add r0, r0, r6
	str r0, [r4, #0x18]
	add r0, sp, #0x34
	bl FUN_020B1A24
	ldr r2, [r4, #0x18]
	add r0, sp, #0x34
	mov r1, #2
	bl FUN_020B1A1C
	ldr r0, _021E5BFC ; =0x04001000
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _021E5C00 ; =0x00300010
	mov r3, #2
	and r0, r1
	str r0, [sp, #0x54]
	mov r0, #1
	sub r0, r0, r7
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	ldr r0, [r0, #0x10]
	add r1, sp, #0x10
	bl MOD14_021DDDD4
	mov r1, #0
	str r0, [r4, #0x20]
	bl FUN_020200A0
	mov r0, #2
	lsl r0, r0, #8
	add r7, r7, #1
	add r6, r6, r0
	add r4, r4, #4
	add r5, r5, #4
	cmp r7, #2
	blt _021E5BA0
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E5BF8: .word 0x021E6908
_021E5BFC: .word 0x04001000
_021E5C00: .word 0x00300010

	thumb_func_start MOD14_021E5C04
MOD14_021E5C04: ; 0x021E5C04
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r1, #0xe
	lsl r1, r1, #6
	str r0, [sp]
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _021E5C18
	bl FUN_0200CAB4
_021E5C18:
	ldr r6, [sp]
	mov r0, #0
	str r0, [sp, #4]
	add r7, r6, #0
_021E5C20:
	ldr r0, [r6, #0x20]
	bl FUN_0201FFC8
	ldr r0, [r6, #0x28]
	bl FUN_0201FFC8
	mov r4, #0
	add r5, r7, #0
_021E5C30:
	ldr r0, [r5, #0x34]
	bl FUN_0201FFC8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _021E5C30
	ldr r0, [sp, #4]
	add r6, r6, #4
	add r0, r0, #1
	add r7, #0x14
	str r0, [sp, #4]
	cmp r0, #2
	blt _021E5C20
	ldr r0, [sp]
	ldr r0, [r0, #0x30]
	bl FUN_0201FFC8
	ldr r0, [sp]
	ldr r0, [r0, #0x5c]
	bl FUN_02016A18
	ldr r0, [sp]
	ldr r0, [r0, #0x64]
	bl FUN_02016A18
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E5C68
MOD14_021E5C68: ; 0x021E5C68
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC558
	add r4, r0, #0
	ldr r0, [r5, #8]
	add r1, r4, #0
	bl MOD14_021DC568
	lsl r7, r4, #2
	add r6, r0, #0
	add r0, r5, r7
	ldr r4, [r0, #0x20]
	ldr r0, [r6]
	str r0, [sp]
	ldr r0, [r5, #8]
	bl MOD14_021DC3F0
	cmp r0, #0
	beq _021E5CF0
	ldrh r0, [r6, #4]
	ldrb r1, [r6, #7]
	ldrb r2, [r6, #6]
	bl FUN_0206B7BC
	add r6, r0, #0
	ldr r0, [sp]
	bl FUN_0206B688
	add r2, r0, #0
	add r1, r5, #0
	mov r3, #0xa
	ldr r0, [r5, #0x14]
	add r1, #0xe8
	lsl r3, r3, #6
	bl MOD14_021E0BAC
	add r0, r5, #0
	add r0, #0xe8
	add r1, sp, #4
	bl FUN_020B0088
	ldr r0, [sp, #4]
	mov r1, #2
	ldr r0, [r0, #0x14]
	lsl r1, r1, #8
	bl DC_FlushRange
	ldr r0, [sp, #4]
	add r1, r5, r7
	mov r2, #2
	ldr r0, [r0, #0x14]
	ldr r1, [r1, #0x18]
	lsl r2, r2, #8
	bl GXS_LoadOBJ
	add r0, r4, #0
	add r1, r6, #4
	bl FUN_02020248
	add r0, r4, #0
	mov r1, #1
	bl FUN_020200A0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021E5CF0:
	add r0, r4, #0
	mov r1, #0
	bl FUN_020200A0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD14_021E5CFC
MOD14_021E5CFC: ; 0x021E5CFC
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC558
	add r6, r0, #0
	add r1, r5, #0
	add r1, #0x78
	lsl r0, r6, #4
	add r4, r1, r0
	add r0, r4, #0
	mov r1, #0
	bl FUN_02019620
	ldr r0, [r5, #8]
	bl MOD14_021DC3F0
	cmp r0, #0
	beq _021E5D56
	ldr r0, [r5, #8]
	add r1, r6, #0
	bl MOD14_021DC568
	add r5, r0, #0
	mov r0, #0
	ldr r1, [r5, #0x28]
	add r2, r0, #0
	bl FUN_02002E14
	ldrb r1, [r4, #7]
	lsl r1, r1, #3
	sub r0, r1, r0
	mov r1, #0
	lsr r3, r0, #1
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021E5D60 ; =0x000F0E00
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x28]
	add r0, r4, #0
	bl FUN_0201BDE0
_021E5D56:
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021E5D60: .word 0x000F0E00

	thumb_func_start MOD14_021E5D64
MOD14_021E5D64: ; 0x021E5D64
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #8]
	bl MOD14_021DC57C
	add r4, r0, #0
	ldr r0, [r5, #0x30]
	bl FUN_020201DC
	cmp r0, #3
	bne _021E5D88
	cmp r4, #0
	beq _021E5D94
	ldr r0, [r5, #0x30]
	mov r1, #4
	bl FUN_02020130
	pop {r3, r4, r5, pc}
_021E5D88:
	cmp r4, #0
	bne _021E5D94
	ldr r0, [r5, #0x30]
	mov r1, #3
	bl FUN_02020130
_021E5D94:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E5D98
MOD14_021E5D98: ; 0x021E5D98
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r4, #0x74
	add r0, r4, #0
	add r5, r1, #0
	bl MOD14_021E612C
	add r0, r4, #0
	mov r1, #0x36
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x37
	bl MOD14_021E613C
	add r0, r4, #0
	add r0, #0x20
	strb r5, [r0]
	mov r0, #0
	add r4, #0x23
	strb r0, [r4]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021E5DC4
MOD14_021E5DC4: ; 0x021E5DC4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r5, #0
	add r4, #0x74
	add r0, r4, #0
	bl MOD14_021E612C
	add r0, r4, #0
	mov r1, #1
	add r0, #0x23
	strb r1, [r0]
	add r0, r5, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	bhi _021E5DFA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E5DF0: ; jump table
	.short _021E5E70 - _021E5DF0 - 2 ; case 0
	.short _021E5E9A - _021E5DF0 - 2 ; case 1
	.short _021E5DFA - _021E5DF0 - 2 ; case 2
	.short _021E5DFA - _021E5DF0 - 2 ; case 3
	.short _021E5EC4 - _021E5DF0 - 2 ; case 4
_021E5DFA:
	add r0, r5, #0
	bl MOD14_021DC3F4
	cmp r0, #2
	bne _021E5E1C
	add r0, r5, #0
	bl MOD14_021DC3F0
	cmp r0, #0
	beq _021E5E12
	mov r1, #0x24
	b _021E5E14
_021E5E12:
	mov r1, #0x23
_021E5E14:
	add r0, r4, #0
	bl MOD14_021E613C
	b _021E5E24
_021E5E1C:
	add r0, r4, #0
	mov r1, #0x22
	bl MOD14_021E613C
_021E5E24:
	add r0, r4, #0
	mov r1, #0x25
	bl MOD14_021E613C
	add r0, r5, #0
	bl MOD14_021DC42C
	ldrb r0, [r0, #0xf]
	cmp r0, #0
	bne _021E5E40
	add r0, r4, #0
	mov r1, #0x28
	bl MOD14_021E613C
_021E5E40:
	add r0, r5, #0
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021E5E4E
	mov r1, #0x26
	b _021E5E50
_021E5E4E:
	mov r1, #0x27
_021E5E50:
	add r0, r4, #0
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x29
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x2a
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x2b
	bl MOD14_021E613C
	pop {r3, r4, r5, pc}
_021E5E70:
	add r0, r4, #0
	mov r1, #0x27
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x25
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x29
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x2a
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x2b
	bl MOD14_021E613C
	pop {r3, r4, r5, pc}
_021E5E9A:
	add r0, r4, #0
	mov r1, #0x26
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x25
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x29
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x2a
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x2b
	bl MOD14_021E613C
	pop {r3, r4, r5, pc}
_021E5EC4:
	add r0, r5, #0
	bl MOD14_021DC558
	cmp r0, #0
	bne _021E5ED2
	mov r1, #0x34
	b _021E5ED4
_021E5ED2:
	mov r1, #0x35
_021E5ED4:
	add r0, r4, #0
	bl MOD14_021E613C
	add r0, r5, #0
	bl MOD14_021DC3CC
	cmp r0, #0
	bne _021E5EE8
	mov r1, #0x26
	b _021E5EEA
_021E5EE8:
	mov r1, #0x27
_021E5EEA:
	add r0, r4, #0
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x29
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x2b
	bl MOD14_021E613C
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E5F04
MOD14_021E5F04: ; 0x021E5F04
	push {r4, r5, r6, lr}
	add r4, r0, #0
	add r5, r4, #0
	add r5, #0x74
	bl MOD14_021DC538
	add r6, r0, #0
	add r0, r4, #0
	bl MOD14_021DC430
	add r4, r0, #0
	add r0, r5, #0
	bl MOD14_021E612C
	add r0, r5, #0
	mov r1, #1
	add r0, #0x23
	strb r1, [r0]
	cmp r6, #0
	beq _021E5F54
	cmp r4, #0
	beq _021E5F3A
	add r0, r5, #0
	mov r1, #0x31
	bl MOD14_021E613C
	b _021E5F42
_021E5F3A:
	add r0, r5, #0
	mov r1, #0x2e
	bl MOD14_021E613C
_021E5F42:
	add r0, r5, #0
	mov r1, #0x32
	bl MOD14_021E613C
	add r0, r5, #0
	mov r1, #0x30
	bl MOD14_021E613C
	b _021E5F7A
_021E5F54:
	cmp r4, #0
	beq _021E5F72
	add r0, r5, #0
	mov r1, #0x2f
	bl MOD14_021E613C
	add r0, r5, #0
	mov r1, #0x32
	bl MOD14_021E613C
	add r0, r5, #0
	mov r1, #0x30
	bl MOD14_021E613C
	b _021E5F7A
_021E5F72:
	add r0, r5, #0
	mov r1, #0x2e
	bl MOD14_021E613C
_021E5F7A:
	add r0, r5, #0
	mov r1, #0x33
	bl MOD14_021E613C
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021E5F84
MOD14_021E5F84: ; 0x021E5F84
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r5, #0
	add r4, #0x74
	bl MOD14_021DC44C
	add r0, r4, #0
	bl MOD14_021E612C
	add r0, r4, #0
	mov r1, #0
	bl MOD14_021E613C
	add r0, r5, #0
	bl MOD14_021DC3C4
	cmp r0, #4
	beq _021E5FB8
	add r0, r4, #0
	mov r1, #1
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #2
	bl MOD14_021E613C
_021E5FB8:
	add r0, r4, #0
	mov r1, #3
	bl MOD14_021E613C
	mov r0, #2
	add r4, #0x23
	strb r0, [r4]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD14_021E5FC8
MOD14_021E5FC8: ; 0x021E5FC8
	push {r4, r5, r6, lr}
	add r4, r0, #0
	add r4, #0x74
	add r5, r1, #0
	bl MOD14_021DC44C
	add r6, r0, #0
	add r0, r4, #0
	bl MOD14_021E612C
	add r0, r4, #0
	mov r1, #4
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #5
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #6
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #7
	bl MOD14_021E613C
	add r0, r6, #0
	bl FUN_0206B668
	add r6, r0, #0
	beq _021E600E
	add r0, r4, #0
	mov r1, #8
	bl MOD14_021E613C
_021E600E:
	cmp r6, #4
	bls _021E601A
	add r0, r4, #0
	mov r1, #9
	bl MOD14_021E613C
_021E601A:
	add r0, r4, #0
	mov r1, #3
	add r0, #0x23
	strb r1, [r0]
	cmp r5, #4
	blt _021E6032
	cmp r5, #9
	bgt _021E6032
	sub r0, r5, #4
	add r4, #0x20
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_021E6032:
	bl ErrorHandling
	pop {r4, r5, r6, pc}

	thumb_func_start MOD14_021E6038
MOD14_021E6038: ; 0x021E6038
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r6, #0x74
	add r5, r1, #0
	bl MOD14_021DC44C
	str r0, [sp]
	add r0, r6, #0
	bl MOD14_021E612C
	cmp r5, #4
	blt _021E6070
	cmp r5, #7
	bgt _021E6070
	sub r0, r5, #4
	ldr r1, _021E60B0 ; =0x021E69A8
	lsl r0, r0, #3
	mov r5, #0
	add r4, r1, r0
_021E605E:
	ldrh r1, [r4]
	add r0, r6, #0
	bl MOD14_021E613C
	add r5, r5, #1
	add r4, r4, #2
	cmp r5, #4
	blt _021E605E
	b _021E60A6
_021E6070:
	mov r4, #0
	add r7, r4, #0
	cmp r5, #9
	bne _021E607A
	mov r4, #4
_021E607A:
	mov r5, #0
_021E607C:
	ldr r0, [sp]
	add r1, r5, #0
	bl FUN_0206B644
	cmp r0, #0
	beq _021E60A0
	cmp r4, #0
	beq _021E6090
	sub r4, r4, #1
	b _021E60A0
_021E6090:
	add r1, r5, #0
	add r0, r6, #0
	add r1, #0x1a
	bl MOD14_021E613C
	add r7, r7, #1
	cmp r7, #4
	bge _021E60A6
_021E60A0:
	add r5, r5, #1
	cmp r5, #8
	blt _021E607C
_021E60A6:
	mov r0, #3
	add r6, #0x23
	strb r0, [r6]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E60B0: .word 0x021E69A8

	thumb_func_start MOD14_021E60B4
MOD14_021E60B4: ; 0x021E60B4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r5, #0
	add r4, #0x74
	add r0, r4, #0
	bl MOD14_021E612C
	add r0, r4, #0
	mov r1, #4
	add r0, #0x23
	strb r1, [r0]
	add r5, #0x57
	add r0, r4, #0
	ldrb r1, [r5]
	add r0, #0x22
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0x38
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x39
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x3a
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x3b
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x3c
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x3d
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x2c
	bl MOD14_021E613C
	add r0, r4, #0
	mov r1, #0x2d
	bl MOD14_021E613C
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD14_021E6118
MOD14_021E6118: ; 0x021E6118
	add r2, r0, #0
	add r2, #0x96
	ldrb r3, [r2]
	mov r2, #1
	lsl r2, r1
	add r1, r3, #0
	eor r1, r2
	add r0, #0x96
	strb r1, [r0]
	bx lr

	thumb_func_start MOD14_021E612C
MOD14_021E612C: ; 0x021E612C
	add r1, r0, #0
	mov r2, #0
	add r1, #0x21
	strb r2, [r1]
	add r0, #0x20
	strb r2, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021E613C
MOD14_021E613C: ; 0x021E613C
	push {r3, r4}
	add r2, r0, #0
	add r2, #0x21
	ldrb r4, [r2]
	cmp r4, #8
	bhs _021E615A
	add r2, r0, #0
	add r2, #0x21
	ldrb r2, [r2]
	add r3, r2, #1
	add r2, r0, #0
	add r2, #0x21
	strb r3, [r2]
	lsl r2, r4, #2
	str r1, [r0, r2]
_021E615A:
	pop {r3, r4}
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021E6160
MOD14_021E6160: ; 0x021E6160
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, _021E6208 ; =0x021C48B8
	add r4, #0x74
	ldr r1, [r0, #0x48]
	mov r0, #0x40
	add r2, r1, #0
	tst r2, r0
	beq _021E61A0
	add r2, r4, #0
	add r2, #0x20
	ldrb r2, [r2]
	cmp r2, #0
	beq _021E618C
	add r1, r4, #0
	add r1, #0x20
	ldrb r1, [r1]
	add r4, #0x20
	sub r0, #0x42
	sub r1, r1, #1
	strb r1, [r4]
	pop {r3, r4, r5, pc}
_021E618C:
	add r2, r4, #0
	add r2, #0x21
	ldrb r2, [r2]
	cmp r2, #3
	blo _021E61A0
	sub r1, r2, #1
	add r4, #0x20
	strb r1, [r4]
	sub r0, #0x42
	pop {r3, r4, r5, pc}
_021E61A0:
	mov r0, #0x80
	add r2, r1, #0
	tst r2, r0
	beq _021E61D8
	add r2, r4, #0
	add r2, #0x21
	ldrb r5, [r2]
	add r2, r4, #0
	add r2, #0x20
	ldrb r3, [r2]
	sub r2, r5, #1
	cmp r3, r2
	bge _021E61CA
	add r1, r4, #0
	add r1, #0x20
	ldrb r1, [r1]
	add r4, #0x20
	sub r0, #0x82
	add r1, r1, #1
	strb r1, [r4]
	pop {r3, r4, r5, pc}
_021E61CA:
	cmp r5, #3
	blo _021E61D8
	mov r0, #0
	add r4, #0x20
	strb r0, [r4]
	sub r0, r0, #2
	pop {r3, r4, r5, pc}
_021E61D8:
	mov r0, #2
	tst r0, r1
	beq _021E61EA
	ldr r0, _021E620C ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, pc}
_021E61EA:
	mov r0, #1
	tst r1, r0
	beq _021E6202
	ldr r0, _021E620C ; =0x000005DD
	bl FUN_020054C8
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	pop {r3, r4, r5, pc}
_021E6202:
	sub r0, r0, #4
	pop {r3, r4, r5, pc}
	nop
_021E6208: .word 0x021C48B8
_021E620C: .word 0x000005DD

	thumb_func_start MOD14_021E6210
MOD14_021E6210: ; 0x021E6210
	add r0, #0x74
	add r1, r0, #0
	add r1, #0x20
	ldrb r1, [r1]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr
	.align 2, 0

	thumb_func_start MOD14_021E6220
MOD14_021E6220: ; 0x021E6220
	ldr r0, [r0, #0x74]
	bx lr

	.section .rodata
	; 0x021E6224
	.incbin "baserom.nds", 0x236b44, 0x7a4

	.section .data
	; 0x021E69E0
	.incbin "baserom.nds", 0x237300, 0x1C

	.section .bss
	; 0x021E69FC
	.space 0x1A0
