	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start wcslen
wcslen: ; 0x020E701C
	mvn r2, #0x0
_020E7020:
	ldrh r1, [r0], #0x2
	add r2, r2, #0x1
	cmp r1, #0x0
	bne _020E7020
	mov r0, r2
	bx lr
	arm_func_end wcslen

	arm_func_start wcscpy
wcscpy: ; 0x020E7038
	mov r3, r0
_020E703C:
	ldrh r2, [r1], #0x2
	mov r12, r3
	strh r2, [r3], #0x2
	ldrh r2, [r12, #0x0]
	cmp r2, #0x0
	bne _020E703C
	bx lr
	arm_func_end wcscpy

	arm_func_start wcschr
wcschr: ; 0x020E7058
	ldrh r2, [r0], #0x2
	cmp r2, #0x0
	beq _020E707C
_020E7064:
	cmp r2, r1
	subeq r0, r0, #0x2
	bxeq lr
	ldrh r2, [r0], #0x2
	cmp r2, #0x0
	bne _020E7064
_020E707C:
	cmp r1, #0x0
	movne r0, #0x0
	subeq r0, r0, #0x2
	bx lr
	arm_func_end wcschr
