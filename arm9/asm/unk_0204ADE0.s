	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_0204ADE0
FUN_0204ADE0: ; 0x0204ADE0
	mov r3, #0x0
	add r2, r3, #0x0
_0204ADE4:
	lsl r1, r3, #0x2
	add r1, r0, r1
	strb r2, [r1, #0x6]
	strb r2, [r1, #0x7]
	strb r2, [r1, #0x8]
	strb r2, [r1, #0x9]
	add r1, r3, #0x1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0x6
	blo _0204ADE4
	str r2, [r0, #0x0]
	strb r2, [r0, #0x4]
	strb r2, [r0, #0x5]
	bx lr
	.balign 4

	thumb_func_start FUN_0204AE04
FUN_0204AE04: ; 0x0204AE04
	push {r4, lr}
	add r4, r0, #0x0
	asr r0, r1, #0x4
	lsr r0, r0, #0x1b
	add r0, r1, r0
	asr r1, r2, #0x4
	lsr r1, r1, #0x1b
	add r1, r2, r1
	lsl r0, r0, #0x13
	lsl r1, r1, #0x13
	ldrb r2, [r4, #0x4]
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	cmp r0, r2
	bne _0204AE28
	ldrb r2, [r4, #0x5]
	cmp r1, r2
	beq _0204AE58
_0204AE28:
	ldr r2, [r4, #0x0]
	lsl r2, r2, #0x2
	add r2, r4, r2
	strb r0, [r2, #0x6]
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x2
	add r0, r4, r0
	strb r1, [r0, #0x7]
	ldr r0, [r4, #0x0]
	mov r1, #0xff
	lsl r0, r0, #0x2
	add r0, r4, r0
	strb r1, [r0, #0x8]
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	lsl r0, r0, #0x2
	add r0, r4, r0
	strb r1, [r0, #0x9]
	ldr r0, [r4, #0x0]
	mov r1, #0x6
	add r0, r0, #0x1
	bl _s32_div_f
	str r1, [r4, #0x0]
_0204AE58:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0204AE5C
FUN_0204AE5C: ; 0x0204AE5C
	push {r4, lr}
	add r4, r0, #0x0
	lsl r0, r1, #0x18
	lsl r1, r2, #0x18
	ldrb r2, [r4, #0x4]
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	cmp r0, r2
	bne _0204AE74
	ldrb r2, [r4, #0x5]
	cmp r1, r2
	beq _0204AEA6
_0204AE74:
	ldr r2, [r4, #0x0]
	lsl r2, r2, #0x2
	add r2, r4, r2
	strb r0, [r2, #0x6]
	ldr r2, [r4, #0x0]
	lsl r2, r2, #0x2
	add r2, r4, r2
	strb r1, [r2, #0x7]
	ldr r2, [r4, #0x0]
	lsl r2, r2, #0x2
	add r2, r4, r2
	strb r3, [r2, #0x8]
	ldr r2, [r4, #0x0]
	mov r3, #0x1
	lsl r2, r2, #0x2
	add r2, r4, r2
	strb r3, [r2, #0x9]
	strb r0, [r4, #0x4]
	strb r1, [r4, #0x5]
	ldr r0, [r4, #0x0]
	mov r1, #0x6
	add r0, r0, #0x1
	bl _s32_div_f
	str r1, [r4, #0x0]
_0204AEA6:
	pop {r4, pc}
