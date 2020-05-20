    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206B688
FUN_0206B688: ; 0x0206B688
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02066A6C
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020672BC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020672BC
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0206B754
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_0206B6D4
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02066A94
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0206B6C8
FUN_0206B6C8: ; 0x0206B6C8
	push {r3, lr}
	bl FUN_020690E4
	bl FUN_0206B688
	pop {r3, pc}

	thumb_func_start FUN_0206B6D4
FUN_0206B6D4: ; 0x0206B6D4
	cmp r1, #0x1
	bne _0206B6E8
	ldr r1, _0206B748 ; =0x000001EA
	cmp r0, r1
	bne _0206B6E2
	add r1, #0xc
	b _0206B6E4
_0206B6E2:
	add r1, #0xb
_0206B6E4:
	add r0, r1, #0x0
	bx lr
_0206B6E8:
	cmp r2, #0x0
	beq _0206B73A
	ldr r3, _0206B74C ; =0x00000182
	cmp r0, r3
	bne _0206B6F8
	add r3, #0x74
	add r0, r2, r3
	bx lr
_0206B6F8:
	cmp r0, #0xc9
	bne _0206B702
	add r3, #0x78
	add r0, r2, r3
	bx lr
_0206B702:
	add r1, r3, #0x0
	add r1, #0x1a
	cmp r0, r1
	bne _0206B710
	add r3, #0x93
	add r0, r2, r3
	bx lr
_0206B710:
	add r1, r3, #0x0
	add r1, #0x1b
	cmp r0, r1
	bne _0206B71E
	add r3, #0x95
	add r0, r2, r3
	bx lr
_0206B71E:
	add r1, r3, #0x0
	add r1, #0x24
	cmp r0, r1
	bne _0206B72C
	add r3, #0x97
	add r0, r2, r3
	bx lr
_0206B72C:
	add r1, r3, #0x0
	add r1, #0x25
	cmp r0, r1
	bne _0206B73A
	add r3, #0x98
	add r0, r2, r3
	bx lr
_0206B73A:
	ldr r1, _0206B750 ; =0x000001ED
	cmp r0, r1
	bls _0206B742
	mov r0, #0x0
_0206B742:
	add r0, r0, #0x7
	bx lr
	nop
_0206B748: .word 0x000001EA
_0206B74C: .word 0x00000182
_0206B750: .word 0x000001ED

	thumb_func_start FUN_0206B754
FUN_0206B754: ; 0x0206B754
	push {r4, lr}
	mov r1, #0xad
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020672BC
	ldr r2, _0206B7B8 ; =0x0000019D
	cmp r0, r2
	bhi _0206B784
	sub r1, r2, #0x1
	cmp r0, r1
	blo _0206B774
	beq _0206B7A4
	cmp r0, r2
	beq _0206B7A4
	b _0206B7B4
_0206B774:
	cmp r0, #0xc9
	bhi _0206B77C
	beq _0206B79C
	b _0206B7B4
_0206B77C:
	sub r2, #0x1b
	cmp r0, r2
	beq _0206B7A4
	b _0206B7B4
_0206B784:
	add r1, r2, #0x0
	add r1, #0x9
	cmp r0, r1
	bhi _0206B794
	add r2, #0x9
	cmp r0, r2
	beq _0206B7A4
	b _0206B7B4
_0206B794:
	add r2, #0xa
	cmp r0, r2
	beq _0206B7A4
	b _0206B7B4
_0206B79C:
	add r0, r4, #0x0
	bl FUN_020690D4
	pop {r4, pc}
_0206B7A4:
	add r0, r4, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r4, pc}
_0206B7B4:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0206B7B8: .word 0x0000019D

	thumb_func_start FUN_0206B7BC
FUN_0206B7BC: ; 0x0206B7BC
	cmp r2, #0x1
	bne _0206B7CE
	ldr r1, _0206B830 ; =0x000001EA
	cmp r0, r1
	bne _0206B7CA
	add r0, r1, #0x5
	b _0206B82A
_0206B7CA:
	add r0, r1, #0x4
	b _0206B82A
_0206B7CE:
	ldr r3, _0206B834 ; =0x000001ED
	cmp r0, r3
	bls _0206B7D8
	mov r0, #0x0
	b _0206B82A
_0206B7D8:
	cmp r1, #0x0
	beq _0206B82A
	add r2, r3, #0x0
	sub r2, #0x6b
	cmp r0, r2
	bne _0206B7EA
	add r0, r3, #0x2
	add r0, r1, r0
	b _0206B82A
_0206B7EA:
	cmp r0, #0xc9
	bne _0206B7F4
	add r0, r3, #0x5
	add r0, r1, r0
	b _0206B82A
_0206B7F4:
	add r2, r3, #0x0
	sub r2, #0x51
	cmp r0, r2
	bne _0206B802
	add r3, #0x21
	add r0, r1, r3
	b _0206B82A
_0206B802:
	add r2, r3, #0x0
	sub r2, #0x50
	cmp r0, r2
	bne _0206B810
	add r3, #0x23
	add r0, r1, r3
	b _0206B82A
_0206B810:
	add r2, r3, #0x0
	sub r2, #0x47
	cmp r0, r2
	bne _0206B81E
	add r3, #0x25
	add r0, r1, r3
	b _0206B82A
_0206B81E:
	add r2, r3, #0x0
	sub r2, #0x46
	cmp r0, r2
	bne _0206B82A
	add r3, #0x26
	add r0, r1, r3
_0206B82A:
	ldr r1, _0206B838 ; =0x020F8074
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_0206B830: .word 0x000001EA
_0206B834: .word 0x000001ED
_0206B838: .word 0x020F8074

	thumb_func_start FUN_0206B83C
FUN_0206B83C: ; 0x0206B83C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02066A6C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0206B754
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020672BC
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020672BC
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02066A94
	ldr r2, [sp, #0x0]
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_0206B7BC
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206B87C
FUN_0206B87C: ; 0x0206B87C
	push {r3, lr}
	bl FUN_020690E4
	bl FUN_0206B83C
	pop {r3, pc}

	thumb_func_start FUN_0206B888
FUN_0206B888: ; 0x0206B888
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0206B88C
FUN_0206B88C: ; 0x0206B88C
	mov r0, #0x2
	bx lr

	thumb_func_start FUN_0206B890
FUN_0206B890: ; 0x0206B890
	mov r0, #0x4
	bx lr

	thumb_func_start FUN_0206B894
FUN_0206B894: ; 0x0206B894
	mov r0, #0x6
	bx lr

	thumb_func_start FUN_0206B898
FUN_0206B898: ; 0x0206B898
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0206B89C
FUN_0206B89C: ; 0x0206B89C
	mov r0, #0x3
	bx lr

	thumb_func_start FUN_0206B8A0
FUN_0206B8A0: ; 0x0206B8A0
	mov r0, #0x5
	bx lr
