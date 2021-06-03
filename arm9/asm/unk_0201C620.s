	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_0201C620
FUN_0201C620: ; 0x0201C620
	ldrb r3, [r0, #0x0]
	strb r3, [r1, #0x0]
	ldrb r0, [r0, #0x1]
	strb r0, [r2, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0201C62C
FUN_0201C62C: ; 0x0201C62C
	ldrb r3, [r0, #0x2]
	strb r3, [r1, #0x0]
	ldrb r0, [r0, #0x3]
	strb r0, [r2, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0201C638
FUN_0201C638: ; 0x0201C638
	push {r4-r5}
	ldr r5, _0201C6B0 ; =0xFFFFFFF8
	ldr r4, [sp, #0xc]
	add r5, sp
	ldrb r5, [r5, #0x18]
	cmp r5, #0x3
	bhi _0201C678
	add r5, r5, r5
	add r5, pc
	ldrh r5, [r5, #0x6]
	lsl r5, r5, #0x10
	asr r5, r5, #0x10
	add pc, r5
_0201C652: ; jump table (using 16-bit offset)
	.short _0201C65A - _0201C652 - 2; case 0
	.short _0201C662 - _0201C652 - 2; case 1
	.short _0201C66A - _0201C652 - 2; case 2
	.short _0201C672 - _0201C652 - 2; case 3
_0201C65A:
	lsl r4, r4, #0x3
	add r4, r0, r4
	ldrb r4, [r4, #0x4]
	b _0201C678
_0201C662:
	lsl r4, r4, #0x3
	add r4, r0, r4
	ldrb r4, [r4, #0x5]
	b _0201C678
_0201C66A:
	lsl r4, r4, #0x3
	add r4, r0, r4
	ldrb r4, [r4, #0x6]
	b _0201C678
_0201C672:
	lsl r4, r4, #0x3
	add r4, r0, r4
	ldrb r4, [r4, #0x7]
_0201C678:
	cmp r1, #0x0
	beq _0201C682
	lsl r5, r4, #0x3
	ldrb r5, [r0, r5]
	strb r5, [r1, #0x0]
_0201C682:
	cmp r2, #0x0
	beq _0201C68E
	lsl r1, r4, #0x3
	add r1, r0, r1
	ldrb r1, [r1, #0x1]
	strb r1, [r2, #0x0]
_0201C68E:
	cmp r3, #0x0
	beq _0201C69A
	lsl r1, r4, #0x3
	add r1, r0, r1
	ldrb r1, [r1, #0x2]
	strb r1, [r3, #0x0]
_0201C69A:
	ldr r2, [sp, #0x8]
	cmp r2, #0x0
	beq _0201C6A8
	lsl r1, r4, #0x3
	add r0, r0, r1
	ldrb r0, [r0, #0x3]
	strb r0, [r2, #0x0]
_0201C6A8:
	add r0, r4, #0x0
	pop {r4-r5}
	bx lr
	nop
_0201C6B0: .word 0xFFFFFFF8
