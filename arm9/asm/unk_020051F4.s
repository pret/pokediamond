    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_020051F4
FUN_020051F4: ; 0x020051F4
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_020048D0
	bl FUN_02004018
	add r4, r0, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	bl NNS_SndArcPlayerStartSeq
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0200526C
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200521C
FUN_0200521C: ; 0x0200521C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_020048D0
	add r4, r0, #0x0
	bl FUN_02004018
	add r6, r0, #0x0
	cmp r4, #0x7
	bne _0200523E
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02005288
	add r4, r0, #0x0
	b _02005258
_0200523E:
	cmp r4, #0x1
	bne _02005250
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020052B8
	add r4, r0, #0x0
	b _02005258
_02005250:
	bl ErrorHandling
	mov r0, #0x0
	pop {r4-r6, pc}
_02005258:
	mov r0, #0x0
	bl FUN_02004DBC
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0200526C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200526C
FUN_0200526C: ; 0x0200526C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02004110
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02004858
	mov r0, #0x1
	bl FUN_02003CE8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02005288
FUN_02005288: ; 0x02005288
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x3
	add r4, r2, #0x0
	bl FUN_02004748
	bl FUN_02003F64
	add r0, r5, #0x0
	bl FUN_02003F90
	mov r0, #0x1a
	bl FUN_02003D38
	bl FUN_02003F3C
	add r0, r4, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	bl NNS_SndArcPlayerStartSeq
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020052B8
FUN_020052B8: ; 0x020052B8
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	mov r0, #0x12
	add r6, r2, #0x0
	bl FUN_02003D38
	mov r0, #0x1f
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x0
	bl FUN_02003FF4
	bl FUN_020048EC
	bl FUN_02004900
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020045C4
	add r0, r6, #0x0
	bl FUN_02003FF4
	add r6, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_02004900
	mov r1, #0x0
	mvn r1, r1
	add r2, r0, #0x0
	add r0, r6, #0x0
	add r3, r1, #0x0
	str r5, [sp, #0x0]
	bl NNS_SndArcPlayerStartSeqEx
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02005308
FUN_02005308: ; 0x02005308
	push {r3-r5, lr}
	add r5, r1, #0x0
	cmp r0, #0x4
	beq _02005318
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_02005318:
	add r0, r5, #0x0
	bl FUN_020048D0
	cmp r0, #0x7
	beq _0200532A
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0200532A:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02003FA8
	mov r0, #0x7
	bl FUN_02003FF4
	add r1, r5, #0x0
	bl NNS_SndArcPlayerStartSeq
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02004110
	mov r0, #0x1
	bl FUN_02003CE8
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02005350
FUN_02005350: ; 0x02005350
	push {r4, lr}
	add r4, r0, #0x0
	bl NNS_SndPlayerStopSeqBySeqNo
	add r0, r4, #0x0
	bl FUN_020048D0
	cmp r0, #0xff
	beq _0200536E
	bl FUN_02004018
	bl FUN_02003FF4
	bl NNS_SndHandleReleaseSeq
_0200536E:
	bl FUN_02005374
	pop {r4, pc}

	thumb_func_start FUN_02005374
FUN_02005374: ; 0x02005374
	push {r3, lr}
	mov r0, #0x0
	bl FUN_02004110
	mov r0, #0x0
	bl FUN_02004130
	mov r0, #0x0
	bl FUN_02003CE8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0200538C
FUN_0200538C: ; 0x0200538C
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02004124
	bl FUN_020048D0
	cmp r0, #0xff
	beq _020053C8
	bl FUN_02004018
	add r7, r0, #0x0
	cmp r4, #0x0
	bne _020053B2
	mov r1, #0x0
	add r2, r1, #0x0
	bl FUN_02004828
_020053B2:
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02004828
	add r0, r5, #0x0
	bl FUN_02004D74
	mov r0, #0x3
	bl FUN_02003CE8
_020053C8:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020053CC
FUN_020053CC: ; 0x020053CC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02004124
	bl FUN_020048D0
	add r6, r0, #0x0
	cmp r6, #0xff
	beq _02005402
	bl FUN_02005404
	cmp r0, #0x0
	bne _020053FC
	add r0, r6, #0x0
	bl FUN_02004018
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02004828
	add r0, r4, #0x0
	bl FUN_02004D74
_020053FC:
	mov r0, #0x4
	bl FUN_02003CE8
_02005402:
	pop {r4-r6, pc}

	thumb_func_start FUN_02005404
FUN_02005404: ; 0x02005404
	push {r3, lr}
	mov r0, #0x6
	bl FUN_02003D38
	ldrh r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02005410
FUN_02005410: ; 0x02005410
	push {r3, lr}
	bl FUN_020048D0
	bl FUN_020048BC
	pop {r3, pc}

	thumb_func_start FUN_0200541C
FUN_0200541C: ; 0x0200541C
	push {r3-r5, lr}
	mov r0, #0xf
	bl FUN_02003D38
	add r5, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x0
	bl NNS_SndPlayerStopSeqAll
	ldrb r0, [r5, #0x0]
	cmp r0, #0x1
	bne _02005440
	mov r0, #0xe
	bl FUN_02004AAC
_02005440:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _0200544C
	mov r0, #0xf
	bl FUN_02004AAC
_0200544C:
	mov r0, #0x0
	bl FUN_02003CE8
	pop {r3-r5, pc}

	thumb_func_start FUN_02005454
FUN_02005454: ; 0x02005454
	push {r3-r7, lr}
	mov r0, #0xf
	bl FUN_02003D38
	add r7, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x7
	bl FUN_02003FF4
	mov r1, #0x0
	bl NNS_SndPlayerStopSeq
	bl FUN_02005374
	mov r5, #0x0
	add r4, r5, #0x0
_0200547A:
	add r0, r5, #0x3
	add r1, r4, #0x0
	bl FUN_020054F8
	add r5, r5, #0x1
	cmp r5, #0x4
	blt _0200547A
	mov r0, #0x0
	bl FUN_02005614
	ldrb r0, [r7, #0x0]
	cmp r0, #0x1
	bne _0200549A
	mov r0, #0xe
	bl FUN_02004AAC
_0200549A:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _020054A6
	mov r0, #0xf
	bl FUN_02004AAC
_020054A6:
	pop {r3-r7, pc}

	thumb_func_start FUN_020054A8
FUN_020054A8: ; 0x020054A8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020054C8
	add r6, r0, #0x0
	ldr r1, _020054C4 ; =0x0000FFFF
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02005530
	add r0, r6, #0x0
	pop {r4-r6, pc}
	nop
_020054C4: .word 0x0000FFFF

	thumb_func_start FUN_020054C8
FUN_020054C8: ; 0x020054C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_020048D0
	bl FUN_02004018
	add r4, r0, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	bl NNS_SndArcPlayerStartSeq
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02004858
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020054F0
FUN_020054F0: ; 0x020054F0
	ldr r3, _020054F4 ; =NNS_SndPlayerStopSeqBySeqNo
	bx r3
	.balign 4
_020054F4: .word NNS_SndPlayerStopSeqBySeqNo

	thumb_func_start FUN_020054F8
FUN_020054F8: ; 0x020054F8
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02003FF4
	add r1, r4, #0x0
	bl NNS_SndPlayerStopSeq
	pop {r4, pc}

	thumb_func_start FUN_02005508
FUN_02005508: ; 0x02005508
	push {r3, lr}
	bl FUN_020048D0
	bl FUN_020048BC
	pop {r3, pc}

	thumb_func_start FUN_02005514
FUN_02005514: ; 0x02005514
	push {r4, lr}
	mov r4, #0x0
_02005518:
	add r0, r4, #0x3
	bl FUN_020048BC
	cmp r0, #0x1
	bne _02005526
	mov r0, #0x1
	pop {r4, pc}
_02005526:
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _02005518
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02005530
FUN_02005530: ; 0x02005530
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_020048D0
	bl FUN_02004018
	bl FUN_02003FF4
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl NNS_SndPlayerSetTrackPan
	pop {r3-r5, pc}

	thumb_func_start FUN_0200554C
FUN_0200554C: ; 0x0200554C
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r0, #0x3
	bl FUN_02004018
	ldr r7, _02005574 ; =0x0000FFFF
	add r4, r0, #0x0
	mov r5, #0x0
_0200555C:
	add r0, r4, r5
	bl FUN_02003FF4
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl NNS_SndPlayerSetTrackPan
	add r5, r5, #0x1
	cmp r5, #0x4
	blt _0200555C
	pop {r3-r7, pc}
	nop
_02005574: .word 0x0000FFFF

	thumb_func_start FUN_02005578
FUN_02005578: ; 0x02005578
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x11
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x23
	bl FUN_02003D38
	ldr r1, _02005610 ; =0x000001B9
	cmp r5, r1
	beq _0200559C
	add r1, #0x36
	cmp r5, r1
	bhi _0200559A
	cmp r5, #0x0
	bne _0200559C
_0200559A:
	mov r5, #0x1
_0200559C:
	ldr r1, _02005610 ; =0x000001B9
	cmp r5, r1
	bne _020055BC
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	mov r2, #0x7f
	add r3, r1, #0x0
	bl FUN_02005D48
	cmp r0, #0x1
	bne _020055BC
	mov r0, #0x0
	bl FUN_02005E80
	mov r0, #0x1
	pop {r3-r5, pc}
_020055BC:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020055E8
	mov r0, #0x0
	bl FUN_02005614
	mov r0, #0x1
	bl FUN_02003FF4
	mov r1, #0x2
	str r1, [sp, #0x0]
	sub r1, r1, #0x3
	add r2, r5, #0x0
	add r3, r1, #0x0
	bl NNS_SndArcPlayerStartSeqEx
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02004858
	b _02005606
_020055E8:
	mov r0, #0x8
	bl FUN_02003FF4
	mov r1, #0x2
	str r1, [sp, #0x0]
	sub r1, r1, #0x3
	add r2, r5, #0x0
	add r3, r1, #0x0
	bl NNS_SndArcPlayerStartSeqEx
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x8
	bl FUN_02004858
_02005606:
	mov r0, #0x0
	bl FUN_02005E80
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02005610: .word 0x000001B9

	thumb_func_start FUN_02005614
FUN_02005614: ; 0x02005614
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0xf
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0xe
	bl FUN_02003D38
	mov r0, #0x1
	bl FUN_02003FF4
	add r1, r5, #0x0
	bl NNS_SndPlayerStopSeq
	mov r0, #0x8
	bl FUN_02003FF4
	add r1, r5, #0x0
	bl NNS_SndPlayerStopSeq
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _02005658
	mov r0, #0xe
	bl FUN_02004C3C
	mov r0, #0xe
	bl FUN_02004A04
_02005658:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _0200566A
	mov r0, #0xf
	bl FUN_02004C3C
	mov r0, #0xf
	bl FUN_02004A04
_0200566A:
	bl FUN_02005DFC
	pop {r4-r6, pc}

	thumb_func_start FUN_02005670
FUN_02005670: ; 0x02005670
	push {r3-r5, lr}
	mov r0, #0xf
	bl FUN_02003D38
	add r5, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0xe
	bl FUN_02003D38
	ldrb r0, [r5, #0x0]
	cmp r0, #0x1
	bne _02005696
	mov r0, #0xe
	bl FUN_02004ABC
	pop {r3-r5, pc}
_02005696:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _020056A4
	mov r0, #0xf
	bl FUN_02004ABC
	pop {r3-r5, pc}
_020056A4:
	mov r0, #0x0
	bl FUN_020048BC
	pop {r3-r5, pc}

	thumb_func_start FUN_020056AC
FUN_020056AC: ; 0x020056AC
	push {r3-r7, lr}
	sub sp, #0x20
	str r0, [sp, #0x4]
	mov r0, #0xf
	str r1, [sp, #0x8]
	add r5, r2, #0x0
	add r6, r3, #0x0
	ldr r7, [sp, #0x38]
	bl FUN_02003D38
	str r0, [sp, #0x14]
	mov r0, #0x10
	bl FUN_02003D38
	str r0, [sp, #0x10]
	mov r0, #0x11
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x1d
	bl FUN_02003D38
	str r0, [sp, #0xc]
	mov r0, #0x23
	bl FUN_02003D38
	lsr r0, r5, #0x1f
	add r0, r5, r0
	asr r0, r0, #0x1
	str r0, [sp, #0x1c]
	add r0, #0x40
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	str r0, [sp, #0x18]
	sub r0, #0x1e
	str r0, [sp, #0x18]
	cmp r0, #0x0
	bgt _020056FC
	mov r0, #0x1
	str r0, [sp, #0x18]
_020056FC:
	mov r0, #0x0
	strb r0, [r4, #0x0]
	ldr r0, [sp, #0x14]
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02005714
	mov r0, #0xe
	bl FUN_02004C3C
	mov r0, #0xe
	bl FUN_02004A04
_02005714:
	ldr r0, [sp, #0x10]
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02005728
	mov r0, #0xf
	bl FUN_02004C3C
	mov r0, #0xf
	bl FUN_02004A04
_02005728:
	ldr r4, [sp, #0x8]
	ldr r0, _02005AB4 ; =0x000001B9
	add r1, r4, #0x0
	cmp r1, r0
	beq _0200573E
	add r0, #0x36
	cmp r1, r0
	bhi _0200573C
	add r0, r4, #0x0
	bne _0200573E
_0200573C:
	mov r4, #0x1
_0200573E:
	ldr r0, _02005AB4 ; =0x000001B9
	ldr r1, [sp, #0x8]
	cmp r1, r0
	bne _020057B4
	ldr r1, [sp, #0x4]
	cmp r1, #0xc
	bhi _020057AE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02005758: ; jump table (using 16-bit offset)
	.short _02005772 - _02005758 - 2; case 0
	.short _02005772 - _02005758 - 2; case 1
	.short _02005772 - _02005758 - 2; case 2
	.short _020057AE - _02005758 - 2; case 3
	.short _020057AE - _02005758 - 2; case 4
	.short _02005772 - _02005758 - 2; case 5
	.short _020057AE - _02005758 - 2; case 6
	.short _020057AE - _02005758 - 2; case 7
	.short _020057AE - _02005758 - 2; case 8
	.short _020057AE - _02005758 - 2; case 9
	.short _020057AE - _02005758 - 2; case 10
	.short _02005772 - _02005758 - 2; case 11
	.short _02005772 - _02005758 - 2; case 12
_02005772:
	bl FUN_02005578
	ldr r0, [sp, #0xc]
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02005794
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	b _020057A8
_02005794:
	ldr r1, [sp, #0x1c]
	mov r0, #0xe
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02004ACC
	mov r0, #0xe
	add r1, r6, #0x0
	bl FUN_02004AF8
_020057A8:
	add sp, #0x20
	mov r0, #0x1
	pop {r3-r7, pc}
_020057AE:
	mov r0, #0x1
	bl FUN_02005E80
_020057B4:
	ldr r0, [sp, #0x4]
	cmp r0, #0xe
	bls _020057BC
	b _02005AC2
_020057BC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020057C8: ; jump table (using 16-bit offset)
	.short _020057E6 - _020057C8 - 2; case 0
	.short _02005802 - _020057C8 - 2; case 1
	.short _02005826 - _020057C8 - 2; case 2
	.short _02005868 - _020057C8 - 2; case 3
	.short _020058B2 - _020057C8 - 2; case 4
	.short _02005900 - _020057C8 - 2; case 5
	.short _02005928 - _020057C8 - 2; case 6
	.short _0200596C - _020057C8 - 2; case 7
	.short _0200599C - _020057C8 - 2; case 8
	.short _020059CA - _020057C8 - 2; case 9
	.short _020059FE - _020057C8 - 2; case 10
	.short _02005A2E - _020057C8 - 2; case 11
	.short _02005A56 - _020057C8 - 2; case 12
	.short _02005A86 - _020057C8 - 2; case 13
	.short _02005ABC - _020057C8 - 2; case 14
_020057E6:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	b _02005AC2
_02005802:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x14
	add r1, r7, #0x0
	bl FUN_02005AE0
	b _02005AC2
_02005826:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	mov r2, #0x40
	bl FUN_02004D20
	add r0, r4, #0x0
	mov r1, #0x14
	bl FUN_02005BC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x8
	add r2, r5, #0x0
	bl FUN_02004D4C
	ldr r2, [sp, #0x18]
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02005AC8
	b _02005AC2
_02005868:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x1e
	add r1, r7, #0x0
	bl FUN_02005AE0
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	mov r2, #0xc0
	bl FUN_02004D20
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_02005BC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x8
	add r2, r5, #0x0
	bl FUN_02004D4C
	ldr r2, [sp, #0x18]
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02005AC8
	b _02005AC2
_020058B2:
	mov r0, #0xe
	bl FUN_02004984
	ldr r2, [sp, #0x1c]
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0xe
	str r7, [sp, #0x0]
	bl FUN_02004B30
	ldr r1, [sp, #0x1c]
	mov r0, #0xe
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02004ACC
	mov r0, #0xf
	add r1, r7, #0x0
	bl FUN_02005AE0
	mov r1, #0x86
	mov r0, #0xe
	lsl r1, r1, #0x8
	bl FUN_02004AE4
	mov r1, #0x3f
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	add r0, r4, #0x0
	mvn r1, r1
	str r7, [sp, #0x0]
	bl FUN_02005BF8
	mov r1, #0x86
	mov r0, #0xf
	lsl r1, r1, #0x8
	bl FUN_02004AE4
	b _02005AC2
_02005900:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x1
	add r2, r0, #0x0
	ldr r1, _02005AB8 ; =0x0000FFFF
	sub r2, #0xe1
	bl FUN_02004D20
	b _02005AC2
_02005928:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	mov r2, #0x2c
	bl FUN_02004D20
	mov r1, #0x3f
	add r0, r4, #0x0
	mvn r1, r1
	bl FUN_02005BC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x8
	add r2, r5, #0x0
	bl FUN_02004D4C
	ldr r2, [sp, #0x18]
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02005AC8
	b _02005AC2
_0200596C:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0xb
	add r1, r7, #0x0
	bl FUN_02005AE0
	mov r0, #0x1
	add r2, r0, #0x0
	ldr r1, _02005AB8 ; =0x0000FFFF
	sub r2, #0x81
	bl FUN_02004D20
	b _02005AC2
_0200599C:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x3c
	add r1, r7, #0x0
	bl FUN_02005AE0
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	mov r2, #0x3c
	bl FUN_02004D20
	b _02005AC2
_020059CA:
	mov r0, #0xe
	bl FUN_02004984
	ldr r2, [sp, #0x1c]
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0xe
	str r7, [sp, #0x0]
	bl FUN_02004B30
	ldr r1, [sp, #0x1c]
	mov r0, #0xe
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02004ACC
	mov r0, #0xd
	add r1, r7, #0x0
	bl FUN_02005AE0
	mov r1, #0x1a
	mov r0, #0xe
	lsl r1, r1, #0xa
	bl FUN_02004AE4
	b _02005AC2
_020059FE:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x64
	add r1, r7, #0x0
	bl FUN_02005AE0
	mov r0, #0x1
	add r2, r0, #0x0
	ldr r1, _02005AB8 ; =0x0000FFFF
	sub r2, #0x2d
	bl FUN_02004D20
	b _02005AC2
_02005A2E:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x1
	add r2, r0, #0x0
	ldr r1, _02005AB8 ; =0x0000FFFF
	sub r2, #0x61
	bl FUN_02004D20
	b _02005AC2
_02005A56:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x14
	add r1, r7, #0x0
	bl FUN_02005AE0
	mov r0, #0x1
	add r2, r0, #0x0
	ldr r1, _02005AB8 ; =0x0000FFFF
	sub r2, #0x61
	bl FUN_02004D20
	b _02005AC2
_02005A86:
	add r0, r4, #0x0
	bl FUN_02005578
	add r0, r4, #0x0
	mov r1, #0x1
	mov r2, #0x7f
	bl FUN_02005AC8
	add r0, r4, #0x0
	mov r1, #0x14
	bl FUN_02005BC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x8
	add r2, r5, #0x0
	bl FUN_02004D4C
	mov r0, #0x8
	add r1, r6, #0x0
	mov r2, #0x0
	bl FUN_02004828
	b _02005AC2
	.balign 4
_02005AB4: .word 0x000001B9
_02005AB8: .word 0x0000FFFF
_02005ABC:
	add r0, r4, #0x0
	bl FUN_02005578
_02005AC2:
	mov r0, #0x1
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_02005AC8
FUN_02005AC8: ; 0x02005AC8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, r2, #0x0
	bl FUN_0200483C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02004858
	pop {r3-r5, pc}

	thumb_func_start FUN_02005AE0
FUN_02005AE0: ; 0x02005AE0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x22
	bl FUN_02003D38
	add r6, r0, #0x0
	bl FUN_02005BA0
	add r0, r4, #0x0
	mov r1, #0x8
	bl AllocFromHeap
	add r4, r0, #0x0
	bne _02005B04
	bl ErrorHandling
	pop {r4-r6, pc}
_02005B04:
	mov r2, #0x0
	strb r2, [r4, #0x0]
	strb r2, [r4, #0x1]
	strb r2, [r4, #0x2]
	strb r2, [r4, #0x3]
	strb r2, [r4, #0x4]
	strb r2, [r4, #0x5]
	strb r2, [r4, #0x6]
	strb r2, [r4, #0x7]
	ldr r0, _02005B28 ; =FUN_02005B2C
	add r1, r4, #0x0
	str r5, [r4, #0x0]
	bl FUN_0200CA44
	str r0, [r4, #0x4]
	str r0, [r6, #0x0]
	pop {r4-r6, pc}
	nop
_02005B28: .word FUN_02005B2C

	thumb_func_start FUN_02005B2C
FUN_02005B2C: ; 0x02005B2C
	push {r4-r6, lr}
	mov r0, #0xf
	add r5, r1, #0x0
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	ldr r2, [r5, #0x0]
	add r4, r0, #0x0
	cmp r2, #0xa
	bne _02005B58
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_02004828
	ldr r2, [r5, #0x0]
	mov r0, #0x8
	mov r1, #0x0
	bl FUN_02004828
_02005B58:
	ldr r0, [r5, #0x0]
	sub r0, r0, #0x1
	str r0, [r5, #0x0]
	bl FUN_02005670
	cmp r0, #0x0
	bne _02005B6A
	mov r0, #0x0
	str r0, [r5, #0x0]
_02005B6A:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	bgt _02005B9E
	mov r0, #0x0
	bl FUN_02005614
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _02005B88
	mov r0, #0xe
	bl FUN_02004C3C
	mov r0, #0xe
	bl FUN_02004A04
_02005B88:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _02005B9A
	mov r0, #0xf
	bl FUN_02004C3C
	mov r0, #0xf
	bl FUN_02004A04
_02005B9A:
	bl FUN_02005BA0
_02005B9E:
	pop {r4-r6, pc}

	thumb_func_start FUN_02005BA0
FUN_02005BA0: ; 0x02005BA0
	push {r3-r5, lr}
	mov r0, #0x22
	bl FUN_02003D38
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02005BC2
	bl FUN_0201B6C8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0200CAB4
	add r0, r5, #0x0
	bl FreeToHeap
_02005BC2:
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02005BC8
FUN_02005BC8: ; 0x02005BC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x11
	add r4, r1, #0x0
	bl FUN_02003D38
	mov r1, #0x1
	strb r1, [r0, #0x0]
	add r0, r1, #0x0
	bl FUN_02005E80
	add r0, r5, #0x0
	bl FUN_02005578
	add r5, r0, #0x0
	ldr r1, _02005BF4 ; =0x0000FFFF
	mov r0, #0x8
	add r2, r4, #0x0
	bl FUN_02004D20
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4
_02005BF4: .word 0x0000FFFF

	thumb_func_start FUN_02005BF8
FUN_02005BF8: ; 0x02005BF8
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	mov r0, #0x11
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02003D38
	mov r1, #0x1
	strb r1, [r0, #0x0]
	mov r0, #0xf
	bl FUN_02004984
	ldr r0, [sp, #0x18]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0xf
	bl FUN_02004B30
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start PlayBGM
PlayBGM: ; 0x02005C28
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020048F4
	add r0, r5, #0x0
	bl FUN_02005CEC
	bl FUN_02004124
	bl FUN_020048D0
	cmp r0, #0xff
	beq _02005C48
	mov r1, #0x1
	bl FUN_020047C8
_02005C48:
	mov r0, #0x1c
	bl FUN_02003D38
	bl FUN_02003F3C
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_02003FA8
	mov r0, #0x2
	bl FUN_02003FF4
	add r1, r5, #0x0
	bl NNS_SndArcPlayerStartSeq
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_02004858
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02005C74
FUN_02005C74: ; 0x02005C74
	push {r4, lr}
	mov r0, #0xd
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x2
	bl FUN_020048BC
	cmp r0, #0x0
	beq _02005C8C
	mov r0, #0x1
	pop {r4, pc}
_02005C8C:
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02005C9A
	sub r0, r0, #0x1
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
_02005C9A:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02005CA0
FUN_02005CA0: ; 0x02005CA0
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x2
	bl FUN_02003FF4
	add r1, r4, #0x0
	bl NNS_SndPlayerStopSeq
	mov r0, #0x6
	bl FUN_02004748
	bl FUN_02003F64
	pop {r4, pc}

	thumb_func_start FUN_02005CBC
FUN_02005CBC: ; 0x02005CBC
	push {r3, lr}
	mov r0, #0xd
	bl FUN_02003D38
	bl FUN_02005C74
	cmp r0, #0x1
	bne _02005CD0
	mov r0, #0x1
	pop {r3, pc}
_02005CD0:
	mov r0, #0x0
	bl FUN_02005CA0
	bl FUN_02004124
	bl FUN_020048D0
	cmp r0, #0xff
	beq _02005CE8
	mov r1, #0x0
	bl FUN_020047C8
_02005CE8:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02005CEC
FUN_02005CEC: ; 0x02005CEC
	push {r3, lr}
	mov r0, #0xd
	bl FUN_02003D38
	mov r1, #0xf
	strh r1, [r0, #0x0]
	pop {r3, pc}
	.balign 4
