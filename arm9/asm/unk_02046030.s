    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02046030
FUN_02046030: ; 0x02046030
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0xc
	bl FUN_020169D8
	add r2, r0, #0x0
	mov r0, #0x0
	strb r0, [r2, #0x0]
	strb r0, [r2, #0x1]
	strb r0, [r2, #0x2]
	strb r0, [r2, #0x3]
	strb r0, [r2, #0x4]
	strb r0, [r2, #0x5]
	strb r0, [r2, #0x6]
	strb r0, [r2, #0x7]
	strb r0, [r2, #0x8]
	strb r0, [r2, #0x9]
	strb r0, [r2, #0xa]
	strb r0, [r2, #0xb]
	ldr r0, [r4, #0x10]
	ldr r1, _02046064 ; =FUN_02046068
	bl FUN_0204640C
	pop {r4, pc}
	nop
_02046064: .word FUN_02046068 

	thumb_func_start FUN_02046068
FUN_02046068: ; 0x02046068
	push {r4-r6, lr}
	sub sp, #0x38
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_020462AC
	ldrb r1, [r4, #0x8]
	cmp r1, #0xb
	bls _0204608A
	b _020461F8
_0204608A:
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02046096: ; jump table (using 16-bit offset)
	.short _020460AE - _02046096 - 2; case 0
	.short _020460D4 - _02046096 - 2; case 1
	.short _020460E2 - _02046096 - 2; case 2
	.short _0204610A - _02046096 - 2; case 3
	.short _02046118 - _02046096 - 2; case 4
	.short _02046150 - _02046096 - 2; case 5
	.short _02046160 - _02046096 - 2; case 6
	.short _0204618A - _02046096 - 2; case 7
	.short _02046198 - _02046096 - 2; case 8
	.short _020461C0 - _02046096 - 2; case 9
	.short _020461CE - _02046096 - 2; case 10
	.short _020461E4 - _02046096 - 2; case 11
_020460AE:
	ldr r0, [r5, #0x38]
	bl FUN_02055320
	strh r0, [r4, #0x4]
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	strh r0, [r4, #0x6]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0206367C
	add r0, r6, #0x0
	bl FUN_0204AFC8
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_020460D4:
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_020460E2:
	bl FUN_0205F1C4
	mov r0, #0xac
	str r0, [sp, #0x24]
	sub r0, #0xad
	str r0, [sp, #0x28]
	ldr r0, _02046200 ; =0x0000034F
	add r1, sp, #0x24
	str r0, [sp, #0x2c]
	ldr r0, _02046204 ; =0x00000231
	str r0, [sp, #0x30]
	mov r0, #0x1
	str r0, [sp, #0x34]
	add r0, r6, #0x0
	bl FUN_02049160
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_0204610A:
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_02046118:
	ldr r0, [r5, #0x38]
	mov r1, #0x1
	bl FUN_02046214
	add r0, r5, #0x0
	bl FUN_02046224
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r3, _02046208 ; =0x0000FFFF
	add r0, r6, #0x0
	mov r1, #0x3
	mov r2, #0x11
	bl FUN_0204C1B4
	ldr r0, _0204620C ; =0x00000679
	bl FUN_020054C8
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_02046150:
	ldr r0, _02046210 ; =0x021C48B8
	ldr r2, [r0, #0x48]
	mov r0, #0x3
	tst r0, r2
	beq _020461F8
	add r0, r1, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_02046160:
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r3, _02046208 ; =0x0000FFFF
	add r0, r6, #0x0
	mov r1, #0x3
	mov r2, #0x10
	bl FUN_0204C1B4
	ldr r0, _0204620C ; =0x00000679
	bl FUN_020054C8
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_0204618A:
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_02046198:
	bl FUN_0205F1D4
	ldrh r2, [r4, #0x6]
	ldrh r1, [r4, #0x4]
	mov r0, #0xa4
	str r0, [sp, #0x10]
	sub r0, #0xa5
	str r0, [sp, #0x14]
	mov r0, #0x0
	str r1, [sp, #0x18]
	str r0, [sp, #0x20]
	str r2, [sp, #0x1c]
	add r0, r6, #0x0
	add r1, sp, #0x10
	bl FUN_02049160
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_020461C0:
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_020461CE:
	ldr r0, [r5, #0x38]
	mov r1, #0x0
	bl FUN_02046214
	add r0, r6, #0x0
	bl FUN_0204B00C
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_020461E4:
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0206367C
	add sp, #0x38
	mov r0, #0x1
	pop {r4-r6, pc}
_020461F8:
	mov r0, #0x0
	add sp, #0x38
	pop {r4-r6, pc}
	nop
_02046200: .word 0x0000034F
_02046204: .word 0x00000231
_02046208: .word 0x0000FFFF
_0204620C: .word 0x00000679
_02046210: .word 0x021C48B8

	thumb_func_start FUN_02046214
FUN_02046214: ; 0x02046214
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020553A0
	add r1, r4, #0x0
	bl FUN_0205889C
	pop {r4, pc}

	thumb_func_start FUN_02046224
FUN_02046224: ; 0x02046224
	push {r3-r4, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	ldr r0, _02046278 ; =0x000008C1
	ldr r1, [r4, #0x20]
	bl FUN_0201EEF0
	ldr r0, _0204627C ; =0x000F81B8
	ldr r1, [r4, #0x20]
	bl FUN_0201EFE0
	ldr r0, _02046280 ; =0x0350523D
	str r0, [sp, #0x8]
	ldr r0, _02046284 ; =0x0015EDB7
	str r0, [sp, #0xc]
	ldr r0, _02046288 ; =0x023DA40E
	str r0, [sp, #0x10]
	ldr r1, [r4, #0x20]
	add r0, sp, #0x8
	bl FUN_0201F04C
	ldr r1, _0204628C ; =0x00000823
	add r0, sp, #0x0
	strh r1, [r0, #0x0]
	mov r1, #0x52
	lsl r1, r1, #0x4
	strh r1, [r0, #0x2]
	mov r1, #0x0
	strh r1, [r0, #0x4]
	ldr r1, [r4, #0x20]
	add r0, sp, #0x0
	bl FUN_0201EF90
	mov r0, #0x3
	ldr r1, _02046290 ; =0x0061C000
	ldr r2, [r4, #0x20]
	lsl r0, r0, #0xe
	bl FUN_0201EC94
	add sp, #0x14
	pop {r3-r4, pc}
	nop
_02046278: .word 0x000008C1
_0204627C: .word 0x000F81B8
_02046280: .word 0x0350523D
_02046284: .word 0x0015EDB7
_02046288: .word 0x023DA40E
_0204628C: .word 0x00000823
_02046290: .word 0x0061C000

	thumb_func_start FUN_02046294
FUN_02046294: ; 0x02046294
	mov r0, #0xeb
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_0204629C
FUN_0204629C: ; 0x0204629C
	ldr r3, _020462A8 ; =memset
	mov r2, #0xeb
	mov r1, #0x0
	lsl r2, r2, #0x2
	bx r3
	nop
_020462A8: .word memset

	thumb_func_start FUN_020462AC
FUN_020462AC: ; 0x020462AC
	ldr r3, _020462B4 ; =FUN_02022610
	mov r1, #0x4
	bx r3
	nop
_020462B4: .word FUN_02022610 

	thumb_func_start FUN_020462B8
FUN_020462B8: ; 0x020462B8
	push {r3-r5, lr}
	add r4, r1, #0x0
	bl FUN_02046338
	cmp r0, #0x0
	beq _020462DE
	lsr r3, r4, #0x1f
	lsl r2, r4, #0x1d
	ldrb r5, [r0, #0x0]
	sub r2, r2, r3
	mov r1, #0x1d
	ror r2, r1
	mov r0, #0x1
	add r1, r3, r2
	add r2, r0, #0x0
	lsl r2, r1
	add r1, r5, #0x0
	tst r1, r2
	bne _020462E0
_020462DE:
	mov r0, #0x0
_020462E0:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020462E4
FUN_020462E4: ; 0x020462E4
	push {r4-r6, lr}
	add r4, r1, #0x0
	bl FUN_02046338
	cmp r0, #0x0
	beq _02046308
	lsr r5, r4, #0x1f
	lsl r3, r4, #0x1d
	sub r3, r3, r5
	mov r2, #0x1d
	ror r3, r2
	mov r6, #0x1
	add r2, r5, r3
	add r3, r6, #0x0
	ldrb r1, [r0, #0x0]
	lsl r3, r2
	orr r1, r3
	strb r1, [r0, #0x0]
_02046308:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204630C
FUN_0204630C: ; 0x0204630C
	push {r4-r6, lr}
	add r4, r1, #0x0
	bl FUN_02046338
	cmp r0, #0x0
	beq _02046334
	lsr r5, r4, #0x1f
	lsl r3, r4, #0x1d
	sub r3, r3, r5
	mov r2, #0x1d
	ror r3, r2
	mov r6, #0x1
	add r2, r5, r3
	add r3, r6, #0x0
	lsl r3, r2
	mov r2, #0xff
	ldrb r1, [r0, #0x0]
	eor r2, r3
	and r1, r2
	strb r1, [r0, #0x0]
_02046334:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02046338
FUN_02046338: ; 0x02046338
	push {r3-r5, lr}
	add r5, r0, #0x0
	cmp r1, #0x0
	bne _02046344
	mov r0, #0x0
	pop {r3-r5, pc}
_02046344:
	mov r0, #0x1
	lsl r0, r0, #0xe
	cmp r1, r0
	bhs _02046364
	mov r0, #0x5b
	lsr r4, r1, #0x3
	lsl r0, r0, #0x2
	cmp r4, r0
	blt _0204635A
	bl ErrorHandling
_0204635A:
	mov r0, #0x9
	lsl r0, r0, #0x6
	add r0, r5, r0
	add r0, r0, r4
	pop {r3-r5, pc}
_02046364:
	sub r1, r1, r0
	asr r0, r1, #0x2
	lsr r0, r0, #0x1d
	add r0, r1, r0
	asr r4, r0, #0x3
	cmp r4, #0x8
	blt _02046376
	bl ErrorHandling
_02046376:
	ldr r0, _0204637C ; =0x021C5A14
	add r0, r0, r4
	pop {r3-r5, pc}
	.balign 4
_0204637C: .word 0x021C5A14

	thumb_func_start FUN_02046380
FUN_02046380: ; 0x02046380
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x1
	lsl r0, r0, #0xe
	sub r4, r1, r0
	mov r0, #0x12
	lsl r0, r0, #0x4
	cmp r4, r0
	blt _02046396
	bl ErrorHandling
_02046396:
	lsl r0, r4, #0x1
	add r0, r5, r0
	pop {r3-r5, pc}
