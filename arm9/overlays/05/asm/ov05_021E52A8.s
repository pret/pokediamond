	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021E52A8
ov05_021E52A8: ; 0x021E52A8
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x60
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov05_021E52D4
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E52C4
ov05_021E52C4: ; 0x021E52C4
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021E52F4
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov05_021E52D4
ov05_021E52D4: ; 0x021E52D4
	push {r3, lr}
	sub sp, #8
	add r3, r0, #0
	add r0, #0x58
	str r0, [sp]
	add r0, r3, #0
	add r0, #0x5c
	str r0, [sp, #4]
	ldr r0, [r3]
	mov r1, #0x11
	mov r2, #0
	add r3, r3, #4
	bl ov05_021E51EC
	add sp, #8
	pop {r3, pc}

	thumb_func_start ov05_021E52F4
ov05_021E52F4: ; 0x021E52F4
	ldr r3, _021E52FC ; =ov05_021E4C00
	ldr r0, [r0, #0x5c]
	bx r3
	nop
_021E52FC: .word ov05_021E4C00
