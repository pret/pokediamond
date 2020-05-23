    .include "asm/macros.inc"
    .include "global.inc"

	.extern gUnknown21C48B8
	.extern UNK_020F96DC

	.section .rodata

	.global UNK_020F7E6C
UNK_020F7E6C: ; 0x020F7E6C
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x55, 0x03

	.global UNK_020F7E74
UNK_020F7E74: ; 0x020F7E74
	.byte 0x03, 0x01, 0x01, 0x0E, 0x08, 0x0D, 0x95, 0x02

	.global UNK_020F7E7C
UNK_020F7E7C: ; 0x020F7E7C
	.byte 0x03, 0x13, 0x01, 0x0C, 0x10, 0x0D, 0x95, 0x02

	.global UNK_020F7E84
UNK_020F7E84: ; 0x020F7E84
	.byte 0x03, 0x01, 0x01, 0x09, 0x02, 0x0D, 0x83, 0x02

	.global UNK_020F7E8C
UNK_020F7E8C: ; 0x020F7E8C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x07, 0x00, 0x02, 0x0A, 0x01, 0x10, 0x2F, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F7EAC
UNK_020F7EAC: ; 0x020F7EAC
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_020653EC
FUN_020653EC: ; 0x020653EC
	push {r4-r6, lr}
	mov r2, #0x5
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0x3
	mov r1, #0x2b
	lsl r2, r2, #0xc
	bl FUN_0201681C
	mov r1, #0x6e
	mov r0, #0x2b
	lsl r1, r1, #0x2
	bl FUN_02016998
	mov r2, #0x6e
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r5, #0x0
	str r6, [r4, #0x4]
	bl FUN_020377AC
	mov r1, #0x5b
	lsl r1, r1, #0x2
	str r5, [r4, r1]
	mov r1, #0x2b
	str r1, [r4, #0x0]
	mov r1, #0x0
	strb r1, [r4, #0x19]
	mov r1, #0xff
	add r6, r0, #0x0
	strb r1, [r4, #0x1a]
	bl LoadPlayerDataAddress
	bl FUN_02024FF4
	strb r0, [r4, #0x16]
	add r0, r6, #0x0
	bl LoadPlayerDataAddress
	bl FUN_02025084
	strh r0, [r4, #0x14]
	add r0, r4, #0x0
	ldr r2, [r4, #0x0]
	add r0, #0x1c
	mov r1, #0x14
	bl FUN_02066010
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_02066070
	add r0, r4, #0x0
	bl FUN_02066270
	ldr r0, _02065470 ; =FUN_020654B0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_0200CA44
	str r0, [r4, #0x8]
	pop {r4-r6, pc}
	.balign 4
_02065470: .word FUN_020654B0

	thumb_func_start FUN_02065474
FUN_02065474: ; 0x02065474
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x8]
	bl FUN_0200CAB4
	ldr r0, [r4, #0x4]
	mov r1, #0x1
	str r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_020662E4
	add r0, r4, #0x0
	add r0, #0x1c
	mov r1, #0x14
	bl FUN_02066044
	add r0, r4, #0x0
	bl FUN_02016A18
	ldr r0, [r4, #0x0]
	bl FUN_020168D0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020654A4
FUN_020654A4: ; 0x020654A4
	ldr r3, _020654AC ; =FUN_02065474
	add r0, r1, #0x0
	bx r3
	nop
_020654AC: .word FUN_02065474

	thumb_func_start FUN_020654B0
FUN_020654B0: ; 0x020654B0
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02066334
	add r0, r4, #0x0
	bl FUN_02065AF4
	ldr r1, _020654CC ; =FUN_020654D0
	add r0, r5, #0x0
	bl FUN_0201B6C4
	pop {r3-r5, pc}
	.balign 4
_020654CC: .word FUN_020654D0

	thumb_func_start FUN_020654D0
FUN_020654D0: ; 0x020654D0
	push {r3-r5, lr}
	mov r0, #0x16
	add r5, r1, #0x0
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	bl FUN_02001204
	add r4, r0, #0x0
	mov r0, #0x69
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	cmp r0, #0x0
	beq _020654EE
	bl FUN_0205EC18
_020654EE:
	ldr r0, _02065544 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x2
	tst r0, r1
	beq _0206550A
	ldr r1, _02065548 ; =FUN_02065658
	ldr r2, _0206554C ; =FUN_020654A4
	add r0, r5, #0x0
	bl FUN_02065FE4
	ldr r0, _02065550 ; =0x000005DC
	bl FUN_020054C8
	pop {r3-r5, pc}
_0206550A:
	mov r0, #0x1
	tst r0, r1
	beq _02065542
	ldr r0, _02065550 ; =0x000005DC
	bl FUN_020054C8
	mov r1, #0x1
	mvn r1, r1
	cmp r4, r1
	beq _0206552A
	add r0, r1, #0x1
	cmp r4, r0
	beq _0206552A
	lsr r0, r1, #0x10
	cmp r4, r0
	bne _02065536
_0206552A:
	ldr r1, _02065548 ; =FUN_02065658
	ldr r2, _0206554C ; =FUN_020654A4
	add r0, r5, #0x0
	bl FUN_02065FE4
	pop {r3-r5, pc}
_02065536:
	ldr r1, _02065548 ; =FUN_02065658
	ldr r2, _02065554 ; =FUN_02065558
	add r0, r5, #0x0
	strb r4, [r5, #0x18]
	bl FUN_02065FE4
_02065542:
	pop {r3-r5, pc}
	.balign 4
_02065544: .word gUnknown21C48B8
_02065548: .word FUN_02065658
_0206554C: .word FUN_020654A4
_02065550: .word 0x000005DC
_02065554: .word FUN_02065558

	thumb_func_start FUN_02065558
FUN_02065558: ; 0x02065558
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldrh r0, [r4, #0x10]
	cmp r0, #0x0
	beq _0206556A
	cmp r0, #0x1
	beq _02065592
	pop {r3-r5, pc}
_0206556A:
	add r0, r4, #0x0
	bl FUN_02066334
	mov r1, #0x0
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl FUN_02065DD8
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r1, #0x0
	ldrb r2, [r4, #0x16]
	add r0, r4, #0x0
	add r3, r1, #0x0
	bl FUN_02066404
	ldrh r0, [r4, #0x10]
	add r0, r0, #0x1
	strh r0, [r4, #0x10]
	pop {r3-r5, pc}
_02065592:
	add r0, r4, #0x0
	bl FUN_020664F4
	cmp r0, #0x0
	beq _020655A8
	ldr r1, _020655AC ; =FUN_020655B0
	add r0, r5, #0x0
	bl FUN_0201B6C4
	mov r0, #0x0
	strh r0, [r4, #0x10]
_020655A8:
	pop {r3-r5, pc}
	nop
_020655AC: .word FUN_020655B0

	thumb_func_start FUN_020655B0
FUN_020655B0: ; 0x020655B0
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r0, #0x16
	add r4, r1, #0x0
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_02001204
	add r5, r0, #0x0
	ldr r0, _02065638 ; =gUnknown21C48B8
	mov r1, #0x2
	ldr r0, [r0, #0x48]
	tst r1, r0
	beq _020655DE
	ldr r1, _0206563C ; =FUN_02065674
	ldr r2, _02065640 ; =FUN_020654B0
	add r0, r4, #0x0
	bl FUN_02065FE4
	ldr r0, _02065644 ; =0x000005DC
	bl FUN_020054C8
	pop {r4-r6, pc}
_020655DE:
	mov r1, #0x1
	tst r0, r1
	beq _02065634
	ldr r0, _02065644 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0x2
	cmp r0, #0x5
	bhi _0206562C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020655FC: ; jump table (using 16-bit offset)
	.short _02065608 - _020655FC - 2; case 0
	.short _02065608 - _020655FC - 2; case 1
	.short _0206562C - _020655FC - 2; case 2
	.short _02065614 - _020655FC - 2; case 3
	.short _02065620 - _020655FC - 2; case 4
	.short _02065608 - _020655FC - 2; case 5
_02065608:
	ldr r1, _0206563C ; =FUN_02065674
	ldr r2, _02065640 ; =FUN_020654B0
	add r0, r4, #0x0
	bl FUN_02065FE4
	pop {r4-r6, pc}
_02065614:
	ldr r1, _02065648 ; =FUN_02065710
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_02065FE4
	pop {r4-r6, pc}
_02065620:
	ldr r1, _0206564C ; =FUN_02065894
	ldr r2, _02065650 ; =FUN_02065938
	add r0, r4, #0x0
	bl FUN_02065FE4
	pop {r4-r6, pc}
_0206562C:
	ldr r1, _02065654 ; =FUN_02065690
	add r0, r6, #0x0
	bl FUN_0201B6C4
_02065634:
	pop {r4-r6, pc}
	nop
_02065638: .word gUnknown21C48B8
_0206563C: .word FUN_02065674
_02065640: .word FUN_020654B0
_02065644: .word 0x000005DC
_02065648: .word FUN_02065710
_0206564C: .word FUN_02065894
_02065650: .word FUN_02065938
_02065654: .word FUN_02065690

	thumb_func_start FUN_02065658
FUN_02065658: ; 0x02065658
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02065EF8
	add r0, r4, #0x0
	bl FUN_020663D4
	ldr r1, [r4, #0xc]
	add r0, r5, #0x0
	bl FUN_0201B6C4
	pop {r3-r5, pc}

	thumb_func_start FUN_02065674
FUN_02065674: ; 0x02065674
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02065F8C
	add r0, r4, #0x0
	bl FUN_020663D4
	ldr r1, [r4, #0xc]
	add r0, r5, #0x0
	bl FUN_0201B6C4
	pop {r3-r5, pc}

	thumb_func_start FUN_02065690
FUN_02065690: ; 0x02065690
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldrh r0, [r4, #0x10]
	cmp r0, #0x3
	bhi _02065704
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020656A8: ; jump table (using 16-bit offset)
	.short _020656B0 - _020656A8 - 2; case 0
	.short _020656C6 - _020656A8 - 2; case 1
	.short _020656D2 - _020656A8 - 2; case 2
	.short _020656DE - _020656A8 - 2; case 3
_020656B0:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02066578
	cmp r0, #0x0
	beq _0206570A
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02066634
	b _02065704
_020656C6:
	add r0, r4, #0x0
	bl FUN_02066728
	cmp r0, #0x0
	bne _02065704
	pop {r3-r5, pc}
_020656D2:
	add r0, r4, #0x0
	bl FUN_020665C0
	cmp r0, #0x0
	bne _02065704
	pop {r3-r5, pc}
_020656DE:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02066578
	cmp r0, #0x0
	beq _0206570A
	add r0, r4, #0x0
	bl FUN_02066334
	add r0, r4, #0x0
	bl FUN_02065AF4
	mov r0, #0x0
	strh r0, [r4, #0x10]
	ldr r1, _0206570C ; =FUN_020654D0
	add r0, r5, #0x0
	bl FUN_0201B6C4
	pop {r3-r5, pc}
_02065704:
	ldrh r0, [r4, #0x10]
	add r0, r0, #0x1
	strh r0, [r4, #0x10]
_0206570A:
	pop {r3-r5, pc}
	.balign 4
_0206570C: .word FUN_020654D0

	thumb_func_start FUN_02065710
FUN_02065710: ; 0x02065710
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r1, #0x0
	ldrh r0, [r4, #0x10]
	cmp r0, #0x5
	bhi _020657DA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02065728: ; jump table (using 16-bit offset)
	.short _02065734 - _02065728 - 2; case 0
	.short _02065744 - _02065728 - 2; case 1
	.short _02065756 - _02065728 - 2; case 2
	.short _02065780 - _02065728 - 2; case 3
	.short _02065798 - _02065728 - 2; case 4
	.short _020657AA - _02065728 - 2; case 5
_02065734:
	mov r1, #0x1
	str r1, [sp, #0x0]
	ldrb r2, [r4, #0x16]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02066404
	b _020657DA
_02065744:
	add r0, r4, #0x0
	bl FUN_020664F4
	cmp r0, #0x0
	beq _020657E0
	add r0, r4, #0x0
	bl FUN_02066520
	b _020657DA
_02065756:
	add r0, r4, #0x0
	bl FUN_0206654C
	cmp r0, #0x0
	blt _020657E0
	beq _02065778
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldrb r2, [r4, #0x16]
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02066404
	mov r0, #0x4
	add sp, #0x4
	strh r0, [r4, #0x10]
	pop {r3-r4, pc}
_02065778:
	mov r0, #0x3
	add sp, #0x4
	strh r0, [r4, #0x10]
	pop {r3-r4, pc}
_02065780:
	add r0, r4, #0x0
	bl FUN_020664D8
	ldr r1, _020657E4 ; =FUN_02065674
	ldr r2, _020657E8 ; =FUN_020654B0
	add r0, r4, #0x0
	bl FUN_02065FE4
	mov r0, #0x0
	add sp, #0x4
	strh r0, [r4, #0x10]
	pop {r3-r4, pc}
_02065798:
	add r0, r4, #0x0
	bl FUN_020664F4
	cmp r0, #0x0
	beq _020657E0
	add r0, r4, #0x0
	bl FUN_02066520
	b _020657DA
_020657AA:
	add r0, r4, #0x0
	bl FUN_0206654C
	cmp r0, #0x0
	blt _020657E0
	beq _020657C2
	ldr r1, _020657EC ; =FUN_020659B8
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_02065FE4
	b _020657CC
_020657C2:
	ldr r1, _020657F0 ; =FUN_020657F4
	ldr r2, _020657E4 ; =FUN_02065674
	add r0, r4, #0x0
	bl FUN_02065FE4
_020657CC:
	add r0, r4, #0x0
	bl FUN_020664D8
	mov r0, #0x0
	add sp, #0x4
	strh r0, [r4, #0x10]
	pop {r3-r4, pc}
_020657DA:
	ldrh r0, [r4, #0x10]
	add r0, r0, #0x1
	strh r0, [r4, #0x10]
_020657E0:
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_020657E4: .word FUN_02065674
_020657E8: .word FUN_020654B0
_020657EC: .word FUN_020659B8
_020657F0: .word FUN_020657F4

	thumb_func_start FUN_020657F4
FUN_020657F4: ; 0x020657F4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r1, #0x0
	ldrh r0, [r4, #0x10]
	cmp r0, #0x0
	beq _0206580A
	cmp r0, #0x1
	beq _0206584E
	cmp r0, #0x2
	beq _0206585C
	b _0206587E
_0206580A:
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	bne _02065820
	add r0, r4, #0x0
	bl FUN_02066334
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x1
	bl FUN_02065DD8
_02065820:
	add r0, r4, #0x0
	bl FUN_020661A0
	cmp r0, #0x0
	beq _0206583C
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldrb r2, [r4, #0x16]
	add r0, r4, #0x0
	mov r1, #0x3
	mov r3, #0x0
	bl FUN_02066404
	b _0206587E
_0206583C:
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldrb r2, [r4, #0x16]
	add r0, r4, #0x0
	mov r1, #0x4
	mov r3, #0x0
	bl FUN_02066404
	b _0206587E
_0206584E:
	add r0, r4, #0x0
	bl FUN_020664F4
	cmp r0, #0x0
	bne _0206587E
	add sp, #0x4
	pop {r3-r4, pc}
_0206585C:
	ldr r0, _02065888 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _02065884
	add r0, r4, #0x0
	bl FUN_020664D8
	ldr r1, _0206588C ; =FUN_02065674
	ldr r2, _02065890 ; =FUN_020654B0
	add r0, r4, #0x0
	bl FUN_02065FE4
	mov r0, #0x0
	add sp, #0x4
	strh r0, [r4, #0x10]
	pop {r3-r4, pc}
_0206587E:
	ldrh r0, [r4, #0x10]
	add r0, r0, #0x1
	strh r0, [r4, #0x10]
_02065884:
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_02065888: .word gUnknown21C48B8
_0206588C: .word FUN_02065674
_02065890: .word FUN_020654B0

	thumb_func_start FUN_02065894
FUN_02065894: ; 0x02065894
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldrh r0, [r4, #0x10]
	cmp r0, #0x3
	bhi _0206592C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020658AA: ; jump table (using 16-bit offset)
	.short _020658B2 - _020658AA - 2; case 0
	.short _020658C8 - _020658AA - 2; case 1
	.short _020658D6 - _020658AA - 2; case 2
	.short _020658E2 - _020658AA - 2; case 3
_020658B2:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02066578
	cmp r0, #0x0
	beq _02065932
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02066634
	b _0206592C
_020658C8:
	add r0, r4, #0x0
	mov r1, #0xe
	bl FUN_02066664
	cmp r0, #0x0
	bne _0206592C
	pop {r3-r5, pc}
_020658D6:
	add r0, r4, #0x0
	bl FUN_020665C0
	cmp r0, #0x0
	bne _0206592C
	pop {r3-r5, pc}
_020658E2:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02066578
	cmp r0, #0x0
	beq _02065932
	mov r0, #0x6d
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r1, r0, #0x0
	add r1, #0x22
	ldrb r5, [r1, #0x0]
	bl FUN_02016A18
	cmp r5, #0x7
	bne _02065912
	ldr r1, [r4, #0xc]
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_02065FE4
	mov r0, #0x0
	strh r0, [r4, #0x10]
	pop {r3-r5, pc}
_02065912:
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_020661F8
	ldr r1, _02065934 ; =FUN_020654B0
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_02065FE4
	mov r0, #0x0
	strh r0, [r4, #0x10]
	pop {r3-r5, pc}
_0206592C:
	ldrh r0, [r4, #0x10]
	add r0, r0, #0x1
	strh r0, [r4, #0x10]
_02065932:
	pop {r3-r5, pc}
	.balign 4
_02065934: .word FUN_020654B0

	thumb_func_start FUN_02065938
FUN_02065938: ; 0x02065938
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r1, #0x0
	ldrh r0, [r4, #0x10]
	cmp r0, #0x0
	beq _0206594E
	cmp r0, #0x1
	beq _02065970
	cmp r0, #0x2
	beq _0206597E
	b _020659A0
_0206594E:
	add r0, r4, #0x0
	bl FUN_02066334
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x2
	bl FUN_02065DD8
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldrb r2, [r4, #0x16]
	add r0, r4, #0x0
	mov r1, #0x5
	mov r3, #0x0
	bl FUN_02066404
	b _020659A0
_02065970:
	add r0, r4, #0x0
	bl FUN_020664F4
	cmp r0, #0x0
	bne _020659A0
	add sp, #0x4
	pop {r3-r4, pc}
_0206597E:
	ldr r0, _020659AC ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _020659A6
	add r0, r4, #0x0
	bl FUN_020664D8
	ldr r1, _020659B0 ; =FUN_02065674
	ldr r2, _020659B4 ; =FUN_020654B0
	add r0, r4, #0x0
	bl FUN_02065FE4
	mov r0, #0x0
	add sp, #0x4
	strh r0, [r4, #0x10]
	pop {r3-r4, pc}
_020659A0:
	ldrh r0, [r4, #0x10]
	add r0, r0, #0x1
	strh r0, [r4, #0x10]
_020659A6:
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_020659AC: .word gUnknown21C48B8
_020659B0: .word FUN_02065674
_020659B4: .word FUN_020654B0

	thumb_func_start FUN_020659B8
FUN_020659B8: ; 0x020659B8
	push {r4-r6, lr}
	add r4, r1, #0x0
	ldrh r0, [r4, #0x10]
	cmp r0, #0x5
	bls _020659C4
	b _02065AE0
_020659C4:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020659D0: ; jump table (using 16-bit offset)
	.short _020659DC - _020659D0 - 2; case 0
	.short _02065A24 - _020659D0 - 2; case 1
	.short _02065A68 - _020659D0 - 2; case 2
	.short _02065A86 - _020659D0 - 2; case 3
	.short _02065AB8 - _020659D0 - 2; case 4
	.short _02065AC4 - _020659D0 - 2; case 5
_020659DC:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02066578
	cmp r0, #0x0
	beq _02065AE6
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02066634
	mov r0, #0x1b
	lsl r0, r0, #0x4
	ldrb r2, [r4, #0x18]
	mov r1, #0xc
	ldr r0, [r4, r0]
	mul r1, r2
	add r1, r4, r1
	ldrh r1, [r1, #0x22]
	ldr r2, [r4, #0x0]
	bl FUN_0206EEF8
	cmp r0, #0x0
	ldr r1, _02065AE8 ; =0x0000013B
	beq _02065A1A
	ldrb r2, [r4, r1]
	mov r0, #0xc0
	bic r2, r0
	mov r0, #0x40
	orr r0, r2
	strb r0, [r4, r1]
	b _02065AE0
_02065A1A:
	ldrb r2, [r4, r1]
	mov r0, #0xc0
	bic r2, r0
	strb r2, [r4, r1]
	b _02065AE0
_02065A24:
	add r0, r4, #0x0
	mov r1, #0x9
	bl FUN_02066664
	cmp r0, #0x0
	beq _02065AE6
	mov r0, #0x6d
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r1, r0, #0x0
	add r1, #0x22
	ldrb r5, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x23
	ldrb r6, [r1, #0x0]
	bl FUN_02016A18
	cmp r6, #0x6
	bne _02065A4E
	cmp r5, #0x7
	bne _02065A58
_02065A4E:
	ldr r0, _02065AEC ; =FUN_020657F4
	str r0, [r4, #0xc]
	mov r0, #0x4
	strh r0, [r4, #0x10]
	pop {r4-r6, pc}
_02065A58:
	strb r5, [r4, #0x17]
	ldrb r1, [r4, #0x18]
	mov r0, #0xc
	mov r2, #0x0
	mul r0, r1
	add r0, r4, r0
	strb r2, [r0, #0x1d]
	b _02065AE0
_02065A68:
	add r0, r4, #0x0
	bl FUN_02066728
	cmp r0, #0x0
	beq _02065AE6
	cmp r0, #0x1
	bne _02065A80
	ldr r0, _02065AEC ; =FUN_020657F4
	str r0, [r4, #0xc]
	mov r0, #0x4
	strh r0, [r4, #0x10]
	pop {r4-r6, pc}
_02065A80:
	ldr r0, _02065AF0 ; =FUN_020654B0
	str r0, [r4, #0xc]
	b _02065AE0
_02065A86:
	add r0, r4, #0x0
	mov r1, #0xb
	bl FUN_02066664
	cmp r0, #0x0
	beq _02065AE6
	mov r0, #0x6d
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02016A18
	ldr r2, _02065AE8 ; =0x0000013B
	ldrb r1, [r4, #0x17]
	ldrb r2, [r4, r2]
	add r0, r4, #0x0
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1e
	bl FUN_020661F8
	ldr r1, _02065AE8 ; =0x0000013B
	mov r0, #0xc0
	ldrb r2, [r4, r1]
	bic r2, r0
	strb r2, [r4, r1]
	b _02065AE0
_02065AB8:
	add r0, r4, #0x0
	bl FUN_020665C0
	cmp r0, #0x0
	bne _02065AE0
	pop {r4-r6, pc}
_02065AC4:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02066578
	cmp r0, #0x0
	beq _02065AE6
	ldr r1, [r4, #0xc]
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_02065FE4
	mov r0, #0x0
	strh r0, [r4, #0x10]
	pop {r4-r6, pc}
_02065AE0:
	ldrh r0, [r4, #0x10]
	add r0, r0, #0x1
	strh r0, [r4, #0x10]
_02065AE6:
	pop {r4-r6, pc}
	.balign 4
_02065AE8: .word 0x0000013B
_02065AEC: .word FUN_020657F4
_02065AF0: .word FUN_020654B0

	thumb_func_start FUN_02065AF4
FUN_02065AF4: ; 0x02065AF4
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r6, #0x0
	bl FUN_0205EB38
	mov r1, #0x69
	lsl r1, r1, #0x2
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #0xc8
	mov r2, #0xa
	mov r3, #0x8a
	bl FUN_0205EC48
	mov r0, #0x69
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r1, r6, #0x0
	mov r2, #0x1
	bl FUN_0205EC6C
	mov r0, #0x69
	lsl r0, r0, #0x2
	mov r1, #0x1
	ldr r0, [r5, r0]
	add r2, r1, #0x0
	bl FUN_0205EC6C
	mov r1, #0x17
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r2, _02065CD8 ; =UNK_020F7E7C
	add r1, r5, r1
	bl FUN_02019150
	mov r1, #0x17
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, #0x24
	ldr r2, _02065CDC ; =UNK_020F7E84
	add r1, r5, r1
	bl FUN_02019150
	mov r0, #0x5d
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0xff
	bl FUN_02019620
	mov r0, #0x65
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0xff
	bl FUN_02019620
	ldrb r0, [r5, #0x1b]
	ldr r1, [r5, #0x0]
	add r0, r0, #0x1
	bl FUN_02012838
	mov r1, #0x59
	lsl r1, r1, #0x2
	add r7, r5, #0x0
	str r0, [r5, r1]
	add r4, r6, #0x0
	add r7, #0x1c
_02065B7E:
	mov r0, #0xc
	mul r0, r4
	add r2, r7, r0
	ldrb r0, [r2, #0x1]
	cmp r0, #0x0
	beq _02065B9E
	mov r0, #0x59
	lsl r0, r0, #0x2
	ldr r1, [r2, #0x8]
	ldrb r2, [r2, #0x0]
	ldr r0, [r5, r0]
	bl FUN_020128A0
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_02065B9E:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x14
	blo _02065B7E
	mov r1, #0x59
	lsl r1, r1, #0x2
	ldr r0, [r5, r1]
	sub r1, #0x4c
	ldr r1, [r5, r1]
	ldr r2, _02065CE0 ; =0x0000FFFF
	bl FUN_020128A0
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	mov r1, #0x5
	lsr r6, r0, #0x18
	lsl r1, r1, #0x6
	ldr r0, _02065CE4 ; =UNK_020F7E8C
	add r1, r5, r1
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r1, #0x5d
	lsl r1, r1, #0x2
	add r0, r1, #0x0
	add r2, r5, r1
	sub r0, #0x28
	str r2, [r5, r0]
	add r0, r1, #0x0
	sub r0, #0x10
	ldr r2, [r5, r0]
	add r0, r1, #0x0
	sub r0, #0x34
	str r2, [r5, r0]
	add r0, r1, #0x0
	sub r0, #0x18
	str r5, [r5, r0]
	add r0, r1, #0x0
	sub r0, #0x24
	strh r6, [r5, r0]
	add r0, r1, #0x0
	sub r0, #0x1d
	ldrb r2, [r5, r0]
	mov r0, #0xf
	bic r2, r0
	mov r0, #0x6
	orr r2, r0
	add r0, r1, #0x0
	sub r0, #0x1d
	strb r2, [r5, r0]
	add r0, r1, #0x0
	ldr r2, _02065CE8 ; =FUN_02065D4C
	sub r0, #0x30
	str r2, [r5, r0]
	add r0, r1, #0x0
	ldr r2, _02065CEC ; =FUN_02065CFC
	sub r0, #0x2c
	str r2, [r5, r0]
	add r0, r1, #0x0
	sub r0, #0x39
	ldrb r0, [r5, r0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1e
	beq _02065C64
	add r0, r1, #0x0
	sub r0, #0x38
	ldrh r0, [r5, r0]
	cmp r0, #0x0
	bne _02065C48
	add r0, r1, #0x0
	sub r0, #0x36
	ldrh r2, [r5, r0]
	cmp r2, #0x0
	beq _02065C5A
	sub r0, r6, #0x1
	cmp r2, r0
	blt _02065C5A
	add r0, r1, #0x0
	sub r0, #0x36
	ldrh r0, [r5, r0]
	sub r1, #0x36
	sub r0, r0, #0x1
	strh r0, [r5, r1]
	b _02065C5A
_02065C48:
	add r0, r0, #0x7
	cmp r0, r6
	blt _02065C5A
	add r0, r1, #0x0
	sub r0, #0x38
	ldrh r0, [r5, r0]
	sub r1, #0x38
	sub r0, r0, #0x1
	strh r0, [r5, r1]
_02065C5A:
	ldr r1, _02065CF0 ; =0x0000013B
	mov r0, #0x30
	ldrb r2, [r5, r1]
	bic r2, r0
	strb r2, [r5, r1]
_02065C64:
	mov r2, #0x5
	lsl r2, r2, #0x6
	sub r1, r2, #0x4
	add r0, r5, r2
	sub r2, r2, #0x2
	ldr r3, [r5, #0x0]
	ldrh r1, [r5, r1]
	lsl r3, r3, #0x18
	ldrh r2, [r5, r2]
	lsr r3, r3, #0x18
	bl FUN_020010A8
	mov r1, #0x16
	lsl r1, r1, #0x4
	str r0, [r5, r1]
	add r1, #0x14
	add r0, r5, r1
	ldr r2, _02065CF4 ; =0x000003D9
	mov r1, #0x0
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r2, #0x65
	ldr r0, _02065CF8 ; =0x0001020F
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	lsl r2, r2, #0x2
	add r0, r5, r2
	str r1, [sp, #0xc]
	sub r2, #0x78
	ldr r2, [r5, r2]
	mov r3, #0x2
	bl FUN_0201BDE0
	mov r0, #0x65
	lsl r0, r0, #0x2
	ldr r2, _02065CF4 ; =0x000003D9
	add r0, r5, r0
	mov r1, #0x0
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r0, #0x17
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x3
	bl FUN_0201AC68
	ldr r1, _02065CF0 ; =0x0000013B
	mov r0, #0xf
	ldrb r2, [r5, r1]
	bic r2, r0
	strb r2, [r5, r1]
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_02065CD8: .word UNK_020F7E7C
_02065CDC: .word UNK_020F7E84
_02065CE0: .word 0x0000FFFF
_02065CE4: .word UNK_020F7E8C
_02065CE8: .word FUN_02065D4C
_02065CEC: .word FUN_02065CFC
_02065CF0: .word 0x0000013B
_02065CF4: .word 0x000003D9
_02065CF8: .word 0x0001020F

	thumb_func_start FUN_02065CFC
FUN_02065CFC: ; 0x02065CFC
	push {r3-r5, lr}
	add r4, r1, #0x0
	mov r1, #0x13
	add r5, r0, #0x0
	bl FUN_02001470
	ldr r1, _02065D48 ; =0x0000FFFF
	cmp r4, r1
	bne _02065D1C
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0xf
	mov r3, #0x2
	bl FUN_020013E8
	pop {r3-r5, pc}
_02065D1C:
	mov r1, #0xc
	mul r1, r4
	add r0, r0, r1
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02065D38
	add r0, r5, #0x0
	mov r1, #0x3
	mov r2, #0xf
	mov r3, #0x4
	bl FUN_020013E8
	pop {r3-r5, pc}
_02065D38:
	add r0, r5, #0x0
	mov r1, #0x7
	mov r2, #0xf
	mov r3, #0x8
	bl FUN_020013E8
	pop {r3-r5, pc}
	nop
_02065D48: .word 0x0000FFFF

	thumb_func_start FUN_02065D4C
FUN_02065D4C: ; 0x02065D4C
	push {r3-r6, lr}
	sub sp, #0x4
	mov r1, #0x13
	add r4, r0, #0x0
	add r6, r2, #0x0
	bl FUN_02001470
	add r1, sp, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, #0x2
	add r2, sp, #0x0
	bl FUN_02001448
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02001470
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r6, #0x0
	bne _02065D7E
	ldr r0, _02065DD4 ; =0x000005DC
	bl FUN_020054C8
_02065D7E:
	add r0, sp, #0x0
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	bne _02065D96
	mov r0, #0x69
	lsl r0, r0, #0x2
	mov r1, #0x0
	ldr r0, [r5, r0]
	add r2, r1, #0x0
	bl FUN_0205EC6C
	b _02065DA4
_02065D96:
	mov r0, #0x69
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	mov r1, #0x0
	mov r2, #0x1
	bl FUN_0205EC6C
_02065DA4:
	add r0, sp, #0x0
	ldrh r1, [r0, #0x2]
	sub r0, r4, #0x7
	cmp r1, r0
	bge _02065DC0
	mov r0, #0x69
	lsl r0, r0, #0x2
	mov r1, #0x1
	ldr r0, [r5, r0]
	add r2, r1, #0x0
	bl FUN_0205EC6C
	add sp, #0x4
	pop {r3-r6, pc}
_02065DC0:
	mov r0, #0x69
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_0205EC6C
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_02065DD4: .word 0x000005DC

	thumb_func_start FUN_02065DD8
FUN_02065DD8: ; 0x02065DD8
	push {r3-r7, lr}
	sub sp, #0x8
	str r1, [sp, #0x0]
	add r5, r0, #0x0
	str r2, [sp, #0x4]
	ldr r1, [r5, #0x0]
	mov r0, #0x4
	bl FUN_02012838
	mov r1, #0x59
	lsl r1, r1, #0x2
	str r0, [r5, r1]
	add r0, r1, #0x0
	add r0, #0xc
	add r1, #0x10
	ldr r0, [r5, r0]
	ldr r2, _02065EC8 ; =UNK_020F7E74
	add r1, r5, r1
	bl FUN_02019150
	mov r0, #0x5d
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0xff
	bl FUN_02019620
	mov r7, #0x43
	ldr r6, _02065ECC ; =UNK_020F7EAC
	mov r4, #0x0
	lsl r7, r7, #0x2
_02065E14:
	lsl r2, r4, #0x3
	add r3, r6, r2
	mov r0, #0x59
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r1, [r5, r7]
	ldr r2, [r6, r2]
	ldr r3, [r3, #0x4]
	bl FUN_02012880
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x4
	blo _02065E14
	mov r1, #0x5
	lsl r1, r1, #0x6
	ldr r0, _02065ED0 ; =UNK_020F7E8C
	add r1, r5, r1
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r0, #0x5d
	lsl r0, r0, #0x2
	add r1, r0, #0x0
	add r2, r5, r0
	sub r1, #0x28
	str r2, [r5, r1]
	add r1, r0, #0x0
	sub r1, #0x10
	ldr r2, [r5, r1]
	add r1, r0, #0x0
	sub r1, #0x34
	str r2, [r5, r1]
	add r1, r0, #0x0
	sub r1, #0x18
	str r5, [r5, r1]
	add r1, r0, #0x0
	mov r2, #0x4
	sub r1, #0x24
	strh r2, [r5, r1]
	add r1, r0, #0x0
	sub r1, #0x22
	strh r2, [r5, r1]
	add r1, r0, #0x0
	sub r1, #0x1a
	ldrh r2, [r5, r1]
	ldr r1, _02065ED4 ; =0xFFFFFE7F
	and r2, r1
	add r1, r0, #0x0
	sub r1, #0x1a
	strh r2, [r5, r1]
	add r1, r0, #0x0
	sub r0, #0x34
	ldr r2, _02065ED8 ; =FUN_02065EE4
	sub r1, #0x30
	str r2, [r5, r1]
	ldr r3, [r5, #0x0]
	ldr r1, [sp, #0x0]
	lsl r3, r3, #0x18
	ldr r2, [sp, #0x4]
	add r0, r5, r0
	lsr r3, r3, #0x18
	bl FUN_020010A8
	mov r1, #0x16
	lsl r1, r1, #0x4
	str r0, [r5, r1]
	add r1, #0x14
	add r0, r5, r1
	ldr r2, _02065EDC ; =0x000003D9
	mov r1, #0x0
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r0, #0x17
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x3
	bl FUN_0201AC68
	ldr r1, _02065EE0 ; =0x0000013B
	mov r0, #0xf
	ldrb r2, [r5, r1]
	bic r2, r0
	mov r0, #0x1
	orr r0, r2
	strb r0, [r5, r1]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02065EC8: .word UNK_020F7E74
_02065ECC: .word UNK_020F7EAC
_02065ED0: .word UNK_020F7E8C
_02065ED4: .word 0xFFFFFE7F
_02065ED8: .word FUN_02065EE4
_02065EDC: .word 0x000003D9
_02065EE0: .word 0x0000013B

	thumb_func_start FUN_02065EE4
FUN_02065EE4: ; 0x02065EE4
	push {r3, lr}
	cmp r2, #0x0
	bne _02065EF0
	ldr r0, _02065EF4 ; =0x000005DC
	bl FUN_020054C8
_02065EF0:
	pop {r3, pc}
	nop
_02065EF4: .word 0x000005DC

	thumb_func_start FUN_02065EF8
FUN_02065EF8: ; 0x02065EF8
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	mov r0, #0x16
	lsl r0, r0, #0x4
	add r1, sp, #0x0
	ldr r0, [r4, r0]
	add r1, #0x2
	add r2, sp, #0x0
	bl FUN_02001300
	mov r0, #0x59
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02012870
	mov r0, #0x65
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019570
	mov r0, #0x65
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x0
	bl FUN_0200CCF8
	mov r0, #0x65
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0x5d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019570
	mov r0, #0x5d
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x0
	bl FUN_0200CCF8
	mov r0, #0x5d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019178
	add r0, sp, #0x0
	mov r1, #0x4f
	ldrh r2, [r0, #0x2]
	lsl r1, r1, #0x2
	strh r2, [r4, r1]
	ldrh r2, [r0, #0x0]
	add r0, r1, #0x2
	add r1, #0x68
	strh r2, [r4, r0]
	ldr r0, [r4, r1]
	cmp r0, #0x0
	beq _02065F7C
	bl FUN_0205EBEC
	mov r0, #0x69
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
_02065F7C:
	mov r0, #0x17
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x3
	bl FUN_0201AC68
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02065F8C
FUN_02065F8C: ; 0x02065F8C
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	mov r0, #0x5d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019570
	mov r0, #0x5d
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x0
	bl FUN_0200CCF8
	mov r0, #0x16
	lsl r0, r0, #0x4
	add r1, sp, #0x0
	ldr r0, [r4, r0]
	add r1, #0x2
	add r2, sp, #0x0
	bl FUN_02001300
	mov r0, #0x59
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02012870
	mov r0, #0x5d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019178
	add r0, r4, #0x0
	bl FUN_020664D8
	mov r0, #0x17
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x3
	bl FUN_0201AC68
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02065FE4
FUN_02065FE4: ; 0x02065FE4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x8]
	add r4, r2, #0x0
	bl FUN_0201B6C4
	mov r0, #0x0
	strh r0, [r5, #0x10]
	str r4, [r5, #0xc]
	pop {r3-r5, pc}

	thumb_func_start FUN_02065FF8
FUN_02065FF8: ; 0x02065FF8
	push {r3, lr}
	strb r1, [r0, #0x0]
	mov r1, #0x0
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0206600E
	bl FUN_02021A4C
_0206600E:
	pop {r3, pc}

	thumb_func_start FUN_02066010
FUN_02066010: ; 0x02066010
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	mov r4, #0x0
	cmp r6, #0x0
	bls _02066040
_0206601E:
	mov r0, #0x8
	add r1, r7, #0x0
	bl FUN_020219F4
	mov r1, #0xc
	mul r1, r4
	add r1, r5, r1
	str r0, [r1, #0x8]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02065FF8
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, r6
	blo _0206601E
_02066040:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02066044
FUN_02066044: ; 0x02066044
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	ldr r4, _0206606C ; =0x00000000
	beq _0206606A
	mov r7, #0xc
_02066050:
	add r0, r4, #0x0
	mul r0, r7
	add r0, r5, r0
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _02066060
	bl FUN_02021A20
_02066060:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, r6
	blo _02066050
_0206606A:
	pop {r3-r7, pc}
	.balign 4
_0206606C: .word 0x00000000

	thumb_func_start FUN_02066070
FUN_02066070: ; 0x02066070
	push {r4-r7, lr}
	sub sp, #0x14
	add r4, r1, #0x0
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r5, r2, #0x0
	bl FUN_02025838
	mov r1, #0x6b
	lsl r1, r1, #0x2
	str r0, [sp, #0x4]
	str r0, [r6, r1]
	add r0, r4, #0x0
	bl FUN_0206F158
	mov r1, #0x1b
	lsl r1, r1, #0x4
	str r0, [r6, r1]
	add r0, r5, #0x0
	bl FUN_020256BC
	add r7, r0, #0x0
	add r0, r6, #0x0
	str r0, [sp, #0x10]
	add r0, #0x1b
	str r0, [sp, #0x10]
	add r0, r6, #0x0
	str r0, [sp, #0x8]
	add r0, #0x1c
	mov r4, #0x0
	str r0, [sp, #0x8]
_020660AE:
	ldr r0, [sp, #0x4]
	mov r1, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020258D4
	mov r0, #0xc
	mul r0, r4
	ldr r1, [sp, #0x8]
	str r0, [sp, #0xc]
	add r5, r1, r0
	ldrb r1, [r6, #0x19]
	mov r0, #0xc
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [sp, #0x8]
	add r1, r4, #0x0
	add r0, r0, r2
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02065FF8
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	strb r4, [r1, r0]
	add r0, r7, #0x0
	bl FUN_020256AC
	cmp r0, #0x0
	beq _02066134
	mov r0, #0x1
	strb r0, [r5, #0x1]
	add r0, r7, #0x0
	bl FUN_020257C8
	strb r0, [r5, #0x4]
	add r0, r7, #0x0
	bl FUN_020257CC
	strb r0, [r5, #0x5]
	ldrb r0, [r5, #0x5]
	bl FUN_0206EAD8
	strh r0, [r5, #0x6]
	add r0, r7, #0x0
	bl FUN_020257C4
	add r1, r0, #0x0
	ldr r0, [r5, #0x8]
	bl FUN_02021E28
	ldrb r0, [r6, #0x19]
	strb r0, [r5, #0x2]
	ldrb r1, [r5, #0x0]
	ldr r0, [sp, #0x0]
	strb r1, [r0, #0x3]
	ldrb r0, [r5, #0x0]
	strb r0, [r6, #0x19]
	ldr r0, [sp, #0x10]
	ldrb r0, [r0, #0x0]
	add r1, r0, #0x1
	ldr r0, [sp, #0x10]
	strb r1, [r0, #0x0]
	ldrb r0, [r6, #0x1a]
	cmp r0, #0xff
	bne _02066134
	strb r4, [r6, #0x1a]
_02066134:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x14
	blo _020660AE
	ldrb r1, [r6, #0x19]
	ldrb r3, [r6, #0x1a]
	mov r0, #0xc
	add r2, r1, #0x0
	mul r2, r0
	add r1, r6, r2
	strb r3, [r1, #0x1f]
	ldrb r1, [r6, #0x1a]
	ldrb r2, [r6, #0x19]
	mul r0, r1
	add r0, r6, r0
	strb r2, [r0, #0x1e]
	add r0, r7, #0x0
	bl FUN_02016A18
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_02066160
FUN_02066160: ; 0x02066160
	push {r3-r6}
	add r2, r1, #0x0
	mov r3, #0xc
	add r1, r0, #0x0
	mul r2, r3
	add r1, #0x1c
	add r1, r1, r2
	ldrb r4, [r1, #0x2]
	ldrb r6, [r1, #0x3]
	add r5, r4, #0x0
	mul r5, r3
	add r4, r0, r5
	strb r6, [r4, #0x1f]
	ldrb r4, [r1, #0x2]
	ldrb r1, [r1, #0x3]
	mul r3, r1
	add r1, r0, r3
	strb r4, [r1, #0x1e]
	add r1, r0, r2
	mov r3, #0x0
	strb r3, [r1, #0x1d]
	ldr r2, _0206619C ; =0x0000013B
	mov r1, #0x30
	ldrb r3, [r0, r2]
	bic r3, r1
	mov r1, #0x10
	orr r1, r3
	strb r1, [r0, r2]
	pop {r3-r6}
	bx lr
	.balign 4
_0206619C: .word 0x0000013B

	thumb_func_start FUN_020661A0
FUN_020661A0: ; 0x020661A0
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrb r1, [r5, #0x18]
	add r2, r5, #0x0
	mov r0, #0xc
	add r2, #0x1c
	mul r0, r1
	add r4, r2, r0
	mov r0, #0x1b
	lsl r0, r0, #0x4
	ldrh r1, [r4, #0x6]
	ldr r0, [r5, r0]
	ldr r3, [r5, #0x0]
	mov r2, #0x1
	bl FUN_0206ED24
	add r6, r0, #0x0
	beq _020661D4
	mov r0, #0x1b
	lsl r0, r0, #0x4
	ldrh r1, [r4, #0x6]
	ldr r0, [r5, r0]
	ldr r3, [r5, #0x0]
	mov r2, #0x1
	bl FUN_0206ED38
_020661D4:
	mov r0, #0x6b
	lsl r0, r0, #0x2
	ldrb r2, [r5, #0x18]
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_02025878
	ldrb r1, [r5, #0x18]
	add r0, r5, #0x0
	bl FUN_02066160
	ldrb r1, [r5, #0x18]
	add r0, r4, #0x0
	bl FUN_02065FF8
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020661F8
FUN_020661F8: ; 0x020661F8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	ldrb r1, [r5, #0x18]
	add r6, r2, #0x0
	add r2, r5, #0x0
	mov r0, #0xc
	add r2, #0x1c
	mul r0, r1
	add r4, r2, r0
	ldrb r0, [r4, #0x1]
	cmp r0, #0x0
	beq _0206626E
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_020377AC
	bl FUN_0206BB1C
	add r1, r7, #0x0
	bl FUN_0206B9B0
	add r2, r0, #0x0
	mov r0, #0x6b
	lsl r0, r0, #0x2
	ldrb r1, [r5, #0x18]
	ldr r0, [r5, r0]
	ldr r3, [r5, #0x0]
	bl FUN_020856A0
	cmp r6, #0x0
	beq _0206625E
	mov r0, #0x1b
	lsl r0, r0, #0x4
	ldrh r1, [r4, #0x6]
	ldr r0, [r5, r0]
	ldr r3, [r5, #0x0]
	mov r2, #0x1
	bl FUN_0206ED24
	cmp r0, #0x0
	beq _0206625E
	mov r0, #0x1b
	lsl r0, r0, #0x4
	ldrh r1, [r4, #0x6]
	ldr r0, [r5, r0]
	ldr r3, [r5, #0x0]
	mov r2, #0x1
	bl FUN_0206ED38
_0206625E:
	ldrb r1, [r5, #0x18]
	add r0, r5, #0x0
	bl FUN_02066160
	ldrb r1, [r5, #0x18]
	add r0, r4, #0x0
	bl FUN_02065FF8
_0206626E:
	pop {r3-r7, pc}

	thumb_func_start FUN_02066270
FUN_02066270: ; 0x02066270
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r2, #0x5a
	ldr r3, [r6, #0x0]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl FUN_0200A86C
	mov r1, #0x43
	lsl r1, r1, #0x2
	str r0, [r6, r1]
	ldr r2, [r6, #0x0]
	mov r0, #0x1
	mov r1, #0x80
	bl FUN_0200AA90
	mov r1, #0x11
	lsl r1, r1, #0x4
	str r0, [r6, r1]
	ldr r1, [r6, #0x0]
	mov r0, #0x80
	bl FUN_020219F4
	mov r1, #0x45
	lsl r1, r1, #0x2
	str r0, [r6, r1]
	sub r1, #0x8
	ldr r0, [r6, r1]
	mov r1, #0x4
	bl FUN_0200A914
	mov r1, #0x46
	lsl r1, r1, #0x2
	str r0, [r6, r1]
	sub r1, #0xc
	ldr r0, [r6, r1]
	mov r1, #0x0
	bl FUN_0200A914
	mov r1, #0x47
	lsl r1, r1, #0x2
	str r0, [r6, r1]
	mov r4, #0x0
	add r5, r6, #0x0
	add r7, r1, #0x4
_020662CC:
	mov r0, #0x43
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	add r1, r4, #0x6
	bl FUN_0200A914
	str r0, [r5, r7]
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x6
	blt _020662CC
	pop {r3-r7, pc}

	thumb_func_start FUN_020662E4
FUN_020662E4: ; 0x020662E4
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r7, #0x12
	mov r4, #0x0
	add r5, r6, #0x0
	lsl r7, r7, #0x4
_020662F0:
	ldr r0, [r5, r7]
	bl FUN_02021A20
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x6
	blt _020662F0
	mov r0, #0x47
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	bl FUN_02021A20
	mov r0, #0x46
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	bl FUN_02021A20
	mov r0, #0x45
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	bl FUN_02021A20
	mov r0, #0x11
	lsl r0, r0, #0x4
	ldr r0, [r6, r0]
	bl FUN_0200AB18
	mov r0, #0x43
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	bl FUN_0200A8B8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02066334
FUN_02066334: ; 0x02066334
	push {r3-r4, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_020377A8
	mov r1, #0x17
	lsl r1, r1, #0x4
	str r0, [r4, r1]
	ldrh r0, [r4, #0x14]
	ldr r2, _020663C8 ; =0x000003E2
	mov r3, #0xa
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [r4, r1]
	mov r1, #0x3
	bl FUN_0200CD68
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, _020663CC ; =0x000003D9
	str r0, [sp, #0x4]
	mov r0, #0x17
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r1, #0x1a
	ldr r2, [r4, #0x0]
	mov r0, #0x0
	lsl r1, r1, #0x4
	bl FUN_02002ED0
	mov r1, #0x6
	ldr r2, [r4, #0x0]
	mov r0, #0x0
	lsl r1, r1, #0x6
	bl FUN_02002EEC
	mov r0, #0x13
	str r0, [sp, #0x0]
	mov r0, #0x1b
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _020663D0 ; =0x0000036D
	mov r1, #0x17
	lsl r1, r1, #0x4
	str r0, [sp, #0x10]
	ldr r0, [r4, r1]
	add r1, #0x14
	add r1, r4, r1
	mov r2, #0x3
	mov r3, #0x2
	bl FUN_02019064
	mov r0, #0x61
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x0
	bl FUN_02019620
	add sp, #0x14
	pop {r3-r4, pc}
	.balign 4
_020663C8: .word 0x000003E2
_020663CC: .word 0x000003D9
_020663D0: .word 0x0000036D

	thumb_func_start FUN_020663D4
FUN_020663D4: ; 0x020663D4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x61
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019570
	mov r0, #0x61
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0x61
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x0
	mov r2, #0x10
	bl MI_CpuFill8
	mov r0, #0x17
	mov r1, #0x0
	lsl r0, r0, #0x4
	str r1, [r4, r0]
	pop {r4, pc}

	thumb_func_start FUN_02066404
FUN_02066404: ; 0x02066404
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [sp, #0x28]
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r0, #0x0
	beq _02066426
	mov r0, #0x61
	lsl r0, r0, #0x2
	ldr r2, _020664CC ; =0x000003E2
	add r0, r5, r0
	mov r1, #0x1
	mov r3, #0xa
	bl FUN_0200D0BC
_02066426:
	mov r1, #0xd8
	str r1, [sp, #0x0]
	mov r0, #0x20
	mov r2, #0x0
	add r1, #0xac
	str r0, [sp, #0x4]
	add r0, r5, r1
	mov r1, #0xff
	add r3, r2, #0x0
	bl FUN_020196F4
	mov r0, #0x1
	bl FUN_02002B60
	mov r0, #0x0
	bl FUN_02002B7C
	cmp r4, #0x0
	bne _02066494
	mov r0, #0x45
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_02021A4C
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	mov r0, #0x11
	lsl r0, r0, #0x4
	ldrb r3, [r5, #0x18]
	mov r2, #0xc
	ldr r0, [r5, r0]
	mul r2, r3
	add r2, r5, r2
	ldr r2, [r2, #0x24]
	mov r1, #0x0
	mov r3, #0x2
	bl FUN_0200ABB4
	mov r2, #0x11
	lsl r2, r2, #0x4
	lsl r3, r4, #0x2
	add r1, r2, #0x4
	ldr r0, [r5, r2]
	add r3, r5, r3
	add r2, #0x10
	ldr r1, [r5, r1]
	ldr r2, [r3, r2]
	bl FUN_0200B7B8
	mov r0, #0x45
	lsl r0, r0, #0x2
	ldr r2, [r5, r0]
	b _0206649E
_02066494:
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x12
	lsl r0, r0, #0x4
	ldr r2, [r1, r0]
_0206649E:
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldr r0, _020664D0 ; =0x0001020F
	str r6, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x61
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	str r3, [sp, #0xc]
	bl FUN_0201BDE0
	mov r1, #0x4e
	lsl r1, r1, #0x2
	strb r0, [r5, r1]
	add r1, #0x4c
	add r0, r5, r1
	bl FUN_020191D0
	ldr r0, _020664D4 ; =0x00000139
	strb r7, [r5, r0]
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_020664CC: .word 0x000003E2
_020664D0: .word 0x0001020F
_020664D4: .word 0x00000139

	thumb_func_start FUN_020664D8
FUN_020664D8: ; 0x020664D8
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x61
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	mov r0, #0x61
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019570
	pop {r4, pc}

	thumb_func_start FUN_020664F4
FUN_020664F4: ; 0x020664F4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x4e
	lsl r0, r0, #0x2
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0x0
	beq _0206650A
	mov r0, #0x0
	pop {r4, pc}
_0206650A:
	ldr r0, _0206651C ; =0x00000139
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	beq _02066518
	add r0, r4, #0x0
	bl FUN_020664D8
_02066518:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0206651C: .word 0x00000139

	thumb_func_start FUN_02066520
FUN_02066520: ; 0x02066520
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, _02066544 ; =UNK_020F7E6C
	str r0, [sp, #0x0]
	mov r0, #0x17
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	ldr r2, _02066548 ; =0x000003D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5a
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_02066544: .word UNK_020F7E6C
_02066548: .word 0x000003D9

	thumb_func_start FUN_0206654C
FUN_0206654C: ; 0x0206654C
	push {r3, lr}
	add r1, r0, #0x0
	mov r0, #0x5a
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	ldr r1, [r1, #0x0]
	bl FUN_020021AC
	cmp r0, #0x0
	beq _0206656A
	mov r1, #0x1
	mvn r1, r1
	cmp r0, r1
	beq _0206656E
	b _02066572
_0206656A:
	mov r0, #0x1
	pop {r3, pc}
_0206656E:
	mov r0, #0x0
	pop {r3, pc}
_02066572:
	add r0, r1, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02066578
FUN_02066578: ; 0x02066578
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldrh r0, [r4, #0x12]
	cmp r0, #0x0
	beq _0206658A
	cmp r0, #0x1
	beq _020665A8
	b _020665BA
_0206658A:
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x0]
	add r2, r1, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	ldrh r0, [r4, #0x12]
	add r0, r0, #0x1
	strh r0, [r4, #0x12]
	b _020665BA
_020665A8:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _020665BA
	mov r0, #0x0
	strh r0, [r4, #0x12]
	add sp, #0xc
	mov r0, #0x1
	pop {r3-r4, pc}
_020665BA:
	mov r0, #0x0
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_020665C0
FUN_020665C0: ; 0x020665C0
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x12]
	cmp r0, #0x0
	beq _020665D4
	cmp r0, #0x1
	beq _020665E6
	cmp r0, #0x2
	beq _02066614
	b _0206662E
_020665D4:
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0204649C
	ldrh r0, [r4, #0x12]
	add r0, r0, #0x1
	strh r0, [r4, #0x12]
	b _0206662E
_020665E6:
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_020464A4
	cmp r0, #0x0
	beq _0206662E
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x5a
	bl MOD06_0224C678
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x5a
	bl MOD06_0224C6E8
	ldrh r0, [r4, #0x12]
	add r0, r0, #0x1
	strh r0, [r4, #0x12]
	b _0206662E
_02066614:
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x5a
	ldr r0, [r0, #0x50]
	bl MOD05_021DA58C
	cmp r0, #0x0
	beq _0206662E
	mov r0, #0x0
	strh r0, [r4, #0x12]
	mov r0, #0x1
	pop {r4, pc}
_0206662E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02066634
FUN_02066634: ; 0x02066634
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x5b
	lsl r0, r0, #0x2
	add r4, r1, #0x0
	ldr r0, [r5, r0]
	mov r1, #0x5a
	bl MOD05_021DAF98
	cmp r4, #0x0
	bne _02066652
	add r0, r5, #0x0
	bl FUN_02065EF8
	b _02066658
_02066652:
	add r0, r5, #0x0
	bl FUN_02065F8C
_02066658:
	add r0, r5, #0x0
	bl FUN_020663D4
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02066664
FUN_02066664: ; 0x02066664
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x12]
	add r6, r1, #0x0
	cmp r0, #0x0
	beq _02066676
	cmp r0, #0x1
	beq _02066708
	b _0206671E
_02066676:
	ldr r0, [r5, #0x0]
	mov r1, #0x40
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x40
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_020377AC
	bl FUN_0206BB1C
	str r0, [r4, #0x0]
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_020377AC
	bl FUN_0206F158
	str r0, [r4, #0x4]
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_020377AC
	bl LoadPlayerDataAddress
	str r0, [r4, #0xc]
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r0, [r0, #0xc]
	bl FUN_02025838
	str r0, [r4, #0x8]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x20
	strb r6, [r0, #0x0]
	ldrb r1, [r5, #0x18]
	mov r0, #0xc
	mul r0, r1
	add r0, r5, r0
	ldrh r0, [r0, #0x22]
	cmp r6, #0xb
	strh r0, [r4, #0x24]
	bne _020666EC
	ldrb r1, [r5, #0x17]
	add r0, r4, #0x0
	add r0, #0x22
	strb r1, [r0, #0x0]
_020666EC:
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r1, _02066724 ; =UNK_020F96DC
	add r2, r4, #0x0
	bl FUN_020373D4
	mov r0, #0x6d
	lsl r0, r0, #0x2
	str r4, [r5, r0]
	ldrh r0, [r5, #0x12]
	add r0, r0, #0x1
	strh r0, [r5, #0x12]
	b _0206671E
_02066708:
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_0204647C
	cmp r0, #0x0
	bne _0206671E
	mov r0, #0x0
	strh r0, [r5, #0x12]
	mov r0, #0x1
	pop {r4-r6, pc}
_0206671E:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_02066724: .word UNK_020F96DC

	thumb_func_start FUN_02066728
FUN_02066728: ; 0x02066728
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x12]
	cmp r0, #0x0
	beq _02066738
	cmp r0, #0x1
	beq _0206677A
	b _020667D0
_02066738:
	ldrb r2, [r4, #0x18]
	mov r0, #0xc
	mul r0, r2
	add r3, r4, r0
	ldrb r0, [r3, #0x1d]
	cmp r0, #0x0
	beq _02066756
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldr r3, [r4, #0x0]
	mov r1, #0x0
	bl FUN_02037F58
	b _0206676C
_02066756:
	ldr r0, [r4, #0x0]
	add r3, #0x21
	str r0, [sp, #0x0]
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldrb r2, [r4, #0x17]
	ldrb r3, [r3, #0x0]
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_02037F2C
_0206676C:
	mov r1, #0x6a
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldrh r0, [r4, #0x12]
	add r0, r0, #0x1
	strh r0, [r4, #0x12]
	b _020667D0
_0206677A:
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0204647C
	cmp r0, #0x0
	bne _020667D0
	mov r0, #0x6a
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_020855E4
	cmp r0, #0x0
	beq _020667BC
	ldrb r0, [r4, #0x18]
	mov r2, #0xc
	mov r3, #0x1
	add r1, r0, #0x0
	mul r1, r2
	add r0, r4, r1
	strb r3, [r0, #0x1d]
	ldrb r3, [r4, #0x18]
	mov r0, #0x6a
	lsl r0, r0, #0x2
	mul r2, r3
	add r2, r4, r2
	ldrb r2, [r2, #0x1c]
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_020855E8
	mov r5, #0x2
	b _020667BE
_020667BC:
	mov r5, #0x1
_020667BE:
	mov r0, #0x6a
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0208562C
	mov r0, #0x0
	strh r0, [r4, #0x12]
	add r0, r5, #0x0
	pop {r3-r5, pc}
_020667D0:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_020667D4
FUN_020667D4: ; 0x020667D4
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	beq _020667F2
	cmp r1, #0x1
	beq _02066802
	b _02066814
_020667F2:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020653EC
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02066814
_02066802:
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	bne _0206680C
	mov r0, #0x0
	pop {r3-r5, pc}
_0206680C:
	bl FUN_02016A18
	mov r0, #0x1
	pop {r3-r5, pc}
_02066814:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02066818
FUN_02066818: ; 0x02066818
	push {r4, lr}
	bl FUN_02046528
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl FUN_020169D8
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	str r0, [r2, #0x4]
	ldr r0, [r4, #0x10]
	ldr r1, _0206683C ; =FUN_020667D4
	bl FUN_0204640C
	pop {r4, pc}
	nop
_0206683C: .word FUN_020667D4
