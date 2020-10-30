	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	#in c file
	.extern MOD05_021E7388

	thumb_func_start MOD05_021E73B4
MOD05_021E73B4: ; 0x021E73B4
	push {r4, r5, r6, lr}
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	bl FUN_020553A0
	add r6, r0, #0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021E73DC
	cmp r0, #1
	beq _021E73EE
	cmp r0, #2
	beq _021E741C
	b _021E74CA
_021E73DC:
	mov r1, #1
	add r0, r6, #0
	lsl r1, r1, #8
	bl FUN_02058410
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _021E74CA
_021E73EE:
	ldr r0, [r4, #0x10]
	bl FUN_02057254
	cmp r0, #0
	beq _021E74CA
	ldr r0, [r4]
	mov r1, #0xc
	bl FUN_0205AFDC
	add r1, r0, #0
	ldr r0, [r4, #0x10]
	bl FUN_02057260
	ldr r0, [r4, #0x10]
	ldr r1, [r4]
	bl FUN_02055304
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #7
	str r0, [r4, #4]
	b _021E74CA
_021E741C:
	ldr r0, [r4, #4]
	cmp r0, #2
	beq _021E742A
	cmp r0, #4
	beq _021E742A
	cmp r0, #6
	bne _021E743A
_021E742A:
	ldr r0, [r4]
	bl MOD05_021E7388
	str r0, [r4]
	ldr r0, [r4, #0x10]
	ldr r1, [r4]
	bl FUN_02055304
_021E743A:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bne _021E74CA
	add r0, r5, #0
	bl FUN_02054B30
	cmp r0, #1
	bne _021E7452
	mov r0, #3
	str r0, [r4]
	b _021E748A
_021E7452:
	add r0, r5, #0
	bl FUN_02054B3C
	cmp r0, #1
	bne _021E7462
	mov r0, #2
	str r0, [r4]
	b _021E748A
_021E7462:
	add r0, r5, #0
	bl FUN_02054B48
	cmp r0, #1
	bne _021E7472
	mov r0, #0
	str r0, [r4]
	b _021E748A
_021E7472:
	add r0, r5, #0
	bl FUN_02054B54
	cmp r0, #1
	bne _021E7482
	mov r0, #1
	str r0, [r4]
	b _021E748A
_021E7482:
	ldr r0, [r4]
	bl MOD05_021E7388
	str r0, [r4]
_021E748A:
	ldr r0, [r4, #0x10]
	ldr r2, [r4]
	add r1, r6, #0
	bl FUN_02056B74
	cmp r0, #0
	bne _021E749E
	mov r0, #1
	str r0, [r4, #8]
	b _021E74CA
_021E749E:
	add r0, r6, #0
	mov r1, #0x80
	bl FUN_02058418
	mov r1, #1
	add r0, r6, #0
	lsl r1, r1, #8
	bl FUN_02058418
	ldr r0, [r4, #0x10]
	ldr r1, [r4]
	bl FUN_02055304
	add r0, r4, #0
	bl MOD05_021E74F8
	ldr r0, _021E74D0 ; =0x00000658
	mov r1, #0
	bl FUN_020054F0
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E74CA:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_021E74D0: .word 0x00000658

	thumb_func_start MOD05_021E74D4
MOD05_021E74D4: ; 0x021E74D4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #4
	add r1, r5, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	bne _021E74E8
	bl ErrorHandling
_021E74E8:
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl memset
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E74F8
MOD05_021E74F8: ; 0x021E74F8
	ldr r3, _021E7500 ; =FUN_02016A8C
	add r1, r0, #0
	mov r0, #4
	bx r3
	.balign 4, 0
_021E7500: .word FUN_02016A8C
