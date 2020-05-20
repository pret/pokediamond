	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_020254B8
FUN_020254B8: ; 0x020254B8
	mov r0, #0x22
	lsl r0, r0, #0x6
	bx lr
	.balign 4

	thumb_func_start FUN_020254C0
FUN_020254C0: ; 0x020254C0
	ldr r3, _020254C8 ; =FUN_02022610
	mov r1, #0x9
	bx r3
	nop
_020254C8: .word FUN_02022610

	thumb_func_start FUN_020254CC
FUN_020254CC: ; 0x020254CC
	push {r3-r7, lr}
	mov r4, #0x0
	ldr r6, _020254EC ; =0x0000FFFF
	add r5, r0, #0x0
	add r7, r4, #0x0
_020254D6:
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x88
	bl memset
	strh r6, [r5, #0x0]
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x10
	blt _020254D6
	pop {r3-r7, pc}
	.balign 4
_020254EC: .word 0x0000FFFF

	thumb_func_start FUN_020254F0
FUN_020254F0: ; 0x020254F0
	mov r2, #0x88
	mul r2, r1
	add r0, r0, r2
	bx lr

	thumb_func_start FUN_020254F8
FUN_020254F8: ; 0x020254F8
	add r0, r0, r1
	add r0, #0x68
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02025500
FUN_02025500: ; 0x02025500
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl StringNotEqual
	cmp r0, #0x0
	bne _0202551A
	ldr r1, [r5, #0x10]
	ldr r0, [r4, #0x10]
	cmp r1, r0
	bne _0202551A
	mov r0, #0x1
	pop {r3-r5, pc}
_0202551A:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02025520
FUN_02025520: ; 0x02025520
	push {r4-r7, lr}
	sub sp, #0x2c
	str r1, [sp, #0x4]
	mov r1, #0x22
	str r0, [sp, #0x0]
	add r0, r3, #0x0
	lsl r1, r1, #0x6
	str r2, [sp, #0x8]
	bl FUN_02016998
	str r0, [sp, #0x10]
	bl FUN_020254CC
	mov r0, #0x0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	ble _02025578
	ldr r7, [sp, #0x4]
	add r6, sp, #0x18
_02025548:
	mov r0, #0x0
	mvn r0, r0
	ldr r5, [sp, #0x0]
	str r0, [r6, #0x0]
	mov r4, #0x0
_02025552:
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02025500
	cmp r0, #0x0
	beq _02025560
	str r4, [r6, #0x0]
_02025560:
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x10
	blt _02025552
	ldr r0, [sp, #0x14]
	add r6, r6, #0x4
	add r1, r0, #0x1
	ldr r0, [sp, #0x8]
	add r7, #0x88
	str r1, [sp, #0x14]
	cmp r1, r0
	blt _02025548
_02025578:
	ldr r0, [sp, #0x8]
	mov r4, #0x0
	str r4, [sp, #0xc]
	cmp r0, #0x0
	ble _020255BE
	ldr r5, [sp, #0x10]
	add r6, sp, #0x18
_02025586:
	ldr r3, [sp, #0x4]
	add r7, r5, #0x0
	mov r2, #0x11
_0202558C:
	ldmia r3!, {r0-r1}
	stmia r7!, {r0-r1}
	sub r2, r2, #0x1
	bne _0202558C
	ldr r1, [r6, #0x0]
	cmp r1, #0x0
	blt _020255A6
	add r2, r1, #0x0
	mov r0, #0x88
	mul r2, r0
	ldr r1, _02025610 ; =0x0000FFFF
	ldr r0, [sp, #0x0]
	strh r1, [r0, r2]
_020255A6:
	ldr r0, [sp, #0x4]
	add r5, #0x88
	add r0, #0x88
	str r0, [sp, #0x4]
	ldr r0, [sp, #0xc]
	add r4, r4, #0x1
	add r1, r0, #0x1
	ldr r0, [sp, #0x8]
	add r6, r6, #0x4
	str r1, [sp, #0xc]
	cmp r1, r0
	blt _02025586
_020255BE:
	mov r0, #0x0
	mov r12, r0
	mov r0, #0x88
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, [sp, #0x10]
	ldr r3, [sp, #0x0]
	add r5, r0, r1
_020255CE:
	ldrh r1, [r3, #0x0]
	ldr r0, _02025610 ; =0x0000FFFF
	cmp r1, r0
	beq _020255EC
	add r6, r3, #0x0
	add r7, r5, #0x0
	mov r2, #0x11
_020255DC:
	ldmia r6!, {r0-r1}
	stmia r7!, {r0-r1}
	sub r2, r2, #0x1
	bne _020255DC
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x10
	bge _020255F8
_020255EC:
	mov r0, r12
	add r0, r0, #0x1
	add r3, #0x88
	mov r12, r0
	cmp r0, #0x10
	blt _020255CE
_020255F8:
	mov r2, #0x22
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x10]
	lsl r2, r2, #0x6
	bl memcpy
	ldr r0, [sp, #0x10]
	bl FUN_02016A18
	add sp, #0x2c
	pop {r4-r7, pc}
	nop
_02025610: .word 0x0000FFFF

	thumb_func_start FUN_02025614
FUN_02025614: ; 0x02025614
	push {r3-r6}
	mov r3, #0x0
	add r4, r0, #0x0
_0202561A:
	ldr r2, [r4, #0x10]
	cmp r1, r2
	bne _02025626
	mov r0, #0x1
	pop {r3-r6}
	bx lr
_02025626:
	add r3, r3, #0x1
	add r4, #0x88
	cmp r3, #0x10
	blt _0202561A
	mov r6, #0x0
	add r3, r6, #0x0
_02025632:
	add r4, r3, #0x0
	add r5, r0, #0x0
_02025636:
	ldr r2, [r5, #0x18]
	cmp r1, r2
	bne _02025642
	add r0, r6, #0x2
	pop {r3-r6}
	bx lr
_02025642:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x10
	blt _02025636
	add r6, r6, #0x1
	add r0, #0x88
	cmp r6, #0x10
	blt _02025632
	mov r0, #0x0
	pop {r3-r6}
	bx lr
