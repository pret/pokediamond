    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0205363C
FUN_0205363C: ; 0x0205363C
	push {r3-r7, lr}
	add r7, r2, #0x0
	lsl r0, r0, #0x1d
	ldr r2, _02053670 ; =0x020F5AC4
	lsr r0, r0, #0x19
	add r5, r2, r0
	lsl r2, r1, #0x3
	mov r1, #0xc
	ldr r0, _02053674 ; =0x020F5B44
	mul r1, r2
	mov r4, #0x0
	add r6, r0, r1
_02053654:
	ldr r3, [r5, #0x0]
	mov r2, #0xc
	mul r2, r3
	add r2, r6, r2
	ldr r2, [r2, #0x4]
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_0200B064
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blt _02053654
	pop {r3-r7, pc}
	.balign 4
_02053670: .word 0x020F5AC4
_02053674: .word 0x020F5B44

	thumb_func_start FUN_02053678
FUN_02053678: ; 0x02053678
	lsl r0, r0, #0x1d
	lsr r3, r0, #0x19
	ldr r0, _02053694 ; =0x020F5AC4
	lsl r2, r2, #0x2
	add r0, r0, r3
	ldr r0, [r2, r0]
	lsl r1, r1, #0x3
	add r1, r1, r0
	mov r0, #0xc
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, _02053698 ; =0x020F5B44
	ldr r0, [r0, r2]
	bx lr
	.balign 4
_02053694: .word 0x020F5AC4
_02053698: .word 0x020F5B44

	thumb_func_start FUN_0205369C
FUN_0205369C: ; 0x0205369C
	push {r3-r4}
	lsl r4, r0, #0x3
	mov r0, #0xc
	ldr r2, _020536C4 ; =0x020F5B44
	mul r0, r4
	mov r3, #0x0
	add r2, r2, r0
_020536AA:
	ldr r0, [r2, #0x0]
	cmp r1, r0
	bne _020536B6
	add r0, r3, r4
	pop {r3-r4}
	bx lr
_020536B6:
	add r3, r3, #0x1
	add r2, #0xc
	cmp r3, #0x8
	blt _020536AA
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4
_020536C4: .word 0x020F5B44

	thumb_func_start FUN_020536C8
FUN_020536C8: ; 0x020536C8
	ldr r3, _020536CC ; =FUN_0205369C
	bx r3
	.balign 4
_020536CC: .word FUN_0205369C

	thumb_func_start FUN_020536D0
FUN_020536D0: ; 0x020536D0
	push {r4, lr}
	add r4, r2, #0x0
	bl FUN_0205369C
	cmp r4, #0x0
	beq _020536FE
	cmp r4, #0x1
	beq _020536EE
	cmp r4, #0x2
	bne _020536F8
	mov r1, #0xc
	mul r1, r0
	ldr r0, _02053700 ; =0x020F5B48
	ldr r0, [r0, r1]
	pop {r4, pc}
_020536EE:
	mov r1, #0xc
	mul r1, r0
	ldr r0, _02053704 ; =0x020F5B4C
	ldr r0, [r0, r1]
	pop {r4, pc}
_020536F8:
	bl ErrorHandling
	mov r0, #0x0
_020536FE:
	pop {r4, pc}
	.balign 4
_02053700: .word 0x020F5B48
_02053704: .word 0x020F5B4C

	thumb_func_start FUN_02053708
FUN_02053708: ; 0x02053708
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	mov r0, #0x56
	mov r1, #0x7
	add r2, sp, #0x0
	add r3, r5, #0x0
	bl FUN_02006C08
	mov r1, #0x9
	add r4, r0, #0x0
	add r0, r5, #0x0
	lsl r1, r1, #0x6
	bl FUN_02016998
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	ldr r3, [r0, #0xc]
	mov r0, #0x1
	add r6, r5, #0x0
	lsl r0, r0, #0x8
_02053734:
	ldrh r1, [r3, #0x0]
	add r2, r2, #0x1
	add r3, r3, #0x2
	strh r1, [r6, #0x0]
	add r6, r6, #0x2
	cmp r2, r0
	blt _02053734
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
