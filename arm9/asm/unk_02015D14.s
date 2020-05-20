    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02015D14
FUN_02015D14: ; 0x02015D14
	cmp r0, #0x7
	bhi _02015D34
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02015D24: ; jump table (using 16-bit offset)
	.short _02015D34 - _02015D24 - 2; case 0
	.short _02015D34 - _02015D24 - 2; case 1
	.short _02015D38 - _02015D24 - 2; case 2
	.short _02015D3E - _02015D24 - 2; case 3
	.short _02015D38 - _02015D24 - 2; case 4
	.short _02015D42 - _02015D24 - 2; case 5
	.short _02015D34 - _02015D24 - 2; case 6
	.short _02015D38 - _02015D24 - 2; case 7
_02015D34:
	mov r0, #0xea
	bx lr
_02015D38:
	mov r0, #0x6d
	lsl r0, r0, #0x2
	bx lr
_02015D3E:
	ldr r0, _02015D48 ; =0x000001B7
	bx lr
_02015D42:
	ldr r0, _02015D4C ; =0x000001B6
	bx lr
	nop
_02015D48: .word 0x000001B7
_02015D4C: .word 0x000001B6

	thumb_func_start FUN_02015D50
FUN_02015D50: ; 0x02015D50
	cmp r0, #0x7
	bhi _02015D70
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02015D60: ; jump table (using 16-bit offset)
	.short _02015D70 - _02015D60 - 2; case 0
	.short _02015D70 - _02015D60 - 2; case 1
	.short _02015D74 - _02015D60 - 2; case 2
	.short _02015D78 - _02015D60 - 2; case 3
	.short _02015D74 - _02015D60 - 2; case 4
	.short _02015D7E - _02015D60 - 2; case 5
	.short _02015D70 - _02015D60 - 2; case 6
	.short _02015D74 - _02015D60 - 2; case 7
_02015D70:
	mov r0, #0xeb
	bx lr
_02015D74:
	ldr r0, _02015D84 ; =0x000001B5
	bx lr
_02015D78:
	mov r0, #0x6e
	lsl r0, r0, #0x2
	bx lr
_02015D7E:
	mov r0, #0x6d
	lsl r0, r0, #0x2
	bx lr
	.balign 4
_02015D84: .word 0x000001B5

	thumb_func_start FUN_02015D88
FUN_02015D88: ; 0x02015D88
	push {r3-r7, lr}
	sub sp, #0x10
	add r6, r3, #0x0
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	str r2, [sp, #0x8]
	cmp r6, #0x1
	beq _02015D9C
	mov r2, #0x1
	b _02015D9E
_02015D9C:
	mov r2, #0x0
_02015D9E:
	ldr r0, [sp, #0x8]
	mov r4, #0x0
	sub r0, r0, #0x1
	str r0, [sp, #0xc]
	beq _02015E18
	ldr r1, _02015E28 ; =0x020ED734
	lsl r0, r2, #0x1
	ldr r5, [sp, #0x4]
	add r7, r1, r0
_02015DB0:
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, r4]
	cmp r0, #0xff
	beq _02015E18
	cmp r0, #0xf7
	blo _02015DEA
	ldr r0, [sp, #0x8]
	sub r3, r0, #0x1
	cmp r3, #0xa
	blo _02015DC6
	mov r3, #0xa
_02015DC6:
	mov r1, #0x0
	cmp r3, #0x0
	ble _02015DDC
	mov r0, #0x6b
	ldr r2, [sp, #0x4]
	lsl r0, r0, #0x2
_02015DD2:
	add r1, r1, #0x1
	strh r0, [r2, #0x0]
	add r2, r2, #0x2
	cmp r1, r3
	blt _02015DD2
_02015DDC:
	ldr r0, [sp, #0x4]
	ldr r2, _02015E2C ; =0x0000FFFF
	lsl r1, r1, #0x1
	strh r2, [r0, r1]
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_02015DEA:
	lsl r0, r0, #0x2
	ldrh r0, [r7, r0]
	cmp r0, #0xea
	beq _02015DF8
	cmp r0, #0xeb
	beq _02015E02
	b _02015E0C
_02015DF8:
	add r0, r6, #0x0
	bl FUN_02015D14
	strh r0, [r5, #0x0]
	b _02015E0E
_02015E02:
	add r0, r6, #0x0
	bl FUN_02015D50
	strh r0, [r5, #0x0]
	b _02015E0E
_02015E0C:
	strh r0, [r5, #0x0]
_02015E0E:
	ldr r0, [sp, #0xc]
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, r0
	blo _02015DB0
_02015E18:
	ldr r2, _02015E2C ; =0x0000FFFF
	ldr r0, [sp, #0x4]
	lsl r1, r4, #0x1
	strh r2, [r0, r1]
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_02015E28: .word 0x020ED734
_02015E2C: .word 0x0000FFFF
