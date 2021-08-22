	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021F5B9C
MOD05_021F5B9C: ; 0x021F5B9C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl FUN_02050DF0
	add r7, r0, #0
	beq _021F5C40
	bl MOD18_0223E2C4
	add r6, r0, #0
	bl MOD18_0223E2DC
	lsl r1, r6, #0x15
	lsl r0, r0, #0x15
	mov r4, #0
	str r1, [sp, #0xc]
	str r0, [sp, #8]
_021F5BC0:
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_020267C4
	add r6, r0, #0
	bl FUN_0204CA80
	str r0, [sp, #0x10]
	add r0, r6, #0
	bl FUN_0204CA90
	str r0, [sp, #0x14]
	cmp r6, #0
	beq _021F5C3A
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02026810
	str r0, [sp, #0x18]
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02026840
	mov r2, #1
	ldr r1, [sp, #0x18]
	lsl r2, r2, #0xc
	str r2, [sp, #0x20]
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	ldr r2, [sp, #0xc]
	str r1, [sp, #0x1c]
	add r1, r1, r2
	ldr r2, [sp, #8]
	str r0, [sp, #0x24]
	add r0, r0, r2
	ldr r2, [sp, #0x10]
	str r1, [sp, #0x1c]
	lsl r2, r2, #0xf
	add r1, r1, r2
	str r1, [sp, #0x1c]
	ldr r1, [sp, #0x14]
	str r0, [sp, #0x24]
	lsl r1, r1, #0xf
	add r0, r0, r1
	str r0, [sp, #0x24]
	ldr r0, [r5, #0x2c]
	add r1, r6, #0
	bl MOD05_021F4CD4
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5, #0x4c]
	add r3, sp, #0x1c
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	bl MOD05_021E7FBC
_021F5C3A:
	add r4, r4, #1
	cmp r4, #0x20
	blt _021F5BC0
_021F5C40:
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
