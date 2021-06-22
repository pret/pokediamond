	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_0201C6B4
FUN_0201C6B4: ; 0x0201C6B4
	mov r2, #0x0
	ldrsb r1, [r0, r2]
	cmp r1, #0x0
	beq _0201C6C4
_0201C6BC:
	add r2, r2, #0x1
	ldrsb r1, [r0, r2]
	cmp r1, #0x0
	bne _0201C6BC
_0201C6C4:
	add r0, r2, #0x0
	bx lr

	thumb_func_start FUN_0201C6C8
FUN_0201C6C8: ; 0x0201C6C8
	push {r4-r5}
	mov r4, #0x1
	mov r3, #0x0
	lsl r4, r4, #0x8
_0201C6D0:
	ldrsb r5, [r0, r3]
	strb r5, [r1, r3]
	ldrsb r5, [r0, r3]
	cmp r2, r5
	beq _0201C6DE
	cmp r5, #0x0
	bne _0201C6FE
_0201C6DE:
	mov r4, #0x0
	strb r4, [r1, r3]
	cmp r2, #0xd
	bne _0201C6F6
	add r1, r3, #0x1
	ldrsb r1, [r0, r1]
	cmp r1, #0xa
	bne _0201C6F6
	add r1, r3, #0x2
	add r0, r0, r1
	pop {r4-r5}
	bx lr
_0201C6F6:
	add r1, r3, #0x1
	add r0, r0, r1
	pop {r4-r5}
	bx lr
_0201C6FE:
	add r3, r3, #0x1
	cmp r3, r4
	blt _0201C6D0
	mov r0, #0x0
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_0201C70C
FUN_0201C70C: ; 0x0201C70C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl FUN_0201C6B4
	mov r5, #0x1
	mov r6, #0x0
	sub r3, r0, #0x1
	bmi _0201C74A
	sub r1, r6, #0x1
	mov r0, #0xa
_0201C720:
	ldrsb r2, [r4, r3]
	cmp r2, #0x30
	blt _0201C732
	cmp r2, #0x39
	bgt _0201C732
	sub r2, #0x30
	mul r2, r5
	add r6, r6, r2
	b _0201C744
_0201C732:
	cmp r3, #0x0
	bne _0201C73E
	cmp r2, #0x2d
	bne _0201C744
	mul r6, r1
	b _0201C744
_0201C73E:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_0201C744:
	mul r5, r0
	sub r3, r3, #0x1
	bpl _0201C720
_0201C74A:
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0201C750
FUN_0201C750: ; 0x0201C750
	push {r3-r5, lr}
	mov r2, #0x0
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r1, r2, #0x0
_0201C75A:
	lsl r0, r2, #0x2
	str r1, [r5, r0]
	add r0, r2, #0x1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, #0x4
	blo _0201C75A
	add r0, r4, #0x0
	bl FUN_0201C6B4
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r2, _0201C788 ; =0x00000000
	beq _0201C784
_0201C776:
	ldrsb r0, [r4, r2]
	strb r0, [r5, r2]
	add r0, r2, #0x1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, r1
	blo _0201C776
_0201C784:
	pop {r3-r5, pc}
	nop
_0201C788: .word 0x00000000

	thumb_func_start FUN_0201C78C
FUN_0201C78C: ; 0x0201C78C
	ldr r1, _0201C79C ; =0x00000121
	cmp r0, r1
	bhs _0201C796
	mov r0, #0x1
	bx lr
_0201C796:
	mov r0, #0x0
	bx lr
	nop
_0201C79C: .word 0x00000121
