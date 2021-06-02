	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021DA5B8
MOD05_021DA5B8: ; 0x021DA5B8
	push {r3, lr}
	mov r0, #4
	mov r1, #0x28
	bl AllocFromHeapAtEnd
	mov r1, #0
	str r1, [r0]
	pop {r3, pc}

	thumb_func_start MOD05_021DA5C8
MOD05_021DA5C8: ; 0x021DA5C8
	ldr r3, _021DA5CC ; =FreeToHeap
	bx r3
	.balign 4, 0
_021DA5CC: .word FreeToHeap

	thumb_func_start MOD05_021DA5D0
MOD05_021DA5D0: ; 0x021DA5D0
	str r0, [r2, #0x14]
	str r1, [r2, #0x18]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021DA5D8
MOD05_021DA5D8: ; 0x021DA5D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x84
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #5
	bls _021DA5E8
	b _021DA78E
_021DA5E8:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DA5F4: ; jump table
	.short _021DA600 - _021DA5F4 - 2 ; case 0
	.short _021DA69A - _021DA5F4 - 2 ; case 1
	.short _021DA6EC - _021DA5F4 - 2 ; case 2
	.short _021DA700 - _021DA5F4 - 2 ; case 3
	.short _021DA714 - _021DA5F4 - 2 ; case 4
	.short _021DA772 - _021DA5F4 - 2 ; case 5
_021DA600:
	ldr r6, _021DA7A4 ; =UNK05_021F650C
	add r3, sp, #0x34
	mov r2, #0xa
_021DA606:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021DA606
	mov r0, #0
	str r0, [r4, #0x20]
	strb r0, [r4, #0x1d]
	mov r0, #3
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	add r0, sp, #0x24
	str r0, [sp, #8]
	sub r2, r2, #2
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	add r3, r2, #0
	bl FUN_0204A840
	mov r0, #1
	strb r0, [r4, #0x1c]
	add r0, sp, #0x20
	str r0, [sp]
	add r0, sp, #0x1c
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, sp, #0x34
	mov r2, #0x14
	add r3, sp, #0x24
	bl FUN_0204A94C
	cmp r0, #0
	beq _021DA688
	ldr r0, [r5, #0x4c]
	ldr r1, [sp, #0x1c]
	bl MOD05_021DA230
	add r6, r0, #0
	strb r6, [r4, #0x1e]
	ldr r0, [r5, #0x2c]
	bl MOD05_021F4C88
	add r7, r0, #0
	ldr r0, [sp, #0x20]
	bl MOD05_021E7EC8
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	bl MOD05_021E7ECC
	ldr r1, [sp, #0x18]
	mov r2, #1
	str r1, [sp]
	str r0, [sp, #4]
	str r7, [sp, #8]
	str r6, [sp, #0xc]
	str r2, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	ldr r3, [sp, #0x1c]
	bl MOD05_021DA464
	b _021DA692
_021DA688:
	bl GF_AssertFail
	add sp, #0x84
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021DA692:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DA78E
_021DA69A:
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl MOD05_021DA5AC
	add r6, r0, #0
	cmp r6, #0x4b
	beq _021DA6B2
	ldr r0, [r5, #0x20]
	bl FUN_0201EC88
	mov r0, #1
	str r0, [r4, #0x20]
_021DA6B2:
	add r0, r6, #0
	bl MOD05_021DAA6C
	cmp r0, #0
	beq _021DA6C0
	ldr r6, _021DA7A8 ; =0x00000608
	b _021DA6C2
_021DA6C0:
	ldr r6, _021DA7AC ; =0x00000605
_021DA6C2:
	ldrb r0, [r4, #0x1e]
	cmp r0, #2
	bne _021DA6CC
	mov r2, #0
	b _021DA6DA
_021DA6CC:
	cmp r0, #4
	bne _021DA6D4
	mov r2, #0
	b _021DA6DA
_021DA6D4:
	bl GF_AssertFail
	mov r2, #0
_021DA6DA:
	ldr r0, [r5, #0x50]
	mov r1, #1
	add r3, r6, #0
	bl MOD05_021DA514
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DA78E
_021DA6EC:
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl MOD05_021DA58C
	cmp r0, #0
	beq _021DA78E
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DA78E
_021DA700:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	mov r1, #0xc
	bl FUN_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DA78E
_021DA714:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r6, r0, #0
	bl FUN_0205AE28
	cmp r0, #1
	bne _021DA78E
	add r0, r6, #0
	bl FUN_0205AE50
	add r0, r6, #0
	mov r1, #1
	bl FUN_0205889C
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl MOD05_021DA5AC
	bl MOD05_021DAA6C
	cmp r0, #0
	beq _021DA746
	mov r6, #0
	b _021DA748
_021DA746:
	ldr r6, _021DA7B0 ; =0x00000607
_021DA748:
	ldrb r0, [r4, #0x1e]
	cmp r0, #2
	bne _021DA752
	mov r2, #1
	b _021DA760
_021DA752:
	cmp r0, #4
	bne _021DA75A
	mov r2, #1
	b _021DA760
_021DA75A:
	bl GF_AssertFail
	mov r2, #1
_021DA760:
	ldr r0, [r5, #0x50]
	mov r1, #1
	add r3, r6, #0
	bl MOD05_021DA514
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DA78E
_021DA772:
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl MOD05_021DA58C
	cmp r0, #0
	beq _021DA78E
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #1
	bl MOD05_021DA54C
	add sp, #0x84
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021DA78E:
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _021DA79E
	add r4, #0x1d
	ldr r0, [r5, #0x20]
	add r1, r4, #0
	bl MOD05_021DA9E8
_021DA79E:
	mov r0, #0
	add sp, #0x84
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021DA7A4: .word UNK05_021F650C
_021DA7A8: .word 0x00000608
_021DA7AC: .word 0x00000605
_021DA7B0: .word 0x00000607

	thumb_func_start MOD05_021DA7B4
MOD05_021DA7B4: ; 0x021DA7B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x84
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #6
	bls _021DA7C4
	b _021DA9BE
_021DA7C4:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DA7D0: ; jump table
	.short _021DA7DE - _021DA7D0 - 2 ; case 0
	.short _021DA896 - _021DA7D0 - 2 ; case 1
	.short _021DA8F6 - _021DA7D0 - 2 ; case 2
	.short _021DA916 - _021DA7D0 - 2 ; case 3
	.short _021DA92A - _021DA7D0 - 2 ; case 4
	.short _021DA980 - _021DA7D0 - 2 ; case 5
	.short _021DA9B0 - _021DA7D0 - 2 ; case 6
_021DA7DE:
	ldr r6, _021DA9D4 ; =UNK05_021F655C
	add r3, sp, #0x34
	mov r2, #0xa
_021DA7E4:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021DA7E4
	mov r3, #0
	str r3, [r4, #0x20]
	strb r3, [r4, #0x1d]
	mov r0, #3
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	add r0, sp, #0x24
	str r0, [sp, #8]
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	sub r2, r2, #2
	bl FUN_0204A840
	mov r0, #1
	strb r0, [r4, #0x1c]
	add r0, sp, #0x20
	str r0, [sp]
	add r0, sp, #0x1c
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, sp, #0x34
	mov r2, #0x14
	add r3, sp, #0x24
	bl FUN_0204A94C
	cmp r0, #0
	beq _021DA864
	ldr r0, [r5, #0x4c]
	ldr r1, [sp, #0x1c]
	bl MOD05_021DA230
	add r6, r0, #0
	strb r6, [r4, #0x1e]
	ldr r0, [r5, #0x2c]
	bl MOD05_021F4C88
	add r7, r0, #0
	ldr r0, [sp, #0x20]
	bl MOD05_021E7EC8
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	bl MOD05_021E7ECC
	ldr r1, [sp, #0x18]
	mov r2, #1
	str r1, [sp]
	str r0, [sp, #4]
	str r7, [sp, #8]
	str r6, [sp, #0xc]
	str r2, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	ldr r3, [sp, #0x1c]
	bl MOD05_021DA464
	b _021DA878
_021DA864:
	bl GF_AssertFail
	mov r0, #1
	bl MOD05_021D7CA4
	mov r0, #6
	str r0, [r4]
	add sp, #0x84
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021DA878:
	ldr r0, [r5, #0x20]
	bl FUN_0201F008
	strh r0, [r4, #0x24]
	ldr r0, [sp, #0x1c]
	cmp r0, #0x4b
	beq _021DA88E
	ldr r0, _021DA9D8 ; =0x0000FFA0
	ldr r1, [r5, #0x20]
	bl FUN_0201EF2C
_021DA88E:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DA9BE
_021DA896:
	mov r1, #0
	str r1, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x10]
	mov r2, #9
	bl FUN_0204C1B4
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl MOD05_021DA5AC
	cmp r0, #0x4b
	beq _021DA8BE
	mov r1, #1
	str r1, [r4, #0x20]
_021DA8BE:
	bl MOD05_021DAA6C
	cmp r0, #0
	beq _021DA8CA
	ldr r6, _021DA9DC ; =0x00000608
	b _021DA8CC
_021DA8CA:
	ldr r6, _021DA9E0 ; =0x00000605
_021DA8CC:
	ldrb r0, [r4, #0x1e]
	cmp r0, #2
	bne _021DA8D6
	mov r2, #0
	b _021DA8E4
_021DA8D6:
	cmp r0, #4
	bne _021DA8DE
	mov r2, #2
	b _021DA8E4
_021DA8DE:
	bl GF_AssertFail
	mov r2, #0
_021DA8E4:
	ldr r0, [r5, #0x50]
	mov r1, #1
	add r3, r6, #0
	bl MOD05_021DA514
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DA9BE
_021DA8F6:
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl MOD05_021DA58C
	cmp r0, #0
	beq _021DA9BE
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	mov r1, #0
	bl FUN_0205889C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DA9BE
_021DA916:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	mov r1, #0xd
	bl FUN_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DA9BE
_021DA92A:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r6, r0, #0
	bl FUN_0205AE28
	cmp r0, #1
	bne _021DA9BE
	add r0, r6, #0
	bl FUN_0205AE50
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl MOD05_021DA5AC
	bl MOD05_021DAA6C
	cmp r0, #0
	beq _021DA954
	mov r6, #0
	b _021DA956
_021DA954:
	ldr r6, _021DA9E4 ; =0x00000607
_021DA956:
	ldrb r0, [r4, #0x1e]
	cmp r0, #2
	bne _021DA960
	mov r2, #1
	b _021DA96E
_021DA960:
	cmp r0, #4
	bne _021DA968
	mov r2, #3
	b _021DA96E
_021DA968:
	bl GF_AssertFail
	mov r2, #1
_021DA96E:
	ldr r0, [r5, #0x50]
	mov r1, #1
	add r3, r6, #0
	bl MOD05_021DA514
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DA9BE
_021DA980:
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl MOD05_021DA58C
	cmp r0, #0
	beq _021DA9BE
	bl FUN_0200E308
	cmp r0, #0
	beq _021DA9BE
	ldr r0, [r5, #0x20]
	bl FUN_0201F008
	ldrh r1, [r4, #0x24]
	cmp r1, r0
	bne _021DA9BE
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #1
	bl MOD05_021DA54C
	add sp, #0x84
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021DA9B0:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DA9BE
	add sp, #0x84
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021DA9BE:
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _021DA9CE
	add r4, #0x1d
	ldr r0, [r5, #0x20]
	add r1, r4, #0
	bl MOD05_021DAA2C
_021DA9CE:
	mov r0, #0
	add sp, #0x84
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021DA9D4: .word UNK05_021F655C
_021DA9D8: .word 0x0000FFA0
_021DA9DC: .word 0x00000608
_021DA9E0: .word 0x00000605
_021DA9E4: .word 0x00000607

	thumb_func_start MOD05_021DA9E8
MOD05_021DA9E8: ; 0x021DA9E8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldrb r0, [r5]
	mov r4, #0xc
	add r1, r0, #0
	mul r1, r4
	cmp r1, #0x60
	bgt _021DAA28
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0x60
	bls _021DAA08
	sub r0, #0x60
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_021DAA08:
	add r0, r6, #0
	bl FUN_0201F008
	sub r0, r0, r4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	beq _021DAA22
	neg r0, r4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r1, r6, #0
	bl FUN_0201EF2C
_021DAA22:
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
_021DAA28:
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DAA2C
MOD05_021DAA2C: ; 0x021DAA2C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldrb r0, [r5]
	lsl r0, r0, #4
	cmp r0, #0x60
	bge _021DAA68
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0x60
	bls _021DAA4A
	sub r0, #0x60
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	b _021DAA4C
_021DAA4A:
	mov r4, #0x10
_021DAA4C:
	add r0, r6, #0
	bl FUN_0201F008
	add r0, r0, r4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	beq _021DAA62
	add r0, r4, #0
	add r1, r6, #0
	bl FUN_0201EF2C
_021DAA62:
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
_021DAA68:
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DAA6C
MOD05_021DAA6C: ; 0x021DAA6C
	cmp r0, #0x46
	beq _021DAA98
	ldr r2, _021DAAA0 ; =0x000001BA
	cmp r0, r2
	beq _021DAA98
	add r1, r2, #0
	sub r1, #0x90
	cmp r0, r1
	beq _021DAA98
	add r1, r2, #0
	add r1, #0xe
	cmp r0, r1
	beq _021DAA98
	add r1, r2, #0
	sub r1, #0xf
	cmp r0, r1
	beq _021DAA98
	add r2, #0x2a
	cmp r0, r2
	beq _021DAA98
	cmp r0, #0x4b
	bne _021DAA9C
_021DAA98:
	mov r0, #1
	bx lr
_021DAA9C:
	mov r0, #0
	bx lr
	.balign 4, 0
_021DAAA0: .word 0x000001BA

	thumb_func_start MOD05_021DAAA4
MOD05_021DAAA4: ; 0x021DAAA4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	add r6, r2, #0
	cmp r0, #5
	bls _021DAAB6
	b _021DAC60
_021DAAB6:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DAAC2: ; jump table
	.short _021DAACE - _021DAAC2 - 2 ; case 0
	.short _021DAB8E - _021DAAC2 - 2 ; case 1
	.short _021DABCE - _021DAAC2 - 2 ; case 2
	.short _021DABEE - _021DAAC2 - 2 ; case 3
	.short _021DAC16 - _021DAAC2 - 2 ; case 4
	.short _021DAC34 - _021DAAC2 - 2 ; case 5
_021DAACE:
	ldr r3, _021DAC68 ; =UNK05_021F64FC
	add r2, sp, #0x20
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	cmp r6, #2
	bne _021DAAF8
	mov r0, #2
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	add r0, sp, #0x30
	str r0, [sp, #8]
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	sub r2, r2, #2
	mov r3, #0
	bl FUN_0204A840
	b _021DAB10
_021DAAF8:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, sp, #0x30
	str r0, [sp, #8]
	mov r2, #0
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	add r3, r2, #0
	bl FUN_0204A840
_021DAB10:
	mov r0, #2
	strb r0, [r4, #0x1c]
	add r0, sp, #0x1c
	str r0, [sp]
	add r0, sp, #0x18
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, sp, #0x20
	mov r2, #4
	add r3, sp, #0x30
	bl FUN_0204A94C
	cmp r0, #0
	beq _021DAB5E
	ldr r0, [r5, #0x2c]
	bl MOD05_021F4C88
	add r6, r0, #0
	ldr r0, [sp, #0x1c]
	bl MOD05_021E7EC8
	add r7, r0, #0
	ldr r0, [sp, #0x1c]
	bl MOD05_021E7ECC
	str r7, [sp]
	str r0, [sp, #4]
	str r6, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	ldr r3, [sp, #0x18]
	mov r2, #2
	bl MOD05_021DA464
	b _021DAB68
_021DAB5E:
	bl GF_AssertFail
	add sp, #0x40
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DAB68:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_0205AD98
	cmp r0, #1
	bne _021DAB82
	add r0, r5, #0
	mov r1, #0x49
	bl FUN_0205ADDC
	b _021DAB86
_021DAB82:
	bl GF_AssertFail
_021DAB86:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DAC60
_021DAB8E:
	mov r0, #1
	bl MOD05_021D7CA4
	ldr r0, [r5, #0x50]
	ldr r3, _021DAC6C ; =0x00000615
	mov r1, #2
	mov r2, #0
	bl MOD05_021DA514
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_0205AD98
	cmp r0, #1
	bne _021DABC2
	cmp r6, #3
	bne _021DABB8
	mov r1, #0xb
	b _021DABBA
_021DABB8:
	mov r1, #0xa
_021DABBA:
	add r0, r5, #0
	bl FUN_0205ADDC
	b _021DABC6
_021DABC2:
	bl GF_AssertFail
_021DABC6:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DAC60
_021DABCE:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_0205AD98
	cmp r0, #1
	bne _021DAC60
	add r0, r5, #0
	mov r1, #0x4a
	bl FUN_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DAC60
_021DABEE:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_0205AD98
	cmp r0, #1
	bne _021DAC60
	cmp r6, #3
	bne _021DAC06
	mov r1, #0xb
	b _021DAC08
_021DAC06:
	mov r1, #0xa
_021DAC08:
	add r0, r5, #0
	bl FUN_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DAC60
_021DAC16:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_0205AE28
	cmp r0, #1
	bne _021DAC60
	add r0, r5, #0
	bl FUN_0205AE50
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DAC60
_021DAC34:
	ldr r0, [r5, #0x50]
	mov r1, #2
	bl MOD05_021DA58C
	cmp r0, #0
	beq _021DAC60
	bl FUN_0200E308
	cmp r0, #0
	beq _021DAC60
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #2
	bl MOD05_021DA54C
	ldr r0, _021DAC6C ; =0x00000615
	mov r1, #0
	bl FUN_020054F0
	add sp, #0x40
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DAC60:
	mov r0, #0
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DAC68: .word UNK05_021F64FC
_021DAC6C: .word 0x00000615

	thumb_func_start MOD05_021DAC70
MOD05_021DAC70: ; 0x021DAC70
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	add r6, r2, #0
	cmp r0, #4
	bls _021DAC82
	b _021DAE04
_021DAC82:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DAC8E: ; jump table
	.short _021DAC98 - _021DAC8E - 2 ; case 0
	.short _021DAD5A - _021DAC8E - 2 ; case 1
	.short _021DAD94 - _021DAC8E - 2 ; case 2
	.short _021DADBA - _021DAC8E - 2 ; case 3
	.short _021DADD8 - _021DAC8E - 2 ; case 4
_021DAC98:
	ldr r3, _021DAE0C ; =UNK05_021F64EC
	add r2, sp, #0x20
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	cmp r6, #2
	bne _021DACC2
	mov r0, #2
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	add r0, sp, #0x30
	str r0, [sp, #8]
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	sub r2, r2, #2
	mov r3, #0
	bl FUN_0204A840
	b _021DACDA
_021DACC2:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, sp, #0x30
	str r0, [sp, #8]
	mov r2, #0
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	add r3, r2, #0
	bl FUN_0204A840
_021DACDA:
	mov r0, #2
	strb r0, [r4, #0x1c]
	add r0, sp, #0x1c
	str r0, [sp]
	add r0, sp, #0x18
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, sp, #0x20
	mov r2, #4
	add r3, sp, #0x30
	bl FUN_0204A94C
	cmp r0, #0
	beq _021DAD2A
	ldr r0, [r5, #0x2c]
	bl MOD05_021F4C88
	add r6, r0, #0
	ldr r0, [sp, #0x1c]
	bl MOD05_021E7EC8
	add r7, r0, #0
	ldr r0, [sp, #0x1c]
	bl MOD05_021E7ECC
	str r7, [sp]
	str r0, [sp, #4]
	str r6, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	ldr r3, [sp, #0x18]
	mov r2, #2
	bl MOD05_021DA464
	b _021DAD34
_021DAD2A:
	bl GF_AssertFail
	add sp, #0x40
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DAD34:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_0205AD98
	cmp r0, #1
	bne _021DAD4E
	add r0, r5, #0
	mov r1, #0x49
	bl FUN_0205ADDC
	b _021DAD52
_021DAD4E:
	bl GF_AssertFail
_021DAD52:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DAE04
_021DAD5A:
	ldr r0, [r5, #0x50]
	ldr r3, _021DAE10 ; =0x00000615
	mov r1, #2
	mov r2, #0
	bl MOD05_021DA514
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_0205AD98
	cmp r0, #1
	bne _021DAD88
	cmp r6, #2
	bne _021DAD7E
	mov r1, #0xa
	b _021DAD80
_021DAD7E:
	mov r1, #0xb
_021DAD80:
	add r0, r5, #0
	bl FUN_0205ADDC
	b _021DAD8C
_021DAD88:
	bl GF_AssertFail
_021DAD8C:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DAE04
_021DAD94:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_0205AD98
	cmp r0, #1
	bne _021DAE04
	add r0, r5, #0
	mov r1, #0x4a
	bl FUN_0205ADDC
	mov r0, #0
	bl MOD05_021D7CA4
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DAE04
_021DADBA:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_0205AE28
	cmp r0, #1
	bne _021DAE04
	add r0, r5, #0
	bl FUN_0205AE50
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DAE04
_021DADD8:
	ldr r0, [r5, #0x50]
	mov r1, #2
	bl MOD05_021DA58C
	cmp r0, #0
	beq _021DAE04
	bl FUN_0200E308
	cmp r0, #0
	beq _021DAE04
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #2
	bl MOD05_021DA54C
	ldr r0, _021DAE10 ; =0x00000615
	mov r1, #0
	bl FUN_020054F0
	add sp, #0x40
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DAE04:
	mov r0, #0
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DAE0C: .word UNK05_021F64EC
_021DAE10: .word 0x00000615

	thumb_func_start MOD05_021DAE14
MOD05_021DAE14: ; 0x021DAE14
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl FUN_02046528
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldrb r1, [r4]
	ldr r0, [r5, #0x50]
	bl MOD05_021DA58C
	cmp r0, #0
	beq _021DAE3C
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DAE3C:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021DAE40
MOD05_021DAE40: ; 0x021DAE40
	push {r4, r5, r6, r7, lr}
	sub sp, #0x84
	ldr r6, _021DAED0 ; =UNK05_021F65AC
	str r3, [sp, #0x18]
	add r5, r0, #0
	add r7, r1, #0
	add r4, sp, #0x34
	mov r3, #0xa
_021DAE50:
	ldmia r6!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r3, r3, #1
	bne _021DAE50
	mov r0, #3
	str r0, [sp]
	mov r3, #1
	add r1, r2, #0
	str r3, [sp, #4]
	add r0, sp, #0x24
	str r0, [sp, #8]
	sub r2, r3, #2
	add r0, r7, #0
	mov r3, #0
	bl FUN_0204A840
	add r0, sp, #0x20
	str r0, [sp]
	add r0, sp, #0x1c
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, sp, #0x34
	mov r2, #0x14
	add r3, sp, #0x24
	bl FUN_0204A94C
	cmp r0, #0
	beq _021DAEC8
	ldr r0, [r5, #0x4c]
	ldr r1, [sp, #0x1c]
	bl MOD05_021DA230
	add r4, r0, #0
	ldr r0, [r5, #0x2c]
	bl MOD05_021F4C88
	add r6, r0, #0
	ldr r0, [sp, #0x20]
	bl MOD05_021E7EC8
	add r7, r0, #0
	ldr r0, [sp, #0x20]
	bl MOD05_021E7ECC
	str r7, [sp]
	str r0, [sp, #4]
	str r6, [sp, #8]
	str r4, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	bl MOD05_021DA464
	add sp, #0x84
	pop {r4, r5, r6, r7, pc}
_021DAEC8:
	bl GF_AssertFail
	add sp, #0x84
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021DAED0: .word UNK05_021F65AC

	thumb_func_start MOD05_021DAED4
MOD05_021DAED4: ; 0x021DAED4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	add r7, r1, #0
	bl MOD05_021DA5AC
	add r6, r0, #0
	ldr r0, [r5, #0x4c]
	add r1, r6, #0
	bl MOD05_021DA230
	add r4, r0, #0
	add r0, r6, #0
	bl MOD05_021DAA6C
	cmp r0, #0
	beq _021DAEFA
	ldr r6, _021DAF20 ; =0x00000608
	b _021DAEFC
_021DAEFA:
	ldr r6, _021DAF24 ; =0x00000605
_021DAEFC:
	cmp r4, #2
	bne _021DAF04
	mov r2, #0
	b _021DAF12
_021DAF04:
	cmp r4, #4
	bne _021DAF0C
	mov r2, #0
	b _021DAF12
_021DAF0C:
	bl GF_AssertFail
	mov r2, #0
_021DAF12:
	ldr r0, [r5, #0x50]
	add r1, r7, #0
	add r3, r6, #0
	bl MOD05_021DA514
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DAF20: .word 0x00000608
_021DAF24: .word 0x00000605

	thumb_func_start MOD05_021DAF28
MOD05_021DAF28: ; 0x021DAF28
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	add r7, r1, #0
	bl MOD05_021DA5AC
	add r6, r0, #0
	ldr r0, [r5, #0x4c]
	add r1, r6, #0
	bl MOD05_021DA230
	add r4, r0, #0
	add r0, r6, #0
	bl MOD05_021DAA6C
	cmp r0, #0
	beq _021DAF4E
	mov r6, #0
	b _021DAF50
_021DAF4E:
	ldr r6, _021DAF74 ; =0x00000607
_021DAF50:
	cmp r4, #2
	bne _021DAF58
	mov r2, #1
	b _021DAF66
_021DAF58:
	cmp r4, #4
	bne _021DAF60
	mov r2, #1
	b _021DAF66
_021DAF60:
	bl GF_AssertFail
	mov r2, #1
_021DAF66:
	ldr r0, [r5, #0x50]
	add r1, r7, #0
	add r3, r6, #0
	bl MOD05_021DA514
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DAF74: .word 0x00000607

	thumb_func_start MOD05_021DAF78
MOD05_021DAF78: ; 0x021DAF78
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #4
	mov r1, #1
	bl AllocFromHeapAtEnd
	add r2, r0, #0
	strb r4, [r2]
	ldr r0, [r5, #0x10]
	ldr r1, _021DAF94 ; =MOD05_021DAE14
	bl FUN_0204640C
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021DAF94: .word MOD05_021DAE14

	thumb_func_start MOD05_021DAF98
MOD05_021DAF98: ; 0x021DAF98
	add r3, r0, #0
	add r2, r1, #0
	ldr r0, [r3, #0x4c]
	ldr r1, [r3, #0x50]
	ldr r3, _021DAFA4 ; =MOD05_021DA54C
	bx r3
	.balign 4, 0
_021DAFA4: .word MOD05_021DA54C

	thumb_func_start MOD05_021DAFA8
MOD05_021DAFA8: ; 0x021DAFA8
	push {r4, r5, lr}
	sub sp, #0x2c
	add r5, r2, #0
	ldr r2, _021DB02C ; =UNK05_021F64E4
	add r4, r3, #0
	ldr r3, [r2]
	ldr r2, [r2, #4]
	str r3, [sp, #0xc]
	str r2, [sp, #0x10]
	mov r2, #1
	str r2, [sp]
	mov r2, #3
	str r2, [sp, #4]
	add r2, sp, #0x1c
	str r2, [sp, #8]
	mov r2, #0
	sub r3, r2, #1
	bl FUN_0204A840
	add r0, sp, #0x18
	str r0, [sp]
	add r0, sp, #0x14
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, sp, #0xc
	mov r2, #2
	add r3, sp, #0x1c
	bl FUN_0204A94C
	cmp r0, #0
	bne _021DAFEA
	bl GF_AssertFail
_021DAFEA:
	ldr r0, [sp, #0x18]
	bl MOD05_021E7EC8
	add r3, r0, #0
	ldr r0, [r4, #0x4c]
	add r1, r5, #0
	str r0, [sp]
	ldr r0, [sp, #0x14]
	mov r2, #1
	bl MOD05_021D9DC0
	cmp r0, #0
	bne _021DB008
	bl GF_AssertFail
_021DB008:
	ldr r0, [sp, #0x14]
	ldr r2, [r4, #0x4c]
	add r1, r5, #0
	bl MOD05_021DA080
	add r4, r0, #0
	bl MOD05_021DA118
	add r0, r4, #0
	mov r1, #0
	bl MOD05_021DA0DC
	add r0, r4, #0
	bl MOD05_021DA0E0
	add sp, #0x2c
	pop {r4, r5, pc}
	nop
_021DB02C: .word UNK05_021F64E4

	thumb_func_start MOD05_021DB030
MOD05_021DB030: ; 0x021DB030
	push {r3, lr}
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	mov r1, #0
	str r1, [r0]
	pop {r3, pc}

	thumb_func_start MOD05_021DB040
MOD05_021DB040: ; 0x021DB040
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl FUN_02046528
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #3
	bhi _021DB126
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DB066: ; jump table
	.short _021DB06E - _021DB066 - 2 ; case 0
	.short _021DB0CA - _021DB066 - 2 ; case 1
	.short _021DB0E8 - _021DB066 - 2 ; case 2
	.short _021DB106 - _021DB066 - 2 ; case 3
_021DB06E:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	cmp r0, #1
	bne _021DB08C
	add r0, r6, #0
	mov r1, #1
	bl FUN_0205889C
	mov r0, #1
	b _021DB096
_021DB08C:
	add r0, r6, #0
	mov r1, #0
	bl FUN_0205889C
	mov r0, #3
_021DB096:
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #8]
	strb r0, [r4, #4]
	ldr r0, [r5, #0x20]
	bl FUN_0201F008
	strh r0, [r4, #0xc]
	ldr r0, _021DB13C ; =0x0000FFA0
	ldr r1, [r5, #0x20]
	bl FUN_0201EF2C
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0xb
	str r0, [sp, #8]
	ldr r3, _021DB140 ; =0x00007FFF
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200E1D0
	mov r0, #1
	str r0, [r4, #8]
	b _021DB126
_021DB0CA:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r6, r0, #0
	mov r1, #0
	bl FUN_0205889C
	add r0, r6, #0
	mov r1, #0xd
	bl FUN_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DB126
_021DB0E8:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r6, r0, #0
	bl FUN_0205AE28
	cmp r0, #1
	bne _021DB126
	add r0, r6, #0
	bl FUN_0205AE50
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DB126
_021DB106:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DB126
	ldr r0, [r5, #0x20]
	bl FUN_0201F008
	ldrh r1, [r4, #0xc]
	cmp r1, r0
	bne _021DB126
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021DB126:
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021DB134
	ldr r0, [r5, #0x20]
	add r1, r4, #4
	bl MOD05_021DAA2C
_021DB134:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021DB13C: .word 0x0000FFA0
_021DB140: .word 0x00007FFF

	thumb_func_start MOD05_021DB144
MOD05_021DB144: ; 0x021DB144
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl FUN_02046528
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_0204652C
	add r5, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _021DB164
	cmp r0, #1
	beq _021DB1A0
	b _021DB1B4
_021DB164:
	ldr r0, [r4, #0x38]
	bl FUN_020553A0
	mov r1, #1
	bl FUN_0205889C
	mov r0, #0
	str r0, [r5, #8]
	strb r0, [r5, #4]
	ldr r0, _021DB1C8 ; =0x00000603
	bl FUN_020054C8
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0xb
	str r0, [sp, #8]
	mov r0, #0
	ldr r3, _021DB1CC ; =0x00007FFF
	add r1, r0, #0
	add r2, r0, #0
	bl FUN_0200E1D0
	mov r0, #1
	str r0, [r5, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DB1B4
_021DB1A0:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DB1B4
	add r0, r5, #0
	bl FreeToHeap
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021DB1B4:
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021DB1C2
	ldr r0, [r4, #0x20]
	add r1, r5, #4
	bl MOD05_021DA9E8
_021DB1C2:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0
_021DB1C8: .word 0x00000603
_021DB1CC: .word 0x00007FFF

	thumb_func_start MOD05_021DB1D0
MOD05_021DB1D0: ; 0x021DB1D0
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	bl FUN_02046528
	add r6, r0, #0
	add r0, r5, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021DB1F0
	cmp r0, #1
	beq _021DB222
	b _021DB236
_021DB1F0:
	mov r0, #0
	str r0, [r4, #8]
	strb r0, [r4, #4]
	ldr r0, _021DB24C ; =0x00000603
	bl FUN_020054C8
	mov r1, #0
	str r1, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	add r0, r5, #0
	mov r2, #0x10
	add r3, r1, #0
	bl FUN_0204C1B4
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DB236
_021DB222:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DB236
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x10
	mov r0, #1
	pop {r4, r5, r6, pc}
_021DB236:
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021DB244
	ldr r0, [r6, #0x20]
	add r1, r4, #4
	bl MOD05_021DA9E8
_021DB244:
	mov r0, #0
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_021DB24C: .word 0x00000603

	thumb_func_start MOD05_021DB250
MOD05_021DB250: ; 0x021DB250
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp, #0x10]
	bl FUN_02046528
	add r5, r0, #0
	ldr r0, [sp, #0x10]
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #3
	bhi _021DB368
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DB276: ; jump table
	.short _021DB27E - _021DB276 - 2 ; case 0
	.short _021DB30C - _021DB276 - 2 ; case 1
	.short _021DB32A - _021DB276 - 2 ; case 2
	.short _021DB348 - _021DB276 - 2 ; case 3
_021DB27E:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	cmp r7, #1
	bne _021DB2A0
	ldr r0, [sp, #0x14]
	mov r1, #1
	bl FUN_0205889C
	mov r0, #1
	b _021DB2AA
_021DB2A0:
	ldr r0, [sp, #0x14]
	mov r1, #0
	bl FUN_0205889C
	mov r0, #3
_021DB2AA:
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #8]
	strb r0, [r4, #4]
	ldr r0, [r5, #0x20]
	bl FUN_0201F008
	strh r0, [r4, #0xc]
	ldr r0, _021DB37C ; =0x0000FFA0
	ldr r1, [r5, #0x20]
	bl FUN_0201EF2C
	cmp r7, #3
	bhi _021DB2EA
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DB2D2: ; jump table
	.short _021DB2DA - _021DB2D2 - 2 ; case 0
	.short _021DB2DE - _021DB2D2 - 2 ; case 1
	.short _021DB2E2 - _021DB2D2 - 2 ; case 2
	.short _021DB2E6 - _021DB2D2 - 2 ; case 3
_021DB2DA:
	mov r6, #3
	b _021DB2EE
_021DB2DE:
	mov r6, #5
	b _021DB2EE
_021DB2E2:
	mov r6, #7
	b _021DB2EE
_021DB2E6:
	mov r6, #0x27
	b _021DB2EE
_021DB2EA:
	bl GF_AssertFail
_021DB2EE:
	mov r1, #0
	str r1, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	add r2, r6, #0
	bl FUN_0204C1B4
	mov r0, #1
	str r0, [r4, #8]
	b _021DB368
_021DB30C:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r6, r0, #0
	mov r1, #0
	bl FUN_0205889C
	add r0, r6, #0
	mov r1, #0xd
	bl FUN_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DB368
_021DB32A:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r6, r0, #0
	bl FUN_0205AE28
	cmp r0, #1
	bne _021DB368
	add r0, r6, #0
	bl FUN_0205AE50
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DB368
_021DB348:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DB368
	ldr r0, [r5, #0x20]
	bl FUN_0201F008
	ldrh r1, [r4, #0xc]
	cmp r1, r0
	bne _021DB368
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DB368:
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021DB376
	ldr r0, [r5, #0x20]
	add r1, r4, #4
	bl MOD05_021DAA2C
_021DB376:
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021DB37C: .word 0x0000FFA0

	thumb_func_start MOD05_021DB380
MOD05_021DB380: ; 0x021DB380
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	bl FUN_02046528
	add r5, r0, #0
	add r0, r7, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #3
	bhi _021DB446
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DB3A6: ; jump table
	.short _021DB3AE - _021DB3A6 - 2 ; case 0
	.short _021DB3F6 - _021DB3A6 - 2 ; case 1
	.short _021DB414 - _021DB3A6 - 2 ; case 2
	.short _021DB432 - _021DB3A6 - 2 ; case 3
_021DB3AE:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bne _021DB3D0
	add r0, r6, #0
	mov r1, #1
	bl FUN_0205889C
	mov r0, #1
	b _021DB3DA
_021DB3D0:
	add r0, r6, #0
	mov r1, #0
	bl FUN_0205889C
	mov r0, #3
_021DB3DA:
	str r0, [r4]
	mov r1, #0
	mov r2, #1
	str r1, [sp]
	mov r0, #6
	str r0, [sp, #4]
	str r2, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	add r0, r7, #0
	add r3, r2, #0
	bl FUN_0204C1B4
	b _021DB446
_021DB3F6:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0
	mov r1, #0
	bl FUN_0205889C
	add r0, r5, #0
	mov r1, #0xd
	bl FUN_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DB446
_021DB414:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_0205AE28
	cmp r0, #1
	bne _021DB446
	add r0, r5, #0
	bl FUN_0205AE50
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021DB446
_021DB432:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DB446
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DB446:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	.section .rodata

	.global UNK05_021F64E4
UNK05_021F64E4: ; 0x021F64E4
	.word 0x0000012F, 0x00000130

	.global UNK05_021F64EC
UNK05_021F64EC: ; 0x021F64EC
	.word 0x00000082, 0x00000083, 0x000001A9, 0x000001AA

	.global UNK05_021F64FC
UNK05_021F64FC: ; 0x021F64FC
	.word 0x00000082, 0x00000083, 0x000001A9, 0x000001AA

	.global UNK05_021F650C
UNK05_021F650C: ; 0x021F650C
	.word 0x00000042, 0x00000043, 0x00000044, 0x00000045
	.word 0x000000F6, 0x00000046, 0x000001AB, 0x000001C8
	.word 0x00000104, 0x00000138, 0x00000139, 0x000001B6
	.word 0x000001BC, 0x000001B9, 0x000001BA, 0x0000012A
	.word 0x000001E4, 0x00000080, 0x0000020F, 0x0000004B

	.global UNK05_021F655C
UNK05_021F655C: ; 0x021F655C
	.word 0x00000042, 0x00000043, 0x00000044, 0x00000045
	.word 0x000000F6, 0x00000046, 0x000001AB, 0x000001C8
	.word 0x00000104, 0x00000138, 0x00000139, 0x000001B6
	.word 0x000001BC, 0x000001B9, 0x000001BA, 0x0000012A
	.word 0x000001E4, 0x00000080, 0x0000020F, 0x0000004B

	.global UNK05_021F65AC
UNK05_021F65AC: ; 0x021F65AC
	.word 0x00000042, 0x00000043, 0x00000044, 0x00000045
	.word 0x000000F6, 0x00000046, 0x000001AB, 0x000001C8
	.word 0x00000104, 0x00000138, 0x00000139, 0x000001B6
	.word 0x000001BC, 0x000001B9, 0x000001BA, 0x0000012A
	.word 0x000001E4, 0x00000080, 0x0000020F, 0x0000004B
