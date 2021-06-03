	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global UNK_021C5994
UNK_021C5994: ; 0x021C5994
	.space 0x4

	.text

	thumb_func_start FUN_0201D040
FUN_0201D040: ; 0x0201D040
	ldr r1, _0201D054 ; =0x04001000
	ldr r2, [r1, #0x0]
	ldr r1, _0201D058 ; =0x00300010
	lsl r3, r1, #0x16
	ldr r3, [r3, #0x0]
	and r2, r1
	and r1, r3
	ldr r3, _0201D05C ; =FUN_0201D060
	bx r3
	nop
_0201D054: .word 0x04001000
_0201D058: .word 0x00300010
_0201D05C: .word FUN_0201D060

	thumb_func_start FUN_0201D060
FUN_0201D060: ; 0x0201D060
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, _0201D120 ; =UNK_021C5994
	str r1, [sp, #0x0]
	ldr r0, [r0, #0x0]
	str r2, [sp, #0x4]
	cmp r0, #0x0
	bne _0201D11A
	ldr r0, [r5, #0xc]
	mov r1, #0x3c
	bl AllocFromHeap
	add r1, r0, #0x0
	ldr r0, _0201D120 ; =UNK_021C5994
	mov r2, #0x3c
	str r1, [r0, #0x0]
	mov r0, #0x0
	bl MIi_CpuClear32
	ldr r1, _0201D120 ; =UNK_021C5994
	ldr r2, [r5, #0x0]
	ldr r0, [r1, #0x0]
	str r2, [r0, #0x4]
	ldr r1, [r1, #0x0]
	ldr r0, [r5, #0xc]
	ldr r2, [r1, #0x4]
	mov r1, #0x54
	mul r1, r2
	bl AllocFromHeap
	ldr r7, _0201D120 ; =UNK_021C5994
	mov r6, #0x0
	ldr r1, [r7, #0x0]
	str r0, [r1, #0x0]
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	ble _0201D0C2
	add r4, r6, #0x0
_0201D0AE:
	ldr r0, [r7, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	bl FUN_0201D690
	ldr r0, [r5, #0x0]
	add r6, r6, #0x1
	add r4, #0x54
	cmp r6, r0
	blt _0201D0AE
_0201D0C2:
	ldr r0, [sp, #0x0]
	bl FUN_0201DED0
	ldr r1, _0201D120 ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x2c]
	ldr r0, [sp, #0x4]
	bl FUN_0201DED0
	ldr r2, _0201D120 ; =UNK_021C5994
	mov r3, #0x1
	ldr r1, [r2, #0x0]
	lsl r3, r3, #0x1a
	str r0, [r1, #0x30]
	ldr r0, [r3, #0x0]
	ldr r1, _0201D124 ; =0xFFCFFFEF
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	and r4, r1
	orr r0, r4
	str r0, [r3, #0x0]
	ldr r3, _0201D128 ; =0x04001000
	ldr r0, [r3, #0x0]
	and r1, r0
	ldr r0, [sp, #0x4]
	orr r0, r1
	str r0, [r3, #0x0]
	ldr r1, [r2, #0x0]
	ldr r0, [r5, #0x4]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	ldr r1, _0201D120 ; =UNK_021C5994
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r0, [r5, #0x8]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	add r1, r0, #0x0
	ldr r2, [r5, #0xc]
	add r0, r4, #0x0
	bl FUN_0201DC58
_0201D11A:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0201D120: .word UNK_021C5994
_0201D124: .word 0xFFCFFFEF
_0201D128: .word 0x04001000

	thumb_func_start FUN_0201D12C
FUN_0201D12C: ; 0x0201D12C
	push {r3, lr}
	ldr r0, _0201D164 ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201D162
	ldr r0, [r0, #0x34]
	bl FUN_0201DCC0
	ldr r0, _0201D164 ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_0201DCC0
	bl FUN_0201D374
	ldr r0, _0201D164 ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	ldr r0, _0201D164 ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	ldr r0, _0201D164 ; =UNK_021C5994
	mov r1, #0x0
	str r1, [r0, #0x0]
_0201D162:
	pop {r3, pc}
	.balign 4
_0201D164: .word UNK_021C5994

	thumb_func_start FUN_0201D168
FUN_0201D168: ; 0x0201D168
	push {r3, lr}
	ldr r0, _0201D190 ; =UNK_021C5994
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	str r2, [r1, #0xc]
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x10]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_0201DD00
	ldr r0, _0201D190 ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_0201DD00
	bl FUN_0201DAE8
	pop {r3, pc}
	nop
_0201D190: .word UNK_021C5994

	thumb_func_start FUN_0201D194
FUN_0201D194: ; 0x0201D194
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r3, r1, #0x0
	cmp r2, #0x1
	add r0, sp, #0x4
	bne _0201D1CA
	str r0, [sp, #0x0]
	ldr r0, _0201D1F4 ; =UNK_021C5994
	add r2, r3, #0x0
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x1c]
	add r3, sp, #0x8
	bl FUN_0201DFF0
	ldr r3, [sp, #0x4]
	cmp r3, #0x0
	ble _0201D1F0
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldr r1, [sp, #0x8]
	mov r0, #0x1
	bl FUN_0201D948
	add sp, #0xc
	pop {r3-r4, pc}
_0201D1CA:
	str r0, [sp, #0x0]
	ldr r0, _0201D1F4 ; =UNK_021C5994
	add r2, r3, #0x0
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x20]
	add r3, sp, #0x8
	bl FUN_0201DFF0
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0201D1F0
	str r0, [sp, #0x0]
	mov r1, #0x0
	ldr r2, [sp, #0x8]
	mov r0, #0x2
	add r3, r1, #0x0
	bl FUN_0201D948
_0201D1F0:
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4
_0201D1F4: .word UNK_021C5994

	thumb_func_start FUN_0201D1F8
FUN_0201D1F8: ; 0x0201D1F8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x8]
	bl FUN_0201D2AC
	cmp r0, #0x1
	bne _0201D20A
	bl GF_AssertFail
_0201D20A:
	bl FUN_0201DAAC
	add r4, r0, #0x0
	bne _0201D21A
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D21A:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201D6B4
	cmp r0, #0x0
	bne _0201D22A
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D22A:
	add r0, r4, #0x0
	bl FUN_0201D724
	cmp r0, #0x0
	bne _0201D23E
	ldr r0, [r4, #0xc]
	bl FUN_0201D324
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D23E:
	ldr r0, _0201D24C ; =UNK_021C5994
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x8]
	add r0, r0, #0x1
	str r0, [r1, #0x8]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0201D24C: .word UNK_021C5994

	thumb_func_start FUN_0201D250
FUN_0201D250: ; 0x0201D250
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x8]
	bl FUN_0201D2AC
	cmp r0, #0x1
	bne _0201D262
	bl GF_AssertFail
_0201D262:
	bl FUN_0201DAAC
	add r4, r0, #0x0
	bne _0201D272
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D272:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201D6B4
	cmp r0, #0x0
	bne _0201D282
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D282:
	mov r0, #0x1
	str r0, [r4, #0x40]
	add r0, r4, #0x0
	bl FUN_0201D724
	cmp r0, #0x0
	bne _0201D29A
	ldr r0, [r4, #0xc]
	bl FUN_0201D324
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D29A:
	ldr r0, _0201D2A8 ; =UNK_021C5994
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x8]
	add r0, r0, #0x1
	str r0, [r1, #0x8]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0201D2A8: .word UNK_021C5994

	thumb_func_start FUN_0201D2AC
FUN_0201D2AC: ; 0x0201D2AC
	push {r3-r4}
	ldr r1, _0201D2D8 ; =UNK_021C5994
	mov r2, #0x0
	ldr r4, [r1, #0x0]
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	ble _0201D2D2
	ldr r3, [r4, #0x0]
_0201D2BC:
	ldr r1, [r3, #0xc]
	cmp r0, r1
	bne _0201D2C8
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_0201D2C8:
	ldr r1, [r4, #0x4]
	add r2, r2, #0x1
	add r3, #0x54
	cmp r2, r1
	blt _0201D2BC
_0201D2D2:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4
_0201D2D8: .word UNK_021C5994

	thumb_func_start FUN_0201D2DC
FUN_0201D2DC: ; 0x0201D2DC
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	bne _0201D2E8
	bl GF_AssertFail
_0201D2E8:
	add r0, r4, #0x0
	bl FUN_0201D7F8
	add r4, r0, #0x0
	bne _0201D2F6
	bl GF_AssertFail
_0201D2F6:
	str r5, [r4, #0x0]
	ldr r1, [r4, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201D30C
	ldr r1, [r4, #0x34]
	ldr r2, [r5, #0x14]
	ldr r3, [r5, #0x10]
	mov r0, #0x13
	bl FUN_0201C2C8
_0201D30C:
	ldr r1, [r4, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201D320
	ldr r1, [r4, #0x38]
	ldr r2, [r5, #0x14]
	ldr r3, [r5, #0x10]
	mov r0, #0x23
	bl FUN_0201C2C8
_0201D320:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201D324
FUN_0201D324: ; 0x0201D324
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r5, #0x1
	mov r7, #0x0
_0201D32C:
	add r0, r6, #0x0
	bl FUN_0201D7F8
	add r4, r0, #0x0
	bne _0201D33A
	bl GF_AssertFail
_0201D33A:
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x4
	bne _0201D34E
	add r0, r4, #0x0
	add r0, #0x10
	bl FUN_0201D4F0
	b _0201D350
_0201D34E:
	add r5, r7, #0x0
_0201D350:
	cmp r5, #0x0
	bne _0201D32C
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201D36E
	add r0, r4, #0x0
	bl FUN_0201D7E0
	ldr r0, _0201D370 ; =UNK_021C5994
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x8]
	sub r0, r0, #0x1
	str r0, [r1, #0x8]
_0201D36E:
	pop {r3-r7, pc}
	.balign 4
_0201D370: .word UNK_021C5994

	thumb_func_start FUN_0201D374
FUN_0201D374: ; 0x0201D374
	push {r4-r6, lr}
	ldr r6, _0201D3AC ; =UNK_021C5994
	mov r4, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, [r1, #0x4]
	cmp r0, #0x0
	ble _0201D3AA
	add r5, r4, #0x0
_0201D384:
	ldr r1, [r1, #0x0]
	add r0, r1, r5
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201D39E
	add r0, r1, r5
	bl FUN_0201D7E0
	ldr r1, [r6, #0x0]
	ldr r0, [r1, #0x8]
	sub r0, r0, #0x1
	str r0, [r1, #0x8]
_0201D39E:
	ldr r1, [r6, #0x0]
	add r4, r4, #0x1
	ldr r0, [r1, #0x4]
	add r5, #0x54
	cmp r4, r0
	blt _0201D384
_0201D3AA:
	pop {r4-r6, pc}
	.balign 4
_0201D3AC: .word UNK_021C5994

	thumb_func_start FUN_0201D3B0
FUN_0201D3B0: ; 0x0201D3B0
	push {r4, lr}
	bl FUN_0201D7F8
	add r4, r0, #0x0
	bne _0201D3BE
	bl GF_AssertFail
_0201D3BE:
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201D3CC
	mov r0, #0x0
	pop {r4, pc}
_0201D3CC:
	add r4, #0x10
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201D3D4
FUN_0201D3D4: ; 0x0201D3D4
	push {r3-r5, lr}
	sub sp, #0x18
	add r5, r1, #0x0
	bl FUN_0201D7F8
	add r4, r0, #0x0
	bne _0201D3E6
	bl GF_AssertFail
_0201D3E6:
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201D3F6
	add sp, #0x18
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D3F6:
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x4]
	add r1, sp, #0x14
	add r2, sp, #0x10
	add r3, r5, #0x0
	bl FUN_0201D86C
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	bne _0201D41A
	add sp, #0x18
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D41A:
	add r0, r4, #0x0
	mov r1, #0x3
	add r0, #0x3c
	strb r1, [r0, #0x0]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	add r0, r4, #0x0
	bl FUN_0201D918
	mov r0, #0x1
	str r0, [r4, #0x48]
	ldr r0, [sp, #0xc]
	str r0, [r4, #0x4c]
	ldr r0, [sp, #0x8]
	str r0, [r4, #0x50]
	add r0, r4, #0x0
	bl FUN_0201DA38
	ldr r0, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x4]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	bl FUN_0201D948
	add r4, #0x10
	add r0, r4, #0x0
	add sp, #0x18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201D458
FUN_0201D458: ; 0x0201D458
	push {r3-r5, lr}
	sub sp, #0x18
	bl FUN_0201D6D8
	add r4, r0, #0x0
	bne _0201D468
	bl GF_AssertFail
_0201D468:
	bl FUN_0201DAAC
	add r5, r0, #0x0
	bne _0201D474
	bl GF_AssertFail
_0201D474:
	add r0, r4, #0x0
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	beq _0201D484
	add sp, #0x18
	mov r0, #0x0
	pop {r3-r5, pc}
_0201D484:
	add r3, r5, #0x0
	mov r2, #0xa
_0201D488:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0201D488
	ldr r0, [r4, #0x0]
	mov r1, #0x4
	str r0, [r3, #0x0]
	add r0, r5, #0x0
	add r0, #0x3c
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	tst r1, r0
	beq _0201D4A8
	ldr r3, [r5, #0x4c]
	b _0201D4AA
_0201D4A8:
	ldr r3, [r5, #0x50]
_0201D4AA:
	add r1, sp, #0xc
	str r1, [sp, #0x0]
	add r1, sp, #0x8
	str r1, [sp, #0x4]
	add r1, sp, #0x14
	add r2, sp, #0x10
	bl FUN_0201D86C
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	add r0, r5, #0x0
	bl FUN_0201D918
	mov r0, #0x1
	str r0, [r5, #0x48]
	ldr r0, [sp, #0xc]
	str r0, [r5, #0x4c]
	ldr r0, [sp, #0x8]
	str r0, [r5, #0x50]
	add r0, r5, #0x0
	bl FUN_0201DA38
	ldr r0, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x4]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	bl FUN_0201D948
	add r5, #0x10
	add r0, r5, #0x0
	add sp, #0x18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201D4F0
FUN_0201D4F0: ; 0x0201D4F0
	push {r4-r6, lr}
	ldr r2, _0201D564 ; =UNK_021C5994
	mov r1, #0x0
	ldr r5, [r2, #0x0]
	ldr r4, [r5, #0x4]
	cmp r4, #0x0
	ble _0201D52E
	ldr r2, [r5, #0x0]
	add r3, r1, #0x0
_0201D502:
	add r6, r2, #0x0
	add r6, #0x3c
	ldrb r6, [r6, #0x0]
	cmp r6, #0x3
	beq _0201D518
	ldr r6, [r5, #0x0]
	add r6, r6, r3
	add r6, #0x3c
	ldrb r6, [r6, #0x0]
	cmp r6, #0x4
	bne _0201D522
_0201D518:
	ldr r6, [r5, #0x0]
	add r6, r6, r3
	add r6, #0x10
	cmp r6, r0
	beq _0201D52E
_0201D522:
	ldr r6, [r5, #0x4]
	add r1, r1, #0x1
	add r2, #0x54
	add r3, #0x54
	cmp r1, r6
	blt _0201D502
_0201D52E:
	cmp r1, r4
	bge _0201D562
	mov r0, #0x54
	add r4, r1, #0x0
	mul r4, r0
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	bl FUN_0201DE4C
	ldr r0, _0201D564 ; =UNK_021C5994
	ldr r1, [r0, #0x0]
	ldr r2, [r1, #0x0]
	add r2, #0x3c
	ldrb r1, [r2, r4]
	cmp r1, #0x3
	bne _0201D554
	mov r0, #0x2
	strb r0, [r2, r4]
	pop {r4-r6, pc}
_0201D554:
	mov r1, #0x0
	strb r1, [r2, r4]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	bl FUN_0201D690
_0201D562:
	pop {r4-r6, pc}
	.balign 4
_0201D564: .word UNK_021C5994

	thumb_func_start FUN_0201D568
FUN_0201D568: ; 0x0201D568
	push {r3-r7, lr}
	sub sp, #0x18
	add r6, r0, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	cmp r1, #0x0
	bne _0201D5A0
	add r1, r5, #0x0
	add r2, sp, #0x14
	add r3, sp, #0x10
	bl FUN_0201DF44
	add r7, r0, #0x0
	beq _0201D5E0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0201DF94
	str r5, [r4, #0x8]
	str r6, [r4, #0x0]
	cmp r5, #0x1
	bne _0201D59A
	ldr r0, [sp, #0x14]
	str r0, [r4, #0x4]
	b _0201D5E0
_0201D59A:
	ldr r0, [sp, #0x10]
	str r0, [r4, #0x4]
	b _0201D5E0
_0201D5A0:
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, sp, #0x14
	add r2, sp, #0x10
	add r3, r6, #0x0
	bl FUN_0201D86C
	add r7, r0, #0x0
	beq _0201D5E0
	ldr r0, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	add r0, r5, #0x0
	bl FUN_0201D948
	str r5, [r4, #0x8]
	cmp r5, #0x1
	bne _0201D5D8
	ldr r0, [sp, #0xc]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x14]
	str r0, [r4, #0x4]
	b _0201D5E0
_0201D5D8:
	ldr r0, [sp, #0x8]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x10]
	str r0, [r4, #0x4]
_0201D5E0:
	add r0, r7, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201D5E8
FUN_0201D5E8: ; 0x0201D5E8
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x8]
	mov r0, #0x1
	tst r0, r1
	beq _0201D61E
	ldr r1, _0201D654 ; =UNK_021C5994
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	add r5, r0, #0x0
	ldr r0, _0201D654 ; =UNK_021C5994
	ldr r1, [r4, #0x4]
	ldr r2, [r0, #0x0]
	ldr r0, [r2, #0x1c]
	sub r0, r1, r0
	ldr r1, [r2, #0x2c]
	bl FUN_0201DF2C
	ldr r2, _0201D654 ; =UNK_021C5994
	add r1, r5, #0x0
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x34]
	bl FUN_0201DDFC
_0201D61E:
	ldr r1, [r4, #0x8]
	mov r0, #0x2
	tst r0, r1
	beq _0201D650
	ldr r1, _0201D654 ; =UNK_021C5994
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	add r5, r0, #0x0
	ldr r0, _0201D654 ; =UNK_021C5994
	ldr r1, [r4, #0x4]
	ldr r2, [r0, #0x0]
	ldr r0, [r2, #0x20]
	sub r0, r1, r0
	ldr r1, [r2, #0x30]
	bl FUN_0201DF2C
	ldr r2, _0201D654 ; =UNK_021C5994
	add r1, r5, #0x0
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x38]
	bl FUN_0201DDFC
_0201D650:
	pop {r3-r5, pc}
	nop
_0201D654: .word UNK_021C5994

	thumb_func_start FUN_0201D658
FUN_0201D658: ; 0x0201D658
	push {r3, lr}
	ldr r0, _0201D670 ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201D666
	bl GF_AssertFail
_0201D666:
	ldr r1, _0201D670 ; =UNK_021C5994
	mov r2, #0x0
	ldr r0, [r1, #0x0]
	str r2, [r1, #0x0]
	pop {r3, pc}
	.balign 4
_0201D670: .word UNK_021C5994

	thumb_func_start FUN_0201D674
FUN_0201D674: ; 0x0201D674
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0201D68C ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201D684
	bl GF_AssertFail
_0201D684:
	ldr r0, _0201D68C ; =UNK_021C5994
	str r4, [r0, #0x0]
	pop {r4, pc}
	nop
_0201D68C: .word UNK_021C5994

	thumb_func_start FUN_0201D690
FUN_0201D690: ; 0x0201D690
	mov r2, #0x0
	str r2, [r0, #0x0]
	str r2, [r0, #0x4]
	strb r2, [r0, #0x8]
	sub r1, r2, #0x1
	str r1, [r0, #0xc]
	str r2, [r0, #0x34]
	add r1, r0, #0x0
	str r2, [r0, #0x38]
	add r1, #0x3c
	strb r2, [r1, #0x0]
	str r2, [r0, #0x40]
	ldr r3, _0201D6B0 ; =NNS_G2dInitImageProxy
	add r0, #0x10
	bx r3
	nop
_0201D6B0: .word NNS_G2dInitImageProxy

	thumb_func_start FUN_0201D6B4
FUN_0201D6B4: ; 0x0201D6B4
	ldr r2, [r0, #0x0]
	str r2, [r1, #0x0]
	ldr r2, [r0, #0x8]
	str r2, [r1, #0xc]
	ldr r2, [r0, #0x4]
	str r2, [r1, #0x4]
	ldr r2, [r1, #0x0]
	ldr r2, [r2, #0xc]
	lsr r2, r2, #0x8
	strb r2, [r1, #0x8]
	ldr r0, [r0, #0xc]
	str r0, [r1, #0x44]
	mov r0, #0x0
	str r0, [r1, #0x48]
	str r0, [r1, #0x4c]
	str r0, [r1, #0x50]
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0201D6D8
FUN_0201D6D8: ; 0x0201D6D8
	push {r3-r6}
	ldr r2, _0201D720 ; =UNK_021C5994
	mov r1, #0x0
	ldr r5, [r2, #0x0]
	ldr r4, [r5, #0x4]
	cmp r4, #0x0
	ble _0201D70A
	ldr r2, [r5, #0x0]
	add r3, r1, #0x0
_0201D6EA:
	add r6, r2, #0x0
	add r6, #0x3c
	ldrb r6, [r6, #0x0]
	cmp r6, #0x0
	beq _0201D6FE
	ldr r6, [r5, #0x0]
	add r6, r6, r3
	add r6, #0x10
	cmp r6, r0
	beq _0201D70A
_0201D6FE:
	ldr r6, [r5, #0x4]
	add r1, r1, #0x1
	add r2, #0x54
	add r3, #0x54
	cmp r1, r6
	blt _0201D6EA
_0201D70A:
	cmp r1, r4
	blt _0201D714
	mov r0, #0x0
	pop {r3-r6}
	bx lr
_0201D714:
	mov r0, #0x54
	ldr r2, [r5, #0x0]
	mul r0, r1
	add r0, r2, r0
	pop {r3-r6}
	bx lr
	.balign 4
_0201D720: .word UNK_021C5994

	thumb_func_start FUN_0201D724
FUN_0201D724: ; 0x0201D724
	push {r3, lr}
	ldrb r1, [r0, #0x8]
	mov r2, #0x1
	cmp r1, #0x0
	beq _0201D736
	mov r1, #0x2
	add r0, #0x3c
	strb r1, [r0, #0x0]
	b _0201D750
_0201D736:
	add r1, r0, #0x0
	add r1, #0x3c
	strb r2, [r1, #0x0]
	ldr r1, [r0, #0x44]
	cmp r1, #0x0
	bne _0201D74A
	bl FUN_0201D754
	add r2, r0, #0x0
	b _0201D750
_0201D74A:
	bl FUN_0201D788
	add r2, r0, #0x0
_0201D750:
	add r0, r2, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0201D754
FUN_0201D754: ; 0x0201D754
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	ldr r0, [r0, #0x10]
	add r2, sp, #0x4
	add r3, sp, #0x0
	bl FUN_0201DF44
	add r4, r0, #0x0
	beq _0201D780
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_0201D858
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	ldr r0, [r0, #0x10]
	bl FUN_0201DF94
_0201D780:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201D788
FUN_0201D788: ; 0x0201D788
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0x0
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	ldr r3, [r4, #0x0]
	ldr r0, [r4, #0x4]
	ldr r3, [r3, #0x10]
	add r1, sp, #0x14
	add r2, sp, #0x10
	bl FUN_0201D86C
	cmp r0, #0x0
	bne _0201D7AE
	add sp, #0x18
	mov r0, #0x0
	pop {r4, pc}
_0201D7AE:
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	add r0, r4, #0x0
	bl FUN_0201D918
	mov r0, #0x1
	str r0, [r4, #0x48]
	ldr r0, [sp, #0xc]
	str r0, [r4, #0x4c]
	ldr r0, [sp, #0x8]
	str r0, [r4, #0x50]
	add r0, r4, #0x0
	bl FUN_0201D9B0
	ldr r0, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x4]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	bl FUN_0201D948
	mov r0, #0x1
	add sp, #0x18
	pop {r4, pc}

	thumb_func_start FUN_0201D7E0
FUN_0201D7E0: ; 0x0201D7E0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x48]
	cmp r1, #0x0
	beq _0201D7EE
	bl FUN_0201DE4C
_0201D7EE:
	add r0, r4, #0x0
	bl FUN_0201D690
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201D7F8
FUN_0201D7F8: ; 0x0201D7F8
	push {r4-r5}
	ldr r2, _0201D82C ; =UNK_021C5994
	mov r1, #0x0
	ldr r5, [r2, #0x0]
	ldr r2, [r5, #0x4]
	cmp r2, #0x0
	ble _0201D824
	ldr r2, [r5, #0x0]
	add r4, r2, #0x0
_0201D80A:
	ldr r3, [r4, #0xc]
	cmp r0, r3
	bne _0201D81A
	mov r0, #0x54
	mul r0, r1
	add r0, r2, r0
	pop {r4-r5}
	bx lr
_0201D81A:
	ldr r3, [r5, #0x4]
	add r1, r1, #0x1
	add r4, #0x54
	cmp r1, r3
	blt _0201D80A
_0201D824:
	mov r0, #0x0
	pop {r4-r5}
	bx lr
	nop
_0201D82C: .word UNK_021C5994

	thumb_func_start FUN_0201D830
FUN_0201D830: ; 0x0201D830
	cmp r1, #0x1
	bne _0201D83C
	mov r1, #0x1
	lsl r1, r1, #0x1a
	ldr r2, [r1, #0x0]
	b _0201D840
_0201D83C:
	ldr r1, _0201D850 ; =0x04001000
	ldr r2, [r1, #0x0]
_0201D840:
	ldr r1, _0201D854 ; =0x00300010
	and r2, r1
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x8]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x8]
	bx lr
	nop
_0201D850: .word 0x04001000
_0201D854: .word 0x00300010

	thumb_func_start FUN_0201D858
FUN_0201D858: ; 0x0201D858
	push {r3, lr}
	str r1, [r0, #0x34]
	str r2, [r0, #0x38]
	ldrb r1, [r0, #0x8]
	cmp r1, #0x0
	bne _0201D868
	bl FUN_0201D9B0
_0201D868:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201D86C
FUN_0201D86C: ; 0x0201D86C
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [sp, #0x1c]
	add r6, r2, #0x0
	str r0, [sp, #0x1c]
	mov r2, #0x1
	add r0, r5, #0x0
	add r4, r1, #0x0
	str r3, [sp, #0x0]
	ldr r7, [sp, #0x18]
	tst r0, r2
	beq _0201D8C4
	ldr r1, _0201D914 ; =UNK_021C5994
	add r0, r3, #0x0
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF10
	ldr r1, _0201D914 ; =UNK_021C5994
	str r0, [r7, #0x0]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	ldr r1, _0201D914 ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x34]
	bl FUN_0201DD74
	mov r1, #0x0
	mvn r1, r1
	str r0, [r4, #0x0]
	cmp r0, r1
	bne _0201D8B8
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3-r7, pc}
_0201D8B8:
	ldr r1, _0201D914 ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF3C
	str r0, [r4, #0x0]
_0201D8C4:
	mov r0, #0x2
	tst r0, r5
	beq _0201D90E
	ldr r1, _0201D914 ; =UNK_021C5994
	ldr r0, [sp, #0x0]
	ldr r1, [r1, #0x0]
	mov r2, #0x1
	ldr r1, [r1, #0x30]
	bl FUN_0201DF10
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r1, _0201D914 ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	ldr r1, _0201D914 ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x38]
	bl FUN_0201DD74
	mov r1, #0x0
	mvn r1, r1
	str r0, [r6, #0x0]
	cmp r0, r1
	bne _0201D902
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3-r7, pc}
_0201D902:
	ldr r1, _0201D914 ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF3C
	str r0, [r6, #0x0]
_0201D90E:
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_0201D914: .word UNK_021C5994

	thumb_func_start FUN_0201D918
FUN_0201D918: ; 0x0201D918
	push {r3-r4}
	ldr r4, [r0, #0x4]
	mov r3, #0x1
	tst r3, r4
	beq _0201D92C
	ldr r3, _0201D944 ; =UNK_021C5994
	ldr r3, [r3, #0x0]
	ldr r3, [r3, #0x1c]
	add r1, r1, r3
	str r1, [r0, #0x34]
_0201D92C:
	ldr r3, [r0, #0x4]
	mov r1, #0x2
	tst r1, r3
	beq _0201D93E
	ldr r1, _0201D944 ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x20]
	add r1, r2, r1
	str r1, [r0, #0x38]
_0201D93E:
	pop {r3-r4}
	bx lr
	nop
_0201D944: .word UNK_021C5994

	thumb_func_start FUN_0201D948
FUN_0201D948: ; 0x0201D948
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x1
	add r4, r1, #0x0
	add r6, r2, #0x0
	tst r0, r5
	beq _0201D97C
	ldr r1, _0201D9AC ; =UNK_021C5994
	add r0, r3, #0x0
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	ldr r1, _0201D9AC ; =UNK_021C5994
	add r7, r0, #0x0
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	ldr r2, _0201D9AC ; =UNK_021C5994
	add r1, r7, #0x0
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x34]
	bl FUN_0201DD18
_0201D97C:
	mov r0, #0x2
	tst r0, r5
	beq _0201D9A8
	ldr r1, _0201D9AC ; =UNK_021C5994
	ldr r0, [sp, #0x18]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	ldr r1, _0201D9AC ; =UNK_021C5994
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	add r0, r6, #0x0
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	ldr r2, _0201D9AC ; =UNK_021C5994
	add r1, r4, #0x0
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x38]
	bl FUN_0201DD18
_0201D9A8:
	pop {r3-r7, pc}
	nop
_0201D9AC: .word UNK_021C5994

	thumb_func_start FUN_0201D9B0
FUN_0201D9B0: ; 0x0201D9B0
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x10
	bl NNS_G2dInitImageProxy
	ldr r1, [r4, #0x4]
	cmp r1, #0x3
	beq _0201D9C8
	add r0, r4, #0x0
	bl FUN_0201D9DC
	pop {r4, pc}
_0201D9C8:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0201D9DC
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0201D9DC
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201D9DC
FUN_0201D9DC: ; 0x0201D9DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x40]
	add r4, r1, #0x0
	cmp r2, #0x0
	beq _0201D9EE
	bl FUN_0201D830
	b _0201D9F0
_0201D9EE:
	add r0, r4, #0x0
_0201D9F0:
	cmp r4, #0x1
	bne _0201D9FE
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r5, #0x34]
	ldr r2, [r2, #0x0]
	b _0201DA04
_0201D9FE:
	ldr r2, _0201DA34 ; =0x04001000
	ldr r1, [r5, #0x38]
	ldr r2, [r2, #0x0]
_0201DA04:
	cmp r0, #0x0
	ldr r0, [r5, #0x0]
	bne _0201DA16
	add r5, #0x10
	add r2, r4, #0x0
	add r3, r5, #0x0
	bl NNS_G2dLoadImage2DMapping
	b _0201DA20
_0201DA16:
	add r5, #0x10
	add r2, r4, #0x0
	add r3, r5, #0x0
	bl NNS_G2dLoadImage1DMapping
_0201DA20:
	cmp r4, #0x1
	bne _0201DA2C
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
_0201DA2C:
	ldr r0, _0201DA34 ; =0x04001000
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
	nop
_0201DA34: .word 0x04001000

	thumb_func_start FUN_0201DA38
FUN_0201DA38: ; 0x0201DA38
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x10
	bl NNS_G2dInitImageProxy
	ldr r1, [r4, #0x4]
	cmp r1, #0x3
	beq _0201DA50
	add r0, r4, #0x0
	bl FUN_0201DA64
	pop {r4, pc}
_0201DA50:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0201DA64
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0201DA64
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201DA64
FUN_0201DA64: ; 0x0201DA64
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x40]
	add r4, r1, #0x0
	cmp r2, #0x0
	beq _0201DA74
	bl FUN_0201D830
_0201DA74:
	cmp r4, #0x1
	bne _0201DA82
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r1, [r5, #0x34]
	ldr r0, [r0, #0x0]
	b _0201DA88
_0201DA82:
	ldr r0, _0201DAA8 ; =0x04001000
	ldr r1, [r5, #0x38]
	ldr r0, [r0, #0x0]
_0201DA88:
	ldr r0, [r5, #0x0]
	add r5, #0x10
	add r2, r4, #0x0
	add r3, r5, #0x0
	bl NNS_G2dLoadImageVramTransfer
	cmp r4, #0x1
	bne _0201DAA0
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
_0201DAA0:
	ldr r0, _0201DAA8 ; =0x04001000
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
	nop
_0201DAA8: .word 0x04001000

	thumb_func_start FUN_0201DAAC
FUN_0201DAAC: ; 0x0201DAAC
	push {r3-r4}
	ldr r1, _0201DAE4 ; =UNK_021C5994
	mov r0, #0x0
	ldr r4, [r1, #0x0]
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	ble _0201DADC
	ldr r1, [r4, #0x0]
	add r3, r1, #0x0
_0201DABE:
	add r2, r3, #0x0
	add r2, #0x3c
	ldrb r2, [r2, #0x0]
	cmp r2, #0x0
	bne _0201DAD2
	mov r2, #0x54
	mul r2, r0
	add r0, r1, r2
	pop {r3-r4}
	bx lr
_0201DAD2:
	ldr r2, [r4, #0x4]
	add r0, r0, #0x1
	add r3, #0x54
	cmp r0, r2
	blt _0201DABE
_0201DADC:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	nop
_0201DAE4: .word UNK_021C5994

	thumb_func_start FUN_0201DAE8
FUN_0201DAE8: ; 0x0201DAE8
	push {r3, lr}
	bl GX_GetBankForOBJ
	cmp r0, #0x30
	bgt _0201DB18
	bge _0201DB60
	cmp r0, #0x10
	bgt _0201DB12
	bge _0201DB54
	cmp r0, #0x3
	bhi _0201DB90
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0201DB0A: ; jump table (using 16-bit offset)
	.short _0201DB32 - _0201DB0A - 2; case 0
	.short _0201DB78 - _0201DB0A - 2; case 1
	.short _0201DB78 - _0201DB0A - 2; case 2
	.short _0201DB84 - _0201DB0A - 2; case 3
_0201DB12:
	cmp r0, #0x20
	beq _0201DB3C
	b _0201DB90
_0201DB18:
	cmp r0, #0x50
	bgt _0201DB24
	bge _0201DB60
	cmp r0, #0x40
	beq _0201DB3C
	b _0201DB90
_0201DB24:
	cmp r0, #0x60
	bgt _0201DB2C
	beq _0201DB48
	b _0201DB90
_0201DB2C:
	cmp r0, #0x70
	beq _0201DB6C
	b _0201DB90
_0201DB32:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB3C:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB48:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB54:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x10
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB60:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x5
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB6C:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x6
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB78:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x10
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB84:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x12
	str r1, [r0, #0x14]
	b _0201DB98
_0201DB90:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x14]
_0201DB98:
	bl GX_GetBankForSubOBJ
	cmp r0, #0x0
	beq _0201DBAE
	cmp r0, #0x8
	beq _0201DBC2
	mov r1, #0x1
	lsl r1, r1, #0x8
	cmp r0, r1
	beq _0201DBB8
	b _0201DBCE
_0201DBAE:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x18]
	b _0201DBD6
_0201DBB8:
	ldr r0, _0201DC38 ; =UNK_021C5994
	lsl r1, r1, #0x6
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x18]
	b _0201DBD6
_0201DBC2:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x10
	str r1, [r0, #0x18]
	b _0201DBD6
_0201DBCE:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x18]
_0201DBD6:
	ldr r0, _0201DC38 ; =UNK_021C5994
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x24]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF3C
	ldr r1, _0201DC38 ; =UNK_021C5994
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x14]
	sub r0, r2, r0
	str r0, [r3, #0x1c]
	ldr r1, [r1, #0x0]
	ldr r0, [r1, #0x28]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF3C
	ldr r1, _0201DC38 ; =UNK_021C5994
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x18]
	sub r0, r2, r0
	str r0, [r3, #0x20]
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	ldr r0, [r1, #0x1c]
	cmp r0, #0x0
	blt _0201DC12
	ldr r0, [r1, #0x20]
	cmp r0, #0x0
	blt _0201DC12
	mov r2, #0x1
_0201DC12:
	cmp r2, #0x0
	bne _0201DC1A
	bl GF_AssertFail
_0201DC1A:
	ldr r0, _0201DC38 ; =UNK_021C5994
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x1c]
	cmp r0, #0x0
	blt _0201DC2E
	ldr r0, [r1, #0x20]
	cmp r0, #0x0
	blt _0201DC2E
	mov r2, #0x1
_0201DC2E:
	cmp r2, #0x0
	bne _0201DC36
	bl GF_AssertFail
_0201DC36:
	pop {r3, pc}
	.balign 4
_0201DC38: .word UNK_021C5994

	thumb_func_start FUN_0201DC3C
FUN_0201DC3C: ; 0x0201DC3C
	push {r3, lr}
	ldr r0, _0201DC54 ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_0201DD00
	ldr r0, _0201DC54 ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_0201DD00
	pop {r3, pc}
	.balign 4
_0201DC54: .word UNK_021C5994

	thumb_func_start FUN_0201DC58
FUN_0201DC58: ; 0x0201DC58
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _0201DCBC ; =UNK_021C5994
	add r4, r1, #0x0
	ldr r1, [r0, #0x0]
	add r6, r2, #0x0
	str r5, [r1, #0x24]
	ldr r1, [r0, #0x0]
	str r4, [r1, #0x28]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	cmp r0, #0x0
	beq _0201DC76
	bl FreeToHeap
_0201DC76:
	ldr r0, _0201DCBC ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	cmp r0, #0x0
	beq _0201DC84
	bl FreeToHeap
_0201DC84:
	ldr r0, _0201DCBC ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x24]
	cmp r0, #0x0
	beq _0201DC9C
	add r0, r6, #0x0
	lsr r1, r5, #0x3
	bl AllocFromHeap
	ldr r1, _0201DCBC ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x34]
_0201DC9C:
	ldr r0, _0201DCBC ; =UNK_021C5994
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	cmp r0, #0x0
	beq _0201DCB4
	add r0, r6, #0x0
	lsr r1, r4, #0x3
	bl AllocFromHeap
	ldr r1, _0201DCBC ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x38]
_0201DCB4:
	bl FUN_0201DC3C
	pop {r4-r6, pc}
	nop
_0201DCBC: .word UNK_021C5994

	thumb_func_start FUN_0201DCC0
FUN_0201DCC0: ; 0x0201DCC0
	push {r3, lr}
	cmp r0, #0x0
	beq _0201DCE2
	ldr r1, _0201DCE4 ; =UNK_021C5994
	ldr r2, [r1, #0x0]
	ldr r1, [r2, #0x34]
	cmp r0, r1
	bne _0201DCDA
	mov r1, #0x0
	str r1, [r2, #0x24]
	bl FreeToHeap
	pop {r3, pc}
_0201DCDA:
	mov r1, #0x0
	str r1, [r2, #0x28]
	bl FreeToHeap
_0201DCE2:
	pop {r3, pc}
	.balign 4
_0201DCE4: .word UNK_021C5994

	thumb_func_start FUN_0201DCE8
FUN_0201DCE8: ; 0x0201DCE8
	ldr r1, _0201DCFC ; =UNK_021C5994
	ldr r2, [r1, #0x0]
	ldr r1, [r2, #0x34]
	cmp r0, r1
	bne _0201DCF6
	ldr r0, [r2, #0x24]
	bx lr
_0201DCF6:
	ldr r0, [r2, #0x28]
	bx lr
	nop
_0201DCFC: .word UNK_021C5994

	thumb_func_start FUN_0201DD00
FUN_0201DD00: ; 0x0201DD00
	push {r4, lr}
	add r4, r0, #0x0
	beq _0201DD16
	bl FUN_0201DCE8
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x0
	lsr r2, r2, #0x3
	bl memset
_0201DD16:
	pop {r4, pc}

	thumb_func_start FUN_0201DD18
FUN_0201DD18: ; 0x0201DD18
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	beq _0201DD6E
	add r0, r4, #0x0
	bl FUN_0201DCE8
	add r6, r5, r6
	add r7, r0, #0x0
	cmp r5, r6
	bhs _0201DD6E
_0201DD32:
	cmp r5, r7
	bhs _0201DD6E
	add r0, r5, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	bl FUN_0201DFE4
	add r0, sp, #0x0
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	lsl r0, r1
	ldr r1, [sp, #0x4]
	ldrb r1, [r4, r1]
	tst r0, r1
	beq _0201DD54
	bl GF_AssertFail
_0201DD54:
	add r2, sp, #0x0
	ldrb r3, [r2, #0x0]
	ldr r1, [sp, #0x4]
	mov r2, #0x1
	lsl r2, r3
	lsl r2, r2, #0x18
	ldrb r0, [r4, r1]
	lsr r2, r2, #0x18
	add r5, r5, #0x1
	orr r0, r2
	strb r0, [r4, r1]
	cmp r5, r6
	blo _0201DD32
_0201DD6E:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201DD74
FUN_0201DD74: ; 0x0201DD74
	push {r3-r7, lr}
	sub sp, #0x10
	add r7, r0, #0x0
	str r1, [sp, #0x0]
	cmp r1, #0x0
	beq _0201DDF2
	add r0, r1, #0x0
	bl FUN_0201DCE8
	mov r6, #0x0
	str r0, [sp, #0x4]
	cmp r0, #0x0
	bls _0201DDF2
_0201DD8E:
	add r0, r6, #0x0
	add r1, sp, #0xc
	add r2, sp, #0x8
	bl FUN_0201DFE4
	add r0, sp, #0x8
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	mov r4, #0x0
	lsl r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	b _0201DDD0
_0201DDA8:
	add r5, r6, r4
	add r0, r5, #0x0
	add r1, sp, #0xc
	add r2, sp, #0x8
	bl FUN_0201DFE4
	add r0, sp, #0x8
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	lsl r0, r1
	lsl r0, r0, #0x18
	ldr r1, [sp, #0x4]
	lsr r0, r0, #0x18
	cmp r5, r1
	blo _0201DDCE
	mov r0, #0x0
	add sp, #0x10
	mvn r0, r0
	pop {r3-r7, pc}
_0201DDCE:
	add r4, r4, #0x1
_0201DDD0:
	ldr r2, [sp, #0xc]
	ldr r1, [sp, #0x0]
	ldrb r1, [r1, r2]
	tst r0, r1
	bne _0201DDDE
	cmp r4, r7
	bls _0201DDA8
_0201DDDE:
	cmp r4, r7
	bls _0201DDE8
	add sp, #0x10
	add r0, r6, #0x0
	pop {r3-r7, pc}
_0201DDE8:
	add r0, r6, r4
	add r6, r0, #0x1
	ldr r0, [sp, #0x4]
	cmp r6, r0
	blo _0201DD8E
_0201DDF2:
	mov r0, #0x0
	mvn r0, r0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201DDFC
FUN_0201DDFC: ; 0x0201DDFC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r2, #0x0
	beq _0201DE46
	add r6, r5, r1
	cmp r5, r6
	bhs _0201DE46
	add r7, sp, #0x0
_0201DE0E:
	add r0, r5, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	bl FUN_0201DFE4
	ldrb r1, [r7, #0x0]
	mov r0, #0x1
	lsl r0, r1
	ldr r1, [sp, #0x4]
	ldrb r1, [r4, r1]
	tst r0, r1
	bne _0201DE2A
	bl GF_AssertFail
_0201DE2A:
	ldrb r0, [r7, #0x0]
	mov r1, #0x1
	ldr r3, [sp, #0x4]
	lsl r1, r0
	mov r0, #0xff
	eor r0, r1
	lsl r0, r0, #0x18
	ldrb r2, [r4, r3]
	lsr r0, r0, #0x18
	add r5, r5, #0x1
	and r0, r2
	strb r0, [r4, r3]
	cmp r5, r6
	blo _0201DE0E
_0201DE46:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201DE4C
FUN_0201DE4C: ; 0x0201DE4C
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	mov r1, #0x1
	tst r0, r1
	beq _0201DE8A
	add r0, r4, #0x0
	add r0, #0x10
	bl NNS_G2dGetImageLocation
	ldr r1, _0201DECC ; =UNK_021C5994
	ldr r2, [r1, #0x0]
	ldr r1, [r2, #0x1c]
	sub r0, r0, r1
	ldr r1, [r2, #0x2c]
	bl FUN_0201DF2C
	ldr r1, _0201DECC ; =UNK_021C5994
	add r5, r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r0, [r4, #0x4c]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF2C
	ldr r2, _0201DECC ; =UNK_021C5994
	add r1, r0, #0x0
	ldr r2, [r2, #0x0]
	add r0, r5, #0x0
	ldr r2, [r2, #0x34]
	bl FUN_0201DDFC
_0201DE8A:
	ldr r0, [r4, #0x4]
	mov r1, #0x2
	tst r0, r1
	beq _0201DEC4
	add r0, r4, #0x0
	add r0, #0x10
	bl NNS_G2dGetImageLocation
	ldr r1, _0201DECC ; =UNK_021C5994
	ldr r2, [r1, #0x0]
	ldr r1, [r2, #0x20]
	sub r0, r0, r1
	ldr r1, [r2, #0x30]
	bl FUN_0201DF2C
	ldr r1, _0201DECC ; =UNK_021C5994
	add r5, r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r0, [r4, #0x50]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF2C
	ldr r2, _0201DECC ; =UNK_021C5994
	add r1, r0, #0x0
	ldr r2, [r2, #0x0]
	add r0, r5, #0x0
	ldr r2, [r2, #0x38]
	bl FUN_0201DDFC
_0201DEC4:
	mov r0, #0x0
	str r0, [r4, #0x48]
	pop {r3-r5, pc}
	nop
_0201DECC: .word UNK_021C5994

	thumb_func_start FUN_0201DED0
FUN_0201DED0: ; 0x0201DED0
	ldr r1, _0201DF04 ; =0x00100010
	cmp r0, r1
	bgt _0201DEDE
	bge _0201DEF4
	cmp r0, #0x10
	beq _0201DEF0
	b _0201DF00
_0201DEDE:
	ldr r1, _0201DF08 ; =0x00200010
	cmp r0, r1
	bgt _0201DEE8
	beq _0201DEF8
	b _0201DF00
_0201DEE8:
	ldr r1, _0201DF0C ; =0x00300010
	cmp r0, r1
	beq _0201DEFC
	b _0201DF00
_0201DEF0:
	mov r0, #0x1
	bx lr
_0201DEF4:
	mov r0, #0x2
	bx lr
_0201DEF8:
	mov r0, #0x4
	bx lr
_0201DEFC:
	mov r0, #0x8
	bx lr
_0201DF00:
	mov r0, #0x1
	bx lr
	.balign 4
_0201DF04: .word 0x00100010
_0201DF08: .word 0x00200010
_0201DF0C: .word 0x00300010

	thumb_func_start FUN_0201DF10
FUN_0201DF10: ; 0x0201DF10
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl _s32_div_f
	cmp r1, #0x0
	beq _0201DF28
	sub r5, r5, r1
	cmp r6, #0x1
	bne _0201DF28
	add r5, r5, r4
_0201DF28:
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0201DF2C
FUN_0201DF2C: ; 0x0201DF2C
	asr r2, r0, #0x4
	lsr r2, r2, #0x1b
	add r2, r0, r2
	ldr r3, _0201DF38 ; =_s32_div_f
	asr r0, r2, #0x5
	bx r3
	.balign 4
_0201DF38: .word _s32_div_f

	thumb_func_start FUN_0201DF3C
FUN_0201DF3C: ; 0x0201DF3C
	mul r1, r0
	lsl r0, r1, #0x5
	bx lr
	.balign 4

	thumb_func_start FUN_0201DF44
FUN_0201DF44: ; 0x0201DF44
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r1, r2, #0x0
	mov r0, #0x1
	add r2, r4, #0x0
	add r7, r3, #0x0
	tst r2, r0
	beq _0201DF6E
	ldr r2, _0201DF90 ; =UNK_021C5994
	ldr r2, [r2, #0x0]
	ldr r6, [r2, #0xc]
	ldr r2, [r2, #0x1c]
	add r3, r6, r5
	cmp r3, r2
	bls _0201DF6C
	bl GF_AssertFail
	mov r0, #0x0
	b _0201DF6E
_0201DF6C:
	str r6, [r1, #0x0]
_0201DF6E:
	mov r1, #0x2
	tst r1, r4
	beq _0201DF8C
	ldr r1, _0201DF90 ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	ldr r3, [r1, #0x10]
	ldr r1, [r1, #0x20]
	add r2, r3, r5
	cmp r2, r1
	bls _0201DF8A
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3-r7, pc}
_0201DF8A:
	str r3, [r7, #0x0]
_0201DF8C:
	pop {r3-r7, pc}
	nop
_0201DF90: .word UNK_021C5994

	thumb_func_start FUN_0201DF94
FUN_0201DF94: ; 0x0201DF94
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	mov r2, #0x1
	add r0, r4, #0x0
	tst r0, r2
	beq _0201DFBC
	ldr r0, _0201DFE0 ; =UNK_021C5994
	ldr r3, [r0, #0x0]
	ldr r1, [r3, #0xc]
	add r1, r1, r5
	str r1, [r3, #0xc]
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0xc]
	ldr r1, [r1, #0x2c]
	bl FUN_0201DF10
	ldr r1, _0201DFE0 ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	str r0, [r1, #0xc]
_0201DFBC:
	mov r0, #0x2
	tst r0, r4
	beq _0201DFDE
	ldr r0, _0201DFE0 ; =UNK_021C5994
	ldr r2, [r0, #0x0]
	ldr r1, [r2, #0x10]
	add r1, r1, r5
	str r1, [r2, #0x10]
	ldr r1, [r0, #0x0]
	mov r2, #0x1
	ldr r0, [r1, #0x10]
	ldr r1, [r1, #0x30]
	bl FUN_0201DF10
	ldr r1, _0201DFE0 ; =UNK_021C5994
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x10]
_0201DFDE:
	pop {r3-r5, pc}
	.balign 4
_0201DFE0: .word UNK_021C5994

	thumb_func_start FUN_0201DFE4
FUN_0201DFE4: ; 0x0201DFE4
	asr r3, r0, #0x3
	str r3, [r1, #0x0]
	mov r1, #0x7
	and r0, r1
	strb r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_0201DFF0
FUN_0201DFF0: ; 0x0201DFF0
	push {r3-r4}
	sub r0, r1, r0
	ldr r4, [sp, #0x8]
	str r0, [r3, #0x0]
	bpl _0201E006
	add r0, r2, r0
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_0201E006:
	str r2, [r4, #0x0]
	pop {r3-r4}
	bx lr
