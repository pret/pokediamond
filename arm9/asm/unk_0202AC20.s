	.include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global UNK_021C59D4
UNK_021C59D4: ; 0x021C59D4
	.space 0x4

	.text

	thumb_func_start FUN_0202AC20
FUN_0202AC20: ; 0x0202AC20
	ldr r0, _0202AC24 ; =0x00001354
	bx lr
	.balign 4
_0202AC24: .word 0x00001354

	thumb_func_start FUN_0202AC28
FUN_0202AC28: ; 0x0202AC28
	bx lr
	.balign 4

	thumb_func_start FUN_0202AC2C
FUN_0202AC2C: ; 0x0202AC2C
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x8
	blt _0202AC3A
	bl ErrorHandling
_0202AC3A:
	mov r0, #0x1
	lsl r0, r0, #0x8
	add r6, r5, r0
	lsl r3, r4, #0x2
	ldr r2, [r6, r3]
	ldr r1, _0202AC60 ; =0xEDB88320
	cmp r2, r1
	bne _0202AC58
	add r0, #0x2c
	add r1, r5, r0
	lsl r0, r4, #0x6
	add r0, r4, r0
	lsl r0, r0, #0x2
	add r0, r1, r0
	pop {r4-r6, pc}
_0202AC58:
	mov r0, #0x0
	str r0, [r6, r3]
	pop {r4-r6, pc}
	nop
_0202AC60: .word 0xEDB88320

	thumb_func_start FUN_0202AC64
FUN_0202AC64: ; 0x0202AC64
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	blt _0202AC72
	bl ErrorHandling
_0202AC72:
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x12
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0202AC8E
	ldr r0, _0202AC94 ; =0x0000094C
	add r1, r5, r0
	mov r0, #0xd6
	lsl r0, r0, #0x2
	mul r0, r4
	add r0, r1, r0
	pop {r3-r5, pc}
_0202AC8E:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0202AC94: .word 0x0000094C

	thumb_func_start FUN_0202AC98
FUN_0202AC98: ; 0x0202AC98
	push {r3-r7, lr}
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	add r7, r2, #0x0
	bl FUN_0202ADF0
	cmp r0, #0x0
	bne _0202ACAC
	mov r0, #0x0
	pop {r3-r7, pc}
_0202ACAC:
	mov r0, #0x1
	mov r4, #0x0
	add r2, r5, #0x0
	lsl r0, r0, #0x8
_0202ACB4:
	ldr r1, [r2, r0]
	cmp r1, #0x0
	bne _0202ACF6
	lsl r0, r4, #0x6
	mov r2, #0x4b
	add r0, r4, r0
	lsl r2, r2, #0x2
	lsl r6, r0, #0x2
	add r1, r5, r2
	ldr r0, [sp, #0x0]
	add r1, r1, r6
	sub r2, #0x28
	bl MI_CpuCopy8
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x1
	ldr r2, _0202AD04 ; =0xEDB88320
	lsl r0, r0, #0x8
	str r2, [r1, r0]
	add r0, #0x2e
	add r1, r5, r0
	ldrh r0, [r1, r6]
	mov r2, #0x3
	bic r0, r2
	lsl r2, r7, #0x10
	lsr r3, r2, #0x10
	mov r2, #0x3
	and r2, r3
	orr r0, r2
	strh r0, [r1, r6]
	mov r0, #0x1
	pop {r3-r7, pc}
_0202ACF6:
	add r4, r4, #0x1
	add r2, r2, #0x4
	cmp r4, #0x8
	blt _0202ACB4
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0202AD04: .word 0xEDB88320

	thumb_func_start FUN_0202AD08
FUN_0202AD08: ; 0x0202AD08
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	bl FUN_0202AE0C
	cmp r0, #0x0
	bne _0202AD1A
	mov r0, #0x0
	pop {r4-r6, pc}
_0202AD1A:
	ldr r0, _0202AD88 ; =0x00000152
	ldrb r0, [r6, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	bne _0202AD34
	add r0, r5, #0x0
	bl FUN_0202ADF0
	cmp r0, #0x0
	bne _0202AD34
	mov r0, #0x0
	pop {r4-r6, pc}
_0202AD34:
	mov r0, #0x12
	mov r4, #0x0
	add r2, r5, #0x0
	lsl r0, r0, #0x4
_0202AD3C:
	ldr r1, [r2, r0]
	cmp r1, #0x0
	bne _0202AD7C
	ldr r1, _0202AD8C ; =0x0000094C
	mov r2, #0xd6
	add r3, r5, r1
	lsl r2, r2, #0x2
	add r1, r4, #0x0
	mul r1, r2
	add r0, r6, #0x0
	add r1, r3, r1
	bl MI_CpuCopy8
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x12
	ldr r2, _0202AD90 ; =0xEDB88320
	lsl r0, r0, #0x4
	str r2, [r1, r0]
	add r0, #0x32
	ldrb r0, [r6, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	bne _0202AD78
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x1
	bl FUN_0202AC98
_0202AD78:
	mov r0, #0x1
	pop {r4-r6, pc}
_0202AD7C:
	add r4, r4, #0x1
	add r2, r2, #0x4
	cmp r4, #0x3
	blt _0202AD3C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_0202AD88: .word 0x00000152
_0202AD8C: .word 0x0000094C
_0202AD90: .word 0xEDB88320

	thumb_func_start FUN_0202AD94
FUN_0202AD94: ; 0x0202AD94
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	sub r0, r4, #0x1
	cmp r0, #0x8
	blt _0202ADA4
	bl ErrorHandling
_0202ADA4:
	sub r4, r4, #0x1
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x1
	mov r2, #0x0
	lsl r0, r0, #0x8
	str r2, [r1, r0]
	add r0, #0x2e
	add r3, r5, r0
	lsl r0, r4, #0x6
	add r0, r4, r0
	lsl r2, r0, #0x2
	ldrh r1, [r3, r2]
	mov r0, #0x3
	bic r1, r0
	strh r1, [r3, r2]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0202ADC8
FUN_0202ADC8: ; 0x0202ADC8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	blt _0202ADD6
	bl ErrorHandling
_0202ADD6:
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x12
	mov r2, #0x0
	lsl r0, r0, #0x4
	str r2, [r1, r0]
	add r0, r5, #0x0
	add r1, r4, #0x1
	bl FUN_0202AEC4
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202ADF0
FUN_0202ADF0: ; 0x0202ADF0
	mov r1, #0x1
	mov r3, #0x0
	lsl r1, r1, #0x8
_0202ADF6:
	ldr r2, [r0, r1]
	cmp r2, #0x0
	bne _0202AE00
	mov r0, #0x1
	bx lr
_0202AE00:
	add r3, r3, #0x1
	add r0, r0, #0x4
	cmp r3, #0x8
	blt _0202ADF6
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0202AE0C
FUN_0202AE0C: ; 0x0202AE0C
	mov r1, #0x12
	mov r3, #0x0
	lsl r1, r1, #0x4
_0202AE12:
	ldr r2, [r0, r1]
	cmp r2, #0x0
	bne _0202AE1C
	mov r0, #0x1
	bx lr
_0202AE1C:
	add r3, r3, #0x1
	add r0, r0, #0x4
	cmp r3, #0x3
	blt _0202AE12
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0202AE28
FUN_0202AE28: ; 0x0202AE28
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x8
	blt _0202AE36
	bl ErrorHandling
_0202AE36:
	lsl r0, r5, #0x2
	add r1, r4, r0
	mov r0, #0x1
	lsl r0, r0, #0x8
	ldr r0, [r1, r0]
	cmp r0, #0x0
	bne _0202AE48
	mov r0, #0x0
	pop {r3-r5, pc}
_0202AE48:
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AE4C
FUN_0202AE4C: ; 0x0202AE4C
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x3
	blt _0202AE5A
	bl ErrorHandling
_0202AE5A:
	lsl r0, r5, #0x2
	add r1, r4, r0
	mov r0, #0x12
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	bne _0202AE6C
	mov r0, #0x0
	pop {r3-r5, pc}
_0202AE6C:
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AE70
FUN_0202AE70: ; 0x0202AE70
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_0202AE76:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202AE4C
	cmp r0, #0x1
	bne _0202AE86
	mov r0, #0x1
	pop {r3-r5, pc}
_0202AE86:
	add r4, r4, #0x1
	cmp r4, #0x3
	blt _0202AE76
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AE90
FUN_0202AE90: ; 0x0202AE90
	push {r3-r4}
	cmp r1, #0x0
	beq _0202AEB8
	ldr r2, _0202AEC0 ; =0x0000012E
	mov r3, #0x0
	add r4, r0, r2
	add r0, r2, #0x0
	sub r0, #0x2a
_0202AEA0:
	ldrh r2, [r4, #0x0]
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x1e
	cmp r1, r2
	bne _0202AEB0
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_0202AEB0:
	add r3, r3, #0x1
	add r4, r4, r0
	cmp r3, #0x8
	blt _0202AEA0
_0202AEB8:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	nop
_0202AEC0: .word 0x0000012E

	thumb_func_start FUN_0202AEC4
FUN_0202AEC4: ; 0x0202AEC4
	push {r3-r5, lr}
	cmp r1, #0x0
	beq _0202AEEE
	ldr r3, _0202AEF0 ; =0x0000012E
	mov r4, #0x41
	mov r2, #0x0
	add r3, r0, r3
	lsl r4, r4, #0x2
_0202AED4:
	ldrh r5, [r3, #0x0]
	lsl r5, r5, #0x1e
	lsr r5, r5, #0x1e
	cmp r1, r5
	bne _0202AEE6
	add r1, r2, #0x1
	bl FUN_0202AD94
	pop {r3-r5, pc}
_0202AEE6:
	add r2, r2, #0x1
	add r3, r3, r4
	cmp r2, #0x8
	blt _0202AED4
_0202AEEE:
	pop {r3-r5, pc}
	.balign 4
_0202AEF0: .word 0x0000012E

	thumb_func_start FUN_0202AEF4
FUN_0202AEF4: ; 0x0202AEF4
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x2
	add r4, r1, #0x0
	lsl r0, r0, #0xa
	cmp r4, r0
	blt _0202AF06
	bl ErrorHandling
_0202AF06:
	mov r0, #0x1
	mov r1, #0x7
	add r2, r4, #0x0
	and r2, r1
	add r1, r0, #0x0
	lsl r1, r2
	asr r2, r4, #0x2
	lsr r2, r2, #0x1d
	add r2, r4, r2
	asr r2, r2, #0x3
	ldrb r2, [r5, r2]
	tst r1, r2
	bne _0202AF22
	mov r0, #0x0
_0202AF22:
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AF24
FUN_0202AF24: ; 0x0202AF24
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x2
	add r4, r1, #0x0
	lsl r0, r0, #0xa
	cmp r4, r0
	blt _0202AF36
	bl ErrorHandling
_0202AF36:
	asr r0, r4, #0x2
	lsr r0, r0, #0x1d
	add r0, r4, r0
	asr r0, r0, #0x3
	mov r1, #0x7
	ldrb r3, [r5, r0]
	mov r2, #0x1
	and r1, r4
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strb r1, [r5, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AF50
FUN_0202AF50: ; 0x0202AF50
	ldr r3, _0202AF58 ; =FUN_0202AEF4
	ldr r1, _0202AF5C ; =0x000007FF
	bx r3
	nop
_0202AF58: .word FUN_0202AEF4
_0202AF5C: .word 0x000007FF

	thumb_func_start FUN_0202AF60
FUN_0202AF60: ; 0x0202AF60
	ldr r3, _0202AF68 ; =FUN_0202AF24
	ldr r1, _0202AF6C ; =0x000007FF
	bx r3
	nop
_0202AF68: .word FUN_0202AF24
_0202AF6C: .word 0x000007FF

	thumb_func_start FUN_0202AF70
FUN_0202AF70: ; 0x0202AF70
	push {r3, lr}
	ldr r1, _0202AF84 ; =UNK_021C59D4
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _0202AF82
	bl FUN_0202251C
	ldr r1, _0202AF84 ; =UNK_021C59D4
	str r0, [r1, #0x0]
_0202AF82:
	pop {r3, pc}
	.balign 4
_0202AF84: .word UNK_021C59D4

	thumb_func_start FUN_0202AF88
FUN_0202AF88: ; 0x0202AF88
	ldr r0, _0202AF98 ; =UNK_021C59D4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202AF94
	mov r1, #0x0
	str r1, [r0, #0x0]
_0202AF94:
	bx lr
	nop
_0202AF98: .word UNK_021C59D4

	thumb_func_start FUN_0202AF9C
FUN_0202AF9C: ; 0x0202AF9C
	push {r3-r5, lr}
	ldr r4, _0202AFBC ; =UNK_021C59D4
	mov r5, #0x0
_0202AFA2:
	ldr r0, [r4, #0x0]
	add r1, r5, #0x0
	bl FUN_0202AE28
	cmp r0, #0x1
	bne _0202AFB2
	add r0, r5, #0x1
	pop {r3-r5, pc}
_0202AFB2:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0202AFA2
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0202AFBC: .word UNK_021C59D4

	thumb_func_start FUN_0202AFC0
FUN_0202AFC0: ; 0x0202AFC0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0202AFCA
	mov r0, #0x0
	pop {r4, pc}
_0202AFCA:
	sub r0, r4, #0x1
	cmp r0, #0x8
	blt _0202AFD4
	bl ErrorHandling
_0202AFD4:
	ldr r0, _0202AFF8 ; =UNK_021C59D4
	sub r1, r4, #0x1
	ldr r0, [r0, #0x0]
	bl FUN_0202AE28
	cmp r0, #0x1
	bne _0202AFF4
	ldr r0, _0202AFF8 ; =UNK_021C59D4
	sub r1, r4, #0x1
	ldr r0, [r0, #0x0]
	bl FUN_0202AC2C
	cmp r0, #0x0
	beq _0202AFF4
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
_0202AFF4:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0202AFF8: .word UNK_021C59D4

	thumb_func_start FUN_0202AFFC
FUN_0202AFFC: ; 0x0202AFFC
	cmp r0, #0x0
	beq _0202B016
	ldr r1, _0202B01C ; =UNK_021C59D4
	ldr r2, [r1, #0x0]
	mov r1, #0x13
	lsl r1, r1, #0x4
	add r2, r2, r1
	sub r1, r0, #0x1
	lsl r0, r1, #0x6
	add r0, r1, r0
	lsl r0, r0, #0x2
	add r0, r2, r0
	bx lr
_0202B016:
	mov r0, #0x0
	bx lr
	nop
_0202B01C: .word UNK_021C59D4

	thumb_func_start FUN_0202B020
FUN_0202B020: ; 0x0202B020
	add r1, r0, #0x0
	ldr r0, _0202B02C ; =UNK_021C59D4
	ldr r3, _0202B030 ; =FUN_0202AD94
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0202B02C: .word UNK_021C59D4
_0202B030: .word FUN_0202AD94
