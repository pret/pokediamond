    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_VSNPrintf
OS_VSNPrintf: ; 0x020CA49C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x64
	mov r9, r2
	str r1, [sp, #0x54]
	str r0, [sp, #0x5c]
	str r0, [sp, #0x58]
	ldrsb r0, [r9, #0x0]
	str r1, [sp, #0x0]
	mov r11, r3
	cmp r0, #0x0
	beq _020CAD18
	mov r0, #0xa
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x20
	str r0, [sp, #0x1c]
	mov r0, #0x30
	str r0, [sp, #0x20]
	mvn r0, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x57
	str r0, [sp, #0x10]
	mov r0, #0x8
	str r0, [sp, #0x14]
	mov r0, #0x37
	str r0, [sp, #0x18]
	mov r0, #0x10
	str r0, [sp, #0x24]
	mov r0, #0x1
	str r0, [sp, #0x28]
	mov r0, #0x2b
	str r0, [sp, #0x34]
	mov r0, #0x2d
	str r0, [sp, #0x30]
	mov r0, #0x2
	str r0, [sp, #0x2c]
_020CA530:
	ldrsb r1, [r9, #0x0]
	and r0, r1, #0xff
	eor r0, r0, #0x20
	sub r0, r0, #0xa1
	cmp r0, #0x3c
	bhs _020CA56C
	add r0, sp, #0x54
	bl string_put_char
	ldrsb r1, [r9, #0x1]!
	cmp r1, #0x0
	beq _020CAD0C
	add r0, sp, #0x54
	add r9, r9, #0x1
	bl string_put_char
	b _020CAD0C
_020CA56C:
	cmp r1, #0x25
	beq _020CA584
	add r0, sp, #0x54
	add r9, r9, #0x1
	bl string_put_char
	b _020CAD0C
_020CA584:
	ldr r6, [sp, #0x4]
	ldr r5, [sp, #0x8]
	ldr r2, [sp, #0xc]
	ldr r0, [sp, #0x10]
	mov r10, r6
	mov r3, r9
_020CA59C:
	ldrsb r4, [r9, #0x1]!
	cmp r4, #0x20
	bgt _020CA5B4
	cmp r4, #0x20
	beq _020CA5F4
	b _020CA60C
_020CA5B4:
	cmp r4, #0x30
	bgt _020CA60C
	cmp r4, #0x2b
	blt _020CA60C
	cmp r4, #0x2b
	beq _020CA5E0
	cmp r4, #0x2d
	beq _020CA5FC
	cmp r4, #0x30
	beq _020CA604
	b _020CA60C
_020CA5E0:
	ldrsb r1, [r9, #-0x1]
	cmp r1, #0x20
	bne _020CA60C
	orr r6, r6, #0x2
	b _020CA59C
_020CA5F4:
	orr r6, r6, #0x1
	b _020CA59C
_020CA5FC:
	orr r6, r6, #0x8
	b _020CA59C
_020CA604:
	orr r6, r6, #0x10
	b _020CA59C
_020CA60C:
	cmp r4, #0x2a
	bne _020CA640
	add r11, r11, #0x4
	ldr r10, [r11, #-0x4]
	add r9, r9, #0x1
	cmp r10, #0x0
	rsblt r10, r10, #0x0
	orrlt r6, r6, #0x8
	b _020CA654
_020CA630:
	ldrsb r4, [r9], #0x1
	mov r1, #0xa
	mla r1, r10, r1, r4
	sub r10, r1, #0x30
_020CA640:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x30
	blt _020CA654
	cmp r1, #0x39
	ble _020CA630
_020CA654:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x2e
	bne _020CA6AC
	ldrsb r1, [r9, #0x1]!
	ldr r5, [sp, #0x4]
	cmp r1, #0x2a
	bne _020CA698
	add r11, r11, #0x4
	ldr r5, [r11, #-0x4]
	add r9, r9, #0x1
	cmp r5, #0x0
	ldrlt r5, [sp, #0x8]
	b _020CA6AC
_020CA688:
	ldrsb r4, [r9], #0x1
	mov r1, #0xa
	mla r1, r5, r1, r4
	sub r5, r1, #0x30
_020CA698:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x30
	blt _020CA6AC
	cmp r1, #0x39
	ble _020CA688
_020CA6AC:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x68
	beq _020CA6C4
	cmp r1, #0x6c
	beq _020CA6DC
	b _020CA6F0
_020CA6C4:
	ldrsb r1, [r9, #0x1]!
	cmp r1, #0x68
	orrne r6, r6, #0x40
	addeq r9, r9, #0x1
	orreq r6, r6, #0x100
	b _020CA6F0
_020CA6DC:
	ldrsb r1, [r9, #0x1]!
	cmp r1, #0x6c
	orrne r6, r6, #0x20
	addeq r9, r9, #0x1
	orreq r6, r6, #0x80
_020CA6F0:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x69
	bgt _020CA740
	cmp r1, #0x63
	blt _020CA720
	cmp r1, #0x63
	beq _020CA7B4
	cmp r1, #0x64
	beq _020CA96C
	cmp r1, #0x69
	beq _020CA96C
	b _020CA950
_020CA720:
	cmp r1, #0x25
	bgt _020CA734
	cmp r1, #0x25
	beq _020CA934
	b _020CA950
_020CA734:
	cmp r1, #0x58
	beq _020CA7A0
	b _020CA950
_020CA740:
	cmp r1, #0x6e
	bgt _020CA754
	cmp r1, #0x6e
	beq _020CA8DC
	b _020CA950
_020CA754:
	sub r1, r1, #0x6f
	cmp r1, #0x9
	addls pc, pc, r1, lsl #0x2
	b _020CA950
_020CA764:
	b _020CA78C
	b _020CA7A8
	b _020CA950
	b _020CA950
	b _020CA828
	b _020CA950
	b _020CA798
	b _020CA950
	b _020CA950
	b _020CA964
_020CA78C:
	ldr r2, [sp, #0x14]
	orr r6, r6, #0x1000
	b _020CA96C
_020CA798:
	orr r6, r6, #0x1000
	b _020CA96C
_020CA7A0:
	ldr r0, [sp, #0x18]
	b _020CA964
_020CA7A8:
	orr r6, r6, #0x4
	ldr r5, [sp, #0x14]
	b _020CA964
_020CA7B4:
	cmp r5, #0x0
	bge _020CA950
	ands r0, r6, #0x8
	add r11, r11, #0x4
	ldr r4, [r11, #-0x4]
	beq _020CA7F0
	mov r0, r4, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_put_char
	ldr r1, [sp, #0x1c]
	sub r2, r10, #0x1
	add r0, sp, #0x54
	bl string_fill_char
	b _020CA820
_020CA7F0:
	ands r0, r6, #0x10
	ldrne r0, [sp, #0x20]
	sub r2, r10, #0x1
	ldreq r0, [sp, #0x1c]
	mov r0, r0, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_fill_char
	mov r0, r4, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_put_char
_020CA820:
	add r9, r9, #0x1
	b _020CAD0C
_020CA828:
	add fp, fp, #0x4
	cmp r5, #0x0
	ldr r7, [sp, #0x4]
	ldr r4, [fp, #-0x4]
	bge _020CA860
	ldrsb r0, [r4]
	cmp r0, #0x0
	beq _020CA874
_020CA848:
	add r7, r7, #0x1
	ldrsb r0, [r4, r7]
	cmp r0, #0x0
	bne _020CA848
	b _020CA874
_020CA85C:
	add r7, r7, #0x1
_020CA860:
	cmp r7, r5
	bge _020CA874
	ldrsb r0, [r4, r7]
	cmp r0, #0x0
	bne _020CA85C
_020CA874:
	ands r0, r6, #0x8
	sub sl, sl, r7
	beq _020CA8A4
	mov r1, r4
	mov r2, r7
	add r0, sp, #0x54
	bl string_put_string
	ldr r1, [sp, #0x1C]
	mov r2, sl
	add r0, sp, #0x54
	bl string_fill_char
	b _020CA8D4
_020CA8A4:
	ands r0, r6, #0x10
	ldrne r0, [sp, #0x20]
	mov r2, sl
	ldreq r0, [sp, #0x1C]
	mov r0, r0, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_fill_char
	mov r1, r4
	mov r2, r7
	add r0, sp, #0x54
	bl string_put_string
_020CA8D4:
	add r9, r9, #0x1
	b _020CAD0C
_020CA8DC:
	ands r0, r6, #0x100
	ldr r1, [sp, #0x58]
	ldr r0, [sp, #0x5c]
	sub r2, r1, r0
	bne _020CA92C
	ands r0, r6, #0x40
	addne r11, r11, #0x4
	ldrne r0, [r11, #-0x4]
	strneh r2, [r0, #0x0]
	bne _020CA92C
	ands r0, r6, #0x80
	addeq r11, r11, #0x4
	ldreq r0, [r11, #-0x4]
	streq r2, [r0, #0x0]
	beq _020CA92C
	add r11, r11, #0x4
	ldr r0, [r11, #-0x4]
	mov r1, r2, asr #0x1f
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
_020CA92C:
	add r9, r9, #0x1
	b _020CAD0C
_020CA934:
	add r0, r3, #0x1
	cmp r0, r9
	bne _020CA950
	add r0, sp, #0x54
	add r9, r9, #0x1
	bl string_put_char
	b _020CAD0C
_020CA950:
	add r0, sp, #0x54
	mov r1, r3
	sub r2, r9, r3
	bl string_put_string
	b _020CAD0C
_020CA964:
	ldr r2, [sp, #0x24]
	orr r6, r6, #0x1000
_020CA96C:
	ands r1, r6, #0x8
	bicne r6, r6, #0x10
	cmp r5, #0x0
	bicge r6, r6, #0x10
	ldrlt r5, [sp, #0x28]
	ldr r7, [sp, #0x4]
	ands r1, r6, #0x1000
	beq _020CAA20
	ands r1, r6, #0x100
	addne r11, r11, #0x4
	ldrneb r4, [r11, #-0x4]
	movne r1, #0x0
	bne _020CA9D0
	ands r1, r6, #0x40
	addne r11, r11, #0x4
	ldrneh r4, [r11, #-0x4]
	movne r1, #0x0
	bne _020CA9D0
	ands r1, r6, #0x80
	addne r11, r11, #0x8
	ldrne r1, [r11, #-0x4]
	ldrne r4, [r11, #-0x8]
	addeq r11, r11, #0x4
	ldreq r4, [r11, #-0x4]
	moveq r1, #0x0
_020CA9D0:
	bic r6, r6, #0x3
	ands r3, r6, #0x4
	beq _020CAAD8
	cmp r2, #0x10
	bne _020CAA0C
	mov r3, #0x0
	cmp r1, r3
	cmpeq r4, r3
	beq _020CAAD8
	ldr r3, [sp, #0x20]
	ldr r7, [sp, #0x2c]
	strb r3, [sp, #0x39]
	add r3, r0, #0x21
	strb r3, [sp, #0x38]
	b _020CAAD8
_020CAA0C:
	cmp r2, #0x8
	ldreq r3, [sp, #0x20]
	ldreq r7, [sp, #0x28]
	streqb r3, [sp, #0x38]
	b _020CAAD8
_020CAA20:
	ands r1, r6, #0x100
	addne r11, r11, #0x4
	ldrnesb r4, [r11, #-0x4]
	movne r1, r4, asr #0x1f
	bne _020CAA64
	ands r1, r6, #0x40
	addne r11, r11, #0x4
	ldrnesh r4, [r11, #-0x4]
	movne r1, r4, asr #0x1f
	bne _020CAA64
	ands r1, r6, #0x80
	addne r11, r11, #0x8
	ldrne r4, [r11, #-0x8]
	ldrne r1, [r11, #-0x4]
	addeq r11, r11, #0x4
	ldreq r4, [r11, #-0x4]
	moveq r1, r4, asr #0x1f
_020CAA64:
	mov r3, #0x0
	and r8, r3, #0x0
	cmp r8, r3
	and r8, r1, #0x80000000
	cmpeq r8, r3
	beq _020CAAA0
	ldr r7, [sp, #0x30]
	mvn r4, r4
	strb r7, [sp, #0x38]
	mvn r7, r1
	mov r1, #0x1
	adds r4, r4, r1
	adc r1, r7, r3
	ldr r7, [sp, #0x28]
	b _020CAAD8
_020CAAA0:
	cmp r1, r3
	cmpeq r4, r3
	bne _020CAAB4
	cmp r5, #0x0
	beq _020CAAD8
_020CAAB4:
	ands r3, r6, #0x2
	ldrne r3, [sp, #0x34]
	ldrne r7, [sp, #0x28]
	strneb r3, [sp, #0x38]
	bne _020CAAD8
	ands r3, r6, #0x1
	ldrne r3, [sp, #0x1c]
	ldrne r7, [sp, #0x28]
	strneb r3, [sp, #0x38]
_020CAAD8:
	cmp r2, #0x8
	ldr r8, [sp, #0x4]
	beq _020CAAF8
	cmp r2, #0xa
	beq _020CAB40
	cmp r2, #0x10
	beq _020CABDC
	b _020CAC28
_020CAAF8:
	mov r0, #0x0
	cmp r1, r0
	cmpeq r4, r0
	beq _020CAC28
_020CAB08:
	and r0, r4, #0x7
	add r3, r0, #0x30
	add r0, sp, #0x3a
	strb r3, [r0, r8]
	mov r4, r4, lsr #0x3
	mov r2, #0x0
	mov r0, r1, lsr #0x3
	orr r4, r4, r1, lsl #0x1d
	cmp r0, r2
	cmpeq r4, r2
	mov r1, r0
	add r8, r8, #0x1
	bne _020CAB08
	b _020CAC28
_020CAB40:
	mov r0, #0x0
	cmp r0, r0
	cmpeq r1, r0
	bne _020CAB8C
	cmp r4, #0x0
	beq _020CAC28
_020CAB58:
	ldr r0, _020CAD60 ; =0xCCCCCCCD
	umull r1, r0, r4, r0
	movs r0, r0, lsr #0x3
	mov r1, #0xa
	mul r1, r0, r1
	sub r1, r4, r1
	mov r4, r0
	add r1, r1, #0x30
	add r0, sp, #0x3a
	strb r1, [r0, r8]
	add r8, r8, #0x1
	bne _020CAB58
	b _020CAC28
_020CAB8C:
	cmp r1, r0
	cmpeq r4, r0
	beq _020CAC28
_020CAB98:
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x4]
	mov r0, r4
	bl _ll_udiv
	mov r3, #0xa
	umull r3, r12, r0, r3
	subs r3, r4, r3
	mov r2, #0x0
	add r4, r3, #0x30
	add r3, sp, #0x3a
	strb r4, [r3, r8]
	cmp r1, r2
	cmpeq r0, r2
	mov r4, r0
	add r8, r8, #0x1
	bne _020CAB98
	b _020CAC28
_020CABDC:
	mov r2, #0x0
	cmp r1, r2
	cmpeq r4, r2
	beq _020CAC28
_020CABEC:
	and r3, r4, #0xf
	cmp r3, #0xa
	mov r4, r4, lsr #0x4
	addlt r3, r3, #0x30
	mov r2, r1, lsr #0x4
	orr r4, r4, r1, lsl #0x1c
	mov r1, r2
	addge r3, r3, r0
	add r2, sp, #0x3a
	strb r3, [r2, r8]
	mov r2, #0x0
	cmp r1, r2
	add r8, r8, #0x1
	cmpeq r4, r2
	bne _020CABEC
_020CAC28:
	cmp r7, #0x0
	ble _020CAC4C
	ldrsb r0, [sp, #0x38]
	cmp r0, #0x30
	ldreq r1, [sp, #0x20]
	addeq r0, sp, #0x3a
	streqb r1, [r0, r8]
	ldreq r7, [sp, #0x4]
	addeq r8, r8, #0x1
_020CAC4C:
	sub r5, r5, r8
	ands r0, r6, #0x10
	beq _020CAC68
	sub r0, r10, r8
	sub r0, r0, r7
	cmp r5, r0
	movlt r5, r0
_020CAC68:
	cmp r5, #0x0
	subgt r10, r10, r5
	add r0, r7, r8
	ands r6, r6, #0x8
	sub r10, r10, r0
	bne _020CAC90
	ldr r1, [sp, #0x1c]
	add r0, sp, #0x54
	mov r2, r10
	bl string_fill_char
_020CAC90:
	cmp r7, #0x0
	ble _020CACB8
	add r0, sp, #0x38
	add r4, r0, r7
_020CACA0:
	ldrsb r1, [r4, #-0x1]!
	sub r7, r7, #0x1
	add r0, sp, #0x54
	bl string_put_char
_020CACB0:
	cmp r7, #0x0
	bgt _020CACA0
_020CACB8:
	ldr r1, [sp, #0x20]
	mov r2, r5
	add r0, sp, #0x54
	bl string_fill_char
_020CACC8:
	cmp r8, #0x0
	ble _020CACF0
	add r0, sp, #0x3A
	add r4, r0, r8
_020CACD8:
	ldrsb r1, [r4, #-0x1]!
	sub r8, r8, #0x1
	add r0, sp, #0x54
	bl string_put_char
	cmp r8, #0x0
	bgt _020CACD8
_020CACF0:
	cmp r6, #0x0
	beq _020CAD08
	ldr r1, [sp, #0x1C]
	mov r2, sl
	add r0, sp, #0x54
	bl string_fill_char
_020CAD08:
	add r9, r9, #0x1
_020CAD0C:
	ldrsb r0, [r9, #0x0]
	cmp r0, #0x0
	bne _020CA530
_020CAD18:
	ldr r0, [sp, #0x54]
	cmp r0, #0x0
	ldrne r0, [sp, #0x58]
	movne r1, #0x0
	strneb r1, [r0, #0x0]
	bne _020CAD48
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	ldrne r1, [sp, #0x5c]
	movne r2, #0x0
	addne r0, r1, r0
	strneb r2, [r0, #-0x1]
_020CAD48:
	ldr r1, [sp, #0x58]
	ldr r0, [sp, #0x5c]
	sub r0, r1, r0
	add sp, sp, #0x64
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020CAD60: .word 0xCCCCCCCD

	arm_func_start OS_SNPrintf
OS_SNPrintf: ; 0x020CAD64
	stmdb sp!, {r0-r3}
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	add r3, sp, #0x10
	bic r3, r3, #0x3
	ldr r2, [sp, #0x10]
	add r3, r3, #0x4
	bl OS_VSNPrintf
	add sp, sp, #0x4
	ldmia sp!, {lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start OS_VSPrintf
OS_VSPrintf: ; 0x020CAD94
	ldr ip, _020CADA8 ; =OS_VSNPrintf
	mov r3, r2
	mov r2, r1
	mvn r1, #0x80000000
	bx r12
	.balign 4
_020CADA8: .word OS_VSNPrintf

	arm_func_start OS_SPrintf
OS_SPrintf: ; 0x020CADAC
	stmdb sp!, {r0-r3}
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	add r2, sp, #0xc
	bic r2, r2, #0x3
	ldr r1, [sp, #0xc]
	add r2, r2, #0x4
	bl OS_VSPrintf
	add sp, sp, #0x4
	ldmia sp!, {lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start string_put_string
string_put_string: ; 0x020CADDC
	stmdb sp!, {r4,lr}
	cmp r2, #0x0
	ldmleia sp!, {r4,lr}
	bxle lr
	ldr lr, [r0, #0x0]
	mov r4, #0x0
	cmp lr, r2
	movhi lr, r2
	cmp lr, #0x0
	bls _020CAE1C
_020CAE04:
	ldrsb r12, [r1, r4]
	ldr r3, [r0, #0x4]
	strb r12, [r3, r4]
	add r4, r4, #0x1
	cmp r4, lr
	blo _020CAE04
_020CAE1C:
	ldr r1, [r0, #0x0]
	sub r1, r1, lr
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, r2
	str r1, [r0, #0x4]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start string_fill_char
string_fill_char:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	addle sp, sp, #0x4
	ldmleia sp!, {lr}
	bxle lr
	ldr r12, [r0, #0x0]
	mov lr, #0x0
	cmp r12, r2
	movhi r12, r2
	cmp r12, #0x0
	bls _020CAE80
_020CAE6C:
	ldr r3, [r0, #0x4]
	strb r1, [r3, lr]
	add lr, lr, #0x1
	cmp lr, r12
	blo _020CAE6C
_020CAE80:
	ldr r1, [r0, #0x0]
	sub r1, r1, r12
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, r2
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start string_put_char
string_put_char:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	ldrne r2, [r0, #0x4]
	strneb r1, [r2, #0x0]
	ldrne r1, [r0, #0x0]
	subne r1, r1, #0x1
	strne r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x1
	str r1, [r0, #0x4]
	bx lr
