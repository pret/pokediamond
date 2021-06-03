	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_0202D394
FUN_0202D394: ; 0x0202D394
	str r1, [r0, #0x0]
	strh r2, [r0, #0xa]
	mov r1, #0x0
	strh r1, [r0, #0x4]
	strh r1, [r0, #0x6]
	strh r1, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start FUN_0202D3A4
FUN_0202D3A4: ; 0x0202D3A4
	push {r3-r7, lr}
	str r2, [sp, #0x0]
	add r5, r0, #0x0
	add r7, r1, #0x0
	bl FUN_0202D498
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bgt _0202D3BC
	bl FUN_02031454
	pop {r3-r7, pc}
_0202D3BC:
	mov r0, #0x8
	ldrsh r4, [r5, r0]
	ldrsh r1, [r5, r0]
	ldr r0, [sp, #0x0]
	mov r6, #0x0
	add r0, r1, r0
	cmp r4, r0
	bge _0202D3F2
_0202D3CC:
	cmp r7, #0x0
	bne _0202D3D4
	bl GF_AssertFail
_0202D3D4:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202D4A8
	ldrb r2, [r7, r6]
	ldr r1, [r5, #0x0]
	add r4, r4, #0x1
	strb r2, [r1, r0]
	mov r0, #0x8
	ldrsh r1, [r5, r0]
	ldr r0, [sp, #0x0]
	add r6, r6, #0x1
	add r0, r1, r0
	cmp r4, r0
	blt _0202D3CC
_0202D3F2:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202D4A8
	strh r0, [r5, #0x8]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202D400
FUN_0202D400: ; 0x0202D400
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0202D42C
	mov r1, #0x4
	add r4, r0, #0x0
	ldrsh r1, [r5, r1]
	add r0, r5, #0x0
	add r1, r1, r4
	bl FUN_0202D4A8
	strh r0, [r5, #0x4]
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0202D41C
FUN_0202D41C: ; 0x0202D41C
	push {r3, lr}
	add r1, sp, #0x0
	mov r2, #0x1
	bl FUN_0202D400
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202D42C
FUN_0202D42C: ; 0x0202D42C
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x4
	ldrsh r4, [r5, r0]
	add r7, r2, #0x0
	str r1, [sp, #0x0]
	add r0, r4, r7
	mov r6, #0x0
	cmp r4, r0
	bge _0202D472
_0202D440:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202D4A8
	mov r1, #0x6
	ldrsh r1, [r5, r1]
	cmp r1, r0
	bne _0202D454
	add r0, r6, #0x0
	pop {r3-r7, pc}
_0202D454:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202D4A8
	ldr r1, [r5, #0x0]
	add r4, r4, #0x1
	ldrb r1, [r1, r0]
	ldr r0, [sp, #0x0]
	strb r1, [r0, r6]
	mov r0, #0x4
	ldrsh r0, [r5, r0]
	add r6, r6, #0x1
	add r0, r0, r7
	cmp r4, r0
	blt _0202D440
_0202D472:
	add r0, r6, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202D478
FUN_0202D478: ; 0x0202D478
	mov r1, #0x4
	mov r3, #0x6
	ldrsh r1, [r0, r1]
	ldrsh r2, [r0, r3]
	cmp r1, r2
	ble _0202D490
	mov r2, #0xa
	ldrsh r2, [r0, r2]
	ldrsh r0, [r0, r3]
	add r0, r2, r0
	sub r0, r0, r1
	bx lr
_0202D490:
	ldrsh r0, [r0, r3]
	sub r0, r0, r1
	bx lr
	.balign 4

	thumb_func_start FUN_0202D498
FUN_0202D498: ; 0x0202D498
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0202D478
	mov r1, #0xa
	ldrsh r1, [r4, r1]
	sub r0, r1, r0
	pop {r4, pc}

	thumb_func_start FUN_0202D4A8
FUN_0202D4A8: ; 0x0202D4A8
	push {r3, lr}
	add r2, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0xa
	ldrsh r1, [r2, r1]
	bl _s32_div_f
	add r0, r1, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202D4BC
FUN_0202D4BC: ; 0x0202D4BC
	mov r1, #0x8
	ldrsh r1, [r0, r1]
	strh r1, [r0, #0x6]
	bx lr
