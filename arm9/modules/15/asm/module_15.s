	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD15_021D74E0
MOD15_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #0
	beq _021D74F2
	cmp r1, #1
	beq _021D752A
	b _021D7552
_021D74F2:
	mov r1, #0
	mov r0, #0x3e
	add r2, r1, #0
	bl FUN_0200433C
	mov r2, #2
	mov r0, #3
	mov r1, #0x22
	lsl r2, r2, #0xe
	bl FUN_0201681C
	mov r2, #0xa
	mov r0, #3
	mov r1, #0x23
	lsl r2, r2, #0xe
	bl FUN_0201681C
	add r0, r5, #0
	bl MOD15_021D7628
	ldr r0, [r0, #0x14]
	mov r1, #0
	bl MOD15_021D8900
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D7552
_021D752A:
	bl FUN_02006278
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D7552
	ldr r0, [r4, #4]
	cmp r0, #2
	bne _021D7548
	ldr r0, [r4, #0x14]
	bl MOD15_021D9538
	b _021D754A
_021D7548:
	mov r0, #0
_021D754A:
	add r4, #0x64
	strb r0, [r4]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D7552:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D7558
MOD15_021D7558: ; 0x021D7558
	push {r4, lr}
	bl FUN_02006278
	add r4, r0, #0
	ldr r0, _021D7594 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	strh r1, [r4, #0x30]
	ldr r1, [r0, #0x44]
	strh r1, [r4, #0x32]
	ldr r0, [r0, #0x4c]
	strh r0, [r4, #0x34]
	ldr r0, [r4, #0x40]
	bl FUN_02022144
	ldr r2, [r4, #0x2c]
	cmp r2, #0
	beq _021D7586
	add r0, r4, #0
	add r4, #0x28
	add r1, r4, #0
	blx r2
	mov r0, #0
	pop {r4, pc}
_021D7586:
	add r1, r4, #0
	ldr r2, [r4, #0x20]
	add r0, r4, #0
	add r1, #0x1c
	blx r2
	pop {r4, pc}
	nop
_021D7594: .word gUnknown21C48B8

	thumb_func_start MOD15_021D7598
MOD15_021D7598: ; 0x021D7598
	push {r4, lr}
	add r4, r2, #0
	cmp r1, #3
	bhi _021D7600
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D75AC: ; jump table
	.short _021D75B4 - _021D75AC - 2 ; case 0
	.short _021D75D4 - _021D75AC - 2 ; case 1
	.short _021D75F6 - _021D75AC - 2 ; case 2
	.short _021D75D4 - _021D75AC - 2 ; case 3
_021D75B4:
	str r0, [r4, #0x38]
	cmp r0, #2
	beq _021D75C0
	cmp r0, #3
	beq _021D75CA
	pop {r4, pc}
_021D75C0:
	ldr r0, [r4, #0x14]
	mov r1, #0x19
	bl MOD15_021D8900
	pop {r4, pc}
_021D75CA:
	ldr r0, [r4, #0x14]
	mov r1, #0x1a
	bl MOD15_021D8900
	pop {r4, pc}
_021D75D4:
	cmp r0, #2
	beq _021D75DE
	cmp r0, #3
	beq _021D75E8
	b _021D75F0
_021D75DE:
	ldr r0, [r4, #0x14]
	mov r1, #0x1b
	bl MOD15_021D8900
	b _021D75F0
_021D75E8:
	ldr r0, [r4, #0x14]
	mov r1, #0x1c
	bl MOD15_021D8900
_021D75F0:
	mov r0, #4
	str r0, [r4, #0x38]
	pop {r4, pc}
_021D75F6:
	sub r1, r0, #2
	cmp r1, #1
	bhi _021D7604
	str r0, [r4, #0x38]
	pop {r4, pc}
_021D7600:
	mov r0, #4
	str r0, [r4, #0x38]
_021D7604:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021D7608
MOD15_021D7608: ; 0x021D7608
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02006278
	add r1, r4, #0
	bl MOD15_021D7774
	mov r0, #0x22
	bl FUN_020168D0
	mov r0, #0x23
	bl FUN_020168D0
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021D7628
MOD15_021D7628: ; 0x021D7628
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #0x68
	mov r2, #0x22
	bl FUN_02006268
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_0200628C
	str r0, [r4]
	bl FUN_0208540C
	str r0, [r4, #4]
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4]
	add r1, #0x10
	add r2, #8
	bl FUN_02085428
	ldr r0, [r4, #4]
	cmp r0, #2
	bne _021D7664
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x60
	add r1, #8
	bl MOD15_021D76C4
_021D7664:
	ldr r1, [r4]
	mov r0, #0x22
	bl FUN_02088F0C
	str r0, [r4, #0x18]
	ldr r1, [r4, #0x18]
	add r0, r4, #0
	bl MOD15_021D87F8
	str r0, [r4, #0x14]
	mov r0, #0x22
	str r0, [sp]
	ldr r0, _021D76B4 ; =0x021DB880
	ldr r2, _021D76B8 ; =MOD15_021D7598
	mov r1, #5
	add r3, r4, #0
	bl FUN_020220C4
	str r0, [r4, #0x40]
	mov r1, #0
	str r1, [r4, #0x44]
	add r0, r4, #0
	str r1, [r4, #0x48]
	add r0, #0x65
	strb r1, [r0]
	str r1, [r4, #0x2c]
	ldr r0, _021D76BC ; =MOD15_021D779C
	str r1, [r4, #0x28]
	str r0, [r4, #0x20]
	add r0, r4, #0
	str r1, [r4, #0x1c]
	add r0, #0x4e
	strh r1, [r0]
	ldr r1, _021D76C0 ; =MOD15_021D83BC
	add r0, r4, #0
	bl MOD15_021D83AC
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D76B4: .word MOD15_021DB880
_021D76B8: .word MOD15_021D7598
_021D76BC: .word MOD15_021D779C
_021D76C0: .word MOD15_021D83BC

	thumb_func_start MOD15_021D76C4
MOD15_021D76C4: ; 0x021D76C4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_02013920
	strh r0, [r5]
	mov r0, #0
	ldrsh r0, [r5, r0]
	bl FUN_02013974
	strb r0, [r5, #3]
	add r0, r4, #0
	bl FUN_02013924
	strb r0, [r5, #2]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D76E8
MOD15_021D76E8: ; 0x021D76E8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #2
	add r4, r1, #0
	ldrsb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, #2]
	ldrsb r1, [r5, r0]
	mov r0, #3
	ldrsb r0, [r5, r0]
	cmp r1, r0
	blt _021D771C
	mov r1, #0
	strb r1, [r5, #2]
	ldrsh r0, [r5, r1]
	add r0, r0, #1
	strh r0, [r5]
	ldrsh r0, [r5, r1]
	cmp r0, #5
	blt _021D7712
	strh r1, [r5]
_021D7712:
	mov r0, #0
	ldrsh r0, [r5, r0]
	bl FUN_02013974
	strb r0, [r5, #3]
_021D771C:
	mov r1, #0
	mov r2, #2
	ldrsh r1, [r5, r1]
	ldrsb r2, [r5, r2]
	add r0, r4, #0
	bl FUN_02013980
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D772C
MOD15_021D772C: ; 0x021D772C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #2
	add r4, r1, #0
	ldrsb r1, [r5, r0]
	sub r1, r1, #1
	strb r1, [r5, #2]
	ldrsb r0, [r5, r0]
	cmp r0, #0
	bge _021D7764
	mov r0, #0
	ldrsh r1, [r5, r0]
	sub r1, r1, #1
	strh r1, [r5]
	ldrsh r0, [r5, r0]
	cmp r0, #0
	bge _021D7752
	mov r0, #4
	strh r0, [r5]
_021D7752:
	mov r0, #0
	ldrsh r0, [r5, r0]
	bl FUN_02013974
	strb r0, [r5, #3]
	mov r0, #3
	ldrsb r0, [r5, r0]
	sub r0, r0, #1
	strb r0, [r5, #2]
_021D7764:
	mov r1, #0
	mov r2, #2
	ldrsh r1, [r5, r1]
	ldrsb r2, [r5, r2]
	add r0, r4, #0
	bl FUN_02013980
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D7774
MOD15_021D7774: ; 0x021D7774
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x40]
	add r4, r1, #0
	bl FUN_0202212C
	ldr r0, [r5, #0x14]
	bl MOD15_021D8888
	ldr r0, [r5, #0x18]
	bl FUN_02088F4C
	add r0, r4, #0
	bl FUN_0200627C
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D7794
MOD15_021D7794: ; 0x021D7794
	str r1, [r0, #0x20]
	mov r1, #0
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start MOD15_021D779C
MOD15_021D779C: ; 0x021D779C
	push {r3, lr}
	ldr r2, [r0, #4]
	lsl r3, r2, #2
	ldr r2, _021D77AC ; =0x021DB874
	ldr r2, [r2, r3]
	blx r2
	pop {r3, pc}
	nop
_021D77AC: .word MOD15_021DB874

	thumb_func_start MOD15_021D77B0
MOD15_021D77B0: ; 0x021D77B0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021D77C6
	cmp r0, #1
	beq _021D7850
	cmp r0, #2
	beq _021D7864
	b _021D7876
_021D77C6:
	ldr r1, [r5, #0x38]
	cmp r1, #0
	bne _021D77D6
	add r0, r5, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #0
	bne _021D77EC
_021D77D6:
	cmp r1, #1
	bne _021D77E4
	add r0, r5, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #1
	bne _021D77EC
_021D77E4:
	ldrh r0, [r5, #0x30]
	mov r1, #4
	tst r1, r0
	beq _021D77F6
_021D77EC:
	ldr r1, _021D787C ; =MOD15_021D8698
	add r0, r5, #0
	bl MOD15_021D83AC
	b _021D7876
_021D77F6:
	mov r1, #0x88
	tst r1, r0
	beq _021D7818
	ldr r0, _021D7880 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	mov r1, #0
	add r0, #0x4c
	strh r1, [r0]
	ldr r0, [r5, #0x14]
	mov r1, #4
	bl MOD15_021D8900
	mov r0, #1
	str r0, [r4]
	b _021D7876
_021D7818:
	mov r1, #2
	tst r1, r0
	beq _021D782E
	ldr r0, _021D7880 ; =0x000005DC
	bl FUN_020054C8
	ldr r1, _021D7884 ; =MOD15_021D851C
	add r0, r5, #0
	bl MOD15_021D83AC
	b _021D7876
_021D782E:
	mov r1, #1
	tst r0, r1
	beq _021D7876
	ldr r0, _021D7880 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	mov r1, #0
	add r0, #0x50
	strh r1, [r0]
	ldr r0, [r5, #0x14]
	mov r1, #6
	bl MOD15_021D8900
	mov r0, #2
	str r0, [r4]
	b _021D7876
_021D7850:
	ldr r0, [r5, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D7876
	ldr r1, _021D7888 ; =MOD15_021D7BC8
	add r0, r5, #0
	bl MOD15_021D7794
	b _021D7876
_021D7864:
	ldr r0, [r5, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D7876
	ldr r1, _021D788C ; =MOD15_021D7D00
	add r0, r5, #0
	bl MOD15_021D7794
_021D7876:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D787C: .word MOD15_021D8698
_021D7880: .word 0x000005DC
_021D7884: .word MOD15_021D851C
_021D7888: .word MOD15_021D7BC8
_021D788C: .word MOD15_021D7D00

	thumb_func_start MOD15_021D7890
MOD15_021D7890: ; 0x021D7890
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021D78A6
	cmp r0, #1
	beq _021D7980
	cmp r0, #2
	beq _021D7994
	b _021D79A6
_021D78A6:
	ldr r1, [r5, #0x38]
	cmp r1, #0
	bne _021D78B6
	add r0, r5, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #0
	bne _021D78CC
_021D78B6:
	cmp r1, #1
	bne _021D78C4
	add r0, r5, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #1
	bne _021D78CC
_021D78C4:
	ldrh r0, [r5, #0x30]
	mov r1, #4
	tst r1, r0
	beq _021D78D6
_021D78CC:
	ldr r1, _021D79AC ; =MOD15_021D8698
	add r0, r5, #0
	bl MOD15_021D83AC
	b _021D79A6
_021D78D6:
	mov r1, #0x88
	tst r1, r0
	beq _021D78F8
	ldr r0, _021D79B0 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	mov r1, #0
	add r0, #0x4c
	strh r1, [r0]
	ldr r0, [r5, #0x14]
	mov r1, #4
	bl MOD15_021D8900
	mov r0, #1
	str r0, [r4]
	b _021D79A6
_021D78F8:
	mov r1, #0x20
	tst r1, r0
	beq _021D7920
	add r0, r5, #0
	add r0, #0x4e
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D79A6
	ldr r0, _021D79B0 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	mov r1, #0
	add r0, #0x4e
	strh r1, [r0]
	ldr r0, [r5, #0x14]
	mov r1, #0xc
	bl MOD15_021D8900
	b _021D79A6
_021D7920:
	mov r1, #0x10
	tst r1, r0
	beq _021D7948
	add r0, r5, #0
	add r0, #0x4e
	ldrh r0, [r0]
	cmp r0, #0
	bne _021D79A6
	ldr r0, _021D79B0 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	mov r1, #1
	add r0, #0x4e
	strh r1, [r0]
	ldr r0, [r5, #0x14]
	mov r1, #0xc
	bl MOD15_021D8900
	b _021D79A6
_021D7948:
	mov r1, #2
	tst r1, r0
	beq _021D795E
	ldr r0, _021D79B0 ; =0x000005DC
	bl FUN_020054C8
	ldr r1, _021D79B4 ; =MOD15_021D851C
	add r0, r5, #0
	bl MOD15_021D83AC
	b _021D79A6
_021D795E:
	mov r1, #1
	tst r0, r1
	beq _021D79A6
	ldr r0, _021D79B0 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	mov r1, #0
	add r0, #0x50
	strh r1, [r0]
	ldr r0, [r5, #0x14]
	mov r1, #6
	bl MOD15_021D8900
	mov r0, #2
	str r0, [r4]
	b _021D79A6
_021D7980:
	ldr r0, [r5, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D79A6
	ldr r1, _021D79B8 ; =MOD15_021D7BC8
	add r0, r5, #0
	bl MOD15_021D7794
	b _021D79A6
_021D7994:
	ldr r0, [r5, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D79A6
	ldr r1, _021D79BC ; =MOD15_021D7D00
	add r0, r5, #0
	bl MOD15_021D7794
_021D79A6:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D79AC: .word MOD15_021D8698
_021D79B0: .word 0x000005DC
_021D79B4: .word MOD15_021D851C
_021D79B8: .word MOD15_021D7BC8
_021D79BC: .word MOD15_021D7D00

	thumb_func_start MOD15_021D79C0
MOD15_021D79C0: ; 0x021D79C0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #4
	bhi _021D7A3C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D79D8: ; jump table
	.short _021D79E2 - _021D79D8 - 2 ; case 0
	.short _021D79F2 - _021D79D8 - 2 ; case 1
	.short _021D7B76 - _021D79D8 - 2 ; case 2
	.short _021D7B88 - _021D79D8 - 2 ; case 3
	.short _021D7B9C - _021D79D8 - 2 ; case 4
_021D79E2:
	ldr r0, [r4, #0x14]
	bl MOD15_021D9538
	add r1, r4, #0
	add r1, #0x64
	strb r0, [r1]
	mov r0, #1
	str r0, [r5]
_021D79F2:
	ldr r1, [r4, #0x38]
	cmp r1, #0
	bne _021D7A02
	add r0, r4, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #0
	bne _021D7A18
_021D7A02:
	cmp r1, #1
	bne _021D7A10
	add r0, r4, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #1
	bne _021D7A18
_021D7A10:
	ldrh r0, [r4, #0x30]
	mov r1, #4
	tst r1, r0
	beq _021D7A22
_021D7A18:
	ldr r1, _021D7BB4 ; =MOD15_021D8698
	add r0, r4, #0
	bl MOD15_021D83AC
	b _021D7BAE
_021D7A22:
	mov r1, #0x40
	tst r1, r0
	beq _021D7A5C
	add r0, r4, #0
	add r0, #0x64
	ldrb r0, [r0]
	cmp r0, #0
	beq _021D7A3C
	add r0, r4, #0
	add r0, #0x4e
	ldrh r0, [r0]
	cmp r0, #0
	bne _021D7A3E
_021D7A3C:
	b _021D7BAE
_021D7A3E:
	ldr r0, _021D7BB8 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	add r0, #0x4e
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0x4e
	strh r1, [r0]
	ldr r0, [r4, #0x14]
	mov r1, #0xc
	bl MOD15_021D8900
	b _021D7BAE
_021D7A5C:
	mov r1, #0x80
	tst r0, r1
	beq _021D7AAC
	ldr r0, _021D7BB8 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	add r0, #0x64
	ldrb r2, [r0]
	cmp r2, #0
	beq _021D7A96
	add r0, r4, #0
	add r0, #0x4e
	ldrh r1, [r0]
	sub r0, r2, #1
	cmp r1, r0
	bge _021D7A96
	add r0, r4, #0
	add r0, #0x4e
	ldrh r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x4e
	strh r1, [r0]
	ldr r0, [r4, #0x14]
	mov r1, #0xc
	bl MOD15_021D8900
	b _021D7AAC
_021D7A96:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x4c
	strh r1, [r0]
	ldr r0, [r4, #0x14]
	mov r1, #4
	bl MOD15_021D8900
	mov r0, #3
	str r0, [r5]
	b _021D7BAE
_021D7AAC:
	ldrh r1, [r4, #0x30]
	mov r0, #8
	tst r0, r1
	bne _021D7AC6
	mov r0, #1
	add r2, r1, #0
	and r2, r0
	beq _021D7AE2
	add r0, r4, #0
	add r0, #0x64
	ldrb r0, [r0]
	cmp r0, #0
	bne _021D7AE2
_021D7AC6:
	ldr r0, _021D7BB8 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0
	add r0, #0x4c
	strh r1, [r0]
	ldr r0, [r4, #0x14]
	mov r1, #4
	bl MOD15_021D8900
	mov r0, #3
	str r0, [r5]
	b _021D7BAE
_021D7AE2:
	ldrh r0, [r4, #0x34]
	mov r3, #0x20
	tst r3, r0
	beq _021D7B12
	ldr r0, _021D7BB8 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0
	add r0, #0x4e
	strh r1, [r0]
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x60
	add r1, #8
	bl MOD15_021D772C
	ldr r0, [r4, #0x14]
	mov r1, #3
	bl MOD15_021D8900
	mov r0, #2
	str r0, [r5]
	b _021D7BAE
_021D7B12:
	mov r3, #0x10
	tst r0, r3
	beq _021D7B40
	ldr r0, _021D7BB8 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0
	add r0, #0x4e
	strh r1, [r0]
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x60
	add r1, #8
	bl MOD15_021D76E8
	ldr r0, [r4, #0x14]
	mov r1, #3
	bl MOD15_021D8900
	mov r0, #2
	str r0, [r5]
	b _021D7BAE
_021D7B40:
	mov r0, #2
	tst r0, r1
	beq _021D7B56
	ldr r0, _021D7BB8 ; =0x000005DC
	bl FUN_020054C8
	ldr r1, _021D7BBC ; =MOD15_021D851C
	add r0, r4, #0
	bl MOD15_021D83AC
	b _021D7BAE
_021D7B56:
	cmp r2, #0
	beq _021D7BAE
	ldr r0, _021D7BB8 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0
	add r0, #0x50
	strh r1, [r0]
	ldr r0, [r4, #0x14]
	mov r1, #6
	bl MOD15_021D8900
	mov r0, #4
	str r0, [r5]
	b _021D7BAE
_021D7B76:
	ldr r0, [r4, #0x14]
	mov r1, #3
	bl MOD15_021D8970
	cmp r0, #0
	beq _021D7BAE
	mov r0, #0
	str r0, [r5]
	b _021D7BAE
_021D7B88:
	ldr r0, [r4, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D7BAE
	ldr r1, _021D7BC0 ; =MOD15_021D7BC8
	add r0, r4, #0
	bl MOD15_021D7794
	b _021D7BAE
_021D7B9C:
	ldr r0, [r4, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D7BAE
	ldr r1, _021D7BC4 ; =MOD15_021D7D00
	add r0, r4, #0
	bl MOD15_021D7794
_021D7BAE:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D7BB4: .word MOD15_021D8698
_021D7BB8: .word 0x000005DC
_021D7BBC: .word MOD15_021D851C
_021D7BC0: .word MOD15_021D7BC8
_021D7BC4: .word MOD15_021D7D00

	thumb_func_start MOD15_021D7BC8
MOD15_021D7BC8: ; 0x021D7BC8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #5
	bls _021D7BD6
	b _021D7CE8
_021D7BD6:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7BE2: ; jump table
	.short _021D7BEE - _021D7BE2 - 2 ; case 0
	.short _021D7CB8 - _021D7BE2 - 2 ; case 1
	.short _021D7CC4 - _021D7BE2 - 2 ; case 2
	.short _021D7CD0 - _021D7BE2 - 2 ; case 3
	.short _021D7CD0 - _021D7BE2 - 2 ; case 4
	.short _021D7CD6 - _021D7BE2 - 2 ; case 5
_021D7BEE:
	ldr r0, [r4, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D7CE8
	ldr r1, [r4, #0x38]
	cmp r1, #0
	bne _021D7C08
	add r0, r4, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #0
	bne _021D7C1E
_021D7C08:
	cmp r1, #1
	bne _021D7C16
	add r0, r4, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #1
	bne _021D7C1E
_021D7C16:
	ldrh r0, [r4, #0x30]
	mov r1, #4
	tst r1, r0
	beq _021D7C28
_021D7C1E:
	ldr r1, _021D7CEC ; =MOD15_021D8698
	add r0, r4, #0
	bl MOD15_021D83AC
	b _021D7CE8
_021D7C28:
	mov r1, #0x30
	tst r1, r0
	beq _021D7C4E
	ldr r0, _021D7CF0 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	add r0, #0x4c
	ldrh r1, [r0]
	mov r0, #1
	eor r1, r0
	add r0, r4, #0
	add r0, #0x4c
	strh r1, [r0]
	ldr r0, [r4, #0x14]
	mov r1, #0xd
	bl MOD15_021D8900
	b _021D7CE8
_021D7C4E:
	mov r1, #8
	tst r1, r0
	beq _021D7C6C
	ldr r0, _021D7CF0 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0
	add r0, #0x4c
	strh r1, [r0]
	ldr r0, [r4, #0x14]
	mov r1, #0xd
	bl MOD15_021D8900
	b _021D7CE8
_021D7C6C:
	mov r1, #0x40
	tst r1, r0
	beq _021D7C86
	ldr r0, _021D7CF0 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #0x14]
	mov r1, #5
	bl MOD15_021D8900
	mov r0, #5
	str r0, [r5]
	b _021D7CE8
_021D7C86:
	mov r1, #1
	tst r1, r0
	beq _021D7CA6
	ldr r0, _021D7CF0 ; =0x000005DC
	bl FUN_020054C8
	add r4, #0x4c
	ldrh r0, [r4]
	cmp r0, #0
	bne _021D7CA0
	mov r0, #1
	str r0, [r5]
	b _021D7CE8
_021D7CA0:
	mov r0, #2
	str r0, [r5]
	b _021D7CE8
_021D7CA6:
	mov r1, #2
	tst r0, r1
	beq _021D7CE8
	ldr r0, _021D7CF0 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #2
	str r0, [r5]
	b _021D7CE8
_021D7CB8:
	mov r1, #3
	str r1, [r5]
	ldr r1, _021D7CF4 ; =MOD15_021D83F0
	bl MOD15_021D83AC
	b _021D7CE8
_021D7CC4:
	mov r1, #4
	str r1, [r5]
	ldr r1, _021D7CF8 ; =MOD15_021D851C
	bl MOD15_021D83AC
	b _021D7CE8
_021D7CD0:
	mov r0, #0
	str r0, [r5]
	b _021D7CE8
_021D7CD6:
	ldr r0, [r4, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D7CE8
	ldr r1, _021D7CFC ; =MOD15_021D779C
	add r0, r4, #0
	bl MOD15_021D7794
_021D7CE8:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7CEC: .word MOD15_021D8698
_021D7CF0: .word 0x000005DC
_021D7CF4: .word MOD15_021D83F0
_021D7CF8: .word MOD15_021D851C
_021D7CFC: .word MOD15_021D779C

	thumb_func_start MOD15_021D7D00
MOD15_021D7D00: ; 0x021D7D00
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021D7D18
	cmp r0, #1
	beq _021D7E0C
	cmp r0, #2
	bne _021D7D16
	b _021D7E20
_021D7D16:
	b _021D7E30
_021D7D18:
	ldr r0, [r5, #0x14]
	mov r1, #0xf
	bl MOD15_021D8970
	cmp r0, #0
	bne _021D7D26
	b _021D7E30
_021D7D26:
	ldr r1, [r5, #0x38]
	cmp r1, #0
	bne _021D7D36
	add r0, r5, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #0
	bne _021D7D4C
_021D7D36:
	cmp r1, #1
	bne _021D7D44
	add r0, r5, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #1
	bne _021D7D4C
_021D7D44:
	ldrh r0, [r5, #0x30]
	mov r1, #4
	tst r1, r0
	beq _021D7D78
_021D7D4C:
	ldr r0, _021D7E34 ; =0x000005E4
	bl FUN_020054C8
	add r0, r5, #0
	add r0, #0x65
	ldrb r1, [r0]
	mov r0, #1
	eor r1, r0
	add r0, r5, #0
	add r0, #0x65
	strb r1, [r0]
	add r0, r5, #0
	mov r1, #0
	add r0, #0x50
	strh r1, [r0]
	ldr r0, [r5, #0x14]
	mov r1, #0x18
	bl MOD15_021D8900
	mov r0, #2
	str r0, [r4]
	b _021D7E30
_021D7D78:
	mov r1, #2
	tst r1, r0
	beq _021D7D96
	ldr r0, _021D7E38 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r5, #0x14]
	mov r1, #7
	bl MOD15_021D8900
	ldr r0, _021D7E3C ; =MOD15_021D779C
	str r0, [r5, #0x24]
	mov r0, #1
	str r0, [r4]
	b _021D7E30
_021D7D96:
	mov r1, #1
	tst r0, r1
	beq _021D7DF2
	add r0, r5, #0
	add r0, #0x50
	ldrh r0, [r0]
	cmp r0, #0xfe
	bne _021D7DBE
	ldr r0, _021D7E38 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r5, #0x14]
	mov r1, #7
	bl MOD15_021D8900
	ldr r0, _021D7E3C ; =MOD15_021D779C
	str r0, [r5, #0x24]
	mov r0, #1
	str r0, [r4]
	b _021D7E30
_021D7DBE:
	add r0, r5, #0
	bl MOD15_021D7E48
	cmp r0, #0
	beq _021D7DEA
	ldr r0, _021D7E38 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	add r0, #0x54
	add r1, r5, #0
	bl MOD15_021D7FE4
	ldr r0, _021D7E40 ; =MOD15_021D8044
	mov r1, #8
	str r0, [r5, #0x24]
	ldr r0, [r5, #0x14]
	bl MOD15_021D8900
	mov r0, #1
	str r0, [r4]
	b _021D7E30
_021D7DEA:
	ldr r0, _021D7E44 ; =0x000005F2
	bl FUN_020054C8
	b _021D7E30
_021D7DF2:
	add r0, r5, #0
	bl MOD15_021D7E80
	cmp r0, #0
	beq _021D7E30
	ldr r0, _021D7E38 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r5, #0x14]
	mov r1, #0xe
	bl MOD15_021D8900
	b _021D7E30
_021D7E0C:
	ldr r0, [r5, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D7E30
	ldr r1, [r5, #0x24]
	add r0, r5, #0
	bl MOD15_021D7794
	b _021D7E30
_021D7E20:
	ldr r0, [r5, #0x14]
	mov r1, #0x18
	bl MOD15_021D8970
	cmp r0, #0
	beq _021D7E30
	mov r0, #0
	str r0, [r4]
_021D7E30:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7E34: .word 0x000005E4
_021D7E38: .word 0x000005DC
_021D7E3C: .word MOD15_021D779C
_021D7E40: .word MOD15_021D8044
_021D7E44: .word 0x000005F2

	thumb_func_start MOD15_021D7E48
MOD15_021D7E48: ; 0x021D7E48
	push {r3, lr}
	add r1, r0, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #0
	ldr r0, [r1, #0x18]
	bne _021D7E6A
	add r1, #0x50
	ldrh r1, [r1]
	bl FUN_020892C4
	cmp r0, #0
	beq _021D7E66
	mov r0, #1
	pop {r3, pc}
_021D7E66:
	mov r0, #0
	pop {r3, pc}
_021D7E6A:
	add r1, #0x50
	ldrh r1, [r1]
	bl FUN_02089300
	cmp r0, #0
	beq _021D7E7A
	mov r0, #1
	pop {r3, pc}
_021D7E7A:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD15_021D7E80
MOD15_021D7E80: ; 0x021D7E80
	push {r3, lr}
	add r1, r0, #0
	add r1, #0x65
	ldrb r1, [r1]
	lsl r2, r1, #2
	ldr r1, _021D7E94 ; =0x021DB86C
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_021D7E94: .word MOD15_021DB86C

	thumb_func_start MOD15_021D7E98
MOD15_021D7E98: ; 0x021D7E98
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x50
	ldrh r2, [r0]
	add r1, r2, #0
	cmp r2, #0xfe
	bne _021D7EA8
	mov r1, #0xc
_021D7EA8:
	cmp r2, #0xfe
	beq _021D7F04
	add r0, r4, #0
	add r0, #0x52
	strh r2, [r0]
	ldrh r0, [r4, #0x34]
	mov r2, #0x40
	tst r2, r0
	beq _021D7EC8
	ldr r0, _021D7F40 ; =0x021DB894
	lsl r1, r1, #2
	ldrb r0, [r0, r1]
	add r4, #0x50
	strh r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D7EC8:
	mov r2, #0x80
	tst r2, r0
	beq _021D7EDC
	ldr r0, _021D7F44 ; =0x021DB895
	lsl r1, r1, #2
	ldrb r0, [r0, r1]
	add r4, #0x50
	strh r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D7EDC:
	mov r2, #0x20
	tst r2, r0
	beq _021D7EF0
	ldr r0, _021D7F48 ; =0x021DB896
	lsl r1, r1, #2
	ldrb r0, [r0, r1]
	add r4, #0x50
	strh r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D7EF0:
	mov r2, #0x10
	tst r0, r2
	beq _021D7F3C
	ldr r0, _021D7F4C ; =0x021DB897
	lsl r1, r1, #2
	ldrb r0, [r0, r1]
	add r4, #0x50
	strh r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D7F04:
	ldrh r1, [r4, #0x34]
	mov r0, #0x40
	tst r0, r1
	beq _021D7F22
	add r0, r4, #0
	add r0, #0x52
	ldrh r0, [r0]
	mov r1, #3
	bl _s32_div_f
	add r1, #9
	add r4, #0x50
	strh r1, [r4]
	mov r0, #1
	pop {r4, pc}
_021D7F22:
	mov r0, #0x80
	tst r0, r1
	beq _021D7F3C
	add r0, r4, #0
	add r0, #0x52
	ldrh r0, [r0]
	mov r1, #3
	bl _s32_div_f
	add r4, #0x50
	strh r1, [r4]
	mov r0, #1
	pop {r4, pc}
_021D7F3C:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D7F40: .word MOD15_021DB894
_021D7F44: .word MOD15_021DB895
_021D7F48: .word MOD15_021DB896
_021D7F4C: .word MOD15_021DB897

	thumb_func_start MOD15_021D7F50
MOD15_021D7F50: ; 0x021D7F50
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x50
	ldrh r0, [r0]
	cmp r0, #0xfe
	beq _021D7FAE
	ldrh r1, [r4, #0x34]
	mov r3, #0x40
	mov r2, #0xff
	tst r3, r1
	beq _021D7F6E
	bl MOD15_021DB7C4
	add r2, r0, #0
	b _021D7F96
_021D7F6E:
	mov r3, #0x80
	tst r3, r1
	beq _021D7F7C
	bl MOD15_021DB7E0
	add r2, r0, #0
	b _021D7F96
_021D7F7C:
	mov r3, #0x10
	tst r3, r1
	beq _021D7F8A
	bl MOD15_021DB818
	add r2, r0, #0
	b _021D7F96
_021D7F8A:
	mov r3, #0x20
	tst r1, r3
	beq _021D7F96
	bl MOD15_021DB7FC
	add r2, r0, #0
_021D7F96:
	cmp r2, #0xff
	beq _021D7FE0
	add r0, r4, #0
	add r0, #0x50
	ldrh r1, [r0]
	add r0, r4, #0
	add r0, #0x52
	strh r1, [r0]
	add r4, #0x50
	strh r2, [r4]
	mov r0, #1
	pop {r4, pc}
_021D7FAE:
	ldrh r1, [r4, #0x34]
	mov r0, #0x40
	tst r0, r1
	beq _021D7FC8
	add r0, r4, #0
	add r0, #0x52
	ldrh r0, [r0]
	bl MOD15_021DB850
	add r4, #0x50
	strh r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D7FC8:
	mov r0, #0x80
	tst r0, r1
	beq _021D7FE0
	add r0, r4, #0
	add r0, #0x52
	ldrh r0, [r0]
	bl MOD15_021DB834
	add r4, #0x50
	strh r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D7FE0:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD15_021D7FE4
MOD15_021D7FE4: ; 0x021D7FE4
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	strh r0, [r4]
	strb r0, [r4, #6]
	strb r0, [r4, #7]
	add r0, r1, #0
	bl MOD15_021D8744
	strh r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #8]
	ldrh r2, [r4, #4]
	cmp r2, #0xa
	bls _021D8016
	add r1, r2, #0
	sub r1, #0xa
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r1, r0, #1
	mov r0, #1
	and r0, r2
	add r0, r1, r0
	strh r0, [r4, #2]
	pop {r4, pc}
_021D8016:
	strh r0, [r4, #2]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021D801C
MOD15_021D801C: ; 0x021D801C
	ldrb r1, [r0, #6]
	ldrb r0, [r0, #7]
	lsl r0, r0, #1
	add r0, r1, r0
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D8028
MOD15_021D8028: ; 0x021D8028
	push {r4, lr}
	add r4, r0, #0
	bl MOD15_021D801C
	ldrh r1, [r4]
	lsl r1, r1, #1
	add r0, r1, r0
	pop {r4, pc}

	thumb_func_start MOD15_021D8038
MOD15_021D8038: ; 0x021D8038
	ldr r0, [r0, #8]
	bx lr

	thumb_func_start MOD15_021D803C
MOD15_021D803C: ; 0x021D803C
	ldrh r0, [r0]
	bx lr

	thumb_func_start MOD15_021D8040
MOD15_021D8040: ; 0x021D8040
	ldrh r0, [r0, #2]
	bx lr

	thumb_func_start MOD15_021D8044
MOD15_021D8044: ; 0x021D8044
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #3
	bls _021D8052
	b _021D81B4
_021D8052:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D805E: ; jump table
	.short _021D8066 - _021D805E - 2 ; case 0
	.short _021D8172 - _021D805E - 2 ; case 1
	.short _021D8184 - _021D805E - 2 ; case 2
	.short _021D819E - _021D805E - 2 ; case 3
_021D8066:
	ldr r0, [r4, #0x38]
	cmp r0, #0
	bne _021D8076
	add r1, r4, #0
	add r1, #0x65
	ldrb r1, [r1]
	cmp r1, #0
	bne _021D808C
_021D8076:
	cmp r0, #1
	bne _021D8084
	add r1, r4, #0
	add r1, #0x65
	ldrb r1, [r1]
	cmp r1, #1
	bne _021D808C
_021D8084:
	ldrh r2, [r4, #0x30]
	mov r1, #4
	tst r1, r2
	beq _021D80BC
_021D808C:
	ldr r0, _021D81B8 ; =0x000005E4
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0
	add r0, #0x50
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0x65
	ldrb r1, [r0]
	mov r0, #1
	eor r1, r0
	add r0, r4, #0
	add r0, #0x65
	strb r1, [r0]
	ldr r0, [r4, #0x14]
	mov r1, #9
	bl MOD15_021D8900
	ldr r0, _021D81BC ; =MOD15_021D7D00
	str r0, [r4, #0x24]
	mov r0, #3
	str r0, [r5]
	b _021D81B4
_021D80BC:
	cmp r0, #2
	bne _021D80CA
	add r0, r4, #0
	add r0, #0x54
	bl MOD15_021D82A8
	b _021D80E2
_021D80CA:
	cmp r0, #3
	bne _021D80D8
	add r0, r4, #0
	add r0, #0x54
	bl MOD15_021D82D0
	b _021D80E2
_021D80D8:
	ldrh r1, [r4, #0x34]
	add r0, r4, #0
	add r0, #0x54
	bl MOD15_021D81C8
_021D80E2:
	cmp r0, #1
	beq _021D80F0
	cmp r0, #2
	beq _021D8102
	cmp r0, #3
	beq _021D8118
	b _021D812E
_021D80F0:
	ldr r0, _021D81C0 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #0x14]
	mov r1, #0xf
	bl MOD15_021D8900
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D8102:
	ldr r0, _021D81C0 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #0x14]
	mov r1, #0x10
	bl MOD15_021D8900
	mov r0, #1
	str r0, [r5]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D8118:
	ldr r0, _021D81C0 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #0x14]
	mov r1, #0x10
	bl MOD15_021D8900
	mov r0, #2
	str r0, [r5]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D812E:
	ldrh r1, [r4, #0x30]
	mov r0, #2
	tst r0, r1
	beq _021D814E
	ldr r0, _021D81C0 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #0x14]
	mov r1, #9
	bl MOD15_021D8900
	ldr r0, _021D81BC ; =MOD15_021D7D00
	str r0, [r4, #0x24]
	mov r0, #3
	str r0, [r5]
	b _021D81B4
_021D814E:
	mov r0, #1
	tst r0, r1
	beq _021D81B4
	ldr r0, _021D81C0 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD15_021D8310
	ldr r0, _021D81C4 ; =MOD15_021D779C
	mov r1, #0xa
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x14]
	bl MOD15_021D8900
	mov r0, #3
	str r0, [r5]
	b _021D81B4
_021D8172:
	ldr r0, [r4, #0x14]
	mov r1, #0x10
	bl MOD15_021D8970
	cmp r0, #0
	beq _021D81B4
	mov r0, #0
	str r0, [r5]
	b _021D81B4
_021D8184:
	ldr r0, [r4, #0x14]
	mov r1, #0x10
	bl MOD15_021D8970
	cmp r0, #0
	beq _021D81B4
	ldr r0, [r4, #0x14]
	mov r1, #0xf
	bl MOD15_021D8900
	mov r0, #0
	str r0, [r5]
	b _021D81B4
_021D819E:
	ldr r0, [r4, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D81B4
	ldr r1, [r4, #0x24]
	add r0, r4, #0
	bl MOD15_021D7794
	mov r0, #0
	str r0, [r5]
_021D81B4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D81B8: .word 0x000005E4
_021D81BC: .word MOD15_021D7D00
_021D81C0: .word 0x000005DC
_021D81C4: .word MOD15_021D779C

	thumb_func_start MOD15_021D81C8
MOD15_021D81C8: ; 0x021D81C8
	push {r3, r4, r5, lr}
	mov r2, #0x80
	add r4, r0, #0
	tst r2, r1
	beq _021D8232
	ldrb r1, [r4, #7]
	cmp r1, #4
	bhs _021D8206
	add r1, r1, #1
	strb r1, [r4, #7]
	bl MOD15_021D8028
	ldrh r1, [r4, #4]
	cmp r0, r1
	bhs _021D81EA
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D81EA:
	cmp r0, r1
	bne _021D81FC
	mov r1, #1
	tst r0, r1
	beq _021D81FC
	mov r0, #0
	strb r0, [r4, #6]
	add r0, r1, #0
	pop {r3, r4, r5, pc}
_021D81FC:
	ldrb r0, [r4, #7]
	sub r0, r0, #1
	strb r0, [r4, #7]
	mov r0, #4
	pop {r3, r4, r5, pc}
_021D8206:
	ldrh r2, [r4]
	ldrh r1, [r4, #2]
	cmp r2, r1
	bhs _021D822E
	mov r1, #1
	str r1, [r4, #8]
	ldrh r1, [r4]
	add r1, r1, #1
	strh r1, [r4]
	bl MOD15_021D8028
	ldrh r1, [r4, #4]
	cmp r0, r1
	bhs _021D8226
	mov r0, #2
	pop {r3, r4, r5, pc}
_021D8226:
	mov r0, #0
	strb r0, [r4, #6]
	mov r0, #3
	pop {r3, r4, r5, pc}
_021D822E:
	mov r0, #4
	pop {r3, r4, r5, pc}
_021D8232:
	mov r5, #0x40
	add r2, r1, #0
	tst r2, r5
	beq _021D8260
	ldrb r0, [r4, #7]
	cmp r0, #0
	beq _021D8248
	sub r0, r0, #1
	strb r0, [r4, #7]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8248:
	ldrh r0, [r4]
	cmp r0, #0
	beq _021D825C
	sub r5, #0x41
	str r5, [r4, #8]
	ldrh r0, [r4]
	sub r0, r0, #1
	strh r0, [r4]
	mov r0, #2
	pop {r3, r4, r5, pc}
_021D825C:
	mov r0, #4
	pop {r3, r4, r5, pc}
_021D8260:
	mov r3, #0x30
	add r2, r1, #0
	tst r2, r3
	beq _021D828A
	ldrb r2, [r4, #6]
	mov r1, #1
	eor r1, r2
	strb r1, [r4, #6]
	bl MOD15_021D8028
	ldrh r1, [r4, #4]
	cmp r0, r1
	bhs _021D827E
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D827E:
	ldrb r1, [r4, #6]
	mov r0, #1
	eor r0, r1
	strb r0, [r4, #6]
	mov r0, #4
	pop {r3, r4, r5, pc}
_021D828A:
	lsl r2, r5, #3
	tst r2, r1
	beq _021D8296
	bl MOD15_021D82A8
	pop {r3, r4, r5, pc}
_021D8296:
	add r3, #0xd0
	tst r1, r3
	beq _021D82A2
	bl MOD15_021D82D0
	pop {r3, r4, r5, pc}
_021D82A2:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D82A8
MOD15_021D82A8: ; 0x021D82A8
	ldrh r1, [r0]
	cmp r1, #0
	beq _021D82CA
	cmp r1, #5
	blo _021D82BE
	sub r1, r1, #5
	strh r1, [r0]
	mov r1, #4
	mvn r1, r1
	str r1, [r0, #8]
	b _021D82C6
_021D82BE:
	neg r1, r1
	str r1, [r0, #8]
	mov r1, #0
	strh r1, [r0]
_021D82C6:
	mov r0, #2
	bx lr
_021D82CA:
	mov r0, #4
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D82D0
MOD15_021D82D0: ; 0x021D82D0
	push {r4, lr}
	add r4, r0, #0
	ldrh r2, [r4, #2]
	ldrh r1, [r4]
	cmp r1, r2
	bhs _021D830C
	add r0, r1, #5
	cmp r0, r2
	bgt _021D82EC
	mov r0, #5
	str r0, [r4, #8]
	ldrh r0, [r4]
	add r0, r0, #5
	b _021D82F2
_021D82EC:
	sub r0, r2, r1
	str r0, [r4, #8]
	ldrh r0, [r4, #2]
_021D82F2:
	strh r0, [r4]
	add r0, r4, #0
	bl MOD15_021D8028
	ldrh r1, [r4, #4]
	cmp r0, r1
	bhs _021D8304
	mov r0, #2
	pop {r4, pc}
_021D8304:
	mov r0, #0
	strb r0, [r4, #6]
	mov r0, #3
	pop {r4, pc}
_021D830C:
	mov r0, #4
	pop {r4, pc}

	thumb_func_start MOD15_021D8310
MOD15_021D8310: ; 0x021D8310
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x54
	bl MOD15_021D8028
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #0
	ldr r0, [r4, #0x18]
	bne _021D8334
	add r1, r4, #0
	add r1, #0x50
	ldrh r1, [r1]
	bl FUN_020892EC
	b _021D833E
_021D8334:
	add r1, r4, #0
	add r1, #0x50
	ldrh r1, [r1]
	bl FUN_02089338
_021D833E:
	add r2, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021D8350
	cmp r0, #1
	beq _021D8354
	cmp r0, #2
	beq _021D8362
	b _021D8370
_021D8350:
	strh r2, [r4, #0x10]
	b _021D8370
_021D8354:
	add r0, r4, #0
	add r0, #0x4e
	ldrh r0, [r0]
	lsl r0, r0, #1
	add r0, r4, r0
	strh r2, [r0, #0x10]
	b _021D8370
_021D8362:
	add r1, r4, #0
	add r1, #0x4e
	ldrh r1, [r1]
	add r0, r4, #0
	add r0, #8
	bl FUN_02013998
_021D8370:
	add r0, r4, #0
	bl MOD15_021D85EC
	pop {r4, pc}

	thumb_func_start MOD15_021D8378
MOD15_021D8378: ; 0x021D8378
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4]
	cmp r1, #0
	beq _021D8388
	cmp r1, #1
	beq _021D8398
	b _021D83A6
_021D8388:
	ldr r0, [r0, #0x14]
	mov r1, #1
	bl MOD15_021D8900
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D83A6
_021D8398:
	ldr r0, [r0, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D83A6
	mov r0, #1
	pop {r4, pc}
_021D83A6:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021D83AC
MOD15_021D83AC: ; 0x021D83AC
	str r1, [r0, #0x2c]
	mov r1, #0
	str r1, [r0, #0x28]
	bx lr

	thumb_func_start MOD15_021D83B4
MOD15_021D83B4: ; 0x021D83B4
	mov r1, #0
	str r1, [r0, #0x2c]
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D83BC
MOD15_021D83BC: ; 0x021D83BC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021D83CE
	cmp r0, #1
	beq _021D83DE
	pop {r3, r4, r5, pc}
_021D83CE:
	ldr r0, [r5, #0x14]
	mov r1, #2
	bl MOD15_021D8900
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D83DE:
	ldr r0, [r5, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D83EE
	add r0, r5, #0
	bl MOD15_021D83B4
_021D83EE:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D83F0
MOD15_021D83F0: ; 0x021D83F0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #3
	bls _021D83FE
	b _021D850C
_021D83FE:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D840A: ; jump table
	.short _021D8412 - _021D840A - 2 ; case 0
	.short _021D8460 - _021D840A - 2 ; case 1
	.short _021D84E6 - _021D840A - 2 ; case 2
	.short _021D84FC - _021D840A - 2 ; case 3
_021D8412:
	bl MOD15_021D85D0
	cmp r0, #0
	bne _021D8424
	ldr r0, [r4]
	bl FUN_02085424
	cmp r0, #0
	beq _021D8456
_021D8424:
	add r0, r4, #0
	bl MOD15_021D85EC
	cmp r0, #0
	beq _021D8448
	add r0, r4, #0
	add r0, #0x66
	mov r1, #1
	mov r2, #0
	bl MOD15_021D8634
	ldr r0, [r4, #0x14]
	mov r1, #0x12
	bl MOD15_021D8900
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8448:
	ldr r0, [r4, #0x14]
	mov r1, #0x14
	bl MOD15_021D8900
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D8456:
	ldr r1, _021D8510 ; =MOD15_021D851C
	add r0, r4, #0
	bl MOD15_021D83AC
	pop {r3, r4, r5, pc}
_021D8460:
	ldr r0, [r4, #0x14]
	mov r1, #0x15
	bl MOD15_021D8970
	cmp r0, #0
	beq _021D850C
	ldrh r1, [r4, #0x30]
	add r0, r4, #0
	add r0, #0x66
	bl MOD15_021D863C
	add r0, r0, #3
	cmp r0, #4
	bhi _021D850C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8488: ; jump table
	.short _021D8492 - _021D8488 - 2 ; case 0
	.short _021D84A2 - _021D8488 - 2 ; case 1
	.short _021D850C - _021D8488 - 2 ; case 2
	.short _021D84B6 - _021D8488 - 2 ; case 3
	.short _021D84A2 - _021D8488 - 2 ; case 4
_021D8492:
	ldr r0, _021D8514 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #0x14]
	mov r1, #0x15
	bl MOD15_021D8900
	pop {r3, r4, r5, pc}
_021D84A2:
	ldr r0, _021D8514 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #0x14]
	mov r1, #0x16
	bl MOD15_021D8900
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D84B6:
	ldr r0, _021D8514 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #4]
	cmp r0, #2
	bne _021D84CA
	add r0, r4, #0
	add r0, #8
	bl FUN_020139B0
_021D84CA:
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4]
	add r1, #0x10
	add r2, #8
	bl FUN_020854A0
	ldr r1, _021D8518 ; =MOD15_021D8378
	add r0, r4, #0
	bl MOD15_021D7794
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D84E6:
	ldrh r1, [r4, #0x30]
	mov r0, #0xf3
	tst r0, r1
	beq _021D850C
	ldr r0, [r4, #0x14]
	mov r1, #0x11
	bl MOD15_021D8900
	mov r0, #3
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D84FC:
	ldr r0, [r4, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D850C
	add r0, r4, #0
	bl MOD15_021D83B4
_021D850C:
	pop {r3, r4, r5, pc}
	nop
_021D8510: .word MOD15_021D851C
_021D8514: .word 0x000005DC
_021D8518: .word MOD15_021D8378

	thumb_func_start MOD15_021D851C
MOD15_021D851C: ; 0x021D851C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _021D8532
	cmp r0, #1
	beq _021D854C
	cmp r0, #2
	beq _021D85B6
	pop {r3, r4, r5, pc}
_021D8532:
	add r0, r4, #0
	mov r1, #1
	add r0, #0x66
	add r2, r1, #0
	bl MOD15_021D8634
	ldr r0, [r4, #0x14]
	mov r1, #0x13
	bl MOD15_021D8900
	mov r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D854C:
	ldr r0, [r4, #0x14]
	mov r1, #0x15
	bl MOD15_021D8970
	cmp r0, #0
	beq _021D85C6
	ldrh r1, [r4, #0x30]
	add r0, r4, #0
	add r0, #0x66
	bl MOD15_021D863C
	add r0, r0, #3
	cmp r0, #4
	bhi _021D85C6
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8574: ; jump table
	.short _021D857E - _021D8574 - 2 ; case 0
	.short _021D858E - _021D8574 - 2 ; case 1
	.short _021D85C6 - _021D8574 - 2 ; case 2
	.short _021D85A2 - _021D8574 - 2 ; case 3
	.short _021D858E - _021D8574 - 2 ; case 4
_021D857E:
	ldr r0, _021D85C8 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #0x14]
	mov r1, #0x15
	bl MOD15_021D8900
	pop {r3, r4, r5, pc}
_021D858E:
	ldr r0, _021D85C8 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #0x14]
	mov r1, #0x16
	bl MOD15_021D8900
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D85A2:
	ldr r0, _021D85C8 ; =0x000005DC
	bl FUN_020054C8
	ldr r1, _021D85CC ; =MOD15_021D8378
	add r0, r4, #0
	bl MOD15_021D7794
	mov r0, #2
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021D85B6:
	ldr r0, [r4, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D85C6
	add r0, r4, #0
	bl MOD15_021D83B4
_021D85C6:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D85C8: .word 0x000005DC
_021D85CC: .word MOD15_021D8378

	thumb_func_start MOD15_021D85D0
MOD15_021D85D0: ; 0x021D85D0
	push {r3, lr}
	add r2, r0, #0
	add r1, r2, #0
	ldr r0, [r2]
	add r1, #0x10
	add r2, #8
	bl FUN_0208545C
	cmp r0, #0
	bne _021D85E8
	mov r0, #1
	pop {r3, pc}
_021D85E8:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD15_021D85EC
MOD15_021D85EC: ; 0x021D85EC
	push {r3, lr}
	ldr r1, [r0, #4]
	cmp r1, #0
	beq _021D85FE
	cmp r1, #1
	beq _021D860E
	cmp r1, #2
	beq _021D8624
	b _021D862C
_021D85FE:
	ldrh r1, [r0, #0x10]
	ldr r0, _021D8630 ; =0x0000FFFF
	cmp r1, r0
	beq _021D860A
	mov r0, #1
	pop {r3, pc}
_021D860A:
	mov r0, #0
	pop {r3, pc}
_021D860E:
	ldrh r2, [r0, #0x10]
	ldr r1, _021D8630 ; =0x0000FFFF
	cmp r2, r1
	beq _021D8620
	ldrh r0, [r0, #0x12]
	cmp r0, r1
	beq _021D8620
	mov r0, #1
	pop {r3, pc}
_021D8620:
	mov r0, #0
	pop {r3, pc}
_021D8624:
	add r0, #8
	bl FUN_02013870
	pop {r3, pc}
_021D862C:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_021D8630: .word 0x0000FFFF

	thumb_func_start MOD15_021D8634
MOD15_021D8634: ; 0x021D8634
	strb r2, [r0]
	strb r1, [r0, #1]
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D863C
MOD15_021D863C: ; 0x021D863C
	mov r2, #0x40
	add r3, r1, #0
	tst r3, r2
	beq _021D865A
	ldrb r1, [r0]
	cmp r1, #0
	bne _021D8650
	sub r2, #0x44
	add r0, r2, #0
	bx lr
_021D8650:
	sub r1, r1, #1
	sub r2, #0x43
	strb r1, [r0]
	add r0, r2, #0
	bx lr
_021D865A:
	mov r2, #0x80
	add r3, r1, #0
	tst r3, r2
	beq _021D867A
	ldrb r3, [r0]
	ldrb r1, [r0, #1]
	cmp r3, r1
	bne _021D8670
	sub r2, #0x84
	add r0, r2, #0
	bx lr
_021D8670:
	add r1, r3, #1
	sub r2, #0x83
	strb r1, [r0]
	add r0, r2, #0
	bx lr
_021D867A:
	mov r2, #1
	tst r2, r1
	beq _021D8684
	ldrb r0, [r0]
	bx lr
_021D8684:
	mov r0, #2
	tst r1, r0
	beq _021D868E
	sub r0, r0, #4
	bx lr
_021D868E:
	sub r0, r0, #3
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D8694
MOD15_021D8694: ; 0x021D8694
	ldrb r0, [r0]
	bx lr

	thumb_func_start MOD15_021D8698
MOD15_021D8698: ; 0x021D8698
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021D86AA
	cmp r0, #1
	beq _021D86CE
	pop {r3, r4, r5, pc}
_021D86AA:
	ldr r0, _021D86E0 ; =0x000005E4
	bl FUN_020054C8
	add r0, r5, #0
	add r0, #0x65
	ldrb r1, [r0]
	mov r0, #1
	eor r1, r0
	add r0, r5, #0
	add r0, #0x65
	strb r1, [r0]
	ldr r0, [r5, #0x14]
	mov r1, #0x17
	bl MOD15_021D8900
	mov r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_021D86CE:
	ldr r0, [r5, #0x14]
	bl MOD15_021D8958
	cmp r0, #0
	beq _021D86DE
	add r0, r5, #0
	bl MOD15_021D83B4
_021D86DE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D86E0: .word 0x000005E4

	thumb_func_start MOD15_021D86E4
MOD15_021D86E4: ; 0x021D86E4
	ldr r0, [r0, #4]
	bx lr

	thumb_func_start MOD15_021D86E8
MOD15_021D86E8: ; 0x021D86E8
	ldr r3, _021D86F0 ; =FUN_02085410
	ldr r0, [r0]
	bx r3
	nop
_021D86F0: .word FUN_02085410

	thumb_func_start MOD15_021D86F4
MOD15_021D86F4: ; 0x021D86F4
	add r0, #0x65
	ldrb r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D86FC
MOD15_021D86FC: ; 0x021D86FC
	ldr r3, _021D8704 ; =FUN_02013920
	add r0, #8
	bx r3
	nop
_021D8704: .word FUN_02013920

	thumb_func_start MOD15_021D8708
MOD15_021D8708: ; 0x021D8708
	push {r3, lr}
	ldr r2, [r0, #4]
	cmp r2, #2
	bne _021D8718
	add r0, #8
	bl FUN_02013918
	pop {r3, pc}
_021D8718:
	lsl r1, r1, #1
	add r0, r0, r1
	ldrh r0, [r0, #0x10]
	pop {r3, pc}

	thumb_func_start MOD15_021D8720
MOD15_021D8720: ; 0x021D8720
	ldr r3, _021D8728 ; =FUN_02013840
	add r0, #8
	bx r3
	nop
_021D8728: .word FUN_02013840

	thumb_func_start MOD15_021D872C
MOD15_021D872C: ; 0x021D872C
	add r0, #0x4e
	ldrh r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D8734
MOD15_021D8734: ; 0x021D8734
	add r0, #0x4c
	ldrh r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D873C
MOD15_021D873C: ; 0x021D873C
	add r0, #0x50
	ldrh r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D8744
MOD15_021D8744: ; 0x021D8744
	push {r3, lr}
	add r1, r0, #0
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #0
	ldr r0, [r1, #0x18]
	bne _021D875C
	add r1, #0x50
	ldrh r1, [r1]
	bl FUN_020892C4
	pop {r3, pc}
_021D875C:
	add r1, #0x50
	ldrh r1, [r1]
	bl FUN_02089300
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD15_021D8768
MOD15_021D8768: ; 0x021D8768
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0x65
	ldrb r0, [r0]
	add r4, r1, #0
	add r3, r2, #0
	cmp r0, #0
	ldr r0, [r5, #0x18]
	bne _021D8786
	add r5, #0x50
	ldrh r1, [r5]
	add r2, r4, #0
	bl FUN_020892CC
	pop {r3, r4, r5, pc}
_021D8786:
	add r5, #0x50
	ldrh r1, [r5]
	add r2, r4, #0
	bl FUN_02089310
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D8794
MOD15_021D8794: ; 0x021D8794
	ldr r3, _021D879C ; =MOD15_021D801C
	add r0, #0x54
	bx r3
	nop
_021D879C: .word MOD15_021D801C

	thumb_func_start MOD15_021D87A0
MOD15_021D87A0: ; 0x021D87A0
	ldr r3, _021D87A8 ; =MOD15_021D8038
	add r0, #0x54
	bx r3
	nop
_021D87A8: .word MOD15_021D8038

	thumb_func_start MOD15_021D87AC
MOD15_021D87AC: ; 0x021D87AC
	push {r3, lr}
	add r0, #0x54
	bl MOD15_021D803C
	cmp r0, #0
	beq _021D87BC
	mov r0, #1
	pop {r3, pc}
_021D87BC:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD15_021D87C0
MOD15_021D87C0: ; 0x021D87C0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0x54
	bl MOD15_021D803C
	add r5, #0x54
	add r4, r0, #0
	add r0, r5, #0
	bl MOD15_021D8040
	cmp r4, r0
	bge _021D87DC
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D87DC:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D87E0
MOD15_021D87E0: ; 0x021D87E0
	ldr r3, _021D87E8 ; =FUN_02085414
	ldr r0, [r0]
	bx r3
	nop
_021D87E8: .word FUN_02085414

	thumb_func_start MOD15_021D87EC
MOD15_021D87EC: ; 0x021D87EC
	ldr r3, _021D87F4 ; =MOD15_021D8694
	add r0, #0x66
	bx r3
	nop
_021D87F4: .word MOD15_021D8694

	thumb_func_start MOD15_021D87F8
MOD15_021D87F8: ; 0x021D87F8
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r6, r1, #0
	mov r1, #0x7d
	add r5, r0, #0
	mov r0, #0x23
	lsl r1, r1, #2
	bl AllocFromHeap
	add r4, r0, #0
	beq _021D8878
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	str r5, [r4, #0x18]
	str r6, [r4, #0x1c]
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x23
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r4, #0
	mov r0, #0x80
	add r1, #0x28
	mov r2, #0x23
	bl FUN_02008C9C
	str r0, [r4, #0x24]
	mov r0, #0x23
	bl FUN_02016B94
	str r0, [r4, #0x20]
	ldr r0, _021D8880 ; =MOD15_021D88D8
	add r1, r4, #0
	mov r2, #2
	bl FUN_0200CA44
	str r0, [r4]
	ldr r0, _021D8884 ; =MOD15_021D88DC
	add r1, r4, #0
	mov r2, #1
	bl MOD15_021D88D0
	mov r1, #0
	str r0, [r4, #4]
	add r2, r4, #0
	add r0, r1, #0
_021D886E:
	add r1, r1, #1
	str r0, [r2, #8]
	add r2, r2, #4
	cmp r1, #4
	blt _021D886E
_021D8878:
	add r0, r4, #0
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_021D8880: .word MOD15_021D88D8
_021D8884: .word MOD15_021D88DC

	thumb_func_start MOD15_021D8888
MOD15_021D8888: ; 0x021D8888
	push {r4, r5, r6, lr}
	add r6, r0, #0
	beq _021D88CE
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	mov r4, #0
	add r5, r6, #0
_021D889A:
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021D88A4
	bl FUN_0200CAB4
_021D88A4:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D889A
	ldr r0, [r6]
	bl FUN_0200CAB4
	ldr r0, [r6, #4]
	bl FUN_0200CAB4
	bl FUN_02009FA0
	ldr r0, [r6, #0x24]
	bl FUN_0201FD58
	ldr r0, [r6, #0x20]
	bl FreeToHeap
	add r0, r6, #0
	bl FreeToHeap
_021D88CE:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD15_021D88D0
MOD15_021D88D0: ; 0x021D88D0
	ldr r3, _021D88D4 ; =FUN_0200CA60
	bx r3
	.align 2, 0
_021D88D4: .word FUN_0200CA60

	thumb_func_start MOD15_021D88D8
MOD15_021D88D8: ; 0x021D88D8
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D88DC
MOD15_021D88DC: ; 0x021D88DC
	push {r3, lr}
	ldr r0, [r1, #0x24]
	bl FUN_0201FDEC
	bl FUN_02009F80
	ldr r3, _021D88F8 ; =OS_IRQTable
	ldr r1, _021D88FC ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, pc}
	nop
_021D88F8: .word OS_IRQTable
_021D88FC: .word 0x00003FF8

	thumb_func_start MOD15_021D8900
MOD15_021D8900: ; 0x021D8900
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	cmp r6, #0x1d
	bhs _021D894E
	mov r0, #0x23
	mov r1, #0x18
	bl AllocFromHeap
	add r1, r0, #0
	beq _021D8952
	mov r4, #0
	str r4, [r1, #0x14]
	str r6, [r1, #0xc]
	str r5, [r1]
	ldr r0, [r5, #0x18]
	add r2, r5, #0
	str r0, [r1, #4]
	ldr r0, [r5, #0x1c]
	str r0, [r1, #8]
_021D8928:
	ldr r0, [r2, #8]
	cmp r0, #0
	bne _021D8944
	ldr r0, _021D8954 ; =0x021DB98C
	lsl r2, r6, #2
	ldr r0, [r0, r2]
	mov r2, #1
	str r4, [r1, #0x10]
	bl FUN_0200CA44
	lsl r1, r4, #2
	add r1, r5, r1
	str r0, [r1, #8]
	pop {r4, r5, r6, pc}
_021D8944:
	add r4, r4, #1
	add r2, r2, #4
	cmp r4, #4
	blt _021D8928
	pop {r4, r5, r6, pc}
_021D894E:
	bl ErrorHandling
_021D8952:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8954: .word MOD15_021DB98C

	thumb_func_start MOD15_021D8958
MOD15_021D8958: ; 0x021D8958
	mov r2, #0
_021D895A:
	ldr r1, [r0, #8]
	cmp r1, #0
	beq _021D8964
	mov r0, #0
	bx lr
_021D8964:
	add r2, r2, #1
	add r0, r0, #4
	cmp r2, #4
	blt _021D895A
	mov r0, #1
	bx lr

	thumb_func_start MOD15_021D8970
MOD15_021D8970: ; 0x021D8970
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
_021D8978:
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021D898C
	bl FUN_0201B6C8
	ldr r0, [r0, #0xc]
	cmp r0, r6
	bne _021D898C
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D898C:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D8978
	mov r0, #1
	pop {r4, r5, r6, pc}

	thumb_func_start MOD15_021D8998
MOD15_021D8998: ; 0x021D8998
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #8]
	bl FUN_0200CAB4
	ldr r0, [r4, #0x10]
	ldr r1, [r4]
	lsl r0, r0, #2
	mov r2, #0
	add r0, r1, r0
	str r2, [r0, #8]
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021D89C0
MOD15_021D89C0: ; 0x021D89C0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r1, #1
	lsl r1, r1, #0x1a
	ldr r0, [r1]
	ldr r2, _021D8AA4 ; =0xFFFFE0FF
	and r0, r2
	str r0, [r1]
	ldr r0, _021D8AA8 ; =0x04001000
	ldr r3, [r0]
	and r2, r3
	str r2, [r0]
	ldr r2, [r1]
	ldr r3, _021D8AAC ; =0xFFCFFFEF
	add r5, r2, #0
	ldr r2, _021D8AB0 ; =0x00100010
	and r5, r3
	orr r2, r5
	str r2, [r1]
	ldr r1, [r0]
	add r2, r1, #0
	and r2, r3
	mov r1, #0x10
	orr r1, r2
	str r1, [r0]
	add r0, r4, #0
	bl MOD15_021D8C30
	add r0, r4, #0
	bl MOD15_021D8AB4
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	bl MOD15_021D95E8
	mov r1, #0x1e
	ldr r2, [r4]
	lsl r1, r1, #4
	str r0, [r2, r1]
	ldr r0, [r4]
	ldr r0, [r0, r1]
	bl MOD15_021D9694
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	bl MOD15_021D9FA0
	mov r1, #0x79
	ldr r2, [r4]
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	ldr r0, [r0, r1]
	bl MOD15_021D9FD4
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	bl MOD15_021DA18C
	mov r1, #0x7a
	ldr r2, [r4]
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	ldr r0, [r0, r1]
	bl MOD15_021DA1D0
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	bl MOD15_021DA828
	mov r1, #0x7b
	ldr r2, [r4]
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	ldr r0, [r0, r1]
	bl MOD15_021DA8E8
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	bl MOD15_021DAE68
	mov r1, #0x1f
	ldr r2, [r4]
	lsl r1, r1, #4
	str r0, [r2, r1]
	ldr r0, [r4]
	ldr r0, [r0, r1]
	bl MOD15_021DAEB4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	bl GX_DispOn
	add r0, r4, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8AA4: .word 0xFFFFE0FF
_021D8AA8: .word 0x04001000
_021D8AAC: .word 0xFFCFFFEF
_021D8AB0: .word 0x00100010

	thumb_func_start MOD15_021D8AB4
MOD15_021D8AB4: ; 0x021D8AB4
	push {r3, r4, lr}
	sub sp, #0x14
	ldr r4, [r0]
	mov r0, #0x66
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_020B19DC
	mov r0, #0x6b
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_020B19DC
	mov r0, #0x15
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_020B1A24
	mov r0, #0x5d
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_020B1A24
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x23
	str r0, [sp, #0xc]
	mov r0, #0x15
	lsl r0, r0, #4
	add r0, r4, r0
	str r0, [sp, #0x10]
	mov r0, #0x4c
	mov r1, #9
	bl FUN_02006AE4
	mov r0, #0x23
	str r0, [sp]
	mov r0, #0x66
	lsl r0, r0, #2
	add r0, r4, r0
	str r0, [sp, #4]
	mov r0, #0x4c
	mov r1, #0xa
	mov r2, #1
	mov r3, #0
	bl FUN_02006A8C
	mov r1, #7
	mov r0, #0x23
	lsl r3, r1, #6
	str r0, [sp]
	mov r0, #0x4c
	mov r2, #1
	add r3, r4, r3
	bl FUN_02006C30
	mov r3, #0x1d
	lsl r3, r3, #4
	str r0, [r4, r3]
	mov r0, #0x23
	sub r3, #8
	str r0, [sp]
	mov r0, #0x4c
	mov r1, #8
	mov r2, #1
	add r3, r4, r3
	bl FUN_02006C5C
	mov r1, #0x76
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r2, #0
	sub r0, r1, #4
	str r2, [r4, r0]
	add r0, r1, #4
	str r2, [r4, r0]
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021D8B58
MOD15_021D8B58: ; 0x021D8B58
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	ldr r0, [r6, #0x14]
	ldr r7, [r6]
	cmp r0, #0
	beq _021D8B6E
	cmp r0, #1
	beq _021D8B90
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_021D8B6E:
	mov r0, #5
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x23
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r6, #0x14]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r6, #0x14]
	pop {r4, r5, r6, r7, pc}
_021D8B90:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D8C2A
	mov r0, #0x1e
	ldr r1, [r6]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl MOD15_021D9634
	mov r0, #0x79
	ldr r1, [r6]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD15_021D9FBC
	mov r0, #0x7a
	ldr r1, [r6]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD15_021DA1B8
	mov r0, #0x7b
	ldr r1, [r6]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD15_021DA8A4
	mov r0, #0x1f
	ldr r1, [r6]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl MOD15_021DAEA4
	mov r4, #0
	add r5, r7, #0
_021D8BD8:
	mov r0, #0x1d
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D8BE6
	bl FreeToHeap
_021D8BE6:
	mov r0, #0x76
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D8BF4
	bl FreeToHeap
_021D8BF4:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _021D8BD8
	ldr r0, [r7, #0x20]
	mov r1, #0
	bl FUN_020178A0
	ldr r0, [r7, #0x20]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r7, #0x20]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r7, #0x20]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r7, #0x20]
	mov r1, #4
	bl FUN_020178A0
	add r0, r6, #0
	bl MOD15_021D8998
_021D8C2A:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD15_021D8C30
MOD15_021D8C30: ; 0x021D8C30
	push {r4, lr}
	ldr r2, _021D8C94 ; =0x04000304
	ldr r4, [r0]
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	mov r0, #1
	mov r1, #0
	add r2, r0, #0
	bl GX_SetGraphicsMode
	ldr r0, _021D8C98 ; =0x021DB964
	bl FUN_0201E66C
	ldr r0, _021D8C9C ; =0x021DB8C8
	bl FUN_02016BBC
	mov r1, #0
	ldr r0, [r4, #0x20]
	ldr r2, _021D8CA0 ; =0x021DB910
	add r3, r1, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x20]
	ldr r2, _021D8CA4 ; =0x021DB8D8
	mov r1, #1
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x20]
	ldr r2, _021D8CA8 ; =0x021DB948
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x20]
	ldr r2, _021D8CAC ; =0x021DB8F4
	mov r1, #3
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x20]
	ldr r2, _021D8CB0 ; =0x021DB92C
	mov r1, #4
	mov r3, #0
	bl FUN_02016C18
	pop {r4, pc}
	nop
_021D8C94: .word 0x04000304
_021D8C98: .word MOD15_021DB964
_021D8C9C: .word MOD15_021DB8C8
_021D8CA0: .word MOD15_021DB910
_021D8CA4: .word MOD15_021DB8D8
_021D8CA8: .word MOD15_021DB948
_021D8CAC: .word MOD15_021DB8F4
_021D8CB0: .word MOD15_021DB92C

	thumb_func_start MOD15_021D8CB4
MOD15_021D8CB4: ; 0x021D8CB4
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021D8CC6
	cmp r0, #1
	beq _021D8CE6
	b _021D8CF8
_021D8CC6:
	mov r0, #5
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x23
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r4, #0x14]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #0x14]
	pop {r3, r4, pc}
_021D8CE6:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D8CFE
	ldr r0, [r4, #0x14]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #0x14]
	pop {r3, r4, pc}
_021D8CF8:
	add r0, r4, #0
	bl MOD15_021D8998
_021D8CFE:
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021D8D04
MOD15_021D8D04: ; 0x021D8D04
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r0, #0x1e
	ldr r4, [r5]
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9964
	ldr r0, [r5, #4]
	bl MOD15_021D872C
	add r1, r0, #0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9E3C
	add r0, r5, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D8D30
MOD15_021D8D30: ; 0x021D8D30
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r0, #0x1e
	ldr r4, [r5]
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021D9DD8
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9DEC
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD15_021DA10C
	ldr r0, [r4, #0x18]
	bl MOD15_021D8734
	add r1, r0, #0
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA124
	add r0, r5, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D8D74
MOD15_021D8D74: ; 0x021D8D74
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r0, #0x79
	ldr r4, [r5]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021DA10C
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9E0C
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD15_021D9DD8
	add r0, r5, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D8DA4
MOD15_021D8DA4: ; 0x021D8DA4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x14]
	ldr r4, [r5]
	cmp r0, #0
	beq _021D8DB6
	cmp r0, #1
	beq _021D8DDC
	pop {r3, r4, r5, pc}
_021D8DB6:
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9DC0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9DEC
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA638
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D8DDC:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA650
	cmp r0, #0
	beq _021D8E18
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA164
	ldr r0, [r4, #0x18]
	bl MOD15_021D873C
	add r1, r0, #0
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA5B4
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD15_021DA588
	add r0, r5, #0
	bl MOD15_021D8998
_021D8E18:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D8E1C
MOD15_021D8E1C: ; 0x021D8E1C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x14]
	ldr r4, [r5]
	cmp r0, #0
	beq _021D8E32
	cmp r0, #1
	beq _021D8E44
	cmp r0, #2
	beq _021D8E56
	pop {r3, r4, r5, pc}
_021D8E32:
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021DB2D0
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D8E44:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA7E8
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D8E56:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA81C
	cmp r0, #0
	beq _021D8E82
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021DB358
	cmp r0, #0
	beq _021D8E82
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA7C4
	add r0, r5, #0
	bl MOD15_021D8998
_021D8E82:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D8E84
MOD15_021D8E84: ; 0x021D8E84
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x14]
	ldr r4, [r5]
	cmp r0, #3
	bhi _021D8F26
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8E9C: ; jump table
	.short _021D8EA4 - _021D8E9C - 2 ; case 0
	.short _021D8EB6 - _021D8E9C - 2 ; case 1
	.short _021D8ED4 - _021D8E9C - 2 ; case 2
	.short _021D8EF4 - _021D8E9C - 2 ; case 3
_021D8EA4:
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021DB2D0
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D8EB6:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021DA588
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA7E8
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D8ED4:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA81C
	cmp r0, #0
	beq _021D8F26
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA7C4
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D8EF4:
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021DB358
	cmp r0, #0
	beq _021D8F26
	ldr r0, [r4, #0x18]
	bl MOD15_021D873C
	add r1, r0, #0
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA5B4
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD15_021DA588
	add r0, r5, #0
	bl MOD15_021D8998
_021D8F26:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D8F28
MOD15_021D8F28: ; 0x021D8F28
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x14]
	ldr r4, [r5]
	cmp r0, #0
	beq _021D8F3A
	cmp r0, #1
	beq _021D8F62
	pop {r3, r4, r5, pc}
_021D8F3A:
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA178
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021DA588
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA6A0
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D8F62:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA6C4
	cmp r0, #0
	beq _021D8F8A
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9E0C
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9DCC
	add r0, r5, #0
	bl MOD15_021D8998
_021D8F8A:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D8F8C
MOD15_021D8F8C: ; 0x021D8F8C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x14]
	ldr r4, [r5]
	cmp r0, #0
	beq _021D8FA2
	cmp r0, #1
	beq _021D8FCA
	cmp r0, #2
	beq _021D8FEA
	pop {r3, r4, r5, pc}
_021D8FA2:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA9D4
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021DA588
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA744
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D8FCA:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA760
	cmp r0, #0
	beq _021D9028
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DAA24
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D8FEA:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DAAD0
	cmp r0, #0
	beq _021D9028
	ldr r0, [r4, #0x18]
	bl MOD15_021D8794
	add r1, r0, #0
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DABC0
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD15_021DAB80
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD15_021DB4E8
	add r0, r5, #0
	bl MOD15_021D8998
_021D9028:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D902C
MOD15_021D902C: ; 0x021D902C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x14]
	ldr r4, [r5]
	cmp r0, #4
	bhi _021D90FC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9044: ; jump table
	.short _021D904E - _021D9044 - 2 ; case 0
	.short _021D9060 - _021D9044 - 2 ; case 1
	.short _021D908A - _021D9044 - 2 ; case 2
	.short _021D90AA - _021D9044 - 2 ; case 3
	.short _021D90BC - _021D9044 - 2 ; case 4
_021D904E:
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021DB2D0
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D9060:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021DAB80
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021DB4E8
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DAAF4
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D908A:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DAB18
	cmp r0, #0
	beq _021D90FC
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA7C4
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D90AA:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA77C
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D90BC:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA7B8
	cmp r0, #0
	beq _021D90FC
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021DB358
	cmp r0, #0
	beq _021D90FC
	ldr r0, [r4, #0x18]
	bl MOD15_021D873C
	add r1, r0, #0
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA5B4
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD15_021DA588
	add r0, r5, #0
	bl MOD15_021D8998
_021D90FC:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D9100
MOD15_021D9100: ; 0x021D9100
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x14]
	ldr r4, [r5]
	cmp r0, #3
	bhi _021D91DC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9118: ; jump table
	.short _021D9120 - _021D9118 - 2 ; case 0
	.short _021D9154 - _021D9118 - 2 ; case 1
	.short _021D917E - _021D9118 - 2 ; case 2
	.short _021D919E - _021D9118 - 2 ; case 3
_021D9120:
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA178
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021DAB80
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021DB4E8
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DAAF4
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D9154:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DAB18
	cmp r0, #0
	beq _021D91DC
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA710
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA77C
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D917E:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA7B8
	cmp r0, #0
	beq _021D91DC
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA720
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D919E:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA738
	cmp r0, #0
	beq _021D91DC
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9964
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD15_021D9DD8
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9E0C
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9DCC
	add r0, r5, #0
	bl MOD15_021D8998
_021D91DC:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D91E0
MOD15_021D91E0: ; 0x021D91E0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x14]
	ldr r4, [r5]
	cmp r0, #3
	bhi _021D92B4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D91F8: ; jump table
	.short _021D9200 - _021D91F8 - 2 ; case 0
	.short _021D9234 - _021D91F8 - 2 ; case 1
	.short _021D925E - _021D91F8 - 2 ; case 2
	.short _021D927E - _021D91F8 - 2 ; case 3
_021D9200:
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA178
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021DAB80
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021DB4E8
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DAAF4
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D9234:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DAB18
	cmp r0, #0
	beq _021D92B4
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA710
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA77C
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D925E:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA7B8
	cmp r0, #0
	beq _021D92B4
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA720
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D927E:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA738
	cmp r0, #0
	beq _021D92B4
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9964
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021D9DD8
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD15_021DA10C
	add r0, r5, #0
	bl MOD15_021D8998
_021D92B4:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D92B8
MOD15_021D92B8: ; 0x021D92B8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r4, [r5]
	ldr r0, [r4, #0x18]
	bl MOD15_021D872C
	add r1, r0, #0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9E3C
	add r0, r5, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D92D8
MOD15_021D92D8: ; 0x021D92D8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r4, [r5]
	ldr r0, [r4, #0x18]
	bl MOD15_021D8734
	add r1, r0, #0
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA124
	add r0, r5, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D92F8
MOD15_021D92F8: ; 0x021D92F8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r4, [r5]
	ldr r0, [r4, #0x18]
	bl MOD15_021D873C
	add r1, r0, #0
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA5B4
	add r0, r5, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D9318
MOD15_021D9318: ; 0x021D9318
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r4, [r5]
	ldr r0, [r4, #0x18]
	bl MOD15_021D8794
	add r1, r0, #0
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DABC0
	add r0, r5, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D9338
MOD15_021D9338: ; 0x021D9338
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x14]
	ldr r4, [r5]
	cmp r0, #0
	beq _021D934A
	cmp r0, #1
	beq _021D9364
	pop {r3, r4, r5, pc}
_021D934A:
	ldr r0, [r4, #0x18]
	bl MOD15_021D87A0
	add r1, r0, #0
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DABFC
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	pop {r3, r4, r5, pc}
_021D9364:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DACB8
	cmp r0, #0
	beq _021D9384
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD15_021DB4E8
	add r0, r5, #0
	bl MOD15_021D8998
_021D9384:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D9388
MOD15_021D9388: ; 0x021D9388
	push {r4, lr}
	add r4, r1, #0
	mov r0, #0x1e
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0
	bl MOD15_021D9CB4
	add r0, r4, #0
	bl MOD15_021D8998
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021D93A4
MOD15_021D93A4: ; 0x021D93A4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r0, #0x1e
	ldr r4, [r5]
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #2
	bl MOD15_021D9CB4
	ldr r0, [r5, #4]
	bl MOD15_021D87EC
	add r1, r0, #0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9ECC
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA118
	cmp r0, #0
	beq _021D93E2
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA0F4
	b _021D93EC
_021D93E2:
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9DC0
_021D93EC:
	add r0, r5, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D93F4
MOD15_021D93F4: ; 0x021D93F4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r0, #0x1e
	ldr r4, [r5]
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #3
	bl MOD15_021D9CB4
	ldr r0, [r5, #4]
	bl MOD15_021D87EC
	add r1, r0, #0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9ECC
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA118
	cmp r0, #0
	beq _021D9432
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA0F4
	b _021D943C
_021D9432:
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9DC0
_021D943C:
	add r0, r5, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D9444
MOD15_021D9444: ; 0x021D9444
	push {r4, lr}
	add r4, r1, #0
	mov r0, #0x1e
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #1
	bl MOD15_021D9CB4
	add r0, r4, #0
	bl MOD15_021D8998
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021D9460
MOD15_021D9460: ; 0x021D9460
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #4]
	ldr r4, [r5]
	bl MOD15_021D87EC
	add r1, r0, #0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9F58
	add r0, r5, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D9480
MOD15_021D9480: ; 0x021D9480
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r0, #0x1e
	ldr r4, [r5]
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD15_021D9CB4
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9F88
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA118
	cmp r0, #0
	beq _021D94B6
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD15_021DA100
	b _021D94C0
_021D94B6:
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD15_021D9DCC
_021D94C0:
	add r0, r5, #0
	bl MOD15_021D8998
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D94C8
MOD15_021D94C8: ; 0x021D94C8
	push {r4, lr}
	add r4, r1, #0
	mov r0, #0x1f
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0
	mov r2, #1
	bl MOD15_021DB520
	add r0, r4, #0
	bl MOD15_021D8998
	pop {r4, pc}

	thumb_func_start MOD15_021D94E4
MOD15_021D94E4: ; 0x021D94E4
	push {r4, lr}
	add r4, r1, #0
	mov r0, #0x1f
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #1
	add r2, r1, #0
	bl MOD15_021DB520
	add r0, r4, #0
	bl MOD15_021D8998
	pop {r4, pc}

	thumb_func_start MOD15_021D9500
MOD15_021D9500: ; 0x021D9500
	push {r4, lr}
	add r4, r1, #0
	mov r0, #0x1f
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0
	add r2, r1, #0
	bl MOD15_021DB520
	add r0, r4, #0
	bl MOD15_021D8998
	pop {r4, pc}

	thumb_func_start MOD15_021D951C
MOD15_021D951C: ; 0x021D951C
	push {r4, lr}
	add r4, r1, #0
	mov r0, #0x1f
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #1
	mov r2, #0
	bl MOD15_021DB520
	add r0, r4, #0
	bl MOD15_021D8998
	pop {r4, pc}

	thumb_func_start MOD15_021D9538
MOD15_021D9538: ; 0x021D9538
	mov r1, #0x1e
	lsl r1, r1, #4
	ldr r3, _021D9544 ; =MOD15_021D9CB0
	ldr r0, [r0, r1]
	bx r3
	nop
_021D9544: .word MOD15_021D9CB0

	thumb_func_start MOD15_021D9548
MOD15_021D9548: ; 0x021D9548
	ldr r0, [r0, #0x20]
	bx lr

	thumb_func_start MOD15_021D954C
MOD15_021D954C: ; 0x021D954C
	ldr r0, [r0, #0x24]
	bx lr

	thumb_func_start MOD15_021D9550
MOD15_021D9550: ; 0x021D9550
	push {r3, r4, r5, r6}
	mov r4, #0x15
	lsl r4, r4, #4
	mov r5, #0x24
	add r6, r0, r4
	mul r5, r2
	add r5, r6, r5
	str r5, [r1]
	add r5, r4, #0
	add r5, #0x48
	add r6, r0, r5
	mov r5, #0x14
	mul r5, r2
	lsl r2, r2, #2
	add r5, r6, r5
	add r2, r0, r2
	add r0, r4, #0
	str r5, [r1, #8]
	add r0, #0x70
	ldr r0, [r2, r0]
	add r4, #0x78
	str r0, [r1, #0xc]
	ldr r0, [r2, r4]
	str r0, [r1, #0x10]
	add r0, r1, #0
	add r0, #0x20
	strb r3, [r0]
	mov r0, #0
	str r0, [r1, #4]
	str r0, [r1, #0x14]
	str r0, [r1, #0x18]
	str r0, [r1, #0x1c]
	pop {r3, r4, r5, r6}
	bx lr

	thumb_func_start MOD15_021D9594
MOD15_021D9594: ; 0x021D9594
	push {r3, r4, r5, lr}
	sub sp, #0x20
	ldr r0, [r0, #0x24]
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
	mov r0, #0x23
	str r0, [sp, #0x1c]
	bl OS_DisableInterrupts
	add r4, r0, #0
	add r0, sp, #0
	bl FUN_0201FF84
	add r5, r0, #0
	add r0, r4, #0
	bl OS_RestoreInterrupts
	cmp r5, #0
	beq _021D95E0
	add r0, r5, #0
	mov r1, #1
	bl FUN_020200BC
	mov r1, #1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_020200D8
_021D95E0:
	add r0, r5, #0
	add sp, #0x20
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D95E8
MOD15_021D95E8: ; 0x021D95E8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #0x1b
	add r5, r0, #0
	mov r0, #0x23
	lsl r1, r1, #4
	add r7, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	str r6, [r4, #4]
	str r7, [r4, #8]
	mov r0, #0
	str r0, [r4, #0x3c]
	str r0, [r4, #0x40]
	str r0, [r4, #0x44]
	mov r0, #0x80
	mov r1, #0x23
	bl String_ctor
	str r0, [r4, #0x4c]
	ldr r2, _021D9630 ; =0x00000182
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x23
	bl NewMsgDataFromNarc
	str r0, [r4, #0x48]
	mov r0, #0x23
	bl FUN_02013690
	str r0, [r4, #0x50]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9630: .word 0x00000182

	thumb_func_start MOD15_021D9634
MOD15_021D9634: ; 0x021D9634
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x50]
	cmp r0, #0
	beq _021D9642
	bl FUN_020136C0
_021D9642:
	ldr r0, [r4, #0x3c]
	cmp r0, #0
	beq _021D964C
	bl FUN_0201FFC8
_021D964C:
	ldr r0, [r4, #0x40]
	cmp r0, #0
	beq _021D9656
	bl FUN_0201FFC8
_021D9656:
	ldr r0, [r4, #0x44]
	cmp r0, #0
	beq _021D9660
	bl FUN_0201FFC8
_021D9660:
	ldr r0, [r4, #0x48]
	cmp r0, #0
	beq _021D966A
	bl DestroyMsgData
_021D966A:
	ldr r0, [r4, #0x4c]
	cmp r0, #0
	beq _021D9674
	bl String_dtor
_021D9674:
	add r0, r4, #0
	add r0, #0xc
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0x1c
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0x2c
	bl FUN_02019178
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD15_021D9694
MOD15_021D9694: ; 0x021D9694
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD15_021D9548
	add r6, r0, #0
	add r0, r5, #0
	bl MOD15_021D97E4
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x23
	str r0, [sp, #0xc]
	mov r0, #0x4c
	add r2, r6, #0
	add r3, r1, #0
	bl FUN_020068C8
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	mov r0, #0x23
	str r0, [sp, #0xc]
	mov r0, #0x4c
	add r2, r6, #0
	bl FUN_0200687C
	lsr r4, r0, #5
	mov r0, #1
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r2, #0
	lsl r0, r4, #0x10
	add r1, r5, #0
	str r2, [sp, #0xc]
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	add r0, r6, #0
	add r1, #0xc
	mov r3, #3
	bl FUN_02019064
	mov r0, #0x15
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r3, #2
	add r1, r5, #0
	str r3, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x6c
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	add r0, r6, #0
	add r1, #0x1c
	mov r2, #0
	bl FUN_02019064
	mov r0, #0xf
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0xa2
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r1, r5, #0
	str r0, [sp, #0x10]
	add r0, r6, #0
	add r1, #0x2c
	mov r2, #0
	mov r3, #0x17
	bl FUN_02019064
	add r0, r4, #0
	add r0, #0xc2
	str r0, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x23
	str r0, [sp, #0xc]
	mov r0, #0x26
	add r2, r6, #0
	add r3, r1, #0
	bl FUN_0200687C
	add r0, r4, #0
	add r0, #0xc2
	str r0, [r5, #0x60]
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x23
	mov r3, #7
	str r0, [sp, #4]
	mov r0, #0x26
	mov r1, #0x18
	mov r2, #0
	lsl r3, r3, #6
	bl FUN_02006930
	ldr r0, [r5, #4]
	bl MOD15_021D87E0
	lsl r0, r0, #0x18
	add r2, r4, #0
	lsr r0, r0, #0x18
	add r2, #0xcb
	str r0, [sp]
	mov r0, #0x23
	lsl r2, r2, #0x10
	str r0, [sp, #4]
	add r0, r6, #0
	mov r1, #0
	lsr r2, r2, #0x10
	mov r3, #0xf
	bl FUN_0200CD68
	add r0, r5, #0
	add r4, #0xcb
	add r0, #0x1c
	add r1, r4, #0
	mov r2, #0xf
	bl FUN_0200D06C
	add r0, r5, #0
	add r0, #0xc
	bl FUN_02019270
	add r0, r5, #0
	add r0, #0x1c
	bl FUN_02019270
	add r0, r5, #0
	bl MOD15_021D9868
	add r0, r5, #0
	bl MOD15_021D9964
	add r0, r5, #0
	mov r1, #0
	bl MOD15_021D9CB4
	add r0, r5, #0
	bl MOD15_021D98C0
	add r0, r6, #0
	mov r1, #0
	bl FUN_02017CD0
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD15_021D97E4
MOD15_021D97E4: ; 0x021D97E4
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #7
	lsl r0, r0, #6
	str r0, [sp]
	mov r0, #0x23
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x4c
	mov r1, #6
	add r3, r2, #0
	bl FUN_02006930
	mov r0, #0x4c
	mov r1, #6
	add r2, sp, #8
	mov r3, #0x23
	bl FUN_02006C08
	add r4, r0, #0
	ldr r0, [sp, #8]
	add r1, r5, #0
	mov r2, #5
	ldr r0, [r0, #0xc]
	add r1, #0x70
	lsl r2, r2, #6
	bl MIi_CpuCopy16
	add r5, #0x70
	mov r1, #5
	add r0, r5, #0
	lsl r1, r1, #6
	bl DC_FlushRange
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start MOD15_021D9834
MOD15_021D9834: ; 0x021D9834
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl MOD15_021D86E4
	cmp r0, #2
	bne _021D985A
	ldr r0, [r4, #4]
	bl MOD15_021D86FC
	add r0, r0, #1
	add r4, #0x70
	lsl r0, r0, #5
	add r0, r4, r0
	mov r1, #0
	mov r2, #0x20
	bl GX_LoadBGPltt
	pop {r4, pc}
_021D985A:
	add r4, #0x70
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x20
	bl GX_LoadBGPltt
	pop {r4, pc}

	thumb_func_start MOD15_021D9868
MOD15_021D9868: ; 0x021D9868
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl MOD15_021D86E4
	cmp r0, #0
	beq _021D9880
	cmp r0, #1
	beq _021D9896
	cmp r0, #2
	beq _021D98BA
	pop {r4, pc}
_021D9880:
	add r0, r4, #0
	mov r1, #0x68
	add r0, #0x54
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0x10
	add r0, #0x56
	strh r1, [r0]
	mov r0, #1
	str r0, [r4, #0x5c]
	pop {r4, pc}
_021D9896:
	add r0, r4, #0
	mov r1, #0x30
	add r0, #0x54
	strh r1, [r0]
	add r0, r4, #0
	mov r2, #0x10
	add r0, #0x56
	strh r2, [r0]
	add r0, r4, #0
	mov r1, #0xa0
	add r0, #0x58
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0x5a
	strh r2, [r0]
	mov r0, #2
	str r0, [r4, #0x5c]
	pop {r4, pc}
_021D98BA:
	mov r0, #0
	str r0, [r4, #0x5c]
	pop {r4, pc}

	thumb_func_start MOD15_021D98C0
MOD15_021D98C0: ; 0x021D98C0
	push {r3, r4, r5, lr}
	sub sp, #0x30
	add r4, r0, #0
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	beq _021D98D8
	add r0, r4, #0
	add r0, #0x54
	add r1, sp, #8
	bl MOD15_021D9C1C
	b _021D98E2
_021D98D8:
	mov r1, #0x80
	add r0, sp, #8
	strh r1, [r0]
	mov r1, #0x18
	strh r1, [r0, #2]
_021D98E2:
	mov r2, #0
	ldr r0, [r4]
	add r1, sp, #0xc
	add r3, r2, #0
	bl MOD15_021D9550
	mov r2, #0
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r5, sp, #8
	mov r3, #2
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	ldr r0, [r4]
	add r1, sp, #0xc
	bl MOD15_021D9594
	str r0, [r4, #0x3c]
	add r0, r4, #0
	mov r1, #1
	bl MOD15_021D9E98
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0xc
	mov r2, #6
	mov r3, #0x18
	bl MOD15_021D9594
	mov r1, #0xd
	str r0, [r4, #0x40]
	bl FUN_02020130
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0xc
	mov r2, #0xfa
	mov r3, #0x18
	bl MOD15_021D9594
	str r0, [r4, #0x44]
	mov r1, #0xc
	bl FUN_02020130
	ldr r0, [r4, #4]
	bl MOD15_021D86E4
	cmp r0, #2
	beq _021D995E
	ldr r0, [r4, #0x44]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl FUN_020200A0
_021D995E:
	add sp, #0x30
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021D9964
MOD15_021D9964: ; 0x021D9964
	push {r4, lr}
	add r4, r0, #0
	bl MOD15_021D9834
	add r0, r4, #0
	add r0, #0xc
	mov r1, #0xd
	bl FUN_02019620
	ldr r0, [r4, #4]
	bl MOD15_021D86E4
	cmp r0, #0
	beq _021D998A
	cmp r0, #1
	beq _021D99B0
	cmp r0, #2
	beq _021D99FA
	b _021D9A02
_021D998A:
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xc
	add r1, #0x54
	bl MOD15_021D9C30
	ldr r0, [r4, #4]
	mov r1, #0
	bl MOD15_021D8708
	add r1, r4, #0
	add r2, r4, #0
	add r3, r0, #0
	add r0, r4, #0
	add r1, #0xc
	add r2, #0x54
	bl MOD15_021D9C58
	b _021D9A02
_021D99B0:
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xc
	add r1, #0x54
	bl MOD15_021D9C30
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xc
	add r1, #0x58
	bl MOD15_021D9C30
	ldr r0, [r4, #4]
	mov r1, #0
	bl MOD15_021D8708
	add r1, r4, #0
	add r2, r4, #0
	add r3, r0, #0
	add r0, r4, #0
	add r1, #0xc
	add r2, #0x54
	bl MOD15_021D9C58
	ldr r0, [r4, #4]
	mov r1, #1
	bl MOD15_021D8708
	add r1, r4, #0
	add r2, r4, #0
	add r3, r0, #0
	add r0, r4, #0
	add r1, #0xc
	add r2, #0x58
	bl MOD15_021D9C58
	b _021D9A02
_021D99FA:
	add r0, r4, #0
	bl MOD15_021D9A0C
	str r0, [r4, #0x5c]
_021D9A02:
	add r4, #0xc
	add r0, r4, #0
	bl FUN_02019548
	pop {r4, pc}

	thumb_func_start MOD15_021D9A0C
MOD15_021D9A0C: ; 0x021D9A0C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp, #0x10]
	ldr r0, [r0, #4]
	mov r1, #0x23
	bl MOD15_021D8720
	mov r4, #0
	str r0, [sp, #0x1c]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x10]
	add r0, #0x64
	str r4, [sp, #0x18]
	add r5, r4, #0
	bl MOD15_021D9B04
	ldr r7, [sp, #0x10]
	add r0, r7, #0
	str r0, [sp, #0x24]
	add r0, #0xc
	str r0, [sp, #0x24]
	add r0, r7, #0
	add r6, r7, #0
	str r0, [sp, #0x20]
	add r0, #0x64
	add r6, #0x54
	str r0, [sp, #0x20]
_021D9A46:
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x1c]
	bl MOD15_021D9B3C
	cmp r0, #3
	bhi _021D9ADE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9A5E: ; jump table
	.short _021D9A66 - _021D9A5E - 2 ; case 0
	.short _021D9A8E - _021D9A5E - 2 ; case 1
	.short _021D9AD4 - _021D9A5E - 2 ; case 2
	.short _021D9ADA - _021D9A5E - 2 ; case 3
_021D9A66:
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9AFC ; =0x0003040D
	ldr r2, [sp, #0x1c]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x24]
	mov r1, #1
	add r3, r5, #0
	bl FUN_0201BDE0
	ldr r1, [sp, #0x1c]
	mov r0, #1
	mov r2, #0
	bl FUN_02002E14
	add r5, r5, r0
	b _021D9ADE
_021D9A8E:
	add r1, r5, #0
	add r0, r7, #0
	add r1, #0x32
	add r0, #0x54
	strh r1, [r0]
	add r1, r4, #0
	add r0, r7, #0
	add r1, #8
	add r0, #0x56
	strh r1, [r0]
	ldr r0, [sp, #0x24]
	add r1, r6, #0
	bl MOD15_021D9C30
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r0, [r0, #4]
	bl MOD15_021D8708
	add r3, r0, #0
	ldr r0, _021D9B00 ; =0x0000FFFF
	cmp r3, r0
	beq _021D9AC6
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x24]
	add r2, r6, #0
	bl MOD15_021D9C58
_021D9AC6:
	ldr r0, [sp, #0x18]
	add r7, r7, #4
	add r0, r0, #1
	add r6, r6, #4
	str r0, [sp, #0x18]
	add r5, #0x64
	b _021D9ADE
_021D9AD4:
	add r4, #0x10
	mov r5, #0
	b _021D9ADE
_021D9ADA:
	mov r0, #0
	str r0, [sp, #0x14]
_021D9ADE:
	ldr r0, [sp, #0x14]
	cmp r0, #0
	bne _021D9A46
	ldr r0, [sp, #0x10]
	add r0, #0x64
	str r0, [sp, #0x10]
	bl MOD15_021D9B30
	ldr r0, [sp, #0x1c]
	bl String_dtor
	ldr r0, [sp, #0x18]
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9AFC: .word 0x0003040D
_021D9B00: .word 0x0000FFFF

	thumb_func_start MOD15_021D9B04
MOD15_021D9B04: ; 0x021D9B04
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #4]
	mov r1, #0x23
	bl MOD15_021D8720
	str r0, [r4]
	bl String_c_str
	str r0, [r4, #4]
	ldrh r1, [r0]
	ldr r0, _021D9B2C ; =0x0000FFFE
	cmp r1, r0
	bne _021D9B26
	mov r0, #1
	str r0, [r4, #8]
	pop {r4, pc}
_021D9B26:
	mov r0, #0
	str r0, [r4, #8]
	pop {r4, pc}
	.align 2, 0
_021D9B2C: .word 0x0000FFFE

	thumb_func_start MOD15_021D9B30
MOD15_021D9B30: ; 0x021D9B30
	ldr r3, _021D9B38 ; =String_dtor
	ldr r0, [r0]
	bx r3
	nop
_021D9B38: .word String_dtor

	thumb_func_start MOD15_021D9B3C
MOD15_021D9B3C: ; 0x021D9B3C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	str r1, [sp]
	mov ip, r0
	ldr r0, [r4, #8]
	cmp r0, #3
	bhi _021D9BCC
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D9B58: ; jump table
	.short _021D9B60 - _021D9B58 - 2 ; case 0
	.short _021D9BB6 - _021D9B58 - 2 ; case 1
	.short _021D9BC2 - _021D9B58 - 2 ; case 2
	.short _021D9BCC - _021D9B58 - 2 ; case 3
_021D9B60:
	cmp r0, #0
	bne _021D9B9C
	ldr r6, _021D9C04 ; =0x0000FFFE
	mov r3, #0xe
	mov r0, #1
	mov r1, #3
	mov r2, #2
	add r7, r6, #1
	lsl r3, r3, #0xc
_021D9B72:
	ldr r5, [r4, #4]
	ldrh r5, [r5]
	cmp r5, r3
	beq _021D9B84
	cmp r5, r6
	beq _021D9B8C
	cmp r5, r7
	beq _021D9B88
	b _021D9B90
_021D9B84:
	str r2, [r4, #8]
	b _021D9B96
_021D9B88:
	str r1, [r4, #8]
	b _021D9B96
_021D9B8C:
	str r0, [r4, #8]
	b _021D9B96
_021D9B90:
	ldr r5, [r4, #4]
	add r5, r5, #2
	str r5, [r4, #4]
_021D9B96:
	ldr r5, [r4, #8]
	cmp r5, #0
	beq _021D9B72
_021D9B9C:
	ldr r3, [r4, #4]
	mov r2, ip
	sub r3, r3, r2
	lsr r2, r3, #0x1f
	add r2, r3, r2
	asr r2, r2, #1
	ldr r0, [sp]
	mov r1, ip
	add r2, r2, #1
	bl FUN_02021E8C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D9BB6:
	mov r0, ip
	bl FUN_0201B8B8
	str r0, [r4, #4]
	mov r0, #1
	b _021D9BD0
_021D9BC2:
	mov r0, ip
	add r0, r0, #2
	str r0, [r4, #4]
	mov r0, #2
	b _021D9BD0
_021D9BCC:
	mov r0, #3
	pop {r3, r4, r5, r6, r7, pc}
_021D9BD0:
	ldr r1, [r4, #4]
	ldrh r2, [r1]
	mov r1, #0xe
	lsl r1, r1, #0xc
	cmp r2, r1
	beq _021D9BEA
	ldr r1, _021D9C04 ; =0x0000FFFE
	cmp r2, r1
	beq _021D9BF6
	add r1, r1, #1
	cmp r2, r1
	beq _021D9BF0
	b _021D9BFC
_021D9BEA:
	mov r1, #2
	str r1, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_021D9BF0:
	mov r1, #3
	str r1, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_021D9BF6:
	mov r1, #1
	str r1, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_021D9BFC:
	mov r1, #0
	str r1, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9C04: .word 0x0000FFFE

	thumb_func_start MOD15_021D9C08
MOD15_021D9C08: ; 0x021D9C08
	mov r2, #0
	ldrsh r2, [r0, r2]
	sub r2, #0x30
	strh r2, [r1]
	mov r2, #2
	ldrsh r0, [r0, r2]
	sub r0, #8
	strh r0, [r1, #2]
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D9C1C
MOD15_021D9C1C: ; 0x021D9C1C
	mov r2, #0
	ldrsh r2, [r0, r2]
	add r2, #0x18
	strh r2, [r1]
	mov r2, #2
	ldrsh r0, [r0, r2]
	add r0, #8
	strh r0, [r1, #2]
	bx lr
	.align 2, 0

	thumb_func_start MOD15_021D9C30
MOD15_021D9C30: ; 0x021D9C30
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r0, r1, #0
	add r1, sp, #8
	bl MOD15_021D9C08
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r3, sp, #8
	ldrh r2, [r3]
	ldrh r3, [r3, #2]
	add r0, r4, #0
	mov r1, #0xe
	bl FUN_020196F4
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD15_021D9C58
MOD15_021D9C58: ; 0x021D9C58
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, _021D9CA8 ; =0x0000FFFF
	add r6, r3, #0
	add r4, r1, #0
	cmp r6, r0
	beq _021D9CA2
	add r0, r2, #0
	add r1, sp, #0x10
	bl MOD15_021D9C08
	ldr r1, [r5, #0x4c]
	add r0, r6, #0
	bl FUN_02013A58
	ldr r1, [r5, #0x4c]
	mov r0, #1
	mov r2, #0
	bl FUN_02002E14
	add r3, sp, #0x10
	mov r0, #2
	ldrsh r0, [r3, r0]
	mov r6, #0
	mov r1, #1
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9CAC ; =0x0005060E
	str r0, [sp, #8]
	str r6, [sp, #0xc]
	ldrsh r3, [r3, r6]
	ldr r2, [r5, #0x4c]
	add r0, r4, #0
	bl FUN_0201BDE0
_021D9CA2:
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_021D9CA8: .word 0x0000FFFF
_021D9CAC: .word 0x0005060E

	thumb_func_start MOD15_021D9CB0
MOD15_021D9CB0: ; 0x021D9CB0
	ldr r0, [r0, #0x5c]
	bx lr

	thumb_func_start MOD15_021D9CB4
MOD15_021D9CB4: ; 0x021D9CB4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r5, r1, #0
	add r0, #0x1c
	mov r1, #9
	bl FUN_02019620
	cmp r5, #3
	bhi _021D9DB0
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9CD4: ; jump table
	.short _021D9CDC - _021D9CD4 - 2 ; case 0
	.short _021D9D66 - _021D9CD4 - 2 ; case 1
	.short _021D9D40 - _021D9CD4 - 2 ; case 2
	.short _021D9D8C - _021D9CD4 - 2 ; case 3
_021D9CDC:
	mov r0, #2
	mov r1, #0x3c
	mov r2, #0
	bl FUN_0200AA90
	add r5, r0, #0
	mov r0, #0x4b
	lsl r0, r0, #2
	mov r1, #0
	bl String_ctor
	mov r1, #0
	add r6, r0, #0
	add r0, r5, #0
	add r2, r1, #0
	bl FUN_0200AEE0
	ldr r0, [r4, #4]
	bl MOD15_021D86E8
	add r1, r0, #0
	ldr r0, [r4, #0x48]
	ldr r2, [r4, #0x4c]
	bl ReadMsgDataIntoString
	ldr r2, [r4, #0x4c]
	add r0, r5, #0
	add r1, r6, #0
	bl StringExpandPlaceholders
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9DBC ; =0x00010209
	mov r1, #1
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x1c
	add r2, r6, #0
	str r3, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r6, #0
	bl String_dtor
	add r0, r5, #0
	bl FUN_0200AB18
	b _021D9DB0
_021D9D40:
	ldr r0, [r4, #0x48]
	ldr r2, [r4, #0x4c]
	mov r1, #6
	bl ReadMsgDataIntoString
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9DBC ; =0x00010209
	mov r1, #1
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x4c]
	add r0, #0x1c
	bl FUN_0201BDE0
	b _021D9DB0
_021D9D66:
	ldr r0, [r4, #0x48]
	ldr r2, [r4, #0x4c]
	mov r1, #7
	bl ReadMsgDataIntoString
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9DBC ; =0x00010209
	mov r1, #1
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x4c]
	add r0, #0x1c
	bl FUN_0201BDE0
	b _021D9DB0
_021D9D8C:
	ldr r0, [r4, #0x48]
	ldr r2, [r4, #0x4c]
	mov r1, #8
	bl ReadMsgDataIntoString
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9DBC ; =0x00010209
	mov r1, #1
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x4c]
	add r0, #0x1c
	bl FUN_0201BDE0
_021D9DB0:
	add r4, #0x1c
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D9DBC: .word 0x00010209

	thumb_func_start MOD15_021D9DC0
MOD15_021D9DC0: ; 0x021D9DC0
	ldr r3, _021D9DC8 ; =MOD15_021D9E98
	mov r1, #0
	bx r3
	nop
_021D9DC8: .word MOD15_021D9E98

	thumb_func_start MOD15_021D9DCC
MOD15_021D9DCC: ; 0x021D9DCC
	ldr r3, _021D9DD4 ; =MOD15_021D9E98
	mov r1, #1
	bx r3
	nop
_021D9DD4: .word MOD15_021D9E98

	thumb_func_start MOD15_021D9DD8
MOD15_021D9DD8: ; 0x021D9DD8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x3c]
	bl FUN_020200A0
	add r0, r4, #0
	mov r1, #1
	bl MOD15_021D9E98
	pop {r4, pc}

	thumb_func_start MOD15_021D9DEC
MOD15_021D9DEC: ; 0x021D9DEC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl MOD15_021D86E4
	cmp r0, #2
	bne _021D9E0A
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, #0x44]
	mov r1, #0
	bl FUN_020200A0
_021D9E0A:
	pop {r4, pc}

	thumb_func_start MOD15_021D9E0C
MOD15_021D9E0C: ; 0x021D9E0C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl MOD15_021D86E4
	cmp r0, #2
	bne _021D9E3A
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4, #0x44]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4, #0x40]
	mov r1, #0xd
	bl FUN_02020130
	ldr r0, [r4, #0x44]
	mov r1, #0xc
	bl FUN_02020130
_021D9E3A:
	pop {r4, pc}

	thumb_func_start MOD15_021D9E3C
MOD15_021D9E3C: ; 0x021D9E3C
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	beq _021D9E6C
	add r2, r4, #0
	lsl r0, r1, #2
	add r2, #0x54
	add r0, r2, r0
	add r1, sp, #0
	bl MOD15_021D9C1C
	add r1, sp, #0
	mov r2, #0
	ldrsh r0, [r1, r2]
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #2
	ldrsh r0, [r1, r0]
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	b _021D9E84
_021D9E6C:
	mov r0, #2
	lsl r0, r0, #0x12
	str r0, [sp, #4]
	mov r0, #6
	lsl r0, r0, #0xe
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x3c]
	add r1, sp, #4
	bl FUN_02020044
_021D9E84:
	ldr r0, [r4, #0x3c]
	add r1, sp, #4
	bl FUN_02020044
	add r0, r4, #0
	mov r1, #1
	bl MOD15_021D9E98
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start MOD15_021D9E98
MOD15_021D9E98: ; 0x021D9E98
	push {r3, lr}
	ldr r2, [r0, #0x5c]
	cmp r2, #0
	beq _021D9EB6
	cmp r1, #0
	ldr r0, [r0, #0x3c]
	beq _021D9EAE
	mov r1, #0
	bl FUN_02020130
	pop {r3, pc}
_021D9EAE:
	mov r1, #1
	bl FUN_02020130
	pop {r3, pc}
_021D9EB6:
	cmp r1, #0
	ldr r0, [r0, #0x3c]
	beq _021D9EC4
	mov r1, #0xe
	bl FUN_02020130
	pop {r3, pc}
_021D9EC4:
	mov r1, #0xf
	bl FUN_02020130
	pop {r3, pc}

	thumb_func_start MOD15_021D9ECC
MOD15_021D9ECC: ; 0x021D9ECC
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r1, #0
	add r0, #0x2c
	mov r1, #9
	bl FUN_02019620
	ldr r0, [r5, #0x48]
	ldr r2, [r5, #0x4c]
	mov r1, #9
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9F54 ; =0x00010209
	mov r3, #0xe
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r5, #0
	ldr r2, [r5, #0x4c]
	add r0, #0x2c
	bl FUN_0201BDE0
	ldr r0, [r5, #0x48]
	ldr r2, [r5, #0x4c]
	mov r1, #0xa
	bl ReadMsgDataIntoString
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9F54 ; =0x00010209
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r5, #0
	ldr r2, [r5, #0x4c]
	add r0, #0x2c
	mov r3, #0xe
	bl FUN_0201BDE0
	ldr r2, [r5, #0x60]
	add r0, r5, #0
	lsl r2, r2, #0x10
	add r0, #0x2c
	mov r1, #0
	lsr r2, r2, #0x10
	mov r3, #0xe
	bl FUN_0200CCA4
	add r1, r5, #0
	ldr r0, [r5, #0x50]
	add r1, #0x2c
	mov r2, #0
	lsl r3, r4, #4
	bl FUN_020136F8
	add r5, #0x2c
	add r0, r5, #0
	bl FUN_020191D0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D9F54: .word 0x00010209

	thumb_func_start MOD15_021D9F58
MOD15_021D9F58: ; 0x021D9F58
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0xe
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0
	add r4, r1, #0
	add r0, #0x2c
	mov r1, #9
	add r3, r2, #0
	bl FUN_020196F4
	ldr r0, [r5, #0x50]
	add r5, #0x2c
	add r1, r5, #0
	mov r2, #0
	lsl r3, r4, #4
	bl FUN_020136F8
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021D9F88
MOD15_021D9F88: ; 0x021D9F88
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x2c
	mov r1, #0
	bl FUN_0200CCF8
	add r4, #0x2c
	add r0, r4, #0
	bl FUN_02019570
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021D9FA0
MOD15_021D9FA0: ; 0x021D9FA0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0x23
	mov r1, #0x10
	add r6, r2, #0
	bl AllocFromHeap
	str r5, [r0]
	str r4, [r0, #4]
	str r6, [r0, #8]
	mov r1, #0
	str r1, [r0, #0xc]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD15_021D9FBC
MOD15_021D9FBC: ; 0x021D9FBC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021D9FCA
	bl FUN_0201FFC8
_021D9FCA:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021D9FD4
MOD15_021D9FD4: ; 0x021D9FD4
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD15_021D9548
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x23
	str r0, [sp, #0xc]
	mov r0, #0x4c
	mov r1, #4
	add r2, r4, #0
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x23
	str r0, [sp, #0xc]
	mov r0, #0x4c
	mov r1, #5
	add r2, r4, #0
	mov r3, #3
	bl FUN_0200687C
	ldr r1, _021DA03C ; =0x021DBA00
	add r0, r4, #0
	mov r2, #0
	bl MOD15_021DA044
	ldr r1, _021DA040 ; =0x021DBA08
	add r0, r4, #0
	mov r2, #1
	bl MOD15_021DA044
	add r0, r5, #0
	bl MOD15_021DA0B8
	add r0, r4, #0
	mov r1, #3
	bl FUN_02017CD0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DA03C: .word MOD15_021DBA00
_021DA040: .word MOD15_021DBA08

	thumb_func_start MOD15_021DA044
MOD15_021DA044: ; 0x021DA044
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r1, #0
	add r4, r2, #0
	add r1, sp, #0x10
	add r2, r5, #0
	bl FUN_02019150
	add r0, sp, #0x10
	bl FUN_02019270
	add r0, sp, #0x10
	mov r1, #0xe
	bl FUN_02019620
	ldr r1, _021DA0B0 ; =0x00000183
	mov r0, #0x1a
	add r2, r4, #0
	mov r3, #0x23
	bl ReadMsgData_NewNarc_NewString
	add r4, r0, #0
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl FUN_02002E14
	ldrb r1, [r5, #3]
	add r2, r4, #0
	lsl r1, r1, #3
	sub r0, r1, r0
	mov r1, #0
	lsr r3, r0, #1
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021DA0B4 ; =0x0001020E
	str r0, [sp, #8]
	add r0, sp, #0x10
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, sp, #0x10
	bl FUN_02019548
	add r0, r4, #0
	bl String_dtor
	add r0, sp, #0x10
	bl FUN_02019178
	add sp, #0x20
	pop {r3, r4, r5, pc}
	nop
_021DA0B0: .word 0x00000183
_021DA0B4: .word 0x0001020E

	thumb_func_start MOD15_021DA0B8
MOD15_021DA0B8: ; 0x021DA0B8
	push {r3, r4, lr}
	sub sp, #0x2c
	add r4, r0, #0
	ldr r0, [r4]
	add r1, sp, #8
	mov r2, #0
	mov r3, #3
	bl MOD15_021D9550
	mov r0, #5
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #8
	mov r2, #0x40
	mov r3, #0x38
	bl MOD15_021D9594
	str r0, [r4, #0xc]
	mov r1, #2
	bl FUN_02020130
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x2c
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021DA0F4
MOD15_021DA0F4: ; 0x021DA0F4
	ldr r3, _021DA0FC ; =FUN_02020130
	ldr r0, [r0, #0xc]
	mov r1, #3
	bx r3
	.align 2, 0
_021DA0FC: .word FUN_02020130

	thumb_func_start MOD15_021DA100
MOD15_021DA100: ; 0x021DA100
	ldr r3, _021DA108 ; =FUN_02020130
	ldr r0, [r0, #0xc]
	mov r1, #2
	bx r3
	.align 2, 0
_021DA108: .word FUN_02020130

	thumb_func_start MOD15_021DA10C
MOD15_021DA10C: ; 0x021DA10C
	ldr r3, _021DA114 ; =FUN_020200A0
	ldr r0, [r0, #0xc]
	bx r3
	nop
_021DA114: .word FUN_020200A0

	thumb_func_start MOD15_021DA118
MOD15_021DA118: ; 0x021DA118
	ldr r3, _021DA120 ; =FUN_02020128
	ldr r0, [r0, #0xc]
	bx r3
	nop
_021DA120: .word FUN_02020128

	thumb_func_start MOD15_021DA124
MOD15_021DA124: ; 0x021DA124
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0
	str r0, [sp, #8]
	cmp r1, #0
	beq _021DA136
	cmp r1, #1
	beq _021DA144
_021DA136:
	mov r0, #1
	lsl r0, r0, #0x12
	str r0, [sp]
	mov r0, #0xe
	lsl r0, r0, #0xe
	str r0, [sp, #4]
	b _021DA150
_021DA144:
	mov r0, #3
	lsl r0, r0, #0x12
	str r0, [sp]
	mov r0, #0xe
	lsl r0, r0, #0xe
	str r0, [sp, #4]
_021DA150:
	ldr r0, [r4, #0xc]
	add r1, sp, #0
	bl FUN_02020044
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_02020130
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD15_021DA164
MOD15_021DA164: ; 0x021DA164
	push {r3, lr}
	ldr r0, [r0]
	bl MOD15_021D9548
	mov r1, #3
	add r2, r1, #0
	mov r3, #0x40
	bl FUN_020179E0
	pop {r3, pc}

	thumb_func_start MOD15_021DA178
MOD15_021DA178: ; 0x021DA178
	push {r3, lr}
	ldr r0, [r0]
	bl MOD15_021D9548
	mov r1, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_020179E0
	pop {r3, pc}

	thumb_func_start MOD15_021DA18C
MOD15_021DA18C: ; 0x021DA18C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x23
	mov r1, #0x60
	add r7, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	str r6, [r4, #4]
	str r7, [r4, #8]
	add r0, r5, #0
	bl MOD15_021D9548
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x10]
	str r0, [r4, #0x18]
	str r0, [r4, #0x5c]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD15_021DA1B8
MOD15_021DA1B8: ; 0x021DA1B8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	beq _021DA1C6
	bl FUN_0201FFC8
_021DA1C6:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021DA1D0
MOD15_021DA1D0: ; 0x021DA1D0
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD15_021D9548
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x23
	str r0, [sp, #0xc]
	mov r0, #0x4c
	mov r1, #2
	add r2, r4, #0
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x23
	str r0, [sp, #0xc]
	mov r0, #0x4c
	mov r1, #3
	add r2, r4, #0
	bl FUN_0200687C
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #5
	bl MOD15_021DA2AC
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD15_021DA3B4
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD15_021DA480
	mov r2, #0
	add r0, r4, #0
	mov r1, #1
	sub r3, r2, #4
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #1
	mov r2, #3
	mov r3, #2
	bl FUN_020179E0
	add r0, r5, #0
	bl MOD15_021DA54C
	mov r1, #2
	add r2, r1, #0
	ldr r0, _021DA2A0 ; =0x04000050
	sub r2, #0xc
	bl G2x_SetBlendBrightness_
	ldr r0, _021DA2A4 ; =0x04000048
	mov r2, #0x3f
	ldrh r3, [r0]
	mov r1, #0x1f
	bic r3, r2
	orr r3, r1
	mov r1, #0x20
	orr r3, r1
	strh r3, [r0]
	ldrh r3, [r0, #2]
	bic r3, r2
	mov r2, #0x1d
	orr r2, r3
	orr r2, r1
	strh r2, [r0, #2]
	add r2, r0, #0
	mov r3, #0xff
	sub r2, #8
	strh r3, [r2]
	mov r2, #0xa0
	sub r0, r0, #4
	strh r2, [r0]
	lsl r3, r1, #0x15
	ldr r2, [r3]
	ldr r0, _021DA2A8 ; =0xFFFF1FFF
	and r2, r0
	lsl r0, r1, #8
	orr r0, r2
	str r0, [r3]
	add r0, r4, #0
	mov r1, #1
	bl FUN_02017CD0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021DA2A0: .word 0x04000050
_021DA2A4: .word 0x04000048
_021DA2A8: .word 0xFFFF1FFF

	thumb_func_start MOD15_021DA2AC
MOD15_021DA2AC: ; 0x021DA2AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r6, r2, #0
	str r0, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r2, _021DA3A4 ; =0x00000181
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x23
	bl NewMsgDataFromNarc
	str r0, [sp, #0x20]
	mov r0, #9
	mov r7, #1
	str r0, [sp, #0x24]
	mov r4, #0
_021DA2CC:
	cmp r4, #0
	beq _021DA2E4
	add r0, r4, #0
	mov r1, #3
	bl _s32_div_f
	cmp r1, #0
	bne _021DA2E4
	ldr r0, [sp, #0x24]
	mov r7, #1
	add r0, r0, #3
	str r0, [sp, #0x24]
_021DA2E4:
	ldr r0, [sp, #0x14]
	add r1, r4, #0
	ldr r0, [r0, #8]
	bl FUN_020892C4
	cmp r0, #0
	beq _021DA302
	ldr r0, [sp, #0x20]
	add r1, r4, #0
	bl NewString_ReadMsgData
	add r5, r0, #0
	ldr r0, _021DA3A8 ; =0x0001020F
	str r0, [sp, #0x1c]
	b _021DA310
_021DA302:
	ldr r0, [sp, #0x20]
	mov r1, #0xc
	bl NewString_ReadMsgData
	add r5, r0, #0
	ldr r0, _021DA3AC ; =0x0003040F
	str r0, [sp, #0x1c]
_021DA310:
	ldr r0, _021DA3B0 ; =0x000003EE
	cmp r6, r0
	blo _021DA31A
	bl ErrorHandling
_021DA31A:
	ldr r0, [sp, #0x24]
	lsl r3, r7, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x18]
	add r1, sp, #0x28
	mov r2, #1
	lsr r3, r3, #0x18
	bl FUN_02019064
	add r0, sp, #0x28
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0
	add r1, r5, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x48
	sub r0, r1, r0
	lsr r3, r0, #1
	mov r0, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, sp, #0x28
	add r2, r5, #0
	bl FUN_0201BDE0
	add r0, sp, #0x28
	bl FUN_02019270
	add r0, sp, #0x28
	bl FUN_02019548
	add r0, r5, #0
	bl String_dtor
	add r0, sp, #0x28
	bl FUN_02019178
	add r4, r4, #1
	add r6, #0x12
	add r7, #0xa
	cmp r4, #0xc
	blt _021DA2CC
	ldr r0, [sp, #0x20]
	bl DestroyMsgData
	add r0, r6, #0
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DA3A4: .word 0x00000181
_021DA3A8: .word 0x0001020F
_021DA3AC: .word 0x0003040F
_021DA3B0: .word 0x000003EE

	thumb_func_start MOD15_021DA3B4
MOD15_021DA3B4: ; 0x021DA3B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r4, r1, #0
	mov r1, #0xce
	add r6, r0, #0
	lsl r1, r1, #2
	add r0, r2, #0
	str r2, [sp, #0x14]
	cmp r0, r1
	blo _021DA3CC
	bl ErrorHandling
_021DA3CC:
	mov r0, #0xa
	str r0, [sp]
	mov r0, #0x19
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	add r1, sp, #0x20
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	add r0, r4, #0
	mov r2, #1
	mov r3, #0x22
	bl FUN_02019064
	mov r0, #4
	mov r1, #0x23
	bl String_ctor
	add r4, r0, #0
	add r0, sp, #0x20
	mov r1, #0xf
	bl FUN_02019620
	bl MOD15_021DB770
	add r7, r0, #0
	ldr r5, _021DA474 ; =0x00000000
	beq _021DA452
_021DA40C:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD15_021DB774
	add r0, r5, #0
	add r1, sp, #0x1c
	add r2, sp, #0x18
	bl MOD15_021DB798
	ldr r0, [r6, #8]
	add r1, r5, #0
	bl FUN_02089300
	cmp r0, #0
	beq _021DA42E
	ldr r1, _021DA478 ; =0x0001020F
	b _021DA430
_021DA42E:
	ldr r1, _021DA47C ; =0x0003040F
_021DA430:
	ldr r0, [sp, #0x18]
	add r2, r4, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r3, [sp, #0x1c]
	add r0, sp, #0x20
	mov r1, #0
	add r3, r3, #3
	bl FUN_0201BDE0
	add r5, r5, #1
	cmp r5, r7
	blo _021DA40C
_021DA452:
	add r0, sp, #0x20
	bl FUN_02019548
	add r0, sp, #0x20
	bl FUN_02019270
	add r0, r4, #0
	bl String_dtor
	add r0, sp, #0x20
	bl FUN_02019178
	ldr r0, [sp, #0x14]
	add r0, #0xc8
	str r0, [sp, #0x14]
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DA474: .word 0x00000000
_021DA478: .word 0x0001020F
_021DA47C: .word 0x0003040F

	thumb_func_start MOD15_021DA480
MOD15_021DA480: ; 0x021DA480
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r2, #0
	str r1, [sp, #0x14]
	ldr r2, _021DA540 ; =0x00000181
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x23
	bl NewMsgDataFromNarc
	mov r1, #0xd
	str r0, [sp, #0x20]
	bl NewString_ReadMsgData
	str r0, [sp, #0x1c]
	mov r0, #0
	ldr r1, [sp, #0x1c]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x40
	sub r0, r1, r0
	lsr r0, r0, #1
	ldr r4, _021DA544 ; =0x021DBA10
	str r0, [sp, #0x18]
	mov r7, #0
	add r6, sp, #0x24
_021DA4B6:
	mov r0, #0x3f
	lsl r0, r0, #4
	cmp r5, r0
	blo _021DA4C2
	bl ErrorHandling
_021DA4C2:
	ldrh r0, [r4, #2]
	add r1, r6, #0
	mov r2, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldrh r3, [r4]
	ldr r0, [sp, #0x14]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02019064
	add r0, r6, #0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021DA548 ; =0x0001020F
	ldr r2, [sp, #0x1c]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r3, [sp, #0x18]
	add r0, r6, #0
	mov r1, #0
	bl FUN_0201BDE0
	add r0, r6, #0
	bl FUN_02019270
	add r0, r6, #0
	bl FUN_02019548
	add r0, r6, #0
	bl FUN_02019178
	add r7, r7, #1
	add r5, #0x10
	add r4, r4, #4
	cmp r7, #2
	blo _021DA4B6
	ldr r0, [sp, #0x1c]
	bl String_dtor
	ldr r0, [sp, #0x20]
	bl DestroyMsgData
	add r0, r5, #0
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_021DA540: .word 0x00000181
_021DA544: .word MOD15_021DBA10
_021DA548: .word 0x0001020F

	thumb_func_start MOD15_021DA54C
MOD15_021DA54C: ; 0x021DA54C
	push {r3, r4, lr}
	sub sp, #0x2c
	add r4, r0, #0
	ldr r0, [r4]
	add r1, sp, #8
	mov r2, #0
	mov r3, #1
	bl MOD15_021D9550
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #8
	mov r2, #0x30
	mov r3, #0x36
	bl MOD15_021D9594
	str r0, [r4, #0x5c]
	mov r1, #4
	bl FUN_02020130
	ldr r0, [r4, #0x5c]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x2c
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021DA588
MOD15_021DA588: ; 0x021DA588
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x5c]
	add r4, r1, #0
	bl FUN_020200A0
	cmp r4, #0
	beq _021DA5B2
	ldr r0, [r5, #4]
	bl MOD15_021D86F4
	cmp r0, #0
	ldr r0, [r5, #0x5c]
	bne _021DA5AC
	mov r1, #4
	bl FUN_02020130
	pop {r3, r4, r5, pc}
_021DA5AC:
	mov r1, #6
	bl FUN_02020130
_021DA5B2:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021DA5B4
MOD15_021DA5B4: ; 0x021DA5B4
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, [r4, #4]
	add r5, r1, #0
	bl MOD15_021D86F4
	mov r1, #0
	str r1, [sp, #0x10]
	cmp r5, #0xfe
	bne _021DA5D6
	mov r0, #0x84
	str r0, [sp, #8]
	mov r0, #0x96
	str r0, [sp, #0xc]
	mov r5, #0x10
	b _021DA616
_021DA5D6:
	cmp r0, #0
	bne _021DA5FE
	add r0, r5, #0
	mov r1, #3
	bl _u32_div_f
	mov r0, #0x50
	mul r0, r1
	add r0, #0x30
	str r0, [sp, #8]
	add r0, r5, #0
	mov r1, #3
	bl _u32_div_f
	mov r1, #0x18
	mul r1, r0
	add r1, #0x36
	str r1, [sp, #0xc]
	mov r5, #4
	b _021DA616
_021DA5FE:
	add r0, r5, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD15_021DB798
	ldr r0, [sp, #4]
	mov r5, #6
	add r0, #0x1a
	str r0, [sp, #8]
	ldr r0, [sp]
	add r0, #0x3e
	str r0, [sp, #0xc]
_021DA616:
	ldr r0, [sp, #8]
	add r1, sp, #8
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x5c]
	bl FUN_02020044
	ldr r0, [r4, #0x5c]
	add r1, r5, #0
	bl FUN_02020130
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021DA638
MOD15_021DA638: ; 0x021DA638
	push {r3, lr}
	mov r3, #0
	str r3, [r0, #0x14]
	mov r1, #0x10
	str r1, [sp]
	mov r1, #2
	add r2, r1, #0
	add r0, #0x1c
	sub r2, #0xc
	bl MOD15_021DB6DC
	pop {r3, pc}

	thumb_func_start MOD15_021DA650
MOD15_021DA650: ; 0x021DA650
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021DA662
	cmp r0, #1
	beq _021DA68C
	b _021DA698
_021DA662:
	add r0, r4, #0
	add r0, #0x1c
	bl MOD15_021DB71C
	cmp r0, #0
	beq _021DA698
	mov r0, #0x18
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #1
	ldr r1, [r4, #0xc]
	add r0, #0x3c
	add r3, r2, #0
	bl MOD15_021DB564
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	b _021DA698
_021DA68C:
	add r4, #0x3c
	add r0, r4, #0
	bl MOD15_021DB5B8
	add sp, #8
	pop {r4, pc}
_021DA698:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021DA6A0
MOD15_021DA6A0: ; 0x021DA6A0
	push {r3, lr}
	sub sp, #8
	add r1, r0, #0
	mov r0, #0
	str r0, [r1, #0x14]
	sub r0, #0x18
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	add r0, r1, #0
	mov r2, #1
	ldr r1, [r1, #0xc]
	add r0, #0x3c
	add r3, r2, #0
	bl MOD15_021DB564
	add sp, #8
	pop {r3, pc}

	thumb_func_start MOD15_021DA6C4
MOD15_021DA6C4: ; 0x021DA6C4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021DA6D6
	cmp r0, #1
	beq _021DA6FE
	b _021DA70A
_021DA6D6:
	add r0, r4, #0
	add r0, #0x3c
	bl MOD15_021DB5B8
	cmp r0, #0
	beq _021DA70A
	mov r0, #0x10
	mov r2, #0
	str r0, [sp]
	add r0, r4, #0
	add r3, r2, #0
	add r0, #0x1c
	mov r1, #2
	sub r3, #0xa
	bl MOD15_021DB6DC
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	b _021DA70A
_021DA6FE:
	add r4, #0x1c
	add r0, r4, #0
	bl MOD15_021DB71C
	add sp, #4
	pop {r3, r4, pc}
_021DA70A:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD15_021DA710
MOD15_021DA710: ; 0x021DA710
	push {r3, lr}
	ldr r0, [r0, #0xc]
	mov r1, #1
	mov r2, #3
	mov r3, #2
	bl FUN_020179E0
	pop {r3, pc}

	thumb_func_start MOD15_021DA720
MOD15_021DA720: ; 0x021DA720
	push {r3, lr}
	mov r2, #0
	mov r1, #0x10
	add r3, r2, #0
	str r1, [sp]
	add r0, #0x1c
	mov r1, #2
	sub r3, #0xa
	bl MOD15_021DB6DC
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD15_021DA738
MOD15_021DA738: ; 0x021DA738
	ldr r3, _021DA740 ; =MOD15_021DB71C
	add r0, #0x1c
	bx r3
	nop
_021DA740: .word MOD15_021DB71C

	thumb_func_start MOD15_021DA744
MOD15_021DA744: ; 0x021DA744
	push {r3, lr}
	sub sp, #8
	mov r1, #0
	str r1, [sp]
	mov r1, #0xc
	str r1, [sp, #4]
	add r0, #0x1c
	mov r1, #2
	mov r2, #0x3f
	mov r3, #0x7c
	bl MOD15_021DB648
	add sp, #8
	pop {r3, pc}

	thumb_func_start MOD15_021DA760
MOD15_021DA760: ; 0x021DA760
	push {r3, lr}
	add r0, #0x1c
	bl MOD15_021DB678
	cmp r0, #0
	beq _021DA778
	mov r0, #1
	mov r1, #0
	bl FUN_0201797C
	mov r0, #1
	pop {r3, pc}
_021DA778:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD15_021DA77C
MOD15_021DA77C: ; 0x021DA77C
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021DA7B4 ; =0x04000050
	mov r1, #2
	mov r2, #0x3f
	mov r3, #0
	bl G2x_SetBlendAlpha_
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201797C
	mov r0, #0x7c
	str r0, [sp]
	mov r0, #0xc
	add r4, #0x1c
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #2
	mov r2, #0x3f
	mov r3, #0
	bl MOD15_021DB648
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_021DA7B4: .word 0x04000050

	thumb_func_start MOD15_021DA7B8
MOD15_021DA7B8: ; 0x021DA7B8
	ldr r3, _021DA7C0 ; =MOD15_021DB678
	add r0, #0x1c
	bx r3
	nop
_021DA7C0: .word MOD15_021DB678

	thumb_func_start MOD15_021DA7C4
MOD15_021DA7C4: ; 0x021DA7C4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl MOD15_021D86F4
	cmp r0, #0
	bne _021DA7D8
	mov r3, #3
	mvn r3, r3
	b _021DA7DA
_021DA7D8:
	mov r3, #0xfc
_021DA7DA:
	ldr r0, [r4, #0xc]
	mov r1, #1
	mov r2, #0
	bl FUN_020179E0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021DA7E8
MOD15_021DA7E8: ; 0x021DA7E8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl MOD15_021D86F4
	cmp r0, #0
	bne _021DA7FE
	mov r0, #0xff
	mvn r0, r0
	b _021DA802
_021DA7FE:
	mov r0, #1
	lsl r0, r0, #8
_021DA802:
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	ldr r1, [r4, #0xc]
	add r0, #0x3c
	mov r2, #1
	mov r3, #0
	bl MOD15_021DB564
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021DA81C
MOD15_021DA81C: ; 0x021DA81C
	ldr r3, _021DA824 ; =MOD15_021DB5B8
	add r0, #0x3c
	bx r3
	nop
_021DA824: .word MOD15_021DB5B8

	thumb_func_start MOD15_021DA828
MOD15_021DA828: ; 0x021DA828
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x23
	mov r1, #0x94
	add r7, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	str r6, [r4, #4]
	str r7, [r4, #8]
	add r0, r5, #0
	bl MOD15_021D9548
	str r0, [r4, #0xc]
	mov r0, #0x20
	mov r1, #0x23
	bl String_ctor
	str r0, [r4, #0x3c]
	mov r0, #0
	str r0, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	mov r0, #0x20
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x10
	mov r2, #2
	mov r3, #4
	bl FUN_02019064
	mov r3, #0
	str r3, [sp]
	mov r1, #0xc
	str r1, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x20
	mov r2, #2
	bl FUN_02019064
	mov r0, #0
	str r0, [r4, #0x30]
	str r0, [r4, #0x34]
	str r0, [r4, #0x38]
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD15_021DA8A4
MOD15_021DA8A4: ; 0x021DA8A4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	cmp r0, #0
	beq _021DA8B2
	bl FUN_0201FFC8
_021DA8B2:
	ldr r0, [r4, #0x34]
	cmp r0, #0
	beq _021DA8BC
	bl FUN_0201FFC8
_021DA8BC:
	ldr r0, [r4, #0x38]
	cmp r0, #0
	beq _021DA8C6
	bl FUN_0201FFC8
_021DA8C6:
	ldr r0, [r4, #0x3c]
	cmp r0, #0
	beq _021DA8D0
	bl String_dtor
_021DA8D0:
	add r0, r4, #0
	add r0, #0x20
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0x10
	bl FUN_02019178
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD15_021DA8E8
MOD15_021DA8E8: ; 0x021DA8E8
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD15_021D9548
	add r4, r0, #0
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x23
	bl FUN_02017F18
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	add r0, r4, #0
	mov r1, #2
	add r3, r2, #0
	bl FUN_02018540
	add r0, r5, #0
	add r0, #0x10
	mov r1, #0
	bl FUN_02019620
	add r0, r5, #0
	add r0, #0x10
	bl FUN_02019270
	add r0, r5, #0
	add r0, #0x10
	bl FUN_02019548
	add r0, r4, #0
	mov r1, #2
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD15_021DA950
	mov r0, #2
	mov r1, #0
	bl FUN_0201797C
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD15_021DA950
MOD15_021DA950: ; 0x021DA950
	push {r3, r4, lr}
	sub sp, #0x2c
	add r4, r0, #0
	ldr r0, [r4]
	add r1, sp, #8
	mov r2, #0
	mov r3, #2
	bl MOD15_021D9550
	mov r0, #3
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #8
	mov r2, #0x48
	mov r3, #0x38
	bl MOD15_021D9594
	str r0, [r4, #0x30]
	mov r1, #8
	bl FUN_02020130
	ldr r0, [r4, #0x30]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #4
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #8
	mov r2, #0xf0
	mov r3, #0x40
	bl MOD15_021D9594
	str r0, [r4, #0x34]
	mov r1, #0xb
	bl FUN_02020130
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #4
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #8
	mov r2, #0xf0
	mov r3, #0x90
	bl MOD15_021D9594
	str r0, [r4, #0x38]
	mov r1, #0xa
	bl FUN_02020130
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x2c
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021DA9D4
MOD15_021DA9D4: ; 0x021DA9D4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r0, #0x10
	mov r1, #0
	bl FUN_02019620
	add r0, r6, #0
	bl MOD15_021DAD78
	ldr r0, [r6, #4]
	bl MOD15_021D8744
	add r7, r0, #0
	cmp r7, #0xa
	bls _021DA9F4
	mov r7, #0xa
_021DA9F4:
	add r0, r6, #0
	add r0, #0x8c
	mov r5, #0
	ldr r4, [r0]
	cmp r7, #0
	bls _021DAA18
_021DAA00:
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl MOD15_021DAD98
	mov r0, #1
	tst r0, r5
	beq _021DAA12
	add r4, #0x18
_021DAA12:
	add r5, r5, #1
	cmp r5, r7
	blo _021DAA00
_021DAA18:
	add r6, #0x10
	add r0, r6, #0
	bl FUN_02019548
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD15_021DAA24
MOD15_021DAA24: ; 0x021DAA24
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021DAABC ; =0x04000050
	mov r1, #4
	mov r2, #0x3f
	mov r3, #0
	bl G2x_SetBlendAlpha_
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	ldr r1, _021DAAC0 ; =0x04000048
	ldr r0, _021DAAC4 ; =0xFFFFC0FF
	ldrh r2, [r1]
	mov r5, #0xff
	and r2, r0
	mov r0, #0x1f
	lsl r0, r0, #8
	orr r2, r0
	lsr r0, r1, #0xd
	orr r0, r2
	strh r0, [r1]
	add r0, r4, #0
	ldrb r2, [r1, #2]
	add r0, #0x84
	strb r2, [r0]
	add r0, r1, #0
	sub r0, #0x48
	mov r2, #0xe
	ldr r3, [r0]
	lsl r2, r2, #0xc
	and r2, r3
	lsr r3, r2, #0xd
	add r2, r4, #0
	add r2, #0x88
	str r3, [r2]
	ldrh r3, [r1, #2]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x1b
	orr r3, r2
	mov r2, #0x20
	orr r3, r2
	strh r3, [r1, #2]
	sub r3, r1, #6
	strh r5, [r3]
	ldr r3, _021DAAC8 ; =0x00002EB0
	sub r1, r1, #2
	strh r3, [r1]
	ldr r3, [r0]
	ldr r1, _021DAACC ; =0xFFFF1FFF
	and r3, r1
	lsl r1, r2, #9
	orr r1, r3
	str r1, [r0]
	add r0, r4, #0
	mov r3, #0
	add r0, #0x80
	str r3, [r0]
	mov r0, #0x7c
	str r0, [sp]
	mov r0, #0xc
	add r4, #0x40
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #4
	mov r2, #0x3f
	bl MOD15_021DB648
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_021DAABC: .word 0x04000050
_021DAAC0: .word 0x04000048
_021DAAC4: .word 0xFFFFC0FF
_021DAAC8: .word 0x00002EB0
_021DAACC: .word 0xFFFF1FFF

	thumb_func_start MOD15_021DAAD0
MOD15_021DAAD0: ; 0x021DAAD0
	push {r3, lr}
	add r1, r0, #0
	add r1, #0x80
	ldr r1, [r1]
	cmp r1, #0
	bne _021DAAEE
	add r0, #0x40
	bl MOD15_021DB678
	cmp r0, #0
	beq _021DAAEA
	mov r0, #1
	pop {r3, pc}
_021DAAEA:
	mov r0, #0
	pop {r3, pc}
_021DAAEE:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD15_021DAAF4
MOD15_021DAAF4: ; 0x021DAAF4
	push {r3, lr}
	sub sp, #8
	add r1, r0, #0
	mov r2, #0
	add r1, #0x80
	str r2, [r1]
	str r2, [sp]
	mov r1, #0xc
	str r1, [sp, #4]
	add r0, #0x40
	mov r1, #4
	mov r2, #0x3f
	mov r3, #0x7c
	bl MOD15_021DB648
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD15_021DAB18
MOD15_021DAB18: ; 0x021DAB18
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #0
	bne _021DAB70
	add r0, r4, #0
	add r0, #0x40
	bl MOD15_021DB678
	cmp r0, #0
	beq _021DAB74
	mov r0, #2
	mov r1, #0
	bl FUN_0201797C
	ldr r0, _021DAB78 ; =0x0400004A
	ldrh r2, [r0]
	mov r0, #0x3f
	bic r2, r0
	add r0, r4, #0
	add r0, #0x84
	ldrb r0, [r0]
	lsl r1, r0, #0x1b
	lsr r1, r1, #0x1b
	lsl r0, r0, #0x1a
	orr r1, r2
	lsr r0, r0, #0x1f
	beq _021DAB56
	mov r0, #0x20
	orr r1, r0
_021DAB56:
	ldr r2, _021DAB78 ; =0x0400004A
	ldr r0, _021DAB7C ; =0xFFFF1FFF
	strh r1, [r2]
	sub r2, #0x4a
	ldr r1, [r2]
	add r4, #0x88
	and r1, r0
	ldr r0, [r4]
	lsl r0, r0, #0xd
	orr r0, r1
	str r0, [r2]
	mov r0, #1
	pop {r4, pc}
_021DAB70:
	mov r0, #1
	pop {r4, pc}
_021DAB74:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021DAB78: .word 0x0400004A
_021DAB7C: .word 0xFFFF1FFF

	thumb_func_start MOD15_021DAB80
MOD15_021DAB80: ; 0x021DAB80
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x30]
	add r4, r1, #0
	bl FUN_020200A0
	cmp r4, #0
	beq _021DABAE
	ldr r0, [r5, #4]
	bl MOD15_021D87AC
	add r1, r0, #0
	ldr r0, [r5, #0x34]
	bl FUN_020200A0
	ldr r0, [r5, #4]
	bl MOD15_021D87C0
	add r1, r0, #0
	ldr r0, [r5, #0x38]
	bl FUN_020200A0
	pop {r3, r4, r5, pc}
_021DABAE:
	ldr r0, [r5, #0x34]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r5, #0x38]
	mov r1, #0
	bl FUN_020200A0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021DABC0
MOD15_021DABC0: ; 0x021DABC0
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r2, r1, #0
	mov r0, #1
	and r2, r0
	mov r0, #0x70
	mul r0, r2
	add r0, #0x48
	lsl r0, r0, #0xc
	str r0, [sp]
	lsr r1, r1, #1
	mov r0, #0x18
	mul r0, r1
	add r0, #0x38
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r4, #0x30]
	add r1, sp, #0
	bl FUN_02020044
	ldr r0, [r4, #0x30]
	mov r1, #8
	bl FUN_02020130
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021DABFC
MOD15_021DABFC: ; 0x021DABFC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r7, r0, #0
	add r4, r1, #0
	bl MOD15_021DACEC
	add r0, r7, #0
	add r0, #0x90
	ldr r0, [r0]
	lsl r6, r4, #1
	str r0, [sp, #0x10]
	add r0, r0, r6
	str r0, [sp, #0x14]
	mov r0, #0x18
	mul r0, r4
	str r0, [sp, #8]
	add r0, r7, #0
	add r0, #0x8c
	ldr r0, [r0]
	ldr r1, [sp, #8]
	add r1, r0, r1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x18]
	cmp r4, #0
	bge _021DAC40
	ldr r0, [sp, #0x14]
	add r5, r1, #0
	str r0, [sp, #0x10]
	lsl r0, r4, #2
	neg r0, r0
	neg r6, r6
	str r0, [sp, #0xc]
	b _021DAC60
_021DAC40:
	add r0, #0x78
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r0, [sp, #0x10]
	add r0, #0xa
	str r0, [sp, #0x10]
	ldr r0, [r7, #4]
	bl MOD15_021D8744
	ldr r1, [sp, #0x10]
	add r1, r6, r1
	cmp r1, r0
	bls _021DAC5C
	sub r6, r6, #1
_021DAC5C:
	lsl r0, r4, #2
	str r0, [sp, #0xc]
_021DAC60:
	mov r4, #0
	cmp r6, #0
	ble _021DAC84
_021DAC66:
	ldr r1, [sp, #0x10]
	add r0, r7, #0
	add r1, r1, r4
	add r2, r5, #0
	bl MOD15_021DAD98
	mov r0, #1
	tst r0, r4
	beq _021DAC7E
	add r5, #0x18
	lsl r0, r5, #0x18
	lsr r5, r0, #0x18
_021DAC7E:
	add r4, r4, #1
	cmp r4, r6
	blt _021DAC66
_021DAC84:
	add r1, r7, #0
	ldr r0, [sp, #0x18]
	add r1, #0x8c
	str r0, [r1]
	add r1, r7, #0
	ldr r0, [sp, #0x14]
	add r1, #0x90
	str r0, [r1]
	add r0, r7, #0
	add r0, #0x10
	bl FUN_02019548
	ldr r0, [sp, #8]
	mov r2, #2
	str r0, [sp]
	ldr r0, [sp, #0xc]
	mov r3, #1
	str r0, [sp, #4]
	add r0, r7, #0
	ldr r1, [r7, #0xc]
	add r0, #0x60
	bl MOD15_021DB564
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD15_021DACB8
MOD15_021DACB8: ; 0x021DACB8
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x60
	bl MOD15_021DB5B8
	cmp r0, #0
	beq _021DACE6
	ldr r0, [r4, #4]
	bl MOD15_021D87AC
	add r1, r0, #0
	ldr r0, [r4, #0x34]
	bl FUN_020200A0
	ldr r0, [r4, #4]
	bl MOD15_021D87C0
	add r1, r0, #0
	ldr r0, [r4, #0x38]
	bl FUN_020200A0
	mov r0, #1
	pop {r4, pc}
_021DACE6:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021DACEC
MOD15_021DACEC: ; 0x021DACEC
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	cmp r1, #0
	ble _021DAD0C
	add r0, #0x8c
	ldr r0, [r0]
	add r0, #0x78
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	mov r0, #0x18
	mul r0, r1
	add r0, r3, r0
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	b _021DAD1A
_021DAD0C:
	add r0, #0x8c
	ldr r4, [r0]
	mov r0, #0x18
	mul r0, r1
	add r0, r4, r0
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
_021DAD1A:
	cmp r3, r4
	bge _021DAD3E
	mov r0, #0xd0
	str r0, [sp]
	sub r0, r4, r3
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0
	lsl r3, r3, #0x10
	add r5, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	add r2, r1, #0
	lsr r3, r3, #0x10
	bl FUN_020196F4
	add sp, #8
	pop {r3, r4, r5, pc}
_021DAD3E:
	mov r0, #0xd0
	str r0, [sp]
	add r0, #0x30
	sub r0, r0, r3
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	lsl r3, r3, #0x10
	add r0, #0x10
	add r2, r1, #0
	lsr r3, r3, #0x10
	bl FUN_020196F4
	mov r1, #0
	mov r0, #0xd0
	str r0, [sp]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	add r5, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD15_021DAD78
MOD15_021DAD78: ; 0x021DAD78
	push {r3, lr}
	add r1, r0, #0
	mov r2, #0x30
	add r1, #0x8c
	str r2, [r1]
	add r1, r0, #0
	mov r3, #0
	add r1, #0x90
	str r3, [r1]
	ldr r0, [r0, #0xc]
	mov r1, #2
	mov r2, #3
	bl FUN_020179E0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD15_021DAD98
MOD15_021DAD98: ; 0x021DAD98
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r4, r2, #0
	ldr r0, [r5, #4]
	ldr r2, [r5, #0x3c]
	add r7, r1, #0
	bl MOD15_021D8768
	cmp r4, #0xf0
	bhi _021DADD4
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021DAE64 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r5, #0
	mov r3, #1
	add r4, r7, #0
	and r4, r3
	mov r3, #0x70
	ldr r2, [r5, #0x3c]
	add r0, #0x10
	mul r3, r4
	bl FUN_0201BDE0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_021DADD4:
	mov r0, #1
	lsl r0, r0, #8
	sub r6, r0, r4
	add r0, r5, #0
	add r0, #0x20
	mov r1, #0
	bl FUN_02019620
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021DAE64 ; =0x00010200
	add r3, r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r5, #0
	ldr r2, [r5, #0x3c]
	add r0, #0x20
	bl FUN_0201BDE0
	mov r2, #0
	mov r0, #1
	add r1, r7, #0
	and r1, r0
	add r7, r1, #0
	mov r0, #0x70
	mul r7, r0
	mov r0, #0x60
	str r0, [sp]
	mov r1, #0x10
	str r1, [sp, #4]
	lsl r1, r7, #0x10
	lsr r1, r1, #0x10
	str r1, [sp, #8]
	lsl r1, r4, #0x10
	lsr r1, r1, #0x10
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x14]
	add r0, r5, #0
	ldr r1, [r5, #0x2c]
	add r0, #0x10
	add r3, r2, #0
	bl FUN_02019658
	mov r1, #0x60
	lsl r2, r7, #0x10
	lsl r3, r6, #0x10
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	lsr r2, r2, #0x10
	str r2, [sp, #8]
	mov r2, #0
	sub r0, r0, r6
	str r2, [sp, #0xc]
	lsl r0, r0, #0x10
	str r1, [sp, #0x10]
	lsr r0, r0, #0x10
	str r0, [sp, #0x14]
	add r0, r5, #0
	ldr r1, [r5, #0x2c]
	add r0, #0x10
	lsr r3, r3, #0x10
	bl FUN_02019658
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DAE64: .word 0x00010200

	thumb_func_start MOD15_021DAE68
MOD15_021DAE68: ; 0x021DAE68
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #5
	add r5, r0, #0
	mov r0, #0x23
	lsl r1, r1, #8
	add r7, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	str r6, [r4, #4]
	str r7, [r4, #8]
	add r0, r5, #0
	bl MOD15_021D9548
	str r0, [r4, #0xc]
	add r0, r5, #0
	bl MOD15_021D954C
	str r0, [r4, #0x10]
	mov r1, #0
	str r1, [r4, #0x14]
	ldr r0, _021DAEA0 ; =0x000004FC
	str r1, [r4, #0x18]
	str r1, [r4, r0]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DAEA0: .word 0x000004FC

	thumb_func_start MOD15_021DAEA4
MOD15_021DAEA4: ; 0x021DAEA4
	push {r4, lr}
	add r4, r0, #0
	bl MOD15_021DB200
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD15_021DAEB4
MOD15_021DAEB4: ; 0x021DAEB4
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	mov r0, #0x40
	str r0, [sp]
	mov r0, #0x23
	str r0, [sp, #4]
	mov r0, #0x4c
	mov r1, #0x15
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x23
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x4c
	mov r1, #0xb
	mov r3, #4
	bl FUN_020068C8
	add r0, r4, #0
	bl MOD15_021DAFAC
	add r0, r4, #0
	bl MOD15_021DAFF8
	ldr r0, [r4, #4]
	bl MOD15_021D86F4
	cmp r0, #0
	bne _021DAF4A
	mov r2, #0xb
	ldr r0, _021DAFA4 ; =0x000001FA
	str r2, [sp]
	mov r1, #7
	str r1, [sp, #4]
	add r0, r4, r0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r2, [sp, #0x14]
	str r1, [sp, #0x18]
	mov r2, #3
	ldr r0, [r4, #0xc]
	mov r1, #4
	add r3, r2, #0
	bl FUN_02018170
	mov r2, #0xb
	mov r0, #0xa5
	lsl r0, r0, #2
	str r2, [sp]
	mov r1, #7
	str r1, [sp, #4]
	add r0, r4, r0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r2, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r4, #0xc]
	mov r1, #4
	mov r2, #3
	mov r3, #0xe
	bl FUN_02018170
	b _021DAF92
_021DAF4A:
	mov r2, #0xb
	add r0, r4, #0
	str r2, [sp]
	mov r1, #7
	str r1, [sp, #4]
	add r0, #0x2c
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r2, [sp, #0x14]
	str r1, [sp, #0x18]
	mov r2, #3
	ldr r0, [r4, #0xc]
	mov r1, #4
	add r3, r2, #0
	bl FUN_02018170
	mov r2, #0xb
	ldr r0, _021DAFA8 ; =0x00000462
	str r2, [sp]
	mov r1, #7
	str r1, [sp, #4]
	add r0, r4, r0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r2, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r4, #0xc]
	mov r1, #4
	mov r2, #3
	mov r3, #0xe
	bl FUN_02018170
_021DAF92:
	add r0, r4, #0
	bl MOD15_021DB154
	ldr r0, [r4, #0xc]
	mov r1, #4
	bl FUN_02017CD0
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0
_021DAFA4: .word 0x000001FA
_021DAFA8: .word 0x00000462

	thumb_func_start MOD15_021DAFAC
MOD15_021DAFAC: ; 0x021DAFAC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r4, _021DAFF4 ; =0x021DBA20
	mov r6, #0
	add r5, #0x2c
_021DAFB8:
	mov r0, #0x23
	str r0, [sp]
	ldrh r1, [r4]
	mov r0, #0x4c
	mov r2, #1
	add r3, sp, #4
	bl FUN_02006BDC
	add r7, r0, #0
	beq _021DAFE6
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r0, #0xc
	mov r2, #0x9a
	bl MIi_CpuCopy16
	add r0, r5, #0
	mov r1, #0x9a
	bl DC_FlushRange
	add r0, r7, #0
	bl FreeToHeap
_021DAFE6:
	add r6, r6, #1
	add r4, r4, #2
	add r5, #0x9a
	cmp r6, #8
	blo _021DAFB8
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DAFF4: .word MOD15_021DBA20

	thumb_func_start MOD15_021DAFF8
MOD15_021DAFF8: ; 0x021DAFF8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	mov r0, #2
	mov r1, #0
	bl FUN_02002C50
	ldr r1, _021DB0F8 ; =0x00000182
	mov r0, #0x1a
	mov r2, #0xb
	mov r3, #0x23
	bl ReadMsgData_NewNarc_NewString
	str r0, [sp, #4]
	ldr r1, _021DB0F8 ; =0x00000182
	mov r0, #0x1a
	mov r2, #0xc
	mov r3, #0x23
	bl ReadMsgData_NewNarc_NewString
	add r7, r0, #0
	ldr r1, _021DB0F8 ; =0x00000182
	mov r0, #0x1a
	mov r2, #0xd
	mov r3, #0x23
	bl ReadMsgData_NewNarc_NewString
	add r6, r0, #0
	ldr r1, _021DB0F8 ; =0x00000182
	mov r0, #0x1a
	mov r2, #0xe
	mov r3, #0x23
	bl ReadMsgData_NewNarc_NewString
	add r4, r0, #0
	mov r0, #0x23
	str r0, [sp]
	mov r0, #0x4c
	mov r1, #0x14
	mov r2, #1
	add r3, sp, #0xc
	bl FUN_02006BB0
	str r0, [sp, #8]
	cmp r0, #0
	beq _021DB0D4
	add r0, sp, #0x10
	bl FUN_0201901C
	ldr r0, [r5, #0xc]
	add r1, sp, #0xc
	str r0, [sp, #0x10]
	mov r0, #0xb
	strb r0, [r1, #0xb]
	mov r0, #0x39
	strb r0, [r1, #0xc]
	ldrh r2, [r1, #0xe]
	ldr r0, _021DB0FC ; =0xFFFF7FFF
	mov r3, #0
	and r0, r2
	strh r0, [r1, #0xe]
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #4]
	ldr r0, [r0, #0x14]
	str r0, [sp, #0x1c]
	ldr r1, [r5, #0xc]
	add r0, sp, #0x10
	bl MOD15_021DB100
	ldr r1, [r5, #0xc]
	add r0, sp, #0x10
	add r2, r7, #0
	mov r3, #0x10
	bl MOD15_021DB100
	ldr r0, [sp, #0xc]
	add r2, r6, #0
	ldr r1, [r0, #0x14]
	mov r0, #0x9a
	lsl r0, r0, #6
	add r0, r1, r0
	str r0, [sp, #0x1c]
	ldr r1, [r5, #0xc]
	add r0, sp, #0x10
	mov r3, #0
	bl MOD15_021DB100
	ldr r1, [r5, #0xc]
	add r0, sp, #0x10
	add r2, r4, #0
	mov r3, #0x10
	bl MOD15_021DB100
	ldr r1, [sp, #0xc]
	ldr r0, [r1, #0x14]
	ldr r1, [r1, #0x10]
	bl DC_FlushRange
	ldr r3, [sp, #0xc]
	mov r0, #0
	str r0, [sp]
	ldr r2, [r3, #0x14]
	ldr r0, [r5, #0xc]
	ldr r3, [r3, #0x10]
	mov r1, #4
	bl FUN_02017E14
	ldr r0, [sp, #8]
	bl FreeToHeap
_021DB0D4:
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	bl String_dtor
	ldr r0, [sp, #4]
	bl String_dtor
	add r0, r7, #0
	bl String_dtor
	mov r0, #2
	bl FUN_02002CF8
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DB0F8: .word 0x00000182
_021DB0FC: .word 0xFFFF7FFF

	thumb_func_start MOD15_021DB100
MOD15_021DB100: ; 0x021DB100
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r2, #0
	str r0, [sp, #0x10]
	mov r0, #2
	add r1, r6, #0
	mov r2, #0
	add r7, r3, #0
	bl FUN_02002F08
	mov r1, #0x58
	sub r0, r1, r0
	lsr r0, r0, #1
	ldr r5, _021DB14C ; =0x021DBA18
	str r0, [sp, #0x14]
	mov r4, #0
_021DB120:
	mov r0, #0
	ldrsh r0, [r5, r0]
	ldr r3, [sp, #0x14]
	mov r1, #2
	add r0, r7, r0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021DB150 ; =0x00010203
	add r2, r6, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	bl FUN_0201BDE0
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #4
	blo _021DB120
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DB14C: .word MOD15_021DBA18
_021DB150: .word 0x00010203

	thumb_func_start MOD15_021DB154
MOD15_021DB154: ; 0x021DB154
	push {r3, r4, lr}
	sub sp, #0x4c
	add r4, r0, #0
	add r0, sp, #0x38
	bl FUN_020B19DC
	add r0, sp, #0x14
	bl FUN_020B1A24
	mov r0, #0x23
	str r0, [sp]
	add r0, sp, #0x38
	str r0, [sp, #4]
	mov r0, #0x4c
	mov r1, #0x19
	mov r2, #2
	mov r3, #0
	bl FUN_02006A8C
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x23
	str r0, [sp, #0xc]
	add r0, sp, #0x14
	str r0, [sp, #0x10]
	mov r0, #0x4c
	mov r1, #0x18
	mov r2, #1
	bl FUN_02006AE4
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #0x4c
	mov r2, #0x16
	mov r3, #0x17
	bl MOD15_021DB224
	mov r0, #0xc0
	str r0, [sp]
	mov r0, #0x38
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r3, r4, #0
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, sp, #0x14
	add r2, sp, #0x38
	add r3, #0x1c
	bl MOD15_021DB26C
	str r0, [r4, #0x14]
	mov r1, #0
	bl FUN_02020130
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0xc0
	str r0, [sp]
	mov r0, #0x88
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r3, r4, #0
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, sp, #0x14
	add r2, sp, #0x38
	add r3, #0x1c
	bl MOD15_021DB26C
	mov r1, #2
	str r0, [r4, #0x18]
	bl FUN_02020130
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x4c
	pop {r3, r4, pc}

	thumb_func_start MOD15_021DB200
MOD15_021DB200: ; 0x021DB200
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021DB20E
	bl FUN_0201FFC8
_021DB20E:
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _021DB218
	bl FUN_0201FFC8
_021DB218:
	add r4, #0x1c
	add r0, r4, #0
	bl MOD15_021DB258
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021DB224
MOD15_021DB224: ; 0x021DB224
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0x23
	add r6, r3, #0
	str r0, [sp]
	add r1, r2, #0
	add r0, r4, #0
	mov r2, #1
	add r3, r5, #4
	bl FUN_02006C30
	str r0, [r5]
	mov r0, #0x23
	add r3, r5, #0
	str r0, [sp]
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #1
	add r3, #0xc
	bl FUN_02006C5C
	str r0, [r5, #8]
	add sp, #4
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD15_021DB258
MOD15_021DB258: ; 0x021DB258
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FreeToHeap
	ldr r0, [r4, #8]
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD15_021DB26C
MOD15_021DB26C: ; 0x021DB26C
	push {r3, r4, lr}
	sub sp, #0x44
	str r2, [sp, #0x28]
	str r1, [sp, #0x20]
	ldr r1, [r3, #4]
	ldr r2, [sp, #0x58]
	str r1, [sp, #0x2c]
	ldr r1, [r3, #0xc]
	str r1, [sp, #0x30]
	add r1, sp, #0x40
	strb r2, [r1]
	mov r1, #0
	str r1, [sp, #0x24]
	str r1, [sp, #0x34]
	str r1, [sp, #0x38]
	str r1, [sp, #0x3c]
	ldr r0, [r0, #0x10]
	str r0, [sp]
	add r0, sp, #0x20
	str r0, [sp, #4]
	ldr r0, [sp, #0x50]
	str r1, [sp, #0x10]
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r0, [sp, #0x54]
	add r0, #0xc0
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0x14]
	mov r0, #2
	str r0, [sp, #0x18]
	mov r0, #0x23
	str r0, [sp, #0x1c]
	add r0, sp, #0
	bl FUN_0201FF84
	add r4, r0, #0
	beq _021DB2CA
	mov r1, #1
	bl FUN_020200BC
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_020200D8
_021DB2CA:
	add r0, r4, #0
	add sp, #0x44
	pop {r3, r4, pc}

	thumb_func_start MOD15_021DB2D0
MOD15_021DB2D0: ; 0x021DB2D0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x23
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0
	beq _021DB32C
	ldr r0, [r5, #4]
	bl MOD15_021D86F4
	str r5, [r4]
	mov r1, #0
	str r1, [r4, #4]
	strh r1, [r4, #8]
	mov r1, #0xe
	mul r1, r0
	ldr r0, _021DB334 ; =0x021DBA30
	mov r2, #1
	ldrh r0, [r0, r1]
	strh r0, [r4, #0xa]
	ldr r0, _021DB338 ; =0x021DBA32
	ldrh r0, [r0, r1]
	strh r0, [r4, #0xc]
	ldr r0, _021DB33C ; =0x021DBA34
	ldrh r0, [r0, r1]
	strh r0, [r4, #0xe]
	ldr r0, _021DB340 ; =0x021DBA36
	ldrh r0, [r0, r1]
	strh r0, [r4, #0x10]
	ldr r0, _021DB344 ; =0x021DBA38
	ldrh r0, [r0, r1]
	strh r0, [r4, #0x12]
	ldr r0, _021DB348 ; =0x021DBA3A
	ldrh r0, [r0, r1]
	strh r0, [r4, #0x14]
	ldr r0, _021DB34C ; =0x021DBA3C
	ldrh r0, [r0, r1]
	add r1, r4, #0
	strh r0, [r4, #0x16]
	ldr r0, _021DB350 ; =MOD15_021DB36C
	bl FUN_0200CA44
	ldr r1, _021DB354 ; =0x000004FC
	str r0, [r5, r1]
	pop {r3, r4, r5, pc}
_021DB32C:
	ldr r0, _021DB354 ; =0x000004FC
	mov r1, #0
	str r1, [r5, r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DB334: .word MOD15_021DBA30
_021DB338: .word MOD15_021DBA32
_021DB33C: .word MOD15_021DBA34
_021DB340: .word MOD15_021DBA36
_021DB344: .word MOD15_021DBA38
_021DB348: .word MOD15_021DBA3A
_021DB34C: .word MOD15_021DBA3C
_021DB350: .word MOD15_021DB36C
_021DB354: .word 0x000004FC

	thumb_func_start MOD15_021DB358
MOD15_021DB358: ; 0x021DB358
	ldr r1, _021DB368 ; =0x000004FC
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _021DB364
	mov r0, #1
	bx lr
_021DB364:
	mov r0, #0
	bx lr
	.align 2, 0
_021DB368: .word 0x000004FC

	thumb_func_start MOD15_021DB36C
MOD15_021DB36C: ; 0x021DB36C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #3
	bls _021DB37C
	b _021DB4E0
_021DB37C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DB388: ; jump table
	.short _021DB390 - _021DB388 - 2 ; case 0
	.short _021DB416 - _021DB388 - 2 ; case 1
	.short _021DB476 - _021DB388 - 2 ; case 2
	.short _021DB4CC - _021DB388 - 2 ; case 3
_021DB390:
	ldr r3, [r4]
	mov r2, #0xb
	str r2, [sp]
	mov r1, #7
	str r1, [sp, #4]
	ldrh r6, [r4, #0xa]
	add r0, r3, #0
	mov r5, #0x9a
	add r0, #0x2c
	mul r5, r6
	add r0, r0, r5
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r2, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r3, #0xc]
	ldrh r2, [r4, #0xe]
	ldrh r3, [r4, #0x10]
	mov r1, #4
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02018170
	ldr r3, [r4]
	mov r2, #0xb
	add r0, r3, #0
	str r2, [sp]
	mov r1, #7
	str r1, [sp, #4]
	ldrh r6, [r4, #0x12]
	mov r5, #0x9a
	add r0, #0x2c
	mul r5, r6
	add r0, r0, r5
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r2, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r3, #0xc]
	ldrh r2, [r4, #0x14]
	ldrh r3, [r4, #0x16]
	mov r1, #4
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02018170
	ldr r0, [r4]
	mov r1, #4
	ldr r0, [r0, #0xc]
	bl FUN_02017CD0
	ldrh r0, [r4, #0xa]
	add sp, #0x1c
	add r0, r0, #1
	strh r0, [r4, #0xa]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, pc}
_021DB416:
	ldrh r0, [r4, #8]
	add r0, r0, #1
	strh r0, [r4, #8]
	ldrh r0, [r4, #8]
	cmp r0, #2
	blo _021DB4E0
	ldr r3, [r4]
	mov r2, #0xb
	str r2, [sp]
	mov r1, #7
	str r1, [sp, #4]
	ldrh r6, [r4, #0xa]
	add r0, r3, #0
	mov r5, #0x9a
	add r0, #0x2c
	mul r5, r6
	add r0, r0, r5
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r2, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r3, #0xc]
	ldrh r2, [r4, #0xe]
	ldrh r3, [r4, #0x10]
	mov r1, #4
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02018170
	ldr r0, [r4]
	mov r1, #4
	ldr r0, [r0, #0xc]
	bl FUN_02017CD0
	mov r0, #0
	strh r0, [r4, #8]
	ldrh r0, [r4, #0xa]
	add sp, #0x1c
	add r0, r0, #1
	strh r0, [r4, #0xa]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, pc}
_021DB476:
	ldrh r0, [r4, #8]
	add r0, r0, #1
	strh r0, [r4, #8]
	ldrh r0, [r4, #8]
	cmp r0, #4
	blo _021DB4E0
	ldr r3, [r4]
	mov r2, #0xb
	str r2, [sp]
	mov r1, #7
	str r1, [sp, #4]
	ldrh r6, [r4, #0xa]
	add r0, r3, #0
	mov r5, #0x9a
	add r0, #0x2c
	mul r5, r6
	add r0, r0, r5
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r2, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r3, #0xc]
	ldrh r2, [r4, #0xe]
	ldrh r3, [r4, #0x10]
	mov r1, #4
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02018170
	ldr r0, [r4]
	mov r1, #4
	ldr r0, [r0, #0xc]
	bl FUN_02017CD0
	ldr r0, [r4, #4]
	add sp, #0x1c
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, pc}
_021DB4CC:
	ldr r1, [r4]
	ldr r0, _021DB4E4 ; =0x000004FC
	mov r2, #0
	str r2, [r1, r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_021DB4E0:
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DB4E4: .word 0x000004FC

	thumb_func_start MOD15_021DB4E8
MOD15_021DB4E8: ; 0x021DB4E8
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #0
	beq _021DB50E
	ldr r0, [r4, #4]
	bl MOD15_021D87AC
	add r1, r0, #0
	ldr r0, [r4, #0x14]
	bl FUN_020200A0
	ldr r0, [r4, #4]
	bl MOD15_021D87C0
	add r1, r0, #0
	ldr r0, [r4, #0x18]
	bl FUN_020200A0
	pop {r4, pc}
_021DB50E:
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_020200A0
	pop {r4, pc}

	thumb_func_start MOD15_021DB520
MOD15_021DB520: ; 0x021DB520
	push {r3, lr}
	cmp r1, #0
	beq _021DB52C
	cmp r1, #1
	beq _021DB548
	pop {r3, pc}
_021DB52C:
	cmp r2, #0
	beq _021DB53E
	cmp r2, #1
	bne _021DB562
	ldr r0, [r0, #0x14]
	mov r1, #1
	bl FUN_02020130
	pop {r3, pc}
_021DB53E:
	ldr r0, [r0, #0x14]
	mov r1, #0
	bl FUN_02020130
	pop {r3, pc}
_021DB548:
	cmp r2, #0
	beq _021DB55A
	cmp r2, #1
	bne _021DB562
	ldr r0, [r0, #0x18]
	mov r1, #3
	bl FUN_02020130
	pop {r3, pc}
_021DB55A:
	ldr r0, [r0, #0x18]
	mov r1, #2
	bl FUN_02020130
_021DB562:
	pop {r3, pc}

	thumb_func_start MOD15_021DB564
MOD15_021DB564: ; 0x021DB564
	push {r4, lr}
	add r4, r0, #0
	str r1, [r4]
	str r2, [r4, #4]
	cmp r3, #0
	bne _021DB57E
	add r0, r1, #0
	add r1, r2, #0
	bl FUN_02017B48
	str r0, [r4, #0xc]
	mov r0, #0
	b _021DB58A
_021DB57E:
	add r0, r1, #0
	add r1, r2, #0
	bl FUN_02017B54
	str r0, [r4, #0xc]
	mov r0, #3
_021DB58A:
	str r0, [r4, #8]
	ldr r0, [sp, #8]
	ldr r1, [r4, #0xc]
	add r2, r1, r0
	ldr r1, _021DB5B4 ; =0x000001FF
	lsl r0, r0, #0xc
	and r1, r2
	str r1, [r4, #0x10]
	ldr r1, [r4, #0xc]
	lsl r1, r1, #0xc
	str r1, [r4, #0xc]
	ldr r1, [sp, #0xc]
	bl _s32_div_f
	str r0, [r4, #0x14]
	ldr r0, [sp, #0xc]
	strh r0, [r4, #0x18]
	mov r0, #0
	strh r0, [r4, #0x1a]
	pop {r4, pc}
	nop
_021DB5B4: .word 0x000001FF

	thumb_func_start MOD15_021DB5B8
MOD15_021DB5B8: ; 0x021DB5B8
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #0x1a]
	cmp r0, #0
	beq _021DB5CC
	cmp r0, #1
	beq _021DB5E0
	cmp r0, #2
	beq _021DB5F6
	b _021DB5FA
_021DB5CC:
	ldr r0, _021DB600 ; =MOD15_021DB604
	add r1, r4, #0
	mov r2, #0
	bl MOD15_021D88D0
	str r0, [r4, #0x1c]
	ldrh r0, [r4, #0x1a]
	add r0, r0, #1
	strh r0, [r4, #0x1a]
	b _021DB5FA
_021DB5E0:
	ldrh r0, [r4, #0x18]
	cmp r0, #0
	bne _021DB5FA
	ldr r0, [r4, #0x1c]
	bl FUN_0200CAB4
	ldrh r0, [r4, #0x1a]
	add r0, r0, #1
	strh r0, [r4, #0x1a]
	mov r0, #1
	pop {r4, pc}
_021DB5F6:
	mov r0, #1
	pop {r4, pc}
_021DB5FA:
	mov r0, #0
	pop {r4, pc}
	nop
_021DB600: .word MOD15_021DB604

	thumb_func_start MOD15_021DB604
MOD15_021DB604: ; 0x021DB604
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #0x18]
	cmp r0, #0
	beq _021DB632
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x14]
	add r3, r1, r0
	str r3, [r4, #0xc]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	ldr r0, [r4]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	asr r3, r3, #0xc
	bl FUN_020179E0
	ldrh r0, [r4, #0x18]
	sub r0, r0, #1
	strh r0, [r4, #0x18]
	pop {r4, pc}
_021DB632:
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	ldr r0, [r4]
	ldr r3, [r4, #0x10]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl FUN_020179E0
	pop {r4, pc}

	thumb_func_start MOD15_021DB648
MOD15_021DB648: ; 0x021DB648
	push {r4, lr}
	add r4, r0, #0
	str r1, [r4]
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	str r2, [r4, #4]
	str r1, [r4, #0x14]
	str r3, [r4, #8]
	sub r0, r0, r3
	bl _s32_div_f
	str r0, [r4, #0x10]
	ldr r0, [sp, #8]
	mov r2, #0
	str r0, [r4, #0xc]
	ldr r0, _021DB674 ; =MOD15_021DB6A0
	add r1, r4, #0
	str r2, [r4, #0x18]
	bl MOD15_021D88D0
	str r0, [r4, #0x1c]
	pop {r4, pc}
	.align 2, 0
_021DB674: .word MOD15_021DB6A0

	thumb_func_start MOD15_021DB678
MOD15_021DB678: ; 0x021DB678
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _021DB698
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _021DB69C
	ldr r0, [r4, #0x1c]
	bl FUN_0200CAB4
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	mov r0, #1
	pop {r4, pc}
_021DB698:
	mov r0, #1
	pop {r4, pc}
_021DB69C:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD15_021DB6A0
MOD15_021DB6A0: ; 0x021DB6A0
	push {r3, lr}
	add r2, r1, #0
	ldr r0, [r2, #0x14]
	cmp r0, #0
	beq _021DB6BC
	ldr r1, [r2, #8]
	ldr r0, [r2, #0x10]
	add r0, r1, r0
	str r0, [r2, #8]
	asr r3, r0, #3
	ldr r0, [r2, #0x14]
	sub r0, r0, #1
	str r0, [r2, #0x14]
	b _021DB6C0
_021DB6BC:
	ldr r0, [r2, #0xc]
	asr r3, r0, #3
_021DB6C0:
	cmp r3, #0x10
	ble _021DB6C6
	mov r3, #0x10
_021DB6C6:
	mov r0, #0x10
	sub r0, r0, r3
	str r0, [sp]
	ldr r0, _021DB6D8 ; =0x04000050
	ldmia r2!, {r1, r2}
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	nop
_021DB6D8: .word 0x04000050

	thumb_func_start MOD15_021DB6DC
MOD15_021DB6DC: ; 0x021DB6DC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _021DB714 ; =0x04000050
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl G2x_SetBlendBrightness_
	ldr r1, [sp, #0x18]
	str r4, [r5]
	str r1, [r5, #0x14]
	lsl r0, r6, #0xc
	str r0, [r5, #8]
	lsl r2, r7, #0xc
	str r2, [r5, #0xc]
	ldr r0, [r5, #8]
	sub r0, r2, r0
	bl _s32_div_f
	str r0, [r5, #0x10]
	mov r2, #0
	ldr r0, _021DB718 ; =MOD15_021DB744
	add r1, r5, #0
	str r2, [r5, #0x18]
	bl MOD15_021D88D0
	str r0, [r5, #0x1c]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DB714: .word 0x04000050
_021DB718: .word MOD15_021DB744

	thumb_func_start MOD15_021DB71C
MOD15_021DB71C: ; 0x021DB71C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _021DB73C
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _021DB740
	ldr r0, [r4, #0x1c]
	bl FUN_0200CAB4
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	mov r0, #1
	pop {r4, pc}
_021DB73C:
	mov r0, #1
	pop {r4, pc}
_021DB740:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD15_021DB744
MOD15_021DB744: ; 0x021DB744
	ldr r0, [r1, #0x14]
	cmp r0, #0
	beq _021DB75C
	ldr r2, [r1, #8]
	ldr r0, [r1, #0x10]
	add r0, r2, r0
	str r0, [r1, #8]
	asr r2, r0, #0xc
	ldr r0, [r1, #0x14]
	sub r0, r0, #1
	str r0, [r1, #0x14]
	b _021DB760
_021DB75C:
	ldr r0, [r1, #0xc]
	asr r2, r0, #0xc
_021DB760:
	ldr r3, _021DB768 ; =0x020C74B8
	ldr r0, _021DB76C ; =0x04000050
	ldr r1, [r1]
	bx r3
	.align 2, 0
_021DB768: .word 0x020C74B8
_021DB76C: .word 0x04000050

	thumb_func_start MOD15_021DB770
MOD15_021DB770: ; 0x021DB770
	mov r0, #0x1b
	bx lr

	thumb_func_start MOD15_021DB774
MOD15_021DB774: ; 0x021DB774
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r5, r1, #0
	cmp r4, #0x1b
	blo _021DB782
	bl ErrorHandling
_021DB782:
	mov r1, #0xa
	ldr r2, _021DB794 ; =0x021DBA4C
	mul r1, r4
	add r1, r2, r1
	add r0, r5, #0
	mov r2, #2
	bl FUN_02021E8C
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DB794: .word MOD15_021DBA4C

	thumb_func_start MOD15_021DB798
MOD15_021DB798: ; 0x021DB798
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	cmp r5, #0x1b
	blo _021DB7A8
	bl ErrorHandling
_021DB7A8:
	mov r0, #0xa
	add r1, r5, #0
	mul r1, r0
	ldr r0, _021DB7BC ; =0x021DBA4E
	ldrb r0, [r0, r1]
	str r0, [r4]
	ldr r0, _021DB7C0 ; =0x021DBA4F
	ldrb r0, [r0, r1]
	str r0, [r6]
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DB7BC: .word MOD15_021DBA4E
_021DB7C0: .word MOD15_021DBA4F

	thumb_func_start MOD15_021DB7C4
MOD15_021DB7C4: ; 0x021DB7C4
	push {r4, lr}
	add r4, r0, #0
	cmp r4, #0x1b
	blo _021DB7D0
	bl ErrorHandling
_021DB7D0:
	mov r0, #0xa
	add r1, r4, #0
	mul r1, r0
	ldr r0, _021DB7DC ; =0x021DBA50
	ldrb r0, [r0, r1]
	pop {r4, pc}
	.align 2, 0
_021DB7DC: .word MOD15_021DBA50

	thumb_func_start MOD15_021DB7E0
MOD15_021DB7E0: ; 0x021DB7E0
	push {r4, lr}
	add r4, r0, #0
	cmp r4, #0x1b
	blo _021DB7EC
	bl ErrorHandling
_021DB7EC:
	mov r0, #0xa
	add r1, r4, #0
	mul r1, r0
	ldr r0, _021DB7F8 ; =0x021DBA51
	ldrb r0, [r0, r1]
	pop {r4, pc}
	.align 2, 0
_021DB7F8: .word MOD15_021DBA51

	thumb_func_start MOD15_021DB7FC
MOD15_021DB7FC: ; 0x021DB7FC
	push {r4, lr}
	add r4, r0, #0
	cmp r4, #0x1b
	blo _021DB808
	bl ErrorHandling
_021DB808:
	mov r0, #0xa
	add r1, r4, #0
	mul r1, r0
	ldr r0, _021DB814 ; =0x021DBA52
	ldrb r0, [r0, r1]
	pop {r4, pc}
	.align 2, 0
_021DB814: .word MOD15_021DBA52

	thumb_func_start MOD15_021DB818
MOD15_021DB818: ; 0x021DB818
	push {r4, lr}
	add r4, r0, #0
	cmp r4, #0x1b
	blo _021DB824
	bl ErrorHandling
_021DB824:
	mov r0, #0xa
	add r1, r4, #0
	mul r1, r0
	ldr r0, _021DB830 ; =0x021DBA53
	ldrb r0, [r0, r1]
	pop {r4, pc}
	.align 2, 0
_021DB830: .word MOD15_021DBA53

	thumb_func_start MOD15_021DB834
MOD15_021DB834: ; 0x021DB834
	push {r4, lr}
	add r4, r0, #0
	cmp r4, #0x1b
	blo _021DB840
	bl ErrorHandling
_021DB840:
	mov r0, #0xa
	add r1, r4, #0
	mul r1, r0
	ldr r0, _021DB84C ; =0x021DBA54
	ldrb r0, [r0, r1]
	pop {r4, pc}
	.align 2, 0
_021DB84C: .word MOD15_021DBA54

	thumb_func_start MOD15_021DB850
MOD15_021DB850: ; 0x021DB850
	push {r4, lr}
	add r4, r0, #0
	cmp r4, #0x1b
	blo _021DB85C
	bl ErrorHandling
_021DB85C:
	mov r0, #0xa
	add r1, r4, #0
	mul r1, r0
	ldr r0, _021DB868 ; =0x021DBA55
	ldrb r0, [r0, r1]
	pop {r4, pc}
	.align 2, 0
_021DB868: .word MOD15_021DBA55

	.rodata
	.global MOD15_021DB86C
MOD15_021DB86C: ; 0x021DB86C
	.byte 0x99, 0x7E, 0x1D, 0x02, 0x51, 0x7F, 0x1D, 0x02

	.global MOD15_021DB874
MOD15_021DB874: ; 0x021DB874
	.byte 0xB1, 0x77, 0x1D, 0x02, 0x91, 0x78, 0x1D, 0x02, 0xC1, 0x79, 0x1D, 0x02

	.global MOD15_021DB880
MOD15_021DB880: ; 0x021DB880
	.byte 0x18, 0x50, 0x18, 0x70, 0x70, 0xA8, 0x18, 0x70, 0x28, 0x48, 0xB0, 0xD0, 0x78, 0x98, 0xB0, 0xD0
	.byte 0xFF, 0x00, 0x00, 0x00

	.global MOD15_021DB894
MOD15_021DB894: ; 0x021DB894
	.byte 0xFE

	.global MOD15_021DB895
MOD15_021DB895: ; 0x021DB895
	.byte 0x03

	.global MOD15_021DB896
MOD15_021DB896: ; 0x021DB896
	.byte 0x02

	.global MOD15_021DB897
MOD15_021DB897: ; 0x021DB897
	.byte 0x01, 0xFE, 0x04, 0x00, 0x02, 0xFE, 0x05, 0x01, 0x00, 0x00, 0x06, 0x05, 0x04, 0x01, 0x07, 0x03
	.byte 0x05, 0x02, 0x08, 0x04, 0x03, 0x03, 0x09, 0x08, 0x07, 0x04, 0x0A, 0x06, 0x08, 0x05, 0x0B, 0x07
	.byte 0x06, 0x06, 0xFE, 0x0B, 0x0A, 0x07, 0xFE, 0x09, 0x0B, 0x08, 0xFE, 0x0A, 0x09, 0x09, 0x00, 0xFE
	.byte 0xFE

	.global MOD15_021DB8C8
MOD15_021DB8C8: ; 0x021DB8C8
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD15_021DB8D8
MOD15_021DB8D8: ; 0x021DB8D8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x1C, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD15_021DB8F4
MOD15_021DB8F4: ; 0x021DB8F4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x02, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD15_021DB910
MOD15_021DB910: ; 0x021DB910
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD15_021DB92C
MOD15_021DB92C: ; 0x021DB92C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD15_021DB948
MOD15_021DB948: ; 0x021DB948
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD15_021DB964
MOD15_021DB964: ; 0x021DB964
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD15_021DB98C
MOD15_021DB98C: ; 0x021DB98C
	.byte 0xC1, 0x89, 0x1D, 0x02, 0x59, 0x8B, 0x1D, 0x02, 0xB5, 0x8C, 0x1D, 0x02, 0x05, 0x8D, 0x1D, 0x02
	.byte 0x31, 0x8D, 0x1D, 0x02, 0x75, 0x8D, 0x1D, 0x02, 0xA5, 0x8D, 0x1D, 0x02, 0x29, 0x8F, 0x1D, 0x02
	.byte 0x8D, 0x8F, 0x1D, 0x02, 0x2D, 0x90, 0x1D, 0x02, 0x01, 0x91, 0x1D, 0x02, 0xE1, 0x91, 0x1D, 0x02
	.byte 0xB9, 0x92, 0x1D, 0x02, 0xD9, 0x92, 0x1D, 0x02, 0xF9, 0x92, 0x1D, 0x02, 0x19, 0x93, 0x1D, 0x02
	.byte 0x39, 0x93, 0x1D, 0x02, 0x89, 0x93, 0x1D, 0x02, 0xA5, 0x93, 0x1D, 0x02, 0xF5, 0x93, 0x1D, 0x02
	.byte 0x45, 0x94, 0x1D, 0x02, 0x61, 0x94, 0x1D, 0x02, 0x81, 0x94, 0x1D, 0x02, 0x1D, 0x8E, 0x1D, 0x02
	.byte 0x85, 0x8E, 0x1D, 0x02, 0xC9, 0x94, 0x1D, 0x02, 0xE5, 0x94, 0x1D, 0x02, 0x01, 0x95, 0x1D, 0x02
	.byte 0x1D, 0x95, 0x1D, 0x02

	.global MOD15_021DBA00
MOD15_021DBA00: ; 0x021DBA00
	.byte 0x03, 0x03, 0x06, 0x0A, 0x02, 0x0D, 0x40, 0x00

	.global MOD15_021DBA08
MOD15_021DBA08: ; 0x021DBA08
	.byte 0x03, 0x13, 0x06, 0x0A, 0x02, 0x0D, 0x54, 0x00

	.global MOD15_021DBA10
MOD15_021DBA10: ; 0x021DBA10
	.byte 0x0C, 0x00, 0x15, 0x00, 0x2C, 0x00, 0x15, 0x00

	.global MOD15_021DBA18
MOD15_021DBA18: ; 0x021DBA18
	.byte 0x16, 0x00, 0x4D, 0x00, 0x84, 0x00, 0xBD, 0x00

	.global MOD15_021DBA20
MOD15_021DBA20: ; 0x021DBA20
	.byte 0x0C, 0x00, 0x0D, 0x00, 0x0E, 0x00, 0x0F, 0x00, 0x10, 0x00, 0x11, 0x00, 0x12, 0x00, 0x13, 0x00

	.global MOD15_021DBA30
MOD15_021DBA30: ; 0x021DBA30
	.byte 0x01, 0x00

	.global MOD15_021DBA32
MOD15_021DBA32: ; 0x021DBA32
	.byte 0x03, 0x00

	.global MOD15_021DBA34
MOD15_021DBA34: ; 0x021DBA34
	.byte 0x03, 0x00

	.global MOD15_021DBA36
MOD15_021DBA36: ; 0x021DBA36
	.byte 0x03, 0x00

	.global MOD15_021DBA38
MOD15_021DBA38: ; 0x021DBA38
	.byte 0x04, 0x00

	.global MOD15_021DBA3A
MOD15_021DBA3A: ; 0x021DBA3A
	.byte 0x03, 0x00

	.global MOD15_021DBA3C
MOD15_021DBA3C: ; 0x021DBA3C
	.byte 0x0E, 0x00, 0x05, 0x00, 0x07, 0x00, 0x03, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00

	.global MOD15_021DBA4C
MOD15_021DBA4C: ; 0x021DBA4C
	.byte 0x2B, 0x01

	.global MOD15_021DBA4E
MOD15_021DBA4E: ; 0x021DBA4E
	.byte 0x1C

	.global MOD15_021DBA4F
MOD15_021DBA4F: ; 0x021DBA4F
	.byte 0x0C

	.global MOD15_021DBA50
MOD15_021DBA50: ; 0x021DBA50
	.byte 0xFE

	.global MOD15_021DBA51
MOD15_021DBA51: ; 0x021DBA51
	.byte 0x0A

	.global MOD15_021DBA52
MOD15_021DBA52: ; 0x021DBA52
	.byte 0x09

	.global MOD15_021DBA53
MOD15_021DBA53: ; 0x021DBA53
	.byte 0x01

	.global MOD15_021DBA54
MOD15_021DBA54: ; 0x021DBA54
	.byte 0x00

	.global MOD15_021DBA55
MOD15_021DBA55: ; 0x021DBA55
	.byte 0x14, 0x2C, 0x01, 0x2C, 0x0C, 0xFE, 0x0B, 0x00, 0x02, 0x01, 0x15, 0x2D, 0x01, 0x3C, 0x0C, 0xFE
	.byte 0x0C, 0x01, 0x03, 0x02, 0x16, 0x2E, 0x01, 0x4C, 0x0C, 0xFE, 0x0D, 0x02, 0x04, 0x03, 0x17, 0x2F
	.byte 0x01, 0x5C, 0x0C, 0xFE, 0x0E, 0x03, 0x05, 0x04, 0x18, 0x30, 0x01, 0x6C, 0x0C, 0xFE, 0x0F, 0x04
	.byte 0x06, 0x05, 0x19, 0x31, 0x01, 0x7C, 0x0C, 0xFE, 0x10, 0x05, 0x07, 0x06, 0x10, 0x32, 0x01, 0x8C
	.byte 0x0C, 0xFE, 0x11, 0x06, 0x08, 0x07, 0x11, 0x33, 0x01, 0x9C, 0x0C, 0xFE, 0x12, 0x07, 0x09, 0x08
	.byte 0x12, 0x34, 0x01, 0xAC, 0x0C, 0xFE, 0x13, 0x08, 0x00, 0x09, 0x1A, 0x35, 0x01, 0x1C, 0x1C, 0x00
	.byte 0x14, 0x13, 0x0B, 0x00, 0x14, 0x36, 0x01, 0x2C, 0x1C, 0x01, 0x15, 0x0A, 0x0C, 0x01, 0x15, 0x37
	.byte 0x01, 0x3C, 0x1C, 0x02, 0x16, 0x0B, 0x0D, 0x02, 0x16, 0x38, 0x01, 0x4C, 0x1C, 0x03, 0x17, 0x0C
	.byte 0x0E, 0x03, 0x17, 0x39, 0x01, 0x5C, 0x1C, 0x04, 0x18, 0x0D, 0x0F, 0x04, 0x18, 0x3A, 0x01, 0x6C
	.byte 0x1C, 0x05, 0x19, 0x0E, 0x10, 0x05, 0x19, 0x3B, 0x01, 0x7C, 0x1C, 0x06, 0xFE, 0x0F, 0x11, 0x06
	.byte 0x10, 0x3C, 0x01, 0x8C, 0x1C, 0x07, 0xFE, 0x10, 0x12, 0x07, 0x11, 0x3D, 0x01, 0x9C, 0x1C, 0x08
	.byte 0xFE, 0x11, 0x13, 0x08, 0x12, 0x3E, 0x01, 0xAC, 0x1C, 0x09, 0x1A, 0x12, 0x0A, 0x09, 0x1A, 0x3F
	.byte 0x01, 0x1C, 0x2C, 0x0A, 0xFE, 0x1A, 0x15, 0x00, 0x14, 0x40, 0x01, 0x2C, 0x2C, 0x0B, 0xFE, 0x14
	.byte 0x16, 0x01, 0x15, 0x41, 0x01, 0x3C, 0x2C, 0x0C, 0xFE, 0x15, 0x17, 0x02, 0x16, 0x42, 0x01, 0x4C
	.byte 0x2C, 0x0D, 0xFE, 0x16, 0x18, 0x03, 0x17, 0x43, 0x01, 0x5C, 0x2C, 0x0E, 0xFE, 0x17, 0x19, 0x04
	.byte 0x18, 0x44, 0x01, 0x6C, 0x2C, 0x0F, 0xFE, 0x18, 0x1A, 0x05, 0x19, 0xAB, 0x01, 0xAC, 0x2C, 0x13
	.byte 0xFE, 0x19, 0x14, 0x09, 0x1A, 0x00, 0x00

	.data
	.bss
