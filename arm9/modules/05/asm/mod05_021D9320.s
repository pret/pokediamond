	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021D9320
MOD05_021D9320: ; 0x021D9320
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	str r1, [sp, #0x10]
	add r4, r3, #0
	add r0, r2, #0
	add r1, r5, #4
	add r2, r4, #0
	bl FUN_02008C9C
	str r0, [r5]
	ldr r1, _021D94B0 ; =0x00000162
	ldr r0, [sp, #0x10]
	strh r4, [r5, r1]
	ldr r0, [r0, #0x10]
	cmp r0, #0
	bne _021D9346
	mov r2, #4
	b _021D9348
_021D9346:
	mov r2, #6
_021D9348:
	sub r0, r1, #2
	strh r2, [r5, r0]
	bl FUN_0200965C
	mov r1, #0x16
	lsl r1, r1, #4
	ldrh r2, [r5, r1]
	add r3, r0, #0
	add r0, r4, #0
	add r1, r2, #0
	mul r1, r3
	bl AllocFromHeap
	add r7, r0, #0
	mov r0, #0
	str r0, [sp, #0x1c]
	mov r0, #0x16
	lsl r0, r0, #4
	ldrh r0, [r5, r0]
	cmp r0, #0
	bls _021D93AA
	ldr r6, [sp, #0x10]
_021D9374:
	ldr r1, [sp, #0x1c]
	add r0, r7, #0
	bl FUN_02009660
	str r0, [sp, #0x20]
	ldr r1, [r6]
	add r0, r4, #0
	bl FUN_020161A4
	ldr r1, [sp, #0x20]
	str r0, [sp, #0x24]
	add r2, r4, #0
	bl FUN_02009668
	ldr r0, [sp, #0x24]
	bl FreeToHeap
	ldr r0, [sp, #0x1c]
	add r6, r6, #4
	add r0, r0, #1
	str r0, [sp, #0x1c]
	mov r0, #0x16
	lsl r0, r0, #4
	ldrh r0, [r5, r0]
	ldr r1, [sp, #0x1c]
	cmp r1, r0
	blo _021D9374
_021D93AA:
	mov r6, #0
	cmp r0, #0
	bls _021D93E0
	str r5, [sp, #0x18]
_021D93B2:
	add r0, r7, #0
	add r1, r6, #0
	bl FUN_02009660
	bl FUN_020096CC
	add r1, r6, #0
	add r2, r4, #0
	bl FUN_02008DEC
	mov r1, #0x13
	ldr r2, [sp, #0x18]
	lsl r1, r1, #4
	str r0, [r2, r1]
	add r0, r2, #0
	add r0, r0, #4
	str r0, [sp, #0x18]
	add r0, r1, #0
	add r0, #0x30
	ldrh r0, [r5, r0]
	add r6, r6, #1
	cmp r6, r0
	blo _021D93B2
_021D93E0:
	mov r1, #0
	str r1, [sp, #0x14]
	cmp r0, #0
	bls _021D942C
	add r6, r5, #0
_021D93EA:
	ldr r1, [sp, #0x14]
	add r0, r7, #0
	bl FUN_02009660
	str r0, [sp, #0x28]
	bl FUN_020096CC
	add r1, r4, #0
	bl FUN_02009424
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r6, r1]
	add r0, r1, #0
	mov r2, #0x52
	sub r0, #0x18
	lsl r2, r2, #2
	ldr r0, [r6, r0]
	ldr r1, [sp, #0x28]
	ldr r2, [r6, r2]
	add r3, r4, #0
	bl FUN_020093A8
	ldr r0, [sp, #0x14]
	add r6, r6, #4
	add r0, r0, #1
	str r0, [sp, #0x14]
	mov r0, #0x16
	lsl r0, r0, #4
	ldrh r0, [r5, r0]
	ldr r1, [sp, #0x14]
	cmp r1, r0
	blo _021D93EA
_021D942C:
	mov r6, #0
	cmp r0, #0
	bls _021D944A
_021D9432:
	add r0, r7, #0
	add r1, r6, #0
	bl FUN_02009660
	bl FUN_020096B4
	mov r0, #0x16
	lsl r0, r0, #4
	ldrh r0, [r5, r0]
	add r6, r6, #1
	cmp r6, r0
	blo _021D9432
_021D944A:
	add r0, r7, #0
	bl FreeToHeap
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009B44
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009DAC
	ldr r1, [sp, #0x10]
	add r0, r4, #0
	ldr r1, [r1, #0x18]
	bl FUN_020161A4
	mov r3, #0x4e
	lsl r3, r3, #2
	ldr r1, [r5, r3]
	add r2, r3, #0
	str r1, [sp]
	add r1, r3, #4
	ldr r1, [r5, r1]
	sub r2, #8
	str r1, [sp, #4]
	add r1, r3, #0
	add r1, #8
	ldr r1, [r5, r1]
	add r6, r0, #0
	str r1, [sp, #8]
	add r1, r3, #0
	add r1, #0xc
	ldr r1, [r5, r1]
	sub r3, r3, #4
	str r1, [sp, #0xc]
	ldr r2, [r5, r2]
	ldr r3, [r5, r3]
	add r1, r4, #0
	bl FUN_02008BE0
	mov r1, #0x4b
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r6, #0
	bl FreeToHeap
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_021D94B0: .word 0x00000162

	thumb_func_start MOD05_021D94B4
MOD05_021D94B4: ; 0x021D94B4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	bl FUN_0201FD58
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02008C80
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009C30
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009E28
	mov r0, #0x16
	lsl r0, r0, #4
	ldrh r0, [r5, r0]
	mov r6, #0
	cmp r0, #0
	bls _021D950C
	mov r7, #0x16
	add r4, r5, #0
	lsl r7, r7, #4
_021D94EE:
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02009448
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02008E2C
	ldrh r0, [r5, r7]
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, r0
	blo _021D94EE
_021D950C:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021D9510
MOD05_021D9510: ; 0x021D9510
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	add r2, r0, #0
	add r4, r1, #0
	mov r0, #4
	ldrsh r0, [r4, r0]
	mov r3, #0x4b
	lsl r3, r3, #2
	lsl r0, r0, #0xc
	str r0, [sp]
	mov r0, #6
	ldrsh r0, [r4, r0]
	add r6, sp, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #8
	ldrsh r0, [r4, r0]
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r0, [r2]
	str r0, [sp, #0xc]
	ldr r0, [r2, r3]
	ldr r1, [r4]
	ldr r5, [r0]
	mov r0, #0x24
	mul r0, r1
	add r0, r5, r0
	str r0, [sp, #0x10]
	ldmia r6!, {r0, r1}
	add r5, sp, #0x14
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	ldr r6, _021D9598 ; =UNK05_021F64D8
	str r0, [r5]
	ldmia r6!, {r0, r1}
	add r5, sp, #0x20
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	mov r1, #0
	str r0, [r5]
	add r0, sp, #0
	strh r1, [r0, #0x2c]
	ldr r0, [r4, #0xc]
	add r3, #0x36
	str r0, [sp, #0x30]
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x34]
	ldrh r0, [r2, r3]
	str r0, [sp, #0x38]
	add r0, sp, #0xc
	bl FUN_0201FE94
	add r5, r0, #0
	bne _021D9580
	bl GF_AssertFail
_021D9580:
	ldrh r1, [r4, #0xa]
	add r0, r5, #0
	bl FUN_02020130
	ldr r1, [r4, #0x10]
	add r0, r5, #0
	bl FUN_0202027C
	add r0, r5, #0
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	nop
_021D9598: .word UNK05_021F64D8

	thumb_func_start MOD05_021D959C
MOD05_021D959C: ; 0x021D959C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	str r1, [sp]
	add r0, r2, #0
	str r3, [sp, #4]
	add r1, r7, #4
	add r2, r3, #0
	bl FUN_02008C9C
	str r0, [r7]
	ldr r1, _021D9678 ; =0x00000162
	ldr r0, [sp, #4]
	strh r0, [r7, r1]
	ldr r0, [sp]
	ldr r0, [r0, #0x10]
	cmp r0, #0
	beq _021D95C8
	ldr r0, [sp]
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _021D95DE
_021D95C8:
	mov r1, #0x16
	mov r0, #4
	lsl r1, r1, #4
	strh r0, [r7, r1]
	add r0, r1, #0
	mov r2, #0
	sub r0, #0x20
	str r2, [r7, r0]
	sub r1, #0x1c
	str r2, [r7, r1]
	b _021D95E4
_021D95DE:
	mov r2, #6
	sub r0, r1, #2
	strh r2, [r7, r0]
_021D95E4:
	mov r0, #0x16
	lsl r0, r0, #4
	ldrh r1, [r7, r0]
	mov r4, #0
	cmp r1, #0
	bls _021D9614
	ldr r5, [sp]
	add r6, r7, #0
_021D95F4:
	ldr r0, [r5]
	ldr r2, [sp, #4]
	add r1, r4, #0
	bl FUN_02008DEC
	mov r1, #0x13
	lsl r1, r1, #4
	str r0, [r6, r1]
	add r0, r1, #0
	add r0, #0x30
	ldrh r1, [r7, r0]
	add r4, r4, #1
	add r5, r5, #4
	add r6, r6, #4
	cmp r4, r1
	blo _021D95F4
_021D9614:
	mov r0, #0
	str r0, [sp, #8]
	cmp r1, #0
	bls _021D9672
	mov r6, #0x52
	add r5, r7, #0
	add r4, r0, #0
	lsl r6, r6, #2
_021D9624:
	ldr r0, [sp]
	ldr r0, [r0]
	cmp r0, #0
	beq _021D9658
	ldr r1, [sp, #4]
	bl FUN_02009424
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r3, [r5, r0]
	mov r1, #0
	ldr r0, [r3, #4]
	cmp r0, #0
	bls _021D9658
	add r2, r1, #0
_021D9648:
	ldr r0, [r3]
	add r1, r1, #1
	str r4, [r0, r2]
	ldr r3, [r5, r6]
	add r2, r2, #4
	ldr r0, [r3, #4]
	cmp r1, r0
	blo _021D9648
_021D9658:
	ldr r0, [sp]
	add r5, r5, #4
	add r0, r0, #4
	str r0, [sp]
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	mov r0, #0x16
	lsl r0, r0, #4
	ldrh r1, [r7, r0]
	ldr r0, [sp, #8]
	cmp r0, r1
	blo _021D9624
_021D9672:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_021D9678: .word 0x00000162

	thumb_func_start MOD05_021D967C
MOD05_021D967C: ; 0x021D967C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0x4d
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x30]
	add r6, r2, #0
	add r7, r3, #0
	bl FUN_0200945C
	cmp r0, #0
	bne _021D96A0
	bl GF_AssertFail
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_021D96A0:
	ldr r0, [sp, #0x30]
	add r2, r6, #0
	str r0, [sp]
	ldr r0, [sp, #0x2c]
	add r3, r7, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x28]
	str r0, [sp, #8]
	ldr r0, _021D96F0 ; =0x00000162
	ldrh r1, [r5, r0]
	sub r0, #0x2e
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_02008FEC
	add r4, r0, #0
	beq _021D96E8
	bl FUN_02009D68
	cmp r0, #1
	beq _021D96D0
	bl GF_AssertFail
_021D96D0:
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl MOD05_021D9780
	ldr r1, [sp, #0x2c]
	add r0, r4, #0
	bl FUN_02009E88
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_021D96E8:
	bl GF_AssertFail
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021D96F0: .word 0x00000162

	thumb_func_start MOD05_021D96F4
MOD05_021D96F4: ; 0x021D96F4
	push {r4, lr}
	sub sp, #8
	mov r4, #2
	str r4, [sp]
	ldr r4, [sp, #0x10]
	str r4, [sp, #4]
	bl MOD05_021D97B4
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD05_021D9708
MOD05_021D9708: ; 0x021D9708
	push {r4, lr}
	sub sp, #8
	mov r4, #3
	str r4, [sp]
	ldr r4, [sp, #0x10]
	str r4, [sp, #4]
	bl MOD05_021D97B4
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD05_021D971C
MOD05_021D971C: ; 0x021D971C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0x13
	lsl r0, r0, #4
	add r4, r1, #0
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x24]
	add r6, r2, #0
	add r7, r3, #0
	bl FUN_0200945C
	cmp r0, #0
	bne _021D9740
	bl GF_AssertFail
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_021D9740:
	ldr r0, [sp, #0x24]
	add r2, r6, #0
	str r0, [sp]
	ldr r0, [sp, #0x20]
	add r3, r7, #0
	str r0, [sp, #4]
	ldr r0, _021D977C ; =0x00000162
	ldrh r1, [r5, r0]
	sub r0, #0x32
	str r1, [sp, #8]
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_02008F34
	add r4, r0, #0
	beq _021D9774
	bl FUN_02009B04
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl MOD05_021D9780
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_021D9774:
	bl GF_AssertFail
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021D977C: .word 0x00000162

	thumb_func_start MOD05_021D9780
MOD05_021D9780: ; 0x021D9780
	push {r3, r4, r5, r6}
	ldr r6, [r0, #4]
	mov r3, #0
	cmp r6, #0
	ble _021D97AC
	ldr r5, [r0]
	add r4, r5, #0
_021D978E:
	ldr r2, [r4]
	cmp r2, #0
	bne _021D97A4
	lsl r2, r3, #2
	str r1, [r5, r2]
	ldr r1, [r0, #8]
	add r1, r1, #1
	str r1, [r0, #8]
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
_021D97A4:
	add r3, r3, #1
	add r4, r4, #4
	cmp r3, r6
	blt _021D978E
_021D97AC:
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021D97B4
MOD05_021D97B4: ; 0x021D97B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [sp, #0x28]
	add r7, r1, #0
	lsl r4, r0, #2
	mov r0, #0x13
	lsl r0, r0, #4
	add r6, r5, r0
	ldr r0, [r6, r4]
	ldr r1, [sp, #0x2c]
	str r2, [sp, #0xc]
	str r3, [sp, #0x10]
	bl FUN_0200945C
	cmp r0, #0
	bne _021D97DE
	bl GF_AssertFail
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021D97DE:
	ldr r0, [sp, #0x2c]
	ldr r2, [sp, #0xc]
	str r0, [sp]
	ldr r0, [sp, #0x28]
	ldr r3, [sp, #0x10]
	str r0, [sp, #4]
	ldr r0, _021D981C ; =0x00000162
	add r1, r7, #0
	ldrh r0, [r5, r0]
	str r0, [sp, #8]
	ldr r0, [r6, r4]
	bl FUN_020090AC
	add r1, r0, #0
	beq _021D9814
	mov r0, #0x52
	add r2, r5, r4
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	bl MOD05_021D9780
	cmp r0, #1
	beq _021D9818
	bl GF_AssertFail
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021D9814:
	bl GF_AssertFail
_021D9818:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021D981C: .word 0x00000162

	thumb_func_start MOD05_021D9820
MOD05_021D9820: ; 0x021D9820
	push {r3, r4, r5, r6, lr}
	sub sp, #0x74
	add r5, r0, #0
	ldr r0, _021D99F4 ; =0x00000162
	add r4, r1, #0
	ldrh r0, [r5, r0]
	mov r1, #0x10
	bl AllocFromHeap
	add r6, r0, #0
	ldr r0, _021D99F4 ; =0x00000162
	mov r1, #8
	ldrh r0, [r5, r0]
	bl AllocFromHeap
	str r0, [r6, #8]
	ldr r0, _021D99F4 ; =0x00000162
	mov r1, #0x24
	ldrh r0, [r5, r0]
	bl AllocFromHeap
	ldr r1, [r6, #8]
	add r2, r4, #0
	str r0, [r1]
	ldr r0, [r6, #8]
	mov r1, #0
	ldr r0, [r0]
	add r3, sp, #0x2c
	str r0, [r6, #4]
_021D985A:
	ldr r0, [r2, #0x14]
	add r1, r1, #1
	add r2, r2, #4
	stmia r3!, {r0}
	cmp r1, #6
	blt _021D985A
	mov r1, #5
	lsl r1, r1, #6
	ldr r0, [r5, r1]
	cmp r0, #0
	beq _021D9878
	add r1, r1, #4
	ldr r1, [r5, r1]
	cmp r1, #0
	bne _021D9882
_021D9878:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x3c]
	str r0, [sp, #0x40]
	b _021D98B8
_021D9882:
	mov r2, #0
	ldr r1, [sp, #0x3c]
	mvn r2, r2
	cmp r1, r2
	beq _021D989A
	bl FUN_0200945C
	cmp r0, #0
	bne _021D989A
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x3c]
_021D989A:
	mov r0, #0
	ldr r1, [sp, #0x40]
	mvn r0, r0
	cmp r1, r0
	beq _021D98B8
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0200945C
	cmp r0, #0
	bne _021D98B8
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x40]
_021D98B8:
	ldr r0, [sp, #0x38]
	str r0, [sp]
	ldr r0, [sp, #0x3c]
	str r0, [sp, #4]
	ldr r0, [sp, #0x40]
	str r0, [sp, #8]
	ldr r0, [r4, #0x30]
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x2c]
	str r0, [sp, #0x10]
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r1, [r5, r0]
	str r1, [sp, #0x14]
	add r1, r0, #4
	ldr r1, [r5, r1]
	str r1, [sp, #0x18]
	add r1, r0, #0
	add r1, #8
	ldr r1, [r5, r1]
	str r1, [sp, #0x1c]
	add r1, r0, #0
	add r1, #0xc
	ldr r1, [r5, r1]
	str r1, [sp, #0x20]
	add r1, r0, #0
	add r1, #0x10
	ldr r1, [r5, r1]
	add r0, #0x14
	str r1, [sp, #0x24]
	ldr r0, [r5, r0]
	str r0, [sp, #0x28]
	ldr r0, [r6, #4]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x30]
	ldr r3, [sp, #0x34]
	bl FUN_02008AA4
	ldr r0, [r5]
	str r0, [sp, #0x44]
	ldr r0, [r6, #4]
	str r0, [sp, #0x48]
	mov r0, #0
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _021D9926
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D9934
_021D9926:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D9934:
	bl _ffix
	str r0, [sp, #0x4c]
	mov r0, #2
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _021D9954
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D9962
_021D9954:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D9962:
	bl _ffix
	str r0, [sp, #0x50]
	mov r0, #4
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _021D9982
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D9990
_021D9982:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D9990:
	bl _ffix
	str r0, [sp, #0x54]
	ldr r0, [r4, #0x10]
	cmp r0, #2
	bne _021D99A6
	mov r0, #3
	ldr r1, [sp, #0x50]
	lsl r0, r0, #0x12
	add r0, r1, r0
	str r0, [sp, #0x50]
_021D99A6:
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #0x58]
	str r0, [sp, #0x5c]
	str r0, [sp, #0x60]
	mov r1, #0
	add r0, sp, #0x2c
	strh r1, [r0, #0x38]
	ldr r0, [r4, #8]
	str r0, [sp, #0x68]
	ldr r0, [r4, #0x10]
	str r0, [sp, #0x6c]
	ldr r0, _021D99F4 ; =0x00000162
	ldrh r0, [r5, r0]
	str r0, [sp, #0x70]
	add r0, sp, #0x44
	bl FUN_0201FE94
	str r0, [r6]
	cmp r0, #0
	beq _021D99EA
	bl FUN_020202A0
	add r5, r0, #0
	ldrh r1, [r4, #6]
	ldr r0, [r6]
	bl FUN_02020130
	ldr r1, [r4, #0xc]
	ldr r0, [r6]
	add r1, r5, r1
	bl FUN_02020248
	b _021D99EE
_021D99EA:
	bl GF_AssertFail
_021D99EE:
	add r0, r6, #0
	add sp, #0x74
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0
_021D99F4: .word 0x00000162

	thumb_func_start MOD05_021D99F8
MOD05_021D99F8: ; 0x021D99F8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6]
	bl FUN_0201FD58
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009C30
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009E28
	mov r0, #0x16
	lsl r0, r0, #4
	ldrh r0, [r6, r0]
	mov r4, #0
	cmp r0, #0
	bls _021D9A46
	mov r7, #0x16
	add r5, r6, #0
	lsl r7, r7, #4
_021D9A28:
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009448
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02008E2C
	ldrh r0, [r6, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blo _021D9A28
_021D9A46:
	pop {r3, r4, r5, r6, r7, pc}

	.section .rodata

	.global UNK05_021F64D8
UNK05_021F64D8: ; 0x021F64D8
	.word 0x00001000, 0x00001000, 0x00001000
