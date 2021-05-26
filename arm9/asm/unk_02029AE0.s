	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02029AE0
FUN_02029AE0: ; 0x02029AE0
	ldr r0, _02029AE4 ; =0x00000FF8
	bx lr
	.balign 4
_02029AE4: .word 0x00000FF8

	thumb_func_start FUN_02029AE8
FUN_02029AE8: ; 0x02029AE8
	ldr r3, _02029AF4 ; =MIi_CpuClear32
	add r1, r0, #0x0
	mov r0, #0x0
	ldr r2, _02029AF8 ; =0x00000FF8
	bx r3
	nop
_02029AF4: .word MIi_CpuClear32
_02029AF8: .word 0x00000FF8

	thumb_func_start FUN_02029AFC
FUN_02029AFC: ; 0x02029AFC
	ldr r3, _02029B04 ; =SavArray_get
	mov r1, #0x1e
	bx r3
	nop
_02029B04: .word SavArray_get

	thumb_func_start FUN_02029B08
FUN_02029B08: ; 0x02029B08
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r0, #0x1
	add r5, r1, #0x0
	lsl r0, r0, #0x8
	add r4, r2, #0x0
	cmp r5, r0
	blt _02029B1C
	bl GF_AssertFail
_02029B1C:
	cmp r4, #0x40
	blt _02029B24
	bl GF_AssertFail
_02029B24:
	strb r5, [r6, #0x5]
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x3
	strb r4, [r6, #0x6]
	bl FUN_02029B90
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02029B38
FUN_02029B38: ; 0x02029B38
	ldrb r0, [r0, #0x5]
	bx lr

	thumb_func_start FUN_02029B3C
FUN_02029B3C: ; 0x02029B3C
	ldrb r0, [r0, #0x6]
	bx lr

	thumb_func_start FUN_02029B40
FUN_02029B40: ; 0x02029B40
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r0, #0x1
	add r5, r1, #0x0
	lsl r0, r0, #0x8
	add r4, r2, #0x0
	cmp r5, r0
	blt _02029B54
	bl GF_AssertFail
_02029B54:
	cmp r4, #0x40
	blt _02029B5C
	bl GF_AssertFail
_02029B5C:
	cmp r5, #0x0
	bne _02029B64
	mov r0, #0x0
	pop {r4-r6, pc}
_02029B64:
	asr r0, r4, #0x1
	lsr r0, r0, #0x1e
	add r0, r4, r0
	asr r1, r0, #0x2
	sub r0, r5, #0x1
	lsl r0, r0, #0x4
	add r0, r1, r0
	add r0, r6, r0
	ldrb r3, [r0, #0x7]
	lsr r2, r4, #0x1f
	lsl r1, r4, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x1
	add r1, r3, #0x0
	asr r1, r0
	mov r0, #0x3
	and r0, r1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02029B90
FUN_02029B90: ; 0x02029B90
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	str r3, [sp, #0x0]
	cmp r3, #0x4
	blt _02029BA2
	bl GF_AssertFail
_02029BA2:
	mov r0, #0x1
	lsl r0, r0, #0x8
	cmp r5, r0
	blt _02029BAE
	bl GF_AssertFail
_02029BAE:
	cmp r4, #0x40
	blt _02029BB6
	bl GF_AssertFail
_02029BB6:
	cmp r5, #0x0
	beq _02029BFE
	asr r0, r4, #0x1
	lsr r0, r0, #0x1e
	add r0, r4, r0
	asr r2, r0, #0x2
	sub r0, r5, #0x1
	lsl r0, r0, #0x4
	add r0, r2, r0
	lsr r2, r4, #0x1f
	lsl r4, r4, #0x1e
	sub r4, r4, r2
	mov r3, #0x1e
	ror r4, r3
	add r2, r2, r4
	lsl r6, r2, #0x1
	mov r2, #0x3
	add r3, r2, #0x0
	add r1, r7, #0x7
	ldrb r4, [r1, r0]
	lsl r3, r6
	mov r2, #0xff
	eor r2, r3
	and r2, r4
	ldr r3, [sp, #0x0]
	strb r2, [r1, r0]
	ldrb r2, [r1, r0]
	lsl r3, r6
	orr r2, r3
	strb r2, [r1, r0]
	cmp r5, #0x67
	beq _02029BFE
	add r0, r7, #0x0
	mov r1, #0x1
	bl FUN_02029C04
_02029BFE:
	pop {r3-r7, pc}

	thumb_func_start FUN_02029C00
FUN_02029C00: ; 0x02029C00
	ldrb r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02029C04
FUN_02029C04: ; 0x02029C04
	strb r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02029C08
FUN_02029C08: ; 0x02029C08
	push {r3-r7, lr}
	mov lr, r0
	mov r0, #0x3
	mov r7, #0x0
	mov r4, #0x2
	mov r6, #0xff
	add r3, r0, #0x0
_02029C16:
	mov r1, lr
	add r1, r1, r7
	ldrb r2, [r1, #0x7]
	mov r12, r1
	mov r1, #0x0
_02029C20:
	add r5, r2, #0x0
	asr r5, r1
	and r5, r3
	cmp r5, #0x1
	bne _02029C40
	add r5, r0, #0x0
	lsl r5, r1
	eor r5, r6
	and r2, r5
	lsl r2, r2, #0x18
	lsr r5, r2, #0x18
	add r2, r4, #0x0
	lsl r2, r1
	orr r2, r5
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
_02029C40:
	add r1, r1, #0x2
	cmp r1, #0x8
	blt _02029C20
	mov r1, r12
	strb r2, [r1, #0x7]
	mov r1, #0xff
	add r7, r7, #0x1
	lsl r1, r1, #0x4
	cmp r7, r1
	blt _02029C16
	pop {r3-r7, pc}
	.balign 4
