	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_0202A924
FUN_0202A924: ; 0x0202A924
	mov r0, #0x45
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_0202A92C
FUN_0202A92C: ; 0x0202A92C
	push {r4, lr}
	mov r2, #0x45
	add r4, r0, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	bl memset
	bl MTRandom
	str r0, [r4, #0x0]
	bl MTRandom
	str r0, [r4, #0x4]
	mov r1, #0x0
	add r3, r4, #0x0
	ldr r0, _0202A980 ; =0x0000FFFF
	str r1, [r4, #0x8]
	strh r0, [r4, #0xc]
	strh r0, [r4, #0xe]
	mov r0, #0x15
	add r3, #0x10
	strb r0, [r4, #0x10]
	add r2, r1, #0x0
_0202A95A:
	str r2, [r3, #0x4]
	strb r2, [r3, #0x8]
	strb r2, [r3, #0x9]
	strb r2, [r3, #0xa]
	strb r2, [r3, #0xb]
	add r1, r1, #0x1
	add r3, #0x8
	cmp r1, #0x15
	blt _0202A95A
	ldr r0, _0202A984 ; =0x0000010F
	strb r2, [r4, r0]
	add r1, r0, #0x1
	strb r2, [r4, r1]
	add r1, r0, #0x2
	strb r2, [r4, r1]
	add r0, r0, #0x3
	strb r2, [r4, r0]
	pop {r4, pc}
	nop
_0202A980: .word 0x0000FFFF
_0202A984: .word 0x0000010F

	thumb_func_start FUN_0202A988
FUN_0202A988: ; 0x0202A988
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start FUN_0202A990
FUN_0202A990: ; 0x0202A990
	push {r3, lr}
	cmp r1, #0x1
	beq _0202A99C
	cmp r1, #0x2
	beq _0202A9A0
	b _0202A9A4
_0202A99C:
	ldr r0, [r0, #0x0]
	pop {r3, pc}
_0202A9A0:
	ldr r0, [r0, #0x4]
	pop {r3, pc}
_0202A9A4:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0202A9AC
FUN_0202A9AC: ; 0x0202A9AC
	add r0, #0xbc
	bx lr

	thumb_func_start Save_Roamers_Get
Save_Roamers_Get: ; 0x0202A9B0
	ldr r3, _0202A9B8 ; =SaveArray_Get
	mov r1, #0x19
	bx r3
	nop
_0202A9B8: .word SaveArray_Get

	thumb_func_start FUN_0202A9BC
FUN_0202A9BC: ; 0x0202A9BC
	add r0, #0x10
	bx lr

	thumb_func_start FUN_0202A9C0
FUN_0202A9C0: ; 0x0202A9C0
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202A9C4
FUN_0202A9C4: ; 0x0202A9C4
	strb r0, [r1, #0x0]
	bx lr

	thumb_func_start FUN_0202A9C8
FUN_0202A9C8: ; 0x0202A9C8
	add r1, r1, #0x4
	lsl r0, r0, #0x3
	add r0, r1, r0
	bx lr

	thumb_func_start FUN_0202A9D0
FUN_0202A9D0: ; 0x0202A9D0
	push {r3-r7, lr}
	add r5, r1, #0x0
	bl Save_Roamers_Get
	add r6, r0, #0x0
	mov r4, #0x0
	add r6, #0x10
	add r7, r4, #0x0
_0202A9E0:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	add r1, r6, #0x0
	bl FUN_0202A9C8
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202A9F8
	sub r1, r1, r5
	str r1, [r0, #0x0]
	bpl _0202A9F8
	str r7, [r0, #0x0]
_0202A9F8:
	add r4, r4, #0x1
	cmp r4, #0x15
	blt _0202A9E0
	pop {r3-r7, pc}

	thumb_func_start FUN_0202AA00
FUN_0202AA00: ; 0x0202AA00
	push {r3, lr}
	bl Save_Roamers_Get
	ldr r1, _0202AA10 ; =0x0000010F
	mov r2, #0x1
	strb r2, [r0, r1]
	pop {r3, pc}
	nop
_0202AA10: .word 0x0000010F

	thumb_func_start FUN_0202AA14
FUN_0202AA14: ; 0x0202AA14
	ldr r1, _0202AA1C ; =0x0000010F
	ldrb r0, [r0, r1]
	bx lr
	nop
_0202AA1C: .word 0x0000010F

	thumb_func_start FUN_0202AA20
FUN_0202AA20: ; 0x0202AA20
	add r2, r0, #0x0
	add r2, #0xc8
	ldr r3, [r2, #0x0]
	cmp r3, r1
	beq _0202AA34
	add r2, r0, #0x0
	add r2, #0xcc
	str r3, [r2, #0x0]
	add r0, #0xc8
	str r1, [r0, #0x0]
_0202AA34:
	bx lr
	.balign 4

	thumb_func_start FUN_0202AA38
FUN_0202AA38: ; 0x0202AA38
	add r0, #0xcc
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202AA40
FUN_0202AA40: ; 0x0202AA40
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	blo _0202AA4E
	bl GF_AssertFail
_0202AA4E:
	mov r0, #0x43
	add r1, r5, r4
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AA58
FUN_0202AA58: ; 0x0202AA58
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x3
	blo _0202AA68
	bl GF_AssertFail
_0202AA68:
	mov r0, #0x43
	add r1, r5, r4
	lsl r0, r0, #0x2
	strb r6, [r1, r0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202AA74
FUN_0202AA74: ; 0x0202AA74
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	blo _0202AA82
	bl GF_AssertFail
_0202AA82:
	mov r0, #0x14
	mul r0, r4
	add r0, r5, r0
	add r0, #0xe2
	ldrb r0, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202AA90
FUN_0202AA90: ; 0x0202AA90
	ldr r2, [r0, #0x0]
	mov r1, #0x14
	mov r0, #0x0
_0202AA96:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _0202AA96
	bx lr

	thumb_func_start FUN_0202AAA0
FUN_0202AAA0: ; 0x0202AAA0
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	blo _0202AAAE
	bl GF_AssertFail
_0202AAAE:
	mov r0, #0x14
	add r5, #0xd0
	mul r0, r4
	add r0, r5, r0
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AAB8
FUN_0202AAB8: ; 0x0202AAB8
	cmp r1, #0x8
	bhi _0202AAF8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202AAC8: ; jump table (using 16-bit offset)
	.short _0202AAF8 - _0202AAC8 - 2; case 0
	.short _0202AADA - _0202AAC8 - 2; case 1
	.short _0202AADE - _0202AAC8 - 2; case 2
	.short _0202AAE2 - _0202AAC8 - 2; case 3
	.short _0202AAE6 - _0202AAC8 - 2; case 4
	.short _0202AAEA - _0202AAC8 - 2; case 5
	.short _0202AAEE - _0202AAC8 - 2; case 6
	.short _0202AAF2 - _0202AAC8 - 2; case 7
	.short _0202AAF6 - _0202AAC8 - 2; case 8
_0202AADA:
	ldr r0, [r0, #0x0]
	bx lr
_0202AADE:
	ldr r0, [r0, #0x4]
	bx lr
_0202AAE2:
	ldr r0, [r0, #0x8]
	bx lr
_0202AAE6:
	ldrh r0, [r0, #0xc]
	bx lr
_0202AAEA:
	ldrh r0, [r0, #0xe]
	bx lr
_0202AAEE:
	ldrb r0, [r0, #0x10]
	bx lr
_0202AAF2:
	ldrb r0, [r0, #0x11]
	bx lr
_0202AAF6:
	ldrb r0, [r0, #0x12]
_0202AAF8:
	bx lr
	.balign 4

	thumb_func_start FUN_0202AAFC
FUN_0202AAFC: ; 0x0202AAFC
	cmp r1, #0x8
	bhi _0202AB3C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202AB0C: ; jump table (using 16-bit offset)
	.short _0202AB3C - _0202AB0C - 2; case 0
	.short _0202AB1E - _0202AB0C - 2; case 1
	.short _0202AB22 - _0202AB0C - 2; case 2
	.short _0202AB26 - _0202AB0C - 2; case 3
	.short _0202AB2A - _0202AB0C - 2; case 4
	.short _0202AB2E - _0202AB0C - 2; case 5
	.short _0202AB32 - _0202AB0C - 2; case 6
	.short _0202AB36 - _0202AB0C - 2; case 7
	.short _0202AB3A - _0202AB0C - 2; case 8
_0202AB1E:
	str r2, [r0, #0x0]
	bx lr
_0202AB22:
	str r2, [r0, #0x4]
	bx lr
_0202AB26:
	str r2, [r0, #0x8]
	bx lr
_0202AB2A:
	strh r2, [r0, #0xc]
	bx lr
_0202AB2E:
	strh r2, [r0, #0xe]
	bx lr
_0202AB32:
	strb r2, [r0, #0x10]
	bx lr
_0202AB36:
	strb r2, [r0, #0x11]
	bx lr
_0202AB3A:
	strb r2, [r0, #0x12]
_0202AB3C:
	bx lr
	.balign 4

	thumb_func_start FUN_0202AB40
FUN_0202AB40: ; 0x0202AB40
	ldr r1, _0202AB48 ; =0x00000111
	add r0, r0, r1
	bx lr
	nop
_0202AB48: .word 0x00000111

	thumb_func_start FUN_0202AB4C
FUN_0202AB4C: ; 0x0202AB4C
	mov r1, #0x11
	lsl r1, r1, #0x4
	add r0, r0, r1
	bx lr

	thumb_func_start FUN_0202AB54
FUN_0202AB54: ; 0x0202AB54
	mov r1, #0x11
	lsl r1, r1, #0x4
	ldrb r0, [r0, r1]
	cmp r0, #0x0
	bne _0202AB62
	mov r0, #0x1
	bx lr
_0202AB62:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0202AB68
FUN_0202AB68: ; 0x0202AB68
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x2
	bls _0202AB76
	bl GF_AssertFail
_0202AB76:
	ldr r0, _0202AB7C ; =0x00000112
	strb r4, [r5, r0]
	pop {r3-r5, pc}
	.balign 4
_0202AB7C: .word 0x00000112

	thumb_func_start FUN_0202AB80
FUN_0202AB80: ; 0x0202AB80
	ldr r1, _0202AB88 ; =0x00000112
	ldrb r0, [r0, r1]
	bx lr
	nop
_0202AB88: .word 0x00000112

	thumb_func_start FUN_0202AB8C
FUN_0202AB8C: ; 0x0202AB8C
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl Save_Roamers_Get
	ldrh r1, [r0, #0xc]
	strh r1, [r5, #0x0]
	ldrh r0, [r0, #0xe]
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0202ABA0
FUN_0202ABA0: ; 0x0202ABA0
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl Save_Roamers_Get
	add r4, r0, #0x0
	cmp r5, #0x10
	blo _0202ABB2
	bl GF_AssertFail
_0202ABB2:
	ldrh r0, [r4, #0xc]
	strh r0, [r4, #0xe]
	strh r5, [r4, #0xc]
	pop {r3-r5, pc}
	.balign 4
