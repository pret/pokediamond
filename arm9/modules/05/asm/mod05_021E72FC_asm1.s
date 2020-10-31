	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	#in asm2
	.extern MOD05_021E73B4
	.extern MOD05_021E74D4

	thumb_func_start MOD05_021E72FC
MOD05_021E72FC: ; 0x021E72FC
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	bl FUN_020553A0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r4, #0
	bl FUN_02054B30
	cmp r0, #1
	bne _021E731E
	mov r2, #3
	b _021E734C
_021E731E:
	add r0, r4, #0
	bl FUN_02054B3C
	cmp r0, #1
	bne _021E732C
	mov r2, #2
	b _021E734C
_021E732C:
	add r0, r4, #0
	bl FUN_02054B48
	cmp r0, #1
	bne _021E733A
	mov r2, #0
	b _021E734C
_021E733A:
	add r0, r4, #0
	bl FUN_02054B54
	cmp r0, #1
	bne _021E7348
	mov r2, #1
	b _021E734C
_021E7348:
	mov r0, #0
	pop {r4, r5, r6, pc}
_021E734C:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD05_021E7358
	mov r0, #1
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021E7358
MOD05_021E7358: ; 0x021E7358
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0x18
	add r6, r1, #0
	add r7, r2, #0
	bl MOD05_021E74D4
	add r4, r0, #0
	str r5, [r4, #0xc]
	str r6, [r4, #0x10]
	ldr r0, _021E7380 ; =0x00000658
	str r7, [r4]
	bl FUN_020054C8
	ldr r1, _021E7384 ; =MOD05_021E73B4
	add r0, r5, #0
	add r2, r4, #0
	bl FUN_020463CC
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E7380: .word 0x00000658
_021E7384: .word MOD05_021E73B4
