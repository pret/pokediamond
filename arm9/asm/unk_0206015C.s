    .include "asm/macros.inc"
    .include "global.inc"

	.extern gUnknown21C48B8

	.text

	thumb_func_start FUN_0206015C
FUN_0206015C: ; 0x0206015C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0xb
	mov r1, #0x10
	bl FUN_020169D8
	add r4, r0, #0x0
	mov r0, #0xb
	bl MOD06_02244DB0
	str r0, [r4, #0x0]
	mov r0, #0xb
	add r1, r5, #0x0
	bl MOD06_02245114
	str r0, [r4, #0x4]
	mov r0, #0x0
	strb r0, [r4, #0xc]
	strb r0, [r4, #0xd]
	ldr r0, [r5, #0x10]
	ldr r1, _02060190 ; =FUN_02060194
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r3-r5, pc}
	nop
_02060190: .word FUN_02060194

	thumb_func_start FUN_02060194
FUN_02060194: ; 0x02060194
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldrb r0, [r4, #0xc]
	cmp r0, #0x8
	bls _020601B0
	b _02060332
_020601B0:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020601BC: ; jump table (using 16-bit offset)
	.short _020601CE - _020601BC - 2; case 0
	.short _020601F2 - _020601BC - 2; case 1
	.short _020601FE - _020601BC - 2; case 2
	.short _02060226 - _020601BC - 2; case 3
	.short _02060232 - _020601BC - 2; case 4
	.short _020602A2 - _020601BC - 2; case 5
	.short _020602F0 - _020601BC - 2; case 6
	.short _020602FC - _020601BC - 2; case 7
	.short _02060312 - _020601BC - 2; case 8
_020601CE:
	add r0, r6, #0x0
	mov r1, #0x1
	bl FUN_0206367C
	ldrb r0, [r4, #0xd]
	ldr r1, [r4, #0x4]
	bl MOD06_02245198
	ldr r0, [r4, #0x4]
	bl MOD06_022451F0
	str r0, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_0204AFC8
	mov r0, #0x1
	strb r0, [r4, #0xc]
	b _02060332
_020601F2:
	add r0, r5, #0x0
	bl FUN_0204AF3C
	mov r0, #0x2
	strb r0, [r4, #0xc]
	b _02060332
_020601FE:
	ldr r0, [r6, #0xc]
	bl FUN_020462AC
	ldrb r1, [r4, #0xd]
	cmp r1, #0x0
	bne _02060210
	bl FUN_0205F1C4
	b _02060218
_02060210:
	cmp r1, #0x5
	bne _02060218
	bl FUN_0205F1D4
_02060218:
	ldr r1, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_02049160
	mov r0, #0x3
	strb r0, [r4, #0xc]
	b _02060332
_02060226:
	add r0, r5, #0x0
	bl FUN_0204AF84
	mov r0, #0x4
	strb r0, [r4, #0xc]
	b _02060332
_02060232:
	ldr r0, [r6, #0x38]
	bl FUN_020553A0
	ldrb r1, [r4, #0xd]
	add r7, r0, #0x0
	add r1, r1, #0x1
	strb r1, [r4, #0xd]
	ldrb r1, [r4, #0xd]
	cmp r1, #0x5
	bhi _02060290
	add r0, r6, #0x0
	bl MOD06_02245088
	add r6, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0x1
	bl FUN_0205889C
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	bl MOD06_02244DC4
	ldr r0, [r4, #0x0]
	bl MOD06_02244EF8
	mov r0, #0x0
	strb r0, [r4, #0xe]
	ldr r0, _02060338 ; =0x00000679
	bl FUN_020054C8
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r3, _0206033C ; =0x0000FFFF
	add r0, r5, #0x0
	mov r1, #0x3
	mov r2, #0x11
	bl FUN_0204C1B4
	mov r0, #0x5
	strb r0, [r4, #0xc]
	b _02060332
_02060290:
	mov r1, #0x0
	bl FUN_0205889C
	add r0, r5, #0x0
	bl FUN_0204B00C
	mov r0, #0x8
	strb r0, [r4, #0xc]
	b _02060332
_020602A2:
	ldrb r0, [r4, #0xe]
	add r0, r0, #0x1
	strb r0, [r4, #0xe]
	ldrb r0, [r4, #0xe]
	cmp r0, #0x3c
	bhs _020602B8
	ldr r0, _02060340 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	beq _02060332
_020602B8:
	ldrb r0, [r4, #0xd]
	ldr r1, [r4, #0x4]
	bl MOD06_02245198
	ldr r0, [r4, #0x4]
	bl MOD06_022451F0
	str r0, [r4, #0x8]
	ldr r0, _02060338 ; =0x00000679
	bl FUN_020054C8
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r3, _0206033C ; =0x0000FFFF
	add r0, r5, #0x0
	mov r1, #0x3
	mov r2, #0x10
	bl FUN_0204C1B4
	mov r0, #0x6
	strb r0, [r4, #0xc]
	b _02060332
_020602F0:
	ldr r0, [r4, #0x0]
	bl MOD06_02244F18
	mov r0, #0x7
	strb r0, [r4, #0xc]
	b _02060332
_020602FC:
	ldr r0, [r4, #0x0]
	bl MOD06_02244F24
	cmp r0, #0x0
	beq _02060332
	ldr r0, [r4, #0x0]
	bl MOD06_02244F2C
	mov r0, #0x1
	strb r0, [r4, #0xc]
	b _02060332
_02060312:
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_0206367C
	ldr r0, [r4, #0x4]
	bl MOD06_02245190
	ldr r0, [r4, #0x0]
	bl MOD06_02244DBC
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_02060332:
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02060338: .word 0x00000679
_0206033C: .word 0x0000FFFF
_02060340: .word gUnknown21C48B8
