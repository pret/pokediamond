	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020ECD4C
	.extern FX_SinCosTable_

	.section .rodata











	.section .data


	.text




	thumb_func_start FUN_02007E40
FUN_02007E40: ; 0x02007E40
	push {r4-r5}
	ldr r5, [r0, #0x54]
	mov r4, #0x2
	orr r4, r5
	str r4, [r0, #0x54]
	add r4, r0, #0x0
	add r4, #0x44
	strb r1, [r4, #0x0]
	add r1, r0, #0x0
	add r1, #0x45
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x46
	strb r3, [r1, #0x0]
	ldr r1, [sp, #0x8]
	add r0, #0x47
	strb r1, [r0, #0x0]
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_02007E68
FUN_02007E68: ; 0x02007E68
	push {r4-r5}
	mov r4, #0x1
	ldr r5, [r0, #0x54]
	lsl r4, r4, #0xc
	orr r4, r5
	str r4, [r0, #0x54]
	add r4, r0, #0x0
	add r4, #0x48
	strb r1, [r4, #0x0]
	add r1, r0, #0x0
	add r1, #0x49
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	mov r2, #0x0
	add r1, #0x4a
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x4b
	strb r3, [r1, #0x0]
	ldr r1, [sp, #0x8]
	str r1, [r0, #0x4c]
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_02007E98
FUN_02007E98: ; 0x02007E98
	push {r4-r7}
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r5, r2, #0x0
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	lsl r0, r5, #0x18
	lsr r5, r0, #0x18
	lsl r0, r3, #0x18
	ldr r2, [sp, #0x10]
	mov r1, #0x0
	lsr r0, r0, #0x18
_02007EB0:
	ldr r3, [r4, #0x0]
	lsl r3, r3, #0x1f
	lsr r3, r3, #0x1f
	beq _02007EDE
	mov r3, #0x1
	ldr r7, [r4, #0x54]
	lsl r3, r3, #0xc
	orr r3, r7
	str r3, [r4, #0x54]
	add r3, r4, #0x0
	add r3, #0x48
	strb r6, [r3, #0x0]
	add r3, r4, #0x0
	add r3, #0x49
	add r7, r4, #0x0
	strb r5, [r3, #0x0]
	add r7, #0x4a
	mov r3, #0x0
	strb r3, [r7, #0x0]
	add r3, r4, #0x0
	add r3, #0x4b
	strb r0, [r3, #0x0]
	str r2, [r4, #0x4c]
_02007EDE:
	add r1, r1, #0x1
	add r4, #0x98
	cmp r1, #0x4
	blt _02007EB0
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_02007EEC
FUN_02007EEC: ; 0x02007EEC
	ldr r2, [r0, #0x54]
	ldr r1, _02007F1C ; =0xFFFFEFFF
	and r1, r2
	str r1, [r0, #0x54]
	add r1, r0, #0x0
	mov r2, #0x0
	add r1, #0x48
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x49
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x4a
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x4b
	strb r2, [r1, #0x0]
	str r2, [r0, #0x4c]
	mov r1, #0x1
	ldr r2, [r0, #0x0]
	lsl r1, r1, #0x8
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_02007F1C: .word 0xFFFFEFFF

	thumb_func_start FUN_02007F20
FUN_02007F20: ; 0x02007F20
	ldr r0, [r0, #0x54]
	lsl r0, r0, #0x13
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	bne _02007F2E
	mov r0, #0x1
	bx lr
_02007F2E:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02007F34
FUN_02007F34: ; 0x02007F34
	mov r2, #0x28
	sub r2, r2, r1
	mov r1, #0x36
	ldrsh r1, [r0, r1]
	mul r1, r2
	asr r1, r1, #0x8
	sub r1, r2, r1
	strh r1, [r0, #0x2e]
	bx lr
	.balign 4

	thumb_func_start FUN_02007F48
FUN_02007F48: ; 0x02007F48
	push {r4-r7}
	add r1, r0, #0x0
	add r1, #0x58
	ldrb r1, [r1, #0x0]
	add r6, r0, #0x0
	add r6, #0x59
	cmp r1, #0x0
	beq _0200800A
	add r1, r0, #0x0
	add r1, #0x5a
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02007FFE
	ldrb r1, [r6, #0x0]
	add r1, r1, #0x1
	strb r1, [r6, #0x0]
	ldrb r3, [r6, #0x0]
	mov r1, #0x84
	lsl r4, r3, #0x1
	add r2, r0, r4
	ldrsb r2, [r2, r1]
	sub r1, #0x85
	cmp r2, r1
	bge _02007FC6
	mov r2, #0x0
	sub r1, r2, #0x2
_02007F7C:
	add r4, r0, r3
	add r4, #0x5c
	ldrb r4, [r4, #0x0]
	add r3, r0, r3
	add r3, #0x5c
	add r4, r4, #0x1
	strb r4, [r3, #0x0]
	ldrb r5, [r6, #0x0]
	lsl r3, r5, #0x1
	add r4, r0, r3
	add r3, r4, #0x0
	add r7, r0, r5
	add r3, #0x85
	add r7, #0x5c
	ldrb r3, [r3, #0x0]
	ldrb r7, [r7, #0x0]
	cmp r3, r7
	beq _02007FA4
	cmp r3, #0x0
	bne _02007FAE
_02007FA4:
	add r3, r0, r5
	add r3, #0x5c
	strb r2, [r3, #0x0]
	add r6, r6, #0x1
	b _02007FB6
_02007FAE:
	mov r3, #0x84
	ldrsb r3, [r4, r3]
	sub r3, r1, r3
	strb r3, [r6, #0x0]
_02007FB6:
	ldrb r3, [r6, #0x0]
	mov r5, #0x84
	lsl r4, r3, #0x1
	add r7, r0, r4
	ldrsb r7, [r7, r5]
	sub r5, #0x85
	cmp r7, r5
	blt _02007F7C
_02007FC6:
	add r2, r0, r4
	mov r1, #0x84
	ldrsb r2, [r2, r1]
	sub r1, #0x85
	cmp r2, r1
	beq _02007FD6
	cmp r3, #0xa
	blo _02007FE6
_02007FD6:
	add r1, r0, #0x0
	mov r2, #0x0
	add r1, #0x5b
	strb r2, [r1, #0x0]
	add r0, #0x58
	strb r2, [r0, #0x0]
	pop {r4-r7}
	bx lr
_02007FE6:
	add r1, r0, #0x0
	add r1, #0x5b
	strb r2, [r1, #0x0]
	ldrb r1, [r6, #0x0]
	lsl r1, r1, #0x1
	add r1, r0, r1
	add r1, #0x85
	ldrb r1, [r1, #0x0]
	add r0, #0x5a
	strb r1, [r0, #0x0]
	pop {r4-r7}
	bx lr
_02007FFE:
	add r1, r0, #0x0
	add r1, #0x5a
	ldrb r1, [r1, #0x0]
	add r0, #0x5a
	sub r1, r1, #0x1
	strb r1, [r0, #0x0]
_0200800A:
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_02008010
FUN_02008010: ; 0x02008010
	mov r2, #0x1
	strb r2, [r0, #0x0]
	mov r3, #0x0
	strb r3, [r0, #0x2]
	ldrsb r2, [r1, r3]
	strb r2, [r0, #0x1]
	ldrb r2, [r1, #0x1]
	strb r2, [r0, #0x3]
	str r1, [r0, #0x10]
	add r2, r3, #0x0
_02008024:
	add r1, r0, r3
	add r3, r3, #0x1
	strb r2, [r1, #0x4]
	cmp r3, #0xa
	blt _02008024
	bx lr

	thumb_func_start FUN_02008030
FUN_02008030: ; 0x02008030
	push {r4-r7}
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	beq _020080C6
	add r3, r0, #0x2
	ldr r4, [r0, #0x10]
	cmp r1, #0x0
	beq _020080C0
	ldrb r1, [r0, #0x3]
	cmp r1, #0x0
	bne _020080BC
	ldrb r1, [r3, #0x0]
	add r1, r1, #0x1
	strb r1, [r3, #0x0]
	ldrb r2, [r3, #0x0]
	mov r1, #0x0
	mvn r1, r1
	lsl r5, r2, #0x1
	ldrsb r6, [r4, r5]
	cmp r6, r1
	bge _02008098
	mov r1, #0x0
_0200805C:
	add r5, r0, r2
	ldrb r2, [r5, #0x4]
	add r2, r2, #0x1
	strb r2, [r5, #0x4]
	ldrb r2, [r3, #0x0]
	add r5, r0, r2
	lsl r2, r2, #0x1
	add r2, r4, r2
	ldrb r7, [r2, #0x1]
	ldrb r6, [r5, #0x4]
	cmp r7, r6
	beq _02008078
	cmp r7, #0x0
	bne _0200807E
_02008078:
	strb r1, [r5, #0x4]
	add r3, r3, #0x1
	b _0200808A
_0200807E:
	mov r5, #0x0
	ldrsb r5, [r2, r5]
	mov r2, #0x1
	mvn r2, r2
	sub r2, r2, r5
	strb r2, [r3, #0x0]
_0200808A:
	ldrb r2, [r3, #0x0]
	mov r6, #0x0
	mvn r6, r6
	lsl r5, r2, #0x1
	ldrsb r7, [r4, r5]
	cmp r7, r6
	blt _0200805C
_02008098:
	ldrsb r5, [r4, r5]
	mov r1, #0x0
	mvn r1, r1
	cmp r5, r1
	beq _020080A6
	cmp r2, #0xa
	blo _020080AE
_020080A6:
	mov r1, #0x0
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x0]
	b _020080C0
_020080AE:
	strb r5, [r0, #0x1]
	ldrb r1, [r3, #0x0]
	lsl r1, r1, #0x1
	add r1, r4, r1
	ldrb r1, [r1, #0x1]
	strb r1, [r0, #0x3]
	b _020080C0
_020080BC:
	sub r1, r1, #0x1
	strb r1, [r0, #0x3]
_020080C0:
	ldrb r0, [r0, #0x1]
	pop {r4-r7}
	bx lr
_020080C6:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_020080D0
FUN_020080D0: ; 0x020080D0
	ldr r2, [r0, #0x0]
	mov r1, #0x80
	orr r2, r1
	add r1, #0x80
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020080E0
FUN_020080E0: ; 0x020080E0
	push {r3-r4}
	add r2, r0, #0x0
	add r3, r2, #0x0
	add r4, r2, #0x4
	add r3, #0x14
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	add r0, #0x6c
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x78
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x6e
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7a
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x70
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7c
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x72
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7e
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x74
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x80
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x76
	ldrh r0, [r0, #0x0]
	add r2, #0x82
	strh r0, [r2, #0x0]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0200813C
FUN_0200813C: ; 0x0200813C
	push {r3-r4}
	add r2, r0, #0x0
	add r4, r2, #0x0
	add r4, #0x14
	add r3, r2, #0x4
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	add r0, #0x78
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x6c
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7a
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x6e
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7c
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x70
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7e
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x72
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x80
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x74
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x82
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x76
	strh r1, [r0, #0x0]
	ldr r1, [r2, #0x0]
	mov r0, #0x80
	orr r1, r0
	add r0, #0x80
	orr r0, r1
	str r0, [r2, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_020081A8
FUN_020081A8: ; 0x020081A8
	mov r3, #0xa7
	lsl r3, r3, #0x2
	str r1, [r0, r3]
	add r1, r3, #0x4
	str r2, [r0, r1]
	bx lr

	thumb_func_start FUN_020081B4
FUN_020081B4: ; 0x020081B4
	mov r3, #0xa9
	lsl r3, r3, #0x2
	str r1, [r0, r3]
	add r1, r3, #0x4
	str r2, [r0, r1]
	bx lr

	thumb_func_start FUN_020081C0
FUN_020081C0: ; 0x020081C0
	add r0, r0, #0x4
	bx lr

	thumb_func_start FUN_020081C4
FUN_020081C4: ; 0x020081C4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02008254 ; =0x000002E1
	ldrb r1, [r4, r0]
	cmp r1, #0x0
	beq _02008212
	mov r1, #0x0
	strb r1, [r4, r0]
	sub r0, #0x81
	add r0, r4, r0
	bl NNS_G2dInitImageProxy
	mov r3, #0xae
	lsl r3, r3, #0x2
	mov r1, #0x20
	strh r1, [r4, r3]
	add r0, r3, #0x2
	strh r1, [r4, r0]
	add r0, r3, #0x0
	sub r0, #0x18
	ldr r1, [r4, r0]
	add r0, r3, #0x0
	add r0, #0x10
	str r1, [r4, r0]
	add r0, r3, #0x0
	sub r0, #0xc
	ldr r1, [r4, r0]
	add r0, r3, #0x0
	add r0, #0x14
	str r1, [r4, r0]
	add r1, r3, #0x0
	sub r1, #0x1c
	add r0, r4, r3
	sub r3, #0x58
	ldr r1, [r4, r1]
	mov r2, #0x0
	add r3, r4, r3
	bl NNS_G2dLoadImage2DMapping
_02008212:
	ldr r0, _02008258 ; =0x000002E2
	ldrb r1, [r4, r0]
	cmp r1, #0x0
	beq _02008252
	mov r1, #0x0
	strb r1, [r4, r0]
	sub r0, #0x5e
	add r0, r4, r0
	bl NNS_G2dInitImagePaletteProxy
	mov r3, #0xaa
	lsl r3, r3, #0x2
	add r0, r3, #0x0
	ldr r1, [r4, r3]
	add r0, #0x30
	str r1, [r4, r0]
	add r0, r3, #0x0
	add r0, #0x8
	ldr r1, [r4, r0]
	add r0, r3, #0x0
	add r0, #0x34
	str r1, [r4, r0]
	add r0, r3, #0x0
	sub r1, r3, #0x4
	add r0, #0x28
	sub r3, #0x24
	ldr r1, [r4, r1]
	add r0, r4, r0
	mov r2, #0x0
	add r3, r4, r3
	bl NNS_G2dLoadPalette
_02008252:
	pop {r4, pc}
	.balign 4
_02008254: .word 0x000002E1
_02008258: .word 0x000002E2

	thumb_func_start FUN_0200825C
FUN_0200825C: ; 0x0200825C
	ldr r2, _02008264 ; =0x000002E3
	strb r1, [r0, r2]
	bx lr
	nop
_02008264: .word 0x000002E3

	thumb_func_start FUN_02008268
FUN_02008268: ; 0x02008268
	push {r4, lr}
	add r4, r0, #0x0
	bne _02008272
	bl GF_AssertFail
_02008272:
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _0200827E
	mov r0, #0x1
	pop {r4, pc}
_0200827E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02008284
FUN_02008284: ; 0x02008284
	mov r2, #0xb9
	lsl r2, r2, #0x2
	ldr r3, [r0, r2]
	orr r1, r3
	str r1, [r0, r2]
	bx lr

	thumb_func_start FUN_02008290
FUN_02008290: ; 0x02008290
	push {r3-r4}
	mov r3, #0xb9
	lsl r3, r3, #0x2
	mov r2, #0x0
	mvn r2, r2
	ldr r4, [r0, r3]
	eor r1, r2
	and r1, r4
	str r1, [r0, r3]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_020082A8
FUN_020082A8: ; 0x020082A8
	push {r4-r7, lr}
	sub sp, #0x5c
	add r6, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x48]
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x48]
	str r6, [sp, #0x44]
	str r0, [sp, #0x38]
_020082BA:
	ldr r0, [sp, #0x44]
	ldr r1, [r0, #0x0]
	lsl r0, r1, #0x1f
	lsr r0, r0, #0x1f
	beq _020082CA
	lsl r0, r1, #0x18
	lsr r0, r0, #0x1f
	bne _020082CC
_020082CA:
	b _020086C2
_020082CC:
	mov r0, #0x80
	bic r1, r0
	ldr r0, [sp, #0x44]
	mov r2, #0xa6
	str r1, [r0, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x48]
	ldr r0, [sp, #0x44]
	ldr r1, [sp, #0x44]
	lsl r2, r2, #0x2
	ldrh r0, [r0, #0x4]
	ldrh r1, [r1, #0x6]
	ldr r2, [r6, r2]
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x58
	str r0, [sp, #0x4c]
	bl NNS_G2dGetUnpackedCharacterData
	ldr r0, [sp, #0x58]
	mov r1, #0xaf
	ldr r0, [r0, #0x4]
	lsl r1, r1, #0x2
	str r0, [r6, r1]
	ldr r0, [sp, #0x58]
	ldr r2, [r0, #0x8]
	add r0, r1, #0x4
	str r2, [r6, r0]
	ldr r0, [sp, #0x58]
	add r1, #0x8
	ldr r0, [r0, #0xc]
	str r0, [r6, r1]
	ldr r0, [sp, #0x58]
	ldr r0, [r0, #0x14]
	str r0, [sp, #0x50]
	bl FUN_02008A74
	ldr r0, [sp, #0x44]
	ldr r1, [sp, #0x50]
	bl FUN_020088EC
	ldr r0, [sp, #0x54]
	cmp r0, #0x3
	beq _02008326
	b _02008554
_02008326:
	mov r5, #0x0
	add r0, r5, #0x0
	str r5, [sp, #0x14]
	str r0, [sp, #0x24]
_0200832E:
	ldr r0, [sp, #0x14]
	mov r1, #0x4f
	sub r2, r1, r0
	mov r0, #0x50
	add r1, r2, #0x0
	mul r1, r0
	ldr r0, [sp, #0x50]
	mov r4, #0x0
	add r0, r0, r1
	str r0, [sp, #0x20]
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x24]
	add r7, r1, r0
	ldr r0, [sp, #0x20]
	str r7, [sp, #0x18]
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x14]
	sub r0, r0, #0x1
	lsl r0, r0, #0x7
	str r0, [sp, #0x10]
_02008356:
	cmp r4, #0x28
	bge _02008442
	ldr r0, [sp, #0x44]
	ldr r1, [r0, #0x54]
	lsl r0, r1, #0x16
	lsr r0, r0, #0x1f
	beq _02008386
	lsl r1, r1, #0x15
	lsr r1, r1, #0x1f
	beq _02008386
	mov r0, #0x27
	sub r1, r0, r4
	ldr r0, [sp, #0x1c]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r1, r4, r1
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_02008386:
	cmp r0, #0x0
	beq _020083A6
	mov r0, #0x27
	sub r1, r0, r4
	ldr r0, [sp, #0x18]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r1, r4, r1
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_020083A6:
	ldr r0, [sp, #0x44]
	ldr r0, [r0, #0x54]
	lsl r1, r0, #0x15
	lsr r1, r1, #0x1f
	beq _020083C4
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r0, [sp, #0x20]
	ldr r1, [r6, r1]
	ldrb r0, [r0, #0x0]
	add r1, r5, r1
	add r1, r4, r1
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_020083C4:
	lsl r0, r0, #0xf
	lsr r0, r0, #0x1c
	str r0, [sp, #0xc]
	beq _02008430
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x14]
	lsl r1, r1, #0x1
	bl _u32_div_f
	cmp r1, #0x0
	beq _020083F4
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r1, [r6, r0]
	ldr r0, [sp, #0x10]
	add r0, r0, r1
	add r0, r4, r0
	add r0, #0x50
	add r1, r5, r1
	add r1, r4, r1
	ldrb r0, [r0, #0x0]
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_020083F4:
	ldr r1, [sp, #0xc]
	add r0, r4, #0x0
	bl _u32_div_f
	cmp r1, #0x0
	beq _02008416
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	add r2, r5, r0
	add r0, r2, r4
	add r0, #0x4f
	ldrb r1, [r0, #0x0]
	add r0, r2, r4
	add r0, #0x50
	strb r1, [r0, #0x0]
	b _0200852E
_02008416:
	ldrb r1, [r7, #0x0]
	mov r0, #0xf
	and r1, r0
	lsl r0, r1, #0x4
	orr r0, r1
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r1, r4, r1
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_02008430:
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	ldrb r0, [r7, #0x0]
	add r1, r5, r1
	add r1, r4, r1
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_02008442:
	ldr r0, [sp, #0x44]
	ldr r1, [r0, #0x54]
	lsl r0, r1, #0x16
	lsr r0, r0, #0x1f
	beq _02008472
	lsl r1, r1, #0x15
	lsr r1, r1, #0x1f
	beq _02008472
	add r1, r4, #0x0
	sub r1, #0x28
	mov r0, #0x4f
	sub r1, r0, r1
	ldr r0, [sp, #0x1c]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
	b _0200852E
_02008472:
	cmp r0, #0x0
	beq _02008496
	add r1, r4, #0x0
	sub r1, #0x28
	mov r0, #0x4f
	sub r1, r0, r1
	ldr r0, [sp, #0x18]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
	b _0200852E
_02008496:
	ldr r0, [sp, #0x44]
	ldr r0, [r0, #0x54]
	lsl r1, r0, #0x15
	lsr r1, r1, #0x1f
	beq _020084B4
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r0, [sp, #0x20]
	ldr r1, [r6, r1]
	ldrb r0, [r0, #0x0]
	add r1, r5, r1
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
	b _0200852E
_020084B4:
	lsl r0, r0, #0xf
	lsr r0, r0, #0x1c
	str r0, [sp, #0x8]
	beq _0200851E
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0x14]
	lsl r1, r1, #0x1
	bl _u32_div_f
	cmp r1, #0x0
	beq _020084E4
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r1, [r6, r0]
	ldr r0, [sp, #0x10]
	add r0, r0, r1
	add r2, r4, r0
	ldr r0, _020086E8 ; =0x00002828
	add r1, r5, r1
	ldrb r0, [r2, r0]
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
	b _0200852E
_020084E4:
	ldr r1, [sp, #0x8]
	add r0, r4, #0x0
	bl _u32_div_f
	cmp r1, #0x0
	beq _02008504
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	ldr r1, _020086EC ; =0x00002827
	add r0, r5, r0
	add r0, r0, r4
	ldrb r2, [r0, r1]
	add r1, r1, #0x1
	strb r2, [r0, r1]
	b _0200852E
_02008504:
	ldrb r1, [r7, #0x0]
	mov r0, #0xf
	and r1, r0
	lsl r0, r1, #0x4
	orr r0, r1
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
	b _0200852E
_0200851E:
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	ldrb r0, [r7, #0x0]
	add r1, r5, r1
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
_0200852E:
	ldr r0, [sp, #0x20]
	add r4, r4, #0x1
	add r0, r0, #0x1
	add r7, r7, #0x1
	str r0, [sp, #0x20]
	cmp r4, #0x50
	bge _0200853E
	b _02008356
_0200853E:
	ldr r0, [sp, #0x24]
	add r5, #0x80
	add r0, #0x50
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x14]
	add r0, r0, #0x1
	str r0, [sp, #0x14]
	cmp r0, #0x50
	bge _02008552
	b _0200832E
_02008552:
	b _020086BC
_02008554:
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x40]
	str r0, [sp, #0x3c]
_0200855C:
	ldr r0, [sp, #0x0]
	mov r1, #0x4f
	sub r2, r1, r0
	mov r0, #0x50
	add r1, r2, #0x0
	mul r1, r0
	ldr r0, [sp, #0x50]
	mov r4, #0x0
	add r0, r0, r1
	str r0, [sp, #0x34]
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x3c]
	add r7, r1, r0
	ldr r0, [sp, #0x34]
	ldr r1, [sp, #0x38]
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x40]
	str r7, [sp, #0x2c]
	add r5, r1, r0
	ldr r0, [sp, #0x0]
	sub r0, r0, #0x1
	lsl r1, r0, #0x7
	ldr r0, [sp, #0x38]
	add r0, r0, r1
	str r0, [sp, #0x28]
_0200858E:
	ldr r0, [sp, #0x44]
	ldr r1, [r0, #0x54]
	lsl r0, r1, #0x16
	lsr r0, r0, #0x1f
	beq _020085D6
	lsl r1, r1, #0x15
	lsr r1, r1, #0x1f
	beq _020085D6
	cmp r4, #0x28
	bge _020085BA
	mov r0, #0x27
	sub r1, r0, r4
	ldr r0, [sp, #0x30]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_020085BA:
	add r1, r4, #0x0
	sub r1, #0x28
	mov r0, #0x4f
	sub r1, r0, r1
	ldr r0, [sp, #0x30]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_020085D6:
	cmp r0, #0x0
	beq _02008612
	cmp r4, #0x28
	bge _020085F6
	mov r0, #0x27
	sub r1, r0, r4
	ldr r0, [sp, #0x2c]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_020085F6:
	add r1, r4, #0x0
	sub r1, #0x28
	mov r0, #0x4f
	sub r1, r0, r1
	ldr r0, [sp, #0x2c]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_02008612:
	ldr r0, [sp, #0x44]
	ldr r0, [r0, #0x54]
	lsl r1, r0, #0x15
	lsr r1, r1, #0x1f
	beq _0200862C
	ldr r0, [sp, #0x34]
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	ldrb r0, [r0, #0x0]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_0200862C:
	lsl r0, r0, #0xf
	lsr r0, r0, #0x1c
	str r0, [sp, #0x4]
	beq _02008688
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	lsl r1, r1, #0x1
	bl _u32_div_f
	cmp r1, #0x0
	beq _02008654
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	ldr r1, [sp, #0x28]
	add r1, r1, r0
	ldrb r1, [r4, r1]
	add r0, r5, r0
	strb r1, [r4, r0]
	b _02008694
_02008654:
	ldr r1, [sp, #0x4]
	add r0, r4, #0x0
	bl _u32_div_f
	cmp r1, #0x0
	beq _02008672
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	add r1, r5, r0
	add r0, r1, r4
	sub r0, r0, #0x1
	ldrb r0, [r0, #0x0]
	strb r0, [r1, r4]
	b _02008694
_02008672:
	ldrb r1, [r7, #0x0]
	mov r0, #0xf
	and r1, r0
	lsl r0, r1, #0x4
	orr r0, r1
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_02008688:
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	ldrb r0, [r7, #0x0]
	add r1, r5, r1
	strb r0, [r4, r1]
_02008694:
	ldr r0, [sp, #0x34]
	add r4, r4, #0x1
	add r0, r0, #0x1
	add r7, r7, #0x1
	str r0, [sp, #0x34]
	cmp r4, #0x50
	bge _020086A4
	b _0200858E
_020086A4:
	ldr r0, [sp, #0x40]
	add r0, #0x80
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x3c]
	add r0, #0x50
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	cmp r0, #0x50
	bge _020086BC
	b _0200855C
_020086BC:
	ldr r0, [sp, #0x4c]
	bl FreeToHeap
_020086C2:
	ldr r0, [sp, #0x44]
	mov r1, #0xa
	add r0, #0x98
	str r0, [sp, #0x44]
	ldr r0, [sp, #0x38]
	lsl r1, r1, #0xa
	add r0, r0, r1
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x54]
	add r0, r0, #0x1
	str r0, [sp, #0x54]
	cmp r0, #0x4
	bge _020086DE
	b _020082BA
_020086DE:
	ldr r1, _020086F0 ; =0x000002E1
	ldr r0, [sp, #0x48]
	strb r0, [r6, r1]
	add sp, #0x5c
	pop {r4-r7, pc}
	.balign 4
_020086E8: .word 0x00002828
_020086EC: .word 0x00002827
_020086F0: .word 0x000002E1

	thumb_func_start FUN_020086F4
FUN_020086F4: ; 0x020086F4
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0xc]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xc]
	add r4, r5, #0x0
	str r0, [sp, #0x8]
_02008706:
	ldr r1, [r4, #0x0]
	lsl r0, r1, #0x1f
	lsr r0, r0, #0x1f
	beq _020087E0
	lsl r0, r1, #0x17
	lsr r0, r0, #0x1f
	beq _020087E0
	ldr r0, _020088CC ; =0xFFFFFEFF
	mov r2, #0xa6
	and r0, r1
	str r0, [r4, #0x0]
	mov r0, #0x1
	str r0, [sp, #0xc]
	lsl r2, r2, #0x2
	ldrh r0, [r4, #0x4]
	ldrh r1, [r4, #0x8]
	ldr r2, [r5, r2]
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x18
	str r0, [sp, #0x10]
	bl NNS_G2dGetUnpackedPaletteData
	ldr r0, [sp, #0x18]
	mov r7, #0x0
	ldr r1, [r0, #0x0]
	mov r0, #0x2d
	lsl r0, r0, #0x4
	str r1, [r5, r0]
	ldr r0, [sp, #0x18]
	add r2, r7, #0x0
	ldr r1, [r0, #0xc]
	ldr r0, [sp, #0x8]
	lsl r3, r0, #0x1
_0200874A:
	mov r6, #0x2b
	lsl r6, r6, #0x4
	ldr r6, [r5, r6]
	ldrh r0, [r1, #0x0]
	add r6, r3, r6
	add r7, r7, #0x1
	strh r0, [r2, r6]
	mov r6, #0xad
	lsl r6, r6, #0x2
	ldrh r0, [r1, #0x0]
	ldr r6, [r5, r6]
	add r1, r1, #0x2
	add r6, r3, r6
	strh r0, [r2, r6]
	add r2, r2, #0x2
	cmp r7, #0x10
	blt _0200874A
	ldr r0, [sp, #0x10]
	bl FreeToHeap
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	beq _020087E0
	mov r2, #0xa6
	lsl r2, r2, #0x2
	ldr r2, [r5, r2]
	mov r0, #0x75 ; NARC_POKETOOL_POKEGRA_OTHERPOKE
	mov r1, #0xd4
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x18
	str r0, [sp, #0x4]
	bl NNS_G2dGetUnpackedPaletteData
	ldr r0, [sp, #0x18]
	mov r7, #0xad
	ldr r0, [r0, #0xc]
	mov r1, #0x0
	lsl r7, r7, #0x2
_0200879E:
	add r6, r4, #0x0
	add r6, #0x6c
	ldrh r6, [r6, #0x0]
	mov r2, #0x2b
	lsl r2, r2, #0x4
	lsl r6, r6, #0x1e
	lsr r6, r6, #0x1e
	add r6, r6, #0x3
	lsl r6, r6, #0x4
	add r6, r1, r6
	ldrh r3, [r0, #0x0]
	ldr r2, [r5, r2]
	lsl r6, r6, #0x1
	strh r3, [r2, r6]
	add r6, r4, #0x0
	add r6, #0x6c
	ldrh r6, [r6, #0x0]
	ldrh r3, [r0, #0x0]
	ldr r2, [r5, r7]
	lsl r6, r6, #0x1e
	lsr r6, r6, #0x1e
	add r6, r6, #0x3
	lsl r6, r6, #0x4
	add r6, r1, r6
	lsl r6, r6, #0x1
	add r1, r1, #0x1
	add r0, r0, #0x2
	strh r3, [r2, r6]
	cmp r1, #0x10
	blt _0200879E
	ldr r0, [sp, #0x4]
	bl FreeToHeap
_020087E0:
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _020088AE
	ldr r0, [r4, #0x54]
	lsl r0, r0, #0x13
	lsr r0, r0, #0x1f
	beq _020088AE
	add r0, r4, #0x0
	add r0, #0x4a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020088A0
	mov r0, #0x1
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r0, #0x4b
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x4a
	strb r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	mov r2, #0xad
	lsl r1, r0, #0x1
	ldr r0, [r4, #0x4c]
	add r3, r4, #0x0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r2, r2, #0x2
	str r0, [sp, #0x0]
	ldr r0, [r5, r2]
	sub r2, r2, #0x4
	add r3, #0x48
	ldr r2, [r5, r2]
	add r0, r0, r1
	add r1, r2, r1
	ldrb r3, [r3, #0x0]
	mov r2, #0x10
	bl BlendPalette
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	beq _02008862
	add r0, r0, #0x3
	lsl r1, r0, #0x5
	ldr r0, [r4, #0x4c]
	mov r2, #0xad
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r3, r4, #0x0
	lsl r2, r2, #0x2
	str r0, [sp, #0x0]
	ldr r0, [r5, r2]
	sub r2, r2, #0x4
	add r3, #0x48
	ldr r2, [r5, r2]
	add r0, r0, r1
	add r1, r2, r1
	ldrb r3, [r3, #0x0]
	mov r2, #0x10
	bl BlendPalette
_02008862:
	add r0, r4, #0x0
	add r0, #0x49
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, r1
	bne _0200887C
	ldr r1, [r4, #0x54]
	ldr r0, _020088D0 ; =0xFFFFEFFF
	and r0, r1
	str r0, [r4, #0x54]
	b _020088AE
_0200887C:
	cmp r0, r1
	bls _02008890
	add r0, r4, #0x0
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x48
	strb r1, [r0, #0x0]
	b _020088AE
_02008890:
	add r0, r4, #0x0
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	add r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x48
	strb r1, [r0, #0x0]
	b _020088AE
_020088A0:
	add r0, r4, #0x0
	add r0, #0x4a
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x4a
	strb r1, [r0, #0x0]
_020088AE:
	ldr r0, [sp, #0x8]
	add r4, #0x98
	add r0, #0x10
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x14]
	add r0, r0, #0x1
	str r0, [sp, #0x14]
	cmp r0, #0x4
	bge _020088C2
	b _02008706
_020088C2:
	ldr r1, _020088D4 ; =0x000002E2
	ldr r0, [sp, #0xc]
	strb r0, [r5, r1]
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4
_020088CC: .word 0xFFFFFEFF
_020088D0: .word 0xFFFFEFFF
_020088D4: .word 0x000002E2

	thumb_func_start FUN_020088D8
FUN_020088D8: ; 0x020088D8
	mov r1, #0xf0
	and r1, r0
	lsl r1, r1, #0x14
	lsl r0, r0, #0x1c
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr

	thumb_func_start FUN_020088EC
FUN_020088EC: ; 0x020088EC
	push {r3, lr}
	add r2, r0, #0x0
	ldrh r0, [r2, #0xa]
	cmp r0, #0x0
	beq _02008900
	add r0, r1, #0x0
	ldr r1, [r2, #0x10]
	mov r2, #0x1
	bl FUN_02008904
_02008900:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02008904
FUN_02008904: ; 0x02008904
	push {r4-r7, lr}
	sub sp, #0x1c
	add r3, r0, #0x0
	add r0, r1, #0x0
	mov lr, r0
	mov r0, #0x0
	mov r12, r0
	ldr r0, _02008A50 ; =UNK_02105AE8
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	str r0, [sp, #0x10]
_0200891A:
	ldr r0, [sp, #0x10]
	mov r1, #0x0
	ldr r6, [r0, #0x0]
	ldrb r0, [r6, #0x0]
	cmp r0, #0xff
	beq _02008992
	ldr r0, [sp, #0x0]
	mov r2, #0xf
	and r0, r2
	str r0, [sp, #0xc]
	sub r0, #0x8
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x0]
	mov r2, #0xf0
	and r0, r2
	lsr r7, r0, #0x4
	sub r7, #0x8
_0200893C:
	lsl r0, r1, #0x1
	add r2, r6, r0
	ldrb r4, [r6, r0]
	ldrb r2, [r2, #0x1]
	ldr r0, [sp, #0xc]
	add r0, r0, r4
	add r2, r7, r2
	lsl r0, r0, #0x18
	lsl r2, r2, #0x18
	lsr r0, r0, #0x18
	lsr r4, r2, #0x18
	mov r2, #0x50
	mul r2, r4
	lsr r5, r0, #0x1
	add r2, r5, r2
	mov r4, #0x1
	tst r0, r4
	ldrb r4, [r3, r2]
	beq _02008974
	mov r0, #0xf0
	and r0, r4
	cmp r0, #0x10
	blt _02008984
	cmp r0, #0x30
	bgt _02008984
	add r4, #0x50
	strb r4, [r3, r2]
	b _02008984
_02008974:
	mov r0, #0xf
	and r0, r4
	cmp r0, #0x1
	blt _02008984
	cmp r0, #0x3
	bgt _02008984
	add r0, r4, #0x5
	strb r0, [r3, r2]
_02008984:
	add r0, r1, #0x1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	lsl r0, r1, #0x1
	ldrb r0, [r6, r0]
	cmp r0, #0xff
	bne _0200893C
_02008992:
	ldr r0, [sp, #0x0]
	lsr r0, r0, #0x8
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x10]
	add r0, r0, #0x4
	str r0, [sp, #0x10]
	mov r0, r12
	add r0, r0, #0x1
	mov r12, r0
	cmp r0, #0x4
	blt _0200891A
	mov r0, lr
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _02008A4A
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r0, _02008A50 ; =UNK_02105AE8
	str r0, [sp, #0x18]
_020089BA:
	ldr r0, [sp, #0x18]
	mov r4, #0x0
	ldr r2, [r0, #0x0]
	ldrb r0, [r2, #0x0]
	cmp r0, #0xff
	beq _02008A34
	ldr r0, [sp, #0x0]
	mov r1, #0xf
	and r0, r1
	str r0, [sp, #0x14]
	add r0, #0x48
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x0]
	mov r1, #0xf0
	and r0, r1
	lsr r7, r0, #0x4
	sub r7, #0x8
_020089DC:
	lsl r0, r4, #0x1
	add r5, r2, r0
	ldrb r1, [r2, r0]
	ldrb r5, [r5, #0x1]
	ldr r0, [sp, #0x14]
	sub r1, #0xe
	add r0, r0, r1
	add r5, r7, r5
	lsl r0, r0, #0x18
	lsl r5, r5, #0x18
	lsr r1, r0, #0x18
	lsr r6, r5, #0x18
	mov r5, #0x50
	lsr r0, r1, #0x1
	mul r5, r6
	add r0, r0, r5
	mov r5, #0x1
	tst r1, r5
	ldrb r5, [r3, r0]
	beq _02008A16
	mov r1, #0xf0
	and r1, r5
	cmp r1, #0x10
	blt _02008A26
	cmp r1, #0x30
	bgt _02008A26
	add r5, #0x50
	strb r5, [r3, r0]
	b _02008A26
_02008A16:
	mov r1, #0xf
	and r1, r5
	cmp r1, #0x1
	blt _02008A26
	cmp r1, #0x3
	bgt _02008A26
	add r1, r5, #0x5
	strb r1, [r3, r0]
_02008A26:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	lsl r0, r4, #0x1
	ldrb r0, [r2, r0]
	cmp r0, #0xff
	bne _020089DC
_02008A34:
	ldr r0, [sp, #0x0]
	lsr r0, r0, #0x8
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x18]
	add r0, r0, #0x4
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	str r0, [sp, #0x8]
	cmp r0, #0x4
	blt _020089BA
_02008A4A:
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_02008A50: .word UNK_02105AE8

	thumb_func_start FUN_02008A54
FUN_02008A54: ; 0x02008A54
	ldr r2, [r0, #0x0]
	ldr r1, _02008A6C ; =0x41C64E6D
	add r3, r2, #0x0
	mul r3, r1
	ldr r1, _02008A70 ; =0x00006073
	add r1, r3, r1
	str r1, [r0, #0x0]
	lsr r0, r1, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
	nop
_02008A6C: .word 0x41C64E6D
_02008A70: .word 0x00006073

	thumb_func_start FUN_02008A74
FUN_02008A74: ; 0x02008A74
	push {r3-r7, lr}
	ldr r1, _02008AA0 ; =0x000018FE
	mov r6, #0x0
	ldrh r2, [r0, r1]
	lsr r4, r1, #0x1
	add r5, r0, r1
	str r2, [sp, #0x0]
	add r7, sp, #0x0
	mvn r6, r6
_02008A86:
	ldrh r1, [r5, #0x0]
	ldr r0, [sp, #0x0]
	eor r0, r1
	strh r0, [r5, #0x0]
	add r0, r7, #0x0
	bl FUN_02008A54
	sub r4, r4, #0x1
	sub r5, r5, #0x2
	cmp r4, r6
	bgt _02008A86
	pop {r3-r7, pc}
	nop
_02008AA0: .word 0x000018FE
