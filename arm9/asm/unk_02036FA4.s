	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_02036FA4
FUN_02036FA4: ; 0x02036FA4
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x38]
	add r4, r1, #0x0
	add r5, r2, #0x0
	bl PlayerAvatar_GetFacingDirection
	add r7, r0, #0x0
	ldr r0, [r6, #0x38]
	bl GetPlayerXCoord
	str r0, [r4, #0x0]
	ldr r0, [r6, #0x38]
	bl FUN_0205532C
	str r0, [r5, #0x0]
	cmp r7, #0x3
	bhi _02036FFA
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02036FD4: ; jump table (using 16-bit offset)
	.short _02036FDC - _02036FD4 - 2; case 0
	.short _02036FE4 - _02036FD4 - 2; case 1
	.short _02036FEC - _02036FD4 - 2; case 2
	.short _02036FF4 - _02036FD4 - 2; case 3
_02036FDC:
	ldr r0, [r5, #0x0]
	sub r0, r0, #0x1
	str r0, [r5, #0x0]
	b _02036FFA
_02036FE4:
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _02036FFA
_02036FEC:
	ldr r0, [r4, #0x0]
	sub r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02036FFA
_02036FF4:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
_02036FFA:
	add r0, r7, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02037000
FUN_02037000: ; 0x02037000
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl FUN_020553A0
	bl FUN_02058BE4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058BE4
	cmp r4, r0
	bne _0203701C
	mov r0, #0x1
	b _0203701E
_0203701C:
	mov r0, #0x0
_0203701E:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3-r5, pc}
