	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020F6754
	.extern UNK_020F693C
	.extern UNK_020F6670
	.extern UNK_020F68EC
	.extern UNK_020F6964
	.extern UNK_020F66CC
	.extern UNK_020F6984
	.extern UNK_020F6724
	.extern UNK_020F69BC
	.extern UNK_020F6928
	.extern UNK_020F6900
	.extern UNK_020F68D8

	.text

	thumb_func_start FUN_02059F04
FUN_02059F04: ; 0x02059F04
	push {r4-r6, lr}
	add r6, r1, #0x0
	mov r1, #0x8
	add r5, r0, #0x0
	bl FUN_0205858C
	add r4, r0, #0x0
	mov r1, #0x0
	ldr r0, _02059F30 ; =UNK_020F693C
	mvn r1, r1
	bl FUN_0205AAB0
	strh r0, [r4, #0x2]
	add r0, r5, #0x0
	mov r1, #0x0
	str r6, [r4, #0x4]
	bl FUN_02058544
	add r0, r5, #0x0
	bl FUN_02058848
	pop {r4-r6, pc}
	.balign 4
_02059F30: .word UNK_020F693C

	thumb_func_start FUN_02059F34
FUN_02059F34: ; 0x02059F34
	ldr r3, _02059F3C ; =FUN_02059F04
	mov r1, #0x0
	bx r3
	nop
_02059F3C: .word FUN_02059F04

	thumb_func_start FUN_02059F40
FUN_02059F40: ; 0x02059F40
	ldr r3, _02059F48 ; =FUN_02059F04
	mov r1, #0x1
	bx r3
	nop
_02059F48: .word FUN_02059F04

	thumb_func_start FUN_02059F4C
FUN_02059F4C: ; 0x02059F4C
	ldr r3, _02059F54 ; =FUN_02059F04
	mov r1, #0x2
	bx r3
	nop
_02059F54: .word FUN_02059F04

	thumb_func_start FUN_02059F58
FUN_02059F58: ; 0x02059F58
	ldr r3, _02059F60 ; =FUN_02059F04
	mov r1, #0x3
	bx r3
	nop
_02059F60: .word FUN_02059F04

	thumb_func_start FUN_02059F64
FUN_02059F64: ; 0x02059F64
	ldr r3, _02059F6C ; =FUN_02059F04
	mov r1, #0x4
	bx r3
	nop
_02059F6C: .word FUN_02059F04

	thumb_func_start FUN_02059F70
FUN_02059F70: ; 0x02059F70
	ldr r3, _02059F78 ; =FUN_02059F04
	mov r1, #0x5
	bx r3
	nop
_02059F78: .word FUN_02059F04

	thumb_func_start FUN_02059F7C
FUN_02059F7C: ; 0x02059F7C
	ldr r3, _02059F84 ; =FUN_02059F04
	mov r1, #0x6
	bx r3
	nop
_02059F84: .word FUN_02059F04

	thumb_func_start FUN_02059F88
FUN_02059F88: ; 0x02059F88
	ldr r3, _02059F90 ; =FUN_02059F04
	mov r1, #0x7
	bx r3
	nop
_02059F90: .word FUN_02059F04

	thumb_func_start FUN_02059F94
FUN_02059F94: ; 0x02059F94
	ldr r3, _02059F9C ; =FUN_02059F04
	mov r1, #0x8
	bx r3
	nop
_02059F9C: .word FUN_02059F04

	thumb_func_start FUN_02059FA0
FUN_02059FA0: ; 0x02059FA0
	ldr r3, _02059FA8 ; =FUN_02059F04
	mov r1, #0x9
	bx r3
	nop
_02059FA8: .word FUN_02059F04

	thumb_func_start FUN_02059FAC
FUN_02059FAC: ; 0x02059FAC
	ldr r3, _02059FB4 ; =FUN_02059F04
	mov r1, #0xa
	bx r3
	nop
_02059FB4: .word FUN_02059F04

	thumb_func_start FUN_02059FB8
FUN_02059FB8: ; 0x02059FB8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020585B0
	add r4, r0, #0x0
	mov r2, #0x0
	ldr r1, [r4, #0x4]
	add r0, r5, #0x0
	mvn r2, r2
	bl FUN_0205ABEC
	mov r2, #0x0
	add r1, r0, #0x0
	mvn r2, r2
	cmp r1, r2
	beq _02059FE0
	add r0, r5, #0x0
	bl FUN_020584AC
	b _0205A010
_02059FE0:
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0205A010
	mov r0, #0x2
	ldrsh r1, [r4, r0]
	sub r1, r1, #0x1
	strh r1, [r4, #0x2]
	ldrsh r0, [r4, r0]
	cmp r0, #0x0
	bgt _0205A010
	ldr r0, _0205A018 ; =UNK_020F693C
	add r1, r2, #0x0
	bl FUN_0205AAB0
	strh r0, [r4, #0x2]
	mov r1, #0x0
	ldr r0, [r4, #0x4]
	mvn r1, r1
	bl FUN_0205AAD4
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020584AC
_0205A010:
	add r0, r5, #0x0
	bl FUN_02059C60
	pop {r3-r5, pc}
	.balign 4
_0205A018: .word UNK_020F693C

	thumb_func_start FUN_0205A01C
FUN_0205A01C: ; 0x0205A01C
	bx lr
	.balign 4

	thumb_func_start FUN_0205A020
FUN_0205A020: ; 0x0205A020
	push {r3, lr}
	mov r1, #0xc
	mov r2, #0xb
	mov r3, #0x0
	bl FUN_0205A050
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A030
FUN_0205A030: ; 0x0205A030
	push {r3, lr}
	mov r1, #0xc
	add r2, r1, #0x0
	mov r3, #0x0
	bl FUN_0205A050
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A040
FUN_0205A040: ; 0x0205A040
	push {r3, lr}
	mov r1, #0xc
	mov r2, #0xd
	mov r3, #0x0
	bl FUN_0205A050
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A050
FUN_0205A050: ; 0x0205A050
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r7, r3, #0x0
	mov r1, #0x10
	add r5, r0, #0x0
	add r6, r2, #0x0
	bl FUN_0205858C
	str r7, [r0, #0x4]
	str r4, [r0, #0x8]
	str r6, [r0, #0xc]
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r5, #0x0
	bl FUN_02058848
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0205A078
FUN_0205A078: ; 0x0205A078
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_020585B0
	add r4, r0, #0x0
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	cmp r0, #0x4
	bhi _0205A16E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205A096: ; jump table (using 16-bit offset)
	.short _0205A0A0 - _0205A096 - 2; case 0
	.short _0205A0CA - _0205A096 - 2; case 1
	.short _0205A0E8 - _0205A096 - 2; case 2
	.short _0205A0FE - _0205A096 - 2; case 3
	.short _0205A15A - _0205A096 - 2; case 4
_0205A0A0:
	add r0, r5, #0x0
	bl FUN_02058848
	add r0, r5, #0x0
	bl FUN_0205886C
	add r0, r5, #0x0
	bl FUN_020584C4
	mov r1, #0x0
	bl FUN_0205AFDC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205AE0C
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	add r0, r0, #0x1
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_0205A0CA:
	add r0, r5, #0x0
	bl FUN_0205B080
	cmp r0, #0x0
	beq _0205A16E
	mov r1, #0x0
	ldr r0, _0205A170 ; =UNK_020F693C
	mvn r1, r1
	bl FUN_0205AAB0
	strh r0, [r4, #0x2]
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	add r0, r0, #0x1
	strh r0, [r4, #0x0]
_0205A0E8:
	mov r0, #0x2
	ldrsh r1, [r4, r0]
	sub r1, r1, #0x1
	strh r1, [r4, #0x2]
	ldrsh r0, [r4, r0]
	cmp r0, #0x0
	bne _0205A16E
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	add r0, r0, #0x1
	strh r0, [r4, #0x0]
_0205A0FE:
	mov r1, #0x0
	ldr r0, [r4, #0xc]
	mvn r1, r1
	bl FUN_0205AAD4
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020584D8
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _0205A12A
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0205A270
	cmp r0, #0x0
	bne _0205A12A
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_0205A12A:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02059918
	cmp r0, #0x0
	beq _0205A13C
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_0205A13C:
	ldr r1, [r4, #0x8]
	add r0, r6, #0x0
	bl FUN_0205AFDC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205AE0C
	add r0, r5, #0x0
	bl FUN_0205883C
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	add r0, r0, #0x1
	strh r0, [r4, #0x0]
_0205A15A:
	add r0, r5, #0x0
	bl FUN_0205B080
	cmp r0, #0x0
	beq _0205A16E
	add r0, r5, #0x0
	bl FUN_02058848
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0205A16E:
	pop {r4-r6, pc}
	.balign 4
_0205A170: .word UNK_020F693C

	thumb_func_start FUN_0205A174
FUN_0205A174: ; 0x0205A174
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r4, r1, #0x0
	bl FUN_02058AFC
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_02058B0C
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_02058538
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_02058540
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	bl FUN_02058480
	cmp r0, #0xd
	bhi _0205A268
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205A1B0: ; jump table (using 16-bit offset)
	.short _0205A268 - _0205A1B0 - 2; case 0
	.short _0205A268 - _0205A1B0 - 2; case 1
	.short _0205A268 - _0205A1B0 - 2; case 2
	.short _0205A268 - _0205A1B0 - 2; case 3
	.short _0205A268 - _0205A1B0 - 2; case 4
	.short _0205A268 - _0205A1B0 - 2; case 5
	.short _0205A1CC - _0205A1B0 - 2; case 6
	.short _0205A1DE - _0205A1B0 - 2; case 7
	.short _0205A1F0 - _0205A1B0 - 2; case 8
	.short _0205A202 - _0205A1B0 - 2; case 9
	.short _0205A214 - _0205A1B0 - 2; case 10
	.short _0205A22A - _0205A1B0 - 2; case 11
	.short _0205A240 - _0205A1B0 - 2; case 12
	.short _0205A254 - _0205A1B0 - 2; case 13
_0205A1CC:
	sub r0, r6, r7
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x4]
	str r6, [r4, #0x8]
	sub r0, r5, r0
	str r0, [r4, #0x4]
	add sp, #0x8
	str r5, [r4, #0xc]
	pop {r3-r7, pc}
_0205A1DE:
	str r6, [r4, #0x0]
	add r0, r6, r7
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x4]
	add sp, #0x8
	sub r0, r5, r0
	str r0, [r4, #0x4]
	str r5, [r4, #0xc]
	pop {r3-r7, pc}
_0205A1F0:
	sub r0, r6, r7
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x4]
	str r6, [r4, #0x8]
	str r5, [r4, #0x4]
	add r0, r5, r0
	add sp, #0x8
	str r0, [r4, #0xc]
	pop {r3-r7, pc}
_0205A202:
	str r6, [r4, #0x0]
	add r0, r6, r7
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x4]
	str r5, [r4, #0x4]
	add r0, r5, r0
	add sp, #0x8
	str r0, [r4, #0xc]
	pop {r3-r7, pc}
_0205A214:
	sub r0, r6, r7
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x4]
	str r6, [r4, #0x8]
	sub r0, r5, r0
	str r0, [r4, #0x4]
	ldr r0, [sp, #0x4]
	add sp, #0x8
	add r0, r5, r0
	str r0, [r4, #0xc]
	pop {r3-r7, pc}
_0205A22A:
	str r6, [r4, #0x0]
	add r0, r6, r7
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x4]
	sub r0, r5, r0
	str r0, [r4, #0x4]
	ldr r0, [sp, #0x4]
	add sp, #0x8
	add r0, r5, r0
	str r0, [r4, #0xc]
	pop {r3-r7, pc}
_0205A240:
	sub r0, r6, r7
	str r0, [r4, #0x0]
	add r0, r6, r7
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x4]
	add sp, #0x8
	sub r0, r5, r0
	str r0, [r4, #0x4]
	str r5, [r4, #0xc]
	pop {r3-r7, pc}
_0205A254:
	sub r0, r6, r7
	str r0, [r4, #0x0]
	add r0, r6, r7
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x4]
	str r5, [r4, #0x4]
	add r0, r5, r0
	add sp, #0x8
	str r0, [r4, #0xc]
	pop {r3-r7, pc}
_0205A268:
	bl GF_AssertFail
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0205A270
FUN_0205A270: ; 0x0205A270
	push {r4-r6, lr}
	sub sp, #0x10
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r1, sp, #0x0
	bl FUN_0205A174
	add r0, r5, #0x0
	bl FUN_02058B2C
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02059BF4
	add r4, r4, r0
	add r0, r5, #0x0
	bl FUN_02058B4C
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02059C00
	add r1, r5, r0
	ldr r0, [sp, #0x0]
	cmp r0, r4
	bgt _0205A2AA
	ldr r0, [sp, #0x8]
	cmp r0, r4
	bge _0205A2B0
_0205A2AA:
	add sp, #0x10
	mov r0, #0x0
	pop {r4-r6, pc}
_0205A2B0:
	ldr r0, [sp, #0x4]
	cmp r0, r1
	bgt _0205A2BC
	ldr r0, [sp, #0xc]
	cmp r0, r1
	bge _0205A2C2
_0205A2BC:
	add sp, #0x10
	mov r0, #0x0
	pop {r4-r6, pc}
_0205A2C2:
	mov r0, #0x1
	add sp, #0x10
	pop {r4-r6, pc}

	thumb_func_start FUN_0205A2C8
FUN_0205A2C8: ; 0x0205A2C8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	mov r1, #0x8
	bl FUN_0205858C
	str r4, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r5, #0x0
	bl FUN_02058848
	add r0, r5, #0x0
	bl FUN_02059C60
	pop {r3-r5, pc}

	thumb_func_start FUN_0205A2EC
FUN_0205A2EC: ; 0x0205A2EC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020585B0
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0205A300
	cmp r0, #0x1
	pop {r3-r5, pc}
_0205A300:
	ldr r1, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_020584AC
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	pop {r3-r5, pc}

	thumb_func_start FUN_0205A310
FUN_0205A310: ; 0x0205A310
	ldr r3, _0205A318 ; =FUN_0205A2C8
	mov r1, #0x0
	bx r3
	nop
_0205A318: .word FUN_0205A2C8

	thumb_func_start FUN_0205A31C
FUN_0205A31C: ; 0x0205A31C
	ldr r3, _0205A324 ; =FUN_0205A2C8
	mov r1, #0x1
	bx r3
	nop
_0205A324: .word FUN_0205A2C8

	thumb_func_start FUN_0205A328
FUN_0205A328: ; 0x0205A328
	ldr r3, _0205A330 ; =FUN_0205A2C8
	mov r1, #0x2
	bx r3
	nop
_0205A330: .word FUN_0205A2C8

	thumb_func_start FUN_0205A334
FUN_0205A334: ; 0x0205A334
	ldr r3, _0205A33C ; =FUN_0205A2C8
	mov r1, #0x3
	bx r3
	nop
_0205A33C: .word FUN_0205A2C8

	thumb_func_start FUN_0205A340
FUN_0205A340: ; 0x0205A340
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	mov r1, #0x8
	bl FUN_0205858C
	strb r4, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r5, #0x0
	bl FUN_02058848
	add r0, r5, #0x0
	bl FUN_02059C60
	pop {r3-r5, pc}

	thumb_func_start FUN_0205A364
FUN_0205A364: ; 0x0205A364
	ldr r3, _0205A36C ; =FUN_0205A340
	mov r1, #0x2
	bx r3
	nop
_0205A36C: .word FUN_0205A340

	thumb_func_start FUN_0205A370
FUN_0205A370: ; 0x0205A370
	ldr r3, _0205A378 ; =FUN_0205A340
	mov r1, #0x3
	bx r3
	nop
_0205A378: .word FUN_0205A340

	thumb_func_start FUN_0205A37C
FUN_0205A37C: ; 0x0205A37C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020585B0
	ldr r6, _0205A39C ; =UNK_020F6754
	add r4, r0, #0x0
	mov r7, #0x2
_0205A38A:
	ldrsb r2, [r4, r7]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	ldr r2, [r6, r2]
	blx r2
	cmp r0, #0x1
	beq _0205A38A
	pop {r3-r7, pc}
	.balign 4
_0205A39C: .word UNK_020F6754

	thumb_func_start FUN_0205A3A0
FUN_0205A3A0: ; 0x0205A3A0
	push {r3-r5, lr}
	add r4, r1, #0x0
	mov r1, #0x26
	add r2, r1, #0x0
	sub r2, #0x27
	add r5, r0, #0x0
	bl FUN_0205ABEC
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	bne _0205A3BE
	add r0, r5, #0x0
	bl FUN_020584C4
_0205A3BE:
	mov r1, #0x0
	bl FUN_0205AFDC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205AE0C
	mov r0, #0x1
	strb r0, [r4, #0x2]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205A3D4
FUN_0205A3D4: ; 0x0205A3D4
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0205B080
	cmp r0, #0x0
	bne _0205A3E4
	mov r0, #0x0
	pop {r4, pc}
_0205A3E4:
	mov r0, #0x0
	str r0, [r4, #0x4]
	mov r0, #0x2
	strb r0, [r4, #0x2]
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0205A3F0
FUN_0205A3F0: ; 0x0205A3F0
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	beq _0205A414
	mov r1, #0x26
	add r2, r1, #0x0
	sub r2, #0x27
	bl FUN_0205ABEC
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _0205A414
	mov r0, #0x0
	strb r0, [r4, #0x2]
	mov r0, #0x1
	pop {r4, pc}
_0205A414:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	cmp r0, #0x18
	bge _0205A422
	mov r0, #0x0
	pop {r4, pc}
_0205A422:
	mov r0, #0x3
	strb r0, [r4, #0x2]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205A42C
FUN_0205A42C: ; 0x0205A42C
	push {r3-r7, lr}
	sub sp, #0x28
	ldr r3, _0205A4BC ; =UNK_020F68D8
	add r2, sp, #0x14
	add r7, r0, #0x0
	add r6, r1, #0x0
	ldmia r3!, {r0-r1}
	add r5, r2, #0x0
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	ldr r4, _0205A4C0 ; =UNK_020F68EC
	str r0, [r2, #0x0]
	add r3, sp, #0x0
	ldmia r4!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r3, #0x0]
	mov r0, #0x0
	ldrsb r0, [r6, r0]
	cmp r0, #0x2
	beq _0205A462
	add r5, r2, #0x0
_0205A462:
	add r0, r7, #0x0
	bl FUN_020584C4
	mov r4, #0x0
	ldr r2, [r5, #0x0]
	sub r1, r4, #0x1
	cmp r2, r1
	beq _0205A486
	add r1, r5, #0x0
	sub r2, r4, #0x1
_0205A476:
	ldr r3, [r1, #0x0]
	cmp r0, r3
	beq _0205A486
	add r1, r1, #0x4
	ldr r3, [r1, #0x0]
	add r4, r4, #0x1
	cmp r3, r2
	bne _0205A476
_0205A486:
	lsl r0, r4, #0x2
	ldr r1, [r5, r0]
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	bne _0205A496
	bl GF_AssertFail
_0205A496:
	add r4, r4, #0x1
	lsl r0, r4, #0x2
	ldr r1, [r5, r0]
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	bne _0205A4A6
	mov r4, #0x0
_0205A4A6:
	lsl r1, r4, #0x2
	ldr r1, [r5, r1]
	add r0, r7, #0x0
	bl FUN_020584AC
	mov r0, #0x0
	strb r0, [r6, #0x2]
	mov r0, #0x1
	add sp, #0x28
	pop {r3-r7, pc}
	nop
_0205A4BC: .word UNK_020F68D8
_0205A4C0: .word UNK_020F68EC

	thumb_func_start FUN_0205A4C4
FUN_0205A4C4: ; 0x0205A4C4
	ldr r3, _0205A4CC ; =FUN_0205A340
	mov r1, #0x3
	bx r3
	nop
_0205A4CC: .word FUN_0205A340

	thumb_func_start FUN_0205A4D0
FUN_0205A4D0: ; 0x0205A4D0
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020585B0
	ldr r6, _0205A4F0 ; =UNK_020F6724
	add r4, r0, #0x0
	mov r7, #0x2
_0205A4DE:
	ldrsb r2, [r4, r7]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	ldr r2, [r6, r2]
	blx r2
	cmp r0, #0x1
	beq _0205A4DE
	pop {r3-r7, pc}
	.balign 4
_0205A4F0: .word UNK_020F6724

	thumb_func_start FUN_0205A4F4
FUN_0205A4F4: ; 0x0205A4F4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020584C4
	mov r1, #0x0
	bl FUN_0205AFDC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205AE0C
	mov r0, #0x1
	strb r0, [r4, #0x2]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205A514
FUN_0205A514: ; 0x0205A514
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0205B080
	cmp r0, #0x0
	bne _0205A524
	mov r0, #0x0
	pop {r4, pc}
_0205A524:
	mov r0, #0x0
	str r0, [r4, #0x4]
	mov r0, #0x2
	strb r0, [r4, #0x2]
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0205A530
FUN_0205A530: ; 0x0205A530
	ldr r0, [r1, #0x4]
	add r0, r0, #0x1
	str r0, [r1, #0x4]
	cmp r0, #0x18
	bge _0205A53E
	mov r0, #0x0
	bx lr
_0205A53E:
	mov r0, #0x3
	strb r0, [r1, #0x2]
	mov r0, #0x1
	bx lr
	.balign 4

	thumb_func_start FUN_0205A548
FUN_0205A548: ; 0x0205A548
	push {r3-r7, lr}
	sub sp, #0x28
	ldr r3, _0205A5F4 ; =UNK_020F6900
	add r2, sp, #0x14
	add r7, r0, #0x0
	add r6, r1, #0x0
	ldmia r3!, {r0-r1}
	add r5, r2, #0x0
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	ldr r3, _0205A5F8 ; =UNK_020F6928
	str r0, [r2, #0x0]
	add r2, sp, #0x0
	ldmia r3!, {r0-r1}
	add r4, r2, #0x0
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	mov r0, #0x0
	ldrsb r0, [r6, r0]
	cmp r0, #0x2
	beq _0205A57E
	add r5, r4, #0x0
_0205A57E:
	add r0, r7, #0x0
	bl FUN_020584C4
	mov r4, #0x0
	ldr r2, [r5, #0x0]
	sub r1, r4, #0x1
	cmp r2, r1
	beq _0205A5A2
	add r1, r5, #0x0
	sub r2, r4, #0x1
_0205A592:
	ldr r3, [r1, #0x0]
	cmp r0, r3
	beq _0205A5A2
	add r1, r1, #0x4
	ldr r3, [r1, #0x0]
	add r4, r4, #0x1
	cmp r3, r2
	bne _0205A592
_0205A5A2:
	lsl r0, r4, #0x2
	ldr r1, [r5, r0]
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	bne _0205A5B2
	bl GF_AssertFail
_0205A5B2:
	add r4, r4, #0x1
	lsl r0, r4, #0x2
	ldr r1, [r5, r0]
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	bne _0205A5C2
	mov r4, #0x0
_0205A5C2:
	lsl r1, r4, #0x2
	ldr r1, [r5, r1]
	add r0, r7, #0x0
	bl FUN_020584AC
	add r0, r7, #0x0
	bl FUN_020584C4
	add r4, r0, #0x0
	add r0, r7, #0x0
	bl FUN_020584A0
	cmp r4, r0
	bne _0205A5E8
	mov r0, #0x0
	ldrsb r0, [r6, r0]
	bl FUN_02059E74
	strb r0, [r6, #0x0]
_0205A5E8:
	mov r0, #0x0
	strb r0, [r6, #0x2]
	mov r0, #0x1
	add sp, #0x28
	pop {r3-r7, pc}
	nop
_0205A5F4: .word UNK_020F6900
_0205A5F8: .word UNK_020F6928

	thumb_func_start FUN_0205A5FC
FUN_0205A5FC: ; 0x0205A5FC
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0x8
	bl FUN_0205858C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205ACE0
	cmp r0, #0x1
	bne _0205A61A
	add r0, r5, #0x0
	add r1, r4, #0x4
	bl FUN_0205ACF4
_0205A61A:
	pop {r3-r5, pc}

	thumb_func_start FUN_0205A61C
FUN_0205A61C: ; 0x0205A61C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020585B0
	ldr r6, _0205A63C ; =UNK_020F66CC
	add r4, r0, #0x0
	mov r7, #0x0
_0205A62A:
	ldrsh r2, [r4, r7]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	ldr r2, [r6, r2]
	blx r2
	cmp r0, #0x1
	beq _0205A62A
	pop {r3-r7, pc}
	.balign 4
_0205A63C: .word UNK_020F66CC

	thumb_func_start FUN_0205A640
FUN_0205A640: ; 0x0205A640
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020584A0
	mov r1, #0x2
	ldrsh r1, [r4, r1]
	add r6, r0, #0x0
	cmp r1, #0x1
	bne _0205A65A
	bl FUN_02059E74
	add r6, r0, #0x0
_0205A65A:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_0205ACE0
	cmp r0, #0x0
	bne _0205A674
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020584AC
_0205A674:
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0205A67C
FUN_0205A67C: ; 0x0205A67C
	push {r3-r7, lr}
	add r4, r1, #0x0
	mov r1, #0x2
	ldrsh r1, [r4, r1]
	add r5, r0, #0x0
	cmp r1, #0x0
	beq _0205A6DA
	bl FUN_02058AFC
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B0C
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B2C
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02058B4C
	ldr r1, [sp, #0x0]
	cmp r6, r1
	bne _0205A6DA
	cmp r7, r0
	bne _0205A6DA
	add r0, r5, #0x0
	bl FUN_020584D4
	bl FUN_02059E74
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_0205ACE0
	cmp r0, #0x0
	bne _0205A6D6
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020584AC
_0205A6D6:
	mov r0, #0x0
	strh r0, [r4, #0x2]
_0205A6DA:
	add r0, r5, #0x0
	bl FUN_020584D4
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02059918
	mov r1, #0x1
	add r2, r0, #0x0
	tst r2, r1
	beq _0205A704
	add r0, r6, #0x0
	strh r1, [r4, #0x2]
	bl FUN_02059E74
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02059918
_0205A704:
	mov r1, #0xc
	cmp r0, #0x0
	beq _0205A70C
	mov r1, #0x20
_0205A70C:
	add r0, r6, #0x0
	bl FUN_0205AFDC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205AE0C
	add r0, r5, #0x0
	bl FUN_0205ACE0
	cmp r0, #0x1
	bne _0205A72C
	add r0, r5, #0x0
	add r1, r4, #0x4
	bl FUN_0205AD0C
_0205A72C:
	add r0, r5, #0x0
	bl FUN_0205883C
	mov r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0205A73C
FUN_0205A73C: ; 0x0205A73C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0205B080
	cmp r0, #0x1
	bne _0205A766
	add r0, r5, #0x0
	bl FUN_02058848
	add r0, r5, #0x0
	bl FUN_0205ACE0
	cmp r0, #0x1
	bne _0205A762
	add r0, r5, #0x0
	add r1, r4, #0x4
	bl FUN_0205AD88
_0205A762:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0205A766:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205A76C
FUN_0205A76C: ; 0x0205A76C
	push {r3-r7, lr}
	add r6, r1, #0x0
	mov r1, #0x10
	add r5, r0, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	bl FUN_0205858C
	add r4, r0, #0x0
	strh r6, [r4, #0x4]
	ldr r0, [sp, #0x0]
	strh r7, [r4, #0x6]
	str r0, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_0205ACE0
	cmp r0, #0x1
	bne _0205A79A
	add r4, #0xc
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205ACF4
_0205A79A:
	pop {r3-r7, pc}

	thumb_func_start FUN_0205A79C
FUN_0205A79C: ; 0x0205A79C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0xe
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A7AC
FUN_0205A7AC: ; 0x0205A7AC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0xf
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A7BC
FUN_0205A7BC: ; 0x0205A7BC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x10
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A7CC
FUN_0205A7CC: ; 0x0205A7CC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x11
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A7DC
FUN_0205A7DC: ; 0x0205A7DC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x12
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A7EC
FUN_0205A7EC: ; 0x0205A7EC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x13
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A7FC
FUN_0205A7FC: ; 0x0205A7FC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x14
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A80C
FUN_0205A80C: ; 0x0205A80C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x15
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A81C
FUN_0205A81C: ; 0x0205A81C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x16
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A82C
FUN_0205A82C: ; 0x0205A82C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x17
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A83C
FUN_0205A83C: ; 0x0205A83C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x18
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A84C
FUN_0205A84C: ; 0x0205A84C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x19
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A85C
FUN_0205A85C: ; 0x0205A85C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x1a
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A86C
FUN_0205A86C: ; 0x0205A86C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x1b
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A87C
FUN_0205A87C: ; 0x0205A87C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x1c
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A88C
FUN_0205A88C: ; 0x0205A88C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x1d
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A89C
FUN_0205A89C: ; 0x0205A89C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x1e
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A8AC
FUN_0205A8AC: ; 0x0205A8AC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x1f
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A8BC
FUN_0205A8BC: ; 0x0205A8BC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x20
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A8CC
FUN_0205A8CC: ; 0x0205A8CC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x21
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A8DC
FUN_0205A8DC: ; 0x0205A8DC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x22
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A8EC
FUN_0205A8EC: ; 0x0205A8EC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x23
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A8FC
FUN_0205A8FC: ; 0x0205A8FC
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x24
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A90C
FUN_0205A90C: ; 0x0205A90C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x25
	bl FUN_0205A76C
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205A91C
FUN_0205A91C: ; 0x0205A91C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020585B0
	ldr r6, _0205A93C ; =UNK_020F6670
	add r4, r0, #0x0
	mov r7, #0x0
_0205A92A:
	ldrsh r2, [r4, r7]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	ldr r2, [r6, r2]
	blx r2
	cmp r0, #0x1
	beq _0205A92A
	pop {r3-r7, pc}
	.balign 4
_0205A93C: .word UNK_020F6670

	thumb_func_start FUN_0205A940
FUN_0205A940: ; 0x0205A940
	push {r3-r7, lr}
	add r4, r1, #0x0
	mov r1, #0x2
	ldrsh r2, [r4, r1]
	mov r1, #0x4
	ldrsh r1, [r4, r1]
	add r5, r0, #0x0
	cmp r2, r1
	bne _0205A98C
	mov r1, #0x6
	ldrsh r1, [r4, r1]
	cmp r1, #0x0
	bne _0205A974
	bl FUN_02058AFC
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B2C
	cmp r6, r0
	bne _0205A98C
	mov r0, #0x2
	ldrsh r0, [r4, r0]
	add r0, r0, #0x1
	strh r0, [r4, #0x2]
	b _0205A98C
_0205A974:
	bl FUN_02058B0C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B4C
	cmp r6, r0
	bne _0205A98C
	mov r0, #0x2
	ldrsh r0, [r4, r0]
	add r0, r0, #0x1
	strh r0, [r4, #0x2]
_0205A98C:
	mov r0, #0x2
	ldrsh r0, [r4, r0]
	cmp r0, #0x3
	bne _0205A9C0
	add r0, r5, #0x0
	bl FUN_02058AFC
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B0C
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B2C
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02058B4C
	ldr r1, [sp, #0x0]
	cmp r6, r1
	bne _0205A9C0
	cmp r7, r0
	bne _0205A9C0
	mov r0, #0x0
	strh r0, [r4, #0x2]
_0205A9C0:
	ldr r0, [r4, #0x8]
	bl FUN_0205AAFC
	add r7, r0, #0x0
	mov r0, #0x2
	ldrsh r0, [r4, r0]
	lsl r0, r0, #0x2
	ldr r6, [r7, r0]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_0205ACE0
	cmp r0, #0x0
	bne _0205A9EA
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020584AC
_0205A9EA:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02059918
	mov r1, #0x1
	tst r1, r0
	beq _0205AA28
	mov r0, #0x2
	ldrsh r1, [r4, r0]
	add r1, r1, #0x1
	strh r1, [r4, #0x2]
	ldrsh r0, [r4, r0]
	lsl r0, r0, #0x2
	ldr r6, [r7, r0]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_0205ACE0
	cmp r0, #0x0
	bne _0205AA20
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020584AC
_0205AA20:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02059918
_0205AA28:
	mov r1, #0xc
	cmp r0, #0x0
	beq _0205AA30
	mov r1, #0x20
_0205AA30:
	add r0, r6, #0x0
	bl FUN_0205AFDC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205AE0C
	add r0, r5, #0x0
	bl FUN_0205ACE0
	cmp r0, #0x1
	bne _0205AA52
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0xc
	bl FUN_0205AD0C
_0205AA52:
	add r0, r5, #0x0
	bl FUN_0205883C
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0205AA60
FUN_0205AA60: ; 0x0205AA60
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0205B080
	cmp r0, #0x1
	bne _0205AA8C
	add r0, r5, #0x0
	bl FUN_02058848
	add r0, r5, #0x0
	bl FUN_0205ACE0
	cmp r0, #0x1
	bne _0205AA88
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0xc
	bl FUN_0205AD88
_0205AA88:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0205AA8C:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0205AA90
FUN_0205AA90: ; 0x0205AA90
	push {r4, lr}
	ldr r2, [r0, #0x0]
	mov r4, #0x0
	cmp r1, r2
	beq _0205AAA4
_0205AA9A:
	add r0, r0, #0x4
	ldr r2, [r0, #0x0]
	add r4, r4, #0x1
	cmp r1, r2
	bne _0205AA9A
_0205AAA4:
	cmp r4, #0x0
	bne _0205AAAC
	bl GF_AssertFail
_0205AAAC:
	add r0, r4, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0205AAB0
FUN_0205AAB0: ; 0x0205AAB0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl LCRandom
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205AA90
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl _s32_div_f
	lsl r0, r1, #0x2
	ldr r0, [r5, r0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0205AAD4
FUN_0205AAD4: ; 0x0205AAD4
	push {r4-r6, lr}
	add r5, r1, #0x0
	bl FUN_0205AAFC
	add r4, r0, #0x0
	bl LCRandom
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0205AA90
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl _s32_div_f
	lsl r0, r1, #0x2
	ldr r0, [r4, r0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0205AAFC
FUN_0205AAFC: ; 0x0205AAFC
	push {r3, lr}
	ldr r1, _0205AB1C ; =UNK_020F69BC
	mov r2, #0x0
_0205AB02:
	cmp r2, r0
	bne _0205AB0A
	ldr r0, [r1, #0x4]
	pop {r3, pc}
_0205AB0A:
	add r1, #0x8
	ldr r2, [r1, #0x0]
	cmp r2, #0x27
	bne _0205AB02
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}
	nop
_0205AB1C: .word UNK_020F69BC

	thumb_func_start FUN_0205AB20
FUN_0205AB20: ; 0x0205AB20
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02058488
	cmp r0, #0x1
	beq _0205AB36
	cmp r0, #0x2
	beq _0205AB36
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0205AB36:
	add r0, r5, #0x0
	bl FUN_02058738
	bl FUN_02055698
	add r6, r0, #0x0
	bl FUN_02057124
	cmp r0, #0x0
	bne _0205AB50
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0205AB50:
	add r0, r5, #0x0
	mov r4, #0x0
	bl FUN_02058480
	ldr r1, _0205ABE8 ; =UNK_020F6984
_0205AB5A:
	lsl r2, r4, #0x2
	ldr r2, [r1, r2]
	add r4, r4, #0x1
	cmp r2, r0
	beq _0205AB68
	cmp r2, #0xff
	bne _0205AB5A
_0205AB68:
	cmp r0, r2
	beq _0205AB72
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0205AB72:
	add r0, r6, #0x0
	bl FUN_020553A0
	bl FUN_02058BE4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058BE4
	cmp r4, r0
	beq _0205AB8E
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0205AB8E:
	add r0, r6, #0x0
	bl GetPlayerXCoord
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0205532C
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02058B2C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B4C
	add r3, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r5, [sp, #0x0]
	sub r2, r6, r0
	add r1, r6, r0
	sub r5, r3, r5
	add r0, r3, r0
	cmp r5, r4
	bgt _0205ABE2
	cmp r0, r4
	blt _0205ABE2
	cmp r2, r7
	bgt _0205ABE2
	cmp r1, r7
	blt _0205ABE2
	add r1, r3, #0x0
	add r0, r6, #0x0
	add r2, r7, #0x0
	add r3, r4, #0x0
	bl FUN_02059E80
	pop {r3-r7, pc}
_0205ABE2:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
	.balign 4
_0205ABE8: .word UNK_020F6984

	thumb_func_start FUN_0205ABEC
FUN_0205ABEC: ; 0x0205ABEC
	push {r4-r7, lr}
	sub sp, #0x14
	str r0, [sp, #0x0]
	add r4, r2, #0x0
	add r0, r1, #0x0
	bl FUN_0205AAFC
	add r1, r4, #0x0
	add r5, r0, #0x0
	bl FUN_0205AA90
	add r4, r0, #0x0
	cmp r4, #0x1
	bne _0205AC10
	mov r0, #0x0
	add sp, #0x14
	mvn r0, r0
	pop {r4-r7, pc}
_0205AC10:
	ldr r0, [sp, #0x0]
	bl FUN_0205AB20
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _0205ACDA
	mov r2, #0x0
	add r3, r5, #0x0
_0205AC22:
	ldr r1, [r3, #0x0]
	cmp r0, r1
	beq _0205ACDA
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, r4
	blt _0205AC22
	mov r7, #0x0
	mvn r7, r7
	ldr r0, [sp, #0x0]
	add r6, r7, #0x0
	bl FUN_02058B2C
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x0]
	bl FUN_02058B4C
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	bl FUN_02058738
	bl FUN_02055698
	str r0, [sp, #0xc]
	bl GetPlayerXCoord
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	bl FUN_0205532C
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0x10]
	cmp r2, r1
	ble _0205AC6A
	mov r7, #0x2
	b _0205AC70
_0205AC6A:
	cmp r2, r1
	bge _0205AC70
	mov r7, #0x3
_0205AC70:
	ldr r1, [sp, #0x4]
	cmp r1, r0
	ble _0205AC7A
	mov r6, #0x0
	b _0205AC80
_0205AC7A:
	cmp r1, r0
	bge _0205AC80
	mov r6, #0x1
_0205AC80:
	mov r0, #0x0
	sub r1, r0, #0x1
	cmp r7, r1
	bne _0205AC9E
_0205AC88:
	ldr r1, [r5, #0x0]
	cmp r6, r1
	bne _0205AC94
	add sp, #0x14
	add r0, r6, #0x0
	pop {r4-r7, pc}
_0205AC94:
	add r0, r0, #0x1
	add r5, r5, #0x4
	cmp r0, r4
	blt _0205AC88
	b _0205ACD6
_0205AC9E:
	cmp r6, r1
	bne _0205ACB8
_0205ACA2:
	ldr r1, [r5, #0x0]
	cmp r7, r1
	bne _0205ACAE
	add sp, #0x14
	add r0, r7, #0x0
	pop {r4-r7, pc}
_0205ACAE:
	add r0, r0, #0x1
	add r5, r5, #0x4
	cmp r0, r4
	blt _0205ACA2
	b _0205ACD6
_0205ACB8:
	ldr r1, [r5, #0x0]
	cmp r7, r1
	bne _0205ACC4
	add sp, #0x14
	add r0, r7, #0x0
	pop {r4-r7, pc}
_0205ACC4:
	cmp r6, r1
	bne _0205ACCE
	add sp, #0x14
	add r0, r6, #0x0
	pop {r4-r7, pc}
_0205ACCE:
	add r0, r0, #0x1
	add r5, r5, #0x4
	cmp r0, r4
	blt _0205ACB8
_0205ACD6:
	mov r0, #0x0
	mvn r0, r0
_0205ACDA:
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0205ACE0
FUN_0205ACE0: ; 0x0205ACE0
	push {r3, lr}
	bl FUN_02058488
	sub r0, r0, #0x7
	cmp r0, #0x1
	bhi _0205ACF0
	mov r0, #0x1
	pop {r3, pc}
_0205ACF0:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0205ACF4
FUN_0205ACF4: ; 0x0205ACF4
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02058488
	cmp r0, #0x7
	bne _0205AD06
	mov r0, #0x0
	strb r0, [r4, #0x1]
	pop {r4, pc}
_0205AD06:
	mov r0, #0x1
	strb r0, [r4, #0x1]
	pop {r4, pc}

	thumb_func_start FUN_0205AD0C
FUN_0205AD0C: ; 0x0205AD0C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	bl FUN_020584C4
	mov r4, #0x0
	add r6, r0, #0x0
	add r1, r4, #0x0
	ldr r0, _0205AD84 ; =UNK_020F6964
	mov r2, #0x1
	b _0205AD26
_0205AD22:
	add r1, r1, #0x4
	add r4, r4, #0x1
_0205AD26:
	cmp r4, #0x4
	bge _0205AD36
	ldrsb r3, [r5, r2]
	lsl r3, r3, #0x4
	add r3, r0, r3
	ldr r3, [r1, r3]
	cmp r6, r3
	bne _0205AD22
_0205AD36:
	cmp r4, #0x4
	blt _0205AD3E
	bl GF_AssertFail
_0205AD3E:
	add r0, r4, #0x1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	strb r6, [r5, #0x0]
	mov r0, #0x1
	add r1, r2, r1
	ldrsb r0, [r5, r0]
	lsl r1, r1, #0x2
	lsl r2, r0, #0x4
	ldr r0, _0205AD84 ; =UNK_020F6964
	add r0, r0, r2
	ldr r4, [r1, r0]
	add r0, r7, #0x0
	mov r1, #0x80
	bl FUN_02058424
	cmp r0, #0x0
	beq _0205AD6C
	mov r0, #0x1
	b _0205AD6E
_0205AD6C:
	mov r0, #0x0
_0205AD6E:
	strb r0, [r5, #0x2]
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_020584AC
	add r0, r7, #0x0
	mov r1, #0x80
	bl FUN_02058410
	pop {r3-r7, pc}
	nop
_0205AD84: .word UNK_020F6964

	thumb_func_start FUN_0205AD88
FUN_0205AD88: ; 0x0205AD88
	push {r3, lr}
	ldrb r1, [r1, #0x2]
	cmp r1, #0x0
	bne _0205AD96
	mov r1, #0x80
	bl FUN_02058418
_0205AD96:
	pop {r3, pc}
