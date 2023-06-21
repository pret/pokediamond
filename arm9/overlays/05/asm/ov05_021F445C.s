	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021F445C
ov05_021F445C: ; 0x021F445C
	push {r4, r5}
	ldr r3, [r2, #0x14]
	cmp r3, #0
	bne _021F446A
	mov r0, #0
	pop {r4, r5}
	bx lr
_021F446A:
	ldr r5, [r2]
	ldr r3, [r2, #8]
	ldr r4, [r2, #4]
	ldr r2, [r2, #0xc]
	add r3, r5, r3
	add r2, r4, r2
	sub r3, r3, #1
	sub r2, r2, #1
	cmp r5, r0
	bgt _021F4490
	cmp r0, r3
	bgt _021F4490
	cmp r4, r1
	bgt _021F4490
	cmp r1, r2
	bgt _021F4490
	mov r0, #1
	pop {r4, r5}
	bx lr
_021F4490:
	mov r0, #0
	pop {r4, r5}
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F4498
ov05_021F4498: ; 0x021F4498
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #8
	bl AllocFromHeap
	mov r1, #0x18
	add r4, r0, #0
	add r0, r6, #0
	mul r1, r5
	bl AllocFromHeap
	str r0, [r4, #4]
	mov r6, #0
	str r5, [r4]
	cmp r5, #0
	bls _021F44D4
	add r0, r6, #0
	mov r1, #0x18
_021F44C0:
	add r2, r6, #0
	ldr r3, [r4, #4]
	mul r2, r1
	add r2, r3, r2
	str r0, [r2, #0x14]
	add r2, r6, #1
	lsl r2, r2, #0x18
	lsr r6, r2, #0x18
	cmp r6, r5
	blo _021F44C0
_021F44D4:
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021F44D8
ov05_021F44D8: ; 0x021F44D8
	push {r4, r5}
	ldr r5, [sp, #0x10]
	mov r4, #0x18
	mul r4, r0
	ldr r0, [r5, #4]
	str r1, [r0, r4]
	ldr r0, [r5, #4]
	ldr r1, [sp, #8]
	add r0, r0, r4
	str r2, [r0, #4]
	ldr r0, [r5, #4]
	add r0, r0, r4
	str r3, [r0, #8]
	ldr r0, [r5, #4]
	add r0, r0, r4
	str r1, [r0, #0xc]
	ldr r0, [r5, #4]
	ldr r1, [sp, #0xc]
	add r0, r0, r4
	str r1, [r0, #0x10]
	ldr r0, [r5, #4]
	mov r1, #1
	add r0, r0, r4
	str r1, [r0, #0x14]
	pop {r4, r5}
	bx lr

	thumb_func_start ov05_021F450C
ov05_021F450C: ; 0x021F450C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021F4520
ov05_021F4520: ; 0x021F4520
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	add r5, r2, #0
	str r3, [sp]
	cmp r3, #0
	bne _021F4532
	bl GF_AssertFail
_021F4532:
	ldr r0, [r5]
	mov r4, #0
	cmp r0, #0
	ble _021F4562
_021F453A:
	mov r3, #0x18
	ldr r2, [r5, #4]
	mul r3, r4
	add r0, r6, #0
	add r1, r7, #0
	add r2, r2, r3
	bl ov05_021F445C
	cmp r0, #0
	beq _021F4556
	ldr r0, [sp]
	strb r4, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F4556:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [r5]
	cmp r4, r0
	blt _021F453A
_021F4562:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F4568
ov05_021F4568: ; 0x021F4568
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r5, r0
	blt _021F4578
	bl GF_AssertFail
_021F4578:
	mov r0, #0x18
	add r6, r5, #0
	mul r6, r0
	ldr r0, [r4, #4]
	add r0, r0, r6
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _021F458C
	bl GF_AssertFail
_021F458C:
	ldr r0, [r4, #4]
	add r0, r0, r6
	ldr r0, [r0, #0x10]
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021F4594
ov05_021F4594: ; 0x021F4594
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r0, #0
	ldr r0, [r6]
	add r4, r1, #0
	cmp r5, r0
	blt _021F45A6
	bl GF_AssertFail
_021F45A6:
	mov r0, #0x18
	ldr r1, [r6, #4]
	mul r0, r5
	add r0, r1, r0
	str r4, [r0, #0x10]
	pop {r4, r5, r6, pc}
	.balign 4, 0
