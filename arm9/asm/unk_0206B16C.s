    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206B16C
FUN_0206B16C: ; 0x0206B16C
	push {r3, lr}
	bl FUN_0206B180
	bl FUN_02022830
	pop {r3, pc}

	thumb_func_start FUN_0206B178
FUN_0206B178: ; 0x0206B178
	ldr r0, _0206B17C ; =0x000121C8
	bx lr
	.balign 4
_0206B17C: .word 0x000121C8

	thumb_func_start FUN_0206B180
FUN_0206B180: ; 0x0206B180
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	mov r7, #0x0
	add r6, r0, #0x4
_0206B188:
	mov r4, #0x0
	add r5, r6, #0x0
_0206B18C:
	add r0, r5, #0x0
	bl WipeBoxMonDataAndEncrypt
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x1e
	blo _0206B18C
	mov r0, #0xff
	lsl r0, r0, #0x4
	add r7, r7, #0x1
	add r6, r6, r0
	cmp r7, #0x12
	blo _0206B188
	mov r3, #0x0
	ldr r1, _0206B200 ; =0x000121B4
	add r4, r3, #0x0
	add r2, r3, #0x0
_0206B1AE:
	ldr r0, [sp, #0x0]
	add r0, r0, r3
	strb r4, [r0, r1]
	add r4, r4, #0x1
	cmp r4, #0x10
	blo _0206B1BC
	add r4, r2, #0x0
_0206B1BC:
	add r3, r3, #0x1
	cmp r3, #0x12
	blo _0206B1AE
	ldr r1, _0206B204 ; =0x000121C6
	ldr r0, [sp, #0x0]
	mov r3, #0x0
	strb r3, [r0, r1]
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xe
	bl NewMsgDataFromNarc
	add r6, r0, #0x0
	beq _0206B1F8
	ldr r1, _0206B208 ; =0x00011EE4
	ldr r0, [sp, #0x0]
	mov r5, #0x0
	add r4, r0, r1
_0206B1E0:
	add r0, r6, #0x0
	add r1, r5, #0x6
	add r2, r4, #0x0
	bl DecryptCopyString
	add r5, r5, #0x1
	add r4, #0x28
	cmp r5, #0x12
	blo _0206B1E0
	add r0, r6, #0x0
	bl DestroyMsgData
_0206B1F8:
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	pop {r3-r7, pc}
	.balign 4
_0206B200: .word 0x000121B4
_0206B204: .word 0x000121C6
_0206B208: .word 0x00011EE4

	thumb_func_start FUN_0206B20C
FUN_0206B20C: ; 0x0206B20C
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r4, [r5, #0x0]
	add r6, r1, #0x0
	mov r7, #0x0
_0206B216:
	add r0, r6, #0x0
	bl FUN_0206AAB4
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0206B244
	cmp r0, #0x0
	beq _0206B232
	bl FUN_02022830
	mov r0, #0x1
	pop {r3-r7, pc}
_0206B232:
	add r4, r4, #0x1
	cmp r4, #0x12
	blo _0206B23A
	add r4, r7, #0x0
_0206B23A:
	ldr r0, [r5, #0x0]
	cmp r4, r0
	bne _0206B216
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0206B244
FUN_0206B244: ; 0x0206B244
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r0, #0x0
	add r0, r2, #0x0
	add r5, r1, #0x0
	str r2, [sp, #0x0]
	bl FUN_0206AAB4
	mov r0, #0x0
	mvn r0, r0
	cmp r5, r0
	bne _0206B25E
	ldr r5, [r6, #0x0]
_0206B25E:
	mov r0, #0xff
	lsl r0, r0, #0x4
	add r1, r6, #0x4
	mul r0, r5
	mov r4, #0x0
	add r5, r1, r0
	str r5, [sp, #0x4]
	mov r6, #0x5
	add r7, r4, #0x0
_0206B270:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl GetBoxMonDataEncrypted
	cmp r0, #0x0
	bne _0206B2A0
	mov r0, #0x88
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, [sp, #0x4]
	mov r3, #0x11
	add r4, r0, r1
_0206B28A:
	ldr r2, [sp, #0x0]
	sub r3, r3, #0x1
	ldmia r2!, {r0-r1}
	str r2, [sp, #0x0]
	stmia r4!, {r0-r1}
	bne _0206B28A
	bl FUN_02022830
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0206B2A0:
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x1e
	blo _0206B270
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206B2B0
FUN_0206B2B0: ; 0x0206B2B0
	push {r3-r7, lr}
	add r7, r3, #0x0
	add r5, r0, #0x0
	add r0, r7, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0206AAB4
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	bne _0206B2CA
	ldr r4, [r5, #0x0]
_0206B2CA:
	cmp r4, #0x12
	bhs _0206B2F4
	cmp r6, #0x1e
	bhs _0206B2F4
	mov r0, #0xff
	lsl r0, r0, #0x4
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x88
	mul r0, r6
	add r0, r1, r0
	add r3, r0, #0x4
	mov r2, #0x11
_0206B2E4:
	ldmia r7!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0206B2E4
	bl FUN_02022830
	mov r0, #0x1
	pop {r3-r7, pc}
_0206B2F4:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0206B2FC
FUN_0206B2FC: ; 0x0206B2FC
	push {r3, lr}
	mov r3, #0x0
	mvn r3, r3
	cmp r1, r3
	bne _0206B308
	ldr r1, [r0, #0x0]
_0206B308:
	cmp r2, #0x1e
	bhs _0206B32A
	cmp r1, #0x12
	bhs _0206B32A
	add r3, r0, #0x4
	mov r0, #0xff
	lsl r0, r0, #0x4
	mul r0, r1
	add r1, r3, r0
	mov r0, #0x88
	mul r0, r2
	add r0, r1, r0
	bl WipeBoxMonDataAndEncrypt
	bl FUN_02022830
	pop {r3, pc}
_0206B32A:
	bl ErrorHandling
	pop {r3, pc}

	thumb_func_start FUN_0206B330
FUN_0206B330: ; 0x0206B330
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0206B334
FUN_0206B334: ; 0x0206B334
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	ldr r6, [r0, #0x0]
	add r0, r0, #0x4
	mov r7, #0xab
	str r0, [sp, #0x4]
_0206B342:
	mov r0, #0xff
	lsl r0, r0, #0x4
	add r1, r6, #0x0
	mul r1, r0
	ldr r0, [sp, #0x4]
	mov r4, #0x0
	add r5, r0, r1
_0206B350:
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x0
	bl GetBoxMonDataEncrypted
	cmp r0, #0x0
	bne _0206B364
	add sp, #0x8
	add r0, r6, #0x0
	pop {r3-r7, pc}
_0206B364:
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x1e
	blt _0206B350
	add r6, r6, #0x1
	cmp r6, #0x12
	blt _0206B374
	mov r6, #0x0
_0206B374:
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	cmp r6, r0
	bne _0206B342
	mov r0, #0x12
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206B384
FUN_0206B384: ; 0x0206B384
	push {r3-r7, lr}
	add r6, r1, #0x0
	str r2, [sp, #0x0]
	mov r1, #0x0
	ldr r2, [r6, #0x0]
	mvn r1, r1
	cmp r2, r1
	bne _0206B398
	ldr r1, [r0, #0x0]
	str r1, [r6, #0x0]
_0206B398:
	ldr r1, [sp, #0x0]
	ldr r4, [r6, #0x0]
	ldr r5, [r1, #0x0]
	add r7, r0, #0x4
	b _0206B3C8
_0206B3A2:
	mov r0, #0xff
	lsl r0, r0, #0x4
	mul r0, r4
	add r1, r7, r0
	mov r0, #0x88
	mul r0, r5
	add r0, r1, r0
	mov r1, #0xab
	mov r2, #0x0
	bl GetBoxMonDataEncrypted
	cmp r0, #0x0
	bne _0206B3C6
	ldr r0, [sp, #0x0]
	str r4, [r6, #0x0]
	str r5, [r0, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_0206B3C6:
	add r5, r5, #0x1
_0206B3C8:
	cmp r5, #0x1e
	blt _0206B3A2
	add r4, r4, #0x1
	cmp r4, #0x12
	blt _0206B3D4
	mov r4, #0x0
_0206B3D4:
	ldr r0, [r6, #0x0]
	cmp r4, r0
	beq _0206B3DE
	mov r5, #0x0
	b _0206B3C8
_0206B3DE:
	mov r0, #0x12
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206B3E4
FUN_0206B3E4: ; 0x0206B3E4
	push {r3-r7, lr}
	sub sp, #0x8
	mov r6, #0x0
	add r0, r0, #0x4
	str r6, [sp, #0x4]
	str r0, [sp, #0x0]
	mov r7, #0xab
_0206B3F2:
	ldr r5, [sp, #0x0]
	mov r4, #0x0
_0206B3F6:
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x0
	bl GetBoxMonDataEncrypted
	cmp r0, #0x0
	beq _0206B406
	add r6, r6, #0x1
_0206B406:
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x1e
	blt _0206B3F6
	mov r0, #0xff
	ldr r1, [sp, #0x0]
	lsl r0, r0, #0x4
	add r0, r1, r0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	str r0, [sp, #0x4]
	cmp r0, #0x12
	blt _0206B3F2
	add r0, r6, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0206B428
FUN_0206B428: ; 0x0206B428
	push {r3, lr}
	cmp r1, #0x12
	bhs _0206B436
	str r1, [r0, #0x0]
	bl FUN_02022830
	pop {r3, pc}
_0206B436:
	bl ErrorHandling
	pop {r3, pc}

	thumb_func_start FUN_0206B43C
FUN_0206B43C: ; 0x0206B43C
	push {r3, lr}
	cmp r1, #0x12
	bhs _0206B44A
	add r1, r0, r1
	ldr r0, _0206B454 ; =0x000121B4
	ldrb r0, [r1, r0]
	pop {r3, pc}
_0206B44A:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	nop
_0206B454: .word 0x000121B4

	thumb_func_start FUN_0206B458
FUN_0206B458: ; 0x0206B458
	push {r3, lr}
	mov r3, #0x0
	mvn r3, r3
	cmp r1, r3
	bne _0206B464
	ldr r1, [r0, #0x0]
_0206B464:
	cmp r1, #0x12
	bhs _0206B478
	cmp r2, #0x18
	bhs _0206B478
	add r1, r0, r1
	ldr r0, _0206B480 ; =0x000121B4
	strb r2, [r1, r0]
	bl FUN_02022830
	pop {r3, pc}
_0206B478:
	bl ErrorHandling
	pop {r3, pc}
	nop
_0206B480: .word 0x000121B4

	thumb_func_start FUN_0206B484
FUN_0206B484: ; 0x0206B484
	push {r3, lr}
	add r3, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	bne _0206B492
	ldr r1, [r3, #0x0]
_0206B492:
	cmp r1, #0x12
	bhs _0206B4A8
	add r0, r2, #0x0
	ldr r2, _0206B4B0 ; =0x00011EE4
	add r3, r3, r2
	mov r2, #0x28
	mul r2, r1
	add r1, r3, r2
	bl FUN_02021E28
	pop {r3, pc}
_0206B4A8:
	bl ErrorHandling
	pop {r3, pc}
	nop
_0206B4B0: .word 0x00011EE4

	thumb_func_start FUN_0206B4B4
FUN_0206B4B4: ; 0x0206B4B4
	push {r3, lr}
	add r3, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	bne _0206B4C2
	ldr r1, [r3, #0x0]
_0206B4C2:
	cmp r1, #0x12
	bhs _0206B4DC
	add r0, r2, #0x0
	ldr r2, _0206B4E0 ; =0x00011EE4
	add r3, r3, r2
	mov r2, #0x28
	mul r2, r1
	add r1, r3, r2
	mov r2, #0x14
	bl FUN_02021EF0
	bl FUN_02022830
_0206B4DC:
	pop {r3, pc}
	nop
_0206B4E0: .word 0x00011EE4

	thumb_func_start FUN_0206B4E4
FUN_0206B4E4: ; 0x0206B4E4
	push {r3-r7, lr}
	mov r2, #0x0
	mvn r2, r2
	cmp r1, r2
	bne _0206B4F0
	ldr r1, [r0, #0x0]
_0206B4F0:
	cmp r1, #0x12
	bhs _0206B520
	add r2, r0, #0x4
	mov r0, #0xff
	lsl r0, r0, #0x4
	mov r4, #0x0
	mul r0, r1
	add r6, r4, #0x0
	add r5, r2, r0
	mov r7, #0xab
_0206B504:
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x0
	bl GetBoxMonDataEncrypted
	cmp r0, #0x0
	beq _0206B514
	add r4, r4, #0x1
_0206B514:
	add r6, r6, #0x1
	add r5, #0x88
	cmp r6, #0x1e
	blt _0206B504
	add r0, r4, #0x0
	pop {r3-r7, pc}
_0206B520:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0206B528
FUN_0206B528: ; 0x0206B528
	push {r3-r7, lr}
	mov r2, #0x0
	mvn r2, r2
	cmp r1, r2
	bne _0206B534
	ldr r1, [r0, #0x0]
_0206B534:
	cmp r1, #0x12
	bhs _0206B572
	add r2, r0, #0x4
	mov r0, #0xff
	lsl r0, r0, #0x4
	mov r4, #0x0
	mul r0, r1
	add r6, r4, #0x0
	add r5, r2, r0
	mov r7, #0xab
_0206B548:
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x0
	bl GetBoxMonDataEncrypted
	cmp r0, #0x0
	beq _0206B566
	add r0, r5, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetBoxMonDataEncrypted
	cmp r0, #0x0
	bne _0206B566
	add r4, r4, #0x1
_0206B566:
	add r6, r6, #0x1
	add r5, #0x88
	cmp r6, #0x1e
	blt _0206B548
	add r0, r4, #0x0
	pop {r3-r7, pc}
_0206B572:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206B57C
FUN_0206B57C: ; 0x0206B57C
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_0206B584:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0206B528
	add r5, r5, #0x1
	add r4, r4, r0
	cmp r5, #0x12
	blo _0206B584
	add r0, r4, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0206B598
FUN_0206B598: ; 0x0206B598
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r4, #0x12
	blo _0206B5B2
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	beq _0206B5B2
	bl ErrorHandling
_0206B5B2:
	cmp r6, #0x1e
	blo _0206B5BA
	bl ErrorHandling
_0206B5BA:
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	bne _0206B5C4
	ldr r4, [r5, #0x0]
_0206B5C4:
	mov r0, #0xff
	lsl r0, r0, #0x4
	add r1, r5, #0x4
	mul r0, r4
	add r1, r1, r0
	mov r0, #0x88
	mul r0, r6
	add r0, r1, r0
	ldr r2, [sp, #0x18]
	add r1, r7, #0x0
	bl SetBoxMonDataEncrypted
	bl FUN_02022830
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206B5E4
FUN_0206B5E4: ; 0x0206B5E4
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x12
	blo _0206B5FC
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	beq _0206B5FC
	bl ErrorHandling
_0206B5FC:
	cmp r6, #0x1e
	blo _0206B604
	bl ErrorHandling
_0206B604:
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	bne _0206B60E
	ldr r4, [r5, #0x0]
_0206B60E:
	mov r0, #0xff
	lsl r0, r0, #0x4
	add r1, r5, #0x4
	mul r0, r4
	add r1, r1, r0
	mov r0, #0x88
	mul r0, r6
	add r0, r1, r0
	pop {r4-r6, pc}

	thumb_func_start FUN_0206B620
FUN_0206B620: ; 0x0206B620
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x8
	blo _0206B62E
	bl ErrorHandling
_0206B62E:
	ldr r0, _0206B640 ; =0x000121C6
	mov r1, #0x1
	ldrb r2, [r5, r0]
	lsl r1, r4
	orr r1, r2
	strb r1, [r5, r0]
	bl FUN_02022830
	pop {r3-r5, pc}
	.balign 4
_0206B640: .word 0x000121C6

	thumb_func_start FUN_0206B644
FUN_0206B644: ; 0x0206B644
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x8
	blo _0206B652
	bl ErrorHandling
_0206B652:
	ldr r0, _0206B664 ; =0x000121C6
	ldrb r2, [r5, r0]
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r1, r4
	tst r1, r2
	bne _0206B662
	mov r0, #0x0
_0206B662:
	pop {r3-r5, pc}
	.balign 4
_0206B664: .word 0x000121C6

	thumb_func_start FUN_0206B668
FUN_0206B668: ; 0x0206B668
	push {r4-r6, lr}
	mov r4, #0x0
	add r6, r0, #0x0
	add r5, r4, #0x0
_0206B670:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0206B644
	cmp r0, #0x0
	beq _0206B67E
	add r5, r5, #0x1
_0206B67E:
	add r4, r4, #0x1
	cmp r4, #0x8
	blo _0206B670
	add r0, r5, #0x0
	pop {r4-r6, pc}
