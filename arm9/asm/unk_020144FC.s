    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_020144FC
FUN_020144FC: ; 0x020144FC
	push {r3, lr}
	add r3, r0, #0x0
	mov r0, #0x20
	str r0, [sp, #0x0]
	ldr r0, [r3, #0x8]
	add r3, #0x4d
	ldrb r3, [r3, #0x0]
	mov r2, #0x1
	lsl r3, r3, #0x14
	lsr r3, r3, #0x10
	bl FUN_02003054
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02014518
FUN_02014518: ; 0x02014518
	push {r3-r7, lr}
	mov r1, #0x78
	add r7, r0, #0x0
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x78
	add r6, r0, #0x0
	bl MI_CpuFill8
	ldr r2, _02014560 ; =0x0000019E
	mov r0, #0x0
	mov r1, #0x1a
	add r3, r7, #0x0
	bl FUN_0200A86C
	str r0, [r6, #0x0]
	mov r4, #0x0
	add r5, r6, #0x0
_0201453E:
	mov r0, #0x16
	add r1, r7, #0x0
	bl FUN_020219F4
	str r0, [r5, #0x4]
	ldr r0, [r6, #0x0]
	ldr r2, [r5, #0x4]
	add r1, r4, #0x0
	bl FUN_0200A8E0
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x1d
	blt _0201453E
	add r0, r6, #0x0
	pop {r3-r7, pc}
	nop
_02014560: .word 0x0000019E

	thumb_func_start FUN_02014564
FUN_02014564: ; 0x02014564
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r6, #0x0
	mov r4, #0x1c
	add r5, #0x70
_0201456E:
	ldr r0, [r5, #0x4]
	bl FUN_02021A20
	sub r5, r5, #0x4
	sub r4, r4, #0x1
	bpl _0201456E
	ldr r0, [r6, #0x0]
	bl FUN_0200A8B8
	add r0, r6, #0x0
	bl FUN_02016A18
	pop {r4-r6, pc}

	thumb_func_start FUN_02014588
FUN_02014588: ; 0x02014588
	lsl r1, r1, #0x2
	add r0, r0, r1
	ldr r0, [r0, #0x4]
	bx lr
