	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202D858
FUN_0202D858: ; 0x0202D858
	push {r3-r4, lr}
	sub sp, #0x1c
	ldr r3, _0202D880 ; =0x020EEB04
	add r4, r0, #0x0
	add r2, sp, #0x0
	mov r1, #0x1a
_0202D864:
	ldrb r0, [r3, #0x0]
	add r3, r3, #0x1
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _0202D864
	cmp r4, #0x1a
	blo _0202D878
	bl ErrorHandling
_0202D878:
	add r0, sp, #0x0
	ldrb r0, [r0, r4]
	add sp, #0x1c
	pop {r3-r4, pc}
	.balign 4
_0202D880: .word 0x020EEB04

	thumb_func_start FUN_0202D884
FUN_0202D884: ; 0x0202D884
	push {r3-r4, lr}
	sub sp, #0x1c
	ldr r3, _0202D8AC ; =0x020EEB1E
	add r4, r0, #0x0
	add r2, sp, #0x0
	mov r1, #0x1a
_0202D890:
	ldrb r0, [r3, #0x0]
	add r3, r3, #0x1
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _0202D890
	cmp r4, #0x1a
	blo _0202D8A4
	bl ErrorHandling
_0202D8A4:
	add r0, sp, #0x0
	ldrb r0, [r0, r4]
	add sp, #0x1c
	pop {r3-r4, pc}
	.balign 4
_0202D8AC: .word 0x020EEB1E

	thumb_func_start FUN_0202D8B0
FUN_0202D8B0: ; 0x0202D8B0
	cmp r0, #0xd
	bgt _0202D8C4
	cmp r0, #0x7
	blt _0202D8CC
	beq _0202D8C8
	cmp r0, #0x9
	beq _0202D8C8
	cmp r0, #0xd
	beq _0202D8C8
	b _0202D8CC
_0202D8C4:
	cmp r0, #0x12
	bne _0202D8CC
_0202D8C8:
	mov r0, #0x1
	bx lr
_0202D8CC:
	mov r0, #0x0
	bx lr
