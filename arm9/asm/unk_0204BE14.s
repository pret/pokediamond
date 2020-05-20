    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0204BE14
FUN_0204BE14: ; 0x0204BE14
	mov r0, #0xe8
	bx lr

	thumb_func_start FUN_0204BE18
FUN_0204BE18: ; 0x0204BE18
	push {r3-r5, lr}
	mov r2, #0x0
	add r3, r2, #0x0
_0204BE1E:
	add r1, r0, r2
	add r2, r2, #0x1
	strb r3, [r1, #0x3]
	cmp r2, #0x20
	blt _0204BE1E
	strb r3, [r0, #0x1]
	strb r3, [r0, #0x2]
	ldrb r1, [r0, #0x0]
	mov r2, #0x1
	bic r1, r2
	strb r1, [r0, #0x0]
	ldrb r4, [r0, #0x0]
	mov r1, #0x38
	bic r4, r1
	strb r4, [r0, #0x0]
	ldrb r4, [r0, #0x0]
	mov r1, #0x2
	bic r4, r1
	strb r4, [r0, #0x0]
	str r3, [r0, #0x24]
	ldrh r1, [r0, #0x28]
	bic r1, r2
	strh r1, [r0, #0x28]
	ldrh r2, [r0, #0x28]
	mov r1, #0x3e
	bic r2, r1
	strh r2, [r0, #0x28]
	ldrh r2, [r0, #0x28]
	ldr r1, _0204BEB0 ; =0xFFFFF03F
	and r1, r2
	strh r1, [r0, #0x28]
	add r1, r0, #0x0
	mov r2, #0x1
	add r1, #0xa8
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0xa4
	str r3, [r1, #0x0]
	ldr r1, _0204BEB4 ; =0x020F486C
	add r2, r0, #0x0
_0204BE6E:
	ldrb r5, [r1, #0x0]
	add r4, r2, #0x0
	add r4, #0xa9
	strb r5, [r4, #0x0]
	add r4, r2, #0x0
	ldrb r5, [r1, #0x1]
	add r4, #0xaa
	add r3, r3, #0x1
	strb r5, [r4, #0x0]
	add r1, r1, #0x2
	add r2, r2, #0x2
	cmp r3, #0x6
	blt _0204BE6E
	mov r4, #0x0
	add r3, r0, #0x0
	add r1, r4, #0x0
_0204BE8E:
	add r2, r3, #0x0
	add r2, #0xb6
	strh r1, [r2, #0x0]
	add r2, r3, #0x0
	add r2, #0xb8
	add r4, r4, #0x1
	add r3, r3, #0x4
	strh r1, [r2, #0x0]
	cmp r4, #0xc
	blt _0204BE8E
	ldrb r3, [r0, #0x0]
	mov r2, #0x4
	bic r3, r2
	strb r3, [r0, #0x0]
	bl FUN_0204BED8
	pop {r3-r5, pc}
	.balign 4
_0204BEB0: .word 0xFFFFF03F
_0204BEB4: .word 0x020F486C

	thumb_func_start FUN_0204BEB8
FUN_0204BEB8: ; 0x0204BEB8
	ldrb r2, [r0, #0x0]
	mov r1, #0x1
	bic r2, r1
	mov r1, #0x1
	orr r1, r2
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0204BEC8
FUN_0204BEC8: ; 0x0204BEC8
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_0204BED0
FUN_0204BED0: ; 0x0204BED0
	add r0, r0, r1
	ldrb r0, [r0, #0x3]
	bx lr
	.balign 4

	thumb_func_start FUN_0204BED8
FUN_0204BED8: ; 0x0204BED8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bmi _0204BEE4
	cmp r4, #0x19
	blt _0204BEE8
_0204BEE4:
	bl ErrorHandling
_0204BEE8:
	mov r0, #0x1
	ldrsb r1, [r5, r0]
	cmp r1, #0x19
	bge _0204BF10
	add r2, r5, #0x3
	ldrb r1, [r2, r4]
	cmp r1, #0x0
	bne _0204BF10
	strb r0, [r2, r4]
	ldrsb r0, [r5, r0]
	add r0, r0, #0x1
	strb r0, [r5, #0x1]
	cmp r4, #0x3
	bne _0204BF0C
	ldrb r1, [r5, #0x0]
	mov r0, #0x2
	orr r0, r1
	strb r0, [r5, #0x0]
_0204BF0C:
	mov r0, #0x1
	pop {r3-r5, pc}
_0204BF10:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0204BF14
FUN_0204BF14: ; 0x0204BF14
	mov r1, #0x2
	ldrsb r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start FUN_0204BF1C
FUN_0204BF1C: ; 0x0204BF1C
	push {r3-r4}
	mov r1, #0x2
	ldrsb r3, [r0, r1]
	mov r2, #0x0
	add r4, r3, #0x0
_0204BF26:
	add r3, r3, #0x1
	cmp r3, #0x19
	blt _0204BF2E
	add r3, r2, #0x0
_0204BF2E:
	cmp r3, r4
	beq _0204BF3A
	add r1, r0, r3
	ldrb r1, [r1, #0x3]
	cmp r1, #0x0
	beq _0204BF26
_0204BF3A:
	mov r1, #0x2
	strb r3, [r0, #0x2]
	ldrsb r0, [r0, r1]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0204BF44
FUN_0204BF44: ; 0x0204BF44
	push {r4, lr}
	add r4, r0, #0x0
	bne _0204BF4E
	bl ErrorHandling
_0204BF4E:
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1d
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0204BF58
FUN_0204BF58: ; 0x0204BF58
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0204BF66
	bl ErrorHandling
_0204BF66:
	cmp r4, #0x8
	blo _0204BF6E
	bl ErrorHandling
_0204BF6E:
	ldrb r1, [r5, #0x0]
	mov r0, #0x38
	bic r1, r0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1a
	orr r0, r1
	strb r0, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204BF84
FUN_0204BF84: ; 0x0204BF84
	ldr r0, [r0, #0x24]
	bx lr

	thumb_func_start FUN_0204BF88
FUN_0204BF88: ; 0x0204BF88
	ldrb r2, [r0, #0x0]
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x1f
	beq _0204BF92
	str r1, [r0, #0x24]
_0204BF92:
	bx lr

	thumb_func_start FUN_0204BF94
FUN_0204BF94: ; 0x0204BF94
	ldrh r0, [r0, #0x28]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_0204BF9C
FUN_0204BF9C: ; 0x0204BF9C
	ldrh r3, [r0, #0x28]
	lsl r3, r3, #0x1a
	lsr r3, r3, #0x1b
	str r3, [r1, #0x0]
	ldrh r0, [r0, #0x28]
	lsl r0, r0, #0x14
	lsr r0, r0, #0x1a
	str r0, [r2, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0204BFB0
FUN_0204BFB0: ; 0x0204BFB0
	push {r4-r5}
	ldrh r4, [r0, #0x28]
	mov r5, #0x1
	lsl r1, r1, #0x10
	bic r4, r5
	lsr r5, r1, #0x10
	mov r1, #0x1
	and r1, r5
	orr r1, r4
	strh r1, [r0, #0x28]
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	lsl r2, r2, #0x1b
	ldrh r1, [r0, #0x28]
	mov r4, #0x3e
	lsr r2, r2, #0x1a
	bic r1, r4
	orr r1, r2
	strh r1, [r0, #0x28]
	ldrh r2, [r0, #0x28]
	ldr r1, _0204BFEC ; =0xFFFFF03F
	and r2, r1
	lsl r1, r3, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x14
	orr r1, r2
	strh r1, [r0, #0x28]
	pop {r4-r5}
	bx lr
	.balign 4
_0204BFEC: .word 0xFFFFF03F

	thumb_func_start FUN_0204BFF0
FUN_0204BFF0: ; 0x0204BFF0
	push {r3-r4}
	add r3, r0, #0x0
	add r3, #0xa8
	ldrb r3, [r3, #0x0]
	cmp r3, r1
	bne _0204C016
	add r1, r0, #0x0
	add r1, #0xa4
	ldr r4, [r1, #0x0]
	mov r3, #0x1
	sub r1, r2, #0x1
	add r2, r3, #0x0
	lsl r2, r1
	add r1, r4, #0x0
	orr r1, r2
	add r0, #0xa4
	str r1, [r0, #0x0]
	pop {r3-r4}
	bx lr
_0204C016:
	add r3, r0, #0x0
	add r3, #0xa8
	strb r1, [r3, #0x0]
	mov r3, #0x1
	sub r1, r2, #0x1
	add r2, r3, #0x0
	lsl r2, r1
	add r0, #0xa4
	str r2, [r0, #0x0]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0204C02C
FUN_0204C02C: ; 0x0204C02C
	push {r3-r4}
	add r3, r0, #0x0
	add r3, #0xa8
	ldrb r3, [r3, #0x0]
	cmp r3, r1
	bne _0204C052
	add r1, r0, #0x0
	add r1, #0xa4
	ldr r4, [r1, #0x0]
	mov r3, #0x1
	sub r1, r2, #0x1
	add r2, r3, #0x0
	lsl r2, r1
	mvn r1, r2
	and r1, r4
	add r0, #0xa4
	str r1, [r0, #0x0]
	pop {r3-r4}
	bx lr
_0204C052:
	add r2, r0, #0x0
	add r2, #0xa8
	strb r1, [r2, #0x0]
	mov r1, #0x0
	add r0, #0xa4
	str r1, [r0, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0204C064
FUN_0204C064: ; 0x0204C064
	add r3, r0, #0x0
	add r3, #0xa8
	ldrb r3, [r3, #0x0]
	cmp r3, r1
	bne _0204C07C
	add r0, #0xa4
	ldr r1, [r0, #0x0]
	sub r0, r2, #0x1
	lsr r1, r0
	mov r0, #0x1
	and r0, r1
	bx lr
_0204C07C:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0204C080
FUN_0204C080: ; 0x0204C080
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r4, #0x6
	blt _0204C092
	bl ErrorHandling
_0204C092:
	lsl r1, r4, #0x1
	add r0, r5, r1
	add r0, #0xa9
	strb r6, [r0, #0x0]
	add r0, r5, r1
	add r0, #0xaa
	strb r7, [r0, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204C0A4
FUN_0204C0A4: ; 0x0204C0A4
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r4, #0x6
	blt _0204C0B6
	bl ErrorHandling
_0204C0B6:
	lsl r1, r4, #0x1
	add r0, r5, r1
	add r0, #0xa9
	ldrb r0, [r0, #0x0]
	strb r0, [r6, #0x0]
	add r0, r5, r1
	add r0, #0xaa
	ldrb r0, [r0, #0x0]
	strb r0, [r7, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204C0CC
FUN_0204C0CC: ; 0x0204C0CC
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_0204C0D4
FUN_0204C0D4: ; 0x0204C0D4
	push {r3, lr}
	ldrb r2, [r0, #0x0]
	lsl r2, r2, #0x1d
	lsr r2, r2, #0x1f
	beq _0204C0E6
	add r0, #0x2a
	mov r2, #0x78
	bl MI_CpuCopy8
_0204C0E6:
	pop {r3, pc}

	thumb_func_start FUN_0204C0E8
FUN_0204C0E8: ; 0x0204C0E8
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r1, r4, #0x0
	add r1, #0x2a
	mov r2, #0x78
	bl MI_CpuCopy8
	ldrb r1, [r4, #0x0]
	mov r0, #0x4
	orr r0, r1
	strb r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0204C104
FUN_0204C104: ; 0x0204C104
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	bl FUN_0204C158
	cmp r0, #0xc
	blt _0204C138
	mov r0, #0x0
	add r1, r5, #0x0
_0204C116:
	add r2, r1, #0x0
	add r2, #0xba
	ldrh r3, [r2, #0x0]
	add r2, r1, #0x0
	add r2, #0xb6
	strh r3, [r2, #0x0]
	add r2, r1, #0x0
	add r2, #0xbc
	ldrh r3, [r2, #0x0]
	add r2, r1, #0x0
	add r2, #0xb8
	add r0, r0, #0x1
	add r1, r1, #0x4
	strh r3, [r2, #0x0]
	cmp r0, #0xb
	blt _0204C116
	mov r0, #0xb
_0204C138:
	lsl r4, r0, #0x2
	add r0, r6, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020672BC
	add r1, r5, r4
	add r1, #0xb6
	strh r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_0206B754
	add r1, r5, r4
	add r1, #0xb8
	strh r0, [r1, #0x0]
	pop {r4-r6, pc}

	thumb_func_start FUN_0204C158
FUN_0204C158: ; 0x0204C158
	mov r2, #0x0
_0204C15A:
	add r1, r0, #0x0
	add r1, #0xb6
	ldrh r1, [r1, #0x0]
	cmp r1, #0x0
	bne _0204C168
	add r0, r2, #0x0
	bx lr
_0204C168:
	add r2, r2, #0x1
	add r0, r0, #0x4
	cmp r2, #0xc
	blt _0204C15A
	add r0, r2, #0x0
	bx lr

	thumb_func_start FUN_0204C174
FUN_0204C174: ; 0x0204C174
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	cmp r4, #0xc
	blt _0204C186
	bl ErrorHandling
_0204C186:
	add r6, r5, #0x0
	lsl r4, r4, #0x2
	add r6, #0xb6
	ldrh r0, [r6, r4]
	cmp r0, #0x0
	bne _0204C196
	bl ErrorHandling
_0204C196:
	ldrh r0, [r6, r4]
	str r0, [r7, #0x0]
	add r0, r5, r4
	add r0, #0xb8
	ldrh r1, [r0, #0x0]
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204C1A8
FUN_0204C1A8: ; 0x0204C1A8
	ldr r3, _0204C1B0 ; =FUN_02022610
	mov r1, #0x5
	bx r3
	nop
_0204C1B0: .word FUN_02022610
