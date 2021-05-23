	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020C3D9C
FUN_020C3D9C: ; 0x020C3D9C
	cmp r1, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r2, [r0, #0x1c]
	cmp r1, r2
	movcs r0, #0x0
	bxcs lr
	mov r2, #0xc
	mul r2, r1, r2
	add r3, r0, #0x20
	ldr r1, [r3, r2]
	mvn r0, #0x0
	cmp r1, r0
	add r0, r3, r2
	moveq r0, #0x0
	bx lr

