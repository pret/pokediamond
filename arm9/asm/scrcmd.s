    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_020399A0
FUN_020399A0: ; 0x020399A0
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020399A4
FUN_020399A4: ; 0x020399A4
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020399A8
FUN_020399A8: ; 0x020399A8
	push {r3, lr}
	bl StopScript
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020399B4
FUN_020399B4: ; 0x020399B4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_020394B8
	strh r7, [r0, #0x0]
	ldr r1, _020399E4 ; =FUN_020399E8
	add r0, r5, #0x0
	str r4, [r5, #0x64]
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_020399E4: .word FUN_020399E8 

	thumb_func_start FUN_020399E8
FUN_020399E8: ; 0x020399E8
	push {r3, lr}
	add r1, r0, #0x0
	ldr r1, [r1, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	ldrh r1, [r0, #0x0]
	sub r1, r1, #0x1
	strh r1, [r0, #0x0]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02039A0A
	mov r0, #0x1
	pop {r3, pc}
_02039A0A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02039A10
FUN_02039A10: ; 0x02039A10
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02039A28
FUN_02039A28: ; 0x02039A28
	ldr r1, [r0, #0x8]
	add r2, r1, #0x1
	str r2, [r0, #0x8]
	ldrb r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r2, [r2, #0x0]
	lsl r1, r3, #0x2
	add r0, r0, r1
	str r2, [r0, #0x64]
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02039A40
FUN_02039A40: ; 0x02039A40
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r5, [r2, #0x0]
	bl ScriptReadWord
	lsl r1, r5, #0x2
	add r1, r4, r1
	str r0, [r1, #0x64]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02039A5C
FUN_02039A5C: ; 0x02039A5C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadWord
	ldrb r1, [r0, #0x0]
	lsl r0, r4, #0x2
	add r0, r5, r0
	str r1, [r0, #0x64]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02039A78
FUN_02039A78: ; 0x02039A78
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	strb r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02039A90
FUN_02039A90: ; 0x02039A90
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	lsl r1, r1, #0x2
	add r1, r4, r1
	ldr r1, [r1, #0x64]
	strb r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02039AAC
FUN_02039AAC: ; 0x02039AAC
	ldr r1, [r0, #0x8]
	add r2, r1, #0x1
	str r2, [r0, #0x8]
	ldrb r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	lsl r1, r1, #0x2
	add r1, r0, r1
	ldr r2, [r1, #0x64]
	lsl r1, r3, #0x2
	add r0, r0, r1
	str r2, [r0, #0x64]
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02039ACC
FUN_02039ACC: ; 0x02039ACC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadWord
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadWord
	ldrb r0, [r0, #0x0]
	strb r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02039AE4
FUN_02039AE4: ; 0x02039AE4
	cmp r0, r1
	bhs _02039AEC
	mov r0, #0x0
	bx lr
_02039AEC:
	cmp r0, r1
	bne _02039AF4
	mov r0, #0x1
	bx lr
_02039AF4:
	mov r0, #0x2
	bx lr

	thumb_func_start FUN_02039AF8
FUN_02039AF8: ; 0x02039AF8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x8]
	add r1, r0, #0x1
	str r1, [r4, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x64]
	str r2, [r4, #0x8]
	ldrb r1, [r1, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r1, r1, #0x2
	add r1, r4, r1
	ldr r1, [r1, #0x64]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02039AE4
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02039B28
FUN_02039B28: ; 0x02039B28
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x8]
	add r1, r0, #0x1
	str r1, [r4, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x64]
	str r2, [r4, #0x8]
	ldrb r1, [r1, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02039AE4
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02039B50
FUN_02039B50: ; 0x02039B50
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	lsl r1, r1, #0x2
	add r1, r4, r1
	ldr r1, [r1, #0x64]
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	bl ScriptReadWord
	ldrb r1, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_02039AE4
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02039B78
FUN_02039B78: ; 0x02039B78
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	ldr r2, [r4, #0x8]
	ldrb r0, [r0, #0x0]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	lsl r1, r1, #0x2
	add r1, r4, r1
	ldr r1, [r1, #0x64]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02039AE4
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02039BA0
FUN_02039BA0: ; 0x02039BA0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	ldr r2, [r4, #0x8]
	ldrb r0, [r0, #0x0]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	bl FUN_02039AE4
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02039BBC
FUN_02039BBC: ; 0x02039BBC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadWord
	ldrb r4, [r0, #0x0]
	add r0, r5, #0x0
	bl ScriptReadWord
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_02039AE4
	strb r0, [r5, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02039BDC
FUN_02039BDC: ; 0x02039BDC
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	ldrh r5, [r0, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02039AE4
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02039C08
FUN_02039C08: ; 0x02039C08
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r1, r0, #0x0
	ldrh r0, [r4, #0x0]
	ldrh r1, [r1, #0x0]
	bl FUN_02039AE4
	strb r0, [r5, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02039C40
FUN_02039C40: ; 0x02039C40
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x7
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xe
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02038EB0
	str r0, [r6, #0x0]
	ldrb r0, [r4, #0x0]
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02039C78
FUN_02039C78: ; 0x02039C78
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x5
	add r0, r5, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x7
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xe
	bl FUN_02039438
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	mov r0, #0x1
	strb r0, [r6, #0x0]
	add r0, r5, #0x0
	bl FUN_02038EB0
	str r0, [r7, #0x0]
	ldrb r0, [r4, #0x0]
	ldr r1, _02039CC4 ; =FUN_02039CC8
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	ldr r0, [sp, #0x0]
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_02039CC4: .word FUN_02039CC8 

	thumb_func_start FUN_02039CC8
FUN_02039CC8: ; 0x02039CC8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x5
	bl FUN_02039438
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02039CDE
	mov r0, #0x1
	pop {r3, pc}
_02039CDE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02039CE4
FUN_02039CE4: ; 0x02039CE4
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x5
	bl FUN_02039438
	mov r1, #0x0
	strb r1, [r0, #0x0]
	add r0, r1, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02039CF8
FUN_02039CF8: ; 0x02039CF8
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	add r2, r0, #0x0
	ldr r1, [r4, #0x8]
	add r0, r4, #0x0
	add r1, r1, r2
	bl ScriptJump
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02039D10
FUN_02039D10: ; 0x02039D10
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadWord
	add r7, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_02058448
	cmp r4, r0
	bne _02039D44
	ldr r1, [r5, #0x8]
	add r0, r5, #0x0
	add r1, r1, r7
	bl ScriptJump
_02039D44:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02039D48
FUN_02039D48: ; 0x02039D48
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x74]
	bl FUN_02046534
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r4, [r1, #0x0]
	add r0, r5, #0x0
	bl ScriptReadWord
	add r2, r0, #0x0
	cmp r6, r4
	bne _02039D72
	ldr r1, [r5, #0x8]
	add r0, r5, #0x0
	add r1, r1, r2
	bl ScriptJump
_02039D72:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02039D78
FUN_02039D78: ; 0x02039D78
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x9
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r4, [r1, #0x0]
	add r0, r5, #0x0
	bl ScriptReadWord
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	cmp r0, r4
	bne _02039DA8
	ldr r1, [r5, #0x8]
	add r0, r5, #0x0
	add r1, r1, r2
	bl ScriptJump
_02039DA8:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02039DAC
FUN_02039DAC: ; 0x02039DAC
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	add r2, r0, #0x0
	ldr r1, [r4, #0x8]
	add r0, r4, #0x0
	add r1, r1, r2
	bl ScriptCall
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02039DC4
FUN_02039DC4: ; 0x02039DC4
	push {r3, lr}
	bl ScriptReturn
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02039DD0
FUN_02039DD0: ; 0x02039DD0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadWord
	add r1, r0, #0x0
	lsl r0, r4, #0x1
	add r3, r4, r0
	ldr r0, _02039E00 ; =0x020F34E8
	ldrb r2, [r5, #0x2]
	add r0, r0, r3
	ldrb r0, [r2, r0]
	cmp r0, #0x1
	bne _02039DFC
	ldr r2, [r5, #0x8]
	add r0, r5, #0x0
	add r1, r2, r1
	bl ScriptJump
_02039DFC:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02039E00: .word 0x020F34E8

	thumb_func_start FUN_02039E04
FUN_02039E04: ; 0x02039E04
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadWord
	add r1, r0, #0x0
	lsl r0, r4, #0x1
	add r3, r4, r0
	ldr r0, _02039E34 ; =0x020F34E8
	ldrb r2, [r5, #0x2]
	add r0, r0, r3
	ldrb r0, [r2, r0]
	cmp r0, #0x1
	bne _02039E30
	ldr r2, [r5, #0x8]
	add r0, r5, #0x0
	add r1, r2, r1
	bl ScriptCall
_02039E30:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02039E34: .word 0x020F34E8

	thumb_func_start FUN_02039E38
FUN_02039E38: ; 0x02039E38
	push {r4, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0203953C
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02039E50
FUN_02039E50: ; 0x02039E50
	push {r4, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02039550
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02039E68
FUN_02039E68: ; 0x02039E68
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02039528
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02039E84
FUN_02039E84: ; 0x02039E84
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldrh r1, [r6, #0x0]
	add r0, r5, #0x0
	bl FUN_02039528
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02039EC0
FUN_02039EC0: ; 0x02039EC0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r1, r0, #0x0
	ldrh r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_0203953C
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02039EE8
FUN_02039EE8: ; 0x02039EE8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0203965C
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02039F0C
FUN_02039F0C: ; 0x02039F0C
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02039678
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02039F30
FUN_02039F30: ; 0x02039F30
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02039640
	strb r0, [r5, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02039F58
FUN_02039F58: ; 0x02039F58
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	ldrh r1, [r4, #0x0]
	add r0, r1, r0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02039F88
FUN_02039F88: ; 0x02039F88
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	ldrh r1, [r4, #0x0]
	sub r0, r1, r0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02039FB8
FUN_02039FB8: ; 0x02039FB8
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02039FDC
FUN_02039FDC: ; 0x02039FDC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	ldrh r0, [r0, #0x0]
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203A00C
FUN_0203A00C: ; 0x0203A00C
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203A038
FUN_0203A038: ; 0x0203A038
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r2, [r2, #0x0]
	ldr r1, [r0, #0x78]
	bl FUN_021E2C24
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203A04C
FUN_0203A04C: ; 0x0203A04C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	add r2, r5, #0x0
	mov r3, #0x20
	bl FUN_0200A86C
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_021E2C24
	add r0, r5, #0x0
	bl FUN_0200A8B8
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203A098
FUN_0203A098: ; 0x0203A098
	push {r3-r6, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	add r2, r5, #0x0
	mov r3, #0x20
	bl FUN_0200A86C
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0x1
	bl FUN_021E2BD0
	add r0, r5, #0x0
	bl FUN_0200A8B8
	ldr r1, _0203A0F8 ; =FUN_0203A2F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_0203A0F8: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A0FC
FUN_0203A0FC: ; 0x0203A0FC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl FUN_021E2C58
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203A13C
FUN_0203A13C: ; 0x0203A13C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl FUN_021E2C58
	ldr r1, _0203A184 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203A184: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A188
FUN_0203A188: ; 0x0203A188
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldrb r3, [r2, #0x0]
	add r1, #0xa8
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	bne _0203A1AA
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_0203A1AA:
	lsl r1, r3, #0x4
	add r1, r3, r1
	add r2, #0x90
	lsl r1, r1, #0x4
	add r4, r2, r1
	ldrh r1, [r2, r1]
	ldr r2, _0203A204 ; =0x0000FFFF
	cmp r1, r2
	bne _0203A1E2
	ldr r2, _0203A208 ; =0x0000022B
	mov r0, #0x1
	mov r1, #0x1a
	mov r3, #0x20
	bl FUN_0200A86C
	add r6, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldrh r2, [r4, #0x2]
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r3, #0x1
	bl FUN_021E2BD0
	add r0, r6, #0x0
	bl FUN_0200A8B8
	b _0203A1F4
_0203A1E2:
	mov r2, #0x6
	ldrsh r2, [r4, r2]
	str r2, [sp, #0x0]
	mov r2, #0x1
	str r2, [sp, #0x4]
	ldrh r2, [r4, #0x2]
	ldrh r3, [r4, #0x4]
	bl FUN_021E2C58
_0203A1F4:
	ldr r1, _0203A20C ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_0203A204: .word 0x0000FFFF
_0203A208: .word 0x0000022B
_0203A20C: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A210
FUN_0203A210: ; 0x0203A210
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r2, [r5, #0x8]
	ldr r6, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	ldr r1, [r5, #0x8]
	add r2, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r3, [r1, #0x0]
	mov r1, #0x0
	add r0, sp, #0x4
	strb r1, [r0, #0x0]
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	ldr r0, [r6, #0xc]
	add r1, r7, #0x0
	bl FUN_02244210
	add r6, r0, #0x0
	add r2, sp, #0x4
	ldrb r2, [r2, #0x0]
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, r2
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	mov r3, #0x1
	bl FUN_021E2CBC
	add r0, r6, #0x0
	bl FUN_0200AB18
	ldr r1, _0203A284 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203A284: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A288
FUN_0203A288: ; 0x0203A288
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, sp, #0x4
	add r1, r5, #0x0
	bl FUN_021E2BB8
	mov r1, #0x3
	add r0, sp, #0x4
	strb r1, [r0, #0x2]
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	ldr r1, [r5, #0x78]
	add r0, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_021E2BD0
	ldr r1, _0203A2C0 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_0203A2C0: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A2C4
FUN_0203A2C4: ; 0x0203A2C4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	mov r3, #0x1
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldrb r2, [r2, #0x0]
	ldr r1, [r4, #0x78]
	bl FUN_021E2BD0
	ldr r1, _0203A2EC ; =FUN_0203A2F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203A2EC: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A2F0
FUN_0203A2F0: ; 0x0203A2F0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	bl FUN_02039438
	ldrb r0, [r0, #0x0]
	bl FUN_020546C8
	pop {r3, pc}

	thumb_func_start FUN_0203A304
FUN_0203A304: ; 0x0203A304
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	lsl r2, r2, #0x18
	ldr r1, [r4, #0x78]
	add r0, r4, #0x0
	lsr r2, r2, #0x18
	mov r3, #0x1
	bl FUN_021E2BD0
	ldr r1, _0203A33C ; =FUN_0203A2F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203A33C: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A340
FUN_0203A340: ; 0x0203A340
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, sp, #0x4
	add r1, r5, #0x0
	bl FUN_021E2BB8
	lsl r2, r4, #0x18
	mov r3, #0x1
	add r0, sp, #0x4
	strb r3, [r0, #0x1]
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	ldr r1, [r5, #0x78]
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_021E2BD0
	ldr r1, _0203A384 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_0203A384: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A388
FUN_0203A388: ; 0x0203A388
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	mov r3, #0x0
	str r3, [sp, #0x0]
	lsl r2, r2, #0x18
	ldr r1, [r4, #0x78]
	add r0, r4, #0x0
	lsr r2, r2, #0x18
	bl FUN_021E2BD0
	ldr r1, _0203A3C0 ; =FUN_0203A2F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_0203A3C0: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A3C4
FUN_0203A3C4: ; 0x0203A3C4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02058488
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [r4, #0x78]
	add r0, r4, #0x0
	mov r3, #0x1
	bl FUN_021E2BD0
	ldr r1, _0203A3FC ; =FUN_0203A2F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_0203A3FC: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A400
FUN_0203A400: ; 0x0203A400
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r1, [r5, #0x8]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r4, [r1, #0x0]
	bl FUN_02030F40
	cmp r0, #0x0
	bne _0203A428
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [r5, #0x78]
	add r0, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x1
	bl FUN_021E2BD0
	b _0203A448
_0203A428:
	add r0, sp, #0x4
	add r1, r5, #0x0
	bl FUN_021E2BB8
	mov r1, #0x1
	add r0, sp, #0x4
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	ldr r1, [r5, #0x78]
	add r0, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_021E2BD0
_0203A448:
	ldr r1, _0203A458 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	nop
_0203A458: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A45C
FUN_0203A45C: ; 0x0203A45C
	push {r3, lr}
	ldr r1, _0203A468 ; =FUN_0203A46C
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203A468: .word FUN_0203A46C 

	thumb_func_start FUN_0203A46C
FUN_0203A46C: ; 0x0203A46C
	ldr r0, _0203A480 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0203A47A
	mov r0, #0x1
	bx lr
_0203A47A:
	mov r0, #0x0
	bx lr
	nop
_0203A480: .word 0x021C48B8

	thumb_func_start FUN_0203A484
FUN_0203A484: ; 0x0203A484
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [r4, #0x64]
	ldr r1, _0203A4A8 ; =FUN_0203A4AC
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203A4A8: .word FUN_0203A4AC 

	thumb_func_start FUN_0203A4AC
FUN_0203A4AC: ; 0x0203A4AC
	ldr r1, _0203A4CC ; =0x021C48B8
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	tst r1, r2
	beq _0203A4BA
	mov r0, #0x1
	bx lr
_0203A4BA:
	ldr r1, [r0, #0x64]
	sub r1, r1, #0x1
	str r1, [r0, #0x64]
	bne _0203A4C6
	mov r0, #0x1
	bx lr
_0203A4C6:
	mov r0, #0x0
	bx lr
	nop
_0203A4CC: .word 0x021C48B8

	thumb_func_start FUN_0203A4D0
FUN_0203A4D0: ; 0x0203A4D0
	push {r3, lr}
	ldr r1, _0203A4DC ; =FUN_0203A4E0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203A4DC: .word FUN_0203A4E0 

	thumb_func_start FUN_0203A4E0
FUN_0203A4E0: ; 0x0203A4E0
	push {r4, lr}
	ldr r1, _0203A55C ; =0x021C48B8
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	add r3, r2, #0x0
	tst r3, r1
	beq _0203A4F2
	mov r0, #0x1
	pop {r4, pc}
_0203A4F2:
	mov r3, #0x40
	tst r3, r2
	beq _0203A506
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	b _0203A556
_0203A506:
	mov r3, #0x80
	tst r3, r2
	beq _0203A51A
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	b _0203A556
_0203A51A:
	mov r3, #0x20
	tst r3, r2
	beq _0203A52E
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	b _0203A556
_0203A52E:
	mov r3, #0x10
	add r4, r2, #0x0
	tst r4, r3
	beq _0203A542
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	b _0203A556
_0203A542:
	lsl r1, r3, #0x6
	tst r1, r2
	beq _0203A552
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02039460
	b _0203A556
_0203A552:
	mov r0, #0x0
	pop {r4, pc}
_0203A556:
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203A55C: .word 0x021C48B8

	thumb_func_start FUN_0203A560
FUN_0203A560: ; 0x0203A560
	push {r3, lr}
	ldr r1, _0203A56C ; =FUN_0203A570
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203A56C: .word FUN_0203A570 

	thumb_func_start FUN_0203A570
FUN_0203A570: ; 0x0203A570
	ldr r0, _0203A58C ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0203A57E
	mov r0, #0x1
	bx lr
_0203A57E:
	mov r0, #0xf0
	tst r0, r1
	beq _0203A588
	mov r0, #0x1
	bx lr
_0203A588:
	mov r0, #0x0
	bx lr
	.balign 4
_0203A58C: .word 0x021C48B8

	thumb_func_start FUN_0203A590
FUN_0203A590: ; 0x0203A590
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x6
	add r0, r4, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02039438
	add r1, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r2, #0x3
	bl FUN_020545B8
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02039438
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl LoadPlayerDataAddress
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02054608
	mov r0, #0x1
	strb r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203A5D8
FUN_0203A5D8: ; 0x0203A5D8
	push {r3-r5, lr}
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x1
	add r0, r4, #0x0
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x6
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200D0E0
	add r0, r5, #0x0
	bl FUN_02019178
	mov r0, #0x0
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203A608
FUN_0203A608: ; 0x0203A608
	push {r3-r5, lr}
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x1
	add r0, r4, #0x0
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x6
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02019178
	mov r0, #0x0
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203A630
FUN_0203A630: ; 0x0203A630
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x31
	add r0, r4, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2d
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x32
	bl FUN_02039438
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x33
	bl FUN_02039438
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x2e
	bl FUN_02039438
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x34
	bl FUN_02039438
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	strh r1, [r6, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	strh r1, [r7, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r2, [r2, #0x0]
	ldr r1, [sp, #0x0]
	strh r2, [r1, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r2, [r2, #0x0]
	ldr r1, [sp, #0x4]
	strh r2, [r1, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r2, [r2, #0x0]
	ldr r1, [sp, #0x8]
	strh r2, [r1, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	strh r1, [r0, #0x0]
	ldr r1, _0203A6C4 ; =FUN_0203A6C8
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0203A6C4: .word FUN_0203A6C8 

	thumb_func_start FUN_0203A6C8
FUN_0203A6C8: ; 0x0203A6C8
	push {r4-r7, lr}
	sub sp, #0xc
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x31
	add r0, r4, #0x0
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x32
	bl FUN_02039438
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x33
	bl FUN_02039438
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x34
	bl FUN_02039438
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x2d
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2e
	bl FUN_02039438
	add r5, r0, #0x0
	ldrh r0, [r6, #0x0]
	cmp r0, #0x0
	bne _0203A71E
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	bne _0203A71E
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0203A71E:
	ldrh r3, [r7, #0x0]
	cmp r3, #0x0
	beq _0203A740
	ldr r0, [sp, #0x8]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	ldr r0, [r4, #0x8]
	bne _0203A738
	mov r1, #0x3
	mov r2, #0x1
	bl FUN_020179E0
	b _0203A740
_0203A738:
	mov r1, #0x3
	mov r2, #0x2
	bl FUN_020179E0
_0203A740:
	ldr r0, [sp, #0x4]
	ldrh r3, [r0, #0x0]
	cmp r3, #0x0
	beq _0203A764
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	ldr r0, [r4, #0x8]
	bne _0203A75C
	mov r1, #0x3
	mov r2, #0x4
	bl FUN_020179E0
	b _0203A764
_0203A75C:
	mov r1, #0x3
	mov r2, #0x5
	bl FUN_020179E0
_0203A764:
	ldrh r0, [r6, #0x0]
	cmp r0, #0x0
	beq _0203A76E
	sub r0, r0, #0x1
	strh r0, [r6, #0x0]
_0203A76E:
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0203A778
	sub r0, r0, #0x1
	strh r0, [r5, #0x0]
_0203A778:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0203A780
FUN_0203A780: ; 0x0203A780
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x11
	add r0, r4, #0x0
	bl FUN_02039438
	str r0, [sp, #0x18]
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	str r0, [sp, #0xc]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	cmp r6, #0x0
	bne _0203A7E0
	add r0, r4, #0x0
	mov r1, #0xa
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02058510
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
_0203A7E0:
	ldr r0, [r4, #0x60]
	ldr r1, [sp, #0x10]
	add r2, r6, #0x0
	bl FUN_021E8128
	ldr r0, [r4, #0x60]
	mov r1, #0x1
	bl FUN_021E8130
	add r0, r4, #0x0
	bl FUN_021E8158
	ldr r2, [sp, #0x18]
	ldr r0, [r5, #0x78]
	ldr r1, [sp, #0xc]
	ldr r2, [r2, #0x0]
	bl FUN_0200A8E0
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x18]
	ldr r0, [r0, #0x0]
	ldr r1, [r7, #0x0]
	ldr r2, [r2, #0x0]
	bl FUN_0200B7B8
	ldr r0, [r4, #0x60]
	bl FUN_021E8140
	mov r3, #0x0
	str r3, [sp, #0x0]
	str r3, [sp, #0x4]
	str r3, [sp, #0x8]
	ldr r2, [r7, #0x0]
	mov r1, #0x1
	bl FUN_0201BD84
	mov r0, #0x1
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0203A830
FUN_0203A830: ; 0x0203A830
	push {r3-r5, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r4, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r5, [r2, #0x0]
	bl ScriptReadHalfword
	add r2, r0, #0x0
	ldr r0, [r4, #0x60]
	add r1, r5, #0x0
	bl FUN_021E8128
	ldr r0, [r4, #0x60]
	mov r1, #0x1
	bl FUN_021E8130
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203A85C
FUN_0203A85C: ; 0x0203A85C
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r3, #0x60]
	bl FUN_021E8130
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203A878
FUN_0203A878: ; 0x0203A878
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x60]
	bl FUN_021E8148
	cmp r0, #0x1
	bne _0203A88E
	mov r0, #0x0
	pop {r4, pc}
_0203A88E:
	ldr r1, _0203A89C ; =FUN_0203A8A0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203A89C: .word FUN_0203A8A0 

	thumb_func_start FUN_0203A8A0
FUN_0203A8A0: ; 0x0203A8A0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x60]
	bl FUN_021E8148
	cmp r0, #0x1
	bne _0203A8B4
	mov r0, #0x1
	pop {r3, pc}
_0203A8B4:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203A8B8
FUN_0203A8B8: ; 0x0203A8B8
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x3
	add r0, r4, #0x0
	bl FUN_02039438
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x11
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x8]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x78]
	ldr r1, [sp, #0x0]
	ldr r2, [r6, #0x0]
	bl FUN_0200A8E0
	ldr r0, [sp, #0x8]
	ldr r1, [r7, #0x0]
	ldr r0, [r0, #0x0]
	ldr r2, [r6, #0x0]
	bl FUN_0200B7B8
	ldr r0, [r4, #0x60]
	bl FUN_021E8140
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl LoadPlayerDataAddress
	add r2, r0, #0x0
	ldr r1, [r7, #0x0]
	add r0, r4, #0x0
	mov r3, #0x1
	bl FUN_02054658
	ldr r1, [sp, #0x4]
	strb r0, [r1, #0x0]
	ldr r0, [sp, #0xc]
	ldr r1, _0203A948 ; =FUN_0203A94C
	str r0, [r5, #0x64]
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0203A948: .word FUN_0203A94C 

	thumb_func_start FUN_0203A94C
FUN_0203A94C: ; 0x0203A94C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x3
	add r0, r5, #0x0
	bl FUN_02039438
	ldr r1, [r7, #0x64]
	add r6, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0x60]
	bl FUN_021E8144
	ldrb r0, [r6, #0x0]
	ldr r5, _0203A9E8 ; =0x0000FFFF
	bl FUN_020546C8
	cmp r0, #0x1
	bne _0203A986
	mov r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_0203A986:
	ldr r0, _0203A9EC ; =0x021C48B8
	mov r1, #0x40
	ldr r0, [r0, #0x48]
	tst r1, r0
	beq _0203A994
	mov r5, #0x0
	b _0203A9B0
_0203A994:
	mov r1, #0x80
	tst r1, r0
	beq _0203A99E
	mov r5, #0x1
	b _0203A9B0
_0203A99E:
	mov r1, #0x20
	tst r1, r0
	beq _0203A9A8
	mov r5, #0x2
	b _0203A9B0
_0203A9A8:
	mov r1, #0x10
	tst r1, r0
	beq _0203A9B0
	mov r5, #0x3
_0203A9B0:
	ldr r1, _0203A9E8 ; =0x0000FFFF
	cmp r5, r1
	beq _0203A9D0
	ldrb r0, [r6, #0x0]
	bl FUN_0201BD7C
	add r7, #0x80
	ldr r0, [r7, #0x0]
	add r1, r5, #0x0
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_0203A9D0:
	mov r1, #0x1
	lsl r1, r1, #0xa
	tst r0, r1
	beq _0203A9E4
	ldrb r0, [r6, #0x0]
	bl FUN_0201BD7C
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r3-r7, pc}
_0203A9E4:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0203A9E8: .word 0x0000FFFF
_0203A9EC: .word 0x021C48B8

	thumb_func_start FUN_0203A9F0
FUN_0203A9F0: ; 0x0203A9F0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203AA08 ; =FUN_0203AA0C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203AA08: .word FUN_0203AA0C 

	thumb_func_start FUN_0203AA0C
FUN_0203AA0C: ; 0x0203AA0C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, _0203AA88 ; =0x021C48B8
	ldr r1, _0203AA8C ; =0x0000FFFF
	ldr r2, [r0, #0x48]
	mov r0, #0x3
	add r3, r2, #0x0
	tst r3, r0
	beq _0203AA36
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0203AA36:
	mov r3, #0x40
	tst r3, r2
	beq _0203AA40
	mov r1, #0x0
	b _0203AA5C
_0203AA40:
	mov r3, #0x80
	tst r3, r2
	beq _0203AA4A
	mov r1, #0x1
	b _0203AA5C
_0203AA4A:
	mov r3, #0x20
	tst r3, r2
	beq _0203AA54
	mov r1, #0x2
	b _0203AA5C
_0203AA54:
	mov r3, #0x10
	tst r3, r2
	beq _0203AA5C
	add r1, r0, #0x0
_0203AA5C:
	ldr r0, _0203AA8C ; =0x0000FFFF
	cmp r1, r0
	beq _0203AA74
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0203AA74:
	mov r0, #0x1
	lsl r0, r0, #0xa
	tst r0, r2
	beq _0203AA82
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}
_0203AA82:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203AA88: .word 0x021C48B8
_0203AA8C: .word 0x0000FFFF

	thumb_func_start FUN_0203AA90
FUN_0203AA90: ; 0x0203AA90
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02039460
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203AAA0
FUN_0203AAA0: ; 0x0203AAA0
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x2
	add r0, r4, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x8]
	ldr r2, _0203AAF4 ; =0x000003D9
	mov r1, #0x3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x8]
	ldr r1, _0203AAF8 ; =0x020F34E0
	ldr r2, _0203AAF4 ; =0x000003D9
	mov r3, #0xb
	bl FUN_02002198
	str r0, [r6, #0x0]
	ldr r1, _0203AAFC ; =FUN_0203AB00
	add r0, r5, #0x0
	str r7, [r5, #0x64]
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203AAF4: .word 0x000003D9
_0203AAF8: .word 0x020F34E0
_0203AAFC: .word FUN_0203AB00 

	thumb_func_start FUN_0203AB00
FUN_0203AB00: ; 0x0203AB00
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x2
	add r0, r6, #0x0
	bl FUN_02039438
	ldr r1, [r5, #0x64]
	add r4, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x4
	bl FUN_020021AC
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	bne _0203AB34
	mov r0, #0x0
	pop {r4-r6, pc}
_0203AB34:
	cmp r0, #0x0
	bne _0203AB3C
	mov r0, #0x0
	b _0203AB3E
_0203AB3C:
	mov r0, #0x1
_0203AB3E:
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_0203AB44
FUN_0203AB44: ; 0x0203AB44
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x12
	bl FUN_02039438
	add r5, r0, #0x0
	ldr r1, _0203AB70 ; =0x000003E2
	add r0, r4, #0x0
	bl FUN_0200D858
	str r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203AB70: .word 0x000003E2

	thumb_func_start FUN_0203AB74
FUN_0203AB74: ; 0x0203AB74
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x12
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_0200DBFC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203AB8C
FUN_0203AB8C: ; 0x0203AB8C
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl FUN_020394B8
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl FUN_021E1BF8
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0203AC14
FUN_0203AC14: ; 0x0203AC14
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl FUN_020394B8
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x78]
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl FUN_021E1BF8
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0203AC9C
FUN_0203AC9C: ; 0x0203AC9C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r1, [r4, #0x8]
	add r3, r1, #0x1
	str r3, [r4, #0x8]
	ldrb r1, [r1, #0x0]
	add r2, r3, #0x1
	str r2, [r4, #0x8]
	ldrb r2, [r3, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_021E1C4C
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203ACC4
FUN_0203ACC4: ; 0x0203ACC4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	bl FUN_021E1C4C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203AD08
FUN_0203AD08: ; 0x0203AD08
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_021E1C54
	ldr r1, _0203AD28 ; =FUN_0203AD2C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AD28: .word FUN_0203AD2C 

	thumb_func_start FUN_0203AD2C
FUN_0203AD2C: ; 0x0203AD2C
	push {r3, lr}
	add r1, r0, #0x0
	ldr r1, [r1, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	ldrh r1, [r0, #0x0]
	ldr r0, _0203AD50 ; =0x0000EEEE
	cmp r1, r0
	beq _0203AD4A
	mov r0, #0x1
	pop {r3, pc}
_0203AD4A:
	mov r0, #0x0
	pop {r3, pc}
	nop
_0203AD50: .word 0x0000EEEE

	thumb_func_start FUN_0203AD54
FUN_0203AD54: ; 0x0203AD54
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_021E1C54
	ldr r1, _0203AD74 ; =FUN_0203AD78
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AD74: .word FUN_0203AD78 

	thumb_func_start FUN_0203AD78
FUN_0203AD78: ; 0x0203AD78
	push {r4-r6, lr}
	add r1, r0, #0x0
	add r0, #0x80
	ldr r1, [r1, #0x64]
	ldr r5, [r0, #0x0]
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	ldrh r1, [r4, #0x0]
	ldr r0, _0203ADC0 ; =0x0000EEEE
	cmp r1, r0
	bne _0203ADBC
	ldr r0, [r5, #0x78]
	bl FUN_02052714
	cmp r0, #0x0
	beq _0203ADB8
	mov r0, #0x8
	strh r0, [r4, #0x0]
	ldr r0, [r6, #0x0]
	bl FUN_021E1ECC
	mov r0, #0x1
	pop {r4-r6, pc}
_0203ADB8:
	mov r0, #0x0
	pop {r4-r6, pc}
_0203ADBC:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203ADC0: .word 0x0000EEEE

	thumb_func_start FUN_0203ADC4
FUN_0203ADC4: ; 0x0203ADC4
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl FUN_020394B8
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl FUN_021E1F34
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0203AE4C
FUN_0203AE4C: ; 0x0203AE4C
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl FUN_020394B8
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x78]
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl FUN_021E1F34
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0203AED4
FUN_0203AED4: ; 0x0203AED4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r3, r0, #0x0
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_021E1F58
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0203AF34
FUN_0203AF34: ; 0x0203AF34
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_021E1F60
	ldr r1, _0203AF54 ; =FUN_0203AD2C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AF54: .word FUN_0203AD2C 

	thumb_func_start FUN_0203AF58
FUN_0203AF58: ; 0x0203AF58
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_021E26CC
	ldr r1, _0203AF80 ; =FUN_0203AD2C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AF80: .word FUN_0203AD2C 

	thumb_func_start FUN_0203AF84
FUN_0203AF84: ; 0x0203AF84
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_021E2B80
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0203AFA4
FUN_0203AFA4: ; 0x0203AFA4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_021E2B9C
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0203AFC4
FUN_0203AFC4: ; 0x0203AFC4
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadWord
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl FUN_0203B120
	add r6, r0, #0x0
	bne _0203AFF6
	bl ErrorHandling
_0203AFF6:
	ldr r1, [r5, #0x8]
	add r0, r6, #0x0
	add r1, r1, r4
	bl FUN_0205AEA4
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	bl FUN_02039438
	ldrb r1, [r0, #0x0]
	add r5, #0x80
	mov r2, #0x0
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_0203B174
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203B024
FUN_0203B024: ; 0x0203B024
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_0203B120
	str r0, [sp, #0x4]
	cmp r0, #0x0
	bne _0203B07A
	bl ErrorHandling
_0203B07A:
	mov r0, #0x4
	add r1, r0, #0x0
	add r1, #0xfc
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	bl FUN_02058B2C
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp, #0x4]
	bl FUN_02058B4C
	lsl r0, r0, #0x10
	ldr r2, [sp, #0x0]
	lsr r0, r0, #0x10
	mov r1, #0x0
	cmp r6, r2
	bhs _0203B0B0
	mov r2, #0xf
	strh r2, [r4, #0x0]
	ldr r2, [sp, #0x0]
	add r1, r1, #0x1
	sub r2, r2, r6
	strh r2, [r4, #0x2]
	b _0203B0C0
_0203B0B0:
	cmp r6, r2
	bls _0203B0C0
	mov r2, #0xe
	strh r2, [r4, #0x0]
	ldr r2, [sp, #0x0]
	add r1, r1, #0x1
	sub r2, r6, r2
	strh r2, [r4, #0x2]
_0203B0C0:
	cmp r0, r7
	bhs _0203B0D4
	lsl r2, r1, #0x2
	mov r3, #0xc
	strh r3, [r4, r2]
	sub r3, r7, r0
	add r0, r4, r2
	strh r3, [r0, #0x2]
	add r1, r1, #0x1
	b _0203B0E6
_0203B0D4:
	cmp r0, r7
	bls _0203B0E6
	lsl r2, r1, #0x2
	mov r3, #0xd
	strh r3, [r4, r2]
	sub r3, r0, r7
	add r0, r4, r2
	strh r3, [r0, #0x2]
	add r1, r1, #0x1
_0203B0E6:
	lsl r2, r1, #0x2
	mov r0, #0xfe
	strh r0, [r4, r2]
	mov r1, #0x0
	add r0, r4, r2
	strh r1, [r0, #0x2]
	ldr r0, [sp, #0x4]
	add r1, r4, #0x0
	bl FUN_0205AEA4
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	bl FUN_02039438
	ldrb r1, [r0, #0x0]
	add r5, #0x80
	add r2, r4, #0x0
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	bl FUN_0203B174
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0203B120
FUN_0203B120: ; 0x0203B120
	push {r3, lr}
	cmp r1, #0xf2
	bne _0203B130
	ldr r0, [r0, #0x34]
	mov r1, #0x30
	bl FUN_020580B4
	pop {r3, pc}
_0203B130:
	cmp r1, #0xf1
	bne _0203B13E
	mov r1, #0xb
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	pop {r3, pc}
_0203B13E:
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203B148
FUN_0203B148: ; 0x0203B148
	push {r3, lr}
	ldr r1, _0203B154 ; =FUN_0203B158
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203B154: .word FUN_0203B158 

	thumb_func_start FUN_0203B158
FUN_0203B158: ; 0x0203B158
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	bl FUN_02039438
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B16E
	mov r0, #0x1
	pop {r3, pc}
_0203B16E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203B174
FUN_0203B174: ; 0x0203B174
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0x4
	mov r1, #0x10
	add r7, r2, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	bne _0203B18E
	bl ErrorHandling
	pop {r3-r7, pc}
_0203B18E:
	str r5, [r4, #0xc]
	str r6, [r4, #0x4]
	ldr r0, _0203B1A4 ; =FUN_0203B1A8
	add r1, r4, #0x0
	mov r2, #0x0
	str r7, [r4, #0x8]
	bl FUN_0200CA44
	str r0, [r4, #0x0]
	pop {r3-r7, pc}
	nop
_0203B1A4: .word FUN_0203B1A8 

	thumb_func_start FUN_0203B1A8
FUN_0203B1A8: ; 0x0203B1A8
	push {r3-r5, lr}
	add r5, r1, #0x0
	ldr r0, [r5, #0xc]
	mov r1, #0x4
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r5, #0x4]
	bl FUN_0205AEF0
	cmp r0, #0x1
	bne _0203B1EC
	ldr r0, [r5, #0x4]
	bl FUN_0205AEFC
	ldr r0, [r5, #0x0]
	bl FUN_0200CAB4
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	beq _0203B1D6
	bl FUN_02016A18
_0203B1D6:
	add r0, r5, #0x0
	bl FUN_02016A18
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203B1E8
	bl ErrorHandling
	pop {r3-r5, pc}
_0203B1E8:
	sub r0, r0, #0x1
	strb r0, [r4, #0x0]
_0203B1EC:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203B1F0
FUN_0203B1F0: ; 0x0203B1F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0xa
	add r0, r4, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B20E
	ldr r0, [r4, #0x34]
	bl FUN_02058780
	b _0203B214
_0203B20E:
	add r0, r5, #0x0
	bl FUN_0203B2E0
_0203B214:
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203B218
FUN_0203B218: ; 0x0203B218
	push {r4-r6, lr}
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0xa
	add r0, r4, #0x0
	bl FUN_02039438
	add r5, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_020553A0
	ldr r1, _0203B2DC ; =0x021C5A0C
	add r6, r0, #0x0
	ldrb r2, [r1, #0x0]
	mov r1, #0x1
	tst r1, r2
	beq _0203B252
	bl FUN_0205AE28
	cmp r0, #0x1
	bne _0203B252
	add r0, r6, #0x0
	bl FUN_02058908
	ldr r1, _0203B2DC ; =0x021C5A0C
	mov r0, #0xfe
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B252:
	ldr r0, _0203B2DC ; =0x021C5A0C
	ldrb r1, [r0, #0x0]
	mov r0, #0x4
	tst r0, r1
	beq _0203B276
	ldr r0, [r5, #0x0]
	bl FUN_02058854
	cmp r0, #0x0
	bne _0203B276
	ldr r0, [r5, #0x0]
	bl FUN_02058908
	ldr r1, _0203B2DC ; =0x021C5A0C
	mov r0, #0xfb
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B276:
	ldr r0, _0203B2DC ; =0x021C5A0C
	ldrb r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0203B2A2
	ldr r0, [r4, #0x34]
	mov r1, #0x30
	bl FUN_020580B4
	add r4, r0, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	bne _0203B2A2
	add r0, r4, #0x0
	bl FUN_02058908
	ldr r1, _0203B2DC ; =0x021C5A0C
	mov r0, #0xfd
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B2A2:
	ldr r0, _0203B2DC ; =0x021C5A0C
	ldrb r1, [r0, #0x0]
	mov r0, #0x8
	tst r0, r1
	beq _0203B2CC
	ldr r0, [r5, #0x0]
	bl FUN_0205E7C4
	add r4, r0, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	bne _0203B2CC
	add r0, r4, #0x0
	bl FUN_02058908
	ldr r1, _0203B2DC ; =0x021C5A0C
	mov r0, #0xf7
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B2CC:
	ldr r0, _0203B2DC ; =0x021C5A0C
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B2D8
	mov r0, #0x1
	pop {r4-r6, pc}
_0203B2D8:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_0203B2DC: .word 0x021C5A0C

	thumb_func_start FUN_0203B2E0
FUN_0203B2E0: ; 0x0203B2E0
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0xa
	add r0, r4, #0x0
	bl FUN_02039438
	add r5, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_020553A0
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x34]
	mov r1, #0x30
	bl FUN_020580B4
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_0205E7C4
	add r6, r0, #0x0
	ldr r0, [r4, #0x34]
	ldr r1, _0203B3A8 ; =0x021C5A0C
	mov r2, #0x0
	strb r2, [r1, #0x0]
	bl FUN_02058780
	ldr r0, [sp, #0x4]
	bl FUN_0205AE28
	cmp r0, #0x0
	bne _0203B334
	ldr r1, _0203B3A8 ; =0x021C5A0C
	mov r0, #0x1
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	ldr r0, [sp, #0x4]
	bl FUN_02058914
_0203B334:
	ldr r0, [r5, #0x0]
	bl FUN_02058854
	cmp r0, #0x0
	beq _0203B34E
	ldr r1, _0203B3A8 ; =0x021C5A0C
	mov r0, #0x4
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	ldr r0, [r5, #0x0]
	bl FUN_02058914
_0203B34E:
	cmp r7, #0x0
	beq _0203B37A
	ldr r0, [r4, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED3C
	cmp r0, #0x1
	bne _0203B37A
	add r0, r7, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	beq _0203B37A
	ldr r1, _0203B3A8 ; =0x021C5A0C
	mov r0, #0x2
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	add r0, r7, #0x0
	bl FUN_02058914
_0203B37A:
	cmp r6, #0x0
	beq _0203B398
	add r0, r6, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	beq _0203B398
	ldr r1, _0203B3A8 ; =0x021C5A0C
	mov r0, #0x8
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_02058914
_0203B398:
	ldr r0, [sp, #0x0]
	ldr r1, _0203B3AC ; =FUN_0203B218
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203B3A8: .word 0x021C5A0C
_0203B3AC: .word FUN_0203B218 

	thumb_func_start FUN_0203B3B0
FUN_0203B3B0: ; 0x0203B3B0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_020587B0
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203B3C0
FUN_0203B3C0: ; 0x0203B3C0
	push {r4, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	ldr r0, [r4, #0x34]
	bl FUN_02058060
	bl FUN_02058908
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0203B3DC
FUN_0203B3DC: ; 0x0203B3DC
	push {r4, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	ldr r0, [r4, #0x34]
	bl FUN_02058060
	bl FUN_02058914
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0203B3F8
FUN_0203B3F8: ; 0x0203B3F8
	push {r3-r6, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02034B64
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02034B6C
	str r0, [sp, #0x0]
	ldr r3, [r5, #0x1c]
	ldr r0, [r5, #0x34]
	ldr r3, [r3, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020575D4
	cmp r0, #0x0
	bne _0203B43A
	bl ErrorHandling
_0203B43A:
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start FUN_0203B440
FUN_0203B440: ; 0x0203B440
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	bl FUN_02057688
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203B468
FUN_0203B468: ; 0x0203B468
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xb
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xc
	str r1, [sp, #0x0]
	mov r3, #0x0
	str r3, [sp, #0x4]
	ldr r1, [r0, #0x1c]
	add r2, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	ldr r0, [r0, #0x34]
	add r1, r6, #0x0
	bl FUN_0205753C
	str r0, [r4, #0x0]
	bl FUN_02059D1C
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	bl FUN_0205889C
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_020588B8
	ldr r0, [r4, #0x0]
	bl FUN_02058B7C
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	add r4, r0, #0x0
	ldr r1, [r1, #0x24]
	bl FUN_021EF5E0
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r0, r4, #0x0
	ldr r1, [r1, #0x20]
	bl FUN_0201EC68
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0203B500
FUN_0203B500: ; 0x0203B500
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xb
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02057654
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xff
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	bl FUN_02058B7C
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	add r4, r0, #0x0
	ldr r1, [r1, #0x24]
	bl FUN_021EF5E0
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r0, r4, #0x0
	ldr r1, [r1, #0x20]
	bl FUN_0201EC68
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203B544
FUN_0203B544: ; 0x0203B544
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	bl FUN_02059E74
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B568
	mov r0, #0x0
	pop {r3-r5, pc}
_0203B568:
	add r1, r4, #0x0
	bl FUN_021F1EC0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203B574
FUN_0203B574: ; 0x0203B574
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_02055320
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203B5B8
FUN_0203B5B8: ; 0x0203B5B8
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B2C
	strh r0, [r6, #0x0]
	add r0, r5, #0x0
	bl FUN_02058B4C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203B618
FUN_0203B618: ; 0x0203B618
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203B640
FUN_0203B640: ; 0x0203B640
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	cmp r7, #0x0
	beq _0203B696
	lsl r0, r7, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0203B6A4
_0203B696:
	lsl r0, r7, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0203B6A4:
	bl _ffix
	str r0, [sp, #0x0]
	cmp r6, #0x0
	beq _0203B6C0
	lsl r0, r6, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0203B6CE
_0203B6C0:
	lsl r0, r6, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0203B6CE:
	bl _ffix
	str r0, [sp, #0x4]
	cmp r4, #0x0
	beq _0203B6EA
	lsl r0, r4, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0203B6F8
_0203B6EA:
	lsl r0, r4, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0203B6F8:
	bl _ffix
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553A0
	add r1, sp, #0x0
	bl FUN_02058BB4
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r0, sp, #0x0
	ldr r1, [r1, #0x20]
	bl FUN_0201EF70
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0203B724
FUN_0203B724: ; 0x0203B724
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	bl FUN_02058994
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203B758
FUN_0203B758: ; 0x0203B758
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058E90
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203B790
FUN_0203B790: ; 0x0203B790
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	cmp r0, #0x0
	beq _0203B7D2
	bl FUN_02058480
	strh r0, [r4, #0x0]
_0203B7D2:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203B7D8
FUN_0203B7D8: ; 0x0203B7D8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x30
	ldr r0, [r0, #0x34]
	bl FUN_020580B4
	mov r1, #0xfe
	bl FUN_02058EB0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203B7F0
FUN_0203B7F0: ; 0x0203B7F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029C80
	bl FUN_02029E0C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203B81C
FUN_0203B81C: ; 0x0203B81C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029C80
	add r1, r6, #0x0
	bl FUN_02029E2C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203B85C
FUN_0203B85C: ; 0x0203B85C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029C80
	lsl r2, r4, #0x10
	add r1, r6, #0x0
	asr r2, r2, #0x10
	bl FUN_02029D44
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203B8A0
FUN_0203B8A0: ; 0x0203B8A0
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	bl FUN_020690CC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203B8E4
FUN_0203B8E4: ; 0x0203B8E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r1, r5, #0x0
	add r1, #0x80
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	bl FUN_020379F8
	str r0, [r4, #0x0]
	ldr r1, _0203B910 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203B910: .word FUN_0203BC04 

	thumb_func_start FUN_0203B914
FUN_0203B914: ; 0x0203B914
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r1, r5, #0x0
	add r1, #0x80
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	bl FUN_02037A1C
	str r0, [r4, #0x0]
	ldr r1, _0203B940 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203B940: .word FUN_0203BC04 

	thumb_func_start FUN_0203B944
FUN_0203B944: ; 0x0203B944
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x20
	ldr r0, [r0, #0x10]
	bl FUN_02037B44
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203B968
FUN_0203B968: ; 0x0203B968
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203B994
	bl ErrorHandling
_0203B994:
	ldr r0, [r4, #0x0]
	bl FUN_02037A40
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x7
	bne _0203B9A6
	mov r0, #0xff
	strh r0, [r5, #0x0]
_0203B9A6:
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203B9B4
FUN_0203B9B4: ; 0x0203B9B4
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r1, r5, #0x0
	str r6, [sp, #0x4]
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r2, [sp, #0x8]
	mov r0, #0x20
	add r3, r7, #0x0
	bl FUN_02037BB0
	str r0, [r4, #0x0]
	ldr r1, _0203BA38 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0203BA38: .word FUN_0203BC04 

	thumb_func_start FUN_0203BA3C
FUN_0203BA3C: ; 0x0203BA3C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203BA7C
	bl ErrorHandling
_0203BA7C:
	ldr r0, [r4, #0x0]
	bl FUN_02037A40
	strh r0, [r6, #0x0]
	ldrh r0, [r6, #0x0]
	cmp r0, #0x7
	bne _0203BA8E
	mov r0, #0xff
	strh r0, [r6, #0x0]
_0203BA8E:
	ldr r0, [r4, #0x0]
	bl FUN_02037A70
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	bne _0203BAA0
	mov r0, #0x1
	b _0203BAA2
_0203BAA0:
	mov r0, #0x0
_0203BAA2:
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r4-r6, pc}

	thumb_func_start FUN_0203BAB0
FUN_0203BAB0: ; 0x0203BAB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r5, #0x0
	add r1, #0x80
	add r2, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	bl FUN_02037C00
	str r0, [r4, #0x0]
	ldr r1, _0203BAF0 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203BAF0: .word FUN_0203BC04 

	thumb_func_start FUN_0203BAF4
FUN_0203BAF4: ; 0x0203BAF4
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203BB20
	bl ErrorHandling
_0203BB20:
	ldr r0, [r4, #0x0]
	bl FUN_02037A78
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0203BB34
FUN_0203BB34: ; 0x0203BB34
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	add r2, r7, #0x0
	bl FUN_021E1858
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203BB80
FUN_0203BB80: ; 0x0203BB80
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0203BB84
FUN_0203BB84: ; 0x0203BB84
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0203BB88
FUN_0203BB88: ; 0x0203BB88
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0203BB8C
FUN_0203BB8C: ; 0x0203BB8C
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0203BB90
FUN_0203BB90: ; 0x0203BB90
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x13
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0203BBAE
	mov r0, #0x0
	pop {r3-r5, pc}
_0203BBAE:
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203BBBC
FUN_0203BBBC: ; 0x0203BBBC
	push {r4-r6, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x13
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	ldr r6, [r4, #0x0]
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0203BBDC
	mov r0, #0x0
	pop {r4-r6, pc}
_0203BBDC:
	ldr r0, [r6, #0x8]
	cmp r0, #0x1
	bne _0203BBF4
	mov r0, #0xb
	bl FUN_02029048
	add r5, #0x98
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r2, #0x1
	bl FUN_02028AD4
_0203BBF4:
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203BC04
FUN_0203BC04: ; 0x0203BC04
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0204647C
	cmp r0, #0x0
	bne _0203BC16
	mov r0, #0x1
	pop {r3, pc}
_0203BC16:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203BC1C
FUN_0203BC1C: ; 0x0203BC1C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_0204AF84
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203BC2C
FUN_0203BC2C: ; 0x0203BC2C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_0204AF3C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203BC3C
FUN_0203BC3C: ; 0x0203BC3C
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02027E24
	cmp r5, #0x0
	bne _0203BC5A
	add r1, r4, #0x0
	bl FUN_02027098
	cmp r0, #0x0
	bne _0203BC68
	mov r0, #0x0
	pop {r3-r5, pc}
_0203BC5A:
	add r1, r4, #0x0
	bl FUN_020270B4
	cmp r0, #0x0
	bne _0203BC68
	mov r0, #0x0
	pop {r3-r5, pc}
_0203BC68:
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203BC6C
FUN_0203BC6C: ; 0x0203BC6C
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0xc]
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02027E24
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0203BC3C
	cmp r0, #0x0
	bne _0203BC90
	mov r0, #0x0
	pop {r3-r7, pc}
_0203BC90:
	ldr r0, [sp, #0x0]
	mov r1, #0xc
	bl FUN_02016998
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	strb r1, [r0, #0x8]
	strb r1, [r0, #0x9]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	str r7, [r0, #0x0]
	str r4, [r0, #0x8]
	str r6, [r0, #0x4]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203BCBC
FUN_0203BCBC: ; 0x0203BCBC
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_021F02C4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203BCCC
FUN_0203BCCC: ; 0x0203BCCC
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_0206F3B8
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203BCD8
FUN_0203BCD8: ; 0x0203BCD8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	ldr r1, [r4, #0x0]
	ldr r1, [r1, #0x4]
	strh r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203BD08
FUN_0203BD08: ; 0x0203BD08
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	bl FUN_02031190
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203BD28
FUN_0203BD28: ; 0x0203BD28
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r2, _0203BDB4 ; =0x000003D9
	ldr r0, [r0, #0x8]
	mov r1, #0x3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0xb
	str r0, [sp, #0x0]
	ldr r0, _0203BDB4 ; =0x000003D9
	mov r1, #0x3
	str r0, [sp, #0x4]
	lsl r0, r7, #0x18
	str r4, [sp, #0x8]
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	mov r0, #0x4
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r2, #0xa
	ldr r0, [r0, #0x8]
	mov r3, #0x5
	bl FUN_0200DC4C
	add r5, #0x80
	str r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_0203ED2C
	mov r0, #0x0
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_0203BDB4: .word 0x000003D9

	thumb_func_start FUN_0203BDB8
FUN_0203BDB8: ; 0x0203BDB8
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_0206B9B0
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r2, _0203BE4C ; =0x000003D9
	ldr r0, [r0, #0x8]
	mov r1, #0x3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0xb
	str r0, [sp, #0x0]
	ldr r0, _0203BE4C ; =0x000003D9
	mov r1, #0x3
	str r0, [sp, #0x4]
	str r4, [sp, #0x8]
	mov r0, #0x4
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r2, #0xa
	ldr r0, [r0, #0x8]
	mov r3, #0x5
	bl FUN_0200DCA4
	str r0, [r6, #0x0]
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r0, #0x0
	add r5, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r5, #0x0]
	lsr r1, r1, #0x10
	bl FUN_0203ED2C
	mov r0, #0x0
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_0203BE4C: .word 0x000003D9

	thumb_func_start FUN_0203BE50
FUN_0203BE50: ; 0x0203BE50
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	strb r1, [r0, #0x0]
	add r0, r1, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203BE68
FUN_0203BE68: ; 0x0203BE68
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	strb r1, [r0, #0x0]
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203BE80
FUN_0203BE80: ; 0x0203BE80
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203BE98 ; =FUN_0203BE9C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203BE98: .word FUN_0203BE9C 

	thumb_func_start FUN_0203BE9C
FUN_0203BE9C: ; 0x0203BE9C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	ldr r0, [r4, #0x0]
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	beq _0203BEC8
	mov r0, #0x1
	pop {r3-r5, pc}
_0203BEC8:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203BECC
FUN_0203BECC: ; 0x0203BECC
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl FUN_020394B8
	add r2, r0, #0x0
	ldr r0, [r5, #0x74]
	ldr r1, [r4, #0x0]
	bl FUN_021E1374
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203BF00
FUN_0203BF00: ; 0x0203BF00
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0203BF1C
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_021E1994
_0203BF1C:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0203BF20
FUN_0203BF20: ; 0x0203BF20
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_0208A338
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203BF2C
FUN_0203BF2C: ; 0x0203BF2C
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	ldr r2, [r5, #0x0]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r2, #0x10]
	ldr r2, [r2, #0xc]
	add r3, r4, #0x0
	bl FUN_020380CC
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_0203BF84
FUN_0203BF84: ; 0x0203BF84
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r1, r5, #0x0
	add r1, #0x80
	add r6, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0xb
	mov r2, #0x0
	add r3, r7, #0x0
	bl FUN_0203BC6C
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203BFCC
	mov r0, #0x1
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_0203BFCC:
	mov r0, #0x0
	strh r0, [r6, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02038130
	ldr r1, _0203BFE8 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203BFE8: .word FUN_0203BB90 

	thumb_func_start FUN_0203BFEC
FUN_0203BFEC: ; 0x0203BFEC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r1, r5, #0x0
	add r1, #0x80
	add r6, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0xb
	mov r2, #0x1
	add r3, r7, #0x0
	bl FUN_0203BC6C
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203C034
	mov r0, #0x1
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_0203C034:
	mov r0, #0x0
	strh r0, [r6, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02038130
	ldr r1, _0203C050 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203C050: .word FUN_0203BB90 

	thumb_func_start FUN_0203C054
FUN_0203C054: ; 0x0203C054
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_0203BC3C
	cmp r0, #0x1
	bne _0203C088
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_0203C088:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_0203C090
FUN_0203C090: ; 0x0203C090
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_0203BC3C
	cmp r0, #0x1
	bne _0203C0C4
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_0203C0C4:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_0203C0CC
FUN_0203C0CC: ; 0x0203C0CC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	mov r1, #0x0
	bl FUN_02027008
	add r1, r4, #0x0
	bl FUN_02027478
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203C0FC
FUN_0203C0FC: ; 0x0203C0FC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02038804
	ldr r1, _0203C114 ; =FUN_0203BC04
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203C114: .word FUN_0203BC04 

	thumb_func_start FUN_0203C118
FUN_0203C118: ; 0x0203C118
	push {r3, lr}
	add r1, r0, #0x0
	ldr r0, [r1, #0x74]
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0xc]
	bl FUN_02085F48
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203C12C
FUN_0203C12C: ; 0x0203C12C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	mov r1, #0x5
	add r4, r0, #0x0
	mov r0, #0xb
	lsl r1, r1, #0x6
	bl FUN_02016998
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	mov r2, #0x2
	bl FUN_0205F7A0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02037E90
	ldr r1, _0203C170 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203C170: .word FUN_0203BB90 

	thumb_func_start FUN_0203C174
FUN_0203C174: ; 0x0203C174
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r2, #0xb
	bl FUN_02088960
	str r0, [r4, #0x0]
	ldr r1, _0203C1A8 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203C1A8: .word FUN_0203BB90 

	thumb_func_start FUN_0203C1AC
FUN_0203C1AC: ; 0x0203C1AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206F158
	mov r1, #0x4
	bl FUN_0206EE64
	cmp r0, #0x0
	bne _0203C1E0
	mov r0, #0x1
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
_0203C1E0:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02028048
	bl FUN_020281B8
	cmp r0, #0x64
	blo _0203C1FA
	mov r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
_0203C1FA:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0203C200
FUN_0203C200: ; 0x0203C200
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r6, r0, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x8
	str r0, [r6, #0x0]
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [sp, #0x0]
	strh r7, [r4, #0x4]
	strh r0, [r4, #0x6]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_02037FE4
	ldr r1, _0203C274 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203C274: .word FUN_0203BB90 

	thumb_func_start FUN_0203C278
FUN_0203C278: ; 0x0203C278
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0xc
	bl FUN_02016998
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0xc]
	str r1, [r0, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	str r1, [r0, #0x4]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02037D60
	ldr r1, _0203C2C0 ; =FUN_0203BBBC
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203C2C0: .word FUN_0203BBBC 

	thumb_func_start FUN_0203C2C4
FUN_0203C2C4: ; 0x0203C2C4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020383F8
	ldr r1, _0203C2DC ; =FUN_0203BC04
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203C2DC: .word FUN_0203BC04 

	thumb_func_start FUN_0203C2E0
FUN_0203C2E0: ; 0x0203C2E0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02065344
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203C2F0
FUN_0203C2F0: ; 0x0203C2F0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_020383D8
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203C300
FUN_0203C300: ; 0x0203C300
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0203842C
	str r0, [r4, #0x0]
	ldr r1, _0203C328 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203C328: .word FUN_0203BB90 

	thumb_func_start FUN_0203C32C
FUN_0203C32C: ; 0x0203C32C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02048694
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203C33C
FUN_0203C33C: ; 0x0203C33C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02038824
	str r0, [r4, #0x0]
	ldr r1, _0203C364 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203C364: .word FUN_0203BB90 

	thumb_func_start FUN_0203C368
FUN_0203C368: ; 0x0203C368
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0203384C
	cmp r0, #0x0
	beq _0203C3BC
	mov r0, #0x1
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl FUN_020386E0
	ldr r1, _0203C3C4 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	b _0203C3C0
_0203C3BC:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0203C3C0:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203C3C4: .word FUN_0203BC04 

	thumb_func_start FUN_0203C3C8
FUN_0203C3C8: ; 0x0203C3C8
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl FUN_0206F3D8
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0203C3E8
FUN_0203C3E8: ; 0x0203C3E8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl FUN_02016998
	str r0, [r4, #0x0]
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r6, #0x4]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_020386A4
	ldr r1, _0203C42C ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	nop
_0203C42C: .word FUN_0203BC04 

	thumb_func_start FUN_0203C430
FUN_0203C430: ; 0x0203C430
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	ldr r1, [r4, #0x0]
	ldr r1, [r1, #0x0]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0205F378
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203C460
FUN_0203C460: ; 0x0203C460
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x8]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0203C474
	mov r0, #0x1
	b _0203C476
_0203C474:
	mov r0, #0x0
_0203C476:
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _0203C492
	bl ErrorHandling
_0203C492:
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_0203789C
	str r0, [r6, #0x0]
	ldr r1, _0203C4AC ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203C4AC: .word FUN_0203BC04 

	thumb_func_start FUN_0203C4B0
FUN_0203C4B0: ; 0x0203C4B0
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203C4DC
	bl ErrorHandling
_0203C4DC:
	ldr r0, [r4, #0x0]
	bl FUN_020378FC
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0203C4F0
FUN_0203C4F0: ; 0x0203C4F0
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x74]
	add r2, r1, #0x0
	mov r3, #0x7
	bl FUN_020385CC
	mov r0, #0x1
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0203C520
FUN_0203C520: ; 0x0203C520
	push {r4-r7, lr}
	sub sp, #0x34
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x74
	add r2, sp, #0xc
	add r7, r0, #0x0
	bl FUN_020671BC
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	str r6, [sp, #0x0]
	add r0, sp, #0xc
	str r0, [sp, #0x4]
	str r4, [sp, #0x8]
	ldr r0, [r5, #0x74]
	mov r1, #0x1
	mov r3, #0xa
	bl FUN_020385CC
	mov r0, #0x1
	add sp, #0x34
	pop {r4-r7, pc}

	thumb_func_start FUN_0203C58C
FUN_0203C58C: ; 0x0203C58C
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	mov r2, #0x0
	str r2, [sp, #0x0]
	str r2, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x74]
	mov r1, #0x6
	mov r3, #0xa
	bl FUN_020385CC
	mov r0, #0x1
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0203C5BC
FUN_0203C5BC: ; 0x0203C5BC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r2, r0, #0x0
	ldr r0, _0203C610 ; =0x0000FFFF
	add r5, #0x80
	strh r0, [r2, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x10]
	mov r3, #0x0
	bl FUN_02037E18
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203C610: .word 0x0000FFFF

	thumb_func_start FUN_0203C614
FUN_0203C614: ; 0x0203C614
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r3, r0, #0x0
	ldr r0, _0203C67C ; =0x0000FFFF
	add r5, #0x80
	strh r0, [r4, #0x0]
	strh r0, [r3, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x10]
	add r2, r4, #0x0
	bl FUN_02037E18
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203C67C: .word 0x0000FFFF

	thumb_func_start FUN_0203C680
FUN_0203C680: ; 0x0203C680
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	bl FUN_0200B518
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203C6C4
FUN_0203C6C4: ; 0x0203C6C4
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r4, [sp, #0x0]
	add r3, r0, #0x0
	str r6, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r1, r7, #0x0
	add r2, r7, #0x0
	bl FUN_0200E1D0
	mov r0, #0x0
	bl FUN_0200E388
	mov r0, #0x1
	bl FUN_0200E388
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0203C70C
FUN_0203C70C: ; 0x0203C70C
	push {r3, lr}
	ldr r1, _0203C718 ; =FUN_0203C71C
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203C718: .word FUN_0203C71C 

	thumb_func_start FUN_0203C71C
FUN_0203C71C: ; 0x0203C71C
	push {r3, lr}
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0203C72A
	mov r0, #0x1
	pop {r3, pc}
_0203C72A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203C730
FUN_0203C730: ; 0x0203C730
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r2, #0x0
	ldr r0, [r5, #0x74]
	add r1, r6, #0x0
	mvn r2, r2
	add r3, r7, #0x0
	bl FUN_02049240
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0203C788
FUN_0203C788: ; 0x0203C788
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r4, [sp, #0x0]
	mov r2, #0x0
	add r5, #0x80
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x10]
	mvn r2, r2
	add r3, r7, #0x0
	bl FUN_02049F98
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0203C7E4
FUN_0203C7E4: ; 0x0203C7E4
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02049FFC
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203C7F4
FUN_0203C7F4: ; 0x0203C7F4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034DC8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	ldr r1, [r5, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203C820
FUN_0203C820: ; 0x0203C820
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	ldr r1, [r4, #0x0]
	ldr r1, [r1, #0x1c]
	ldr r1, [r1, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203C844
FUN_0203C844: ; 0x0203C844
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x74]
	add r2, r4, #0x0
	bl FUN_021E6990
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203C874
FUN_0203C874: ; 0x0203C874
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205DD40
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x74]
	add r2, r4, #0x0
	bl FUN_021E6410
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203C8B4
FUN_0203C8B4: ; 0x0203C8B4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x74]
	add r2, r4, #0x0
	bl FUN_021E6BF4
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203C8E4
FUN_0203C8E4: ; 0x0203C8E4
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	mov r2, #0x1
	str r2, [sp, #0x4]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	sub r2, r2, #0x2
	add r3, r6, #0x0
	bl FUN_02049274
	mov r0, #0x1
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_0203C930
FUN_0203C930: ; 0x0203C930
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r5, r0, #0x0
	mov r1, #0x0
	bl FUN_02034DF4
	add r0, r5, #0x0
	bl FUN_02034DEC
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xc]
	bl FUN_021DC174
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203C960
FUN_0203C960: ; 0x0203C960
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r5, r0, #0x0
	mov r1, #0x0
	bl FUN_02034DF4
	add r0, r5, #0x0
	bl FUN_02034DEC
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xc]
	bl FUN_021DC174
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203C990
FUN_0203C990: ; 0x0203C990
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553E8
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_0224666C
	str r0, [r4, #0x0]
	ldr r1, _0203C9F4 ; =FUN_0203C9F8
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	nop
_0203C9F4: .word FUN_0203C9F8 

	thumb_func_start FUN_0203C9F8
FUN_0203C9F8: ; 0x0203C9F8
	push {r4, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_022466A0
	cmp r0, #0x1
	bne _0203CA1A
	ldr r0, [r4, #0x0]
	bl FUN_022466AC
	mov r0, #0x1
	pop {r4, pc}
_0203CA1A:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203CA20
FUN_0203CA20: ; 0x0203CA20
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_021E7030
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203CA2C
FUN_0203CA2C: ; 0x0203CA2C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553C4
	cmp r0, #0x1
	bne _0203CA54
	mov r0, #0x1
	b _0203CA56
_0203CA54:
	mov r0, #0x0
_0203CA56:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203CA5C
FUN_0203CA5C: ; 0x0203CA5C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x8]
	add r0, r1, #0x1
	str r0, [r4, #0x8]
	ldrb r0, [r1, #0x0]
	cmp r0, #0x1
	bne _0203CAA4
	add r0, r4, #0x0
	add r0, #0x80
	mov r1, #0x12
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x6
	bl FUN_0204AB20
	add r0, r4, #0x0
	add r0, #0x80
	mov r1, #0x12
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x6
	mov r2, #0x1
	bl FUN_0204ABDC
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	ldr r0, [r0, #0x38]
	bl FUN_021E5FD8
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_021E5FE0
	b _0203CAE4
_0203CAA4:
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	ldr r0, [r0, #0x38]
	bl FUN_021E5FD8
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_021E5FE0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_0204AB20
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x1c]
	ldr r1, [r1, #0x0]
	bl FUN_0204AB58
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r2, #0x1
	bl FUN_0204ABDC
_0203CAE4:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0203CAE8
FUN_0203CAE8: ; 0x0203CAE8
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	ldr r0, [r0, #0x38]
	bl FUN_021E5FD8
	add r4, #0x80
	mov r1, #0x12
	ldr r0, [r4, #0x0]
	lsl r1, r1, #0x6
	bl FUN_0204AB20
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0203CB08
FUN_0203CB08: ; 0x0203CB08
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055720
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203CB20
FUN_0203CB20: ; 0x0203CB20
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553C4
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203CB48
FUN_0203CB48: ; 0x0203CB48
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553D4
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0203CB60
FUN_0203CB60: ; 0x0203CB60
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_021E5FE0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203CB70
FUN_0203CB70: ; 0x0203CB70
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202A9B0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0202A990
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02245910
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203CBBC
FUN_0203CBBC: ; 0x0203CBBC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F388
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203CBE8
FUN_0203CBE8: ; 0x0203CBE8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x8
	add r0, r4, #0x0
	bl FUN_02039438
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x6
	bl FUN_02039438
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r2, [r6, #0x0]
	mov r3, #0xb
	bl FUN_0206AD4C
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02039438
	mov r1, #0xf
	bl FUN_02019620
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl LoadPlayerDataAddress
	add r2, r0, #0x0
	ldr r1, [r6, #0x0]
	add r0, r4, #0x0
	mov r3, #0x1
	bl FUN_02054658
	strb r0, [r7, #0x0]
	ldr r1, _0203CC84 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203CC84: .word FUN_0203A2F0 

	thumb_func_start FUN_0203CC88
FUN_0203CC88: ; 0x0203CC88
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_02240790
	ldr r1, _0203CCF4 ; =FUN_0203CCF8
	add r0, r5, #0x0
	str r6, [r5, #0x64]
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203CCF4: .word FUN_0203CCF8 

	thumb_func_start FUN_0203CCF8
FUN_0203CCF8: ; 0x0203CCF8
	push {r4, lr}
	add r1, r0, #0x0
	ldr r1, [r1, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	bl FUN_022407DC
	cmp r0, #0x0
	bne _0203CD18
	mov r0, #0x0
	pop {r4, pc}
_0203CD18:
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203CD20
FUN_0203CD20: ; 0x0203CD20
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_022407F8
	ldr r1, _0203CD8C ; =FUN_0203CD90
	add r0, r5, #0x0
	str r6, [r5, #0x64]
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203CD8C: .word FUN_0203CD90 

	thumb_func_start FUN_0203CD90
FUN_0203CD90: ; 0x0203CD90
	push {r4, lr}
	add r1, r0, #0x0
	ldr r1, [r1, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	bl FUN_02240844
	cmp r0, #0x0
	bne _0203CDB0
	mov r0, #0x0
	pop {r4, pc}
_0203CDB0:
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203CDB8
FUN_0203CDB8: ; 0x0203CDB8
	push {r3, lr}
	bl ScriptReadHalfword
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203CDC4
FUN_0203CDC4: ; 0x0203CDC4
	push {r3, lr}
	bl ScriptReadHalfword
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203CDD0
FUN_0203CDD0: ; 0x0203CDD0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r6, r0, #0x0
	add r5, #0x80
	ldr r4, [r6, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x10]
	add r1, #0x2c
	mov r2, #0x5
	bl FUN_02047174
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r6, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_0203CE00
FUN_0203CE00: ; 0x0203CE00
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02080C38
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203CE0C
FUN_0203CE0C: ; 0x0203CE0C
	push {r3-r4, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, #0x80
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r1, sp, #0x0
	bl FUN_02034DD4
	mov r0, #0x0
	add sp, #0x14
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0203CE8C
FUN_0203CE8C: ; 0x0203CE8C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034DD0
	ldr r0, [r0, #0x0]
	bl FUN_021E2608
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203CEBC
FUN_0203CEBC: ; 0x0203CEBC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	str r0, [sp, #0x4]
	bl FUN_02039438
	add r7, r0, #0x0
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r6, [r0, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r3, r0, #0x0
	ldr r0, [r7, #0x0]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	add r2, r4, #0x0
	bl FUN_021E2464
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0203CF04
FUN_0203CF04: ; 0x0203CF04
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020244A4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203CF34
FUN_0203CF34: ; 0x0203CF34
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202445C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203CF64
FUN_0203CF64: ; 0x0203CF64
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02024404
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203CF94
FUN_0203CF94: ; 0x0203CF94
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020243C8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203CFC4
FUN_0203CFC4: ; 0x0203CFC4
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0203CFC8
FUN_0203CFC8: ; 0x0203CFC8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	cmp r6, #0x0
	bne _0203D02E
	add r0, r7, #0x0
	bl FUN_02024550
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	mov r1, #0x2
	mov r2, #0xa
	bl FUN_0205F2E4
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_02054CC8
	b _0203D048
_0203D02E:
	add r0, r7, #0x0
	bl FUN_02024518
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_020239CC
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_02054D1C
_0203D048:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203D050
FUN_0203D050: ; 0x0203D050
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x74]
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	add r3, r4, #0x0
	bl FUN_02046E18
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_0203D0A4
FUN_0203D0A4: ; 0x0203D0A4
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x74]
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	add r3, r4, #0x0
	bl FUN_02046E18
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_0203D0F8
FUN_0203D0F8: ; 0x0203D0F8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x74]
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	bl FUN_02046FA0
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203D134
FUN_0203D134: ; 0x0203D134
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_020470AC
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203D140
FUN_0203D140: ; 0x0203D140
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_021F4DC8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203D150
FUN_0203D150: ; 0x0203D150
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_021F4D80
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203D178
FUN_0203D178: ; 0x0203D178
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl FUN_02046DB4
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203D194
FUN_0203D194: ; 0x0203D194
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_021F4E7C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203D1A4
FUN_0203D1A4: ; 0x0203D1A4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020386B4
	ldr r1, _0203D1BC ; =FUN_0203BC04
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203D1BC: .word FUN_0203BC04 

	thumb_func_start FUN_0203D1C0
FUN_0203D1C0: ; 0x0203D1C0
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r5, [r1, #0xc]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202280C
	cmp r0, #0x0
	beq _0203D1EC
	mov r0, #0x0
	strh r0, [r4, #0x0]
	b _0203D210
_0203D1EC:
	add r0, r5, #0x0
	bl FUN_02022804
	cmp r0, #0x0
	bne _0203D1FC
	mov r0, #0x1
	strh r0, [r4, #0x0]
	b _0203D210
_0203D1FC:
	add r0, r5, #0x0
	bl FUN_0202282C
	cmp r0, #0x0
	beq _0203D20C
	mov r0, #0x2
	strh r0, [r4, #0x0]
	b _0203D210
_0203D20C:
	mov r0, #0x3
	strh r0, [r4, #0x0]
_0203D210:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203D214
FUN_0203D214: ; 0x0203D214
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_021E85FC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203D23C
FUN_0203D23C: ; 0x0203D23C
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_021E3424
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203D248
FUN_0203D248: ; 0x0203D248
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0204C1A8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204BEC8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203D278
FUN_0203D278: ; 0x0203D278
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0204C1A8
	add r1, r5, #0x0
	bl FUN_0204BED8
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203D2A4
FUN_0203D2A4: ; 0x0203D2A4
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0204C1A8
	add r1, r6, #0x0
	bl FUN_0204BED0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203D2E4
FUN_0203D2E4: ; 0x0203D2E4
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [r4, #0x64]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02031588
	ldr r1, _0203D310 ; =FUN_0203D314
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D310: .word FUN_0203D314 

	thumb_func_start FUN_0203D314
FUN_0203D314: ; 0x0203D314
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02030F20
	cmp r0, #0x2
	bge _0203D324
	mov r0, #0x1
	pop {r4, pc}
_0203D324:
	ldr r0, [r4, #0x64]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020315D8
	pop {r4, pc}

	thumb_func_start FUN_0203D330
FUN_0203D330: ; 0x0203D330
	push {r3, lr}
	bl FUN_0203168C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203D33C
FUN_0203D33C: ; 0x0203D33C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0205296C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203D36C
FUN_0203D36C: ; 0x0203D36C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r1, r0, #0x0
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r1, [r1, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052C0C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203D3A4
FUN_0203D3A4: ; 0x0203D3A4
	push {r4, lr}
	bl ScriptReadHalfword
	add r4, r0, #0x0
	cmp r4, #0x5
	beq _0203D3BC
	cmp r4, #0x7
	beq _0203D3BC
	cmp r4, #0x9
	beq _0203D3BC
	cmp r4, #0x6
	bne _0203D3C2
_0203D3BC:
	bl FUN_02031C54
	b _0203D3CA
_0203D3C2:
	cmp r4, #0xb
	bne _0203D3CA
	bl FUN_02031C64
_0203D3CA:
	bl FUN_02031190
	cmp r0, #0x0
	bne _0203D3D8
	add r0, r4, #0x0
	bl FUN_02052B74
_0203D3D8:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0203D3DC
FUN_0203D3DC: ; 0x0203D3DC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r5, #0x80
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	bl FUN_020377AC
	bl FUN_02013B5C
	add r5, r0, #0x0
	cmp r4, #0x0
	bne _0203D432
	ldr r0, [r7, #0x0]
	bl FUN_02058448
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	b _0203D434
_0203D432:
	mov r2, #0x0
_0203D434:
	str r5, [sp, #0x0]
	ldr r0, [r6, #0x0]
	ldr r3, [sp, #0x4]
	add r1, r4, #0x0
	bl FUN_02052D08
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203D448
FUN_0203D448: ; 0x0203D448
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0208881C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203D458
FUN_0203D458: ; 0x0203D458
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x7c]
	bl FUN_02052F74
	bl FUN_02031B50
	ldr r1, _0203D478 ; =FUN_0203D47C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D478: .word FUN_0203D47C 

	thumb_func_start FUN_0203D47C
FUN_0203D47C: ; 0x0203D47C
	push {r3, lr}
	bl FUN_02030F20
	cmp r0, #0x2
	bge _0203D48A
	mov r0, #0x1
	pop {r3, pc}
_0203D48A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203D490
FUN_0203D490: ; 0x0203D490
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r7, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02058448
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r2, [sp, #0x0]
	ldr r0, [r0, #0x78]
	ldr r3, [r7, #0x0]
	bl FUN_02052A10
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203D4E8
FUN_0203D4E8: ; 0x0203D4E8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_020527A8
	strh r0, [r4, #0x0]
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0203D522
	add r5, #0x80
	ldr r0, [r5, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
_0203D522:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203D528
FUN_0203D528: ; 0x0203D528
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xa
	add r0, r5, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_02058448
	add r1, r0, #0x0
	ldr r0, [r5, #0x78]
	bl FUN_020524CC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203D560
FUN_0203D560: ; 0x0203D560
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xa
	add r0, r5, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_02058448
	add r1, r0, #0x0
	ldr r0, [r5, #0x78]
	add r2, r7, #0x0
	bl FUN_02052544
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203D5B0
FUN_0203D5B0: ; 0x0203D5B0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203D5C8 ; =FUN_0203D5CC
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D5C8: .word FUN_0203D5CC 

	thumb_func_start FUN_0203D5CC
FUN_0203D5CC: ; 0x0203D5CC
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	ldr r0, [r5, #0x78]
	bl FUN_02052604
	ldr r1, [r6, #0x64]
	add r4, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_020394B8
	cmp r4, #0x0
	bne _0203D5F0
	mov r0, #0x0
	pop {r4-r6, pc}
_0203D5F0:
	strh r4, [r0, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203D5F8
FUN_0203D5F8: ; 0x0203D5F8
	push {r3, lr}
	add r0, #0x80
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x34]
	ldr r1, [r1, #0x7c]
	bl FUN_020534DC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203D60C
FUN_0203D60C: ; 0x0203D60C
	push {r3, lr}
	mov r0, #0x4
	bl FUN_02052B74
	bl FUN_02031C2C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203D61C
FUN_0203D61C: ; 0x0203D61C
	push {r3, lr}
	bl FUN_02031C64
	bl FUN_02031B50
	mov r0, #0x0
	bl FUN_02052B74
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203D630
FUN_0203D630: ; 0x0203D630
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r4, #0x78]
	add r1, r6, #0x0
	bl FUN_0205265C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203D66C
FUN_0203D66C: ; 0x0203D66C
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203D684 ; =FUN_0203D688
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D684: .word FUN_0203D688 

	thumb_func_start FUN_0203D688
FUN_0203D688: ; 0x0203D688
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052608
	cmp r0, #0x1
	blo _0203D6BC
	add r5, #0x80
	strh r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052E10
	mov r0, #0x1
	pop {r3-r5, pc}
_0203D6BC:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203D6C4
FUN_0203D6C4: ; 0x0203D6C4
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203D6DC ; =FUN_0203D6E0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D6DC: .word FUN_0203D6E0 

	thumb_func_start FUN_0203D6E0
FUN_0203D6E0: ; 0x0203D6E0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052648
	ldr r1, _0203D724 ; =0x021C48B8
	ldr r2, [r1, #0x48]
	mov r1, #0x2
	tst r1, r2
	beq _0203D716
	add r5, #0x80
	ldr r0, [r5, #0x0]
	mov r1, #0x8
	ldr r0, [r0, #0x78]
	bl FUN_02052718
_0203D716:
	cmp r0, #0x0
	beq _0203D720
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0203D720:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0203D724: .word 0x021C48B8

	thumb_func_start FUN_0203D728
FUN_0203D728: ; 0x0203D728
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02049EA4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203D738
FUN_0203D738: ; 0x0203D738
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239BC
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239CC
	add r1, r0, #0x0
	ldr r2, [r4, #0x0]
	add r0, r6, #0x0
	bl FUN_0205363C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203D774
FUN_0203D774: ; 0x0203D774
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239BC
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239CC
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02053678
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_020239CC
	ldrh r1, [r4, #0x0]
	mov r2, #0x2
	bl FUN_020536D0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203D7DC
FUN_0203D7DC: ; 0x0203D7DC
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239BC
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239CC
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02053678
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203D834
FUN_0203D834: ; 0x0203D834
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	lsl r1, r1, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl FUN_02023A2C
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203D868
FUN_0203D868: ; 0x0203D868
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02048498
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203D874
FUN_0203D874: ; 0x0203D874
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r1, r4, #0x0
	bl FUN_02034E04
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203D8A0
FUN_0203D8A0: ; 0x0203D8A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020239CC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203D8D0
FUN_0203D8D0: ; 0x0203D8D0
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02046528
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	bl FUN_02085140
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203D8E8
FUN_0203D8E8: ; 0x0203D8E8
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0203D8EC
FUN_0203D8EC: ; 0x0203D8EC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02050024
	ldr r1, _0203D900 ; =FUN_0203D904
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203D900: .word FUN_0203D904 

	thumb_func_start FUN_0203D904
FUN_0203D904: ; 0x0203D904
	push {r3, lr}
	bl FUN_02031810
	cmp r0, #0x1
	beq _0203D91A
	bl FUN_0202EDF8
	cmp r0, #0x1
	beq _0203D91A
	mov r0, #0x1
	pop {r3, pc}
_0203D91A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203D920
FUN_0203D920: ; 0x0203D920
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02050048
	ldr r1, _0203D934 ; =FUN_0203D904
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203D934: .word FUN_0203D904 

	thumb_func_start FUN_0203D938
FUN_0203D938: ; 0x0203D938
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0204FF5C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203D948
FUN_0203D948: ; 0x0203D948
	push {r3, lr}
	bl ScriptReadHalfword
	bl FUN_0204F6DC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203D958
FUN_0203D958: ; 0x0203D958
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206F158
	add r1, r6, #0x0
	bl FUN_0206EE64
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203D998
FUN_0203D998: ; 0x0203D998
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r3, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02034B74
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203D9E8
FUN_0203D9E8: ; 0x0203D9E8
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	add r5, r0, #0x0
	add r1, r7, #0x0
	str r4, [sp, #0x0]
	bl FUN_02058E28
	add r0, r5, #0x0
	bl FUN_02059D1C
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0203DA78
FUN_0203DA78: ; 0x0203DA78
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02034BDC
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203DAB0
FUN_0203DAB0: ; 0x0203DAB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02034BAC
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203DAE8
FUN_0203DAE8: ; 0x0203DAE8
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r3, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02034C0C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203DB38
FUN_0203DB38: ; 0x0203DB38
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r3, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02034C34
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203DB88
FUN_0203DB88: ; 0x0203DB88
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	bne _0203DBC6
	bl ErrorHandling
_0203DBC6:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_021F1EC0
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203DBD4
FUN_0203DBD4: ; 0x0203DBD4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xc
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	ldr r1, [r5, #0x0]
	cmp r1, #0x0
	beq _0203DBFC
	strh r0, [r1, #0x0]
_0203DBFC:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203DC00
FUN_0203DC00: ; 0x0203DC00
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	lsl r1, r4, #0x5
	ldr r3, [r5, #0x8]
	add r2, r0, #0x0
	add r0, r3, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	lsl r4, r6, #0x5
	ldrb r3, [r3, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r7, r1
	add r2, r2, r4
	bl FUN_021DAE40
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203DC58
FUN_0203DC58: ; 0x0203DC58
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_021DAF78
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DC70
FUN_0203DC70: ; 0x0203DC70
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_021DAF98
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DC88
FUN_0203DC88: ; 0x0203DC88
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_021DAED4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DCA0
FUN_0203DCA0: ; 0x0203DCA0
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_021DAF28
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DCB8
FUN_0203DCB8: ; 0x0203DCB8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064CA8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DCC8
FUN_0203DCC8: ; 0x0203DCC8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02241230
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DCD8
FUN_0203DCD8: ; 0x0203DCD8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064CC8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DCE8
FUN_0203DCE8: ; 0x0203DCE8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02241914
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DCF8
FUN_0203DCF8: ; 0x0203DCF8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064D10
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DD08
FUN_0203DD08: ; 0x0203DD08
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064D4C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DD18
FUN_0203DD18: ; 0x0203DD18
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl FUN_02064D88
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DD34
FUN_0203DD34: ; 0x0203DD34
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl FUN_02242A38
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DD50
FUN_0203DD50: ; 0x0203DD50
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020388B4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DD60
FUN_0203DD60: ; 0x0203DD60
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r0, [r5, #0x64]
	ldr r0, [r6, #0x0]
	bl FUN_02058448
	add r1, r5, #0x0
	add r1, #0x80
	add r2, r0, #0x0
	ldr r1, [r1, #0x0]
	add r0, r7, #0x0
	bl FUN_0224CA54
	str r0, [r4, #0x0]
	ldr r1, _0203DDBC ; =FUN_0203DDC0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203DDBC: .word FUN_0203DDC0 

	thumb_func_start FUN_0203DDC0
FUN_0203DDC0: ; 0x0203DDC0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0224CA2C
	strh r0, [r5, #0x0]
	ldrh r1, [r5, #0x0]
	ldr r0, _0203DDFC ; =0x0000FFFE
	cmp r1, r0
	beq _0203DDF6
	mov r0, #0x1
	pop {r3-r5, pc}
_0203DDF6:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203DDFC: .word 0x0000FFFE

	thumb_func_start FUN_0203DE00
FUN_0203DE00: ; 0x0203DE00
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	bl FUN_0224CA58
	strb r0, [r4, #0x0]
	ldr r1, _0203DE34 ; =FUN_0203DE38
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203DE34: .word FUN_0203DE38 

	thumb_func_start FUN_0203DE38
FUN_0203DE38: ; 0x0203DE38
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	bl FUN_02039438
	ldrb r0, [r0, #0x0]
	bl FUN_020546C8
	pop {r3, pc}

	thumb_func_start FUN_0203DE4C
FUN_0203DE4C: ; 0x0203DE4C
	push {r3, lr}
	bl FUN_0224CA94
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DE58
FUN_0203DE58: ; 0x0203DE58
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r5, [r2, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0224CAA0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203DE80
FUN_0203DE80: ; 0x0203DE80
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r5, [r2, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0224CAB4
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203DEA8
FUN_0203DEA8: ; 0x0203DEA8
	push {r3, lr}
	sub sp, #0x8
	mov r3, #0x0
	str r3, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r1, #0x1
	ldr r0, [r0, #0x74]
	add r2, r1, #0x0
	bl FUN_02242BE0
	mov r0, #0x1
	add sp, #0x8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203DEC4
FUN_0203DEC4: ; 0x0203DEC4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	add r4, r0, #0x0
	bne _0203DEEC
	bl ErrorHandling
_0203DEEC:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0205889C
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203DEF8
FUN_0203DEF8: ; 0x0203DEF8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	add r4, r0, #0x0
	bne _0203DF20
	bl ErrorHandling
_0203DF20:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0205889C
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203DF2C
FUN_0203DF2C: ; 0x0203DF2C
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02066818
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203DF38
FUN_0203DF38: ; 0x0203DF38
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02025838
	mov r1, #0x0
	bl FUN_0202589C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203DF64
FUN_0203DF64: ; 0x0203DF64
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl FUN_02063650
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0203DF84
FUN_0203DF84: ; 0x0203DF84
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0204B2A4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203DFA8
FUN_0203DFA8: ; 0x0203DFA8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	bl FUN_0201B9EC
	add r1, r5, #0x0
	bl _s32_div_f
	strh r1, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203DFE0
FUN_0203DFE0: ; 0x0203DFE0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	bl FUN_0201B9EC
	add r1, r5, #0x0
	bl _s32_div_f
	strh r1, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203E018
FUN_0203E018: ; 0x0203E018
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_021F3A18
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203E054
FUN_0203E054: ; 0x0203E054
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_021F3AB4
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203E078
FUN_0203E078: ; 0x0203E078
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	add r3, r0, #0x0
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl FUN_021F3B7C
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0203E0CC
FUN_0203E0CC: ; 0x0203E0CC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	add r3, r0, #0x0
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl FUN_021F3B4C
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0203E120
FUN_0203E120: ; 0x0203E120
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	mov r1, #0x82
	lsl r1, r1, #0x8
	bl FUN_0205F3F8
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203E138
FUN_0203E138: ; 0x0203E138
	push {r4, lr}
	add r0, #0x80
	ldr r4, [r0, #0x0]
	ldr r0, [r4, #0xc]
	bl FUN_020462AC
	mov r1, #0x1
	bl FUN_0205F2D4
	ldr r0, [r4, #0xc]
	bl FUN_020289A4
	mov r1, #0x1
	bl FUN_020289B0
	add r1, r4, #0x0
	add r1, #0x98
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_02048C58
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203E168
FUN_0203E168: ; 0x0203E168
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r7, #0x0
	sub r0, #0x10
	cmp r0, #0xa
	bhi _0203E23A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0203E1EA: ; jump table (using 16-bit offset)
	.short _0203E200 - _0203E1EA - 2; case 0
	.short _0203E20C - _0203E1EA - 2; case 1
	.short _0203E218 - _0203E1EA - 2; case 2
	.short _0203E226 - _0203E1EA - 2; case 3
	.short _0203E23A - _0203E1EA - 2; case 4
	.short _0203E226 - _0203E1EA - 2; case 5
	.short _0203E226 - _0203E1EA - 2; case 6
	.short _0203E226 - _0203E1EA - 2; case 7
	.short _0203E226 - _0203E1EA - 2; case 8
	.short _0203E226 - _0203E1EA - 2; case 9
	.short _0203E226 - _0203E1EA - 2; case 10
_0203E200:
	mov r0, #0x4
	mov r6, #0x1
	bl FUN_02029120
	str r0, [r5, #0x0]
	b _0203E23E
_0203E20C:
	mov r0, #0x4
	mov r6, #0x1
	bl FUN_0202912C
	str r0, [r5, #0x0]
	b _0203E23E
_0203E218:
	ldr r0, [sp, #0x0]
	mov r1, #0x4
	mov r6, #0x1
	bl FUN_02029138
	str r0, [r5, #0x0]
	b _0203E23E
_0203E226:
	sub r7, #0x13
	lsl r0, r7, #0x18
	ldr r1, [sp, #0x0]
	lsr r0, r0, #0x18
	mov r2, #0x4
	mov r6, #0x1
	bl FUN_0202914C
	str r0, [r5, #0x0]
	b _0203E23E
_0203E23A:
	mov r0, #0x1
	pop {r3-r7, pc}
_0203E23E:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r1, [r5, #0x0]
	add r0, #0x98
	ldr r0, [r0, #0x0]
	add r2, r6, #0x0
	bl FUN_02028AD4
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203E254
FUN_0203E254: ; 0x0203E254
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0203E258
FUN_0203E258: ; 0x0203E258
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020271A4
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203E29C
FUN_0203E29C: ; 0x0203E29C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020270D8
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203E2F8
FUN_0203E2F8: ; 0x0203E2F8
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r7, #0x0
	bl FUN_02027114
	cmp r6, r0
	bhi _0203E352
	mov r0, #0x1
	b _0203E354
_0203E352:
	mov r0, #0x0
_0203E354:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203E35C
FUN_0203E35C: ; 0x0203E35C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	bl FUN_02027264
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203E38C
FUN_0203E38C: ; 0x0203E38C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r6, #0x0
	bl FUN_02027100
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203E3D0
FUN_0203E3D0: ; 0x0203E3D0
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02024504
	cmp r0, #0x1
	bne _0203E404
	mov r0, #0x1
	strh r0, [r4, #0x0]
_0203E404:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203E408
FUN_0203E408: ; 0x0203E408
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_020244EC
	cmp r0, #0x1
	bne _0203E43C
	mov r0, #0x1
	strh r0, [r4, #0x0]
_0203E43C:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203E440
FUN_0203E440: ; 0x0203E440
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x20
	mov r2, #0x0
	bl FUN_02038AF4
	str r0, [r4, #0x0]
	ldr r1, _0203E46C ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203E46C: .word FUN_0203BB90 

	thumb_func_start FUN_0203E470
FUN_0203E470: ; 0x0203E470
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x20
	mov r2, #0x1
	bl FUN_02038AF4
	str r0, [r4, #0x0]
	ldr r1, _0203E49C ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203E49C: .word FUN_0203BB90 

	thumb_func_start FUN_0203E4A0
FUN_0203E4A0: ; 0x0203E4A0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0224CBB0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203E4B0
FUN_0203E4B0: ; 0x0203E4B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0224CC24
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203E4D8
FUN_0203E4D8: ; 0x0203E4D8
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203E4F0
FUN_0203E4F0: ; 0x0203E4F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r4, #0x0
	bl FUN_0202A0E8
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203E510
FUN_0203E510: ; 0x0203E510
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r7, #0x0
	bl FUN_0202A150
	ldr r1, _0203E564 ; =0xFFFF0000
	and r1, r0
	lsr r1, r1, #0x10
	strh r1, [r4, #0x0]
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0203E564: .word 0xFFFF0000

	thumb_func_start FUN_0203E568
FUN_0203E568: ; 0x0203E568
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	ldr r1, [r5, #0x8]
	add r2, r1, #0x1
	str r2, [r5, #0x8]
	lsl r2, r4, #0x10
	add r4, r2, #0x0
	orr r4, r0
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0203E59C
	cmp r0, #0x1
	beq _0203E5B0
	cmp r0, #0x2
	beq _0203E5C4
	b _0203E5D6
_0203E59C:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0202A11C
	b _0203E5D6
_0203E5B0:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0202A07C
	b _0203E5D6
_0203E5C4:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0202A0A8
_0203E5D6:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203E5DC
FUN_0203E5DC: ; 0x0203E5DC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x4]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r4, [r1, #0x0]
	add r0, r7, #0x0
	bl FUN_02034E24
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02034E28
	add r7, r0, #0x0
	cmp r4, #0x0
	beq _0203E62C
	cmp r4, #0x1
	beq _0203E642
	b _0203E66E
_0203E62C:
	ldr r0, [sp, #0x0]
	bl FUN_0205F1F4
	ldr r0, [sp, #0x4]
	bl FUN_02060FD0
	mov r0, #0x1e
	strh r0, [r6, #0x0]
	mov r0, #0x0
	strh r0, [r7, #0x0]
	b _0203E66E
_0203E642:
	ldr r0, [sp, #0x0]
	bl FUN_0205F204
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02061574
	mov r0, #0x4
	bl FUN_0202912C
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r2, #0x1
	add r0, #0x98
	ldr r0, [r0, #0x0]
	bl FUN_02028AD4
	mov r0, #0x0
	strh r0, [r6, #0x0]
	strh r0, [r7, #0x0]
_0203E66E:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0203E674
FUN_0203E674: ; 0x0203E674
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0206015C
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203E684
FUN_0203E684: ; 0x0203E684
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_022456E8
	strh r0, [r6, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203E6B4
FUN_0203E6B4: ; 0x0203E6B4
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064E20
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203E6C4
FUN_0203E6C4: ; 0x0203E6C4
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	mov r1, #0x0
	add r6, r0, #0x0
	mov r0, #0x41
	add r2, r1, #0x0
	bl FUN_0200433C
	add r5, #0x80
	ldrh r1, [r4, #0x0]
	ldr r0, [r5, #0x0]
	add r2, r6, #0x0
	bl FUN_0224525C
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_0203E6FC
FUN_0203E6FC: ; 0x0203E6FC
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	bl FUN_02245340
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203E72C
FUN_0203E72C: ; 0x0203E72C
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055560
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203E744
FUN_0203E744: ; 0x0203E744
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F688
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203E774
FUN_0203E774: ; 0x0203E774
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	bl FUN_020244A4
	add r4, r0, #0x0
	bl FUN_0201B9EC
	add r1, r4, #0x0
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp, #0x0]
	mov r1, #0x19
	strh r1, [r0, #0x0]
	mov r4, #0x1
	mov r5, #0x0
_0203E7B6:
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_020245F0
	cmp r0, #0x1
	bne _0203E7DC
	add r0, r4, #0x0
	bl FUN_02069B40
	cmp r0, #0x0
	beq _0203E7DC
	cmp r5, r6
	bne _0203E7D6
	ldr r0, [sp, #0x0]
	strh r4, [r0, #0x0]
	b _0203E7E8
_0203E7D6:
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_0203E7DC:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, _0203E7EC ; =0x000001ED
	cmp r4, r0
	bls _0203E7B6
_0203E7E8:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0203E7EC: .word 0x000001ED

	thumb_func_start FUN_0203E7F0
FUN_0203E7F0: ; 0x0203E7F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r1, r4, #0x0
	bl FUN_0205F5A4
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203E81C
FUN_0203E81C: ; 0x0203E81C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F594
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203E848
FUN_0203E848: ; 0x0203E848
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202AA00
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203E858
FUN_0203E858: ; 0x0203E858
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02060490
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203E870
FUN_0203E870: ; 0x0203E870
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r4, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r1, [r1, #0x0]
	mov r0, #0xb
	bl FUN_0224884C
	str r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203E894
FUN_0203E894: ; 0x0203E894
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_022488EC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203E8C4
FUN_0203E8C4: ; 0x0203E8C4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_022488F4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203E8F4
FUN_0203E8F4: ; 0x0203E8F4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r5, #0x74]
	ldr r1, [r4, #0x0]
	mov r3, #0xb
	bl FUN_02060790
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203E928
FUN_0203E928: ; 0x0203E928
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_022488CC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203E940
FUN_0203E940: ; 0x0203E940
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	bl FUN_02024D4C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203E954
FUN_0203E954: ; 0x0203E954
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	bl FUN_02024CE0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203E968
FUN_0203E968: ; 0x0203E968
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	mov r0, #0x0
	strh r0, [r6, #0x0]
	cmp r4, #0x1
	bne _0203E9AE
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	bl FUN_02024C84
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	bl FUN_02023A90
	b _0203E9C8
_0203E9AE:
	cmp r4, #0x2
	bne _0203E9C4
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	bl FUN_02024CA4
	strh r0, [r6, #0x0]
	b _0203E9C8
_0203E9C4:
	bl ErrorHandling
_0203E9C8:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203E9CC
FUN_0203E9CC: ; 0x0203E9CC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_0206B9B0
	add r5, r0, #0x0
	mov r1, #0xd
	mov r2, #0x0
	bl FUN_020671BC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xe
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xf
	mov r2, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x10
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x11
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x12
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r4, r6
	add r2, r7, r1
	ldr r1, [sp, #0x4]
	add r2, r1, r2
	ldr r1, [sp, #0x8]
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0203EA68
FUN_0203EA68: ; 0x0203EA68
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_020126B4
	ldr r0, [sp, #0xc]
	strh r0, [r4, #0x0]
	mov r0, #0x0
	add sp, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203EA90
FUN_0203EA90: ; 0x0203EA90
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl FUN_022411F4
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0203EAB0
FUN_0203EAB0: ; 0x0203EAB0
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r7, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r5, #0x0
	bl FUN_021F61E8
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_021F61DC
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203EB20
FUN_0203EB20: ; 0x0203EB20
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r4, #0x80
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	bl FUN_0224C27C
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203EB48
FUN_0203EB48: ; 0x0203EB48
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	add r5, #0x80
	lsl r1, r4, #0x18
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x0]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl FUN_0224C520
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203EB88
FUN_0203EB88: ; 0x0203EB88
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	ldr r1, [r5, #0x8]
	add r2, r1, #0x1
	str r2, [r5, #0x8]
	ldrb r6, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r7, [sp, #0x0]
	add r5, #0x80
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	ldr r3, [sp, #0x8]
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_020607D4
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0203EBC8
FUN_0203EBC8: ; 0x0203EBC8
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r1, #0xa
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203EBE4
FUN_0203EBE4: ; 0x0203EBE4
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	add r0, r6, #0x0
	bl FUN_020377AC
	bl FUN_020238F4
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_02022510
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	add r1, r7, #0x0
	bl FUN_0224D14C
	add r5, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r5, r0
	beq _0203EC7E
	cmp r5, #0x7
	ble _0203EC88
_0203EC7E:
	mov r0, #0xff
	strh r0, [r4, #0x0]
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0203EC88:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0206B644
	cmp r0, #0x0
	beq _0203EC98
	mov r0, #0x0
	b _0203ECA2
_0203EC98:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0206B620
	add r0, r5, #0x1
_0203ECA2:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203ECAC
FUN_0203ECAC: ; 0x0203ECAC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02026CB4
	bl FUN_020269CC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203ECD8
FUN_0203ECD8: ; 0x0203ECD8
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl FUN_0224C678
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203ECF4
FUN_0203ECF4: ; 0x0203ECF4
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl FUN_0224C6E8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203ED10
FUN_0203ED10: ; 0x0203ED10
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl FUN_0224C6F4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203ED2C
FUN_0203ED2C: ; 0x0203ED2C
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024DA0
	add r6, r0, #0x0
	mov r0, #0x20
	bl FUN_020669C0
	add r4, r0, #0x0
	bl FUN_02066978
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x32
	mov r3, #0x20
	bl FUN_02066ACC
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0202498C
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203ED70
FUN_0203ED70: ; 0x0203ED70
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022510
	bl FUN_0206B3E4
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	mov r0, #0x87
	lsl r0, r0, #0x2
	sub r0, r0, r1
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203EDA4
FUN_0203EDA4: ; 0x0203EDA4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x16
	bl FUN_02039438
	add r4, r0, #0x0
	mov r0, #0x0
	add r5, #0x80
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	bl FUN_021E7184
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203EDC8
FUN_0203EDC8: ; 0x0203EDC8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x16
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_021E71E8
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203EDE0
FUN_0203EDE0: ; 0x0203EDE0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r4, #0x80
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	bl FUN_0224E554
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203EE08
FUN_0203EE08: ; 0x0203EE08
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0206486C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203EE18
FUN_0203EE18: ; 0x0203EE18
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020649D4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203EE28
FUN_0203EE28: ; 0x0203EE28
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020649B0
	cmp r0, #0x0
	beq _0203EE4E
	mov r0, #0x1
	b _0203EE50
_0203EE4E:
	mov r0, #0x0
_0203EE50:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203EE58
FUN_0203EE58: ; 0x0203EE58
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0224E764
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203EE68
FUN_0203EE68: ; 0x0203EE68
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0224E7C4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203EE78
FUN_0203EE78: ; 0x0203EE78
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r4, #0x0
	bl FUN_0202A170
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203EE98
FUN_0203EE98: ; 0x0203EE98
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206BAE4
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_0203EED8
FUN_0203EED8: ; 0x0203EED8
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, sp, #0x4
	strh r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	str r0, [sp, #0x0]
	bl FUN_0206B9AC
	add r4, #0x80
	add r6, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r7, r0, #0x0
	mov r5, #0x0
	cmp r6, #0x0
	ble _0203EF4E
_0203EF18:
	ldr r0, [sp, #0x0]
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020671BC
	ldr r1, _0203EF54 ; =0x00000182
	cmp r0, r1
	bne _0203EF48
	add r0, r4, #0x0
	mov r1, #0x70
	add r2, sp, #0x4
	bl FUN_02067830
	add r0, r4, #0x0
	bl FUN_02066ED8
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_02024AF0
_0203EF48:
	add r5, r5, #0x1
	cmp r5, r6
	blt _0203EF18
_0203EF4E:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0203EF54: .word 0x00000182

	thumb_func_start FUN_0203EF58
FUN_0203EF58: ; 0x0203EF58
	push {r3-r7, lr}
	sub sp, #0x30
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	str r0, [sp, #0xc]
	bl FUN_0206B9AC
	add r2, sp, #0x18
	mov r4, #0x0
	ldr r3, _0203F008 ; =0x020F34FC
	str r0, [sp, #0x8]
	add r7, r2, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [sp, #0x8]
	str r4, [sp, #0x4]
	cmp r0, #0x0
	ble _0203EFFC
	mov r5, #0x1
	str r7, [sp, #0x14]
_0203EFA2:
	ldr r0, [sp, #0xc]
	add r1, r4, #0x0
	bl FUN_0206B9B0
	add r6, r0, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x10]
	add r0, r6, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r3, r0, #0x0
	mov r0, #0x67
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0x2
	cmp r1, r0
	bne _0203EFF2
	mov r2, #0x0
	add r1, r2, #0x0
	str r3, [r7, #0x0]
	cmp r4, #0x0
	ble _0203EFE8
	ldr r6, [sp, #0x14]
_0203EFD8:
	ldr r0, [r6, #0x0]
	cmp r3, r0
	bne _0203EFE0
	add r2, r5, #0x0
_0203EFE0:
	add r1, r1, #0x1
	add r6, r6, #0x4
	cmp r1, r4
	blt _0203EFD8
_0203EFE8:
	cmp r2, #0x0
	bne _0203EFF2
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	str r0, [sp, #0x4]
_0203EFF2:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r7, r7, #0x4
	cmp r4, r0
	blt _0203EFA2
_0203EFFC:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x1
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_0203F008: .word 0x020F34FC

	thumb_func_start FUN_0203F00C
FUN_0203F00C: ; 0x0203F00C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F1C4
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203F020
FUN_0203F020: ; 0x0203F020
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F1D4
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203F034
FUN_0203F034: ; 0x0203F034
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_020389CC
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0203F058
FUN_0203F058: ; 0x0203F058
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0204B2D8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203F07C
FUN_0203F07C: ; 0x0203F07C
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r7, r0, #0x0
	bne _0203F0FA
	bl ErrorHandling
_0203F0FA:
	str r6, [sp, #0x0]
	str r4, [sp, #0x4]
	ldr r0, [r5, #0x74]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	add r1, r7, #0x0
	bl FUN_02054F50
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_0203F110
FUN_0203F110: ; 0x0203F110
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r5, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	bne _0203F164
	bl ErrorHandling
_0203F164:
	ldr r0, [r4, #0x74]
	add r1, r5, #0x0
	add r2, r7, #0x0
	add r3, r6, #0x0
	bl FUN_0205502C
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start FUN_0203F174
FUN_0203F174: ; 0x0203F174
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02054E30
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203F19C
FUN_0203F19C: ; 0x0203F19C
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	mov r6, #0x0
	add r7, r0, #0x0
	add r4, r6, #0x0
	add r5, sp, #0x4
_0203F1CA:
	add r1, r4, #0x0
	add r0, r7, #0x0
	add r1, #0x22
	mov r2, #0x1
	bl FUN_020270D8
	cmp r0, #0x1
	bne _0203F1E0
	mov r0, #0x1
	strh r0, [r5, #0x0]
	add r6, r6, #0x1
_0203F1E0:
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, #0x10
	blt _0203F1CA
	cmp r6, #0x0
	bne _0203F1F8
	ldr r0, [sp, #0x0]
	ldr r1, _0203F230 ; =0x0000FFFF
	add sp, #0x24
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4-r7, pc}
_0203F1F8:
	bl FUN_0201B9EC
	add r1, r6, #0x0
	bl _s32_div_f
	mov r4, #0x0
	add r2, sp, #0x4
_0203F206:
	ldrh r0, [r2, #0x0]
	cmp r0, #0x1
	bne _0203F212
	cmp r1, #0x0
	beq _0203F21A
	sub r1, r1, #0x1
_0203F212:
	add r4, r4, #0x1
	add r2, r2, #0x2
	cmp r4, #0x10
	blt _0203F206
_0203F21A:
	cmp r4, #0x10
	blt _0203F222
	bl ErrorHandling
_0203F222:
	ldr r0, [sp, #0x0]
	add r4, #0x22
	strh r4, [r0, #0x0]
	mov r0, #0x0
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0203F230: .word 0x0000FFFF

	thumb_func_start FUN_0203F234
FUN_0203F234: ; 0x0203F234
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	ldr r1, _0203F250 ; =0x021C4918
	ldrb r1, [r1, #0x6]
	strh r1, [r0, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203F250: .word 0x021C4918

	thumb_func_start FUN_0203F254
FUN_0203F254: ; 0x0203F254
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	mov r1, #0x0
	bl FUN_0205F698
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203F26C
FUN_0203F26C: ; 0x0203F26C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldrb r4, [r1, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	cmp r4, #0x0
	beq _0203F2A0
	add r1, r6, #0x0
	bl FUN_0205F4E4
	b _0203F2A6
_0203F2A0:
	add r1, r6, #0x0
	bl FUN_0205F50C
_0203F2A6:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203F2AC
FUN_0203F2AC: ; 0x0203F2AC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B6D0
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203F2E4
FUN_0203F2E4: ; 0x0203F2E4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205F6C8
	cmp r0, #0xa
	blo _0203F314
	mov r0, #0x1
	b _0203F316
_0203F314:
	mov r0, #0x0
_0203F316:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203F31C
FUN_0203F31C: ; 0x0203F31C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F648
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203F348
FUN_0203F348: ; 0x0203F348
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02027210
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203F38C
FUN_0203F38C: ; 0x0203F38C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02046030
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203F39C
FUN_0203F39C: ; 0x0203F39C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0205F668
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0203F3AC
FUN_0203F3AC: ; 0x0203F3AC
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02013B5C
	bl FUN_02013B74
	cmp r0, #0x20
	bne _0203F3FE
	ldr r0, _0203F414 ; =0x0000FFFF
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
_0203F3FE:
	strh r0, [r4, #0x0]
	bl FUN_02013BE4
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r7, #0x0
	bl FUN_0200B518
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0203F414: .word 0x0000FFFF

	thumb_func_start FUN_0203F418
FUN_0203F418: ; 0x0203F418
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02013B5C
	bl FUN_02013BC8
	cmp r0, #0x1
	bne _0203F444
	mov r0, #0x1
	b _0203F446
_0203F444:
	mov r0, #0x0
_0203F446:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203F44C
FUN_0203F44C: ; 0x0203F44C
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205F710
	cmp r0, #0x5
	blo _0203F47C
	mov r0, #0x1
	b _0203F47E
_0203F47C:
	mov r0, #0x0
_0203F47E:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203F484
FUN_0203F484: ; 0x0203F484
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	ldr r5, [r5, #0x0]
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02023788
	add r7, r0, #0x0
	bl FUN_02023818
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204B2B4
	cmp r6, r0
	bne _0203F4CE
	add r0, r7, #0x0
	bl FUN_0202381C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204B2C0
	cmp r6, r0
	bne _0203F4CE
	mov r0, #0x1
	strh r0, [r4, #0x0]
	b _0203F4D2
_0203F4CE:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0203F4D2:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0203F4D8
FUN_0203F4D8: ; 0x0203F4D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202471C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203F508
FUN_0203F508: ; 0x0203F508
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r6, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x1c]
	ldr r1, [r2, #0x8]
	lsl r1, r1, #0x10
	lsr r5, r1, #0x10
	ldr r1, [r2, #0xc]
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	cmp r7, #0x3
	blo _0203F54C
	ldr r7, _0203F5C8 ; =0x0000010E
	b _0203F582
_0203F54C:
	cmp r0, #0x1e
	blo _0203F556
	mov r7, #0x43
	lsl r7, r7, #0x2
	b _0203F582
_0203F556:
	bl FUN_0201B9EC
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, #0x19
	bge _0203F568
	ldr r7, _0203F5CC ; =0x0000010D
	b _0203F582
_0203F568:
	bl FUN_0201B9EC
	mov r1, #0x6
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r1, r0, #0x10
	mov r0, #0x6
	mul r0, r7
	add r0, r1, r0
	lsl r1, r0, #0x1
	ldr r0, _0203F5D0 ; =0x020F3538
	ldrh r7, [r0, r1]
_0203F582:
	cmp r5, #0xb
	bne _0203F59A
	cmp r4, #0x1
	bne _0203F58E
	mov r4, #0x0
	b _0203F5A4
_0203F58E:
	cmp r4, #0x14
	bne _0203F596
	mov r4, #0x2
	b _0203F5A4
_0203F596:
	mov r4, #0x5
	b _0203F5A4
_0203F59A:
	cmp r5, #0x14
	bne _0203F5A2
	mov r4, #0x1
	b _0203F5A4
_0203F5A2:
	mov r4, #0x3
_0203F5A4:
	mov r5, #0x0
_0203F5A6:
	cmp r5, r4
	beq _0203F5B8
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl FUN_02034C24
_0203F5B8:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x4
	blo _0203F5A6
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0203F5C8: .word 0x0000010E
_0203F5CC: .word 0x0000010D
_0203F5D0: .word 0x020F3538

	thumb_func_start FUN_0203F5D4
FUN_0203F5D4: ; 0x0203F5D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F720
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203F604
FUN_0203F604: ; 0x0203F604
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F740
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203F634
FUN_0203F634: ; 0x0203F634
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F760
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203F664
FUN_0203F664: ; 0x0203F664
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x0
	add r3, sp, #0x0
	add r0, #0x8
_0203F684:
	ldr r6, [r0, #0x0]
	ldr r1, [r5, #0x8]
	add r6, r6, #0x1
	str r6, [r0, #0x0]
	ldrb r1, [r1, #0x0]
	add r2, r2, #0x1
	strb r1, [r3, #0x0]
	add r3, r3, #0x1
	cmp r2, #0x5
	blt _0203F684
	ldr r1, [r0, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	ldrb r6, [r2, #0x0]
	mov r0, #0x4
	bl FUN_02027E5C
	add r1, sp, #0x0
	add r2, r6, #0x0
	mov r3, #0x0
	add r7, r0, #0x0
	bl FUN_02027F04
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02028048
	add r1, r7, #0x0
	bl FUN_02028094
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02016A18
	ldr r0, _0203F6E0 ; =0x0000FFFF
	cmp r5, r0
	bne _0203F6D8
	strh r0, [r4, #0x0]
	b _0203F6DA
_0203F6D8:
	strh r6, [r4, #0x0]
_0203F6DA:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0203F6E0: .word 0x0000FFFF

	thumb_func_start FUN_0203F6E4
FUN_0203F6E4: ; 0x0203F6E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02028048
	bl FUN_02028074
	ldr r1, _0203F71C ; =0x0000FFFF
	cmp r0, r1
	bne _0203F712
	mov r0, #0x0
	b _0203F714
_0203F712:
	mov r0, #0x1
_0203F714:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203F71C: .word 0x0000FFFF

	thumb_func_start FUN_0203F720
FUN_0203F720: ; 0x0203F720
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r5, r0, #0x0
	cmp r4, #0x3
	bls _0203F752
	bl ErrorHandling
_0203F752:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205F4A0
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0203F760
FUN_0203F760: ; 0x0203F760
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x20
	ldr r0, [r0, #0xc]
	add r2, sp, #0x0
	bl FUN_02022534
	ldr r1, [sp, #0x0]
	add r4, r0, #0x0
	cmp r1, #0x0
	bne _0203F798
	mov r1, #0x0
	strh r1, [r5, #0x0]
	bl FUN_02016A18
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F798:
	cmp r1, #0x1
	bne _0203F7AE
	mov r1, #0x0
	bl FUN_0202B21C
	strh r0, [r5, #0x0]
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F7AE:
	cmp r1, #0x2
	bne _0203F7BE
	mov r1, #0x0
	strh r1, [r5, #0x0]
	bl FUN_02016A18
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F7BE:
	mov r0, #0x0
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203F7C8
FUN_0203F7C8: ; 0x0203F7C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r1, r5, #0x0
	add r1, #0x80
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	add r2, r6, #0x0
	bl FUN_02037A48
	str r0, [r4, #0x0]
	ldr r1, _0203F808 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203F808: .word FUN_0203BC04 

	thumb_func_start FUN_0203F80C
FUN_0203F80C: ; 0x0203F80C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203F84C
	bl ErrorHandling
_0203F84C:
	ldr r0, [r4, #0x0]
	bl FUN_02037A40
	strh r0, [r6, #0x0]
	ldrh r0, [r6, #0x0]
	cmp r0, #0x7
	bne _0203F85E
	mov r0, #0xff
	strh r0, [r6, #0x0]
_0203F85E:
	ldr r0, [r4, #0x0]
	bl FUN_02037A70
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	bne _0203F870
	mov r0, #0x1
	b _0203F872
_0203F870:
	mov r0, #0x0
_0203F872:
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r4-r6, pc}

	thumb_func_start FUN_0203F880
FUN_0203F880: ; 0x0203F880
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	cmp r4, #0x64
	bls _0203F8A2
	mov r4, #0x64
_0203F8A2:
	bl FUN_0201B9EC
	mov r1, #0x65
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	cmp r0, r4
	bgt _0203F8B8
	mov r0, #0x1
	b _0203F8BA
_0203F8B8:
	mov r0, #0x0
_0203F8BA:
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203F8C0
FUN_0203F8C0: ; 0x0203F8C0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r4, #0x0
	beq _0203F8FC
	cmp r4, #0x1
	beq _0203F906
	cmp r4, #0x2
	beq _0203F910
	b _0203F91A
_0203F8FC:
	mov r2, #0x0
	mov r3, #0x20
	bl FUN_0224F12C
	b _0203F91E
_0203F906:
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0224F12C
	b _0203F91E
_0203F910:
	mov r2, #0x2
	mov r3, #0x20
	bl FUN_0224F12C
	b _0203F91E
_0203F91A:
	bl ErrorHandling
_0203F91E:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203F924
FUN_0203F924: ; 0x0203F924
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F6A8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203F954
FUN_0203F954: ; 0x0203F954
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	cmp r0, #0x0
	bne _0203F978
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02239944
	b _0203F982
_0203F978:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02239AAC
_0203F982:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203F988
FUN_0203F988: ; 0x0203F988
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0203384C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203F9B0
FUN_0203F9B0: ; 0x0203F9B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020286EC
	bl FUN_02028448
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203F9DC
FUN_0203F9DC: ; 0x0203F9DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	ldr r1, _0203FA10 ; =0x0000FF79
	add r1, r4, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	cmp r1, #0x1
	bhi _0203FA0C
	bl FUN_02025C30
_0203FA0C:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0203FA10: .word 0x0000FF79

	thumb_func_start FUN_0203FA14
FUN_0203FA14: ; 0x0203FA14
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	mov r1, #0x0
	strh r1, [r0, #0x0]
	ldr r1, _0203FA54 ; =0x0000012A
	cmp r4, r1
	blo _0203FA4E
	add r1, #0xf
	cmp r4, r1
	bhi _0203FA4E
	mov r1, #0x1
	strh r1, [r0, #0x0]
_0203FA4E:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203FA54: .word 0x0000012A

	thumb_func_start FUN_0203FA58
FUN_0203FA58: ; 0x0203FA58
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	mov r0, #0x20
	bl FUN_0200AA80
	add r4, r0, #0x0
	ldr r2, _0203FB48 ; =0x00000147
	mov r0, #0x0
	mov r1, #0x1a
	mov r3, #0x20
	bl FUN_0200A86C
	add r5, r0, #0x0
	ldr r2, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200B518
	ldr r2, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0200B518
	ldr r2, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0200B518
	add r0, r4, #0x0
	mov r1, #0x3
	add r2, r7, #0x0
	bl FUN_0200B518
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0200A9C4
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200A914
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r7, #0x0
	bl FUN_02021CE0
	cmp r0, #0x0
	bne _0203FB24
	mov r0, #0x1
	b _0203FB26
_0203FB24:
	mov r0, #0x0
_0203FB26:
	strh r0, [r6, #0x0]
	add r0, r7, #0x0
	bl FUN_02021A20
	ldr r0, [sp, #0x0]
	bl FUN_02021A20
	add r0, r5, #0x0
	bl FUN_0200A8B8
	add r0, r4, #0x0
	bl FUN_0200AB18
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_0203FB48: .word 0x00000147

	thumb_func_start FUN_0203FB4C
FUN_0203FB4C: ; 0x0203FB4C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02023788
	mov r1, #0x1
	bl FUN_02023828
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203FB64
FUN_0203FB64: ; 0x0203FB64
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_0205296C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203FB94
FUN_0203FB94: ; 0x0203FB94
	push {r3, lr}
	bl FUN_02033E74
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203FBA0
FUN_0203FBA0: ; 0x0203FBA0
	push {r3, lr}
	bl FUN_02033ED0
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203FBAC
FUN_0203FBAC: ; 0x0203FBAC
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02034E48
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203FBBC
FUN_0203FBBC: ; 0x0203FBBC
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034DCC
	str r4, [r0, #0x0]
	str r6, [r0, #0x8]
	mov r1, #0x0
	str r7, [r0, #0xc]
	mvn r1, r1
	str r1, [r0, #0x4]
	mov r1, #0x1
	str r1, [r0, #0x10]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0203FC1C
FUN_0203FC1C: ; 0x0203FC1C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	ldr r2, [r5, #0x8]
	add r1, r0, #0x0
	add r0, r2, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldrb r4, [r2, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	bne _0203FC4C
	bl ErrorHandling
_0203FC4C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020588B8
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203FC58
FUN_0203FC58: ; 0x0203FC58
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02065078
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203FC80
FUN_0203FC80: ; 0x0203FC80
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x28
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0202280C
	cmp r0, #0x0
	bne _0203FCAA
	add r0, r5, #0x0
	mov r1, #0x4
	mov r2, #0x3
	bl FUN_021E8588
	str r0, [r4, #0x0]
	bl FUN_021E84F4
_0203FCAA:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203FCB0
FUN_0203FCB0: ; 0x0203FCB0
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x28
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0202280C
	cmp r0, #0x0
	bne _0203FCD6
	ldr r0, [r4, #0x0]
	bl FUN_021E856C
	ldr r0, [r4, #0x0]
	bl FUN_021E85E4
_0203FCD6:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203FCDC
FUN_0203FCDC: ; 0x0203FCDC
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_0206367C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203FCF4
FUN_0203FCF4: ; 0x0203FCF4
	push {r4-r7, lr}
	sub sp, #0x84
	add r7, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r7, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	mov r4, #0x0
	add r6, r4, #0x0
	add r5, r4, #0x0
_0203FD10:
	add r0, r7, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r1, r5, #0x0
	bl FUN_020239D0
	cmp r0, #0x1
	bne _0203FD2C
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_0203FD2C:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x8
	blo _0203FD10
	cmp r6, #0x8
	bhi _0203FD70
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0203FD46: ; jump table (using 16-bit offset)
	.short _0203FD58 - _0203FD46 - 2; case 0
	.short _0203FD5C - _0203FD46 - 2; case 1
	.short _0203FD5C - _0203FD46 - 2; case 2
	.short _0203FD60 - _0203FD46 - 2; case 3
	.short _0203FD60 - _0203FD46 - 2; case 4
	.short _0203FD64 - _0203FD46 - 2; case 5
	.short _0203FD64 - _0203FD46 - 2; case 6
	.short _0203FD68 - _0203FD46 - 2; case 7
	.short _0203FD6C - _0203FD46 - 2; case 8
_0203FD58:
	mov r1, #0x1
	b _0203FD72
_0203FD5C:
	mov r1, #0x2
	b _0203FD72
_0203FD60:
	mov r1, #0x3
	b _0203FD72
_0203FD64:
	mov r1, #0x4
	b _0203FD72
_0203FD68:
	mov r1, #0x5
	b _0203FD72
_0203FD6C:
	mov r1, #0x6
	b _0203FD72
_0203FD70:
	mov r1, #0x1
_0203FD72:
	ldr r0, _0203FDB4 ; =0x020F4218
	mov r2, #0x0
	add r6, sp, #0x4
_0203FD78:
	lsl r3, r2, #0x2
	add r5, r0, r3
	ldrh r3, [r5, #0x2]
	cmp r1, r3
	blt _0203FD8E
	ldrh r5, [r5, #0x0]
	lsl r3, r4, #0x1
	strh r5, [r6, r3]
	add r3, r4, #0x1
	lsl r3, r3, #0x18
	lsr r4, r3, #0x18
_0203FD8E:
	add r2, r2, #0x1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	cmp r2, #0x13
	blo _0203FD78
	ldr r1, _0203FDB8 ; =0x0000FFFF
	lsl r0, r4, #0x1
	add r2, sp, #0x4
	strh r1, [r2, r0]
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldr r0, [r7, #0x74]
	add r7, #0x80
	ldr r1, [r7, #0x0]
	bl FUN_0223D3D0
	mov r0, #0x1
	add sp, #0x84
	pop {r4-r7, pc}
	.balign 4
_0203FDB4: .word 0x020F4218
_0203FDB8: .word 0x0000FFFF

	thumb_func_start FUN_0203FDBC
FUN_0203FDBC: ; 0x0203FDBC
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, _0203FE00 ; =0x0000FFF8
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0x5
	bhi _0203FDE4
	mov r0, #0x1
	b _0203FDE6
_0203FDE4:
	mov r0, #0x0
_0203FDE6:
	lsl r3, r2, #0x2
	str r0, [sp, #0x0]
	ldr r2, _0203FE04 ; =0x02105E10
	ldr r0, [r4, #0x74]
	add r4, #0x80
	ldr r2, [r2, r3]
	ldr r1, [r4, #0x0]
	mov r3, #0x0
	bl FUN_0223D3D0
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203FE00: .word 0x0000FFF8
_0203FE04: .word 0x02105E10

	thumb_func_start FUN_0203FE08
FUN_0203FE08: ; 0x0203FE08
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	cmp r2, #0x1
	bhi _0203FE28
	mov r0, #0x1
	b _0203FE2A
_0203FE28:
	mov r0, #0x0
_0203FE2A:
	lsl r3, r2, #0x2
	str r0, [sp, #0x0]
	ldr r2, _0203FE44 ; =0x02105DEC
	ldr r0, [r4, #0x74]
	add r4, #0x80
	ldr r2, [r2, r3]
	ldr r1, [r4, #0x0]
	mov r3, #0x1
	bl FUN_0223D3D0
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203FE44: .word 0x02105DEC

	thumb_func_start FUN_0203FE48
FUN_0203FE48: ; 0x0203FE48
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	mov r0, #0x0
	lsl r3, r2, #0x2
	str r0, [sp, #0x0]
	ldr r2, _0203FE7C ; =0x02105DF4
	ldr r0, [r4, #0x74]
	add r4, #0x80
	ldr r2, [r2, r3]
	ldr r1, [r4, #0x0]
	mov r3, #0x2
	bl FUN_0223D3D0
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203FE7C: .word 0x02105DF4

	thumb_func_start FUN_0203FE80
FUN_0203FE80: ; 0x0203FE80
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02038AD0
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203FE90
FUN_0203FE90: ; 0x0203FE90
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	bl FUN_02082140
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0203FEC0
FUN_0203FEC0: ; 0x0203FEC0
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [r4, #0x64]
	ldr r1, _0203FEF0 ; =FUN_0203FEF4
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203FEF0: .word FUN_0203FEF4 

	thumb_func_start FUN_0203FEF4
FUN_0203FEF4: ; 0x0203FEF4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r1, [r4, #0x64]
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02082158
	pop {r4, pc}

	thumb_func_start FUN_0203FF10
FUN_0203FF10: ; 0x0203FF10
	push {r3-r7, lr}
	sub sp, #0x38
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_020239A0
	add r7, r0, #0x0
	ldr r1, [sp, #0x8]
	add r0, sp, #0x14
	strb r1, [r0, #0x0]
	ldr r1, [sp, #0x4]
	strb r1, [r0, #0x1]
	ldr r1, [sp, #0xc]
	strb r1, [r0, #0x2]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED0C
	add r1, sp, #0x14
	strb r0, [r1, #0x3]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	bl FUN_02024CA4
	add r1, sp, #0x14
	strb r0, [r1, #0x4]
	strb r6, [r1, #0x5]
	ldr r0, [sp, #0x10]
	str r7, [sp, #0x20]
	str r0, [sp, #0x1c]
	add r0, r5, #0x0
	str r4, [sp, #0x24]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl LoadPlayerDataAddress
	str r0, [sp, #0x2c]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r5, #0x80
	ldr r0, [r0, #0xc]
	str r0, [sp, #0x30]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029EF8
	str r0, [sp, #0x34]
	add r0, sp, #0x14
	bl FUN_02081214
	ldr r1, [sp, #0x0]
	str r0, [r1, #0x0]
	add r0, r7, #0x0
	bl FUN_02021A20
	mov r0, #0x0
	add sp, #0x38
	pop {r3-r7, pc}

	thumb_func_start FUN_02040028
FUN_02040028: ; 0x02040028
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034824
	add r5, #0x80
	ldr r3, [r5, #0x0]
	add r2, r0, #0x0
	ldr r1, [r3, #0xc]
	add r3, #0x98
	ldr r0, [r4, #0x0]
	ldr r3, [r3, #0x0]
	bl FUN_02082630
	ldr r0, [r4, #0x0]
	bl FUN_020814E8
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02040074
FUN_02040074: ; 0x02040074
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r3, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r2, [r6, #0x0]
	add r1, r7, #0x0
	bl FUN_0208201C
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020400C8
FUN_020400C8: ; 0x020400C8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r3, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r2, [r6, #0x0]
	add r1, r7, #0x0
	bl FUN_02082034
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204011C
FUN_0204011C: ; 0x0204011C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r3, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r2, [r6, #0x0]
	add r1, r7, #0x0
	bl FUN_0208206C
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02040170
FUN_02040170: ; 0x02040170
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r3, #0x1
	str r3, [sp, #0x4]
	ldr r0, [r4, #0x0]
	add r2, r6, #0x0
	bl FUN_0200AD38
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020401CC
FUN_020401CC: ; 0x020401CC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02081DC4
	ldr r1, _020401EC ; =FUN_020401F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_020401EC: .word FUN_020401F0 

	thumb_func_start FUN_020401F0
FUN_020401F0: ; 0x020401F0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02081EB8
	pop {r3, pc}

	thumb_func_start FUN_02040204
FUN_02040204: ; 0x02040204
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	ldr r1, [r1, #0x0]
	bl FUN_02080E0C
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_02040220
FUN_02040220: ; 0x02040220
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_02082090
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0204025C
FUN_0204025C: ; 0x0204025C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_020820B8
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02040298
FUN_02040298: ; 0x02040298
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_020820DC
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020402D4
FUN_020402D4: ; 0x020402D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0208213C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02040304
FUN_02040304: ; 0x02040304
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_0208210C
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02040340
FUN_02040340: ; 0x02040340
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0208217C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02040370
FUN_02040370: ; 0x02040370
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02082190
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020403A0
FUN_020403A0: ; 0x020403A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020821B4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020403D0
FUN_020403D0: ; 0x020403D0
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	bl FUN_020821C4
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02040414
FUN_02040414: ; 0x02040414
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	bl FUN_020821DC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02040458
FUN_02040458: ; 0x02040458
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020821F0
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02040488
FUN_02040488: ; 0x02040488
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r3, [sp, #0x4]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02082214
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020404FC
FUN_020404FC: ; 0x020404FC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02082254
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204052C
FUN_0204052C: ; 0x0204052C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r6, #0x0]
	mov r3, #0xb
	bl FUN_02082284
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204056C
FUN_0204056C: ; 0x0204056C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020822F0
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204059C
FUN_0204059C: ; 0x0204059C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_0208223C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020405B4
FUN_020405B4: ; 0x020405B4
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_0208224C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020405CC
FUN_020405CC: ; 0x020405CC
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02082444
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_020405F8
FUN_020405F8: ; 0x020405F8
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r1, _02040614 ; =FUN_02040618
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_02040614: .word FUN_02040618 

	thumb_func_start FUN_02040618
FUN_02040618: ; 0x02040618
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02082508
	cmp r0, #0x1
	bne _02040632
	mov r0, #0x1
	pop {r3, pc}
_02040632:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02040638
FUN_02040638: ; 0x02040638
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0x1c]
	bl FUN_021F4608
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0204064C
FUN_0204064C: ; 0x0204064C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0x1c]
	bl FUN_021F45E8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02040660
FUN_02040660: ; 0x02040660
	push {r4-r5, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x0]
	add r1, sp, #0x18
	add r2, sp, #0x14
	add r3, sp, #0x10
	bl FUN_020825A0
	ldr r0, [sp, #0x14]
	cmp r0, #0x1
	beq _020406B0
	ldr r0, [sp, #0x10]
	cmp r0, #0x1
	beq _020406B0
	ldr r0, [sp, #0xc]
	cmp r0, #0x1
	beq _020406B0
	ldr r0, [sp, #0x8]
	cmp r0, #0x1
	bne _020406B6
_020406B0:
	mov r0, #0x1
	strh r0, [r5, #0x0]
	b _020406BA
_020406B6:
	mov r0, #0x0
	strh r0, [r5, #0x0]
_020406BA:
	mov r0, #0x0
	add sp, #0x1c
	pop {r4-r5, pc}

	thumb_func_start FUN_020406C0
FUN_020406C0: ; 0x020406C0
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_0224D3E8
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_020406CC
FUN_020406CC: ; 0x020406CC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0xf
	add r0, r6, #0x0
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r4, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r5, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_020377AC
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r5, #0x0
	bl FUN_0200ABC0
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040700
FUN_02040700: ; 0x02040700
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0xf
	add r0, r4, #0x0
	bl FUN_02039438
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	ldr r2, [r4, #0xc]
	bl FUN_0200ABE4
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02040724
FUN_02040724: ; 0x02040724
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0xf
	add r0, r4, #0x0
	bl FUN_02039438
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	ldr r2, [r4, #0xc]
	bl FUN_0200AC0C
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02040748
FUN_02040748: ; 0x02040748
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0xf
	add r0, r6, #0x0
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r7, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	add r2, r0, #0x0
	ldr r0, [r7, #0x0]
	add r1, r4, #0x0
	bl FUN_0200AC60
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02040790
FUN_02040790: ; 0x02040790
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200AE38
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020407C8
FUN_020407C8: ; 0x020407C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200AEE0
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040800
FUN_02040800: ; 0x02040800
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	bl FUN_0206EA30
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200AD5C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204083C
FUN_0204083C: ; 0x0204083C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200AD5C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040874
FUN_02040874: ; 0x02040874
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	bl FUN_02054C14
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FUN_0200AD38
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_020408BC
FUN_020408BC: ; 0x020408BC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r7, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	ldr r1, [r5, #0x8]
	add r2, r1, #0x1
	str r2, [r5, #0x8]
	ldrb r4, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r3, [r2, #0x0]
	cmp r4, #0x0
	bne _02040904
	bl FUN_02054C14
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
_02040904:
	str r4, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r7, #0x0]
	ldr r2, [sp, #0x8]
	add r1, r6, #0x0
	bl FUN_0200AD38
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0204091C
FUN_0204091C: ; 0x0204091C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0xf
	add r0, r6, #0x0
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r7, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	add r2, r0, #0x0
	ldr r0, [r7, #0x0]
	add r1, r4, #0x0
	bl FUN_0200ACF8
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02040964
FUN_02040964: ; 0x02040964
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	ldr r0, [r4, #0xc]
	bl FUN_02022510
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	mov r1, #0x1e
	bl _s32_div_f
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x1e
	bl _s32_div_f
	add r2, r1, #0x0
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	bl FUN_0206B5E4
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200ACF8
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_020409C0
FUN_020409C0: ; 0x020409C0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B02C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020409F8
FUN_020409F8: ; 0x020409F8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B064
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040A30
FUN_02040A30: ; 0x02040A30
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_020377AC
	bl FUN_020238F4
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r7, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r7, #0x8]
	add r0, r4, #0x0
	ldrb r5, [r1, #0x0]
	bl FUN_020239CC
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02023A28
	add r1, r0, #0x0
	add r0, r7, #0x0
	mov r2, #0x2
	bl FUN_020536D0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r5, #0x0
	bl FUN_0200B09C
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02040A7C
FUN_02040A7C: ; 0x02040A7C
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r7, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x8]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r5, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x4
	bl FUN_02040AE4
	add r6, r0, #0x0
	str r5, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	ldr r0, [r7, #0x0]
	ldr r3, [sp, #0x8]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0200ABB4
	add r0, r6, #0x0
	bl FUN_02021A20
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02040AE4
FUN_02040AE4: ; 0x02040AE4
	push {r3-r5, lr}
	ldr r2, _02040B08 ; =0x0000016A
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	bl FUN_0200A86C
	add r5, r0, #0x0
	add r1, r4, #0x0
	bl FUN_0200A914
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200A8B8
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02040B08: .word 0x0000016A

	thumb_func_start FUN_02040B0C
FUN_02040B0C: ; 0x02040B0C
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r4, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r4, #0x8]
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldrb r5, [r1, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F388
	mov r1, #0x4
	bl FUN_02040AE4
	add r4, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	ldr r0, [r6, #0x0]
	add r1, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02040B5C
FUN_02040B5C: ; 0x02040B5C
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r4, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r4, #0x8]
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldrb r5, [r1, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F398
	mov r1, #0x4
	bl FUN_02040AE4
	add r4, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	ldr r0, [r6, #0x0]
	add r1, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02040BAC
FUN_02040BAC: ; 0x02040BAC
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r4, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r4, #0x8]
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldrb r5, [r1, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F3C0
	mov r1, #0x4
	bl FUN_02040AE4
	add r4, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	ldr r0, [r6, #0x0]
	add r1, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02040BFC
FUN_02040BFC: ; 0x02040BFC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B350
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040C34
FUN_02040C34: ; 0x02040C34
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B1D4
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040C6C
FUN_02040C6C: ; 0x02040C6C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B164
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040CA4
FUN_02040CA4: ; 0x02040CA4
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	mov r0, #0x16
	mov r1, #0x4
	bl FUN_020219F4
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r7, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	mov r1, #0x4
	add r2, r4, #0x0
	bl FUN_02064E60
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	ldr r0, [r7, #0x0]
	add r1, r6, #0x0
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02040D04
FUN_02040D04: ; 0x02040D04
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r4, #0x8]
	add r7, r0, #0x0
	add r0, r1, #0x1
	str r0, [r4, #0x8]
	add r0, r4, #0x0
	ldrb r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	sub r5, #0x95
	add r4, r0, #0x0
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x20
	bl FUN_020852E8
	add r5, r0, #0x0
	cmp r4, #0x2
	bhs _02040D5A
	mov r0, #0x1
	b _02040D5C
_02040D5A:
	mov r0, #0x0
_02040D5C:
	str r0, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	ldr r0, [r7, #0x0]
	add r1, r6, #0x0
	add r2, r5, #0x0
	mov r3, #0x0
	bl FUN_0200ABB4
	add r0, r5, #0x0
	bl FUN_02021A20
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02040D7C
FUN_02040D7C: ; 0x02040D7C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200AE04
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040DB4
FUN_02040DB4: ; 0x02040DB4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B660
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040DEC
FUN_02040DEC: ; 0x02040DEC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r7, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	mov r0, #0xb
	ldrb r6, [r1, #0x0]
	add r1, r0, #0x0
	bl FUN_020219F4
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024EB4
	bl FUN_02024F0C
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02021E28
	ldr r0, _02040E48 ; =0x020ECAC4
	mov r3, #0x0
	ldrb r0, [r0, #0x0]
	str r3, [sp, #0x0]
	add r1, r6, #0x0
	str r0, [sp, #0x4]
	ldr r0, [r7, #0x0]
	add r2, r4, #0x0
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02040E48: .word 0x020ECAC4

	thumb_func_start FUN_02040E4C
FUN_02040E4C: ; 0x02040E4C
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0xf
	add r0, r6, #0x0
	bl FUN_02039438
	ldr r1, [r4, #0x8]
	add r7, r0, #0x0
	add r0, r1, #0x1
	str r0, [r4, #0x8]
	add r0, r4, #0x0
	ldrb r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	ldr r1, [sp, #0x0]
	bl FUN_0206B9B0
	add r4, #0x36
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	ldr r0, [r7, #0x0]
	add r1, r5, #0x0
	bl FUN_0200AD5C
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02040EB4
FUN_02040EB4: ; 0x02040EB4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r1, #0x3
	bl FUN_0207FC5C
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200AD94
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040EF8
FUN_02040EF8: ; 0x02040EF8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	sub r2, r2, #0x1
	lsl r2, r2, #0x10
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	bl FUN_0200B534
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02040F34
FUN_02040F34: ; 0x02040F34
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200AE70
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040F6C
FUN_02040F6C: ; 0x02040F6C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200AEA8
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040FA4
FUN_02040FA4: ; 0x02040FA4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B388
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02040FDC
FUN_02040FDC: ; 0x02040FDC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B20C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02041014
FUN_02041014: ; 0x02041014
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B19C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204104C
FUN_0204104C: ; 0x0204104C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	ldr r0, [r5, #0x8]
	add r1, r4, #0x0
	add r0, r0, #0x1
	str r0, [r5, #0x8]
	ldr r0, [r6, #0x0]
	add r2, r7, #0x0
	bl FUN_0200ACC0
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02041094
FUN_02041094: ; 0x02041094
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldrb r4, [r1, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F3C0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200ACC0
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020410C8
FUN_020410C8: ; 0x020410C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B698
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02041100
FUN_02041100: ; 0x02041100
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B09C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02041138
FUN_02041138: ; 0x02041138
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	sub r2, r2, #0x1
	lsl r2, r2, #0x10
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	bl FUN_0200B568
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02041174
FUN_02041174: ; 0x02041174
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_0200B7A8
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02041194
FUN_02041194: ; 0x02041194
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F5D8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020411C4
FUN_020411C4: ; 0x020411C4
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r0, #0x0
	add r0, #0x80
	ldr r7, [r0, #0x0]
	ldr r0, [r7, #0xc]
	bl FUN_02022510
	str r0, [sp, #0x20]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, _0204133C ; =0x00000000
	str r0, [sp, #0x1c]
	str r0, [sp, #0x18]
	ldr r5, [sp, #0x1c]
	beq _02041286
_0204123C:
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _0204127C
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	lsl r1, r1, #0x10
	ldr r0, [sp, #0x0]
	lsr r1, r1, #0x10
	bl FUN_02041354
	cmp r0, #0x0
	beq _0204127C
	ldr r1, [sp, #0x1c]
	cmp r1, r0
	bge _0204127C
	str r0, [sp, #0x1c]
	str r5, [sp, #0x18]
_0204127C:
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, r6
	blo _0204123C
_02041286:
	mov r6, #0x0
	str r6, [sp, #0x14]
	str r6, [sp, #0x10]
	add r7, r6, #0x0
_0204128E:
	mov r5, #0x0
_02041290:
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x10]
	add r2, r5, #0x0
	bl FUN_0206B5E4
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020672BC
	cmp r0, #0x0
	beq _020412E0
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020672BC
	cmp r0, #0x0
	bne _020412E0
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	lsl r1, r1, #0x10
	ldr r0, [sp, #0x0]
	lsr r1, r1, #0x10
	bl FUN_02041354
	cmp r0, #0x0
	beq _020412E0
	cmp r6, r0
	bge _020412E0
	add r6, r0, #0x0
	add r0, r5, r7
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x14]
_020412E0:
	add r5, r5, #0x1
	cmp r5, #0x1e
	blo _02041290
	ldr r0, [sp, #0x10]
	add r7, #0x1e
	add r0, r0, #0x1
	str r0, [sp, #0x10]
	cmp r0, #0x12
	blo _0204128E
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _0204130C
	cmp r6, #0x0
	bne _0204130C
	ldr r0, [sp, #0xc]
	mov r1, #0x0
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	strh r1, [r0, #0x0]
	b _02041336
_0204130C:
	ldr r0, [sp, #0x1c]
	cmp r0, r6
	blo _02041326
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0xc]
	strh r1, [r0, #0x0]
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x8]
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	mov r1, #0x0
	strh r1, [r0, #0x0]
	b _02041336
_02041326:
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0xc]
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	mov r1, #0x1
	strh r6, [r0, #0x0]
	ldr r0, [sp, #0x4]
	strh r1, [r0, #0x0]
_02041336:
	mov r0, #0x0
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_0204133C: .word 0x00000000

	thumb_func_start FUN_02041340
FUN_02041340: ; 0x02041340
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F5FC
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02041354
FUN_02041354: ; 0x02041354
	push {r4-r7, lr}
	sub sp, #0xc
	mov r6, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r7, r6, #0x0
_02041360:
	add r0, r5, #0x0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x0]
	cmp r0, r1
	bne _020413AC
	add r0, r5, #0x0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, #0x0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	add r0, r7, #0x1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	cmp r7, #0x5
	blo _02041360
_020413AC:
	ldr r1, _020413BC ; =0x021C5A10
	ldr r0, [sp, #0x8]
	strh r0, [r1, #0x2]
	ldr r0, [sp, #0x4]
	strh r0, [r1, #0x0]
	add r0, r6, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_020413BC: .word 0x021C5A10

	thumb_func_start FUN_020413C0
FUN_020413C0: ; 0x020413C0
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02005410
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_020413E8
FUN_020413E8: ; 0x020413E8
	push {r3, lr}
	bl ScriptReadHalfword
	bl FUN_0200521C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020413F8
FUN_020413F8: ; 0x020413F8
	push {r3, lr}
	bl ScriptReadHalfword
	bl FUN_02004124
	mov r1, #0x0
	bl FUN_02005350
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0204140C
FUN_0204140C: ; 0x0204140C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x1c]
	ldr r1, [r1, #0x0]
	bl FUN_0204ABA8
	bl FUN_0200521C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02041424
FUN_02041424: ; 0x02041424
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0204AB20
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0204143C
FUN_0204143C: ; 0x0204143C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020053CC
	ldr r1, _02041460 ; =FUN_02041464
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_02041460: .word FUN_02041464 

	thumb_func_start FUN_02041464
FUN_02041464: ; 0x02041464
	push {r3, lr}
	bl FUN_02005404
	cmp r0, #0x0
	bne _02041472
	mov r0, #0x1
	pop {r3, pc}
_02041472:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02041478
FUN_02041478: ; 0x02041478
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	mov r0, #0x7f
	mov r2, #0x0
	bl FUN_0200538C
	ldr r1, _02041498 ; =FUN_02041464
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_02041498: .word FUN_02041464 

	thumb_func_start FUN_0204149C
FUN_0204149C: ; 0x0204149C
	push {r3, lr}
	ldr r1, [r0, #0x8]
	add r3, r1, #0x1
	str r3, [r0, #0x8]
	ldrb r2, [r1, #0x0]
	add r1, r3, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r3, #0x0]
	add r0, r2, #0x0
	bl FUN_020047C8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020414B8
FUN_020414B8: ; 0x020414B8
	push {r3, lr}
	bl ScriptReadHalfword
	add r1, r0, #0x0
	mov r0, #0x4
	bl FUN_02005308
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020414CC
FUN_020414CC: ; 0x020414CC
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r0, [r2, #0x0]
	bl FUN_020040F4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020414E0
FUN_020414E0: ; 0x020414E0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	bl FUN_020054C8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020414FC
FUN_020414FC: ; 0x020414FC
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	mov r1, #0x0
	bl FUN_020054F0
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02041518
FUN_02041518: ; 0x02041518
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [r4, #0x64]
	ldr r1, _0204153C ; =FUN_02041540
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0204153C: .word FUN_02041540 

	thumb_func_start FUN_02041540
FUN_02041540: ; 0x02041540
	push {r3, lr}
	ldr r0, [r0, #0x64]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02005508
	cmp r0, #0x0
	bne _02041554
	mov r0, #0x1
	pop {r3, pc}
_02041554:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02041558
FUN_02041558: ; 0x02041558
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r0, r5, #0x0
	bl FUN_02005578
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02041588
FUN_02041588: ; 0x02041588
	push {r3, lr}
	ldr r1, _02041594 ; =FUN_02041598
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_02041594: .word FUN_02041598 

	thumb_func_start FUN_02041598
FUN_02041598: ; 0x02041598
	push {r3, lr}
	bl FUN_02005670
	cmp r0, #0x0
	bne _020415A6
	mov r0, #0x1
	pop {r3, pc}
_020415A6:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020415AC
FUN_020415AC: ; 0x020415AC
	push {r3, lr}
	bl ScriptReadHalfword
	bl FUN_02005C28
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020415BC
FUN_020415BC: ; 0x020415BC
	push {r3, lr}
	ldr r1, _020415C8 ; =FUN_020415CC
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_020415C8: .word FUN_020415CC 

	thumb_func_start FUN_020415CC
FUN_020415CC: ; 0x020415CC
	push {r3, lr}
	bl FUN_02005CBC
	cmp r0, #0x0
	bne _020415DA
	mov r0, #0x1
	pop {r3, pc}
_020415DA:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020415E0
FUN_020415E0: ; 0x020415E0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029EF8
	bl FUN_02005D20
	cmp r0, #0x1
	bne _02041610
	mov r0, #0x1
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
_02041610:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02041618
FUN_02041618: ; 0x02041618
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	bl FUN_02005E28
	cmp r0, #0x0
	bne _0204163C
	mov r0, #0x1
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4, pc}
_0204163C:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02041644
FUN_02041644: ; 0x02041644
	push {r3, lr}
	bl FUN_02005E64
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02041650
FUN_02041650: ; 0x02041650
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029EF8
	bl FUN_02005E6C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_02041664
FUN_02041664: ; 0x02041664
	push {r3, lr}
	mov r1, #0x0
	mov r0, #0x3f
	add r2, r1, #0x0
	bl FUN_0200433C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_02041674
FUN_02041674: ; 0x02041674
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200488C
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020416A8
FUN_020416A8: ; 0x020416A8
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	bne _02041708
	add r0, r4, #0x0
	mov r1, #0x18
	bl FUN_02039438
	str r0, [sp, #0x14]
	add r0, r4, #0x0
	mov r1, #0x19
	bl FUN_02039438
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x1a
	bl FUN_02039438
	add r0, r4, #0x0
	mov r1, #0x1b
	bl FUN_02039438
	add r0, r4, #0x0
	mov r1, #0x1c
	bl FUN_02039438
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	mov r1, #0x1d
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x1e
	bl FUN_02039438
	b _02041748
_02041708:
	add r0, r4, #0x0
	mov r1, #0x1f
	bl FUN_02039438
	str r0, [sp, #0x14]
	add r0, r4, #0x0
	mov r1, #0x20
	bl FUN_02039438
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x21
	bl FUN_02039438
	add r0, r4, #0x0
	mov r1, #0x22
	bl FUN_02039438
	add r0, r4, #0x0
	mov r1, #0x23
	bl FUN_02039438
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	mov r1, #0x24
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x25
	bl FUN_02039438
_02041748:
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0xc]
	ldr r0, [r0, #0x0]
	ldr r3, [sp, #0x14]
	str r0, [sp, #0x4]
	str r5, [sp, #0x8]
	ldr r0, [r6, #0x0]
	ldr r1, [r4, #0x38]
	ldr r2, [r2, #0x0]
	ldr r3, [r3, #0x0]
	bl FUN_0205CA4C
	str r0, [r7, #0x0]
	mov r0, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02041770
FUN_02041770: ; 0x02041770
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x0]
	cmp r6, #0x0
	bne _020417AE
	add r5, #0x80
	ldr r0, [r5, #0x0]
	mov r1, #0x1e
	bl FUN_02039438
	b _020417B8
_020417AE:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	mov r1, #0x25
	bl FUN_02039438
_020417B8:
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	bne _020417C6
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_020417C6:
	bl FUN_0205CA64
	cmp r0, #0x1
	bne _020417DC
	ldr r0, [r5, #0x0]
	bl FUN_0205CA78
	mov r0, #0x0
	str r0, [r5, #0x0]
	mov r0, #0x1
	strh r0, [r4, #0x0]
_020417DC:
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_020417E0
FUN_020417E0: ; 0x020417E0
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1c
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	ldrh r1, [r5, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02041808
FUN_02041808: ; 0x02041808
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1b
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x22
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	cmp r7, #0x0
	bne _02041852
	ldrh r1, [r4, #0x0]
	b _02041854
_02041852:
	ldrh r1, [r6, #0x0]
_02041854:
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204185C
FUN_0204185C: ; 0x0204185C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x8
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_020395F4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204188C
FUN_0204188C: ; 0x0204188C
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x8
	add r0, r4, #0x0
	bl FUN_02039438
	add r0, r4, #0x0
	mov r1, #0x17
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r6, #0x0
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED3C
	cmp r0, #0x1
	bne _020418F2
	ldr r0, [r4, #0xc]
	bl FUN_020462AC
	bl FUN_0205F368
	add r6, r0, #0x0
_020418F2:
	mov r0, #0xb
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	ldr r0, [r5, #0x74]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x8]
	add r3, r6, #0x0
	bl FUN_020470E8
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204190C
FUN_0204190C: ; 0x0204190C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	mov r0, #0xb
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	ldr r0, [r5, #0x74]
	add r1, r7, #0x0
	add r3, r6, #0x0
	bl FUN_020470E8
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02041970
FUN_02041970: ; 0x02041970
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x8
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_020395F4
	bl FUN_0203962C
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bne _020419D2
	mov r0, #0x0
	mov r1, #0x2
	add r2, r0, #0x0
	b _020419EC
_020419D2:
	ldrh r0, [r4, #0x0]
	bl FUN_02039618
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bne _020419E6
	mov r0, #0x3
	mov r1, #0x5
	mov r2, #0x6
	b _020419EC
_020419E6:
	mov r0, #0x7
	mov r1, #0x9
	mov r2, #0xa
_020419EC:
	strh r0, [r7, #0x0]
	strh r1, [r6, #0x0]
	strh r2, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020419F8
FUN_020419F8: ; 0x020419F8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x8
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_020395F4
	bl FUN_0203962C
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bne _02041A5A
	mov r1, #0x0
	mov r0, #0x11
	add r2, r1, #0x0
	b _02041A74
_02041A5A:
	ldrh r0, [r4, #0x0]
	bl FUN_02039618
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bne _02041A6E
	mov r0, #0x12
	mov r1, #0x0
	mov r2, #0x6
	b _02041A74
_02041A6E:
	mov r0, #0x13
	mov r1, #0x0
	mov r2, #0xa
_02041A74:
	strh r0, [r7, #0x0]
	strh r1, [r6, #0x0]
	strh r2, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02041A80
FUN_02041A80: ; 0x02041A80
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x8
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_020395F4
	bl FUN_0203962C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02041AB4
FUN_02041AB4: ; 0x02041AB4
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	bl FUN_0204AD0C
	bl FUN_02004724
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02041AD4
FUN_02041AD4: ; 0x02041AD4
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02048498
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_02041AE0
FUN_02041AE0: ; 0x02041AE0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020480B8
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02041B10
FUN_02041B10: ; 0x02041B10
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020480C8
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02041B40
FUN_02041B40: ; 0x02041B40
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020480D8
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02041B70
FUN_02041B70: ; 0x02041B70
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	bl FUN_0204A248
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02041B9C
FUN_02041B9C: ; 0x02041B9C
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	mov r1, #0xb
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r2, #0x0
	ldr r0, [r4, #0x74]
	mov r1, #0x1
	add r3, r2, #0x0
	bl FUN_020470E8
	mov r0, #0x1
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_02041BC4
FUN_02041BC4: ; 0x02041BC4
	push {r3-r5, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02058738
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02058448
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r4, #0x0
	lsr r1, r1, #0x10
	bl FUN_0203965C
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02041BF0
FUN_02041BF0: ; 0x02041BF0
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl ScriptReadWord
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02058738
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02058448
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r7, #0x0
	lsr r1, r1, #0x10
	bl FUN_02039640
	cmp r0, #0x1
	bne _02041C34
	ldr r1, [r6, #0x8]
	add r0, r6, #0x0
	add r1, r1, r4
	bl ScriptJump
	mov r0, #0x1
	pop {r3-r7, pc}
_02041C34:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02041C38
FUN_02041C38: ; 0x02041C38
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202881C
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r7, [r0, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	cmp r0, #0x6
	bls _02041C6C
	b _02041E38
_02041C6C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02041C78: ; jump table (using 16-bit offset)
	.short _02041C86 - _02041C78 - 2; case 0
	.short _02041CBC - _02041C78 - 2; case 1
	.short _02041CF2 - _02041C78 - 2; case 2
	.short _02041D28 - _02041C78 - 2; case 3
	.short _02041D5E - _02041C78 - 2; case 4
	.short _02041D94 - _02041C78 - 2; case 5
	.short _02041DCE - _02041C78 - 2; case 6
_02041C86:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02028828
	strh r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02041CBC:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02028840
	strh r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02041CF2:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r3, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r7, #0x0
	add r2, r5, #0x0
	bl FUN_0200B708
	b _02041E38
_02041D28:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r7, #0x0
	add r2, r5, #0x0
	bl FUN_0200B708
	b _02041E38
_02041D5E:
	mov r1, #0x0
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_020287A8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	mov r2, #0x0
	str r2, [sp, #0x0]
	str r5, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x74]
	mov r1, #0x5
	mov r3, #0x7
	bl FUN_020385CC
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_02041D94:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02028828
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x1
	bl FUN_02028700
	cmp r6, #0x0
	beq _02041DC8
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_020612F8
_02041DC8:
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02041DCE:
	mov r0, #0x40
	mov r1, #0x20
	bl FUN_020219F4
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r1, r6, #0x0
	add r7, r0, #0x0
	bl FUN_02023990
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0x1
	add r3, r6, #0x0
	bl FUN_020287C0
	add r0, r7, #0x0
	bl FUN_020239CC
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020287EC
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0x2
	bl FUN_02028810
	bl FUN_0201BA60
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02028788
	add r0, r6, #0x0
	bl FUN_02021A20
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0x1
	bl FUN_02028700
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_020612EC
_02041E38:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02041E40
FUN_02041E40: ; 0x02041E40
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	cmp r0, #0x6
	bls _02041E4E
	b _02041FD2
_02041E4E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02041E5A: ; jump table (using 16-bit offset)
	.short _02041E68 - _02041E5A - 2; case 0
	.short _02041E88 - _02041E5A - 2; case 1
	.short _02041F24 - _02041E5A - 2; case 2
	.short _02041ECA - _02041E5A - 2; case 3
	.short _02041F2E - _02041E5A - 2; case 4
	.short _02041F68 - _02041E5A - 2; case 5
	.short _02041FB4 - _02041E5A - 2; case 6
_02041E68:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02248CD0
	strh r0, [r5, #0x0]
	b _02041FD2
_02041E88:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	ldr r0, _02041FD8 ; =0x00000233
	add r4, #0x80
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	add r1, r7, #0x0
	bl FUN_02249038
	strh r0, [r6, #0x0]
	b _02041FD2
_02041ECA:
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r1, [r5, #0x0]
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl FUN_022490A0
	b _02041FD2
_02041F24:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_02248CC0
	b _02041FD2
_02041F2E:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r4, #0x80
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FUN_022491FC
	strh r0, [r6, #0x0]
	b _02041FD2
_02041F68:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02248F70
	strh r0, [r5, #0x0]
	b _02041FD2
_02041FB4:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02248FE0
	strh r0, [r5, #0x0]
_02041FD2:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02041FD8: .word 0x00000233

	thumb_func_start FUN_02041FDC
FUN_02041FDC: ; 0x02041FDC
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02061374
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02042000
FUN_02042000: ; 0x02042000
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0206B9B0
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02061460
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02042038
FUN_02042038: ; 0x02042038
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	cmp r0, #0x0
	beq _02042058
	cmp r0, #0x1
	beq _020420A8
	b _02042106
_02042058:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r7, r0, #0x0
	ldr r0, _0204210C ; =0x00000232
	add r5, #0x80
	strh r0, [r6, #0x0]
	ldr r0, [sp, #0x0]
	ldr r1, [r5, #0x0]
	ldr r2, [r4, #0x0]
	bl FUN_020421F0
	strh r0, [r7, #0x0]
	b _02042106
_020420A8:
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r3, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020421D8
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_0202A170
_02042106:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0204210C: .word 0x00000232

	thumb_func_start FUN_02042110
FUN_02042110: ; 0x02042110
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	bl FUN_02042214
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204214C
FUN_0204214C: ; 0x0204214C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	cmp r0, #0x0
	beq _02042170
	cmp r0, #0x1
	beq _020421A2
	cmp r0, #0x2
	beq _020421BC
	b _020421D4
_02042170:
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0206B9B0
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x4
	bl FUN_02060F3C
	b _020421D4
_020421A2:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02060F9C
	b _020421D4
_020421BC:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02060F88
_020421D4:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020421D8
FUN_020421D8: ; 0x020421D8
	push {r3, lr}
	sub r1, r1, #0x1
	lsl r3, r1, #0x4
	ldr r1, _020421EC ; =0x020F4264
	ldr r3, [r1, r3]
	cmp r3, #0x0
	beq _020421EA
	add r1, r2, #0x0
	blx r3
_020421EA:
	pop {r3, pc}
	.balign 4
_020421EC: .word 0x020F4264

	thumb_func_start FUN_020421F0
FUN_020421F0: ; 0x020421F0
	push {r4, lr}
	sub r0, r0, #0x1
	lsl r4, r0, #0x4
	ldr r0, _0204220C ; =0x020F4268
	ldr r3, [r0, r4]
	cmp r3, #0x0
	beq _02042204
	add r0, r1, #0x0
	add r1, r2, #0x0
	blx r3
_02042204:
	ldr r0, _02042210 ; =0x020F4270
	ldr r0, [r0, r4]
	pop {r4, pc}
	nop
_0204220C: .word 0x020F4268
_02042210: .word 0x020F4270

	thumb_func_start FUN_02042214
FUN_02042214: ; 0x02042214
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	add r5, r1, #0x0
	bl FUN_02022504
	mov r1, #0x1
	add r2, r5, #0x0
	bl FUN_0202B710
	cmp r0, #0x0
	bne _02042230
	mov r0, #0x0
	pop {r3-r5, pc}
_02042230:
	sub r0, r5, #0x1
	lsl r1, r0, #0x4
	ldr r0, _02042248 ; =0x020F426C
	ldr r1, [r0, r1]
	cmp r1, #0x0
	bne _02042240
	mov r0, #0x1
	pop {r3-r5, pc}
_02042240:
	add r0, r4, #0x0
	blx r1
	pop {r3-r5, pc}
	nop
_02042248: .word 0x020F426C

	thumb_func_start FUN_0204224C
FUN_0204224C: ; 0x0204224C
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	mov r0, #0x40
	mov r1, #0x4
	str r3, [sp, #0x8]
	bl FUN_020219F4
	add r1, r7, #0x0
	add r4, r0, #0x0
	bl FUN_02021E28
	ldr r0, [sp, #0x24]
	ldr r3, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	add r1, r6, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl FUN_02021A20
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02042288
FUN_02042288: ; 0x02042288
	push {r4, lr}
	ldr r0, [r0, #0xc]
	add r4, r1, #0x0
	bl FUN_0206BB1C
	bl FUN_0204A20C
	bl FUN_020690E4
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200AC60
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020422A8
FUN_020422A8: ; 0x020422A8
	push {r4, lr}
	ldr r0, [r0, #0x4]
	add r4, r1, #0x0
	ldr r0, [r0, #0x14]
	bl FUN_02252538
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200B02C
	pop {r4, pc}

	thumb_func_start FUN_020422C0
FUN_020422C0: ; 0x020422C0
	push {r4, lr}
	sub sp, #0x20
	ldr r0, [r0, #0xc]
	add r4, r1, #0x0
	bl FUN_02022504
	bl FUN_0202B844
	ldrh r0, [r0, #0x2]
	mov r1, #0x4
	add r2, sp, #0x8
	bl FUN_0200A99C
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r0, #0x1
	mov r1, #0x0
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r2, sp, #0x8
	add r3, r1, #0x0
	bl FUN_0204224C
	add sp, #0x20
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020422F4
FUN_020422F4: ; 0x020422F4
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	bl FUN_0202B85C
	ldrb r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02042304
FUN_02042304: ; 0x02042304
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_0204C1A8
	bl FUN_0204BEC8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02042314
FUN_02042314: ; 0x02042314
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	bl FUN_0202B838
	ldrb r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02042324
FUN_02042324: ; 0x02042324
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	mov r1, #0x0
	bl FUN_02027098
	pop {r3, pc}

	thumb_func_start FUN_02042334
FUN_02042334: ; 0x02042334
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	bl FUN_0202B850
	ldrb r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02042344
FUN_02042344: ; 0x02042344
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	bl FUN_0202B844
	ldrb r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02042354
FUN_02042354: ; 0x02042354
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r0, #0xa8
	bl FUN_022434BC
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02042364
FUN_02042364: ; 0x02042364
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_022434D0
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r1, #0xa8
	str r0, [r1, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02042394
FUN_02042394: ; 0x02042394
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r0, #0xa8
	ldr r0, [r0, #0x0]
	bl FUN_02243694
	add r4, #0x80
	ldr r1, [r4, #0x0]
	mov r0, #0x0
	add r1, #0xa8
	str r0, [r1, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_020423B0
FUN_020423B0: ; 0x020423B0
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	bl ScriptReadHalfword
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r7, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl ScriptReadHalfword
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [sp, #0x4]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r0, #0x80
	ldr r1, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0xa8
	ldr r5, [r0, #0x0]
	ldr r0, [sp, #0x0]
	cmp r0, #0x64
	bls _020423FA
	b _020426F6
_020423FA:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02042406: ; jump table (using 16-bit offset)
	.short _020424D0 - _02042406 - 2; case 0
	.short _020424DA - _02042406 - 2; case 1
	.short _020424F6 - _02042406 - 2; case 2
	.short _020424FC - _02042406 - 2; case 3
	.short _02042508 - _02042406 - 2; case 4
	.short _02042516 - _02042406 - 2; case 5
	.short _0204251E - _02042406 - 2; case 6
	.short _020426F6 - _02042406 - 2; case 7
	.short _02042526 - _02042406 - 2; case 8
	.short _02042532 - _02042406 - 2; case 9
	.short _02042540 - _02042406 - 2; case 10
	.short _0204254E - _02042406 - 2; case 11
	.short _0204255A - _02042406 - 2; case 12
	.short _020426F6 - _02042406 - 2; case 13
	.short _02042564 - _02042406 - 2; case 14
	.short _0204256E - _02042406 - 2; case 15
	.short _02042578 - _02042406 - 2; case 16
	.short _020426F6 - _02042406 - 2; case 17
	.short _020426F6 - _02042406 - 2; case 18
	.short _020426F6 - _02042406 - 2; case 19
	.short _020426F6 - _02042406 - 2; case 20
	.short _020426F6 - _02042406 - 2; case 21
	.short _020426F6 - _02042406 - 2; case 22
	.short _020426F6 - _02042406 - 2; case 23
	.short _020426F6 - _02042406 - 2; case 24
	.short _020426F6 - _02042406 - 2; case 25
	.short _020426F6 - _02042406 - 2; case 26
	.short _020426F6 - _02042406 - 2; case 27
	.short _020426F6 - _02042406 - 2; case 28
	.short _020426F6 - _02042406 - 2; case 29
	.short _0204258A - _02042406 - 2; case 30
	.short _020425A2 - _02042406 - 2; case 31
	.short _020425BC - _02042406 - 2; case 32
	.short _020425C8 - _02042406 - 2; case 33
	.short _020425D2 - _02042406 - 2; case 34
	.short _020425DC - _02042406 - 2; case 35
	.short _020425E6 - _02042406 - 2; case 36
	.short _020425F0 - _02042406 - 2; case 37
	.short _020425F8 - _02042406 - 2; case 38
	.short _02042600 - _02042406 - 2; case 39
	.short _02042608 - _02042406 - 2; case 40
	.short _0204261A - _02042406 - 2; case 41
	.short _02042626 - _02042406 - 2; case 42
	.short _02042642 - _02042406 - 2; case 43
	.short _0204264C - _02042406 - 2; case 44
	.short _02042656 - _02042406 - 2; case 45
	.short _02042660 - _02042406 - 2; case 46
	.short _0204266A - _02042406 - 2; case 47
	.short _02042674 - _02042406 - 2; case 48
	.short _02042680 - _02042406 - 2; case 49
	.short _0204268C - _02042406 - 2; case 50
	.short _020426A0 - _02042406 - 2; case 51
	.short _020426AA - _02042406 - 2; case 52
	.short _020426B4 - _02042406 - 2; case 53
	.short _020426BE - _02042406 - 2; case 54
	.short _020426CC - _02042406 - 2; case 55
	.short _02042612 - _02042406 - 2; case 56
	.short _020426DA - _02042406 - 2; case 57
	.short _020426F6 - _02042406 - 2; case 58
	.short _020426F6 - _02042406 - 2; case 59
	.short _020426F6 - _02042406 - 2; case 60
	.short _020426F6 - _02042406 - 2; case 61
	.short _020426F6 - _02042406 - 2; case 62
	.short _020426F6 - _02042406 - 2; case 63
	.short _020426F6 - _02042406 - 2; case 64
	.short _020426F6 - _02042406 - 2; case 65
	.short _020426F6 - _02042406 - 2; case 66
	.short _020426F6 - _02042406 - 2; case 67
	.short _020426F6 - _02042406 - 2; case 68
	.short _020426F6 - _02042406 - 2; case 69
	.short _020426F6 - _02042406 - 2; case 70
	.short _020426F6 - _02042406 - 2; case 71
	.short _020426F6 - _02042406 - 2; case 72
	.short _020426F6 - _02042406 - 2; case 73
	.short _020426F6 - _02042406 - 2; case 74
	.short _020426F6 - _02042406 - 2; case 75
	.short _020426F6 - _02042406 - 2; case 76
	.short _020426F6 - _02042406 - 2; case 77
	.short _020426F6 - _02042406 - 2; case 78
	.short _020426F6 - _02042406 - 2; case 79
	.short _020426F6 - _02042406 - 2; case 80
	.short _020426F6 - _02042406 - 2; case 81
	.short _020426F6 - _02042406 - 2; case 82
	.short _020426F6 - _02042406 - 2; case 83
	.short _020426F6 - _02042406 - 2; case 84
	.short _020426F6 - _02042406 - 2; case 85
	.short _020426F6 - _02042406 - 2; case 86
	.short _020426F6 - _02042406 - 2; case 87
	.short _020426F6 - _02042406 - 2; case 88
	.short _020426F6 - _02042406 - 2; case 89
	.short _020426F6 - _02042406 - 2; case 90
	.short _020426F6 - _02042406 - 2; case 91
	.short _020426F6 - _02042406 - 2; case 92
	.short _020426F6 - _02042406 - 2; case 93
	.short _020426F6 - _02042406 - 2; case 94
	.short _020426F6 - _02042406 - 2; case 95
	.short _020426F6 - _02042406 - 2; case 96
	.short _020426F6 - _02042406 - 2; case 97
	.short _020426F6 - _02042406 - 2; case 98
	.short _020426F6 - _02042406 - 2; case 99
	.short _020426E6 - _02042406 - 2; case 100
_020424D0:
	add r0, r6, #0x0
	bl FUN_0224312C
	strh r0, [r4, #0x0]
	b _020426FA
_020424DA:
	cmp r6, #0x0
	bne _020424EA
	ldrb r0, [r5, #0xe]
	ldr r1, [r1, #0xc]
	bl FUN_022432E4
	strh r0, [r4, #0x0]
	b _020426FA
_020424EA:
	ldr r1, [r1, #0xc]
	add r0, r6, #0x0
	bl FUN_022432E4
	strh r0, [r4, #0x0]
	b _020426FA
_020424F6:
	bl FUN_0224339C
	b _020426FA
_020424FC:
	ldr r0, [r1, #0xc]
	bl FUN_0202A8CC
	bl FUN_022433A8
	b _020426FA
_02042508:
	ldr r0, [r1, #0xc]
	bl FUN_0202A8CC
	bl FUN_022433B0
	strh r0, [r4, #0x0]
	b _020426FA
_02042516:
	add r0, r1, #0x0
	bl FUN_022433B8
	b _020426FA
_0204251E:
	add r0, r1, #0x0
	bl FUN_022433F8
	b _020426FA
_02042526:
	ldr r0, [r1, #0xc]
	add r1, r6, #0x0
	bl FUN_02243408
	strh r0, [r4, #0x0]
	b _020426FA
_02042532:
	ldr r1, [r1, #0xc]
	mov r0, #0x0
	mov r2, #0x2
	bl FUN_02243E74
	strh r0, [r4, #0x0]
	b _020426FA
_02042540:
	mov r0, #0x0
	ldr r1, [r1, #0xc]
	add r2, r0, #0x0
	bl FUN_02243E74
	strh r0, [r4, #0x0]
	b _020426FA
_0204254E:
	ldr r0, [r1, #0xc]
	lsl r1, r6, #0x18
	lsr r1, r1, #0x18
	bl FUN_02243428
	b _020426FA
_0204255A:
	ldr r0, [r1, #0xc]
	bl FUN_02243448
	strh r0, [r4, #0x0]
	b _020426FA
_02042564:
	ldr r0, [r1, #0xc]
	bl FUN_0224345C
	strh r0, [r4, #0x0]
	b _020426FA
_0204256E:
	ldr r0, [r1, #0xc]
	bl FUN_022434AC
	strh r0, [r4, #0x0]
	b _020426FA
_02042578:
	ldrh r3, [r4, #0x0]
	ldr r0, [r7, #0x74]
	ldr r2, [sp, #0x4]
	add r1, r6, #0x0
	bl FUN_0205FD38
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0204258A:
	add r0, r1, #0x0
	mov r1, #0x13
	bl FUN_02039438
	add r2, r0, #0x0
	ldr r1, [r7, #0x74]
	add r0, r5, #0x0
	bl FUN_022436C8
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_020425A2:
	add r0, r1, #0x0
	mov r1, #0x13
	bl FUN_02039438
	add r7, #0x80
	ldr r2, [r7, #0x0]
	add r1, r0, #0x0
	ldr r2, [r2, #0xc]
	add r0, r5, #0x0
	bl FUN_022436E8
	strh r0, [r4, #0x0]
	b _020426FA
_020425BC:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl FUN_02243780
	strh r0, [r4, #0x0]
	b _020426FA
_020425C8:
	add r0, r5, #0x0
	bl FUN_022438DC
	strh r0, [r4, #0x0]
	b _020426FA
_020425D2:
	add r0, r5, #0x0
	bl FUN_022438E0
	strh r0, [r4, #0x0]
	b _020426FA
_020425DC:
	add r0, r5, #0x0
	bl FUN_022438FC
	strh r0, [r4, #0x0]
	b _020426FA
_020425E6:
	add r0, r5, #0x0
	bl FUN_02243920
	strh r0, [r4, #0x0]
	b _020426FA
_020425F0:
	add r0, r5, #0x0
	bl FUN_022439F8
	b _020426FA
_020425F8:
	add r0, r5, #0x0
	bl FUN_02243AD8
	b _020426FA
_02042600:
	add r0, r5, #0x0
	bl FUN_02243BA8
	b _020426FA
_02042608:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl FUN_02243C5C
	b _020426FA
_02042612:
	add r0, r5, #0x0
	bl FUN_02243D3C
	b _020426FA
_0204261A:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02243DA0
	strh r0, [r4, #0x0]
	b _020426FA
_02042626:
	add r0, r1, #0x0
	mov r1, #0x17
	bl FUN_02039438
	add r7, #0x80
	add r2, r0, #0x0
	ldr r0, [r7, #0x0]
	add r1, r5, #0x0
	ldr r0, [r0, #0x10]
	bl FUN_02243DB8
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02042642:
	add r0, r5, #0x0
	bl FUN_02243DC0
	strh r0, [r4, #0x0]
	b _020426FA
_0204264C:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02243DC4
	b _020426FA
_02042656:
	add r0, r5, #0x0
	bl FUN_02243DD8
	strh r0, [r4, #0x0]
	b _020426FA
_02042660:
	add r0, r5, #0x0
	bl FUN_02243DE0
	strh r0, [r4, #0x0]
	b _020426FA
_0204266A:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl FUN_02243E34
	b _020426FA
_02042674:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl FUN_02243F18
	strh r0, [r4, #0x0]
	b _020426FA
_02042680:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl FUN_02243F50
	strh r0, [r4, #0x0]
	b _020426FA
_0204268C:
	ldrb r1, [r5, #0x10]
	mov r0, #0xe0
	bic r1, r0
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r5, #0x10]
	b _020426FA
_020426A0:
	ldrb r0, [r5, #0x10]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1d
	strh r0, [r4, #0x0]
	b _020426FA
_020426AA:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl FUN_02243838
	b _020426FA
_020426B4:
	add r0, r5, r6
	add r0, #0x2a
	ldrb r0, [r0, #0x0]
	strh r0, [r4, #0x0]
	b _020426FA
_020426BE:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02243E74
	strh r0, [r4, #0x0]
	b _020426FA
_020426CC:
	lsl r1, r6, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_0204290C
	strh r0, [r4, #0x0]
	b _020426FA
_020426DA:
	ldr r1, [r1, #0xc]
	add r0, r5, #0x0
	bl FUN_02243F9C
	strh r0, [r4, #0x0]
	b _020426FA
_020426E6:
	cmp r5, #0x0
	bne _020426F0
	mov r0, #0x1
	strh r0, [r4, #0x0]
	b _020426FA
_020426F0:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	b _020426FA
_020426F6:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_020426FA:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02042700
FUN_02042700: ; 0x02042700
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	add r1, #0xa8
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	lsl r2, r6, #0x4
	add r2, r6, r2
	mov r1, #0x38
	lsl r2, r2, #0x4
	mul r1, r7
	add r2, r4, r2
	add r3, r2, r1
	mov r2, #0xb2
	lsl r2, r2, #0x2
	ldrh r1, [r3, r2]
	lsl r1, r1, #0x15
	lsr r4, r1, #0x15
	ldr r1, [sp, #0x0]
	strh r4, [r1, #0x0]
	add r1, r2, #0x4
	ldrh r1, [r3, r1]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02042780
FUN_02042780: ; 0x02042780
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0205FE10
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020427A8
FUN_020427A8: ; 0x020427A8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0205FF5C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020427D0
FUN_020427D0: ; 0x020427D0
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	add r0, #0xa8
	ldr r6, [r0, #0x0]
	ldr r0, _0204285C ; =0x00000884
	mov r2, #0x46
	add r0, r6, r0
	bl MI_CpuFill8
	cmp r4, #0x0
	beq _0204281E
	cmp r4, #0x1
	beq _02042830
	cmp r4, #0x2
	beq _0204283E
	b _0204284C
_0204281E:
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r0, r1, #0x0
	add r0, #0xa8
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0xc]
	bl FUN_022446FC
	b _0204284C
_02042830:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	add r0, #0xa8
	ldr r0, [r0, #0x0]
	bl FUN_02244758
	b _0204284C
_0204283E:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	add r0, #0xa8
	ldr r0, [r0, #0x0]
	bl FUN_02244770
_0204284C:
	bl FUN_02031190
	ldr r1, _02042860 ; =0x0000083E
	add r1, r6, r1
	bl FUN_020316AC
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0204285C: .word 0x00000884
_02042860: .word 0x0000083E

	thumb_func_start FUN_02042864
FUN_02042864: ; 0x02042864
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x10]
	bl FUN_0205FDDC
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02042894
FUN_02042894: ; 0x02042894
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202A8E4
	add r1, sp, #0x0
	bl FUN_0202A864
	add r0, sp, #0x0
	ldrb r1, [r0, #0x0]
	strh r1, [r4, #0x0]
	ldrb r0, [r0, #0x1]
	strh r0, [r6, #0x0]
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start FUN_020428E0
FUN_020428E0: ; 0x020428E0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202A8E4
	bl FUN_0202A74C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204290C
FUN_0204290C: ; 0x0204290C
	cmp r1, #0x2
	bne _02042918
	ldrb r0, [r0, #0x10]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1d
	bx lr
_02042918:
	cmp r1, #0x1
	bne _0204293E
	ldrb r1, [r0, #0xf]
	cmp r1, #0x2
	bne _02042930
	ldrb r0, [r0, #0x10]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1d
	lsl r1, r0, #0x1
	ldr r0, _0204294C ; =0x020F4334
	ldrh r0, [r0, r1]
	bx lr
_02042930:
	ldrb r0, [r0, #0x12]
	cmp r0, #0x0
	beq _0204293A
	mov r0, #0x61
	bx lr
_0204293A:
	mov r0, #0x0
	bx lr
_0204293E:
	ldrb r0, [r0, #0x11]
	cmp r0, #0x0
	beq _02042948
	mov r0, #0x61
	bx lr
_02042948:
	mov r0, #0x0
	bx lr
	.balign 4
_0204294C: .word 0x020F4334

	thumb_func_start FUN_02042950
FUN_02042950: ; 0x02042950
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r1, [r5, #0x8]
	ldr r0, [r0, #0x0]
	add r2, r1, #0x1
	str r2, [r5, #0x8]
	ldrb r6, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	mov r1, #0x26
	bl FUN_02039438
	add r5, #0x80
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_021E2A70
	str r0, [r7, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02042980
FUN_02042980: ; 0x02042980
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x26
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_021E29B4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02042998
FUN_02042998: ; 0x02042998
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x26
	bl FUN_02039438
	add r1, r0, #0x0
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	bl FUN_021E2AD4
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020429B8
FUN_020429B8: ; 0x020429B8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202A8D8
	mov r1, #0x0
	add r2, r1, #0x0
	bl FUN_0202A3B4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_020429E8
FUN_020429E8: ; 0x020429E8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202A8D8
	add r1, r5, #0x0
	mov r2, #0x5
	bl FUN_0202A3B4
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02042A18
FUN_02042A18: ; 0x02042A18
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202A8D8
	add r1, r5, #0x0
	mov r2, #0x6
	bl FUN_0202A3B4
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02042A48
FUN_02042A48: ; 0x02042A48
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r5, [r1, #0xc]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202A8D8
	mov r1, #0x0
	add r2, r1, #0x0
	bl FUN_0202A3B4
	cmp r0, r6
	bhs _02042A8E
	mov r0, #0x0
	b _02042A90
_02042A8E:
	mov r0, #0x1
_02042A90:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02042A98
FUN_02042A98: ; 0x02042A98
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	cmp r7, #0x1
	bne _02042AEE
	mov r1, #0x1a
	b _02042AF0
_02042AEE:
	mov r1, #0x0
_02042AF0:
	add r1, r1, r6
	lsl r2, r1, #0x2
	ldr r1, _02042B04 ; =0x020F433E
	ldrh r1, [r1, r2]
	strh r1, [r4, #0x0]
	ldr r1, _02042B08 ; =0x020F4340
	ldrh r1, [r1, r2]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02042B04: .word 0x020F433E
_02042B08: .word 0x020F4340

	thumb_func_start FUN_02042B0C
FUN_02042B0C: ; 0x02042B0C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r1, r0, #0x0
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r1, [r1, #0x0]
	bl FUN_0204B5FC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02042B40
FUN_02042B40: ; 0x02042B40
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_0204B63C
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02042B74
FUN_02042B74: ; 0x02042B74
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_0204B660
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02042BA8
FUN_02042BA8: ; 0x02042BA8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_0204B684
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02042BDC
FUN_02042BDC: ; 0x02042BDC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_0204B6A4
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02042C10
FUN_02042C10: ; 0x02042C10
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_0204B57C
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02042C44
FUN_02042C44: ; 0x02042C44
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_0204B5A8
	add r0, r6, #0x0
	mov r1, #0x3
	bl FUN_0202A0E8
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02042C8C
FUN_02042C8C: ; 0x02042C8C
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	cmp r0, #0x0
	beq _02042C9E
	cmp r0, #0x1
	beq _02042CA8
	b _02042CB2
_02042C9E:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_0204B9A0
	b _02042CB6
_02042CA8:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_0204B9CC
	b _02042CB6
_02042CB2:
	bl ErrorHandling
_02042CB6:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02042CBC
FUN_02042CBC: ; 0x02042CBC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r1, r0, #0x0
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r1, [r1, #0x0]
	bl FUN_0204B4FC
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0202A170
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02042CF0
FUN_02042CF0: ; 0x02042CF0
	str r1, [r0, #0x0]
	str r2, [r0, #0x4]
	str r3, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02042CF8
FUN_02042CF8: ; 0x02042CF8
	push {r3, lr}
	bl FUN_0202AF9C
	bl FUN_0202AFC0
	pop {r3, pc}

	thumb_func_start FUN_02042D04
FUN_02042D04: ; 0x02042D04
	push {r3, lr}
	bl FUN_0202AF9C
	bl FUN_0202AFFC
	pop {r3, pc}

	thumb_func_start FUN_02042D10
FUN_02042D10: ; 0x02042D10
	push {r3, lr}
	bl FUN_0202AF9C
	bl FUN_0202B020
	pop {r3, pc}

	thumb_func_start FUN_02042D1C
FUN_02042D1C: ; 0x02042D1C
	push {r3-r7, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	bl ScriptReadHalfword
	cmp r0, #0x8
	bls _02042D2C
	b _02042F04
_02042D2C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02042D38: ; jump table (using 16-bit offset)
	.short _02042D4A - _02042D38 - 2; case 0
	.short _02042D74 - _02042D38 - 2; case 1
	.short _02042DA0 - _02042D38 - 2; case 2
	.short _02042DC0 - _02042D38 - 2; case 3
	.short _02042DFC - _02042D38 - 2; case 4
	.short _02042E2E - _02042D38 - 2; case 5
	.short _02042E9A - _02042D38 - 2; case 6
	.short _02042D58 - _02042D38 - 2; case 7
	.short _02042D66 - _02042D38 - 2; case 8
_02042D4A:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	mov r1, #0x20
	ldr r0, [r0, #0xc]
	bl FUN_0202AF70
	b _02042F04
_02042D58:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0xc]
	bl FUN_0202AF88
	b _02042F04
_02042D66:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	ldr r0, [r0, #0xc]
	bl FUN_0202AF88
	b _02042F04
_02042D74:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02042CF8
	cmp r0, #0x0
	beq _02042D9A
	mov r0, #0x1
	strh r0, [r5, #0x0]
	b _02042F04
_02042D9A:
	mov r0, #0x0
	strh r0, [r5, #0x0]
	b _02042F04
_02042DA0:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02042CF8
	strh r0, [r5, #0x0]
	b _02042F04
_02042DC0:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02042CF8
	sub r0, r0, #0x1
	lsl r5, r0, #0x4
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r7, _02042F0C ; =0x020F43E4
	bl FUN_02042D04
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r2, [r7, r5]
	blx r2
	strh r0, [r6, #0x0]
	b _02042F04
_02042DFC:
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02042CF8
	sub r0, r0, #0x1
	ldr r1, _02042F0C ; =0x020F43E4
	lsl r0, r0, #0x4
	add r5, r1, r0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02042D04
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r2, [r5, #0x4]
	blx r2
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_02042D10
	b _02042F04
_02042E2E:
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02042CF8
	sub r0, r0, #0x1
	ldr r1, _02042F0C ; =0x020F43E4
	lsl r0, r0, #0x4
	add r5, r1, r0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02042D04
	add r4, #0x80
	add r3, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r2, [r6, #0x0]
	add r0, sp, #0x14
	bl FUN_02042CF0
	ldr r2, [sp, #0x0]
	ldr r3, [r5, #0x8]
	add r0, sp, #0x14
	add r1, r7, #0x0
	blx r3
	b _02042F04
_02042E9A:
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02042CF8
	sub r0, r0, #0x1
	ldr r1, _02042F0C ; =0x020F43E4
	lsl r0, r0, #0x4
	add r5, r1, r0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02042D04
	add r4, #0x80
	add r3, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r2, [r6, #0x0]
	add r0, sp, #0x8
	bl FUN_02042CF0
	ldr r2, [sp, #0x4]
	ldr r3, [r5, #0xc]
	add r0, sp, #0x8
	add r1, r7, #0x0
	blx r3
_02042F04:
	mov r0, #0x0
	add sp, #0x20
	pop {r3-r7, pc}
	nop
_02042F0C: .word 0x020F43E4

	thumb_func_start FUN_02042F10
FUN_02042F10: ; 0x02042F10
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	cmp r0, #0x6
	bge _02042F24
	mov r0, #0x1
	pop {r3, pc}
_02042F24:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02042F28
FUN_02042F28: ; 0x02042F28
	push {r3, lr}
	sub sp, #0x8
	add r1, r0, #0x0
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r3, #0x1
	str r3, [sp, #0x4]
	ldr r1, [r1, #0xc]
	ldr r2, _02042F44 ; =0x000001EA
	mov r0, #0x20
	bl FUN_0204A0C8
	add sp, #0x8
	pop {r3, pc}
	.balign 4
_02042F44: .word 0x000001EA

	thumb_func_start FUN_02042F48
FUN_02042F48: ; 0x02042F48
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r1, #0x0]
	mov r0, #0xd
	strh r0, [r2, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r4, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02042F6C
FUN_02042F6C: ; 0x02042F6C
	push {r3-r7, lr}
	sub sp, #0x38
	str r0, [sp, #0x4]
	bl FUN_02042D04
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	mov r7, #0x0
	add r5, r0, #0x0
	add r4, r0, #0x4
	add r0, r4, #0x0
	mov r1, #0x97
	add r2, r7, #0x0
	add r5, #0xf0
	bl FUN_020671BC
	add r1, r7, #0x0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x14]
	add r0, r4, #0x0
	mov r1, #0x7
	add r2, r7, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	bl OS_GetTick
	bl FUN_0201BA10
	add r1, r0, #0x0
	ldr r0, [sp, #0x14]
	str r1, [sp, #0x34]
	cmp r0, #0x0
	beq _02042FE8
	cmp r0, #0x1
	bne _02042FE6
	add r0, r6, #0x0
	bl FUN_02068AAC
	cmp r0, #0x0
	beq _02042FE8
_02042FD0:
	ldr r0, [sp, #0x34]
	bl FUN_0201BA10
	add r1, r0, #0x0
	add r0, r6, #0x0
	str r1, [sp, #0x34]
	bl FUN_02068AAC
	cmp r0, #0x0
	bne _02042FD0
	b _02042FE8
_02042FE6:
	str r0, [sp, #0x34]
_02042FE8:
	ldr r1, [sp, #0x34]
	add r0, r4, #0x0
	bl FUN_0206A23C
	add r0, r4, #0x0
	bl FUN_020689E0
	str r0, [sp, #0x30]
	add r0, r4, #0x0
	mov r1, #0x6f
	add r2, sp, #0x30
	bl FUN_02067830
	add r0, r4, #0x0
	mov r1, #0x4b
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x18]
	add r0, r4, #0x0
	mov r1, #0x4a
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x49
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x20]
	add r0, r4, #0x0
	mov r1, #0x48
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x24]
	add r0, r4, #0x0
	mov r1, #0x46
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x47
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r6, r0
	ldr r0, [sp, #0x24]
	add r1, r0, r1
	ldr r0, [sp, #0x20]
	add r1, r0, r1
	ldr r0, [sp, #0x1c]
	add r1, r0, r1
	ldr r0, [sp, #0x18]
	add r0, r0, r1
	str r0, [sp, #0x30]
	bne _020430DA
	bl FUN_0201B9EC
	add r6, r0, #0x0
	mov r0, #0x1f
	and r0, r6
	str r0, [sp, #0x34]
	add r0, r4, #0x0
	mov r1, #0x46
	add r2, sp, #0x34
	bl FUN_02067830
	mov r0, #0x3e
	lsl r0, r0, #0x4
	and r0, r6
	lsr r0, r0, #0x5
	str r0, [sp, #0x34]
	add r0, r4, #0x0
	mov r1, #0x47
	add r2, sp, #0x34
	bl FUN_02067830
	mov r0, #0x1f
	lsl r0, r0, #0xa
	and r0, r6
	lsr r0, r0, #0xa
	str r0, [sp, #0x34]
	add r0, r4, #0x0
	mov r1, #0x48
	add r2, sp, #0x34
	bl FUN_02067830
	bl FUN_0201B9EC
	add r6, r0, #0x0
	mov r0, #0x1f
	and r0, r6
	str r0, [sp, #0x34]
	add r0, r4, #0x0
	mov r1, #0x49
	add r2, sp, #0x34
	bl FUN_02067830
	mov r0, #0x3e
	lsl r0, r0, #0x4
	and r0, r6
	lsr r0, r0, #0x5
	str r0, [sp, #0x34]
	add r0, r4, #0x0
	mov r1, #0x4a
	add r2, sp, #0x34
	bl FUN_02067830
	mov r0, #0x1f
	lsl r0, r0, #0xa
	and r0, r6
	lsr r0, r0, #0xa
	str r0, [sp, #0x34]
	add r0, r4, #0x0
	mov r1, #0x4b
	add r2, sp, #0x34
	bl FUN_02067830
_020430DA:
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0xc]
	bl FUN_0202A918
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2e
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _020430FC
	mov r0, #0x49
	bl FUN_0207FCE0
	ldrb r1, [r5, #0x0]
	strb r1, [r6, r0]
_020430FC:
	add r0, r4, #0x0
	mov r1, #0x2f
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02043114
	mov r0, #0x4a
	bl FUN_0207FCE0
	ldrb r1, [r5, #0x1]
	strb r1, [r6, r0]
_02043114:
	add r0, r4, #0x0
	mov r1, #0x30
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0204312C
	mov r0, #0x4b
	bl FUN_0207FCE0
	ldrb r1, [r5, #0x2]
	strb r1, [r6, r0]
_0204312C:
	add r0, r4, #0x0
	mov r1, #0x31
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02043144
	mov r0, #0x4c
	bl FUN_0207FCE0
	ldrb r1, [r5, #0x3]
	strb r1, [r6, r0]
_02043144:
	add r0, r4, #0x0
	mov r1, #0x32
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0204315C
	mov r0, #0x4d
	bl FUN_0207FCE0
	ldrb r1, [r5, #0x4]
	strb r1, [r6, r0]
_0204315C:
	add r0, r4, #0x0
	mov r1, #0x33
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02043174
	mov r0, #0x4e
	bl FUN_0207FCE0
	ldrb r1, [r5, #0x5]
	strb r1, [r6, r0]
_02043174:
	add r0, r4, #0x0
	mov r1, #0x34
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0204318C
	mov r0, #0x4f
	bl FUN_0207FCE0
	ldrb r1, [r5, #0x6]
	strb r1, [r6, r0]
_0204318C:
	add r0, r4, #0x0
	mov r1, #0x67
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _020431A4
	mov r0, #0x19
	bl FUN_0207FCE0
	ldrb r1, [r5, #0x7]
	strb r1, [r6, r0]
_020431A4:
	add r0, r4, #0x0
	mov r1, #0x68
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _020431BC
	mov r0, #0x1a
	bl FUN_0207FCE0
	ldrb r1, [r5, #0x8]
	strb r1, [r6, r0]
_020431BC:
	add r0, r4, #0x0
	mov r1, #0x69
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _020431D4
	mov r0, #0x1b
	bl FUN_0207FCE0
	ldrb r1, [r5, #0x9]
	strb r1, [r6, r0]
_020431D4:
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204322C
	ldr r0, [sp, #0xc]
	mov r1, #0x20
	bl FUN_020239A0
	add r5, r0, #0x0
	ldr r0, [sp, #0xc]
	bl FUN_020239BC
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0xc]
	bl FUN_020239CC
	str r0, [sp, #0x28]
	mov r0, #0x20
	bl FUN_020669C0
	add r7, r0, #0x0
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_02069B88
	add r0, r7, #0x0
	mov r1, #0x90
	add r2, r5, #0x0
	bl FUN_02067830
	add r0, r7, #0x0
	mov r1, #0x7
	add r2, sp, #0x2c
	bl FUN_02067830
	add r0, r7, #0x0
	mov r1, #0x9c
	add r2, sp, #0x28
	bl FUN_02067830
	add r0, r5, #0x0
	add r4, r7, #0x0
	bl FUN_02021A20
_0204322C:
	ldr r1, [sp, #0x8]
	mov r0, #0x2
	bl FUN_02015CF8
	add r3, r0, #0x0
	mov r0, #0x20
	str r0, [sp, #0x0]
	ldr r1, [sp, #0xc]
	add r0, r4, #0x0
	mov r2, #0x4
	bl FUN_0208089C
	add r0, r4, #0x0
	bl FUN_02066ED8
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_0206B900
	cmp r0, #0x0
	beq _02043266
	ldr r0, [sp, #0x4]
	add r1, r4, #0x0
	ldr r0, [r0, #0xc]
	bl FUN_0202C144
_02043266:
	cmp r7, #0x0
	beq _02043270
	add r0, r7, #0x0
	bl FUN_02016A18
_02043270:
	add sp, #0x38
	pop {r3-r7, pc}

	thumb_func_start FUN_02043274
FUN_02043274: ; 0x02043274
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02042D04
	add r7, r0, #0x0
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x7
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	add r0, r7, #0x4
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	bl FUN_0200ACA4
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020432B4
FUN_020432B4: ; 0x020432B4
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r1, #0x0]
	mov r0, #0x4
	strh r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_020432C0
FUN_020432C0: ; 0x020432C0
	ldr r3, _020432C4 ; =FUN_02042F6C
	bx r3
	.balign 4
_020432C4: .word FUN_02042F6C 

	thumb_func_start FUN_020432C8
FUN_020432C8: ; 0x020432C8
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02042D04
	add r7, r0, #0x0
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x8
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	add r0, r7, #0x4
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	bl FUN_0200AC60
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02043308
FUN_02043308: ; 0x02043308
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02042D04
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0206ED24
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02043330
FUN_02043330: ; 0x02043330
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02042D04
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0206ED38
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02043358
FUN_02043358: ; 0x02043358
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02042D04
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x9
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	add r2, r7, #0x0
	bl FUN_0200AE38
	pop {r3-r7, pc}

	thumb_func_start FUN_02043394
FUN_02043394: ; 0x02043394
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	ldr r0, [r0, #0xc]
	add r6, r2, #0x0
	bl FUN_0206F158
	ldr r0, [r5, #0x0]
	bl FUN_02042D04
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x5
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x4]
	bl FUN_0200AE38
	pop {r4-r6, pc}

	thumb_func_start FUN_020433C4
FUN_020433C4: ; 0x020433C4
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_020433C8
FUN_020433C8: ; 0x020433C8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02042D04
	add r1, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02023BD4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020433DC
FUN_020433DC: ; 0x020433DC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02042D04
	add r7, r0, #0x0
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0xa
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	add r0, r7, #0x0
	mov r1, #0x20
	bl FUN_02023AF4
	add r4, r0, #0x0
	mov r1, #0x1
	str r1, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x4]
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl FUN_02021A20
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02043430
FUN_02043430: ; 0x02043430
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r1, #0x0]
	mov r0, #0x6
	strh r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_0204343C
FUN_0204343C: ; 0x0204343C
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	bl FUN_02025DB0
	cmp r0, #0xc8
	bge _02043450
	mov r0, #0x1
	pop {r3, pc}
_02043450:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02043454
FUN_02043454: ; 0x02043454
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02042D04
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02026CC4
	ldr r1, [r4, #0x0]
	bl FUN_02025D6C
	pop {r3-r5, pc}

	thumb_func_start FUN_0204346C
FUN_0204346C: ; 0x0204346C
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02042D04
	ldr r7, [r0, #0x0]
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0xb
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	add r2, r7, #0x0
	bl FUN_0200B350
	pop {r3-r7, pc}

	thumb_func_start FUN_020434A4
FUN_020434A4: ; 0x020434A4
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r1, #0x0]
	mov r0, #0x6
	strh r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_020434B0
FUN_020434B0: ; 0x020434B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02042D04
	ldr r4, [r0, #0x4]
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _020434CA
	cmp r0, #0x2
	beq _020434DA
	cmp r0, #0x3
	beq _020434DE
	b _020434E2
_020434CA:
	ldr r0, [r5, #0xc]
	bl FUN_02029C80
	add r1, r4, #0x0
	mov r2, #0x1
	bl FUN_02029DD4
	pop {r3-r5, pc}
_020434DA:
	mov r0, #0x1
	pop {r3-r5, pc}
_020434DE:
	mov r0, #0x1
	pop {r3-r5, pc}
_020434E2:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020434E8
FUN_020434E8: ; 0x020434E8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02042D04
	ldr r4, [r0, #0x4]
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _02043502
	cmp r0, #0x2
	beq _02043512
	cmp r0, #0x3
	beq _02043526
	pop {r3-r5, pc}
_02043502:
	ldr r0, [r5, #0xc]
	bl FUN_02029C80
	add r1, r4, #0x0
	mov r2, #0x1
	bl FUN_02029D44
	pop {r3-r5, pc}
_02043512:
	ldr r0, [r5, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	mov r2, #0x1
	bl FUN_020271A4
	pop {r3-r5, pc}
_02043526:
	ldr r0, [r5, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	bl FUN_02027264
	pop {r3-r5, pc}

	thumb_func_start FUN_02043538
FUN_02043538: ; 0x02043538
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02042D04
	ldr r2, [r0, #0x4]
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _02043558
	cmp r0, #0x2
	beq _02043562
	cmp r0, #0x3
	beq _0204356C
	b _02043574
_02043558:
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	bl FUN_0200B534
	b _02043574
_02043562:
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	bl FUN_0200B660
	b _02043574
_0204356C:
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	bl FUN_0200B6D0
_02043574:
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0xc
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02043594
FUN_02043594: ; 0x02043594
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r1, #0x0]
	mov r0, #0x6
	strh r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_020435A0
FUN_020435A0: ; 0x020435A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02042D04
	ldr r1, _020435C0 ; =0x000001C6
	add r0, r4, #0x0
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0206ED24
	pop {r3-r5, pc}
	.balign 4
_020435C0: .word 0x000001C6

	thumb_func_start FUN_020435C4
FUN_020435C4: ; 0x020435C4
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206F158
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02042D04
	ldr r0, [r4, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	ldr r1, _020435F4 ; =0x000001C6
	add r0, r5, #0x0
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0206ED38
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0205F478
	pop {r3-r5, pc}
	.balign 4
_020435F4: .word 0x000001C6

	thumb_func_start FUN_020435F8
FUN_020435F8: ; 0x020435F8
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02042D04
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0xe
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	ldr r0, [r5, #0x4]
	ldr r2, _02043630 ; =0x000001C6
	mov r1, #0x1
	bl FUN_0200AE38
	pop {r4-r6, pc}
	nop
_02043630: .word 0x000001C6

	thumb_func_start FUN_02043634
FUN_02043634: ; 0x02043634
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	ldr r0, [r0, #0xc]
	add r6, r2, #0x0
	bl FUN_0206F158
	ldr r0, [r5, #0x0]
	bl FUN_02042D04
	mov r2, #0x53
	lsl r2, r2, #0x2
	strh r2, [r4, #0x0]
	mov r0, #0x5
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	add r2, #0x7a
	bl FUN_0200AE38
	pop {r4-r6, pc}

	thumb_func_start FUN_02043660
FUN_02043660: ; 0x02043660
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02042D04
	mov r1, #0x71
	add r0, r4, #0x0
	lsl r1, r1, #0x2
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0206ED24
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02043684
FUN_02043684: ; 0x02043684
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206F158
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02042D04
	ldr r0, [r4, #0xc]
	bl FUN_020462AC
	mov r1, #0x71
	add r4, r0, #0x0
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0206ED38
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0205F478
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020436B8
FUN_020436B8: ; 0x020436B8
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02042D04
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0xf
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	mov r2, #0x71
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	lsl r2, r2, #0x2
	bl FUN_0200AE38
	pop {r4-r6, pc}

	thumb_func_start FUN_020436F0
FUN_020436F0: ; 0x020436F0
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	ldr r0, [r0, #0xc]
	add r6, r2, #0x0
	bl FUN_0206F158
	ldr r0, [r5, #0x0]
	bl FUN_02042D04
	mov r2, #0x53
	lsl r2, r2, #0x2
	strh r2, [r4, #0x0]
	mov r0, #0x5
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	add r2, #0x78
	bl FUN_0200AE38
	pop {r4-r6, pc}

	thumb_func_start FUN_0204371C
FUN_0204371C: ; 0x0204371C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02042D04
	ldr r1, _0204373C ; =0x000001C7
	add r0, r4, #0x0
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0206ED24
	pop {r3-r5, pc}
	.balign 4
_0204373C: .word 0x000001C7

	thumb_func_start FUN_02043740
FUN_02043740: ; 0x02043740
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206F158
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02042D04
	ldr r0, [r4, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	ldr r1, _02043770 ; =0x000001C7
	add r0, r5, #0x0
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0206ED38
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0205F478
	pop {r3-r5, pc}
	.balign 4
_02043770: .word 0x000001C7

	thumb_func_start FUN_02043774
FUN_02043774: ; 0x02043774
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02042D04
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x10
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	ldr r0, [r5, #0x4]
	ldr r2, _020437AC ; =0x000001C7
	mov r1, #0x1
	bl FUN_0200AE38
	pop {r4-r6, pc}
	nop
_020437AC: .word 0x000001C7

	thumb_func_start FUN_020437B0
FUN_020437B0: ; 0x020437B0
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	ldr r0, [r0, #0xc]
	add r6, r2, #0x0
	bl FUN_0206F158
	ldr r0, [r5, #0x0]
	bl FUN_02042D04
	mov r2, #0x53
	lsl r2, r2, #0x2
	strh r2, [r4, #0x0]
	mov r0, #0x5
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	add r2, #0x7b
	bl FUN_0200AE38
	pop {r4-r6, pc}

	thumb_func_start FUN_020437DC
FUN_020437DC: ; 0x020437DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0204C1A8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02042D04
	add r0, r4, #0x0
	bl FUN_0204BEC8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020437F8
FUN_020437F8: ; 0x020437F8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0204C1A8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02042D04
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_0204BED8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02043818
FUN_02043818: ; 0x02043818
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02042D04
	add r7, r0, #0x0
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x12
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	ldr r0, [r5, #0x4]
	ldr r2, [r7, #0x0]
	mov r1, #0x1
	bl FUN_0200B02C
	pop {r3-r7, pc}

	thumb_func_start FUN_02043850
FUN_02043850: ; 0x02043850
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02042D04
	mov r0, #0x53
	lsl r0, r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x13
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	bl FUN_0200ABC0
	pop {r4-r6, pc}

	thumb_func_start FUN_0204387C
FUN_0204387C: ; 0x0204387C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	cmp r0, #0x0
	bne _020438B2
	add r0, r4, #0x0
	bl FUN_0205F224
	add r5, #0x80
	ldr r0, [r5, #0x0]
	bl FUN_0204B9EC
	b _020438CA
_020438B2:
	cmp r0, #0x1
	bne _020438C6
	add r0, r4, #0x0
	bl FUN_0205F234
	add r5, #0x80
	ldr r0, [r5, #0x0]
	bl FUN_0204BA1C
	b _020438CA
_020438C6:
	bl ErrorHandling
_020438CA:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020438D0
FUN_020438D0: ; 0x020438D0
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022528
	add r6, r0, #0x0
	mov r0, #0x20
	bl FUN_020669C0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0202C000
	cmp r0, #0x6
	bne _02043908
	mov r0, #0x1
	b _0204390A
_02043908:
	mov r0, #0x0
_0204390A:
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02016A18
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02043918
FUN_02043918: ; 0x02043918
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022528
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022510
	str r0, [sp, #0x8]
	mov r0, #0x20
	bl FUN_020669C0
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	mov r5, #0x0
_0204395C:
	add r0, r7, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0202BFD8
	mov r0, #0x20
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r4, #0x0
	mov r2, #0x2
	mov r3, #0x0
	bl FUN_0208089C
	add r0, r4, #0x0
	bl FUN_020690E4
	add r1, r0, #0x0
	ldr r0, [sp, #0x8]
	bl FUN_0206B20C
	cmp r0, #0x0
	bne _0204398C
	bl ErrorHandling
_0204398C:
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0xc]
	bl FUN_0202C144
	add r5, r5, #0x1
	cmp r5, #0x6
	blt _0204395C
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r7, #0x0
	bl FUN_0202BEDC
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_020439B4
FUN_020439B4: ; 0x020439B4
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	cmp r6, #0x3
	bhi _02043A40
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020439EE: ; jump table (using 16-bit offset)
	.short _020439F6 - _020439EE - 2; case 0
	.short _02043A02 - _020439EE - 2; case 1
	.short _02043A0E - _020439EE - 2; case 2
	.short _02043A1A - _020439EE - 2; case 3
_020439F6:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_0204BAC4
	strh r0, [r5, #0x0]
	b _02043A40
_02043A02:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_0204BAD4
	strh r0, [r5, #0x0]
	b _02043A40
_02043A0E:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_0204BAE4
	strh r0, [r5, #0x0]
	b _02043A40
_02043A1A:
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0204BAD4
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0204BAC4
	add r4, #0x80
	add r7, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0204BAE4
	add r0, r7, r0
	add r0, r6, r0
	strh r0, [r5, #0x0]
_02043A40:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02043A44
FUN_02043A44: ; 0x02043A44
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x26
	bl FUN_02039438
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl FUN_021E2950
	str r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02043A94
FUN_02043A94: ; 0x02043A94
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x26
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_021E29B4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02043AAC
FUN_02043AAC: ; 0x02043AAC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x26
	bl FUN_02039438
	add r1, r0, #0x0
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	bl FUN_021E29C8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02043ACC
FUN_02043ACC: ; 0x02043ACC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202390C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02028930
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02043AFC
FUN_02043AFC: ; 0x02043AFC
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202390C
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02028934
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02043B28
FUN_02043B28: ; 0x02043B28
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202390C
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202896C
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02043B54
FUN_02043B54: ; 0x02043B54
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202390C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r1, r0, #0x0
	ldrh r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_0202896C
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02043B84
FUN_02043B84: ; 0x02043B84
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_020377AC
	bl FUN_020238F4
	ldr r0, [r5, #0xc]
	bl FUN_0202390C
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadWord
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02028930
	cmp r0, r4
	bhs _02043BC8
	mov r0, #0x0
	b _02043BCA
_02043BC8:
	mov r0, #0x1
_02043BCA:
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02043BD0
FUN_02043BD0: ; 0x02043BD0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_020377AC
	bl FUN_020238F4
	ldr r0, [r4, #0xc]
	bl FUN_0202390C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	ldrh r5, [r0, #0x0]
	add r0, r6, #0x0
	bl FUN_02028930
	cmp r0, r5
	bhs _02043C1E
	mov r0, #0x0
	b _02043C20
_02043C1E:
	mov r0, #0x1
_02043C20:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02043C28
FUN_02043C28: ; 0x02043C28
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202390C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02028954
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02043C6C
FUN_02043C6C: ; 0x02043C6C
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadWord
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02023A30
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02043C90
FUN_02043C90: ; 0x02043C90
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadWord
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02023A54
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02043CB4
FUN_02043CB4: ; 0x02043CB4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02023A54
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02043CE4
FUN_02043CE4: ; 0x02043CE4
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadWord
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02023A10
	cmp r0, r4
	bhs _02043D20
	mov r0, #0x0
	b _02043D22
_02043D20:
	mov r0, #0x1
_02043D22:
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02043D28
FUN_02043D28: ; 0x02043D28
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02023A10
	cmp r0, r4
	bhs _02043D6E
	mov r0, #0x0
	b _02043D70
_02043D6E:
	mov r0, #0x1
_02043D70:
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02043D78
FUN_02043D78: ; 0x02043D78
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x27
	bl FUN_02039438
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl FUN_021E27E8
	str r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02043DC8
FUN_02043DC8: ; 0x02043DC8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x27
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_021E288C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02043DE0
FUN_02043DE0: ; 0x02043DE0
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x27
	bl FUN_02039438
	add r1, r0, #0x0
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	bl FUN_021E28A0
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02043E00
FUN_02043E00: ; 0x02043E00
	push {r3-r5, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	ldr r5, [r0, #0xc]
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02023D58
	ldr r1, [r4, #0x0]
	bl FUN_021ED4E0
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02043E20
FUN_02043E20: ; 0x02043E20
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02022610
	bl FUN_021ED5EC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02043E50
FUN_02043E50: ; 0x02043E50
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x8
	ldr r0, [r0, #0xc]
	bl FUN_02022610
	bl FUN_021ECD64
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02043E68
FUN_02043E68: ; 0x02043E68
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x8
	ldr r0, [r5, #0xc]
	bl FUN_02022610
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r2, r0, #0x0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_021ED0CC
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02043E9C
FUN_02043E9C: ; 0x02043E9C
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xf
	add r0, r5, #0x0
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	ldr r6, [r5, #0xc]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x8
	bl FUN_02022610
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	lsl r3, r4, #0x18
	ldr r1, [r7, #0x0]
	add r2, r6, #0x0
	lsr r3, r3, #0x18
	bl FUN_021EC71C
	ldr r1, [sp, #0x0]
	strh r0, [r1, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02043EFC
FUN_02043EFC: ; 0x02043EFC
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xf
	add r0, r5, #0x0
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	ldr r5, [r5, #0xc]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x8
	bl FUN_02022610
	lsl r1, r4, #0x18
	ldr r2, [r7, #0x0]
	lsr r1, r1, #0x18
	bl FUN_021EC854
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02043F50
FUN_02043F50: ; 0x02043F50
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	ldr r4, [r0, #0xc]
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02022610
	ldr r2, [r6, #0x0]
	add r1, r5, #0x0
	bl FUN_021EC864
	strh r0, [r7, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02043FA0
FUN_02043FA0: ; 0x02043FA0
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xf
	add r0, r5, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	ldr r2, [r6, #0x0]
	add r1, r7, #0x0
	bl FUN_021ED5C4
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02043FF4
FUN_02043FF4: ; 0x02043FF4
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r1, r6, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	ldr r5, [r4, #0xc]
	bl ScriptReadHalfword
	add r6, #0x80
	add r1, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206BB1C
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x8
	bl FUN_02022610
	lsl r1, r6, #0x18
	add r2, r0, #0x0
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	add r3, r5, #0x0
	bl FUN_021EC57C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02044034
FUN_02044034: ; 0x02044034
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	ldr r5, [r0, #0xc]
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02023D58
	lsl r1, r4, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x0]
	ldr r1, [r6, #0x0]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	str r1, [sp, #0x4]
	lsl r1, r7, #0x18
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_021ED52C
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_020440C0
FUN_020440C0: ; 0x020440C0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02022610
	bl FUN_021ED644
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020440F0
FUN_020440F0: ; 0x020440F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02022610
	bl FUN_02023C90
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02044120
FUN_02044120: ; 0x02044120
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02044138
FUN_02044138: ; 0x02044138
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0204413C
FUN_0204413C: ; 0x0204413C
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02044140
FUN_02044140: ; 0x02044140
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02044158
FUN_02044158: ; 0x02044158
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F54C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0204416C
FUN_0204416C: ; 0x0204416C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F55C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02044198
FUN_02044198: ; 0x02044198
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	bl FUN_0201B9EC
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0xf
	bhs _020441D6
	mov r0, #0x0
	b _02044218
_020441D6:
	cmp r0, #0x1e
	bhs _020441DE
	mov r0, #0x1
	b _02044218
_020441DE:
	cmp r0, #0x2d
	bhs _020441E6
	mov r0, #0x2
	b _02044218
_020441E6:
	cmp r0, #0x3c
	bhs _020441EE
	mov r0, #0x3
	b _02044218
_020441EE:
	cmp r0, #0x46
	bhs _020441F6
	mov r0, #0x4
	b _02044218
_020441F6:
	cmp r0, #0x50
	bhs _020441FE
	mov r0, #0x5
	b _02044218
_020441FE:
	cmp r0, #0x58
	bhs _02044206
	mov r0, #0x6
	b _02044218
_02044206:
	cmp r0, #0x5d
	bhs _0204420E
	mov r0, #0x7
	b _02044218
_0204420E:
	cmp r0, #0x62
	bhs _02044216
	mov r0, #0x8
	b _02044218
_02044216:
	mov r0, #0x9
_02044218:
	ldr r2, _020442B4 ; =0x0000011D
	cmp r5, r2
	bgt _02044244
	bge _02044290
	cmp r5, #0x27
	bgt _02044236
	cmp r5, #0x23
	blt _02044230
	beq _02044284
	cmp r5, #0x27
	beq _02044290
	b _0204429C
_02044230:
	cmp r5, #0x19
	beq _02044294
	b _0204429C
_02044236:
	cmp r5, #0x36
	bgt _0204423E
	beq _0204428C
	b _0204429C
_0204423E:
	cmp r5, #0xff
	beq _02044288
	b _0204429C
_02044244:
	add r1, r2, #0x0
	add r1, #0x8c
	cmp r5, r1
	bgt _0204426C
	add r1, r2, #0x0
	add r1, #0x8c
	cmp r5, r1
	bge _02044288
	add r1, r2, #0x0
	add r1, #0xf
	cmp r5, r1
	bgt _02044264
	add r2, #0xf
	cmp r5, r2
	beq _02044284
	b _0204429C
_02044264:
	add r2, #0x84
	cmp r5, r2
	beq _0204428C
	b _0204429C
_0204426C:
	add r1, r2, #0x0
	add r1, #0x8e
	cmp r5, r1
	bgt _0204427C
	add r2, #0x8e
	cmp r5, r2
	beq _02044298
	b _0204429C
_0204427C:
	add r2, #0x9b
	cmp r5, r2
	beq _02044298
	b _0204429C
_02044284:
	mov r2, #0x0
	b _0204429E
_02044288:
	mov r2, #0x1
	b _0204429E
_0204428C:
	mov r2, #0x2
	b _0204429E
_02044290:
	mov r2, #0x3
	b _0204429E
_02044294:
	mov r2, #0x4
	b _0204429E
_02044298:
	mov r2, #0x5
	b _0204429E
_0204429C:
	mov r2, #0x0
_0204429E:
	add r3, r2, #0x0
	mov r1, #0x14
	mul r3, r1
	ldr r2, _020442B8 ; =0x020F4494
	lsl r1, r0, #0x1
	add r0, r2, r3
	ldrh r0, [r1, r0]
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_020442B4: .word 0x0000011D
_020442B8: .word 0x020F4494

	thumb_func_start FUN_020442BC
FUN_020442BC: ; 0x020442BC
	push {r4-r7, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034824
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	ldr r0, [sp, #0x10]
	lsl r3, r7, #0x18
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	mov r0, #0xc
	str r0, [sp, #0x8]
	ldr r1, [r5, #0xc]
	ldr r2, [sp, #0xc]
	mov r0, #0xb
	lsr r3, r3, #0x18
	bl FUN_0204A048
	strh r0, [r4, #0x0]
	mov r0, #0x0
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0204434C
FUN_0204434C: ; 0x0204434C
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	ldrh r1, [r6, #0x0]
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _020443A0
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	b _020443A2
_020443A0:
	mov r0, #0x0
_020443A2:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020443A8
FUN_020443A8: ; 0x020443A8
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_020377AC
	bl FUN_020238F4
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	ldrh r1, [r6, #0x0]
	bl FUN_0206B9B0
	mov r1, #0x7
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r7, #0x0
	bl FUN_020239BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r5, r0
	bne _0204440C
	mov r0, #0x0
	b _0204440E
_0204440C:
	mov r0, #0x1
_0204440E:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02044414
FUN_02044414: ; 0x02044414
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	ldr r0, [r4, #0xc]
	bl FUN_020238F4
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206BB1C
	add r6, r0, #0x0
	bl FUN_0206B9AC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x6
	bhs _02044494
	mov r0, #0xb
	bl FUN_020669C0
	add r4, r0, #0x0
	bl FUN_02066978
	mov r0, #0x1
	add r1, r5, #0x0
	bl FUN_02015CF8
	mov r1, #0x3
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r1, [sp, #0x8]
	add r0, r4, #0x0
	mov r2, #0x1
	add r3, r7, #0x0
	bl FUN_021ECF14
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0206B900
	add r0, r4, #0x0
	bl FUN_02016A18
_02044494:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0204449C
FUN_0204449C: ; 0x0204449C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl FUN_0204A120
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020444F4
FUN_020444F4: ; 0x020444F4
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_0206B9B0
	mov r2, #0x0
	mov r1, #0x4c
	add r4, r0, #0x0
	strh r2, [r6, #0x0]
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02044556
	mov r0, #0x0
	pop {r3-r7, pc}
_02044556:
	add r0, r4, #0x0
	mov r1, #0x36
	mov r2, #0x0
	bl FUN_020671BC
	cmp r5, r0
	beq _0204458E
	add r0, r4, #0x0
	mov r1, #0x37
	mov r2, #0x0
	bl FUN_020671BC
	cmp r5, r0
	beq _0204458E
	add r0, r4, #0x0
	mov r1, #0x38
	mov r2, #0x0
	bl FUN_020671BC
	cmp r5, r0
	beq _0204458E
	add r0, r4, #0x0
	mov r1, #0x39
	mov r2, #0x0
	bl FUN_020671BC
	cmp r5, r0
	bne _02044592
_0204458E:
	mov r0, #0x1
	strh r0, [r6, #0x0]
_02044592:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02044598
FUN_02044598: ; 0x02044598
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x4]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r1, _02044650 ; =0x00000006
	ldr r0, [sp, #0x0]
	ldr r6, _02044654 ; =0x00000000
	strh r1, [r0, #0x0]
	beq _02044648
_020445E4:
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _0204463E
	add r0, r4, #0x0
	mov r1, #0x36
	mov r2, #0x0
	bl FUN_020671BC
	cmp r5, r0
	beq _02044638
	add r0, r4, #0x0
	mov r1, #0x37
	mov r2, #0x0
	bl FUN_020671BC
	cmp r5, r0
	beq _02044638
	add r0, r4, #0x0
	mov r1, #0x38
	mov r2, #0x0
	bl FUN_020671BC
	cmp r5, r0
	beq _02044638
	add r0, r4, #0x0
	mov r1, #0x39
	mov r2, #0x0
	bl FUN_020671BC
	cmp r5, r0
	bne _0204463E
_02044638:
	ldr r0, [sp, #0x0]
	strh r6, [r0, #0x0]
	b _02044648
_0204463E:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, r7
	blo _020445E4
_02044648:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02044650: .word 0x00000006
_02044654: .word 0x00000000

	thumb_func_start FUN_02044658
FUN_02044658: ; 0x02044658
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	bl FUN_0204A32C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0204469C
FUN_0204469C: ; 0x0204469C
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	mov r4, #0x0
	ldr r0, [sp, #0x4]
	add r5, r4, #0x0
	strh r4, [r0, #0x0]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bls _02044726
_020446EA:
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r6, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _0204471A
	add r0, r6, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bhi _0204471A
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
_0204471A:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x8]
	cmp r4, r0
	blo _020446EA
_02044726:
	ldr r0, [sp, #0x4]
	strh r5, [r0, #0x0]
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02044730
FUN_02044730: ; 0x02044730
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r2, #0x0
	mov r1, #0x4c
	add r5, r0, #0x0
	strh r2, [r4, #0x0]
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02044786
	add r0, r5, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r4, #0x0]
_02044786:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204478C
FUN_0204478C: ; 0x0204478C
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r1, r6, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl ScriptReadHalfword
	add r6, #0x80
	add r1, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r6, r0
	blt _020447D2
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_020447D2:
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _020447F2
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_020447F2:
	add r0, r5, #0x0
	bl FUN_02068854
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02044800
FUN_02044800: ; 0x02044800
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r1, _02044884 ; =0x000000FF
	ldr r0, [sp, #0x4]
	ldr r5, _02044888 ; =0x00000000
	strh r1, [r0, #0x0]
	beq _0204487E
_02044848:
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02044874
	add r0, r4, #0x0
	bl FUN_02068854
	ldr r1, [sp, #0x0]
	cmp r1, r0
	bne _02044874
	ldr r0, [sp, #0x4]
	strh r5, [r0, #0x0]
	b _0204487E
_02044874:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r6
	blo _02044848
_0204487E:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02044884: .word 0x000000FF
_02044888: .word 0x00000000

	thumb_func_start FUN_0204488C
FUN_0204488C: ; 0x0204488C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x9
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020448D4
FUN_020448D4: ; 0x020448D4
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034824
	add r7, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	ldr r1, [sp, #0x0]
	bl FUN_0206B9B0
	mov r1, #0x9
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020671BC
	add r1, sp, #0x4
	strh r0, [r1, #0x0]
	cmp r4, #0x0
	beq _02044982
	add r0, r5, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x1
	mov r2, #0xb
	bl FUN_0206E7B8
	cmp r0, #0x34
	bne _0204495A
	mov r0, #0x96
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0204495A:
	add r0, r5, #0x0
	mov r1, #0x9a
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0xb
	bne _0204496E
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0204496E:
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	cmp r7, r0
	bne _02044982
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02044982:
	add r0, sp, #0x4
	ldrh r1, [r0, #0x0]
	add r1, r1, r4
	strh r1, [r0, #0x0]
	ldrh r1, [r0, #0x0]
	cmp r1, #0xff
	bls _02044994
	mov r1, #0xff
	strh r1, [r0, #0x0]
_02044994:
	add r0, r5, #0x0
	mov r1, #0x9
	add r2, sp, #0x4
	bl FUN_02067830
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_020449A4
FUN_020449A4: ; 0x020449A4
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x9
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020671BC
	add r1, sp, #0x0
	strh r0, [r1, #0x0]
	ldrh r0, [r1, #0x0]
	cmp r4, r0
	bls _020449F8
	mov r0, #0x0
	b _020449FA
_020449F8:
	sub r0, r0, r4
_020449FA:
	strh r0, [r1, #0x0]
	add r0, r5, #0x0
	mov r1, #0x9
	add r2, sp, #0x0
	bl FUN_02067830
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start FUN_02044A0C
FUN_02044A0C: ; 0x02044A0C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r7, #0x0
	bl FUN_0206B9B0
	add r4, #0x13
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02044A6C
FUN_02044A6C: ; 0x02044A6C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02054DEC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02044A94
FUN_02044A94: ; 0x02044A94
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	add r4, r0, #0x0
	mov r1, #0xb0
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r6, #0x0]
	add r0, r4, #0x0
	mov r1, #0xb1
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r7, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02044B00
FUN_02044B00: ; 0x02044B00
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02044B2C
FUN_02044B2C: ; 0x02044B2C
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	mov r5, #0x0
	add r7, r0, #0x0
	add r4, r5, #0x0
	cmp r7, #0x0
	ble _02044B7A
_02044B5A:
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02044B74
	add r4, r4, #0x1
_02044B74:
	add r5, r5, #0x1
	cmp r5, r7
	blt _02044B5A
_02044B7A:
	ldr r0, [sp, #0x0]
	strh r4, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02044B84
FUN_02044B84: ; 0x02044B84
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	mov r5, #0x0
	add r4, r5, #0x0
	str r0, [sp, #0x8]
	cmp r0, #0x0
	ble _02044C00
_02044BC8:
	ldr r0, [sp, #0x0]
	cmp r5, r0
	beq _02044BF8
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r6, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02044BF8
	add r0, r6, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02044BF8
	add r4, r4, #0x1
_02044BF8:
	ldr r0, [sp, #0x8]
	add r5, r5, #0x1
	cmp r5, r0
	blt _02044BC8
_02044C00:
	ldr r0, [sp, #0x4]
	strh r4, [r0, #0x0]
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02044C0C
FUN_02044C0C: ; 0x02044C0C
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	ldr r0, [r7, #0xc]
	bl FUN_02022510
	str r0, [sp, #0x4]
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	mov r5, #0x0
	add r4, r5, #0x0
	str r0, [sp, #0x8]
	cmp r0, #0x0
	ble _02044C76
_02044C44:
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r6, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02044C6E
	add r0, r6, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02044C6E
	add r4, r4, #0x1
_02044C6E:
	ldr r0, [sp, #0x8]
	add r5, r5, #0x1
	cmp r5, r0
	blt _02044C44
_02044C76:
	ldr r0, [sp, #0x4]
	bl FUN_0206B57C
	add r1, r4, r0
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02044C88
FUN_02044C88: ; 0x02044C88
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	mov r5, #0x0
	add r7, r0, #0x0
	add r4, r5, #0x0
	cmp r7, #0x0
	ble _02044CD6
_02044CB6:
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02044CD0
	add r4, r4, #0x1
_02044CD0:
	add r5, r5, #0x1
	cmp r5, r7
	blt _02044CB6
_02044CD6:
	ldr r0, [sp, #0x0]
	strh r4, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02044CE0
FUN_02044CE0: ; 0x02044CE0
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r4, _02044D40 ; =0x00000000
	ldr r0, [sp, #0x0]
	strh r4, [r0, #0x0]
	beq _02044D3C
	mov r7, #0x99
_02044D12:
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_0206B9B0
	add r1, r7, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02044D32
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	strh r1, [r0, #0x0]
	b _02044D3C
_02044D32:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r6
	blo _02044D12
_02044D3C:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02044D40: .word 0x00000000

	thumb_func_start FUN_02044D44
FUN_02044D44: ; 0x02044D44
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x6f
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02044D8C
FUN_02044D8C: ; 0x02044D8C
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r6, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02044DDA
	mov r0, #0x0
	strh r0, [r5, #0x0]
	pop {r4-r6, pc}
_02044DDA:
	mov r4, #0x0
	add r0, r6, #0x0
	mov r1, #0x36
	add r2, r4, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02044DF0
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02044DF0:
	add r0, r6, #0x0
	mov r1, #0x37
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02044E04
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02044E04:
	add r0, r6, #0x0
	mov r1, #0x38
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02044E18
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02044E18:
	add r0, r6, #0x0
	mov r1, #0x39
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02044E2C
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02044E2C:
	strh r4, [r5, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02044E34
FUN_02044E34: ; 0x02044E34
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	add r1, r4, #0x0
	bl FUN_020699A4
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02044E78
FUN_02044E78: ; 0x02044E78
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	add r1, r7, #0x0
	bl FUN_0206B9B0
	add r4, #0x36
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02044ED8
FUN_02044ED8: ; 0x02044ED8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x6
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02044F20
FUN_02044F20: ; 0x02044F20
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r2, #0x0
	add r1, sp, #0x0
	strh r2, [r1, #0x0]
	mov r1, #0x6
	add r2, sp, #0x0
	bl FUN_02067830
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02044F58
FUN_02044F58: ; 0x02044F58
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r5, _02044FE4 ; =0x00000000
	ldr r0, [sp, #0x4]
	strh r5, [r0, #0x0]
	beq _02044FDE
_02044F9E:
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02044FD4
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [sp, #0x0]
	cmp r0, r1
	bne _02044FD4
	ldr r0, [sp, #0x4]
	mov r1, #0x1
	strh r1, [r0, #0x0]
	b _02044FDE
_02044FD4:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r6
	blo _02044F9E
_02044FDE:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02044FE4: .word 0x00000000

	thumb_func_start FUN_02044FE8
FUN_02044FE8: ; 0x02044FE8
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_0206B9B0
	mov r4, #0x0
	add r6, r0, #0x0
	add r5, r4, #0x0
	add r7, r4, #0x0
_0204502A:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	add r1, r7, #0x0
	bl FUN_0207FC5C
	add r1, r0, #0x0
	add r0, r6, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02045048
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_02045048:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x50
	blo _0204502A
	ldr r0, [sp, #0x0]
	strh r5, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204505C
FUN_0204505C: ; 0x0204505C
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	lsl r0, r0, #0x10
	add r4, #0x80
	lsr r6, r0, #0x10
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x8]
	str r0, [sp, #0x4]
_0204509A:
	mov r5, #0x0
	cmp r6, #0x0
	bls _020450E8
	ldr r0, [sp, #0x8]
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
_020450A6:
	ldr r0, [sp, #0xc]
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _020450E8
	add r0, r7, #0x0
	mov r1, #0x0
	bl FUN_0207FC5C
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _020450DE
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	b _020450E8
_020450DE:
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, r6
	blo _020450A6
_020450E8:
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x8]
	cmp r0, #0x50
	blo _0204509A
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02045104
FUN_02045104: ; 0x02045104
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r7, #0x0
	bl FUN_0206B9B0
	add r5, r0, #0x0
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	mov r1, #0x0
	bl FUN_0207FC5C
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02045170
FUN_02045170: ; 0x02045170
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	mov r1, #0x1
	add r0, sp, #0x0
	add r5, #0x80
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	add r5, r0, #0x0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	mov r1, #0x0
	bl FUN_0207FC5C
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r2, sp, #0x0
	bl FUN_02067830
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_020451D0
FUN_020451D0: ; 0x020451D0
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	bl FUN_0206B9AC
	lsl r0, r0, #0x10
	add r4, #0x80
	lsr r6, r0, #0x10
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x4]
_0204520C:
	mov r5, #0x0
	cmp r6, #0x0
	bls _0204524C
_02045212:
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x4c
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02045242
	add r0, r4, #0x0
	mov r1, #0x3
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02045242
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	strh r1, [r0, #0x0]
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_02045242:
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, r6
	blo _02045212
_0204524C:
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	cmp r0, #0x50
	blo _0204520C
	ldr r1, [sp, #0x0]
	mov r0, #0x0
	strh r0, [r1, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02045264
FUN_02045264: ; 0x02045264
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02045268
FUN_02045268: ; 0x02045268
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r4, #0x0
	ldr r7, _020452B0 ; =0x020F450C
	str r0, [sp, #0x0]
	add r5, r4, #0x0
_02045288:
	ldr r0, [r6, #0xc]
	bl FUN_0206F158
	lsl r1, r4, #0x2
	ldrh r1, [r7, r1]
	mov r2, #0x4
	bl FUN_0206EEF8
	add r0, r5, r0
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x7
	blo _02045288
	ldr r0, [sp, #0x0]
	strh r5, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_020452B0: .word 0x020F450C

	thumb_func_start FUN_020452B4
FUN_020452B4: ; 0x020452B4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	mov r5, #0x0
	ldr r2, _02045300 ; =0x020F450C
	strh r5, [r4, #0x0]
_020452E0:
	lsl r3, r5, #0x2
	ldrh r1, [r2, r3]
	cmp r0, r1
	bne _020452F0
	ldr r0, _02045304 ; =0x020F450E
	ldrh r0, [r0, r3]
	strh r0, [r4, #0x0]
	b _020452FA
_020452F0:
	add r1, r5, #0x1
	lsl r1, r1, #0x10
	lsr r5, r1, #0x10
	cmp r5, #0x7
	blo _020452E0
_020452FA:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_02045300: .word 0x020F450C
_02045304: .word 0x020F450E

	thumb_func_start FUN_02045308
FUN_02045308: ; 0x02045308
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	mov r4, #0x0
	ldr r0, [sp, #0x8]
	add r6, r4, #0x0
	strh r4, [r0, #0x0]
	ldr r0, [sp, #0x4]
	strh r4, [r0, #0x0]
_02045358:
	ldr r0, [r7, #0xc]
	lsl r5, r4, #0x2
	bl FUN_0206F158
	ldr r1, _02045394 ; =0x020F450C
	mov r2, #0x4
	ldrh r1, [r1, r5]
	bl FUN_0206EEF8
	add r0, r6, r0
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp, #0x0]
	cmp r6, r0
	blo _02045384
	ldr r0, _02045394 ; =0x020F450C
	ldrh r1, [r0, r5]
	ldr r0, [sp, #0x8]
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	strh r4, [r0, #0x0]
	b _0204538E
_02045384:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x7
	blo _02045358
_0204538E:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02045394: .word 0x020F450C

	thumb_func_start FUN_02045398
FUN_02045398: ; 0x02045398
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0204539C
FUN_0204539C: ; 0x0204539C
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020453A0
FUN_020453A0: ; 0x020453A0
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	ldr r1, _020453EC ; =0x020F4528
	lsl r2, r4, #0x2
	ldrh r1, [r1, r2]
	strh r1, [r6, #0x0]
	ldr r1, _020453F0 ; =0x020F452A
	ldrh r1, [r1, r2]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_020453EC: .word 0x020F4528
_020453F0: .word 0x020F452A

	thumb_func_start FUN_020453F4
FUN_020453F4: ; 0x020453F4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02024D64
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02045424
FUN_02045424: ; 0x02045424
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	bl FUN_02024D80
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02045438
FUN_02045438: ; 0x02045438
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034E20
	bl FUN_02055474
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02045468
FUN_02045468: ; 0x02045468
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034E20
	mov r1, #0x1
	bl FUN_02055488
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02045484
FUN_02045484: ; 0x02045484
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	cmp r4, #0x8
	blo _020454B6
	bl ErrorHandling
_020454B6:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r1, r4, #0x0
	bl FUN_020239D0
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020454CC
FUN_020454CC: ; 0x020454CC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	cmp r4, #0x8
	blo _020454EA
	bl ErrorHandling
_020454EA:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r1, r4, #0x0
	bl FUN_020239E4
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02045500
FUN_02045500: ; 0x02045500
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ECE0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204552C
FUN_0204552C: ; 0x0204552C
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	mov r4, #0x0
	ldr r7, _02045578 ; =0x020F4574
	str r0, [sp, #0x0]
	add r5, r4, #0x0
_02045548:
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	ldrb r1, [r7, r4]
	bl FUN_020239D0
	cmp r0, #0x1
	bne _02045564
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_02045564:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x8
	blo _02045548
	ldr r0, [sp, #0x0]
	strh r5, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02045578: .word 0x020F4574

	thumb_func_start FUN_0204557C
FUN_0204557C: ; 0x0204557C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ECD4
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02045590
FUN_02045590: ; 0x02045590
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED3C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020455BC
FUN_020455BC: ; 0x020455BC
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED1C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_020455D0
FUN_020455D0: ; 0x020455D0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED2C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_020455E4
FUN_020455E4: ; 0x020455E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED6C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02045610
FUN_02045610: ; 0x02045610
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED4C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02045624
FUN_02045624: ; 0x02045624
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED5C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02045638
FUN_02045638: ; 0x02045638
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED0C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02045664
FUN_02045664: ; 0x02045664
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ECFC
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02045678
FUN_02045678: ; 0x02045678
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	ldr r2, [r5, #0x8]
	add r4, r0, #0x0
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	beq _020456A6
	cmp r1, #0x1
	beq _0204569E
	cmp r1, #0x2
	beq _020456AE
	b _020456CC
_0204569E:
	mov r1, #0x1
	bl FUN_0205F264
	b _020456D0
_020456A6:
	mov r1, #0x0
	bl FUN_0205F264
	b _020456D0
_020456AE:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0205F264
	strh r0, [r5, #0x0]
	b _020456D0
_020456CC:
	bl ErrorHandling
_020456D0:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_020456D4
FUN_020456D4: ; 0x020456D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	ldr r2, [r5, #0x8]
	add r4, r0, #0x0
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	beq _02045700
	cmp r1, #0x1
	beq _020456FA
	cmp r1, #0x2
	beq _02045706
	b _02045722
_020456FA:
	bl FUN_0205F274
	b _02045726
_02045700:
	bl FUN_0205F284
	b _02045726
_02045706:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F294
	strh r0, [r5, #0x0]
	b _02045726
_02045722:
	bl ErrorHandling
_02045726:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204572C
FUN_0204572C: ; 0x0204572C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	ldr r2, [r5, #0x8]
	add r4, r0, #0x0
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	beq _02045758
	cmp r1, #0x1
	beq _02045752
	cmp r1, #0x2
	beq _0204575E
	b _0204577A
_02045752:
	bl FUN_0205F2A4
	b _0204577E
_02045758:
	bl FUN_0205F2B4
	b _0204577E
_0204575E:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F2C4
	strh r0, [r5, #0x0]
	b _0204577E
_0204577A:
	bl ErrorHandling
_0204577E:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02045784
FUN_02045784: ; 0x02045784
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r1, r6, #0x0
	add r2, r7, #0x0
	mov r3, #0x4
	bl FUN_0206ED38
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_020457DC
FUN_020457DC: ; 0x020457DC
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r1, r6, #0x0
	add r2, r7, #0x0
	mov r3, #0x4
	bl FUN_0206EDD4
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02045834
FUN_02045834: ; 0x02045834
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r1, r6, #0x0
	add r2, r7, #0x0
	mov r3, #0x4
	bl FUN_0206ED24
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0204588C
FUN_0204588C: ; 0x0204588C
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r1, r6, #0x0
	add r2, r7, #0x0
	mov r3, #0xb
	bl FUN_0206EE50
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_020458E4
FUN_020458E4: ; 0x020458E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02054CB0
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02045918
FUN_02045918: ; 0x02045918
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0xb
	bl FUN_0206E7B8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02045950
FUN_02045950: ; 0x02045950
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02045954
FUN_02045954: ; 0x02045954
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02045958
FUN_02045958: ; 0x02045958
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r5, [r1, #0xc]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02026CC4
	add r1, r6, #0x0
	bl FUN_02025D6C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020459AC
FUN_020459AC: ; 0x020459AC
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020459E8
FUN_020459E8: ; 0x020459E8
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r5, [r1, #0xc]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02026CC4
	add r1, r6, #0x0
	bl FUN_02025D94
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02045A3C
FUN_02045A3C: ; 0x02045A3C
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02045A78
FUN_02045A78: ; 0x02045A78
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r5, [r1, #0xc]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02026CC4
	add r1, r6, #0x0
	bl FUN_02026298
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02045ACC
FUN_02045ACC: ; 0x02045ACC
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02045B08
FUN_02045B08: ; 0x02045B08
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02045B44
FUN_02045B44: ; 0x02045B44
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02045B80
FUN_02045B80: ; 0x02045B80
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r0, r4, #0x0
	bl FUN_02026CC4
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02045BC8
FUN_02045BC8: ; 0x02045BC8
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02045C04
FUN_02045C04: ; 0x02045C04
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02045C40
FUN_02045C40: ; 0x02045C40
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02045C7C
FUN_02045C7C: ; 0x02045C7C
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r5, [r1, #0xc]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02026CC4
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020260C4
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02045CD4
FUN_02045CD4: ; 0x02045CD4
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02045D10
FUN_02045D10: ; 0x02045D10
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02045D4C
FUN_02045D4C: ; 0x02045D4C
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02045D88
FUN_02045D88: ; 0x02045D88
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r1, r5, #0x0
	add r1, #0x80
	lsl r2, r4, #0x18
	add r6, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	lsr r2, r2, #0x18
	bl FUN_02037CF0
	str r0, [r6, #0x0]
	ldr r1, _02045DCC ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	nop
_02045DCC: .word FUN_0203BC04 

	thumb_func_start FUN_02045DD0
FUN_02045DD0: ; 0x02045DD0
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02045DFC
	bl ErrorHandling
_02045DFC:
	ldr r0, [r4, #0x0]
	bl FUN_02037D5C
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x4
	bne _02045E0E
	mov r0, #0xff
	strh r0, [r5, #0x0]
_02045E0E:
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02045E1C
FUN_02045E1C: ; 0x02045E1C
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02045E20
FUN_02045E20: ; 0x02045E20
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x20
	bl FUN_02088DF8
	add r5, r0, #0x0
	bl FUN_02088EF8
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02016A18
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02045E74
FUN_02045E74: ; 0x02045E74
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	add r7, r1, #0x0
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	str r2, [sp, #0x0]
	add r6, r3, #0x0
	bl FUN_02039438
	str r0, [sp, #0x4]
	mov r0, #0x20
	bl FUN_02088DD8
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	str r4, [r0, #0x0]
	ldr r0, [sp, #0x0]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r4, #0x8]
	str r6, [r4, #0xc]
	add r0, r5, #0x0
	strb r7, [r4, #0x15]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_02038864
	ldr r1, _02045EDC ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	add r0, r6, #0x0
	bl FUN_02016A18
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02045EDC: .word FUN_0203BC04 

	thumb_func_start FUN_02045EE0
FUN_02045EE0: ; 0x02045EE0
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_02045EE4
FUN_02045EE4: ; 0x02045EE4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_0206B9B0
	add r4, r0, #0x0
	mov r1, #0x20
	bl FUN_02088DF8
	add r3, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x1
	add r2, r4, #0x0
	bl FUN_02045E74
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_02045F24
FUN_02045F24: ; 0x02045F24
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	add r6, r0, #0x0
	mov r0, #0x20
	mov r1, #0x4
	bl FUN_02016998
	add r3, r0, #0x0
	ldr r0, _02045F80 ; =0x0000FFFF
	strh r4, [r3, #0x0]
	strh r0, [r3, #0x2]
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02045E74
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_02045F80: .word 0x0000FFFF

	thumb_func_start FUN_02045F84
FUN_02045F84: ; 0x02045F84
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02045F88
FUN_02045F88: ; 0x02045F88
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	ldr r4, [r0, #0x0]
	cmp r4, #0x0
	bne _02045FB2
	bl ErrorHandling
_02045FB2:
	ldrb r0, [r4, #0x16]
	cmp r0, #0x0
	bne _02045FBC
	mov r0, #0x0
	b _02045FBE
_02045FBC:
	mov r0, #0xff
_02045FBE:
	strh r0, [r5, #0x0]
	add r0, r4, #0x0
	bl FUN_02088DF0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02045FCC
FUN_02045FCC: ; 0x02045FCC
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	ldr r4, [r0, #0x0]
	cmp r4, #0x0
	bne _02045FF6
	bl ErrorHandling
_02045FF6:
	ldrb r0, [r4, #0x16]
	cmp r0, #0x0
	bne _02046000
	mov r0, #0x0
	b _02046002
_02046000:
	mov r0, #0xff
_02046002:
	strh r0, [r5, #0x0]
	add r0, r4, #0x0
	bl FUN_02088DF0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02046010
FUN_02046010: ; 0x02046010
	push {r3, lr}
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0204601C
FUN_0204601C: ; 0x0204601C
	push {r3, lr}
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02046028
FUN_02046028: ; 0x02046028
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0204602C
FUN_0204602C: ; 0x0204602C
	mov r0, #0x0
	bx lr
