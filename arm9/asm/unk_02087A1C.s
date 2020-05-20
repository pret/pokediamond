    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02087A1C
FUN_02087A1C: ; 0x02087A1C
	ldr r3, _02087A34 ; =0x020FD13C
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
_02087A34: .word 0x020FD13C

	thumb_func_start FUN_02087A38
FUN_02087A38: ; 0x02087A38
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x6
	blt _02087A44
	bl ErrorHandling
_02087A44:
	ldr r0, _02087A4C ; =0x020FD13C
	ldrb r0, [r0, r4]
	pop {r4, pc}
	nop
_02087A4C: .word 0x020FD13C

	thumb_func_start FUN_02087A50
FUN_02087A50: ; 0x02087A50
	ldr r3, _02087A68 ; =0x020FD120
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
_02087A68: .word 0x020FD120
