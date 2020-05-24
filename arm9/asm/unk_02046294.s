    .include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global UNK_021C5A14
UNK_021C5A14: ; 0x021C5A14
	.space 0x8

	.text

	thumb_func_start FUN_02046294
FUN_02046294: ; 0x02046294
	mov r0, #0xeb
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_0204629C
FUN_0204629C: ; 0x0204629C
	ldr r3, _020462A8 ; =memset
	mov r2, #0xeb
	mov r1, #0x0
	lsl r2, r2, #0x2
	bx r3
	nop
_020462A8: .word memset

	thumb_func_start FUN_020462AC
FUN_020462AC: ; 0x020462AC
	ldr r3, _020462B4 ; =FUN_02022610
	mov r1, #0x4
	bx r3
	nop
_020462B4: .word FUN_02022610

	thumb_func_start FUN_020462B8
FUN_020462B8: ; 0x020462B8
	push {r3-r5, lr}
	add r4, r1, #0x0
	bl FUN_02046338
	cmp r0, #0x0
	beq _020462DE
	lsr r3, r4, #0x1f
	lsl r2, r4, #0x1d
	ldrb r5, [r0, #0x0]
	sub r2, r2, r3
	mov r1, #0x1d
	ror r2, r1
	mov r0, #0x1
	add r1, r3, r2
	add r2, r0, #0x0
	lsl r2, r1
	add r1, r5, #0x0
	tst r1, r2
	bne _020462E0
_020462DE:
	mov r0, #0x0
_020462E0:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020462E4
FUN_020462E4: ; 0x020462E4
	push {r4-r6, lr}
	add r4, r1, #0x0
	bl FUN_02046338
	cmp r0, #0x0
	beq _02046308
	lsr r5, r4, #0x1f
	lsl r3, r4, #0x1d
	sub r3, r3, r5
	mov r2, #0x1d
	ror r3, r2
	mov r6, #0x1
	add r2, r5, r3
	add r3, r6, #0x0
	ldrb r1, [r0, #0x0]
	lsl r3, r2
	orr r1, r3
	strb r1, [r0, #0x0]
_02046308:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204630C
FUN_0204630C: ; 0x0204630C
	push {r4-r6, lr}
	add r4, r1, #0x0
	bl FUN_02046338
	cmp r0, #0x0
	beq _02046334
	lsr r5, r4, #0x1f
	lsl r3, r4, #0x1d
	sub r3, r3, r5
	mov r2, #0x1d
	ror r3, r2
	mov r6, #0x1
	add r2, r5, r3
	add r3, r6, #0x0
	lsl r3, r2
	mov r2, #0xff
	ldrb r1, [r0, #0x0]
	eor r2, r3
	and r1, r2
	strb r1, [r0, #0x0]
_02046334:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02046338
FUN_02046338: ; 0x02046338
	push {r3-r5, lr}
	add r5, r0, #0x0
	cmp r1, #0x0
	bne _02046344
	mov r0, #0x0
	pop {r3-r5, pc}
_02046344:
	mov r0, #0x1
	lsl r0, r0, #0xe
	cmp r1, r0
	bhs _02046364
	mov r0, #0x5b
	lsr r4, r1, #0x3
	lsl r0, r0, #0x2
	cmp r4, r0
	blt _0204635A
	bl ErrorHandling
_0204635A:
	mov r0, #0x9
	lsl r0, r0, #0x6
	add r0, r5, r0
	add r0, r0, r4
	pop {r3-r5, pc}
_02046364:
	sub r1, r1, r0
	asr r0, r1, #0x2
	lsr r0, r0, #0x1d
	add r0, r1, r0
	asr r4, r0, #0x3
	cmp r4, #0x8
	blt _02046376
	bl ErrorHandling
_02046376:
	ldr r0, _0204637C ; =UNK_021C5A14
	add r0, r0, r4
	pop {r3-r5, pc}
	.balign 4
_0204637C: .word UNK_021C5A14

	thumb_func_start FUN_02046380
FUN_02046380: ; 0x02046380
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x1
	lsl r0, r0, #0xe
	sub r4, r1, r0
	mov r0, #0x12
	lsl r0, r0, #0x4
	cmp r4, r0
	blt _02046396
	bl ErrorHandling
_02046396:
	lsl r0, r4, #0x1
	add r0, r5, r0
	pop {r3-r5, pc}
