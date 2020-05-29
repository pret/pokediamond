    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206B8A4
FUN_0206B8A4: ; 0x0206B8A4
	mov r0, #0x59
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_0206B8AC
FUN_0206B8AC: ; 0x0206B8AC
	push {r4, lr}
	mov r1, #0x59
	lsl r1, r1, #0x4
	bl AllocFromHeap
	add r4, r0, #0x0
	bl FUN_0206B8C0
	add r0, r4, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0206B8C0
FUN_0206B8C0: ; 0x0206B8C0
	ldr r3, _0206B8C8 ; =FUN_0206B8CC
	mov r1, #0x6
	bx r3
	nop
_0206B8C8: .word FUN_0206B8CC

	thumb_func_start FUN_0206B8CC
FUN_0206B8CC: ; 0x0206B8CC
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	cmp r6, #0x6
	ble _0206B8DA
	bl ErrorHandling
_0206B8DA:
	mov r2, #0x59
	add r0, r5, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl memset
	mov r4, #0x0
	str r4, [r5, #0x4]
	str r6, [r5, #0x0]
	add r5, #0x8
_0206B8EE:
	add r0, r5, #0x0
	bl FUN_02066978
	add r4, r4, #0x1
	add r5, #0xec
	cmp r4, #0x6
	blt _0206B8EE
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0206B900
FUN_0206B900: ; 0x0206B900
	push {r4-r5}
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldr r1, [r3, #0x4]
	ldr r0, [r3, #0x0]
	cmp r1, r0
	blt _0206B914
	mov r0, #0x0
	pop {r4-r5}
	bx lr
_0206B914:
	mov r0, #0xec
	mul r0, r1
	add r5, r3, r0
	add r5, #0x8
	mov r4, #0x1d
_0206B91E:
	ldmia r2!, {r0-r1}
	stmia r5!, {r0-r1}
	sub r4, r4, #0x1
	bne _0206B91E
	ldr r0, [r2, #0x0]
	str r0, [r5, #0x0]
	ldr r0, [r3, #0x4]
	add r0, r0, #0x1
	str r0, [r3, #0x4]
	mov r0, #0x1
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_0206B938
FUN_0206B938: ; 0x0206B938
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r4, r1, #0x0
	bpl _0206B944
	bl ErrorHandling
_0206B944:
	ldr r0, [r7, #0x4]
	cmp r4, r0
	blt _0206B94E
	bl ErrorHandling
_0206B94E:
	ldr r0, [r7, #0x0]
	cmp r4, r0
	blt _0206B958
	bl ErrorHandling
_0206B958:
	ldr r0, [r7, #0x4]
	cmp r0, #0x0
	bgt _0206B962
	bl ErrorHandling
_0206B962:
	ldr r0, [r7, #0x4]
	sub r0, r0, #0x1
	cmp r4, r0
	bge _0206B992
	mov r0, #0xec
	mul r0, r4
	add r6, r7, r0
_0206B970:
	add r5, r6, #0x0
	add r3, r6, #0x0
	add r5, #0xf4
	add r3, #0x8
	mov r2, #0x1d
_0206B97A:
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0206B97A
	ldr r0, [r5, #0x0]
	add r4, r4, #0x1
	str r0, [r3, #0x0]
	ldr r0, [r7, #0x4]
	add r6, #0xec
	sub r0, r0, #0x1
	cmp r4, r0
	blt _0206B970
_0206B992:
	add r1, r7, #0x0
	mov r0, #0xec
	add r1, #0x8
	mul r0, r4
	add r0, r1, r0
	bl FUN_02066978
	ldr r0, [r7, #0x4]
	sub r0, r0, #0x1
	str r0, [r7, #0x4]
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206B9AC
FUN_0206B9AC: ; 0x0206B9AC
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0206B9B0
FUN_0206B9B0: ; 0x0206B9B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bpl _0206B9BC
	bl ErrorHandling
_0206B9BC:
	ldr r0, [r5, #0x4]
	cmp r4, r0
	blt _0206B9C6
	bl ErrorHandling
_0206B9C6:
	ldr r0, [r5, #0x0]
	cmp r4, r0
	blt _0206B9D0
	bl ErrorHandling
_0206B9D0:
	mov r0, #0xec
	add r5, #0x8
	mul r0, r4
	add r0, r5, r0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0206B9DC
FUN_0206B9DC: ; 0x0206B9DC
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x0
	bge _0206B9EC
	bl ErrorHandling
_0206B9EC:
	ldr r0, [r5, #0x4]
	cmp r4, r0
	blt _0206B9F6
	bl ErrorHandling
_0206B9F6:
	ldr r0, [r5, #0x0]
	cmp r4, r0
	blt _0206BA00
	bl ErrorHandling
_0206BA00:
	add r1, r5, #0x0
	mov r0, #0xec
	add r1, #0x8
	mul r0, r4
	add r4, r1, r0
	add r0, r4, #0x0
	mov r1, #0xab
	mov r2, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0xab
	mov r2, #0x0
	bl FUN_020671BC
	sub r2, r7, r0
	mov r3, #0x1d
_0206BA24:
	ldmia r6!, {r0-r1}
	stmia r4!, {r0-r1}
	sub r3, r3, #0x1
	bne _0206BA24
	ldr r0, [r6, #0x0]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x4]
	add r0, r0, r2
	str r0, [r5, #0x4]
	pop {r3-r7, pc}

	thumb_func_start FUN_0206BA38
FUN_0206BA38: ; 0x0206BA38
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	add r6, r2, #0x0
	cmp r5, #0x0
	bge _0206BA48
	bl ErrorHandling
_0206BA48:
	ldr r0, [r4, #0x4]
	cmp r5, r0
	blt _0206BA52
	bl ErrorHandling
_0206BA52:
	ldr r0, [r4, #0x0]
	cmp r5, r0
	blt _0206BA5C
	bl ErrorHandling
_0206BA5C:
	cmp r6, #0x0
	bge _0206BA64
	bl ErrorHandling
_0206BA64:
	ldr r0, [r4, #0x4]
	cmp r6, r0
	blt _0206BA6E
	bl ErrorHandling
_0206BA6E:
	ldr r0, [r4, #0x0]
	cmp r6, r0
	blt _0206BA78
	bl ErrorHandling
_0206BA78:
	mov r0, #0x0
	mov r1, #0xec
	bl AllocFromHeap
	mov r12, r0
	add r1, r4, #0x0
	mov r0, #0xec
	add r1, #0x8
	mul r0, r5
	add r3, r1, r0
	add r5, r3, #0x0
	mov r2, r12
	mov r7, #0x1d
_0206BA92:
	ldmia r5!, {r0-r1}
	stmia r2!, {r0-r1}
	sub r7, r7, #0x1
	bne _0206BA92
	ldr r0, [r5, #0x0]
	add r4, #0x8
	str r0, [r2, #0x0]
	mov r0, #0xec
	mul r0, r6
	add r2, r4, r0
	add r5, r2, #0x0
	mov r4, #0x1d
_0206BAAA:
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r4, r4, #0x1
	bne _0206BAAA
	ldr r0, [r5, #0x0]
	mov r4, r12
	str r0, [r3, #0x0]
	mov r3, #0x1d
_0206BABA:
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	sub r3, r3, #0x1
	bne _0206BABA
	ldr r0, [r4, #0x0]
	str r0, [r2, #0x0]
	mov r0, r12
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0206BAD0
FUN_0206BAD0: ; 0x0206BAD0
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0xb2
_0206BAD8:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0206BAD8
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0206BAE4
FUN_0206BAE4: ; 0x0206BAE4
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x4]
	add r7, r1, #0x0
	mov r4, #0x0
	cmp r0, #0x0
	ble _0206BB0E
	add r5, r6, #0x0
	add r5, #0x8
_0206BAF6:
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	cmp r7, r0
	beq _0206BB0E
	ldr r0, [r6, #0x4]
	add r4, r4, #0x1
	add r5, #0xec
	cmp r4, r0
	blt _0206BAF6
_0206BB0E:
	ldr r0, [r6, #0x4]
	cmp r4, r0
	beq _0206BB18
	mov r0, #0x1
	pop {r3-r7, pc}
_0206BB18:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0206BB1C
FUN_0206BB1C: ; 0x0206BB1C
	ldr r3, _0206BB24 ; =FUN_02022610
	mov r1, #0x2
	bx r3
	nop
_0206BB24: .word FUN_02022610
