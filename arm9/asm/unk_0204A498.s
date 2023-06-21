	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F4708
UNK_020F4708: ; 0x020F4708
	.word sub_0204A4A4, sub_0204A5F4

	.global UNK_020F4710
UNK_020F4710: ; 0x020F4710
	.word sub_0204A5C0, sub_0204A640

	.text

	thumb_func_start sub_0204A498
sub_0204A498: ; 0x0204A498
	cmp r0, r1
	blt _0204A4A0
	sub r0, r0, r1
	bx lr
_0204A4A0:
	sub r0, r1, r0
	bx lr

	thumb_func_start sub_0204A4A4
sub_0204A4A4: ; 0x0204A4A4
	push {r3-r7, lr}
	sub sp, #0x38
	add r4, r2, #0x0
	add r6, r3, #0x0
	add r5, r0, #0x0
	mov r0, #0x0
	str r4, [sp, #0x2c]
	str r6, [sp, #0x34]
	str r0, [sp, #0x10]
	str r0, [sp, #0x30]
	ldr r0, [r5, #0x24]
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x28]
	bl MapMatrix_GetWidth
	str r0, [sp, #0x24]
	lsl r0, r0, #0x5
	str r0, [sp, #0xc]
	asr r0, r4, #0xf
	lsr r0, r0, #0x10
	add r0, r4, r0
	asr r7, r0, #0x10
	asr r0, r6, #0xf
	lsr r0, r0, #0x10
	add r0, r6, r0
	asr r0, r0, #0x10
	str r0, [sp, #0x1c]
	add r2, r5, #0x0
	add r2, #0x9c
	ldr r1, [sp, #0x1c]
	ldr r2, [r2, #0x0]
	add r0, r7, #0x0
	add r3, sp, #0x28
	bl MOD05_021F4520
	str r0, [sp, #0x20]
	lsr r0, r7, #0x5
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x1c]
	lsr r0, r0, #0x5
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	lsl r0, r0, #0x5
	add r0, #0x10
	lsl r0, r0, #0x10
	sub r0, r4, r0
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x14]
	lsl r0, r0, #0x5
	add r0, #0x10
	lsl r0, r0, #0x10
	sub r0, r6, r0
	str r0, [sp, #0x34]
	ldr r0, [sp, #0xc]
	mul r0, r1
	ldr r1, [sp, #0xc]
	add r0, r7, r0
	bl MOD05_021EF620
	ldr r2, [sp, #0x14]
	add r1, r0, #0x0
	add r3, r2, #0x0
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x8]
	mul r3, r0
	ldr r0, [sp, #0x18]
	add r0, r0, r3
	bl MOD05_021EF654
	add r1, r0, #0x0
	cmp r1, #0x3
	bls _0204A53C
	mov r4, #0x0
	b _0204A558
_0204A53C:
	lsl r1, r1, #0x18
	ldr r0, [sp, #0x8]
	lsr r1, r1, #0x18
	bl MOD05_021EF8C8
	add r3, r0, #0x0
	add r0, sp, #0x30
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x34]
	bl MOD05_021F3DA4
	add r4, r0, #0x0
_0204A558:
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	beq _0204A5A4
	add r0, sp, #0x28
	add r5, #0x9c
	ldrb r0, [r0, #0x0]
	ldr r1, [r5, #0x0]
	bl MOD05_021F4568
	add r5, r0, #0x0
	cmp r4, #0x0
	beq _0204A59E
	ldr r0, [sp, #0x30]
	str r0, [sp, #0x10]
	cmp r5, r0
	bgt _0204A57C
	mov r1, #0x1
	b _0204A5B2
_0204A57C:
	ldr r1, [sp, #0x4]
	bl sub_0204A498
	add r4, r0, #0x0
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	bl sub_0204A498
	cmp r4, r0
	bgt _0204A598
	ldr r0, [sp, #0x30]
	mov r1, #0x1
	str r0, [sp, #0x10]
	b _0204A5B2
_0204A598:
	str r5, [sp, #0x10]
	mov r1, #0x2
	b _0204A5B2
_0204A59E:
	mov r1, #0x2
	str r5, [sp, #0x10]
	b _0204A5B2
_0204A5A4:
	cmp r4, #0x0
	beq _0204A5B0
	ldr r0, [sp, #0x30]
	mov r1, #0x1
	str r0, [sp, #0x10]
	b _0204A5B2
_0204A5B0:
	mov r1, #0x0
_0204A5B2:
	ldr r0, [sp, #0x50]
	cmp r0, #0x0
	beq _0204A5BA
	strb r1, [r0, #0x0]
_0204A5BA:
	ldr r0, [sp, #0x10]
	add sp, #0x38
	pop {r3-r7, pc}

	thumb_func_start sub_0204A5C0
sub_0204A5C0: ; 0x0204A5C0
	push {r3, lr}
	asr r1, r2, #0xf
	lsr r1, r1, #0x10
	add r1, r2, r1
	asr r2, r3, #0xf
	lsr r2, r2, #0x10
	add r2, r3, r2
	ldr r0, [r0, #0x24]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	mov r3, #0x0
	bl MOD05_021EF844
	ldr r1, [sp, #0x8]
	cmp r1, #0x0
	beq _0204A5EE
	cmp r0, #0x0
	beq _0204A5E8
	mov r1, #0x1
	b _0204A5EA
_0204A5E8:
	mov r1, #0x0
_0204A5EA:
	ldr r0, [sp, #0x8]
	strb r1, [r0, #0x0]
_0204A5EE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_0204A5F4
sub_0204A5F4: ; 0x0204A5F4
	push {r3-r7, lr}
	ldr r7, [r0, #0x24]
	add r4, r3, #0x0
	add r0, r7, #0x0
	add r3, sp, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl MOD05_021EF844
	cmp r0, #0x0
	bne _0204A612
	mov r0, #0xff
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
_0204A612:
	add r1, sp, #0x0
	ldrb r1, [r1, #0x0]
	add r0, r7, #0x0
	bl MOD05_021EF8DC
	lsr r2, r5, #0x1f
	lsl r1, r5, #0x1b
	sub r1, r1, r2
	mov r3, #0x1b
	ror r1, r3
	add r1, r2, r1
	lsr r5, r6, #0x1f
	lsl r2, r6, #0x1b
	sub r2, r2, r5
	ror r2, r3
	add r2, r5, r2
	lsl r2, r2, #0x5
	add r1, r1, r2
	lsl r1, r1, #0x1
	ldrh r0, [r0, r1]
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start sub_0204A640
sub_0204A640: ; 0x0204A640
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x28]
	add r4, r2, #0x0
	add r5, r1, #0x0
	add r7, r3, #0x0
	bl MapMatrix_GetWidth
	asr r2, r4, #0x4
	asr r1, r5, #0x4
	lsr r2, r2, #0x1b
	lsr r1, r1, #0x1b
	add r2, r4, r2
	add r1, r5, r1
	asr r2, r2, #0x5
	asr r1, r1, #0x5
	mul r0, r2
	add r0, r1, r0
	ldr r1, [r6, #0x54]
	bl sub_0204A3A4
	lsr r2, r5, #0x1f
	lsl r1, r5, #0x1b
	sub r1, r1, r2
	mov r3, #0x1b
	ror r1, r3
	add r1, r2, r1
	lsr r5, r4, #0x1f
	lsl r2, r4, #0x1b
	sub r2, r2, r5
	ror r2, r3
	add r2, r5, r2
	lsl r2, r2, #0x5
	add r1, r1, r2
	lsl r1, r1, #0x1
	ldrh r0, [r0, r1]
	strh r0, [r7, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_0204A690
sub_0204A690: ; 0x0204A690
	push {r3, lr}
	cmp r1, #0x0
	bne _0204A69C
	ldr r1, _0204A6AC ; =UNK_020F4708
	str r1, [r0, #0x0]
	pop {r3, pc}
_0204A69C:
	cmp r1, #0x1
	bne _0204A6A6
	ldr r1, _0204A6B0 ; =UNK_020F4710
	str r1, [r0, #0x0]
	pop {r3, pc}
_0204A6A6:
	bl GF_AssertFail
	pop {r3, pc}
	.balign 4
_0204A6AC: .word UNK_020F4708
_0204A6B0: .word UNK_020F4710

	thumb_func_start sub_0204A6B4
sub_0204A6B4: ; 0x0204A6B4
	push {r3-r4, lr}
	sub sp, #0x4
	ldr r4, [r0, #0x58]
	add r3, sp, #0x0
	ldr r4, [r4, #0x4]
	blx r4
	cmp r0, #0x0
	beq _0204A6DA
	add r0, sp, #0x0
	ldrh r0, [r0, #0x0]
	asr r0, r0, #0xf
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x1
	and r1, r0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #0x1
	beq _0204A6DC
_0204A6DA:
	mov r0, #0x0
_0204A6DC:
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start sub_0204A6E0
sub_0204A6E0: ; 0x0204A6E0
	push {r3-r4, lr}
	sub sp, #0x4
	ldr r4, [r0, #0x58]
	add r3, sp, #0x0
	ldr r4, [r4, #0x4]
	blx r4
	cmp r0, #0x0
	beq _0204A700
	add r0, sp, #0x0
	ldrh r0, [r0, #0x0]
	add sp, #0x4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3-r4, pc}
_0204A700:
	mov r0, #0xff
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start sub_0204A708
sub_0204A708: ; 0x0204A708
	push {r3-r4, lr}
	sub sp, #0x4
	ldr r4, [sp, #0x10]
	str r4, [sp, #0x0]
	ldr r4, [r0, #0x58]
	ldr r4, [r4, #0x0]
	blx r4
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start sub_0204A71C
sub_0204A71C: ; 0x0204A71C
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, [sp, #0x10]
	mov r5, #0x2
	str r1, [sp, #0x0]
	ldr r1, [r4, #0x4]
	lsl r2, r2, #0x10
	lsl r5, r5, #0xe
	lsl r3, r3, #0x10
	add r2, r2, r5
	add r3, r3, r5
	bl sub_0204A708
	ldr r1, [r4, #0x4]
	cmp r0, r1
	bge _0204A744
	mov r4, #0x0
	add r2, r1, #0x0
	mvn r4, r4
	b _0204A754
_0204A744:
	cmp r0, r1
	ble _0204A750
	add r2, r0, #0x0
	add r0, r1, #0x0
	mov r4, #0x1
	b _0204A754
_0204A750:
	mov r0, #0x0
	pop {r3-r5, pc}
_0204A754:
	sub r1, r2, r0
	mov r0, #0x5
	lsl r0, r0, #0xe
	cmp r1, r0
	blt _0204A768
	cmp r4, #0x0
	bne _0204A76A
	bl GF_AssertFail
	b _0204A76A
_0204A768:
	mov r4, #0x0
_0204A76A:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0204A770
sub_0204A770: ; 0x0204A770
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, sp, #0x4
	add r5, r0, #0x0
	add r4, r2, #0x0
	add r7, r3, #0x0
	str r6, [sp, #0x0]
	bl sub_0204A71C
	ldr r1, [sp, #0x20]
	cmp r1, #0x0
	beq _0204A78A
	strb r0, [r1, #0x0]
_0204A78A:
	cmp r0, #0x0
	bne _0204A7C2
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl sub_0204A6B4
	add r6, r0, #0x0
	bne _0204A7BC
	add r0, sp, #0x4
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0204A7BC
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl sub_0204A6E0
	bl sub_020548B4
	cmp r0, #0x0
	beq _0204A7BC
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0204A7BC:
	add sp, #0x8
	add r0, r6, #0x0
	pop {r3-r7, pc}
_0204A7C2:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start sub_0204A7C8
sub_0204A7C8: ; 0x0204A7C8
	push {r3-r7, lr}
	sub sp, #0x10
	add r6, sp, #0x8
	add r5, r0, #0x0
	str r1, [sp, #0x4]
	add r4, r2, #0x0
	add r7, r3, #0x0
	str r6, [sp, #0x0]
	bl sub_0204A71C
	ldr r1, [sp, #0x28]
	cmp r1, #0x0
	beq _0204A7E4
	strb r0, [r1, #0x0]
_0204A7E4:
	cmp r0, #0x0
	bne _0204A83A
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r0, r5, #0x0
	ldr r3, [r3, #0x4]
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl sub_0205CE00
	cmp r0, #0x0
	bne _0204A834
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl sub_0204A6B4
	str r0, [sp, #0xc]
	cmp r0, #0x0
	bne _0204A82E
	add r0, sp, #0x8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0204A82E
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl sub_0204A6E0
	bl sub_020548B4
	cmp r0, #0x0
	beq _0204A82E
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_0204A82E:
	ldr r0, [sp, #0xc]
	add sp, #0x10
	pop {r3-r7, pc}
_0204A834:
	ldr r0, [sp, #0xc]
	add sp, #0x10
	pop {r3-r7, pc}
_0204A83A:
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start sub_0204A840
sub_0204A840: ; 0x0204A840
	push {r3-r7, lr}
	add r6, r0, r2
	ldr r0, [sp, #0x18]
	add r4, r1, r3
	add r0, r6, r0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x1c]
	ldr r5, [sp, #0x20]
	add r7, r4, r0
	cmp r6, #0x0
	blt _0204A864
	cmp r4, #0x0
	blt _0204A864
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	blt _0204A864
	cmp r7, #0x0
	bge _0204A868
_0204A864:
	bl GF_AssertFail
_0204A868:
	lsl r0, r6, #0x10
	str r0, [r5, #0x0]
	lsl r0, r4, #0x10
	str r0, [r5, #0x4]
	ldr r0, [sp, #0x0]
	lsl r0, r0, #0x10
	str r0, [r5, #0x8]
	lsl r0, r7, #0x10
	str r0, [r5, #0xc]
	pop {r3-r7, pc}

	thumb_func_start sub_0204A87C
sub_0204A87C: ; 0x0204A87C
	push {r4-r5, lr}
	sub sp, #0xc
	add r3, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r0, sp, #0x0
	add r1, r3, #0x0
	bl MOD05_021E7EA0
	ldr r1, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, [sp, #0x8]
	add r0, r1, r0
	str r0, [sp, #0x0]
	ldr r1, [r4, #0x8]
	add r2, r2, r1
	str r2, [sp, #0x8]
	ldr r1, [r5, #0x0]
	cmp r1, r0
	bgt _0204A8BC
	ldr r1, [r5, #0x8]
	cmp r0, r1
	bgt _0204A8BC
	ldr r0, [r5, #0x4]
	cmp r0, r2
	bgt _0204A8BC
	ldr r0, [r5, #0xc]
	cmp r2, r0
	bgt _0204A8BC
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r5, pc}
_0204A8BC:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start sub_0204A8C4
sub_0204A8C4: ; 0x0204A8C4
	push {r4-r7, lr}
	sub sp, #0x1c
	str r0, [sp, #0x0]
	mov r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x4]
	str r0, [sp, #0x8]
_0204A8D4:
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [r1, #0x24]
	add r2, sp, #0xc
	bl MOD05_021EF604
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x8]
	ldr r0, [r0, #0x24]
	bl MOD05_021EF824
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x28]
	bl MapMatrix_GetWidth
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r2, sp, #0x10
	bl sub_0204AAD4
	mov r5, #0x0
_0204A900:
	ldr r0, [sp, #0xc]
	add r1, r5, #0x0
	bl MOD05_021E7ED0
	add r1, r7, #0x0
	add r2, sp, #0x10
	add r4, r0, #0x0
	bl sub_0204A87C
	cmp r0, #0x0
	beq _0204A92E
	add r0, r4, #0x0
	bl MOD05_021E7EC4
	cmp r0, r6
	bne _0204A92E
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0204A928
	str r4, [r0, #0x0]
_0204A928:
	add sp, #0x1c
	mov r0, #0x1
	pop {r4-r7, pc}
_0204A92E:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x20
	blo _0204A900
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	cmp r0, #0x4
	blo _0204A8D4
	mov r0, #0x0
	add sp, #0x1c
	pop {r4-r7, pc}

	thumb_func_start sub_0204A94C
sub_0204A94C: ; 0x0204A94C
	push {r4-r7, lr}
	sub sp, #0x1c
	str r0, [sp, #0x0]
	mov r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	str r3, [sp, #0x4]
	str r0, [sp, #0x8]
_0204A95C:
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [r1, #0x24]
	add r2, sp, #0xc
	bl MOD05_021EF604
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x8]
	ldr r0, [r0, #0x24]
	bl MOD05_021EF824
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x28]
	bl MapMatrix_GetWidth
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r2, sp, #0x10
	bl sub_0204AAD4
	mov r6, #0x0
_0204A988:
	ldr r0, [sp, #0xc]
	add r1, r6, #0x0
	bl MOD05_021E7ED0
	ldr r1, [sp, #0x4]
	add r2, sp, #0x10
	add r7, r0, #0x0
	bl sub_0204A87C
	cmp r0, #0x0
	beq _0204A9D2
	add r0, r7, #0x0
	bl MOD05_021E7EC4
	mov r1, #0x0
	cmp r4, #0x0
	bls _0204A9D2
_0204A9AA:
	lsl r2, r1, #0x2
	ldr r2, [r5, r2]
	cmp r0, r2
	bne _0204A9C8
	ldr r1, [sp, #0x30]
	cmp r1, #0x0
	beq _0204A9BA
	str r7, [r1, #0x0]
_0204A9BA:
	ldr r1, [sp, #0x34]
	cmp r1, #0x0
	beq _0204A9C2
	str r0, [r1, #0x0]
_0204A9C2:
	add sp, #0x1c
	mov r0, #0x1
	pop {r4-r7, pc}
_0204A9C8:
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, r4
	blo _0204A9AA
_0204A9D2:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x20
	blo _0204A988
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	cmp r0, #0x4
	blo _0204A95C
	mov r0, #0x0
	add sp, #0x1c
	pop {r4-r7, pc}

	thumb_func_start sub_0204A9F0
sub_0204A9F0: ; 0x0204A9F0
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x0]
	add r5, r1, #0x0
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	mov r7, #0x0
_0204A9FE:
	ldr r1, [sp, #0x0]
	add r0, r7, #0x0
	ldr r1, [r1, #0x24]
	add r2, sp, #0xc
	bl MOD05_021EF604
	mov r4, #0x0
_0204AA0C:
	ldr r0, [sp, #0xc]
	add r1, r4, #0x0
	bl MOD05_021E7ED0
	add r6, r0, #0x0
	bl MOD05_021E7EC4
	cmp r0, r5
	bne _0204AA40
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0204AA26
	str r6, [r0, #0x0]
_0204AA26:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _0204AA3A
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, #0x24]
	bl MOD05_021EF824
	ldr r1, [sp, #0x8]
	str r0, [r1, #0x0]
_0204AA3A:
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_0204AA40:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x20
	blo _0204AA0C
	add r0, r7, #0x1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	cmp r7, #0x4
	blo _0204A9FE
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_0204AA5C
sub_0204AA5C: ; 0x0204AA5C
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	str r3, [sp, #0x4]
	str r0, [sp, #0x8]
_0204AA6C:
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [r1, #0x24]
	add r2, sp, #0xc
	bl MOD05_021EF604
	mov r6, #0x0
_0204AA7A:
	ldr r0, [sp, #0xc]
	add r1, r6, #0x0
	bl MOD05_021E7ED0
	add r7, r0, #0x0
	bl MOD05_021E7EC4
	mov r1, #0x0
	cmp r4, #0x0
	bls _0204AAB6
_0204AA8E:
	lsl r2, r1, #0x2
	ldr r2, [r5, r2]
	cmp r0, r2
	bne _0204AAAC
	ldr r1, [sp, #0x4]
	cmp r1, #0x0
	beq _0204AA9E
	str r7, [r1, #0x0]
_0204AA9E:
	ldr r1, [sp, #0x28]
	cmp r1, #0x0
	beq _0204AAA6
	str r0, [r1, #0x0]
_0204AAA6:
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_0204AAAC:
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, r4
	blo _0204AA8E
_0204AAB6:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x20
	blo _0204AA7A
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	cmp r0, #0x4
	blo _0204AA6C
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start sub_0204AAD4
sub_0204AAD4: ; 0x0204AAD4
	push {r4-r6, lr}
	add r4, r2, #0x0
	mov r2, #0x1
	lsl r2, r2, #0x14
	str r2, [r4, #0x0]
	add r5, r0, #0x0
	add r6, r1, #0x0
	str r2, [r4, #0x8]
	bl _s32_div_f
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	ldr r0, [r4, #0x0]
	lsl r1, r1, #0x15
	add r0, r0, r1
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	ldr r1, [r4, #0x8]
	lsl r0, r0, #0x15
	add r0, r1, r0
	str r0, [r4, #0x8]
	pop {r4-r6, pc}
	.balign 4
