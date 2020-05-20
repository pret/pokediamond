	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02029EC4
FUN_02029EC4: ; 0x02029EC4
	mov r0, #0xfb
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_02029ECC
FUN_02029ECC: ; 0x02029ECC
	push {r4, lr}
	add r4, r0, #0x0
	mov r2, #0xfb
	mov r0, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	bl MIi_CpuClear32
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02029EE4
FUN_02029EE4: ; 0x02029EE4
	push {r4, lr}
	mov r1, #0xfb
	lsl r1, r1, #0x2
	bl FUN_02016998
	add r4, r0, #0x0
	bl FUN_02029ECC
	add r0, r4, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02029EF8
FUN_02029EF8: ; 0x02029EF8
	ldr r3, _02029F00 ; =FUN_02022610
	mov r1, #0x16
	bx r3
	nop
_02029F00: .word FUN_02022610

	thumb_func_start FUN_02029F04
FUN_02029F04: ; 0x02029F04
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02029F08
FUN_02029F08: ; 0x02029F08
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02029F10
FUN_02029F10: ; 0x02029F10
	add r0, r0, #0x4
	bx lr

	thumb_func_start FUN_02029F14
FUN_02029F14: ; 0x02029F14
	push {r4-r7}
	mov r5, #0x0
	mov r2, #0xfa
	add r4, r5, #0x0
	mov r6, #0xf
	lsl r2, r2, #0x2
_02029F20:
	ldrsb r7, [r1, r4]
	add r3, r0, r5
	and r7, r6
	lsl r7, r7, #0x18
	lsr r7, r7, #0x18
	sub r7, #0x8
	lsl r7, r7, #0x18
	asr r7, r7, #0x14
	strb r7, [r0, r5]
	ldrsb r7, [r1, r4]
	add r4, r4, #0x1
	add r5, r5, #0x2
	lsl r7, r7, #0x14
	lsr r7, r7, #0x18
	sub r7, #0x8
	lsl r7, r7, #0x18
	asr r7, r7, #0x14
	strb r7, [r3, #0x1]
	cmp r4, r2
	blt _02029F20
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_02029F4C
FUN_02029F4C: ; 0x02029F4C
	push {r4-r7}
	add r3, r0, #0x0
	add r2, r1, #0x0
	mov r0, #0x1
	mov r1, #0x0
	str r0, [r3, #0x0]
	add r0, r1, #0x0
_02029F5A:
	ldrsb r4, [r2, r0]
	add r6, r3, r1
	add r7, r2, r0
	asr r5, r4, #0x3
	lsr r5, r5, #0x1c
	add r5, r4, r5
	lsl r4, r5, #0x14
	asr r4, r4, #0x18
	add r4, #0x8
	strb r4, [r6, #0x4]
	mov r4, #0x4
	ldrsb r5, [r6, r4]
	mov r4, #0x1
	ldrsb r4, [r7, r4]
	add r0, r0, #0x2
	add r1, r1, #0x1
	asr r7, r4, #0x3
	lsr r7, r7, #0x1c
	add r7, r4, r7
	lsl r4, r7, #0x14
	asr r4, r4, #0x18
	add r4, #0x8
	lsl r4, r4, #0x18
	lsr r4, r4, #0x14
	orr r4, r5
	strb r4, [r6, #0x4]
	mov r4, #0x7d
	lsl r4, r4, #0x4
	cmp r0, r4
	blt _02029F5A
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_02029F9C
FUN_02029F9C: ; 0x02029F9C
	add r2, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	mov r2, #0xfb
	ldr r3, _02029FAC ; =MIi_CpuCopyFast
	lsl r2, r2, #0x2
	bx r3
	nop
_02029FAC: .word MIi_CpuCopyFast
