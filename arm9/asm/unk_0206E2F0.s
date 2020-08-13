    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206E2F0
FUN_0206E2F0: ; 0x0206E2F0
	push {r4, lr}
	mov r1, #0x78
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x78
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0206E308
FUN_0206E308: ; 0x0206E308
	mov r0, #0x78
	bx lr

	thumb_func_start FUN_0206E30C
FUN_0206E30C: ; 0x0206E30C
	add r0, #0x65
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0206E314
FUN_0206E314: ; 0x0206E314
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r1, r2, #0x0
	add r5, r0, #0x0
	add r6, r3, #0x0
	bl FUN_0206E30C
	str r4, [r5, #0x0]
	str r6, [r5, #0x6c]
	mov r0, #0x0
	add r5, #0x66
	strh r0, [r5, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0206E330
FUN_0206E330: ; 0x0206E330
	push {r3-r4}
	mov r4, #0xc
	mul r4, r3
	add r0, r0, r4
	str r1, [r0, #0x4]
	strb r2, [r0, #0xc]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0206E340
FUN_0206E340: ; 0x0206E340
	add r1, r0, #0x0
	add r1, #0x76
	ldrh r2, [r1, #0x0]
	mov r1, #0x1
	add r0, #0x76
	bic r2, r1
	mov r1, #0x1
	orr r1, r2
	strh r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0206E354
FUN_0206E354: ; 0x0206E354
	str r1, [r0, #0x70]
	bx lr

	thumb_func_start FUN_0206E358
FUN_0206E358: ; 0x0206E358
	add r0, #0x74
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0206E360
FUN_0206E360: ; 0x0206E360
	add r2, r0, #0x0
	add r2, #0x76
	ldrh r3, [r2, #0x0]
	ldr r2, _0206E378 ; =0xFFFF0001
	lsl r1, r1, #0x11
	and r2, r3
	lsr r1, r1, #0x10
	orr r1, r2
	add r0, #0x76
	strh r1, [r0, #0x0]
	bx lr
	nop
_0206E378: .word 0xFFFF0001

	thumb_func_start FUN_0206E37C
FUN_0206E37C: ; 0x0206E37C
	add r0, #0x66
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0206E384
FUN_0206E384: ; 0x0206E384
	add r0, #0x68
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0206E38C
FUN_0206E38C: ; 0x0206E38C
	add r0, #0x74
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0206E394
FUN_0206E394: ; 0x0206E394
	add r0, #0x75
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0206E39C
FUN_0206E39C: ; 0x0206E39C
	push {r3, lr}
	bl FUN_0202390C
	bl CheckCoins
	pop {r3, pc}

	thumb_func_start FUN_0206E3A8
FUN_0206E3A8: ; 0x0206E3A8
	push {r4-r6, lr}
	bl FUN_02029C80
	add r6, r0, #0x0
	mov r5, #0x0
	mov r4, #0x1
_0206E3B4:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02029E2C
	add r4, r4, #0x1
	add r5, r5, r0
	cmp r4, #0x50
	bls _0206E3B4
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0206E3C8
FUN_0206E3C8: ; 0x0206E3C8
	push {r3, lr}
	bl FUN_02027E24
	bl FUN_0202708C
	bl FUN_02027168
	pop {r3, pc}

	thumb_func_start FUN_0206E3D8
FUN_0206E3D8: ; 0x0206E3D8
	push {r3, lr}
	bl FUN_02027E24
	bl FUN_0202708C
	bl FUN_02027184
	pop {r3, pc}

	thumb_func_start FUN_0206E3E8
FUN_0206E3E8: ; 0x0206E3E8
	push {r3, lr}
	bl FUN_0202A8D8
	mov r1, #0x0
	add r2, r1, #0x0
	bl FUN_0202A3B4
	pop {r3, pc}

	thumb_func_start FUN_0206E3F8
FUN_0206E3F8: ; 0x0206E3F8
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r0, #0x0
	str r1, [sp, #0x8]
	add r5, r2, #0x0
	add r4, r3, #0x0
	mov r0, #0x0
	mov r1, #0x1a
	mov r2, #0x7
	bl NewMsgDataFromNarc
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0200AA80
	add r4, r0, #0x0
	cmp r5, #0x0
	bne _0206E428
	add r0, r6, #0x0
	mov r1, #0x63
	bl NewString_ReadMsgData
	add r5, r0, #0x0
	b _0206E4FA
_0206E428:
	mov r1, #0x1b
	lsl r1, r1, #0x4
	cmp r5, r1
	bne _0206E454
	add r0, r6, #0x0
	mov r1, #0x61
	bl NewString_ReadMsgData
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0206E3E8
	mov r1, #0x0
	add r2, r0, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r3, #0x4
	bl FUN_0200AD38
	b _0206E4FA
_0206E454:
	add r2, r1, #0x2
	cmp r5, r2
	bne _0206E47E
	add r0, r6, #0x0
	mov r1, #0x5c
	bl NewString_ReadMsgData
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0206E3A8
	mov r1, #0x0
	add r2, r0, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r3, #0x4
	bl FUN_0200AD38
	b _0206E4FA
_0206E47E:
	add r2, r1, #0x3
	cmp r5, r2
	bne _0206E4C0
	add r0, r6, #0x0
	mov r1, #0x5d
	bl NewString_ReadMsgData
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0206E3C8
	mov r1, #0x0
	add r2, r0, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r3, #0x3
	bl FUN_0200AD38
	add r0, r7, #0x0
	bl FUN_0206E3D8
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r1, #0x1
	add r0, r4, #0x0
	mov r3, #0x2
	str r1, [sp, #0x4]
	bl FUN_0200AD38
	b _0206E4FA
_0206E4C0:
	add r1, #0xc
	cmp r5, r1
	bne _0206E4EA
	add r0, r6, #0x0
	mov r1, #0x39
	bl NewString_ReadMsgData
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0206E39C
	mov r1, #0x0
	add r2, r0, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r3, #0x5
	bl FUN_0200AD38
	b _0206E4FA
_0206E4EA:
	bl FUN_0200AB18
	add r0, r6, #0x0
	bl DestroyMsgData
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0206E4FA:
	ldr r1, [sp, #0x8]
	add r0, r4, #0x0
	add r2, r5, #0x0
	bl StringExpandPlaceholders
	add r0, r5, #0x0
	bl String_dtor
	add r0, r4, #0x0
	bl FUN_0200AB18
	add r0, r6, #0x0
	bl DestroyMsgData
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0206E51C
FUN_0206E51C: ; 0x0206E51C
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	ldr r4, [sp, #0x18]
	cmp r3, #0x1
	beq _0206E52E
	cmp r3, #0x2
	beq _0206E54C
	b _0206E56A
_0206E52E:
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0x7
	add r3, r4, #0x0
	bl NewMsgDataFromNarc
	add r4, r0, #0x0
	mov r1, #0x38
	add r2, r5, #0x0
	bl ReadMsgDataIntoString
	add r0, r4, #0x0
	bl DestroyMsgData
	pop {r3-r7, pc}
_0206E54C:
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0x7
	add r3, r4, #0x0
	bl NewMsgDataFromNarc
	add r4, r0, #0x0
	mov r1, #0x6f
	add r2, r5, #0x0
	bl ReadMsgDataIntoString
	add r0, r4, #0x0
	bl DestroyMsgData
	pop {r3-r7, pc}
_0206E56A:
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xc7
	add r3, r4, #0x0
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0200AA80
	add r4, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0x24
	bl NewString_ReadMsgData
	add r6, r0, #0x0
	ldr r2, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200ABC0
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl StringExpandPlaceholders
	add r0, r6, #0x0
	bl String_dtor
	add r0, r4, #0x0
	bl FUN_0200AB18
	add r0, r7, #0x0
	bl DestroyMsgData
	pop {r3-r7, pc}
	.balign 4
