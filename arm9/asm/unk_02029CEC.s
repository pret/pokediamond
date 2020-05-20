	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02029CEC
FUN_02029CEC: ; 0x02029CEC
	mov r1, #0x12
	lsl r1, r1, #0x4
	add r0, r0, r1
	bx lr

	thumb_func_start FUN_02029CF4
FUN_02029CF4: ; 0x02029CF4
	ldrb r0, [r0, r1]
	bx lr

	thumb_func_start FUN_02029CF8
FUN_02029CF8: ; 0x02029CF8
	mov r3, #0x0
	add r2, r1, #0x1
_02029CFC:
	ldrb r1, [r0, #0x0]
	cmp r2, r1
	bne _02029D06
	mov r0, #0x1
	bx lr
_02029D06:
	add r3, r3, #0x1
	add r0, r0, #0x3
	cmp r3, #0x8
	blt _02029CFC
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02029D14
FUN_02029D14: ; 0x02029D14
	push {r4-r7}
	mov r6, #0x0
	add r4, r6, #0x0
	add r2, r1, #0x1
	add r3, r6, #0x0
_02029D1E:
	add r5, r3, #0x0
	add r7, r0, #0x0
_02029D22:
	ldrb r1, [r7, #0x0]
	cmp r2, r1
	bne _02029D2A
	add r6, r6, #0x1
_02029D2A:
	add r5, r5, #0x1
	add r7, r7, #0x3
	cmp r5, #0x8
	blt _02029D22
	add r4, r4, #0x1
	add r0, #0x18
	cmp r4, #0xc
	blt _02029D1E
	add r0, r6, #0x0
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_02029D40
FUN_02029D40: ; 0x02029D40
	strb r2, [r0, r1]
	bx lr

	thumb_func_start FUN_02029D44
FUN_02029D44: ; 0x02029D44
	push {r4-r6, lr}
	add r5, r1, #0x0
	sub r1, r5, #0x1
	add r6, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02029D14
	mov r1, #0x12
	lsl r1, r1, #0x4
	add r2, r6, r1
	sub r1, r5, #0x1
	ldrb r3, [r2, r1]
	add r0, r0, r3
	cmp r4, #0x0
	bge _02029D6E
	add r0, r4, r3
	bmi _02029D6A
	strb r0, [r2, r1]
	b _02029D7E
_02029D6A:
	mov r0, #0x0
	pop {r4-r6, pc}
_02029D6E:
	add r0, r0, r4
	cmp r0, #0x63
	bgt _02029D7A
	add r0, r3, r4
	strb r0, [r2, r1]
	b _02029D7E
_02029D7A:
	mov r0, #0x0
	pop {r4-r6, pc}
_02029D7E:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02029D84
FUN_02029D84: ; 0x02029D84
	push {r4-r6, lr}
	add r5, r1, #0x0
	sub r1, r5, #0x1
	add r6, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02029D14
	cmp r4, #0x0
	bge _02029DAC
	mov r0, #0x12
	lsl r0, r0, #0x4
	add r2, r6, r0
	sub r1, r5, #0x1
	ldrb r0, [r2, r1]
	add r0, r4, r0
	bmi _02029DA8
	strb r0, [r2, r1]
	b _02029DD0
_02029DA8:
	mov r0, #0x0
	pop {r4-r6, pc}
_02029DAC:
	add r0, r0, r4
	cmp r0, #0x63
	bgt _02029DCC
	mov r0, #0x12
	lsl r0, r0, #0x4
	add r2, r6, r0
	sub r1, r5, #0x1
	ldrb r0, [r2, r1]
	add r0, r0, r4
	strb r0, [r2, r1]
	ldrb r0, [r2, r1]
	cmp r0, #0x63
	blo _02029DD0
	mov r0, #0x63
	strb r0, [r2, r1]
	b _02029DD0
_02029DCC:
	mov r0, #0x0
	pop {r4-r6, pc}
_02029DD0:
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_02029DD4
FUN_02029DD4: ; 0x02029DD4
	push {r4-r6, lr}
	add r5, r1, #0x0
	sub r1, r5, #0x1
	add r6, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02029D14
	sub r1, r5, #0x1
	add r2, r6, r1
	mov r1, #0x12
	lsl r1, r1, #0x4
	ldrb r1, [r2, r1]
	add r0, r0, r1
	cmp r4, #0x0
	bge _02029DFE
	add r0, r4, r1
	bmi _02029DFA
	mov r0, #0x1
	pop {r4-r6, pc}
_02029DFA:
	mov r0, #0x0
	pop {r4-r6, pc}
_02029DFE:
	add r0, r0, r4
	cmp r0, #0x63
	bgt _02029E08
	mov r0, #0x1
	pop {r4-r6, pc}
_02029E08:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02029E0C
FUN_02029E0C: ; 0x02029E0C
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r5, #0x0
	mov r4, #0x1
_02029E14:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02029E2C
	cmp r0, #0x0
	beq _02029E22
	add r5, r5, #0x1
_02029E22:
	add r4, r4, #0x1
	cmp r4, #0x51
	blt _02029E14
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02029E2C
FUN_02029E2C: ; 0x02029E2C
	push {r3-r5, lr}
	add r5, r1, #0x0
	sub r1, r5, #0x1
	add r4, r0, #0x0
	bl FUN_02029D14
	sub r1, r5, #0x1
	add r2, r4, r1
	mov r1, #0x12
	lsl r1, r1, #0x4
	ldrb r1, [r2, r1]
	add r0, r0, r1
	pop {r3-r5, pc}
	.balign 4
