    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020FD120
UNK_020FD120: ; 0x020FD120
	.byte 0x17, 0x00, 0x19, 0x00, 0x36, 0x00, 0x4D, 0x00, 0x78, 0x00, 0x81, 0x00, 0xCA, 0x00, 0xD6, 0x00
	.byte 0xD7, 0x00, 0xD8, 0x00, 0xE4, 0x00, 0x16, 0x01, 0x1F, 0x01, 0x3B, 0x01

	.global UNK_020FD13C
UNK_020FD13C: ; 0x020FD13C
	.byte 0x01, 0x02, 0x03, 0x05, 0x04, 0x07

	.text

	thumb_func_start FUN_02087A1C
FUN_02087A1C: ; 0x02087A1C
	ldr r3, _02087A34 ; =UNK_020FD13C
	mov r2, #0x0
_02087A20:
	ldrb r1, [r3, #0x0]
	cmp r0, r1
	beq _02087A2E
	add r2, r2, #0x1
	add r3, r3, #0x1
	cmp r2, #0x6
	blt _02087A20
_02087A2E:
	add r0, r2, #0x0
	bx lr
	nop
_02087A34: .word UNK_020FD13C

	thumb_func_start FUN_02087A38
FUN_02087A38: ; 0x02087A38
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x6
	blt _02087A44
	bl ErrorHandling
_02087A44:
	ldr r0, _02087A4C ; =UNK_020FD13C
	ldrb r0, [r0, r4]
	pop {r4, pc}
	nop
_02087A4C: .word UNK_020FD13C

	thumb_func_start FUN_02087A50
FUN_02087A50: ; 0x02087A50
	ldr r3, _02087A68 ; =UNK_020FD120
	mov r2, #0x0
_02087A54:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	beq _02087A62
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0xe
	blt _02087A54
_02087A62:
	add r0, r2, #0x0
	bx lr
	nop
_02087A68: .word UNK_020FD120
