    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0200BB14
FUN_0200BB14: ; 0x0200BB14
	push {r4, lr}
	mov r1, #0x4e
	lsl r1, r1, #0x2
	add r4, r0, #0x0
	bl AllocFromHeap
	cmp r0, #0x0
	bne _0200BB28
	mov r0, #0x0
	pop {r4, pc}
_0200BB28:
	str r4, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	mov r1, #0x1
	str r1, [r0, #0x8]
	pop {r4, pc}

	thumb_func_start FUN_0200BB34
FUN_0200BB34: ; 0x0200BB34
	push {r4, lr}
	add r4, r0, #0x0
	bne _0200BB3E
	bl ErrorHandling
_0200BB3E:
	ldr r0, [r4, #0x0]
	mov r1, #0x58
	bl AllocFromHeap
	cmp r0, #0x0
	bne _0200BB4E
	mov r0, #0x0
	pop {r4, pc}
_0200BB4E:
	ldr r1, [r4, #0x4]
	mov r2, #0x0
	add r1, r1, #0x1
	str r1, [r4, #0x4]
	add r3, r0, #0x0
	add r1, r2, #0x0
_0200BB5A:
	add r2, r2, #0x1
	str r1, [r3, #0xc]
	add r3, r3, #0x4
	cmp r2, #0x6
	blt _0200BB5A
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200BB68
FUN_0200BB68: ; 0x0200BB68
	add r0, #0x10
	bx lr

	thumb_func_start FUN_0200BB6C
FUN_0200BB6C: ; 0x0200BB6C
	push {r4-r7, lr}
	sub sp, #0x24
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r5, #0x0
	bne _0200BB80
	bl ErrorHandling
_0200BB80:
	cmp r5, #0x0
	bne _0200BB8A
	add sp, #0x24
	mov r0, #0x0
	pop {r4-r7, pc}
_0200BB8A:
	ldr r0, [r6, #0x0]
	str r0, [sp, #0x14]
	ldr r0, [r6, #0x4]
	str r0, [sp, #0x18]
	ldr r0, [r6, #0x8]
	str r0, [sp, #0x1c]
	ldr r0, [r5, #0x0]
	str r0, [sp, #0x20]
	ldr r1, [r6, #0xc]
	ldr r2, [r6, #0x10]
	add r0, sp, #0x14
	bl FUN_0201D060
	ldr r1, [r5, #0x0]
	add r0, r7, #0x0
	bl FUN_0201E00C
	bl NNS_G2dInitOamManagerModule
	ldr r0, [r5, #0x8]
	cmp r0, #0x1
	bne _0200BBD6
	ldr r0, [r4, #0x10]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x1c]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x0]
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	ldr r3, [r4, #0xc]
	bl FUN_02009EAC
_0200BBD6:
	ldr r1, [r5, #0x0]
	mov r0, #0x20
	bl FUN_0201C328
	str r0, [r5, #0xc]
	bl FUN_0201D168
	bl FUN_0201E0BC
	mov r0, #0x1
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0200BBF0
FUN_0200BBF0: ; 0x0200BBF0
	push {r4, lr}
	add r3, r0, #0x0
	add r4, r1, #0x0
	cmp r3, #0x0
	beq _0200BBFE
	cmp r4, #0x0
	bne _0200BC02
_0200BBFE:
	mov r0, #0x0
	pop {r4, pc}
_0200BC02:
	add r0, r2, #0x0
	add r1, r3, #0x0
	ldr r2, [r3, #0x0]
	add r1, #0x10
	bl FUN_02008C9C
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0200BC14
FUN_0200BC14: ; 0x0200BC14
	ldr r3, _0200BC18 ; =FUN_0201FFC8
	bx r3
	.balign 4
_0200BC18: .word FUN_0201FFC8

	thumb_func_start FUN_0200BC1C
FUN_0200BC1C: ; 0x0200BC1C
	push {r4, lr}
	add r4, r0, #0x0
	bne _0200BC26
	bl ErrorHandling
_0200BC26:
	ldr r0, [r4, #0x0]
	bl FUN_0201FDEC
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200BC30
FUN_0200BC30: ; 0x0200BC30
	ldr r3, _0200BC34 ; =FUN_02009F80
	bx r3
	.balign 4
_0200BC34: .word FUN_02009F80

	thumb_func_start FUN_0200BC38
FUN_0200BC38: ; 0x0200BC38
	ldr r3, _0200BC3C ; =FUN_0201C348
	bx r3
	.balign 4
_0200BC3C: .word FUN_0201C348

	thumb_func_start FUN_0200BC40
FUN_0200BC40: ; 0x0200BC40
	ldr r3, _0200BC48 ; =FUN_0201FD58
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200BC48: .word FUN_0201FD58

	thumb_func_start FUN_0200BC4C
FUN_0200BC4C: ; 0x0200BC4C
	push {r3, lr}
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0200BC58
	bl FUN_02008C80
_0200BC58:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0200BC5C
FUN_0200BC5C: ; 0x0200BC5C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x54]
	mov r4, #0x0
	cmp r0, #0x0
	ble _0200BC7C
_0200BC68:
	ldr r0, [r5, #0x8]
	add r1, r4, #0x0
	bl FUN_02009660
	bl FUN_020096B4
	ldr r0, [r5, #0x54]
	add r4, r4, #0x1
	cmp r4, r0
	blt _0200BC68
_0200BC7C:
	ldr r0, [r5, #0x8]
	bl FreeToHeap
	ldr r0, [r5, #0x24]
	bl FUN_02009C30
	ldr r0, [r5, #0x28]
	bl FUN_02009E28
	ldr r0, [r5, #0x54]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0200BCAE
	add r4, r5, #0x0
_0200BC98:
	ldr r0, [r4, #0x24]
	bl FUN_02009448
	ldr r0, [r4, #0xc]
	bl FUN_02008E2C
	ldr r0, [r5, #0x54]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _0200BC98
_0200BCAE:
	pop {r4-r6, pc}

	thumb_func_start FUN_0200BCB0
FUN_0200BCB0: ; 0x0200BCB0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0201C350
	bl FUN_0201D12C
	bl FUN_0201E08C
	ldr r0, [r4, #0x8]
	cmp r0, #0x1
	bne _0200BCCC
	bl FUN_02009FA0
_0200BCCC:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200BCD0
FUN_0200BCD0: ; 0x0200BCD0
	ldr r2, [r0, #0x4]
	ldr r3, _0200BCDC ; =FreeToHeap
	sub r2, r2, #0x1
	str r2, [r0, #0x4]
	add r0, r1, #0x0
	bx r3
	.balign 4
_0200BCDC: .word FreeToHeap

	thumb_func_start FUN_0200BCE0
FUN_0200BCE0: ; 0x0200BCE0
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0200BC40
	add r0, r4, #0x0
	bl FUN_0200BC4C
	add r0, r4, #0x0
	bl FUN_0200BC5C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0200BCD0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0200BD04
FUN_0200BD04: ; 0x0200BD04
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0200BD12
	bl ErrorHandling
_0200BD12:
	add r0, r4, #0x0
	bl FUN_0200BCB0
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start FUN_0200BD20
FUN_0200BD20: ; 0x0200BD20
	push {r4-r7, lr}
	sub sp, #0x24
	add r5, r0, #0x0
	mov r0, #0x6
	add r4, r1, #0x0
	str r2, [sp, #0x10]
	str r0, [sp, #0x14]
	cmp r5, #0x0
	beq _0200BD36
	cmp r4, #0x0
	bne _0200BD3C
_0200BD36:
	add sp, #0x24
	mov r0, #0x0
	pop {r4-r7, pc}
_0200BD3C:
	add r0, r2, #0x0
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	bne _0200BD48
	mov r0, #0x4
	str r0, [sp, #0x14]
_0200BD48:
	ldr r0, [sp, #0x14]
	str r0, [r4, #0x54]
	bl FUN_0200965C
	add r2, r0, #0x0
	ldr r1, [sp, #0x14]
	ldr r0, [r5, #0x0]
	mul r1, r2
	bl AllocFromHeap
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x14]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0200BD94
	ldr r6, [sp, #0x10]
_0200BD68:
	ldr r0, [r4, #0x8]
	add r1, r7, #0x0
	bl FUN_02009660
	str r0, [sp, #0x18]
	ldr r0, [r5, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_020161A4
	ldr r1, [sp, #0x18]
	ldr r2, [r5, #0x0]
	str r0, [sp, #0x1c]
	bl FUN_02009668
	ldr r0, [sp, #0x1c]
	bl FreeToHeap
	ldr r0, [sp, #0x14]
	add r7, r7, #0x1
	add r6, r6, #0x4
	cmp r7, r0
	blt _0200BD68
_0200BD94:
	ldr r0, [sp, #0x14]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0200BDBE
	add r7, r4, #0x0
_0200BD9E:
	ldr r0, [r4, #0x8]
	add r1, r6, #0x0
	bl FUN_02009660
	bl FUN_020096CC
	ldr r2, [r5, #0x0]
	add r1, r6, #0x0
	bl FUN_02008DEC
	str r0, [r7, #0xc]
	ldr r0, [sp, #0x14]
	add r6, r6, #0x1
	add r7, r7, #0x4
	cmp r6, r0
	blt _0200BD9E
_0200BDBE:
	ldr r0, [sp, #0x14]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0200BDF6
	add r6, r4, #0x0
_0200BDC8:
	ldr r0, [r4, #0x8]
	add r1, r7, #0x0
	bl FUN_02009660
	str r0, [sp, #0x20]
	bl FUN_020096CC
	ldr r1, [r5, #0x0]
	bl FUN_02009424
	add r2, r0, #0x0
	str r2, [r6, #0x24]
	ldr r0, [r6, #0xc]
	ldr r1, [sp, #0x20]
	ldr r3, [r5, #0x0]
	bl FUN_020093A8
	str r0, [r6, #0x3c]
	ldr r0, [sp, #0x14]
	add r7, r7, #0x1
	add r6, r6, #0x4
	cmp r7, r0
	blt _0200BDC8
_0200BDF6:
	ldr r0, [r4, #0x24]
	bl FUN_02009A90
	ldr r0, [r4, #0x28]
	bl FUN_02009D34
	ldr r1, [sp, #0x10]
	ldr r0, [r5, #0x0]
	ldr r1, [r1, #0x18]
	bl FUN_020161A4
	ldr r1, [r4, #0x14]
	add r6, r0, #0x0
	str r1, [sp, #0x0]
	ldr r1, [r4, #0x18]
	str r1, [sp, #0x4]
	ldr r1, [r4, #0x1c]
	str r1, [sp, #0x8]
	ldr r1, [r4, #0x20]
	str r1, [sp, #0xc]
	ldr r1, [r5, #0x0]
	ldr r2, [r4, #0xc]
	ldr r3, [r4, #0x10]
	bl FUN_02008BE0
	str r0, [r4, #0x4]
	add r0, r6, #0x0
	bl FreeToHeap
	mov r0, #0x1
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0200BE38
FUN_0200BE38: ; 0x0200BE38
	push {r4, lr}
	sub sp, #0x28
	mov r3, #0x4
	mov r4, #0x6
	ldrsh r3, [r2, r3]
	ldrsh r4, [r2, r4]
	str r4, [sp, #0x0]
	str r3, [sp, #0x4]
	ldrh r4, [r2, #0xa]
	str r4, [sp, #0x8]
	ldr r4, [r2, #0xc]
	str r4, [sp, #0xc]
	ldr r4, [r2, #0x10]
	str r4, [sp, #0x10]
	ldr r4, [r2, #0x14]
	str r4, [sp, #0x14]
	ldr r4, [r2, #0x18]
	str r4, [sp, #0x18]
	ldr r4, [r2, #0x1c]
	str r4, [sp, #0x1c]
	ldr r4, [r2, #0x20]
	str r4, [sp, #0x20]
	ldr r4, [r2, #0x24]
	str r4, [sp, #0x24]
	ldr r2, [r2, #0x0]
	bl FUN_0200BE74
	add sp, #0x28
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200BE74
FUN_0200BE74: ; 0x0200BE74
	push {r4, lr}
	sub sp, #0x30
	add r4, r0, #0x0
	ldr r0, [r1, #0x0]
	str r0, [sp, #0x0]
	ldr r0, [r1, #0x4]
	ldr r1, [r0, #0x0]
	mov r0, #0x24
	mul r0, r2
	add r0, r1, r0
	str r0, [sp, #0x4]
	cmp r3, #0x0
	ble _0200BEA0
	lsl r0, r3, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0200BEAE
_0200BEA0:
	lsl r0, r3, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0200BEAE:
	bl _ffix
	str r0, [sp, #0x8]
	add r1, sp, #0x28
	mov r0, #0x10
	ldrsh r0, [r1, r0]
	cmp r0, #0x0
	ble _0200BED0
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0200BEDE
_0200BED0:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0200BEDE:
	bl _ffix
	str r0, [sp, #0xc]
	add r1, sp, #0x28
	mov r0, #0x14
	ldrsh r0, [r1, r0]
	cmp r0, #0x0
	ble _0200BF00
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0200BF0E
_0200BF00:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0200BF0E:
	bl _ffix
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x4c]
	cmp r0, #0x2
	bne _0200BF24
	mov r0, #0x3
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0x12
	add r0, r1, r0
	str r0, [sp, #0xc]
_0200BF24:
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	mov r1, #0x0
	add r0, sp, #0x0
	strh r1, [r0, #0x20]
	ldr r0, [sp, #0x44]
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x4c]
	str r0, [sp, #0x28]
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x2c]
	add r0, sp, #0x0
	bl FUN_0201FE94
	add r4, r0, #0x0
	beq _0200BF5A
	add r1, sp, #0x28
	ldrh r1, [r1, #0x18]
	bl FUN_02020130
	ldr r1, [sp, #0x48]
	add r0, r4, #0x0
	bl FUN_02020248
_0200BF5A:
	add r0, r4, #0x0
	add sp, #0x30
	pop {r4, pc}

	thumb_func_start FUN_0200BF60
FUN_0200BF60: ; 0x0200BF60
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	add r5, r1, #0x0
	add r6, r2, #0x0
	cmp r0, #0x0
	beq _0200BF78
	cmp r5, #0x0
	bne _0200BF7E
_0200BF78:
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0200BF7E:
	ldr r0, [r6, #0x10]
	cmp r0, #0x0
	beq _0200BF8A
	ldr r0, [r6, #0x14]
	cmp r0, #0x0
	bne _0200BF8E
_0200BF8A:
	mov r0, #0x4
	str r0, [sp, #0x4]
_0200BF8E:
	ldr r0, [sp, #0x4]
	str r0, [r5, #0x54]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0200BFBE
	add r7, r6, #0x0
	add r4, r5, #0x0
_0200BFA0:
	ldr r2, [sp, #0x0]
	ldr r0, [r7, #0x0]
	ldr r1, [sp, #0x8]
	ldr r2, [r2, #0x0]
	bl FUN_02008DEC
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x8]
	add r7, r7, #0x4
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	add r4, r4, #0x4
	str r1, [sp, #0x8]
	cmp r1, r0
	blt _0200BFA0
_0200BFBE:
	ldr r0, [sp, #0x4]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0200C004
	add r4, r7, #0x0
_0200BFC8:
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _0200BFF8
	ldr r1, [sp, #0x0]
	ldr r1, [r1, #0x0]
	bl FUN_02009424
	str r0, [r5, #0x24]
	mov r0, #0x0
	str r0, [r5, #0x3c]
	ldr r3, [r5, #0x24]
	add r1, r0, #0x0
	ldr r0, [r3, #0x4]
	cmp r0, #0x0
	ble _0200BFF8
	add r2, r1, #0x0
_0200BFE8:
	ldr r0, [r3, #0x0]
	add r1, r1, #0x1
	str r4, [r0, r2]
	ldr r3, [r5, #0x24]
	add r2, r2, #0x4
	ldr r0, [r3, #0x4]
	cmp r1, r0
	blt _0200BFE8
_0200BFF8:
	ldr r0, [sp, #0x4]
	add r7, r7, #0x1
	add r6, r6, #0x4
	add r5, r5, #0x4
	cmp r7, r0
	blt _0200BFC8
_0200C004:
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0200C00C
FUN_0200C00C: ; 0x0200C00C
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	ldr r1, [sp, #0x28]
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_0200945C
	cmp r0, #0x0
	bne _0200C02A
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0200C02A:
	ldr r0, [sp, #0x28]
	ldr r3, [sp, #0x20]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	add r1, r6, #0x0
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r2, r7, #0x0
	str r0, [sp, #0x8]
	ldr r0, [r4, #0xc]
	bl FUN_02008F34
	add r5, r0, #0x0
	beq _0200C058
	bl FUN_02009B04
	ldr r0, [r4, #0x24]
	add r1, r5, #0x0
	bl FUN_0200C474
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0200C058:
	bl ErrorHandling
	cmp r5, #0x0
	beq _0200C066
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0200C066:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0200C06C
FUN_0200C06C: ; 0x0200C06C
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #0x34]
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_0200945C
	cmp r0, #0x0
	bne _0200C08C
	mov r0, #0x0
	add sp, #0x10
	mvn r0, r0
	pop {r3-r7, pc}
_0200C08C:
	ldr r0, [sp, #0x34]
	ldr r3, [sp, #0x28]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x30]
	add r1, r6, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x2c]
	add r2, r7, #0x0
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x0]
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x10]
	bl FUN_02008FEC
	add r5, r0, #0x0
	beq _0200C0D0
	bl FUN_02009D68
	cmp r0, #0x1
	beq _0200C0B8
	bl ErrorHandling
_0200C0B8:
	ldr r0, [r4, #0x28]
	add r1, r5, #0x0
	bl FUN_0200C474
	ldr r1, [sp, #0x30]
	add r0, r5, #0x0
	bl FUN_02009E88
	lsl r0, r0, #0x18
	add sp, #0x10
	asr r0, r0, #0x18
	pop {r3-r7, pc}
_0200C0D0:
	bl ErrorHandling
	mov r0, #0x0
	mvn r0, r0
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_0200C0DC
FUN_0200C0DC: ; 0x0200C0DC
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [sp, #0x28]
	add r6, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x2c]
	add r1, r3, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x30]
	ldr r3, [sp, #0x24]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x34]
	str r0, [sp, #0xc]
	add r0, r2, #0x0
	ldr r2, [sp, #0x20]
	bl FUN_0200C06C
	add r4, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	beq _0200C11A
	ldr r3, [sp, #0x2c]
	lsl r2, r4, #0x14
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x10
	lsl r3, r3, #0x5
	bl FUN_02003108
_0200C11A:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200C124
FUN_0200C124: ; 0x0200C124
	push {r3-r4, lr}
	sub sp, #0xc
	ldr r4, [sp, #0x18]
	str r4, [sp, #0x0]
	mov r4, #0x2
	str r4, [sp, #0x4]
	ldr r4, [sp, #0x1c]
	str r4, [sp, #0x8]
	bl FUN_0200C404
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0200C13C
FUN_0200C13C: ; 0x0200C13C
	push {r3-r4, lr}
	sub sp, #0xc
	ldr r4, [sp, #0x18]
	str r4, [sp, #0x0]
	mov r4, #0x3
	str r4, [sp, #0x4]
	ldr r4, [sp, #0x1c]
	str r4, [sp, #0x8]
	bl FUN_0200C404
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0200C154
FUN_0200C154: ; 0x0200C154
	push {r4-r7, lr}
	sub sp, #0x74
	add r7, r0, #0x0
	ldr r0, [r7, #0x0]
	add r6, r1, #0x0
	mov r1, #0x10
	add r5, r2, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	bne _0200C170
	add sp, #0x74
	mov r0, #0x0
	pop {r4-r7, pc}
_0200C170:
	ldr r0, [r7, #0x0]
	mov r1, #0x8
	bl AllocFromHeap
	str r0, [r4, #0x8]
	cmp r0, #0x0
	bne _0200C184
	add sp, #0x74
	mov r0, #0x0
	pop {r4-r7, pc}
_0200C184:
	ldr r0, [r7, #0x0]
	mov r1, #0x24
	bl AllocFromHeap
	ldr r1, [r4, #0x8]
	str r0, [r1, #0x0]
	ldr r0, [r4, #0x8]
	ldr r0, [r0, #0x0]
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x8]
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	bne _0200C1AC
	cmp r0, #0x0
	beq _0200C1A6
	bl FreeToHeap
_0200C1A6:
	add sp, #0x74
	mov r0, #0x0
	pop {r4-r7, pc}
_0200C1AC:
	mov r1, #0x0
	add r2, r5, #0x0
	add r3, sp, #0x2c
_0200C1B2:
	ldr r0, [r2, #0x14]
	add r1, r1, #0x1
	add r2, r2, #0x4
	stmia r3!, {r0}
	cmp r1, #0x6
	blt _0200C1B2
	ldr r0, [r6, #0x1c]
	cmp r0, #0x0
	beq _0200C1CA
	ldr r1, [r6, #0x20]
	cmp r1, #0x0
	bne _0200C1D4
_0200C1CA:
	mov r0, #0x0
	mvn r0, r0
	str r0, [sp, #0x3c]
	str r0, [sp, #0x40]
	b _0200C206
_0200C1D4:
	mov r2, #0x0
	ldr r1, [sp, #0x3c]
	mvn r2, r2
	cmp r1, r2
	beq _0200C1EC
	bl FUN_0200945C
	cmp r0, #0x0
	bne _0200C1EC
	mov r0, #0x0
	mvn r0, r0
	str r0, [sp, #0x3c]
_0200C1EC:
	mov r0, #0x0
	ldr r1, [sp, #0x40]
	mvn r0, r0
	cmp r1, r0
	beq _0200C206
	ldr r0, [r6, #0x20]
	bl FUN_0200945C
	cmp r0, #0x0
	bne _0200C206
	mov r0, #0x0
	mvn r0, r0
	str r0, [sp, #0x40]
_0200C206:
	ldr r0, [sp, #0x38]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x3c]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x40]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x30]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x2c]
	str r0, [sp, #0x10]
	ldr r0, [r6, #0xc]
	str r0, [sp, #0x14]
	ldr r0, [r6, #0x10]
	str r0, [sp, #0x18]
	ldr r0, [r6, #0x14]
	str r0, [sp, #0x1c]
	ldr r0, [r6, #0x18]
	str r0, [sp, #0x20]
	ldr r0, [r6, #0x1c]
	str r0, [sp, #0x24]
	ldr r0, [r6, #0x20]
	str r0, [sp, #0x28]
	ldr r0, [r4, #0x4]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x30]
	ldr r3, [sp, #0x34]
	bl FUN_02008AA4
	ldr r0, [r6, #0x0]
	str r0, [sp, #0x44]
	ldr r0, [r4, #0x4]
	str r0, [sp, #0x48]
	mov r0, #0x0
	ldrsh r0, [r5, r0]
	cmp r0, #0x0
	ble _0200C260
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0200C26E
_0200C260:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0200C26E:
	bl _ffix
	str r0, [sp, #0x4c]
	mov r0, #0x2
	ldrsh r0, [r5, r0]
	cmp r0, #0x0
	ble _0200C28E
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0200C29C
_0200C28E:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0200C29C:
	bl _ffix
	str r0, [sp, #0x50]
	mov r0, #0x4
	ldrsh r0, [r5, r0]
	cmp r0, #0x0
	ble _0200C2BC
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0200C2CA
_0200C2BC:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0200C2CA:
	bl _ffix
	str r0, [sp, #0x54]
	ldr r0, [r5, #0x10]
	cmp r0, #0x2
	bne _0200C2E0
	mov r0, #0x3
	ldr r1, [sp, #0x50]
	lsl r0, r0, #0x12
	add r0, r1, r0
	str r0, [sp, #0x50]
_0200C2E0:
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [sp, #0x58]
	str r0, [sp, #0x5c]
	str r0, [sp, #0x60]
	mov r1, #0x0
	add r0, sp, #0x2c
	strh r1, [r0, #0x38]
	ldr r0, [r5, #0x8]
	str r0, [sp, #0x68]
	ldr r0, [r5, #0x10]
	str r0, [sp, #0x6c]
	ldr r0, [r7, #0x0]
	str r0, [sp, #0x70]
	add r0, sp, #0x44
	bl FUN_0201FE94
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x30]
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0200C328
	bl FUN_020202A0
	add r6, r0, #0x0
	ldrh r1, [r5, #0x6]
	ldr r0, [r4, #0x0]
	bl FUN_02020130
	ldr r1, [r5, #0xc]
	ldr r0, [r4, #0x0]
	add r1, r6, r1
	bl FUN_02020248
	b _0200C32C
_0200C328:
	bl ErrorHandling
_0200C32C:
	add r0, r4, #0x0
	add sp, #0x74
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0200C334
FUN_0200C334: ; 0x0200C334
	push {r3, lr}
	ldr r0, [r0, #0x10]
	bl FUN_020094F0
	mov r1, #0x0
	bl FUN_02009E54
	pop {r3, pc}

	thumb_func_start FUN_0200C344
FUN_0200C344: ; 0x0200C344
	push {r4, lr}
	ldr r0, [r0, #0x10]
	add r4, r2, #0x0
	bl FUN_020094F0
	add r1, r4, #0x0
	bl FUN_02009E88
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200C358
FUN_0200C358: ; 0x0200C358
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldr r0, [r3, #0xc]
	ldr r1, [r3, #0x24]
	ldr r3, _0200C364 ; =FUN_0200C4F4
	bx r3
	.balign 4
_0200C364: .word FUN_0200C4F4

	thumb_func_start FUN_0200C368
FUN_0200C368: ; 0x0200C368
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldr r0, [r3, #0x10]
	ldr r1, [r3, #0x28]
	ldr r3, _0200C374 ; =FUN_0200C548
	bx r3
	.balign 4
_0200C374: .word FUN_0200C548

	thumb_func_start FUN_0200C378
FUN_0200C378: ; 0x0200C378
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldr r0, [r3, #0x14]
	ldr r1, [r3, #0x2c]
	ldr r3, _0200C384 ; =FUN_0200C4A8
	bx r3
	.balign 4
_0200C384: .word FUN_0200C4A8

	thumb_func_start FUN_0200C388
FUN_0200C388: ; 0x0200C388
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldr r0, [r3, #0x18]
	ldr r1, [r3, #0x30]
	ldr r3, _0200C394 ; =FUN_0200C4A8
	bx r3
	.balign 4
_0200C394: .word FUN_0200C4A8

	thumb_func_start FUN_0200C398
FUN_0200C398: ; 0x0200C398
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0200BC40
	ldr r0, [r6, #0x24]
	bl FUN_02009C30
	ldr r0, [r6, #0x28]
	bl FUN_02009E28
	ldr r0, [r6, #0x54]
	mov r4, #0x0
	cmp r0, #0x0
	ble _0200C3D0
	add r5, r6, #0x0
_0200C3BA:
	ldr r0, [r5, #0x24]
	bl FUN_02009448
	ldr r0, [r5, #0xc]
	bl FUN_02008E2C
	ldr r0, [r6, #0x54]
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r0
	blt _0200C3BA
_0200C3D0:
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_0200BCD0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200C3DC
FUN_0200C3DC: ; 0x0200C3DC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	beq _0200C3EE
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x0]
	bl FUN_02009CDC
_0200C3EE:
	ldr r0, [r4, #0x0]
	bl FUN_0201FFC8
	ldr r0, [r4, #0x8]
	bl FUN_02008C80
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200C404
FUN_0200C404: ; 0x0200C404
	push {r4-r7, lr}
	sub sp, #0x14
	add r6, r1, #0x0
	add r7, r0, #0x0
	ldr r0, [sp, #0x2c]
	add r5, r6, #0x0
	lsl r4, r0, #0x2
	add r5, #0xc
	ldr r0, [r5, r4]
	ldr r1, [sp, #0x30]
	str r2, [sp, #0xc]
	str r3, [sp, #0x10]
	bl FUN_0200945C
	cmp r0, #0x0
	bne _0200C42A
	add sp, #0x14
	mov r0, #0x0
	pop {r4-r7, pc}
_0200C42A:
	ldr r0, [sp, #0x30]
	ldr r1, [sp, #0xc]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x2c]
	ldr r2, [sp, #0x10]
	str r0, [sp, #0x4]
	ldr r0, [r7, #0x0]
	ldr r3, [sp, #0x28]
	str r0, [sp, #0x8]
	ldr r0, [r5, r4]
	bl FUN_020090AC
	add r5, r0, #0x0
	beq _0200C460
	add r0, r6, r4
	ldr r0, [r0, #0x24]
	add r1, r5, #0x0
	bl FUN_0200C474
	add r4, r0, #0x0
	cmp r4, #0x1
	beq _0200C45A
	bl ErrorHandling
_0200C45A:
	add sp, #0x14
	add r0, r4, #0x0
	pop {r4-r7, pc}
_0200C460:
	bl ErrorHandling
	cmp r5, #0x0
	beq _0200C46E
	add sp, #0x14
	mov r0, #0x1
	pop {r4-r7, pc}
_0200C46E:
	mov r0, #0x0
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_0200C474
FUN_0200C474: ; 0x0200C474
	push {r3-r6}
	ldr r6, [r0, #0x4]
	mov r3, #0x0
	cmp r6, #0x0
	ble _0200C4A0
	ldr r5, [r0, #0x0]
	add r4, r5, #0x0
_0200C482:
	ldr r2, [r4, #0x0]
	cmp r2, #0x0
	bne _0200C498
	lsl r2, r3, #0x2
	str r1, [r5, r2]
	ldr r1, [r0, #0x8]
	add r1, r1, #0x1
	str r1, [r0, #0x8]
	mov r0, #0x1
	pop {r3-r6}
	bx lr
_0200C498:
	add r3, r3, #0x1
	add r4, r4, #0x4
	cmp r3, r6
	blt _0200C482
_0200C4A0:
	mov r0, #0x0
	pop {r3-r6}
	bx lr
	.balign 4

	thumb_func_start FUN_0200C4A8
FUN_0200C4A8: ; 0x0200C4A8
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x4]
	add r7, r2, #0x0
	mov r6, #0x0
	cmp r0, #0x0
	ble _0200C4F0
	add r4, r6, #0x0
_0200C4BA:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _0200C4E6
	bl FUN_02009530
	cmp r0, r7
	bne _0200C4E6
	ldr r1, [r5, #0x0]
	lsl r4, r6, #0x2
	ldr r0, [sp, #0x0]
	ldr r1, [r1, r4]
	bl FUN_02009490
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	str r1, [r0, r4]
	ldr r0, [r5, #0x8]
	sub r0, r0, #0x1
	str r0, [r5, #0x8]
	mov r0, #0x1
	pop {r3-r7, pc}
_0200C4E6:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _0200C4BA
_0200C4F0:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0200C4F4
FUN_0200C4F4: ; 0x0200C4F4
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x4]
	add r7, r2, #0x0
	mov r6, #0x0
	cmp r0, #0x0
	ble _0200C542
	add r4, r6, #0x0
_0200C506:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _0200C538
	bl FUN_02009530
	cmp r0, r7
	bne _0200C538
	add r0, r7, #0x0
	bl FUN_0201D324
	ldr r1, [r5, #0x0]
	lsl r4, r6, #0x2
	ldr r0, [sp, #0x0]
	ldr r1, [r1, r4]
	bl FUN_02009490
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	str r1, [r0, r4]
	ldr r0, [r5, #0x8]
	sub r0, r0, #0x1
	str r0, [r5, #0x8]
	mov r0, #0x1
	pop {r3-r7, pc}
_0200C538:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _0200C506
_0200C542:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200C548
FUN_0200C548: ; 0x0200C548
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x4]
	add r7, r2, #0x0
	mov r6, #0x0
	cmp r0, #0x0
	ble _0200C596
	add r4, r6, #0x0
_0200C55A:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _0200C58C
	bl FUN_02009530
	cmp r0, r7
	bne _0200C58C
	add r0, r7, #0x0
	bl FUN_0201E1C8
	ldr r1, [r5, #0x0]
	lsl r4, r6, #0x2
	ldr r0, [sp, #0x0]
	ldr r1, [r1, r4]
	bl FUN_02009490
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	str r1, [r0, r4]
	ldr r0, [r5, #0x8]
	sub r0, r0, #0x1
	str r0, [r5, #0x8]
	mov r0, #0x1
	pop {r3-r7, pc}
_0200C58C:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _0200C55A
_0200C596:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200C59C
FUN_0200C59C: ; 0x0200C59C
	ldr r3, _0200C5A4 ; =FUN_020201E4
	mov r1, #0x1
	lsl r1, r1, #0xc
	bx r3
	.balign 4
_0200C5A4: .word FUN_020201E4

	thumb_func_start FUN_0200C5A8
FUN_0200C5A8: ; 0x0200C5A8
	ldr r3, _0200C5B0 ; =FUN_0200C59C
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C5B0: .word FUN_0200C59C

	thumb_func_start FUN_0200C5B4
FUN_0200C5B4: ; 0x0200C5B4
	ldr r3, _0200C5BC ; =FUN_020201E4
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C5BC: .word FUN_020201E4

	thumb_func_start FUN_0200C5C0
FUN_0200C5C0: ; 0x0200C5C0
	ldr r3, _0200C5C8 ; =FUN_02020130
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C5C8: .word FUN_02020130

	thumb_func_start FUN_0200C5CC
FUN_0200C5CC: ; 0x0200C5CC
	ldr r3, _0200C5D4 ; =FUN_020201DC
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C5D4: .word FUN_020201DC

	thumb_func_start FUN_0200C5D8
FUN_0200C5D8: ; 0x0200C5D8
	ldr r3, _0200C5DC ; =FUN_020200BC
	bx r3
	.balign 4
_0200C5DC: .word FUN_020200BC

	thumb_func_start FUN_0200C5E0
FUN_0200C5E0: ; 0x0200C5E0
	ldr r3, _0200C5E8 ; =FUN_0200C5D8
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C5E8: .word FUN_0200C5D8

	thumb_func_start FUN_0200C5EC
FUN_0200C5EC: ; 0x0200C5EC
	ldr r3, _0200C5F0 ; =FUN_020200D8
	bx r3
	.balign 4
_0200C5F0: .word FUN_020200D8

	thumb_func_start FUN_0200C5F4
FUN_0200C5F4: ; 0x0200C5F4
	ldr r3, _0200C5FC ; =FUN_0200C5EC
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C5FC: .word FUN_0200C5EC

	thumb_func_start FUN_0200C600
FUN_0200C600: ; 0x0200C600
	ldr r3, _0200C604 ; =FUN_02020388
	bx r3
	.balign 4
_0200C604: .word FUN_02020388

	thumb_func_start FUN_0200C608
FUN_0200C608: ; 0x0200C608
	ldr r3, _0200C610 ; =FUN_0200C600
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C610: .word FUN_0200C600

	thumb_func_start FUN_0200C614
FUN_0200C614: ; 0x0200C614
	ldr r3, _0200C618 ; =FUN_02020208
	bx r3
	.balign 4
_0200C618: .word FUN_02020208

	thumb_func_start FUN_0200C61C
FUN_0200C61C: ; 0x0200C61C
	ldr r3, _0200C624 ; =FUN_0200C614
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C624: .word FUN_0200C614

	thumb_func_start FUN_0200C628
FUN_0200C628: ; 0x0200C628
	ldr r3, _0200C62C ; =FUN_0202022C
	bx r3
	.balign 4
_0200C62C: .word FUN_0202022C

	thumb_func_start FUN_0200C630
FUN_0200C630: ; 0x0200C630
	ldr r3, _0200C638 ; =FUN_0200C628
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C638: .word FUN_0200C628

	thumb_func_start FUN_0200C63C
FUN_0200C63C: ; 0x0200C63C
	ldr r3, _0200C640 ; =FUN_020200A0
	bx r3
	.balign 4
_0200C640: .word FUN_020200A0

	thumb_func_start FUN_0200C644
FUN_0200C644: ; 0x0200C644
	ldr r3, _0200C64C ; =FUN_0200C63C
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C64C: .word FUN_0200C63C

	thumb_func_start FUN_0200C650
FUN_0200C650: ; 0x0200C650
	ldr r3, _0200C654 ; =FUN_02020128
	bx r3
	.balign 4
_0200C654: .word FUN_02020128

	thumb_func_start FUN_0200C658
FUN_0200C658: ; 0x0200C658
	ldr r3, _0200C660 ; =FUN_0200C650
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C660: .word FUN_0200C650

	thumb_func_start FUN_0200C664
FUN_0200C664: ; 0x0200C664
	ldr r3, _0200C668 ; =FUN_02020248
	bx r3
	.balign 4
_0200C668: .word FUN_02020248

	thumb_func_start FUN_0200C66C
FUN_0200C66C: ; 0x0200C66C
	ldr r3, _0200C674 ; =FUN_0200C664
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C674: .word FUN_0200C664

	thumb_func_start FUN_0200C678
FUN_0200C678: ; 0x0200C678
	ldr r3, _0200C67C ; =FUN_020202A8
	bx r3
	.balign 4
_0200C67C: .word FUN_020202A8

	thumb_func_start FUN_0200C680
FUN_0200C680: ; 0x0200C680
	ldr r3, _0200C688 ; =FUN_0200C678
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C688: .word FUN_0200C678

	thumb_func_start FUN_0200C68C
FUN_0200C68C: ; 0x0200C68C
	ldr r3, _0200C694 ; =FUN_02020300
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C694: .word FUN_02020300

	thumb_func_start FUN_0200C698
FUN_0200C698: ; 0x0200C698
	ldr r3, _0200C6A0 ; =FUN_02020238
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bx r3
	.balign 4
_0200C6A0: .word FUN_02020238

	thumb_func_start FUN_0200C6A4
FUN_0200C6A4: ; 0x0200C6A4
	ldr r3, _0200C6AC ; =FUN_02020240
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C6AC: .word FUN_02020240

	thumb_func_start FUN_0200C6B0
FUN_0200C6B0: ; 0x0200C6B0
	ldr r3, _0200C6B8 ; =FUN_0200C698
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C6B8: .word FUN_0200C698

	thumb_func_start FUN_0200C6BC
FUN_0200C6BC: ; 0x0200C6BC
	ldr r3, _0200C6C0 ; =FUN_02020310
	bx r3
	.balign 4
_0200C6C0: .word FUN_02020310

	thumb_func_start FUN_0200C6C4
FUN_0200C6C4: ; 0x0200C6C4
	ldr r3, _0200C6CC ; =FUN_0200C6BC
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C6CC: .word FUN_0200C6BC

	thumb_func_start FUN_0200C6D0
FUN_0200C6D0: ; 0x0200C6D0
	ldr r3, _0200C6D4 ; =FUN_0202032C
	bx r3
	.balign 4
_0200C6D4: .word FUN_0202032C

	thumb_func_start FUN_0200C6D8
FUN_0200C6D8: ; 0x0200C6D8
	ldr r3, _0200C6E0 ; =FUN_0200C6D0
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C6E0: .word FUN_0200C6D0

	thumb_func_start FUN_0200C6E4
FUN_0200C6E4: ; 0x0200C6E4
	push {r3-r4, lr}
	sub sp, #0xc
	lsl r1, r1, #0xc
	str r1, [sp, #0x0]
	lsl r1, r2, #0xc
	add r4, r0, #0x0
	str r1, [sp, #0x4]
	bl FUN_02020380
	cmp r0, #0x2
	bne _0200C704
	mov r0, #0x3
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x12
	add r0, r1, r0
	str r0, [sp, #0x4]
_0200C704:
	mov r0, #0x0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02020044
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0200C714
FUN_0200C714: ; 0x0200C714
	ldr r3, _0200C71C ; =FUN_0200C6E4
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C71C: .word FUN_0200C6E4

	thumb_func_start FUN_0200C720
FUN_0200C720: ; 0x0200C720
	push {r4-r5, lr}
	sub sp, #0xc
	lsl r1, r1, #0xc
	str r1, [sp, #0x0]
	lsl r1, r2, #0xc
	add r5, r0, #0x0
	add r4, r3, #0x0
	str r1, [sp, #0x4]
	bl FUN_02020380
	cmp r0, #0x2
	bne _0200C73E
	ldr r0, [sp, #0x4]
	add r0, r0, r4
	str r0, [sp, #0x4]
_0200C73E:
	mov r0, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02020044
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_0200C750
FUN_0200C750: ; 0x0200C750
	push {r3, lr}
	ldr r0, [r0, #0x0]
	bl FUN_0200C720
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0200C75C
FUN_0200C75C: ; 0x0200C75C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r6, r1, #0x0
	add r5, r2, #0x0
	bl FUN_0202011C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	strh r0, [r6, #0x0]
	add r0, r7, #0x0
	bl FUN_02020380
	cmp r0, #0x2
	ldr r1, [r4, #0x4]
	bne _0200C794
	mov r0, #0x3
	lsl r0, r0, #0x12
	sub r1, r1, r0
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	strh r0, [r5, #0x0]
	pop {r3-r7, pc}
_0200C794:
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	strh r0, [r5, #0x0]
	pop {r3-r7, pc}

	thumb_func_start FUN_0200C7A0
FUN_0200C7A0: ; 0x0200C7A0
	ldr r3, _0200C7A8 ; =FUN_0200C75C
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C7A8: .word FUN_0200C75C

	thumb_func_start FUN_0200C7AC
FUN_0200C7AC: ; 0x0200C7AC
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	add r6, r1, #0x0
	add r5, r2, #0x0
	add r7, r3, #0x0
	bl FUN_0202011C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	strh r0, [r6, #0x0]
	ldr r0, [sp, #0x0]
	bl FUN_02020380
	cmp r0, #0x2
	bne _0200C7E2
	ldr r0, [r4, #0x4]
	sub r1, r0, r7
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	strh r0, [r5, #0x0]
	pop {r3-r7, pc}
_0200C7E2:
	ldr r1, [r4, #0x4]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	strh r0, [r5, #0x0]
	pop {r3-r7, pc}

	thumb_func_start FUN_0200C7F0
FUN_0200C7F0: ; 0x0200C7F0
	push {r3, lr}
	ldr r0, [r0, #0x0]
	bl FUN_0200C7AC
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0200C7FC
FUN_0200C7FC: ; 0x0200C7FC
	push {r3-r6, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_0202011C
	ldr r2, [r0, #0x0]
	lsl r1, r5, #0xc
	add r1, r2, r1
	str r1, [sp, #0x0]
	ldr r2, [r0, #0x4]
	lsl r1, r4, #0xc
	add r1, r2, r1
	str r1, [sp, #0x4]
	ldr r0, [r0, #0x8]
	add r1, sp, #0x0
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	bl FUN_02020044
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_0200C82C
FUN_0200C82C: ; 0x0200C82C
	ldr r3, _0200C834 ; =FUN_0200C7FC
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C834: .word FUN_0200C7FC

	thumb_func_start FUN_0200C838
FUN_0200C838: ; 0x0200C838
	ldr r3, _0200C83C ; =FUN_020200EC
	bx r3
	.balign 4
_0200C83C: .word FUN_020200EC

	thumb_func_start FUN_0200C840
FUN_0200C840: ; 0x0200C840
	ldr r3, _0200C848 ; =FUN_0200C838
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C848: .word FUN_0200C838

	thumb_func_start FUN_0200C84C
FUN_0200C84C: ; 0x0200C84C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl FUN_02020120
	add r4, r0, #0x0
	ldr r0, _0200C880 ; =0x45800000
	add r1, r6, #0x0
	bl _fmul
	bl _ffix
	str r0, [r4, #0x0]
	ldr r0, _0200C880 ; =0x45800000
	add r1, r7, #0x0
	bl _fmul
	bl _ffix
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02020064
	pop {r3-r7, pc}
	.balign 4
_0200C880: .word 0x45800000

	thumb_func_start FUN_0200C884
FUN_0200C884: ; 0x0200C884
	ldr r3, _0200C88C ; =FUN_0200C84C
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C88C: .word FUN_0200C84C

	thumb_func_start FUN_0200C890
FUN_0200C890: ; 0x0200C890
	ldr r3, _0200C894 ; =FUN_02020088
	bx r3
	.balign 4
_0200C894: .word FUN_02020088

	thumb_func_start FUN_0200C898
FUN_0200C898: ; 0x0200C898
	ldr r3, _0200C8A0 ; =FUN_0200C890
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C8A0: .word FUN_0200C890

	thumb_func_start FUN_0200C8A4
FUN_0200C8A4: ; 0x0200C8A4
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	bl FUN_02020124
	add r0, r0, r5
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r0, r4, #0x0
	bl FUN_02020088
	pop {r3-r5, pc}

	thumb_func_start FUN_0200C8BC
FUN_0200C8BC: ; 0x0200C8BC
	ldr r3, _0200C8C4 ; =FUN_0200C8A4
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C8C4: .word FUN_0200C8A4

	thumb_func_start FUN_0200C8C8
FUN_0200C8C8: ; 0x0200C8C8
	ldr r3, _0200C8CC ; =FUN_02020100
	bx r3
	.balign 4
_0200C8CC: .word FUN_02020100

	thumb_func_start FUN_0200C8D0
FUN_0200C8D0: ; 0x0200C8D0
	ldr r3, _0200C8D8 ; =FUN_0200C8C8
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C8D8: .word FUN_0200C8C8

	thumb_func_start FUN_0200C8DC
FUN_0200C8DC: ; 0x0200C8DC
	push {lr}
	sub sp, #0xc
	lsl r1, r1, #0xc
	str r1, [sp, #0x0]
	lsl r1, r2, #0xc
	str r1, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	ldr r0, [r0, #0x0]
	add r1, sp, #0x0
	bl FUN_02020054
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_0200C8F8
FUN_0200C8F8: ; 0x0200C8F8
	ldr r3, _0200C900 ; =FUN_02020358
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C900: .word FUN_02020358

	thumb_func_start FUN_0200C904
FUN_0200C904: ; 0x0200C904
	ldr r3, _0200C908 ; =FUN_02020398
	bx r3
	.balign 4
_0200C908: .word FUN_02020398

	thumb_func_start FUN_0200C90C
FUN_0200C90C: ; 0x0200C90C
	ldr r3, _0200C914 ; =FUN_0200C904
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0200C914: .word FUN_0200C904

	thumb_func_start FUN_0200C918
FUN_0200C918: ; 0x0200C918
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	ldr r1, [sp, #0x28]
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_0200945C
	cmp r0, #0x0
	bne _0200C936
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0200C936:
	ldr r0, [sp, #0x28]
	ldr r3, [sp, #0x20]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	add r1, r6, #0x0
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r2, r7, #0x0
	str r0, [sp, #0x8]
	ldr r0, [r4, #0xc]
	bl FUN_02008F34
	add r5, r0, #0x0
	beq _0200C964
	bl FUN_02009AC4
	ldr r0, [r4, #0x24]
	add r1, r5, #0x0
	bl FUN_0200C474
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0200C964:
	bl ErrorHandling
	cmp r5, #0x0
	beq _0200C972
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0200C972:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0200C978
FUN_0200C978: ; 0x0200C978
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	ldr r1, [sp, #0x28]
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_0200945C
	cmp r0, #0x0
	bne _0200C996
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0200C996:
	ldr r0, [sp, #0x28]
	ldr r3, [sp, #0x20]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	add r1, r6, #0x0
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r2, r7, #0x0
	str r0, [sp, #0x8]
	ldr r0, [r4, #0xc]
	bl FUN_02008F34
	add r5, r0, #0x0
	beq _0200C9C4
	bl FUN_02009B78
	ldr r0, [r4, #0x24]
	add r1, r5, #0x0
	bl FUN_0200C474
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0200C9C4:
	bl ErrorHandling
	cmp r5, #0x0
	beq _0200C9D2
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0200C9D2:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0200C9D8
FUN_0200C9D8: ; 0x0200C9D8
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	ldr r1, [sp, #0x24]
	add r7, r2, #0x0
	str r3, [sp, #0x8]
	bl FUN_020094F0
	add r6, r0, #0x0
	ldr r0, [sp, #0x20]
	ldr r3, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	str r0, [sp, #0x4]
	ldr r0, [r4, #0xc]
	add r2, r7, #0x0
	bl FUN_020090FC
	add r0, r6, #0x0
	bl FUN_02009BE8
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0200CA0C
FUN_0200CA0C: ; 0x0200CA0C
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #0x24]
	add r7, r2, #0x0
	str r3, [sp, #0x8]
	bl FUN_020094F0
	add r6, r0, #0x0
	ldr r0, [sp, #0x20]
	ldr r3, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x10]
	add r2, r7, #0x0
	bl FUN_02009168
	add r0, r6, #0x0
	bl FUN_02009DE0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0200CA40
FUN_0200CA40: ; 0x0200CA40
	ldr r0, [r0, #0x0]
	bx lr
