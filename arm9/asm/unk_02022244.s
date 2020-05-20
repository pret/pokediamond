	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02022244
FUN_02022244: ; 0x02022244
	push {r3-r4}
	ldr r3, [r0, #0xc]
	mov r2, #0x0
	sub r3, r3, #0x1
	beq _02022262
	ldr r4, [r0, #0x0]
_02022250:
	ldrh r3, [r4, #0x2]
	cmp r3, r1
	bhi _02022262
	ldr r3, [r0, #0xc]
	add r2, r2, #0x1
	sub r3, r3, #0x1
	add r4, r4, #0x2
	cmp r2, r3
	blo _02022250
_02022262:
	ldr r1, [r0, #0x4]
	ldrb r3, [r1, r2]
	add r1, sp, #0x0
	strb r3, [r1, #0x0]
	ldr r0, [r0, #0x8]
	ldrb r2, [r0, r2]
	strb r2, [r1, #0x1]
	ldrb r0, [r1, #0x0]
	lsl r1, r2, #0x8
	orr r0, r1
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0202227C
FUN_0202227C: ; 0x0202227C
	ldr r2, [r0, #0x0]
	str r2, [r1, #0xc]
	add r2, r0, #0x4
	str r2, [r1, #0x0]
	ldr r0, [r1, #0xc]
	lsl r0, r0, #0x1
	add r2, r2, r0
	str r2, [r1, #0x4]
	ldr r0, [r1, #0xc]
	add r0, r2, r0
	str r0, [r1, #0x8]
	bx lr
