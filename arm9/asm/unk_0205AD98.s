    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_02105F9C
	.extern UNK_020F6C84
	.extern UNK_020F6C54
	.extern UNK_020F6C6C
	.extern UNK_020F6440
	.extern UNK_020F6308
	.extern UNK_020F6C48

	.text

	thumb_func_start FUN_0205AD98
FUN_0205AD98: ; 0x0205AD98
	push {r4, lr}
	mov r1, #0x1
	add r4, r0, #0x0
	bl FUN_0205842C
	cmp r0, #0x0
	bne _0205ADAA
	mov r0, #0x0
	pop {r4, pc}
_0205ADAA:
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0205842C
	cmp r0, #0x1
	bne _0205ADBA
	mov r0, #0x0
	pop {r4, pc}
_0205ADBA:
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_0205842C
	cmp r0, #0x1
	bne _0205ADD6
	add r0, r4, #0x0
	mov r1, #0x20
	bl FUN_0205842C
	cmp r0, #0x0
	bne _0205ADD6
	mov r0, #0x0
	pop {r4, pc}
_0205ADD6:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205ADDC
FUN_0205ADDC: ; 0x0205ADDC
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x69
	blt _0205ADEA
	bl ErrorHandling
_0205ADEA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020586E8
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020586F8
	add r0, r5, #0x0
	mov r1, #0x10
	bl FUN_02058410
	add r0, r5, #0x0
	mov r1, #0x20
	bl FUN_02058418
	pop {r3-r5, pc}

	thumb_func_start FUN_0205AE0C
FUN_0205AE0C: ; 0x0205AE0C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020586E8
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020586F8
	add r0, r4, #0x0
	mov r1, #0x20
	bl FUN_02058418
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205AE28
FUN_0205AE28: ; 0x0205AE28
	push {r4, lr}
	mov r1, #0x10
	add r4, r0, #0x0
	bl FUN_0205842C
	cmp r0, #0x0
	bne _0205AE3A
	mov r0, #0x1
	pop {r4, pc}
_0205AE3A:
	add r0, r4, #0x0
	mov r1, #0x20
	bl FUN_0205842C
	cmp r0, #0x0
	beq _0205AE4A
	mov r0, #0x1
	pop {r4, pc}
_0205AE4A:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205AE50
FUN_0205AE50: ; 0x0205AE50
	push {r4, lr}
	mov r1, #0x10
	add r4, r0, #0x0
	bl FUN_0205842C
	cmp r0, #0x0
	bne _0205AE62
	mov r0, #0x1
	pop {r4, pc}
_0205AE62:
	add r0, r4, #0x0
	mov r1, #0x20
	bl FUN_0205842C
	cmp r0, #0x0
	bne _0205AE72
	mov r0, #0x0
	pop {r4, pc}
_0205AE72:
	add r0, r4, #0x0
	mov r1, #0x30
	bl FUN_02058418
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205AE80
FUN_0205AE80: ; 0x0205AE80
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x10
	bl FUN_02058418
	add r0, r4, #0x0
	mov r1, #0x20
	bl FUN_02058410
	add r0, r4, #0x0
	mov r1, #0xff
	bl FUN_020586E8
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020586F8
	pop {r4, pc}

	thumb_func_start FUN_0205AEA4
FUN_0205AEA4: ; 0x0205AEA4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0x4
	mov r1, #0x14
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	bne _0205AEBA
	bl ErrorHandling
_0205AEBA:
	add r2, r4, #0x0
	mov r1, #0x14
	mov r0, #0x0
_0205AEC0:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _0205AEC0
	add r0, r5, #0x0
	bl FUN_02058578
	bl FUN_0205839C
	sub r2, r0, #0x1
	ldr r0, _0205AEEC ; =FUN_0205AF2C
	add r1, r4, #0x0
	bl FUN_0200CA44
	add r7, r0, #0x0
	bne _0205AEE4
	bl ErrorHandling
_0205AEE4:
	str r5, [r4, #0xc]
	str r6, [r4, #0x10]
	add r0, r7, #0x0
	pop {r3-r7, pc}
	.balign 4
_0205AEEC: .word FUN_0205AF2C

	thumb_func_start FUN_0205AEF0
FUN_0205AEF0: ; 0x0205AEF0
	push {r3, lr}
	bl FUN_0201B6C8
	ldr r0, [r0, #0x4]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205AEFC
FUN_0205AEFC: ; 0x0205AEFC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0201B6C8
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0205AE28
	cmp r0, #0x1
	beq _0205AF14
	bl ErrorHandling
_0205AF14:
	ldr r0, [r4, #0xc]
	bl FUN_0205AE50
	mov r0, #0x4
	add r1, r4, #0x0
	bl FreeToHeapExplicit
	add r0, r5, #0x0
	bl FUN_0200CAB4
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205AF2C
FUN_0205AF2C: ; 0x0205AF2C
	push {r3-r5, lr}
	ldr r4, _0205AF44 ; =UNK_020F6C54
	add r5, r1, #0x0
_0205AF32:
	ldr r1, [r5, #0x0]
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	blx r1
	cmp r0, #0x1
	beq _0205AF32
	pop {r3-r5, pc}
	nop
_0205AF44: .word UNK_020F6C54

	thumb_func_start FUN_0205AF48
FUN_0205AF48: ; 0x0205AF48
	mov r1, #0x0
	str r1, [r0, #0x8]
	mov r1, #0x1
	str r1, [r0, #0x0]
	add r0, r1, #0x0
	bx lr

	thumb_func_start FUN_0205AF54
FUN_0205AF54: ; 0x0205AF54
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0205AD98
	cmp r0, #0x0
	bne _0205AF66
	mov r0, #0x0
	pop {r4, pc}
_0205AF66:
	mov r0, #0x2
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205AF70
FUN_0205AF70: ; 0x0205AF70
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0xc]
	ldrh r1, [r1, #0x0]
	bl FUN_0205ADDC
	mov r0, #0x3
	str r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205AF88
FUN_0205AF88: ; 0x0205AF88
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0205AE28
	cmp r0, #0x0
	bne _0205AF9A
	mov r0, #0x0
	pop {r4, pc}
_0205AF9A:
	mov r0, #0x4
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205AFA4
FUN_0205AFA4: ; 0x0205AFA4
	ldr r1, [r0, #0x8]
	ldr r3, [r0, #0x10]
	add r2, r1, #0x1
	str r2, [r0, #0x8]
	ldrh r1, [r3, #0x2]
	cmp r2, r1
	bge _0205AFBA
	mov r1, #0x1
	str r1, [r0, #0x0]
	add r0, r1, #0x0
	bx lr
_0205AFBA:
	add r1, r3, #0x4
	str r1, [r0, #0x10]
	ldrh r1, [r3, #0x4]
	cmp r1, #0xfe
	beq _0205AFCC
	mov r1, #0x0
	str r1, [r0, #0x0]
	mov r0, #0x1
	bx lr
_0205AFCC:
	mov r1, #0x1
	str r1, [r0, #0x4]
	mov r1, #0x5
	str r1, [r0, #0x0]
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0205AFD8
FUN_0205AFD8: ; 0x0205AFD8
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0205AFDC
FUN_0205AFDC: ; 0x0205AFDC
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r4, r1, #0x0
	cmp r7, #0x4
	blt _0205AFEA
	bl ErrorHandling
_0205AFEA:
	ldr r3, _0205B01C ; =UNK_020F6308
	ldr r6, [r3, #0x0]
	cmp r6, #0x0
	beq _0205B014
	mov r1, #0x0
_0205AFF4:
	add r2, r1, #0x0
	add r5, r6, #0x0
_0205AFF8:
	ldr r0, [r5, #0x0]
	cmp r4, r0
	bne _0205B004
	lsl r0, r7, #0x2
	ldr r0, [r6, r0]
	pop {r3-r7, pc}
_0205B004:
	add r2, r2, #0x1
	add r5, r5, #0x4
	cmp r2, #0x4
	blt _0205AFF8
	add r3, r3, #0x4
	ldr r6, [r3, #0x0]
	cmp r6, #0x0
	bne _0205AFF4
_0205B014:
	bl ErrorHandling
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_0205B01C: .word UNK_020F6308

	thumb_func_start FUN_0205B020
FUN_0205B020: ; 0x0205B020
	push {r4-r5}
	ldr r4, _0205B054 ; =UNK_020F6308
	ldr r5, [r4, #0x0]
	cmp r5, #0x0
	beq _0205B04A
	mov r2, #0x0
_0205B02C:
	add r3, r2, #0x0
_0205B02E:
	ldr r1, [r5, #0x0]
	cmp r0, r1
	bne _0205B03A
	add r0, r3, #0x0
	pop {r4-r5}
	bx lr
_0205B03A:
	add r3, r3, #0x1
	add r5, r5, #0x4
	cmp r3, #0x4
	blt _0205B02E
	add r4, r4, #0x4
	ldr r5, [r4, #0x0]
	cmp r5, #0x0
	bne _0205B02C
_0205B04A:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r5}
	bx lr
	nop
_0205B054: .word UNK_020F6308

	thumb_func_start FUN_0205B058
FUN_0205B058: ; 0x0205B058
	push {r3-r5, lr}
	add r5, r0, #0x0
_0205B05C:
	add r0, r5, #0x0
	bl FUN_020586F0
	add r4, r0, #0x0
	cmp r4, #0xff
	beq _0205B07C
	add r0, r5, #0x0
	bl FUN_02058710
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205B0B4
	cmp r0, #0x0
	bne _0205B05C
_0205B07C:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205B080
FUN_0205B080: ; 0x0205B080
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0205B058
	add r0, r4, #0x0
	mov r1, #0x20
	bl FUN_0205842C
	cmp r0, #0x0
	bne _0205B098
	mov r0, #0x0
	pop {r4, pc}
_0205B098:
	add r0, r4, #0x0
	mov r1, #0x20
	bl FUN_02058418
	add r0, r4, #0x0
	mov r1, #0xff
	bl FUN_020586E8
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020586F8
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0205B0B4
FUN_0205B0B4: ; 0x0205B0B4
	push {r3, lr}
	lsl r3, r1, #0x2
	ldr r1, _0205B0C4 ; =UNK_020F6440
	ldr r3, [r1, r3]
	lsl r1, r2, #0x2
	ldr r1, [r3, r1]
	blx r1
	pop {r3, pc}
	.balign 4
_0205B0C4: .word UNK_020F6440

	thumb_func_start FUN_0205B0C8
FUN_0205B0C8: ; 0x0205B0C8
	push {r3, lr}
	mov r1, #0x20
	bl FUN_02058410
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0205B0D4
FUN_0205B0D4: ; 0x0205B0D4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020584AC
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r4, #0x0
	bl FUN_02059C60
	add r0, r4, #0x0
	bl FUN_02058700
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205B0F4
FUN_0205B0F4: ; 0x0205B0F4
	push {r3, lr}
	mov r1, #0x0
	bl FUN_0205B0D4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B100
FUN_0205B100: ; 0x0205B100
	push {r3, lr}
	mov r1, #0x1
	bl FUN_0205B0D4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B10C
FUN_0205B10C: ; 0x0205B10C
	push {r3, lr}
	mov r1, #0x2
	bl FUN_0205B0D4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B118
FUN_0205B118: ; 0x0205B118
	push {r3, lr}
	mov r1, #0x3
	bl FUN_0205B0D4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B124
FUN_0205B124: ; 0x0205B124
	push {r3-r7, lr}
	add r4, r1, #0x0
	mov r1, #0xc
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_020585DC
	add r1, sp, #0x8
	ldrh r1, [r1, #0x10]
	strh r1, [r0, #0x0]
	strh r7, [r0, #0x2]
	str r4, [r0, #0x4]
	str r6, [r0, #0x8]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02059C0C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020584D8
	add r1, sp, #0x8
	ldrh r1, [r1, #0x10]
	add r0, r5, #0x0
	bl FUN_02058544
	add r0, r5, #0x0
	mov r1, #0x4
	bl FUN_02058410
	add r0, r5, #0x0
	bl FUN_02058700
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0205B16C
FUN_0205B16C: ; 0x0205B16C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02058600
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_02059CC8
	add r0, r5, #0x0
	bl FUN_02059D1C
	mov r0, #0x2
	ldrsh r1, [r4, r0]
	sub r1, r1, #0x1
	strh r1, [r4, #0x2]
	ldrsh r0, [r4, r0]
	cmp r0, #0x0
	ble _0205B198
	mov r0, #0x0
	pop {r3-r5, pc}
_0205B198:
	add r0, r5, #0x0
	mov r1, #0x28
	bl FUN_02058410
	add r0, r5, #0x0
	bl FUN_02059C60
	add r0, r5, #0x0
	bl FUN_020586A0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r5, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205B1C0
FUN_0205B1C0: ; 0x0205B1C0
	push {r3, lr}
	mov r2, #0x1
	str r2, [sp, #0x0]
	mov r1, #0x0
	lsl r2, r2, #0xb
	mov r3, #0x20
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B1D4
FUN_0205B1D4: ; 0x0205B1D4
	push {r3, lr}
	mov r1, #0x1
	lsl r2, r1, #0xb
	mov r3, #0x20
	str r1, [sp, #0x0]
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B1E8
FUN_0205B1E8: ; 0x0205B1E8
	push {r3, lr}
	mov r1, #0x1
	str r1, [sp, #0x0]
	mov r1, #0x2
	lsl r2, r1, #0xa
	mov r3, #0x20
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B1FC
FUN_0205B1FC: ; 0x0205B1FC
	push {r3, lr}
	mov r2, #0x1
	str r2, [sp, #0x0]
	mov r1, #0x3
	lsl r2, r2, #0xb
	mov r3, #0x20
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B210
FUN_0205B210: ; 0x0205B210
	push {r3, lr}
	mov r2, #0x2
	str r2, [sp, #0x0]
	mov r1, #0x0
	lsl r2, r2, #0xb
	mov r3, #0x10
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B224
FUN_0205B224: ; 0x0205B224
	push {r3, lr}
	mov r1, #0x2
	str r1, [sp, #0x0]
	mov r1, #0x1
	lsl r2, r1, #0xc
	mov r3, #0x10
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B238
FUN_0205B238: ; 0x0205B238
	push {r3, lr}
	mov r1, #0x2
	lsl r2, r1, #0xb
	mov r3, #0x10
	str r1, [sp, #0x0]
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B24C
FUN_0205B24C: ; 0x0205B24C
	push {r3, lr}
	mov r2, #0x2
	str r2, [sp, #0x0]
	mov r1, #0x3
	lsl r2, r2, #0xb
	mov r3, #0x10
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B260
FUN_0205B260: ; 0x0205B260
	push {r3, lr}
	mov r1, #0x3
	mov r2, #0x2
	str r1, [sp, #0x0]
	mov r1, #0x0
	lsl r2, r2, #0xc
	mov r3, #0x8
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B278
FUN_0205B278: ; 0x0205B278
	push {r3, lr}
	mov r1, #0x3
	str r1, [sp, #0x0]
	mov r1, #0x1
	lsl r2, r1, #0xd
	mov r3, #0x8
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B28C
FUN_0205B28C: ; 0x0205B28C
	push {r3, lr}
	mov r1, #0x3
	str r1, [sp, #0x0]
	mov r1, #0x2
	lsl r2, r1, #0xc
	mov r3, #0x8
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B2A0
FUN_0205B2A0: ; 0x0205B2A0
	push {r3, lr}
	mov r2, #0x2
	mov r1, #0x3
	lsl r2, r2, #0xc
	mov r3, #0x8
	str r1, [sp, #0x0]
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B2B4
FUN_0205B2B4: ; 0x0205B2B4
	push {r3, lr}
	mov r3, #0x4
	mov r1, #0x0
	lsl r2, r3, #0xc
	str r3, [sp, #0x0]
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B2C8
FUN_0205B2C8: ; 0x0205B2C8
	push {r3, lr}
	mov r1, #0x1
	mov r3, #0x4
	lsl r2, r1, #0xe
	str r3, [sp, #0x0]
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B2DC
FUN_0205B2DC: ; 0x0205B2DC
	push {r3, lr}
	mov r1, #0x2
	mov r3, #0x4
	lsl r2, r1, #0xd
	str r3, [sp, #0x0]
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B2F0
FUN_0205B2F0: ; 0x0205B2F0
	push {r3, lr}
	mov r3, #0x4
	mov r1, #0x3
	lsl r2, r3, #0xc
	str r3, [sp, #0x0]
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B304
FUN_0205B304: ; 0x0205B304
	push {r3, lr}
	mov r1, #0x5
	mov r2, #0x2
	str r1, [sp, #0x0]
	mov r1, #0x0
	lsl r2, r2, #0xe
	mov r3, #0x2
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B31C
FUN_0205B31C: ; 0x0205B31C
	push {r3, lr}
	mov r1, #0x5
	str r1, [sp, #0x0]
	mov r1, #0x1
	lsl r2, r1, #0xf
	mov r3, #0x2
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B330
FUN_0205B330: ; 0x0205B330
	push {r3, lr}
	mov r1, #0x5
	str r1, [sp, #0x0]
	mov r1, #0x2
	lsl r2, r1, #0xe
	add r3, r1, #0x0
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B344
FUN_0205B344: ; 0x0205B344
	push {r3, lr}
	mov r1, #0x5
	mov r2, #0x2
	str r1, [sp, #0x0]
	mov r1, #0x3
	lsl r2, r2, #0xe
	mov r3, #0x2
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B35C
FUN_0205B35C: ; 0x0205B35C
	push {r3, lr}
	mov r2, #0x1
	mov r1, #0x0
	lsl r2, r2, #0x10
	mov r3, #0x1
	str r1, [sp, #0x0]
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B370
FUN_0205B370: ; 0x0205B370
	push {r3, lr}
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r1, #0x1
	lsl r2, r1, #0x10
	add r3, r1, #0x0
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B384
FUN_0205B384: ; 0x0205B384
	push {r3, lr}
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r1, #0x2
	lsl r2, r1, #0xf
	mov r3, #0x1
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B398
FUN_0205B398: ; 0x0205B398
	push {r3, lr}
	mov r1, #0x0
	mov r2, #0x1
	str r1, [sp, #0x0]
	mov r1, #0x3
	lsl r2, r2, #0x10
	mov r3, #0x1
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B3B0
FUN_0205B3B0: ; 0x0205B3B0
	push {r3, lr}
	mov r1, #0x9
	mov r2, #0x1
	str r1, [sp, #0x0]
	mov r1, #0x0
	lsl r2, r2, #0xe
	mov r3, #0x4
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B3C8
FUN_0205B3C8: ; 0x0205B3C8
	push {r3, lr}
	mov r1, #0x9
	str r1, [sp, #0x0]
	mov r1, #0x1
	lsl r2, r1, #0xe
	mov r3, #0x4
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B3DC
FUN_0205B3DC: ; 0x0205B3DC
	push {r3, lr}
	mov r1, #0x9
	str r1, [sp, #0x0]
	mov r1, #0x2
	lsl r2, r1, #0xd
	mov r3, #0x4
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B3F0
FUN_0205B3F0: ; 0x0205B3F0
	push {r3, lr}
	mov r1, #0x9
	mov r2, #0x1
	str r1, [sp, #0x0]
	mov r1, #0x3
	lsl r2, r2, #0xe
	mov r3, #0x4
	bl FUN_0205B124
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205B408
FUN_0205B408: ; 0x0205B408
	push {r3-r7, lr}
	add r7, r1, #0x0
	add r6, r2, #0x0
	add r4, r3, #0x0
	mov r1, #0xc
	add r5, r0, #0x0
	bl FUN_020585DC
	strh r4, [r0, #0x0]
	add r1, r6, #0x1
	strh r1, [r0, #0x2]
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_020584AC
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02058544
	add r0, r5, #0x0
	bl FUN_02059C60
	add r0, r5, #0x0
	bl FUN_02058700
	pop {r3-r7, pc}

	thumb_func_start FUN_0205B43C
FUN_0205B43C: ; 0x0205B43C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058600
	mov r1, #0x2
	ldrsh r2, [r0, r1]
	sub r2, r2, #0x1
	strh r2, [r0, #0x2]
	ldrsh r0, [r0, r1]
	cmp r0, #0x0
	ble _0205B456
	mov r0, #0x0
	pop {r4, pc}
_0205B456:
	add r0, r4, #0x0
	mov r1, #0x20
	bl FUN_02058410
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0205B470
FUN_0205B470: ; 0x0205B470
	push {r3, lr}
	mov r1, #0x0
	mov r2, #0x20
	mov r3, #0x1
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B480
FUN_0205B480: ; 0x0205B480
	push {r3, lr}
	mov r1, #0x1
	mov r2, #0x20
	add r3, r1, #0x0
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B490
FUN_0205B490: ; 0x0205B490
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x20
	mov r3, #0x1
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B4A0
FUN_0205B4A0: ; 0x0205B4A0
	push {r3, lr}
	mov r1, #0x3
	mov r2, #0x20
	mov r3, #0x1
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B4B0
FUN_0205B4B0: ; 0x0205B4B0
	push {r3, lr}
	mov r1, #0x0
	mov r2, #0x10
	mov r3, #0x2
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B4C0
FUN_0205B4C0: ; 0x0205B4C0
	push {r3, lr}
	mov r1, #0x1
	mov r2, #0x10
	mov r3, #0x2
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B4D0
FUN_0205B4D0: ; 0x0205B4D0
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x10
	add r3, r1, #0x0
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B4E0
FUN_0205B4E0: ; 0x0205B4E0
	push {r3, lr}
	mov r1, #0x3
	mov r2, #0x10
	mov r3, #0x2
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B4F0
FUN_0205B4F0: ; 0x0205B4F0
	push {r3, lr}
	mov r1, #0x0
	mov r2, #0x8
	mov r3, #0x3
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B500
FUN_0205B500: ; 0x0205B500
	push {r3, lr}
	mov r1, #0x1
	mov r2, #0x8
	mov r3, #0x3
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B510
FUN_0205B510: ; 0x0205B510
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x8
	mov r3, #0x3
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B520
FUN_0205B520: ; 0x0205B520
	push {r3, lr}
	mov r1, #0x3
	mov r2, #0x8
	add r3, r1, #0x0
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B530
FUN_0205B530: ; 0x0205B530
	push {r3, lr}
	mov r2, #0x4
	mov r1, #0x0
	add r3, r2, #0x0
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B540
FUN_0205B540: ; 0x0205B540
	push {r3, lr}
	mov r2, #0x4
	mov r1, #0x1
	add r3, r2, #0x0
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B550
FUN_0205B550: ; 0x0205B550
	push {r3, lr}
	mov r2, #0x4
	mov r1, #0x2
	add r3, r2, #0x0
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B560
FUN_0205B560: ; 0x0205B560
	push {r3, lr}
	mov r2, #0x4
	mov r1, #0x3
	add r3, r2, #0x0
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B570
FUN_0205B570: ; 0x0205B570
	push {r3, lr}
	mov r1, #0x0
	mov r2, #0x2
	mov r3, #0x5
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B580
FUN_0205B580: ; 0x0205B580
	push {r3, lr}
	mov r1, #0x1
	mov r2, #0x2
	mov r3, #0x5
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B590
FUN_0205B590: ; 0x0205B590
	push {r3, lr}
	mov r1, #0x2
	add r2, r1, #0x0
	mov r3, #0x5
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B5A0
FUN_0205B5A0: ; 0x0205B5A0
	push {r3, lr}
	mov r1, #0x3
	mov r2, #0x2
	mov r3, #0x5
	bl FUN_0205B408
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B5B0
FUN_0205B5B0: ; 0x0205B5B0
	push {r3-r7, lr}
	add r4, r1, #0x0
	mov r1, #0x10
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_020585DC
	strb r4, [r0, #0xc]
	str r6, [r0, #0x0]
	strb r7, [r0, #0xd]
	add r2, sp, #0x8
	ldrh r1, [r2, #0x10]
	strb r1, [r0, #0xe]
	mov r1, #0x14
	ldrsh r1, [r2, r1]
	cmp r6, #0x0
	strb r1, [r0, #0xf]
	ldrh r1, [r2, #0x18]
	strh r1, [r0, #0x8]
	bne _0205B5E2
	add r0, r5, #0x0
	bl FUN_02059C60
	b _0205B5EA
_0205B5E2:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02059C0C
_0205B5EA:
	ldr r1, _0205B614 ; =0x00010004
	add r0, r5, #0x0
	bl FUN_02058410
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020584D8
	add r1, sp, #0x8
	ldrh r1, [r1, #0x10]
	add r0, r5, #0x0
	bl FUN_02058544
	add r0, r5, #0x0
	bl FUN_02058700
	ldr r0, _0205B618 ; =0x0000060B
	bl FUN_020054C8
	pop {r3-r7, pc}
	nop
_0205B614: .word 0x00010004
_0205B618: .word 0x0000060B

	thumb_func_start FUN_0205B61C
FUN_0205B61C: ; 0x0205B61C
	push {r3-r5, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	bl FUN_02058600
	add r4, r0, #0x0
	ldr r2, [r4, #0x0]
	cmp r2, #0x0
	beq _0205B66C
	mov r1, #0xc
	ldrsb r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02059CC8
	add r0, r5, #0x0
	bl FUN_02059D1C
	mov r0, #0x1
	ldr r1, [r4, #0x4]
	lsl r0, r0, #0x10
	cmp r1, r0
	blt _0205B65E
	mov r0, #0x0
	str r0, [r4, #0x4]
	mov r1, #0xc
	ldrsb r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02059C0C
	add r0, r5, #0x0
	mov r1, #0x4
	bl FUN_02058410
_0205B65E:
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	bge _0205B666
	neg r1, r1
_0205B666:
	ldr r0, [r4, #0x4]
	add r0, r0, r1
	str r0, [r4, #0x4]
_0205B66C:
	ldrh r1, [r4, #0xa]
	ldrh r0, [r4, #0x8]
	add r0, r1, r0
	strh r0, [r4, #0xa]
	mov r0, #0xf
	ldrh r1, [r4, #0xa]
	lsl r0, r0, #0x8
	cmp r1, r0
	bls _0205B680
	strh r0, [r4, #0xa]
_0205B680:
	mov r1, #0xf
	ldrsb r1, [r4, r1]
	ldrh r0, [r4, #0xa]
	lsl r2, r1, #0x2
	ldr r1, _0205B6F8 ; =UNK_02105F9C
	lsr r0, r0, #0x8
	lsl r0, r0, #0x10
	ldr r2, [r1, r2]
	mov r1, #0x0
	str r1, [sp, #0xc]
	lsr r0, r0, #0xe
	ldr r0, [r2, r0]
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	add r0, r5, #0x0
	add r1, sp, #0xc
	bl FUN_02058B94
	mov r0, #0xd
	ldrsb r1, [r4, r0]
	sub r1, r1, #0x1
	strb r1, [r4, #0xd]
	ldrsb r0, [r4, r0]
	cmp r0, #0x0
	ble _0205B6B8
	add sp, #0x18
	mov r0, #0x0
	pop {r3-r5, pc}
_0205B6B8:
	add r1, sp, #0x0
	mov r0, #0x0
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	str r0, [r1, #0x8]
	add r0, r5, #0x0
	bl FUN_02058B94
	ldr r1, _0205B6FC ; =0x00020028
	add r0, r5, #0x0
	bl FUN_02058410
	add r0, r5, #0x0
	bl FUN_02059C60
	add r0, r5, #0x0
	bl FUN_020586A0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r5, #0x0
	bl FUN_02058700
	ldr r0, _0205B700 ; =0x00000647
	bl FUN_020054C8
	mov r0, #0x1
	add sp, #0x18
	pop {r3-r5, pc}
	nop
_0205B6F8: .word UNK_02105F9C
_0205B6FC: .word 0x00020028
_0205B700: .word 0x00000647

	thumb_func_start FUN_0205B704
FUN_0205B704: ; 0x0205B704
	push {lr}
	sub sp, #0xc
	mov r2, #0x2
	str r2, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x4]
	add r2, #0xfe
	str r2, [sp, #0x8]
	add r2, r1, #0x0
	mov r3, #0x10
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_0205B724
FUN_0205B724: ; 0x0205B724
	push {lr}
	sub sp, #0xc
	mov r1, #0x2
	str r1, [sp, #0x0]
	mov r2, #0x0
	str r2, [sp, #0x4]
	add r1, #0xfe
	str r1, [sp, #0x8]
	mov r1, #0x1
	mov r3, #0x10
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_0205B744
FUN_0205B744: ; 0x0205B744
	push {lr}
	sub sp, #0xc
	mov r1, #0x2
	add r3, r1, #0x0
	str r1, [sp, #0x0]
	mov r2, #0x0
	str r2, [sp, #0x4]
	add r3, #0xfe
	str r3, [sp, #0x8]
	mov r3, #0x10
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_0205B764
FUN_0205B764: ; 0x0205B764
	push {lr}
	sub sp, #0xc
	mov r1, #0x2
	str r1, [sp, #0x0]
	mov r2, #0x0
	str r2, [sp, #0x4]
	add r1, #0xfe
	str r1, [sp, #0x8]
	mov r1, #0x3
	mov r3, #0x10
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_0205B784
FUN_0205B784: ; 0x0205B784
	push {lr}
	sub sp, #0xc
	mov r1, #0x3
	str r1, [sp, #0x0]
	mov r1, #0x0
	mov r2, #0x2
	str r1, [sp, #0x4]
	lsl r2, r2, #0x8
	str r2, [sp, #0x8]
	add r2, r1, #0x0
	mov r3, #0x8
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_0205B7A4
FUN_0205B7A4: ; 0x0205B7A4
	push {lr}
	sub sp, #0xc
	mov r1, #0x3
	str r1, [sp, #0x0]
	mov r2, #0x0
	mov r1, #0x2
	str r2, [sp, #0x4]
	lsl r1, r1, #0x8
	str r1, [sp, #0x8]
	mov r1, #0x1
	mov r3, #0x8
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_0205B7C4
FUN_0205B7C4: ; 0x0205B7C4
	push {lr}
	sub sp, #0xc
	mov r1, #0x3
	str r1, [sp, #0x0]
	mov r2, #0x0
	mov r1, #0x2
	str r2, [sp, #0x4]
	lsl r1, r1, #0x8
	str r1, [sp, #0x8]
	mov r1, #0x2
	mov r3, #0x8
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_0205B7E4
FUN_0205B7E4: ; 0x0205B7E4
	push {lr}
	sub sp, #0xc
	mov r1, #0x3
	mov r3, #0x2
	str r1, [sp, #0x0]
	mov r2, #0x0
	str r2, [sp, #0x4]
	lsl r3, r3, #0x8
	str r3, [sp, #0x8]
	mov r3, #0x8
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_0205B804
FUN_0205B804: ; 0x0205B804
	push {lr}
	sub sp, #0xc
	mov r1, #0x3
	str r1, [sp, #0x0]
	mov r1, #0x0
	mov r2, #0x2
	str r1, [sp, #0x4]
	lsl r2, r2, #0x8
	str r2, [sp, #0x8]
	lsl r2, r2, #0x4
	mov r3, #0x8
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_0205B824
FUN_0205B824: ; 0x0205B824
	push {lr}
	sub sp, #0xc
	mov r1, #0x3
	str r1, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x4]
	mov r1, #0x2
	lsl r1, r1, #0x8
	str r1, [sp, #0x8]
	mov r1, #0x1
	lsl r2, r1, #0xd
	mov r3, #0x8
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_0205B848
FUN_0205B848: ; 0x0205B848
	push {lr}
	sub sp, #0xc
	mov r1, #0x3
	str r1, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x4]
	mov r1, #0x2
	lsl r1, r1, #0x8
	str r1, [sp, #0x8]
	mov r1, #0x2
	lsl r2, r1, #0xc
	mov r3, #0x8
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_0205B86C
FUN_0205B86C: ; 0x0205B86C
	push {lr}
	sub sp, #0xc
	mov r1, #0x3
	str r1, [sp, #0x0]
	mov r2, #0x0
	str r2, [sp, #0x4]
	mov r2, #0x2
	lsl r2, r2, #0x8
	str r2, [sp, #0x8]
	lsl r2, r2, #0x4
	mov r3, #0x8
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_0205B88C
FUN_0205B88C: ; 0x0205B88C
	push {lr}
	sub sp, #0xc
	mov r2, #0x3
	str r2, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x4]
	add r2, #0xfd
	str r2, [sp, #0x8]
	mov r2, #0x2
	lsl r2, r2, #0xc
	mov r3, #0x10
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_0205B8AC
FUN_0205B8AC: ; 0x0205B8AC
	push {lr}
	sub sp, #0xc
	mov r2, #0x3
	str r2, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x4]
	add r2, #0xfd
	mov r1, #0x1
	str r2, [sp, #0x8]
	lsl r2, r1, #0xd
	mov r3, #0x10
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_0205B8CC
FUN_0205B8CC: ; 0x0205B8CC
	push {lr}
	sub sp, #0xc
	mov r2, #0x3
	str r2, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x4]
	add r2, #0xfd
	mov r1, #0x2
	str r2, [sp, #0x8]
	lsl r2, r1, #0xc
	mov r3, #0x10
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_0205B8EC
FUN_0205B8EC: ; 0x0205B8EC
	push {lr}
	sub sp, #0xc
	mov r1, #0x3
	str r1, [sp, #0x0]
	mov r2, #0x0
	str r2, [sp, #0x4]
	add r2, r1, #0x0
	add r2, #0xfd
	str r2, [sp, #0x8]
	mov r2, #0x2
	lsl r2, r2, #0xc
	mov r3, #0x10
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_0205B910
FUN_0205B910: ; 0x0205B910
	push {lr}
	sub sp, #0xc
	mov r1, #0xa
	str r1, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x4]
	mov r1, #0xf0
	str r1, [sp, #0x8]
	mov r1, #0x2
	lsl r2, r1, #0xb
	mov r3, #0x10
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_0205B930
FUN_0205B930: ; 0x0205B930
	push {lr}
	sub sp, #0xc
	mov r1, #0xa
	str r1, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x4]
	mov r1, #0xf0
	mov r2, #0x1
	str r1, [sp, #0x8]
	mov r1, #0x3
	lsl r2, r2, #0xc
	mov r3, #0x10
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_0205B954
FUN_0205B954: ; 0x0205B954
	push {lr}
	sub sp, #0xc
	mov r1, #0xb
	str r1, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x4]
	mov r1, #0x5
	lsl r1, r1, #0x6
	str r1, [sp, #0x8]
	mov r1, #0x2
	lsl r2, r1, #0xd
	mov r3, #0xc
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_0205B978
FUN_0205B978: ; 0x0205B978
	push {lr}
	sub sp, #0xc
	mov r1, #0xb
	str r1, [sp, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x4]
	mov r1, #0x5
	lsl r1, r1, #0x6
	mov r2, #0x1
	str r1, [sp, #0x8]
	mov r1, #0x3
	lsl r2, r2, #0xe
	mov r3, #0xc
	bl FUN_0205B5B0
	mov r0, #0x1
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_0205B99C
FUN_0205B99C: ; 0x0205B99C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	mov r1, #0x4
	bl FUN_020585DC
	str r4, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_02058700
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205B9B4
FUN_0205B9B4: ; 0x0205B9B4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058600
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0205B9CA
	sub r1, r1, #0x1
	str r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4, pc}
_0205B9CA:
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0205B9D4
FUN_0205B9D4: ; 0x0205B9D4
	push {r3, lr}
	mov r1, #0x1
	bl FUN_0205B99C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B9E0
FUN_0205B9E0: ; 0x0205B9E0
	push {r3, lr}
	mov r1, #0x2
	bl FUN_0205B99C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B9EC
FUN_0205B9EC: ; 0x0205B9EC
	push {r3, lr}
	mov r1, #0x4
	bl FUN_0205B99C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205B9F8
FUN_0205B9F8: ; 0x0205B9F8
	push {r3, lr}
	mov r1, #0x8
	bl FUN_0205B99C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BA04
FUN_0205BA04: ; 0x0205BA04
	push {r3, lr}
	mov r1, #0xf
	bl FUN_0205B99C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BA10
FUN_0205BA10: ; 0x0205BA10
	push {r3, lr}
	mov r1, #0x10
	bl FUN_0205B99C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BA1C
FUN_0205BA1C: ; 0x0205BA1C
	push {r3, lr}
	mov r1, #0x20
	bl FUN_0205B99C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BA28
FUN_0205BA28: ; 0x0205BA28
	push {r4, lr}
	mov r1, #0x8
	add r4, r0, #0x0
	bl FUN_020585DC
	mov r1, #0x1
	lsl r1, r1, #0x10
	str r1, [r0, #0x4]
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205BA4C
FUN_0205BA4C: ; 0x0205BA4C
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl FUN_02058600
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, [r4, #0x4]
	add r0, r1, r0
	str r0, [r4, #0x0]
	add r1, sp, #0x0
	mov r0, #0x0
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	str r0, [r1, #0x8]
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02058B94
	ldr r1, [r4, #0x0]
	asr r0, r1, #0xe
	lsr r0, r0, #0x11
	add r0, r1, r0
	asr r0, r0, #0xf
	cmp r0, #0x28
	bge _0205BA88
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r5, pc}
_0205BA88:
	add r0, r5, #0x0
	bl FUN_02058700
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r5, pc}

	thumb_func_start FUN_0205BA94
FUN_0205BA94: ; 0x0205BA94
	push {r4, lr}
	mov r1, #0x8
	add r4, r0, #0x0
	bl FUN_020585DC
	mov r1, #0x5
	lsl r1, r1, #0x12
	str r1, [r0, #0x0]
	ldr r1, _0205BABC ; =0xFFFF0000
	str r1, [r0, #0x4]
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4, pc}
	nop
_0205BABC: .word 0xFFFF0000

	thumb_func_start FUN_0205BAC0
FUN_0205BAC0: ; 0x0205BAC0
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl FUN_02058600
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, [r4, #0x4]
	add r0, r1, r0
	str r0, [r4, #0x0]
	bpl _0205BADA
	mov r0, #0x0
	str r0, [r4, #0x0]
_0205BADA:
	add r1, sp, #0x0
	mov r0, #0x0
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	str r0, [r1, #0x8]
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02058B94
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	ble _0205BAFA
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r5, pc}
_0205BAFA:
	add r0, r5, #0x0
	bl FUN_02058700
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_0205BB08
FUN_0205BB08: ; 0x0205BB08
	push {r4, lr}
	mov r1, #0x2
	add r4, r0, #0x0
	lsl r1, r1, #0x8
	bl FUN_02058410
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205BB20
FUN_0205BB20: ; 0x0205BB20
	push {r4, lr}
	mov r1, #0x2
	add r4, r0, #0x0
	lsl r1, r1, #0x8
	bl FUN_02058418
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205BB38
FUN_0205BB38: ; 0x0205BB38
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x80
	bl FUN_02058410
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0205BB4C
FUN_0205BB4C: ; 0x0205BB4C
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x80
	bl FUN_02058418
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0205BB60
FUN_0205BB60: ; 0x0205BB60
	push {r4, lr}
	mov r1, #0x1
	add r4, r0, #0x0
	lsl r1, r1, #0x8
	bl FUN_02058410
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205BB78
FUN_0205BB78: ; 0x0205BB78
	push {r4, lr}
	mov r1, #0x1
	add r4, r0, #0x0
	lsl r1, r1, #0x8
	bl FUN_02058418
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205BB90
FUN_0205BB90: ; 0x0205BB90
	push {r4-r6, lr}
	add r6, r1, #0x0
	mov r1, #0x8
	add r5, r0, #0x0
	bl FUN_020585DC
	add r4, r0, #0x0
	str r6, [r4, #0x0]
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r2, #0x1
	bl MOD05_021E7AC0
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_02058700
	pop {r4-r6, pc}

	thumb_func_start FUN_0205BBB4
FUN_0205BBB4: ; 0x0205BBB4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02058600
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	bl MOD05_021E799C
	cmp r0, #0x1
	bne _0205BBD8
	ldr r0, [r4, #0x4]
	bl FUN_02064520
	add r0, r5, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r3-r5, pc}
_0205BBD8:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0205BBDC
FUN_0205BBDC: ; 0x0205BBDC
	push {r3, lr}
	mov r1, #0x0
	bl FUN_0205BB90
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0205BBE8
FUN_0205BBE8: ; 0x0205BBE8
	push {r3, lr}
	mov r1, #0x1
	bl FUN_0205BB90
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0205BBF4
FUN_0205BBF4: ; 0x0205BBF4
	push {r3-r7, lr}
	add r4, r1, #0x0
	mov r1, #0x8
	add r5, r0, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	bl FUN_020585DC
	strh r4, [r0, #0x0]
	strh r6, [r0, #0x2]
	strh r7, [r0, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02059C0C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020584D8
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02058544
	add r0, r5, #0x0
	mov r1, #0x4
	bl FUN_02058410
	add r0, r5, #0x0
	bl FUN_02058700
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0205BC34
FUN_0205BC34: ; 0x0205BC34
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	bl FUN_02058600
	add r4, r0, #0x0
	mov r2, #0x6
	ldrsh r2, [r4, r2]
	mov r1, #0x0
	ldrsh r1, [r4, r1]
	lsl r2, r2, #0x2
	ldr r2, [r6, r2]
	add r0, r5, #0x0
	bl FUN_02059CC8
	add r0, r5, #0x0
	bl FUN_02059D1C
	mov r0, #0x6
	ldrsh r1, [r4, r0]
	add r1, r1, #0x1
	strh r1, [r4, #0x6]
	ldrsh r1, [r4, r0]
	mov r0, #0x4
	ldrsh r0, [r4, r0]
	cmp r1, r0
	bge _0205BC6E
	mov r0, #0x0
	pop {r4-r6, pc}
_0205BC6E:
	add r0, r5, #0x0
	mov r1, #0x28
	bl FUN_02058410
	add r0, r5, #0x0
	bl FUN_02059C60
	add r0, r5, #0x0
	bl FUN_020586A0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r5, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_0205BC94
FUN_0205BC94: ; 0x0205BC94
	push {r3, lr}
	mov r2, #0x6
	mov r1, #0x0
	add r3, r2, #0x0
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BCA4
FUN_0205BCA4: ; 0x0205BCA4
	push {r3, lr}
	mov r2, #0x6
	mov r1, #0x1
	add r3, r2, #0x0
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BCB4
FUN_0205BCB4: ; 0x0205BCB4
	push {r3, lr}
	mov r2, #0x6
	mov r1, #0x2
	add r3, r2, #0x0
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BCC4
FUN_0205BCC4: ; 0x0205BCC4
	push {r3, lr}
	mov r2, #0x6
	mov r1, #0x3
	add r3, r2, #0x0
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BCD4
FUN_0205BCD4: ; 0x0205BCD4
	push {r3, lr}
	ldr r1, _0205BCE8 ; =UNK_020F6C6C
	bl FUN_0205BC34
	cmp r0, #0x1
	bne _0205BCE4
	mov r0, #0x1
	pop {r3, pc}
_0205BCE4:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0205BCE8: .word UNK_020F6C6C

	thumb_func_start FUN_0205BCEC
FUN_0205BCEC: ; 0x0205BCEC
	push {r3, lr}
	mov r1, #0x0
	mov r2, #0x3
	mov r3, #0x7
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BCFC
FUN_0205BCFC: ; 0x0205BCFC
	push {r3, lr}
	mov r1, #0x1
	mov r2, #0x3
	mov r3, #0x7
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BD0C
FUN_0205BD0C: ; 0x0205BD0C
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x3
	mov r3, #0x7
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BD1C
FUN_0205BD1C: ; 0x0205BD1C
	push {r3, lr}
	mov r1, #0x3
	add r2, r1, #0x0
	mov r3, #0x7
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BD2C
FUN_0205BD2C: ; 0x0205BD2C
	push {r3, lr}
	ldr r1, _0205BD40 ; =UNK_020F6C48
	bl FUN_0205BC34
	cmp r0, #0x1
	bne _0205BD3C
	mov r0, #0x1
	pop {r3, pc}
_0205BD3C:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0205BD40: .word UNK_020F6C48

	thumb_func_start FUN_0205BD44
FUN_0205BD44: ; 0x0205BD44
	push {r3, lr}
	mov r1, #0x0
	mov r2, #0x7
	mov r3, #0x8
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BD54
FUN_0205BD54: ; 0x0205BD54
	push {r3, lr}
	mov r1, #0x1
	mov r2, #0x7
	mov r3, #0x8
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BD64
FUN_0205BD64: ; 0x0205BD64
	push {r3, lr}
	mov r1, #0x2
	mov r2, #0x7
	mov r3, #0x8
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BD74
FUN_0205BD74: ; 0x0205BD74
	push {r3, lr}
	mov r1, #0x3
	mov r2, #0x7
	mov r3, #0x8
	bl FUN_0205BBF4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0205BD84
FUN_0205BD84: ; 0x0205BD84
	push {r3, lr}
	ldr r1, _0205BD98 ; =UNK_020F6C84
	bl FUN_0205BC34
	cmp r0, #0x1
	bne _0205BD94
	mov r0, #0x1
	pop {r3, pc}
_0205BD94:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0205BD98: .word UNK_020F6C84

	thumb_func_start FUN_0205BD9C
FUN_0205BD9C: ; 0x0205BD9C
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x4
	bl FUN_020585DC
	add r0, r4, #0x0
	mov r1, #0x9
	bl FUN_02058544
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0205BDB8
FUN_0205BDB8: ; 0x0205BDB8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058600
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	cmp r1, #0x8
	blt _0205BDE0
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020584AC
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r4, #0x0
	bl FUN_02058700
_0205BDE0:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0205BDE4
FUN_0205BDE4: ; 0x0205BDE4
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	mov r1, #0x4
	bl FUN_020585DC
	add r0, r4, #0x0
	bl FUN_0205EB20
	cmp r0, #0x0
	beq _0205BDFE
	bl FUN_02064520
_0205BDFE:
	add r1, sp, #0x0
	mov r0, #0x0
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	str r0, [r1, #0x8]
	add r0, r4, #0x0
	bl FUN_02058B94
	add r0, r4, #0x0
	bl MOD06_0224D2E0
	ldr r1, _0205BE34 ; =0x00010004
	add r0, r4, #0x0
	bl FUN_02058410
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0x14
	bl FUN_02058418
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x0
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_0205BE34: .word 0x00010004

	thumb_func_start FUN_0205BE38
FUN_0205BE38: ; 0x0205BE38
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl FUN_02058600
	add r4, r0, #0x0
	ldr r0, _0205BE98 ; =UNK_02105F9C
	add r1, sp, #0x0
	ldr r2, [r0, #0x0]
	mov r0, #0x0
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	str r0, [r1, #0x8]
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x2
	ldr r0, [r2, r0]
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02058B94
	ldr r0, [r4, #0x0]
	add r0, r0, #0x2
	str r0, [r4, #0x0]
	cmp r0, #0x10
	bhs _0205BE70
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r5, pc}
_0205BE70:
	mov r0, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02058B94
	ldr r1, _0205BE9C ; =0x00020028
	add r0, r5, #0x0
	bl FUN_02058410
	add r0, r5, #0x0
	bl FUN_0205EB2C
	add r0, r5, #0x0
	bl FUN_02058700
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r5, pc}
	nop
_0205BE98: .word UNK_02105F9C
_0205BE9C: .word 0x00020028

	thumb_func_start FUN_0205BEA0
FUN_0205BEA0: ; 0x0205BEA0
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x4
	bl FUN_020585DC
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0205BEBC
FUN_0205BEBC: ; 0x0205BEBC
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x4
	bl FUN_020585DC
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02058544
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0205BED8
FUN_0205BED8: ; 0x0205BED8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058600
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	cmp r1, #0x15
	bhs _0205BEEE
	mov r0, #0x0
	pop {r4, pc}
_0205BEEE:
	add r0, r4, #0x0
	bl FUN_02058700
	mov r0, #0x1
	pop {r4, pc}
