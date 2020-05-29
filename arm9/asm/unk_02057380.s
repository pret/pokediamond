    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F6364

	.text

	thumb_func_start FUN_02057380
FUN_02057380: ; 0x02057380
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r7, r2, #0x0
	bl FUN_02057444
	add r4, r0, #0x0
	add r1, r6, #0x0
	bl FUN_020583E0
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058364
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_02058398
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020573AC
FUN_020573AC: ; 0x020573AC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020583CC
	add r1, r0, #0x0
	mov r0, #0xb
	bl FUN_02016A8C
	mov r0, #0xb
	add r1, r4, #0x0
	bl FUN_02016A8C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020573C8
FUN_020573C8: ; 0x020573C8
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r5, r2, #0x0
	str r3, [sp, #0x4]
	ldr r7, [sp, #0x20]
	bl FUN_02058368
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_020583CC
	add r4, r0, #0x0
	cmp r6, #0x0
	beq _02057430
_020573E6:
	add r0, r4, #0x0
	bl FUN_02058830
	cmp r0, #0x1
	bne _02057426
	ldr r2, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r3, r7, #0x0
	bl FUN_02057F90
	cmp r0, #0x0
	beq _02057408
	cmp r0, #0x1
	beq _02057426
	cmp r0, #0x2
	b _02057426
_02057408:
	add r0, r4, #0x0
	bl FUN_02058450
	cmp r5, r0
	beq _02057426
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0xa
	bl FUN_0205842C
	cmp r0, #0x0
	bne _02057426
	add r0, r4, #0x0
	bl FUN_02057654
_02057426:
	mov r0, #0x4a
	lsl r0, r0, #0x2
	add r4, r4, r0
	sub r6, r6, #0x1
	bne _020573E6
_02057430:
	ldr r0, [sp, #0x0]
	bl FUN_020583A0
	add r1, r0, #0x0
	ldr r0, [sp, #0x0]
	bl MOD05_021F2AF4
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02057444
FUN_02057444: ; 0x02057444
	push {r4-r6, lr}
	mov r1, #0x4b
	add r4, r0, #0x0
	mov r0, #0xb
	lsl r1, r1, #0x2
	bl AllocFromHeap
	add r5, r0, #0x0
	bne _0205745A
	bl ErrorHandling
_0205745A:
	mov r2, #0x4b
	add r0, r5, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	bl memset
	mov r0, #0x4a
	lsl r0, r0, #0x2
	add r6, r4, #0x0
	mul r6, r0
	mov r0, #0xb
	add r1, r6, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	bne _0205747E
	bl ErrorHandling
_0205747E:
	add r0, r4, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl memset
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020583B4
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02057494
FUN_02057494: ; 0x02057494
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	add r7, r2, #0x0
	bl FUN_02058BFC
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02058CE0
	cmp r0, #0x0
	bne _020574C8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl FUN_02057C98
	add r4, r0, #0x0
	beq _020574E8
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02058214
	add r0, r4, #0x0
	pop {r3-r7, pc}
_020574C8:
	add r0, r6, #0x0
	bl FUN_02058CFC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02058010
	add r4, r0, #0x0
	beq _020574E8
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02058258
	add r0, r4, #0x0
	pop {r3-r7, pc}
_020574E8:
	add r0, r5, #0x0
	bl FUN_02057C64
	add r4, r0, #0x0
	beq _0205753A
	add r0, r5, #0x0
	bl FUN_020583E8
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_02057D2C
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02057E90
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_0205844C
	add r0, r4, #0x0
	bl FUN_020581A4
	add r0, r4, #0x0
	bl FUN_020581B4
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_02058410
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02057CF0
	add r0, r5, #0x0
	bl FUN_02058360
	bl FUN_0205836C
	add r0, r4, #0x0
_0205753A:
	pop {r3-r7, pc}

	thumb_func_start FUN_0205753C
FUN_0205753C: ; 0x0205753C
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, sp, #0x0
	mov r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_02058BF8
	ldr r1, [sp, #0x38]
	add r0, sp, #0x0
	bl FUN_02058C00
	ldr r1, [sp, #0x3c]
	add r0, sp, #0x0
	bl FUN_02058C08
	add r0, sp, #0x0
	mov r1, #0x0
	bl FUN_02058C10
	add r0, sp, #0x0
	mov r1, #0x0
	bl FUN_02058C18
	add r0, sp, #0x0
	mov r1, #0x0
	bl FUN_02058C20
	add r0, sp, #0x0
	add r1, r7, #0x0
	bl FUN_02058C28
	mov r1, #0x0
	add r0, sp, #0x0
	add r2, r1, #0x0
	bl FUN_02058C34
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x1
	bl FUN_02058C34
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x2
	bl FUN_02058C34
	add r0, sp, #0x0
	mov r1, #0x0
	bl FUN_02058C7C
	add r0, sp, #0x0
	mov r1, #0x0
	bl FUN_02058C88
	add r0, sp, #0x0
	add r1, r4, #0x0
	bl FUN_02058C94
	add r0, sp, #0x0
	add r1, r6, #0x0
	bl FUN_02058CA4
	add r0, sp, #0x0
	mov r1, #0x0
	bl FUN_02058C9C
	ldr r2, [sp, #0x40]
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02057494
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_020575D4
FUN_020575D4: ; 0x020575D4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	ldr r2, [sp, #0x18]
	add r7, r3, #0x0
	mov r4, #0x0
	bl FUN_02058CAC
	str r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02057610
	bl FUN_02058C1C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020583E8
	lsl r1, r6, #0x10
	lsr r1, r1, #0x10
	bl FUN_02039528
	cmp r0, #0x0
	bne _02057610
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	add r2, r7, #0x0
	bl FUN_02057494
	add r4, r0, #0x0
_02057610:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02057614
FUN_02057614: ; 0x02057614
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058454
	add r0, r4, #0x0
	bl FUN_02058148
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0xe
	bl FUN_02058418
	add r0, r4, #0x0
	bl FUN_020581B4
	pop {r4, pc}

	thumb_func_start FUN_02057634
FUN_02057634: ; 0x02057634
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02058934
	cmp r0, #0x1
	bne _02057648
	add r0, r5, #0x0
	bl FUN_020576A8
_02057648:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02057614
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02057654
FUN_02057654: ; 0x02057654
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058578
	bl FUN_020587E0
	cmp r0, #0x1
	bne _0205766A
	add r0, r4, #0x0
	bl FUN_020586B4
_0205766A:
	add r0, r4, #0x0
	bl FUN_02058660
	add r0, r4, #0x0
	bl FUN_02058564
	add r0, r4, #0x0
	bl FUN_02058580
	bl FUN_02058374
	add r0, r4, #0x0
	bl FUN_02057F80
	pop {r4, pc}

	thumb_func_start FUN_02057688
FUN_02057688: ; 0x02057688
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02058490
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058738
	lsl r1, r5, #0x10
	lsr r1, r1, #0x10
	bl FUN_0203953C
	add r0, r4, #0x0
	bl FUN_02057654
	pop {r3-r5, pc}

	thumb_func_start FUN_020576A8
FUN_020576A8: ; 0x020576A8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058578
	bl FUN_020587E0
	cmp r0, #0x1
	bne _020576D6
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0xe
	bl FUN_02058424
	cmp r0, #0x0
	beq _020576CC
	add r0, r4, #0x0
	bl FUN_020586B4
_020576CC:
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0xe
	bl FUN_02058418
_020576D6:
	ldr r1, _02057708 ; =0x0000FFFF
	add r0, r4, #0x0
	bl FUN_02058454
	ldr r1, _0205770C ; =FUN_02058ED8
	add r0, r4, #0x0
	bl FUN_02058684
	ldr r1, _02057710 ; =FUN_02058EDC
	add r0, r4, #0x0
	bl FUN_02058698
	ldr r1, _02057710 ; =FUN_02058EDC
	add r0, r4, #0x0
	bl FUN_020586AC
	ldr r1, _02057714 ; =FUN_02058EE0
	add r0, r4, #0x0
	bl FUN_020586C0
	ldr r1, _02057718 ; =FUN_02058EE4
	add r0, r4, #0x0
	bl FUN_020586D4
	pop {r4, pc}
	.balign 4
_02057708: .word 0x0000FFFF
_0205770C: .word FUN_02058ED8
_02057710: .word FUN_02058EDC
_02057714: .word FUN_02058EE0
_02057718: .word FUN_02058EE4

	thumb_func_start FUN_0205771C
FUN_0205771C: ; 0x0205771C
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r4, #0x0
	bl FUN_02058368
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020583CC
	mov r7, #0x4a
	add r5, r0, #0x0
	lsl r7, r7, #0x2
_02057734:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02058424
	cmp r0, #0x0
	beq _02057746
	add r0, r5, #0x0
	bl FUN_02057654
_02057746:
	add r4, r4, #0x1
	add r5, r5, r7
	cmp r4, r6
	blt _02057734
	pop {r3-r7, pc}

	thumb_func_start FUN_02057750
FUN_02057750: ; 0x02057750
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020587E0
	cmp r0, #0x1
	beq _02057760
	bl ErrorHandling
_02057760:
	add r0, r5, #0x0
	mov r4, #0x0
	bl FUN_02058368
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020583CC
	mov r7, #0x4a
	add r5, r0, #0x0
	lsl r7, r7, #0x2
_02057776:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02058424
	cmp r0, #0x0
	beq _0205779C
	mov r1, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0xe
	bl FUN_02058424
	cmp r0, #0x0
	beq _0205779C
	add r0, r5, #0x0
	bl FUN_020586C8
	add r0, r5, #0x0
	bl FUN_0205816C
_0205779C:
	add r4, r4, #0x1
	add r5, r5, r7
	cmp r4, r6
	blt _02057776
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020577A8
FUN_020577A8: ; 0x020577A8
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020587E0
	cmp r0, #0x1
	beq _020577B8
	bl ErrorHandling
_020577B8:
	add r0, r5, #0x0
	mov r4, #0x0
	bl FUN_02058368
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020583CC
	mov r7, #0x4a
	add r5, r0, #0x0
	lsl r7, r7, #0x2
_020577CE:
	add r0, r5, #0x0
	bl FUN_02058830
	cmp r0, #0x1
	bne _020577F6
	add r0, r5, #0x0
	bl FUN_02058884
	cmp r0, #0x1
	bne _020577EA
	add r0, r5, #0x0
	bl FUN_020586DC
	b _020577F0
_020577EA:
	add r0, r5, #0x0
	bl FUN_020581B4
_020577F0:
	add r0, r5, #0x0
	bl FUN_02058148
_020577F6:
	add r4, r4, #0x1
	add r5, r5, r7
	cmp r4, r6
	blt _020577CE
	pop {r3-r7, pc}

	thumb_func_start FUN_02057800
FUN_02057800: ; 0x02057800
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r1, sp, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	bl FUN_020580F4
	cmp r0, #0x0
	beq _02057846
_02057820:
	ldr r1, [sp, #0x0]
	add r0, r7, #0x0
	add r2, r5, #0x0
	bl FUN_02057894
	sub r4, r4, #0x1
	add r5, #0x50
	cmp r4, #0x0
	bgt _02057836
	bl ErrorHandling
_02057836:
	add r0, r6, #0x0
	add r1, sp, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	bl FUN_020580F4
	cmp r0, #0x0
	bne _02057820
_02057846:
	cmp r4, #0x0
	beq _02057856
	mov r2, #0x50
	add r0, r5, #0x0
	mov r1, #0x0
	mul r2, r4
	bl memset
_02057856:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0205785C
FUN_0205785C: ; 0x0205785C
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r7, r2, #0x0
	beq _02057892
_02057866:
	ldr r1, [r5, #0x0]
	mov r0, #0x1
	tst r0, r1
	beq _0205788C
	add r0, r6, #0x0
	bl FUN_02057C64
	add r4, r0, #0x0
	bne _0205787C
	bl ErrorHandling
_0205787C:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020579C4
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02057AEC
_0205788C:
	add r5, #0x50
	sub r7, r7, #0x1
	bne _02057866
_02057892:
	pop {r3-r7, pc}

	thumb_func_start FUN_02057894
FUN_02057894: ; 0x02057894
	push {r3-r6, lr}
	sub sp, #0xc
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r4, r2, #0x0
	add r0, r5, #0x0
	bl FUN_0205840C
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02058440
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_02058448
	strb r0, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_02058450
	strh r0, [r4, #0x10]
	add r0, r5, #0x0
	bl FUN_02058458
	strh r0, [r4, #0x12]
	add r0, r5, #0x0
	bl FUN_02058480
	strb r0, [r4, #0x9]
	add r0, r5, #0x0
	bl FUN_02058488
	strh r0, [r4, #0x14]
	add r0, r5, #0x0
	bl FUN_02058490
	strh r0, [r4, #0x16]
	add r0, r5, #0x0
	bl FUN_02058498
	strh r0, [r4, #0x18]
	add r0, r5, #0x0
	bl FUN_020584A0
	strb r0, [r4, #0xc]
	add r0, r5, #0x0
	bl FUN_020584C4
	strb r0, [r4, #0xd]
	add r0, r5, #0x0
	bl FUN_020584D4
	strb r0, [r4, #0xe]
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	strh r0, [r4, #0x1a]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02058510
	strh r0, [r4, #0x1c]
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_02058510
	strh r0, [r4, #0x1e]
	add r0, r5, #0x0
	bl FUN_02058538
	strb r0, [r4, #0xa]
	add r0, r5, #0x0
	bl FUN_02058540
	strb r0, [r4, #0xb]
	add r0, r5, #0x0
	bl FUN_02058AFC
	strh r0, [r4, #0x20]
	add r0, r5, #0x0
	bl FUN_02058B04
	strh r0, [r4, #0x22]
	add r0, r5, #0x0
	bl FUN_02058B0C
	strh r0, [r4, #0x24]
	add r0, r5, #0x0
	bl FUN_02058B2C
	strh r0, [r4, #0x26]
	add r0, r5, #0x0
	bl FUN_02058B3C
	strh r0, [r4, #0x28]
	add r0, r5, #0x0
	bl FUN_02058B4C
	strh r0, [r4, #0x2a]
	mov r0, #0x26
	mov r1, #0x2a
	ldrsh r0, [r4, r0]
	ldrsh r1, [r4, r1]
	add r2, sp, #0x0
	bl FUN_02059E60
	add r0, r5, #0x0
	bl FUN_02058B80
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02058AE4
	add r2, r0, #0x0
	add r0, r6, #0x0
	add r1, sp, #0x0
	bl FUN_02059EC8
	cmp r0, #0x0
	bne _0205798E
	add r0, r5, #0x0
	bl FUN_02058B80
	b _02057990
_0205798E:
	ldr r0, [sp, #0x4]
_02057990:
	str r0, [r4, #0x2c]
	add r0, r5, #0x0
	bl FUN_020585B0
	add r3, r4, #0x0
	add r3, #0x30
	mov r2, #0x10
_0205799E:
	ldrb r1, [r0, #0x0]
	add r0, r0, #0x1
	strb r1, [r3, #0x0]
	add r3, r3, #0x1
	sub r2, r2, #0x1
	bne _0205799E
	add r0, r5, #0x0
	bl FUN_020585D8
	add r4, #0x40
	mov r2, #0x10
_020579B4:
	ldrb r1, [r0, #0x0]
	add r0, r0, #0x1
	strb r1, [r4, #0x0]
	add r4, r4, #0x1
	sub r2, r2, #0x1
	bne _020579B4
	add sp, #0xc
	pop {r3-r6, pc}

	thumb_func_start FUN_020579C4
FUN_020579C4: ; 0x020579C4
	push {r4-r5, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	ldr r1, [r4, #0x0]
	add r5, r0, #0x0
	bl FUN_02058408
	ldr r1, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_0205843C
	ldrb r1, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_02058444
	ldrh r1, [r4, #0x10]
	add r0, r5, #0x0
	bl FUN_0205844C
	ldrh r1, [r4, #0x12]
	add r0, r5, #0x0
	bl FUN_02058454
	ldrb r1, [r4, #0x9]
	add r0, r5, #0x0
	bl FUN_0205847C
	ldrh r1, [r4, #0x14]
	add r0, r5, #0x0
	bl FUN_02058484
	ldrh r1, [r4, #0x16]
	add r0, r5, #0x0
	bl FUN_0205848C
	ldrh r1, [r4, #0x18]
	add r0, r5, #0x0
	bl FUN_02058494
	mov r1, #0xc
	ldrsb r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_0205849C
	mov r1, #0xd
	ldrsb r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_020584A4
	mov r1, #0xe
	ldrsb r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_020584CC
	mov r1, #0x1a
	ldrsh r1, [r4, r1]
	add r0, r5, #0x0
	mov r2, #0x0
	bl FUN_020584EC
	mov r1, #0x1c
	ldrsh r1, [r4, r1]
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_020584EC
	mov r1, #0x1e
	ldrsh r1, [r4, r1]
	add r0, r5, #0x0
	mov r2, #0x2
	bl FUN_020584EC
	mov r1, #0xa
	ldrsb r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02058534
	mov r1, #0xb
	ldrsb r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_0205853C
	mov r1, #0x20
	ldrsh r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02058B00
	mov r1, #0x22
	ldrsh r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02058B08
	mov r1, #0x24
	ldrsh r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02058B10
	mov r1, #0x26
	ldrsh r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02058B30
	mov r1, #0x28
	ldrsh r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02058B40
	mov r1, #0x2a
	ldrsh r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02058B50
	add r1, sp, #0x0
	mov r0, #0x0
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	str r0, [r1, #0x8]
	ldr r0, [r4, #0x2c]
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02058B6C
	add r0, r5, #0x0
	bl FUN_020585B0
	add r3, r4, #0x0
	add r3, #0x30
	mov r2, #0x10
_02057AC4:
	ldrb r1, [r3, #0x0]
	add r3, r3, #0x1
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _02057AC4
	add r0, r5, #0x0
	bl FUN_020585D8
	add r4, #0x40
	mov r2, #0x10
_02057ADA:
	ldrb r1, [r4, #0x0]
	add r4, r4, #0x1
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _02057ADA
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_02057AEC
FUN_02057AEC: ; 0x02057AEC
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02057B34
	add r0, r4, #0x0
	bl FUN_02057B54
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058570
	add r0, r4, #0x0
	bl FUN_02057EE0
	add r0, r4, #0x0
	bl FUN_0205AE80
	add r0, r4, #0x0
	bl FUN_020581B4
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02057CF0
	add r0, r4, #0x0
	bl FUN_0205866C
	add r0, r5, #0x0
	bl FUN_02058360
	bl FUN_0205836C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02057B34
FUN_02057B34: ; 0x02057B34
	push {r4, lr}
	mov r1, #0x5
	add r4, r0, #0x0
	bl FUN_02058410
	ldr r1, _02057B50 ; =0x00EF4248
	add r0, r4, #0x0
	bl FUN_02058418
	add r0, r4, #0x0
	bl FUN_0205815C
	pop {r4, pc}
	nop
_02057B50: .word 0x00EF4248

	thumb_func_start FUN_02057B54
FUN_02057B54: ; 0x02057B54
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r1, sp, #0x0
	bl FUN_02058B5C
	add r0, r4, #0x0
	bl FUN_02058B2C
	add r1, r0, #0x0
	mov r0, #0x2
	lsl r2, r1, #0x10
	lsl r0, r0, #0xe
	add r0, r2, r0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_02058B18
	add r0, r4, #0x0
	bl FUN_02058B3C
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B20
	add r0, r4, #0x0
	bl FUN_02058B4C
	add r1, r0, #0x0
	mov r0, #0x2
	lsl r2, r1, #0x10
	lsl r0, r0, #0xe
	add r0, r2, r0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl FUN_02058B28
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02058B6C
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02057BAC
FUN_02057BAC: ; 0x02057BAC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r2, #0x0
	add r7, r0, #0x0
	add r4, r3, #0x0
	str r1, [sp, #0x0]
	cmp r5, #0x0
	bne _02057BC0
	bl ErrorHandling
_02057BC0:
	lsl r0, r5, #0x5
	str r0, [sp, #0x4]
	ldr r1, [sp, #0x4]
	mov r0, #0xb
	bl AllocFromHeapAtEnd
	add r6, r0, #0x0
	bne _02057BD4
	bl ErrorHandling
_02057BD4:
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl memcpy
	mov r0, #0xb
	mov r1, #0x14
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	bne _02057BEE
	bl ErrorHandling
_02057BEE:
	ldr r0, [sp, #0x0]
	str r0, [r4, #0x0]
	str r5, [r4, #0x4]
	mov r0, #0x0
	str r0, [r4, #0x8]
	str r7, [r4, #0xc]
	add r0, r4, #0x0
	str r6, [r4, #0x10]
	bl FUN_02057C08
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02057C08
FUN_02057C08: ; 0x02057C08
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_020583E8
	add r6, r5, #0x0
	ldr r4, [r5, #0x10]
	add r7, r0, #0x0
	add r6, #0x8
_02057C1A:
	add r0, r4, #0x0
	bl FUN_02058CE0
	cmp r0, #0x1
	beq _02057C30
	ldrh r1, [r4, #0x8]
	add r0, r7, #0x0
	bl FUN_02039528
	cmp r0, #0x0
	bne _02057C42
_02057C30:
	ldr r0, [r5, #0xc]
	ldr r2, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02057494
	cmp r0, #0x0
	bne _02057C42
	bl ErrorHandling
_02057C42:
	ldr r0, [r6, #0x0]
	add r4, #0x20
	add r0, r0, #0x1
	str r0, [r6, #0x0]
	ldr r1, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r1, r0
	blt _02057C1A
	ldr r1, [r5, #0x10]
	mov r0, #0xb
	bl FUN_02016A8C
	mov r0, #0xb
	add r1, r5, #0x0
	bl FUN_02016A8C
	pop {r3-r7, pc}

	thumb_func_start FUN_02057C64
FUN_02057C64: ; 0x02057C64
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r4, #0x0
	bl FUN_02058368
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020583CC
	mov r7, #0x4a
	add r5, r0, #0x0
	lsl r7, r7, #0x2
_02057C7C:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02058424
	cmp r0, #0x0
	bne _02057C8C
	add r0, r5, #0x0
	pop {r3-r7, pc}
_02057C8C:
	add r4, r4, #0x1
	add r5, r5, r7
	cmp r4, r6
	blt _02057C7C
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02057C98
FUN_02057C98: ; 0x02057C98
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	mov r1, #0x0
	add r4, r2, #0x0
	str r1, [sp, #0x4]
	add r1, sp, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	add r6, r0, #0x0
	bl FUN_020580F4
	cmp r0, #0x1
	bne _02057CEA
	add r7, sp, #0x0
_02057CB6:
	ldr r0, [sp, #0x0]
	bl FUN_020589CC
	cmp r0, #0x1
	bne _02057CDA
	ldr r0, [sp, #0x0]
	bl FUN_02058448
	cmp r5, r0
	bne _02057CDA
	ldr r0, [sp, #0x0]
	bl FUN_02058750
	cmp r4, r0
	bne _02057CDA
	ldr r0, [sp, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}
_02057CDA:
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	bl FUN_020580F4
	cmp r0, #0x1
	beq _02057CB6
_02057CEA:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02057CF0
FUN_02057CF0: ; 0x02057CF0
	push {r3-r5, lr}
	add r4, r1, #0x0
	bl FUN_0205839C
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058480
	cmp r0, #0x30
	beq _02057D08
	cmp r0, #0x32
	bne _02057D0A
_02057D08:
	add r5, r5, #0x2
_02057D0A:
	ldr r0, _02057D28 ; =FUN_0205832C
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FUN_0200CA44
	add r5, r0, #0x0
	bne _02057D1C
	bl ErrorHandling
_02057D1C:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058554
	pop {r3-r5, pc}
	nop
_02057D28: .word FUN_0205832C

	thumb_func_start FUN_02057D2C
FUN_02057D2C: ; 0x02057D2C
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r6, r2, #0x0
	bl FUN_02058BFC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058444
	add r0, r4, #0x0
	bl FUN_02058C04
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02058170
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058454
	add r0, r4, #0x0
	bl FUN_02058C0C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205847C
	add r0, r4, #0x0
	bl FUN_02058C14
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058484
	add r0, r4, #0x0
	bl FUN_02058C1C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205848C
	add r0, r4, #0x0
	bl FUN_02058C24
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058494
	add r0, r4, #0x0
	bl FUN_02058C2C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205849C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02058C58
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x0
	bl FUN_020584EC
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02058C58
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_020584EC
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02058C58
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x2
	bl FUN_020584EC
	add r0, r4, #0x0
	bl FUN_02058C80
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058534
	add r0, r4, #0x0
	bl FUN_02058C8C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205853C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02057DFC
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02057DFC
FUN_02057DFC: ; 0x02057DFC
	push {r3-r6, lr}
	sub sp, #0xc
	add r6, r1, #0x0
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02058C98
	add r5, r0, #0x0
	mov r0, #0x2
	lsl r1, r5, #0x10
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058B00
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058B18
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058B30
	add r0, r6, #0x0
	bl FUN_02058CA0
	asr r1, r0, #0x3
	str r0, [sp, #0x4]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r5, r0, #0xc
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058B08
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058B20
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058B40
	add r0, r6, #0x0
	bl FUN_02058CA8
	add r5, r0, #0x0
	mov r0, #0x2
	lsl r1, r5, #0x10
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058B10
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058B28
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02058B50
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02058B6C
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02057E90
FUN_02057E90: ; 0x02057E90
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, _02057EDC ; =0x00001801
	add r5, r0, #0x0
	bl FUN_02058410
	add r0, r5, #0x0
	bl FUN_020581F8
	cmp r0, #0x1
	bne _02057EAE
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020589B0
_02057EAE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02058570
	add r0, r5, #0x0
	bl FUN_020584A0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020584A4
	add r0, r5, #0x0
	bl FUN_020584A0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_0205AE80
	pop {r3-r5, pc}
	nop
_02057EDC: .word 0x00001801

	thumb_func_start FUN_02057EE0
FUN_02057EE0: ; 0x02057EE0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02058480
	bl FUN_02058D14
	add r4, r0, #0x0
	bl FUN_02058D2C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058630
	add r0, r4, #0x0
	bl FUN_02058D30
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058644
	add r0, r4, #0x0
	bl FUN_02058D34
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058658
	pop {r3-r5, pc}

	thumb_func_start FUN_02057F18
FUN_02057F18: ; 0x02057F18
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02058458
	mov r1, #0x2
	lsl r1, r1, #0xc
	cmp r0, r1
	bne _02057F2C
	ldr r5, _02057F7C ; =UNK05_021F9080
	b _02057F32
_02057F2C:
	bl FUN_02058D4C
	add r5, r0, #0x0
_02057F32:
	add r0, r5, #0x0
	bl FUN_02058D38
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058684
	add r0, r5, #0x0
	bl FUN_02058D3C
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058698
	add r0, r5, #0x0
	bl FUN_02058D40
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020586AC
	add r0, r5, #0x0
	bl FUN_02058D44
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020586C0
	add r0, r5, #0x0
	bl FUN_02058D48
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020586D4
	pop {r3-r5, pc}
	nop
_02057F7C: .word UNK05_021F9080

	thumb_func_start FUN_02057F80
FUN_02057F80: ; 0x02057F80
	ldr r3, _02057F8C ; =memset
	mov r2, #0x4a
	mov r1, #0x0
	lsl r2, r2, #0x2
	bx r3
	nop
_02057F8C: .word memset

	thumb_func_start FUN_02057F90
FUN_02057F90: ; 0x02057F90
	push {r3-r7, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r3, #0x0
	str r1, [sp, #0x0]
	cmp r6, #0x0
	beq _0205800A
_02057F9E:
	add r0, r4, #0x0
	bl FUN_02058BFC
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058448
	cmp r7, r0
	bne _02058002
	add r0, r4, #0x0
	bl FUN_02058CE0
	cmp r0, #0x1
	bne _02057FE8
	add r0, r4, #0x0
	bl FUN_02058CFC
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020589CC
	cmp r0, #0x1
	bne _02057FDA
	add r0, r5, #0x0
	bl FUN_02058750
	cmp r7, r0
	bne _02058002
	mov r0, #0x1
	pop {r3-r7, pc}
_02057FDA:
	add r0, r5, #0x0
	bl FUN_02058450
	cmp r7, r0
	bne _02058002
	mov r0, #0x2
	pop {r3-r7, pc}
_02057FE8:
	add r0, r5, #0x0
	bl FUN_020589CC
	cmp r0, #0x1
	bne _02058002
	add r0, r5, #0x0
	bl FUN_02058750
	ldr r1, [sp, #0x0]
	cmp r1, r0
	bne _02058002
	mov r0, #0x2
	pop {r3-r7, pc}
_02058002:
	sub r6, r6, #0x1
	add r4, #0x20
	cmp r6, #0x0
	bne _02057F9E
_0205800A:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02058010
FUN_02058010: ; 0x02058010
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	mov r1, #0x0
	add r4, r2, #0x0
	str r1, [sp, #0x4]
	add r1, sp, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	add r6, r0, #0x0
	bl FUN_020580F4
	cmp r0, #0x1
	bne _02058058
	add r7, sp, #0x0
_0205802E:
	ldr r0, [sp, #0x0]
	bl FUN_02058448
	cmp r5, r0
	bne _02058048
	ldr r0, [sp, #0x0]
	bl FUN_02058450
	cmp r4, r0
	bne _02058048
	ldr r0, [sp, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}
_02058048:
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	bl FUN_020580F4
	cmp r0, #0x1
	beq _0205802E
_02058058:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02058060
FUN_02058060: ; 0x02058060
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	cmp r5, #0x0
	bne _0205806E
	bl ErrorHandling
_0205806E:
	add r0, r5, #0x0
	bl FUN_02058368
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020583C4
	mov r7, #0x4a
	add r5, r0, #0x0
	lsl r7, r7, #0x2
_02058082:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205842C
	cmp r0, #0x1
	bne _020580A6
	add r0, r5, #0x0
	bl FUN_020589CC
	cmp r0, #0x0
	bne _020580A6
	add r0, r5, #0x0
	bl FUN_02058448
	cmp r6, r0
	bne _020580A6
	add r0, r5, #0x0
	pop {r3-r7, pc}
_020580A6:
	sub r4, r4, #0x1
	add r5, r5, r7
	cmp r4, #0x0
	bgt _02058082
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020580B4
FUN_020580B4: ; 0x020580B4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	bl FUN_02058368
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020583C4
	mov r7, #0x4a
	add r5, r0, #0x0
	lsl r7, r7, #0x2
_020580CC:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205842C
	cmp r0, #0x1
	bne _020580E6
	add r0, r5, #0x0
	bl FUN_02058480
	cmp r6, r0
	bne _020580E6
	add r0, r5, #0x0
	pop {r3-r7, pc}
_020580E6:
	sub r4, r4, #0x1
	add r5, r5, r7
	cmp r4, #0x0
	bgt _020580CC
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020580F4
FUN_020580F4: ; 0x020580F4
	push {r3-r7, lr}
	add r5, r2, #0x0
	add r4, r0, #0x0
	str r1, [sp, #0x0]
	add r6, r3, #0x0
	bl FUN_02058368
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, r7
	blt _0205810E
	mov r0, #0x0
	pop {r3-r7, pc}
_0205810E:
	add r0, r4, #0x0
	bl FUN_020583C4
	mov r1, #0x4a
	ldr r2, [r5, #0x0]
	lsl r1, r1, #0x2
	mul r1, r2
	add r4, r0, r1
_0205811E:
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	add r0, r4, #0x0
	bl FUN_02058424
	cmp r6, r0
	bne _02058138
	ldr r0, [sp, #0x0]
	str r4, [r0, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_02058138:
	mov r0, #0x4a
	lsl r0, r0, #0x2
	add r4, r4, r0
	ldr r0, [r5, #0x0]
	cmp r0, r7
	blt _0205811E
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02058148
FUN_02058148: ; 0x02058148
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x4
	bl FUN_02058410
	add r0, r4, #0x0
	bl FUN_0205815C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205815C
FUN_0205815C: ; 0x0205815C
	ldr r3, _02058164 ; =FUN_02058418
	ldr r1, _02058168 ; =0x05108000
	bx r3
	nop
_02058164: .word FUN_02058418
_02058168: .word 0x05108000

	thumb_func_start FUN_0205816C
FUN_0205816C: ; 0x0205816C
	bx lr
	.balign 4

	thumb_func_start FUN_02058170
FUN_02058170: ; 0x02058170
	push {r3, lr}
	cmp r1, #0x65
	blt _02058186
	cmp r1, #0x75
	bgt _02058186
	sub r1, #0x65
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02039504
	add r1, r0, #0x0
_02058186:
	add r0, r1, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205818C
FUN_0205818C: ; 0x0205818C
	push {r4, lr}
	mov r1, #0x1
	lsl r1, r1, #0xc
	add r4, r0, #0x0
	bl FUN_02058424
	cmp r0, #0x0
	beq _020581A2
	add r0, r4, #0x0
	bl FUN_02059D1C
_020581A2:
	pop {r4, pc}

	thumb_func_start FUN_020581A4
FUN_020581A4: ; 0x020581A4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02057EE0
	add r0, r4, #0x0
	bl FUN_02058EE8
	pop {r4, pc}

	thumb_func_start FUN_020581B4
FUN_020581B4: ; 0x020581B4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058578
	bl FUN_020587E0
	cmp r0, #0x0
	beq _020581F6
	add r0, r4, #0x0
	bl FUN_0205818C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r4, #0x0
	mov r1, #0x0
	bl MOD05_021F2E0C
	add r0, r4, #0x0
	bl FUN_02058884
	cmp r0, #0x0
	bne _020581F6
	add r0, r4, #0x0
	bl FUN_02057F18
	add r0, r4, #0x0
	bl FUN_0205868C
	add r0, r4, #0x0
	bl FUN_02058878
_020581F6:
	pop {r4, pc}

	thumb_func_start FUN_020581F8
FUN_020581F8: ; 0x020581F8
	push {r3, lr}
	bl FUN_02058498
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, _02058210 ; =0x0000FFFF
	cmp r1, r0
	bne _0205820C
	mov r0, #0x1
	pop {r3, pc}
_0205820C:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02058210: .word 0x0000FFFF

	thumb_func_start FUN_02058214
FUN_02058214: ; 0x02058214
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020589CC
	cmp r0, #0x1
	beq _02058228
	bl ErrorHandling
_02058228:
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020589B0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0205844C
	add r0, r4, #0x0
	bl FUN_02058C24
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058494
	add r0, r4, #0x0
	bl FUN_02058C1C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205848C
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02058258
FUN_02058258: ; 0x02058258
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	add r4, r1, #0x0
	bl FUN_02058CE0
	cmp r0, #0x1
	beq _0205826E
	bl ErrorHandling
_0205826E:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020589B0
	add r0, r6, #0x0
	bl FUN_02058C24
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058494
	add r0, r6, #0x0
	bl FUN_02058CFC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205848C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205844C
	pop {r4-r6, pc}

	thumb_func_start FUN_0205829C
FUN_0205829C: ; 0x0205829C
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02058744
	add r0, r0, r4
	pop {r4, pc}

	thumb_func_start FUN_020582A8
FUN_020582A8: ; 0x020582A8
	push {r4-r6, lr}
	add r6, r1, #0x0
	mov r1, #0x1
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_0205842C
	cmp r0, #0x0
	bne _020582BE
	mov r0, #0x0
	pop {r4-r6, pc}
_020582BE:
	add r0, r5, #0x0
	bl FUN_02058448
	cmp r6, r0
	beq _020582CC
	mov r0, #0x0
	pop {r4-r6, pc}
_020582CC:
	add r0, r5, #0x0
	bl FUN_02058450
	cmp r4, r0
	beq _020582F2
	add r0, r5, #0x0
	bl FUN_020589CC
	cmp r0, #0x0
	bne _020582E4
	mov r0, #0x0
	pop {r4-r6, pc}
_020582E4:
	add r0, r5, #0x0
	bl FUN_02058750
	cmp r4, r0
	beq _020582F2
	mov r0, #0x0
	pop {r4-r6, pc}
_020582F2:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020582F8
FUN_020582F8: ; 0x020582F8
	push {r3-r7, lr}
	add r4, r1, #0x0
	mov r1, #0x1
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_0205842C
	cmp r0, #0x0
	bne _02058310
	mov r0, #0x0
	pop {r3-r7, pc}
_02058310:
	add r0, r5, #0x0
	bl FUN_0205845C
	cmp r0, r4
	beq _0205831E
	mov r0, #0x0
	pop {r3-r7, pc}
_0205831E:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020582A8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0205832C
FUN_0205832C: ; 0x0205832C
	push {r4, lr}
	add r4, r1, #0x0
	add r0, r4, #0x0
	bl FUN_02058EF8
	add r0, r4, #0x0
	bl FUN_02058830
	cmp r0, #0x0
	beq _02058346
	add r0, r4, #0x0
	bl FUN_02058348
_02058346:
	pop {r4, pc}

	thumb_func_start FUN_02058348
FUN_02058348: ; 0x02058348
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058578
	bl FUN_020587E0
	cmp r0, #0x1
	bne _0205835E
	add r0, r4, #0x0
	bl MOD05_021F1D8C
_0205835E:
	pop {r4, pc}

	thumb_func_start FUN_02058360
FUN_02058360: ; 0x02058360
	bx lr
	.balign 4

	thumb_func_start FUN_02058364
FUN_02058364: ; 0x02058364
	str r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02058368
FUN_02058368: ; 0x02058368
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0205836C
FUN_0205836C: ; 0x0205836C
	ldr r1, [r0, #0x8]
	add r1, r1, #0x1
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02058374
FUN_02058374: ; 0x02058374
	ldr r1, [r0, #0x8]
	sub r1, r1, #0x1
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start FUN_0205837C
FUN_0205837C: ; 0x0205837C
	ldr r2, [r0, #0x0]
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02058384
FUN_02058384: ; 0x02058384
	ldr r2, [r0, #0x0]
	mvn r1, r1
	and r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058390
FUN_02058390: ; 0x02058390
	ldr r0, [r0, #0x0]
	and r0, r1
	bx lr
	.balign 4

	thumb_func_start FUN_02058398
FUN_02058398: ; 0x02058398
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start FUN_0205839C
FUN_0205839C: ; 0x0205839C
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_020583A0
FUN_020583A0: ; 0x020583A0
	add r0, #0x18
	bx lr

	thumb_func_start FUN_020583A4
FUN_020583A4: ; 0x020583A4
	mov r2, #0x12
	lsl r2, r2, #0x4
	str r1, [r0, r2]
	bx lr

	thumb_func_start FUN_020583AC
FUN_020583AC: ; 0x020583AC
	mov r1, #0x12
	lsl r1, r1, #0x4
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start FUN_020583B4
FUN_020583B4: ; 0x020583B4
	mov r2, #0x49
	lsl r2, r2, #0x2
	str r1, [r0, r2]
	bx lr

	thumb_func_start FUN_020583BC
FUN_020583BC: ; 0x020583BC
	mov r1, #0x49
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start FUN_020583C4
FUN_020583C4: ; 0x020583C4
	mov r1, #0x49
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start FUN_020583CC
FUN_020583CC: ; 0x020583CC
	mov r1, #0x49
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start FUN_020583D4
FUN_020583D4: ; 0x020583D4
	mov r1, #0x4a
	ldr r2, [r0, #0x0]
	lsl r1, r1, #0x2
	add r1, r2, r1
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_020583E0
FUN_020583E0: ; 0x020583E0
	mov r2, #0x4a
	lsl r2, r2, #0x2
	str r1, [r0, r2]
	bx lr

	thumb_func_start FUN_020583E8
FUN_020583E8: ; 0x020583E8
	mov r1, #0x4a
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start FUN_020583F0
FUN_020583F0: ; 0x020583F0
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start FUN_020583F4
FUN_020583F4: ; 0x020583F4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	bne _02058402
	bl ErrorHandling
_02058402:
	ldr r0, [r4, #0x14]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02058408
FUN_02058408: ; 0x02058408
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0205840C
FUN_0205840C: ; 0x0205840C
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02058410
FUN_02058410: ; 0x02058410
	ldr r2, [r0, #0x0]
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02058418
FUN_02058418: ; 0x02058418
	ldr r2, [r0, #0x0]
	mvn r1, r1
	and r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058424
FUN_02058424: ; 0x02058424
	ldr r0, [r0, #0x0]
	and r0, r1
	bx lr
	.balign 4

	thumb_func_start FUN_0205842C
FUN_0205842C: ; 0x0205842C
	ldr r0, [r0, #0x0]
	tst r0, r1
	beq _02058436
	mov r0, #0x1
	bx lr
_02058436:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0205843C
FUN_0205843C: ; 0x0205843C
	str r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02058440
FUN_02058440: ; 0x02058440
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02058444
FUN_02058444: ; 0x02058444
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02058448
FUN_02058448: ; 0x02058448
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_0205844C
FUN_0205844C: ; 0x0205844C
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start FUN_02058450
FUN_02058450: ; 0x02058450
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_02058454
FUN_02058454: ; 0x02058454
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start FUN_02058458
FUN_02058458: ; 0x02058458
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start FUN_0205845C
FUN_0205845C: ; 0x0205845C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02058458
	add r4, r0, #0x0
	bl FUN_0205C334
	cmp r0, #0x1
	bne _02058476
	add r0, r5, #0x0
	bl FUN_0205C340
	add r4, r0, #0x0
_02058476:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205847C
FUN_0205847C: ; 0x0205847C
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start FUN_02058480
FUN_02058480: ; 0x02058480
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start FUN_02058484
FUN_02058484: ; 0x02058484
	str r1, [r0, #0x18]
	bx lr

	thumb_func_start FUN_02058488
FUN_02058488: ; 0x02058488
	ldr r0, [r0, #0x18]
	bx lr

	thumb_func_start FUN_0205848C
FUN_0205848C: ; 0x0205848C
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_02058490
FUN_02058490: ; 0x02058490
	ldr r0, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_02058494
FUN_02058494: ; 0x02058494
	str r1, [r0, #0x20]
	bx lr

	thumb_func_start FUN_02058498
FUN_02058498: ; 0x02058498
	ldr r0, [r0, #0x20]
	bx lr

	thumb_func_start FUN_0205849C
FUN_0205849C: ; 0x0205849C
	str r1, [r0, #0x24]
	bx lr

	thumb_func_start FUN_020584A0
FUN_020584A0: ; 0x020584A0
	ldr r0, [r0, #0x24]
	bx lr

	thumb_func_start FUN_020584A4
FUN_020584A4: ; 0x020584A4
	ldr r2, [r0, #0x28]
	str r2, [r0, #0x30]
	str r1, [r0, #0x28]
	bx lr

	thumb_func_start FUN_020584AC
FUN_020584AC: ; 0x020584AC
	push {r3-r5, lr}
	add r4, r1, #0x0
	mov r1, #0x80
	add r5, r0, #0x0
	bl FUN_02058424
	cmp r0, #0x0
	bne _020584C2
	ldr r0, [r5, #0x28]
	str r0, [r5, #0x30]
	str r4, [r5, #0x28]
_020584C2:
	pop {r3-r5, pc}

	thumb_func_start FUN_020584C4
FUN_020584C4: ; 0x020584C4
	ldr r0, [r0, #0x28]
	bx lr

	thumb_func_start FUN_020584C8
FUN_020584C8: ; 0x020584C8
	ldr r0, [r0, #0x30]
	bx lr

	thumb_func_start FUN_020584CC
FUN_020584CC: ; 0x020584CC
	ldr r2, [r0, #0x2c]
	str r2, [r0, #0x34]
	str r1, [r0, #0x2c]
	bx lr

	thumb_func_start FUN_020584D4
FUN_020584D4: ; 0x020584D4
	ldr r0, [r0, #0x2c]
	bx lr

	thumb_func_start FUN_020584D8
FUN_020584D8: ; 0x020584D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020584AC
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020584CC
	pop {r3-r5, pc}

	thumb_func_start FUN_020584EC
FUN_020584EC: ; 0x020584EC
	push {r3, lr}
	cmp r2, #0x0
	beq _020584FC
	cmp r2, #0x1
	beq _02058500
	cmp r2, #0x2
	beq _02058504
	b _02058508
_020584FC:
	str r1, [r0, #0x38]
	pop {r3, pc}
_02058500:
	str r1, [r0, #0x3c]
	pop {r3, pc}
_02058504:
	str r1, [r0, #0x40]
	pop {r3, pc}
_02058508:
	bl ErrorHandling
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058510
FUN_02058510: ; 0x02058510
	push {r3, lr}
	cmp r1, #0x0
	beq _02058520
	cmp r1, #0x1
	beq _02058524
	cmp r1, #0x2
	beq _02058528
	b _0205852C
_02058520:
	ldr r0, [r0, #0x38]
	pop {r3, pc}
_02058524:
	ldr r0, [r0, #0x3c]
	pop {r3, pc}
_02058528:
	ldr r0, [r0, #0x40]
	pop {r3, pc}
_0205852C:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02058534
FUN_02058534: ; 0x02058534
	str r1, [r0, #0x44]
	bx lr

	thumb_func_start FUN_02058538
FUN_02058538: ; 0x02058538
	ldr r0, [r0, #0x44]
	bx lr

	thumb_func_start FUN_0205853C
FUN_0205853C: ; 0x0205853C
	str r1, [r0, #0x48]
	bx lr

	thumb_func_start FUN_02058540
FUN_02058540: ; 0x02058540
	ldr r0, [r0, #0x48]
	bx lr

	thumb_func_start FUN_02058544
FUN_02058544: ; 0x02058544
	add r0, #0xa0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0205854C
FUN_0205854C: ; 0x0205854C
	add r0, #0xa0
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058554
FUN_02058554: ; 0x02058554
	add r0, #0xb0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0205855C
FUN_0205855C: ; 0x0205855C
	add r0, #0xb0
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058564
FUN_02058564: ; 0x02058564
	push {r3, lr}
	bl FUN_0205855C
	bl FUN_0200CAB4
	pop {r3, pc}

	thumb_func_start FUN_02058570
FUN_02058570: ; 0x02058570
	add r0, #0xb4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058578
FUN_02058578: ; 0x02058578
	add r0, #0xb4
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058580
FUN_02058580: ; 0x02058580
	ldr r3, _02058588 ; =FUN_02058360
	add r0, #0xb4
	ldr r0, [r0, #0x0]
	bx r3
	.balign 4
_02058588: .word FUN_02058360

	thumb_func_start FUN_0205858C
FUN_0205858C: ; 0x0205858C
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x10
	ble _0205859A
	bl ErrorHandling
_0205859A:
	add r0, r4, #0x0
	bl FUN_020585B0
	mov r1, #0x0
	add r2, r5, #0x0
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020585B0
FUN_020585B0: ; 0x020585B0
	add r0, #0xd8
	bx lr

	thumb_func_start FUN_020585B4
FUN_020585B4: ; 0x020585B4
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x10
	ble _020585C2
	bl ErrorHandling
_020585C2:
	add r0, r4, #0x0
	bl FUN_020585D8
	mov r1, #0x0
	add r2, r5, #0x0
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020585D8
FUN_020585D8: ; 0x020585D8
	add r0, #0xe8
	bx lr

	thumb_func_start FUN_020585DC
FUN_020585DC: ; 0x020585DC
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x10
	ble _020585EA
	bl ErrorHandling
_020585EA:
	add r0, r4, #0x0
	bl FUN_02058600
	mov r1, #0x0
	add r2, r5, #0x0
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02058600
FUN_02058600: ; 0x02058600
	add r0, #0xf8
	bx lr

	thumb_func_start FUN_02058604
FUN_02058604: ; 0x02058604
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x20
	ble _02058612
	bl ErrorHandling
_02058612:
	add r0, r4, #0x0
	bl FUN_02058628
	mov r1, #0x0
	add r2, r5, #0x0
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02058628
FUN_02058628: ; 0x02058628
	mov r1, #0x42
	lsl r1, r1, #0x2
	add r0, r0, r1
	bx lr

	thumb_func_start FUN_02058630
FUN_02058630: ; 0x02058630
	add r0, #0xb8
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058638
FUN_02058638: ; 0x02058638
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xb8
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start FUN_02058644
FUN_02058644: ; 0x02058644
	add r0, #0xbc
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0205864C
FUN_0205864C: ; 0x0205864C
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xbc
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start FUN_02058658
FUN_02058658: ; 0x02058658
	add r0, #0xc0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058660
FUN_02058660: ; 0x02058660
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xc0
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start FUN_0205866C
FUN_0205866C: ; 0x0205866C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058480
	bl FUN_02058D14
	add r1, r0, #0x0
	ldr r1, [r1, #0x10]
	add r0, r4, #0x0
	blx r1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02058684
FUN_02058684: ; 0x02058684
	add r0, #0xc4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0205868C
FUN_0205868C: ; 0x0205868C
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xc4
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start FUN_02058698
FUN_02058698: ; 0x02058698
	add r0, #0xc8
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020586A0
FUN_020586A0: ; 0x020586A0
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xc8
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start FUN_020586AC
FUN_020586AC: ; 0x020586AC
	add r0, #0xcc
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020586B4
FUN_020586B4: ; 0x020586B4
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xcc
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start FUN_020586C0
FUN_020586C0: ; 0x020586C0
	add r0, #0xd0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020586C8
FUN_020586C8: ; 0x020586C8
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xd0
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start FUN_020586D4
FUN_020586D4: ; 0x020586D4
	add r0, #0xd4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020586DC
FUN_020586DC: ; 0x020586DC
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xd4
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start FUN_020586E8
FUN_020586E8: ; 0x020586E8
	add r0, #0xa4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020586F0
FUN_020586F0: ; 0x020586F0
	add r0, #0xa4
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020586F8
FUN_020586F8: ; 0x020586F8
	add r0, #0xa8
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058700
FUN_02058700: ; 0x02058700
	add r1, r0, #0x0
	add r1, #0xa8
	ldr r1, [r1, #0x0]
	add r0, #0xa8
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058710
FUN_02058710: ; 0x02058710
	add r0, #0xa8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058718
FUN_02058718: ; 0x02058718
	add r0, #0xac
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058720
FUN_02058720: ; 0x02058720
	add r0, #0xac
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058728
FUN_02058728: ; 0x02058728
	add r0, #0xae
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058730
FUN_02058730: ; 0x02058730
	add r0, #0xae
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02058738
FUN_02058738: ; 0x02058738
	push {r3, lr}
	bl FUN_02058580
	bl FUN_020583E8
	pop {r3, pc}

	thumb_func_start FUN_02058744
FUN_02058744: ; 0x02058744
	push {r3, lr}
	bl FUN_02058578
	bl FUN_0205839C
	pop {r3, pc}

	thumb_func_start FUN_02058750
FUN_02058750: ; 0x02058750
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020589CC
	cmp r0, #0x1
	beq _02058760
	bl ErrorHandling
_02058760:
	add r0, r4, #0x0
	bl FUN_02058490
	pop {r4, pc}

	thumb_func_start FUN_02058768
FUN_02058768: ; 0x02058768
	ldr r3, _02058770 ; =FUN_0205837C
	mov r1, #0x6
	bx r3
	nop
_02058770: .word FUN_0205837C

	thumb_func_start FUN_02058774
FUN_02058774: ; 0x02058774
	ldr r3, _0205877C ; =FUN_02058384
	mov r1, #0x6
	bx r3
	nop
_0205877C: .word FUN_02058384

	thumb_func_start FUN_02058780
FUN_02058780: ; 0x02058780
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02058368
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020583CC
	mov r6, #0x4a
	add r5, r0, #0x0
	lsl r6, r6, #0x2
_02058796:
	add r0, r5, #0x0
	bl FUN_02058830
	cmp r0, #0x0
	beq _020587A6
	add r0, r5, #0x0
	bl FUN_02058908
_020587A6:
	add r5, r5, r6
	sub r4, r4, #0x1
	bne _02058796
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020587B0
FUN_020587B0: ; 0x020587B0
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02058368
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020583CC
	mov r6, #0x4a
	add r5, r0, #0x0
	lsl r6, r6, #0x2
_020587C6:
	add r0, r5, #0x0
	bl FUN_02058830
	cmp r0, #0x0
	beq _020587D6
	add r0, r5, #0x0
	bl FUN_02058914
_020587D6:
	add r5, r5, r6
	sub r4, r4, #0x1
	bne _020587C6
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020587E0
FUN_020587E0: ; 0x020587E0
	push {r3, lr}
	mov r1, #0x1
	bl FUN_02058390
	cmp r0, #0x0
	beq _020587F0
	mov r0, #0x1
	pop {r3, pc}
_020587F0:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_020587F4
FUN_020587F4: ; 0x020587F4
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02058578
	add r1, r4, #0x0
	bl FUN_02058390
	pop {r4, pc}

	thumb_func_start FUN_02058804
FUN_02058804: ; 0x02058804
	push {r3, lr}
	cmp r1, #0x0
	bne _02058812
	mov r1, #0x8
	bl FUN_0205837C
	pop {r3, pc}
_02058812:
	mov r1, #0x8
	bl FUN_02058384
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205881C
FUN_0205881C: ; 0x0205881C
	push {r3, lr}
	mov r1, #0x8
	bl FUN_02058390
	cmp r0, #0x0
	bne _0205882C
	mov r0, #0x1
	pop {r3, pc}
_0205882C:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02058830
FUN_02058830: ; 0x02058830
	ldr r3, _02058838 ; =FUN_0205842C
	mov r1, #0x1
	bx r3
	nop
_02058838: .word FUN_0205842C

	thumb_func_start FUN_0205883C
FUN_0205883C: ; 0x0205883C
	ldr r3, _02058844 ; =FUN_02058410
	mov r1, #0x2
	bx r3
	nop
_02058844: .word FUN_02058410

	thumb_func_start FUN_02058848
FUN_02058848: ; 0x02058848
	ldr r3, _02058850 ; =FUN_02058418
	mov r1, #0x2
	bx r3
	nop
_02058850: .word FUN_02058418

	thumb_func_start FUN_02058854
FUN_02058854: ; 0x02058854
	ldr r3, _0205885C ; =FUN_0205842C
	mov r1, #0x2
	bx r3
	nop
_0205885C: .word FUN_0205842C

	thumb_func_start FUN_02058860
FUN_02058860: ; 0x02058860
	ldr r3, _02058868 ; =FUN_02058410
	mov r1, #0x4
	bx r3
	nop
_02058868: .word FUN_02058410

	thumb_func_start FUN_0205886C
FUN_0205886C: ; 0x0205886C
	ldr r3, _02058874 ; =FUN_02058418
	mov r1, #0x8
	bx r3
	nop
_02058874: .word FUN_02058418

	thumb_func_start FUN_02058878
FUN_02058878: ; 0x02058878
	ldr r3, _02058880 ; =FUN_02058410
	mov r1, #0x1
	lsl r1, r1, #0xe
	bx r3
	.balign 4
_02058880: .word FUN_02058410

	thumb_func_start FUN_02058884
FUN_02058884: ; 0x02058884
	ldr r3, _0205888C ; =FUN_0205842C
	mov r1, #0x1
	lsl r1, r1, #0xe
	bx r3
	.balign 4
_0205888C: .word FUN_0205842C

	thumb_func_start FUN_02058890
FUN_02058890: ; 0x02058890
	ldr r3, _02058898 ; =FUN_0205842C
	mov r1, #0x2
	lsl r1, r1, #0x8
	bx r3
	.balign 4
_02058898: .word FUN_0205842C

	thumb_func_start FUN_0205889C
FUN_0205889C: ; 0x0205889C
	push {r3, lr}
	cmp r1, #0x1
	bne _020588AC
	mov r1, #0x2
	lsl r1, r1, #0x8
	bl FUN_02058410
	pop {r3, pc}
_020588AC:
	mov r1, #0x2
	lsl r1, r1, #0x8
	bl FUN_02058418
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020588B8
FUN_020588B8: ; 0x020588B8
	push {r3, lr}
	cmp r1, #0x1
	bne _020588C8
	mov r1, #0x1
	lsl r1, r1, #0x12
	bl FUN_02058418
	pop {r3, pc}
_020588C8:
	mov r1, #0x1
	lsl r1, r1, #0x12
	bl FUN_02058410
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020588D4
FUN_020588D4: ; 0x020588D4
	push {r3, lr}
	mov r1, #0x2
	lsl r1, r1, #0x12
	bl FUN_0205842C
	cmp r0, #0x1
	beq _020588E6
	mov r0, #0x1
	pop {r3, pc}
_020588E6:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020588EC
FUN_020588EC: ; 0x020588EC
	push {r3, lr}
	cmp r1, #0x1
	bne _020588FC
	mov r1, #0x2
	lsl r1, r1, #0x12
	bl FUN_02058410
	pop {r3, pc}
_020588FC:
	mov r1, #0x2
	lsl r1, r1, #0x12
	bl FUN_02058418
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058908
FUN_02058908: ; 0x02058908
	ldr r3, _02058910 ; =FUN_02058410
	mov r1, #0x40
	bx r3
	nop
_02058910: .word FUN_02058410

	thumb_func_start FUN_02058914
FUN_02058914: ; 0x02058914
	ldr r3, _0205891C ; =FUN_02058418
	mov r1, #0x40
	bx r3
	nop
_0205891C: .word FUN_02058418

	thumb_func_start FUN_02058920
FUN_02058920: ; 0x02058920
	push {r3, lr}
	mov r1, #0x40
	bl FUN_0205842C
	cmp r0, #0x1
	bne _02058930
	mov r0, #0x1
	pop {r3, pc}
_02058930:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02058934
FUN_02058934: ; 0x02058934
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058578
	bl FUN_020587E0
	cmp r0, #0x0
	bne _02058948
	mov r0, #0x0
	pop {r4, pc}
_02058948:
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0xe
	bl FUN_02058424
	cmp r0, #0x0
	beq _0205895A
	mov r0, #0x1
	pop {r4, pc}
_0205895A:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02058960
FUN_02058960: ; 0x02058960
	push {r3, lr}
	cmp r1, #0x1
	bne _02058970
	mov r1, #0x2
	lsl r1, r1, #0x16
	bl FUN_02058410
	pop {r3, pc}
_02058970:
	mov r1, #0x2
	lsl r1, r1, #0x16
	bl FUN_02058418
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205897C
FUN_0205897C: ; 0x0205897C
	push {r3, lr}
	mov r1, #0x2
	lsl r1, r1, #0x16
	bl FUN_02058424
	cmp r0, #0x0
	beq _0205898E
	mov r0, #0x1
	pop {r3, pc}
_0205898E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058994
FUN_02058994: ; 0x02058994
	push {r3, lr}
	cmp r1, #0x1
	bne _020589A4
	mov r1, #0x1
	lsl r1, r1, #0xa
	bl FUN_02058410
	pop {r3, pc}
_020589A4:
	mov r1, #0x1
	lsl r1, r1, #0xa
	bl FUN_02058418
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020589B0
FUN_020589B0: ; 0x020589B0
	push {r3, lr}
	cmp r1, #0x1
	bne _020589C0
	mov r1, #0x2
	lsl r1, r1, #0x18
	bl FUN_02058410
	pop {r3, pc}
_020589C0:
	mov r1, #0x2
	lsl r1, r1, #0x18
	bl FUN_02058418
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020589CC
FUN_020589CC: ; 0x020589CC
	push {r3, lr}
	mov r1, #0x2
	lsl r1, r1, #0x18
	bl FUN_02058424
	cmp r0, #0x0
	beq _020589DE
	mov r0, #0x1
	pop {r3, pc}
_020589DE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020589E4
FUN_020589E4: ; 0x020589E4
	push {r3, lr}
	cmp r1, #0x1
	bne _020589F4
	mov r1, #0x1
	lsl r1, r1, #0x1a
	bl FUN_02058410
	pop {r3, pc}
_020589F4:
	mov r1, #0x1
	lsl r1, r1, #0x1a
	bl FUN_02058418
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058A00
FUN_02058A00: ; 0x02058A00
	push {r3, lr}
	mov r1, #0x1
	lsl r1, r1, #0x1a
	bl FUN_02058424
	cmp r0, #0x0
	beq _02058A12
	mov r0, #0x1
	pop {r3, pc}
_02058A12:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058A18
FUN_02058A18: ; 0x02058A18
	push {r3, lr}
	cmp r1, #0x1
	bne _02058A28
	mov r1, #0x2
	lsl r1, r1, #0x1a
	bl FUN_02058410
	pop {r3, pc}
_02058A28:
	mov r1, #0x2
	lsl r1, r1, #0x1a
	bl FUN_02058418
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058A34
FUN_02058A34: ; 0x02058A34
	push {r3, lr}
	mov r1, #0x2
	lsl r1, r1, #0x1a
	bl FUN_02058424
	cmp r0, #0x0
	beq _02058A46
	mov r0, #0x1
	pop {r3, pc}
_02058A46:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058A4C
FUN_02058A4C: ; 0x02058A4C
	push {r3, lr}
	cmp r1, #0x1
	bne _02058A5C
	mov r1, #0x1
	lsl r1, r1, #0x1c
	bl FUN_02058410
	pop {r3, pc}
_02058A5C:
	mov r1, #0x1
	lsl r1, r1, #0x1c
	bl FUN_02058418
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058A68
FUN_02058A68: ; 0x02058A68
	push {r3, lr}
	mov r1, #0x1
	lsl r1, r1, #0x1c
	bl FUN_02058424
	cmp r0, #0x0
	beq _02058A7A
	mov r0, #0x1
	pop {r3, pc}
_02058A7A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058A80
FUN_02058A80: ; 0x02058A80
	push {r3, lr}
	cmp r1, #0x1
	bne _02058A90
	mov r1, #0x1
	lsl r1, r1, #0x18
	bl FUN_02058410
	pop {r3, pc}
_02058A90:
	mov r1, #0x1
	lsl r1, r1, #0x18
	bl FUN_02058418
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058A9C
FUN_02058A9C: ; 0x02058A9C
	push {r3, lr}
	mov r1, #0x1
	lsl r1, r1, #0x18
	bl FUN_02058424
	cmp r0, #0x0
	beq _02058AAE
	mov r0, #0x1
	pop {r3, pc}
_02058AAE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058AB4
FUN_02058AB4: ; 0x02058AB4
	push {r3, lr}
	mov r1, #0x10
	bl FUN_02058424
	cmp r0, #0x0
	beq _02058AC4
	mov r0, #0x1
	pop {r3, pc}
_02058AC4:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02058AC8
FUN_02058AC8: ; 0x02058AC8
	push {r3, lr}
	cmp r1, #0x1
	bne _02058AD8
	mov r1, #0x2
	lsl r1, r1, #0x1c
	bl FUN_02058410
	pop {r3, pc}
_02058AD8:
	mov r1, #0x2
	lsl r1, r1, #0x1c
	bl FUN_02058418
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058AE4
FUN_02058AE4: ; 0x02058AE4
	push {r3, lr}
	mov r1, #0x2
	lsl r1, r1, #0x1c
	bl FUN_02058424
	cmp r0, #0x0
	beq _02058AF6
	mov r0, #0x1
	pop {r3, pc}
_02058AF6:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058AFC
FUN_02058AFC: ; 0x02058AFC
	ldr r0, [r0, #0x4c]
	bx lr

	thumb_func_start FUN_02058B00
FUN_02058B00: ; 0x02058B00
	str r1, [r0, #0x4c]
	bx lr

	thumb_func_start FUN_02058B04
FUN_02058B04: ; 0x02058B04
	ldr r0, [r0, #0x50]
	bx lr

	thumb_func_start FUN_02058B08
FUN_02058B08: ; 0x02058B08
	str r1, [r0, #0x50]
	bx lr

	thumb_func_start FUN_02058B0C
FUN_02058B0C: ; 0x02058B0C
	ldr r0, [r0, #0x54]
	bx lr

	thumb_func_start FUN_02058B10
FUN_02058B10: ; 0x02058B10
	str r1, [r0, #0x54]
	bx lr

	thumb_func_start FUN_02058B14
FUN_02058B14: ; 0x02058B14
	ldr r0, [r0, #0x58]
	bx lr

	thumb_func_start FUN_02058B18
FUN_02058B18: ; 0x02058B18
	str r1, [r0, #0x58]
	bx lr

	thumb_func_start FUN_02058B1C
FUN_02058B1C: ; 0x02058B1C
	ldr r0, [r0, #0x5c]
	bx lr

	thumb_func_start FUN_02058B20
FUN_02058B20: ; 0x02058B20
	str r1, [r0, #0x5c]
	bx lr

	thumb_func_start FUN_02058B24
FUN_02058B24: ; 0x02058B24
	ldr r0, [r0, #0x60]
	bx lr

	thumb_func_start FUN_02058B28
FUN_02058B28: ; 0x02058B28
	str r1, [r0, #0x60]
	bx lr

	thumb_func_start FUN_02058B2C
FUN_02058B2C: ; 0x02058B2C
	ldr r0, [r0, #0x64]
	bx lr

	thumb_func_start FUN_02058B30
FUN_02058B30: ; 0x02058B30
	str r1, [r0, #0x64]
	bx lr

	thumb_func_start FUN_02058B34
FUN_02058B34: ; 0x02058B34
	ldr r2, [r0, #0x64]
	add r1, r2, r1
	str r1, [r0, #0x64]
	bx lr

	thumb_func_start FUN_02058B3C
FUN_02058B3C: ; 0x02058B3C
	ldr r0, [r0, #0x68]
	bx lr

	thumb_func_start FUN_02058B40
FUN_02058B40: ; 0x02058B40
	str r1, [r0, #0x68]
	bx lr

	thumb_func_start FUN_02058B44
FUN_02058B44: ; 0x02058B44
	ldr r2, [r0, #0x68]
	add r1, r2, r1
	str r1, [r0, #0x68]
	bx lr

	thumb_func_start FUN_02058B4C
FUN_02058B4C: ; 0x02058B4C
	ldr r0, [r0, #0x6c]
	bx lr

	thumb_func_start FUN_02058B50
FUN_02058B50: ; 0x02058B50
	str r1, [r0, #0x6c]
	bx lr

	thumb_func_start FUN_02058B54
FUN_02058B54: ; 0x02058B54
	ldr r2, [r0, #0x6c]
	add r1, r2, r1
	str r1, [r0, #0x6c]
	bx lr

	thumb_func_start FUN_02058B5C
FUN_02058B5C: ; 0x02058B5C
	add r2, r0, #0x0
	add r2, #0x70
	add r3, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start FUN_02058B6C
FUN_02058B6C: ; 0x02058B6C
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x70
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_02058B7C
FUN_02058B7C: ; 0x02058B7C
	add r0, #0x70
	bx lr

	thumb_func_start FUN_02058B80
FUN_02058B80: ; 0x02058B80
	ldr r0, [r0, #0x74]
	bx lr

	thumb_func_start FUN_02058B84
FUN_02058B84: ; 0x02058B84
	add r2, r0, #0x0
	add r2, #0x7c
	add r3, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start FUN_02058B94
FUN_02058B94: ; 0x02058B94
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x7c
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_02058BA4
FUN_02058BA4: ; 0x02058BA4
	add r2, r0, #0x0
	add r2, #0x88
	add r3, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start FUN_02058BB4
FUN_02058BB4: ; 0x02058BB4
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x88
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_02058BC4
FUN_02058BC4: ; 0x02058BC4
	add r2, r0, #0x0
	add r2, #0x94
	add r3, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start FUN_02058BD4
FUN_02058BD4: ; 0x02058BD4
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x94
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_02058BE4
FUN_02058BE4: ; 0x02058BE4
	push {r3, lr}
	bl FUN_02058B80
	asr r1, r0, #0x3
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058BF8
FUN_02058BF8: ; 0x02058BF8
	strh r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02058BFC
FUN_02058BFC: ; 0x02058BFC
	ldrh r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02058C00
FUN_02058C00: ; 0x02058C00
	strh r1, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02058C04
FUN_02058C04: ; 0x02058C04
	ldrh r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02058C08
FUN_02058C08: ; 0x02058C08
	strh r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02058C0C
FUN_02058C0C: ; 0x02058C0C
	ldrh r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02058C10
FUN_02058C10: ; 0x02058C10
	strh r1, [r0, #0x6]
	bx lr

	thumb_func_start FUN_02058C14
FUN_02058C14: ; 0x02058C14
	ldrh r0, [r0, #0x6]
	bx lr

	thumb_func_start FUN_02058C18
FUN_02058C18: ; 0x02058C18
	strh r1, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02058C1C
FUN_02058C1C: ; 0x02058C1C
	ldrh r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02058C20
FUN_02058C20: ; 0x02058C20
	strh r1, [r0, #0xa]
	bx lr

	thumb_func_start FUN_02058C24
FUN_02058C24: ; 0x02058C24
	ldrh r0, [r0, #0xa]
	bx lr

	thumb_func_start FUN_02058C28
FUN_02058C28: ; 0x02058C28
	strh r1, [r0, #0xc]
	bx lr

	thumb_func_start FUN_02058C2C
FUN_02058C2C: ; 0x02058C2C
	mov r1, #0xc
	ldrsh r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start FUN_02058C34
FUN_02058C34: ; 0x02058C34
	push {r3, lr}
	cmp r2, #0x0
	beq _02058C44
	cmp r2, #0x1
	beq _02058C48
	cmp r2, #0x2
	beq _02058C4C
	b _02058C50
_02058C44:
	strh r1, [r0, #0xe]
	pop {r3, pc}
_02058C48:
	strh r1, [r0, #0x10]
	pop {r3, pc}
_02058C4C:
	strh r1, [r0, #0x12]
	pop {r3, pc}
_02058C50:
	bl ErrorHandling
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02058C58
FUN_02058C58: ; 0x02058C58
	push {r3, lr}
	cmp r1, #0x0
	beq _02058C68
	cmp r1, #0x1
	beq _02058C6C
	cmp r1, #0x2
	beq _02058C70
	b _02058C74
_02058C68:
	ldrh r0, [r0, #0xe]
	pop {r3, pc}
_02058C6C:
	ldrh r0, [r0, #0x10]
	pop {r3, pc}
_02058C70:
	ldrh r0, [r0, #0x12]
	pop {r3, pc}
_02058C74:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02058C7C
FUN_02058C7C: ; 0x02058C7C
	strh r1, [r0, #0x14]
	bx lr

	thumb_func_start FUN_02058C80
FUN_02058C80: ; 0x02058C80
	mov r1, #0x14
	ldrsh r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start FUN_02058C88
FUN_02058C88: ; 0x02058C88
	strh r1, [r0, #0x16]
	bx lr

	thumb_func_start FUN_02058C8C
FUN_02058C8C: ; 0x02058C8C
	mov r1, #0x16
	ldrsh r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start FUN_02058C94
FUN_02058C94: ; 0x02058C94
	strh r1, [r0, #0x18]
	bx lr

	thumb_func_start FUN_02058C98
FUN_02058C98: ; 0x02058C98
	ldrh r0, [r0, #0x18]
	bx lr

	thumb_func_start FUN_02058C9C
FUN_02058C9C: ; 0x02058C9C
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_02058CA0
FUN_02058CA0: ; 0x02058CA0
	ldr r0, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_02058CA4
FUN_02058CA4: ; 0x02058CA4
	strh r1, [r0, #0x1a]
	bx lr

	thumb_func_start FUN_02058CA8
FUN_02058CA8: ; 0x02058CA8
	ldrh r0, [r0, #0x1a]
	bx lr

	thumb_func_start FUN_02058CAC
FUN_02058CAC: ; 0x02058CAC
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r7, r1, #0x0
	str r2, [sp, #0x0]
	mov r4, #0x0
	add r5, r2, #0x0
_02058CB8:
	add r0, r5, #0x0
	bl FUN_02058CE0
	cmp r0, #0x0
	bne _02058CD4
	add r0, r5, #0x0
	bl FUN_02058BFC
	cmp r6, r0
	bne _02058CD4
	ldr r0, [sp, #0x0]
	lsl r1, r4, #0x5
	add r0, r0, r1
	pop {r3-r7, pc}
_02058CD4:
	add r4, r4, #0x1
	add r5, #0x20
	cmp r4, r7
	blt _02058CB8
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02058CE0
FUN_02058CE0: ; 0x02058CE0
	push {r3, lr}
	bl FUN_02058C24
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, _02058CF8 ; =0x0000FFFF
	cmp r1, r0
	bne _02058CF4
	mov r0, #0x1
	pop {r3, pc}
_02058CF4:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02058CF8: .word 0x0000FFFF

	thumb_func_start FUN_02058CFC
FUN_02058CFC: ; 0x02058CFC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058CE0
	cmp r0, #0x1
	beq _02058D0C
	bl ErrorHandling
_02058D0C:
	add r0, r4, #0x0
	bl FUN_02058C1C
	pop {r4, pc}

	thumb_func_start FUN_02058D14
FUN_02058D14: ; 0x02058D14
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x37
	blo _02058D20
	bl ErrorHandling
_02058D20:
	ldr r0, _02058D28 ; =UNK_020F6364
	lsl r1, r4, #0x2
	ldr r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02058D28: .word UNK_020F6364

	thumb_func_start FUN_02058D2C
FUN_02058D2C: ; 0x02058D2C
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02058D30
FUN_02058D30: ; 0x02058D30
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02058D34
FUN_02058D34: ; 0x02058D34
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_02058D38
FUN_02058D38: ; 0x02058D38
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02058D3C
FUN_02058D3C: ; 0x02058D3C
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02058D40
FUN_02058D40: ; 0x02058D40
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02058D44
FUN_02058D44: ; 0x02058D44
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_02058D48
FUN_02058D48: ; 0x02058D48
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start FUN_02058D4C
FUN_02058D4C: ; 0x02058D4C
	push {r3, lr}
	ldr r3, _02058D6C ; =UNK05_021F9494
	ldr r1, _02058D70 ; =0x0000FFFF
_02058D52:
	ldr r2, [r3, #0x0]
	cmp r2, r0
	bne _02058D5C
	ldr r0, [r3, #0x4]
	pop {r3, pc}
_02058D5C:
	add r3, #0x8
	ldr r2, [r3, #0x0]
	cmp r2, r1
	bne _02058D52
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02058D6C: .word UNK05_021F9494
_02058D70: .word 0x0000FFFF

	thumb_func_start FUN_02058D74
FUN_02058D74: ; 0x02058D74
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl FUN_02058368
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020583CC
	add r5, r0, #0x0
_02058D8A:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02058424
	cmp r0, #0x0
	beq _02058DAE
	add r0, r5, #0x0
	bl FUN_02058B2C
	cmp r6, r0
	bne _02058DAE
	add r0, r5, #0x0
	bl FUN_02058B4C
	cmp r7, r0
	bne _02058DAE
	add r0, r5, #0x0
	pop {r3-r7, pc}
_02058DAE:
	mov r0, #0x4a
	lsl r0, r0, #0x2
	add r5, r5, r0
	sub r4, r4, #0x1
	bne _02058D8A
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02058DBC
FUN_02058DBC: ; 0x02058DBC
	push {r4-r6, lr}
	add r4, r1, #0x0
	ldr r1, [r4, #0x0]
	add r6, r2, #0x0
	asr r2, r1, #0x4
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	add r5, r0, #0x0
	bl FUN_02058B30
	ldr r1, [r4, #0x4]
	add r0, r5, #0x0
	asr r2, r1, #0x3
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	bl FUN_02058B40
	ldr r1, [r4, #0x8]
	add r0, r5, #0x0
	asr r2, r1, #0x4
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	bl FUN_02058B50
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02058B6C
	add r0, r5, #0x0
	bl FUN_02059C60
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020584A4
	add r0, r5, #0x0
	bl FUN_0205AE80
	add r0, r5, #0x0
	mov r1, #0x4
	bl FUN_02058410
	add r0, r5, #0x0
	mov r1, #0xa
	bl FUN_02058418
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02058E28
FUN_02058E28: ; 0x02058E28
	push {r3-r6, lr}
	sub sp, #0xc
	add r4, r2, #0x0
	mov r2, #0x2
	add r6, r3, #0x0
	lsl r3, r1, #0x10
	lsl r2, r2, #0xe
	add r2, r3, r2
	add r5, r0, #0x0
	str r2, [sp, #0x0]
	bl FUN_02058B30
	lsl r0, r4, #0xf
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02058B40
	mov r0, #0x2
	lsl r1, r6, #0x10
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02058B50
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02058B6C
	add r0, r5, #0x0
	bl FUN_02059C60
	ldr r1, [sp, #0x20]
	add r0, r5, #0x0
	bl FUN_020584A4
	add r0, r5, #0x0
	mov r1, #0x4
	bl FUN_02058410
	add r0, r5, #0x0
	mov r1, #0xa
	bl FUN_02058418
	add r0, r5, #0x0
	bl FUN_0205AE80
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02058E90
FUN_02058E90: ; 0x02058E90
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02058660
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205847C
	add r0, r5, #0x0
	bl FUN_02057EE0
	add r0, r5, #0x0
	bl FUN_02058EE8
	pop {r3-r5, pc}

	thumb_func_start FUN_02058EB0
FUN_02058EB0: ; 0x02058EB0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058444
	add r0, r4, #0x0
	bl FUN_02058860
	add r0, r4, #0x0
	bl FUN_0205815C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02058EC8
FUN_02058EC8: ; 0x02058EC8
	bx lr
	.balign 4

	thumb_func_start FUN_02058ECC
FUN_02058ECC: ; 0x02058ECC
	bx lr
	.balign 4

	thumb_func_start FUN_02058ED0
FUN_02058ED0: ; 0x02058ED0
	bx lr
	.balign 4

	thumb_func_start FUN_02058ED4
FUN_02058ED4: ; 0x02058ED4
	bx lr
	.balign 4

	thumb_func_start FUN_02058ED8
FUN_02058ED8: ; 0x02058ED8
	bx lr
	.balign 4

	thumb_func_start FUN_02058EDC
FUN_02058EDC: ; 0x02058EDC
	bx lr
	.balign 4

	thumb_func_start FUN_02058EE0
FUN_02058EE0: ; 0x02058EE0
	bx lr
	.balign 4

	thumb_func_start FUN_02058EE4
FUN_02058EE4: ; 0x02058EE4
	bx lr
	.balign 4
