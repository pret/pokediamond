	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0201C360
FUN_0201C360: ; 0x0201C360
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x8
	bl FUN_02016998
	mov r1, #0x14
	add r4, r0, #0x0
	add r0, r6, #0x0
	mul r1, r5
	bl FUN_02016998
	str r0, [r4, #0x0]
	mov r6, #0x0
	str r5, [r4, #0x4]
	cmp r5, #0x0
	ble _0201C398
	add r5, r6, #0x0
_0201C386:
	ldr r0, [r4, #0x0]
	add r0, r0, r5
	bl FUN_0201C444
	ldr r0, [r4, #0x4]
	add r6, r6, #0x1
	add r5, #0x14
	cmp r6, r0
	blt _0201C386
_0201C398:
	add r0, r4, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0201C39C
FUN_0201C39C: ; 0x0201C39C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201C414
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201C3B4
FUN_0201C3B4: ; 0x0201C3B4
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r4, #0x0
	add r7, r2, #0x0
	mov r12, r1
	add r6, r3, #0x0
	add r2, r4, #0x0
	cmp r0, #0x0
	ble _0201C3E2
	ldr r5, [r5, #0x0]
	add r3, r5, #0x0
_0201C3CC:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	bne _0201C3DA
	mov r0, #0x14
	mul r0, r2
	add r4, r5, r0
	b _0201C3E2
_0201C3DA:
	add r2, r2, #0x1
	add r3, #0x14
	cmp r2, r0
	blt _0201C3CC
_0201C3E2:
	cmp r4, #0x0
	bne _0201C3EA
	mov r0, #0x0
	pop {r3-r7, pc}
_0201C3EA:
	mov r0, r12
	str r0, [r4, #0x0]
	str r7, [r4, #0x4]
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	str r6, [r4, #0x8]
	str r0, [r4, #0xc]
	mov r0, #0xff
	strb r0, [r4, #0x10]
	lsl r1, r1, #0x4
	strb r0, [r4, #0x11]
	add r0, r4, #0x0
	lsr r1, r1, #0x10
	bl FUN_0201C454
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0201C40C
FUN_0201C40C: ; 0x0201C40C
	ldr r3, _0201C410 ; =FUN_0201C444
	bx r3
	.balign 4
_0201C410: .word FUN_0201C444

	thumb_func_start FUN_0201C414
FUN_0201C414: ; 0x0201C414
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0201C434
	add r4, r6, #0x0
_0201C422:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	bl FUN_0201C444
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0x14
	cmp r6, r0
	blt _0201C422
_0201C434:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0201C438
FUN_0201C438: ; 0x0201C438
	ldr r3, _0201C440 ; =FUN_0201C454
	lsl r1, r1, #0x4
	lsr r1, r1, #0x10
	bx r3
	.balign 4
_0201C440: .word FUN_0201C454

	thumb_func_start FUN_0201C444
FUN_0201C444: ; 0x0201C444
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	str r1, [r0, #0xc]
	strb r1, [r0, #0x10]
	strb r1, [r0, #0x11]
	bx lr

	thumb_func_start FUN_0201C454
FUN_0201C454: ; 0x0201C454
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02022244
	add r2, sp, #0x0
	strb r0, [r2, #0x0]
	lsr r0, r0, #0x8
	strb r0, [r2, #0x1]
	ldrb r0, [r2, #0x0]
	add r1, sp, #0x0
	add r1, #0x2
	strb r0, [r2, #0x2]
	ldrb r0, [r2, #0x1]
	strb r0, [r2, #0x3]
	ldrb r3, [r4, #0x10]
	ldrb r0, [r2, #0x2]
	cmp r3, r0
	beq _0201C482
	add r0, r4, #0x0
	bl FUN_0201C49C
_0201C482:
	add r0, sp, #0x0
	ldrb r1, [r4, #0x11]
	ldrb r0, [r0, #0x3]
	cmp r1, r0
	beq _0201C496
	add r1, sp, #0x0
	add r0, r4, #0x0
	add r1, #0x2
	bl FUN_0201C4C8
_0201C496:
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201C49C
FUN_0201C49C: ; 0x0201C49C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0201C4F4
	ldr r3, [r5, #0x8]
	add r2, r0, #0x0
	lsl r1, r3, #0x10
	ldr r6, _0201C4C4 ; =0x7FFF0000
	mov r0, #0x0
	and r3, r6
	lsr r3, r3, #0x10
	lsr r1, r1, #0xd
	lsl r3, r3, #0x4
	bl FUN_0201C2C8
	ldrb r0, [r4, #0x0]
	strb r0, [r5, #0x10]
	pop {r4-r6, pc}
	nop
_0201C4C4: .word 0x7FFF0000

	thumb_func_start FUN_0201C4C8
FUN_0201C4C8: ; 0x0201C4C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0201C500
	ldr r3, [r5, #0xc]
	add r2, r0, #0x0
	lsl r1, r3, #0x10
	ldr r6, _0201C4F0 ; =0xFFFF0000
	mov r0, #0x1
	and r3, r6
	lsr r3, r3, #0x10
	lsr r1, r1, #0xd
	lsl r3, r3, #0x3
	bl FUN_0201C2C8
	ldrb r0, [r4, #0x1]
	strb r0, [r5, #0x11]
	pop {r4-r6, pc}
	nop
_0201C4F0: .word 0xFFFF0000

	thumb_func_start FUN_0201C4F4
FUN_0201C4F4: ; 0x0201C4F4
	ldr r3, _0201C4FC ; =FUN_0201C50C
	ldr r0, [r0, #0x4]
	ldrb r1, [r1, #0x0]
	bx r3
	.balign 4
_0201C4FC: .word FUN_0201C50C

	thumb_func_start FUN_0201C500
FUN_0201C500: ; 0x0201C500
	ldr r3, _0201C508 ; =FUN_0201C540
	ldr r0, [r0, #0x4]
	ldrb r1, [r1, #0x1]
	bx r3
	.balign 4
_0201C508: .word FUN_0201C540

	thumb_func_start FUN_0201C50C
FUN_0201C50C: ; 0x0201C50C
	push {r3-r4}
	add r2, r0, #0x0
	add r2, #0x42
	ldrh r2, [r2, #0x0]
	add r4, r0, #0x0
	add r4, #0x3c
	add r3, r4, r2
	ldrh r2, [r4, r2]
	add r3, r3, #0x4
	mul r1, r2
	add r3, r3, r1
	bne _0201C52A
	mov r0, #0x0
	pop {r3-r4}
	bx lr
_0201C52A:
	ldr r1, [r0, #0x14]
	add r2, r0, r1
	ldr r1, [r3, #0x0]
	ldr r0, [r0, #0x8]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	add r0, r1, r0
	lsl r0, r0, #0x3
	add r0, r2, r0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201C540
FUN_0201C540: ; 0x0201C540
	push {r3-r4}
	ldrh r2, [r0, #0x34]
	add r4, r0, r2
	ldrh r2, [r4, #0x6]
	add r3, r4, r2
	ldrh r2, [r4, r2]
	add r3, r3, #0x4
	mul r1, r2
	add r2, r3, r1
	bne _0201C55A
	mov r0, #0x0
	pop {r3-r4}
	bx lr
_0201C55A:
	ldr r1, [r0, #0x38]
	add r1, r0, r1
	ldrh r0, [r2, #0x0]
	lsl r0, r0, #0x3
	add r0, r1, r0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201C568
FUN_0201C568: ; 0x0201C568
	ldr r1, [r1, #0x0]
	ldr r0, [r0, #0x8]
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	lsr r1, r1, #0xd
	lsr r0, r0, #0xd
	add r0, r1, r0
	bx lr

	thumb_func_start FUN_0201C578
FUN_0201C578: ; 0x0201C578
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_0201C750
	add r0, r4, #0x0
	add r0, #0x3c
	add r1, sp, #0x0
	bl FUN_020BC2A0
	add r1, r0, #0x0
	bne _0201C598
	add sp, #0x10
	mov r0, #0x0
	pop {r4, pc}
_0201C598:
	add r0, r4, #0x0
	bl FUN_0201C568
	add sp, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201C5A4
FUN_0201C5A4: ; 0x0201C5A4
	push {r3, lr}
	ldr r0, [r1, #0x0]
	mov r1, #0x7
	lsl r1, r1, #0x1a
	and r1, r0
	lsr r1, r1, #0x1a
	cmp r1, #0x4
	bhi _0201C5DA
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0201C5C0: ; jump table (using 16-bit offset)
	.short _0201C5DA - _0201C5C0 - 2; case 0
	.short _0201C5D6 - _0201C5C0 - 2; case 1
	.short _0201C5CA - _0201C5C0 - 2; case 2
	.short _0201C5CE - _0201C5C0 - 2; case 3
	.short _0201C5D2 - _0201C5C0 - 2; case 4
_0201C5CA:
	mov r1, #0x4
	b _0201C5DE
_0201C5CE:
	mov r1, #0x2
	b _0201C5DE
_0201C5D2:
	mov r1, #0x1
	b _0201C5DE
_0201C5D6:
	mov r1, #0x1
	b _0201C5DE
_0201C5DA:
	mov r0, #0x0
	pop {r3, pc}
_0201C5DE:
	mov r3, #0x7
	lsl r3, r3, #0x14
	add r2, r0, #0x0
	and r2, r3
	lsl r3, r3, #0x3
	and r0, r3
	lsr r2, r2, #0x14
	lsr r0, r0, #0x17
	lsl r2, r2, #0x4
	lsl r0, r0, #0x4
	mul r0, r2
	bl _u32_div_f
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201C5FC
FUN_0201C5FC: ; 0x0201C5FC
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_0201C750
	add r0, r4, #0x0
	add r0, #0x3c
	add r1, sp, #0x0
	bl FUN_020BC2A0
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0201C5A4
	add sp, #0x10
	pop {r4, pc}
	.balign 4
