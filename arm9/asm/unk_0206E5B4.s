    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206E5B4
FUN_0206E5B4: ; 0x0206E5B4
	push {r3-r6}
	add r3, r0, #0x0
	add r0, r2, #0x0
	cmp r1, r0
	beq _0206E63A
	lsl r2, r1, #0x2
	ldrh r4, [r3, r2]
	add r5, r3, r2
	add r2, sp, #0x0
	strh r4, [r2, #0x0]
	ldrh r4, [r5, #0x2]
	strh r4, [r2, #0x2]
	cmp r0, r1
	bls _0206E600
	sub r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r1, r1, #0x10
	lsl r2, r0, #0x10
	asr r1, r1, #0x10
	asr r5, r2, #0x10
	cmp r1, r5
	bge _0206E62C
	lsl r2, r1, #0x2
	add r2, r3, r2
	add r4, r2, #0x0
_0206E5E8:
	ldrh r6, [r2, #0x4]
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	strh r6, [r4, #0x0]
	ldrh r6, [r2, #0x6]
	asr r1, r1, #0x10
	add r2, r2, #0x4
	strh r6, [r4, #0x2]
	add r4, r4, #0x4
	cmp r1, r5
	blt _0206E5E8
	b _0206E62C
_0206E600:
	lsl r1, r1, #0x10
	asr r5, r1, #0x10
	lsl r1, r0, #0x10
	asr r4, r1, #0x10
	cmp r5, r4
	ble _0206E62C
	lsl r1, r5, #0x2
	add r1, r3, r1
	add r2, r1, #0x0
_0206E612:
	sub r6, r1, #0x4
	ldrh r6, [r6, #0x0]
	sub r5, r5, #0x1
	lsl r5, r5, #0x10
	strh r6, [r2, #0x0]
	sub r6, r1, #0x2
	ldrh r6, [r6, #0x0]
	asr r5, r5, #0x10
	sub r1, r1, #0x4
	strh r6, [r2, #0x2]
	sub r2, r2, #0x4
	cmp r5, r4
	bgt _0206E612
_0206E62C:
	lsl r4, r0, #0x2
	add r0, sp, #0x0
	ldrh r1, [r0, #0x0]
	add r2, r3, r4
	strh r1, [r3, r4]
	ldrh r0, [r0, #0x2]
	strh r0, [r2, #0x2]
_0206E63A:
	pop {r3-r6}
	bx lr
	.balign 4
