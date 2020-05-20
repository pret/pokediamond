    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0205C334
FUN_0205C334: ; 0x0205C334
	cmp r0, #0x64
	bne _0205C33C
	mov r0, #0x1
	bx lr
_0205C33C:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0205C340
FUN_0205C340: ; 0x0205C340
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020585B0
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0205C352
	ldr r0, _0205C370 ; =0x0000FFFF
	pop {r4, pc}
_0205C352:
	add r0, r4, #0x0
	bl FUN_02058934
	cmp r0, #0x1
	bne _0205C36C
	add r0, r4, #0x0
	bl FUN_02058628
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0205C36C
	ldr r0, [r0, #0x0]
	pop {r4, pc}
_0205C36C:
	ldr r0, _0205C370 ; =0x0000FFFF
	pop {r4, pc}
	.balign 4
_0205C370: .word 0x0000FFFF

	thumb_func_start FUN_0205C374
FUN_0205C374: ; 0x0205C374
	push {r3, lr}
	bl FUN_020585B0
	mov r1, #0x1
	strh r1, [r0, #0x2]
	pop {r3, pc}

	thumb_func_start FUN_0205C380
FUN_0205C380: ; 0x0205C380
	push {r3, lr}
	mov r1, #0x4
	bl FUN_0205858C
	mov r1, #0x0
	strh r1, [r0, #0x0]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205C390
FUN_0205C390: ; 0x0205C390
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020585B0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058738
	add r1, r5, #0x0
	bl FUN_0204B5FC
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205C3AC
FUN_0205C3AC: ; 0x0205C3AC
	bx lr
	.balign 4

	thumb_func_start FUN_0205C3B0
FUN_0205C3B0: ; 0x0205C3B0
	push {r4, lr}
	mov r1, #0x18
	add r4, r0, #0x0
	bl FUN_02058604
	ldr r1, _0205C3CC ; =0x0000FFFF
	str r1, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	add r0, r4, #0x0
	bl MOD06_0224A310
	pop {r4, pc}
	nop
_0205C3CC: .word 0x0000FFFF

	thumb_func_start FUN_0205C3D0
FUN_0205C3D0: ; 0x0205C3D0
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020585B0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058628
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058738
	add r1, r5, #0x0
	bl FUN_0204B5FC
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl MOD05_021F2E28
	cmp r0, #0x1
	beq _0205C488
	ldr r0, [r4, #0x4]
	cmp r6, r0
	beq _0205C454
	add r1, r4, #0x0
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	add r1, #0x8
	bl MOD05_021F2094
	add r0, r5, #0x0
	bl FUN_02058738
	add r1, r5, #0x0
	bl FUN_0204B61C
	add r1, r6, #0x0
	bl FUN_0205C53C
	ldr r1, _0205C48C ; =0x0000FFFF
	str r0, [r4, #0x0]
	cmp r0, r1
	ldr r0, [r4, #0x4]
	beq _0205C440
	cmp r0, #0x0
	beq _0205C432
	add r0, r5, #0x0
	bl MOD06_0224A528
_0205C432:
	add r1, r4, #0x0
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	add r1, #0x8
	bl MOD05_021F1F78
	b _0205C450
_0205C440:
	cmp r0, #0x0
	beq _0205C450
	ldrh r0, [r7, #0x2]
	cmp r0, #0x0
	bne _0205C450
	add r0, r5, #0x0
	bl MOD06_0224A528
_0205C450:
	mov r0, #0x0
	strh r0, [r7, #0x2]
_0205C454:
	add r0, r5, #0x0
	str r6, [r4, #0x4]
	bl MOD05_021F2E28
	cmp r0, #0x1
	beq _0205C488
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	beq _0205C488
	add r0, r5, #0x0
	bl MOD05_021F2F48
	add r0, r5, #0x0
	bl MOD05_021F1DFC
	cmp r0, #0x0
	bne _0205C480
	mov r1, #0x1
	ldr r0, [r4, #0x8]
	lsl r1, r1, #0xc
	bl FUN_0201F854
_0205C480:
	ldr r1, [r4, #0x8]
	add r0, r5, #0x0
	bl MOD05_021F2F6C
_0205C488:
	pop {r3-r7, pc}
	nop
_0205C48C: .word 0x0000FFFF

	thumb_func_start FUN_0205C490
FUN_0205C490: ; 0x0205C490
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058628
	add r2, r0, #0x0
	add r1, r2, #0x0
	ldr r2, [r2, #0x0]
	add r0, r4, #0x0
	add r1, #0x8
	bl MOD05_021F2094
	pop {r4, pc}

	thumb_func_start FUN_0205C4A8
FUN_0205C4A8: ; 0x0205C4A8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02058628
	add r4, r0, #0x0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _0205C4C0
	add r1, r4, #0x0
	add r1, #0xc
	bl MOD05_021F20D8
_0205C4C0:
	add r1, r4, #0x0
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	add r1, #0x8
	bl MOD05_021F2094
	mov r1, #0x2
	add r0, r5, #0x0
	lsl r1, r1, #0x14
	bl FUN_02058410
	pop {r3-r5, pc}

	thumb_func_start FUN_0205C4D8
FUN_0205C4D8: ; 0x0205C4D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02058628
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl MOD05_021F2E28
	cmp r0, #0x1
	beq _0205C536
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	bne _0205C516
	ldr r2, [r4, #0x0]
	ldr r0, _0205C538 ; =0x0000FFFF
	cmp r2, r0
	beq _0205C506
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x8
	bl MOD05_021F1F78
	b _0205C510
_0205C506:
	mov r1, #0x2
	add r0, r5, #0x0
	lsl r1, r1, #0x14
	bl FUN_02058418
_0205C510:
	add r0, r5, #0x0
	bl MOD06_0224A310
_0205C516:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _0205C536
	add r1, r4, #0x0
	add r1, #0xc
	bl MOD05_021F20F8
	ldr r1, [r4, #0x8]
	add r0, r5, #0x0
	bl MOD05_021F2F48
	mov r1, #0x2
	add r0, r5, #0x0
	lsl r1, r1, #0x14
	bl FUN_02058418
_0205C536:
	pop {r3-r5, pc}
	.balign 4
_0205C538: .word 0x0000FFFF

	thumb_func_start FUN_0205C53C
FUN_0205C53C: ; 0x0205C53C
	push {r3, lr}
	cmp r1, #0x0
	beq _0205C548
	cmp r1, #0x1
	beq _0205C54C
	b _0205C550
_0205C548:
	ldr r0, _0205C590 ; =0x0000FFFF
	pop {r3, pc}
_0205C54C:
	ldr r0, _0205C590 ; =0x0000FFFF
	pop {r3, pc}
_0205C550:
	sub r2, r0, #0x1
	mov r0, #0xc
	ldr r3, _0205C594 ; =0x021F9194
	mul r0, r2
	add r2, r3, r0
	cmp r1, #0x5
	bhi _0205C588
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205C56A: ; jump table (using 16-bit offset)
	.short _0205C588 - _0205C56A - 2; case 0
	.short _0205C588 - _0205C56A - 2; case 1
	.short _0205C576 - _0205C56A - 2; case 2
	.short _0205C57C - _0205C56A - 2; case 3
	.short _0205C580 - _0205C56A - 2; case 4
	.short _0205C584 - _0205C56A - 2; case 5
_0205C576:
	mov r0, #0x1
	lsl r0, r0, #0xc
	pop {r3, pc}
_0205C57C:
	ldr r0, [r2, #0x0]
	pop {r3, pc}
_0205C580:
	ldr r0, [r2, #0x4]
	pop {r3, pc}
_0205C584:
	ldr r0, [r2, #0x8]
	pop {r3, pc}
_0205C588:
	bl ErrorHandling
	ldr r0, _0205C590 ; =0x0000FFFF
	pop {r3, pc}
	.balign 4
_0205C590: .word 0x0000FFFF
_0205C594: .word 0x021F9194
