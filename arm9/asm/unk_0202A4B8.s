	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202A4B8
FUN_0202A4B8: ; 0x0202A4B8
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldrb r0, [r1, #0x2]
	mov r2, #0xfa
	lsl r2, r2, #0x2
	sub r0, r0, #0x1
	add r3, r0, #0x0
	mul r3, r2
	lsl r0, r3, #0x10
	lsr r4, r0, #0x10
	ldrh r3, [r1, #0x4]
	mov r0, #0xa
	ldrb r5, [r1, #0x3]
	mul r0, r3
	mov r3, #0x14
	mul r3, r5
	lsl r0, r0, #0x10
	lsl r3, r3, #0x10
	lsr r0, r0, #0x10
	lsr r3, r3, #0x10
	add r3, r0, r3
	add r0, r2, #0x0
	sub r0, #0x32
	cmp r3, r0
	ble _0202A4EE
	mov r5, #0x0
	b _0202A4F6
_0202A4EE:
	sub r2, #0x32
	sub r0, r2, r3
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_0202A4F6:
	ldrh r1, [r1, #0x6]
	ldr r0, _0202A51C ; =0x000003CA
	cmp r1, r0
	bls _0202A502
	mov r1, #0x0
	b _0202A510
_0202A502:
	add r0, #0x1e
	sub r0, r0, r1
	mov r1, #0x1e
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
_0202A510:
	add r0, r4, r5
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	strh r0, [r6, #0x16]
	pop {r4-r6, pc}
	.balign 4
_0202A51C: .word 0x000003CA

