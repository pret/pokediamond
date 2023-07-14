	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021D80E8
ov05_021D80E8: ; 0x021D80E8
	ldrh r2, [r0]
	mov r1, #1
	bic r2, r1
	strh r2, [r0]
	ldrh r2, [r0]
	mov r1, #2
	bic r2, r1
	strh r2, [r0]
	ldrh r2, [r0]
	mov r1, #4
	bic r2, r1
	strh r2, [r0]
	ldrh r2, [r0]
	mov r1, #8
	bic r2, r1
	strh r2, [r0]
	ldrh r2, [r0]
	mov r1, #0x10
	bic r2, r1
	strh r2, [r0]
	ldrh r2, [r0]
	mov r1, #0x20
	bic r2, r1
	strh r2, [r0]
	ldrh r2, [r0]
	mov r1, #0x40
	bic r2, r1
	strh r2, [r0]
	ldrh r2, [r0]
	mov r1, #0x80
	bic r2, r1
	strh r2, [r0]
	ldrh r2, [r0]
	ldr r1, _021D8154 ; =0xFFFFFEFF
	and r1, r2
	strh r1, [r0]
	ldrh r2, [r0]
	ldr r1, _021D8158 ; =0xFFFFFDFF
	and r1, r2
	strh r1, [r0]
	ldrh r2, [r0]
	ldr r1, _021D815C ; =0xFFFFFBFF
	and r1, r2
	strh r1, [r0]
	ldrh r2, [r0]
	ldr r1, _021D8160 ; =0xFFFFF7FF
	and r2, r1
	strh r2, [r0]
	mov r2, #0xff
	strb r2, [r0, #2]
	asr r1, r1, #0xc
	strb r1, [r0, #3]
	bx lr
	nop
_021D8154: .word 0xFFFFFEFF
_021D8158: .word 0xFFFFFDFF
_021D815C: .word 0xFFFFFBFF
_021D8160: .word 0xFFFFF7FF

	thumb_func_start ov05_021D8164
ov05_021D8164: ; 0x021D8164
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	add r4, r3, #0
	bl ov05_021D80E8
	ldr r0, [r7, #0x38]
	bl sub_02055378
	str r0, [sp, #4]
	ldr r0, [r7, #0x38]
	bl sub_02055370
	str r0, [sp]
	ldr r0, [r7, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r2, r0, #0
	ldr r0, [sp, #4]
	strh r6, [r5, #4]
	strh r4, [r5, #6]
	cmp r0, #3
	beq _021D819A
	cmp r0, #0
	bne _021D81F8
_021D819A:
	mov r0, #1
	lsl r0, r0, #0xa
	tst r0, r6
	beq _021D81AA
	ldrh r1, [r5]
	mov r0, #4
	orr r0, r1
	strh r0, [r5]
_021D81AA:
	mov r0, #2
	lsl r0, r0, #0xa
	tst r0, r6
	beq _021D81BA
	ldrh r1, [r5]
	mov r0, #8
	orr r0, r1
	strh r0, [r5]
_021D81BA:
	mov r3, #1
	add r0, r6, #0
	tst r0, r3
	beq _021D81CE
	ldrh r1, [r5]
	mov r0, #1
	bic r1, r0
	add r0, r1, #0
	orr r0, r3
	strh r0, [r5]
_021D81CE:
	mov r0, #2
	tst r0, r6
	beq _021D81DC
	ldrh r1, [r5]
	mov r0, #0x80
	orr r0, r1
	strh r0, [r5]
_021D81DC:
	mov r0, #0xf0
	add r3, r4, #0
	and r3, r0
	beq _021D81EC
	ldrh r1, [r5]
	mov r0, #0x10
	orr r0, r1
	strh r0, [r5]
_021D81EC:
	cmp r3, #0
	beq _021D81F8
	ldrh r1, [r5]
	mov r0, #0x20
	orr r0, r1
	strh r0, [r5]
_021D81F8:
	ldr r0, [sp, #4]
	cmp r0, #3
	bne _021D820C
	ldr r0, [sp]
	cmp r0, #1
	bne _021D820C
	ldrh r1, [r5]
	mov r0, #0x40
	orr r0, r1
	strh r0, [r5]
_021D820C:
	ldr r0, [sp, #4]
	cmp r0, #3
	bne _021D821A
	ldrh r1, [r5]
	mov r0, #2
	orr r0, r1
	strh r0, [r5]
_021D821A:
	cmp r2, #0
	bne _021D8224
	mov r0, #0x40
	tst r0, r4
	bne _021D8242
_021D8224:
	cmp r2, #1
	bne _021D822E
	mov r0, #0x80
	tst r0, r4
	bne _021D8242
_021D822E:
	cmp r2, #2
	bne _021D8238
	mov r0, #0x20
	tst r0, r4
	bne _021D8242
_021D8238:
	cmp r2, #3
	bne _021D8246
	mov r0, #0x10
	tst r0, r4
	beq _021D8246
_021D8242:
	strb r2, [r5, #3]
	b _021D824C
_021D8246:
	mov r0, #0
	mvn r0, r0
	strb r0, [r5, #3]
_021D824C:
	ldr r0, [r7, #0x38]
	add r1, r6, #0
	add r2, r4, #0
	bl sub_02057020
	strb r0, [r5, #2]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021D825C
ov05_021D825C: ; 0x021D825C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x38]
	bl sub_02055378
	add r6, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r1, [r0]
	ldr r0, _021D831C ; =0x00000156
	cmp r1, r0
	beq _021D827C
	add sp, #0x10
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D827C:
	ldr r0, [r4, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205ED3C
	cmp r0, #0
	bne _021D8290
	add sp, #0x10
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D8290:
	cmp r6, #0
	bne _021D82EC
	ldr r0, [r4, #0x38]
	bl sub_02055370
	ldrb r1, [r5, #2]
	lsl r2, r1, #0x18
	asr r3, r2, #0x18
	mov r2, #0
	mvn r2, r2
	cmp r3, r2
	beq _021D82CE
	cmp r0, #1
	bne _021D82CE
	add r0, r4, #0
	add r2, sp, #0xc
	add r3, sp, #8
	bl ov05_021D9130
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #8]
	add r0, r4, #0
	bl sub_0204A6E0
	bl sub_0205478C
	cmp r0, #0
	beq _021D8314
	add sp, #0x10
	mov r0, #1
	pop {r4, r5, r6, pc}
_021D82CE:
	mov r0, #3
	ldrsb r1, [r5, r0]
	sub r0, r0, #4
	cmp r1, r0
	beq _021D8314
	add r0, r4, #0
	bl ov05_021D9194
	bl sub_0205478C
	cmp r0, #0
	beq _021D8314
	add sp, #0x10
	mov r0, #1
	pop {r4, r5, r6, pc}
_021D82EC:
	cmp r6, #3
	bne _021D8314
	ldrb r1, [r5, #2]
	add r0, r4, #0
	add r2, sp, #4
	add r3, sp, #0
	bl ov05_021D9130
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r4, #0
	bl sub_0204A6E0
	bl sub_0205478C
	cmp r0, #0
	beq _021D8314
	add sp, #0x10
	mov r0, #1
	pop {r4, r5, r6, pc}
_021D8314:
	mov r0, #0
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_021D831C: .word 0x00000156

	thumb_func_start ov05_021D8320
ov05_021D8320: ; 0x021D8320
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldrh r0, [r5]
	add r4, r1, #0
	lsl r0, r0, #0x14
	lsr r0, r0, #0x1f
	bne _021D8342
	add r0, r4, #0
	mov r1, #1
	bl sub_0203989C
	cmp r0, #1
	bne _021D8342
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8342:
	ldrh r0, [r5]
	lsl r0, r0, #0x14
	lsr r0, r0, #0x1f
	bne _021D8384
	ldr r0, [r4, #0xc]
	bl SaveArray_PlayerParty_Get
	bl HasEnoughAlivePokemonForDoubleBattle
	add r6, r0, #0
	ldr r0, [r4, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205ED3C
	cmp r0, #1
	bne _021D8366
	mov r6, #1
_021D8366:
	add r0, r4, #0
	add r1, r6, #0
	bl sub_0205C598
	cmp r0, #1
	bne _021D8384
	ldr r0, [r4, #0x38]
	bl sub_02055B14
	ldr r0, [r4, #0x34]
	bl sub_02058780
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8384:
	ldrh r0, [r5]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	beq _021D83A6
	ldr r0, [r4, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205ED5C
	add r0, r4, #0
	bl ov05_021D8D24
	cmp r0, #1
	bne _021D83A6
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D83A6:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021D825C
	cmp r0, #0
	beq _021D83C2
	add r0, r4, #0
	mov r1, #4
	mov r2, #0
	bl sub_02038C78
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D83C2:
	ldrh r1, [r5, #4]
	ldrh r2, [r5, #6]
	ldr r0, [r4, #0x38]
	mov r6, #0
	bl sub_02057020
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	bl Save_VarsFlags_Get
	mov r1, #2
	bl sub_0205F264
	cmp r0, #0
	beq _021D83E4
	mov r0, #1
	orr r6, r0
_021D83E4:
	ldr r0, [r4, #0xc]
	bl SaveArray_PlayerParty_Get
	mov r1, #0x7f
	bl GetIdxOfFirstPartyMonWithMove
	cmp r0, #0xff
	beq _021D83F8
	mov r0, #2
	orr r6, r0
_021D83F8:
	ldr r1, [r4, #0x38]
	add r0, r4, #0
	add r2, r7, #0
	add r3, r6, #0
	bl ov05_021E61A4
	cmp r0, #1
	bne _021D840E
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D840E:
	ldrh r0, [r5]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	beq _021D8436
	add r0, r4, #0
	bl ov05_021D8954
	cmp r0, #0
	beq _021D8426
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8426:
	add r0, r4, #0
	bl ov05_021D859C
	cmp r0, #1
	bne _021D8436
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8436:
	ldrh r0, [r5]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	beq _021D845A
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetFacingDirection
	ldrb r1, [r5, #2]
	cmp r1, r0
	bne _021D845A
	add r0, r4, #0
	bl ov05_021D859C
	cmp r0, #1
	bne _021D845A
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D845A:
	ldrh r0, [r5]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _021D8532
	add r0, r4, #0
	add r1, sp, #4
	bl sub_02037090
	cmp r0, #1
	bne _021D84B8
	ldr r0, [r4, #0x38]
	bl sub_02055B30
	cmp r0, #1
	bne _021D8486
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r1, r0, #0
	ldr r0, [r4, #0x38]
	bl sub_02055B8C
_021D8486:
	ldr r0, [sp, #4]
	bl sub_02058488
	cmp r0, #9
	beq _021D84A8
	ldr r5, [sp, #4]
	add r0, r5, #0
	bl sub_02058498
	add r1, r0, #0
	lsl r1, r1, #0x10
	add r0, r4, #0
	lsr r1, r1, #0x10
	add r2, r5, #0
	bl sub_02038C78
	b _021D84B2
_021D84A8:
	ldr r2, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	bl sub_02038C78
_021D84B2:
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D84B8:
	add r0, r4, #0
	bl sub_02034AF0
	add r6, r0, #0
	add r0, r4, #0
	bl sub_02034AF8
	add r2, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl sub_020370BC
	add r1, r0, #0
	ldr r0, _021D8594 ; =0x0000FFFF
	cmp r1, r0
	beq _021D84EA
	lsl r1, r1, #0x10
	add r0, r4, #0
	lsr r1, r1, #0x10
	mov r2, #0
	bl sub_02038C78
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D84EA:
	add r0, r4, #0
	add r1, sp, #0
	bl ov05_021F4D2C
	cmp r0, #0
	beq _021D850A
	ldr r1, [sp]
	add r0, r4, #0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	mov r2, #0
	bl sub_02038C78
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D850A:
	add r0, r4, #0
	bl ov05_021D9194
	add r1, r0, #0
	add r0, r4, #0
	bl ov05_021D8BAC
	add r1, r0, #0
	ldr r0, _021D8594 ; =0x0000FFFF
	cmp r1, r0
	beq _021D8532
	lsl r1, r1, #0x10
	add r0, r4, #0
	lsr r1, r1, #0x10
	mov r2, #0
	bl sub_02038C78
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8532:
	ldrh r0, [r5]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	beq _021D8552
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021D89BC
	cmp r0, #1
	bne _021D8552
	add r0, r4, #0
	bl ov05_021D9290
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8552:
	ldrh r0, [r5]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _021D856A
	add r0, r4, #0
	bl sub_0205DB44
	cmp r0, #1
	bne _021D856A
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D856A:
	ldrh r0, [r5]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _021D858E
	add r0, r4, #0
	bl sub_02035068
	cmp r0, #1
	bne _021D858E
	ldr r0, _021D8598 ; =0x000005FD
	bl PlaySE
	add r0, r4, #0
	bl sub_02035080
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D858E:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021D8594: .word 0x0000FFFF
_021D8598: .word 0x000005FD

	thumb_func_start ov05_021D859C
ov05_021D859C: ; 0x021D859C
	push {r3, r4, r5, lr}
	add r1, sp, #0
	add r5, r0, #0
	bl sub_02037230
	cmp r0, #1
	bne _021D85C4
	ldr r4, [sp]
	add r0, r4, #0
	bl sub_02058498
	add r1, r0, #0
	lsl r1, r1, #0x10
	add r0, r5, #0
	lsr r1, r1, #0x10
	add r2, r4, #0
	bl sub_02038C78
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D85C4:
	add r0, r5, #0
	bl sub_02034AF0
	add r4, r0, #0
	add r0, r5, #0
	bl sub_02034AF8
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl sub_020371D0
	add r1, r0, #0
	ldr r0, _021D85F8 ; =0x0000FFFF
	cmp r1, r0
	beq _021D85F4
	lsl r1, r1, #0x10
	add r0, r5, #0
	lsr r1, r1, #0x10
	mov r2, #0
	bl sub_02038C78
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D85F4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021D85F8: .word 0x0000FFFF

	thumb_func_start ov05_021D85FC
ov05_021D85FC: ; 0x021D85FC
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4]
	lsl r0, r0, #0x14
	lsr r0, r0, #0x1f
	bne _021D8618
	add r0, r1, #0
	mov r1, #1
	bl sub_0203989C
	cmp r0, #1
	bne _021D8618
	mov r0, #1
	pop {r4, pc}
_021D8618:
	bl sub_02031438
	cmp r0, #0
	bne _021D862C
	bl sub_02031190
	bl sub_0204F6B4
	cmp r0, #0
	beq _021D8630
_021D862C:
	mov r0, #0
	pop {r4, pc}
_021D8630:
	bl ov18_0223DCB4
	ldrh r0, [r4]
	lsl r1, r0, #0x1f
	lsr r1, r1, #0x1f
	beq _021D8646
	mov r0, #0
	bl ov18_0223DCD0
	mov r0, #0
	pop {r4, pc}
_021D8646:
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _021D8654
	bl ov18_0223DC98
	mov r0, #0
	pop {r4, pc}
_021D8654:
	bl ov18_0223D8F4
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov05_021D865C
ov05_021D865C: ; 0x021D865C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrh r0, [r4]
	add r5, r1, #0
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	beq _021D868E
	mov r0, #3
	ldrsb r0, [r4, r0]
	cmp r0, #1
	bne _021D868E
	add r0, r5, #0
	bl ov05_021D9178
	bl sub_020547E0
	cmp r0, #0
	beq _021D868E
	ldr r1, _021D872C ; =0x0000238D
	add r0, r5, #0
	mov r2, #0
	bl sub_02038C78
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D868E:
	bl sub_02031438
	cmp r0, #0
	bne _021D86AA
	bl sub_02031190
	bl sub_0204F6B4
	cmp r0, #0
	bne _021D86AA
	bl sub_02050A68
	cmp r0, #0
	bne _021D86AE
_021D86AA:
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D86AE:
	ldrh r0, [r4]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _021D86FE
	add r0, r5, #0
	add r1, sp, #0
	bl sub_02037090
	cmp r0, #1
	bne _021D86FE
	ldr r0, [sp]
	bl sub_02058480
	cmp r0, #1
	beq _021D86FE
	ldr r0, [r5, #0x38]
	bl sub_02055B30
	cmp r0, #1
	bne _021D86E4
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r1, r0, #0
	ldr r0, [r5, #0x38]
	bl sub_02055B8C
_021D86E4:
	ldr r4, [sp]
	add r0, r4, #0
	bl sub_02058498
	add r1, r0, #0
	lsl r1, r1, #0x10
	add r0, r5, #0
	lsr r1, r1, #0x10
	add r2, r4, #0
	bl sub_02038C78
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D86FE:
	ldrh r0, [r4]
	lsl r1, r0, #0x1f
	lsr r1, r1, #0x1f
	beq _021D8710
	add r0, r5, #0
	bl sub_02052044
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8710:
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _021D8726
	ldr r0, _021D8730 ; =0x000005FD
	bl PlaySE
	add r0, r5, #0
	bl sub_0203515C
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8726:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D872C: .word 0x0000238D
_021D8730: .word 0x000005FD

	thumb_func_start ov05_021D8734
ov05_021D8734: ; 0x021D8734
	push {r3, r4, r5, lr}
	mov r5, #0
	mov r4, #1
_021D873A:
	add r0, r4, #0
	bl sub_0202DFA4
	cmp r0, #0
	beq _021D8746
	add r5, r5, #1
_021D8746:
	add r4, r4, #1
	cmp r4, #5
	blt _021D873A
	cmp r5, #1
	blt _021D8754
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8754:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021D8758
ov05_021D8758: ; 0x021D8758
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r5, r1, #0
	bl sub_0202CB8C
	mov r1, #0xfe
	tst r0, r1
	beq _021D878A
	bl ov05_021D8734
	cmp r0, #0
	beq _021D8786
	bl sub_02030F20
	cmp r0, #1
	ble _021D8786
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl sub_02038C78
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8786:
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D878A:
	ldrh r0, [r4]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _021D87D4
	add r0, r5, #0
	add r1, sp, #0
	bl sub_02037090
	cmp r0, #1
	bne _021D87D4
	ldr r0, [r5, #0x38]
	bl sub_02055B30
	cmp r0, #1
	bne _021D87B6
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r1, r0, #0
	ldr r0, [r5, #0x38]
	bl sub_02055B8C
_021D87B6:
	bl sub_02031C10
	ldr r4, [sp]
	add r0, r4, #0
	bl sub_02058498
	add r1, r0, #0
	lsl r1, r1, #0x10
	add r0, r5, #0
	lsr r1, r1, #0x10
	add r2, r4, #0
	bl sub_02038C78
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D87D4:
	ldrh r0, [r4]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	beq _021D87F4
	add r0, r5, #0
	bl ov05_021D9178
	bl sub_02054B60
	cmp r0, #0
	beq _021D87F4
	add r0, r5, #0
	bl sub_02049D9C
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D87F4:
	ldrh r0, [r4]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _021D8816
	ldr r0, _021D881C ; =0x000005FD
	bl PlaySE
	add r0, r5, #0
	bl sub_02035118
	mov r0, #4
	bl sub_02052B74
	bl sub_02031C2C
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8816:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D881C: .word 0x000005FD

	thumb_func_start ov05_021D8820
ov05_021D8820: ; 0x021D8820
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldrh r0, [r5]
	add r4, r1, #0
	lsl r0, r0, #0x14
	lsr r0, r0, #0x1f
	bne _021D8842
	add r0, r4, #0
	mov r1, #1
	bl sub_0203989C
	cmp r0, #1
	bne _021D8842
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D8842:
	ldrh r0, [r5]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _021D88FA
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02037090
	cmp r0, #1
	bne _021D88A0
	ldr r0, [r4, #0x38]
	bl sub_02055B30
	cmp r0, #1
	bne _021D886E
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r1, r0, #0
	ldr r0, [r4, #0x38]
	bl sub_02055B8C
_021D886E:
	ldr r0, [sp]
	bl sub_02058488
	cmp r0, #9
	beq _021D8890
	ldr r5, [sp]
	add r0, r5, #0
	bl sub_02058498
	add r1, r0, #0
	lsl r1, r1, #0x10
	add r0, r4, #0
	lsr r1, r1, #0x10
	add r2, r5, #0
	bl sub_02038C78
	b _021D889A
_021D8890:
	ldr r2, [sp]
	add r0, r4, #0
	mov r1, #0
	bl sub_02038C78
_021D889A:
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D88A0:
	add r0, r4, #0
	bl sub_02034AF0
	add r6, r0, #0
	add r0, r4, #0
	bl sub_02034AF8
	add r2, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl sub_020370BC
	add r1, r0, #0
	ldr r0, _021D894C ; =0x0000FFFF
	cmp r1, r0
	beq _021D88D2
	lsl r1, r1, #0x10
	add r0, r4, #0
	lsr r1, r1, #0x10
	mov r2, #0
	bl sub_02038C78
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D88D2:
	add r0, r4, #0
	bl ov05_021D9194
	add r1, r0, #0
	add r0, r4, #0
	bl ov05_021D8BAC
	add r1, r0, #0
	ldr r0, _021D894C ; =0x0000FFFF
	cmp r1, r0
	beq _021D88FA
	lsl r1, r1, #0x10
	add r0, r4, #0
	lsr r1, r1, #0x10
	mov r2, #0
	bl sub_02038C78
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D88FA:
	ldrh r0, [r5]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	beq _021D8914
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021D89BC
	cmp r0, #1
	bne _021D8914
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D8914:
	ldrh r0, [r5]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _021D892C
	add r0, r4, #0
	bl sub_0205DB44
	cmp r0, #1
	bne _021D892C
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D892C:
	ldrh r0, [r5]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _021D8946
	ldr r0, _021D8950 ; =0x000005FD
	bl PlaySE
	add r0, r4, #0
	bl sub_02035080
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D8946:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0
_021D894C: .word 0x0000FFFF
_021D8950: .word 0x000005FD

	thumb_func_start ov05_021D8954
ov05_021D8954: ; 0x021D8954
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r1, sp, #4
	add r2, sp, #0
	bl ov05_021D90F8
	ldr r0, [r4, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F244
	cmp r0, #1
	bne _021D8998
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r4, #0
	bl sub_0204BA68
	cmp r0, #1
	bne _021D8992
	add r0, r4, #0
	bl sub_0204BA90
	add r1, r0, #0
	add r0, r4, #0
	bl sub_02046F70
	add sp, #8
	mov r0, #1
	pop {r4, pc}
_021D8992:
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_021D8998:
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl MapHeader_HasWildEncounters
	cmp r0, #0
	beq _021D89B4
	add r0, r4, #0
	bl ov06_0223BA04
	cmp r0, #1
	bne _021D89B4
	add sp, #8
	mov r0, #1
	pop {r4, pc}
_021D89B4:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021D89BC
ov05_021D89BC: ; 0x021D89BC
	push {r4, r5, r6, lr}
	sub sp, #0x28
	add r5, r1, #0
	mov r1, #3
	ldrsb r2, [r5, r1]
	sub r1, r1, #4
	add r6, r0, #0
	cmp r2, r1
	bne _021D89D4
	add sp, #0x28
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D89D4:
	bl ov06_022426AC
	cmp r0, #0
	beq _021D89E2
	add sp, #0x28
	mov r0, #1
	pop {r4, r5, r6, pc}
_021D89E2:
	add r0, r6, #0
	add r1, sp, #0x10
	add r2, sp, #0xc
	bl ov05_021D9114
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	add r0, r6, #0
	bl sub_0204A6B4
	cmp r0, #0
	bne _021D8A00
	add sp, #0x28
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D8A00:
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	add r0, r6, #0
	add r3, sp, #0x14
	bl ov05_021D91B0
	cmp r0, #0
	beq _021D8A4A
	mov r0, #3
	ldrsb r1, [r5, r0]
	sub r0, r0, #4
	cmp r1, r0
	beq _021D8A4A
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	add r0, r6, #0
	bl sub_0204A6E0
	bl sub_020547B0
	cmp r0, #0
	beq _021D8A4A
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	ldrsb r0, [r5, r0]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x18]
	add r0, r6, #0
	bl sub_0204C260
	add sp, #0x28
	mov r0, #1
	pop {r4, r5, r6, pc}
_021D8A4A:
	add r0, r6, #0
	add r1, sp, #0x10
	add r2, sp, #0xc
	bl ov05_021D90F8
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	add r0, r6, #0
	bl sub_0204A6E0
	add r4, r0, #0
	bl sub_020547BC
	cmp r0, #0
	bne _021D8A72
	add r0, r4, #0
	bl sub_020547EC
	cmp r0, #0
	beq _021D8A80
_021D8A72:
	mov r0, #3
	ldrsb r0, [r5, r0]
	cmp r0, #3
	beq _021D8AF4
	add sp, #0x28
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D8A80:
	add r0, r4, #0
	bl sub_020547C8
	cmp r0, #0
	bne _021D8A94
	add r0, r4, #0
	bl sub_020547F8
	cmp r0, #0
	beq _021D8AA2
_021D8A94:
	mov r0, #3
	ldrsb r0, [r5, r0]
	cmp r0, #2
	beq _021D8AF4
	add sp, #0x28
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D8AA2:
	add r0, r4, #0
	bl sub_020547E0
	cmp r0, #0
	bne _021D8AB6
	add r0, r4, #0
	bl sub_02054810
	cmp r0, #0
	beq _021D8AC4
_021D8AB6:
	mov r0, #3
	ldrsb r0, [r5, r0]
	cmp r0, #1
	beq _021D8AF4
	add sp, #0x28
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D8AC4:
	add r0, r4, #0
	bl sub_020548D8
	cmp r0, #0
	beq _021D8ADC
	mov r0, #3
	ldrsb r0, [r5, r0]
	cmp r0, #3
	beq _021D8AF4
	add sp, #0x28
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D8ADC:
	add r0, r4, #0
	bl sub_020548E4
	cmp r0, #0
	beq _021D8AF4
	mov r0, #3
	ldrsb r0, [r5, r0]
	cmp r0, #2
	beq _021D8AF4
	add sp, #0x28
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D8AF4:
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	add r0, r6, #0
	add r3, sp, #0x14
	bl ov05_021D91B0
	cmp r0, #0
	bne _021D8B0A
	add sp, #0x28
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D8B0A:
	add r0, r4, #0
	bl sub_020547B0
	cmp r0, #0
	beq _021D8B18
	mov r1, #1
	b _021D8B90
_021D8B18:
	add r0, r4, #0
	bl sub_020548D8
	cmp r0, #0
	beq _021D8B26
	mov r1, #3
	b _021D8B90
_021D8B26:
	add r0, r4, #0
	bl sub_020548E4
	cmp r0, #0
	beq _021D8B34
	mov r1, #3
	b _021D8B90
_021D8B34:
	add r0, r4, #0
	bl sub_020547BC
	cmp r0, #0
	bne _021D8B70
	add r0, r4, #0
	bl sub_020547EC
	cmp r0, #0
	bne _021D8B70
	add r0, r4, #0
	bl sub_020547C8
	cmp r0, #0
	bne _021D8B70
	add r0, r4, #0
	bl sub_020547F8
	cmp r0, #0
	bne _021D8B70
	add r0, r4, #0
	bl sub_020547E0
	cmp r0, #0
	bne _021D8B70
	add r0, r4, #0
	bl sub_02054810
	cmp r0, #0
	beq _021D8B8A
_021D8B70:
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	ldrsb r0, [r5, r0]
	str r0, [sp, #4]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x18]
	add r0, r6, #0
	bl sub_0204C29C
	add sp, #0x28
	mov r0, #1
	pop {r4, r5, r6, pc}
_021D8B8A:
	add sp, #0x28
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D8B90:
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	ldrsb r0, [r5, r0]
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x18]
	add r0, r6, #0
	bl sub_0204C260
	mov r0, #1
	add sp, #0x28
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021D8BAC
ov05_021D8BAC: ; 0x021D8BAC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x38]
	add r4, r1, #0
	bl PlayerAvatar_GetFacingDirection
	add r6, r0, #0
	add r0, r4, #0
	bl sub_02054878
	cmp r0, #0
	beq _021D8BCC
	cmp r6, #0
	bne _021D8BCC
	ldr r0, _021D8CE4 ; =0x000007E2
	pop {r3, r4, r5, r6, r7, pc}
_021D8BCC:
	add r0, r4, #0
	bl sub_02054914
	cmp r0, #0
	beq _021D8BDA
	ldr r0, _021D8CE8 ; =0x000009C4
	pop {r3, r4, r5, r6, r7, pc}
_021D8BDA:
	add r0, r4, #0
	bl sub_02054920
	cmp r0, #0
	beq _021D8BE8
	ldr r0, _021D8CEC ; =0x000009C5
	pop {r3, r4, r5, r6, r7, pc}
_021D8BE8:
	add r0, r4, #0
	bl sub_0205492C
	cmp r0, #0
	beq _021D8BF6
	ldr r0, _021D8CF0 ; =0x000009C6
	pop {r3, r4, r5, r6, r7, pc}
_021D8BF6:
	add r0, r4, #0
	bl sub_02054938
	cmp r0, #0
	beq _021D8C04
	ldr r0, _021D8CF4 ; =0x000009C7
	pop {r3, r4, r5, r6, r7, pc}
_021D8C04:
	add r0, r4, #0
	bl sub_02054944
	cmp r0, #0
	beq _021D8C12
	ldr r0, _021D8CF8 ; =0x000009C8
	pop {r3, r4, r5, r6, r7, pc}
_021D8C12:
	add r0, r4, #0
	bl sub_02054950
	cmp r0, #0
	beq _021D8C20
	ldr r0, _021D8CFC ; =0x000009C9
	pop {r3, r4, r5, r6, r7, pc}
_021D8C20:
	add r0, r4, #0
	bl sub_0205495C
	cmp r0, #0
	beq _021D8C2E
	ldr r0, _021D8D00 ; =0x000009CA
	pop {r3, r4, r5, r6, r7, pc}
_021D8C2E:
	add r0, r4, #0
	bl sub_02054968
	cmp r0, #0
	beq _021D8C3C
	ldr r0, _021D8D04 ; =0x000009CB
	pop {r3, r4, r5, r6, r7, pc}
_021D8C3C:
	add r0, r4, #0
	bl sub_02054A48
	cmp r0, #0
	beq _021D8C4A
	ldr r0, _021D8D08 ; =0x00002716
	pop {r3, r4, r5, r6, r7, pc}
_021D8C4A:
	add r0, r4, #0
	bl sub_02054884
	cmp r0, #0
	beq _021D8C58
	ldr r0, _021D8D0C ; =0x000009CC
	pop {r3, r4, r5, r6, r7, pc}
_021D8C58:
	add r0, r4, #0
	bl sub_02054A54
	cmp r0, #0
	beq _021D8C66
	ldr r0, _021D8D10 ; =0x000007EE
	pop {r3, r4, r5, r6, r7, pc}
_021D8C66:
	add r0, r4, #0
	bl sub_02054B14
	cmp r0, #0
	beq _021D8C78
	cmp r6, #0
	bne _021D8C78
	ldr r0, _021D8D14 ; =0x00002774
	pop {r3, r4, r5, r6, r7, pc}
_021D8C78:
	add r0, r4, #0
	add r1, r6, #0
	bl ov05_021E69BC
	cmp r0, #0
	beq _021D8C88
	ldr r0, _021D8D18 ; =0x00002713
	pop {r3, r4, r5, r6, r7, pc}
_021D8C88:
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetState
	cmp r0, #2
	beq _021D8CE0
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetProfileAddr
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	add r7, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r2, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	bl sub_0204A6E0
	add r1, r0, #0
	ldr r0, [r5, #0x38]
	add r2, r4, #0
	bl ov05_021E643C
	cmp r0, #0
	beq _021D8CE0
	add r0, r6, #0
	mov r1, #4
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0
	beq _021D8CE0
	ldr r0, [r5, #0xc]
	bl SaveArray_PlayerParty_Get
	mov r1, #0x39
	bl GetIdxOfFirstPartyMonWithMove
	cmp r0, #0xff
	beq _021D8CE0
	ldr r0, _021D8D1C ; =0x00002714
	pop {r3, r4, r5, r6, r7, pc}
_021D8CE0:
	ldr r0, _021D8D20 ; =0x0000FFFF
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021D8CE4: .word 0x000007E2
_021D8CE8: .word 0x000009C4
_021D8CEC: .word 0x000009C5
_021D8CF0: .word 0x000009C6
_021D8CF4: .word 0x000009C7
_021D8CF8: .word 0x000009C8
_021D8CFC: .word 0x000009C9
_021D8D00: .word 0x000009CA
_021D8D04: .word 0x000009CB
_021D8D08: .word 0x00002716
_021D8D0C: .word 0x000009CC
_021D8D10: .word 0x000007EE
_021D8D14: .word 0x00002774
_021D8D18: .word 0x00002713
_021D8D1C: .word 0x00002714
_021D8D20: .word 0x0000FFFF

	thumb_func_start ov05_021D8D24
ov05_021D8D24: ; 0x021D8D24
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl ov06_02242404
	cmp r0, #0
	beq _021D8D34
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8D34:
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r2, r0, #0
	ldr r1, [r5, #0x38]
	add r0, r5, #0
	bl ov05_021E72FC
	cmp r0, #1
	bne _021D8D4C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8D4C:
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	add r4, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	bl sub_0204A6E0
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021D8E1C
	cmp r0, #1
	bne _021D8D76
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8D76:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	add r3, r6, #0
	bl ov05_021D8E54
	cmp r0, #1
	bne _021D8D90
	add r0, r5, #0
	bl ov05_021D9290
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8D90:
	ldr r0, [r5, #0x38]
	bl sub_020556B4
	cmp r0, #0
	beq _021D8D9E
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D8D9E:
	add r0, r5, #0
	mov r1, #5
	mov r2, #1
	bl ov05_021EFA9C
	add r0, r5, #0
	bl ov05_021D9010
	cmp r0, #1
	bne _021D8DB6
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8DB6:
	add r0, r5, #0
	bl ov05_021D9090
	cmp r0, #1
	bne _021D8DC4
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8DC4:
	add r0, r5, #0
	bl ov05_021D8F38
	cmp r0, #1
	bne _021D8DD2
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8DD2:
	add r0, r5, #0
	bl ov05_021D8F84
	cmp r0, #1
	bne _021D8DE0
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8DE0:
	add r0, r5, #0
	bl ov05_021D8F90
	cmp r0, #1
	bne _021D8DEE
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8DEE:
	add r0, r5, #0
	bl ov05_021D8F9C
	cmp r0, #1
	bne _021D8DFC
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8DFC:
	add r0, r5, #0
	bl ov05_021D8FA8
	cmp r0, #0
	beq _021D8E0C
	add r0, r5, #0
	bl ov05_021D8FD0
_021D8E0C:
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F56C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021D8E1C
ov05_021D8E1C: ; 0x021D8E1C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl sub_02034B5C
	add r5, r0, #0
	add r0, r4, #0
	bl sub_02034B54
	add r2, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl sub_02037264
	add r1, r0, #0
	ldr r0, _021D8E50 ; =0x0000FFFF
	cmp r1, r0
	beq _021D8E4A
	add r0, r4, #0
	mov r2, #0
	bl sub_02038C78
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8E4A:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D8E50: .word 0x0000FFFF

	thumb_func_start ov05_021D8E54
ov05_021D8E54: ; 0x021D8E54
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r3, #0
	add r3, sp, #0xc
	add r4, r0, #0
	bl ov05_021D91B0
	cmp r0, #0
	bne _021D8E6C
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D8E6C:
	add r0, r5, #0
	bl sub_020548C0
	cmp r0, #1
	bne _021D8EB0
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetFacingDirection
	cmp r0, #2
	bne _021D8E84
	mov r0, #3
	b _021D8E96
_021D8E84:
	cmp r0, #3
	bne _021D8E8C
	mov r0, #2
	b _021D8E96
_021D8E8C:
	bl GF_AssertFail
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D8E96:
	mov r3, #0
	str r3, [sp]
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	bl sub_0204C260
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8EB0:
	add r0, r5, #0
	bl sub_020548CC
	cmp r0, #1
	bne _021D8EEC
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetFacingDirection
	cmp r0, #2
	beq _021D8ED2
	cmp r0, #3
	beq _021D8ED2
	bl GF_AssertFail
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D8ED2:
	mov r3, #0
	str r3, [sp]
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	bl sub_0204C260
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8EEC:
	add r0, r5, #0
	bl sub_020547D4
	cmp r0, #0
	bne _021D8F00
	add r0, r5, #0
	bl sub_02054804
	cmp r0, #0
	beq _021D8F16
_021D8F00:
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	bl sub_0204C29C
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8F16:
	add r0, r5, #0
	bl sub_02054B60
	cmp r0, #0
	beq _021D8F30
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	bl sub_02049718
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8F30:
	mov r0, #0
	add sp, #0x20
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021D8F38
ov05_021D8F38: ; 0x021D8F38
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl SaveArray_PlayerParty_Get
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	bl Save_Daycare_Get
	add r1, r5, #0
	add r2, r4, #0
	bl ov05_021ED378
	cmp r0, #1
	bne _021D8F7A
	ldr r0, [r4, #0xc]
	bl Save_GameStats_Get
	add r5, r0, #0
	mov r1, #0xb
	bl GameStats_Inc
	add r0, r5, #0
	mov r1, #0xf
	bl GameStats_AddSpecial
	ldr r1, _021D8F80 ; =0x000007EF
	add r0, r4, #0
	mov r2, #0
	bl sub_02038C78
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8F7A:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D8F80: .word 0x000007EF

	thumb_func_start ov05_021D8F84
ov05_021D8F84: ; 0x021D8F84
	push {r3, lr}
	bl ov05_021E1654
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021D8F90
ov05_021D8F90: ; 0x021D8F90
	push {r3, lr}
	bl sub_0205E4A4
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021D8F9C
ov05_021D8F9C: ; 0x021D8F9C
	ldr r3, _021D8FA4 ; =ov06_0224C24C
	add r1, r0, #0
	ldr r0, [r1, #0xc]
	bx r3
	.balign 4, 0
_021D8FA4: .word ov06_0224C24C

	thumb_func_start ov05_021D8FA8
ov05_021D8FA8: ; 0x021D8FA8
	push {r3, r4, r5, lr}
	ldr r0, [r0, #0xc]
	mov r5, #0
	bl Save_VarsFlags_Get
	add r4, r0, #0
	bl sub_0205F780
	add r0, r0, #1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	cmp r1, #0x80
	blo _021D8FC6
	add r1, r5, #0
	mov r5, #1
_021D8FC6:
	add r0, r4, #0
	bl sub_0205F790
	add r0, r5, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021D8FD0
ov05_021D8FD0: ; 0x021D8FD0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl SaveArray_PlayerParty_Get
	add r6, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl MapHeader_GetMapSec
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r6, #0
	bl GetPartyCount
	add r7, r0, #0
	mov r4, #0
	cmp r7, #0
	ble _021D900C
_021D8FF6:
	add r0, r6, #0
	add r1, r4, #0
	bl GetPartyMonByIndex
	mov r1, #5
	add r2, r5, #0
	bl MonApplyFriendshipMod
	add r4, r4, #1
	cmp r4, r7
	blt _021D8FF6
_021D900C:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021D9010
ov05_021D9010: ; 0x021D9010
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl SaveArray_PlayerParty_Get
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	bl Save_LocalFieldData_Get
	bl sub_02034E2C
	ldrh r1, [r0]
	add r1, r1, #1
	strh r1, [r0]
	ldrh r2, [r0]
	mov r1, #3
	and r1, r2
	strh r1, [r0]
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D903E
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D903E:
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl MapHeader_GetMapSec
	add r1, r0, #0
	lsl r1, r1, #0x10
	add r0, r4, #0
	lsr r1, r1, #0x10
	bl ApplyPoisonStep
	cmp r0, #0
	beq _021D9060
	cmp r0, #1
	beq _021D9064
	cmp r0, #2
	beq _021D9070
	b _021D9086
_021D9060:
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D9064:
	ldr r0, [r5, #4]
	ldr r0, [r0, #0x20]
	bl ov05_021F4724
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D9070:
	ldr r0, [r5, #4]
	ldr r0, [r0, #0x20]
	bl ov05_021F4724
	ldr r1, _021D908C ; =0x000007D3
	add r0, r5, #0
	mov r2, #0
	bl sub_02038C78
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D9086:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D908C: .word 0x000007D3

	thumb_func_start ov05_021D9090
ov05_021D9090: ; 0x021D9090
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F214
	cmp r0, #0
	bne _021D90A6
	mov r0, #0
	pop {r4, pc}
_021D90A6:
	ldr r0, [r4, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetSafariBallsCounter
	ldrh r0, [r0]
	cmp r0, #0
	bne _021D90C4
	ldr r1, _021D90F0 ; =0x00002262
	add r0, r4, #0
	mov r2, #0
	bl sub_02038C78
	mov r0, #1
	pop {r4, pc}
_021D90C4:
	ldr r0, [r4, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetSafariStepsCounter
	ldrh r1, [r0]
	add r1, r1, #1
	strh r1, [r0]
	ldrh r1, [r0]
	mov r0, #0x7d
	lsl r0, r0, #2
	cmp r1, r0
	blo _021D90EC
	ldr r1, _021D90F4 ; =0x00002261
	add r0, r4, #0
	mov r2, #0
	bl sub_02038C78
	mov r0, #1
	pop {r4, pc}
_021D90EC:
	mov r0, #0
	pop {r4, pc}
	.balign 4, 0
_021D90F0: .word 0x00002262
_021D90F4: .word 0x00002261

	thumb_func_start ov05_021D90F8
ov05_021D90F8: ; 0x021D90F8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x38]
	add r4, r1, #0
	add r6, r2, #0
	bl GetPlayerXCoord
	str r0, [r4]
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	str r0, [r6]
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021D9114
ov05_021D9114: ; 0x021D9114
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x38]
	add r4, r1, #0
	add r6, r2, #0
	bl PlayerAvatar_GetFacingDirection
	add r1, r0, #0
	add r0, r5, #0
	add r2, r4, #0
	add r3, r6, #0
	bl ov05_021D9130
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021D9130
ov05_021D9130: ; 0x021D9130
	push {r4, r5, r6, lr}
	add r4, r2, #0
	add r5, r3, #0
	add r6, r1, #0
	add r1, r4, #0
	add r2, r5, #0
	bl ov05_021D90F8
	cmp r6, #3
	bhi _021D9176
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9150: ; jump table
	.short _021D9158 - _021D9150 - 2 ; case 0
	.short _021D9160 - _021D9150 - 2 ; case 1
	.short _021D9168 - _021D9150 - 2 ; case 2
	.short _021D9170 - _021D9150 - 2 ; case 3
_021D9158:
	ldr r0, [r5]
	sub r0, r0, #1
	str r0, [r5]
	pop {r4, r5, r6, pc}
_021D9160:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	pop {r4, r5, r6, pc}
_021D9168:
	ldr r0, [r4]
	sub r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021D9170:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021D9176:
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021D9178
ov05_021D9178: ; 0x021D9178
	push {r4, lr}
	sub sp, #8
	add r1, sp, #4
	add r2, sp, #0
	add r4, r0, #0
	bl ov05_021D90F8
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r4, #0
	bl sub_0204A6E0
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov05_021D9194
ov05_021D9194: ; 0x021D9194
	push {r4, lr}
	sub sp, #8
	add r1, sp, #4
	add r2, sp, #0
	add r4, r0, #0
	bl ov05_021D9114
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r4, #0
	bl sub_0204A6E0
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov05_021D91B0
ov05_021D91B0: ; 0x021D91B0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r7, r1, #0
	str r2, [sp]
	add r5, r3, #0
	bl sub_02034B18
	add r6, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	bne _021D91CC
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D91CC:
	add r0, r4, #0
	add r1, r6, #0
	bl sub_02034B00
	cmp r0, #0
	bne _021D91DC
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D91DC:
	ldrh r3, [r0, #6]
	mov r1, #1
	lsl r1, r1, #8
	cmp r3, r1
	bne _021D920C
	ldrh r1, [r0, #4]
	ldr r0, _021D9244 ; =0x00000FFF
	cmp r1, r0
	beq _021D91F2
	bl GF_AssertFail
_021D91F2:
	ldr r0, [r4, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetDynamicWarp
	add r2, r0, #0
	ldmia r2!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r2!, {r0, r1}
	stmia r5!, {r0, r1}
	ldr r0, [r2]
	str r0, [r5]
	b _021D921E
_021D920C:
	ldrh r2, [r0, #2]
	ldrh r1, [r0]
	ldrh r0, [r0, #4]
	str r0, [r5]
	str r3, [r5, #4]
	str r1, [r5, #8]
	str r2, [r5, #0xc]
	mov r0, #1
	str r0, [r5, #0x10]
_021D921E:
	ldr r0, [r4, #0xc]
	bl Save_LocalFieldData_Get
	bl sub_02034DC4
	add r5, r0, #0
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetFacingDirection
	ldr r1, [r4, #0x1c]
	ldr r1, [r1]
	str r1, [r5]
	str r6, [r5, #4]
	ldr r1, [sp]
	str r7, [r5, #8]
	str r1, [r5, #0xc]
	str r0, [r5, #0x10]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021D9244: .word 0x00000FFF

	thumb_func_start ov05_021D9248
ov05_021D9248: ; 0x021D9248
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	add r7, r1, #0
	str r2, [sp]
	add r4, r3, #0
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetSpecialSpawnWarpPtr
	add r6, r0, #0
	ldr r3, [r5, #0x1c]
	add r2, r6, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	cmp r4, #0
	str r0, [r2]
	str r4, [r6, #0x10]
	ldr r0, [sp]
	str r7, [r6, #8]
	str r0, [r6, #0xc]
	bne _021D9280
	ldr r0, [r6, #0xc]
	add r0, r0, #1
	str r0, [r6, #0xc]
_021D9280:
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	str r0, [r6]
	mov r0, #0
	mvn r0, r0
	str r0, [r6, #4]
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021D9290
ov05_021D9290: ; 0x021D9290
	push {r3, r4, lr}
	sub sp, #0x1c
	add r1, sp, #4
	add r2, sp, #0
	add r4, r0, #0
	bl ov05_021D90F8
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r4, #0
	add r3, sp, #8
	bl ov05_021D91B0
	cmp r0, #0
	beq _021D92DA
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl MapHeader_MapIsOnMainMatrix
	cmp r0, #1
	bne _021D931C
	ldr r0, [sp, #8]
	bl MapHeader_MapIsOnMainMatrix
	cmp r0, #0
	bne _021D931C
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r3, r0, #0
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r4, #0
	bl ov05_021D9248
	add sp, #0x1c
	pop {r3, r4, pc}
_021D92DA:
	add r0, r4, #0
	add r1, sp, #4
	add r2, sp, #0
	bl ov05_021D9114
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r4, #0
	add r3, sp, #8
	bl ov05_021D91B0
	cmp r0, #0
	beq _021D931C
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl MapHeader_MapIsOnMainMatrix
	cmp r0, #1
	bne _021D931C
	ldr r0, [sp, #8]
	bl MapHeader_MapIsOnMainMatrix
	cmp r0, #0
	bne _021D931C
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r3, r0, #0
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r4, #0
	bl ov05_021D9248
_021D931C:
	add sp, #0x1c
	pop {r3, r4, pc}
