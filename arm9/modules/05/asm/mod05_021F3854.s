	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021F3854
MOD05_021F3854: ; 0x021F3854
	mov r0, #0
	str r0, [r2]
	str r0, [r2, #4]
	bx lr

	thumb_func_start MOD05_021F385C
MOD05_021F385C: ; 0x021F385C
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F3860
MOD05_021F3860: ; 0x021F3860
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x38]
	add r4, r2, #0
	bl FUN_02055320
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	add r7, r0, #0
	ldr r0, [r4]
	cmp r0, r6
	bne _021F3882
	ldr r0, [r4, #4]
	cmp r0, r7
	beq _021F38B4
_021F3882:
	str r6, [r4]
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	str r7, [r4, #4]
	bl FUN_0204A6E0
	add r4, r0, #0
	bl FUN_02054A18
	cmp r0, #0
	beq _021F389E
	mov r2, #0
	b _021F38AA
_021F389E:
	add r0, r4, #0
	bl FUN_02054A0C
	cmp r0, #0
	beq _021F38B4
	mov r2, #1
_021F38AA:
	add r0, r6, #0
	add r1, r7, #0
	add r3, r5, #0
	bl MOD05_021DAFA8
_021F38B4:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F38B8
MOD05_021F38B8: ; 0x021F38B8
	ldr r0, [r0, #4]
	ldr r3, _021F38C4 ; =MOD05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _021F38C8 ; =UNK05_021FC58C
	bx r3
	nop
_021F38C4: .word MOD05_021D8024
_021F38C8: .word UNK05_021FC58C

	.section .rodata

	.global UNK05_021FC58C
UNK05_021FC58C: ; 0x021FC58C
	.word 0x00000002, 0x00000008, MOD05_021F3854, MOD05_021F385C
	.word MOD05_021F3860, 0x00000000
