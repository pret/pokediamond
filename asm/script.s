    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start InitScriptHandler
InitScriptHandler: ; 0x02038B1C
	push {r3-r4}
	mov r3, #0x0
	strb r3, [r0, #0x1]
	str r3, [r0, #0x8]
	strb r3, [r0, #0x0]
	str r3, [r0, #0x4]
	str r1, [r0, #0x5c]
	str r2, [r0, #0x60]
	add r1, r0, #0x0
	add r4, r3, #0x0
_02038B30:
	add r3, r3, #0x1
	str r4, [r1, #0x64]
	add r1, r1, #0x4
	cmp r3, #0x4
	blo _02038B30
	add r2, r0, #0x0
	mov r1, #0x0
_02038B3E:
	add r4, r4, #0x1
	str r1, [r2, #0xc]
	add r2, r2, #0x4
	cmp r4, #0x14
	blo _02038B3E
	str r1, [r0, #0x74]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_02038B50
FUN_02038B50: ; 0x02038B50
	str r1, [r0, #0x8]
	mov r1, #0x1
	strb r1, [r0, #0x1]
	add r0, r1, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02038B5C
FUN_02038B5C: ; 0x02038B5C
	mov r2, #0x2
	strb r2, [r0, #0x1]
	str r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02038B64
FUN_02038B64: ; 0x02038B64
	mov r1, #0x0
	strb r1, [r0, #0x1]
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02038B6C
FUN_02038B6C: ; 0x02038B6C
	str r1, [r0, #0x74]
	bx lr

	thumb_func_start ScriptHandler_Main
ScriptHandler_Main: ; 0x02038B70
	push {r4, lr}
	add r4, r0, #0x0
	ldrb r1, [r4, #0x1]
	cmp r1, #0x0
	bne _02038B7E
	mov r0, #0x0
	pop {r4, pc}
_02038B7E:
	beq _02038B8A
	cmp r1, #0x1
	beq _02038BA6
	cmp r1, #0x2
	beq _02038B8E
	b _02038BD8
_02038B8A:
	mov r0, #0x0
	pop {r4, pc}
_02038B8E:
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	beq _02038BA2
	blx r1
	cmp r0, #0x1
	bne _02038B9E
	mov r0, #0x1
	strb r0, [r4, #0x1]
_02038B9E:
	mov r0, #0x1
	pop {r4, pc}
_02038BA2:
	mov r0, #0x1
	strb r0, [r4, #0x1]
_02038BA6:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	bne _02038BB2
	mov r0, #0x0
	strb r0, [r4, #0x1]
	pop {r4, pc}
_02038BB2:
	add r0, r4, #0x0
	bl FUN_02038C30
	add r1, r0, #0x0
	ldr r0, [r4, #0x60]
	cmp r1, r0
	blo _02038BCA
	bl ErrorHandling
	mov r0, #0x0
	strb r0, [r4, #0x1]
	pop {r4, pc}
_02038BCA:
	ldr r2, [r4, #0x5c]
	lsl r1, r1, #0x2
	ldr r1, [r2, r1]
	add r0, r4, #0x0
	blx r1
	cmp r0, #0x1
	bne _02038BA6
_02038BD8:
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_02038BDC
FUN_02038BDC: ; 0x02038BDC
	ldrb r3, [r0, #0x0]
	add r2, r3, #0x1
	cmp r2, #0x14
	blt _02038BE8
	mov r0, #0x1
	bx lr
_02038BE8:
	lsl r2, r3, #0x2
	add r2, r0, r2
	str r1, [r2, #0xc]
	ldrb r1, [r0, #0x0]
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02038BF8
FUN_02038BF8: ; 0x02038BF8
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	bne _02038C02
	mov r0, #0x0
	bx lr
_02038C02:
	sub r1, r1, #0x1
	strb r1, [r0, #0x0]
	ldrb r1, [r0, #0x0]
	lsl r1, r1, #0x2
	add r0, r0, r1
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_02038C10
FUN_02038C10: ; 0x02038C10
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02038C14
FUN_02038C14: ; 0x02038C14
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x8]
	bl FUN_02038BDC
	str r4, [r5, #0x8]
	pop {r3-r5, pc}

	thumb_func_start FUN_02038C24
FUN_02038C24: ; 0x02038C24
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02038BF8
	str r0, [r4, #0x8]
	pop {r4, pc}

	thumb_func_start FUN_02038C30
FUN_02038C30: ; 0x02038C30
	ldr r1, [r0, #0x8]
	add r3, r1, #0x1
	str r3, [r0, #0x8]
	ldrb r2, [r1, #0x0]
	add r1, r3, #0x1
	str r1, [r0, #0x8]
	ldrb r0, [r3, #0x0]
	lsl r0, r0, #0x8
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr

	thumb_func_start FUN_02038C48
FUN_02038C48: ; 0x02038C48
	push {r4-r5}
	ldr r1, [r0, #0x8]
	add r2, r1, #0x1
	str r2, [r0, #0x8]
	ldrb r3, [r1, #0x0]
	add r1, r2, #0x1
	add r5, r1, #0x1
	str r1, [r0, #0x8]
	ldrb r2, [r2, #0x0]
	add r4, r5, #0x1
	str r5, [r0, #0x8]
	ldrb r1, [r1, #0x0]
	str r4, [r0, #0x8]
	ldrb r0, [r5, #0x0]
	mov r4, #0x0
	add r0, r4, r0
	lsl r0, r0, #0x8
	add r0, r0, r1
	lsl r0, r0, #0x8
	add r0, r0, r2
	lsl r0, r0, #0x8
	add r0, r0, r3
	pop {r4-r5}
	bx lr
