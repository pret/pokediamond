	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0201BCBC
FUN_0201BCBC: ; 0x0201BCBC
	ldr r1, _0201BCC4 ; =0x02105BB4
	str r0, [r1, #0x0]
	bx lr
	nop
_0201BCC4: .word 0x02105BB4

	thumb_func_start FUN_0201BCC8
FUN_0201BCC8: ; 0x0201BCC8
	push {r4-r6, lr}
	ldr r4, _0201BCF8 ; =0x021C5714
	mov r5, #0x0
_0201BCCE:
	ldr r3, [r4, #0x0]
	cmp r3, #0x0
	bne _0201BCE8
	ldr r6, _0201BCF8 ; =0x021C5714
	lsl r4, r5, #0x2
	bl FUN_0200CA7C
	str r0, [r6, r4]
	ldr r0, [r6, r4]
	cmp r0, #0x0
	bne _0201BCF0
	mov r5, #0x8
	b _0201BCF0
_0201BCE8:
	add r5, r5, #0x1
	add r4, r4, #0x4
	cmp r5, #0x8
	blt _0201BCCE
_0201BCF0:
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	pop {r4-r6, pc}
	nop
_0201BCF8: .word 0x021C5714

	thumb_func_start FUN_0201BCFC
FUN_0201BCFC: ; 0x0201BCFC
	push {r4-r6, lr}
	add r5, r0, #0x0
	cmp r5, #0x8
	blo _0201BD08
	bl ErrorHandling
_0201BD08:
	ldr r6, _0201BD40 ; =0x021C5714
	lsl r4, r5, #0x2
	ldr r0, [r6, r4]
	cmp r0, #0x0
	bne _0201BD16
	bl ErrorHandling
_0201BD16:
	cmp r5, #0x8
	bhs _0201BD3C
	ldr r0, [r6, r4]
	cmp r0, #0x0
	beq _0201BD3C
	bl FUN_0201B6C8
	add r5, r0, #0x0
	beq _0201BD32
	bl FUN_0201C238
	add r0, r5, #0x0
	bl FUN_02016A18
_0201BD32:
	ldr r0, [r6, r4]
	bl FUN_0200CAB4
	mov r0, #0x0
	str r0, [r6, r4]
_0201BD3C:
	pop {r4-r6, pc}
	nop
_0201BD40: .word 0x021C5714

	thumb_func_start FUN_0201BD44
FUN_0201BD44: ; 0x0201BD44
	lsl r1, r0, #0x2
	ldr r0, _0201BD58 ; =0x021C5714
	ldr r0, [r0, r1]
	cmp r0, #0x0
	beq _0201BD52
	mov r0, #0x1
	bx lr
_0201BD52:
	mov r0, #0x0
	bx lr
	nop
_0201BD58: .word 0x021C5714

	thumb_func_start FUN_0201BD5C
FUN_0201BD5C: ; 0x0201BD5C
	mov r1, #0x0
	ldr r2, _0201BD6C ; =0x021C5714
	add r0, r1, #0x0
_0201BD62:
	add r1, r1, #0x1
	stmia r2!, {r0}
	cmp r1, #0x8
	blt _0201BD62
	bx lr
	.balign 4
_0201BD6C: .word 0x021C5714

	thumb_func_start FUN_0201BD70
FUN_0201BD70: ; 0x0201BD70
	push {r3, lr}
	bl FUN_0201BD44
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}

	thumb_func_start FUN_0201BD7C
FUN_0201BD7C: ; 0x0201BD7C
	ldr r3, _0201BD80 ; =FUN_0201BCFC
	bx r3
	.balign 4
_0201BD80: .word FUN_0201BCFC

	thumb_func_start FUN_0201BD84
FUN_0201BD84: ; 0x0201BD84
	push {r3, lr}
	sub sp, #0x18
	str r0, [sp, #0x4]
	lsl r0, r3, #0x18
	lsr r3, r0, #0x18
	ldr r0, [sp, #0x20]
	str r2, [sp, #0x0]
	add r2, sp, #0x0
	strb r1, [r2, #0x9]
	lsl r0, r0, #0x18
	strb r3, [r2, #0xa]
	lsr r0, r0, #0x18
	strb r0, [r2, #0xb]
	strb r3, [r2, #0xc]
	strb r0, [r2, #0xd]
	ldr r0, _0201BDDC ; =0x02105BB4
	lsl r1, r1, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r1
	ldrb r0, [r1, #0x2]
	strb r0, [r2, #0xe]
	ldrb r0, [r1, #0x3]
	strb r0, [r2, #0xf]
	ldrb r0, [r1, #0x4]
	strb r0, [r2, #0x10]
	ldrb r0, [r1, #0x5]
	strb r0, [r2, #0x11]
	ldrb r0, [r1, #0x6]
	strb r0, [r2, #0x12]
	ldrb r0, [r1, #0x7]
	ldr r1, [sp, #0x24]
	strb r0, [r2, #0x13]
	mov r0, #0x0
	strh r0, [r2, #0x14]
	strb r0, [r2, #0x16]
	mov r0, #0xff
	strb r0, [r2, #0x17]
	ldr r2, [sp, #0x28]
	add r0, sp, #0x0
	bl FUN_0201BE98
	add sp, #0x18
	pop {r3, pc}
	nop
_0201BDDC: .word 0x02105BB4

	thumb_func_start FUN_0201BDE0
FUN_0201BDE0: ; 0x0201BDE0
	push {r3, lr}
	sub sp, #0x18
	str r0, [sp, #0x4]
	lsl r0, r3, #0x18
	lsr r3, r0, #0x18
	ldr r0, [sp, #0x20]
	str r2, [sp, #0x0]
	add r2, sp, #0x0
	strb r1, [r2, #0x9]
	lsl r0, r0, #0x18
	strb r3, [r2, #0xa]
	lsr r0, r0, #0x18
	strb r0, [r2, #0xb]
	strb r3, [r2, #0xc]
	strb r0, [r2, #0xd]
	ldr r0, _0201BE38 ; =0x02105BB4
	lsl r1, r1, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r1
	ldrb r0, [r1, #0x2]
	strb r0, [r2, #0xe]
	ldrb r0, [r1, #0x3]
	strb r0, [r2, #0xf]
	ldrb r0, [r1, #0x4]
	ldr r1, [sp, #0x28]
	strb r0, [r2, #0x10]
	lsr r0, r1, #0x10
	strb r0, [r2, #0x11]
	lsr r0, r1, #0x8
	strb r0, [r2, #0x13]
	strb r1, [r2, #0x12]
	mov r0, #0x0
	strh r0, [r2, #0x14]
	strb r0, [r2, #0x16]
	mov r0, #0xff
	strb r0, [r2, #0x17]
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x2c]
	add r0, sp, #0x0
	bl FUN_0201BE98
	add sp, #0x18
	pop {r3, pc}
	nop
_0201BE38: .word 0x02105BB4

	thumb_func_start FUN_0201BE3C
FUN_0201BE3C: ; 0x0201BE3C
	push {r3, lr}
	sub sp, #0x18
	str r0, [sp, #0x4]
	lsl r0, r3, #0x18
	lsr r3, r0, #0x18
	ldr r0, [sp, #0x20]
	str r2, [sp, #0x0]
	add r2, sp, #0x0
	strb r1, [r2, #0x9]
	lsl r0, r0, #0x18
	strb r3, [r2, #0xa]
	lsr r0, r0, #0x18
	strb r0, [r2, #0xb]
	strb r3, [r2, #0xc]
	strb r0, [r2, #0xd]
	ldr r0, [sp, #0x2c]
	strb r0, [r2, #0xe]
	ldr r0, [sp, #0x30]
	strb r0, [r2, #0xf]
	ldr r0, _0201BE94 ; =0x02105BB4
	ldr r3, [r0, #0x0]
	lsl r0, r1, #0x3
	add r0, r3, r0
	ldrb r0, [r0, #0x4]
	ldr r1, [sp, #0x28]
	strb r0, [r2, #0x10]
	lsr r0, r1, #0x10
	strb r0, [r2, #0x11]
	lsr r0, r1, #0x8
	strb r0, [r2, #0x13]
	strb r1, [r2, #0x12]
	mov r0, #0x0
	strh r0, [r2, #0x14]
	strb r0, [r2, #0x16]
	mov r0, #0xff
	strb r0, [r2, #0x17]
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x34]
	add r0, sp, #0x0
	bl FUN_0201BE98
	add sp, #0x18
	pop {r3, pc}
	nop
_0201BE94: .word 0x02105BB4

	thumb_func_start FUN_0201BE98
FUN_0201BE98: ; 0x0201BE98
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _0201BFD0 ; =0x02105BB4
	add r6, r1, #0x0
	ldr r0, [r0, #0x0]
	add r5, r2, #0x0
	cmp r0, #0x0
	bne _0201BEAC
	mov r0, #0xff
	pop {r3-r7, pc}
_0201BEAC:
	mov r0, #0x0
	mov r1, #0x30
	bl FUN_02016998
	add r4, r0, #0x0
	mov r1, #0x1
	add r0, #0x23
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	add r0, #0x24
	strb r3, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r2, [r0, #0x0]
	mov r0, #0x7f
	bic r2, r0
	lsl r0, r6, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x7f
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x25
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x26
	strb r3, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x27
	strb r3, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x29
	strb r3, [r0, #0x0]
	add r1, r3, #0x0
_0201BEF4:
	add r0, r4, r3
	add r3, r3, #0x1
	strb r1, [r0, #0x1c]
	cmp r3, #0x7
	blt _0201BEF4
	add r3, r7, #0x0
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	bl FUN_02021F2C
	str r0, [r4, #0x0]
	ldr r0, _0201BFD4 ; =0x021C570C
	str r5, [r4, #0x18]
	mov r1, #0x0
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0201C1A8
	cmp r6, #0xff
	beq _0201BF74
	cmp r6, #0x0
	beq _0201BF74
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r2, [r0, #0x0]
	mov r1, #0x7f
	add r0, r2, #0x0
	bic r0, r1
	lsl r1, r2, #0x19
	lsr r1, r1, #0x19
	add r1, #0xff
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	mov r1, #0x7f
	and r1, r2
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x25
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r1, [r0, #0x0]
	mov r0, #0x80
	mov r2, #0x1
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x25
	strb r1, [r0, #0x0]
	ldr r0, _0201BFD8 ; =FUN_0201BFDC
	add r1, r4, #0x0
	bl FUN_0201BCC8
	add r1, r4, #0x0
	add r1, #0x28
	strb r0, [r1, #0x0]
	add r4, #0x28
	ldrb r0, [r4, #0x0]
	pop {r3-r7, pc}
_0201BF74:
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r1, [r0, #0x0]
	mov r0, #0x7f
	mov r5, #0x0
	bic r1, r0
	add r0, r4, #0x0
	add r0, #0x25
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r1, [r0, #0x0]
	mov r0, #0x80
	bic r1, r0
	add r0, r4, #0x0
	add r0, #0x25
	strb r1, [r0, #0x0]
	ldrb r0, [r7, #0x11]
	ldrb r1, [r7, #0x12]
	ldrb r2, [r7, #0x13]
	bl FUN_0201C05C
	mov r7, #0x1
	lsl r7, r7, #0xa
_0201BFA4:
	add r0, r4, #0x0
	bl FUN_0201C048
	cmp r0, #0x1
	beq _0201BFB4
	add r5, r5, #0x1
	cmp r5, r7
	blo _0201BFA4
_0201BFB4:
	cmp r6, #0xff
	beq _0201BFBE
	ldr r0, [r4, #0x4]
	bl FUN_020191D0
_0201BFBE:
	add r0, r4, #0x0
	bl FUN_0201C238
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x8
	pop {r3-r7, pc}
	nop
_0201BFD0: .word 0x02105BB4
_0201BFD4: .word 0x021C570C
_0201BFD8: .word FUN_0201BFDC

	thumb_func_start FUN_0201BFDC
FUN_0201BFDC: ; 0x0201BFDC
	push {r4, lr}
	ldr r0, _0201C044 ; =0x021C570C
	add r4, r1, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201C042
	add r0, r4, #0x0
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201C036
	mov r0, #0x0
	strh r0, [r4, #0x2a]
	ldrb r0, [r4, #0x11]
	ldrb r1, [r4, #0x12]
	ldrb r2, [r4, #0x13]
	bl FUN_0201C05C
	add r0, r4, #0x0
	bl FUN_0201C048
	cmp r0, #0x0
	beq _0201C014
	cmp r0, #0x1
	beq _0201C02C
	cmp r0, #0x3
	beq _0201C01A
	pop {r4, pc}
_0201C014:
	ldr r0, [r4, #0x4]
	bl FUN_020191D0
_0201C01A:
	ldr r2, [r4, #0x18]
	cmp r2, #0x0
	beq _0201C042
	ldrh r1, [r4, #0x2a]
	add r0, r4, #0x0
	blx r2
	add r4, #0x29
	strb r0, [r4, #0x0]
	pop {r4, pc}
_0201C02C:
	add r4, #0x28
	ldrb r0, [r4, #0x0]
	bl FUN_0201BCFC
	pop {r4, pc}
_0201C036:
	ldrh r1, [r4, #0x2a]
	ldr r2, [r4, #0x18]
	add r0, r4, #0x0
	blx r2
	add r4, #0x29
	strb r0, [r4, #0x0]
_0201C042:
	pop {r4, pc}
	.balign 4
_0201C044: .word 0x021C570C

	thumb_func_start FUN_0201C048
FUN_0201C048: ; 0x0201C048
	push {r4, lr}
	add r4, r0, #0x0
_0201C04C:
	ldrb r0, [r4, #0x9]
	add r1, r4, #0x0
	bl FUN_02002DB0
	cmp r0, #0x2
	beq _0201C04C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201C05C
FUN_0201C05C: ; 0x0201C05C
	push {r3-r7, lr}
	sub sp, #0x30
	ldr r3, _0201C0F8 ; =0x021C570C
	mov r5, #0x0
	str r5, [sp, #0x20]
	str r0, [sp, #0x24]
	str r2, [sp, #0x28]
	str r1, [sp, #0x2c]
	strh r1, [r3, #0x6]
	strh r0, [r3, #0x2]
	add r0, sp, #0x20
	strh r2, [r3, #0x4]
	str r5, [sp, #0x14]
	str r0, [sp, #0x8]
	mov r12, r0
	mov lr, r0
	str r0, [sp, #0x18]
_0201C07E:
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x8]
	ldr r0, [r0, #0x0]
	str r0, [sp, #0x1c]
_0201C08C:
	mov r0, #0x0
	str r0, [sp, #0xc]
	mov r0, lr
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0x0]
	lsl r7, r0, #0x4
_0201C09A:
	ldr r0, [sp, #0x0]
	mov r3, #0x0
	ldr r0, [r0, #0x0]
	mov r4, r12
	lsl r6, r0, #0x8
_0201C0A4:
	ldr r0, [r4, #0x0]
	add r1, r7, #0x0
	lsl r0, r0, #0xc
	orr r0, r6
	orr r1, r0
	ldr r0, [sp, #0x1c]
	add r3, r3, #0x1
	add r2, r0, #0x0
	orr r2, r1
	lsl r1, r5, #0x1
	ldr r0, _0201C0FC ; =0x021C5734
	add r5, r5, #0x1
	add r4, r4, #0x4
	strh r2, [r0, r1]
	cmp r3, #0x4
	blt _0201C0A4
	ldr r0, [sp, #0x0]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xc]
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	cmp r0, #0x4
	blt _0201C09A
	ldr r0, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x10]
	add r0, r0, #0x1
	str r0, [sp, #0x10]
	cmp r0, #0x4
	blt _0201C08C
	ldr r0, [sp, #0x8]
	add r0, r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x14]
	add r0, r0, #0x1
	str r0, [sp, #0x14]
	cmp r0, #0x4
	blt _0201C07E
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_0201C0F8: .word 0x021C570C
_0201C0FC: .word 0x021C5734

	thumb_func_start FUN_0201C100
FUN_0201C100: ; 0x0201C100
	ldrh r2, [r0, #0x0]
	lsr r2, r2, #0x8
	lsl r3, r2, #0x1
	ldr r2, _0201C1A4 ; =0x021C5734
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x0]
	ldrh r3, [r0, #0x0]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x2]
	ldrh r3, [r0, #0x2]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x4]
	ldrh r3, [r0, #0x2]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x6]
	ldrh r3, [r0, #0x4]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x8]
	ldrh r3, [r0, #0x4]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0xa]
	ldrh r3, [r0, #0x6]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0xc]
	ldrh r3, [r0, #0x6]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0xe]
	ldrh r3, [r0, #0x8]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x10]
	ldrh r3, [r0, #0x8]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x12]
	ldrh r3, [r0, #0xa]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x14]
	ldrh r3, [r0, #0xa]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x16]
	ldrh r3, [r0, #0xc]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x18]
	ldrh r3, [r0, #0xc]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x1a]
	ldrh r3, [r0, #0xe]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x1c]
	ldrh r0, [r0, #0xe]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x17
	ldrh r0, [r2, r0]
	strh r0, [r1, #0x1e]
	bx lr
	.balign 4
_0201C1A4: .word 0x021C5734

	thumb_func_start FUN_0201C1A8
FUN_0201C1A8: ; 0x0201C1A8
	mov r1, #0x0
	str r1, [r0, #0x2c]
	bx lr
	.balign 4

	thumb_func_start FUN_0201C1B0
FUN_0201C1B0: ; 0x0201C1B0
	push {r3-r5, lr}
	sub sp, #0x8
	mov r1, #0x6
	mov r0, #0x0
	lsl r1, r1, #0x8
	bl FUN_02016998
	mov r2, #0x0
	add r5, r0, #0x0
	str r2, [sp, #0x0]
	mov r0, #0xe
	mov r1, #0x5
	add r3, sp, #0x4
	bl FUN_02006BB0
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	mov r2, #0x6
	ldr r0, [r0, #0x14]
	add r1, r5, #0x0
	lsl r2, r2, #0x8
	bl MIi_CpuCopy32
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201C1EC
FUN_0201C1EC: ; 0x0201C1EC
	push {r3-r7, lr}
	sub sp, #0x18
	add r4, r0, #0x0
	ldr r0, [r4, #0x2c]
	add r7, r3, #0x0
	ldr r5, [r4, #0x4]
	cmp r0, #0x0
	bne _0201C202
	bl FUN_0201C1B0
	str r0, [r4, #0x2c]
_0201C202:
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r6, r7, #0x0
	mul r6, r0
	add r0, r5, #0x0
	ldr r4, [r4, #0x2c]
	bl FUN_0201AB0C
	sub r0, r0, #0x3
	lsl r0, r0, #0x13
	mov r1, #0x18
	lsr r2, r0, #0x10
	str r1, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	mov r2, #0x0
	str r2, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	add r1, r4, r6
	add r3, r2, #0x0
	bl FUN_02019658
	add sp, #0x18
	pop {r3-r7, pc}

	thumb_func_start FUN_0201C238
FUN_0201C238: ; 0x0201C238
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x2c]
	cmp r0, #0x0
	beq _0201C24A
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x2c]
_0201C24A:
	pop {r4, pc}
