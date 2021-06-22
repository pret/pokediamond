	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD17_021D74E0
MOD17_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r5, r0, #0
	add r0, r7, #0
	mov r1, #8
	bl AllocFromHeap
	lsl r6, r5, #3
	add r4, r0, #0
	add r0, r7, #0
	add r1, r6, #0
	bl AllocFromHeap
	mov r1, #0
	add r2, r6, #0
	str r0, [r4]
	bl memset
	str r5, [r4, #4]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021D74E0

	thumb_func_start MOD17_021D750C
MOD17_021D750C: ; 0x021D750C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D750C

	thumb_func_start MOD17_021D7520
MOD17_021D7520: ; 0x021D7520
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD17_021D76E0
	add r4, r0, #0
	bne _021D7532
	bl GF_AssertFail
_021D7532:
	ldr r0, [r5, #0x18]
	str r0, [r4]
	add r0, r5, #0
	bl MOD17_021D770C
	str r0, [r4, #4]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7520

	thumb_func_start MOD17_021D7544
MOD17_021D7544: ; 0x021D7544
	push {r3, lr}
	add r1, sp, #0
	bl MOD17_021D7740
	add r0, sp, #0
	bl FUN_02020A40
	pop {r3, pc}
	thumb_func_end MOD17_021D7544

	thumb_func_start MOD17_021D7554
MOD17_021D7554: ; 0x021D7554
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r6, r1, #0
	str r2, [sp]
	add r7, r3, #0
	bl MOD17_021D7544
	cmp r0, #0
	bne _021D756E
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021D756E:
	add r0, r4, #0
	add r1, sp, #8
	add r2, sp, #4
	bl MOD17_021D7600
	ldr r0, _021D75D8 ; =gMain + 0x40
	ldr r1, [sp, #8]
	ldrh r2, [r0, #0x1c]
	sub r1, r2, r1
	str r1, [r6]
	ldrh r1, [r0, #0x1e]
	ldr r0, [sp, #4]
	sub r1, r1, r0
	ldr r0, [sp]
	sub r4, r1, #4
	str r1, [r0]
	add r0, r1, #4
	cmp r4, r0
	bge _021D75D2
_021D7594:
	cmp r4, #0
	blt _021D75C6
	ldr r0, [r6]
	sub r5, r0, #4
	add r0, r0, #4
	cmp r5, r0
	bge _021D75C6
_021D75A2:
	cmp r5, #0
	blt _021D75BC
	add r0, r7, #0
	add r1, r5, #0
	add r2, r4, #0
	mov r3, #0
	bl MOD17_021D7B0C
	cmp r0, #0
	bne _021D75BC
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D75BC:
	ldr r0, [r6]
	add r5, r5, #1
	add r0, r0, #4
	cmp r5, r0
	blt _021D75A2
_021D75C6:
	ldr r0, [sp]
	add r4, r4, #1
	ldr r0, [r0]
	add r0, r0, #4
	cmp r4, r0
	blt _021D7594
_021D75D2:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D75D8: .word gMain + 0x40
	thumb_func_end MOD17_021D7554

	thumb_func_start MOD17_021D75DC
MOD17_021D75DC: ; 0x021D75DC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r1, sp, #0
	bl MOD17_021D7740
	add r0, sp, #0
	add r1, r5, #0
	add r2, r4, #0
	bl FUN_02020AE8
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021D75DC

	thumb_func_start MOD17_021D75F4
MOD17_021D75F4: ; 0x021D75F4
	ldr r3, _021D75FC ; =FUN_02013EC4
	ldr r0, [r0, #4]
	bx r3
	nop
_021D75FC: .word FUN_02013EC4
	thumb_func_end MOD17_021D75F4

	thumb_func_start MOD17_021D7600
MOD17_021D7600: ; 0x021D7600
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r0, [r0, #4]
	add r5, r1, #0
	add r4, r2, #0
	bl FUN_02013ECC
	add r1, sp, #0
	strh r0, [r1]
	lsr r0, r0, #0x10
	strh r0, [r1, #2]
	ldrh r0, [r1]
	strh r0, [r1, #4]
	ldrh r0, [r1, #2]
	strh r0, [r1, #6]
	mov r0, #4
	ldrsh r0, [r1, r0]
	str r0, [r5]
	mov r0, #6
	ldrsh r0, [r1, r0]
	str r0, [r4]
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7600

	thumb_func_start MOD17_021D7630
MOD17_021D7630: ; 0x021D7630
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r0, [r0, #4]
	add r5, r1, #0
	add r4, r2, #0
	bl FUN_02013EF0
	add r1, sp, #0
	strh r0, [r1]
	lsr r0, r0, #0x10
	strh r0, [r1, #2]
	ldrh r0, [r1]
	strh r0, [r1, #4]
	ldrh r0, [r1, #2]
	strh r0, [r1, #6]
	mov r0, #4
	ldrsh r0, [r1, r0]
	str r0, [r5]
	mov r0, #6
	ldrsh r0, [r1, r0]
	str r0, [r4]
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7630

	thumb_func_start MOD17_021D7660
MOD17_021D7660: ; 0x021D7660
	ldr r3, _021D7668 ; =FUN_02013EB0
	ldr r0, [r0, #4]
	bx r3
	nop
_021D7668: .word FUN_02013EB0
	thumb_func_end MOD17_021D7660

	thumb_func_start MOD17_021D766C
MOD17_021D766C: ; 0x021D766C
	ldr r3, _021D7674 ; =FUN_02013EFC
	ldr r0, [r0, #4]
	bx r3
	nop
_021D7674: .word FUN_02013EFC
	thumb_func_end MOD17_021D766C

	thumb_func_start MOD17_021D7678
MOD17_021D7678: ; 0x021D7678
	ldr r3, _021D7680 ; =FUN_02013F00
	ldr r0, [r0, #4]
	bx r3
	nop
_021D7680: .word FUN_02013F00
	thumb_func_end MOD17_021D7678

	thumb_func_start MOD17_021D7684
MOD17_021D7684: ; 0x021D7684
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r1, #0
	add r4, r2, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021D7630
	ldr r0, [sp, #4]
	cmp r0, #0x10
	beq _021D76A4
	cmp r0, #0x20
	beq _021D76AA
	cmp r0, #0x40
	beq _021D76B0
	b _021D76B4
_021D76A4:
	mov r0, #0
	str r0, [r5]
	b _021D76B4
_021D76AA:
	mov r0, #0xa
	str r0, [r5]
	b _021D76B4
_021D76B0:
	mov r0, #0x14
	str r0, [r5]
_021D76B4:
	ldr r0, [sp]
	cmp r0, #0x10
	beq _021D76C6
	cmp r0, #0x20
	beq _021D76CE
	cmp r0, #0x40
	beq _021D76D6
	add sp, #8
	pop {r3, r4, r5, pc}
_021D76C6:
	mov r0, #0
	add sp, #8
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D76CE:
	mov r0, #0xa
	add sp, #8
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D76D6:
	mov r0, #0x14
	str r0, [r4]
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7684

	thumb_func_start MOD17_021D76E0
MOD17_021D76E0: ; 0x021D76E0
	push {r3, r4}
	ldr r4, [r0, #4]
	mov r1, #0
	cmp r4, #0
	ble _021D7704
	ldr r3, [r0]
	add r2, r3, #0
_021D76EE:
	ldr r0, [r2, #4]
	cmp r0, #0
	bne _021D76FC
	lsl r0, r1, #3
	add r0, r3, r0
	pop {r3, r4}
	bx lr
_021D76FC:
	add r1, r1, #1
	add r2, #8
	cmp r1, r4
	blt _021D76EE
_021D7704:
	mov r0, #0
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021D76E0

	thumb_func_start MOD17_021D770C
MOD17_021D770C: ; 0x021D770C
	push {r3, lr}
	sub sp, #0x20
	ldr r1, [r0, #4]
	mov r3, #0
	str r1, [sp]
	ldr r1, [r0, #8]
	str r1, [sp, #4]
	ldr r1, [r0, #0xc]
	str r1, [sp, #8]
	ldr r2, [r0, #0x10]
	add r1, sp, #0
	strh r2, [r1, #0xc]
	ldr r2, [r0, #0x14]
	strh r2, [r1, #0xe]
	strh r3, [r1, #0x10]
	mov r2, #0x1f
	str r2, [sp, #0x14]
	str r3, [sp, #0x18]
	ldr r0, [r0, #0x1c]
	strh r0, [r1, #0x1c]
	add r0, sp, #0
	bl FUN_02013E84
	add sp, #0x20
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD17_021D770C

	thumb_func_start MOD17_021D7740
MOD17_021D7740: ; 0x021D7740
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #4]
	add r4, r1, #0
	bl FUN_02013ECC
	add r1, sp, #0
	strh r0, [r1, #4]
	lsr r0, r0, #0x10
	strh r0, [r1, #6]
	ldrh r0, [r1, #4]
	strh r0, [r1, #0xc]
	ldrh r0, [r1, #6]
	strh r0, [r1, #0xe]
	ldr r0, [r5, #4]
	bl FUN_02013EF0
	add r1, sp, #0
	strh r0, [r1]
	lsr r0, r0, #0x10
	strh r0, [r1, #2]
	ldrh r0, [r1]
	strh r0, [r1, #8]
	ldrh r0, [r1, #2]
	strh r0, [r1, #0xa]
	mov r0, #0xe
	ldrsh r2, [r1, r0]
	mov r0, #0xa
	strb r2, [r4]
	ldrsh r0, [r1, r0]
	add r0, r2, r0
	strb r0, [r4, #1]
	mov r0, #0xc
	ldrsh r2, [r1, r0]
	mov r0, #8
	strb r2, [r4, #2]
	ldrsh r0, [r1, r0]
	add r0, r2, r0
	strb r0, [r4, #3]
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021D7740

	thumb_func_start MOD17_021D7794
MOD17_021D7794: ; 0x021D7794
	push {r3, lr}
	bl MOD17_021D7D08
	bl MOD17_021D7D28
	bl MOD17_021D7DB0
	ldr r0, _021D77B0 ; =gMain + 0x60
	mov r1, #1
	strb r1, [r0, #5]
	bl GX_SwapDisplay
	pop {r3, pc}
	nop
_021D77B0: .word gMain + 0x60
	thumb_func_end MOD17_021D7794

	thumb_func_start MOD17_021D77B4
MOD17_021D77B4: ; 0x021D77B4
	push {r3, lr}
	ldr r0, _021D77D0 ; =gMain + 0x60
	mov r1, #0
	strb r1, [r0, #5]
	bl GX_SwapDisplay
	bl MOD17_021D7E0C
	bl MOD17_021D7E00
	bl GX_ResetBankForTex
	pop {r3, pc}
	nop
_021D77D0: .word gMain + 0x60
	thumb_func_end MOD17_021D77B4

	thumb_func_start MOD17_021D77D4
MOD17_021D77D4: ; 0x021D77D4
	push {r3, r4, r5, lr}
	sub sp, #0x10
	ldr r5, _021D7824 ; =0x021DE274
	add r3, sp, #0
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r4, #0
	add r1, r2, #0
	bl MOD17_021D7E1C
	mov r2, #0xa
	add r0, r4, #0
	mov r1, #0xe
	lsl r2, r2, #0xa
	mov r3, #0x20
	bl MOD17_021D82E4
	add r0, r4, #0
	bl MOD17_021D8088
	add r0, r4, #0
	mov r1, #0xd
	bl MOD17_021D82B8
	add r0, r4, #0
	bl MOD17_021D80CC
	mov r0, #0xe
	bl BgConfig_Alloc
	str r0, [r4, #0x38]
	add r0, r4, #0
	bl MOD17_021D7F34
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7824: .word MOD17_021DE274
	thumb_func_end MOD17_021D77D4

	thumb_func_start MOD17_021D7828
MOD17_021D7828: ; 0x021D7828
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021D82D4
	add r0, r4, #0
	bl MOD17_021D7E58
	add r0, r4, #0
	bl MOD17_021D8058
	ldr r0, [r4, #0x38]
	bl FreeToHeap
	add r0, r4, #0
	bl MOD17_021D834C
	add r0, r4, #0
	bl MOD17_021D816C
	add r0, r4, #0
	bl MOD17_021D80B4
	ldr r0, [r4, #4]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, [r4, #0x10]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4, #0x10]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7828

	thumb_func_start MOD17_021D786C
MOD17_021D786C: ; 0x021D786C
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020222AC
	bl NNS_G2dSetupSoftwareSpriteCamera
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _021D7884
	add r0, r4, #0
	bl MOD17_021D7E68
_021D7884:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _021D7890
	ldr r0, [r4, #0x20]
	bl FUN_02006ED4
_021D7890:
	mov r0, #0
	add r1, r0, #0
	bl FUN_020222B4
	add r0, r4, #0
	bl MOD17_021D8194
	pop {r4, pc}
	thumb_func_end MOD17_021D786C

	thumb_func_start MOD17_021D78A0
MOD17_021D78A0: ; 0x021D78A0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4]
	ldr r2, [r4, #4]
	add r5, r0, #0
	bl MOD17_021D7E74
	ldr r1, [r4, #8]
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	bl MOD17_021D7ED4
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021D78A0

	thumb_func_start MOD17_021D78BC
MOD17_021D78BC: ; 0x021D78BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02013DEC
	ldr r0, [r4]
	bl FUN_02013E5C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D78BC

	thumb_func_start MOD17_021D78D0
MOD17_021D78D0: ; 0x021D78D0
	push {r4, r5, r6, lr}
	sub sp, #0x70
	add r5, r0, #0
	mov r0, #0
	str r1, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	add r4, r2, #0
	ldr r2, [r5, #0x40]
	add r6, r3, #0
	str r2, [sp, #0x14]
	ldr r2, [r5, #0x44]
	add r3, r1, #0
	str r2, [sp, #0x18]
	ldr r2, [r5, #0x48]
	str r2, [sp, #0x1c]
	ldr r2, [r5, #0x4c]
	str r2, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, sp, #0x4c
	add r2, r1, #0
	bl FUN_02008AA4
	ldr r0, [r5, #0x3c]
	str r0, [sp, #0x2c]
	add r0, sp, #0x4c
	str r0, [sp, #0x30]
	lsl r0, r4, #0xc
	str r0, [sp, #0x34]
	lsl r0, r6, #0xc
	str r0, [sp, #0x38]
	mov r0, #0
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x80]
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x84]
	str r0, [sp, #0x44]
	mov r0, #0xe
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	bl FUN_0201FF84
	add sp, #0x70
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021D78D0

	thumb_func_start MOD17_021D7934
MOD17_021D7934: ; 0x021D7934
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r4, [sp, #0x1c]
	str r4, [sp]
	ldr r4, [sp, #0x18]
	str r4, [sp, #4]
	mov r4, #0xe
	str r4, [sp, #8]
	ldr r0, [r0, #0x40]
	bl FUN_02008F34
	bl FUN_02009B04
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7934

	thumb_func_start MOD17_021D7954
MOD17_021D7954: ; 0x021D7954
	push {r4, lr}
	sub sp, #0x10
	ldr r4, [sp, #0x20]
	str r4, [sp]
	ldr r4, [sp, #0x18]
	str r4, [sp, #4]
	ldr r4, [sp, #0x1c]
	str r4, [sp, #8]
	mov r4, #0xe
	str r4, [sp, #0xc]
	ldr r0, [r0, #0x44]
	bl FUN_02008FEC
	bl FUN_02009D68
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7954

	thumb_func_start MOD17_021D7978
MOD17_021D7978: ; 0x021D7978
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r4, [sp, #0x18]
	str r4, [sp]
	mov r4, #2
	str r4, [sp, #4]
	mov r4, #0xe
	str r4, [sp, #8]
	ldr r0, [r0, #0x48]
	bl FUN_020090AC
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7978

	thumb_func_start MOD17_021D7994
MOD17_021D7994: ; 0x021D7994
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r4, [sp, #0x18]
	str r4, [sp]
	mov r4, #3
	str r4, [sp, #4]
	mov r4, #0xe
	str r4, [sp, #8]
	ldr r0, [r0, #0x4c]
	bl FUN_020090AC
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7994

	thumb_func_start MOD17_021D79B0
MOD17_021D79B0: ; 0x021D79B0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	bl FUN_020094F0
	add r1, r0, #0
	ldr r0, [r4, #0x40]
	bl FUN_02009490
	pop {r4, pc}
	thumb_func_end MOD17_021D79B0

	thumb_func_start MOD17_021D79C4
MOD17_021D79C4: ; 0x021D79C4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x44]
	bl FUN_020094F0
	add r1, r0, #0
	ldr r0, [r4, #0x44]
	bl FUN_02009490
	pop {r4, pc}
	thumb_func_end MOD17_021D79C4

	thumb_func_start MOD17_021D79D8
MOD17_021D79D8: ; 0x021D79D8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x48]
	bl FUN_020094F0
	add r1, r0, #0
	ldr r0, [r4, #0x48]
	bl FUN_02009490
	pop {r4, pc}
	thumb_func_end MOD17_021D79D8

	thumb_func_start MOD17_021D79EC
MOD17_021D79EC: ; 0x021D79EC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x4c]
	bl FUN_020094F0
	add r1, r0, #0
	ldr r0, [r4, #0x4c]
	bl FUN_02009490
	pop {r4, pc}
	thumb_func_end MOD17_021D79EC

	thumb_func_start MOD17_021D7A00
MOD17_021D7A00: ; 0x021D7A00
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0x76
	mov r2, #0x13
	mov r3, #0xe
	bl MOD17_021D8358
	add r0, r5, #0
	add r1, r4, #0
	bl MOD17_021D81A0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD17_021D821C
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021D7A00

	thumb_func_start MOD17_021D7A24
MOD17_021D7A24: ; 0x021D7A24
	ldr r3, _021D7A28 ; =MOD17_021D83AC
	bx r3
	.align 2, 0
_021D7A28: .word MOD17_021D83AC
	thumb_func_end MOD17_021D7A24

	thumb_func_start MOD17_021D7A2C
MOD17_021D7A2C: ; 0x021D7A2C
	push {r4, r5, r6, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x2c]
	add r6, r1, #0
	add r5, r2, #0
	bl FUN_02020CD4
	ldr r1, [r4, #0x30]
	lsl r5, r5, #2
	add r0, r6, #0
	add r1, r1, r5
	bl NNS_G2dGetUnpackedCharacterData
	ldr r0, [r4, #0x30]
	ldr r0, [r0, r5]
	pop {r4, r5, r6, pc}
	thumb_func_end MOD17_021D7A2C

	thumb_func_start MOD17_021D7A4C
MOD17_021D7A4C: ; 0x021D7A4C
	push {r3, r4}
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _021D7A78 ; =0xFFFF1FFF
	add r3, r0, #0
	and r1, r2
	str r1, [r0]
	add r3, #8
	ldrh r4, [r3]
	mov r2, #3
	mov r1, #1
	bic r4, r2
	orr r1, r4
	add r0, #0xa
	strh r1, [r3]
	ldrh r1, [r0]
	bic r1, r2
	strh r1, [r0]
	pop {r3, r4}
	bx lr
	nop
_021D7A78: .word 0xFFFF1FFF
	thumb_func_end MOD17_021D7A4C

	thumb_func_start MOD17_021D7A7C
MOD17_021D7A7C: ; 0x021D7A7C
	push {r3, r4}
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _021D7AD8 ; =0xFFFF1FFF
	add r3, r0, #0
	and r2, r1
	lsr r1, r0, #0xd
	orr r1, r2
	str r1, [r0]
	add r3, #0x48
	ldrh r4, [r3]
	mov r2, #0x3f
	mov r1, #0x1f
	bic r4, r2
	orr r1, r4
	strh r1, [r3]
	add r3, r0, #0
	add r3, #0x4a
	ldrh r4, [r3]
	mov r1, #0x12
	bic r4, r2
	orr r1, r4
	strh r1, [r3]
	add r1, r0, #0
	ldr r2, _021D7ADC ; =0x00000AF6
	add r1, #0x40
	strh r2, [r1]
	add r1, r0, #0
	ldr r2, _021D7AE0 ; =0x0000128F
	add r1, #0x44
	strh r2, [r1]
	add r2, r0, #0
	add r2, #8
	ldrh r3, [r2]
	mov r1, #3
	add r0, #0xa
	bic r3, r1
	strh r3, [r2]
	ldrh r2, [r0]
	bic r2, r1
	mov r1, #1
	orr r1, r2
	strh r1, [r0]
	pop {r3, r4}
	bx lr
	.align 2, 0
_021D7AD8: .word 0xFFFF1FFF
_021D7ADC: .word 0x00000AF6
_021D7AE0: .word 0x0000128F
	thumb_func_end MOD17_021D7A7C

	thumb_func_start MOD17_021D7AE4
MOD17_021D7AE4: ; 0x021D7AE4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	bl DoScheduledBgGpuUpdates
	ldr r0, [r4, #0x20]
	bl FUN_020081C4
	bl FUN_02009F80
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7AE4

	thumb_func_start MOD17_021D7AFC
MOD17_021D7AFC: ; 0x021D7AFC
	push {r3, lr}
	add r3, r1, #0
	mov r1, #0x76
	mov r2, #0x13
	bl MOD17_021D8358
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7AFC

	thumb_func_start MOD17_021D7B0C
MOD17_021D7B0C: ; 0x021D7B0C
	push {r4, r5}
	ldrh r5, [r0, #2]
	ldrh r4, [r0]
	lsl r5, r5, #3
	cmp r1, #0
	blt _021D7B26
	cmp r2, #0
	blt _021D7B26
	cmp r1, r5
	bge _021D7B26
	lsl r4, r4, #3
	cmp r2, r4
	blt _021D7B2C
_021D7B26:
	mov r0, #2
	pop {r4, r5}
	bx lr
_021D7B2C:
	add r4, r2, #0
	mul r4, r5
	add r4, r1, r4
	lsr r5, r4, #0x1f
	lsl r2, r4, #0x1d
	sub r2, r2, r5
	mov r1, #0x1d
	ror r2, r1
	add r1, r5, r2
	lsl r2, r1, #2
	add r1, r3, #0
	ldr r3, [r0, #0x14]
	asr r0, r4, #2
	lsr r0, r0, #0x1d
	add r0, r4, r0
	asr r0, r0, #3
	lsl r0, r0, #2
	ldr r3, [r3, r0]
	mov r0, #0xf
	lsl r0, r2
	lsl r1, r2
	and r0, r3
	cmp r1, r0
	bne _021D7B62
	mov r0, #1
	pop {r4, r5}
	bx lr
_021D7B62:
	mov r0, #0
	pop {r4, r5}
	bx lr
	thumb_func_end MOD17_021D7B0C

	thumb_func_start MOD17_021D7B68
MOD17_021D7B68: ; 0x021D7B68
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r2, #0
	bl MOD17_021D7E1C
	mov r2, #0xa
	add r0, r5, #0
	add r1, r4, #0
	lsl r2, r2, #0xa
	mov r3, #0x20
	bl MOD17_021D82E4
	ldr r0, [r5, #0x20]
	mov r1, #1
	bl FUN_0200825C
	add r0, r5, #0
	add r1, r4, #0
	bl MOD17_021D82B8
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7B68

	thumb_func_start MOD17_021D7B94
MOD17_021D7B94: ; 0x021D7B94
	push {r4, r5, lr}
	sub sp, #0x1c
	ldr r3, _021D7BE0 ; =0x021DE2D8
	add r5, r0, #0
	str r1, [r5, #0x38]
	add r4, r2, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #2
	str r0, [r2]
	ldr r0, [r5, #0x38]
	bl FreeBgTilemapBuffer
	ldr r0, [r5, #0x38]
	mov r1, #2
	add r2, sp, #0
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	add r3, r4, #0
	bl BG_ClearCharDataRange
	ldr r0, [r5, #0x38]
	mov r1, #2
	bl BgClearTilemapBufferAndCommit
	add sp, #0x1c
	pop {r4, r5, pc}
	nop
_021D7BE0: .word MOD17_021DE2D8
	thumb_func_end MOD17_021D7B94

	thumb_func_start MOD17_021D7BE4
MOD17_021D7BE4: ; 0x021D7BE4
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021D82D4
	add r0, r4, #0
	bl MOD17_021D7E58
	add r0, r4, #0
	bl MOD17_021D834C
	ldr r0, [r4, #4]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, [r4, #0x10]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4, #0x10]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7BE4

	thumb_func_start MOD17_021D7C10
MOD17_021D7C10: ; 0x021D7C10
	ldr r3, _021D7C18 ; =FreeBgTilemapBuffer
	ldr r0, [r0, #0x38]
	mov r1, #2
	bx r3
	.align 2, 0
_021D7C18: .word FreeBgTilemapBuffer
	thumb_func_end MOD17_021D7C10

	thumb_func_start MOD17_021D7C1C
MOD17_021D7C1C: ; 0x021D7C1C
	ldr r3, _021D7C24 ; =FUN_020081C4
	ldr r0, [r0, #0x20]
	bx r3
	nop
_021D7C24: .word FUN_020081C4
	thumb_func_end MOD17_021D7C1C

	thumb_func_start MOD17_021D7C28
MOD17_021D7C28: ; 0x021D7C28
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r0, _021D7CAC ; =0x04000454
	str r3, [sp]
	mov r1, #0
	str r1, [r0]
	sub r0, #0x10
	add r6, r2, #0
	ldr r7, [sp, #0x18]
	str r1, [r0]
	bl NNS_G2dSetupSoftwareSpriteCamera
	ldr r1, _021D7CB0 ; =0x04000470
	lsl r0, r4, #0xc
	str r0, [r1]
	lsl r0, r6, #0xc
	str r0, [r1]
	mov r0, #0
	str r0, [r1]
	ldr r0, [sp]
	ldr r1, _021D7CB4 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r0, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r0, [r1, r0]
	ldrsh r1, [r1, r2]
	bl G3_RotZ
	ldr r2, [r7, #8]
	ldr r1, [r7, #4]
	ldr r3, [r7]
	ldr r0, _021D7CB8 ; =0x0400046C
	str r3, [r0]
	str r1, [r0]
	neg r1, r4
	str r2, [r0]
	lsl r1, r1, #0xc
	str r1, [r0, #4]
	neg r1, r6
	lsl r1, r1, #0xc
	str r1, [r0, #4]
	mov r1, #0
	str r1, [r0, #4]
	sub r0, #0x28
	str r1, [r0]
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _021D7C94
	add r0, r5, #0
	bl MOD17_021D7E68
_021D7C94:
	ldr r0, [r5, #0x24]
	cmp r0, #0
	beq _021D7CA0
	ldr r0, [r5, #0x20]
	bl FUN_02006ED4
_021D7CA0:
	ldr r0, _021D7CBC ; =0x04000448
	mov r1, #1
	str r1, [r0]
	str r1, [r0]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7CAC: .word 0x04000454
_021D7CB0: .word 0x04000470
_021D7CB4: .word FX_SinCosTable_
_021D7CB8: .word 0x0400046C
_021D7CBC: .word 0x04000448
	thumb_func_end MOD17_021D7C28

	thumb_func_start MOD17_021D7CC0
MOD17_021D7CC0: ; 0x021D7CC0
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021D80CC
	mov r0, #0xe
	bl BgConfig_Alloc
	str r0, [r4, #0x38]
	add r0, r4, #0
	bl MOD17_021D7F34
	pop {r4, pc}
	thumb_func_end MOD17_021D7CC0

	thumb_func_start MOD17_021D7CD8
MOD17_021D7CD8: ; 0x021D7CD8
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021D8058
	ldr r0, [r4, #0x38]
	bl FreeToHeap
	add r0, r4, #0
	bl MOD17_021D816C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7CD8

	thumb_func_start MOD17_021D7CF0
MOD17_021D7CF0: ; 0x021D7CF0
	push {r3, lr}
	ldr r0, [r0, #0x38]
	bl DoScheduledBgGpuUpdates
	bl FUN_02009F80
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7CF0

	thumb_func_start MOD17_021D7D00
MOD17_021D7D00: ; 0x021D7D00
	ldr r3, _021D7D04 ; =MOD17_021D8194
	bx r3
	.align 2, 0
_021D7D04: .word MOD17_021D8194
	thumb_func_end MOD17_021D7D00

	thumb_func_start MOD17_021D7D08
MOD17_021D7D08: ; 0x021D7D08
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7D24 ; =0x021DE32C
	add r3, sp, #0
	mov r2, #5
_021D7D12:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7D12
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7D24: .word MOD17_021DE32C
	thumb_func_end MOD17_021D7D08

	thumb_func_start MOD17_021D7D28
MOD17_021D7D28: ; 0x021D7D28
	push {r3, lr}
	bl NNS_G3dInit
	bl G3X_InitMtxStack
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r0, _021D7D9C ; =0x04000008
	mov r1, #3
	ldrh r2, [r0]
	bic r2, r1
	mov r1, #1
	orr r1, r2
	strh r1, [r0]
	add r0, #0x58
	ldrh r1, [r0]
	ldr r2, _021D7DA0 ; =0xFFFFCFFD
	and r1, r2
	strh r1, [r0]
	ldrh r3, [r0]
	add r1, r2, #2
	and r3, r1
	mov r1, #0x10
	orr r1, r3
	strh r1, [r0]
	ldrh r3, [r0]
	ldr r1, _021D7DA4 ; =0x0000CFFB
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
	ldr r2, _021D7DA8 ; =0x04000540
	mov r0, #2
	ldr r1, _021D7DAC ; =0xBFFF0000
	str r0, [r2]
	str r1, [r2, #0x40]
	mov r1, #1
	bl NNS_GfdInitFrmTexVramManager
	mov r0, #1
	lsl r0, r0, #0xe
	mov r1, #1
	bl NNS_GfdInitFrmPlttVramManager
	pop {r3, pc}
	.align 2, 0
_021D7D9C: .word 0x04000008
_021D7DA0: .word 0xFFFFCFFD
_021D7DA4: .word 0x0000CFFB
_021D7DA8: .word 0x04000540
_021D7DAC: .word 0xBFFF0000
	thumb_func_end MOD17_021D7D28

	thumb_func_start MOD17_021D7DB0
MOD17_021D7DB0: ; 0x021D7DB0
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021D7DF8 ; =0x021DE254
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl SetBothScreensModesAndDisable
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7DFC ; =0xFFCFFFEF
	and r1, r0
	mov r0, #0x10
	orr r0, r1
	str r0, [r2]
	bl NNS_G2dInitOamManagerModule
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r0, #0x1f
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x13
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021D7DF8: .word MOD17_021DE254
_021D7DFC: .word 0xFFCFFFEF
	thumb_func_end MOD17_021D7DB0

	thumb_func_start MOD17_021D7E00
MOD17_021D7E00: ; 0x021D7E00
	push {r3, lr}
	bl NNS_GfdResetFrmTexVramState
	bl NNS_GfdResetFrmPlttVramState
	pop {r3, pc}
	thumb_func_end MOD17_021D7E00

	thumb_func_start MOD17_021D7E0C
MOD17_021D7E0C: ; 0x021D7E0C
	push {r3, lr}
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	bl NNS_G2dInitOamManagerModule
	pop {r3, pc}
	thumb_func_end MOD17_021D7E0C

	thumb_func_start MOD17_021D7E1C
MOD17_021D7E1C: ; 0x021D7E1C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_02013CD4
	str r0, [r5]
	mov r1, #0x76
	ldr r0, [r4, #0xc]
	lsl r1, r1, #2
	bl AllocFromHeap
	str r0, [r5, #4]
	mov r0, #0x76
	str r0, [r5, #8]
	mov r0, #0
	str r0, [r5, #0xc]
	ldr r0, [r4, #0xc]
	mov r1, #0x4c
	bl AllocFromHeap
	str r0, [r5, #0x10]
	mov r0, #0x13
	str r0, [r5, #0x14]
	mov r0, #0
	str r0, [r5, #0x18]
	mov r0, #1
	str r0, [r5, #0x1c]
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021D7E1C

	thumb_func_start MOD17_021D7E58
MOD17_021D7E58: ; 0x021D7E58
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02013D18
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}
	thumb_func_end MOD17_021D7E58

	thumb_func_start MOD17_021D7E68
MOD17_021D7E68: ; 0x021D7E68
	ldr r3, _021D7E70 ; =FUN_02013D5C
	ldr r0, [r0]
	bx r3
	nop
_021D7E70: .word FUN_02013D5C
	thumb_func_end MOD17_021D7E68

	thumb_func_start MOD17_021D7E74
MOD17_021D7E74: ; 0x021D7E74
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0
	str r0, [sp, #4]
	add r0, r2, #0
	add r4, r1, #0
	str r2, [sp]
	cmp r0, #0
	ble _021D7ED0
	add r7, r5, #0
	add r6, r4, #0
	add r7, #0xc
_021D7E8E:
	ldr r1, [r5, #0xc]
	ldr r0, [r5, #8]
	cmp r1, r0
	blt _021D7E9A
	bl GF_AssertFail
_021D7E9A:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021D7EB0
	add r0, r6, #0
	bl FUN_02013D98
	ldr r2, [r5, #0xc]
	ldr r1, [r5, #4]
	lsl r2, r2, #2
	str r0, [r1, r2]
	b _021D7EBA
_021D7EB0:
	ldr r1, [r5, #0xc]
	ldr r0, [r5, #4]
	lsl r2, r1, #2
	mov r1, #0
	str r1, [r0, r2]
_021D7EBA:
	ldr r0, [r7]
	add r4, #8
	add r0, r0, #1
	str r0, [r7]
	ldr r0, [sp, #4]
	add r6, #8
	add r1, r0, #1
	ldr r0, [sp]
	str r1, [sp, #4]
	cmp r1, r0
	blt _021D7E8E
_021D7ED0:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021D7E74

	thumb_func_start MOD17_021D7ED4
MOD17_021D7ED4: ; 0x021D7ED4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0
	str r0, [sp, #4]
	add r0, r2, #0
	add r4, r1, #0
	str r2, [sp]
	cmp r0, #0
	ble _021D7F30
	add r7, r5, #0
	add r6, r4, #0
	add r7, #0x18
_021D7EEE:
	ldr r1, [r5, #0x18]
	ldr r0, [r5, #0x14]
	cmp r1, r0
	blt _021D7EFA
	bl GF_AssertFail
_021D7EFA:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021D7F10
	add r0, r6, #0
	bl FUN_02013E14
	ldr r2, [r5, #0x18]
	ldr r1, [r5, #0x10]
	lsl r2, r2, #2
	str r0, [r1, r2]
	b _021D7F1A
_021D7F10:
	ldr r1, [r5, #0x18]
	ldr r0, [r5, #0x10]
	lsl r2, r1, #2
	mov r1, #0
	str r1, [r0, r2]
_021D7F1A:
	ldr r0, [r7]
	add r4, #0xc
	add r0, r0, #1
	str r0, [r7]
	ldr r0, [sp, #4]
	add r6, #0xc
	add r1, r0, #1
	ldr r0, [sp]
	str r1, [sp, #4]
	cmp r1, r0
	blt _021D7EEE
_021D7F30:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021D7ED4

	thumb_func_start MOD17_021D7F34
MOD17_021D7F34: ; 0x021D7F34
	push {r4, r5, lr}
	sub sp, #0x8c
	ldr r5, _021D8044 ; =0x021DE2A0
	add r4, r0, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x70
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	ldr r0, [r4, #0x38]
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #1
	mov r1, #0x20
	mov r2, #0
	mov r3, #0xe
	bl BG_ClearCharDataRange
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D8048 ; =0x021DE2BC
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	ldr r0, [r4, #0x38]
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	mov r3, #0xe
	bl BG_ClearCharDataRange
	ldr r0, [r4, #0x38]
	mov r1, #2
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D804C ; =0x021DE2F4
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	ldr r0, [r4, #0x38]
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #0xe
	bl BG_ClearCharDataRange
	ldr r0, [r4, #0x38]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D8050 ; =0x021DE284
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	ldr r0, [r4, #0x38]
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0xe
	bl BG_ClearCharDataRange
	ldr r0, [r4, #0x38]
	mov r1, #4
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D8054 ; =0x021DE310
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	ldr r0, [r4, #0x38]
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #5
	mov r1, #0x20
	mov r2, #0
	mov r3, #0xe
	bl BG_ClearCharDataRange
	ldr r0, [r4, #0x38]
	mov r1, #5
	bl BgClearTilemapBufferAndCommit
	add sp, #0x8c
	pop {r4, r5, pc}
	nop
_021D8044: .word MOD17_021DE2A0
_021D8048: .word MOD17_021DE2BC
_021D804C: .word MOD17_021DE2F4
_021D8050: .word MOD17_021DE284
_021D8054: .word MOD17_021DE310
	thumb_func_end MOD17_021D7F34

	thumb_func_start MOD17_021D8058
MOD17_021D8058: ; 0x021D8058
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #0x38]
	mov r1, #2
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #0x38]
	mov r1, #3
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #0x38]
	mov r1, #4
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #0x38]
	mov r1, #5
	bl FreeBgTilemapBuffer
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D8058

	thumb_func_start MOD17_021D8088
MOD17_021D8088: ; 0x021D8088
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x77
	mov r1, #0xe
	bl FUN_02020C44
	mov r1, #0x77
	str r0, [r4, #0x2c]
	mov r0, #0xe
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x77
	mov r1, #0
	lsl r2, r2, #2
	str r0, [r4, #0x30]
	bl memset
	mov r0, #0x77
	str r0, [r4, #0x34]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D8088

	thumb_func_start MOD17_021D80B4
MOD17_021D80B4: ; 0x021D80B4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	bl FreeToHeap
	ldr r0, [r4, #0x2c]
	bl FUN_02020C90
	mov r0, #0
	str r0, [r4, #0x34]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D80B4

	thumb_func_start MOD17_021D80CC
MOD17_021D80CC: ; 0x021D80CC
	push {r4, r5, lr}
	sub sp, #0x24
	ldr r5, _021D8168 ; =0x021DE264
	add r3, sp, #0x14
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r1, #0x10
	add r0, r2, #0
	add r2, r1, #0
	bl FUN_0201D060
	mov r0, #5
	mov r1, #0xe
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	bl NNS_G2dInitOamManagerModule
	mov r0, #0
	str r0, [sp]
	mov r1, #0x7c
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x1f
	str r3, [sp, #0xc]
	mov r2, #0xe
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r4, #0
	mov r0, #0x30
	add r1, #0x50
	mov r2, #0xe
	bl FUN_02008C9C
	str r0, [r4, #0x3c]
	add r0, r4, #0
	mov r2, #2
	add r0, #0x50
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	mov r0, #8
	mov r1, #0
	mov r2, #0xe
	bl FUN_02008DEC
	str r0, [r4, #0x40]
	mov r0, #5
	mov r1, #1
	mov r2, #0xe
	bl FUN_02008DEC
	str r0, [r4, #0x44]
	mov r0, #0x30
	mov r1, #2
	mov r2, #0xe
	bl FUN_02008DEC
	str r0, [r4, #0x48]
	mov r0, #0x30
	mov r1, #3
	mov r2, #0xe
	bl FUN_02008DEC
	str r0, [r4, #0x4c]
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_021D8168: .word MOD17_021DE264
	thumb_func_end MOD17_021D80CC

	thumb_func_start MOD17_021D816C
MOD17_021D816C: ; 0x021D816C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x3c]
	bl FUN_0201FD58
	mov r4, #0
_021D8178:
	ldr r0, [r5, #0x40]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D8178
	bl FUN_0201D12C
	bl FUN_0201E08C
	bl FUN_02009FA0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021D816C

	thumb_func_start MOD17_021D8194
MOD17_021D8194: ; 0x021D8194
	ldr r3, _021D819C ; =FUN_0201FDEC
	ldr r0, [r0, #0x3c]
	bx r3
	nop
_021D819C: .word FUN_0201FDEC
	thumb_func_end MOD17_021D8194

	thumb_func_start MOD17_021D81A0
MOD17_021D81A0: ; 0x021D81A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r4, #0
	add r7, r0, #0
	add r6, r1, #0
	add r5, r4, #0
_021D81AC:
	mov r0, #1
	str r0, [sp]
	mov r0, #0x19
	add r1, r4, #1
	mov r2, #0
	mov r3, #0xe
	bl GfGfxLoader_LoadFromNarc
	str r0, [sp, #4]
	cmp r0, #0
	bne _021D81C6
	bl GF_AssertFail
_021D81C6:
	ldr r1, [sp, #4]
	add r0, r7, #0
	add r2, r4, #0
	bl MOD17_021D7A2C
	ldr r1, [r6]
	add r4, r4, #1
	add r1, r1, r5
	str r0, [r1, #4]
	ldr r1, [r7]
	ldr r0, [r6]
	str r1, [r0, r5]
	add r5, #8
	cmp r4, #0x64
	blt _021D81AC
	mov r0, #1
	mov r1, #0
	str r0, [sp]
	mov r0, #0x19
	add r2, r1, #0
	mov r3, #0xe
	bl GfGfxLoader_LoadFromNarc
	add r4, r0, #0
	ldr r0, [r6, #0x14]
	add r1, r4, #0
	mov r2, #0
	bl FUN_02020CD4
	ldr r1, [r6, #8]
	add r0, r4, #0
	add r1, r1, #4
	bl NNS_G2dGetUnpackedPaletteData
	ldr r1, [r7]
	ldr r0, [r6, #8]
	str r1, [r0]
	ldr r0, [r6, #8]
	mov r1, #3
	str r1, [r0, #8]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021D81A0

	thumb_func_start MOD17_021D821C
MOD17_021D821C: ; 0x021D821C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	mov r0, #0x87
	add r5, r1, #0
	mov r4, #0
	str r0, [sp, #8]
_021D822A:
	mov r0, #1
	add r1, r4, #0
	str r0, [sp]
	mov r0, #0x19
	add r1, #0xce
	mov r2, #0
	mov r3, #0xe
	bl GfGfxLoader_LoadFromNarc
	add r2, r4, #0
	add r1, r0, #0
	add r2, #0x64
	add r0, r7, #0
	lsl r6, r2, #3
	bl MOD17_021D7A2C
	ldr r1, [r5]
	mov r2, #0
	add r1, r1, r6
	str r0, [r1, #4]
	ldr r1, [r7]
	ldr r0, [r5]
	mov r3, #0xe
	str r1, [r0, r6]
	add r0, r4, #1
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp]
	ldr r1, [sp, #8]
	mov r0, #0x19
	bl GfGfxLoader_LoadFromNarc
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #4]
	bl FUN_02020CD4
	ldr r1, [sp, #4]
	mov r0, #0xc
	add r6, r1, #0
	mul r6, r0
	ldr r1, [r5, #8]
	ldr r0, [sp, #0xc]
	add r1, r1, r6
	add r1, r1, #4
	bl NNS_G2dGetUnpackedPaletteData
	ldr r0, [r5, #8]
	add r0, r0, r6
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _021D8298
	bl GF_AssertFail
_021D8298:
	ldr r1, [r7]
	ldr r0, [r5, #8]
	add r4, r4, #1
	str r1, [r0, r6]
	ldr r0, [r5, #8]
	add r1, r0, r6
	mov r0, #1
	str r0, [r1, #8]
	ldr r0, [sp, #8]
	add r0, r0, #4
	str r0, [sp, #8]
	cmp r4, #0x12
	blt _021D822A
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021D821C

	thumb_func_start MOD17_021D82B8
MOD17_021D82B8: ; 0x021D82B8
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	add r3, r1, #0
	mov r2, #0
	mov r0, #0x19
	mov r1, #0xeb
	str r2, [sp]
	bl GfGfxLoader_LoadFromNarc
	str r0, [r4, #0x28]
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D82B8

	thumb_func_start MOD17_021D82D4
MOD17_021D82D4: ; 0x021D82D4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4, #0x28]
	pop {r4, pc}
	thumb_func_end MOD17_021D82D4

	thumb_func_start MOD17_021D82E4
MOD17_021D82E4: ; 0x021D82E4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	bl FUN_02006D98
	str r0, [r5, #0x20]
	ldr r3, _021D833C ; =NNS_GfdDefaultFuncAllocTexVram
	mov r1, #0
	ldr r3, [r3]
	add r0, r4, #0
	add r2, r1, #0
	blx r3
	ldr r3, _021D8340 ; =NNS_GfdDefaultFuncAllocPlttVram
	add r4, r0, #0
	ldr r3, [r3]
	add r0, r6, #0
	mov r1, #0
	mov r2, #1
	blx r3
	ldr r2, _021D8344 ; =0x7FFF0000
	add r6, r0, #0
	and r2, r4
	lsl r1, r4, #0x10
	lsr r2, r2, #0x10
	ldr r0, [r5, #0x20]
	lsr r1, r1, #0xd
	lsl r2, r2, #4
	bl FUN_020081A8
	ldr r2, _021D8348 ; =0xFFFF0000
	lsl r1, r6, #0x10
	and r2, r6
	lsr r2, r2, #0x10
	ldr r0, [r5, #0x20]
	lsr r1, r1, #0xd
	lsl r2, r2, #3
	bl FUN_020081B4
	mov r0, #1
	str r0, [r5, #0x24]
	pop {r4, r5, r6, pc}
	nop
_021D833C: .word NNS_GfdDefaultFuncAllocTexVram
_021D8340: .word NNS_GfdDefaultFuncAllocPlttVram
_021D8344: .word 0x7FFF0000
_021D8348: .word 0xFFFF0000
	thumb_func_end MOD17_021D82E4

	thumb_func_start MOD17_021D834C
MOD17_021D834C: ; 0x021D834C
	ldr r3, _021D8354 ; =FUN_020072E8
	ldr r0, [r0, #0x20]
	bx r3
	nop
_021D8354: .word FUN_020072E8
	thumb_func_end MOD17_021D834C

	thumb_func_start MOD17_021D8358
MOD17_021D8358: ; 0x021D8358
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	lsl r0, r4, #3
	str r0, [sp]
	add r7, r3, #0
	ldr r1, [sp]
	add r0, r7, #0
	add r6, r2, #0
	bl AllocFromHeap
	ldr r2, [sp]
	mov r1, #0
	str r0, [r5]
	bl memset
	add r0, r4, #0
	add r1, r7, #0
	bl FUN_02020C44
	str r0, [r5, #0x10]
	str r4, [r5, #4]
	mov r0, #0xc
	add r4, r6, #0
	mul r4, r0
	add r0, r7, #0
	add r1, r4, #0
	bl AllocFromHeap
	mov r1, #0
	add r2, r4, #0
	str r0, [r5, #8]
	bl memset
	add r0, r6, #0
	add r1, r7, #0
	bl FUN_02020C44
	str r0, [r5, #0x14]
	str r6, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021D8358

	thumb_func_start MOD17_021D83AC
MOD17_021D83AC: ; 0x021D83AC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021D83BE
	bl FUN_02020C90
	mov r0, #0
	str r0, [r4, #0x10]
_021D83BE:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021D83CC
	bl FUN_02020C90
	mov r0, #0
	str r0, [r4, #0x14]
_021D83CC:
	ldr r0, [r4]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4]
	ldr r0, [r4, #8]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4, #8]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D83AC

	thumb_func_start MOD17_021D83E4
MOD17_021D83E4: ; 0x021D83E4
	push {r3, r4, r5, lr}
	sub sp, #8
	mov r2, #2
	add r4, r0, #0
	mov r0, #3
	mov r1, #0xd
	lsl r2, r2, #0x10
	bl CreateHeap
	mov r2, #1
	mov r0, #3
	mov r1, #0xe
	lsl r2, r2, #0x12
	bl CreateHeap
	ldr r1, _021D84D8 ; =0x000006D8
	add r0, r4, #0
	mov r2, #0xd
	bl OverlayManager_CreateAndGetData
	ldr r2, _021D84D8 ; =0x000006D8
	mov r1, #0
	add r5, r0, #0
	bl memset
	ldr r0, _021D84DC ; =MOD17_021D8FC8
	add r1, r5, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	add r0, r4, #0
	bl OverlayManager_GetField18
	add r4, r0, #0
	ldr r1, [r4, #0xc]
	ldr r0, _021D84E0 ; =0x000006C8
	str r1, [r5, r0]
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	mov r1, #0x5e
	lsl r1, r1, #2
	ldr r0, [r4, #8]
	add r1, r5, r1
	bl MOD17_021DAFA4
	add r0, r5, #0
	bl MOD17_021D8D60
	mov r1, #0x35
	lsl r1, r1, #4
	add r0, r5, r1
	sub r1, #0x81
	mov r2, #0xd
	bl MOD17_021DB9F4
	mov r0, #0xaf
	lsl r0, r0, #2
	mov r1, #0xd
	bl MOD17_021D74E0
	mov r1, #0xd6
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r1, [r4]
	add r0, r5, #0
	mov r2, #0xa
	bl MOD17_021D8DA8
	add r0, r5, #0
	bl MOD17_021D8E84
	add r0, r5, #0
	mov r1, #0
	bl MOD17_021D8FD0
	add r0, r5, #0
	bl MOD17_021D9024
	ldr r1, [r4, #0xc]
	add r0, r5, #0
	bl MOD17_021D9228
	ldr r0, _021D84E4 ; =0x00000554
	mov r2, #0xfa
	add r1, r5, r0
	str r1, [sp]
	mov r1, #1
	sub r0, #0xc8
	lsl r2, r2, #2
	str r1, [sp, #4]
	add r1, r5, r2
	sub r2, #0x8c
	add r0, r5, r0
	add r2, r5, r2
	add r3, r5, #0
	bl MOD17_021DB038
	mov r0, #0xd
	bl FUN_02014590
	ldr r1, _021D84E8 ; =0x000006A4
	str r0, [r5, r1]
	mov r0, #0xd
	mov r1, #1
	bl AllocWindows
	ldr r2, _021D84EC ; =0x000006A8
	mov r1, #0
	str r0, [r5, r2]
	sub r2, #0xc
	str r1, [r5, r2]
	mov r0, #0x35
	add r2, r1, #0
	bl FUN_0200433C
	mov r0, #1
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D84D8: .word 0x000006D8
_021D84DC: .word MOD17_021D8FC8
_021D84E0: .word 0x000006C8
_021D84E4: .word 0x00000554
_021D84E8: .word 0x000006A4
_021D84EC: .word 0x000006A8
	thumb_func_end MOD17_021D83E4

	thumb_func_start MOD17_021D84F0
MOD17_021D84F0: ; 0x021D84F0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, r7, #0
	mov r6, #0
	bl OverlayManager_GetField18
	ldr r1, [r5]
	cmp r1, #0xc
	bhi _021D85BA
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8518: ; jump table
	.short _021D8532 - _021D8518 - 2 ; case 0
	.short _021D8532 - _021D8518 - 2 ; case 1
	.short _021D854E - _021D8518 - 2 ; case 2
	.short _021D855E - _021D8518 - 2 ; case 3
	.short _021D858A - _021D8518 - 2 ; case 4
	.short _021D85AA - _021D8518 - 2 ; case 5
	.short _021D85D8 - _021D8518 - 2 ; case 6
	.short _021D860C - _021D8518 - 2 ; case 7
	.short _021D8636 - _021D8518 - 2 ; case 8
	.short _021D8678 - _021D8518 - 2 ; case 9
	.short _021D86B2 - _021D8518 - 2 ; case 10
	.short _021D86D4 - _021D8518 - 2 ; case 11
	.short _021D86F2 - _021D8518 - 2 ; case 12
_021D8532:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #0xd
	str r1, [sp, #8]
	mov r1, #5
	add r2, r1, #0
	add r3, r6, #0
	bl FUN_0200E1D0
	mov r0, #2
	str r0, [r5]
	b _021D8710
_021D854E:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D85BA
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8710
_021D855E:
	ldr r0, [r0, #0x1c]
	cmp r0, #1
	bne _021D8584
	mov r0, #1
	bl FUN_02002BB8
	ldr r0, _021D871C ; =0x00000554
	ldr r2, _021D8720 ; =0x00000151
	add r0, r4, r0
	mov r1, #0x1a
	mov r3, #0x2f
	bl MOD17_021DCB80
	ldr r1, _021D8724 ; =0x000006CC
	str r0, [r4, r1]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8710
_021D8584:
	mov r0, #6
	str r0, [r5]
	b _021D8710
_021D858A:
	ldr r0, _021D8724 ; =0x000006CC
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D85BA
	ldr r0, _021D871C ; =0x00000554
	add r0, r4, r0
	bl MOD17_021DCBC0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8710
_021D85AA:
	ldr r0, _021D8728 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	and r1, r0
	ldr r0, _021D872C ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	orr r0, r1
	bne _021D85BC
_021D85BA:
	b _021D8710
_021D85BC:
	ldr r0, _021D871C ; =0x00000554
	ldr r2, _021D8720 ; =0x00000151
	add r0, r4, r0
	mov r1, #0x1a
	mov r3, #0x30
	bl MOD17_021DCB48
	add r0, r6, #0
	bl FUN_02002BB8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8710
_021D85D8:
	ldr r1, _021D8730 ; =0x0000069C
	ldr r0, [r4, r1]
	cmp r0, #3
	bne _021D85EE
	add r1, r1, #4
	add r0, r4, #0
	add r1, r4, r1
	bl MOD17_021D92BC
	mov r0, #7
	str r0, [r5]
_021D85EE:
	ldr r0, _021D8734 ; =0x0000048C
	add r0, r4, r0
	bl MOD17_021DAF64
	add r0, r4, #0
	bl MOD17_021D9BE8
	ldr r0, _021D871C ; =0x00000554
	add r0, r4, r0
	bl MOD17_021DCB30
	add r0, r4, #0
	bl MOD17_021D9140
	b _021D8710
_021D860C:
	mov r0, #0x6a
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _021D8710
	add r1, r6, #0
	str r1, [r4, r0]
	mov r1, #8
	str r1, [r5]
	mov r1, #4
	sub r0, r0, #4
	str r1, [r4, r0]
	mov r1, #0x47
	lsl r1, r1, #4
	add r0, r4, r1
	sub r1, #0x88
	add r1, r4, r1
	mov r2, #0xe
	bl MOD17_021DD464
	b _021D8710
_021D8636:
	ldr r1, _021D8730 ; =0x0000069C
	ldr r0, [r4, r1]
	cmp r0, #9
	bne _021D864E
	add r1, r1, #4
	add r0, r4, #0
	add r1, r4, r1
	bl MOD17_021D942C
	mov r0, #0xa
	str r0, [r5]
	b _021D8710
_021D864E:
	cmp r0, #8
	bne _021D8662
	mov r0, #9
	str r0, [r5]
	mov r0, #5
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD17_021D9C3C
	b _021D8710
_021D8662:
	add r0, r4, #0
	bl MOD17_021D98F0
	ldr r1, _021D8730 ; =0x0000069C
	str r0, [r4, r1]
	mov r0, #0x47
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD17_021DD488
	b _021D8710
_021D8678:
	ldr r0, _021D8730 ; =0x0000069C
	ldr r1, [r4, r0]
	cmp r1, #6
	bne _021D868C
	mov r1, #1
	add r0, #0x10
	str r1, [r4, r0]
	mov r0, #0xb
	str r0, [r5]
	b _021D8710
_021D868C:
	cmp r1, #7
	bne _021D869C
	add r1, r6, #0
	add r0, #0x10
	str r1, [r4, r0]
	mov r0, #0xb
	str r0, [r5]
	b _021D8710
_021D869C:
	add r0, r4, #0
	bl MOD17_021D9CAC
	ldr r1, _021D8730 ; =0x0000069C
	str r0, [r4, r1]
	mov r0, #0x47
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD17_021DD488
	b _021D8710
_021D86B2:
	mov r0, #0x6a
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _021D8710
	add r2, r6, #0
	str r2, [r4, r0]
	mov r1, #6
	str r1, [r5]
	sub r0, r0, #4
	str r2, [r4, r0]
	mov r0, #0x47
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD17_021DD494
	b _021D8710
_021D86D4:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #0xd
	str r1, [sp, #8]
	add r1, r6, #0
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8710
_021D86F2:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D8710
	add r0, r6, #0
	str r0, [r5]
	ldr r0, _021D8730 ; =0x0000069C
	mov r1, #0xa
	str r1, [r4, r0]
	mov r0, #0x47
	lsl r0, r0, #4
	add r0, r4, r0
	mov r6, #1
	bl MOD17_021DD494
_021D8710:
	add r0, r4, #0
	bl MOD17_021D8D8C
	add r0, r6, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D871C: .word 0x00000554
_021D8720: .word 0x00000151
_021D8724: .word 0x000006CC
_021D8728: .word gMain
_021D872C: .word gMain + 0x40
_021D8730: .word 0x0000069C
_021D8734: .word 0x0000048C
	thumb_func_end MOD17_021D84F0

	thumb_func_start MOD17_021D8738
MOD17_021D8738: ; 0x021D8738
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, r6, #0
	bl OverlayManager_GetField18
	add r5, r0, #0
	ldr r0, _021D8808 ; =0x000006AC
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021D8768
	ldr r0, [r5, #0x10]
	mov r1, #7
	bl FUN_0202A170
	mov r1, #0xfa
	lsl r1, r1, #2
	ldr r0, [r5, #4]
	ldr r2, [r5, #0x14]
	add r1, r4, r1
	bl MOD17_021D95AC
_021D8768:
	ldr r1, [r5, #0x18]
	cmp r1, #0
	beq _021D8780
	ldr r0, _021D8808 ; =0x000006AC
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021D877C
	mov r0, #1
	str r0, [r1]
	b _021D8780
_021D877C:
	mov r0, #0
	str r0, [r1]
_021D8780:
	ldr r0, _021D880C ; =0x000006A4
	ldr r0, [r4, r0]
	bl FUN_020145A8
	ldr r0, _021D8810 ; =0x000006A8
	mov r1, #1
	ldr r0, [r4, r0]
	bl WindowArray_dtor
	add r0, r4, #0
	bl MOD17_021D92AC
	ldr r0, _021D8814 ; =0x0000048C
	add r0, r4, r0
	bl MOD17_021DB08C
	add r0, r4, #0
	bl MOD17_021D912C
	add r0, r4, #0
	bl MOD17_021D9014
	add r0, r4, #0
	bl MOD17_021D8E60
	add r0, r4, #0
	bl MOD17_021D8F40
	mov r0, #0xd6
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD17_021D750C
	mov r0, #0xd6
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r0, #8
	add r0, r4, r0
	bl MOD17_021DBA1C
	add r0, r4, #0
	bl MOD17_021D8D94
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl FUN_0201CD04
	cmp r0, #1
	beq _021D87F0
	bl GF_AssertFail
_021D87F0:
	add r0, r6, #0
	bl OverlayManager_FreeData
	mov r0, #0xd
	bl DestroyHeap
	mov r0, #0xe
	bl DestroyHeap
	mov r0, #1
	pop {r4, r5, r6, pc}
	nop
_021D8808: .word 0x000006AC
_021D880C: .word 0x000006A4
_021D8810: .word 0x000006A8
_021D8814: .word 0x0000048C
	thumb_func_end MOD17_021D8738

	thumb_func_start MOD17_021D8818
MOD17_021D8818: ; 0x021D8818
	push {r3, r4, r5, lr}
	sub sp, #8
	mov r2, #2
	add r5, r0, #0
	mov r0, #3
	mov r1, #0xd
	lsl r2, r2, #0x10
	bl CreateHeap
	mov r2, #1
	mov r0, #3
	mov r1, #0xe
	lsl r2, r2, #0x12
	bl CreateHeap
	ldr r1, _021D897C ; =0x000006D8
	add r0, r5, #0
	mov r2, #0xd
	bl OverlayManager_CreateAndGetData
	ldr r2, _021D897C ; =0x000006D8
	mov r1, #0
	add r4, r0, #0
	bl memset
	ldr r0, _021D8980 ; =MOD17_021D8FC8
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	add r0, r5, #0
	bl OverlayManager_GetField18
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	ldr r1, _021D8984 ; =0x000006B4
	str r0, [r4, r1]
	ldr r2, [r5, #0x10]
	add r0, r1, #4
	str r2, [r4, r0]
	add r0, r1, #0
	ldr r2, [r5, #0x14]
	add r0, #8
	str r2, [r4, r0]
	add r0, r1, #0
	ldr r2, [r5, #8]
	add r0, #0xc
	str r2, [r4, r0]
	ldr r0, [r5, #0x1c]
	add r1, #0x10
	str r0, [r4, r1]
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	mov r1, #0x5e
	lsl r1, r1, #2
	ldr r0, [r5, #0x18]
	add r1, r4, r1
	bl MOD17_021DAFA4
	add r0, r4, #0
	bl MOD17_021D8D60
	ldr r0, [r4, #0x3c]
	mov r1, #0
	bl FUN_0201FD98
	bl FUN_02033E74
	mov r0, #1
	mov r1, #0x10
	bl FUN_02008D44
	mov r0, #1
	bl FUN_02008DDC
	mov r1, #0x35
	lsl r1, r1, #4
	add r0, r4, r1
	sub r1, #0x81
	mov r2, #0xd
	bl MOD17_021DB9F4
	mov r0, #0xaf
	lsl r0, r0, #2
	mov r1, #0xd
	bl MOD17_021D74E0
	mov r1, #0xd6
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r1, [r5, #0x20]
	ldr r0, _021D8988 ; =0x000006C8
	str r1, [r4, r0]
	sub r1, r0, #4
	ldr r1, [r4, r1]
	ldrb r1, [r1, #0x16]
	cmp r1, #0
	bne _021D88F2
	ldr r0, [r5, #0xc]
	bl MOD17_021D9C08
	mov r1, #0x6b
	lsl r1, r1, #4
	str r0, [r4, r1]
	b _021D88F8
_021D88F2:
	mov r1, #0x14
	sub r0, #0x18
	str r1, [r4, r0]
_021D88F8:
	mov r2, #0x6b
	lsl r2, r2, #4
	ldr r1, [r5]
	ldr r2, [r4, r2]
	add r0, r4, #0
	bl MOD17_021D8E18
	add r0, r4, #0
	bl MOD17_021D8E84
	add r0, r4, #0
	mov r1, #0
	bl MOD17_021D8FD0
	add r0, r4, #0
	bl MOD17_021D90A8
	ldr r0, [r5, #0x20]
	mov r1, #0x6b
	str r0, [sp]
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	ldr r2, [r5, #8]
	ldr r3, [r5, #0x1c]
	add r0, r4, #0
	bl MOD17_021D926C
	ldr r0, _021D898C ; =0x00000554
	mov r2, #0xfa
	add r1, r4, r0
	str r1, [sp]
	mov r1, #0
	sub r0, #0xc8
	lsl r2, r2, #2
	str r1, [sp, #4]
	add r1, r4, r2
	sub r2, #0x8c
	add r0, r4, r0
	add r2, r4, r2
	add r3, r4, #0
	bl MOD17_021DB038
	mov r0, #0xd
	bl FUN_02014590
	ldr r1, _021D8990 ; =0x000006A4
	str r0, [r4, r1]
	mov r0, #0xd
	mov r1, #1
	bl AllocWindows
	ldr r1, _021D8994 ; =0x000006A8
	mov r2, #0
	str r0, [r4, r1]
	add r0, r1, #0
	sub r0, #0xc
	add r1, #0x1c
	str r2, [r4, r0]
	ldr r0, [r4, r1]
	ldrb r0, [r0, #0x16]
	bl FUN_020833D4
	mov r0, #1
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_021D897C: .word 0x000006D8
_021D8980: .word MOD17_021D8FC8
_021D8984: .word 0x000006B4
_021D8988: .word 0x000006C8
_021D898C: .word 0x00000554
_021D8990: .word 0x000006A4
_021D8994: .word 0x000006A8
	thumb_func_end MOD17_021D8818

	thumb_func_start MOD17_021D8998
MOD17_021D8998: ; 0x021D8998
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	bl OverlayManager_GetData
	ldr r1, [r4]
	add r5, r0, #0
	mov r6, #0
	cmp r1, #0x14
	bhi _021D89FA
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021D89B8: ; jump table
	.short _021D89E2 - _021D89B8 - 2 ; case 0
	.short _021D89F2 - _021D89B8 - 2 ; case 1
	.short _021D8A04 - _021D89B8 - 2 ; case 2
	.short _021D8A3C - _021D89B8 - 2 ; case 3
	.short _021D8A5A - _021D89B8 - 2 ; case 4
	.short _021D8A72 - _021D89B8 - 2 ; case 5
	.short _021D8A90 - _021D89B8 - 2 ; case 6
	.short _021D8AB2 - _021D89B8 - 2 ; case 7
	.short _021D8AD0 - _021D89B8 - 2 ; case 8
	.short _021D8AE8 - _021D89B8 - 2 ; case 9
	.short _021D8B0A - _021D89B8 - 2 ; case 10
	.short _021D8B1C - _021D89B8 - 2 ; case 11
	.short _021D8B3A - _021D89B8 - 2 ; case 12
	.short _021D8B56 - _021D89B8 - 2 ; case 13
	.short _021D8BBC - _021D89B8 - 2 ; case 14
	.short _021D8BEA - _021D89B8 - 2 ; case 15
	.short _021D8C64 - _021D89B8 - 2 ; case 16
	.short _021D8C64 - _021D89B8 - 2 ; case 17
	.short _021D8C64 - _021D89B8 - 2 ; case 18
	.short _021D8C04 - _021D89B8 - 2 ; case 19
	.short _021D8C34 - _021D89B8 - 2 ; case 20
_021D89E2:
	mov r0, #0x2a
	mov r1, #0x1e
	bl FUN_020053CC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D89F2:
	bl FUN_02005404
	cmp r0, #0
	beq _021D89FC
_021D89FA:
	b _021D8C64
_021D89FC:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8A04:
	bl MOD17_021D9778
	mov r2, #0x6b
	lsl r2, r2, #4
	ldr r2, [r5, r2]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD17_021D9BA4
	ldr r0, _021D8C70 ; =0x000006B8
	ldr r0, [r5, r0]
	cmp r0, #3
	beq _021D8A28
	add r0, r5, #0
	mov r1, #0x1a
	bl MOD17_021D9B9C
	b _021D8A30
_021D8A28:
	add r0, r5, #0
	mov r1, #0x1c
	bl MOD17_021D9B9C
_021D8A30:
	ldr r1, _021D8C74 ; =0x000006CC
	str r0, [r5, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8A3C:
	ldr r0, _021D8C74 ; =0x000006CC
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D8B42
	add r0, r5, #0
	bl MOD17_021D9BC4
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8A5A:
	mov r1, #0x1b
	lsl r1, r1, #6
	ldr r1, [r5, r1]
	add r1, #0x1d
	bl MOD17_021D9B9C
	ldr r1, _021D8C74 ; =0x000006CC
	str r0, [r5, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8A72:
	ldr r0, _021D8C74 ; =0x000006CC
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D8B42
	add r0, r5, #0
	bl MOD17_021D9BC4
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8A90:
	ldr r1, _021D8C70 ; =0x000006B8
	ldr r1, [r5, r1]
	cmp r1, #3
	beq _021D8AA0
	mov r1, #0x2a
	bl MOD17_021D9B9C
	b _021D8AA6
_021D8AA0:
	mov r1, #0x29
	bl MOD17_021D9B9C
_021D8AA6:
	ldr r1, _021D8C74 ; =0x000006CC
	str r0, [r5, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8AB2:
	ldr r0, _021D8C74 ; =0x000006CC
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D8B42
	add r0, r5, #0
	bl MOD17_021D9BC4
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8AD0:
	ldr r0, _021D8C78 ; =0x000006C4
	ldr r0, [r5, r0]
	ldrb r0, [r0, #0x16]
	cmp r0, #0
	beq _021D8AE0
	mov r0, #2
	bl FUN_02031588
_021D8AE0:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8AE8:
	ldr r0, _021D8C78 ; =0x000006C4
	ldr r0, [r5, r0]
	ldrb r0, [r0, #0x16]
	cmp r0, #0
	beq _021D8B04
	mov r0, #2
	bl FUN_020315D8
	cmp r0, #0
	beq _021D8B42
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8B04:
	add r0, r1, #1
	str r0, [r4]
	b _021D8C64
_021D8B0A:
	bl MOD17_021D9800
	ldr r0, _021D8C7C ; =0x00000643
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8B1C:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #0xd
	str r1, [sp, #8]
	mov r1, #0x11
	mov r2, #0x13
	add r3, r6, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8B3A:
	bl FUN_0200E308
	cmp r0, #0
	bne _021D8B44
_021D8B42:
	b _021D8C64
_021D8B44:
	ldr r1, _021D8C80 ; =0x00000491
	mov r0, #7
	add r2, r6, #0
	bl FUN_0200433C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8B56:
	ldr r0, _021D8C84 ; =0x0000069C
	ldr r1, [r5, r0]
	cmp r1, #3
	bne _021D8B86
	add r0, #0x28
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02083A7C
	ldr r0, _021D8C78 ; =0x000006C4
	ldr r0, [r5, r0]
	ldrb r0, [r0, #0x16]
	cmp r0, #0
	beq _021D8B80
	ldr r0, _021D8C88 ; =0x00000554
	ldr r2, _021D8C8C ; =0x00000151
	add r0, r5, r0
	mov r1, #0x1a
	mov r3, #0x2e
	bl MOD17_021DCB48
_021D8B80:
	mov r0, #0xe
	str r0, [r4]
	b _021D8C64
_021D8B86:
	ldr r0, _021D8C88 ; =0x00000554
	add r0, r5, r0
	bl MOD17_021DCBE4
	cmp r0, #0
	bne _021D8B9E
	mov r0, #0xf
	str r0, [r4]
	mov r0, #0x1a
	lsl r0, r0, #6
	bl PlaySE
_021D8B9E:
	ldr r0, _021D8C90 ; =0x0000048C
	add r0, r5, r0
	bl MOD17_021DAF64
	add r0, r5, #0
	bl MOD17_021D9BE8
	ldr r0, _021D8C88 ; =0x00000554
	add r0, r5, r0
	bl MOD17_021DCB30
	add r0, r5, #0
	bl MOD17_021D9140
	b _021D8C64
_021D8BBC:
	ldr r0, _021D8C88 ; =0x00000554
	add r0, r5, r0
	bl MOD17_021DCBE4
	cmp r0, #0
	bne _021D8BD4
	mov r0, #0xf
	str r0, [r4]
	mov r0, #0x1a
	lsl r0, r0, #6
	bl PlaySE
_021D8BD4:
	add r0, r5, #0
	bl MOD17_021D9BE8
	ldr r0, _021D8C88 ; =0x00000554
	add r0, r5, r0
	bl MOD17_021DCB30
	add r0, r5, #0
	bl MOD17_021D9E28
	b _021D8C64
_021D8BEA:
	ldr r0, _021D8C88 ; =0x00000554
	add r0, r5, r0
	bl MOD17_021DCB30
	ldr r0, _021D8C88 ; =0x00000554
	add r0, r5, r0
	bl MOD17_021DCBF4
	cmp r0, #0
	beq _021D8C64
	mov r0, #0x13
	str r0, [r4]
	b _021D8C64
_021D8C04:
	mov r0, #0x1a
	lsl r0, r0, #6
	bl FUN_02005508
	cmp r0, #1
	beq _021D8C64
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #0xd
	str r1, [sp, #8]
	mov r1, #0x1a
	add r2, r1, #0
	add r3, r6, #0
	bl FUN_0200E1D0
	ldr r0, _021D8C94 ; =0x00000684
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C64
_021D8C34:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D8C64
	add r0, r6, #0
	str r0, [r4]
	mov r2, #1
	ldr r0, _021D8C84 ; =0x0000069C
	mov r1, #0xa
	str r1, [r5, r0]
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D8C98 ; =0xFFFF1FFF
	mov r6, #1
	and r0, r1
	str r0, [r2]
	mov r0, #0xfa
	lsl r0, r0, #2
	add r1, r6, #0
	add r0, r5, r0
	sub r1, #0x41
	mov r2, #0x28
	bl MOD17_021DA118
_021D8C64:
	add r0, r5, #0
	bl MOD17_021D8D8C
	add r0, r6, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D8C70: .word 0x000006B8
_021D8C74: .word 0x000006CC
_021D8C78: .word 0x000006C4
_021D8C7C: .word 0x00000643
_021D8C80: .word 0x00000491
_021D8C84: .word 0x0000069C
_021D8C88: .word 0x00000554
_021D8C8C: .word 0x00000151
_021D8C90: .word 0x0000048C
_021D8C94: .word 0x00000684
_021D8C98: .word 0xFFFF1FFF
	thumb_func_end MOD17_021D8998

	thumb_func_start MOD17_021D8C9C
MOD17_021D8C9C: ; 0x021D8C9C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, r5, #0
	bl OverlayManager_GetField18
	ldr r2, _021D8D50 ; =0x000006B4
	add r3, r0, #0
	mov r1, #0xfa
	ldr r0, [r3, #4]
	lsl r1, r1, #2
	ldr r2, [r4, r2]
	ldr r3, [r3, #0x24]
	add r1, r4, r1
	bl MOD17_021D964C
	ldr r0, _021D8D54 ; =0x000006A4
	ldr r0, [r4, r0]
	bl FUN_020145A8
	ldr r0, _021D8D58 ; =0x000006A8
	mov r1, #1
	ldr r0, [r4, r0]
	bl WindowArray_dtor
	add r0, r4, #0
	bl MOD17_021D92AC
	ldr r0, _021D8D5C ; =0x0000048C
	add r0, r4, r0
	bl MOD17_021DB08C
	add r0, r4, #0
	bl MOD17_021D912C
	add r0, r4, #0
	bl MOD17_021D9014
	add r0, r4, #0
	bl MOD17_021D8E60
	add r0, r4, #0
	bl MOD17_021D8F40
	mov r0, #0xd6
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD17_021D750C
	mov r0, #0xd6
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r0, #8
	add r0, r4, r0
	bl MOD17_021DBA1C
	add r0, r4, #0
	bl MOD17_021D8D94
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl FUN_0201CD04
	cmp r0, #1
	beq _021D8D30
	bl GF_AssertFail
_021D8D30:
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0xd
	bl DestroyHeap
	mov r0, #0xe
	bl DestroyHeap
	bl FUN_02083404
	bl FUN_02033ED0
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_021D8D50: .word 0x000006B4
_021D8D54: .word 0x000006A4
_021D8D58: .word 0x000006A8
_021D8D5C: .word 0x0000048C
	thumb_func_end MOD17_021D8C9C

	thumb_func_start MOD17_021D8D60
MOD17_021D8D60: ; 0x021D8D60
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	bl MOD17_021D7794
	add r0, r4, #0
	bl MOD17_021D77D4
	add r0, r4, #0
	add r1, sp, #0
	bl MOD17_021D7A00
	add r0, r4, #0
	add r1, sp, #0
	bl MOD17_021D78A0
	add r0, sp, #0
	bl MOD17_021D7A24
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D8D60

	thumb_func_start MOD17_021D8D8C
MOD17_021D8D8C: ; 0x021D8D8C
	ldr r3, _021D8D90 ; =MOD17_021D786C
	bx r3
	.align 2, 0
_021D8D90: .word MOD17_021D786C
	thumb_func_end MOD17_021D8D8C

	thumb_func_start MOD17_021D8D94
MOD17_021D8D94: ; 0x021D8D94
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021D78BC
	add r0, r4, #0
	bl MOD17_021D7828
	bl MOD17_021D77B4
	pop {r4, pc}
	thumb_func_end MOD17_021D8D94

	thumb_func_start MOD17_021D8DA8
MOD17_021D8DA8: ; 0x021D8DA8
	push {r4, r5, lr}
	sub sp, #0x34
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	mov r1, #0xd6
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x10]
	lsl r1, r1, #2
	str r0, [sp, #0x18]
	ldr r0, [r5, #0x28]
	str r0, [sp, #0x1c]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x38]
	str r2, [sp, #0x30]
	str r0, [sp, #0x24]
	ldr r0, [r5, r1]
	str r0, [sp, #0x28]
	add r0, r1, #0
	sub r0, #8
	add r0, r5, r0
	add r1, #0x90
	str r0, [sp, #0x2c]
	add r0, r5, r1
	add r1, sp, #0x10
	bl MOD17_021D9F80
	mov r0, #0xfa
	lsl r0, r0, #2
	add r0, r5, r0
	add r1, r4, #0
	add r2, sp, #0
	mov r3, #0xe
	bl MOD17_021DA024
	add r0, r5, #0
	add r1, sp, #0
	bl MOD17_021DB6D8
	mov r0, #0xfa
	lsl r0, r0, #2
	add r0, r5, r0
	bl MOD17_021DA178
	mov r0, #0xfa
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	mov r2, #0xe
	bl MOD17_021DA2F0
	add sp, #0x34
	pop {r4, r5, pc}
	thumb_func_end MOD17_021D8DA8

	thumb_func_start MOD17_021D8E18
MOD17_021D8E18: ; 0x021D8E18
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	bl MOD17_021D8DA8
	mov r0, #0x46
	lsl r0, r0, #4
	add r0, r4, r0
	add r1, sp, #0xc
	add r2, sp, #8
	bl MOD17_021DB878
	mov r0, #0x46
	lsl r0, r0, #4
	add r0, r4, r0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021DB960
	ldr r3, [sp, #8]
	mov r0, #0x46
	lsr r2, r3, #0x1f
	add r2, r3, r2
	asr r3, r2, #1
	ldr r2, [sp]
	lsl r0, r0, #4
	sub r3, r3, r2
	mov r2, #0x8d
	add r0, r4, r0
	mov r1, #0xc0
	sub r2, r2, r3
	bl MOD17_021DB7F4
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D8E18

	thumb_func_start MOD17_021D8E60
MOD17_021D8E60: ; 0x021D8E60
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xfa
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021DA33C
	mov r0, #0xfa
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021DA100
	mov r0, #0xfa
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021D9FD4
	pop {r4, pc}
	thumb_func_end MOD17_021D8E60

	thumb_func_start MOD17_021D8E84
MOD17_021D8E84: ; 0x021D8E84
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	ldr r0, [r5]
	str r0, [sp]
	ldr r0, [r5, #4]
	str r0, [sp, #4]
	ldr r0, [r5, #0x10]
	str r0, [sp, #8]
	ldr r0, [r5, #0x28]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x38]
	str r0, [sp, #0x10]
	mov r0, #0x5e
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #0x28]
	mov r0, #0xd6
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	str r1, [sp, #0x14]
	add r1, r0, #0
	sub r1, #8
	add r1, r5, r1
	str r1, [sp, #0x18]
	mov r1, #0xe
	str r1, [sp, #0x1c]
	mov r1, #2
	str r1, [sp, #0x20]
	mov r1, #1
	add r0, r0, #4
	str r1, [sp, #0x24]
	add r0, r5, r0
	add r1, sp, #0
	bl MOD17_021DA5A8
	mov r0, #0xd7
	lsl r0, r0, #2
	mov r1, #0
	add r0, r5, r0
	add r2, r1, #0
	bl MOD17_021DA918
	mov r6, #0
_021D8EDC:
	mov r0, #0x5e
	lsl r0, r0, #2
	add r0, r5, r0
	add r1, r6, #0
	bl MOD17_021DAFF4
	add r7, r0, #0
	mov r4, #0
	cmp r7, #0
	ble _021D8F04
_021D8EF0:
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	add r2, r6, #0
	bl MOD17_021DA6FC
	add r4, r4, #1
	cmp r4, r7
	blt _021D8EF0
_021D8F04:
	add r6, r6, #1
	cmp r6, #0x64
	blt _021D8EDC
	mov r7, #0xd7
	mov r6, #0x5e
	mov r4, #0
	lsl r7, r7, #2
	lsl r6, r6, #2
_021D8F14:
	add r0, r5, r6
	add r1, r4, #0
	bl MOD17_021DB008
	add r2, r0, #0
	cmp r2, #0x12
	bge _021D8F2A
	add r0, r5, r7
	mov r1, #1
	bl MOD17_021DA6FC
_021D8F2A:
	add r4, r4, #1
	cmp r4, #0x12
	blt _021D8F14
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r5, r0
	bl MOD17_021DA844
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021D8E84

	thumb_func_start MOD17_021D8F40
MOD17_021D8F40: ; 0x021D8F40
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021DAA60
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021DA818
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021DA5E0
	pop {r4, pc}
	thumb_func_end MOD17_021D8F40

	thumb_func_start MOD17_021D8F64
MOD17_021D8F64: ; 0x021D8F64
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, _021D8FC4 ; =0x04000008
	mov r2, #3
	ldrh r3, [r0]
	mov r1, #1
	bic r3, r2
	orr r1, r3
	strh r1, [r0]
	ldrh r1, [r0, #2]
	bic r1, r2
	strh r1, [r0, #2]
	ldrh r3, [r0, #4]
	mov r1, #2
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #4]
	ldrh r3, [r0, #6]
	mov r1, #3
	bic r3, r2
	add r2, r3, #0
	orr r2, r1
	strh r2, [r0, #6]
	add r3, r1, #0
	ldr r0, [r4, #0x38]
	add r2, r1, #0
	sub r3, #0x13
	bl BgSetPosTextAndCommit
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl MOD17_021DA9AC
	mov r1, #0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	mov r2, #2
	add r3, r1, #0
	str r1, [sp]
	bl MOD17_021DA9F8
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D8FC4: .word 0x04000008
	thumb_func_end MOD17_021D8F64

	thumb_func_start MOD17_021D8FC8
MOD17_021D8FC8: ; 0x021D8FC8
	ldr r3, _021D8FCC ; =MOD17_021D7AE4
	bx r3
	.align 2, 0
_021D8FCC: .word MOD17_021D7AE4
	thumb_func_end MOD17_021D8FC8

	thumb_func_start MOD17_021D8FD0
MOD17_021D8FD0: ; 0x021D8FD0
	push {r3, lr}
	sub sp, #0x30
	ldr r2, [r0, #0x38]
	str r2, [sp]
	mov r2, #0x19
	str r2, [sp, #4]
	lsl r2, r1, #1
	add r1, r2, #0
	add r1, #0x79
	str r1, [sp, #8]
	mov r1, #0x85
	str r1, [sp, #0xc]
	mov r1, #1
	add r2, #0x7a
	str r2, [sp, #0x10]
	mov r2, #0
	str r1, [sp, #0x1c]
	str r1, [sp, #0x20]
	mov r1, #2
	str r1, [sp, #0x24]
	mov r1, #0xe
	str r1, [sp, #0x2c]
	ldr r1, _021D9010 ; =0x000004A8
	str r2, [sp, #0x14]
	add r0, r0, r1
	add r1, sp, #0
	str r2, [sp, #0x18]
	str r2, [sp, #0x28]
	bl MOD17_021DBD04
	add sp, #0x30
	pop {r3, pc}
	.align 2, 0
_021D9010: .word 0x000004A8
	thumb_func_end MOD17_021D8FD0

	thumb_func_start MOD17_021D9014
MOD17_021D9014: ; 0x021D9014
	ldr r1, _021D901C ; =0x000004A8
	ldr r3, _021D9020 ; =MOD17_021DBD4C
	add r0, r0, r1
	bx r3
	.align 2, 0
_021D901C: .word 0x000004A8
_021D9020: .word MOD17_021DBD4C
	thumb_func_end MOD17_021D9014

	thumb_func_start MOD17_021D9024
MOD17_021D9024: ; 0x021D9024
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, _021D9090 ; =0x000004D4
	add r1, r4, #0
	add r0, r4, r0
	bl MOD17_021DC304
	ldr r0, _021D9090 ; =0x000004D4
	mov r1, #0
	ldr r2, _021D9094 ; =MOD17_021D9180
	add r0, r4, r0
	add r3, r4, #0
	str r1, [sp]
	bl MOD17_021DC538
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D9090 ; =0x000004D4
	ldr r2, _021D9098 ; =MOD17_021D91A0
	add r0, r4, r0
	mov r1, #1
	add r3, r4, #0
	bl MOD17_021DC538
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D9090 ; =0x000004D4
	ldr r2, _021D909C ; =MOD17_021D91C0
	add r0, r4, r0
	mov r1, #2
	add r3, r4, #0
	bl MOD17_021DC538
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D9090 ; =0x000004D4
	ldr r2, _021D90A0 ; =MOD17_021D91F4
	add r0, r4, r0
	mov r1, #3
	add r3, r4, #0
	bl MOD17_021DC538
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D9090 ; =0x000004D4
	ldr r2, _021D90A4 ; =MOD17_021D9160
	add r0, r4, r0
	mov r1, #4
	add r3, r4, #0
	bl MOD17_021DC538
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D9090: .word 0x000004D4
_021D9094: .word MOD17_021D9180
_021D9098: .word MOD17_021D91A0
_021D909C: .word MOD17_021D91C0
_021D90A0: .word MOD17_021D91F4
_021D90A4: .word MOD17_021D9160
	thumb_func_end MOD17_021D9024

	thumb_func_start MOD17_021D90A8
MOD17_021D90A8: ; 0x021D90A8
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, _021D9114 ; =0x000004D4
	add r1, r4, #0
	add r0, r4, r0
	bl MOD17_021DC304
	ldr r0, _021D9114 ; =0x000004D4
	mov r1, #0
	ldr r2, _021D9118 ; =MOD17_021D9180
	add r0, r4, r0
	add r3, r4, #0
	str r1, [sp]
	bl MOD17_021DC538
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D9114 ; =0x000004D4
	ldr r2, _021D911C ; =MOD17_021D91A0
	add r0, r4, r0
	mov r1, #1
	add r3, r4, #0
	bl MOD17_021DC538
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D9114 ; =0x000004D4
	ldr r2, _021D9120 ; =MOD17_021D91C0
	add r0, r4, r0
	mov r1, #2
	add r3, r4, #0
	bl MOD17_021DC538
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D9114 ; =0x000004D4
	ldr r2, _021D9124 ; =MOD17_021D91F4
	add r0, r4, r0
	mov r1, #3
	add r3, r4, #0
	bl MOD17_021DC538
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D9114 ; =0x000004D4
	ldr r2, _021D9128 ; =MOD17_021D9160
	add r0, r4, r0
	mov r1, #4
	add r3, r4, #0
	bl MOD17_021DC538
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D9114: .word 0x000004D4
_021D9118: .word MOD17_021D9180
_021D911C: .word MOD17_021D91A0
_021D9120: .word MOD17_021D91C0
_021D9124: .word MOD17_021D91F4
_021D9128: .word MOD17_021D9160
	thumb_func_end MOD17_021D90A8

	thumb_func_start MOD17_021D912C
MOD17_021D912C: ; 0x021D912C
	add r1, r0, #0
	ldr r0, _021D9138 ; =0x000004D4
	ldr r3, _021D913C ; =MOD17_021DC468
	add r0, r1, r0
	bx r3
	nop
_021D9138: .word 0x000004D4
_021D913C: .word MOD17_021DC468
	thumb_func_end MOD17_021D912C

	thumb_func_start MOD17_021D9140
MOD17_021D9140: ; 0x021D9140
	ldr r1, _021D9148 ; =0x000004D4
	ldr r3, _021D914C ; =MOD17_021DC4CC
	add r0, r0, r1
	bx r3
	.align 2, 0
_021D9148: .word 0x000004D4
_021D914C: .word MOD17_021DC4CC
	thumb_func_end MOD17_021D9140

	thumb_func_start MOD17_021D9150
MOD17_021D9150: ; 0x021D9150
	ldr r1, _021D9158 ; =0x000004D4
	ldr r3, _021D915C ; =MOD17_021DC4E4
	add r0, r0, r1
	bx r3
	.align 2, 0
_021D9158: .word 0x000004D4
_021D915C: .word MOD17_021DC4E4
	thumb_func_end MOD17_021D9150

	thumb_func_start MOD17_021D9160
MOD17_021D9160: ; 0x021D9160
	push {r4, lr}
	mov r0, #0xd7
	add r4, r1, #0
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021DAAB8
	cmp r0, #0
	beq _021D9178
	ldr r0, _021D917C ; =0x0000069C
	mov r1, #3
	str r1, [r4, r0]
_021D9178:
	pop {r4, pc}
	nop
_021D917C: .word 0x0000069C
	thumb_func_end MOD17_021D9160

	thumb_func_start MOD17_021D9180
MOD17_021D9180: ; 0x021D9180
	push {r4, lr}
	mov r0, #0xd7
	add r4, r1, #0
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021DAA6C
	add r1, r0, #0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	mov r2, #0
	bl MOD17_021DA8B0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D9180

	thumb_func_start MOD17_021D91A0
MOD17_021D91A0: ; 0x021D91A0
	push {r4, lr}
	mov r0, #0xd7
	add r4, r1, #0
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021DAA6C
	add r1, r0, #0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	mov r2, #1
	bl MOD17_021DA8B0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D91A0

	thumb_func_start MOD17_021D91C0
MOD17_021D91C0: ; 0x021D91C0
	push {r4, lr}
	ldr r0, _021D91F0 ; =0x0000069C
	add r4, r1, #0
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D91EC
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl MOD17_021DAA7C
	add r2, r0, #0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl MOD17_021DA918
	ldr r0, _021D91F0 ; =0x0000069C
	mov r1, #0
	str r1, [r4, r0]
_021D91EC:
	pop {r4, pc}
	nop
_021D91F0: .word 0x0000069C
	thumb_func_end MOD17_021D91C0

	thumb_func_start MOD17_021D91F4
MOD17_021D91F4: ; 0x021D91F4
	push {r4, lr}
	ldr r0, _021D9224 ; =0x0000069C
	add r4, r1, #0
	ldr r0, [r4, r0]
	cmp r0, #1
	beq _021D9220
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #1
	bl MOD17_021DAA7C
	add r2, r0, #0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #1
	bl MOD17_021DA918
	ldr r0, _021D9224 ; =0x0000069C
	mov r1, #1
	str r1, [r4, r0]
_021D9220:
	pop {r4, pc}
	nop
_021D9224: .word 0x0000069C
	thumb_func_end MOD17_021D91F4

	thumb_func_start MOD17_021D9228
MOD17_021D9228: ; 0x021D9228
	push {r4, r5, lr}
	sub sp, #0x24
	add r4, r0, #0
	add r2, sp, #0
	mov r0, #0
	add r3, r1, #0
	add r5, r2, #0
	add r1, r0, #0
	stmia r5!, {r0, r1}
	stmia r5!, {r0, r1}
	stmia r5!, {r0, r1}
	stmia r5!, {r0, r1}
	str r0, [r5]
	ldr r0, [r4, #0x38]
	add r1, r2, #0
	str r0, [sp]
	ldr r0, [r4, #0x3c]
	mov r2, #0xf
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x40
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0x10]
	ldr r0, _021D9268 ; =0x00000554
	str r3, [sp, #0xc]
	add r0, r4, r0
	bl MOD17_021DC950
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_021D9268: .word 0x00000554
	thumb_func_end MOD17_021D9228

	thumb_func_start MOD17_021D926C
MOD17_021D926C: ; 0x021D926C
	push {r3, r4, lr}
	sub sp, #0x24
	ldr r4, [r0, #0x38]
	str r4, [sp]
	ldr r4, [r0, #0x3c]
	str r1, [sp, #0x10]
	ldr r1, _021D92A4 ; =0x00000151
	str r4, [sp, #4]
	str r1, [sp, #0x14]
	add r1, r2, #7
	str r1, [sp, #0x18]
	mov r1, #0x3c
	str r1, [sp, #0x1c]
	ldr r1, [sp, #0x30]
	add r4, r0, #0
	str r1, [sp, #0xc]
	ldr r1, _021D92A8 ; =0x00000554
	add r4, #0x40
	add r0, r0, r1
	add r1, sp, #0
	mov r2, #0x3f
	str r4, [sp, #8]
	str r3, [sp, #0x20]
	bl MOD17_021DC950
	add sp, #0x24
	pop {r3, r4, pc}
	nop
_021D92A4: .word 0x00000151
_021D92A8: .word 0x00000554
	thumb_func_end MOD17_021D926C

	thumb_func_start MOD17_021D92AC
MOD17_021D92AC: ; 0x021D92AC
	ldr r1, _021D92B4 ; =0x00000554
	ldr r3, _021D92B8 ; =MOD17_021DCA80
	add r0, r0, r1
	bx r3
	.align 2, 0
_021D92B4: .word 0x00000554
_021D92B8: .word MOD17_021DCA80
	thumb_func_end MOD17_021D92AC

	thumb_func_start MOD17_021D92BC
MOD17_021D92BC: ; 0x021D92BC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r0, _021D92E0 ; =MOD17_021D92E4
	mov r1, #0x10
	mov r2, #0xa
	mov r3, #0xd
	bl FUN_020061E8
	bl FUN_0201B6C8
	str r5, [r0]
	str r4, [r0, #4]
	mov r1, #0
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	pop {r3, r4, r5, pc}
	nop
_021D92E0: .word MOD17_021D92E4
	thumb_func_end MOD17_021D92BC

	thumb_func_start MOD17_021D92E4
MOD17_021D92E4: ; 0x021D92E4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	cmp r1, #9
	bls _021D92F2
	b _021D9424
_021D92F2:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D92FE: ; jump table
	.short _021D9312 - _021D92FE - 2 ; case 0
	.short _021D9334 - _021D92FE - 2 ; case 1
	.short _021D934E - _021D92FE - 2 ; case 2
	.short _021D936A - _021D92FE - 2 ; case 3
	.short _021D937E - _021D92FE - 2 ; case 4
	.short _021D93A4 - _021D92FE - 2 ; case 5
	.short _021D93C4 - _021D92FE - 2 ; case 6
	.short _021D93EA - _021D92FE - 2 ; case 7
	.short _021D9406 - _021D92FE - 2 ; case 8
	.short _021D941A - _021D92FE - 2 ; case 9
_021D9312:
	mov r0, #0xd7
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	mov r1, #3
	mov r2, #0
	bl MOD17_021DA870
	cmp r0, #0
	bne _021D932A
	bl GF_AssertFail
_021D932A:
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D9334:
	mov r0, #0xd7
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	bl MOD17_021DAAB8
	cmp r0, #0
	beq _021D9424
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D934E:
	mov r0, #1
	str r0, [sp]
	mov r0, #8
	add r1, r0, #0
	sub r1, #0x18
	mov r2, #0
	mov r3, #0xa
	bl FUN_0200A208
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D936A:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #0
	beq _021D9424
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D937E:
	ldr r1, [r4]
	ldr r0, _021D9428 ; =0x000004D4
	mov r2, #8
	add r0, r1, r0
	mov r1, #0
	bl MOD17_021DC508
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #8
	blt _021D9424
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D93A4:
	mov r1, #7
	add r0, r4, #0
	mvn r1, r1
	mov r2, #5
	mov r3, #8
	bl MOD17_021D970C
	cmp r0, #0
	beq _021D9424
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D93C4:
	ldr r0, [r4]
	mov r1, #1
	bl MOD17_021D8FD0
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x38]
	mov r2, #3
	mov r3, #0
	bl ScheduleSetBgPosText
	ldr r0, [r4]
	bl MOD17_021D9848
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D93EA:
	mov r1, #0
	mov r0, #1
	add r2, r1, #0
	str r0, [sp]
	mov r0, #8
	sub r2, #0x10
	mov r3, #0xa
	bl FUN_0200A208
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D9406:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #0
	beq _021D9424
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D941A:
	ldr r1, [r4, #4]
	mov r2, #1
	str r2, [r1]
	bl FUN_0200621C
_021D9424:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D9428: .word 0x000004D4
	thumb_func_end MOD17_021D92E4

	thumb_func_start MOD17_021D942C
MOD17_021D942C: ; 0x021D942C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r0, _021D9450 ; =MOD17_021D9454
	mov r1, #0x10
	mov r2, #0xa
	mov r3, #0xd
	bl FUN_020061E8
	bl FUN_0201B6C8
	str r5, [r0]
	str r4, [r0, #4]
	mov r1, #0
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	pop {r3, r4, r5, pc}
	nop
_021D9450: .word MOD17_021D9454
	thumb_func_end MOD17_021D942C

	thumb_func_start MOD17_021D9454
MOD17_021D9454: ; 0x021D9454
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	cmp r1, #9
	bls _021D9462
	b _021D95A4
_021D9462:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D946E: ; jump table
	.short _021D9482 - _021D946E - 2 ; case 0
	.short _021D949E - _021D946E - 2 ; case 1
	.short _021D94B2 - _021D946E - 2 ; case 2
	.short _021D94E6 - _021D946E - 2 ; case 3
	.short _021D9506 - _021D946E - 2 ; case 4
	.short _021D952E - _021D946E - 2 ; case 5
	.short _021D954A - _021D946E - 2 ; case 6
	.short _021D955E - _021D946E - 2 ; case 7
	.short _021D9580 - _021D946E - 2 ; case 8
	.short _021D959A - _021D946E - 2 ; case 9
_021D9482:
	mov r0, #1
	str r0, [sp]
	mov r0, #8
	add r1, r0, #0
	sub r1, #0x18
	mov r2, #0
	mov r3, #0xa
	bl FUN_0200A208
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D949E:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #0
	beq _021D95A4
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D94B2:
	ldr r0, [r4]
	bl MOD17_021D98D0
	ldr r0, [r4]
	bl MOD17_021D8F64
	ldr r0, [r4]
	bl MOD17_021D9150
	ldr r0, [r4]
	mov r1, #0
	bl MOD17_021D8FD0
	ldr r0, [r4]
	mov r2, #3
	add r3, r2, #0
	ldr r0, [r0, #0x38]
	mov r1, #1
	sub r3, #0x2b
	bl ScheduleSetBgPosText
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D94E6:
	mov r1, #8
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0xd
	add r3, r1, #0
	bl MOD17_021D970C
	cmp r0, #0
	beq _021D95A4
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D9506:
	ldr r1, [r4]
	ldr r0, _021D95A8 ; =0x000004D4
	add r0, r1, r0
	mov r1, #0
	add r2, r1, #0
	sub r2, #8
	bl MOD17_021DC508
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #8
	blt _021D95A4
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D952E:
	mov r1, #0
	mov r0, #1
	add r2, r1, #0
	str r0, [sp]
	mov r0, #8
	sub r2, #0x10
	mov r3, #0xa
	bl FUN_0200A208
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D954A:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #0
	beq _021D95A4
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D955E:
	mov r0, #0xd7
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	mov r1, #0
	add r2, r1, #0
	bl MOD17_021DA870
	cmp r0, #0
	bne _021D9576
	bl GF_AssertFail
_021D9576:
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D9580:
	mov r0, #0xd7
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	bl MOD17_021DAAB8
	cmp r0, #0
	beq _021D95A4
	ldr r0, [r4, #0xc]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_021D959A:
	ldr r1, [r4, #4]
	mov r2, #1
	str r2, [r1]
	bl FUN_0200621C
_021D95A4:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D95A8: .word 0x000004D4
	thumb_func_end MOD17_021D9454

	thumb_func_start MOD17_021D95AC
MOD17_021D95AC: ; 0x021D95AC
	push {r3, r4, r5, r6, r7, lr}
	str r1, [sp]
	add r6, r0, #0
	add r4, r2, #0
	bl FUN_02027310
	ldr r1, [sp]
	ldr r2, [sp]
	add r1, #0x84
	ldr r1, [r1]
	add r0, r6, #0
	add r2, #0x78
	bl FUN_02027348
	cmp r4, #0
	beq _021D95EC
	add r0, r4, #0
	mov r1, #0xd
	bl PlayerProfile_GetPlayerName_NewString
	add r5, r0, #0
	add r0, r4, #0
	bl PlayerProfile_GetTrainerGender
	add r2, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	bl FUN_020274F0
	add r0, r5, #0
	bl String_dtor
_021D95EC:
	ldr r0, [sp]
	mov r5, #0
	add r7, r0, #0
	ldr r4, [r0, #0x1c]
	add r7, #0x14
	cmp r4, r7
	beq _021D9612
_021D95FA:
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021D960C
	ldr r1, [r4]
	add r0, r6, #0
	add r2, r5, #0
	bl FUN_02027380
	add r5, r5, #1
_021D960C:
	ldr r4, [r4, #8]
	cmp r4, r7
	bne _021D95FA
_021D9612:
	ldr r0, [sp]
	ldr r4, [r0, #0xc]
	add r7, r0, #4
	cmp r4, r7
	beq _021D9634
_021D961C:
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021D962E
	ldr r1, [r4]
	add r0, r6, #0
	add r2, r5, #0
	bl FUN_02027380
	add r5, r5, #1
_021D962E:
	ldr r4, [r4, #8]
	cmp r4, r7
	bne _021D961C
_021D9634:
	ldr r1, [sp]
	add r0, r6, #0
	ldr r1, [r1, #0x74]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02027448
	add r0, r6, #0
	bl FUN_020272D4
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021D95AC

	thumb_func_start MOD17_021D964C
MOD17_021D964C: ; 0x021D964C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0xd
	mov r1, #0xac
	str r2, [sp, #4]
	add r4, r3, #0
	bl AllocFromHeap
	add r6, r0, #0
	bl MOD17_021D9CD4
	ldr r1, [sp]
	ldr r2, [sp]
	add r1, #0x84
	ldr r1, [r1]
	add r0, r7, #0
	add r2, #0x78
	bl FUN_02027778
	cmp r4, #0
	beq _021D969A
	add r0, r4, #0
	mov r1, #0xd
	bl PlayerProfile_GetPlayerName_NewString
	add r5, r0, #0
	add r0, r4, #0
	bl PlayerProfile_GetTrainerGender
	add r2, r0, #0
	add r0, r7, #0
	add r1, r5, #0
	bl FUN_02027A58
	add r0, r5, #0
	bl String_dtor
_021D969A:
	ldr r1, [sp]
	add r0, r6, #0
	add r1, #0x14
	mov r2, #1
	bl MOD17_021D9E00
	ldr r1, [sp]
	add r0, r6, #0
	add r1, r1, #4
	mov r2, #0
	bl MOD17_021D9E00
	add r0, r6, #0
	bl MOD17_021D9D14
	mov r4, #0
	add r5, r4, #0
_021D96BC:
	add r0, r6, #0
	add r1, r5, #0
	bl MOD17_021D9D84
	cmp r0, #1
	bne _021D96DE
	add r0, r6, #0
	add r1, r5, #0
	bl MOD17_021D9D70
	add r1, r0, #0
	ldr r1, [r1]
	add r0, r7, #0
	add r2, r4, #0
	bl FUN_020277B4
	add r4, r4, #1
_021D96DE:
	add r5, r5, #1
	cmp r5, #0x15
	blt _021D96BC
	ldr r1, [sp]
	add r0, r7, #0
	ldr r1, [r1, #0x74]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_0202787C
	ldr r1, [sp, #4]
	add r0, r7, #0
	bl FUN_020278AC
	add r0, r7, #0
	bl FUN_02027710
	add r0, r6, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021D964C

	thumb_func_start MOD17_021D970C
MOD17_021D970C: ; 0x021D970C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r0, #8
	bge _021D9728
	mov r0, #0xfa
	ldr r3, [r5]
	lsl r0, r0, #2
	add r0, r3, r0
	bl MOD17_021DA118
_021D9728:
	ldr r0, [r5, #8]
	cmp r0, #1
	blt _021D9766
	ldr r0, [r5]
	mov r1, #2
	ldr r0, [r0, #0x38]
	add r2, r1, #0
	add r3, r4, #0
	bl ScheduleSetBgPosText
	ldr r0, [r5]
	mov r1, #1
	ldr r0, [r0, #0x38]
	mov r2, #2
	add r3, r4, #0
	bl ScheduleSetBgPosText
	ldr r0, [r5]
	mov r1, #2
	ldr r0, [r0, #0x38]
	mov r2, #5
	add r3, r6, #0
	bl ScheduleSetBgPosText
	ldr r0, [r5]
	mov r1, #1
	ldr r0, [r0, #0x38]
	mov r2, #5
	add r3, r6, #0
	bl ScheduleSetBgPosText
_021D9766:
	ldr r0, [r5, #8]
	add r0, r0, #1
	str r0, [r5, #8]
	cmp r0, r7
	ble _021D9774
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9774:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021D970C

	thumb_func_start MOD17_021D9778
MOD17_021D9778: ; 0x021D9778
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	mov r2, #0
	ldr r0, [r4, #0x38]
	mov r1, #3
	add r3, r2, #0
	bl BgSetPosTextAndCommit
	mov r1, #3
	ldr r0, [r4, #0x38]
	add r2, r1, #0
	mov r3, #0
	bl BgSetPosTextAndCommit
	add r0, r4, #0
	mov r1, #0
	bl MOD17_021D9B74
	ldr r1, _021D97FC ; =0x04000008
	mov r3, #3
	ldrh r2, [r1]
	mov r0, #2
	bic r2, r3
	orr r0, r2
	strh r0, [r1]
	ldrh r2, [r1, #2]
	mov r0, #1
	bic r2, r3
	orr r2, r0
	strh r2, [r1, #2]
	ldrh r4, [r1, #4]
	mov r2, #3
	bic r4, r3
	orr r2, r4
	strh r2, [r1, #4]
	ldrh r2, [r1, #6]
	bic r2, r3
	strh r2, [r1, #6]
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0
	bl FUN_0200E394
	pop {r4, pc}
	nop
_021D97FC: .word 0x04000008
	thumb_func_end MOD17_021D9778

	thumb_func_start MOD17_021D9800
MOD17_021D9800: ; 0x021D9800
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021D9BCC
	ldr r0, [r4, #0x38]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	add r0, r4, #0
	bl MOD17_021D8F64
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	ldr r0, [r4, #0x3c]
	mov r1, #1
	bl FUN_0201FD98
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	pop {r4, pc}
	thumb_func_end MOD17_021D9800

	thumb_func_start MOD17_021D9848
MOD17_021D9848: ; 0x021D9848
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	mov r2, #0
	ldr r0, [r4, #0x38]
	mov r1, #3
	add r3, r2, #0
	bl BgSetPosTextAndCommit
	mov r1, #3
	ldr r0, [r4, #0x38]
	add r2, r1, #0
	mov r3, #0
	bl BgSetPosTextAndCommit
	ldr r0, [r4, #0x38]
	mov r1, #0x19
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #5
	str r0, [sp, #0xc]
	add r0, sp, #0
	strb r1, [r0, #0x10]
	mov r1, #4
	strb r1, [r0, #0x11]
	ldr r0, _021D98C8 ; =0x000006A4
	add r1, sp, #0
	ldr r0, [r4, r0]
	bl FUN_020145C8
	add r0, r4, #0
	mov r1, #1
	bl MOD17_021D9B4C
	ldr r0, _021D98CC ; =0x04000008
	mov r2, #3
	ldrh r3, [r0]
	mov r1, #2
	bic r3, r2
	orr r1, r3
	strh r1, [r0]
	ldrh r3, [r0, #2]
	mov r1, #1
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #2]
	ldrh r3, [r0, #4]
	mov r1, #3
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #4]
	ldrh r1, [r0, #6]
	bic r1, r2
	strh r1, [r0, #6]
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_021D98C8: .word 0x000006A4
_021D98CC: .word 0x04000008
	thumb_func_end MOD17_021D9848

	thumb_func_start MOD17_021D98D0
MOD17_021D98D0: ; 0x021D98D0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D98EC ; =0x000006A4
	ldr r0, [r4, r0]
	bl FUN_020146C4
	add r0, r4, #0
	bl MOD17_021D9B6C
	ldr r0, [r4, #0x38]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	pop {r4, pc}
	.align 2, 0
_021D98EC: .word 0x000006A4
	thumb_func_end MOD17_021D98D0

	thumb_func_start MOD17_021D98F0
MOD17_021D98F0: ; 0x021D98F0
	push {r3, lr}
	ldr r1, _021D9914 ; =0x000006A4
	ldr r0, [r0, r1]
	bl FUN_0201466C
	cmp r0, #0
	beq _021D9908
	cmp r0, #1
	beq _021D990C
	cmp r0, #2
	beq _021D9910
	pop {r3, pc}
_021D9908:
	mov r0, #4
	pop {r3, pc}
_021D990C:
	mov r0, #8
	pop {r3, pc}
_021D9910:
	mov r0, #9
	pop {r3, pc}
	.align 2, 0
_021D9914: .word 0x000006A4
	thumb_func_end MOD17_021D98F0

	thumb_func_start MOD17_021D9918
MOD17_021D9918: ; 0x021D9918
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, _021D99D0 ; =0x000006C8
	str r1, [sp, #0x14]
	ldr r0, [r5, r0]
	add r7, r2, #0
	add r4, r3, #0
	bl Options_GetFrame
	add r6, r0, #0
	mov r0, #0
	mov r1, #0xe0
	mov r2, #0xe
	bl FUN_02002EEC
	str r4, [sp]
	add r0, sp, #0x20
	ldrb r1, [r0, #0x10]
	mov r2, #3
	add r3, r7, #0
	str r1, [sp, #4]
	ldrb r0, [r0, #0x14]
	ldr r1, _021D99D4 ; =0x000006A8
	str r0, [sp, #8]
	mov r0, #7
	str r0, [sp, #0xc]
	mov r0, #0x92
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x38]
	ldr r1, [r5, r1]
	bl AddWindowParameterized
	ldr r0, _021D99D4 ; =0x000006A8
	mov r1, #0xf
	ldr r0, [r5, r0]
	bl FillWindowPixelBuffer
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xe
	str r0, [sp, #4]
	ldr r0, [r5, #0x38]
	mov r1, #3
	mov r2, #0x74
	mov r3, #8
	bl FUN_0200CD68
	ldr r0, _021D99D4 ; =0x000006A8
	mov r1, #0
	ldr r0, [r5, r0]
	mov r2, #0x74
	mov r3, #8
	bl FUN_0200D0BC
	ldr r2, _021D99D8 ; =0x00000151
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0xd
	bl NewMsgDataFromNarc
	ldr r1, [sp, #0x14]
	add r6, r0, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	mov r3, #0
	str r3, [sp]
	ldr r0, _021D99DC ; =0x0001020F
	str r3, [sp, #4]
	str r0, [sp, #8]
	ldr r0, _021D99D4 ; =0x000006A8
	str r3, [sp, #0xc]
	ldr r0, [r5, r0]
	mov r1, #1
	add r2, r4, #0
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl DestroyMsgData
	ldr r0, _021D99D4 ; =0x000006A8
	ldr r0, [r5, r0]
	bl CopyWindowToVram
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D99D0: .word 0x000006C8
_021D99D4: .word 0x000006A8
_021D99D8: .word 0x00000151
_021D99DC: .word 0x0001020F
	thumb_func_end MOD17_021D9918

	thumb_func_start MOD17_021D99E0
MOD17_021D99E0: ; 0x021D99E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, _021D9A58 ; =0x000006A8
	add r4, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0xf
	bl FillWindowPixelBuffer
	ldr r2, _021D9A5C ; =0x00000151
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0xd
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r7, r0, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #1
	lsl r0, r0, #8
	mov r1, #0xd
	bl String_ctor
	add r4, r0, #0
	ldr r0, _021D9A60 ; =0x000006D4
	add r1, r4, #0
	ldr r0, [r5, r0]
	add r2, r6, #0
	bl StringExpandPlaceholders
	mov r3, #0
	str r3, [sp]
	ldr r0, _021D9A64 ; =0x0001020F
	str r3, [sp, #4]
	str r0, [sp, #8]
	ldr r0, _021D9A58 ; =0x000006A8
	str r3, [sp, #0xc]
	ldr r0, [r5, r0]
	mov r1, #1
	add r2, r4, #0
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add r0, r7, #0
	bl DestroyMsgData
	ldr r0, _021D9A58 ; =0x000006A8
	ldr r0, [r5, r0]
	bl CopyWindowToVram
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9A58: .word 0x000006A8
_021D9A5C: .word 0x00000151
_021D9A60: .word 0x000006D4
_021D9A64: .word 0x0001020F
	thumb_func_end MOD17_021D99E0

	thumb_func_start MOD17_021D9A68
MOD17_021D9A68: ; 0x021D9A68
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0x6d
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r4, r1, #0
	cmp r0, #0
	beq _021D9A7E
	bl GF_AssertFail
_021D9A7E:
	ldr r0, _021D9B08 ; =0x000006A8
	mov r1, #0xf
	ldr r0, [r5, r0]
	bl FillWindowPixelBuffer
	ldr r2, _021D9B0C ; =0x00000151
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0xd
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r7, r0, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	mov r0, #1
	lsl r0, r0, #8
	mov r1, #0xd
	bl String_ctor
	mov r1, #0x6d
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #4
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	ldr r0, _021D9B10 ; =0x000006C4
	ldr r1, [r5, r0]
	ldrb r1, [r1, #0x16]
	cmp r1, #0
	bne _021D9ACE
	add r0, r0, #4
	ldr r0, [r5, r0]
	bl Options_GetTextFrameDelay
	b _021D9AD0
_021D9ACE:
	mov r0, #1
_021D9AD0:
	mov r3, #0
	str r3, [sp]
	str r0, [sp, #4]
	ldr r0, _021D9B14 ; =0x0001020F
	ldr r2, _021D9B08 ; =0x000006A8
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r0, [r5, r2]
	add r2, #0x28
	ldr r2, [r5, r2]
	mov r1, #1
	bl AddTextPrinterParameterized2
	add r6, r0, #0
	add r0, r4, #0
	bl String_dtor
	add r0, r7, #0
	bl DestroyMsgData
	ldr r0, _021D9B08 ; =0x000006A8
	ldr r0, [r5, r0]
	bl CopyWindowToVram
	add r0, r6, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9B08: .word 0x000006A8
_021D9B0C: .word 0x00000151
_021D9B10: .word 0x000006C4
_021D9B14: .word 0x0001020F
	thumb_func_end MOD17_021D9A68

	thumb_func_start MOD17_021D9B18
MOD17_021D9B18: ; 0x021D9B18
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x6d
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0x6d
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	pop {r4, pc}
	thumb_func_end MOD17_021D9B18

	thumb_func_start MOD17_021D9B30
MOD17_021D9B30: ; 0x021D9B30
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D9B48 ; =0x000006A8
	ldr r0, [r4, r0]
	bl ClearWindowTilemapAndCopyToVram
	ldr r0, _021D9B48 ; =0x000006A8
	ldr r0, [r4, r0]
	bl RemoveWindow
	pop {r4, pc}
	nop
_021D9B48: .word 0x000006A8
	thumb_func_end MOD17_021D9B30

	thumb_func_start MOD17_021D9B4C
MOD17_021D9B4C: ; 0x021D9B4C
	push {r3, lr}
	sub sp, #8
	mov r2, #0x1b
	str r2, [sp]
	mov r2, #2
	mov r3, #1
	str r2, [sp, #4]
	bl MOD17_021D9918
	add sp, #8
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD17_021D9B4C

	thumb_func_start MOD17_021D9B64
MOD17_021D9B64: ; 0x021D9B64
	ldr r3, _021D9B68 ; =MOD17_021D99E0
	bx r3
	.align 2, 0
_021D9B68: .word MOD17_021D99E0
	thumb_func_end MOD17_021D9B64

	thumb_func_start MOD17_021D9B6C
MOD17_021D9B6C: ; 0x021D9B6C
	ldr r3, _021D9B70 ; =MOD17_021D9B30
	bx r3
	.align 2, 0
_021D9B70: .word MOD17_021D9B30
	thumb_func_end MOD17_021D9B6C

	thumb_func_start MOD17_021D9B74
MOD17_021D9B74: ; 0x021D9B74
	push {r4, lr}
	sub sp, #8
	mov r2, #0x1b
	str r2, [sp]
	mov r2, #4
	str r2, [sp, #4]
	mov r2, #2
	mov r3, #0x13
	add r4, r0, #0
	bl MOD17_021D9918
	mov r0, #0xd
	bl ScrStrBufs_new
	ldr r1, _021D9B98 ; =0x000006D4
	str r0, [r4, r1]
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_021D9B98: .word 0x000006D4
	thumb_func_end MOD17_021D9B74

	thumb_func_start MOD17_021D9B9C
MOD17_021D9B9C: ; 0x021D9B9C
	ldr r3, _021D9BA0 ; =MOD17_021D9A68
	bx r3
	.align 2, 0
_021D9BA0: .word MOD17_021D9A68
	thumb_func_end MOD17_021D9B9C

	thumb_func_start MOD17_021D9BA4
MOD17_021D9BA4: ; 0x021D9BA4
	push {r3, lr}
	sub sp, #8
	mov r3, #0
	str r3, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldr r3, _021D9BC0 ; =0x000006D4
	ldr r0, [r0, r3]
	mov r3, #2
	bl BufferIntegerAsString
	add sp, #8
	pop {r3, pc}
	nop
_021D9BC0: .word 0x000006D4
	thumb_func_end MOD17_021D9BA4

	thumb_func_start MOD17_021D9BC4
MOD17_021D9BC4: ; 0x021D9BC4
	ldr r3, _021D9BC8 ; =MOD17_021D9B18
	bx r3
	.align 2, 0
_021D9BC8: .word MOD17_021D9B18
	thumb_func_end MOD17_021D9BC4

	thumb_func_start MOD17_021D9BCC
MOD17_021D9BCC: ; 0x021D9BCC
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021D9B30
	ldr r0, _021D9BE4 ; =0x000006D4
	ldr r0, [r4, r0]
	bl ScrStrBufs_delete
	ldr r0, _021D9BE4 ; =0x000006D4
	mov r1, #0
	str r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_021D9BE4: .word 0x000006D4
	thumb_func_end MOD17_021D9BCC

	thumb_func_start MOD17_021D9BE8
MOD17_021D9BE8: ; 0x021D9BE8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xfa
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021DA368
	add r1, r0, #0
	ldr r0, _021D9C04 ; =0x00000554
	add r0, r4, r0
	bl MOD17_021DCBD8
	pop {r4, pc}
	nop
_021D9C04: .word 0x00000554
	thumb_func_end MOD17_021D9BE8

	thumb_func_start MOD17_021D9C08
MOD17_021D9C08: ; 0x021D9C08
	push {r4, lr}
	cmp r0, #3
	bhi _021D9C32
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9C1A: ; jump table
	.short _021D9C22 - _021D9C1A - 2 ; case 0
	.short _021D9C26 - _021D9C1A - 2 ; case 1
	.short _021D9C2A - _021D9C1A - 2 ; case 2
	.short _021D9C2E - _021D9C1A - 2 ; case 3
_021D9C22:
	mov r4, #5
	b _021D9C36
_021D9C26:
	mov r4, #0xa
	b _021D9C36
_021D9C2A:
	mov r4, #0xf
	b _021D9C36
_021D9C2E:
	mov r4, #0x14
	b _021D9C36
_021D9C32:
	bl GF_AssertFail
_021D9C36:
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D9C08

	thumb_func_start MOD17_021D9C3C
MOD17_021D9C3C: ; 0x021D9C3C
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	mov r1, #0x19
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #5
	str r0, [sp, #0xc]
	add r0, sp, #0
	strb r1, [r0, #0x10]
	mov r1, #4
	strb r1, [r0, #0x11]
	ldr r0, _021D9CA4 ; =0x000006A4
	ldr r0, [r4, r0]
	bl FUN_020146C4
	ldr r0, _021D9CA4 ; =0x000006A4
	add r1, sp, #0
	ldr r0, [r4, r0]
	bl FUN_020145C8
	add r0, r4, #0
	mov r1, #2
	bl MOD17_021D9B64
	ldr r0, _021D9CA8 ; =0x04000008
	mov r2, #3
	ldrh r3, [r0]
	mov r1, #2
	bic r3, r2
	orr r1, r3
	strh r1, [r0]
	ldrh r3, [r0, #2]
	mov r1, #1
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #2]
	ldrh r3, [r0, #4]
	mov r1, #3
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #4]
	ldrh r1, [r0, #6]
	bic r1, r2
	strh r1, [r0, #6]
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_021D9CA4: .word 0x000006A4
_021D9CA8: .word 0x04000008
	thumb_func_end MOD17_021D9C3C

	thumb_func_start MOD17_021D9CAC
MOD17_021D9CAC: ; 0x021D9CAC
	push {r3, lr}
	ldr r1, _021D9CD0 ; =0x000006A4
	ldr r0, [r0, r1]
	bl FUN_0201466C
	cmp r0, #0
	beq _021D9CC4
	cmp r0, #1
	beq _021D9CC8
	cmp r0, #2
	beq _021D9CCC
	pop {r3, pc}
_021D9CC4:
	mov r0, #5
	pop {r3, pc}
_021D9CC8:
	mov r0, #6
	pop {r3, pc}
_021D9CCC:
	mov r0, #7
	pop {r3, pc}
	.align 2, 0
_021D9CD0: .word 0x000006A4
	thumb_func_end MOD17_021D9CAC

	thumb_func_start MOD17_021D9CD4
MOD17_021D9CD4: ; 0x021D9CD4
	ldr r3, _021D9CDC ; =memset
	mov r1, #0
	mov r2, #0xac
	bx r3
	.align 2, 0
_021D9CDC: .word memset
	thumb_func_end MOD17_021D9CD4

	thumb_func_start MOD17_021D9CE0
MOD17_021D9CE0: ; 0x021D9CE0
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #0
	bne _021D9CF0
	bl GF_AssertFail
_021D9CF0:
	add r0, r5, #0
	add r0, #0xa8
	ldr r0, [r0]
	lsl r0, r0, #3
	str r4, [r5, r0]
	add r0, r5, #0
	add r0, #0xa8
	ldr r0, [r0]
	lsl r0, r0, #3
	add r0, r5, r0
	str r6, [r0, #4]
	add r0, r5, #0
	add r0, #0xa8
	ldr r0, [r0]
	add r5, #0xa8
	add r0, r0, #1
	str r0, [r5]
	pop {r4, r5, r6, pc}
	thumb_func_end MOD17_021D9CE0

	thumb_func_start MOD17_021D9D14
MOD17_021D9D14: ; 0x021D9D14
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r0, #0xa8
	ldr r2, [r0]
	mov r1, #0
	cmp r2, #0
	ble _021D9D6C
_021D9D22:
	lsl r0, r1, #3
	add r7, r6, r0
	ldr r0, [r7, #4]
	cmp r0, #1
	bne _021D9D60
	mov r4, #0
	cmp r2, #0
	ble _021D9D58
	add r5, r6, #0
_021D9D34:
	ldr r0, [r5, #4]
	cmp r0, #0
	bne _021D9D4A
	add r0, r7, #0
	add r1, r5, #0
	bl MOD17_021D9DA4
	cmp r0, #1
	bne _021D9D4A
	mov r0, #1
	str r0, [r5, #4]
_021D9D4A:
	add r0, r6, #0
	add r0, #0xa8
	ldr r0, [r0]
	add r4, r4, #1
	add r5, #8
	cmp r4, r0
	blt _021D9D34
_021D9D58:
	mov r0, #2
	str r0, [r7, #4]
	mov r1, #0
	b _021D9D62
_021D9D60:
	add r1, r1, #1
_021D9D62:
	add r0, r6, #0
	add r0, #0xa8
	ldr r2, [r0]
	cmp r1, r2
	blt _021D9D22
_021D9D6C:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021D9D14

	thumb_func_start MOD17_021D9D70
MOD17_021D9D70: ; 0x021D9D70
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #0x15
	blo _021D9D7E
	bl GF_AssertFail
_021D9D7E:
	lsl r0, r5, #3
	ldr r0, [r4, r0]
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021D9D70

	thumb_func_start MOD17_021D9D84
MOD17_021D9D84: ; 0x021D9D84
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #0x15
	blo _021D9D92
	bl GF_AssertFail
_021D9D92:
	lsl r0, r5, #3
	add r0, r4, r0
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021D9DA0
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D9DA0:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021D9D84

	thumb_func_start MOD17_021D9DA4
MOD17_021D9DA4: ; 0x021D9DA4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r4, r0, #0
	ldr r0, [r4]
	add r5, r1, #0
	add r1, sp, #0x28
	add r2, sp, #0x24
	bl MOD17_021DBCC8
	add r0, sp, #0x20
	str r0, [sp]
	ldr r0, [r4]
	add r1, sp, #0x14
	add r2, sp, #0x18
	add r3, sp, #0x1c
	bl MOD17_021DBC70
	mov r4, #0
	add r6, sp, #0x10
	add r7, sp, #0xc
_021D9DCC:
	str r4, [sp]
	str r6, [sp, #4]
	str r7, [sp, #8]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	bl MOD17_021D9E78
	ldr r0, [r5]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	bl MOD17_021DBAE8
	cmp r0, #1
	bne _021D9DF2
	add sp, #0x2c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D9DF2:
	add r4, r4, #1
	cmp r4, #0x10
	blt _021D9DCC
	mov r0, #0
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021D9DA4

	thumb_func_start MOD17_021D9E00
MOD17_021D9E00: ; 0x021D9E00
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r4, [r5, #8]
	add r6, r0, #0
	add r7, r2, #0
	cmp r4, r5
	beq _021D9E24
_021D9E0E:
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021D9E1E
	add r0, r6, #0
	add r1, r4, #0
	add r2, r7, #0
	bl MOD17_021D9CE0
_021D9E1E:
	ldr r4, [r4, #8]
	cmp r4, r5
	bne _021D9E0E
_021D9E24:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021D9E00

	thumb_func_start MOD17_021D9E28
MOD17_021D9E28: ; 0x021D9E28
	push {r3, r4, r5, lr}
	ldr r2, _021D9E70 ; =0x000006C4
	mov r1, #0
	ldr r2, [r0, r2]
	ldrb r3, [r2, #0x16]
	cmp r3, #0
	bne _021D9E40
	ldr r2, _021D9E74 ; =0x00000554
	add r0, r0, r2
	bl MOD17_021DCBEC
	pop {r3, r4, r5, pc}
_021D9E40:
	ldrb r4, [r2, #0x14]
	ldrb r3, [r2, #0x15]
	cmp r4, r3
	bne _021D9E6C
	add r4, r1, #0
	add r5, r2, #0
_021D9E4C:
	ldrb r3, [r5, #0x10]
	cmp r3, #1
	bne _021D9E54
	add r1, r1, #1
_021D9E54:
	add r4, r4, #1
	add r5, r5, #1
	cmp r4, #4
	blt _021D9E4C
	ldrb r2, [r2, #0x17]
	cmp r2, r1
	bgt _021D9E6C
	ldr r1, _021D9E74 ; =0x00000554
	add r0, r0, r1
	mov r1, #0
	bl MOD17_021DCBEC
_021D9E6C:
	pop {r3, r4, r5, pc}
	nop
_021D9E70: .word 0x000006C4
_021D9E74: .word 0x00000554
	thumb_func_end MOD17_021D9E28

	thumb_func_start MOD17_021D9E78
MOD17_021D9E78: ; 0x021D9E78
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r0, #0
	str r1, [sp]
	add r7, r2, #0
	add r0, r3, #0
	sub r0, r0, r7
	mov r1, #3
	str r3, [sp, #4]
	ldr r4, [sp, #0x2c]
	ldr r5, [sp, #0x30]
	bl _u32_div_f
	add r1, r7, r0
	lsl r0, r0, #1
	add r0, r7, r0
	str r0, [sp, #8]
	ldr r0, [sp]
	str r1, [sp, #0xc]
	sub r0, r0, r6
	mov r1, #3
	bl _u32_div_f
	add r2, r6, r0
	lsl r0, r0, #1
	ldr r1, [sp, #0x28]
	add r0, r6, r0
	cmp r1, #0xf
	bhi _021D9F7A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D9EBE: ; jump table
	.short _021D9EDE - _021D9EBE - 2 ; case 0
	.short _021D9EE6 - _021D9EBE - 2 ; case 1
	.short _021D9EEE - _021D9EBE - 2 ; case 2
	.short _021D9EF6 - _021D9EBE - 2 ; case 3
	.short _021D9F00 - _021D9EBE - 2 ; case 4
	.short _021D9F0A - _021D9EBE - 2 ; case 5
	.short _021D9F14 - _021D9EBE - 2 ; case 6
	.short _021D9F1E - _021D9EBE - 2 ; case 7
	.short _021D9F2A - _021D9EBE - 2 ; case 8
	.short _021D9F34 - _021D9EBE - 2 ; case 9
	.short _021D9F3E - _021D9EBE - 2 ; case 10
	.short _021D9F48 - _021D9EBE - 2 ; case 11
	.short _021D9F54 - _021D9EBE - 2 ; case 12
	.short _021D9F5E - _021D9EBE - 2 ; case 13
	.short _021D9F68 - _021D9EBE - 2 ; case 14
	.short _021D9F72 - _021D9EBE - 2 ; case 15
_021D9EDE:
	str r7, [r4]
	add sp, #0x10
	str r6, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9EE6:
	str r7, [r4]
	add sp, #0x10
	str r2, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9EEE:
	str r7, [r4]
	add sp, #0x10
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9EF6:
	ldr r0, [sp]
	str r7, [r4]
	add sp, #0x10
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F00:
	ldr r0, [sp, #0xc]
	add sp, #0x10
	str r0, [r4]
	str r6, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F0A:
	ldr r0, [sp, #0xc]
	add sp, #0x10
	str r0, [r4]
	str r2, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F14:
	ldr r1, [sp, #0xc]
	add sp, #0x10
	str r1, [r4]
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F1E:
	ldr r0, [sp, #0xc]
	str r0, [r4]
	ldr r0, [sp]
	add sp, #0x10
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F2A:
	ldr r0, [sp, #8]
	add sp, #0x10
	str r0, [r4]
	str r6, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F34:
	ldr r0, [sp, #8]
	add sp, #0x10
	str r0, [r4]
	str r2, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F3E:
	ldr r1, [sp, #8]
	add sp, #0x10
	str r1, [r4]
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F48:
	ldr r0, [sp, #8]
	str r0, [r4]
	ldr r0, [sp]
	add sp, #0x10
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F54:
	ldr r0, [sp, #4]
	add sp, #0x10
	str r0, [r4]
	str r6, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F5E:
	ldr r0, [sp, #4]
	add sp, #0x10
	str r0, [r4]
	str r2, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F68:
	ldr r1, [sp, #4]
	add sp, #0x10
	str r1, [r4]
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021D9F72:
	ldr r0, [sp, #4]
	str r0, [r4]
	ldr r0, [sp]
	str r0, [r5]
_021D9F7A:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021D9E78

	thumb_func_start MOD17_021D9F80
MOD17_021D9F80: ; 0x021D9F80
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1]
	mov r2, #0
	str r0, [r4, #0x2c]
	ldr r0, [r1, #4]
	str r0, [r4, #0x30]
	ldr r0, [r1, #8]
	str r0, [r4, #0x34]
	ldr r0, [r1, #0xc]
	str r0, [r4, #0x38]
	ldr r0, [r1, #0x10]
	str r0, [r4, #0x3c]
	ldr r0, [r1, #0x14]
	str r0, [r4, #0x40]
	ldr r0, [r1, #0x18]
	str r0, [r4, #0x44]
	str r2, [r4, #0x74]
	ldr r0, [r1, #0x1c]
	str r0, [r4]
	add r0, r4, #4
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	add r0, r4, #0
	add r0, #0x14
	str r0, [r4, #0x1c]
	str r0, [r4, #0x20]
	str r2, [r4, #0x24]
	ldr r0, [r1, #0x20]
	add r1, r4, #0
	str r0, [r4, #0x28]
	ldr r0, [r4]
	add r1, #0x78
	mov r2, #3
	bl MOD17_021DBA30
	add r4, #0x14
	add r1, r4, #0
	bl MOD17_021DBA90
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D9F80

	thumb_func_start MOD17_021D9FD4
MOD17_021D9FD4: ; 0x021D9FD4
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021DA058
	add r0, r4, #0
	bl MOD17_021DA100
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x88
	bl memset
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021D9FD4

	thumb_func_start MOD17_021D9FF0
MOD17_021D9FF0: ; 0x021D9FF0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, [sp, #0x20]
	add r6, r1, #0
	str r0, [sp]
	add r5, r2, #0
	add r0, r4, #0
	add r7, r3, #0
	ldr r1, [r4, #0x3c]
	add r0, #0x78
	add r2, r6, #0
	add r3, r5, #0
	bl MOD17_021DB700
	add r0, r4, #0
	ldr r1, [sp, #0x1c]
	add r0, #0x78
	bl MOD17_021DB7D8
	add r4, #0x78
	ldr r2, [sp, #0x18]
	add r0, r4, #0
	add r1, r7, #0
	bl MOD17_021DB7F4
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021D9FF0

	thumb_func_start MOD17_021DA024
MOD17_021DA024: ; 0x021DA024
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r6, r0, #0
	str r3, [sp]
	add r5, r1, #0
	add r4, r2, #0
	ldr r1, [r6, #0x3c]
	add r0, #0x78
	add r2, r5, #0
	add r3, r4, #0
	bl MOD17_021DB700
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD17_021DA024

	thumb_func_start MOD17_021DA040
MOD17_021DA040: ; 0x021DA040
	ldr r3, _021DA04C ; =MOD17_021DBA90
	add r2, r0, #0
	add r0, r1, #0
	ldr r1, [r2, #0x20]
	bx r3
	nop
_021DA04C: .word MOD17_021DBA90
	thumb_func_end MOD17_021DA040

	thumb_func_start MOD17_021DA050
MOD17_021DA050: ; 0x021DA050
	ldr r3, _021DA054 ; =MOD17_021DBAA0
	bx r3
	.align 2, 0
_021DA054: .word MOD17_021DBAA0
	thumb_func_end MOD17_021DA050

	thumb_func_start MOD17_021DA058
MOD17_021DA058: ; 0x021DA058
	ldr r3, _021DA060 ; =MOD17_021DB7C0
	add r0, #0x78
	bx r3
	nop
_021DA060: .word MOD17_021DB7C0
	thumb_func_end MOD17_021DA058

	thumb_func_start MOD17_021DA064
MOD17_021DA064: ; 0x021DA064
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r4, r0, #0
	ldr r5, [r4, #0x24]
	ldr r0, [r4, #0x28]
	cmp r5, r0
	bge _021DA0BE
	ldr r0, [r4, #0x44]
	str r0, [sp]
	ldr r0, [r4, #0x2c]
	str r0, [sp, #4]
	ldr r5, [r4, #0x30]
	lsl r0, r1, #2
	ldr r0, [r5, r0]
	str r0, [sp, #8]
	ldr r0, [r4, #0x34]
	ldr r0, [r0]
	str r2, [sp, #0x10]
	str r3, [sp, #0x14]
	str r1, [sp, #0x18]
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x38]
	ldrb r0, [r0, r1]
	str r0, [sp, #0x1c]
	add r0, sp, #0
	bl MOD17_021D7520
	ldr r1, [sp, #0x30]
	add r5, r0, #0
	bl MOD17_021D766C
	ldr r0, [r4]
	add r1, r5, #0
	mov r2, #0
	bl MOD17_021DBA30
	add r1, r4, #4
	bl MOD17_021DBA90
	ldr r0, [r4, #0x24]
	add sp, #0x20
	add r0, r0, #1
	str r0, [r4, #0x24]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA0BE:
	mov r0, #0
	add sp, #0x20
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DA064

	thumb_func_start MOD17_021DA0C4
MOD17_021DA0C4: ; 0x021DA0C4
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r3, r2, #0
	ldr r5, [r4, #0x24]
	ldr r2, [r4, #0x28]
	cmp r5, r2
	bge _021DA0E2
	mov r2, #1
	bl MOD17_021DA454
	ldr r0, [r4, #0x24]
	add r0, r0, #1
	str r0, [r4, #0x24]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA0E2:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA0C4

	thumb_func_start MOD17_021DA0E8
MOD17_021DA0E8: ; 0x021DA0E8
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	bl MOD17_021DBAA0
	ldr r0, [r4, #0x24]
	sub r0, r0, #1
	str r0, [r4, #0x24]
	bpl _021DA0FE
	bl GF_AssertFail
_021DA0FE:
	pop {r4, pc}
	thumb_func_end MOD17_021DA0E8

	thumb_func_start MOD17_021DA100
MOD17_021DA100: ; 0x021DA100
	push {r4, lr}
	add r4, r0, #0
	add r0, r4, #4
	bl MOD17_021DBAB0
	add r0, r4, #0
	add r0, #0x14
	bl MOD17_021DBAB0
	mov r0, #0
	str r0, [r4, #0x24]
	pop {r4, pc}
	thumb_func_end MOD17_021DA100

	thumb_func_start MOD17_021DA118
MOD17_021DA118: ; 0x021DA118
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, r5, #4
	add r4, r1, #0
	add r6, r2, #0
	bl MOD17_021DBC38
	add r5, #0x14
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD17_021DBC38
	pop {r4, r5, r6, pc}
	thumb_func_end MOD17_021DA118

	thumb_func_start MOD17_021DA134
MOD17_021DA134: ; 0x021DA134
	ldr r3, _021DA13C ; =MOD17_021DBC38
	add r0, #0x14
	bx r3
	nop
_021DA13C: .word MOD17_021DBC38
	thumb_func_end MOD17_021DA134

	thumb_func_start MOD17_021DA140
MOD17_021DA140: ; 0x021DA140
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	neg r4, r2
	neg r7, r1
	add r0, r5, #4
	add r1, r7, #0
	add r2, r4, #0
	add r6, r3, #0
	bl MOD17_021DBC38
	ldr r2, [sp, #0x18]
	add r0, r5, #4
	add r1, r6, #0
	bl MOD17_021DBC38
	add r0, r5, #0
	add r0, #0x14
	add r1, r7, #0
	add r2, r4, #0
	bl MOD17_021DBC38
	add r5, #0x14
	ldr r2, [sp, #0x18]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD17_021DBC38
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DA140

	thumb_func_start MOD17_021DA178
MOD17_021DA178: ; 0x021DA178
	ldr r3, _021DA180 ; =MOD17_021DA184
	mov r1, #0
	mvn r1, r1
	bx r3
	.align 2, 0
_021DA180: .word MOD17_021DA184
	thumb_func_end MOD17_021DA178

	thumb_func_start MOD17_021DA184
MOD17_021DA184: ; 0x021DA184
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r7, #0
	ldr r4, [r7, #0x1c]
	add r6, #0x14
	add r5, r1, #0
	cmp r4, r6
	beq _021DA1B2
_021DA194:
	ldr r0, [r4, #4]
	cmp r0, #0
	ldr r0, [r4]
	bne _021DA1A4
	add r1, r5, #0
	bl MOD17_021D766C
	b _021DA1AA
_021DA1A4:
	add r1, r5, #0
	bl MOD17_021DB7D8
_021DA1AA:
	ldr r4, [r4, #8]
	sub r5, r5, #1
	cmp r4, r6
	bne _021DA194
_021DA1B2:
	ldr r4, [r7, #0xc]
	add r6, r7, #4
	sub r5, #8
	cmp r4, r6
	beq _021DA1DA
_021DA1BC:
	ldr r0, [r4, #4]
	cmp r0, #0
	ldr r0, [r4]
	bne _021DA1CC
	add r1, r5, #0
	bl MOD17_021D766C
	b _021DA1D2
_021DA1CC:
	add r1, r5, #0
	bl MOD17_021DB7D8
_021DA1D2:
	ldr r4, [r4, #8]
	sub r5, r5, #1
	cmp r4, r6
	bne _021DA1BC
_021DA1DA:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DA184

	thumb_func_start MOD17_021DA1DC
MOD17_021DA1DC: ; 0x021DA1DC
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r7, #0
	ldr r4, [r7, #0x1c]
	add r6, #0x14
	add r5, r1, #0
	cmp r4, r6
	beq _021DA218
_021DA1EC:
	ldr r0, [r4, #4]
	cmp r0, #0
	ldr r0, [r4]
	bne _021DA204
	bl MOD17_021D7678
	add r1, r0, #0
	ldr r0, [r4]
	add r1, r1, r5
	bl MOD17_021D766C
	b _021DA212
_021DA204:
	bl MOD17_021DB7E8
	add r1, r0, #0
	ldr r0, [r4]
	add r1, r1, r5
	bl MOD17_021DB7D8
_021DA212:
	ldr r4, [r4, #8]
	cmp r4, r6
	bne _021DA1EC
_021DA218:
	ldr r4, [r7, #0xc]
	add r6, r7, #4
	cmp r4, r6
	beq _021DA24C
_021DA220:
	ldr r0, [r4, #4]
	cmp r0, #0
	ldr r0, [r4]
	bne _021DA238
	bl MOD17_021D7678
	add r1, r0, #0
	ldr r0, [r4]
	add r1, r1, r5
	bl MOD17_021D766C
	b _021DA246
_021DA238:
	bl MOD17_021DB7E8
	add r1, r0, #0
	ldr r0, [r4]
	add r1, r1, r5
	bl MOD17_021DB7D8
_021DA246:
	ldr r4, [r4, #8]
	cmp r4, r6
	bne _021DA220
_021DA24C:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA1DC

	thumb_func_start MOD17_021DA250
MOD17_021DA250: ; 0x021DA250
	push {r3, lr}
	mov r1, #0x12
	add r0, sp, #0
	strb r1, [r0]
	mov r1, #0x8f
	strb r1, [r0, #1]
	mov r1, #0x8a
	strb r1, [r0, #2]
	mov r1, #0xf6
	strb r1, [r0, #3]
	add r0, sp, #0
	bl FUN_02020A40
	pop {r3, pc}
	thumb_func_end MOD17_021DA250

	thumb_func_start MOD17_021DA26C
MOD17_021DA26C: ; 0x021DA26C
	push {r3, lr}
	mov r3, #0x12
	add r0, sp, #0
	strb r3, [r0]
	mov r3, #0x8f
	strb r3, [r0, #1]
	mov r3, #0x8a
	strb r3, [r0, #2]
	mov r3, #0xf6
	strb r3, [r0, #3]
	add r0, sp, #0
	bl FUN_02020AE8
	pop {r3, pc}
	thumb_func_end MOD17_021DA26C

	thumb_func_start MOD17_021DA288
MOD17_021DA288: ; 0x021DA288
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	ldr r5, [r0, #0x1c]
	str r0, [sp]
	str r0, [sp, #4]
	add r0, #0x14
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	str r0, [sp, #4]
	cmp r5, r0
	beq _021DA2BE
_021DA2A0:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	add r3, r7, #0
	bl MOD17_021DBB1C
	cmp r0, #1
	bne _021DA2B6
	add sp, #0xc
	add r0, r5, #0
	pop {r4, r5, r6, r7, pc}
_021DA2B6:
	ldr r5, [r5, #8]
	ldr r0, [sp, #4]
	cmp r5, r0
	bne _021DA2A0
_021DA2BE:
	ldr r0, [sp]
	ldr r5, [r0, #0xc]
	add r0, r0, #4
	str r0, [sp, #8]
	cmp r5, r0
	beq _021DA2E8
_021DA2CA:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	add r3, r7, #0
	bl MOD17_021DBB1C
	cmp r0, #1
	bne _021DA2E0
	add sp, #0xc
	add r0, r5, #0
	pop {r4, r5, r6, r7, pc}
_021DA2E0:
	ldr r5, [r5, #8]
	ldr r0, [sp, #8]
	cmp r5, r0
	bne _021DA2CA
_021DA2E8:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA288

	thumb_func_start MOD17_021DA2F0
MOD17_021DA2F0: ; 0x021DA2F0
	push {r3, r4, r5, lr}
	sub sp, #0x30
	add r5, r0, #0
	ldr r0, [r5, #0x40]
	add r4, r1, #0
	str r0, [sp]
	mov r0, #0x19
	lsl r1, r4, #2
	str r0, [sp, #4]
	add r0, r1, #0
	add r0, #0x86
	str r0, [sp, #8]
	add r0, r1, #0
	add r0, #0x87
	str r0, [sp, #0xc]
	mov r0, #0x88
	str r0, [sp, #0x14]
	mov r0, #0x10
	str r0, [sp, #0x18]
	mov r0, #2
	str r0, [sp, #0x1c]
	mov r0, #1
	add r1, #0x88
	str r1, [sp, #0x10]
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
	mov r0, #0
	str r0, [sp, #0x28]
	add r0, r5, #0
	add r0, #0x48
	add r1, sp, #0
	str r2, [sp, #0x2c]
	bl MOD17_021DBD04
	str r4, [r5, #0x74]
	add sp, #0x30
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA2F0

	thumb_func_start MOD17_021DA33C
MOD17_021DA33C: ; 0x021DA33C
	ldr r3, _021DA344 ; =MOD17_021DBD4C
	add r0, #0x48
	bx r3
	nop
_021DA344: .word MOD17_021DBD4C
	thumb_func_end MOD17_021DA33C

	thumb_func_start MOD17_021DA348
MOD17_021DA348: ; 0x021DA348
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x78]
	add r4, r1, #0
	mov r1, #0
	add r6, r2, #0
	bl FUN_0200782C
	str r0, [r4]
	ldr r0, [r5, #0x78]
	mov r1, #1
	bl FUN_0200782C
	str r0, [r6]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA348

	thumb_func_start MOD17_021DA368
MOD17_021DA368: ; 0x021DA368
	ldr r0, [r0, #0x24]
	bx lr
	thumb_func_end MOD17_021DA368

	thumb_func_start MOD17_021DA36C
MOD17_021DA36C: ; 0x021DA36C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	ldr r6, [r7, #0x1c]
	mov r4, #0
	add r7, #0x14
	str r1, [sp]
	str r2, [sp, #4]
	add r5, r4, #0
	cmp r6, r7
	beq _021DA3CA
_021DA382:
	add r0, r6, #0
	add r1, sp, #0xc
	add r2, sp, #8
	bl MOD17_021DA528
	cmp r4, #0
	bge _021DA394
	neg r1, r4
	b _021DA396
_021DA394:
	add r1, r4, #0
_021DA396:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bge _021DA3A0
	neg r2, r0
	b _021DA3A2
_021DA3A0:
	add r2, r0, #0
_021DA3A2:
	cmp r2, r1
	ble _021DA3A8
	add r4, r0, #0
_021DA3A8:
	cmp r5, #0
	bge _021DA3B0
	neg r1, r5
	b _021DA3B2
_021DA3B0:
	add r1, r5, #0
_021DA3B2:
	ldr r0, [sp, #8]
	cmp r0, #0
	bge _021DA3BC
	neg r2, r0
	b _021DA3BE
_021DA3BC:
	add r2, r0, #0
_021DA3BE:
	cmp r2, r1
	ble _021DA3C4
	add r5, r0, #0
_021DA3C4:
	ldr r6, [r6, #8]
	cmp r6, r7
	bne _021DA382
_021DA3CA:
	ldr r0, [sp]
	str r4, [r0]
	ldr r0, [sp, #4]
	str r5, [r0]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA36C

	thumb_func_start MOD17_021DA3D8
MOD17_021DA3D8: ; 0x021DA3D8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	ldr r4, [r0, #0x1c]
	add r7, #0x14
	str r0, [sp]
	add r6, r1, #0
	cmp r4, r7
	beq _021DA436
	asr r0, r6, #0xa
	mov r1, #0x1f
	and r0, r1
	str r0, [sp, #0xc]
	asr r0, r6, #5
	and r0, r1
	str r0, [sp, #8]
	add r0, r6, #0
	and r0, r1
	str r0, [sp, #4]
_021DA3FE:
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021DA410
	ldr r0, [r4]
	add r1, r6, #0
	ldr r0, [r0, #4]
	bl FUN_02013F0C
	b _021DA430
_021DA410:
	ldr r5, [r4]
	ldr r2, [sp, #0xc]
	ldr r0, [r5]
	mov r1, #0x18
	bl FUN_02007558
	ldr r0, [r5]
	ldr r2, [sp, #8]
	mov r1, #0x19
	bl FUN_02007558
	ldr r0, [r5]
	ldr r2, [sp, #4]
	mov r1, #0x1a
	bl FUN_02007558
_021DA430:
	ldr r4, [r4, #8]
	cmp r4, r7
	bne _021DA3FE
_021DA436:
	ldr r0, [sp]
	ldr r4, [r0, #0xc]
	add r5, r0, #4
	cmp r4, r5
	beq _021DA450
_021DA440:
	ldr r0, [r4]
	add r1, r6, #0
	ldr r0, [r0, #4]
	bl FUN_02013F0C
	ldr r4, [r4, #8]
	cmp r4, r5
	bne _021DA440
_021DA450:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DA3D8

	thumb_func_start MOD17_021DA454
MOD17_021DA454: ; 0x021DA454
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x50
	str r0, [sp, #0xc]
	str r2, [sp, #0x14]
	str r1, [sp, #0x10]
	add r0, r1, #0
	add r1, sp, #0x4c
	add r2, sp, #0x48
	add r4, r3, #0
	bl MOD17_021DBBB8
	ldr r0, [sp, #0x10]
	add r1, sp, #0x44
	add r2, sp, #0x40
	bl MOD17_021DBC08
	ldr r0, [sp, #0x10]
	add r1, sp, #0x3c
	add r2, sp, #0x38
	bl MOD17_021DBC20
	mov r0, #0x76
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r5, #0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x4c]
	ldr r1, [sp, #0x44]
	str r0, [sp, #0x24]
	add r0, r0, r1
	ldr r6, [sp, #0x3c]
	ldr r1, [sp, #0x40]
	sub r0, r0, r6
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x38]
	str r0, [sp, #0x28]
	add r0, r0, r1
	sub r0, r0, r7
	str r0, [sp, #0x18]
	ldr r0, [sp, #0xc]
	add r4, r5, #0
	str r0, [sp, #0x2c]
	add r0, #0x78
	str r0, [sp, #0x2c]
_021DA4AE:
	str r4, [sp]
	add r0, sp, #0x34
	str r0, [sp, #4]
	add r0, sp, #0x30
	str r0, [sp, #8]
	ldr r0, [sp, #0x28]
	ldr r2, [sp, #0x24]
	ldr r1, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	add r0, r0, r7
	add r2, r2, r6
	bl MOD17_021D9E78
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x34]
	ldr r2, [sp, #0x30]
	ldr r3, [sp, #0x20]
	bl MOD17_021DB8F8
	add r4, r4, #1
	orr r5, r0
	cmp r4, #0x10
	blt _021DA4AE
	cmp r5, #0
	beq _021DA504
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _021DA4F6
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	add r1, #0x14
	str r1, [sp, #0xc]
	bl MOD17_021DBA90
	add sp, #0x50
	pop {r3, r4, r5, r6, r7, pc}
_021DA4F6:
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r1, [r1, #0x20]
	bl MOD17_021DBA90
	add sp, #0x50
	pop {r3, r4, r5, r6, r7, pc}
_021DA504:
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _021DA518
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	add r1, r1, #4
	bl MOD17_021DBA90
	add sp, #0x50
	pop {r3, r4, r5, r6, r7, pc}
_021DA518:
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r1, [r1, #0x10]
	bl MOD17_021DBA90
	add sp, #0x50
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA454

	thumb_func_start MOD17_021DA528
MOD17_021DA528: ; 0x021DA528
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	add r4, r2, #0
	add r6, r0, #0
	add r1, sp, #0x14
	add r2, sp, #0x10
	bl MOD17_021DBC08
	add r0, r6, #0
	add r1, sp, #0xc
	add r2, sp, #8
	bl MOD17_021DBBB8
	add r0, r6, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021DBC20
	ldr r1, [sp, #4]
	ldr r0, [sp, #0xc]
	mov r2, #0x8a
	add r3, r0, r1
	sub r6, r2, r3
	ldr r2, [sp, #0x14]
	ldr r7, [sp, #8]
	add r0, r0, r2
	sub r3, r0, r1
	ldr r2, [sp]
	mov r0, #0x12
	add r1, r7, r2
	sub r0, r0, r1
	ldr r1, [sp, #0x10]
	sub r3, #0xf6
	add r1, r7, r1
	sub r2, r1, r2
	sub r2, #0x8f
	cmp r6, #0
	ble _021DA57A
	str r6, [r5]
	b _021DA588
_021DA57A:
	cmp r3, #0
	ble _021DA584
	neg r1, r3
	str r1, [r5]
	b _021DA588
_021DA584:
	mov r1, #0
	str r1, [r5]
_021DA588:
	cmp r0, #0
	ble _021DA592
	add sp, #0x18
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_021DA592:
	cmp r2, #0
	ble _021DA59E
	neg r0, r2
	add sp, #0x18
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_021DA59E:
	mov r0, #0
	str r0, [r4]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA528

	thumb_func_start MOD17_021DA5A8
MOD17_021DA5A8: ; 0x021DA5A8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	str r1, [r5, #0x44]
	ldr r1, [r4, #4]
	str r1, [r5, #0x48]
	ldr r1, [r4, #8]
	str r1, [r5, #0x4c]
	ldr r1, [r4, #0xc]
	str r1, [r5, #0x50]
	ldr r1, [r4, #0x10]
	str r1, [r5, #0x54]
	ldr r1, [r4, #0x14]
	str r1, [r5, #0x58]
	ldr r1, [r4, #0x18]
	str r1, [r5, #8]
	ldr r1, [r4, #0x28]
	str r1, [r5, #4]
	mov r1, #0
	bl MOD17_021DA9AC
	add r0, r5, #0
	add r1, r4, #0
	bl MOD17_021DAAC8
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA5A8

	thumb_func_start MOD17_021DA5E0
MOD17_021DA5E0: ; 0x021DA5E0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl MOD17_021DA818
	add r5, r6, #0
	mov r4, #0
	add r5, #0xc
_021DA5EE:
	add r0, r5, #0
	bl MOD17_021DAB8C
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #4
	blt _021DA5EE
	add r0, r6, #0
	mov r1, #0
	mov r2, #0x8c
	bl memset
	pop {r4, r5, r6, pc}
	thumb_func_end MOD17_021DA5E0

	thumb_func_start MOD17_021DA608
MOD17_021DA608: ; 0x021DA608
	push {r3, lr}
	cmp r0, #0
	beq _021DA618
	cmp r0, #1
	beq _021DA688
	cmp r0, #2
	beq _021DA696
	pop {r3, pc}
_021DA618:
	cmp r1, #5
	bgt _021DA620
	mov r0, #0
	pop {r3, pc}
_021DA620:
	cmp r1, #0xb
	bgt _021DA628
	mov r0, #1
	pop {r3, pc}
_021DA628:
	cmp r1, #0x11
	bgt _021DA630
	mov r0, #2
	pop {r3, pc}
_021DA630:
	cmp r1, #0x15
	bgt _021DA638
	mov r0, #3
	pop {r3, pc}
_021DA638:
	cmp r1, #0x1c
	bgt _021DA640
	mov r0, #4
	pop {r3, pc}
_021DA640:
	cmp r1, #0x21
	bgt _021DA648
	mov r0, #5
	pop {r3, pc}
_021DA648:
	cmp r1, #0x26
	bgt _021DA650
	mov r0, #6
	pop {r3, pc}
_021DA650:
	cmp r1, #0x2a
	bgt _021DA658
	mov r0, #7
	pop {r3, pc}
_021DA658:
	cmp r1, #0x31
	bgt _021DA660
	mov r0, #8
	pop {r3, pc}
_021DA660:
	cmp r1, #0x37
	bgt _021DA668
	mov r0, #9
	pop {r3, pc}
_021DA668:
	cmp r1, #0x3c
	bgt _021DA670
	mov r0, #0xa
	pop {r3, pc}
_021DA670:
	cmp r1, #0x47
	bgt _021DA678
	mov r0, #0xb
	pop {r3, pc}
_021DA678:
	cmp r1, #0x5b
	bgt _021DA680
	mov r0, #0xc
	pop {r3, pc}
_021DA680:
	cmp r1, #0x63
	bgt _021DA6A2
	mov r0, #0xd
	pop {r3, pc}
_021DA688:
	add r0, r2, #0
	bl MOD17_021DB014
	mov r1, #9
	bl _s32_div_f
	pop {r3, pc}
_021DA696:
	add r0, r2, #0
	bl MOD17_021DB014
	mov r1, #9
	bl _s32_div_f
_021DA6A2:
	pop {r3, pc}
	thumb_func_end MOD17_021DA608

	thumb_func_start MOD17_021DA6A4
MOD17_021DA6A4: ; 0x021DA6A4
	push {r3, r4, r5, lr}
	add r5, r2, #0
	add r4, r3, #0
	cmp r0, #0
	beq _021DA6B8
	cmp r0, #1
	beq _021DA6EA
	cmp r0, #2
	beq _021DA6EA
	pop {r3, r4, r5, pc}
_021DA6B8:
	mov r0, #0xa
	str r0, [r5]
	mov r0, #0x12
	str r0, [r4]
	bl MTRandom
	ldr r2, [sp, #0x10]
	mov r1, #0x6c
	sub r1, r1, r2
	bl _u32_div_f
	ldr r0, [r5]
	add r0, r0, r1
	str r0, [r5]
	bl MTRandom
	ldr r2, [sp, #0x14]
	mov r1, #0x7d
	sub r1, r1, r2
	bl _u32_div_f
	ldr r0, [r4]
	add r0, r0, r1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021DA6EA:
	ldr r0, [sp, #0x18]
	bl MOD17_021DB014
	add r1, r5, #0
	add r2, r4, #0
	bl MOD17_021DAC68
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA6A4

	thumb_func_start MOD17_021DA6FC
MOD17_021DA6FC: ; 0x021DA6FC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x48
	add r5, r0, #0
	ldr r0, [r5, #0x58]
	add r4, r2, #0
	str r4, [sp, #0x40]
	str r0, [sp, #0x28]
	ldr r0, [r5, #0x44]
	add r6, r1, #0
	mov r1, #0
	str r0, [sp, #0x2c]
	str r1, [sp, #0x38]
	str r1, [sp, #0x3c]
	cmp r6, #0
	beq _021DA724
	cmp r6, #1
	beq _021DA730
	cmp r6, #2
	beq _021DA73E
	b _021DA74C
_021DA724:
	ldr r0, [r5, #0x50]
	str r4, [sp, #0xc]
	ldrb r0, [r0, r4]
	add r7, r1, #0
	str r0, [sp, #0x44]
	b _021DA750
_021DA730:
	add r0, r4, #0
	str r0, [sp, #0xc]
	add r0, #0x64
	str r0, [sp, #0xc]
	add r7, r4, #1
	str r1, [sp, #0x44]
	b _021DA750
_021DA73E:
	add r0, r4, #0
	str r0, [sp, #0xc]
	add r0, #0x64
	str r0, [sp, #0xc]
	add r7, r4, #1
	str r1, [sp, #0x44]
	b _021DA750
_021DA74C:
	bl GF_AssertFail
_021DA750:
	ldr r0, [sp, #0xc]
	ldr r1, [r5, #0x48]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r1, r7, #2
	str r0, [sp, #0x30]
	ldr r2, [r5, #0x4c]
	cmp r0, #0
	ldr r1, [r2, r1]
	str r1, [sp, #0x34]
	bne _021DA76A
	bl GF_AssertFail
_021DA76A:
	ldr r0, [sp, #0x34]
	cmp r0, #0
	bne _021DA774
	bl GF_AssertFail
_021DA774:
	ldr r2, [r5, #4]
	add r0, r6, #0
	add r1, r4, #0
	bl MOD17_021DA608
	add r7, r0, #0
	add r0, sp, #0x28
	bl MOD17_021D7520
	str r0, [sp, #0x10]
	ldr r0, [r5, #8]
	ldr r1, [sp, #0x10]
	add r2, r6, #0
	bl MOD17_021DBA30
	mov r1, #0xc
	mul r1, r6
	add r1, r5, r1
	ldr r2, [r1, #0xc]
	lsl r1, r7, #4
	add r1, r2, r1
	ldr r1, [r1, #0xc]
	str r0, [sp, #0x14]
	bl MOD17_021DBA90
	ldr r0, [sp, #0x14]
	add r1, sp, #0x1c
	add r2, sp, #0x18
	bl MOD17_021DBC08
	ldr r0, [sp, #0x1c]
	add r1, r4, #0
	str r0, [sp]
	ldr r0, [sp, #0x18]
	add r2, sp, #0x24
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	add r3, sp, #0x20
	str r0, [sp, #8]
	add r0, r6, #0
	bl MOD17_021DA6A4
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x20]
	bl MOD17_021DBB68
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	add r2, r6, #0
	add r3, r7, #0
	bl MOD17_021DAC40
	add sp, #0x48
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA6FC

	thumb_func_start MOD17_021DA7E4
MOD17_021DA7E4: ; 0x021DA7E4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	mov r1, #0xc
	add r5, r0, #0
	mul r1, r4
	add r7, r3, #0
	add r1, r5, r1
	add r6, r2, #0
	ldr r2, [r1, #0xc]
	lsl r1, r6, #4
	add r0, r7, #0
	add r1, r2, r1
	bl MOD17_021DBA90
	ldr r1, [r7]
	add r0, r5, #0
	add r2, r4, #0
	add r3, r6, #0
	bl MOD17_021DAC40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA7E4

	thumb_func_start MOD17_021DA810
MOD17_021DA810: ; 0x021DA810
	ldr r3, _021DA814 ; =MOD17_021DBAA0
	bx r3
	.align 2, 0
_021DA814: .word MOD17_021DBAA0
	thumb_func_end MOD17_021DA810

	thumb_func_start MOD17_021DA818
MOD17_021DA818: ; 0x021DA818
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r7, #0
_021DA81E:
	ldr r0, [r5, #0x10]
	mov r6, #0
	cmp r0, #0
	ble _021DA83A
	add r4, r6, #0
_021DA828:
	ldr r0, [r5, #0xc]
	add r0, r0, r4
	bl MOD17_021DBAB0
	ldr r0, [r5, #0x10]
	add r6, r6, #1
	add r4, #0x10
	cmp r6, r0
	blt _021DA828
_021DA83A:
	add r7, r7, #1
	add r5, #0xc
	cmp r7, #3
	blt _021DA81E
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DA818

	thumb_func_start MOD17_021DA844
MOD17_021DA844: ; 0x021DA844
	push {r4, r5, r6, lr}
	mov r5, #0
	mvn r5, r5
	bl MOD17_021DABB4
	add r6, r0, #0
	ldr r4, [r6, #8]
	cmp r4, r6
	beq _021DA86C
_021DA856:
	ldr r0, [r4, #4]
	cmp r0, #2
	bhi _021DA864
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD17_021D766C
_021DA864:
	ldr r4, [r4, #8]
	sub r5, r5, #1
	cmp r4, r6
	bne _021DA856
_021DA86C:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA844

	thumb_func_start MOD17_021DA870
MOD17_021DA870: ; 0x021DA870
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r6, r1, #0
	ldr r1, [r5, #0x3c]
	add r4, r2, #0
	cmp r1, #0
	bne _021DA8A8
	ldr r1, [r5]
	mov r2, #0xc
	mul r2, r1
	str r4, [sp]
	add r2, r5, r2
	ldr r2, [r2, #0x14]
	add r3, r6, #0
	bl MOD17_021DACA4
	mov r0, #0xc
	mul r0, r6
	str r6, [r5]
	add r0, r5, r0
	str r4, [r0, #0x14]
	add r0, r5, #0
	bl MOD17_021DA844
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021DA8A8:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA870

	thumb_func_start MOD17_021DA8B0
MOD17_021DA8B0: ; 0x021DA8B0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r1, [sp, #4]
	str r0, [sp]
	str r2, [sp, #8]
	bl MOD17_021DAA7C
	add r7, r0, #0
	ldr r0, [sp, #4]
	mov r1, #0xc
	mul r1, r0
	ldr r0, [sp]
	mov r4, #1
	add r6, r0, r1
	ldr r0, [r6, #0x10]
	cmp r0, #1
	ble _021DA912
_021DA8D2:
	ldr r0, [sp, #8]
	cmp r0, #0
	bne _021DA8E4
	ldr r1, [r6, #0x10]
	add r0, r4, r7
	bl _s32_div_f
	add r5, r1, #0
	b _021DA8EC
_021DA8E4:
	sub r5, r7, r4
	bpl _021DA8EC
	ldr r0, [r6, #0x10]
	add r5, r5, r0
_021DA8EC:
	ldr r0, [sp]
	ldr r1, [sp, #4]
	add r2, r5, #0
	bl MOD17_021DABDC
	ldr r1, [r0, #8]
	cmp r1, r0
	beq _021DA90A
	ldr r0, [sp]
	ldr r1, [sp, #4]
	add r2, r5, #0
	bl MOD17_021DA870
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_021DA90A:
	ldr r0, [r6, #0x10]
	add r4, r4, #1
	cmp r4, r0
	blt _021DA8D2
_021DA912:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DA8B0

	thumb_func_start MOD17_021DA918
MOD17_021DA918: ; 0x021DA918
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #0
	add r5, r0, #0
	add r6, r2, #0
	bl MOD17_021DAB38
	mov r0, #0xc
	mul r0, r4
	str r4, [r5]
	add r0, r5, r0
	str r6, [r0, #0x14]
	add r0, r5, #0
	mov r1, #1
	bl MOD17_021DAB38
	add r0, r5, #0
	bl MOD17_021DA844
	pop {r4, r5, r6, pc}
	thumb_func_end MOD17_021DA918

	thumb_func_start MOD17_021DA940
MOD17_021DA940: ; 0x021DA940
	push {r3, lr}
	mov r1, #0x12
	add r0, sp, #0
	strb r1, [r0]
	mov r1, #0x8f
	strb r1, [r0, #1]
	mov r1, #0xa
	strb r1, [r0, #2]
	mov r1, #0x76
	strb r1, [r0, #3]
	add r0, sp, #0
	bl FUN_02020A40
	pop {r3, pc}
	thumb_func_end MOD17_021DA940

	thumb_func_start MOD17_021DA95C
MOD17_021DA95C: ; 0x021DA95C
	push {r3, lr}
	mov r3, #0x12
	add r0, sp, #0
	strb r3, [r0]
	mov r3, #0x8f
	strb r3, [r0, #1]
	mov r3, #0xa
	strb r3, [r0, #2]
	mov r3, #0x76
	strb r3, [r0, #3]
	add r0, sp, #0
	bl FUN_02020AE8
	pop {r3, pc}
	thumb_func_end MOD17_021DA95C

	thumb_func_start MOD17_021DA978
MOD17_021DA978: ; 0x021DA978
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp]
	bl MOD17_021DABB4
	add r5, r0, #0
	ldr r4, [r5, #8]
	cmp r4, r5
	beq _021DA9A6
_021DA98C:
	ldr r3, [sp]
	add r0, r4, #0
	add r1, r6, #0
	add r2, r7, #0
	bl MOD17_021DBB1C
	cmp r0, #1
	bne _021DA9A0
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_021DA9A0:
	ldr r4, [r4, #8]
	cmp r4, r5
	bne _021DA98C
_021DA9A6:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DA978

	thumb_func_start MOD17_021DA9AC
MOD17_021DA9AC: ; 0x021DA9AC
	push {r3, r4, r5, lr}
	sub sp, #0x30
	add r5, r0, #0
	ldr r0, [r5, #0x54]
	add r4, r1, #0
	str r0, [sp]
	mov r0, #0x19
	lsl r1, r4, #1
	str r0, [sp, #4]
	add r0, r1, #0
	add r0, #0x81
	str r0, [sp, #8]
	mov r0, #0x85
	str r0, [sp, #0xc]
	mov r0, #8
	str r0, [sp, #0x14]
	mov r0, #0x81
	str r0, [sp, #0x18]
	mov r0, #3
	str r0, [sp, #0x1c]
	mov r0, #1
	str r0, [sp, #0x20]
	mov r0, #2
	str r0, [sp, #0x24]
	mov r0, #0
	str r0, [sp, #0x28]
	mov r0, #0xe
	add r1, #0x82
	str r0, [sp, #0x2c]
	add r0, r5, #0
	str r1, [sp, #0x10]
	add r0, #0x5c
	add r1, sp, #0
	bl MOD17_021DBD04
	str r4, [r5, #0x40]
	add sp, #0x30
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DA9AC

	thumb_func_start MOD17_021DA9F8
MOD17_021DA9F8: ; 0x021DA9F8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r0, #0
	ldr r0, [r5, #0x54]
	add r4, r1, #0
	str r0, [sp, #8]
	mov r0, #0x19
	lsl r1, r4, #1
	str r0, [sp, #0xc]
	add r0, r1, #0
	add r0, #0x81
	str r0, [sp, #0x10]
	mov r0, #0x85
	str r0, [sp, #0x14]
	mov r0, #8
	add r1, #0x82
	str r0, [sp, #0x1c]
	mov r0, #0x81
	str r1, [sp, #0x18]
	str r0, [sp, #0x20]
	mov r0, #3
	mov r1, #2
	str r0, [sp, #0x24]
	mov r0, #1
	str r1, [sp, #0x2c]
	mov r7, #0
	mov r1, #0xe
	str r0, [sp, #0x28]
	str r7, [sp, #0x30]
	str r1, [sp, #0x34]
	tst r0, r2
	beq _021DAA3A
	mov r7, #0x70
_021DAA3A:
	mov r0, #2
	tst r0, r2
	beq _021DAA44
	mov r6, #0x81
	b _021DAA46
_021DAA44:
	mov r6, #0
_021DAA46:
	ldr r0, [sp, #0x50]
	str r3, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x5c
	add r1, sp, #8
	add r2, r7, #0
	add r3, r6, #0
	bl MOD17_021DBE3C
	str r4, [r5, #0x40]
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DA9F8

	thumb_func_start MOD17_021DAA60
MOD17_021DAA60: ; 0x021DAA60
	ldr r3, _021DAA68 ; =MOD17_021DBD4C
	add r0, #0x5c
	bx r3
	nop
_021DAA68: .word MOD17_021DBD4C
	thumb_func_end MOD17_021DAA60

	thumb_func_start MOD17_021DAA6C
MOD17_021DAA6C: ; 0x021DAA6C
	push {r4, lr}
	add r4, r0, #0
	bne _021DAA76
	bl GF_AssertFail
_021DAA76:
	ldr r0, [r4]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DAA6C

	thumb_func_start MOD17_021DAA7C
MOD17_021DAA7C: ; 0x021DAA7C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	cmp r5, #0
	bne _021DAA8C
	bl GF_AssertFail
_021DAA8C:
	mov r0, #0xc
	mul r0, r4
	add r3, r5, r0
	add r3, #0xc
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [sp, #8]
	add sp, #0xc
	pop {r4, r5, pc}
	thumb_func_end MOD17_021DAA7C

	thumb_func_start MOD17_021DAAA4
MOD17_021DAAA4: ; 0x021DAAA4
	push {r4, lr}
	add r4, r3, #0
	bl MOD17_021DABDC
	ldr r2, [sp, #8]
	add r1, r4, #0
	bl MOD17_021DBC38
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DAAA4

	thumb_func_start MOD17_021DAAB8
MOD17_021DAAB8: ; 0x021DAAB8
	ldr r0, [r0, #0x3c]
	cmp r0, #0
	bne _021DAAC2
	mov r0, #1
	bx lr
_021DAAC2:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DAAB8

	thumb_func_start MOD17_021DAAC8
MOD17_021DAAC8: ; 0x021DAAC8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4, #0x1c]
	add r5, r0, #0
	add r0, #0xc
	bl MOD17_021DAB48
	mov r0, #0
	str r0, [r5]
	ldr r0, [r5, #0xc]
	mov r1, #1
	bl MOD17_021DAB04
	add r0, r5, #0
	ldr r1, [r4, #0x20]
	add r0, #0x18
	bl MOD17_021DAB48
	add r0, r5, #0
	ldr r1, [r4, #0x24]
	add r0, #0x24
	bl MOD17_021DAB48
	add r5, #0x30
	add r0, r5, #0
	mov r1, #1
	bl MOD17_021DAB48
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DAAC8

	thumb_func_start MOD17_021DAB04
MOD17_021DAB04: ; 0x021DAB04
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r4, [r5, #8]
	add r6, r1, #0
	cmp r4, r5
	beq _021DAB24
_021DAB10:
	ldr r0, [r4, #4]
	cmp r0, #2
	bhi _021DAB1E
	ldr r0, [r4]
	add r1, r6, #0
	bl MOD17_021D7660
_021DAB1E:
	ldr r4, [r4, #8]
	cmp r4, r5
	bne _021DAB10
_021DAB24:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DAB04

	thumb_func_start MOD17_021DAB28
MOD17_021DAB28: ; 0x021DAB28
	push {r4, lr}
	add r4, r3, #0
	bl MOD17_021DABDC
	add r1, r4, #0
	bl MOD17_021DAB04
	pop {r4, pc}
	thumb_func_end MOD17_021DAB28

	thumb_func_start MOD17_021DAB38
MOD17_021DAB38: ; 0x021DAB38
	push {r4, lr}
	add r4, r1, #0
	bl MOD17_021DABB4
	add r1, r4, #0
	bl MOD17_021DAB04
	pop {r4, pc}
	thumb_func_end MOD17_021DAB38

	thumb_func_start MOD17_021DAB48
MOD17_021DAB48: ; 0x021DAB48
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r0, #0xe
	lsl r1, r4, #4
	bl AllocFromHeap
	str r0, [r5]
	str r4, [r5, #4]
	mov r6, #0
	str r6, [r5, #8]
	ldr r0, [r5, #4]
	cmp r0, #0
	ble _021DAB88
	add r4, r6, #0
	add r7, r6, #0
_021DAB68:
	ldr r0, [r5]
	add r1, r7, #0
	add r0, r0, r4
	str r0, [r0, #8]
	ldr r0, [r5]
	add r0, r0, r4
	str r0, [r0, #0xc]
	ldr r0, [r5]
	add r0, r0, r4
	bl MOD17_021DAB04
	ldr r0, [r5, #4]
	add r6, r6, #1
	add r4, #0x10
	cmp r6, r0
	blt _021DAB68
_021DAB88:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DAB48

	thumb_func_start MOD17_021DAB8C
MOD17_021DAB8C: ; 0x021DAB8C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4]
	strb r0, [r4]
	strb r0, [r4, #1]
	strb r0, [r4, #2]
	strb r0, [r4, #3]
	strb r0, [r4, #4]
	strb r0, [r4, #5]
	strb r0, [r4, #6]
	strb r0, [r4, #7]
	strb r0, [r4, #8]
	strb r0, [r4, #9]
	strb r0, [r4, #0xa]
	strb r0, [r4, #0xb]
	pop {r4, pc}
	thumb_func_end MOD17_021DAB8C

	thumb_func_start MOD17_021DABB4
MOD17_021DABB4: ; 0x021DABB4
	push {r3}
	sub sp, #0xc
	ldr r2, [r0]
	mov r1, #0xc
	mul r1, r2
	add r3, r0, r1
	add r3, #0xc
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [sp, #8]
	ldr r1, [sp]
	lsl r0, r0, #4
	add r0, r1, r0
	add sp, #0xc
	pop {r3}
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DABB4

	thumb_func_start MOD17_021DABDC
MOD17_021DABDC: ; 0x021DABDC
	push {r4}
	sub sp, #0xc
	mov r3, #0xc
	mul r3, r1
	add r4, r0, r3
	add r4, #0xc
	ldmia r4!, {r0, r1}
	add r3, sp, #0
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	str r0, [r3]
	ldr r1, [sp]
	lsl r0, r2, #4
	add r0, r1, r0
	add sp, #0xc
	pop {r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DABDC

	thumb_func_start MOD17_021DAC00
MOD17_021DAC00: ; 0x021DAC00
	push {r4, lr}
	mov r4, #0
	bl MOD17_021DABDC
	ldr r1, [r0, #8]
	cmp r1, r0
	beq _021DAC16
_021DAC0E:
	ldr r1, [r1, #8]
	add r4, r4, #1
	cmp r1, r0
	bne _021DAC0E
_021DAC16:
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DAC00

	thumb_func_start MOD17_021DAC1C
MOD17_021DAC1C: ; 0x021DAC1C
	push {r3, r4, r5, lr}
	add r5, r3, #0
	mov r4, #0
	bl MOD17_021DABDC
	ldr r1, [r0, #8]
	cmp r1, r0
	beq _021DAC3C
_021DAC2C:
	cmp r4, r5
	bne _021DAC34
	add r0, r1, #0
	pop {r3, r4, r5, pc}
_021DAC34:
	ldr r1, [r1, #8]
	add r4, r4, #1
	cmp r1, r0
	bne _021DAC2C
_021DAC3C:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DAC1C

	thumb_func_start MOD17_021DAC40
MOD17_021DAC40: ; 0x021DAC40
	push {r4, lr}
	ldr r4, [r0]
	cmp r4, r2
	bne _021DAC54
	mov r4, #0xc
	mul r4, r2
	add r0, r0, r4
	ldr r0, [r0, #0x14]
	cmp r3, r0
	beq _021DAC5E
_021DAC54:
	add r0, r1, #0
	mov r1, #0
	bl MOD17_021D7660
	pop {r4, pc}
_021DAC5E:
	add r0, r1, #0
	mov r1, #1
	bl MOD17_021D7660
	pop {r4, pc}
	thumb_func_end MOD17_021DAC40

	thumb_func_start MOD17_021DAC68
MOD17_021DAC68: ; 0x021DAC68
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	mov r1, #9
	add r4, r2, #0
	bl _s32_div_f
	add r7, r1, #0
	add r0, r7, #0
	mov r1, #3
	bl _s32_div_f
	add r6, r0, #0
	add r0, r7, #0
	mov r1, #3
	bl _s32_div_f
	add r0, r6, #1
	lsl r2, r0, #3
	lsl r0, r6, #5
	add r0, r2, r0
	add r0, #0x10
	str r0, [r4]
	add r0, r1, #1
	lsl r2, r0, #3
	mov r0, #0x18
	mul r0, r1
	add r0, r2, r0
	add r0, #8
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DAC68

	thumb_func_start MOD17_021DACA4
MOD17_021DACA4: ; 0x021DACA4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp]
	ldr r0, _021DAD18 ; =MOD17_021DAD1C
	mov r1, #0x30
	mov r2, #0
	mov r3, #0xd
	bl FUN_020061E8
	bl FUN_0201B6C8
	add r4, r0, #0
	str r5, [r4]
	str r6, [r4, #4]
	ldr r0, [sp]
	str r7, [r4, #8]
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x18]
	add r1, r6, #0
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0x1c]
	add r0, r5, #0
	add r2, r7, #0
	bl MOD17_021DAC00
	str r0, [r4, #0x20]
	ldr r1, [sp]
	ldr r2, [sp, #0x18]
	add r0, r5, #0
	bl MOD17_021DAC00
	str r0, [r4, #0x24]
	ldr r1, [r4, #0x20]
	add r2, r1, r0
	mov r1, #0xc
	mov r0, #0xd
	mul r1, r2
	str r2, [r4, #0x2c]
	bl AllocFromHeap
	str r0, [r4, #0x28]
	cmp r0, #0
	bne _021DAD04
	bl GF_AssertFail
_021DAD04:
	ldr r3, [r4, #0x2c]
	mov r2, #0xc
	ldr r0, [r4, #0x28]
	mov r1, #0
	mul r2, r3
	bl memset
	mov r0, #1
	str r0, [r5, #0x3c]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DAD18: .word MOD17_021DAD1C
	thumb_func_end MOD17_021DACA4

	thumb_func_start MOD17_021DAD1C
MOD17_021DAD1C: ; 0x021DAD1C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x1c]
	cmp r0, #4
	bls _021DAD2C
	b _021DAE74
_021DAD2C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DAD38: ; jump table
	.short _021DAD42 - _021DAD38 - 2 ; case 0
	.short _021DAD96 - _021DAD38 - 2 ; case 1
	.short _021DADE2 - _021DAD38 - 2 ; case 2
	.short _021DAE28 - _021DAD38 - 2 ; case 3
	.short _021DAE40 - _021DAD38 - 2 ; case 4
_021DAD42:
	mov r0, #0x83
	mvn r0, r0
	str r0, [sp]
	ldr r0, [r4]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x10]
	mov r3, #0
	bl MOD17_021DAAA4
	ldr r0, [r4]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x10]
	mov r3, #1
	bl MOD17_021DAB28
	mov r0, #0
	str r0, [r4, #0x14]
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x14
	str r1, [sp]
	ldr r1, [r0, #0x40]
	add r1, r1, #1
	lsr r3, r1, #0x1f
	lsl r2, r1, #0x1f
	sub r2, r2, r3
	mov r1, #0x1f
	ror r2, r1
	add r1, r3, r2
	mov r2, #2
	mov r3, #5
	bl MOD17_021DA9F8
	ldr r0, [r4, #0x20]
	mov r1, #1
	bl MOD17_021DAF30
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	b _021DAE78
_021DAD96:
	ldr r0, [r4, #0x18]
	mov r6, #0
	cmp r0, #0
	ble _021DADCA
	add r5, r4, #0
	add r5, #0x20
_021DADA2:
	ldr r0, [r4, #0x20]
	sub r0, r0, #1
	bmi _021DADC2
	ldr r0, [r5]
	sub r0, r0, #1
	str r0, [r5]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0x20]
	bl MOD17_021DAC1C
	ldr r1, [r4, #0x28]
	ldr r2, [r4, #0x2c]
	bl MOD17_021DAE84
_021DADC2:
	ldr r0, [r4, #0x18]
	add r6, r6, #1
	cmp r6, r0
	blt _021DADA2
_021DADCA:
	ldr r0, [r4, #0x20]
	cmp r0, #0
	bne _021DAE78
	ldr r0, [r4, #0x24]
	mov r1, #2
	bl MOD17_021DAF30
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	b _021DAE78
_021DADE2:
	ldr r0, [r4, #0x18]
	mov r6, #0
	cmp r0, #0
	ble _021DAE16
	add r5, r4, #0
	add r5, #0x24
_021DADEE:
	ldr r0, [r4, #0x24]
	sub r0, r0, #1
	bmi _021DAE0E
	ldr r0, [r5]
	sub r0, r0, #1
	str r0, [r5]
	ldr r0, [r4]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0x24]
	bl MOD17_021DAC1C
	ldr r1, [r4, #0x28]
	ldr r2, [r4, #0x2c]
	bl MOD17_021DAE84
_021DAE0E:
	ldr r0, [r4, #0x18]
	add r6, r6, #1
	cmp r6, r0
	blt _021DADEE
_021DAE16:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	bne _021DAE78
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	mov r0, #0
	str r0, [r4, #0x18]
	b _021DAE78
_021DAE28:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	cmp r0, #3
	ble _021DAE78
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021DAE78
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	b _021DAE78
_021DAE40:
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	mov r3, #0
	bl MOD17_021DAB28
	mov r0, #0x83
	mvn r0, r0
	str r0, [sp]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	mov r3, #0
	bl MOD17_021DAAA4
	ldr r0, [r4]
	mov r1, #0
	str r1, [r0, #0x3c]
	ldr r0, [r4, #0x28]
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200621C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_021DAE74:
	bl GF_AssertFail
_021DAE78:
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	bl MOD17_021DAEC4
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD17_021DAD1C

	thumb_func_start MOD17_021DAE84
MOD17_021DAE84: ; 0x021DAE84
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	bl MOD17_021DAE9C
	str r4, [r0]
	mov r1, #3
	str r1, [r0, #4]
	mov r1, #0x2c
	str r1, [r0, #8]
	pop {r4, pc}
	thumb_func_end MOD17_021DAE84

	thumb_func_start MOD17_021DAE9C
MOD17_021DAE9C: ; 0x021DAE9C
	push {r3, r4}
	mov r3, #0
	cmp r1, #0
	ble _021DAEBE
	add r4, r0, #0
_021DAEA6:
	ldr r2, [r4]
	cmp r2, #0
	bne _021DAEB6
	mov r1, #0xc
	mul r1, r3
	add r0, r0, r1
	pop {r3, r4}
	bx lr
_021DAEB6:
	add r3, r3, #1
	add r4, #0xc
	cmp r3, r1
	blt _021DAEA6
_021DAEBE:
	mov r0, #0
	pop {r3, r4}
	bx lr
	thumb_func_end MOD17_021DAE9C

	thumb_func_start MOD17_021DAEC4
MOD17_021DAEC4: ; 0x021DAEC4
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	mov r4, #0
	cmp r6, #0
	ble _021DAEE4
_021DAED0:
	ldr r0, [r5]
	cmp r0, #0
	beq _021DAEDC
	add r0, r5, #0
	bl MOD17_021DAEE8
_021DAEDC:
	add r4, r4, #1
	add r5, #0xc
	cmp r4, r6
	blt _021DAED0
_021DAEE4:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DAEC4

	thumb_func_start MOD17_021DAEE8
MOD17_021DAEE8: ; 0x021DAEE8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4]
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021DBBB8
	ldr r1, [sp]
	ldr r0, [r4, #8]
	add r2, r1, r0
	str r2, [sp]
	ldr r0, [r4]
	ldr r1, [sp, #4]
	bl MOD17_021DBB68
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #0
	bgt _021DAF2C
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	strb r0, [r4, #2]
	strb r0, [r4, #3]
	strb r0, [r4, #4]
	strb r0, [r4, #5]
	strb r0, [r4, #6]
	strb r0, [r4, #7]
	strb r0, [r4, #8]
	strb r0, [r4, #9]
	strb r0, [r4, #0xa]
	strb r0, [r4, #0xb]
_021DAF2C:
	add sp, #8
	pop {r4, pc}
	thumb_func_end MOD17_021DAEE8

	thumb_func_start MOD17_021DAF30
MOD17_021DAF30: ; 0x021DAF30
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	bl _s32_div_f
	sub r0, r4, r1
	add r0, r5, r0
	add r1, r4, #0
	bl _s32_div_f
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DAF30

	thumb_func_start MOD17_021DAF48
MOD17_021DAF48: ; 0x021DAF48
	add r3, r0, #0
	mov r2, #0x1c
	mov r1, #0
_021DAF4E:
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _021DAF4E
	ldr r1, _021DAF60 ; =MOD17_021DAFA0
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	bx lr
	.align 2, 0
_021DAF60: .word MOD17_021DAFA0
	thumb_func_end MOD17_021DAF48

	thumb_func_start MOD17_021DAF64
MOD17_021DAF64: ; 0x021DAF64
	push {r4, lr}
	ldr r1, _021DAF9C ; =gMain + 0x40
	add r4, r0, #0
	ldrh r2, [r1, #0x20]
	cmp r2, #0
	beq _021DAF76
	ldr r1, [r4, #4]
	blx r1
	b _021DAF8C
_021DAF76:
	ldrh r1, [r1, #0x22]
	cmp r1, #0
	beq _021DAF82
	ldr r1, [r4, #0xc]
	blx r1
	b _021DAF8C
_021DAF82:
	ldrb r1, [r4, #0x18]
	cmp r1, #0
	beq _021DAF8C
	ldr r1, [r4, #8]
	blx r1
_021DAF8C:
	ldr r0, _021DAF9C ; =gMain + 0x40
	ldrh r1, [r0, #0x1c]
	strh r1, [r4, #0x14]
	ldrh r1, [r0, #0x1e]
	strh r1, [r4, #0x16]
	ldrh r0, [r0, #0x22]
	strb r0, [r4, #0x18]
	pop {r4, pc}
	.align 2, 0
_021DAF9C: .word gMain + 0x40
	thumb_func_end MOD17_021DAF64

	thumb_func_start MOD17_021DAFA0
MOD17_021DAFA0: ; 0x021DAFA0
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DAFA0

	thumb_func_start MOD17_021DAFA4
MOD17_021DAFA4: ; 0x021DAFA4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r6, r0, #0
	mov r4, #0
	add r5, r7, #0
_021DAFAE:
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_02027114
	add r4, r4, #1
	stmia r5!, {r0}
	cmp r4, #0x64
	blt _021DAFAE
	mov r0, #0x19
	mov r3, #0
	add r2, r7, #0
	mov r1, #0x12
	lsl r0, r0, #4
_021DAFC8:
	add r3, r3, #1
	str r1, [r2, r0]
	add r2, r2, #4
	cmp r3, #0x12
	blt _021DAFC8
	mov r5, #0x19
	mov r4, #0
	lsl r5, r5, #4
_021DAFD8:
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_0202714C
	cmp r0, #0x12
	beq _021DAFEA
	lsl r0, r0, #2
	add r0, r7, r0
	str r4, [r0, r5]
_021DAFEA:
	add r4, r4, #1
	cmp r4, #0x12
	blt _021DAFD8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DAFA4

	thumb_func_start MOD17_021DAFF4
MOD17_021DAFF4: ; 0x021DAFF4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #0x64
	blo _021DB002
	bl GF_AssertFail
_021DB002:
	lsl r0, r5, #2
	ldr r0, [r4, r0]
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DAFF4

	thumb_func_start MOD17_021DB008
MOD17_021DB008: ; 0x021DB008
	lsl r1, r1, #2
	add r1, r0, r1
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bx lr
	thumb_func_end MOD17_021DB008

	thumb_func_start MOD17_021DB014
MOD17_021DB014: ; 0x021DB014
	push {r3, r4}
	mov r2, #0x19
	mov r4, #0
	lsl r2, r2, #4
_021DB01C:
	ldr r3, [r0, r2]
	cmp r1, r3
	bne _021DB028
	add r0, r4, #0
	pop {r3, r4}
	bx lr
_021DB028:
	add r4, r4, #1
	add r0, r0, #4
	cmp r4, #0x12
	blt _021DB01C
	add r0, r4, #0
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DB014

	thumb_func_start MOD17_021DB038
MOD17_021DB038: ; 0x021DB038
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD17_021DAF48
	mov r0, #0xd
	mov r1, #0x34
	bl AllocFromHeap
	str r0, [r5]
	mov r1, #0
	mov r2, #0x34
	bl memset
	ldr r1, [r5]
	ldr r0, [sp, #0x18]
	str r4, [r1, #4]
	str r6, [r1, #8]
	str r7, [r1]
	str r0, [r1, #0xc]
	ldr r0, [sp, #0x1c]
	str r0, [r1, #0x2c]
	ldr r0, _021DB07C ; =MOD17_021DB0A0
	str r0, [r5, #4]
	ldr r0, _021DB080 ; =MOD17_021DB210
	str r0, [r5, #8]
	ldr r0, _021DB084 ; =MOD17_021DB3A4
	str r0, [r5, #0xc]
	ldr r0, _021DB088 ; =MOD17_021DB08C
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DB07C: .word MOD17_021DB0A0
_021DB080: .word MOD17_021DB210
_021DB084: .word MOD17_021DB3A4
_021DB088: .word MOD17_021DB08C
	thumb_func_end MOD17_021DB038

	thumb_func_start MOD17_021DB08C
MOD17_021DB08C: ; 0x021DB08C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FreeToHeap
	add r0, r4, #0
	bl MOD17_021DAF48
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DB08C

	thumb_func_start MOD17_021DB0A0
MOD17_021DB0A0: ; 0x021DB0A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r4, [r5]
	ldr r0, [r4, #4]
	bl MOD17_021DA250
	cmp r0, #0
	beq _021DB122
	ldr r3, [r4]
	ldr r0, [r4, #4]
	ldr r3, [r3, #0x30]
	add r1, sp, #0xc
	add r2, sp, #8
	bl MOD17_021DA288
	add r6, r0, #0
	beq _021DB0D2
	ldr r0, [r6, #4]
	cmp r0, #3
	bne _021DB0D2
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	bne _021DB0D2
	mov r6, #0
_021DB0D2:
	cmp r6, #0
	beq _021DB15E
	ldr r0, [r6, #4]
	cmp r0, #0
	bne _021DB0E8
	ldr r0, [r4, #4]
	add r1, r6, #0
	bl MOD17_021DA0E8
	mov r7, #0
	b _021DB104
_021DB0E8:
	add r0, r6, #0
	bl MOD17_021DA050
	ldr r0, [r6]
	bl MOD17_021DB7E8
	add r1, r4, #0
	add r2, r4, #0
	add r7, r0, #0
	add r0, r6, #0
	add r1, #0x24
	add r2, #0x28
	bl MOD17_021DBBB8
_021DB104:
	ldr r0, [r4, #4]
	bl MOD17_021DA178
	ldr r0, [sp, #8]
	add r1, r6, #0
	str r0, [sp]
	str r7, [sp, #4]
	ldr r3, [sp, #0xc]
	add r0, r4, #0
	mov r2, #1
	bl MOD17_021DB4D8
	bl MOD17_021D7A7C
	b _021DB15E
_021DB122:
	ldr r0, [r4, #8]
	bl MOD17_021DA940
	cmp r0, #0
	beq _021DB15E
	ldr r3, [r4]
	ldr r0, [r4, #8]
	ldr r3, [r3, #0x30]
	add r1, sp, #0xc
	add r2, sp, #8
	bl MOD17_021DA978
	add r6, r0, #0
	beq _021DB15E
	bl MOD17_021DA810
	ldr r0, [r4, #8]
	bl MOD17_021DA844
	ldr r0, [sp, #8]
	mov r2, #0
	str r0, [sp]
	str r2, [sp, #4]
	ldr r3, [sp, #0xc]
	add r0, r4, #0
	add r1, r6, #0
	bl MOD17_021DB4D8
	bl MOD17_021D7A7C
_021DB15E:
	ldr r1, [r4, #0x10]
	cmp r1, #0
	beq _021DB1A8
	ldr r1, [r1, #4]
	ldr r0, _021DB1AC ; =0x000005EB
	cmp r1, #0
	beq _021DB176
	cmp r1, #1
	beq _021DB180
	cmp r1, #3
	beq _021DB192
	b _021DB19A
_021DB176:
	ldr r1, _021DB1B0 ; =MOD17_021DB210
	str r1, [r5, #8]
	ldr r1, _021DB1B4 ; =MOD17_021DB3A4
	str r1, [r5, #0xc]
	b _021DB19A
_021DB180:
	ldr r0, _021DB1B8 ; =MOD17_021DB1D0
	str r0, [r5, #8]
	ldr r0, _021DB1BC ; =MOD17_021DB1CC
	str r0, [r5, #0xc]
	add r0, r5, #0
	bl MOD17_021DB4AC
	ldr r0, _021DB1C0 ; =0x0000067E
	b _021DB19A
_021DB192:
	ldr r1, _021DB1C4 ; =MOD17_021DB3D4
	str r1, [r5, #8]
	ldr r1, _021DB1C8 ; =MOD17_021DB404
	str r1, [r5, #0xc]
_021DB19A:
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl PlaySE
	add r0, r4, #0
	bl MOD17_021DB680
_021DB1A8:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DB1AC: .word 0x000005EB
_021DB1B0: .word MOD17_021DB210
_021DB1B4: .word MOD17_021DB3A4
_021DB1B8: .word MOD17_021DB1D0
_021DB1BC: .word MOD17_021DB1CC
_021DB1C0: .word 0x0000067E
_021DB1C4: .word MOD17_021DB3D4
_021DB1C8: .word MOD17_021DB404
	thumb_func_end MOD17_021DB0A0

	thumb_func_start MOD17_021DB1CC
MOD17_021DB1CC: ; 0x021DB1CC
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DB1CC

	thumb_func_start MOD17_021DB1D0
MOD17_021DB1D0: ; 0x021DB1D0
	push {r4, lr}
	sub sp, #8
	ldr r4, [r0]
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021DB20A
	ldr r0, [r0, #4]
	cmp r0, #1
	beq _021DB1E6
	bl GF_AssertFail
_021DB1E6:
	ldr r0, [r4, #0x10]
	mov r2, #0x1c
	ldr r0, [r0, #4]
	mov r3, #0x1e
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x21
	ldrb r0, [r0]
	mov r1, #4
	str r0, [sp, #4]
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	add r0, r4, #0
	bl MOD17_021DB59C
	add r0, r4, #0
	bl MOD17_021DB534
_021DB20A:
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DB1D0

	thumb_func_start MOD17_021DB210
MOD17_021DB210: ; 0x021DB210
	push {r4, r5, r6, lr}
	sub sp, #0x28
	add r6, r0, #0
	ldr r4, [r6]
	ldr r1, [r4, #0x10]
	cmp r1, #0
	bne _021DB220
	b _021DB38E
_021DB220:
	add r1, sp, #0x18
	str r1, [sp]
	add r1, sp, #0x24
	add r2, sp, #0x20
	add r3, sp, #0x1c
	bl MOD17_021DB588
	ldr r0, [r4, #4]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x24]
	bl MOD17_021DA26C
	add r5, r0, #0
	ldr r0, [r4, #4]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x24]
	bl MOD17_021DA26C
	add r5, r5, r0
	ldr r0, [r4, #4]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	bl MOD17_021DA26C
	add r5, r5, r0
	ldr r0, [r4, #4]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x20]
	bl MOD17_021DA26C
	add r0, r5, r0
	cmp r0, #4
	blt _021DB2C2
	ldr r2, [r4]
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x10]
	ldr r2, [r2, #0x30]
	bl MOD17_021DA0C4
	cmp r0, #0
	bne _021DB2AC
	mov r0, #0x1c
	ldrsh r0, [r4, r0]
	str r0, [sp, #0xc]
	mov r0, #0x1e
	ldrsh r0, [r4, r0]
	str r0, [sp, #8]
	ldr r0, _021DB394 ; =0x00000683
	bl PlaySE
	ldr r0, [r4, #0xc]
	ldr r2, _021DB398 ; =0x00000151
	mov r1, #0x1a
	mov r3, #3
	bl MOD17_021DCB48
	ldr r0, [r4, #0x10]
	mov r1, #4
	ldr r0, [r0, #4]
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x21
	ldrb r0, [r0]
	str r0, [sp, #4]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #8]
	add r0, r4, #0
	bl MOD17_021DB59C
	b _021DB388
_021DB2AC:
	ldr r0, [r4, #4]
	bl MOD17_021DA178
	bl MOD17_021D7A4C
	mov r0, #0
	str r0, [r4, #0x30]
	ldr r0, _021DB39C ; =0x000005EA
	bl PlaySE
	b _021DB388
_021DB2C2:
	ldr r0, [r4, #0x10]
	add r1, sp, #0x24
	ldr r5, [r0]
	add r0, sp, #0x18
	str r0, [sp]
	add r0, r6, #0
	add r2, sp, #0x20
	add r3, sp, #0x1c
	bl MOD17_021DB548
	ldr r0, [r4, #8]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x24]
	bl MOD17_021DA95C
	add r6, r0, #0
	ldr r0, [r4, #8]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x20]
	bl MOD17_021DA95C
	add r0, r6, r0
	cmp r0, #2
	bge _021DB340
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #1
	bne _021DB32C
	ldr r0, [r4, #0x10]
	add r1, sp, #0x14
	add r2, sp, #0x10
	bl MOD17_021DBC08
	bl MTRandom
	ldr r2, [sp, #0x14]
	mov r1, #0x6c
	sub r1, r1, r2
	bl _u32_div_f
	add r1, #0xa
	str r1, [sp, #0xc]
	bl MTRandom
	ldr r2, [sp, #0x10]
	mov r1, #0x7d
	sub r1, r1, r2
	bl _u32_div_f
	add r1, #0x12
	str r1, [sp, #8]
	b _021DB338
_021DB32C:
	mov r0, #0x1c
	ldrsh r0, [r4, r0]
	str r0, [sp, #0xc]
	mov r0, #0x1e
	ldrsh r0, [r4, r0]
	str r0, [sp, #8]
_021DB338:
	ldr r0, _021DB394 ; =0x00000683
	bl PlaySE
	b _021DB350
_021DB340:
	ldr r0, [r4, #0x10]
	add r1, sp, #0xc
	add r2, sp, #8
	bl MOD17_021DBBB8
	ldr r0, _021DB3A0 ; =0x000005EB
	bl PlaySE
_021DB350:
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #1
	bne _021DB36E
	ldr r0, [r4, #0x10]
	ldr r2, [r4, #8]
	ldr r0, [r0, #4]
	ldr r1, [r5]
	ldr r2, [r2, #4]
	bl MOD17_021DA608
	add r1, r4, #0
	add r1, #0x21
	strb r0, [r1]
_021DB36E:
	ldr r0, [r4, #0x10]
	mov r1, #4
	ldr r0, [r0, #4]
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x21
	ldrb r0, [r0]
	str r0, [sp, #4]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #8]
	add r0, r4, #0
	bl MOD17_021DB59C
_021DB388:
	add r0, r4, #0
	bl MOD17_021DB534
_021DB38E:
	add sp, #0x28
	pop {r4, r5, r6, pc}
	nop
_021DB394: .word 0x00000683
_021DB398: .word 0x00000151
_021DB39C: .word 0x000005EA
_021DB3A0: .word 0x000005EB
	thumb_func_end MOD17_021DB210

	thumb_func_start MOD17_021DB3A4
MOD17_021DB3A4: ; 0x021DB3A4
	push {r4, lr}
	ldr r2, [r0]
	ldr r0, [r2, #0x10]
	cmp r0, #0
	beq _021DB3C8
	ldr r3, _021DB3CC ; =gMain + 0x40
	ldr r1, _021DB3D0 ; =0x0000FFFF
	ldrh r4, [r3, #0x1c]
	cmp r4, r1
	beq _021DB3C8
	beq _021DB3C8
	ldrh r3, [r3, #0x1e]
	ldr r1, [r2, #0x14]
	ldr r2, [r2, #0x18]
	sub r1, r4, r1
	sub r2, r3, r2
	bl MOD17_021DBB68
_021DB3C8:
	pop {r4, pc}
	nop
_021DB3CC: .word gMain + 0x40
_021DB3D0: .word 0x0000FFFF
	thumb_func_end MOD17_021DB3A4

	thumb_func_start MOD17_021DB3D4
MOD17_021DB3D4: ; 0x021DB3D4
	push {r4, lr}
	ldr r4, [r0]
	ldr r1, [r4, #0x10]
	cmp r1, #0
	beq _021DB3FE
	ldr r0, [r4, #4]
	bl MOD17_021DA040
	ldr r0, [r4, #4]
	bl MOD17_021DA178
	bl MOD17_021D7A4C
	mov r0, #0
	str r0, [r4, #0x30]
	ldr r0, _021DB400 ; =0x000005EB
	bl PlaySE
	add r0, r4, #0
	bl MOD17_021DB534
_021DB3FE:
	pop {r4, pc}
	.align 2, 0
_021DB400: .word 0x000005EB
	thumb_func_end MOD17_021DB3D4

	thumb_func_start MOD17_021DB404
MOD17_021DB404: ; 0x021DB404
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldr r4, [r0]
	str r0, [sp]
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021DB49E
	ldr r1, _021DB4A4 ; =gMain + 0x40
	ldrh r2, [r1, #0x1c]
	ldr r1, _021DB4A8 ; =0x0000FFFF
	cmp r2, r1
	beq _021DB49E
	beq _021DB49E
	add r1, sp, #8
	add r2, sp, #4
	bl MOD17_021DBC20
	ldr r0, [r4, #0x10]
	add r1, sp, #0x10
	add r2, sp, #0xc
	bl MOD17_021DBC08
	ldr r0, _021DB4A4 ; =gMain + 0x40
	ldr r1, [r4, #0x14]
	ldrh r2, [r0, #0x1c]
	ldr r3, [sp, #0xc]
	sub r5, r2, r1
	ldrh r1, [r0, #0x1e]
	ldr r0, [r4, #0x18]
	ldr r2, [sp, #4]
	sub r6, r1, r0
	sub r3, r3, r2
	ldr r1, [sp, #8]
	ldr r0, [sp, #0x10]
	str r3, [sp, #0xc]
	sub r0, r0, r1
	add r3, r5, r1
	add r7, r6, r2
	str r0, [sp, #0x10]
	cmp r3, #0x8a
	bgt _021DB45C
	mov r0, #0x8a
	sub r5, r0, r1
	b _021DB466
_021DB45C:
	add r1, r5, r0
	cmp r1, #0xf6
	blt _021DB466
	mov r1, #0xf6
	sub r5, r1, r0
_021DB466:
	cmp r7, #0x12
	bgt _021DB470
	mov r0, #0x12
	sub r6, r0, r2
	b _021DB47C
_021DB470:
	ldr r1, [sp, #0xc]
	add r0, r6, r1
	cmp r0, #0x8f
	blt _021DB47C
	mov r0, #0x8f
	sub r6, r0, r1
_021DB47C:
	ldr r0, [sp]
	add r1, r5, #0
	add r2, r6, #0
	bl MOD17_021DB6B4
	ldr r0, [r4, #4]
	add r1, sp, #8
	add r2, sp, #4
	bl MOD17_021DA36C
	ldr r1, [sp, #8]
	ldr r2, [sp, #4]
	ldr r0, [sp]
	add r1, r5, r1
	add r2, r6, r2
	bl MOD17_021DB6B4
_021DB49E:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021DB4A4: .word gMain + 0x40
_021DB4A8: .word 0x0000FFFF
	thumb_func_end MOD17_021DB404

	thumb_func_start MOD17_021DB4AC
MOD17_021DB4AC: ; 0x021DB4AC
	push {r3, r4, r5, lr}
	ldr r4, [r0]
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021DB4D4
	ldr r0, [r0, #4]
	cmp r0, #1
	beq _021DB4C0
	bl GF_AssertFail
_021DB4C0:
	ldr r0, [r4, #0x10]
	ldr r5, [r0]
	ldr r0, [r4, #4]
	bl MOD17_021DA33C
	ldr r0, [r4, #4]
	ldr r1, [r5]
	mov r2, #0xe
	bl MOD17_021DA2F0
_021DB4D4:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DB4AC

	thumb_func_start MOD17_021DB4D8
MOD17_021DB4D8: ; 0x021DB4D8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	add r0, r4, #0
	add r1, sp, #4
	add r2, sp, #0
	add r7, r3, #0
	bl MOD17_021DBBB8
	str r4, [r5, #0x10]
	ldr r0, [sp, #4]
	strh r0, [r5, #0x1c]
	ldr r0, [sp]
	strh r0, [r5, #0x1e]
	add r0, r5, #0
	add r0, #0x20
	strb r6, [r0]
	ldr r0, [sp, #0x20]
	str r7, [r5, #0x14]
	str r0, [r5, #0x18]
	cmp r6, #0
	bne _021DB51A
	ldr r1, [r5, #0x10]
	ldr r0, [r5, #8]
	ldr r1, [r1, #4]
	bl MOD17_021DAA7C
	add r1, r5, #0
	add r1, #0x21
	strb r0, [r1]
	b _021DB522
_021DB51A:
	add r0, r5, #0
	mov r1, #0
	add r0, #0x21
	strb r1, [r0]
_021DB522:
	mov r0, #1
	str r0, [r5, #0x30]
	ldr r1, [sp, #0x24]
	add r0, r4, #0
	bl MOD17_021DBAD0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DB4D8

	thumb_func_start MOD17_021DB534
MOD17_021DB534: ; 0x021DB534
	mov r2, #0
	str r2, [r0, #0x10]
	strh r2, [r0, #0x1c]
	add r1, r0, #0
	strh r2, [r0, #0x1e]
	add r1, #0x20
	strb r2, [r1]
	add r0, #0x21
	strb r2, [r0]
	bx lr
	thumb_func_end MOD17_021DB534

	thumb_func_start MOD17_021DB548
MOD17_021DB548: ; 0x021DB548
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r4, [r0]
	add r5, r1, #0
	ldr r0, [r4, #0x10]
	add r6, r2, #0
	add r1, sp, #0xc
	add r2, sp, #8
	add r7, r3, #0
	bl MOD17_021DBC08
	ldr r0, [r4, #0x10]
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021DBBB8
	ldr r0, [sp]
	str r0, [r5]
	ldr r1, [sp]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [r6]
	ldr r0, [sp, #4]
	str r0, [r7]
	ldr r1, [sp, #4]
	ldr r0, [sp, #0xc]
	add r1, r1, r0
	ldr r0, [sp, #0x28]
	str r1, [r0]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DB548

	thumb_func_start MOD17_021DB588
MOD17_021DB588: ; 0x021DB588
	push {r3, r4, lr}
	sub sp, #4
	ldr r4, [sp, #0x10]
	str r4, [sp]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	bl MOD17_021DBC70
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD17_021DB588

	thumb_func_start MOD17_021DB59C
MOD17_021DB59C: ; 0x021DB59C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp]
	ldr r0, _021DB60C ; =MOD17_021DB610
	mov r1, #0x2c
	mov r2, #0
	mov r3, #0xd
	bl FUN_020061E8
	bl FUN_0201B6C8
	add r4, r0, #0
	ldr r0, [r5, #8]
	add r1, sp, #8
	str r0, [r4]
	ldr r0, [r5, #0x10]
	add r2, sp, #4
	str r0, [r4, #4]
	str r6, [r4, #0x20]
	ldr r0, [sp]
	str r7, [r4, #0x10]
	str r0, [r4, #0x14]
	ldr r0, [sp, #0x20]
	str r0, [r4, #0x18]
	ldr r0, [sp, #0x24]
	str r0, [r4, #0x1c]
	ldr r0, [r5, #8]
	add r0, #0x3c
	str r0, [r4, #0x24]
	add r0, r5, #0
	add r0, #0x30
	str r0, [r4, #0x28]
	ldr r0, [r5, #0x10]
	bl MOD17_021DBBB8
	ldr r1, [r4, #0x10]
	ldr r0, [sp, #8]
	sub r0, r1, r0
	add r1, r6, #0
	bl _s32_div_f
	str r0, [r4, #8]
	ldr r1, [r4, #0x14]
	ldr r0, [sp, #4]
	sub r0, r1, r0
	add r1, r6, #0
	bl _s32_div_f
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r5, #0x30]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DB60C: .word MOD17_021DB610
	thumb_func_end MOD17_021DB59C

	thumb_func_start MOD17_021DB610
MOD17_021DB610: ; 0x021DB610
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x24]
	ldr r0, [r0]
	cmp r0, #1
	beq _021DB67C
	ldr r0, [r4, #4]
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021DBBB8
	ldr r1, [sp, #4]
	ldr r0, [r4, #8]
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r1, [sp]
	ldr r0, [r4, #0xc]
	add r0, r1, r0
	str r0, [sp]
	ldr r0, [r4, #0x20]
	sub r0, r0, #1
	str r0, [r4, #0x20]
	ldr r0, [r4, #4]
	bpl _021DB674
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x14]
	bl MOD17_021DBB68
	ldr r0, [r4]
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x1c]
	ldr r3, [r4, #4]
	bl MOD17_021DA7E4
	ldr r0, [r4]
	bl MOD17_021DA844
	ldr r0, [r4, #0x28]
	ldr r0, [r0]
	cmp r0, #0
	bne _021DB66A
	bl MOD17_021D7A4C
_021DB66A:
	add r0, r5, #0
	bl FUN_0200621C
	add sp, #8
	pop {r3, r4, r5, pc}
_021DB674:
	ldr r1, [sp, #4]
	ldr r2, [sp]
	bl MOD17_021DBB68
_021DB67C:
	add sp, #8
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DB610

	thumb_func_start MOD17_021DB680
MOD17_021DB680: ; 0x021DB680
	push {r3, lr}
	ldr r3, [r0, #0x10]
	ldr r1, [r3, #4]
	cmp r1, #0
	bne _021DB69A
	ldr r3, [r3]
	ldr r0, [r0, #0xc]
	ldr r2, _021DB6B0 ; =0x00000152
	ldr r3, [r3]
	mov r1, #0x1a
	bl MOD17_021DCB48
	pop {r3, pc}
_021DB69A:
	cmp r1, #1
	bne _021DB6AE
	ldr r3, [r3]
	mov r2, #0x55
	ldr r0, [r0, #0xc]
	ldr r3, [r3]
	mov r1, #0x1a
	lsl r2, r2, #2
	bl MOD17_021DCB48
_021DB6AE:
	pop {r3, pc}
	.align 2, 0
_021DB6B0: .word 0x00000152
	thumb_func_end MOD17_021DB680

	thumb_func_start MOD17_021DB6B4
MOD17_021DB6B4: ; 0x021DB6B4
	push {r4, r5, r6, lr}
	ldr r4, [r0]
	add r5, r1, #0
	ldr r0, [r4, #0x10]
	add r6, r2, #0
	bl MOD17_021DBB68
	ldr r1, [r4, #0x24]
	ldr r2, [r4, #0x28]
	ldr r0, [r4, #4]
	sub r1, r5, r1
	sub r2, r6, r2
	bl MOD17_021DA134
	str r5, [r4, #0x24]
	str r6, [r4, #0x28]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DB6B4

	thumb_func_start MOD17_021DB6D8
MOD17_021DB6D8: ; 0x021DB6D8
	push {r3, r4, lr}
	sub sp, #4
	mov r2, #0
	str r2, [sp]
	add r4, r0, #0
	ldrh r0, [r1]
	ldrh r1, [r1, #2]
	mov r3, #0xe
	bl GfGfxLoader_LoadFromNarc
	add r1, r0, #0
	add r0, r4, #0
	mov r2, #0x76
	bl MOD17_021D7A2C
	ldr r0, [r0, #0x14]
	bl FUN_02008A74
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD17_021DB6D8

	thumb_func_start MOD17_021DB700
MOD17_021DB700: ; 0x021DB700
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r2, #0
	add r5, r0, #0
	add r7, r1, #0
	add r6, r3, #0
	add r0, r4, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #2
	bl FUN_02068B68
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	mov r2, #0xc0
	mov r3, #0x38
	bl FUN_020073A0
	str r0, [r5]
	add r0, r5, #0
	add r1, sp, #0x18
	add r2, sp, #0x14
	bl MOD17_021DB878
	ldr r1, [sp, #0x18]
	mov r2, #0x38
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	ldr r1, [sp, #0x14]
	str r0, [sp, #0x18]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	str r0, [sp, #0x14]
	sub r0, r2, r0
	strb r0, [r5, #4]
	ldr r0, [sp, #0x14]
	mov r1, #0xc0
	add r0, #0x38
	strb r0, [r5, #5]
	ldr r0, [sp, #0x18]
	sub r0, r1, r0
	strb r0, [r5, #6]
	ldr r0, [sp, #0x18]
	add r0, #0xc0
	strb r0, [r5, #7]
	ldr r0, [sp, #0x14]
	str r0, [sp]
	ldr r3, [sp, #0x18]
	add r0, r5, #4
	bl MOD17_021DB9B8
	add r0, r4, #0
	mov r1, #2
	bl FUN_02068E14
	mov r2, #0
	str r2, [sp]
	add r7, r0, #0
	ldrh r0, [r6]
	ldrh r1, [r6, #2]
	ldr r3, [sp, #0x30]
	bl GfGfxLoader_LoadFromNarc
	add r1, sp, #0x10
	add r6, r0, #0
	bl NNS_G2dGetUnpackedCharacterData
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0x14]
	bl FUN_02008A74
	ldr r1, [sp, #0x10]
	ldr r0, [r1, #0x14]
	ldrh r1, [r1, #2]
	lsl r1, r1, #3
	bl MOD17_021DB96C
	strb r0, [r5, #8]
	add r0, r6, #0
	strb r7, [r5, #9]
	bl FreeToHeap
	str r4, [r5, #0xc]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DB700

	thumb_func_start MOD17_021DB7C0
MOD17_021DB7C0: ; 0x021DB7C0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02007534
	mov r1, #0x10
	mov r0, #0
_021DB7CE:
	strb r0, [r4]
	add r4, r4, #1
	sub r1, r1, #1
	bne _021DB7CE
	pop {r4, pc}
	thumb_func_end MOD17_021DB7C0

	thumb_func_start MOD17_021DB7D8
MOD17_021DB7D8: ; 0x021DB7D8
	ldr r3, _021DB7E4 ; =FUN_02007558
	add r2, r1, #0
	ldr r0, [r0]
	mov r1, #2
	bx r3
	nop
_021DB7E4: .word FUN_02007558
	thumb_func_end MOD17_021DB7D8

	thumb_func_start MOD17_021DB7E8
MOD17_021DB7E8: ; 0x021DB7E8
	ldr r3, _021DB7F0 ; =FUN_0200782C
	ldr r0, [r0]
	mov r1, #2
	bx r3
	.align 2, 0
_021DB7F0: .word FUN_0200782C
	thumb_func_end MOD17_021DB7E8

	thumb_func_start MOD17_021DB7F4
MOD17_021DB7F4: ; 0x021DB7F4
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r2, #0
	add r5, r0, #0
	add r1, sp, #8
	add r2, sp, #4
	bl MOD17_021DB878
	ldr r0, [r5]
	mov r1, #0
	add r2, r4, #0
	bl FUN_02007558
	ldr r0, [r5]
	mov r1, #1
	add r2, r6, #0
	bl FUN_02007558
	ldr r1, [sp, #4]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r2, r0, #1
	ldr r1, [sp, #8]
	str r2, [sp, #4]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	str r0, [sp, #8]
	str r2, [sp]
	ldr r3, [sp, #8]
	add r0, r5, #4
	add r1, r4, #0
	add r2, r6, #0
	bl MOD17_021DB9B8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD17_021DB7F4

	thumb_func_start MOD17_021DB840
MOD17_021DB840: ; 0x021DB840
	ldr r3, _021DB848 ; =FUN_02020A40
	add r0, r0, #4
	bx r3
	nop
_021DB848: .word FUN_02020A40
	thumb_func_end MOD17_021DB840

	thumb_func_start MOD17_021DB84C
MOD17_021DB84C: ; 0x021DB84C
	ldr r3, _021DB854 ; =FUN_02020AE8
	add r0, r0, #4
	bx r3
	nop
_021DB854: .word FUN_02020AE8
	thumb_func_end MOD17_021DB84C

	thumb_func_start MOD17_021DB858
MOD17_021DB858: ; 0x021DB858
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	mov r1, #0
	add r6, r2, #0
	bl FUN_0200782C
	str r0, [r4]
	ldr r0, [r5]
	mov r1, #1
	bl FUN_0200782C
	str r0, [r6]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DB858

	thumb_func_start MOD17_021DB878
MOD17_021DB878: ; 0x021DB878
	mov r0, #0x50
	str r0, [r1]
	str r0, [r2]
	bx lr
	thumb_func_end MOD17_021DB878

	thumb_func_start MOD17_021DB880
MOD17_021DB880: ; 0x021DB880
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD17_021DB840
	cmp r0, #0
	bne _021DB89A
	add sp, #0x10
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021DB89A:
	add r0, r5, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021DB858
	add r0, r5, #0
	add r1, sp, #0xc
	add r2, sp, #8
	bl MOD17_021DB878
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #4]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	sub r1, r2, r0
	ldr r3, [sp, #8]
	ldr r0, [sp]
	lsr r2, r3, #0x1f
	add r2, r3, r2
	asr r2, r2, #1
	sub r0, r0, r2
	str r0, [sp]
	ldr r0, _021DB8F4 ; =gMain + 0x40
	str r1, [sp, #4]
	ldrh r2, [r0, #0x1c]
	mov r3, #0
	sub r1, r2, r1
	str r1, [r4]
	ldrh r1, [r0, #0x1e]
	ldr r0, [sp]
	sub r2, r1, r0
	str r2, [r6]
	ldr r1, [r4]
	add r0, r7, #0
	bl MOD17_021D7B0C
	cmp r0, #0
	bne _021DB8EE
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DB8EE:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DB8F4: .word gMain + 0x40
	thumb_func_end MOD17_021DB880

	thumb_func_start MOD17_021DB8F8
MOD17_021DB8F8: ; 0x021DB8F8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD17_021DB84C
	cmp r0, #0
	bne _021DB912
	add sp, #0x10
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021DB912:
	add r0, r5, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021DB858
	add r0, r5, #0
	add r1, sp, #0xc
	add r2, sp, #8
	bl MOD17_021DB878
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #4]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	sub r1, r2, r0
	ldr r3, [sp, #8]
	str r1, [sp, #4]
	lsr r2, r3, #0x1f
	add r2, r3, r2
	ldr r0, [sp]
	asr r2, r2, #1
	sub r0, r0, r2
	str r0, [sp]
	sub r2, r6, r0
	sub r1, r4, r1
	add r0, r7, #0
	mov r3, #0
	bl MOD17_021D7B0C
	cmp r0, #0
	bne _021DB958
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DB958:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DB8F8

	thumb_func_start MOD17_021DB960
MOD17_021DB960: ; 0x021DB960
	ldrb r3, [r0, #8]
	str r3, [r1]
	ldrb r0, [r0, #9]
	str r0, [r2]
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DB960

	thumb_func_start MOD17_021DB96C
MOD17_021DB96C: ; 0x021DB96C
	push {r4, r5, r6, r7}
	mov ip, r0
	add r7, r1, #0
	mov r2, #0
_021DB974:
	mov r3, #0
	add r4, r3, #0
_021DB978:
	add r1, r2, r4
	lsr r0, r1, #0x1f
	lsl r6, r1, #0x1f
	sub r6, r6, r0
	mov r5, #0x1f
	ror r6, r5
	add r5, r0, r6
	lsl r6, r5, #2
	mov r5, #0xf
	add r0, r1, r0
	lsl r5, r6
	asr r1, r0, #1
	mov r0, ip
	lsl r5, r5, #0x18
	ldrsb r0, [r0, r1]
	lsr r5, r5, #0x18
	tst r0, r5
	beq _021DB9A2
	add r0, r2, #0
	pop {r4, r5, r6, r7}
	bx lr
_021DB9A2:
	add r3, r3, #1
	add r4, r4, r7
	cmp r3, #0x50
	blt _021DB978
	add r2, r2, #1
	cmp r2, #0x50
	blt _021DB974
	mov r0, #0x50
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DB96C

	thumb_func_start MOD17_021DB9B8
MOD17_021DB9B8: ; 0x021DB9B8
	push {r3, r4}
	ldr r4, [sp, #8]
	sub r4, r2, r4
	bmi _021DB9C2
	b _021DB9C4
_021DB9C2:
	mov r4, #0
_021DB9C4:
	strb r4, [r0]
	ldr r4, [sp, #8]
	add r2, r2, r4
	cmp r2, #0xbf
	bgt _021DB9D0
	b _021DB9D2
_021DB9D0:
	mov r2, #0xbf
_021DB9D2:
	strb r2, [r0, #1]
	sub r2, r1, r3
	bmi _021DB9DA
	b _021DB9DC
_021DB9DA:
	mov r2, #0
_021DB9DC:
	add r1, r1, r3
	strb r2, [r0, #2]
	cmp r1, #0xff
	bgt _021DB9EA
	strb r1, [r0, #3]
	pop {r3, r4}
	bx lr
_021DB9EA:
	mov r1, #0xff
	strb r1, [r0, #3]
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DB9B8

	thumb_func_start MOD17_021DB9F4
MOD17_021DB9F4: ; 0x021DB9F4
	push {r4, r5, r6, lr}
	add r6, r1, #0
	lsl r4, r6, #4
	add r5, r0, #0
	add r0, r2, #0
	add r1, r4, #0
	bl AllocFromHeap
	str r0, [r5]
	cmp r0, #0
	bne _021DBA0E
	bl GF_AssertFail
_021DBA0E:
	ldr r0, [r5]
	mov r1, #0
	add r2, r4, #0
	bl memset
	str r6, [r5, #4]
	pop {r4, r5, r6, pc}
	thumb_func_end MOD17_021DB9F4

	thumb_func_start MOD17_021DBA1C
MOD17_021DBA1C: ; 0x021DBA1C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4]
	str r0, [r4, #4]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBA1C

	thumb_func_start MOD17_021DBA30
MOD17_021DBA30: ; 0x021DBA30
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r6, r1, #0
	add r7, r2, #0
	cmp r0, #0
	bne _021DBA42
	bl GF_AssertFail
_021DBA42:
	ldr r0, [r5, #4]
	cmp r0, #0
	bne _021DBA4C
	bl GF_AssertFail
_021DBA4C:
	ldr r2, [r5, #4]
	mov r4, #0
	cmp r2, #0
	ble _021DBA64
	ldr r1, [r5]
_021DBA56:
	ldr r0, [r1]
	cmp r0, #0
	beq _021DBA64
	add r4, r4, #1
	add r1, #0x10
	cmp r4, r2
	blt _021DBA56
_021DBA64:
	cmp r2, r4
	bgt _021DBA6C
	bl GF_AssertFail
_021DBA6C:
	ldr r0, [r5]
	lsl r1, r4, #4
	str r6, [r0, r1]
	ldr r0, [r5]
	add r0, r0, r1
	str r7, [r0, #4]
	ldr r0, [r5]
	add r0, r0, r1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBA30

	thumb_func_start MOD17_021DBA80
MOD17_021DBA80: ; 0x021DBA80
	mov r2, #0x10
	mov r1, #0
_021DBA84:
	strb r1, [r0]
	add r0, r0, #1
	sub r2, r2, #1
	bne _021DBA84
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DBA80

	thumb_func_start MOD17_021DBA90
MOD17_021DBA90: ; 0x021DBA90
	ldr r2, [r1, #8]
	str r2, [r0, #8]
	ldr r2, [r1, #8]
	str r0, [r2, #0xc]
	str r1, [r0, #0xc]
	str r0, [r1, #8]
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DBA90

	thumb_func_start MOD17_021DBAA0
MOD17_021DBAA0: ; 0x021DBAA0
	ldr r2, [r0, #8]
	ldr r1, [r0, #0xc]
	str r2, [r1, #8]
	ldr r1, [r0, #0xc]
	ldr r0, [r0, #8]
	str r1, [r0, #0xc]
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DBAA0

	thumb_func_start MOD17_021DBAB0
MOD17_021DBAB0: ; 0x021DBAB0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r4, [r6, #8]
	cmp r4, r6
	beq _021DBACE
_021DBABA:
	add r0, r4, #0
	ldr r5, [r4, #8]
	bl MOD17_021DBAA0
	add r0, r4, #0
	bl MOD17_021DBA80
	add r4, r5, #0
	cmp r5, r6
	bne _021DBABA
_021DBACE:
	pop {r4, r5, r6, pc}
	thumb_func_end MOD17_021DBAB0

	thumb_func_start MOD17_021DBAD0
MOD17_021DBAD0: ; 0x021DBAD0
	push {r3, lr}
	ldr r2, [r0, #4]
	ldr r0, [r0]
	cmp r2, #3
	bge _021DBAE0
	bl MOD17_021D766C
	pop {r3, pc}
_021DBAE0:
	bl MOD17_021DB7D8
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBAD0

	thumb_func_start MOD17_021DBAE8
MOD17_021DBAE8: ; 0x021DBAE8
	push {r3, lr}
	ldr r3, [r0, #4]
	ldr r0, [r0]
	cmp r3, #3
	bge _021DBB06
	mov r3, #0
	mvn r3, r3
	cmp r1, r3
	bne _021DBB00
	bl MOD17_021D7544
	pop {r3, pc}
_021DBB00:
	bl MOD17_021D75DC
	pop {r3, pc}
_021DBB06:
	mov r3, #0
	mvn r3, r3
	cmp r1, r3
	bne _021DBB14
	bl MOD17_021DB840
	pop {r3, pc}
_021DBB14:
	bl MOD17_021DB84C
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBAE8

	thumb_func_start MOD17_021DBB1C
MOD17_021DBB1C: ; 0x021DBB1C
	push {r4, lr}
	ldr r4, [r0, #4]
	cmp r4, #0
	bne _021DBB32
	ldr r0, [r0]
	ldr r4, [r0]
	lsl r4, r4, #2
	ldr r3, [r3, r4]
	bl MOD17_021D7554
	pop {r4, pc}
_021DBB32:
	cmp r4, #1
	bne _021DBB46
	ldr r0, [r0]
	ldr r4, [r0]
	add r4, #0x64
	lsl r4, r4, #2
	ldr r3, [r3, r4]
	bl MOD17_021D7554
	pop {r4, pc}
_021DBB46:
	cmp r4, #2
	ldr r0, [r0]
	bne _021DBB5A
	ldr r4, [r0]
	add r4, #0x64
	lsl r4, r4, #2
	ldr r3, [r3, r4]
	bl MOD17_021D7554
	pop {r4, pc}
_021DBB5A:
	mov r4, #0x76
	lsl r4, r4, #2
	ldr r3, [r3, r4]
	bl MOD17_021DB880
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBB1C

	thumb_func_start MOD17_021DBB68
MOD17_021DBB68: ; 0x021DBB68
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r1, #0
	ldr r1, [r0, #4]
	add r4, r2, #0
	cmp r1, #3
	bge _021DBB88
	lsl r1, r5, #0x10
	lsl r2, r4, #0x10
	ldr r0, [r0]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD17_021D75F4
	add sp, #8
	pop {r4, r5, r6, pc}
_021DBB88:
	ldr r6, [r0]
	add r1, sp, #4
	add r0, r6, #0
	add r2, sp, #0
	bl MOD17_021DB878
	ldr r1, [sp, #4]
	ldr r2, [sp]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r1, r0, #1
	lsr r0, r2, #0x1f
	add r0, r2, r0
	asr r2, r0, #1
	str r1, [sp, #4]
	str r2, [sp]
	add r0, r6, #0
	add r1, r5, r1
	add r2, r4, r2
	bl MOD17_021DB7F4
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBB68

	thumb_func_start MOD17_021DBBB8
MOD17_021DBBB8: ; 0x021DBBB8
	push {r4, r5, r6, lr}
	sub sp, #8
	ldr r3, [r0, #4]
	add r5, r1, #0
	add r4, r2, #0
	cmp r3, #3
	bge _021DBBD0
	ldr r0, [r0]
	bl MOD17_021D7600
	add sp, #8
	pop {r4, r5, r6, pc}
_021DBBD0:
	ldr r6, [r0]
	add r0, r6, #0
	bl MOD17_021DB858
	add r0, r6, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021DB878
	ldr r1, [sp, #4]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r2, r0, #1
	ldr r1, [sp]
	str r2, [sp, #4]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	str r0, [sp]
	ldr r0, [r5]
	sub r0, r0, r2
	str r0, [r5]
	ldr r1, [r4]
	ldr r0, [sp]
	sub r0, r1, r0
	str r0, [r4]
	add sp, #8
	pop {r4, r5, r6, pc}
	thumb_func_end MOD17_021DBBB8

	thumb_func_start MOD17_021DBC08
MOD17_021DBC08: ; 0x021DBC08
	push {r3, lr}
	ldr r3, [r0, #4]
	ldr r0, [r0]
	cmp r3, #3
	bge _021DBC18
	bl MOD17_021D7630
	pop {r3, pc}
_021DBC18:
	bl MOD17_021DB878
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBC08

	thumb_func_start MOD17_021DBC20
MOD17_021DBC20: ; 0x021DBC20
	push {r3, lr}
	ldr r3, [r0, #4]
	ldr r0, [r0]
	cmp r3, #3
	bge _021DBC30
	bl MOD17_021D7684
	pop {r3, pc}
_021DBC30:
	bl MOD17_021DB960
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBC20

	thumb_func_start MOD17_021DBC38
MOD17_021DBC38: ; 0x021DBC38
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r4, [r5, #8]
	add r6, r1, #0
	add r7, r2, #0
	cmp r4, r5
	beq _021DBC6A
_021DBC48:
	add r0, r4, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021DBBB8
	ldr r0, [sp, #4]
	add r1, r0, r6
	ldr r0, [sp]
	str r1, [sp, #4]
	add r2, r0, r7
	str r2, [sp]
	add r0, r4, #0
	bl MOD17_021DBB68
	ldr r4, [r4, #8]
	cmp r4, r5
	bne _021DBC48
_021DBC6A:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBC38

	thumb_func_start MOD17_021DBC70
MOD17_021DBC70: ; 0x021DBC70
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r1, #0
	add r6, r2, #0
	add r5, r0, #0
	add r1, sp, #0x14
	add r2, sp, #0x10
	add r7, r3, #0
	bl MOD17_021DBC08
	add r0, r5, #0
	add r1, sp, #0xc
	add r2, sp, #8
	bl MOD17_021DBBB8
	add r0, r5, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021DBC20
	ldr r1, [sp, #8]
	ldr r0, [sp]
	add r0, r1, r0
	str r0, [r4]
	ldr r1, [sp, #8]
	ldr r0, [sp, #0x10]
	add r1, r1, r0
	ldr r0, [sp]
	sub r0, r1, r0
	str r0, [r6]
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #4]
	add r0, r1, r0
	str r0, [r7]
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x14]
	add r1, r1, r0
	ldr r0, [sp, #4]
	sub r1, r1, r0
	ldr r0, [sp, #0x30]
	str r1, [r0]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBC70

	thumb_func_start MOD17_021DBCC8
MOD17_021DBCC8: ; 0x021DBCC8
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r4, r2, #0
	add r6, r0, #0
	add r1, sp, #0xc
	add r2, sp, #8
	bl MOD17_021DBC08
	add r0, r6, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD17_021DBBB8
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #4]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	add r0, r2, r0
	str r0, [r5]
	ldr r1, [sp, #8]
	ldr r2, [sp]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	add r0, r2, r0
	str r0, [r4]
	add sp, #0x10
	pop {r4, r5, r6, pc}
	thumb_func_end MOD17_021DBCC8

	thumb_func_start MOD17_021DBD04
MOD17_021DBD04: ; 0x021DBD04
	add r2, r0, #0
	ldr r0, [r1]
	str r0, [r2]
	ldr r3, [r1, #0x14]
	asr r0, r3, #2
	lsr r0, r0, #0x1d
	add r0, r3, r0
	asr r0, r0, #3
	str r0, [r2, #0xc]
	ldr r3, [r1, #0x18]
	asr r0, r3, #2
	lsr r0, r0, #0x1d
	add r0, r3, r0
	asr r0, r0, #3
	str r0, [r2, #0x10]
	ldr r0, [r1, #0x1c]
	ldr r3, _021DBD48 ; =MOD17_021DBEE8
	str r0, [r2, #0x1c]
	ldr r0, [r1, #0x24]
	str r0, [r2, #0x20]
	ldr r0, [r1, #0x20]
	str r0, [r2, #0x24]
	ldr r0, [r1, #0x28]
	str r0, [r2, #0x28]
	ldr r0, [r1, #4]
	str r0, [r2, #4]
	ldr r0, [r1, #0x10]
	str r0, [r2, #8]
	add r0, r1, #0
	add r1, r2, #0
	add r1, #0x14
	add r2, #0x18
	bx r3
	nop
_021DBD48: .word MOD17_021DBEE8
	thumb_func_end MOD17_021DBD04

	thumb_func_start MOD17_021DBD4C
MOD17_021DBD4C: ; 0x021DBD4C
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x1c]
	ldr r0, [r4]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl BgClearTilemapBufferAndCommit
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x2c
	bl memset
	pop {r4, pc}
	thumb_func_end MOD17_021DBD4C

	thumb_func_start MOD17_021DBD68
MOD17_021DBD68: ; 0x021DBD68
	ldr r2, [r1]
	str r2, [r0]
	ldr r2, [r1, #4]
	str r2, [r0, #4]
	ldr r2, [r1, #8]
	str r2, [r0, #8]
	mov r2, #0
	str r2, [r0, #0xc]
	str r2, [r0, #0x10]
	ldr r1, [r1, #0xc]
	str r1, [r0, #0x14]
	bx lr
	thumb_func_end MOD17_021DBD68

	thumb_func_start MOD17_021DBD80
MOD17_021DBD80: ; 0x021DBD80
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	add r1, r0, r1
	str r1, [r5, #0xc]
	ldr r0, [r5, #8]
	cmp r1, r0
	ble _021DBDE4
	mov r2, #0
	str r2, [r5, #0xc]
	ldr r0, [r5, #0x10]
	cmp r0, #0
	bne _021DBDA4
	ldr r1, [r5, #4]
	mov r0, #1
	str r0, [r5, #0x10]
	b _021DBDAA
_021DBDA4:
	ldr r0, [r5]
	ldr r1, [r0, #8]
	str r2, [r5, #0x10]
_021DBDAA:
	ldr r0, [r5, #0x14]
	mov r2, #0
	str r0, [sp]
	ldr r0, [r5]
	add r3, sp, #0x14
	ldr r0, [r0, #4]
	bl GfGfxLoader_GetScrnData
	ldr r3, [r5]
	add r4, r0, #0
	ldr r0, [r3, #0x18]
	str r0, [sp]
	ldr r0, [r3, #0xc]
	str r0, [sp, #4]
	ldr r0, [r3, #0x10]
	str r0, [sp, #8]
	ldr r0, [r3, #0x28]
	str r0, [sp, #0xc]
	ldr r0, [r3, #0x20]
	str r0, [sp, #0x10]
	ldr r0, [r3]
	ldr r1, [r3, #0x1c]
	ldr r2, [sp, #0x14]
	ldr r3, [r3, #0x14]
	bl MOD17_021DC004
	add r0, r4, #0
	bl FreeToHeap
_021DBDE4:
	add sp, #0x18
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DBD80

	thumb_func_start MOD17_021DBDE8
MOD17_021DBDE8: ; 0x021DBDE8
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r1, [r5]
	ldr r0, [r5, #0x14]
	mov r2, #0
	str r0, [sp]
	ldr r0, [r1, #4]
	ldr r1, [r1, #8]
	add r3, sp, #0x14
	bl GfGfxLoader_GetScrnData
	ldr r3, [r5]
	add r4, r0, #0
	ldr r0, [r3, #0x18]
	str r0, [sp]
	ldr r0, [r3, #0xc]
	str r0, [sp, #4]
	ldr r0, [r3, #0x10]
	str r0, [sp, #8]
	ldr r0, [r3, #0x28]
	str r0, [sp, #0xc]
	ldr r0, [r3, #0x20]
	str r0, [sp, #0x10]
	ldr r0, [r3]
	ldr r1, [r3, #0x1c]
	ldr r2, [sp, #0x14]
	ldr r3, [r3, #0x14]
	bl MOD17_021DC004
	add r0, r4, #0
	bl FreeToHeap
	mov r1, #0x18
	mov r0, #0
_021DBE2E:
	strb r0, [r5]
	add r5, r5, #1
	sub r1, r1, #1
	bne _021DBE2E
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBDE8

	thumb_func_start MOD17_021DBE3C
MOD17_021DBE3C: ; 0x021DBE3C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	add r5, r1, #0
	str r2, [sp]
	str r3, [sp, #4]
	ldr r0, _021DBEC4 ; =MOD17_021DBF94
	mov r1, #0x4c
	mov r2, #0
	mov r3, #0xd
	bl FUN_020061E8
	bl FUN_0201B6C8
	add r4, r0, #0
	str r6, [r4]
	add r7, r5, #0
	add r3, r4, #4
	mov r2, #6
_021DBE62:
	ldmia r7!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021DBE62
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x20]
	str r0, [r4, #0x34]
	ldr r0, [sp]
	str r1, [r4, #0x38]
	bl _s32_div_f
	str r0, [r4, #0x3c]
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x20]
	bl _s32_div_f
	str r0, [r4, #0x40]
	ldr r0, [r6]
	ldr r1, [r6, #0x1c]
	bl Bg_GetXpos
	str r0, [r4, #0x44]
	ldr r0, [r6]
	ldr r1, [r6, #0x1c]
	bl Bg_GetYpos
	str r0, [r4, #0x48]
	mov r0, #0x80
	str r0, [r5, #0x28]
	mov r0, #5
	str r0, [r5, #0x24]
	ldr r1, [r5, #0x14]
	ldr r0, [sp]
	sub r0, r1, r0
	str r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	ldr r0, [sp, #4]
	sub r0, r1, r0
	str r0, [r5, #0x18]
	mov r0, #0xe
	mov r1, #0
	str r0, [r5, #0x2c]
	add r0, r5, #0
	add r2, r1, #0
	bl MOD17_021DBEE8
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DBEC4: .word MOD17_021DBF94
	thumb_func_end MOD17_021DBE3C

	thumb_func_start MOD17_021DBEC8
MOD17_021DBEC8: ; 0x021DBEC8
	push {r3, r4}
	ldr r2, [r0, #8]
	add r0, #0xc
	lsr r4, r2, #1
	mov r3, #0
	cmp r4, #0
	ble _021DBEE4
_021DBED6:
	ldrh r2, [r0]
	add r3, r3, #1
	add r2, r2, r1
	strh r2, [r0]
	add r0, r0, #2
	cmp r3, r4
	blt _021DBED6
_021DBEE4:
	pop {r3, r4}
	bx lr
	thumb_func_end MOD17_021DBEC8

	thumb_func_start MOD17_021DBEE8
MOD17_021DBEE8: ; 0x021DBEE8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5, #0x14]
	add r6, r2, #0
	asr r0, r1, #2
	lsr r0, r0, #0x1d
	add r0, r1, r0
	asr r0, r0, #3
	ldr r1, [r5, #0x18]
	str r0, [sp, #0x18]
	asr r0, r1, #2
	lsr r0, r0, #0x1d
	add r0, r1, r0
	asr r0, r0, #3
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x28]
	str r0, [sp]
	ldr r0, [r5, #0x2c]
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	ldr r1, [r5, #8]
	ldr r2, [r5]
	ldr r3, [r5, #0x1c]
	bl MOD17_021DC084
	ldr r0, [r5, #0x1c]
	cmp r0, #4
	bge _021DBF28
	mov r2, #0
	b _021DBF2A
_021DBF28:
	mov r2, #4
_021DBF2A:
	ldr r0, [r5, #0x20]
	lsl r0, r0, #5
	str r0, [sp]
	ldr r0, [r5, #0x2c]
	str r0, [sp, #4]
	ldr r3, [r5, #0x24]
	ldr r0, [r5, #4]
	ldr r1, [r5, #0xc]
	lsl r3, r3, #5
	bl MOD17_021DC0D4
	ldr r0, [r5, #0x2c]
	mov r2, #0
	str r0, [sp]
	ldr r0, [r5, #4]
	ldr r1, [r5, #0x10]
	add r3, sp, #0x24
	bl GfGfxLoader_GetScrnData
	ldr r2, [sp, #0x24]
	str r0, [sp, #0x20]
	ldrh r0, [r2]
	lsr r7, r0, #3
	ldrh r0, [r2, #2]
	add r3, r7, #0
	lsr r0, r0, #3
	str r0, [sp, #0x1c]
	str r0, [sp]
	ldr r0, [sp, #0x18]
	str r0, [sp, #4]
	ldr r0, [sp, #0x14]
	str r0, [sp, #8]
	ldr r0, [r5, #0x28]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x24]
	str r0, [sp, #0x10]
	ldr r0, [r5]
	ldr r1, [r5, #0x1c]
	bl MOD17_021DC004
	ldr r0, [sp, #0x20]
	bl FreeToHeap
	cmp r4, #0
	beq _021DBF86
	str r7, [r4]
_021DBF86:
	cmp r6, #0
	beq _021DBF8E
	ldr r0, [sp, #0x1c]
	str r0, [r6]
_021DBF8E:
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DBEE8

	thumb_func_start MOD17_021DBF94
MOD17_021DBF94: ; 0x021DBF94
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x38]
	sub r0, r0, #1
	str r0, [r4, #0x38]
	ldr r1, [r4]
	bmi _021DBFC8
	ldr r0, [r1]
	ldr r1, [r1, #0x1c]
	ldr r3, [r4, #0x3c]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	mov r2, #2
	bl ScheduleSetBgPosText
	ldr r1, [r4]
	ldr r3, [r4, #0x40]
	ldr r0, [r1]
	ldr r1, [r1, #0x1c]
	mov r2, #5
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl ScheduleSetBgPosText
	pop {r3, r4, r5, pc}
_021DBFC8:
	ldr r0, [r1]
	ldr r1, [r1, #0x1c]
	ldr r3, [r4, #0x44]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	mov r2, #0
	bl ScheduleSetBgPosText
	ldr r1, [r4]
	ldr r3, [r4, #0x48]
	ldr r0, [r1]
	ldr r1, [r1, #0x1c]
	mov r2, #3
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl ScheduleSetBgPosText
	ldr r0, [r4]
	add r1, r4, #4
	bl MOD17_021DBD04
	ldr r1, [r4, #0x34]
	cmp r1, #0
	beq _021DBFFC
	mov r0, #1
	str r0, [r1]
_021DBFFC:
	add r0, r5, #0
	bl FUN_0200621C
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DBF94

	thumb_func_start MOD17_021DC004
MOD17_021DC004: ; 0x021DC004
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r1, #0
	add r4, r2, #0
	add r7, r0, #0
	ldr r1, [sp, #0x3c]
	add r0, r4, #0
	add r6, r3, #0
	bl MOD17_021DBEC8
	ldr r1, [sp, #0x30]
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	str r0, [sp]
	ldr r3, [sp, #0x38]
	str r2, [sp, #4]
	add r4, #0xc
	lsl r3, r3, #0x18
	str r4, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	str r2, [sp, #0x18]
	ldr r2, [sp, #0x34]
	lsl r1, r5, #0x18
	lsl r2, r2, #0x18
	add r0, r7, #0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl CopyToBgTilemapRect
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #0x30]
	ldr r2, [sp, #0x34]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r0, [sp, #0x40]
	ldr r3, [sp, #0x38]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r1, r5, #0x18
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	str r0, [sp, #8]
	add r0, r7, #0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl BgTilemapRectChangePalette
	lsl r1, r5, #0x18
	add r0, r7, #0
	lsr r1, r1, #0x18
	bl ScheduleBgTilemapBufferTransfer
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DC004

	thumb_func_start MOD17_021DC084
MOD17_021DC084: ; 0x021DC084
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	str r1, [sp, #4]
	ldr r0, [sp, #0x24]
	mov r1, #0x14
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	add r2, r4, #0
	mov r1, #0x14
	mov r0, #0
_021DC0A0:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _021DC0A0
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #4]
	str r0, [sp]
	add r0, r7, #0
	mov r2, #0
	add r3, r4, #4
	bl GfGfxLoader_GetCharData
	str r0, [r4, #8]
	str r5, [r4]
	ldr r0, [sp, #0x20]
	str r6, [r4, #0xc]
	str r0, [r4, #0x10]
	ldr r0, _021DC0D0 ; =MOD17_021DC11C
	add r1, r4, #0
	mov r2, #0x80
	bl FUN_0200CA98
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DC0D0: .word MOD17_021DC11C
	thumb_func_end MOD17_021DC084

	thumb_func_start MOD17_021DC0D4
MOD17_021DC0D4: ; 0x021DC0D4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	str r1, [sp]
	ldr r0, [sp, #0x1c]
	mov r1, #0x14
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	add r2, r4, #0
	mov r1, #0x14
	mov r0, #0
_021DC0EE:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _021DC0EE
	ldr r1, [sp]
	ldr r3, [sp, #0x1c]
	add r0, r7, #0
	add r2, r4, #0
	bl GfGfxLoader_GetPlttData
	str r0, [r4, #4]
	str r5, [r4, #8]
	ldr r0, [sp, #0x18]
	str r6, [r4, #0xc]
	str r0, [r4, #0x10]
	ldr r0, _021DC118 ; =MOD17_021DC158
	add r1, r4, #0
	mov r2, #0x80
	bl FUN_0200CA98
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DC118: .word MOD17_021DC158
	thumb_func_end MOD17_021DC0D4

	thumb_func_start MOD17_021DC11C
MOD17_021DC11C: ; 0x021DC11C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4, #4]
	add r5, r0, #0
	ldr r0, [r1, #0x14]
	ldr r1, [r1, #0x10]
	bl DC_FlushRange
	ldr r3, [r4, #4]
	ldr r0, [r4, #0x10]
	str r0, [sp]
	ldr r1, [r4, #0xc]
	ldr r2, [r3, #0x14]
	lsl r1, r1, #0x18
	ldr r0, [r4]
	ldr r3, [r3, #0x10]
	lsr r1, r1, #0x18
	bl BG_LoadCharTilesData
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #8]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC11C

	thumb_func_start MOD17_021DC158
MOD17_021DC158: ; 0x021DC158
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	ldr r1, [r4, #0x10]
	ldr r0, [r0, #0xc]
	bl DC_FlushRange
	ldr r0, [r4, #8]
	cmp r0, #0
	bne _021DC17C
	ldr r0, [r4]
	ldr r1, [r4, #0xc]
	ldr r0, [r0, #0xc]
	ldr r2, [r4, #0x10]
	bl GX_LoadBGPltt
	b _021DC18C
_021DC17C:
	cmp r0, #4
	bne _021DC18C
	ldr r0, [r4]
	ldr r1, [r4, #0xc]
	ldr r0, [r0, #0xc]
	ldr r2, [r4, #0x10]
	bl GXS_LoadBGPltt
_021DC18C:
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #4]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DC158

	thumb_func_start MOD17_021DC1A0
MOD17_021DC1A0: ; 0x021DC1A0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	cmp r5, #0
	bne _021DC1AE
	bl GF_AssertFail
_021DC1AE:
	cmp r4, #0
	bne _021DC1B6
	bl GF_AssertFail
_021DC1B6:
	ldr r0, [r4]
	bl FUN_0201FE94
	str r0, [r5]
	cmp r0, #0
	bne _021DC1C6
	bl GF_AssertFail
_021DC1C6:
	ldr r0, [r4, #0xc]
	str r0, [r5, #4]
	ldr r0, [r4, #8]
	str r0, [r5, #8]
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021DC1D8
	str r0, [r5, #0xc]
	pop {r3, r4, r5, pc}
_021DC1D8:
	ldr r0, _021DC1E0 ; =MOD17_021DC2DC
	str r0, [r5, #0xc]
	pop {r3, r4, r5, pc}
	nop
_021DC1E0: .word MOD17_021DC2DC
	thumb_func_end MOD17_021DC1A0

	thumb_func_start MOD17_021DC1E4
MOD17_021DC1E4: ; 0x021DC1E4
	push {r3, r4, r5, lr}
	sub sp, #0x30
	add r4, r1, #0
	add r5, r0, #0
	bl MOD17_021DC1A0
	ldr r0, [r4, #0x14]
	str r0, [sp]
	ldr r0, [r4, #0x10]
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r0, [r0]
	str r0, [sp, #8]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0xc]
	ldr r0, [r5]
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x24]
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x1c]
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x20]
	str r0, [sp, #0x1c]
	mov r0, #0
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
	ldr r0, [r4]
	ldr r0, [r0, #0x28]
	str r0, [sp, #0x28]
	ldr r0, [r4]
	ldr r0, [r0, #0x2c]
	str r0, [sp, #0x2c]
	add r0, sp, #0
	bl FUN_020117E8
	str r0, [r5, #0x10]
	add sp, #0x30
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DC1E4

	thumb_func_start MOD17_021DC230
MOD17_021DC230: ; 0x021DC230
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_0201FFC8
	mov r1, #0x10
	mov r0, #0
_021DC23E:
	strb r0, [r4]
	add r4, r4, #1
	sub r1, r1, #1
	bne _021DC23E
	pop {r4, pc}
	thumb_func_end MOD17_021DC230

	thumb_func_start MOD17_021DC248
MOD17_021DC248: ; 0x021DC248
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021DC230
	ldr r0, [r4, #0x10]
	bl FUN_02011870
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x20
	bl memset
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC248

	thumb_func_start MOD17_021DC264
MOD17_021DC264: ; 0x021DC264
	push {r3, lr}
	ldr r2, [r0, #4]
	cmp r1, r2
	bne _021DC272
	ldr r1, [r0, #8]
	ldr r2, [r0, #0xc]
	blx r2
_021DC272:
	pop {r3, pc}
	thumb_func_end MOD17_021DC264

	thumb_func_start MOD17_021DC274
MOD17_021DC274: ; 0x021DC274
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	add r6, r2, #0
	mov r4, #2
	add r5, #0x20
_021DC280:
	cmp r4, r7
	beq _021DC28C
	add r0, r5, #0
	bl MOD17_021DC2EC
	b _021DC2B0
_021DC28C:
	cmp r6, #0
	bne _021DC29E
	add r0, r5, #0
	bl MOD17_021DC2F8
	ldr r0, _021DC2BC ; =0x0000067D
	bl PlaySE
	b _021DC2B0
_021DC29E:
	cmp r6, #2
	bne _021DC2AA
	add r0, r5, #0
	bl MOD17_021DC2E0
	b _021DC2B0
_021DC2AA:
	add r0, r5, #0
	bl MOD17_021DC2F8
_021DC2B0:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #3
	ble _021DC280
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DC2BC: .word 0x0000067D
	thumb_func_end MOD17_021DC274

	thumb_func_start MOD17_021DC2C0
MOD17_021DC2C0: ; 0x021DC2C0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r5, #0
	bne _021DC2D2
	bl GF_AssertFail
_021DC2D2:
	str r7, [r5, #4]
	str r6, [r5, #8]
	str r4, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC2C0

	thumb_func_start MOD17_021DC2DC
MOD17_021DC2DC: ; 0x021DC2DC
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DC2DC

	thumb_func_start MOD17_021DC2E0
MOD17_021DC2E0: ; 0x021DC2E0
	ldr r3, _021DC2E8 ; =FUN_02020208
	ldr r0, [r0]
	mov r1, #2
	bx r3
	.align 2, 0
_021DC2E8: .word FUN_02020208
	thumb_func_end MOD17_021DC2E0

	thumb_func_start MOD17_021DC2EC
MOD17_021DC2EC: ; 0x021DC2EC
	ldr r3, _021DC2F4 ; =FUN_02020208
	ldr r0, [r0]
	mov r1, #0
	bx r3
	.align 2, 0
_021DC2F4: .word FUN_02020208
	thumb_func_end MOD17_021DC2EC

	thumb_func_start MOD17_021DC2F8
MOD17_021DC2F8: ; 0x021DC2F8
	ldr r3, _021DC300 ; =FUN_02020208
	ldr r0, [r0]
	mov r1, #1
	bx r3
	.align 2, 0
_021DC300: .word FUN_02020208
	thumb_func_end MOD17_021DC2F8

	thumb_func_start MOD17_021DC304
MOD17_021DC304: ; 0x021DC304
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #1
	mov r1, #0xd
	bl FUN_02011744
	str r0, [r5, #0x64]
	add r0, r4, #0
	bl MOD17_021DC760
	mov r0, #0x90
	str r0, [sp]
	mov r0, #0x28
	str r0, [sp, #4]
	mov r0, #0x20
	str r0, [sp, #8]
	add r0, r5, #0
	mov r1, #0
	add r2, r4, #0
	mov r3, #0x30
	bl MOD17_021DC628
	mov r0, #0x28
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x6c
	mov r1, #0
	mov r2, #0x30
	mov r3, #0x98
	bl MOD17_021DC748
	mov r0, #0x90
	str r0, [sp]
	mov r0, #0x28
	str r0, [sp, #4]
	mov r0, #0x20
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0x10
	mov r1, #1
	add r2, r4, #0
	mov r3, #8
	bl MOD17_021DC628
	mov r0, #0x28
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x6c
	mov r1, #1
	mov r2, #8
	mov r3, #0x98
	bl MOD17_021DC748
	mov r0, #0x90
	str r0, [sp]
	mov r0, #0x2a
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0x20
	mov r1, #2
	add r2, r4, #0
	mov r3, #0x60
	bl MOD17_021DC628
	mov r0, #0x2a
	str r0, [sp]
	mov r0, #0x22
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x6c
	mov r1, #2
	mov r2, #0x60
	mov r3, #0x9c
	bl MOD17_021DC748
	mov r0, #0x90
	str r0, [sp]
	mov r0, #0x2a
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0x30
	mov r1, #3
	add r2, r4, #0
	mov r3, #0x88
	bl MOD17_021DC628
	mov r0, #0x2a
	str r0, [sp]
	mov r0, #0x22
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x6c
	mov r1, #3
	mov r2, #0x88
	mov r3, #0x9c
	bl MOD17_021DC748
	mov r0, #2
	mov r1, #0xe
	bl FUN_02002C50
	mov r0, #9
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	ldr r2, _021DC460 ; =0x00000151
	add r0, r4, #0
	mov r1, #0x1a
	mov r3, #0
	bl MOD17_021DC880
	add r6, r0, #0
	str r6, [sp]
	mov r0, #0xb8
	str r0, [sp, #4]
	mov r0, #0x90
	str r0, [sp, #8]
	mov r0, #0x48
	str r0, [sp, #0xc]
	mov r0, #0x2a
	str r0, [sp, #0x10]
	add r0, r5, #0
	ldr r3, [r5, #0x64]
	add r0, #0x40
	mov r1, #4
	add r2, r4, #0
	bl MOD17_021DC698
	mov r0, #0x48
	str r0, [sp]
	mov r0, #0x22
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x6c
	mov r1, #4
	mov r2, #0xb8
	mov r3, #0x9c
	bl MOD17_021DC748
	add r0, r6, #0
	bl MOD17_021DC8F8
	mov r0, #2
	bl FUN_02002CF8
	mov r0, #1
	str r0, [r5, #0x60]
	add r0, r4, #0
	bl MOD17_021DC7E0
	add r0, r5, #0
	add r0, #0x20
	bl MOD17_021DC2E0
	mov r0, #0xd
	str r0, [sp]
	add r0, r5, #0
	ldr r2, _021DC464 ; =MOD17_021DC570
	add r0, #0x6c
	mov r1, #5
	add r3, r5, #0
	bl FUN_020220C4
	str r0, [r5, #0x68]
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DC460: .word 0x00000151
_021DC464: .word MOD17_021DC570
	thumb_func_end MOD17_021DC304

	thumb_func_start MOD17_021DC468
MOD17_021DC468: ; 0x021DC468
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r4, #0
_021DC470:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD17_021D79D8
	add r0, r5, #0
	add r1, r4, #0
	bl MOD17_021D79EC
	add r0, r4, #0
	bl FUN_0201D324
	add r4, r4, #1
	cmp r4, #5
	blt _021DC470
	mov r0, #0
	bl FUN_0201E1C8
	mov r0, #1
	bl FUN_0201E1C8
	mov r5, #0
	add r4, r6, #0
_021DC49C:
	add r0, r4, #0
	bl MOD17_021DC230
	add r5, r5, #1
	add r4, #0x10
	cmp r5, #4
	blt _021DC49C
	add r0, r6, #0
	add r0, #0x54
	bl FUN_0201D5E8
	add r0, r6, #0
	add r0, #0x40
	bl MOD17_021DC248
	ldr r0, [r6, #0x64]
	bl FUN_020117BC
	ldr r0, [r6, #0x68]
	bl FUN_0202212C
	mov r0, #0
	str r0, [r6, #0x68]
	pop {r4, r5, r6, pc}
	thumb_func_end MOD17_021DC468

	thumb_func_start MOD17_021DC4CC
MOD17_021DC4CC: ; 0x021DC4CC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x68]
	cmp r0, #0
	bne _021DC4DA
	bl GF_AssertFail
_021DC4DA:
	ldr r0, [r4, #0x68]
	bl FUN_02022144
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC4CC

	thumb_func_start MOD17_021DC4E4
MOD17_021DC4E4: ; 0x021DC4E4
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x40
	mov r1, #3
	bl MOD17_021DC808
	add r0, r4, #0
	add r0, #0x40
	mov r1, #3
	bl MOD17_021DC82C
	add r0, r4, #0
	mov r1, #2
	mov r2, #3
	bl MOD17_021DC274
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC4E4

	thumb_func_start MOD17_021DC508
MOD17_021DC508: ; 0x021DC508
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r6, r1, #0
	add r7, r2, #0
	mov r4, #0
	add r5, r0, #0
_021DC514:
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	bl MOD17_021DC904
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #4
	blt _021DC514
	ldr r0, [sp]
	add r1, r6, #0
	add r0, #0x40
	add r2, r7, #0
	str r0, [sp]
	bl MOD17_021DC940
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC508

	thumb_func_start MOD17_021DC538
MOD17_021DC538: ; 0x021DC538
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r5, #0
	bne _021DC54A
	bl GF_AssertFail
_021DC54A:
	cmp r4, #4
	bge _021DC55E
	lsl r0, r4, #4
	ldr r3, [sp, #0x18]
	add r0, r5, r0
	add r1, r6, #0
	add r2, r7, #0
	bl MOD17_021DC2C0
	pop {r3, r4, r5, r6, r7, pc}
_021DC55E:
	add r5, #0x40
	ldr r3, [sp, #0x18]
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	bl MOD17_021DC2C0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC538

	thumb_func_start MOD17_021DC570
MOD17_021DC570: ; 0x021DC570
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	cmp r6, #4
	bhi _021DC618
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DC588: ; jump table
	.short _021DC592 - _021DC588 - 2 ; case 0
	.short _021DC5AE - _021DC588 - 2 ; case 1
	.short _021DC5D0 - _021DC588 - 2 ; case 2
	.short _021DC5D0 - _021DC588 - 2 ; case 3
	.short _021DC5E6 - _021DC588 - 2 ; case 4
_021DC592:
	add r0, r4, #0
	bl MOD17_021DC808
	ldr r1, _021DC620 ; =0x00000681
	add r0, r4, #0
	mov r2, #0
	add r3, r5, #0
	bl MOD17_021DC870
	add r0, r4, #0
	add r1, r5, #0
	bl MOD17_021DC264
	pop {r4, r5, r6, pc}
_021DC5AE:
	add r0, r4, #0
	add r0, #0x10
	bl MOD17_021DC808
	add r0, r4, #0
	ldr r1, _021DC620 ; =0x00000681
	add r0, #0x10
	mov r2, #0
	add r3, r5, #0
	bl MOD17_021DC870
	add r4, #0x10
	add r0, r4, #0
	add r1, r5, #0
	bl MOD17_021DC264
	pop {r4, r5, r6, pc}
_021DC5D0:
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	bl MOD17_021DC274
	lsl r0, r6, #4
	add r0, r4, r0
	add r1, r5, #0
	bl MOD17_021DC264
	pop {r4, r5, r6, pc}
_021DC5E6:
	ldr r0, [r4, #0x60]
	cmp r0, #1
	bne _021DC61C
	add r0, r4, #0
	add r0, #0x40
	bl MOD17_021DC808
	add r0, r4, #0
	add r0, #0x40
	add r1, r5, #0
	bl MOD17_021DC82C
	add r0, r4, #0
	ldr r1, _021DC624 ; =0x000005E2
	add r0, #0x40
	mov r2, #0
	add r3, r5, #0
	bl MOD17_021DC870
	add r4, #0x40
	add r0, r4, #0
	add r1, r5, #0
	bl MOD17_021DC264
	pop {r4, r5, r6, pc}
_021DC618:
	bl GF_AssertFail
_021DC61C:
	pop {r4, r5, r6, pc}
	nop
_021DC620: .word 0x00000681
_021DC624: .word 0x000005E2
	thumb_func_end MOD17_021DC570

	thumb_func_start MOD17_021DC628
MOD17_021DC628: ; 0x021DC628
	push {r4, r5, r6, lr}
	sub sp, #0x90
	add r6, r0, #0
	mov r0, #0
	str r1, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	add r5, r2, #0
	str r0, [sp, #8]
	mov r2, #0
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldr r0, [r5, #0x40]
	add r4, r3, #0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x44]
	add r3, r1, #0
	str r0, [sp, #0x18]
	ldr r0, [r5, #0x48]
	str r0, [sp, #0x1c]
	ldr r0, [r5, #0x4c]
	str r0, [sp, #0x20]
	str r2, [sp, #0x24]
	str r2, [sp, #0x28]
	add r0, sp, #0x5c
	bl FUN_02008AA4
	ldr r0, [r5, #0x3c]
	mov r2, #0
	mov r1, #1
	str r0, [sp, #0x2c]
	add r0, sp, #0x5c
	str r0, [sp, #0x30]
	lsl r0, r4, #0xc
	str r0, [sp, #0x34]
	ldr r0, [sp, #0xa0]
	str r1, [sp, #0x54]
	lsl r0, r0, #0xc
	str r0, [sp, #0x38]
	mov r0, #2
	str r0, [sp, #0x50]
	mov r0, #0xe
	str r0, [sp, #0x58]
	add r0, sp, #0x2c
	str r0, [sp, #0x80]
	str r1, [sp, #0x8c]
	add r0, r6, #0
	add r1, sp, #0x80
	str r2, [sp, #0x3c]
	str r2, [sp, #0x84]
	str r2, [sp, #0x88]
	bl MOD17_021DC1A0
	add sp, #0x90
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC628

	thumb_func_start MOD17_021DC698
MOD17_021DC698: ; 0x021DC698
	push {r4, r5, r6, lr}
	sub sp, #0xa8
	add r5, r0, #0
	mov r0, #0
	str r1, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	add r4, r2, #0
	str r0, [sp, #8]
	mov r2, #0
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldr r0, [r4, #0x40]
	add r6, r3, #0
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x44]
	add r3, r1, #0
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x48]
	str r0, [sp, #0x1c]
	ldr r0, [r4, #0x4c]
	str r0, [sp, #0x20]
	str r2, [sp, #0x24]
	str r2, [sp, #0x28]
	add r0, sp, #0x5c
	bl FUN_02008AA4
	ldr r0, [r4, #0x3c]
	mov r1, #2
	str r0, [sp, #0x2c]
	add r0, sp, #0x5c
	str r0, [sp, #0x30]
	ldr r0, [sp, #0xbc]
	mov r2, #0xe
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	ldr r0, [sp, #0xc0]
	str r1, [sp, #0x50]
	mov r1, #1
	lsl r0, r0, #0xc
	str r0, [sp, #0x38]
	mov r0, #0
	str r2, [sp, #0x58]
	add r2, sp, #0x2c
	str r0, [sp, #0x3c]
	str r0, [sp, #0x84]
	str r0, [sp, #0x88]
	ldr r0, [sp, #0xb8]
	str r1, [sp, #0x54]
	str r0, [sp, #0x90]
	mov r0, #0x10
	str r0, [sp, #0x9c]
	mov r0, #0x13
	str r2, [sp, #0x80]
	str r1, [sp, #0x8c]
	str r6, [sp, #0x94]
	str r0, [sp, #0xa0]
	ldr r0, [r4, #0x44]
	bl FUN_020094F0
	mov r1, #0
	bl FUN_02009E54
	str r0, [sp, #0x98]
	ldr r0, [sp, #0xb8]
	mov r1, #1
	mov r2, #0xd
	bl FUN_02011898
	mov r1, #1
	add r3, r5, #0
	add r2, r1, #0
	add r3, #0x14
	bl FUN_0201D568
	cmp r0, #0
	bne _021DC736
	bl GF_AssertFail
_021DC736:
	ldr r0, [r5, #0x18]
	add r1, sp, #0x80
	str r0, [sp, #0xa4]
	add r0, r5, #0
	bl MOD17_021DC1E4
	add sp, #0xa8
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC698

	thumb_func_start MOD17_021DC748
MOD17_021DC748: ; 0x021DC748
	lsl r1, r1, #2
	strb r3, [r0, r1]
	add r1, r0, r1
	ldr r0, [sp, #4]
	strb r2, [r1, #2]
	add r0, r3, r0
	strb r0, [r1, #1]
	ldr r0, [sp]
	add r0, r2, r0
	strb r0, [r1, #3]
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DC748

	thumb_func_start MOD17_021DC760
MOD17_021DC760: ; 0x021DC760
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0x6b
	mov r4, #0
	str r0, [sp, #0xc]
	mov r7, #0x6a
	mov r6, #0x69
_021DC770:
	mov r0, #1
	str r0, [sp]
	ldr r2, [sp, #0xc]
	add r0, r5, #0
	mov r1, #0x19
	mov r3, #0
	str r4, [sp, #4]
	bl MOD17_021D7934
	add r0, r5, #0
	mov r1, #0x19
	add r2, r7, #0
	mov r3, #0
	str r4, [sp]
	bl MOD17_021D7978
	add r0, r5, #0
	mov r1, #0x19
	add r2, r6, #0
	mov r3, #0
	str r4, [sp]
	bl MOD17_021D7994
	ldr r0, [sp, #0xc]
	add r4, r4, #1
	add r0, r0, #3
	str r0, [sp, #0xc]
	add r7, r7, #3
	add r6, r6, #3
	cmp r4, #5
	blt _021DC770
	mov r0, #1
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r3, #0
	add r0, r5, #0
	mov r1, #0x19
	mov r2, #0x68
	str r3, [sp, #8]
	bl MOD17_021D7954
	mov r1, #1
	str r1, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r1, [sp, #8]
	add r0, r5, #0
	mov r1, #0x19
	mov r2, #0x78
	mov r3, #0
	bl MOD17_021D7954
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC760

	thumb_func_start MOD17_021DC7E0
MOD17_021DC7E0: ; 0x021DC7E0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021DC7E6:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD17_021D79B0
	add r4, r4, #1
	cmp r4, #5
	blt _021DC7E6
	add r0, r5, #0
	mov r1, #0
	bl MOD17_021D79C4
	add r0, r5, #0
	mov r1, #1
	bl MOD17_021D79C4
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC7E0

	thumb_func_start MOD17_021DC808
MOD17_021DC808: ; 0x021DC808
	push {r3, lr}
	cmp r1, #0
	bne _021DC814
	bl MOD17_021DC2F8
	pop {r3, pc}
_021DC814:
	cmp r1, #2
	bne _021DC81E
	bl MOD17_021DC2E0
	pop {r3, pc}
_021DC81E:
	cmp r1, #1
	beq _021DC826
	cmp r1, #3
	bne _021DC82A
_021DC826:
	bl MOD17_021DC2EC
_021DC82A:
	pop {r3, pc}
	thumb_func_end MOD17_021DC808

	thumb_func_start MOD17_021DC82C
MOD17_021DC82C: ; 0x021DC82C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bne _021DC848
	ldr r0, [r5, #0x10]
	mov r1, #0x10
	mov r2, #0xf
	bl FUN_020118C4
	ldr r0, [r5, #0x10]
	mov r1, #4
	bl FUN_02011A60
	pop {r3, r4, r5, pc}
_021DC848:
	cmp r4, #1
	bne _021DC856
	ldr r0, [r5, #0x10]
	mov r1, #0x10
	mov r2, #0x13
	bl FUN_020118C4
_021DC856:
	cmp r4, #3
	bne _021DC86C
	ldr r0, [r5, #0x10]
	mov r1, #0x10
	mov r2, #0x13
	bl FUN_020118C4
	ldr r0, [r5, #0x10]
	mov r1, #3
	bl FUN_02011A60
_021DC86C:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC82C

	thumb_func_start MOD17_021DC870
MOD17_021DC870: ; 0x021DC870
	push {r3, lr}
	cmp r3, r2
	bne _021DC87E
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	bl PlaySE
_021DC87E:
	pop {r3, pc}
	thumb_func_end MOD17_021DC870

	thumb_func_start MOD17_021DC880
MOD17_021DC880: ; 0x021DC880
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r3, #0
	mov r0, #0
	mov r3, #0xd
	bl NewMsgDataFromNarc
	add r6, r0, #0
	bne _021DC898
	bl GF_AssertFail
_021DC898:
	add r0, r6, #0
	add r1, r4, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	mov r0, #0xe
	mov r1, #1
	bl AllocWindows
	add r4, r0, #0
	bl InitWindow
	mov r0, #0
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	str r0, [sp]
	str r0, [sp, #4]
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r5, #0x38]
	add r1, r4, #0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl AddTextWindowTopLeftCorner
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021DC8F4 ; =0x00010203
	mov r1, #2
	str r0, [sp, #8]
	add r0, r4, #0
	add r2, r7, #0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	add r0, r6, #0
	bl DestroyMsgData
	add r0, r4, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DC8F4: .word 0x00010203
	thumb_func_end MOD17_021DC880

	thumb_func_start MOD17_021DC8F8
MOD17_021DC8F8: ; 0x021DC8F8
	ldr r3, _021DC900 ; =FUN_020191A4
	mov r1, #1
	bx r3
	nop
_021DC900: .word WindowArray_dtor
	thumb_func_end MOD17_021DC8F8

	thumb_func_start MOD17_021DC904
MOD17_021DC904: ; 0x021DC904
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	add r6, r2, #0
	bl FUN_0202011C
	add r3, r0, #0
	add r2, sp, #0
	ldmia r3!, {r0, r1}
	add r7, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r1, [sp]
	lsl r0, r4, #0xc
	add r0, r1, r0
	str r0, [sp]
	ldr r1, [sp, #4]
	lsl r0, r6, #0xc
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r0, [r5]
	add r1, r7, #0
	bl FUN_02020044
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DC904

	thumb_func_start MOD17_021DC940
MOD17_021DC940: ; 0x021DC940
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021DC904
	ldr r0, [r4, #0x10]
	bl FUN_02011938
	pop {r4, pc}
	thumb_func_end MOD17_021DC940

	thumb_func_start MOD17_021DC950
MOD17_021DC950: ; 0x021DC950
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r6, r2, #0
	mov r1, #1
	add r5, r0, #0
	tst r1, r6
	beq _021DC96A
	mov r2, #0x52
	mov r1, #0
	lsl r2, r2, #2
	bl memset
_021DC96A:
	mov r0, #2
	tst r0, r6
	beq _021DC978
	ldr r1, [r4]
	add r0, r5, #0
	bl MOD17_021DCC00
_021DC978:
	mov r0, #4
	add r1, r6, #0
	tst r1, r0
	beq _021DC99C
	mov r1, #0x1b
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #0x1f
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	add r0, r5, #0
	ldr r1, [r4]
	add r0, #0x2c
	mov r2, #2
	mov r3, #0x13
	bl MOD17_021DCC68
_021DC99C:
	mov r0, #8
	tst r0, r6
	beq _021DC9B0
	add r0, r5, #0
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0x10]
	add r0, #0x38
	bl MOD17_021DCE34
_021DC9B0:
	mov r0, #0x10
	tst r0, r6
	beq _021DC9CC
	ldr r0, [r4]
	str r0, [sp]
	ldr r0, [r4, #0x20]
	str r0, [sp, #4]
	add r0, r5, #0
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0x1c]
	add r0, #0xa0
	bl MOD17_021DD074
_021DC9CC:
	mov r0, #0x20
	tst r0, r6
	beq _021DCA42
	mov r0, #0x1b
	str r0, [sp]
	mov r2, #2
	str r2, [sp, #4]
	mov r0, #0x8b
	str r0, [sp, #8]
	mov r3, #1
	str r3, [sp, #0xc]
	add r0, #0xa9
	ldr r1, [r4]
	add r0, r5, r0
	bl MOD17_021DCC68
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _021DCA7C ; =0x0001020F
	mov r1, #0x1a
	str r0, [sp, #8]
	mov r0, #0xff
	str r0, [sp, #0xc]
	add r0, #0x35
	ldr r0, [r5, r0]
	ldr r2, [r4, #0x14]
	mov r3, #6
	bl MOD17_021DCD80
	mov r0, #0x48
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _021DCA7C ; =0x0001020F
	mov r1, #0x1a
	str r0, [sp, #8]
	mov r0, #0xff
	str r0, [sp, #0xc]
	add r0, #0x35
	ldr r0, [r5, r0]
	ldr r2, [r4, #0x14]
	ldr r3, [r4, #0x18]
	bl MOD17_021DCD80
	mov r0, #0x4d
	lsl r0, r0, #2
	mov r2, #1
	ldr r0, [r5, r0]
	mov r1, #0
	add r3, r2, #0
	bl FUN_0200D0BC
_021DCA42:
	ldr r0, [r4, #4]
	str r0, [r5, #0x30]
	ldr r0, [r4, #8]
	str r0, [r5, #0x34]
	ldr r0, [r4]
	ldr r1, [r4, #0xc]
	bl MOD17_021DCC38
	ldr r0, [r4, #0xc]
	bl Options_GetFrame
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r4, #0xc]
	bl Options_GetTextFrameDelay
	mov r1, #5
	lsl r1, r1, #6
	str r0, [r5, r1]
	add r0, r1, #0
	sub r0, #8
	ldr r0, [r5, r0]
	sub r1, #8
	orr r0, r6
	str r0, [r5, r1]
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_021DCA7C: .word 0x0001020F
	thumb_func_end MOD17_021DC950

	thumb_func_start MOD17_021DCA80
MOD17_021DCA80: ; 0x021DCA80
	push {r4, lr}
	mov r1, #0x4e
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r1, #2
	tst r1, r2
	beq _021DCAA0
	bl MOD17_021DCCD8
	mov r1, #0x4e
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r0, #2
	bic r2, r0
	str r2, [r4, r1]
_021DCAA0:
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	mov r0, #4
	tst r0, r1
	beq _021DCABE
	ldr r0, [r4, #0x2c]
	bl MOD17_021DCCE0
	mov r1, #0x4e
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r0, #4
	bic r2, r0
	str r2, [r4, r1]
_021DCABE:
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	mov r0, #8
	tst r0, r1
	beq _021DCAE0
	add r0, r4, #0
	ldr r1, [r4, #0x34]
	add r0, #0x38
	bl MOD17_021DCF30
	mov r1, #0x4e
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r0, #8
	bic r2, r0
	str r2, [r4, r1]
_021DCAE0:
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	mov r0, #0x10
	tst r0, r1
	beq _021DCB02
	add r0, r4, #0
	ldr r1, [r4, #0x34]
	add r0, #0xa0
	bl MOD17_021DD178
	mov r1, #0x4e
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r0, #0x10
	bic r2, r0
	str r2, [r4, r1]
_021DCB02:
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r2, [r4, r0]
	mov r1, #0x20
	tst r1, r2
	beq _021DCB22
	sub r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD17_021DCCE0
	mov r1, #0x4e
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r0, #0x20
	bic r2, r0
	str r2, [r4, r1]
_021DCB22:
	mov r2, #0x52
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	pop {r4, pc}
	thumb_func_end MOD17_021DCA80

	thumb_func_start MOD17_021DCB30
MOD17_021DCB30: ; 0x021DCB30
	push {r3, lr}
	mov r1, #0x4e
	lsl r1, r1, #2
	ldr r2, [r0, r1]
	mov r1, #0x10
	tst r1, r2
	beq _021DCB44
	add r0, #0xa0
	bl MOD17_021DD1AC
_021DCB44:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD17_021DCB30

	thumb_func_start MOD17_021DCB48
MOD17_021DCB48: ; 0x021DCB48
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0x4e
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r1, [r5, r0]
	mov r0, #4
	add r6, r2, #0
	add r7, r3, #0
	tst r0, r1
	bne _021DCB64
	bl GF_AssertFail
_021DCB64:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0xff
	str r0, [sp, #8]
	ldr r0, [r5, #0x2c]
	add r1, r4, #0
	add r2, r6, #0
	add r3, r7, #0
	bl MOD17_021DCCEC
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DCB48

	thumb_func_start MOD17_021DCB80
MOD17_021DCB80: ; 0x021DCB80
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0x4e
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r1, [r5, r0]
	mov r0, #4
	add r6, r2, #0
	add r7, r3, #0
	tst r0, r1
	bne _021DCB9C
	bl GF_AssertFail
_021DCB9C:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #5
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	add r0, r0, #4
	str r1, [sp, #8]
	add r0, r5, r0
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x2c]
	add r1, r4, #0
	add r2, r6, #0
	add r3, r7, #0
	bl MOD17_021DCD34
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DCB80

	thumb_func_start MOD17_021DCBC0
MOD17_021DCBC0: ; 0x021DCBC0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0x51
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	pop {r4, pc}
	thumb_func_end MOD17_021DCBC0

	thumb_func_start MOD17_021DCBD8
MOD17_021DCBD8: ; 0x021DCBD8
	ldr r3, _021DCBE0 ; =MOD17_021DCEE8
	add r0, #0x38
	bx r3
	nop
_021DCBE0: .word MOD17_021DCEE8
	thumb_func_end MOD17_021DCBD8

	thumb_func_start MOD17_021DCBE4
MOD17_021DCBE4: ; 0x021DCBE4
	add r0, #0xbc
	ldr r0, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DCBE4

	thumb_func_start MOD17_021DCBEC
MOD17_021DCBEC: ; 0x021DCBEC
	add r0, #0xc0
	str r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DCBEC

	thumb_func_start MOD17_021DCBF4
MOD17_021DCBF4: ; 0x021DCBF4
	ldr r3, _021DCBFC ; =MOD17_021DD454
	add r0, #0xd0
	bx r3
	nop
_021DCBFC: .word MOD17_021DD454
	thumb_func_end MOD17_021DCBF4

	thumb_func_start MOD17_021DCC00
MOD17_021DCC00: ; 0x021DCC00
	push {r3, lr}
	sub sp, #0x30
	str r1, [sp]
	mov r1, #0x19
	str r1, [sp, #4]
	mov r1, #0xe0
	str r1, [sp, #8]
	mov r1, #0xe1
	str r1, [sp, #0xc]
	mov r2, #0
	mov r1, #0xe2
	str r1, [sp, #0x10]
	mov r1, #4
	str r1, [sp, #0x1c]
	mov r1, #1
	str r1, [sp, #0x20]
	mov r1, #0xe
	str r1, [sp, #0x2c]
	add r1, sp, #0
	str r2, [sp, #0x14]
	str r2, [sp, #0x18]
	str r2, [sp, #0x24]
	str r2, [sp, #0x28]
	bl MOD17_021DBD04
	add sp, #0x30
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD17_021DCC00

	thumb_func_start MOD17_021DCC38
MOD17_021DCC38: ; 0x021DCC38
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r0, r1, #0
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xe
	mov r2, #1
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #5
	add r3, r2, #0
	bl FUN_0200CD68
	mov r0, #4
	mov r1, #0x40
	mov r2, #0xe
	bl FUN_02002EEC
	add sp, #8
	pop {r4, pc}
	thumb_func_end MOD17_021DCC38

	thumb_func_start MOD17_021DCC68
MOD17_021DCC68: ; 0x021DCC68
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r7, r1, #0
	add r6, r3, #0
	mov r0, #0xe
	mov r1, #1
	add r4, r2, #0
	bl AllocWindows
	str r0, [r5]
	bl InitWindow
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #0x28]
	lsl r3, r4, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r0, [sp, #0x2c]
	mov r2, #5
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x30]
	lsr r3, r3, #0x18
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r1, [r5]
	add r0, r7, #0
	bl AddWindowParameterized
	ldr r0, [r5]
	mov r1, #0xf
	bl FillWindowPixelBuffer
	ldr r0, [sp, #0x34]
	cmp r0, #0
	beq _021DCCCC
	mov r2, #1
	ldr r0, [r5]
	mov r1, #0
	add r3, r2, #0
	bl FUN_0200D0BC
_021DCCCC:
	ldr r0, [r5]
	bl CopyWindowToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DCC68

	thumb_func_start MOD17_021DCCD8
MOD17_021DCCD8: ; 0x021DCCD8
	ldr r3, _021DCCDC ; =MOD17_021DBD4C
	bx r3
	.align 2, 0
_021DCCDC: .word MOD17_021DBD4C
	thumb_func_end MOD17_021DCCD8

	thumb_func_start MOD17_021DCCE0
MOD17_021DCCE0: ; 0x021DCCE0
	ldr r3, _021DCCE8 ; =FUN_020191A4
	mov r1, #1
	bx r3
	nop
_021DCCE8: .word WindowArray_dtor
	thumb_func_end MOD17_021DCCE0

	thumb_func_start MOD17_021DCCEC
MOD17_021DCCEC: ; 0x021DCCEC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	mov r1, #0xf
	add r5, r0, #0
	add r6, r2, #0
	add r7, r3, #0
	bl FillWindowPixelBuffer
	ldr r0, [sp, #0x28]
	add r1, r4, #0
	str r0, [sp]
	ldr r0, [sp, #0x2c]
	add r2, r6, #0
	str r0, [sp, #4]
	ldr r0, _021DCD30 ; =0x0001020F
	add r3, r7, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x30]
	str r0, [sp, #0xc]
	add r0, r5, #0
	bl MOD17_021DCD80
	mov r2, #1
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0
	add r3, r2, #0
	bl FUN_0200D0BC
	add r0, r4, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DCD30: .word 0x0001020F
	thumb_func_end MOD17_021DCCEC

	thumb_func_start MOD17_021DCD34
MOD17_021DCD34: ; 0x021DCD34
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	mov r1, #0xf
	add r5, r0, #0
	add r6, r2, #0
	add r7, r3, #0
	bl FillWindowPixelBuffer
	ldr r0, [sp, #0x28]
	add r1, r4, #0
	str r0, [sp]
	ldr r0, [sp, #0x2c]
	add r2, r6, #0
	str r0, [sp, #4]
	ldr r0, _021DCD7C ; =0x0001020F
	add r3, r7, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x30]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x34]
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl MOD17_021DCDD4
	mov r2, #1
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0
	add r3, r2, #0
	bl FUN_0200D0BC
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021DCD7C: .word 0x0001020F
	thumb_func_end MOD17_021DCD34

	thumb_func_start MOD17_021DCD80
MOD17_021DCD80: ; 0x021DCD80
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r6, r0, #0
	add r4, r3, #0
	mov r0, #0
	mov r3, #0xd
	bl NewMsgDataFromNarc
	add r5, r0, #0
	bne _021DCD98
	bl GF_AssertFail
_021DCD98:
	add r0, r5, #0
	add r1, r4, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, [sp, #0x24]
	ldr r3, [sp, #0x20]
	str r0, [sp]
	ldr r0, [sp, #0x2c]
	mov r1, #1
	str r0, [sp, #4]
	ldr r0, [sp, #0x28]
	add r2, r4, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r6, #0
	bl AddTextPrinterParameterized2
	add r6, r0, #0
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl DestroyMsgData
	add r0, r6, #0
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DCD80

	thumb_func_start MOD17_021DCDD4
MOD17_021DCDD4: ; 0x021DCDD4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldr r4, [sp, #0x38]
	add r7, r0, #0
	ldr r0, [r4]
	add r5, r1, #0
	add r6, r2, #0
	str r3, [sp, #0x10]
	cmp r0, #0
	beq _021DCDEC
	bl GF_AssertFail
_021DCDEC:
	mov r0, #0
	add r1, r5, #0
	add r2, r6, #0
	mov r3, #0xd
	bl NewMsgDataFromNarc
	add r5, r0, #0
	bne _021DCE00
	bl GF_AssertFail
_021DCE00:
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	bl NewString_ReadMsgData
	str r0, [r4]
	ldr r0, [sp, #0x2c]
	ldr r3, [sp, #0x28]
	str r0, [sp]
	ldr r0, [sp, #0x34]
	mov r1, #1
	str r0, [sp, #4]
	ldr r0, [sp, #0x30]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r2, [r4]
	add r0, r7, #0
	bl AddTextPrinterParameterized2
	add r4, r0, #0
	add r0, r5, #0
	bl DestroyMsgData
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DCDD4

	thumb_func_start MOD17_021DCE34
MOD17_021DCE34: ; 0x021DCE34
	push {r4, r5, r6, r7, lr}
	sub sp, #0x6c
	add r5, r1, #0
	mov r1, #0x67
	str r1, [sp]
	mov r1, #0xe1
	str r1, [sp, #4]
	mov r1, #0x66
	str r1, [sp, #8]
	mov r1, #0x65
	str r1, [sp, #0xc]
	mov r1, #2
	str r1, [sp, #0x10]
	mov r1, #0x7d
	add r4, r2, #0
	lsl r1, r1, #4
	str r3, [sp, #0x1c]
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	add r1, r4, #0
	mov r2, #0xe
	mov r3, #0x19
	bl MOD17_021DCF54
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	add r2, sp, #0x48
	mov r3, #0
	bl MOD17_021DD014
	add r0, sp, #0x48
	str r0, [sp, #0x2c]
	mov r0, #2
	str r0, [sp, #0x40]
	mov r0, #0
	str r0, [sp, #0x24]
	str r0, [sp, #0x3c]
	mov r0, #0xe
	str r0, [sp, #0x44]
	mov r0, #0x68
	ldr r7, [sp, #0x24]
	str r5, [sp, #0x28]
	str r0, [sp, #0x20]
_021DCE8A:
	ldr r0, [sp, #0x20]
	mov r6, #0
	str r0, [sp, #0x34]
	lsl r1, r0, #0xc
	mov r0, #2
	lsl r0, r0, #0x14
	str r1, [sp, #0x34]
	add r0, r1, r0
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x18]
	lsl r1, r7, #2
	mov r4, #0x26
	add r5, r0, r1
_021DCEA4:
	str r4, [sp, #0x30]
	lsl r0, r4, #0xc
	str r0, [sp, #0x30]
	add r0, sp, #0x28
	bl FUN_0201FF84
	mov r1, #1
	str r0, [r5, #0x10]
	bl FUN_02020130
	ldr r0, [sp, #0x1c]
	add r1, r6, r7
	cmp r1, r0
	blt _021DCEC8
	ldr r0, [r5, #0x10]
	mov r1, #0
	bl FUN_020200A0
_021DCEC8:
	add r6, r6, #1
	add r4, #0x12
	add r5, r5, #4
	cmp r6, #0xa
	blt _021DCEA4
	ldr r0, [sp, #0x20]
	add r7, #0xa
	add r0, #0x12
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x24]
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, #2
	blt _021DCE8A
	add sp, #0x6c
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DCE34

	thumb_func_start MOD17_021DCEE8
MOD17_021DCEE8: ; 0x021DCEE8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r6, [r7, #0x60]
	add r5, r1, #0
	cmp r6, r5
	bge _021DCF0E
	cmp r6, r5
	bge _021DCF2C
	lsl r0, r6, #2
	add r4, r7, r0
_021DCEFC:
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_02020130
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, r5
	blt _021DCEFC
	b _021DCF2C
_021DCF0E:
	cmp r6, r5
	ble _021DCF2C
	sub r6, r6, #1
	cmp r6, r5
	blt _021DCF2C
	lsl r0, r6, #2
	add r4, r7, r0
_021DCF1C:
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_02020130
	sub r6, r6, #1
	sub r4, r4, #4
	cmp r6, r5
	bge _021DCF1C
_021DCF2C:
	str r5, [r7, #0x60]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DCEE8

	thumb_func_start MOD17_021DCF30
MOD17_021DCF30: ; 0x021DCF30
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r4, #0
	add r5, r6, #0
_021DCF3A:
	ldr r0, [r5, #0x10]
	bl FUN_0201FFC8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x14
	blt _021DCF3A
	add r0, r6, #0
	add r1, r7, #0
	bl MOD17_021DCFE0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DCF30

	thumb_func_start MOD17_021DCF54
MOD17_021DCF54: ; 0x021DCF54
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r2, #0
	ldr r7, [sp, #0x3c]
	ldr r2, [sp, #0x28]
	add r5, r0, #0
	add r0, r7, r2
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r4, r1, #0
	str r6, [sp, #8]
	ldr r0, [r4]
	str r3, [sp, #0x10]
	add r1, r3, #0
	mov r3, #0
	bl FUN_02008F34
	str r0, [r5]
	bl FUN_02009B04
	ldr r0, [r5]
	bl FUN_02009474
	ldr r2, [sp, #0x2c]
	ldr r1, [sp, #0x10]
	add r0, r7, r2
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, [sp, #0x38]
	mov r3, #0
	str r0, [sp, #8]
	str r6, [sp, #0xc]
	ldr r0, [r4, #4]
	bl FUN_02008FEC
	str r0, [r5, #4]
	bl FUN_02009D68
	ldr r0, [r5, #4]
	bl FUN_02009474
	ldr r2, [sp, #0x30]
	ldr r1, [sp, #0x10]
	add r0, r7, r2
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldr r0, [r4, #8]
	mov r3, #0
	bl FUN_020090AC
	ldr r2, [sp, #0x34]
	str r0, [r5, #8]
	add r0, r7, r2
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldr r0, [r4, #0xc]
	ldr r1, [sp, #0x10]
	mov r3, #0
	bl FUN_020090AC
	str r0, [r5, #0xc]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DCF54

	thumb_func_start MOD17_021DCFE0
MOD17_021DCFE0: ; 0x021DCFE0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	bl FUN_02009C0C
	ldr r0, [r5, #4]
	bl FUN_02009E04
	ldr r0, [r4]
	ldr r1, [r5]
	bl FUN_02009490
	ldr r0, [r4, #4]
	ldr r1, [r5, #4]
	bl FUN_02009490
	ldr r0, [r4, #8]
	ldr r1, [r5, #8]
	bl FUN_02009490
	ldr r0, [r4, #0xc]
	ldr r1, [r5, #0xc]
	bl FUN_02009490
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DCFE0

	thumb_func_start MOD17_021DD014
MOD17_021DD014: ; 0x021DD014
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	add r7, r2, #0
	add r6, r3, #0
	bl FUN_02009530
	str r0, [sp, #0x2c]
	ldr r0, [r5, #4]
	bl FUN_02009530
	str r0, [sp, #0x30]
	ldr r0, [r5, #8]
	bl FUN_02009530
	str r0, [sp, #0x34]
	ldr r0, [r5, #0xc]
	bl FUN_02009530
	str r0, [sp]
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r6, [sp, #0x10]
	ldr r1, [r4]
	ldr r2, [sp, #0x30]
	str r1, [sp, #0x14]
	ldr r1, [r4, #4]
	ldr r3, [sp, #0x34]
	str r1, [sp, #0x18]
	ldr r1, [r4, #8]
	str r1, [sp, #0x1c]
	ldr r1, [r4, #0xc]
	str r1, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	ldr r1, [sp, #0x2c]
	add r0, r7, #0
	bl FUN_02008AA4
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD014

	thumb_func_start MOD17_021DD074
MOD17_021DD074: ; 0x021DD074
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x60
	add r4, r1, #0
	mov r1, #0xe5
	str r1, [sp]
	mov r1, #0xe6
	str r1, [sp, #4]
	mov r1, #0xe4
	str r1, [sp, #8]
	mov r1, #0xe3
	str r1, [sp, #0xc]
	mov r1, #2
	str r1, [sp, #0x10]
	ldr r1, _021DD170 ; =0x00000BB8
	add r5, r2, #0
	str r3, [sp, #0x18]
	str r1, [sp, #0x14]
	add r7, r0, #0
	add r1, r5, #0
	mov r2, #0xe
	mov r3, #0x19
	bl MOD17_021DCF54
	add r0, r7, #0
	add r1, r5, #0
	add r2, sp, #0x3c
	mov r3, #0
	bl MOD17_021DD014
	add r0, sp, #0x3c
	str r0, [sp, #0x20]
	mov r2, #2
	mov r0, #0xe
	mov r1, #0x3a
	str r0, [sp, #0x38]
	lsl r1, r1, #0xc
	lsl r0, r2, #0x14
	mov r6, #0
	str r4, [sp, #0x1c]
	str r1, [sp, #0x28]
	add r0, r1, r0
	str r2, [sp, #0x34]
	str r6, [sp, #0x30]
	str r0, [sp, #0x28]
	mov r4, #0x67
	add r5, r7, #0
_021DD0D0:
	str r4, [sp, #0x24]
	lsl r0, r4, #0xc
	str r0, [sp, #0x24]
	add r0, sp, #0x1c
	bl FUN_0201FF84
	str r0, [r5, #0x10]
	add r6, r6, #1
	add r4, #0x18
	add r5, r5, #4
	cmp r6, #2
	blt _021DD0D0
	ldr r0, [sp, #0x18]
	mov r1, #0x1e
	str r0, [r7, #0x1c]
	mul r1, r0
	str r1, [r7, #0x20]
	ldr r1, [sp, #0x7c]
	str r1, [r7, #0x2c]
	str r0, [r1]
	ldr r1, [r7, #0x2c]
	str r0, [r1, #8]
	add r0, r7, #0
	mov r1, #0
	add r0, #0x90
	str r1, [r0]
	add r0, r7, #0
	bl MOD17_021DD204
	mov r0, #0xe
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #0xc1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r7, #0
	ldr r1, [sp, #0x78]
	add r0, #0x18
	mov r2, #0xa
	mov r3, #8
	bl MOD17_021DCC68
	ldr r0, [r7, #0x18]
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r0, #0
	str r0, [sp]
	mov r3, #4
	ldr r0, _021DD174 ; =0x00010200
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r2, #0xff
	str r2, [sp, #0xc]
	ldr r0, [r7, #0x18]
	mov r1, #0x1a
	add r2, #0x52
	bl MOD17_021DCD80
	mov r0, #0x48
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, _021DD174 ; =0x00010200
	mov r2, #0xff
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	ldr r0, [r7, #0x18]
	mov r1, #0x1a
	add r2, #0x52
	mov r3, #5
	bl MOD17_021DCD80
	ldr r0, [r7, #0x18]
	bl CopyWindowToVram
	add sp, #0x60
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DD170: .word 0x00000BB8
_021DD174: .word 0x00010200
	thumb_func_end MOD17_021DD074

	thumb_func_start MOD17_021DD178
MOD17_021DD178: ; 0x021DD178
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x24]
	add r4, r1, #0
	cmp r0, #0
	beq _021DD188
	bl FUN_0200CAB4
_021DD188:
	ldr r0, [r5, #0x28]
	cmp r0, #0
	beq _021DD192
	bl FUN_0200CAB4
_021DD192:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD17_021DCFE0
	ldr r0, [r5, #0x18]
	bl MOD17_021DCCE0
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x94
	bl memset
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DD178

	thumb_func_start MOD17_021DD1AC
MOD17_021DD1AC: ; 0x021DD1AC
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021DD27C
	ldr r0, [r4, #0x20]
	mov r1, #0x1e
	bl _s32_div_f
	add r1, r0, #0
	ldr r0, [r4, #0x2c]
	bl FUN_02083A34
	add r0, r4, #0
	bl MOD17_021DD1DC
	add r0, r4, #0
	bl MOD17_021DD204
	add r4, #0x30
	add r0, r4, #0
	bl MOD17_021DD3BC
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD1AC

	thumb_func_start MOD17_021DD1DC
MOD17_021DD1DC: ; 0x021DD1DC
	push {r3, lr}
	ldr r1, [r0, #0x2c]
	ldr r2, [r1]
	ldr r1, [r0, #0x1c]
	cmp r1, r2
	beq _021DD1FC
	str r2, [r0, #0x1c]
	cmp r2, #0xa
	bgt _021DD1FC
	add r1, r0, #0
	add r1, #0x30
	bl MOD17_021DD2E0
	ldr r0, _021DD200 ; =0x00000683
	bl PlaySE
_021DD1FC:
	pop {r3, pc}
	nop
_021DD200: .word 0x00000683
	thumb_func_end MOD17_021DD1DC

	thumb_func_start MOD17_021DD204
MOD17_021DD204: ; 0x021DD204
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	ldr r0, [r6, #0x1c]
	mov r1, #1
	str r0, [sp]
	mov r0, #0xa
	add r4, r1, #0
	mul r4, r0
	mov r7, #0
	add r5, r6, #0
_021DD21A:
	ldr r0, [sp]
	add r1, r4, #0
	bl _s32_div_f
	str r0, [sp, #4]
	cmp r0, #0xa
	ble _021DD22C
	bl GF_AssertFail
_021DD22C:
	ldr r0, [r5, #0x10]
	ldr r1, [sp, #4]
	bl FUN_02020130
	ldr r0, [sp, #4]
	add r1, r0, #0
	ldr r0, [sp]
	mul r1, r4
	sub r0, r0, r1
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0xa
	bl _s32_div_f
	add r4, r0, #0
	add r0, r6, #0
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #0
	bne _021DD26E
	ldr r0, [r6, #0x1c]
	cmp r0, #0xa
	bgt _021DD26E
	ldr r0, [r5, #0x10]
	mov r1, #1
	bl FUN_0202027C
	cmp r7, #1
	bne _021DD26E
	add r1, r6, #0
	add r1, #0x90
	mov r0, #1
	str r0, [r1]
_021DD26E:
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #2
	blt _021DD21A
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD204

	thumb_func_start MOD17_021DD27C
MOD17_021DD27C: ; 0x021DD27C
	ldr r1, [r0, #0x20]
	sub r1, r1, #1
	bmi _021DD284
	str r1, [r0, #0x20]
_021DD284:
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DD27C

	thumb_func_start MOD17_021DD288
MOD17_021DD288: ; 0x021DD288
	str r1, [r0]
	str r1, [r0, #4]
	sub r1, r2, r1
	str r1, [r0, #8]
	str r3, [r0, #0x10]
	mov r1, #0
	str r1, [r0, #0xc]
	bx lr
	thumb_func_end MOD17_021DD288

	thumb_func_start MOD17_021DD298
MOD17_021DD298: ; 0x021DD298
	push {r4, lr}
	add r4, r0, #0
	ldr r2, [r4, #0xc]
	ldr r0, [r4, #8]
	lsl r2, r2, #0xc
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	ldr r1, [r4, #0x10]
	lsl r1, r1, #0xc
	bl FX_Div
	ldr r1, [r4, #4]
	add r0, r0, r1
	str r0, [r4]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r0, r0, #1
	cmp r0, r1
	bgt _021DD2D8
	str r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}
_021DD2D8:
	str r1, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD298

	thumb_func_start MOD17_021DD2E0
MOD17_021DD2E0: ; 0x021DD2E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp]
	str r1, [sp, #4]
	mov r1, #0x3a
	mov r0, #2
	lsl r1, r1, #0xc
	lsl r0, r0, #0x14
	ldr r4, [sp, #4]
	str r1, [sp, #0x10]
	add r0, r1, r0
	str r0, [sp, #0x10]
	add r0, r4, #0
	ldr r6, [sp]
	mov r7, #0
	mov r5, #0x67
	str r0, [sp, #8]
_021DD302:
	ldr r0, [r6, #0x10]
	mov r1, #2
	str r0, [r4, #4]
	bl FUN_020200EC
	ldr r2, [sp, #8]
	str r5, [sp, #0xc]
	lsl r0, r5, #0xc
	add r2, #0xc
	add r3, sp, #0xc
	str r0, [sp, #0xc]
	ldmia r3!, {r0, r1}
	str r2, [sp, #8]
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r7, r7, #1
	str r0, [r2]
	add r6, r6, #4
	add r4, r4, #4
	add r5, #0x18
	cmp r7, #2
	blt _021DD302
	ldr r0, [sp]
	ldr r1, [r0, #0x1c]
	mov r0, #0xa
	sub r0, r0, r1
	cmp r0, #0
	ble _021DD35C
	lsl r0, r0, #0xc
	ldr r2, _021DD3B8 ; =0x00000266
	asr r1, r0, #0x1f
	mov r3, #0
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r4, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r4, #0xc
	orr r1, r0
	lsl r0, r2, #1
	add r4, r1, r0
	b _021DD360
_021DD35C:
	mov r4, #1
	lsl r4, r4, #0xc
_021DD360:
	ldr r0, [sp, #4]
	mov r2, #1
	add r0, #0x24
	add r1, r4, #0
	lsl r2, r2, #0xc
	mov r3, #0x10
	bl MOD17_021DD288
	mov r2, #6
	asr r1, r4, #0x1f
	add r0, r4, #0
	lsl r2, r2, #0xe
	mov r3, #0
	bl _ll_mul
	mov r3, #2
	mov r2, #0
	lsl r3, r3, #0xa
	add r3, r0, r3
	adc r1, r2
	lsl r0, r1, #0x14
	lsr r1, r3, #0xc
	orr r1, r0
	mov r0, #6
	lsl r0, r0, #0xe
	sub r4, r1, r0
	ldr r0, [sp, #4]
	add r1, r4, #0
	add r0, #0x38
	mov r3, #0x10
	bl MOD17_021DD288
	ldr r0, [sp, #4]
	add r1, r4, #0
	add r0, #0x4c
	mov r2, #0
	mov r3, #0x10
	bl MOD17_021DD288
	ldr r0, [sp, #4]
	mov r1, #1
	str r1, [r0]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DD3B8: .word 0x00000266
	thumb_func_end MOD17_021DD2E0

	thumb_func_start MOD17_021DD3BC
MOD17_021DD3BC: ; 0x021DD3BC
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _021DD44E
	add r0, r5, #0
	add r0, #0x24
	bl MOD17_021DD298
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x38
	bl MOD17_021DD298
	add r0, r5, #0
	add r0, #0x4c
	bl MOD17_021DD298
	ldr r0, [r5, #0x24]
	add r1, sp, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x24]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x24]
	str r0, [sp, #0x14]
	ldr r0, [r5, #4]
	bl FUN_02020064
	ldr r0, [r5, #8]
	add r1, sp, #0xc
	bl FUN_02020064
	add r6, r5, #0
	add r6, #0xc
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	ldr r1, [sp]
	ldr r0, [r5, #0x38]
	sub r0, r1, r0
	str r0, [sp]
	ldr r1, [sp, #4]
	ldr r0, [r5, #0x4c]
	sub r0, r1, r0
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	add r1, r2, #0
	bl FUN_02020044
	add r6, r5, #0
	add r6, #0x18
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	ldr r1, [sp, #4]
	ldr r0, [r5, #0x4c]
	sub r0, r1, r0
	str r0, [sp, #4]
	ldr r0, [r5, #8]
	add r1, r2, #0
	bl FUN_02020044
	cmp r4, #0
	beq _021DD44E
	mov r0, #0
	str r0, [r5]
_021DD44E:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD3BC

	thumb_func_start MOD17_021DD454
MOD17_021DD454: ; 0x021DD454
	ldr r0, [r0]
	cmp r0, #1
	beq _021DD45E
	mov r0, #1
	bx lr
_021DD45E:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DD454

	thumb_func_start MOD17_021DD464
MOD17_021DD464: ; 0x021DD464
	push {r3, lr}
	sub sp, #0x10
	add r3, r1, #0
	stmia r0!, {r1}
	add r3, #0x48
	str r3, [sp]
	ldr r1, [r1, #0x74]
	lsl r1, r1, #2
	add r1, #0x89
	str r1, [sp, #4]
	mov r1, #0x10
	str r1, [sp, #8]
	add r1, sp, #0
	str r2, [sp, #0xc]
	bl MOD17_021DBD68
	add sp, #0x10
	pop {r3, pc}
	thumb_func_end MOD17_021DD464

	thumb_func_start MOD17_021DD488
MOD17_021DD488: ; 0x021DD488
	ldr r3, _021DD490 ; =MOD17_021DBD80
	add r0, r0, #4
	mov r1, #1
	bx r3
	.align 2, 0
_021DD490: .word MOD17_021DBD80
	thumb_func_end MOD17_021DD488

	thumb_func_start MOD17_021DD494
MOD17_021DD494: ; 0x021DD494
	push {r4, lr}
	add r4, r0, #0
	add r0, r4, #4
	bl MOD17_021DBDE8
	mov r1, #0x1c
	mov r0, #0
_021DD4A2:
	strb r0, [r4]
	add r4, r4, #1
	sub r1, r1, #1
	bne _021DD4A2
	pop {r4, pc}
	thumb_func_end MOD17_021DD494

	thumb_func_start MOD17_021DD4AC
MOD17_021DD4AC: ; 0x021DD4AC
	push {r3, r4, lr}
	sub sp, #0x6c
	add r2, r0, #0
	add r4, r1, #0
	add r0, sp, #0
	add r1, r2, #0
	bl MOD17_021DD9E8
	add r0, sp, #0
	add r1, r4, #0
	bl MOD17_021DD9FC
	add r0, sp, #0
	bl MOD17_021DD6DC
	add sp, #0x6c
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD4AC

	thumb_func_start MOD17_021DD4D0
MOD17_021DD4D0: ; 0x021DD4D0
	push {r3, r4, lr}
	sub sp, #0x6c
	add r2, r0, #0
	add r4, r1, #0
	add r0, sp, #0
	add r1, r2, #0
	bl MOD17_021DD9E8
	add r0, sp, #0
	add r1, r4, #0
	bl MOD17_021DDA44
	add r0, sp, #0
	bl MOD17_021DD6DC
	add sp, #0x6c
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD4D0

	thumb_func_start MOD17_021DD4F4
MOD17_021DD4F4: ; 0x021DD4F4
	push {r3, r4, lr}
	sub sp, #0x6c
	add r2, r0, #0
	add r4, r1, #0
	add r0, sp, #0
	add r1, r2, #0
	bl MOD17_021DD9E8
	add r0, sp, #0
	add r1, r4, #0
	bl MOD17_021DDA44
	add r0, sp, #0
	bl MOD17_021DD778
	add sp, #0x6c
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD4F4

	thumb_func_start MOD17_021DD518
MOD17_021DD518: ; 0x021DD518
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x95
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #1
	bne _021DD52E
	sub r0, #0x48
	add r0, r4, r0
	bl MOD17_021DD488
_021DD52E:
	mov r0, #0x96
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021DD53E
	add r0, r4, #0
	bl MOD17_021DD838
_021DD53E:
	pop {r4, pc}
	thumb_func_end MOD17_021DD518

	thumb_func_start MOD17_021DD540
MOD17_021DD540: ; 0x021DD540
	push {r4, lr}
	mov r1, #0x95
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	cmp r1, #0
	beq _021DD552
	bl MOD17_021DD984
_021DD552:
	add r0, r4, #0
	bl MOD17_021DD968
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl MOD17_021D750C
	mov r0, #6
	mov r1, #0
	lsl r0, r0, #6
	str r1, [r4, r0]
	sub r0, #8
	add r0, r4, r0
	bl MOD17_021DBA1C
	add r0, r4, #0
	bl MOD17_021DD86C
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD540

	thumb_func_start MOD17_021DD58C
MOD17_021DD58C: ; 0x021DD58C
	ldr r3, _021DD590 ; =MOD17_021D7C1C
	bx r3
	.align 2, 0
_021DD590: .word MOD17_021D7C1C
	thumb_func_end MOD17_021DD58C

	thumb_func_start MOD17_021DD594
MOD17_021DD594: ; 0x021DD594
	mov r2, #0x96
	lsl r2, r2, #2
	str r1, [r0, r2]
	bx lr
	thumb_func_end MOD17_021DD594

	thumb_func_start MOD17_021DD59C
MOD17_021DD59C: ; 0x021DD59C
	str r1, [r0, #0x1c]
	bx lr
	thumb_func_end MOD17_021DD59C

	thumb_func_start MOD17_021DD5A0
MOD17_021DD5A0: ; 0x021DD5A0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r6, r2, #0
	mov r2, #0x61
	add r4, r1, #0
	lsl r2, r2, #2
	add r5, r0, #0
	add r1, r2, #0
	add r0, r5, r2
	str r6, [sp]
	add r1, #0xac
	add r2, #0xb0
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	add r3, r4, #0
	bl MOD17_021DA140
	mov r0, #0x95
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021DD5E8
	mov r3, #0x88
	ldr r0, [r5, #0x38]
	mov r1, #2
	mov r2, #0
	sub r3, r3, r4
	bl BgSetPosTextAndCommit
	mov r3, #0x10
	ldr r0, [r5, #0x38]
	mov r1, #2
	mov r2, #3
	sub r3, r3, r6
	bl BgSetPosTextAndCommit
_021DD5E8:
	mov r0, #0x23
	lsl r0, r0, #4
	str r4, [r5, r0]
	add r0, r0, #4
	str r6, [r5, r0]
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD5A0

	thumb_func_start MOD17_021DD5F8
MOD17_021DD5F8: ; 0x021DD5F8
	mov r3, #0x8e
	lsl r3, r3, #2
	str r1, [r0, r3]
	add r1, r3, #4
	str r2, [r0, r1]
	bx lr
	thumb_func_end MOD17_021DD5F8

	thumb_func_start MOD17_021DD604
MOD17_021DD604: ; 0x021DD604
	mov r2, #9
	lsl r2, r2, #6
	strh r1, [r0, r2]
	bx lr
	thumb_func_end MOD17_021DD604

	thumb_func_start MOD17_021DD60C
MOD17_021DD60C: ; 0x021DD60C
	push {r3, r4}
	mov r4, #0x91
	lsl r4, r4, #2
	str r1, [r0, r4]
	add r1, r4, #4
	str r2, [r0, r1]
	add r4, #8
	str r3, [r0, r4]
	pop {r3, r4}
	bx lr
	thumb_func_end MOD17_021DD60C

	thumb_func_start MOD17_021DD620
MOD17_021DD620: ; 0x021DD620
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0x7f
	lsl r0, r0, #2
	add r4, r1, #0
	add r6, r2, #0
	add r0, r5, r0
	add r1, sp, #8
	add r2, sp, #4
	bl MOD17_021DB878
	mov r0, #0x61
	lsl r0, r0, #2
	add r0, r5, r0
	add r1, sp, #0x10
	add r2, sp, #0xc
	bl MOD17_021DA348
	mov r0, #0x23
	lsl r0, r0, #4
	ldr r1, [sp, #0x10]
	ldr r2, [r5, r0]
	sub r1, r4, r1
	add r0, r0, #4
	add r7, r2, r1
	ldr r1, [r5, r0]
	ldr r0, [sp, #0xc]
	sub r0, r6, r0
	add r0, r1, r0
	str r0, [sp]
	ldr r2, [sp]
	add r0, r5, #0
	add r1, r7, #0
	bl MOD17_021DD5A0
	ldr r2, [sp]
	add r0, r5, #0
	sub r1, r4, r7
	sub r2, r6, r2
	bl MOD17_021DD5F8
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DD620

	thumb_func_start MOD17_021DD678
MOD17_021DD678: ; 0x021DD678
	push {r4, r5, r6, lr}
	add r4, r2, #0
	mov r2, #0x92
	add r5, r0, #0
	mov r0, #0x28
	lsl r2, r2, #2
	sub r0, r0, r3
	ldr r2, [r5, r2]
	lsl r0, r0, #0xc
	add r6, r1, #0
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	add r2, r0, #0
	add r0, r5, #0
	mov r5, #2
	add r3, r1, #0
	add r1, r6, #0
	mov r6, #0
	lsl r5, r5, #0xa
	add r5, r2, r5
	adc r3, r6
	lsl r2, r3, #0x14
	lsr r3, r5, #0xc
	orr r3, r2
	asr r2, r3, #0xc
	sub r2, r4, r2
	bl MOD17_021DD620
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD678

	thumb_func_start MOD17_021DD6B8
MOD17_021DD6B8: ; 0x021DD6B8
	mov r2, #0x25
	lsl r2, r2, #4
	strh r1, [r0, r2]
	sub r2, #0xcc
	ldr r3, _021DD6C8 ; =MOD17_021DA3D8
	add r0, r0, r2
	bx r3
	nop
_021DD6C8: .word MOD17_021DA3D8
	thumb_func_end MOD17_021DD6B8

	thumb_func_start MOD17_021DD6CC
MOD17_021DD6CC: ; 0x021DD6CC
	mov r2, #0x61
	lsl r2, r2, #2
	ldr r3, _021DD6D8 ; =MOD17_021DA1DC
	add r0, r0, r2
	bx r3
	nop
_021DD6D8: .word MOD17_021DA1DC
	thumb_func_end MOD17_021DD6CC

	thumb_func_start MOD17_021DD6DC
MOD17_021DD6DC: ; 0x021DD6DC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #0x97
	ldr r0, [r5, #0x68]
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x97
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	mov r0, #0x8b
	ldr r1, [r5, #0x68]
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [r5, #0x68]
	bl AllocMonZeroed
	mov r1, #0x8a
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r5]
	ldr r1, [r4, r1]
	bl FUN_02027CB8
	add r0, r4, #0
	add r1, r5, #0
	bl MOD17_021DD7F4
	ldr r1, [r5, #0x58]
	ldr r2, [r5, #0x68]
	add r0, r4, #0
	bl MOD17_021D7B94
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r2, [r5, #0x68]
	add r0, r4, r0
	mov r1, #0x15
	bl MOD17_021DB9F4
	ldr r1, [r5, #0x68]
	mov r0, #0x14
	bl MOD17_021D74E0
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r4, r1]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD17_021DD88C
	add r0, r4, #0
	add r1, r5, #0
	bl MOD17_021DD954
	mov r1, #0x83
	lsl r1, r1, #2
	add r0, r4, r1
	sub r1, #0x88
	ldr r2, [r5, #0x68]
	add r1, r4, r1
	bl MOD17_021DD464
	mov r0, #0x95
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r0, #4
	str r1, [r4, r0]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD17_021DD994
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DD6DC

	thumb_func_start MOD17_021DD778
MOD17_021DD778: ; 0x021DD778
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #0x97
	ldr r0, [r5, #0x68]
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x97
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	mov r0, #0x8b
	ldr r1, [r5, #0x68]
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [r5, #0x68]
	bl AllocMonZeroed
	mov r1, #0x8a
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r5]
	ldr r1, [r4, r1]
	bl FUN_02027CB8
	add r0, r4, #0
	add r1, r5, #0
	bl MOD17_021DD7F4
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r2, [r5, #0x68]
	add r0, r4, r0
	mov r1, #0x15
	bl MOD17_021DB9F4
	ldr r1, [r5, #0x68]
	mov r0, #0x14
	bl MOD17_021D74E0
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r4, r1]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD17_021DD88C
	mov r0, #0x95
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r1, #1
	add r0, r0, #4
	str r1, [r4, r0]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD17_021DD994
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD17_021DD778

	thumb_func_start MOD17_021DD7F4
MOD17_021DD7F4: ; 0x021DD7F4
	push {r3, r4, r5, lr}
	sub sp, #0x28
	add r4, r1, #0
	ldr r1, _021DD834 ; =0x000002CE
	add r5, r0, #0
	str r1, [sp]
	mov r1, #0x76
	str r1, [sp, #4]
	mov r1, #0x13
	str r1, [sp, #8]
	ldr r1, [r4, #0x68]
	str r1, [sp, #0xc]
	ldr r2, [r4, #0x68]
	add r1, sp, #0
	bl MOD17_021D7B68
	ldr r3, [r4, #0x68]
	add r0, r5, #0
	add r1, sp, #0x10
	add r2, r4, #0
	bl MOD17_021DDA8C
	add r0, r5, #0
	add r1, sp, #0x10
	bl MOD17_021D78A0
	add r0, sp, #0x10
	bl MOD17_021D7A24
	add sp, #0x28
	pop {r3, r4, r5, pc}
	nop
_021DD834: .word 0x000002CE
	thumb_func_end MOD17_021DD7F4

	thumb_func_start MOD17_021DD838
MOD17_021DD838: ; 0x021DD838
	push {r3, r4, lr}
	sub sp, #4
	mov r3, #0x91
	lsl r3, r3, #2
	add r1, r0, r3
	str r1, [sp]
	add r1, r3, #0
	sub r1, #0x14
	ldr r2, [r0, r1]
	add r1, r3, #0
	sub r1, #0xc
	ldr r1, [r0, r1]
	add r1, r2, r1
	add r2, r3, #0
	sub r2, #0x10
	ldr r4, [r0, r2]
	add r2, r3, #0
	sub r2, #8
	sub r3, r3, #4
	ldr r2, [r0, r2]
	ldrh r3, [r0, r3]
	add r2, r4, r2
	bl MOD17_021D7C28
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD17_021DD838

	thumb_func_start MOD17_021DD86C
MOD17_021DD86C: ; 0x021DD86C
	push {r4, lr}
	add r4, r0, #0
	bl MOD17_021D78BC
	add r0, r4, #0
	bl MOD17_021D7BE4
	mov r0, #0x95
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021DD88A
	add r0, r4, #0
	bl MOD17_021D7C10
_021DD88A:
	pop {r4, pc}
	thumb_func_end MOD17_021DD86C

	thumb_func_start MOD17_021DD88C
MOD17_021DD88C: ; 0x021DD88C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	add r5, r0, #0
	add r2, sp, #0x28
	mov r0, #0
	add r6, r1, #0
	add r3, r2, #0
	add r1, r0, #0
	stmia r3!, {r0, r1}
	stmia r3!, {r0, r1}
	stmia r3!, {r0, r1}
	stmia r3!, {r0, r1}
	str r0, [r3]
	ldr r0, [r5]
	str r0, [sp, #0x28]
	ldr r0, [r5, #4]
	str r0, [sp, #0x2c]
	ldr r0, [r5, #0x10]
	str r0, [sp, #0x30]
	ldr r0, [r5, #0x28]
	str r0, [sp, #0x34]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0x38]
	ldr r0, [r5, #0x38]
	str r0, [sp, #0x3c]
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	str r1, [sp, #0x40]
	add r1, r0, #0
	sub r1, #8
	add r1, r5, r1
	str r1, [sp, #0x44]
	mov r1, #0x15
	add r0, r0, #4
	str r1, [sp, #0x48]
	add r0, r5, r0
	add r1, r2, #0
	bl MOD17_021D9F80
	ldr r0, [r6]
	bl FUN_02027CA8
	add r7, r0, #0
	ldr r0, [r6]
	bl FUN_02027CB0
	add r4, r0, #0
	ldr r0, [r6]
	bl FUN_02027CA0
	str r4, [sp]
	str r0, [sp, #4]
	ldr r0, [r6, #0x68]
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [sp, #8]
	add r0, r5, r1
	add r1, #0xa4
	ldr r1, [r5, r1]
	add r2, sp, #0x18
	add r3, r7, #0
	bl MOD17_021D9FF0
	ldr r0, [r6, #0x54]
	mov r7, #0
	cmp r0, #0
	ble _021DD950
	add r4, r6, #0
_021DD916:
	ldr r0, [r4, #4]
	bl FUN_02027CF8
	str r0, [sp, #0xc]
	ldr r0, [r4, #4]
	bl FUN_02027CFC
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	bl FUN_02027D00
	str r0, [sp, #0x14]
	ldr r0, [r4, #4]
	bl FUN_02027D04
	str r0, [sp]
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	add r0, r5, r0
	bl MOD17_021DA064
	ldr r0, [r6, #0x54]
	add r7, r7, #1
	add r4, r4, #4
	cmp r7, r0
	blt _021DD916
_021DD950:
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DD88C

	thumb_func_start MOD17_021DD954
MOD17_021DD954: ; 0x021DD954
	add r2, r1, #0
	mov r1, #0x61
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r1, [r2, #0x5c]
	ldr r3, _021DD964 ; =MOD17_021DA2F0
	ldr r2, [r2, #0x68]
	bx r3
	.align 2, 0
_021DD964: .word MOD17_021DA2F0
	thumb_func_end MOD17_021DD954

	thumb_func_start MOD17_021DD968
MOD17_021DD968: ; 0x021DD968
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x61
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021DA100
	mov r0, #0x61
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD17_021D9FD4
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DD968

	thumb_func_start MOD17_021DD984
MOD17_021DD984: ; 0x021DD984
	mov r1, #0x61
	lsl r1, r1, #2
	ldr r3, _021DD990 ; =MOD17_021DA33C
	add r0, r0, r1
	bx r3
	nop
_021DD990: .word MOD17_021DA33C
	thumb_func_end MOD17_021DD984

	thumb_func_start MOD17_021DD994
MOD17_021DD994: ; 0x021DD994
	push {r3, r4, r5, lr}
	add r3, r1, #0
	mov r1, #0x23
	add r4, r0, #0
	mov r2, #0x48
	lsl r1, r1, #4
	str r2, [r4, r1]
	mov r5, #0x38
	add r2, r1, #4
	str r5, [r4, r2]
	add r2, r1, #0
	add r2, #8
	str r5, [r4, r2]
	add r2, r1, #0
	mov r5, #0x40
	add r2, #0xc
	str r5, [r4, r2]
	lsl r2, r5, #6
	add r5, r1, #0
	add r5, #0x14
	str r2, [r4, r5]
	add r5, r1, #0
	add r5, #0x18
	str r2, [r4, r5]
	add r5, r1, #0
	add r5, #0x1c
	str r2, [r4, r5]
	mov r2, #0
	add r1, #0x10
	strh r2, [r4, r1]
	ldr r1, [r3, #0x60]
	ldr r2, [r3, #0x64]
	bl MOD17_021DD5A0
	mov r0, #0x25
	ldr r1, _021DD9E4 ; =0x00007FFF
	lsl r0, r0, #4
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
	nop
_021DD9E4: .word 0x00007FFF
	thumb_func_end MOD17_021DD994

	thumb_func_start MOD17_021DD9E8
MOD17_021DD9E8: ; 0x021DD9E8
	ldr r2, [r1]
	str r2, [r0, #0x58]
	ldr r2, [r1, #4]
	str r2, [r0, #0x60]
	ldr r2, [r1, #8]
	str r2, [r0, #0x64]
	ldr r1, [r1, #0xc]
	str r1, [r0, #0x68]
	bx lr
	.align 2, 0
	thumb_func_end MOD17_021DD9E8

	thumb_func_start MOD17_021DD9FC
MOD17_021DD9FC: ; 0x021DD9FC
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r5, r0, #0
	add r0, r7, #0
	bl FUN_02027564
	add r6, r5, #0
	str r0, [r5]
	mov r4, #0
	str r4, [r5, #0x54]
	add r6, #0x54
_021DDA12:
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02027528
	cmp r0, #0
	beq _021DDA34
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02027590
	ldr r1, [r5, #0x54]
	lsl r1, r1, #2
	add r1, r5, r1
	str r0, [r1, #4]
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
_021DDA34:
	add r4, r4, #1
	cmp r4, #0xa
	blt _021DDA12
	add r0, r7, #0
	bl FUN_0202766C
	str r0, [r5, #0x5c]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DD9FC

	thumb_func_start MOD17_021DDA44
MOD17_021DDA44: ; 0x021DDA44
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r5, r0, #0
	add r0, r7, #0
	bl FUN_02027A94
	add r6, r5, #0
	str r0, [r5]
	mov r4, #0
	str r4, [r5, #0x54]
	add r6, #0x54
_021DDA5A:
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02027A14
	cmp r0, #0
	beq _021DDA7C
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02027AC4
	ldr r1, [r5, #0x54]
	lsl r1, r1, #2
	add r1, r5, r1
	str r0, [r1, #4]
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
_021DDA7C:
	add r4, r4, #1
	cmp r4, #0x14
	blt _021DDA5A
	add r0, r7, #0
	bl FUN_02027C28
	str r0, [r5, #0x5c]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DDA44

	thumb_func_start MOD17_021DDA8C
MOD17_021DDA8C: ; 0x021DDA8C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r7, r3, #0
	add r5, r0, #0
	add r6, r2, #0
	add r0, r4, #0
	add r1, r7, #0
	bl MOD17_021D7AFC
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	add r3, r7, #0
	bl MOD17_021DDAAC
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD17_021DDA8C

	thumb_func_start MOD17_021DDAAC
MOD17_021DDAAC: ; 0x021DDAAC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #0x10]
	add r0, r2, #0
	ldr r0, [r0, #0x54]
	add r4, r1, #0
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	cmp r0, #0
	ble _021DDB1E
	add r6, r2, #0
_021DDAC6:
	ldr r0, [r6, #4]
	bl FUN_02027CF8
	add r5, r0, #0
	ldr r0, [r4, #0x10]
	add r1, r5, #0
	bl FUN_02020CB0
	cmp r0, #1
	bne _021DDB0C
	mov r0, #1
	str r0, [sp]
	ldr r3, [sp, #0xc]
	mov r0, #0x19
	add r1, r5, #1
	mov r2, #0
	bl GfGfxLoader_LoadFromNarc
	add r7, r0, #0
	ldr r0, [r4, #0x10]
	add r1, r7, #0
	add r2, r5, #0
	bl FUN_02020CD4
	ldr r1, [r4]
	lsl r5, r5, #3
	add r1, r1, r5
	add r0, r7, #0
	add r1, r1, #4
	bl NNS_G2dGetUnpackedCharacterData
	ldr r0, [sp, #4]
	ldr r1, [r0]
	ldr r0, [r4]
	str r1, [r0, r5]
_021DDB0C:
	ldr r0, [sp, #0x10]
	add r6, r6, #4
	add r0, r0, #1
	str r0, [sp, #0x10]
	ldr r0, [sp, #8]
	ldr r1, [r0, #0x54]
	ldr r0, [sp, #0x10]
	cmp r0, r1
	blt _021DDAC6
_021DDB1E:
	mov r0, #1
	mov r1, #0
	str r0, [sp]
	ldr r3, [sp, #0xc]
	mov r0, #0x19
	add r2, r1, #0
	bl GfGfxLoader_LoadFromNarc
	add r5, r0, #0
	ldr r0, [r4, #0x14]
	add r1, r5, #0
	mov r2, #0
	bl FUN_02020CD4
	ldr r1, [r4, #8]
	add r0, r5, #0
	add r1, r1, #4
	bl NNS_G2dGetUnpackedPaletteData
	ldr r0, [sp, #4]
	ldr r1, [r0]
	ldr r0, [r4, #8]
	str r1, [r0]
	ldr r0, [r4, #8]
	mov r1, #3
	str r1, [r0, #8]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD17_021DDAAC

	thumb_func_start MOD17_021DDB58
MOD17_021DDB58: ; 0x021DDB58
	push {r3, r4, r5, lr}
	sub sp, #0x10
	mov r2, #2
	add r5, r0, #0
	mov r0, #3
	mov r1, #0xd
	lsl r2, r2, #0x10
	bl CreateHeap
	mov r2, #1
	mov r0, #3
	mov r1, #0xe
	lsl r2, r2, #0x12
	bl CreateHeap
	mov r1, #0x65
	add r0, r5, #0
	lsl r1, r1, #2
	mov r2, #0xd
	bl OverlayManager_CreateAndGetData
	mov r2, #0x65
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	ldr r0, _021DDC28 ; =MOD17_021DDD40
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	add r0, r5, #0
	bl OverlayManager_GetField18
	add r5, r0, #0
	ldr r0, [r5, #8]
	cmp r0, #0
	ldr r0, [r5]
	bne _021DDBB4
	ldr r1, [r5, #4]
	bl FUN_02027008
	str r0, [r4]
	b _021DDBBC
_021DDBB4:
	ldr r1, [r5, #4]
	bl FUN_02027044
	str r0, [r4, #4]
_021DDBBC:
	ldr r0, [r5, #4]
	str r0, [r4, #8]
	ldr r0, [r5, #8]
	str r0, [r4, #0xc]
	bl MOD17_021D7794
	ldr r0, _021DDC2C ; =gMain + 0x60
	mov r1, #0
	strb r1, [r0, #5]
	bl GX_SwapDisplay
	add r0, r4, #0
	add r0, #0x14
	mov r1, #0xe
	bl MOD17_021D7CC0
	ldr r0, [r4, #0x4c]
	str r0, [sp]
	mov r0, #0x48
	str r0, [sp, #4]
	mov r0, #0x10
	str r0, [sp, #8]
	mov r0, #0xe
	str r0, [sp, #0xc]
	ldr r0, [r4, #0xc]
	cmp r0, #0
	add r0, sp, #0
	bne _021DDBFC
	ldr r1, [r4]
	bl MOD17_021DD4AC
	b _021DDC02
_021DDBFC:
	ldr r1, [r4, #4]
	bl MOD17_021DD4D0
_021DDC02:
	str r0, [r4, #0x10]
	add r0, r4, #0
	bl MOD17_021DDD54
	add r0, r4, #0
	bl MOD17_021DDDFC
	add r0, r4, #0
	bl MOD17_021DDE50
	add r0, r4, #0
	bl MOD17_021DDF1C
	add r0, r4, #0
	bl MOD17_021DDFAC
	mov r0, #1
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DDC28: .word MOD17_021DDD40
_021DDC2C: .word gMain + 0x60
	thumb_func_end MOD17_021DDB58

	thumb_func_start MOD17_021DDC30
MOD17_021DDC30: ; 0x021DDC30
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	bl OverlayManager_GetData
	add r5, r0, #0
	bl FUN_020222AC
	bl NNS_G2dSetupSoftwareSpriteCamera
	ldr r0, [r5, #0x10]
	bl MOD17_021DD518
	mov r0, #0
	add r1, r0, #0
	bl FUN_020222B4
	add r5, #0x14
	add r0, r5, #0
	bl MOD17_021D7D00
	ldr r0, [r4]
	cmp r0, #5
	bhi _021DDCEA
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DDC6C: ; jump table
	.short _021DDC78 - _021DDC6C - 2 ; case 0
	.short _021DDC7E - _021DDC6C - 2 ; case 1
	.short _021DDC9C - _021DDC6C - 2 ; case 2
	.short _021DDCAC - _021DDC6C - 2 ; case 3
	.short _021DDCBC - _021DDC6C - 2 ; case 4
	.short _021DDCDC - _021DDC6C - 2 ; case 5
_021DDC78:
	add r0, r0, #1
	str r0, [r4]
	b _021DDCEA
_021DDC7E:
	mov r0, #6
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r0, #0xd
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #5
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DDCEA
_021DDC9C:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DDCEA
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DDCEA
_021DDCAC:
	ldr r1, _021DDCF0 ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #3
	tst r1, r2
	beq _021DDCEA
	add r0, r0, #1
	str r0, [r4]
	b _021DDCEA
_021DDCBC:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0xd
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #2
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DDCEA
_021DDCDC:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DDCEA
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021DDCEA:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_021DDCF0: .word gMain
	thumb_func_end MOD17_021DDC30

	thumb_func_start MOD17_021DDCF4
MOD17_021DDCF4: ; 0x021DDCF4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	bl MOD17_021DD540
	add r0, r4, #0
	bl MOD17_021DDEDC
	add r0, r4, #0
	bl MOD17_021DDF84
	add r4, #0x14
	add r0, r4, #0
	bl MOD17_021D7CD8
	bl MOD17_021D77B4
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0xd
	bl DestroyHeap
	mov r0, #0xe
	bl DestroyHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD17_021DDCF4

	thumb_func_start MOD17_021DDD40
MOD17_021DDD40: ; 0x021DDD40
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	bl MOD17_021DD58C
	add r4, #0x14
	add r0, r4, #0
	bl MOD17_021D7CF0
	pop {r4, pc}
	thumb_func_end MOD17_021DDD40

	thumb_func_start MOD17_021DDD54
MOD17_021DDD54: ; 0x021DDD54
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0x40
	str r0, [sp]
	mov r0, #0xe
	str r0, [sp, #4]
	mov r0, #0x19
	mov r1, #0x7e
	mov r2, #0
	mov r3, #0x60
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0xe
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x4c]
	mov r0, #0x19
	mov r1, #0x7d
	mov r3, #1
	bl GfGfxLoader_LoadCharData
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bne _021DDD92
	mov r1, #0x80
	mov r4, #4
	b _021DDD96
_021DDD92:
	mov r1, #0x7f
	mov r4, #3
_021DDD96:
	mov r0, #0xe
	str r0, [sp]
	mov r0, #0x19
	mov r2, #0
	add r3, sp, #0x10
	bl GfGfxLoader_GetScrnData
	ldr r2, [sp, #0x10]
	mov r3, #0
	str r3, [sp]
	add r6, r0, #0
	ldrh r0, [r2]
	mov r1, #1
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldrh r0, [r2, #2]
	add r2, #0xc
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [r5, #0x4c]
	bl LoadRectToBgTilemapRect
	ldr r1, [sp, #0x10]
	mov r2, #0
	ldrh r0, [r1]
	add r3, r2, #0
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp]
	ldrh r0, [r1, #2]
	mov r1, #1
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [r5, #0x4c]
	bl BgTilemapRectChangePalette
	add r0, r6, #0
	bl FreeToHeap
	ldr r0, [r5, #0x4c]
	mov r1, #1
	bl ScheduleBgTilemapBufferTransfer
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD17_021DDD54

	thumb_func_start MOD17_021DDDFC
MOD17_021DDDFC: ; 0x021DDDFC
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0xe
	str r0, [sp, #4]
	mov r0, #0xc
	add r1, r0, #0
	mov r2, #4
	mov r3, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xe
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x4c]
	mov r0, #0xc
	mov r1, #0xb
	mov r3, #4
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xe
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x4c]
	mov r0, #0xc
	mov r1, #0xa
	mov r3, #4
	bl GfGfxLoader_LoadCharData
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DDDFC

	thumb_func_start MOD17_021DDE50
MOD17_021DDE50: ; 0x021DDE50
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0xfa
	lsl r0, r0, #2
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x14
	mov r1, #0x19
	mov r2, #0xe9
	mov r3, #0
	bl MOD17_021D7934
	mov r0, #1
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0xfa
	lsl r0, r0, #2
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x14
	mov r1, #0x19
	mov r2, #0xea
	mov r3, #0
	bl MOD17_021D7954
	mov r0, #0xfa
	lsl r0, r0, #2
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x14
	mov r1, #0x19
	mov r2, #0xe8
	mov r3, #0
	bl MOD17_021D7978
	mov r0, #0xfa
	lsl r0, r0, #2
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x14
	mov r1, #0x19
	mov r2, #0xe7
	mov r3, #0
	bl MOD17_021D7994
	mov r0, #0x64
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0xfa
	add r0, #0x14
	lsl r1, r1, #2
	mov r2, #0
	mov r3, #0x90
	bl MOD17_021D78D0
	mov r1, #0x63
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #1
	bl FUN_02020238
	add sp, #0xc
	pop {r3, r4, pc}
	thumb_func_end MOD17_021DDE50

	thumb_func_start MOD17_021DDEDC
MOD17_021DDEDC: ; 0x021DDEDC
	push {r4, lr}
	mov r1, #0xfa
	add r4, r0, #0
	add r0, #0x14
	lsl r1, r1, #2
	bl MOD17_021D79B0
	add r0, r4, #0
	mov r1, #0xfa
	add r0, #0x14
	lsl r1, r1, #2
	bl MOD17_021D79C4
	add r0, r4, #0
	mov r1, #0xfa
	add r0, #0x14
	lsl r1, r1, #2
	bl MOD17_021D79D8
	add r0, r4, #0
	mov r1, #0xfa
	add r0, #0x14
	lsl r1, r1, #2
	bl MOD17_021D79EC
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FFC8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DDEDC

	thumb_func_start MOD17_021DDF1C
MOD17_021DDF1C: ; 0x021DDF1C
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0xe
	mov r1, #1
	bl AllocWindows
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [r4, r1]
	mov r0, #0x12
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #5
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x4c]
	ldr r1, [r4, r1]
	mov r2, #3
	mov r3, #0
	bl AddWindowParameterized
	mov r0, #0
	mov r1, #0xa0
	mov r2, #0xe
	bl FUN_02002ED0
	mov r0, #3
	mov r1, #0
	bl SetBgPriority
	mov r0, #0
	mov r1, #2
	bl SetBgPriority
	mov r0, #1
	add r1, r0, #0
	bl SetBgPriority
	mov r1, #3
	ldr r0, [r4, #0x4c]
	add r2, r1, #0
	mov r3, #0
	bl BgSetPosTextAndCommit
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DDF1C

	thumb_func_start MOD17_021DDF84
MOD17_021DDF84: ; 0x021DDF84
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl ClearWindowTilemapAndCopyToVram
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl RemoveWindow
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl WindowArray_dtor
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD17_021DDF84

	thumb_func_start MOD17_021DDFAC
MOD17_021DDFAC: ; 0x021DDFAC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, [r4, #0xc]
	cmp r0, #0
	bne _021DDFCA
	add r0, r4, #0
	bl MOD17_021DDFDC
	b _021DDFD0
_021DDFCA:
	add r0, r4, #0
	bl MOD17_021DE0F4
_021DDFD0:
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl CopyWindowToVram
	pop {r4, pc}
	thumb_func_end MOD17_021DDFAC

	thumb_func_start MOD17_021DDFDC
MOD17_021DDFDC: ; 0x021DDFDC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	ldr r2, _021DE0EC ; =0x00000151
	add r5, r0, #0
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0xd
	bl NewMsgDataFromNarc
	str r0, [sp, #0x10]
	cmp r0, #0
	bne _021DDFF8
	bl GF_AssertFail
_021DDFF8:
	mov r0, #0xd
	bl ScrStrBufs_new
	add r6, r0, #0
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #5
	bl FUN_02020130
	mov r0, #3
	lsl r0, r0, #0x10
	str r0, [sp, #0x14]
	mov r0, #9
	lsl r0, r0, #0x10
	str r0, [sp, #0x18]
	mov r0, #0
	str r0, [sp, #0x1c]
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, sp, #0x14
	bl FUN_02020044
	mov r0, #0xc
	mov r1, #0xd
	bl String_ctor
	add r7, r0, #0
	ldr r0, [r5]
	add r1, r7, #0
	bl FUN_02027608
	mov r0, #0
	add r1, r7, #0
	add r2, r0, #0
	bl FUN_02002E14
	add r4, r0, #0
	mov r0, #7
	str r0, [sp]
	mov r1, #0
	lsr r3, r4, #0x1f
	add r3, r4, r3
	asr r4, r3, #1
	mov r3, #0x80
	ldr r0, _021DE0F0 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x19
	str r1, [sp, #0xc]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r2, r7, #0
	sub r3, r3, r4
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	ldr r0, [r5]
	bl FUN_0202769C
	add r2, r0, #0
	add r0, r6, #0
	mov r1, #0
	bl FUN_0200B518
	mov r0, #0xc8
	mov r1, #0xd
	bl String_ctor
	add r4, r0, #0
	ldr r0, [sp, #0x10]
	mov r1, #0x2d
	bl NewString_ReadMsgData
	add r7, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	add r2, r7, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r0, #0x1b
	str r0, [sp]
	mov r1, #0
	ldr r0, _021DE0F0 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x19
	str r1, [sp, #0xc]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	lsr r5, r3, #0x1f
	add r5, r3, r5
	asr r5, r5, #1
	mov r3, #0x80
	add r2, r4, #0
	sub r3, r3, r5
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	add r0, r7, #0
	bl String_dtor
	ldr r0, [sp, #0x10]
	bl DestroyMsgData
	add r0, r6, #0
	bl ScrStrBufs_delete
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DE0EC: .word 0x00000151
_021DE0F0: .word 0x00010200
	thumb_func_end MOD17_021DDFDC

	thumb_func_start MOD17_021DE0F4
MOD17_021DE0F4: ; 0x021DE0F4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, #8]
	bl FUN_02020130
	ldr r0, [r5, #4]
	bl FUN_02027C58
	add r6, r0, #0
	mov r0, #0xd
	bl ScrStrBufs_new
	add r7, r0, #0
	mov r0, #0xc8
	mov r1, #0xd
	bl String_ctor
	add r4, r0, #0
	ldr r0, [r5, #8]
	bl FUN_02083298
	add r2, r0, #0
	add r0, r7, #0
	mov r1, #0
	bl BufferContestMessage2
	add r0, r6, #0
	bl FUN_02083268
	add r2, r0, #0
	add r0, r7, #0
	mov r1, #1
	bl BufferContestMessage
	ldr r0, [r5, #4]
	bl FUN_02027B44
	add r6, r0, #0
	ldr r0, [r5, #4]
	add r1, r4, #0
	bl FUN_02027B0C
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r0, r7, #0
	mov r1, #3
	add r2, r4, #0
	add r3, r6, #0
	bl BufferString
	mov r0, #0xd
	bl AllocMonZeroed
	add r6, r0, #0
	ldr r0, [r5, #4]
	add r1, r6, #0
	bl FUN_02027B78
	add r0, r6, #0
	bl FUN_020690E4
	add r2, r0, #0
	add r0, r7, #0
	mov r1, #4
	bl BufferBoxMonNickname
	add r0, r6, #0
	bl FreeToHeap
	ldr r2, _021DE24C ; =0x00000151
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0xd
	bl NewMsgDataFromNarc
	str r0, [sp, #0x10]
	cmp r0, #0
	bne _021DE1A0
	bl GF_AssertFail
_021DE1A0:
	ldr r0, [sp, #0x10]
	mov r1, #0x2b
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r7, #0
	add r1, r4, #0
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r0, #7
	str r0, [sp]
	mov r1, #0
	lsr r6, r3, #0x1f
	add r6, r3, r6
	ldr r0, _021DE250 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x19
	str r1, [sp, #0xc]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	asr r6, r6, #1
	mov r3, #0x80
	add r2, r4, #0
	sub r3, r3, r6
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	mov r1, #0x2c
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r7, #0
	add r1, r4, #0
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r0, #0x1b
	str r0, [sp]
	mov r1, #0
	ldr r0, _021DE250 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x19
	str r1, [sp, #0xc]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	lsr r5, r3, #0x1f
	add r5, r3, r5
	asr r5, r5, #1
	mov r3, #0x80
	add r2, r4, #0
	sub r3, r3, r5
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	ldr r0, [sp, #0x10]
	bl DestroyMsgData
	add r0, r7, #0
	bl ScrStrBufs_delete
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021DE24C: .word 0x00000151
_021DE250: .word 0x00010200
	thumb_func_end MOD17_021DE0F4

	.rodata
	.global MOD17_021DE254
MOD17_021DE254: ; 0x021DE254
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD17_021DE264
MOD17_021DE264: ; 0x021DE264
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00

	.global MOD17_021DE274
MOD17_021DE274: ; 0x021DE274
	.byte 0xCE, 0x02, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00

	.global MOD17_021DE284
MOD17_021DE284: ; 0x021DE284
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0F, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD17_021DE2A0
MOD17_021DE2A0: ; 0x021DE2A0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD17_021DE2BC
MOD17_021DE2BC: ; 0x021DE2BC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD17_021DE2D8
MOD17_021DE2D8: ; 0x021DE2D8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD17_021DE2F4
MOD17_021DE2F4: ; 0x021DE2F4
	.byte 0x00, 0x00, 0x00, 0x00, 0x6F, 0xFF, 0xFF, 0xFF, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x02, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD17_021DE310
MOD17_021DE310: ; 0x021DE310
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD17_021DE32C
MOD17_021DE32C: ; 0x021DE32C
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.data
	.bss
