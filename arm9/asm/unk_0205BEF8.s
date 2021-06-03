	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F70D8
UNK_020F70D8: ; 0x020F70D8
	.word 0x00000000, 0x00000000, 0x00000001, 0x00000001

	.global UNK_020F70E8
UNK_020F70E8: ; 0x020F70E8
	.word 0x00000002, 0x00000003, 0x00000000, 0x00000001

	.global UNK_020F70F8
UNK_020F70F8: ; 0x020F70F8
	.word 0x00000000, 0x00000002, 0x00000001, 0x00000003
	.word 0x00000000, 0x00000003, 0x00000001, 0x00000002

	.global UNK_020F7118
UNK_020F7118: ; 0x020F7118
	.word FUN_0205BFE0, FUN_0205BFE0, FUN_0205BFE0, FUN_0205BFE0
	.word FUN_0205BFEC, FUN_0205C16C, FUN_0205C16C, FUN_0205BFE0
	.word FUN_0205BFE0, FUN_0205BFE0, FUN_0205BFE0, FUN_0205BFE0

	.global UNK_020F7148
UNK_020F7148: ; 0x020F7148
	.word FUN_0205BFE4, FUN_0205BFE4, FUN_0205BFE4, FUN_0205BFE4
	.word FUN_0205C004, FUN_0205C198, FUN_0205C198, FUN_0205BFE4
	.word FUN_0205BFE4, FUN_0205BFE4, FUN_0205BFE4, FUN_0205BFE4

	.global UNK_020F7178
UNK_020F7178: ; 0x020F7178
	.word FUN_0205BFE8, FUN_0205BFE8, FUN_0205BFE8, FUN_0205BFE8
	.word FUN_0205C080, FUN_0205C214, FUN_0205C214, FUN_0205BFE8
	.word FUN_0205BFE8, FUN_0205BFE8, FUN_0205BFE8, FUN_0205BFE8

	.text

	thumb_func_start FUN_0205BEF8
FUN_0205BEF8: ; 0x0205BEF8
	ldr r3, _0205BEFC ; =FUN_0205BF24
	bx r3
	.balign 4
_0205BEFC: .word FUN_0205BF24

	thumb_func_start FUN_0205BF00
FUN_0205BF00: ; 0x0205BF00
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0205BF40
	cmp r0, #0x0
	bne _0205BF10
	mov r0, #0x0
	pop {r4, pc}
_0205BF10:
	add r0, r4, #0x0
	bl FUN_0205BF5C
	cmp r0, #0x0
	beq _0205BF1E
	mov r0, #0x1
	pop {r4, pc}
_0205BF1E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205BF24
FUN_0205BF24: ; 0x0205BF24
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058488
	add r1, r0, #0x0
	lsl r2, r1, #0x2
	ldr r1, _0205BF3C ; =UNK_020F7118
	add r0, r4, #0x0
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_0205BF3C: .word UNK_020F7118

	thumb_func_start FUN_0205BF40
FUN_0205BF40: ; 0x0205BF40
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058488
	add r1, r0, #0x0
	lsl r2, r1, #0x2
	ldr r1, _0205BF58 ; =UNK_020F7148
	add r0, r4, #0x0
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_0205BF58: .word UNK_020F7148

	thumb_func_start FUN_0205BF5C
FUN_0205BF5C: ; 0x0205BF5C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058488
	add r1, r0, #0x0
	lsl r2, r1, #0x2
	ldr r1, _0205BF74 ; =UNK_020F7178
	add r0, r4, #0x0
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_0205BF74: .word UNK_020F7178

	thumb_func_start FUN_0205BF78
FUN_0205BF78: ; 0x0205BF78
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02058B2C
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B14
	cmp r5, r0
	beq _0205BF90
	mov r0, #0x1
	pop {r3-r5, pc}
_0205BF90:
	add r0, r4, #0x0
	bl FUN_02058B4C
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B24
	cmp r5, r0
	beq _0205BFA6
	mov r0, #0x1
	pop {r3-r5, pc}
_0205BFA6:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205BFAC
FUN_0205BFAC: ; 0x0205BFAC
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02058B2C
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B14
	cmp r5, r0
	beq _0205BFC4
	mov r0, #0x0
	pop {r3-r5, pc}
_0205BFC4:
	add r0, r4, #0x0
	bl FUN_02058B4C
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B24
	cmp r5, r0
	bne _0205BFDA
	mov r0, #0x1
	pop {r3-r5, pc}
_0205BFDA:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205BFE0
FUN_0205BFE0: ; 0x0205BFE0
	bx lr
	.balign 4

	thumb_func_start FUN_0205BFE4
FUN_0205BFE4: ; 0x0205BFE4
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0205BFE8
FUN_0205BFE8: ; 0x0205BFE8
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0205BFEC
FUN_0205BFEC: ; 0x0205BFEC
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0x9
	bl FUN_020585B4
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02058510
	strb r0, [r4, #0x3]
	pop {r3-r5, pc}

	thumb_func_start FUN_0205C004
FUN_0205C004: ; 0x0205C004
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020585D8
	add r4, r0, #0x0
	ldrb r0, [r4, #0x0]
	cmp r0, #0x3
	bhi _0205C07C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205C020: ; jump table (using 16-bit offset)
	.short _0205C028 - _0205C020 - 2; case 0
	.short _0205C03A - _0205C020 - 2; case 1
	.short _0205C062 - _0205C020 - 2; case 2
	.short _0205C078 - _0205C020 - 2; case 3
_0205C028:
	add r0, r5, #0x0
	bl FUN_0205BF78
	cmp r0, #0x1
	bne _0205C07C
	ldrb r0, [r4, #0x0]
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	b _0205C07C
_0205C03A:
	add r0, r5, #0x0
	bl FUN_0205BFAC
	cmp r0, #0x0
	beq _0205C07C
	mov r0, #0x2
	ldrsb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, #0x2]
	ldrsb r1, [r4, r0]
	mov r0, #0x3
	ldrsb r0, [r4, r0]
	cmp r1, r0
	bge _0205C05C
	mov r0, #0x0
	strb r0, [r4, #0x0]
	b _0205C07C
_0205C05C:
	ldrb r0, [r4, #0x0]
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
_0205C062:
	add r0, r5, #0x0
	bl FUN_02058854
	cmp r0, #0x1
	beq _0205C07C
	ldrb r0, [r4, #0x0]
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	mov r0, #0x0
	strb r0, [r4, #0x2]
	strb r0, [r4, #0x1]
_0205C078:
	mov r0, #0x1
	pop {r3-r5, pc}
_0205C07C:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0205C080
FUN_0205C080: ; 0x0205C080
	push {r4-r6, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	bl FUN_020585D8
	add r4, r0, #0x0
	ldrb r0, [r4, #0x1]
	cmp r0, #0x3
	bhi _0205C15E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205C09E: ; jump table (using 16-bit offset)
	.short _0205C0A6 - _0205C09E - 2; case 0
	.short _0205C0C8 - _0205C09E - 2; case 1
	.short _0205C0FA - _0205C09E - 2; case 2
	.short _0205C110 - _0205C09E - 2; case 3
_0205C0A6:
	ldr r3, _0205C164 ; =UNK_020F70D8
	add r2, sp, #0x10
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	add r0, r5, #0x0
	bl FUN_020584C4
	strb r0, [r4, #0x4]
	lsl r1, r0, #0x2
	add r0, sp, #0x10
	ldr r0, [r0, r1]
	strb r0, [r4, #0x5]
	ldrb r0, [r4, #0x1]
	add r0, r0, #0x1
	strb r0, [r4, #0x1]
_0205C0C8:
	ldr r6, _0205C168 ; =UNK_020F70E8
	add r3, sp, #0x0
	add r2, r3, #0x0
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	mov r0, #0x5
	ldrsb r0, [r4, r0]
	lsl r3, r0, #0x3
	mov r0, #0x6
	ldrsb r0, [r4, r0]
	lsl r1, r0, #0x2
	add r0, r2, r3
	ldr r0, [r1, r0]
	mov r1, #0x0
	bl FUN_0205AFDC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205AE0C
	ldrb r0, [r4, #0x1]
	add r0, r0, #0x1
	strb r0, [r4, #0x1]
_0205C0FA:
	add r0, r5, #0x0
	bl FUN_0205B080
	cmp r0, #0x0
	bne _0205C10A
	add sp, #0x20
	mov r0, #0x1
	pop {r4-r6, pc}
_0205C10A:
	ldrb r0, [r4, #0x1]
	add r0, r0, #0x1
	strb r0, [r4, #0x1]
_0205C110:
	mov r0, #0x8
	ldrsb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, #0x8]
	ldrsb r0, [r4, r0]
	cmp r0, #0x8
	bge _0205C124
	add sp, #0x20
	mov r0, #0x1
	pop {r4-r6, pc}
_0205C124:
	mov r0, #0x0
	strb r0, [r4, #0x8]
	mov r0, #0x7
	ldrsb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, #0x7]
	ldrsb r0, [r4, r0]
	cmp r0, #0x4
	bge _0205C148
	mov r0, #0x6
	ldrsb r0, [r4, r0]
	add sp, #0x20
	add r1, r0, #0x1
	mov r0, #0x1
	and r1, r0
	strb r1, [r4, #0x6]
	strb r0, [r4, #0x1]
	pop {r4-r6, pc}
_0205C148:
	mov r1, #0x4
	ldrsb r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_020584AC
	ldrb r0, [r4, #0x1]
	add r0, r0, #0x1
	strb r0, [r4, #0x1]
	mov r0, #0x0
	strb r0, [r4, #0x7]
	strb r0, [r4, #0x0]
_0205C15E:
	mov r0, #0x0
	add sp, #0x20
	pop {r4-r6, pc}
	.balign 4
_0205C164: .word UNK_020F70D8
_0205C168: .word UNK_020F70E8

	thumb_func_start FUN_0205C16C
FUN_0205C16C: ; 0x0205C16C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0x9
	bl FUN_020585B4
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02058510
	strb r0, [r4, #0x3]
	add r0, r5, #0x0
	bl FUN_02058488
	cmp r0, #0x5
	beq _0205C190
	mov r0, #0x1
	b _0205C192
_0205C190:
	mov r0, #0x0
_0205C192:
	strb r0, [r4, #0x5]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205C198
FUN_0205C198: ; 0x0205C198
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020585D8
	add r4, r0, #0x0
	ldrb r0, [r4, #0x0]
	cmp r0, #0x3
	bhi _0205C210
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205C1B4: ; jump table (using 16-bit offset)
	.short _0205C1BC - _0205C1B4 - 2; case 0
	.short _0205C1CE - _0205C1B4 - 2; case 1
	.short _0205C1F6 - _0205C1B4 - 2; case 2
	.short _0205C20C - _0205C1B4 - 2; case 3
_0205C1BC:
	add r0, r5, #0x0
	bl FUN_0205BF78
	cmp r0, #0x1
	bne _0205C210
	ldrb r0, [r4, #0x0]
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	b _0205C210
_0205C1CE:
	add r0, r5, #0x0
	bl FUN_0205BFAC
	cmp r0, #0x0
	beq _0205C210
	mov r0, #0x2
	ldrsb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, #0x2]
	ldrsb r1, [r4, r0]
	mov r0, #0x3
	ldrsb r0, [r4, r0]
	cmp r1, r0
	bge _0205C1F0
	mov r0, #0x0
	strb r0, [r4, #0x0]
	b _0205C210
_0205C1F0:
	ldrb r0, [r4, #0x0]
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
_0205C1F6:
	add r0, r5, #0x0
	bl FUN_02058854
	cmp r0, #0x1
	beq _0205C210
	ldrb r0, [r4, #0x0]
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	mov r0, #0x0
	strb r0, [r4, #0x2]
	strb r0, [r4, #0x1]
_0205C20C:
	mov r0, #0x1
	pop {r3-r5, pc}
_0205C210:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0205C214
FUN_0205C214: ; 0x0205C214
	push {r3-r7, lr}
	sub sp, #0x20
	ldr r3, _0205C330 ; =UNK_020F70F8
	add r2, sp, #0x0
	add r7, r0, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	add r0, r7, #0x0
	bl FUN_020585D8
	add r4, r0, #0x0
	ldrb r0, [r4, #0x1]
	cmp r0, #0x3
	bhi _0205C32A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205C248: ; jump table (using 16-bit offset)
	.short _0205C250 - _0205C248 - 2; case 0
	.short _0205C296 - _0205C248 - 2; case 1
	.short _0205C2BC - _0205C248 - 2; case 2
	.short _0205C2D2 - _0205C248 - 2; case 3
_0205C250:
	add r0, r7, #0x0
	bl FUN_020584C4
	mov r5, #0x0
	add r6, r0, #0x0
	add r1, r5, #0x0
	add r0, sp, #0x0
	mov r2, #0x5
	b _0205C266
_0205C262:
	add r1, r1, #0x4
	add r5, r5, #0x1
_0205C266:
	cmp r5, #0x4
	bge _0205C276
	ldrsb r3, [r4, r2]
	lsl r3, r3, #0x4
	add r3, r0, r3
	ldr r3, [r1, r3]
	cmp r6, r3
	bne _0205C262
_0205C276:
	cmp r5, #0x4
	blt _0205C27E
	bl GF_AssertFail
_0205C27E:
	add r0, r5, #0x1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	strb r6, [r4, #0x4]
	add r0, r2, r1
	strb r0, [r4, #0x6]
	ldrb r0, [r4, #0x1]
	add r0, r0, #0x1
	strb r0, [r4, #0x1]
_0205C296:
	mov r0, #0x5
	ldrsb r0, [r4, r0]
	add r2, sp, #0x0
	lsl r3, r0, #0x4
	mov r0, #0x6
	ldrsb r0, [r4, r0]
	lsl r1, r0, #0x2
	add r0, r2, r3
	ldr r0, [r1, r0]
	mov r1, #0x0
	bl FUN_0205AFDC
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0205AE0C
	ldrb r0, [r4, #0x1]
	add r0, r0, #0x1
	strb r0, [r4, #0x1]
_0205C2BC:
	add r0, r7, #0x0
	bl FUN_0205B080
	cmp r0, #0x0
	bne _0205C2CC
	add sp, #0x20
	mov r0, #0x1
	pop {r3-r7, pc}
_0205C2CC:
	ldrb r0, [r4, #0x1]
	add r0, r0, #0x1
	strb r0, [r4, #0x1]
_0205C2D2:
	mov r0, #0x8
	ldrsb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, #0x8]
	ldrsb r0, [r4, r0]
	cmp r0, #0x8
	bge _0205C2E6
	add sp, #0x20
	mov r0, #0x1
	pop {r3-r7, pc}
_0205C2E6:
	mov r0, #0x0
	strb r0, [r4, #0x8]
	mov r0, #0x7
	ldrsb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, #0x7]
	ldrsb r0, [r4, r0]
	cmp r0, #0x4
	bge _0205C314
	mov r0, #0x6
	ldrsb r0, [r4, r0]
	add sp, #0x20
	add r0, r0, #0x1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	strb r0, [r4, #0x6]
	mov r0, #0x1
	strb r0, [r4, #0x1]
	pop {r3-r7, pc}
_0205C314:
	mov r1, #0x4
	ldrsb r1, [r4, r1]
	add r0, r7, #0x0
	bl FUN_020584AC
	ldrb r0, [r4, #0x1]
	add r0, r0, #0x1
	strb r0, [r4, #0x1]
	mov r0, #0x0
	strb r0, [r4, #0x7]
	strb r0, [r4, #0x0]
_0205C32A:
	mov r0, #0x0
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_0205C330: .word UNK_020F70F8
