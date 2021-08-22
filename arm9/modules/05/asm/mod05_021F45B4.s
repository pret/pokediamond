	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021F45B4
MOD05_021F45B4: ; 0x021F45B4
	push {r4, lr}
	mov r1, #0x1c
	bl AllocFromHeap
	add r4, r0, #0
	bl MOD05_021F4650
	add r0, r4, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F45C8
MOD05_021F45C8: ; 0x021F45C8
	push {r4, lr}
	add r4, r0, #0
	beq _021F45E4
	ldr r1, [r4]
	cmp r1, #1
	bne _021F45D8
	bl MOD05_021F4608
_021F45D8:
	add r0, r4, #0
	bl MOD05_021F4650
	add r0, r4, #0
	bl FreeToHeap
_021F45E4:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F45E8
MOD05_021F45E8: ; 0x021F45E8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021F4604 ; =MOD05_021F4688
	add r1, r4, #0
	bl FUN_02015F34
	cmp r0, #1
	beq _021F45FC
	bl GF_AssertFail
_021F45FC:
	mov r0, #1
	str r0, [r4]
	pop {r4, pc}
	nop
_021F4604: .word MOD05_021F4688

	thumb_func_start MOD05_021F4608
MOD05_021F4608: ; 0x021F4608
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F34
	cmp r0, #1
	beq _021F461C
	bl GF_AssertFail
_021F461C:
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4624
MOD05_021F4624: ; 0x021F4624
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r2, #0
	bl MOD05_021F46A8
	add r4, r0, #0
	bne _021F4636
	bl GF_AssertFail
_021F4636:
	cmp r4, #0
	beq _021F4642
	str r6, [r4, #4]
	str r5, [r4, #8]
	mov r0, #1
	str r0, [r4]
_021F4642:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4648
MOD05_021F4648: ; 0x021F4648
	ldr r3, _021F464C ; =MOD05_021F4678
	bx r3
	.balign 4, 0
_021F464C: .word MOD05_021F4678

	thumb_func_start MOD05_021F4650
MOD05_021F4650: ; 0x021F4650
	push {r3, r4, r5, lr}
	add r3, r0, #0
	mov r2, #0x1c
	mov r1, #0
_021F4658:
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _021F4658
	mov r4, #0
	str r4, [r0]
	add r5, r0, #4
_021F4666:
	add r0, r5, #0
	bl MOD05_021F4678
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #2
	blt _021F4666
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4678
MOD05_021F4678: ; 0x021F4678
	mov r2, #0
	ldr r1, _021F4684 ; =MOD05_021F46A4
	str r2, [r0]
	str r1, [r0, #8]
	str r2, [r0, #4]
	bx lr
	.balign 4, 0
_021F4684: .word MOD05_021F46A4

	thumb_func_start MOD05_021F4688
MOD05_021F4688: ; 0x021F4688
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #4
_021F4690:
	ldr r1, [r5, #8]
	ldr r2, [r5, #0xc]
	add r0, r4, #0
	blx r2
	add r6, r6, #1
	add r5, #0xc
	add r4, #0xc
	cmp r6, #2
	blt _021F4690
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F46A4
MOD05_021F46A4: ; 0x021F46A4
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F46A8
MOD05_021F46A8: ; 0x021F46A8
	mov r2, #0
	add r3, r0, #0
_021F46AC:
	ldr r1, [r3, #4]
	cmp r1, #0
	bne _021F46BC
	add r1, r0, #4
	mov r0, #0xc
	mul r0, r2
	add r0, r1, r0
	bx lr
_021F46BC:
	add r2, r2, #1
	add r3, #0xc
	cmp r2, #2
	blt _021F46AC
	mov r0, #0
	bx lr
