	.include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_021CEDD4
	.extern UNK_021CED98

	.text

	thumb_func_start FUN_0201B6D0
FUN_0201B6D0: ; 0x0201B6D0
	push {r4-r7, lr}
	sub sp, #0x34
	add r6, r1, #0x0
	add r4, r0, #0x0
	add r5, r2, #0x0
	ldmia r6!, {r0-r1}
	add r2, sp, #0x1c
	stmia r2!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r4, #0x14
	str r0, [r2, #0x0]
	mov r0, #0x20
	ldrsh r0, [r4, r0]
	add r7, r3, #0x0
	mov r1, #0x1a
	str r0, [sp, #0x0]
	mov r0, #0x22
	ldrsh r0, [r4, r0]
	mov r2, #0x1c
	mov r3, #0x1e
	str r0, [sp, #0x4]
	add r0, sp, #0x28
	str r0, [sp, #0x8]
	mov r0, #0x18
	ldrsh r0, [r4, r0]
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	bl FUN_0201B808
	add r0, sp, #0x1c
	bl FUN_020B8474
	ldr r1, _0201B764 ; =UNK_021CEDD4
	add r0, r5, #0x0
	bl MI_Copy36B
	ldr r1, _0201B768 ; =UNK_021CED98
	mov r0, #0xa4
	ldr r2, [r1, #0x7c]
	bic r2, r0
	add r0, r7, #0x0
	str r2, [r1, #0x7c]
	bl FUN_020B844C
	bl FUN_020B849C
	mov r1, #0x0
	mov r0, #0x11
	add r2, r1, #0x0
	bl FUN_020BB1C0
	ldr r0, [r4, #0x24]
	add r1, sp, #0x10
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	mov r0, #0x1b
	mov r2, #0x3
	bl FUN_020BB1C0
	add r0, sp, #0x28
	bl FUN_0201B82C
	add r4, r0, #0x0
	mov r2, #0x1
	mov r0, #0x12
	add r1, sp, #0xc
	str r2, [sp, #0xc]
	bl FUN_020BB1C0
	add r0, r4, #0x0
	add sp, #0x34
	pop {r4-r7, pc}
	.balign 4
_0201B764: .word UNK_021CEDD4
_0201B768: .word UNK_021CED98

	thumb_func_start FUN_0201B76C
FUN_0201B76C: ; 0x0201B76C
	push {r3-r5, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x2
	ldrsh r0, [r4, r0]
	str r0, [sp, #0x0]
	mov r0, #0x4
	ldrsh r0, [r4, r0]
	str r0, [sp, #0x4]
	add r0, sp, #0x1c
	str r0, [sp, #0x8]
	mov r0, #0x0
	ldrsh r3, [r4, r0]
	add r1, r0, #0x0
	add r2, r0, #0x0
	bl FUN_0201B808
	add r0, r5, #0x0
	bl FUN_020B8474
	bl FUN_020B849C
	mov r1, #0x0
	mov r0, #0x11
	add r2, r1, #0x0
	bl FUN_020BB1C0
	ldr r0, [r4, #0x10]
	lsl r2, r0, #0xc
	ldr r0, [r4, #0xc]
	lsl r1, r0, #0xc
	ldr r0, [r4, #0x8]
	lsl r0, r0, #0xc
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	str r2, [sp, #0x18]
	mov r0, #0x1b
	add r1, sp, #0x10
	mov r2, #0x3
	bl FUN_020BB1C0
	add r0, sp, #0x1c
	bl FUN_0201B82C
	add r4, r0, #0x0
	mov r2, #0x1
	mov r0, #0x12
	add r1, sp, #0xc
	str r2, [sp, #0xc]
	bl FUN_020BB1C0
	add r0, r4, #0x0
	add sp, #0x28
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201B7DC
FUN_0201B7DC: ; 0x0201B7DC
	push {r4-r6, lr}
	add r6, r3, #0x0
	add r4, r2, #0x0
	add r2, r6, #0x0
	add r5, r1, #0x0
	add r1, r6, #0x0
	add r2, #0x8
	bl FUN_0201B880
	add r2, r6, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x2
	add r2, #0xc
	bl FUN_0201B880
	add r1, r6, #0x4
	add r6, #0x10
	add r0, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0201B880
	pop {r4-r6, pc}

	thumb_func_start FUN_0201B808
FUN_0201B808: ; 0x0201B808
	push {r3-r4}
	ldr r4, [sp, #0x10]
	strh r0, [r4, #0x0]
	strh r1, [r4, #0x2]
	ldr r1, _0201B828 ; =0xFFFFFFF8
	strh r2, [r4, #0x4]
	strh r3, [r4, #0x6]
	add r1, sp
	mov r0, #0x10
	ldrsh r0, [r1, r0]
	strh r0, [r4, #0x8]
	mov r0, #0x14
	ldrsh r0, [r1, r0]
	strh r0, [r4, #0xa]
	pop {r3-r4}
	bx lr
	.balign 4
_0201B828: .word 0xFFFFFFF8

	thumb_func_start FUN_0201B82C
FUN_0201B82C: ; 0x0201B82C
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r0, _0201B87C ; =0x000030C1
	mov r2, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x29
	add r1, sp, #0x4
	str r2, [sp, #0x8]
	bl FUN_020BB1C0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x40
	add r1, sp, #0x0
	mov r2, #0x1
	bl FUN_020BB1C0
	mov r1, #0x0
	mov r0, #0x41
	add r2, r1, #0x0
	bl FUN_020BB1C0
	mov r0, #0x70
	add r1, r4, #0x0
	mov r2, #0x3
	bl FUN_020BB1C0
	bl FUN_020BB394
	add r4, sp, #0x8
_0201B86A:
	add r0, r4, #0x0
	bl G3X_GetBoxTestResult
	cmp r0, #0x0
	bne _0201B86A
	ldr r0, [sp, #0x8]
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_0201B87C: .word 0x000030C1

	thumb_func_start FUN_0201B880
FUN_0201B880: ; 0x0201B880
	push {r3-r4}
	ldr r4, _0201B8B4 ; =0x00007FFF
	mov r3, #0x0
	cmp r0, r4
	blo _0201B896
_0201B88A:
	add r3, r3, #0x1
	lsl r3, r3, #0x18
	lsr r0, r0, #0x1
	lsr r3, r3, #0x18
	cmp r0, r4
	bhs _0201B88A
_0201B896:
	strh r0, [r1, #0x0]
	mov r0, #0x1
	mov r1, #0x0
	str r0, [r2, #0x0]
	cmp r3, #0x0
	ble _0201B8AE
_0201B8A2:
	ldr r0, [r2, #0x0]
	add r1, r1, #0x1
	lsl r0, r0, #0x1
	str r0, [r2, #0x0]
	cmp r1, r3
	blt _0201B8A2
_0201B8AE:
	pop {r3-r4}
	bx lr
	nop
_0201B8B4: .word 0x00007FFF
