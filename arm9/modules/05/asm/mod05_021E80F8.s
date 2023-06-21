	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E80F8
MOD05_021E80F8: ; 0x021E80F8
	push {r3, lr}
	mov r1, #0x14
	bl AllocFromHeap
	add r3, r0, #0
	mov r2, #0x14
	mov r1, #0
_021E8106:
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _021E8106
	pop {r3, pc}

	thumb_func_start MOD05_021E8110
MOD05_021E8110: ; 0x021E8110
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #0x13]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1f
	beq _021E8120
	bl RemoveWindow
_021E8120:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD05_021E8128
MOD05_021E8128: ; 0x021E8128
	strb r1, [r0, #0x12]
	strh r2, [r0, #0x10]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021E8130
MOD05_021E8130: ; 0x021E8130
	ldrb r3, [r0, #0x13]
	mov r2, #0x7f
	bic r3, r2
	mov r2, #0x7f
	and r1, r2
	orr r1, r3
	strb r1, [r0, #0x13]
	bx lr

	thumb_func_start MOD05_021E8140
MOD05_021E8140: ; 0x021E8140
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021E8144
MOD05_021E8144: ; 0x021E8144
	ldrb r0, [r0, #0x12]
	bx lr

	thumb_func_start MOD05_021E8148
MOD05_021E8148: ; 0x021E8148
	ldrb r0, [r0, #0x13]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x19
	bne _021E8154
	mov r0, #1
	bx lr
_021E8154:
	mov r0, #0
	bx lr

	thumb_func_start MOD05_021E8158
MOD05_021E8158: ; 0x021E8158
	push {r4, lr}
	ldr r4, [r0, #0x60]
	ldrb r1, [r4, #0x13]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x19
	cmp r1, #4
	bhi _021E81BA
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E8172: ; jump table
	.short _021E81BA - _021E8172 - 2 ; case 0
	.short _021E817C - _021E8172 - 2 ; case 1
	.short _021E818A - _021E8172 - 2 ; case 2
	.short _021E819C - _021E8172 - 2 ; case 3
	.short _021E81AE - _021E8172 - 2 ; case 4
_021E817C:
	bl MOD05_021E81D0
	ldrb r1, [r4, #0x13]
	mov r0, #0x7f
	bic r1, r0
	strb r1, [r4, #0x13]
	pop {r4, pc}
_021E818A:
	bl MOD05_021E82A0
	cmp r0, #1
	bne _021E81BA
	ldrb r1, [r4, #0x13]
	mov r0, #0x7f
	bic r1, r0
	strb r1, [r4, #0x13]
	pop {r4, pc}
_021E819C:
	bl MOD05_021E8260
	cmp r0, #1
	bne _021E81BA
	ldrb r1, [r4, #0x13]
	mov r0, #0x7f
	bic r1, r0
	strb r1, [r4, #0x13]
	pop {r4, pc}
_021E81AE:
	bl MOD05_021E820C
	ldrb r1, [r4, #0x13]
	mov r0, #0x7f
	bic r1, r0
	strb r1, [r4, #0x13]
_021E81BA:
	pop {r4, pc}

	thumb_func_start MOD05_021E81BC
MOD05_021E81BC: ; 0x021E81BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x60]
	bl MOD05_021E8130
	add r0, r4, #0
	bl MOD05_021E8158
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E81D0
MOD05_021E81D0: ; 0x021E81D0
	push {r4, lr}
	mov r1, #3
	add r4, r0, #0
	add r3, r1, #0
	ldr r0, [r4, #8]
	add r2, r1, #0
	sub r3, #0x33
	bl BgSetPosTextAndCommit
	ldr r1, [r4, #0x60]
	ldrb r0, [r1, #0x13]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _021E8200
	ldrb r2, [r1, #0x12]
	ldr r0, [r4, #8]
	mov r3, #3
	bl sub_020546E0
	ldr r2, [r4, #0x60]
	mov r0, #0x80
	ldrb r1, [r2, #0x13]
	orr r0, r1
	strb r0, [r2, #0x13]
_021E8200:
	ldr r0, [r4, #0x60]
	ldrb r1, [r0, #0x12]
	ldrh r2, [r0, #0x10]
	bl sub_02054744
	pop {r4, pc}

	thumb_func_start MOD05_021E820C
MOD05_021E820C: ; 0x021E820C
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, [r4, #0x60]
	ldrb r1, [r0, #0x13]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1f
	beq _021E825A
	bl RemoveWindow
	mov r0, #0x12
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	mov r2, #0
	ldr r0, [r4, #8]
	mov r1, #3
	add r3, r2, #0
	bl FillBgTilemapRect
	ldr r0, [r4, #8]
	mov r1, #3
	bl BgCommitTilemapBufferToVram
	mov r1, #3
	ldr r0, [r4, #8]
	add r2, r1, #0
	mov r3, #0
	bl BgSetPosTextAndCommit
	ldr r2, [r4, #0x60]
	mov r0, #0x80
	ldrb r1, [r2, #0x13]
	bic r1, r0
	strb r1, [r2, #0x13]
_021E825A:
	add sp, #0x10
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E8260
MOD05_021E8260: ; 0x021E8260
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	mov r1, #3
	bl Bg_GetYpos
	cmp r0, #0
	bne _021E8274
	mov r0, #1
	pop {r4, pc}
_021E8274:
	mov r1, #0x2f
	mvn r1, r1
	cmp r0, r1
	ble _021E8280
	cmp r0, #0
	blt _021E828E
_021E8280:
	mov r1, #3
	add r3, r1, #0
	ldr r0, [r4, #8]
	add r2, r1, #0
	sub r3, #0x33
	bl BgSetPosTextAndCommit
_021E828E:
	ldr r0, [r4, #8]
	mov r1, #3
	mov r2, #4
	mov r3, #0x10
	bl BgSetPosTextAndCommit
	mov r0, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E82A0
MOD05_021E82A0: ; 0x021E82A0
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, [r4, #8]
	mov r1, #3
	bl Bg_GetYpos
	mov r1, #0x2f
	mvn r1, r1
	cmp r0, r1
	bne _021E82EC
	mov r0, #0x12
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	mov r2, #0
	ldr r0, [r4, #8]
	mov r1, #3
	add r3, r2, #0
	bl FillBgTilemapRect
	ldr r0, [r4, #8]
	mov r1, #3
	bl BgCommitTilemapBufferToVram
	mov r1, #3
	ldr r0, [r4, #8]
	add r2, r1, #0
	mov r3, #0
	bl BgSetPosTextAndCommit
	add sp, #0x10
	mov r0, #1
	pop {r4, pc}
_021E82EC:
	ble _021E82F2
	cmp r0, #0
	blt _021E82FE
_021E82F2:
	mov r1, #3
	ldr r0, [r4, #8]
	add r2, r1, #0
	mov r3, #0
	bl BgSetPosTextAndCommit
_021E82FE:
	ldr r0, [r4, #8]
	mov r1, #3
	mov r2, #5
	mov r3, #0x10
	bl BgSetPosTextAndCommit
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
