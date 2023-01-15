	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F71A8
UNK_020F71A8: ; 0x020F71A8
	.word FUN_0205C888, FUN_0205C8B4, FUN_0205C8E0, FUN_0205C90C

	.global UNK_020F71B8
UNK_020F71B8: ; 0x020F71B8
	.word FUN_0205CB14, FUN_0205CB30, FUN_0205CB5C, FUN_0205CBA4
	.word FUN_0205CBDC, FUN_0205CBF8, FUN_0205CC10, FUN_0205CC2C
	.word FUN_0205CC40, FUN_0205CC58, FUN_0205CC70, FUN_0205CC88
	.word FUN_0205CCB0, FUN_0205CCD0, FUN_0205CCEC, FUN_0205CD68
	.word FUN_0205CD90, FUN_0205CDAC

	.text

	thumb_func_start FUN_0205C598
FUN_0205C598: ; 0x0205C598
	push {r3-r7, lr}
	sub sp, #0x58
	add r5, r0, #0x0
	ldr r7, [r5, #0x38]
	add r4, r1, #0x0
	ldr r6, [r5, #0x34]
	add r1, sp, #0x40
	str r1, [sp, #0x0]
	add r1, r6, #0x0
	add r2, r7, #0x0
	mov r3, #0x0
	bl FUN_0205C6BC
	cmp r0, #0x0
	bne _0205C5BC
	add sp, #0x58
	mov r0, #0x0
	pop {r3-r7, pc}
_0205C5BC:
	ldr r0, [sp, #0x50]
	cmp r0, #0x0
	bne _0205C642
	ldr r1, _0205C6B8 ; =0x00000F0A
	ldr r2, [sp, #0x54]
	add r0, r5, #0x0
	bl FUN_02038C78
	cmp r4, #0x0
	beq _0205C5E4
	add r0, sp, #0x28
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x54]
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_0205C6BC
	cmp r0, #0x0
	bne _0205C604
_0205C5E4:
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4c]
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x54]
	ldr r2, [sp, #0x40]
	ldr r3, [sp, #0x44]
	add r0, r5, #0x0
	bl FUN_02038CA8
	add sp, #0x58
	mov r0, #0x1
	pop {r3-r7, pc}
_0205C604:
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4c]
	str r0, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x54]
	ldr r2, [sp, #0x40]
	ldr r3, [sp, #0x44]
	add r0, r5, #0x0
	bl FUN_02038CA8
	ldr r0, [sp, #0x30]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x34]
	str r0, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x1
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x3c]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	add r0, r5, #0x0
	bl FUN_02038CA8
	add sp, #0x58
	mov r0, #0x1
	pop {r3-r7, pc}
_0205C642:
	cmp r0, #0x1
	bne _0205C6AE
	cmp r4, #0x0
	bne _0205C650
	add sp, #0x58
	mov r0, #0x0
	pop {r3-r7, pc}
_0205C650:
	ldr r2, [sp, #0x54]
	ldr r3, [sp, #0x4c]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0205C9F0
	add r1, r0, #0x0
	ldr r2, [sp, #0x40]
	ldr r3, [sp, #0x44]
	add r0, sp, #0x10
	bl FUN_0205C73C
	ldr r1, _0205C6B8 ; =0x00000F0A
	ldr r2, [sp, #0x54]
	add r0, r5, #0x0
	bl FUN_02038C78
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4c]
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x54]
	ldr r2, [sp, #0x40]
	ldr r3, [sp, #0x44]
	add r0, r5, #0x0
	bl FUN_02038CA8
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x1c]
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	add r0, r5, #0x0
	bl FUN_02038CA8
	add sp, #0x58
	mov r0, #0x1
	pop {r3-r7, pc}
_0205C6AE:
	bl GF_AssertFail
	mov r0, #0x0
	add sp, #0x58
	pop {r3-r7, pc}
	.balign 4
_0205C6B8: .word 0x00000F0A

	thumb_func_start FUN_0205C6BC
FUN_0205C6BC: ; 0x0205C6BC
	push {r3-r7, lr}
	sub sp, #0x10
	add r6, r0, #0x0
	mov r0, #0x0
	add r5, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	str r0, [sp, #0xc]
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, sp, #0x4
	add r2, sp, #0xc
	mov r3, #0x1
	bl FUN_020580F4
	cmp r0, #0x0
	beq _0205C734
_0205C6DE:
	cmp r4, #0x0
	beq _0205C6E8
	ldr r0, [sp, #0x4]
	cmp r4, r0
	beq _0205C724
_0205C6E8:
	ldr r0, [sp, #0x4]
	add r1, r7, #0x0
	add r2, sp, #0x8
	bl FUN_0205C794
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x0]
	cmp r0, r1
	beq _0205C724
	ldr r0, [sp, #0x4]
	bl FUN_0205C9D8
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl TrainerFlagCheck
	cmp r0, #0x0
	bne _0205C724
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0x8]
	bl FUN_0205C73C
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_0205C724:
	add r0, r5, #0x0
	add r1, sp, #0x4
	add r2, sp, #0xc
	mov r3, #0x1
	bl FUN_020580F4
	cmp r0, #0x0
	bne _0205C6DE
_0205C734:
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0205C73C
FUN_0205C73C: ; 0x0205C73C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [r5, #0x0]
	str r3, [r5, #0x4]
	add r0, r4, #0x0
	bl FUN_02058498
	str r0, [r5, #0x8]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_020395F4
	str r0, [r5, #0xc]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl Field_TrainerIsDoubleBattle
	str r0, [r5, #0x10]
	str r4, [r5, #0x14]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205C768
FUN_0205C768: ; 0x0205C768
	push {r3, lr}
	bl FUN_02058488
	cmp r0, #0x8
	bhi _0205C792
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0205C77E: ; jump table (using 16-bit offset)
	.short _0205C792 - _0205C77E - 2; case 0
	.short _0205C792 - _0205C77E - 2; case 1
	.short _0205C792 - _0205C77E - 2; case 2
	.short _0205C792 - _0205C77E - 2; case 3
	.short _0205C790 - _0205C77E - 2; case 4
	.short _0205C790 - _0205C77E - 2; case 5
	.short _0205C790 - _0205C77E - 2; case 6
	.short _0205C790 - _0205C77E - 2; case 7
	.short _0205C790 - _0205C77E - 2; case 8
_0205C790:
	mov r0, #0x1
_0205C792:
	pop {r3, pc}

	thumb_func_start FUN_0205C794
FUN_0205C794: ; 0x0205C794
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x8]
	bl FUN_0205C768
	cmp r0, #0x1
	bne _0205C802
	add r0, r4, #0x0
	bl GetPlayerXCoord
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl GetPlayerYCoord
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020584C4
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	add r2, r0, #0x0
	str r6, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r3, r7, #0x0
	bl FUN_0205C86C
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r6, r0
	beq _0205C7FA
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0205C938
	cmp r0, #0x0
	bne _0205C7FA
	ldr r0, [sp, #0x8]
	add sp, #0x14
	str r4, [r0, #0x0]
	add r0, r6, #0x0
	pop {r4-r7, pc}
_0205C7FA:
	mov r0, #0x0
	add sp, #0x14
	mvn r0, r0
	pop {r4-r7, pc}
_0205C802:
	cmp r0, #0x2
	bne _0205C864
	add r0, r4, #0x0
	bl GetPlayerXCoord
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	bl GetPlayerYCoord
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	str r0, [sp, #0xc]
	mov r4, #0x0
_0205C822:
	str r7, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205C86C
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r6, r0
	beq _0205C856
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0205C938
	cmp r0, #0x0
	bne _0205C856
	ldr r0, [sp, #0x8]
	add sp, #0x14
	str r4, [r0, #0x0]
	add r0, r6, #0x0
	pop {r4-r7, pc}
_0205C856:
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _0205C822
	mov r0, #0x0
	add sp, #0x14
	mvn r0, r0
	pop {r4-r7, pc}
_0205C864:
	mov r0, #0x0
	mvn r0, r0
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_0205C86C
FUN_0205C86C: ; 0x0205C86C
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, [sp, #0x14]
	lsl r5, r4, #0x2
	ldr r4, _0205C884 ; =UNK_020F71A8
	str r1, [sp, #0x0]
	add r1, r2, #0x0
	add r2, r3, #0x0
	ldr r3, [sp, #0x10]
	ldr r4, [r4, r5]
	blx r4
	pop {r3-r5, pc}
	.balign 4
_0205C884: .word UNK_020F71A8

	thumb_func_start FUN_0205C888
FUN_0205C888: ; 0x0205C888
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02058B2C
	cmp r0, r6
	bne _0205C8AE
	add r0, r7, #0x0
	bl FUN_02058B4C
	cmp r4, r0
	bge _0205C8AE
	sub r1, r0, r5
	cmp r4, r1
	blt _0205C8AE
	sub r0, r0, r4
	pop {r3-r7, pc}
_0205C8AE:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}

	thumb_func_start FUN_0205C8B4
FUN_0205C8B4: ; 0x0205C8B4
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02058B2C
	cmp r0, r6
	bne _0205C8DA
	add r0, r7, #0x0
	bl FUN_02058B4C
	cmp r4, r0
	ble _0205C8DA
	add r1, r0, r5
	cmp r4, r1
	bgt _0205C8DA
	sub r0, r4, r0
	pop {r3-r7, pc}
_0205C8DA:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}

	thumb_func_start FUN_0205C8E0
FUN_0205C8E0: ; 0x0205C8E0
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02058B4C
	cmp r0, r6
	bne _0205C906
	add r0, r7, #0x0
	bl FUN_02058B2C
	cmp r4, r0
	bge _0205C906
	sub r1, r0, r5
	cmp r4, r1
	blt _0205C906
	sub r0, r0, r4
	pop {r3-r7, pc}
_0205C906:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}

	thumb_func_start FUN_0205C90C
FUN_0205C90C: ; 0x0205C90C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02058B4C
	cmp r0, r6
	bne _0205C932
	add r0, r7, #0x0
	bl FUN_02058B2C
	cmp r4, r0
	ble _0205C932
	add r1, r0, r5
	cmp r4, r1
	bgt _0205C932
	sub r0, r4, r0
	pop {r3-r7, pc}
_0205C932:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}

	thumb_func_start FUN_0205C938
FUN_0205C938: ; 0x0205C938
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r1, #0x0
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	cmp r2, #0x0
	bne _0205C94C
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0205C94C:
	bl FUN_02058B2C
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	bl FUN_02058B4C
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	bl FUN_02058B3C
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl FUN_02059BF4
	add r6, r4, r0
	add r0, r5, #0x0
	bl FUN_02059C00
	add r4, r7, r0
	ldr r0, [sp, #0x8]
	mov r7, #0x0
	sub r0, r0, #0x1
	str r0, [sp, #0x10]
	cmp r0, #0x0
	ble _0205C9B4
	mov r0, #0x1
	str r0, [sp, #0x14]
_0205C982:
	ldr r0, [sp, #0x4]
	ldr r2, [sp, #0xc]
	add r1, r6, #0x0
	add r3, r4, #0x0
	str r5, [sp, #0x0]
	bl FUN_020598F0
	ldr r1, [sp, #0x14]
	bic r0, r1
	beq _0205C99C
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0205C99C:
	add r0, r5, #0x0
	bl FUN_02059BF4
	add r6, r6, r0
	add r0, r5, #0x0
	bl FUN_02059C00
	add r4, r4, r0
	ldr r0, [sp, #0x10]
	add r7, r7, #0x1
	cmp r7, r0
	blt _0205C982
_0205C9B4:
	ldr r0, [sp, #0x4]
	ldr r2, [sp, #0xc]
	add r1, r6, #0x0
	add r3, r4, #0x0
	str r5, [sp, #0x0]
	bl FUN_020598F0
	mov r1, #0x1
	bic r0, r1
	cmp r0, #0x4
	bne _0205C9D0
	add sp, #0x18
	mov r0, #0x0
	pop {r3-r7, pc}
_0205C9D0:
	mov r0, #0x1
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0205C9D8
FUN_0205C9D8: ; 0x0205C9D8
	push {r3, lr}
	bl FUN_02058498
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_020395F4
	pop {r3, pc}

	thumb_func_start FUN_0205C9E8
FUN_0205C9E8: ; 0x0205C9E8
	ldr r3, _0205C9EC ; =FUN_0205C9D8
	bx r3
	.balign 4
_0205C9EC: .word FUN_0205C9D8

	thumb_func_start FUN_0205C9F0
FUN_0205C9F0: ; 0x0205C9F0
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	mov r0, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, sp, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	bl FUN_020580F4
	cmp r0, #0x0
	beq _0205CA40
	add r7, sp, #0x0
_0205CA10:
	ldr r0, [sp, #0x0]
	cmp r0, r4
	beq _0205CA30
	bl FUN_0205C768
	sub r0, r0, #0x1
	cmp r0, #0x1
	bhi _0205CA30
	ldr r0, [sp, #0x0]
	bl FUN_0205C9D8
	cmp r6, r0
	bne _0205CA30
	ldr r0, [sp, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}
_0205CA30:
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	bl FUN_020580F4
	cmp r0, #0x0
	bne _0205CA10
_0205CA40:
	bl GF_AssertFail
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0205CA4C
FUN_0205CA4C: ; 0x0205CA4C
	push {r3-r4, lr}
	sub sp, #0xc
	ldr r4, [sp, #0x18]
	str r4, [sp, #0x0]
	ldr r4, [sp, #0x1c]
	str r4, [sp, #0x4]
	ldr r4, [sp, #0x20]
	str r4, [sp, #0x8]
	bl FUN_0205CA80
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0205CA64
FUN_0205CA64: ; 0x0205CA64
	push {r4, lr}
	add r4, r0, #0x0
	bne _0205CA6E
	bl GF_AssertFail
_0205CA6E:
	add r0, r4, #0x0
	bl FUN_0205CAD4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205CA78
FUN_0205CA78: ; 0x0205CA78
	ldr r3, _0205CA7C ; =FUN_0205CAE0
	bx r3
	.balign 4
_0205CA7C: .word FUN_0205CAE0

	thumb_func_start FUN_0205CA80
FUN_0205CA80: ; 0x0205CA80
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0x4
	mov r1, #0x2c
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	bne _0205CA9A
	bl GF_AssertFail
_0205CA9A:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x2c
	bl memset
	ldr r0, [sp, #0x0]
	str r7, [r4, #0x8]
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x18]
	add r1, r4, #0x0
	str r0, [r4, #0x10]
	ldr r0, [sp, #0x1c]
	mov r2, #0xff
	str r0, [r4, #0x14]
	ldr r0, [sp, #0x20]
	str r0, [r4, #0x18]
	str r5, [r4, #0x24]
	ldr r0, _0205CAD0 ; =FUN_0205CAF8
	str r6, [r4, #0x28]
	bl FUN_0200CA44
	add r4, r0, #0x0
	bne _0205CACC
	bl GF_AssertFail
_0205CACC:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_0205CAD0: .word FUN_0205CAF8

	thumb_func_start FUN_0205CAD4
FUN_0205CAD4: ; 0x0205CAD4
	push {r3, lr}
	bl FUN_0201B6C8
	ldr r0, [r0, #0x4]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205CAE0
FUN_0205CAE0: ; 0x0205CAE0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201B6C8
	add r1, r0, #0x0
	mov r0, #0x4
	bl FreeToHeapExplicit
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start FUN_0205CAF8
FUN_0205CAF8: ; 0x0205CAF8
	push {r3-r5, lr}
	ldr r4, _0205CB10 ; =UNK_020F71B8
	add r5, r1, #0x0
_0205CAFE:
	ldr r1, [r5, #0x0]
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	blx r1
	cmp r0, #0x1
	beq _0205CAFE
	pop {r3-r5, pc}
	nop
_0205CB10: .word UNK_020F71B8

	thumb_func_start FUN_0205CB14
FUN_0205CB14: ; 0x0205CB14
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r4, [r5, #0x24]
	add r0, r4, #0x0
	bl FUN_02058854
	cmp r0, #0x1
	bne _0205CB2A
	add r0, r4, #0x0
	bl FUN_02058914
_0205CB2A:
	mov r0, #0x1
	str r0, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0205CB30
FUN_0205CB30: ; 0x0205CB30
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r5, [r4, #0x24]
	add r0, r5, #0x0
	bl FUN_02058854
	cmp r0, #0x1
	bne _0205CB44
	mov r0, #0x0
	pop {r3-r5, pc}
_0205CB44:
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x8]
	bl MOD05_021F1EC0
	add r0, r5, #0x0
	mov r1, #0x40
	bl FUN_02058410
	mov r0, #0x2
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0205CB5C
FUN_0205CB5C: ; 0x0205CB5C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x28]
	bl FUN_020553A0
	bl FUN_0205AE28
	cmp r0, #0x0
	bne _0205CB72
	mov r0, #0x0
	pop {r4, pc}
_0205CB72:
	ldr r0, [r4, #0x24]
	bl FUN_02058480
	sub r0, #0x33
	cmp r0, #0x3
	bhi _0205CB9A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205CB8A: ; jump table (using 16-bit offset)
	.short _0205CB92 - _0205CB8A - 2; case 0
	.short _0205CB92 - _0205CB8A - 2; case 1
	.short _0205CB92 - _0205CB8A - 2; case 2
	.short _0205CB92 - _0205CB8A - 2; case 3
_0205CB92:
	mov r0, #0x7
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
_0205CB9A:
	mov r0, #0x3
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205CBA4
FUN_0205CBA4: ; 0x0205CBA4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x24]
	bl FUN_0205AD98
	cmp r0, #0x0
	bne _0205CBB6
	mov r0, #0x0
	pop {r4, pc}
_0205CBB6:
	mov r0, #0x0
	ldr r1, [r4, #0x8]
	mvn r0, r0
	cmp r1, r0
	bne _0205CBC4
	bl GF_AssertFail
_0205CBC4:
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	bl FUN_0205AFDC
	add r1, r0, #0x0
	ldr r0, [r4, #0x24]
	bl FUN_0205ADDC
	mov r0, #0x4
	str r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0205CBDC
FUN_0205CBDC: ; 0x0205CBDC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x24]
	bl FUN_0205AE28
	cmp r0, #0x0
	bne _0205CBEE
	mov r0, #0x0
	pop {r4, pc}
_0205CBEE:
	mov r0, #0x5
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205CBF8
FUN_0205CBF8: ; 0x0205CBF8
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	ldr r0, [r4, #0x24]
	add r2, r1, #0x0
	bl MOD05_021E7AC0
	str r0, [r4, #0x20]
	mov r0, #0x6
	str r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0205CC10
FUN_0205CC10: ; 0x0205CC10
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x20]
	bl MOD05_021E799C
	cmp r0, #0x1
	bne _0205CC28
	ldr r0, [r4, #0x20]
	bl FUN_02064520
	mov r0, #0x9
	str r0, [r4, #0x0]
_0205CC28:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0205CC2C
FUN_0205CC2C: ; 0x0205CC2C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x24]
	mov r1, #0x65
	bl FUN_0205ADDC
	mov r0, #0x8
	str r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0205CC40
FUN_0205CC40: ; 0x0205CC40
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x24]
	bl FUN_0205AE28
	cmp r0, #0x1
	bne _0205CC52
	mov r0, #0x9
	str r0, [r4, #0x0]
_0205CC52:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205CC58
FUN_0205CC58: ; 0x0205CC58
	ldr r1, [r0, #0x1c]
	add r1, r1, #0x1
	str r1, [r0, #0x1c]
	cmp r1, #0x1e
	blt _0205CC6A
	mov r1, #0x0
	str r1, [r0, #0x1c]
	mov r1, #0xa
	str r1, [r0, #0x0]
_0205CC6A:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0205CC70
FUN_0205CC70: ; 0x0205CC70
	ldr r1, [r0, #0xc]
	cmp r1, #0x1
	bgt _0205CC7E
	mov r1, #0xd
	str r1, [r0, #0x0]
	mov r0, #0x1
	bx lr
_0205CC7E:
	mov r1, #0xb
	str r1, [r0, #0x0]
	mov r0, #0x1
	bx lr
	.balign 4

	thumb_func_start FUN_0205CC88
FUN_0205CC88: ; 0x0205CC88
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x24]
	bl FUN_0205AD98
	cmp r0, #0x1
	bne _0205CCAA
	ldr r0, [r4, #0x8]
	mov r1, #0xc
	bl FUN_0205AFDC
	add r1, r0, #0x0
	ldr r0, [r4, #0x24]
	bl FUN_0205ADDC
	mov r0, #0xc
	str r0, [r4, #0x0]
_0205CCAA:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205CCB0
FUN_0205CCB0: ; 0x0205CCB0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x24]
	bl FUN_0205AE28
	cmp r0, #0x0
	bne _0205CCC2
	mov r0, #0x0
	pop {r4, pc}
_0205CCC2:
	ldr r0, [r4, #0xc]
	sub r0, r0, #0x1
	str r0, [r4, #0xc]
	mov r0, #0xa
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0205CCD0
FUN_0205CCD0: ; 0x0205CCD0
	ldr r1, [r0, #0x1c]
	add r1, r1, #0x1
	str r1, [r0, #0x1c]
	cmp r1, #0x8
	bge _0205CCDE
	mov r0, #0x0
	bx lr
_0205CCDE:
	mov r1, #0x0
	str r1, [r0, #0x1c]
	mov r1, #0xe
	str r1, [r0, #0x0]
	mov r0, #0x1
	bx lr
	.balign 4

	thumb_func_start FUN_0205CCEC
FUN_0205CCEC: ; 0x0205CCEC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x28]
	bl FUN_020553A0
	add r4, r0, #0x0
	bl FUN_02058B2C
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B4C
	add r7, r0, #0x0
	ldr r0, [r5, #0x24]
	bl FUN_02058B2C
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x24]
	bl FUN_02058B4C
	add r3, r0, #0x0
	ldr r2, [sp, #0x0]
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_02059E80
	add r6, r0, #0x0
	ldr r0, [r5, #0x28]
	bl PlayerAvatar_GetFacingDirection
	cmp r6, r0
	beq _0205CD60
	ldr r0, [r5, #0x18]
	cmp r0, #0x0
	beq _0205CD38
	ldr r0, [r5, #0x14]
	cmp r0, #0x2
	bne _0205CD60
_0205CD38:
	add r0, r4, #0x0
	bl FUN_0205AD98
	cmp r0, #0x1
	bne _0205CD64
	add r0, r4, #0x0
	mov r1, #0x80
	bl FUN_02058418
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_0205AFDC
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205ADDC
	mov r0, #0xf
	str r0, [r5, #0x0]
	b _0205CD64
_0205CD60:
	mov r0, #0x10
	str r0, [r5, #0x0]
_0205CD64:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0205CD68
FUN_0205CD68: ; 0x0205CD68
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x28]
	bl FUN_020553A0
	add r5, r0, #0x0
	bl FUN_0205AE28
	cmp r0, #0x0
	bne _0205CD80
	mov r0, #0x0
	pop {r3-r5, pc}
_0205CD80:
	add r0, r5, #0x0
	bl FUN_0205AE50
	mov r0, #0x10
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205CD90
FUN_0205CD90: ; 0x0205CD90
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x24]
	bl FUN_0205AE50
	ldr r0, [r4, #0x24]
	mov r1, #0x0
	bl FUN_02058E90
	mov r0, #0x11
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205CDAC
FUN_0205CDAC: ; 0x0205CDAC
	mov r1, #0x1
	str r1, [r0, #0x4]
	mov r0, #0x0
	bx lr
