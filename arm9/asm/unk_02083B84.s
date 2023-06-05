	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020FBF98
UNK_020FBF98: ; 0x020FBF98
	.word FUN_02083BAC, FUN_02083D28, FUN_02083D30
	.word FUN_02083C24, FUN_0202DA84, 0x00000000
	.word FUN_02083C44, FUN_0202DA84, 0x00000000
	.word FUN_02083C54, FUN_0202DA84, 0x00000000
	.word FUN_02083C58, FUN_0202DA84, 0x00000000
	.word FUN_02083C5C, FUN_0202DA84, 0x00000000
	.word FUN_02083CAC, FUN_02083D24, FUN_02083D30
	.word FUN_02083CD8, FUN_02083D18, FUN_02083D30
	.word FUN_02083C68, FUN_0202DA80, 0x00000000
	.word FUN_02083C6C, FUN_0202DA84, 0x00000000
	.word FUN_02083C7C, FUN_02083D20, 0x00000000

	.text

	thumb_func_start FUN_02083B84
FUN_02083B84: ; 0x02083B84
	ldr r3, _02083B90 ; =FUN_0202D8D0
	add r2, r0, #0x0
	ldr r0, _02083B94 ; =UNK_020FBF98
	mov r1, #0xb
	bx r3
	nop
_02083B90: .word FUN_0202D8D0
_02083B94: .word UNK_020FBF98

	thumb_func_start FUN_02083B98
FUN_02083B98: ; 0x02083B98
	cmp r0, #0xc
	bne _02083BA0
	mov r0, #0xc
	bx lr
_02083BA0:
	cmp r0, #0x6
	bhs _02083BA8
	add r0, r0, #0x6
	bx lr
_02083BA8:
	sub r0, r0, #0x6
	bx lr

	thumb_func_start FUN_02083BAC
FUN_02083BAC: ; 0x02083BAC
	push {r4-r6, lr}
	add r3, #0x84
	add r5, r0, #0x0
	add r6, r2, #0x0
	ldr r4, [r3, #0x0]
	bl FUN_02031190
	cmp r5, r0
	beq _02083C1A
	ldr r0, _02083C1C ; =0x0000221C
	mov r2, #0x59
	ldr r0, [r4, r0]
	add r1, r6, #0x0
	lsl r2, r2, #0x4
	bl memcpy
	ldr r0, [r4, #0x58]
	add r0, r0, #0x1
	str r0, [r4, #0x58]
	bl SaveArray_Party_sizeof
	mov r1, #0x59
	ldr r2, [r4, #0x58]
	lsl r1, r1, #0x4
	mul r1, r2
	cmp r1, r0
	blt _02083C06
	bl FUN_02031190
	cmp r0, #0x1
	bne _02083BF6
	add r0, r4, #0x0
	mov r1, #0x1b
	mov r2, #0x0
	bl MOD71_0222F440
	b _02083C14
_02083BF6:
	bl FUN_02031190
	ldr r1, _02083C20 ; =0x00002218
	ldr r2, [r4, #0x50]
	ldr r1, [r4, r1]
	bl MOD71_0222F480
	b _02083C14
_02083C06:
	bl FUN_02031190
	ldr r1, _02083C20 ; =0x00002218
	ldr r2, [r4, #0x50]
	ldr r1, [r4, r1]
	bl MOD71_0222F480
_02083C14:
	ldr r0, [r4, #0x50]
	add r0, r0, #0x1
	str r0, [r4, #0x50]
_02083C1A:
	pop {r4-r6, pc}
	.balign 4
_02083C1C: .word 0x0000221C
_02083C20: .word 0x00002218

	thumb_func_start FUN_02083C24
FUN_02083C24: ; 0x02083C24
	push {r4-r6, lr}
	add r3, #0x84
	add r5, r0, #0x0
	add r6, r2, #0x0
	ldr r4, [r3, #0x0]
	bl FUN_02031190
	cmp r5, r0
	beq _02083C40
	ldrb r0, [r6, #0x0]
	bl FUN_02083B98
	add r4, #0x8c
	str r0, [r4, #0x0]
_02083C40:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02083C44
FUN_02083C44: ; 0x02083C44
	add r3, #0x84
	ldrb r2, [r2, #0x0]
	ldr r1, [r3, #0x0]
	lsl r0, r0, #0x2
	add r0, r1, r0
	str r2, [r0, #0x60]
	bx lr
	.balign 4

	thumb_func_start FUN_02083C54
FUN_02083C54: ; 0x02083C54
	bx lr
	.balign 4

	thumb_func_start FUN_02083C58
FUN_02083C58: ; 0x02083C58
	bx lr
	.balign 4

	thumb_func_start FUN_02083C5C
FUN_02083C5C: ; 0x02083C5C
	add r3, #0x84
	ldr r0, [r3, #0x0]
	mov r1, #0x2
	str r1, [r0, #0x54]
	bx lr
	.balign 4

	thumb_func_start FUN_02083C68
FUN_02083C68: ; 0x02083C68
	bx lr
	.balign 4

	thumb_func_start FUN_02083C6C
FUN_02083C6C: ; 0x02083C6C
	add r3, #0x84
	mov r0, #0x8b
	ldrb r2, [r2, #0x0]
	ldr r1, [r3, #0x0]
	lsl r0, r0, #0x6
	str r2, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02083C7C
FUN_02083C7C: ; 0x02083C7C
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldr r0, [r3, #0xc]
	add r5, r2, #0x0
	bl FUN_0202A918
	add r4, r0, #0x0
	bl FUN_02031190
	cmp r6, r0
	beq _02083CA8
	mov r2, #0x0
_02083C94:
	ldrb r1, [r5, r2]
	cmp r1, #0x0
	beq _02083CA2
	ldrb r0, [r4, r2]
	cmp r0, r1
	beq _02083CA2
	strb r1, [r4, r2]
_02083CA2:
	add r2, r2, #0x1
	cmp r2, #0xe
	blt _02083C94
_02083CA8:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02083CAC
FUN_02083CAC: ; 0x02083CAC
	push {r4-r6, lr}
	add r3, #0x84
	add r5, r0, #0x0
	add r6, r2, #0x0
	ldr r4, [r3, #0x0]
	bl FUN_02031190
	cmp r5, r0
	beq _02083CD0
	ldr r0, _02083CD4 ; =0x00002224
	add r1, r6, #0x0
	ldr r0, [r4, r0]
	mov r2, #0x1
	mov r3, #0x1a
	bl FUN_02025520
	mov r0, #0x3
	str r0, [r4, #0x54]
_02083CD0:
	pop {r4-r6, pc}
	nop
_02083CD4: .word 0x00002224

	thumb_func_start FUN_02083CD8
FUN_02083CD8: ; 0x02083CD8
	push {r4-r6, lr}
	add r3, #0x84
	add r5, r0, #0x0
	add r6, r2, #0x0
	ldr r4, [r3, #0x0]
	bl FUN_02031190
	cmp r5, r0
	beq _02083D0A
	ldr r1, _02083D0C ; =0x00002E14
	mov r2, #0xfb
	add r3, r4, r1
	lsl r2, r2, #0x2
	add r1, r5, #0x0
	mul r1, r2
	add r0, r6, #0x0
	add r1, r3, r1
	sub r2, r2, #0x4
	bl MIi_CpuCopyFast
	mov r0, #0x4
	str r0, [r4, #0x54]
	mov r0, #0x0
	bl FUN_02031400
_02083D0A:
	pop {r4-r6, pc}
	.balign 4
_02083D0C: .word 0x00002E14

	thumb_func_start FUN_02083D10
FUN_02083D10: ; 0x02083D10
	add r0, #0x84
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02083D18
FUN_02083D18: ; 0x02083D18
	mov r0, #0xfb
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_02083D20
FUN_02083D20: ; 0x02083D20
	mov r0, #0xe
	bx lr

	thumb_func_start FUN_02083D24
FUN_02083D24: ; 0x02083D24
	mov r0, #0x88
	bx lr

	thumb_func_start FUN_02083D28
FUN_02083D28: ; 0x02083D28
	mov r0, #0x59
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02083D30
FUN_02083D30: ; 0x02083D30
	add r1, #0x84
	ldr r2, [r1, #0x0]
	ldr r1, _02083D44 ; =0x000022F4
	add r2, r2, r1
	mov r1, #0x59
	lsl r1, r1, #0x4
	mul r1, r0
	add r0, r2, r1
	bx lr
	nop
_02083D44: .word 0x000022F4
