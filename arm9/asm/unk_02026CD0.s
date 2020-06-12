	.include "asm/macros.inc"
    .include "global.inc"

	.extern gGameLanguage

	.text

	thumb_func_start FUN_02026CD0
FUN_02026CD0: ; 0x02026CD0
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	add r7, r3, #0x0
	bl GetMonDataEncrypted
	add r2, r5, #0x0
	strh r0, [r5, #0x8]
	add r0, r4, #0x0
	mov r1, #0x74
	add r2, #0xa
	bl GetMonDataEncrypted
	mov r1, #0x0
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl GetMonDataEncrypted
	str r0, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl GetMonDataEncrypted
	str r0, [r5, #0x4]
	add r0, r4, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl GetMonDataEncrypted
	add r1, r5, #0x0
	add r1, #0x33
	strb r0, [r1, #0x0]
	add r0, r5, #0x0
	add r0, #0x31
	strb r6, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x32
	strb r7, [r0, #0x0]
	add r1, sp, #0x8
	mov r0, #0x10
	ldrsb r0, [r1, r0]
	add r5, #0x30
	strb r0, [r5, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026D34
FUN_02026D34: ; 0x02026D34
	push {r3-r6, lr}
	sub sp, #0xc
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r4, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x8
	bl MOD17_021DB858
	add r0, r4, #0x0
	bl MOD17_021DB7E8
	add r4, r0, #0x0
	mov r0, #0x1
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x8
	cmp r1, r0
	blt _02026D5E
	bl ErrorHandling
_02026D5E:
	mov r0, #0x1
	ldr r1, [sp, #0x8]
	lsl r0, r0, #0x8
	cmp r1, r0
	blt _02026D6C
	bl ErrorHandling
_02026D6C:
	mov r0, #0x7f
	mvn r0, r0
	cmp r4, r0
	bgt _02026D78
	bl ErrorHandling
_02026D78:
	lsl r0, r4, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02026CD0
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02026D98
FUN_02026D98: ; 0x02026D98
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r1, r5, #0x0
	add r4, r2, #0x0
	add r1, #0x20
	mov r2, #0x8
	bl FUN_02021EF0
	add r5, #0x34
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02026DB0
FUN_02026DB0: ; 0x02026DB0
	strb r1, [r0, #0x0]
	ldr r1, _02026DC0 ; =0xFFFFFFF0
	strb r2, [r0, #0x1]
	strb r3, [r0, #0x2]
	add r1, sp
	ldrb r1, [r1, #0x10]
	strb r1, [r0, #0x3]
	bx lr
	.balign 4
_02026DC0: .word 0xFFFFFFF0

	thumb_func_start FUN_02026DC4
FUN_02026DC4: ; 0x02026DC4
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	cmp r4, #0x3d
	blo _02026DD4
	bl ErrorHandling
_02026DD4:
	lsr r2, r4, #0x1f
	lsl r1, r4, #0x1d
	sub r1, r1, r2
	mov r0, #0x1d
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1a
	lsr r1, r0, #0x18
	lsr r0, r4, #0x3
	lsl r0, r0, #0x18
	mov r2, #0xf
	lsr r0, r0, #0x16
	lsl r2, r1
	ldr r3, [r5, r0]
	mvn r2, r2
	and r2, r3
	str r2, [r5, r0]
	add r2, r6, #0x0
	ldr r3, [r5, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r5, r0]
	pop {r4-r6, pc}

	thumb_func_start FUN_02026E08
FUN_02026E08: ; 0x02026E08
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3d
	blo _02026E16
	bl ErrorHandling
_02026E16:
	lsr r3, r4, #0x1f
	lsl r2, r4, #0x1d
	lsr r0, r4, #0x3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x16
	sub r2, r2, r3
	mov r1, #0x1d
	ror r2, r1
	add r1, r3, r2
	lsl r1, r1, #0x18
	ldr r0, [r5, r0]
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1a
	add r2, r0, #0x0
	lsr r1, r1, #0x18
	lsr r2, r1
	mov r0, #0xf
	and r0, r2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x9
	bls _02026E44
	mov r0, #0x9
_02026E44:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026E48
FUN_02026E48: ; 0x02026E48
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x2
	blo _02026E58
	bl ErrorHandling
_02026E58:
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1b
	sub r1, r1, r2
	mov r0, #0x1b
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	lsr r0, r6, #0x5
	lsl r0, r0, #0x18
	mov r2, #0x1
	lsr r0, r0, #0x16
	lsl r2, r1
	ldr r3, [r5, r0]
	mvn r2, r2
	and r2, r3
	str r2, [r5, r0]
	add r2, r4, #0x0
	ldr r3, [r5, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r5, r0]
	pop {r4-r6, pc}

	thumb_func_start FUN_02026E88
FUN_02026E88: ; 0x02026E88
	lsr r2, r1, #0x5
	lsl r2, r2, #0x18
	lsr r2, r2, #0x16
	ldr r3, [r0, r2]
	lsr r2, r1, #0x1f
	lsl r1, r1, #0x1b
	sub r1, r1, r2
	mov r0, #0x1b
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r3, #0x0
	lsr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
	.balign 4

	thumb_func_start FUN_02026EB0
FUN_02026EB0: ; 0x02026EB0
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x12
	bls _02026EC0
	bl ErrorHandling
_02026EC0:
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1b
	lsr r1, r0, #0x18
	lsr r0, r6, #0x2
	lsl r0, r0, #0x18
	mov r2, #0xff
	lsr r0, r0, #0x16
	lsl r2, r1
	ldr r3, [r5, r0]
	mvn r2, r2
	and r2, r3
	str r2, [r5, r0]
	add r2, r4, #0x0
	ldr r3, [r5, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r5, r0]
	pop {r4-r6, pc}

	thumb_func_start FUN_02026EF4
FUN_02026EF4: ; 0x02026EF4
	lsr r2, r1, #0x2
	lsl r2, r2, #0x18
	lsr r2, r2, #0x16
	ldr r0, [r0, r2]
	lsr r3, r1, #0x1f
	lsl r2, r1, #0x1e
	sub r2, r2, r3
	mov r1, #0x1e
	ror r2, r1
	add r1, r3, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x18
	lsr r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr

	thumb_func_start FUN_02026F18
FUN_02026F18: ; 0x02026F18
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_02026F20:
	lsl r1, r4, #0x18
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026EF4
	cmp r0, #0x12
	beq _02026F30
	add r5, r5, #0x1
_02026F30:
	add r4, r4, #0x1
	cmp r4, #0x12
	blt _02026F20
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	pop {r4-r6, pc}

	thumb_func_start FUN_02026F3C
FUN_02026F3C: ; 0x02026F3C
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0x2
	add r4, r2, #0x0
	bl FUN_02068E14
	mov r1, #0x80
	strb r1, [r5, #0x0]
	mov r1, #0x28
	sub r1, r1, r0
	mov r0, #0x8d
	sub r0, r0, r1
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x0]
	add r0, #0x28
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026F60
FUN_02026F60: ; 0x02026F60
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r6, _02026FC8 ; =0x00001234
	mov r4, #0x0
	add r5, r7, #0x0
_02026F6A:
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0x74
	bl memset
	str r6, [r5, #0x0]
	add r4, r4, #0x1
	add r5, #0x74
	cmp r4, #0xb
	blt _02026F6A
	ldr r0, _02026FCC ; =0x000004FC
	mov r6, #0x0
	add r4, r7, r0
	add r5, r7, #0x0
_02026F86:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x98
	bl memset
	ldr r1, _02026FC8 ; =0x00001234
	ldr r0, _02026FCC ; =0x000004FC
	add r6, r6, #0x1
	str r1, [r5, r0]
	add r4, #0x98
	add r5, #0x98
	cmp r6, #0x5
	blt _02026F86
	ldr r0, _02026FD0 ; =0x000007F4
	mov r1, #0x0
	add r0, r7, r0
	mov r2, #0x40
	bl memset
	ldr r5, _02026FD4 ; =0x0000081C
	mov r4, #0x0
	mov r6, #0x12
_02026FB2:
	lsl r2, r4, #0x18
	add r0, r7, r5
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026EB0
	add r4, r4, #0x1
	cmp r4, #0x12
	blt _02026FB2
	pop {r3-r7, pc}
	nop
_02026FC8: .word 0x00001234
_02026FCC: .word 0x000004FC
_02026FD0: .word 0x000007F4
_02026FD4: .word 0x0000081C

	thumb_func_start FUN_02026FD8
FUN_02026FD8: ; 0x02026FD8
	ldr r0, _02026FDC ; =0x00000834
	bx lr
	.balign 4
_02026FDC: .word 0x00000834

	thumb_func_start FUN_02026FE0
FUN_02026FE0: ; 0x02026FE0
	mov r0, #0x74
	bx lr

	thumb_func_start FUN_02026FE4
FUN_02026FE4: ; 0x02026FE4
	mov r0, #0x98
	bx lr

	thumb_func_start FUN_02026FE8
FUN_02026FE8: ; 0x02026FE8
	push {r4, lr}
	mov r1, #0x98
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x98
	add r4, r0, #0x0
	bl memset
	ldr r0, _02027004 ; =0x00001234
	str r0, [r4, #0x0]
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_02027004: .word 0x00001234

	thumb_func_start FUN_02027008
FUN_02027008: ; 0x02027008
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	cmp r6, #0xb
	blt _02027016
	bl ErrorHandling
_02027016:
	mov r0, #0x74
	add r4, r6, #0x0
	mul r4, r0
	ldr r1, [r5, r4]
	ldr r0, _0202703C ; =0x00001234
	cmp r1, r0
	beq _0202702A
	ldr r0, _02027040 ; =0x00002345
	cmp r1, r0
	bne _0202702E
_0202702A:
	mov r0, #0x1
	b _02027030
_0202702E:
	mov r0, #0x0
_02027030:
	cmp r0, #0x0
	bne _02027038
	bl ErrorHandling
_02027038:
	add r0, r5, r4
	pop {r4-r6, pc}
	.balign 4
_0202703C: .word 0x00001234
_02027040: .word 0x00002345

	thumb_func_start FUN_02027044
FUN_02027044: ; 0x02027044
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	cmp r6, #0x5
	blt _02027052
	bl ErrorHandling
_02027052:
	mov r0, #0x98
	add r4, r6, #0x0
	mul r4, r0
	ldr r0, _02027080 ; =0x000004FC
	add r1, r5, r4
	ldr r1, [r1, r0]
	ldr r0, _02027084 ; =0x00001234
	cmp r1, r0
	beq _0202706A
	ldr r0, _02027088 ; =0x00002345
	cmp r1, r0
	bne _0202706E
_0202706A:
	mov r0, #0x1
	b _02027070
_0202706E:
	mov r0, #0x0
_02027070:
	cmp r0, #0x0
	bne _02027078
	bl ErrorHandling
_02027078:
	ldr r0, _02027080 ; =0x000004FC
	add r0, r5, r0
	add r0, r0, r4
	pop {r4-r6, pc}
	.balign 4
_02027080: .word 0x000004FC
_02027084: .word 0x00001234
_02027088: .word 0x00002345

	thumb_func_start FUN_0202708C
FUN_0202708C: ; 0x0202708C
	ldr r1, _02027094 ; =0x000007F4
	add r0, r0, r1
	bx lr
	nop
_02027094: .word 0x000007F4

	thumb_func_start FUN_02027098
FUN_02027098: ; 0x02027098
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xb
	blt _020270A6
	bl ErrorHandling
_020270A6:
	mov r0, #0x74
	mul r0, r4
	add r0, r5, r0
	bl FUN_0202729C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020270B4
FUN_020270B4: ; 0x020270B4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x5
	blt _020270C2
	bl ErrorHandling
_020270C2:
	ldr r0, _020270D4 ; =0x000004FC
	add r1, r5, r0
	mov r0, #0x98
	mul r0, r4
	add r0, r1, r0
	bl FUN_020276D8
	pop {r3-r5, pc}
	nop
_020270D4: .word 0x000004FC

	thumb_func_start FUN_020270D8
FUN_020270D8: ; 0x020270D8
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r2, #0x0
	mov r4, #0x1
	bl FUN_02027114
	cmp r6, #0x3d
	bhs _020270F2
	add r0, r0, r5
	cmp r0, #0x9
	bls _020270FA
	mov r4, #0x0
	b _020270FA
_020270F2:
	add r0, r0, r5
	cmp r0, #0x1
	bls _020270FA
	mov r4, #0x0
_020270FA:
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02027100
FUN_02027100: ; 0x02027100
	push {r3, lr}
	bl FUN_0202714C
	cmp r0, #0x12
	beq _0202710E
	mov r0, #0x1
	pop {r3, pc}
_0202710E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02027114
FUN_02027114: ; 0x02027114
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x64
	blo _02027122
	bl ErrorHandling
_02027122:
	cmp r5, #0x3d
	bhs _02027132
	lsl r1, r5, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E08
	pop {r3-r5, pc}
_02027132:
	bhs _02027138
	bl ErrorHandling
_02027138:
	sub r5, #0x3d
	lsl r0, r5, #0x18
	lsr r1, r0, #0x18
	add r4, #0x20
	lsl r1, r1, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E88
	pop {r3-r5, pc}

	thumb_func_start FUN_0202714C
FUN_0202714C: ; 0x0202714C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x12
	blo _0202715A
	bl ErrorHandling
_0202715A:
	add r5, #0x28
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026EF4
	pop {r3-r5, pc}

	thumb_func_start FUN_02027168
FUN_02027168: ; 0x02027168
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_02027170:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02027114
	add r4, r4, #0x1
	add r5, r5, r0
	cmp r4, #0x64
	blt _02027170
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02027184
FUN_02027184: ; 0x02027184
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_0202718C:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0202714C
	cmp r0, #0x12
	beq _0202719A
	add r5, r5, #0x1
_0202719A:
	add r4, r4, #0x1
	cmp r4, #0x12
	blt _0202718C
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020271A4
FUN_020271A4: ; 0x020271A4
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x64
	blo _020271B4
	bl ErrorHandling
_020271B4:
	cmp r4, #0x3d
	bhs _020271DA
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E08
	add r0, r0, r6
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, #0x9
	bls _020271CE
	mov r1, #0x9
_020271CE:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026DC4
	pop {r4-r6, pc}
_020271DA:
	add r0, r5, #0x0
	lsl r1, r4, #0x18
	add r0, #0x20
	lsr r1, r1, #0x18
	bl FUN_02026E88
	add r0, r0, r6
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x1
	bls _020271F2
	mov r6, #0x1
_020271F2:
	cmp r4, #0x3d
	bhs _020271FA
	bl ErrorHandling
_020271FA:
	sub r4, #0x3d
	lsl r0, r4, #0x18
	lsr r2, r0, #0x18
	add r5, #0x20
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026E48
	pop {r4-r6, pc}

	thumb_func_start FUN_02027210
FUN_02027210: ; 0x02027210
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x64
	blo _02027220
	bl ErrorHandling
_02027220:
	cmp r4, #0x3d
	bhs _02027248
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E08
	cmp r0, r6
	bls _0202723A
	sub r0, r0, r6
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	b _0202723C
_0202723A:
	mov r1, #0x0
_0202723C:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026DC4
	pop {r4-r6, pc}
_02027248:
	bhs _0202724E
	bl ErrorHandling
_0202724E:
	sub r4, #0x3d
	lsl r0, r4, #0x18
	lsr r2, r0, #0x18
	add r5, #0x20
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	mov r1, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026E48
	pop {r4-r6, pc}

	thumb_func_start FUN_02027264
FUN_02027264: ; 0x02027264
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x12
	blo _02027272
	bl ErrorHandling
_02027272:
	add r0, r5, #0x0
	lsl r1, r4, #0x18
	add r0, #0x28
	lsr r1, r1, #0x18
	bl FUN_02026EF4
	cmp r0, #0x12
	bne _02027298
	add r0, r5, #0x0
	add r0, #0x28
	bl FUN_02026F18
	lsl r2, r4, #0x18
	add r5, #0x28
	add r1, r0, #0x0
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026EB0
_02027298:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202729C
FUN_0202729C: ; 0x0202729C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _020272CC ; =0x00001234
	cmp r1, r0
	beq _020272AE
	ldr r0, _020272D0 ; =0x00002345
	cmp r1, r0
	bne _020272B2
_020272AE:
	mov r0, #0x1
	b _020272B4
_020272B2:
	mov r0, #0x0
_020272B4:
	cmp r0, #0x0
	bne _020272BC
	bl ErrorHandling
_020272BC:
	ldr r1, [r4, #0x0]
	ldr r0, _020272D0 ; =0x00002345
	cmp r1, r0
	bne _020272C8
	mov r0, #0x1
	pop {r4, pc}
_020272C8:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_020272CC: .word 0x00001234
_020272D0: .word 0x00002345

	thumb_func_start FUN_020272D4
FUN_020272D4: ; 0x020272D4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027304 ; =0x00001234
	cmp r1, r0
	beq _020272E6
	ldr r0, _02027308 ; =0x00002345
	cmp r1, r0
	bne _020272EA
_020272E6:
	mov r0, #0x1
	b _020272EC
_020272EA:
	mov r0, #0x0
_020272EC:
	cmp r0, #0x0
	bne _020272F4
	bl ErrorHandling
_020272F4:
	ldr r0, _02027308 ; =0x00002345
	str r0, [r4, #0x0]
	ldr r0, _0202730C ; =gGameLanguage
	add r4, #0x71
	ldrb r0, [r0, #0x0]
	strb r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02027304: .word 0x00001234
_02027308: .word 0x00002345
_0202730C: .word gGameLanguage

	thumb_func_start FUN_02027310
FUN_02027310: ; 0x02027310
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027340 ; =0x00001234
	cmp r1, r0
	beq _02027322
	ldr r0, _02027344 ; =0x00002345
	cmp r1, r0
	bne _02027326
_02027322:
	mov r0, #0x1
	b _02027328
_02027326:
	mov r0, #0x0
_02027328:
	cmp r0, #0x0
	bne _02027330
	bl ErrorHandling
_02027330:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x74
	bl memset
	ldr r0, _02027340 ; =0x00001234
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4
_02027340: .word 0x00001234
_02027344: .word 0x00002345

	thumb_func_start FUN_02027348
FUN_02027348: ; 0x02027348
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027378 ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _0202735E
	ldr r0, _0202737C ; =0x00002345
	cmp r1, r0
	bne _02027362
_0202735E:
	mov r0, #0x1
	b _02027364
_02027362:
	mov r0, #0x0
_02027364:
	cmp r0, #0x0
	bne _0202736C
	bl ErrorHandling
_0202736C:
	add r0, r5, #0x4
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D34
	pop {r4-r6, pc}
	.balign 4
_02027378: .word 0x00001234
_0202737C: .word 0x00002345

	thumb_func_start FUN_02027380
FUN_02027380: ; 0x02027380
	push {r4-r7, lr}
	sub sp, #0x14
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x4]
	add r6, r2, #0x0
	bl FUN_02013ECC
	add r1, sp, #0xc
	strh r0, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x2]
	ldrh r0, [r1, #0x0]
	strh r0, [r1, #0x4]
	ldrh r0, [r1, #0x2]
	strh r0, [r1, #0x6]
	ldr r0, [r4, #0x4]
	bl FUN_02013F00
	str r0, [sp, #0x8]
	cmp r6, #0xa
	blt _020273B0
	bl ErrorHandling
_020273B0:
	add r1, sp, #0xc
	mov r0, #0x4
	ldrsh r1, [r1, r0]
	add r0, #0xfc
	cmp r1, r0
	blt _020273C0
	bl ErrorHandling
_020273C0:
	add r1, sp, #0xc
	mov r0, #0x6
	ldrsh r7, [r1, r0]
	add r0, #0xfa
	cmp r7, r0
	blt _020273D0
	bl ErrorHandling
_020273D0:
	mov r1, #0x7f
	ldr r0, [sp, #0x8]
	mvn r1, r1
	cmp r0, r1
	bgt _020273DE
	bl ErrorHandling
_020273DE:
	mov r0, #0x1
	lsl r0, r6
	ldr r1, [r5, #0x3c]
	str r0, [sp, #0x4]
	tst r0, r1
	beq _020273EE
	bl ErrorHandling
_020273EE:
	ldr r1, [r5, #0x0]
	ldr r0, _02027440 ; =0x00001234
	cmp r1, r0
	beq _020273FC
	ldr r0, _02027444 ; =0x00002345
	cmp r1, r0
	bne _02027400
_020273FC:
	mov r0, #0x1
	b _02027402
_02027400:
	mov r0, #0x0
_02027402:
	cmp r0, #0x0
	bne _0202740A
	bl ErrorHandling
_0202740A:
	ldr r0, [sp, #0x8]
	add r1, r5, #0x0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r3, sp, #0xc
	mov r2, #0x4
	ldrsh r2, [r3, r2]
	lsl r3, r7, #0x18
	add r1, #0x48
	lsl r0, r6, #0x2
	add r0, r1, r0
	ldr r1, [r4, #0x0]
	lsl r2, r2, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02026DB0
	ldr r1, [r5, #0x3c]
	ldr r0, [sp, #0x4]
	orr r0, r1
	str r0, [r5, #0x3c]
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02027440: .word 0x00001234
_02027444: .word 0x00002345

	thumb_func_start FUN_02027448
FUN_02027448: ; 0x02027448
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027470 ; =0x00001234
	cmp r1, r0
	beq _0202745C
	ldr r0, _02027474 ; =0x00002345
	cmp r1, r0
	bne _02027460
_0202745C:
	mov r0, #0x1
	b _02027462
_02027460:
	mov r0, #0x0
_02027462:
	cmp r0, #0x0
	bne _0202746A
	bl ErrorHandling
_0202746A:
	add r5, #0x70
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4
_02027470: .word 0x00001234
_02027474: .word 0x00002345

	thumb_func_start FUN_02027478
FUN_02027478: ; 0x02027478
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020274B0 ; =0x00001234
	cmp r1, r0
	beq _0202748C
	ldr r0, _020274B4 ; =0x00002345
	cmp r1, r0
	bne _02027490
_0202748C:
	mov r0, #0x1
	b _02027492
_02027490:
	mov r0, #0x0
_02027492:
	cmp r0, #0x0
	bne _0202749A
	bl ErrorHandling
_0202749A:
	add r0, r5, #0x0
	add r0, #0x40
	bl FUN_02013724
	add r5, #0x40
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_02013998
	pop {r3-r5, pc}
	.balign 4
_020274B0: .word 0x00001234
_020274B4: .word 0x00002345

	thumb_func_start FUN_020274B8
FUN_020274B8: ; 0x020274B8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020274E8 ; =0x00001234
	cmp r1, r0
	beq _020274CC
	ldr r0, _020274EC ; =0x00002345
	cmp r1, r0
	bne _020274D0
_020274CC:
	mov r0, #0x1
	b _020274D2
_020274D0:
	mov r0, #0x0
_020274D2:
	cmp r0, #0x0
	bne _020274DA
	bl ErrorHandling
_020274DA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x74
	bl memcpy
	pop {r3-r5, pc}
	nop
_020274E8: .word 0x00001234
_020274EC: .word 0x00002345

	thumb_func_start FUN_020274F0
FUN_020274F0: ; 0x020274F0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027520 ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _02027506
	ldr r0, _02027524 ; =0x00002345
	cmp r1, r0
	bne _0202750A
_02027506:
	mov r0, #0x1
	b _0202750C
_0202750A:
	mov r0, #0x0
_0202750C:
	cmp r0, #0x0
	bne _02027514
	bl ErrorHandling
_02027514:
	add r0, r5, #0x4
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D98
	pop {r4-r6, pc}
	.balign 4
_02027520: .word 0x00001234
_02027524: .word 0x00002345

	thumb_func_start FUN_02027528
FUN_02027528: ; 0x02027528
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xa
	blt _02027536
	bl ErrorHandling
_02027536:
	ldr r1, [r5, #0x0]
	ldr r0, _0202755C ; =0x00001234
	cmp r1, r0
	beq _02027544
	ldr r0, _02027560 ; =0x00002345
	cmp r1, r0
	bne _02027548
_02027544:
	mov r0, #0x1
	b _0202754A
_02027548:
	mov r0, #0x0
_0202754A:
	cmp r0, #0x0
	bne _02027552
	bl ErrorHandling
_02027552:
	mov r0, #0x1
	ldr r1, [r5, #0x3c]
	lsl r0, r4
	and r0, r1
	pop {r3-r5, pc}
	.balign 4
_0202755C: .word 0x00001234
_02027560: .word 0x00002345

	thumb_func_start FUN_02027564
FUN_02027564: ; 0x02027564
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027588 ; =0x00001234
	cmp r1, r0
	beq _02027576
	ldr r0, _0202758C ; =0x00002345
	cmp r1, r0
	bne _0202757A
_02027576:
	mov r0, #0x1
	b _0202757C
_0202757A:
	mov r0, #0x0
_0202757C:
	cmp r0, #0x0
	bne _02027584
	bl ErrorHandling
_02027584:
	add r0, r4, #0x4
	pop {r4, pc}
	.balign 4
_02027588: .word 0x00001234
_0202758C: .word 0x00002345

	thumb_func_start FUN_02027590
FUN_02027590: ; 0x02027590
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xa
	blt _0202759E
	bl ErrorHandling
_0202759E:
	mov r0, #0x1
	ldr r1, [r5, #0x3c]
	lsl r0, r4
	tst r0, r1
	bne _020275AC
	bl ErrorHandling
_020275AC:
	ldr r1, [r5, #0x0]
	ldr r0, _020275D0 ; =0x00001234
	cmp r1, r0
	beq _020275BA
	ldr r0, _020275D4 ; =0x00002345
	cmp r1, r0
	bne _020275BE
_020275BA:
	mov r0, #0x1
	b _020275C0
_020275BE:
	mov r0, #0x0
_020275C0:
	cmp r0, #0x0
	bne _020275C8
	bl ErrorHandling
_020275C8:
	add r5, #0x48
	lsl r0, r4, #0x2
	add r0, r5, r0
	pop {r3-r5, pc}
	.balign 4
_020275D0: .word 0x00001234
_020275D4: .word 0x00002345

	thumb_func_start FUN_020275D8
FUN_020275D8: ; 0x020275D8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027600 ; =0x00001234
	cmp r1, r0
	beq _020275EA
	ldr r0, _02027604 ; =0x00002345
	cmp r1, r0
	bne _020275EE
_020275EA:
	mov r0, #0x1
	b _020275F0
_020275EE:
	mov r0, #0x0
_020275F0:
	cmp r0, #0x0
	bne _020275F8
	bl ErrorHandling
_020275F8:
	add r0, r4, #0x4
	bl FUN_02027C84
	pop {r4, pc}
	.balign 4
_02027600: .word 0x00001234
_02027604: .word 0x00002345

	thumb_func_start FUN_02027608
FUN_02027608: ; 0x02027608
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027634 ; =0x00001234
	cmp r1, r0
	beq _0202761C
	ldr r0, _02027638 ; =0x00002345
	cmp r1, r0
	bne _02027620
_0202761C:
	mov r0, #0x1
	b _02027622
_02027620:
	mov r0, #0x0
_02027622:
	cmp r0, #0x0
	bne _0202762A
	bl ErrorHandling
_0202762A:
	add r0, r5, #0x4
	add r1, r4, #0x0
	bl FUN_02027C88
	pop {r3-r5, pc}
	.balign 4
_02027634: .word 0x00001234
_02027638: .word 0x00002345

	thumb_func_start FUN_0202763C
FUN_0202763C: ; 0x0202763C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027664 ; =0x00001234
	cmp r1, r0
	beq _0202764E
	ldr r0, _02027668 ; =0x00002345
	cmp r1, r0
	bne _02027652
_0202764E:
	mov r0, #0x1
	b _02027654
_02027652:
	mov r0, #0x0
_02027654:
	cmp r0, #0x0
	bne _0202765C
	bl ErrorHandling
_0202765C:
	add r0, r4, #0x4
	bl FUN_02027C98
	pop {r4, pc}
	.balign 4
_02027664: .word 0x00001234
_02027668: .word 0x00002345

	thumb_func_start FUN_0202766C
FUN_0202766C: ; 0x0202766C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027694 ; =0x00001234
	cmp r1, r0
	beq _0202767E
	ldr r0, _02027698 ; =0x00002345
	cmp r1, r0
	bne _02027682
_0202767E:
	mov r0, #0x1
	b _02027684
_02027682:
	mov r0, #0x0
_02027684:
	cmp r0, #0x0
	bne _0202768C
	bl ErrorHandling
_0202768C:
	add r4, #0x70
	ldrb r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02027694: .word 0x00001234
_02027698: .word 0x00002345

	thumb_func_start FUN_0202769C
FUN_0202769C: ; 0x0202769C
	ldr r3, _020276A4 ; =FUN_02013918
	add r0, #0x40
	mov r1, #0x0
	bx r3
	.balign 4
_020276A4: .word FUN_02013918

	thumb_func_start FUN_020276A8
FUN_020276A8: ; 0x020276A8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _020276D0 ; =0x00001234
	cmp r1, r0
	beq _020276BA
	ldr r0, _020276D4 ; =0x00002345
	cmp r1, r0
	bne _020276BE
_020276BA:
	mov r0, #0x1
	b _020276C0
_020276BE:
	mov r0, #0x0
_020276C0:
	cmp r0, #0x0
	bne _020276C8
	bl ErrorHandling
_020276C8:
	add r4, #0x71
	ldrb r0, [r4, #0x0]
	pop {r4, pc}
	nop
_020276D0: .word 0x00001234
_020276D4: .word 0x00002345

	thumb_func_start FUN_020276D8
FUN_020276D8: ; 0x020276D8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027708 ; =0x00001234
	cmp r1, r0
	beq _020276EA
	ldr r0, _0202770C ; =0x00002345
	cmp r1, r0
	bne _020276EE
_020276EA:
	mov r0, #0x1
	b _020276F0
_020276EE:
	mov r0, #0x0
_020276F0:
	cmp r0, #0x0
	bne _020276F8
	bl ErrorHandling
_020276F8:
	ldr r1, [r4, #0x0]
	ldr r0, _0202770C ; =0x00002345
	cmp r1, r0
	bne _02027704
	mov r0, #0x1
	pop {r4, pc}
_02027704:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_02027708: .word 0x00001234
_0202770C: .word 0x00002345

	thumb_func_start FUN_02027710
FUN_02027710: ; 0x02027710
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027738 ; =0x00001234
	cmp r1, r0
	beq _02027722
	ldr r0, _0202773C ; =0x00002345
	cmp r1, r0
	bne _02027726
_02027722:
	mov r0, #0x1
	b _02027728
_02027726:
	mov r0, #0x0
_02027728:
	cmp r0, #0x0
	bne _02027730
	bl ErrorHandling
_02027730:
	ldr r0, _0202773C ; =0x00002345
	str r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02027738: .word 0x00001234
_0202773C: .word 0x00002345

	thumb_func_start FUN_02027740
FUN_02027740: ; 0x02027740
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027770 ; =0x00001234
	cmp r1, r0
	beq _02027752
	ldr r0, _02027774 ; =0x00002345
	cmp r1, r0
	bne _02027756
_02027752:
	mov r0, #0x1
	b _02027758
_02027756:
	mov r0, #0x0
_02027758:
	cmp r0, #0x0
	bne _02027760
	bl ErrorHandling
_02027760:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x98
	bl memset
	ldr r0, _02027770 ; =0x00001234
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4
_02027770: .word 0x00001234
_02027774: .word 0x00002345

	thumb_func_start FUN_02027778
FUN_02027778: ; 0x02027778
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020277AC ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _0202778E
	ldr r0, _020277B0 ; =0x00002345
	cmp r1, r0
	bne _02027792
_0202778E:
	mov r0, #0x1
	b _02027794
_02027792:
	mov r0, #0x0
_02027794:
	cmp r0, #0x0
	bne _0202779C
	bl ErrorHandling
_0202779C:
	add r5, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D34
	pop {r4-r6, pc}
	nop
_020277AC: .word 0x00001234
_020277B0: .word 0x00002345

	thumb_func_start FUN_020277B4
FUN_020277B4: ; 0x020277B4
	push {r4-r7, lr}
	sub sp, #0x14
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x4]
	add r6, r2, #0x0
	bl FUN_02013ECC
	add r1, sp, #0xc
	strh r0, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x2]
	ldrh r0, [r1, #0x0]
	strh r0, [r1, #0x4]
	ldrh r0, [r1, #0x2]
	strh r0, [r1, #0x6]
	ldr r0, [r4, #0x4]
	bl FUN_02013F00
	str r0, [sp, #0x8]
	cmp r6, #0x14
	blt _020277E4
	bl ErrorHandling
_020277E4:
	add r1, sp, #0xc
	mov r0, #0x4
	ldrsh r1, [r1, r0]
	add r0, #0xfc
	cmp r1, r0
	blt _020277F4
	bl ErrorHandling
_020277F4:
	add r1, sp, #0xc
	mov r0, #0x6
	ldrsh r7, [r1, r0]
	add r0, #0xfa
	cmp r7, r0
	blt _02027804
	bl ErrorHandling
_02027804:
	mov r1, #0x7f
	ldr r0, [sp, #0x8]
	mvn r1, r1
	cmp r0, r1
	bgt _02027812
	bl ErrorHandling
_02027812:
	mov r0, #0x1
	lsl r0, r6
	ldr r1, [r5, #0x40]
	str r0, [sp, #0x4]
	tst r0, r1
	beq _02027822
	bl ErrorHandling
_02027822:
	ldr r1, [r5, #0x0]
	ldr r0, _02027874 ; =0x00001234
	cmp r1, r0
	beq _02027830
	ldr r0, _02027878 ; =0x00002345
	cmp r1, r0
	bne _02027834
_02027830:
	mov r0, #0x1
	b _02027836
_02027834:
	mov r0, #0x0
_02027836:
	cmp r0, #0x0
	bne _0202783E
	bl ErrorHandling
_0202783E:
	ldr r0, [sp, #0x8]
	add r1, r5, #0x0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r3, sp, #0xc
	mov r2, #0x4
	ldrsh r2, [r3, r2]
	lsl r3, r7, #0x18
	add r1, #0x44
	lsl r0, r6, #0x2
	add r0, r1, r0
	ldr r1, [r4, #0x0]
	lsl r2, r2, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02026DB0
	ldr r1, [r5, #0x40]
	ldr r0, [sp, #0x4]
	orr r0, r1
	str r0, [r5, #0x40]
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02027874: .word 0x00001234
_02027878: .word 0x00002345

	thumb_func_start FUN_0202787C
FUN_0202787C: ; 0x0202787C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020278A4 ; =0x00001234
	cmp r1, r0
	beq _02027890
	ldr r0, _020278A8 ; =0x00002345
	cmp r1, r0
	bne _02027894
_02027890:
	mov r0, #0x1
	b _02027896
_02027894:
	mov r0, #0x0
_02027896:
	cmp r0, #0x0
	bne _0202789E
	bl ErrorHandling
_0202789E:
	add r5, #0x94
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4
_020278A4: .word 0x00001234
_020278A8: .word 0x00002345

	thumb_func_start FUN_020278AC
FUN_020278AC: ; 0x020278AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020278D4 ; =0x00001234
	cmp r1, r0
	beq _020278C0
	ldr r0, _020278D8 ; =0x00002345
	cmp r1, r0
	bne _020278C4
_020278C0:
	mov r0, #0x1
	b _020278C6
_020278C4:
	mov r0, #0x0
_020278C6:
	cmp r0, #0x0
	bne _020278CE
	bl ErrorHandling
_020278CE:
	str r4, [r5, #0x4]
	pop {r3-r5, pc}
	nop
_020278D4: .word 0x00001234
_020278D8: .word 0x00002345

	thumb_func_start FUN_020278DC
FUN_020278DC: ; 0x020278DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202790C ; =0x00001234
	cmp r1, r0
	beq _020278F0
	ldr r0, _02027910 ; =0x00002345
	cmp r1, r0
	bne _020278F4
_020278F0:
	mov r0, #0x1
	b _020278F6
_020278F4:
	mov r0, #0x0
_020278F6:
	cmp r0, #0x0
	bne _020278FE
	bl ErrorHandling
_020278FE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x98
	bl memcpy
	pop {r3-r5, pc}
	nop
_0202790C: .word 0x00001234
_02027910: .word 0x00002345

	thumb_func_start FUN_02027914
FUN_02027914: ; 0x02027914
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202795C ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _0202792C
	ldr r0, _02027960 ; =0x00002345
	cmp r1, r0
	bne _02027930
_0202792C:
	mov r0, #0x1
	b _02027932
_02027930:
	mov r0, #0x0
_02027932:
	cmp r0, #0x0
	bne _0202793A
	bl ErrorHandling
_0202793A:
	add r1, sp, #0x4
	add r0, r4, #0x0
	add r1, #0x1
	add r2, sp, #0x4
	bl FUN_02026F3C
	add r5, #0x8
	str r6, [sp, #0x0]
	add r3, sp, #0x4
	ldrb r2, [r3, #0x1]
	ldrb r3, [r3, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02026CD0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_0202795C: .word 0x00001234
_02027960: .word 0x00002345

	thumb_func_start FUN_02027964
FUN_02027964: ; 0x02027964
	push {r4-r7, lr}
	sub sp, #0xc
	str r3, [sp, #0x4]
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	ldr r4, [sp, #0x24]
	cmp r6, #0x14
	blo _0202797A
	bl ErrorHandling
_0202797A:
	cmp r7, #0x64
	blo _02027982
	bl ErrorHandling
_02027982:
	mov r1, #0x1
	ldr r0, [sp, #0x4]
	lsl r1, r1, #0x8
	cmp r0, r1
	blt _02027990
	bl ErrorHandling
_02027990:
	add r0, sp, #0x10
	ldrb r1, [r0, #0x10]
	mov r0, #0x1
	lsl r0, r0, #0x8
	cmp r1, r0
	blt _020279A0
	bl ErrorHandling
_020279A0:
	mov r0, #0x7f
	mvn r0, r0
	cmp r4, r0
	bgt _020279AC
	bl ErrorHandling
_020279AC:
	mov r0, #0x1
	lsl r0, r6
	ldr r1, [r5, #0x40]
	str r0, [sp, #0x8]
	tst r0, r1
	beq _020279BC
	bl ErrorHandling
_020279BC:
	ldr r1, [r5, #0x0]
	ldr r0, _02027A0C ; =0x00001234
	cmp r1, r0
	beq _020279CA
	ldr r0, _02027A10 ; =0x00002345
	cmp r1, r0
	bne _020279CE
_020279CA:
	mov r0, #0x1
	b _020279D0
_020279CE:
	mov r0, #0x0
_020279D0:
	cmp r0, #0x0
	bne _020279D8
	bl ErrorHandling
_020279D8:
	mov r0, #0x38
	ldrsb r0, [r5, r0]
	cmp r0, r4
	blt _020279E6
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
_020279E6:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r3, sp, #0x10
	add r1, r5, #0x0
	ldrb r3, [r3, #0x10]
	add r1, #0x44
	lsl r0, r6, #0x2
	add r0, r1, r0
	ldr r2, [sp, #0x4]
	add r1, r7, #0x0
	bl FUN_02026DB0
	ldr r1, [r5, #0x40]
	ldr r0, [sp, #0x8]
	orr r0, r1
	str r0, [r5, #0x40]
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02027A0C: .word 0x00001234
_02027A10: .word 0x00002345

	thumb_func_start FUN_02027A14
FUN_02027A14: ; 0x02027A14
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x14
	blt _02027A22
	bl ErrorHandling
_02027A22:
	ldr r1, [r5, #0x0]
	ldr r0, _02027A50 ; =0x00001234
	cmp r1, r0
	beq _02027A30
	ldr r0, _02027A54 ; =0x00002345
	cmp r1, r0
	bne _02027A34
_02027A30:
	mov r0, #0x1
	b _02027A36
_02027A34:
	mov r0, #0x0
_02027A36:
	cmp r0, #0x0
	bne _02027A3E
	bl ErrorHandling
_02027A3E:
	mov r0, #0x1
	add r1, r0, #0x0
	ldr r2, [r5, #0x40]
	lsl r1, r4
	tst r1, r2
	bne _02027A4C
	mov r0, #0x0
_02027A4C:
	pop {r3-r5, pc}
	nop
_02027A50: .word 0x00001234
_02027A54: .word 0x00002345

	thumb_func_start FUN_02027A58
FUN_02027A58: ; 0x02027A58
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027A8C ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _02027A6E
	ldr r0, _02027A90 ; =0x00002345
	cmp r1, r0
	bne _02027A72
_02027A6E:
	mov r0, #0x1
	b _02027A74
_02027A72:
	mov r0, #0x0
_02027A74:
	cmp r0, #0x0
	bne _02027A7C
	bl ErrorHandling
_02027A7C:
	add r5, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D98
	pop {r4-r6, pc}
	nop
_02027A8C: .word 0x00001234
_02027A90: .word 0x00002345

	thumb_func_start FUN_02027A94
FUN_02027A94: ; 0x02027A94
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027ABC ; =0x00001234
	cmp r1, r0
	beq _02027AA6
	ldr r0, _02027AC0 ; =0x00002345
	cmp r1, r0
	bne _02027AAA
_02027AA6:
	mov r0, #0x1
	b _02027AAC
_02027AAA:
	mov r0, #0x0
_02027AAC:
	cmp r0, #0x0
	bne _02027AB4
	bl ErrorHandling
_02027AB4:
	add r4, #0x8
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_02027ABC: .word 0x00001234
_02027AC0: .word 0x00002345

	thumb_func_start FUN_02027AC4
FUN_02027AC4: ; 0x02027AC4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x14
	blt _02027AD2
	bl ErrorHandling
_02027AD2:
	mov r0, #0x1
	ldr r1, [r5, #0x40]
	lsl r0, r4
	tst r0, r1
	bne _02027AE0
	bl ErrorHandling
_02027AE0:
	ldr r1, [r5, #0x0]
	ldr r0, _02027B04 ; =0x00001234
	cmp r1, r0
	beq _02027AEE
	ldr r0, _02027B08 ; =0x00002345
	cmp r1, r0
	bne _02027AF2
_02027AEE:
	mov r0, #0x1
	b _02027AF4
_02027AF2:
	mov r0, #0x0
_02027AF4:
	cmp r0, #0x0
	bne _02027AFC
	bl ErrorHandling
_02027AFC:
	add r5, #0x44
	lsl r0, r4, #0x2
	add r0, r5, r0
	pop {r3-r5, pc}
	.balign 4
_02027B04: .word 0x00001234
_02027B08: .word 0x00002345

	thumb_func_start FUN_02027B0C
FUN_02027B0C: ; 0x02027B0C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027B3C ; =0x00001234
	cmp r1, r0
	beq _02027B20
	ldr r0, _02027B40 ; =0x00002345
	cmp r1, r0
	bne _02027B24
_02027B20:
	mov r0, #0x1
	b _02027B26
_02027B24:
	mov r0, #0x0
_02027B26:
	cmp r0, #0x0
	bne _02027B2E
	bl ErrorHandling
_02027B2E:
	add r5, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02027C88
	pop {r3-r5, pc}
	nop
_02027B3C: .word 0x00001234
_02027B40: .word 0x00002345

	thumb_func_start FUN_02027B44
FUN_02027B44: ; 0x02027B44
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027B70 ; =0x00001234
	cmp r1, r0
	beq _02027B56
	ldr r0, _02027B74 ; =0x00002345
	cmp r1, r0
	bne _02027B5A
_02027B56:
	mov r0, #0x1
	b _02027B5C
_02027B5A:
	mov r0, #0x0
_02027B5C:
	cmp r0, #0x0
	bne _02027B64
	bl ErrorHandling
_02027B64:
	add r4, #0x8
	add r0, r4, #0x0
	bl FUN_02027C98
	pop {r4, pc}
	nop
_02027B70: .word 0x00001234
_02027B74: .word 0x00002345

	thumb_func_start FUN_02027B78
FUN_02027B78: ; 0x02027B78
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027BD4 ; =0x00001234
	cmp r1, r0
	beq _02027B8E
	ldr r0, _02027BD8 ; =0x00002345
	cmp r1, r0
	bne _02027B92
_02027B8E:
	mov r0, #0x1
	b _02027B94
_02027B92:
	mov r0, #0x0
_02027B94:
	cmp r0, #0x0
	bne _02027B9C
	bl ErrorHandling
_02027B9C:
	mov r1, #0x1
	str r1, [sp, #0x0]
	ldr r0, [r5, #0x8]
	mov r2, #0x0
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r0, [r5, #0xc]
	add r3, r2, #0x0
	str r0, [sp, #0xc]
	ldrh r1, [r5, #0x10]
	add r0, r4, #0x0
	bl CreateMon
	add r2, r5, #0x0
	add r0, r4, #0x0
	mov r1, #0x74
	add r2, #0x12
	bl SetMonDataEncrypted
	add r5, #0x3b
	add r0, r4, #0x0
	mov r1, #0x70
	add r2, r5, #0x0
	bl SetMonDataEncrypted
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_02027BD4: .word 0x00001234
_02027BD8: .word 0x00002345

	thumb_func_start FUN_02027BDC
FUN_02027BDC: ; 0x02027BDC
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x14
	blt _02027BEA
	bl ErrorHandling
_02027BEA:
	mov r0, #0x1
	ldr r1, [r5, #0x40]
	lsl r0, r4
	tst r0, r1
	bne _02027BF8
	bl ErrorHandling
_02027BF8:
	ldr r1, [r5, #0x0]
	ldr r0, _02027C20 ; =0x00001234
	cmp r1, r0
	beq _02027C06
	ldr r0, _02027C24 ; =0x00002345
	cmp r1, r0
	bne _02027C0A
_02027C06:
	mov r0, #0x1
	b _02027C0C
_02027C0A:
	mov r0, #0x0
_02027C0C:
	cmp r0, #0x0
	bne _02027C14
	bl ErrorHandling
_02027C14:
	add r5, #0x44
	lsl r0, r4, #0x2
	add r0, r5, r0
	bl FUN_02027CF8
	pop {r3-r5, pc}
	.balign 4
_02027C20: .word 0x00001234
_02027C24: .word 0x00002345

	thumb_func_start FUN_02027C28
FUN_02027C28: ; 0x02027C28
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027C50 ; =0x00001234
	cmp r1, r0
	beq _02027C3A
	ldr r0, _02027C54 ; =0x00002345
	cmp r1, r0
	bne _02027C3E
_02027C3A:
	mov r0, #0x1
	b _02027C40
_02027C3E:
	mov r0, #0x0
_02027C40:
	cmp r0, #0x0
	bne _02027C48
	bl ErrorHandling
_02027C48:
	add r4, #0x94
	ldrb r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02027C50: .word 0x00001234
_02027C54: .word 0x00002345

	thumb_func_start FUN_02027C58
FUN_02027C58: ; 0x02027C58
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027C7C ; =0x00001234
	cmp r1, r0
	beq _02027C6A
	ldr r0, _02027C80 ; =0x00002345
	cmp r1, r0
	bne _02027C6E
_02027C6A:
	mov r0, #0x1
	b _02027C70
_02027C6E:
	mov r0, #0x0
_02027C70:
	cmp r0, #0x0
	bne _02027C78
	bl ErrorHandling
_02027C78:
	ldr r0, [r4, #0x4]
	pop {r4, pc}
	.balign 4
_02027C7C: .word 0x00001234
_02027C80: .word 0x00002345

	thumb_func_start FUN_02027C84
FUN_02027C84: ; 0x02027C84
	ldrh r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02027C88
FUN_02027C88: ; 0x02027C88
	add r2, r0, #0x0
	ldr r3, _02027C94 ; =FUN_02021E28
	add r2, #0x20
	add r0, r1, #0x0
	add r1, r2, #0x0
	bx r3
	.balign 4
_02027C94: .word FUN_02021E28

	thumb_func_start FUN_02027C98
FUN_02027C98: ; 0x02027C98
	add r0, #0x34
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02027CA0
FUN_02027CA0: ; 0x02027CA0
	mov r1, #0x30
	ldrsb r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start FUN_02027CA8
FUN_02027CA8: ; 0x02027CA8
	add r0, #0x31
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02027CB0
FUN_02027CB0: ; 0x02027CB0
	add r0, #0x32
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02027CB8
FUN_02027CB8: ; 0x02027CB8
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	mov r1, #0x1
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r5, #0x0]
	mov r2, #0x0
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r0, [r5, #0x4]
	add r3, r2, #0x0
	str r0, [sp, #0xc]
	ldrh r1, [r5, #0x8]
	add r0, r4, #0x0
	bl CreateMon
	add r2, r5, #0x0
	add r0, r4, #0x0
	mov r1, #0x74
	add r2, #0xa
	bl SetMonDataEncrypted
	add r5, #0x33
	add r0, r4, #0x0
	mov r1, #0x70
	add r2, r5, #0x0
	bl SetMonDataEncrypted
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02027CF8
FUN_02027CF8: ; 0x02027CF8
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02027CFC
FUN_02027CFC: ; 0x02027CFC
	ldrb r0, [r0, #0x1]
	bx lr

	thumb_func_start FUN_02027D00
FUN_02027D00: ; 0x02027D00
	ldrb r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02027D04
FUN_02027D04: ; 0x02027D04
	mov r1, #0x3
	ldrsb r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start FUN_02027D0C
FUN_02027D0C: ; 0x02027D0C
	push {r4-r7, lr}
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0xc
	add r7, r0, #0x0
	mov r0, #0x1
	add r4, r1, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_0202729C
	cmp r0, #0x1
	bne _02027D6A
	ldr r1, _02027D78 ; =0xEDB88320
	add r0, sp, #0x4
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x4
	add r1, r4, #0x0
	mov r2, #0x74
	bl MATH_CalcCRC32
	add r6, r0, #0x0
	mov r5, #0x0
_02027D3C:
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl FUN_02027008
	add r4, r0, #0x0
	ldr r1, _02027D78 ; =0xEDB88320
	add r0, sp, #0x4
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x4
	add r1, r4, #0x0
	mov r2, #0x74
	bl MATH_CalcCRC32
	cmp r0, r6
	bne _02027D62
	mov r0, #0x0
	str r0, [sp, #0x0]
	b _02027D6E
_02027D62:
	add r5, r5, #0x1
	cmp r5, #0xb
	blt _02027D3C
	b _02027D6E
_02027D6A:
	mov r0, #0x0
	str r0, [sp, #0x0]
_02027D6E:
	ldr r0, [sp, #0x0]
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02027D78: .word 0xEDB88320

	thumb_func_start FUN_02027D7C
FUN_02027D7C: ; 0x02027D7C
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	mov r7, #0x0
	ldr r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r5, r2, #0x0
	add r6, r7, #0x0
	str r3, [sp, #0x8]
	cmp r0, #0x0
	ble _02027DB6
	add r4, r3, #0x0
_02027D94:
	ldr r0, [sp, #0x4]
	cmp r6, r0
	beq _02027DAC
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02027DAC
	add r0, r5, #0x0
	bl FUN_02027D0C
	cmp r0, #0x1
	bne _02027DAC
	add r7, r7, #0x1
_02027DAC:
	ldr r0, [sp, #0x0]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _02027D94
_02027DB6:
	mov r4, #0xa
_02027DB8:
	add r1, r4, r7
	cmp r1, #0xb
	bge _02027DD6
	add r0, r5, #0x0
	bl FUN_02027008
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02027008
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020274B8
_02027DD6:
	sub r4, r4, #0x1
	cmp r4, #0x1
	bge _02027DB8
	ldr r0, [sp, #0x0]
	mov r6, #0x1
	mov r4, #0x0
	cmp r0, #0x0
	ble _02027E1E
_02027DE6:
	ldr r0, [sp, #0x4]
	cmp r4, r0
	beq _02027E10
	ldr r0, [sp, #0x8]
	ldr r7, [r0, #0x0]
	cmp r7, #0x0
	beq _02027E10
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02027D0C
	cmp r0, #0x1
	bne _02027E10
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02027008
	add r1, r7, #0x0
	add r6, r6, #0x1
	bl FUN_020274B8
_02027E10:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r0, r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x0]
	cmp r4, r0
	blt _02027DE6
_02027E1E:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02027E24
FUN_02027E24: ; 0x02027E24
	ldr r3, _02027E2C ; =FUN_02022610
	mov r1, #0xe
	bx r3
	nop
_02027E2C: .word FUN_02022610
