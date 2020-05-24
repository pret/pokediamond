	.include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020EE940
UNK_020EE940: ; 0x020EE940
	.short 0x01EA, 0x0097, 0x00F9, 0x00FA, 0x00FB, 0x0181, 0x0182, 0x01E9
	.short 0x01EA, 0x01EB, 0x01EC, 0x01ED

	.text

	thumb_func_start FUN_02023C40
FUN_02023C40: ; 0x02023C40
	mov r0, #0x1e
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02023C48
FUN_02023C48: ; 0x02023C48
	push {r4, lr}
	mov r2, #0x1e
	add r4, r0, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl memset
	add r0, r4, #0x0
	bl FUN_020669A0
	add r0, r4, #0x0
	add r0, #0xec
	bl FUN_020669A0
	mov r0, #0x76
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, r0, #0x4
	strb r1, [r4, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02023C74
FUN_02023C74: ; 0x02023C74
	mov r2, #0xec
	mul r2, r1
	add r0, r0, r2
	bx lr

	thumb_func_start FUN_02023C7C
FUN_02023C7C: ; 0x02023C7C
	bx lr
	.balign 4

	thumb_func_start FUN_02023C80
FUN_02023C80: ; 0x02023C80
	add r0, #0x88
	bx lr

	thumb_func_start FUN_02023C84
FUN_02023C84: ; 0x02023C84
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023C8C
FUN_02023C8C: ; 0x02023C8C
	bx lr
	.balign 4

	thumb_func_start FUN_02023C90
FUN_02023C90: ; 0x02023C90
	mov r1, #0x76
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start FUN_02023C98
FUN_02023C98: ; 0x02023C98
	mov r1, #0x77
	lsl r1, r1, #0x2
	ldrb r0, [r0, r1]
	bx lr

	thumb_func_start FUN_02023CA0
FUN_02023CA0: ; 0x02023CA0
	add r0, #0xe8
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023CA8
FUN_02023CA8: ; 0x02023CA8
	add r2, r0, #0x0
	add r2, #0xe8
	ldr r2, [r2, #0x0]
	add r0, #0xe8
	add r1, r2, r1
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023CB8
FUN_02023CB8: ; 0x02023CB8
	mov r2, #0x76
	lsl r2, r2, #0x2
	str r1, [r0, r2]
	bx lr

	thumb_func_start FUN_02023CC0
FUN_02023CC0: ; 0x02023CC0
	mov r2, #0x77
	lsl r2, r2, #0x2
	strb r1, [r0, r2]
	bx lr

	thumb_func_start FUN_02023CC8
FUN_02023CC8: ; 0x02023CC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0xc
	mov r2, #0x0
	bl FUN_020672BC
	add r5, #0xec
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xc
	mov r2, #0x0
	bl FUN_020672BC
	cmp r4, r0
	beq _02023CEA
	mov r0, #0x1
	pop {r3-r5, pc}
_02023CEA:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02023CF0
FUN_02023CF0: ; 0x02023CF0
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0x1d
_02023CF8:
	ldmia r3!, {r0-r1}
	stmia r4!, {r0-r1}
	sub r2, r2, #0x1
	bne _02023CF8
	ldr r0, [r3, #0x0]
	str r0, [r4, #0x0]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02023D08
FUN_02023D08: ; 0x02023D08
	push {r3-r4}
	mov r1, #0x0
	add r2, r0, #0x0
	add r4, r1, #0x0
_02023D10:
	add r1, r1, #0x1
	strh r4, [r2, #0x38]
	add r2, r2, #0x2
	cmp r1, #0x8
	blt _02023D10
	add r3, r0, #0x0
	mov r2, #0x0
_02023D1E:
	add r1, r3, #0x0
	add r1, #0x48
	add r4, r4, #0x1
	add r3, r3, #0x2
	strh r2, [r1, #0x0]
	cmp r4, #0xb
	blt _02023D1E
	ldr r1, _02023D38 ; =0x0000FFFF
	strh r1, [r0, #0x38]
	add r0, #0x48
	strh r1, [r0, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4
_02023D38: .word 0x0000FFFF

	thumb_func_start FUN_02023D3C
FUN_02023D3C: ; 0x02023D3C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020669A0
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0xe8
	add r4, #0x88
	str r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_02023D08
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02023D58
FUN_02023D58: ; 0x02023D58
	ldr r3, _02023D60 ; =FUN_02022610
	mov r1, #0x8
	bx r3
	nop
_02023D60: .word FUN_02022610

	thumb_func_start FUN_02023D64
FUN_02023D64: ; 0x02023D64
	mov r0, #0x4f
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_02023D6C
FUN_02023D6C: ; 0x02023D6C
	push {r4, lr}
	mov r1, #0x4f
	lsl r1, r1, #0x2
	bl FUN_02016998
	add r4, r0, #0x0
	bl FUN_02024378
	add r0, r4, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02023D80
FUN_02023D80: ; 0x02023D80
	ldr r3, _02023D88 ; =MI_CpuCopy8
	mov r2, #0x4f
	lsl r2, r2, #0x2
	bx r3
	.balign 4
_02023D88: .word MI_CpuCopy8

	thumb_func_start FUN_02023D8C
FUN_02023D8C: ; 0x02023D8C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02023DE8 ; =0x000001A6
	add r4, r1, #0x0
	cmp r4, r0
	beq _02023DA2
	add r0, r0, #0x1
	cmp r4, r0
	beq _02023DA2
	bl ErrorHandling
_02023DA2:
	lsl r1, r4, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x0
	bne _02023DB4
	mov r0, #0x0
	pop {r3-r5, pc}
_02023DB4:
	ldr r0, _02023DE8 ; =0x000001A6
	cmp r4, r0
	bne _02023DBE
	sub r0, #0x9e
	b _02023DC0
_02023DBE:
	sub r0, #0x9d
_02023DC0:
	add r0, r5, r0
	ldrb r1, [r0, #0x0]
	mov r2, #0x1
	add r0, r1, #0x0
	tst r0, r2
	bne _02023DCE
	mov r2, #0x0
_02023DCE:
	mov r0, #0x2
	tst r0, r1
	beq _02023DD8
	mov r0, #0x1
	b _02023DDA
_02023DD8:
	mov r0, #0x0
_02023DDA:
	cmp r2, r0
	bne _02023DE2
	mov r0, #0x1
	pop {r3-r5, pc}
_02023DE2:
	mov r0, #0x2
	pop {r3-r5, pc}
	nop
_02023DE8: .word 0x000001A6

	thumb_func_start FUN_02023DEC
FUN_02023DEC: ; 0x02023DEC
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _02023E6C ; =0x000001A6
	add r6, r1, #0x0
	add r5, r2, #0x0
	cmp r6, r0
	beq _02023E04
	add r0, r0, #0x1
	cmp r6, r0
	beq _02023E04
	bl ErrorHandling
_02023E04:
	lsl r1, r6, #0x10
	add r0, r7, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x0
	bne _02023E16
	mov r0, #0x0
	pop {r3-r7, pc}
_02023E16:
	ldr r0, _02023E6C ; =0x000001A6
	cmp r6, r0
	bne _02023E20
	sub r0, #0x9e
	b _02023E22
_02023E20:
	sub r0, #0x9d
_02023E22:
	add r4, r7, r0
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_02023D8C
	mov r6, #0x0
	cmp r0, #0x0
	bls _02023E66
	mov r1, #0x1
_02023E34:
	add r2, r6, #0x1
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	sub r2, r2, #0x1
	lsl r2, r2, #0x10
	lsr r3, r2, #0x10
	add r7, r3, #0x0
	mov r2, #0x7
	asr r3, r3, #0x3
	and r7, r2
	add r2, r1, #0x0
	ldrb r3, [r4, r3]
	lsl r2, r7
	tst r2, r3
	beq _02023E56
	add r2, r1, #0x0
	b _02023E58
_02023E56:
	mov r2, #0x0
_02023E58:
	cmp r2, r5
	bne _02023E60
	mov r0, #0x1
	pop {r3-r7, pc}
_02023E60:
	add r6, r6, #0x1
	cmp r6, r0
	blo _02023E34
_02023E66:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02023E6C: .word 0x000001A6

	thumb_func_start FUN_02023E70
FUN_02023E70: ; 0x02023E70
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, _02023F28 ; =0x000001A6
	add r5, r1, #0x0
	add r7, r2, #0x0
	cmp r5, r0
	beq _02023E88
	add r0, r0, #0x1
	cmp r5, r0
	beq _02023E88
	bl ErrorHandling
_02023E88:
	lsl r2, r7, #0x18
	add r0, r6, #0x0
	add r1, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02023DEC
	cmp r0, #0x0
	bne _02023F26
	ldr r0, _02023F28 ; =0x000001A6
	cmp r5, r0
	bne _02023EA2
	sub r0, #0x9e
	b _02023EA4
_02023EA2:
	sub r0, #0x9d
_02023EA4:
	add r4, r6, r0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02023D8C
	add r5, r0, #0x0
	cmp r5, #0x2
	bge _02023F26
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x2
	blo _02023EC6
	bl ErrorHandling
_02023EC6:
	sub r0, r6, #0x1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r2, r1, #0x0
	mov r0, #0x7
	and r2, r0
	asr r1, r1, #0x3
	mov r3, #0x1
	lsl r3, r2
	ldrb r0, [r4, r1]
	mvn r3, r3
	and r0, r3
	strb r0, [r4, r1]
	lsl r0, r7, #0x18
	lsr r6, r0, #0x18
	add r0, r6, #0x0
	ldrb r3, [r4, r1]
	lsl r0, r2
	orr r0, r3
	strb r0, [r4, r1]
	cmp r5, #0x0
	bne _02023F26
	add r0, r5, #0x2
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r6, #0x2
	blo _02023F00
	bl ErrorHandling
_02023F00:
	sub r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r0, #0x7
	add r1, r2, #0x0
	and r1, r0
	asr r0, r2, #0x3
	mov r2, #0x1
	lsl r2, r1
	ldrb r3, [r4, r0]
	mvn r2, r2
	and r2, r3
	strb r2, [r4, r0]
	add r2, r6, #0x0
	ldrb r3, [r4, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strb r1, [r4, r0]
_02023F26:
	pop {r3-r7, pc}
	.balign 4
_02023F28: .word 0x000001A6

	thumb_func_start FUN_02023F2C
FUN_02023F2C: ; 0x02023F2C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x67
	add r4, r1, #0x0
	lsl r0, r0, #0x2
	cmp r4, r0
	beq _02023F44
	add r0, r0, #0x1
	cmp r4, r0
	beq _02023F44
	bl ErrorHandling
_02023F44:
	lsl r1, r4, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x0
	bne _02023F56
	mov r0, #0x0
	pop {r3-r5, pc}
_02023F56:
	mov r0, #0x67
	lsl r0, r0, #0x2
	cmp r4, r0
	bne _02023F62
	sub r0, #0x92
	b _02023F64
_02023F62:
	sub r0, #0x91
_02023F64:
	add r1, r5, r0
	mov r0, #0x0
	mov r3, #0x3
_02023F6A:
	lsl r2, r0, #0x10
	lsr r5, r2, #0x10
	asr r2, r5, #0x2
	ldrb r4, [r1, r2]
	lsl r2, r5, #0x1e
	lsr r2, r2, #0x1d
	asr r4, r2
	add r2, r4, #0x0
	and r2, r3
	cmp r2, #0x3
	beq _02023F86
	add r0, r0, #0x1
	cmp r0, #0x3
	blt _02023F6A
_02023F86:
	pop {r3-r5, pc}

	thumb_func_start FUN_02023F88
FUN_02023F88: ; 0x02023F88
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r0, #0x67
	add r5, r1, #0x0
	lsl r0, r0, #0x2
	add r4, r2, #0x0
	cmp r5, r0
	beq _02023FA2
	add r0, r0, #0x1
	cmp r5, r0
	beq _02023FA2
	bl ErrorHandling
_02023FA2:
	lsl r1, r5, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x0
	bne _02023FB4
	mov r0, #0x0
	pop {r4-r6, pc}
_02023FB4:
	mov r0, #0x67
	lsl r0, r0, #0x2
	cmp r5, r0
	bne _02023FC0
	sub r0, #0x92
	b _02023FC2
_02023FC0:
	sub r0, #0x91
_02023FC2:
	add r1, r6, r0
	mov r0, #0x0
	mov r3, #0x3
_02023FC8:
	lsl r2, r0, #0x10
	lsr r6, r2, #0x10
	asr r2, r6, #0x2
	ldrb r5, [r1, r2]
	lsl r2, r6, #0x1e
	lsr r2, r2, #0x1d
	asr r5, r2
	add r2, r5, #0x0
	and r2, r3
	cmp r2, r4
	bne _02023FE2
	mov r0, #0x1
	pop {r4-r6, pc}
_02023FE2:
	add r0, r0, #0x1
	cmp r0, #0x3
	blt _02023FC8
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02023FEC
FUN_02023FEC: ; 0x02023FEC
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r0, #0x67
	add r5, r1, #0x0
	lsl r0, r0, #0x2
	add r7, r2, #0x0
	cmp r5, r0
	beq _02024006
	add r0, r0, #0x1
	cmp r5, r0
	beq _02024006
	bl ErrorHandling
_02024006:
	lsl r2, r7, #0x18
	add r0, r6, #0x0
	add r1, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02023F88
	cmp r0, #0x0
	bne _02024064
	mov r0, #0x67
	lsl r0, r0, #0x2
	cmp r5, r0
	bne _02024022
	sub r0, #0x92
	b _02024024
_02024022:
	sub r0, #0x91
_02024024:
	add r4, r6, r0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02023F2C
	add r5, r0, #0x0
	cmp r5, #0x3
	bge _02024064
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x4
	blo _02024040
	bl ErrorHandling
_02024040:
	lsl r0, r5, #0x10
	lsr r2, r0, #0x10
	lsl r0, r2, #0x1e
	lsr r1, r0, #0x1d
	asr r0, r2, #0x2
	mov r2, #0x3
	lsl r2, r1
	ldrb r3, [r4, r0]
	mvn r2, r2
	and r2, r3
	strb r2, [r4, r0]
	lsl r2, r7, #0x18
	lsr r2, r2, #0x18
	ldrb r3, [r4, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strb r1, [r4, r0]
_02024064:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02024068
FUN_02024068: ; 0x02024068
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r6, #0x4
	blo _02024078
	bl ErrorHandling
_02024078:
	cmp r4, #0xf
	bls _02024080
	bl ErrorHandling
_02024080:
	cmp r6, #0x2
	bhs _0202409E
	lsl r0, r6, #0x2
	add r0, #0x18
	mov r1, #0xf
	lsl r1, r0
	ldr r2, [r5, #0x40]
	mvn r1, r1
	and r2, r1
	add r1, r4, #0x0
	lsl r1, r0
	add r0, r2, #0x0
	orr r0, r1
	str r0, [r5, #0x40]
	pop {r4-r6, pc}
_0202409E:
	sub r0, r6, #0x2
	lsl r0, r0, #0x18
	add r1, r5, #0x0
	lsr r0, r0, #0x16
	add r1, #0x80
	ldr r2, [r1, #0x0]
	add r0, #0x18
	mov r1, #0xf
	lsl r1, r0
	mvn r1, r1
	and r2, r1
	add r1, r5, #0x0
	add r1, #0x80
	str r2, [r1, #0x0]
	add r1, r5, #0x0
	add r1, #0x80
	ldr r2, [r1, #0x0]
	add r1, r4, #0x0
	lsl r1, r0
	add r0, r2, #0x0
	orr r0, r1
	add r5, #0x80
	str r0, [r5, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020240D0
FUN_020240D0: ; 0x020240D0
	push {r3-r6}
	mov r3, #0xf
	mov r1, #0x0
	add r4, r3, #0x0
_020240D8:
	lsl r2, r1, #0x18
	lsr r6, r2, #0x18
	cmp r6, #0x2
	bhs _020240EE
	lsl r2, r6, #0x2
	ldr r5, [r0, #0x40]
	add r2, #0x18
	lsr r5, r2
	add r2, r5, #0x0
	and r2, r4
	b _02024102
_020240EE:
	add r2, r0, #0x0
	add r2, #0x80
	ldr r5, [r2, #0x0]
	sub r2, r6, #0x2
	lsl r2, r2, #0x18
	lsr r2, r2, #0x16
	add r2, #0x18
	lsr r5, r2
	add r2, r5, #0x0
	and r2, r3
_02024102:
	cmp r2, #0xf
	beq _0202410C
	add r1, r1, #0x1
	cmp r1, #0x4
	blt _020240D8
_0202410C:
	add r0, r1, #0x0
	pop {r3-r6}
	bx lr
	.balign 4

	thumb_func_start FUN_02024114
FUN_02024114: ; 0x02024114
	push {r4-r7}
	mov r2, #0xf
	mov r6, #0x0
	add r3, r2, #0x0
_0202411C:
	lsl r4, r6, #0x18
	lsr r5, r4, #0x18
	cmp r5, #0x2
	bhs _02024134
	ldr r7, [r0, #0x40]
	lsl r4, r5, #0x2
	add r4, #0x18
	add r5, r7, #0x0
	lsr r5, r4
	add r4, r5, #0x0
	and r4, r3
	b _02024146
_02024134:
	add r4, r0, #0x0
	sub r5, r5, #0x2
	add r4, #0x80
	lsl r5, r5, #0x18
	lsr r5, r5, #0x16
	ldr r4, [r4, #0x0]
	add r5, #0x18
	lsr r4, r5
	and r4, r2
_02024146:
	cmp r1, r4
	bne _02024150
	mov r0, #0x1
	pop {r4-r7}
	bx lr
_02024150:
	add r6, r6, #0x1
	cmp r6, #0x4
	blt _0202411C
	mov r0, #0x0
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_0202415C
FUN_0202415C: ; 0x0202415C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, _02024198 ; =0x00000182
	cmp r6, r0
	bne _02024196
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02024114
	cmp r0, #0x0
	bne _02024196
	add r0, r5, #0x0
	bl FUN_020240D0
	add r2, r0, #0x0
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	bl FUN_02024068
_02024196:
	pop {r4-r6, pc}
	.balign 4
_02024198: .word 0x00000182

	thumb_func_start FUN_0202419C
FUN_0202419C: ; 0x0202419C
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r4, #0x0
	mov r6, #0xf
_020241A4:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl FUN_02024068
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _020241A4
	pop {r4-r6, pc}

	thumb_func_start FUN_020241B8
FUN_020241B8: ; 0x020241B8
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xc9
	bne _02024210
	add r0, r2, #0x0
	bl FUN_020690CC
	lsl r1, r0, #0x18
	lsr r3, r1, #0x18
	mov r1, #0x43
	mov r4, #0x0
	add r6, r5, #0x0
	lsl r1, r1, #0x2
_020241D4:
	ldrb r2, [r6, r1]
	cmp r3, r2
	bne _020241DE
	mov r1, #0x1
	b _020241E8
_020241DE:
	add r4, r4, #0x1
	add r6, r6, #0x1
	cmp r4, #0x1c
	blt _020241D4
	mov r1, #0x0
_020241E8:
	cmp r1, #0x0
	bne _02024290
	mov r1, #0x43
	mov r3, #0x0
	add r4, r5, #0x0
	lsl r1, r1, #0x2
_020241F4:
	ldrb r2, [r4, r1]
	cmp r2, #0xff
	beq _02024202
	add r3, r3, #0x1
	add r4, r4, #0x1
	cmp r3, #0x1c
	blt _020241F4
_02024202:
	cmp r3, #0x1c
	bge _02024290
	mov r1, #0x43
	add r2, r5, r3
	lsl r1, r1, #0x2
	strb r0, [r2, r1]
	pop {r4-r6, pc}
_02024210:
	mov r6, #0x67
	lsl r6, r6, #0x2
	cmp r4, r6
	bne _0202422E
	add r0, r2, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02023FEC
	pop {r4-r6, pc}
_0202422E:
	add r3, r6, #0x1
	cmp r4, r3
	bne _0202424A
	add r0, r2, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02023FEC
	pop {r4-r6, pc}
_0202424A:
	add r3, r6, #0x0
	add r3, #0xa
	cmp r4, r3
	bne _02024268
	add r0, r2, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02023E70
	pop {r4-r6, pc}
_02024268:
	add r3, r6, #0x0
	add r3, #0xb
	cmp r4, r3
	bne _02024286
	add r0, r2, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02023E70
	pop {r4-r6, pc}
_02024286:
	sub r6, #0x1a
	cmp r4, r6
	bne _02024290
	bl FUN_0202415C
_02024290:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02024294
FUN_02024294: ; 0x02024294
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r0, r1, #0x0
	bl FUN_02087A50
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02087A1C
	cmp r4, #0xe
	beq _020242C0
	cmp r0, #0x6
	beq _020242C0
	ldr r1, _020242C4 ; =0x00000129
	add r3, r5, r1
	ldrb r2, [r3, r4]
	mov r1, #0x1
	lsl r1, r0
	add r0, r2, #0x0
	orr r0, r1
	strb r0, [r3, r4]
_020242C0:
	pop {r4-r6, pc}
	nop
_020242C4: .word 0x00000129

	thumb_func_start FUN_020242C8
FUN_020242C8: ; 0x020242C8
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x12
	add r4, r2, #0x0
	bl FUN_02068678
	cmp r0, #0xff
	bne _020242EA
	cmp r4, #0x0
	bne _020242E4
	mov r0, #0x2
	pop {r4-r6, pc}
_020242E4:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_020242EA:
	sub r0, r6, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r1, #0x1
	mov r0, #0x7
	add r3, r2, #0x0
	and r3, r0
	add r0, r1, #0x0
	lsl r0, r3
	asr r3, r2, #0x3
	add r3, r5, r3
	add r3, #0x84
	ldrb r3, [r3, #0x0]
	tst r0, r3
	bne _0202430A
	mov r1, #0x0
_0202430A:
	lsl r0, r1, #0x18
	lsr r1, r0, #0x18
	cmp r4, #0x1
	bne _0202433A
	add r4, r2, #0x0
	asr r2, r2, #0x3
	add r2, r5, r2
	mov r0, #0x7
	add r2, #0xc4
	mov r3, #0x1
	and r4, r0
	add r0, r3, #0x0
	ldrb r2, [r2, #0x0]
	lsl r0, r4
	tst r0, r2
	bne _0202432C
	mov r3, #0x0
_0202432C:
	lsl r0, r3, #0x18
	lsr r0, r0, #0x18
	cmp r0, r1
	bne _0202433C
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_0202433A:
	add r0, r1, #0x0
_0202433C:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02024340
FUN_02024340: ; 0x02024340
	push {r4-r5}
	mov r3, #0x0
	ldr r5, _02024360 ; =UNK_020EE940 + 2
	mov r4, #0x1
	add r1, r3, #0x0
_0202434A:
	ldrh r2, [r5, #0x0]
	cmp r0, r2
	bne _02024352
	add r4, r1, #0x0
_02024352:
	add r3, r3, #0x1
	add r5, r5, #0x2
	cmp r3, #0xb
	blt _0202434A
	add r0, r4, #0x0
	pop {r4-r5}
	bx lr
	.balign 4
_02024360: .word UNK_020EE940 + 2

	thumb_func_start FUN_02024364
FUN_02024364: ; 0x02024364
	ldr r1, _02024374 ; =0x000001EA
	mov r2, #0x1
	cmp r0, r1
	bne _0202436E
	mov r2, #0x0
_0202436E:
	add r0, r2, #0x0
	bx lr
	nop
_02024374: .word 0x000001EA

	thumb_func_start FUN_02024378
FUN_02024378: ; 0x02024378
	push {r4, lr}
	mov r2, #0x4f
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r4, r0, #0x0
	bl memset
	ldr r0, _020243C0 ; =0xBEEFCAFE
	mov r1, #0x0
	str r0, [r4, #0x0]
	ldr r0, _020243C4 ; =0x00000139
	mov r2, #0x1c
	strb r1, [r4, r0]
	sub r0, #0x2d
	add r0, r4, r0
	mov r1, #0xff
	bl memset
	mov r1, #0xff
	add r0, r1, #0x0
	add r0, #0x9
	strb r1, [r4, r0]
	add r0, r1, #0x0
	add r0, #0xa
	strb r1, [r4, r0]
	add r0, r1, #0x0
	add r0, #0xb
	strb r1, [r4, r0]
	add r0, r1, #0x0
	add r0, #0xc
	strb r1, [r4, r0]
	add r0, r4, #0x0
	bl FUN_0202419C
	pop {r4, pc}
	nop
_020243C0: .word 0xBEEFCAFE
_020243C4: .word 0x00000139

	thumb_func_start FUN_020243C8
FUN_020243C8: ; 0x020243C8
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, _020243FC ; =0xBEEFCAFE
	cmp r1, r0
	beq _020243D8
	bl ErrorHandling
_020243D8:
	ldr r7, _02024400 ; =0x000001ED
	mov r5, #0x0
	mov r4, #0x1
_020243DE:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_02024594
	cmp r0, #0x1
	bne _020243EE
	add r5, r5, #0x1
_020243EE:
	add r4, r4, #0x1
	cmp r4, r7
	ble _020243DE
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	pop {r3-r7, pc}
	nop
_020243FC: .word 0xBEEFCAFE
_02024400: .word 0x000001ED

	thumb_func_start FUN_02024404
FUN_02024404: ; 0x02024404
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, _02024438 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024414
	bl ErrorHandling
_02024414:
	ldr r7, _0202443C ; =0x000001ED
	mov r5, #0x0
	mov r4, #0x1
_0202441A:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x1
	bne _0202442A
	add r5, r5, #0x1
_0202442A:
	add r4, r4, #0x1
	cmp r4, r7
	ble _0202441A
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	pop {r3-r7, pc}
	nop
_02024438: .word 0xBEEFCAFE
_0202443C: .word 0x000001ED

	thumb_func_start FUN_02024440
FUN_02024440: ; 0x02024440
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02024CA4
	cmp r0, #0x0
	beq _02024454
	add r0, r4, #0x0
	bl FUN_02024404
	pop {r4, pc}
_02024454:
	add r0, r4, #0x0
	bl FUN_020244A4
	pop {r4, pc}

	thumb_func_start FUN_0202445C
FUN_0202445C: ; 0x0202445C
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, _0202449C ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202446C
	bl ErrorHandling
_0202446C:
	ldr r7, _020244A0 ; =0x000001ED
	mov r5, #0x0
	mov r4, #0x1
_02024472:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_02024594
	cmp r0, #0x1
	bne _0202448E
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02069B40
	cmp r0, #0x0
	beq _0202448E
	add r5, r5, #0x1
_0202448E:
	add r4, r4, #0x1
	cmp r4, r7
	ble _02024472
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	pop {r3-r7, pc}
	nop
_0202449C: .word 0xBEEFCAFE
_020244A0: .word 0x000001ED

	thumb_func_start FUN_020244A4
FUN_020244A4: ; 0x020244A4
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, _020244E4 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020244B4
	bl ErrorHandling
_020244B4:
	ldr r7, _020244E8 ; =0x000001ED
	mov r5, #0x0
	mov r4, #0x1
_020244BA:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x1
	bne _020244D6
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02069B40
	cmp r0, #0x0
	beq _020244D6
	add r5, r5, #0x1
_020244D6:
	add r4, r4, #0x1
	cmp r4, r7
	ble _020244BA
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	pop {r3-r7, pc}
	nop
_020244E4: .word 0xBEEFCAFE
_020244E8: .word 0x000001ED

	thumb_func_start FUN_020244EC
FUN_020244EC: ; 0x020244EC
	push {r3, lr}
	bl FUN_02024518
	ldr r1, _02024500 ; =0x000001E2
	cmp r0, r1
	blo _020244FC
	mov r0, #0x1
	pop {r3, pc}
_020244FC:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02024500: .word 0x000001E2

	thumb_func_start FUN_02024504
FUN_02024504: ; 0x02024504
	push {r3, lr}
	bl FUN_02024550
	cmp r0, #0x96
	blo _02024512
	mov r0, #0x1
	pop {r3, pc}
_02024512:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02024518
FUN_02024518: ; 0x02024518
	push {r3-r7, lr}
	ldr r7, _0202454C ; =0x000001ED
	add r6, r0, #0x0
	mov r5, #0x0
	mov r4, #0x1
_02024522:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_02024594
	cmp r0, #0x1
	bne _02024542
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02024340
	cmp r0, #0x1
	bne _02024542
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_02024542:
	add r4, r4, #0x1
	cmp r4, r7
	ble _02024522
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4
_0202454C: .word 0x000001ED

	thumb_func_start FUN_02024550
FUN_02024550: ; 0x02024550
	push {r3-r7, lr}
	ldr r7, _02024590 ; =0x000001ED
	add r6, r0, #0x0
	mov r5, #0x0
	mov r4, #0x1
_0202455A:
	lsl r1, r4, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_020245F0
	cmp r0, #0x1
	bne _02024586
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02069B40
	cmp r0, #0x0
	beq _02024586
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02024364
	cmp r0, #0x1
	bne _02024586
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_02024586:
	add r4, r4, #0x1
	cmp r4, r7
	ble _0202455A
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4
_02024590: .word 0x000001ED

	thumb_func_start FUN_02024594
FUN_02024594: ; 0x02024594
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020245E8 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020245A6
	bl ErrorHandling
_020245A6:
	cmp r4, #0x0
	beq _020245B0
	ldr r0, _020245EC ; =0x000001ED
	cmp r4, r0
	bls _020245B8
_020245B0:
	bl ErrorHandling
	mov r0, #0x1
	b _020245BA
_020245B8:
	mov r0, #0x0
_020245BA:
	cmp r0, #0x0
	beq _020245C2
	mov r0, #0x0
	pop {r3-r5, pc}
_020245C2:
	sub r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r0, #0x1
	mov r1, #0x7
	and r1, r2
	add r3, r0, #0x0
	lsl r3, r1
	asr r1, r2, #0x3
	add r2, r5, r1
	ldrb r1, [r2, #0x4]
	tst r1, r3
	beq _020245E4
	add r2, #0x44
	ldrb r1, [r2, #0x0]
	tst r1, r3
	bne _020245E6
_020245E4:
	mov r0, #0x0
_020245E6:
	pop {r3-r5, pc}
	.balign 4
_020245E8: .word 0xBEEFCAFE
_020245EC: .word 0x000001ED

	thumb_func_start FUN_020245F0
FUN_020245F0: ; 0x020245F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024640 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024602
	bl ErrorHandling
_02024602:
	cmp r4, #0x0
	beq _0202460C
	ldr r0, _02024644 ; =0x000001ED
	cmp r4, r0
	bls _02024614
_0202460C:
	bl ErrorHandling
	mov r0, #0x1
	b _02024616
_02024614:
	mov r0, #0x0
_02024616:
	cmp r0, #0x0
	beq _0202461E
	mov r0, #0x0
	pop {r3-r5, pc}
_0202461E:
	sub r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	mov r0, #0x1
	mov r1, #0x7
	and r1, r3
	add r2, r0, #0x0
	lsl r2, r1
	asr r1, r3, #0x3
	add r1, r5, r1
	add r1, #0x44
	ldrb r1, [r1, #0x0]
	tst r1, r2
	bne _0202463C
	mov r0, #0x0
_0202463C:
	pop {r3-r5, pc}
	nop
_02024640: .word 0xBEEFCAFE
_02024644: .word 0x000001ED

	thumb_func_start FUN_02024648
FUN_02024648: ; 0x02024648
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024670 ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202465A
	bl ErrorHandling
_0202465A:
	cmp r4, #0x0
	bne _02024666
	mov r0, #0x41
	lsl r0, r0, #0x2
	ldr r6, [r5, r0]
	b _0202466A
_02024666:
	bl ErrorHandling
_0202466A:
	add r0, r6, #0x0
	pop {r4-r6, pc}
	nop
_02024670: .word 0xBEEFCAFE

	thumb_func_start FUN_02024674
FUN_02024674: ; 0x02024674
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020246D4 ; =0xBEEFCAFE
	add r6, r2, #0x0
	cmp r1, r0
	beq _02024688
	bl ErrorHandling
_02024688:
	cmp r4, #0x0
	beq _02024692
	ldr r0, _020246D8 ; =0x000001ED
	cmp r4, r0
	bls _0202469A
_02024692:
	bl ErrorHandling
	mov r0, #0x1
	b _0202469C
_0202469A:
	mov r0, #0x0
_0202469C:
	cmp r0, #0x0
	beq _020246A6
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_020246A6:
	sub r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	add r3, r2, #0x0
	asr r2, r2, #0x3
	add r2, r5, r2
	mov r0, #0x7
	add r2, #0x44
	mov r1, #0x1
	and r3, r0
	ldrb r2, [r2, #0x0]
	lsl r1, r3
	tst r1, r2
	beq _020246CE
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020242C8
	pop {r4-r6, pc}
_020246CE:
	sub r0, #0x8
	pop {r4-r6, pc}
	nop
_020246D4: .word 0xBEEFCAFE
_020246D8: .word 0x000001ED

	thumb_func_start FUN_020246DC
FUN_020246DC: ; 0x020246DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024718 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020246EE
	bl ErrorHandling
_020246EE:
	mov r0, #0x43
	mov r2, #0x0
	lsl r0, r0, #0x2
_020246F4:
	add r1, r5, r2
	ldrb r1, [r1, r0]
	cmp r1, #0xff
	beq _02024702
	add r2, r2, #0x1
	cmp r2, #0x1c
	blt _020246F4
_02024702:
	cmp r2, r4
	bgt _0202470C
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0202470C:
	mov r0, #0x43
	add r1, r5, r4
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	pop {r3-r5, pc}
	nop
_02024718: .word 0xBEEFCAFE

	thumb_func_start FUN_0202471C
FUN_0202471C: ; 0x0202471C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024744 ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202472C
	bl ErrorHandling
_0202472C:
	mov r1, #0x43
	mov r0, #0x0
	lsl r1, r1, #0x2
_02024732:
	add r2, r4, r0
	ldrb r2, [r2, r1]
	cmp r2, #0xff
	beq _02024740
	add r0, r0, #0x1
	cmp r0, #0x1c
	blt _02024732
_02024740:
	pop {r4, pc}
	nop
_02024744: .word 0xBEEFCAFE

	thumb_func_start FUN_02024748
FUN_02024748: ; 0x02024748
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202479C ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202475A
	bl ErrorHandling
_0202475A:
	ldr r1, _020247A0 ; =0x000001A6
	add r0, r5, #0x0
	bl FUN_02023D8C
	cmp r0, r4
	bgt _0202476C
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0202476C:
	cmp r4, #0x2
	blt _02024774
	bl ErrorHandling
_02024774:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	sub r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r0, #0x1
	mov r1, #0x7
	and r1, r2
	add r3, r0, #0x0
	lsl r3, r1
	asr r1, r2, #0x3
	add r2, r5, r1
	mov r1, #0x42
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	tst r1, r3
	bne _0202479A
	mov r0, #0x0
_0202479A:
	pop {r3-r5, pc}
	.balign 4
_0202479C: .word 0xBEEFCAFE
_020247A0: .word 0x000001A6

	thumb_func_start FUN_020247A4
FUN_020247A4: ; 0x020247A4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _020247C0 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020247B4
	bl ErrorHandling
_020247B4:
	ldr r1, _020247C4 ; =0x000001A6
	add r0, r4, #0x0
	bl FUN_02023D8C
	pop {r4, pc}
	nop
_020247C0: .word 0xBEEFCAFE
_020247C4: .word 0x000001A6

	thumb_func_start FUN_020247C8
FUN_020247C8: ; 0x020247C8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202481C ; =0xBEEFCAFE
	cmp r1, r0
	beq _020247DA
	bl ErrorHandling
_020247DA:
	ldr r1, _02024820 ; =0x000001A7
	add r0, r5, #0x0
	bl FUN_02023D8C
	cmp r0, r4
	bgt _020247EC
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_020247EC:
	cmp r4, #0x2
	blt _020247F4
	bl ErrorHandling
_020247F4:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	sub r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r0, #0x1
	mov r1, #0x7
	and r1, r2
	add r3, r0, #0x0
	lsl r3, r1
	asr r1, r2, #0x3
	add r2, r5, r1
	ldr r1, _02024824 ; =0x00000109
	ldrb r1, [r2, r1]
	tst r1, r3
	bne _02024818
	mov r0, #0x0
_02024818:
	pop {r3-r5, pc}
	nop
_0202481C: .word 0xBEEFCAFE
_02024820: .word 0x000001A7
_02024824: .word 0x00000109

	thumb_func_start FUN_02024828
FUN_02024828: ; 0x02024828
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024844 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024838
	bl ErrorHandling
_02024838:
	ldr r1, _02024848 ; =0x000001A7
	add r0, r4, #0x0
	bl FUN_02023D8C
	pop {r4, pc}
	nop
_02024844: .word 0xBEEFCAFE
_02024848: .word 0x000001A7

	thumb_func_start FUN_0202484C
FUN_0202484C: ; 0x0202484C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024894 ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202485E
	bl ErrorHandling
_0202485E:
	mov r1, #0x67
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	bl FUN_02023F2C
	cmp r0, r4
	bgt _02024872
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_02024872:
	cmp r4, #0x3
	blt _0202487A
	bl ErrorHandling
_0202487A:
	lsl r0, r4, #0x10
	lsr r2, r0, #0x10
	asr r0, r2, #0x2
	add r1, r5, r0
	ldr r0, _02024898 ; =0x0000010A
	ldrb r1, [r1, r0]
	lsl r0, r2, #0x1e
	lsr r0, r0, #0x1d
	asr r1, r0
	mov r0, #0x3
	and r0, r1
	pop {r3-r5, pc}
	nop
_02024894: .word 0xBEEFCAFE
_02024898: .word 0x0000010A

	thumb_func_start FUN_0202489C
FUN_0202489C: ; 0x0202489C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _020248B8 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020248AC
	bl ErrorHandling
_020248AC:
	mov r1, #0x67
	add r0, r4, #0x0
	lsl r1, r1, #0x2
	bl FUN_02023F2C
	pop {r4, pc}
	.balign 4
_020248B8: .word 0xBEEFCAFE

	thumb_func_start FUN_020248BC
FUN_020248BC: ; 0x020248BC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024900 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020248CE
	bl ErrorHandling
_020248CE:
	ldr r1, _02024904 ; =0x0000019D
	add r0, r5, #0x0
	bl FUN_02023F2C
	cmp r0, r4
	bgt _020248E0
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_020248E0:
	cmp r4, #0x3
	blt _020248E8
	bl ErrorHandling
_020248E8:
	lsl r0, r4, #0x10
	lsr r2, r0, #0x10
	asr r0, r2, #0x2
	add r1, r5, r0
	ldr r0, _02024908 ; =0x0000010B
	ldrb r1, [r1, r0]
	lsl r0, r2, #0x1e
	lsr r0, r0, #0x1d
	asr r1, r0
	mov r0, #0x3
	and r0, r1
	pop {r3-r5, pc}
	.balign 4
_02024900: .word 0xBEEFCAFE
_02024904: .word 0x0000019D
_02024908: .word 0x0000010B

	thumb_func_start FUN_0202490C
FUN_0202490C: ; 0x0202490C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024928 ; =0xBEEFCAFE
	cmp r1, r0
	beq _0202491C
	bl ErrorHandling
_0202491C:
	ldr r1, _0202492C ; =0x0000019D
	add r0, r4, #0x0
	bl FUN_02023F2C
	pop {r4, pc}
	nop
_02024928: .word 0xBEEFCAFE
_0202492C: .word 0x0000019D

	thumb_func_start FUN_02024930
FUN_02024930: ; 0x02024930
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202496C ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024942
	bl ErrorHandling
_02024942:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x2
	bhs _02024958
	lsl r0, r0, #0x2
	ldr r1, [r5, #0x40]
	add r0, #0x18
	lsr r1, r0
	mov r0, #0xf
	and r0, r1
	pop {r3-r5, pc}
_02024958:
	add r5, #0x80
	sub r0, r0, #0x2
	lsl r0, r0, #0x18
	ldr r1, [r5, #0x0]
	lsr r0, r0, #0x16
	add r0, #0x18
	lsr r1, r0
	mov r0, #0xf
	and r0, r1
	pop {r3-r5, pc}
	.balign 4
_0202496C: .word 0xBEEFCAFE

	thumb_func_start FUN_02024970
FUN_02024970: ; 0x02024970
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024988 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024980
	bl ErrorHandling
_02024980:
	add r0, r4, #0x0
	bl FUN_020240D0
	pop {r4, pc}
	.balign 4
_02024988: .word 0xBEEFCAFE

	thumb_func_start FUN_0202498C
FUN_0202498C: ; 0x0202498C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	add r0, r1, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	mov r1, #0x0
	ldr r0, [sp, #0x0]
	add r2, r1, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_020689E0
	add r6, r0, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02024AE4 ; =0xBEEFCAFE
	cmp r1, r0
	beq _020249C4
	bl ErrorHandling
_020249C4:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020249D0
	ldr r1, _02024AE8 ; =0x000001ED
	cmp r0, r1
	bls _020249D8
_020249D0:
	bl ErrorHandling
	mov r0, #0x1
	b _020249DA
_020249D8:
	mov r0, #0x0
_020249DA:
	cmp r0, #0x0
	bne _02024ADE
	ldr r0, [sp, #0x4]
	mov r2, #0x1
	sub r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	mov r0, #0x7
	and r0, r4
	add r1, r2, #0x0
	lsl r1, r0
	asr r0, r4, #0x3
	add r3, r5, r0
	add r3, #0x44
	ldrb r3, [r3, #0x0]
	tst r3, r1
	bne _02024A70
	ldr r1, _02024AEC ; =0x00000147
	ldr r0, [sp, #0x4]
	cmp r0, r1
	bne _02024A08
	sub r1, #0x43
	str r7, [r5, r1]
_02024A08:
	lsl r0, r6, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x2
	bls _02024A14
	bl ErrorHandling
_02024A14:
	cmp r6, #0x2
	bne _02024A1A
	mov r6, #0x0
_02024A1A:
	cmp r6, #0x2
	blo _02024A22
	bl ErrorHandling
_02024A22:
	add r2, r5, #0x0
	mov r0, #0x7
	add r3, r4, #0x0
	and r3, r0
	mov r0, #0x1
	lsl r0, r3
	add r2, #0xc4
	asr r1, r4, #0x3
	ldrb r7, [r2, r1]
	mvn r0, r0
	and r0, r7
	strb r0, [r2, r1]
	add r0, r6, #0x0
	ldrb r7, [r2, r1]
	lsl r0, r3
	orr r0, r7
	strb r0, [r2, r1]
	cmp r6, #0x2
	blo _02024A4C
	bl ErrorHandling
_02024A4C:
	add r1, r5, #0x0
	mov r0, #0x7
	add r2, r4, #0x0
	and r2, r0
	mov r3, #0x1
	lsl r3, r2
	add r1, #0x84
	asr r0, r4, #0x3
	ldrb r7, [r1, r0]
	mvn r3, r3
	lsl r6, r2
	and r3, r7
	strb r3, [r1, r0]
	ldrb r3, [r1, r0]
	add r2, r3, #0x0
	orr r2, r6
	strb r2, [r1, r0]
	b _02024AC0
_02024A70:
	add r0, r5, r0
	add r0, #0x84
	ldrb r0, [r0, #0x0]
	tst r0, r1
	bne _02024A7C
	mov r2, #0x0
_02024A7C:
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	cmp r0, r6
	beq _02024AC0
	lsl r0, r6, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x2
	bls _02024A90
	bl ErrorHandling
_02024A90:
	cmp r6, #0x2
	bne _02024A96
	mov r6, #0x0
_02024A96:
	cmp r6, #0x2
	blo _02024A9E
	bl ErrorHandling
_02024A9E:
	add r1, r5, #0x0
	mov r0, #0x7
	add r2, r4, #0x0
	and r2, r0
	mov r3, #0x1
	lsl r3, r2
	add r1, #0xc4
	asr r0, r4, #0x3
	ldrb r7, [r1, r0]
	mvn r3, r3
	lsl r6, r2
	and r3, r7
	strb r3, [r1, r0]
	ldrb r3, [r1, r0]
	add r2, r3, #0x0
	orr r2, r6
	strb r2, [r1, r0]
_02024AC0:
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_020241B8
	mov r1, #0x7
	add r5, #0x44
	asr r0, r4, #0x3
	ldrb r3, [r5, r0]
	mov r2, #0x1
	and r1, r4
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strb r1, [r5, r0]
_02024ADE:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02024AE4: .word 0xBEEFCAFE
_02024AE8: .word 0x000001ED
_02024AEC: .word 0x00000147

	thumb_func_start FUN_02024AF0
FUN_02024AF0: ; 0x02024AF0
	push {r4-r7, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	str r1, [sp, #0x0]
	add r0, r1, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp, #0x0]
	mov r1, #0xc
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x8]
	mov r1, #0x0
	ldr r0, [sp, #0x0]
	add r2, r1, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	bl FUN_020689E0
	add r7, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024C78 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024B32
	bl ErrorHandling
_02024B32:
	cmp r6, #0x0
	beq _02024B3C
	ldr r0, _02024C7C ; =0x000001ED
	cmp r6, r0
	bls _02024B44
_02024B3C:
	bl ErrorHandling
	mov r0, #0x1
	b _02024B46
_02024B44:
	mov r0, #0x0
_02024B46:
	cmp r0, #0x0
	beq _02024B4C
	b _02024C72
_02024B4C:
	sub r0, r6, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	mov r0, #0x1
	mov r1, #0x7
	and r1, r5
	add r2, r0, #0x0
	asr r3, r5, #0x3
	lsl r2, r1
	add r1, r4, r3
	add r1, #0x44
	ldrb r1, [r1, #0x0]
	tst r1, r2
	bne _02024BEA
	ldr r1, _02024C80 ; =0x00000147
	cmp r6, r1
	bne _02024B74
	ldr r0, [sp, #0x4]
	sub r1, #0x43
	str r0, [r4, r1]
_02024B74:
	lsl r0, r7, #0x18
	lsr r7, r0, #0x18
	cmp r7, #0x2
	bls _02024B80
	bl ErrorHandling
_02024B80:
	cmp r7, #0x2
	bne _02024B86
	mov r7, #0x0
_02024B86:
	cmp r7, #0x2
	blo _02024B8E
	bl ErrorHandling
_02024B8E:
	mov r0, #0x7
	and r0, r5
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	add r0, #0xc4
	asr r3, r5, #0x3
	ldrb r1, [r0, r3]
	mov r2, #0x1
	str r1, [sp, #0xc]
	ldr r1, [sp, #0x10]
	lsl r2, r1
	ldr r1, [sp, #0xc]
	mvn r2, r2
	and r1, r2
	strb r1, [r0, r3]
	ldrb r1, [r0, r3]
	add r2, r7, #0x0
	mov r12, r1
	ldr r1, [sp, #0x10]
	lsl r2, r1
	mov r1, r12
	orr r1, r2
	strb r1, [r0, r3]
	cmp r7, #0x2
	blo _02024BC4
	bl ErrorHandling
_02024BC4:
	add r1, r4, #0x0
	mov r0, #0x7
	add r2, r5, #0x0
	and r2, r0
	mov r3, #0x1
	lsl r3, r2
	add r1, #0x84
	asr r0, r5, #0x3
	ldrb r5, [r1, r0]
	mvn r3, r3
	and r3, r5
	strb r3, [r1, r0]
	add r5, r7, #0x0
	ldrb r3, [r1, r0]
	lsl r5, r2
	add r2, r3, #0x0
	orr r2, r5
	strb r2, [r1, r0]
	b _02024C3C
_02024BEA:
	add r1, r4, r3
	add r1, #0x84
	ldrb r1, [r1, #0x0]
	tst r1, r2
	bne _02024BF6
	mov r0, #0x0
_02024BF6:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, r7
	beq _02024C3C
	lsl r0, r7, #0x18
	lsr r7, r0, #0x18
	cmp r7, #0x2
	bls _02024C0A
	bl ErrorHandling
_02024C0A:
	cmp r7, #0x2
	bne _02024C10
	mov r7, #0x0
_02024C10:
	cmp r7, #0x2
	blo _02024C18
	bl ErrorHandling
_02024C18:
	add r1, r4, #0x0
	mov r0, #0x7
	add r2, r5, #0x0
	and r2, r0
	mov r3, #0x1
	lsl r3, r2
	add r1, #0xc4
	asr r0, r5, #0x3
	ldrb r5, [r1, r0]
	mvn r3, r3
	and r3, r5
	strb r3, [r1, r0]
	add r5, r7, #0x0
	ldrb r3, [r1, r0]
	lsl r5, r2
	add r2, r3, #0x0
	orr r2, r5
	strb r2, [r1, r0]
_02024C3C:
	ldr r2, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020241B8
	ldr r2, [sp, #0x8]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_02024294
	sub r0, r6, #0x1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r1, r4, #0x4
	asr r0, r6, #0x3
	mov r2, #0x7
	ldrb r5, [r1, r0]
	mov r3, #0x1
	and r2, r6
	lsl r3, r2
	add r2, r5, #0x0
	orr r2, r3
	add r4, #0x44
	strb r2, [r1, r0]
	ldrb r1, [r4, r0]
	orr r1, r3
	strb r1, [r4, r0]
_02024C72:
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02024C78: .word 0xBEEFCAFE
_02024C7C: .word 0x000001ED
_02024C80: .word 0x00000147

	thumb_func_start FUN_02024C84
FUN_02024C84: ; 0x02024C84
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024C9C ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024C94
	bl ErrorHandling
_02024C94:
	ldr r0, _02024CA0 ; =0x00000139
	mov r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
	.balign 4
_02024C9C: .word 0xBEEFCAFE
_02024CA0: .word 0x00000139

	thumb_func_start FUN_02024CA4
FUN_02024CA4: ; 0x02024CA4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024CBC ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024CB4
	bl ErrorHandling
_02024CB4:
	ldr r0, _02024CC0 ; =0x00000139
	ldrb r0, [r4, r0]
	pop {r4, pc}
	nop
_02024CBC: .word 0xBEEFCAFE
_02024CC0: .word 0x00000139

	thumb_func_start FUN_02024CC4
FUN_02024CC4: ; 0x02024CC4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024CDC ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024CD4
	bl ErrorHandling
_02024CD4:
	mov r0, #0x4a
	lsl r0, r0, #0x2
	ldrb r0, [r4, r0]
	pop {r4, pc}
	.balign 4
_02024CDC: .word 0xBEEFCAFE

	thumb_func_start FUN_02024CE0
FUN_02024CE0: ; 0x02024CE0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024CFC ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024CF0
	bl ErrorHandling
_02024CF0:
	mov r0, #0x4a
	mov r1, #0x1
	lsl r0, r0, #0x2
	strb r1, [r4, r0]
	pop {r4, pc}
	nop
_02024CFC: .word 0xBEEFCAFE

	thumb_func_start FUN_02024D00
FUN_02024D00: ; 0x02024D00
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r6, #0x8
	blo _02024D10
	bl ErrorHandling
_02024D10:
	ldr r1, [r4, #0x0]
	ldr r0, _02024D44 ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024D1C
	bl ErrorHandling
_02024D1C:
	add r0, r5, #0x0
	bl FUN_02087A50
	add r5, r0, #0x0
	cmp r5, #0xe
	bne _02024D2C
	mov r0, #0x0
	pop {r4-r6, pc}
_02024D2C:
	add r0, r6, #0x0
	bl FUN_02087A1C
	mov r1, #0x1
	add r2, r1, #0x0
	lsl r2, r0
	ldr r0, _02024D48 ; =0x00000129
	add r1, r4, r5
	ldrb r0, [r1, r0]
	and r0, r2
	pop {r4-r6, pc}
	nop
_02024D44: .word 0xBEEFCAFE
_02024D48: .word 0x00000129

	thumb_func_start FUN_02024D4C
FUN_02024D4C: ; 0x02024D4C
	ldr r1, _02024D54 ; =0x00000137
	mov r2, #0x1
	strb r2, [r0, r1]
	bx lr
	.balign 4
_02024D54: .word 0x00000137

	thumb_func_start FUN_02024D58
FUN_02024D58: ; 0x02024D58
	ldr r1, _02024D60 ; =0x00000137
	ldrb r0, [r0, r1]
	bx lr
	nop
_02024D60: .word 0x00000137

	thumb_func_start FUN_02024D64
FUN_02024D64: ; 0x02024D64
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024D7C ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024D74
	bl ErrorHandling
_02024D74:
	mov r0, #0x4e
	lsl r0, r0, #0x2
	ldrb r0, [r4, r0]
	pop {r4, pc}
	.balign 4
_02024D7C: .word 0xBEEFCAFE

	thumb_func_start FUN_02024D80
FUN_02024D80: ; 0x02024D80
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02024D9C ; =0xBEEFCAFE
	cmp r1, r0
	beq _02024D90
	bl ErrorHandling
_02024D90:
	mov r0, #0x4e
	mov r1, #0x1
	lsl r0, r0, #0x2
	strb r1, [r4, r0]
	pop {r4, pc}
	nop
_02024D9C: .word 0xBEEFCAFE

	thumb_func_start FUN_02024DA0
FUN_02024DA0: ; 0x02024DA0
	ldr r3, _02024DA8 ; =FUN_02022610
	mov r1, #0x7
	bx r3
	nop
_02024DA8: .word FUN_02022610

	thumb_func_start FUN_02024DAC
FUN_02024DAC: ; 0x02024DAC
	push {r3-r5, lr}
	add r4, r2, #0x0
	ldr r2, _02024E60 ; =0x0000019D
	add r5, r0, #0x0
	cmp r1, r2
	bgt _02024DD6
	sub r3, r2, #0x1
	cmp r1, r3
	blt _02024DC6
	beq _02024E24
	cmp r1, r2
	beq _02024E36
	b _02024E5A
_02024DC6:
	cmp r1, #0xc9
	bgt _02024DCE
	beq _02024DEE
	b _02024E5A
_02024DCE:
	sub r2, #0x1b
	cmp r1, r2
	beq _02024E48
	b _02024E5A
_02024DD6:
	add r3, r2, #0x0
	add r3, #0x9
	cmp r1, r3
	bgt _02024DE6
	add r2, #0x9
	cmp r1, r2
	beq _02024E00
	b _02024E5A
_02024DE6:
	add r2, #0xa
	cmp r1, r2
	beq _02024E12
	b _02024E5A
_02024DEE:
	bl FUN_0202471C
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020246DC
	pop {r3-r5, pc}
_02024E00:
	bl FUN_020247A4
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02024748
	pop {r3-r5, pc}
_02024E12:
	bl FUN_02024828
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020247C8
	pop {r3-r5, pc}
_02024E24:
	bl FUN_0202489C
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202484C
	pop {r3-r5, pc}
_02024E36:
	bl FUN_0202490C
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020248BC
	pop {r3-r5, pc}
_02024E48:
	bl FUN_02024970
	cmp r4, r0
	bhs _02024E5A
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02024930
	pop {r3-r5, pc}
_02024E5A:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_02024E60: .word 0x0000019D
