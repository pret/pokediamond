	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02034E78
FUN_02034E78: ; 0x02034E78
	push {r3, lr}
	cmp r0, #0x0
	ble _02034E82
	cmp r0, #0x14
	bls _02034E88
_02034E82:
	bl ErrorHandling
	mov r0, #0x1
_02034E88:
	sub r0, r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_02034E8C
FUN_02034E8C: ; 0x02034E8C
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_02034E90
FUN_02034E90: ; 0x02034E90
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02034E78
	lsl r1, r0, #0x4
	ldr r0, _02034EB8 ; =0x020F222A
	ldrh r0, [r0, r1]
	str r0, [r4, #0x0]
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0x4]
	ldr r0, _02034EBC ; =0x020F222C
	ldrh r0, [r0, r1]
	str r0, [r4, #0x8]
	ldr r0, _02034EC0 ; =0x020F222E
	ldrh r0, [r0, r1]
	str r0, [r4, #0xc]
	mov r0, #0x1
	str r0, [r4, #0x10]
	pop {r4, pc}
	.balign 4
_02034EB8: .word 0x020F222A
_02034EBC: .word 0x020F222C
_02034EC0: .word 0x020F222E

	thumb_func_start FUN_02034EC4
FUN_02034EC4: ; 0x02034EC4
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02034E78
	lsl r1, r0, #0x4
	ldr r0, _02034EEC ; =0x020F2224
	ldrh r0, [r0, r1]
	str r0, [r4, #0x0]
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0x4]
	ldr r0, _02034EF0 ; =0x020F2226
	ldrh r0, [r0, r1]
	str r0, [r4, #0x8]
	ldr r0, _02034EF4 ; =0x020F2228
	ldrh r0, [r0, r1]
	str r0, [r4, #0xc]
	mov r0, #0x0
	str r0, [r4, #0x10]
	pop {r4, pc}
	.balign 4
_02034EEC: .word 0x020F2224
_02034EF0: .word 0x020F2226
_02034EF4: .word 0x020F2228

	thumb_func_start FUN_02034EF8
FUN_02034EF8: ; 0x02034EF8
	ldr r3, _02034F18 ; =0x020F2224
	mov r2, #0x0
_02034EFC:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	bne _02034F0C
	ldrb r1, [r3, #0xc]
	cmp r1, #0x0
	beq _02034F0C
	add r0, r2, #0x1
	bx lr
_02034F0C:
	add r2, r2, #0x1
	add r3, #0x10
	cmp r2, #0x14
	blo _02034EFC
	mov r0, #0x0
	bx lr
	.balign 4
_02034F18: .word 0x020F2224

	thumb_func_start FUN_02034F1C
FUN_02034F1C: ; 0x02034F1C
	ldr r3, _02034F3C ; =0x020F2224
	mov r2, #0x0
_02034F20:
	ldrh r1, [r3, #0x6]
	cmp r0, r1
	bne _02034F30
	ldrb r1, [r3, #0xc]
	cmp r1, #0x0
	beq _02034F30
	add r0, r2, #0x1
	bx lr
_02034F30:
	add r2, r2, #0x1
	add r3, #0x10
	cmp r2, #0x14
	blo _02034F20
	mov r0, #0x0
	bx lr
	.balign 4
_02034F3C: .word 0x020F2224

	thumb_func_start FUN_02034F40
FUN_02034F40: ; 0x02034F40
	push {r3-r6}
	asr r3, r1, #0x4
	lsr r3, r3, #0x1b
	add r3, r1, r3
	asr r1, r2, #0x4
	lsr r1, r1, #0x1b
	add r1, r2, r1
	mov r4, #0x0
	asr r2, r1, #0x5
	ldr r5, _02034F84 ; =0x020F2224
	asr r3, r3, #0x5
	add r1, r4, #0x0
_02034F58:
	ldrh r6, [r5, #0x6]
	cmp r0, r6
	bne _02034F76
	ldrh r6, [r5, #0x8]
	add r4, r1, #0x1
	lsr r6, r6, #0x5
	cmp r3, r6
	bne _02034F76
	ldrh r6, [r5, #0xa]
	lsr r6, r6, #0x5
	cmp r2, r6
	bne _02034F76
	add r0, r4, #0x0
	pop {r3-r6}
	bx lr
_02034F76:
	add r1, r1, #0x1
	add r5, #0x10
	cmp r1, #0x14
	blo _02034F58
	add r0, r4, #0x0
	pop {r3-r6}
	bx lr
	.balign 4
_02034F84: .word 0x020F2224

	thumb_func_start FUN_02034F88
FUN_02034F88: ; 0x02034F88
	push {r4, lr}
	ldr r3, _02034FB8 ; =0x020F2224
	mov r4, #0x0
_02034F8E:
	ldrh r2, [r3, #0x6]
	cmp r1, r2
	bne _02034FAE
	ldrb r2, [r3, #0xd]
	cmp r2, #0x0
	beq _02034FAE
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	ldr r2, _02034FBC ; =0x020F2232
	lsl r3, r4, #0x4
	ldrh r2, [r2, r3]
	mov r1, #0x1
	bl FUN_0205F2E4
	pop {r4, pc}
_02034FAE:
	add r4, r4, #0x1
	add r3, #0x10
	cmp r4, #0x14
	blo _02034F8E
	pop {r4, pc}
	.balign 4
_02034FB8: .word 0x020F2224
_02034FBC: .word 0x020F2232

	thumb_func_start FUN_02034FC0
FUN_02034FC0: ; 0x02034FC0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02034E78
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_020462AC
	ldr r2, _02034FE0 ; =0x020F2232
	lsl r3, r4, #0x4
	ldrh r2, [r2, r3]
	mov r1, #0x2
	bl FUN_0205F2E4
	pop {r3-r5, pc}
	.balign 4
_02034FE0: .word 0x020F2232
