	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202A2C4
FUN_0202A2C4: ; 0x0202A2C4
	push {r4, lr}
	add r3, r0, #0x0
	cmp r1, #0xa
	bhi _0202A36A
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202A2D8: ; jump table (using 16-bit offset)
	.short _0202A2EE - _0202A2D8 - 2; case 0
	.short _0202A300 - _0202A2D8 - 2; case 1
	.short _0202A306 - _0202A2D8 - 2; case 2
	.short _0202A30C - _0202A2D8 - 2; case 3
	.short _0202A312 - _0202A2D8 - 2; case 4
	.short _0202A318 - _0202A2D8 - 2; case 5
	.short _0202A326 - _0202A2D8 - 2; case 6
	.short _0202A334 - _0202A2D8 - 2; case 7
	.short _0202A346 - _0202A2D8 - 2; case 8
	.short _0202A35A - _0202A2D8 - 2; case 9
	.short _0202A354 - _0202A2D8 - 2; case 10
_0202A2EE:
	ldrb r1, [r3, #0x0]
	mov r0, #0x1c
	bic r1, r0
	ldrb r0, [r2, #0x0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r3, #0x0]
	pop {r4, pc}
_0202A300:
	ldrb r0, [r2, #0x0]
	strb r0, [r3, #0x2]
	pop {r4, pc}
_0202A306:
	ldrb r0, [r2, #0x0]
	strb r0, [r3, #0x3]
	pop {r4, pc}
_0202A30C:
	ldrh r0, [r2, #0x0]
	strh r0, [r3, #0x4]
	pop {r4, pc}
_0202A312:
	ldrh r0, [r2, #0x0]
	strh r0, [r3, #0x6]
	pop {r4, pc}
_0202A318:
	add r3, #0x8
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0x4
	bl MI_CpuCopy8
	pop {r4, pc}
_0202A326:
	add r3, #0x2c
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0x10
	bl MI_CpuCopy8
	pop {r4, pc}
_0202A334:
	ldrb r4, [r3, #0x0]
	ldrb r1, [r2, #0x0]
	mov r0, #0x1
	bic r4, r0
	mov r0, #0x1
	and r0, r1
	orr r0, r4
	strb r0, [r3, #0x0]
	pop {r4, pc}
_0202A346:
	add r3, #0xc
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0x1c
	bl MI_CpuCopy8
	pop {r4, pc}
_0202A354:
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x28]
	pop {r4, pc}
_0202A35A:
	ldrb r1, [r3, #0x0]
	mov r0, #0xe0
	bic r1, r0
	ldrb r0, [r2, #0x0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r3, #0x0]
_0202A36A:
	pop {r4, pc}