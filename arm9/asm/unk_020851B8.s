    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_020851B8
FUN_020851B8: ; 0x020851B8
	push {r3, lr}
	mov r1, #0xc
	bl FUN_02016998
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	strb r1, [r0, #0x8]
	strb r1, [r0, #0x9]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	pop {r3, pc}

	thumb_func_start FUN_020851DC
FUN_020851DC: ; 0x020851DC
	push {r4-r6, lr}
	sub r1, #0x95
	lsl r1, r1, #0x10
	lsr r6, r1, #0x10
	add r1, r6, #0x0
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02085200
	cmp r4, #0x1
	bne _020851F4
	strb r6, [r5, #0x8]
_020851F4:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020851F8
FUN_020851F8: ; 0x020851F8
	strb r1, [r0, #0x9]
	strb r2, [r0, #0xa]
	strb r3, [r0, #0xb]
	bx lr

	thumb_func_start FUN_02085200
FUN_02085200: ; 0x02085200
	push {r3-r6}
	lsr r6, r1, #0x1f
	lsl r5, r1, #0x1b
	lsr r2, r1, #0x5
	lsl r4, r2, #0x2
	sub r5, r5, r6
	mov r1, #0x1b
	ror r5, r1
	ldr r3, [r0, r4]
	mov r2, #0x1
	add r1, r6, r5
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r0, r4]
	pop {r3-r6}
	bx lr
	.balign 4

	thumb_func_start FUN_02085224
FUN_02085224: ; 0x02085224
	push {r4-r5}
	lsr r5, r1, #0x1f
	lsl r4, r1, #0x1b
	lsr r1, r1, #0x5
	lsl r1, r1, #0x2
	sub r4, r4, r5
	mov r3, #0x1b
	ror r4, r3
	mov r2, #0x1
	add r3, r5, r4
	add r4, r2, #0x0
	lsl r4, r3
	ldr r0, [r0, r1]
	tst r0, r4
	bne _02085244
	mov r2, #0x0
_02085244:
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	pop {r4-r5}
	bx lr

	thumb_func_start FUN_0208524C
FUN_0208524C: ; 0x0208524C
	ldrb r3, [r0, #0x9]
	strb r3, [r1, #0x0]
	ldrb r0, [r0, #0xa]
	strb r0, [r2, #0x0]
	bx lr
	.balign 4
