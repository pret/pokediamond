	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E5564
MOD05_021E5564: ; 0x021E5564
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x60
	add r3, r2, #0
	add r5, r0, #0
	bl MOD05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl MOD05_021E5590
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E5580
MOD05_021E5580: ; 0x021E5580
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021E55B0
	add r0, r4, #0
	bl MOD05_021E4C00
	pop {r4, pc}

	thumb_func_start MOD05_021E5590
MOD05_021E5590: ; 0x021E5590
	push {r3, lr}
	sub sp, #8
	add r3, r0, #0
	add r0, #0x58
	str r0, [sp]
	add r0, r3, #0
	add r0, #0x5c
	str r0, [sp, #4]
	ldr r0, [r3]
	mov r1, #0x15
	mov r2, #0
	add r3, r3, #4
	bl MOD05_021E51EC
	add sp, #8
	pop {r3, pc}

	thumb_func_start MOD05_021E55B0
MOD05_021E55B0: ; 0x021E55B0
	ldr r3, _021E55B8 ; =MOD05_021E4C00
	ldr r0, [r0, #0x5c]
	bx r3
	nop
_021E55B8: .word MOD05_021E4C00
